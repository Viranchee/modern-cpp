
#include "mlir/IR/Dialect.h"
#include "mlir/InitAllDialects.h"
#include "mlir/InitAllPasses.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include <cstddef>
#include <stdio.h>

// docs: https://mlir.llvm.org/docs/PatternRewriter/
// arith dialect: https://mlir.llvm.org/docs/Dialects/ArithOps/
// examples: https://github.com/llvm/llvm-project/tree/main/mlir/examples

namespace mlir {

using arith::ConstantIntOp;
using arith::ConstantOp;
using arith::ShLIOp;

// Merge multiple left shifts with constant value to a single left shift
// eg. (x << 4) << 16 => x << 20
struct LeftShiftPattern : public OpRewritePattern<ShLIOp> {
  LeftShiftPattern(mlir::MLIRContext *context)
      : OpRewritePattern<ShLIOp>(context, 1) {}

  void initialize() {
    setDebugName("LeftShift");
    addDebugLabels("ConstantFoldLeftShiftPass");
  }

  LogicalResult iterativeMatcher(ShLIOp inst4) const {

    // 1. %c4_i32 = arith.constant 4      : i32
    // 2. %c16_i32 = arith.constant 16    : i32
    // 3. %0 = arith.shli %arg0, %c4_i32  : i32
    // 4. %1 = arith.shli %0,   %c16_i32  : i32    <--- Match works for this

    // Check if the shift left value is a constant
    auto inst2 = inst4.getRhs().getDefiningOp<ConstantIntOp>();
    auto inst3 = inst4.getLhs().getDefiningOp<ShLIOp>();
    if (!inst2 || !inst3) {
      return failure();
    }
    // Check if the shift left's shift left value is a constant shifter
    auto inst1 = inst3.getRhs().getDefiningOp<ConstantIntOp>();
    if (!inst1) {
      return failure();
    }

    return success();
  }

  LogicalResult match(ShLIOp inst4) const override {
    return iterativeMatcher(inst4);
  }

  void rewrite(ShLIOp inst4, PatternRewriter &rewriter) const override {
    auto inst2 = inst4.getRhs().getDefiningOp<ConstantIntOp>();
    auto inst3 = inst4.getLhs().getDefiningOp<ShLIOp>();
    auto inst1 = inst3.getRhs().getDefiningOp<ConstantIntOp>();
    const auto shiftAmount = inst1.value() + inst2.value();
    const auto width = inst1.getType().getIntOrFloatBitWidth();
    const auto variable = inst3.getLhs();

    // /*
    // This if/else block could be removed, or combined with the below
    // instruction
    if (shiftAmount > width) {
      // TODO: If shift amount > int width, use 0
      auto zero = rewriter.create<ConstantOp>(
          inst1->getLoc(), rewriter.getIntegerAttr(inst1.getType(), 0));
      ValueRange newZero = {zero};
      rewriter.replaceOp(inst4, newZero);
      rewriter.eraseOp(inst1);
      rewriter.eraseOp(inst2);
      rewriter.eraseOp(inst3);
      rewriter.eraseOp(inst4);
      return;
    }
    // */

    ConstantIntOp arithConstantValue = rewriter.create<ConstantIntOp>(
        inst1.getLoc(), /*value*/ shiftAmount,
        /*width*/ inst1.getType().getIntOrFloatBitWidth());
    // WARN: Why did I have to create ValueRange?
    // The rewriter.replace(op, newOp) did not work
    ValueRange newConst = {arithConstantValue};
    rewriter.replaceOp(inst1, newConst);
    rewriter.eraseOp(inst1);
    ShLIOp newShl =
        rewriter.create<ShLIOp>(inst4.getLoc(), variable, arithConstantValue);
    ValueRange newShlRange = {newShl};
    rewriter.replaceOp(inst4, newShlRange);
    rewriter.eraseOp(inst2);
    rewriter.eraseOp(inst3);
    rewriter.eraseOp(inst4);
  }
};

class MultiToShiftPass
    : public PassWrapper<MultiToShiftPass, OperationPass<func::FuncOp>> {
private:
  StringRef getArgument() const final { return "instcombine"; }

  StringRef getDescription() const final {
    return "A simple shift left combiner";
  }

  void runOnOperation() override {
    RewritePatternSet patterns(&getContext());
    patterns.add<LeftShiftPattern>(&getContext());
    (void)applyPatternsAndFoldGreedily(getOperation(), std::move(patterns));
  }
};

} // namespace mlir

int main(int argc, char **argv) {
  mlir::registerAllPasses();
  mlir::PassRegistration<mlir::MultiToShiftPass>();

  mlir::DialectRegistry registry;
  registerAllDialects(registry);

  return mlir::asMainReturnCode(
      mlir::MlirOptMain(argc, argv, "Custom optimizer driver\n", registry));
}

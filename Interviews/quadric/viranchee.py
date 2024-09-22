#! /usr/bin/env python3

class Call:
  
    def __init__(self, op):
        self._op = op
        self._operand = []

    def __call__(self, *n):
        self._operand.extend(list(n))
        return self
    
    def deepCopy(self):
        new_call = Call(self._op)
        for n in self._operand:
            new_call._operand.append(n.deepCopy())
        return new_call
  
def print_graph(call, done={}):
    if call not in done:
        args = []
        for n in call._operand:
            args.append(print_graph(n, done))
        done[call] = len(done)+1
        print(f"%{done[call]} = {call._op}","(",','.join("%"+str(item) for item in args),")")
    return done[call]

def op_commoning(call: Call):
    computed = {}
    
    def recurse_remove_common(node: Call):
        if not node._operand:
            return node._op
        return_value = ""
        for i in range(len(node._operand)):
            res = recurse_remove_common(node._operand[i])
            return_value += res
            if res in computed:
                node._operand[i] = computed[res]
            else:
                computed[res] = node._operand[i]
        return return_value + node._op
    recurse_remove_common(call)
    return call


def example():
    input = Call('A')
    c = Call('C')(Call('B')(Call('A')(input)))
    d = Call('D')(Call('B')(Call('A')(input)))
    output = Call('Z')(c, d)
    print("\nOriginal:\n")
    print_graph(output, done={})

    mod_call = op_commoning(output.deepCopy())

    print("\nModified:\n")
    print_graph(mod_call, done={})


if __name__ == "__main__":
    example()
    
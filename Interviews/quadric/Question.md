Task 1
Given a program expressed in the given IR, an example of which is given in the following code snippet, your goal is to implement the "op_commoning function that performs op commoning. The function should find all common chains of calls, that is calls applied to the same exact inputs, and transform the program so that each of these identical calls are executed just once instead of multiple times. Your solution should improve the performance of programs without affecting their semantics.

```
Example Input IR:
%1 = 1( )
%2 = A (%1 )
%3 = B ( %2)
%4 = C ( %3)
%5 = A (%1 )
%6 = B (%5)
%7 = D (%6 )
%8 = Z ( %4, %7)
Example Output where op A and op B have been commoned:
%1 = 1( )
%2 = A (%1 )
%3 = B (%2 )
%4 = C ( %3)
%5 = D (%3)
%6 = Z ( %4, %5)
```

The initial code for IR data structure is provided below: 

```
class Call:
def _init_(self, op):
self._op = op
self._operand = 0
def _call_(self, *n):
self._operand.extend(list(n))
return self
def print_graph(call, done=0):
if call not in done:
args = 0
for n in call._ operand:
args.append(print_graph(n, done))
done[call] = len(done) +1
print(f"%{done|call]} = {call. op)""(* join("%"+str (item) for item in args)." ")
return donelcalll
def op_commoning (call):
# write your implementation here 
```

Example Input Graph
input = Call('A')
c = Call(C)(Call(B') (Call(A)(input)))
d = Call('D')(Call(B')(Call(A)(input)))
output = Call(2)(c, d)
print_graphoutput)
mod_call = op_commoning(output)
print_graph(mod_call)
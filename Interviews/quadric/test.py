class Call:
    def __init__(self, op):
        self._op = op
        self._operand = []
    
    def __call__(self, *n):
        self._operand. extend(list(n))
        return self

def op_commoning(call: Call):
    map = {}
    def rec(node: Call):
        if not node._operand:
            return node._op
        to_return = ""
        for i in range(len(node._operand)):
            res = rec(node._operand[i])
            to_return+=res
            if(res in map):
                node._operand[i] = map[res]
            else:
                map[res] = node._operand[i]
        return to_return + node._op
    rec(call)
    return 

def print_graph(call, done={}):
    if call not in done:
        args = []
        for n in call._operand:
            args.append(print_graph(n, done))
        done[call] = len(done)+1
        print(f"%{done[call]} = {call._op}","(",','.join("%"+str(item) for item in args),")")
    return done[call]


# Example Input Graph
input = Call('A')
x = Call('X')
c = Call('C')(Call('B')(Call('A')(input), x))
d = Call('D')(Call('B')(Call('A')(input), Call('X')))
output = Call('Z')(c, d)
print_graph(output)
print("after \n")
mod_call = op_commoning(output)
# print_graph(output, {})
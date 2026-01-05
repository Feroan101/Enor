import sys
from tokenizer import tokenize, read_source
from validator import address_pass, label_pass, valid_pass
from parser import resolve_operands
from emitter import emit_bytecode

def main():
    if len(sys.argv) != 3:
        print("usage: assembler <input.asm> <output.bin>")
        sys.exit(1)
    
    source = read_source(sys.argv[1])
    if source is None:
        return 1
    
    output = sys.argv[2]

    tokens = tokenize(source)             # tokenize asm (seperate values)
    if tokens == 1:
        return tokens

    symbol_table = label_pass(tokens)   # generate symbol_tabel
    if symbol_table == 3:
        return symbol_table

    rc = valid_pass(tokens, symbol_table)            # checks instruction
    if rc != 0:
        return rc
    
    rc = address_pass(tokens)                        # assign physical byte index
    if rc != 0:
        return rc
    
    rc = resolve_operands(tokens, symbol_table)      # turns operands into actual values (instead of list) and turn labels in JMPs to a byte offset
    if rc != 0:
        return rc
    
    rc = emit_bytecode(tokens, output)               # outta this fucking hellhole
    if rc != 0:
        return rc

    return VM_OK

if __name__ == '__main__':
    sys.exit(main())
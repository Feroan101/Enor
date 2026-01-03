import sys

opcodes = {
    "HALT": { "opcode": 0xFF, "operands": 0},
    "NOP":  { "opcode": 0x00, "operands": 0}, 
    "PUSH": { "opcode": 0x01, "operands": 1}, 
    "POP":  { "opcode": 0x02, "operands": 0}, 
    "ADD":  { "opcode": 0x03, "operands": 0}, 
    "SUB":  { "opcode": 0x04, "operands": 0}, 
    "MUL":  { "opcode": 0x05, "operands": 0}, 
    "DIV":  { "opcode": 0x06, "operands": 0}, 
    "DUP":  { "opcode": 0x07, "operands": 0}, 
    "JMP":  { "opcode": 0x08, "operands": 1}, 
    "JZ":   { "opcode": 0x09, "operands": 1}, 
    "PRINT":{ "opcode": 0x0A, "operands": 0}, 
    "LOAD": { "opcode": 0x0B, "operands": 1},
    "STORE":{ "opcode": 0x0C, "operands": 1},
    "SWAP": { "opcode": 0x0D, "operands": 0},
    "EQ":   { "opcode": 0x0E, "operands": 0},
    "LT":   { "opcode": 0x0F, "operands": 0}
    }

def read_source(file_path):
    with open(file_path, 'r') as asm:
        return (asm.readlines())    # reads asm from file
   
def label_pass(tokens):
    symbol_table = {}
    instruction_counter = 0
    for token in tokens:
        if (token["type"] == "instruction"):
            instruction_counter += 1
            continue
        
        name = token["name"]
        line = token["line"]
        for name in symbol_table: # checks for repeats
            print(f"ERROR: label { name } at line { line } already exists")
            return 3

        symbol_table[name] = instruction_counter
        
    return(symbol_table)

def valid_pass(tokens, symbols):
    for token in tokens:
        if (token["type"] == "label"):
            continue

        opcode = token["opcode"]
        line = token["line"]
        operands = token["operands"]

        # Check opcode exists
        if (not opcode in opcodes):
            print(f"ERROR: { opcode } is not a valid opcode at line { line }")
            return 2

        expected = opcodes[opcode]["operands"]
        # Check operand count matches
        if (len(operands) != expected):
            print(f"ERROR: { opcode } expects { expected } operands but got { len(operands) } at line { line }")
            return 2
        
        # check operand type
        for op in operands:
            if (op.lstrip('-').isdigit()):
                continue
            elif (op.isalnum() and op[0].isalpha()):
                if (not op in symbols): # jmp and stuff
                    print(f"ERROR: label { op } at line { line } doesnt exist")
                    return 2
            else:
                print(f"ERROR: invalid operand '{ op }' at line { line }")
                return 2
        
    return 0

def tokenize(lines):
    tokenized_lines = []
    source_line = 1

    for line in lines:
        line = line.strip()         # rm whitespaces 
        line = line.split("//", 1)[0]  # rm comments (//)
        line = line.split()         # tokenize

        if not line: # checks empty line
            source_line += 1
            continue

        line_num = source_line
        source_line += 1

        if (line[0].endswith(':')): # checks for labels
            line_type = 'label'
            if (len(line) > 1):
                print(f"ERROR: invaid use of labels at line {line_num}")
                return 1
            
            line_name = line[0][:-1].lower()
            if (not line_name or not line_name.isalpha()):
                print(f"ERROR: tried to fuck a label at line {line_num}")
                return 1
  
            token = dict(type= line_type, name = line_name, line = line_num)
            tokenized_lines.append(token)
            continue 
        else: 
            line_type = 'instruction'

        line_opcode = line[0].upper() # opcode
        if (not line_opcode.isalpha()):
            print(f"ERROR: found garbage(you) at line: {line_num}")
            return 1

        # wrong operand count
        line_operands = line[1:]

        token = dict(type = line_type, opcode = line_opcode, operands = line_operands, line = line_num)
        tokenized_lines.append(token)

    return(tokenized_lines)

def main():
    if len(sys.argv) < 1:
        print(f"useage:python3 {sys.argv[0]} <assembly.asm>")
        return 1
    
    source = read_source(f"../programs/{sys.argv[1]}") # change path later
    # print(source)
    tokens = tokenize(source)
    symbol_table = label_pass(tokens)
    valid_pass(tokens, symbol_table)

if __name__ == '__main__':
    main()
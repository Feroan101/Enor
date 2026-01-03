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

'''
def tokenError(token): # idek wtf this shii is please ignore this fn
    for t in token:
        if (t["type"] == "label"):
            token_oprand = t["operands"]
            token_opcode = t["opcode"]
            # garbage line

            # no opcode and unknown opcode - validator
            if (token_opcode not in opcodes):
                print(f"ERROR: at line: {t["line"]}")
                return 2

            # check datatype - validator
            for oprand in token_oprand:
                if (type(oprand) is not int ):
                    print(f"ERROR: at line: {t["line"]}")

            if(len(line_operands) != opcodes[line_opcode]["operands"]):
                print(f"ERROR: at line: {line_num}")
                return 1

            #check label repeats
            #undefined labels   
            #relative jump overflow
'''

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
            
            line_name = line[0][:-1]
            if (not line_name or not line_name.isalpha()):
                print(f"ERROR: tried to fuck a label at line {line_num}")
                return 1
  
            token = dict(type= line_type, name = line_name, line = line_num)
            tokenized_lines.append(token)
            continue 
        else: 
            line_type = 'instruction'

        line_opcode = line[0] # opcode
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

if __name__ == '__main__':
    main()
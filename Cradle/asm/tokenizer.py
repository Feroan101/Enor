def read_source(file_path):
    with open(file_path, 'r') as asm:
        return (asm.readlines())    # reads asm from file
    
def tokenize(lines):
    tokenized_lines = []
    source_line = 1

    for line in lines:
        line = line.strip()             # rm whitespaces 
        line = line.split("//", 1)[0]   # rm comments (//)
        line = line.split()             # tokenize

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
            
            line_name = line[0][:-1].lower() # label
            if (not line_name or not line_name.isalpha()): # checks label is empty or not alpha
                print(f"ERROR: invalid label name at line {line_num}")
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
        line_operands = line[1:] # operands

        token = dict(type = line_type, opcode = line_opcode, operands = line_operands, line = line_num)
        tokenized_lines.append(token)

    return(tokenized_lines)
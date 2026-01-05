from opcodes import opcodes

def address_pass(tokens): # assign physical byte index
    ip = 0
    for token in tokens:
        if token["type"] != "instruction":
            continue

        token["ip"] = ip
        
        operand_count = opcodes[token["opcode"]]["operands"]   
        instruction_size = 1 + (operand_count * 2)
        
        ip += instruction_size

    return 0

def label_pass(tokens):  # creates a symbol table for label lookup
    symbol_table = {}
    ip = 0  # byte address

    for token in tokens:
        if token["type"] == "label":
            name = token["name"]
            line = token["line"]

            if name in symbol_table:
                print(f"ERROR: label {name} at line {line} already exists")
                return 3

            symbol_table[name] = ip
            continue

        ip += 1 + 2 * len(token["operands"]) # ip = 1 byte opcode + 2 bytes per operand

    return symbol_table


def valid_pass(tokens, symbols): # checks instruction
    for token in tokens:
        if (token["type"] == "label"): # ignore labels
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
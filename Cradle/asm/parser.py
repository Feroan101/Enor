      
def resolve_operands(tokens, symbols): # turn labels in JMPs to byte and operands to int
    for token in tokens:
        if token["type"] != "instruction":
            continue

        opcode = token["opcode"]
        operands = token["operands"]
        resolved = []

        for op in operands:
            # Immediate integer
            if op.lstrip('-').isdigit():
                resolved.append(int(op))
                continue
            
            # jump labels
            if opcode not in ("JMP", "JZ"):
                print(f"ERROR: label operand not allowed for {opcode} at line {token['line']}")
                return 4
            
            if (op not in symbols):
                print(f"ERROR: undefined label '{op}' at line {token['line']}")
                return 4
            
            offset = symbols[opcode] - (token["ip"] + 1) # offset = target_ip - (current_ip + instruction_size)
            resolved.append(offset)

        token["operands"] = resolved

    return 0

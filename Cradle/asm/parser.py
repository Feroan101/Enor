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
            
            # Jump labels
            if opcode not in ("JMP", "JZ", "JNZ"):
                print(f"ERROR: label operand not allowed for {opcode} at line {token['line']}")
                return 4
            
            if op not in symbols:
                print(f"ERROR: undefined label '{op}' at line {token['line']}")
                return 4
            
            target_ip = symbols[op]  # absolute byte offset of the label
            resolved.append(target_ip)

        token["operands"] = resolved

    return 0

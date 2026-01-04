from opcodes import opcodes

def emit_bytecode(tokens, path):
    bytecode = bytearray()
    for token in tokens:
        if (token["type"] == "label"):
            continue
        
        opcode = token["opcode"]
        operands = token["operands"]

        opcode_byte = opcodes[opcode]["opcode"]
        bytecode.append(opcode_byte)

        for op in operands:
            value = int(op)
            bytecode.extend(value.to_bytes(2, byteorder="little", signed=True))

    with open(path, 'wb') as out:
        out.write(bytecode)
        
    # print(f"code emitted at {path}")
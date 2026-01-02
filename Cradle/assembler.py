# ONLY FOR TESTING
# creating bin files

#NOP - 0x00
#PUSH - 0x01
#POP - 0x02
#ADD - 0x03
#SUB - 0x04
#MUL - 0x05
#DIV - 0x06
#DUP - 0x07
#JMP - 0x08 
#JZ - 0x09
#PRINT = 0x0A

opcodes = {
        "HALT": 0xFF,
        "NOP": 0x00, 
        "PUSH": 0x01, 
        "POP": 0x02, 
        "ADD": 0x03, 
        "SUB": 0x04, 
        "MUL": 0x05, 
        "DIV": 0x06, 
        "DUP": 0x07, 
        "JMP": 0x08, 
        "JZ": 0x09, 
        "PRINT": 0x0A, 
        }

code = []

with open("assembly.s", "r") as ass:
    content = ass.read()


Lines = content.split()
for line in Lines:
    if line in opcodes:
        code.append(opcodes[line])
    elif line.isnumeric():
        code.append(int(line))
    else:
        print(line + " is a invalid instruction")
    
print(code)

with open("program.bin", "wb") as f:
    f.write(bytes(code))
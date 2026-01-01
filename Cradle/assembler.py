# ONLY FOR TESTING
# creating bin files

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

code = [
    0x01, 0x03,   # 0: PUSH 3

    0x07,         # 2: DUP
    0x09, 0x0A,   # 3: JZ 10 (HALT)

    0x01, 0x01,   # 5: PUSH 1
    0x04,         # 7: SUB

    0x08, 0x02,   # 8: JMP 2 (back to DUP)

    0xFF          # 10: HALT
]


with open("program.bin", "wb") as f:
    f.write(bytes(code))
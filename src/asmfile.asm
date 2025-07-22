section .data
    msg_format db "%s", 0
    msg_1 db "Running function 'imgCvtGrayFloatToInt'...", 10, 0
    msg_2 db "Done!", 10, 10, 0

section .text
    bits 64
    default rel
    global imgCvtGrayFloatToInt
    extern printf

imgCvtGrayFloatToInt:
    call printRun

    ;TODO: continue here

    call printDone
    ret

printRun:
    sub rsp, 8*8
    lea rcx, msg_format
    lea rdx, msg_1
    call printf
    add rsp, 8*8
    ret

printDone:
    sub rsp, 8*8
    lea rcx, msg_format
    lea rdx, msg_2
    call printf
    add rsp, 8*8
    ret
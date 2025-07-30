section .data
multiplier dd 255.0

section .text
bits 64
default rel
global imgCvtGrayFloatToInt

; rcx   : int imgHeight         (height of the image in pixels)
; rdx   : int imgWidth          (width of the image in pixels)
; r8    : float *imgFloatRep    (pointer to an array of the image's float representation)
; r9    : int *imgIntRep        (pointer to an array of the image's int representation)
imgCvtGrayFloatToInt: ; TODO: Implement the function
    imul rcx, rdx

    L1: 
        movss xmm1, [r8]
        mulss xmm1, [multiplier]
        cvtss2si eax, xmm1
        mov [r9], eax
        add r8, 4
        add r9, 4
        LOOP L1
    ret
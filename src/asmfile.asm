section .text
    bits 64
    default rel
    global imgCvtGrayFloatToInt

; rcx   : int imgHeight         (height of the image in pixels)
; rdx   : int imgWidth          (width of the image in pixels)
; r8    : float *imgFloatRep    (pointer to an array of the image's float representation)
; r9    : int *imgIntRep        (pointer to an array of the image's int representation)
imgCvtGrayFloatToInt:
    ; TODO: Implement the function

    ret
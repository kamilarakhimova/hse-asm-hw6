section .rodata           ; for constant objects
  const3 dq 3.0
  const5 dq 5.0
  
section .text
global f1               ; f1 = 2**x + 1
f1:
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    fld1
    fscale
    fyl2x
    fdiv st0, st1
    fsubp st1, st0
    f2xm1
    fld1
    faddp st1, st0
    fld qword[ebp + 8]
    fld1
    fscale
    fstp st1
    fmulp st1, st0
    fld1
    faddp st1, st0
    mov esp, ebp
    pop ebp
    ret
 
global f2               ; f2 = x**5 = x * x * x * x * x
f2:
  push ebp
  mov ebp, esp
  finit
  fld qword[ebp + 8]
  fld qword[ebp + 8]
  fld qword[ebp + 8]
  fld qword[ebp + 8]
  fld qword[ebp + 8]
  fmulp
  fmulp
  fmulp
  fmulp
  mov esp, ebp
  pop ebp
  ret
  
global f3               ; f3 = (1 - x) / 3
f3:
  push ebp
  mov ebp, esp
  finit
  fld1
  fld qword[ebp + 8]
  fsubp st1, st0
  fld qword[const3]
  fdivp st1, st0
  mov esp, ebp
  pop ebp
  ret
  
global f1_diff          ; f1_diff = 2**x * ln(2)
f1_diff:
  push ebp
  mov ebp, esp
  finit
  fld qword[ebp + 8]
  fld qword[ebp + 8]
  fld1
  fscale
  fyl2x
  fdiv st0, st1
  fsubp st1, st0
  f2xm1
  fld1
  faddp st1, st0
  fld qword[ebp + 8]
  fld1
  fscale
  fstp st1
  fmulp st1, st0
  fldln2
  fmulp st1, st0
  mov esp, ebp
  pop ebp
  ret

global f2_diff          ; f2_diff = 5 * x**4 = 5 * x * x * x * x
f2_diff:
  push ebp
  mov ebp, esp
  finit
  fld qword[const5]
  fld qword[ebp + 8]
  fld qword[ebp + 8]
  fld qword[ebp + 8]
  fld qword[ebp + 8]
  fmulp
  fmulp
  fmulp
  fmulp
  mov esp, ebp
  pop ebp
  ret

global f3_diff          ; f3_diff = - 1 / 3
f3_diff:
  push ebp
  mov ebp, esp
  finit
  fld1
  fld qword[const3]
  fdivp st1, st0
  fchs
  mov esp, ebp
  pop ebp
  ret

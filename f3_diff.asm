section .rodata           ; for constant objects
  const dq 3.0

section .text
global f3_diff          ; f3_diff = - 1 / 3
f3_diff:
  fld1
  fld qword[const]
  fdivp
  fchs
  ret

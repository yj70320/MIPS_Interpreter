        .text
        .globl main
        
main:   li      $t0, 10
        li      $t1, 1
        li      $t2, 5
        
cal:    add     $a0, $t0, $t1

        li      $v0, 1
        syscall

exit:   li      $v0, 10
        syscall

        .data
L:      .asciiz "hello\n"

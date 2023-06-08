	.file	"26_true_void_func_stmt.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	func
	.type	func, @function
func:
	addi	sp,sp,-48
	sd	s0,40(sp)
	addi	s0,sp,48
	mv	a5,a0
	sw	a5,-36(s0)
	li	a5,2
	sw	a5,-36(s0)
	li	a5,3
	sw	a5,-20(s0)
	lw	a4,-36(s0)
	lw	a5,-20(s0)
	addw	a5,a4,a5
	sw	a5,-36(s0)
	nop
	ld	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	func, .-func
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32
	li	a5,4
	sw	a5,-20(s0)
	li	a5,2
	sw	a5,-24(s0)
	lw	a5,-24(s0)
	mv	a0,a5
	call	func
	lw	a5,-20(s0)
	mv	a0,a5
	ld	ra,24(sp)
	ld	s0,16(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 10.2.0"

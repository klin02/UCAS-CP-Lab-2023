	.file	"11_true_unaop.c"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sd	s0,24(sp)
	addi	s0,sp,32
	sb	zero,-17(s0)
	lbu	a5,-17(s0)
	sext.w	a5,a5
	snez	a5,a5
	andi	a5,a5,0xff
	xori	a5,a5,1
	andi	a5,a5,0xff
	sext.w	a5,a5
	sb	a5,-18(s0)
	lbu	a5,-18(s0)
	andi	a5,a5,1
	sb	a5,-18(s0)
	li	a5,0
	mv	a0,a5
	ld	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (g2ee5e430018) 12.2.0"

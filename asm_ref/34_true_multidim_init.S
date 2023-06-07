	.file	"34_true_multidim_init.c"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.globl	a
	.section	.rodata
	.align	3
	.type	a, @object
	.size	a, 72
a:
	.word	1
	.word	2
	.word	3
	.word	4
	.zero	8
	.zero	48
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-48
	sd	s0,40(sp)
	addi	s0,sp,48
	sd	zero,-40(s0)
	sd	zero,-32(s0)
	sd	zero,-24(s0)
	li	a5,1
	sw	a5,-40(s0)
	li	a5,2
	sw	a5,-36(s0)
	li	a5,3
	sw	a5,-32(s0)
	li	a4,0
	lw	a5,-28(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	mv	a0,a5
	ld	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	main, .-main
	.ident	"GCC: (g2ee5e430018) 12.2.0"

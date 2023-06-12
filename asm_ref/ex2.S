	.file	"ex.c"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.section	.text.startup,"ax",@progbits
	.align	2
	.globl	main
	.type	main, @function
main:
	li	a0,0
	ret
	.size	main, .-main
	.globl	ed
	.globl	gg
	.globl	b
	.globl	a
	.globl	bl
	.globl	bll
	.data
	.align	3
	.type	b, @object
	.size	b, 16
b:
	.word	1067030938
	.word	1078774989
	.zero	8
	.bss
	.align	3
	.type	gg, @object
	.size	gg, 16
gg:
	.zero	16
	.section	.sbss,"aw",@nobits
	.align	2
	.type	a, @object
	.size	a, 4
a:
	.zero	4
	.section	.sdata,"aw"
	.align	3
	.type	bl, @object
	.size	bl, 2
bl:
	.byte	1
	.byte	0
	.type	bll, @object
	.size	bll, 1
bll:
	.byte	1
	.section	.srodata,"a"
	.align	2
	.type	ed, @object
	.size	ed, 4
ed:
	.zero	4
	.ident	"GCC: (g2ee5e430018) 12.2.0"

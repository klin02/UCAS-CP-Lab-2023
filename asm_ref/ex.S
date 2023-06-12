	.file	"ex.c"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.globl	bll
	.section	.sdata,"aw"
	.type	bll, @object
	.size	bll, 1
bll:
	.byte	1
	.globl	bl
	.align	3
	.type	bl, @object
	.size	bl, 2
bl:
	.byte	1
	.byte	0
	.globl	a
	.section	.sbss,"aw",@nobits
	.align	2
	.type	a, @object
	.size	a, 4
a:
	.zero	4
	.globl	b
	.data
	.align	3
	.type	b, @object
	.size	b, 16
b:
	.word	1067030938
	.word	1078774989
	.zero	8
	.globl	gg
	.bss
	.align	3
	.type	gg, @object
	.size	gg, 16
gg:
	.zero	16
	.globl	ed
	.section	.srodata,"a"
	.align	2
	.type	ed, @object
	.size	ed, 4
ed:
	.zero	4
	.section	.rodata
	.align	3
.LC0:
	.word	1
	.word	2
	.word	3
	.word	4
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-112
	sd	s0,104(sp)
	addi	s0,sp,112
	li	a5,5
	sw	a5,-20(s0)

	sh	zero,-64(s0)
	sb	zero,-62(s0)
	li	a5,1
	sb	a5,-64(s0)
	
	lui	a5,%hi(.LC0)
	addi	a5,a5,%lo(.LC0)
	ld	a4,0(a5)
	sd	a4,-80(s0)
	ld	a5,8(a5)
	sd	a5,-72(s0)
	
	sd	zero,-112(s0)
	sd	zero,-104(s0)
	sd	zero,-96(s0)
	sd	zero,-88(s0)
	lui	a5,%hi(.LC1)
	fld	fa5,%lo(.LC1)(a5)
	fsd	fa5,-112(s0)
	lui	a5,%hi(.LC2)
	fld	fa5,%lo(.LC2)(a5)
	fsd	fa5,-104(s0)
	
	lui	a5,%hi(.LC3)
	fld	fa5,%lo(.LC3)(a5)
	fsd	fa5,-32(s0)
	
	lui	a5,%hi(a)
	lw	a5,%lo(a)(a5)
	sw	a5,-36(s0)
	lw	a5,-20(s0)
	sw	a5,-40(s0)
	lw	a5,-76(s0)
	sw	a5,-44(s0)
	lui	a5,%hi(b+4)
	flw	fa5,%lo(b+4)(a5)

	fsw	fa5,-48(s0)
	fld	fa5,-104(s0)
	fsd	fa5,-56(s0)
	li	a5,0
	mv	a0,a5
	ld	s0,104(sp)
	addi	sp,sp,112
	jr	ra
	.size	main, .-main
	.section	.rodata
	.align	3
.LC1:
	.word	-1717986918
	.word	1072798105
	.align	3
.LC2:
	.word	-1717986918
	.word	1073846681
	.align	3
.LC3:
	.word	-343597384
	.word	1073920081
	.ident	"GCC: (g2ee5e430018) 12.2.0"

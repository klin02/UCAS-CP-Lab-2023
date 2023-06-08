	.file	"array.c"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.globl	b
	.section	.sbss,"aw",@nobits
	.align	2
	.type	b, @object
	.size	b, 4
b:
	.zero	4
	.globl	a1
	.data
	.align	3
	.type	a1, @object
	.size	a1, 36
a1:
	.word	1
	.zero	8
	.word	2
	.word	3
	.zero	4
	.word	4
	.zero	8
	.section	.rodata
	.align	3
.LC0:
	.word	1
	.word	2
	.word	3
	.word	4
	.text
	.align	2
	.globl	func
	.type	func, @function
func:
	addi	sp,sp,-64
	sd	s0,56(sp)
	addi	s0,sp,64
	sd	a0,-56(s0)
	sd	a1,-64(s0)
	li	a5,3
	sw	a5,-20(s0)
	ld	a5,-64(s0)
	flw	fa5,8(a5)
	fsw	fa5,-24(s0)
	lui	a5,%hi(.LC0)
	addi	a5,a5,%lo(.LC0)
	ld	a4,0(a5)
	sd	a4,-40(s0)
	ld	a5,8(a5)
	sd	a5,-32(s0)
	li	a5,6
	sw	a5,-28(s0)
	ld	a5,-56(s0)
	lw	a5,8(a5)
	mv	a0,a5
	ld	s0,56(sp)
	addi	sp,sp,64
	jr	ra
	.size	func, .-func
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-144
	sd	ra,136(sp)
	sd	s0,128(sp)
	addi	s0,sp,144
	sd	zero,-56(s0)
	sd	zero,-48(s0)
	sd	zero,-40(s0)
	sd	zero,-32(s0)
	sw	zero,-24(s0)
	li	a5,1
	sw	a5,-56(s0)
	li	a5,2
	sw	a5,-44(s0)
	li	a5,3
	sw	a5,-40(s0)
	li	a5,4
	sw	a5,-32(s0)
	lui	a5,%hi(a1)
	addi	a5,a5,%lo(a1)
	li	a4,3
	sw	a4,0(a5)
	li	a5,5
	sw	a5,-24(s0)
	lui	a5,%hi(.LC1)
	flw	fa5,%lo(.LC1)(a5)
	fsw	fa5,-64(s0)
	addi	a5,s0,-72
	mv	a1,a5
	lui	a5,%hi(a1+24)
	addi	a0,a5,%lo(a1+24)
	call	func
	mv	a5,a0
	sw	a5,-20(s0)
	sd	zero,-144(s0)
	sd	zero,-136(s0)
	sd	zero,-128(s0)
	sd	zero,-120(s0)
	sd	zero,-112(s0)
	sd	zero,-104(s0)
	sd	zero,-96(s0)
	sd	zero,-88(s0)
	sd	zero,-80(s0)
	lui	a5,%hi(.LC2)
	fld	fa5,%lo(.LC2)(a5)
	fsd	fa5,-144(s0)
	lui	a5,%hi(.LC3)
	fld	fa5,%lo(.LC3)(a5)
	fsd	fa5,-120(s0)
	lui	a5,%hi(.LC4)
	fld	fa5,%lo(.LC4)(a5)
	fsd	fa5,-112(s0)
	lui	a5,%hi(.LC5)
	fld	fa5,%lo(.LC5)(a5)
	fsd	fa5,-96(s0)
	li	a5,0
	mv	a0,a5
	ld	ra,136(sp)
	ld	s0,128(sp)
	addi	sp,sp,144
	jr	ra
	.size	main, .-main
	.section	.rodata
	.align	2
.LC1:
	.word	1067869798
	.align	3
.LC2:
	.word	858993459
	.word	1072902963
	.align	3
.LC3:
	.word	-858993459
	.word	1073794252
	.align	3
.LC4:
	.word	1717986918
	.word	1074423398
	.align	3
.LC5:
	.word	-858993459
	.word	1074842828
	.ident	"GCC: (g2ee5e430018) 12.2.0"

	.file	"qsort.bc"
	.section	.text.startup,"ax",@progbits
	.align	16, 0x90
	.type	__cxx_global_var_init,@function
__cxx_global_var_init:                  # @__cxx_global_var_init
	.cfi_startproc
# BB#0:
	pushq	%rax
.Ltmp1:
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	callq	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	movl	$_ZStL8__ioinit, %esi
	movl	$__dso_handle, %edx
	callq	__cxa_atexit
	popq	%rax
	ret
.Ltmp2:
	.size	__cxx_global_var_init, .Ltmp2-__cxx_global_var_init
	.cfi_endproc

	.text
	.globl	_Z6qusortiiPi
	.align	16, 0x90
	.type	_Z6qusortiiPi,@function
_Z6qusortiiPi:                          # @_Z6qusortiiPi
	.cfi_startproc
# BB#0:
	subq	$56, %rsp
.Ltmp4:
	.cfi_def_cfa_offset 64
	movl	%edi, 52(%rsp)
	movl	%esi, 48(%rsp)
	movq	%rdx, 40(%rsp)
	movl	52(%rsp), %eax
	cmpl	48(%rsp), %eax
	jge	.LBB1_7
# BB#1:
	movl	52(%rsp), %eax
	movl	%eax, 36(%rsp)
	movl	48(%rsp), %eax
	movl	%eax, 32(%rsp)
	movslq	36(%rsp), %rax
	movq	40(%rsp), %rcx
	movl	(%rcx,%rax,4), %eax
	movl	%eax, 28(%rsp)
	movl	36(%rsp), %eax
	movl	%eax, 24(%rsp)
	movl	36(%rsp), %eax
	incl	%eax
	movl	%eax, 20(%rsp)
	jmp	.LBB1_2
	.align	16, 0x90
.LBB1_5:                                #   in Loop: Header=BB1_2 Depth=1
	incl	20(%rsp)
.LBB1_2:                                # =>This Inner Loop Header: Depth=1
	movl	20(%rsp), %eax
	cmpl	32(%rsp), %eax
	jg	.LBB1_6
# BB#3:                                 #   in Loop: Header=BB1_2 Depth=1
	movslq	20(%rsp), %rax
	movq	40(%rsp), %rcx
	movl	(%rcx,%rax,4), %eax
	cmpl	28(%rsp), %eax
	jge	.LBB1_5
# BB#4:                                 #   in Loop: Header=BB1_2 Depth=1
	incl	24(%rsp)
	movslq	20(%rsp), %rax
	movq	40(%rsp), %rcx
	movl	(%rcx,%rax,4), %eax
	movl	%eax, 16(%rsp)
	movslq	24(%rsp), %rcx
	movq	40(%rsp), %rax
	movl	(%rax,%rcx,4), %ecx
	movslq	20(%rsp), %rdx
	movl	%ecx, (%rax,%rdx,4)
	movq	40(%rsp), %rax
	movslq	24(%rsp), %rcx
	movl	16(%rsp), %edx
	movl	%edx, (%rax,%rcx,4)
	jmp	.LBB1_5
.LBB1_6:
	movslq	36(%rsp), %rax
	movq	40(%rsp), %rcx
	movl	(%rcx,%rax,4), %eax
	movl	%eax, 12(%rsp)
	movslq	24(%rsp), %rcx
	movq	40(%rsp), %rax
	movl	(%rax,%rcx,4), %ecx
	movslq	36(%rsp), %rdx
	movl	%ecx, (%rax,%rdx,4)
	movq	40(%rsp), %rax
	movslq	24(%rsp), %rcx
	movl	12(%rsp), %edx
	movl	%edx, (%rax,%rcx,4)
	movq	40(%rsp), %rdx
	movl	52(%rsp), %edi
	movl	24(%rsp), %esi
	decl	%esi
	callq	_Z6qusortiiPi
	movl	24(%rsp), %edi
	incl	%edi
	movq	40(%rsp), %rdx
	movl	48(%rsp), %esi
	callq	_Z6qusortiiPi
.LBB1_7:
	addq	$56, %rsp
	ret
.Ltmp5:
	.size	_Z6qusortiiPi, .Ltmp5-_Z6qusortiiPi
	.cfi_endproc

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	subq	$40, %rsp
.Ltmp7:
	.cfi_def_cfa_offset 48
	movl	$0, 36(%rsp)
	movl	.L_ZZ4mainE1a+16(%rip), %eax
	movl	%eax, 32(%rsp)
	vmovaps	.L_ZZ4mainE1a(%rip), %xmm0
	vmovaps	%xmm0, 16(%rsp)
	leaq	16(%rsp), %rdx
	xorl	%edi, %edi
	movl	$4, %esi
	callq	_Z6qusortiiPi
	movl	$0, 12(%rsp)
	jmp	.LBB2_1
	.align	16, 0x90
.LBB2_2:                                #   in Loop: Header=BB2_1 Depth=1
	movslq	12(%rsp), %rax
	movl	16(%rsp,%rax,4), %esi
	movl	$_ZSt4cout, %edi
	callq	_ZNSolsEi
	movq	%rax, %rdi
	movl	$.L.str, %esi
	callq	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	incl	12(%rsp)
.LBB2_1:                                # =>This Inner Loop Header: Depth=1
	cmpl	$4, 12(%rsp)
	jle	.LBB2_2
# BB#3:
	movl	36(%rsp), %eax
	addq	$40, %rsp
	ret
.Ltmp8:
	.size	main, .Ltmp8-main
	.cfi_endproc

	.section	.text.startup,"ax",@progbits
	.align	16, 0x90
	.type	_GLOBAL__I_a,@function
_GLOBAL__I_a:                           # @_GLOBAL__I_a
	.cfi_startproc
# BB#0:
	pushq	%rax
.Ltmp10:
	.cfi_def_cfa_offset 16
	callq	__cxx_global_var_init
	popq	%rax
	ret
.Ltmp11:
	.size	_GLOBAL__I_a, .Ltmp11-_GLOBAL__I_a
	.cfi_endproc

	.type	_ZStL8__ioinit,@object  # @_ZStL8__ioinit
	.lcomm	_ZStL8__ioinit,1
	.type	.L_ZZ4mainE1a,@object   # @_ZZ4mainE1a
	.section	.rodata,"a",@progbits
	.align	16
.L_ZZ4mainE1a:
	.long	14                      # 0xe
	.long	2                       # 0x2
	.long	56                      # 0x38
	.long	8                       # 0x8
	.long	6                       # 0x6
	.size	.L_ZZ4mainE1a, 20

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	 " "
	.size	.L.str, 2

	.section	.ctors,"aw",@progbits
	.align	8
	.quad	_GLOBAL__I_a

	.section	".note.GNU-stack","",@progbits

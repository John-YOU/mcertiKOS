/*
 * void cswitch(struct kctx *from, struct kctx *to);
 */
  .globl cswitch
cswitch:
  movl  4(%esp), %eax /* %eax <- from */   /*get the first param*/
  movl  8(%esp), %edx /* %edx <- to */     /*get the second param*/

  /* TODO: save the old kernel context */
  /*movl 0(%esp), %ecx
  movl %eax, %esp
  sub %eax, 0x18
  pushl %eax
  pushl %edi
  pushl %esi
  pushl %ebx
  pushl %ebp
  pushl %ecx
  */
  movl 0(%esp), %ecx
  /*add %eax, 0x18*/
  movl %eax, %esp
  pushl %ecx
  pushl %ebp
  pushl %ebx
  pushl %esi
  pushl %edi
  pushl %esp

  /* TODO: load the new kernel context */

  movl %edx, %esp
  popl (%esp)
  popl %edi
  popl %esi
  popl %ebx
  popl %ebp
  popl (%esp)

  xor %eax, %eax
  ret



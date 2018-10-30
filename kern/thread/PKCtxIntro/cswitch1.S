/*
 * void cswitch(struct kctx *from, struct kctx *to);
 */
  .globl cswitch
cswitch:
  movl  4(%esp), %eax /* %eax <- from */   /*get the first param*/
  movl  8(%esp), %edx /* %edx <- to */     /*get the second param*/

  /* TODO: save the old kernel context */
  movl %esp, 0(%eax)
  movl %edi, 4(%eax)
  movl %esi, 8(%eax)
  movl %ebx, 12(%eax)
  movl %ebp, 16(%eax)
  movl (%esp), %ecx;
  movl %ecx, 20(%eax) //eip

  movl (%edx), %esp
  movl 4(%edx), %edi
  movl 8(%edx), %esi
  movl 12(%edx), %ebx
  movl 16(%edx), %ebp
  movl 20(%edx), %ecx
  movl %ecx, (%esp)

  /*movl 0(%esp), %ecx
  movl %eax, %esp
  sub %eax, 0x18
  pushl %eax
  pushl %edi
  pushl %esi
  pushl %ebx
  pushl %ebp
  pushl %ecx
  
  movl 0(%esp), %ecx
  pushl %ecx
  pushl %ebp
  pushl %ebx
  pushl %esi
  pushl %edi
  pushl (%esp)*/

  /* TODO: load the new kernel context */

  /*
  movl %edx, %esp
  popl 0(%esp)
  popl %ebp
  popl %ebx
  popl %esi
  popl %edi
  popl (%esp)
  */
  

  xor %eax, %eax
  ret


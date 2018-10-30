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
  movl (%esp), %ecx
  movl %ecx, 20(%eax) //eip

  movl (%edx), %esp
  movl 20(%edx), %ecx
  movl %ecx, (%esp)  
  movl 16(%edx), %ebp
  movl 12(%edx), %ebx
  movl 8(%edx), %esi
  movl 4(%edx), %edi
  
  
  

  xor %eax, %eax
  ret


# -*-Makefile-*-

OBJDIRS += $(KERN_OBJDIR)/vmm/MPTFork

KERN_SRCFILES += $(KERN_DIR)/vmm/MPTFork/MPTFork.c


$(KERN_OBJDIR)/vmm/MPTFork/%.o: $(KERN_DIR)/vmm/MPTFork/%.c
	@echo + $(COMP_NAME)[KERN/vmm/MPTFork] $<
	@mkdir -p $(@D)
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<

$(KERN_OBJDIR)/vmm/MPTFork/%.o: $(KERN_DIR)/vmm/MPTFork/%.S
	@echo + as[KERN/vmm/MPTFork] $<
	@mkdir -p $(@D)
	$(V)$(CC) $(KERN_CFLAGS) -c -o $@ $<

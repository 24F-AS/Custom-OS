global idt_load
extern irq1_handler
extern irq0_handler

section .text

; Load the IDT pointer
idt_load:
    mov eax, [esp + 4]
    lidt [eax]
    ret

; IRQ0 - Timer (Scheduler)
global irq0
extern schedule
irq0:
    pusha
    cld
    
    push esp          ; Pass current ESP as argument to schedule(uint32_t current_esp)
    call schedule
    add esp, 4        ; Clean up argument
    
    mov esp, eax      ; eax contains the new ESP returned by schedule
    
    popa
    iret

; IRQ1 - Keyboard
global irq1
irq1:
    pusha
    cld
    call irq1_handler
    popa
    iret

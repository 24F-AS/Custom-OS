global idt_load
extern irq1_handler
extern irq0_handler

section .text

; Load the IDT pointer
idt_load:
    mov eax, [esp + 4]
    lidt [eax]
    ret

; IRQ0 - Timer
global irq0
irq0:
    pusha
    cld
    call irq0_handler
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

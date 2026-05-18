#include "interrupt.h"

extern void EPIC_trap_handler(void);

void Interrupt_Init(void)
{
    // 1. Включаем тактирование EPIC
    PM->CLK_APB_M_SET |= PM_CLOCK_APB_M_EPIC_M;
    // 2. Разрешаем прерывание от TIMER32_2 в EPIC
    EPIC->MASK_LEVEL_SET = 1 << EPIC_LINE_TIMER32_2_S;
    // 3. Устанавливаем обработчик прерываний
    riscv_irq_set_handler(RISCV_IRQ_MEI, EPIC_trap_handler);
    // 4. Включаем внешние прерывания
    riscv_irq_enable(RISCV_IRQ_MEI);
    // 5. Включаем глобальные прерывания
    riscv_irq_global_enable();
}
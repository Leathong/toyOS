#include "trap.h"

#include "../lib.h"
#include "../printk.h"
#include "gate.h"

extern "C" void handle_divide_error(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_divide_error(0),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp, *p);
  while (1) {};
}

extern "C" void handle_debug(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(RED, BLACK, "handle_debug(1),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp, *p);
  while (1) {};
}

extern "C" void handle_nmi(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(RED, BLACK, "handle_nmi(2),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp, *p);
  while (1) {};
}

extern "C" void handle_int3(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(RED, BLACK, "handle_int3(3),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp, *p);
  while (1) {};
}

extern "C" void handle_overflow(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_overflow(4),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp, *p);
  while (1) {};
}

extern "C" void handle_bounds(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_bounds(5),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp, *p);
  while (1) {};
}

extern "C" void handle_undefined_opcode(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_undefined_opcode(6),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp, *p);
  while (1) {};
}

extern "C" void handle_dev_not_available(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_dev_not_available(7),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp,
    *p);
  while (1) {};
}

extern "C" void handle_double_fault(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_double_fault(8),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp, *p);
  while (1) {};
}

extern "C" void handle_coprocessor_segment_overrun(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_coprocessor_segment_overrun(9),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n",
    error_code, rsp, *p);
  while (1) {};
}

extern "C" void handle_invalid_TSS(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_invalid_TSS(10),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp, *p);

  if (error_code & 0x01) {
    // color_printfk(RED,BLACK,"The exception occurred during delivery of an event external to the
    // program,such as an interrupt or an earlier exception.\n");
    color_printfk(RED, BLACK, __FUNCTION__);
  }
  if (error_code & 0x02) {
    color_printfk(RED, BLACK, "Refers to a gate descriptor in the IDT;\n");
  } else {
    color_printfk(RED, BLACK, "Refers to a descriptor in the GDT or the current LDT;\n");
  }
  if ((error_code & 0x02) == 0) {
    if (error_code & 0x04) {
      color_printfk(RED, BLACK, "Refers to a segment or gate descriptor in the LDT;\n");
    } else {
      color_printfk(RED, BLACK, "Refers to a descriptor in the current GDT;\n");
    }
  }

  color_printfk(RED, BLACK, "Segment Selector Index:%#010x\n", error_code & 0xfff8);

  while (1) {};
}

extern "C" void handle_segment_not_present(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_segment_not_present(11),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code,
    rsp, *p);

  if (error_code & 0x01) {
    // color_printfk(RED,BLACK,"The exception occurred during delivery of an event external to the
    // program,such as an interrupt or an earlier exception.\n");
    color_printfk(RED, BLACK, __FUNCTION__);
  }
  if (error_code & 0x02) {
    color_printfk(RED, BLACK, "Refers to a gate descriptor in the IDT;\n");
  } else {
    color_printfk(RED, BLACK, "Refers to a descriptor in the GDT or the current LDT;\n");
  }
  if ((error_code & 0x02) == 0) {
    if (error_code & 0x04) {
      color_printfk(RED, BLACK, "Refers to a segment or gate descriptor in the LDT;\n");
    } else {
      color_printfk(RED, BLACK, "Refers to a descriptor in the current GDT;\n");
    }
  }
  color_printfk(RED, BLACK, "Segment Selector Index:%#010x\n", error_code & 0xfff8);

  while (1) {};
}

extern "C" void handle_stack_segment_fault(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_stack_segment_fault(12),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code,
    rsp, *p);

  if (error_code & 0x01) {
    // color_printfk(RED,BLACK,"The exception occurred during delivery of an event external to the
    // program,such as an interrupt or an earlier exception.\n");
    color_printfk(RED, BLACK, __FUNCTION__);
  }

  if (error_code & 0x02) {
    color_printfk(RED, BLACK, "Refers to a gate descriptor in the IDT;\n");
  } else {
    color_printfk(RED, BLACK, "Refers to a descriptor in the GDT or the current LDT;\n");
  }
  if ((error_code & 0x02) == 0) {
    if (error_code & 0x04) {
      color_printfk(RED, BLACK, "Refers to a segment or gate descriptor in the LDT;\n");
    } else {
      color_printfk(RED, BLACK, "Refers to a descriptor in the current GDT;\n");
    }
  }
  color_printfk(RED, BLACK, "Segment Selector Index:%#010x\n", error_code & 0xfff8);

  while (1) {};
}

extern "C" void handle_general_protection(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_general_protection(13),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp,
    *p);

  if (error_code & 0x01) {
    // color_printfk(RED,BLACK,"The exception occurred during delivery of an event external to the
    // program,such as an interrupt or an earlier exception.\n");
    color_printfk(RED, BLACK, __FUNCTION__);
  }
  if (error_code & 0x02) {
    color_printfk(RED, BLACK, "Refers to a gate descriptor in the IDT;\n");
  } else {
    color_printfk(RED, BLACK, "Refers to a descriptor in the GDT or the current LDT;\n");
  }

  if ((error_code & 0x02) == 0) {
    if (error_code & 0x04) {
      color_printfk(RED, BLACK, "Refers to a segment or gate descriptor in the LDT;\n");
    } else {
      color_printfk(RED, BLACK, "Refers to a descriptor in the current GDT;\n");
    }
  }

  color_printfk(RED, BLACK, "Segment Selector Index:%#010x\n", error_code & 0xfff8);

  while (1) {};
}

extern "C" void handle_page_fault(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  unsigned long cr2 = 0;

  __asm__ __volatile__("movq	%%cr2,	%0" : "=r"(cr2)::"memory");

  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_page_fault(14),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp, *p);

  if (!(error_code & 0x01)) {
    color_printfk(RED, BLACK, "Page Not-Present,\t");
  }
  if (error_code & 0x02) {
    color_printfk(RED, BLACK, "Write Cause Fault,\t");
  } else {
    color_printfk(RED, BLACK, "Read Cause Fault,\t");
  }
  if (error_code & 0x04) {
    color_printfk(RED, BLACK, "Fault in user(3)\t");
  } else {
    color_printfk(RED, BLACK, "Fault in supervisor(0,1,2)\t");
  }
  if (error_code & 0x08) {
    color_printfk(RED, BLACK, ",Reserved Bit Cause Fault\t");
  }
  if (error_code & 0x10) {
    color_printfk(RED, BLACK, ",Instruction fetch Cause Fault");
  }
  color_printfk(RED, BLACK, "\n");

  color_printfk(RED, BLACK, "CR2:%#018lx\n", cr2);

  while (1) {};
}

extern "C" void handle_x87_FPU_error(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_x87_FPU_error(16),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp, *p);
  while (1) {};
}

extern "C" void handle_alignment_check(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_alignment_check(17),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp, *p);
  while (1) {};
}

extern "C" void handle_machine_check(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_machine_check(18),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp, *p);
  while (1) {};
}

extern "C" void handle_SIMD_exception(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_SIMD_exception(19),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n", error_code, rsp, *p);
  while (1) {};
}

extern "C" void handle_virtualization_exception(unsigned long rsp, unsigned long error_code) {
  unsigned long* p = NULL;
  p = (unsigned long*)(rsp + 0x98);
  color_printfk(
    RED, BLACK, "handle_virtualization_exception(20),ERROR_CODE:%#018lx,RSP:%#018lx,RIP:%#018lx\n",
    error_code, rsp, *p);
  while (1) {};
}

extern "C" void sys_vector_init(void) {
#define IST 1

  set_trap_gate(0, IST, divide_error);
  set_trap_gate(1, IST, debug);
  set_intr_gate(2, IST, nmi);
  set_system_gate(3, IST, int3);
  set_system_gate(4, IST, overflow);
  set_system_gate(5, IST, bounds);
  set_trap_gate(6, IST, undefined_opcode);
  set_trap_gate(7, IST, dev_not_available);
  set_trap_gate(8, IST, double_fault);
  set_trap_gate(9, IST, coprocessor_segment_overrun);
  set_trap_gate(10, IST, invalid_TSS);
  set_trap_gate(11, IST, segment_not_present);
  set_trap_gate(12, IST, stack_segment_fault);
  set_trap_gate(13, IST, general_protection);
  set_trap_gate(14, IST, page_fault);
  // 15 Intel reserved. Do not use.
  set_trap_gate(16, IST, x87_FPU_error);
  set_trap_gate(17, IST, alignment_check);
  set_trap_gate(18, IST, machine_check);
  set_trap_gate(19, IST, SIMD_exception);
  set_trap_gate(20, IST, virtualization_exception);

#undef IST

  // set_system_gate(SYSTEM_CALL_VECTOR,7,system_call);
}

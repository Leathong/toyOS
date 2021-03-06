#ifndef __MEMORY_H__
#define __MEMORY_H__

static unsigned long* Global_CR3 = nullptr;

constexpr int MAX_E820S = 32;

struct E820 {
  unsigned long address;
  unsigned long length;
  unsigned int type;
} __attribute__((packed));

////struct page attribute (alloc_pages flags)
constexpr unsigned long PG_PTable_Maped = (1UL << 0);
constexpr unsigned long PG_Kernel_Init = (1UL << 1);
constexpr unsigned long PG_Referenced = (1UL << 2);
constexpr unsigned long PG_Dirty = (1UL << 3);
constexpr unsigned long PG_Active = (1UL << 4);
constexpr unsigned long PG_Up_To_Date = (1UL << 5);
constexpr unsigned long PG_Device = (1UL << 6);
constexpr unsigned long PG_Kernel = (1UL << 7);
constexpr unsigned long PG_K_Share_To_U = (1UL << 8);
constexpr unsigned long PG_Slab = (1UL << 9);

struct Page {
  struct Zone* zone_struct;
  unsigned long PHY_address;
  unsigned long attribute;

  unsigned long reference_count;

  unsigned long age;
};

struct Zone {
  struct Page* pages_group;
  unsigned long pages_count;

  unsigned long zone_start_address;
  unsigned long zone_end_address;
  unsigned long zone_length;
  unsigned long attribute;

  struct Global_Memory_Descriptor* GMD_struct;

  unsigned long page_using_count;
  unsigned long page_free_count;

  unsigned long total_pages_link;
};

typedef struct Global_Memory_Descriptor {
  struct E820 e820[MAX_E820S];
  unsigned long e820_count;

  unsigned long* bits_map;
  unsigned long bits_count;
  unsigned long bits_length;

  struct Page* pages_struct;
  unsigned long pages_count;
  unsigned long pages_length;

  struct Zone* zones_struct;
  unsigned long zones_count;
  unsigned long zones_length;

  unsigned long start_code, end_code, end_data, end_brk;

  unsigned long end_of_struct;
} Global_Memory_Descriptor;

static Global_Memory_Descriptor memory_management_struct;

constexpr unsigned long PAGE_OFFSET = 0xffff'8000'0000'0000;

constexpr unsigned long PAGE_GDT_SHIFT = 39;
constexpr unsigned long PAGE_1G_SHIFT = 30;
constexpr unsigned long PAGE_2M_SHIFT = 21;
constexpr unsigned long PAGE_4K_SHIFT = 12;

constexpr unsigned long PAGE_2M_SIZE = (1UL << PAGE_2M_SHIFT);
constexpr unsigned long PAGE_4K_SIZE = (1UL << PAGE_4K_SHIFT);

constexpr unsigned long PAGE_2M_MASK(unsigned long addr) {
  return addr & (~(PAGE_2M_SIZE - 1));
}

constexpr unsigned long PAGE_4K_MASK(unsigned long addr) {
  return addr & (~(PAGE_4K_SIZE - 1));
}

constexpr unsigned long PAGE_2M_ALIGN(unsigned long addr) {
  return (addr + PAGE_2M_SIZE - 1) & (~(PAGE_2M_SIZE - 1));
}
constexpr unsigned long PAGE_4K_ALIGN(unsigned long addr) {
  return (addr + PAGE_4K_SIZE - 1) & (~(PAGE_4K_SIZE - 1));
}

constexpr unsigned long Virt_To_Phy(unsigned long addr) {
  return addr - PAGE_OFFSET;
}
constexpr unsigned long Phy_To_Virt(unsigned long addr) {
  return addr + PAGE_OFFSET;
}

// constexpr unsigned long Virt_To_2M_Page(unsigned long addr)	{
//  return memory_management_struct.pages_struct + (addr - PAGE_OFFSET >> PAGE_2M_SHIFT);
//}
// constexpr unsigned long Phy_to_2M_Page(unsigned long addr)	{
//  return memory_management_struct.pages_struct + (addr >> PAGE_2M_SHIFT)
//}

////page table attribute

//	bit 63	execution disable:
constexpr unsigned long PAGE_XD = 0x1000000000000000;

//	bit 12	page attribute table
constexpr unsigned long PAGE_PAT = 0x1000;

//	bit 8	global page:1,global;0,part
constexpr unsigned long PAGE_GLOBAL = 0x0100;

//	bit 7	page size:1,big page;0,small page;
constexpr unsigned long PAGE_PS = 0x0080;

//	bit 6	dirty:1,dirty;0,clean;
constexpr unsigned long PAGE_DIRTY = 0x0040;

//	bit 5	accessed:1,visited;0,unvisited;
constexpr unsigned long PAGE_ACCESSED = 0x0020;

//	bit 4	page level cache disable
constexpr unsigned long PAGE_PCD = 0x0010;

//	bit 3	page level write through
constexpr unsigned long PAGE_PWT = 0x0008;

//	bit 2	user supervisor:1,user and supervisor;0,supervisor;
constexpr unsigned long PAGE_U_S = 0x0004;

//	bit 1	read write:1,read and write;0,read;
constexpr unsigned long PAGE_R_W = 0x0002;

//	bit 0	present:1,present;0,no present;
constexpr unsigned long PAGE_PRESENT = 0x0001;

constexpr unsigned long PAGE_KERNEL_GDT = (PAGE_R_W | PAGE_PRESENT);
constexpr unsigned long PAGE_KERNEL_DIR = (PAGE_R_W | PAGE_PRESENT);
constexpr unsigned long PAGE_KERNEL_PAGE = (PAGE_PS | PAGE_R_W | PAGE_PRESENT);
constexpr unsigned long PAGE_USER_DIR = (PAGE_U_S | PAGE_R_W | PAGE_PRESENT);
constexpr unsigned long PAGE_USER_PAGE = (PAGE_PS | PAGE_U_S | PAGE_R_W | PAGE_PRESENT);

/*

*/

typedef struct {
  unsigned long pml4t;
} pml4t_t;
constexpr unsigned long mk_pml4t(unsigned long addr, unsigned long attr) {
  return addr | attr;
}
static inline void set_pml4t(pml4t_t* pml4tptr, const pml4t_t& pml4tval) {
  *(pml4tptr) = (pml4tval);
}

typedef struct {
  unsigned long pdpt;
} pdpt_t;
constexpr unsigned long mk_pdpt(unsigned long addr, unsigned long attr) {
  return addr | attr;
}
static inline void set_pdpt(pdpt_t* pdptptr, const pdpt_t& pdptval) {
  *(pdptptr) = (pdptval);
}

typedef struct {
  unsigned long pdt;
} pdt_t;
constexpr unsigned long mk_pdt(unsigned long addr, unsigned long attr) {
  return addr | attr;
}
static inline void set_pdt(pdt_t* pdtptr, const pdt_t& pdtval) {
  *(pdtptr) = (pdtval);
}

typedef struct {
  unsigned long pt;
} pt_t;
constexpr unsigned long mk_pt(unsigned long addr, unsigned long attr) {
  return addr | attr;
}
static inline void set_pt(pt_t* ptptr, const pt_t& ptval) {
  *(ptptr) = (ptval);
}

extern "C" void init_memory(void);

static inline void flush_tlb(unsigned long addr) {
  __asm__ __volatile__("invlpg  (%0)  \n\t" ::"r"(addr) : "memory");
}

static inline void flush_tlb_all() {
  unsigned long tmpreg;
  __asm__ __volatile__(
    "movq  %%cr3,  %0  \n\t"
    "movq  %0,  %%cr3  \n\t"
    : "=r"(tmpreg)
    :
    : "memory");
}

static inline unsigned long* Get_pgd() {
  unsigned long* tmp;
  __asm__ __volatile__("movq  %%cr3,  %0  \n\t" : "=r"(tmp) : : "memory");
  return tmp;
}

#endif

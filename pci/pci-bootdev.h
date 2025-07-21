

#ifndef __PCI_BOOTDEV_H__
#define __PCI_BOOTDEV_H__

#include <bootdev.h>
#include <bootflow.h>
#include <log.h>
#include <bootmeth.h>
#include <asm/io.h>
#include <linux/bitops.h>



#define CMD_INIT 0x01

#define VALID_CMD_MASK (1 << 8) 
#define RETRIEVE_CMD_MASK GENMASK(7, 0)

#define CMD_RETRIEVE_OFF 0x8

#define DATA_ADDR_RANGE_START 0x800000000
#define DATA_CMD_RANGE_START 0x90000000

struct pci_mc_bootdev{
    ulong pci_cmd_register;
    ulong pci_memory_space;
}; 

static inline u16 read_cmd(struct pci_mc_bootdev* pmd){
   return readw(pmd->pci_cmd_register + CMD_RETRIEVE_OFF);
}

static inline u16 check_cmd_valid(u16 cmd){
    return cmd & VALID_CMD_MASK;
}

static inline u16 get_cmd(u16 cmd){
    return cmd & RETRIEVE_CMD_MASK;
}
#endif

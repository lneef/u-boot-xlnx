

#ifndef __PCI_BOOT_H__
#define __PCI_BOOT_H__

#include "linux/types.h"
#include <bootflow.h>
#include <asm/io.h>
#include <linux/bitops.h>

struct pci_boot_data{
    ulong data_addr, cmd_addr;
    ulong data_range_size;
};

#define CMD_INIT 0x01

#define VALID_CMD_MASK (1 << 8) 
#define RETRIEVE_CMD_MASK GENMASK(7, 0)

#define CMD_RETRIEVE_OFF 0x8

static inline u16 read_cmd(struct pci_boot_data* pbd){
   return readw(pbd->cmd_addr + CMD_RETRIEVE_OFF);
}

static inline u16 check_cmd_valid(u16 cmd){
    return cmd & VALID_CMD_MASK;
}

static inline u16 get_cmd(u16 cmd){
    return cmd & RETRIEVE_CMD_MASK;
}

int load_image(struct udevice* dev);

#endif

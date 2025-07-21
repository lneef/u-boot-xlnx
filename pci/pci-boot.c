
#include "cpu_func.h"
#include "linux/errno.h"
#include "pci-bootdev.h"
#include <pci-boot.h>

int wait_for_image(struct bootflow* bflow){
    u16 cmd;
    struct pci_mc_bootdev* pmd = (struct pci_mc_bootdev*)bflow->bootmeth_priv;
    if(!pmd)
        return -ENODEV;
    cmd = read_cmd(pmd);
    while (!check_cmd_valid(cmd)) {
        cmd = read_cmd(pmd);
    }

    if(get_cmd(cmd) != CMD_INIT)
        return -ENODEV;
    invalidate_dcache_range(DATA_ADDR_RANGE_START, DATA_ADDR_RANGE_START + 0x2000000);
    return 0; 
}

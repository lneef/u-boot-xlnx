#include "cpu_func.h"
#include "dm/device.h"
#include "linux/errno.h"
#include <pci-boot.h>
int load_image(struct udevice* dev){
    u16 cmd;
    struct pci_boot_data* pbd = dev_get_priv(dev);
    if(!pbd)
        return -ENODEV;
    cmd = read_cmd(pbd);
    while (!check_cmd_valid(cmd)) {
        cmd = read_cmd(pbd);
    }

    if(get_cmd(cmd) != CMD_INIT)
        return -ENODEV;
    invalidate_dcache_range(pbd->data_addr, pbd->data_addr + 0x2000000);
    return 0; 
}





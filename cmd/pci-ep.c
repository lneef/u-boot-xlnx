#include "command.h"
#include "console.h"
#include "cpu_func.h"
#include "dm/device.h"
#include "dm/uclass-id.h"
#include "dm/uclass.h"
#include "pci_ep.h"
#include <cli.h>

static int load_image(struct udevice* dev){
    int ret;
    do{
        ret = pci_ep_load_from_host(dev);
    }while(!ctrlc() && ret == -EAGAIN);
    flush_dcache_all();
    return ret; 
}

int do_pci_ep(struct cmd_tbl *cmds, int flag, int argc, char *const argv[]) {
  struct udevice *dev;
  if (uclass_get_device(UCLASS_PCI_EP, 0, &dev))
    return CMD_RET_FAILURE;
  if(load_image(dev))
      return CMD_RET_FAILURE;
  return CMD_RET_SUCCESS;
}

U_BOOT_CMD(pcieimageload, 1, 1, do_pci_ep, "Load image from RC", "");

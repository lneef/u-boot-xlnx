#include "command.h"
#include "dm/device.h"
#include "dm/uclass-id.h"
#include "dm/uclass.h"
#include "pci-boot.h"
#include <cli.h>

static int load_boot_image(struct udevice *dev) { return load_image(dev); }

int do_pci_ep(struct cmd_tbl *cmds, int flag, int argc, char *const argv[]) {
  struct udevice *dev;
  if (uclass_get_device(UCLASS_PCI_EP, 0, &dev))
    return CMD_RET_FAILURE;
  load_boot_image(dev);
  return CMD_RET_SUCCESS;
}

U_BOOT_CMD(pciepload, 1, 1, do_pci_ep, "Load image from RC", "");

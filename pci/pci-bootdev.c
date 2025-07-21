#include "asm/global_data.h"
#include <bootdev.h>
#include <bootflow.h>
#include <dm.h>
#include <log.h>
#include <bootmeth.h>
#include "pci-bootdev.h"
#include <stdlib.h>

DECLARE_GLOBAL_DATA_PTR;


static int pci_get_booflow(struct udevice* dev, struct bootflow_iter* iter, struct bootflow* bflow){
    // write reserved pci mc memory region to priv bootmeth memory
    int ret;

    ret = bootmeth_check(bflow->method, iter);
    if(ret)
        return log_msg_ret("check", ret);
    bflow->name = strdup("pci-mc");
    bflow->bootmeth_priv = malloc(sizeof(struct pci_mc_bootdev));
    struct pci_mc_bootdev* pmd = (struct pci_mc_bootdev*) bflow->bootmeth_priv;
    pmd->pci_memory_space = DATA_ADDR_RANGE_START;
    pmd->pci_cmd_register = DATA_CMD_RANGE_START;
    ret = bootmeth_read_bootflow(bflow->method, bflow);
    if(ret)
        return log_msg_ret("read", ret);
    return 0;
};

static int pci_bootdev_bind(struct udevice *dev)
{
	struct bootdev_uc_plat *ucp = dev_get_uclass_plat(dev);

  ucp->prio = BOOTDEVP_4_SCAN_FAST;

	return 0;
}

static const struct udevice_id pci_bootdev_ids[] = {
	{ .compatible = "u-boot,bootdev-pci" },
	{ }
};

struct bootdev_ops pci_bootdev_ops = {
    .get_bootflow = pci_get_booflow
};


U_BOOT_DRIVER(pci_bootdev) = {
	.name		= "pci_bootdev",
	.id		= UCLASS_BOOTDEV,
	.ops		= &pci_bootdev_ops,
	.bind		= pci_bootdev_bind,
	.of_match	= pci_bootdev_ids,
};

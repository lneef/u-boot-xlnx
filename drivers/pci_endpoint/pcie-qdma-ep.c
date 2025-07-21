#include "dm/device.h"
#include "dm/uclass-id.h"
#include <pci_ep.h>
#include <pci-boot.h>

#define DATA_ADDR_RANGE_START 0x800000000
#define DATA_CMD_RANGE_START 0x90000000
#define DATA_RANGE_SIZE 0x1000000

static struct pci_ep_ops pq_ops = {};

static int qdma_pci_ep_probe(struct udevice *dev)
{
  struct pci_boot_data* pbd = (struct pci_boot_data*)dev_get_priv(dev);
  pbd->data_addr = DATA_ADDR_RANGE_START;
  pbd->cmd_addr = DATA_CMD_RANGE_START;
  pbd->data_range_size = DATA_RANGE_SIZE;
	return 0;
}

static int qdma_pci_ep_remove(struct udevice *dev)
{
	return 0;
}

const struct udevice_id qdma_pci_ep_of_match[] = {
	{ .compatible = "xlnx,qdma" },
	{ }
};

U_BOOT_DRIVER(pcie_qdma_ep) = {
    .name = "xlnx-qdma-ep",
    .id = UCLASS_PCI_EP,
    .of_match = qdma_pci_ep_of_match,
    .probe = qdma_pci_ep_probe,
    .remove = qdma_pci_ep_remove,
    .ops = &pq_ops,
    .priv_auto = sizeof(struct pci_boot_data)
};

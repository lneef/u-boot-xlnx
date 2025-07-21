#include "dm/device.h"
#include "dm/uclass-id.h"
#include <pci_ep.h>

static struct pci_ep_ops pq_ops = {};

static int qdma_pci_ep_probe(struct udevice *dev)
{
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
};

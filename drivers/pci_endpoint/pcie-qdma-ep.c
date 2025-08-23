#include "asm/io.h"
#include "dm/device.h"
#include "dm/devres.h"
#include "dm/read.h"
#include "dm/uclass-id.h"
#include "fdtdec.h"
#include <linux/bitops.h>
#include <linux/io.h>
#include <pci_ep.h>

#define PCI_EP_CTRL_LINK_UP 0x8

struct pci_ep_ctrl_data {
  void __iomem *cmd_addr;
};

static inline int check_link_up(struct pci_ep_ctrl_data *pbd) {
  u8 val = readb(pbd->cmd_addr + PCI_EP_CTRL_LINK_UP);
  if (val & 1)
    return 0;
  return -ENODEV;
}

static int qdma_pci_ep_probe(struct udevice *dev) {
  fdt_addr_t addr;
  fdt_size_t size;
  struct pci_ep_ctrl_data *pbd = (struct pci_ep_ctrl_data *)dev_get_priv(dev);
  addr = dev_read_addr_size(dev, &size);
  if (addr == FDT_ADDR_T_NONE)
    return -EINVAL;
  pbd->cmd_addr = devm_ioremap(dev, addr, size);
  if (!pbd->cmd_addr)
    return log_msg_ret("ioremap", -ENOMEM);
  return 0;
}

static int qdma_pci_ep_remove(struct udevice *dev) {
  struct pci_ep_ctrl_data *pbd = (struct pci_ep_ctrl_data *)dev_get_priv(dev);
  if (pbd->cmd_addr)
    iounmap(pbd->cmd_addr);
  return 0;
}

static int qdma_pci_ep_load_from_host(struct udevice *dev) {
  struct pci_ep_ctrl_data *pbd = (struct pci_ep_ctrl_data *)dev_get_priv(dev);
  u32 irq_val = readl(pbd->cmd_addr);
  if (irq_val == 0)
    return -EAGAIN;
  if (irq_val == -1)
    return -ENOENT;
  writel(0ul, pbd->cmd_addr);
  return 0;
}

const struct udevice_id qdma_pci_ep_of_match[] = {
    {.compatible = "xlnx,qdma"},
    {}
};

static struct pci_ep_ops pq_ops = {
    .load_from_host = qdma_pci_ep_load_from_host,
};

U_BOOT_DRIVER(pcie_qdma_ep) = {
    .name = "xlnx-qdma-ep",
    .id = UCLASS_PCI_EP,
    .of_match = qdma_pci_ep_of_match,
    .probe = qdma_pci_ep_probe,
    .remove = qdma_pci_ep_remove,
    .ops = &pq_ops,
    .priv_auto = sizeof(struct pci_ep_ctrl_data),
};

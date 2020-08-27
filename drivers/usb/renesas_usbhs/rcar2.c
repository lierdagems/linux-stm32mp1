// SPDX-License-Identifier: GPL-1.0+
/*
 * Renesas USB driver R-Car Gen. 2 initialization and power control
 *
 * Copyright (C) 2014 Ulrich Hecht
 */

#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/phy/phy.h>
#include "common.h"
#include "rcar2.h"

static int usbhs_rcar2_hardware_init(struct platform_device *pdev)
{
	struct usbhs_priv *priv = usbhs_pdev_to_priv(pdev);

	if (IS_ENABLED(CONFIG_GENERIC_PHY)) {
		struct phy *phy = phy_get(&pdev->dev, "usb");

		if (IS_ERR(phy))
			return PTR_ERR(phy);

		priv->phy = phy;
		return 0;
	}

	return -ENXIO;
}

static int usbhs_rcar2_hardware_exit(struct platform_device *pdev)
{
	struct usbhs_priv *priv = usbhs_pdev_to_priv(pdev);

	if (priv->phy) {
		phy_put(&pdev->dev, priv->phy);
		priv->phy = NULL;
	}

	return 0;
}

static int usbhs_rcar2_power_ctrl(struct platform_device *pdev,
				void __iomem *base, int enable)
{
	struct usbhs_priv *priv = usbhs_pdev_to_priv(pdev);
	int retval = -ENODEV;

	if (priv->phy) {
		if (enable) {
			retval = phy_init(priv->phy);

			if (!retval)
				retval = phy_power_on(priv->phy);
		} else {
			phy_power_off(priv->phy);
			phy_exit(priv->phy);
			retval = 0;
		}
	}

	return retval;
}

static int usbhs_rcar2_get_id(struct platform_device *pdev)
{
	return USBHS_GADGET;
}

const struct renesas_usbhs_platform_callback usbhs_rcar2_ops = {
	.hardware_init = usbhs_rcar2_hardware_init,
	.hardware_exit = usbhs_rcar2_hardware_exit,
	.power_ctrl = usbhs_rcar2_power_ctrl,
	.get_id = usbhs_rcar2_get_id,
};

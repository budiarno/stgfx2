#include <linux/platform_device.h>
#include <linux/stm/platform.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/stm/bdisp2_shared.h>
#include "bdisp2/bdisp2_os.h"
#include "blit_debug.h"

#ifdef UNIFIED_DRIVER
#undef __exit
#define __exit
#endif


static void release(struct device *dev) { }

static struct stm_plat_blit_data plat_blit_7111 = {
	.device_type = STM_BLITTER_VERSION_7200c2_7111_7141_7105,
	.nb_aq = 4,
	.nb_cq = 2,
	.line_buffer_length = 128,
	.mb_buffer_length = 128,
	.rotate_buffer_length = 16,
	.device_name = "stm-bdispII",
};

static struct platform_device bdisp_7111 = {
	.name = "stm-bdispII",
	.id = -1,
	.num_resources = 7,
	.resource = (struct resource[]) {
		STM_PLAT_RESOURCE_MEM_NAMED("bdisp-io", 0xfe20b000, 0x1000),
		STM_PLAT_RESOURCE_IRQ_NAMED("bdisp-aq1", evt2irq(0x1580), -1),
		STM_PLAT_RESOURCE_IRQ_NAMED("bdisp-aq2", evt2irq(0x1580), -1),
		STM_PLAT_RESOURCE_IRQ_NAMED("bdisp-aq3", evt2irq(0x1580), -1),
		STM_PLAT_RESOURCE_IRQ_NAMED("bdisp-aq4", evt2irq(0x1580), -1),
		STM_PLAT_RESOURCE_IRQ_NAMED("bdisp-cq1", evt2irq(0x1760), -1),
		STM_PLAT_RESOURCE_IRQ_NAMED("bdisp-cq2", evt2irq(0x1760), -1),
	},

	.dev.platform_data = ((void *) (uintptr_t)
			      &plat_blit_7111),
	.dev.release = release,
};


static int __init stm_blit_stx7111_init(void)
{
	stm_blit_printd(0, "%s\n", __func__);

	return platform_device_register(&bdisp_7111);
}

static void __exit stm_blit_stx7111_exit(void)
{
	stm_blit_printd(0, "%s\n", __func__);

	platform_device_unregister(&bdisp_7111);
}

#ifdef UNIFIED_DRIVER

int __init stm_blit_glue_init(void)
{
	return stm_blit_stx7111_init();
}

void __exit stm_blit_glue_exit(void)
{
	stm_blit_stx7111_exit();
}

#else /* UNIFIED_DRIVER */

MODULE_AUTHOR("André Draszik <andre.draszik@st.com");
MODULE_DESCRIPTION("STMicroelectronics STx7111 BDispII driver glue");
MODULE_LICENSE("GPL");

module_init(stm_blit_stx7111_init);
module_exit(stm_blit_stx7111_exit);

#endif /* UNIFIED_DRIVER */

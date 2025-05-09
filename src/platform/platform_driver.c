#include <uapi/systypes.h>
#include <merlin/platform/driver.h>
#include <dts.h>

static struct platform_device_driver *merlin_platform_get_from_handle(devh_t handle)
{
    /* define a merlin-level platform drivers listing context to search in */
    return NULL;
}

/* Map given device handle into the task memory */
int merlin_platform_driver_map(devh_t handle)
{
    sys_dev_map(handle);
}

/* Unmap given device handle from the task memory */
int merlin_platform_driver_unmap(devh_t handle)
{
    sys_dev_unmap(handle);
}

/* resolve driver context in the registered driver(s) for given IRQn using DTS backend,
 * and call the fops->isr routine for it.
 * Minimalist model, to auto-dispatch IRQ events received from sys_get_event()
 */
int merlin_platform_driver_irq_displatch(IRQn)
{
    devh_t handle = platform_dts_get_handle(IRQn);
    struct platform_device_driver *self = platform_get_from_handle(handle);
    return self->platform_fops.isr(self, IRQn);
}

void merlin_platform_driver_map(struct platform_device_driver *self)
{
    merlin_platform_dts_map(self->devh);
}

void merlin_platform_driver_unmap(struct platform_device_driver *self)
{
    merlin_platform_dts_unmap(self->devh);
}

size_t merlin_platform_get_baseaddr(struct platform_device_driver *self)
{
    return merlin_platform_dts_get_baseaddr(self)
}

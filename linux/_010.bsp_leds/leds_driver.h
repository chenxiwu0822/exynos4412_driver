#ifndef __LED_DRIVER_H
#define __LED_DRIVER_H

#define LED_MAGIC  'L'

#define LED_ON     _IO(LED_MAGIC, 0)
#define LED_OFF    _IO(LED_MAGIC, 1)

#define LED_MAX    2

#endif /* __LED_DRIVER_H */
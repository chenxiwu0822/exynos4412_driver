#ifndef __BEEP_DRIVER_H
#define __BEEP_DRIVER_H

#define BEEP_MAGIC  'B'

#define BEEP_ON     _IO(BEEP_MAGIC, 0)
#define BEEP_OFF    _IO(BEEP_MAGIC, 1)

#define BEEP_MAX    2

#endif /* __BEEP_DRIVER_H */
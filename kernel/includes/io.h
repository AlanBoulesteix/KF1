#pragma once

inline void outb(uint16_t port, uint8_t val);
inline uint8_t inb(uint16_t port);
inline void io_wait(void);

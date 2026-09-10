#include "memory/bus.hpp"

namespace gbcemu
{

// TODO: Worth considering a small struct { uint16_t start, end; } 
// per-region table or a switch on the high nibble of the address
std::uint8_t Bus::read(std::uint16_t address) const
{
    if (address <= 0x3FFF)
    {
        return bank0_[address];
    }
    if (address <= 0x7FFF)
    {
        return bank1_[address - 0x4000];
    }
    if (address <= 0x9FFF)
    {
        return vram_[address - 0x8000];
    }
    if (address <= 0xBFFF)
    {
        return external_ram_[address - 0xA000];
    }
    if (address <= 0xCFFF)
    {
        return work_ram0_[address - 0xC000];
    }

    if (address <= 0xDFFF)
    {
        return work_ram1_[address - 0xD000];
    }

    if (address <= 0xFDFF)
    {
        return read(address - 0x2000);
    }

    if (address <= 0xFE9F)
    {
        return oam_[address - 0xFE00];
    }

    if (address <= 0xFEFF)
    {
        return 0xFF;
    }

    if (address <= 0xFF7F)
    {
        return io_registers_[address - 0xFF00];
    }

    if (address <= 0xFFFE)
    {
        return hram_[address - 0xFF80];
    }

    return interrupt_enable_; // 0xFFFF

}

void Bus::write(std::uint16_t address, std::uint8_t value)
{
    if (address <= 0x7FFF)
    {
        // Not yet implemented — no-op for now
        return;
    }
    if (address <= 0x9FFF)
    {
        vram_[address - 0x8000] = value;
        return;
    }
    if (address <= 0xBFFF)
    {
        external_ram_[address - 0xA000] = value;
        return;
    }
    if (address <= 0xCFFF)
    {
        work_ram0_[address - 0xC000] = value;
        return;
    }
    
    if (address <= 0xDFFF)
    {
        work_ram1_[address - 0xD000] = value;
        return;
    }

    if (address <= 0xFDFF)
    {
        write(address - 0x2000, value);
        return;
    }
    if (address <= 0xFE9F)
    {
        oam_[address - 0xFE00] = value;
        return;
    }
    if (address <= 0xFEFF)
    {
        return;
    }
    if (address <= 0xFF7F)
    {
        io_registers_[address - 0xFF00] = value;
        return;
    }
    if (address <= 0xFFFE)
    {
        hram_[address - 0xFF80] = value;
        return;
    }

    interrupt_enable_ = value; // 0xFFFF
}

} // namespace gbcemu

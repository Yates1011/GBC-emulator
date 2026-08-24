#include "memory/bus.hpp"

namespace gbcemu
{

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

    // Not yet implemented (Echo RAM, OAM, I/O, HRAM, IE)
    return 0xFF;
}

void Bus::write(std::uint16_t address, std::uint8_t value)
{
    if (address <= 0x3FFF)
    {
        bank0_[address] = value;
        return;
    }
    if (address <= 0x7FFF)
    {
        bank1_[address - 0x4000] = value;
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
    // Not yet implemented — no-op for now
}

} // namespace gbcemu

#include "cartridge/cartridge.hpp"

namespace gbcemu
{

Cartridge::Cartridge(std::vector<std::uint8_t> rom) : rom_(std::move(rom)) {}

std::uint8_t Cartridge::read(std::uint16_t address) const
{
    return rom_.at(address);
}

} // namespace gbcemu

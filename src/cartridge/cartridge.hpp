#pragma once

#include <cstdint>
#include <vector>

namespace gbcemu
{

class Cartridge
{
public:
    explicit Cartridge(std::vector<std::uint8_t> rom);

    [[nodiscard]] std::uint8_t read(std::uint16_t address) const;

private:
    std::vector<std::uint8_t> rom_;
};

} // namespace gbcemu

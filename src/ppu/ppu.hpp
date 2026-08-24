#pragma once

namespace gbcemu
{

class Bus;

class Ppu
{
public:
    explicit Ppu(Bus& bus);

    void step();

private:
    Bus& bus_;
};

} // namespace gbcemu

#pragma once

namespace gbcemu
{

class Bus;

class Cpu
{
public:
    explicit Cpu(Bus& bus);

    void step();

private:
    Bus& bus_;
};

} // namespace gbcemu

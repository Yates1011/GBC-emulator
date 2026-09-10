#include "cpu/cpu.hpp"

namespace gbcemu
{

    Cpu::Cpu(Bus& bus) : bus_(bus) {}

    uint8_t Cpu::control_unit()
    {
        return 0;
    }

    uint8_t Cpu::ALU(uint8_t& input_a, uint8_t input_b)
    {
        return 0;
    }

    uint16_t Cpu::IDU()
    {
        // internal address bus)
        return 0;
    }

    void Cpu::step() {}


    // using OpHandler = void(CPU::*)();
    // static constexpr std::array<OpHandler, 256> opcode_table = { &CPU::op_nop, &CPU::op_ld_bc_d16, ... };

} // namespace gbcemu
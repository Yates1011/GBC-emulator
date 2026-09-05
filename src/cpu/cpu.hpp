#pragma once

#include <array>
#include <cstdint>
/*
The CPU is made up of 4 subsytems:

Control unit - decodes the executed instructions and generates control signals. It is also
repsonsible for checking and dispatching interrupts.

Regisater file - holds most of the state of the CPU in registers.

*/

inline constexpr std::size_t N_GENERAL_PURPOSE_REGISTERS = 6;

namespace gbcemu
{

enum class GeneralPurposeRegistersMap : uint8_t
{
    B = 0,
    C = 1,
    D = 2,
    E = 3,
    H = 4,
    L = 5
};

class Bus;

class Cpu
{
public:
    /* Register file */
    uint16_t program_counter{};
    uint16_t stack_pointer{};
    uint8_t accumulator{};
    uint8_t flags_register{};
    std::array<uint8_t, N_GENERAL_PURPOSE_REGISTERS> general_purpose_registers{};
    uint8_t instruction_register{};
    uint8_t interrupt_enable{}; // TODO: bool?

    explicit Cpu(Bus& bus); // i_/o_: data bus

    void step();

private:
    uint8_t control_unit();

    uint8_t ALU(uint8_t& input_a, uint8_t input_b);

    uint16_t IDU(); // o_: internal address bus

    Bus& bus_;
};

} // namespace gbcemu
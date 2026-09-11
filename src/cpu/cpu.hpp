#pragma once

#include <cstdint>
#include <array>
/*
The CPU is made up of 4 subsytems:

Control unit - decodes the executed instructions and generates control signals. It is also repsonsible 
for checking and dispatching interrupts. 

Regisater file - holds most of the state of the CPU in registers. 

TODO: it is worth noting that GBC instructions 
constantly operate on 16-bit register pairs (LD BC,d16, INC HL, ADD HL,DE, etc.). 
std::array<std::pair<uint8_t,uint8_t>, 3> could be an nice way of dealing with this 

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
            uint16_t program_counter {}; 
            uint16_t stack_pointer   {}; 
            uint8_t accumulator      {};
            uint8_t flags_register   {};
            std::array<uint8_t, N_GENERAL_PURPOSE_REGISTERS> general_purpose_registers{};
            uint8_t instruction_register {};
            uint8_t interrupt_enable {}; // TODO: bool?

            explicit Cpu(Bus& bus); // i_/o_: data bus

            void step(); 

            uint8_t fetch_byte();

            // TODO: need a rest command that sets pc to 0x100
            //https://gbdev.io/pandocs/The_Cartridge_Header.html
            

        private:
            uint8_t control_unit(); // does the decode 

            uint8_t ALU(uint8_t& input_a, uint8_t input_b);

            uint16_t IDU(); // o_: internal address bus 

            Bus& bus_;

            bool isHalted = false;
    };

} // namespace gbcemu
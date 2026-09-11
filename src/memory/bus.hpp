#pragma once

#include <array>
#include <cstdint>

inline constexpr std::size_t WRAM_SIZE = 0x1000;     // 4 KiB
inline constexpr std::size_t VRAM_SIZE = 0x2000;     // 8 KiB
inline constexpr std::size_t ROM_BANK_SIZE = 0x4000; // 16 KiB
inline constexpr std::size_t OAM_SIZE = 0xA0;        // 160 B
inline constexpr std::size_t IO_SIZE = 0x80;         // 128 B
inline constexpr std::size_t HRAM_SIZE = 0x7F;       // 127 B
inline constexpr std::size_t BOOT_ROM_SIZE = 0x100;  // 256 B


class CPU; 


class Bus
{
    public:
        Bus(CPU& cpu);

        [[nodiscard]] std::uint8_t read(std::uint16_t address) const;
        void write(std::uint16_t address, std::uint8_t value);
        void reset();

    private:
        std::array<std::uint8_t, ROM_BANK_SIZE> bank0_{}; // From cartridge, usually a fixed bank
        std::array<std::uint8_t, ROM_BANK_SIZE> bank1_{}; // From cartridge, switchable bank via mapper (if any)
        std::array<std::uint8_t, VRAM_SIZE> vram_{};         // In CGB mode, swtichable bank/01
        std::array<std::uint8_t, VRAM_SIZE> external_ram_{}; // From cartridge, switchable bank if any
        std::array<std::uint8_t, WRAM_SIZE> work_ram0_{};    // In CGB mode, swtichable bank 1-7
        std::array<std::uint8_t, WRAM_SIZE> work_ram1_{};    // In CGB mode, swtichable bank 1-7
        std::array<std::uint8_t, OAM_SIZE> oam_{};
        std::array<std::uint8_t, IO_SIZE> io_registers_{};
        std::array<std::uint8_t, HRAM_SIZE> hram_{};
        std::array<std::uint8_t, BOOT_ROM_SIZE> boot_rom_{};

        std::uint8_t interrupt_enable_{};

        CPU& cpu;

        bool boot_rom_enabled_ {true};

};

enum class MemoryRegion
{
    RomBank00,
    RomBankNN,
    Vram,
    ExternalRam,
    WramBank0,
    WramBankNN,
    EchoRam,
    Oam,
    Unusable,
    IoRegisters,
    Hram,
    InterruptEnable
};


#pragma once

// ============================================================
// XorStr - Compile-time String Encryption (XOR based)
// Encrypts string literals at compile-time so they don't
// appear as plaintext in the compiled binary.
// Usage: XorStr("my secret string").decrypt()
// Or macro: XS("my secret string")
// ============================================================

#include <string>
#include <array>

namespace xor_util
{
    constexpr char XOR_KEY = 0x5A; // Change this key to produce different encrypted output

    template <size_t N>
    class XorString
    {
    private:
        std::array<char, N> m_encrypted;
        
    public:
        // Encrypt at compile-time
        constexpr XorString(const char(&str)[N]) : m_encrypted{}
        {
            for (size_t i = 0; i < N; ++i)
            {
                m_encrypted[i] = str[i] ^ (XOR_KEY + static_cast<char>(i % 7));
            }
        }

        // Decrypt at runtime - returns std::string
        std::string decrypt() const
        {
            std::string result;
            result.reserve(N - 1);
            for (size_t i = 0; i < N - 1; ++i)
            {
                result += static_cast<char>(m_encrypted[i] ^ (XOR_KEY + static_cast<char>(i % 7)));
            }
            return result;
        }

        // Decrypt into a provided char buffer
        void decrypt_to(char* buffer, size_t bufSize) const
        {
            size_t len = (N - 1 < bufSize - 1) ? N - 1 : bufSize - 1;
            for (size_t i = 0; i < len; ++i)
            {
                buffer[i] = static_cast<char>(m_encrypted[i] ^ (XOR_KEY + static_cast<char>(i % 7)));
            }
            buffer[len] = '\0';
        }
    };
}

// Helper macro for easy usage
#define XS(str) (xor_util::XorString<sizeof(str)>(str).decrypt())

// Helper macro that returns c_str() for C-style APIs
#define XSC(str) (xor_util::XorString<sizeof(str)>(str).decrypt().c_str())

#pragma once

// ============================================================
// JunkCode - Dead Code / Mutation Engine
// Adds meaningless but non-removable computations to change
// the binary's instruction layout and hash signature.
// All functions use 'volatile' to prevent compiler optimization.
// ============================================================

#include <cstdint>
#include <cmath>
#include <cstdlib>

namespace JunkEngine
{
    // Volatile sink to prevent dead-code elimination
    inline volatile int g_junk_sink_1 = 0;
    inline volatile int g_junk_sink_2 = 0;
    inline volatile double g_junk_sink_3 = 0.0;
    inline volatile uint64_t g_junk_sink_4 = 0;

    // --- Block A: Integer arithmetic junk ---
    inline void JunkBlockA()
    {
        volatile int a = 17;
        volatile int b = 43;
        volatile int c = 0;
        for (volatile int i = 0; i < 3; i++)
        {
            c = (a * b + i) ^ (b - a);
            a = c % 127 + 1;
            b = (a + c) ^ 0x3F;
        }
        g_junk_sink_1 = c;
    }

    // --- Block B: Floating point junk ---
    inline void JunkBlockB()
    {
        volatile double x = 2.71828;
        volatile double y = 3.14159;
        volatile double z = 0.0;
        for (volatile int i = 0; i < 5; i++)
        {
            z = sin(x) * cos(y) + tan(x * 0.1);
            x = z + 0.001 * i;
            y = x * z - 1.337;
        }
        g_junk_sink_3 = z;
    }

    // --- Block C: Bitwise manipulation junk ---
    inline void JunkBlockC()
    {
        volatile uint64_t val = 0xDEADBEEFCAFEBABEULL;
        volatile uint64_t mask = 0xF0F0F0F0F0F0F0F0ULL;
        for (volatile int i = 0; i < 4; i++)
        {
            val = (val ^ mask) >> 3;
            mask = (mask << 1) | (val & 0xFF);
            val = val + mask - (i * 0x1337);
        }
        g_junk_sink_4 = val;
    }

    // --- Block D: Mixed computation junk ---
    inline void JunkBlockD()
    {
        volatile int arr[8] = { 12, 45, 78, 23, 56, 89, 34, 67 };
        volatile int sum = 0;
        for (volatile int i = 0; i < 8; i++)
        {
            sum += arr[i] * (i + 1);
            arr[i] = sum ^ (arr[i] << 2);
        }
        g_junk_sink_2 = sum;
    }

    // --- Block E: Nested loop junk ---
    inline void JunkBlockE()
    {
        volatile int matrix[4][4] = { {0} };
        for (volatile int i = 0; i < 4; i++)
        {
            for (volatile int j = 0; j < 4; j++)
            {
                matrix[i][j] = (i * 4 + j) ^ 0xAB;
                matrix[i][j] = matrix[i][j] * 3 + 7;
            }
        }
        g_junk_sink_1 = matrix[3][3];
    }

    // --- Block F: String-like byte manipulation junk ---
    inline void JunkBlockF()
    {
        volatile char buf[32] = { 0 };
        for (volatile int i = 0; i < 31; i++)
        {
            buf[i] = static_cast<char>((i * 7 + 13) % 95 + 32);
        }
        volatile int hash = 0;
        for (volatile int i = 0; i < 31; i++)
        {
            hash = hash * 31 + buf[i];
        }
        g_junk_sink_2 = hash;
    }

    // --- Block G: Fibonacci-like junk ---
    inline void JunkBlockG()
    {
        volatile uint64_t a = 1, b = 1, c = 0;
        for (volatile int i = 0; i < 20; i++)
        {
            c = a + b;
            a = b;
            b = c;
        }
        g_junk_sink_4 = c;
    }

    // --- Block H: Prime sieve junk ---
    inline void JunkBlockH()
    {
        volatile int count = 0;
        for (volatile int n = 2; n < 50; n++)
        {
            volatile bool is_prime = true;
            for (volatile int d = 2; d * d <= n; d++)
            {
                if (n % d == 0) { is_prime = false; break; }
            }
            if (is_prime) count++;
        }
        g_junk_sink_1 = count;
    }

    // Master function - call this to inject all junk blocks
    inline void RunAllJunk()
    {
        JunkBlockA();
        JunkBlockB();
        JunkBlockC();
        JunkBlockD();
        JunkBlockE();
        JunkBlockF();
        JunkBlockG();
        JunkBlockH();
    }

    // Scatter junk - call individual blocks at different points in code
    inline void ScatterJunk1() { JunkBlockA(); JunkBlockC(); JunkBlockG(); }
    inline void ScatterJunk2() { JunkBlockB(); JunkBlockD(); JunkBlockH(); }
    inline void ScatterJunk3() { JunkBlockE(); JunkBlockF(); }
}

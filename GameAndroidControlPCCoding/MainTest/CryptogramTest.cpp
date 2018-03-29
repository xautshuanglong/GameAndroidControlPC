#include "CryptogramTest.h"

#include <Algorithm/AES.h>
#include "Log.h"

namespace Shuanglong::Test
{
    uint8_t aes_xtime(uint8_t x)
    {
        return ((x << 1) ^ (((x >> 7) & 1) * 0x1b));
    }

    uint8_t aes_xtimes(uint8_t x, int ts)
    {
        while (ts-- > 0)
        {
            x = aes_xtime(x);
        }

        return x;
    }

    uint8_t aes_mul(uint8_t x, uint8_t y)
    {
        /*
        * encrypt: y has only 2 bits: can be 1, 2 or 3
        * decrypt: y could be any value of 9, b, d, or e
        */

        return ((((y >> 0) & 1) * aes_xtimes(x, 0)) ^
                (((y >> 1) & 1) * aes_xtimes(x, 1)) ^
                (((y >> 2) & 1) * aes_xtimes(x, 2)) ^
                (((y >> 3) & 1) * aes_xtimes(x, 3)) ^
                (((y >> 4) & 1) * aes_xtimes(x, 4)) ^
                (((y >> 5) & 1) * aes_xtimes(x, 5)) ^
                (((y >> 6) & 1) * aes_xtimes(x, 6)) ^
                (((y >> 7) & 1) * aes_xtimes(x, 7)));
    }

    void aes_mix_columns(uint8_t *state)
    {
        uint8_t y[16] = { 2, 3, 1, 1,  1, 2, 3, 1,  1, 1, 2, 3,  3, 1, 1, 2 };
        uint8_t s[4];
        int i, j, r;

        for (i = 0; i < 4; i++)
        {
            for (r = 0; r < 4; r++)
            {
                s[r] = 0;
                for (j = 0; j < 4; j++)
                {
                    s[r] = s[r] ^ aes_mul(state[i * 4 + j], y[r * 4 + j]);
                }
            }
            for (r = 0; r < 4; r++)
            {
                state[i * 4 + r] = s[r];
            }
        }
    }

    CryptogramTest::CryptogramTest()
    {}

    CryptogramTest::~CryptogramTest()
    {}

    void CryptogramTest::Entry()
    {
        std::cout << std::endl << "----------------------------------- Cryptogram Testing -----------------------------------" << std::endl;
        Shuanglong::Algorithm::AES aes;
        aes.Test();

        uint8_t pTest[] = { 0x63, 0x53, 0xe0, 0x8c, 0x09, 0x60, 0xe1, 0x04, 0xcd, 0x70, 0xb7, 0x51, 0xba, 0xca, 0xd0, 0xe7 };
        aes_mix_columns(pTest);
        int i = 0;
    }

    void CryptogramTest::Exit()
    {
        ;
    }
}

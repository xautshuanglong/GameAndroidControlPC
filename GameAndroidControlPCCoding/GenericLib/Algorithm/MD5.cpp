#include "stdafx.h"
#include "MD5.h"

namespace Shuanglong::Algorithm
{
/* Constants for MD5Transform routine. */
#define S11 7  
#define S12 12  
#define S13 17  
#define S14 22  
#define S21 5  
#define S22 9  
#define S23 14  
#define S24 20  
#define S31 4  
#define S32 11  
#define S33 16  
#define S34 23  
#define S41 6  
#define S42 10  
#define S43 15  
#define S44 21  

/* F, G, H and I are basic MD5 functions. */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))  
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))  
#define H(x, y, z) ((x) ^ (y) ^ (z))  
#define I(x, y, z) ((y) ^ ((x) | (~z)))  

/* ROTATE_LEFT rotates x left n bits.*/
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))  

/*
    FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
    Rotation is separate from addition to prevent recomputation.
*/
#define FF(a, b, c, d, x, s, ac) {     \
    (a) += F((b), (c), (d)) + (x)+ac;  \
    (a) = ROTATE_LEFT((a), (s));       \
    (a) += (b);                        \
}

#define GG(a, b, c, d, x, s, ac) {     \
    (a) += G((b), (c), (d)) + (x)+ac;  \
    (a) = ROTATE_LEFT((a), (s));       \
    (a) += (b);                        \
}

#define HH(a, b, c, d, x, s, ac) {     \
    (a) += H((b), (c), (d)) + (x)+ac;  \
    (a) = ROTATE_LEFT((a), (s));       \
    (a) += (b);                        \
}

#define II(a, b, c, d, x, s, ac) {     \
    (a) += I((b), (c), (d)) + (x)+ac;  \
    (a) = ROTATE_LEFT((a), (s));       \
    (a) += (b);                        \
}

    const byte MD5::PADDING[64] = { 0x80 };
    const char MD5::HEX[16] = {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'a', 'b',
        'c', 'd', 'e', 'f'
    };


    const unsigned int r[] = {
        7,12,17,22,
        7,12,17,22,
        7,12,17,22,
        7,12,17,22,
        5,9,14,20,
        5,9,14,20,
        5,9,14,20,
        5,9,14,20,
        4,11,16,23,
        4,11,16,23,
        4,11,16,23,
        4,11,16,23,
        6,10,15,21,
        6,10,15,21,
        6,10,15,21,
        6,10,15,21 };

    MD5::MD5()
    {
        //Initialize variables:
        int h0 = 0x67452301;
        int h1 = 0xEFCDAB89;
        int h2 = 0x98BADCFE;
        int h3 = 0x10325476;

        int a = h0;
        int b = h1;
        int c = h2;
        int d = h3;

        int tempF = 0, tempG = 0;

        byte message[64] = { 0 };
        unsigned int k[64] = { 0 };
        message[0] = 0x80;
        message[1] = 0;
        message[2] = 0;
        message[3] = 0;
        long long len = 0;
        int w[16] = { 0 };
        memcpy_s(&message[56], 8, &len, 8);

        for (int i = 0; i < 64; ++i)
        {
            k[i] = abs(sin(i + 1)) * pow(2, 32);
        }

        for (int i = 0; i < 16; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                w[i] |= message[i * 4 + j] << (j * 8);
            }
        }

        for (int i = 0; i < 64; ++i)
        {
            if (i < 16)
            {
                tempF = F(b, c, d);
                tempG = i;
            }
            else if (i < 32)
            {
                tempF = G(b, c, d);
                tempG = (i * 5 + 1) % 16;
            }
            else if (i < 48)
            {
                tempF = H(b, c, d);
                tempG = (i * 3 + 5) % 16;
            }
            else if (i <= 64)
            {
                tempF = I(b, c, d);
                tempG = (i * 7) % 16;
            }

            unsigned int temp = d;
            d = c;
            c = b;
            b = ROTATE_LEFT((a + tempF + k[i] + w[tempG]), r[i]) + b;
            a = temp;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;

        printf_s("%s:%d md5=%s\n", __FILE__, __LINE__, (DDChangeHex(h0).append(DDChangeHex(h1)).append(DDChangeHex(h2)).append(DDChangeHex(h3))).c_str());
    }

    MD5::~MD5()
    {
    }

    std::string MD5::DDChangeHex(int a)
    {
        int b;
        std::string StrA = "";
        std::string StrB;
        for (int i = 0; i < 4; i++)
        {
            StrB = "";
            b = ((a >> i * 8) % (1 << 8)) & 0xff;   //逆序处理每个字节
            for (int j = 0; j < 2; j++)
            {
                StrB.insert(0, 1, HEX[b % 16]);
                b = b / 16;
            }
            StrA += StrB;
        }
        return StrA;
    }
}

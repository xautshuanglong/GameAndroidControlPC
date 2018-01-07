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

        //MD5("The quick brown fox jumps over the lazy dog") = 9e107d9d372bb6826bd81d3542a419d6
        //MD5("The quick brown fox jumps over the lazy cog") = 1055d3e698d289f2af8663725127bd4b

        byte message[64] = { 0 };
        unsigned int k[64] = { 0 };
        message[0] = 'T';
        message[1] = 'h';
        message[2] = 'e';
        message[3] = ' ';
        message[4] = 'q';
        message[5] = 'u';
        message[6] = 'i';
        message[7] = 'c';
        message[8] = 'k';
        message[9] = ' ';
        message[10] = 'b';
        message[11] = 'r';
        message[12] = 'o';
        message[13] = 'w';
        message[14] = 'n';
        message[15] = ' ';
        message[16] = 'f';
        message[17] = 'o';
        message[18] = 'x';
        message[19] = ' ';
        message[20] = 'j';
        message[21] = 'u';
        message[22] = 'm';
        message[23] = 'p';
        message[24] = 's';
        message[25] = ' ';
        message[26] = 'o';
        message[27] = 'v';
        message[28] = 'e';
        message[29] = 'r';
        message[30] = ' ';
        message[31] = 't';
        message[32] = 'h';
        message[33] = 'e';
        message[34] = ' ';
        message[35] = 'l';
        message[36] = 'a';
        message[37] = 'z';
        message[38] = 'y';
        message[39] = ' ';
        message[40] = 'c';
        message[41] = 'o';
        message[42] = 'g';
        message[43] = 0x80;
        
        //message[56] = 0x58;
        //message[57] = 0x01;
        //message[58] = 0x00;
        //message[59] = 0x00;
        //message[60] = 0x00;
        //message[61] = 0x00;
        //message[62] = 0x00;
        //message[63] = 0x00;
        long long len = 344;
        int w[16] = { 0 };
        if (IsLittleEndian())
        {
            printf_s("Is little endian\n");
            memcpy_s(&message[56], 8, &len, 8);
        }

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

    void MD5::Update(std::string &inString)
    {}

    void MD5::Update(std::ifstream &inFileStream)
    {}

    void MD5::Update(const char* inBuffer, int inLength)
    {}

    std::string MD5::FinalDigest()
    {
        std::string retString = "";
        return retString;
    }

    bool MD5::IsLittleEndian()
    {
        bool retFlag = false;
        union EndianTest
        {
            int intVaule;
            char bytes[4];
        };

        EndianTest endian = { 0 };
        endian.intVaule = 0x12345678;
        if (endian.bytes[0] == 0x78)
        {
            retFlag = true;
        }
        return retFlag;
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

#include "Mn.h"

const unsigned int Tenzo1[24] = {
    T1_V1,
    T1_V2,
    T1_V3,
    T1_V4,
    T1_V5,
    T1_V6,
    T1_V7,
    T1_V8,
    T1_V9,
    T1_V10,
    T1_V11,
    T1_V12,
    T1_V13,
    T1_V14,
    T1_V15,
    T1_V16,
    T1_V17,
    T1_V18,
    T1_V19,
    T1_V20,
    T1_V21,
    T1_V22,
    T1_V23,
    T1_V24};

const int TempTenzo1[24] = {
    -55,
    -50,
    -40,
    -30,
    -20,
    -10,
    0,
    10,
    20,
    25,
    30,
    40,
    50, 60, 70, 80, 90, 100, 110, 120, 125, 130, 140, 150
};



const unsigned int Tenzo2[34] = {T2_V1,
    T2_V2,
    T2_V3,
    T2_V4,
    T2_V5,
    T2_V6,
    T2_V7,
    T2_V8,
    T2_V9,
    T2_V10,
    T2_V11,
    T2_V12,
    T2_V13,
    T2_V14,
    T2_V15,
    T2_V16,
    T2_V17,
    T2_V18,
    T2_V19,
    T2_V20,
    T2_V21,
    T2_V22,
    T2_V23,
    T2_V24,
    T2_V25,
    T2_V26,
    T2_V27,
    T2_V28,
    T2_V29,
    T2_V30,
    T2_V31,
    T2_V32,
    T2_V33,
    T2_V34};

const int TempTenzo2[34] = {
    -40,
    -35,
    -30,
    -25,
    -20,
    -15,
    -10,
    -5,
    0,
    5,
    10,
    15,
    20,
    25,
    30,
    35,
    40,
    45,
    50,
    55,
    60,
    65,
    70,
    75,
    80,
    85,
    90,
    95,
    100,
    105,
    110,
    115,
    120,
    125
};

const unsigned int Tenzo7[29] = {
    T7_V1,
    T7_V2,
    T7_V3,
    T7_V4,
    T7_V5,
    T7_V6,
    T7_V7,
    T7_V8,
    T7_V9,
    T7_V10,
    T7_V11,
    T7_V12,
    T7_V13,
    T7_V14,
    T7_V15,
    T7_V16,
    T7_V17,
    T7_V18,
    T7_V19,
    T7_V20,
    T7_V21,
    T7_V22,
    T7_V23,
    T7_V24,
    T7_V25,
    T7_V26,
    T7_V27,
    T7_V28,
    T7_V29
};

const int TempTenzo7[] = {
    -30,
    -25,
    -20,
    -15,
    -10,
    -5,
    -0,
    5,
    10,
    15,
    20,
    25,
    30,
    35,
    40,
    45,
    50,
    55,
    60,
    65,
    70,
    75,
    80,
    85,
    90,
    95,
    100,
    105,
    110
};




const unsigned int Tenzo8[29] = {
    T8_V1,
    T8_V2,
    T8_V3,
    T8_V4,
    T8_V5,
    T8_V6,
    T8_V7,
    T8_V8,
    T8_V9,
    T8_V10,
    T8_V11,
    T8_V12,
    T8_V13,
    T8_V14,
    T8_V15,
    T8_V16,
    T8_V17,
    T8_V18,
    T8_V19,
    T8_V20,
    T8_V21,
    T8_V22,
    T8_V23,
    T8_V24,
    T8_V25,
    T8_V26,
    T8_V27,
    T8_V28,
    T8_V29
};

const unsigned int Tenzo9[166] = {
    T9_V1,
    T9_V2,
    T9_V3,
    T9_V4,
    T9_V5,
    T9_V6,
    T9_V7,
    T9_V8,
    T9_V9,
    T9_V10,
    T9_V11,
    T9_V12,
    T9_V13,
    T9_V14,
    T9_V15,
    T9_V16,
    T9_V17,
    T9_V18,
    T9_V19,
    T9_V20,
    T9_V21,
    T9_V22,
    T9_V23,
    T9_V24,
    T9_V25,
    T9_V26,
    T9_V27,
    T9_V28,
    T9_V29,

    T9_V30,
    T9_V31,
    T9_V32,
    T9_V33,
    T9_V34,
    T9_V35,
    T9_V36,
    T9_V37,
    T9_V38,
    T9_V39,
    T9_V40,
    T9_V41,
    T9_V42,
    T9_V43,
    T9_V44,
    T9_V45,
    T9_V46,
    T9_V47,
    T9_V48,
    T9_V49,
    T9_V50,
    T9_V51,
    T9_V52,
    T9_V53,
    T9_V54,
    T9_V55,
    T9_V56,
    T9_V57,
    T9_V58,
    T9_V59,
    T9_V60,
    T9_V61,
    T9_V62,
    T9_V63,
    T9_V64,
    T9_V65,
    T9_V66,
    T9_V67,
    T9_V68,
    T9_V69,
    T9_V70,
    T9_V71,
    T9_V72,
    T9_V73,
    T9_V74,
    T9_V75,
    T9_V76,
    T9_V77,
    T9_V78,
    T9_V79,
    T9_V80,
    T9_V81,
    T9_V82,
    T9_V83,
    T9_V84,
    T9_V85,
    T9_V86,
    T9_V87,
    T9_V88,
    T9_V89,
    T9_V90,
    T9_V91,
    T9_V92,
    T9_V93,
    T9_V94,
    T9_V95,
    T9_V96,
    T9_V97,
    T9_V98,
    T9_V99,
    T9_V100,
    T9_V101,
    T9_V102,
    T9_V103,
    T9_V104,
    T9_V105,
    T9_V106,
    T9_V107,
    T9_V108,
    T9_V109,
    T9_V110,
    T9_V111,
    T9_V112,
    T9_V113,
    T9_V114,
    T9_V115,
    T9_V116,
    T9_V117,
    T9_V118,
    T9_V119,
    T9_V120,
    T9_V121,
    T9_V122,
    T9_V123,
    T9_V124,
    T9_V125,
    T9_V126,
    T9_V127,
    T9_V128,
    T9_V129,
    T9_V130,
    T9_V131,
    T9_V132,
    T9_V133,
    T9_V134,
    T9_V135,
    T9_V136,
    T9_V137,
    T9_V138,
    T9_V139,
    T9_V140,
    T9_V141,
    T9_V142,
    T9_V143,
    T9_V144,
    T9_V145,
    T9_V146,
    T9_V147,
    T9_V148,
    T9_V149,
    T9_V150,
    T9_V151,
    T9_V152,
    T9_V153,
    T9_V154,
    T9_V155,
    T9_V156,
    T9_V157,
    T9_V158,
    T9_V159,
    T9_V160,
    T9_V161,
    T9_V162,
    T9_V163,
    T9_V164,
    T9_V165,
    T9_V166

};


const int TempTenzo8[29] = {
    -30,
    -25,
    -20,
    -15,
    -10,
    -5,
    -0,
    5,
    10,
    15,
    20,
    25,
    30,
    35,
    40,
    45,
    50,
    55,
    60,
    65,
    70,
    75,
    80,
    85,
    90,
    95,
    100,
    105,
    110
};


const int TempTenzo9[166] = {
    -40,
    -39,
    -38,
    -37,
    -36,
    -35,
    -34,
    -33,
    -32,
    -31,
    -30,
    -29,
    -28,
    -27,
    -26,
    -25,
    -24,
    -23,
    -22,
    -21,
    -20,
    -19,
    -18,
    -17,
    -16,
    -15,
    -14,
    -13,
    -12,
    -11,
    -10,
    -9,
    -8,
    -7,
    -6,
    -5,
    -4,
    -3,
    -2,
    -1,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    24,
    25,
    26,
    27,
    28,
    29,
    30,
    31,
    32,
    33,
    34,
    35,
    36,
    37,
    38,
    39,
    40,
    41,
    42,
    43,
    44,
    45,
    46,
    47,
    48,
    49,
    50,
    51,
    52,
    53,
    54,
    55,
    56,
    57,
    58,
    59,
    60,
    61,
    62,
    63,
    64,
    65,
    66,
    67,
    68,
    69,
    70,
    71,
    72,
    73,
    74,
    75,
    76,
    77,
    78,
    79,
    80,
    81,
    82,
    83,
    84,
    85,
    86,
    87,
    88,
    89,
    90,
    91,
    92,
    93,
    94,
    95,
    96,
    97,
    98,
    99,
    100,
    101,
    102,
    103,
    104,
    105,
    106,
    107,
    108,
    109,
    110,
    111,
    112,
    113,
    114,
    115,
    116,
    117,
    118,
    119,
    120,
    121,
    122,
    123,
    124,
    125
};



const unsigned int Tenzo3[] = {T3_V1,
    T3_V2,
    T3_V3,
    T3_V4,
    T3_V5,
    T3_V6,
    T3_V7,
    T3_V8,
    T3_V9,
    T3_V10,
    T3_V11,
    T3_V12,
    T3_V13,
    T3_V14,
    T3_V15,
    T3_V16,
    T3_V17,
    T3_V18,
    T3_V19,
    T3_V20,
    T3_V21,
    T3_V22,
    T3_V23,
    T3_V24,
    T3_V25,
    T3_V26,
    T3_V27,};




const unsigned int Tenzo5[] = {T5_V1,
    T5_V2,
    T5_V3,
    T5_V4,
    T5_V5,
    T5_V6,
    T5_V7,
    T5_V8,
    T5_V9,
    T5_V10,
    T5_V11,
    T5_V12,
    T5_V13,
    T5_V14,
    T5_V15,
    T5_V16,
    T5_V17,
    T5_V18,
    T5_V19,
    T5_V20,
    T5_V21,
    T5_V22,
    T5_V23,
    T5_V24,
    T5_V25,
    T5_V26,
    T5_V27,};




const int TempTenzo3[] = {
    -55,
    -50,
    -40,
    -30,
    -20,
    -10,
    0,
    10,
    20,
    25,
    30,
    40,
    50,
    60,
    70,
    80,
    90,
    100,
    110,
    120,
    125,
    130,
    140,
    150,
    160,
    170,
    175
};



const unsigned int Tenzo4[] = {T4_V1,
    T4_V2,
    T4_V3,
    T4_V4,
    T4_V5,
    T4_V6,
    T4_V7,
    T4_V8,
    T4_V9,
    T4_V10,
    T4_V11,
    T4_V12,
    T4_V13,
    T4_V14,
    T4_V15,
    T4_V16,
    T4_V17,
    T4_V18,
    T4_V19,
    T4_V20,
    T4_V21,
    T4_V22,
    T4_V23,
    T4_V24,
    T4_V25,
    T4_V26,
    T4_V27,
    T4_V28,
    T4_V29,
    T4_V30,
    T4_V31,
    T4_V32,
    T4_V33,
    T4_V34,
    T4_V35,
    T4_V36,};

const int TempTenzo4[] = {
    -40,
    -30,
    -20,
    -10,
    0,
    10,
    20,
    25,
    30,
    40,
    50,
    60,
    70,
    80,
    90,
    100,
    110,
    120,
    130,
    140,
    150,
    160,
    170,
    180,
    190,
    200,
    210,
    220,
    230,
    240,
    250,
    260,
    270,
    280,
    290,
    300

};









const unsigned int Tenzo6[] = {T5_V1,
    T6_V2,
    T6_V3,
    T6_V4,
    T6_V5,
    T6_V6,
    T6_V7,
    T6_V8,
    T6_V9,
    T6_V10,
    T6_V11,
    T6_V12,
    T6_V13,
    T6_V14,
    T6_V15,
    T6_V16,
    T6_V17,
    T6_V18,
    T6_V19,
    T6_V20,
    T6_V21,
    T6_V22,
    T6_V23,
    T6_V24,};




const int TempTenzo6[] = {
    -55,
    -50,
    -40,
    -30,
    -20,
    -10,
    0,
    10,
    20,
    25,
    30,
    40,
    50,
    60,
    70,
    80,
    90,
    100,
    110,
    120,
    125,
    130,
    140,
    150

};




float GetTemperaturePTC_KTY81_210(unsigned int ResTemp) {
    int k = 0, sz = sizeof (Tenzo1);
    float T, T1, temp;

    sz = sz >> 1;

    while (ResTemp > Tenzo1[k])
        k++;

    if (k >= sz)
        return (float) 150;

    if (k == 0)
        return (float) - 55;

    T = Tenzo1[k] - Tenzo1[k - 1];
    T1 = ResTemp - Tenzo1[k - 1];

    temp = TempTenzo1[k] - TempTenzo1[k - 1];


    T1 = (T1 * temp) / T;

    T = TempTenzo1[k - 1] + T1;



    return T;
}





float GetTemperature_NTCALUG03A103H(unsigned int ResTemp) {
    int k = 0, sz = sizeof (Tenzo2);
    float T, T1, temp;

    sz = sz >> 1;

    while (ResTemp < Tenzo2[k])
        k++;

    if (k >= sz)
        return (float) 125;

    if (k == 0)
        return (float) - 40;

    T = Tenzo2[k - 1] - Tenzo2[k];
    T1 = Tenzo2[k - 1] - ResTemp;

    temp = TempTenzo2[k] - TempTenzo2[k - 1];


    T1 = (T1 * temp) / T;

    T = TempTenzo2[k - 1] + T1;



    return T;
}




float GetTemperature_MF58_B_5K(unsigned int ResTemp) {
    int k = 0, sz = sizeof (Tenzo7);
    float T, T1, temp;

    sz = sz >> 1;

    while (ResTemp < Tenzo7[k])
        k++;

    if (k >= sz)
        return (float) 125;

    if (k == 0)
        return (float) - 40;

    T = Tenzo7[k - 1] - Tenzo7[k];
    T1 = Tenzo7[k - 1] - ResTemp;

    temp = TempTenzo7[k] - TempTenzo7[k - 1];


    T1 = (T1 * temp) / T;

    T = TempTenzo7[k - 1] + T1;



    return T;
}




float GetTemperature_MF58_G_10K(unsigned int ResTemp) {
    int k = 0, sz = sizeof (Tenzo8);
    float T, T1, temp;

    sz = sz >> 1;

    while (ResTemp < Tenzo8[k])
        k++;

    if (k >= sz)
        return (float) 125;

    if (k == 0)
        return (float) - 40;

    T = Tenzo8[k - 1] - Tenzo8[k];
    T1 = Tenzo8[k - 1] - ResTemp;

    temp = TempTenzo8[k] - TempTenzo8[k - 1];


    T1 = (T1 * temp) / T;

    T = TempTenzo8[k - 1] + T1;



    return T;
}



float GetTemperature_NCP18XH103F03RB(unsigned int ResTemp) {
    int k = 0, sz = sizeof (Tenzo9);
    float T, T1, temp;

    sz = sz >> 1;

    while (ResTemp < Tenzo9[k])
        k++;

    if (k >= sz)
        return (float) 125;

    if (k == 0)
        return (float) - 40;

    T = Tenzo9[k - 1] - Tenzo9[k];
    T1 = Tenzo9[k - 1] - ResTemp;

    temp = TempTenzo9[k] - TempTenzo9[k - 1];


    T1 = (T1 * temp) / T;

    T = TempTenzo9[k - 1] + T1;



    return T;
}


float GetTemperaturePTC_KTY83_110(unsigned int ResTemp) {
    int k = 0, sz = sizeof (Tenzo3);
    float T, T1, temp;

    sz = sz >> 1;

    while (ResTemp > Tenzo3[k])
        k++;

    if (k >= sz)
        return (float) 150;

    if (k == 0)
        return (float) - 55;

    T = Tenzo3[k] - Tenzo3[k - 1];
    T1 = ResTemp - Tenzo3[k - 1];

    temp = TempTenzo3[k] - TempTenzo3[k - 1];


    T1 = (T1 * temp) / T;

    T = TempTenzo3[k - 1] + T1;



    return T;
}

float GetTemperaturePTC_KTY83_122(unsigned int ResTemp) {
    int k = 0, sz = sizeof (Tenzo5);
    float T, T1, temp;

    sz = sz >> 1;

    while (ResTemp > Tenzo5[k])
        k++;

    if (k >= sz)
        return (float) 150;

    if (k == 0)
        return (float) - 55;

    T = Tenzo5[k] - Tenzo5[k - 1];
    T1 = ResTemp - Tenzo5[k - 1];

    temp = TempTenzo3[k] - TempTenzo3[k - 1]; // TempTenzo3 and TempTenzo5 are the same


    T1 = (T1 * temp) / T;

    T = TempTenzo3[k - 1] + T1;



    return T;
}

float GetTemperaturePTC_KTY81_210_FETs(unsigned int ResTemp) {
    int k = 0, sz = sizeof (Tenzo6);
    float T, T1, temp;

    sz = sz >> 1;

    while (ResTemp > Tenzo6[k])
        k++;

    if (k >= sz)
        return (float) 150;

    if (k == 0)
        return (float) - 55;

    T = Tenzo6[k] - Tenzo6[k - 1];
    T1 = ResTemp - Tenzo6[k - 1];

    temp = TempTenzo6[k] - TempTenzo6[k - 1];


    T1 = (T1 * temp) / T;

    T = TempTenzo6[k - 1] + T1;



    return T;
}

float GetTemperaturePTC_KTY84_130(unsigned int ResTemp) {
    int k = 0, sz = sizeof (Tenzo4);
    float T, T1, temp;

    sz = sz >> 1;

    while (ResTemp > Tenzo4[k])
        k++;

    if (k >= sz)
        return (float) 150;

    if (k == 0)
        return (float) - 55;

    T = Tenzo4[k] - Tenzo4[k - 1];
    T1 = ResTemp - Tenzo4[k - 1];

    temp = TempTenzo4[k] - TempTenzo4[k - 1];


    T1 = (T1 * temp) / T;

    T = TempTenzo4[k - 1] + T1;



    return T;
}
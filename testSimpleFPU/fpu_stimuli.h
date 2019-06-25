#define N 50
int A_float[] = {
0x6b8b4567,
0x66334873,
0x2ae8944a,
0x46e87ccd,
0x2eb141f2,
0x7545e146,
0x12200854,
0x1f16e9e8,
0x140e0f76,
0xded7263,
0x41a7c4c9,
0x25e45d32,
0x3f2dba31,
0x62bbd95a,
0x333ab105,
0x2d1d5ae9,
0x8edbdab,
0xb03e0c6,
0x71f32454,
0x2901d82,
0x1e7ff521,
0x6ceaf087,
0x3006c83e,
0x5577f8e1,
0x3804823e,
0x5c482a97,
0x51ead36b,
0x153ea438,
0x6a2342ec,
0x725a06fb,
0x7a6d8d3c,
0x6de91b18,
0x32fff902,
0x749abb43,
0x79a1deaa,
0x70c6a529,
0x4f4ef005,
0x275ac794,
0x180115be,
0x354fe9f9,
0xd34b6a8,
0x61574095,
0x579be4f1,
0x2f305def,
0x4ad084e9,
0x5db70ae5,
0x15014acb,
0x799d0247,
0x168e121f,
0x5dc79ea8,
};
int B_float[] = {
0x327b23c6,
0x74b0dc51,
0x625558ec,
0x3d1b58ba,
0x41b71efb,
0x515f007c,
0x4db127f8,
0x1190cde7,
0x3352255a,
0x3e4ccccd,
0x6b68079a,
0x519b500d,
0x7c83e458,
0x436c6125,
0x721da317,
0x6763845e,
0x79838cb2,
0x189a769b,
0x2ca88611,
0x3a95f874,
0x7c3dbd3d,
0x22221a70,
0x614fd4a1,
0x440badfc,
0x77465f01,
0x2463b9ea,
0x2d517796,
0x3855585c,
0x2a487cb0,
0x2cd89a32,
0x4b588f54,
0x38437fdb,
0x684a481a,
0x3dc240fb,
0x75c6c33a,
0x520eedd1,
0x23f9c13c,
0x39386575,
0x235ba861,
0x15b5af5c,
0x10233c99,
0x7e0c57b1,
0x310c50b3,
0x25a70bf7,
0x1f48eaa1,
0x100f8fca,
0x5f5e7fd0,
0x6b94764,
0x1eba5d23,
0x540a471c,
};
int C_float[] = {
0x643c9869,
0x19495cff,
0x238e1f29,
0x507ed7ab,
0x79e2a9e3,
0x5bd062c2,
0x216231b,
0x66ef438d,
0x109cf92e,
0x1befd79f,
0x4e6afb66,
0x431bd7b7,
0x257130a3,
0x628c895d,
0x2443a858,
0x75a2a8d4,
0x4353d0cd,
0x54e49eb4,
0x836c40e,
0x8138641,
0x737b8ddc,
0x4516dde9,
0x419ac241,
0x5072367,
0x7724c67e,
0x5e884adc,
0x580bd78f,
0x70a64e2a,
0x1d4ed43b,
0x57e4ccaf,
0x542289ec,
0x7644a45c,
0x579478fe,
0x1ba026fa,
0x12e685fb,
0x374a3fe6,
0x649bb77c,
0x1cf10fd8,
0x47398c89,
0x741226bb,
0x3f6ab60f,
0x77ae35eb,
0x5ff87e05,
0x1dbabf00,
0x1381823a,
0x6590700b,
0x98a3148,
0x42c296bd,
0x661e3f1e,
0x7bd3ee7b,
};
int add_exp[] = {
0x6b8b4567,
0x74b0dc51,
0x625558ec,
0x46e87ce0,
0x41b71efb,
0x7545e146,
0x4db127f8,
0x1f16e9e8,
0x3352255a,
0x3e4ccccd,
0x6b68079a,
0x519b500d,
0x7c83e458,
0x62bbd95a,
0x721da317,
0x6763845e,
0x79838cb2,
0x189a769b,
0x71f32454,
0x3a95f874,
0x7c3dbd3d,
0x6ceaf087,
0x614fd4a1,
0x5577f8e1,
0x77465f01,
0x5c482a97,
0x51ead36b,
0x3855585c,
0x6a2342ec,
0x725a06fb,
0x7a6d8d3c,
0x6de91b18,
0x684a481a,
0x749abb43,
0x79a2a56d,
0x70c6a529,
0x4f4ef005,
0x39386575,
0x235ba863,
0x354fe9f9,
0x10260f74,
0x7e0c57b1,
0x579be4f1,
0x2f305e04,
0x4ad084e9,
0x5db70ae5,
0x5f5e7fd0,
0x799d0247,
0x1eba5db1,
0x5dc79eb9,
};
int sub_exp[] = {
0x6b8b4567,
0xf4b0dc51,
0xe25558ec,
0x46e87cba,
0xc1b71efb,
0x7545e146,
0xcdb127f8,
0x1f16e9e8,
0xb352255a,
0xbe4ccccd,
0xeb68079a,
0xd19b500d,
0xfc83e458,
0x62bbd95a,
0xf21da317,
0xe763845e,
0xf9838cb2,
0x989a769b,
0x71f32454,
0xba95f874,
0xfc3dbd3d,
0x6ceaf087,
0xe14fd4a1,
0x5577f8e1,
0xf7465f01,
0x5c482a97,
0x51ead36b,
0xb855585c,
0x6a2342ec,
0x725a06fb,
0x7a6d8d3c,
0x6de91b18,
0xe84a481a,
0x749abb43,
0x79a117e7,
0x70c6a529,
0x4f4ef005,
0xb9386575,
0xa35ba85f,
0x354fe9f9,
0x902069be,
0xfe0c57b1,
0x579be4f1,
0x2f305dda,
0x4ad084e9,
0x5db70ae5,
0xdf5e7fd0,
0x799d0247,
0x9eba5c95,
0x5dc79e97,
};
int min_exp[] = {
0x327b23c6,
0x66334873,
0x2ae8944a,
0x3d1b58ba,
0x2eb141f2,
0x515f007c,
0x12200854,
0x1190cde7,
0x140e0f76,
0xded7263,
0x41a7c4c9,
0x25e45d32,
0x3f2dba31,
0x436c6125,
0x333ab105,
0x2d1d5ae9,
0x8edbdab,
0xb03e0c6,
0x2ca88611,
0x2901d82,
0x1e7ff521,
0x22221a70,
0x3006c83e,
0x440badfc,
0x3804823e,
0x2463b9ea,
0x2d517796,
0x153ea438,
0x2a487cb0,
0x2cd89a32,
0x4b588f54,
0x38437fdb,
0x32fff902,
0x3dc240fb,
0x75c6c33a,
0x520eedd1,
0x23f9c13c,
0x275ac794,
0x180115be,
0x15b5af5c,
0xd34b6a8,
0x61574095,
0x310c50b3,
0x25a70bf7,
0x1f48eaa1,
0x100f8fca,
0x15014acb,
0x6b94764,
0x168e121f,
0x540a471c,
};
int max_exp[] = {
0x6b8b4567,
0x74b0dc51,
0x625558ec,
0x46e87ccd,
0x41b71efb,
0x7545e146,
0x4db127f8,
0x1f16e9e8,
0x3352255a,
0x3e4ccccd,
0x6b68079a,
0x519b500d,
0x7c83e458,
0x62bbd95a,
0x721da317,
0x6763845e,
0x79838cb2,
0x189a769b,
0x71f32454,
0x3a95f874,
0x7c3dbd3d,
0x6ceaf087,
0x614fd4a1,
0x5577f8e1,
0x77465f01,
0x5c482a97,
0x51ead36b,
0x3855585c,
0x6a2342ec,
0x725a06fb,
0x7a6d8d3c,
0x6de91b18,
0x684a481a,
0x749abb43,
0x79a1deaa,
0x70c6a529,
0x4f4ef005,
0x39386575,
0x235ba861,
0x354fe9f9,
0x10233c99,
0x7e0c57b1,
0x579be4f1,
0x2f305def,
0x4ad084e9,
0x5db70ae5,
0x5f5e7fd0,
0x799d0247,
0x1eba5d23,
0x5dc79ea8,
};
int sqrt_exp[] = {
0x55858444,
0x52d63c0d,
0x352c8a4f,
0x432c8198,
0x3716a0eb,
0x5a61125b,
0x28ca6806,
0x2f448e1b,
0x29beb3da,
0x26ae5621,
0x40928a9c,
0x32aaf836,
0x3f52e399,
0x511b103f,
0x395a9dbc,
0x3648b4be,
0x242e71c1,
0x2537bdb5,
0x58b06a2d,
0x2107d19f,
0x2efffa90,
0x562d69df,
0x37b9c0d0,
0x4a7bf441,
0x3bb82e0f,
0x4de25e46,
0x48ad5f21,
0x2a5ceab1,
0x54cc7025,
0x58ec407f,
0x5cf69a78,
0x56acbc49,
0x3935027a,
0x5a0cbb84,
0x5c8ff12e,
0x581f7507,
0x47662a4b,
0x336ca8c1,
0x2bb5c8ee,
0x3a66b522,
0x2657166a,
0x506abe60,
0x4b8d42a3,
0x37547c32,
0x45235f44,
0x4e99111a,
0x2a35ee45,
0x5c8dc3ae,
0x2b06da1c,
0x4e9fd90b,
};
int mul_exp[] = {
0x5e88a082,
0x7f800000,
0x4dc1d42b,
0x448d1424,
0x30fd972f,
0x7f800000,
0x205d7d7d,
0x0,
0x7e93ad2,
0xcbdf51c,
0x6d980f51,
0x380a8bd6,
0x7c330279,
0x66ad73a7,
0x65e5eaff,
0x550bd8f9,
0x42f4556f,
0x0,
0x5f200f2c,
0x2a368,
0x5b3db52e,
0x4f94c479,
0x51dad7b9,
0x5a074ca9,
0x6fcd5bd2,
0x41320f22,
0x3fc0244c,
0xe1ee070,
0x54ffb79a,
0x5fb87937,
0x7f800000,
0x66b2040f,
0x5bca4294,
0x72ead25f,
0x7f800000,
0x7f800000,
0x33c9e3a8,
0x211d9627,
0x3761,
0xb938ed9,
0x0,
0x7f800000,
0x492ae4b1,
0x15662b0a,
0x2aa3a6f3,
0x2e4d4bcb,
0x34e0bed2,
0x40e344dd,
0x3,
0x7257a5f3,
};
int div_exp[] = {
0x788df765,
0x3101c0d0,
0x80b89d4,
0x493f8fb4,
0x2c77cd94,
0x63632926,
0x3e74168,
0x4d056681,
0x202d0ee3,
0xf14677e,
0x15b919b3,
0x13bc346f,
0x22899d0,
0x5ecb70fa,
0x97978a,
0x5310df1,
0x0,
0x31da9179,
0x7f800000,
0x776014c,
0x0,
0x7f800000,
0xe260561,
0x50e33cc8,
0x558081,
0x776104b5,
0x640f7efe,
0x1c64c1d1,
0x7f507789,
0x7f800000,
0x6e8c684e,
0x75189f46,
0xa21f984,
0x764bea3b,
0x43507bb3,
0x5e31e589,
0x6ad41cb3,
0x2d97de0e,
0x34167125,
0x5f127a8e,
0x3c8db447,
0x22c4525d,
0x660e3633,
0x49072441,
0x6b04d7f0,
0x7f800000,
0x1,
0x7f800000,
0x37432814,
0x4938c859,
};
int madd_exp[] = {
0x643ca97d,
0x7f800000,
0x4dc1d42b,
0x507ed7ac,
0x79e2a9e3,
0x7f800000,
0x205d7d7d,
0x66ef438d,
0x109cf968,
0x1befd79f,
0x6d980f51,
0x431bd7b9,
0x7c330279,
0x66ae0031,
0x65e5eaff,
0x75a2a8d4,
0x43a6fdc2,
0x54e49eb4,
0x5f200f2c,
0x8138646,
0x737b8ddc,
0x4f94c47d,
0x51dad7b9,
0x5a074ca9,
0x7724c819,
0x5e884adc,
0x580bd78f,
0x70a64e2a,
0x54ffb79a,
0x5fb87a1b,
0x7f800000,
0x7644a45c,
0x5bcad70d,
0x72ead25f,
0x7f800000,
0x7f800000,
0x649bb77c,
0x211e0eaf,
0x47398c89,
0x741226bb,
0x3f6ab60f,
0x7f800000,
0x5ff87e05,
0x1dbabf73,
0x2aa3a6f3,
0x6590700b,
0x34e0bed2,
0x42d0cb0b,
0x661e3f1e,
0x7bd3ee96,
};
int eq_exp[] = {
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
};
int lt_exp[] = {
0x0,
0x1,
0x1,
0x0,
0x1,
0x0,
0x1,
0x0,
0x1,
0x1,
0x1,
0x1,
0x1,
0x0,
0x1,
0x1,
0x1,
0x1,
0x0,
0x1,
0x1,
0x0,
0x1,
0x0,
0x1,
0x0,
0x0,
0x1,
0x0,
0x0,
0x0,
0x0,
0x1,
0x0,
0x0,
0x0,
0x0,
0x1,
0x1,
0x0,
0x1,
0x1,
0x0,
0x0,
0x0,
0x0,
0x1,
0x0,
0x1,
0x0,
};
int le_exp[] = {
0x0,
0x1,
0x1,
0x0,
0x1,
0x0,
0x1,
0x0,
0x1,
0x1,
0x1,
0x1,
0x1,
0x0,
0x1,
0x1,
0x1,
0x1,
0x0,
0x1,
0x1,
0x0,
0x1,
0x0,
0x1,
0x0,
0x0,
0x1,
0x0,
0x0,
0x0,
0x0,
0x1,
0x0,
0x0,
0x0,
0x0,
0x1,
0x1,
0x0,
0x1,
0x1,
0x0,
0x0,
0x0,
0x0,
0x1,
0x0,
0x1,
0x0,
};
int add_act[] = {
0x6b8b4567,
0x66334873,
0x2ae8944a,
0x46e87ccd,
0x2eb141f2,
0x7545e146,
0x12200854,
0x1f16e9e8,
0x140e0f76,
0xded7263,
0x41a7c4c9,
0x25e45d32,
0x3f2dba31,
0x62bbd95a,
0x333ab105,
0x2d1d5ae9,
0x8edbdab,
0xb03e0c6,
0x71f32454,
0x2901d82,
0x1e7ff521,
0x6ceaf087,
0x3006c83e,
0x5577f8e1,
0x3804823e,
0x5c482a97,
0x51ead36b,
0x153ea438,
0x6a2342ec,
0x725a06fb,
0x7a6d8d3c,
0x6de91b18,
0x32fff902,
0x749abb43,
0x79a1deaa,
0x70c6a529,
0x4f4ef005,
0x275ac794,
0x180115be,
0x354fe9f9,
0xd34b6a8,
0x61574095,
0x579be4f1,
0x2f305def,
0x4ad084e9,
0x5db70ae5,
0x15014acb,
0x799d0247,
0x168e121f,
0x5dc79ea8,
};
int sub_act[] = {
0x6b8b4567,
0x66334873,
0x2ae8944a,
0x46e87ccd,
0x2eb141f2,
0x7545e146,
0x12200854,
0x1f16e9e8,
0x140e0f76,
0xded7263,
0x41a7c4c9,
0x25e45d32,
0x3f2dba31,
0x62bbd95a,
0x333ab105,
0x2d1d5ae9,
0x8edbdab,
0xb03e0c6,
0x71f32454,
0x2901d82,
0x1e7ff521,
0x6ceaf087,
0x3006c83e,
0x5577f8e1,
0x3804823e,
0x5c482a97,
0x51ead36b,
0x153ea438,
0x6a2342ec,
0x725a06fb,
0x7a6d8d3c,
0x6de91b18,
0x32fff902,
0x749abb43,
0x79a1deaa,
0x70c6a529,
0x4f4ef005,
0x275ac794,
0x180115be,
0x354fe9f9,
0xd34b6a8,
0x61574095,
0x579be4f1,
0x2f305def,
0x4ad084e9,
0x5db70ae5,
0x15014acb,
0x799d0247,
0x168e121f,
0x5dc79ea8,
};
int min_act[] = {
0x6b8b4567,
0x66334873,
0x2ae8944a,
0x46e87ccd,
0x2eb141f2,
0x7545e146,
0x12200854,
0x1f16e9e8,
0x140e0f76,
0xded7263,
0x41a7c4c9,
0x25e45d32,
0x3f2dba31,
0x62bbd95a,
0x333ab105,
0x2d1d5ae9,
0x8edbdab,
0xb03e0c6,
0x71f32454,
0x2901d82,
0x1e7ff521,
0x6ceaf087,
0x3006c83e,
0x5577f8e1,
0x3804823e,
0x5c482a97,
0x51ead36b,
0x153ea438,
0x6a2342ec,
0x725a06fb,
0x7a6d8d3c,
0x6de91b18,
0x32fff902,
0x749abb43,
0x79a1deaa,
0x70c6a529,
0x4f4ef005,
0x275ac794,
0x180115be,
0x354fe9f9,
0xd34b6a8,
0x61574095,
0x579be4f1,
0x2f305def,
0x4ad084e9,
0x5db70ae5,
0x15014acb,
0x799d0247,
0x168e121f,
0x5dc79ea8,
};
int max_act[] = {
0x6b8b4567,
0x66334873,
0x2ae8944a,
0x46e87ccd,
0x2eb141f2,
0x7545e146,
0x12200854,
0x1f16e9e8,
0x140e0f76,
0xded7263,
0x41a7c4c9,
0x25e45d32,
0x3f2dba31,
0x62bbd95a,
0x333ab105,
0x2d1d5ae9,
0x8edbdab,
0xb03e0c6,
0x71f32454,
0x2901d82,
0x1e7ff521,
0x6ceaf087,
0x3006c83e,
0x5577f8e1,
0x3804823e,
0x5c482a97,
0x51ead36b,
0x153ea438,
0x6a2342ec,
0x725a06fb,
0x7a6d8d3c,
0x6de91b18,
0x32fff902,
0x749abb43,
0x79a1deaa,
0x70c6a529,
0x4f4ef005,
0x275ac794,
0x180115be,
0x354fe9f9,
0xd34b6a8,
0x61574095,
0x579be4f1,
0x2f305def,
0x4ad084e9,
0x5db70ae5,
0x15014acb,
0x799d0247,
0x168e121f,
0x5dc79ea8,
};
int sqrt_act[] = {
0x6b8b4567,
0x66334873,
0x2ae8944a,
0x46e87ccd,
0x2eb141f2,
0x7545e146,
0x12200854,
0x1f16e9e8,
0x140e0f76,
0xded7263,
0x41a7c4c9,
0x25e45d32,
0x3f2dba31,
0x62bbd95a,
0x333ab105,
0x2d1d5ae9,
0x8edbdab,
0xb03e0c6,
0x71f32454,
0x2901d82,
0x1e7ff521,
0x6ceaf087,
0x3006c83e,
0x5577f8e1,
0x3804823e,
0x5c482a97,
0x51ead36b,
0x153ea438,
0x6a2342ec,
0x725a06fb,
0x7a6d8d3c,
0x6de91b18,
0x32fff902,
0x749abb43,
0x79a1deaa,
0x70c6a529,
0x4f4ef005,
0x275ac794,
0x180115be,
0x354fe9f9,
0xd34b6a8,
0x61574095,
0x579be4f1,
0x2f305def,
0x4ad084e9,
0x5db70ae5,
0x15014acb,
0x799d0247,
0x168e121f,
0x5dc79ea8,
};
int mul_act[] = {
0x6b8b4567,
0x66334873,
0x2ae8944a,
0x46e87ccd,
0x2eb141f2,
0x7545e146,
0x12200854,
0x1f16e9e8,
0x140e0f76,
0xded7263,
0x41a7c4c9,
0x25e45d32,
0x3f2dba31,
0x62bbd95a,
0x333ab105,
0x2d1d5ae9,
0x8edbdab,
0xb03e0c6,
0x71f32454,
0x2901d82,
0x1e7ff521,
0x6ceaf087,
0x3006c83e,
0x5577f8e1,
0x3804823e,
0x5c482a97,
0x51ead36b,
0x153ea438,
0x6a2342ec,
0x725a06fb,
0x7a6d8d3c,
0x6de91b18,
0x32fff902,
0x749abb43,
0x79a1deaa,
0x70c6a529,
0x4f4ef005,
0x275ac794,
0x180115be,
0x354fe9f9,
0xd34b6a8,
0x61574095,
0x579be4f1,
0x2f305def,
0x4ad084e9,
0x5db70ae5,
0x15014acb,
0x799d0247,
0x168e121f,
0x5dc79ea8,
};
int div_act[] = {
0x6b8b4567,
0x66334873,
0x2ae8944a,
0x46e87ccd,
0x2eb141f2,
0x7545e146,
0x12200854,
0x1f16e9e8,
0x140e0f76,
0xded7263,
0x41a7c4c9,
0x25e45d32,
0x3f2dba31,
0x62bbd95a,
0x333ab105,
0x2d1d5ae9,
0x8edbdab,
0xb03e0c6,
0x71f32454,
0x2901d82,
0x1e7ff521,
0x6ceaf087,
0x3006c83e,
0x5577f8e1,
0x3804823e,
0x5c482a97,
0x51ead36b,
0x153ea438,
0x6a2342ec,
0x725a06fb,
0x7a6d8d3c,
0x6de91b18,
0x32fff902,
0x749abb43,
0x79a1deaa,
0x70c6a529,
0x4f4ef005,
0x275ac794,
0x180115be,
0x354fe9f9,
0xd34b6a8,
0x61574095,
0x579be4f1,
0x2f305def,
0x4ad084e9,
0x5db70ae5,
0x15014acb,
0x799d0247,
0x168e121f,
0x5dc79ea8,
};
int madd_act[] = {
0x6b8b4567,
0x66334873,
0x2ae8944a,
0x46e87ccd,
0x2eb141f2,
0x7545e146,
0x12200854,
0x1f16e9e8,
0x140e0f76,
0xded7263,
0x41a7c4c9,
0x25e45d32,
0x3f2dba31,
0x62bbd95a,
0x333ab105,
0x2d1d5ae9,
0x8edbdab,
0xb03e0c6,
0x71f32454,
0x2901d82,
0x1e7ff521,
0x6ceaf087,
0x3006c83e,
0x5577f8e1,
0x3804823e,
0x5c482a97,
0x51ead36b,
0x153ea438,
0x6a2342ec,
0x725a06fb,
0x7a6d8d3c,
0x6de91b18,
0x32fff902,
0x749abb43,
0x79a1deaa,
0x70c6a529,
0x4f4ef005,
0x275ac794,
0x180115be,
0x354fe9f9,
0xd34b6a8,
0x61574095,
0x579be4f1,
0x2f305def,
0x4ad084e9,
0x5db70ae5,
0x15014acb,
0x799d0247,
0x168e121f,
0x5dc79ea8,
};
int eq_act[] = {
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
};
int lt_act[] = {
0x0,
0x1,
0x1,
0x0,
0x1,
0x0,
0x1,
0x0,
0x1,
0x1,
0x1,
0x1,
0x1,
0x0,
0x1,
0x1,
0x1,
0x1,
0x0,
0x1,
0x1,
0x0,
0x1,
0x0,
0x1,
0x0,
0x0,
0x1,
0x0,
0x0,
0x0,
0x0,
0x1,
0x0,
0x0,
0x0,
0x0,
0x1,
0x1,
0x0,
0x1,
0x1,
0x0,
0x0,
0x0,
0x0,
0x1,
0x0,
0x1,
0x0,
};
int le_act[] = {
0x0,
0x1,
0x1,
0x0,
0x1,
0x0,
0x1,
0x0,
0x1,
0x1,
0x1,
0x1,
0x1,
0x0,
0x1,
0x1,
0x1,
0x1,
0x0,
0x1,
0x1,
0x0,
0x1,
0x0,
0x1,
0x0,
0x0,
0x1,
0x0,
0x0,
0x0,
0x0,
0x1,
0x0,
0x0,
0x0,
0x0,
0x1,
0x1,
0x0,
0x1,
0x1,
0x0,
0x0,
0x0,
0x0,
0x1,
0x0,
0x1,
0x0,
};

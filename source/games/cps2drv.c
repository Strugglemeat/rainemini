#define DRV_DEF_LOAD load_cps2
#define DRV_DEF_VIDEO &video_cps1
#define DRV_DEF_EXEC execute_cps2_frame
#define DRV_DEF_SOUND sound_qsound
#define DRV_DEF_INPUT input_p2b6
#define DRV_DEF_DSW NULL
#define DRV_DEF_CLEAR clear_cps2
/* cps2 drivers, see cps1.c for the code (VERY similar to cps1) */

#include "gameinc.h"
#include "cps1.h"
#include "sound/adpcm.h"
#include "sound/sasound.h"

static struct ROM_INFO rom_1944[] =
{
  LOAD_SW16( CPU1, "nffu.03", 0x000000, 0x80000, 0x9693cf8f),
  LOAD_SW16( CPU1, "nff.04", 0x080000, 0x80000, 0xdba1c66e),
  LOAD_SW16( CPU1, "nffu.05", 0x100000, 0x80000, 0xea813eb7),
  { "nff.13m", 0x400000, 0xc9fca741, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "nff.15m", 0x400000, 0xf809d898, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "nff.17m", 0x400000, 0x15ba4507, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "nff.19m", 0x400000, 0x3dd41b8c, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "nff.14m", 0x100000, 0x3fe3a54b, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "nff.16m", 0x100000, 0x565cd231, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "nff.18m", 0x100000, 0x63ca5988, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "nff.20m", 0x100000, 0x21eb8f3b, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "nff.01", 0x00000, 0x20000, 0xd2e44318),
  LOAD_SW16( SMP1, "nff.11m", 0x000000, 0x400000, 0x243e4e05),
  LOAD_SW16( SMP1, "nff.12m", 0x400000, 0x400000, 0x4fcf1600),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_1944j[] = // clone of 1944
{
  LOAD_SW16( CPU1, "nffj.03", 0x000000, 0x80000, 0x247521ef),
  LOAD_SW16( CPU1, "nff.04", 0x080000, 0x80000, 0xdba1c66e),
  LOAD_SW16( CPU1, "nffj.05", 0x100000, 0x80000, 0x7f20c2ef),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_19xx[] =
{
  LOAD_SW16( CPU1, "19xu.03", 0x000000, 0x80000, 0x05955268),
  LOAD_SW16( CPU1, "19xu.04", 0x080000, 0x80000, 0x3111ab7f),
  LOAD_SW16( CPU1, "19xu.05", 0x100000, 0x80000, 0x38df4a63),
  LOAD_SW16( CPU1, "19xu.06", 0x180000, 0x80000, 0x5c7e60d3),
  LOAD_SW16( CPU1, "19x.07", 0x200000, 0x80000, 0x61c0296c),
  { "19x.13m", 0x080000, 0x427aeb18, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "19x.15m", 0x080000, 0x63bdbf54, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "19x.17m", 0x080000, 0x2dfe18b5, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "19x.19m", 0x080000, 0xcbef9579, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "19x.14m", 0x200000, 0xe916967c, REGION_GFX1, 0x0800000, LOAD_16_64 },
  { "19x.16m", 0x200000, 0x6e75f3db, REGION_GFX1, 0x0800002, LOAD_16_64 },
  { "19x.18m", 0x200000, 0x2213e798, REGION_GFX1, 0x0800004, LOAD_16_64 },
  { "19x.20m", 0x200000, 0xab9d5b96, REGION_GFX1, 0x0800006, LOAD_16_64 },
  LOAD( ROM2, "19x.01", 0x00000, 0x20000, 0xef55195e),
  LOAD_SW16( SMP1, "19x.11m", 0x000000, 0x200000, 0xd38beef3),
  LOAD_SW16( SMP1, "19x.12m", 0x200000, 0x200000, 0xd47c96e2),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_19xxj[] = // clone of 19xx
{
  LOAD_SW16( CPU1, "19xj.03a", 0x000000, 0x80000, 0xed08bdd1),
  LOAD_SW16( CPU1, "19xj.04a", 0x080000, 0x80000, 0xfb8e3f29),
  LOAD_SW16( CPU1, "19xj.05a", 0x100000, 0x80000, 0xaa508ac4),
  LOAD_SW16( CPU1, "19xj.06a", 0x180000, 0x80000, 0xff2d785b),
  LOAD_SW16( CPU1, "19x.07", 0x200000, 0x80000, 0x61c0296c),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_19xxjr1[] = // clone of 19xx
{
  LOAD_SW16( CPU1, "19xj.03", 0x000000, 0x80000, 0x26a381ed),
  LOAD_SW16( CPU1, "19xj.04", 0x080000, 0x80000, 0x30100cca),
  LOAD_SW16( CPU1, "19xj.05", 0x100000, 0x80000, 0xde67e938),
  LOAD_SW16( CPU1, "19xj.06", 0x180000, 0x80000, 0x39f9a409),
  LOAD_SW16( CPU1, "19x.07", 0x200000, 0x80000, 0x61c0296c),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_19xxa[] = // clone of 19xx
{
  LOAD_SW16( CPU1, "19xa.03", 0x000000, 0x80000, 0x0c20fd50),
  LOAD_SW16( CPU1, "19xa.04", 0x080000, 0x80000, 0x1fc37508),
  LOAD_SW16( CPU1, "19xa.05", 0x100000, 0x80000, 0x6c9cc4ed),
  LOAD_SW16( CPU1, "19xa.06", 0x180000, 0x80000, 0xca5b9f76),
  LOAD_SW16( CPU1, "19x.07", 0x200000, 0x80000, 0x61c0296c),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_19xxh[] = // clone of 19xx
{
  LOAD_SW16( CPU1, "19xh.03a", 0x000000, 0x80000, 0x357be2ac),
  LOAD_SW16( CPU1, "19xh.04a", 0x080000, 0x80000, 0xbb13ea3b),
  LOAD_SW16( CPU1, "19xh.05a", 0x100000, 0x80000, 0xcbd76601),
  LOAD_SW16( CPU1, "19xh.06a", 0x180000, 0x80000, 0xb362de8b),
  LOAD_SW16( CPU1, "19x.07", 0x200000, 0x80000, 0x61c0296c),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_19xxb[] = // clone of 19xx
{
  LOAD_SW16( CPU1, "19xb.03a", 0x000000, 0x80000, 0x341bdf4a),
  LOAD_SW16( CPU1, "19xb.04a", 0x080000, 0x80000, 0xdff8069e),
  LOAD_SW16( CPU1, "19xb.05a", 0x100000, 0x80000, 0xa47a92a8),
  LOAD_SW16( CPU1, "19xb.06a", 0x180000, 0x80000, 0xc52df10d),
  LOAD_SW16( CPU1, "19x.07", 0x200000, 0x80000, 0x61c0296c),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_armwar[] =
{
  LOAD_SW16( CPU1, "pwge.03c", 0x000000, 0x80000, 0x31f74931),
  LOAD_SW16( CPU1, "pwge.04c", 0x080000, 0x80000, 0x16f34f5f),
  LOAD_SW16( CPU1, "pwge.05b", 0x100000, 0x80000, 0x4403ed08),
  LOAD_SW16( CPU1, "pwg.06", 0x180000, 0x80000, 0x87a60ce8),
  LOAD_SW16( CPU1, "pwg.07", 0x200000, 0x80000, 0xf7b148df),
  LOAD_SW16( CPU1, "pwg.08", 0x280000, 0x80000, 0xcc62823e),
  LOAD_SW16( CPU1, "pwg.09a", 0x300000, 0x80000, 0x4c26baee),
  LOAD_SW16( CPU1, "pwg.10", 0x380000, 0x80000, 0x07c4fb28),
  { "pwg.13m", 0x400000, 0xae8fe08e, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "pwg.15m", 0x400000, 0xdb560f58, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "pwg.17m", 0x400000, 0xbc475b94, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "pwg.19m", 0x400000, 0x07439ff7, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "pwg.14m", 0x100000, 0xc3f9ba63, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "pwg.16m", 0x100000, 0x815b0e7b, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "pwg.18m", 0x100000, 0x0109c71b, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "pwg.20m", 0x100000, 0xeb75ffbe, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "pwg.01", 0x00000, 0x20000, 0x18a5c0e4),
  LOAD( ROM2, "pwg.02", 0x20000, 0x20000, 0xc9dfffa6),
  LOAD_SW16( SMP1, "pwg.11m", 0x000000, 0x200000, 0xa78f7433),
  LOAD_SW16( SMP1, "pwg.12m", 0x200000, 0x200000, 0x77438ed0),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_armwarr1[] = // clone of armwar
{
  LOAD_SW16( CPU1, "pwge.03b", 0x000000, 0x80000, 0xe822e3e9),
  LOAD_SW16( CPU1, "pwge.04b", 0x080000, 0x80000, 0x4f89de39),
  LOAD_SW16( CPU1, "pwge.05a", 0x100000, 0x80000, 0x83df24e5),
  LOAD_SW16( CPU1, "pwg.06", 0x180000, 0x80000, 0x87a60ce8),
  LOAD_SW16( CPU1, "pwg.07", 0x200000, 0x80000, 0xf7b148df),
  LOAD_SW16( CPU1, "pwg.08", 0x280000, 0x80000, 0xcc62823e),
  LOAD_SW16( CPU1, "pwg.09", 0x300000, 0x80000, 0xddc85ca6),
  LOAD_SW16( CPU1, "pwg.10", 0x380000, 0x80000, 0x07c4fb28),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_armwaru[] = // clone of armwar
{
  LOAD_SW16( CPU1, "pwgu.03b", 0x000000, 0x80000, 0x8b95497a),
  LOAD_SW16( CPU1, "pwgu.04b", 0x080000, 0x80000, 0x29eb5661),
  LOAD_SW16( CPU1, "pwgu.05b", 0x100000, 0x80000, 0xa54e9e44),
  LOAD_SW16( CPU1, "pwg.06", 0x180000, 0x80000, 0x87a60ce8),
  LOAD_SW16( CPU1, "pwg.07", 0x200000, 0x80000, 0xf7b148df),
  LOAD_SW16( CPU1, "pwg.08", 0x280000, 0x80000, 0xcc62823e),
  LOAD_SW16( CPU1, "pwg.09a", 0x300000, 0x80000, 0x4c26baee),
  LOAD_SW16( CPU1, "pwg.10", 0x380000, 0x80000, 0x07c4fb28),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_armwaru1[] = // clone of armwar
{
  LOAD_SW16( CPU1, "pwgu.03a", 0x000000, 0x80000, 0x73d397b1),
  LOAD_SW16( CPU1, "pwgu.04a", 0x080000, 0x80000, 0x1f1de215),
  LOAD_SW16( CPU1, "pwgu.05a", 0x100000, 0x80000, 0x835fbe73),
  LOAD_SW16( CPU1, "pwg.06", 0x180000, 0x80000, 0x87a60ce8),
  LOAD_SW16( CPU1, "pwg.07", 0x200000, 0x80000, 0xf7b148df),
  LOAD_SW16( CPU1, "pwg.08", 0x280000, 0x80000, 0xcc62823e),
  LOAD_SW16( CPU1, "pwg.09", 0x300000, 0x80000, 0xddc85ca6),
  LOAD_SW16( CPU1, "pwg.10", 0x380000, 0x80000, 0x07c4fb28),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_pgear[] = // clone of armwar
{
  LOAD_SW16( CPU1, "pwgj.03a", 0x000000, 0x80000, 0xc79c0c02),
  LOAD_SW16( CPU1, "pwgj.04a", 0x080000, 0x80000, 0x167c6ed8),
  LOAD_SW16( CPU1, "pwgj.05a", 0x100000, 0x80000, 0xa63fb400),
  LOAD_SW16( CPU1, "pwg.06", 0x180000, 0x80000, 0x87a60ce8),
  LOAD_SW16( CPU1, "pwg.07", 0x200000, 0x80000, 0xf7b148df),
  LOAD_SW16( CPU1, "pwg.08", 0x280000, 0x80000, 0xcc62823e),
  LOAD_SW16( CPU1, "pwg.09a", 0x300000, 0x80000, 0x4c26baee),
  LOAD_SW16( CPU1, "pwg.10", 0x380000, 0x80000, 0x07c4fb28),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_pgearr1[] = // clone of armwar
{
  LOAD_SW16( CPU1, "pwgj.03", 0x000000, 0x80000, 0xf264e74b),
  LOAD_SW16( CPU1, "pwgj.04", 0x080000, 0x80000, 0x23a84983),
  LOAD_SW16( CPU1, "pwgj.05", 0x100000, 0x80000, 0xbef58c62),
  LOAD_SW16( CPU1, "pwg.06", 0x180000, 0x80000, 0x87a60ce8),
  LOAD_SW16( CPU1, "pwg.07", 0x200000, 0x80000, 0xf7b148df),
  LOAD_SW16( CPU1, "pwg.08", 0x280000, 0x80000, 0xcc62823e),
  LOAD_SW16( CPU1, "pwg.09", 0x300000, 0x80000, 0xddc85ca6),
  LOAD_SW16( CPU1, "pwg.10", 0x380000, 0x80000, 0x07c4fb28),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_armwara[] = // clone of armwar
{
  LOAD_SW16( CPU1, "pwga.03a", 0x000000, 0x80000, 0x8d474ab1),
  LOAD_SW16( CPU1, "pwga.04a", 0x080000, 0x80000, 0x81b5aec7),
  LOAD_SW16( CPU1, "pwga.05a", 0x100000, 0x80000, 0x2618e819),
  LOAD_SW16( CPU1, "pwg.06", 0x180000, 0x80000, 0x87a60ce8),
  LOAD_SW16( CPU1, "pwg.07", 0x200000, 0x80000, 0xf7b148df),
  LOAD_SW16( CPU1, "pwg.08", 0x280000, 0x80000, 0xcc62823e),
  LOAD_SW16( CPU1, "pwg.09", 0x300000, 0x80000, 0xddc85ca6),
  LOAD_SW16( CPU1, "pwg.10", 0x380000, 0x80000, 0x07c4fb28),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_avsp[] =
{
  LOAD_SW16( CPU1, "avpe.03d", 0x000000, 0x80000, 0x774334a9),
  LOAD_SW16( CPU1, "avpe.04d", 0x080000, 0x80000, 0x7fa83769),
  LOAD_SW16( CPU1, "avp.05d", 0x100000, 0x80000, 0xfbfb5d7a),
  LOAD_SW16( CPU1, "avp.06", 0x180000, 0x80000, 0x190b817f),
  { "avp.13m", 0x200000, 0x8f8b5ae4, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "avp.15m", 0x200000, 0xb00280df, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "avp.17m", 0x200000, 0x94403195, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "avp.19m", 0x200000, 0xe1981245, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "avp.14m", 0x200000, 0xebba093e, REGION_GFX1, 0x0800000, LOAD_16_64 },
  { "avp.16m", 0x200000, 0xfb228297, REGION_GFX1, 0x0800002, LOAD_16_64 },
  { "avp.18m", 0x200000, 0x34fb7232, REGION_GFX1, 0x0800004, LOAD_16_64 },
  { "avp.20m", 0x200000, 0xf90baa21, REGION_GFX1, 0x0800006, LOAD_16_64 },
  LOAD( ROM2, "avp.01", 0x00000, 0x20000, 0x2d3b4220),
  LOAD_SW16( SMP1, "avp.11m", 0x000000, 0x200000, 0x83499817),
  LOAD_SW16( SMP1, "avp.12m", 0x200000, 0x200000, 0xf4110d49),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_avspu[] = // clone of avsp
{
  LOAD_SW16( CPU1, "avpu.03d", 0x000000, 0x80000, 0x42757950),
  LOAD_SW16( CPU1, "avpu.04d", 0x080000, 0x80000, 0x5abcdee6),
  LOAD_SW16( CPU1, "avp.05d", 0x100000, 0x80000, 0xfbfb5d7a),
  LOAD_SW16( CPU1, "avp.06", 0x180000, 0x80000, 0x190b817f),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_avspj[] = // clone of avsp
{
  LOAD_SW16( CPU1, "avpj.03d", 0x000000, 0x80000, 0x49799119),
  LOAD_SW16( CPU1, "avpj.04d", 0x080000, 0x80000, 0x8cd2bba8),
  LOAD_SW16( CPU1, "avp.05d", 0x100000, 0x80000, 0xfbfb5d7a),
  LOAD_SW16( CPU1, "avp.06", 0x180000, 0x80000, 0x190b817f),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_avspa[] = // clone of avsp
{
  LOAD_SW16( CPU1, "avpa.03d", 0x000000, 0x80000, 0x6c1c1858),
  LOAD_SW16( CPU1, "avpa.04d", 0x080000, 0x80000, 0x94f50b0c),
  LOAD_SW16( CPU1, "avp.05d", 0x100000, 0x80000, 0xfbfb5d7a),
  LOAD_SW16( CPU1, "avp.06", 0x180000, 0x80000, 0x190b817f),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_avsph[] = // clone of avsp
{
  LOAD_SW16( CPU1, "avph.03d", 0x000000, 0x80000, 0x3e440447),
  LOAD_SW16( CPU1, "avph.04d", 0x080000, 0x80000, 0xaf6fc82f),
  LOAD_SW16( CPU1, "avp.05d", 0x100000, 0x80000, 0xfbfb5d7a),
  LOAD_SW16( CPU1, "avp.06", 0x180000, 0x80000, 0x190b817f),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_batcir[] =
{
  LOAD_SW16( CPU1, "btce.03", 0x000000, 0x80000, 0xbc60484b),
  LOAD_SW16( CPU1, "btce.04", 0x080000, 0x80000, 0x457d55f6),
  LOAD_SW16( CPU1, "btce.05", 0x100000, 0x80000, 0xe86560d7),
  LOAD_SW16( CPU1, "btce.06", 0x180000, 0x80000, 0xf778e61b),
  LOAD_SW16( CPU1, "btc.07", 0x200000, 0x80000, 0x7322d5db),
  LOAD_SW16( CPU1, "btc.08", 0x280000, 0x80000, 0x6aac85ab),
  LOAD_SW16( CPU1, "btc.09", 0x300000, 0x80000, 0x1203db08),
  { "btc.13m", 0x400000, 0xdc705bad, REGION_GFX1, 0x000000, LOAD_16_64 },
  { "btc.15m", 0x400000, 0xe5779a3c, REGION_GFX1, 0x000002, LOAD_16_64 },
  { "btc.17m", 0x400000, 0xb33f4112, REGION_GFX1, 0x000004, LOAD_16_64 },
  { "btc.19m", 0x400000, 0xa6fcdb7e, REGION_GFX1, 0x000006, LOAD_16_64 },
  LOAD( ROM2, "btc.01", 0x00000, 0x20000, 0x1e194310),
  LOAD( ROM2, "btc.02", 0x20000, 0x20000, 0x01aeb8e6),
  LOAD_SW16( SMP1, "btc.11m", 0x000000, 0x200000, 0xc27f2229),
  LOAD_SW16( SMP1, "btc.12m", 0x200000, 0x200000, 0x418a2e33),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_batcirj[] = // clone of batcir
{
  LOAD_SW16( CPU1, "btcj.03", 0x000000, 0x80000, 0x6b7e168d),
  LOAD_SW16( CPU1, "btcj.04", 0x080000, 0x80000, 0x46ba3467),
  LOAD_SW16( CPU1, "btcj.05", 0x100000, 0x80000, 0x0e23a859),
  LOAD_SW16( CPU1, "btcj.06", 0x180000, 0x80000, 0xa853b59c),
  LOAD_SW16( CPU1, "btc.07", 0x200000, 0x80000, 0x7322d5db),
  LOAD_SW16( CPU1, "btc.08", 0x280000, 0x80000, 0x6aac85ab),
  LOAD_SW16( CPU1, "btc.09", 0x300000, 0x80000, 0x1203db08),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_batcira[] = // clone of batcir
{
  LOAD_SW16( CPU1, "btca.03", 0x000000, 0x80000, 0x1ad20d87),
  LOAD_SW16( CPU1, "btca.04", 0x080000, 0x80000, 0x2b3f4dbe),
  LOAD_SW16( CPU1, "btca.05", 0x100000, 0x80000, 0x8238a3d9),
  LOAD_SW16( CPU1, "btca.06", 0x180000, 0x80000, 0x446c7c02),
  LOAD_SW16( CPU1, "btc.07", 0x200000, 0x80000, 0x7322d5db),
  LOAD_SW16( CPU1, "btc.08", 0x280000, 0x80000, 0x6aac85ab),
  LOAD_SW16( CPU1, "btc.09", 0x300000, 0x80000, 0x1203db08),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_choko[] =
{
  LOAD_SW16( CPU1, "tkoj.03", 0x000000, 0x80000, 0x11f5452f),
  LOAD_SW16( CPU1, "tkoj.04", 0x080000, 0x80000, 0x68655378),
  { "tkoj1_d.simm1", 0x200000, 0x6933377d, REGION_GFX1, 0x0000000, LOAD_8_64 },
  { "tkoj1_c.simm1", 0x200000, 0x7f668950, REGION_GFX1, 0x0000001, LOAD_8_64 },
  { "tkoj1_b.simm1", 0x200000, 0xcfb68ca9, REGION_GFX1, 0x0000002, LOAD_8_64 },
  { "tkoj1_a.simm1", 0x200000, 0x437e21c5, REGION_GFX1, 0x0000003, LOAD_8_64 },
  { "tkoj3_d.simm3", 0x200000, 0xa9e32b57, REGION_GFX1, 0x0000004, LOAD_8_64 },
  { "tkoj3_c.simm3", 0x200000, 0xb7ab9338, REGION_GFX1, 0x0000005, LOAD_8_64 },
  { "tkoj3_b.simm3", 0x200000, 0x4d3f919a, REGION_GFX1, 0x0000006, LOAD_8_64 },
  { "tkoj3_a.simm3", 0x200000, 0xcfef17ab, REGION_GFX1, 0x0000007, LOAD_8_64 },
  LOAD( ROM2, "tko.01", 0x00000, 0x20000, 0x6eda50c2),
  LOAD_16_8( SMP1, "tkoj5_a.simm5", 0x000000, 0x200000, 0xab45d509),
  LOAD_16_8( SMP1, "tkoj5_b.simm5", 0x000001, 0x200000, 0xfa905c3d),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_csclub[] =
{
  LOAD_SW16( CPU1, "csce.03a", 0x000000, 0x80000, 0x824082be),
  LOAD_SW16( CPU1, "csce.04a", 0x080000, 0x80000, 0x74e6a4fe),
  LOAD_SW16( CPU1, "csce.05a", 0x100000, 0x80000, 0x8ae0df19),
  LOAD_SW16( CPU1, "csce.06a", 0x180000, 0x80000, 0x51f2f0d3),
  LOAD_SW16( CPU1, "csce.07a", 0x200000, 0x80000, 0x003968fd),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { "csc.73", 0x080000, 0x335f07c3, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "csc.74", 0x080000, 0xab215357, REGION_GFX1, 0xa00000, LOAD_16_64 },
  { "csc.75", 0x080000, 0xa2367381, REGION_GFX1, 0xc00000, LOAD_16_64 },
  { "csc.76", 0x080000, 0x728aac1f, REGION_GFX1, 0xe00000, LOAD_16_64 },
  { "csc.63", 0x080000, 0x3711b8ca, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "csc.64", 0x080000, 0x828a06d8, REGION_GFX1, 0xa00002, LOAD_16_64 },
  { "csc.65", 0x080000, 0x86ee4569, REGION_GFX1, 0xc00002, LOAD_16_64 },
  { "csc.66", 0x080000, 0xc24f577f, REGION_GFX1, 0xe00002, LOAD_16_64 },
  { "csc.83", 0x080000, 0x0750d12a, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "csc.84", 0x080000, 0x90a92f39, REGION_GFX1, 0xa00004, LOAD_16_64 },
  { "csc.85", 0x080000, 0xd08ab012, REGION_GFX1, 0xc00004, LOAD_16_64 },
  { "csc.86", 0x080000, 0x41652583, REGION_GFX1, 0xe00004, LOAD_16_64 },
  { "csc.93", 0x080000, 0xa756c7f7, REGION_GFX1, 0x800006, LOAD_16_64 },
  { "csc.94", 0x080000, 0xfb7ccc73, REGION_GFX1, 0xa00006, LOAD_16_64 },
  { "csc.95", 0x080000, 0x4d014297, REGION_GFX1, 0xc00006, LOAD_16_64 },
  { "csc.96", 0x080000, 0x6754b1ef, REGION_GFX1, 0xe00006, LOAD_16_64 },
  LOAD( ROM2, "csc.01", 0x00000, 0x20000, 0xee162111),
  LOAD_SW16( SMP1, "csc.51", 0x000000, 0x080000, 0x5a52afd5),
  LOAD_SW16( SMP1, "csc.52", 0x080000, 0x080000, 0x1408a811),
  LOAD_SW16( SMP1, "csc.53", 0x100000, 0x080000, 0x4fb9f57c),
  LOAD_SW16( SMP1, "csc.54", 0x180000, 0x080000, 0x9a8f40ec),
  LOAD_SW16( SMP1, "csc.55", 0x200000, 0x080000, 0x91529a91),
  LOAD_SW16( SMP1, "csc.56", 0x280000, 0x080000, 0x9a345334),
  LOAD_SW16( SMP1, "csc.57", 0x300000, 0x080000, 0xaedc27f2),
  LOAD_SW16( SMP1, "csc.58", 0x380000, 0x080000, 0x2300b7b3),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_csclub1[] = // clone of csclub
{
  LOAD_SW16( CPU1, "csce.03", 0x000000, 0x80000, 0xf2c852ef),
  LOAD_SW16( CPU1, "csce.04", 0x080000, 0x80000, 0x1184530f),
  LOAD_SW16( CPU1, "csce.05", 0x100000, 0x80000, 0x804e2b6b),
  LOAD_SW16( CPU1, "csce.06", 0x180000, 0x80000, 0x09277cb9),
  LOAD_SW16( CPU1, "csc.07", 0x200000, 0x80000, 0x01b05caa),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { "csc.14m", 0x200000, 0xe8904afa, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "csc.16m", 0x200000, 0xc98c8079, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "csc.18m", 0x200000, 0xc030df5a, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "csc.20m", 0x200000, 0xb4e55863, REGION_GFX1, 0x800006, LOAD_16_64 },
  LOAD_SW16( SMP1, "csc.11m", 0x000000, 0x200000, 0xa027b827),
  LOAD_SW16( SMP1, "csc.12m", 0x200000, 0x200000, 0xcb7f6e55),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_csclubj[] = // clone of csclub
{
  LOAD_SW16( CPU1, "cscj.03", 0x000000, 0x80000, 0xec4ddaa2),
  LOAD_SW16( CPU1, "cscj.04", 0x080000, 0x80000, 0x60c632bb),
  LOAD_SW16( CPU1, "cscj.05", 0x100000, 0x80000, 0xad042003),
  LOAD_SW16( CPU1, "cscj.06", 0x180000, 0x80000, 0x169e4d40),
  LOAD_SW16( CPU1, "csc.07", 0x200000, 0x80000, 0x01b05caa),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { "csc.14m", 0x200000, 0xe8904afa, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "csc.16m", 0x200000, 0xc98c8079, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "csc.18m", 0x200000, 0xc030df5a, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "csc.20m", 0x200000, 0xb4e55863, REGION_GFX1, 0x800006, LOAD_16_64 },
  LOAD_SW16( SMP1, "csc.11m", 0x000000, 0x200000, 0xa027b827),
  LOAD_SW16( SMP1, "csc.12m", 0x200000, 0x200000, 0xcb7f6e55),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_cscluba[] = // clone of csclub
{
  LOAD_SW16( CPU1, "csca.03", 0x000000, 0x80000, 0xb6acd708),
  LOAD_SW16( CPU1, "csca.04", 0x080000, 0x80000, 0xd44ae35f),
  LOAD_SW16( CPU1, "csca.05", 0x100000, 0x80000, 0x8da76aec),
  LOAD_SW16( CPU1, "csca.06", 0x180000, 0x80000, 0xa1b7b1ee),
  LOAD_SW16( CPU1, "csc.07", 0x200000, 0x80000, 0x01b05caa),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { "csc.14m", 0x200000, 0xe8904afa, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "csc.16m", 0x200000, 0xc98c8079, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "csc.18m", 0x200000, 0xc030df5a, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "csc.20m", 0x200000, 0xb4e55863, REGION_GFX1, 0x800006, LOAD_16_64 },
  LOAD_SW16( SMP1, "csc.11m", 0x000000, 0x200000, 0xa027b827),
  LOAD_SW16( SMP1, "csc.12m", 0x200000, 0x200000, 0xcb7f6e55),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_csclubh[] = // clone of csclub
{
  LOAD_SW16( CPU1, "csch.03", 0x000000, 0x80000, 0x0dd7e46d),
  LOAD_SW16( CPU1, "csch.04", 0x080000, 0x80000, 0x486e8143),
  LOAD_SW16( CPU1, "csch.05", 0x100000, 0x80000, 0x9e509dfb),
  LOAD_SW16( CPU1, "csch.06", 0x180000, 0x80000, 0x817ba313),
  LOAD_SW16( CPU1, "csc.07", 0x200000, 0x80000, 0x01b05caa),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { "csc.14m", 0x200000, 0xe8904afa, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "csc.16m", 0x200000, 0xc98c8079, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "csc.18m", 0x200000, 0xc030df5a, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "csc.20m", 0x200000, 0xb4e55863, REGION_GFX1, 0x800006, LOAD_16_64 },
  LOAD_SW16( SMP1, "csc.11m", 0x000000, 0x200000, 0xa027b827),
  LOAD_SW16( SMP1, "csc.12m", 0x200000, 0x200000, 0xcb7f6e55),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_cybots[] =
{
  LOAD_SW16( CPU1, "cybe.03", 0x000000, 0x80000, 0x234381cd),
  LOAD_SW16( CPU1, "cybe.04", 0x080000, 0x80000, 0x80691061),
  LOAD_SW16( CPU1, "cyb.05", 0x100000, 0x80000, 0xec40408e),
  LOAD_SW16( CPU1, "cyb.06", 0x180000, 0x80000, 0x1ad0bed2),
  LOAD_SW16( CPU1, "cyb.07", 0x200000, 0x80000, 0x6245a39a),
  LOAD_SW16( CPU1, "cyb.08", 0x280000, 0x80000, 0x4b48e223),
  LOAD_SW16( CPU1, "cyb.09", 0x300000, 0x80000, 0xe15238f6),
  LOAD_SW16( CPU1, "cyb.10", 0x380000, 0x80000, 0x75f4003b),
  { "cyb.13m", 0x400000, 0xf0dce192, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "cyb.15m", 0x400000, 0x187aa39c, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "cyb.17m", 0x400000, 0x8a0e4b12, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "cyb.19m", 0x400000, 0x34b62612, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "cyb.14m", 0x400000, 0xc1537957, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "cyb.16m", 0x400000, 0x15349e86, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "cyb.18m", 0x400000, 0xd83e977d, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "cyb.20m", 0x400000, 0x77cdad5c, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "cyb.01", 0x00000, 0x20000, 0x9c0fb079),
  LOAD( ROM2, "cyb.02", 0x20000, 0x20000, 0x51cb0c4e),
  LOAD_SW16( SMP1, "cyb.11m", 0x000000, 0x200000, 0x362ccab2),
  LOAD_SW16( SMP1, "cyb.12m", 0x200000, 0x200000, 0x7066e9cc),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_cybotsu[] = // clone of cybots
{
  LOAD_SW16( CPU1, "cybu.03", 0x000000, 0x80000, 0xdb4da8f4),
  LOAD_SW16( CPU1, "cybu.04", 0x080000, 0x80000, 0x1eec68ac),
  LOAD_SW16( CPU1, "cyb.05", 0x100000, 0x80000, 0xec40408e),
  LOAD_SW16( CPU1, "cyb.06", 0x180000, 0x80000, 0x1ad0bed2),
  LOAD_SW16( CPU1, "cyb.07", 0x200000, 0x80000, 0x6245a39a),
  LOAD_SW16( CPU1, "cyb.08", 0x280000, 0x80000, 0x4b48e223),
  LOAD_SW16( CPU1, "cyb.09", 0x300000, 0x80000, 0xe15238f6),
  LOAD_SW16( CPU1, "cyb.10", 0x380000, 0x80000, 0x75f4003b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_cybotsj[] = // clone of cybots
{
  LOAD_SW16( CPU1, "cybj.03", 0x000000, 0x80000, 0x6096eada),
  LOAD_SW16( CPU1, "cybj.04", 0x080000, 0x80000, 0x7b0ffaa9),
  LOAD_SW16( CPU1, "cyb.05", 0x100000, 0x80000, 0xec40408e),
  LOAD_SW16( CPU1, "cyb.06", 0x180000, 0x80000, 0x1ad0bed2),
  LOAD_SW16( CPU1, "cyb.07", 0x200000, 0x80000, 0x6245a39a),
  LOAD_SW16( CPU1, "cyb.08", 0x280000, 0x80000, 0x4b48e223),
  LOAD_SW16( CPU1, "cyb.09", 0x300000, 0x80000, 0xe15238f6),
  LOAD_SW16( CPU1, "cyb.10", 0x380000, 0x80000, 0x75f4003b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddtod[] =
{
  LOAD_SW16( CPU1, "dade.03c", 0x000000, 0x80000, 0x8e73533d),
  LOAD_SW16( CPU1, "dade.04c", 0x080000, 0x80000, 0x00c2e82e),
  LOAD_SW16( CPU1, "dade.05c", 0x100000, 0x80000, 0xea996008),
  LOAD_SW16( CPU1, "dad.06a", 0x180000, 0x80000, 0x6225495a),
  LOAD_SW16( CPU1, "dad.07a", 0x200000, 0x80000, 0xb3480ec3),
  { "dad.13m", 0x200000, 0xda3cb7d6, REGION_GFX1, 0x000000, LOAD_16_64 },
  { "dad.15m", 0x200000, 0x92b63172, REGION_GFX1, 0x000002, LOAD_16_64 },
  { "dad.17m", 0x200000, 0xb98757f5, REGION_GFX1, 0x000004, LOAD_16_64 },
  { "dad.19m", 0x200000, 0x8121ce46, REGION_GFX1, 0x000006, LOAD_16_64 },
  { "dad.14m", 0x100000, 0x837e6f3f, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "dad.16m", 0x100000, 0xf0916bdb, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "dad.18m", 0x100000, 0xcef393ef, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "dad.20m", 0x100000, 0x8953fe9e, REGION_GFX1, 0x800006, LOAD_16_64 },
  LOAD( ROM2, "dad.01", 0x00000, 0x20000, 0x3f5e2424),
  LOAD_SW16( SMP1, "dad.11m", 0x000000, 0x200000, 0x0c499b67),
  LOAD_SW16( SMP1, "dad.12m", 0x200000, 0x200000, 0x2f0b5a4e),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddtodr1[] = // clone of ddtod
{
  LOAD_SW16( CPU1, "dade.03a", 0x000000, 0x80000, 0x665a035e),
  LOAD_SW16( CPU1, "dade.04a", 0x080000, 0x80000, 0x02613207),
  LOAD_SW16( CPU1, "dade.05a", 0x100000, 0x80000, 0x36845996),
  LOAD_SW16( CPU1, "dad.06", 0x180000, 0x80000, 0x13aa3e56),
  LOAD_SW16( CPU1, "dad.07", 0x200000, 0x80000, 0x431cb6dd),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddtodu[] = // clone of ddtod
{
  LOAD_SW16( CPU1, "dadu.03b", 0x000000, 0x80000, 0xa519905f),
  LOAD_SW16( CPU1, "dadu.04b", 0x080000, 0x80000, 0x52562d38),
  LOAD_SW16( CPU1, "dadu.05b", 0x100000, 0x80000, 0xee1cfbfe),
  LOAD_SW16( CPU1, "dad.06", 0x180000, 0x80000, 0x13aa3e56),
  LOAD_SW16( CPU1, "dad.07", 0x200000, 0x80000, 0x431cb6dd),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddtodur1[] = // clone of ddtod
{
  LOAD_SW16( CPU1, "dadu.03a", 0x000000, 0x80000, 0x4413f177),
  LOAD_SW16( CPU1, "dadu.04a", 0x080000, 0x80000, 0x168de230),
  LOAD_SW16( CPU1, "dadu.05a", 0x100000, 0x80000, 0x03d39e91),
  LOAD_SW16( CPU1, "dad.06", 0x180000, 0x80000, 0x13aa3e56),
  LOAD_SW16( CPU1, "dad.07", 0x200000, 0x80000, 0x431cb6dd),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddtodj[] = // clone of ddtod
{
  LOAD_SW16( CPU1, "dadj.03c", 0x000000, 0x80000, 0x0b1b5798),
  LOAD_SW16( CPU1, "dadj.04c", 0x080000, 0x80000, 0xc6a2fbc8),
  LOAD_SW16( CPU1, "dadj.05c", 0x100000, 0x80000, 0x189b15fe),
  LOAD_SW16( CPU1, "dad.06a", 0x180000, 0x80000, 0x6225495a),
  LOAD_SW16( CPU1, "dad.07a", 0x200000, 0x80000, 0xb3480ec3),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddtodjr1[] = // clone of ddtod
{
  LOAD_SW16( CPU1, "dadj.03b", 0x000000, 0x80000, 0x87606b85),
  LOAD_SW16( CPU1, "dadj.04b", 0x080000, 0x80000, 0x24d49575),
  LOAD_SW16( CPU1, "dadj.05b", 0x100000, 0x80000, 0x56ce51f7),
  LOAD_SW16( CPU1, "dad.06", 0x180000, 0x80000, 0x13aa3e56),
  LOAD_SW16( CPU1, "dad.07", 0x200000, 0x80000, 0x431cb6dd),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddtodjr2[] = // clone of ddtod
{
  LOAD_SW16( CPU1, "dadj.03a", 0x000000, 0x80000, 0x711638dc),
  LOAD_SW16( CPU1, "dadj.04a", 0x080000, 0x80000, 0x4869639c),
  LOAD_SW16( CPU1, "dadj.05a", 0x100000, 0x80000, 0x484c0efa),
  LOAD_SW16( CPU1, "dad.06", 0x180000, 0x80000, 0x13aa3e56),
  LOAD_SW16( CPU1, "dad.07", 0x200000, 0x80000, 0x431cb6dd),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddtoda[] = // clone of ddtod
{
  LOAD_SW16( CPU1, "dada.03a", 0x000000, 0x80000, 0xfc6f2dd7),
  LOAD_SW16( CPU1, "dada.04a", 0x080000, 0x80000, 0xd4be4009),
  LOAD_SW16( CPU1, "dada.05a", 0x100000, 0x80000, 0x6712d1cf),
  LOAD_SW16( CPU1, "dad.06", 0x180000, 0x80000, 0x13aa3e56),
  LOAD_SW16( CPU1, "dad.07", 0x200000, 0x80000, 0x431cb6dd),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddtodh[] = // clone of ddtod
{
  LOAD_SW16( CPU1, "dadh.03c", 0x000000, 0x80000, 0x5750a861),
  LOAD_SW16( CPU1, "dadh.04c", 0x080000, 0x80000, 0xcfbf1b56),
  LOAD_SW16( CPU1, "dadh.05c", 0x100000, 0x80000, 0xa6e562ba),
  LOAD_SW16( CPU1, "dad.06a", 0x180000, 0x80000, 0x6225495a),
  LOAD_SW16( CPU1, "dad.07a", 0x200000, 0x80000, 0xb3480ec3),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddtodhr1[] = // clone of ddtod
{
  LOAD_SW16( CPU1, "dadh.03b", 0x000000, 0x80000, 0xae0cb98e),
  LOAD_SW16( CPU1, "dadh.04b", 0x080000, 0x80000, 0xb5774363),
  LOAD_SW16( CPU1, "dadh.05b", 0x100000, 0x80000, 0x6ce2a485),
  LOAD_SW16( CPU1, "dad.06", 0x180000, 0x80000, 0x13aa3e56),
  LOAD_SW16( CPU1, "dad.07", 0x200000, 0x80000, 0x431cb6dd),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddtodhr2[] = // clone of ddtod
{
  LOAD_SW16( CPU1, "dadh.03a", 0x000000, 0x80000, 0x43d04aa3),
  LOAD_SW16( CPU1, "dadh.04a", 0x080000, 0x80000, 0x8b8d296c),
  LOAD_SW16( CPU1, "dadh.05a", 0x100000, 0x80000, 0xdaae6b14),
  LOAD_SW16( CPU1, "dad.06", 0x180000, 0x80000, 0x13aa3e56),
  LOAD_SW16( CPU1, "dad.07", 0x200000, 0x80000, 0x431cb6dd),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddsom[] =
{
  LOAD_SW16( CPU1, "dd2e.03e", 0x000000, 0x80000, 0x449361af),
  LOAD_SW16( CPU1, "dd2e.04e", 0x080000, 0x80000, 0x5b7052b6),
  LOAD_SW16( CPU1, "dd2e.05e", 0x100000, 0x80000, 0x788d5f60),
  LOAD_SW16( CPU1, "dd2e.06e", 0x180000, 0x80000, 0xe0807e1e),
  LOAD_SW16( CPU1, "dd2e.07", 0x200000, 0x80000, 0xbb777a02),
  LOAD_SW16( CPU1, "dd2e.08", 0x280000, 0x80000, 0x30970890),
  LOAD_SW16( CPU1, "dd2e.09", 0x300000, 0x80000, 0x99e2194d),
  LOAD_SW16( CPU1, "dd2e.10", 0x380000, 0x80000, 0xe198805e),
  { "dd2.13m", 0x400000, 0xa46b4e6e, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "dd2.15m", 0x400000, 0xd5fc50fc, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "dd2.17m", 0x400000, 0x837c0867, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "dd2.19m", 0x400000, 0xbb0ec21c, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "dd2.14m", 0x200000, 0x6d824ce2, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "dd2.16m", 0x200000, 0x79682ae5, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "dd2.18m", 0x200000, 0xacddd149, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "dd2.20m", 0x200000, 0x117fb0c0, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "dd2.01", 0x00000, 0x20000, 0x99d657e5),
  LOAD( ROM2, "dd2.02", 0x20000, 0x20000, 0x117a3824),
  LOAD_SW16( SMP1, "dd2.11m", 0x000000, 0x200000, 0x98d0c325),
  LOAD_SW16( SMP1, "dd2.12m", 0x200000, 0x200000, 0x5ea2e7fa),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddsomr1[] = // clone of ddsom
{
  LOAD_SW16( CPU1, "dd2e.03d", 0x000000, 0x80000, 0x6c084ab5),
  LOAD_SW16( CPU1, "dd2e.04d", 0x080000, 0x80000, 0x9b94a947),
  LOAD_SW16( CPU1, "dd2e.05d", 0x100000, 0x80000, 0x5d6a63c6),
  LOAD_SW16( CPU1, "dd2e.06d", 0x180000, 0x80000, 0x31bde8ee),
  LOAD_SW16( CPU1, "dd2e.07", 0x200000, 0x80000, 0xbb777a02),
  LOAD_SW16( CPU1, "dd2e.08", 0x280000, 0x80000, 0x30970890),
  LOAD_SW16( CPU1, "dd2e.09", 0x300000, 0x80000, 0x99e2194d),
  LOAD_SW16( CPU1, "dd2e.10", 0x380000, 0x80000, 0xe198805e),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddsomr2[] = // clone of ddsom
{
  LOAD_SW16( CPU1, "dd2e.03b", 0x000000, 0x80000, 0xcd2deb66),
  LOAD_SW16( CPU1, "dd2e.04b", 0x080000, 0x80000, 0xbfee43cc),
  LOAD_SW16( CPU1, "dd2e.05b", 0x100000, 0x80000, 0x049ab19d),
  LOAD_SW16( CPU1, "dd2e.06b", 0x180000, 0x80000, 0x3994fb8b),
  LOAD_SW16( CPU1, "dd2e.07", 0x200000, 0x80000, 0xbb777a02),
  LOAD_SW16( CPU1, "dd2e.08", 0x280000, 0x80000, 0x30970890),
  LOAD_SW16( CPU1, "dd2e.09", 0x300000, 0x80000, 0x99e2194d),
  LOAD_SW16( CPU1, "dd2e.10", 0x380000, 0x80000, 0xe198805e),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddsomr3[] = // clone of ddsom
{
  LOAD_SW16( CPU1, "dd2e.03a", 0x000000, 0x80000, 0x6de67678),
  LOAD_SW16( CPU1, "dd2e.04a", 0x080000, 0x80000, 0x0e45739a),
  LOAD_SW16( CPU1, "dd2e.05a", 0x100000, 0x80000, 0x3dce8025),
  LOAD_SW16( CPU1, "dd2e.06a", 0x180000, 0x80000, 0x51bafbef),
  LOAD_SW16( CPU1, "dd2e.07", 0x200000, 0x80000, 0xbb777a02),
  LOAD_SW16( CPU1, "dd2e.08", 0x280000, 0x80000, 0x30970890),
  LOAD_SW16( CPU1, "dd2e.09", 0x300000, 0x80000, 0x99e2194d),
  LOAD_SW16( CPU1, "dd2e.10", 0x380000, 0x80000, 0xe198805e),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddsomu[] = // clone of ddsom
{
  LOAD_SW16( CPU1, "dd2u.03g", 0x000000, 0x80000, 0xfb089b39),
  LOAD_SW16( CPU1, "dd2u.04g", 0x080000, 0x80000, 0xcd432b73),
  LOAD_SW16( CPU1, "dd2.05g", 0x100000, 0x80000, 0x5eb1991c),
  LOAD_SW16( CPU1, "dd2.06g", 0x180000, 0x80000, 0xc26b5e55),
  LOAD_SW16( CPU1, "dd2.07", 0x200000, 0x80000, 0x909a0b8b),
  LOAD_SW16( CPU1, "dd2.08", 0x280000, 0x80000, 0xe53c4d01),
  LOAD_SW16( CPU1, "dd2.09", 0x300000, 0x80000, 0x5f86279f),
  LOAD_SW16( CPU1, "dd2.10", 0x380000, 0x80000, 0xad954c26),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddsomur1[] = // clone of ddsom
{
  LOAD_SW16( CPU1, "dd2u.03d", 0x000000, 0x80000, 0x0f700d84),
  LOAD_SW16( CPU1, "dd2u.04d", 0x080000, 0x80000, 0xb99eb254),
  LOAD_SW16( CPU1, "dd2.05d", 0x100000, 0x80000, 0xb23061f3),
  LOAD_SW16( CPU1, "dd2.06d", 0x180000, 0x80000, 0x8bf1d8ce),
  LOAD_SW16( CPU1, "dd2.07", 0x200000, 0x80000, 0x909a0b8b),
  LOAD_SW16( CPU1, "dd2.08", 0x280000, 0x80000, 0xe53c4d01),
  LOAD_SW16( CPU1, "dd2.09", 0x300000, 0x80000, 0x5f86279f),
  LOAD_SW16( CPU1, "dd2.10", 0x380000, 0x80000, 0xad954c26),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddsomj[] = // clone of ddsom
{
  LOAD_SW16( CPU1, "dd2j.03g", 0x000000, 0x80000, 0xe6c8c985),
  LOAD_SW16( CPU1, "dd2j.04g", 0x080000, 0x80000, 0x8386c0bd),
  LOAD_SW16( CPU1, "dd2.05g", 0x100000, 0x80000, 0x5eb1991c),
  LOAD_SW16( CPU1, "dd2.06g", 0x180000, 0x80000, 0xc26b5e55),
  LOAD_SW16( CPU1, "dd2.07", 0x200000, 0x80000, 0x909a0b8b),
  LOAD_SW16( CPU1, "dd2.08", 0x280000, 0x80000, 0xe53c4d01),
  LOAD_SW16( CPU1, "dd2.09", 0x300000, 0x80000, 0x5f86279f),
  LOAD_SW16( CPU1, "dd2.10", 0x380000, 0x80000, 0xad954c26),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddsomjr1[] = // clone of ddsom
{
  LOAD_SW16( CPU1, "dd2j.03b", 0x000000, 0x80000, 0x965d74e5),
  LOAD_SW16( CPU1, "dd2j.04b", 0x080000, 0x80000, 0x958eb8f3),
  LOAD_SW16( CPU1, "dd2.05b", 0x100000, 0x80000, 0xd38571ca),
  LOAD_SW16( CPU1, "dd2.06b", 0x180000, 0x80000, 0x6d5a3bbb),
  LOAD_SW16( CPU1, "dd2.07", 0x200000, 0x80000, 0x909a0b8b),
  LOAD_SW16( CPU1, "dd2.08", 0x280000, 0x80000, 0xe53c4d01),
  LOAD_SW16( CPU1, "dd2.09", 0x300000, 0x80000, 0x5f86279f),
  LOAD_SW16( CPU1, "dd2.10", 0x380000, 0x80000, 0xad954c26),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddsoma[] = // clone of ddsom
{
  LOAD_SW16( CPU1, "dd2a.03g", 0x000000, 0x80000, 0x0b4fec22),
  LOAD_SW16( CPU1, "dd2a.04g", 0x080000, 0x80000, 0x055b7019),
  LOAD_SW16( CPU1, "dd2.05g", 0x100000, 0x80000, 0x5eb1991c),
  LOAD_SW16( CPU1, "dd2.06g", 0x180000, 0x80000, 0xc26b5e55),
  LOAD_SW16( CPU1, "dd2.07", 0x200000, 0x80000, 0x909a0b8b),
  LOAD_SW16( CPU1, "dd2.08", 0x280000, 0x80000, 0xe53c4d01),
  LOAD_SW16( CPU1, "dd2.09", 0x300000, 0x80000, 0x5f86279f),
  LOAD_SW16( CPU1, "dd2.10", 0x380000, 0x80000, 0xad954c26),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddsomb[] = // clone of ddsom
{
  LOAD_SW16( CPU1, "dd2b.03a", 0x000000, 0x80000, 0xe8ce7fbb),
  LOAD_SW16( CPU1, "dd2b.04a", 0x080000, 0x80000, 0x6b679664),
  LOAD_SW16( CPU1, "dd2b.05a", 0x100000, 0x80000, 0x9b2534eb),
  LOAD_SW16( CPU1, "dd2b.06a", 0x180000, 0x80000, 0x3b21ba59),
  LOAD_SW16( CPU1, "dd2b.07", 0x200000, 0x80000, 0xfce2558d),
  LOAD_SW16( CPU1, "dd2e.08", 0x280000, 0x80000, 0x30970890),
  LOAD_SW16( CPU1, "dd2e.09", 0x300000, 0x80000, 0x99e2194d),
  LOAD_SW16( CPU1, "dd2e.10", 0x380000, 0x80000, 0xe198805e),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddsomh[] = // clone of ddsom
{
  LOAD_SW16( CPU1, "dd2h.03a", 0x000000, 0x80000, 0xe472c9f3),
  LOAD_SW16( CPU1, "dd2h.04a", 0x080000, 0x80000, 0x315a7706),
  LOAD_SW16( CPU1, "dd2h.05a", 0x100000, 0x80000, 0x9b2534eb),
  LOAD_SW16( CPU1, "dd2h.06a", 0x180000, 0x80000, 0x3b21ba59),
  LOAD_SW16( CPU1, "dd2h.07a", 0x200000, 0x80000, 0xfce2558d),
  LOAD_SW16( CPU1, "dd2e.08", 0x280000, 0x80000, 0x30970890),
  LOAD_SW16( CPU1, "dd2e.09", 0x300000, 0x80000, 0x99e2194d),
  LOAD_SW16( CPU1, "dd2e.10", 0x380000, 0x80000, 0xe198805e),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_dimahoo[] =
{
  LOAD_SW16( CPU1, "gmde.03", 0x000000, 0x80000, 0x968fcecd),
  LOAD_SW16( CPU1, "gmd.04", 0x080000, 0x80000, 0x37485567),
  LOAD_SW16( CPU1, "gmd.05", 0x100000, 0x80000, 0xda269ffb),
  LOAD_SW16( CPU1, "gmd.06", 0x180000, 0x80000, 0x55b483c9),
  { "gmd.13m", 0x400000, 0x80dd19f0, REGION_GFX1, 0x000000, LOAD_16_64 },
  { "gmd.15m", 0x400000, 0xdfd93a78, REGION_GFX1, 0x000002, LOAD_16_64 },
  { "gmd.17m", 0x400000, 0x16356520, REGION_GFX1, 0x000004, LOAD_16_64 },
  { "gmd.19m", 0x400000, 0xdfc33031, REGION_GFX1, 0x000006, LOAD_16_64 },
  LOAD( ROM2, "gmd.01", 0x00000, 0x20000, 0x3f9bc985),
  LOAD( ROM2, "gmd.02", 0x20000, 0x20000, 0x3fd39dde),
  LOAD_SW16( SMP1, "gmd.11m", 0x000000, 0x400000, 0x06a65542),
  LOAD_SW16( SMP1, "gmd.12m", 0x400000, 0x400000, 0x50bc7a31),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_dimahoou[] = // clone of dimahoo
{
  LOAD_SW16( CPU1, "gmdu.03", 0x000000, 0x80000, 0x43bcb15f),
  LOAD_SW16( CPU1, "gmd.04", 0x080000, 0x80000, 0x37485567),
  LOAD_SW16( CPU1, "gmd.05", 0x100000, 0x80000, 0xda269ffb),
  LOAD_SW16( CPU1, "gmd.06", 0x180000, 0x80000, 0x55b483c9),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_gmahou[] = // clone of dimahoo
{
  LOAD_SW16( CPU1, "gmdj.03", 0x000000, 0x80000, 0xcd6979e3),
  LOAD_SW16( CPU1, "gmd.04", 0x080000, 0x80000, 0x37485567),
  LOAD_SW16( CPU1, "gmd.05", 0x100000, 0x80000, 0xda269ffb),
  LOAD_SW16( CPU1, "gmd.06", 0x180000, 0x80000, 0x55b483c9),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_dstlk[] =
{
  LOAD_SW16( CPU1, "vame.03a", 0x000000, 0x80000, 0x004c9cff),
  LOAD_SW16( CPU1, "vame.04a", 0x080000, 0x80000, 0xae413ff2),
  LOAD_SW16( CPU1, "vame.05a", 0x100000, 0x80000, 0x60678756),
  LOAD_SW16( CPU1, "vame.06a", 0x180000, 0x80000, 0x912870b3),
  LOAD_SW16( CPU1, "vame.07a", 0x200000, 0x80000, 0xdabae3e8),
  LOAD_SW16( CPU1, "vame.08a", 0x280000, 0x80000, 0x2c6e3077),
  LOAD_SW16( CPU1, "vame.09a", 0x300000, 0x80000, 0xf16db74b),
  LOAD_SW16( CPU1, "vame.10a", 0x380000, 0x80000, 0x701e2147),
  { "vam.13m", 0x400000, 0xc51baf99, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "vam.15m", 0x400000, 0x3ce83c77, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "vam.17m", 0x400000, 0x4f2408e0, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "vam.19m", 0x400000, 0x9ff60250, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "vam.14m", 0x100000, 0xbd87243c, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "vam.16m", 0x100000, 0xafec855f, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "vam.18m", 0x100000, 0x3a033625, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "vam.20m", 0x100000, 0x2bff6a89, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "vam.01", 0x00000, 0x20000, 0x64b685d5),
  LOAD( ROM2, "vam.02", 0x20000, 0x20000, 0xcf7c97c7),
  LOAD_SW16( SMP1, "vam.11m", 0x000000, 0x200000, 0x4a39deb2),
  LOAD_SW16( SMP1, "vam.12m", 0x200000, 0x200000, 0x1a3e5c03),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_dstlku[] = // clone of dstlk
{
  LOAD_SW16( CPU1, "vamu.03b", 0x000000, 0x80000, 0x68a6343f),
  LOAD_SW16( CPU1, "vamu.04b", 0x080000, 0x80000, 0x58161453),
  LOAD_SW16( CPU1, "vamu.05b", 0x100000, 0x80000, 0xdfc038b8),
  LOAD_SW16( CPU1, "vamu.06b", 0x180000, 0x80000, 0xc3842c89),
  LOAD_SW16( CPU1, "vamu.07b", 0x200000, 0x80000, 0x25b60b6e),
  LOAD_SW16( CPU1, "vamu.08b", 0x280000, 0x80000, 0x2113c596),
  LOAD_SW16( CPU1, "vamu.09b", 0x300000, 0x80000, 0x2d1e9ae5),
  LOAD_SW16( CPU1, "vamu.10b", 0x380000, 0x80000, 0x81145622),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_dstlkur1[] = // clone of dstlk
{
  LOAD_SW16( CPU1, "vamu.03a", 0x000000, 0x80000, 0x628899f9),
  LOAD_SW16( CPU1, "vamu.04a", 0x080000, 0x80000, 0x696d9b25),
  LOAD_SW16( CPU1, "vamu.05a", 0x100000, 0x80000, 0x673ed50a),
  LOAD_SW16( CPU1, "vamu.06a", 0x180000, 0x80000, 0xf2377be7),
  LOAD_SW16( CPU1, "vamu.07a", 0x200000, 0x80000, 0xd8f498c4),
  LOAD_SW16( CPU1, "vamu.08a", 0x280000, 0x80000, 0xe6a8a1a0),
  LOAD_SW16( CPU1, "vamu.09a", 0x300000, 0x80000, 0x8dd55b24),
  LOAD_SW16( CPU1, "vamu.10a", 0x380000, 0x80000, 0xc1a3d9be),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vampj[] = // clone of dstlk
{
  LOAD_SW16( CPU1, "vamj.03a", 0x000000, 0x80000, 0xf55d3722),
  LOAD_SW16( CPU1, "vamj.04b", 0x080000, 0x80000, 0x4d9c43c4),
  LOAD_SW16( CPU1, "vamj.05a", 0x100000, 0x80000, 0x6c497e92),
  LOAD_SW16( CPU1, "vamj.06a", 0x180000, 0x80000, 0xf1bbecb6),
  LOAD_SW16( CPU1, "vamj.07a", 0x200000, 0x80000, 0x1067ad84),
  LOAD_SW16( CPU1, "vamj.08a", 0x280000, 0x80000, 0x4b89f41f),
  LOAD_SW16( CPU1, "vamj.09a", 0x300000, 0x80000, 0xfc0a4aac),
  LOAD_SW16( CPU1, "vamj.10a", 0x380000, 0x80000, 0x9270c26b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vampja[] = // clone of dstlk
{
  LOAD_SW16( CPU1, "vamj.03a", 0x000000, 0x80000, 0xf55d3722),
  LOAD_SW16( CPU1, "vamj.04a", 0x080000, 0x80000, 0xfdcbdae3),
  LOAD_SW16( CPU1, "vamj.05a", 0x100000, 0x80000, 0x6c497e92),
  LOAD_SW16( CPU1, "vamj.06a", 0x180000, 0x80000, 0xf1bbecb6),
  LOAD_SW16( CPU1, "vamj.07a", 0x200000, 0x80000, 0x1067ad84),
  LOAD_SW16( CPU1, "vamj.08a", 0x280000, 0x80000, 0x4b89f41f),
  LOAD_SW16( CPU1, "vamj.09a", 0x300000, 0x80000, 0xfc0a4aac),
  LOAD_SW16( CPU1, "vamj.10a", 0x380000, 0x80000, 0x9270c26b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vampjr1[] = // clone of dstlk
{
  LOAD_SW16( CPU1, "vamj.03", 0x000000, 0x80000, 0x8895bf77),
  LOAD_SW16( CPU1, "vamj.04", 0x080000, 0x80000, 0x5027db3d),
  LOAD_SW16( CPU1, "vamj.05", 0x100000, 0x80000, 0x97c66fdb),
  LOAD_SW16( CPU1, "vamj.06", 0x180000, 0x80000, 0x9b4c3426),
  LOAD_SW16( CPU1, "vamj.07", 0x200000, 0x80000, 0x303bc4fd),
  LOAD_SW16( CPU1, "vamj.08", 0x280000, 0x80000, 0x3dea3646),
  LOAD_SW16( CPU1, "vamj.09", 0x300000, 0x80000, 0xc119a827),
  LOAD_SW16( CPU1, "vamj.10", 0x380000, 0x80000, 0x46593b79),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_dstlka[] = // clone of dstlk
{
  LOAD_SW16( CPU1, "vama.03a", 0x000000, 0x80000, 0x294e0bec),
  LOAD_SW16( CPU1, "vama.04a", 0x080000, 0x80000, 0xbc18e128),
  LOAD_SW16( CPU1, "vama.05a", 0x100000, 0x80000, 0xe709fa59),
  LOAD_SW16( CPU1, "vama.06a", 0x180000, 0x80000, 0x55e4d387),
  LOAD_SW16( CPU1, "vama.07a", 0x200000, 0x80000, 0x24e8f981),
  LOAD_SW16( CPU1, "vama.08a", 0x280000, 0x80000, 0x743f3a8e),
  LOAD_SW16( CPU1, "vama.09a", 0x300000, 0x80000, 0x67fa5573),
  LOAD_SW16( CPU1, "vama.10a", 0x380000, 0x80000, 0x5e03d747),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_dstlkh[] = // clone of dstlk
{
  LOAD_SW16( CPU1, "vamh.03c", 0x000000, 0x80000, 0x4d7b9e8f),
  LOAD_SW16( CPU1, "vamh.04c", 0x080000, 0x80000, 0x2217e9a0),
  LOAD_SW16( CPU1, "vamh.05c", 0x100000, 0x80000, 0x3a05b13c),
  LOAD_SW16( CPU1, "vamh.06c", 0x180000, 0x80000, 0x11d70a1c),
  LOAD_SW16( CPU1, "vamh.07c", 0x200000, 0x80000, 0xdb5a8767),
  LOAD_SW16( CPU1, "vamh.08c", 0x280000, 0x80000, 0x2a4fd79b),
  LOAD_SW16( CPU1, "vamh.09c", 0x300000, 0x80000, 0x15187632),
  LOAD_SW16( CPU1, "vamh.10c", 0x380000, 0x80000, 0x192d2d81),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ecofghtr[] =
{
  LOAD_SW16( CPU1, "uece.03", 0x000000, 0x80000, 0xec2c1137),
  LOAD_SW16( CPU1, "uece.04", 0x080000, 0x80000, 0xb35f99db),
  LOAD_SW16( CPU1, "uece.05", 0x100000, 0x80000, 0xd9d42d31),
  LOAD_SW16( CPU1, "uece.06", 0x180000, 0x80000, 0x9d9771cf),
  { "uec.13m", 0x200000, 0xdcaf1436, REGION_GFX1, 0x000000, LOAD_16_64 },
  { "uec.15m", 0x200000, 0x2807df41, REGION_GFX1, 0x000002, LOAD_16_64 },
  { "uec.17m", 0x200000, 0x8a708d02, REGION_GFX1, 0x000004, LOAD_16_64 },
  { "uec.19m", 0x200000, 0xde7be0ef, REGION_GFX1, 0x000006, LOAD_16_64 },
  { "uec.14m", 0x100000, 0x1a003558, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "uec.16m", 0x100000, 0x4ff8a6f9, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "uec.18m", 0x100000, 0xb167ae12, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "uec.20m", 0x100000, 0x1064bdc2, REGION_GFX1, 0x800006, LOAD_16_64 },
  LOAD( ROM2, "uec.01", 0x00000, 0x20000, 0xc235bd15),
  LOAD_SW16( SMP1, "uec.11m", 0x000000, 0x200000, 0x81b25d39),
  LOAD_SW16( SMP1, "uec.12m", 0x200000, 0x200000, 0x27729e52),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ecofghtru[] = // clone of ecofghtr
{
  LOAD_SW16( CPU1, "uecu.03a", 0x000000, 0x80000, 0x22d88a4d),
  LOAD_SW16( CPU1, "uecu.04a", 0x080000, 0x80000, 0x6436cfcd),
  LOAD_SW16( CPU1, "uecu.05a", 0x100000, 0x80000, 0x336f121b),
  LOAD_SW16( CPU1, "uecu.06a", 0x180000, 0x80000, 0x6f99d984),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ecofghtru1[] = // clone of ecofghtr
{
  LOAD_SW16( CPU1, "uecu.03", 0x000000, 0x80000, 0x6792480c),
  LOAD_SW16( CPU1, "uecu.04", 0x080000, 0x80000, 0x95ce69d5),
  LOAD_SW16( CPU1, "uecu.05", 0x100000, 0x80000, 0x3a1e78ad),
  LOAD_SW16( CPU1, "uecu.06", 0x180000, 0x80000, 0xa3e2f3cc),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_uecology[] = // clone of ecofghtr
{
  LOAD_SW16( CPU1, "uecj.03", 0x000000, 0x80000, 0x94c40a4c),
  LOAD_SW16( CPU1, "uecj.04", 0x080000, 0x80000, 0x8d6e3a09),
  LOAD_SW16( CPU1, "uecj.05", 0x100000, 0x80000, 0x8604ecd7),
  LOAD_SW16( CPU1, "uecj.06", 0x180000, 0x80000, 0xb7e1d31f),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ecofghtra[] = // clone of ecofghtr
{
  LOAD_SW16( CPU1, "ueca.03", 0x000000, 0x80000, 0xbd4589b1),
  LOAD_SW16( CPU1, "ueca.04", 0x080000, 0x80000, 0x1d134b7d),
  LOAD_SW16( CPU1, "ueca.05", 0x100000, 0x80000, 0x9c581fc7),
  LOAD_SW16( CPU1, "ueca.06", 0x180000, 0x80000, 0xc92a7c50),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ecofghtrh[] = // clone of ecofghtr
{
  LOAD_SW16( CPU1, "uech.03", 0x000000, 0x80000, 0x14c9365e),
  LOAD_SW16( CPU1, "uech.04", 0x080000, 0x80000, 0x579495dc),
  LOAD_SW16( CPU1, "uech.05", 0x100000, 0x80000, 0x96807a8e),
  LOAD_SW16( CPU1, "uech.06", 0x180000, 0x80000, 0x682b9dbc),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_gigawing[] =
{
  LOAD_SW16( CPU1, "ggwu.03", 0x000000, 0x80000, 0xac725eb2),
  LOAD_SW16( CPU1, "ggwu.04", 0x080000, 0x80000, 0x392f4118),
  LOAD_SW16( CPU1, "ggw.05", 0x100000, 0x80000, 0x3239d642),
  { "ggw.13m", 0x400000, 0x105530a4, REGION_GFX1, 0x000000, LOAD_16_64 },
  { "ggw.15m", 0x400000, 0x9e774ab9, REGION_GFX1, 0x000002, LOAD_16_64 },
  { "ggw.17m", 0x400000, 0x466e0ba4, REGION_GFX1, 0x000004, LOAD_16_64 },
  { "ggw.19m", 0x400000, 0x840c8dea, REGION_GFX1, 0x000006, LOAD_16_64 },
  LOAD( ROM2, "ggw.01", 0x00000, 0x20000, 0x4c6351d5),
  LOAD_SW16( SMP1, "ggw.11m", 0x000000, 0x400000, 0xe172acf5),
  LOAD_SW16( SMP1, "ggw.12m", 0x400000, 0x400000, 0x4bee4e8f),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_gigawingj[] = // clone of gigawing
{
  LOAD_SW16( CPU1, "ggwj.03a", 0x000000, 0x80000, 0xfdd23b91),
  LOAD_SW16( CPU1, "ggwj.04a", 0x080000, 0x80000, 0x8c6e093c),
  LOAD_SW16( CPU1, "ggwj.05a", 0x100000, 0x80000, 0x43811454),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_gigawinga[] = // clone of gigawing
{
  LOAD_SW16( CPU1, "ggwa.03a", 0x000000, 0x80000, 0x116f8837),
  LOAD_SW16( CPU1, "ggwa.04a", 0x080000, 0x80000, 0xe6e3f0c4),
  LOAD_SW16( CPU1, "ggwa.05a", 0x100000, 0x80000, 0x465e8ac9),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_gigawingh[] = // clone of gigawing
{
  LOAD_SW16( CPU1, "ggwh.03a", 0x000000, 0x80000, 0xb9ee36eb),
  LOAD_SW16( CPU1, "ggwh.04a", 0x080000, 0x80000, 0x72e548fe),
  LOAD_SW16( CPU1, "ggw.05", 0x100000, 0x80000, 0x3239d642),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_gigawingb[] = // clone of gigawing
{
  LOAD_SW16( CPU1, "ggwb.03", 0x000000, 0x80000, 0xa1f8a448),
  LOAD_SW16( CPU1, "ggwb.04", 0x080000, 0x80000, 0x6a423e76),
  LOAD_SW16( CPU1, "ggw.05", 0x100000, 0x80000, 0x3239d642),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_hsf2[] =
{
  LOAD_SW16( CPU1, "hs2u.03", 0x000000, 0x80000, 0xb308151e),
  LOAD_SW16( CPU1, "hs2u.04", 0x080000, 0x80000, 0x327aa49c),
  LOAD_SW16( CPU1, "hs2.05", 0x100000, 0x80000, 0xdde34a35),
  LOAD_SW16( CPU1, "hs2.06", 0x180000, 0x80000, 0xf4e56dda),
  LOAD_SW16( CPU1, "hs2.07", 0x200000, 0x80000, 0xee4420fc),
  LOAD_SW16( CPU1, "hs2.08", 0x280000, 0x80000, 0xc9441533),
  LOAD_SW16( CPU1, "hs2.09", 0x300000, 0x80000, 0x3fc638a8),
  LOAD_SW16( CPU1, "hs2.10", 0x380000, 0x80000, 0x20d0f9e4),
  { "hs2.13m", 0x800000, 0xa6ecab17, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "hs2.15m", 0x800000, 0x10a0ae4d, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "hs2.17m", 0x800000, 0xadfa7726, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "hs2.19m", 0x800000, 0xbb3ae322, REGION_GFX1, 0x0000006, LOAD_16_64 },
  LOAD( ROM2, "hs2.01", 0x00000, 0x20000, 0xc1a13786),
  LOAD( ROM2, "hs2.02", 0x20000, 0x20000, 0x2d8794aa),
  LOAD_SW16( SMP1, "hs2.11m", 0x000000, 0x800000, 0x0e15c359),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_hsf2a[] = // clone of hsf2
{
  LOAD_SW16( CPU1, "hs2a.03", 0x000000, 0x80000, 0xd50a17e0),
  LOAD_SW16( CPU1, "hs2a.04", 0x080000, 0x80000, 0xa27f42de),
  LOAD_SW16( CPU1, "hs2.05", 0x100000, 0x80000, 0xdde34a35),
  LOAD_SW16( CPU1, "hs2.06", 0x180000, 0x80000, 0xf4e56dda),
  LOAD_SW16( CPU1, "hs2.07", 0x200000, 0x80000, 0xee4420fc),
  LOAD_SW16( CPU1, "hs2.08", 0x280000, 0x80000, 0xc9441533),
  LOAD_SW16( CPU1, "hs2.09", 0x300000, 0x80000, 0x3fc638a8),
  LOAD_SW16( CPU1, "hs2.10", 0x380000, 0x80000, 0x20d0f9e4),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_hsf2j[] = // clone of hsf2
{
  LOAD_SW16( CPU1, "hs2j.03", 0x000000, 0x80000, 0x00738f73),
  LOAD_SW16( CPU1, "hs2j.04", 0x080000, 0x80000, 0x40072c4a),
  LOAD_SW16( CPU1, "hs2.05", 0x100000, 0x80000, 0xdde34a35),
  LOAD_SW16( CPU1, "hs2.06", 0x180000, 0x80000, 0xf4e56dda),
  LOAD_SW16( CPU1, "hs2.07", 0x200000, 0x80000, 0xee4420fc),
  LOAD_SW16( CPU1, "hs2.08", 0x280000, 0x80000, 0xc9441533),
  LOAD_SW16( CPU1, "hs2.09", 0x300000, 0x80000, 0x3fc638a8),
  LOAD_SW16( CPU1, "hs2.10", 0x380000, 0x80000, 0x20d0f9e4),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_jyangoku[] =
{
  LOAD_SW16( CPU1, "majj.03", 0x000000, 0x80000, 0x4614a3b2),
  { "maj1_d.simm1", 0x200000, 0xba0fe27b, REGION_GFX1, 0x0000000, LOAD_8_64 },
  { "maj1_c.simm1", 0x200000, 0x2cd141bf, REGION_GFX1, 0x0000001, LOAD_8_64 },
  { "maj1_b.simm1", 0x200000, 0xe29e4c26, REGION_GFX1, 0x0000002, LOAD_8_64 },
  { "maj1_a.simm1", 0x200000, 0x7f68b88a, REGION_GFX1, 0x0000003, LOAD_8_64 },
  { "maj3_d.simm3", 0x200000, 0x3aaeb90b, REGION_GFX1, 0x0000004, LOAD_8_64 },
  { "maj3_c.simm3", 0x200000, 0x97894cea, REGION_GFX1, 0x0000005, LOAD_8_64 },
  { "maj3_b.simm3", 0x200000, 0xec737d9d, REGION_GFX1, 0x0000006, LOAD_8_64 },
  { "maj3_a.simm3", 0x200000, 0xc23b6f22, REGION_GFX1, 0x0000007, LOAD_8_64 },
  LOAD( ROM2, "maj.01", 0x00000, 0x20000, 0x1fe8c213),
  LOAD_16_8( SMP1, "maj5_a.simm5", 0x000000, 0x200000, 0x5ad9ee53),
  LOAD_16_8( SMP1, "maj5_b.simm5", 0x000001, 0x200000, 0xefb3dbfb),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_megaman2[] =
{
  LOAD_SW16( CPU1, "rm2u.03", 0x000000, 0x80000, 0x8ffc2cd1),
  LOAD_SW16( CPU1, "rm2u.04", 0x080000, 0x80000, 0xbb30083a),
  LOAD_SW16( CPU1, "rm2.05", 0x100000, 0x80000, 0x02ee9efc),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { "rm2.14m", 0x200000, 0x9b1f00b4, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "rm2.16m", 0x200000, 0xc2bb0c24, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "rm2.18m", 0x200000, 0x12257251, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "rm2.20m", 0x200000, 0xf9b6e786, REGION_GFX1, 0x800006, LOAD_16_64 },
  LOAD( ROM2, "rm2.01a", 0x00000, 0x20000, 0xd18e7859),
  LOAD( ROM2, "rm2.02", 0x20000, 0x20000, 0xc463ece0),
  LOAD_SW16( SMP1, "rm2.11m", 0x000000, 0x200000, 0x2106174d),
  LOAD_SW16( SMP1, "rm2.12m", 0x200000, 0x200000, 0x546c1636),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_megaman2a[] = // clone of megaman2
{
  LOAD_SW16( CPU1, "rm2a.03", 0x000000, 0x80000, 0x2b330ca7),
  LOAD_SW16( CPU1, "rm2a.04", 0x080000, 0x80000, 0x8b47942b),
  LOAD_SW16( CPU1, "rm2.05", 0x100000, 0x80000, 0x02ee9efc),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_rockman2j[] = // clone of megaman2
{
  LOAD_SW16( CPU1, "rm2j.03", 0x000000, 0x80000, 0xdbaa1437),
  LOAD_SW16( CPU1, "rm2j.04", 0x080000, 0x80000, 0xcf5ba612),
  LOAD_SW16( CPU1, "rm2.05", 0x100000, 0x80000, 0x02ee9efc),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_megaman2h[] = // clone of megaman2
{
  LOAD_SW16( CPU1, "rm2h.03", 0x000000, 0x80000, 0xbb180378),
  LOAD_SW16( CPU1, "rm2h.04", 0x080000, 0x80000, 0x205ffcd6),
  LOAD_SW16( CPU1, "rm2.05", 0x100000, 0x80000, 0x02ee9efc),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

#if 0
// for now it doesn't work anyway !
static struct OKIM6295interface oki_gigaman2 =
{
	1,  /* 1 chip */
	{ 1061 }, // ???
	{ REGION_SMP1 },
	{ 100 }
};

static struct SOUND_INFO sound_gigaman2[] =
{
   { SOUND_M6295, &oki_gigaman2     },
   { 0,              NULL,                 },
};
#endif

static struct ROM_INFO rom_gigaman2[] = // clone of megaman2
{
  LOAD_SW16( CPU1, "sys_rom1.bin", 0x000000, 0x400000, 0x2eaa5e10),
  { REGION_EMPTY, 0, 0 , REGION_ROM2, 0, LOAD_NORMAL },
  LOAD( GFX1, "cg_rom1.bin", 0x0000000, 0x400000, 0xed55a641),
  { "cg_rom1.bin", 0x400000, 0xed55a641, REGION_GFX1, 0x0800000, LOAD_CONTINUE },
  LOAD( GFX1, "cg_rom2.bin", 0x0400000, 0x400000, 0x63918c05),
  { "cg_rom2.bin", 0x400000, 0x63918c05, REGION_GFX1, 0x0c00000, LOAD_CONTINUE },
	/* No Qsound, OKI instead.. */
  LOAD( SMP1, "pcm_rom1.bin", 0x000000, 0x800000, 0x41a854ab),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mmatrix[] =
{
  LOAD_SW16( CPU1, "mmxu.03", 0x000000, 0x80000, 0xab65b599),
  LOAD_SW16( CPU1, "mmxu.04", 0x080000, 0x80000, 0x0135fc6c),
  LOAD_SW16( CPU1, "mmxu.05", 0x100000, 0x80000, 0xf1fd2b84),
  { "mmx.13m", 0x400000, 0x04748718, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "mmx.15m", 0x400000, 0x38074f44, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "mmx.17m", 0x400000, 0xe4635e35, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "mmx.19m", 0x400000, 0x4400a3f2, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "mmx.14m", 0x400000, 0xd52bf491, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "mmx.16m", 0x400000, 0x23f70780, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "mmx.18m", 0x400000, 0x2562c9d5, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "mmx.20m", 0x400000, 0x583a9687, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "mmx.01", 0x00000, 0x20000, 0xc57e8171),
  LOAD_SW16( SMP1, "mmx.11m", 0x000000, 0x400000, 0x4180b39f),
  LOAD_SW16( SMP1, "mmx.12m", 0x400000, 0x400000, 0x95e22a59),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mmatrixj[] = // clone of mmatrix
{
  LOAD_SW16( CPU1, "mmxj.03", 0x000000, 0x80000, 0x1d5de213),
  LOAD_SW16( CPU1, "mmxj.04", 0x080000, 0x80000, 0xd943a339),
  LOAD_SW16( CPU1, "mmxj.05", 0x100000, 0x80000, 0x0c8b4abb),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_msh[] =
{
  LOAD_SW16( CPU1, "mshe.03e", 0x000000, 0x80000, 0xbd951414),
  LOAD_SW16( CPU1, "mshe.04e", 0x080000, 0x80000, 0x19dd42f2),
  LOAD_SW16( CPU1, "msh.05", 0x100000, 0x80000, 0x6a091b9e),
  LOAD_SW16( CPU1, "msh.06b", 0x180000, 0x80000, 0x803e3fa4),
  LOAD_SW16( CPU1, "msh.07a", 0x200000, 0x80000, 0xc45f8e27),
  LOAD_SW16( CPU1, "msh.08a", 0x280000, 0x80000, 0x9ca6f12c),
  LOAD_SW16( CPU1, "msh.09a", 0x300000, 0x80000, 0x82ec27af),
  LOAD_SW16( CPU1, "msh.10b", 0x380000, 0x80000, 0x8d931196),
  { "msh.13m", 0x400000, 0x09d14566, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "msh.15m", 0x400000, 0xee962057, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "msh.17m", 0x400000, 0x604ece14, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "msh.19m", 0x400000, 0x94a731e8, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "msh.14m", 0x400000, 0x4197973e, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "msh.16m", 0x400000, 0x438da4a0, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "msh.18m", 0x400000, 0x4db92d94, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "msh.20m", 0x400000, 0xa2b0c6c0, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "msh.01", 0x00000, 0x20000, 0xc976e6f9),
  LOAD( ROM2, "msh.02", 0x20000, 0x20000, 0xce67d0d9),
  LOAD_SW16( SMP1, "msh.11m", 0x000000, 0x200000, 0x37ac6d30),
  LOAD_SW16( SMP1, "msh.12m", 0x200000, 0x200000, 0xde092570),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshu[] = // clone of msh
{
  LOAD_SW16( CPU1, "mshu.03", 0x000000, 0x80000, 0xd2805bdd),
  LOAD_SW16( CPU1, "mshu.04", 0x080000, 0x80000, 0x743f96ff),
  LOAD_SW16( CPU1, "msh.05", 0x100000, 0x80000, 0x6a091b9e),
  LOAD_SW16( CPU1, "msh.06b", 0x180000, 0x80000, 0x803e3fa4),
  LOAD_SW16( CPU1, "msh.07a", 0x200000, 0x80000, 0xc45f8e27),
  LOAD_SW16( CPU1, "msh.08a", 0x280000, 0x80000, 0x9ca6f12c),
  LOAD_SW16( CPU1, "msh.09a", 0x300000, 0x80000, 0x82ec27af),
  LOAD_SW16( CPU1, "msh.10b", 0x380000, 0x80000, 0x8d931196),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshj[] = // clone of msh
{
  LOAD_SW16( CPU1, "mshj.03g", 0x000000, 0x80000, 0x261f4091),
  LOAD_SW16( CPU1, "mshj.04g", 0x080000, 0x80000, 0x61d791c6),
  LOAD_SW16( CPU1, "msh.05a", 0x100000, 0x80000, 0xf37539e6),
  LOAD_SW16( CPU1, "msh.06b", 0x180000, 0x80000, 0x803e3fa4),
  LOAD_SW16( CPU1, "msh.07a", 0x200000, 0x80000, 0xc45f8e27),
  LOAD_SW16( CPU1, "msh.08a", 0x280000, 0x80000, 0x9ca6f12c),
  LOAD_SW16( CPU1, "msh.09a", 0x300000, 0x80000, 0x82ec27af),
  LOAD_SW16( CPU1, "msh.10b", 0x380000, 0x80000, 0x8d931196),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshjr1[] = // clone of msh
{
  LOAD_SW16( CPU1, "mshj.03f", 0x000000, 0x80000, 0xff172fd2),
  LOAD_SW16( CPU1, "mshj.04f", 0x080000, 0x80000, 0xebbb205a),
  LOAD_SW16( CPU1, "msh.05", 0x100000, 0x80000, 0x6a091b9e),
  LOAD_SW16( CPU1, "msh.06b", 0x180000, 0x80000, 0x803e3fa4),
  LOAD_SW16( CPU1, "msh.07a", 0x200000, 0x80000, 0xc45f8e27),
  LOAD_SW16( CPU1, "msh.08a", 0x280000, 0x80000, 0x9ca6f12c),
  LOAD_SW16( CPU1, "msh.09a", 0x300000, 0x80000, 0x82ec27af),
  LOAD_SW16( CPU1, "msh.10b", 0x380000, 0x80000, 0x8d931196),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_msha[] = // clone of msh
{
  LOAD_SW16( CPU1, "msha.03e", 0x000000, 0x80000, 0xec84ec44),
  LOAD_SW16( CPU1, "msha.04e", 0x080000, 0x80000, 0x098b8503),
  LOAD_SW16( CPU1, "msh.05", 0x100000, 0x80000, 0x6a091b9e),
  LOAD_SW16( CPU1, "msh.06b", 0x180000, 0x80000, 0x803e3fa4),
  LOAD_SW16( CPU1, "msh.07a", 0x200000, 0x80000, 0xc45f8e27),
  LOAD_SW16( CPU1, "msh.08a", 0x280000, 0x80000, 0x9ca6f12c),
  LOAD_SW16( CPU1, "msh.09a", 0x300000, 0x80000, 0x82ec27af),
  LOAD_SW16( CPU1, "msh.10b", 0x380000, 0x80000, 0x8d931196),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshh[] = // clone of msh
{
  LOAD_SW16( CPU1, "mshh.03c", 0x000000, 0x80000, 0x8d84b0fa),
  LOAD_SW16( CPU1, "mshh.04c", 0x080000, 0x80000, 0xd638f601),
  LOAD_SW16( CPU1, "msh.05a", 0x100000, 0x80000, 0xf37539e6),
  LOAD_SW16( CPU1, "msh.06b", 0x180000, 0x80000, 0x803e3fa4),
  LOAD_SW16( CPU1, "msh.07a", 0x200000, 0x80000, 0xc45f8e27),
  LOAD_SW16( CPU1, "msh.08a", 0x280000, 0x80000, 0x9ca6f12c),
  LOAD_SW16( CPU1, "msh.09a", 0x300000, 0x80000, 0x82ec27af),
  LOAD_SW16( CPU1, "msh.10b", 0x380000, 0x80000, 0x8d931196),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshb[] = // clone of msh
{
  LOAD_SW16( CPU1, "mshb.03c", 0x000000, 0x80000, 0x19697f74),
  LOAD_SW16( CPU1, "mshb.04c", 0x080000, 0x80000, 0x95317a6f),
  LOAD_SW16( CPU1, "msh.05a", 0x100000, 0x80000, 0xf37539e6),
  LOAD_SW16( CPU1, "msh.06b", 0x180000, 0x80000, 0x803e3fa4),
  LOAD_SW16( CPU1, "msh.07a", 0x200000, 0x80000, 0xc45f8e27),
  LOAD_SW16( CPU1, "msh.08a", 0x280000, 0x80000, 0x9ca6f12c),
  LOAD_SW16( CPU1, "msh.09a", 0x300000, 0x80000, 0x82ec27af),
  LOAD_SW16( CPU1, "msh.10b", 0x380000, 0x80000, 0x8d931196),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshvsf[] =
{
  LOAD_SW16( CPU1, "mvse.03f", 0x000000, 0x80000, 0xb72dc199),
  LOAD_SW16( CPU1, "mvse.04f", 0x080000, 0x80000, 0x6ef799f9),
  LOAD_SW16( CPU1, "mvs.05a", 0x100000, 0x80000, 0x1a5de0cb),
  LOAD_SW16( CPU1, "mvs.06a", 0x180000, 0x80000, 0x959f3030),
  LOAD_SW16( CPU1, "mvs.07b", 0x200000, 0x80000, 0x7f915bdb),
  LOAD_SW16( CPU1, "mvs.08a", 0x280000, 0x80000, 0xc2813884),
  LOAD_SW16( CPU1, "mvs.09b", 0x300000, 0x80000, 0x3ba08818),
  LOAD_SW16( CPU1, "mvs.10b", 0x380000, 0x80000, 0xcf0dba98),
  { "mvs.13m", 0x400000, 0x29b05fd9, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "mvs.15m", 0x400000, 0xfaddccf1, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "mvs.17m", 0x400000, 0x97aaf4c7, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "mvs.19m", 0x400000, 0xcb70e915, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "mvs.14m", 0x400000, 0xb3b1972d, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "mvs.16m", 0x400000, 0x08aadb5d, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "mvs.18m", 0x400000, 0xc1228b35, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "mvs.20m", 0x400000, 0x366cc6c2, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "mvs.01", 0x00000, 0x20000, 0x68252324),
  LOAD( ROM2, "mvs.02", 0x20000, 0x20000, 0xb34e773d),
  LOAD_SW16( SMP1, "mvs.11m", 0x000000, 0x400000, 0x86219770),
  LOAD_SW16( SMP1, "mvs.12m", 0x400000, 0x400000, 0xf2fd7f68),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshvsfu[] = // clone of mshvsf
{
  LOAD_SW16( CPU1, "mvsu.03g", 0x000000, 0x80000, 0x0664ab15),
  LOAD_SW16( CPU1, "mvsu.04g", 0x080000, 0x80000, 0x97e060ee),
  LOAD_SW16( CPU1, "mvs.05d", 0x100000, 0x80000, 0x921fc542),
  LOAD_SW16( CPU1, "mvs.06a", 0x180000, 0x80000, 0x959f3030),
  LOAD_SW16( CPU1, "mvs.07b", 0x200000, 0x80000, 0x7f915bdb),
  LOAD_SW16( CPU1, "mvs.08a", 0x280000, 0x80000, 0xc2813884),
  LOAD_SW16( CPU1, "mvs.09b", 0x300000, 0x80000, 0x3ba08818),
  LOAD_SW16( CPU1, "mvs.10b", 0x380000, 0x80000, 0xcf0dba98),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshvsfu1[] = // clone of mshvsf
{
  LOAD_SW16( CPU1, "mvsu.03d", 0x000000, 0x80000, 0xae60a66a),
  LOAD_SW16( CPU1, "mvsu.04d", 0x080000, 0x80000, 0x91f67d8a),
  LOAD_SW16( CPU1, "mvs.05a", 0x100000, 0x80000, 0x1a5de0cb),
  LOAD_SW16( CPU1, "mvs.06a", 0x180000, 0x80000, 0x959f3030),
  LOAD_SW16( CPU1, "mvs.07b", 0x200000, 0x80000, 0x7f915bdb),
  LOAD_SW16( CPU1, "mvs.08a", 0x280000, 0x80000, 0xc2813884),
  LOAD_SW16( CPU1, "mvs.09b", 0x300000, 0x80000, 0x3ba08818),
  LOAD_SW16( CPU1, "mvs.10b", 0x380000, 0x80000, 0xcf0dba98),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshvsfj[] = // clone of mshvsf
{
  LOAD_SW16( CPU1, "mvsj.03i", 0x000000, 0x80000, 0xd8cbb691),
  LOAD_SW16( CPU1, "mvsj.04i", 0x080000, 0x80000, 0x32741ace),
  LOAD_SW16( CPU1, "mvs.05h", 0x100000, 0x80000, 0x77870dc3),
  LOAD_SW16( CPU1, "mvs.06a", 0x180000, 0x80000, 0x959f3030),
  LOAD_SW16( CPU1, "mvs.07b", 0x200000, 0x80000, 0x7f915bdb),
  LOAD_SW16( CPU1, "mvs.08a", 0x280000, 0x80000, 0xc2813884),
  LOAD_SW16( CPU1, "mvs.09b", 0x300000, 0x80000, 0x3ba08818),
  LOAD_SW16( CPU1, "mvs.10b", 0x380000, 0x80000, 0xcf0dba98),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshvsfj1[] = // clone of mshvsf
{
  LOAD_SW16( CPU1, "mvsj.03h", 0x000000, 0x80000, 0xfbe2115f),
  LOAD_SW16( CPU1, "mvsj.04h", 0x080000, 0x80000, 0xb528a367),
  LOAD_SW16( CPU1, "mvs.05g", 0x100000, 0x80000, 0x9515a245),
  LOAD_SW16( CPU1, "mvs.06a", 0x180000, 0x80000, 0x959f3030),
  LOAD_SW16( CPU1, "mvs.07b", 0x200000, 0x80000, 0x7f915bdb),
  LOAD_SW16( CPU1, "mvs.08a", 0x280000, 0x80000, 0xc2813884),
  LOAD_SW16( CPU1, "mvs.09b", 0x300000, 0x80000, 0x3ba08818),
  LOAD_SW16( CPU1, "mvs.10b", 0x380000, 0x80000, 0xcf0dba98),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshvsfj2[] = // clone of mshvsf
{
  LOAD_SW16( CPU1, "mvsj.03g", 0x000000, 0x80000, 0xfdfa7e26),
  LOAD_SW16( CPU1, "mvsj.04g", 0x080000, 0x80000, 0xc921825f),
  LOAD_SW16( CPU1, "mvs.05a", 0x100000, 0x80000, 0x1a5de0cb),
  LOAD_SW16( CPU1, "mvs.06a", 0x180000, 0x80000, 0x959f3030),
  LOAD_SW16( CPU1, "mvs.07b", 0x200000, 0x80000, 0x7f915bdb),
  LOAD_SW16( CPU1, "mvs.08a", 0x280000, 0x80000, 0xc2813884),
  LOAD_SW16( CPU1, "mvs.09b", 0x300000, 0x80000, 0x3ba08818),
  LOAD_SW16( CPU1, "mvs.10b", 0x380000, 0x80000, 0xcf0dba98),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshvsfh[] = // clone of mshvsf
{
  LOAD_SW16( CPU1, "mvsh.03f", 0x000000, 0x80000, 0x4f60f41e),
  LOAD_SW16( CPU1, "mvsh.04f", 0x080000, 0x80000, 0xdc08ec12),
  LOAD_SW16( CPU1, "mvs.05a", 0x100000, 0x80000, 0x1a5de0cb),
  LOAD_SW16( CPU1, "mvs.06a", 0x180000, 0x80000, 0x959f3030),
  LOAD_SW16( CPU1, "mvs.07b", 0x200000, 0x80000, 0x7f915bdb),
  LOAD_SW16( CPU1, "mvs.08a", 0x280000, 0x80000, 0xc2813884),
  LOAD_SW16( CPU1, "mvs.09b", 0x300000, 0x80000, 0x3ba08818),
  LOAD_SW16( CPU1, "mvs.10b", 0x380000, 0x80000, 0xcf0dba98),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshvsfa[] = // clone of mshvsf
{
  LOAD_SW16( CPU1, "mvsa.03f", 0x000000, 0x80000, 0x5b863716),
  LOAD_SW16( CPU1, "mvsa.04f", 0x080000, 0x80000, 0x4886e65f),
  LOAD_SW16( CPU1, "mvs.05a", 0x100000, 0x80000, 0x1a5de0cb),
  LOAD_SW16( CPU1, "mvs.06a", 0x180000, 0x80000, 0x959f3030),
  LOAD_SW16( CPU1, "mvs.07b", 0x200000, 0x80000, 0x7f915bdb),
  LOAD_SW16( CPU1, "mvs.08a", 0x280000, 0x80000, 0xc2813884),
  LOAD_SW16( CPU1, "mvs.09b", 0x300000, 0x80000, 0x3ba08818),
  LOAD_SW16( CPU1, "mvs.10b", 0x380000, 0x80000, 0xcf0dba98),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshvsfa1[] = // clone of mshvsf
{
  LOAD_SW16( CPU1, "mvsa.03", 0x000000, 0x80000, 0x92ef1933),
  LOAD_SW16( CPU1, "mvsa.04", 0x080000, 0x80000, 0x4b24373c),
  LOAD_SW16( CPU1, "mvs.05", 0x100000, 0x80000, 0xac180c1c),
  LOAD_SW16( CPU1, "mvs.06a", 0x180000, 0x80000, 0x959f3030),
  LOAD_SW16( CPU1, "mvs.07b", 0x200000, 0x80000, 0x7f915bdb),
  LOAD_SW16( CPU1, "mvs.08a", 0x280000, 0x80000, 0xc2813884),
  LOAD_SW16( CPU1, "mvs.09b", 0x300000, 0x80000, 0x3ba08818),
  LOAD_SW16( CPU1, "mvs.10b", 0x380000, 0x80000, 0xcf0dba98),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshvsfb[] = // clone of mshvsf
{
  LOAD_SW16( CPU1, "mvsb.03g", 0x000000, 0x80000, 0x143895ef),
  LOAD_SW16( CPU1, "mvsb.04g", 0x080000, 0x80000, 0xdd8a886c),
  LOAD_SW16( CPU1, "mvs.05d", 0x100000, 0x80000, 0x921fc542),
  LOAD_SW16( CPU1, "mvs.06a", 0x180000, 0x80000, 0x959f3030),
  LOAD_SW16( CPU1, "mvs.07b", 0x200000, 0x80000, 0x7f915bdb),
  LOAD_SW16( CPU1, "mvs.08a", 0x280000, 0x80000, 0xc2813884),
  LOAD_SW16( CPU1, "mvs.09b", 0x300000, 0x80000, 0x3ba08818),
  LOAD_SW16( CPU1, "mvs.10b", 0x380000, 0x80000, 0xcf0dba98),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshvsfb1[] = // clone of mshvsf
{
  LOAD_SW16( CPU1, "mvsb.03f", 0x000000, 0x80000, 0x9c4bb950),
  LOAD_SW16( CPU1, "mvsb.04f", 0x080000, 0x80000, 0xd3320d13),
  LOAD_SW16( CPU1, "mvs.05a", 0x100000, 0x80000, 0x1a5de0cb),
  LOAD_SW16( CPU1, "mvs.06a", 0x180000, 0x80000, 0x959f3030),
  LOAD_SW16( CPU1, "mvs.07b", 0x200000, 0x80000, 0x7f915bdb),
  LOAD_SW16( CPU1, "mvs.08a", 0x280000, 0x80000, 0xc2813884),
  LOAD_SW16( CPU1, "mvs.09b", 0x300000, 0x80000, 0x3ba08818),
  LOAD_SW16( CPU1, "mvs.10b", 0x380000, 0x80000, 0xcf0dba98),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mvsc[] =
{
//  ROM_LOAD16_WORD_SWAP( "mvce.04a", 0x080000, 0x80000, BAD_DUMP CRC(cac02153) SHA1(ee9f9da6fda53f21ba7b74367612c90281269690) )
  LOAD_SW16( CPU1, "mvce.03a", 0x000000, 0x80000, 0x824e4a90),
  LOAD_SW16( CPU1, "mvce.04a", 0x080000, 0x80000, 0x436c5a4e),
  LOAD_SW16( CPU1, "mvc.05a", 0x100000, 0x80000, 0x2d8c8e86),
  LOAD_SW16( CPU1, "mvc.06a", 0x180000, 0x80000, 0x8528e1f5),
  LOAD_SW16( CPU1, "mvc.07", 0x200000, 0x80000, 0xc3baa32b),
  LOAD_SW16( CPU1, "mvc.08", 0x280000, 0x80000, 0xbc002fcd),
  LOAD_SW16( CPU1, "mvc.09", 0x300000, 0x80000, 0xc67b26df),
  LOAD_SW16( CPU1, "mvc.10", 0x380000, 0x80000, 0x0fdd1e26),
  { "mvc.13m", 0x400000, 0xfa5f74bc, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "mvc.15m", 0x400000, 0x71938a8f, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "mvc.17m", 0x400000, 0x92741d07, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "mvc.19m", 0x400000, 0xbcb72fc6, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "mvc.14m", 0x400000, 0x7f1df4e4, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "mvc.16m", 0x400000, 0x90bd3203, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "mvc.18m", 0x400000, 0x67aaf727, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "mvc.20m", 0x400000, 0x8b0bade8, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "mvc.01", 0x00000, 0x20000, 0x41629e95),
  LOAD( ROM2, "mvc.02", 0x20000, 0x20000, 0x963abf6b),
  LOAD_SW16( SMP1, "mvc.11m", 0x000000, 0x400000, 0x850fe663),
  LOAD_SW16( SMP1, "mvc.12m", 0x400000, 0x400000, 0x7ccb1896),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mvscr1[] = // clone of mvsc
{
  LOAD_SW16( CPU1, "mvce.03", 0x000000, 0x80000, 0xe0633fc0),
  LOAD_SW16( CPU1, "mvce.04", 0x080000, 0x80000, 0xa450a251),
  LOAD_SW16( CPU1, "mvc.05", 0x100000, 0x80000, 0x7db71ce9),
  LOAD_SW16( CPU1, "mvc.06", 0x180000, 0x80000, 0x4b0b6d3e),
  LOAD_SW16( CPU1, "mvc.07", 0x200000, 0x80000, 0xc3baa32b),
  LOAD_SW16( CPU1, "mvc.08", 0x280000, 0x80000, 0xbc002fcd),
  LOAD_SW16( CPU1, "mvc.09", 0x300000, 0x80000, 0xc67b26df),
  LOAD_SW16( CPU1, "mvc.10", 0x380000, 0x80000, 0x0fdd1e26),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mvscu[] = // clone of mvsc
{
  LOAD_SW16( CPU1, "mvcu.03d", 0x000000, 0x80000, 0xc6007557),
  LOAD_SW16( CPU1, "mvcu.04d", 0x080000, 0x80000, 0x724b2b20),
  LOAD_SW16( CPU1, "mvc.05a", 0x100000, 0x80000, 0x2d8c8e86),
  LOAD_SW16( CPU1, "mvc.06a", 0x180000, 0x80000, 0x8528e1f5),
  LOAD_SW16( CPU1, "mvc.07", 0x200000, 0x80000, 0xc3baa32b),
  LOAD_SW16( CPU1, "mvc.08", 0x280000, 0x80000, 0xbc002fcd),
  LOAD_SW16( CPU1, "mvc.09", 0x300000, 0x80000, 0xc67b26df),
  LOAD_SW16( CPU1, "mvc.10", 0x380000, 0x80000, 0x0fdd1e26),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mvscur1[] = // clone of mvsc
{
  LOAD_SW16( CPU1, "mvcu.03", 0x000000, 0x80000, 0x13f2be57),
  LOAD_SW16( CPU1, "mvcu.04", 0x080000, 0x80000, 0x5e9b380d),
  LOAD_SW16( CPU1, "mvcu.05", 0x100000, 0x80000, 0x12f321be),
  LOAD_SW16( CPU1, "mvcu.06", 0x180000, 0x80000, 0x2f1524bc),
  LOAD_SW16( CPU1, "mvcu.07", 0x200000, 0x80000, 0x5fdecadb),
  LOAD_SW16( CPU1, "mvc.08", 0x280000, 0x80000, 0xbc002fcd),
  LOAD_SW16( CPU1, "mvc.09", 0x300000, 0x80000, 0xc67b26df),
  LOAD_SW16( CPU1, "mvcu.10", 0x380000, 0x80000, 0x4f36cd63),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mvscj[] = // clone of mvsc
{
  LOAD_SW16( CPU1, "mvcj.03a", 0x000000, 0x80000, 0x3df18879),
  LOAD_SW16( CPU1, "mvcj.04a", 0x080000, 0x80000, 0x07d212e8),
  LOAD_SW16( CPU1, "mvc.05a", 0x100000, 0x80000, 0x2d8c8e86),
  LOAD_SW16( CPU1, "mvc.06a", 0x180000, 0x80000, 0x8528e1f5),
  LOAD_SW16( CPU1, "mvc.07", 0x200000, 0x80000, 0xc3baa32b),
  LOAD_SW16( CPU1, "mvc.08", 0x280000, 0x80000, 0xbc002fcd),
  LOAD_SW16( CPU1, "mvc.09", 0x300000, 0x80000, 0xc67b26df),
  LOAD_SW16( CPU1, "mvc.10", 0x380000, 0x80000, 0x0fdd1e26),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mvscjr1[] = // clone of mvsc
{
  LOAD_SW16( CPU1, "mvcj.03", 0x000000, 0x80000, 0x2164213f),
  LOAD_SW16( CPU1, "mvcj.04", 0x080000, 0x80000, 0xc905c86f),
  LOAD_SW16( CPU1, "mvc.05", 0x100000, 0x80000, 0x7db71ce9),
  LOAD_SW16( CPU1, "mvc.06", 0x180000, 0x80000, 0x4b0b6d3e),
  LOAD_SW16( CPU1, "mvc.07", 0x200000, 0x80000, 0xc3baa32b),
  LOAD_SW16( CPU1, "mvc.08", 0x280000, 0x80000, 0xbc002fcd),
  LOAD_SW16( CPU1, "mvc.09", 0x300000, 0x80000, 0xc67b26df),
  LOAD_SW16( CPU1, "mvc.10", 0x380000, 0x80000, 0x0fdd1e26),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mvscjsing[] = // clone of mvsc
{
  LOAD_16_8( CPU1, "mvc_ja.simm1", 0x000000, 0x200000, 0x6a2ef7c2),
  LOAD_16_8( CPU1, "mvc_ja.simm3", 0x000001, 0x200000, 0x699d09ad),
  { "mvc64-13m.13", 0x800000, 0x8428ce69, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "mvc64-15m.15", 0x800000, 0x2e0028f4, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "mvc64-17m.17", 0x800000, 0x308ca826, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "mvc64-19m.19", 0x800000, 0x10699fe1, REGION_GFX1, 0x0000006, LOAD_16_64 },
  LOAD_SW16( SMP1, "mvc64-11m.11", 0x000000, 0x800000, 0x5d8819e0),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mvsca[] = // clone of mvsc
{
  LOAD_SW16( CPU1, "mvca.03a", 0x000000, 0x80000, 0x2ff4ae25),
  LOAD_SW16( CPU1, "mvca.04a", 0x080000, 0x80000, 0xf28427ef),
  LOAD_SW16( CPU1, "mvc.05a", 0x100000, 0x80000, 0x2d8c8e86),
  LOAD_SW16( CPU1, "mvc.06a", 0x180000, 0x80000, 0x8528e1f5),
  LOAD_SW16( CPU1, "mvc.07", 0x200000, 0x80000, 0xc3baa32b),
  LOAD_SW16( CPU1, "mvc.08", 0x280000, 0x80000, 0xbc002fcd),
  LOAD_SW16( CPU1, "mvc.09", 0x300000, 0x80000, 0xc67b26df),
  LOAD_SW16( CPU1, "mvc.10", 0x380000, 0x80000, 0x0fdd1e26),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mvscar1[] = // clone of mvsc
{
  LOAD_SW16( CPU1, "mvca.03", 0x000000, 0x80000, 0xfe5fa7b9),
  LOAD_SW16( CPU1, "mvca.04", 0x080000, 0x80000, 0x082b701c),
  LOAD_SW16( CPU1, "mvc.05", 0x100000, 0x80000, 0x7db71ce9),
  LOAD_SW16( CPU1, "mvc.06", 0x180000, 0x80000, 0x4b0b6d3e),
  LOAD_SW16( CPU1, "mvc.07", 0x200000, 0x80000, 0xc3baa32b),
  LOAD_SW16( CPU1, "mvc.08", 0x280000, 0x80000, 0xbc002fcd),
  LOAD_SW16( CPU1, "mvc.09", 0x300000, 0x80000, 0xc67b26df),
  LOAD_SW16( CPU1, "mvc.10", 0x380000, 0x80000, 0x0fdd1e26),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mvsch[] = // clone of mvsc
{
  LOAD_SW16( CPU1, "mvch.03", 0x000000, 0x80000, 0x6a0ec9f7),
  LOAD_SW16( CPU1, "mvch.04", 0x080000, 0x80000, 0x00f03fa4),
  LOAD_SW16( CPU1, "mvc.05a", 0x100000, 0x80000, 0x2d8c8e86),
  LOAD_SW16( CPU1, "mvc.06a", 0x180000, 0x80000, 0x8528e1f5),
  LOAD_SW16( CPU1, "mvc.07", 0x200000, 0x80000, 0xc3baa32b),
  LOAD_SW16( CPU1, "mvc.08", 0x280000, 0x80000, 0xbc002fcd),
  LOAD_SW16( CPU1, "mvc.09", 0x300000, 0x80000, 0xc67b26df),
  LOAD_SW16( CPU1, "mvc.10", 0x380000, 0x80000, 0x0fdd1e26),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mvscb[] = // clone of mvsc
{
  LOAD_SW16( CPU1, "mvcb.03a", 0x000000, 0x80000, 0x7155953b),
  LOAD_SW16( CPU1, "mvcb.04a", 0x080000, 0x80000, 0xfb117d0e),
  LOAD_SW16( CPU1, "mvc.05a", 0x100000, 0x80000, 0x2d8c8e86),
  LOAD_SW16( CPU1, "mvc.06a", 0x180000, 0x80000, 0x8528e1f5),
  LOAD_SW16( CPU1, "mvc.07", 0x200000, 0x80000, 0xc3baa32b),
  LOAD_SW16( CPU1, "mvc.08", 0x280000, 0x80000, 0xbc002fcd),
  LOAD_SW16( CPU1, "mvc.09", 0x300000, 0x80000, 0xc67b26df),
  LOAD_SW16( CPU1, "mvc.10", 0x380000, 0x80000, 0x0fdd1e26),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mpang[] =
{
  LOAD_SW16( CPU1, "mpne.03c", 0x000000, 0x80000, 0xfe16fc9f),
  LOAD_SW16( CPU1, "mpne.04c", 0x080000, 0x80000, 0x2cc5ec22),
  { "mpn-simm.01c", 0x200000, 0x388db66b, REGION_GFX1, 0x0000000, LOAD_8_64 },
  { "mpn-simm.01d", 0x200000, 0xaff1b494, REGION_GFX1, 0x0000001, LOAD_8_64 },
  { "mpn-simm.01a", 0x200000, 0xa9c4857b, REGION_GFX1, 0x0000002, LOAD_8_64 },
  { "mpn-simm.01b", 0x200000, 0xf759df22, REGION_GFX1, 0x0000003, LOAD_8_64 },
  { "mpn-simm.03c", 0x200000, 0xdec6b720, REGION_GFX1, 0x0000004, LOAD_8_64 },
  { "mpn-simm.03d", 0x200000, 0xf8774c18, REGION_GFX1, 0x0000005, LOAD_8_64 },
  { "mpn-simm.03a", 0x200000, 0xc2aea4ec, REGION_GFX1, 0x0000006, LOAD_8_64 },
  { "mpn-simm.03b", 0x200000, 0x84d6dc33, REGION_GFX1, 0x0000007, LOAD_8_64 },
  LOAD( ROM2, "mpn.01", 0x00000, 0x20000, 0x90c7adb6),
  LOAD_SW16( SMP1, "mpn-simm.05a", 0x000000, 0x200000, 0x318a2e21),
  LOAD_SW16( SMP1, "mpn-simm.05b", 0x200000, 0x200000, 0x5462f4e8),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mpangr1[] = // clone of mpang
{
  LOAD_SW16( CPU1, "mpne.03b", 0x000000, 0x80000, 0x6ef0f9b2),
  LOAD_SW16( CPU1, "mpne.04b", 0x080000, 0x80000, 0x30a468bb),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mpangu[] = // clone of mpang
{
  LOAD_SW16( CPU1, "mpnu.03", 0x000000, 0x80000, 0x6e7ed03c),
  LOAD_SW16( CPU1, "mpnu.04", 0x080000, 0x80000, 0xde079131),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { "mpn.13m", 0x200000, 0xc5f123dc, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "mpn.15m", 0x200000, 0x8e033265, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "mpn.17m", 0x200000, 0xcfcd73d2, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "mpn.19m", 0x200000, 0x2db1ffbc, REGION_GFX1, 0x800006, LOAD_16_64 },
  LOAD_SW16( SMP1, "mpn.q1", 0x000000, 0x100000, 0xd21c1f5a),
  LOAD_SW16( SMP1, "mpn.q2", 0x100000, 0x100000, 0xd22090b1),
  LOAD_SW16( SMP1, "mpn.q3", 0x200000, 0x100000, 0x60aa5ef2),
  LOAD_SW16( SMP1, "mpn.q4", 0x300000, 0x100000, 0x3a67d203),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mpangj[] = // clone of mpang
{
  LOAD_SW16( CPU1, "mpnj.03a", 0x000000, 0x80000, 0xbf597b1c),
  LOAD_SW16( CPU1, "mpnj.04a", 0x080000, 0x80000, 0xf4a3ab0f),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_nwarr[] =
{
  LOAD_SW16( CPU1, "vphe.03f", 0x000000, 0x80000, 0xa922c44f),
  LOAD_SW16( CPU1, "vphe.04c", 0x080000, 0x80000, 0x7312d890),
  LOAD_SW16( CPU1, "vphe.05d", 0x100000, 0x80000, 0xcde8b506),
  LOAD_SW16( CPU1, "vphe.06c", 0x180000, 0x80000, 0xbe99e7d0),
  LOAD_SW16( CPU1, "vphe.07b", 0x200000, 0x80000, 0x69e0e60c),
  LOAD_SW16( CPU1, "vphe.08b", 0x280000, 0x80000, 0xd95a3849),
  LOAD_SW16( CPU1, "vphe.09b", 0x300000, 0x80000, 0x9882561c),
  LOAD_SW16( CPU1, "vphe.10b", 0x380000, 0x80000, 0x976fa62f),
  { "vph.13m", 0x400000, 0xc51baf99, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "vph.15m", 0x400000, 0x3ce83c77, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "vph.17m", 0x400000, 0x4f2408e0, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "vph.19m", 0x400000, 0x9ff60250, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "vph.14m", 0x400000, 0x7a0e1add, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "vph.16m", 0x400000, 0x2f41ca75, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "vph.18m", 0x400000, 0x64498eed, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "vph.20m", 0x400000, 0x17f2433f, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "vph.01", 0x00000, 0x20000, 0x5045dcac),
  LOAD( ROM2, "vph.02", 0x20000, 0x20000, 0x86b60e59),
  LOAD_SW16( SMP1, "vph.11m", 0x000000, 0x200000, 0xe1837d33),
  LOAD_SW16( SMP1, "vph.12m", 0x200000, 0x200000, 0xfbd3cd90),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_nwarru[] = // clone of nwarr
{
  LOAD_SW16( CPU1, "vphu.03f", 0x000000, 0x80000, 0x85d6a359),
  LOAD_SW16( CPU1, "vphu.04c", 0x080000, 0x80000, 0xcb7fce77),
  LOAD_SW16( CPU1, "vphu.05e", 0x100000, 0x80000, 0xe08f2bba),
  LOAD_SW16( CPU1, "vphu.06c", 0x180000, 0x80000, 0x08c04cdb),
  LOAD_SW16( CPU1, "vphu.07b", 0x200000, 0x80000, 0xb5a5ab19),
  LOAD_SW16( CPU1, "vphu.08b", 0x280000, 0x80000, 0x51bb20fb),
  LOAD_SW16( CPU1, "vphu.09b", 0x300000, 0x80000, 0x41a64205),
  LOAD_SW16( CPU1, "vphu.10b", 0x380000, 0x80000, 0x2b1d43ae),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_nwarrh[] = // clone of nwarr
{
  LOAD_SW16( CPU1, "vphh.03d", 0x000000, 0x80000, 0x6029c7be),
  LOAD_SW16( CPU1, "vphh.04a", 0x080000, 0x80000, 0xd26625ee),
  LOAD_SW16( CPU1, "vphh.05c", 0x100000, 0x80000, 0x73ee0b8a),
  LOAD_SW16( CPU1, "vphh.06a", 0x180000, 0x80000, 0xa5b3a50a),
  LOAD_SW16( CPU1, "vphh.07", 0x200000, 0x80000, 0x5fc2bdc1),
  LOAD_SW16( CPU1, "vphh.08", 0x280000, 0x80000, 0xe65588d9),
  LOAD_SW16( CPU1, "vphh.09", 0x300000, 0x80000, 0xa2ce6d63),
  LOAD_SW16( CPU1, "vphh.10", 0x380000, 0x80000, 0xe2f4f4b9),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_nwarrb[] = // clone of nwarr
{
  LOAD_SW16( CPU1, "vphb.03d", 0x000000, 0x80000, 0x3a426d3f),
  LOAD_SW16( CPU1, "vphb.04a", 0x080000, 0x80000, 0x51c4bb2f),
  LOAD_SW16( CPU1, "vphb.05c", 0x100000, 0x80000, 0xac44d997),
  LOAD_SW16( CPU1, "vphb.06a", 0x180000, 0x80000, 0x5072a5fe),
  LOAD_SW16( CPU1, "vphb.07", 0x200000, 0x80000, 0x9b355192),
  LOAD_SW16( CPU1, "vphb.08", 0x280000, 0x80000, 0x42220f84),
  LOAD_SW16( CPU1, "vphb.09", 0x300000, 0x80000, 0x029e015d),
  LOAD_SW16( CPU1, "vphb.10", 0x380000, 0x80000, 0x37b3ce37),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_nwarra[] = // clone of nwarr
{
  LOAD_SW16( CPU1, "vpha.03b", 0x000000, 0x80000, 0x0a70cdd6),
  LOAD_SW16( CPU1, "vpha.04b", 0x080000, 0x80000, 0x70ce62e4),
  LOAD_SW16( CPU1, "vpha.05b", 0x100000, 0x80000, 0x5692a03f),
  LOAD_SW16( CPU1, "vpha.06b", 0x180000, 0x80000, 0xb810fe66),
  LOAD_SW16( CPU1, "vpha.07b", 0x200000, 0x80000, 0x1be264f3),
  LOAD_SW16( CPU1, "vpha.08b", 0x280000, 0x80000, 0x86f1ed52),
  LOAD_SW16( CPU1, "vpha.09b", 0x300000, 0x80000, 0x7e96bd0a),
  LOAD_SW16( CPU1, "vpha.10b", 0x380000, 0x80000, 0x58bce2fd),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vhuntj[] = // clone of nwarr
{
  LOAD_SW16( CPU1, "vphj.03f", 0x000000, 0x80000, 0x3de2e333),
  LOAD_SW16( CPU1, "vphj.04c", 0x080000, 0x80000, 0xc95cf304),
  LOAD_SW16( CPU1, "vphj.05d", 0x100000, 0x80000, 0x50de5ddd),
  LOAD_SW16( CPU1, "vphj.06c", 0x180000, 0x80000, 0xac3bd3d5),
  LOAD_SW16( CPU1, "vphj.07b", 0x200000, 0x80000, 0x0761309f),
  LOAD_SW16( CPU1, "vphj.08b", 0x280000, 0x80000, 0x5a5c2bf5),
  LOAD_SW16( CPU1, "vphj.09b", 0x300000, 0x80000, 0x823d6d99),
  LOAD_SW16( CPU1, "vphj.10b", 0x380000, 0x80000, 0x32c7d8f0),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vhuntjr1s[] = // clone of nwarr
{
  LOAD_SW16( CPU1, "vphjstop.03b", 0x000000, 0x80000, 0x9c4e6191),
  LOAD_SW16( CPU1, "vphj.04c", 0x080000, 0x80000, 0xc95cf304),
  LOAD_SW16( CPU1, "vphj.05d", 0x100000, 0x80000, 0x50de5ddd),
  LOAD_SW16( CPU1, "vphj.06c", 0x180000, 0x80000, 0xac3bd3d5),
  LOAD_SW16( CPU1, "vphj.07b", 0x200000, 0x80000, 0x0761309f),
  LOAD_SW16( CPU1, "vphj.08b", 0x280000, 0x80000, 0x5a5c2bf5),
  LOAD_SW16( CPU1, "vphj.09b", 0x300000, 0x80000, 0x823d6d99),
  LOAD_SW16( CPU1, "vphj.10b", 0x380000, 0x80000, 0x32c7d8f0),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vhuntjr1[] = // clone of nwarr
{
  LOAD_SW16( CPU1, "vphj.03c", 0x000000, 0x80000, 0x606b682a),
  LOAD_SW16( CPU1, "vphj.04b", 0x080000, 0x80000, 0xa3b40393),
  LOAD_SW16( CPU1, "vphj.05b", 0x100000, 0x80000, 0xfccd5558),
  LOAD_SW16( CPU1, "vphj.06b", 0x180000, 0x80000, 0x07e10a73),
  LOAD_SW16( CPU1, "vphj.07b", 0x200000, 0x80000, 0x0761309f),
  LOAD_SW16( CPU1, "vphj.08b", 0x280000, 0x80000, 0x5a5c2bf5),
  LOAD_SW16( CPU1, "vphj.09b", 0x300000, 0x80000, 0x823d6d99),
  LOAD_SW16( CPU1, "vphj.10b", 0x380000, 0x80000, 0x32c7d8f0),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vhuntjr2[] = // clone of nwarr
{
  LOAD_SW16( CPU1, "vphj.03b", 0x000000, 0x80000, 0x679c3fa9),
  LOAD_SW16( CPU1, "vphj.04a", 0x080000, 0x80000, 0xeb6e71e4),
  LOAD_SW16( CPU1, "vphj.05a", 0x100000, 0x80000, 0xeaf634ea),
  LOAD_SW16( CPU1, "vphj.06a", 0x180000, 0x80000, 0xb70cc6be),
  LOAD_SW16( CPU1, "vphj.07a", 0x200000, 0x80000, 0x46ab907d),
  LOAD_SW16( CPU1, "vphj.08a", 0x280000, 0x80000, 0x1c00355e),
  LOAD_SW16( CPU1, "vphj.09a", 0x300000, 0x80000, 0x026e6f82),
  LOAD_SW16( CPU1, "vphj.10a", 0x380000, 0x80000, 0xaadfb3ea),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_progear[] =
{
  LOAD_SW16( CPU1, "pgau.03", 0x000000, 0x80000, 0x343a783e),
  LOAD_SW16( CPU1, "pgau.04", 0x080000, 0x80000, 0x16208d79),
  { "pga-simm.01c", 0x200000, 0x452f98b0, REGION_GFX1, 0x0000000, LOAD_8_64 },
  { "pga-simm.01d", 0x200000, 0x9e672092, REGION_GFX1, 0x0000001, LOAD_8_64 },
  { "pga-simm.01a", 0x200000, 0xae9ddafe, REGION_GFX1, 0x0000002, LOAD_8_64 },
  { "pga-simm.01b", 0x200000, 0x94d72d94, REGION_GFX1, 0x0000003, LOAD_8_64 },
  { "pga-simm.03c", 0x200000, 0x48a1886d, REGION_GFX1, 0x0000004, LOAD_8_64 },
  { "pga-simm.03d", 0x200000, 0x172d7e37, REGION_GFX1, 0x0000005, LOAD_8_64 },
  { "pga-simm.03a", 0x200000, 0x9ee33d98, REGION_GFX1, 0x0000006, LOAD_8_64 },
  { "pga-simm.03b", 0x200000, 0x848dee32, REGION_GFX1, 0x0000007, LOAD_8_64 },
  LOAD( ROM2, "pga.01", 0x00000, 0x20000, 0xbdbfa992),
  LOAD_SW16( SMP1, "pga-simm.05a", 0x000000, 0x200000, 0xc0aac80c),
  LOAD_SW16( SMP1, "pga-simm.05b", 0x200000, 0x200000, 0x37a65d86),
  LOAD_SW16( SMP1, "pga-simm.06a", 0x400000, 0x200000, 0xd3f1e934),
  LOAD_SW16( SMP1, "pga-simm.06b", 0x600000, 0x200000, 0x8b39489a),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_progearj[] = // clone of progear
{
  LOAD_SW16( CPU1, "pgaj.03", 0x000000, 0x80000, 0x06dbba54),
  LOAD_SW16( CPU1, "pgaj.04", 0x080000, 0x80000, 0xa1f1f1bc),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_progeara[] = // clone of progear
{
  LOAD_SW16( CPU1, "pgaa.03", 0x000000, 0x80000, 0x25e6e2ce),
  LOAD_SW16( CPU1, "pgaa.04", 0x080000, 0x80000, 0x8104307e),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_pzloop2[] =
{
  LOAD_SW16( CPU1, "pl2e.03", 0x000000, 0x80000, 0x3b1285b2),
  LOAD_SW16( CPU1, "pl2e.04", 0x080000, 0x80000, 0x40a2d647),
  LOAD_SW16( CPU1, "pl2e.05", 0x100000, 0x80000, 0x0f11d818),
  LOAD_SW16( CPU1, "pl2e.06", 0x180000, 0x80000, 0x86fbbdf4),
  { "pl2-simm.01c", 0x200000, 0x137b13a7, REGION_GFX1, 0x0000000, LOAD_8_64 },
  { "pl2-simm.01d", 0x200000, 0xa2db1507, REGION_GFX1, 0x0000001, LOAD_8_64 },
  { "pl2-simm.01a", 0x200000, 0x7e80ff8e, REGION_GFX1, 0x0000002, LOAD_8_64 },
  { "pl2-simm.01b", 0x200000, 0xcd93e6ed, REGION_GFX1, 0x0000003, LOAD_8_64 },
  { "pl2-simm.03c", 0x200000, 0x0f52bbca, REGION_GFX1, 0x0000004, LOAD_8_64 },
  { "pl2-simm.03d", 0x200000, 0xa62712c3, REGION_GFX1, 0x0000005, LOAD_8_64 },
  { "pl2-simm.03a", 0x200000, 0xb60c9f8e, REGION_GFX1, 0x0000006, LOAD_8_64 },
  { "pl2-simm.03b", 0x200000, 0x83fef284, REGION_GFX1, 0x0000007, LOAD_8_64 },
  LOAD( ROM2, "pl2.01", 0x00000, 0x20000, 0x35697569),
  LOAD_SW16( SMP1, "pl2-simm.05a", 0x000000, 0x200000, 0x85d8fbe8),
  LOAD_SW16( SMP1, "pl2-simm.05b", 0x200000, 0x200000, 0x1ed62584),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_pzloop2j[] = // clone of pzloop2
{
  LOAD_SW16( CPU1, "pl2j.03c", 0x000000, 0x80000, 0x3b76b806),
  LOAD_SW16( CPU1, "pl2j.04c", 0x080000, 0x80000, 0x8878a42a),
  LOAD_SW16( CPU1, "pl2j.05c", 0x100000, 0x80000, 0x51081ea4),
  LOAD_SW16( CPU1, "pl2j.06c", 0x180000, 0x80000, 0x51c68494),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_pzloop2jr1[] = // clone of pzloop2
{
  LOAD_SW16( CPU1, "pl2j.03a", 0x000000, 0x80000, 0x0a751bd0),
  LOAD_SW16( CPU1, "pl2j.04a", 0x080000, 0x80000, 0xc3f72afe),
  LOAD_SW16( CPU1, "pl2j.05a", 0x100000, 0x80000, 0x6ea9dbfc),
  LOAD_SW16( CPU1, "pl2j.06a", 0x180000, 0x80000, 0x0f14848d),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_qndream[] =
{
  LOAD_SW16( CPU1, "tqzj.03a", 0x000000, 0x80000, 0x7acf3e30),
  LOAD_SW16( CPU1, "tqzj.04", 0x080000, 0x80000, 0xf1044a87),
  LOAD_SW16( CPU1, "tqzj.05", 0x100000, 0x80000, 0x4105ba0e),
  LOAD_SW16( CPU1, "tqzj.06", 0x180000, 0x80000, 0xc371e8a5),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { "tqz.14m", 0x200000, 0x98af88a2, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "tqz.16m", 0x200000, 0xdf82d491, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "tqz.18m", 0x200000, 0x42f132ff, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "tqz.20m", 0x200000, 0xb2e128a3, REGION_GFX1, 0x800006, LOAD_16_64 },
  LOAD( ROM2, "tqz.01", 0x00000, 0x20000, 0xe9ce9d0a),
  LOAD_SW16( SMP1, "tqz.11m", 0x000000, 0x200000, 0x78e7884f),
  LOAD_SW16( SMP1, "tqz.12m", 0x200000, 0x200000, 0x2e049b13),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ringdest[] =
{
  LOAD_SW16( CPU1, "smbe.03b", 0x000000, 0x80000, 0xb8016278),
  LOAD_SW16( CPU1, "smbe.04b", 0x080000, 0x80000, 0x18c4c447),
  LOAD_SW16( CPU1, "smbe.05b", 0x100000, 0x80000, 0x18ebda7f),
  LOAD_SW16( CPU1, "smbe.06b", 0x180000, 0x80000, 0x89c80007),
  LOAD_SW16( CPU1, "smb.07", 0x200000, 0x80000, 0xb9a11577),
  LOAD_SW16( CPU1, "smb.08", 0x280000, 0x80000, 0xf931b76b),
  { "smb.13m", 0x200000, 0xd9b2d1de, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "smb.15m", 0x200000, 0x9a766d92, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "smb.17m", 0x200000, 0x51800f0f, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "smb.19m", 0x200000, 0x35757e96, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "smb.14m", 0x200000, 0xe5bfd0e7, REGION_GFX1, 0x0800000, LOAD_16_64 },
  { "smb.16m", 0x200000, 0xc56c0866, REGION_GFX1, 0x0800002, LOAD_16_64 },
  { "smb.18m", 0x200000, 0x4ded3910, REGION_GFX1, 0x0800004, LOAD_16_64 },
  { "smb.20m", 0x200000, 0x26ea1ec5, REGION_GFX1, 0x0800006, LOAD_16_64 },
  { "smb.21m", 0x080000, 0x0a08c5fc, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "smb.23m", 0x080000, 0x0911b6c4, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "smb.25m", 0x080000, 0x82d6c4ec, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "smb.27m", 0x080000, 0x9b48678b, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "smb.01", 0x00000, 0x20000, 0x0abc229a),
  LOAD( ROM2, "smb.02", 0x20000, 0x20000, 0xd051679a),
  LOAD_SW16( SMP1, "smb.11m", 0x000000, 0x200000, 0xc56935f9),
  LOAD_SW16( SMP1, "smb.12m", 0x200000, 0x200000, 0x955b0782),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_smbomb[] = // clone of ringdest
{
  LOAD_SW16( CPU1, "smbj.03a", 0x000000, 0x80000, 0x1c5613de),
  LOAD_SW16( CPU1, "smbj.04a", 0x080000, 0x80000, 0x29071ed7),
  LOAD_SW16( CPU1, "smbj.05a", 0x100000, 0x80000, 0xeb20bce4),
  LOAD_SW16( CPU1, "smbj.06a", 0x180000, 0x80000, 0x94b420cd),
  LOAD_SW16( CPU1, "smb.07", 0x200000, 0x80000, 0xb9a11577),
  LOAD_SW16( CPU1, "smb.08", 0x280000, 0x80000, 0xf931b76b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_smbombr1[] = // clone of ringdest
{
  LOAD_SW16( CPU1, "smbj.03", 0x000000, 0x80000, 0x52eafb10),
  LOAD_SW16( CPU1, "smbj.04", 0x080000, 0x80000, 0xaa6e8078),
  LOAD_SW16( CPU1, "smbj.05", 0x100000, 0x80000, 0xb69e7d5f),
  LOAD_SW16( CPU1, "smbj.06", 0x180000, 0x80000, 0x8d857b56),
  LOAD_SW16( CPU1, "smb.07", 0x200000, 0x80000, 0xb9a11577),
  LOAD_SW16( CPU1, "smb.08", 0x280000, 0x80000, 0xf931b76b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ringdesta[] = // clone of ringdest
{
  LOAD_SW16( CPU1, "smba.03a", 0x000000, 0x80000, 0xd3744dfd),
  LOAD_SW16( CPU1, "smba.04a", 0x080000, 0x80000, 0xf32d5b4f),
  LOAD_SW16( CPU1, "smba.05a", 0x100000, 0x80000, 0x1016454f),
  LOAD_SW16( CPU1, "smba.06a", 0x180000, 0x80000, 0x94b420cd),
  LOAD_SW16( CPU1, "smb.07", 0x200000, 0x80000, 0xb9a11577),
  LOAD_SW16( CPU1, "smb.08", 0x280000, 0x80000, 0xf931b76b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mmancp2u[] =
{
  LOAD_SW16( CPU1, "rcmu.03b", 0x000000, 0x80000, 0xc39f037f),
  LOAD_SW16( CPU1, "rcmu.04b", 0x080000, 0x80000, 0xcd6f5e99),
  LOAD_SW16( CPU1, "rcm.05b", 0x100000, 0x80000, 0x4376ea95),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { "rcm.73", 0x080000, 0x774c6e04, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "rcm.63", 0x080000, 0xacad7c62, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "rcm.83", 0x080000, 0x6af30499, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "rcm.93", 0x080000, 0x7a5a5166, REGION_GFX1, 0x800006, LOAD_16_64 },
  { "rcm.74", 0x080000, 0x004ec725, REGION_GFX1, 0xa00000, LOAD_16_64 },
  { "rcm.64", 0x080000, 0x65c0464e, REGION_GFX1, 0xa00002, LOAD_16_64 },
  { "rcm.84", 0x080000, 0xfb3097cc, REGION_GFX1, 0xa00004, LOAD_16_64 },
  { "rcm.94", 0x080000, 0x2e16557a, REGION_GFX1, 0xa00006, LOAD_16_64 },
  { "rcm.75", 0x080000, 0x70a73f99, REGION_GFX1, 0xc00000, LOAD_16_64 },
  { "rcm.65", 0x080000, 0xecedad3d, REGION_GFX1, 0xc00002, LOAD_16_64 },
  { "rcm.85", 0x080000, 0x3d6186d8, REGION_GFX1, 0xc00004, LOAD_16_64 },
  { "rcm.95", 0x080000, 0x8c7700f1, REGION_GFX1, 0xc00006, LOAD_16_64 },
  { "rcm.76", 0x080000, 0x89a889ad, REGION_GFX1, 0xe00000, LOAD_16_64 },
  { "rcm.66", 0x080000, 0x1300eb7b, REGION_GFX1, 0xe00002, LOAD_16_64 },
  { "rcm.86", 0x080000, 0x6d974ebd, REGION_GFX1, 0xe00004, LOAD_16_64 },
  { "rcm.96", 0x080000, 0x7da4cd24, REGION_GFX1, 0xe00006, LOAD_16_64 },
  LOAD( ROM2, "rcm.01", 0x00000, 0x20000, 0xd60cf8a3),
  LOAD_SW16( SMP1, "rcm.51", 0x000000, 0x80000, 0xb6d07080),
  LOAD_SW16( SMP1, "rcm.52", 0x080000, 0x80000, 0xdfddc493),
  LOAD_SW16( SMP1, "rcm.53", 0x100000, 0x80000, 0x6062ae3a),
  LOAD_SW16( SMP1, "rcm.54", 0x180000, 0x80000, 0x08c6f3bf),
  LOAD_SW16( SMP1, "rcm.55", 0x200000, 0x80000, 0xf97dfccc),
  LOAD_SW16( SMP1, "rcm.56", 0x280000, 0x80000, 0xade475bc),
  LOAD_SW16( SMP1, "rcm.57", 0x300000, 0x80000, 0x075effb3),
  LOAD_SW16( SMP1, "rcm.58", 0x380000, 0x80000, 0xf6c1f87b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_rmancp2j[] =
{
  LOAD_SW16( CPU1, "rcmj.03a", 0x000000, 0x80000, 0x30559f60),
  LOAD_SW16( CPU1, "rcmj.04a", 0x080000, 0x80000, 0x5efc9366),
  LOAD_SW16( CPU1, "rcm.05a", 0x100000, 0x80000, 0x517ccde2),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { "rcm.73", 0x080000, 0x774c6e04, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "rcm.63", 0x080000, 0xacad7c62, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "rcm.83", 0x080000, 0x6af30499, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "rcm.93", 0x080000, 0x7a5a5166, REGION_GFX1, 0x800006, LOAD_16_64 },
  { "rcm.74", 0x080000, 0x004ec725, REGION_GFX1, 0xa00000, LOAD_16_64 },
  { "rcm.64", 0x080000, 0x65c0464e, REGION_GFX1, 0xa00002, LOAD_16_64 },
  { "rcm.84", 0x080000, 0xfb3097cc, REGION_GFX1, 0xa00004, LOAD_16_64 },
  { "rcm.94", 0x080000, 0x2e16557a, REGION_GFX1, 0xa00006, LOAD_16_64 },
  { "rcm.75", 0x080000, 0x70a73f99, REGION_GFX1, 0xc00000, LOAD_16_64 },
  { "rcm.65", 0x080000, 0xecedad3d, REGION_GFX1, 0xc00002, LOAD_16_64 },
  { "rcm.85", 0x080000, 0x3d6186d8, REGION_GFX1, 0xc00004, LOAD_16_64 },
  { "rcm.95", 0x080000, 0x8c7700f1, REGION_GFX1, 0xc00006, LOAD_16_64 },
  { "rcm.76", 0x080000, 0x89a889ad, REGION_GFX1, 0xe00000, LOAD_16_64 },
  { "rcm.66", 0x080000, 0x1300eb7b, REGION_GFX1, 0xe00002, LOAD_16_64 },
  { "rcm.86", 0x080000, 0x6d974ebd, REGION_GFX1, 0xe00004, LOAD_16_64 },
  { "rcm.96", 0x080000, 0x7da4cd24, REGION_GFX1, 0xe00006, LOAD_16_64 },
  LOAD( ROM2, "rcm.01", 0x00000, 0x20000, 0xd60cf8a3),
  LOAD_SW16( SMP1, "rcm.51", 0x000000, 0x80000, 0xb6d07080),
  LOAD_SW16( SMP1, "rcm.52", 0x080000, 0x80000, 0xdfddc493),
  LOAD_SW16( SMP1, "rcm.53", 0x100000, 0x80000, 0x6062ae3a),
  LOAD_SW16( SMP1, "rcm.54", 0x180000, 0x80000, 0x08c6f3bf),
  LOAD_SW16( SMP1, "rcm.55", 0x200000, 0x80000, 0xf97dfccc),
  LOAD_SW16( SMP1, "rcm.56", 0x280000, 0x80000, 0xade475bc),
  LOAD_SW16( SMP1, "rcm.57", 0x300000, 0x80000, 0x075effb3),
  LOAD_SW16( SMP1, "rcm.58", 0x380000, 0x80000, 0xf6c1f87b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfa[] =
{
  LOAD_SW16( CPU1, "sfze.03d", 0x000000, 0x80000, 0xebf2054d),
  LOAD_SW16( CPU1, "sfz.04b", 0x080000, 0x80000, 0x8b73b0e5),
  LOAD_SW16( CPU1, "sfz.05a", 0x100000, 0x80000, 0x0810544d),
  LOAD_SW16( CPU1, "sfz.06", 0x180000, 0x80000, 0x806e8f38),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { "sfz.14m", 0x200000, 0x90fefdb3, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "sfz.16m", 0x200000, 0x5354c948, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "sfz.18m", 0x200000, 0x41a1e790, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "sfz.20m", 0x200000, 0xa549df98, REGION_GFX1, 0x800006, LOAD_16_64 },
  LOAD( ROM2, "sfz.01", 0x00000, 0x20000, 0xffffec7d),
  LOAD( ROM2, "sfz.02", 0x20000, 0x20000, 0x45f46a08),
  LOAD_SW16( SMP1, "sfz.11m", 0x000000, 0x200000, 0xc4b093cd),
  LOAD_SW16( SMP1, "sfz.12m", 0x200000, 0x200000, 0x8bdbc4b4),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfar1[] = // clone of sfa
{
  LOAD_SW16( CPU1, "sfze.03c", 0x000000, 0x80000, 0xa1b69dd7),
  LOAD_SW16( CPU1, "sfze.04b", 0x080000, 0x80000, 0xbb90acd5),
  LOAD_SW16( CPU1, "sfz.05a", 0x100000, 0x80000, 0x0810544d),
  LOAD_SW16( CPU1, "sfz.06", 0x180000, 0x80000, 0x806e8f38),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfar2[] = // clone of sfa
{
  LOAD_SW16( CPU1, "sfze.03b", 0x000000, 0x80000, 0x2bf5708e),
  LOAD_SW16( CPU1, "sfz.04a", 0x080000, 0x80000, 0x5f99e9a5),
  LOAD_SW16( CPU1, "sfz.05a", 0x100000, 0x80000, 0x0810544d),
  LOAD_SW16( CPU1, "sfz.06", 0x180000, 0x80000, 0x806e8f38),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfar3[] = // clone of sfa
{
  LOAD_SW16( CPU1, "sfze.03a", 0x000000, 0x80000, 0xfdbcd434),
  LOAD_SW16( CPU1, "sfz.04", 0x080000, 0x80000, 0x0c436d30),
  LOAD_SW16( CPU1, "sfz.05", 0x100000, 0x80000, 0x1f363612),
  LOAD_SW16( CPU1, "sfz.06", 0x180000, 0x80000, 0x806e8f38),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfau[] = // clone of sfa
{
  LOAD_SW16( CPU1, "sfzu.03a", 0x000000, 0x80000, 0x49fc7db9),
  LOAD_SW16( CPU1, "sfz.04a", 0x080000, 0x80000, 0x5f99e9a5),
  LOAD_SW16( CPU1, "sfz.05a", 0x100000, 0x80000, 0x0810544d),
  LOAD_SW16( CPU1, "sfz.06", 0x180000, 0x80000, 0x806e8f38),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfza[] = // clone of sfa
{
  LOAD_SW16( CPU1, "sfza.03a", 0x000000, 0x80000, 0xca91bed9),
  LOAD_SW16( CPU1, "sfz.04a", 0x080000, 0x80000, 0x5f99e9a5),
  LOAD_SW16( CPU1, "sfz.05a", 0x100000, 0x80000, 0x0810544d),
  LOAD_SW16( CPU1, "sfz.06", 0x180000, 0x80000, 0x806e8f38),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfzj[] = // clone of sfa
{
  LOAD_SW16( CPU1, "sfzj.03c", 0x000000, 0x80000, 0xf5444120),
  LOAD_SW16( CPU1, "sfz.04b", 0x080000, 0x80000, 0x8b73b0e5),
  LOAD_SW16( CPU1, "sfz.05a", 0x100000, 0x80000, 0x0810544d),
  LOAD_SW16( CPU1, "sfz.06", 0x180000, 0x80000, 0x806e8f38),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfzjr1[] = // clone of sfa
{
  LOAD_SW16( CPU1, "sfzj.03b", 0x000000, 0x80000, 0x844220c2),
  LOAD_SW16( CPU1, "sfz.04a", 0x080000, 0x80000, 0x5f99e9a5),
  LOAD_SW16( CPU1, "sfz.05a", 0x100000, 0x80000, 0x0810544d),
  LOAD_SW16( CPU1, "sfz.06", 0x180000, 0x80000, 0x806e8f38),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfzjr2[] = // clone of sfa
{
  LOAD_SW16( CPU1, "sfzj.03a", 0x000000, 0x80000, 0x3cfce93c),
  LOAD_SW16( CPU1, "sfz.04", 0x080000, 0x80000, 0x0c436d30),
  LOAD_SW16( CPU1, "sfz.05", 0x100000, 0x80000, 0x1f363612),
  LOAD_SW16( CPU1, "sfz.06", 0x180000, 0x80000, 0x806e8f38),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfzh[] = // clone of sfa
{
  LOAD_SW16( CPU1, "sfzh.03d", 0x000000, 0x80000, 0x6e08cbe0),
  LOAD_SW16( CPU1, "sfz.04c", 0x080000, 0x80000, 0xbb90acd5),
  LOAD_SW16( CPU1, "sfz.05c", 0x100000, 0x80000, 0x0810544d),
  LOAD_SW16( CPU1, "sfz.06", 0x180000, 0x80000, 0x806e8f38),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfzhr1[] = // clone of sfa
{
  LOAD_SW16( CPU1, "sfzh.03c", 0x000000, 0x80000, 0xbce635aa),
  LOAD_SW16( CPU1, "sfz.04a", 0x080000, 0x80000, 0x5f99e9a5),
  LOAD_SW16( CPU1, "sfz.05a", 0x100000, 0x80000, 0x0810544d),
  LOAD_SW16( CPU1, "sfz.06", 0x180000, 0x80000, 0x806e8f38),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfzb[] = // clone of sfa
{
  LOAD_SW16( CPU1, "sfzb.03g", 0x000000, 0x80000, 0x348862d4),
  LOAD_SW16( CPU1, "sfzb.04e", 0x080000, 0x80000, 0x8d9b2480),
  LOAD_SW16( CPU1, "sfz.05a", 0x100000, 0x80000, 0x0810544d),
  LOAD_SW16( CPU1, "sfz.06", 0x180000, 0x80000, 0x806e8f38),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfzbr1[] = // clone of sfa
{
  LOAD_SW16( CPU1, "sfzb.03e", 0x000000, 0x80000, 0xecba89a3),
  LOAD_SW16( CPU1, "sfz.04b", 0x080000, 0x80000, 0x8b73b0e5),
  LOAD_SW16( CPU1, "sfz.05a", 0x100000, 0x80000, 0x0810544d),
  LOAD_SW16( CPU1, "sfz.06", 0x180000, 0x80000, 0x806e8f38),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfa2[] =
{
  LOAD_SW16( CPU1, "sz2e.03", 0x000000, 0x80000, 0x1061e6bb),
  LOAD_SW16( CPU1, "sz2e.04", 0x080000, 0x80000, 0x22d17b26),
  LOAD_SW16( CPU1, "sz2.05", 0x100000, 0x80000, 0x4b442a7c),
  LOAD_SW16( CPU1, "sz2.06", 0x180000, 0x80000, 0x5b1d49c0),
  LOAD_SW16( CPU1, "sz2.07", 0x200000, 0x80000, 0x8e184246),
  LOAD_SW16( CPU1, "sz2.08", 0x280000, 0x80000, 0x0fe8585d),
  { "sz2.13m", 0x400000, 0x4d1f1f22, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "sz2.15m", 0x400000, 0x19cea680, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "sz2.17m", 0x400000, 0xe01b4588, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "sz2.19m", 0x400000, 0x0feeda64, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "sz2.14m", 0x100000, 0x0560c6aa, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "sz2.16m", 0x100000, 0xae940f87, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "sz2.18m", 0x100000, 0x4bc3c8bc, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "sz2.20m", 0x100000, 0x39e674c0, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "sz2.01a", 0x00000, 0x20000, 0x1bc323cf),
  LOAD( ROM2, "sz2.02a", 0x20000, 0x20000, 0xba6a5013),
  LOAD_SW16( SMP1, "sz2.11m", 0x000000, 0x200000, 0xaa47a601),
  LOAD_SW16( SMP1, "sz2.12m", 0x200000, 0x200000, 0x2237bc53),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfa2u[] = // clone of sfa2
{
  LOAD_SW16( CPU1, "sz2u.03a", 0x000000, 0x80000, 0xd03e504f),
  LOAD_SW16( CPU1, "sz2u.04a", 0x080000, 0x80000, 0xfae0e9c3),
  LOAD_SW16( CPU1, "sz2u.05a", 0x100000, 0x80000, 0xd02dd758),
  LOAD_SW16( CPU1, "sz2u.06", 0x180000, 0x80000, 0xc5c8eb63),
  LOAD_SW16( CPU1, "sz2u.07", 0x200000, 0x80000, 0x5de01cc5),
  LOAD_SW16( CPU1, "sz2u.08", 0x280000, 0x80000, 0xbea11d56),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfa2ur1[] = // clone of sfa2
{
  LOAD_SW16( CPU1, "sz2u.03", 0x000000, 0x80000, 0x84a09006),
  LOAD_SW16( CPU1, "sz2u.04", 0x080000, 0x80000, 0xac46e5ed),
  LOAD_SW16( CPU1, "sz2u.05", 0x100000, 0x80000, 0x6c0c79d3),
  LOAD_SW16( CPU1, "sz2u.06", 0x180000, 0x80000, 0xc5c8eb63),
  LOAD_SW16( CPU1, "sz2u.07", 0x200000, 0x80000, 0x5de01cc5),
  LOAD_SW16( CPU1, "sz2u.08", 0x280000, 0x80000, 0xbea11d56),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz2j[] = // clone of sfa2
{
  LOAD_SW16( CPU1, "sz2j.03b", 0x000000, 0x80000, 0x3e1e2e85),
  LOAD_SW16( CPU1, "sz2j.04b", 0x080000, 0x80000, 0xf53d6c45),
  LOAD_SW16( CPU1, "sz2j.05b", 0x100000, 0x80000, 0xdd224156),
  LOAD_SW16( CPU1, "sz2j.06b", 0x180000, 0x80000, 0xa45a75a6),
  LOAD_SW16( CPU1, "sz2j.07b", 0x200000, 0x80000, 0x6352f038),
  LOAD_SW16( CPU1, "sz2j.08b", 0x280000, 0x80000, 0x92b66e01),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz2jr1[] = // clone of sfa2
{
  LOAD_SW16( CPU1, "sz2j.03a", 0x000000, 0x80000, 0x97461e28),
  LOAD_SW16( CPU1, "sz2j.04a", 0x080000, 0x80000, 0xae4851a9),
  LOAD_SW16( CPU1, "sz2.05a", 0x100000, 0x80000, 0x98e8e992),
  LOAD_SW16( CPU1, "sz2.06", 0x180000, 0x80000, 0x5b1d49c0),
  LOAD_SW16( CPU1, "sz2j.07a", 0x200000, 0x80000, 0xd910b2a2),
  LOAD_SW16( CPU1, "sz2.08", 0x280000, 0x80000, 0x0fe8585d),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz2a[] = // clone of sfa2
{
  LOAD_SW16( CPU1, "sz2a.03a", 0x000000, 0x80000, 0x30d2099f),
  LOAD_SW16( CPU1, "sz2a.04a", 0x080000, 0x80000, 0x1cc94db1),
  LOAD_SW16( CPU1, "sz2.05a", 0x100000, 0x80000, 0x98e8e992),
  LOAD_SW16( CPU1, "sz2.06", 0x180000, 0x80000, 0x5b1d49c0),
  LOAD_SW16( CPU1, "sz2a.07a", 0x200000, 0x80000, 0x0aed2494),
  LOAD_SW16( CPU1, "sz2.08", 0x280000, 0x80000, 0x0fe8585d),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz2b[] = // clone of sfa2
{
  LOAD_SW16( CPU1, "sz2b.03b", 0x000000, 0x80000, 0x1ac12812),
  LOAD_SW16( CPU1, "sz2b.04b", 0x080000, 0x80000, 0xe4ffaf68),
  LOAD_SW16( CPU1, "sz2b.05a", 0x100000, 0x80000, 0xdd224156),
  LOAD_SW16( CPU1, "sz2b.06a", 0x180000, 0x80000, 0xa45a75a6),
  LOAD_SW16( CPU1, "sz2b.07a", 0x200000, 0x80000, 0x7d19d5ec),
  LOAD_SW16( CPU1, "sz2b.08", 0x280000, 0x80000, 0x92b66e01),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz2br1[] = // clone of sfa2
{
  LOAD_SW16( CPU1, "sz2b.03", 0x000000, 0x80000, 0xe6ce530b),
  LOAD_SW16( CPU1, "sz2b.04", 0x080000, 0x80000, 0x1605a0cb),
  LOAD_SW16( CPU1, "sz2.05", 0x100000, 0x80000, 0x4b442a7c),
  LOAD_SW16( CPU1, "sz2.06", 0x180000, 0x80000, 0x5b1d49c0),
  LOAD_SW16( CPU1, "sz2b.07", 0x200000, 0x80000, 0x947e8ac6),
  LOAD_SW16( CPU1, "sz2b.08", 0x280000, 0x80000, 0x92b66e01),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz2h[] = // clone of sfa2
{
  LOAD_SW16( CPU1, "sz2h.03", 0x000000, 0x80000, 0xbfeddf5b),
  LOAD_SW16( CPU1, "sz2h.04", 0x080000, 0x80000, 0xea5009fb),
  LOAD_SW16( CPU1, "sz2.05", 0x100000, 0x80000, 0x4b442a7c),
  LOAD_SW16( CPU1, "sz2.06", 0x180000, 0x80000, 0x5b1d49c0),
  LOAD_SW16( CPU1, "sz2h.07", 0x200000, 0x80000, 0x947e8ac6),
  LOAD_SW16( CPU1, "sz2h.08", 0x280000, 0x80000, 0x92b66e01),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz2n[] = // clone of sfa2
{
  LOAD_SW16( CPU1, "sz2n.03", 0x000000, 0x80000, 0x58924741),
  LOAD_SW16( CPU1, "sz2n.04", 0x080000, 0x80000, 0x592a17c5),
  LOAD_SW16( CPU1, "sz2.05", 0x100000, 0x80000, 0x4b442a7c),
  LOAD_SW16( CPU1, "sz2.06", 0x180000, 0x80000, 0x5b1d49c0),
  LOAD_SW16( CPU1, "sz2.07", 0x200000, 0x80000, 0x8e184246),
  LOAD_SW16( CPU1, "sz2.08", 0x280000, 0x80000, 0x0fe8585d),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz2al[] =
{
  LOAD_SW16( CPU1, "szaa.03", 0x000000, 0x80000, 0x88e7023e),
  LOAD_SW16( CPU1, "szaa.04", 0x080000, 0x80000, 0xae8ec36e),
  LOAD_SW16( CPU1, "szaa.05", 0x100000, 0x80000, 0xf053a55e),
  LOAD_SW16( CPU1, "szaa.06", 0x180000, 0x80000, 0xcfc0e7a8),
  LOAD_SW16( CPU1, "szaa.07", 0x200000, 0x80000, 0x5feb8b20),
  LOAD_SW16( CPU1, "szaa.08", 0x280000, 0x80000, 0x6eb6d412),
  { "sza.13m", 0x400000, 0x4d1f1f22, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "sza.15m", 0x400000, 0x19cea680, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "sza.17m", 0x400000, 0xe01b4588, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "sza.19m", 0x400000, 0x0feeda64, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "sza.14m", 0x100000, 0x0560c6aa, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "sza.16m", 0x100000, 0xae940f87, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "sza.18m", 0x100000, 0x4bc3c8bc, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "sza.20m", 0x100000, 0x39e674c0, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "sza.01", 0x00000, 0x20000, 0x1bc323cf),
  LOAD( ROM2, "sza.02", 0x20000, 0x20000, 0xba6a5013),
  LOAD_SW16( SMP1, "sza.11m", 0x000000, 0x200000, 0xaa47a601),
  LOAD_SW16( SMP1, "sza.12m", 0x200000, 0x200000, 0x2237bc53),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz2alj[] = // clone of sfz2al
{
  LOAD_SW16( CPU1, "szaj.03a", 0x000000, 0x80000, 0xa3802fe3),
  LOAD_SW16( CPU1, "szaj.04a", 0x080000, 0x80000, 0xe7ca87c7),
  LOAD_SW16( CPU1, "szaj.05a", 0x100000, 0x80000, 0xc88ebf88),
  LOAD_SW16( CPU1, "szaj.06a", 0x180000, 0x80000, 0x35ed5b7a),
  LOAD_SW16( CPU1, "szaj.07a", 0x200000, 0x80000, 0x975dcb3e),
  LOAD_SW16( CPU1, "szaj.08a", 0x280000, 0x80000, 0xdc73f2d7),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz2alh[] = // clone of sfz2al
{
  LOAD_SW16( CPU1, "szah.03", 0x000000, 0x80000, 0x06f93d1d),
  LOAD_SW16( CPU1, "szah.04", 0x080000, 0x80000, 0xe62ee914),
  LOAD_SW16( CPU1, "szah.05", 0x100000, 0x80000, 0x2b7f4b20),
  LOAD_SW16( CPU1, "sza.06", 0x180000, 0x80000, 0x0abda2fc),
  LOAD_SW16( CPU1, "sza.07", 0x200000, 0x80000, 0xe9430762),
  LOAD_SW16( CPU1, "sza.08", 0x280000, 0x80000, 0xb65711a9),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz2alb[] = // clone of sfz2al
{
  LOAD_SW16( CPU1, "szab.03", 0x000000, 0x80000, 0xcb436eca),
  LOAD_SW16( CPU1, "szab.04", 0x080000, 0x80000, 0x14534bea),
  LOAD_SW16( CPU1, "szab.05", 0x100000, 0x80000, 0x7fb10658),
  LOAD_SW16( CPU1, "sza.06", 0x180000, 0x80000, 0x0abda2fc),
  LOAD_SW16( CPU1, "sza.07", 0x200000, 0x80000, 0xe9430762),
  LOAD_SW16( CPU1, "sza.08", 0x280000, 0x80000, 0xb65711a9),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfa3[] =
{
  LOAD_SW16( CPU1, "sz3e.03c", 0x000000, 0x80000, 0x9762b206),
  LOAD_SW16( CPU1, "sz3e.04c", 0x080000, 0x80000, 0x5ad3f721),
  LOAD_SW16( CPU1, "sz3.05c", 0x100000, 0x80000, 0x57fd0a40),
  LOAD_SW16( CPU1, "sz3.06c", 0x180000, 0x80000, 0xf6305f8b),
  LOAD_SW16( CPU1, "sz3.07c", 0x200000, 0x80000, 0x6eab0f6f),
  LOAD_SW16( CPU1, "sz3.08c", 0x280000, 0x80000, 0x910c4a3b),
  LOAD_SW16( CPU1, "sz3.09c", 0x300000, 0x80000, 0xb29e5199),
  LOAD_SW16( CPU1, "sz3.10b", 0x380000, 0x80000, 0xdeb2ff52),
  { "sz3.13m", 0x400000, 0x0f7a60d9, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "sz3.15m", 0x400000, 0x8e933741, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "sz3.17m", 0x400000, 0xd6e98147, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "sz3.19m", 0x400000, 0xf31a728a, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "sz3.14m", 0x400000, 0x5ff98297, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "sz3.16m", 0x400000, 0x52b5bdee, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "sz3.18m", 0x400000, 0x40631ed5, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "sz3.20m", 0x400000, 0x763409b4, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "sz3.01", 0x00000, 0x20000, 0xde810084),
  LOAD( ROM2, "sz3.02", 0x20000, 0x20000, 0x72445dc4),
  LOAD_SW16( SMP1, "sz3.11m", 0x000000, 0x400000, 0x1c89eed1),
  LOAD_SW16( SMP1, "sz3.12m", 0x400000, 0x400000, 0xf392b13a),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfa3u[] = // clone of sfa3
{
  LOAD_SW16( CPU1, "sz3u.03c", 0x000000, 0x80000, 0xe007da2e),
  LOAD_SW16( CPU1, "sz3u.04c", 0x080000, 0x80000, 0x5f78f0e7),
  LOAD_SW16( CPU1, "sz3.05c", 0x100000, 0x80000, 0x57fd0a40),
  LOAD_SW16( CPU1, "sz3.06c", 0x180000, 0x80000, 0xf6305f8b),
  LOAD_SW16( CPU1, "sz3.07c", 0x200000, 0x80000, 0x6eab0f6f),
  LOAD_SW16( CPU1, "sz3.08c", 0x280000, 0x80000, 0x910c4a3b),
  LOAD_SW16( CPU1, "sz3.09c", 0x300000, 0x80000, 0xb29e5199),
  LOAD_SW16( CPU1, "sz3.10b", 0x380000, 0x80000, 0xdeb2ff52),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfa3ur1[] = // clone of sfa3
{
  LOAD_SW16( CPU1, "sz3u.03", 0x000000, 0x80000, 0xb5984a19),
  LOAD_SW16( CPU1, "sz3u.04", 0x080000, 0x80000, 0x7e8158ba),
  LOAD_SW16( CPU1, "sz3.05", 0x100000, 0x80000, 0x9b21518a),
  LOAD_SW16( CPU1, "sz3.06", 0x180000, 0x80000, 0xe7a6c3a7),
  LOAD_SW16( CPU1, "sz3.07", 0x200000, 0x80000, 0xec4c0cfd),
  LOAD_SW16( CPU1, "sz3.08", 0x280000, 0x80000, 0x5c7e7240),
  LOAD_SW16( CPU1, "sz3.09", 0x300000, 0x80000, 0xc5589553),
  LOAD_SW16( CPU1, "sz3.10", 0x380000, 0x80000, 0xa9717252),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz3j[] = // clone of sfa3
{
  LOAD_SW16( CPU1, "sz3j.03c", 0x000000, 0x80000, 0xcadf4a51),
  LOAD_SW16( CPU1, "sz3j.04c", 0x080000, 0x80000, 0xfcb31228),
  LOAD_SW16( CPU1, "sz3.05c", 0x100000, 0x80000, 0x57fd0a40),
  LOAD_SW16( CPU1, "sz3.06c", 0x180000, 0x80000, 0xf6305f8b),
  LOAD_SW16( CPU1, "sz3.07c", 0x200000, 0x80000, 0x6eab0f6f),
  LOAD_SW16( CPU1, "sz3.08c", 0x280000, 0x80000, 0x910c4a3b),
  LOAD_SW16( CPU1, "sz3.09c", 0x300000, 0x80000, 0xb29e5199),
  LOAD_SW16( CPU1, "sz3.10b", 0x380000, 0x80000, 0xdeb2ff52),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz3jr1[] = // clone of sfa3
{
  LOAD_SW16( CPU1, "sz3j.03a", 0x000000, 0x80000, 0x6ee0beae),
  LOAD_SW16( CPU1, "sz3j.04a", 0x080000, 0x80000, 0xa6e2978d),
  LOAD_SW16( CPU1, "sz3.05a", 0x100000, 0x80000, 0x05964b7d),
  LOAD_SW16( CPU1, "sz3.06a", 0x180000, 0x80000, 0x78ce2179),
  LOAD_SW16( CPU1, "sz3.07a", 0x200000, 0x80000, 0x398bf52f),
  LOAD_SW16( CPU1, "sz3.08a", 0x280000, 0x80000, 0x866d0588),
  LOAD_SW16( CPU1, "sz3.09a", 0x300000, 0x80000, 0x2180892c),
  LOAD_SW16( CPU1, "sz3.10", 0x380000, 0x80000, 0xa9717252),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz3jr2[] = // clone of sfa3
{
  LOAD_SW16( CPU1, "sz3j.03", 0x000000, 0x80000, 0xf7cb4b13),
  LOAD_SW16( CPU1, "sz3j.04", 0x080000, 0x80000, 0x0846c29d),
  LOAD_SW16( CPU1, "sz3.05", 0x100000, 0x80000, 0x9b21518a),
  LOAD_SW16( CPU1, "sz3.06", 0x180000, 0x80000, 0xe7a6c3a7),
  LOAD_SW16( CPU1, "sz3.07", 0x200000, 0x80000, 0xec4c0cfd),
  LOAD_SW16( CPU1, "sz3.08", 0x280000, 0x80000, 0x5c7e7240),
  LOAD_SW16( CPU1, "sz3.09", 0x300000, 0x80000, 0xc5589553),
  LOAD_SW16( CPU1, "sz3.10", 0x380000, 0x80000, 0xa9717252),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz3a[] = // clone of sfa3
{
  LOAD_SW16( CPU1, "sz3a.03d", 0x000000, 0x80000, 0xd7e140d6),
  LOAD_SW16( CPU1, "sz3a.04d", 0x080000, 0x80000, 0xe06869a2),
  LOAD_SW16( CPU1, "sz3.05c", 0x100000, 0x80000, 0x57fd0a40),
  LOAD_SW16( CPU1, "sz3.06c", 0x180000, 0x80000, 0xf6305f8b),
  LOAD_SW16( CPU1, "sz3.07c", 0x200000, 0x80000, 0x6eab0f6f),
  LOAD_SW16( CPU1, "sz3.08c", 0x280000, 0x80000, 0x910c4a3b),
  LOAD_SW16( CPU1, "sz3.09c", 0x300000, 0x80000, 0xb29e5199),
  LOAD_SW16( CPU1, "sz3.10b", 0x380000, 0x80000, 0xdeb2ff52),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz3ar1[] = // clone of sfa3
{
  LOAD_SW16( CPU1, "sz3a.03a", 0x000000, 0x80000, 0x29c681fd),
  LOAD_SW16( CPU1, "sz3a.04", 0x080000, 0x80000, 0x9ddd1484),
  LOAD_SW16( CPU1, "sz3.05", 0x100000, 0x80000, 0x9b21518a),
  LOAD_SW16( CPU1, "sz3.06", 0x180000, 0x80000, 0xe7a6c3a7),
  LOAD_SW16( CPU1, "sz3.07", 0x200000, 0x80000, 0xec4c0cfd),
  LOAD_SW16( CPU1, "sz3.08", 0x280000, 0x80000, 0x5c7e7240),
  LOAD_SW16( CPU1, "sz3.09", 0x300000, 0x80000, 0xc5589553),
  LOAD_SW16( CPU1, "sz3.10", 0x380000, 0x80000, 0xa9717252),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfa3h[] = // clone of sfa3
{
  LOAD_SW16( CPU1, "sz3h.03c", 0x000000, 0x80000, 0xb3b563a3),
  LOAD_SW16( CPU1, "sz3h.04c", 0x080000, 0x80000, 0x47891fec),
  LOAD_SW16( CPU1, "sz3.05c", 0x100000, 0x80000, 0x57fd0a40),
  LOAD_SW16( CPU1, "sz3.06c", 0x180000, 0x80000, 0xf6305f8b),
  LOAD_SW16( CPU1, "sz3.07c", 0x200000, 0x80000, 0x6eab0f6f),
  LOAD_SW16( CPU1, "sz3.08c", 0x280000, 0x80000, 0x910c4a3b),
  LOAD_SW16( CPU1, "sz3.09c", 0x300000, 0x80000, 0xb29e5199),
  LOAD_SW16( CPU1, "sz3.10b", 0x380000, 0x80000, 0xdeb2ff52),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfa3hr1[] = // clone of sfa3
{
  LOAD_SW16( CPU1, "sz3h.03", 0x000000, 0x80000, 0x4b16cb3e),
  LOAD_SW16( CPU1, "sz3h.04", 0x080000, 0x80000, 0x88ad2e6a),
  LOAD_SW16( CPU1, "sz3.05", 0x100000, 0x80000, 0x9b21518a),
  LOAD_SW16( CPU1, "sz3.06", 0x180000, 0x80000, 0xe7a6c3a7),
  LOAD_SW16( CPU1, "sz3.07", 0x200000, 0x80000, 0xec4c0cfd),
  LOAD_SW16( CPU1, "sz3.08", 0x280000, 0x80000, 0x5c7e7240),
  LOAD_SW16( CPU1, "sz3.09", 0x300000, 0x80000, 0xc5589553),
  LOAD_SW16( CPU1, "sz3.10", 0x380000, 0x80000, 0xa9717252),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfa3b[] = // clone of sfa3
{
  LOAD_SW16( CPU1, "sz3b.03", 0x000000, 0x80000, 0x046c9b4d),
  LOAD_SW16( CPU1, "sz3b.04", 0x080000, 0x80000, 0xda211919),
  LOAD_SW16( CPU1, "sz3.05", 0x100000, 0x80000, 0x9b21518a),
  LOAD_SW16( CPU1, "sz3.06", 0x180000, 0x80000, 0xe7a6c3a7),
  LOAD_SW16( CPU1, "sz3.07", 0x200000, 0x80000, 0xec4c0cfd),
  LOAD_SW16( CPU1, "sz3.08", 0x280000, 0x80000, 0x5c7e7240),
  LOAD_SW16( CPU1, "sz3.09", 0x300000, 0x80000, 0xc5589553),
  LOAD_SW16( CPU1, "sz3.10", 0x380000, 0x80000, 0xa9717252),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sgemf[] =
{
  LOAD_SW16( CPU1, "pcfu.03", 0x000000, 0x80000, 0xac2e8566),
  LOAD_SW16( CPU1, "pcf.04", 0x080000, 0x80000, 0xf4314c96),
  LOAD_SW16( CPU1, "pcf.05", 0x100000, 0x80000, 0x215655f6),
  LOAD_SW16( CPU1, "pcf.06", 0x180000, 0x80000, 0xea6f13ea),
  LOAD_SW16( CPU1, "pcf.07", 0x200000, 0x80000, 0x5ac6d5ea),
  { "pcf.13m", 0x400000, 0x22d72ab9, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "pcf.15m", 0x400000, 0x16a4813c, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "pcf.17m", 0x400000, 0x1097e035, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "pcf.19m", 0x400000, 0xd362d874, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "pcf.14m", 0x100000, 0x0383897c, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "pcf.16m", 0x100000, 0x76f91084, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "pcf.18m", 0x100000, 0x756c3754, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "pcf.20m", 0x100000, 0x9ec9277d, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "pcf.01", 0x00000, 0x20000, 0x254e5f33),
  LOAD( ROM2, "pcf.02", 0x20000, 0x20000, 0x6902f4f9),
  LOAD_SW16( SMP1, "pcf.11m", 0x000000, 0x400000, 0xa5dea005),
  LOAD_SW16( SMP1, "pcf.12m", 0x400000, 0x400000, 0x4ce235fe),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_pfghtj[] = // clone of sgemf
{
  LOAD_SW16( CPU1, "pcfj.03", 0x000000, 0x80000, 0x681da43e),
  LOAD_SW16( CPU1, "pcf.04", 0x080000, 0x80000, 0xf4314c96),
  LOAD_SW16( CPU1, "pcf.05", 0x100000, 0x80000, 0x215655f6),
  LOAD_SW16( CPU1, "pcf.06", 0x180000, 0x80000, 0xea6f13ea),
  LOAD_SW16( CPU1, "pcf.07", 0x200000, 0x80000, 0x5ac6d5ea),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sgemfa[] = // clone of sgemf
{
  LOAD_SW16( CPU1, "pcfa.03", 0x000000, 0x80000, 0xe17c089a),
  LOAD_SW16( CPU1, "pcf.04", 0x080000, 0x80000, 0xf4314c96),
  LOAD_SW16( CPU1, "pcf.05", 0x100000, 0x80000, 0x215655f6),
  LOAD_SW16( CPU1, "pcf.06", 0x180000, 0x80000, 0xea6f13ea),
  LOAD_SW16( CPU1, "pcf.07", 0x200000, 0x80000, 0x5ac6d5ea),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sgemfh[] = // clone of sgemf
{
  LOAD_SW16( CPU1, "pcfh.03", 0x000000, 0x80000, 0xe9103347),
  LOAD_SW16( CPU1, "pcf.04", 0x080000, 0x80000, 0xf4314c96),
  LOAD_SW16( CPU1, "pcf.05", 0x100000, 0x80000, 0x215655f6),
  LOAD_SW16( CPU1, "pcf.06", 0x180000, 0x80000, 0xea6f13ea),
  LOAD_SW16( CPU1, "pcf.07", 0x200000, 0x80000, 0x5ac6d5ea),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_spf2t[] =
{
  LOAD_SW16( CPU1, "pzfu.03a", 0x000000, 0x80000, 0x346e62ef),
  LOAD_SW16( CPU1, "pzf.04", 0x080000, 0x80000, 0xb80649e2),
/* Ignored : 	ROM_FILL(             0x000000, 0x800000, 0 ) */
  { "pzf.14m", 0x100000, 0x2d4881cb, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "pzf.16m", 0x100000, 0x4b0fd1be, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "pzf.18m", 0x100000, 0xe43aac33, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "pzf.20m", 0x100000, 0x7f536ff1, REGION_GFX1, 0x800006, LOAD_16_64 },
  LOAD( ROM2, "pzf.01", 0x00000, 0x20000, 0x600fb2a3),
  LOAD( ROM2, "pzf.02", 0x20000, 0x20000, 0x496076e0),
  LOAD_SW16( SMP1, "pzf.11m", 0x000000, 0x200000, 0x78442743),
  LOAD_SW16( SMP1, "pzf.12m", 0x200000, 0x200000, 0x399d2c7b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_spf2xj[] = // clone of spf2t
{
  LOAD_SW16( CPU1, "pzfj.03a", 0x000000, 0x80000, 0x2070554a),
  LOAD_SW16( CPU1, "pzf.04", 0x080000, 0x80000, 0xb80649e2),
/* Ignored : 	ROM_FILL(             0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_spf2ta[] = // clone of spf2t
{
  LOAD_SW16( CPU1, "pzfa.03", 0x000000, 0x80000, 0x3cecfa78),
  LOAD_SW16( CPU1, "pzf.04", 0x080000, 0x80000, 0xb80649e2),
/* Ignored : 	ROM_FILL(             0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_spf2th[] = // clone of spf2t
{
  LOAD_SW16( CPU1, "pzfh.03", 0x000000, 0x80000, 0x20510f2d),
  LOAD_SW16( CPU1, "pzf.04", 0x080000, 0x80000, 0xb80649e2),
/* Ignored : 	ROM_FILL(             0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2[] =
{
  LOAD_SW16( CPU1, "ssfe.03", 0x000000, 0x80000, 0xa597745d),
  LOAD_SW16( CPU1, "ssfe.04", 0x080000, 0x80000, 0xb082aa67),
  LOAD_SW16( CPU1, "ssfe.05", 0x100000, 0x80000, 0x02b9c137),
  LOAD_SW16( CPU1, "ssfe.06", 0x180000, 0x80000, 0x70d470c5),
  LOAD_SW16( CPU1, "ssfe.07", 0x200000, 0x80000, 0x2409001d),
  { "ssf.13m", 0x200000, 0xcf94d275, REGION_GFX1, 0x000000, LOAD_16_64 },
  { "ssf.15m", 0x200000, 0x5eb703af, REGION_GFX1, 0x000002, LOAD_16_64 },
  { "ssf.17m", 0x200000, 0xffa60e0f, REGION_GFX1, 0x000004, LOAD_16_64 },
  { "ssf.19m", 0x200000, 0x34e825c5, REGION_GFX1, 0x000006, LOAD_16_64 },
  { "ssf.14m", 0x100000, 0xb7cc32e7, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "ssf.16m", 0x100000, 0x8376ad18, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "ssf.18m", 0x100000, 0xf5b1b336, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "ssf.20m", 0x100000, 0x459d5c6b, REGION_GFX1, 0x800006, LOAD_16_64 },
  LOAD( ROM2, "ssf.01", 0x00000, 0x20000, 0xeb247e8c),
  LOAD( SMP1, "ssf.q01", 0x000000, 0x080000, 0xa6f9da5c),
  LOAD( SMP1, "ssf.q02", 0x080000, 0x080000, 0x8c66ae26),
  LOAD( SMP1, "ssf.q03", 0x100000, 0x080000, 0x695cc2ca),
  LOAD( SMP1, "ssf.q04", 0x180000, 0x080000, 0x9d9ebe32),
  LOAD( SMP1, "ssf.q05", 0x200000, 0x080000, 0x4770e7b7),
  LOAD( SMP1, "ssf.q06", 0x280000, 0x080000, 0x4e79c951),
  LOAD( SMP1, "ssf.q07", 0x300000, 0x080000, 0xcdd14313),
  LOAD( SMP1, "ssf.q08", 0x380000, 0x080000, 0x6f5a088c),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2u[] = // clone of ssf2
{
  LOAD_SW16( CPU1, "ssfu.03a", 0x000000, 0x80000, 0x72f29c33),
  LOAD_SW16( CPU1, "ssfu.04a", 0x080000, 0x80000, 0x935cea44),
  LOAD_SW16( CPU1, "ssfu.05", 0x100000, 0x80000, 0xa0acb28a),
  LOAD_SW16( CPU1, "ssfu.06", 0x180000, 0x80000, 0x47413dcf),
  LOAD_SW16( CPU1, "ssfu.07", 0x200000, 0x80000, 0xe6066077),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2a[] = // clone of ssf2
{
  LOAD_SW16( CPU1, "ssfa.03b", 0x000000, 0x80000, 0x83a059bf),
  LOAD_SW16( CPU1, "ssfa.04a", 0x080000, 0x80000, 0x5d873642),
  LOAD_SW16( CPU1, "ssfa.05", 0x100000, 0x80000, 0xf8fb4de2),
  LOAD_SW16( CPU1, "ssfa.06b", 0x180000, 0x80000, 0x3185d19d),
  LOAD_SW16( CPU1, "ssfa.07", 0x200000, 0x80000, 0x36e29217),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2ar1[] = // clone of ssf2
{
  LOAD_SW16( CPU1, "ssfa.03a", 0x000000, 0x80000, 0xd2a3c520),
  LOAD_SW16( CPU1, "ssfa.04a", 0x080000, 0x80000, 0x5d873642),
  LOAD_SW16( CPU1, "ssfa.05", 0x100000, 0x80000, 0xf8fb4de2),
  LOAD_SW16( CPU1, "ssfa.06", 0x180000, 0x80000, 0xaa8acee7),
  LOAD_SW16( CPU1, "ssfa.07", 0x200000, 0x80000, 0x36e29217),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2j[] = // clone of ssf2
{
  LOAD_SW16( CPU1, "ssfj.03b", 0x000000, 0x80000, 0x5c2e356d),
  LOAD_SW16( CPU1, "ssfj.04a", 0x080000, 0x80000, 0x013bd55c),
  LOAD_SW16( CPU1, "ssfj.05", 0x100000, 0x80000, 0x0918d19a),
  LOAD_SW16( CPU1, "ssfj.06b", 0x180000, 0x80000, 0x014e0c6d),
  LOAD_SW16( CPU1, "ssfj.07", 0x200000, 0x80000, 0xeb6a9b1b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2jr1[] = // clone of ssf2
{
  LOAD_SW16( CPU1, "ssfj.03a", 0x000000, 0x80000, 0x0bbf1304),
  LOAD_SW16( CPU1, "ssfj.04a", 0x080000, 0x80000, 0x013bd55c),
  LOAD_SW16( CPU1, "ssfj.05", 0x100000, 0x80000, 0x0918d19a),
  LOAD_SW16( CPU1, "ssfj.06", 0x180000, 0x80000, 0xd808a6cd),
  LOAD_SW16( CPU1, "ssfj.07", 0x200000, 0x80000, 0xeb6a9b1b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2jr2[] = // clone of ssf2
{
  LOAD_SW16( CPU1, "ssfj.03", 0x000000, 0x80000, 0x7eb0efed),
  LOAD_SW16( CPU1, "ssfj.04", 0x080000, 0x80000, 0xd7322164),
  LOAD_SW16( CPU1, "ssfj.05", 0x100000, 0x80000, 0x0918d19a),
  LOAD_SW16( CPU1, "ssfj.06", 0x180000, 0x80000, 0xd808a6cd),
  LOAD_SW16( CPU1, "ssfj.07", 0x200000, 0x80000, 0xeb6a9b1b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2h[] = // clone of ssf2
{
  LOAD_SW16( CPU1, "ssfh.03", 0x000000, 0x80000, 0xb086b355),
  LOAD_SW16( CPU1, "ssfh.04", 0x080000, 0x80000, 0x1e629b29),
  LOAD_SW16( CPU1, "ssfh.05", 0x100000, 0x80000, 0xb5997e10),
  LOAD_SW16( CPU1, "ssfh.06", 0x180000, 0x80000, 0x793b8fad),
  LOAD_SW16( CPU1, "ssfh.07", 0x200000, 0x80000, 0xcbb92ac3),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2tb[] = // clone of ssf2
{
  LOAD_SW16( CPU1, "ssfe.03tc", 0x000000, 0x80000, 0x496a8409),
  LOAD_SW16( CPU1, "ssfe.04tc", 0x080000, 0x80000, 0x4b45c18b),
  LOAD_SW16( CPU1, "ssfe.05t", 0x100000, 0x80000, 0x6a9c6444),
  LOAD_SW16( CPU1, "ssfe.06tb", 0x180000, 0x80000, 0xe4944fc3),
  LOAD_SW16( CPU1, "ssfe.07t", 0x200000, 0x80000, 0x2c9f4782),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2tbr1[] = // clone of ssf2
{
  LOAD_SW16( CPU1, "ssfe.03t", 0x000000, 0x80000, 0x1e018e34),
  LOAD_SW16( CPU1, "ssfe.04t", 0x080000, 0x80000, 0xac92efaf),
  LOAD_SW16( CPU1, "ssfe.05t", 0x100000, 0x80000, 0x6a9c6444),
  LOAD_SW16( CPU1, "ssfe.06t", 0x180000, 0x80000, 0xf442562b),
  LOAD_SW16( CPU1, "ssfe.07t", 0x200000, 0x80000, 0x2c9f4782),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2tbj[] = // clone of ssf2
{
  LOAD_SW16( CPU1, "ssfj.03t", 0x000000, 0x80000, 0x980d4450),
  LOAD_SW16( CPU1, "ssfj.04t", 0x080000, 0x80000, 0xb4dc1906),
  LOAD_SW16( CPU1, "ssfj.05t", 0x100000, 0x80000, 0xa7e35fbc),
  LOAD_SW16( CPU1, "ssfj.06t", 0x180000, 0x80000, 0xcb592b30),
  LOAD_SW16( CPU1, "ssfj.07t", 0x200000, 0x80000, 0x1f239515),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2tbh[] = // clone of ssf2
{
  LOAD_SW16( CPU1, "ssfh.03tb", 0x000000, 0x80000, 0x6db7d28b),
  LOAD_SW16( CPU1, "ssfh.04t", 0x080000, 0x80000, 0x0fe7d895),
  LOAD_SW16( CPU1, "ssfh.05t", 0x100000, 0x80000, 0x41be4f2d),
  LOAD_SW16( CPU1, "ssfh.06tb", 0x180000, 0x80000, 0xd2522eb1),
  LOAD_SW16( CPU1, "ssfh.07t", 0x200000, 0x80000, 0xb1c3a3c6),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2t[] =
{
  LOAD_SW16( CPU1, "sfxe.03c", 0x000000, 0x80000, 0x2fa1f396),
  LOAD_SW16( CPU1, "sfxe.04a", 0x080000, 0x80000, 0xd0bc29c6),
  LOAD_SW16( CPU1, "sfxe.05", 0x100000, 0x80000, 0x65222964),
  LOAD_SW16( CPU1, "sfxe.06a", 0x180000, 0x80000, 0x8fe9f531),
  LOAD_SW16( CPU1, "sfxe.07", 0x200000, 0x80000, 0x8a7d0cb6),
  LOAD_SW16( CPU1, "sfxe.08", 0x280000, 0x80000, 0x74c24062),
  LOAD_SW16( CPU1, "sfx.09", 0x300000, 0x80000, 0x642fae3f),
  { "sfx.13m", 0x200000, 0xcf94d275, REGION_GFX1, 0x000000, LOAD_16_64 },
  { "sfx.15m", 0x200000, 0x5eb703af, REGION_GFX1, 0x000002, LOAD_16_64 },
  { "sfx.17m", 0x200000, 0xffa60e0f, REGION_GFX1, 0x000004, LOAD_16_64 },
  { "sfx.19m", 0x200000, 0x34e825c5, REGION_GFX1, 0x000006, LOAD_16_64 },
  { "sfx.14m", 0x100000, 0xb7cc32e7, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "sfx.16m", 0x100000, 0x8376ad18, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "sfx.18m", 0x100000, 0xf5b1b336, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "sfx.20m", 0x100000, 0x459d5c6b, REGION_GFX1, 0x800006, LOAD_16_64 },
  { "sfx.21m", 0x100000, 0xe32854af, REGION_GFX1, 0xc00000, LOAD_16_64 },
  { "sfx.23m", 0x100000, 0x760f2927, REGION_GFX1, 0xc00002, LOAD_16_64 },
  { "sfx.25m", 0x100000, 0x1ee90208, REGION_GFX1, 0xc00004, LOAD_16_64 },
  { "sfx.27m", 0x100000, 0xf814400f, REGION_GFX1, 0xc00006, LOAD_16_64 },
  LOAD( ROM2, "sfx.01", 0x00000, 0x20000, 0xb47b8835),
  LOAD( ROM2, "sfx.02", 0x20000, 0x20000, 0x0022633f),
  LOAD_SW16( SMP1, "sfx.11m", 0x000000, 0x200000, 0x9bdbd476),
  LOAD_SW16( SMP1, "sfx.12m", 0x200000, 0x200000, 0xa05e3aab),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2tu[] = // clone of ssf2t
{
  LOAD_SW16( CPU1, "sfxu.03e", 0x000000, 0x80000, 0xd6ff689e),
  LOAD_SW16( CPU1, "sfxu.04a", 0x080000, 0x80000, 0x532b5ffd),
  LOAD_SW16( CPU1, "sfxu.05", 0x100000, 0x80000, 0xffa3c6de),
  LOAD_SW16( CPU1, "sfxu.06b", 0x180000, 0x80000, 0x83f9382b),
  LOAD_SW16( CPU1, "sfxu.07a", 0x200000, 0x80000, 0x6ab673e8),
  LOAD_SW16( CPU1, "sfxu.08", 0x280000, 0x80000, 0xb3c71810),
  LOAD_SW16( CPU1, "sfx.09", 0x300000, 0x80000, 0x642fae3f),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2tur1[] = // clone of ssf2t
{
  LOAD_SW16( CPU1, "sfxu.03c", 0x000000, 0x80000, 0x86e4a335),
  LOAD_SW16( CPU1, "sfxu.04a", 0x080000, 0x80000, 0x532b5ffd),
  LOAD_SW16( CPU1, "sfxu.05", 0x100000, 0x80000, 0xffa3c6de),
  LOAD_SW16( CPU1, "sfxu.06a", 0x180000, 0x80000, 0xe4c04c99),
  LOAD_SW16( CPU1, "sfxu.07", 0x200000, 0x80000, 0xd8199e41),
  LOAD_SW16( CPU1, "sfxu.08", 0x280000, 0x80000, 0xb3c71810),
  LOAD_SW16( CPU1, "sfx.09", 0x300000, 0x80000, 0x642fae3f),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2ta[] = // clone of ssf2t
{
  LOAD_SW16( CPU1, "sfxa.03c", 0x000000, 0x80000, 0x04b9ff34),
  LOAD_SW16( CPU1, "sfxa.04a", 0x080000, 0x80000, 0x16ea5f7a),
  LOAD_SW16( CPU1, "sfxa.05", 0x100000, 0x80000, 0x53d61f0c),
  LOAD_SW16( CPU1, "sfxa.06a", 0x180000, 0x80000, 0x066d09b5),
  LOAD_SW16( CPU1, "sfxa.07", 0x200000, 0x80000, 0xa428257b),
  LOAD_SW16( CPU1, "sfxa.08", 0x280000, 0x80000, 0x39be596c),
  LOAD_SW16( CPU1, "sfx.09", 0x300000, 0x80000, 0x642fae3f),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2xj[] = // clone of ssf2t
{
  LOAD_SW16( CPU1, "sfxj.03c", 0x000000, 0x80000, 0xa7417b79),
  LOAD_SW16( CPU1, "sfxj.04a", 0x080000, 0x80000, 0xaf7767b4),
  LOAD_SW16( CPU1, "sfxj.05", 0x100000, 0x80000, 0xf4ff18f5),
  LOAD_SW16( CPU1, "sfxj.06a", 0x180000, 0x80000, 0x260d0370),
  LOAD_SW16( CPU1, "sfxj.07", 0x200000, 0x80000, 0x1324d02a),
  LOAD_SW16( CPU1, "sfxj.08", 0x280000, 0x80000, 0x2de76f10),
  LOAD_SW16( CPU1, "sfx.09", 0x300000, 0x80000, 0x642fae3f),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2xjr[] = // clone of ssf2t
{
  LOAD_SW16( CPU1, "sfxo.03c", 0x000000, 0x80000, 0x2ba33dc6),
  LOAD_SW16( CPU1, "sfxo.04a", 0x080000, 0x80000, 0xba663dd7),
  LOAD_SW16( CPU1, "sfxo.05", 0x100000, 0x80000, 0x1321625c),
  LOAD_SW16( CPU1, "sfxo.06a", 0x180000, 0x80000, 0x0cc490ed),
  LOAD_SW16( CPU1, "sfxo.07", 0x200000, 0x80000, 0x64b9015e),
  LOAD_SW16( CPU1, "sfxo.08", 0x280000, 0x80000, 0xb60f4b58),
  LOAD_SW16( CPU1, "sfxo.09", 0x300000, 0x80000, 0x642fae3f),
  { "ssf.69", 0x080000, 0xe9123f9f, REGION_GFX1, 0x000000, LOAD_16_64 },
  { "ssf.70", 0x080000, 0x2f8201f3, REGION_GFX1, 0x200000, LOAD_16_64 },
  { "ssf.71", 0x080000, 0x0fa334b4, REGION_GFX1, 0x400000, LOAD_16_64 },
  { "ssf.72", 0x080000, 0xb76740d3, REGION_GFX1, 0x600000, LOAD_16_64 },
  { "ssf.73", 0x080000, 0x14f058ec, REGION_GFX1, 0x800000, LOAD_16_64 },
  { "ssf.74", 0x080000, 0x800c3ae9, REGION_GFX1, 0xa00000, LOAD_16_64 },
  { "sfx.75", 0x080000, 0x06cf540b, REGION_GFX1, 0xc00000, LOAD_16_64 },
  { "sfx.76", 0x080000, 0x71084e42, REGION_GFX1, 0xe00000, LOAD_16_64 },
  { "ssf.59", 0x080000, 0x6eb3ee4d, REGION_GFX1, 0x000002, LOAD_16_64 },
  { "ssf.60", 0x080000, 0x2bcf1eda, REGION_GFX1, 0x200002, LOAD_16_64 },
  { "ssf.61", 0x080000, 0x3330cc11, REGION_GFX1, 0x400002, LOAD_16_64 },
  { "ssf.62", 0x080000, 0x96e2ead3, REGION_GFX1, 0x600002, LOAD_16_64 },
  { "ssf.63", 0x080000, 0xe356a275, REGION_GFX1, 0x800002, LOAD_16_64 },
  { "ssf.64", 0x080000, 0xfec5698b, REGION_GFX1, 0xa00002, LOAD_16_64 },
  { "sfx.65", 0x080000, 0x69da0751, REGION_GFX1, 0xc00002, LOAD_16_64 },
  { "sfx.66", 0x080000, 0xcc53ec15, REGION_GFX1, 0xe00002, LOAD_16_64 },
  { "ssf.79", 0x080000, 0xcf0d44a8, REGION_GFX1, 0x000004, LOAD_16_64 },
  { "ssf.80", 0x080000, 0x56a153a4, REGION_GFX1, 0x200004, LOAD_16_64 },
  { "ssf.81", 0x080000, 0x5484e5f6, REGION_GFX1, 0x400004, LOAD_16_64 },
  { "ssf.82", 0x080000, 0xfce6b7f5, REGION_GFX1, 0x600004, LOAD_16_64 },
  { "ssf.83", 0x080000, 0x042d7970, REGION_GFX1, 0x800004, LOAD_16_64 },
  { "ssf.84", 0x080000, 0x88c472e6, REGION_GFX1, 0xa00004, LOAD_16_64 },
  { "sfx.85", 0x080000, 0xa7d66348, REGION_GFX1, 0xc00004, LOAD_16_64 },
  { "sfx.86", 0x080000, 0xcf9119c8, REGION_GFX1, 0xe00004, LOAD_16_64 },
  { "ssf.89", 0x080000, 0x6d374ad9, REGION_GFX1, 0x000006, LOAD_16_64 },
  { "ssf.90", 0x080000, 0x34cf8bcf, REGION_GFX1, 0x200006, LOAD_16_64 },
  { "ssf.91", 0x080000, 0xd796ea3f, REGION_GFX1, 0x400006, LOAD_16_64 },
  { "ssf.92", 0x080000, 0xc85fb7e3, REGION_GFX1, 0x600006, LOAD_16_64 },
  { "ssf.93", 0x080000, 0x6c50c2b5, REGION_GFX1, 0x800006, LOAD_16_64 },
  { "ssf.94", 0x080000, 0x59549f63, REGION_GFX1, 0xa00006, LOAD_16_64 },
  { "sfx.95", 0x080000, 0x86c97869, REGION_GFX1, 0xc00006, LOAD_16_64 },
  { "sfx.96", 0x080000, 0x1c0e1989, REGION_GFX1, 0xe00006, LOAD_16_64 },
  LOAD_SW16( SMP1, "ssf.51a", 0x000000, 0x080000, 0x9eda6954),
  LOAD_SW16( SMP1, "ssf.52a", 0x080000, 0x080000, 0x355f6589),
  LOAD_SW16( SMP1, "ssf.53a", 0x100000, 0x080000, 0xd5d08a05),
  LOAD_SW16( SMP1, "ssf.54a", 0x180000, 0x080000, 0x930725eb),
  LOAD_SW16( SMP1, "ssf.55a", 0x200000, 0x080000, 0x827abf3c),
  LOAD_SW16( SMP1, "ssf.56a", 0x280000, 0x080000, 0x3919c0e5),
  LOAD_SW16( SMP1, "ssf.57a", 0x300000, 0x080000, 0x1ba9bfa6),
  LOAD_SW16( SMP1, "ssf.58a", 0x380000, 0x080000, 0x0c89a272),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vhunt2[] =
{
  LOAD_SW16( CPU1, "vh2j.03a", 0x000000, 0x80000, 0x9ae8f186),
  LOAD_SW16( CPU1, "vh2j.04a", 0x080000, 0x80000, 0xe2fabf53),
  LOAD_SW16( CPU1, "vh2j.05", 0x100000, 0x80000, 0xde34f624),
  LOAD_SW16( CPU1, "vh2j.06", 0x180000, 0x80000, 0x6a3b9897),
  LOAD_SW16( CPU1, "vh2j.07", 0x200000, 0x80000, 0xb021c029),
  LOAD_SW16( CPU1, "vh2j.08", 0x280000, 0x80000, 0xac873dff),
  LOAD_SW16( CPU1, "vh2j.09", 0x300000, 0x80000, 0xeaefce9c),
  LOAD_SW16( CPU1, "vh2j.10", 0x380000, 0x80000, 0x11730952),
  { "vh2.13m", 0x400000, 0x3b02ddaa, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "vh2.15m", 0x400000, 0x4e40de66, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "vh2.17m", 0x400000, 0xb31d00c9, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "vh2.19m", 0x400000, 0x149be3ab, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "vh2.14m", 0x400000, 0xcd09bd63, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "vh2.16m", 0x400000, 0xe0182c15, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "vh2.18m", 0x400000, 0x778dc4f6, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "vh2.20m", 0x400000, 0x605d9d1d, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "vh2.01", 0x00000, 0x20000, 0x67b9f779),
  LOAD( ROM2, "vh2.02", 0x20000, 0x20000, 0xaaf15fcb),
  LOAD_SW16( SMP1, "vh2.11m", 0x000000, 0x400000, 0x38922efd),
  LOAD_SW16( SMP1, "vh2.12m", 0x400000, 0x400000, 0x6e2430af),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vhunt2r1[] = // clone of vhunt2
{
  LOAD_SW16( CPU1, "vh2j.03", 0x000000, 0x80000, 0x1a5feb13),
  LOAD_SW16( CPU1, "vh2j.04", 0x080000, 0x80000, 0x434611a5),
  LOAD_SW16( CPU1, "vh2j.05", 0x100000, 0x80000, 0xde34f624),
  LOAD_SW16( CPU1, "vh2j.06", 0x180000, 0x80000, 0x6a3b9897),
  LOAD_SW16( CPU1, "vh2j.07", 0x200000, 0x80000, 0xb021c029),
  LOAD_SW16( CPU1, "vh2j.08", 0x280000, 0x80000, 0xac873dff),
  LOAD_SW16( CPU1, "vh2j.09", 0x300000, 0x80000, 0xeaefce9c),
  LOAD_SW16( CPU1, "vh2j.10", 0x380000, 0x80000, 0x11730952),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vsav[] =
{
  LOAD_SW16( CPU1, "vm3e.03d", 0x000000, 0x80000, 0xf5962a8c),
  LOAD_SW16( CPU1, "vm3e.04d", 0x080000, 0x80000, 0x21b40ea2),
  LOAD_SW16( CPU1, "vm3.05a", 0x100000, 0x80000, 0x4118e00f),
  LOAD_SW16( CPU1, "vm3.06a", 0x180000, 0x80000, 0x2f4fd3a9),
  LOAD_SW16( CPU1, "vm3.07b", 0x200000, 0x80000, 0xcbda91b8),
  LOAD_SW16( CPU1, "vm3.08a", 0x280000, 0x80000, 0x6ca47259),
  LOAD_SW16( CPU1, "vm3.09b", 0x300000, 0x80000, 0xf4a339e3),
  LOAD_SW16( CPU1, "vm3.10b", 0x380000, 0x80000, 0xfffbb5b8),
  { "vm3.13m", 0x400000, 0xfd8a11eb, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "vm3.15m", 0x400000, 0xdd1e7d4e, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "vm3.17m", 0x400000, 0x6b89445e, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "vm3.19m", 0x400000, 0x3830fdc7, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "vm3.14m", 0x400000, 0xc1a28e6c, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "vm3.16m", 0x400000, 0x194a7304, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "vm3.18m", 0x400000, 0xdf9a9f47, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "vm3.20m", 0x400000, 0xc22fc3d9, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "vm3.01", 0x00000, 0x20000, 0xf778769b),
  LOAD( ROM2, "vm3.02", 0x20000, 0x20000, 0xcc09faa1),
  LOAD_SW16( SMP1, "vm3.11m", 0x000000, 0x400000, 0xe80e956e),
  LOAD_SW16( SMP1, "vm3.12m", 0x400000, 0x400000, 0x9cd71557),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vsavu[] = // clone of vsav
{
  LOAD_SW16( CPU1, "vm3u.03d", 0x000000, 0x80000, 0x1f295274),
  LOAD_SW16( CPU1, "vm3u.04d", 0x080000, 0x80000, 0xc46adf81),
  LOAD_SW16( CPU1, "vm3.05a", 0x100000, 0x80000, 0x4118e00f),
  LOAD_SW16( CPU1, "vm3.06a", 0x180000, 0x80000, 0x2f4fd3a9),
  LOAD_SW16( CPU1, "vm3.07b", 0x200000, 0x80000, 0xcbda91b8),
  LOAD_SW16( CPU1, "vm3.08a", 0x280000, 0x80000, 0x6ca47259),
  LOAD_SW16( CPU1, "vm3.09b", 0x300000, 0x80000, 0xf4a339e3),
  LOAD_SW16( CPU1, "vm3.10b", 0x380000, 0x80000, 0xfffbb5b8),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vsavj[] = // clone of vsav
{
  LOAD_SW16( CPU1, "vm3j.03d", 0x000000, 0x80000, 0x2a2e74a4),
  LOAD_SW16( CPU1, "vm3j.04d", 0x080000, 0x80000, 0x1c2427bc),
  LOAD_SW16( CPU1, "vm3j.05a", 0x100000, 0x80000, 0x95ce88d5),
  LOAD_SW16( CPU1, "vm3j.06b", 0x180000, 0x80000, 0x2c4297e0),
  LOAD_SW16( CPU1, "vm3j.07b", 0x200000, 0x80000, 0xa38aaae7),
  LOAD_SW16( CPU1, "vm3j.08a", 0x280000, 0x80000, 0x5773e5c9),
  LOAD_SW16( CPU1, "vm3j.09b", 0x300000, 0x80000, 0xd064f8b9),
  LOAD_SW16( CPU1, "vm3j.10b", 0x380000, 0x80000, 0x434518e9),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vsava[] = // clone of vsav
{
  LOAD_SW16( CPU1, "vm3a.03d", 0x000000, 0x80000, 0x44c1198f),
  LOAD_SW16( CPU1, "vm3a.04d", 0x080000, 0x80000, 0x2218b781),
  LOAD_SW16( CPU1, "vm3.05a", 0x100000, 0x80000, 0x4118e00f),
  LOAD_SW16( CPU1, "vm3.06a", 0x180000, 0x80000, 0x2f4fd3a9),
  LOAD_SW16( CPU1, "vm3.07b", 0x200000, 0x80000, 0xcbda91b8),
  LOAD_SW16( CPU1, "vm3.08a", 0x280000, 0x80000, 0x6ca47259),
  LOAD_SW16( CPU1, "vm3.09b", 0x300000, 0x80000, 0xf4a339e3),
  LOAD_SW16( CPU1, "vm3.10b", 0x380000, 0x80000, 0xfffbb5b8),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vsavh[] = // clone of vsav
{
  LOAD_SW16( CPU1, "vm3h.03a", 0x000000, 0x80000, 0x7cc62df8),
  LOAD_SW16( CPU1, "vm3h.04d", 0x080000, 0x80000, 0xd716f3b5),
  LOAD_SW16( CPU1, "vm3.05a", 0x100000, 0x80000, 0x4118e00f),
  LOAD_SW16( CPU1, "vm3.06a", 0x180000, 0x80000, 0x2f4fd3a9),
  LOAD_SW16( CPU1, "vm3.07b", 0x200000, 0x80000, 0xcbda91b8),
  LOAD_SW16( CPU1, "vm3.08a", 0x280000, 0x80000, 0x6ca47259),
  LOAD_SW16( CPU1, "vm3.09b", 0x300000, 0x80000, 0xf4a339e3),
  LOAD_SW16( CPU1, "vm3.10b", 0x380000, 0x80000, 0xfffbb5b8),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vsav2[] =
{
  LOAD_SW16( CPU1, "vs2j.03", 0x000000, 0x80000, 0x89fd86b4),
  LOAD_SW16( CPU1, "vs2j.04", 0x080000, 0x80000, 0x107c091b),
  LOAD_SW16( CPU1, "vs2j.05", 0x100000, 0x80000, 0x61979638),
  LOAD_SW16( CPU1, "vs2j.06", 0x180000, 0x80000, 0xf37c5bc2),
  LOAD_SW16( CPU1, "vs2j.07", 0x200000, 0x80000, 0x8f885809),
  LOAD_SW16( CPU1, "vs2j.08", 0x280000, 0x80000, 0x2018c120),
  LOAD_SW16( CPU1, "vs2j.09", 0x300000, 0x80000, 0xfac3c217),
  LOAD_SW16( CPU1, "vs2j.10", 0x380000, 0x80000, 0xeb490213),
  { "vs2.13m", 0x400000, 0x5c852f52, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "vs2.15m", 0x400000, 0xa20f58af, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "vs2.17m", 0x400000, 0x39db59ad, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "vs2.19m", 0x400000, 0x00c763a7, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "vs2.14m", 0x400000, 0xcd09bd63, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "vs2.16m", 0x400000, 0xe0182c15, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "vs2.18m", 0x400000, 0x778dc4f6, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "vs2.20m", 0x400000, 0x605d9d1d, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "vs2.01", 0x00000, 0x20000, 0x35190139),
  LOAD( ROM2, "vs2.02", 0x20000, 0x20000, 0xc32dba09),
  LOAD_SW16( SMP1, "vs2.11m", 0x000000, 0x400000, 0xd67e47b7),
  LOAD_SW16( SMP1, "vs2.12m", 0x400000, 0x400000, 0x6d020a14),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmcota[] =
{
  LOAD_SW16( CPU1, "xmne.03f", 0x000000, 0x80000, 0x5a726d13),
  LOAD_SW16( CPU1, "xmne.04f", 0x080000, 0x80000, 0x06a83f3a),
  LOAD_SW16( CPU1, "xmne.05b", 0x100000, 0x80000, 0x87b0ed0f),
  LOAD_SW16( CPU1, "xmn.06a", 0x180000, 0x80000, 0x1b86a328),
  LOAD_SW16( CPU1, "xmn.07a", 0x200000, 0x80000, 0x2c142a44),
  LOAD_SW16( CPU1, "xmn.08a", 0x280000, 0x80000, 0xf712d44f),
  LOAD_SW16( CPU1, "xmn.09a", 0x300000, 0x80000, 0x9241cae8),
  LOAD_SW16( CPU1, "xmne.10b", 0x380000, 0x80000, 0xcb36b0a4),
  { "xmn.13m", 0x400000, 0xbf4df073, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "xmn.15m", 0x400000, 0x4d7e4cef, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "xmn.17m", 0x400000, 0x513eea17, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "xmn.19m", 0x400000, 0xd23897fc, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "xmn.14m", 0x400000, 0x778237b7, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "xmn.16m", 0x400000, 0x67b36948, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "xmn.18m", 0x400000, 0x015a7c4c, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "xmn.20m", 0x400000, 0x9dde2758, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "xmn.01a", 0x00000, 0x20000, 0x40f479ea),
  LOAD( ROM2, "xmn.02a", 0x20000, 0x20000, 0x39d9b5ad),
  LOAD_SW16( SMP1, "xmn.11m", 0x000000, 0x200000, 0xc848a6bc),
  LOAD_SW16( SMP1, "xmn.12m", 0x200000, 0x200000, 0x729c188f),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmcotar1[] = // clone of xmcota
{
  LOAD_SW16( CPU1, "xmne.03e", 0x000000, 0x80000, 0xa9a09b09),
  LOAD_SW16( CPU1, "xmne.04e", 0x080000, 0x80000, 0x52fa2106),
  LOAD_SW16( CPU1, "xmn.05a", 0x100000, 0x80000, 0xac0d7759),
  LOAD_SW16( CPU1, "xmn.06a", 0x180000, 0x80000, 0x1b86a328),
  LOAD_SW16( CPU1, "xmn.07a", 0x200000, 0x80000, 0x2c142a44),
  LOAD_SW16( CPU1, "xmn.08a", 0x280000, 0x80000, 0xf712d44f),
  LOAD_SW16( CPU1, "xmn.09a", 0x300000, 0x80000, 0x9241cae8),
  LOAD_SW16( CPU1, "xmn.10a", 0x380000, 0x80000, 0x53c0eab9),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmcotau[] = // clone of xmcota
{
  LOAD_SW16( CPU1, "xmnu.03e", 0x000000, 0x80000, 0x0bafeb0e),
  LOAD_SW16( CPU1, "xmnu.04e", 0x080000, 0x80000, 0xc29bdae3),
  LOAD_SW16( CPU1, "xmn.05a", 0x100000, 0x80000, 0xac0d7759),
  LOAD_SW16( CPU1, "xmn.06a", 0x180000, 0x80000, 0x1b86a328),
  LOAD_SW16( CPU1, "xmn.07a", 0x200000, 0x80000, 0x2c142a44),
  LOAD_SW16( CPU1, "xmn.08a", 0x280000, 0x80000, 0xf712d44f),
  LOAD_SW16( CPU1, "xmn.09a", 0x300000, 0x80000, 0x9241cae8),
  LOAD_SW16( CPU1, "xmn.10a", 0x380000, 0x80000, 0x53c0eab9),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmcotah[] = // clone of xmcota
{
  LOAD_SW16( CPU1, "xmnh.03f", 0x000000, 0x80000, 0xe4b85a90),
  LOAD_SW16( CPU1, "xmnh.04f", 0x080000, 0x80000, 0x7dfe1406),
  LOAD_SW16( CPU1, "xmnh.05b", 0x100000, 0x80000, 0x87b0ed0f),
  LOAD_SW16( CPU1, "xmn.06a", 0x180000, 0x80000, 0x1b86a328),
  LOAD_SW16( CPU1, "xmn.07a", 0x200000, 0x80000, 0x2c142a44),
  LOAD_SW16( CPU1, "xmn.08a", 0x280000, 0x80000, 0xf712d44f),
  LOAD_SW16( CPU1, "xmn.09a", 0x300000, 0x80000, 0x9241cae8),
  LOAD_SW16( CPU1, "xmnh.10b", 0x380000, 0x80000, 0xcb36b0a4),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmcotahr1[] = // clone of xmcota
{
  LOAD_SW16( CPU1, "xmnh.03d", 0x000000, 0x80000, 0x63b0a84f),
  LOAD_SW16( CPU1, "xmnh.04d", 0x080000, 0x80000, 0xb1b9b727),
  LOAD_SW16( CPU1, "xmn.05a", 0x100000, 0x80000, 0xac0d7759),
  LOAD_SW16( CPU1, "xmn.06a", 0x180000, 0x80000, 0x1b86a328),
  LOAD_SW16( CPU1, "xmn.07a", 0x200000, 0x80000, 0x2c142a44),
  LOAD_SW16( CPU1, "xmn.08a", 0x280000, 0x80000, 0xf712d44f),
  LOAD_SW16( CPU1, "xmn.09a", 0x300000, 0x80000, 0x9241cae8),
  LOAD_SW16( CPU1, "xmn.10a", 0x380000, 0x80000, 0x53c0eab9),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmcotaj[] = // clone of xmcota
{
  LOAD_SW16( CPU1, "xmnj.03e", 0x000000, 0x80000, 0x0df29f5f),
  LOAD_SW16( CPU1, "xmnj.04e", 0x080000, 0x80000, 0x4a65833b),
  LOAD_SW16( CPU1, "xmn.05a", 0x100000, 0x80000, 0xac0d7759),
  LOAD_SW16( CPU1, "xmn.06a", 0x180000, 0x80000, 0x1b86a328),
  LOAD_SW16( CPU1, "xmn.07a", 0x200000, 0x80000, 0x2c142a44),
  LOAD_SW16( CPU1, "xmn.08a", 0x280000, 0x80000, 0xf712d44f),
  LOAD_SW16( CPU1, "xmn.09a", 0x300000, 0x80000, 0x9241cae8),
  LOAD_SW16( CPU1, "xmn.10a", 0x380000, 0x80000, 0x53c0eab9),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmcotaj1[] = // clone of xmcota
{
  LOAD_SW16( CPU1, "xmnj.03d", 0x000000, 0x80000, 0x79086d62),
  LOAD_SW16( CPU1, "xmnj.04d", 0x080000, 0x80000, 0x38eed613),
  LOAD_SW16( CPU1, "xmn.05", 0x100000, 0x80000, 0xc3ed62a2),
  LOAD_SW16( CPU1, "xmn.06", 0x180000, 0x80000, 0xf03c52e1),
  LOAD_SW16( CPU1, "xmn.07", 0x200000, 0x80000, 0x325626b1),
  LOAD_SW16( CPU1, "xmn.08", 0x280000, 0x80000, 0x7194ea10),
  LOAD_SW16( CPU1, "xmn.09", 0x300000, 0x80000, 0xae946df3),
  LOAD_SW16( CPU1, "xmn.10", 0x380000, 0x80000, 0x32a6be1d),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmcotaj2[] = // clone of xmcota
{
  LOAD_SW16( CPU1, "xmnj.03b", 0x000000, 0x80000, 0xc8175fb3),
  LOAD_SW16( CPU1, "xmnj.04b", 0x080000, 0x80000, 0x54b3fba3),
  LOAD_SW16( CPU1, "xmn.05", 0x100000, 0x80000, 0xc3ed62a2),
  LOAD_SW16( CPU1, "xmn.06", 0x180000, 0x80000, 0xf03c52e1),
  LOAD_SW16( CPU1, "xmn.07", 0x200000, 0x80000, 0x325626b1),
  LOAD_SW16( CPU1, "xmn.08", 0x280000, 0x80000, 0x7194ea10),
  LOAD_SW16( CPU1, "xmn.09", 0x300000, 0x80000, 0xae946df3),
  LOAD_SW16( CPU1, "xmn.10", 0x380000, 0x80000, 0x32a6be1d),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmcotaj3[] = // clone of xmcota
{
  LOAD_SW16( CPU1, "xmnj.03a", 0x000000, 0x80000, 0x00761611),
  LOAD_SW16( CPU1, "xmnj.04a", 0x080000, 0x80000, 0x614d3f60),
  LOAD_SW16( CPU1, "xmn.05", 0x100000, 0x80000, 0xc3ed62a2),
  LOAD_SW16( CPU1, "xmn.06", 0x180000, 0x80000, 0xf03c52e1),
  LOAD_SW16( CPU1, "xmn.07", 0x200000, 0x80000, 0x325626b1),
  LOAD_SW16( CPU1, "xmn.08", 0x280000, 0x80000, 0x7194ea10),
  LOAD_SW16( CPU1, "xmn.09", 0x300000, 0x80000, 0xae946df3),
  LOAD_SW16( CPU1, "xmn.10", 0x380000, 0x80000, 0x32a6be1d),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmcotajr[] = // clone of xmcota
{
  LOAD_SW16( CPU1, "xmno.03a", 0x000000, 0x80000, 0x7ab19acf),
  LOAD_SW16( CPU1, "xmno.04a", 0x080000, 0x80000, 0x7615dd21),
  LOAD_SW16( CPU1, "xmno.05a", 0x100000, 0x80000, 0x0303d672),
  LOAD_SW16( CPU1, "xmno.06a", 0x180000, 0x80000, 0x332839a5),
  LOAD_SW16( CPU1, "xmno.07", 0x200000, 0x80000, 0x6255e8d5),
  LOAD_SW16( CPU1, "xmno.08", 0x280000, 0x80000, 0xb8ebe77c),
  LOAD_SW16( CPU1, "xmno.09", 0x300000, 0x80000, 0x5440d950),
  LOAD_SW16( CPU1, "xmno.10a", 0x380000, 0x80000, 0xb8296966),
  LOAD( ROM2, "xmn.01", 0x00000, 0x20000, 0x7178336e),
  LOAD( ROM2, "xmn.02", 0x20000, 0x20000, 0x0ec58501),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmcotaa[] = // clone of xmcota
{
  LOAD_SW16( CPU1, "xmna.03e", 0x000000, 0x80000, 0xf1ade6e7),
  LOAD_SW16( CPU1, "xmna.04e", 0x080000, 0x80000, 0xb5a8843d),
  LOAD_SW16( CPU1, "xmn.05a", 0x100000, 0x80000, 0xac0d7759),
  LOAD_SW16( CPU1, "xmn.06a", 0x180000, 0x80000, 0x1b86a328),
  LOAD_SW16( CPU1, "xmn.07a", 0x200000, 0x80000, 0x2c142a44),
  LOAD_SW16( CPU1, "xmn.08a", 0x280000, 0x80000, 0xf712d44f),
  LOAD_SW16( CPU1, "xmn.09a", 0x300000, 0x80000, 0x9241cae8),
  LOAD_SW16( CPU1, "xmn.10a", 0x380000, 0x80000, 0x53c0eab9),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmcotaar1[] = // clone of xmcota
{
  LOAD_SW16( CPU1, "xmna.03a", 0x000000, 0x80000, 0x7df8b27e),
  LOAD_SW16( CPU1, "xmna.04a", 0x080000, 0x80000, 0xb44e30a7),
  LOAD_SW16( CPU1, "xmn.05", 0x100000, 0x80000, 0xc3ed62a2),
  LOAD_SW16( CPU1, "xmn.06", 0x180000, 0x80000, 0xf03c52e1),
  LOAD_SW16( CPU1, "xmn.07", 0x200000, 0x80000, 0x325626b1),
  LOAD_SW16( CPU1, "xmn.08", 0x280000, 0x80000, 0x7194ea10),
  LOAD_SW16( CPU1, "xmn.09", 0x300000, 0x80000, 0xae946df3),
  LOAD_SW16( CPU1, "xmn.10", 0x380000, 0x80000, 0x32a6be1d),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmvsf[] =
{
  LOAD_SW16( CPU1, "xvse.03f", 0x000000, 0x80000, 0xdb06413f),
  LOAD_SW16( CPU1, "xvse.04f", 0x080000, 0x80000, 0xef015aef),
  LOAD_SW16( CPU1, "xvs.05a", 0x100000, 0x80000, 0x7db6025d),
  LOAD_SW16( CPU1, "xvs.06a", 0x180000, 0x80000, 0xe8e2c75c),
  LOAD_SW16( CPU1, "xvs.07", 0x200000, 0x80000, 0x08f0abed),
  LOAD_SW16( CPU1, "xvs.08", 0x280000, 0x80000, 0x81929675),
  LOAD_SW16( CPU1, "xvs.09", 0x300000, 0x80000, 0x9641f36b),
  { "xvs.13m", 0x400000, 0xf6684efd, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "xvs.15m", 0x400000, 0x29109221, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "xvs.17m", 0x400000, 0x92db3474, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "xvs.19m", 0x400000, 0x3733473c, REGION_GFX1, 0x0000006, LOAD_16_64 },
  { "xvs.14m", 0x400000, 0xbcac2e41, REGION_GFX1, 0x1000000, LOAD_16_64 },
  { "xvs.16m", 0x400000, 0xea04a272, REGION_GFX1, 0x1000002, LOAD_16_64 },
  { "xvs.18m", 0x400000, 0xb0def86a, REGION_GFX1, 0x1000004, LOAD_16_64 },
  { "xvs.20m", 0x400000, 0x4b40ff9f, REGION_GFX1, 0x1000006, LOAD_16_64 },
  LOAD( ROM2, "xvs.01", 0x00000, 0x20000, 0x3999e93a),
  LOAD( ROM2, "xvs.02", 0x20000, 0x20000, 0x101bdee9),
  LOAD_SW16( SMP1, "xvs.11m", 0x000000, 0x200000, 0x9cadcdbc),
  LOAD_SW16( SMP1, "xvs.12m", 0x200000, 0x200000, 0x7b11e460),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmvsfr1[] = // clone of xmvsf
{
  LOAD_SW16( CPU1, "xvse.03d", 0x000000, 0x80000, 0x5ae5bd3b),
  LOAD_SW16( CPU1, "xvse.04d", 0x080000, 0x80000, 0x5eb9c02e),
  LOAD_SW16( CPU1, "xvs.05a", 0x100000, 0x80000, 0x7db6025d),
  LOAD_SW16( CPU1, "xvs.06a", 0x180000, 0x80000, 0xe8e2c75c),
  LOAD_SW16( CPU1, "xvs.07", 0x200000, 0x80000, 0x08f0abed),
  LOAD_SW16( CPU1, "xvs.08", 0x280000, 0x80000, 0x81929675),
  LOAD_SW16( CPU1, "xvs.09", 0x300000, 0x80000, 0x9641f36b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmvsfu[] = // clone of xmvsf
{
  LOAD_SW16( CPU1, "xvsu.03k", 0x000000, 0x80000, 0x8739ef61),
  LOAD_SW16( CPU1, "xvsu.04k", 0x080000, 0x80000, 0xe11d35c1),
  LOAD_SW16( CPU1, "xvs.05a", 0x100000, 0x80000, 0x7db6025d),
  LOAD_SW16( CPU1, "xvs.06a", 0x180000, 0x80000, 0xe8e2c75c),
  LOAD_SW16( CPU1, "xvs.07", 0x200000, 0x80000, 0x08f0abed),
  LOAD_SW16( CPU1, "xvs.08", 0x280000, 0x80000, 0x81929675),
  LOAD_SW16( CPU1, "xvs.09", 0x300000, 0x80000, 0x9641f36b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmvsfur1[] = // clone of xmvsf
{
  LOAD_SW16( CPU1, "xvsu.03h", 0x000000, 0x80000, 0x5481155a),
  LOAD_SW16( CPU1, "xvsu.04h", 0x080000, 0x80000, 0x1e236388),
  LOAD_SW16( CPU1, "xvs.05a", 0x100000, 0x80000, 0x7db6025d),
  LOAD_SW16( CPU1, "xvs.06a", 0x180000, 0x80000, 0xe8e2c75c),
  LOAD_SW16( CPU1, "xvs.07", 0x200000, 0x80000, 0x08f0abed),
  LOAD_SW16( CPU1, "xvs.08", 0x280000, 0x80000, 0x81929675),
  LOAD_SW16( CPU1, "xvs.09", 0x300000, 0x80000, 0x9641f36b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmvsfj[] = // clone of xmvsf
{
  LOAD_SW16( CPU1, "xvsj.03i", 0x000000, 0x80000, 0xef24da96),
  LOAD_SW16( CPU1, "xvsj.04i", 0x080000, 0x80000, 0x70a59b35),
  LOAD_SW16( CPU1, "xvs.05a", 0x100000, 0x80000, 0x7db6025d),
  LOAD_SW16( CPU1, "xvs.06a", 0x180000, 0x80000, 0xe8e2c75c),
  LOAD_SW16( CPU1, "xvs.07", 0x200000, 0x80000, 0x08f0abed),
  LOAD_SW16( CPU1, "xvs.08", 0x280000, 0x80000, 0x81929675),
  LOAD_SW16( CPU1, "xvs.09", 0x300000, 0x80000, 0x9641f36b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmvsfjr1[] = // clone of xmvsf
{
  LOAD_SW16( CPU1, "xvsj.03d", 0x000000, 0x80000, 0xbeb81de9),
  LOAD_SW16( CPU1, "xvsj.04d", 0x080000, 0x80000, 0x23d11271),
  LOAD_SW16( CPU1, "xvs.05a", 0x100000, 0x80000, 0x7db6025d),
  LOAD_SW16( CPU1, "xvs.06a", 0x180000, 0x80000, 0xe8e2c75c),
  LOAD_SW16( CPU1, "xvs.07", 0x200000, 0x80000, 0x08f0abed),
  LOAD_SW16( CPU1, "xvs.08", 0x280000, 0x80000, 0x81929675),
  LOAD_SW16( CPU1, "xvs.09", 0x300000, 0x80000, 0x9641f36b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmvsfjr2[] = // clone of xmvsf
{
  LOAD_SW16( CPU1, "xvsj.03c", 0x000000, 0x80000, 0x180656a1),
  LOAD_SW16( CPU1, "xvsj.04c", 0x080000, 0x80000, 0x5832811c),
  LOAD_SW16( CPU1, "xvs.05", 0x100000, 0x80000, 0x030e0e1e),
  LOAD_SW16( CPU1, "xvs.06", 0x180000, 0x80000, 0x5d04a8ff),
  LOAD_SW16( CPU1, "xvs.07", 0x200000, 0x80000, 0x08f0abed),
  LOAD_SW16( CPU1, "xvs.08", 0x280000, 0x80000, 0x81929675),
  LOAD_SW16( CPU1, "xvs.09", 0x300000, 0x80000, 0x9641f36b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmvsfa[] = // clone of xmvsf
{
  LOAD_SW16( CPU1, "xvsa.03k", 0x000000, 0x80000, 0xd0cca7a8),
  LOAD_SW16( CPU1, "xvsa.04k", 0x080000, 0x80000, 0x8c8e76fd),
  LOAD_SW16( CPU1, "xvs.05a", 0x100000, 0x80000, 0x7db6025d),
  LOAD_SW16( CPU1, "xvs.06a", 0x180000, 0x80000, 0xe8e2c75c),
  LOAD_SW16( CPU1, "xvs.07", 0x200000, 0x80000, 0x08f0abed),
  LOAD_SW16( CPU1, "xvs.08", 0x280000, 0x80000, 0x81929675),
  LOAD_SW16( CPU1, "xvs.09", 0x300000, 0x80000, 0x9641f36b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmvsfar1[] = // clone of xmvsf
{
  LOAD_SW16( CPU1, "xvsa.03e", 0x000000, 0x80000, 0x9bdde21c),
  LOAD_SW16( CPU1, "xvsa.04e", 0x080000, 0x80000, 0x33300edf),
  LOAD_SW16( CPU1, "xvs.05a", 0x100000, 0x80000, 0x7db6025d),
  LOAD_SW16( CPU1, "xvs.06a", 0x180000, 0x80000, 0xe8e2c75c),
  LOAD_SW16( CPU1, "xvs.07", 0x200000, 0x80000, 0x08f0abed),
  LOAD_SW16( CPU1, "xvs.08", 0x280000, 0x80000, 0x81929675),
  LOAD_SW16( CPU1, "xvs.09", 0x300000, 0x80000, 0x9641f36b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmvsfar2[] = // clone of xmvsf
{
  LOAD_SW16( CPU1, "xvsa.03d", 0x000000, 0x80000, 0x2b164fd7),
  LOAD_SW16( CPU1, "xvsa.04d", 0x080000, 0x80000, 0x2d32f039),
  LOAD_SW16( CPU1, "xvs.05a", 0x100000, 0x80000, 0x7db6025d),
  LOAD_SW16( CPU1, "xvs.06a", 0x180000, 0x80000, 0xe8e2c75c),
  LOAD_SW16( CPU1, "xvs.07", 0x200000, 0x80000, 0x08f0abed),
  LOAD_SW16( CPU1, "xvs.08", 0x280000, 0x80000, 0x81929675),
  LOAD_SW16( CPU1, "xvs.09", 0x300000, 0x80000, 0x9641f36b),
  LOAD( ROM2, "xvs.01", 0x00000, 0x20000, 0x3999e93a),
  LOAD( ROM2, "xvsa.02", 0x20000, 0x20000, 0x19272e4c),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmvsfh[] = // clone of xmvsf
{
  LOAD_SW16( CPU1, "xvsh.03a", 0x000000, 0x80000, 0xd4fffb04),
  LOAD_SW16( CPU1, "xvsh.04a", 0x080000, 0x80000, 0x1b4ea638),
  LOAD_SW16( CPU1, "xvs.05a", 0x100000, 0x80000, 0x7db6025d),
  LOAD_SW16( CPU1, "xvs.06a", 0x180000, 0x80000, 0xe8e2c75c),
  LOAD_SW16( CPU1, "xvs.07", 0x200000, 0x80000, 0x08f0abed),
  LOAD_SW16( CPU1, "xvs.08", 0x280000, 0x80000, 0x81929675),
  LOAD_SW16( CPU1, "xvs.09", 0x300000, 0x80000, 0x9641f36b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmvsfb[] = // clone of xmvsf
{
  LOAD_SW16( CPU1, "xvsb.03h", 0x000000, 0x80000, 0x05baccca),
  LOAD_SW16( CPU1, "xvsb.04h", 0x080000, 0x80000, 0xe350c755),
  LOAD_SW16( CPU1, "xvs.05a", 0x100000, 0x80000, 0x7db6025d),
  LOAD_SW16( CPU1, "xvs.06a", 0x180000, 0x80000, 0xe8e2c75c),
  LOAD_SW16( CPU1, "xvs.07", 0x200000, 0x80000, 0x08f0abed),
  LOAD_SW16( CPU1, "xvs.08", 0x280000, 0x80000, 0x81929675),
  LOAD_SW16( CPU1, "xvs.09", 0x300000, 0x80000, 0x9641f36b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_1944d[] = // clone of 1944
{
  LOAD_SW16( CPU1, "nffud.03", 0x000000, 0x80000, 0x28e8aae4),
  LOAD_SW16( CPU1, "nff.04", 0x080000, 0x80000, 0xdba1c66e),
  LOAD_SW16( CPU1, "nffu.05", 0x100000, 0x80000, 0xea813eb7),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_19xxd[] = // clone of 19xx
{
  LOAD_SW16( CPU1, "19xud.03", 0x000000, 0x80000, 0xf81b60e5),
  LOAD_SW16( CPU1, "19xud.04", 0x080000, 0x80000, 0xcc44638c),
  LOAD_SW16( CPU1, "19xud.05", 0x100000, 0x80000, 0x33a168de),
  LOAD_SW16( CPU1, "19xud.06", 0x180000, 0x80000, 0xe0111282),
  LOAD_SW16( CPU1, "19x.07", 0x200000, 0x80000, 0x61c0296c),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz2ad[] = // clone of sfa2
{
  LOAD_SW16( CPU1, "sz2ad.03a", 0x000000, 0x80000, 0x017f8fab),
  LOAD_SW16( CPU1, "sz2ad.04a", 0x080000, 0x80000, 0xf50e5ea2),
  LOAD_SW16( CPU1, "sz2.05a", 0x100000, 0x80000, 0x98e8e992),
  LOAD_SW16( CPU1, "sz2.06", 0x180000, 0x80000, 0x5b1d49c0),
  LOAD_SW16( CPU1, "sz2a.07a", 0x200000, 0x80000, 0x0aed2494),
  LOAD_SW16( CPU1, "sz2.08", 0x280000, 0x80000, 0x0fe8585d),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_avspd[] = // clone of avsp
{
  LOAD_SW16( CPU1, "avped.03d", 0x000000, 0x80000, 0x66aa8aad),
  LOAD_SW16( CPU1, "avped.04d", 0x080000, 0x80000, 0x579306c2),
  LOAD_SW16( CPU1, "avp.05d", 0x100000, 0x80000, 0xfbfb5d7a),
  LOAD_SW16( CPU1, "avpd.06", 0x180000, 0x80000, 0x63094539),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_batcird[] = // clone of batcir
{
  LOAD_SW16( CPU1, "btced.03", 0x000000, 0x80000, 0x0737db6d),
  LOAD_SW16( CPU1, "btced.04", 0x080000, 0x80000, 0xef1a8823),
  LOAD_SW16( CPU1, "btced.05", 0x100000, 0x80000, 0x20bdbb14),
  LOAD_SW16( CPU1, "btced.06", 0x180000, 0x80000, 0xb4d8f5bc),
  LOAD_SW16( CPU1, "btc.07", 0x200000, 0x80000, 0x7322d5db),
  LOAD_SW16( CPU1, "btc.08", 0x280000, 0x80000, 0x6aac85ab),
  LOAD_SW16( CPU1, "btc.09", 0x300000, 0x80000, 0x1203db08),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddtodd[] = // clone of ddtod
{
  LOAD_SW16( CPU1, "daded.03c", 0x000000, 0x80000, 0x843330f4),
  LOAD_SW16( CPU1, "daded.04c", 0x080000, 0x80000, 0x306f14fc),
  LOAD_SW16( CPU1, "daded.05c", 0x100000, 0x80000, 0x8c6b8328),
  LOAD_SW16( CPU1, "dad.06a", 0x180000, 0x80000, 0x6225495a),
  LOAD_SW16( CPU1, "dadd.07a", 0x200000, 0x80000, 0x0f0df6cc),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddsomud[] = // clone of ddsom
{
  LOAD_SW16( CPU1, "dd2ud.03g", 0x000000, 0x80000, 0x816f695a),
  LOAD_SW16( CPU1, "dd2ud.04g", 0x080000, 0x80000, 0x7cc81c6b),
  LOAD_SW16( CPU1, "dd2.05g", 0x100000, 0x80000, 0x5eb1991c),
  LOAD_SW16( CPU1, "dd2.06g", 0x180000, 0x80000, 0xc26b5e55),
  LOAD_SW16( CPU1, "dd2.07", 0x200000, 0x80000, 0x909a0b8b),
  LOAD_SW16( CPU1, "dd2.08", 0x280000, 0x80000, 0xe53c4d01),
  LOAD_SW16( CPU1, "dd2.09", 0x300000, 0x80000, 0x5f86279f),
  LOAD_SW16( CPU1, "dd2d.10", 0x380000, 0x80000, 0x0c172f8f),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ecofghtrd[] = // clone of ecofghtr
{
  LOAD_SW16( CPU1, "ueced.03", 0x000000, 0x80000, 0xac725d2b),
  LOAD_SW16( CPU1, "ueced.04", 0x080000, 0x80000, 0xf800138d),
  LOAD_SW16( CPU1, "ueced.05", 0x100000, 0x80000, 0xeb6a12f2),
  LOAD_SW16( CPU1, "ueced.06", 0x180000, 0x80000, 0x8380ec9a),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_gigawingjd[] = // clone of gigawing
{
  LOAD_SW16( CPU1, "ggwjd.03a", 0x000000, 0x80000, 0xcb1c756e),
  LOAD_SW16( CPU1, "ggwjd.04a", 0x080000, 0x80000, 0xfa158e04),
  LOAD_SW16( CPU1, "ggwjd.05a", 0x100000, 0x80000, 0x1c5bc4e7),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_gigawingd[] = // clone of gigawing
{
  LOAD_SW16( CPU1, "ggwu_d.03", 0x000000, 0x80000, 0xdde92dfa),
  LOAD_SW16( CPU1, "ggwu_d.04", 0x080000, 0x80000, 0xe0509ae2),
  LOAD_SW16( CPU1, "ggw_d.05", 0x100000, 0x80000, 0x722d0042),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_hsf2d[] = // clone of hsf2
{
  LOAD_SW16( CPU1, "hs2ad.03", 0x000000, 0x80000, 0x0153d371),
  LOAD_SW16( CPU1, "hs2ad.04", 0x080000, 0x80000, 0x0276b78a),
  LOAD_SW16( CPU1, "hs2.05", 0x100000, 0x80000, 0xdde34a35),
  LOAD_SW16( CPU1, "hs2.06", 0x180000, 0x80000, 0xf4e56dda),
  LOAD_SW16( CPU1, "hs2.07", 0x200000, 0x80000, 0xee4420fc),
  LOAD_SW16( CPU1, "hs2.08", 0x280000, 0x80000, 0xc9441533),
  LOAD_SW16( CPU1, "hs2.09", 0x300000, 0x80000, 0x3fc638a8),
  LOAD_SW16( CPU1, "hs2.10", 0x380000, 0x80000, 0x20d0f9e4),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_megamn2d[] = // clone of megaman2
{
  LOAD_SW16( CPU1, "rm2ud.03", 0x000000, 0x80000, 0xd3635f25),
  LOAD_SW16( CPU1, "rm2ud.04", 0x080000, 0x80000, 0x768a1705),
  LOAD_SW16( CPU1, "rm2.05", 0x100000, 0x80000, 0x02ee9efc),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
/* Ignored : 	ROM_FILL(               0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mvscud[] = // clone of mvsc
{
  LOAD_SW16( CPU1, "mvcud.03d", 0x000000, 0x80000, 0x75cde3e5),
  LOAD_SW16( CPU1, "mvcud.04d", 0x080000, 0x80000, 0xb32ea484),
  LOAD_SW16( CPU1, "mvc.05a", 0x100000, 0x80000, 0x2d8c8e86),
  LOAD_SW16( CPU1, "mvc.06a", 0x180000, 0x80000, 0x8528e1f5),
  LOAD_SW16( CPU1, "mvcd.07", 0x200000, 0x80000, 0x205293e9),
  LOAD_SW16( CPU1, "mvc.08", 0x280000, 0x80000, 0xbc002fcd),
  LOAD_SW16( CPU1, "mvc.09", 0x300000, 0x80000, 0xc67b26df),
  LOAD_SW16( CPU1, "mvc.10", 0x380000, 0x80000, 0x0fdd1e26),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_nwarrud[] = // clone of nwarr
{
  LOAD_SW16( CPU1, "vphud.03f", 0x000000, 0x80000, 0x20d4d5a8),
  LOAD_SW16( CPU1, "vphud.04c", 0x080000, 0x80000, 0x61be9b42),
  LOAD_SW16( CPU1, "vphud.05e", 0x100000, 0x80000, 0x1ba906d8),
  LOAD_SW16( CPU1, "vphu.06c", 0x180000, 0x80000, 0x08c04cdb),
  LOAD_SW16( CPU1, "vphu.07b", 0x200000, 0x80000, 0xb5a5ab19),
  LOAD_SW16( CPU1, "vphu.08b", 0x280000, 0x80000, 0x51bb20fb),
  LOAD_SW16( CPU1, "vphu.09b", 0x300000, 0x80000, 0x41a64205),
  LOAD_SW16( CPU1, "vphud.10b", 0x380000, 0x80000, 0x9619adad),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ringdstd[] = // clone of ringdest
{
  LOAD_SW16( CPU1, "smbed.03b", 0x000000, 0x80000, 0xf6fba4cd),
  LOAD_SW16( CPU1, "smbed.04b", 0x080000, 0x80000, 0x193bc493),
  LOAD_SW16( CPU1, "smbed.05b", 0x100000, 0x80000, 0x168cccbb),
  LOAD_SW16( CPU1, "smbed.06b", 0x180000, 0x80000, 0x04673262),
  LOAD_SW16( CPU1, "smb.07", 0x200000, 0x80000, 0xb9a11577),
  LOAD_SW16( CPU1, "smb.08", 0x280000, 0x80000, 0xf931b76b),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfad[] = // clone of sfa
{
  LOAD_SW16( CPU1, "sfzed.03d", 0x000000, 0x80000, 0xa1a54827),
  LOAD_SW16( CPU1, "sfz.04b", 0x080000, 0x80000, 0x8b73b0e5),
  LOAD_SW16( CPU1, "sfz.05a", 0x100000, 0x80000, 0x0810544d),
  LOAD_SW16( CPU1, "sfz.06", 0x180000, 0x80000, 0x806e8f38),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
/* Ignored : 	ROM_FILL(               0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshud[] = // clone of msh
{
  LOAD_SW16( CPU1, "mshud.03", 0x000000, 0x80000, 0xc1d8c4c6),
  LOAD_SW16( CPU1, "mshud.04", 0x080000, 0x80000, 0xe73dda16),
  LOAD_SW16( CPU1, "mshud.05", 0x100000, 0x80000, 0x3b493e84),
  LOAD_SW16( CPU1, "msh.06b", 0x180000, 0x80000, 0x803e3fa4),
  LOAD_SW16( CPU1, "msh.07a", 0x200000, 0x80000, 0xc45f8e27),
  LOAD_SW16( CPU1, "msh.08a", 0x280000, 0x80000, 0x9ca6f12c),
  LOAD_SW16( CPU1, "msh.09a", 0x300000, 0x80000, 0x82ec27af),
  LOAD_SW16( CPU1, "msh.10b", 0x380000, 0x80000, 0x8d931196),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz2ald[] = // clone of sfz2al
{
  LOAD_SW16( CPU1, "szaad.03", 0x000000, 0x80000, 0x89f9483b),
  LOAD_SW16( CPU1, "szaad.04", 0x080000, 0x80000, 0xaef27ae5),
  LOAD_SW16( CPU1, "szaa.05", 0x100000, 0x80000, 0xf053a55e),
  LOAD_SW16( CPU1, "szaa.06", 0x180000, 0x80000, 0xcfc0e7a8),
  LOAD_SW16( CPU1, "szaa.07", 0x200000, 0x80000, 0x5feb8b20),
  LOAD_SW16( CPU1, "szaa.08", 0x280000, 0x80000, 0x6eb6d412),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfa3ud[] = // clone of sfa3
{
  LOAD_SW16( CPU1, "sz3ud.03c", 0x000000, 0x80000, 0x6db8add7),
  LOAD_SW16( CPU1, "sz3ud.04c", 0x080000, 0x80000, 0xd9c65a26),
  LOAD_SW16( CPU1, "sz3.05c", 0x100000, 0x80000, 0x57fd0a40),
  LOAD_SW16( CPU1, "sz3.06c", 0x180000, 0x80000, 0xf6305f8b),
  LOAD_SW16( CPU1, "sz3.07c", 0x200000, 0x80000, 0x6eab0f6f),
  LOAD_SW16( CPU1, "sz3.08c", 0x280000, 0x80000, 0x910c4a3b),
  LOAD_SW16( CPU1, "sz3.09c", 0x300000, 0x80000, 0xb29e5199),
  LOAD_SW16( CPU1, "sz3.10b", 0x380000, 0x80000, 0xdeb2ff52),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_spf2xjd[] = // clone of spf2t
{
  LOAD_SW16( CPU1, "pzfjd.03a", 0x000000, 0x80000, 0x5e85ed08),
  LOAD_SW16( CPU1, "pzf.04", 0x080000, 0x80000, 0xb80649e2),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vsavd[] = // clone of vsav
{
  LOAD_SW16( CPU1, "vm3ed.03d", 0x000000, 0x80000, 0x97d805e3),
  LOAD_SW16( CPU1, "vm3ed.04d", 0x080000, 0x80000, 0x5e07fdce),
  LOAD_SW16( CPU1, "vm3.05a", 0x100000, 0x80000, 0x4118e00f),
  LOAD_SW16( CPU1, "vm3.06a", 0x180000, 0x80000, 0x2f4fd3a9),
  LOAD_SW16( CPU1, "vm3.07b", 0x200000, 0x80000, 0xcbda91b8),
  LOAD_SW16( CPU1, "vm3.08a", 0x280000, 0x80000, 0x6ca47259),
  LOAD_SW16( CPU1, "vm3.09b", 0x300000, 0x80000, 0xf4a339e3),
  LOAD_SW16( CPU1, "vm3.10b", 0x380000, 0x80000, 0xfffbb5b8),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmcotar1d[] = // clone of xmcota
{
  LOAD_SW16( CPU1, "xmned.03e", 0x000000, 0x80000, 0xbef56003),
  LOAD_SW16( CPU1, "xmned.04e", 0x080000, 0x80000, 0xb1a21fa6),
  LOAD_SW16( CPU1, "xmn.05a", 0x100000, 0x80000, 0xac0d7759),
  LOAD_SW16( CPU1, "xmn.06a", 0x180000, 0x80000, 0x1b86a328),
  LOAD_SW16( CPU1, "xmn.07a", 0x200000, 0x80000, 0x2c142a44),
  LOAD_SW16( CPU1, "xmn.08a", 0x280000, 0x80000, 0xf712d44f),
  LOAD_SW16( CPU1, "xmn.09a", 0x300000, 0x80000, 0x9241cae8),
  LOAD_SW16( CPU1, "xmn.10a", 0x380000, 0x80000, 0x53c0eab9),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xmvsfu1d[] = // clone of xmvsf
{
  LOAD_SW16( CPU1, "xvsud.03h", 0x000000, 0x80000, 0x4e2e76b7),
//  ROM_LOAD16_WORD_SWAP( "xvsd.05a",  0x100000, 0x80000, CRC(de347b11) SHA1(297ae207811df9a4973de1df00b2efaa14a0137d) ) // bad dump?
  LOAD_SW16( CPU1, "xvsud.04h", 0x080000, 0x80000, 0x290c61a7),
  LOAD_SW16( CPU1, "xvs.05a", 0x100000, 0x80000, 0x7db6025d),
//  ROM_LOAD16_WORD_SWAP( "xvsd.07",   0x200000, 0x80000, CRC(f761ded7) SHA1(e49277398734dea044e7c8ec16800db196905e6f) ) // bad dump ?
  LOAD_SW16( CPU1, "xvs.06a", 0x180000, 0x80000, 0xe8e2c75c),
  LOAD_SW16( CPU1, "xvs.07", 0x200000, 0x80000, 0x08f0abed),
  LOAD_SW16( CPU1, "xvs.08", 0x280000, 0x80000, 0x81929675),
  LOAD_SW16( CPU1, "xvs.09", 0x300000, 0x80000, 0x9641f36b),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_dstlku1d[] = // clone of dstlk
{
  LOAD_SW16( CPU1, "vamud.03a", 0x000000, 0x80000, 0x47b7a680),
  LOAD_SW16( CPU1, "vamud.04a", 0x080000, 0x80000, 0x3b7a4939),
  LOAD_SW16( CPU1, "vamu.05a", 0x100000, 0x80000, 0x673ed50a),
  LOAD_SW16( CPU1, "vamu.06a", 0x180000, 0x80000, 0xf2377be7),
  LOAD_SW16( CPU1, "vamu.07a", 0x200000, 0x80000, 0xd8f498c4),
  LOAD_SW16( CPU1, "vamu.08a", 0x280000, 0x80000, 0xe6a8a1a0),
  LOAD_SW16( CPU1, "vamud.09a", 0x300000, 0x80000, 0x8b333a19),
  LOAD_SW16( CPU1, "vamu.10a", 0x380000, 0x80000, 0xc1a3d9be),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_progearud[] = // clone of progear
{
  LOAD_SW16( CPU1, "pgau_d.03", 0x000000, 0x80000, 0xba22b9c5),
  LOAD_SW16( CPU1, "pgau_d.04", 0x080000, 0x80000, 0xdf3927ef),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_progearjd[] = // clone of progear
{
  LOAD_SW16( CPU1, "pgaj_d.03", 0x000000, 0x80000, 0x0271f3a3),
  LOAD_SW16( CPU1, "pgaj_d.04", 0x080000, 0x80000, 0xbe4b7799),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_progearjbl[] = // clone of progear
{
  LOAD_SW16( CPU1, "pgaj_bl.03", 0x000000, 0x80000, 0x4fef676c),
  LOAD_SW16( CPU1, "pgaj_bl.04", 0x080000, 0x80000, 0xa069bd3b),
  { "pga.13m", 0x400000, 0x5194c198, REGION_GFX1, 0x0000000, LOAD_16_64 },
  { "pga.15m", 0x400000, 0xb794e83f, REGION_GFX1, 0x0000002, LOAD_16_64 },
  { "pga.17m", 0x400000, 0x87f22918, REGION_GFX1, 0x0000004, LOAD_16_64 },
  { "pga.19m", 0x400000, 0x65ffb45b, REGION_GFX1, 0x0000006, LOAD_16_64 },
  LOAD_SW16( SMP1, "pga.11m", 0x000000, 0x400000, 0xabdd224e),
  LOAD_SW16( SMP1, "pga.12m", 0x400000, 0x400000, 0xdac53406),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2ud[] = // clone of ssf2
{
  LOAD_SW16( CPU1, "ssfud.03a", 0x000000, 0x80000, 0xfad5daf8),
  LOAD_SW16( CPU1, "ssfud.04a", 0x080000, 0x80000, 0x0d31af65),
  LOAD_SW16( CPU1, "ssfud.05", 0x100000, 0x80000, 0x75c651ef),
  LOAD_SW16( CPU1, "ssfud.06", 0x180000, 0x80000, 0x85c3ec00),
  LOAD_SW16( CPU1, "ssfud.07", 0x200000, 0x80000, 0x247e2504),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2tbd[] = // clone of ssf2
{
  LOAD_SW16( CPU1, "ssfed.3tc", 0x000000, 0x80000, 0x5d86caf8),
  LOAD_SW16( CPU1, "ssfed.4tc", 0x080000, 0x80000, 0xf6e1f98d),
  LOAD_SW16( CPU1, "ssfed.5t", 0x100000, 0x80000, 0x75c651ef),
  LOAD_SW16( CPU1, "ssfed.6tb", 0x180000, 0x80000, 0x9adac7d7),
  LOAD_SW16( CPU1, "ssfed.7t", 0x200000, 0x80000, 0x84f54db3),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssf2xjd[] = // clone of ssf2t
{
  LOAD_SW16( CPU1, "sfxjd.03c", 0x000000, 0x80000, 0x316de996),
  LOAD_SW16( CPU1, "sfxjd.04a", 0x080000, 0x80000, 0x9bf3bb2e),
  LOAD_SW16( CPU1, "sfxjd.05", 0x100000, 0x80000, 0xc63358d0),
  LOAD_SW16( CPU1, "sfxjd.06a", 0x180000, 0x80000, 0xccb29808),
  LOAD_SW16( CPU1, "sfxjd.07", 0x200000, 0x80000, 0x61f94982),
  LOAD_SW16( CPU1, "sfxjd.08", 0x280000, 0x80000, 0xd399c36c),
  LOAD_SW16( CPU1, "sfxd.09", 0x300000, 0x80000, 0x0b3a6196),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sgemfd[] = // clone of sgemf
{
  LOAD_SW16( CPU1, "pcfud.03", 0x000000, 0x80000, 0x8b83674a),
  LOAD_SW16( CPU1, "pcfd.04", 0x080000, 0x80000, 0xb58f1d03),
  LOAD_SW16( CPU1, "pcf.05", 0x100000, 0x80000, 0x215655f6),
  LOAD_SW16( CPU1, "pcf.06", 0x180000, 0x80000, 0xea6f13ea),
  LOAD_SW16( CPU1, "pcf.07", 0x200000, 0x80000, 0x5ac6d5ea),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_armwar1d[] = // clone of armwar
{
  LOAD_SW16( CPU1, "pwged.03b", 0x000000, 0x80000, 0x496bd483),
  LOAD_SW16( CPU1, "pwged.04b", 0x080000, 0x80000, 0x9bd6a38f),
  LOAD_SW16( CPU1, "pwged.05a", 0x100000, 0x80000, 0x4c11d30f),
  LOAD_SW16( CPU1, "pwg.06", 0x180000, 0x80000, 0x87a60ce8),
  LOAD_SW16( CPU1, "pwg.07", 0x200000, 0x80000, 0xf7b148df),
  LOAD_SW16( CPU1, "pwg.08", 0x280000, 0x80000, 0xcc62823e),
  LOAD_SW16( CPU1, "pwg.09", 0x300000, 0x80000, 0xddc85ca6),
  LOAD_SW16( CPU1, "pwg.10", 0x380000, 0x80000, 0x07c4fb28),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_dimahoud[] = // clone of dimahoo
{
  LOAD_SW16( CPU1, "gmdud.03", 0x000000, 0x80000, 0x12888435),
  LOAD_SW16( CPU1, "gmd.04", 0x080000, 0x80000, 0x37485567),
  LOAD_SW16( CPU1, "gmd.05", 0x100000, 0x80000, 0xda269ffb),
  LOAD_SW16( CPU1, "gmdud.06", 0x180000, 0x80000, 0xd825efda),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mmatrixd[] = // clone of mmatrix
{
  LOAD_SW16( CPU1, "mmxud.03", 0x000000, 0x80000, 0x36711e60),
  LOAD_SW16( CPU1, "mmxud.04", 0x080000, 0x80000, 0x4687226f),
  LOAD_SW16( CPU1, "mmxud.05", 0x100000, 0x80000, 0x52124398),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vhunt2d[] = // clone of vhunt2
{
  LOAD_SW16( CPU1, "vh2j_d.03a", 0x000000, 0x80000, 0x696e0157),
  LOAD_SW16( CPU1, "vh2j_d.04a", 0x080000, 0x80000, 0xced9bba3),
  LOAD_SW16( CPU1, "vh2j.05", 0x100000, 0x80000, 0xde34f624),
  LOAD_SW16( CPU1, "vh2j.06", 0x180000, 0x80000, 0x6a3b9897),
  LOAD_SW16( CPU1, "vh2j.07", 0x200000, 0x80000, 0xb021c029),
  LOAD_SW16( CPU1, "vh2j.08", 0x280000, 0x80000, 0xac873dff),
  LOAD_SW16( CPU1, "vh2j.09", 0x300000, 0x80000, 0xeaefce9c),
  LOAD_SW16( CPU1, "vh2j.10", 0x380000, 0x80000, 0x11730952),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vsav2d[] = // clone of vsav2
{
  LOAD_SW16( CPU1, "vs2j_d.03", 0x000000, 0x80000, 0x50865f7b),
  LOAD_SW16( CPU1, "vs2j_d.04", 0x080000, 0x80000, 0xc3bff0e3),
  LOAD_SW16( CPU1, "vs2j.05", 0x100000, 0x80000, 0x61979638),
  LOAD_SW16( CPU1, "vs2j.06", 0x180000, 0x80000, 0xf37c5bc2),
  LOAD_SW16( CPU1, "vs2j.07", 0x200000, 0x80000, 0x8f885809),
  LOAD_SW16( CPU1, "vs2j.08", 0x280000, 0x80000, 0x2018c120),
  LOAD_SW16( CPU1, "vs2j.09", 0x300000, 0x80000, 0xfac3c217),
  LOAD_SW16( CPU1, "vs2j.10", 0x380000, 0x80000, 0xeb490213),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_csclub1d[] = // clone of csclub
{
  LOAD_SW16( CPU1, "csce_d.03", 0x000000, 0x80000, 0x5aedc6e6),
  LOAD_SW16( CPU1, "csce_d.04", 0x080000, 0x80000, 0xa3d9aa25),
  LOAD_SW16( CPU1, "csce_d.05", 0x100000, 0x80000, 0x0915c9d1),
  LOAD_SW16( CPU1, "csce_d.06", 0x180000, 0x80000, 0x09c77d99),
  LOAD_SW16( CPU1, "csc_d.07", 0x200000, 0x80000, 0x77478e25),
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_cybotsud[] = // clone of cybots
{
  LOAD_SW16( CPU1, "cybu_d.03", 0x000000, 0x80000, 0xee7560fb),
  LOAD_SW16( CPU1, "cybu_d.04", 0x080000, 0x80000, 0x7e7425a0),
  LOAD_SW16( CPU1, "cyb.05", 0x100000, 0x80000, 0xec40408e),
  LOAD_SW16( CPU1, "cyb.06", 0x180000, 0x80000, 0x1ad0bed2),
  LOAD_SW16( CPU1, "cyb.07", 0x200000, 0x80000, 0x6245a39a),
  LOAD_SW16( CPU1, "cyb.08", 0x280000, 0x80000, 0x4b48e223),
  LOAD_SW16( CPU1, "cyb.09", 0x300000, 0x80000, 0xe15238f6),
  LOAD_SW16( CPU1, "cyb.10", 0x380000, 0x80000, 0x75f4003b),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mshvsfu1d[] = // clone of mshvsf
{
  LOAD_SW16( CPU1, "mvsu_d.03d", 0x000000, 0x80000, 0x1c88bee3),
  LOAD_SW16( CPU1, "mvsu_d.04d", 0x080000, 0x80000, 0x1e8b2535),
  LOAD_SW16( CPU1, "mvs_d.05a", 0x100000, 0x80000, 0x373856fb),
  LOAD_SW16( CPU1, "mvs.06a", 0x180000, 0x80000, 0x959f3030),
  LOAD_SW16( CPU1, "mvs.07b", 0x200000, 0x80000, 0x7f915bdb),
  LOAD_SW16( CPU1, "mvs.08a", 0x280000, 0x80000, 0xc2813884),
  LOAD_SW16( CPU1, "mvs.09b", 0x300000, 0x80000, 0x3ba08818),
  LOAD_SW16( CPU1, "mvs.10b", 0x380000, 0x80000, 0xcf0dba98),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_spf2td[] = // clone of spf2t
{
  LOAD_SW16( CPU1, "pzfu_d.03a", 0x000000, 0x80000, 0x7836b903),
  LOAD_SW16( CPU1, "pzf.04", 0x080000, 0x80000, 0xb80649e2),
/* Ignored : 	ROM_FILL( 0x000000, 0x100000, 0 ) */
/* Ignored : 	ROM_FILL(              0x000000, 0x800000, 0 ) */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz3jr2d[] = // clone of sfa3
{
  LOAD_SW16( CPU1, "sz3j_d.03", 0x000000, 0x80000, 0xb0436151),
  LOAD_SW16( CPU1, "sz3j_d.04", 0x080000, 0x80000, 0x642d8170),
  LOAD_SW16( CPU1, "sz3.05", 0x100000, 0x80000, 0x9b21518a),
  LOAD_SW16( CPU1, "sz3.06", 0x180000, 0x80000, 0xe7a6c3a7),
  LOAD_SW16( CPU1, "sz3.07", 0x200000, 0x80000, 0xec4c0cfd),
  LOAD_SW16( CPU1, "sz3.08", 0x280000, 0x80000, 0x5c7e7240),
  LOAD_SW16( CPU1, "sz3.09", 0x300000, 0x80000, 0xc5589553),
  LOAD_SW16( CPU1, "sz3.10", 0x380000, 0x80000, 0xa9717252),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sfz2jd[] = // clone of sfa2
{
  LOAD_SW16( CPU1, "sz2j_d.03a", 0x000000, 0x80000, 0xb7325df8),
  LOAD_SW16( CPU1, "sz2j_d.04a", 0x080000, 0x80000, 0xa1022a3e),
  LOAD_SW16( CPU1, "sz2.05a", 0x100000, 0x80000, 0x98e8e992),
  LOAD_SW16( CPU1, "sz2.06", 0x180000, 0x80000, 0x5b1d49c0),
  LOAD_SW16( CPU1, "sz2j.07a", 0x200000, 0x80000, 0xd910b2a2),
  LOAD_SW16( CPU1, "sz2.08", 0x280000, 0x80000, 0x0fe8585d),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct INPUT_INFO input_p4b4[] =
{
  INP0( P1_RIGHT, 0x00, 0x01 ),
  INP0( P1_LEFT, 0x00, 0x02 ),
  INP0( P1_DOWN, 0x00, 0x04 ),
  INP0( P1_UP, 0x00, 0x08 ),
  INP0( P1_B1, 0x00, 0x10 ),
  INP0( P1_B2, 0x00, 0x20 ),
  INP0( P1_B3, 0x00, 0x40 ),
  INP0( P1_B4, 0x00, 0x80 ),
  INP0( P2_RIGHT, 0x01, 0x01 ),
  INP0( P2_LEFT, 0x01, 0x02 ),
  INP0( P2_DOWN, 0x01, 0x04 ),
  INP0( P2_UP, 0x01, 0x08 ),
  INP0( P2_B1, 0x01, 0x10 ),
  INP0( P2_B2, 0x01, 0x20 ),
  INP0( P2_B3, 0x01, 0x40 ),
  INP0( P2_B4, 0x01, 0x80 ),

  INP0( P3_RIGHT, 0x02, 0x01 ),
  INP0( P3_LEFT, 0x02, 0x02 ),
  INP0( P3_DOWN, 0x02, 0x04 ),
  INP0( P3_UP, 0x02, 0x08 ),
  INP0( P3_B1, 0x02, 0x10 ),
  INP0( P3_B2, 0x02, 0x20 ),
  INP0( P3_B3, 0x02, 0x40 ),
  INP0( P3_B4, 0x02, 0x80 ),
  INP0( P4_RIGHT, 0x03, 0x01 ),
  INP0( P4_LEFT, 0x03, 0x02 ),
  INP0( P4_DOWN, 0x03, 0x04 ),
  INP0( P4_UP, 0x03, 0x08 ),
  INP0( P4_B1, 0x03, 0x10 ),
  INP0( P4_B2, 0x03, 0x20 ),
  INP0( P4_B3, 0x03, 0x40 ),
  INP0( P4_B4, 0x03, 0x80 ),

  INP0( TEST, 0x04, 0x02 ),
  INP0( SERVICE, 0x04, 0x04 ),
  INP0( P1_START, 0x05, 0x01 ),
  INP0( P2_START, 0x05, 0x02 ),
  INP0( P3_START, 0x05, 0x04 ),
  INP0( P4_START, 0x05, 0x08 ),
  INP0( COIN1, 0x05, 0x10 ),
  INP0( COIN2, 0x05, 0x20 ),
  INP0( COIN3, 0x05, 0x40 ),
  INP0( COIN4, 0x05, 0x80 ),
   END_INPUT
};

static struct INPUT_INFO input_p4b3[] =
{
    INCL_INP( p4b4 ),
    INP0( UNUSED, 3, 0x80 ), // P4_B4
    INP0( UNUSED, 0x02, 0x80 ), // P3_B4
    INP0( UNUSED, 0x01, 0x80 ), // P2_B4
    INP0( UNUSED, 0x00, 0x80 ), // P1_B4
   END_INPUT
};

static struct INPUT_INFO input_p4b2[] =
{
    INCL_INP( p4b3 ),
  INP0( UNUSED, 0x03, 0x40 ), // P4_B3
  INP0( UNUSED, 0x02, 0x40 ), // P3_B3
  INP0( UNUSED, 0x01, 0x40 ), // P2_B3
  INP0( UNUSED, 0x00, 0x40 ), // P1_B3
  END_INPUT
};

static struct INPUT_INFO input_p3b4[] =
{
    INCL_INP( p4b4 ),
    INP0( UNUSED, 0x03, 0xff ), // p4
    INP0( UNUSED, 0x05, 0x08 ), // P4_START
    INP0( UNUSED, 0x05, 0x80 ), // COIN4
    END_INPUT
};

static struct INPUT_INFO input_p3b3[] =
{
    INCL_INP( p3b4 ),
    INP0( UNUSED, 0x02, 0x80 ), // P3_B4
    INP0( UNUSED, 0x01, 0x80 ), // P2_B4
    INP0( UNUSED, 0x00, 0x80 ), // P1_B4
    END_INPUT
};

static struct INPUT_INFO input_p2b4[] =
{
    INCL_INP( p3b4 ),
    INP0( UNUSED, 2, 0xff ), // bye P3
    INP0( UNUSED, 0x05, 0x04 ), // P3_START
    INP0( UNUSED, 0x05, 0x40 ), // COIN3
   END_INPUT
};

static struct INPUT_INFO input_p2b3[] =
{
    INCL_INP( p2b4 ),
    INP0( UNUSED, 0x00, 0x80 ), // P1_B4
    INP0( UNUSED, 0x01, 0x80 ), // P2_B4
    END_INPUT
};

static struct INPUT_INFO input_p2b2[] =
{
    INCL_INP( p2b3 ),
    INP0( UNUSED, 0x00, 0x40 ), // P1_B3
    INP0( UNUSED, 0x01, 0x40 ), // P2_B3
    END_INPUT
};

static struct INPUT_INFO input_p2b1[] =
{
    INCL_INP( p2b2 ),
    INP0( UNUSED, 0x00, 0x20 ), // P1_B2
    INP0( UNUSED, 0x01, 0x20 ), // P2_B2
    END_INPUT
};

// 2 players, 6 buttons (2 rows of 3 buttons)
static struct INPUT_INFO input_p2b6[] =
{
    // Notice : inputs inclusion is incompatible with combinations
  INP0( P1_RIGHT, 0x00, 0x01 ),
  INP0( P1_LEFT, 0x00, 0x02 ),
  INP0( P1_DOWN, 0x00, 0x04 ),
  INP0( P1_UP, 0x00, 0x08 ),
  INP0( P1_B1, 0x00, 0x10 ),
  INP0( P1_B2, 0x00, 0x20 ),
  INP0( P1_B3, 0x00, 0x40 ),
  INP0( UNUSED, 0x00, 0x80 ),
  INP0( P2_RIGHT, 0x01, 0x01 ),
  INP0( P2_LEFT, 0x01, 0x02 ),
  INP0( P2_DOWN, 0x01, 0x04 ),
  INP0( P2_UP, 0x01, 0x08 ),
  INP0( P2_B1, 0x01, 0x10 ),
  INP0( P2_B2, 0x01, 0x20 ),
  INP0( P2_B3, 0x01, 0x40 ),
  INP0( UNUSED, 0x01, 0x80 ),

  INP0( P1_B4, 0x02, 0x01 ),
  INP0( P1_B5, 0x02, 0x02 ),
  INP0( P1_B6, 0x02, 0x04 ),
  INP0( UNUSED,0x02, 0x08 ),
  INP0( P2_B4, 0x02, 0x10 ),
  INP0( P2_B5, 0x02, 0x20 ),
  INP0( UNUSED, 0x02, 0xc0 ),
  INP0( P2_B6, 0x05, 0x40 ),

  // bit 0 is eeprom at offset 4
  INP0( TEST, 0x04, 0x02 ),
  INP0( SERVICE, 0x04, 0x04 ),
  INP0( UNUSED, 0x04, 0xf8 ), // or unknown ?
  INP0( P1_START, 0x05, 0x01 ),
  INP0( P2_START, 0x05, 0x02 ),
  INP0( COIN1, 0x05, 0x10 ),
  INP0( COIN2, 0x05, 0x20 ),
  INP0( UNUSED, 5, 0xcc ),
#ifndef RAINE_DOS
  INP0( P1_B1B2, 0, 0x30 ),
  INP0( P1_B1B2B3, 0, 0x70 ),
  INP0( P1_B4B5B6, 2, 0x07 ),
  INP0( P2_B1B2, 1, 0x30 ),
  INP0( P2_B1B2B3, 1, 0x70 ),
#endif
  END_INPUT
};

// 2 players, 6 buttons and 1 unused ticket dispenser...
static struct INPUT_INFO input_p2b6t[] =
{
    INCL_INP( p2b6 ),
    INP1( UNUSED, 0x03, 0x20 ),
    END_INPUT
};

static struct INPUT_INFO input_p1b3[] =
{
  INP0( P1_RIGHT, 0x00, 0x01 ),
  INP0( P1_LEFT, 0x00, 0x02 ),
  INP0( P1_DOWN, 0x00, 0x04 ),
  INP0( P1_UP, 0x00, 0x08 ),
  INP0( P1_B1, 0x00, 0x10 ),
  INP0( P1_B2, 0x00, 0x20 ),
  INP0( P1_B3, 0x00, 0x40 ),

  INP0( TEST, 0x04, 0x02 ),
  INP0( SERVICE, 0x04, 0x04 ),
  INP0( P1_START, 0x05, 0x01 ),
  INP0( COIN1, 0x05, 0x10 ),
   END_INPUT
};

static struct INPUT_INFO input_p1b2[] =
{
  INP0( P1_RIGHT, 0x00, 0x01 ),
  INP0( P1_LEFT, 0x00, 0x02 ),
  INP0( P1_DOWN, 0x00, 0x04 ),
  INP0( P1_UP, 0x00, 0x08 ),
  INP0( P1_B1, 0x00, 0x10 ),
  INP0( P1_B2, 0x00, 0x20 ),

  INP0( TEST, 0x04, 0x02 ),
  INP0( SERVICE, 0x04, 0x04 ),
  INP0( P1_START, 0x05, 0x01 ),
  INP0( COIN1, 0x05, 0x10 ),
   END_INPUT
};

static struct INPUT_INFO input_qndream[] =
// super bizarre inputs : 4 buttons instead of joystick !
{
  INP0( P1_B4, 0x00, 0x01 ),
  INP0( P1_B3, 0x00, 0x02 ),
  INP0( P1_B2, 0x00, 0x04 ),
  INP0( P1_B1, 0x00, 0x08 ),

  INP0( P2_B4, 0x01, 0x01 ),
  INP0( P2_B3, 0x01, 0x02 ),
  INP0( P2_B2, 0x01, 0x04 ),
  INP0( P2_B1, 0x01, 0x08 ),

  INP0( TEST, 0x04, 0x02 ),
  INP0( SERVICE, 0x04, 0x04 ),
  INP0( P1_START, 0x05, 0x01 ),
  INP0( P2_START, 0x05, 0x02 ),
  INP0( COIN1, 0x05, 0x10 ),
  INP0( COIN2, 0x05, 0x20 ),
   END_INPUT
};

static struct ROMSW_DATA romswd_msh[] =
{
  { "Japan", 0x0},
  { "USA",0x2},
  { "Hispanic", 0x4},
  { "Asia",0x6},
  { "Euro",0x8},
  { "Brazil",0xa},
  { NULL,                    0    },
};

static struct ROMSW_DATA romswd_1944[] =
{
  { "Japan", 0x0},
  { "USA",0x2},
  { "Euro", 0x4},
  { "Asia",0x6},
  { "Western",0x8},
  { "Brazil",0xa},
  { NULL,                    0    },
};

static struct ROMSW_DATA romswd_vhunt2[] =
{
  { "Japan", 0x0},
  { "USA",0x2},
  { "Hispanic", 0x4},
  { "Oceania",0x6},
  { "Asia",0x8},
  { "Euro",0xa},
  { "Brazil",0xc},
  { NULL,                    0    },
};

static struct ROMSW_DATA romswd_19xx[] =
{
  { "Japan", 0x0},
  { "USA", 1 },
  { "Asia",0x2},
  { "Hispanic", 3 },
  { "Euro", 0x4},
  { "Brazil", 5 },
  { NULL,                    0    },
};

static struct ROMSW_INFO romsw_msh[] =
{
   { 0xc3, 0x08, romswd_msh },
   { 0,        0,    NULL },
};

static struct ROMSW_INFO romsw_1944[] =
{
   { 0xc3, 0x02, romswd_1944 },
   { 0,        0,    NULL },
};

static struct ROMSW_INFO romsw_vhunt2[] =
{
   { 0x10ce, 0x00, romswd_vhunt2 },
   { 0,        0,    NULL },
};

static struct ROMSW_INFO romsw_19xx[] =
{
   { 0xc0, 0x00, romswd_19xx },
   { 0,        0,    NULL },
};

static struct ROMSW_INFO romsw_mpangj[] =
{
   { 0x7a0, 0x02, romswd_vhunt2 },
   { 0,        0,    NULL },
};

static struct ROMSW_DATA romswd_phoenix[] =
{
  { "Japan", 0x0},
  { "USA", 1 },
  { "Euro",0x2},
  { "Brazil", 0x3},
  { "Hispanic", 4 },
  { "Asia", 5 },
  { NULL,                    0    },
};


static struct ROMSW_INFO romsw_phoenix[] =
{
   { 0xfffffe, 0x02, romswd_phoenix },
   { 0,        0,    NULL },
};

GMEI( ssf2, "Super Street Fighter II: The New Challengers (World 930911)", CAPCOM, 1993, GAME_BEAT);
CLNEI( ssf2u, ssf2, "Super Street Fighter II: The New Challengers (USA 930911)", CAPCOM, 1993, GAME_BEAT);
CLNEI( ssf2a, ssf2, "Super Street Fighter II: The New Challengers (Asia 931005)", CAPCOM, 1993, GAME_BEAT);
CLNEI( ssf2ar1, ssf2, "Super Street Fighter II: The New Challengers (Asia 930914)", CAPCOM, 1993, GAME_BEAT);
CLNEI( ssf2j, ssf2, "Super Street Fighter II: The New Challengers (Japan 931005)", CAPCOM, 1993, GAME_BEAT);
CLNEI( ssf2jr1, ssf2, "Super Street Fighter II: The New Challengers (Japan 930911)", CAPCOM, 1993, GAME_BEAT);
CLNEI( ssf2jr2, ssf2, "Super Street Fighter II: The New Challengers (Japan 930910)", CAPCOM, 1993, GAME_BEAT);
CLNEI( ssf2h, ssf2, "Super Street Fighter II: The New Challengers (Hispanic 930911)", CAPCOM, 1993, GAME_BEAT);
CLNEI( ssf2tb, ssf2, "Super Street Fighter II: The Tournament Battle (World 931119)", CAPCOM, 1993, GAME_BEAT);
CLNEI( ssf2tbr1, ssf2, "Super Street Fighter II: The Tournament Battle (World 930911)", CAPCOM, 1993, GAME_BEAT);
CLNEI( ssf2tbj, ssf2, "Super Street Fighter II: The Tournament Battle (Japan 930911)", CAPCOM, 1993, GAME_BEAT);
CLNEI( ssf2tbh, ssf2, "Super Street Fighter II: The Tournament Battle (Hispanic 931005)", CAPCOM, 1993, GAME_BEAT);
GMEI( ecofghtr, "Eco Fighters (World 931203)", CAPCOM, 1993, GAME_SHOOT,
  .input = input_p2b3);
CLNEI( ecofghtru, ecofghtr, "Eco Fighters (USA 940215)", CAPCOM, 1993, GAME_SHOOT,
  .input = input_p2b3);
CLNEI( ecofghtru1, ecofghtr, "Eco Fighters (USA 931203)", CAPCOM, 1993, GAME_SHOOT,
  .input = input_p2b3);
CLNEI( uecology, ecofghtr, "Ultimate Ecology (Japan 931203)", CAPCOM, 1993, GAME_SHOOT,
  .input = input_p2b3);
CLNEI( ecofghtra, ecofghtr, "Eco Fighters (Asia 931203)", CAPCOM, 1993, GAME_SHOOT,
  .input = input_p2b3);
CLNEI( ecofghtrh, ecofghtr, "Eco Fighters (Hispanic 931203)", CAPCOM, 1993, GAME_SHOOT,
  .input = input_p2b3);
GMEI( ddtod, "Dungeons & Dragons: Tower of Doom (Euro 940412)", CAPCOM, 1993, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddtodr1, ddtod, "Dungeons & Dragons: Tower of Doom (Euro 940113)", CAPCOM, 1993, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddtodu, ddtod, "Dungeons & Dragons: Tower of Doom (USA 940125)", CAPCOM, 1993, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddtodur1, ddtod, "Dungeons & Dragons: Tower of Doom (USA 940113)", CAPCOM, 1993, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddtodj, ddtod, "Dungeons & Dragons: Tower of Doom (Japan 940412)", CAPCOM, 1993, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddtodjr1, ddtod, "Dungeons & Dragons: Tower of Doom (Japan 940125)", CAPCOM, 1993, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddtodjr2, ddtod, "Dungeons & Dragons: Tower of Doom (Japan 940113)", CAPCOM, 1993, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddtoda, ddtod, "Dungeons & Dragons: Tower of Doom (Asia 940113)", CAPCOM, 1993, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddtodh, ddtod, "Dungeons & Dragons: Tower of Doom (Hispanic 940412)", CAPCOM, 1993, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddtodhr1, ddtod, "Dungeons & Dragons: Tower of Doom (Hispanic 940125)", CAPCOM, 1993, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddtodhr2, ddtod, "Dungeons & Dragons: Tower of Doom (Hispanic 940113)", CAPCOM, 1993, GAME_BEAT,
  .input = input_p4b4);
GMEI( ssf2t, "Super Street Fighter II Turbo (World 940223)", CAPCOM, 1994, GAME_BEAT);
CLNEI( ssf2ta, ssf2t, "Super Street Fighter II Turbo (Asia 940223)", CAPCOM, 1994, GAME_BEAT);
CLNEI( ssf2tu, ssf2t, "Super Street Fighter II Turbo (USA 940323)", CAPCOM, 1994, GAME_BEAT);
CLNEI( ssf2tur1, ssf2t, "Super Street Fighter II Turbo (USA 940223)", CAPCOM, 1994, GAME_BEAT);
CLNEI( ssf2xj, ssf2t, "Super Street Fighter II X: Grand Master Challenge (Japan 940223)", CAPCOM, 1994, GAME_BEAT);
CLNEI( ssf2xjr, ssf2t, "Super Street Fighter II X: Grand Master Challenge (Japan 940223 rent version)", CAPCOM, 1994, GAME_BEAT);
GMEI( avsp, "Alien vs. Predator (Euro 940520)", CAPCOM, 1994, GAME_BEAT,
  .input = input_p3b3);
CLNEI( avspu, avsp, "Alien vs. Predator (USA 940520)", CAPCOM, 1994, GAME_BEAT,
  .input = input_p3b3);
CLNEI( avspj, avsp, "Alien vs. Predator (Japan 940520)", CAPCOM, 1994, GAME_BEAT,
  .input = input_p3b3);
CLNEI( avspa, avsp, "Alien vs. Predator (Asia 940520)", CAPCOM, 1994, GAME_BEAT,
  .input = input_p3b3);
CLNEI( avsph, avsp, "Alien vs. Predator (Hispanic 940520)", CAPCOM, 1994, GAME_BEAT,
  .input = input_p3b3);
GMEI( dstlk, "Darkstalkers: The Night Warriors (Euro 940705)", CAPCOM, 1994, GAME_BEAT);
CLNEI( dstlku, dstlk, "Darkstalkers: The Night Warriors (USA 940818)", CAPCOM, 1994, GAME_BEAT);
CLNEI( dstlkur1, dstlk, "Darkstalkers: The Night Warriors (USA 940705)", CAPCOM, 1994, GAME_BEAT);
CLNEI( dstlka, dstlk, "Darkstalkers: The Night Warriors (Asia 940705)", CAPCOM, 1994, GAME_BEAT);
CLNEI( dstlkh, dstlk, "Darkstalkers: The Night Warriors (Hispanic 940818)", CAPCOM, 1994, GAME_BEAT);
CLNEI( vampj, dstlk, "Vampire: The Night Warriors (Japan 940705)", CAPCOM, 1994, GAME_BEAT);
CLNEI( vampja, dstlk, "Vampire: The Night Warriors (Japan 940705 alt)", CAPCOM, 1994, GAME_BEAT);
CLNEI( vampjr1, dstlk, "Vampire: The Night Warriors (Japan 940630)", CAPCOM, 1994, GAME_BEAT);
GMEI( ringdest, "Ring of Destruction: Slammasters II (Euro 940902)", CAPCOM, 1994, GAME_SPORTS);
CLNEI( ringdesta, ringdest, "Ring of Destruction: Slammasters II (Asia 940831)", CAPCOM, 1994, GAME_SPORTS);
CLNEI( smbomb, ringdest, "Super Muscle Bomber: The International Blowout (Japan 940831)", CAPCOM, 1994, GAME_SPORTS);
CLNEI( smbombr1, ringdest, "Super Muscle Bomber: The International Blowout (Japan 940808)", CAPCOM, 1994, GAME_SPORTS);
GMEI( armwar, "Armored Warriors (Euro 941024)", CAPCOM, 1994, GAME_BEAT,
  .input = input_p3b3);
CLNEI( armwarr1, armwar, "Armored Warriors (Euro 941011)", CAPCOM, 1994, GAME_BEAT,
  .input = input_p3b3);
CLNEI( armwaru, armwar, "Armored Warriors (USA 941024)", CAPCOM, 1994, GAME_BEAT,
  .input = input_p3b3);
CLNEI( armwaru1, armwar, "Armored Warriors (USA 940920)", CAPCOM, 1994, GAME_BEAT,
  .input = input_p3b3);
CLNEI( pgear, armwar, "Powered Gear: Strategic Variant Armor Equipment (Japan 941024)", CAPCOM, 1994, GAME_BEAT,
  .input = input_p3b3);
CLNEI( pgearr1, armwar, "Powered Gear: Strategic Variant Armor Equipment (Japan 940916)", CAPCOM, 1994, GAME_BEAT,
  .input = input_p3b3);
CLNEI( armwara, armwar, "Armored Warriors (Asia 940920)", CAPCOM, 1994, GAME_BEAT,
  .input = input_p3b3);
GMEI( xmcota, "X-Men: Children of the Atom (Euro 950331)", CAPCOM, 1994, GAME_BEAT);
CLNEI( xmcotar1, xmcota, "X-Men: Children of the Atom (Euro 950105)", CAPCOM, 1994, GAME_BEAT);
CLNEI( xmcotau, xmcota, "X-Men: Children of the Atom (USA 950105)", CAPCOM, 1994, GAME_BEAT);
CLNEI( xmcotah, xmcota, "X-Men: Children of the Atom (Hispanic 950331)", CAPCOM, 1994, GAME_BEAT);
CLNEI( xmcotahr1, xmcota, "X-Men: Children of the Atom (Hispanic 950105)", CAPCOM, 1994, GAME_BEAT);
CLNEI( xmcotaj, xmcota, "X-Men: Children of the Atom (Japan 950105)", CAPCOM, 1994, GAME_BEAT);
CLNEI( xmcotaj1, xmcota, "X-Men: Children of the Atom (Japan 941222)", CAPCOM, 1994, GAME_BEAT);
CLNEI( xmcotaj2, xmcota, "X-Men: Children of the Atom (Japan 941219)", CAPCOM, 1994, GAME_BEAT);
CLNEI( xmcotaj3, xmcota, "X-Men: Children of the Atom (Japan 941217)", CAPCOM, 1994, GAME_BEAT);
CLNEI( xmcotajr, xmcota, "X-Men: Children of the Atom (Japan 941208 rent version)", CAPCOM, 1994, GAME_BEAT);
CLNEI( xmcotaa, xmcota, "X-Men: Children of the Atom (Asia 950105)", CAPCOM, 1994, GAME_BEAT);
CLNEI( xmcotaar1, xmcota, "X-Men: Children of the Atom (Asia 941217)", CAPCOM, 1994, GAME_BEAT);
GMEI( nwarr, "Night Warriors: Darkstalkers' Revenge (Euro 950316)", CAPCOM, 1995, GAME_BEAT);
CLNEI( nwarru, nwarr, "Night Warriors: Darkstalkers' Revenge (USA 950406)", CAPCOM, 1995, GAME_BEAT);
CLNEI( nwarrh, nwarr, "Night Warriors: Darkstalkers' Revenge (Hispanic 950403)", CAPCOM, 1995, GAME_BEAT);
CLNEI( nwarrb, nwarr, "Night Warriors: Darkstalkers' Revenge (Brazil 950403)", CAPCOM, 1995, GAME_BEAT);
CLNEI( nwarra, nwarr, "Night Warriors: Darkstalkers' Revenge (Asia 950302)", CAPCOM, 1995, GAME_BEAT);
CLNEI( vhuntj, nwarr, "Vampire Hunter: Darkstalkers' Revenge (Japan 950316)", CAPCOM, 1995, GAME_BEAT);
CLNEI( vhuntjr1s, nwarr, "Vampire Hunter: Darkstalkers' Revenge (Japan 950307 stop version)", CAPCOM, 1995, GAME_BEAT);
CLNEI( vhuntjr1, nwarr, "Vampire Hunter: Darkstalkers' Revenge (Japan 950307)", CAPCOM, 1995, GAME_BEAT);
CLNEI( vhuntjr2, nwarr, "Vampire Hunter: Darkstalkers' Revenge (Japan 950302)", CAPCOM, 1995, GAME_BEAT);
GMEI( cybots, "Cyberbots: Fullmetal Madness (Euro 950424)", CAPCOM, 1995, GAME_BEAT,
  .input = input_p2b4);
CLNEI( cybotsu, cybots, "Cyberbots: Fullmetal Madness (USA 950424)", CAPCOM, 1995, GAME_BEAT,
  .input = input_p2b4);
CLNEI( cybotsj, cybots, "Cyberbots: Fullmetal Madness (Japan 950420)", CAPCOM, 1995, GAME_BEAT,
  .input = input_p2b4);
GMEI( sfa, "Street Fighter Alpha: Warriors' Dreams (Euro 950727)", CAPCOM, 1995, GAME_BEAT);
CLNEI( sfar1, sfa, "Street Fighter Alpha: Warriors' Dreams (Euro 950718)", CAPCOM, 1995, GAME_BEAT);
CLNEI( sfar2, sfa, "Street Fighter Alpha: Warriors' Dreams (Euro 950627)", CAPCOM, 1995, GAME_BEAT);
CLNEI( sfar3, sfa, "Street Fighter Alpha: Warriors' Dreams (Euro 950605)", CAPCOM, 1995, GAME_BEAT);
CLNEI( sfau, sfa, "Street Fighter Alpha: Warriors' Dreams (USA 950627)", CAPCOM, 1995, GAME_BEAT);
CLNEI( sfza, sfa, "Street Fighter Zero (Asia 950627)", CAPCOM, 1995, GAME_BEAT);
CLNEI( sfzj, sfa, "Street Fighter Zero (Japan 950727)", CAPCOM, 1995, GAME_BEAT);
CLNEI( sfzjr1, sfa, "Street Fighter Zero (Japan 950627)", CAPCOM, 1995, GAME_BEAT);
CLNEI( sfzjr2, sfa, "Street Fighter Zero (Japan 950605)", CAPCOM, 1995, GAME_BEAT);
CLNEI( sfzh, sfa, "Street Fighter Zero (Hispanic 950718)", CAPCOM, 1995, GAME_BEAT);
CLNEI( sfzhr1, sfa, "Street Fighter Zero (Hispanic 950627)", CAPCOM, 1995, GAME_BEAT);
CLNEI( sfzb, sfa, "Street Fighter Zero (Brazil 951109)", CAPCOM, 1995, GAME_BEAT);
CLNEI( sfzbr1, sfa, "Street Fighter Zero (Brazil 950727)", CAPCOM, 1995, GAME_BEAT);
CLNEI( mmancp2u, megaman, "Mega Man: The Power Battle (CPS2, USA 951006, SAMPLE Version)", CAPCOM, 1995, GAME_BEAT,
  .input = input_p2b3);
CLNEI( rmancp2j, megaman, "Rockman: The Power Battle (CPS2, Japan 950922)", CAPCOM, 1995, GAME_BEAT,
  .input = input_p2b3);
GMEI( msh, "Marvel Super Heroes (Euro 951024)", CAPCOM, 1995, GAME_BEAT,
	.romsw = romsw_msh);
CLNEI( mshu, msh, "Marvel Super Heroes (USA 951024)", CAPCOM, 1995, GAME_BEAT);
CLNEI( mshj, msh, "Marvel Super Heroes (Japan 951117)", CAPCOM, 1995, GAME_BEAT);
CLNEI( mshjr1, msh, "Marvel Super Heroes (Japan 951024)", CAPCOM, 1995, GAME_BEAT);
CLNEI( msha, msh, "Marvel Super Heroes (Asia 951024)", CAPCOM, 1995, GAME_BEAT);
CLNEI( mshh, msh, "Marvel Super Heroes (Hispanic 951117)", CAPCOM, 1995, GAME_BEAT);
CLNEI( mshb, msh, "Marvel Super Heroes (Brazil 951117)", CAPCOM, 1995, GAME_BEAT);
GMEI( 19xx, "19XX: The War Against Destiny (USA 951207)", CAPCOM, 1996, GAME_SHOOT,
  .video = &video_cps1_270,
  .input = input_p2b2, .romsw = romsw_19xx);
CLNEI( 19xxa, 19xx, "19XX: The War Against Destiny (Asia 951207)", CAPCOM, 1996, GAME_SHOOT,
  .video = &video_cps1_270,
  .input = input_p2b2);
CLNEI( 19xxj, 19xx, "19XX: The War Against Destiny (Japan 951225)", CAPCOM, 1996, GAME_SHOOT,
  .video = &video_cps1_270,
  .input = input_p2b2);
CLNEI( 19xxjr1, 19xx, "19XX: The War Against Destiny (Japan 951207)", CAPCOM, 1996, GAME_SHOOT,
  .video = &video_cps1_270,
  .input = input_p2b2);
CLNEI( 19xxh, 19xx, "19XX: The War Against Destiny (Hispanic 951218)", CAPCOM, 1996, GAME_SHOOT,
  .video = &video_cps1_270,
  .input = input_p2b2);
CLNEI( 19xxb, 19xx, "19XX: The War Against Destiny (Brazil 951218)", CAPCOM, 1996, GAME_SHOOT,
  .video = &video_cps1_270,
  .input = input_p2b2);
GMEI( ddsom, "Dungeons & Dragons: Shadow over Mystara (Euro 960619)", CAPCOM, 1996, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddsomr1, ddsom, "Dungeons & Dragons: Shadow over Mystara (Euro 960223)", CAPCOM, 1996, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddsomr2, ddsom, "Dungeons & Dragons: Shadow over Mystara (Euro 960209)", CAPCOM, 1996, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddsomr3, ddsom, "Dungeons & Dragons: Shadow over Mystara (Euro 960208)", CAPCOM, 1996, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddsomu, ddsom, "Dungeons & Dragons: Shadow over Mystara (USA 960619)", CAPCOM, 1996, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddsomur1, ddsom, "Dungeons & Dragons: Shadow over Mystara (USA 960209)", CAPCOM, 1996, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddsomj, ddsom, "Dungeons & Dragons: Shadow over Mystara (Japan 960619)", CAPCOM, 1996, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddsomjr1, ddsom, "Dungeons & Dragons: Shadow over Mystara (Japan 960206)", CAPCOM, 1996, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddsoma, ddsom, "Dungeons & Dragons: Shadow over Mystara (Asia 960619)", CAPCOM, 1996, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddsomh, ddsom, "Dungeons & Dragons: Shadow over Mystara (Hispanic 960223)", CAPCOM, 1996, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ddsomb, ddsom, "Dungeons & Dragons: Shadow over Mystara (Brazil 960223)", CAPCOM, 1996, GAME_BEAT,
  .input = input_p4b4);
GMEI( sfa2, "Street Fighter Alpha 2 (Euro 960229)", CAPCOM, 1996, GAME_BEAT);
CLNEI( sfa2u, sfa2, "Street Fighter Alpha 2 (USA 960430)", CAPCOM, 1996, GAME_BEAT);
CLNEI( sfa2ur1, sfa2, "Street Fighter Alpha 2 (USA 960306)", CAPCOM, 1996, GAME_BEAT);
CLNEI( sfz2j, sfa2, "Street Fighter Zero 2 (Japan 960430)", CAPCOM, 1996, GAME_BEAT);
CLNEI( sfz2jr1, sfa2, "Street Fighter Zero 2 (Japan 960227)", CAPCOM, 1996, GAME_BEAT);
CLNEI( sfz2a, sfa2, "Street Fighter Zero 2 (Asia 960227)", CAPCOM, 1996, GAME_BEAT);
CLNEI( sfz2b, sfa2, "Street Fighter Zero 2 (Brazil 960531)", CAPCOM, 1996, GAME_BEAT);
CLNEI( sfz2br1, sfa2, "Street Fighter Zero 2 (Brazil 960304)", CAPCOM, 1996, GAME_BEAT);
CLNEI( sfz2h, sfa2, "Street Fighter Zero 2 (Hispanic 960304)", CAPCOM, 1996, GAME_BEAT);
CLNEI( sfz2n, sfa2, "Street Fighter Zero 2 (Oceania 960229)", CAPCOM, 1996, GAME_BEAT);
GMEI( sfz2al, "Street Fighter Zero 2 Alpha (Asia 960826)", CAPCOM, 1996, GAME_BEAT);
CLNEI( sfz2alj, sfz2al, "Street Fighter Zero 2 Alpha (Japan 960805)", CAPCOM, 1996, GAME_BEAT);
CLNEI( sfz2alh, sfz2al, "Street Fighter Zero 2 Alpha (Hispanic 960813)", CAPCOM, 1996, GAME_BEAT);
CLNEI( sfz2alb, sfz2al, "Street Fighter Zero 2 Alpha (Brazil 960813)", CAPCOM, 1996, GAME_BEAT);
GMEI( spf2t, "Super Puzzle Fighter II Turbo (USA 960620)", CAPCOM, 1996, GAME_PUZZLE,
  .input = input_p2b2);
CLNEI( spf2xj, spf2t, "Super Puzzle Fighter II X (Japan 960531)", CAPCOM, 1996, GAME_PUZZLE,
  .input = input_p2b2);
CLNEI( spf2ta, spf2t, "Super Puzzle Fighter II Turbo (Asia 960529)", CAPCOM, 1996, GAME_PUZZLE,
  .input = input_p2b2);
CLNEI( spf2th, spf2t, "Super Puzzle Fighter II Turbo (Hispanic 960531)", CAPCOM, 1996, GAME_PUZZLE,
  .input = input_p2b2);
GMEI( megaman2, "Mega Man 2: The Power Fighters (USA 960708)", CAPCOM, 1996, GAME_BEAT,
  .input = input_p2b3);
CLNEI( megaman2a, megaman2, "Mega Man 2: The Power Fighters (Asia 960708)", CAPCOM, 1996, GAME_BEAT,
  .input = input_p2b3);
CLNEI( rockman2j, megaman2, "Rockman 2: The Power Fighters (Japan 960708)", CAPCOM, 1996, GAME_BEAT,
  .input = input_p2b3);
CLNEI( megaman2h, megaman2, "Mega Man 2: The Power Fighters (Hispanic 960712)", CAPCOM, 1996, GAME_BEAT,
  .input = input_p2b3);
GMEI( qndream, "Quiz Nanairo Dreams: Nijiirochou no Kiseki (Japan 960826)", CAPCOM, 1996, GAME_QUIZZ,
  .input = input_qndream);
GMEI( xmvsf, "X-Men Vs. Street Fighter (Euro 961004)", CAPCOM, 1996, GAME_BEAT);
CLNEI( xmvsfr1, xmvsf, "X-Men Vs. Street Fighter (Euro 960910)", CAPCOM, 1996, GAME_BEAT);
CLNEI( xmvsfu, xmvsf, "X-Men Vs. Street Fighter (USA 961023)", CAPCOM, 1996, GAME_BEAT);
CLNEI( xmvsfur1, xmvsf, "X-Men Vs. Street Fighter (USA 961004)", CAPCOM, 1996, GAME_BEAT);
CLNEI( xmvsfj, xmvsf, "X-Men Vs. Street Fighter (Japan 961004)", CAPCOM, 1996, GAME_BEAT);
CLNEI( xmvsfjr1, xmvsf, "X-Men Vs. Street Fighter (Japan 960910)", CAPCOM, 1996, GAME_BEAT);
CLNEI( xmvsfjr2, xmvsf, "X-Men Vs. Street Fighter (Japan 960909)", CAPCOM, 1996, GAME_BEAT);
CLNEI( xmvsfa, xmvsf, "X-Men Vs. Street Fighter (Asia 961023)", CAPCOM, 1996, GAME_BEAT);
CLNEI( xmvsfar1, xmvsf, "X-Men Vs. Street Fighter (Asia 960919)", CAPCOM, 1996, GAME_BEAT);
CLNEI( xmvsfar2, xmvsf, "X-Men Vs. Street Fighter (Asia 960910)", CAPCOM, 1996, GAME_BEAT);
CLNEI( xmvsfh, xmvsf, "X-Men Vs. Street Fighter (Hispanic 961004)", CAPCOM, 1996, GAME_BEAT);
CLNEI( xmvsfb, xmvsf, "X-Men Vs. Street Fighter (Brazil 961023)", CAPCOM, 1996, GAME_BEAT);
GMEI( batcir, "Battle Circuit (Euro 970319)", CAPCOM, 1997, GAME_BEAT,
  .input = input_p4b2);
CLNEI( batcira, batcir, "Battle Circuit (Asia 970319)", CAPCOM, 1997, GAME_BEAT,
  .input = input_p4b2);
CLNEI( batcirj, batcir, "Battle Circuit (Japan 970319)", CAPCOM, 1997, GAME_BEAT,
  .input = input_p4b2);
GMEI( vsav, "Vampire Savior: The Lord of Vampire (Euro 970519)", CAPCOM, 1997, GAME_BEAT);
CLNEI( vsavu, vsav, "Vampire Savior: The Lord of Vampire (USA 970519)", CAPCOM, 1997, GAME_BEAT);
CLNEI( vsavj, vsav, "Vampire Savior: The Lord of Vampire (Japan 970519)", CAPCOM, 1997, GAME_BEAT);
CLNEI( vsava, vsav, "Vampire Savior: The Lord of Vampire (Asia 970519)", CAPCOM, 1997, GAME_BEAT);
CLNEI( vsavh, vsav, "Vampire Savior: The Lord of Vampire (Hispanic 970519)", CAPCOM, 1997, GAME_BEAT);
GMEI( mshvsf, "Marvel Super Heroes Vs. Street Fighter (Euro 970625)", CAPCOM, 1997, GAME_BEAT);
CLNEI( mshvsfu, mshvsf, "Marvel Super Heroes Vs. Street Fighter (USA 970827)", CAPCOM, 1997, GAME_BEAT);
CLNEI( mshvsfu1, mshvsf, "Marvel Super Heroes Vs. Street Fighter (USA 970625)", CAPCOM, 1997, GAME_BEAT);
CLNEI( mshvsfj, mshvsf, "Marvel Super Heroes Vs. Street Fighter (Japan 970707)", CAPCOM, 1997, GAME_BEAT);
CLNEI( mshvsfj1, mshvsf, "Marvel Super Heroes Vs. Street Fighter (Japan 970702)", CAPCOM, 1997, GAME_BEAT);
CLNEI( mshvsfj2, mshvsf, "Marvel Super Heroes Vs. Street Fighter (Japan 970625)", CAPCOM, 1997, GAME_BEAT);
CLNEI( mshvsfh, mshvsf, "Marvel Super Heroes Vs. Street Fighter (Hispanic 970625)", CAPCOM, 1997, GAME_BEAT);
CLNEI( mshvsfa, mshvsf, "Marvel Super Heroes Vs. Street Fighter (Asia 970625)", CAPCOM, 1997, GAME_BEAT);
CLNEI( mshvsfa1, mshvsf, "Marvel Super Heroes Vs. Street Fighter (Asia 970620)", CAPCOM, 1997, GAME_BEAT);
CLNEI( mshvsfb, mshvsf, "Marvel Super Heroes Vs. Street Fighter (Brazil 970827)", CAPCOM, 1997, GAME_BEAT);
CLNEI( mshvsfb1, mshvsf, "Marvel Super Heroes Vs. Street Fighter (Brazil 970625)", CAPCOM, 1997, GAME_BEAT);
GMEI( csclub, "Capcom Sports Club (Euro 971017)", CAPCOM, 1997, GAME_SPORTS,
  .input = input_p2b3);
CLNEI( csclub1, csclub, "Capcom Sports Club (Euro 970722)", CAPCOM, 1997, GAME_SPORTS,
  .input = input_p2b3);
CLNEI( cscluba, csclub, "Capcom Sports Club (Asia 970722)", CAPCOM, 1997, GAME_SPORTS,
  .input = input_p2b3);
CLNEI( csclubj, csclub, "Capcom Sports Club (Japan 970722)", CAPCOM, 1997, GAME_SPORTS,
  .input = input_p2b3);
CLNEI( csclubh, csclub, "Capcom Sports Club (Hispanic 970722)", CAPCOM, 1997, GAME_SPORTS,
  .input = input_p2b3);
GMEI( sgemf, "Super Gem Fighter Mini Mix (USA 970904)", CAPCOM, 1997, GAME_BEAT,
  .input = input_p2b3);
CLNEI( pfghtj, sgemf, "Pocket Fighter (Japan 970904)", CAPCOM, 1997, GAME_BEAT,
  .input = input_p2b3);
CLNEI( sgemfa, sgemf, "Super Gem Fighter: Mini Mix (Asia 970904)", CAPCOM, 1997, GAME_BEAT,
  .input = input_p2b3);
CLNEI( sgemfh, sgemf, "Super Gem Fighter: Mini Mix (Hispanic 970904)", CAPCOM, 1997, GAME_BEAT,
  .input = input_p2b3);
GMEI( vhunt2, "Vampire Hunter 2: Darkstalkers Revenge (Japan 970929)", CAPCOM, 1997, GAME_BEAT, .romsw = romsw_vhunt2);
CLNEI( vhunt2r1, vhunt2, "Vampire Hunter 2: Darkstalkers Revenge (Japan 970913)", CAPCOM, 1997, GAME_BEAT);
GMEI( vsav2, "Vampire Savior 2: The Lord of Vampire (Japan 970913)", CAPCOM, 1997, GAME_BEAT);
GMEI( mvsc, "Marvel Vs. Capcom: Clash of Super Heroes (Euro 980123)", CAPCOM, 1998, GAME_BEAT);
CLNEI( mvscr1, mvsc, "Marvel Vs. Capcom: Clash of Super Heroes (Euro 980112)", CAPCOM, 1998, GAME_BEAT);
CLNEI( mvscu, mvsc, "Marvel Vs. Capcom: Clash of Super Heroes (USA 980123)", CAPCOM, 1998, GAME_BEAT);
CLNEI( mvscur1, mvsc, "Marvel Vs. Capcom: Clash of Super Heroes (USA 971222)", CAPCOM, 1998, GAME_BEAT);
CLNEI( mvscj, mvsc, "Marvel Vs. Capcom: Clash of Super Heroes (Japan 980123)", CAPCOM, 1998, GAME_BEAT);
CLNEI( mvscjr1, mvsc, "Marvel Vs. Capcom: Clash of Super Heroes (Japan 980112)", CAPCOM, 1998, GAME_BEAT);
CLNEI( mvscjsing, mvsc, "Marvel Vs. Capcom: Clash of Super Heroes (Japan 980123) (Single PCB)", CAPCOM, 1998, GAME_BEAT);
CLNEI( mvsca, mvsc, "Marvel Vs. Capcom: Clash of Super Heroes (Asia 980123)", CAPCOM, 1998, GAME_BEAT);
CLNEI( mvscar1, mvsc, "Marvel Vs. Capcom: Clash of Super Heroes (Asia 980112)", CAPCOM, 1998, GAME_BEAT);
CLNEI( mvsch, mvsc, "Marvel Vs. Capcom: Clash of Super Heroes (Hispanic 980123)", CAPCOM, 1998, GAME_BEAT);
CLNEI( mvscb, mvsc, "Marvel Vs. Capcom: Clash of Super Heroes (Brazil 980123)", CAPCOM, 1998, GAME_BEAT);
GMEI( sfa3, "Street Fighter Alpha 3 (Euro 980904)", CAPCOM, 1998, GAME_BEAT);
CLNEI( sfa3u, sfa3, "Street Fighter Alpha 3 (USA 980904)", CAPCOM, 1998, GAME_BEAT);
CLNEI( sfa3ur1, sfa3, "Street Fighter Alpha 3 (USA 980629)", CAPCOM, 1998, GAME_BEAT);
CLNEI( sfa3h, sfa3, "Street Fighter Alpha 3 (Hispanic 980904)", CAPCOM, 1998, GAME_BEAT,
  .input = input_p2b6t);
CLNEI( sfa3hr1, sfa3, "Street Fighter Alpha 3 (Hispanic 980629)", CAPCOM, 1998, GAME_BEAT,
  .input = input_p2b6t);
CLNEI( sfa3b, sfa3, "Street Fighter Alpha 3 (Brazil 980629)", CAPCOM, 1998, GAME_BEAT,
  .input = input_p2b6t);
CLNEI( sfz3j, sfa3, "Street Fighter Zero 3 (Japan 980904)", CAPCOM, 1998, GAME_BEAT);
CLNEI( sfz3jr1, sfa3, "Street Fighter Zero 3 (Japan 980727)", CAPCOM, 1998, GAME_BEAT);
CLNEI( sfz3jr2, sfa3, "Street Fighter Zero 3 (Japan 980629)", CAPCOM, 1998, GAME_BEAT);
CLNEI( sfz3a, sfa3, "Street Fighter Zero 3 (Asia 980904)", CAPCOM, 1998, GAME_BEAT);
CLNEI( sfz3ar1, sfa3, "Street Fighter Zero 3 (Asia 980701)", CAPCOM, 1998, GAME_BEAT);
GMEI( jyangoku, "Jyangokushi: Haoh no Saihai (Japan 990527)", CAPCOM, 1999, GAME_PUZZLE,
  .input = input_p1b2);
GMEI( hsf2, "Hyper Street Fighter 2: The Anniversary Edition (USA 040202)", CAPCOM, 2004, GAME_BEAT);
CLNEI( hsf2a, hsf2, "Hyper Street Fighter 2: The Anniversary Edition (Asia 040202)", CAPCOM, 2004, GAME_BEAT);
CLNEI( hsf2j, hsf2, "Hyper Street Fighter 2: The Anniversary Edition (Japan 031222)", CAPCOM, 2004, GAME_BEAT);
GMEI( gigawing, "Giga Wing (USA 990222)", TAKUMI, 1999, GAME_SHOOT,
  .input = input_p2b2);
CLNEI( gigawingj, gigawing, "Giga Wing (Japan 990223)", TAKUMI, 1999, GAME_SHOOT,
  .input = input_p2b2);
CLNEI( gigawinga, gigawing, "Giga Wing (Asia 990222)", TAKUMI, 1999, GAME_SHOOT,
  .input = input_p2b2);
CLNEI( gigawingh, gigawing, "Giga Wing (Hispanic 990222)", TAKUMI, 1999, GAME_SHOOT,
  .input = input_p2b2);
CLNEI( gigawingb, gigawing, "Giga Wing (Brazil 990222)", TAKUMI, 1999, GAME_SHOOT,
  .input = input_p2b2);
GMEI( mmatrix, "Mars Matrix: Hyper Solid Shooting (USA 000412)", TAKUMI, 2000, GAME_SHOOT,
  .input = input_p2b1);
CLNEI( mmatrixj, mmatrix, "Mars Matrix: Hyper Solid Shooting (Japan 000412)", TAKUMI, 2000, GAME_SHOOT,
  .input = input_p2b1);
GMEI( mpang, "Mighty! Pang (Euro 001010)", MITCHELL, 2000, GAME_SHOOT,
  .input = input_p2b1);
CLNEI( mpangr1, mpang, "Mighty! Pang (Euro 000925)", MITCHELL, 2000, GAME_SHOOT,
  .input = input_p2b1);
CLNEI( mpangu, mpang, "Mighty! Pang (USA 001010)", MITCHELL, 2000, GAME_SHOOT,
  .input = input_p2b1);
CLNEI( mpangj, mpang, "Mighty! Pang (Japan 001011)", MITCHELL, 2000, GAME_SHOOT,
  .input = input_p2b1, .romsw = romsw_mpangj);
GMEI( pzloop2, "Puzz Loop 2 (Euro 010302)", MITCHELL, 2001, GAME_PUZZLE,
  .input = input_p2b1);
CLNEI( pzloop2j, pzloop2, "Puzz Loop 2 (Japan 010226)", MITCHELL, 2001, GAME_PUZZLE,
  .input = input_p2b1);
CLNEI( pzloop2jr1, pzloop2, "Puzz Loop 2 (Japan 010205)", MITCHELL, 2001, GAME_PUZZLE,
  .input = input_p2b1);
GMEI( choko, "Janpai Puzzle Choukou (Japan 010820)", MITCHELL, 2001, GAME_PUZZLE,
  .input = input_p1b3);
GMEI( dimahoo, "Dimahoo (Euro 000121)", RAIZING, 2000, GAME_SHOOT,
  .input = input_p2b3,
  .video = &video_cps1_270);
CLNEI( dimahoou, dimahoo, "Dimahoo (USA 000121)", RAIZING, 2000, GAME_SHOOT,
  .input = input_p2b3,
  .video = &video_cps1_270);
CLNEI( gmahou, dimahoo, "Great Mahou Daisakusen (Japan 000121)", RAIZING, 2000, GAME_SHOOT,
  .video = &video_cps1_270,
  .input = input_p2b3);
GMEI( 1944, "1944: The Loop Master (USA 000620)", RAIZING, 2000, GAME_SHOOT,
  .input = input_p2b2,
  .romsw = romsw_1944);
CLNEI( 1944j, 1944, "1944: The Loop Master (Japan 000620)", RAIZING, 2000, GAME_SHOOT,
  .input = input_p2b2);
GMEI( progear, "Progear (USA 010117)", CAVE, 2001, GAME_SHOOT,
  .input = input_p2b3);
CLNEI( progearj, progear, "Progear no Arashi (Japan 010117)", CAVE, 2001, GAME_SHOOT,
  .input = input_p2b3);
CLNEI( progeara, progear, "Progear (Asia 010117)", CAVE, 2001, GAME_SHOOT,
  .input = input_p2b3);
CLNEI( ssf2ud, ssf2, "Super Street Fighter II: The New Challengers (USA 930911 Phoenix Edition) (bootleg)", BOOTLEG, 1993, GAME_BEAT);
CLNEI( ddtodd, ddtod, "Dungeons & Dragons: Tower of Doom (Euro 940412 Phoenix Edition) (bootleg)", BOOTLEG, 1993, GAME_BEAT,
  .input = input_p4b4);
CLNEI( ecofghtrd, ecofghtr, "Eco Fighters (World 931203 Phoenix Edition) (bootleg)", BOOTLEG, 1993, GAME_SHOOT,
  .input = input_p2b3);
CLNEI( armwar1d, armwar, "Armored Warriors (Euro 941011 Phoenix Edition) (bootleg)", BOOTLEG, 1994, GAME_BEAT,
  .input = input_p3b3);
CLNEI( avspd, avsp, "Alien vs. Predator (Euro 940520 Phoenix Edition) (bootleg)", BOOTLEG, 1994, GAME_BEAT,
  .input = input_p3b3);
CLNEI( dstlku1d, dstlk, "Darkstalkers: The Night Warriors (USA 940705 Phoenix Edition) (bootleg)", BOOTLEG, 1994, GAME_BEAT);
CLNEI( ringdstd, ringdest, "Ring of Destruction: Slammasters II (Euro 940902 Phoenix Edition) (bootleg)", BOOTLEG, 1994, GAME_SPORTS);
CLNEI( xmcotar1d, xmcota, "X-Men: Children of the Atom (Euro 950105 Phoenix Edition) (bootleg)", BOOTLEG, 1994, GAME_BEAT);
CLNEI( nwarrud, nwarr, "Night Warriors: Darkstalkers' Revenge (USA 950406 Phoenix Edition) (bootleg)", BOOTLEG, 1995, GAME_BEAT);
CLNEI( sfad, sfa, "Street Fighter Alpha: Warriors' Dreams (Euro 950727 Phoenix Edition) (bootleg)", BOOTLEG, 1995, GAME_BEAT);
CLNEI( mshud, msh, "Marvel Super Heroes (US 951024 Phoenix Edition) (bootleg)", BOOTLEG, 1995, GAME_BEAT);
CLNEI( 19xxd, 19xx, "19XX: The War Against Destiny (USA 951207 Phoenix Edition) (bootleg)", BOOTLEG, 1996, GAME_SHOOT,
  .video = &video_cps1_270,
  .input = input_p2b2);
CLNEI( sfz2ad, sfa2, "Street Fighter Zero 2 (Asia 960227 Phoenix Edition) (bootleg)", BOOTLEG, 1996, GAME_BEAT);
CLNEI( sfz2jd, sfa2, "Street Fighter Zero 2 (Japan 960227 Phoenix Edition) (bootleg)", BOOTLEG, 1996, GAME_BEAT);
CLNEI( spf2td, spf2t, "Super Puzzle Fighter II Turbo (USA 960620 Phoenix Edition) (bootleg)", BOOTLEG, 1996, GAME_PUZZLE,
  .input = input_p2b2);
CLNEI( spf2xjd, spf2t, "Super Puzzle Fighter II X (Japan 960531 Phoenix Edition) (bootleg)", BOOTLEG, 1996, GAME_PUZZLE,
  .input = input_p2b2);
CLNEI( ddsomud, ddsom, "Dungeons & Dragons: Shadow over Mystara (USA 960619 Phoenix Edition) (bootleg)", BOOTLEG, 1996, GAME_BEAT,
  .input = input_p4b4);
CLNEI( gigaman2, megaman2, "Giga Man 2: The Power Fighters (bootleg of Mega Man 2: The Power Fighters)", BOOTLEG, 1996, GAME_BEAT|GAME_NOT_WORKING,
  .input = input_p2b3);
CLNEI( megamn2d, megaman2, "Mega Man 2: The Power Fighters (USA 960708 Phoenix Edition) (bootleg)", BOOTLEG, 1996, GAME_BEAT,
  .input = input_p2b3);
CLNEI( sfz2ald, sfz2al, "Street Fighter Zero 2 Alpha (Asia 960826 Phoenix Edition) (bootleg)", BOOTLEG, 1996, GAME_BEAT);
CLNEI( xmvsfu1d, xmvsf, "X-Men Vs. Street Fighter (USA 961004 Phoenix Edition) (bootleg)", BOOTLEG, 1996, GAME_BEAT);
CLNEI( batcird, batcir, "Battle Circuit (Euro 970319 Phoenix Edition) (bootleg)", BOOTLEG, 1997, GAME_BEAT,
  .input = input_p4b2);
CLNEI( vsavd, vsav, "Vampire Savior: The Lord of Vampire (Euro 970519 Phoenix Edition) (bootleg)", BOOTLEG, 1997, GAME_BEAT);
CLNEI( mvscud, mvsc, "Marvel Vs. Capcom: Clash of Super Heroes (USA 980123 Phoenix Edition) (bootleg)", BOOTLEG, 1998, GAME_BEAT);
CLNEI( sfa3ud, sfa3, "Street Fighter Alpha 3 (USA 980904 Phoenix Edition) (bootleg)", BOOTLEG, 1998, GAME_BEAT);
CLNEI( gigawingd, gigawing, "Giga Wing (USA 990222 Phoenix Edition) (bootleg)", BOOTLEG, 1999, GAME_SHOOT,
  .input = input_p2b2);
CLNEI( gigawingjd, gigawing, "Giga Wing (Japan 990223 Phoenix Edition) (bootleg)", BOOTLEG, 1999, GAME_SHOOT,
  .input = input_p2b2);
CLNEI( 1944d, 1944, "1944: The Loop Master (USA 000620 Phoenix Edition) (bootleg)", BOOTLEG, 2000, GAME_SHOOT,
  .input = input_p2b2);
CLNEI( progearud, progear, "Progear (USA 010117 Phoenix Edition) (bootleg)", BOOTLEG, 2001, GAME_SHOOT,
  .input = input_p2b3);
CLNEI( progearjd, progear, "Progear no Arashi (Japan 010117 Phoenix Edition) (bootleg)", BOOTLEG, 2001, GAME_SHOOT,
  .input = input_p2b3);
CLNEI( progearjbl, progear, "Progear no Arashi (Japan 010117) (decrypted bootleg)", BOOTLEG, 2001, GAME_SHOOT,
  .input = input_p2b3);
CLNEI( hsf2d, hsf2, "Hyper Street Fighter II: The Anniversary Edition (Asia 040202 Phoenix Edition) (bootleg)", BOOTLEG, 2004, GAME_BEAT);
CLNEI( ssf2tbd, ssf2, "Super Street Fighter II: The Tournament Battle (World 931119 Phoenix Edition) (bootleg)", BOOTLEG, 1993, GAME_BEAT);
CLNEI( ssf2xjd, ssf2t, "Super Street Fighter II X: Grand Master Challenge (Japan 940223 Phoenix Edition) (bootleg)", BOOTLEG, 1994, GAME_BEAT);
CLNEI( sgemfd, sgemf, "Super Gem Fighter Mini Mix (USA 970904 Phoenix Edition) (bootleg)", BOOTLEG, 1997, GAME_BEAT,
  .input = input_p2b3);
CLNEI( mmatrixd, mmatrix, "Mars Matrix: Hyper Solid Shooting (USA 000412 Phoenix Edition) (bootleg)", BOOTLEG, 2000, GAME_SHOOT,
  .input = input_p2b1,
  .romsw = romsw_phoenix);
CLNEI( dimahoud, dimahoo, "Dimahoo (USA 000121 Phoenix Edition) (bootleg)", BOOTLEG, 2000, GAME_SHOOT,
  .video = &video_cps1_270,
  .input = input_p2b3);
CLNEI( vhunt2d, vhunt2, "Vampire Hunter 2: Darkstalkers Revenge (Japan 970913 Phoenix Edition) (bootleg)", BOOTLEG, 1997, GAME_BEAT);
CLNEI( vsav2d, vsav2, "Vampire Savior 2: The Lord of Vampire (Japan 970913 Phoenix Edition) (bootleg)", BOOTLEG, 1997, GAME_BEAT);
CLNEI( csclub1d, csclub, "Capcom Sports Club (Euro 970722 Phoenix Edition) (bootleg)", BOOTLEG, 1997, GAME_SPORTS,
  .input = input_p2b3);
CLNEI( cybotsud, cybots, "Cyberbots: Fullmetal Madness (USA 950424 Phoenix Edition) (bootleg)", BOOTLEG, 1995, GAME_BEAT,
  .input = input_p2b4);
CLNEI( mshvsfu1d, mshvsf, "Marvel Super Heroes Vs. Street Fighter (USA 970625 Phoenix Edition) (bootleg)", BOOTLEG, 1997, GAME_BEAT);
CLNEI( sfz3jr2d, sfa3, "Street Fighter Zero 3 (Japan 980629 Phoenix Edition) (bootleg)", BOOTLEG, 1998, GAME_BEAT);

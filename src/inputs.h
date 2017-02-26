/**
 * @file inputs.h
 * @brief Common input sequences.
 *
 */

#ifndef MML_INPUTS_H
#define MML_INPUTS_H

#include "gctypes.h"
#include "controller.h"

/** represent an input in its minimal form **/
typedef struct __attribute__((packed))
{
    u16 controller;
    s8 frameOffset;
    u8 flags;

} RawInput;

typedef struct
{
    RawInput* inputs;
    u32 size;

} Move;

/** flags */
#define NO_FLAGS    0
#define JUMPSQUAT   (1 << 0)
#define SH_LENGTH   (1 << 1)

#define RELEASE 0x0000
#define STICK_ANGLE(x) ((((u8) (((x) / 360.f) * 255.f)) << 8) & 0xFF00)
#define OVERWRITE    {0, 0, 0}

/** @cond **/
extern RawInput _raw_shNeutralB[4];
extern RawInput _raw_shortHop[2];
extern RawInput _raw_tech[2];
extern RawInput _raw_spotDodge[3];
extern RawInput _raw_aPress[2];
extern RawInput _raw_hitDI[2];
extern RawInput _raw_throwDI[1];
extern RawInput _raw_UpB[2];
/** @endcond **/

/** Short Hop Neutral B. */
extern Move _mv_shNeutralB;

/** Short Hop */
extern Move _mv_shortHop;

/** Hit standard tech */
extern Move _mv_tech;

/** Set tech direction **/
#define SET_TECH_DIR(x) _raw_tech[0] = (RawInput) {L_BUTTON | FULL_STICK | STICK_ANGLE(x), 0, NO_FLAGS}

/** Spot Dodge */
extern Move _mv_spotDodge;

/** Get Up Attack */
extern Move _mv_getUpAttack;

/** Jab */
extern Move _mv_jab;

/** DI from hit */
extern Move _mv_hitDI;

/** Set the direction of DI for normal hits **/
#define SET_HIT_DI_DIR(x) _raw_hitDI[0] = (RawInput) {FULL_STICK | STICK_ANGLE((x)), 0, NO_FLAGS}

/** DI from throw */
extern Move _mv_throwDI;

/** Set the direction of DI for throws **/
#define SET_THROW_DI_DIR(x) _raw_throwDI[0] = (RawInput) {FULL_STICK | STICK_ANGLE((x)), 0, NO_FLAGS}

/** Up B **/
extern Move _mv_UpB;

/** Set the direction for the Up B **/
#define SET_UP_B_DIR(x) _raw_UpB[1] = (RawInput) {FULL_STICK | STICK_ANGLE((x)), 2, NO_FLAGS}

#endif

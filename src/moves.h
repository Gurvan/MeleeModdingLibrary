/**
 * @file moves.h
 * @brief Common input sequences.
 *
 */

#ifndef MML_MOVES_H
#define MML_MOVES_H

#include "gctypes.h"
#include "controller.h"

/** represent an input in its minimal form */
typedef struct __attribute__((packed))
{
    u16 controller; /**< controller state */
    s8 frameOffset; /**< frame offset */
    u8 flags; /**< input flags */

} RawInput;

/** Represents a single move (string of timed inputs) */
typedef struct
{
    RawInput* inputs; /**< input array */
    u32 size; /**< size of array */

} Move;

//@{
/** Input Flags */
#define NO_FLAGS    0
#define JUMPSQUAT   (1 << 0)
#define SH_LENGTH   (1 << 1)
//@}

//@{
/** Controller State Macros */
#define RELEASE 0x0000
#define STICK_ANGLE(x) ((((u8) (((x) / 360.f) * 255.f)) << 8) & 0xFF00)
#define OVERWRITE    {0, 0, 0}
//@}

/** @cond **/
extern RawInput _raw_shNeutralB[4];
extern RawInput _raw_shortHop[2];
extern RawInput _raw_tech[2];
extern RawInput _raw_spotDodge[3];
extern RawInput _raw_aPress[2];
extern RawInput _raw_hitDI[2];
extern RawInput _raw_holdDirection[1];
extern RawInput _raw_upB[2];
extern RawInput _raw_sideB[2];
extern RawInput _raw_doubleJump[1];
extern RawInput _raw_downB[2];
/** @endcond **/

/** Short Hop Neutral B. */
extern Move _mv_shNeutralB;

/** Short Hop */
extern Move _mv_shortHop;

/** Hit standard tech */
extern Move _mv_tech;

/** Set tech direction **/
#define SET_TECH_DIR(x) _raw_tech[0] = \
    (RawInput) {L_BUTTON | FULL_STICK | STICK_ANGLE(x), 0, NO_FLAGS}

/** Spot Dodge */
extern Move _mv_spotDodge;

/** Get Up Attack */
extern Move _mv_getUpAttack;

/** Jab */
extern Move _mv_jab;

/** DI from hit */
extern Move _mv_hitDI;

/** Set the direction of DI for normal hits */
#define SET_HIT_DI_DIR(x) _raw_hitDI[0] = \
    (RawInput) {FULL_STICK | STICK_ANGLE((x)), 0, NO_FLAGS}

/** DI from throw @note INDEFINITE */
extern Move _mv_throwDI;

/** Set the direction of DI for throws */
#define SET_THROW_DI_DIR(x) _raw_holdDirection[0] = \
    (RawInput) {FULL_STICK | STICK_ANGLE((x)), 0, NO_FLAGS}

/** Up B @note INDEFINITE */
extern Move _mv_upB;

/** Set the direction for the Up B */
#define SET_UP_B_DIR(x) _raw_upB[1] = \
    (RawInput) {FULL_STICK | STICK_ANGLE((x)), 2, NO_FLAGS}

/** Side B */
extern Move _mv_sideB;

/** Set the direction for the side B */
#define SET_SIDE_B_DIR(x) _raw_sideB[0] = \
    (RawInput) {B_BUTTON | FULL_STICK | STICK_ANGLE((x)), 0, NO_FLAGS}

/** Double Jump with Direction @note INDEFINITE */
extern Move _mv_doubleJump;

/** Set the direction for the double jump */
#define SET_DJ_DIR(x) _raw_doubleJump[0] = \
    (RawInput) {X_BUTTON | FULL_STICK | STICK_ANGLE((x)), 0, NO_FLAGS}

/** Ledgedash */
extern Move _mv_ledgeDash;

/** Hold Control Stick in Direction @note INDEFINITE */
extern Move _mv_holdDirection;

/** Set the direction of the control stick */
#define SET_HOLD_DIR(x) _raw_holdDirection[0] = \
    (RawInput) {FULL_STICK | STICK_ANGLE((x)), 0, NO_FLAGS}

/** Down B */
extern Move _mv_downB;

#endif


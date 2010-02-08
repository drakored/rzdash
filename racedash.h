/* racedash.h bitmap file for GLCD library */
/* Bitmap created from racedash.bmp        */
/* Date: 8 Feb 2010                             */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef racedash_H
#define racedash_H

static uint8_t racedash[] = {
  128, // width
  64, // height

  /* page 0 (lines 0-7) */
  0xff,0xff,0xe3,0xdf,0xbf,0xdf,0xe3,0xff,0xff,0x7f,0x3f,0x9f,0xcf,0xef,0xe7,0xf7,
  0xf3,0xfb,0xfb,0xf9,0xfd,0xfd,0xf9,0xf1,0xe5,0xcd,0x9d,0x3d,0x7d,0xfd,0xfd,0xfd,
  0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,
  0xfd,0xfd,0xfd,0x1,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0x1,0xfd,0xfd,0xfd,
  0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0x1,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,
  0xfd,0xfd,0x1,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0x1,0xfd,0xfd,
  0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0x1,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,
  0xfd,0xfd,0xfd,0x1,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0x1,0xff,
  
  /* page 1 (lines 8-15) */
  0xff,0xff,0xff,0x3f,0xf,0x27,0x73,0xf9,0xfc,0xfe,0xfe,0xfc,0xf9,0xf3,0xe7,0xcf,
  0x9f,0x3f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfc,0xf9,0xf3,
  0xe7,0xcf,0x9f,0x3f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0xff,
  
  /* page 2 (lines 16-23) */
  0xff,0x7,0xf0,0xfe,0xff,0xff,0xfe,0xfc,0xf9,0xf3,0xe7,0xcf,0x9f,0x3f,0x7f,0xff,
  0xff,0xff,0xfe,0xfc,0xf9,0xf3,0xe7,0xcf,0x9f,0x3f,0x7f,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xfe,0xfc,0xf9,0xf3,0xe7,0xcf,0x9f,0x3f,0x7f,0xff,0xff,0xff,
  0xff,0xff,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0xff,
  
  /* page 3 (lines 24-31) */
  0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfc,
  0xf9,0xf3,0xe7,0xcf,0x9f,0x3f,0x7f,0xff,0xff,0xff,0xfe,0xfc,0xf9,0xf3,0xe7,0xcf,
  0x9f,0x3f,0x7f,0xff,0xff,0x1f,0xdf,0x5f,0x5f,0x5f,0x5f,0x5f,0x5e,0x5c,0x59,0x53,
  0x47,0x4f,0x5f,0x40,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x40,0x5f,0x5f,0x5f,
  0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x40,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,
  0x5f,0x5f,0x40,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x40,0x5f,0x5f,
  0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x40,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,
  0x5f,0x5f,0x5f,0x40,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x40,0x7f,
  
  /* page 4 (lines 32-39) */
  0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfc,0xf9,0xf3,0xe7,0xcf,0x9f,0x3f,0x7f,0xff,
  0xff,0xff,0xfe,0xfc,0xf9,0x0,0xff,0x0,0xff,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
  0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
  0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
  0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
  0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
  0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0xff,
  
  /* page 5 (lines 40-47) */
  0xff,0x0,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,
  0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,
  0x7e,0x7e,0x7e,0x7e,0x7e,0x0,0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,
  
  /* page 6 (lines 48-55) */
  0xff,0x0,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,
  0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,
  0xdf,0xdf,0xdf,0xdf,0xdf,0x0,0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,
  
  /* page 7 (lines 56-63) */
  0xff,0x80,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,
  0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,
  0xbb,0xbb,0xbb,0xbb,0xbb,0x80,0xff,0x0,0xff,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
  0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
  0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
  0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
  0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
  0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xff
  
};
#endif

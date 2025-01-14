/*

    File: file_drw2.c

    Copyright (C) YEAR Christophe GRENIER <grenier@cgsecurity.org>

    This software is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write the Free Software Foundation, Inc., 51
    Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

 */

#if !defined(SINGLE_FORMAT) || defined(SINGLE_FORMAT_drw2)
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#include <stdio.h>
#include "types.h"
#include "filegen.h"

/*@ requires \valid(file_stat); */
static void register_header_check_drw2(file_stat_t *file_stat);

const file_hint_t file_hint_drw2= {
  .extension="drw",
  .description="Designer DRW file",
  .max_filesize=PHOTOREC_MAX_FILE_SIZE,
  .recover=1,
  .enable_by_default=1,
  .register_header_check=&register_header_check_drw2
};

/*
static void file_check_drw2(file_recovery_t *file_recovery)
{
  const unsigned char drw2_footer[FOOTER_SIZE]= {
    FOOTER_MAGIC
  };
  file_search_footer(file_recovery, drw2_footer, sizeof(drw2_footer), FOOTER_EXTRA);
}
*/

static int header_check_drw2(const unsigned char *buffer, const unsigned int buffer_size, const unsigned int safe_header_only, const file_recovery_t *file_recovery, file_recovery_t *file_recovery_new)
{
  reset_file_recovery(file_recovery_new);
  file_recovery_new->extension=file_hint_drw2.extension;
  //file_recovery_new->file_check=&file_check_drw2;
  return 1;
}

static void register_header_check_drw2(file_stat_t *file_stat)
{
  static const unsigned char drw2_header[10]=  {
     0x01, 0xff, 0x02, 0x04, 0x03, 0x02, 0x00, 0x02, 0x02, 0x02 
   // 0x01, 0xff, 0x02, 0x04, 0x03, 0x02, 0x00, 0x02, 0x02, 0x02, 0x21, 0x05, 0x00, 0x04
  };
  register_header_check(0, drw2_header, sizeof(drw2_header), &header_check_drw2, file_stat);
}
#endif

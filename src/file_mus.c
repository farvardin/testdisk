/*

    File: file_mus.c

    Copyright (C) 2006-2007 Christophe GRENIER <grenier@cgsecurity.org>
  
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

#if !defined(SINGLE_FORMAT) || defined(SINGLE_FORMAT_mus)
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
static void register_header_check_mus(file_stat_t *file_stat);

const file_hint_t file_hint_mus = {
  .extension = "mus",
  .description = "Finale Music Score",
  .max_filesize = PHOTOREC_MAX_FILE_SIZE,
  .recover = 1,
  .enable_by_default = 1,
  .register_header_check = &register_header_check_mus
};

/*@
  @ requires valid_file_recovery(file_recovery);
  @ requires \valid(file_recovery->handle);
  @ requires \separated(file_recovery, file_recovery->handle, file_recovery->extension, &errno, &Frama_C_entropy_source);
  @ requires \initialized(&file_recovery->time);
  @ requires file_recovery->file_check == &file_check_mus;
  @ ensures \valid(file_recovery->handle);
  @ assigns *file_recovery->handle, errno, file_recovery->file_size;
  @ assigns Frama_C_entropy_source;
  @*/
static void file_check_mus(file_recovery_t *file_recovery)
{
  const unsigned char mus_footer[5] = { '-', '^', 'e', 'n', 'd' };
  file_search_footer(file_recovery, mus_footer, sizeof(mus_footer), 0);
}

/*@
  @ requires buffer_size > 0;
  @ requires \valid_read(buffer+(0..buffer_size-1));
  @ requires valid_file_recovery(file_recovery);
  @ requires \valid(file_recovery_new);
  @ requires file_recovery_new->blocksize > 0;
  @ requires separation: \separated(&file_hint_mus, buffer+(..), file_recovery, file_recovery_new);
  @ ensures \result == 0 || \result == 1;
  @ ensures  \result!=0 ==> valid_file_recovery(file_recovery_new);
  @ assigns  *file_recovery_new;
  @*/
static int header_check_mus(const unsigned char *buffer, const unsigned int buffer_size, const unsigned int safe_header_only, const file_recovery_t *file_recovery, file_recovery_t *file_recovery_new)
{
  reset_file_recovery(file_recovery_new);
  file_recovery_new->min_filesize = 18;
  file_recovery_new->file_check = &file_check_mus;
  file_recovery_new->extension = file_hint_mus.extension;
  return 1;
}

static void register_header_check_mus(file_stat_t *file_stat)
{
  static const unsigned char mus_header[18] = { 'E', 'N', 'I', 'G', 'M', 'A', ' ', 'B', 'I', 'N', 'A', 'R', 'Y', ' ', 'F', 'I', 'L', 'E' };
  register_header_check(0, mus_header, sizeof(mus_header), &header_check_mus, file_stat);
}
#endif

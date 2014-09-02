/**
 * @author Chris Pick <conv@chrispick.com>
 * @section LICENSE
 *
 * Copyright 2010 Chris Pick. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY CHRIS PICK ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL CHRIS PICK OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of Chris Pick.
 */

#include <input.h>

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static bool input_prepend(input_t **pp_input, uint32_t value)
{
    static const input_t INPUT_INITIALIZER;

    input_t *p_input = malloc(sizeof(*p_input));
    if(!p_input)
    {
        fprintf(stderr,
                "%s: malloc failed\n",
                __func__);
        return false;
    }

    *p_input = INPUT_INITIALIZER;
    p_input->p_next = *pp_input;
    p_input->value = value;

    *pp_input = p_input;
    return true;
}

input_t *input_new(const char *p_buf)
{
    input_t *p_input = NULL;

    char *p_buf_parse_end;
    errno = 0;
    uint32_t value = strtol(p_buf, &p_buf_parse_end, 0 /*base*/);
    if((p_buf == p_buf_parse_end) || (*p_buf_parse_end != '\0')
            || (errno == ERANGE))
        goto fail;

    if(!input_prepend(&p_input, value))
        goto fail;

    return p_input;

fail:
    input_free(p_input);
    p_input = NULL;
    return p_input;
}

void input_free(input_t *p_input)
{
    while(p_input)
    {
        input_t *p_input_next = p_input->p_next;
        free(p_input);
        p_input = p_input_next;
    }
}

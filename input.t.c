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

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    /* test decimal */

    input_t *p_input = input_new("1234");
    if(!p_input)
    {
        fprintf(stderr, "%s: input_new failed\n", __func__);
        return EXIT_FAILURE;
    }

    uint32_t value_expected = 1234;
    if(value_expected != p_input->value)
    {
        fprintf(stderr,
                "%s: value expected: %" PRIu32 " got: %" PRIu32 "\n",
                __func__, value_expected, p_input->value);
        return EXIT_FAILURE;
    }

    if(p_input->p_next)
    {
        fprintf(stderr, "%s: unexpected next\n", __func__);
        return EXIT_FAILURE;
    }

    input_free(p_input);
    p_input = NULL;

    /* test invalid number */

    p_input = input_new("xyz");
    if(p_input)
    {
        fprintf(stderr, "%s: input_new succeeded unexpectedly\n", __func__);
        return EXIT_FAILURE;
    }

    printf("success\n");
    return EXIT_SUCCESS;
}

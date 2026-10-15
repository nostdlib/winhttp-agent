#pragma once

#include "types.h"
#include "stackstrings.h"
#include "ntdll.h"
#include "system.h"

class UUID {
    UINT8 data[16];

    public:
        constexpr UUID() noexcept : data{}
        {
        }
        constexpr UUID(const UINT8 initData[16]) noexcept : data{}
        {
            for (INT32 i = 0; i < 16; i++)
                data[i] = initData[i];
        }
        BOOL ToString(PCHAR out, USIZE outCapacity) const
        {
            if (out == NULL || outCapacity < 37) {
                if (out != NULL && outCapacity > 0)
                    out[0] = '\0';
                return FALSE;
            }

            USIZE index = 0;
            CHAR hex[17];
            BuildHexDigits(hex);
            for (INT32 i = 0; i < 16; i++)
            {
                out[index++] = hex[(USIZE)((data[i] >> 4) & 0xF)];
                out[index++] = hex[(USIZE)(data[i] & 0xF)];
                if (i == 3 || i == 5 || i == 7 || i == 9)
                    out[index++] = '-';
            }
            out[index] = '\0';
            return TRUE;
        }

        
};

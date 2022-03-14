#include "memset.h"
#include "types.h"

void memset(u8 *mem, u8 b, u64 l) {
    for (u64 i=0; i < l; i++) {
        *(mem+i) = b;
    }
}

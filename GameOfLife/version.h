#ifndef VERSION_H
#define VERSION_H

#define VER_MAJOR 0
#define VER_MINOR 7
#define VER_PATCH 0

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define VERSION_COUT VER_MAJOR << "." << VER_MINOR << "." << VER_PATCH
#define VERSION_STR STR(VER_MAJOR) "." STR(VER_MINOR) "." STR(VER_PATCH)

#endif // VERSION_H

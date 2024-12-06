#pragma once

#include <dirent.h>

namespace tt::app::files {

    /** File types for `dirent`'s `d_type`. */
enum {
    TT_DT_UNKNOWN = 0,
#define TT_DT_UNKNOWN TT_DT_UNKNOWN // Unknown type
    TT_DT_FIFO = 1,
#define TT_DT_FIFO TT_DT_FIFO // Named pipe or FIFO
    TT_DT_CHR = 2,
#define TT_DT_CHR TT_DT_CHR // Character device
    TT_DT_DIR = 4,
#define TT_DT_DIR TT_DT_DIR // Directory
    TT_DT_BLK = 6,
#define TT_DT_BLK TT_DT_BLK // Block device
    TT_DT_REG = 8,
#define TT_DT_REG TT_DT_REG // Regular file
    TT_DT_LNK = 10,
#define TT_DT_LNK TT_DT_LNK // Symbolic link
    TT_DT_SOCK = 12,
#define TT_DT_SOCK TT_DT_SOCK // Local-domain socket
    TT_DT_WHT = 14
#define TT_DT_WHT TT_DT_WHT // Whiteout inodes
};

typedef int (*ScandirFilter)(const struct dirent*);

typedef int (*ScandirSort)(const struct dirent**, const struct dirent**);

/**
 * Alphabetic sorting function for tt_scandir()
 * @param left left-hand side part for comparison
 * @param right right-hand side part for comparison
 * @return 0, -1 or 1
 */
int	dirent_sort_alpha(const struct dirent** left, const struct dirent** right);

int dirent_sort_alpha_and_type(const struct dirent** left, const struct dirent** right);

int dirent_filter_dot_entries(const struct dirent* entry);

/**
 * A scandir()-like implementation that works on ESP32.
 * It does not return "." and ".." items but otherwise functions the same.
 * It returns an allocated output array with allocated dirent instances.
 * The caller is responsible for free-ing the memory of these.
 *
 * @param[in] path path the scan for files and directories
 * @param[out] output a pointer to an array of dirent*
 * @param[in] filter an optional filter to filter out specific items
 * @param[in] sort an optional sorting function
 * @return the amount of items that were stored in "output" or -1 when an error occurred
 */
int scandir(
    const char* path,
    struct dirent*** output,
    ScandirFilter _Nullable filter,
    ScandirSort _Nullable sort
);

} // namespace
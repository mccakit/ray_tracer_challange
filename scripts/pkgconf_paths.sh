#!/usr/bin/env bash

ROOT="${1:-$PWD/conan/full_deploy/host}"

if [ ! -d "$ROOT" ]; then
    echo "Directory not found: $ROOT"
    return 1 2>/dev/null || exit 1
fi

# Collect all lib/pkgconfig directories
PKG_PATHS=$(find "$ROOT" -type d -path "*/lib/pkgconfig" | sort | paste -sd:)

if [ -z "$PKG_PATHS" ]; then
    echo "No pkgconfig directories found."
    return 1 2>/dev/null || exit 1
fi

# Preserve existing PKG_CONFIG_PATH if set
if [ -n "$PKG_CONFIG_PATH" ]; then
    export PKG_CONFIG_PATH="$PKG_PATHS:$PKG_CONFIG_PATH"
else
    export PKG_CONFIG_PATH="$PKG_PATHS"
fi

echo "PKG_CONFIG_PATH set."

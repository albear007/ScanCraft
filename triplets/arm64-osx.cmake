set(VCPKG_TARGET_ARCHITECTURE arm64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)

set(VCPKG_CMAKE_SYSTEM_NAME Darwin)
set(VCPKG_OSX_ARCHITECTURES arm64)

if (NOT DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 13.0)
endif()
### custom
# Disable compiler tracking to increase binary cache hit rate
# https://learn.microsoft.com/en-us/vcpkg/users/triplets
# https://github.com/microsoft/vcpkg/pull/17526
set(VCPKG_DISABLE_COMPILER_TRACKING ON)

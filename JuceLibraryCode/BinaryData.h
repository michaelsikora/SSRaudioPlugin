/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   IEMPluginSuiteSmall_png;
    const int            IEMPluginSuiteSmall_pngSize = 42218;

    extern const char*   RobotoBold_ttf;
    const int            RobotoBold_ttfSize = 135820;

    extern const char*   RobotoLight_ttf;
    const int            RobotoLight_ttfSize = 140276;

    extern const char*   RobotoMedium_ttf;
    const int            RobotoMedium_ttfSize = 137308;

    extern const char*   RobotoRegular_ttf;
    const int            RobotoRegular_ttfSize = 145348;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 5;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}

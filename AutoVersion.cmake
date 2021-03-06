### PREFACE ###
# https://github.com/mpb27/cmake-auto-version/blob/master/AutoVersion.cmake
#


### Git ###
find_package(Git)
if (GIT_FOUND)
    message(STATUS "Found Git")
    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
            OUTPUT_VARIABLE GIT_REVISION
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    message(STATUS "Current Git commit hash: " ${GIT_REVISION})
endif()


### Subversion ###
find_package(Subversion)
if (SUBVERSION_FOUND)
    message(STATUS "Found Subversion")
    get_filename_component(TMP ${VERSION_FILE} PATH)
    if (IS_DIRECTORY ${TMP}/.svn)
        message(STATUS "found svn folder: " ${TMP}/.svn)
        Subversion_WC_INFO(${VERSION_FILE} ABV)
        message(STATUS ${ABV_WC_LAST_CHANGED_REV})
    endif()
    #Subversion_WC_INFO(${VERSION_FILE} ABV)
    #message(STATUS ${ABV_WC_LAST_CHANGED_REV})
endif()


### MS Build Date ###
string(TIMESTAMP MS_BUILDDATE "%y%j")
message("MS Build Date: ${MS_BUILDDATE}")

##
# Version format: #define VERSION "<major>.<minor>-<increment>-<revision>"
# if revision doesn't exist, then use ms build date?
#
# Preserve major and minor
# increment <increment>
# update <revision>
#
#
#

string(TIMESTAMP TODAY "%Y")

### Read version file ###
if(NOT EXISTS ${VERSION_FILE})
    file(TOUCH ${VERSION_FILE})
    set(V_MAJOR "4") #initial commit
    set(V_MINOR "00")
    set(V_BUILD "1")
    set(V_REV   ${GIT_REVISION})
    file(WRITE ${VERSION_FILE} 
    "#pragma once\n#define SIMLIB_VERSION ${V_MAJOR}.${V_MINOR}.${V_BUILD}-${V_REV}\n"
    "#define SIMLIB_NVER 0x${V_MAJOR}${V_MINOR}\n"
    "#define SIMLIB_COPYRIGHT \"(c) Petr Peringer, 1991-${TODAY}\"")
else()
    file(READ ${VERSION_FILE} VERSION_TEXT)
    # ... regex used to match version, and 1-4 group matches ...
    string(REGEX MATCH "([0-9]+).([0-9]+).([0-9]+)" MY_MATCHES "${VERSION_TEXT}")
    set(V_MAJOR ${CMAKE_MATCH_1})
    set(V_MINOR ${CMAKE_MATCH_2})
    set(V_BUILD ${CMAKE_MATCH_3})
    set(V_REV   ${CMAKE_MATCH_4})
    message(STATUS "Major: ${V_MAJOR}   Minor: ${V_MINOR}   Build: ${V_BUILD}    Revision: ${V_REV}")
    # ... increment the build number ...
    math(EXPR V_BUILD "${V_BUILD}+1")
    # ... update revision ...
    set(V_REV ${GIT_REVISION})
    message(STATUS "Major: ${V_MAJOR}   Minor: ${V_MINOR}   Build: ${V_BUILD}    Revision: ${V_REV}")
    # ... regex to replace with new string ...
    string(REGEX REPLACE
            "([0-9]+).([0-9]+).([0-9]+)\\-([0-9a-zA-Z]+)"
            "${V_MAJOR}.${V_MINOR}.${V_BUILD}-${V_REV}"
            VERSION_TEXT "${VERSION_TEXT}")
    string(REGEX REPLACE
            "0x([0-9]+)"
            "0x${V_MAJOR}${V_MINOR}"
            VERSION_TEXT "${VERSION_TEXT}")
    string(REGEX REPLACE
            "1991-([0-9]+)"
            "1991-${TODAY}"
            VERSION_TEXT "${VERSION_TEXT}")
    # ... write back to file ...
    file(WRITE ${VERSION_FILE} "${VERSION_TEXT}")
endif()

# References:
#    - get GIT hash : https://stackoverflow.com/questions/949314/
#

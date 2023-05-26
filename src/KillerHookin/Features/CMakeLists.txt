
MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children ${curdir}/*) # This was changed
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${child}) # This was changed
            STRING (REPLACE "${curdir}/" "" child ${child})
            STRING (REPLACE "${curdir}" "" child ${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()


SUBDIRLIST (directories ${CMAKE_CURRENT_SOURCE_DIR})

FILE (READ "${CMAKE_CURRENT_SOURCE_DIR}/AddFeatures.h.in" contents)

SET (includes_string "")
SET (features_string "")

FOREACH (subdir ${directories})
    IF (NOT ${subdir} STREQUAL "Base")
	    STRING(APPEND includes_string "#include \"${subdir}/Feature${subdir}.h\"\n")
    ENDIF()
ENDFOREACH()

FOREACH (subdir ${directories})
    IF (NOT ${subdir} STREQUAL "Base")
	    STRING(APPEND features_string "Globals::g_features.emplace_back(new Feature${subdir}())\;\n\t\t")
    ENDIF()
ENDFOREACH()

STRING (REPLACE "//{EMPLACE_INCLUDES_HERE}//" "${includes_string}" contents "${contents}")
STRING (REPLACE "//{EMPLACE_FEATURES_HERE}//" "${features_string}" contents "${contents}")

FILE (WRITE "./AddFeatures.h" ${contents})
# This is a windows only file so we can run gradle tests via ctest

# Are these needed?
# FILE(TO_NATIVE_PATH ${GRADLE_EXECUTABLE} GRADLE_NATIVE_PATH)
# FILE(TO_NATIVE_PATH ${BIN_DIR} BINDIR_NATIVE_PATH)


execute_process(COMMAND cmd /C ${GRADLE_EXECUTABLE} --console=plain 
                cmakeCheck -DcmakeBuildDir=${BINDIR} -Dorg.gradle.daemon=false
                WORKING_DIRECTORY ${JAVA_SRC_ROOT}
                RESULT_VARIABLE HAD_ERROR)


if(HAD_ERROR)
message(FATAL_ERROR "Java Unitests failed")
endif()
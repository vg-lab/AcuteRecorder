# Copyright (c) 2012-2016 Stefan.Eilemann@epfl.ch
# See doc/GitTargets.md for documentation

# Targets:
# * ${PROJECT_NAME}-branch: Create a new branch for developing the current
#   version and push it to origin. The branch name is MAJOR.MINOR.
# * ${PROJECT_NAME}-cut: Delete the current version branch locally and remote.
# * ${PROJECT_NAME}-tag: Create the version branch if needed, and create a tag
#   release-VERSION on the version branch HEAD. Pushes the tag to the
#   origin repository.
# * ${PROJECT_NAME}-untag: Delete the current tag locally and remote
# * ${PROJECT_NAME}-retag: Move an existing tag to HEAD
# * tarball: Run ${PROJECT_NAME}-tarball for all projects
# * ${PROJECT_NAME}-tarball: Create an archive of the source code at
#   PROJECT_VERSION
# Targets for internal use:
# * ${PROJECT_NAME}-make-branch: Used by ${PROJECT_NAME}-branch to create a new
#   local branch
# * ${PROJECT_NAME}-create-tarball: Used by ${PROJECT_NAME}-tarball

if(GITTARGETS_FOUND)
  return()
endif()
set(GITTARGETS_FOUND 1)

if(NOT GIT_FOUND)
  find_package(Git QUIET)
endif()
if(NOT GIT_EXECUTABLE)
  return()
endif()

find_program(GZIP_EXECUTABLE gzip)

# branch
set(BRANCH_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
add_custom_target(${PROJECT_NAME}-make-branch
  COMMAND "${GIT_EXECUTABLE}" checkout ${BRANCH_VERSION} || "${GIT_EXECUTABLE}" checkout -b ${BRANCH_VERSION}
  COMMENT "Create local branch ${BRANCH_VERSION}"
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
  )

if(TARGET ${PROJECT_NAME}-flatten-gitexternal)
  set(BRANCH_DEP ${PROJECT_NAME}-flatten-gitexternal)
else()
  set(BRANCH_DEP ${PROJECT_NAME}-make-branch)
endif()

add_custom_target(${PROJECT_NAME}-branch
  COMMAND "${GIT_EXECUTABLE}" push origin ${BRANCH_VERSION}
  COMMENT "Add remote branch ${BRANCH_VERSION}"
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
  DEPENDS ${BRANCH_DEP}
  )

# remove branch
add_custom_target(${PROJECT_NAME}-cut
  COMMAND "${GIT_EXECUTABLE}" branch -d ${BRANCH_VERSION}
  COMMAND "${GIT_EXECUTABLE}" push origin --delete ${BRANCH_VERSION}
  COMMENT "Remove branch ${BRANCH_VERSION}"
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
  )

# tag on branch
file(WRITE ${PROJECT_BINARY_DIR}/gitbranchandtag.cmake
  "# Branch:
   execute_process(COMMAND \"${GIT_EXECUTABLE}\" branch ${BRANCH_VERSION}
     RESULT_VARIABLE hadbranch ERROR_VARIABLE error
     WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
   if(NOT hadbranch)
     execute_process(COMMAND \"${GIT_EXECUTABLE}\" push origin ${BRANCH_VERSION}
      WORKING_DIRECTORY \"${PROJECT_SOURCE_DIR}\")
   endif()
   set(TAG_BRANCH ${BRANCH_VERSION})

   # Create or move tag
   execute_process(
     COMMAND \"${GIT_EXECUTABLE}\" tag -f ${PROJECT_VERSION} ${TAG_BRANCH}
     COMMAND \"${GIT_EXECUTABLE}\" push --tags
     RESULT_VARIABLE notdone WORKING_DIRECTORY \"${PROJECT_SOURCE_DIR}\")
   if(notdone)
     message(FATAL_ERROR
        \"Error creating tag ${PROJECT_VERSION} on branch ${TAG_BRANCH}\")
   endif()")

add_custom_target(${PROJECT_NAME}-tag
  COMMAND "${CMAKE_COMMAND}" -P "${PROJECT_BINARY_DIR}/gitbranchandtag.cmake"
  COMMENT "Add tag ${PROJECT_VERSION}"
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
  )

# remove tag
add_custom_target(${PROJECT_NAME}-untag
  COMMAND "${GIT_EXECUTABLE}" tag -d ${PROJECT_VERSION}
  COMMAND "${GIT_EXECUTABLE}" push origin :${PROJECT_VERSION}
  COMMENT "Remove tag ${PROJECT_VERSION}"
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
  )

# move tag
add_custom_target(${PROJECT_NAME}-retag
  COMMAND "${CMAKE_COMMAND}" -P "${PROJECT_BINARY_DIR}/gitbranchandtag.cmake"
  COMMENT "Add tag ${PROJECT_VERSION}"
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
  DEPENDS ${PROJECT_NAME}-untag)

# tarball
set(TARBALL "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}.tar")

add_custom_target(${PROJECT_NAME}-create-tarball
  COMMAND "${GIT_EXECUTABLE}" archive --worktree-attributes
    --prefix ${PROJECT_NAME}-${PROJECT_VERSION}/ -o ${TARBALL}
    ${PROJECT_VERSION}
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
  COMMENT "Creating ${TARBALL}"
  )

if(GZIP_EXECUTABLE)
  set(TARBALL_GZ "${TARBALL}.gz")
  add_custom_target(${PROJECT_NAME}-tarball
    COMMAND "${CMAKE_COMMAND}" -E remove ${TARBALL_GZ}
    COMMAND "${GZIP_EXECUTABLE}" ${TARBALL}
    DEPENDS ${PROJECT_NAME}-create-tarball
    WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
    COMMENT "Compressing ${TARBALL_GZ}"
  )
else()
  add_custom_target(${PROJECT_NAME}-tarball DEPENDS ${PROJECT_NAME}-create-tarball)
endif()

if(NOT TARGET tarball)
  add_custom_target(tarball)
endif()
add_dependencies(tarball ${PROJECT_NAME}-tarball)

set(_gittargets_TARGETS ${PROJECT_NAME}-branch ${PROJECT_NAME}-make-branch
  ${PROJECT_NAME}-cut ${PROJECT_NAME}-tag ${PROJECT_NAME}-untag tarball
  ${PROJECT_NAME}-retag ${PROJECT_NAME}-tarball ${PROJECT_NAME}-create-tarball)
foreach(_gittargets_TARGET ${_gittargets_TARGETS})
  set_target_properties(${_gittargets_TARGET} PROPERTIES
    EXCLUDE_FROM_DEFAULT_BUILD ON FOLDER git)
endforeach()

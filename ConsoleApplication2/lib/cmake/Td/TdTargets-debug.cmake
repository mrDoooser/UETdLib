#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Td::tdutils" for configuration "Debug"
set_property(TARGET Td::tdutils APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Td::tdutils PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/tdutils.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Td::tdutils )
list(APPEND _IMPORT_CHECK_FILES_FOR_Td::tdutils "${_IMPORT_PREFIX}/lib/tdutils.lib" )

# Import target "Td::tdactor" for configuration "Debug"
set_property(TARGET Td::tdactor APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Td::tdactor PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/tdactor.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Td::tdactor )
list(APPEND _IMPORT_CHECK_FILES_FOR_Td::tdactor "${_IMPORT_PREFIX}/lib/tdactor.lib" )

# Import target "Td::tdnet" for configuration "Debug"
set_property(TARGET Td::tdnet APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Td::tdnet PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/tdnet.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Td::tdnet )
list(APPEND _IMPORT_CHECK_FILES_FOR_Td::tdnet "${_IMPORT_PREFIX}/lib/tdnet.lib" )

# Import target "Td::tdsqlite" for configuration "Debug"
set_property(TARGET Td::tdsqlite APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Td::tdsqlite PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/tdsqlite.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Td::tdsqlite )
list(APPEND _IMPORT_CHECK_FILES_FOR_Td::tdsqlite "${_IMPORT_PREFIX}/lib/tdsqlite.lib" )

# Import target "Td::tddb" for configuration "Debug"
set_property(TARGET Td::tddb APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Td::tddb PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/tddb.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Td::tddb )
list(APPEND _IMPORT_CHECK_FILES_FOR_Td::tddb "${_IMPORT_PREFIX}/lib/tddb.lib" )

# Import target "Td::tdjson" for configuration "Debug"
set_property(TARGET Td::tdjson APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Td::tdjson PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/tdjson.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/tdjson.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Td::tdjson )
list(APPEND _IMPORT_CHECK_FILES_FOR_Td::tdjson "${_IMPORT_PREFIX}/lib/tdjson.lib" "${_IMPORT_PREFIX}/bin/tdjson.dll" )

# Import target "Td::tdjson_static" for configuration "Debug"
set_property(TARGET Td::tdjson_static APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Td::tdjson_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/tdjson_static.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Td::tdjson_static )
list(APPEND _IMPORT_CHECK_FILES_FOR_Td::tdjson_static "${_IMPORT_PREFIX}/lib/tdjson_static.lib" )

# Import target "Td::tdjson_private" for configuration "Debug"
set_property(TARGET Td::tdjson_private APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Td::tdjson_private PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/tdjson_private.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Td::tdjson_private )
list(APPEND _IMPORT_CHECK_FILES_FOR_Td::tdjson_private "${_IMPORT_PREFIX}/lib/tdjson_private.lib" )

# Import target "Td::tdclient" for configuration "Debug"
set_property(TARGET Td::tdclient APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Td::tdclient PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/tdclient.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Td::tdclient )
list(APPEND _IMPORT_CHECK_FILES_FOR_Td::tdclient "${_IMPORT_PREFIX}/lib/tdclient.lib" )

# Import target "Td::tdcore" for configuration "Debug"
set_property(TARGET Td::tdcore APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Td::tdcore PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/tdcore.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Td::tdcore )
list(APPEND _IMPORT_CHECK_FILES_FOR_Td::tdcore "${_IMPORT_PREFIX}/lib/tdcore.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

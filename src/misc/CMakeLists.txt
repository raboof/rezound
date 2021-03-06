cmake_minimum_required(VERSION 3.1)	
project(misc)

find_package(BISON)
BISON_TARGET(cfg_tab CNestedDataFile/cfg.y "${CMAKE_CURRENT_BINARY_DIR}/cfg.tab.cpp" COMPILE_FLAGS "-b cfg")

find_package(FLEX)
FLEX_TARGET(cfg_lex CNestedDataFile/cfg.l "${CMAKE_CURRENT_BINARY_DIR}/cfg.lex.cpp")
ADD_FLEX_BISON_DEPENDENCY(cfg_lex cfg_tab)

add_library(misc STATIC
	stdx/latch
	stdx/thread
	stdx/stdx.cpp 

	CPath.h
	endian_util.h
	#TMemoryPipe.cpp
	TMemoryPipe.h
	TTempVarSetter.h

	CNestedDataFile/CNestedDataFile.h
	CNestedDataFile/anytype.h
	CNestedDataFile/CNestedDataFile.cpp
	"${FLEX_cfg_lex_OUTPUTS}"
	"${BISON_cfg_tab_OUTPUTS}"
)

if (ENABLE_NLS)
	# for convenience, since misc is a dependency of everything, just make the INTL target a dependency of it
	target_include_directories(misc PUBLIC ${Intl_INCLUDE_DIRS})
	target_link_libraries(misc ${Intl_LIBRARIES})
endif()


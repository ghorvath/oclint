macro(build_dynamic_rule name)
  set(CMAKE_SHARED_LINKER_FLAGS "-undefined dynamic_lookup")
  
  add_library(${name} SHARED
    ${name}.cpp
    )
  
  SET_TARGET_PROPERTIES(${name}
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/oclint/rules
    )

  target_link_libraries(${name} 
    ${OCLINT_COMMON_LINK_LIB}
    OCLintCore
    OCLintHelper
    OCLintException
    )
endmacro(build_dynamic_rule)

macro(build_dynamic_rules rules)
  FOREACH(it ${rules})
    build_dynamic_rule(${it})
  ENDFOREACH(it)
endmacro(build_dynamic_rules)

macro(build_static_rules rules)
  SET(cpp_files)
  FOREACH(it ${rules})
    list(APPEND cpp_files ${it}.cpp)
  ENDFOREACH(it)
  
  add_library(OCLintRule ${cpp_files})
endmacro(build_static_rules)

SET(LIST_OF_RULES 
  EmptyIfStatementRule
  UnusedLocalVariableRule
  UnusedMethodParameterRule
  CyclomaticComplexityRule
  LongParameterListRule
  LongMethodRule
  ConstantIfStatementRule
  UnreachableCodeRule
  NPathComplexityRule
  IfStatementWithNegatedConditionRule
  RedundantIfStatementRule
  RedundantLocalVariableRule
  )

if(IS_CI_BUILD)
build_static_rules("${LIST_OF_RULES}")
endif()

build_dynamic_rules("${LIST_OF_RULES}")

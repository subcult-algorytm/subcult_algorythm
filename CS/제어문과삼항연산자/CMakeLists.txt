project(ControlStatementAndTriadOperator)

add_executable(ControlStatementAndTriadOperator test.cpp)

if(MSVC)
    target_compile_options(ControlStatementAndTriadOperator PRIVATE /O2)
endif()

set_property(TARGET ControlStatementAndTriadOperator PROPERTY COMPILE_OPTIONS "/RTC-")


set_target_properties(ControlStatementAndTriadOperator PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
#pragma once
#include <string>

class ErrorMessages {
public:
    static const std::string MASS_ZERO;
    static const std::string INVALID_INPUT;
    static const std::string OUT_OF_BOUNDS;
    static const std::string UNSUPPORTED_OPERATION;
    static const std::string GLFWINITFAILED;
    static const std::string WINDOWCREATIONFAILED;
    static const std::string OPENGLFAILEDTOINIT;
    static const std::string SHADERSCOMPILEERROR;
    static const std::string PROGRAMCOMPILEERROR;
    static const std::string SHADERSLOADINGERROR;
};

const std::string ErrorMessages::INVALID_INPUT = "INVALID INPUT: Value is not acceptable";
const std::string ErrorMessages::OUT_OF_BOUNDS = "ERROR: Value is out of bounds";
const std::string ErrorMessages::UNSUPPORTED_OPERATION = "ERROR: Operation is not supported";
const std::string ErrorMessages::GLFWINITFAILED = "ERROR: GLFW INIT FAIL";
const std::string ErrorMessages::WINDOWCREATIONFAILED = "ERROR: An error ocurried while creating window";
const std::string ErrorMessages::OPENGLFAILEDTOINIT = "ERROR: An error ocurried while tryng to start OPENGL";
const std::string ErrorMessages::SHADERSCOMPILEERROR = "One or more errors ocurried while compiling shaders";
const std::string ErrorMessages::PROGRAMCOMPILEERROR = "One or more errors ocurried while compiling program";
const std::string ErrorMessages::SHADERSLOADINGERROR = "ERROR: An error ocurried while loading shaders";
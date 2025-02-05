#include <iostream>
#include "OpenGlResources.h"
#include "ProgramBuild.h"
#include "ProgramKit.h"

int main() {
	try {
		std::unique_ptr<ProgramKit> program = resources.getProgram();
		PB::BuildProgram(program->getProgram(), program->getWindow());

		return EXIT_SUCCESS;
	}
	catch (std::runtime_error er) {
		std::cerr << "[ERROR]: " << er.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (std::invalid_argument er) {
		std::cerr << "[ERROR]: " << er.what() << std::endl;
		return EXIT_FAILURE;
	}
}
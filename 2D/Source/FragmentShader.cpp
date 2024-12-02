#include "FragmentShader.h"

color4_t FragmentShader::Process(const fragment_input_t& fragment)
{
	return fragment.color;
}



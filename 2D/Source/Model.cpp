	#include "Model.h"
#include "Framebuffer.h"
#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>


bool Model::Load(const std::string& filename)
{
	std::ifstream stream(filename);
	if (!stream.is_open()) {
		std::cerr << "Error loading your model: " << filename << std::endl;
		return false;
	}
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;

	std::string line;
	while (std::getline(stream, line)) {
		// Push in vertices
		if (line.substr(0, 2) == "v ") {
			std::istringstream sstream{ line.substr(2) };
			glm::vec3 position;
			sstream >> position.x;
			sstream >> position.y;
			sstream >> position.z;
			vertices.push_back(position);
		}
		// Push in normals	
		else if (line.substr(0, 3) == "vn ") {
			// read normal of vertex
			std::istringstream sstream{ line.substr(3) };
			glm::vec3 normal;		
			sstream >> normal.x;
			sstream >> normal.y;
			sstream >> normal.z;
			normals.push_back(normal);
		}
		else if (line.substr(0, 2) == "f ") {
			std::istringstream sstream{ line.substr(2) };
			std::string str;
			while (std::getline(sstream, str, ' ')) {
				std::istringstream sstream(str);
				std::string indexString;

				size_t i = 0;
				unsigned int index[3] = { 0, 0, 0 };
				while (std::getline(sstream, indexString, '/')) {
					if (!indexString.empty()) {
						std::istringstream indexStream{ indexString };
						indexStream >> index[i];
					}
					i++;
				}
				if (index[0]) {

					vertex_t vertex;
					vertex.position = vertices[index[0] - 1];
					vertex.normal = (index[2]) ? normals[index[2] - 1] : glm::vec3{ 1 };

					m_vb.push_back(vertex);

				}
			}
		}
	}

	stream.close();
	return true;
}

void Model::SetColor(const color4_t& color)
{
	m_color = color;
}

void Model::Draw()
{
	Shader::Draw(m_vb);

}

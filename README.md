# Software Renderer and Ray Tracer

## Overview
This project is a dual-purpose rendering engine that implements a **Software Renderer** and a **Ray Tracer**. Designed for high-quality 3D visualization, it supports various shading techniques, realistic lighting, and post-processing effects. The project is built using **SDL** and **glm** libraries.

---

## Features

### Software Renderer
- **Shader Support**: 
  - Vertex shaders for geometry transformation.
  - Fragment shaders for pixel-level manipulation.
- **Lighting Models**:
  - Gouraud shading for smooth lighting across surfaces. (work in progress)
  - Phong shading for detailed highlights and reflections. (work in progress)
- **3D Model Rendering**: Efficiently loads and renders complex 3D models. (Currently has a bug that it doesn't load the model)
- **Post-Processing**: Adds visual effects after rendering, enhancing the final image.
- **Rendering Primitives**: Supports basic geometric shapes such as triangles, lines, and points.

### Ray Tracer
- **Material Rendering**:
  - Lambertian (diffuse) surfaces.
  - Metallic surfaces with realistic reflections.
  - Dielectric materials (e.g., glass) with refractive properties.
- **Anti-Aliasing**: Reduces jagged edges for smoother visuals.
- **Multiple Bounce Reflections**: Simulates realistic light behavior with multiple reflections and refractions.
- **Support for Complex Models**: Handles intricate geometry with ease.

---

## Requirements

- **SDL2**: For window management and input handling.
- **glm**: For mathematical operations (vectors, matrices, transformations).

---

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/software-renderer-ray-tracer.git
   cd software-renderer-ray-tracer
   ```
2. Install dependencies:
   ```bash
   sudo apt-get install libsdl2-dev
   ```
   Or use your package manager for SDL2.
3. Build the project:
   ```bash
   make
   ```

---

## Usage

1. Run the executable:
   ```bash
   ./renderer
   ```
2. Use keyboard and mouse controls to interact with the rendered scene.
3. Customize shaders and materials through configuration files.

---

## Demo
Include screenshots or gifs showing the Software Renderer and Ray Tracer in action.

---

## Contributing

1. Fork the repository.
2. Create a new branch for your feature:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes and push:
   ```bash
   git commit -m "Add feature-name"
   git push origin feature-name
   ```
4. Open a pull request.

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Acknowledgments

- **SDL**: [https://www.libsdl.org/](https://www.libsdl.org/)
- **glm**: [https://glm.g-truc.net/](https://glm.g-truc.net/)

---

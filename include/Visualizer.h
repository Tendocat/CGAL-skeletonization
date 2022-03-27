#pragma once

#include <pmp/visualization/MeshViewer.h>

class Visualizer : public pmp::MeshViewer
{
public:
	Visualizer(const std::string& title, int width, int height);
	void process_imgui();
};
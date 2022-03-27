//
// Created by evanz on 3/18/22.
//

#ifndef SKGEN_VIEWER_H
#define SKGEN_VIEWER_H

#include <pmp/visualization/MeshViewer.h>

class Viewer : public pmp::MeshViewer
{
public:
	Viewer(const std::string& title, int width, int height, bool show_imgui = true);

	void process_imgui();

};

#endif //SKGEN_VIEWER_H

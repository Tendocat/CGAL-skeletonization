//
// Created by evanz on 3/18/22.
//

#ifndef SKGEN_VIEWER_H
#define SKGEN_VIEWER_H

#include <pmp/visualization/MeshViewer.h>
#include <imgui.h>
#include <imfilebrowser.h>

class Viewer : public pmp::MeshViewer
{
public:
	Viewer() = delete;
	Viewer(const std::string& title, int width, int height, bool showgui = true);

	void process_imgui();

private:
    ImGui::FileBrowser fb;

};

#endif //SKGEN_VIEWER_H

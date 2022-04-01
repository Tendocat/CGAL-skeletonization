//
// Created by evanz on 3/18/22.
//

#pragma once

#include <pmp/visualization/MeshViewer.h>
#include <imgui.h>
#include <imfilebrowser.h>

class MeshViewer : public pmp::MeshViewer
{
public:
	MeshViewer() = delete;
	MeshViewer(const std::string& title, int width, int height, bool showgui = true);

	void process_imgui();

private:
    ImGui::FileBrowser fb;

};
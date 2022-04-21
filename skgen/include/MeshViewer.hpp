//
// Created by evanz on 3/18/22.
//

#pragma once

#include <pmp/visualization/MeshViewer.h>
#include <imgui.h>
#include <imfilebrowser.h>

#include "Skeleton.hpp"

class MeshViewer : public pmp::MeshViewer
{
    public:
        MeshViewer() = delete;
        MeshViewer(const std::string& title, int width, int height, bool showgui = true);

        void process_imgui();

        void update_mesh() override;
        void draw(const std::string& draw_mode) override;
        

    private:
        ImGui::FileBrowser _fbMesh;
        ImGui::FileBrowser _fbSkel;

        pmp::SurfaceMeshGL _skeleton;

        bool _isDrawingSkeleton;
};

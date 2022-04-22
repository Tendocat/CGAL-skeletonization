#pragma once

#include <pmp/visualization/MeshViewer.h>
#include <imgui.h>
#include <imfilebrowser.h>

#include "SkeletonManager.hpp"

/**
 * @brief ...
 */
class MeshViewer : public pmp::MeshViewer
{
    private:
        inline static const float BREAK_THRESHOLD_MIN = 0.6f;
        inline static const float BREAK_THRESHOLD_MAX = 1.4f;

        ImGui::FileBrowser _fbMesh;

        pmp::SurfaceMeshGL _skeleton;

        bool _drawSkeleton;

        float _breakThreshold;

    public:
        MeshViewer() = delete;
        MeshViewer(const std::string& title, int width, int height, bool showgui = true);

        /**
         * @brief MeshViewer overided loop
         */
        void process_imgui();

        /**
         * @brief load the skeleton of a mesh at a given path
         */
        void load_skeleton(const char* path);

        /**
         * @brief ...
         */
        void update_mesh() override;

        /**
         * @brief ...
         */
        void draw(const std::string& draw_mode) override;
};

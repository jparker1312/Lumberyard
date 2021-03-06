#pragma once

/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#include <AzCore/std/string/string.h>
#include <AzCore/std/containers/vector.h>
#include <AzCore/std/containers/unordered_map.h>
#include <GFxFramework/MaterialIO/IMaterial.h>
#include <SceneAPI/SceneCore/Events/CallProcessorBinder.h>

struct IConvertContext;

namespace AZ
{
    namespace SceneAPI
    {
        namespace DataTypes
        {
            class IGroup;
        }
    }
    namespace RC
    {
        struct MeshGroupExportContext;
        struct ContainerExportContext;
        struct MeshNodeExportContext;

        class MaterialExporter
            : public SceneAPI::Events::CallProcessorBinder
        {
        public:
            MaterialExporter(IConvertContext* convertContext);
            ~MaterialExporter() override = default;

            SceneAPI::Events::ProcessingResult SetupMaterial(GroupExportContext& context);
            SceneAPI::Events::ProcessingResult ConfigureContainer(ContainerExportContext& context);
            SceneAPI::Events::ProcessingResult ProcessNode(NodeExportContext& context);
            SceneAPI::Events::ProcessingResult PatchMesh(MeshNodeExportContext& context);

        protected:
            SceneAPI::Events::ProcessingResult HandleMaterialFileLoadingAndCreation(GroupExportContext& context);

            bool LoadMaterialFile(GroupExportContext& context);

            void SetupGlobalMaterial(ContainerExportContext& context);
            void CreateSubMaterials(ContainerExportContext& context);
            void PatchSubmeshes(ContainerExportContext& context);
            void AssignCommonMaterial(NodeExportContext& context);
            SceneAPI::Events::ProcessingResult PatchMaterials(MeshNodeExportContext& context);
            SceneAPI::Events::ProcessingResult BuildRelocationTable(AZStd::vector<size_t>& table, MeshNodeExportContext& context);
            void Reset();

            AZStd::shared_ptr<AZ::GFxFramework::IMaterialGroup> m_materialGroup;
            AZStd::unordered_map<int, AZStd::string> m_physMaterialNames;
            const SceneAPI::DataTypes::IGroup* m_cachedGroup;
            IConvertContext* m_convertContext;
            bool m_exportMaterial;
        };
    } // RC
} // AZ

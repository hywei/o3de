/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Component/EntityId.h>
#include <Editor/Nodes/NodeUtils.h>
#include <ScriptCanvas/Bus/NodeIdPair.h>
#include <ScriptCanvas/Core/SubgraphInterfaceUtility.h>
#include <ScriptCanvas/Variable/VariableCore.h>
#include <ScriptCanvas/Data/Data.h>


namespace ScriptCanvas
{
    class Node;
}

namespace ScriptEvents
{
    class Method;
}

namespace ScriptCanvasEditor::Nodes
{

    struct DataDrivenNodeCreationData
    {
        AZ_TYPE_INFO(DataDrivenNodeCreationData, "{A7DE9ECF-81F9-4A03-B3E4-3510591A50BB}");
        AZ_CLASS_ALLOCATOR(DataDrivenNodeCreationData, AZ::SystemAllocator);

        static void Reflect(AZ::ReflectContext* reflectContext);

        AZ::Crc32 m_lexicalId;
        AZStd::any m_userData;
        AZStd::string m_title;
        AZStd::string m_toolTip;
        ScriptCanvas::Data::Type m_dataType;
        AZStd::string m_subStyle;
    };

    // Specific create methods which will also handle displaying the node.
    AZStd::pair<ScriptCanvas::Node*, NodeIdPair> CreateAndGetNode(const AZ::Uuid& classData, const ScriptCanvas::ScriptCanvasId& scriptCanvasId, const StyleConfiguration& styleConfiguration, AZStd::function<void(ScriptCanvas::Node*)> = nullptr);
    NodeIdPair CreateNode(const AZ::Uuid& classData, const ScriptCanvas::ScriptCanvasId& scriptCanvasId, const StyleConfiguration& styleConfiguration);
    NodeIdPair CreateObjectMethodNode(AZStd::string_view className, AZStd::string_view methodName, const ScriptCanvas::ScriptCanvasId& scriptCanvasId, ScriptCanvas::PropertyStatus propertyStatus);
    NodeIdPair CreateObjectMethodOverloadNode(AZStd::string_view className, AZStd::string_view methodName, const ScriptCanvas::ScriptCanvasId& scriptCanvasGraphId);
    NodeIdPair CreateGlobalMethodNode(AZStd::string_view methodName, bool isProperty, const ScriptCanvas::ScriptCanvasId& scriptCanvasId);
    NodeIdPair CreateEbusWrapperNode(AZStd::string_view busName, const ScriptCanvas::ScriptCanvasId& scriptCanvasId);

    // Create methods for data driven nodes
    NodeIdPair CreateDataDrivenNode(const ScriptCanvasEditor::Nodes::DataDrivenNodeCreationData& nodeData, const ScriptCanvas::ScriptCanvasId& scriptCanvasId);

    // Script Events
    NodeIdPair CreateScriptEventReceiverNode(const ScriptCanvas::ScriptCanvasId& scriptCanvasId, const AZ::Data::AssetId& assetId);
    NodeIdPair CreateScriptEventSenderNode(const ScriptCanvas::ScriptCanvasId& scriptCanvasId, const AZ::Data::AssetId& assetId, const ScriptCanvas::EBusEventId& eventId);

    // CreateNodeResult
    CreateNodeResult CreateGetVariableNodeResult(const ScriptCanvas::VariableId& variableId, ScriptCanvas::ScriptCanvasId scriptCanvasGraphId);
    CreateNodeResult CreateSetVariableNodeResult(const ScriptCanvas::VariableId& variableId, ScriptCanvas::ScriptCanvasId scriptCanvasGraphId);
    NodeIdPair CreateGetVariableNode(const ScriptCanvas::VariableId& variableId, ScriptCanvas::ScriptCanvasId scriptCanvasGraphId);
    NodeIdPair CreateSetVariableNode(const ScriptCanvas::VariableId& variableId, ScriptCanvas::ScriptCanvasId scriptCanvasGraphId);

    // Functions
    NodeIdPair CreateFunctionNode(const ScriptCanvas::ScriptCanvasId& scriptCanvasGraphId, const AZ::Data::AssetId& assetId, const ScriptCanvas::Grammar::FunctionSourceId& sourceId);
    NodeIdPair CreateFunctionDefinitionNode(const ScriptCanvas::ScriptCanvasId& scriptCanvasId, bool isInput, AZStd::string rootName = "New Nodeling");

    // AZ Event
    NodeIdPair CreateAzEventHandlerNode(const AZ::BehaviorMethod& methodWithAzEventReturn, ScriptCanvas::ScriptCanvasId scriptCanvasId,
        AZ::EntityId connectingMethodNodeId);
}

#pragma once

#include "DataExport/Rendering/Headers/AssimpExtensions.h"

namespace Data
{
	namespace DataExport
	{
		// created bone from existing node (deep copy)
		ExportNode::ExportNode(Core::Ptr<const aiNode> initialNode)
		{
			exportNode = false;
			
			// don't care about meshes since those will be handled elsewhere

			mName = initialNode->mName;
			mTransformation = initialNode->mTransformation;

			mNumChildren = initialNode->mNumChildren;
			mChildren = new Core::Ptr<aiNode>[mNumChildren];
			for (Core::uint i = 0; i < mNumChildren; i++)
			{
				mChildren[i] = new ExportNode(initialNode->mChildren[i]);
				mChildren[i]->mParent = this;
			}
		}

		// marks node as include if names match
		void ExportNode::IncludeNode(Core::String name)
		{
			IncludeIfContainsName(name);
		}

		bool ExportNode::IncludeIfContainsName(Core::String name)
		{
			bool include = false;

			if (mName == aiString(name))
			{
				include = true;
			}

			for (Core::uint i = 0; i < mNumChildren; i++)
			{
				if (static_cast<Core::Ptr<ExportNode>>(mChildren[i])->IncludeIfContainsName(name))
				{
					include = true;
				}
			}

			exportNode |= include;
			return include;
		}

		// marks all nodes with an included child node as export
		// then removes any nodes not marked as export
		void ExportNode::CleanStructure()
		{
			for (Core::uint i = 0; i < mNumChildren; i++)
			{
				static_cast<Core::Ptr<ExportNode>>(mChildren[i])->CleanStructure();
			}

			ExportIfChildren();
			RemoveNonExportChildren();
		}

		void ExportNode::ExportIfChildren()
		{
			if (exportNode)
			{
				return;
			}

			for (Core::uint i = 0; i < mNumChildren; i++)
			{
				if (static_cast<Core::Ptr<ExportNode>>(mChildren[i])->exportNode)
				{
					exportNode = true;
					return;
				}
			}
		}

		void ExportNode::RemoveNonExportChildren()
		{
			for (int i = mNumChildren - 1; i >= 0; i--)
			{
				if (static_cast<Core::Ptr<ExportNode>>(mChildren[i])->exportNode)
				{
					delete mChildren[i];
					mNumChildren--;
				}
			}
		}
	}
}

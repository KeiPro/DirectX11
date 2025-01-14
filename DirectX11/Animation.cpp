#include "pch.h"
#include "Animation.h"
#include "Texture.h"

Animation::Animation() : Super(ResourceType::Animation)
{
}

Animation::~Animation()
{
}

void Animation::Load(const wstring& path)
{
	tinyxml2::XMLDocument doc;

	string pathStr(path.begin(), path.end());

	XMLError error = doc.LoadFile(pathStr.c_str());
	assert(error == XmlError::XML_SUCCESS);

	XmlElement* root = doc.FirstChildElement();
	string nameStr = root->Attribute("Name");
	_name = wstring(nameStr.begin(), nameStr.end());

	_loop = root->BoolAttribute("Loop");
	_path = path;

	// Load Texture
	XmlElement* node =  root->FirstChildElement();
	while (node != nullptr)
	{
		Keyframe keyframe;

		keyframe.offset.x = node->FloatAttribute("OffsetX");
		keyframe.offset.y = node->FloatAttribute("OffsetY");
		keyframe.size.x = node->FloatAttribute("SizeX");
		keyframe.size.y = node->FloatAttribute("SizeY");
		keyframe.time = node->FloatAttribute("Time");

		AddKeyframe(keyframe);

		node = node->NextSiblingElement(); // 트리구조에서 형제들을 순환할 때 사용.
	}

}

void Animation::Save(const wstring& path)
{
	tinyxml2::XMLDocument doc;

	XMLElement* root = doc.NewElement("Animation");
	doc.LinkEndChild(root); // <Animation> 이라는 노드를 생성.

	string nameStr(GetName().begin(), GetName().end());
	root->SetAttribute("Name", nameStr.c_str()); // <Animation Name="SnakeAnim"> </Animation> 이렇게 내용이 추가된다.
	root->SetAttribute("Loop", _loop);
	root->SetAttribute("TexturePath", "TODO");

	for (const auto& keyframe : _keyframes)
	{
		XMLElement* node = doc.NewElement("Keyframe");
		root->LinkEndChild(node);

		node->SetAttribute("OffsetX", keyframe.offset.x);
		node->SetAttribute("OffsetY", keyframe.offset.y);
		node->SetAttribute("SizeX", keyframe.size.x);
		node->SetAttribute("SizeY", keyframe.size.y);
		node->SetAttribute("Time", keyframe.time);
	}

	string pathStr(path.begin(), path.end());
	auto result = doc.SaveFile(pathStr.c_str());
	assert(result == XMLError::XML_SUCCESS);
}

Vec2 Animation::GetTextureSize()
{
	return _texture->GetSize();
}

const Keyframe& Animation::GetKeyframe(int32 index)
{
	return _keyframes[index];
}

int32 Animation::GetKeyframeCount()
{
	return static_cast<int32>(_keyframes.size());
}

void Animation::AddKeyframe(const Keyframe& keyframe)
{
	_keyframes.push_back(keyframe);
}

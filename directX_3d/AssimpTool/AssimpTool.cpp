#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	//{
	//	shared_ptr<Converter> converter = make_shared<Converter>();

	//	// FBX -> Memory
	//	converter->ReadAssetFile(L"House/House.fbx");

	//	// Memory -> CustomData로 저장
	//	converter->ExportMaterialData(L"House/House");
	//	converter->ExportModelData(L"House/House");

	//	// 사용할 땐, CustomData를 불러와서 Memory에 저장.
	//	// CustomData -> Memory
	//}

	{
		shared_ptr<Converter> converter = make_shared<Converter>();

		// FBX -> Memory
		converter->ReadAssetFile(L"Tower/Tower.fbx");

		// Memory -> CustomData로 저장
		converter->ExportMaterialData(L"Tower/Tower");
		converter->ExportModelData(L"Tower/Tower");

		// 사용할 땐, CustomData를 불러와서 Memory에 저장.
		// CustomData -> Memory
	}
}

void AssimpTool::Update()
{
}

void AssimpTool::Render()
{
}

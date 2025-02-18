#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	{
		shared_ptr<Converter> converter = make_shared<Converter>();

		// FBX -> Memory
		converter->ReadAssetFile(L"Kachujin/Mesh.fbx");

		// Memory -> CustomData로 저장
		converter->ExportMaterialData(L"Kachujin/Kachujin");
		converter->ExportModelData(L"Kachujin/Kachujin");

		// 사용할 땐, CustomData를 불러와서 Memory에 저장.
		// CustomData -> Memory
	}

	//{
	//	shared_ptr<Converter> converter = make_shared<Converter>();

	//	// FBX -> Memory
	//	converter->ReadAssetFile(L"Tank/Tank.fbx");

	//	// Memory -> CustomData로 저장
	//	converter->ExportMaterialData(L"Tank/Tank");
	//	converter->ExportModelData(L"Tank/Tank");

	//	// 사용할 땐, CustomData를 불러와서 Memory에 저장.
	//	// CustomData -> Memory
	//}
}

void AssimpTool::Update()
{
}

void AssimpTool::Render()
{
}

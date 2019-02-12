#include "Moa.h"
#include "../Engine/MemoryInputStream.h"
#include "../Engine/CppGame.h"
#include <iostream>

Moa::Moa(char* meshData, int dataLength)
{
	MemoryInputStream reader(meshData, dataLength);
	while (!reader.Eof()) {
		char* buffer;
		reader.get(buffer, 16);
		delete[] buffer;

		char nameLength = 0;
		char* name;
		reader.get(nameLength);
		reader.get(name, nameLength);

		std::cout << name << std::endl;

		char unkCount = 0;
		reader.get(unkCount);

		char* unkdat;
		reader.get(unkdat, 8);
		delete[] unkdat;

		for (int i = 0; i < unkCount; ++i)
		{
			int unk;
			reader.get(unk);
		}

		char* unkData;
		reader.get(unkData, 56);
		delete[] unkData;


		char count = 0;
		reader.get(count);
		for (int i = 0; i < count; ++i)
		{
			int modelId = 0;
			reader.get(modelId);

			int charLib = 0;
			reader.get(charLib);

			char* submeshName;
			reader.get(submeshName, 4);


			unsigned long meshDataLength;
			char* submeshData;

			if (CppGame::Loader.get_file(modelId, &meshDataLength, submeshData))
			{
				std::cout << "Successfully loaded model: " << submeshName[0] << submeshName[1] << submeshName[2] << submeshName[3] << " ID: " << std::hex << modelId << std::endl;
			}
			else
			{
				std::cout << "Failed to load model: " << submeshName[0] << submeshName[1] << submeshName[2] << submeshName[3] << " ID: " << std::hex << modelId << std::endl;

			}

			char matValueCount;
			reader.get(matValueCount);
			int baseValue = 0;
			int colorMap = 0;

			for (int j = 0; j < matValueCount; ++j)
			{
				char* matName;
				reader.get(matName, 4);
				int id = 0;
				reader.get(id);

				std::string matNameString(matName, 4);

				if (matNameString == "BASE")
					baseValue = id;
				if (matNameString == "CMAP")
					colorMap = id;
			}

			MgaMesh* mesh;

			unsigned long textureDatLength;
			char* textureDat;

			if (CppGame::Loader.get_file(baseValue, &textureDatLength, textureDat))
				std::cout << "Successfully loaded texture: " << " ID: " << std::hex << baseValue << std::endl;

			auto tex = new TxaTexture(textureDat, textureDatLength);

			if (colorMap != 0) {
				unsigned long colorTexDatLength;
				char* colorTexDat;

				if (CppGame::Loader.get_file(colorMap, &colorTexDatLength, colorTexDat))
					std::cout << "Successfully loaded color map: " << " ID: " << std::hex << colorMap << std::endl;

				auto colorTex = new TxaTexture(colorTexDat, colorTexDatLength);

				mesh = new MgaMesh(submeshData, meshDataLength, tex, nullptr);
			}
			else
			{
				mesh = new MgaMesh(submeshData, meshDataLength, tex, nullptr);
			}


			submeshes.push_back(mesh);
			if (submeshData != nullptr)
				delete[] submeshData;


			int mat1Count;
			reader.get(mat1Count);
			for (int j = 0; j < mat1Count; ++j)
			{
				char type = 0;
				reader.get(type);

				char* matName;
				reader.get(matName, 3);

				int unk0 = 0;
				int unk1 = 0;
				int unk2 = 0;
				int unk3 = 0;
				char unk4 = 0;

				reader.get(unk0);
				reader.get(unk1);
				reader.get(unk2);
				reader.get(unk3);
				reader.get(unk4);
			}
		}

		char unk = 0;
		reader.get(unk);
	}
}

void Moa::Draw(Shader& shader)
{
	for (auto submesh : submeshes)
	{
		submesh->Draw(shader);
	}
}

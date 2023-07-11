#include "jhRenderer.h"
#include "jhResources.h"
#include "jhMaterial.h"
#include "jhSceneManager.h"
#include "jhPaintShader.h"
#include "jhParticleShader.h"

namespace jh::renderer
{
	Vertex vertexes[4] = {};
	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	Camera* mainCamera = nullptr;
	std::vector<Camera*> cameras[(UINT)eSceneType::End];
	std::vector<DebugMesh> debugMeshes;
	std::vector<LightAttribute> lights;
	StructedBuffer* lightsBuffer = nullptr;

	void LoadMesh()
	{
		#pragma region POINT MESH
				Vertex v = {};
				std::shared_ptr<Mesh> pointMesh = std::make_shared<Mesh>();
				Resources::Insert<Mesh>(L"PointMesh", pointMesh);
				pointMesh->CreateVertexBuffer(&v, 1);
				UINT pointIndex = 0;
				pointMesh->CreateIndexBuffer(&pointIndex, 1);
		#pragma endregion
		#pragma region RECT MESH
				vertexes[0].pos = Vector4(-0.5f, 0.5f, 0.f, 1.f);
				vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
				vertexes[0].uv = Vector2(0.f, 0.f);

				vertexes[1].pos = Vector4(0.5f, 0.5f, 0.f, 1.f);
				vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
				vertexes[1].uv = Vector2(1.f, 0.f);

				vertexes[2].pos = Vector4(0.5f, -0.5f, 0.f, 1.f);
				vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
				vertexes[2].uv = Vector2(1.f, 1.f);

				vertexes[3].pos = Vector4(-0.5f, -0.5f, 0.f, 1.f);
				vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
				vertexes[3].uv = Vector2(0.f, 1.f);

				// Create Mesh
				std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
				Resources::Insert<Mesh>(L"RectMesh", mesh);
				mesh->CreateVertexBuffer(vertexes, 4);

				// �ε��� ����
				std::vector<UINT> indexes;
				indexes.push_back(0);
				indexes.push_back(1);
				indexes.push_back(2);

				indexes.push_back(0);
				indexes.push_back(2);
				indexes.push_back(3);
				indexes.push_back(0);
				mesh->CreateIndexBuffer(indexes.data(), indexes.size());
		#pragma endregion
		#pragma region DEBUG RECT MESH
				vertexes[0].pos = Vector4(-0.5f, 0.5f, -0.00001f, 1.0f);
				vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
				vertexes[0].uv = Vector2(0.f, 0.f);

				vertexes[1].pos = Vector4(0.5f, 0.5f, -0.00001f, 1.0f);
				vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
				vertexes[1].uv = Vector2(1.0f, 0.0f);

				vertexes[2].pos = Vector4(0.5f, -0.5f, -0.00001f, 1.0f);
				vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
				vertexes[2].uv = Vector2(1.0f, 1.0f);

				vertexes[3].pos = Vector4(-0.5f, -0.5f, -0.00001f, 1.0f);
				vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
				vertexes[3].uv = Vector2(0.0f, 1.0f);

				std::shared_ptr<Mesh> debugMesh = std::make_shared<Mesh>();
				Resources::Insert<Mesh>(L"DebugRectMesh", debugMesh);
				debugMesh->CreateVertexBuffer(vertexes, 4);
				debugMesh->CreateIndexBuffer(indexes.data(), indexes.size());
		#pragma endregion
		#pragma region CIRCLE MESH
				std::vector<Vertex> circleVertexes;
				Vertex center = {};
				center.pos = Vector4(0.f, 0.f, -0.00001f, 1.f);
				center.color = Vector4(0.f, 1.f, 0.f, 1.f);
				center.uv = Vector2::Zero;

				circleVertexes.push_back(center);

				int iSlice = 80;
				float fRadius = 0.5f;
				float fTheta = XM_2PI / (float)iSlice;

				for (size_t i = 0; i < iSlice; i++)
				{
					Vertex vtx = {};
					vtx.pos = Vector4(fRadius * cosf(fTheta * (float)i),
						fRadius * sinf(fTheta * (float)i), -0.00001f, 1.f);
					vtx.color = center.color;

					circleVertexes.push_back(vtx);
				}

				// �ε��� ����
				indexes.clear();

				for (size_t i = 0; i < iSlice - 2; i++)
				{
					indexes.push_back((UINT)i + 1);
				}
				indexes.push_back(1);

				// Create Mesh
				std::shared_ptr<Mesh> circleMesh = std::make_shared<Mesh>();
				Resources::Insert<Mesh>(L"CircleMesh", circleMesh);
				circleMesh->CreateVertexBuffer(circleVertexes.data(), circleVertexes.size());
				circleMesh->CreateIndexBuffer(indexes.data(), indexes.size());
		#pragma endregion
#pragma region Cube Mesh
				Vertex arrCube[24] = {};

				// ����
				arrCube[0].pos = Vector4(-0.5f, 0.5f, 0.5f, 1.0f);
				arrCube[0].color = Vector4(1.f, 1.f, 1.f, 1.f);
				arrCube[0].uv = Vector2(0.f, 0.f);
				arrCube[0].normal = Vector3(0.f, 1.f, 0.f);

				arrCube[1].pos = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
				arrCube[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
				arrCube[1].uv = Vector2(0.f, 0.f);
				arrCube[1].normal = Vector3(0.f, 1.f, 0.f);

				arrCube[2].pos = Vector4(0.5f, 0.5f, -0.5f, 1.0f);
				arrCube[2].color = Vector4(1.f, 1.f, 1.f, 1.f);
				arrCube[2].uv = Vector2(0.f, 0.f);
				arrCube[2].normal = Vector3(0.f, 1.f, 0.f);

				arrCube[3].pos = Vector4(-0.5f, 0.5f, -0.5f, 1.0f);
				arrCube[3].color = Vector4(1.f, 1.f, 1.f, 1.f);
				arrCube[3].uv = Vector2(0.f, 0.f);
				arrCube[3].normal = Vector3(0.f, 1.f, 0.f);

				// �Ʒ� ��	
				arrCube[4].pos = Vector4(-0.5f, -0.5f, -0.5f, 1.0f);
				arrCube[4].color = Vector4(1.f, 0.f, 0.f, 1.f);
				arrCube[4].uv = Vector2(0.f, 0.f);
				arrCube[4].normal = Vector3(0.f, -1.f, 0.f);

				arrCube[5].pos = Vector4(0.5f, -0.5f, -0.5f, 1.0f);
				arrCube[5].color = Vector4(1.f, 0.f, 0.f, 1.f);
				arrCube[5].uv = Vector2(0.f, 0.f);
				arrCube[5].normal = Vector3(0.f, -1.f, 0.f);

				arrCube[6].pos = Vector4(0.5f, -0.5f, 0.5f, 1.0f);
				arrCube[6].color = Vector4(1.f, 0.f, 0.f, 1.f);
				arrCube[6].uv = Vector2(0.f, 0.f);
				arrCube[6].normal = Vector3(0.f, -1.f, 0.f);

				arrCube[7].pos = Vector4(-0.5f, -0.5f, 0.5f, 1.0f);
				arrCube[7].color = Vector4(1.f, 0.f, 0.f, 1.f);
				arrCube[7].uv = Vector2(0.f, 0.f);
				arrCube[7].normal = Vector3(0.f, -1.f, 0.f);

				// ���� ��
				arrCube[8].pos = Vector4(-0.5f, 0.5f, 0.5f, 1.0f);
				arrCube[8].color = Vector4(0.f, 1.f, 0.f, 1.f);
				arrCube[8].uv = Vector2(0.f, 0.f);
				arrCube[8].normal = Vector3(-1.f, 0.f, 0.f);

				arrCube[9].pos = Vector4(-0.5f, 0.5f, -0.5f, 1.0f);
				arrCube[9].color = Vector4(0.f, 1.f, 0.f, 1.f);
				arrCube[9].uv = Vector2(0.f, 0.f);
				arrCube[9].normal = Vector3(-1.f, 0.f, 0.f);

				arrCube[10].pos = Vector4(-0.5f, -0.5f, -0.5f, 1.0f);
				arrCube[10].color = Vector4(0.f, 1.f, 0.f, 1.f);
				arrCube[10].uv = Vector2(0.f, 0.f);
				arrCube[10].normal = Vector3(-1.f, 0.f, 0.f);

				arrCube[11].pos = Vector4(-0.5f, -0.5f, 0.5f, 1.0f);
				arrCube[11].color = Vector4(0.f, 1.f, 0.f, 1.f);
				arrCube[11].uv = Vector2(0.f, 0.f);
				arrCube[11].normal = Vector3(-1.f, 0.f, 0.f);

				// ������ ��
				arrCube[12].pos = Vector4(0.5f, 0.5f, -0.5f, 1.0f);
				arrCube[12].color = Vector4(0.f, 0.f, 1.f, 1.f);
				arrCube[12].uv = Vector2(0.f, 0.f);
				arrCube[12].normal = Vector3(1.f, 0.f, 0.f);

				arrCube[13].pos = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
				arrCube[13].color = Vector4(0.f, 0.f, 1.f, 1.f);
				arrCube[13].uv = Vector2(0.f, 0.f);
				arrCube[13].normal = Vector3(1.f, 0.f, 0.f);

				arrCube[14].pos = Vector4(0.5f, -0.5f, 0.5f, 1.0f);
				arrCube[14].color = Vector4(0.f, 0.f, 1.f, 1.f);
				arrCube[14].uv = Vector2(0.f, 0.f);
				arrCube[14].normal = Vector3(1.f, 0.f, 0.f);

				arrCube[15].pos = Vector4(0.5f, -0.5f, -0.5f, 1.0f);
				arrCube[15].color = Vector4(0.f, 0.f, 1.f, 1.f);
				arrCube[15].uv = Vector2(0.f, 0.f);
				arrCube[15].normal = Vector3(1.f, 0.f, 0.f);

				// �� ��
				arrCube[16].pos = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
				arrCube[16].color = Vector4(1.f, 1.f, 0.f, 1.f);
				arrCube[16].uv = Vector2(0.f, 0.f);
				arrCube[16].normal = Vector3(0.f, 0.f, 1.f);

				arrCube[17].pos = Vector4(-0.5f, 0.5f, 0.5f, 1.0f);
				arrCube[17].color = Vector4(1.f, 1.f, 0.f, 1.f);
				arrCube[17].uv = Vector2(0.f, 0.f);
				arrCube[17].normal = Vector3(0.f, 0.f, 1.f);

				arrCube[18].pos = Vector4(-0.5f, -0.5f, 0.5f, 1.0f);
				arrCube[18].color = Vector4(1.f, 1.f, 0.f, 1.f);
				arrCube[18].uv = Vector2(0.f, 0.f);
				arrCube[18].normal = Vector3(0.f, 0.f, 1.f);

				arrCube[19].pos = Vector4(0.5f, -0.5f, 0.5f, 1.0f);
				arrCube[19].color = Vector4(1.f, 1.f, 0.f, 1.f);
				arrCube[19].uv = Vector2(0.f, 0.f);
				arrCube[19].normal = Vector3(0.f, 0.f, 1.f);

				// �� ��
				arrCube[20].pos = Vector4(-0.5f, 0.5f, -0.5f, 1.0f);;
				arrCube[20].color = Vector4(1.f, 0.f, 1.f, 1.f);
				arrCube[20].uv = Vector2(0.f, 0.f);
				arrCube[20].normal = Vector3(0.f, 0.f, -1.f);

				arrCube[21].pos = Vector4(0.5f, 0.5f, -0.5f, 1.0f);
				arrCube[21].color = Vector4(1.f, 0.f, 1.f, 1.f);
				arrCube[21].uv = Vector2(0.f, 0.f);
				arrCube[21].normal = Vector3(0.f, 0.f, -1.f);

				arrCube[22].pos = Vector4(0.5f, -0.5f, -0.5f, 1.0f);
				arrCube[22].color = Vector4(1.f, 0.f, 1.f, 1.f);
				arrCube[22].uv = Vector2(0.f, 0.f);
				arrCube[22].normal = Vector3(0.f, 0.f, -1.f);

				arrCube[23].pos = Vector4(-0.5f, -0.5f, -0.5f, 1.0f);
				arrCube[23].color = Vector4(1.f, 0.f, 1.f, 1.f);
				arrCube[23].uv = Vector2(0.f, 0.f);
				arrCube[23].normal = Vector3(0.f, 0.f, -1.f);

				indexes.clear();
				for (size_t i = 0; i < 6; i++)
				{
					indexes.push_back(i * 4);
					indexes.push_back(i * 4 + 1);
					indexes.push_back(i * 4 + 2);

					indexes.push_back(i * 4);
					indexes.push_back(i * 4 + 2);
					indexes.push_back(i * 4 + 3);
				}

				// Create Mesh
				std::shared_ptr<Mesh> cubeMesh = std::make_shared<Mesh>();
				Resources::Insert<Mesh>(L"CubeMesh", cubeMesh);
				cubeMesh->CreateVertexBuffer(arrCube, 24);
				cubeMesh->CreateIndexBuffer(indexes.data(), indexes.size());
#pragma endregion
	}

	void LoadShader()
	{
		#pragma region DEFAULT TRIANGLE SHADER
				std::shared_ptr<Shader> defaultShader = std::make_shared<Shader>();
				defaultShader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
				defaultShader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");

				Resources::Insert<Shader>(L"RectShader", defaultShader);
		#pragma endregion
		#pragma region SPRITE SHADER
				std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
				spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
				spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
				spriteShader->SetRSState(eRSType::SolidNone);

				Resources::Insert<Shader>(L"SpriteShader", spriteShader);
		#pragma endregion
		#pragma region UI SHADER
				std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
				uiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
				uiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

				Resources::Insert<Shader>(L"UIShader", uiShader);
		#pragma endregion
		#pragma region GRID SHADER
				std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
				gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
				gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
				gridShader->SetRSState(eRSType::SolidNone);
				gridShader->SetDSState(eDSType::NoWrite);
				gridShader->SetBSState(eBSType::AlphaBlend);

				Resources::Insert<Shader>(L"GridShader", gridShader);
		#pragma endregion
		#pragma region FADE SHADER
				std::shared_ptr<Shader> fadeShader = std::make_shared<Shader>();
				fadeShader->Create(eShaderStage::VS, L"FadeInOutVS.hlsl", "main");
				fadeShader->Create(eShaderStage::PS, L"FadeInOutPS.hlsl", "main");
				fadeShader->SetRSState(eRSType::SolidNone);
				fadeShader->SetDSState(eDSType::NoWrite);
				fadeShader->SetBSState(eBSType::AlphaBlend);

				Resources::Insert<Shader>(L"FadeShader", fadeShader);
		#pragma endregion
		#pragma region DEBUG SHADER
				std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
				debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
				debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
				debugShader->SetRSState(eRSType::SolidNone);
				debugShader->SetDSState(eDSType::NoWrite);
				debugShader->SetBSState(eBSType::AlphaBlend);
				debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

				Resources::Insert<Shader>(L"DebugShader", debugShader);
		#pragma endregion
		#pragma region PAINT SHADER
				std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
				paintShader->Create(L"PaintCS.hlsl", "main");

				Resources::Insert<PaintShader>(L"PaintShader", paintShader);
		#pragma endregion
		#pragma region PARTICLE SHADER
				std::shared_ptr<Shader> particleShader = std::make_shared<Shader>();
				particleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
				particleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
				particleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
				particleShader->SetRSState(eRSType::SolidNone);
				particleShader->SetDSState(eDSType::NoWrite);
				particleShader->SetBSState(eBSType::AlphaBlend);
				particleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

				Resources::Insert<Shader>(L"ParticleShader", particleShader);

				std::shared_ptr<ParticleShader> particleCS = std::make_shared<ParticleShader>();
				Resources::Insert<ParticleShader>(L"ParticleCS", particleCS);
				particleCS->Create(L"ParticleCS.hlsl", "main");
		#pragma endregion
#pragma region BASIC 3D
				std::shared_ptr<Shader> basicShader = std::make_shared<Shader>();
				basicShader->Create(eShaderStage::VS, L"BasicVS.hlsl", "main");
				basicShader->Create(eShaderStage::PS, L"BasicPS.hlsl", "main");
				Resources::Insert<Shader>(L"BasicShader", basicShader);
#pragma endregion
	}

	void SetUpState()
	{
		// Input Layout (���� ���� ����)
		#pragma region Input Layout
				D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[6] = {};

				arrLayoutDesc[0].AlignedByteOffset = 0;
				arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				arrLayoutDesc[0].InputSlot = 0;
				arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				arrLayoutDesc[0].SemanticName = "POSITION";
				arrLayoutDesc[0].SemanticIndex = 0;

				arrLayoutDesc[1].AlignedByteOffset = 16;
				arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				arrLayoutDesc[1].InputSlot = 0;
				arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				arrLayoutDesc[1].SemanticName = "COLOR";
				arrLayoutDesc[1].SemanticIndex = 0;

				arrLayoutDesc[2].AlignedByteOffset = 32;
				arrLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
				arrLayoutDesc[2].InputSlot = 0;
				arrLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				arrLayoutDesc[2].SemanticName = "TEXCOORD";
				arrLayoutDesc[2].SemanticIndex = 0;

				arrLayoutDesc[3].AlignedByteOffset = 40;
				arrLayoutDesc[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				arrLayoutDesc[3].InputSlot = 0;
				arrLayoutDesc[3].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				arrLayoutDesc[3].SemanticName = "TANGENT";
				arrLayoutDesc[3].SemanticIndex = 0;

				arrLayoutDesc[4].AlignedByteOffset = 52;
				arrLayoutDesc[4].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				arrLayoutDesc[4].InputSlot = 0;
				arrLayoutDesc[4].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				arrLayoutDesc[4].SemanticName = "BINORMAL";
				arrLayoutDesc[4].SemanticIndex = 0;

				arrLayoutDesc[5].AlignedByteOffset = 64;
				arrLayoutDesc[5].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				arrLayoutDesc[5].InputSlot = 0;
				arrLayoutDesc[5].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				arrLayoutDesc[5].SemanticName = "NORMAL";
				arrLayoutDesc[5].SemanticIndex = 0;

				std::shared_ptr<Shader> defaultShader = Resources::Find<Shader>(L"RectShader");
				GetDevice()->CreateInputLayout(arrLayoutDesc, 3, defaultShader->GetVSBlobBufferPointer(),
					defaultShader->GetVSBlobBufferSize(), defaultShader->GetInputLayoutAddressOf());

				std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
				GetDevice()->CreateInputLayout(arrLayoutDesc, 3, spriteShader->GetVSBlobBufferPointer(),
					spriteShader->GetVSBlobBufferSize(), spriteShader->GetInputLayoutAddressOf());

				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				GetDevice()->CreateInputLayout(arrLayoutDesc, 3, uiShader->GetVSBlobBufferPointer(),
					uiShader->GetVSBlobBufferSize(), uiShader->GetInputLayoutAddressOf());

				std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
				GetDevice()->CreateInputLayout(arrLayoutDesc, 3, gridShader->GetVSBlobBufferPointer(),
					gridShader->GetVSBlobBufferSize(), gridShader->GetInputLayoutAddressOf());

				std::shared_ptr<Shader> fadeShader = Resources::Find<Shader>(L"FadeShader");
				GetDevice()->CreateInputLayout(arrLayoutDesc, 3, fadeShader->GetVSBlobBufferPointer(),
					fadeShader->GetVSBlobBufferSize(), fadeShader->GetInputLayoutAddressOf());

				std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
				GetDevice()->CreateInputLayout(arrLayoutDesc, 3, debugShader->GetVSBlobBufferPointer(),
					debugShader->GetVSBlobBufferSize(), debugShader->GetInputLayoutAddressOf());

				std::shared_ptr<Shader> particleShader = Resources::Find<Shader>(L"ParticleShader");
				GetDevice()->CreateInputLayout(arrLayoutDesc, 3, particleShader->GetVSBlobBufferPointer(),
					particleShader->GetVSBlobBufferSize(), particleShader->GetInputLayoutAddressOf());

				std::shared_ptr<Shader> basicShader = Resources::Find<Shader>(L"BasicShader");
				GetDevice()->CreateInputLayout(arrLayoutDesc, 6, basicShader->GetVSBlobBufferPointer(),
					basicShader->GetVSBlobBufferSize(), basicShader->GetInputLayoutAddressOf());
		#pragma endregion

		#pragma region SamplerState
				D3D11_SAMPLER_DESC samplerDesc = {};
				samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
				samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
				samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
				samplerDesc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;

				GetDevice()->CreateSamplerState(&samplerDesc,
					samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

				samplerDesc.Filter = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
				GetDevice()->CreateSamplerState(&samplerDesc,
					samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());

				samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
				GetDevice()->CreateSamplerState(&samplerDesc,
					samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());

				GetDevice()->BindsSamplers((UINT)eSamplerType::Point, 1,
					samplerStates[(UINT)eSamplerType::Point].GetAddressOf());
				GetDevice()->BindsSamplers((UINT)eSamplerType::Linear, 1,
					samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());
				GetDevice()->BindsSamplers((UINT)eSamplerType::Anisotropic, 1,
					samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		#pragma endregion

		#pragma region RasterizerState
				D3D11_RASTERIZER_DESC rsDesc = {};
				rsDesc.FillMode = D3D11_FILL_SOLID;
				rsDesc.CullMode = D3D11_CULL_BACK;

				GetDevice()->CreateRasterizerState(&rsDesc,
					rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

				rsDesc.FillMode = D3D11_FILL_SOLID;
				rsDesc.CullMode = D3D11_CULL_FRONT;

				GetDevice()->CreateRasterizerState(&rsDesc,
					rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

				rsDesc.FillMode = D3D11_FILL_SOLID;
				rsDesc.CullMode = D3D11_CULL_NONE;

				GetDevice()->CreateRasterizerState(&rsDesc,
					rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

				rsDesc.FillMode = D3D11_FILL_WIREFRAME;
				rsDesc.CullMode = D3D11_CULL_NONE;

				GetDevice()->CreateRasterizerState(&rsDesc,
					rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
		#pragma endregion

		#pragma region DepthStencilState
				D3D11_DEPTH_STENCIL_DESC dsDesc = {};
				dsDesc.DepthEnable = true;
				dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
				dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				dsDesc.StencilEnable = false;

				GetDevice()->CreateDepthStencilState(&dsDesc,
					depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

				dsDesc.DepthEnable = true;
				dsDesc.DepthFunc = D3D11_COMPARISON_GREATER;
				dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				dsDesc.StencilEnable = false;

				GetDevice()->CreateDepthStencilState(&dsDesc,
					depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

				dsDesc.DepthEnable = true;
				dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
				dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
				dsDesc.StencilEnable = false;

				GetDevice()->CreateDepthStencilState(&dsDesc,
					depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

				dsDesc.DepthEnable = false;
				dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
				dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
				dsDesc.StencilEnable = false;

				GetDevice()->CreateDepthStencilState(&dsDesc,
					depthStencilStates[(UINT)eDSType::None].GetAddressOf());
		#pragma endregion

		#pragma region BlendState
				blendStates[(UINT)eBSType::Default] = nullptr;

				D3D11_BLEND_DESC bsDesc = {};
				bsDesc.AlphaToCoverageEnable = false;
				bsDesc.IndependentBlendEnable = false;
				bsDesc.RenderTarget[0].BlendEnable = true;
				bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
				bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
				bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
				bsDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
				bsDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
				bsDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

				bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

				GetDevice()->CreateBlendState(&bsDesc,
					blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

				bsDesc.AlphaToCoverageEnable = false;
				bsDesc.IndependentBlendEnable = false;
				bsDesc.RenderTarget[0].BlendEnable = true;
				bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
				bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
				bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

				bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

				GetDevice()->CreateBlendState(&bsDesc,
					blendStates[(UINT)eBSType::OneOne].GetAddressOf());
		#pragma endregion
	}

	void LoadBuffer()
	{
		#pragma region CONSTANT BUFFER
				constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
				constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

				constantBuffers[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
				constantBuffers[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

				constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
				constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

				constantBuffers[(UINT)eCBType::Fade] = new ConstantBuffer(eCBType::Fade);
				constantBuffers[(UINT)eCBType::Fade]->Create(sizeof(FadeCB));

				constantBuffers[(UINT)eCBType::Animation] = new ConstantBuffer(eCBType::Animation);
				constantBuffers[(UINT)eCBType::Animation]->Create(sizeof(AnimationCB));

				constantBuffers[(UINT)eCBType::Light] = new ConstantBuffer(eCBType::Light);
				constantBuffers[(UINT)eCBType::Light]->Create(sizeof(LightCB));

				constantBuffers[(UINT)eCBType::ParticleSystem] = new ConstantBuffer(eCBType::ParticleSystem);
				constantBuffers[(UINT)eCBType::ParticleSystem]->Create(sizeof(ParticleSystemCB));

				constantBuffers[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
				constantBuffers[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));
		#pragma endregion
		#pragma region STRUCTURED BUFFER
				lightsBuffer = new StructedBuffer();
				lightsBuffer->Create(sizeof(LightAttribute), 128, eSRVType::SRV, nullptr, true);
		#pragma endregion
	}

	void LoadTexture()
	{
		#pragma region STATIC TEXTURE
				Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
				Resources::Load<Texture>(L"DefaultSprite", L"Light.png");
				Resources::Load<Texture>(L"HPBarTexture", L"HPBar.png");
				Resources::Load<Texture>(L"CartoonSmoke", L"particle\\CartoonSmoke.png");
				Resources::Load<Texture>(L"Noise_01", L"noise\\noise_01.png");
				Resources::Load<Texture>(L"Noise_02", L"noise\\noise_02.png");
		#pragma endregion
		#pragma region DYNAMIC TEXTURE
				std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
				uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM,
					D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
				Resources::Insert<Texture>(L"PaintTexture", uavTexture);
		#pragma endregion
		#pragma region STATIC TEXTURE(PORTFOLIO)
				// MainTitle
				Resources::Load<Texture>(L"MainBackground", L"Portfolio\\title_back.png");
				Resources::Load<Texture>(L"SelectBackground", L"Portfolio\\title_select_bg.png");
				Resources::Load<Texture>(L"MainTitle", L"Portfolio\\titlek.png");
				Resources::Load<Texture>(L"MainCopy", L"Portfolio\\copy.png");
				Resources::Load<Texture>(L"SelectButton", L"Portfolio\\select_button.png");
				Resources::Load<Texture>(L"ButtonSelectFrame", L"Portfolio\\button_select_frame.png");

				// Titles
				Resources::Load<Texture>(L"gs1Title", L"Portfolio\\titlegs1k.png");
				Resources::Load<Texture>(L"gs1Copy", L"Portfolio\\copygs1.png");

				// Episodes
				Resources::Load<Texture>(L"ep1Image", L"Portfolio\\storygs1 #2074.png");
				Resources::Load<Texture>(L"ep1Text", L"Portfolio\\title_textgs1k.png");
				Resources::Load<Texture>(L"EpisodeFrame", L"Portfolio\\episode_select_frame.png");

				// Text
				Resources::Load<Texture>(L"TextBackground", L"Portfolio\\talk_bg.png");
				Resources::Load<Texture>(L"TextArrow", L"Portfolio\\select_arrow.png");

				// Court Backgrounds
				Resources::Load<Texture>(L"WaitingRoom", L"Portfolio\\Backgrounds\\bg002.png");
				Resources::Load<Texture>(L"Court", L"Portfolio\\Backgrounds\\Court.png");
				Resources::Load<Texture>(L"Desk1", L"Portfolio\\Backgrounds\\etc22.png");
				Resources::Load<Texture>(L"Desk2", L"Portfolio\\Backgrounds\\etc21.png");
				Resources::Load<Texture>(L"Desk3", L"Portfolio\\Backgrounds\\etc20.png");
				Resources::Load<Texture>(L"WholeCourt", L"Portfolio\\Backgrounds\\bg006.png");
				Resources::Load<Texture>(L"SupportBack", L"Portfolio\\Backgrounds\\bg007.png");
				Resources::Load<Texture>(L"JudgeBack", L"Portfolio\\Backgrounds\\bg008.png");
		#pragma endregion
	}

	void LoadMaterial()
	{
#pragma region DEFAULT
		std::shared_ptr<Texture> defaultTexture = Resources::Find<Texture>(L"PaintTexture");
		std::shared_ptr<Shader> defaultShader = Resources::Find<Shader>(L"RectShader");
		std::shared_ptr<Material> defaultMaterial = std::make_shared<Material>();
		defaultMaterial->SetShader(defaultShader);
		defaultMaterial->SetTexture(eTextureSlot::T0, defaultTexture);
		Resources::Insert<Material>(L"RectMaterial", defaultMaterial);
#pragma endregion
#pragma region SPRITE
		std::shared_ptr<Texture> spriteTexture = Resources::Find<Texture>(L"DefaultSprite");
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
		spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
		spriteMaterial->SetShader(spriteShader);
		spriteMaterial->SetTexture(eTextureSlot::T0, spriteTexture);
		Resources::Insert<Material>(L"SpriteMaterial", spriteMaterial);
#pragma endregion
#pragma region UI
		std::shared_ptr<Texture> uiTexture = Resources::Find<Texture>(L"HPBarTexture");
		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
		uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		uiMaterial->SetShader(uiShader);
		uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
		Resources::Insert<Material>(L"UIMaterial", uiMaterial);
#pragma endregion
#pragma region GRID
		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		std::shared_ptr<Material> gridMaterial = std::make_shared<Material>();
		gridMaterial->SetShader(gridShader);
		Resources::Insert<Material>(L"GridMaterial", gridMaterial);
#pragma endregion
#pragma region FADE
		std::shared_ptr<Shader> fadeShader = Resources::Find<Shader>(L"FadeShader");
		std::shared_ptr<Material> fadeMaterial = std::make_shared<Material>();
		fadeMaterial->SetRenderingMode(eRenderingMode::Transparent);
		fadeMaterial->SetShader(fadeShader);
		Resources::Insert<Material>(L"FadeMaterial", fadeMaterial);
#pragma endregion
#pragma region DEBUG
		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		std::shared_ptr<Material> debugMaterial = std::make_shared<Material>();
		debugMaterial->SetRenderingMode(eRenderingMode::Transparent);
		debugMaterial->SetShader(debugShader);
		Resources::Insert<Material>(L"DebugMaterial", debugMaterial);
#pragma endregion
#pragma region PARTICLE
		std::shared_ptr<Shader> particleShader = Resources::Find<Shader>(L"ParticleShader");
		std::shared_ptr<Material> particleMaterial = std::make_shared<Material>();
		particleMaterial->SetRenderingMode(eRenderingMode::Transparent);
		particleMaterial->SetShader(particleShader);
		Resources::Insert<Material>(L"ParticleMaterial", particleMaterial);
#pragma endregion
#pragma region BASIC
		std::shared_ptr<Shader> basicShader = Resources::Find<Shader>(L"BasicShader");
		std::shared_ptr<Material> basicMaterial = std::make_shared<Material>();
		basicMaterial->SetRenderingMode(eRenderingMode::Transparent);
		basicMaterial->SetShader(basicShader);
		Resources::Insert<Material>(L"BasicMaterial", basicMaterial);
#pragma endregion

#pragma region Portfolio
		// Main
		{
			// Background
			std::shared_ptr<Texture> mbTexture = Resources::Find<Texture>(L"MainBackground");
			std::shared_ptr<Material> mbMaterial = std::make_shared<Material>();
			mbMaterial->SetRenderingMode(eRenderingMode::Transparent);
			mbMaterial->SetShader(uiShader);
			mbMaterial->SetTexture(eTextureSlot::T0, mbTexture);
			Resources::Insert<Material>(L"MBMaterial", mbMaterial);

			// Select Background
			std::shared_ptr<Texture> sbTexture = Resources::Find<Texture>(L"SelectBackground");
			std::shared_ptr<Material> sbMaterial = std::make_shared<Material>();
			sbMaterial->SetRenderingMode(eRenderingMode::Transparent);
			sbMaterial->SetShader(uiShader);
			sbMaterial->SetTexture(eTextureSlot::T0, sbTexture);
			Resources::Insert<Material>(L"SBMaterial", sbMaterial);

			// Title
			std::shared_ptr<Texture> mtTexture = Resources::Find<Texture>(L"MainTitle");
			std::shared_ptr<Material> mtMaterial = std::make_shared<Material>();
			mtMaterial->SetRenderingMode(eRenderingMode::Transparent);
			mtMaterial->SetShader(uiShader);
			mtMaterial->SetTexture(eTextureSlot::T0, mtTexture);
			Resources::Insert<Material>(L"MTMaterial", mtMaterial);

			// Copy
			std::shared_ptr<Texture> mcTexture = Resources::Find<Texture>(L"MainCopy");
			std::shared_ptr<Material> mcMaterial = std::make_shared<Material>();
			mcMaterial->SetRenderingMode(eRenderingMode::Transparent);
			mcMaterial->SetShader(uiShader);
			mcMaterial->SetTexture(eTextureSlot::T0, mcTexture);
			Resources::Insert<Material>(L"MCMaterial", mcMaterial);

			// Button
			std::shared_ptr<Texture> sbtnTexture = Resources::Find<Texture>(L"SelectButton");
			std::shared_ptr<Material> sbtnMaterial = std::make_shared<Material>();
			sbtnMaterial->SetRenderingMode(eRenderingMode::Transparent);
			sbtnMaterial->SetShader(uiShader);
			sbtnMaterial->SetTexture(eTextureSlot::T0, sbtnTexture);
			Resources::Insert<Material>(L"SBTNMaterial", sbtnMaterial);

			// ButtonFrame
			std::shared_ptr<Texture> bsfTexture = Resources::Find<Texture>(L"ButtonSelectFrame");
			std::shared_ptr<Material> bsfMaterial = std::make_shared<Material>();
			bsfMaterial->SetRenderingMode(eRenderingMode::Transparent);
			bsfMaterial->SetShader(uiShader);
			bsfMaterial->SetTexture(eTextureSlot::T0, bsfTexture);
			Resources::Insert<Material>(L"BSFMaterial", bsfMaterial);

			// TextBackground
			std::shared_ptr<Texture> tbTexture = Resources::Find<Texture>(L"TextBackground");
			std::shared_ptr<Material> tbMaterial = std::make_shared<Material>();
			tbMaterial->SetRenderingMode(eRenderingMode::Transparent);
			tbMaterial->SetShader(uiShader);
			tbMaterial->SetTexture(eTextureSlot::T0, tbTexture);
			Resources::Insert<Material>(L"TBMaterial", tbMaterial);

			// TextArrow
			std::shared_ptr<Texture> taTexture = Resources::Find<Texture>(L"TextArrow");
			std::shared_ptr<Material> taMaterial = std::make_shared<Material>();
			taMaterial->SetRenderingMode(eRenderingMode::Transparent);
			taMaterial->SetShader(uiShader);
			taMaterial->SetTexture(eTextureSlot::T0, taTexture);
			Resources::Insert<Material>(L"TAMaterial", taMaterial);
		}
		//GS1
		{
			// Title
			std::shared_ptr<Texture> gs1tTexture = Resources::Find<Texture>(L"gs1Title");
			std::shared_ptr<Material> gs1tMaterial = std::make_shared<Material>();
			gs1tMaterial->SetRenderingMode(eRenderingMode::Transparent);
			gs1tMaterial->SetShader(uiShader);
			gs1tMaterial->SetTexture(eTextureSlot::T0, gs1tTexture);
			Resources::Insert<Material>(L"GS1TMaterial", gs1tMaterial);

			// Copy
			std::shared_ptr<Texture> gs1cTexture = Resources::Find<Texture>(L"gs1Copy");
			std::shared_ptr<Material> gs1cMaterial = std::make_shared<Material>();
			gs1cMaterial->SetRenderingMode(eRenderingMode::Transparent);
			gs1cMaterial->SetShader(uiShader);
			gs1cMaterial->SetTexture(eTextureSlot::T0, gs1cTexture);
			Resources::Insert<Material>(L"GS1CMaterial", gs1cMaterial);

			// Episodes
			std::shared_ptr<Texture> episodeSelectFrameTexture = Resources::Find<Texture>(L"EpisodeFrame");
			std::shared_ptr<Material> episodeSelectFrameMaterial = std::make_shared<Material>();
			episodeSelectFrameMaterial->SetRenderingMode(eRenderingMode::Transparent);
			episodeSelectFrameMaterial->SetShader(uiShader);
			episodeSelectFrameMaterial->SetTexture(eTextureSlot::T0, episodeSelectFrameTexture);
			Resources::Insert<Material>(L"ESFMaterial", episodeSelectFrameMaterial);

			std::shared_ptr<Texture> ep1iTexture = Resources::Find<Texture>(L"ep1Image");
			std::shared_ptr<Material> ep1iMaterial = std::make_shared<Material>();
			ep1iMaterial->SetRenderingMode(eRenderingMode::Transparent);
			ep1iMaterial->SetShader(uiShader);
			ep1iMaterial->SetTexture(eTextureSlot::T0, ep1iTexture);
			Resources::Insert<Material>(L"EP1IMaterial", ep1iMaterial);

			std::shared_ptr<Texture> ep1tTexture = Resources::Find<Texture>(L"ep1Text");
			std::shared_ptr<Material> ep1tMaterial = std::make_shared<Material>();
			ep1tMaterial->SetRenderingMode(eRenderingMode::Transparent);
			ep1tMaterial->SetShader(uiShader);
			ep1tMaterial->SetTexture(eTextureSlot::T0, ep1tTexture);
			Resources::Insert<Material>(L"EP1TMaterial", ep1tMaterial);

			// Waiting Room
			std::shared_ptr<Texture> wrTexture = Resources::Find<Texture>(L"WaitingRoom");
			std::shared_ptr<Material> wrMaterial = std::make_shared<Material>();
			wrMaterial->SetRenderingMode(eRenderingMode::Opaque);
			wrMaterial->SetShader(uiShader);
			wrMaterial->SetTexture(eTextureSlot::T0, wrTexture);
			Resources::Insert<Material>(L"WaitingRoomMaterial", wrMaterial);

			// Court
			std::shared_ptr<Texture> courtTexture = Resources::Find<Texture>(L"Court");
			std::shared_ptr<Material> courtMaterial = std::make_shared<Material>();
			courtMaterial->SetRenderingMode(eRenderingMode::Opaque);
			courtMaterial->SetShader(uiShader);
			courtMaterial->SetTexture(eTextureSlot::T0, courtTexture);
			Resources::Insert<Material>(L"CourtMaterial", courtMaterial);

			std::shared_ptr<Texture> judgeBackTexture = Resources::Find<Texture>(L"JudgeBack");
			std::shared_ptr<Material> judgeBackMaterial = std::make_shared<Material>();
			judgeBackMaterial->SetRenderingMode(eRenderingMode::Opaque);
			judgeBackMaterial->SetShader(uiShader);
			judgeBackMaterial->SetTexture(eTextureSlot::T0, judgeBackTexture);
			Resources::Insert<Material>(L"JudgeBackMaterial", judgeBackMaterial);

			std::shared_ptr<Texture> desk1Texture = Resources::Find<Texture>(L"Desk1");
			std::shared_ptr<Material> desk1Material = std::make_shared<Material>();
			desk1Material->SetRenderingMode(eRenderingMode::Transparent);
			desk1Material->SetShader(uiShader);
			desk1Material->SetTexture(eTextureSlot::T0, desk1Texture);
			Resources::Insert<Material>(L"Desk1Material", desk1Material);

			std::shared_ptr<Texture> desk2Texture = Resources::Find<Texture>(L"Desk2");
			std::shared_ptr<Material> desk2Material = std::make_shared<Material>();
			desk2Material->SetRenderingMode(eRenderingMode::Transparent);
			desk2Material->SetShader(uiShader);
			desk2Material->SetTexture(eTextureSlot::T0, desk2Texture);
			Resources::Insert<Material>(L"Desk2Material", desk2Material);

			std::shared_ptr<Texture> desk3Texture = Resources::Find<Texture>(L"Desk3");
			std::shared_ptr<Material> desk3Material = std::make_shared<Material>();
			desk3Material->SetRenderingMode(eRenderingMode::Transparent);
			desk3Material->SetShader(uiShader);
			desk3Material->SetTexture(eTextureSlot::T0, desk3Texture);
			Resources::Insert<Material>(L"Desk3Material", desk3Material);
		}
#pragma endregion
	}

	void Initialize()
	{
		LoadMesh();
		LoadShader();
		SetUpState();
		LoadBuffer();
		LoadTexture();
		LoadMaterial();
	}

	void Render()
	{
		BindNoiseTexture();
		BindLights();

		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		for (Camera* cam : cameras[(UINT)type])
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras[(UINT)type].clear();
		renderer::lights.clear();
	}

	void Release()
	{
		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i];
			constantBuffers[i] = nullptr;
		}

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}

	void PushLightAttribute(LightAttribute lightAttribute)
	{
		lights.push_back(lightAttribute);
	}

	void BindLights()
	{
		lightsBuffer->SetData(lights.data(), lights.size());
		lightsBuffer->BindSRV(eShaderStage::VS, 13);
		lightsBuffer->BindSRV(eShaderStage::PS, 13);

		renderer::LightCB trCB = {};
		trCB.numberOfLight = lights.size();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Light];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

	void BindNoiseTexture()
	{
		std::shared_ptr<Texture> noise = Resources::Find<Texture>(L"Noise_01");
		noise->BindShaderResource(eShaderStage::VS, 16);
		noise->BindShaderResource(eShaderStage::HS, 16);
		noise->BindShaderResource(eShaderStage::DS, 16);
		noise->BindShaderResource(eShaderStage::GS, 16);
		noise->BindShaderResource(eShaderStage::PS, 16);
		noise->BindShaderResource(eShaderStage::CS, 16);

		NoiseCB info = {};
		info.noiseSize.x = noise->GetWidth();
		info.noiseSize.y = noise->GetHeight();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Noise];
		cb->SetData(&info);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}
}

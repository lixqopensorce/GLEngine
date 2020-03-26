#pragma once
using Microsoft::WRL::ComPtr;
using namespace DirectX;

class Device
{
public:
	Device(UINT width, UINT height, std::wstring name);

	~Device() {}
	
	//TODO::模型单独拆分出去
	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

	void OnInit();
	void OnUpdate() {}
	void OnRender();
	void OnDestroy() {
		WaitForPreviousFrame();
		CloseHandle(m_fenceEvent);
	}

	//key event
	void OnKeyDown(UINT8 keyCode){}
	void OnKeyUp(UINT8 keyCode) {}

	UINT GetWidth() const { return m_width; }
	UINT GetHeight() const { return m_height; }
	std::wstring GetWindowTitle() const { return m_windowTitle; }

	std::wstring GetAssetFullPath(LPCWSTR assetName){ return m_assetsPath + assetName; }
private:
	void InitPipeLine();
	void LoadAsset();
private:
	UINT m_width;
	UINT m_height;
	std::wstring m_windowTitle;
	float m_aspectRatio;
	std::wstring m_assetsPath;
	CD3DX12_VIEWPORT m_viewport;
	CD3DX12_RECT m_scissorRect;

	ComPtr<ID3D12Device> m_device;
	ComPtr<ID3D12CommandQueue> m_commandQueue;
	ComPtr<ID3D12CommandAllocator> m_commandAllocator;
	ComPtr<ID3D12GraphicsCommandList> m_commandList;
	ComPtr<IDXGISwapChain3> m_swapChain;
	ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
	ComPtr<ID3D12RootSignature> m_rootSignature;
	ComPtr<ID3D12PipelineState> m_pipeState;
	ComPtr<ID3D12Resource> m_vertexBuffer;
	//顶点视图
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

	ComPtr<ID3D12Fence> m_fence;
	HANDLE m_fenceEvent;
	DWORD m_fenceValue;

	//rtv资源
	static const int m_frameCount = 2;
	ComPtr<ID3D12Resource> m_renderTarget[m_frameCount];
	int m_rtvDiscriptroSize;
	int m_frameIndex = 0;

	void WaitForPreviousFrame();
};


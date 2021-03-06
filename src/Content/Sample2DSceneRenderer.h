﻿#pragma once

#include "..\Common\DeviceResources.h"
#include "..\Common\StepTimer.h"

namespace Hello2D
{
	// This sample renderer instantiates a basic rendering pipeline.
	class Sample2DSceneRenderer
	{
	public:
		Sample2DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
		void ReleaseDeviceDependentResources();
		void Update(DX::StepTimer const& timer);
		void Render();
		void StartTracking();
		void TrackingUpdate(float positionX);
		void StopTracking();
		bool IsTracking() { return m_tracking; }

		void Zoom(bool zoomIn);
		void ToggleRenderingMode();
		void ToggleFeathering();

	private:
		void MakeScenery();
		void MakeLeftMountain();
		void MakeRightMountain();
		void MakeSun();
		void MakeRiver();
		void MakePhotoFrame();

		void RenderScene(ID2D1DeviceContext2 *context);
		void DrawPhotoFrame(ID2D1DeviceContext2 *context);
		void CacheRendering();

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources>             m_deviceResources;
														 
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>     m_solidBrush;
		Microsoft::WRL::ComPtr<ID2D1RadialGradientBrush> m_radialGradBrush;
														 
		Microsoft::WRL::ComPtr<ID2D1PathGeometry>        m_pathLeftMountain;
		Microsoft::WRL::ComPtr<ID2D1PathGeometry>        m_pathRightMountain;
		Microsoft::WRL::ComPtr<ID2D1PathGeometry>        m_pathSun;
		Microsoft::WRL::ComPtr<ID2D1PathGeometry>        m_pathRiver;
		Microsoft::WRL::ComPtr<ID2D1PathGeometry>        m_pathPhotoFrame;
		
		Microsoft::WRL::ComPtr<ID2D1Layer>               m_clipLayer;

		Microsoft::WRL::ComPtr<ID2D1Bitmap>              m_sceneBitmap;
		Microsoft::WRL::ComPtr<ID2D1Bitmap>              m_maskBitmap;
		Microsoft::WRL::ComPtr<ID2D1BitmapBrush>         m_bitmapBrush;

		enum class RenderingMode
		{
			Vector,
			Raster
		}                                                m_renderingMode = RenderingMode::Vector;
		float                                            m_scaleFactor = 1.0f;

		// Variables used with the rendering loop.		 
		bool	                                         m_loadingComplete;
		bool	                                         m_tracking;
		bool                                             m_rasterized = false;
		enum class FeatheringMode
		{
			Off,
			On,
			Alpha
		}                                                m_feathering = FeatheringMode::Off;

		constexpr static auto                            m_sunRadius = 85.0f;
		constexpr static D2D1_POINT_2F                   m_sunCenter { 355.0f, 255.0f };
		constexpr static auto                            m_scaleDelta = 0.1f;
	};
}


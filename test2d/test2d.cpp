#include <windows.h>  
#include <d2d1.h>  
#include <d2d1helper.h>  
#include <dwrite.h>  
#pragma comment(lib, "dwrite.lib")  
#pragma comment(lib, "d2d1.lib")  

#include <Gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

#include <wincodec.h>  

#include "D2dWrap.h"

D2dEngine	*_e;

HINSTANCE g_hinst;  
HWND g_hwnd;  

//ID2D1Factory * g_factory;  
//ID2D1HwndRenderTarget * g_render_target;  
//ID2D1SolidColorBrush  * g_brush;  
//
//IDWriteFactory * g_write_factory;  
//IDWriteTextFormat * g_text_format;  
//
//ID2D1GradientStopCollection * g_gradient_stop_collection;  
//ID2D1LinearGradientBrush  * g_linear_gradient_brush;  
//ID2D1RadialGradientBrush * g_radial_gradient_brush;  
//
//IWICImagingFactory * g_image_factory = NULL;  
//ID2D1Bitmap * g_bitmap = NULL;  
//ID2D1Bitmap * g_bitmap2 = NULL;  

//D2dWrap		dw;


void BitmapToBuffer( LPBYTE pData, Bitmap *pBitmap, int cx, int cy )
{
	BitmapData	bmpData;
	Rect		rt( 0, 0, cx, cy );

	pBitmap->LockBits(	&rt, 
		ImageLockModeRead|ImageLockModeWrite,
		PixelFormat24bppRGB,
		&bmpData );

	LPBYTE		lp = (LPBYTE)bmpData.Scan0;
	int			imageSize = cx*cy*3;

	memcpy( pData, lp, imageSize );
	pBitmap->UnlockBits( &bmpData );
}

bool AppInit()  
{  
	//CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);


	//D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_factory);  

	//RECT rc;  
	//GetClientRect(g_hwnd, &rc);  

	//g_factory->CreateHwndRenderTarget(  
	//	D2D1::RenderTargetProperties(),  
	//	D2D1::HwndRenderTargetProperties(g_hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)    ),  
	//	&g_render_target);  

	//g_render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::WhiteSmoke), &g_brush);  

	//// Init Font  
	//DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(g_write_factory),reinterpret_cast<IUnknown **>(&g_write_factory));  
	//g_write_factory->CreateTextFormat(L"Arial", NULL, DWRITE_FONT_WEIGHT_NORMAL,  
	//	DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 40, L"",&g_text_format);  


	//// Create Gradient Stops  
	//D2D1_GRADIENT_STOP gradient_stops[3];  
	//gradient_stops[0].color = D2D1::ColorF(D2D1::ColorF::LightGreen);  
	//gradient_stops[0].position = 0.0f;  
	//gradient_stops[1].color = D2D1::ColorF(D2D1::ColorF::DarkGreen);  
	//gradient_stops[1].position = 0.5f;  
	//gradient_stops[2].color = D2D1::ColorF(D2D1::ColorF::Green);  
	//gradient_stops[2].position = 1.0f;  

	//// Create Interface  
	//g_render_target->CreateGradientStopCollection(gradient_stops, 3, &g_gradient_stop_collection);  

	//// Create Linear Gradient Brush  
	//g_render_target->CreateLinearGradientBrush(  
	//	D2D1::LinearGradientBrushProperties(D2D1::Point2F(0,0), D2D1::Point2F(600,600)),   
	//	g_gradient_stop_collection, &g_linear_gradient_brush);  

	//g_render_target->CreateRadialGradientBrush(  
	//	D2D1::RadialGradientBrushProperties(D2D1::Point2F(500,500),D2D1::Point2F(),1000.0f,1000.0f),  
	//	g_gradient_stop_collection,&g_radial_gradient_brush);  

	//// Initialize Image Factory  
	//CoCreateInstance(CLSID_WICImagingFactory,NULL,CLSCTX_INPROC_SERVER,__uuidof(g_image_factory),(LPVOID*)&g_image_factory);  

	//IWICBitmapDecoder *bitmapdecoder = NULL;  
	//g_image_factory->CreateDecoderFromFilename(L"f:\\c.jpg",NULL,GENERIC_READ,WICDecodeMetadataCacheOnDemand,&bitmapdecoder);//  

	//IWICBitmapFrameDecode  *pframe = NULL;  
	//bitmapdecoder->GetFrame(0,&pframe);  

	//IWICFormatConverter * fmtcovter = NULL;  
	//g_image_factory->CreateFormatConverter(&fmtcovter);  
	//fmtcovter->Initialize(pframe,GUID_WICPixelFormat32bppPBGRA,WICBitmapDitherTypeNone,NULL,0.0f,WICBitmapPaletteTypeCustom);  
	//g_render_target->CreateBitmapFromWicBitmap(fmtcovter, NULL, &g_bitmap);

	////HGLOBAL m_hGlobal = GlobalAlloc( GMEM_MOVEABLE, 1000000 );
	////LPBYTE	m_lpBuf = (LPBYTE)GlobalLock( m_hGlobal );

	////Bitmap	bmp( L"f:\\其它应用.png" );
	////int w = bmp.GetWidth();
	////int h = bmp.GetHeight();
	////BitmapToBuffer( m_lpBuf, &bmp, w, h );

	////D2D1_SIZE_U		d2size = {w,h};
	////D2D1_BITMAP_PROPERTIES		dbp;
	////dbp.dpiX = 100;
	////dbp.dpiY = 100;
	////dbp.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED);
	//////dbp.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_B8G8R8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED);

	////g_render_target->CreateBitmap( d2size, m_lpBuf, w*4, dbp, &g_bitmap2 );

	////GlobalUnlock( m_hGlobal );
	////GlobalFree( m_hGlobal );

	//fmtcovter->Release();  
	//pframe->Release();  
	//bitmapdecoder->Release();  

	return true;  
}  

void OnSize(LPARAM lparam)  
{  
	//if(g_render_target)  
	//	g_render_target->Resize(D2D1::SizeU(LOWORD(lparam),HIWORD(lparam)));  

	//dw.resize( LOWORD(lparam), HIWORD(lparam) );
	_e->d2Resize( LOWORD(lparam), HIWORD(lparam) );
}  


class CWin32Drawer : public IDrawer
{
public:
	void DoDraw()
	{
		float	w, h;
		_e->d2GetSize( w, h );

		ID2D1Bitmap *bmp = _e->d2NewBitmap( L"f:\\c.jpg" );
		_e->d2DrawBitmap( bmp, 0, 0, 500, 400, 1.f );
		_e->d2_safe_release( bmp );

		ID2D1SolidColorBrush *sb = _e->d2NewSolidBrush( D2D1::ColorF(RGB(0,0,255)) );
		IDWriteTextFormat *ft = _e->d2NewFont( L"宋体", 40, 700 );
		_e->d2DrawText( L"中华人民共和国", 100, 100, 400, 40, ft, sb );

		_e->d2_safe_release( ft );
		_e->d2_safe_release( sb );

		_e->TestGDIPlus();

		//ID2D1Bitmap *bmp2 = _e->d2NewBitmap( L"f:\\123.bmp");
		//_e->d2DrawBitmap( bmp2, 100, 100, 100, 100, 0.5f );

		//_e->d2_safe_release( bmp2 );
	}
};


CWin32Drawer _w32Drawer;

void OnPaint( HWND hwnd )  
{  
	//bool bContinue = dw.draw();
	//if( !bContinue )

	{

		//_e->_render_target->BeginDraw();
		//ID2D1Bitmap *bmp = _e->d2NewBitmap( L"f:\\c.jpg" );
		//_e->d2DrawBitmap( bmp, 0, 0, 400, 300, 0.9f );
		//_e->d2_safe_release( bmp );
		//_e->_render_target->EndDraw();
		_e->d2Draw( &_w32Drawer );
	}



	{
		PAINTSTRUCT ps = { 0 };
		HDC hdc = ::BeginPaint(hwnd, &ps);
		::EndPaint(hwnd, &ps);
	}

	//OutputDebugString( L"OnPaint\n" );
	//if(!g_render_target)  
	//	return;

	//g_render_target->BeginDraw();  

	//// Clear Background  
	//g_render_target->Clear(D2D1::ColorF(0.63, 0.84, 0.00));   

	////// Draw Ellipse    
	//D2D1_SIZE_F size = g_render_target->GetSize();    
	////D2D1_RECT_F r = {0, 0, size.width, size.height};  
	////g_render_target->FillRectangle(&r, g_linear_gradient_brush);   
	//////g_render_target->FillRectangle(&ellipse, g_linear_gradient_brush);   

	//// Draw Image  
	//D2D1_RECT_F imgr = {0, 0, size.width/2, size.height/2};  
	////g_render_target->DrawBitmap(g_bitmap, imgr, rand()*1.f/RAND_MAX);  
	//g_render_target->DrawBitmap(g_bitmap, imgr); 

	////D2D1_RECT_F imgr2 = {100, 100, 200, 200};  
	//////g_render_target->DrawBitmap(g_bitmap, imgr, rand()*1.f/RAND_MAX);  
	////g_render_target->DrawBitmap(g_bitmap2, imgr2);

	//// Draw Text   
	//const wchar_t * text = L"Direct2D Draw Image";  
	//g_render_target->DrawText(text, wcslen(text),  
	//  g_text_format,  
	//  D2D1::RectF(100, 190, size.width, size.height),  
	//  g_brush);  

	//g_render_target->EndDraw();  

	////PAINTSTRUCT ps = { 0 };
	////HDC hdc = ::BeginPaint(hwnd, &ps);
	//////LineTo( hdc, 400, 300 );
	////::EndPaint(hwnd, &ps);
}  

void OnDestroy()  
{  
	//g_bitmap->Release(); 
	////g_bitmap2->Release(); 
	//g_image_factory->Release();  

	//g_linear_gradient_brush->Release();  
	//g_radial_gradient_brush->Release();  
	//g_gradient_stop_collection->Release();  
	//g_text_format->Release();  
	//g_write_factory->Release();  
	//g_brush->Release();  
	//g_render_target->Release();  
	//g_factory->Release();  
}  

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)   
{  
	switch(msg)   
	{    
	case WM_PAINT:  
		{
			OnPaint( hwnd );
		}

		break;  

	case WM_SIZE:  
		OnSize(lparam);
		InvalidateRect( hwnd, NULL, FALSE );
		break;

	case WM_LBUTTONDOWN:
		//dw.reset();
		InvalidateRect( hwnd, NULL, FALSE );
		break;

	case WM_DESTROY:   
		OnDestroy();  
		PostQuitMessage(0);  
		break;  

	default:  
		return DefWindowProc(hwnd, msg, wparam, lparam);  
	}  
	return 0;  
}  

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)   
{  
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	ULONG_PTR token;
	GdiplusStartupInput gsi;
	::GdiplusStartup(&token, &gsi, NULL);

	_e = new D2dEngine;
	_e->d2Startup();

	WNDCLASSEX wc;    
	MSG msg;    

	memset(&wc,0,sizeof(wc));  
	wc.cbSize = sizeof(WNDCLASSEX);  
	wc.lpfnWndProc = WndProc;   
	wc.hInstance = hinst;  
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);  
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);  
	wc.lpszClassName = L"WindowClass";  
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);    
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);   

	if(!RegisterClassEx(&wc))   
	{  
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",MB_ICONEXCLAMATION|MB_OK);  
		return 0;  
	}  

	g_hinst = hinst;  

	g_hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,L"WindowClass",L"Direct2D Demo",WS_VISIBLE|WS_OVERLAPPEDWINDOW,  
		CW_USEDEFAULT,   
		CW_USEDEFAULT,   
		640,   
		480,   
		NULL, NULL, hinst, NULL);  

	if(g_hwnd == NULL)   
	{  
		MessageBox(NULL, L"Window Creation Failed!", L"Error!",MB_ICONEXCLAMATION|MB_OK);  
		return 0;  
	}  

	//if(!AppInit())   
	//if( !dw.InitD2d( g_hwnd ) )
	if( !_e->d2InitHRT( g_hwnd ) )
	{  
		MessageBox(NULL, L"Application Initialisation Failed !", L"Error",MB_ICONEXCLAMATION|MB_OK);  
		return 0;  
	}



	while(GetMessage(&msg, NULL, 0, 0) > 0)   
	{    
		TranslateMessage(&msg);    
		DispatchMessage(&msg);   
	}  

	delete _e;
	_e = NULL;

	::GdiplusShutdown(token);
	return msg.wParam;  
} 
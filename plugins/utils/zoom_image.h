#pragma once
//#include "util.h"
#include "log.h"
#include <windows.h>

static const std::wstring kImageJPEG = L"image/jpeg";
static const std::wstring kImagePNG  = L"image/png";
static const std::wstring kImageBMP  = L"image/bmp";
static const std::wstring kImageGIF  = L"image/gif";


class ZoomImage
{
public:
	ZoomImage(void);
	~ZoomImage(void);
	//�������ź��ͼƬ����·��
	void SetImagePath(const std::wstring &image_path);
	//����Ϊ�Զ�����ģʽ
	void SetAutoZoom(bool area_zoom,int auto_max_with,int auto_max_height);
	//����Ϊ�̶���С����ģʽ
	void SetSize(int width,int height);
	//����Ϊ����������ģʽ
	void SetRatio(float ratio);
	
	/*
	 *	@brief ����ĳһ��ͼƬ�������浽Ϊָ����ʽ
	 *	@param filepath:Ҫ���ŵ�ԴͼƬ·��
	 *	@param mime_type:�����ͼƬ����
	 */
	bool Zoom(const std::wstring& filepath,std::wstring mime_type=L"image/jpeg");
	//��ͼƬ����Ϊָ�����ͣ���������ͼƬ
	bool ConvertImageFormat(std::wstring& filepath, std::wstring mime_type);
	//��ȡͼ��ķ�ת����
	static Gdiplus::RotateFlipType GetRotateFlipType(Gdiplus::Image& image);
	static std::wstring GetMimeType(const std::wstring& filepath);
	static void GetMimeType(const std::wstring& filepath, std::wstring& mime_type_out, std::wstring& exten_out);
	/*
	*	@brief ��width��height�ı�������ȡԴͼƬ��ͬ���������Χ��ͼƬ���֣������浽Ϊָ����ʽ
	*	@param filepath:ԴͼƬ·��
	*	@param image_path_out:���ͼƬ·��
	*	@param width:Ҫ���ŵ�ԴͼƬ·��
	*	@param height:Ҫ���ŵ�ԴͼƬ·��
	*	@param mime_type:�����ͼƬ����
	*/
	static bool SavePaddingImage(const std::wstring& image_path, const std::wstring& image_path_out, int width, int height, std::wstring mime_type = L"image/jpeg");

protected:
	//�ж��Ƿ���Ҫ��������
	bool IsNeedZoom(int width,int height);
	//�������ź�Ĵ�С��������浽width_��height_
	bool CalculateSize(int width_src,int height_src);
	static bool GetImageCLSID(const wchar_t* format, CLSID* pCLSID);
	static bool SaveImage(Gdiplus::Image& image, const std::wstring& file_path,std::wstring mime_type,long quality_num = 95);
	static Gdiplus::RotateFlipType GetRotateFlipType(short orientation);
	static std::wstring GetMimeType(GUID& clsid);

private:
	enum ZoomType
	{
		by_fixed_size = 0,
		by_ratio,
		by_auto,by_none
	};//by_fixed_size:���̶��ߴ�,by_ratio:����������;

	std::wstring file_path_save_;
	ZoomType zoom_type_;

	bool area_zoom_; //�Ƿ��������width*height;
	int auto_max_width_;
	int auto_max_height_;

	int width_;
	int height_;

	float ratio_;

	std::wstring image_path_;
};

//����ͼ������max_width * max_height������£�����ֵΪtrue��ʾ��Ҫ�ü���ͬʱ��ͼƬ��������size
bool CalculateImageSize(const std::wstring& file, SIZE& size, int max_width, int max_height);

//��������ͼ����Сcx * cy
void ZoomImageF(const std::wstring &src, const std::wstring &dest, int cx, int cy);
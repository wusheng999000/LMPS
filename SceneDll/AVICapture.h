#pragma once

#include <vfw.h>
#pragma comment(lib,"vfw32.lib ")

class CAVICapture
{
public:
	CAVICapture(void);
	~CAVICapture(void);
	
public:
	bool StartCapture(CString filename, int w, int h, float fps);
    bool EndCapture();
    bool CaptureFrame();

    int GetWidth() const;
    int GetHeight() const;
    float GetFrameRate() const;

 private:
    void CleanUp();

 private:
    int nWidth;
    int nHeight;
    float mFrameRate;
    int nFrameCounter;
    bool m_bCapturing;
    PAVIFILE aviFile;
    PAVISTREAM aviStream;
    PAVISTREAM compAviStream;
    unsigned char* image;
};

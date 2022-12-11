#include "soundManager.h"

GLvoid PlaySoundMP3(std::string str, GLboolean isLoop, MCI_OPEN_PARMS &openBgm) {
    //MCI_OPEN_PARMS openBgm;     // 무한 루프
    //openBgm.lpstrElementName = s2ws(str).c_str();
    std::wstring stemp = std::wstring(str.begin(), str.end());
    LPCWSTR sw = stemp.c_str();
    openBgm.lpstrElementName = sw;
    openBgm.lpstrDeviceType = TEXT("mpegvideo");
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
    if(isLoop)
        mciSendCommand(openBgm.wDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);
    else
        mciSendCommand(openBgm.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openBgm);
}

GLvoid SetBgm(std::string str, MCI_OPEN_PARMS& openBgm) {
    if (openBgm.lpstrElementName == nullptr) {
        std::wstring stemp = std::wstring(str.begin(), str.end());
        LPCWSTR sw = stemp.c_str();
        openBgm.lpstrElementName = sw;
        openBgm.lpstrDeviceType = TEXT("mpegvideo");
        mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
    }
}

GLvoid PlaySoundMP3(MCI_OPEN_PARMS& openBgm, GLboolean isLoop) {
    if (isLoop)
        mciSendCommand(openBgm.wDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);
    else
        mciSendCommand(openBgm.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openBgm);
}

GLvoid SoundToStart(MCI_OPEN_PARMS& openBgm) {
    if(openBgm.lpstrElementName != nullptr)
        mciSendCommand(openBgm.wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
}

GLvoid PlaySoundMP3(std::string str, GLboolean isLoop) {
    MCI_OPEN_PARMS openBgm;
    //openBgm.lpstrElementName = s2ws(str).c_str();
    std::wstring stemp = std::wstring(str.begin(), str.end());
    LPCWSTR sw = stemp.c_str();
    openBgm.lpstrElementName = sw;
    openBgm.lpstrDeviceType = TEXT("mpegvideo");
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
    if (isLoop)
        mciSendCommand(openBgm.wDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);
    else
        mciSendCommand(openBgm.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openBgm);
}

std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}
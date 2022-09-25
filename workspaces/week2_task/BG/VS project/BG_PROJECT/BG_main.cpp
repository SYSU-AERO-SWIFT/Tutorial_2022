#include "BG_H.h"
int main()
{
    Recovery test;
    string filePath;
    cout << "请输入视频绝对地址:" << endl;
    cout << "例如：D:/Github/Tutorial_2022/resource/video0.mp4" << endl;
    cin >> filePath;
    test.readVideo();
    test.process(filePath);
    test.showResult();
    return 0;
}
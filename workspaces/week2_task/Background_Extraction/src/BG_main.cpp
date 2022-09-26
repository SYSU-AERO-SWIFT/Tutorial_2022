#include "BG_H.h"
int main(int argc,char **argv)
{
    Recovery test;
    string filePath;
    //cout << "请输入视频绝对地址:" << endl;
    //cout << "例如：D:/Github/Tutorial_2022/resource/video0.mp4" << endl;
    //cin >> filePath;
    test.readVideo(argv[1]);
    test.process();
    test.showResult();
    return 0;
}

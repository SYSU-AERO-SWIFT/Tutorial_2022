## 通过Vim输出 Hello World 的过程简介

1. ctrl+alt+T 打开终端
2. 执行`cd /Desktop/MyProgram` 进入文件夹 没有相关文件夹请mkdir或者鼠标右键（如果你有图形桌面的话）
3. 执行‘vim helloworld.cpp’ vim会自动帮你新建一个名为“helloworld.cpp”的文件
4. 输入代码
```
#include <iostream>
using namespace std;

int main(){
	string out = "Hello World!";
	cout<<out;
	cout<<"\n";
	return 0;
}
```
5. 键盘按下Esc退出Insert模式。再通过键盘输入`:wq`保存并推出，其中w表示保存，q表示退出
6. 继续在终端中执行
   ```
   $ g++ helloworld.cpp -o helloworld`
   ```
   完成对cpp源码的编译。
   其中g++参数用法请自行查阅
7. 执行`./helloworld`，享受终端回复给你`Hello World!`的乐趣吧（笑）
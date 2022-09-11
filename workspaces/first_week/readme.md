#第一周考核任务

>**第一次做项目，文件起名比较随意，请根据下面指示进行**

## hello

这是第一题的文件夹，运行的是一个输出`Hello world`的程序

运行方式：
```
cd ~/hello   //进入指定文件夹

./HELLO 
```
即可运行，并输出以下结果

```
Hello world
```
## newpack

这是第二题的文件夹，`publiser`将发布一个话题`/topic`，包含一个随机数，`subscriber`接收后打印在终端上

运行方式
先启动ros
```
roscore
```
打开第二个终端窗口
```
cd ~/newpack   //进入指定文件夹
source devel/setup.bash   //如后续rosrun无法找到请多次重置环境变量
rosrun pack1 publisher
```
publisher开始运行，随后打开第三个终端窗口

```
cd ~/newpack   //进入指定文件夹
source devel/setup.bash
rosrun pack1 subscriber
```
立刻在终端上看到输出数据，为随机数数列，
```
[ INFO] [1662823903.901797764]: get -51

[ INFO] [1662823904.002273185]: get 38

[ INFO] [1662823904.101232242]: get -113

[ INFO] [1662823904.201749838]: get 126

[ INFO] [1662823904.301976404]: get -78

[ INFO] [1662823904.401217751]: get 112

[ INFO] [1662823904.502289013]: get -74

[ INFO] [1662823904.601167168]: get -33
```
键入`ctrl+C`停止运行subscriber

## serve
此为第三题的文件夹，`client`将以一个（0，1）间的浮点数**n**向`server`提出**request**，若**n<0.5**，`server`拒绝并返回false，client接收后打印No，反之打印Yes

运行方式
先启动ros
```
roscore
```
打开第二个终端窗口
```
cd ~/serve   //进入指定文件夹
source devel/setup.bash
rosrun pack2 client  //应当先打开client
```
publisher开始运行，并等待service回应，随后打开第三个终端窗口

```
cd ~/serve   //进入指定文件夹
source devel/setup.bash
rosrun pack2 server
```
立刻在终端上看到输出数据，
```
[ INFO] [1662824144.281396131]: 0.910878,No

[ INFO] [1662824144.282238852]: 0.325200,Yes

[ INFO] [1662824144.282990658]: 0.003141,Yes

[ INFO] [1662824144.283792289]: 0.044701,Yes

[ INFO] [1662824144.284612080]: 0.418142,Yes

[ INFO] [1662824144.285436247]: 0.337968,Yes
```
键入`ctrl+C`停止运行（应该先停止`client`，否则一直被拒会一直输出No）

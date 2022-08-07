# 基于git和GitHub完成考核任务

Author：@PiCaHor

| 版本 | 说明 |备注|
| ---- | ---- | ---- |
| v0.0.0 | 建立文档 |无|

## 前言

该部分将要介绍如何使用git作为版本管理语言，GitHub作为仓库来进行本次考核

该部分分为两部分： **Windows** 和**Linux**两个操作系统下如何完成

这里说明如果你的目标是学到完整的项目管理，请专注学习Linux部分

关于git语言这里不进行更多的阐述给出两个参考

[git官方文档](https://git-scm.com/book/zh/v2)

[基于java的git学习网站](https://learngitbranching.js.org/?locale=zh_CN)

由于github容易出现域名污染，所以可能会出现登不上以及图片加载不成功的情况这里有条件的同学可以科学上网，如果不行请在提交时多试几次，针对图片问题可以将仓库clone到本地后进行查看。 

### Windows

##### 前置准备

- Windows系统
- 较为充足的存储空间
- GitHub Desktop-[下载地址](https://desktop.github.com/)

- github账号

##### 获取仓库

首先来到考核仓库，在右上角点击Fork按钮，完成后你就成功的将考核仓库拷贝一份自己的部分，以后你都可以在头像下的Your repositories中找到它

然后打开Github Desktop 在菜单栏中选择File-Clone repository

如图：

![image](./image/githubdesktop_1.png)

选择对应的仓库与保存地址，点击`clone`。至此你的远程仓库就克隆到本地了

接下来你只需要将你完成的内容在对应的文件夹下保存

##### 更新仓库

当你在后续时间中打开项目时，请留意是否有`Pull origin`按钮

如图

![image](./image/githubdesktop_2.jpg)

点击它更新远程仓库的内容

##### 提交考核

当你对本地仓库进行编辑后你的所有操作都会被track，在desktop上会有对应的显示

当你确定好你要提交的内容后（你可以通过取消文件前面的选择来选择部分上传）

下面的过程就是编辑Common

你需要在头像旁边的summery部分添加梗概说明并可以在Descrption部分添加必要的说明

对于梗概的规定在考试规范中规定

完成后点击`Commit to main`

然后点击主页面上的`Push origin`的按钮，便成功将更新推到了个人的远程仓库之中。

##### 提交pr请求合并到主仓库

当你完成对于所有内容的修改之后来到github上自己fork的仓库

如果你有修改可以看见如图

![image](./image/githubdesktop_3.png)

点击`pull requests` 在页面中点击`New pull request`

在base repository-base中选择自己对应的分支（请注意不要合并到主仓库的main，否则不会予以合并）

然后点击`Create pull request`

在接下来的页面中取消勾选`Allow edits by maintainers`同时在Title与下方添加必要的说明后点击`Create pull request`

下一个页面中在右侧有五个标签栏：

1. Reviewers: 这里可以 @考核负责人让他们来批改你的工作，请在这里点选所有考核负责人。
2. Assignees: 这里填申请人，也就是你自己。
3. Labels: 对 Issue 和 Pull request 进行分类，每个标签都有对应说明，请按实际情况选择，如果是提交成果，选择 `submit`，如果你是第一次使用这个功能，选择 `First Issue!`，各位会欢迎你的到来。
4. Projects: 忽略
5. Milestone: 忽略。

而后只需小小等待以下冲突检测通过后，便可以联系学长姐将你的提交合并到主仓库中

## Linux-UBUNTU

##### 前置准备

- Ubuntu 或者其他的Linux/Unix系统
- github账号

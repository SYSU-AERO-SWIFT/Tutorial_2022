## 程序设计能力练习题

- 请用 C++ 编写程序，直接使用 `g++` 编译。
- 开设此题的目的只是想让你熟悉基本的 C++ 和程序设计，多动动脑筋。
- 只要简单测试 Accepted 就可以得分，代码简洁可得满分。
- **我们会对代码做检查，请独立认真完成**。
- 只需要提交函数定义，请自行测试完整代码。

## 第二周题目 —— 链表求和

### Description

给定两个用链表表示的整数，每个节点包含一个数位。

这些数位是反向存放的，也就是个位排在链表首部。

编写函数对这两个整数求和，并用链表形式返回结果。

编写一个函数，接口如下:

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
```

说明：
1. 不需要自己定义ListNode，也不需要自己包含关于ListNode的头文件，可以认为已有ListNode的定义
2. 不要对输入链表执行原地修改，也不要直接返回输入链表
3. 可以不用担心返回链表的内存泄露问题

### Input

两个链表，分别表示两个加数。

### Output

链表形式的两数之和。

### Sample

```
输入：(7 -> 1 -> 6) + (5 -> 9 -> 2)，即617 + 295
输出：2 -> 1 -> 9，即912
```

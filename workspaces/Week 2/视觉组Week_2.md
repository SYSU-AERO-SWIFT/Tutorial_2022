# 视觉组第二周任务

Author: @Chasers0205



## 任务一：成功还原 video0.mp4 背景图

```
g++ demo.cpp -o demo `pkg-config --cflags --libs opencv`
./demo ../../../resource/video0.mp4
```

![image-20220925220456521](C:\Users\不蒸馒头争口气\AppData\Roaming\Typora\typora-user-images\image-20220925220456521.png)

## 任务二：成功还原 video1.mp4 背景图

```
g++ demo.cpp -o demo `pkg-config --cflags --libs opencv`
./demo ../../../resource.video1.mp4
```

![image-20220925220643102](C:\Users\不蒸馒头争口气\AppData\Roaming\Typora\typora-user-images\image-20220925220643102.png)

## 任务三：成功还原 video2.mp4 背景图

![image-20220925230654183](C:\Users\不蒸馒头争口气\AppData\Roaming\Typora\typora-user-images\image-20220925230654183.png)

## 任务四：输出程序运行计时

略。

## 任务五：使用 makefile 成功编译运行

（未完成）

## 任务六：编写说明文档

略。

## 任务七：完成第二周程序设计题

详见addTwoNumbers.cpp

```
 ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head=nullptr;
        ListNode* temp=nullptr;
        int left=0;
        int total=0;
        int num_1,num_2;
        while(l1||l2)
        {
            num_1=l1?l1->val:0;
            num_2=l2?l2->val:0;
            total=num_1+num_2+left;
            if(!head)
            {
                head=temp=new ListNode(total%10);
            }
            else
            {
                temp->next=new ListNode(total%10);
                temp=temp->next;
            }
            left=(total>=10)?1:0;
            if(l1) l1=l1->next;
            if(l2) l2=l2->next;
        }
        if(left) temp->next=new ListNode(left);
        return head;
    }
```


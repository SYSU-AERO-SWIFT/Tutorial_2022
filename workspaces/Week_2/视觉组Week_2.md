# 视觉组第二周任务

Author: @Chasers0205



## 任务一：成功还原 video0.mp4 背景图

```
g++ demo.cpp -o demo `pkg-config --cflags --libs opencv`
./demo ../../../resource/video0.mp4
```

![image-video0](https://github.com/Chasers0205/Tutorial_2022/blob/main/workspaces/Week_2/video0.jpg)

## 任务二：成功还原 video1.mp4 背景图

```
g++ demo.cpp -o demo `pkg-config --cflags --libs opencv`
./demo ../../../resource.video1.mp4
```

![image-video1](https://github.com/Chasers0205/Tutorial_2022/blob/main/workspaces/Week_2/video1.jpg)

## 任务三：成功还原 video2.mp4 背景图

```
g++ demo2.cpp -o demo2 `pkg-config --cflags --libs opencv`
./demo2 ../../../resource.video2.mp4
```

![image-video2](https://github.com/Chasers0205/Tutorial_2022/blob/main/workspaces/Week_2/video2.jpg)

## 任务四：输出程序运行计时

详见cmd。

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


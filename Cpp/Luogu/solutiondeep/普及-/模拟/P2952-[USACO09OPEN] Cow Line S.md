# 题目信息

# [USACO09OPEN] Cow Line S

## 题目描述

Farmer John（以下简称 FJ）的 $N$ 头奶牛（用 $1 \dots N$ 编号）在直线上排队。一开始，这条线上没有任何奶牛，随着时间的推移，奶牛们会一个接一个地站到队伍的左边或右边。又过了一会儿，某些奶牛会从队伍里离开，去吃自己最喜欢的草料。

FJ 无法跟踪每一头奶牛，于是，他想让你来帮助他。

奶牛以 $1 \dots N$ 的顺序排队，并且离开的奶牛不会再次回来。数据将会给出 $S$（$1 \le S \le 100000$） 条指令，各占一行，分两种：

- $A$ 头奶牛加入了队列（还有一个参数，表示从左加入还是从右加入）；
- $K$ 头奶牛从左边或者右边离开了队列（还有两个参数，分别表示从左离开还是从右离开和离开多少头奶牛）。

输入的命令一定是可以执行的。

所有的操作结束后，你的程序应该以从左到右的顺序输出这个奶牛队列。数据保证最后的队列不空。

## 样例 #1

### 输入

```
10 
A L 
A L 
A R 
A L 
D R 2 
A R 
A R 
D L 1 
A L 
A R 
```

### 输出

```
7 
2 
5 
6 
8 
```

# AI分析结果

• 综合分析与结论：
    - 思路方面，多数题解利用双端队列（deque）来模拟奶牛排队和离开的过程，因为deque支持从两端插入和删除元素，符合题目需求；部分题解使用vector模拟，通过在特定位置插入和删除元素实现；还有用双向链表或数组模拟队列的做法。
    - 算法要点在于根据输入指令判断操作类型（插入或删除）和方向（左或右），然后调用相应数据结构的方法进行处理，最后输出队列中的元素。
    - 解决难点主要是熟悉所选数据结构的操作方法，如deque的push_front、push_back、pop_front、pop_back等函数的使用。同时要注意输入输出的处理，避免因格式问题出错。

    - 整体来看，使用deque的题解较为简洁高效，利用vector的题解实现稍复杂，双向链表和数组模拟相对繁琐。

• 所选的题解：
  - 作者：Sooke (赞：62)  星级：5星
    - 关键亮点：思路清晰简洁，直接点明使用deque解决问题，详细介绍deque特性及基本操作，并指出使用时需考虑时间复杂度，代码简短精炼。
    - 重点代码：
```cpp
#include <iostream>
#include <deque>
using namespace std;
deque < int > Q;
int main(){
    int n, c = 1, k;
    char a, b;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a >> b;
        if(a == 'A' && b == 'L') Q.push_front(c++); else
        if(a == 'A') Q.push_back(c++);  else
        if(b == 'L'){
            cin >> k;
            for(int j = 1; j <= k; j++) Q.pop_front();
        } else {
            cin >> k;
            for(int j = 1; j <= k; j++) Q.pop_back();
        }
    }
    while(!Q.empty()) cout << Q.front() << endl, Q.pop_front();
    return 0;
}
```
    - 核心实现思想：根据输入的指令，判断是从左边还是右边插入奶牛（用push_front或push_back），或者从左边还是右边删除奶牛（用pop_front或pop_back），用变量c记录奶牛编号。最后通过循环输出deque中的元素。

  - 作者：Karl_Aurora (赞：14)  星级：4星
    - 关键亮点：对deque的介绍详细，包括头文件、定义方式及常用成员函数，代码中使用快速读入输出优化，并用迭代器输出结果。
    - 个人心得：提到之前写题解发布不了的情况。
    - 重点代码：
```cpp
//xhyAKIOI出品，禁止典型zmxqs行为
#include<iostream>
#include<cstdio>
#include<deque>
using namespace std;
inline int read(){
    int W = 0;bool f = false;char ch = getchar();
    while(ch < '0' || ch > '9'){f |= ch == '-';ch = getchar();}
    while(ch >= '0' && ch <= '9'){W = (W << 3) + (W << 1) + (ch ^ 48);ch = getchar();}
    return f? -W : W;
    //快速读入啦
}
inline void write(int x){
    if(x == 0){putchar('0');return;}
    if(x < 0){putchar('-');x = -x;}
    static char num[21];static int top = 0;
    while(x){num[++top] = (x % 10) ^ '0';x /= 10;}
    while(top)putchar(num[top--]);
    //快速输出啦
}
deque<int>q;
char ch1, ch2;
int k, n, count;
int main(){
    cerr << "xhytql,AKIOI!";
    n = read();
    for(int i = 1; i <= n; i++){
        cin >> ch1 >> ch2;
        if(ch1 == 'A'){//判断操作类型
            if(ch2 == 'L')q.push_front(++count);
            else q.push_back(++count);
            //判断操作位置
        }
        else{
            k = read();//读入删除个数
            if(ch2 == 'L'){for(int j = 1; j <= k; j++)q.pop_front();}
            else{for(int j = 1; j <= k; j++)q.pop_back();}
            //仍然是判断操作位置
        }
    }
    deque<int>::iterator it;
    for(it = q.begin(); it!= q.end(); it++){
        write(*it);putchar('\n');
        //用迭代器输出
    }
    return 0;
}
```
    - 核心实现思想：与Sooke的思路类似，根据输入指令对deque进行操作，只是在输入输出上做了优化，使用自定义的快速读入read和快速输出write函数，最后用迭代器遍历输出deque中的元素。

  - 作者：fls233666 (赞：4)  星级：4星
    - 关键亮点：先分析题目所需数据结构特点，引出双端队列，详细介绍deque常用操作及时间复杂度，代码实现清晰，给出两种输出方式。
    - 重点代码：
```cpp
#include<iostream>
#include<deque>
using namespace std;
deque<int>line;  //建双端队列
int main(){
    int n, b = 1;
    //b为要入队的牛的编号
    cin >> n;  //读入操作数量
    char c, f;  //c为操作名称，f为操作的位置
    for(int k, i = 0; i < n; i++){
        cin >> c >> f;  //读入操作
        if(c == 'A'){  //加入元素
            if(f == 'L')
                line.push_front(b);
            if(f == 'R')
                line.push_back(b);
            b++;
        }
        if(c == 'D'){  //删除元素
            cin >> k;
            if(f == 'L')
                for(int i = 0; i < k; i++)
                    line.pop_front();
            if(f == 'R')
                for(int i = 0; i < k; i++)
                    line.pop_back();
        }
    }

    //输出
    for(int i = 0; i < line.size(); i++)
        cout << line[i] << endl;

    //以下是输出的等价写法
    /*while(!line.empty()){
        cout << line.front() << endl;
        line.pop_front();
    }*/
    return 0;
}
```
    - 核心实现思想：通过读入的指令判断操作类型和位置，对deque进行插入（push_front或push_back）和删除（pop_front或pop_back）操作，最后通过遍历deque的方式输出其中的元素，提供了两种常见的输出方法。

• 最优关键思路或技巧：使用双端队列（deque）数据结构，利用其能从两端插入和删除元素的特性，简洁高效地模拟奶牛排队和离开的过程。同时，在代码实现中注意输入输出的处理以及对数据结构操作的熟练运用。

• 可拓展之处：同类型题通常围绕对特殊数据结构的操作和模拟，类似算法套路是根据题目对数据插入、删除、访问等操作的要求，选择合适的数据结构（如栈、队列、双端队列、链表等）进行模拟实现。

• 推荐题目：
    - P1996 约瑟夫问题：涉及到循环队列的操作和模拟。
    - P1829 [国家集训队]Crash的数字表格 / JZPTAB：需要对数据结构进行合理选择和优化来解决数论相关问题，可锻炼对数据结构应用的能力。
    - P3370 【模板】字符串哈希：通过字符串相关操作考察对数据结构的运用，与本题类似，需选择合适结构优化操作。 

---
处理用时：76.14秒
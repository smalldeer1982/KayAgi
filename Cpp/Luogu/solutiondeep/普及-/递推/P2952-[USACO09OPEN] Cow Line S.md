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

### 综合分析与结论

本题的核心在于模拟双向队列的操作，要求能够从队列的两端进行插入和删除操作。大多数题解都使用了C++的STL容器`deque`来实现这一功能，少数题解使用了数组模拟或链表来实现。整体来看，使用`deque`的题解代码简洁、可读性高，且时间复杂度较低，是较为推荐的解法。

### 所选高星题解

#### 1. 作者：Sooke (赞：62)  
**星级：5星**  
**关键亮点：**  
- 使用`deque`容器，代码简洁且高效。
- 通过计数器`c`自动生成奶牛的编号，避免了手动管理编号的复杂性。
- 代码逻辑清晰，易于理解。

**核心代码：**
```cpp
#include <iostream>
#include <deque>
using namespace std;
deque < int > Q;
int main(){
    int n , c=1 , k;
    char a , b;
    cin >> n;
    for(int i=1 ; i <= n ; i++){
        cin >> a >> b;
        if(a == 'A' && b == 'L') Q.push_front(c++); else
        if(a == 'A') Q.push_back(c++);  else
        if(b == 'L'){
            cin >> k;
            for(int j=1 ; j <= k ; j++) Q.pop_front();
        } else {
            cin >> k;
            for(int j=1 ; j <= k ; j++) Q.pop_back();
        }
    }
    while(!Q.empty()) cout << Q.front() << endl , Q.pop_front();
    return 0;
}
```

#### 2. 作者：fls233666 (赞：4)  
**星级：4星**  
**关键亮点：**  
- 详细介绍了`deque`的基本操作，适合新手学习。
- 代码结构清晰，注释详细，便于理解。

**核心代码：**
```cpp
#include<iostream>
#include<deque>
using namespace std;
deque<int>line;
int main(){
    int n,b=1;
    cin>>n;
    char c,f;
    for(int k,i=0;i<n;i++){
        cin>>c>>f;
        if(c=='A'){
            if(f=='L') line.push_front(b);
            if(f=='R') line.push_back(b);
            b++;
        }
        if(c=='D'){
            cin>>k;
            if(f=='L') for(int i=0;i<k;i++) line.pop_front();
            if(f=='R') for(int i=0;i<k;i++) line.pop_back();
        }
    }
    for(int i=0;i<line.size();i++) cout<<line[i]<<endl;
    return 0;
}
```

#### 3. 作者：StupidSeven (赞：3)  
**星级：4星**  
**关键亮点：**  
- 使用`vector`模拟双向队列，展示了不同的实现方式。
- 代码逻辑清晰，适合理解队列的基本操作。

**核心代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> v;
int n,s,k;
char x,y;
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>x>>y;
        if(x=='A'){
            s++;
            if(y=='L') v.insert(v.begin(),s);
            else v.push_back(s);
        }
        else{
            if(x=='D') cin>>k;
            if(y=='L') v.erase(v.begin(),v.begin()+k);
            else for(int i=0;i<k;i++) v.pop_back();
        }
    }
    for(int i=0;i<v.size();i++) printf("%d\n",v[i]);
    return 0;
}
```

### 最优关键思路与技巧

1. **使用`deque`容器**：`deque`是C++ STL中的双向队列，支持在队列的两端进行插入和删除操作，时间复杂度为O(1)，非常适合本题的需求。
2. **自动编号**：通过一个计数器`c`自动生成奶牛的编号，简化了编号管理。
3. **代码简洁性**：使用`deque`的题解代码通常较为简洁，逻辑清晰，易于理解和维护。

### 可拓展之处

- **类似题目**：可以尝试解决其他需要双向操作的队列问题，如滑动窗口最大值、双端队列的合并等。
- **数据结构扩展**：除了`deque`，还可以尝试使用链表或数组模拟双向队列，理解不同数据结构的优缺点。

### 推荐题目

1. **P1886 滑动窗口**：考察滑动窗口的最大值，可以使用双端队列优化。
2. **P1440 求m区间内的最小值**：类似滑动窗口问题，适合练习双端队列的应用。
3. **P2827 蚯蚓**：考察队列的合并与分割，适合练习队列的高级操作。

### 个人心得总结

- **调试经历**：部分题解提到在输入处理时遇到问题，如`scanf`读取空格和回车，建议使用`cin`或`getline`来避免这些问题。
- **踩坑教训**：使用`vector`模拟双向队列时，删除操作的时间复杂度较高，建议使用`deque`来优化。
- **顿悟感想**：理解`deque`的双向操作特性后，代码实现变得非常简单，适合快速解决类似问题。

---
处理用时：40.54秒
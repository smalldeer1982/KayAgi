# 题目信息

# Cirno's Perfect Bitmasks Classroom

## 题目描述

> 就算是很简单的问题，她一定也答不上来。——《东方求闻史纪》   

琪露诺的完美位运算教室开始了！    
琪露诺给了她的学生一个正整数 $x$，作为作业题，她的学生需要找到一个满足以下两个条件的，最小的正整数 $y$。
- $x \operatorname{and} y>0$     
- $x \operatorname{xor} y>0$ 

这里的 $\operatorname{and}$ 和 $\operatorname{xor}$ 都是位运算。      
她的学生米斯蒂娅对这个问题束手无策，请你来帮帮她。

## 样例 #1

### 输入

```
7
1
2
5
9
16
114514
1000000```

### 输出

```
3
3
1
1
17
2
64```

# AI分析结果

### 题目内容中文重写
#### Cirno's Perfect Bitmasks Classroom

##### 题目描述
> 就算是很简单的问题，她一定也答不上来。——《东方求闻史纪》   

琪露诺的完美位运算教室开始了！    
琪露诺给了她的学生一个正整数 $x$，作为作业题，她的学生需要找到一个满足以下两个条件的，最小的正整数 $y$。
- $x \operatorname{and} y>0$     
- $x \operatorname{xor} y>0$ 

这里的 $\operatorname{and}$ 和 $\operatorname{xor}$ 都是位运算。      
她的学生米斯蒂娅对这个问题束手无策，请你来帮帮她。

##### 样例 #1
###### 输入
```
7
1
2
5
9
16
114514
1000000
```
###### 输出
```
3
3
1
1
17
2
64
```

### 综合分析与结论
这些题解的核心思路都是根据位运算 `and` 和 `xor` 的性质，结合 $x$ 的二进制表示来确定最小的 $y$。主要通过分类讨论 $x$ 的不同情况来求解，如 $x = 1$、$x$ 为奇数、$x$ 为偶数且二进制中 $1$ 的个数为 $1$ 或大于 $1$ 等。

#### 算法要点
- 利用 `lowbit` 运算找到 $x$ 二进制表示中最低位的 $1$ 所对应的值。
- 通过判断 $x$ 二进制中 $1$ 的个数进行分类讨论。

#### 解决难点
- 确定 $y$ 的最小值，需要考虑 $x$ 的不同情况，避免遗漏特殊情况。
- 对于 $x$ 二进制中只有一个 $1$ 的情况，要特殊处理以满足两个位运算条件。

### 评分较高的题解
- **作者：Failure_Terminator（5星）**
    - **关键亮点**：思路清晰，先将题意转化为二进制表示下的条件，明确 $y$ 的范围，再通过循环向后推导找到合适的 $y$，代码注释详细解释了 `lowbit` 运算。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
int lowbit(int x){return x&(-x);}
int main()
{
    cin>>T;
    while(T--){
        scanf("%d",&n);
        int t=lowbit(n);
        while(!(t^n && t&n)) t++;
        printf("%d\n",t);
    }
    return 0;
}
```
    - **核心实现思想**：先通过 `lowbit` 函数得到 $n$ 二进制表示中最低位的 $1$ 所对应的值 $t$，然后不断递增 $t$，直到满足 $t$ 与 $n$ 的异或和与运算结果都大于 $0$，最后输出 $t$。

- **作者：708151_qwq（4星）**
    - **关键亮点**：对 $x$ 的不同情况进行了详细分类讨论，逻辑清晰，代码简洁易懂。
    - **核心代码**：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long lowbit(long long x) {return x&(-x);}
int main() {
    int n; scanf("%d",&n);
    for(int i=0; i<n; i++) {
        long long x; scanf("%lld",&x);
        if(x==1) printf("3\n");
        if(x%2==1&&x!=1) printf("1\n");
        if(x%2==0) {
            if(lowbit(x)==x) printf("%lld\n",x+1);
            else printf("%lld\n",lowbit(x));
        }
    }
    return 0;
}
```
    - **核心实现思想**：根据 $x$ 是否等于 $1$、是否为奇数、是否为偶数且二进制中只有一个 $1$ 进行分类讨论，分别输出对应的 $y$ 值。

- **作者：Southern_Dynasty（4星）**
    - **关键亮点**：使用 `__builtin_popcount(x)` 函数方便地求出 $x$ 二进制位下 $1$ 的个数，代码结构清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define lowbit(x) x&-x
int T,x;
signed main(){
    T=read();
    while(T--){
        x=read();
        if(x==1){println(3);continue;}
        if(__builtin_popcount(x)==1)println(x+1);
        else println(lowbit(x));
    }
    return 0;
}
```
    - **核心实现思想**：先判断 $x$ 是否等于 $1$，若等于则输出 $3$；再通过 `__builtin_popcount(x)` 判断 $x$ 二进制中 $1$ 的个数，若为 $1$ 则输出 $x + 1$，否则输出 `lowbit(x)`。

### 最优关键思路或技巧
- **分类讨论**：根据 $x$ 的不同情况进行分类讨论，简化问题求解过程。
- **`lowbit` 运算**：利用 `lowbit` 运算快速找到 $x$ 二进制表示中最低位的 $1$ 所对应的值，为确定 $y$ 提供基础。

### 可拓展之处
同类型题可能会改变位运算的条件或增加其他限制，例如要求满足多个位运算条件或在一定范围内寻找 $y$。类似算法套路可以是对二进制表示进行分析，通过分类讨论和位运算来解决问题。

### 推荐洛谷题目
- [P1100 高低位交换](https://www.luogu.com.cn/problem/P1100)
- [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)
- [P1550 [USACO08OCT]Watering Hole G](https://www.luogu.com.cn/problem/P1550)

### 个人心得摘录与总结
- **作者：yinhy09**：第一次打夜间 CF 比赛，正赶上 Wdoi 超级良心思维场，本人 CF newbie 都差点过掉 D，差点就上绿了。总结：分享了比赛体验和感受，体现了对题目的思考和参与竞赛的积极性。
- **作者：linyuhuai**：前往 blog 获得更好的阅读体验。总结：提醒读者可以通过博客获取更好的阅读体验，可能博客中有更详细的解释和补充内容。 

---
处理用时：36.06秒
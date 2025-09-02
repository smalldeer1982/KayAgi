# 题目信息

# [ARC053A] ドミノ色塗り

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc053/tasks/arc053_a

# AI分析结果

### 题目内容重写
#### [ARC053A] 多米诺骨牌涂色

**题目描述**

在一个 $h$ 行 $w$ 列的矩阵中，有多少种方法可以放置一个 $1 \times 2$ 的多米诺骨牌？多米诺骨牌可以水平或垂直放置。

### 算法分类
数学

### 题解分析与结论
这道题的核心是通过数学推导计算出在给定大小的矩阵中放置 $1 \times 2$ 多米诺骨牌的总方法数。大多数题解都采用了类似的思路，即将问题分为水平放置和垂直放置两种情况，分别计算每种情况的可能性，最后将两者相加得到总方法数。

### 精选题解
#### 题解1：Rulu (5星)
**关键亮点**：
- 通过具体的例子（2×3和4×1的矩阵）进行详细分析，帮助理解问题。
- 推导出通用公式 $(w-1)*h + (h-1)*w$，并给出了边界条件的判断。
- 代码简洁明了，逻辑清晰。

**代码实现**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int h,w;
    cin>>h>>w;
    if((h==1&&w==1)||h==0||w==0)
    {
        cout<<0;
        return 0;
    }
    cout<<(w-1)*h+(h-1)*w;
    return 0;
}
```

#### 题解2：LZH_LOVE_ZRG (4星)
**关键亮点**：
- 提供了两种解决方案，一种是枚举法，另一种是数学推导法。
- 数学推导法简洁高效，代码实现也非常清晰。
- 对边界条件的处理更加简洁。

**代码实现**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n; cin>>n;
    int m; cin>>m; 
    cout<<(n==1||m==1?0:(n-1)*m+n*(m-1));
    return 0;
}
```

#### 题解3：WHJ___ (4星)
**关键亮点**：
- 通过特殊化问题（$W*1$ 和 $1*H$ 的矩形）推导出一般情况的公式。
- 推导过程详细，逻辑清晰，易于理解。
- 代码实现简洁，且包含了必要的输入输出处理。

**代码实现**：
```cpp
#include<bits/stdc++.h>
#define I long long
#define RI register int
#define il inline
#define rt return
using namespace std;
const int N=1e+7;

I h,m;

il I d(){
    I x=0,f=1;
    char c=0;
    while(!isdigit(c=getchar()))f-=(c=='-')*2;
    while(isdigit(c)){x=(x<<1)+(x<<3)+f*(c-48);c=getchar();}
    rt x;
}

signed main()
{
    RI i,j;
    h=d();m=d();
    cout<<(h-1)*m+(m-1)*h;
    rt 0;
}
```

### 最优关键思路
1. **分情况讨论**：将问题分为水平放置和垂直放置两种情况，分别计算每种情况的可能性。
2. **数学推导**：通过简单的数学公式 $(w-1)*h + (h-1)*w$ 计算出总方法数。
3. **边界条件处理**：对特殊情况（如 $1 \times 1$ 矩阵）进行特殊处理，确保程序的鲁棒性。

### 可拓展之处
类似的问题可以扩展到更大或更复杂的形状，如 $2 \times 2$ 或 $1 \times 3$ 的多米诺骨牌，或者在不同形状的网格中放置不同形状的物体。

### 推荐题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
3. [P1044 栈](https://www.luogu.com.cn/problem/P1044)

### 个人心得摘录
- **Rulu**：通过具体的例子进行分析，帮助理解问题，推导出通用公式。
- **LZH_LOVE_ZRG**：提供了两种解决方案，枚举法虽然简单但效率较低，数学推导法更加高效。
- **WHJ___**：通过特殊化问题推导出一般情况的公式，推导过程详细，逻辑清晰。

---
处理用时：28.15秒
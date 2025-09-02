# 题目信息

# [USACO2.1] 顺序的分数 Ordered Fractions

## 题目描述

输入一个自然数 $n$，对于一个最简分数 $a/b$（分子和分母互质的分数），满足 $1 \le b \le n,0 \le a/b \le 1$，请找出所有满足条件的分数。

这有一个例子，当 $n=5$ 时，所有解为：

$$\frac01,\frac15,\frac14,\frac13,\frac25,\frac12,\frac35,\frac23,\frac34 ,\frac45,\frac11$$

给定一个自然数 $n$，请编程按分数值递增的顺序输出所有解。
 
注：   
1、$0$ 和任意自然数的最大公约数就是那个自然数。    
2、互质指最大公约数等于1的两个自然数。


## 说明/提示

【数据范围】    
对于 $100\%$ 的数据，$1\le n \le 160$。

USACO 2.1

翻译来自NOCOW


## 样例 #1

### 输入

```
5
```

### 输出

```
0/1
1/5
1/4
1/3
2/5
1/2
3/5
2/3
3/4
4/5
1/1
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕枚举所有可能的分数，判断其是否为最简分数，并按分数值递增排序输出。思路可分为枚举排序和分治两类。枚举排序是常见方法，通过双重循环枚举分子分母，用`gcd`函数判断最简，再用排序算法排序；分治则基于数学性质，利用分治递归生成有序最简分数。

### 高分题解
1. **作者：浮尘ii（5星）**
    - **关键亮点**：思路独特，引入Stern - Brocot Tree理论，分治算法避免排序，代码简洁高效，有详细理论证明和补充说明。
    - **核心代码**
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int    N;

void DFS(const int& l1, const int& l2, const int& r1, const int& r2)
{
    if(l2 > N || r2 > N)
        return;

    DFS(l1, l2, l1 + r1, l2 + r2);
    if(l2 + r2 <= N)
        printf("%d/%d\n", l1 + r1, l2 + r2);
    DFS(l1 + r1, l2 + r2, r1, r2);
}

int main()
{
    cin >> N;

    printf("0/1\n");
    DFS(0, 1, 1, 1);
    printf("1/1\n");

    return 0;
}
```
    - **核心思想**：从`0/1`和`1/1`开始，递归生成中间分数`(l1 + r1)/(l2 + r2)`，并保证其在`l1/l2`和`r1/r2`之间且为最简分数。
2. **作者：robin2333（4星）**
    - **关键亮点**：详细证明分治算法的数学性质，思路清晰，代码简洁。
    - **核心代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;

void dfs(int a1,int a2,int b1,int b2){
    if(b2>n||b1>n)return;
    dfs(a1,a1+a2,b1,b1+b2);
    if(b1+b2<=n)cout<<a1+a2<<"/"<<b1+b2<<endl;
    dfs(a1+a2,a2,b1+b2,b2);
}

int main(){
    cin>>n;
    cout<<0<<"/"<<1<<endl;
    dfs(0,1,1,1);
    cout<<1<<"/"<<1<<endl;
}
```
    - **核心思想**：基于法雷数列性质，递归生成有序最简分数。
3. **作者：袁宇轩（4星）**
    - **关键亮点**：避免除法精度误差，用交叉相乘比较分数大小，思路巧妙，代码简洁。
    - **核心代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
    int x,y;
}a[23456];
bool cmp(node A,node B)
{
    if (A.x*B.y!=A.y*B.x) return A.x*B.y<A.y*B.x;
    else return A.x<B.x;
}
int main()
{
    cin>>n;
    int cnt=0;
    a[++cnt].x=0;
    a[cnt].y=1;
    a[++cnt].x=1;
    a[cnt].y=1;
    for (int i=1;i<=n;i++)
        for (int j=i+1;j<=n;j++)
            a[++cnt].x=i,a[cnt].y=j;
    sort(a+1,a+cnt+1,cmp);
    for (int i=1;i<=cnt;i++)
    {
        if (i>1 && a[i].x*a[i-1].y==a[i].y*a[i-1].x) continue;
        cout<<a[i].x<<'/'<<a[i].y<<endl;
    }
    return 0;
}
```
    - **核心思想**：枚举所有可能分数，用交叉相乘自定义排序规则，避免除法精度问题。

### 最优关键思路与技巧
- **分治算法**：利用Stern - Brocot Tree或法雷数列性质，递归生成有序最简分数，避免排序。
- **交叉相乘比较**：比较分数大小时，用交叉相乘代替除法，避免精度误差。
- **去重技巧**：使用`set`存储分数，重载`<`运算符实现去重和排序。

### 拓展思路
同类型题目可能涉及更复杂的分数运算或排序规则，可考虑使用优先队列、线段树等数据结构优化算法。类似算法套路可用于处理区间合并、有序序列生成等问题。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法和优先队列的应用。
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)：涉及字符串处理和贪心策略。
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：考察排序和贪心算法。

### 个人心得摘录与总结
- **御·Dragon**：提醒注意数组大小，避免因数组开小导致错误，同时要注意判断大小符号的使用。
- **袁宇轩**：指出用除法比较分数大小存在精度误差问题，建议使用交叉相乘方法。 

---
处理用时：31.94秒
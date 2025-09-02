# 题目信息

# Boxes Packing

## 题目描述

有 $n$ 个物品，$m$ 个盒子。其中第 $i$ 个物品的大小为 $a_i$，所有盒子的大小均为 $k$。Makmis 先生想要将这些物品放入盒子中。对于每个物品，如果可以放入当前盒子中则放入当前盒子，否则换一个新的盒子放入。如果物品数量太多使得盒子装不下，可以**将先放入的物品丢弃**。求出最多能够放入多少物品。

## 说明/提示

#### 样例解释
- 在第一组样例中，可以将后 $4$ 个放入盒子。
- 在第二组样例中仅有一个盒子，故只能放入最后一个。
- 在第三组样例中有 $3$ 个大小为 $3$ 的盒子，每个盒子正好装满。
#### 数据规模与约定
保证 $1\le n,m\le2\times 10^5$，$1\le k\le10^9$，$1\le a_i\le k$。

## 样例 #1

### 输入

```
5 2 6
5 2 1 4 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 1 4
4 2 3 4 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5 3 3
1 2 3 1 1
```

### 输出

```
5
```

# AI分析结果

### 题目重写
#### 题目描述
有 $n$ 个物品，$m$ 个盒子。其中第 $i$ 个物品的大小为 $a_i$，所有盒子的大小均为 $k$。Makmis 先生想要将这些物品放入盒子中。对于每个物品，如果可以放入当前盒子中则放入当前盒子，否则换一个新的盒子放入。如果物品数量太多使得盒子装不下，可以**将先放入的物品丢弃**。求出最多能够放入多少物品。

#### 样例解释
- 在第一组样例中，可以将后 $4$ 个放入盒子。
- 在第二组样例中仅有一个盒子，故只能放入最后一个。
- 在第三组样例中有 $3$ 个大小为 $3$ 的盒子，每个盒子正好装满。

#### 数据规模与约定
保证 $1\le n,m\le2\times 10^5$，$1\le k\le10^9$，$1\le a_i\le k$。

### 题解分析与结论
#### 题解对比
1. **Plozia**：从后往前贪心模拟，时间复杂度 $O(n)$，思路清晰，代码简洁。
2. **StudyingFather**：同样从后往前模拟，时间复杂度 $O(n)$，代码简洁，直接输出结果。
3. **fls233666**：使用二分答案，时间复杂度 $O(n \log n)$，思路较为复杂，但适用性广。

#### 最优思路
从后往前贪心模拟是最优解，时间复杂度为 $O(n)$，思路简单且代码实现容易。二分答案虽然适用性广，但在此题中显得复杂且不必要。

#### 关键技巧
- **从后往前贪心**：由于题目允许丢弃前面的物品，从后往前模拟可以保证最大化放入物品的数量。
- **线性时间复杂度**：通过一次遍历即可得到结果，适合大规模数据。

#### 扩展思路
- 类似题目：可以考察如何在不允许丢弃物品的情况下，最大化放入物品的数量。
- 其他应用：贪心算法在资源分配、任务调度等问题中也有广泛应用。

### 推荐题目
1. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
2. [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)
3. [P1068 分数线划定](https://www.luogu.com.cn/problem/P1068)

### 精选题解
#### 1. Plozia (5星)
**关键亮点**：从后往前贪心模拟，思路清晰，代码简洁。
**代码实现**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,a[200000+10],sum,t;
int box[200000+10];
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) sum+=a[i];
    t=n;
    while(m!=0&&t!=0)
    {
        box[m]+=a[t];
        if(box[m]>k)
        {
            m--;
            box[m]=a[t];
        }
        t--;
    }
    if(m==0) t++;
    printf("%d\n",n-t);
    return 0;
}
```

#### 2. StudyingFather (5星)
**关键亮点**：从后往前模拟，直接输出结果，代码简洁。
**代码实现**：
```cpp
#include <stdio.h>
int a[200005];
int main()
{
 int n,m,k;
 scanf("%d%d%d",&n,&m,&k);
 for(int i=n;i>=1;i--)
  scanf("%d",&a[i]);
 int rem=m,used=0;
 for(int i=1;i<=n;i++)
 {
  if(used+a[i]>k)
  {
   rem--,used=a[i];
   if(rem==0)
   {
    printf("%d\n",i-1);
    return 0;
   }
  }
  else used+=a[i];
 }
 printf("%d\n",n);
 return 0;
}
```

#### 3. fls233666 (4星)
**关键亮点**：二分答案，适用性广，思路较为复杂。
**代码实现**：
```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;
const int mxn = 2e5+5;
int g[mxn],nk,m,n,l,r,md;
inline bool ck(int st){
    int cnt=1,v=0;
    for(rgt i=st;i<=n;i++){
        if(v+g[i]>nk){
            cnt++;
            v=g[i];
        }else v+=g[i];
    }
    return cnt>m;
}
int main(){
    scanf("%d%d%d",&n,&m,&nk);
    for(rgt i=1;i<=n;i++) scanf("%d",&g[i]);
    l=0;
    r=n;
    while(l<r){
        md=(l+r+1)>>1;
        if(ck(md)) l=md;
        else r=md-1;
    }
    printf("%d",n-l);
    return 0;
}
```

---
处理用时：35.17秒
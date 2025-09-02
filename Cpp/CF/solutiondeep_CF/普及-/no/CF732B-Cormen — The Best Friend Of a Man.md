# 题目信息

# Cormen — The Best Friend Of a Man

## 题目描述

Recently a dog was bought for Polycarp. The dog's name is Cormen. Now Polycarp has a lot of troubles. For example, Cormen likes going for a walk.

Empirically Polycarp learned that the dog needs at least $ k $ walks for any two consecutive days in order to feel good. For example, if $ k=5 $ and yesterday Polycarp went for a walk with Cormen $ 2 $ times, today he has to go for a walk at least $ 3 $ times.

Polycarp analysed all his affairs over the next $ n $ days and made a sequence of $ n $ integers $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ is the number of times Polycarp will walk with the dog on the $ i $ -th day while doing all his affairs (for example, he has to go to a shop, throw out the trash, etc.).

Help Polycarp determine the minimum number of walks he needs to do additionaly in the next $ n $ days so that Cormen will feel good during all the $ n $ days. You can assume that on the day before the first day and on the day after the $ n $ -th day Polycarp will go for a walk with Cormen exactly $ k $ times.

Write a program that will find the minumum number of additional walks and the appropriate schedule — the sequence of integers $ b_{1},b_{2},...,b_{n} $ ( $ b_{i}>=a_{i} $ ), where $ b_{i} $ means the total number of walks with the dog on the $ i $ -th day.

## 样例 #1

### 输入

```
3 5
2 0 1
```

### 输出

```
4
2 3 2
```

## 样例 #2

### 输入

```
3 1
0 0 0
```

### 输出

```
1
0 1 0
```

## 样例 #3

### 输入

```
4 6
2 4 3 5
```

### 输出

```
0
2 4 3 5
```

# AI分析结果

### 题目翻译
# 科尔曼——人类最好的朋友

## 题目描述
最近，波利卡普买了一只狗，这只狗叫科尔曼。现在，波利卡普有了很多麻烦。例如，科尔曼喜欢散步。

根据经验，波利卡普了解到，为了让狗感觉良好，在任意连续的两天里，狗至少需要散步 $k$ 次。例如，如果 $k = 5$，并且昨天波利卡普和科尔曼一起散步了 $2$ 次，那么今天他至少要散步 $3$ 次。

波利卡普分析了接下来 $n$ 天的所有事务，并列出了一个由 $n$ 个整数组成的序列 $a_{1},a_{2},\cdots,a_{n}$，其中 $a_{i}$ 表示在第 $i$ 天，波利卡普在处理所有事务的同时会和狗一起散步的次数（例如，他可能需要去商店、倒垃圾等等）。

请帮助波利卡普确定在接下来的 $n$ 天里，他至少还需要额外散步多少次，才能让科尔曼在这 $n$ 天里都感觉良好。你可以假设在第一天之前和第 $n$ 天之后，波利卡普都会和科尔曼一起散步恰好 $k$ 次。

编写一个程序，找出最少的额外散步次数，并给出相应的日程安排——一个整数序列 $b_{1},b_{2},\cdots,b_{n}$（$b_{i} \geq a_{i}$），其中 $b_{i}$ 表示在第 $i$ 天和狗一起散步的总次数。

## 样例 #1
### 输入
```
3 5
2 0 1
```
### 输出
```
4
2 3 2
```

## 样例 #2
### 输入
```
3 1
0 0 0
```
### 输出
```
1
0 1 0
```

## 样例 #3
### 输入
```
4 6
2 4 3 5
```
### 输出
```
0
2 4 3 5
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是使用贪心算法来解决问题。对于相邻的两个数，如果它们的和小于 $k$，就增加后面那个数，使其和达到 $k$，这样能保证增加的数值最小。各题解的不同主要体现在代码实现细节和输入输出方式上。

### 题解评分
| 作者 | 评分 | 思路清晰度 | 代码可读性 | 优化程度 |
| --- | --- | --- | --- | --- |
| Da_un | 4星 | 思路清晰，对贪心策略的解释较为详细 | 代码结构清晰，注释明确 | 无明显优化，但能正确解决问题 |
| yxy666 | 4星 | 思路简洁明了，贪心思想阐述清晰 | 代码简洁，有快读优化 | 快读优化提高了输入效率 |
| Yh0326 | 3星 | 思路明确，但解释相对简略 | 代码简洁，但部分变量命名不够直观 | 无明显优化 |
| 封禁用户 | 3星 | 思路简单直接，但解释不够深入 | 代码有注释，但使用 `while` 循环增加了时间复杂度 | 无明显优化 |
| ttq012 | 3星 | 结合动态规划和贪心解释，稍显复杂 | 代码结构清晰，但部分表述可简化 | 无明显优化 |
| _Scaley | 3星 | 思路详细，对贪心策略解释充分 | 代码有宏定义，增加了理解难度 | 无明显优化 |
| ModestCoder_ | 3星 | 思路简洁，但解释较少 | 代码有快读，部分逻辑可优化 | 快读优化提高了输入效率 |
| Erina | 3星 | 思路简单，但部分表述不准确 | 代码结构简单，但存在小错误 | 无明显优化 |
| 梦游的小雪球 | 3星 | 思路简单，但代码存在错误 | 代码有注释，但存在语法错误 | 无明显优化 |

### 所选题解
- **Da_un（4星）**
    - **关键亮点**：思路清晰，对贪心策略的解释较为详细，代码结构清晰，注释明确。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAXN 600
using namespace std;
int n,k;
int f[MAXN],ans;
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&f[i]);
    for(int i=2;i<=n;i++){//取i与i-1,于是从2开始 
        if(f[i]+f[i-1]<k){//此时需要更改数值 
            int t=k-f[i-1];//t是f[i]要到的最小数值 
            ans+=(t-f[i]);//累加增加的数值 
            f[i]+=(t-f[i]);//更改f[i]使之达到符合条件的最小值 
        }
    }
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)
        printf("%d ",f[i]);
    //输出 
    return 0;
    //完结撒花~~ 
} 
```
- **yxy666（4星）**
    - **关键亮点**：思路简洁明了，贪心思想阐述清晰，代码简洁，有快读优化。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans,a[505];
inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
    return ret*f;
}//快读
int main(){
    n=read();k=read();
    for(int i=1;i<=n;i++)a[i]=read();//输入
    for(int i=2;i<=n;i++){//因为第一个数前面没有数，所以从第二个开始找
        if(a[i]+a[i-1]<k){
            ans+=k-a[i]-a[i-1];a[i]+=k-a[i]-a[i-1];
        }//如果加和不够，贪心的想法，加给后面的数。答案累加
    }
    printf("%d\n",ans); 
    for(int i=1;i<=n;i++)printf("%d ",a[i]);//输出
    return 0;
}
```

### 最优关键思路或技巧
使用贪心算法，每次只考虑相邻两个数的和是否小于 $k$，如果小于就增加后面那个数，因为后面的数还会参与下一次的判断，这样能保证增加的数值最小。

### 可拓展之处
同类型的题目可能会有不同的约束条件，例如要求相邻三个数的和不小于某个值，或者有更多的限制条件。解题思路仍然可以使用贪心算法，根据具体的约束条件进行调整。

### 推荐题目
1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
2. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
3. [P2240 【深基12.例1】部分背包问题](https://www.luogu.com.cn/problem/P2240)

### 个人心得
题解中暂无个人心得相关内容。

---
处理用时：43.47秒
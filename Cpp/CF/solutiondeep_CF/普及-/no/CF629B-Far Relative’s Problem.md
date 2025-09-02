# 题目信息

# Far Relative’s Problem

## 题目描述

Famil Door wants to celebrate his birthday with his friends from Far Far Away. He has $ n $ friends and each of them can come to the party in a specific range of days of the year from $ a_{i} $ to $ b_{i} $ . Of course, Famil Door wants to have as many friends celebrating together with him as possible.

Far cars are as weird as Far Far Away citizens, so they can only carry two people of opposite gender, that is exactly one male and one female. However, Far is so far from here that no other transportation may be used to get to the party.

Famil Door should select some day of the year and invite some of his friends, such that they all are available at this moment and the number of male friends invited is equal to the number of female friends invited. Find the maximum number of friends that may present at the party.

## 说明/提示

In the first sample, friends $ 3 $ and $ 4 $ can come on any day in range $ [117,128] $ .

In the second sample, friends with indices $ 3 $ , $ 4 $ , $ 5 $ and $ 6 $ can come on day $ 140 $ .

## 样例 #1

### 输入

```
4
M 151 307
F 343 352
F 117 145
M 24 128
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
M 128 130
F 128 131
F 131 140
F 131 141
M 131 200
M 140 200
```

### 输出

```
4
```

# AI分析结果

### 题目中文重写
# 远亲的问题

## 题目描述
法米尔·多尔（Famil Door）想和来自遥远之地的朋友们一起庆祝他的生日。他有 $n$ 个朋友，每个朋友都可以在一年中的特定时间段 $[a_{i}, b_{i}]$ 内来参加派对。当然，法米尔·多尔希望尽可能多的朋友能和他一起庆祝。

遥远之地的汽车和那里的居民一样奇特，它们只能搭载一男一女两名乘客，也就是说，必须恰好一名男性和一名女性。然而，这个地方非常遥远，没有其他交通工具可以用来前往派对。

法米尔·多尔应该选择一年中的某一天并邀请一些朋友，使得这些朋友在这一天都有空，并且邀请的男性朋友数量等于女性朋友数量。请找出最多可以有多少朋友参加派对。

## 说明/提示
在第一个样例中，朋友 3 和 4 可以在区间 $[117, 128]$ 内的任何一天来参加派对。

在第二个样例中，索引为 3、4、5 和 6 的朋友可以在第 140 天来参加派对。

## 样例 #1
### 输入
```
4
M 151 307
F 343 352
F 117 145
M 24 128
```
### 输出
```
2
```

## 样例 #2
### 输入
```
6
M 128 130
F 128 131
F 131 140
F 131 141
M 131 200
M 140 200
```
### 输出
```
4
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是通过枚举一年中的每一天，统计当天空闲的男性和女性朋友数量，然后取两者中的最小值，最后找出这个最小值的最大值并乘以 2 得到最多可邀请的朋友数。

不同题解的差异主要体现在实现细节和优化上：
- 大部分题解直接暴力枚举每一天，统计男女数量。
- 部分题解通过记录最早空闲起始日和最晚空闲结束日，减少不必要的枚举，优化了时间复杂度。
- 还有题解使用差分和前缀和的方法，进一步优化区间更新和查询的效率。

### 评分较高的题解
- **作者：封禁用户（4星）**
    - **关键亮点**：思路清晰，通过记录最早空闲起始日和最晚空闲结束日，避免了遍历该年的每一天，优化了时间复杂度。代码注释详细，可读性高。
    - **个人心得**：无
- **作者：smyslenny（4星）**
    - **关键亮点**：使用差分和前缀和的方法，对区间更新和查询进行了优化，减少了时间复杂度。同时给出了差分的学习链接，方便读者学习。
    - **个人心得**：无

### 重点代码
#### 封禁用户的代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int m[366]={0},wm[366]={0};   //开两个数组分别记录该年每天空闲的男性、女性朋友数并初始化
int main()
{
    ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
    int n,begin,end;   //定义总朋友数、每位朋友该年空闲日期起始和结束
    char gender;   //定义每位朋友的性别
    int minb=100000000,maxe=-100000000,ans=0;   //定义朋友的最早空闲起始日和最晚空闲结束日并以极值初始化（避免遍历该年每一天），需邀最多朋友数
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>gender>>begin>>end;
        minb=min(minb,begin);   //朋友的最早空闲起始日
        maxe=max(maxe,end);   //朋友的最晚空闲结束日
        for(int j=begin;j<=end;j++)
        {
            if(gender=='M') m[j]++;   //如为男性则在当天空闲男性数累加
            else wm[j]++;   //如为另一性别－－女性，则在当天空闲女性数累加
        }
    }
    for(int i=minb;i<=maxe;i++)   //从朋友的最早空闲起始日到最晚空闲结束日间遍历
    {
        ans=max(ans,min(m[i],wm[i]));   //求该年空闲男性、女性朋友组对最多那天的对数
    }
    ans*=2;   //需邀朋友数为对数两倍
    cout<<ans;
    return 0;   //结束整个程序
}
```
**核心实现思想**：使用两个数组分别记录每天空闲的男性和女性朋友数，通过记录最早和最晚空闲时间，减少不必要的枚举，最后找出可组对数最多的那天，将对数乘以 2 得到最终结果。

#### smyslenny 的代码
```c++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using namespace std;

int n;

int read()
{
    int x=0,y=1;
    char c=getchar();
    while(c<'0' || c>'9') {if(c=='-') y=0;c=getchar();}
    while(c>='0' && c<='9') { x=x*10+(c^48);c=getchar();}
    return y?x:-x;
}

int Man[M],Woman[M],Max,Ans,Ans_1,Ans_2;

int main()
{
    n=read();
    for(int i=1,l,r;i<=n;i++)
    {
        char op;
        cin>>op;l=read(),r=read(),Max=max(Max,max(l,r));
        if(op=='M')//差分
            Man[l]++,Man[r+1]--;
        else
            Woman[l]++,Woman[r+1]--;
    }
    for(int i=1;i<=Max;i++)//前缀和
    {
        Ans_1+=Man[i],Ans_2+=Woman[i];
        Ans=max(Ans,min(Ans_1,Ans_2));
    }
    printf("%d\n",Ans<<1);
    return 0;
}
```
**核心实现思想**：使用差分标记区间加，记录每个区间有空闲时间的人数变化，然后通过前缀和计算出每天实际的男女空闲人数，最后找出可组对数最多的那天，将对数乘以 2 得到最终结果。

### 最优关键思路或技巧
- **记录最早和最晚空闲时间**：避免遍历该年的每一天，减少不必要的计算。
- **差分和前缀和**：对于区间更新和查询，使用差分和前缀和可以将时间复杂度从 $O(n)$ 优化到 $O(1)$。

### 可拓展之处
同类型题或类似算法套路：
- 区间覆盖问题：给定多个区间，求某个点被最多区间覆盖的情况。
- 活动安排问题：给定多个活动的开始和结束时间，求某个时间点能同时进行的活动最多的情况。

### 推荐题目
- [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)
- [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)
- [P2367 语文成绩](https://www.luogu.com.cn/problem/P2367)

### 个人心得摘录与总结
- **wangkangyou**：提到使用小技巧将字母转换成数字，开在同一张表上方便比较，体现了代码实现上的技巧。
- **江山_远方**：指出翻译有锅，虽然说是 2019 年，但枚举天数时要枚举 366 天，提醒读者要注意题目细节。

---
处理用时：47.27秒
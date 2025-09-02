# 题目信息

# Average Sleep Time

## 题目描述

It's been almost a week since Polycarp couldn't get rid of insomnia. And as you may already know, one week in Berland lasts $ k $ days!

When Polycarp went to a doctor with his problem, the doctor asked him about his sleeping schedule (more specifically, the average amount of hours of sleep per week). Luckily, Polycarp kept records of sleep times for the last $ n $ days. So now he has a sequence $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ is the sleep time on the $ i $ -th day.

The number of records is so large that Polycarp is unable to calculate the average value by himself. Thus he is asking you to help him with the calculations. To get the average Polycarp is going to consider $ k $ consecutive days as a week. So there will be $ n-k+1 $ weeks to take into consideration. For example, if $ k=2 $ , $ n=3 $ and $ a=[3,4,7] $ , then the result is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF808B/86ab5f462dc3fdaf9fb78d24cfe814007844dab2.png).

You should write a program which will calculate average sleep times of Polycarp over all weeks.

## 说明/提示

In the third example there are $ n-k+1=7 $ weeks, so the answer is sums of all weeks divided by 7.

## 样例 #1

### 输入

```
3 2
3 4 7
```

### 输出

```
9.0000000000
```

## 样例 #2

### 输入

```
1 1
10
```

### 输出

```
10.0000000000
```

## 样例 #3

### 输入

```
8 2
1 2 4 100000 123 456 789 1
```

### 输出

```
28964.2857142857
```

# AI分析结果

### 题目中文重写
# 平均睡眠时间

## 题目描述
波利卡普已经失眠快一周了。在伯兰，一周持续 $k$ 天！

当波利卡普带着失眠问题去看医生时，医生询问他的睡眠时间表（更具体地说，是每周的平均睡眠时间）。幸运的是，波利卡普记录了过去 $n$ 天的睡眠时间。所以现在他有一个序列 $a_{1},a_{2},\cdots,a_{n}$，其中 $a_{i}$ 是第 $i$ 天的睡眠时间。

记录的数量太多了，波利卡普自己无法计算平均值。因此，他请求你帮助他进行计算。为了计算平均值，波利卡普将连续的 $k$ 天视为一周。这样就会有 $n - k + 1$ 周需要考虑。例如，如果 $k = 2$，$n = 3$ 且 $a = [3, 4, 7]$，那么结果是 。

你应该编写一个程序来计算波利卡普所有周的平均睡眠时间。

## 说明/提示
在第三个样例中，有 $n - k + 1 = 7$ 周，所以答案是所有周的睡眠时间总和除以 7。

## 样例 #1
### 输入
```
3 2
3 4 7
```
### 输出
```
9.0000000000
```

## 样例 #2
### 输入
```
1 1
10
```
### 输出
```
10.0000000000
```

## 样例 #3
### 输入
```
8 2
1 2 4 100000 123 456 789 1
```
### 输出
```
28964.2857142857
```

### 算法分类
前缀和

### 综合分析与结论
这些题解的核心都是计算所有长度为 $k$ 的连续区间的和的平均值。大部分题解采用前缀和算法，通过预处理前缀和数组，能在 $O(1)$ 时间内计算出任意区间的和，从而将时间复杂度从暴力枚举的 $O(nk)$ 优化到 $O(n)$。部分题解采用滑动窗口的思想，本质上与前缀和类似。还有题解通过计算每个数在所有区间中出现的次数来求解。

### 所选的题解
- **EnofTaiPeople（4星）**
  - 关键亮点：思路清晰，采用滑动窗口思想，代码简洁，详细提醒了浮点数类型和占位符的使用。
  - 个人心得：强调细节很多，适合新手学浮点数，提醒占位符是 `Lf`。
- **_Harrisonwhl_（4星）**
  - 关键亮点：思路明确，使用前缀和算法，详细指出了数据类型的选择，避免了因数据类型问题导致的错误。
  - 个人心得：提醒记得开 `long long`，求和变量不开 `long long` 会 WA#17，前缀和数组不开 `long long` 会 WA#21。
- **pandaSTT（4星）**
  - 关键亮点：思路清晰，采用前缀和算法，代码简洁，有明确的思路注释。
  - 个人心得：温馨提醒“十年 OI 一场空，不开 long long 见祖宗”。

### 重点代码
#### EnofTaiPeople 的代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
    long double ans=0,now=0;int n,num[200005],k,i;
    scanf("%d%d",&n,&k);num[0]=0;
    for(i=1;i<=n;++i)scanf("%d",num+i);
    for(i=1;i<k;++i)now+=num[i];
    for(i=k;i<=n;++i){
        now+=num[i]-num[i-k];
        ans+=now/(n-k+1);
    }
    printf("%.9Lf\n",ans);
    return 0;
}
```
核心实现思想：使用 `now` 记录当前位置的前 $k$ 个数字的和，通过不断更新 `now` 的值，累加每个区间的平均值到 `ans` 中。

#### _Harrisonwhl_ 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a[200005];
long long s[200005];
int main()
{
    cin >> n >> k;
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        s[i]=s[i-1]+a[i];//计算前缀和。
    }
    long long sum=0;
    for (int i=1;i<=n-k+1;i++)
        sum += s[i+k-1]-s[i-1];//加上每个区间。
    printf("%.9f",sum * 1.0 / (n-k+1));//算平均数，保留九位小数。
    return 0;	
}
```
核心实现思想：先计算前缀和数组 `s`，然后通过 `s[i+k-1] - s[i-1]` 计算每个长度为 $k$ 的区间的和，累加所有区间的和到 `sum` 中，最后计算平均值。

#### pandaSTT 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,sum[200005],a[200005];//一定要开 long long 
double ans;
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    }
    for(int i=k;i<=n;i++){
        ans+=(sum[i]-sum[i-k])*1.0;//利用前缀和计算每连续 k 个数字的和
    }
    printf("%.9lf",ans/(n-k+1));//平均数=总和/数量，题目给出了数量为 (n-k+1)
    return 0;
}
```
核心实现思想：同样先计算前缀和数组 `sum`，然后通过 `sum[i] - sum[i-k]` 计算每个长度为 $k$ 的区间的和，累加所有区间的和到 `ans` 中，最后计算平均值。

### 最优关键思路或技巧
- 前缀和：通过预处理前缀和数组，可以在 $O(1)$ 时间内计算出任意区间的和，避免了重复计算，将时间复杂度从 $O(nk)$ 优化到 $O(n)$。
- 数据类型：使用 `long long` 或 `long double` 避免数据溢出。

### 拓展思路
同类型题或类似算法套路：
- 区间查询问题：如给定一个数组，多次查询某个区间的和，可以使用前缀和算法。
- 滑动窗口问题：在处理连续区间的问题时，可以使用滑动窗口的思想，通过维护窗口的左右边界来更新窗口内的信息。

### 推荐题目
- P1115 最大子段和
- P2671 [NOIP2015 普及组] 求和
- P3131 [USACO16JAN]Subsequences Summing to Sevens S

---
处理用时：45.63秒
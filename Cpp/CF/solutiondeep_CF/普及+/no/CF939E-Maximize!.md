# 题目信息

# Maximize!

## 题目描述

You are given a multiset $ S $ consisting of positive integers (initially empty). There are two kind of queries:

1. Add a positive integer to $ S $ , the newly added integer is not less than any number in it.
2. Find a subset $ s $ of the set $ S $ such that the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF939E/6f55d1af0b4bb2f506e26b52edc60c22c6c89cc4.png) is maximum possible. Here $ max(s) $ means maximum value of elements in $ s $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF939E/41a32d216cf052c5a047afb797c2b693c1941a38.png) — the average value of numbers in $ s $ . Output this maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF939E/6f55d1af0b4bb2f506e26b52edc60c22c6c89cc4.png).

## 样例 #1

### 输入

```
6
1 3
2
1 4
2
1 8
2
```

### 输出

```
0.0000000000
0.5000000000
3.0000000000
```

## 样例 #2

### 输入

```
4
1 1
1 4
1 5
2
```

### 输出

```
2.0000000000
```

# AI分析结果

### 题目内容
# 最大化！

## 题目描述
给定一个由正整数组成的多重集 \(S\)（初始为空）。有两种类型的查询：
1. 向 \(S\) 中添加一个正整数，新添加的整数不小于集合中的任何数。
2. 找到集合 \(S\) 的一个子集 \(s\)，使得值 \(\max(s)-\frac{\sum_{x\in s}x}{|s|}\) 尽可能大。这里 \(\max(s)\) 表示 \(s\) 中元素的最大值，\(\frac{\sum_{x\in s}x}{|s|}\) 表示 \(s\) 中数的平均值。输出这个 \(\max(s)-\frac{\sum_{x\in s}x}{|s|}\) 的最大可能值。

## 样例 #1
### 输入
```
6
1 3
2
1 4
2
1 8
2
```
### 输出
```
0.0000000000
0.5000000000
3.0000000000
```

## 样例 #2
### 输入
```
4
1 1
1 4
1 5
2
```
### 输出
```
2.0000000000
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解主要围绕贪心策略展开，核心思路是为使 \(\max(s)-\frac{\sum_{x\in s}x}{|s|}\) 最大，需让最大值尽量大且平均值尽量小。所以每次新加入的最大值必选，同时选部分较小值以拉低平均值。不同题解在实现方式上有差异，部分用尺取法，部分用二分法。

### 所选的题解
- **作者：DarkMoon_Dragon（5星）**
  - **关键亮点**：对贪心策略进行了详细证明，逻辑清晰，代码简洁，采用尺取法统计答案。
  - **重点代码及核心实现思想**：
```cpp
const int N = 5e5 + 50;
int op;
ll sum = 0;
ll maxn, l;
int sz;
ll a[N];
int main() {
    int q = read();
    while (q--) {
        op = read();
        if (op == 1) {
            a[++sz] = read();
            sum += (a[sz] - maxn);
            maxn = a[sz];
            while (l < sz && a[l + 1] * (l + 1) < sum) {
                sum += a[++l];
            }
        } else {
            double ans = maxn - double(sum) / double(l + 1);
            printf("%.14lf\n", ans);
        }
    }
}
```
核心实现思想为：每次加入新数时，更新总和 `sum` 和最大值 `maxn`，通过尺取法移动指针 `l`，判断是否加入新数能使平均值更小，查询时根据当前 `maxn` 和 `sum` 计算并输出结果。
- **作者：Ayano_Kimishima（4星）**
  - **关键亮点**：提出二分做法，利用数递增的特点优化时间复杂度，从 $O(n^2)$ 优化到 $O(n\log_2n)$。
  - **重点代码及核心实现思想**：
```cpp
#include<iostream>
#include<algorithm> 
using namespace std;
double st[500005],summ[500005];
int top;
int main()
{
    int q;
    cin>>q;
    while(q--)
    {
        int opt,cnt=1;
        double x;
        cin>>opt;
        if(opt == 1)
        {
            scanf("%lf",&x); 
            st[++top]=x;
            summ[top]=summ[top - 1]+x;
        }
        else
        {
            double ping = st[top];
            int mid, l = 1, r = top;
            while (l < r)
            {
                mid = l + r >> 1;
                if ((summ[mid]+st[top])/(mid + 1)*1.0>(summ[mid + 1]+st[top])/(mid + 2)*1.0)
                    l = mid + 1;
                else
                    r = mid;
            }
            printf("%.10llf\n",st[top]-(summ[r]+st[top])/(r + 1)*1.0);
        }
    }
    return 0;
}
```
核心实现思想为：用前缀和数组 `summ` 记录累加和，每次查询时，通过二分查找确定选取元素的个数，使得包含最大值时平均数最小，进而计算并输出结果。
- **作者：培淇2021（4星）**
  - **关键亮点**：用数学方式严格证明了贪心策略，逻辑严谨，同样采用尺取法实现。
  - **重点代码及核心实现思想**：
```cpp
if(ch == 1)
{
    cnt++;
    cin>>a[cnt];
    sum += a[cnt] - maxn;
    maxn = a[cnt];
    while(poi < cnt && (poi + 1)*a[poi + 1] < sum)
    {
        poi++;
        sum += a[poi];
    }
}
else
    printf("%.10lf\n",(double)maxn-(double)sum/((double)poi + 1.00000));
```
核心实现思想与DarkMoon_Dragon类似，加入新数时更新总和 `sum` 和最大值 `maxn`，通过尺取法移动指针 `poi` 来调整选取的元素，查询时根据当前 `maxn` 和 `sum` 计算并输出结果。

### 最优关键思路或技巧
- **贪心策略**：确定每次新加入的最大值必选，且为使平均值最小，要选取前面较小的数，这是解决本题的核心思路。
- **尺取法与二分优化**：尺取法通过移动指针动态调整选取的元素，以满足贪心条件；二分法利用数据递增特性优化查找过程，降低时间复杂度。

### 拓展思路
同类型题常围绕贪心策略设计，涉及维护集合或序列，通过特定操作使某个目标函数最优。类似算法套路是先分析目标函数性质，确定贪心方向，再选择合适数据结构或方法实现。例如在数据有序时，可考虑二分优化查找；在需动态调整元素时，尺取法是常用手段。

### 相似知识点洛谷题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过对数据排序确定贪心策略，求解最大收益问题。
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：利用贪心算法解决生产调度中的时间最优问题。
- [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937)：运用贪心策略处理区间分配问题。 

---
处理用时：99.20秒
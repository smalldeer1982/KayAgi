# 题目信息

# Power of Points

## 题目描述

You are given $ n $ points with integer coordinates $ x_1,\dots x_n $ , which lie on a number line.

For some integer $ s $ , we construct segments \[ $ s,x_1 $ \], \[ $ s,x_2 $ \], $ \dots $ , \[ $ s,x_n $ \]. Note that if $ x_i<s $ , then the segment will look like \[ $ x_i,s $ \]. The segment \[ $ a, b $ \] covers all integer points $ a, a+1, a+2, \dots, b $ .

We define the power of a point $ p $ as the number of segments that intersect the point with coordinate $ p $ , denoted as $ f_p $ .

Your task is to compute $ \sum\limits_{p=1}^{10^9}f_p $ for each $ s \in \{x_1,\dots,x_n\} $ , i.e., the sum of $ f_p $ for all integer points from $ 1 $ to $ 10^9 $ .

For example, if the initial coordinates are $ [1,2,5,7,1] $ and we choose $ s=5 $ , then the segments will be: $ [1,5] $ , $ [2,5] $ , $ [5,5] $ , $ [5,7] $ , $ [1,5] $ . And the powers of the points will be: $ f_1=2, f_2=3, f_3=3, f_4=3, f_5=5, f_6=1, f_7=1, f_8=0, \dots, f_{10^9}=0 $ . Their sum is $ 2+3+3+3+5+1+1=18 $ .

## 说明/提示

In the first test case we first choose $ s=x_1=1 $ , then the following segments are formed: $ [1,1] $ , $ [1,4] $ , $ [1,3] $ .

The powers of the points will be as follows: $ f_1=3, f_2=2, f_3=2, f_4=1, f_5=0 \dots $ The sum of powers of the points: $ 3+2+2+1+0+\dots+0=8 $ .

After that we choose $ s=x_2=4 $ . Then there will be such segments: $ [1,4] $ , $ [4,4] $ , $ [3,4] $ , and powers of the points are $ f_1=1, f_2=1, f_3=2, f_4=3 $ .

At the end we take $ s=x_3=3 $ and the segments look like this: $ [1,3] $ , $ [3,4] $ , $ [3,3] $ , the powers of the points are $ f_1=1, f_2=1, f_3=3, f_4=1 $ .

## 样例 #1

### 输入

```
3
3
1 4 3
5
1 2 5 7 1
4
1 10 100 1000```

### 输出

```
8 7 6
16 15 18 24 16
1111 1093 1093 2893```

# AI分析结果

【题目内容】
# 点的力量

## 题目描述

给定 $n$ 个整数坐标点 $x_1,\dots x_n$，这些点位于数轴上。

对于某个整数 $s$，我们构造线段 $[s,x_1]$, $[s,x_2]$, $\dots$, $[s,x_n]$。注意，如果 $x_i < s$，则线段为 $[x_i, s]$。线段 $[a, b]$ 覆盖所有整数点 $a, a+1, a+2, \dots, b$。

我们定义点 $p$ 的力量为覆盖该点的线段数量，记为 $f_p$。

你的任务是对于每个 $s \in \{x_1,\dots,x_n\}$，计算 $\sum\limits_{p=1}^{10^9}f_p$，即从 $1$ 到 $10^9$ 所有整数点的 $f_p$ 之和。

例如，如果初始坐标为 $[1,2,5,7,1]$，且选择 $s=5$，则线段为：$[1,5]$, $[2,5]$, $[5,5]$, $[5,7]$, $[1,5]$。点的力量为：$f_1=2, f_2=3, f_3=3, f_4=3, f_5=5, f_6=1, f_7=1, f_8=0, \dots, f_{10^9}=0$。它们的和为 $2+3+3+3+5+1+1=18$。

## 说明/提示

在第一个测试用例中，首先选择 $s=x_1=1$，则生成的线段为：$[1,1]$, $[1,4]$, $[1,3]$。

点的力量为：$f_1=3, f_2=2, f_3=2, f_4=1, f_5=0 \dots$。点的力量之和为 $3+2+2+1+0+\dots+0=8$。

接着选择 $s=x_2=4$，则生成的线段为：$[1,4]$, $[4,4]$, $[3,4]$，点的力量为 $f_1=1, f_2=1, f_3=2, f_4=3$。

最后选择 $s=x_3=3$，则生成的线段为：$[1,3]$, $[3,4]$, $[3,3]$，点的力量为 $f_1=1, f_2=1, f_3=3, f_4=1$。

## 样例 #1

### 输入

```
3
3
1 4 3
5
1 2 5 7 1
4
1 10 100 1000
```

### 输出

```
8 7 6
16 15 18 24 16
1111 1093 1093 2893
```

【算法分类】  
前缀和、排序

【题解分析与结论】  
本题的核心在于如何高效计算每个 $s$ 对应的 $\sum\limits_{p=1}^{10^9}f_p$。由于直接计算每个点的力量会导致时间复杂度过高，因此需要通过数学推导和前缀和优化来简化计算。

1. **关键思路**：  
   - 通过排序和前缀和，将问题转化为对每个 $s$ 的绝对值求和问题。
   - 利用前缀和和后缀和，快速计算每个 $s$ 对应的 $\sum |x_i - s|$。

2. **难点对比**：  
   - **ScottSuperb** 的题解通过排序和递推的方式，利用前缀和和后缀和快速计算每个 $s$ 的答案，时间复杂度为 $O(n \log n)$。
   - **2huk** 的题解通过维护前缀和和后缀和，直接计算每个 $s$ 的答案，思路清晰且代码简洁。
   - **I_am_kunzi** 的题解通过递推公式，避免了重复计算，进一步优化了时间复杂度。

3. **最优思路**：  
   - **2huk** 的题解通过前缀和和后缀和的维护，直接计算每个 $s$ 的答案，思路清晰且代码简洁，是最优解法。

【评分较高的题解】  
1. **2huk**（5星）  
   - **关键亮点**：通过前缀和和后缀和的维护，直接计算每个 $s$ 的答案，思路清晰且代码简洁。  
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++)
         pre[i] = pre[i - 1] + x[i].first,
         p[x[i].second] = i;
     
     for(int i=n;i>=1;i--)
         suf[i] = suf[i + 1] + x[i].first;
     
     for(int i=1;i<=n;i++)
     {
         int k = x[i].first * (p[i] - 1) - pre[p[i] - 1] + suf[p[i] + 1] - (n - p[i]) * x[i].first + n;
         printf("%d ", k);
     }
     ```

2. **ScottSuperb**（4星）  
   - **关键亮点**：通过排序和递推的方式，利用前缀和和后缀和快速计算每个 $s$ 的答案，时间复杂度为 $O(n \log n)$。  
   - **代码核心**：
     ```cpp
     for(int i = 0; i < n; ++i) ans += p[i].first - p[0].first + 1;
     res[p[0].second] = ans;
     for(int i = 1; i < n; ++i) {
         ans = ans + (i * 2 - n) * (p[i].first - p[i - 1].first);
         res[p[i].second] = ans;
     }
     ```

3. **I_am_kunzi**（4星）  
   - **关键亮点**：通过递推公式，避免了重复计算，进一步优化了时间复杂度。  
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++)
         sum+=a[i].x-a[1].x+1;
     ans[a[1].id]=sum;
     for(int i=2;i<=n;i++){
         sum+=((i<<1)-2-n)*(long long)(a[i].x-a[i-1].x);
         ans[a[i].id]=sum;
     }
     ```

【最优关键思路】  
通过排序和前缀和的维护，直接计算每个 $s$ 的答案，避免了重复计算，时间复杂度为 $O(n \log n)$。

【可拓展之处】  
类似的问题可以通过前缀和和后缀和的维护来优化计算，例如区间求和、区间覆盖等问题。

【推荐题目】  
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)  
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)  
3. [P3382 【模板】线段树 1](https://www.luogu.com.cn/problem/P3382)

---
处理用时：39.65秒
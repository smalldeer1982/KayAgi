# 题目信息

# Chopping Carrots (Easy Version)

## 题目描述

这是该问题的简单版本。两个版本间的区别仅为 $n$、$k$、$a_i$ 和 $\sum n$ 的上界。

注意不正常的空间限制。

给出长度为 $n$ 的整数数组 $ a_1, a_2, \ldots, a_n $，以及一个整数 $k$。

一个长度为 $n$ 的整数数组 $ p_1, p_2, \ldots, p_n $ 的花费为 $\max\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right) - \min\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right)$。
此处，$ \lfloor \frac{x}{y} \rfloor $ 表示 $x$ 除以 $y$ 的整数部分。
请找到花费最小的数组 $p$，且满足对任意 $ 1 \le i \le n$ 都有 $ 1 \le p_i \le k $。

## 说明/提示

在第一个测试组中，最优的数组是 $ p = [1, 1, 1, 2, 2] $。
$ \lfloor \frac{a_i}{p_i} \rfloor $ 得到的结果数组为 $ [4, 5, 6, 4, 5] $。
数组 $p$ 的花费为 $ \max\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) - \min\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) = 6 - 4 = 2 $。
可以证明，没有（满足题目条件的）数组的花费更小。

在第二个测试组中，最优的数组之一为 $ p = [12, 12, 12, 12, 12] $，它使得所有的 $ \lfloor \frac{a_i}{p_i} \rfloor $ 的值都为 $0$。

在第三个测试组中，唯一可能的数组为 $ p = [1, 1, 1] $。

## 样例 #1

### 输入

```
7
5 2
4 5 6 8 11
5 12
4 5 6 8 11
3 1
2 9 15
7 3
2 3 5 5 6 9 10
6 56
54 286 527 1436 2450 2681
3 95
16 340 2241
2 2
1 3```

### 输出

```
2
0
13
1
4
7
0```

# AI分析结果

### 题目内容重写

#### 题目描述

这是该问题的简单版本。两个版本间的区别仅为 $n$、$k$、$a_i$ 和 $\sum n$ 的上界。

注意不正常的空间限制。

给出长度为 $n$ 的整数数组 $ a_1, a_2, \ldots, a_n $，以及一个整数 $k$。

一个长度为 $n$ 的整数数组 $ p_1, p_2, \ldots, p_n $ 的花费为 $\max\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right) - \min\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right)$。
此处，$ \lfloor \frac{x}{y} \rfloor $ 表示 $x$ 除以 $y$ 的整数部分。
请找到花费最小的数组 $p$，且满足对任意 $ 1 \le i \le n$ 都有 $ 1 \le p_i \le k $。

#### 说明/提示

在第一个测试组中，最优的数组是 $ p = [1, 1, 1, 2, 2] $。
$ \lfloor \frac{a_i}{p_i} \rfloor $ 得到的结果数组为 $ [4, 5, 6, 4, 5] $。
数组 $p$ 的花费为 $ \max\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) - \min\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) = 6 - 4 = 2 $。
可以证明，没有（满足题目条件的）数组的花费更小。

在第二个测试组中，最优的数组之一为 $ p = [12, 12, 12, 12, 12] $，它使得所有的 $ \lfloor \frac{a_i}{p_i} \rfloor $ 的值都为 $0$。

在第三个测试组中，唯一可能的数组为 $ p = [1, 1, 1] $。

#### 样例 #1

##### 输入

```
7
5 2
4 5 6 8 11
5 12
4 5 6 8 11
3 1
2 9 15
7 3
2 3 5 5 6 9 10
6 56
54 286 527 1436 2450 2681
3 95
16 340 2241
2 2
1 3
```

##### 输出

```
2
0
13
1
4
7
0
```

### 题解分析与结论

#### 综合分析

本题的核心在于找到一个数组 $p$，使得 $\max\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right) - \min\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right)$ 最小，且 $1 \le p_i \le k$。由于 $n$ 和 $k$ 的上界较小，大多数题解采用了枚举或二分搜索的策略。

#### 题解评分与亮点

1. **蒟蒻炒扇贝 (4星)**
   - **关键亮点**：通过枚举最小值，并使用二分搜索来找到每个 $p_i$ 的最优值，时间复杂度为 $O(Vn\log k)$，其中 $V$ 是序列 $a$ 元素的最大值。
   - **代码核心**：使用二分搜索来找到每个 $p_i$ 的最优值，确保 $\lfloor \frac{a_i}{p_i} \rfloor$ 尽可能接近枚举的最小值。

2. **tzyt (4星)**
   - **关键亮点**：通过枚举最小值，并贪心地让每个 $\lfloor \frac{a_i}{p_i} \rfloor$ 尽可能接近最小值，从而减少最大值。
   - **代码核心**：直接计算 $p_i = \lfloor \frac{a_i}{mn} \rfloor$，并确保 $p_i \le k$。

3. **Erica_N_Contina (4星)**
   - **关键亮点**：预处理每个 $a_i$ 在 $p \in [1, k]$ 时的 $\lfloor \frac{a_i}{p} \rfloor$ 值，并使用二分搜索来找到最接近最大值的值。
   - **代码核心**：使用数论分块优化预处理，时间复杂度为 $O(n\sqrt{n})$。

#### 最优关键思路

最优的思路是通过枚举最小值，并使用二分搜索或数论分块来找到每个 $p_i$ 的最优值，从而最小化 $\max\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right) - \min\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right)$。

#### 可拓展之处

类似的问题可以扩展到更大的 $n$ 和 $k$，或者更复杂的约束条件。此外，可以尝试使用动态规划或其他优化算法来进一步降低时间复杂度。

#### 推荐题目

1. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
2. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P3389 【模板】高斯消元法](https://www.luogu.com.cn/problem/P3389)

#### 个人心得摘录

- **蒟蒻炒扇贝**：通过二分搜索来找到每个 $p_i$ 的最优值，确保 $\lfloor \frac{a_i}{p_i} \rfloor$ 尽可能接近枚举的最小值。
- **tzyt**：直接计算 $p_i = \lfloor \frac{a_i}{mn} \rfloor$，并确保 $p_i \le k$，贪心策略简洁有效。
- **Erica_N_Contina**：使用数论分块优化预处理，时间复杂度为 $O(n\sqrt{n})$，适用于更大的数据范围。

### 核心代码片段

#### 蒟蒻炒扇贝

```cpp
for(int mn=a[1]/k;mn<=a[1];mn++)
{
    int maxn=0,minn=2e9;
    for(int i=1;i<=n;i++)
    {
        int l=1,r=k,p=1;
        while(l<=r)
        {
            int mid=(l+r)/2;
            if(a[i]/mid<mn)r=mid-1;
            else l=mid+1,p=mid;
        }
        maxn=max(maxn,a[i]/p);
        minn=min(minn,a[i]/p);
    }
    if(minn==mn)ans=min(ans,maxn-mn);
}
```

#### tzyt

```cpp
for(int mnv=0;mnv<=a[1];mnv++)
{
    for(int i=1;i<=n;i++)
    {
        int p=min(k,(mnv?(a[i]/mnv):k));
        mxv=max(mxv,a[i]/p);
    }
    ans=min(ans,mxv-mnv);
}
```

#### Erica_N_Contina

```cpp
for(int i=1;i<=n;i++)
{
    int tot=0,r=0;
    for(int l=1;l<=min(k,a[i]);l=r+1)
    {
        r=a[i]/(a[i]/l);
        tmp[++tot]=a[i]/l;
    }
    if(k>a[i])tmp[++tot]=0;
    maxn=max(maxn,tmp[tot]);
    tmp[0]=M;
    for(int j=tot;j;j--)nxt[tmp[j]]=max(nxt[tmp[j]],tmp[j-1]);
}
```

---
处理用时：58.06秒
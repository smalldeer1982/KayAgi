# 题目信息

# Binary Inversions

## 题目描述

You are given a binary array $ ^{\dagger} $ of length $ n $ . You are allowed to perform one operation on it at most once. In an operation, you can choose any element and flip it: turn a $ 0 $ into a $ 1 $ or vice-versa.

What is the maximum number of inversions $ ^{\ddagger} $ the array can have after performing at most one operation?

 $ ^\dagger $ A binary array is an array that contains only zeroes and ones.

 $ ^\ddagger $ The number of inversions in an array is the number of pairs of indices $ i,j $ such that $ i<j $ and $ a_i > a_j $ .

## 说明/提示

For the first test case, the inversions are initially formed by the pairs of indices ( $ 1, 2 $ ), ( $ 1, 4 $ ), ( $ 3, 4 $ ), being a total of $ 3 $ , which already is the maximum possible.

For the second test case, the inversions are initially formed by the pairs of indices ( $ 2, 3 $ ), ( $ 2, 4 $ ), ( $ 2, 6 $ ), ( $ 5, 6 $ ), being a total of four. But, by flipping the first element, the array becomes $ {1, 1, 0, 0, 1, 0} $ , which has the inversions formed by the pairs of indices ( $ 1, 3 $ ), ( $ 1, 4 $ ), ( $ 1, 6 $ ), ( $ 2, 3 $ ), ( $ 2, 4 $ ), ( $ 2, 6 $ ), ( $ 5, 6 $ ) which total to $ 7 $ inversions which is the maximum possible.

## 样例 #1

### 输入

```
5
4
1 0 1 0
6
0 1 0 0 1 0
2
0 0
8
1 0 1 1 0 0 0 1
3
1 1 1```

### 输出

```
3
7
1
13
2```

# AI分析结果

### 题目内容
# 二进制逆序对

## 题目描述
给定一个长度为 $n$ 的二进制数组 $^{\dagger}$ 。你最多可以对其执行一次操作。在一次操作中，你可以选择任意一个元素并翻转它：将 $0$ 变为 $1$ 或将 $1$ 变为 $0$ 。
执行至多一次操作后，该数组最多能有多少个逆序对 $^{\ddagger}$ ？

$ ^\dagger $ 二进制数组是指仅包含 $0$ 和 $1$ 的数组。

$ ^\ddagger $ 数组中的逆序对数量是指满足 $i < j$ 且 $a_i > a_j$ 的索引对 $(i, j)$ 的数量。

## 说明/提示
对于第一个测试用例，逆序对最初由索引对 $(1, 2)$，$(1, 4)$，$(3, 4)$ 构成，总数为 $3$，这已经是最大可能值。
对于第二个测试用例，逆序对最初由索引对 $(2, 3)$，$(2, 4)$，$(2, 6)$，$(5, 6)$ 构成，总数为 $4$ 。但是，通过翻转第一个元素，数组变为 $\{1, 1, 0, 0, 1, 0\}$，其逆序对由索引对 $(1, 3)$，$(1, 4)$，$(1, 6)$，$(2, 3)$，$(2, 4)$，$(2, 6)$，$(5, 6)$ 构成，总数为 $7$ 个逆序对，这是最大可能值。

## 样例 #1
### 输入
```
5
4
1 0 1 0
6
0 1 0 0 1 0
2
0 0
8
1 0 1 1 0 0 0 1
3
1 1 1
```
### 输出
```
3
7
1
13
2
```

### 算法分类
枚举

### 综合分析与结论
三道题解均围绕计算原数组逆序对数量以及通过改变一个元素来寻找最大逆序对数量展开。litachloveyou 和 _Remake_ 都利用前缀和优化计算，而BLX32M_10 采用贪心思想简化情况。主要难点在于如何高效计算逆序对数量以及分析改变一个元素后逆序对数量的变化。litachloveyou 和 _Remake_ 的方法通用性更强，通过前缀和可以快速获取数组不同位置前后的 $0$ 和 $1$ 的数量，从而准确计算逆序对变化；BLX32M_10 的贪心策略虽巧妙，但依赖于对题目特性的深入观察，即改变第一个 $0$ 或最后一个 $1$ 能使逆序对增加最多。

### 所选的题解
- **litachloveyou（5星）**
    - **关键亮点**：使用前缀和快速统计前面 $1$ 的数量和后面 $0$ 的数量，先计算原数组逆序对，再枚举每个位置修改后的逆序对数量变化，代码简洁高效。
    - **核心代码片段**：
```cpp
void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        b[i] = b[i - 1] + a[i];
    }
    ll cnt = 0, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i])
        {
            int sum = (n - i) - (b[n] - b[i]);
            cnt += sum;
        }
        else
        {
            int sum = b[i - 1];
            cnt += sum;
        }
    }
    cnt = cnt / 2;
    ans = cnt;
    for (int i = 1; i <= n; i++)
    {
        if (a[i])
        {
            int sum = (n - i) - (b[n] - b[i]);
            int mid = b[i - 1];
            ans = max(ans, cnt - sum + mid);
        }
        else
        {
            int sum = b[i - 1];
            int mid = (n - i) - (b[n] - b[i]);
            ans = max(ans, cnt - sum + mid);
        }
    }
    printf("%lld\n", ans);
}
```
    - **核心实现思想**：首先通过前缀和数组 `b` 记录前 $i$ 个元素中 $1$ 的数量。计算原逆序对时，对于 $1$ 统计其后 $0$ 的数量，对于 $0$ 统计其前 $1$ 的数量并累加。枚举修改位置时，根据当前元素是 $0$ 还是 $1$ 来计算修改后逆序对数量的变化，取最大值。
- **_Remake_（4星）**
    - **关键亮点**：同样利用前缀和处理，思路清晰，通过预处理出原序列逆序对个数以及 $0$ 和 $1$ 的前缀和，然后扫描数组计算改变每个位置后逆序对增加量的最大值。
    - **核心代码片段**：
```cpp
signed main()
{
    T = read();
    while (T--)
    {
        n = read();
        for (int r = 1; r <= n; r++)
        {
            A[r] = read();
            pres_0[r] = pres_0[r - 1] + (A[r] == 0);
            pres_1[r] = pres_1[r - 1] + (A[r] == 1);
        }
        long long Cnt = 0;
        long long Ans = 0;
        for (int r = n; r >= 1; r--)
        {
            if (A[r] == 0)
            {
                Cnt++;
            }
            else
            {
                Ans += Cnt;
            }
        }
        long long det = 0;
        for (int r = 1; r <= n; r++)
        {
            if (A[r] == 1)
            {
                det = std::max(det, pres_1[r - 1] - (pres_0[n] - pres_0[r]));
            }
            else
            {
                det = std::max(det, (pres_0[n] - pres_0[r]) - pres_1[r - 1]);
            }
        }
        if (det > 0)
        {
            Ans += det;
        }
        printf("%lld\n", Ans);
    }
    return 0;
}
```
    - **核心实现思想**：先通过循环计算原数组逆序对数量 `Ans`。同时利用前缀和数组 `pres_0` 和 `pres_1` 分别记录前 $i$ 个元素中 $0$ 和 $1$ 的数量。再次扫描数组，对于每个位置，根据其值为 $0$ 或 $1$ 计算改变该位置后逆序对增加量 `det`，若 `det` 大于 $0$，则将其加到原逆序对数量上得到最终答案。
- **BLX32M_10（4星）**
    - **关键亮点**：提出贪心策略，认为改变第一个 $0$ 或最后一个 $1$ 能使逆序对增加最多，通过三次计算逆序对数量（不变、改第一个 $0$、改最后一个 $1$）取最大值，简化了枚举过程。
    - **核心代码片段**：
```cpp
signed main()
{
    int t;
    scanf("%lld", &t);
    while (t--)
    {
        int n, l1 = 0, f0 = 0, cnt = 0, ans = 0, res = 0;
        scanf("%lld", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%lld", &a[i]);
            if (a[i] == 1)
                l1 = i;
        }
        for (int i = 1; i <= n; i++)
            if (a[i] == 0)
            {
                f0 = i;
                break;
            }
        for (int i = n; i >= 1; i--)
        {
            if (a[i])
                ans += cnt;
            else
                cnt++;
        }
        res = max(res, ans);
        a[l1] = 0;
        ans = 0, cnt = 0;
        for (int i = n; i >= 1; i--)
        {
            if (a[i])
                ans += cnt;
            else
                cnt++;
        }
        res = max(res, ans);
        a[l1] = 1;
        a[f0] = 1;
        ans = 0, cnt = 0;
        for (int i = n; i >= 1; i--)
        {
            if (a[i])
                ans += cnt;
            else
                cnt++;
        }
        res = max(res, ans);
        printf("%lld\n", res);
    }
    return 0;
}
```
    - **核心实现思想**：先找出数组中第一个 $0$ 和最后一个 $1$ 的位置。通过从后向前遍历数组计算原数组逆序对数量 `ans` 并更新最大值 `res`。然后分别改变最后一个 $1$ 和第一个 $0$，重新计算逆序对数量并与 `res` 比较取最大值。

### 最优关键思路或技巧
利用前缀和优化逆序对数量计算以及变化分析是较为通用且高效的方法，能够快速获取数组不同位置前后的 $0$ 和 $1$ 的数量，从而准确计算逆序对及其变化。贪心策略如 BLX32M_10 的方法，若能准确发现题目特性，可大幅简化枚举过程，提高效率。

### 可拓展之处
同类型题可拓展到其他有限取值数组（如仅含 $0, 1, 2$）在特定操作下求最大逆序对问题。类似算法套路可用于解决一些涉及区间统计和局部调整影响全局结果的问题，通过前缀和、差分等手段优化计算。

### 洛谷相似题目
- P1908 逆序对
- P3377 【模板】左偏树（可并堆）（部分涉及逆序对计算思想）
- P5634 【CSGRound2】开拓者的卓识（逆序对相关应用） 

---
处理用时：55.12秒
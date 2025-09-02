# 题目信息

# Cyclic Rotation

## 题目描述

There is an array $ a $ of length $ n $ . You may perform the following operation any number of times:

- Choose two indices $ l $ and $ r $ where $ 1 \le l < r \le n $ and $ a_l = a_r $ . Then, set $ a[l \ldots r] = [a_{l+1}, a_{l+2}, \ldots, a_r, a_l] $ .

You are also given another array $ b $ of length $ n $ which is a permutation of $ a $ . Determine whether it is possible to transform array $ a $ into an array $ b $ using the above operation some number of times.

## 说明/提示

In the first test case, we can choose $ l=2 $ and $ r=5 $ to form $ [1, 3, 3, 2, 2] $ .

In the second test case, we can choose $ l=2 $ and $ r=4 $ to form $ [1, 4, 2, 2, 1] $ . Then, we can choose $ l=1 $ and $ r=5 $ to form $ [4, 2, 2, 1, 1] $ .

In the third test case, it can be proven that it is not possible to transform array $ a $ to $ b $ using the operation.

## 样例 #1

### 输入

```
5
5
1 2 3 3 2
1 3 3 2 2
5
1 2 4 2 1
4 2 2 1 1
5
2 4 5 5 2
2 2 4 5 5
3
1 2 3
1 2 3
3
1 1 2
2 1 1```

### 输出

```
YES
YES
NO
YES
NO```

# AI分析结果

### 题目内容中文重写
# 循环旋转

## 题目描述
有一个长度为 $n$ 的数组 $a$。你可以进行任意次数的以下操作：
- 选择两个索引 $l$ 和 $r$，其中 $1 \le l < r \le n$ 且 $a_l = a_r$。然后，将 $a[l \ldots r]$ 设置为 $[a_{l+1}, a_{l+2}, \ldots, a_r, a_l]$。

你还会得到另一个长度为 $n$ 的数组 $b$，它是 $a$ 的一个排列。判断是否可以使用上述操作将数组 $a$ 转换为数组 $b$。

## 说明/提示
在第一个测试用例中，我们可以选择 $l = 2$ 和 $r = 5$ 来得到 $[1, 3, 3, 2, 2]$。
在第二个测试用例中，我们可以选择 $l = 2$ 和 $r = 4$ 来得到 $[1, 4, 2, 2, 1]$。然后，我们可以选择 $l = 1$ 和 $r = 5$ 来得到 $[4, 2, 2, 1, 1]$。
在第三个测试用例中，可以证明不可能使用该操作将数组 $a$ 转换为 $b$。

## 样例 #1
### 输入
```
5
5
1 2 3 3 2
1 3 3 2 2
5
1 2 4 2 1
4 2 2 1 1
5
2 4 5 5 2
2 2 4 5 5
3
1 2 3
1 2 3
3
1 1 2
2 1 1
```
### 输出
```
YES
YES
NO
YES
NO
```

### 算法分类
模拟

### 综合分析与结论
- **思路对比**：
    - Kzh_root 的题解是将数组 $b$ 变换到 $a$，从右到左处理 $b$，记录连续相同元素个数，用双指针模拟匹配过程。
    - Alex_Wei 的题解是依次归位 $b_1\sim b_n$，根据 $a_i$ 与 $b_i$ 的关系决定是否移动元素，通过记录移动元素数量和维护指针来加速匹配。
- **算法要点对比**：
    - Kzh_root 使用 `map` 记录连续相同元素个数，双指针分别指向 $a$ 和 $b$ 数组。
    - Alex_Wei 使用数组 `cnt` 记录移动元素数量，维护指针 `pt` 尝试匹配 $a$ 和 $b$ 数组。
- **解决难点对比**：
    - Kzh_root 主要解决如何处理连续相同元素以及如何进行匹配的问题。
    - Alex_Wei 主要解决如何根据贪心策略决定元素是否移动以及如何加速匹配过程的问题。

### 所选的题解
- **Kzh_root 的题解（4星）**：
    - **关键亮点**：思路清晰，通过将问题转换为 $b$ 到 $a$ 的变换，降低了问题复杂度；代码实现简洁，使用双指针模拟匹配过程。
- **Alex_Wei 的题解（3星）**：
    - **关键亮点**：运用贪心策略，对元素是否移动进行了合理的决策；通过记录移动元素数量和维护指针加速了匹配过程。

### 重点代码
#### Kzh_root 的题解核心代码
```cpp
int ai=n,bi=n;
b[n+1]=0;//防止一些毒瘤数据
while(bi)
{
    if(ai&&bi&&a[ai]==b[bi])
    {
        ai--,bi--;
        continue;
    }
    if(b[bi]==b[bi+1])
        cnt[b[bi--]]++;
    else if(cnt[a[ai]])
        cnt[a[ai--]]--;
    else
    {
        flag=false;
        break;
    }
}
```
**核心实现思想**：使用双指针 `ai` 和 `bi` 分别指向数组 $a$ 和 $b$ 的末尾。如果当前元素相等，则指针都左移；如果 $b$ 中当前元素和下一个元素相等，则将该元素数量记录到 `cnt` 中；如果 `cnt` 中有 $a$ 当前元素，则使用记录的元素进行匹配。

#### Alex_Wei 的题解核心代码
```cpp
int pt = 1;
for(int i = 1; i <= n; i++) {
    while(b[i] != a[pt] && pt <= n) cnt[a[pt++]]++;
    if(pt > n) return puts("NO"), void();
    if(cnt[a[pt]]) cnt[a[pt]]--;
    else pt++;
}
puts("YES");
```
**核心实现思想**：使用指针 `pt` 尝试匹配 $a$ 和 $b$ 数组。如果当前元素不相等，则将 $a$ 中元素数量记录到 `cnt` 中；如果 `cnt` 中有当前元素，则使用记录的元素进行匹配，否则 `pt` 右移。

### 最优关键思路或技巧
- 转换问题方向，将 $a$ 到 $b$ 的变换转换为 $b$ 到 $a$ 的变换，降低问题复杂度。
- 运用贪心策略，根据元素相等情况决定是否移动元素。
- 使用双指针和记录元素数量的方法模拟匹配过程。

### 可拓展之处
同类型题或类似算法套路：可以拓展到其他数组变换问题，通过合理的操作规则和贪心策略来判断数组是否可以相互转换。

### 推荐洛谷题目
- P1047 [NOIP2005 普及组] 校门外的树
- P1059 [NOIP2006 普及组] 明明的随机数
- P1067 [NOIP2009 普及组] 多项式输出

---
处理用时：37.52秒
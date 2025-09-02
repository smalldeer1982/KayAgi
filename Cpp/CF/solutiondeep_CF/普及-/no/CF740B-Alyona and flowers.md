# 题目信息

# Alyona and flowers

## 题目描述

Little Alyona is celebrating Happy Birthday! Her mother has an array of $ n $ flowers. Each flower has some mood, the mood of $ i $ -th flower is $ a_{i} $ . The mood can be positive, zero or negative.

Let's define a subarray as a segment of consecutive flowers. The mother suggested some set of subarrays. Alyona wants to choose several of the subarrays suggested by her mother. After that, each of the flowers will add to the girl's happiness its mood multiplied by the number of chosen subarrays the flower is in.

For example, consider the case when the mother has $ 5 $ flowers, and their moods are equal to $ 1,-2,1,3,-4 $ . Suppose the mother suggested subarrays $ (1,-2) $ , $ (3,-4) $ , $ (1,3) $ , $ (1,-2,1,3) $ . Then if the girl chooses the third and the fourth subarrays then:

- the first flower adds $ 1·1=1 $ to the girl's happiness, because he is in one of chosen subarrays,
- the second flower adds $ (-2)·1=-2 $ , because he is in one of chosen subarrays,
- the third flower adds $ 1·2=2 $ , because he is in two of chosen subarrays,
- the fourth flower adds $ 3·2=6 $ , because he is in two of chosen subarrays,
- the fifth flower adds $ (-4)·0=0 $ , because he is in no chosen subarrays.

Thus, in total $ 1+(-2)+2+6+0=7 $ is added to the girl's happiness. Alyona wants to choose such subarrays from those suggested by the mother that the value added to her happiness would be as large as possible. Help her do this!

Alyona can choose any number of the subarrays, even $ 0 $ or all suggested by her mother.

## 说明/提示

The first example is the situation described in the statements.

In the second example Alyona should choose all subarrays.

The third example has answer $ 0 $ because Alyona can choose none of the subarrays.

## 样例 #1

### 输入

```
5 4
1 -2 1 3 -4
1 2
4 5
3 4
1 4
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4 3
1 2 3 4
1 3
2 4
1 1
```

### 输出

```
16
```

## 样例 #3

### 输入

```
2 2
-1 -2
1 1
1 2
```

### 输出

```
0
```

# AI分析结果

### 题目翻译
# 阿廖娜与花朵

## 题目描述
小阿廖娜正在庆祝生日！她的妈妈有一个由 $ n $ 朵花组成的数组。每朵花都有某种情绪，第 $ i $ 朵花的情绪值为 $ a_{i} $ 。情绪值可以是正数、零或负数。

我们将连续的花朵段定义为一个子数组。妈妈给出了一些子数组。阿廖娜想从妈妈给出的子数组中选择若干个。之后，每朵花都会将其情绪值乘以该花所在的所选子数组的数量，然后将这个结果累加到女孩的快乐值中。

例如，假设妈妈有 $ 5 $ 朵花，它们的情绪值分别为 $ 1, -2, 1, 3, -4 $ 。假设妈妈给出的子数组为 $ (1, -2) $ 、 $ (3, -4) $ 、 $ (1, 3) $ 、 $ (1, -2, 1, 3) $ 。如果女孩选择了第三个和第四个子数组，那么：
- 第一朵花对女孩的快乐值的贡献为 $ 1×1 = 1 $ ，因为它只在一个所选子数组中。
- 第二朵花的贡献为 $ (-2)×1 = -2 $ ，因为它也只在一个所选子数组中。
- 第三朵花的贡献为 $ 1×2 = 2 $ ，因为它在两个所选子数组中。
- 第四朵花的贡献为 $ 3×2 = 6 $ ，因为它同样在两个所选子数组中。
- 第五朵花的贡献为 $ (-4)×0 = 0 $ ，因为它不在任何所选子数组中。

因此，女孩的快乐值总共增加了 $ 1 + (-2) + 2 + 6 + 0 = 7 $ 。阿廖娜希望从妈妈给出的子数组中选择一些，使得她的快乐值增加得尽可能多。请帮助她实现这个目标！

阿廖娜可以选择任意数量的子数组，甚至可以不选（选 $ 0 $ 个）或者选择妈妈给出的所有子数组。

## 说明/提示
第一个样例就是题目描述中给出的情况。

在第二个样例中，阿廖娜应该选择所有的子数组。

第三个样例的答案是 $ 0 $ ，因为阿廖娜可以不选择任何子数组。

## 样例 #1
### 输入
```
5 4
1 -2 1 3 -4
1 2
4 5
3 4
1 4
```
### 输出
```
7
```

## 样例 #2
### 输入
```
4 3
1 2 3 4
1 3
2 4
1 1
```
### 输出
```
16
```

## 样例 #3
### 输入
```
2 2
-1 -2
1 1
1 2
```
### 输出
```
0
```

### 算法分类
前缀和、贪心

### 综合分析与结论
这些题解的核心思路都是贪心策略，即只选择区间和大于 0 的区间，因为这样能使最终的快乐值最大。在计算区间和时，大部分题解采用了前缀和算法，通过前缀和数组可以在 $O(1)$ 时间内计算出任意区间的和，避免了每次都遍历区间元素的 $O(n)$ 复杂度。部分题解还给出了未使用前缀和优化的暴力解法，虽然数据范围小能通过，但复杂度较高。

### 所选的题解
- **Keep_RAD（4星）**
  - **关键亮点**：思路清晰，先介绍了前缀和的概念，再详细说明解题思路，代码注释详细，易于理解。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[102],he[102],sum;
int main()
{
    int n,m;
    cin>>n>>m;
    int l,r;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        he[i]=he[i-1]+a[i];
    }
    for(int i=1;i<=m;i++)
    {
        cin>>l>>r;
        if(he[r]-he[l-1]>0) sum+=he[r]-he[l-1];
    }
    cout<<sum;
    return 0;
}
```
  - **核心实现思想**：先读入数组并计算前缀和数组 `he`，`he[i]` 表示 `a` 数组中前 `i` 个数的和。然后读入每个区间的左右端点 `l` 和 `r`，通过 `he[r] - he[l - 1]` 计算区间和，若大于 0 则累加到 `sum` 中。

### 最优关键思路或技巧
- **贪心策略**：只选择区间和大于 0 的区间，因为选择区间和为负数的区间会使最终结果变小。
- **前缀和算法**：通过预处理前缀和数组，可以在 $O(1)$ 时间内计算任意区间的和，将计算区间和的复杂度从 $O(n)$ 降低到 $O(1)$。

### 拓展思路
同类型题目通常会涉及区间和的计算以及根据某些条件选择区间的问题。类似的算法套路包括：
- 当需要频繁计算区间和时，优先考虑使用前缀和算法。
- 在选择区间时，根据具体问题的条件采用贪心策略，如选择和最大、长度最短等。

### 推荐题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：求连续子数组的最大和。
- [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)：涉及区间和与组合的问题。
- [P3131 [USACO16JAN]Subsequences Summing to Sevens S](https://www.luogu.com.cn/problem/P3131)：利用前缀和解决区间和的问题。

### 个人心得
部分题解提到数据范围小，暴力解法也能通过，但使用前缀和算法可以优化复杂度，在数据范围变大时更具优势。这提醒我们在解题时要考虑算法的复杂度，尽量选择更优的解法。 

---
处理用时：38.55秒
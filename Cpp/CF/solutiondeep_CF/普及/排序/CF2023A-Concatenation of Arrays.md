# 题目信息

# Concatenation of Arrays

## 题目描述

You are given $ n $ arrays $ a_1 $ , $ \ldots $ , $ a_n $ . The length of each array is two. Thus, $ a_i = [a_{i, 1}, a_{i, 2}] $ . You need to concatenate the arrays into a single array of length $ 2n $ such that the number of inversions $ ^{\dagger} $ in the resulting array is minimized. Note that you do not need to count the actual number of inversions.

More formally, you need to choose a permutation $ ^{\ddagger} $ $ p $ of length $ n $ , so that the array $ b = [a_{p_1,1}, a_{p_1,2}, a_{p_2, 1}, a_{p_2, 2}, \ldots, a_{p_n,1}, a_{p_n,2}] $ contains as few inversions as possible.

 $ ^{\dagger} $ The number of inversions in an array $ c $ is the number of pairs of indices $ i $ and $ j $ such that $ i < j $ and $ c_i > c_j $ .

 $ ^{\ddagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, we concatenated the arrays in the order $ 2, 1 $ . Let's consider the inversions in the resulting array $ b = [2, 3, 1, 4] $ :

- $ i = 1 $ , $ j = 3 $ , since $ b_1 = 2 > 1 = b_3 $ ;
- $ i = 2 $ , $ j = 3 $ , since $ b_2 = 3 > 1 = b_3 $ .

Thus, the number of inversions is $ 2 $ . It can be proven that this is the minimum possible number of inversions.

In the second test case, we concatenated the arrays in the order $ 3, 1, 2 $ . Let's consider the inversions in the resulting array $ b = [2, 1, 3, 2, 4, 3] $ :

- $ i = 1 $ , $ j = 2 $ , since $ b_1 = 2 > 1 = b_2 $ ;
- $ i = 3 $ , $ j = 4 $ , since $ b_3 = 3 > 2 = b_4 $ ;
- $ i = 5 $ , $ j = 6 $ , since $ b_5 = 4 > 3 = b_6 $ .

Thus, the number of inversions is $ 3 $ . It can be proven that this is the minimum possible number of inversions.

In the third test case, we concatenated the arrays in the order $ 4, 2, 1, 5, 3 $ .

## 样例 #1

### 输入

```
4
2
1 4
2 3
3
3 2
4 3
2 1
5
5 10
2 3
9 6
4 1
8 7
1
10 20```

### 输出

```
2 3 1 4
2 1 3 2 4 3
4 1 2 3 5 10 8 7 9 6
10 20```

# AI分析结果

### 题目内容中文重写
# 数组的连接

## 题目描述
给定 $n$ 个数组 $a_1, \ldots, a_n$，每个数组的长度为 2，即 $a_i = [a_{i, 1}, a_{i, 2}]$。你需要将这些数组连接成一个长度为 $2n$ 的单个数组，使得所得数组中的逆序对 $^{\dagger}$ 数量最少。注意，你不需要计算实际的逆序对数量。

更正式地说，你需要选择一个长度为 $n$ 的排列 $^{\ddagger}$ $p$，使得数组 $b = [a_{p_1,1}, a_{p_1,2}, a_{p_2, 1}, a_{p_2, 2}, \ldots, a_{p_n,1}, a_{p_n,2}]$ 包含的逆序对尽可能少。

$^{\dagger}$ 数组 $c$ 中的逆序对数量是满足 $i < j$ 且 $c_i > c_j$ 的索引对 $(i, j)$ 的数量。

$^{\ddagger}$ 长度为 $n$ 的排列是一个由从 1 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是一个排列（2 在数组中出现了两次），$[1,3,4]$ 也不是一个排列（$n = 3$ 但数组中有 4）。

## 说明/提示
在第一个测试用例中，我们按 2, 1 的顺序连接数组。让我们考虑所得数组 $b = [2, 3, 1, 4]$ 中的逆序对：
- $i = 1$，$j = 3$，因为 $b_1 = 2 > 1 = b_3$；
- $i = 2$，$j = 3$，因为 $b_2 = 3 > 1 = b_3$。

因此，逆序对的数量是 2。可以证明这是可能的最小逆序对数量。

在第二个测试用例中，我们按 3, 1, 2 的顺序连接数组。让我们考虑所得数组 $b = [2, 1, 3, 2, 4, 3]$ 中的逆序对：
- $i = 1$，$j = 2$，因为 $b_1 = 2 > 1 = b_2$；
- $i = 3$，$j = 4$，因为 $b_3 = 3 > 2 = b_4$；
- $i = 5$，$j = 6$，因为 $b_5 = 4 > 3 = b_6$。

因此，逆序对的数量是 3。可以证明这是可能的最小逆序对数量。

在第三个测试用例中，我们按 4, 2, 1, 5, 3 的顺序连接数组。

## 样例 #1
### 输入
```
4
2
1 4
2 3
3
3 2
4 3
2 1
5
5 10
2 3
9 6
4 1
8 7
1
10 20
```
### 输出
```
2 3 1 4
2 1 3 2 4 3
4 1 2 3 5 10 8 7 9 6
10 20
```

### 综合分析与结论
这些题解主要围绕如何对给定的长度为 2 的数组进行排序，使得连接后的数组逆序对最少。不同题解的思路和方法各有不同：
- **基于最大值和和的排序**：如 Eddie08012025 和 zengxuheng 的题解，通过比较数组元素的最大值和元素和来确定排序顺序。
- **基于最小值和最大值的排序**：aeiouaoeiu 和 Austin0116 的题解，以二元组的最小值为第一关键字，最大值为第二关键字进行升序排序。
- **基于和的排序**：CEFqwq 的题解，以数对元素和为关键字排序。
- **暴力计算逆序对**：wangyishan 的题解，通过暴力计算交换一对 `pair` 产生的逆序对数，并结合最小值较小的尽量放前面的原则排序。
- **计算可能贡献的逆序对**：Introl 的题解，计算每个数组可能贡献的逆序对数量，然后排序。
- **区间分析**：Louis_lxy 的题解，从区间包含和相交的角度分析逆序对的贡献，按左端点排序。

### 所选的题解
- **Eddie08012025（4星）**
    - **关键亮点**：思路清晰，通过分类讨论证明了排序规则的正确性，代码实现简洁。
    - **核心代码**：
```cpp
bool cmd(pair<int,int>a,pair<int,int>b){
    int a1=a.first,a2=a.second,b1=b.first,b2=b.second,cnt;
    int maxn=max({a1,a2,b1,b2});
    if((a1==maxn||a2==maxn)&&(b1==maxn||b2==maxn)){
        return (a1+a2)<(b1+b2);
    }else if(a1==maxn||a2==maxn){
        return 0;
    }else if(b1==maxn||b2==maxn){
        return 1;
    }
}
```
核心实现思想：先找出两个数对中的最大值，若两个数对都包含最大值，则比较数对元素和，和小的在前；若只有一个数对包含最大值，则该数对排在后面。

- **aeiouaoeiu（4星）**
    - **关键亮点**：通过分类讨论两个二元组的不同情况，得出按二元组最小值为第一关键字，最大值为第二关键字升序排序的结论，思路严谨。
    - **核心代码**：
```cpp
sort(id+1,id+1+n,[&](ll x,ll y){
    if(mn[x]==mn[y]) return mx[x]<mx[y];
    else return mn[x]<mn[y];
});
```
核心实现思想：使用 lambda 表达式定义排序规则，先比较二元组的最小值，若相等则比较最大值，升序排序。

- **Austin0116（4星）**
    - **关键亮点**：通过贪心思想，排除了错误的贪心方法，确定了正确的排序规则，代码简洁。
    - **核心代码**：
```cpp
struct ha{
    int x,y;
    inline bool operator < (const ha &o) const{
        if(min(x,y)!=min(o.x,o.y)) return min(x,y)<min(o.x,o.y);
        return max(x,y)<max(o.x,o.y);
    }
};
```
核心实现思想：重载小于运算符，先比较数对的最小值，若不相等则最小值小的在前；若相等则比较最大值，最大值小的在前。

### 最优关键思路或技巧
- **贪心思想**：通过局部最优的排序规则来达到全局逆序对最少的目的，如基于最大值、和、最小值等的排序规则。
- **分类讨论**：对不同情况的数对进行分类讨论，证明排序规则的正确性。

### 可拓展之处
同类型题可能会改变数组的长度或增加其他限制条件，类似算法套路可应用于其他需要通过排序来优化某个指标的问题，如通过邻项交换法确定最优排列顺序。

### 洛谷相似题目
1. P1080 国王游戏：同样涉及通过排序来优化某个指标，使用邻项交换法。
2. ABC366F：与本题思路类似，通过合理排序来达到最优结果。
3. P1223 排队接水：通过排序使得总等待时间最短，也是贪心排序的应用。

### 个人心得摘录与总结
- **Austin0116**：提到一开始有两种贪心思路，一种错误一种正确，错误的贪心方法没有传递性，并给出了反例。总结是在使用贪心算法时，要确保贪心策略具有传递性，否则可能得到错误结果。 

---
处理用时：52.34秒
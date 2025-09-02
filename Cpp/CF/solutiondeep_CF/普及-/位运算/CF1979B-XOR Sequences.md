# 题目信息

# XOR Sequences

## 题目描述

You are given two distinct non-negative integers $ x $ and $ y $ . Consider two infinite sequences $ a_1, a_2, a_3, \ldots $ and $ b_1, b_2, b_3, \ldots $ , where

- $ a_n = n \oplus x $ ;
- $ b_n = n \oplus y $ .

Here, $ x \oplus y $ denotes the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operation of integers $ x $ and $ y $ .

For example, with $ x = 6 $ , the first $ 8 $ elements of sequence $ a $ will look as follows: $ [7, 4, 5, 2, 3, 0, 1, 14, \ldots] $ . Note that the indices of elements start with $ 1 $ .

Your task is to find the length of the longest common subsegment $ ^\dagger $ of sequences $ a $ and $ b $ . In other words, find the maximum integer $ m $ such that $ a_i = b_j, a_{i + 1} = b_{j + 1}, \ldots, a_{i + m - 1} = b_{j + m - 1} $ for some $ i, j \ge 1 $ .

 $ ^\dagger $ A subsegment of sequence $ p $ is a sequence $ p_l,p_{l+1},\ldots,p_r $ , where $ 1 \le l \le r $ .

## 说明/提示

In the first test case, the first $ 7 $ elements of sequences $ a $ and $ b $ are as follows:

 $ a = [1, 2, 3, 4, 5, 6, 7,\ldots] $

 $ b = [0, 3, 2, 5, 4, 7, 6,\ldots] $

It can be shown that there isn't a positive integer $ k $ such that the sequence $ [k, k + 1] $ occurs in $ b $ as a subsegment. So the answer is $ 1 $ .

In the third test case, the first $ 20 $ elements of sequences $ a $ and $ b $ are as follows:

 $ a = [56, 59, 58, 61, 60, 63, 62, 49, 48, 51, 50, 53, 52, 55, 54, \textbf{41, 40, 43, 42}, 45, \ldots] $

 $ b = [36, 39, 38, 33, 32, 35, 34, 45, 44, 47, 46, \textbf{41, 40, 43, 42}, 53, 52, 55, 54, 49, \ldots] $

It can be shown that one of the longest common subsegments is the subsegment $ [41, 40, 43, 42] $ with a length of $ 4 $ .

## 样例 #1

### 输入

```
4
0 1
12 4
57 37
316560849 14570961```

### 输出

```
1
8
4
33554432```

# AI分析结果

### 题目中文重写
## XOR 序列

### 题目描述
给定两个不同的非负整数 $x$ 和 $y$。考虑两个无限序列 $a_1, a_2, a_3, \ldots$ 和 $b_1, b_2, b_3, \ldots$，其中：
- $a_n = n \oplus x$；
- $b_n = n \oplus y$。

这里，$x \oplus y$ 表示整数 $x$ 和 $y$ 的[按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)运算。

例如，当 $x = 6$ 时，序列 $a$ 的前 8 个元素如下：$[7, 4, 5, 2, 3, 0, 1, 14, \ldots]$。注意，元素的索引从 1 开始。

你的任务是找出序列 $a$ 和 $b$ 的最长公共子段 $^\dagger$ 的长度。换句话说，找到最大的整数 $m$，使得对于某些 $i, j \geq 1$，有 $a_i = b_j, a_{i + 1} = b_{j + 1}, \ldots, a_{i + m - 1} = b_{j + m - 1}$。

$^\dagger$ 序列 $p$ 的子段是指序列 $p_l,p_{l+1},\ldots,p_r$，其中 $1 \leq l \leq r$。

### 说明/提示
在第一个测试用例中，序列 $a$ 和 $b$ 的前 7 个元素如下：
$a = [1, 2, 3, 4, 5, 6, 7,\ldots]$
$b = [0, 3, 2, 5, 4, 7, 6,\ldots]$

可以证明，不存在正整数 $k$ 使得序列 $[k, k + 1]$ 作为子段出现在 $b$ 中。因此，答案是 1。

在第三个测试用例中，序列 $a$ 和 $b$ 的前 20 个元素如下：
$a = [56, 59, 58, 61, 60, 63, 62, 49, 48, 51, 50, 53, 52, 55, 54, \textbf{41, 40, 43, 42}, 45, \ldots]$
$b = [36, 39, 38, 33, 32, 35, 34, 45, 44, 47, 46, \textbf{41, 40, 43, 42}, 53, 52, 55, 54, 49, \ldots]$

可以证明，其中一个最长的公共子段是子段 $[41, 40, 43, 42]$，长度为 4。

### 样例 #1
#### 输入
```
4
0 1
12 4
57 37
316560849 14570961
```
#### 输出
```
1
8
4
33554432
```

### 题解综合分析与结论
- **思路对比**：大部分题解都围绕异或运算的性质展开，通过分析 $x$ 和 $y$ 异或结果的二进制特征来确定最长公共子段的长度。部分题解通过观察样例找规律得出结论，部分题解从异或运算的原理进行推导。
- **算法要点**：核心算法是计算 $x \oplus y$ 的最低位 1 及其后面所有 0 构成的数，即 `lowbit(x ^ y)`。不同题解在实现 `lowbit` 函数时方式略有不同，但本质相同。
- **解决难点**：难点在于理解为什么最长公共子段的长度与 $x \oplus y$ 的最低位 1 有关。各题解通过异或运算的性质、二进制位的分析等方式进行解释。

### 高评分题解
- **Little_x_starTYJ（5星）**
    - **关键亮点**：思路清晰，详细解释了异或运算的性质以及为什么答案是 `lowbit(x ^ y)`，代码简洁易懂。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int lowbit(int x) {
    return x & (-x);
}
signed main() {
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int x, y;
        cin >> x >> y;
        cout << lowbit(x ^ y) << endl;
    }
    return 0;
}
```
- **liaoxingrui（4星）**
    - **关键亮点**：清晰阐述了最长公共子段的起始和结束条件，结合异或运算的性质得出答案，代码简洁。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y;
inline int lowbit(int x){
    return (-x)&x;
}
int main(){
    cin>>n;
    while(n--){
        cin>>x>>y;
        cout<<lowbit(x^y)<<endl;
    }
    return 0;
}
```
- **Scean_Tong（4星）**
    - **关键亮点**：先分析枚举法的超时问题，再引入异或性质进行优化，详细解释了 `lowbit(x ^ y)` 的含义，代码规范。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
int lowbit(int x){
    return x&(-x);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        int x,y;
        cin>>x>>y;
        cout<<lowbit(x^y)<<'\n';        
    } 
    return 0;
}
```

### 最优关键思路或技巧
- **思维方式**：通过分析异或运算的性质，将问题转化为寻找 $x \oplus y$ 的最低位 1，避免了直接枚举的高时间复杂度。
- **代码实现技巧**：使用 `lowbit` 函数快速计算一个数二进制下最低位 1 及其后面所有 0 构成的数。

### 可拓展之处
同类型题可能会涉及更多复杂的位运算，或者结合其他数据结构和算法。类似算法套路可用于解决与二进制位相关的问题，如判断两个数在二进制下某几位是否相同、寻找二进制下的特殊位等。

### 洛谷相似题目推荐
- [P1837 连通图](https://www.luogu.com.cn/problem/P1837)：涉及位运算和图论知识。
- [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)：主要考察位运算的应用。
- [P3811 【模板】乘法逆元](https://www.luogu.com.cn/problem/P3811)：虽然主要是数论问题，但部分解法会用到位运算优化。

### 个人心得摘录与总结
- **ny_Dacong**：认为部分题解表述不够通俗，自己以通俗为主进行题解，强调证明可能不严谨，语言啰嗦。总结：在学习过程中，不同的表述方式有助于理解问题，对于复杂问题可以先从通俗的角度入手。
- **_Dynamic_Programming**：表示做题时没有思路，通过看样例猜出做法。总结：在没有思路时，观察样例找规律是一种有效的解题方法，但后续需要对结论进行证明。

---
处理用时：38.72秒
# 题目信息

# Sum

## 题目描述

Vasya has found a piece of paper with an array written on it. The array consists of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Vasya noticed that the following condition holds for the array $ a_{i}<=a_{i+1}<=2·a_{i} $ for any positive integer $ i $ ( $ i&lt;n $ ).

Vasya wants to add either a "+" or a "-" before each number of array. Thus, Vasya will get an expression consisting of $ n $ summands. The value of the resulting expression is the sum of all its elements. The task is to add signs "+" and "-" before each number so that the value of expression $ s $ meets the limits $ 0<=s<=a_{1} $ . Print a sequence of signs "+" and "-", satisfying the given limits. It is guaranteed that the solution for the problem exists.

## 样例 #1

### 输入

```
4
1 2 3 5
```

### 输出

```
+++-```

## 样例 #2

### 输入

```
3
3 3 5
```

### 输出

```
++-```

# AI分析结果

### 题目内容
# 和

## 题目描述
瓦夏发现了一张写有数组的纸。该数组由 $n$ 个整数 $a_{1},a_{2},\cdots,a_{n}$ 组成。瓦夏注意到对于该数组，对于任意正整数 $i$（$i < n$），都满足 $a_{i} \leq a_{i + 1} \leq 2 \cdot a_{i}$ 。

瓦夏想在数组的每个数前添加一个“$+$”或“$-$”。这样，瓦夏将得到一个由 $n$ 个加数组成的表达式。所得表达式的值就是其所有元素的和。任务是在每个数前添加“$+$”和“$-$”号，使得表达式的值 $s$ 满足 $0 \leq s \leq a_{1}$ 。输出满足给定限制的“$+$”和“$-$”符号序列。保证该问题有解。

## 样例 #1
### 输入
```
4
1 2 3 5
```
### 输出
```
+++-
```

## 样例 #2
### 输入
```
3
3 3 5
```
### 输出
```
++-
```

### 算法分类
贪心

### 题解综合分析与结论
两位作者的题解思路本质都是贪心策略。123456zmy 的题解从后往前贪心，通过比较当前数与后续数和的关系来确定符号，并且通过数组记录符号状态后统一输出；_acat_ 的题解则是从数学角度分析，利用数组元素间的大小关系，通过从末尾开始大的减小的方式保证最终结果在范围内，两种方法都利用了题目中数组元素的特殊性质。123456zmy 的题解代码实现较为清晰，思路也容易理解；_acat_ 的题解虽然思路有一定创新性，但在代码实现上缺失，且分析过程相对复杂。整体来看，123456zmy 的题解质量更高。

### 所选的题解
- **123456zmy 题解**
  - **星级**：4 星
  - **关键亮点**：思路清晰，从后往前贪心，利用数组记录符号状态方便统一输出。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100001],s,ans[100001],b[100001],tmp;
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    s=a[n];
    for(int i=n - 1;i;i--)
    {
        if(s>a[i])ans[i]=1;
        else b[i + 1]=1;
        s=abs(s - a[i]);
    }
    for(int i=1;i<=n;i++)tmp^=b[i],putchar(tmp^ans[i]?'-':'+');
    return 0;
}
```
  - **核心实现思想**：从后往前遍历数组，若当前数之后的和大于当前数，则当前数符号设为 `-` 记录在 `ans` 数组；否则将当前数之后的数符号反转记录在 `b` 数组，同时更新和 `s`。最后通过异或操作根据 `ans` 和 `b` 数组确定每个数最终符号并输出。

### 最优关键思路或技巧
利用数组元素 $a_{i} \leq a_{i + 1} \leq 2a_{i}$ 的性质，从后往前贪心确定每个数的符号，巧妙利用数组记录符号状态以简化输出操作。

### 可拓展之处
此类题目属于利用数列特殊性质进行贪心构造的类型。相似套路是根据给定数列的限制条件，从某个方向（如本题从后往前）进行贪心决策，通过不断调整符号使结果满足范围要求。

### 洛谷相似题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)

---
处理用时：40.76秒
# 题目信息

# Clear Symmetry

## 题目描述

Consider some square matrix $ A $ with side $ n $ consisting of zeros and ones. There are $ n $ rows numbered from $ 1 $ to $ n $ from top to bottom and $ n $ columns numbered from $ 1 $ to $ n $ from left to right in this matrix. We'll denote the element of the matrix which is located at the intersection of the $ i $ -row and the $ j $ -th column as $ A_{i,j} $ .

Let's call matrix $ A $ clear if no two cells containing ones have a common side.

Let's call matrix $ A $ symmetrical if it matches the matrices formed from it by a horizontal and/or a vertical reflection. Formally, for each pair $ (i,j) $ $ (1<=i,j<=n) $ both of the following conditions must be met: $ A_{i,j}=A_{n-i+1,j} $ and $ A_{i,j}=A_{i,n-j+1} $ .

Let's define the sharpness of matrix $ A $ as the number of ones in it.

Given integer $ x $ , your task is to find the smallest positive integer $ n $ such that there exists a clear symmetrical matrix $ A $ with side $ n $ and sharpness $ x $ .

## 说明/提示

The figure below shows the matrices that correspond to the samples:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF201A/4a353f15397909088e2fcb0cff23c93ecb30c822.png)

## 样例 #1

### 输入

```
4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
9
```

### 输出

```
5
```

# AI分析结果

### 题目内容
# 清晰对称

## 题目描述
考虑一个边长为 $n$ 的方阵 $A$，其元素由 $0$ 和 $1$ 组成。该矩阵有 $n$ 行，从上到下编号为 $1$ 到 $n$；有 $n$ 列，从左到右编号为 $1$ 到 $n$。我们将位于第 $i$ 行和第 $j$ 列交叉处的矩阵元素记为 $A_{i,j}$。

如果任意两个值为 $1$ 的单元格都没有公共边，我们称矩阵 $A$ 是清晰的。

如果矩阵 $A$ 与通过水平和/或垂直反射形成的矩阵相同，我们称矩阵 $A$ 是对称的。形式上，对于每一对 $(i, j)$（$1 \leq i, j \leq n$），必须满足以下两个条件：$A_{i,j} = A_{n - i + 1,j}$ 且 $A_{i,j} = A_{i,n - j + 1}$。

我们将矩阵 $A$ 的锐度定义为其中 $1$ 的数量。

给定整数 $x$，你的任务是找到最小的正整数 $n$，使得存在一个边长为 $n$、锐度为 $x$ 的清晰对称矩阵 $A$。

## 说明/提示
下图展示了与示例对应的矩阵：
![示例矩阵](https://cdn.luogu.com.cn/upload/vjudge_pic/CF201A/4a353f15397909088e2fcb0cff23c93ecb30c822.png)

## 样例 #1
### 输入
```
4
```
### 输出
```
3
```

## 样例 #2
### 输入
```
9
```
### 输出
```
5
```

### 算法分类
数学

### 题解综合分析与结论
这两道题解思路一致，都基于一个关键结论：一个 $(2*i + 1)*(2*i + 1)$ 的对称矩阵，最多容纳的 $1$ 的数量为 $((2*i + 1)*(2*i + 1)+1)/2$ ，答案即为 $2*i + 1$ 。不同在于实现方式，“流绪” 的题解给出了具体代码实现，通过预处理将不同 $i$ 对应的容纳 $1$ 的最大数量存入数组，然后通过遍历数组找到满足条件的最小 $n$ ；“引领天下” 的题解未给出代码，只是点明暴力求解思路，并指出 $i = 3$ 时需特判。

### 所选的题解
- **作者：流绪 (4星)**
    - **关键亮点**：给出完整代码，实现思路清晰，通过预处理和遍历数组实现快速查询。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long 
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define mod 10
using namespace std;
int a[maxn];
int main()
{
    ios::sync_with_stdio(false);
    int x;
    cin >> x;
    if(x==3)
        cout << 5;
    else
    {
        int p=0;
        for(int i=0;p<200;i++)
        { 
            p = ((2*i+1)*(2*i+1)+1)/2;
            a[i]  = p; 
        } 
        for(int i=0;;i++)
            if(a[i]>=x)
            {
                p=i;
                break;
            }
        cout << 2*p+1;
    }
    return 0; 
}  
```
核心实现思想：先预处理不同 $i$ 对应的 $(2*i + 1)*(2*i + 1)$ 对称矩阵容纳 $1$ 的最大数量并存入数组 `a` ，输入 $x$ 后，遍历数组 `a` 找到第一个大于等于 $x$ 的元素，其下标 $i$ 对应的 $2*i + 1$ 即为答案，同时对 $x = 3$ 进行特判。

### 最优关键思路或技巧
通过数学推导得出 $(2*i + 1)*(2*i + 1)$ 对称矩阵容纳 $1$ 的最大数量公式，利用这个公式进行预处理和查找，简化问题求解过程。

### 拓展思路
此类题目属于数学规律推导与应用类型，遇到类似需要寻找矩阵或图形某种特性与数量关系的题目，都可以尝试通过数学方法推导规律，再依据规律进行代码实现。

### 洛谷相似题目推荐
- [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)：通过找规律来计算满足特定条件的数的个数，考察对数学规律的发现与应用。
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：需要根据等差数列求和公式等数学知识来解决连续自然数和的问题，与本题类似，都需挖掘数学关系求解。
- [P2669 金币](https://www.luogu.com.cn/problem/P2669)：通过寻找金币数量变化规律，利用数学方法计算总金币数，锻炼数学思维与编程实现能力。 

---
处理用时：42.16秒
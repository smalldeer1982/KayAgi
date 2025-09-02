# 题目信息

# Ehab and a Special Coloring Problem

## 题目描述

You're given an integer $ n $ . For every integer $ i $ from $ 2 $ to $ n $ , assign a positive integer $ a_i $ such that the following conditions hold:

- For any pair of integers $ (i,j) $ , if $ i $ and $ j $ are coprime, $ a_i \neq a_j $ .
- The maximal value of all $ a_i $ should be minimized (that is, as small as possible).

A pair of integers is called [coprime](https://en.wikipedia.org/wiki/Coprime_integers) if their [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) is $ 1 $ .

## 说明/提示

In the first example, notice that $ 3 $ and $ 4 $ are coprime, so $ a_3 \neq a_4 $ . Also, notice that $ a=[1,2,3] $ satisfies the first condition, but it's not a correct answer because its maximal value is $ 3 $ .

## 样例 #1

### 输入

```
4
```

### 输出

```
1 2 1 ```

## 样例 #2

### 输入

```
3
```

### 输出

```
2 1```

# AI分析结果

### 题目内容
# Ehab和一个特殊的染色问题

## 题目描述
给定一个整数 $n$ 。对于从 $2$ 到 $n$ 的每个整数 $i$ ，分配一个正整数 $a_i$ ，使得以下条件成立：
- 对于任意一对整数 $(i,j)$ ，如果 $i$ 和 $j$ 互质，那么 $a_i \neq a_j$ 。
- 所有 $a_i$ 的最大值应最小化（即尽可能小）。

一对整数如果它们的[最大公约数](https://en.wikipedia.org/wiki/Greatest_common_divisor)为 $1$ ，则称这对整数是[互质的](https://en.wikipedia.org/wiki/Coprime_integers)。

## 说明/提示
在第一个示例中，注意 $3$ 和 $4$ 互质，所以 $a_3 \neq a_4$ 。另外，注意 $a=[1,2,3]$ 满足第一个条件，但它不是正确答案，因为其最大值为 $3$ 。

## 样例 #1
### 输入
```
4
```
### 输出
```
1 2 1 
```
## 样例 #2
### 输入
```
3
```
### 输出
```
2 1
```
### 算法分类
数学（质数相关性质应用）

### 题解综合分析与结论
所有题解思路本质相同，均基于埃氏筛法思想。核心思路是利用若两数不互质，可令其对应 $a$ 值相同，以最小化 $a$ 序列最大值。具体操作是从 $2$ 开始遍历，若当前数未被赋值（说明是质数或与之前数互质），则赋予新值，并将其倍数位置也赋为该值。各题解主要差异在代码实现细节，如输入方式、变量命名、代码风格等。

### 所选的题解
 - **作者：I_like_magic (4星)**
    - **关键亮点**：思路清晰，代码简洁明了，直接基于埃氏筛法思想实现，对埃氏筛法应用描述清晰。
    - **重点代码**：
```cpp
#include<iostream>
using namespace std;
int n;
int a[100005];
int c;
signed main(){
    cin>>n;
    for(int i=2;i<=n;i++){
        if(a[i])continue; //非质数
        c++; //一个新数字
        for(int j=1;j*i<=n;j++){
            a[i*j]=c; //倍数赋值为 c
        }
    }
    for(int i=2;i<=n;i++){ //从 2 开始
        cout<<a[i]<<" ";
    }
    return 0; //完美收尾
}
```
核心实现思想：外层循环遍历 $2$ 到 $n$ ，若当前数已被赋值则跳过；否则给其及倍数赋予新值，最后输出结果。
 - **作者：Provicy (4星)**
    - **关键亮点**：对思路的解释较为详细，不仅阐述做法，还感性分析了正确性，代码使用了快速读入优化。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
#define ri register
using namespace std; const int N=200010;
inline int read()
{
    int s=0,w=1; ri char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1; ch=getchar(); }
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar(); return s*w;
}
int n,p[N],cnt;
int main()
{
    n=read();
    for(ri int i=2;i<=n;i++)
    {
        if(p[i]) continue; cnt++;
        for(ri int j=i;j<=n;j+=i) p[j]=cnt;
    }
    for(ri int i=2;i<=n;i++) printf("%d ",p[i]); puts("");
    return 0;
}
```
核心实现思想：通过快速读入获取 $n$ ，然后类似埃氏筛法，遍历 $2$ 到 $n$ ，未赋值的数（质数或与之前数互质）赋予新值并更新其倍数，最后输出结果。
 - **作者：幽界の冥神 (4星)**
    - **关键亮点**：先给出埃氏筛法模板，便于读者理解，对类筛法思路解释详细，代码简洁。
    - **重点代码**：
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#define N 2000005

using namespace std;

int n, a[N], num;
int main () {
    scanf ("%d", &n);
    for (int i = 2; i <= n; ++i)
        if (!a[i]) {
            ++num;
            for (int j = i; j <= n; j += i) a[j] = num;
        }
    for (int i = 2; i <= n; ++i)
        printf("%d ", a[i]);
    return 0;
}
```
核心实现思想：读入 $n$ 后，遍历 $2$ 到 $n$ ，未赋值的数赋予新值并更新其倍数，最后输出结果。

### 最优关键思路或技巧
利用质数性质及埃氏筛法思想，通过对不互质数赋予相同值来最小化结果序列的最大值。这种基于数论性质的构造方法是解决本题的关键。

### 可拓展思路
此类题目通常围绕数论中质数、互质等概念展开，类似套路是利用数的整除关系和互质关系来构造满足条件的序列。常见拓展方向是增加限制条件，如对 $a_i$ 的取值范围进一步限制，或改变互质判断条件等。

### 洛谷相似题目推荐
 - **P1075 [NOIP2012 普及组] 质因数分解**：通过对一个数进行质因数分解，考察对质数概念及相关算法的理解。
 - **P2312 [NOIP2014 普及组] 解方程**：涉及到对多项式方程根的求解，需要运用数论知识，与本题一样考察对数学概念在编程中的应用。
 - **P1835 素数密度**：要求计算给定区间内素数的个数，与本题类似，都需要对质数相关算法进行运用。 

---
处理用时：68.72秒
# 题目信息

# Array

## 题目描述

Chris the Rabbit has been interested in arrays ever since he was a child. At the moment he is researching arrays with the length of $ n $ , containing only integers from $ 1 $ to $ n $ . He is not good at math, that's why some simple things drive him crazy. For example, yesterday he grew keen on counting how many different beautiful arrays there are. Chris thinks that an array is beautiful if it meets one of the two conditions:

- each elements, starting from the second one, is no more than the preceding one
- each element, starting from the second one, is no less than the preceding one

Having got absolutely mad at himself and at math, Chris came to Stewie and Brian to ask them for help. However, they only laughed at him and said that the answer is too simple and not interesting. Help Chris the Rabbit to find the answer at last.

## 样例 #1

### 输入

```
2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
```

### 输出

```
17
```

# AI分析结果

### 题目中文重写
## 数组

### 题目描述
兔子克里斯从小就对数组感兴趣。目前，他正在研究长度为 $n$ 的数组，这些数组仅包含从 $1$ 到 $n$ 的整数。他不擅长数学，这就是为什么一些简单的事情会让他抓狂。例如，昨天他热衷于计算有多少个不同的漂亮数组。克里斯认为，如果一个数组满足以下两个条件之一，那么它就是漂亮的：
- 从第二个元素开始，每个元素都不大于前一个元素；
- 从第二个元素开始，每个元素都不小于前一个元素。

克里斯对自己和数学感到无比抓狂，于是他去找斯图尔特和布莱恩寻求帮助。然而，他们只是嘲笑他，说答案太简单了，没什么意思。最后，请帮助兔子克里斯找到答案。

### 样例 #1
#### 输入
```
2
```
#### 输出
```
4
```

### 样例 #2
#### 输入
```
3
```
#### 输出
```
17
```

### 题解综合分析与结论
这些题解主要围绕如何计算满足特定条件（单调不降或单调不升）的长度为 $n$ 且元素范围在 $1$ 到 $n$ 的数组的数量。整体思路可分为组合数学和动态规划两类。
- **组合数学思路**：多数题解采用此思路，通过将问题转化为组合问题求解。如将数组表示为集合，利用插板法计算组合数，得出单调不降或单调不升序列的数量为 $C_{2n - 1}^n$ ，最终答案为 $2C_{2n - 1}^n - n$ 。
- **动态规划思路**：设 $f[i][j]$ 表示前 $i$ 个数到达最后一位是 $j$ 的递增序列的方案数，通过状态转移方程 $f[i][j] = \sum_{k = 1}^{j}f[i - 1][k]$ 计算，后发现其与杨辉三角的关系，得出结果。

**算法要点对比**：
|思路|算法要点|难点|
| ---- | ---- | ---- |
|组合数学|将问题转化为插板法问题，计算组合数 $C_{2n - 1}^n$ ，考虑重复情况减去 $n$ |组合问题的转化，涉及除法取模时逆元的计算|
|动态规划|定义状态 $f[i][j]$ ，推导状态转移方程，发现与杨辉三角的联系|状态转移方程的推导，打表发现规律并优化时间复杂度|

### 所选题解
1. **作者：Prurite (5星)**
    - **关键亮点**：思路清晰，将问题进行两次转化，详细阐述了从原问题到组合问题的推导过程，对插板法的解释直观易懂。
    - **核心代码思想**：虽未给出代码，但思路明确，通过计算组合数 $C_{2n - 1}^n$ ，最终得出答案 $2C_{2n - 1}^n - n$ ，涉及除法取模时需使用逆元。
2. **作者：pufanyi (4星)**
    - **关键亮点**：从动态规划角度入手，通过打表发现规律，将问题与杨辉三角联系起来，优化了时间复杂度，代码实现完整。
    - **核心代码**：
```cpp
#include <fstream>
using namespace std;
typedef long long LL;
ifstream fin("pretty.in");
ofstream fout("pretty.out");
inline LL pow(LL x, LL y, LL mod) {
    LL ans = 1;
    for(; y; y >>= 1, x = (x*x)%mod)
        if(y & 1)
            ans = (ans*x) % mod;
    return ans % mod;
}
const LL mod = 1000000007;
const int maxn = 100005;
LL fac[maxn<<1];
int main() {
    LL n;
    fin >> n;
    fac[0] = 1;
    for(int i = 1; i <= (n<<1); ++i)
        fac[i] = fac[i-1] * i % mod;
    fout << (fac[n<<1]* pow(fac[n]*fac[n]%mod, mod-2, mod)) % mod - n << endl;
    return 0;
}
```
    - **核心代码思想**：先预处理阶乘，再用快速幂计算逆元，根据组合数公式 $C_{2n}^n$ 计算结果，最后减去 $n$ 得到最终答案。
3. **作者：Ryan_Adam (4星)**
    - **关键亮点**：思路简洁明了，直接指出问题的本质，将问题转化为插板法经典例题，快速得出答案。
    - **核心代码思想**：虽未给出代码，但明确指出输出 $2\binom{2n - 1}{n} - n$ 即可，强调了问题的关键转化。

### 最优关键思路或技巧
- **问题转化思维**：将原问题转化为组合问题或与杨辉三角相关的问题，简化计算。
- **插板法**：在组合数学中，通过插板法将分配问题转化为组合数计算。
- **打表找规律**：在动态规划中，通过打表发现状态转移与杨辉三角的关系，优化时间复杂度。

### 可拓展之处
同类型题可能会改变数组元素的范围、长度或条件，如元素范围变为 $1$ 到 $m$ ，或条件变为满足某种特定的单调性等。类似算法套路可用于解决其他组合分配问题，如将 $m$ 个相同的球放入 $n$ 个不同的盒子，每个盒子允许为空等问题。

### 洛谷相似题目推荐
1. [P1833 樱花](https://www.luogu.com.cn/problem/P1833)：涉及组合数学和动态规划的综合应用。
2. [P2822 组合数问题](https://www.luogu.com.cn/problem/P2822)：主要考察组合数的计算和取模。
3. [P3197 [HNOI2008]越狱](https://www.luogu.com.cn/problem/P3197)：需要运用组合数学和快速幂解决问题。

### 个人心得摘录与总结
- **作者：pufanyi**：一开始用暴力打表发现规律，没想到可以进一步优化，最后发现与杨辉三角的关系，优化了时间复杂度。总结为在解题过程中可通过打表找规律，再深入分析规律进行优化。
- **作者：蒟蒻丁**：被之前的卡特兰数误导，浪费了很多时间。提醒我们在解题时不要受以往经验的局限，要从问题本身出发思考。 

---
处理用时：34.41秒
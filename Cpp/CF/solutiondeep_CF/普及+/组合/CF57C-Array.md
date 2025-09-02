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

### 题目翻译
## 数组

### 题目描述
兔子克里斯从小就对数组感兴趣。目前，他正在研究长度为 $n$ 的数组，这些数组仅包含从 $1$ 到 $n$ 的整数。他不擅长数学，因此一些简单的事情也会让他抓狂。例如，昨天他热衷于计算有多少个不同的“美丽数组”。克里斯认为，如果一个数组满足以下两个条件之一，那么它就是美丽的：
- 从第二个元素开始，每个元素都不大于前一个元素；
- 从第二个元素开始，每个元素都不小于前一个元素。

克里斯对自己和数学感到无比抓狂，于是他去找斯图伊和布莱恩寻求帮助。然而，他们只是嘲笑他，并说答案太简单，没什么意思。请帮助兔子克里斯最终找到答案。

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
- **思路对比**：大部分题解都利用了单调不降和单调不升序列的对称性，先计算单调不降序列的数量，再乘以 2 并减去重复计算的全部相同元素的序列数量（共 $n$ 种）。不同题解在计算单调不降序列数量时方法不同，如组合数学的插板法、动态规划、构建等价数组等。
- **算法要点**：
    - **组合数学插板法**：将问题转化为 $n$ 个 1 插入 $n - 1$ 个隔板的方案数，得到 $C_{2n - 1}^n$。
    - **动态规划**：设 $f[i][j]$ 表示前 $i$ 个数到达最后一位是 $j$ 的递增序列的方案数，通过状态转移方程 $f[i][j] = \sum_{k = 1}^{j}f[i - 1][k]$ 计算，发现其结果与杨辉三角有关，进而得到组合数公式。
    - **构建等价数组**：通过对原数组进行变换，如 $b_i = a_i + i$，将问题转化为组合数问题。
- **解决难点**：本题的难点在于如何将原问题转化为可计算的组合数学或动态规划问题，以及处理组合数计算中的除法取模问题，大部分题解使用逆元（如费马小定理）来解决。

### 高评分题解
1. **作者：Prurite（5星）**
    - **关键亮点**：思路清晰，详细阐述了两次转化过程，将原问题逐步转化为组合数学的插板法问题，最后得出答案公式 $2C_{2n - 1}^n - n$。
    - **核心代码思想**：虽然未给出代码，但思路明确，可根据组合数公式和逆元计算答案。
2. **作者：pufanyi（4星）**
    - **关键亮点**：先使用动态规划暴力求解，通过打表发现规律与杨辉三角有关，进而推导出组合数公式 $2C_{2n}^n - n$，并给出了完整代码。
    - **核心代码**：
```cpp
#include <fstream>
using namespace std;
typedef long long LL;
ifstream fin("pretty.in");
ofstream fout("pretty.out");
inline LL pow(LL x, LL y, LL mod) {
    LL ans = 1;
    for (; y; y >>= 1, x = (x * x) % mod)
        if (y & 1)
            ans = (ans * x) % mod;
    return ans % mod;
}
const LL mod = 1000000007;
const int maxn = 100005;
LL fac[maxn << 1];
int main() {
    LL n;
    fin >> n;
    fac[0] = 1;
    for (int i = 1; i <= (n << 1); ++i)
        fac[i] = fac[i - 1] * i % mod;
    fout << (fac[n << 1] * pow(fac[n] * fac[n] % mod, mod - 2, mod)) % mod - n << endl;
    return 0;
}
```
3. **作者：codecode（4星）**
    - **关键亮点**：通过构建等价数组 $b_i = a_i + i$，将问题转化为组合数问题，得出答案公式 $2C_{2n - 1}^n - n = C_{2n}^n - n$，并给出了预处理逆元计算组合数的代码。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 233;
int n, ans = 1, et[maxn];
signed main() {
    cin >> n;
    et[1] = 1;
    for (int i = 2; i <= n; i++)
        et[i] = (mod - mod / i) * et[mod % i] % mod; // 预处理逆元
    for (int i = 1; i <= n; i++)
        ans = ans * et[i] % mod * (n + i) % mod; // 暴力组合数
    cout << ((ans - n) % mod + mod) % mod;
    return 0;
}
```

### 最优关键思路或技巧
- **转化思想**：将原问题转化为组合数学或动态规划问题，如插板法、构建等价数组等，简化问题的求解。
- **对称性利用**：利用单调不降和单调不升序列的对称性，只计算一种情况，再通过简单的计算得到最终答案。
- **逆元处理**：在组合数计算中，使用逆元解决除法取模问题，保证计算的正确性。

### 可拓展之处
同类型题或类似算法套路：
- 其他组合数学问题，如将 $m$ 个相同元素分成 $n$ 组，每组元素个数有一定限制的问题。
- 动态规划问题，如状态转移方程与杨辉三角有关的问题。

### 洛谷相似题目推荐
1. [P1873 砍树](https://www.luogu.com.cn/problem/P1873)：涉及二分查找和组合数学思想。
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)：卡特兰数相关问题，与组合数学有关。
3. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：动态规划问题，可锻炼状态转移方程的推导能力。

### 个人心得摘录与总结
- **作者：pufanyi**：先使用暴力动态规划求解，通过打表发现规律，避免了复杂的数学推导，体现了从简单到复杂、从实践中发现规律的解题思路。
- **作者：蒟蒻丁**：被之前的卡特兰数误导，走了弯路，提醒我们在解题时要避免思维定式，尝试不同的思路。

---
处理用时：35.56秒
# 题目信息

# PLEASE

## 题目描述

正如我们所知道的，Barney的工作是"PLEASE"并且ta工作时不需要做太多事情。这就是ta开始玩"cups and key"的原因。在这个游戏中有三个完全相同的杯子从左到右排成一行。最初，通往Barney心房的钥匙在中间的杯子下面



游戏总共有$n$个回合，每个回合中，Barney等概率地选择两侧杯子的其中一个与中间的杯子交换位置，钥匙始终在原来的杯子中



游戏结束后，Barney要求一位女装大佬（就是你）答出钥匙在中间杯子中的概率



由于回合非常多，ta给了你一个数组`a[k]`，$n=\prod_{i=1}^k a_i$



最后的答案化为形如`p/q`的最简分数形式后，分子分母同对$1e9+7$取模

## 样例 #1

### 输入

```
1
2
```

### 输出

```
1/2
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
0/1
```

# AI分析结果

### 题目内容
# PLEASE

## 题目描述
正如我们所知道的，Barney的工作是“PLEASE”，并且ta工作时不需要做太多事情。这就是ta开始玩“cups and key”的原因。在这个游戏中有三个完全相同的杯子从左到右排成一行。最初，通往Barney心房的钥匙在中间的杯子下面。

游戏总共有\(n\)个回合，每个回合中，Barney等概率地选择两侧杯子的其中一个与中间的杯子交换位置，钥匙始终在原来的杯子中。

游戏结束后，Barney要求一位女装大佬（就是你）答出钥匙在中间杯子中的概率。

由于回合非常多，ta给了你一个数组`a[k]`，\(n=\prod_{i=1}^k a_i\)。

最后的答案化为形如`p/q`的最简分数形式后，分子分母同对\(1e9 + 7\)取模。

## 样例 #1
### 输入
```
1
2
```
### 输出
```
1/2
```

## 样例 #2
### 输入
```
3
1 1 1
```
### 输出
```
0/1
```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕通过建立数列关系来求解钥匙在中间杯子的概率。思路上，有的通过定义状态和概率，构建递推式；有的利用特征根方程求解通项公式；还有的使用矩阵快速幂等方法。难点在于如何准确建立数列关系，并对得到的概率表达式进行化简以及处理取模运算。不同题解在方法运用和代码实现上各有特点。

### 所选的题解
- **作者：Falashiro（5星）**
  - **关键亮点**：思路清晰，通过定义状态、画出树状图，逐步推导递推式，进而得出通项公式，对通项公式化简及整除性分析详细，代码简洁明了。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
    int w = 0, f = 1;
    char c =' ';
    while (c < '0' || c > '9')c = getchar(), f = c == '-'? -1 : f;
    while (c >= '0' && c <= '9')w = w * 10 + c - 48, c = getchar();
    return w * f;
}
const int mod = 1e9 + 7;
int pown(int x, int y) {
    int res = 1, ans = x;
    while (y) {
        if (y & 1)res = res * ans % mod;
        ans = ans * ans % mod;
        y >>= 1;
    }
    return res;
}
signed main() {
    int n = read(), x, y = 2;
    bool flag = 0;
    for (int i = 1; i <= n; i++)
        x = read(), flag = x % 2? flag : 1, y = pown(y, x) % mod;
    y = y * pown(2, mod - 2) % mod;
    if (flag)printf("%lld/%lld", (y + 1) * pown(3, mod - 2) % mod, y);
    else printf("%lld/%lld", (y - 1 + mod) * pown(3, mod - 2) % mod, y);
    return 0;
}
```
  - **核心实现思想**：先读入数据，计算\(2^n\)对\(mod\)取模，根据\(n\)的奇偶性计算并输出最终概率的分子分母对\(mod\)取模的结果。

- **作者：syzf2222（4星）**
  - **关键亮点**：通过设\(f_i\)和\(g_i\)表示不同位置概率，利用数列知识求解通项公式，对整除关系分析清晰，代码有一定注释。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5 + 10;
const int mod = 1e9 + 7;
const int inv3 = 333333336;
int n, a[maxn];
inline int read() {
    int x = 0, f = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-')f = -1; c = getchar(); }
    while (c >= '0' && c <= '9') { x = (x << 1) + (x << 3) + c - '0'; c = getchar(); }
    return x * f;
}
inline int ksm(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1)res = res * x % mod;
        x = (x * x) % mod; y >>= 1;
    }
    return res;
}
signed main() {
    n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read() % (mod - 1);
    int res = 1;
    for (int i = 1; i <= n; i++)
        res = res * a[i] % (mod - 1);
    if (!res)res = mod - 1;
    int up = 1, down = 1;
    down = ksm(2, res - 1);
    up = down + ((res & 1)? -1 : 1);
    up = up * inv3 % mod;
    printf("%lld/%lld\n", up, down);
    return 0;
}
```
  - **核心实现思想**：读入数据并对指数取模，计算\(2^{n - 1}\)对\(mod\)取模作为分母，根据\(n\)的奇偶性计算分子并对\(mod\)取模，最后输出结果。

- **作者：PrincessQi（4星）**
  - **关键亮点**：详细介绍多种处理数列的方法，包括矩阵快速幂、推导通项公式以及利用OEIS，拓宽解题思路。
  - **核心代码（以推导通项公式为例）**：
```cpp
// 推导通项公式部分主要在分析过程，代码核心与其他递推思路类似，以下为类似计算最终结果代码
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9 + 7;
int ksm(int b, int p) {
    int s = 1; b %= mod;
    while (p) {
        if (p & 1)s = s * b % mod;
        b = b * b % mod; p >>= 1;
    }
    return s;
}
signed main() {
    // 读入数据部分省略
    int n; cin >> n;
    int res = 1;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        res = res * x % (mod - 1);
    }
    if (!res)res = mod - 1;
    int up = 1, down = 1;
    down = ksm(2, res - 1);
    up = down + ((res & 1)? -1 : 1);
    up = up * ksm(3, mod - 2) % mod;
    printf("%lld/%lld\n", up, down);
    return 0;
}
```
  - **核心实现思想**：读入数据计算\(n\)，进而计算\(2^{n - 1}\)对\(mod\)取模作为分母，根据\(n\)奇偶性计算分子并对\(mod\)取模后输出。

### 最优关键思路或技巧
通过定义状态和概率，建立递推关系，再利用数列知识求解通项公式，是解决本题的关键思路。在实现过程中，快速幂计算指数、利用逆元处理除法取模等技巧保证了计算效率和结果准确性。

### 可拓展之处
同类型题可围绕通过建立数列递推关系求解概率或其他数学问题。类似算法套路包括准确分析状态转移，构建递推式，再根据递推式特点选择合适方法求解，如特征根方程、矩阵快速幂等。

### 推荐题目
- [P1962 斐波那契数列](https://www.luogu.com.cn/problem/P1962)：通过递推关系求解斐波那契数列，与本题建立数列关系求解概率类似。
- [P2190 仪仗队](https://www.luogu.com.cn/problem/P2190)：涉及数论和数学分析，与本题在数学思维运用上有相似之处。
- [P1266 速度限制](https://www.luogu.com.cn/problem/P1266)：通过数学方法建立方程求解问题，锻炼数学建模和计算能力。

### 个人心得摘录
 - **作者：syzf2222**：“深深地感到自己的弱小。” 表达对自身能力的感慨，侧面反映出算法学习的深度和广度。 

---
处理用时：70.00秒
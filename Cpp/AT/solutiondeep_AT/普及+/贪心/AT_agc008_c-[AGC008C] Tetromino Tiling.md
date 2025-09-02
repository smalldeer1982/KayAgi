# 题目信息

# [AGC008C] Tetromino Tiling

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc008/tasks/agc008_c

正方形のマスを $ 4 $ 個繋げた形をテトロミノといいます。 次の $ 7 $ 種類のテトロミノを順に I, O, T, J, L, S, Z 型と呼ぶことにします。

 ![a60bcb8e9e8f22e3af51049eda063392.png](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc008_c/41da26817a0aa4921d5f3228c5ba880f4ed240c0.png)

すぬけ君は I, O, T, J, L, S, Z 型のテトロミノをそれぞれ $ a_I $, $ a_O $, $ a_T $, $ a_J $, $ a_L $, $ a_S $, $ a_Z $ 個ずつ持っています。 すぬけ君はこれらのテトロミノのうち $ K $ 個を組み合わせ、縦 $ 2 $ マス、横 $ 2K $ マスの長方形を作ろうとしています。 このとき、すぬけ君は次のルールに従います。

- 各テトロミノを置くとき、回転はできるが、反転はできない。
- 長方形の各マスにはちょうど $ 1 $ 個のテトロミノが置かれているようにする。
- 長方形の外部にテトロミノが置かれていないようにする。

すぬけ君はできるだけ大きい長方形を作ろうとしています。 $ K $ の最大値を求めてください。

## 说明/提示

### 制約

- $ 0\ <\ =a_I,a_O,a_T,a_J,a_L,a_S,a_Z\ <\ =10^9 $
- $ a_I+a_O+a_T+a_J+a_L+a_S+a_Z\ >\ =1 $

### Sample Explanation 1

たとえば、図のように組み合わせればよいです。 !\[45515ed2a1dd5e41c5e4ca1f39323d8e.png\](https://atcoder.jp/img/agc008/45515ed2a1dd5e41c5e4ca1f39323d8e.png)

### Sample Explanation 2

長方形を作ることができません。

## 样例 #1

### 输入

```
2 1 1 0 0 0 0```

### 输出

```
3```

## 样例 #2

### 输入

```
0 0 10 0 0 0 0```

### 输出

```
0```

# AI分析结果

### 题目内容重写
#### [AGC008C] Tetromino Tiling

**题目描述**

正方形的小方块通过连接4个可以形成一种称为“Tetromino”的形状。以下7种Tetromino分别称为I、O、T、J、L、S、Z型。

![Tetromino图示](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc008_c/41da26817a0aa4921d5f3228c5ba880f4ed240c0.png)

Snuke君有I、O、T、J、L、S、Z型的Tetromino各$a_I$、$a_O$、$a_T$、$a_J$、$a_L$、$a_S$、$a_Z$个。他想要用其中的$K$个Tetromino拼成一个高2格、宽$2K$格的长方形。拼合时需要遵循以下规则：

- 每个Tetromino可以旋转，但不能翻转。
- 长方形的每个格子必须正好被一个Tetromino覆盖。
- Tetromino不能超出长方形范围。

Snuke君希望拼出尽可能大的长方形。请找出$K$的最大值。

**说明/提示**

**约束条件**
- $0 \leq a_I, a_O, a_T, a_J, a_L, a_S, a_Z \leq 10^9$
- $a_I + a_O + a_T + a_J + a_L + a_S + a_Z \geq 1$

**样例解释1**

例如，可以按照下图的方式拼合：
![样例1图示](https://atcoder.jp/img/agc008/45515ed2a1dd5e41c5e4ca1f39323d8e.png)

**样例解释2**

无法拼出长方形。

**样例输入1**
```
2 1 1 0 0 0 0
```

**样例输出1**
```
3
```

**样例输入2**
```
0 0 10 0 0 0 0
```

**样例输出2**
```
0
```

---

### 题解综合分析与结论

这道题的核心在于通过观察Tetromino的形状，排除无法使用的类型（T、S、Z），并分析剩余类型（I、O、J、L）的组合方式。所有题解都基于以下关键思路：

1. **排除不可用类型**：T、S、Z型的Tetromino无法拼出符合条件的长方形，因此直接排除。
2. **O型的贡献**：O型的Tetromino可以直接拼出$2 \times 2$的长方形，因此其数量可以直接计入答案。
3. **I、J、L型的组合方式**：有两种主要组合方式：
   - 两个I、两个J或两个L型可以拼出$2 \times 4$的长方形。
   - 一个I、一个J和一个L型可以拼出$2 \times 6$的长方形。
4. **贪心策略**：优先使用I、J、L型的组合方式，尽可能多地拼出长方形。

所有题解都围绕上述思路展开，但实现细节和代码简洁度有所不同。以下是评分较高的题解：

---

### 精选题解

#### 题解1：作者：FFTotoro (★★★★★)
**关键亮点**：
- 思路清晰，代码简洁。
- 通过条件判断直接计算最大$K$值，避免了复杂的分类讨论。
- 使用`max`函数直接比较两种组合方式的结果。

**代码核心实现**：
```cpp
#include<iostream>
#define int long long
using namespace std;
signed main(){
    int i,o,t,j,l; cin>>i>>o>>t>>j>>l; // J 和 L 后面的都不用读入了
    cout<<o+max(i&&j&&l?3+(i-1)/2*2+(j-1)/2*2+(l-1)/2*2:0,i/2*2+j/2*2+l/2*2)<<endl;
    return 0;
}
```
**核心思想**：通过`max`函数比较两种组合方式的结果，优先使用I、J、L型的组合方式。

---

#### 题解2：作者：fengenrong (★★★★☆)
**关键亮点**：
- 详细解释了每种Tetromino的组合方式。
- 代码逻辑清晰，易于理解。
- 通过`max`函数比较两种组合方式的结果。

**代码核心实现**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int I,O,T,J,L,S,Z,ans;
signed main()
{
    cin>>I>>O>>T>>J>>L>>S>>Z;
    ans=max(I/2*2+J/2*2+L/2*2,I>0&&J>0&&L>0?(I-1)/2*2+(J-1)/2*2+(L-1)/2*2+3:0);
    cout<<O+ans<<endl;
    return 0;
}
```
**核心思想**：通过`max`函数比较两种组合方式的结果，优先使用I、J、L型的组合方式。

---

#### 题解3：作者：_ChongYun_ (★★★★☆)
**关键亮点**：
- 代码简洁，逻辑清晰。
- 通过条件判断直接计算最大$K$值，避免了复杂的分类讨论。
- 使用`max`函数直接比较两种组合方式的结果。

**代码核心实现**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,c,d,e,f,g;
int ff(int x){ return x-x%2; }
signed main(){
    cin>>a>>b>>c>>d>>e>>f>>g;
    cout<<b+max(ff(a)+ff(d)+ff(e),(a&&d&&e)?ff(a-1)+ff(d-1)+ff(e-1)+3:0)<<endl;
    return 0;
}
```
**核心思想**：通过`max`函数比较两种组合方式的结果，优先使用I、J、L型的组合方式。

---

### 最优关键思路与技巧
1. **排除不可用类型**：T、S、Z型的Tetromino无法拼出符合条件的长方形，直接排除。
2. **贪心策略**：优先使用I、J、L型的组合方式，尽可能多地拼出长方形。
3. **组合方式**：两种主要组合方式：
   - 两个I、两个J或两个L型可以拼出$2 \times 4$的长方形。
   - 一个I、一个J和一个L型可以拼出$2 \times 6$的长方形。
4. **代码优化**：通过`max`函数直接比较两种组合方式的结果，避免复杂的分类讨论。

---

### 拓展思路与类似题目
1. **类似题目**：
   - [P1005 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005)：考察贪心策略和组合优化。
   - [P1044 栈](https://www.luogu.com.cn/problem/P1044)：考察组合数学和递推思想。
   - [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)：考察动态规划和组合优化。

2. **调试心得**：
   - **分类讨论**：在实现过程中，确保所有可能的组合方式都被考虑，避免遗漏。
   - **边界条件**：注意输入为0的情况，确保代码能够正确处理。

---

### 推荐题目
1. [P1005 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)

---
处理用时：60.02秒
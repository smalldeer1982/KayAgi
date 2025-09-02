# 题目信息

# Two Sets

## 题目描述

Little Petya likes numbers a lot. Recently his mother has presented him a collection of $ n $ non-negative integers. There's only one thing Petya likes more than numbers: playing with little Masha. He immediately decided to give a part of his new collection to her. To make the game even more interesting, Petya decided to give Masha such collection of numbers for which the following conditions fulfill:

- Let's introduce $ x_{1} $ to denote the $ xor $ of all numbers Petya has got left; and let's introduce $ x_{2} $ to denote the $ xor $ of all numbers he gave to Masha. Value $ (x_{1}+x_{2}) $ must be as large as possible.
- If there are multiple ways to divide the collection so that the previous condition fulfilled, then Petya minimizes the value $ x_{1} $ .

The $ xor $ operation is a bitwise excluding "OR", that is denoted as "xor" in the Pascal language and "^" in C/C++/Java.

Help Petya divide the collection as described above. If there are multiple suitable ways to divide it, find any of them. Please note that after Petya gives a part of his numbers to Masha, he may have no numbers left. The reverse situation is also possible, when Petya gives nothing to Masha. In both cases we must assume that the $ xor $ of an empty set of numbers equals 0.

## 样例 #1

### 输入

```
6
1 2 3 4 5 6
```

### 输出

```
2 2 2 2 2 2
```

## 样例 #2

### 输入

```
3
1000000000000 1000000000000 1000000000000
```

### 输出

```
2 2 2
```

## 样例 #3

### 输入

```
8
1 1 2 2 3 3 4 4
```

### 输出

```
1 2 1 2 2 2 1 2
```

# AI分析结果


### 💡 Kay的C++算法解析：Two Sets 深入学习指南 💡

**题目解读**  
给定 $n$ 个非负整数，将其分成两个集合 $S_1$ 和 $S_2$，使 $S_1$ 的异或和 $x_1$ 与 $S_2$ 的异或和 $x_2$ 之和 $(x_1+x_2)$ 最大，且最小化 $x_1$。

✨ **本题主要考察**：`线性代数应用`（异或方程组的求解）  
🗣️ **初步分析**：  
> 问题本质是**按位贪心+线性基/高斯消元**。想象你有两堆宝石（集合），每堆的魔法值（异或和）需满足特定规则：
> - 设所有数的异或和为 $S$，则 $x_1 \oplus x_2 = S$。
> - **最大化 $x_1+x_2$**：对 $S$ 为 $0$ 的位，让 $x_1$ 和 $x_2$ 均为 $1$（贡献 $2^{i+1}$）；对 $S$ 为 $1$ 的位，贡献固定为 $2^i$。
> - **最小化 $x_1$**：在 $S=1$ 的位让 $x_1=0$。
>
> **核心策略**：从高位到低位优先处理 $S=0$ 的位（贪心最大化），再处理 $S=1$ 的位（贪心最小化）。用线性基或高斯消元解决位间依赖。  
> **可视化设计**：用像素宝石代表数字，高亮当前处理位，动态展示分组决策（详见第5节）。

---

### 2. 精选优质题解参考

**题解一（荣耀火影）**  
* **点评**：思路清晰，用高斯消元解异或方程组。代码中 `f` 数组存储系数，`pos` 记录主元位置，从高位到低位处理 $S=0$ 和 $S=1$ 的位。亮点在于**用 `bitset` 优化消元过程**，边界处理严谨（跳过自由变元），竞赛实用性强。但变量名可读性可提升（如 `f` 改为 `equations`）。

**题解二（chenxia25）**  
* **点评**：通过重排数位优先级（先 $S=0$ 后 $S=1$）简化问题，**线性基贪心求 $x_1$ 后还原方案**。亮点是添加额外数 $a_{n+1}=x_1$ 构造方程，用高斯消元反推分组。代码结构稍复杂，但算法有效性高，复杂度 $O(n \log a_i)$。

**题解三（littleKtian）**  
* **点评**：分两次循环处理 $S=0$ 和 $S=1$ 的位，**动态重建线性基并决策 $x_1$ 的位值**。亮点是用 `base_mask` 记录基的生成路径，高效还原分组方案。代码简洁但变量命名抽象（如 `t`, `w`），学习时需结合注释。

---

### 3. 核心难点辨析与解题策略

1.  **难点1：理解位贡献的贪心策略**  
    * **分析**：$S=0$ 的位对 $x_1+x_2$ 的贡献可达 $2^{i+1}$（若 $x_1=1$），而 $S=1$ 的位贡献固定。需优先处理高位 $S=0$ 的位，再最小化 $x_1$。  
    * 💡 **学习笔记**：**高位优先贪心是最大化总和的关键**。

2.  **难点2：处理多比特位的相互影响**  
    * **分析**：一个数包含多个位，决策依赖需解异或方程组。例如：方程 $a_{i,j}x_1 \oplus \cdots = b_j$ 表示第 $j$ 位的约束。  
    * 💡 **学习笔记**：**线性基/高斯消元是解决位间依赖的标准工具**。

3.  **难点3：还原分组方案**  
    * **分析**：求 $x_1$ 后需找出哪些数在 $S_1$。通过线性基的 `base_mask` 或高斯消元的主元变量反推。  
    * 💡 **学习笔记**：**记录基的生成路径可高效还原方案**。

#### ✨ 解题技巧总结
- **技巧1：位分解法**：将问题拆解到每个二进制位独立分析。
- **技巧2：优先级重排**：按 $S=0$ > $S=1$ 和高位 > 低位的顺序处理。
- **技巧3：线性代数工具**：灵活选用高斯消元（显式方程组）或线性基（隐式贪心）。
- **技巧4：方案还原**：用 `bitset` 跟踪基的生成路径或高斯消元的主元。

---

### 4. C++核心代码实现赏析

**本题通用核心C++实现参考**  
* **说明**：综合题解思路，基于线性基的贪心策略实现。
* **完整核心代码**：
  ```cpp
  #include <bits/stdc++.h>
  using namespace std;
  typedef long long ll;
  const int N = 1e5 + 5, M = 62;

  ll base[M], mask[M], S;
  int n, ans[N];
  vector<int> bit_order;

  void insert(int id, ll x) {
    ll msk = 1LL << id;
    for (int i = M-1; i >= 0; i--) {
      if (!(x >> i & 1)) continue;
      if (base[i]) {
        x ^= base[i];
        msk ^= mask[i];
      } else {
        base[i] = x;
        mask[i] = msk;
        break;
      }
    }
  }

  int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
      ll x; cin >> x;
      insert(i, x);
      S ^= x;
      ans[i] = 2;  // 初始默认在 S2
    }

    // 构建优先级: 先 S=0 的位, 再 S=1 的位
    for (int i = M-1; i >= 0; i--)
      if (!(S >> i & 1)) bit_order.push_back(i);
    for (int i = M-1; i >= 0; i--)
      if (S >> i & 1) bit_order.push_back(i);

    // 贪心确定 x1
    ll x1 = 0;
    for (int b : bit_order) {
      ll new_x1 = x1 ^ (1LL << b);
      for (int i = M-1; i >= 0; i--) {
        if (!(new_x1 >> i & 1)) continue;
        if (!base[i]) break;
        new_x1 ^= base[i];
      }
      if (new_x1 == 0) x1 ^= (1LL << b);
    }

    // 还原分组方案
    ll solution = 0;
    for (int i = M-1; i >= 0; i--) {
      if (!(x1 >> i & 1)) continue;
      if (!base[i]) break;
      x1 ^= base[i];
      solution ^= mask[i];
    }
    for (int i = 0; i < n; i++)
      if (solution >> i & 1) ans[i] = 1;

    for (int i = 0; i < n; i++) cout << ans[i] << " ";
  }
  ```
* **代码解读概要**：  
  > 1. 计算总异或和 $S$，初始化线性基。
  > 2. 按优先级处理每位：尝试设置 $x_1$ 的位值，通过基验证可行性。
  > 3. 用 `mask` 记录基的生成路径，反推哪些数应在 $S_1$。

---

### 5. 算法可视化：像素动画演示

**主题**：宝石分组大冒险（8位像素风）  
**核心演示**：动态展示按位贪心决策过程。  
**设计思路**：  
> - **像素宝石**：每个数用 8×8 像素方块表示，内部显示二进制值（如 `0010`）。  
> - **位高亮**：当前处理的位闪烁，该位为 1 的宝石边框变金色。  
> - **决策动画**：  
>     - $S=0$ 的位：宝石分裂为两个（象征 $x_1=x_2=1$），播放上升音效。  
>     - $S=1$ 的位：宝石滑向 $S_2$（象征 $x_1=0$），播放低沉音效。  
> - **控制面板**：步进按钮、速度滑块、重置键。  
> - **游戏化**：每成功处理一位得 `2^(i+1)` 分，累计显示总分。

---

### 6. 拓展练习与相似问题思考

1. **洛谷 P3857 [TJOI2008]彩灯**  
   🗣️ **推荐理由**：线性基模板题，求子集异或值种类数，巩固基的生成。

2. **洛谷 P4151 [WC2011]最大XOR和路径**  
   🗣️ **推荐理由**：将路径异或问题转化为线性基应用，拓展图论场景。

3. **洛谷 P4301 [CQOI2013]新Nim游戏**  
   🗣️ **推荐理由**：结合博弈与线性基，练习贪心策略构造。

---

### 7. 学习心得与经验分享
> 本次分析的题解中未发现明确的作者个人心得分享部分。

---
**结语**：通过位分解和线性代数工具，Two Sets 问题被优雅解决。理解贪心优先级和基的生成是关键。下次挑战见！💪

---
处理用时：322.69秒
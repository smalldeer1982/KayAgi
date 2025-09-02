# 题目信息

# Anton and School - 2

## 题目描述

As you probably know, Anton goes to school. One of the school subjects that Anton studies is Bracketology. On the Bracketology lessons students usually learn different sequences that consist of round brackets (characters "(" and ")" (without quotes)).

On the last lesson Anton learned about the regular simple bracket sequences (RSBS). A bracket sequence $ s $ of length $ n $ is an RSBS if the following conditions are met:

- It is not empty (that is $ n≠0 $ ).
- The length of the sequence is even.
- First ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to "(".
- Last ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to ")".

For example, the sequence "((()))" is an RSBS but the sequences "((())" and "(()())" are not RSBS.

Elena Ivanovna, Anton's teacher, gave him the following task as a homework. Given a bracket sequence $ s $ . Find the number of its distinct subsequences such that they are RSBS. Note that a subsequence of $ s $ is a string that can be obtained from $ s $ by deleting some of its elements. Two subsequences are considered distinct if distinct sets of positions are deleted.

Because the answer can be very big and Anton's teacher doesn't like big numbers, she asks Anton to find the answer modulo $ 10^{9}+7 $ .

Anton thought of this task for a very long time, but he still doesn't know how to solve it. Help Anton to solve this task and write a program that finds the answer for it!

## 说明/提示

In the first sample the following subsequences are possible:

- If we delete characters at the positions $ 1 $ and $ 5 $ (numbering starts with one), we will get the subsequence "(())".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".

The rest of the subsequnces are not RSBS. So we got $ 6 $ distinct subsequences that are RSBS, so the answer is $ 6 $ .

## 样例 #1

### 输入

```
)(()()
```

### 输出

```
6
```

## 样例 #2

### 输入

```
()()()
```

### 输出

```
7
```

## 样例 #3

### 输入

```
)))
```

### 输出

```
0
```

# AI分析结果


### 💡 Kay的C++算法解析：Anton and School - 2 深入学习指南 💡

**引言**  
今天我们一起分析CF785D "Anton and School - 2"这道C++编程题。本指南将帮助大家梳理题目思路，理解核心算法，掌握解题技巧，并通过像素动画直观感受算法执行过程。

---

### 1. 题目解读与核心算法识别
✨ **本题主要考察**：组合数学（范德蒙德卷积应用）

🗣️ **初步分析**：
> 解决本题的关键在于运用组合数学中的**范德蒙德卷积公式**。想象你在玩一个像素游戏：将括号序列看作由"("（绿色方块）和")"（红色方块）组成的关卡。你需要找出所有满足条件的子序列——前半段全绿、后半段全红，且长度偶数的子序列。  
> - **核心思路**：枚举每个"("作为子序列的最后一个左括号，计算其贡献。若当前位置左边有 `a` 个"("（包括自身），右边有 `b` 个")"，则贡献为组合数 `C(a+b-1, a)`（通过范德蒙德卷积推导）。  
> - **难点突破**：直接组合求和复杂度 O(n²)，而卷积公式优化为 O(1) 单点计算。  
> - **可视化设计**：在像素动画中，高亮当前枚举的"("（黄色闪烁），动态显示左边绿色方块数 `a` 和右边红色方块数 `b`，最后用像素数字展示组合数计算结果。  
> - **复古游戏化**：采用8位FC游戏风格，单步执行时触发"叮"音效；贡献计算成功时播放胜利音效；累计得分机制增强趣味性。

---

### 2. 精选优质题解参考
以下是思路清晰、代码规范、算法高效的优质题解（评分≥4★）：

**题解一（来源：_Life_）**  
* **点评**：  
  思路直击核心——枚举最后一个"("并应用范德蒙德卷积优化。推导过程清晰解释卷积公式的转化（`∑C(a-1,i)C(b,i+1)=C(a+b-1,a)`）。代码规范：前缀和变量命名明确（`l[]`/`r[]`），线性预处理阶乘逆元（`fac[]`/`inv[]`），边界处理严谨（`C(n,m)`中检查 `n<m`）。算法优化显著（O(n)复杂度），实践价值高，可直接用于竞赛。

**题解二（来源：YuntianZhao）**  
* **点评**：  
  亮点在于详细展示公式推导（含卷积证明草图），帮助理解数学本质。代码中快速幂求逆元（`power()`函数）是基础但关键的技巧，变量名`cnt1`/`cnt2`直观体现组合参数。虽然求幂复杂度O(log P)略高，但代码可读性强，适合初学者理解组合数计算原理。

**题解三（来源：是个汉子）**  
* **点评**：  
  代码结构工整，模块化设计突出：分离`fpow()`快速幂、`init()`预处理、`C()`组合数函数。边界处理（`x<0||y<0||x<y`时返回0）展现鲁棒性。题解强调"强制选最后一个左括号"避免重复，实践时调试友好。

---

### 3. 核心难点辨析与解题策略
**关键点1：状态定义与问题分解**  
* **分析**：  
  如何避免枚举所有子序列？优质题解均采用**枚举最后一个"("**策略，将问题分解为：左边选 `a-1` 个"("（不含当前），右边选 `b` 个")"的子问题。关键变量是前缀和数组 `l[i]`/`r[i]`，需在预处理时计算。  
* 💡 **学习笔记**：将大问题拆解为独立子问题是降低复杂度的关键。

**关键点2：组合求和的优化**  
* **分析**：  
  直接计算 `∑C(a-1,i)C(b,i+1)` 的复杂度 O(n²) 不可接受。通过**范德蒙德卷积**（`∑C(n,i)C(m,k-i)=C(n+m,k)`）转化为单组合数 `C(a+b-1,a)`，实现O(1)计算。  
* 💡 **学习笔记**：熟悉组合恒等式能大幅优化计数问题。

**关键点3：组合数的高效计算**  
* **分析**：  
  需要频繁计算组合数模 `1e9+7`。优质题解均预处理阶乘数组 `fac[]` 及其逆元 `inv[]`。逆元可通过快速幂（费马小定理）或线性递推求得，后者更优（O(n)）。  
* 💡 **学习笔记**：预处理阶乘逆元是组合问题的标准操作。

#### ✨ 解题技巧总结
- **组合问题分解**：将复杂计数转化为独立子问题（如固定最后一个元素）。  
- **恒等式应用**：范德蒙德卷积处理双重组合求和。  
- **预处理优化**：线性时间计算阶乘逆元，O(1)查询组合数。  
- **边界严谨性**：检查 `n<m` 或负数情况，避免运行时错误。

---

### 4. C++核心代码实现赏析
**本题通用核心C++实现参考**  
* **说明**：综合优质题解思路，包含阶乘预处理、前缀和计算、卷积优化。  
* **完整核心代码**：
  ```cpp
  #include <iostream>
  #include <cstring>
  #define int long long
  const int N = 2e5 + 5, mod = 1e9 + 7;
  char s[N];
  int fac[N], inv[N], l[N], r[N];

  int power(int a, int b) {
      int res = 1;
      for (; b; b >>= 1, a = a * a % mod)
          if (b & 1) res = res * a % mod;
      return res;
  }

  void init() {
      fac[0] = 1;
      for (int i = 1; i < N; ++i) 
          fac[i] = fac[i - 1] * i % mod;
      inv[N - 1] = power(fac[N - 1], mod - 2);
      for (int i = N - 2; i >= 0; --i) 
          inv[i] = inv[i + 1] * (i + 1) % mod;
  }

  int C(int n, int m) {
      if (n < m || m < 0) return 0;
      return fac[n] * inv[m] % mod * inv[n - m] % mod;
  }

  signed main() {
      init();
      std::cin >> (s + 1);
      int n = std::strlen(s + 1);
      for (int i = 1; i <= n; ++i) 
          l[i] = l[i - 1] + (s[i] == '(');
      for (int i = n; i >= 1; --i) 
          r[i] = r[i + 1] + (s[i] == ')');
      int ans = 0;
      for (int i = 1; i <= n; ++i) 
          if (s[i] == '(') 
              ans = (ans + C(l[i] + r[i] - 1, l[i])) % mod;
      std::cout << ans;
      return 0;
  }
  ```
* **代码解读概要**：
  1. `init()`预处理阶乘数组`fac[]`和逆元数组`inv[]`。  
  2. `C(n,m)`函数用预处理结果O(1)计算组合数。  
  3. 两次遍历计算前缀和`l[i]`（[1,i]的"("数量）和后缀和`r[i]`（[i,n]的")"数量）。  
  4. 枚举每个"("，用卷积公式`C(l[i]+r[i]-1, l[i])`累加答案。

#### 各题解核心片段赏析
**题解一（_Life_）**  
* **亮点**：线性求逆元，无快速幂调用。  
* **核心代码**：
  ```cpp
  inv[n] = fastpow(fac[n], mod-2);
  for(int i = n-1; i >= 0; i--) 
      inv[i] = inv[i+1] * (i+1) % mod; // 线性递推逆元
  ```
* **代码解读**：  
  > 逆元从后往前递推：`inv[i] = inv[i+1]*(i+1)`。利用公式：  
  > `i!⁻¹ = (i+1)!⁻¹ * (i+1) (mod M)`  
  > 复杂度O(n)优于快速幂的O(n log M)。

**题解二（YuntianZhao）**  
* **亮点**：快速幂模板通用性强。  
* **核心代码**：
  ```cpp
  long long power(long long x, int n) {
    long long ans = 1;
    while (n) {
        if (n & 1) ans = ans * x % mod;
        x = x * x % mod; n >>= 1;
    } return ans;
  }
  ```
* **学习笔记**：快速幂是数论基础，需熟练掌握位运算优化。

**题解三（是个汉子）**  
* **亮点**：函数封装清晰（`fpow`/`C`）。  
* **核心代码**：
  ```cpp
  void pre_work(){
      for(int i=1; i<=maxn; i++) 
          fac[i] = fac[i-1]*i % mod;
      inv[maxn] = fpow(fac[maxn], mod-2);
      // 逆元递推
  }
  ```
* **学习笔记**：模块化代码提升可读性和复用性。

---

### 5. 算法可视化：像素动画演示
**动画演示主题**：  
"括号探险者"在8位像素风格的括号序列中移动，动态演示组合数计算过程。

**核心演示内容**：
1. **初始化**：  
   - 序列显示为像素网格（绿"( "/红")"）。  
   - 控制面板含"步进"、"调速"、"重置"按钮。  
   - 8-bit背景音乐启动。

2. **枚举左括号**：  
   - 像素小人移动到"("位置时，方块高亮闪烁黄色，播放"叮"音效。  
   - 左侧显示`a = l[i]`（绿方块数），右侧显示`b = r[i]`（红方块数）。

3. **卷积计算**：  
   - 动态绘制组合数公式：`C(a+b-1, a)`。  
   - 用像素数字展示计算步骤：`fac[]`取值→乘法→取模。  
   - 结果出现时，目标括号变金色，播放胜利音效。

4. **游戏化交互**：  
   - 每计算一个左括号得1分，累计分数显示在顶部。  
   - "自动播放"模式：算法自动遍历所有"("，速度可调。  
   - 通关条件：所有"("处理完毕，结算总分。

**设计思路**：  
复古像素风格降低理解压力，音效反馈强化关键操作（枚举/计算成功）。游戏化积分激励学习者逐步深入。

---

### 6. 拓展练习与相似问题思考
**通用思路迁移**：  
范德蒙德卷积适用场景：  
1. 双序列独立选取的组合求和（如选左括号+右括号）。  
2. 卡特兰数相关问题（括号匹配变种）。  
3. 分组选取问题（如从两堆选k个物品）。

**洛谷题目推荐**：  
1. **P1641 [SCOI2010]生成字符串**  
   → 练习组合数建模和边界处理。  
2. **P3200 [HNOI2009]有趣的数列**  
   → 卡特兰数+组合恒等式应用。  
3. **P1754 球迷购票问题**  
   → 二维选取问题，可用卷积优化。

---

### 7. 学习心得与经验分享
> **参考经验**（来自_Life_）：  
> "推导时先写出原始组合求和式，再观察是否匹配范德蒙德形式。调试时验证小数据卷积是否成立。"  
>   
> **点评**：  
> 作者强调从暴力式出发优化的思维路径。实际编码时，预处理数组的边界（如`inv[0]=1`）易出错，建议写单测验证组合数函数。

---

**结语**  
通过本题我们深入掌握了组合数学的实践应用。记住：分解问题→数学优化→高效编码是解决计数问题的黄金路径。下次挑战再见！ 💪

---
处理用时：164.04秒
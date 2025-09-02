# 题目信息

# Matrix game

## 题目描述

Aryan and Harshith play a game. They both start with three integers $ a $ , $ b $ , and $ k $ . Aryan then gives Harshith two integers $ n $ and $ m $ . Harshith then gives Aryan a matrix $ X $ with $ n $ rows and $ m $ columns, such that each of the elements of $ X $ is between $ 1 $ and $ k $ (inclusive). After that, Aryan wins if he can find a submatrix $ ^{\text{∗}} $ $ Y $ of $ X $ with $ a $ rows and $ b $ columns such that all elements of $ Y $ are equal.

For example, when $ a=2, b=2, k=6, n=3 $ and $ m=3 $ , if Harshith gives Aryan the matrix below, it is a win for Aryan as it has a submatrix of size $ 2\times 2 $ with all elements equal to $ 1 $ as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120D/ff9ee31dfc04aa73a7daca458dede1d4462758ef.png) Example of a matrix where Aryan wins Aryan gives you the values of $ a $ , $ b $ , and $ k $ . He asks you to find the lexicographically minimum tuple $ (n,m) $ that he should give to Harshith such that Aryan always wins. Help Aryan win the game. Assume that Harshith plays optimally. The values of $ n $ and $ m $ can be large, so output them modulo $ 10^9+7 $ . A tuple $ (n_1, m_1) $ is said to be lexicographically smaller than $ (n_2, m_2) $ if either $ n_1<n_2 $ or $ n_1=n_2 $ and $ m_1<m_2 $ .

 $ ^{\text{∗}} $ A submatrix of a matrix is obtained by removing some rows and/or columns from the original matrix.

## 说明/提示

For the first test case, every $ n\times m $ matrix contains a $ 1\times 1 $ submatrix with all elements equal. $ (1,1) $ is the lexicographically minimum tuple among all of them.

For the second test case, it can be verified that whatever $ 3\times 7 $ matrix Harshith gives to Aryan, Aryan can always win by finding a $ 2\times 2 $ submatrix with all elements equal. $ (3,7) $ is also the lexicographically minimum tuple among all possible tuples where Aryan always wins.

## 样例 #1

### 输入

```
3
1 1 5
2 2 2
90000 80000 70000```

### 输出

```
1 1
3 7
299929959 603196135```

# AI分析结果


### 💡 Kay的C++算法解析：Matrix Game 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`组合数学与鸽巢原理应用`  
🗣️ **初步分析**：  
> 解决这道题的关键在于理解**鸽巢原理**（抽屉原理）。想象你有 $k$ 种颜色的鸽子（数字）要放进 $n$ 个鸽巢（行）。为了让某种颜色至少出现 $a$ 次，需要 $(a-1)×k+1$ 行。类似地，列数 $m$ 的确定需要计算每列可能的合法方案数（$k×\binom{n}{a}$），再用鸽巢原理保证至少一种方案出现 $b$ 次。  
> - **可视化设计**：将用8位像素风格展示鸽巢原理。每个数字用不同颜色像素块表示，当某列积累 $a$ 个同色块时触发闪光特效。列计数阶段用进度条动画展示方案积累过程，$b$ 次达成时播放胜利音效。

---

#### 2. 精选优质题解参考
**题解一（作者：yitinboge_fan）**  
* **点评**：思路直击核心——用鸽巢原理分层推导 $n$ 和 $m$ 的下界。代码中组合数计算采用逆元连乘，处理大数取模严谨（如 `(n-i+1+p)%p` 防负数）。亮点在于完整呈现数学推导到代码的映射关系，变量名 `n, m, a, b, k` 贴合题意，竞赛适用性强。

**题解二（作者：_O_v_O_）**  
* **点评**：与题解一思路一致但更强调组合数计算模块化（独立 `calc()` 函数）。亮点在于封装逆元计算逻辑，提升代码复用性。需注意 `inv(i)*((n-i+1+mod))%mod` 的连续取模可能影响效率，但对本题数据规模仍高效。

---

#### 3. 核心难点辨析与解题策略
1. **难点1：行列约束的分离推导**  
   * **分析**：需独立分析行/列的最小值。行约束仅需单列视角（$n=(a-1)×k+1$），列约束需全局方案统计（$m=k×\binom{n}{a}×(b-1)+1$）。  
   * 💡 **学习笔记**：分解维度是降低复杂度的关键！

2. **难点2：大数组合数取模计算**  
   * **分析**：当 $n≈10^9$ 时，用公式 $\binom{n}{a}=\prod_{i=1}^a \frac{n-i+1}{i}$ 配合逆元逐步计算，避免阶乘爆炸。  
   * 💡 **学习笔记**：模逆元（`fastpow(i, p-2)`）是处理除法的利器。

3. **难点3：鸽巢原理的两次应用**  
   * **分析**：第一次用于行（强制单列存在 $a$ 个相同数），第二次用于列（强制存在 $b$ 列满足条件）。  
   * 💡 **学习笔记**：多层鸽巢原理可解决嵌套约束问题。

**✨ 解题技巧总结**  
- **数学建模优先**：将问题转化为鸽巢原理的计数模型  
- **分步取模技巧**：对大数连乘/除每一步独立取模  
- **边界防御性编程**：如 `(n-i+1+p) % p` 避免负数  

---

#### 4. C++核心代码实现赏析
**通用核心实现参考**  
```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const ll p = 1e9+7;

ll fastpow(ll base, ll exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = res * base % p;
        base = base * base % p;
        exp >>= 1;
    }
    return res;
}

int main() {
    int T; cin >> T;
    while (T--) {
        ll a, b, k; cin >> a >> b >> k;
        ll n = ((a-1) * k + 1) % p;    // 行下界
        ll comb = 1;                    // 计算组合数C(n,a)
        for (int i = 1; i <= a; ++i) {
            comb = comb * (n - i + 1 + p) % p * fastpow(i, p-2) % p;
        }
        ll m = (k * comb % p * (b-1) + 1) % p;  // 列下界
        cout << n << " " << m << endl;
    }
}
```
**代码解读概要**：  
1. 读入 $a, b, k$ 后计算最小行数 $n$  
2. 通过连乘和逆元计算 $\binom{n}{a}$（避免大阶乘）  
3. 用鸽巢原理推导最小列数 $m$  

---

#### 5. 算法可视化：像素动画演示
**🎮 主题**：《像素鸽巢大冒险》- 8位机风格演示鸽巢原理  
**🎨 设计思路**：  
- **像素网格**：行/列化为网格，数字1~k用不同颜色像素块（16色调色盘）  
- **核心动效**：  
  - **行积累阶段**：每列独立计数，同色块积累时播放 `叮` 音效，达 $a$ 块时整列闪光  
  - **列积累阶段**：右侧进度条统计每列达标情况，$b$ 次达成时触发胜利动画（烟花+胜利音效）  
- **交互控制**：  
  - 速度滑块调节自动演示速率  
  - `单步执行`按钮逐步观察计数过程  
  - `AI演示`模式自动完成全流程（类似吃豆人自动寻路）  

**🕹️ 技术实现**：  
```javascript
// 伪代码：鸽巢计数动画
function drawGrid() {
  for (let col = 0; col < m; col++) {
    for (let row = 0; row < n; row++) {
      const color = matrix[row][col]; // 1~k对应颜色
      drawPixel(row, col, PALETTE[color]); 
      if (isCritical(row, col)) flashEffect(); // 达a个同色时闪烁
    }
    drawProgressBar(col, count[col]); // 列进度条
  }
}
```

---

#### 6. 拓展练习与相似问题思考
**🔗 通用技巧迁移**：  
鸽巢原理适用于：  
1. 存在性证明（如必有两个数差为k的倍数）  
2. 最坏情况分析（如缓存失效问题）  
3. 子结构重复出现（如字符串重复子序列）  

**📚 洛谷练习推荐**：  
1. **P2219 [HAOI2007]覆盖问题**  
   → 鸽巢原理在几何覆盖问题中的变形  
2. **P4132 [BJOI2012]算不了一夜**  
   → 大数组合数取模的进阶练习  
3. **P2280 [HNOI2003]激光炸弹**  
   → 子矩阵约束的二维推广  

---

#### 7. 学习心得与经验分享
> **参考经验**：题解未提供作者调试心得，但实践中需注意：  
> - **大数陷阱**：当 $a=90000, k=70000$ 时，$n$ 超 `int` 范围，必须用 `long long`  
> - **负数取模**：`(n-i+1+p)%p` 确保被除数非负  

---

通过本次分析，我们深入理解了鸽巢原理在二维约束问题中的精妙应用。记住：分解维度+数学建模是突破复杂约束的关键！🎯

---
处理用时：110.63秒
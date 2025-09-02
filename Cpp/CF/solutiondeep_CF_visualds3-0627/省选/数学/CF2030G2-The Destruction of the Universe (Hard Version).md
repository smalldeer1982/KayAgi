# 题目信息

# The Destruction of the Universe (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, $ n \leq 10^6 $ . You can only make hacks if both versions of the problem are solved.

Orangutans are powerful beings—so powerful that they only need $ 1 $ unit of time to destroy every vulnerable planet in the universe!

There are $ n $ planets in the universe. Each planet has an interval of vulnerability $ [l, r] $ , during which it will be exposed to destruction by orangutans. Orangutans can also expand the interval of vulnerability of any planet by $ 1 $ unit.

Specifically, suppose the expansion is performed on planet $ p $ with interval of vulnerability $ [l_p, r_p] $ . Then, the resulting interval of vulnerability may be either $ [l_p - 1, r_p] $ or $ [l_p, r_p + 1] $ .

Given a set of planets, orangutans can destroy all planets if the intervals of vulnerability of all planets in the set intersect at least one common point. Let the score of such a set denote the minimum number of expansions that must be performed.

Orangutans are interested in the sum of scores of all non-empty subsets of the planets in the universe. As the answer can be large, output it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first testcase, there are seven non-empty subsets of planets we must consider:

- For each of the subsets $ \{[1,1]\}, \{[2,3]\}, \{[3,3]\} $ , the score is $ 0 $ .
- For the subset $ \{[2,3], [3,3]\} $ , the score is $ 0 $ , because the point $ 3 $ is already contained in both planets' interval of vulnerability.
- For the subset $ \{[1,1], [2,3]\} $ , the score is $ 1 $ . By using one operation on changing the interval of vulnerability of the second planet to be $ [1,3] $ , the two planets now both have the point $ 1 $ in their interval.
- For the subset $ \{[1,1], [3,3]\} $ , the score is $ 2 $ . By using two operations on changing the interval of vulnerability of the first planet to be $ [1,3] $ , the two planets now both have the point $ 3 $ in their interval.
- For the subset $ \{[1,1], [2,3], [3,3]\} $ , the score is $ 2 $ . By using one operation on changing the interval of vulnerability of the first planet to be $ [1,2] $ and one operation on changing the interval of vulnerability of the third planet to $ [2,3] $ , all three planets will have the point $ 2 $ in their interval.

The sum of scores of all non-empty subsets of the first testcase is $ 0 \cdot 4 + 1 \cdot 1 + 2\cdot2 = 5 $ .

## 样例 #1

### 输入

```
3
3
1 1
2 3
3 3
4
1 4
2 3
2 4
1 1
5
1 2
2 3
3 4
4 5
1 5```

### 输出

```
5
6
24```

# AI分析结果



### 算法分类
**组合数学**

---

### 题解思路与难点分析
**核心目标**：计算所有非空子集的得分之和，每个子集的得分是使其扩展后的区间存在交点的最小操作次数。  
**关键思路**：  
1. **中位数性质**：最优交点必然在所有区间端点构成的集合中，且满足组合数学中的对称性条件。  
2. **端点枚举**：离散化后枚举每个端点作为可能的中位数，统计其左右需要扩展的线段数。  
3. **组合数优化**：利用范德蒙德卷积将双重求和简化为单个组合数，结合前缀/后缀和快速计算贡献。

**解决难点**：  
- **重复端点处理**：通过离散化重新编号端点，确保每个端点唯一。  
- **贡献去重**：通过分类讨论端点类型（左/右端点）确保不重复计算子集。  
- **高效计算**：预处理前缀和（右端点信息）和后缀和（左端点信息）实现 O(1) 计算每个端点的贡献。

---

### 最优题解评分与亮点（≥4星）
1. **ForgotMe 的题解（5星）**  
   - **亮点**：通过重新编号端点避免重复，利用前缀/后缀和优化时间复杂度至 O(n)。代码清晰，预处理组合数和快速计算贡献的逻辑简洁。  
   - **关键代码段**：
     ```cpp
     for(int i=1;i<=2*n;i++)s1[i]+=s1[i-1],s3[i]=add(s3[i],s3[i-1]);
     for(int i=2*n-1;i>=1;i--)s2[i]+=s2[i+1],s4[i]=add(s4[i],s4[i+1]);
     // 枚举端点并计算贡献
     for(int i=1;i<=2*n;i++) {
         int val=rev[i], c1=s1[i-1], c2=s2[i+1];
         int val2 = ...; // 利用组合数和前缀和计算贡献
         res = add(res, val2 * ...);
     }
     ```

---

### 关键公式推导与优化
**公式简化**：  
对于每个端点 x，贡献计算可分解为：  
- 左边需扩展的线段数 `cnt1`，贡献为 `Σ(l_i - x)`  
- 右边需扩展的线段数 `cnt2`，贡献为 `Σ(x - r_i)`  
利用组合数性质：  
$$ \sum_{j} \binom{cnt1}{j} \binom{cnt2}{j} = \binom{cnt1 + cnt2}{cnt1} $$  
**预处理**：  
- `s1[i]`：右端点 ≤i 的线段数。  
- `s3[i]`：右端点 ≤i 的线段 r_i 之和。  
- `s2[i]`：左端点 ≥i 的线段数。  
- `s4[i]`：左端点 ≥i 的线段 l_i 之和。  

---

### 同类型题目套路
- **通用思路**：离散化端点，枚举每个关键点统计贡献，利用组合数性质优化计算。  
- **常见模型**：涉及区间覆盖、中位数性质、子集贡献累积的问题。  

---

### 推荐相似题目
1. [CF1540B] Tree Array（组合数学+期望）  
2. [Luogu P4213] 组合数问题（前缀和+数论分块）  
3. [CF1396C] Monster Invaders（离散化+贡献计算）  

---

### 可视化设计
**动画方案**：  
1. **像素风格界面**：  
   - **端点标记**：用红色/蓝色方块表示左右端点，绿色表示当前枚举的 x。  
   - **贡献计算**：左侧线段用红色箭头，右侧用蓝色箭头，组合数公式逐步显示。  
2. **音效与交互**：  
   - **步骤音效**：每次计算组合数时播放“点击”音效。  
   - **自动推导**：AI 自动枚举端点并高亮当前计算步骤，背景音乐为 8-bit 风格。  
3. **Canvas 绘制**：  
   - 动态绘制线段分布，滑动条调节枚举速度，积分显示当前累计贡献。  

**代码片段（伪代码）**：  
```javascript
// 初始化像素画布
const canvas = initCanvas('8-bit');
drawEndpoints(endpoints, colors);
// 自动枚举端点
for (let x of endpoints) {
    highlight(x, 'green');
    let cnt1 = getLeftCount(x);
    let cnt2 = getRightCount(x);
    playSound('step');
    drawCombinatorics(cnt1, cnt2);
    updateScore(calculateContribution(cnt1, cnt2));
    await sleep(speed);
}
```

---

### 核心代码实现
```cpp
// 预处理组合数
void init_C(int n) {
    fac[0] = 1;
    for(int i=1; i<=n; i++) fac[i] = 1ll*fac[i-1]*i%mod;
    inv[n] = qkpow(fac[n], mod-2);
    for(int i=n-1; i>=1; i--) inv[i] = 1ll*inv[i+1]*(i+1)%mod;
}
// 计算贡献
for(int i=1; i<=2*n; i++) {
    int val = rev[i], c1 = s1[i-1], c2 = s2[i+1];
    int val2 = dec(s4[i+1], 1ll*val*c2%mod);
    res = add(res, 1ll*val2 * mi[pro] % mod * binom(...));
}
```

---

### 个人心得
- **离散化技巧**：通过重新编号端点确保唯一性，避免边界条件错误。  
- **组合数优化**：识别范德蒙德卷积是减少复杂度的关键，需熟练掌握此类恒等式。  
- **调试经验**：前缀和数组大小需仔细检查，防止越界导致的未定义行为。

---
处理用时：87.90秒
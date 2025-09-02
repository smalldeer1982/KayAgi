# 题目信息

# Koxia and Tree

## 题目描述

Imi has an undirected tree with $ n $ vertices where edges are numbered from $ 1 $ to $ n-1 $ . The $ i $ -th edge connects vertices $ u_i $ and $ v_i $ . There are also $ k $ butterflies on the tree. Initially, the $ i $ -th butterfly is on vertex $ a_i $ . All values of $ a $ are pairwise distinct.

Koxia plays a game as follows:

- For $ i = 1, 2, \dots, n - 1 $ , Koxia set the direction of the $ i $ -th edge as $ u_i \rightarrow v_i $ or $ v_i \rightarrow u_i $ with equal probability.
- For $ i = 1, 2, \dots, n - 1 $ , if a butterfly is on the initial vertex of $ i $ -th edge and there is no butterfly on the terminal vertex, then this butterfly flies to the terminal vertex. Note that operations are sequentially in order of $ 1, 2, \dots, n - 1 $ instead of simultaneously.
- Koxia chooses two butterflies from the $ k $ butterflies with equal probability from all possible $ \frac{k(k-1)}{2} $ ways to select two butterflies, then she takes the distance $ ^\dagger $ between the two chosen vertices as her score.

Now, Koxia wants you to find the expected value of her score, modulo $ 998\,244\,353^\ddagger $ .

 $ ^\dagger $ The distance between two vertices on a tree is the number of edges on the (unique) simple path between them.

 $ ^\ddagger $ Formally, let $ M = 998\,244\,353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first test case, the tree is shown below. Vertices containing butterflies are noted as bold.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1770E/b5933c313633856733c2f7b6fac2b7be83ed7851.png)There are only $ 2 $ butterflies so the choice of butterflies is fixed. Let's consider the following $ 4 $ cases:

- Edges are $ 1 \rightarrow 2 $ and $ 2 \rightarrow 3 $ : butterfly on vertex $ 1 $ moves to vertex $ 2 $ , but butterfly on vertex $ 3 $ doesn't move. The distance between vertices $ 2 $ and $ 3 $ is $ 1 $ .
- Edges are $ 1 \rightarrow 2 $ and $ 3 \rightarrow 2 $ : butterfly on vertex $ 1 $ moves to vertex $ 2 $ , but butterfly on vertex $ 3 $ can't move to vertex $ 2 $ because it's occupied. The distance between vertices $ 2 $ and $ 3 $ is $ 1 $ .
- Edges are $ 2 \rightarrow 1 $ and $ 2 \rightarrow 3 $ : butterflies on both vertex $ 1 $ and vertex $ 3 $ don't move. The distance between vertices $ 1 $ and $ 3 $ is $ 2 $ .
- Edges are $ 2 \rightarrow 1 $ and $ 3 \rightarrow 2 $ : butterfly on vertex $ 1 $ doesn't move, but butterfly on vertex $ 3 $ move to vertex $ 2 $ . The distance between vertices $ 1 $ and $ 2 $ is $ 1 $ .

Therefore, the expected value of Koxia's score is $ \frac {1+1+2+1} {4} = \frac {5} {4} $ , which is $ 748\,683\,266 $ after modulo $ 998\,244\,353 $ .

In the second test case, the tree is shown below. Vertices containing butterflies are noted as bold. The expected value of Koxia's score is $ \frac {11} {6} $ , which is $ 831\,870\,296 $ after modulo $ 998\,244\,353 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1770E/c99c1f065a7b394b09acc90fcc6d66aa233890d9.png)

## 样例 #1

### 输入

```
3 2
1 3
1 2
2 3```

### 输出

```
748683266```

## 样例 #2

### 输入

```
5 3
3 4 5
1 2
1 3
2 4
2 5```

### 输出

```
831870296```

# AI分析结果



---

### 唯一算法分类  
**组合数学**

---

### 题解思路与算法要点  
#### **核心思路**
1. **贡献分解**：将总期望距离拆分为每条边的独立贡献，利用线性期望性质。
2. **动态概率维护**：维护每个节点存在蝴蝶的概率 $p_u$，处理边时根据方向调整概率。
3. **子树预处理**：DFS 预处理初始子树蝴蝶数量 $s_v$，计算静态贡献基础。
4. **四情况分析**：对每条边 $(u,v)$，分四种情况（都有/都无/单侧有蝴蝶）计算期望贡献。

#### **关键公式推导**
- **概率转移**：处理边 $(u,v)$ 后，两节点概率变为 $p_u = p_v = \frac{p_u + p_v}{2}$。
- **动态贡献计算**：  
  贡献分为四部分：  
  - $p_u \cdot p_v \cdot s_v(k-s_v)$（都不移动）  
  - $(1-p_u)(1-p_v) \cdot s_v(k-s_v)$（都不移动）  
  - $p_u(1-p_v) \cdot \frac{s_v(k-s_v) + (s_v+1)(k-s_v-1)}{2}$（u→v 移动概率 0.5）  
  - $(1-p_u)p_v \cdot \frac{s_v(k-s_v) + (s_v-1)(k-s_v+1)}{2}$（v→u 移动概率 0.5）

#### **解决难点**
- **动态调整子树大小**：蝴蝶移动最多改变子树大小 ±1，需正确建模概率影响。
- **模运算处理**：概率计算需处理模意义下的分数和负数，例如 $(1-p_u) \mod 998244353$。

---

### 题解评分 (≥4星)  
1. **hejianxing（5星）**  
   - 完整推导四种情况的贡献公式，代码清晰处理模运算。  
   - 关键优化：通过父子关系预处理子树大小，减少冗余计算。  
   - 代码片段：  
     ```cpp  
     ans = ((ans  
     + p[u] * p[v] % mod * s[v] % mod * (k - s[v]) % mod  
     + ... ) % mod + mod) % mod;  
     ```

2. **CbrX（5星）**  
   - 简化公式推导，强调概率转移的对称性。  
   - 代码结构紧凑，变量命名清晰，适合快速理解核心逻辑。  
   - 关键代码：  
     ```cpp  
     f[u] = f[v] = (f[u] + f[v]) * i2 % mod;  
     ```

3. **shinkuu（4星）**  
   - 明确分拆四类情况的贡献，注释详细。  
   - 预处理子树大小后直接计算，逻辑简明。  

---

### 最优思路提炼  
1. **边贡献分解**：将整体问题转化为每条边的独立贡献计算，避免处理复杂路径。
2. **概率动态更新**：通过 $\frac{p_u + p_v}{2}$ 对称更新概率，简化状态转移。
3. **子树预处理**：DFS 预处理初始子树蝴蝶数，快速计算基础贡献。
4. **模运算优化**：使用预计算逆元（如 `inv2 = 499122177`）加速分数计算。

---

### 同类型题与算法套路  
- **常见套路**：树上的期望贡献分解、动态概率维护、模意义下的分数运算。
- **类似题目**：  
  1. **洛谷 P6151**：[集体数] 动态维护路径贡献。  
  2. **洛谷 P3177**：[HAOI2015] 树上染色，统计边贡献。  
  3. **CF1392H**：期望与组合数学结合的分步处理。

---

### 推荐题目  
1. **P6151**（动态规划与期望结合）  
2. **P3177**（子树贡献统计）  
3. **CF1392H**（组合数学与模运算）

---

### 个人心得摘录  
- **概率转移细节**：处理 $(1-p_u)$ 时需显式取模避免负数（如 `(1-p_u+mod)%mod`）。
- **父子关系预处理**：DFS 中固定 $u$ 为 $v$ 的父节点，确保子树大小计算正确性。

---

### 可视化与算法演示  
#### **动画方案设计**
- **树形结构绘制**：Canvas 绘制树，节点标记初始蝴蝶位置，边编号高亮处理。
- **逐步处理边**：当前边 $(u,v)$ 闪烁，显示其方向选择概率（50%双向）。
- **概率更新效果**：节点 $u$ 和 $v$ 颜色渐变反映 $p_u, p_v$ 变化（如绿色深浅表概率）。
- **贡献计算弹幕**：实时显示当前边的四类贡献计算式和累加结果。

#### **复古像素风格实现**  
- **颜色方案**：16 色调色板，节点用 8x8 像素块，边用 1px 线条。  
- **音效设计**：  
  - **移动成功**：8-bit "哔"声。  
  - **贡献计算**：短促 "滴"声。  
- **自动演示模式**：AI 模拟边处理顺序，自动播放推导步骤。

#### **交互功能**  
- **步进控制**：空格键单步执行边处理，方向键调整动画速度。  
- **贡献对比视图**：分屏显示四类贡献的公式和当前值，颜色区分计算项。

---

### 核心代码片段（C++）  
```cpp
// 概率转移与贡献计算（hejianxing 题解核心逻辑）
LL inv2 = qpow(2, mod - 2);
for (每条边 (u, v)) {
    if (fa[v] != u) swap(u, v); // 确保 u 是父节点
    LL pu = p[u], pv = p[v];
    LL term1 = pu * pv % mod * s[v] % mod * (k - s[v]) % mod;
    LL term2 = (1 - pu) * (1 - pv) % mod * s[v] % mod * (k - s[v]) % mod;
    LL term3 = pu * (1 - pv) % mod * inv2 % mod * 
        (s[v]*(k-s[v]) + (s[v]+1)*(k-s[v]-1)) % mod;
    LL term4 = (1 - pu) * pv % mod * inv2 % mod * 
        (s[v]*(k-s[v]) + (s[v]-1)*(k-s[v]+1)) % mod;
    ans = (ans + term1 + term2 + term3 + term4) % mod;
    p[u] = p[v] = (pu + pv) * inv2 % mod; // 概率对称更新
}
```

---

通过上述分析，该题的核心在于组合数学中的期望分解与动态概率维护，结合树结构的预处理和模运算优化，最终实现高效计算。

---
处理用时：81.31秒
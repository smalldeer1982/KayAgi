# 题目信息

# Doremy's Pegging Game

## 题目描述

Doremy has $ n+1 $ pegs. There are $ n $ red pegs arranged as vertices of a regular $ n $ -sided polygon, numbered from $ 1 $ to $ n $ in anti-clockwise order. There is also a blue peg of slightly smaller diameter in the middle of the polygon. A rubber band is stretched around the red pegs.

Doremy is very bored today and has decided to play a game. Initially, she has an empty array $ a $ . While the rubber band does not touch the blue peg, she will:

1. choose $ i $ ( $ 1 \leq i \leq n $ ) such that the red peg $ i $ has not been removed;
2. remove the red peg $ i $ ;
3. append $ i $ to the back of $ a $ .

Doremy wonders how many possible different arrays $ a $ can be produced by the following process. Since the answer can be big, you are only required to output it modulo $ p $ . $ p $ is guaranteed to be a prime number.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764D/39b25225514736b577fbcbcd5d0b5bf29ecc4db4.png) game with $ n=9 $ and $ a=[7,5,2,8,3,9,4] $ and another game with $ n=8 $ and $ a=[3,4,7,1,8,5,2] $

## 说明/提示

In the first test case, $ n=4 $ , some possible arrays $ a $ that can be produced are $ [4,2,3] $ and $ [1,4] $ . However, it is not possible for $ a $ to be $ [1] $ or $ [1,4,3] $ .

## 样例 #1

### 输入

```
4 100000007```

### 输出

```
16```

## 样例 #2

### 输入

```
1145 141919831```

### 输出

```
105242108```

# AI分析结果



---

### 算法分类
组合数学

---

### 题解思路、算法要点与解决难点

**核心问题转化**：当移除的钉子形成连续至少 $\lfloor n/2 \rfloor$ 个的缺口时，操作停止。需统计所有移除序列，满足最后一次操作使缺口达到阈值，且之前未触发条件。

**关键思路**：
1. **对称性简化**：假设最后一个移除的钉子为 $n$，最终结果乘 $n$（环状对称）。
2. **缺口枚举**：缺口由左侧连续移除 $s$ 个和右侧连续移除 $t$ 个组成，满足 $s + t \geq \lfloor n/2 \rfloor - 1$。
3. **组合排列计算**：剩余钉子中选择 $i$ 个，计算组合数 $C(M, i)$ 与排列数 $(m+i)!$，其中 $M = \max(0, n - m - 3)$。

**难点解决**：
- **避免重复计数**：通过固定最后一个钉子位置，利用对称性避免环状重复。
- **动态规划/组合优化**：预处理阶乘与逆元加速组合计算，时间复杂度 $O(n^2)$。

---

### 题解评分（≥4星）

1. **VinstaG173（5星）**
   - **亮点**：清晰的数学推导，预处理阶乘优化计算，代码简洁高效。
   - **代码**：利用对称性枚举缺口总和 $m$，组合数快速求解。

2. **honglan0301（4星）**
   - **亮点**：动态规划定义状态 $f(i,j)$，直观枚举缺口位置。
   - **不足**：未明确处理偶数特殊情况，代码可读性稍逊。

3. **Alex_Wei（4星）**
   - **亮点**：缺口距离枚举，结合奇偶性分类讨论。
   - **不足**：公式描述稍简略，需结合代码理解。

---

### 最优思路或技巧提炼

1. **对称性固定末尾元素**：将环状问题转化为线性，简化计算。
2. **缺口参数化枚举**：将缺口长度和位置参数化为 $m = s + t$，避免环状复杂计算。
3. **组合数+排列数快速计算**：预处理阶乘及逆元，快速求组合数与排列数乘积。

---

### 同类型题与算法套路

- **环形排列问题**：通常利用对称性固定起始点或末尾元素。
- **组合计数优化**：预处理阶乘/逆元，快速计算组合排列。
- **动态规划枚举状态**：定义缺口长度、位置等状态转移方程。

**类似题目推荐**：
1. [P1350 车的放置](https://www.luogu.com.cn/problem/P1350)（组合数应用）
2. [P3197 越狱](https://www.luogu.com.cn/problem/P3197)（排列组合逆向思维）
3. [CF559C Gerald and Giant Chess](https://codeforces.com/problemset/problem/559/C)（组合数+动态规划）

---

### 代码核心实现

**VinstaG173 的代码片段**：
```cpp
void solve() {
    int n, mod; 
    cin >> n >> mod;
    vector<ll> fac(n+1), fic(n+1);
    fac[0] = 1;
    for (int i=1; i<=n; ++i) fac[i] = fac[i-1] * i % mod;
    fic[n] = pow_mod(fac[n], mod-2, mod); // 逆元
    for (int i=n; i>=1; --i) fic[i-1] = fic[i] * i % mod;
    
    ll res = 0;
    int c = n / 2;
    for (int m = c-1; m <= n-3; ++m) { // 枚举缺口总和 m = s + t
        ll tmp = 0;
        int M = max(0, n - m - 3);
        for (int i=0; i<=M; ++i) { // 选择 i 个额外钉子
            tmp = (tmp + fac[m+i] * comb(M, i)) % mod;
        }
        res = (res + (2*c - m - 1) * tmp) % mod;
    }
    if (n % 2 == 0) // 处理偶数特殊情况
        res = (res + fac[n-2]) % mod;
    res = res * n % mod; // 乘对称性
    cout << res << endl;
}
```

---

### 可视化与算法演示

**动画设计**：
1. **环形钉子布局**：红色钉子围成环，蓝色居中。橡皮筋动态收缩。
2. **缺口高亮**：当连续移除钉子数达到阈值时，高亮缺口区域。
3. **步进移除**：点击单步演示移除过程，实时检测缺口条件。

**复古像素风格**：
- **Canvas 绘制**：钉子为像素点，缺口用闪烁色块标记。
- **音效触发**：移除钉子时播放“点击”音效，达成条件时播放胜利音效。
- **自动演示模式**：AI 模拟最优移除路径，动态显示组合计算过程。

**交互功能**：
- **速度调节**：滑动条控制动画速度。
- **关卡模式**：不同 $n$ 值为独立关卡，积分奖励正确解答。

---
处理用时：228.33秒
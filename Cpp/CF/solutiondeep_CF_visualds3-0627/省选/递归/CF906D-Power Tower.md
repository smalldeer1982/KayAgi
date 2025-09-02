# 题目信息

# Power Tower

## 题目描述

Priests of the Quetzalcoatl cult want to build a tower to represent a power of their god. Tower is usually made of power-charged rocks. It is built with the help of rare magic by levitating the current top of tower and adding rocks at its bottom. If top, which is built from $ k-1 $ rocks, possesses power $ p $ and we want to add the rock charged with power $ w_{k} $ then value of power of a new tower will be $ {w_{k}}^{p} $ .

Rocks are added from the last to the first. That is for sequence $ w_{1},...,w_{m} $ value of power will be

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF906D/a7b9adfbee151f2e3ef09f9dbad2cf6b657882ca.png)After tower is built, its power may be extremely large. But still priests want to get some information about it, namely they want to know a number called cumulative power which is the true value of power taken modulo $ m $ . Priests have $ n $ rocks numbered from $ 1 $ to $ n $ . They ask you to calculate which value of cumulative power will the tower possess if they will build it from rocks numbered $ l,l+1,...,r $ .

## 说明/提示

 $ 3^{27}=7625597484987 $

## 样例 #1

### 输入

```
6 1000000000
1 2 2 3 3 3
8
1 1
1 6
2 2
2 3
2 4
4 4
4 5
4 6
```

### 输出

```
1
1
2
4
256
3
27
597484987
```

# AI分析结果



---

## 算法分类  
**扩展欧拉定理**

---

## 综合分析与结论  
### 题目核心逻辑  
计算形如 $w_l^{w_{l+1}^{w_{l+2}^{\cdots^{w_r}}}} \bmod m$ 的塔式幂模。直接计算指数不可行，需用扩展欧拉定理递归降幂：

$$
a^c \equiv 
\begin{cases}
a^c & c < \varphi(p) \\
a^{c \bmod \varphi(p) + \varphi(p)} & \text{otherwise}
\end{cases} \pmod{p}
$$

### 核心难点与解决方案  
1. **递归边界与模数衰减**  
   - 每层递归将模数 $p$ 替换为其欧拉函数 $\varphi(p)$，$\varphi(p)$ 的衰减速度是 $\log$ 级（至少折半），递归最多 $\log m$ 层。
   - 预处理所有可能的 $\varphi(p)$ 值存入哈希表，避免重复计算。

2. **快速幂的扩展处理**  
   - 快速幂需维护两种状态：实际值和是否超过当前模数。若中间结果 $\ge$ 当前模数，需保留余数 + 模数的形式，以满足扩展定理条件。

3. **递归终止条件**  
   - 当模数 $p=1$ 或达到序列末尾时返回 $1$（任何数模 $1$ 为 $0$），但需根据实际情况调整返回值。

### 可视化设计思路  
1. **递归过程动画**  
   - **颜色标记**：当前递归层数的模数用不同颜色高亮，如红色表示初始模数，蓝色表示 $\varphi(p)$，绿色表示 $\varphi(\varphi(p))$。
   - **步进控制**：展示每一步递归调用和返回值的计算过程，如用户点击“下一步”时展开当前指数计算。

2. **像素风格展示**  
   - 用 8-bit 像素风格显示递归树，每个节点表示一个模数 $p$，子节点为 $\varphi(p)$。
   - 音效触发：递归进入下一层时播放“滴”声，返回结果时播放“叮”声，模数变为 $1$ 时播放成功音效。

3. **交互式比较**  
   - 并行展示不同题解的递归路径，对比快速幂中是否保留余数 + 模数的差异（如题解 C20203030 与 suxxsfe 的实现）。

---

## 题解清单 (≥4星)  
### 1. C20203030（⭐⭐⭐⭐⭐）  
**关键亮点**：  
- 预处理 $\varphi$ 值存入 `map`，避免重复计算。  
- 快速幂中动态判断是否超过模数，维护余数 + 模数的形式。  
- 代码注释详细，递归出口处理清晰。  

**代码片段**：  
```cpp
int qkpow(int a, int b, int MOD) {
    int res = 1;
    while (b > 0) {
        if (b & 1) {
            res = res * a;
            if (res >= MOD) res = res % MOD + MOD; // 保留余数 + MOD
        }
        a = a * a;
        if (a >= MOD) a = a % MOD + MOD; // 维护余数 + MOD
        b >>= 1;
    }
    return res;
}
```

### 2. suxxsfe（⭐⭐⭐⭐⭐）  
**关键亮点**：  
- 递归函数直接返回余数 + 模数的形式，避免额外标志位。  
- 预处理 $\varphi$ 的 `map` 用法简洁高效。  

**代码片段**：  
```cpp
int power(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) res = mo(1LL * res * a, mod);
        a = mo(1LL * a * a, mod);
        b >>= 1;
    }
    return res; // 返回值已包含余数 + MOD（若需要）
}
```

### 3. OldVagrant（⭐⭐⭐⭐）  
**关键亮点**：  
- 使用结构体 `flag` 同时返回值和是否超过模数的标志。  
- 通过二元组传递状态，严格遵循扩展定理条件。  

**代码片段**：  
```cpp
flag qpow(int a, int b, int p) {
    flag tmp;
    int ans = 1, flag = 0;
    if (a >= p) a = a % p + p; // 预处理 a 的余数
    while (b) {
        if (b & 1) ans = ans * a;
        if (ans >= p) flag = 1, ans %= p; // 设置标志位
        a = a * a;
        if (a >= p) a = a % p + p;
        b >>= 1;
    }
    tmp.val = ans;
    tmp.big = flag;
    return tmp;
}
```

---

## 最优思路提炼  
1. **预处理欧拉函数**  
   - 用哈希表存储所有可能的 $\varphi(p)$，递归时直接查询。  
2. **递归降幂公式**  
   - 若当前指数 $c \ge \varphi(p)$，则 $a^c \equiv a^{c \bmod \varphi(p) + \varphi(p)} \pmod{p}$。  
3. **快速幂的余数维护**  
   - 快速幂中若中间结果 $\ge$ 当前模数，保留 `余数 + 模数` 的形式以满足后续递归条件。  

---

## 同类题目推荐  
1. **P4139 上帝与集合的正确用法**  
   - 计算无限塔式幂 $2^{2^{2^{\cdots}}} \bmod p$，同样需扩展欧拉定理。  
2. **CF17D Notepad**  
   - 计算 $(b-1) \cdot b^{n-1} \bmod c$，需处理大指数取模。  
3. **UOJ228 基础数据结构练习题**  
   - 区间开根与区间和查询，类似的分治降复杂度思想。  

---

## 个人心得摘录  
- **调试教训**：快速幂中若未正确处理余数 + 模数，会导致递归层数错误（如题解 C20203030 的注释强调必须保留余数）。  
- **顿悟点**：欧拉函数的衰减速度保证了递归层数为 $\log m$ 级别，无需担心栈溢出。  

---

## 代码实现（核心逻辑）  
```cpp
#include <map>
using namespace std;

map<int, int> phi_cache;

int phi(int n) {
    if (phi_cache.count(n)) return phi_cache[n];
    int res = n, t = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res = res / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) res = res / n * (n - 1);
    return phi_cache[t] = res;
}

int mod_pow(int a, int b, int mod) {
    int res = 1;
    bool over = false;
    a %= mod;
    while (b) {
        if (b & 1) {
            if (res > mod / a) over = true;
            res = res * a % mod;
        }
        if (a > mod / a) over = true;
        a = a * a % mod;
        b >>= 1;
    }
    return over ? res + mod : res;
}

int tower_pow(int l, int r, int mod) {
    if (mod == 1) return 0;
    if (l == r) return w[l] % mod + (w[l] >= mod ? mod : 0);
    int p = phi(mod);
    int exp = tower_pow(l + 1, r, p);
    return mod_pow(w[l], exp, mod);
}
```

---

## 可视化与复古游戏设计  
### 动画方案  
- **Canvas 绘制递归树**：每个节点为当前模数 $p$，边表示 $\varphi(p)$ 的衰减。  
- **颜色标记**：初始模数用红色，$\varphi(p)$ 用渐变的蓝色，模数 $1$ 用绿色。  
- **音效设计**：  
  - `pow_sound.wav`：快速幂计算时播放。  
  - `phi_sound.wav`：进入新递归层时播放。  
  - `success.wav`：模数变为 $1$ 时播放。  

### 自动演示模式  
- **AI 决策逻辑**：自动展开最左侧未计算的指数，模拟递归深度优先搜索。  
- **积分系统**：每正确计算一层模数得 10 分，错误操作扣 5 分。  

### 像素风格实现  
```javascript
// 示例：绘制递归树节点
function drawNode(ctx, x, y, p, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x, y, 32, 32); // 32x32 像素方块
    ctx.fillStyle = '#000';
    ctx.fillText(p.toString(), x + 8, y + 20);
}
```

---

**注**：以上内容整合了各题解的核心思路与优化技巧，重点突出扩展欧拉定理的递归应用与快速幂的余数维护机制。

---
处理用时：103.57秒
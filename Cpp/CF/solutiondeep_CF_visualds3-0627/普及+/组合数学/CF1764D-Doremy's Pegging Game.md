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



**1. 算法分类**  
组合数学/计数问题

---

**2. 综合分析与结论**  
**核心难点**：  
- 确定合法操作序列的充要条件：最后一步必须形成至少 $\lfloor n/2 \rfloor$ 个连续移除的钉子，且此前无此情况。  
- 利用环状结构的对称性简化计算，通过组合数学精确计数。

**算法要点**：  
1. **对称性简化**：只需计算最后一个钉子为固定位置（如 $n$）的情况，最终答案乘 $n$。  
2. **连续段分析**：枚举最终形成的连续段长度，计算其两侧的扩展范围（递增/递减序列长度 $s,t$）。  
3. **组合数+阶乘**：预处理阶乘和组合数模 $p$，计算剩余钉子的自由排列方式。  
4. **特判处理**：当 $n$ 为偶数时，可能存在只剩一个钉子的特殊情况。

**可视化设计**：  
- **动画方案**：  
  - 展示正多边形钉子的逐步移除过程，用红色高亮最后形成的连续段。  
  - 每次移除钉子时，动态检查是否形成 $\lfloor n/2 \rfloor$ 连续段，触发停止条件。  
- **颜色标记**：  
  - 蓝色：未移除的钉子  
  - 灰色：已移除的钉子  
  - 红色闪烁：最后一步触发的连续段  
- **复古像素风**：  
  - 用 8-bit 风格绘制多边形钉子和橡皮筋  
  - 音效：移除钉子时播放短促电子音，达成条件时播放胜利音效  

---

**3. 题解清单（≥4星）**  
**VinstaG173（★★★★☆）**  
- 亮点：利用对称性将问题转化为固定最后一个钉子的情况，数学推导严密，代码简洁高效。  
- 关键代码：  
  ```cpp
  for(rg int m=n/2-1;m<n-2;++m){
    tmp=0;for(rg int i=0;i<=n-m-3;++i){
      tmp=(tmp+fac[m+i]*C(n-m-3,i))%ntf;
    }res=(res+(n-(n&1)-1-m)*tmp)%ntf;
  }  
  ```

**Alex_Wei（★★★★☆）**  
- 亮点：通过枚举两侧点间距 $i$ 和保留钉子数 $j$，清晰分离变量，特判处理优雅。  
- 关键公式：  
  $$ \text{ans} = n \sum_i r \times \sum_{j=0}^{i-2} \binom{i-2}{j} (n-3-j)! $$

**MortisM（★★★☆☆）**  
- 亮点：直接枚举连续段长度 $l$，代码逻辑直白，但缺少特判说明。  

---

**4. 最优思路提炼**  
- **对称性转换**：通过固定最后一个钉子简化计算，答案乘 $n$。  
- **双指针扩展**：通过分析连续段两侧的递增/递减序列（$s$ 和 $t$），确定剩余钉子的自由排列空间。  
- **组合爆炸剪枝**：预处理阶乘和逆元加速组合数计算，时间复杂度优化至 $O(n^2)$。  

---

**5. 相似题目推荐**  
1. [CF1392E - Omkar and Duck](https://codeforces.com/problemset/problem/1392/E)（组合路径计数）  
2. [洛谷 P3773 - 计数](https://www.luogu.com.cn/problem/P3773)（模素数下的组合数计算）  
3. [ARC087D - Squirrel Migration](https://atcoder.jp/contests/arc087/tasks/arc087_d)（环状结构的组合计数）  

---

**6. 核心代码实现**  
预处理阶乘和逆元的代码片段：  
```cpp
fac[0] = 1;
for(int i=1; i<=n; i++) fac[i] = fac[i-1] * i % mod;
fic[n] = qpow(fac[n], mod-2, mod);
for(int i=n; i>=1; i--) fic[i-1] = fic[i] * i % mod;
```

组合数计算逻辑：  
```cpp
ll C(int m, int k) {
    return fac[m] * fic[k] % mod * fic[m-k] % mod;
}
```

---

**7. 可视化交互设计**  
- **Canvas 绘制**：  
  - 初始化正多边形，每个钉子用 8×8 像素方块表示。  
  - 点击钉子触发移除动画，自动检测连续段。  
- **音效触发**：  
  ```javascript
  function playSound(effect) {
    const sfx = {
      remove: new Audio('data:audio/wav;base64,UklGRl9...'),
      win: new Audio('data:audio/wav;base64,UklGRho...')
    };
    sfx[effect].play();
  }
  ```
- **自动演示模式**：  
  ```javascript
  function autoPlay() {
    let steps = generateValidSequence();
    steps.forEach((peg, i) => {
      setTimeout(() => highlightPeg(peg), i * 500);
    });
  }
  ```

---
处理用时：67.10秒
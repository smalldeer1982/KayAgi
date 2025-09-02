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


### 💡 Kay的C++算法解析：Doremy's Pegging Game 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`组合计数`与`环上枚举`  
🗣️ **初步分析**：
> 本题是经典的环上组合计数问题，可类比为"圆桌骑士移除"：移除骑士时，若被移除的骑士在圆桌上有连续≥⌊n/2⌋个座位空出，则中央宝物掉落。核心技巧是通过对称性固定最后一个移除的钉子（如n号），最后乘以n处理环的对称性。  
> - **核心思路**：枚举连续移除段的长度l（从⌊n/2⌋开始），计算该段长度下，最后一个钉子的位置选择数r，并统计非连续段区域的额外移除方案。
> - **难点**：确保移除序列的最后一个操作才触发连续条件（之前不满足），需推导连续段长度l与位置选择数r的关系：r = 2⌊n/2⌋ - l。
> - **可视化设计**：采用8位像素风格圆桌，红钉用彩色像素表示，移除时播放"咔嚓"音效。当连续移除段≥⌊n/2⌋时，橡皮筋收缩并播放"胜利"音效。关键高亮：当前移除钉、连续段长度计数条、可用额外移除区（绿色边框）。

---

#### 2. 精选优质题解参考
**题解一：VinstaG173（思路严谨）**  
* **点评**：  
  通过对称性固定最后一个钉子，枚举连续段长度l及额外移除数x，组合数+阶乘直接计数。亮点在：  
  1. 利用环对称性简化计数（*n处理）  
  2. 清晰推导可用钉子数available = max(0, n-l-2)  
  3. 代码简洁（预处理阶乘+逆元），时间复杂度O(n²)  
  代码规范：变量名`fac/fic`含义明确，边界处理严谨（available为负时取0）。

**题解二：MortisM（枚举直观）**  
* **点评**：  
  直接枚举连续段长度l和额外移除数x，给出直观公式：  
  `ans += (2c-l) * C(available,x) * fac[l+x-1]`。  
  亮点：  
  1. 用`available = n-l-2`精准描述非连续区  
  2. 用`(l+x-1)!`处理前序操作排列  
  实践价值高：代码可直接用于竞赛（注意n为偶数时无额外特判）。

**题解三：Alex_Wei（变量命名优）**  
* **点评**：  
  枚举"绑定点距离i"，通过`r = i`（偶）或`i-1`（奇）计算最后一个钉子的位置选择。亮点：  
  1. 关键变量名`i/r`直击物理意义  
  2. 用`(n-3-j)!`高效处理排列  
  代码可读性强：`for`循环范围明确（偶：i∈[1,⌊n/2⌋]，奇：i∈[2,⌊(n+1)/2⌋]）。

---

#### 3. 核心难点辨析与解题策略
1.  **难点：最后操作的触发时机**  
    * **分析**：需确保移除序列的最后一个操作才首次满足连续段≥⌊n/2⌋。优质题解通过`r = 2c - l`确保：在移除最后钉子前，连续段长度=l-1 < c。  
    * 💡 **学习笔记**：关键变量`l`必须≥c，且`r>0`时方案才合法。

2.  **难点：环上连续段的表示**  
    * **分析**：利用钉子位置的对称性，固定最后一个钉子为n，最终结果*n。非连续区用`available = n-l-2`表示（两段保留区各1钉）。  
    * 💡 **学习笔记**：组合数`C(available,x)`高效处理非连续区方案。

3.  **难点：排列数计算**  
    * **分析**：前l+x-1个操作可任意排列（最后1钉固定），故乘以`fac[l+x-1]`。  
    * 💡 **学习笔记**：阶乘预处理将O(n!)优化至O(1)查询。

### ✨ 解题技巧总结
- **环对称转换**：固定最后1钉位置，计数值*n  
- **分块枚举法**：连续段(l)与非连续区(x)独立计算  
- **组合数优化**：预处理阶乘+逆元，避免重复计算  
- **边界处理**：available<0时取0，避免非法访问

---

#### 4. C++核心代码实现赏析
**本题通用核心C++实现参考**  
* **说明**：综合VinstaG173和MortisM思路，无额外特判（n=4验证通过）  
* **完整核心代码**：
```cpp
#include <iostream>
using namespace std;
typedef long long ll;

ll qpow(ll base, ll exp, ll mod) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

int main() {
    int n, p;
    cin >> n >> p;
    ll fac[5005] = {1}, inv[5005];
    for (int i = 1; i <= n; i++) fac[i] = fac[i-1] * i % p;
    inv[n] = qpow(fac[n], p-2, p);
    for (int i = n; i; i--) inv[i-1] = inv[i] * i % p;

    auto C = [&](int m, int k) -> ll {
        if (k < 0 || k > m) return 0;
        return fac[m] * inv[k] % p * inv[m-k] % p;
    };

    int c = n / 2;
    ll ans = 0;
    for (int l = c; l < n; l++) {
        int r = 2 * c - l;
        if (r <= 0) continue;
        int available = n - l - 2;
        if (available < 0) available = 0;
        for (int x = 0; x <= available; x++) {
            ans = (ans + r * C(available, x) % p * fac[l+x-1]) % p;
        }
    }
    cout << ans * n % p << endl;
}
```
* **代码解读概要**：  
  1. 预处理阶乘`fac[]`和逆元`inv[]`（费马小定理）  
  2. 枚举连续段长`l`（从`c`到`n-1`）  
  3. 计算位置选择数`r = 2c - l`（跳过非法值）  
  4. 组合数`C(available,x)`选额外移除钉  
  5. 排列数`fac[l+x-1]`处理前序操作顺序  
  6. 最终`*n`处理环对称性

---

#### 5. 算法可视化：像素动画演示
**动画演示主题**：`圆桌骑士-8位像素版`  
**核心演示**：橡皮筋接触蓝钉的临界条件触发  
**设计思路**：  
- **8位像素风**：圆桌=像素圆（FC红白机配色），红钉=16色像素块  
- **音效设计**：移除钉→"咔嚓"声；达成条件→16bit胜利音效  
- **游戏化**：每关对应不同n值，通关要求：找到所有合法移除序列  

**关键帧步骤**：  
1. **初始化**：绘制正n边形红钉（编号1~n），中央蓝钉  
   - 控制面板：开始/暂停、单步、速度滑块  
2. **移除操作**：  
   - 点击钉子→高亮闪烁+播放"咔嚓"声  
   - 实时标记：当前移除钉（红色）、连续段（黄色边框）  
3. **连续段检测**：  
   - 当连续移除段≥⌊n/2⌋：橡皮筋收缩+蓝钉闪烁+播放胜利音效  
   - 显示公式：`r = 2c-l`（当前连续段长l）  
4. **AI演示模式**：  
   - 自动模拟所有合法序列，速度可调  
   - 当前步骤对应代码行高亮（如`C(available,x)`）  

---

#### 6. 拓展练习与相似问题思考
**通用技巧迁移**：  
1. 环上连续区间的计数（如圆桌骑士、钟表刻度）  
2. 组合数+排列数的联合应用  
3. 对称性优化（固定锚点）  

**洛谷练习推荐**：  
1. **P1246 编码**  
   🗣️ 练习组合计数基本应用  
2. **P1371 NOI元丹**  
   🗣️ 环上区间计数+前缀和优化  
3. **P2364 木偶剧**  
   🗣️ 复杂移除序列的计数（需处理条件触发）  

---

#### 7. 学习心得与经验分享
> **经验摘录（VinstaG173）**：  
> "边界处理时，`available = n-l-2`可能为负，需`max(0,available)`"  
> **点评**：  
> 这是组合计数中`防越界`的典型技巧，建议：  
> 1. 用`if(available<0) available=0`代替直接访问  
> 2. 测试n=3,4,5的边界值  

---

通过本次分析，我们深入掌握了环上组合计数的核心技巧。记得多写测试用例验证边界！下次挑战见！💪

---
处理用时：426.81秒
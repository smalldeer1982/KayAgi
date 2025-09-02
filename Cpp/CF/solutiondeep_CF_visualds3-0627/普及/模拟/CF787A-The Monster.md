# 题目信息

# The Monster

## 题目描述

A monster is chasing after Rick and Morty on another planet. They're so frightened that sometimes they scream. More accurately, Rick screams at times $ b,b+a,b+2a,b+3a,... $ and Morty screams at times $ d,d+c,d+2c,d+3c,... $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF787A/23c11249630f1c4252ef0b9cda8ec1bf9b317b5a.png)The Monster will catch them if at any point they scream at the same time, so it wants to know when it will catch them (the first time they scream at the same time) or that they will never scream at the same time.

## 说明/提示

In the first sample testcase, Rick's $ 5 $ th scream and Morty's $ 8 $ th time are at time $ 82 $ .

In the second sample testcase, all Rick's screams will be at odd times and Morty's will be at even times, so they will never scream at the same time.

## 样例 #1

### 输入

```
20 2
9 19
```

### 输出

```
82
```

## 样例 #2

### 输入

```
2 1
16 12
```

### 输出

```
-1
```

# AI分析结果



**唯一算法分类**：数论（贝祖定理应用）与模拟

---

### **综合分析与结论**

**题目核心**：寻找两个等差数列首次相等的项，即解方程 `b + a*x = d + c*y`，其中 `x,y` 是非负整数。

**核心难点**：
1. **存在性判断**：无解情况（如奇偶性冲突、无法满足同余条件）。
2. **高效求解**：避免暴力枚举的潜在高时间复杂度。

**最优解法思路**：
1. **数论判断**：利用贝祖定理，若 `(d - b) % gcd(a, c) ≠ 0`，则无解。
2. **模拟调整**：通过交替增加较大的时间值，快速逼近相等点。

**算法流程**：
1. **计算最大公约数** `k = gcd(a, c)`，若 `(d - b) % k ≠ 0`，直接输出 `-1`。
2. **模拟递增**：每次将较小的 `b` 或 `d` 加上对应的步长 `a` 或 `c`，直到两者相等。

**可视化设计**：
- **动画效果**：两个时间轴分别标记 `Rick` 和 `Morty` 的当前时间，高亮调整后的值。
- **颜色标记**：红色箭头指向当前操作的时间轴（例如 `b < d` 时，红色箭头在 `Rick` 侧）。
- **音效触发**：每次递增时播放“滴答”音效，相等时播放成功音效（8-bit 风格）。
- **自动演示**：设置默认速度，允许用户调整步进间隔，观察调整过程。

---

### **题解评分（≥4星）**

1. **Alex_Wei（★★★★★）**
   - **亮点**：结合贝祖定理快速判断无解，模拟调整高效。
   - **代码**：简洁易懂，时间复杂度接近 `O(|d - b| / gcd(a, c))`。

2. **sodak（★★★★）**
   - **亮点**：与 Alex_Wei 思路一致，代码更简短。
   - **优化点**：直接递增较大值，无冗余判断。

3. **肖恩Sean（★★★★）**
   - **亮点**：使用扩展欧几里得算法解同余方程，数学严谨。
   - **适用场景**：适合更大数据范围，但代码复杂度较高。

---

### **最优思路提炼**

**关键技巧**：
1. **贝祖定理判断存在性**：将问题转化为线性方程求解，避免无效计算。
2. **贪心调整策略**：每次仅调整较小的时间值，确保逐步逼近解。

**代码实现核心**：
```cpp
int k = gcd(a, c);
if ((d - b) % k != 0) cout << -1;
else {
    while (b != d) {
        if (b < d) b += a;
        else d += c;
    }
    cout << b;
}
```

---

### **同类型题拓展**

1. **线性同余方程**：如 `a*x ≡ b (mod m)` 的求解。
2. **最小公共倍数**：利用 `gcd` 和 `lcm` 处理周期性事件。
3. **双指针调整**：类似合并有序链表的思路，交替推进指针。

**洛谷推荐题目**：
1. **P1516** 青蛙的约会（扩展欧几里得经典题）
2. **P2421** 荒岛野人（同余与周期冲突）
3. **P1082** 同余方程（扩展欧几里得基础）

---

### **个人心得摘录**

- **xujian**：暴力枚举需注意边界，`100` 次循环足够覆盖本题数据。
- **Alex_Wei**：贝祖定理的应用是关键，避免无效循环。
- **肖恩Sean**：扩展欧几里得虽复杂，但通用性强，适合深入学习。

---

### **可视化与复古游戏化设计**

**动画方案**：
- **Canvas 绘制**：横向时间轴，`Rick` 和 `Morty` 的当前时间用像素方块表示。
- **步进效果**：每次递增时，对应方块向右跳跃，伴随 `8-bit` 音效。
- **成功动画**：时间相等时，方块爆炸为像素粒子，背景音乐切换为胜利旋律。

**代码片段（JS 伪代码）**：
```javascript
function simulate() {
    let b = rickStart, d = mortyStart;
    while (b !== d) {
        if (b < d) {
            b += a;
            playSound('rick_step'); // 播放 Rick 步进音效
        } else {
            d += c;
            playSound('morty_step'); // 播放 Morty 步进音效
        }
        updateCanvas(b, d); // 更新 Canvas 显示
    }
    playSound('success'); // 成功音效
}
```

**复古风格**：
- **调色板**：16 色 FC 风格，红色（Rick）、绿色（Morty）、黄色（爆炸）。
- **背景音乐**：循环播放低比特率芯片音乐，音效使用简单方波生成。

---
处理用时：74.59秒
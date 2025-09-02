# 题目信息

# Border

## 题目描述

Astronaut Natasha arrived on Mars. She knows that the Martians are very poor aliens. To ensure a better life for the Mars citizens, their emperor decided to take tax from every tourist who visited the planet. Natasha is the inhabitant of Earth, therefore she had to pay the tax to enter the territory of Mars.

There are $ n $ banknote denominations on Mars: the value of $ i $ -th banknote is $ a_i $ . Natasha has an infinite number of banknotes of each denomination.

Martians have $ k $ fingers on their hands, so they use a number system with base $ k $ . In addition, the Martians consider the digit $ d $ (in the number system with base $ k $ ) divine. Thus, if the last digit in Natasha's tax amount written in the number system with the base $ k $ is $ d $ , the Martians will be happy. Unfortunately, Natasha does not know the Martians' divine digit yet.

Determine for which values $ d $ Natasha can make the Martians happy.

Natasha can use only her banknotes. Martians don't give her change.

## 说明/提示

Consider the first test case. It uses the octal number system.

If you take one banknote with the value of $ 12 $ , you will get $ 14_8 $ in octal system. The last digit is $ 4_8 $ .

If you take one banknote with the value of $ 12 $ and one banknote with the value of $ 20 $ , the total value will be $ 32 $ . In the octal system, it is $ 40_8 $ . The last digit is $ 0_8 $ .

If you take two banknotes with the value of $ 20 $ , the total value will be $ 40 $ , this is $ 50_8 $ in the octal system. The last digit is $ 0_8 $ .

No other digits other than $ 0_8 $ and $ 4_8 $ can be obtained. Digits $ 0_8 $ and $ 4_8 $ could also be obtained in other ways.

The second test case uses the decimal number system. The nominals of all banknotes end with zero, so Natasha can give the Martians only the amount whose decimal notation also ends with zero.

## 样例 #1

### 输入

```
2 8
12 20
```

### 输出

```
2
0 4 ```

## 样例 #2

### 输入

```
3 10
10 20 30
```

### 输出

```
1
0 ```

# AI分析结果



# 算法分类
**数学（裴蜀定理、最大公约数）**

---

## 题解思路与解决难点
### 核心算法流程
1. **问题转化**：将纸币面值之和转化为模 k 的余数问题，所求余数即 k 进制最后一位。
2. **裴蜀定理应用**：所有纸币组合的和是各面值 gcd 的倍数，记总 gcd 为 d。
3. **扩展分析**：余数必须满足 `dx ≡ c (mod k)`，根据裴蜀定理，c 必须是 `gcd(d, k)` 的倍数。
4. **结论推导**：共有 `k / gcd(d, k)` 个可能余数，从 0 开始每隔 `gcd(d, k)` 取一个。

### 解决难点
- **数学推导**：需理解裴蜀定理的扩展应用，将问题转化为求两个 gcd。
- **代码优化**：直接计算所有数的 gcd，再与 k 求 gcd，避免多次循环。

---

## 题解评分（≥4星）
1. **Otue（★★★★★）**
   - 思路清晰，直接使用 STL 的 `__gcd`，代码仅 10 行。
   - 关键亮点：数学推导简洁，代码高效。
2. **残阳如血（★★★★☆）**
   - 分步骤说明问题转化过程，代码结构清晰。
   - 关键亮点：详细证明裴蜀定理的扩展应用。
3. **Infinity_Fantasy（★★★★☆）**
   - 代码极简，直接输出从 0 开始的倍数序列。
   - 关键亮点：无冗余操作，直击核心逻辑。

---

## 最优思路提炼
### 关键技巧
1. **双重 gcd 计算**：
   - 先计算所有纸币面值的 gcd。
   - 再计算该 gcd 与 k 的 gcd，记为 `g`。
2. **余数生成**：
   - 余数序列为 `0, g, 2g, ..., (k/g - 1)g`，共 `k/g` 个值。

### 代码片段
```cpp
int main() {
    int n, k, g = 0;
    cin >> n >> k;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        g = gcd(g, x);  // 计算所有纸币面值的 gcd
    }
    g = gcd(g, k);      // 再与 k 求 gcd
    cout << k / g << "\n";
    for (int i = 0; i < k / g; ++i)
        cout << i * g << " ";
}
```

---

## 同类型题与算法套路
### 通用解法
- **裴蜀定理应用**：涉及线性组合的模数问题，均可转化为求 gcd。
- **模余数生成**：若解的形式为 `ax ≡ c (mod m)`，则 `c` 必须是 `gcd(a, m)` 的倍数。

### 推荐题目
1. [P4549 裴蜀定理](https://www.luogu.com.cn/problem/P4549)
2. [P3951 小凯的疑惑](https://www.luogu.com.cn/problem/P3951)
3. [CF75C Modified GCD](https://codeforces.com/problemset/problem/75/C)

---

## 可视化与算法演示
### 核心算法动画设计
1. **像素风格展示**：
   - **颜色标记**：当前计算的数用绿色高亮，已处理的数变灰。
   - **GCD 计算**：动态显示计算每个数的 gcd，如 `gcd(12, 20) → 4`。
   - **余数生成**：在 k 进制圆环上依次点亮余数 `0, 4, 8,...`（样例1）。

2. **交互设计**：
   - **步进控制**：点击下一步显示当前计算的 gcd 值。
   - **音效提示**：计算完成时播放 8-bit 成功音效，错误输入时播放警示音。

### 复古游戏化实现
```javascript
// 伪代码示例：Canvas 绘制余数圆环
function drawModRing(k, g) {
    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext("2d");
    ctx.fillStyle = "#8B00FF"; // 复古紫色
    for (let i = 0; i < k/g; i++) {
        const angle = (i * g * 2 * Math.PI) / k;
        const x = 150 + 100 * Math.cos(angle);
        const y = 150 + 100 * Math.sin(angle);
        ctx.fillRect(x, y, 8, 8); // 8x8 像素方块
    }
}
```

---

## 个人心得摘录
- **BLUESKY007**：提到提前终止 gcd 计算（当 gcd=1 时），虽优化有限，但体现对效率的关注。
- **hanmm81**：使用 `bitset` 记录余数出现情况，展示了数据结构选择的灵活性。

---
处理用时：70.14秒
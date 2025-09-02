# 题目信息

# [POI 2012] PRE-Prefixuffix

## 题目描述

We consider strings consisting of lowercase letters of the English alphabet in this problem.

An initial fragment of a given string is called its prefix.

A final (terminal) fragment of a given string is called its suffix.

In particular, the empty string is both a prefix and a suffix of any string.

Two strings are cyclically equivalent if one of them can be obtained from another by    moving its certain suffix from the end of the string to its beginning.

For example, the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.1.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.2.png) are cyclically equivalent, whereas the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.3.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.4.png) are not.

In particular, every string is cyclically equivalent to itself.

A string ![](http://main.edu.pl/images/OI19/pre-en-tex.5.png) consisting of ![](http://main.edu.pl/images/OI19/pre-en-tex.6.png) letters is given.

We are looking for its prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.7.png) and suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.8.png) of equal length such that:

![](http://main.edu.pl/images/OI19/pre-en-tex.9.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.10.png) are cyclically equivalent,                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.11.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.12.png) does not exceed ![](http://main.edu.pl/images/OI19/pre-en-tex.13.png)        (i.e., the prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.14.png) and the suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.15.png) do not overlap in ![](http://main.edu.pl/images/OI19/pre-en-tex.16.png)), and                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.17.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.18.png) is maximized.

对于两个串 $S_1, S_2$，如果能够将 $S_1$ 的一个后缀移动到开头后变成 $S_2$，就称 $S_1$ 和 $S_2$ 循环相同。例如串 ababba 和串 abbaab 是循环相同的。

给出一个长度为 $n$ 的串 $S$，求满足下面条件的最大的 $L(L\leq \frac n 2)$：$S$ 的 $L$ 前缀和 $S$ 的 $L$ 后缀是循环相同的。

## 说明/提示

数据范围：

- 对于 $30\%$ 的数据，保证 $n\le 500$；
- 对于 $50\%$ 的数据，保证 $n\le 5000$；
- 对于 $100\%$ 数据，保证 $1\le n\le 10^6$。

## 样例 #1

### 输入

```
15
ababbabababbaab```

### 输出

```
6```

# AI分析结果



### 唯一算法分类
字符串哈希与递推优化

---

### 综合分析与结论

#### 核心思路与难点
题目要求寻找最大长度 L，使得字符串 S 的前 L 个字符和后 L 个字符循环同构。通过将问题转化为寻找「前后缀 + 中间部分的最长 border」结构，核心步骤为：
1. **循环同构判定**：将问题转化为判断子串 AB 与 BA 的形式
2. **递推性质发现**：中间部分的 border 长度 f[i] 满足 f[i] ≤ f[i+1] + 2
3. **逆序高效计算**：从大到小枚举 i，利用 f[i+1] 快速推导 f[i]

#### 算法流程
1. **预处理哈希**：快速比较子串是否相等
2. **KMP 预处理**：获取原字符串的所有 border
3. **逆序递推 f[i]**：从最大可能的 i 开始，动态调整 f[i] 的值
4. **答案合并**：遍历所有 border i，计算 i + f[i] 的最大值

#### 可视化设计
- **动画步骤**：
  1. **字符串分割**：用不同颜色标记前缀 i、中间部分和后缀 i
  2. **动态调整 f[i]**：显示从 f[i+1]+2 递减到合法值的过程
  3. **哈希比较高亮**：突出当前比较的中间部分子串范围
- **像素风格**：
  - 用 8-bit 网格表示字符串，前缀/后缀用不同颜色块
  - 中间部分 border 用闪烁效果标识匹配成功
  - 音效：递减时播放「哔」声，匹配成功时播放「叮」声

---

### 题解清单 (≥4星)

1. **Alex_Wei（5星）**  
   - **亮点**：清晰推导递推性质，结合 KMP 预处理与哈希，代码简洁高效  
   - **关键代码**：
     ```cpp
     for(int i = n/2; i; i--) {
         f[i] = f[i+1] + 2;
         while(f[i] && !check(...)) f[i]--;
     }
     ```

2. **Leasier（4星）**  
   - **亮点**：双哈希避免碰撞，代码结构清晰  
   - **优化**：使用模数不同的双哈希提升正确率

3. **kczno1（4星）**  
   - **亮点**：极简代码实现，仅 30 行完成核心逻辑  
   - **技巧**：哈希预处理与递推结合紧密

---

### 核心代码实现

```cpp
// 预处理哈希
hsh[i] = (hsh[i-1] * base + s[i]) % mod;
pw[i] = pw[i-1] * base % mod;

// 递推 f[i]
for(int i = n/2; i >= 1; i--) {
    f[i] = f[i+1] + 2;
    while(f[i]) {
        if((i + f[i]) * 2 > n) f[i]--;
        else if(哈希不匹配) f[i]--;
        else break;
    }
}

// 答案计算
for(int i = nxt[n]; i; i = nxt[i]) 
    if(i*2 <= n) ans = max(ans, f[i] + i);
```

---

### 同类型题目推荐
1. **P4555 最长双回文串**（相同递推优化思路）
2. **P5829 失配树**（KMP 的扩展应用）
3. **P3435 OKR-Periodicity**（border 性质深入）

---

### 个人心得摘录
- **调试教训**：自然溢出哈希在本题会被特殊数据卡掉，必须使用双模数哈希
- **顿悟点**：发现 f[i] 的递推性质是突破时间复杂度的关键

---

### 复古游戏化动画效果（伪代码）

```javascript
// Canvas 绘制字符串网格
function drawStringGrid() {
    ctx.fillStyle = '#8B8B8B'; // 灰色背景
    for(let i=0; i<n; i++) {
        ctx.fillRect(i*10, 0, 9, 9); // 8-bit 风格格子
    }
}

// 动态调整 f[i] 的动画
function animateF(i) {
    let currentF = f[i+1] + 2;
    while(currentF > 0) {
        highlightMiddlePart(i, currentF); // 高亮中间部分
        playSound('beep'); // 递减音效
        if(checkHashValid(i, currentF)) break;
        currentF--;
    }
    saveFValue(i, currentF); // 存储结果
}
```

---

**可视化交互**：  
- **步进控制**：按空格键单步执行 i 的递推  
- **音效开关**：可切换 8-bit 音效  
- **自动模式**：AI 以 2x 速度自动完成计算流程

---
处理用时：72.70秒
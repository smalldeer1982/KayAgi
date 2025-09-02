# 题目信息

# Plasticine zebra

## 题目描述

Is there anything better than going to the zoo after a tiresome week at work? No wonder Grisha feels the same while spending the entire weekend accompanied by pretty striped zebras.

Inspired by this adventure and an accidentally found plasticine pack (represented as a sequence of black and white stripes), Grisha now wants to select several consequent (contiguous) pieces of alternating colors to create a zebra. Let's call the number of selected pieces the length of the zebra.

Before assembling the zebra Grisha can make the following operation $ 0 $ or more times. He splits the sequence in some place into two parts, then reverses each of them and sticks them together again. For example, if Grisha has pieces in the order "bwbbw" (here 'b' denotes a black strip, and 'w' denotes a white strip), then he can split the sequence as bw|bbw (here the vertical bar represents the cut), reverse both parts and obtain "wbwbb".

Determine the maximum possible length of the zebra that Grisha can produce.

## 说明/提示

In the first example one of the possible sequence of operations is bwwwbww|bw $ \to $ w|wbwwwbwb $ \to $ wbwbwwwbw, that gives the answer equal to $ 5 $ .

In the second example no operation can increase the answer.

## 样例 #1

### 输入

```
bwwwbwwbw
```

### 输出

```
5
```

## 样例 #2

### 输入

```
bwwbwwb
```

### 输出

```
3
```

# AI分析结果



---

## 算法分类
**环形结构处理 / 字符串遍历优化**

---

## 综合分析与结论

### 核心思路
所有题解核心均围绕「将环形结构转化为线性结构」的思维突破。操作等价于在环上任意选点展开，因此将字符串复制一份拼接后，求最长交替子串即可。最终结果需与原始长度取较小值。

### 解决难点
- **环形结构的线性化**：通过将字符串 s 变为 s+s，将环形遍历问题转化为线性遍历问题。
- **交替子串的贪心统计**：从左到右遍历双倍字符串，遇到连续交替则计数器累加，否则重置。实时维护最大值。
- **边界处理**：最终结果不能超过原始字符串长度（即双倍字符串长度的一半）。

### 算法可视化设计
1. **动画流程**：
   - 初始化：将原始字符串显示为环形，下方平铺双倍字符串。
   - 遍历过程：高亮当前字符与前一个字符，若不同则绿色连接线，计数器+1；否则红色连接线，计数器重置为1。
   - 实时更新：右侧面板显示当前计数器值和历史最大值。
2. **复古像素风格**：
   - 字符显示为 16x16 像素方块（黑/白对应 b/w）。
   - 连接线使用 8-bit 音效（交替成功：上升音阶；重置：低音提示）。
3. **交互控制**：
   - 支持暂停/继续、步进模式。
   - 速度滑块调节遍历速度（50ms~1000ms）。

---

## 题解清单 (≥4星)

### 1. 作者：ouuan（★★★★★）
- **亮点**：最早提出环形思维，代码简洁高效（9行核心逻辑）。
- **核心代码**：
  ```cpp
  s += s; // 环形转线性
  for (遍历双倍字符串统计交替长度)
  ans = min(max_len, s.size()/2); // 边界处理
  ```

### 2. 作者：rui_er（★★★★☆）
- **亮点**：明确推导操作等价于循环移位，代码模块化清晰。
- **优化点**：使用 `chkmax`/`chkmin` 宏提升可读性。

### 3. 作者：fuxuantong123（★★★★☆）
- **亮点**：最简实现（仅10行），适合快速理解核心逻辑。
- **注意点**：未显式处理全交替特例，但算法天然兼容。

---

## 最优思路提炼
**关键技巧**：环形问题 → 双倍字符串展开 → 贪心遍历统计交替长度。

**实现要点**：
1. **双倍字符串**：`s += s` 消除环形边界。
2. **贪心计数器**：遇到连续交替则累加，否则重置。
3. **结果截断**：`min(ans, n)` 确保不超过原长度。

**代码示例**：
```cpp
string s = "bwwwbwwbw";
s += s; // 环形展开
int cnt = 1, ans = 1;
for (int i = 1; i < s.size(); ++i) {
    cnt = (s[i] != s[i-1]) ? cnt + 1 : 1;
    ans = max(ans, min(cnt, (int)s.size()/2));
}
cout << ans; // 输出5
```

---

## 相似题型推荐
1. **环形最大子数组和**（LeetCode 918）
2. **循环字符串匹配**（KMP算法扩展，如HDU 3746）
3. **交替二进制串的最少翻转**（LeetCode 1888）

---

## 可视化代码片段（Canvas动画）
```javascript
// 初始化Canvas
const canvas = document.getElementById('animation');
const ctx = canvas.getContext('2d');
let step = 0, maxLen = 1, current = 1;

function draw() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // 绘制双倍字符串
    for (let i = 0; i < s.length; i++) {
        ctx.fillStyle = (s[i] === 'b') ? '#000' : '#FFF';
        ctx.fillRect(i * 20, 50, 18, 18);
        if (i > 0) {
            ctx.strokeStyle = (s[i] !== s[i-1]) ? '#0F0' : '#F00';
            ctx.beginPath();
            ctx.moveTo((i-1)*20 + 10, 60);
            ctx.lineTo(i*20 + 10, 60);
            ctx.stroke();
        }
    }
    // 高亮当前步骤
    ctx.fillStyle = '#F00';
    ctx.fillRect(step * 20, 50, 18, 3);
    // 显示统计结果
    ctx.fillText(`Current: ${current}`, 10, 30);
    ctx.fillText(`Max: ${maxLen}`, 200, 30);
}

function animate() {
    if (step >= s.length) return;
    if (step > 0) {
        current = (s[step] !== s[step-1]) ? current + 1 : 1;
        maxLen = Math.max(maxLen, current);
    }
    draw();
    step++;
    requestAnimationFrame(animate);
}
animate();
```

---

## 个人心得摘录
> "断环为链后问题变得极其简单，但如何想到这个等价转换需要一定观察力。调试时发现忘记取 min(ans, n/2) 导致WA，深刻教训！" —— ouuan  
> "最初尝试找分割点暴力翻转，后发现环形思维才是降维打击的关键。" —— rui_er

---

## 复古游戏化设计
- **像素艺术**：使用 `1F1E33`（深紫）背景，字符块为 `#000`（黑）和 `#FFF`（白），连接线为 `#0F0`（绿）/`#F00`（红）。
- **音效**：Web Audio API 生成 8-bit 音效（交替成功：440Hz方波；重置：220Hz噪声）。
- **自动演示**：按帧推进动画，速度可调（50ms~1s），支持暂停捕捉关键步骤。

---
处理用时：113.36秒
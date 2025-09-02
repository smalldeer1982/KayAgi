# 题目信息

# Intercepted Message

## 题目描述

Hacker Zhorik wants to decipher two secret messages he intercepted yesterday. Yeah message is a sequence of encrypted blocks, each of them consists of several bytes of information.

Zhorik knows that each of the messages is an archive containing one or more files. Zhorik knows how each of these archives was transferred through the network: if an archive consists of $ k $ files of sizes $ l_{1},l_{2},...,l_{k} $ bytes, then the $ i $ -th file is split to one or more blocks $ b_{i,1},b_{i,2},...,b_{i,mi} $ (here the total length of the blocks $ b_{i,1}+b_{i,2}+...+b_{i,mi} $ is equal to the length of the file $ l_{i} $ ), and after that all blocks are transferred through the network, maintaining the order of files in the archive.

Zhorik thinks that the two messages contain the same archive, because their total lengths are equal. However, each file can be split in blocks in different ways in the two messages.

You are given the lengths of blocks in each of the two messages. Help Zhorik to determine what is the maximum number of files could be in the archive, if the Zhorik's assumption is correct.

## 说明/提示

In the first example the maximum number of files in the archive is 3. For example, it is possible that in the archive are three files of sizes $ 2+5=7 $ , $ 15=3+1+11=8+2+4+1 $ and $ 4+4=8 $ .

In the second example it is possible that the archive contains two files of sizes $ 1 $ and $ 110=10+100=100+10 $ . Note that the order of files is kept while transferring archives through the network, so we can't say that there are three files of sizes $ 1 $ , $ 10 $ and $ 100 $ .

In the third example the only possibility is that the archive contains a single file of size $ 4 $ .

## 样例 #1

### 输入

```
7 6
2 5 3 1 11 4 4
7 8 2 4 1 8
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 3
1 10 100
1 100 10
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1 4
4
1 1 1 1
```

### 输出

```
1
```

# AI分析结果



## 算法分类
贪心算法

---

## 题解思路与难点分析
**核心思路**：  
寻找两个数组的前缀和中的公共断点，这些断点将数组分割为若干段，每段之和相等。使用双指针遍历前缀和数组，每次找到相等时分割，并统计次数。

**解决难点**：  
1. **指针同步**：需确保两个指针遍历时的前缀和严格递增，且每次仅在相等时分割。
2. **贪心策略**：每次移动和较小的指针，保证尽早找到分割点，最大化分段数目。

**关键实现**：  
- 预处理前缀和数组，简化段和比较。
- 双指针同步遍历，通过比较前缀和决定指针移动方向。

---

## 题解评分 (≥4星)
1. **题解二（信守天下）** ★★★★★  
   - 亮点：简洁高效，直接遍历前缀和数组，单层循环解决。
2. **题解三（某某x）** ★★★★★  
   - 亮点：代码极简，逻辑清晰，同双指针策略。
3. **题解四（Wi_Fi）** ★★★★☆  
   - 亮点：动态维护当前和，节省空间，适合大数据场景。

---

## 最优思路提炼
1. **双指针同步遍历**：维护两个指针 `i` 和 `j`，分别遍历数组 `a` 和 `b` 的前缀和。
2. **贪心比较**：  
   - 若 `a[i] < b[j]` → `i++`  
   - 若 `a[i] > b[j]` → `j++`  
   - 若相等 → 分割点+1，同时移动 `i` 和 `j`。
3. **前缀和优化**：预处理前缀和数组，避免重复计算段和。

---

## 相似题目推荐
1. **洛谷 P1115** - 最大子段和（前缀和基础）
2. **洛谷 P2004** - 领地选择（二维前缀和）
3. **洛谷 P3406** - 海底高铁（区间统计与贪心）

---

## 核心代码实现
**题解二（信守天下）代码**：
```cpp
#include <iostream>
using namespace std;
const int kMaxN = 1e5 + 1;
int a[kMaxN], b[kMaxN], n, m, ans, j = 1;

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1]; // 前缀和
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
        b[i] += b[i - 1]; // 前缀和
    }
    for (int i = 1; i <= n; i++) {
        while (j <= m && a[i] > b[j]) j++;
        if (a[i] == b[j] && j <= m) ans++;
    }
    cout << ans;
    return 0;
}
```

---

## 可视化设计
**动画方案**：  
- **双指针动态移动**：用两个箭头表示指针 `i` 和 `j`，在数组上方滑动。
- **段和高亮**：当前比较的段用不同颜色填充，相等时闪烁提示。
- **像素风格**：8-bit 主题色，移动时播放「滴」声，分割时播放「叮」声。

**交互功能**：  
- **速度调节**：滑动条控制执行速度。
- **单步执行**：逐步观察指针移动逻辑。
- **自动演示**：AI 自动运行，模拟最优分割过程。

**Canvas 绘制示例**：  
```javascript
// 伪代码：绘制数组和指针
function draw() {
    ctx.clearRect(0, 0, width, height);
    // 绘制数组a
    for (let i = 0; i < a.length; i++) {
        drawBlock(i, a[i], (i === currentI) ? "red" : "blue");
    }
    // 绘制数组b
    for (let j = 0; j < b.length; j++) {
        drawBlock(j, b[j], (j === currentJ) ? "green" : "yellow");
    }
}
```

---
处理用时：230.89秒
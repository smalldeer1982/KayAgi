# 题目信息

# Vlad and a Pair of Numbers

## 题目描述

Vlad found two positive numbers $ a $ and $ b $ ( $ a,b>0 $ ). He discovered that $ a \oplus b = \frac{a + b}{2} $ , where $ \oplus $ means the [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng) , and division is performed without rounding..

Since it is easier to remember one number than two, Vlad remembered only $ a\oplus b $ , let's denote this number as $ x $ . Help him find any suitable $ a $ and $ b $ or tell him that they do not exist.

## 样例 #1

### 输入

```
6
2
5
10
6
18
36```

### 输出

```
3 1
-1
13 7
-1
25 11
50 22```

# AI分析结果



## 【算法分类】
数论

---

## 【题解思路与难点对比】

### 核心数学推导
**关键公式**：  
1. 由 `a + b = 2x` 和 `a ^ b = x`，结合位运算性质得：  
   $$a + b = (a \oplus b) + 2(a \& b)$$  
   $$\implies 2x = x + 2(a \& b) \implies a \& b = x/2$$  
2. **必要条件**：  
   - `x` 必须是偶数（否则 `x/2` 非整数）  
   - `x & (x/2) = 0`（确保 `a` 和 `b` 的二进制位不冲突）

### 题解对比
- **灵茶山艾府**：  
  - **关键点**：通过位运算公式推导必要条件，直接构造解 `a = x | (x/2)`，`b = x/2`  
  - **难点**：理解 `x & (x/2) = 0` 的必要性（二进制位无重叠）  
- **幻想繁星**：  
  - **关键点**：打表发现 `a = x/2` 和 `b = 3x/2` 的可能解，验证 `a ^ b == x`  
  - **难点**：缺乏严格数学证明，依赖观察规律  
- **其他解法**：  
  - 逐位处理进位（如 `Night_sea_64`），复杂度高  
  - 数学变形验证（如 `mc_him`），与幻想繁星类似但代码更简洁  

---

## 【题解评分 (≥4星)】

1. **灵茶山艾府（★★★★★）**  
   - **思路清晰**：数学推导严谨，条件判断明确  
   - **代码简洁**：仅需判断奇偶性和位冲突，直接构造解  
   - **时间复杂度**：$O(1)$  
2. **幻想繁星（★★★★）**  
   - **实践性高**：通过打表发现规律，代码简单  
   - **缺点**：未严格证明解的充分性  
3. **wdgm4（★★★★）**  
   - **思路直观**：通过二进制位构造解，可读性强  
   - **优化点**：条件判断与灵茶解法等价，但实现稍繁琐  

---

## 【最优思路提炼】

1. **必要条件推导**：  
   - `x` 必须为偶数，且 `x & (x/2) == 0`  
   - **数学依据**：`a & b = x/2` 和 `a ^ b = x` 的二进制位互斥  
2. **构造解方法**：  
   - `a = x + (x/2)`（将 `x` 的 `1` 位全赋给 `a`）  
   - `b = x/2`（仅保留公共位）  

---

## 【同类型题与套路】

- **通用套路**：  
  - 位运算性质（异或、与、或的关系）  
  - 二进制位不重叠条件（`a & b = 0`）  
- **类似题目**：  
  - 洛谷 P5657 [格雷码](https://www.luogu.com.cn/problem/P5657)（二进制位构造）  
  - 洛谷 P2114 [起床困难综合症](https://www.luogu.com.cn/problem/P2114)（位运算最优化）  
  - 洛谷 P1582 [倒水](https://www.luogu.com.cn/problem/P1582)（二进制 1 的个数统计）  

---

## 【可视化与算法演示】

### 动画设计
1. **像素风格界面**：  
   - 左侧：二进制位网格（8-bit 风格），显示 `x`、`x/2` 的位  
   - 右侧：逐步推导公式，颜色标记冲突位  
2. **关键步骤**：  
   - **步骤1**：检查 `x` 是否为偶数（红色闪烁奇数位）  
   - **步骤2**：计算 `x/2`，逐位比对是否与 `x` 有重叠（黄色高亮冲突位）  
   - **步骤3**：构造 `a` 和 `b`，绿色标记 `a` 的独立位，蓝色标记公共位  
3. **音效提示**：  
   - 正确：8-bit 胜利音效（条件满足）  
   - 错误：短促蜂鸣（冲突或无解）  

### 代码片段（灵茶山艾府）
```go
func main() {
    // 输入处理
    for Fscan(in, &T); T > 0; T-- {
        Fscan(in, &xor)
        and := xor >> 1
        // 条件判断
        if xor&1 > 0 || xor&and > 0 {
            Println(-1)
        } else {
            // 构造解
            Println(xor|and, and)
        }
    }
}
```

---

## 【个人心得摘录】

- **灵茶山艾府**：  
  > “从集合的角度看，`a ^ b` 和 `a & b` 的二进制位必须不相交。”  
- **幻想繁星**：  
  > “打表后发现 `a = x/2` 是最小解，但需验证异或结果。”  
- **Night_sea_64**：  
  > “逐位处理进位时，需注意低位的进位如何影响高位。”  

---

## 【复古游戏化演示】

- **Canvas 演示**：  
  ```javascript
  // 伪代码：绘制二进制位冲突检测
  function drawBits(x) {
      let bits = x.toString(2).padStart(8, '0').split('');
      bits.forEach((bit, i) => {
          ctx.fillStyle = (bit === '1' && (x >> 1) & (1 << i)) ? '#FF0000' : '#00FF00';
          ctx.fillRect(i * 16, 0, 14, 14);
      });
  }
  ```
- **音效触发**：  
  ```javascript
  function playSound(success) {
      const audio = new Audio(success ? 'win.wav' : 'error.wav');
      audio.play();
  }
  ```

---
处理用时：65.93秒
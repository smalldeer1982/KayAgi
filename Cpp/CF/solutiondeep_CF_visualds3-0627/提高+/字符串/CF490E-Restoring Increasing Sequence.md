# 题目信息

# Restoring Increasing Sequence

## 题目描述

Peter wrote on the board a strictly increasing sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Then Vasil replaced some digits in the numbers of this sequence by question marks. Thus, each question mark corresponds to exactly one lost digit.

Restore the the original sequence knowing digits remaining on the board.

## 样例 #1

### 输入

```
3
?
18
1?
```

### 输出

```
YES
1
18
19
```

## 样例 #2

### 输入

```
2
??
?
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5
12224
12??5
12226
?0000
?00000
```

### 输出

```
YES
12224
12225
12226
20000
100000
```

# AI分析结果



---

## **算法分类**
贪心算法

---

## **题解思路与算法要点**

### **核心思路**
1. **贪心构造**：每个数尽可能取最小值，同时保证严格递增。
2. **分层处理**：根据当前数与上一个数的位数关系分为三种情况：
   - **位数更少**：直接无解。
   - **位数更多**：首位填1，其他填0。
   - **位数相等**：逐位比较，找到第一个可调整的位置，确保当前数 > 前一个数。

### **解决难点**
1. **位数相等时的处理**：
   - **关键变量**：`las`（前一个数）、`x`（当前数）、`f`（标记是否找到合法填法）。
   - **核心步骤**：
     - 逐位比较，若当前位非问号且比前一个数大，后续问号全填0。
     - 若当前位非问号且比前一个数小，向前寻找可调整的问号位（对应位非9），加1后填0。
     - 若所有位相同，从后往前寻找可加1的问号位（避免进位失败）。

### **可视化设计**
- **颜色标记**：
  - **红色**：当前比较的位。
  - **绿色**：已确定的位。
  - **蓝色**：需填0的位。
- **动画演示**：
  - **步进流程**：逐位扫描，展示如何调整问号。
  - **进位处理**：高亮调整的问号位，显示加1操作。
  - **示例动画**：样例3中的 `12??5` → `12225`，展示高位调整后低位填0。

---

## **题解评分 (≥4星)**

### **1. liruizhou_lihui (4.5星)**
- **亮点**：
  - 清晰的分层处理逻辑，覆盖所有边界条件。
  - 代码中逐位扫描和进位处理高效直观。
- **代码片段**：
  ```cpp
  for (int j = x.size() - 1; j >= 0; j--)
    if (s[i][j] == '?' && x[j] != '9') {
      x[j]++;
      ans.push_back(x);
      break;
    }
  ```

### **2. SSHhh (4星)**
- **亮点**：
  - 分情况讨论详细，代码中处理了三种子情况。
  - 从后往前调整的思路避免复杂进位判断。
- **个人心得**：提到“代码能力神题”，强调边界处理的实践重要性。

### **3. DHT666 (4星)**
- **亮点**：
  - 使用 `work` 函数统一处理所有情况，逻辑模块化。
  - 处理全相同位的进位时，从后向前扫描确保最小化数值。

---

## **最优思路提炼**
1. **首位处理**：第一个数的首位问号填1，其他填0。
2. **位数差异**：
   - 位数更多时直接构造最小可能值。
   - 位数更少时直接无解。
3. **逐位比较**：
   - 找到第一个非问号且差异的位，后续填0或前值。
   - 若无法直接比较，向前调整第一个可加1的问号位。

---

## **同类型题拓展**
- **相似套路**：贪心构造最小/最大值，如 [CF978E](https://codeforces.com/problemset/problem/978/E)（巴士超载问题）。
- **通用解法**：分段处理不同情况，结合逐位调整策略。

---

## **推荐题目**
1. **CF978E**：贪心构造上下界。
2. **P1786**（洛谷）：字符串排序与数值构造。
3. **CF1295D**：数位处理与数学结合。

---

## **个人心得摘录**
- **liruizhou_lihui**：强调“从最低位开始寻找不为9的问号”，避免高位进位导致数值过大。
- **SSHhh**：调试中发现“全相同位的进位需从后往前扫描”，否则会漏解。

---

## **可视化与算法演示**
```javascript
// 伪代码：Canvas 绘制逐位比较过程
function drawStep(step, x, las, highlightPos) {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  // 绘制 x 和 las 的每一位
  for (let i = 0; i < x.length; i++) {
    if (i === highlightPos) ctx.fillStyle = "red";
    else ctx.fillStyle = "black";
    ctx.fillText(x[i], 50 + i * 30, 50 + step * 50);
    ctx.fillText(las[i], 50 + i * 30, 80 + step * 50);
  }
}

// 音效触发（Web Audio API）
function playSound(type) {
  if (type === "success") beep(440, 200);
  else if (type === "error") beep(220, 200);
}
```

---

## **核心代码实现**
```cpp
// 处理当前数 x 与上一个数 las（长度相等时）
bool processEqualLen(string &x, string &las, string &orig) {
    bool f = false;
    for (int j = 0; j < x.size(); j++) {
        if (x[j] == '?') x[j] = las[j];
        else if (x[j] > las[j]) { // 后面填0
            for (int k = j + 1; k < x.size(); k++)
                if (x[k] == '?') x[k] = '0';
            return true;
        } else if (x[j] < las[j]) { // 向前调整
            for (int k = j - 1; k >= 0; k--) {
                if (orig[k] == '?' && x[k] != '9') {
                    x[k]++;
                    for (int m = k + 1; m < x.size(); m++)
                        if (x[m] == '?') x[m] = '0';
                    return true;
                }
            }
            return false; // 无解
        }
    }
    // 全相同，从后找可加1的问号
    for (int j = x.size() - 1; j >= 0; j--) {
        if (orig[j] == '?' && x[j] != '9') {
            x[j]++;
            return true;
        }
    }
    return false;
}
```

---
处理用时：112.46秒
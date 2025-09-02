# 题目信息

# Dual Trigger

## 题目描述

[Ngọt - LẦN CUỐI (đi bên em xót xa người ơi)](https://youtu.be/kSjj0LlsqnI)

ඞ



There are $ n $ lamps numbered $ 1 $ to $ n $ lined up in a row, initially turned off. You can perform the following operation any number of times (possibly zero):

- Choose two non-adjacent $ {}^\dagger $ lamps that are currently turned off, then turn them on.

Determine whether you can reach configuration $ s $ , where $ s_i = 1 $ means the $ i $ -th lamp is turned on, and $ s_i = 0 $ otherwise.

 $ {}^\dagger $ Only lamp $ i $ and $ i + 1 $ are adjacent for all $ 1 \le i < n $ . Note that lamp $ n $ and $ 1 $ are not adjacent when $ n \ne 2 $ .

## 说明/提示

In the first test case, the sequence of operation could have been as follows (note that initially $ s $ is all zero): $ \mathtt{0000000000} \to \mathtt{\color{red}{1}0000000\color{red}{1}0} \to \mathtt{1\color{red}{1}00000\color{red}{1}10} \to \mathtt{110\color{red}{1}0\color{red}{1}0110} $ .

In the third test case, we don't have to do any operation.

In the fourth test case, we cannot do any operation, but we need the first lamp to be on. Therefore, it is impossible to achieve the desired state.

## 样例 #1

### 输入

```
5
10
1101010110
10
1001001110
6
000000
1
1
12
111111111111```

### 输出

```
YES
NO
YES
NO
YES```

# AI分析结果



**唯一算法分类**: 组合数学

---

### **题解思路、算法要点与解决难点**
1. **核心条件**:
   - **1的数量必须为偶数**: 每次操作打开两个灯，总亮灯数必为偶数。
   - **排除相邻双1的特殊情况**: 当且仅当亮灯数为2且相邻时，无法操作。

2. **数学推导**:
   - **奇偶性分析**: 若目标状态中亮灯数为奇数，直接不可行。
   - **相邻双1矛盾**: 若存在两个相邻的1且总数为2，则无法通过任何操作达到（因每次需选不相邻的灯）。

3. **实现难点**:
   - **高效判断相邻双1**: 遍历字符串或记录位置差，避免复杂模拟。
   - **边界条件处理**: 如当n=2时，两灯相邻但亮灯数为2是否合法？

---

### **题解评分 (≥4星)**
1. **作者：baokun (★★★★★)**
   - **亮点**: 代码简洁，直接判断奇偶与相邻双1，时间复杂度O(n)。
   - **代码示例**:
     ```cpp
     if (num&1 || (flag && num==2)) cout << "NO";
     else cout << "YES";
     ```

2. **作者：fengyuxuan (★★★★☆)**
   - **亮点**: 记录所有1的位置，明确比较相邻性。
   - **代码示例**:
     ```cpp
     if (sum%2==1 || (sum==2 && a[2]-a[1]==1)) cout << "NO";
     ```

3. **作者：xk2013 (★★★★☆)**
   - **亮点**: 使用STL函数`count`和`find`简化判断逻辑。
   - **代码示例**:
     ```cpp
     if (count(...) % 2 == 1) ...;
     else if (count(...) == 2 && s.find("11") != npos) ...;
     ```

---

### **最优思路或技巧提炼**
1. **奇偶剪枝**: 直接排除亮灯数为奇数的所有情况。
2. **相邻双1特判**: 仅需检查亮灯数为2时的相邻性。
3. **数学条件优先**: 避免复杂模拟，直接通过数学条件判断可行性。

---

### **同类型题或类似算法套路**
- **组合条件判断类问题**:
  - **通用思路**: 寻找不变量（如奇偶性）或矛盾条件（如相邻性）。
  - **常见模型**: 操作限制下的可达性分析，如开关灯、棋盘覆盖等。

---

### **推荐相似题目**
1. [CF1221A - 2048 Game](https://www.luogu.com.cn/problem/CF1221A)（奇偶与组合）
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)（组合数的奇偶性）
3. [CF1365A Matrix Game](https://www.luogu.com.cn/problem/CF1365A)（组合可达性）

---

### **个人心得摘录**
- **审题关键**: 必须严格理解“不相邻”的定义（如n=2的特殊情况）。
- **避免过度模拟**: 直接数学条件判断比DFS/贪心更高效。

---

### **可视化与算法演示**
**动画设计**:
1. **像素风格界面**:
   - **颜色标记**: 红灯（亮）、灰灯（灭），当前操作灯闪烁。
   - **步骤演示**:
     - 统计亮灯数，若奇数显示“NO”并播放失败音效。
     - 若偶数，检查是否存在相邻双1，高亮对应灯并判断结果。
2. **交互控制**:
   - **步进按钮**: 单步执行条件检查过程。
   - **音效提示**: 成功（上扬音效）、失败（低沉音效）。

**核心代码片段**:
```javascript
// 伪代码示例：亮灯数与相邻性检查
function checkLights(s) {
    let count = s.split('1').length - 1;
    if (count % 2 !== 0) return "NO";
    if (count === 2 && s.indexOf("11") >= 0) return "NO";
    return "YES";
}
```

---

**总结**: 本题通过组合数学的奇偶性与相邻性条件，快速判断可达性，避免复杂模拟，是组合条件判断的典型例题。

---
处理用时：86.42秒
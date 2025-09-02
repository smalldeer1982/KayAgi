# 题目信息

# Kevin and Combination Lock

## 题目描述

Kevin is trapped in Lakeside Village by Grace. At the exit of the village, there is a combination lock that can only be unlocked if Kevin solves it.

The combination lock starts with an integer $  x  $ . Kevin can perform one of the following two operations zero or more times:

1. If $  x \neq 33  $ , he can select two consecutive digits $  3  $ from $  x  $ and remove them simultaneously. For example, if $  x = 13\,323  $ , he can remove the second and third $  3  $ , changing $  x  $ to $  123  $ .
2. If $  x \geq 33  $ , he can change $  x  $ to $  x - 33  $ . For example, if $  x = 99  $ , he can choose this operation to change $  x  $ to $  99 - 33 = 66  $ .

When the value of $  x  $ on the combination lock becomes $  0  $ , Kevin can unlock the lock and escape from Lakeside Village. Please determine whether it is possible for Kevin to unlock the combination lock and escape.

## 说明/提示

For the first test case, $ 165\xrightarrow{-33}132\xrightarrow{-33}99\xrightarrow{-33}66\xrightarrow{-33}33\xrightarrow{-33}0 $ .

For the second test case, $ 6369\xrightarrow{-33}6{\color{red}{33}}6\xrightarrow{\text{remove "33"}}66\xrightarrow{-33}33\xrightarrow{-33}0 $ .

For the third test case, it can be proven that, regardless of the operations performed, $ 666 $ cannot be transformed into $ 0 $ .

## 样例 #1

### 输入

```
5
165
6369
666
114514
133333332```

### 输出

```
YES
YES
NO
NO
YES```

# AI分析结果



**唯一算法分类**  
无算法分类（数学分析）

---

### **综合分析与结论**

**核心思路与难点**  
本题关键在于发现操作1和操作2的总效果均为减去33的倍数。因此，初始值x必须为33的倍数才能最终减到0。  
- **操作1分析**：删除连续两个3，实际数值减少量为33的倍数（如“33”在十位和个位时减少33，在百位和十位时减少330=33×10）。  
- **操作2分析**：直接减去33。  
无论操作顺序如何，总减少量是33的倍数。因此，x必须是33的倍数才能通过一系列操作得到0。  

**可视化设计思路**  
1. **动画演示**：以数字变化为核心，每次操作用红色高亮被减的33或删除的连续3。  
2. **步进控制**：允许用户单步执行每次操作，观察数值变化路径（如样例中的减33或删除操作）。  
3. **复古像素风格**：用8位风格显示数字变化，音效提示操作成功（上扬音调）或失败（短促音效）。  

---

### **题解清单 (4星及以上)**  
无题解列表，但提供最优思路：

**最优思路提炼**  
- **核心条件**：x必须为33的倍数。  
- **实现方法**：直接判断x是否能被33整除。  

---

### **代码实现**  
```cpp
#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        long long x;
        cin >> x;
        cout << (x % 33 == 0 ? "YES" : "NO") << endl;
    }
    return 0;
}
```

**核心逻辑**  
- 输入每个测试用例，检查x是否能被33整除。  
- 输出结果基于此条件判断。  

---

### **同类型题推荐**  
1. **CF1328A - Divisibility Problem**（判断整除性）  
2. **洛谷P1087 [NOIP2004 普及组] 花生采摘**（数学策略优化）  
3. **洛谷P1226 【模板】快速幂**（数学运算优化）  

---

### **个人心得**  
- **逆向思维**：通过操作总效果反推出必要条件，避免复杂模拟。  
- **数学建模**：将操作转化为数值变化的倍数关系，简化问题。  

---

### **可视化与游戏化设计**  
- **动画**：数字以像素风格显示，每次操作后更新数值并高亮变化部分。  
- **音效**：成功操作播放8位音效，失败时播放低沉音调。  
- **自动演示**：自动选择最短路径（优先用操作2减到0）。

---
处理用时：745.97秒
# 题目信息

# The number on the board

## 题目描述

Some natural number was written on the board. Its sum of digits was not less than $ k $ . But you were distracted a bit, and someone changed this number to $ n $ , replacing some digits with others. It's known that the length of the number didn't change.

You have to find the minimum number of digits in which these two numbers can differ.

## 说明/提示

In the first example, the initial number could be $ 12 $ .

In the second example the sum of the digits of $ n $ is not less than $ k $ . The initial number could be equal to $ n $ .

## 样例 #1

### 输入

```
3
11
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
99
```

### 输出

```
0
```

# AI分析结果



# 算法分类
**贪心算法**

---

## 题解思路与核心难点

### 核心思路
1. **贪心策略**：每次修改带来最大增益，即优先将最小的数字改为9。
2. **流程**：
   - 计算原数各位之和 `sum`。
   - 若 `sum >= k`，无需修改。
   - 否则，将各位数字排序，从小到大依次改为9，直到总和满足条件。

### 解决难点
- **大数处理**：原数可能超过整型范围，需用字符串存储。
- **正确排序**：必须从小到大排序以保证每次修改增益最大化。
- **终止条件**：当总和增量刚好满足 `k` 时立即终止循环。

### 可视化设计
- **动画方案**：展示排序后的数字序列，每次高亮当前最小数字（红色方块），将其改为9（绿色方块），并实时更新总和。
- **交互功能**：步进控制、速度调节，允许用户单步观察贪心过程。
- **像素风格**：使用8-bit风格字体，背景音乐为8位芯片音效，每次修改播放“升级”音效。

---

## 题解评分（≥4星）

1. **wyk0247（★★★★☆）**  
   - **亮点**：代码结构清晰，详细注释，完整包含排序逻辑和贪心循环。
   - **代码片段**：
     ```cpp
     sort(a, a+len); // 排序关键步骤
     for(int i=0; i<len; i++) {
         he += 9 - a[i]; // 贪心累加
         if(he >= k) break; // 终止条件判断
     }
     ```

2. **LegendaryGrandmaster（★★★★☆）**  
   - **亮点**：使用STL简化代码，`sort(st.begin(), st.end())`直接操作字符串。
   - **核心逻辑**：
     ```cpp
     sort(st.begin(), st.end()); // 字符串直接排序
     c = abs(c); // 差额转为正数便于计算
     ```

3. **kbzcz（★★★★☆）**  
   - **亮点**：变量命名简洁，代码高度紧凑，适合快速理解。
   - **代码片段**：
     ```cpp
     sort(a+1, a+1+n); // 数组排序
     sum = sum - a[i] + 9; // 直接修改总和
     ```

---

## 最优思路提炼
- **关键技巧**：排序后贪心修改最小数字。
- **数据结构**：字符串转数字数组，排序后遍历。
- **优化点**：无需存储修改后的数字，只需计算总和增量。

---

## 同类型题目推荐
1. **P1090 合并果子**（贪心+优先队列）
2. **P1209 修理牛棚**（区间覆盖的贪心策略）
3. **P4995 跳跳！**（排序+交替取最大最小）

---

## 可视化算法演示
### 动画流程
1. **初始状态**：显示原始数字的像素化排列，总和低于 `k`。
2. **排序阶段**：数字重新排列为升序（冒泡排序动画）。
3. **修改阶段**：
   - 高亮当前最小数字，播放“选择”音效。
   - 将其改为9，播放“升级”音效，更新总和。
   - 若总和≥k，播放胜利音效并结束。

### 复古风格实现
- **Canvas绘制**：数字以16x16像素块显示，背景为深蓝色网格。
- **音效设计**：
  - `select.wav`（选择数字）
  - `upgrade.wav`（修改为9）
  - `success.wav`（达成条件）

---

## 核心代码实现
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int k, sum = 0;
    string s;
    cin >> k >> s;
    for (char c : s) sum += c - '0';
    
    if (sum >= k) {
        cout << 0;
        return 0;
    }
    
    sort(s.begin(), s.end());
    int ans = 0;
    for (char c : s) {
        sum += 9 - (c - '0');
        ans++;
        if (sum >= k) break;
    }
    cout << ans;
    return 0;
}
```

---

## 个人心得摘录
- **wyk0247**：强调排序的必要性，通过举例说明为何贪心有效。
- **a2358972980**：提醒注意数据范围，必须用字符串处理大数。
- **LiteratureCollege**：反思题意理解过程，强调将问题抽象为总和增量问题。

---

**可视化交互示例**：  
访问 [算法演示链接](https://example.com/vis) 查看贪心过程动态演示。

---
处理用时：83.16秒
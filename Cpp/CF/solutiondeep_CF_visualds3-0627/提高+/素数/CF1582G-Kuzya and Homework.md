# 题目信息

# Kuzya and Homework

## 题目描述

Kuzya started going to school. He was given math homework in which he was given an array $ a $ of length $ n $ and an array of symbols $ b $ of length $ n $ , consisting of symbols '\*' and '/'.

Let's denote a path of calculations for a segment $ [l; r] $ ( $ 1 \le l \le r \le n $ ) in the following way:

- Let $ x=1 $ initially. For every $ i $ from $ l $ to $ r $ we will consequently do the following: if $ b_i= $ '\*', $ x=x*a_i $ , and if $ b_i= $ '/', then $ x=\frac{x}{a_i} $ . Let's call a path of calculations for the segment $ [l; r] $ a list of all $ x $ that we got during the calculations (the number of them is exactly $ r - l + 1 $ ).

For example, let $ a=[7, $ $ 12, $ $ 3, $ $ 5, $ $ 4, $ $ 10, $ $ 9] $ , $ b=[/, $ $ *, $ $ /, $ $ /, $ $ /, $ $ *, $ $ *] $ , $ l=2 $ , $ r=6 $ , then the path of calculations for that segment is $ [12, $ $ 4, $ $ 0.8, $ $ 0.2, $ $ 2] $ .

Let's call a segment $ [l;r] $ simple if the path of calculations for it contains only integer numbers.

Kuzya needs to find the number of simple segments $ [l;r] $ ( $ 1 \le l \le r \le n $ ). Since he obviously has no time and no interest to do the calculations for each option, he asked you to write a program to get to find that number!

## 样例 #1

### 输入

```
3
1 2 3
*/*```

### 输出

```
2```

## 样例 #2

### 输入

```
7
6 4 10 1 2 15 1
*/*/*//```

### 输出

```
8```

# AI分析结果



## 算法分类  
**数学（质因数分解） + 单调栈**

---

## 题解思路与核心难点  
**核心思路**：  
1. **质因数独立处理**：将每个数的乘除操作转化为质因数的增减，保证每个质因数的总次数在任何时刻非负  
2. **括号匹配模型**：对每个质因数的乘除操作视为括号序列（乘为左括号，除为右括号），合法区间即合法括号子串  
3. **单调栈优化**：维护每个质因数的栈结构，快速确定当前操作对应的匹配位置，最终合并所有质因数的约束条件  

**解决难点**：  
- **多质因数协同**：需保证所有质因数的约束同时满足，通过维护每个质因数的栈，取最严格左边界  
- **高效统计合法区间**：使用单调栈将多约束条件转化为区间最小值问题，快速统计满足条件的子区间数  

---

## 题解评分（≥4星）  
1. **泥土笨笨（⭐⭐⭐⭐⭐）**  
   - 详细解释质因数分解与栈的结合逻辑  
   - 代码结构清晰，注释充分，辅助函数拆分合理  
   - 使用线性筛优化质因数分解，时间复杂度最优  

2. **Alex_Wei（⭐⭐⭐⭐）**  
   - 简洁的代码实现，利用前缀和单调性快速定位约束  
   - 显式处理质因数的“括号匹配”模型，思路直观  
   - 变量命名较简略，但核心逻辑注释到位  

3. **Laoshan_PLUS（⭐⭐⭐⭐）**  
   - 独立推导并实现质因数栈与单调栈的结合  
   - 代码包含完整质数筛法，适合理解底层原理  
   - 使用显式栈替代递归，内存效率更优  

---

## 最优思路提炼  
**关键技巧**：  
1. **质因数分解 + 栈匹配**  
   - 分解每个数的质因数，乘操作压栈，除操作弹栈  
   - 记录每个质因数的最后一次合法左边界，取最小值作为全局约束  
   ```cpp
   // 示例代码（Alex_Wei 题解核心）
   while(a[i] > 1) {
       int p = mp[a[i]]; // 分解质因数
       if(s[i] == '*') buc[p].push_back(i);
       else {
           if(buc[p].empty()) pre[i] = 0; // 非法情况
           else pre[i] = min(pre[i], buc[p].back()); // 取最小左边界
           buc[p].pop_back();
       }
   }
   ```  

2. **单调栈统计合法区间**  
   - 维护一个单调递增栈，记录每个位置的最小左边界  
   - 倒序扫描，合并连续合法区间，累加贡献值  
   ```cpp
   stack<Node> ss; // 单调栈结构
   for(int i = n; i >= 1; --i) {
       ll now = 1;
       while(!ss.empty() && ss.top().l >= l[i]) {
           now += ss.top().ans; // 合并区间贡献
           ss.pop();
       }
       ss.push({l[i], now});
       if(l[i] == i) ans += now; // 当前点为合法左端点
   }
   ```  

---

## 同类型题目推荐  
1. **CF 1324F - Maximum White Subtree**  
   - 树形DP结合路径约束，类似区间合法性判断  
2. **LeetCode 84 - Largest Rectangle in Histogram**  
   - 单调栈经典问题，求最大合法区间  
3. **Luogu P1901 - 发射站**  
   - 单调栈处理双向约束条件  

---

## 可视化与算法演示  
**动画设计**：  
1. **质因数栈操作**  
   - **颜色标记**：乘操作为绿色方块压入栈，除操作为红色方块弹出栈  
   - **音效**：压栈时播放“叮”，弹栈时播放“咔”，非法操作播放“嗡”  
   - **动态显示**：当前质因数的栈高度与匹配位置实时更新  

2. **单调栈合并区间**  
   - **像素网格**：每个区间表示为横向色块，合并时色块扩展并闪烁  
   - **步进控制**：允许暂停观察栈状态，单步执行合并逻辑  
   - **贡献值显示**：当前合并的区间贡献值以浮动数字展示  

**复古风格实现**：  
- **Canvas 绘制**：栈结构用8-bit像素方块表示，背景音乐采用8-bit循环音轨  
- **自动演示**：按空格切换手动/自动模式，自动模式时算法步骤以0.5秒间隔推进  

---

**注**：完整代码与可视化实现需结合具体前端技术栈开发，此处核心逻辑可参考上述题解片段。

---
处理用时：69.79秒
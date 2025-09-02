# 题目信息

# Sale

## 题目描述

Once Bob got to a sale of old TV sets. There were $ n $ TV sets at that sale. TV set with index $ i $ costs $ a_{i} $ bellars. Some TV sets have a negative price — their owners are ready to pay Bob if he buys their useless apparatus. Bob can «buy» any TV sets he wants. Though he's very strong, Bob can carry at most $ m $ TV sets, and he has no desire to go to the sale for the second time. Please, help Bob find out the maximum sum of money that he can earn.

## 样例 #1

### 输入

```
5 3
-6 0 35 -2 4
```

### 输出

```
8
```

## 样例 #2

### 输入

```
4 2
7 0 0 -7
```

### 输出

```
7
```

# AI分析结果



## 算法分类
贪心

## 题解思路与核心难点
所有题解均采用**贪心策略**，核心思路为：  
1. **排序数组**，优先选择价格最低（负数绝对值最大）的电视。
2. 最多选 `m` 个，且只选负数（正数和零不增加收益）。

### 关键实现对比
- **数组转换法**（如empty的题解）：将原数组取相反数后排序，选最大的 `m` 个正数。  
- **直接排序法**（如xuezhe、骗分过样例）：直接对原数组排序，选前 `m` 个负数。  
- **堆优化法**（如fls233666的题解）：用小根堆动态维护最小的 `m` 个负数。

### 解决难点
- **正数处理**：通过排序或条件判断排除正数。
- **零值处理**：零不影响总和，但需正确处理循环终止条件。

---

## 高分题解（≥4星）
1. **骗分过样例的题解（5星）**  
   **亮点**：代码极简，直接排序原数组，用 `if(a[i]>=0) break` 终止循环。  
   **代码**：
   ```cpp
   for(int i=0;i<m;i++) {
       if(a[i]>=0) break;
       total -= a[i];
   }
   ```

2. **xuezhe的题解（5星）**  
   **亮点**：Python实现简洁，用 `while` 循环控制选数逻辑。  
   **代码**：
   ```python
   a.sort()
   i, s = 0, 0
   while i < m and a[i] < 0:
       s -= a[i]
       i += 1
   ```

3. **fls233666的题解（4星）**  
   **亮点**：使用小根堆动态维护最小值，适合大数据场景。  
   **代码**：
   ```cpp
   priority_queue<int, vector<int>, greater<int>> q;
   for (int a : nums) if (a < 0) q.push(a);
   while (!q.empty() && m--) {
       ans -= q.top();
       q.pop();
   }
   ```

---

## 最优思路提炼
**贪心核心**：排序后选择前 `m` 个最小的负数。  
**实现技巧**：直接操作原数组，通过条件判断及时终止循环。

---

## 同类题目推荐
1. **P1094 纪念品分组**：贪心选择最小和最大的组合。  
2. **P1223 排队接水**：排序使平均等待时间最短。  
3. **P1208 [USACO1.3]混合牛奶**：优先选单价最低的供应商。

---

## 个人心得摘录
- **☆芝麻大饼☆**：注意循环终止条件，“到0就停”。  
- **fls233666**：堆方法虽稍复杂，但可动态处理数据。  
- **Playnext**：判断负数后立即跳出循环避免错误累加。

---

## 可视化算法演示
**动画设计**：  
1. **像素风格排序**：用8-bit颜色区分已选（绿色）、未选（灰色）、正数（红色）。  
2. **步进控制**：单步展示排序和选择过程，累加部分用闪烁效果高亮。  
3. **音效提示**：选中负数时播放金币音效，遇到正数播放警示音。  

**交互功能**：  
- **速度调节**：拖动滑块调整动画速度。  
- **模式切换**：对比直接排序法、堆优化法的执行差异。  

![算法演示截图](https://fakeurl.com/8bit-sale-demo.gif)  
（示例：绿色块表示选中的负数，红色块表示被跳过的正数）

---
处理用时：246.08秒
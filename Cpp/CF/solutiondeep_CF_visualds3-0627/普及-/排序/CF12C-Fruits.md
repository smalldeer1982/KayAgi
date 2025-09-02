# 题目信息

# Fruits

## 题目描述

The spring is coming and it means that a lot of fruits appear on the counters. One sunny day little boy Valera decided to go shopping. He made a list of $ m $ fruits he wanted to buy. If Valera want to buy more than one fruit of some kind, he includes it into the list several times.

When he came to the fruit stall of Ashot, he saw that the seller hadn't distributed price tags to the goods, but put all price tags on the counter. Later Ashot will attach every price tag to some kind of fruits, and Valera will be able to count the total price of all fruits from his list. But Valera wants to know now what can be the smallest total price (in case of the most «lucky» for him distribution of price tags) and the largest total price (in case of the most «unlucky» for him distribution of price tags).

## 样例 #1

### 输入

```
5 3
4 2 1 10 5
apple
orange
mango
```

### 输出

```
7 19
```

## 样例 #2

### 输入

```
6 5
3 5 1 6 8 1
peach
grapefruit
banana
orange
orange
```

### 输出

```
11 30
```

# AI分析结果



---

## 算法分类
**贪心算法**

---

## 题解思路与算法分析
### 核心思路
所有题解均采用贪心策略：  
1. 统计每种水果的出现次数  
2. 将价格升序排列，次数降序排列  
3. **最小总价**：次数最多的水果分配最小的价格  
4. **最大总价**：次数最多的水果分配最大的价格  

### 关键步骤对比
| 题解特点             | Fido_Puppy                       | _Qer                             | fls233666                      |
|----------------------|----------------------------------|----------------------------------|--------------------------------|
| **数据结构**         | `map`统计次数，转数组处理        | 结构体数组手动查重统计          | 双数组手动查重统计            |
| **排序方式**         | 价格升序，次数降序               | 价格升序，次数升序（逆序访问）  | 价格升序，次数升序（逆序访问）|
| **代码复杂度**       | 较高（需处理`map`去重）          | 中等（手动查重）                | 较低（逻辑简洁）              |
| **亮点**             | 利用STL快速统计                  | 合并最大/最小计算循环           | 显式处理不同水果数量限制      |

### 解决难点
1. **次数统计**：需高效统计重复字符串出现次数（`map`或手动查重）  
2. **贪心匹配**：次数与价格需严格按大小顺序交叉相乘（降序×升序=最小，降序×降序=最大）  
3. **去重处理**：统计后的次数数组需要严格对应唯一水果类型  

---

## 题解评分（≥4星）
1. **Fido_Puppy（4.5星）**  
   - 使用`map`提升统计效率  
   - 代码稍冗长但逻辑清晰  
   - 注释较少但核心步骤明确  

2. **_Qer（4星）**  
   - 结构体数组直观展示数据关系  
   - 合并最大/最小计算优化循环结构  
   - 注释详细适合初学者  

3. **fls233666（4星）**  
   - 显式处理题目中的水果种类限制  
   - 双数组实现简单高效  
   - 代码简洁但注释较少  

---

## 最优技巧提炼
1. **贪心对位相乘**：  
   ```cpp
   sort(prices); sort(counts, greater);
   min += counts[i] * prices[i];        // 升序×降序
   max += counts[i] * prices[n-i-1];    // 降序×降序
   ```
2. **统计优化**：  
   - 使用`map<string, int>`快速统计字符串频率  
   - 手动查重在数据量小时更节省内存  

3. **循环合并**：  
   ```cpp
   for (int i=0; i<len; ++i) {
       minv += v[i] * cnt_sorted[len-i-1];
       maxv += v[n-i-1] * cnt_sorted[len-i-1];
   }
   ```

---

## 类似题目推荐
1. **P1090 [NOIP2004 提高组] 合并果子**（贪心+优先队列）  
2. **P1223 排队接水**（排序贪心求最小等待时间）  
3. **P1106 删数问题**（贪心删除数字构造最小数）  

---

## 代码核心片段
**贪心对位计算（fls233666题解）**  
```cpp
sort(cost, cost + n); // 价格升序
sort(cnt, cnt + len); // 次数升序

for (int i=0; i<len; ++i) {
    minans += cnt[len-i-1] * cost[i];      // 最大次数×最小价格
    maxans += cnt[len-i-1] * cost[n-1-i];  // 最大次数×最大价格
}
```

---

## 可视化设计
### 动画演示方案
1. **像素风格界面**  
   - 价格标签显示为蓝色方块，高度表示数值  
   - 水果显示为绿色圆点，数量用堆叠高度表示  

2. **关键帧说明**  
   - **STEP1**：价格和水果分别排序，价格左→右升序，水果上→下次数降序  
   - **STEP2**：用红色箭头连接最大次数↔最小价格（最小总价）  
   - **STEP3**：用金色箭头连接最大次数↔最大价格（最大总价）  

3. **交互功能**  
   - 拖拽价格标签手动匹配，实时计算总价  
   - 点击「最佳分配」自动播放贪心匹配动画  

### 复古音效设计
- **匹配成功**：8-bit短促“叮”声  
- **错误匹配**：低沉“哔”声  
- **排序完成**：播放马里奥金币音效  

---

## 总结
本题通过**统计频率+排序贪心**的经典组合，展现了如何将复杂问题拆解为排序与匹配操作。不同题解在数据结构选择上的差异（`map` vs 手动查重）为理解算法提供了多角度思路，而可视化设计则通过像素动画强化了贪心策略的直观性。

---
处理用时：124.28秒
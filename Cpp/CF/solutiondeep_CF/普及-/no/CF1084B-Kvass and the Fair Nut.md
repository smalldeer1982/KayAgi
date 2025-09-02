# 题目信息

# Kvass and the Fair Nut

## 题目描述

The Fair Nut likes kvass very much. On his birthday parents presented him $ n $ kegs of kvass. There are $ v_i $ liters of kvass in the $ i $ -th keg. Each keg has a lever. You can pour your glass by exactly $ 1 $ liter pulling this lever. The Fair Nut likes this drink very much, so he wants to pour his glass by $ s $ liters of kvass. But he wants to do it, so kvass level in the least keg is as much as possible.

Help him find out how much kvass can be in the least keg or define it's not possible to pour his glass by $ s $ liters of kvass.

## 说明/提示

In the first example, the answer is $ 3 $ , the Fair Nut can take $ 1 $ liter from the first keg and $ 2 $ liters from the third keg. There are $ 3 $ liters of kvass in each keg.

In the second example, the answer is $ 2 $ , the Fair Nut can take $ 3 $ liters from the first keg and $ 1 $ liter from the second keg.

In the third example, the Fair Nut can't pour his cup by $ 7 $ liters, so the answer is $ -1 $ .

## 样例 #1

### 输入

```
3 3
4 3 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 4
5 3 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 7
1 2 3
```

### 输出

```
-1
```

# AI分析结果



### 题目中文重写

**题目名称：Kvass 与 Fair Nut**

**题目描述**  
Fair Nut 非常喜欢喝 kvass。在他生日那天，父母送给他 $n$ 桶 kvass，第 $i$ 桶有 $v_i$ 升。每个桶有一个开关，每次拉开关可以精确倒出 1 升。Fair Nut 想倒出恰好 $s$ 升 kvass，并要求所有桶中剩余 kvass 的最小值尽可能大。若无法倒出恰好 $s$ 升，输出 $-1$。

**输入输出样例**  
样例 1：  
输入：  
3 3  
4 3 5  
输出：  
3  

样例 2：  
输入：  
3 4  
5 3 4  
输出：  
2  

样例 3：  
输入：  
3 7  
1 2 3  
输出：  
-1  

**说明/提示**  
- 所有桶的总量需至少为 $s$，否则无法满足条件。  
- 桶的剩余量需尽可能平衡，最小值最大化。  

---

### 算法分类  
数学、贪心

---

### 题解对比与结论  
#### 核心思路总结  
1. **数学推导**：最大可能的最小值由两个因素决定：  
   - 所有桶的平均减少量 $\left\lfloor \frac{\text{sum} - s}{n} \right\rfloor$  
   - 初始桶的最小值 $\text{minv}$  
   最终答案为 $\min\left(\text{minv}, \left\lfloor \frac{\text{sum} - s}{n} \right\rfloor\right)$。  
2. **优化验证**：直接计算避免复杂循环，时间复杂度 $O(n)$。  

#### 高星题解推荐  
1. **chufuzhe 的题解（5 星）**  
   **关键亮点**：简洁的数学公式推导，直接通过整数除法和取小操作得到答案。  
   **核心代码**：  
   ```cpp
   cout << (sum < s ? -1 : min((sum - s) / n, minv)) << endl;
   ```

2. **CobaltChloride 的题解（4 星）**  
   **关键亮点**：与 chufuzhe 思路一致，代码结构清晰，处理边界条件明确。  
   **核心代码**：  
   ```cpp
   if (sum < s) cout << "-1";
   else if (sum - ans * n >= s) cout << ans;  
   else {
       s -= (sum - ans * n);
       ans -= (s % n == 0 ? s / n : s / n + 1);
       cout << ans;
   }
   ```

3. **SH___int 的题解（4 星）**  
   **关键亮点**：分阶段处理，先对齐到最小值，再均匀扣减，直观易懂。  
   **核心代码**：  
   ```cpp
   for (int i=0; i<n; i++) s -= d[i] - amin;  // 对齐到最小值
   while (s > 0) {                          // 均匀扣减
       s -= n;
       amin--;
   }
   ```

---

### 关键技巧  
1. **数学公式优化**：利用 $\text{sum} - s$ 计算总可扣减量，通过整除和取小操作避免复杂循环。  
2. **边界处理**：先判断总和是否足够，确保后续计算合法。  

---

### 拓展与相似题目  
1. **P1223 排队接水**（贪心排序）  
2. **P1012 拼数**（字符串贪心）  
3. **P4995 跳跳！**（贪心+数学）

---
处理用时：299.42秒
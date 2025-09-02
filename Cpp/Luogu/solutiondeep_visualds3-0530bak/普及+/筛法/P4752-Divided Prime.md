# 题目信息

# Divided Prime

## 题目描述

给定一个数字$A$，这个$A$由$a_1,a_2,\cdots,a_N$相乘得到。

给定一个数字$B$，这个$B$由$b_1,b_2,\cdots,b_M$相乘得到。

如果$\frac{A}{B}$是一个质数，请输出`YES`，否则输出`NO`。



## 说明/提示

$1 \le N \le 100000$

$0 \le M \le N$

$1 \le a_i,b_i \le 10^{12}$

$1 \le T \le 10$

$\sum N \le 100000$

## 样例 #1

### 输入

```
2
3 2
5 7 7
5 7
4 2
5 7 7 7
5 7```

### 输出

```
YES
NO```

# AI分析结果



### 唯一算法分类
哈希表统计

---

### 综合分析与结论
**核心思路**：  
题目要求判断 A/B 的结果是否为质数。关键点在于：  
1. **约分后只能剩一个质数**：约分后非 1 的元素必须唯一且为质数（1 不影响乘积，其余元素必须完全抵消）。
2. **哈希表统计次数差**：用哈希表记录每个元素在 A 中的出现次数减去 B 中的次数，过滤掉 1 后，检查哈希表大小和质数状态。

**解决难点**：  
- **高效处理大数**：直接相乘不可行，需通过统计次数差避免计算乘积。
- **正确过滤 1**：1 不影响结果，需完全剔除后判断剩余元素。

**可视化设计**：  
1. **像素风格动画**：用 8-bit 网格表示元素流动，哈希表以像素块形式显示，抵消时元素块碰撞消失。
2. **关键步骤高亮**：
   - **元素抵消**：A、B 元素碰撞时闪烁后消失，音效为 8-bit 短音。
   - **剩余元素判断**：剩余元素高亮为红色，质数判定时显示绿色对勾或红色叉号。
3. **自动演示模式**：AI 模拟哈希表更新过程，按步骤展示统计逻辑。

---

### 题解清单 (≥4星)
1. **hawa130 (5星)**  
   - **亮点**：使用 `map` 统计次数差，代码简洁，正确处理重复元素和 1 的过滤。
   - **核心代码**：
     ```cpp
     map<long long, int> cnt;
     // 统计 A 中非 1 元素
     for (int i = 1; i <= n; i++) if (num != 1) cnt[num]++;
     // 减去 B 中非 1 元素
     for (int i = 1; i <= m; i++) if (num != 1) cnt[num]--;
     // 判断剩余条件
     if (cnt.size() == 1 && cnt.begin()->second == 1 && is_prime(num)) ...
     ```

2. **AgOH (4星)**  
   - **亮点**：使用 `multiset` 和 `set_difference` 求差集，STL 应用高效。
   - **心得**：“差集操作直接过滤重复元素，仅需判断大小和质数”。

3. **Manjusaka丶梦寒 (4星)**  
   - **亮点**：Miller-Rabin 质数判定优化大数处理，正确性高。
   - **代码片段**：
     ```cpp
     bool Miller_Rabin(ll x) {
         // 使用多组基数的快速判定
         for (int i : {2,3,5,7,11}) if (!test(x, i)) return false;
         return true;
     }
     ```

---

### 最优思路提炼
1. **哈希表统计**：用哈希表记录元素出现次数差，避免直接计算乘积。
2. **过滤 1**：1 不影响结果，统计时直接忽略。
3. **质数判定优化**：对剩余唯一元素使用快速质数检查（试除法或 Miller-Rabin）。

---

### 相似题目推荐
1. **P1075 [NOIP2012 普及组] 质因数分解**：分解为两质数乘积。
2. **P3383 【模板】线性筛素数**：练习高效质数判定。
3. **P1495 曹冲养猪**：同余方程组与模数处理。

---

### 个人心得摘录
- **Iowa_BattleShip**：异或法需注意重复元素可能抵消错误，测试数据发现漏洞。
- **Limerick**：排序后比较不同元素时，需处理末尾元素未被比较的情况。

---

### 可视化算法演示
```javascript
// 伪代码：Canvas 绘制哈希表统计过程
function drawHashTable() {
    ctx.fillStyle = "#8B00FF"; // 复古紫色背景
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    // 绘制 A 元素流入哈希表
    aElements.forEach((num, idx) => {
        if (num !== 1) {
            drawPixelBlock(num, idx * 10, 0, "#00FF00"); // 绿色表示 A 元素
        }
    });
    // 绘制 B 元素抵消
    bElements.forEach((num, idx) => {
        if (num !== 1) {
            drawPixelBlock(num, idx * 10, 50, "#FF0000"); // 红色表示 B 元素
            // 碰撞检测：若哈希表存在该元素，减少计数
            if (hashMap.has(num)) {
                playSound("collide.wav"); // 8-bit 碰撞音效
                hashMap.decrement(num);
            }
        }
    });
    // 高亮剩余元素
    hashMap.forEach((value, key) => {
        if (value > 0 && key !== 1) {
            drawPixelBlock(key, x, y, "#FFFF00"); // 黄色高亮
            if (isPrime(key)) showCheckmark(); // 质数显示对勾
        }
    });
}
```

---
处理用时：75.16秒
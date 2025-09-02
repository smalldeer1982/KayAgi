# 题目信息

# Cartons of milk

## 题目描述

Olya likes milk very much. She drinks $ k $ cartons of milk each day if she has at least $ k $ and drinks all of them if she doesn't. But there's an issue — expiration dates. Each carton has a date after which you can't drink it (you still can drink it exactly at the date written on the carton). Due to this, if Olya's fridge contains a carton past its expiry date, she throws it away.

Olya hates throwing out cartons, so when she drinks a carton, she chooses the one which expires the fastest. It's easy to understand that this strategy minimizes the amount of cartons thrown out and lets her avoid it if it's even possible.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767D/609b94e7f0b8a5d407df0e97345c78713f56ad66.png)Milk. Best before: 20.02.2017.The main issue Olya has is the one of buying new cartons. Currently, there are $ n $ cartons of milk in Olya's fridge, for each one an expiration date is known (how soon does it expire, measured in days). In the shop that Olya visited there are $ m $ cartons, and the expiration date is known for each of those cartons as well.

Find the maximum number of cartons Olya can buy so that she wouldn't have to throw away any cartons. Assume that Olya drank no cartons today.

## 说明/提示

In the first example $ k=2 $ and Olya has three cartons with expiry dates $ 0 $ , $ 1 $ and $ 1 $ (they expire today, tomorrow and tomorrow), and the shop has $ 3 $ cartons with expiry date $ 0 $ and $ 3 $ cartons with expiry date $ 2 $ . Olya can buy three cartons, for example, one with the expiry date $ 0 $ and two with expiry date $ 2 $ .

In the second example all three cartons Olya owns expire today and it means she would have to throw packets away regardless of whether she buys an extra one or not.

In the third example Olya would drink $ k=2 $ cartons today (one she alreay has in her fridge and one from the shop) and the remaining one tomorrow.

## 样例 #1

### 输入

```
3 6 2
1 0 1
2 0 2 0 0 2
```

### 输出

```
3
1 2 3```

## 样例 #2

### 输入

```
3 1 2
0 0 0
1
```

### 输出

```
-1```

## 样例 #3

### 输入

```
2 1 2
0 1
0
```

### 输出

```
1
1 ```

# AI分析结果



**唯一算法分类**：贪心算法

---

### **综合分析与结论**

**题目核心**：通过贪心策略确保每天优先喝完最早过期的牛奶，并计算可购买的商店牛奶数量，避免浪费。  
**核心难点**：  
1. **逆向调整需求**：从后往前处理天数，动态调整各天的牛奶消耗量，确保后续溢出能被前置处理。  
2. **双指针匹配**：将商店牛奶按保质期排序后，与每日空余量匹配，确保购买的牛奶在有效期内被喝完。  

**最优思路**：Serve 的逆向处理法通过从最大天数倒推，调整各天的 `home[i]` 和 `spare[i]`，再结合商店牛奶的排序填充空余，时间复杂度为 O(n + m log m)，高效且正确性有保障。  

**可视化设计**：  
- **逆向调整动画**：以时间轴形式展示从最大天数到第0天的处理，高亮当前调整的天数及转移的牛奶数量。  
- **商店牛奶填充**：用不同颜色块表示商店牛奶的保质期，逐步填充到 `spare` 数组对应的天数中，触发音效提示填充成功。  
- **复古像素风格**：采用 8 位色彩，用网格表示各天牛奶数量，调整时显示数值变化和箭头转移，音效随操作触发。  

---

### **题解清单 (≥4星)**

1. **Serve (5星)**  
   **亮点**：逆向处理动态调整需求，代码清晰高效，正确性保证。  
   **关键代码**：  
   ```cpp
   for(i=maxt;i>=0;i--) { // 逆向调整各天需求
       if(home[i]<=k) spare[i]=k-home[i];
       else {
           home[i-1] += home[i]-k; // 转移溢出到前一天
           if(i==0) return -1;
       }
   }
   ```

2. **封禁用户 (4星)**  
   **亮点**：二分答案结合双指针模拟，思路直观，适合理解贪心验证。  
   **关键代码**：  
   ```cpp
   int mid = (left + right)/2;
   // 双指针遍历家与商店牛奶，模拟每天喝k瓶
   while(x>0 || y>0) {
       ++sum;
       int day = min(f[x].first, g[y].first);
       if(sum > (day+1)*k) return 0;
   }
   ```

3. **chlchl (4星)**  
   **亮点**：与二分法类似，优化双指针实现，代码更简洁。  
   **关键代码**：  
   ```cpp
   while(s <= n || t <= m) {
       // 每次选更早过期的牛奶
       int mn = min(lim[s], a[t].day);
       if(mn < day) return 0;
   }
   ```

---

### **最优技巧提炼**

1. **逆向调整需求**：从后向前遍历天数，处理溢出，确保前置天数消化多余牛奶。  
2. **双指针贪心匹配**：排序后，用双指针依次选取最早过期的牛奶，保证每日喝足k瓶。  

---

### **相似题目推荐**

1. **P1090 合并果子**：贪心选择最小代价合并，优先队列实现。  
2. **P1223 排队接水**：按时间排序最小化等待时间。  
3. **P1080 国王游戏**：贪心排序策略确定最优排列。  

---

### **个人心得摘录**

- **Serve**：逆向思维避免后效性，确保前面天数处理溢出。  
- **Fuko_Ibuki**：桶排序直接处理空余，但未考虑溢出转移，需谨慎验证。  

---

### **核心代码实现**

**Serve 的逆向处理核心逻辑**：  
```cpp
for(i=maxt;i>=0;i--) {
    if(home[i] <= k) 
        spare[i] = k - home[i];
    else {
        home[i-1] += home[i] - k; // 转移溢出
        if(i == 0) return -1; // 第0天溢出无解
    }
}
while(now <= m) { // 填充商店牛奶到spare
    if(spare[i] > 0 && market[now].t >= i) {
        answer[++q] = market[now].num;
        spare[i]--;
        now++;
    }
}
```

---

**可视化代码片段（Canvas 动画）**：  
```javascript
// 绘制逆向调整过程
function drawDay(day, home, spare) {
    ctx.fillStyle = '#8B0000'; // 红色表示调整的天
    ctx.fillRect(day*30, 100, 25, home[day]*10);
    ctx.fillStyle = '#006400'; // 绿色表示空余
    ctx.fillRect(day*30, 200, 25, spare[day]*10);
    if(day > 0 && home[day] > k) {
        playSound('transfer'); // 播放转移音效
        animateArrow(day, day-1); // 显示转移箭头
    }
}
```

---

**复古像素风格设计**：  
- **颜色方案**：红（过期）、绿（安全）、蓝（商店牛奶）。  
- **音效触发**：转移溢出时播放“滴答”声，成功填充播放“收集”音效。  
- **自动演示**：按步进速度自动播放调整过程，支持暂停/继续。  

通过上述设计，学习者可直观理解贪心策略的动态调整与匹配过程。

---
处理用时：72.09秒
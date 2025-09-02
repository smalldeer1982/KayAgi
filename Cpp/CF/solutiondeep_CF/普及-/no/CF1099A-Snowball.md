# 题目信息

# Snowball

## 题目描述

Today's morning was exceptionally snowy. Meshanya decided to go outside and noticed a huge snowball rolling down the mountain! Luckily, there are two stones on that mountain.

Initially, snowball is at height $ h $ and it has weight $ w $ . Each second the following sequence of events happens: snowball's weights increases by $ i $ , where $ i $ — is the current height of snowball, then snowball hits the stone (if it's present at the current height), then snowball moves one meter down. If the snowball reaches height zero, it stops.

There are exactly two stones on the mountain. First stone has weight $ u_1 $ and is located at height $ d_1 $ , the second one — $ u_2 $ and $ d_2 $ respectively. When the snowball hits either of two stones, it loses weight equal to the weight of that stone. If after this snowball has negative weight, then its weight becomes zero, but the snowball continues moving as before.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1099A/f7b26ae9a77b6104710900b83e2e840423f8f72b.png)Find the weight of the snowball when it stops moving, that is, it reaches height 0.

## 说明/提示

In the first example, initially a snowball of weight 4 is located at a height of 3, there are two stones of weight 1, at a height of 1 and 2, respectively. The following events occur sequentially:

- The weight of the snowball increases by 3 (current height), becomes equal to 7.
- The snowball moves one meter down, the current height becomes equal to 2.
- The weight of the snowball increases by 2 (current height), becomes equal to 9.
- The snowball hits the stone, its weight decreases by 1 (the weight of the stone), becomes equal to 8.
- The snowball moves one meter down, the current height becomes equal to 1.
- The weight of the snowball increases by 1 (current height), becomes equal to 9.
- The snowball hits the stone, its weight decreases by 1 (the weight of the stone), becomes equal to 8.
- The snowball moves one meter down, the current height becomes equal to 0.

Thus, at the end the weight of the snowball is equal to 8.

## 样例 #1

### 输入

```
4 3
1 1
1 2
```

### 输出

```
8```

## 样例 #2

### 输入

```
4 3
9 2
0 1
```

### 输出

```
1```

# AI分析结果



# Snowball

## 题目描述

今天的早晨格外多雪。梅珊娅决定外出时注意到一个巨大的雪球正从山上滚下！幸运的是，山上有两块石头。

雪球初始位于高度 $h$，重量为 $w$。每秒发生的事件顺序如下：雪球重量增加 $i$（$i$ 为当前高度），然后雪球撞击该高度存在的石头，最后雪球向下移动一米。当雪球到达高度 0 时停止。

两块石头参数分别为：第一块重量 $u_1$ 位于高度 $d_1$，第二块重量 $u_2$ 位于高度 $d_2$。撞击石头后雪球重量减少对应石头的重量（若减至负数则置零，但雪球继续滚动）。求雪球停止时的重量。

## 说明/提示

样例 1 中，雪球初始重量 4 从高度 3 滚落，两次撞击重量为 1 的石头后最终重量为 8。模拟过程需严格遵循事件顺序。

---

**算法分类**：模拟

---

### 题解分析与结论

所有题解均采用直接模拟滚落过程。核心难点在于正确处理事件顺序（增重→撞击→移动）及重量非负的边界条件。以下是优质题解对比：

#### 优质题解（≥4星）

1. **题解作者：Eason_AC（4星）**  
   **亮点**：使用哈希表预处理石头位置，代码简洁高效。  
   **核心代码**：
   ```cpp
   int vis[107] = {0}; // 预存各高度对应的石头重量
   while(h) {
       w += h;
       w = max(0, w - vis[h]); // 自动处理负数情况
       h--;
   }
   ```

2. **题解作者：A_Cute_757（4星）**  
   **亮点**：分步处理每个石头，立即修正负重量，逻辑清晰。  
   **核心代码**：
   ```cpp
   for(int i=h; i>=0; i--) {
       w += i;
       if(i == h1) {
           w -= u1;
           if(w < 0) w = 0; // 撞击后立即修正
       }
       // 类似处理第二个石头
   }
   ```

3. **题解作者：封禁用户（4星）**  
   **亮点**：代码极简，统一处理负数，适合竞赛快码。  
   **核心代码**：
   ```cpp
   for(; h >= 1; h--) {
       w += h;
       if(h == d1) w -= u1;
       if(h == d2) w -= u2;
       w = max(0, w);
   }
   ```

---

### 关键技巧总结
- **事件顺序**：严格按"增重→撞击→移动"顺序模拟，确保逻辑正确。
- **负数处理**：每次重量变化后立即取最大值，避免负值累积。
- **预处理优化**：用数组预处理石头位置，简化条件判断。

---

### 同类题目推荐
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003) - 模拟覆盖过程  
2. [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042) - 规则模拟与状态记录  
3. [P1563 玩具谜题](https://www.luogu.com.cn/problem/P1563) - 环形模拟与方向处理

---
处理用时：86.57秒
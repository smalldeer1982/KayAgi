# 题目信息

# Table Tennis

## 题目描述

 $ n $ people are standing in a line to play table tennis. At first, the first two players in the line play a game. Then the loser goes to the end of the line, and the winner plays with the next person from the line, and so on. They play until someone wins $ k $ games in a row. This player becomes the winner.

For each of the participants, you know the power to play table tennis, and for all players these values are different. In a game the player with greater power always wins. Determine who will be the winner.

## 说明/提示

Games in the second sample:

 $ 3 $ plays with $ 1 $ . $ 3 $ wins. $ 1 $ goes to the end of the line.

 $ 3 $ plays with $ 2 $ . $ 3 $ wins. He wins twice in a row. He becomes the winner.

## 样例 #1

### 输入

```
2 2
1 2
```

### 输出

```
2 ```

## 样例 #2

### 输入

```
4 2
3 1 2 4
```

### 输出

```
3 ```

## 样例 #3

### 输入

```
6 2
6 5 3 1 2 4
```

### 输出

```
6 ```

## 样例 #4

### 输入

```
2 10000000000
2 1
```

### 输出

```
2
```

# AI分析结果



### 题目中文重写
（题目已为中文，无需重复）

### 算法分类
模拟、队列

### 题解对比与分析
**核心思路**：当需要连续获胜次数 $k \geq n-1$ 时，最大值必定能连胜到底；否则模拟前 $k$ 轮比赛即可。

**关键优化**：发现当最大值成为擂主后永远不会失败，此时可直接返回最大值，避免了无效的大规模模拟。

### 高分题解推荐
#### 1. TheSky233 的题解（★★★★★）
**亮点**：
- 使用 deque 高效处理队列头尾操作
- 正确处理 $k \geq n$ 的特殊情况
- 代码结构清晰，变量命名规范
- 添加了必要的前置知识说明

**核心代码**：
```cpp
deque<int> q;
while(winstreak<k){
    int fr=q.front(); q.pop_front();
    int se=q.front(); q.pop_front();
    if(fr>se){
        winstreak++;
        q.push_front(fr);
        q.push_back(se);
    }else{
        winstreak=1;
        q.push_front(se);
        q.push_back(fr);
    }
}
```

#### 2. 至成天下 的题解（★★★★）
**亮点**：
- 使用单个变量维护擂主状态
- 提前处理 $k > n$ 的特殊情况
- 代码简洁，时间复杂度控制合理

**关键优化点**：
```cpp
if(k>n){ // 特判最大值
    cout<<maxn<<endl;
    return 0;
}
while(1){
    if(a<q.front()){ // 比较队头和擂主
        coun=1;
        int t=a;
        a=q.front();
        q.pop();
        q.push(t);
    }
    // ... 后续逻辑
}
```

### 关键技巧总结
1. **队列特性应用**：使用队列（或 deque）维护参赛者顺序，保证 $O(1)$ 时间完成头尾操作
2. **极值预判优化**：当 $k \geq n-1$ 时直接返回最大值，将时间复杂度从 $O(k)$ 降为 $O(n)$
3. **连胜计数重置**：新擂主出现时将计数器重置为 1（而非 0）

### 相似题目推荐
1. [CF455A Boredom](https://www.luogu.com.cn/problem/CF455A)（贪心策略与极值处理）
2. [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)（环形队列模拟）
3. [P1996 约瑟夫问题](https://www.luogu.com.cn/problem/P1996)（队列模拟经典问题）

### 题解心得摘录
1. TheSky233：  
   "注意 $k \leq 10^{12}$，如果纯模拟一定会 TLE，但是 $n \leq 500$，容易想到直接判断极值情况"  
   ——强调极端数据预处理的必要性

2. To_Carpe_Diem：  
   "hack 数据发现当 $n > k$ 时程序不一定正确"  
   ——验证边界条件的重要性

3. 至成天下：  
   "k>n时输出的能力值一定是最大的，纯模拟过不了10^12"  
   ——点明算法优化的核心突破口

这些经验体现了算法题解中：边界条件验证、极端数据处理、时间复杂度预判的重要性，是解决同类问题的通用思维模式。

---
处理用时：61.24秒
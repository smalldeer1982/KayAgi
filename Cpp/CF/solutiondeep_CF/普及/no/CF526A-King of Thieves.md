# 题目信息

# King of Thieves

## 题目描述

In this problem you will meet the simplified model of game King of Thieves.

In a new ZeptoLab game called "King of Thieves" your aim is to reach a chest with gold by controlling your character, avoiding traps and obstacles on your way.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526A/527857f6180736c7bf1bfc93b9cfb6aa3a26550b.png)An interesting feature of the game is that you can design your own levels that will be available to other players. Let's consider the following simple design of a level.

A dungeon consists of $ n $ segments located at a same vertical level, each segment is either a platform that character can stand on, or a pit with a trap that makes player lose if he falls into it. All segments have the same length, platforms on the scheme of the level are represented as '\*' and pits are represented as '.'.

One of things that affects speedrun characteristics of the level is a possibility to perform a series of consecutive jumps of the same length. More formally, when the character is on the platform number $ i_{1} $ , he can make a sequence of jumps through the platforms $ i_{1}&lt;i_{2}&lt;...&lt;i_{k} $ , if $ i_{2}-i_{1}=i_{3}-i_{2}=...=i_{k}-i_{k-1} $ . Of course, all segments $ i_{1},i_{2},...\ i_{k} $ should be exactly the platforms, not pits.

Let's call a level to be good if you can perform a sequence of four jumps of the same length or in the other words there must be a sequence $ i_{1},i_{2},...,i_{5} $ , consisting of five platforms so that the intervals between consecutive platforms are of the same length. Given the scheme of the level, check if it is good.

## 说明/提示

In the first sample test you may perform a sequence of jumps through platforms $ 2,5,8,11,14 $ .

## 样例 #1

### 输入

```
16
.**.*..*.***.**.
```

### 输出

```
yes```

## 样例 #2

### 输入

```
11
.*.*...*.*.
```

### 输出

```
no```

# AI分析结果



# King of Thieves

## 题目描述

在一个新游戏"King of Thieves"中，你需要设计一个地牢关卡。地牢由 $n$ 个水平排列的片段组成，每个片段是平台（`*`）或陷阱（`.`）。判断是否存在五个平台 $i_1,i_2,...,i_5$ 满足严格递增且相邻间距相等（即 $i_2-i_1 = i_3-i_2 = ... = i_5-i_4$）。

## 输入输出样例

### 样例1
输入：  
16  
.**.*..*.***.**.  
输出：  
yes  

### 样例2  
输入：  
11  
.*.*...*.*.  
输出：  
no  

---

**算法分类**：枚举

---

### 题解分析与结论

#### 最优思路总结
通过双重循环枚举跳跃起点和步长，检查是否存在满足条件的五个连续平台。核心技巧是**在内部循环中限制跳跃步长的范围，确保不越界访问数组**，并通过逐步跳跃验证平台连续性。

---

### 精选题解

#### 题解作者：Hooch（5星）
**关键亮点**：  
1. 枚举步长时通过循环条件 `k <= n` 确保不越界访问  
2. 使用逐步跳跃验证平台连续性，逻辑清晰  
3. 时间复杂度 $O(n^3)$ 在 $n \le 100$ 时完全可行  

**核心代码**：  
```cpp
for (int i = 1; i <= n; ++i) { // 枚举跳跃长度
    for (int j = 1; j <= n; ++j) { // 枚举起点
        if (s[j] == '.') continue;
        int k, cnt = 0;
        for (k = j + i; k <= n; k += i) { // 逐步跳跃并验证
            if (s[k] == '.') break;
            ++cnt;
        }
        if (cnt >= 4) return puts("yes"), 0;
    }
}
```

---

### 拓展建议
1. **类似题目**  
   - [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：枚举所有合法排列  
   - [P1036 选数](https://www.luogu.com.cn/problem/P1036)：枚举子集验证条件  
   - [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：枚举组合计算  

2. **调试技巧**  
   - 枚举类题目需特别注意循环边界条件  
   - 使用断言或手动计算跳跃后的索引范围  
   - 对于小数据范围问题，优先保证正确性再优化效率

---
处理用时：208.18秒
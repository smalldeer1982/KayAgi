# 题目信息

# Tape Programming

## 题目描述

There is a programming language in which every program is a non-empty sequence of "<" and ">" signs and digits. Let's explain how the interpreter of this programming language works. A program is interpreted using movement of instruction pointer (IP) which consists of two parts.

- Current character pointer (CP);
- Direction pointer (DP) which can point left or right;

Initially CP points to the leftmost character of the sequence and DP points to the right.

We repeat the following steps until the first moment that CP points to somewhere outside the sequence.

- If CP is pointing to a digit the interpreter prints that digit then CP moves one step according to the direction of DP. After that the value of the printed digit in the sequence decreases by one. If the printed digit was $ 0 $ then it cannot be decreased therefore it's erased from the sequence and the length of the sequence decreases by one.
- If CP is pointing to "<" or ">" then the direction of DP changes to "left" or "right" correspondingly. Then CP moves one step according to DP. If the new character that CP is pointing to is "<" or ">" then the previous character will be erased from the sequence.

If at any moment the CP goes outside of the sequence the execution is terminated.

It's obvious the every program in this language terminates after some steps.

We have a sequence $ s_{1},s_{2},...,s_{n} $ of "<", ">" and digits. You should answer $ q $ queries. Each query gives you $ l $ and $ r $ and asks how many of each digit will be printed if we run the sequence $ s_{l},s_{l+1},...,s_{r} $ as an independent program in this language.

## 样例 #1

### 输入

```
7 4
1>3>22<
1 3
4 7
7 7
1 7```

### 输出

```
0 1 0 1 0 0 0 0 0 0
2 2 2 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
2 3 2 1 0 0 0 0 0 0
```

# AI分析结果



## 算法分类
**链表模拟 + 并查集优化**

---

## 题解分析与结论

### 核心思路对比
1. **__gcd 的解法**  
   - **核心思想**：预处理每个位置在不同移动方向下的输出情况，利用并查集处理字符删除后的区间赋值问题。  
   - **关键变量**：  
     - `f[0][i][j]` 表示从位置 i 首次向左移动时，数字 j 的输出次数  
     - `f[1][i][j]` 表示首次到达位置 i 时，数字 j 的输出次数  
   - **链表实现**：用双向链表维护未被删除的字符，快速模拟指针移动  
   - **并查集优化**：在向左移动时，快速给连续区间赋值，避免重复操作  

2. **LinkyChristian 的解法**  
   - **核心思想**：预处理整个指针移动序列，记录每个操作步骤的输出前缀和  
   - **链表维护**：动态删除字符，记录指针移动路径  
   - **前缀和查询**：通过记录输出次数的前缀和数组，快速回答区间查询  

### 解决难点
- **动态删除处理**：双向链表动态维护存活字符，确保 CP 移动正确  
- **高效区间查询**：通过预处理输出次数的前缀差异，避免每次模拟整个区间  
- **并查集加速赋值**：在向左移动时，合并已处理区间，避免重复扫描  

---

## 题解评分（≥4星）

1. **__gcd 的解法（5星）**  
   - **亮点**：  
     - 并查集巧妙处理向左移动时的连续区间赋值  
     - 双向链表实现简洁高效  
   - **代码可读性**：结构清晰，关键逻辑有详细注释  
   - **优化程度**：时间复杂度 O(nα(n))，显著优于暴力解法  

2. **LinkyChristian 的解法（4星）**  
   - **亮点**：  
     - 操作序列预处理思路直观  
     - 利用前缀和快速响应查询  
   - **不足**：未明确处理某些边界情况（如连续删除）  

---

## 最优思路提炼
1. **链表维护存活字符**：通过 `l[i]` 和 `r[i]` 数组实现 O(1) 删除  
2. **双前缀数组设计**：区分向左/向右首次到达时的输出次数  
3. **并查集区间合并**：向左移动时，快速标记已处理的连续区间  

---

## 同类型题与算法套路
- **链表模拟删除**：[CF1172E]  
- **并查集区间合并**：[NOI2002 银河英雄传说]  
- **前缀和差分查询**：[洛谷 P1983 车站分级]  

---

## 推荐题目
1. **P1141 01迷宫**（链表维护连通性）  
2. **P1197 [JSOI2008]星球大战**（并查集逆序处理）  
3. **P3402 可持久化并查集**（结合链表与并查集）  

---

## 可视化设计

### 动画方案
1. **像素风格网格**：  
   - 每个字符显示为 16x16 像素块，数字为绿色，"<>"为红色  
   - CP 指针用黄色箭头表示，DP 方向用箭头颜色（左蓝/右橙）  

2. **关键操作高亮**：  
   - 删除字符时，方块变为灰色并播放「碎裂」音效  
   - 输出数字时，对应统计栏闪烁  

3. **并查集演示**：  
   - 向左移动时，用绿色线条连接合并的区间  

### 交互功能
- **步进控制**：空格键单步执行  
- **速度调节**：拖动条控制动画速度（1x-10x）  
- **音效**：  
  - `move.wav`：指针移动  
  - `delete.wav`：字符删除  
  - `output.wav`：数字输出  

---

## 核心代码片段（__gcd 解法）

```cpp
// 双向链表初始化
for(int i = 0; i <= n; i++) {
    l[i] = i - 1; 
    r[i] = i + 1;
}

// 并查集处理向左移动
void move(int &p, int &dir) {
    if(dir == 0) { // 向左移动
        int j = find(nxt) + 1;
        while(j <= p) {
            for(int i=0; i<10; i++) 
                f[0][j][i] = b[i];
            unionn(j, j-1); 
            j = find(j)+1;
        }
    }
}
```

---

## 个人心得摘录
> "细节真的超多" —— 需特别注意字符删除后链表的更新顺序，以及并查集赋值的边界条件。调试时可通过打印链表状态逐帧验证。

---
处理用时：62.20秒
# 题目信息

# Escape from Stones

## 题目描述

Squirrel Liss lived in a forest peacefully, but unexpected trouble happens. Stones fall from a mountain. Initially Squirrel Liss occupies an interval $ [0,1] $ . Next, $ n $ stones will fall and Liss will escape from the stones. The stones are numbered from 1 to $ n $ in order.

The stones always fall to the center of Liss's interval. When Liss occupies the interval $ [k-d,k+d] $ and a stone falls to $ k $ , she will escape to the left or to the right. If she escapes to the left, her new interval will be $ [k-d,k] $ . If she escapes to the right, her new interval will be $ [k,k+d] $ .

You are given a string $ s $ of length $ n $ . If the $ i $ -th character of $ s $ is "l" or "r", when the $ i $ -th stone falls Liss will escape to the left or to the right, respectively. Find the sequence of stones' numbers from left to right after all the $ n $ stones falls.

## 说明/提示

In the first example, the positions of stones 1, 2, 3, 4, 5 will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF264A/c25aff142a5735311a4288820a328b17b4aeb12a.png), respectively. So you should print the sequence: 3, 5, 4, 2, 1.

## 样例 #1

### 输入

```
llrlr
```

### 输出

```
3
5
4
2
1
```

## 样例 #2

### 输入

```
rrlll
```

### 输出

```
1
2
5
4
3
```

## 样例 #3

### 输入

```
lrlrr
```

### 输出

```
2
4
5
3
1
```

# AI分析结果



### 题目翻译
#### 逃离落石
**题目描述**  
松鼠Liss原本占据区间$[0,1]$。随后$n$块石头依次落下，每块石头会落在Liss当前占据区间的中点。每当石头落下时，Liss会向左或右逃离，导致区间缩小。若第$i$个字符为'l'，Liss向左逃离，新区间右端点变为原中点；若为'r'则向右逃离，左端点变为原中点。要求按最终所有石头的位置从左到右输出它们的编号顺序。

**输入样例与输出**  
样例1输入`llrlr`，输出为3、5、4、2、1（详见原题图示）。

---

### 算法分类  
**构造、模拟**

---

### 题解对比与结论  
各题解核心思路一致：**所有'r'操作的石头按顺序输出，所有'l'操作的石头逆序输出**。关键点在于观察到选择方向对最终位置顺序的影响规律，无需模拟区间变化过程。

#### 高星题解（4★+）  
1. **nightwatch.ryan（5★）**  
   - **关键亮点**：代码极简，两次遍历解决问题。第一次遍历直接输出'r'的编号，第二次逆序遍历输出'l'的编号。时间复杂度$O(n)$，空间复杂度$O(1)$，无额外数据结构。  
   - **代码核心**：  
     ```cpp
     for(int i=0; i<len; i++) if(s[i]=='r') printf("%d\n",i+1);
     for(int i=len-1; i>=0; i--) if(s[i]=='l') printf("%d\n",i+1);
     ```

2. **分离性漫游（5★）**  
   - **思路与实现**：与上例完全一致，代码风格清晰，强调规律发现过程，适合理解思路。  

3. **Speech_less（4★）**  
   - **亮点**：分拆'r'和'l'到不同数组，明确升序与降序输出逻辑，代码结构更易扩展。  
   - **核心代码**：  
     ```cpp
     for(int i=1; i<=rs; i++) cout<<r[i]+1<<"\n";  // r升序
     for(int i=ls; i>=1; i--) cout<<l[i]+1<<"\n"; // l降序
     ```

---

### 关键技巧  
1. **规律观察**：避免模拟区间分裂过程，直接通过方向字符确定输出顺序。  
2. **逆序处理**：利用栈或逆序遍历实现'l'的逆序输出，减少计算量。  

---

### 相似题目推荐  
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)（贪心构造最小数）  
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（优先队列贪心）  
3. [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)（栈的经典应用）

---
处理用时：98.33秒
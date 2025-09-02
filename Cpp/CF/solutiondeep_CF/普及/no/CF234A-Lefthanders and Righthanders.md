# 题目信息

# Lefthanders and Righthanders

## 题目描述

One fine October day a mathematics teacher Vasily Petrov went to a class and saw there $ n $ pupils who sat at the ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234A/666f6519688863e0a36337875170dd12050e1c31.png) desks, two people at each desk. Vasily quickly realized that number $ n $ is even. Like all true mathematicians, Vasily has all students numbered from 1 to $ n $ .

But Vasily Petrov did not like the way the children were seated at the desks. According to him, the students whose numbers differ by $ 1 $ , can not sit together, as they talk to each other all the time, distract others and misbehave.

On the other hand, if a righthanded student sits at the left end of the desk and a lefthanded student sits at the right end of the desk, they hit elbows all the time and distract each other. In other cases, the students who sit at the same desk, do not interfere with each other.

Vasily knows very well which students are lefthanders and which ones are righthanders, and he asks you to come up with any order that meets these two uncomplicated conditions (students do not talk to each other and do not bump their elbows). It is guaranteed that the input is such that at least one way to seat the students always exists.

## 样例 #1

### 输入

```
6
LLRLLL
```

### 输出

```
1 4
2 5
6 3
```

## 样例 #2

### 输入

```
4
RRLL
```

### 输出

```
3 1
4 2
```

# AI分析结果



# Lefthanders and Righthanders（左撇子与右撇子）

## 题目重述
$ n $ 名学生（偶数）两人一桌，要求：
1. 编号差为1的学生不能同桌
2. 同一桌的右撇子（R）不能在左侧，左撇子（L）不能在右侧（即RL组合不可）

输出满足条件的任意一种座位安排方案，保证有解。

**算法分类**：构造

---

## 题解分析与结论
### 核心思路
1. **配对策略**：将学生 $ i $ 与 $ i+\frac{n}{2} $ 配对，确保相邻编号不会出现在同一桌
2. **方向处理**：若配对出现RL组合，交换两人位置输出；其他组合直接输出

### 最优题解亮点
1. **Hanriver（4星）**  
   - 清晰分析两种约束的优先级，采用CF经典构造套路  
   - 正确处理字符串索引与编号的偏移关系  
   ```cpp
   for(int i=0;i<=n/2-1;i++) 
       if(a[i]=='R'&&a[i+n/2]=='L') 
           printf("%d %d\n",i+n/2+1,i+1);
   ```

2. **Leonid（4星）**  
   - 代码极简风格，直接命中问题核心  
   - 显式处理字符数组的1-based索引  
   ```cpp
   for(int i=1;i<=(n>>1);++i)
       if(s[i]=='R'&&s[i+(n>>1)]=='L') 
           printf("%d %d\n",i+(n>>1),i);
   ```

3. **hanyuchen2019（4星）**  
   - 使用直观的变量命名增强可读性  
   - 特别强调文件操作的重要性避免低级错误  
   ```cpp
   if(ch[i]=='R'&&ch[n/2+i]=='L')
       printf("%d %d\n",n/2+i,i);
   ```

---

## 关键技巧总结
1. **数学构造法**：利用编号差为n/2的配对方式，巧妙规避相邻编号问题
2. **特判交换策略**：仅对RL组合进行位置交换，其他组合直接输出
3. **索引处理技巧**：注意字符数组索引与题目编号的转换（0-based vs 1-based）

---

## 同类题目推荐
1. CF12B - [正确的等式构造]（构造+排序）
2. P1105 - [平台](https://www.luogu.com.cn/problem/P1105)（构造+区间处理）
3. CF1118A - [水桶问题](https://www.luogu.com.cn/problem/CF1118A)（数学构造+极值分析）

---

## 题解心得摘录
- **文件操作**：多个题解强调必须添加`freopen`，否则会Runtime Error（来自Hanriver、hanyuchen2019）
- **调试经验**：特别注意字符数组索引偏移问题（如Leonid使用s+1索引）
- **构造思维**：将复杂约束拆分为独立处理的数学问题（Hanriver的约束分离分析法）

---
处理用时：51.71秒
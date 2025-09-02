# 题目信息

# Planting Trees

## 题目描述

Vasya is a Greencode wildlife preservation society proponent. One day he found an empty field nobody owned, divided it into $ n×m $ squares and decided to plant a forest there. Vasya will plant $ nm $ trees of all different heights from $ 1 $ to $ nm $ . For his forest to look more natural he wants any two trees growing in the side neighbouring squares to have the absolute value of difference in heights to be strictly more than 1. Help Vasya: make the plan of the forest planting for which this condition is fulfilled.

## 样例 #1

### 输入

```
2 3
```

### 输出

```
3 6 2
5 1 4
```

## 样例 #2

### 输入

```
2 1
```

### 输出

```
-1
```

# AI分析结果



# Planting Trees

## 题目描述

Vasya 是 Greencode 野生动物保护协会的支持者。某天他发现了一块无主的空地，将其划分为 $n×m$ 的方格，并决定在此种植森林。Vasya 将种植 $nm$ 棵高度互不相同的树，高度从 $1$ 到 $nm$。为了让森林看起来更自然，他希望任意两棵在相邻（上下左右）方格的树的高度差的绝对值严格大于 1。请帮助 Vasya 设计满足此条件的种植方案。

## 样例 #1

### 输入

```
2 3
```

### 输出

```
3 6 2
5 1 4
```

## 样例 #2

### 输入

```
2 1
```

### 输出

```
-1
```

---

**算法分类**  
构造

---

### 题解分析与结论

题目核心在于构造满足相邻元素差严格大于 1 的矩阵。所有题解均基于以下思路：
1. **特判条件**：当 $n=1 \land m=1$ 时输出 1；当 $n+m<5$ 且非 1×1 时输出 -1。
2. **分组交替填充**：将数分为前半段（小数）和后半段（大数），按坐标和奇偶性交替填入。

**关键思路**  
- 将数分为两组：小数（$1 \sim \lfloor nm/2 \rfloor$）和大数（$\lfloor nm/2 \rfloor+1 \sim nm$）。
- 根据 $(i+j)\%2$ 的值决定当前位置填大数还是小数，确保相邻数来自不同组，差值至少为 $\lfloor nm/2 \rfloor + 1 - \lfloor nm/2 \rfloor = 1$，结合组内递增顺序保证实际差值更大。

---

### 高星题解推荐

#### 题解作者：zct_sky（4 星）
**亮点**  
- 代码简洁，直接分组交替输出。
- 核心代码：
  ```cpp
  int l=1, b=n*m/2+1;
  for(int i=0; i<n; i++, puts(""))
      for(int j=0; j<m; j++, putchar(' '))
          if((i+j)%2) cout << l++;
          else cout << b++;
  ```
**注意**：行末可能有多余空格，但多数评测系统接受此格式。

#### 题解作者：DecemberFox（4 星）
**亮点**  
- 模块化输入输出，代码结构清晰。
- 核心逻辑：
  ```cpp
  int a=1, b=(n*m)/2+1;
  for(i=1; i<=n; ++i)
      for(j=1; j<=m; ++j)
          if((i+j)%2) write(a++, ' ');
          else write(b++, ' ');
  ```

#### 题解作者：xiaozeyu（4 星）
**亮点**  
- 变量命名清晰，逻辑简洁。
- 核心代码：
  ```cpp
  t1 = n*m/2 + 1;
  for (i=0; i<n; i++, cout<<'\n')
      for (j=0; j<m; j++)
          if ((i+j)%2==0) cout << t1++ << ' ';
          else cout << t2++ << ' ';
  ```

---

### 关键技巧总结
1. **分组构造**：将数据分为互补区间，避免相邻差过小。
2. **坐标奇偶性**：利用 $(i+j)\%2$ 快速确定填充模式。
3. **特判优化**：通过数学观察简化无解情况的判断。

---

### 类似题目推荐
1. [CF510B Fox And Two Dots](https://codeforces.com/problemset/problem/510/B)（构造回路）
2. [CF1450D Rating Compression](https://codeforces.com/problemset/problem/1450/D)（排列构造）
3. [CF3D Least Cost Bracket Sequence](https://codeforces.com/problemset/problem/3/D)（条件构造）

---
处理用时：240.93秒
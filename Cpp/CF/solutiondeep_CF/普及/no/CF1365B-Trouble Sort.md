# 题目信息

# Trouble Sort

## 题目描述

Ashish has $ n $ elements arranged in a line.

These elements are represented by two integers $ a_i $ — the value of the element and $ b_i $ — the type of the element (there are only two possible types: $ 0 $ and $ 1 $ ). He wants to sort the elements in non-decreasing values of $ a_i $ .

He can perform the following operation any number of times:

- Select any two elements $ i $ and $ j $ such that $ b_i \ne b_j $ and swap them. That is, he can only swap two elements of different types in one move.

Tell him if he can sort the elements in non-decreasing values of $ a_i $ after performing any number of operations.

## 说明/提示

For the first case: The elements are already in sorted order.

For the second case: Ashish may first swap elements at positions $ 1 $ and $ 2 $ , then swap elements at positions $ 2 $ and $ 3 $ .

For the third case: The elements are already in sorted order.

For the fourth case: No swap operations may be performed as there is no pair of elements $ i $ and $ j $ such that $ b_i \ne b_j $ . The elements cannot be sorted.

For the fifth case: Ashish may swap elements at positions $ 3 $ and $ 4 $ , then elements at positions $ 1 $ and $ 2 $ .

## 样例 #1

### 输入

```
5
4
10 20 20 30
0 1 0 1
3
3 1 2
0 1 1
4
2 2 4 8
1 1 1 1
3
5 15 4
0 0 0
4
20 10 100 50
1 0 0 1```

### 输出

```
Yes
Yes
Yes
No
Yes```

# AI分析结果

### 题目内容重写
#### 题目描述
Ashish 有 $n$ 个元素排列成一行。这些元素由两个整数 $a_i$ 和 $b_i$ 表示，其中 $a_i$ 是元素的值，$b_i$ 是元素的类型（只有两种可能的类型：$0$ 和 $1$）。他希望将这些元素按 $a_i$ 的非递减顺序排序。

他可以执行以下操作任意次数：
- 选择任意两个元素 $i$ 和 $j$，使得 $b_i \ne b_j$，并交换它们。也就是说，他只能交换两个不同类型的元素。

请告诉他，在执行任意次数的操作后，是否可以将元素按 $a_i$ 的非递减顺序排序。

#### 说明/提示
- 对于第一个样例：元素已经按顺序排列。
- 对于第二个样例：Ashish 可以先交换位置 $1$ 和 $2$ 的元素，然后交换位置 $2$ 和 $3$ 的元素。
- 对于第三个样例：元素已经按顺序排列。
- 对于第四个样例：由于没有一对元素 $i$ 和 $j$ 满足 $b_i \ne b_j$，因此无法执行任何交换操作。元素无法排序。
- 对于第五个样例：Ashish 可以先交换位置 $3$ 和 $4$ 的元素，然后交换位置 $1$ 和 $2$ 的元素。

#### 样例 #1
##### 输入
```
5
4
10 20 20 30
0 1 0 1
3
3 1 2
0 1 1
4
2 2 4 8
1 1 1 1
3
5 15 4
0 0 0
4
20 10 100 50
1 0 0 1
```

##### 输出
```
Yes
Yes
Yes
No
Yes
```

### 算法分类
排序、模拟

### 题解分析与结论
所有题解的核心思路都是基于以下观察：
1. 如果数组中存在两种类型的元素（即既有 $0$ 又有 $1$），那么可以通过交换操作将数组排序。
2. 如果数组中只有一种类型的元素，则无法进行交换操作，此时只能判断数组是否已经是非递减的。

题解之间的差异主要体现在代码的实现细节和优化上。大多数题解都采用了类似的逻辑，即先判断是否存在两种类型的元素，如果存在则输出 `Yes`，否则判断数组是否已经是非递减的。

### 评分较高的题解
#### 题解1：封禁用户 (赞：7)
- **星级**：5星
- **关键亮点**：代码简洁，逻辑清晰，直接通过判断是否存在两种类型的元素来决定输出结果。
- **核心代码**：
```cpp
bool f1 = 0,f0 = 0;
F(i,1,n) f1 |= (b[i]),f0 |= (!b[i]);
if(f1&&f0) {
    puts("Yes");
    goto END;
}
F(i,1,n-1)
    if(a[i] > a[i+1]) {
        puts("No");
        goto END;	
    }
puts("Yes");
```

#### 题解2：do_while_true (赞：2)
- **星级**：4星
- **关键亮点**：代码简洁，逻辑清晰，通过判断是否存在两种类型的元素来决定输出结果。
- **核心代码**：
```cpp
if(l+y==1&&f==1) puts("No");
else puts("Yes");
```

#### 题解3：Blunt_Feeling (赞：2)
- **星级**：4星
- **关键亮点**：代码简洁，逻辑清晰，通过判断是否存在两种类型的元素来决定输出结果。
- **核心代码**：
```cpp
if(f0&&f1) puts("Yes");
else puts(check()?"Yes":"No");
```

### 最优关键思路或技巧
1. **类型判断**：通过检查数组中是否存在两种类型的元素，来决定是否可以进行交换操作。
2. **非递减判断**：如果数组中只有一种类型的元素，则直接判断数组是否已经是非递减的。

### 可拓展之处
类似的问题可以扩展到更多类型的元素，或者不同类型的元素有不同的交换规则。此外，可以进一步优化判断非递减序列的算法，使其更加高效。

### 推荐题目
1. [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)
2. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
3. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

### 个人心得摘录
- **封禁用户**：通过简单的逻辑判断，直接得出结论，代码简洁高效。
- **do_while_true**：通过判断是否存在两种类型的元素，快速得出结论，代码简洁明了。
- **Blunt_Feeling**：通过判断是否存在两种类型的元素，快速得出结论，代码简洁高效。

---
处理用时：32.65秒
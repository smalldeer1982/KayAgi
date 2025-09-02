# 题目信息

# Generating Sets

## 题目描述

You are given a set $ Y $ of $ n $ distinct positive integers $ y_{1},y_{2},...,y_{n} $ .

Set $ X $ of $ n $ distinct positive integers $ x_{1},x_{2},...,x_{n} $ is said to generate set $ Y $ if one can transform $ X $ to $ Y $ by applying some number of the following two operation to integers in $ X $ :

1. Take any integer $ x_{i} $ and multiply it by two, i.e. replace $ x_{i} $ with $ 2·x_{i} $ .
2. Take any integer $ x_{i} $ , multiply it by two and add one, i.e. replace $ x_{i} $ with $ 2·x_{i}+1 $ .

Note that integers in $ X $ are not required to be distinct after each operation.

Two sets of distinct integers $ X $ and $ Y $ are equal if they are equal as sets. In other words, if we write elements of the sets in the array in the increasing order, these arrays would be equal.

Note, that any set of integers (or its permutation) generates itself.

You are given a set $ Y $ and have to find a set $ X $ that generates $ Y $ and the maximum element of $ X $ is mininum possible.

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
4 5 2 3 1 
```

## 样例 #2

### 输入

```
6
15 14 3 13 1 12
```

### 输出

```
12 13 14 7 3 1 
```

## 样例 #3

### 输入

```
6
9 7 13 17 5 11
```

### 输出

```
4 5 2 6 3 1 
```

# AI分析结果

### 题目内容
# 生成集合

## 题目描述
给定一个由 $n$ 个不同正整数 $y_{1},y_{2},\cdots,y_{n}$ 组成的集合 $Y$ 。
如果可以通过对集合 $X$ 中的整数应用以下两种操作若干次，将集合 $X$ 转换为集合 $Y$，则称由 $n$ 个不同正整数 $x_{1},x_{2},\cdots,x_{n}$ 组成的集合 $X$ 生成了集合 $Y$ ：
1. 取任意整数 $x_{i}$ 并将其乘以 2，即把 $x_{i}$ 替换为 $2·x_{i}$ 。
2. 取任意整数 $x_{i}$ ，将其乘以 2 并加 1，即把 $x_{i}$ 替换为 $2·x_{i}+1$ 。
注意，每次操作后集合 $X$ 中的整数不要求是不同的。
两个由不同整数组成的集合 $X$ 和 $Y$ 相等，当且仅当它们作为集合相等。换句话说，如果我们将集合中的元素按升序写入数组，这些数组将相等。
注意，任何整数集合（或其排列）都能生成自身。
给定集合 $Y$ ，你必须找到一个生成 $Y$ 的集合 $X$ ，且 $X$ 中的最大元素尽可能小。

## 样例 #1
### 输入
```
5
1 2 3 4 5
```
### 输出
```
4 5 2 3 1 
```

## 样例 #2
### 输入
```
6
15 14 3 13 1 12
```
### 输出
```
12 13 14 7 3 1 
```

## 样例 #3
### 输入
```
6
9 7 13 17 5 11
```
### 输出
```
4 5 2 6 3 1 
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解思路基本一致，均采用贪心策略。要点为每次选取集合中的最大元素，不断将其除以2，直到得到一个集合中不存在的数，然后将该数替换原最大数插入集合。若最大元素一直除到0都未找到可替换的数，则结束操作。解决的难点在于如何高效地维护集合以及实现贪心选择，不同题解在数据结构使用上略有差异，多数使用`set`，有一个使用`priority_queue`结合`unordered_map`。整体思路清晰，实现方式较为常规。

### 所选的题解
 - **作者lgx57**：★★★★
    - **关键亮点**：代码简洁明了，直接使用`set`维护集合，逻辑清晰，注释较少但不影响理解。
    - **重点代码**：
```cpp
while ("ljd loves xyq forever"){
    int x=(*(--s.end()));
    int num=x;
    while (x){
        if (!s.count(x)){
            s.erase(num);
            s.insert(x);
            break;
        }
        x>>=1;
    }
    if (x==0){
        s.insert(num);
        break;
    }
}
```
核心实现思想：每次从`set`中取出最大元素，不断右移（除以2），若找到集合中不存在的数则替换原最大数，若除到0都未找到则结束循环。
 - **作者Little_Cabbage**：★★★★
    - **关键亮点**：代码结构完整，有自定义的输入输出函数，对知识点有明确说明，使用`set`维护集合，逻辑清晰。
    - **重点代码**：
```cpp
while (1) {
    int x = *(--s.end());
    int old = x;
    while (x && s.count(x)) x >>= 1;
    if (!x) break;
    s.erase(old);
    s.insert(x);
}
```
核心实现思想：从`set`获取最大元素，不断右移（除以2），若找到集合中不存在的数则替换原最大数，若除到0则结束循环。
 - **作者仗剑_天涯**：★★★★
    - **关键亮点**：对题目有翻译，贪心思路表述清晰，代码简洁，使用`set`维护集合。
    - **重点代码**：
```cpp
while(1)
{
    set<int>::iterator i=tree.end();
    i--;
    t=*i;
    while(tree.find(t)!=tree.end()&&t)
    {
        t>>=1;
    }
    if(t==0) break;
    tree.erase(i);
    tree.insert(t);
}
```
核心实现思想：从`set`找到最大元素，不断右移（除以2），若找到集合中不存在的数则替换原最大数，若除到0则结束循环。

### 最优关键思路或技巧
使用`set`数据结构，利用其自动排序和快速查找、插入、删除元素的特性，高效实现贪心算法中对集合的维护操作。每次选取最大元素并不断缩小，以达到使生成集合$X$中最大元素最小的目的。

### 拓展
同类型题通常围绕贪心策略，结合集合操作或元素变换规则，求某种最优解。类似算法套路是在给定操作规则下，通过合理的贪心选择，不断优化目标值。例如给定一些数字和合并操作，每次合并两个数字产生新数字并带来一定代价，求最小代价等。

### 洛谷相似题目推荐
 - [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过不断合并最小的两个数，求最小总代价，考察贪心策略。
 - [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及双方博弈下的贪心策略运用。
 - [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过对元素排序实现贪心，优化目标值。 

---
处理用时：48.74秒
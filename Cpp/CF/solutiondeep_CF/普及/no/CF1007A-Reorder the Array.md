# 题目信息

# Reorder the Array

## 题目描述

You are given an array of integers. Vasya can permute (change order) its integers. He wants to do it so that as many as possible integers will become on a place where a smaller integer used to stand. Help Vasya find the maximal number of such integers.

For instance, if we are given an array $ [10, 20, 30, 40] $ , we can permute it so that it becomes $ [20, 40, 10, 30] $ . Then on the first and the second positions the integers became larger ( $ 20>10 $ , $ 40>20 $ ) and did not on the third and the fourth, so for this permutation, the number that Vasya wants to maximize equals $ 2 $ . Read the note for the first example, there is one more demonstrative test case.

Help Vasya to permute integers in such way that the number of positions in a new array, where integers are greater than in the original one, is maximal.

## 说明/提示

In the first sample, one of the best permutations is $ [1, 5, 5, 3, 10, 1, 1] $ . On the positions from second to fifth the elements became larger, so the answer for this permutation is 4.

In the second sample, there is no way to increase any element with a permutation, so the answer is 0.

## 样例 #1

### 输入

```
7
10 1 1 1 5 5 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1 1 1 1 1
```

### 输出

```
0
```

# AI分析结果

### 题目重写
#### 重排数组

**题目描述**

给定一个整数数组。Vasya可以重新排列（改变顺序）数组中的整数。他希望尽可能多的整数在新的位置上比原来的位置上的整数大。帮助Vasya找到满足条件的最大整数个数。

例如，给定数组 $[10, 20, 30, 40]$，我们可以将其重新排列为 $[20, 40, 10, 30]$。在第一个和第二个位置上，整数比原来的大（$20>10$，$40>20$），而在第三个和第四个位置上没有，因此对于这个排列，Vasya想要最大化的数字是 $2$。请阅读第一个样例的说明，那里有一个更具说明性的测试用例。

帮助Vasya以这种方式重新排列整数，使得新数组中比原来位置上的整数大的位置数最大。

**说明/提示**

在第一个样例中，一个最佳排列是 $[1, 5, 5, 3, 10, 1, 1]$。在第二个到第五个位置上，元素比原来的大，因此这个排列的答案是4。

在第二个样例中，无法通过任何排列增加任何元素，因此答案是0。

**样例 #1**

**输入**

```
7
10 1 1 1 5 5 3
```

**输出**

```
4
```

**样例 #2**

**输入**

```
5
1 1 1 1 1
```

**输出**

```
0
```

### 算法分类
贪心

### 题解分析与结论
该问题的核心是通过贪心算法找到一种排列方式，使得尽可能多的元素在新位置上比原来的位置上的元素大。大多数题解都采用了排序后贪心匹配的思路，即先对数组进行排序，然后通过双指针或类似的方法进行匹配。

### 评分较高的题解

#### 1. 作者：kevin1616 (赞：2)
**星级：4星**
**关键亮点：**
- 思路清晰，代码简洁。
- 通过排序后贪心匹配，时间复杂度为 $O(n \log n)$。
- 使用了双指针技巧，避免了不必要的重复匹配。

**代码核心实现：**
```cpp
sort(a + 1, a + n + 1); // 给序列排序
for(int i = 2; i <= n; i++){ // 枚举当前较小元素
    if(a[i] > a[sum]){ // 判断当前较小元素是否可以配对当前最小元素
        sum++; // 删除当前最小元素
        ans++; // 将答案个数增加1
    }
}
```

#### 2. 作者：chenpengda (赞：2)
**星级：4星**
**关键亮点：**
- 详细解释了贪心匹配的思路。
- 通过优化避免了重复匹配，提高了效率。
- 代码实现简洁明了。

**代码核心实现：**
```cpp
int j = 0;
for(int i = 0; i < n - 1 && j < n; i++){
    j++; // 将j向后累加，原因在上面
    if(yuan[j] > yuan[i]){ // 代表可以匹配
        sum++;
    }
    else i--; // 相当于还是这个i，但是是下一个j。
}
```

#### 3. 作者：nightwatch.ryan (赞：1)
**星级：4星**
**关键亮点：**
- 思路清晰，代码简洁。
- 通过排序后贪心匹配，时间复杂度为 $O(n \log n)$。
- 使用了双指针技巧，避免了不必要的重复匹配。

**代码核心实现：**
```cpp
std::sort(a, a + n);
for(register int i = 0, j = 0; i < n; i++){
    j++;
    if(j > n){
        break;
    }
    if(a[i] < a[j]){
        res++;
    }else{
        i--;
    }
}
```

### 最优关键思路或技巧
1. **排序后贪心匹配**：先对数组进行排序，然后通过双指针或类似的方法进行匹配，确保每个元素尽可能匹配到比它大的元素。
2. **双指针技巧**：使用双指针可以避免重复匹配，提高匹配效率。
3. **时间复杂度优化**：通过排序和双指针技巧，将时间复杂度优化到 $O(n \log n)$。

### 可拓展之处
该问题可以拓展到其他类似的贪心匹配问题，例如：
- 匹配问题：给定两个数组，如何匹配使得满足某种条件的匹配数最大。
- 区间覆盖问题：给定一组区间，如何选择最少的区间覆盖所有点。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：35.02秒
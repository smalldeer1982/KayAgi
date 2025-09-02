# 题目信息

# Vitya in the Countryside

## 题目描述

Every summer Vitya comes to visit his grandmother in the countryside. This summer, he got a huge wart. Every grandma knows that one should treat warts when the moon goes down. Thus, Vitya has to catch the moment when the moon is down.

Moon cycle lasts 30 days. The size of the visible part of the moon (in Vitya's units) for each day is $ 0 $ , $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ , $ 7 $ , $ 8 $ , $ 9 $ , $ 10 $ , $ 11 $ , $ 12 $ , $ 13 $ , $ 14 $ , $ 15 $ , $ 14 $ , $ 13 $ , $ 12 $ , $ 11 $ , $ 10 $ , $ 9 $ , $ 8 $ , $ 7 $ , $ 6 $ , $ 5 $ , $ 4 $ , $ 3 $ , $ 2 $ , $ 1 $ , and then cycle repeats, thus after the second $ 1 $ again goes $ 0 $ .

As there is no internet in the countryside, Vitya has been watching the moon for $ n $ consecutive days and for each of these days he wrote down the size of the visible part of the moon. Help him find out whether the moon will be up or down next day, or this cannot be determined by the data he has.

## 说明/提示

In the first sample, the size of the moon on the next day will be equal to $ 8 $ , thus the answer is "UP".

In the second sample, the size of the moon on the next day will be $ 11 $ , thus the answer is "DOWN".

In the third sample, there is no way to determine whether the size of the moon on the next day will be $ 7 $ or $ 9 $ , thus the answer is -1.

## 样例 #1

### 输入

```
5
3 4 5 6 7
```

### 输出

```
UP
```

## 样例 #2

### 输入

```
7
12 13 14 15 14 13 12
```

### 输出

```
DOWN
```

## 样例 #3

### 输入

```
1
8
```

### 输出

```
-1
```

# AI分析结果

### 题目翻译
# 维佳在乡下

## 题目描述
每年夏天，维佳都会去乡下看望他的奶奶。今年夏天，他长了一个很大的疣。每个奶奶都知道，应该在月亮下山的时候治疗疣。因此，维佳必须抓住月亮下山的时刻。

月亮的周期持续 30 天。每天月亮可见部分的大小（以维佳的单位计）为 0、1、2、3、4、5、6、7、8、9、10、11、12、13、14、15、14、13、12、11、10、9、8、7、6、5、4、3、2、1，然后周期重复，因此在第二个 1 之后又会变成 0。

由于乡下没有网络，维佳连续观察了月亮 $n$ 天，并记录下了每天月亮可见部分的大小。请帮助他判断第二天月亮是会升起还是落下，或者根据他现有的数据无法确定。

## 说明/提示
在第一个样例中，第二天月亮的大小将等于 8，因此答案是 “UP”。

在第二个样例中，第二天月亮的大小将是 11，因此答案是 “DOWN”。

在第三个样例中，无法确定第二天月亮的大小是 7 还是 9，因此答案是 -1。

## 样例 #1
### 输入
```
5
3 4 5 6 7
```
### 输出
```
UP
```

## 样例 #2
### 输入
```
7
12 13 14 15 14 13 12
```
### 输出
```
DOWN
```

## 样例 #3
### 输入
```
1
8
```
### 输出
```
-1
```

### 算法分类
无算法分类

### 综合分析与结论
这些题解的核心思路都是根据输入的月亮大小数据，判断第二天月亮的变化趋势（上升或下降）。主要依据最后一天或最后两天的月亮大小数据，同时考虑特殊值 0 和 15。
- **思路**：都关注最后一天或最后两天的月亮大小，通过比较大小判断升降趋势，对 0 和 15 进行特判。
- **算法要点**：利用最后一个或最后两个数据判断趋势，特判 0 和 15 的情况。
- **解决难点**：处理特殊值 0 和 15，以及当 $n = 1$ 时无法判断的情况。

### 题解评分
- **ahawzlc**：4星。思路清晰，有图形辅助理解，代码简洁。
- **CobaltChloride**：3星。思路简单直接，但代码中数组定义有问题。
- **蒟蒻lxy**：3星。分析详细，但代码嵌套较多。
- **锦瑟，华年**：3星。考虑情况全面，但代码结构稍显复杂。
- **shenmadongdong**：3星。思路正确，但使用的是 Pascal 语言，且逻辑判断较复杂。

### 所选题解
- **ahawzlc**：4星。关键亮点在于通过图形辅助理解，思路清晰，代码简洁。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int va1,va2,n;
    cin>>n;
    for(int i=1;i<n;i++) cin>>va1;
    cin>>va2;
    if(va2==15) puts("DOWN");//特判1
    else if(va2==0) puts("UP");//特判2
    else if(n==1) puts("-1");//序列len==1，无法判断
    else if(va2>va1) puts("UP");//升序
    else puts("DOWN");//降序
    return 0;
}
```
核心实现思想：先读取数据，然后根据最后一个数据是否为 15 或 0 进行特判，再判断序列长度是否为 1，最后根据最后两个数据的大小关系判断升降趋势。

### 关键思路或技巧
- 利用最后两个数据判断升降趋势，因为两个数据是最短的能够判断升降序的序列。
- 对特殊值 0 和 15 进行特判，因为它们的下一个值是确定的。

### 拓展思路
同类型题可能会涉及其他周期性变化的问题，如季节变化、时钟指针转动等，解题思路类似，都是根据最后一个或最后几个数据判断下一个状态。

### 推荐洛谷题目
- P1001 A+B Problem
- P1000 超级玛丽游戏
- P1002 [NOIP2002 普及组] 过河卒

### 个人心得
无

---
处理用时：30.23秒
# 题目信息

# Frodo and pillows

## 题目描述

 $ n $ hobbits are planning to spend the night at Frodo's house. Frodo has $ n $ beds standing in a row and $ m $ pillows ( $ n<=m $ ). Each hobbit needs a bed and at least one pillow to sleep, however, everyone wants as many pillows as possible. Of course, it's not always possible to share pillows equally, but any hobbit gets hurt if he has at least two pillows less than some of his neighbors have.

Frodo will sleep on the $ k $ -th bed in the row. What is the maximum number of pillows he can have so that every hobbit has at least one pillow, every pillow is given to some hobbit and no one is hurt?

## 说明/提示

In the first example Frodo can have at most two pillows. In this case, he can give two pillows to the hobbit on the first bed, and one pillow to each of the hobbits on the third and the fourth beds.

In the second example Frodo can take at most four pillows, giving three pillows to each of the others.

In the third example Frodo can take three pillows, giving two pillows to the hobbit in the middle and one pillow to the hobbit on the third bed.

## 样例 #1

### 输入

```
4 6 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 10 3
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3 6 1
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# 弗罗多和枕头

## 题目描述
有\(n\)个霍比特人计划在弗罗多的家中过夜。弗罗多有排成一排的\(n\)张床和\(m\)个枕头（\(n \leq m\)）。每个霍比特人都需要一张床和至少一个枕头才能入睡，然而，每个人都希望拥有尽可能多的枕头。当然，并不总是能够平均分配枕头，但是如果任何一个霍比特人比他的一些邻居少至少两个枕头，他就会感到受伤。
弗罗多将睡在这一排的第\(k\)张床上。在每个霍比特人都至少有一个枕头，每个枕头都分给了某个霍比特人，且没有人受伤的情况下，他最多能有多少个枕头？

## 说明/提示
在第一个例子中，弗罗多最多能有两个枕头。在这种情况下，他可以给第一张床上的霍比特人两个枕头，给第三张和第四张床上的霍比特人各一个枕头。
在第二个例子中，弗罗多最多能拿四个枕头，给其他每个人三个枕头。
在第三个例子中，弗罗多可以拿三个枕头，给中间床上的霍比特人两个枕头，给第三张床上的霍比特人一个枕头。

## 样例 #1
### 输入
```
4 6 2
```
### 输出
```
2
```

## 样例 #2
### 输入
```
3 10 3
```
### 输出
```
4
```

## 样例 #3
### 输入
```
3 6 1
```
### 输出
```
3
```

### 算法分类
二分

### 综合分析与结论
所有题解都采用二分弗罗多的枕头数，并结合贪心构造等差数列来解决问题。思路核心在于通过二分查找确定弗罗多可能的最大枕头数，同时利用贪心策略保证相邻霍比特人枕头数差不超1且总数不超\(m\)。难点在于如何优化计算总枕头数的过程，避免超时。各题解都通过等差数列求和公式优化，将时间复杂度从\(\Theta (n \log m)\)降至\(\Theta(\log m)\)。

### 所选的题解
- **作者：tallnut (5星)**
    - **关键亮点**：思路清晰，先给出TLE代码并分析复杂度，再通过等差数列公式优化，还提及可进一步优化二分上界。
    - **个人心得**：分析出暴力代码复杂度会爆，从而想到用等差数列公式优化。
    - **重点代码 - 核心实现思想**：通过`sum`函数计算等差数列和，`check`函数中根据弗罗多位置及枕头数，利用等差数列公式计算总枕头数并判断是否满足条件。
```cpp
//计算 l+(l+1)+...+r
ull sum(ull l,ull r) { return ((l + r) * (r - l + 1)) >> 1; }
bool check(int x)
{
    ull tmpsum = x;
    ull i = k - 1,j = x - 1;
    if (j >= i) tmpsum += sum(j - i + 1,j);
    else tmpsum += (sum(1,j) + (i - j));

    i = n - k;
    j = x - 1;
    if (j >= i) tmpsum += sum(j - i + 1,j);
    else tmpsum += (sum(1,j) + (i - j));
    return tmpsum <= m;
}
```
- **作者：ModestCoder_ (4星)**
    - **关键亮点**：代码简洁，直接利用等差数列求和计算，逻辑清晰。
    - **重点代码 - 核心实现思想**：`check`函数中根据弗罗多枕头数`mid`，通过条件判断分别计算左右两侧的枕头总数并求和，判断是否不超过\(m\)。
```cpp
bool check(LL mid){
    LL x = k + mid - 1, sum = 0;
    if (x > n) sum += (mid + mid - n + k) * (n - k + 1) / 2; else
    sum += (mid + 1) * mid / 2 + n - k - mid + 1;
    x = k - mid + 1;
    if (x < 1) sum += (mid + mid - k) * (k - 1) / 2; else
    sum += (mid - 1) * mid / 2 + k - mid;
    return sum <= m;
}
```
- **作者：_JellyFish_ (4星)**
    - **关键亮点**：通过注释给出具体序列示例辅助理解，代码结构清晰。
    - **重点代码 - 核心实现思想**：`Cnt`函数计算从1到`num`的序列和，`check`函数根据弗罗多枕头数`x`，分情况计算左右两侧枕头数并求和与\(m\)比较。
```cpp
int Cnt(int num){//Cnt(num)表示从1到num的序列和 
    return num*(num+1)/2;
}
int check(int x){
    int lsum=0,rsum=0;
    if(x>L)lsum=x*L-Cnt(L);
    else lsum=Cnt(x-1)+(L-x+1);
    if(x>R)rsum=x*R-Cnt(R);
    else rsum=Cnt(x-1)+(R-x+1);
    return lsum+rsum+x;
}
```

### 最优关键思路或技巧
1. **二分查找**：通过二分弗罗多的枕头数，快速缩小搜索范围，找到满足条件的最大值。
2. **贪心构造等差数列**：以弗罗多为中心向两边构造公差为1的等差数列分配枕头，保证总枕头数最少且满足相邻差不超1的条件，利用等差数列求和公式优化计算过程。

### 可拓展思路
同类型题常围绕资源分配，在满足一定限制条件下求某一元素的最值。类似算法套路为通过二分答案结合贪心策略解决，关键在于分析限制条件并利用数学方法优化计算。

### 洛谷推荐题目
1. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：二分答案，贪心判断。
2. [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：同样是二分答案与贪心结合的题目。
3. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：通过二分答案解决数列分段问题。 

---
处理用时：61.38秒
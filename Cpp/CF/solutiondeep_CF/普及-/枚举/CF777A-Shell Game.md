# 题目信息

# Shell Game

## 题目描述

Bomboslav likes to look out of the window in his room and watch lads outside playing famous shell game. The game is played by two persons: operator and player. Operator takes three similar opaque shells and places a ball beneath one of them. Then he shuffles the shells by swapping some pairs and the player has to guess the current position of the ball.

Bomboslav noticed that guys are not very inventive, so the operator always swaps the left shell with the middle one during odd moves (first, third, fifth, etc.) and always swaps the middle shell with the right one during even moves (second, fourth, etc.).

Let's number shells from $ 0 $ to $ 2 $ from left to right. Thus the left shell is assigned number $ 0 $ , the middle shell is $ 1 $ and the right shell is $ 2 $ . Bomboslav has missed the moment when the ball was placed beneath the shell, but he knows that exactly $ n $ movements were made by the operator and the ball was under shell $ x $ at the end. Now he wonders, what was the initial position of the ball?

## 说明/提示

In the first sample, the ball was initially placed beneath the middle shell and the operator completed four movements.

1. During the first move operator swapped the left shell and the middle shell. The ball is now under the left shell.
2. During the second move operator swapped the middle shell and the right one. The ball is still under the left shell.
3. During the third move operator swapped the left shell and the middle shell again. The ball is again in the middle.
4. Finally, the operators swapped the middle shell and the right shell. The ball is now beneath the right shell.

## 样例 #1

### 输入

```
4
2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1
1
```

### 输出

```
0
```

# AI分析结果

### 题目翻译
# 贝壳游戏

## 题目描述
邦博斯拉夫喜欢在他房间里望着窗外，看外面的小伙子们玩著名的贝壳游戏。这个游戏由两个人玩：操作员和玩家。操作员拿出三个相似的不透明贝壳，把一个球放在其中一个下面。然后他通过交换一些贝壳对来打乱它们的顺序，玩家必须猜出球当前的位置。

邦博斯拉夫注意到那些人不太有创意，所以操作员在奇数移动（第一次、第三次、第五次等）时总是交换左边的贝壳和中间的贝壳，在偶数移动（第二次、第四次等）时总是交换中间的贝壳和右边的贝壳。

让我们从左到右将贝壳编号为 $0$ 到 $2$。因此，左边的贝壳编号为 $0$，中间的贝壳编号为 $1$，右边的贝壳编号为 $2$。邦博斯拉夫错过了球被放在贝壳下面的那一刻，但他知道操作员正好进行了 $n$ 次移动，并且球最后在编号为 $x$ 的贝壳下面。现在他想知道，球最初的位置是哪里？

## 说明/提示
在第一个样例中，球最初被放在中间的贝壳下面，操作员完成了四次移动。
1. 在第一次移动中，操作员交换了左边的贝壳和中间的贝壳。现在球在左边的贝壳下面。
2. 在第二次移动中，操作员交换了中间的贝壳和右边的贝壳。球仍然在左边的贝壳下面。
3. 在第三次移动中，操作员再次交换了左边的贝壳和中间的贝壳。球又回到了中间。
4. 最后，操作员交换了中间的贝壳和右边的贝壳。现在球在右边的贝壳下面。

## 样例 #1
### 输入
```
4
2
```
### 输出
```
1
```

## 样例 #2
### 输入
```
1
1
```
### 输出
```
0
```

### 综合分析与结论
这些题解的核心思路都是利用操作的周期性来简化问题，因为经过分析可知每6次操作后球的位置会回到初始状态，所以可以将操作次数 $n$ 对6取模。各题解的主要区别在于实现方式：
- **暴力枚举**：通过大量的`if`语句列举出 $n\%6$ 后每种情况对应的初始位置。
- **数组预处理**：将6种可能的情况存储在二维数组中，根据 $n\%6$ 和最终位置直接查找初始位置。
- **位运算模拟**：利用异或运算模拟交换过程，逆向操作得到初始位置。
- **循环模拟**：模拟 $n$ 次交换过程，但由于 $n$ 可能很大，这种方法会超时。

### 所选题解
- **作者：_YRH_（5星）**
    - **关键亮点**：思路清晰，代码简洁，通过预处理6种可能情况的二维数组，直接根据 $n\%6$ 和最终位置输出初始位置，可读性强。
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int i,j,k,m,n;
int a[101][101]={{0,1,2},{1,0,2},{1,2,0},{2,1,0},{2,0,1},{0,2,1},{0,1,2}};//预处理6种可能情况

int main(){
    scanf("%d%d",&n,&m);//输入
    n%=6;//每6个一循环
    printf("%d",a[n][m]);//输出
    return 0;
}
```
- **作者：nonanalyzer（5星）**
    - **关键亮点**：采用逆向思维，用位运算模拟交换过程，代码简洁高效，只需两个变量，不使用额外的数组存储所有情况，节省内存。
```cpp
#include<cstdio>
int n,x;
int main(){
    for(scanf("%d%d",&n,&x),n%=6;n;--n) n&1?(x^2?x^=1:x):(x?x^=3:x);
    return printf("%d\n",x),0;
}
```
- **作者：艾恩葛朗特（4星）**
    - **关键亮点**：使用快读提高输入效率，通过定义二维数组存储6种情况，根据 $n\%6$ 和最终位置输出初始位置，代码结构清晰。
```cpp
#include<cstdio>
#include<string>
using namespace std;

const int a[6][3]={{0,1,2},{1,0,2},{1,2,0},{2,1,0},{2,0,1},{0,2,1}};//表越大，分越多 
int n,m;

int read()//快读 
{
    int x = 0, f = 1;
    char ch = getchar();
    for (;!isdigit(ch); ch = getchar())
        if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar())
        x = x * 10 + ch - '0';
    return x * f;
}

int main()
{
    n=read();
    m=read();
    printf("%d",a[n%6][m]);//6个一个循环，所以n%6 
    return 0;
}
```

### 最优关键思路或技巧
- 发现操作的周期性，将操作次数 $n$ 对6取模，大大减少计算量。
- 利用位运算模拟交换过程，代码简洁且节省内存。
- 预处理所有可能的情况，存储在数组中，通过数组索引直接查找结果，提高效率。

### 拓展思路
同类型题可能会有不同的操作规则和周期，解题的关键在于找出操作的规律和周期，然后利用取模运算简化问题。类似的算法套路还有周期数列、循环节问题等。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：通过模拟和逆向思维解决问题。
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：需要找出操作的规律，利用数组进行标记。
3. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：通过排序和双指针法解决问题，也需要一定的思维技巧。

### 个人心得摘录与总结
- **作者：nonanalyzer**：提到别的大佬都是正着模拟，自己打算另辟蹊径逆向操作，怕重复解法过不了审核。总结：在解题时可以尝试不同的思路和方法，避免与他人解法雷同。
- **作者：World_Creater**：指出用 $O(N)$ 的模拟方法会超时，出题人太毒瘤。总结：在解题时要考虑算法的时间复杂度，对于数据范围较大的题目，需要寻找更优的解法。

---
处理用时：33.78秒
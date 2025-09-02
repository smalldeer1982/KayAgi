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
### Shell Game

#### 题目描述
Bomboslav喜欢在房间里望着窗外，看外面的小伙子们玩著名的贝壳游戏。这个游戏由两个人玩：操作者和玩家。操作者拿出三个相似的不透明贝壳，把一个球放在其中一个下面。然后他通过交换一些贝壳对来打乱顺序，玩家需要猜出球当前的位置。

Bomboslav注意到这些人不太有创意，所以操作者在奇数步（第一步、第三步、第五步等）总是交换左边的贝壳和中间的贝壳，在偶数步（第二步、第四步等）总是交换中间的贝壳和右边的贝壳。

我们从左到右将贝壳编号为 $0$ 到 $2$。因此，左边的贝壳编号为 $0$，中间的贝壳编号为 $1$，右边的贝壳编号为 $2$。Bomboslav错过了球被放在贝壳下面的那一刻，但他知道操作者正好进行了 $n$ 次移动，并且球最后在编号为 $x$ 的贝壳下面。现在他想知道，球最初的位置在哪里？

#### 说明/提示
在第一个样例中，球最初放在中间的贝壳下面，操作者完成了四次移动。
1. 在第一次移动中，操作者交换了左边的贝壳和中间的贝壳。现在球在左边的贝壳下面。
2. 在第二次移动中，操作者交换了中间的贝壳和右边的贝壳。球仍然在左边的贝壳下面。
3. 在第三次移动中，操作者再次交换了左边的贝壳和中间的贝壳。球又回到了中间。
4. 最后，操作者交换了中间的贝壳和右边的贝壳。现在球在右边的贝壳下面。

#### 样例 #1
##### 输入
```
4
2
```
##### 输出
```
1
```

#### 样例 #2
##### 输入
```
1
1
```
##### 输出
```
0
```

### 综合分析与结论
这些题解的核心思路都是利用游戏操作的周期性（每6次操作一循环）来解决问题，主要区别在于实现方式。
- **暴力枚举**：通过大量的`if`语句对每种可能的操作次数和最终位置组合进行判断，如The_Power_of_Pigeon的题解。
- **数组预处理**：将6种可能的情况存储在二维数组中，根据操作次数取模后的结果和最终位置直接从数组中获取初始位置，如_YRH_、艾恩葛朗特、CobaltChloride等的题解。
- **模拟操作**：通过循环模拟操作过程，根据操作次数的奇偶性交换贝壳位置，如大头菜赛高！、opened、至成天下的题解。
- **位运算模拟**：利用异或运算模拟贝壳交换，从最终位置倒推初始位置，如nonanalyzer的题解。

### 高评分题解
- **_YRH_（4星）**
    - **关键亮点**：思路清晰，通过预处理数组存储6种可能情况，代码简洁易懂，利用取模操作处理循环。
    - **核心代码**：
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int i,j,k,m,n;
int a[101][101]={{0,1,2},{1,0,2},{1,2,0},{2,1,0},{2,0,1},{0,2,1},{0,1,2}};

int main(){
    scanf("%d%d",&n,&m);
    n%=6;
    printf("%d",a[n][m]);
    return 0;
}
```
- **nonanalyzer（4星）**
    - **关键亮点**：采用倒推思路，使用位运算模拟贝壳交换，代码简洁高效，节省内存。
    - **核心代码**：
```cpp
#include<cstdio>
int n,x;
int main(){
    for(scanf("%d%d",&n,&x),n%=6;n;--n) n&1?(x^2?x^=1:x):(x?x^=3:x);
    return printf("%d\n",x),0;
}
```
- **艾恩葛朗特（4星）**
    - **关键亮点**：使用快读优化输入，通过预处理二维数组解决问题，代码结构清晰。
    - **核心代码**：
```cpp
#include<cstdio>
#include<string>
using namespace std;

const int a[6][3]={{0,1,2},{1,0,2},{1,2,0},{2,1,0},{2,0,1},{0,2,1}};
int n,m;

int read()
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
    printf("%d",a[n%6][m]);
    return 0;
}
```

### 最优关键思路或技巧
- 发现操作的周期性，通过取模将问题简化为6种情况，降低时间复杂度。
- 利用位运算模拟贝壳交换，代码简洁且节省内存。

### 拓展思路
同类型题目可能涉及不同的交换规则或更多的元素，解题关键依然是寻找操作的周期性和规律，可通过模拟操作或数学推导来解决。

### 洛谷相似题目推荐
- P1003 [铺地毯](https://www.luogu.com.cn/problem/P1003)：需要根据一定规则处理二维平面上的元素覆盖问题，可通过模拟操作求解。
- P1047 [校门外的树](https://www.luogu.com.cn/problem/P1047)：涉及区间操作，可通过标记数组模拟操作过程。
- P1094 [纪念品分组](https://www.luogu.com.cn/problem/P1094)：需要根据一定规则对元素进行分组，可通过排序和模拟分组过程解决。

### 个人心得摘录与总结
- **nonanalyzer**：提到别的大佬多是正着模拟，自己采用倒推思路，担心重复解法过不了审核。总结：在解题时可尝试不同思路，避免与他人解法雷同。
- **World_Creater**：指出用模拟方法会TLE，出题人毒瘤。总结：在解题时要考虑时间复杂度，对于大数据量的题目，需寻找更优解法。 

---
处理用时：34.38秒
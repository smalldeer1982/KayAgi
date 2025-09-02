# 题目信息

# Weird Game

## 题目描述

Yaroslav, Andrey and Roman can play cubes for hours and hours. But the game is for three, so when Roman doesn't show up, Yaroslav and Andrey play another game.

Roman leaves a word for each of them. Each word consists of $ 2·n $ binary characters "0" or "1". After that the players start moving in turns. Yaroslav moves first. During a move, a player must choose an integer from 1 to $ 2·n $ , which hasn't been chosen by anybody up to that moment. Then the player takes a piece of paper and writes out the corresponding character from his string.

Let's represent Yaroslav's word as $ s=s_{1}s_{2}...\ s_{2n} $ . Similarly, let's represent Andrey's word as $ t=t_{1}t_{2}...\ t_{2n} $ . Then, if Yaroslav choose number $ k $ during his move, then he is going to write out character $ s_{k} $ on the piece of paper. Similarly, if Andrey choose number $ r $ during his move, then he is going to write out character $ t_{r} $ on the piece of paper.

The game finishes when no player can make a move. After the game is over, Yaroslav makes some integer from the characters written on his piece of paper (Yaroslav can arrange these characters as he wants). Andrey does the same. The resulting numbers can contain leading zeroes. The person with the largest number wins. If the numbers are equal, the game ends with a draw.

You are given two strings $ s $ and $ t $ . Determine the outcome of the game provided that Yaroslav and Andrey play optimally well.

## 样例 #1

### 输入

```
2
0111
0001
```

### 输出

```
First
```

## 样例 #2

### 输入

```
3
110110
001001
```

### 输出

```
First
```

## 样例 #3

### 输入

```
3
111000
000111
```

### 输出

```
Draw
```

## 样例 #4

### 输入

```
4
01010110
00101101
```

### 输出

```
First
```

## 样例 #5

### 输入

```
4
01100000
10010011
```

### 输出

```
Second
```

# AI分析结果

### 题目内容
# 奇怪的游戏

## 题目描述
雅罗斯拉夫、安德烈和罗曼可以玩骰子玩上好几个小时。但这个游戏是三个人玩的，所以当罗曼不来的时候，雅罗斯拉夫和安德烈就玩另一个游戏。

罗曼给他们每人留了一个单词。每个单词由 $2·n$ 个二进制字符“0”或“1”组成。之后，玩家们开始轮流行动。雅罗斯拉夫先行动。在一轮行动中，玩家必须从1到 $2·n$ 中选择一个之前任何人都没有选过的整数。然后，玩家拿一张纸，写下他的字符串中对应的字符。

我们将雅罗斯拉夫的单词表示为 $s = s_{1}s_{2}... s_{2n}$ 。同样，我们将安德烈的单词表示为 $t = t_{1}t_{2}... t_{2n}$ 。那么，如果雅罗斯拉夫在他的回合中选择了数字 $k$ ，那么他将在纸上写下字符 $s_{k}$ 。同样，如果安德烈在他的回合中选择了数字 $r$ ，那么他将在纸上写下字符 $t_{r}$ 。

游戏在没有玩家可以行动时结束。游戏结束后，雅罗斯拉夫用写在纸上的字符组成一个整数（雅罗斯拉夫可以随意排列这些字符）。安德烈也做同样的事情。得到的数字可以包含前导零。数字最大的人获胜。如果数字相等，游戏以平局结束。

给定两个字符串 $s$ 和 $t$ 。假设雅罗斯拉夫和安德烈都玩得最优，确定游戏的结果。

## 样例 #1
### 输入
```
2
0111
0001
```
### 输出
```
First
```

## 样例 #2
### 输入
```
3
110110
001001
```
### 输出
```
First
```

## 样例 #3
### 输入
```
3
111000
000111
```
### 输出
```
Draw
```

## 样例 #4
### 输入
```
4
01010110
00101101
```
### 输出
```
First
```

## 样例 #5
### 输入
```
4
01100000
10010011
```
### 输出
```
Second
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，即优先选择对自己最有利的字符。具体要点如下：
 - **统计字符类型**：统计两个字符串中对应位置同为1、一个为1另一个为0的情况的数量。
 - **贪心选择**：优先选择两个字符串对应位置都为1的字符，这样既能增加自己的1的数量又能减少对方的1的数量；之后再选择自己字符串为1而对方为0的字符。
 - **结果判断**：通过比较两人最终获得1的数量来确定游戏结果。

各题解的主要区别在于实现细节和优化方式，例如对相同情况的处理方式，以及代码的简洁性和可读性。

### 所选的题解
 - **作者：pipi (赞：7) - 5星**
    - **关键亮点**：思路清晰，代码简洁，直接按照贪心策略统计各类字符数量并计算结果。
    - **重点代码**：
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int main(){
    int n,aa=0,bb=0,cc=0,dd=0,ee=0,sc1=0,sc2=0;
    scanf("%d",&n);
    bool a[2 * n],b[2 * n],l=0,k;
    n *= 2;
    for(int i=0;i<n;i++){
        scanf("%1ol",&a[i]);
        if(a[i])aa++;
    }
    for(int i=0;i<n;i++){
        scanf("%1ol",&b[i]);
        if(b[i])bb++;
    }
    for(int i=0;i<n;i++){
        if(a[i] == 1&&b[i] == 1) dd++;
        if(a[i] == 1&&b[i] == 0) cc++;
        if(a[i] == 0&&b[i] == 1) ee++;
    }
    for(int i=0;i<n;i++){
        if(dd){
            sc1++;
            dd--;
        }
        else if(cc){
            sc1++;
            cc--;
        }
        else if(ee){
            ee--;
        }
        if(dd){
            sc2++;
            dd--;
        }
        else if(ee){
            sc2++;
            ee--;
        }
        else if(cc){
            cc--;
        }
    }
    if(sc2 > sc1) printf("Second");
    if(sc1 > sc2) printf("First");
    if(sc1 == sc2) printf("Draw");
} 
```
    - **核心实现思想**：先统计出两个字符串中对应位置同为1（dd）、第一个字符串为1第二个为0（cc）、第一个字符串为0第二个为1（ee）的数量，然后按照贪心策略轮流分配这些位置，最后比较两人获得1的数量得出结果。
 - **作者：ModestCoder_ (赞：2) - 4星**
    - **关键亮点**：将1分为两类分开讨论，逻辑较为清晰，代码简洁高效。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
#define maxn 2000010
using namespace std;
int n, a[maxn], b[maxn], s1, s2, s3;

int get(){
    char c = getchar();
    for (; c!= '0' && c!= '1'; c = getchar());
    return c == '1';
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= (n << 1); ++i) a[i] = get();
    for (int i = 1; i <= (n << 1); ++i) b[i] = get();
    for (int i = 1; i <= (n << 1); ++i)
        if (a[i] &&!b[i]) ++s1; else
        if (!a[i] && b[i]) ++s2; else 
        if (a[i] && b[i]) ++s3;
    if (s3 & 1) --s2;
    if (s1 > s2) puts("First"); else
    if (s2 > s1 + 1) puts("Second"); else puts("Draw");
    return 0;
}
```
    - **核心实现思想**：统计两类1（某一个位置上只有一行拥有1，某一个位置上两行都有1）的个数，对两行都有1的个数为奇数的情况进行特殊处理，然后比较两类1的数量关系得出结果。
 - **作者：yu__xuan (赞：1) - 4星**
    - **关键亮点**：详细阐述选数策略，代码实现与思路紧密结合，易于理解。
    - **重点代码**：
```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>

int n, ans1, ans2;
std::string s1, s2;

int main() {
    std::cin >> n >> s1 >> s2;
    int num = 0, num1 = 0, num2 = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (s1[i] == '1') ++num1;
        if (s2[i] == '1') ++num2;
        if (s1[i] == '1' && s1[i] == s2[i]) ++num;
    }
    bool flag = 0;
    int ans1 = 0, ans2 = 0, cnt = num;
    while(num) {
        if (!flag) {
            --num2;
            --num1;
            ++ans1;
            flag = 1;
        } 
        else {
            --num1;
            --num2;
            ++ans2;
            flag = 0;
        }
        num--;
    }
    while(cnt < 2 * n) {
        if (!flag) {
            if (num1) {
                --num1;
                ++ans1;
            }
            else {
                if (num2) --num2;
            }
            flag = 1;
        }
        else {
            if (num2) {
                --num2;
                ++ans2;
            }
            else {
                if (num1) --num1;
            }
            flag = 0;
        }
        ++cnt;
    }
    if (ans1 > ans2) puts("First");
    else if (ans1 < ans2) puts("Second");
    else puts("Draw");
    return 0;
}
```
    - **核心实现思想**：先统计两个字符串中1的总数以及对应位置同为1的数量，然后按照贪心策略，先处理对应位置同为1的情况，再处理剩余情况，通过标志位轮流给两人分配字符，最后比较两人获得1的数量得出结果。

### 最优关键思路或技巧
 - **贪心策略**：优先选择对自己最有利的位置，即两个字符串对应位置都为1的字符，这是解决本题的核心思路。
 - **分类统计**：将字符情况进行分类统计，如分为两个字符串对应位置同为1、一个为1另一个为0的情况，便于后续按照贪心策略处理。

### 同类型题或类似算法套路拓展
同类型题通常是博弈类的贪心问题，类似算法套路是分析每个选择对双方的影响，找到最优的选择策略，优先选择对自己收益最大且对对手收益最小的选项。

### 洛谷相似题目推荐
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937)
 - [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

### 个人心得摘录与总结
无。 

---
处理用时：87.89秒
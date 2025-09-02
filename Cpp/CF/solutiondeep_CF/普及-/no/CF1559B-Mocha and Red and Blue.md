# 题目信息

# Mocha and Red and Blue

## 题目描述

As their story unravels, a timeless tale is told once again...

Shirahime, a friend of Mocha's, is keen on playing the music game Arcaea and sharing Mocha interesting puzzles to solve. This day, Shirahime comes up with a new simple puzzle and wants Mocha to solve them. However, these puzzles are too easy for Mocha to solve, so she wants you to solve them and tell her the answers. The puzzles are described as follow.

There are $ n $ squares arranged in a row, and each of them can be painted either red or blue.

Among these squares, some of them have been painted already, and the others are blank. You can decide which color to paint on each blank square.

Some pairs of adjacent squares may have the same color, which is imperfect. We define the imperfectness as the number of pairs of adjacent squares that share the same color.

For example, the imperfectness of "BRRRBBR" is $ 3 $ , with "BB" occurred once and "RR" occurred twice.

Your goal is to minimize the imperfectness and print out the colors of the squares after painting.

## 说明/提示

In the first test case, if the squares are painted "BRRBRBR", the imperfectness is $ 1 $ (since squares $ 2 $ and $ 3 $ have the same color), which is the minimum possible imperfectness.

## 样例 #1

### 输入

```
5
7
?R???BR
7
???R???
1
?
1
B
10
?R??RB??B?```

### 输出

```
BRRBRBR
BRBRBRB
B
B
BRRBRBBRBR```

# AI分析结果

### 题目内容
#### Mocha与红蓝颜色
#### 题目描述
随着她们的故事展开，一个永恒的传说再次被诉说……

紫苑，Mocha的一位朋友，热衷于玩音乐游戏《Arcaea》，并喜欢和Mocha分享有趣的谜题来解答。这天，紫苑想出了一个新的简单谜题，想让Mocha来解答。然而，这些谜题对Mocha来说太容易解决了，所以她希望你能解答这些谜题并告诉她答案。谜题描述如下。

有\(n\)个正方形排成一排，每个正方形可以被涂成红色或蓝色。

在这些正方形中，有些已经被涂好了颜色，而其他的是空白的。你可以决定在每个空白正方形上涂什么颜色。

一些相邻的正方形对可能具有相同的颜色，这是不完美的。我们将不完美度定义为具有相同颜色的相邻正方形对的数量。

例如，“BRRRBBR”的不完美度是\(3\)，其中“BB”出现了一次，“RR”出现了两次。

你的目标是最小化不完美度，并输出涂完颜色后的正方形颜色。
#### 说明/提示
在第一个测试用例中，如果正方形被涂成“BRRBRBR”，不完美度是\(1\)（因为第\(2\)个和第\(3\)个正方形颜色相同），这是最小可能的不完美度。
#### 样例 #1
##### 输入
```
5
7
?R???BR
7
???R???
1
?
1
B
10
?R??RB??B?
```
##### 输出
```
BRRBRBR
BRBRBRB
B
B
BRRBRBBRBR
```
• **算法分类**：贪心
• **综合分析与结论**：这些题解主要围绕如何通过合理策略填充字符串中的`?`，以最小化相邻字符相同的对数。多数题解采用贪心策略，即从已确定字符处向两侧交替填充`R`和`B`。部分题解还考虑了全`?`字符串的特殊情况，直接交替填充。少数题解使用动态规划，通过状态转移方程计算每个位置填`R`或`B`的最小不完美度。贪心策略思路和实现相对简单，动态规划虽思路稍复杂，但理论上能更全面严谨地求解。
• **所选的题解**
  - **作者：SpeedStar (5星)**
    - **关键亮点**：思路清晰简洁，代码实现高效。先判断字符串是否全为`?`，是则直接交替填充；否则找到首个非`?`字符，从该位置向两侧扫描填充，逻辑清晰。
    - **重点代码**：
```cpp
if (cnt == n) {
    rep(i, n) s[i] = i % 2 == 0? 'R' : 'B';
}
else {
    int i = 0;
    while (s[i] == '?') i++;
    drep(j, i) s[j] = s[j + 1] == 'R'? 'B' : 'R';
    while (i!= n) {
        int j = i + 1;
        while (j!= n and s[j] == '?') j++;
        srep(k, i + 1, j) s[k] = s[k - 1] == 'R'? 'B' : 'R';
        i = j;
    }
}
```
    - **核心实现思想**：若全为`?`，按奇偶位交替填充；否则，先找到首个非`?`字符，从其左侧开始，每个`?`填充为右侧相邻字符的相反颜色；再从该位置向右扫描，每次遇到下一个非`?`字符前，将中间的`?`填充为左侧相邻字符的相反颜色。
  - **作者：anideahe (4星)**
    - **关键亮点**：采用动态规划方法，通过状态转移方程全面考虑每个位置填`R`或`B`的情况，理论上能准确求出最小不完美度及对应方案。
    - **重点代码**：
```cpp
for(int i=1;i<=n;i=-~i){
    int j=get(f[i-1][1]+1,f[i-1][0],i-1);
    int k=get(f[i-1][1],f[i-1][0]+1,i-1);
    if(s[i]!='B'){
        f[i][1]=j;
        if(j==f[i-1][0]) g[i][1]=0;
        else g[i][1]=1;
    }
    if(s[i]!='R'){
        f[i][0]=k;
        if(k==f[i-1][1]) g[i][0]=1;
        else g[i][0]=0;
    }
}
```
    - **核心实现思想**：定义`f(i,0/1)`表示第`i`个位置为`B`/`R`时的最小不完美度，`g(i,0/1)`记录转移来源。通过状态转移方程，结合当前位置和前一个位置可填字符情况，计算并更新每个位置的最小不完美度及转移路径，最后倒序扫描得出最佳方案。
  - **作者：Leasier (4星)**
    - **关键亮点**：思路直观，先处理全`?`情况，再针对非全`?`字符串，从首个非`?`字符向两侧交替填充，通过简单分析证明方案正确性。
    - **重点代码**：
```cpp
while (j <= n && s[j] == '?') j++;
for (int k = j - 1; k >= 1; k--){
    s[k] = s[k + 1] == 'B'? 'R' : 'B';
}
for (; j <= n; j++){
    if (s[j] == '?') s[j] = s[j - 1] == 'B'? 'R' : 'B';
}
```
    - **核心实现思想**：先找到首个非`?`字符，从其左侧开始，每个`?`填充为右侧相邻字符的相反颜色；再从该位置向右扫描，遇到`?`则填充为左侧相邻字符的相反颜色。
• **最优关键思路或技巧**：贪心策略是较优选择，从已确定颜色的字符向两侧交替填充`R`和`B`，能有效最小化相邻字符相同对数，实现简单且高效。此方法利用了问题的局部最优可导致全局最优的性质。
• **拓展**：此类题目属于字符串构造与优化问题，通常可通过贪心策略解决。类似套路是分析局部最优情况，并证明其能推广到全局最优。例如在处理其他字符填充、排列优化等问题时，也可尝试从局部出发找规律。
• **推荐题目**：
  - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过合理排序实现贪心策略，与本题类似，需分析局部最优以达全局最优。
  - [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及策略选择与优化，可尝试贪心思路，与本题在寻找最优解思路上有相似处。
  - [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)：字符串相关问题，通过贪心或其他优化策略解决，锻炼字符串处理与优化能力，与本题有一定相关性。
• **个人心得**：无 

---
处理用时：79.95秒
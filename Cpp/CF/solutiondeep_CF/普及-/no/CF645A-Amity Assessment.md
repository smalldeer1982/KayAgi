# 题目信息

# Amity Assessment

## 题目描述

Bessie the cow and her best friend Elsie each received a sliding puzzle on Pi Day. Their puzzles consist of a $ 2×2 $ grid and three tiles labeled 'A', 'B', and 'C'. The three tiles sit on top of the grid, leaving one grid cell empty. To make a move, Bessie or Elsie can slide a tile adjacent to the empty cell into the empty cell as shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF645A/dea7f0e6f6bd920a326a8e3da7a33cbf3667be5d.png)In order to determine if they are truly Best Friends For Life (BFFLs), Bessie and Elsie would like to know if there exists a sequence of moves that takes their puzzles to the same configuration (moves can be performed in both puzzles). Two puzzles are considered to be in the same configuration if each tile is on top of the same grid cell in both puzzles. Since the tiles are labeled with letters, rotations and reflections are not allowed.

## 说明/提示

The solution to the first sample is described by the image. All Bessie needs to do is slide her 'A' tile down.

In the second sample, the two puzzles can never be in the same configuration. Perhaps Bessie and Elsie are not meant to be friends after all...

## 样例 #1

### 输入

```
AB
XC
XB
AC
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
AB
XC
AC
BX
```

### 输出

```
NO
```

# AI分析结果

【题目内容（中文重写）】
# Amity Assessment

## 题目描述
奶牛贝西（Bessie）和她最好的朋友埃尔西（Elsie）在圆周率日（Pi Day）各收到了一个滑动拼图。她们的拼图由一个 $2×2$ 的网格和三个标有 'A'、'B' 和 'C' 的瓷砖组成。这三个瓷砖放在网格上，留下一个网格单元格为空。为了移动，贝西或埃尔西可以将与空单元格相邻的瓷砖滑入空单元格，如下所示：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF645A/dea7f0e6f6bd920a326a8e3da7a33cbf3667be5d.png)

为了确定她们是否真的是一生的挚友（BFFLs），贝西和埃尔西想知道是否存在一系列的移动，能使她们的拼图达到相同的配置（在两个拼图中都可以进行移动）。如果每个瓷砖在两个拼图中都位于相同的网格单元格上，则认为两个拼图处于相同的配置。由于瓷砖标有字母，不允许旋转和反射。

## 说明/提示
第一个样例的解决方案如图所示。贝西只需要将她的 'A' 瓷砖向下滑动即可。

在第二个样例中，两个拼图永远无法达到相同的配置。也许贝西和埃尔西终究不是注定的朋友……

## 样例 #1
### 输入
```
AB
XC
XB
AC
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
AB
XC
AC
BX
```
### 输出
```
NO
```

【算法分类】
模拟

【综合分析与结论】
这些题解主要围绕判断能否通过规定的滑动操作使两个 $2×2$ 拼图达到相同配置展开。思路大致可分为两类：一类是直接模拟滑动过程，多次移动并检查是否与目标拼图相同；另一类是发现拼图中字母的顺时针（或逆时针）顺序在滑动过程中不变，通过比较顺序来判断。

|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|MZY666|用外层循环多次按同一种方法改变第一组数据，每次改变后判断是否与第二组数据相同|定义移动和判断的函数，循环移动并判断|确定移动规则和循环次数|3星|
|小之森夏音|模拟按同一方向（逆时针）滑动方格一中的方块，每次滑动后判断是否与方格二相同|使用循环和条件判断进行滑动和比较|确定滑动次数上限|2星|
|皮卡丘最萌|列举出所有可能的图形，判断是否有符合题意的|手动列出12种图形并逐一判断|图形列举的完整性|2星|
|liuyifan|判断两两间的可行性，根据结果输出|定义判断函数，比较两个拼图的判断结果|判断可行性的逻辑|3星|
|cyrxdzj|暴力模拟，找出空格，重复移动12次并判断|定义判断方阵是否一致的函数，按规则移动并判断|移动次数的确定和空格位置的更新|3星|
|SegTre|判断两个拼图的顺时针顺序是否为循环同构串|按顺时针顺序读取拼图，比较顺序|循环同构串的判断|4星|
|Farkas_W|判断三个字母 $A,B,C$ 之间的位置关系，比较顺时针方向 $A$ 的下一个字母|找出 $A$ 的位置，确定顺时针方向 $A$ 的下一个字母|位置关系的判断|3星|
|BF_AlphaShoot|比较不算 $\mathtt{X}$ 时顺时针方向上 $\mathtt{A,B,C}$ 的顺序|存储初始顺序和结果顺序，比较顺序|顺序的存储和比较|3星|
|_Legacy|判断两个方格的顺序是否相同|定义比较顺序的函数，制造顺序字符串并比较|顺序比较的实现|3星|

【所选题解】
- SegTre（4星）
  - 关键亮点：发现拼图中字母顺时针顺序不变的规律，通过比较顺时针顺序判断是否可达到相同配置，思路巧妙，代码简洁。
  - 重点代码：
```cpp
#include<cstdio>
#include<cctype>
using namespace std;
char s[4],s1[3],s2[3];
int main() {
    int p=0;
    for(int i=0;i<4;++i) while(!isalpha(s[i]=getchar())); //按照 0123 顺序读入 
    if(s[0]!='X') s1[p++]=s[0];
    if(s[1]!='X') s1[p++]=s[1];
    if(s[3]!='X') s1[p++]=s[3];
    if(s[2]!='X') s1[p++]=s[2]; // s1 存第一张图顺时针顺序，X 跳开 
    p=0;
    for(int i=0;i<4;++i) while(!isalpha(s[i]=getchar()));
    if(s[0]!='X') s2[p++]=s[0];
    if(s[1]!='X') s2[p++]=s[1];
    if(s[3]!='X') s2[p++]=s[3];
    if(s[2]!='X') s2[p++]=s[2];
    p=0;
    while(s1[0]!=s2[p]) p++;
    for(int i=0;i<3;++i)
        if(s1[i]!=s2[(i+p)%3]) { // 顺时针排列 0 ~ 2 ，2 过后还是 0 ——模 3 即可实现 
            printf("NO");
            return 0;
        }
    printf("YES");
    return 0;
}
```
核心实现思想：先按顺序读入两个拼图，提取出不含 'X' 的顺时针顺序存储在 `s1` 和 `s2` 中，然后找到 `s2` 中与 `s1[0]` 相同的位置，通过循环比较后续字母是否相同，利用取模操作实现循环比较。

【最优关键思路或技巧】
发现拼图中字母的顺时针（或逆时针）顺序在滑动过程中保持不变这一规律，将复杂的滑动模拟问题转化为简单的顺序比较问题，大大简化了判断过程。

【可拓展之处】
同类型题可能会有不同大小的网格或更多的拼图块，类似算法套路可应用于判断通过规定操作能否使两个状态达到一致的问题，关键在于找到操作过程中不变的特征进行比较。

【推荐题目】
1. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：通过回溯法模拟皇后的放置过程，判断是否满足条件。
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举和组合的方式选择数字，判断是否满足质数条件。
3. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：通过动态规划或搜索的方法模拟卒的移动过程，计算路径数量。

【个人心得】
部分题解提到可以通过玩类似的拼图小游戏来找规律，这说明在解决问题时可以通过实际操作来探索规律，帮助理解问题和找到解题思路。

---
处理用时：46.46秒
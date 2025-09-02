# 题目信息

# Playoff Tournament

## 题目描述

$ 2^k $ teams participate in a playoff tournament. The tournament consists of $ 2^k - 1 $ games. They are held as follows: first of all, the teams are split into pairs: team $ 1 $ plays against team $ 2 $ , team $ 3 $ plays against team $ 4 $ (exactly in this order), and so on (so, $ 2^{k-1} $ games are played in that phase). When a team loses a game, it is eliminated, and each game results in elimination of one team (there are no ties). After that, only $ 2^{k-1} $ teams remain. If only one team remains, it is declared the champion; otherwise, $ 2^{k-2} $ games are played: in the first one of them, the winner of the game " $ 1 $ vs $ 2 $ " plays against the winner of the game " $ 3 $ vs $ 4 $ ", then the winner of the game " $ 5 $ vs $ 6 $ " plays against the winner of the game " $ 7 $ vs $ 8 $ ", and so on. This process repeats until only one team remains.

For example, this picture describes the chronological order of games with $ k = 3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1535D/c7e451b61d4040a41b998ad855d9eabb637fb38d.png)Let the string $ s $ consisting of $ 2^k - 1 $ characters describe the results of the games in chronological order as follows:

- if $ s_i $ is 0, then the team with lower index wins the $ i $ -th game;
- if $ s_i $ is 1, then the team with greater index wins the $ i $ -th game;
- if $ s_i $ is ?, then the result of the $ i $ -th game is unknown (any team could win this game).

Let $ f(s) $ be the number of possible winners of the tournament described by the string $ s $ . A team $ i $ is a possible winner of the tournament if it is possible to replace every ? with either 1 or 0 in such a way that team $ i $ is the champion.

You are given the initial state of the string $ s $ . You have to process $ q $ queries of the following form:

- $ p $ $ c $ — replace $ s_p $ with character $ c $ , and print $ f(s) $ as the result of the query.

## 样例 #1

### 输入

```
3
0110?11
6
5 1
6 ?
7 ?
1 ?
5 ?
1 1```

### 输出

```
1
2
3
3
5
4```

# AI分析结果

### 题目翻译
# 季后赛锦标赛

## 题目描述
有 $2^k$ 支队伍参加一场季后赛锦标赛。该锦标赛由 $2^k - 1$ 场比赛组成，比赛按以下方式进行：首先，队伍被分成若干对：队伍 1 与队伍 2 比赛，队伍 3 与队伍 4 比赛（严格按照此顺序），依此类推（因此，在这一阶段会进行 $2^{k - 1}$ 场比赛）。当一支队伍输掉一场比赛时，它就会被淘汰，每场比赛都会淘汰一支队伍（不存在平局）。之后，就只剩下 $2^{k - 1}$ 支队伍。如果只剩下一支队伍，那么它就会被宣布为冠军；否则，会进行 $2^{k - 2}$ 场比赛：在其中的第一场比赛中，“1 对 2” 比赛的胜者与 “3 对 4” 比赛的胜者对决，然后 “5 对 6” 比赛的胜者与 “7 对 8” 比赛的胜者对决，依此类推。这个过程会一直重复，直到只剩下一支队伍。

例如，这张图片描述了 $k = 3$ 时比赛的时间顺序：
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1535D/c7e451b61d4040a41b998ad855d9eabb637fb38d.png)

设由 $2^k - 1$ 个字符组成的字符串 $s$ 按时间顺序描述比赛的结果，规则如下：
- 如果 $s_i$ 为 0，则编号较小的队伍赢得第 $i$ 场比赛；
- 如果 $s_i$ 为 1，则编号较大的队伍赢得第 $i$ 场比赛；
- 如果 $s_i$ 为?，则第 $i$ 场比赛的结果未知（任何一支队伍都可能赢得这场比赛）。

设 $f(s)$ 为字符串 $s$ 所描述的锦标赛中可能的获胜者数量。如果可以通过将每个? 替换为 1 或 0，使得队伍 $i$ 成为冠军，那么队伍 $i$ 就是锦标赛的一个可能获胜者。

你会得到字符串 $s$ 的初始状态。你需要处理 $q$ 个以下形式的查询：
- $p$ $c$ — 将 $s_p$ 替换为字符 $c$，并将 $f(s)$ 作为查询结果输出。

## 样例 #1
### 输入
```
3
0110?11
6
5 1
6 ?
7 ?
1 ?
5 ?
1 1
```
### 输出
```
1
2
3
3
5
4
```

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是将比赛过程抽象成二叉树结构，通过动态规划的方式来计算可能的获胜者数量。不同题解的主要区别在于对比赛编号的处理方式以及具体的实现细节。

- **思路对比**：大部分题解都采用了将比赛编号重新排序的方法，使得可以用线段树或类似线段树的方式来存储和更新信息。一些题解通过翻转字符串或重新编号来实现这一点。
- **算法要点**：设 $f_i$ 表示第 $i$ 场比赛可能的获胜者个数，根据比赛结果字符（0、1、?）进行状态转移。如果 $s_i$ 为 0，则 $f_i$ 等于右子节点的可能获胜者个数；如果 $s_i$ 为 1，则 $f_i$ 等于左子节点的可能获胜者个数；如果 $s_i$ 为?，则 $f_i$ 等于左右子节点的可能获胜者个数之和。
- **解决难点**：原比赛编号与线段树节点存储编号方式不同，需要通过重新编号或翻转字符串等方式解决。每次修改操作后，需要更新从修改节点到根节点路径上的所有节点的状态。

### 所选题解
- **作者：HoshizoraZ (赞：8)，4星**
  - **关键亮点**：思路清晰，详细阐述了如何通过改变比赛编号的存储方式来利用线段树求解问题，代码实现简洁明了。
- **作者：Ivan422 (赞：3)，4星**
  - **关键亮点**：指出淘汰制的树是二叉树，并通过将顺序倒过来以常规方式存储，使用动态规划记录每个点胜利的可能点，逻辑清晰。
- **作者：Xiphi (赞：0)，4星**
  - **关键亮点**：将比赛抽象成完全二叉树，给出了明确的状态转移式，并且解释了翻转原串的原因，代码实现较为简洁。

### 重点代码
#### HoshizoraZ 的代码
```cpp
void build(int i, int l, int r){
    if(l == r){
        ans[i] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
    if(s[i] == '0') ans[i] = ans[i << 1 | 1];
    if(s[i] == '1') ans[i] = ans[i << 1];
    if(s[i] == '?') ans[i] = ans[i << 1] + ans[i << 1 |1];
}
```
**核心实现思想**：递归构建线段树，根据比赛结果字符更新每个节点的可能获胜者个数。

#### Ivan422 的代码
```cpp
void rev(int p){
    if(p==0)return;
    if(idt(p)<=(1<<(k-1))){
        if(s[idt(p)]=='?')f[p]=2;
        else f[p]=1;        
    }else{
        if(s[idt(p)]=='?')f[p]=f[p*2]+f[p*2+1];
        if(s[idt(p)]=='0')f[p]=f[p*2+1];
        if(s[idt(p)]=='1')f[p]=f[p*2];
    }
    rev(p/2);
}
```
**核心实现思想**：递归更新节点状态，根据比赛结果字符计算每个节点的可能获胜者个数。

#### Xiphi 的代码
```cpp
void build(int p,int l,int r){
    if(l==r){
        tr[p]=1;
        return ;
    }
    int mid=l+r>>1;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
    if(s[p]=='0') tr[p]=tr[p<<1|1];
    else if(s[p]=='1') tr[p]=tr[p<<1];
    else if(s[p]=='?') tr[p]=tr[p<<1|1]+tr[p<<1];
}
```
**核心实现思想**：递归构建树，根据比赛结果字符更新每个节点的可能获胜者个数。

### 最优关键思路或技巧
- **重新编号**：将比赛编号重新排序，使其符合线段树或类似数据结构的存储方式，方便进行状态转移和更新。
- **动态规划**：通过定义状态 $f_i$ 表示第 $i$ 场比赛可能的获胜者个数，根据比赛结果字符进行状态转移，避免了重复计算。

### 拓展思路
同类型题或类似算法套路：
- 其他涉及二叉树结构的动态规划问题，如二叉树的路径问题、节点选择问题等。
- 具有递归性质的比赛或淘汰制问题，可通过类似的方法将其抽象成树结构进行求解。

### 推荐题目
- [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
- [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)

### 个人心得摘录与总结
- **Ryanhao**：提到自己的做法在树的存储上有点复杂，欢迎大佬研究更方便的做法。总结：在解题时要注意选择合适的数据结构和算法，避免不必要的复杂操作。

---
处理用时：59.26秒
# Logical Expression

## 题目描述

You are given a boolean function of three variables which is defined by its truth table. You need to find an expression of minimum length that equals to this function. The expression may consist of:

- Operation AND ('&', ASCII code 38)
- Operation OR ('|', ASCII code 124)
- Operation NOT ('!', ASCII code 33)
- Variables x, y and z (ASCII codes 120-122)
- Parentheses ('(', ASCII code 40, and ')', ASCII code 41)

If more than one expression of minimum length exists, you should find the lexicographically smallest one.

Operations have standard priority. NOT has the highest priority, then AND goes, and OR has the lowest priority. The expression should satisfy the following grammar:

E ::= E '|' T | T

T ::= T '&' F | F

F ::= '!' F | '(' E ')' | 'x' | 'y' | 'z'

## 说明/提示

The truth table for the second function:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913E/c3830892a1af029262c7cea8f026f08f9802d2de.png)

## 样例 #1

### 输入

```
4
00110011
00000111
11110000
00011111
```

### 输出

```
y
(y|z)&x
!x
x|y&z
```

# 题解

## 作者：dengyaotriangle (赞：5)

题意：有x,y,z三个变量,你要找到一个最短的逻辑表达式，使得对应每一个x,y,z的可能取值，表达式的值总为给定的值。（长度相同取字典序最小值）

每次给定一个二进制数，从左向右第 $i$ 位代表 $x,y,z$ 取000,001,010...时表达式的值

输入都是给的状压了，那这题显然是一个状压。

我们设一个表达式的"值"为$x,y,z$取000,001,010,...,111时的取值组成的二进制数（与题意相同）

我们考虑dp

设 $dp[i][j]$ 代表dp到第$i$层,值为$j$的最短表达式

显然有边界  
$dp[0][0\text{b}00001111]='x'$  
$dp[0][0\text{b}00110011]='y'$  
$dp[0][0\text{b}01010101]='z'$  

我们发现，人人为我的方法不太可行，考虑我为人人的做法

那么我们可以设计出如下转移:  
$dp[i][j]\rightarrow dp[i+1][j]$  
$'('+dp[i][j]+')'\rightarrow dp[i+1][j]$  
$'!'+dp[i][j]\rightarrow dp[i+1][255 \text{ xor } j]$  
$dp[i][j]+'|'+dp[i][k]\rightarrow dp[i+1][j\text{ or } k]$  
$dp[i][j]+'\&'+dp[i][k]\rightarrow dp[i+1][j\text{ and } k]$  

$j,k \in [0,255]$

（左侧的那坨都代表字符串拼接）

但这样做是有问题的，你会发现直接拼接可能导致一些运算优先级的混淆，比如$x|y$和$y|z$，如果我们对它们进行最后一项转移，那么就会变成$x|y\&y|z$，中间的与运算结合了两个y，这不是我们想要的结果，但相反，如果$x\&y$和$!z$进行这次转移却没有问题

我们考虑增加一维k

设 $dp[i][j][k]$ 代表dp到第$i$层,值为$j$，且优先级为$k$的最短表达式  
其中，我们对于一个表达式$S$定义优先级：  
如果$S$有一个没有在任何括号内的$'|'$字符，那么优先级为$0$  
否则，如果$S$有一个没有在任何括号内的$'\&'$字符，那么优先级为$1$  
否则，优先级为$2$

那么显然，单变量的优先级为$2$，故边界为

$dp[0][0\text{b}00001111][2]='x'$  
$dp[0][0\text{b}00110011][2]='y'$  
$dp[0][0\text{b}01010101][2]='z'$  

那么就可以放心地设计转移了  
$dp[i][j][k]\rightarrow dp[i+1][j][k]$，$j\in[0,255],k\in[0,2]$   
这一个是直接转移  

$'('+dp[i][j][k]+')'\rightarrow dp[i+1][j][2]$，$j\in[0,255],k\in[0,2]$   
这一个是加上括号，这样所有的都被包住了，优先级升至2

$'!'+dp[i][j][2]\rightarrow dp[i+1][255 \text{ xor } j][2]$，$j\in[0,255]$   
因为任何优先级小于2的表达式前面加一个!都会导致前面一部分与!结合，故只有2优先级的才可以

$dp[i][j1][k1]+'|'+dp[j2][k2]\rightarrow dp[i+1][j1\text{ or } j2][0]$，$j1,j2\in[0,255],k1\in[0,2],k2\in[1,2]$   
我们考虑如果给一个优先级等于0的后边加 | ，发现没有问题，而如果在前面加，则会导致前面一部分和前边的算式结合，导致混淆，故加在前面的必须优先级大于0，而后面的大于等于即可

$dp[i][j1][k1]+'\&'+dp[j2][k2]\rightarrow dp[i+1][j1\text{ and } j2][1]$，$j1,j2\in[0,255],k1\in[1,2],k2=2$   
同上，只不过与运算高一级

那么我们现在会转移了，只剩下一个问题：到底要dp多少层？

显然，我们发现，三个变量随便瞎那啥组合有很大概率很短地就组合出了想要的表达式，那么设成较小的数并没有问题，我这里取$10$，可以通过

所以就直接预处理，然后对于每次询问，输出即可

程序里的cerr会输出所有可能的表达式，看起来竟然很赏心悦目（？）

哦，还有关于0b表示二进制数这玩意好像老一点的编译器不能用，请谨慎模仿（
```cpp
#include<bits/stdc++.h>
//dengyaotriangle!
using namespace std;

const int maxn=(1<<8);
const int itn=10;

int n;
string dp[itn][maxn][3];

void upd(string& trg,string org){
    if(trg.empty())trg=org;
    else if(org.size()<trg.size())trg=org;
    else if(org<trg&&org.size()==trg.size())trg=org;
}

int main(){
    dp[0][0b00001111][2]='x';
    dp[0][0b00110011][2]='y';
    dp[0][0b01010101][2]='z';
    for(int i=0;i<itn-1;i++){
        for(int j=0;j<maxn;j++){
            if(!dp[i][j][0].empty())upd(dp[i+1][j][0],dp[i][j][0]);
            if(!dp[i][j][1].empty())upd(dp[i+1][j][1],dp[i][j][1]);
            if(!dp[i][j][2].empty())upd(dp[i+1][j][2],dp[i][j][2]);
            if(!dp[i][j][0].empty())upd(dp[i+1][j][2],"("+dp[i][j][0]+")");
            if(!dp[i][j][1].empty())upd(dp[i+1][j][2],"("+dp[i][j][1]+")");
            if(!dp[i][j][2].empty())upd(dp[i+1][j][2],"("+dp[i][j][2]+")");
            if(!dp[i][j][2].empty())upd(dp[i+1][0b11111111^j][2],"!"+dp[i][j][2]);
        }
        for(int j=0;j<maxn;j++){
            for(int k=0;k<maxn;k++){
                if(!dp[i][j][0].empty()&&!dp[i][k][1].empty())upd(dp[i+1][j|k][0],dp[i][j][0]+"|"+dp[i][k][1]);
                if(!dp[i][j][0].empty()&&!dp[i][k][2].empty())upd(dp[i+1][j|k][0],dp[i][j][0]+"|"+dp[i][k][2]);
                if(!dp[i][j][1].empty()&&!dp[i][k][1].empty())upd(dp[i+1][j|k][0],dp[i][j][1]+"|"+dp[i][k][1]);
                if(!dp[i][j][1].empty()&&!dp[i][k][2].empty())upd(dp[i+1][j|k][0],dp[i][j][1]+"|"+dp[i][k][2]);
                if(!dp[i][j][2].empty()&&!dp[i][k][1].empty())upd(dp[i+1][j|k][0],dp[i][j][2]+"|"+dp[i][k][1]);
                if(!dp[i][j][2].empty()&&!dp[i][k][2].empty())upd(dp[i+1][j|k][0],dp[i][j][2]+"|"+dp[i][k][2]);
                if(!dp[i][j][1].empty()&&!dp[i][k][2].empty())upd(dp[i+1][j&k][1],dp[i][j][1]+"&"+dp[i][k][2]);
                if(!dp[i][j][2].empty()&&!dp[i][k][2].empty())upd(dp[i+1][j&k][1],dp[i][j][2]+"&"+dp[i][k][2]);
            }
        }
    }
    for(int i=0;i<maxn;i++){
        string ans="";
        upd(ans,dp[itn-1][i][0]);
        upd(ans,dp[itn-1][i][1]);
        upd(ans,dp[itn-1][i][2]);
        cerr<<i<<':'<<ans<<'\n';
    }
    ios::sync_with_stdio(0);
    int t;
    cin>>t;
    while(t--){
        char f[10];
        cin>>f;
        int o=0;
        for(int i=0;i<8;i++) o=(o<<1|(f[i]-'0'));
        string ans="";
        upd(ans,dp[itn-1][o][0]);
        upd(ans,dp[itn-1][o][1]);
        upd(ans,dp[itn-1][o][2]);
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：chenxia25 (赞：3)

不请自来，这是 tourist 出的「hot tea」哦 %%%。

---

拒绝打表。我们考虑一个显然的 DP：$dp_i$ 表示 $i$ 被表示出来的最小字符串。转移的时候呢，由于我们需要知道被逻辑运算符连接的 $1\sim2 $ 个表达式分别需不需要加括号，我们需要知道这个表达式的最后一步的逻辑运算符的优先级和当前逻辑运算符的优先级的大小关系。于是不难想到在 DP 状态上再加一维表示最后一步逻辑运算符的优先级，分成三级，无符号和非符号是最高级。至此都非常自然吧。

然后这个 DP 显然是有后效性的。我们考虑这样一个方案：分成若干轮，每轮无后效性地用上一轮的结果来松弛本轮。而且这个一脸小清新样子，看起来不出几轮就能获得稳定状态，永远不会松弛成功。有些人就用打表了，这好吗，这不好。我使用的是卡时，卡了 $2\mathrm s$ 大约跑了 $5$ 次（一次的复杂度 $\mathrm O\!\left(3^22^{16}\right)$ 带大常数），得到了正确的结果。

最后输出就可以了，$n\leq 10000$ 是个幌子。

真就乱搞做题呗，**_[code](https://www.luogu.com.cn/paste/uztxga4f)_**。

---

但是正解不是乱搞，毕竟是 tourist 出的题。

看到有后效性最优化 DP，我们想到抽象成最短路模型。但这个 DP 的转移是依靠两个决策同时松弛的，无法转化为图。但是如果视最短路为特殊的有后效性最优化 DP 的话，我们可以使用最短路算法的核心思想来优化一般的有后效性最优化 DP。

可见上面那个乱搞就是 Bellman-Ford。我们考虑 Dijkstra，它的核心思想是，逐步把最短路数组确定化，每轮选出未确定的中最小的，那么有结论说它已经确定了，用它来松弛其他人，进入下一轮。

我们来考虑这个东西的证明，然后来试图转化到本题这个一般有后效性最优化 DP 这个广义的最短路。每轮中选出未确定中最小的来确定，注意到一个值已经被确定了当且仅当它的最短路的上一个（在 DP 中叫做最优决策）在之前被确定并且把别人松驰过了。然后我们假设最小的没被确定，那么它的最优决策没被确定，但这个最短路这条链是通向源点的，那么终究有一个更大的被确定了，那最短路怎么可能越跑越短呢（可见边权必须为正才能 Dijkstra）。

回到这题，我们考虑每次选出未确定的 DP 值中最小的来确定。那么它确实应该被确定当且仅当它的最优决策对的两个 DP 值都已经在之前被确定了。假设不成立，那么必有后面更大的确定 DP 值作为它的间接最优决策，这是不可能的。那么这样就是对的，复杂度 $\mathrm O\!\left(3^22^{16}\right)$，甚至不需要堆优化，因为在这个广义的图中有 $m=\mathrm O\!\left(n^2\right)$。

**_[code](https://www.luogu.com.cn/paste/ueo0p8wr)_**

---

以上。

---

## 作者：沉石鱼惊旋 (赞：3)

# 题目翻译

给定 $x=(00001111)_2,y=(00110011)_2,z=(01010101)_2$。

你有二元运算符『与』和『或』，以及一元运算符『取反』。

与：表示二进制下按位与，字符是 `&`。

或：表示二进制下按位或，字符是 `|`。

取反：表示二进制下按位取反，字符是 `!`。

优先级从大到小排列是：取反，与，或。

给出 $n(1\leq n\leq 10^4)$ 个询问，每次给出长度为 $8$ 的二进制串，求其在使用 $x,y,z$ 和以上三种操作后得到该二进制串的最优答案。

对于『最优答案』的解释：优先取长度小的，长度一样优先取字典序小的。

# 题目思路

首先，$n\leq 10^4$ 的数据范围是假的，只有 $256$ 个输入串。

二进制串改成十进制数状压也是显然的。

考虑设计 $f_i$ 表示凑到 $i$ 的『最优答案』。

但是因为优先级会有很多括号的事情，所以加入一位 $f_{i,k}$ 表示凑到 $i$ 当前优先级为 $k$ 得到的『最优答案』。

转移十分显然，这里从自己转移到别人比较方便，分两大类：

1. 一元运算符

那么就是给自己前面加上 `!` 即可。

2. 二元运算符

转移暴力枚举 $i,j\in [0,256)$，之后枚举 $i$ 和 $j$ 的优先级，再枚举两个二元运算符进行转移。

关于实现，这里不推荐大家写若干循环，我直接手动循环展开转移的。不然优先级加括号要判挺多东西。

但是，这个做法还有个问题。你转移一次不一定是对的啊。

然后你会发现，你一共 $255$ 个值的状态，其实状态很少，多跑几轮总能转移结束。那么你就类似图论最短路多跑几次，直到所有的“松弛操作”都没有进行再结束。

也就是说，状态设计成 $f_{r,i,k}$ 表示第 $r$ 轮转移凑到 $i$ 当前优先级为 $k$ 得到的『最优答案』。

实现的时候注意优先级问题要加括号！取『最优答案』的时候要注意不要从空串开始转移。关于转移次数，我转移了 $6$ 轮就过了。

# 完整代码

[CF submission 254456293](https://codeforces.com/contest/913/submission/254456293)

```cpp
#include <bits/stdc++.h>
using namespace std;
const int a[] = {0b00001111, 0b00110011, 0b01010101};
const char ch[] = {'x', 'y', 'z'};
const char op[] = {'|', '&', '!'}; // 低 ~ 高，单值 和 括号 也算 2 级，高级 外面可以套 低级
const int R = 6;
const int n = 1 << 8;
string Min(string &a, string &b) { return a.size() ^ b.size() ? (a.size() < b.size() ? a : b) : (a < b ? a : b); }
void chkmn(string &a, string b)
{
    if (a.empty())
        a = b;
    else
        a = Min(a, b);
}
int StB(string &s)
{
    int ret = 0;
    for (char c : s)
        ret = ret << 1 | c ^ '0';
    return ret;
}
int inv(int x) { return 0b11111111 ^ x; }
string f[R + 1][n][3];
string ans[n];
int t;
void solve()
{
    string s;
    cin >> s;
    cout << ans[StB(s)] << '\n';
}
int main()
{
    for (int i = 0; i < 3; i++)
        f[0][a[i]][2] = ch[i];
    for (int r = 0; r < R; r++)
    {
        // 单值修改
        for (int i = 0; i < n; i++)
        {
            // 继承原始
            if (!f[r][i][0].empty())
                chkmn(f[r + 1][i][0], f[r][i][0]);
            if (!f[r][i][1].empty())
                chkmn(f[r + 1][i][1], f[r][i][1]);
            if (!f[r][i][2].empty())
                chkmn(f[r + 1][i][2], f[r][i][2]);
            // 取反
            if (!f[r][i][0].empty())
                chkmn(f[r + 1][inv(i)][2], "!(" + f[r][i][0] + ")");
            if (!f[r][i][1].empty())
                chkmn(f[r + 1][inv(i)][2], "!(" + f[r][i][1] + ")");
            if (!f[r][i][2].empty())
                chkmn(f[r + 1][inv(i)][2], "!" + f[r][i][2]);
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // 0 | 0
                if (!f[r][i][0].empty() && !f[r][j][0].empty())
                    chkmn(f[r + 1][i | j][0], f[r][i][0] + "|" + f[r][j][0]);
                // 0 | 1
                if (!f[r][i][0].empty() && !f[r][j][1].empty())
                    chkmn(f[r + 1][i | j][0], f[r][i][0] + "|" + f[r][j][1]);
                // 0 | 2
                if (!f[r][i][0].empty() && !f[r][j][2].empty())
                    chkmn(f[r + 1][i | j][0], f[r][i][0] + "|" + f[r][j][2]);
                // 0 & 0
                if (!f[r][i][0].empty() && !f[r][j][0].empty())
                    chkmn(f[r + 1][i & j][1], "(" + f[r][i][0] + ")&(" + f[r][j][0] + ")");
                // 0 & 1
                if (!f[r][i][0].empty() && !f[r][j][1].empty())
                    chkmn(f[r + 1][i & j][1], "(" + f[r][i][0] + ")&" + f[r][j][1]);
                // 0 & 2
                if (!f[r][i][0].empty() && !f[r][j][2].empty())
                    chkmn(f[r + 1][i & j][1], "(" + f[r][i][0] + ")&" + f[r][j][2]);

                // 1 | 0
                if (!f[r][i][1].empty() && !f[r][j][0].empty())
                    chkmn(f[r + 1][i | j][0], f[r][i][1] + "|" + f[r][j][0]);
                // 1 | 1
                if (!f[r][i][1].empty() && !f[r][j][1].empty())
                    chkmn(f[r + 1][i | j][0], f[r][i][1] + "|" + f[r][j][1]);
                // 1 | 2
                if (!f[r][i][1].empty() && !f[r][j][2].empty())
                    chkmn(f[r + 1][i | j][0], f[r][i][1] + "|" + f[r][j][2]);
                // 1 & 0
                if (!f[r][i][1].empty() && !f[r][j][0].empty())
                    chkmn(f[r + 1][i & j][1], f[r][i][1] + "&(" + f[r][j][0] + ")");
                // 1 & 1
                if (!f[r][i][1].empty() && !f[r][j][1].empty())
                    chkmn(f[r + 1][i & j][1], f[r][i][1] + "&" + f[r][j][1]);
                // 1 & 2
                if (!f[r][i][1].empty() && !f[r][j][2].empty())
                    chkmn(f[r + 1][i & j][1], f[r][i][1] + "&" + f[r][j][2]);

                // 2 | 0
                if (!f[r][i][2].empty() && !f[r][j][0].empty())
                    chkmn(f[r + 1][i | j][0], f[r][i][2] + "|" + f[r][j][0]);
                // 2 | 1
                if (!f[r][i][2].empty() && !f[r][j][1].empty())
                    chkmn(f[r + 1][i | j][0], f[r][i][2] + "|" + f[r][j][1]);
                // 2 | 2
                if (!f[r][i][2].empty() && !f[r][j][2].empty())
                    chkmn(f[r + 1][i | j][0], f[r][i][2] + "|" + f[r][j][2]);
                // 2 & 0
                if (!f[r][i][2].empty() && !f[r][j][0].empty())
                    chkmn(f[r + 1][i & j][1], f[r][i][2] + "&(" + f[r][j][0] + ")");
                // 2 & 1
                if (!f[r][i][2].empty() && !f[r][j][1].empty())
                    chkmn(f[r + 1][i & j][1], f[r][i][2] + "&" + f[r][j][1]);
                // 2 & 2
                if (!f[r][i][2].empty() && !f[r][j][2].empty())
                    chkmn(f[r + 1][i & j][1], f[r][i][2] + "&" + f[r][j][2]);
            }
        }
        // cerr << r << endl;
        // for (int i = 0; i < n; i++)
        //     for (int j = 0; j < 3; j++)
        //         cerr << f[r][i][j] << " \n"[j == 2];
        // cerr << endl;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 3; j++)
            chkmn(ans[i], f[R][i][j]);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：xtx1092515503 (赞：2)

一种打表优化的DP做法。

------------

首先，观察到所有可能的输入串数量不超过 $2^8=256$ 种，就可以往打表方向想了。

然后，我们发现，假设一种运算，其取值表为一个串 $a$，另一种运算的取值表为串 $b$，则如果我们把这两种运算用一种 `operator` 怼一块，其最终效果就相当于把 $a$ 串和 $b$ 串怼一块。

于是我们发现，只需要维护一个运算的取值表就可以来表示一种运算。

但是，我们发现，仅维护取值表，表示运算本身是可以的，但是在合并两种运算的时候，不知道要不要加括号。

于是我们便得额外再设一维，表示其最后一次进行的运算是什么。以 $0$ 表示 `or` 运算，$1$ 表示 `and` 运算，$2$ 表示 `not` 运算，$3$ 表示里面是一个常数。这样，如果一个优先级大的运算符被加在了**比它小**的运算后面，运算要加括号；被加在了**不大于它**的运算前面，也要加括号。

我们设 $f[i][j]$ 表示若运算的取值表是 $i$，外层运算符是 $j$，其字典序最小的串是什么（即，储存的值是一个 `string`）。

我们并不知道DP顺序是什么；但是，仿照Bellman-Ford的思想，我们完全可以多跑几轮，每一轮枚举两个运算拼一起，这样多拼几次，总会把所有东西都变成稳定态。

猜想可得轮数不会太大；我跑了 $20$ 轮就够了。

因为我们的目标是打表，所以也没必要使用什么奇技淫巧来优化，反正这么没加任何优化地写下来，最终也在 `20s` 内就把表打完了。假如不想打表的话，就还要费尽心思优化DP，不如打表来得爽（

打表部分的代码，最终答案被存到了 $r$ 数组中：

```cpp
#include<bits/stdc++.h>
using namespace std;
string f[256][4];//the minimum of data i, with overall state j(0:or 1:and 2:not 3:const) 
map<string,int>mp;
string s[256],r[256];
string match(pair<string,int>x,pair<string,int>y,int op){
//	cout<<x.first<<' '<<y.first<<' '<<op<<'=';
	if(op>x.second)x.first="("+x.first+")";
	if(op>=y.second)y.first="("+y.first+")";
//	cout<<x.first+(op==1?'&':'|')+y.first<<endl;
	return x.first+(op==1?'&':'|')+y.first; 
}
string rev(pair<string,int>x){
	if(x.second>=2)return "!"+x.first;
	return "!("+x.first+")";
}
void chmn(string &x,string y){if(!y.empty()&&(x.empty()||x.size()>y.size()||x.size()==y.size()&&x>y))x=y;}
int main(){
	for(int i=0;i<256;i++){
		for(int j=7;j>=0;j--)s[i]+='0'+((i>>j)&1);
		mp[s[i]]=i;
	}
	f[mp["00001111"]][3]="x";
	f[mp["00110011"]][3]="y";
	f[mp["01010101"]][3]="z";
	for(int stp=0;stp<=20;stp++){
		printf("%d\n",stp);
		for(int i=0;i<256;i++)for(int j=0;j<256;j++)for(int ii=0;ii<4;ii++)for(int jj=0;jj<4;jj++){
			if(f[i][ii].empty()||f[j][jj].empty())continue;
			chmn(f[i|j][0],match(make_pair(f[i][ii],ii),make_pair(f[j][jj],jj),0));
			chmn(f[i&j][1],match(make_pair(f[i][ii],ii),make_pair(f[j][jj],jj),1));
		}
		for(int i=0;i<256;i++)for(int ii=0;ii<4;ii++){
			if(f[i][ii].empty())continue;
			chmn(f[(~i)&255][2],rev(make_pair(f[i][ii],ii)));
		}
	}
	for(int i=0;i<256;i++)for(int j=0;j<4;j++)chmn(r[i],f[i][j]);
	for(int i=0;i<256;i++)cout<<"\""<<r[i]<<"\","<<endl;
	int n;
	cin>>n;
	string ss;
	while(n--)cin>>ss,cout<<r[mp[ss]]<<endl;
	return 0;
}
*/
```

---

## 作者：Purslane (赞：1)

# Solution

有人说这题很难，但我觉得随便写写就做完了啊？？

考虑真值表 $\texttt F_1$ 当前最优的拟合为 $S_1$，$\texttt F_2$ 当前最优拟合为 $S_2$，那么对于真值表 $\texttt F_1 \text{ and } \texttt F_2$ 就可以用 $S_1 + \texttt \& + S_2$ 拟合吗？$\texttt F_1 \text{ or } \texttt F_2$ 就可以用 $S_1 + \texttt | + S_2$ 拟合吗？

显然，由于运算优先级，后一种必定可以实现，前一种只有 $S_1$ 和 $S_2$ 都是 $\square \texttt \& \square \texttt \& \square \texttt \&\dots \texttt \& \square$ 这种形态才能直接连接。那么再开一位记录一下最外层有没有 $\texttt |$ 作为连接。

对于取反操作，容易发现除了单个变量，取反都必须加括号。

不断进行松弛操作。汝可模拟得之。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=260;
int n,len[MAXN][2],cx,cy,cz,ccx,ccy,ccz;
string ans[MAXN][2];
//如果 op = -1，那么说明最外层套了个 !()  ——值得注意的是，不用打括号当且仅当里面只有一个变量，直接预处理
//否则，如果 op=1 表示用 | 连接；如果 op=2 表示用 & 连接
//第二维表示有没有 | 作为最外层连接。这样再用 & 连接的时候就要打括号，并且默认最外层没有 | 连接。
int trans(string S) {
	int ans=0;
	for(auto ch:S) ans=((ans<<1)+(ch-'0'));
	return ans;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cx=trans("00001111"),cy=trans("00110011"),cz=trans("01010101");
	ccx=255-cx,ccy=255-cy,ccz=255-cz;
	memset(len,0x3f,sizeof(len)),len[cx][0]=len[cy][0]=len[cz][0]=1,len[ccx][0]=len[ccy][0]=len[ccz][0]=2;
	ans[cx][0]="x",ans[cy][0]="y",ans[cz][0]="z";
	ans[ccx][0]="!x",ans[ccy][0]="!y",ans[ccz][0]="!z";
	while(1) {
		int flg=0;
		ffor(x,0,255) ffor(xop,0,1) ffor(y,0,255) ffor(yop,0,1) if(len[x][xop]!=0x3f3f3f3f&&len[y][yop]!=0x3f3f3f3f) {
			string _and,_or;
			if(xop) _and="(";_and+=ans[x][xop];if(xop) _and+=")";
			_and+="&"; if(yop) _and+="(";_and+=ans[y][yop];if(yop) _and+=")";
			_or=ans[x][xop]+"|"+ans[y][yop];
			if(len[x&y][0]>len[x][xop]+len[y][yop]+1+2*xop+2*yop||len[x&y][0]==len[x][xop]+len[y][yop]+1+2*xop+2*yop&&_and<ans[x&y][0]) {
				len[x&y][0]=len[x][xop]+len[y][yop]+1+2*xop+2*yop,ans[x&y][0]=_and,flg=1;
			}
			if(len[x|y][1]>len[x][xop]+len[y][yop]+1||len[x|y][1]==len[x][xop]+len[y][yop]+1&&_or<ans[x|y][1]) {
				len[x|y][1]=len[x][xop]+len[y][yop]+1,ans[x|y][1]=_or,flg=1;
			}
		}
		ffor(x,0,255) ffor(xop,0,1) if(len[x][xop]!=0x3f3f3f3f) {
			string _not="!("+ans[x][xop]+")";
			if(len[255-x][0]>len[x][xop]+3||len[255-x][0]==len[x][xop]+3&&_not<ans[255-x][0]) {
				len[255-x][0]=len[x][xop]+3,ans[255-x][0]=_not,flg=1;
			}
		}
		if(!flg) break;
	}
	int T; cin>>T;
	while(T--) {
		string S; cin>>S; int id=trans(S);
		if(len[id][0]<len[id][1]) cout<<ans[id][0]<<'\n';
		else if(len[id][0]>len[id][1]) cout<<ans[id][1]<<'\n';
		else cout<<min(ans[id][0],ans[id][1])<<'\n';	
	}
	return 0;
} 
```

---

## 作者：xfrvq (赞：0)

注意到 $8$ 位字符串，考虑状压 dp 求出 $2^8=256$ 种可能的答案。

为避免转移顺序乱套，加一维代表转移到了第几层，每次只能 $i$ 层向 $i+1$ 层转移。

此时还有优先级问题，我们看看题目中是怎么说明优先级的。

> $$E=\begin{cases}E\operatorname{or}T\\T\end{cases}$$
> $$T=\begin{cases}T\operatorname{and}F\\F\end{cases}$$
> $$F=\begin{cases}\operatorname{not}F\\(E)\\\mathtt{x,y,z}\end{cases}$$

于是加一维优先级 $j\in\{0,1,2\}$ 代表 $E,T,F$ 三种类型的式子。

最终状态：$f_{i,S,j}$ 代表 dp 到第 $i$ 层，表示状态为 $S$，优先级为 $j$ 的**式子**。

转移分为如下几种：

+ 加括号：$F\gets(E),(T)$
+ 非：$F\gets\operatorname{not}F$
+ 或：$E\gets X\operatorname{or}Y,X\in\{E,T,F\},Y\in\{T,F\}$
+ 与：$T\gets X\operatorname{and}F,X\in\{T,F\}$

为什么与，或中的 $X,Y$ 集合不对等？这是因为运算符后面的表达式可能被运算符抢走一部分。运算符前的表达式由于从左往右因此无误。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = (a);i <= (b);++i)

int T;
bitset<8> n;
string f[11][256][3],s;

void upd(auto &S,auto T){
	if(empty(S) || size(T) < size(S) || size(T) == size(S) && T < S) S = T;
}

int main(){
	f[0][15][2] = 'x',f[0][51][2] = 'y',f[0][85][2] = 'z';
	rep(k,0,9){
		rep(i,0,255){
			rep(j,0,2) if(size(f[k][i][j])) upd(f[k + 1][i][j],f[k][i][j]);
			if(size(f[k][i][0])) upd(f[k + 1][i][2],'(' + f[k][i][0] + ')');
			if(size(f[k][i][1])) upd(f[k + 1][i][2],'(' + f[k][i][1] + ')');
			if(size(f[k][i][2])) upd(f[k + 1][255 ^ i][2],'!' + f[k][i][2]);
			rep(j,0,255)
				rep(y,1,2){
					if(size(f[k][i][y]) && size(f[k][j][2])) upd(f[k + 1][i & j][1],f[k][i][y] + '&' + f[k][j][2]);
					rep(x,0,2)
						if(size(f[k][i][x]) && size(f[k][j][y])) upd(f[k + 1][i | j][0],f[k][i][x] + '|' + f[k][j][y]);
				}
		}
	}
	for(scanf("%d",&T);T--;){
		cin >> n,s = "";
		rep(i,0,2) upd(s,f[10][n.to_ulong()][i]);
		cout << s << '\n';
	}
	return 0;
}
```

---


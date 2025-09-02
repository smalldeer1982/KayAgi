# [USACO10HOL] Rocks and Trees G

## 题目背景

```
My country's bigger than most
And if asked I boast
'Cause I'm really proud
So I shout it loud
Though our numbers are few
We will welcome you
Although we don't have history
Gold medal winning teams
Heroes or prisoners
World famous volcanoes
Still what we've got's glorious
'Cause we've got
Rocks and trees
And trees and rocks
And rocks and trees
And trees and rocks
And rocks and trees
And trees and rocks
And rocks and trees
And trees and rocks
And water
-The Arrogant Worms, on Canada
（本段为诗歌，具体内容与题目无关）

## 题目描述

After moving across the 49th parallel to Canada, the land of rocks and trees, Farmer John's cows invented a game to spend their leisure time on the pasture; naturally, it involved the rocks and trees! Cowboy Ted likes this game very much, but so poor is his luck that he always loses to other cows. This time, he is going to seek your help. 

The game's rules are simple. It is played with a tree that has both $N$$(2 \leqslant N \leqslant10000)$nodes conveniently numbered $1 \cdots N$ and also $N-1$ branches. Node 1 is the root of this tree; except for node 1, node $i$ has parent $P_i$ $(1 \leqslant P_i < i)$. Initially, Each node contains some rocks (except the root node, which has no rocks). In particular, non-root node $i$ has exactly $R_i (1 \leqslant R_i \leqslant 1000)$ rocks at the beginning of the game. 

Two players alternate turns to play this game in turn, with Ted going first. In each turn, the current player can choose a non-root node $i$ and move at most $L (1 \leqslant L \leqslant 1000)$ rocks from this node one branch closer to the root (i.e., move these rocks to the parent node). He must move at least one rock, and, of course, he cannot exceed the current number of rocks on this node. The game ends when a player can't make a legal move (i.e., when all the rocks are on node 1); that player loses. 

Ted needs your help. He has given you the initial configuration of the game, and he will then make $T (1 \leqslant T \leqslant 10000)$changes to the configuration one by one. Please help him determine, after each step, if he can win the game beginning from this configuration, assuming both he and his opponent use the best possible strategy. 

Ted's changes are specified as two integers $A_j (1 < A_j \leqslant N)$ and $B_j (1 \leqslant B_j \leqslant 1000)$, meaning that Ted will change the number of rocks on node $A_j$ to $B_j$ (this is a `set` not a `subtract` or `add`), and will then ask you whether he can win. Changes accumulate; node $A_j$'s rocks stay at $B_j$ until another change for $A_j$ appears.

Consider this example with three nodes numbered as shown and the shape shown in Board 0. Initially, there are 5 rocks on node 2 and 3 rocks on node 3; see Board 1.

For the first change, Ted removes 2 rocks from node 2 (thus leaving 3); see Board 2. For the second change, Ted removes 2 rocks from node 3 (thus leaving 1). Note that node 2 still has 3 rocks; see Board 3.

Board 0 Board 1 Board 2 Board 3

（原题面并未给出链接）

Your program should determine in each case who wins.

For about 30% of the test cases, $N \leqslant 10$, and $T \leqslant 100$, and no tree node will have more than 5 rocks on it after any of Ted's changes.

Partial feedback will be provided for your first $50$ submissions.

## 说明/提示

数据来源：bzoj。

## 样例 #1

### 输入

```
3 2 10 
1 5 
1 3 
2 3 
3 1 
```

### 输出

```
No 
Yes 
```

# 题解

## 作者：lizbaka (赞：1)

关于Nim游戏，sg函数及其一些变形可以戳这位大佬的blog:

https://blog.csdn.net/clover_hxy/article/details/53818624

---

## Solution
这是一道阶梯Nim游戏的题，与普通的阶梯Nim游戏不同之处在于它是在一棵树上移动，实际上就是多个阶梯Nim游戏的复合

我们知道，阶梯Nim游戏可以视作对奇数阶梯上上的石子做Nim，证明在上方的blog中有提及，在此不再赘述

在此题中，设$1$号节点的深度为$0$，那么深度为奇数的节点即为“奇数阶梯”

考虑每次对节点上石头数量的修改，我们可以保存上一次修改后求出的$sg$值的异或和$x$

如果修改的节点的深度为偶数，对答案并没有贡献，直接判断上一次的$x$即可

如果修改的节点的深度为奇数，由于异或满足自反性(即$x$ xor $x$ $=0$)，所以在修改之前，我们只需要对$x$异或一遍修改前的数，再异或一遍修改后的数即可，而没有必要重新求一遍异或和

## Code
```cpp
#include <cstdio>
#define maxn 10005
#define maxL 1005
using namespace std;

int n,T,L;
int r[maxn],prt[maxn],dep[maxn];
int sg[maxL];

int x;
inline bool Solve(int pos,int chg)
{
    if(!(dep[pos]&1))
        return x;
    x^=sg[r[pos]];
    x^=sg[r[pos]=chg];
    return x;
}

int main()
{
    scanf("%d%d%d",&n,&T,&L);
    register int i;
    int a,b;
    for(i=1;i<=1000;++i)
        sg[i]=i%(L+1);
    for(i=2;i<=n;++i)
    {
        scanf("%d%d",&prt[i],&r[i]);
        dep[i]=dep[prt[i]]+1;
        if(dep[i]&1)
            x^=sg[r[i]];
    }
    for(i=1;i<=T;++i)
    {
        scanf("%d%d",&a,&b);
        if(Solve(a,b))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}


```

---

## 作者：qiucr (赞：0)

### 题意
在树上做一个台阶 Nim 游戏，求先手是否必胜
### 思路
首先我们知道，对于一个台阶 Nim 游戏，我们可以看成把台阶为**奇数编号**的抽出来做一个普通的 Nim 游戏。\
结论为若**奇数编号**台阶的所有石子异或和为 $0$ 则先手必败，反之必胜。\
简单证明一下，若后手移动**偶数编号**的台阶的石子，那么先手可以在之后把后手移动的石子等量的移动到下一个**偶数编号**的石子，结果不变，所以我们可以看成**偶数编号**的石子是无贡献的。\
对于这道题，其实也没什么区别，记录每个点的深度，若深度为**奇数**，则把答案异或其的 $sg_i$，由 sg 定理知道正确性显然，然后就做完了
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e6+100,mod=1e9+7;
int n,T,m;
int w[N],dep[N],f[N];
int res;
int sg(int x){
    if(f[x]!=-1) return f[x];
    unordered_map<int,int> S;
    for(int i=1;i<=m;i++){
        if(x<i) break;
        S[sg(x-i)]=true;
    }
    for(int i=0;;i++) if(!S.count(i)) return f[x]=i;
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>T>>m;
    memset(f,-1,sizeof f);
    for(int i=2;i<=n;i++){
        int fa;
        cin>>fa>>w[i];
        dep[i]=dep[fa]+1;
        if(dep[i]&1) res^=sg(w[i]);
    }
    while(T--){
        int a,b;
        cin>>a>>b;
        if(dep[a]&1) res^=sg(w[a]),w[a]=b,res^=sg(w[a]);
        if(res) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    return 0;
}

```

---


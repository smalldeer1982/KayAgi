# Sagheer and Apple Tree

## 题目描述

Sagheer is playing a game with his best friend Soliman. He brought a tree with $ n $ nodes numbered from $ 1 $ to $ n $ and rooted at node $ 1 $ . The $ i $ -th node has $ a_{i} $ apples. This tree has a special property: the lengths of all paths from the root to any leaf have the same parity (i.e. all paths have even length or all paths have odd length).

Sagheer and Soliman will take turns to play. Soliman will make the first move. The player who can't make a move loses.

In each move, the current player will pick a single node, take a non-empty subset of apples from it and do one of the following two things:

1. eat the apples, if the node is a leaf.
2. move the apples to one of the children, if the node is non-leaf.

Before Soliman comes to start playing, Sagheer will make exactly one change to the tree. He will pick two different nodes $ u $ and $ v $ and swap the apples of $ u $ with the apples of $ v $ .

Can you help Sagheer count the number of ways to make the swap (i.e. to choose $ u $ and $ v $ ) after which he will win the game if both players play optimally? $ (u,v) $ and $ (v,u) $ are considered to be the same pair.

## 说明/提示

In the first sample, Sagheer can only win if he swapped node $ 1 $ with node $ 3 $ . In this case, both leaves will have $ 2 $ apples. If Soliman makes a move in a leaf node, Sagheer can make the same move in the other leaf. If Soliman moved some apples from a root to a leaf, Sagheer will eat those moved apples. Eventually, Soliman will not find a move.

In the second sample, There is no swap that will make Sagheer win the game.

Note that Sagheer must make the swap even if he can win with the initial tree.

## 样例 #1

### 输入

```
3
2 2 3
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 2 3
1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
8
7 2 2 5 4 3 1 1
1 1 1 4 4 5 6
```

### 输出

```
4
```

# 题解

## 作者：Hoks (赞：1)

## 前言
第一次自己切 $2300$ 的博弈论题目，感觉挺有意思的。

曾今在某本书上看到过类似于这道题目的一道题。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
首先我们都知道博弈论的一个入门问题：Nim 游戏。

他的结论是先手还是后手必胜与所有石子堆的数量有关，异或和为 $0$ 方为先手必胜。

考虑他的一个推广形式，即为**阶梯游戏**：
> 有一个 $n$ 级的阶梯，每级阶梯上有若干硬币。二人轮流操作，每次可以将某一级台阶上的若干个硬币移到下一级。无法操作者输。问是先手必胜还是后手必胜。

这是一个经典问题，我们考虑把他转化为 Nim 游戏来求解。

设最低一级的台阶为 $1$，那么按照奇偶分类，先手移动的台阶有两种可能：
1. 先手移动了一个偶数编号的台阶。
2. 先手移动了一个奇数编号的台阶。

对于 $2$ 情况，设移动的台阶编号为 $x$，显然有 $x>2$，所以移动一级后 $x-1>1$，不为最低一级台阶，必然是可以仿照先手的操作后手把这个台阶再往下移一格的。

而对于 $1$ 情况，这就是一个 Nim 取石子游戏，套路的套用结论即可。

解决了阶梯游戏问题，我们再来考虑这个题目。

这个题目唯一的提升就是**链变为了树**。

但是注意到题目中的关键词**从根到任何叶子的路径长度的奇偶性相同**。

我们会发现，从 $x$ 移动到他的任意儿子 $y$，距离 $y$ 子树中的任意叶子的距离奇偶性都是相同的。

也就是其实就是有很多不同的可以分叉的阶梯，但是分叉并不影响奇偶性。

那么还是套用上面的结论，到叶子距离为偶数的会有影响，而奇数的可以套路的模仿操作而规避。

偶数的仍然是 Nim 游戏，所以只要满足这些偶数节点的异或和为 $0$，即为后手必胜。

用桶存一下可以换的点的个数，直接数一下即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,M=1.7e7+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,s,tot,ans,cnt[M],a[N],f[N];vector<int>e[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void dfs(int u){for(auto v:e[u]) dfs(v),f[u]=f[v]^1;}
signed main()
{
	n=read();for(int i=1;i<=n;i++) a[i]=read();
	for(int i=2;i<=n;i++) e[read()].emplace_back(i);
	dfs(1);for(int i=1;i<=n;i++) (!f[i])&&(s^=a[i]),cnt[a[i]]+=f[i],tot+=f[i];
	if(!s) ans=tot*(tot-1)/2+(n-tot)*(n-tot-1)/2;
	for(int i=1;i<=n;i++) (!f[i])&&(ans+=cnt[s^a[i]]);
	print(ans);genshin:;flush();return 0;
}
```

---

## 作者：Cloud_Umbrella (赞：1)

## 分析：

前置知识：Nim 游戏。

这是一道博弈论，只要你明白了“取石子游戏”，应该也不难理解。首先，为什么所有石子的异或和为零时，先手必输，而如果不为零，先手必赢？我简单的解释一下。

当全部堆的石子数量为零时，石子异或和为零。先手没得取，所以先手必输。

更普遍的，假设原序列的异或和为 $0$，那么有个显然的结论，就是改变某个数（只能缩小）之后异或和不可能还是 $0$，此时先手必输。当异或和不为零时，先手一定有办法将异或和变为零。设异或和为 $t$，则 $t$ 在二进制下某个位置上的 $1$ 在原序列中一定能找到一个数在这位上也有 $1$，那么将这个数改变为这个数异或上 $t$，就可以达到异或和为零的目的。

那么这题也是类似。因为叶子结点深度奇偶性相同，所以可以看成一条链。将所有结点根据到终点距离的奇偶性分成两类，假如一次操作将奇数点上的一部分移到偶数点，那另一个人可以立即将这部分移到奇数点，所以是没有意义的。那么只剩下从偶数点移到奇数点的情况。是不是很熟悉？其实某节点对答案的贡献跟移来移去无关，跟最后一次移到终点时有关，假如将离终点距离为 $1$ 的结点移到终点，另一个人立刻将它吃掉。由于双方都是最优，所以转换成了取石子问题。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5, M = 1.7e7 + 5;//注意大小 
int n, a[N], d[N], t[M]/*这个没用的值出现的次数*/, head[N], to[N], nxt[N];
int tmp, tot/*无用点的个数*/, ans, cnt;
void add(int u, int v) {
	++cnt;
	to[cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}
void init(int x) {
	for (int i = head[x]; i; i = nxt[i]) {
		init(to[i]);
		d[x] = d[to[i]] ^ 1;
	}
}
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
	for (int i = 2, u; i <= n; ++i) {
		scanf("%lld", &u);
		add(u, i);
	}
	init(1);//算是预处理 
	for (int i = 1; i <= n; ++i) 
		if(!d[i]) tmp ^= a[i];
	for (int i = 1; i <= n; ++i) {
		if(d[i]) {
			t[a[i]]++;
			tot++;
		}
	}
	if(!tmp) ans = tot * (tot - 1) / 2 + (n - tot) * (n - tot - 1) / 2;
	for (int i = 1; i <= n; ++i) 
		if(!d[i]) ans += t[tmp ^ a[i]];
	printf("%lld\n", ans);
	return 0;//好习惯伴终生 
} 
```

---

## 作者：极寒神冰 (赞：1)

### 题意：

给定一棵$n$个节点的苹果树，第$i$个点上有$a_i$个苹果。这棵树有一个特殊的性质是：从根到任何叶子的路径长度的奇偶性相同。

Sagheer 和 Soliman 将在树上轮流移动，Soliman 先手，当轮到某个玩家在自己的回合不能移动时这个玩家失败。

每次移动时，两个玩家都可以任意选择一个节点，从中取出至少一个苹果，进行以下两种操作之一：

1. 若选择叶子节点，则吃掉这些苹果
2. 若选择非叶节点，则可以将这些苹果移动到某个子节点。

在每次游戏开始之前，Sagheer 可以对苹果树进行一次更改：选择两个节点$u,v(u\ne v)$然后交换$a_u,a_v$。

假设双方都走最优方案，求出有多少对$(u,v)$满足后手获胜（$(u,v)$与$(v,u)$视为一样）。





### sol：

在标准nim游戏中，直接计算每堆石子的异或值，若异或值为$0$，则先手必败，否则先手必胜。

而nim游戏的某个变体为有一个额外操作，允许玩家将$>0$个石子加入某个石堆中（以及给定一些使游戏不会无限进行的条件），那么这个问题的解决方案类似于标准nim游戏，因为这个额外的操作将被原本获胜的玩家使用，而当原本失败的玩家使用时，原本胜利的玩家可以通过扔掉这些被加入的石子。

而本题可以建模为上面所提到的变体。令所有叶节点为黑色，然后让所有黑色节点的父亲为白色，白色节点的父亲为黑色……这样黑白染色之后，黑色节点就可以看成石堆，而白色节点就可以看成拿石子或加石子的操作。

注意到由于题目保证了题目保证了从根到任何叶子的路径长度的奇偶性相同，因此不会有一个节点有两种颜色。

所以说，若所有黑色节点的异或值$s=0$，则在初始树上 Soliman 为先手必败，而为了保持这种状态，Sagheer 可以进行以下两个操作：

1. 交换任意两个黑色节点或者白色节点。
2. 交换两个黑白节点满足两个点的苹果数量相同。

若所有黑色节点的异或值$s\neq 0$，则在初始树上 Sagheer 为后手必败。因此为了交换后改变异或值满足$s=0$，Sagheer 需要将某个黑色节点$u$与白色节点$v$交换满足$s\oplus a_u \oplus a_v=0$。

时间复杂度为线性。

```c++
int n;
int col[111111];
vector<int>e[111111],blk;
int a[111111],cnt[2];
map<int,int>mp;
int s,ans;
void dfs(int u)
{
    for(int v:e[u]) dfs(v);
    if(e[u].size()==0) col[u]=0;
    else col[u]=col[e[u][0]]^1;
    if(!col[u]) s^=a[u],blk.pb(a[u]);
    else ++mp[a[u]];
    ++cnt[col[u]];
}
signed main()
{
    n=read();
    R(i,1,n) a[i]=read();
    R(i,2,n) e[read()].pb(i);
    dfs(1);
    if(s==0)
    {
        ans=(cnt[0]*(cnt[0]-1ll)+cnt[1]*(cnt[1]-1))>>1;
        for(int x:blk) ans+=mp[x];
    }   
    else
    {
        for(int x:blk) if((x^s)<=10000000) ans+=mp[x^s];
    }
    writeln(ans);
}
```



---

## 作者：Priestess_SLG (赞：0)

简单 $2300$。考虑到树的特殊性质，根节点到所有叶子结点的距离的奇偶性均相同，那么可以考虑把所有结点按照层数分类，问题转化为 Nim 阶梯博弈，只需要判断所有到所属子树内叶子结点距离为偶数的结点的异或值是否为 $0$ 即可。

问题变为如何计数答案。交换奇偶性相同的层对答案不会产生影响，可以单独处理。而若交换的是奇偶性不同的层，则将会把当前的异或值再异或上这两个元素所对应的值，只需要判断这个值是否为 $0$，简单开桶维护即可。时间复杂度为 $O(n)$，但是我没看到数据范围 $a_i\le 10^7$ 所以用了 `map` 维护，时间复杂度变为 $O(n\log n)$，也能过。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500010;
int a[N], dep[N];
vector<int> adj[N];
void dfs(int u) {
    for (int &v : adj[u]) {
        dfs(v);
        dep[u] = dep[v] ^ 1;
    }
}
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 2; i <= n; ++i) {
        int x; cin >> x;
        adj[x].emplace_back(i);
    }
    dfs(1);
    int now = 0;
    for (int i = 1; i <= n; ++i)
        if (!dep[i]) now ^= a[i];
    map<int, int> mp;
    int cnt = 0, use = 0, use2 = 0;
    for (int i = 1; i <= n; ++i) {
        if (dep[i]) {
            ++mp[a[i]];
            ++use;
        } else ++use2;
    }
    for (int i = 1; i <= n; ++i)
        if (!dep[i]) cnt += mp[a[i] ^ now];
    if (!now) {
        cnt += use * (use - 1) / 2;
        cnt += use2 * (use2 - 1) / 2;
    }
    cout << cnt << '\n';
    return 0;
}
```

---


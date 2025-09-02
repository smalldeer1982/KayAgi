# Bakry and Partitioning

## 题目描述

### 题目背景

Bakry 遇到了一道题，但他懒得做了，于是他想让你帮他做。


一棵树有 $n$ 个节点，第 $i$ 个节点的点权为 $a_i$ 。（注：树是一个有 $n$ 个节点、$n-1$ 条边的连通图）

你需要回答：能不能选择这棵树中的至少 $1$ 条边、至多 $k-1$ 条边删除，使得删除完这些边的树满足以下条件：

- 每个联通块的点权异或和相等

## 样例 #1

### 输入

```
5
2 2
1 3
1 2
5 5
3 3 3 3 3
1 2
2 3
1 4
4 5
5 2
1 7 2 3 5
1 2
2 3
1 4
4 5
5 3
1 6 4 1 2
1 2
2 3
1 4
4 5
3 3
1 7 4
1 2
2 3```

### 输出

```
NO
YES
NO
YES
NO```

# 题解

## 作者：清烛 (赞：15)

## Description

问将一棵树划分为最多 $k$ 个连通块，要求这些连通块内点权的异或和相等，问是否有解。

## Solution
首先我们发现，如果所有的点权异或和为 $0$，则必然有解，而且断掉任意一条边都是可以的。

为什么？考虑 $a\oplus b = 0$ 为的充要条件即为 $a = b$。而一条边必然将树划分为两个连通块，故任意一条边两侧连通块的异或和都相等。$\square$

然而异或和可能不为 $0$，我们不妨设其为 $m$。而根据异或的性质，我们知道划分出来的各个连通块的异或和只能为 $m$，而且连通块的个数为奇数。

这是为什么？考虑划分为三个连通块的情况：既要异或起来为 $m$ 又要两两相等，不难发现只能为三个 $m$。然后我们又会发现，但凡有解，一定能划分为这样的三个连通块。

可以这样理解，不妨将相邻的两个合并，会发现合并出了 $0$，再合并的话又会合并出 $m$。

现在问题就转化为了找到三个连通块使得他们的异或和都为 $m$。

问题再转化一下， 可以变为找到两个连通块使得他们的异或和为 $m$。因为我们考虑异或的性质，这两个连通块绝不可能互相包含。

现在问题就很简单了。dfs 扫描一遍即可。如果遇到一个节点 $u$ 有两个子树 $v_1,v_2$ 内含异或和为 $m$ 的子树，则一定有解。而且，如果当前子树 $u$ 的异或和为 $0$，且存在一个包含在 $u$ 内的异或和为 $m$ 的子树，则也一定有解。

稍加分析可知上面两种涵盖了所有的情况。为什么？因为我们其实找到两条边，他们划分出的异或和为 $m$ 的区域没有交，则其就为合法的。反映到上面的第一种，就是两个子树内有 $m$（不可能有交），以及子树 $v$ 内有 $m$，子树 $u$ 以外的部分也有 $m$。

还不明白的可以看下代码，看了代码应该就明白了。

## Implementation

```cpp
#include <cstdio>
#include <cctype>
#include <vector>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

namespace fastIO {} // namespace fastIO

using namespace fastIO;

const int maxn = 1e5 + 5;
std::vector<int> G[maxn];
int n, k, a[maxn], sum[maxn], cnt0[maxn], cntk[maxn];
int xorsum = 0;

bool dfs(int u, int fa) {
    sum[u] = a[u];
    int tmpk = 0, tmp0 = 0;
    for (auto v : G[u]) {
        if (v == fa) continue;
        if (dfs(v, u)) return true;
        sum[u] ^= sum[v];
        if (cntk[v]) ++tmpk;
        if (cnt0[v]) ++tmp0;
        if (tmpk >= 2) return true;
    }
    if (!sum[u] && tmpk) return true;
    cnt0[u] = ((tmp0 ? 1 : 0) | (sum[u] == 0));
    cntk[u] = ((tmpk ? 1 : 0) | (sum[u] == xorsum));
    return false;
}

int main() {
    int T; read(T);
    while (T--) {
        read(n), read(k);
        xorsum = 0;
        FOR(i, 1, n) G[i].clear(), read(a[i]), xorsum ^= a[i];
        FOR(i, 1, n - 1) {
            int u, v; read(u), read(v);
            G[u].push_back(v), G[v].push_back(u);
        }
        if (!xorsum) puts("YES");
        else {
            if (k >= 3 && dfs(1, 0)) puts("YES");
            else puts("NO");
        }
    }
    return output(), 0;
}
```





---

## 作者：Alex_Wei (赞：7)

### 1592C. [Bakry and Partitioning](https://www.luogu.com.cn/problem/CF1592C)

分两种情况讨论：

- 异或和为 $0$。此时删去任意一条边都符合要求。
- 异或和不为 $0$。不妨设其为 $c$。此时若 $k=2$ 则显然无解。否则若树上存在两个不相交子树满足异或和为 $c$ 则有解（断掉这两个子树，剩下的图异或和也是 $c$），可以通过 dfs 求出 $sz_i$ 表示子树内最多有多少个不相交的异或和为 $c$ 的 “小子树”，以及 $x_i$ 表示子树异或和。若 $sz_i\geq 2$ 或者 $sz_i=1$ 且 $x_i=0$（此时当前子树就可以被分成一个小子树和剩下来的连通块，且异或和都为 $c$）则有解。否则可以证明无解。

时间复杂度 $\mathcal{O}(n)$。

```cpp
const int N=2e5+5;
const int inf=0x3f3f3f3f;

int n,k,a[N];
vector <int> e[N];
int sz[N],xo[N],tot,ok;
void dfs(int id,int f){
	sz[id]=0,xo[id]=a[id];
	for(int it:e[id])
		if(it!=f)dfs(it,id),xo[id]^=xo[it],sz[id]+=sz[it];
	if(sz[id]==0&&xo[id]==tot)sz[id]=1;
	if(sz[id]==1&&xo[id]==0||sz[id]>=2)ok=1;
}
void solve(){
	cin>>n>>k,tot=ok=0;
	for(int i=1;i<=n;i++)cin>>a[i],tot^=a[i],e[i].clear();
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		e[u].pb(v),e[v].pb(u);
	}
	if(tot==0)return puts("YES"),void();
	if(k==2)return puts("NO"),void();
	dfs(1,0),puts(ok?"YES":"NO");
}
int main(){
	int t=1; cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：Daidly (赞：5)

异或的题大部分还是用了 $a$ ${\rm{xor}}$ $a=0$ 这个性质。

记整个树的权值异或和为 $sum$。

可以发现，若能分成 $x$ 个连通块：

- 若 $x$ 为偶数，则满足 $sum=0$，因为可以将偶数个 $x$ 两两异或，结果为 $0$，输出 `YES`。

- 若 $x$ 为奇数，可以两两消去直到剩 $3$ 个，`dfs check` 即可。

`dfs check` 过程中，若 $u$ 的子树的异或和等于 $sum$，则算一个，若找到两条及以上的边可以满足条件，并且 $k\ge3$，就输出 `YES`。

因为 $sum=$ 子树异或和 的个数大于等于 $2$，就已经保证有两个等于 $sum$ 的，并且总的还等于 $sum$，所以可以。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

inline void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int MAXN=2e5+5;
int t,n,k,a[MAXN],sum;
vector<int>e[MAXN];

int cnt;

int dfs(int u,int fa){
	int ans=a[u],v,tmp;
	for(int i=0;i<e[u].size();++i){
		v=e[u][i];
		if(fa==v)continue;
		tmp=dfs(v,u);
		if(tmp==sum)cnt++;
		else ans^=tmp;
	}
	return ans;
}

int main(){
	t=read();
	while(t--){
		sum=cnt=0;
		n=read(),k=read();
		for(int i=1;i<=n;++i){
			a[i]=read();
			sum^=a[i];
			e[i].clear();
		}
		for(int i=1;i<n;++i){
			int u=read(),v=read();
			e[u].push_back(v);
			e[v].push_back(u);
		}
		if(!sum)puts("YES");
		else if(k>=3){
			dfs(1,0);
			if(cnt>=2)puts("YES");
			else puts("NO");
		}else puts("NO");
	}
	return 0;
}
```

---

## 作者：World_Creater (赞：2)

诈骗题。

首先如果所有点的异或和为 $0$，我们一定可以找到两个连通块使得他们的异或和相等。直接输出 `YES`。

这是显然的，如果不存在这样两个连通块，那么异或和一定不为 $0$ 。

否则我们至少需要划分出三个连通块，**若不存在划分成三个连通块的方案，则一定无解。**（因为肯定可以将多个连通块其中几个连通块合并成一个连通块，最终变成三个连通块）。

由此我们可以得到代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],nxt[400005],head[200005],go[400005],K,k,s1,s2,f,ans;
void add(int u,int v)
{
	nxt[++K]=head[u];
	head[u]=K;
	go[K]=v;
}
void dfs(int x,int fa)
{
	int p1=s2,f1=f;
	s2^=a[x];
	for(int i=head[x];i;i=nxt[i])
	{
		int g=go[i];
		if(g!=fa)
			dfs(g,x);
	}
	int p2=s2;
	if(f==f1&&x!=1&&(p1^p2)==s1) f++;
	if((p1^p2)==0&&f!=f1) ans=1;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		K=0;
		s1=0;
		s2=0;
		f=0;
		ans=0;
		for(int i=1;i<=n;i++)
		{
			head[i]=0;
		}	
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			s1^=a[i];
		}
		for(int i=1;i<n;i++)
		{
			int u,v;
			cin>>u>>v;
			add(u,v);
			add(v,u);
		}
		if(s1==0)
		{
			puts("YES");
			continue;
		}
		dfs(1,0);
		puts((f>=2||ans)&&k>2?"YES":"NO");

	}
}
```

---

## 作者：NiLu (赞：1)


## 分析

如果你能分区树为 $m$ 的组件,每个组件的 $xor$ 是 $x$ ,然后你可以树分割成 $m-2$ 组件通过合并任何 $3$ 相邻组件到 $1$ 组件,和新组件的 $xor$ 等于 $x$ , $x$ $xor$ $x$ $xor$ $x$ $=$ $x$。

注意,答案永远是Yes,如果数组的 $xor$ 是 $0$ 。因为你可以删除树中的任何边，这两个分量就会有相同的 $xor$ 。否则，我们需要将树分成三个具有相同   $xor$ 的组件。假设 $x$ 是树中的所有节点值 $xor$ ,那么每个组件的  $xor$ 等于 $x$ ,我们需要寻找这两个分量从树上删除其中之一的  $xor$ 每个组件 = $x$ ,如果我们发现他们和 $K!=2$ 然后答案是“Yes”,否则“No”。为了搜索这两条边，我们首先在结点 $1$ 上开根，然后搜索最深的子树，使子树的 $xor$ 值等于 $x$ ，然后擦除这条边，再搜索第二条边。

## 总结

这题质量很高（题解我写了好久）

---

## 作者：ZLCT (赞：0)

# CF1592C Bakry and Partitioning
## 题意
给定一个 $n$ 个节点的树和长度为 $n$ 的序列 $a$ 以及一个整数 $k$。求能不能删除 $[1,k)$ 条边使得剩余连通块的异或和相等。\
$2\ge k \ge n$
## 太复杂没思路？
第一眼看到题很可能无从下手，于是我们从简单的例子来看。\
当 $k=2$ 时，相当于我们必须断掉一条边使两个连通块异或和相等。这个我们是很容易判断的，只需要遍历一遍树，把每个子树的异或和都算出来并且对每一条边都判断一下可不可以删除。
### 参考代码
```cpp
void dfs(int u,int fa){
    sum[u]=a[u];
    for(int v:G[u]){
        if(v!=fa){
            dfs(v,u);
            sum[u]^=sum[v];
        }
    }
    if((sumxor^sum[u])==sum[u])flag=1;
}
```
$k>2$ 还是不好办？别急，我们继续举例子。\
当 $k=3$ 时，我们依旧可以删除 $1$ 条边，于是上面的判断依旧成立。唯一多的就是我们可以删除 $2$ 条边了。\
我们考虑此时的局面。场上会出现 $3$ 个异或和相等的连通块，那么我们考虑把其中两个联通块异或起来就变成了 $0$，那么剩下连通块的异或和就是整棵树的异或和（不理解的可以构造一个）。\
既然我们已经确定了一个连通块的异或和了，题目又要求每个连通块的异或和相同，其余两个连通块的异或和我们也顺势求出来了。
### 理论成立，实践开始
```cpp
void check(int u,int fa){
    int flagnow=num;
    for(int v:G[u]){
        if(v==fa)continue;
        check(v,u);
        if(sum[v]==sumxor&&!vis[v]){
            num++;
            vis[v]=1;
            if(num==2)flag=1;
        }
        if(num!=flagnow)vis[u]=1;
        if((flagnow!=num)&&(sum[u]^sumxor)==sumxor)flag=1;
        //子树内已经有一个满足条件的连通块且当前树其他节点异或和为整棵树的异或和
    }
}
```
有点眉目了？或者还是没看出来？\
没有关系，我们继续~~打表~~观察 $k=4$ 的情况。\
这时候我们前两种删边方法依旧存在，只是多出来删 $3$ 条边的情况。\
我们如果删 $3$ 条边，就会出现 $4$ 个连通块，并且每个连通块的异或和相等。\
哦～？貌似有一些有趣的事情发生了。\
我们把其中两个相邻连通块合并起来，你会发现它们合成了一个异或和为 $0$ 的连通块，我们再把这个连通块和任意一个连通块合并，由于 $0\oplus x=x$，于是原来 $4$ 个异或和为 $x$ 的连通块可以看成 $2$ 个。\
这不就是我们删 $1$ 条边的情况吗？\
**amazing!**\
对于删 $4$ 条边的情况，我们用同样的思想可以转化为删 $2$ 条边的情况，以后同理都可以转化成删 $1/2$ 条边的情况。
## 思路过程整理
如果熟悉异或的性质，其实很容易发现上述做法，如果不太熟悉，我们也可以通过上面一步一步的观察把一个复杂的大问题一点点细分，逐步拆解，最终得到答案。
## solution
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,a[212345],k,sum[212345],sumxor,num;
bool vis[212345];
bool flag;
vector<int>G[112345];
void dfs(int u,int fa){
    sum[u]=a[u];
    for(int v:G[u]){
        if(v!=fa){
            dfs(v,u);
            sum[u]^=sum[v];
        }
    }
    if((sumxor^sum[u])==sum[u])flag=1;
}
void check(int u,int fa){
    int flagnow=num;
    for(int v:G[u]){
        if(v==fa)continue;
        check(v,u);
        if(sum[v]==sumxor&&!vis[v]){
            num++;
            vis[v]=1;
            if(num==2)flag=1;
        }
        if(num!=flagnow)vis[u]=1;
        if((flagnow!=num)&&(sum[u]^sumxor)==sumxor)flag=1;
    }
}
void solve(){
    cin>>n>>k;sumxor=0;flag=0;num=0;
    for(int i=1;i<=n;++i)G[i].clear();
    for(int i=1;i<=n;++i){
        vis[i]=0;
        cin>>a[i];
        sumxor^=a[i];
    }
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1,1);
    if(flag){
        cout<<"YES\n";
        return;
    }
    check(1,1);
    if(flag&&k>2){
        cout<<"YES\n";
    }else{
        cout<<"NO\n";
    }
}
signed main(){
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：Exber (赞：0)

从每一部分的异或和相同出发，设分割后每一部分的异或和都为 $k$，所有 $a_i$ 的异或和为 $sum$。不难发现**要么 $sum=0$ 即最后是偶数个 $k$ 异或起来，要么 $sum=k$ 即最后是奇数个 $k$ 异或起来**。

- 若 $sum=0$，我们**割断任意一条边都一定合法。因为割出来的两部分只有异或和相同它们异或起来的结果 $sum$ 才为 $0$**。

- 若 $sum=k$，那么**割断两条边，分割出三个异或和为 $k$ 的连通块显然是最优的**。所以**考虑找到两个异或和都为 $k$ 的连通块，剩下那一块异或和就自然为 $k$**。因为**肯定有一个满足条件的连通块是一棵子树，减掉它的贡献后又会有一个满足条件的连通块是一棵子树**，所以跑一次 $dfs$，**求出每个节点子树去掉异或和为的 $k$ 子树后的异或和** $dp_u=\operatorname{xor}_{v\text{ 是 }u\text{ 的儿子}}[dp_v\not=k]dp_v$ 即可。最后若 $\sum\limits_{u} [dp_u=k]\ge2$ 就说明有解。

部分代码如下：

```cpp
void dfs(int u,int fa,long long val)
{
	dp[u]=a[u];
	for(int i=h[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==fa)
		{
			continue;
		}
		dfs(v,u,val);
		if(dp[v]!=val)
		{
			dp[u]^=dp[v];
		}
	}
}

inline void slove()
{
	esum=0;
	scanf("%d%d",&n,&k);
	long long sm=0;
	for(int i=1;i<=n;i++)
	{
		h[i]=0;
		dp[i]=0;
		scanf("%lld",&a[i]);
		sm^=a[i];
	}
	for(int i=1;i<=n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	if(sm==0)
	{
		puts("YES");
		return;
	}
	if(k==2)
	{
		puts("NO");
		return;
	}
	dfs(1,0,sm);
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		cnt+=dp[i]==sm;
	}
	puts(cnt>=2?"YES":"NO");
}
```

---

## 作者：frank15 (赞：0)

这题的关键：$a\oplus a=0$。

如果可以分成偶数个连通块，则可以将它们两两配对异或，最终异或和为  $0$。

反过来，若所有数的异或和为 $0$，则有解。

如果可以分成奇数个连通块，依然将它们两两配对，最终可以剩下三个（因为至少要删去一条边，若剩下一个则说明没删边）。

那么问题就转换成了判定这棵树是否可以分成三个异或和相同的连通块。

不妨设 $\operatorname{sum}_i$ 表示以 $i$ 为根的子树的异或和，$x,y,z$ 表示这三个连通块， $\operatorname{tot}_x,\operatorname{tot}_y,\operatorname{tot}_z$ 表示它们各自的异或和，$x$ 为包含根的连通块。

首先，
$$
\begin{aligned}
  	\because \ &\operatorname{tot}_x \oplus \operatorname{tot}_y \oplus \operatorname{tot}_z = \operatorname{sum}_1, \ \operatorname{tot}_x \oplus \operatorname{tot}_y=0 \\
  	\therefore \ &\operatorname{tot}_z=\operatorname{sum}_1, \\
  	&\text{同理得} \operatorname{tot}_x=\operatorname{tot}_y=\operatorname{tot}_z=\operatorname{sum}_1
  \end{aligned}
$$

即这三个连通块的异或和均为所有数的异或和。

接着我们开始分类讨论。

1. 若 $y, \ z$ 不相交，如图：

[![5XeElD.png](https://z3.ax1x.com/2021/10/29/5XeElD.png)](https://imgtu.com/i/5XeElD)

  此时我们只需要判断以 $1$ 为根的子树中是否有两个节点的值均为  $\operatorname{sum}_1$，dfs 一遍即可，复杂度  $\mathcal{O}({n})$。
   	

2. 若 $y \in z \ \text{或} \ z\in y$，
		

[![5Xm4Vs.png](https://z3.ax1x.com/2021/10/29/5Xm4Vs.png)](https://imgtu.com/i/5Xm4Vs)

   此时以 $y$ 为根的子树中，一部分是属于 $y$ 的，一部分是属于 $z$ 的，显然有 $\operatorname{sum}_y=\operatorname{tot}_y \oplus \operatorname{tot}_z = 0$，也就是说我们要找到一个节点，其 $\operatorname{sum}$ 值为0，并且其子树中有一个节点的 $\operatorname{sum}$ 值为 $\operatorname{sum}_1$。我们可以在找到一个 $\operatorname{sum}$ 值为 $0$ 的节点的时候就在其子树中查找，并全部标记访问过，复杂度  $\mathcal{O}({n})$。


代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
const int maxn=1e5+5;
int t,n,k,cnt,U,V;
int sum[maxn],a[maxn],dfn[maxn],Max[maxn],rnk[maxn];
bool vis[maxn];
vector<int> v[maxn];
void dfs(int x,int fa){
    //dfn[x]表示x的dfn序，这样方便访问一个节点的子树
    //rnk[x]表示dfn序为x的节点
    //Max[x]表示x子树中最大的dfn，这样就知道了区间范围
    //sum[x]表示以x为根的子树的异或和
	dfn[x]=Max[x]=++cnt;
	rnk[cnt]=x;
	sum[x]=a[x];
	for(int i=0;i<v[x].size();i++)
		if(v[x][i]!=fa){
			dfs(v[x][i],x);
			Max[x]=max(Max[x],Max[v[x][i]]);
			sum[x]^=sum[v[x][i]];
		}
}
int dfs2(int x,int fa){
	//res表示以x为根，有多少个不相交的子树sum值为sum[1]
	int res=0;
	for(int i=0;i<v[x].size();i++)
		if(v[x][i]!=fa)
			res+=dfs2(v[x][i],x);
	if(x==1)
		return res>=2;//这里直接做了一个判定，res>=2即合法
	else
		return max(res,int(sum[x]==sum[1]));
}
int main(){
	scanf("%d",&t);
	for(int T=1;T<=t;T++){
		cnt=0;
		scanf("%d%d",&n,&k);
		--k;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			v[i].clear();
			sum[i]=vis[i]=dfn[i]=Max[i]=rnk[i]=0;
		}
		for(int i=1;i<n;i++){
			scanf("%d%d",&U,&V);
			v[U].push_back(V);
			v[V].push_back(U);
		}
		dfs(1,0);
		if(!sum[1])
			puts("yes");
		else{
			if(k==1)
				puts("no");
			else{
				bool flag=0;
				if(dfs2(1,0)){
					puts("yes");
					continue;
				}
                //第一种情况
				for(int i=1;i<=n;i++)
					if(!vis[i]){
						vis[i]=1;
						if(!sum[i]){
							for(int j=dfn[i];j<=Max[i];j++){
								vis[rnk[j]]=1;
								if(sum[rnk[j]]==sum[1]){
									flag=1;
									break;
								}
							}//访问其子树
						}
						if(flag)
							break;
					}
				if(flag)
					puts("yes");
				else
					puts("no");
			}
		}
	}
	return 0;
}
```

---


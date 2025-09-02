# Tachibana Kanade's Tofu

## 题目描述

Tachibana Kanade likes Mapo Tofu very much. One day, the canteen cooked all kinds of tofu to sell, but not all tofu is Mapo Tofu, only those spicy enough can be called Mapo Tofu.

Each piece of tofu in the canteen is given a $ m $ -based number, all numbers are in the range $ [l,r] $ ( $ l $ and $ r $ being $ m $ -based numbers), and for every $ m $ -based integer in the range $ [l,r] $ , there exists a piece of tofu with that number.

To judge what tofu is Mapo Tofu, Tachibana Kanade chose $ n $ $ m $ -based number strings, and assigned a value to each string. If a string appears in the number of a tofu, the value of the string will be added to the value of that tofu. If a string appears multiple times, then the value is also added that many times. Initially the value of each tofu is zero.

Tachibana Kanade considers tofu with values no more than $ k $ to be Mapo Tofu. So now Tachibana Kanade wants to know, how many pieces of tofu are Mapo Tofu?

## 说明/提示

In the first sample, 10, 11 and 100 are the only three decimal numbers in $ [1,100] $ with a value greater than 1. Here the value of 1 is 1 but not 2, since numbers cannot contain leading zeros and thus cannot be written as "01".

In the second sample, no numbers in the given interval have a value greater than 12.

In the third sample, 110000 and 110001 are the only two binary numbers in the given interval with a value no greater than 6.

## 样例 #1

### 输入

```
2 10 1
1 1
3 1 0 0
1 1 1
1 0 1
```

### 输出

```
97
```

## 样例 #2

### 输入

```
2 10 12
2 5 9
6 6 3 5 4 9 7
2 0 6 1
3 6 7 2 1
```

### 输出

```
635439
```

## 样例 #3

### 输入

```
4 2 6
6 1 0 1 1 1 0
6 1 1 0 1 0 0
1 1 2
3 0 1 0 5
4 0 1 1 0 4
3 1 0 1 2
```

### 输出

```
2
```

# 题解

## 作者：kouylan (赞：1)

~~我家立华奏特别爱吃麻婆豆腐，我天天做给她吃，她吃的可香了！~~

~~我是不会告诉你我是因为题目名称才点进来的。~~

一看到这种多模式串匹配的问题，就能想到用 AC 自动机。然后又是求 $[l,r]$ 中的方案数，就能想到是数位 dp。

我们可以定义 $f(x,now,lim,p0,v)$ 表示目前考虑到了数的第 $x$ 位，在 AC 自动机上的 $now$ 点，是/否压着上限，现在是/否在前导 $0$ 中，目前权值是 $v$ 的方案数。答案就是 $f(1,root,0,0,0)$。

我们考虑用记忆化搜索转移。每次枚举当前位填什么数字（注意这题数字范围是 $0\sim m-1$）。然后 AC 自动机上走到对应子节点，权值加上当前点的 $ed$ 值，如果新权值 $\leq k$，就可以接着往下转移。

有几个小细节需要注意：如果当前仍然处于前导 $0$ 中，第二维的 $now$ 是不需要动的。还有计算时 $l$ 需要减 $1$，要小心是 $m$ 进制。

当然，这个题如果写递推的话要比记忆化搜索快很多。~~但仗着 CF 机子快加上 $5s$ 时限，我还是成功卡过去了。~~

下面是 AC 代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int M = 1e9+7ll;

#define int long long

int n,m,k,lenl,dl[205],lenr,dr[205],ans;
int root=0,cnt,ch[205][20],ed[205],fail[205];
int len,a[205];
int dig[205],f[205][205][2][205];

void insert(int n,int v)
{
	int now=root;
	for(int i=1;i<=n;i++)
	{
		if(!ch[now][a[i]])
			ch[now][a[i]] = ++cnt;
		now = ch[now][a[i]];
	}
	ed[now] += v;
	ed[now] %= M; 
}

void getfail()
{
	fail[root] = root;
	queue<int> q;
	for(int i=0;i<m;i++)
		if(ch[root][i])
		{
			fail[ch[root][i]] = root;
			q.push(ch[root][i]);
		}
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		for(int i=0;i<m;i++)
		{
			if(ch[x][i])
			{
				fail[ch[x][i]] = ch[fail[x]][i];
				q.push(ch[x][i]);
				ed[ch[x][i]] += ed[fail[ch[x][i]]];
				ed[ch[x][i]] %= M;
			}
			else
				ch[x][i] = ch[fail[x]][i];
		}
	}
}

int dp(int x,int now,int lim,int p0,int v)
{
	if(x==len+1)
		return (p0 && v<=k);
	if(lim && f[x][now][p0][v]>=0)
		return f[x][now][p0][v];
	int res=0;
	for(int i=0;i<m;i++)
	{
		if(!lim && i>dig[x])
			break;
		int to=ch[now][i],v1=v;
		if(p0 || i>0)
			v1 += ed[to];
		if(v1<=k)
			res += dp(x+1,((p0 || i>0) ? to : now),(lim || i<dig[x]),(p0 || i>0),v1);
		res %= M;
	}
	if(lim)
		f[x][now][p0][v] = res%M;
	return res%M;
}

signed main()
{
	cin>>n>>m>>k;
	cin>>lenl;
	for(int i=1;i<=lenl;cin>>dl[i++]);
	for(int i=lenl;i>=1;i--)
	{
		if(dl[i]>0)
		{
			dl[i]--;
			break;
		}
		dl[i] = m-1;
	}
	cin>>lenr;
	for(int i=1;i<=lenr;cin>>dr[i++]);
	for(int i=1,v;i<=n&&cin>>len;i++)
	{
		for(int j=1;j<=len;cin>>a[j++]);
		cin>>v;
		insert(len,v);
	}
	getfail();
	len = lenr;
	for(int i=1;i<=lenr;i++)
		dig[i] = dr[i];
	memset(f,-1,sizeof(f));
	ans = dp(1,root,0,0,0);
	len = lenl;
	for(int i=1;i<=lenl;i++)
		dig[i] = dl[i];
	memset(f,-1,sizeof(f));
	ans = (ans-dp(1,root,0,0,0)+M)%M;
	cout<<ans<<endl;
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：BotYoung (赞：0)

前置知识：**AC 自动机**，**数位 DP**
## 前言
本题建议降紫，理由如下：

- CF Rating `*2500`

- 本题题面的引导性较强，可以说根据输入内容就能大概判断出使用了何种算法。

- 所以思维难度就不用说了。从算法的角度来看，就是很一般的 AC 自动机和数位 DP 嵌套，都是省选以前的内容；算好空间之后，使用记忆化搜索的实现难度也并不高。

## 题意
给定 $n$ 个 $m$ 进制数字样本串和一个常数 $k$，第 $i$ 个样本串有一个价值 $v_i$。一个模式串的相似度定义为其所有样本串子串的价值之和。现给定一个 $m$ 进制区间 $[L,R]$，求出 $[L,R]$ 之间相似度不超过 $k$ 的模式串的个数，对 $10^9+7$ 取模。
## 思路
缝合怪+套路题。

看到“$n$ 个样本串”，果断考虑 AC 自动机；看到一个有限范围内的区间 $[L,R]$，果断考虑数位 DP。

~~（其实想到这里题目差不多已经解完了）~~

考虑 $dp$ 状态的定义，显然需要记录当前转移的位数 $len$ 以及模式串已经达到的相似度 $now$。

### Q:如何快速计算 $now$？
很简单，套用 AC 自动机。如果我们能够记录一个模式串对应在自动机上的节点，那么就可以直接在自动机上转移。形式化的，我们先预处理从某一个节点开始暴力跳失配指针的 $v$ 之和。若当前字符串在自动机上对应 $x$ 节点，现在往数字串的末尾添加数字 $i$，那么我们直接把 $x$ 移动至对应的儿子节点 $ch_{x,i}$，自然的，$now\leftarrow now+v_{ch_{x,i}}$。

然后就是一个细节问题。注意到样本串包含前导零，意味着一个模式串中间部分的 $0$ 会对答案产生贡献（如：$S=01$，$T=101$）。而模式串中不含前导零，也就是说在最高位之前样本串都不能产生贡献。

所以需要在 DP 状态中多记录一维前导零的状态。

用记忆化搜索无脑实现即可。AC 自动机的大小是 $\sum len\leq200$，DP 状态的数量等于 $len_{L}\times\sum len\times k$，转移复杂度为 $O(m)$，故总时间复杂度为 $O(len_{L}mk\sum len)$，CF $5s$ 时限可过。

知道大家想看什么，上代码了：
```cpp
#include <bits/stdc++.h>
#define reg register
#define rep(i, l, r) for (reg int i = l; i <= r; i++)
#define per(i, r, l) for (reg int i = r; i >= l; i--)
using namespace std;
typedef long long ll;
typedef unsigned long long llu;
namespace io {
inline ll read() {
    reg ll s = 0, f = 1;
    reg char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        s = (s << 1) + (s << 3) + (ch ^ '0');
        ch = getchar();
    }
    return s * f;
}
inline void write(reg ll x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 ^ '0');
}
inline void write(reg ll x, reg char c) { write(x), putchar(c); }
}  // namespace io
using namespace io;
const int N = 205, M = 25, K = 505, mod = 1e9 + 7;
int n, m, k, dp[N][N][2][K];
int tot, num[N];
struct number {
    int len, num[N], val;
    inline void operator--() {
        rep(i, 1, len) {
            if (num[i] > 0) {
                num[i]--;
                break;
            }
            num[i] = m - 1;
        }
    }
} L, R, T;
struct AC_Automaton {
    int ncnt = 0;
    const int root = 0;
    int ch[N][M], fail[N];
    ll val[N];
    queue<int> Q;
    inline void insert(number a) {
        int x = root;
        per(i, a.len, 1) {
            if (!ch[x][a.num[i]])
                ch[x][a.num[i]] = ++ncnt;
            x = ch[x][a.num[i]];
        }
        val[x] += a.val;
    }
    inline void build() {
        rep(i, 0, m - 1) {
            if (ch[root][i]) {
                fail[ch[root][i]] = root;
                Q.push(ch[root][i]);
            }
        }
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            rep(i, 0, m - 1) {
                if (ch[u][i]) {
                    fail[ch[u][i]] = ch[fail[u]][i];
                    Q.push(ch[u][i]);
                    val[ch[u][i]] += val[fail[ch[u][i]]];
                } else
                    ch[u][i] = ch[fail[u]][i];
            }
        }
    }
} AC;
inline ll dfs(int len, int x, int now, bool limit, bool lead) {
    if (!len)
        return (!lead && now <= k);
    if (!limit && dp[len][x][lead][now] != -1)
        return dp[len][x][lead][now];
    int up = limit ? num[len] : m - 1;
    ll res = 0;
    rep(i, 0, up) {
        int y = AC.ch[x][i], tmp = now;
        if (!lead || i)
            tmp += AC.val[y];
        if (tmp <= k)
            (res += dfs(len - 1, (lead && (!i)) ? x : y, tmp, limit && (i == num[len]), lead && (!i))) %= mod;
    }
    if (!limit)
        dp[len][x][lead][now] = res;
    return res;
}
inline ll solve(number x) {
    memset(dp, -1, sizeof dp);
    tot = x.len;
    rep(i, 1, tot) num[i] = x.num[i];
    return dfs(tot, 0, 0, 1, 1);
}
int main() {
    n = read(), m = read(), k = read();
    L.len = read();
    per(i, L.len, 1) L.num[i] = read();
    --L;
    R.len = read();
    per(i, R.len, 1) R.num[i] = read();
    rep(i, 1, n) {
        T.len = read();
        per(j, T.len, 1) T.num[j] = read();
        T.val = read(), AC.insert(T);
    }
    AC.build();
    ll ans = (solve(R) - solve(L) + mod) % mod;
    write(ans);
    return 0;
}
```

---

## 作者：Drind (赞：0)

为了这碗醋包了大半个月的饺子。

首先我们发现这道题给定区间左端点右端点求区间内符合某种规律的数字个数，我们考虑用数位 dp 来解决这个问题。在数位 dp 的过程中我们发现我们比较难处理数字中出现了某个特殊数字串要怎么判断，对于这些多模式串匹配问题，我们考虑用 AC 自动机解决，这样这道题就被转换成了在 AC 自动机上数位 dp。

我们记 $f_{len,st,nk}$ 为目前处理前 $len$ 位，在 AC 自动机上的第 $st$ 个节点，并且现在的相似度已经达到了 $nk$，这样我们就直接枚举下一位放什么，记忆化搜索即可。

AC 自动机的实现是有点小细节的，实现详见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e2+10;
const int p=1e9+7;

int tr[N][21],cnt;
int fail[N],val[N];

int L[N][2],x[N];

int n,m,k;

void insert(int t){
	int u=0;
	for(int i=1;i<=x[0];i++){
		int v=x[i];
		if(!tr[u][v]) tr[u][v]=++cnt;
		u=tr[u][v];
	}
	val[u]+=t;//注意每次插入一个数字串到 trie 树上的权值是不一样的。
}

void build(){
	queue<int>q;
	for(int i=0;i<m;i++) if(tr[0][i]) q.push(tr[0][i]);
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=0;i<m;i++){
			if(tr[u][i]) fail[tr[u][i]]=tr[fail[u]][i],q.push(tr[u][i]),val[tr[u][i]]+=val[fail[tr[u][i]]];
            		//注意到我们匹配成功要加上他 fail 树上的子节点，因为存在自己和子节点同时匹配成功的情况
            		//例如主串 abc ，模式串 bc 和 c，这样我们在匹配到 bc 的时候顺便把 fail 指针指向的 c 也一起匹配了。
			else tr[u][i]=tr[fail[u]][i];
		}
	}
}

int dp[201][N][501];

int dfs(int len,int st,int nk,bool lim,bool lead,int x){
	if(len==L[0][x]+1) return ((!lead)&&nk<=k)?1:0;//如果到现在全部都是前导 0 是不能计入答案的。
	if(nk>k) return 0;//剪枝，以防爆数组。
	if(!lim&&!lead&&dp[len][st][nk]!=-1) return dp[len][st][nk];//记忆化
	int limit=lim?L[len][x]:m-1,ans=0;
	for(int i=0;i<=limit;i++){
		ans=(ans+dfs(len+1,(lead&&(i==0))?st:tr[st][i],(lead&&(i==0))?nk:(nk+val[tr[st][i]]),lim&&(i==L[len][x]),lead&&(i==0),x))%p;//如果还在前导 0 里是不能在 AC 自动机上跳的，也不能计入答案。
	}
	if(!lead&&!lim) dp[len][st][nk]=ans;
	return ans;
}

int work(int x){
	memset(dp,-1,sizeof dp); //注意我们的 len 从 1 开始，所以长度不一样的时候记忆化数组对应的也不一样，可以选择倒序处理但是这题时限卡的不紧，每次清空记忆化数组也可以过。
	return dfs(1,0,0,1,1,x);
}

int check(int x){//特判左端点的情况，跳 AC 自动机即可
	int u=0,ans=0;
	for(int i=1;i<=L[0][x];i++){
		u=tr[u][L[i][x]];
		ans+=val[u];
	}
	return ans<=k;
}

inline void fake_main(){
	cin>>n>>m>>k;
	cin>>L[0][0]; for(int i=1;i<=L[0][0];i++) cin>>L[i][0];
	cin>>L[0][1]; for(int i=1;i<=L[0][1];i++) cin>>L[i][1];
	for(int i=1;i<=n;i++){
		cin>>x[0]; int tmp;
		for(int j=1;j<=x[0];j++) cin>>x[j]; 
		cin>>tmp;;
		insert(tmp);
	}
	build();
	cout<<((work(1)-work(0)+check(0))%p+p)%p<<"\n"; //注意减法取模要防止出现负数。
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：_ctz (赞：0)

[安利blog](https://ctz45562.github.io/2019/10/15/Codeforces433E-Tachibana-Kanade-s-Tofu/)


[传送门](https://www.luogu.org/problem/CF433E)

这翻译跟那啥一样。。。复述一遍题意：

> 给定$n$个$m$进制数（可能包含前导$0$），每个数有一个价值$v_i$。定义一个$m$进制数的权值为$\sum\limits_{i=1}^ncnt_i\times v_i$，其中$cnt_i$为第$i$个数在该数中作为子串出现的次数。求$[L,R]$中（$L,R$均为$m$进制数），权值不超过$K$且不含前导零的$m$进制数的个数。

很套路的$AC$自动机上数位$DP$。

设$f(i,0/1,0/1,j,k)$为填到第$i$位、是否顶上界、是否有前导零、位于$AC$自动机的$j$节点、权值为$k$的方案数。

枚举数字刷表转移即可。

转移时要特别注意前导零。如果转移后的状态依然有前导零，权值$k$不会改变，**$AC$自动机也不会往下走**，因为这点调了一个小时$QAQ$。

复杂度$O(4lenK\sum|S|m)$，算出来是$O(1.6\times 10^9)$，刷表时跳过不合法状态再加上滚动数组就能过了。

代码：

``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

#define maxn 205
#define inf 0x3f3f3f3f

const int mod = 1e9 + 7;

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
#define son(x,y) son[x][y]
int en[maxn],line[maxn],son[maxn][20],pre[maxn],L[maxn],R[maxn],s[maxn],f[2][2][2][maxn][505],cnt=1,m,K;
void insert(int len,int v){
	int node=1;
	for(register int i=1;i<=len;++i){
		if(!son(node,s[i]))son(node,s[i])=++cnt;
		node=son(node,s[i]);
	}
	en[node]+=v;
}
void build(){
	int head=0,tail=1;
	line[1]=1;
	for(register int i=0;i<m;++i)son(0,i)=1;
	while(head<tail){
		int node=line[++head],x;
		en[node]+=en[pre[node]];
		for(register int i=0;i<m;++i){
			x=son(node,i);
			if(x)pre[x]=son(pre[node],i),line[++tail]=x;
			else son(node,i)=son(pre[node],i);
		}
	}
}
inline void add(int &x,int y){x+=y;if(x>=mod)x-=mod;}
int solve(int *tp){
	int len=tp[0],ans=0;
	memset(f,0,sizeof f);
	f[len&1][1][1][1][0]=1;
	for(register int i=len;i;--i)
		for(register int j=0;j<2;++j)
			for(register int k=0;k<2;++k)
				for(register int l=1;l<=cnt;++l)
					for(register int p=0;p<=K;++p){
						if(!f[i&1][j][k][l][p])continue;
						for(register int q=j?tp[i]:m-1;~q;--q)
							if((k&&!q)||p+en[son(l,q)]<=K)
								add(f[i&1^1][j&&q==tp[i]][k&&!q][(k&&!q)?l:son(l,q)][(k&&!q)?p:p+en[son(l,q)]],f[i&1][j][k][l][p]);
						f[i&1][j][k][l][p]=0;
					}
	for(register int i=1;i<=cnt;++i)
		for(register int j=0;j<=K;++j)
			add(ans,(f[0][0][0][i][j]+f[0][1][0][i][j])%mod);
	return ans;
}
int main(){
	int n=read();
	m=read(),K=read(),L[0]=read();
	for(register int i=1;i<=L[0];++i)L[L[0]-i+1]=read();
	R[0]=read();
	for(register int i=1;i<=R[0];++i)R[R[0]-i+1]=read();
	while(n--){
		int len=read();
		for(register int i=1;i<=len;++i)s[i]=read();
		insert(len,read());
	}
	build();
	int node=1,ans,sum=0;
	for(register int i=L[0];i;--i)node=son(node,L[i]),sum+=en[node];
	ans=sum<=K;
	printf("%d\n",(solve(R)-solve(L)+ans+mod)%mod);
}

```


---


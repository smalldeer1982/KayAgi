# Coin Troubles

## 题目描述

In the Isle of Guernsey there are $ n $ different types of coins. For each $ i $ $ (1<=i<=n) $ , coin of type $ i $ is worth $ a_{i} $ cents. It is possible that $ a_{i}=a_{j} $ for some $ i $ and $ j $ $ (i≠j) $ .

Bessie has some set of these coins totaling $ t $ cents. She tells Jessie $ q $ pairs of integers. For each $ i $ $ (1<=i<=q) $ , the pair $ b_{i},c_{i} $ tells Jessie that Bessie has a strictly greater number of coins of type $ b_{i} $ than coins of type $ c_{i} $ . It is known that all $ b_{i} $ are distinct and all $ c_{i} $ are distinct.

Help Jessie find the number of possible combinations of coins Bessie could have. Two combinations are considered different if there is some $ i $ $ (1<=i<=n) $ , such that the number of coins Bessie has of type $ i $ is different in the two combinations. Since the answer can be very large, output it modulo $ 1000000007 $ $ (10^{9}+7) $ .

If there are no possible combinations of coins totaling $ t $ cents that satisfy Bessie's conditions, output 0.

## 说明/提示

For the first sample, the following 3 combinations give a total of 17 cents and satisfy the given conditions: $ {0 of type 1,1 of type 2,3 of type 3,2 of type 4},{0,0,6,1},{2,0,3,1} $ .

No other combinations exist. Note that even though 4 occurs in both $ b_{i} $ and $ c_{i}, $ the problem conditions are still satisfied because all $ b_{i} $ are distinct and all $ c_{i} $ are distinct.

## 样例 #1

### 输入

```
4 2 17
3 1 2 5
4 2
3 4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 2 6
3 1 1
1 2
2 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3 2 10
1 2 3
1 2
2 1
```

### 输出

```
0
```

# 题解

## 作者：45dino (赞：3)

思路很容易想到，但是还是错了好几发，实在是太菜了 ![kk](https://cdn.luogu.com.cn/upload/pic/62227.png)

由于题目规定 $b$ 和 $c$ 互不相同，如果把每一个限制看作一条从 $b$ 连向 $c$ 的边，则最后的图中每一个连通块只能是环或链。

如果有环，感性理解一下，显然无解。

考虑每条链对总面值的最小贡献。

对于一条长度为 $n$ 的链，根节点所对的那种硬币最少取 $n-1$ 个，叶节点所对的最少不取，把最少的贡献从 $t$ 中扣除。

然后发现当把某一条链上的某一个点所对的硬币多取一个，同时就得多取从根到这个点上的所有硬币。

对于每一个点，计算多取这个点对 $t$ 的贡献，再跑一个完全背包即可。

参考代码：
```cpp
#pragma GCC optimize ("Ofast")
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	bool flag=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			flag=0;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return (flag?x:~(x-1));
}
int n,q,t,a[301],pre[301],nxt[301],f[100001],fa[301];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
vector<int> v;
const int mod=1e9+7;
signed main()
{
	n=read();
	q=read();
	t=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		fa[i]=i;
	while(q--)
	{
		int x=read(),y=read();
		if(find(x)==find(y))
		{
			puts("0");
			return 0;
		}
		fa[find(x)]=find(y);
		pre[y]=x;
		nxt[x]=y;
	}
	for(int i=1;i<=n;i++)
		if(pre[i]==0)
		{
			int num=0,tot=0,sum=0;
			for(int l=i;nxt[l];l=nxt[l])
				num++;
//			cout<<i<<" "<<num<<endl;
			for(int l=i;num>=0;l=nxt[l])
			{
				t-=num*a[l];
				sum+=a[l];
//				cout<<l<<" "<<num<<" "<<sum<<endl;
				num--;
				v.push_back(sum);
			}
		}
//	for(int i:v)
//		cout<<i<<endl;
	f[0]=1;
	if(t<0)
	{
		puts("0");
		return 0;
	}
	for(int i:v)
		for(int l=0;l+i<=t;l++)
			(f[l+i]+=f[l])%=mod;
	cout<<f[t]<<endl;
	return 0;
}
/*
4 2 17
3 1 2 5
4 2
3 4
*/
```


---

## 作者：turt1e (赞：2)

题目链接：<https://codeforces.com/problemset/problem/283/C>

### 题意：
有 $n$ 种硬币，每种硬币都有一个价格 $ai$，现在有 $q$ 个限制，每个限制会告诉你 $(b,c)$，并要求 $b$ 种硬币的数量**严格大于** $c$ 种硬币的数量。现在问你一共有多少种买硬币的方法，使得最后买硬币一共要 $t$ 元。答案最后要求对 $10^9+7$ 取模。

### 思路：
对于每一个限制，我们首先想到，如果对于一个数，它限制的数如果限制了它本身，那么肯定一种方法都没有。刨去这种特殊情况，如果将每一种限制画出来连在一起（未限制和被限制的点单独出现），直观的看就是多个有向无环图，容易想到拓扑序，也就可以看成多个树和多个点。考虑每条链的最小贡献，对于每一个被限制的点，我们每次可以将它的所有父亲节点的值从 $t$ 中减去，这样子就可以满足被限制的点的数量严格小于限制它的点的数量。

对于每一条链，我们可以把它作为一个整体考虑贡献，这样子我们就可以把这道题转化为完全背包了。

##### 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long // 不开long long见祖宗

const int N = 1e5 + 10, M = 310, mod = 1e9 + 7;
int k[M * 4], f[M][N], s[M], p[N], dp[N], fa[M];
int n, q, t;
vector <int> nxt[M];
int find(int x)
{
	if(p[x] == 0) return s[x];
	int fa = find(p[x]);
	return fa + s[x];
}
int find2(int x) // 找父亲
{
	return fa[x] == x ? x : fa[x] = find2(fa[x]);
}

signed main()
{
	int op = 0;
	cin >> n >> q >> t;
	for(int i = 1; i <= n; i++) cin >> s[i];
	for(int i = 1; i <= n; i++) fa[i] = i; // 预处理
	for(int i = 1; i <= q; i++)
	{
		int a, b;
		cin >> a >> b;
		if(find2(a) == find2(b)) // 找到环了
		{
			cout << '0';
			return 0;
		}
		fa[find2(a)] = find2(b);
		p[b] = a;
	}
	for(int i = 1; i <= n; i++)
	{
		if(p[i]) 
		{
			k[++op] = find(i);
			t -= (k[op] - s[i]);
		}
		else k[++op] = s[i];
	}
	if(t < 0) // 需要的硬币比拥有的硬币多，直接cout 0
	{
		cout << '0';
		return 0;
	}
	dp[0] = 1;
	for(int i = 1; i <= op; i++) // 完全背包
	{
		for(int l = 0; l + k[i] <= t; l++)
		{
			dp[l + k[i]] = (dp[l + k[i]] + dp[l]) % mod;
		}
	}
	cout << dp[t] % mod;
}

```

（本蒟蒻的第一篇题解，如有错误多多指正）

---

## 作者：xxseven (赞：1)

注意到题目条件中，$b$ 互不相同，$c$ 互不相同。

看到这种不知道怎么用的条件，考虑图论建模。

对于每一组 $(b,c)$，我们将 $b$ 向 $c$ 连边。

我们可以判掉有环的情况，这种情况必定无解。

由于上面的条件，我们可以发现每个点的出度和入度均不超过 $1$，那么可以得出，如果无环，连出的图一定由很多条链组成。

考虑我们要选入一个新的物品 $x$。那么在它所在的链上，从链头到 $x$ 上的物品都要增加一个。

为了描述这种捆绑关系，我们直接在链上做前缀和，选一个 $x$ 带来的价值即为链头到 $x$ 的物品价值和。

同时，由于偏序关系为严格大于，在每条链上，每个节点都要先选取**它到链尾的节点数再减一**个。发现可以拆成除了链尾以外所有节点上的前缀和的值，直接计算即可。

时间复杂度 $O(nt)$，可以通过。

[AC 记录](https://codeforces.com/contest/283/submission/289173786)。

---

## 作者：ZLCT (赞：1)

# CF283C Coin Troubles
## 题目翻译
给定 $n$ 种面值的硬币，每种硬币都有无限个。给出 $m$ 个约束条件形如 $(a,b)$ 表示第 $a$ 种硬币的个数要严格大于第 $b$ 种硬币个数。保证 $a_i\ne a_j(i\ne j)$ 且 $b_i\ne b_j(i\ne j)$。求有多少种方案使得凑出价值 $t$。
## 背包变体
### 完全背包求方案数
看到这个题假设忽略 $m$ 个约束条件，那就是完全背包求方案数。\
完全背包如何求方案数呢？其实和完全背包形式类似。\
我们类似完全背包的想法不断枚举最后一位的硬币面值与取得的最终硬币面值，完全背包求的是最小代价于是取 $\min$，那么求方案数就需要取加和。\
具体转移方程就是 $f_i=\sum\limits_{j=a_i}^{t}f_{j-a_i}$。
### 限制条件
接下来我们考虑那 $m$ 条约束条件。\
首先最直观的一个想法包括观察样例 $3$ 我们会发现若这些条件构成了一个环那一定不合法（因为无法做到 $a>b>a$）。\
接下来我们就要挖掘题目的特殊性质：$a_i,b_i$ 互不重复。\
这个性质告诉我们什么呢？假设一个限制条件相当于 $b\rightarrow a$ 的一条有向边，这告诉我们一个点的出度和入度最多为 $1$。进一步告诉我们假设不存在环，那么这 $m$ 条限制条件一定构成了若干条链。\
根据题目要求，这条链从起点开始一定是严格上升的。那么无论如何对于一条链肯定有这条链上最后一个点至少选 $0$ 个，倒数第二个点至少选 $1$ 个，以此类推。\
所以我们可以先把这些必要的硬币选上，这样样例二那种必要的减去以后剩余 $t<0$ 的情况一定没有合法方案。这样原来的上升序列就变成了不下降序列，对于不下降序列我们对应到差分数组上，条件就转化为了差分数组每个元素都非负。\
这样条件就变成了背包的条件，于是我们考虑对于这个差分数组进行背包。对于新数组第 $i$ 个元素的面值就是这个元素在差分数组 $+1$ 所对应的贡献，即 $i$ 所在链上 $i$ 及后面所有硬币面值之和。
### 实现
首先判断环我们可以在反图上跑遍 topo，这样可以求出是否有环以及每个点在所在链上的深度，以便先把必要的硬币选出来。\
接着我们在正图上跑一遍 topo，这一遍求每一个点作为差分数组上元素的贡献。\
最后对新算出的贡献跑一遍完全背包求方案数即可。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=333;
const int mod=1e9+7;
int n,m,w,a[N],d[N],b[N],deg[N],DEG[N],f[112345];
vector<int>G[N];
vector<int>g[N];
void topo(){
    queue<int>q;
    for(int i=1;i<=n;++i){
        if(!deg[i]){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int v:G[u]){
            d[v]=d[u]+1;
            deg[v]--;
            q.push(v);
        }
    }
}
void TOPO(){
    queue<int>q;
    for(int i=1;i<=n;++i){
        if(!DEG[i]){
            q.push(i);
            b[i]=a[i];
        }
    }
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int v:g[u]){
            b[v]=b[u]+a[v];
            DEG[v]--;
            q.push(v);
        }
    }
}
signed main(){
    cin>>n>>m>>w;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=1;i<=m;++i){
        int u,v;cin>>u>>v;
        G[v].push_back(u);
        g[u].push_back(v);
        deg[u]++;
        DEG[v]++;
    }
    topo();
    TOPO();
    for(int i=1;i<=n;++i){
        if(deg[i]){
            cout<<0<<'\n';
            return 0;
        }
        w-=a[i]*d[i];
        if(w<0){
            cout<<0<<'\n';
            return 0;
        }
    }
    f[0]=1;
    for(int i=1;i<=n;++i){
        for(int j=b[i];j<=w;++j){
            f[j]+=f[j-b[i]];
            f[j]%=mod;
        }
    }
    cout<<f[w]<<'\n';
    return 0;
}
```

---

## 作者：wwlw (赞：1)

2020.11.2

[Link](https://www.luogu.com.cn/problem/CF283C)
----------------

### 题目描述

有 $n$ 种不同的硬币，每个硬币有一个价值 $a_i$​（不同硬币价值可能相同).

$Bessie$ 有若干种选择硬币的方法使得选出的硬币总价值为 $t$。 $Bessie$ 会给你 $q$ 对 $(b,c)$，并告诉你第 $b$ 种硬币的数量严格大于第 $c$ 种硬币的数量。保证这 $q$ 对 $(b,c)$ 中所有 $b$ 都不同且所有 $c$ 也都不同。 
问有多少种选择硬币的方法满足选出的硬币总价值为 $t$。

$Bessie$ 认为两种方案不同指的是两种方案存在至少一种硬币数量不同。

答案对 $10^9+7$ 取模。

### 解法

对于一个约束条件 $(b_i,c_i)$ ，建一条 $c_i\to b_i$ 的边（反图）。

可以看出一个点的入度和出度小于等于一，那么这个图一定是由若干个简单环和链组成的。有环显然答案为零，只考虑链的情况。

先构造一组最小的合法的方案，所组成的价值即为每个节点的价值乘上其到根节点的距离，任意其它的方案多会比此方案多，我们不妨先用 $t$ 减去这个值。对于一种硬币 $i$，我们如果想要再用掉一个且满足约束条件的话，那么 $i$ 的整个子树里面的硬币都需要再用一次，即我们可以把每个物品的价值直接改为其子树价值和。可以发现这样总是满足条件的，那么现在的问题就转换为完全背包了。

```cpp
#include<stdio.h>
#include<queue>
using namespace std;
#define M 1000007
#define N 507
#define ll long long
#define Mod 1000000007

inline ll read(){
    ll x=0; bool flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}

struct E{
    int next,to;
}e[N];
int head[N],cnt=0,n,m;
bool in[N];
queue<int> Q;
ll dp[M],t,a[N],dep[N];

inline void add(int id,int to){
    e[++cnt]=(E){head[id],to};
    head[id]=cnt;
}

void dfs(int u){
    for(int i=head[u];i;i=e[i].next){
        int v=e[i].to;
        dfs(v);
        a[u]+=a[v];
    }
}

int main(){
//    freopen("coin.in","r",stdin);
//    freopen("coin.out","w",stdout);
    n=read(),m=read(),t=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        add(v,u),in[u]=1;
    }
    for(int i=1;i<=n;i++)
        if(!in[i]) dep[i]=1,Q.push(i);
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        for(int i=head[u];i;i=e[i].next){
            int v=e[i].to;
            dep[v]=dep[u]+1;
            t-=(dep[u]*a[v]);
            Q.push(v);
        }
    }
    for(int i=1;i<=n;i++)
        if(!dep[i]){
            printf("0");
            return 0;
        }
    for(int i=1;i<=n;i++)
        if(dep[i]==1) dfs(i);
    dp[0]=1;
    if(t<0){
        printf("0");
        return 0;
    }
    for(int i=1;i<=n;i++)
        for(ll j=a[i];j<=t;j++)
            dp[j]=(dp[j]+dp[j-a[i]])%Mod;
    printf("%lld",dp[t]);
}
```


---

## 作者：Purslane (赞：0)

# Solution

水篇题解找存在感。

如果偏序关系出现了环，显然无解。否则，偏序关系构成了若干条链，依次考虑每条链。

注意到链的倒数第二个元素至少要选 $1$ 个，倒数第三个元素至少要选 $2$ 个，依次类推，最后一个元素至少要选 $(len-1)$ 个。先扣掉这一部分的贡献。

这时候问题变为 $b$ 的次数不少于 $c$。于是对物品进行一个线性变换，依次将前 $i$ 个物品的和当做新的第 $i$ 个物品即可。复杂度 $O(nt)$。

代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10,MOD=1e9+7;
int n,m,t,fa[MAXN],dp[MAXN],a[MAXN],pre[MAXN],nxt[MAXN],rnk[MAXN];
int find(int k) {return (fa[k]==k)?k:(fa[k]=find(fa[k]));}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>t,dp[0]=1; ffor(i,1,n) cin>>a[i],fa[i]=i;
	ffor(i,1,m) {
		int u,v; cin>>u>>v,nxt[u]=v,pre[v]=u;
		if(find(u)==find(v)) return cout<<0,0;
		fa[find(u)]=find(v);	
	}
	ffor(i,1,n) if(nxt[i]==0) {
		int lst=pre[i];
		while(lst) rnk[lst]=rnk[nxt[lst]]+1,lst=pre[lst];
	}
	ffor(i,1,n) {
		t-=rnk[i]*a[i];	
		if(t<0) return cout<<0,0;
	}
	ffor(i,1,n) if(pre[i]==0) {
		int sum=0,lst=i;
		while(lst) {
			sum+=a[lst];
			if(sum>t) break ;
			ffor(j,sum,t) dp[j]=(dp[j]+dp[j-sum])%MOD;
			lst=nxt[lst];
		}
	}
	cout<<dp[t];
	return 0;
}
```

做完这道题可以看看 [$\color{purple} \text P2481 \ 代码拍卖会$](https://www.luogu.com.cn/problem/P2481)，差不多的。

---

## 作者：龙翔凤翥 (赞：0)

###  solution：完全背包+分析
1. 我们假设a<b<c<d<...（a代表第a中硬币的数量）(**我们称这种关系为链关系**（假设）），那么如果我们增加a种硬币数量要加1，那么b种硬币肯定也要加1.所以可以把b种硬币的价值设为a+b。转换为完全背包模型。
2. 细节处理：我们需要处理出现环的情况，如果所有的硬币形成环，那么ans=0。
3. 详情见代码
## Code：
```
// luogu-judger-enable-o2
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define RN register int
#define ll long long
const ll mod=1e9+7;
inline int read() {
    int x=0,o=1;
    char ch=getchar();
    while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-') o=-1,ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*o;
}
int n,q,t;
int f[100050];
int a[550],so[550],fa[550];
int main()
{
	n=read(),q=read(),t=read();
	for(RN i=1;i<=n;i++)
		a[i]=read();
	for(RN i=1;i<=q;i++)
	{
		int v,x;
		v=read(),x=read();
		so[x]++;//x的“儿子”+1
		fa[v]=x;//v的“父亲”为x
	}
	for(RN i=1;i<=q;i++)
	{
		int pos=0;
		for(RN j=1;j<=n;j++)
		{
			if((fa[j])&&(!so[j]))
			{pos=j;break;}
		}
		if(!pos)//若是环
		{puts("0");return 0;}
		int pre=fa[pos];
		fa[pos]=0;//把这个节点去掉
		so[pre]--;
		//cout<<"fa[2]="<<fa[2]<<" so[2]="<<so[2]<<endl;
		//cout<<"fa[4]="<<fa[4]<<" so[4]="<<so[4]<<endl;
		t-=a[pos];//作为链关系的根，在方案中肯定要有一种
		a[pre]+=a[pos];//类似把b的值改为a+b
		if(t<0)
		{puts("0");return 0;}
	}
	f[0]=1;
	for(RN i=1;i<=n;i++){
		for(RN j=a[i];j<=t;j++)
			f[j]=(f[j]+f[j-a[i]])%mod;//完全背包模型
	}
	cout<<f[t]<<endl;
	return 0;
}
```

---


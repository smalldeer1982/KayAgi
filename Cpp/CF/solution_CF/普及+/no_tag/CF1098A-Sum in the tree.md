# Sum in the tree

## 题目描述

Mitya has a rooted tree with $ n $ vertices indexed from $ 1 $ to $ n $ , where the root has index $ 1 $ . Each vertex $ v $ initially had an integer number $ a_v \ge 0 $ written on it. For every vertex $ v $ Mitya has computed $ s_v $ : the sum of all values written on the vertices on the path from vertex $ v $ to the root, as well as $ h_v $ — the depth of vertex $ v $ , which denotes the number of vertices on the path from vertex $ v $ to the root. Clearly, $ s_1=a_1 $ and $ h_1=1 $ .

Then Mitya erased all numbers $ a_v $ , and by accident he also erased all values $ s_v $ for vertices with even depth (vertices with even $ h_v $ ). Your task is to restore the values $ a_v $ for every vertex, or determine that Mitya made a mistake. In case there are multiple ways to restore the values, you're required to find one which minimizes the total sum of values $ a_v $ for all vertices in the tree.

## 样例 #1

### 输入

```
5
1 1 1 1
1 -1 -1 -1 -1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 2 3 1
1 -1 2 -1 -1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
1 2
2 -1 1
```

### 输出

```
-1
```

# 题解

## 作者：览遍千秋 (赞：4)

本题解同步发布于[本场$\mathrm{CF}$总题解](https://www.luogu.org/blog/kaiming/CF530Div2)，欢迎来踩。

---

## A(DIV.1),D(DIV.2) - Sum in the tree

### 直观但错误的想法

一开始有一个非常直观的想法，对于每一个结点，如果不知道它的$s$，就直接设它为$0$，可是在$\color{red} \mathrm{WA}$了几次之后，就会考虑到这样的一种情况：

有一结点$x$，$s$未知，如果这时候令其点权为$k$，则其每一个儿子都可以比令$x$点权为$0$少掉$k$的代价，这种情况显然比直接令$x$优。

但是这个错误的思路可以打开我们正确的思路。

### 考虑无解

$\forall son$，如果存在$s_{son}<s_x$，则无解。

### 正解

将$s_{son}$上提，使$s_x=min { s_{son} }$

贪心即可。

code:
```
#include<bits/stdc++.h>
using namespace std;
#define maxn 100003
#define int long long
#define INF 0x3f3f3f3f
int n,fa[maxn];
int s[maxn],ans;
int Head[maxn],Next[maxn],tot,to[maxn];

template<typename Tp>
void read(Tp &x){
	x=0;char ch=1;int fh;
	while(ch!='-'&&(ch>'9'||ch<'0')) ch=getchar();
	if(ch=='-'){
		ch=getchar();fh=-1;
	}
	else fh=1;
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	x*=fh;
}

void dfs1(int x){
	s[fa[x]]=min(s[fa[x]],s[x]);
	for(int i=Head[x];i;i=Next[i]){
		dfs1(to[i]);
	}
}

void dfs2(int x){
	if(s[x]<s[fa[x]]){
		puts("-1");exit(0);
	}
	if(s[x]!=INF)
		ans+=s[x]-s[fa[x]];
	for(int i=Head[x];i;i=Next[i]){
		dfs2(to[i]);
	}
}

void add(int x,int y){
	to[++tot]=y,Next[tot]=Head[x],Head[x]=tot;
}

int main(){
	read(n);
	for(register int i=2;i<=n;i++){
		read(fa[i]);
		add(fa[i],i);
	}
	for(register int i=1;i<=n;i++){
		read(s[i]);if(s[i]==-1) s[i]=INF;
	}
	dfs1(1);dfs2(1);
	printf("%I64d\n",ans);
	return 0;
}
```

---

## 作者：tXX_F (赞：2)

# Sum in the tree

## 解题思路

由题意可知，若让一个 $a_i$ 尽可能的去给更多的 $s_i$ 做贡献，即可使 $\sum a_i$ 最小。所以对每个 $-1$ 的 $s_i$ 搜索出其孩子中的最小 $s_i$（因为要求每个子节点 $s_i$ 总会大于父节点 $s_i$）,最后判断若有子节点 $s_i$ 小于父节点 $s_i$，则输出 $-1$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
char buf[1048576], *p1, *p2;
template<typename T>inline void Super_Quick_Read(T &x) {
	bool f = 1;
	x = 0;
	char ch = (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? 0 : *p1++);
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = !f;
		ch = (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? 0 : *p1++);
	}
	while (ch >= '0' && ch <= '9')x = (x << 1) + (x << 3) + (ch ^ 48), ch = (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? 0 : *p1++);
	x = (f ? x : -x);
	return;
}
template<typename T>inline void Quick_Write(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) Quick_Write(x / 10);
	putchar(x % 10 + '0');
	return;
}
int n;
long long s[200005];
int V[200005], F[200005], Next[200005], Father[200005], Length;
long long Answer = 0;
inline void Add(int a, int b) {
	V[++Length] = b, Next[Length] = F[a], F[a] = Length;
}
inline long long Dfs(int n) {
	if (s[n] != -1)	return s[n];
	else {
		int k = F[n];
		long long _min = INT_MAX;
		while (k != -1)_min = min(Dfs(V[k]), _min), k = Next[k];
		s[n] = _min;
		return s[n];
	}
}
signed main() {
	Super_Quick_Read(n);
	for (register int i = 0; i <= n + 1; ++i)F[i] = -1;
	for (register int i = 2, p; i <= n; ++i)Super_Quick_Read(p), Add(p, i), Father[i] = p;
	for (register int i = 1; i <= n; ++i)Super_Quick_Read(s[i]);
	int flag = 0;
	for (register int i = 1, t1, t2; i <= n; ++i) {
		t1 = Dfs(i), t2 = Dfs(Father[i]);
		if (t1 != INT_MAX) {
			if (t2 > t1)flag = 1;
			Answer += (t1 - t2);
		}
	}
	if (flag)puts("-1");
	else Quick_Write(Answer);
	return 0;
}
```

---

## 作者：子谦。 (赞：2)

很简单的一道贪心题

首先，先想想怎么判断是否合法

题目中说，a是自然数，那么子节点的s明显是不能比父节点大的，如果比父节点大，不合法！

所有深度为偶数的点的s被删除了，也只有深度为偶数的点被删除了，所以如果深度为奇数的点被删除了，或者有深度为偶数的点没有被删除，不合法！

所有不合法的情况我们已经判断完了，下面考虑如何使权值和最小

对于奇数层的点我们肯定是无法影响了，只有通过控制偶数层的点的权值才能影响总的权值和，而且只能影响自己和自己子节点的权值

我们从简单的入手，对于偶数层叶子结点，我们直接让它的$s$等于父节点的$s$即可，这样$a$为$0$，合法且最优

对于有一个子节点的偶数层节点，取值在$[s_{fa},s_{son}]$中任意取值，总的权值和都是不变的。

简单证明一下，就是$a_{son}=s_{son}-s_v,a_{v}=s_v-s_{fa},a_v+a_{son}=s_{son}-s_{fa}$，而两个$s$都是已知的，所以这里的s爱取啥取啥，只要合法就行

那么对于子节点大于1的偶数层节点我们怎么处理呢，我们设子节点的权值不全相同

那么$a_v=s_v-s_{fa},\sum a_{son}=\sum (s_{son}-s_v)$

总的和就是$\sum(s_{son}-s_v)+s_v-s_{fa}$

显然，当$s_v$越小时，这个式子的值也就越小，同时我们还要保证合法，所以$s_v$我们就取最小的$s_{son}$

为了程序的简练，我们将三种情况合并，简述为

> 若存在子节点则为最小的$s_{son}$，否则为$s_{fa}$

由于数据范围不小，记得开long long

就是这么简单，下面上代码，由于讲的已经很清楚了，代码就不加注释了

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#ifdef ONLINE_JUDGE
#define puts(o) puts("I AK IOI\n")
#endif
#define ll long long
#define gc getchar
#define maxn 100005
using namespace std;

inline ll read(){
    ll a=0;int f=0;char p=gc();
    while(!isdigit(p)){f|=p=='-';p=gc();}
    while(isdigit(p)){a=(a<<3)+(a<<1)+(p^48);p=gc();}
    return f?-a:a;
}int n,ans;ll sum;

struct ahaha{
    int to,next;
}e[maxn];int tot,head[maxn];
inline void add(int u,int v){
    e[tot]={v,head[u]};head[u]=tot++;
}

int f[maxn],dep[maxn];ll s[maxn],s1[maxn];
void dfs(int u,int fa){
    for(int i=head[u];~i;i=e[i].next){
        int v=e[i].to;
        if(~s[v]){
            if((dep[v]&1)^1){ans=1;return;}
        }
        else{
            if(dep[v]&1){ans=1;return;}
            s[v]=(s1[v]==1000000001?s[u]:s1[v]);
        }
        if(s[v]<s[u]){ans=1;return;}
        sum+=s[v]-s[u];
        dfs(v,u);if(ans)return;
    }
}
ll dfs(int u){
    for(int i=head[u];~i;i=e[i].next){
        int v=e[i].to;
        dep[v]=dep[u]+1;
        s1[u]=min(s1[u],dfs(v));
    }
    return s[u];
}

int main(){memset(head,-1,sizeof head);
    n=read();dep[1]=1;
    for(int i=2;i<=n;++i)
        add(read(),i);
    for(int i=1;i<=n;++i){
        s[i]=read();
        s1[i]=1000000001;
    }
    sum+=s[1];dfs(1);dfs(1,-1);
    if(ans)
        puts("-1");
    else
        printf("%I64d\n",sum);
    return 0;
}
```

~~抄代码的怕是A不了~~

---

## 作者：RYANGSJ (赞：1)

## 思路

设数组$f_i$ 表示在最优方案下 从 $i$ 号节点到根节点的点权之和。

考虑贪心，为了使得方案最优，我们应该让深度小的节点的点权尽可能的大，于是我们先从根节点开始遍历整个树，设当前这个节点为 $x$，当 $s_x$ 的值为 $-1$ 时，我们令 $f_x=\max_{y \subseteq \operatorname{son(x)}}f_y$ ，如果 $s_x$ 的值不为 $-1$ ，那么就令 $f_x = s_x$。

对于 $x$ 子树中任意一个节点 $y$，如果有 $f_x  > f_y$ ，则为无解。

答案即为 $\sum_{i=2}^{n} f_i-f_{fa_i}$。

上代码



~~~c++
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
using namespace std;
inline int read(){int f=1,res=0;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){res*=10;res+=ch-'0';ch=getchar();}return f*res;}
inline void write(int x){if(x<0){putchar('-');write(-x);}else if(x<=9){putchar(x+'0');}else{write(x/10);putchar((x%10)+'0');}return;}
struct edge{
	int u,v,w;
}e[2000005];
int n,s[2000005];
int first[2000005],nxt[2000005],fa[2000005],cnt;
int f[2000005];
int a[2000005];
int ans;
bool vis[2000005];
void add(int u,int v,int w){
	cnt++;
	e[cnt]=(edge){u,v,w};
	nxt[cnt]=first[u];
	first[u]=cnt;
	return;
}
void dfs(int x){
	int k=first[x];
	vis[x]=1;
	while(k!=-1){
		if(!vis[e[k].v]){
			if(f[e[k].v]==0x7fffffff)f[e[k].v]=f[x];
			ans+=f[e[k].v]-f[x];
			dfs(e[k].v);
		}
		k=nxt[k];
	}
	vis[x]=0;
	return;
}
void dfs1(int x){
	vis[x]=1;
	int k=first[x];
	int tmp=0x7fffffff;
	while(k!=-1){
		if(!vis[e[k].v]){
			dfs1(e[k].v);
			tmp=min(tmp,f[e[k].v]);
		}
		k=nxt[k];
	}
	if(s[x]==-1)f[x]=tmp;
	else{
		if(s[x]>tmp){
			puts("-1");
			exit(0);
		}
		f[x]=s[x];
	}
	vis[x]=0;
	return;
}
signed main(){
	memset(first,-1,sizeof(first));
	n=read();
	for(int i=2;i<=n;i++){
		int v=read();fa[i]=v;
		add(i,v,0),add(v,i,0);
	}
	for(int i=1;i<=n;i++){
		s[i]=read();
	}
	dfs1(1);
	ans=s[1];
	dfs(1);
	write(ans);
	return 0;
}
/*
hap
*/
~~~



---

## 作者：zym20249_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1098A)

## 题意
有 $n$ 个节点，构成了一个树，点权为 $a_i$，每个节点的 $s_i$ 表示从这个节点到根节点的点权总和。$h_i$ 为深度，$p_i$ 为他的父节点，编号为偶数的 $s_i$ 并不知道，要找出一种使得树中所有节点权值总和最小的方式。

## 思路
通过贪心的思想，我们可以推出在深度更高的节点权值越大越好。所以我们可以看每一个编号为奇数的，查看他的爷爷节点，用自己的 $s_i$ 减掉爷爷节点的 $s_i$，然后让父亲节点更大。至于为什么让深度更低的越大越好，我们可以推理一下：
- 我们可以构建一个二叉树，有两个叶子节点为 $y_1$ 和 $y_2$，父亲节点为 $x$，$y_1$ 的路径权值和为 $s_4$，$y_2$ 的路径权值和为 $s_5$，爷爷节点权值为 $1$，则$2x+2+y_1+y_2=s_4+s_5$，我们设 $t$ 为 $2x+y_1+y_2$ 所以 $x+t-2x$ 就是 $t-x$，而这里的 $t$ 为 $2x+y_1+y_2$ 所以当 $x$ 更大时总共的权值和最小。
- 如果你理解能力强我们也可以简单的理解为当 $x$ 每加 $1$，$y_1$ 和 $y_2$ 就可以多减 $1$ 来使得总共的权值和最小。

---

## 作者：Cure_Wing (赞：0)

[CF1098A Sum in the tree](https://www.luogu.com.cn/problem/CF1098A)

### 思路

我们总能想到一个事情，如果一个节点的儿子都至少要加上 $k$，那么把这个 $k$ 加在这个节点一定是不劣的。因为儿子的个数总不小于 $1$（叶子节点除外）。

$1$ 号节点的赋值肯定是 $s_1$。看到限制全在奇数行，根据上一段的思想，我们肯定让赋值越上面越好。于是对于偶数行的节点，我们计算下一行的儿子的最小和，用这个数减去它父亲的 $s$ 值就是在这个节点可以放的最大值。看的出来，如果这个差值是负数，显然无法成立，判定无解。对于奇数行的数，我们计算它应得和与父亲的差值，这是它必填的最小值。同样的，如果这个差值是负数，也一定无法满足，得到无解。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using std::cin;using std::cout;
constexpr int N=100005,inf=2e9;
int n,v,s[N];
long long ans;
std::vector<int>edge[N];
inline void down(int u,int fa,int val,int deep){
	if(deep&1){
		if(s[u]<val){cout<<-1;exit(0);}//差值为负必无解
		ans+=s[u]-val;//奇数行必填最小值
		for(int i:edge[u]) down(i,u,s[u],deep+1);
	}else{
		int minn=inf;
		for(int i:edge[u]) minn=std::min(s[i],minn);//偶数行取最小和
		if(minn-val<0){cout<<-1;exit(0);}//差值为负必无解
		if(minn!=inf) ans+=minn-val;//注意叶子节点的特判
		for(int i:edge[u]) down(i,u,minn,deep+1);
	}
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;
	for(int i=2;i<=n;++i){
		cin>>v;
		edge[v].push_back(i);
	}
	for(int i=1;i<=n;++i) cin>>s[i];
	down(1,0,0,1);
	cout<<ans;
	return 0;
}
```

---

## 作者：eb0ycn (赞：0)

传送门：[CF1098A](https://www.luogu.com.cn/problem/CF1098A)

## 题意

给定一个以 $1$ 为根节点，大小为 $n$ 的树。根节点深度为 $1$。

树上原本每个节点都有一个非负权值 $a_i$，记 $s_i$ 表示从 $i$ 号节点到根节点的路径上所有点的权值和，包括根节点及其本身。

现在给你每个节点的 $s_i$。深度为偶数的节点的 $s_i$ 为 $-1$，表示该节点的 $s_i$ 未知。

请你还原树的每个节点的权值 $a_i$。使得其满足所有深度为奇数的节点的 $s_i$。并输出所有满足情况的方案中，$\sum a_i$ 的最小值。

如果无解，则输出 $-1$。

## 思路（注意这不是最优做法）

首先无解的条件很好推出来：儿子节点的 $s$ 值小于它的祖先。（$-1$ 的情况简单特判一下）

一个节点的深度越小，影响的节点越多。所以在合法范围内我们尽量让父亲节点的 $a$ 值大一点。类似于树形 dp，如果当前节点的深度为奇数，$s_u \gets \min\{s_v\}$，否则 $s_u$ 不变。因为奇数深度的点 $s$ 值可以改变，而偶数深度 $s$ 值固定。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n,tot,s[200001],head[200001],nxt[200001],to[200001],p[200001],st[200001],top,u,maxn[200001];
void add(int x,int y){nxt[++tot]=head[x],head[x]=tot,to[tot]=y;}
ll ans;
bool check(){
	st[++top]=1,maxn[1]=s[1];
	while(top){ 
		u=st[top--];
		for(int i=head[u];i;i=nxt[i]){
			if(s[to[i]]==-1)maxn[to[i]]=maxn[u];
			else if(s[to[i]]<maxn[u])return 0*(top=0);
			else maxn[to[i]]=s[to[i]];
			st[++top]=to[i];
		}
	}return 1;
}
void dfs(int x){
	ll ret=0x3f3f3f3f3f3f3f3f;
	for(int i=head[x];i;i=nxt[i])dfs(to[i]),ret=min(ret,1ll*s[to[i]]);
	if(s[x]!=maxn[x]){
		if(!head[x])s[x]=maxn[x];
		else s[x]=ret;
	}
	for(int i=head[x];i;i=nxt[i])ans+=s[to[i]]-s[x];
}
int main(){
	scanf("%d",&n);for(int i=2;i<=n;++i)scanf("%d",p+i),add(p[i],i);
	for(int i=1;i<=n;++i)scanf("%d",s+i);
	if(!check())return 0*printf("-1");dfs(1);
	return 0*printf("%lld",ans+s[1]);
}
```


---

## 作者：FiraCode (赞：0)

## 思路：
考虑贪心，对于一个深度为偶数的点，那么显然将它取到它子树中每个数的权值最小。

比如这组数据：
```
5
1 2 2 3
1 -1 2 3 -1
```

考虑在 $2$ 处设 $a_2 = 1$，这样可以使得 $a_3$ 和 $a_4$ 同时减一。

## Code：
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

int n;
int s[100010];
vector<int> e[100010];
int sum;

void dfs(int u, int sfa, int fa = -1) {
	if (s[u] != -1) {
		if (s[u] < sfa) {
			puts("-1");
			exit(0);
		}
		sum += s[u] - sfa;
		for (auto v : e[u]) {
			if (v != fa)
				dfs(v, s[u], u);
		}
	} else {
		int minn = 1 << 30;
		for (auto v : e[u]) {
			if (v != fa)
				minn = min(minn, s[v] - sfa);
		}
		if (minn < 0) {
			puts("-1");
			exit(0);
		}
		if (minn != 1 << 30)
			sum += minn;
		for (auto v : e[u])
			if (v != fa)
				dfs(v, sfa + minn, u);
	}
}

signed main() {
	scanf("%lld", &n);
	for (int i = 2; i <= n; ++i) {
		int fa;
		scanf("%lld", &fa);
		e[fa].push_back(i);
		e[i].push_back(fa);
	}
	for (int i = 1; i <= n; ++i) scanf("%lld", &s[i]);

	dfs(1, 0);

	printf("%lld\n", sum);

	return 0;
}
```

---

## 作者：PeyNiKge (赞：0)

### 题意描述

给定一棵有根树，树根为 $1$ 号节点，每个点有一个**非负**权值 $a$，给出深度为奇数的点到根路径上点的权值和 $s$，求树的所有节点权值和的最小是多少。

### 题目分析

考虑贪心。

显然，$a_1=s_1$。

对于一个深度为偶数的点 $u$，考虑 $u$ 的每个子节点 $v$, 对 $u$ 权值的影响。

首先，我们可以找到 $u$ 的子节点中 $s_v$ 最小节点 $v$。

设 $u$ 的父节点为 $f$。

我们可以令 $a_v=0$，$a_u=s_f-s_v$。

然后，对于其他子节点 $v'$，$a_{v'}=s_{v'}-s_{f}-a_{u}$。

可以证明这样是最优的情况。

### 代码

```c++
#include<bits/stdc++.h>
#define int long long
#define PII pair<int, int>
#define Kg putchar(' ')
#define Ed puts("")
#define inf 0x7fffffff
#define INF 0x7fffffffffffffff
using namespace std;
const int N = 2e5 + 10, M = 5e3 + 10;
void read(int &ans){ans = 0;int f = 1;char ch = getchar();while(ch < '0' || ch > '9'){if(ch == '-'){f = -1;}ch = getchar();}while(ch >= '0' && ch <= '9'){ans = (ans << 1) + (ans << 3) + (ch ^ 48), ch = getchar();}ans *= f;}
void print(int x){if(x < 0){putchar('-'), print(-x);}else if(x < 10){putchar(x % 10 + '0');}else{print(x / 10);putchar(x % 10 + '0');}}
struct Graph{
	int hd[N], cnt;
	struct edge{int nt, to, w;}e[N * 2];
    Graph(){memset(e, 0, sizeof(e)), memset(hd, 0, sizeof(hd)), cnt = 0;}
    void clear(){memset(e, 0, sizeof(e)), memset(hd, 0, sizeof(hd)), cnt = 0;}
    void add(int x, int y){e[++cnt].nt = hd[x], hd[x] = cnt, e[cnt].to = y;}
    void add(int x, int y, int z){e[++cnt].nt = hd[x], hd[x] = cnt, e[cnt].to = y, e[cnt].w = z;}
	#define Son(G, u) for(int iKKJs = G.hd[u], v = G.e[iKKJs].to, w = G.e[iKKJs].w; iKKJs; iKKJs = G.e[iKKJs].nt, v = G.e[iKKJs].to, w = G.e[iKKJs].w)
}G;
int n, a[N], s[N];
int dep[N];
void dfs(int u, int F){
	bool flag = false;
	int mn = inf;
	Son(G, u){
		if(v == F) continue;
		dep[v] = dep[u] ^ 1;
		dfs(v, u);
		mn = min(mn, s[v]);
		flag = true;
	}
	if(dep[u] && flag){
		a[u] = mn - s[F];
		if(mn < s[F]){
			print(-1);
			exit(0);
		} 
		Son(G, u){
			if(v == F) continue;
			a[v] = s[v] - s[F] - a[u];
		}
	}
}
int mn, ans;
signed main(){
	read(n);
	for(int i = 2, p; i <= n; i++){
		read(p);
		G.add(i, p), G.add(p, i);
	}
	for(int i = 1; i <= n; i++){
		read(s[i]);
	}
	dfs(1, 0);
	a[1] = s[1];
	for(int i = 1; i <= n; i++){
		ans += a[i];
	}
	print(ans);
	return 0;
}

```

---


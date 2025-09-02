# Strange Function

## 题目描述

### 题面描述

定义函数 $f$：$f(x)$ 为所有满足 $x_i>x_{1,2,\cdots,i-1}$ 的 $x_i$ 组成的序列，例如 $f[3,1,2,7,7,3,6,7,8]=[3,7,8]$。

给出两个序列 $a,b$，你可以删掉 $a$ 中的一些元素。删掉 $a_i$ 的代价为 $p_i$。你需要求出最小代价使得 $f(a)=b$ 或给出无解。

## 样例 #1

### 输入

```
11
4 1 3 3 7 8 7 9 10 7 11
3 5 0 -2 5 3 6 7 8 2 4
3
3 7 10```

### 输出

```
YES
20```

## 样例 #2

### 输入

```
6
2 1 5 3 6 5
3 -9 0 16 22 -14
4
2 3 5 6```

### 输出

```
NO```

# 题解

## 作者：Alex_Wei (赞：13)

> [LG 传送门](https://www.luogu.com.cn/problem/CF1334F) & [CF 传送门](https://codeforces.ml/problemset/problem/1334/F)。

> 题意简述：

> 定义序列函数 $f(x)$：所有满足 $x_i>x_{1\cdots i-1}$ 的 $x_i$ 组成的序列。如 $f[3,1,2,7,7,3,6,7,8]=[3,7,8]$。

> 给出三个序列 $a,p,b$，删除 $a_i$ 的代价为 $p_i$（$p_i$ 可能为负）。求使 $f(a)=b$ 的最小代价。无解输出 $\texttt{NO}$。

---

显然如果 $b$ 不是 $a$ 的子序列肯定无解，否则一定有解。

**按照 $a_i$ 从小到大** DP，设 $f_i$ 为以 $i$ 结尾的最小代价：

- 如果 $a_i\notin b$，则忽略。
- 如果 $a_i\in b$，设 $a_i=b_j$，则 $f_i=\min_{x=1}^{i-1}(f_x+\operatorname{contri}(x+1,i-1,b_{j-1}))[a_x=b_{j-1}]$。其中 $\operatorname{contri}(l,r,v)$ 为区间 $[l,r]$ 需要被删除的数之和，即 $i\in[l,r]$ 中所有满足 $a_i\geq v$ 或 $q_i<0$ 的 $q_i$ 之和，可以用主席树求出。

主席树常数大又难写？考虑到 $\operatorname{contri}(l,r,b_{j-1})$ 和 $\operatorname{contri}(l,r,b_j)$ 之间只改变了所有满足 $b_{j-1}<a_x\leq b_j$ 的 $q_x$ 的贡献，用树状数组维护即可。

可以看出这样 DP 是 $O(n^2\log n)$ 的。其实并不需要枚举所有 $x$，求 $f_i$ 时：

- 如果这是 $b_j$ 第一次在 $a$ 出现，直接按照上面的方程 DP 即可。
- 否则设 $b_j$ 前一次出现在 $a_y$（即 $y<i$，$a_y=b_j$），则一开始直接计算 $f_i=f_y+\operatorname{contri}(y,i-1)$ 就可以替代所有小于 $y$ 且 $a_x=b_{j-1}$ 的转移。
- 这样每个数只会被转移 $1$ 次，单次时间复杂度 $O(\log n)$（计算 $\operatorname{contri}$ 的 $\log$）。

需要注意边界条件，可以适当设置边界值方便写代码。

判断是否有解 $O(n\log n)$，DP 过程 $O(n\log n)$，总时间复杂度 $O(n\log n)$。在 CF 上跑的飞快。

```cpp
const int N=5e5+5;

vector <int> buc[N];
ll n,m,a[N],b[N],p[N],f[N],c[N];
void modify(int x,int v){while(x<=n)c[x]+=v,x+=x&-x;}
ll query(int x){ll ans=0; while(x)ans+=c[x],x-=x&-x; return ans;}
ll cal(int l,int r){return query(r)-query(l-1);}

int main(){
	n=read()+1,mem(f,0x3f),f[0]=0;
	for(int i=1;i<n;i++)a[i]=read(),buc[a[i]].pb(i);
	buc[0].pb(0),buc[n].pb(n);
	for(int i=1;i<n;i++)p[i]=read(),modify(i,p[i]);
	b[m=read()+1]=n; for(int i=1;i<m;i++)b[i]=read();
	
	for(int i=1;i<=m;i++){
		if(i>1)for(int j=b[i-2]+1;j<=b[i-1];j++)
			for(int k:buc[j])if(p[k]>0)modify(k,-p[k]);
		int pos=-1,sz=buc[b[i-1]].size()-1;
		for(int j=0;j<buc[b[i]].size();j++){
			int k=buc[b[i]][j];
			if(j)f[k]=f[buc[b[i]][j-1]]+cal(buc[b[i]][j-1],k-1);
			while(pos<sz&&buc[b[i-1]][pos+1]<k){
				int l=buc[b[i-1]][++pos];
				f[k]=min(f[k],f[l]+cal(l+1,k-1));
			}
		}
	}
	if(f[n]<1e16)printf("YES\n%lld\n",f[n]);
	else puts("NO");
	
	return 0;
}
```

应该有更简单的方法，到时候再来填坑。

---

Upd on 2020.4.15：把代码改整洁了。

不填坑了，丢个完整代码自己体会（

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N=5e5+5;
int n,m,a[N],b[N],p[N],ind[N];
ll c[N];
void modify(int x,ll v){x++; while(x<=m+1)c[x]+=v,x+=x&-x;}
ll query(int x){x++; ll ans=0; while(x)ans+=c[x],x-=x&-x; return ans;}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	for(int i=1;i<=n;i++)scanf("%d",p+i);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)scanf("%d",b+i),ind[b[i]]=i;
	modify(1,1e18);
	for(int i=1;i<=n;i++){
		ll v,nv;
		if(ind[a[i]])v=query(ind[a[i]]-1);
		modify(0,p[i]);
		if(p[i]>0)modify(lower_bound(b+1,b+m+1,a[i])-b,-p[i]);
		if(ind[a[i]]){
			nv=query(ind[a[i]]);
			if(v<nv)modify(ind[a[i]],v-nv),modify(ind[a[i]]+1,nv-v);
		}
	}
	ll ans=query(m);
	if(ans>1e16)puts("NO");
	else printf("YES\n%lld\n",ans);
	
	return 0;
}
```

---

## 作者：AutumnKite (赞：12)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

### 题解

首先考虑将删去最小的转化成保留最大的。

这种选一个子序列满足什么条件的问题，我们首先考虑一个经典的 DP。

设 $f_{i,j}$ 表示 $a$ 的前 $i$ 个数中选出一个子序列（强制 $i$ 选），进行题目中的操作后得到的序列与 $b_{1\ldots j}$ 相等时的最大权值。

由于我们强制 $i$ 选，所以合法的 $j$ 是唯一的，我们大可不必记录 $j$ 这一维状态。

考虑满足 $a_i=b_j$ 的唯一的 $j$，令 $a_0=b_0=0$，那么有转移
$$f_i=\max_{0\le k < i,a_k=b_{j-1}}\{f_k+\sum_{t=k+1}^{i-1}[a_t\le a_k][p_t > 0]p_t\}+p_i$$

对于当前的 $i$，设
$$g_k=f_k+\sum_{t=k+1}^{i-1}[a_t\le a_k][p_t > 0]p_t$$

考虑将 $i$ 加 $1$ 后 $g_k$ 的变化。对于满足 $0\le k < i$ 的所有 $k$，如果 $p_i\le 0$ 那么 $g_k$ 显然不会改变，否则所有满足 $a_k\ge a_i$ 的 $g_k$ 会加上 $p_i$；对于 $k=i$ 的 $g_k$，有 $g_k=f_i$。

考虑一个以 $a_k$ 为下标的数组，位置 $v$ 的值即为
$$\max_{0\le k < i,a_k=v}\{g_k\}$$

根据上述分析，我们需要在这个数组上支持后缀加、单点取 $\max$、单点查询操作即可。单点取 $\max$ 操作可以拆分为一个单点查询和两个后缀加操作。

后缀加、单点查询可以用树状数组简单地维护。

时间复杂度 $O(n\log n)$。

### 代码

```cpp
const int N = 500005;
const long long INF = 0x3f3f3f3f3f3f3f3fll;

int n, a[N], m, b[N];
long long w[N], sum, f[N];

struct BIT{
	long long c[N];
	
	void add(int x, long long v) { // 后缀加
		for (; x <= n; x += x & -x) {
			c[x] += v;
		}
	}

	long long query(int x) { // 单点查询
		long long s = 0;
		for (; x; x ^= x & -x) {
			s += c[x];
		}
		return s;
	}
} T;

int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
	}
	for (int i = 1; i <= n; ++i) {
		read(w[i]);
		sum += w[i];
	}
	read(m);
	for (int i = 1; i <= m; ++i) {
		read(b[i]);
	}
	T.add(1, -INF);
	for (int i = 1; i <= n; ++i) {
		int j = std::lower_bound(b + 1, b + 1 + m, a[i]) - b;
		if (j <= m && a[i] == b[j]) {
			if (j == 1) {
				f[i] = w[i];
			} else {
				f[i] = T.query(b[j - 1]) + w[i];
			}
		} else {
			f[i] = -INF;
		}
		if (w[i] > 0) {
			T.add(a[i], w[i]);
		}
		long long tmp = T.query(a[i]);
		if (f[i] > tmp) {
			T.add(a[i], f[i] - tmp);
			T.add(a[i] + 1, tmp - f[i]);
		}
	}
	long long ans = T.query(b[m]);
	if (ans > -1e15) {
		printStr("YES");
		print(sum - ans); // 用总和减去最大保留的权值
	} else {
		printStr("NO");
	}
}
```

---

## 作者：luogubot (赞：4)

提供一个 [CF 评论区指出的线性做法](https://codeforces.ml/blog/entry/75877?#comment-601296)。

考虑在 $a,b$ 的前后都添加上 $0$ 与 $n+1$，下标从 $0$ 开始。考虑把 $b_j=a_i$ 的 $a_i$ 设为 $2j$，把 $b_j<a_i<b_{j+1}$ 的 $a_i$ 设为 $2j+1$，限制就变为了保留一个由 $0$ 到 $2m$ 支撑的上升子序列，在第一个 $2i$ 之前不能出现 $2i-1$，这和原限制是等价的，因为就算在 $2i$ 之前出现了超过 $2i$ 的数，也会在之后的限制中被敲掉。

这个重新赋值的过程由于 $b$ 是有序的，可以线性完成。

当 $a_i=2j$ 时，设 $f_i$ 是在前缀 $[0,i]$ 中，仅保证值不超过 $2j$ 的数合法的最小花费，也就是 $i$ 前面允许存在没被删掉的超过 $2j$ 的数。

可以这样转移强制其作为保留的第一个 $2j$：

$$
f_i=\{f_x+\sum_{k=x+1}^{i-1}[p_k<0]p_k\}+\sum_{k=0}^{i-1}[a_k=2j\lor a_k=2j-1][p_k>0]p_k
$$

其中 $x$ 是 $i$ 前面最近的一个 $a_x=2(j-1)$ 的位置，原本是应该枚举 $x$ 取 $\min$ 的，但如果像下面一样转移了 $a_i$ 不作为第一个出现的 $2j$ 情况后，选择最近的一个 $x$ 转移就显然等价了：
$$
f_i=\{f_x+\sum_{k=x+1}^{i} [p_k<0]p_k\}
$$
同理，这里也只需要找最近的一个 $x$ 满足 $a_x=2j$ 就好了，因为最近的一个覆盖了前面的所有转移可能，对负数预处理出前缀和就可以简单实现了。另外，这里 $k$ 上界是 $i$ 的原因为，如果 $p_i<0$，且挖掉 $i$ 更优则可以挖掉，而上面的转移中强制保留作为第一个 $2j$ 则不能挖掉 $i$。

总复杂度 $O(n)$，[提交记录](https://codeforces.com/contest/1334/submission/160690507)。



---

## 作者：Hadtsti (赞：2)

### 题意简述

对于序列 $x$，定义函数 $f(x)$ 为所有满足 $x_i>x_{1,2,\cdots,i-1}$ 的 $x_i$ 组成的序列。给出长为 $n$ 的序列 $a$ 和长为 $m(1\le m\le n\le 5\times 10^5)$ 的序列 $b$，以及长为 $n$ 的价格序列 $p$。现要求从 $a$ 中删除一些元素，使得删除后的 $a$ 序列满足 $f(a)=b$。其中删除第 $i$ 个元素的价格为 $p_i$，求最小的删除价格。

### 题目分析

首先求最小删除价格可以转化为求最大剩余价格。然后最暴力的 DP 是好想的：设 $F_{i,j}$ 表示只考虑 $a$ 的前 $i$ 位时，保留的子序列的 $f$ 值恰好为 $b$ 的前 $j$ 项的最大价值。那么有状态转移方程：

$$
F_{i,j}= \begin{cases}
F_{i-1,j}+\max(0,p_i)\quad &(b_j> a_i)\\
\max(F_{i-1,j}+\max(0,p_i),F_{i-1,j-1}+p_i)\quad &(b_j=a_i)\\
F_{i-1,j}\quad &(b_j<a_i)
\end{cases} 
$$

这样的时间复杂度是 $O(n^2)$，空间复杂度是 $O(nm)$，考虑优化。首先状态里 $i$ 这一维可以滚动数组去掉，然后我们观察状态转移方程，发现它实际上是对 $j$ 这一维进行了区间加、单点查询、单点修改的操作。直接拿一个树状数组维护好了。时间复杂度 $O(n\log m)$，空间复杂度 $O(n+m)$。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[500010],b[500010],p[500010];
long long c[500010]/*树状数组*/,ans;
void add(int l,int r,long long v)//区间加 
{
	r++;
	while((l<=m||r<=m)&&(l^r))
		l<r?(c[l]+=v,l+=l&-l):(c[r]-=v,r+=r&-r);
}
long long ask(int x)//单点查 
{
	long long res=0;
	for(;x;x-=x&-x)
		res+=c[x];
	return res;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i]),ans+=p[i];
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
		scanf("%d",&b[i]);	
	add(1,m,0xcfcfcfcfcfcfcfcfll);//初始值为 -inf 
	for(int i=1;i<=n;i++)
	{
		int id=lower_bound(b+1,b+m+1,a[i])-b;//找到第一个大于等于 a_i 的 b 的下标 
		if(p[i]>0)//第一种转移 
			add(id,m,p[i]);
		if(b[id]==a[i])//第二种转移 
		{
			long long tmp1=ask(id),tmp2=ask(id-1)+p[i];
			if(tmp2>tmp1)
				add(id,id,tmp2-tmp1);
		} 
	}
	ans-=ask(m);//答案是删除的价格，因此用总和减 
	if(ans>1e17)//无解 
		printf("NO");
	else
		printf("YES\n%lld",ans);
	return 0;
}
```


---

## 作者：chenxia25 (赞：2)

eJOI做不动了，来水个以前留下的坑（

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/CF1334F) & [CodeForces题目页面传送门](https://codeforces.com/contest/1334/problem/F)

>题意见洛谷里的翻译。（翻译得够清楚了吧，translated by Alex_Wei/se/qq）

先探索$f(x)=y$且$\forall i\in[1,|y|],y_i=x_{z_i}$的充要条件。显然$z_1=1$。不妨设$z_{|y|+1}=|x|+1$，那么$\forall i\in[1,|y|]$：为了让$(z_i,z_{i+1})$内所有元素都留不下来，前面必定要有元素大于等于它们，又因为$x_{z_i}$留下来了，所以$x_{z_i}$大于前面所有元素，于是$\forall j\in(z_i,z_{i+1}),x_j\leq x_{z_i}$是必要的；为了让$x_{z_{i+1}}$（如果存在的话）留下来，它肯定要大于前面所有元素，即$\forall j\in(z_i,z_{i+1}),x_j<x_{z_{i+1}}$是必要的。由于$y_i<y_{i+1}$（题目保证），综合一下就变成了$\forall i\in[1,|y|],\forall j\in(z_i,z_{i+1}),x_j\leq x_{z_i}$作为必要条件。此时不难发现充分性也成立。over。

不妨令$n=n+1,m=m+1$并令$a_n=n,b_m=m$。设$id=b^{-1}$。就有了一个比较显然的DP：若$a_i\in\{b_j\}$，$dp_i$有意义且表示考虑到位置$i$，若$a_i$是$b$的最后一位，需要花的最小代价。边界$dp_0=0$，目标$dp_n$（$=+\infty$则$\texttt{No}$）（体现了之前在$a,b$结尾分别追加$n+1,m+1$的意义，为了方便让$a$的最后一位也是$b$的最后一位）。

转移的话，考虑枚举决策$j$，将$(j,i)$之间该删的删掉，$p$值为负的也顺带删一下，则

$$dp_i=\min_{j\in[0,i),a_j=b_{id_{a_i}-1}}\left\{dp_j+\sum_{k=j+1}^{i-1}\left[a_k>b_{id_{a_i}-1}\lor p_k<0\right]p_k\right\}$$

这个$\sum$里的东西可以分成两类：$a_k>b_{id_{a_i}-1},p_k\geq0$和$p_k<0$，两种都用前缀和变一下形，然后two-pointers优化一下DP即可。其中第$1$类的前缀和需要值域BIT$\log$求。

$\mathrm O(n\log n)$。（还是挺简单的吧）

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=0x3f3f3f3f3f3f3f3f;
int lowbit(int x){return x&-x;}
const int N=500001,M=N;
int n,m;
int a[N+1],p[N+1],b[M+1];
int id[N+1];
struct bitree{//BIT
	int sum[N+1];
	void init(){memset(sum,0,sizeof(sum));}
	void add(int x,int v){
		while(x<=n)sum[x]+=v,x+=lowbit(x);
	}
	int Sum(int x){
		int res=0;
		while(x)res+=sum[x],x-=lowbit(x);
		return res;
	}
	int _sum(int l,int r){return Sum(r)-Sum(l-1);}
}bit;
int now[M+1];//two-pointers优化DP 
int dp[N+1];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%lld",a+i);
	n++;a[n]=n;
	for(int i=1;i<n;i++)scanf("%lld",p+i);
	cin>>m;
	for(int i=1;i<=m;i++)scanf("%lld",b+i),id[b[i]]=i;
	b[++m]=n;id[n]=m;//追加 
	bit.init();
	memset(now,0x3f,sizeof(now));
	now[0]=0;
	int ne=0;//目前第2类的前缀和 
	for(int i=1;i<=n;i++){//DP 
		if(id[a[i]]){
			if(now[id[a[i]]-1]<inf)dp[i]=now[id[a[i]]-1]+bit._sum(b[id[a[i]]-1]+1,n)+ne;
			else dp[i]=inf;//计算DP值 
			if(p[i]>=0)bit.add(a[i],p[i]);
			else ne+=p[i];//加入a[i]，更新某类的前缀和 
			if(dp[i]<inf)now[id[a[i]]]=min(now[id[a[i]]],dp[i]-bit._sum(a[i]+1,n)-ne);//two-pointers 
//			printf("dp[%lld]=%lld\n",i,dp[i]);
		}
		else{//加入a[i]，更新某类的前缀和 
			if(p[i]>=0)bit.add(a[i],p[i]);
			else ne+=p[i];
		}
	}
	if(dp[n]<inf)cout<<"YES\n"<<dp[n];
	else puts("NO");//目标 
	return 0;
}
```

然鹅听wjz鸽鸽说有$\mathrm O(n)$的方法但是不会~~（orz）~~，为了吊打他，我当然要把$\mathrm O(n)$方法做出来啊（

于是苦思冥想，想怎么不带$\log$地求第$1$类的前缀和，结果发现这就是个二维数点啊怎么可能不带$\log$。。就zbl。于是去看$\mathrm O(n)$[题解](https://codeforces.com/blog/entry/75877?#comment-601296)，恍然大悟，太妙了吧/qiang

不妨重构状态转移方程。从整体来考虑，计算$dp_i$的时候从一开始一共删去了哪些第$1$类元素呢（第$2$类照原来方法计算）？以下标为横坐标，值为纵坐标，不难发现删去的是一个直角顶点在左上角的直角三角形框住的内部，因为随坐标增大，删除的值的下限$b_{id_{a_i}-1}$越高。原来的状态转移方程是延$y$轴的平行线切片的，现在我们延$x$轴的平行线切片，每到计算$dp_i$时就加上切出来的那一片的纵坐标段内所有的元素（因为横坐标是一个前缀），然后two-pointers稍微维护一下即可。至于怎么知道每个元素属于哪个切片？直观上应该是`lower_bound`的，但那样是带$\log$的，于是离线装桶+two-pointers即可线性。

我知道你不懂我在讲什么，没关系的，我自己看懂就可以了（（

$\mathrm O(n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
const int inf=0x3f3f3f3f3f3f3f3f;
const int N=500001,M=N;
int n,m;
int a[N+1],p[N+1],b[M+1];
int id[N+1];
vector<int> pos[N+1];
int lwb[N+1];//two-pointers算出来的lower_bound值 
int add[M+1];//此切片目前应该加的 
int now[M+1];//two-pointers优化DP 
int dp[N+1];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%lld",a+i);
	n++;a[n]=n;
	for(int i=1;i<n;i++)scanf("%lld",p+i);
	cin>>m;
	for(int i=1;i<=m;i++)scanf("%lld",b+i),id[b[i]]=i;
	b[++m]=n;id[n]=m;//追加
	for(int i=1;i<=n;i++)pos[a[i]].pb(i);//装桶 
	for(int i=1,j=1;i<=n;i++){//two-pointers计算lwb 
		if(b[j]<i)j++;
		lwb[i]=j;
	}
	memset(now,0x3f,sizeof(now));
	now[0]=0;
	int ne=0;//目前第2类的前缀和 
	for(int i=1;i<=n;i++){//DP 
		if(id[a[i]]){ 
			if(now[id[a[i]]-1]<inf)dp[i]=now[id[a[i]]-1]+add[id[a[i]]]+ne;
			else dp[i]=inf;//计算DP值 
			if(p[i]>=0)add[lwb[a[i]]]+=p[i];
			else ne+=p[i];//加入a[i]，更新某类的前缀和 
			if(dp[i]<inf)now[id[a[i]]]=min(now[id[a[i]]],dp[i]-ne);//two-pointers 
//			printf("dp[%lld]=%lld\n",i,dp[i]);
		}
		else{//加入a[i]，更新某类的前缀和 
			if(p[i]>=0)add[lwb[a[i]]]+=p[i];
			else ne+=p[i];
		}
	}
	if(dp[n]<inf)cout<<"YES\n"<<dp[n];
	else puts("NO");//目标 
	return 0;
}
```

最终还是要尛$\texttt{\color{black}A\color{red}lex\_Wei}$啊，没有他我根本get不到这题的精髓/cy

---

## 作者：tommymio (赞：1)

非常好的一道 $\text{DP}$ 题。

看到两个序列，大概有一个粗略的想法，设 $f_{i,j}$ 为 $a$ 序列匹配到第 $i$ 位，$b$ 序列匹配到第 $j$ 位的最小代价。~~然后就优化不了了~~

正着想很难想，不如反着想，删去一些元素的最小代价，就是保留最大代价的元素。并且我们发现，固定每个 $a_i$ 就确定了其对应的 $j$。所以修改状态： $f_i$ 为 $a$ 序列匹配到第 $i$ 位，$b$ 序列匹配到第 $j$ 位的最大 $p_i$ 之和，其中 $b_j=a_i$，若不存在这样的 $j$ 则 $f_i=-\infty$。

于是有转移式：

$$
f_i=\max_{k=b_{j-1}}\left\{f_k+\sum_{x=k+1}^{i-1}[a_x\leq a_k \wedge p_k>0]\times p_k\right\}+p_i
$$

暴力转移是 $O(n)$ 的，尝试降低转移时间复杂度。发现求和部分的左边界固定，而右边界单调增，这启发我们用一个 $\text{BIT}$ 维护 $\max$ 里的值。将影响转移的 $p_x$ 的贡献累加上去。

**Show the Code**

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;
int n,m;
ll inf,f[500005],sum[500005];
int p[500005],a[500005],b[500005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void add(int x,ll val) {for(;x<=n;x+=x&(-x)) sum[x]+=val;}
inline ll ask(int x) {ll res=0; for(;x;x-=x&(-x)) res+=sum[x]; return res;}
int main() {
	ll ans=0,s=0;
	n=read(); for(register int i=1;i<=n;++i) a[i]=read();
	for(register int i=1;i<=n;++i) s+=(p[i]=read()); m=read();
	for(register int i=1;i<=m;++i) b[i]=read();
    memset(&inf,0x3f,sizeof(inf));
	add(1,-inf);
	for(register int i=1;i<=n;++i) {
		int x=std::lower_bound(b+1,b+1+m,a[i])-b; f[i]=-inf;
		if(x<=m&&b[x]==a[i]) {f[i]=ask(b[x-1])+p[i];}
		if(p[i]>0) {add(a[i],p[i]);} ll tmp=ask(a[i]);
		if(f[i]>tmp) {add(a[i],f[i]-tmp);add(a[i]+1,tmp-f[i]);} 
	}
	ans=ask(b[m]);
	if(ans>-1e15) {printf("YES\n%lld\n",s-ans);}
	else {printf("NO\n");}
	return 0;
}
```


---

## 作者：FZzzz (赞：1)

比赛的时候死刚 E，最后没刚出来。结束前五分钟听说 F 是 ds，看错题以为是 sb 题，后悔死。

赛后重新想了一下，发现是道好题，半个小时才会。然而还是后悔死，我 E 刚了将近一个小时啊啊啊。

写一下代码马上就不后悔了，这题我调了两天……

~~说不定本来应该去写 G 的？卷积匹配不难写吧（flag）。~~

------------
看错题想了个假贪心，回过来以后发现没法贪心。

那就 dp 咯，设 $dp_{i,j}$ 为当前搞到 $a_i$ 和 $b_j$ 的答案。

这个 dp 的状态就是平方的……个鬼啊！

发现 $j$ 这一维可以直接丢掉。

然后想怎么转移。显然就是枚举后面的每一个等于 $b_{j+1}$ 的点，然后从那个点转移过来。代价就是中间这一段所有需要被删的点，易证即为所有大于 $b_j$ 的点或代价为负的点。

你 dp 的顺序是从大到小（对于 $b$ 来说就是从后往前）对吧，所以你就先插入所有代价为负的点，然后每次处理完一个 $j$ 就把一些点插进树状数组。

看楼上 @Alex_Wei 神仙说可以主席树……其实我感觉主席树还会好写一些（

这样的 dp 是 $O(n^2\log n)$ 的，考虑优化。

优化也很简单，记后缀 min 就可以了……个鬼啊！

其实不用这么麻烦。我们发现其实可以钦定每个点只能转移到它后面的第一个 $b_{j+1}$，然后再从下面一个 $b_j$ 转移过来，就可以达到一样的效果。

我这里还用了一个数组储存每个状态的可达性。

然后就是细！节！一！堆！楼上 @Alex_Wei 神仙说可以加一些边界值简化代码，就我在这瞎分类讨论，自闭了……

代码丢一下吧：
```cpp
#include<algorithm>
#include<vector>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
	while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
const int maxn=5e5+5;
int n,m,b[maxn],p[maxn];
vector<int> v[maxn];
typedef long long ll;
ll dp[maxn];
bool g[maxn];
ll c[maxn];
inline int lowbit(int x){
	return x&-x;
}
void modify(int x,ll k){
	while(x<=n){
		c[x]+=k;
		x+=lowbit(x);
	}
}
ll query(int x){
	ll s=0;
	while(x>0){
		s+=c[x];
		x-=lowbit(x);
	}
	return s;
}
const ll inf=9e18;
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    for(int i=1;i<=n;i++) v[readint()].push_back(i);
    for(int i=1;i<=n;i++) p[i]=readint();
    m=readint();
    for(int i=1;i<=m;i++) b[i]=readint();
    int lst=0;
    for(int i=1;i<=m;i++){
    	lst=upper_bound(v[b[i]].begin(),v[b[i]].end(),lst)-v[b[i]].begin();
    	if(lst==(int)v[b[i]].size()){
    		printf("NO\n");
    		return 0;
		}
		lst=v[b[i]][lst];
	}
	printf("YES\n");
	for(int i=1;i<=n;i++) if(p[i]<0) modify(i,p[i]);
	for(int i=b[m]+1;i<=n;i++) for(int j=0;j<(int)v[i].size();j++){
		int x=v[i][j];
		if(p[x]>0) modify(x,p[x]);
	}
	for(int i=m;i>0;i--){
		for(int j=(int)v[b[i]].size()-1;j>=0;j--){
			int x=v[b[i]][j];
			g[x]=0;
			dp[x]=inf;
			if(i==m){
				g[x]=1;
				dp[x]=query(n)-query(x);
			}
			else{
				int y=upper_bound(v[b[i+1]].begin(),v[b[i+1]].end(),x)-v[b[i+1]].begin();
				if(y<(int)v[b[i+1]].size()){
					y=v[b[i+1]][y];
					if(g[y]){
						g[x]=1;
						dp[x]=min(dp[x],dp[y]+query(y-1)-query(x));
					}
				}
			}
		}
		if(i==0) for(int j=1;j<=b[i];j++) for(int k=0;k<(int)v[j].size();k++){
			int x=v[j][k];
			if(p[x]>0) modify(x,p[x]);
		}
		else for(int j=b[i-1]+1;j<=b[i];j++) for(int k=0;k<(int)v[j].size();k++){
			int x=v[j][k];
			if(p[x]>0) modify(x,p[x]);
		}
		for(int j=(int)v[b[i]].size()-1;j>=0;j--){
			int x=v[b[i]][j];
			if(j<(int)v[b[i]].size()-1){
				int y=v[b[i]][j+1];
				if(g[y]){
					g[x]=1;
					dp[x]=min(dp[x],dp[y]+query(y-1)-query(x-1));
				}
			}
		}
	}
	printf("%lld\n",dp[v[b[1]][0]]+query(v[b[1]][0]-1));
    return 0;
}
```

---

## 作者：Zory (赞：1)

### [CF1334F Strange Function](https://codeforces.com/contest/1334/problem/F)

**题意：**$n \le 5e5$序列a，删除第i个需要花费$|p_i| \le 1e9$，用最小花费使序列前缀max去重后恰得到b

看到luogu题解区神长只好写一发，虽然写的是bit，但因为拷板子懒得做任何优化并没有在cf榜中有什么优势，重在代码复杂度

无脑设 $dp_{i,j}=$匹配到$a_i,b_j$，如果不选i，$b_j<a_i$的 $dp_{i-1,j}+p_i \rightarrow dp_{i,j}$而其他可以不动（但是在p是负数时，能移除就移除），选的时候只需要更新最多一处$b_z=a_i,dp_{i,z} \leftarrow dp_{i-1,z-1}$，总复杂度为$O(nlogn)$

```cpp
const int N=1e6+10;
//树状数组板子
struct BIT
{
    ll bit[N];void clear(ll val=0){ mem(bit,val); }
    int lowbit(int x){return x&-x;}
    void ad(int x,ll c){ while(x<N) bit[x]+=c,x+=lowbit(x); }
    ll ask(int x){ ll ret=0;while(x>=1) ret+=bit[x],x-=lowbit(x);return ret; }

    void ad(int l,int r,ll c){ ad(l,c),ad(r+1,-c);}
    void chmin(int x,ll c){ll now=ask(x);if(c<now) ad(x,x,c-now);}
}dp;//下面的+1都是位移挪出0
//------------------FIXED------------------
int a[N],p[N],b[N],go[N];
void main()
{
    int n=qread();fo(i,1,n) a[i]=qread();fo(i,1,n) p[i]=qread();
    int m=qread();fo(i,1,m) go[b[i]=qread()]=i;dp.ad(1+1,bin(60));
    fo(i,1,n)
        if(p[i]<0)
        {
            dp.ad(0+1,m+1,p[i]);
            if(go[a[i]]){ int z=go[a[i]];dp.chmin(z+1,dp.ask(z-1+1)-p[i]); }
        }
        else
        {
            if(go[a[i]]){ int z=go[a[i]];dp.chmin(z+1,dp.ask(z-1+1)); }
            dp.ad(0+1, lower_bound(b+1,b+m+1,a[i])-b-1+1 ,p[i]);
        }
    ll ans=dp.ask(m+1);if(ans<=1e16) printf("YES\n%lld",ans); else puts("NO");
}
```


---

## 作者：MatrixGroup (赞：0)

## 题意

请找出一个长度为 $n$ 的序列 $a$ 的子序列，使得其所有前缀严格最大值按序组成数组 $b$，而且删除的数的权值之和最小，或报告无解。

$n\le5\times10^5$。

## 解法

不难想到一个 $O(n^2)$ 的 dp：$dp_{i,j}$ 表示 $a_{1\cdots i}$ 的子序列的前缀严格最大值组成了 $b_{1\cdots j}$。

考虑把 $i$ 滚动数组可以把空间优化成 $O(n)$。

发现更新等价于区间加（加一个无用的数）和单点改、单点查（加一个有用的数）。用线段树即可实现。

时间复杂度 $O(n\log n)$。

这是一个很常用的，Educational 的 trick。

---

## 作者：lgswdn_SA (赞：0)

$f(x)$ 为满足 $x_i>x_{1,2,...,i-1}$ 的序列，给定 $a,b$，可以删掉 $a$ 中的某些元素（有自己的删除代价），使得 $f(a)=b$，最小化删除代价。

这里是我想到的一个和题解区树上数组优化转移的题解类似但不同的一个做法。直接上线段树维护 DP。


$f(i,j)$ 表示前 $i$ 个元素（$i$ 随便删不删），目前 $f(a[1,i])=b[1,j]$ 的最小代价。有两种转移。若 $a_{i+1}=b_{j+1}$，则可以更新 $f(i+1,j+1)$。当然所有情况都可以去更新 $f(i+1,j)$，其中部分情况需要讨论一下。

容易发现，对于每个 $i$ 不存在或只存在一个位置使得 $a_{i+1}=b_{j+1}$，所以转移相当于一个单点更新和区间更新。考虑用线段树去维护第二维。从 $f_i\to f_{i+1}$ 的转移可以分为以下几步（如果不存在位置就跳过单点更新就行了）：

- 找到使得 $a_{i+1}=b_{j+1}$ 的位置 $j$，设其为 $pos$。
- 单点问询得到 $f_{i,pos}$。
- 如果 $p_{i+1}$ 为负数那么全局加上 $p_{i+1}$。否则找到最大的 $s$ 使得 $b_s<a_{i+1}$，然后 $f[0,s]$ 区间加 $p_{i+1}$。
- 点更新 $f_{i+1}(pos+1)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int N=1e6+9,inf=0x3f3f3f3f3f3f3f3f;
typedef pair<int,int>pii;

inline long long read() {
	long long res=0, w=1; char c=getchar();
	while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
	while(isdigit(c)) {res=res*10+c-48; c=getchar();}
	return res*w;
}

int n,a[N],p[N],m,b[N],bd[N];

int tot=1,ls[N],rs[N],val[N],tag[N];
void build(int p,int l,int r) {
	val[p]=inf;
	if(l==r) return; int mid=(l+r)/2;
	build(ls[p]=++tot,l,mid), build(rs[p]=++tot,mid+1,r);
}
void pushdown(int p) {
	if(tag[p]) {
		if(val[ls[p]]!=inf) val[ls[p]]+=tag[p], tag[ls[p]]+=tag[p];
		if(val[rs[p]]!=inf) val[rs[p]]+=tag[p], tag[rs[p]]+=tag[p];
		tag[p]=0;
	}
}
void add(int k) {if(val[1]!=inf) val[1]+=k, tag[1]+=k;}
void add(int p,int l,int r,int x,int y,int k) {
	if(l==x&&r==y) {if(val[p]!=inf) val[p]+=k, tag[p]+=k; return;}
	int mid=(l+r)/2; pushdown(p);
	if(y<=mid) add(ls[p],l,mid,x,y,k);
	else if(x>mid) add(rs[p],mid+1,r,x,y,k);
	else add(ls[p],l,mid,x,mid,k), add(rs[p],mid+1,r,mid+1,y,k);
	val[p]=min(val[ls[p]],val[rs[p]]);
}
void mdf(int p,int l,int r,int x,int y) {
	if(l==r) {val[p]=min(val[p],y); return;}
	int mid=(l+r)/2; pushdown(p);
	if(x<=mid) mdf(ls[p],l,mid,x,y);
	else mdf(rs[p],mid+1,r,x,y);
	val[p]=min(val[ls[p]],val[rs[p]]);
}
int qry(int p,int l,int r,int x) {
	if(l==r) return val[p];
	int mid=(l+r)/2; pushdown(p);
	if(x<=mid) return qry(ls[p],l,mid,x);
	else return qry(rs[p],mid+1,r,x);
}

signed main() {
	n=read();
	rep(i,1,n) a[i]=read();
	rep(i,1,n) p[i]=read();
	m=read();
	rep(i,1,m) b[i]=read(), bd[b[i]]=i;
	build(1,0,m); mdf(1,0,n,0,0);
	rep(i,0,n-1) {
		int pos=bd[a[i+1]]-1,ff=0;
		if(pos>=0) ff=qry(1,0,m,pos);
		if(p[i+1]<=0) add(p[i+1]);
		else {
			int pq=lower_bound(b+1,b+m+1,a[i+1])-b-1;
			add(1,0,m,0,pq,p[i+1]);
		}
		if(pos>=0) mdf(1,0,m,pos+1,ff);
	}
	if(qry(1,0,m,m)==inf) puts("NO");
	else printf("YES\n%lld\n",qry(1,0,m,m));
	return 0;
}
```



---

## 作者：NaCN (赞：0)


定义序列函数 $f(x)$ ：所有满足 $x_i>x_{1\cdots i-1}$
组成的序列。如 $f[3,1,2,7,7,3,6,7,8]=[3,7,8]$

给出三个序列 $a,p,b$ ，删除 $a_i$的代价为 $p_i$（$p_i$可能为负）。求使 $f(a)=b$ 的最小代价。无解输出$NO$。
<!--more-->
一切都要从简单开始，可以考虑$b[i]->b[i+1]$这么转移。

枚举$i=1..m$。设$dp[pos[b[i]]]$表示若选中需要的删除的数字最小值。

显然枚举所有$dp[pos[b[i-1]]$转移过来。为了表示清楚，我设$r$为某个$b[i]$的位置。$l$为$b[i-1]$的某个位置则
$dp[r]=dp[l]+sum(l,r,v\geq b[i-1] \ or \ p[i]<0)$

观察到这一步因为$b[i]$单调，所有可以每次删去一部分$<b[i-1]$，然后树状数组查询。但是这样会$TLE$

因为对于每个状态$dp[pos[b[i]]]$需要重复枚举。由于$pos[b[i]]$是单调增的，并且满足要求的$pos[b[i-1]]$也随之增多，这里可以单调判断。考虑$dp[pos[b[i]][j]]=dp[pos[b[i]][j-1]]+sum(pos[b[i]][j-1]],pos[b[i]][j]],v\geq b[i-1] \ or \ p[i]<0)$。直接转移即可。

+ 注意转移边界开闭
+ 注意启始的状态边界


<details>
  <summary>代码</summary>


```c++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
#include <stack>
using namespace std;
typedef long long ll;
#define pii pair<int, int>
#define mk make_pair
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const ll infll = 1e18;
ll tr[N], n;
void modify(int x, int v)
{
    while (x <= n)
        tr[x] += v, x += x & -x;
}
ll query(int x)
{
    ll ans = 0;
    while (x)
        ans += tr[x], x -= x & -x;
    return ans;
}
ll cal(int l, int r) { return query(r) - query(l - 1); }
ll dp[N];
vector<int> pos[N];
int p[N], a[N], b[N], m;
int main()
{
    bool flag = 1;
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), pos[a[i]].push_back(i);
    for (int i = 1; i <= n; i++)
        scanf("%d", &p[i]), modify(i, p[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &b[i]);
    int cnt = 1;
    for (int i = 1; i <= n; i++)
        if (cnt <= m && a[i] == b[cnt])
            ++cnt;

    if (cnt <= m)
        return puts("NO"), 0;
    b[0] = 0;
    pos[0].push_back(0);
    a[n + 1] = n + 1;
    pos[a[n + 1]].push_back(n + 1);
    b[m + 1] = n + 1;
    for (int i = 1; i <= m + 1; i++)
    {
        if (i > 1)
            for (int j = b[i - 2] + 1; j <= b[i - 1]; j++)
                for (int k : pos[j])
                    if (p[k] > 0)
                        modify(k, -p[k]);
        int now = b[i];
        int pre = b[i - 1];

        //cout << "---" << b[i] << endl;
        int t = 0;
        for (int j = 0; j < pos[now].size(); j++)
        {
            int r = pos[now][j];

            dp[pos[now][j]] = infll;
            if (j)
                dp[pos[now][j]] = dp[pos[now][j - 1]] + cal(pos[now][j - 1], pos[now][j] - 1);
            int cnt = 0;
            for (; t < pos[pre].size() && pos[pre][t] < pos[now][j]; t++)
            {
                int l = pos[pre][t];
                //cout << r << " " << l << endl;
                if (dp[l] != infll)
                    dp[r] = min(dp[r], dp[l] + cal(l + 1, r - 1));
            }
        }
    }

    printf("YES\n%lld\n", dp[n + 1]);
}
```
  </details>
  

---


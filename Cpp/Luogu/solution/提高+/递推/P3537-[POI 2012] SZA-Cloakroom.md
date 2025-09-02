# [POI 2012] SZA-Cloakroom

## 题目描述

每年，Byteotia 举行富人聚会。 他们聚在一起炫耀他们的收入、Lebytene 的鞋子和其他奢侈品。 当然，并不是所有这些骄傲的物品都会被带入宴会——大衣、夹克、雨伞等会被留在衣帽间，离开时再取走。 不幸的是，一伙 Byteotia 小偷计划闯入衣帽间，偷走其中的一部分物品。 此时此刻，团伙的头目正在审查其他团伙成员提出的抢劫计划（他们是民主的！）。 计划通常如下：小偷在时间 $m_j$ 闯入衣帽间，拿走价值正好为 $k_j$ 的物品并逃跑，整个抢劫过程耗时 $s_j$。 团伙头目首先想知道这些计划中哪些是可行的，哪些不可行。 一个计划是可行的，如果在时间 $m_j$ 可以收集总价值为 $k_j$ 的物品，并且直到 $m_j+s_j$ 时刻没有人出现取回任何被盗物品（在这种情况下，他们会通知保安，抢劫就会失败）。 特别地，如果在时间 $m_j$ 不可能选择总价值正好为 $k_j$ 的物品，那么计划不可行，因此被拒绝。 知道每件物品的存放和取回时间，确定哪些计划是可行的，哪些不可行。 我们假设在抢劫开始的那一刻留在衣帽间的物品已经可以被偷走（见例子）。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
6 2 7
5 4 9
1 2 4
2 5 8
1 3 9
5
2 7 1
2 7 2
3 2 0
5 7 2
4 1 5```

### 输出

```
TAK
NIE
TAK
TAK
NIE```

# 题解

## 作者：MloVtry (赞：23)

背包。

先把物品按照a排个序，询问离线，按照m排个序。

这样就可以用增添物品的方法让$a_i\leq m$这个条件合法。设$f_k$表示当一些物品的$\sum C_i=k$时，其中$b_i$的最小值的最大化值。

emmmm....就是让这个$b_i$的最小值尽可能大。

DP一下即可。

代码
```cpp
#include<bits/stdc++.h>
#define N 1200000
using namespace std;
struct node
{
	int a,b,c,id;
}a[1010],b[N];
int f[100010],ans[N];
bool comp(node aa,node bb)
{
	return aa.a<bb.a;
}
int n,m;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d%d%d",&a[i].c,&a[i].a,&a[i].b);
	scanf("%d",&m);
	for(int i=1;i<=m;++i) scanf("%d%d%d",&b[i].a,&b[i].b,&b[i].c),b[i].id=i;
	sort(a+1,a+n+1,comp);
	sort(b+1,b+m+1,comp);
	int j=1;f[0]=1e9;
	for(int i=1;i<=m;++i)
	{
		while(j<=n&&a[j].a<=b[i].a)
		{
			for(int k=100000;k>=a[j].c;--k)
			f[k]=max(f[k],min(f[k-a[j].c],a[j].b));
			j++;
		}
		if(f[b[i].b]>b[i].a+b[i].c) ans[b[i].id]=1;
	}
	for(int i=1;i<=m;++i) puts(ans[i]?"TAK":"NIE");
	return 0;
}
```

---

## 作者：Shawk (赞：11)

看这道题的题解都写的有些简单，特此补上一篇稍详细一些的题解（代码有注释）。
* 题目大意

n件物品分别有属性a,b,c.

p个询问分别有属性m,k,s.

对于每个询问给出是否存在满足以下三个条件的情况，有输出`TAK`，否则输出`NIE`。

1. 每个物品$a \leq m$
1. 每个物品$b>m+s$
1. 所有物品c的和等于k

* 解题思路

**考虑暴力**，枚举k的所有组成情况并进行记录，每次询问仅须判断c的和为k的几个数，这样预处理都有$2^{1000}$,妥妥49分TLE。

`q[k][i].a`表示和为k的第i种方案中所有物品a属性的最大值。

`q[k][i].b`表示和为k的第i种方案中所有物品b属性的最小值。
```cpp
//...
struct Node {
	int a, b;
	Node() {}
	Node(int x, int y) {
		a = x; b = y;
	}
};
//...
vector<Node> q[100005];//用q数组记录，便于查询
void Dfs(int x, int big, int small, int sum) {
	if (big > small || sum > 100000) return;
    //剪枝优化，a比b大或总和超过数据范围就不再考虑
	q[sum].push_back(Node(big, small));
	for (int i = x + 1; i <= n; ++i)
		Dfs(i, max(big, a[i]), min(small, b[i]), sum + c[i]);
}
int main() {
	//...
	while (Q--) {
		int m, k, s, f = 0;
		scanf("%d%d%d", &m, &k, &s);
		for (int i = 0; i < q[k].size(); ++i)//枚举每种方案进行判断
			if (q[k][i].a <= m && q[k][i].b > m + s) f = 1;
		puts(f ? "TAK" : "NIE");
	}
	return 0;
}
//错误解法只列出关键部分，提供暴力思路
```
这么大的数据，而且有3个条件需要满足，考虑离线算法。

1. 看第一个条件：每个物品$a \leq m$

将物品按照a的大小排序，询问按照m的大小排序，这样，对于第一个条件满足当前询问的物品，也一定会满足后面的询问的第一个条件，节省了一些时间。

2. 每个物品$b>m+s$，先略过

3. 所有物品c的和等于k

类似于背包问题，需要把背包装满，可以按照背包的思路进行dp。

**`f[k]`表示，在满足$a \leq m$的物品中c属性之和为k的方案中最小的 b 属性的最大值**。

这一点需要重点理解，需要满足每个物品$b>m+s$，就需要最小的b比m+s大就可以，但是c属性的和为k的方案数有可能不止一种，需要找到最优的就是在满足x是这个方案中最小的b属性值的前提下尽可能的找x最大的方案。~~越说越迷糊，看代码可能会好懂一些。~~
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct Node1 {
	int a, b, c;
	bool operator < (const Node1 &b) const {
		return a < b.a;
	}//重载运算符，对物品按a值从小到大排序
}a[1005];
struct Node2 {
	int m, k, s, id;
	bool operator < (const Node2 &b) const {
		return m < b.m;
	}/重载运算符，对询问按m值从小到大排序
}b[1000005];
int n, q, f[100005];//f数组题解中的加粗部分进行了详细的解释
bool ans[1000005];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d%d", &a[i].c, &a[i].a, &a[i].b);
	scanf("%d", &q);
	for (int i = 1; i <= q; ++i)
		scanf("%d%d%d", &b[i].m, &b[i].k, &b[i].s), b[i].id = i;
       //记录编号id，离线排序后便于保存答案
	sort(a + 1, a + n + 1);//对物品按a值从小到大排序
	sort(b + 1, b + q + 1);//对询问按m值从小到大排序
	f[0] = 1 << 30;//初始化f[0]为极大值，防止在运行 min(f[k-a[j].c], a[j].b)时出现结果都是0的情况
	for (int i = 1, j = 1; i <= q; ++i) {
		for (; j <= n && a[j].a <= b[i].m; ++j)//满足条件1：a<=m
			for (int k = 100000; k >= a[j].c; --k)
				f[k] = max(f[k], min(f[k-a[j].c], a[j].b));
		if (f[b[i].k] > b[i].m + b[i].s) ans[b[i].id] = 1;
        //满足条件3：c之和==k
        //满足条件2：b>m+s
	}
	for (int i = 1; i <= q; ++i)
		puts(ans[i] ? "TAK" : "NIE");
    //三目运算符，个人比较喜欢使用，挺方便
	return 0;
}
```


---

## 作者：5k_sync_closer (赞：10)

对一次询问 $m,k,s$，求出在 $a_i\le m$ 的物品中选出一些物品满足 $\sum c_i=k$ 时 $\min b_i$ 最大值 $f$，若 $f>m+s$ 则答案为 `TAK`，否则为 `NIE`。

把物品按 $a$ 从小到大排序，询问按 $m$ 从小到大排序，这样 $a_i\le m$ 的物品集是只加不减的。

设 $f_k$ 表示在目前考虑的物品中选出一些物品满足 $\sum c_i=k$ 时 $\min b_i$ 最大值，

考虑加入物品 $i$ 的贡献，有转移 $f_{k}\gets\max\{f_k,\min\{f_{k-c_i},b_i\}\}$。

则处理一次询问 $m,k,s$ 时，先加入所有 $a_i\le m$ 的物品，然后若 $f_k>m+s$ 则答案为 `TAK`，否则为 `NIE`。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct S
{
    int a, b, c;
} a[1050];
struct Q
{
    int m, k, s, i;
} q[1000050];
int n, m, f[100050];
bool b[1000050];
bool C1(S x, S y) { return x.a < y.a; }
bool C2(Q x, Q y) { return x.m < y.m; }
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d%d%d", &a[i].c, &a[i].a, &a[i].b);
    sort(a, a + n, C1);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i)
        scanf("%d%d%d", &q[i].m, &q[i].k, &q[i].s), q[i].i = i;
    sort(q, q + m, C2);
    f[0] = 1e9;
    for (int i = 0, j = 0; i < m; ++i)
    {
        for (; j < n && a[j].a <= q[i].m; ++j)
            for (int l = 1e5; l >= a[j].c; --l)
                f[l] = max(f[l], min(f[l - a[j].c], a[j].b));
        b[q[i].i] = f[q[i].k] > q[i].m + q[i].s;
    }
    for (int i = 0; i < m; ++i)
        puts(b[i] ? "TAK" : "NIE");
    return 0;
}
```


---

## 作者：翼德天尊 (赞：2)

首先很容易想到将所有物品先按照 $a_i$ 升序排序，去掉一维偏序，然后用背包做。

而为了快速处理询问，我们显然是要预处理的，但是预处理并不好做，我们好像需要对于每一个 $a_i$ 的每一个 $m+s$ 的处理出和能不能到 $k$，十分不好处理，而且空间也肯定存不下。

那怎么办呢？考虑一种可以替代预处理且比预处理更加高效的方式——离线。

不妨将所有询问离线下来，挂在对应的 $a_i$ 上，处理到当前 $a_i$ 的询问时，按照 $b_i$ 从小到大加入背包，依次处理。但是这样的时间复杂度是 $O(n^2k)$ 的，还需要继续优化。

哪里冗余了呢？我们的背包含义是【能否】啊！**bool 数组极大地浪费了我们的转移复杂度**，因为**在相同时间内**我们**转移的信息变少了**。

不妨用 $b_i$ 替代能否，将 $dp_i$ 的含义从能否正好是 $k$ 变成在和为 $k$ 的情况下 $b_i$ 最大的最小值。于是我们就可以快乐转移了。

时间复杂度 $O(nk)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
const int N=1e3+5;
const int M=1e6+5;
const int INF=2e9+6;
int n,dp[M],ans[M],maxk;
struct node{
	int a,b,c;
}p[N];
struct node1{
	int s,k,id; 
	node1 (int s=0,int k=0,int id=0)
		:s(s),k(k),id(id){} 
};
vector<node1> qu[N]; 
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
bool cmp(node x,node y){
	return x.a<y.a;
}
int find(int x){
	int l=1,r=n,sum=-1;
	while (l<=r){
		int mid=l+r>>1;
		if (p[mid].a<=x) l=mid+1,sum=mid;
		else r=mid-1;
	}
	return sum;
}
signed main(){
	n=read();
	for (int i=1;i<=n;i++) p[i].c=read(),p[i].a=read(),p[i].b=read();
	sort(p+1,p+1+n,cmp);
	int q=read();
	for (int i=1;i<=q;i++){
		int m=read(),k=read(),s=read()+m;
		maxk=max(maxk,k);
		int g=find(m);
		if (g!=-1) qu[g].push_back(node1(s,k,i));
	//	cout<<"----------"<<s<<" "<<k<<" "<<i<<"\n";
	}
	dp[0]=INF;
	for (int i=1;i<=maxk;i++) dp[i]=-1;
//	puts("");
//	for (int i=1;i<=n;i++)
//		cout<<p[i].a<<" "<<p[i].b<<" "<<p[i].c<<'\n';
//	puts("");
	for (int i=1;i<=n;i++){
		for (int j=maxk;j>=p[i].c;j--){
			if (dp[j-p[i].c]!=-1)
				dp[j]=max(dp[j],min(p[i].b,dp[j-p[i].c]));
		}
	//	for (int j=0;j<=maxk;j++) cout<<dp[j]<<' ';
	//	puts("");
		int len=qu[i].size();
		for (int j=0;j<len;j++){
			if (dp[qu[i][j].k]>qu[i][j].s) ans[qu[i][j].id]=1;
		}
	}
	for (int i=1;i<=q;i++){
		if (ans[i]==0) puts("NIE");
		else puts("TAK");
	}
	return 0;
} 

```

---

## 作者：IYSY2009I (赞：1)

考虑先将询问和物品分别按 $m$ 和 $a$ 排序。

定义 $f_{i,j}$ （在实际写代码中需要滚掉第一维）表示考虑到第 $i$ 号物品，选的物品恰好为 $j$ 时，$b$ 的最小值最大可能是多少。初始化：

$$f_{0,i}= \begin{cases}0 & x=0 \\ - \infty & x>0\end{cases}$$

转移考虑第 $i$ 个物品选或不选：

$$f_{i,j}=\operatorname{max}(f_{i-1,j},\min(f_{i-1,j-c[i]},b[i]))$$

对于每一组询问，我们找到最大的 $\le m$ 的 $a_i$，当第 $i$ 层状态转移完后，只需要判断 $f_{i,k}>m+s$ 即可。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct obj{
	int a,b,c;
};
obj o[1005];
bool cmp1(obj x,obj y){
	return x.a<y.a;
}
int f[100005];
bool ans[1000005];
struct query{
	int m,k,s,x,id;
};
query q[1000005];
bool cmp2(query a,query b){
	return a.x<b.x;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&o[i].c,&o[i].a,&o[i].b);
	sort(o+1,o+n+1,cmp1);
	o[0].a=2e9;
	int Q;
	scanf("%d",&Q);
	for(int i=1;i<=Q;i++){
		q[i].id=i;
		scanf("%d%d%d",&q[i].m,&q[i].k,&q[i].s);
		int l=0,r=n;
		while(r-l>1){
			int mid=(l+r)>>1;
			if(o[mid].a>q[i].m) r=mid-1;
			else l=mid;
		}
		if(o[r].a<=q[i].m) q[i].x=r;
		else q[i].x=l;
	}
	sort(q+1,q+Q+1,cmp2);
	int zz=1;
	while(!q[zz].x){
		ans[q[zz].id]=0;
		zz++;
	}
	f[0]=2e9;
	for(int j=1;j<=100000;j++)
		f[j]=-1;
	for(int i=1;i<=n;i++){
		for(int j=100000;j>=0;j--)
			if(j>=o[i].c&&f[j-o[i].c]!=-1) f[j]=max(f[j],min(f[j-o[i].c],o[i].b));
		while(q[zz].x==i&&zz<=Q){
			if(f[q[zz].k]>q[zz].m+q[zz].s) ans[q[zz].id]=1;
			else ans[q[zz].id]=0;
			zz++;
		}
	}
	for(int i=1;i<=Q;i++){
		if(!ans[i]) printf("NIE\n");
		else printf("TAK\n");
	}
	return 0;
} 
```


---

## 作者：快乐的大童 (赞：1)

## P3537	[POI2012] SZA-Cloakroom
[题目传送门](https://www.luogu.com.cn/problem/P3537)

这道题看起来是一道 01 背包，但其不平常的数据范围使得我们无法正常进行 01 背包。

将物品按照 $a_i$ 排序，我们考虑记录 $f_{i,j,k}$ 表示前 $i$ 个物品，总体积为 $j$，$b_i$ 最小值为 $k$ 的局面是否合法。转移类似 01 背包，$f_{i,j,k}=f_{i-1,j,k},f_{i,j+c_i,\min(k,b_i)}\leftarrow f_{i-1,j,k}$。时间复杂度 $O(nkb)$，无法通过。

我们发现将 dp 数组的数据类型设为 `bool` 会浪费大量可记录信息，所以我们考虑修改状态定义为 $f_{i,j}$ 表示前 $i$ 个物品，总体积为 $j$，所取物品的 $b_i$ 最小值是多少。转移还是 01 背包，$f_{i,j}=\min(f_{i-1,j},f_{i-1,j-c_i},b_i)$。注意在 $j< c_i$ 时只有 $f_{i,j}=f_{i-1,j}$。处理询问时只需要判断 $f_{p,k}$ 是否大于 $m+s$ 即可，其中 $p$ 是最后一个满足 $a_i\le m$ 的 $i$。

当然这样空间限制会达到 $10^5\times 10^3\times 4\text{B}=381.5\text{MB}$，会 MLE。由于我们需要第一维，所以我们不能按照普通 01 背包优化空间的方式进行优化。所以我们考虑将询问离线并按 $m$ 排序，在排序的过程中，每当 $m$ 变化，就进行相应的 01 背包操作，这样询问时由于已经限制了第一维，我们直接判断 $f_k$ 是否大于 $m+s$ 即可，时间复杂度 $O(nk)$，空间复杂度 $O(k)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define PY puts("TAK")
#define PN puts("NIE")
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define per(a,b,c) for(int a=b;a>=c;a--)
using namespace std;
namespace fastIO{
	template<typename T>void rd(T &x){
		x=0;char ch=getchar();T fl=1;
		while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();};
		while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();};x=x*fl;
	}
	template<typename T,typename ...T1>void rd(T &x, T1 &...x1){rd(x);rd(x1...);}
	template<typename T> void write(T x){
		if(x<0){x=-x;putchar('-');}
		if(x/10)write(x/10);putchar(x%10+'0');
	}
	template<typename T> void write(T x,char op){write(x);putchar(op);}
}using namespace fastIO;
const int maxn=1e3+5,maxm=1e5+5,inf=0x3f3f3f3f;
int n,q;
struct node{
	int x,y,z;
	friend bool operator<(node p,node pp){
		return p.x<pp.x;
	}
}a[maxn];
struct query{
	int m,k,s,num,ans;
	friend bool operator<(query p,query pp){
		return p.m<pp.m;
	}
}qq[maxm*10];
bool cmp(query p,query pp){
	return p.num<pp.num;
}
int f[maxm];
signed main(){
	rd(n);rep(i,1,n)rd(a[i].z,a[i].x,a[i].y);
	rd(q);rep(i,1,q)rd(qq[i].m,qq[i].k,qq[i].s),qq[i].num=i;
	sort(a+1,a+n+1);sort(qq+1,qq+q+1);f[0]=inf;
	int p=1;
	rep(i,1,q){
		while(p<=n&&qq[i].m>=a[p].x){
			per(j,100000,a[p].z)f[j]=max(f[j],min(f[j-a[p].z],a[p].y));
			p++;
		}
		if(f[qq[i].k]>qq[i].m+qq[i].s)qq[i].ans=1;
	}
	sort(qq+1,qq+q+1,cmp);
	rep(i,1,q){if(qq[i].ans)PY;else PN;}
}

```


---

## 作者：mulberror (赞：1)

$$\href{http://blog.chhokmah.cn/index.php/archives/73/}{\Large\texttt{My blog}}$$

----
## 思路要点
考虑将所有的询问离线后进行统一处理。

首先不考虑 $b$ 的限制，那么只需要考虑 $a\leq m$ 这个偏序关系。

为了减少重复的计算，考虑将物品和询问分别按照 $a$ 和 $m$ 排序，然后从小到大依次更新背包即可。

那么显然只需要存在一组 $b$ 满足即可，也就是只需要满足所有的合法方案中每个方案的最小的 $b$ 的最大值 $>m+s$ 即可。

所以我们考虑更换 $DP$ 的状态为 $f[i]$表示之前所有的物品，和为 $i$ 的合法方案中 $b$ 最小值的最大值。

这样只需要在处理完所有物品后查看当前的$f[c]$是否$<m+s$即可，正确性显然。

时间复杂度 $O(nq)$

## 代码
```cpp
#include <bits/stdc++.h>
#define For(i, s, t) for (int i = s; i <= t; i++)
#define inf 0x3f3f3f3f

using namespace std;

const int N = 1005;
const int M = 1e6 + 5;
const int S = 1e5;

struct Query {
  int m, k, s, id;
} query[M];

struct Project {
  int a, b, c;
} p[N];

int n, q, mxz;
int f[S + 5];
int ans[M];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  memset(f, ~0x3f, sizeof f);
  f[0] = inf;
  mxz = 0;
  cin >> n;
  For (i, 1, n) {
    cin >> p[i].c >> p[i].a >> p[i].b; 
    mxz += p[i].c;
  }
  cin >> q;
  For (i, 1, q) {
    cin >> query[i].m >> query[i].k >> query[i].s;
    query[i].id = i;
  }
  sort(p + 1, p + 1 + n, [](Project lhs, Project rhs) {
    return lhs.a < rhs.a;
  });
  sort(query + 1, query + 1 + q, [](Query lhs, Query rhs) {
    return lhs.m < rhs.m;
  });
  int lfp = 1;
  For (i, 1, q) {
    while (lfp <= n && p[lfp].a <= query[i].m) {
      for (int j = min(mxz, S); j >= p[lfp].c; j--) {
        f[j] = max(f[j], min(f[j - p[lfp].c], p[lfp].b));
      }
      lfp++;
    }
    if (f[query[i].k] > query[i].m + query[i].s) {
      ans[query[i].id] = 1;
    }
  }
  For (i, 1, q) {
    cout << (ans[i] ? "TAK" : "NIE") << '\n';
  }
  return 0; 
}
```
## 后言
- 所有的有关**和为k**的问题都大概率可以转化为背包。

- 如果有多个限制条件，且这些限制条件都满足某种偏序，那么可以考虑先排序其中一维，在考虑第二维。

- 问题复杂时，且所有的限制条件相对独立，可以先分开考虑，在合在一起考虑。

---

## 作者：nofind (赞：1)

题意：https://www.luogu.org/problem/P3537

一时思路不开阔,没想出正解(不会告诉你我把k看成了<=100000,0)

首先对于第一个约束,**考虑离线,将物品和询问分别按照a和m排序,之后单指针添加物品即可**

f[i]表示添加物品的c总和为i时的物品中b值最小的那一个能够取到的最大值

对于询问i,判断f[qr[i].k]是否大于qr[i].m+qr[i].s即可(注意不要取等)

最后一点:**数据中物品是先读c的!!!**

code:
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;
const int maxq=1000010;
const int maxK=100010;
int n,Q,maxk;
int f[maxK];
bool ans[maxq];
struct things
{
	int a,b,c;
}th[maxn];
struct Query
{
	int m,k,s,id;
}qr[maxq];
inline int read()
{
	char c=getchar();int res=0,f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=res*10+c-'0',c=getchar();
	return res*f;
}
bool cmp1(things x,things y){return x.a<y.a;}
bool cmp2(Query x,Query y){return x.m<y.m;}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)th[i].c=read(),th[i].a=read(),th[i].b=read();
	Q=read();
	for(int i=1;i<=Q;i++)qr[i].m=read(),qr[i].k=read(),qr[i].s=read(),qr[i].id=i,maxk=max(maxk,qr[i].k);
	sort(th+1,th+n+1,cmp1);sort(qr+1,qr+Q+1,cmp2);
	int j=1;
	f[0]=8423904;
	for(int i=1;i<=Q;i++)
	{
		while(j<=n&&th[j].a<=qr[i].m)
		{
			for(int k=maxk;k>=th[j].c;k--)
				f[k]=max(f[k],min(f[k-th[j].c],th[j].b));
			j++;
		}
		ans[qr[i].id]=(f[qr[i].k]>(qr[i].m+qr[i].s))?1:0;
	}
	for(int i=1;i<=Q;i++)puts(ans[i]?"TAK":"NIE");
	return 0;
}
```


---

## 作者：lyhqwq (赞：1)

# Solution

首先我们将物品按照 $a$ 排序，在将询问离线，按照 $m$ 排序，这样满足询问 $m$ 的限制的物品数就只增不减，我们只需要考虑 $m+s$ 的限制即可。

我们令 $f_{i,j}$ 表示前 $i$ 个物品，价值的和为 $j$。这些物品的 $b$ 的最小值最大是多少。

有显然的转移

$f_{i,j}=\max \{ \min\{f_{k-c_i},b_i\}\}$

如果 $f_{i,j}>m+s$ 那么就输出 TAK，否则输出 NIE。

因为物品是只增不减的，所以复杂度和双指针类似，是 $O(n\max\{k_i\})$ 的，可以通过。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
const int M=100005;
struct node{
    int a,b,c;
}a[N];
struct Tque{
    int id,m,k,s;
}que[N];
int ans[N];
int n,q;
int f[M];
bool cmp1(node x,node y){
    return x.a<y.a;
}
bool cmp2(Tque x,Tque y){
    return x.m<y.m;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d%d",&a[i].c,&a[i].a,&a[i].b);
    sort(a+1,a+1+n,cmp1);
    scanf("%d",&q);
    for(int i=1;i<=q;i++) scanf("%d%d%d",&que[i].m,&que[i].k,&que[i].s),que[i].id=i;
    sort(que+1,que+1+q,cmp2);
    f[0]=1000000000;
    for(int i=1,j=1;i<=q;i++){
        for(;j<=n&&a[j].a<=que[i].m;j++){
            for(int k=100000;k>=a[j].c;k--){
                f[k]=max(f[k],min(f[k-a[j].c],a[j].b));
            }
        }
        ans[que[i].id]=(f[que[i].k]>que[i].m+que[i].s);
    }
    for(int i=1;i<=q;i++){
        if(ans[i]) puts("TAK");
        else puts("NIE");
    }
    return 0;
}

```


---

## 作者：Nuyoah_awa (赞：0)

### 题目分析

我们观察对于每个询问能选的范围：$a_i \le m,b_i >m + s$。

对于暴力，我们可以枚举出每个符合上述条件的物品，对其作背包判断。很明显时间复杂度太大了，过不了。

考虑数据范围：$n\le 1000,k_i \le 10 ^ 5$，我们可以考虑在 $k$ 上做文章，而 $b,m,s$ 数据过大，可以作为判断标准。

于是我们可以定义 $f_{i, j}$ 表示枚举到第 $i$ 个物品，所选物品价值和为 $j$，这些物品 $b$ 的最小值。

转移方程与传统背包类似：

$$f_{i, j} = \max\{f_{i-1, j}, \min\{f_{i-1, j-c_i}, b_i\}\}$$

对于一个询问，我们很容易发现所有 $a_i$ 小于 $m$ 的物品都可以用，所以可以先将物品按照 $a$ 排序，然后找到第一个 $a_i <m$ 的物品，判断 $f_{i, j} > m + s$ 则可以，否则不行。

时间复杂度主要在于 DP，而对于询问，我们可以按照 $m$ 排序，然后用类似双指针的算法处理，所以总时间复杂度是 $\mathcal O(n \times \max\{k_i\})$ 的。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define int long long
using namespace std;
const int N = 1e3 + 5, M = 1e6 + 5, MX = 1e5 + 5, INF = 1e18;
struct node{
    int v, p, d;
}a[N];
struct node1{
    int id, s, tot, t;
}b[M];
int n, Q, f[MX + 5];
bool opt[M];

inline bool cmp(node u, node v)
{
    return u.p < v.p;
}

bool cmp_s(node1 u, node1 v)
{
    return u.s < v.s;
}

signed main()
{
    scanf("%lld", &n);
    for(register int i = 1;i <= n;i++)
        scanf("%lld %lld %lld", &a[i].v, &a[i].p, &a[i].d);
    sort(a + 1, a + n + 1, cmp);
    scanf("%lld", &Q);
    for(register int i = 1;i <= Q;i++)
    {
        scanf("%lld %lld %lld", &b[i].s, &b[i].tot, &b[i].t);
        b[i].id = i;
    }
    sort(b + 1, b + Q + 1, cmp_s);
    f[0] = INF;
    int k = 1;
    for(register int i = 1;i <= n;i++)
    {
        for(register int j = MX;j >= a[i].v;j--)
            f[j] = max(f[j], min(f[j-a[i].v], a[i].d));
        while(k <= Q && b[k].s < a[i+1].p)
        {
            opt[b[k].id] = (b[k].s + b[k].t < f[b[k].tot]) ? true : false;
            k++;
        }
    }
    while(k <= Q)
    {
        opt[b[k].id] = (b[k].s + b[k].t < f[b[k].tot]) ? true : false;
        k++;
    }
    for(register int i = 1;i <= Q;i++)
        printf(opt[i] ? "TAK\n" : "NIE\n");
    return 0;
}
```

---

## 作者：快斗游鹿 (赞：0)

## 思路

因为要满足 $a_i\le m$，很自然地想到把数据离线下来，分别按 $a,m$ 从小到大排序，这样就可以通过每次添加的方式满足这个要求。

因为所有 $b_i$ 都要大于 $m+s$，所以我们可以记 $f_k$ 表示当 $c_i$ 总和为 $k$ 时，能取到的 $b_i$ 的最小值的最大值。每次 $f_k=\max(f_k,\min(f_{k-c_i},b_i))$，其中 $b_i,c_i$ 就是题目中的属性 $b_i,c_i$。初始值 $f_0$ 要设成一个极大值。

每次结束时看看 $f_k$ 是否大于 $m+s$ 就好了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
struct Node{
	int a,b,c;
}e[N];
struct Ask{
	int m,k,s,id;
}q[N];
int n,Q,f[N];
bool ans[N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
bool cmpa(Node xxx,Node yyy){
	return xxx.a<yyy.a;
}
bool cmpb(Ask xxx,Ask yyy){
	return xxx.m<yyy.m;
}
int main(){
	freopen("std.in","r",stdin);
	n=read();
	for(int i=1;i<=n;i++){
		e[i].c=read();e[i].a=read();e[i].b=read();
	}
	Q=read();
	for(int i=1;i<=Q;i++){
		q[i].m=read();q[i].k=read();q[i].s=read();q[i].id=i;
	}
	sort(e+1,e+1+n,cmpa);
	sort(q+1,q+1+Q,cmpb);
	int j=1;f[0]=1e9;
	for(int i=1;i<=Q;i++){
		while(e[j].a<=q[i].m&&j<=n){
			for(int k=1e5;k>=e[j].c;k--){
				f[k]=max(f[k],min(f[k-e[j].c],e[j].b));
			}
			//cout<<f[e[j].c]<<endl;
			j++;
		}
		if(f[q[i].k]>q[i].m+q[i].s)ans[q[i].id]=1;
	}
	for(int i=1;i<=Q;i++){
		if(ans[i])puts("TAK");
		else puts("NIE");
	}
	return 0;
}


```


---

## 作者：Link_Cut_Y (赞：0)

[博客园观看效果更佳](https://www.cnblogs.com/LcyRegister/p/17006672.html)

### 题目大意

有 $n$ 件物品，每件物品有三个属性 $a_i, b_i, c_i (a_i < b_i)$。

再给出 $q$ 个询问，每个询问由非负整数 $m, k, s$组成，问是否能够选出某些物品使得：

1. 对于每个选的物品 $i$，满足 $a_i \leq m$ 且 $b_i > m + s$。

2. 所有选出物品的 $c$ 的和正好是 $k$。

### 分析

如果没有 $a_i \leq m$ 且 $b_i > m + s$ 的条件，明显是个背包。

然而有这两个限制就不好办了。我们可以先把询问离线下来，按照 $m$ 排序（当然 $a_i$ 也要排序），这样就把二维偏序转化成了一维。（大概可以这样理解）。

接下来，我们需要判断在 $\forall a_i \leq m$ 和 $\sum c_i = k$ 满足后 $[\forall b_i > m + s]$ 是否成立。

这个也很好办。我们只需要将背包状态设为 $f_i$ 表示背包容积（即放入的 $c$）大小为 $i$ 时 $b$ 的最小值的最大值。只要这个最小值比 $m + s$ 大，那么就一定合法，否则一定不合法。

最后一定注意输入顺序是 $c, a, b$ 而不是 $a, b, c$！
### 参考代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int N = 1010, M = 1000010;
struct Node {
    int a, b, c;
    bool operator < (const Node& tmp)const {
        return a < tmp.a;
    }
}p[N];
struct Queries {
    int m, k, s, id;
    bool operator < (const Queries& tmp)const {
        return m < tmp.m;
    }
}q[M];
int f[100010];
int n, m;
bool ans[M];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ )
        scanf("%d%d%d", &p[i].c, &p[i].a, &p[i].b);
    sort(p + 1, p + n + 1);
    scanf("%d", &m);
    for (int i = 1; i <= m; i ++ )
        scanf("%d%d%d", &q[i].m, &q[i].k, &q[i].s),
        q[i].id = i;
    sort(q + 1, q + m + 1); // 将限制 A 消除

    int now = 1; f[0] = 0x3f3f3f3f;
    for (int i = 1; i <= m; i ++ ) {
        while (now <= n && p[now].a <= q[i].m) {
            for (int j = 100000; j >= p[now].c; j -- )
                f[j] = max(f[j], min(f[j - p[now].c], p[now].b)); // 背包满足限制 C
            now ++ ;
        }
        if (f[q[i].k] > q[i].m + q[i].s) ans[q[i].id] = true; // 判断限制 B 是否满足
    }

    for (int i = 1; i <= m; i ++ )
        puts(ans[i] ? "TAK" : "NIE");
    return 0;
}
```

---

## 作者：Alex_Wei (赞：0)

> *[P3537 [POI2012]SZA-Cloakroom](https://www.luogu.com.cn/problem/P3537)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

好题，一开始一直在想 $\dfrac {nk\log n}{\omega}$ 的 $0/1$ 背包可行性做法，发现无论如何都不可做。但是**背包问题并不一定只能装 $0/1$**，我们要充分发挥 $f_i$ 的值域带来的信息。

由于背包不可删除，所以**按顺序将物品加入背包**方便回答，故将询问离线处理。

设 $f_i$ 表示要用左端点小于当前位置 $p$ 的所有物品组合出价值 $i$，所需物品右端点最小值的最大值。其中 $p$ 是不断递增的，与此同时回答对应的询问。

不妨设要加入 $(c_i,a_i,b_i)$，根据我们的策略有 $a_i$ 递增，转移方程如下：
$$
f_j=\max(f_j,\min(f_{j-c_i},b_i))
$$
对于一次询问 $(k_j,l_j,r_j)\ (l_j=s_j,r_j=s_j+m_j)$，显然只能用 $a_i\leq l_j$ 的物品，因此对于在加入 $a_i$ 之前先要回答所有 $l_j<a_i$ 的询问才能保证正确性。在此基础上，若 $f_{k_j}>r_j$ 说明可行，否则不可行，这一点结合 $f$ 的定义容易理解。

综上，时间复杂度 $\mathcal{O}(nk+q\log q)$。

```cpp
const int N = 1e5 + 5;
int n, q, f[N], ans[N << 4];
pair <pii, int> item[N];
pair <pii, pii> query[N << 4];
int main(){
	cin >> n, f[0] = 1e9;
	for(int i = 1; i <= n; i++) cin >> item[i].se >> item[i].fi.fi >> item[i].fi.se;
	cin >> q, sort(item + 1, item + n + 1);
	for(int i = 1; i <= q; i++)
		query[i].fi.fi = read(), query[i].se.fi = read(),
		query[i].fi.se = read() + query[i].fi.fi, query[i].se.se = i;
	sort(query + 1, query + q + 1);
	for(int i = 1, p = 1; i <= n + 1; i++) {
		while(p <= q && (query[p].fi.fi < item[i].fi.fi || i == n + 1))
			ans[query[p].se.se] = f[query[p].se.fi] > query[p].fi.se, p++;
		for(int k = N - 1; k >= item[i].se; k--)
			cmax(f[k], min(f[k - item[i].se], item[i].fi.se));
	} for(int i = 1; i <= q; i++) puts(ans[i] ? "TAK" : "NIE");
	return flush(), 0;
}
```

---


# [GDCPC 2023] Base Station Construction

## 题目描述

中国移动通信集团广东有限公司深圳分公司（以下简称``深圳移动``）于 $1999$ 年正式注册。四年后，广东省大学生程序设计竞赛第一次举办。深圳移动与广东省大学生程序设计竞赛一起见证了广东省计算机行业的兴旺与发展。

在建设通信线路的过程中，信号基站的选址是一个非常关键的问题。某城市从西到东的距离为 $n$ 千米，工程师们已经考察了在从西往东 $1, 2, \cdots, n$ 千米的位置建设基站的成本，分别是 $a_1, a_2, \cdots, a_n$。

为了保证居民的通信质量，基站的选址还需要满足 $m$ 条需求。第 $i$ 条需求可以用一对整数 $l_i$ 和 $r_i$ 表示（$1 \le l_i \le r_i \le n$），代表从西往东 $l_i$ 千米到 $r_i$ 千米的位置之间（含两端）至少需要建设 $1$ 座基站。

作为总工程师，您需要决定基站的数量与位置，并计算满足所有需求的最小总成本。

## 样例 #1

### 输入

```
2
5
3 2 4 1 100
3
1 3
2 4
5 5
5
7 3 4 2 2
3
1 4
2 3
4 5```

### 输出

```
102
5```

# 题解

## 作者：sunzz3183 (赞：11)

# P9691 [GDCPC2023] Base Station Construction 题解

## 题意

给定一个长度为 $n$ 的序列 $a$，现在需要选择任意个数，使得选择的数的和最小且对于给定给的 $m$ 个区间 $[l_i,r_i]$，每个区间都有至少一个数被选择。

## 分析

设状态 $f_i$ 为考虑了前 $i$ 个数，并且第 $i$ 个数一定选的最小值。

我们可以把 $a_{n+1}=0$ ，这样 $f_{n+1}$ 就是答案。

转移类似这样：

$$ f_i=\min_j {f_j}+a_i$$

其中，转移需要满足 $m$ 个条件，考虑，对于每一个合法的 $j$，说明 $(j,i)$ 的区间内，没有一个完整的区间，所以我们记录一个数组 $pre$，$pre_i$ 表示能转移到 $i$ 的最小合法的 $j$。

所以完整转移为：

$$ f_i=\min_{pre_i\leq j<i} {f_j}+a_i$$

然后求 $pre$ 的方式为：

$$ pre_i=\max_{r_j<i}{l_j}$$

两个式子分别可以用单调队列优化 $dp$ 和预处理前缀最大值求出来。

## 代码

```cpp
void Main(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    a[++n]=0;
    for(int i=1;i<=n;i++)pre[i]=0;
    m=read();
    for(int i=1;i<=m;i++){
        int l=read(),r=read();
        pre[r+1]=max(pre[r+1],l);
    }
    pre[1]=0;
    for(int i=2;i<=n;i++)pre[i]=max(pre[i],pre[i-1]);
    l=1,r=0;q[++r]=0;
    for(int i=1;i<=n;i++){
        while(l<=r&&q[l]<pre[i])l++;
        f[i]=f[q[l]]+a[i];
        while(l<=r&&f[q[r]]>=f[i])r--;
        q[++r]=i;
    }
    printf("%lld\n",f[n]);
    return;
}
```


---

## 作者：cjh20090318 (赞：6)

很好的单调队列优化 DP 练习题。

## 题意

有 $i$ 个点排成一排，从左到右编号依次为 $1 \sim n$。选择第 $i$ 个点的代价为 $a_i$。

有 $m$ 个要求，第 $i$ 个要求为在 $[l_i,r_i]$ 中至少要选择一个节点。

请你找到代价最小的选择方案使得能够满足所有要求，并给出最小的代价。

## 分析

因为每个点的代价不同，所以不能直接贪心做区间选点问题，但是可以利用类似的思路。

设 $f_i$ 表示前 $i$ 个点中，第 $i$ 个点必选的最小代价。

考虑转移，设转移决策点为 $j$，那么必然要满足的条件是对于所有右端点小于 $i$ 的区间，$j$ 不能小于这些区间的左端点，否则这个区间就会被漏选（因为后面的决策点也选择不了这些漏选的区间）。

设 $x_i$ 表示右端点小于 $i$ 的区间左端点最大值。

然后就可以写出状态转移方程：

$$
f_i = a_i + \min\limits_{j = x_i}^{i-1}f_j
$$

具体实现就将所有区间按右端点从小到大排序，双指针维护最大值。因为这个决策点是单调递增的，所以可以使用单调队列优化。

最终的答案也即：

$$
\min\limits_{j = x_n}^n f_j
$$

时间复杂度 $O(m \log m)$，瓶颈在于区间排序，动态规划部分的时间复杂度为 $O(n+m)$。

## 代码

```cpp
//the code is from chenjh
#include<bits/stdc++.h>
#define MAXN 500005
using namespace std;
typedef long long LL;
int n,m,a[MAXN];
struct SEG{
	int l,r;
	bool operator < (const SEG&B)const{return r<B.r;}//将区间按右端点从小到大排序。
}e[MAXN];
LL f[MAXN];
int q[MAXN],h,t;
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&e[i].l,&e[i].r);
	sort(e+1,e+m+1);
	int l=0;
	h=1,t=0,q[++t]=0;
	for(int i=1,j=1;i<=n;i++){
		f[i]=f[q[h]]+a[i];
		while(h<=t&&f[q[t]]>f[i]) --t;//弹出不优的决策。
		q[++t]=i;
		for(;j<=m&&e[j].r<=i;j++) l=max(l,e[j].l);//双指针维护最大值。
		while(h<=t&&q[h]<l) ++h;//排除过时决策。
	}
	printf("%lld\n",f[q[h]]);
}
int main(){
    int T;scanf("%d",&T);
    while(T--) solve();
    return 0;
}
```

---

## 作者：nr0728 (赞：4)

很明显的 DP。

设 $f_i$ 为考虑前 $i$ 个数且选择第 $i$ 个数的花费最小值。显然 $f_i=\min\limits_{j\ \in\ \sf{选上\ }\it{a_i}\sf{\ 数后前面区间都选到的}\ \it{j}\ \sf{集合}}f_j+a_i$。

现在我们看看如何计算此集合。显然对于每一个限制条件的 $l_i,r_i$，$\forall i\gt r_i$ 至少要从 $f_{l_i}$ 开始，枚举到 $f_{i-1}$，因为这样才能保证这个区间取到数了。当然为了确保前面区间都取到数，我们需要满足所有条件。设 $s$，代表选上 $a_i$ 数后前面区间都选到的 $j$ 集合为 $\{s,{s+1},\cdots,{i-1}\}$，那么 $s$ 为前面所有 $r_i+1$ 对应的 $l_i$ 的最大值。所以只需要对每组限制条件打标记（$tag_{r_i+1}=l_i$），DP 时更新 $s$ 并转移，就可以 $\mathcal O(n^2)$ 实现了。

下面我们考虑如何优化。注意到取的是集合的最小值，而第 $i$ 次我们其实只需要删除集合中：

- $f_{i-1}$。
- 原来的 $s$ 到更新的 $s-1$ 下标的 $f$ 值。

容易发现每个 $f_i$ 最多只会进入一次、出去一次集合。而我们要求集合中最小值，所以可以用 `std::multiset`（这里不用 `set`，因为可能有重复 $f_i$）。时间复杂度 $O(n\log n)$，可以通过。

考试的时候写的代码，有点丑：

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i(a);i<=(b);++i)
#define req(i,a,b) for(int i(a);i>=(b);--i)
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf,ubuf[1<<23],*u=ubuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
template<typename TP> inline TP read(TP &num)
{
	TP x=0;
	int f=0;
	char ch=getchar();
	while(ch<48||ch>57) f|=ch=='-',ch=getchar();
	while(48<=ch&&ch<=57) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return num=f?-x:x;
}
template<typename ...Args> inline void read(Args &...args)
{
	(read(args),...);
}
template<typename TP> inline void write(TP x)
{
	(x<0)?(putchar('-'),x=-x):0;
	(x>9)?(write(x/10),0):0;
	putchar((x%10)^48);
}
template<typename TP> inline void writeln(TP x)
{
	write<TP>(x);
	puts("");
}
int T,n,a[500001],q,l[500001],r[500001],f[500001],st;
int id[500001];
basic_string<int> lim[500001];
multiset<int> s;
// f[i] denotes the minimum of (ensure previous conditions are satisfied, and choose i-th number)
inline void solve()
{
	st=0;
	rep(i,1,n)
	{
		f[i]=9e18;
		if(lim[i].size()) st=max(st,lim[i].back());
		rep(j,st,i-1) f[i]=min(f[i],f[j]);
		f[i]+=a[i];
	}
	int ans=9e18;
	rep(i,l[id[q]],r[id[q]]) ans=min(ans,f[i]);
	writeln(ans);
}
signed main()
{
    read(T);
    while(T--)
    {
    	read(n);
    	rep(i,1,n) read(a[i]),lim[i].clear(),f[i]=0;
    	read(q);
    	rep(i,1,q)
    	{
    		read(l[i],r[i]);
    		lim[r[i]+1]+=l[i];
    	}
    	iota(id+1,id+q+1,1);
    	sort(id+1,id+q+1,[](int x,int y){return l[x]<l[y];});
    	rep(i,1,n) sort(lim[i].begin(),lim[i].end());
    	st=0;
    	if(n*n<=1e8)
    	{
    		solve();
    		continue;
    // 		return 0;
    	}
    	s.clear();
    	rep(i,1,n)
    	{
    		s.emplace(f[i-1]);
    		if(lim[i].size())
    		{
    			int ost=st;
    			st=max(st,lim[i].back());
    			// st ~ i-1
    			rep(j,ost,st-1) s.erase(s.find(f[j]));
    		}
    		f[i]=(s.size()?*s.begin():0)+a[i];
    	}
    	int ans=9e18;
    	rep(i,l[id[q]],r[id[q]]) ans=min(ans,f[i]);
    	writeln(ans);
    }
	return 0;
}
```

---

## 作者：xtzqhy (赞：2)

CSP 因为这个爆了，所以来写题解。

如果没有点权，那么这是一个经典贪心问题。

但现在有点权，所以考虑 DP。

设 $f_i$ 表示考虑前 $i$ 个位置，且最后一个放在 $i$ 的最小代价，那么转移为
$$
f_i=\min f_j + a_i
$$
可以发现，一个合法的 $j$ 必须满足限制：在 $(j,i)$ 中不能有一个完整的区间。

设 $pre_i$ 表示 $i$ 的第一个合法位置，则转移应为
$$
f_i=\min_{pre_i\le j < i} f_j+a_i
$$
固定区间转移，一看就很单调队列。

所以预处理出来 $pre_i$ 后单调队列优化一下即可。

为了方便求答案，我们在 $n+1$ 处放一个虚点，那么答案就是 $f_{n+1}$。

复杂度 $O(n)$。
```cpp
#include"bits/stdc++.h"
#define re register
#define int long long
using namespace std;
const int maxn=5e5+10;
int n,m;
int a[maxn],pre[maxn],q[maxn],f[maxn];
inline void solve(){
	cin>>n;
	for(re int i=1;i<=n;++i) cin>>a[i];a[++n]=0;
	for(re int i=1;i<=n;++i) pre[i]=0,f[i]=0;
	cin>>m;
	for(re int i=1,l,r;i<=m;++i){
		cin>>l>>r;
		pre[r+1]=max(pre[r+1],l);
	}
	for(re int i=1;i<=n;++i) pre[i]=max(pre[i],pre[i-1]);
	int l=1,r=0;
	q[++r]=0;
	for(re int i=1;i<=n;++i){
		while(l<=r&&q[l]<pre[i]) ++l;
		f[i]=f[q[l]]+a[i];
		while(l<=r&&f[q[r]]>=f[i]) --r;
		q[++r]=i;
	}
	cout<<f[n]<<'\n';
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
#endif	
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T;cin>>T;while(T--) solve();
    return 0;
}
```

---

## 作者：coding_goat (赞：2)

前置知识：[单调队列](https://www.luogu.com.cn/problem/P1886)。

去年还是蒟蒻的时候在洛谷上的比赛中看过这题，现在回来补了 qwq。

设 $f_i$ 表示当前位置为 $i$，且必须选 $i$ 的最小花费。所以我们可以得到：

$$f_i=f_j+v_i$$

其中 $j$ 到 $i$ 之间没有任何完整的区间（因为如果有的话，那么从 $f_j$ 转移过来会导致那个区间没有基站）。

所以我们设 $pre_i$ 为距离位置 $i$ 最远且中间没有包含完整区间的最大位置，用前缀计算一下即可。则每次转移就是：

$$f_i=(\min_{pre_i\le j <i} f_j )+v_i$$

看到转移式长这样，我们可以考虑用单调队列维护 $f_j$。

维护一个单调队列，区间长度为 $pre_i$，队首到队尾呈单调不减，单调队列存储元素编号。那么每次转移前，先使得队首 $h \ge pre_i$，然后我们就获得了 $pre_i \le j < i$ 的 $f_j$ 的最小值。直接转移即可。然后我们将 $f_j$ 入队，同时维护单调队列的单调性即可。

每个测试数据的时间复杂度为 $O(n)$。

代码：

```cpp
/*
返せ！返せ！ボクの家族を
悪の手から未来の欠片を取返す
ボクの使命だ　この身の全てが滅びようとも
返せ！返せ！ボクの家族を
0419　必ず見
また幸せな温もりをこの鉄の肌で感じたい
*/
#include<bits/stdc++.h>
#define ll long long
#define int long long
#define mem(a,b) memset((a),(b),sizeof(a))
#define lb(x) ((x)&-(x))
#define lc(x) ((x)<<1)
#define rc(x) (((x)<<1)|1)
#define pb(G,x) (G).push_back((x))
using namespace std;
inline int read()
{
	int xx=0;int f=1;
	char c = getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f = -1;
		c = getchar();
	}
	while(c>='0'&&c<='9')
	{
		xx = (xx<<1)+(xx<<3)+(c^48);
		c = getchar();
	}
	return xx*f;
}
#define maxn 500050

int n,m,l,r,pre[maxn],v[maxn],q[maxn],f[maxn];

void work()
{
	n=read();
	for(int i=1;i<=n;i++) v[i]=read();
	m=read();
	for(int i=1;i<=m;i++)
	{
		l=read(),r=read();
		pre[r+1]=max(pre[r+1],l);//因为 l 到 r 为一个区间，则 pre[r+1] 和 l 取最值 
	}
	for(int i=1;i<=n+1;i++) pre[i]=max(pre[i-1],pre[i]);//再处理一个前缀 max，因为 pre[i] 肯定包含 pre[i-1]。
	int h=1,t=1;//队首和队尾
	for(int i=1;i<=n+1;i++)
	{
		while(h<=t&&q[h]<pre[i]) h++;//处理区间长度
		f[i]=f[q[h]]+v[i];//转移
		while(h<=t&&f[q[t]]>=f[i]) t--;//处理单调性
		q[++t]=i;//入队
	}
	cout<<f[n+1]<<'\n';
	for(int i=1;i<=n+1;i++) pre[i]=v[i]=f[i]=0;//清空，用多少清多少
	for(int i =h;i<=t;i++) q[i]=0;//不用 memset 防止超时
}

signed main()		
{
	int _=read();
	while(_--)
		work();
	return 0;
}
```

---

## 作者：lfxxx (赞：1)

考虑设计状态 $f_{i}$ 表示考虑前 $i$ 个且钦定选择了第 $i$ 个的最小花费。

考虑怎么处理限制的问题，不难发现假若转移过程中跨过了一个区间那么就不行，具体而言，在从 $f_{j}$ 转移到 $f_{i}$ 的过程中若区间 $[j,i]$ 中包含了一个限制就一定不行。

从这不难看出，可以转移到每个 $i$ 的 $j$ 一定在一段区间中，所以把上面那个 $f$ 扔到线段树上转移即可。

下面是我队友 LiwenX 的代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int kmaxn=1000001+10;
int tt,n;
int m,a[1000001];
struct line{
  int l,r;
}b[1000001],c[1000001];
bool cmp(line x,line y){
  if(x.l==y.l) return x.r<y.r;
  return x.l>y.l;
}
int minn[1000001];
int f[1000001],g[1000001];
bool vis[1000001];
int tree[500001<<2];
#define ls (now<<1)
#define rs (now<<1|1)
#define mid ((l+r)>>1)
void build(int now,int l,int r){
  if(l==r){
    tree[now]=1e15;
    return ;
  }
  build(ls,l,mid);
  build(rs,mid+1,r);
  tree[now]=1e15;
}
void add(int now,int l,int r,int x,int k){
  if(l==r){
    tree[now]=k;
    return ;
  }
  if(mid>=x) add(ls,l,mid,x,k);
  else add(rs,mid+1,r,x,k);
  tree[now]=min(tree[ls],tree[rs]);
}
int ask(int now,int l,int r,int x,int y){
  if(l>=x&&r<=y){
    return tree[now];
  }
  int ret=1e15;
  if(mid>=x) ret=ask(ls,l,mid,x,y);
  if(mid<y) ret=min(ret,ask(rs,mid+1,r,x,y));
  return ret;
}
signed main(){
//  freopen("_.in","r",stdin);
//  freopen("solve.out","w",stdout);
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cin>>tt;
  while(tt--){
    cin>>n;
    for(int i=1;i<=n;i++){
      cin>>a[i];
      minn[i]=1e15;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
      cin>>b[i].l>>b[i].r;
    }
    sort(b+1,b+1+m,cmp);
    int tot=0;
    for(int i=1;i<=m;i++){
      if(b[i].r<c[tot].r||tot==0){
        c[++tot]=b[i];
      }
    }
    build(1,0,n); 
    m=tot;
    for(int i=1;i<=m;i++){
      vis[c[i].l]=1;
      minn[c[i].r]=min(minn[c[i].r],c[i].l);
    }
    for(int i=n-1;i;i--){
      minn[i]=min(minn[i],minn[i+1]);
    }
    add(1,0,n,0,0);
    for(int i=1;i<=n;i++){ 
      int L=minn[i]; 
      if(L>i){
        f[i]=g[i-1]+a[i];
        g[i]=g[i-1];
      }
      else{
        f[i]=ask(1,0,n,L-1,i)+a[i];
        g[i]=f[i];
        if(!vis[i]) g[i]=min(g[i],g[i-1]);
      }
      add(1,0,n,i,g[i]);
//      cout<<i<<':'<<f[i]<<' '<<g[i]<<'\n';
    }
    cout<<g[n]<<'\n';
    for(int i=1;i<=n;i++){
      f[i]=g[i]=vis[i]=0;
      minn[i]=1e15;
    }
  }
  return 0;
}
/*
1
5
7 3 4 2 2
3
1 4
2 3
4 5
*/

```


---

## 作者：OIer_ACMer (赞：0)

# 题目解析：

本题，额，只想一句话，~~我这辈子都没见过这么明显的一眼题~~。

我们设 $dp_i$ 为已经枚举了 $1$ 到 $i$ 所有的点且已经满足了该区间内所有的条件的最小花费。所以，我们为了更快地求出答案，令 $n + 1$ 号点的点权位 $0$ 那么答案就是 $dp_{n + 1}$。至于怎么求每一项 $dp_i$ 的值，我们就只用枚举在 $i$ 之前的 $j$ 项的最小值。

但同时，我们还不能忽视题目告诉我们的每一个条件，我们接着考虑之后 $j + 1$ 一直到 $i - 1$ 之间有没有要求的区间。此时，假设我们要调查的区间为 $k$ 一直到 $i - 1$，当 $i$ 的下标更新为 $i + 1$ 时若一个区间的以 $i$ 结尾并且左端点在 $k$ 到 $i$ 之间。则对于 $i +1$ 来说 $j$ 的区间会变小。在这个过程中，$j$ 的区间会不断向右缩小，这时，我们为了优化时间复杂度，可以用单调栈来维护区间。

# 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 500009
int T, n, m, hed, ed;
int a[N], l[N], q[N];
int dp[N];
signed main()
{
    cin >> T;
    while (T--)
    {
        cin >> n;
        memset(l, 0, sizeof(l));
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            int ll, rr;
            cin >> ll >> rr;
            l[rr] = max(l[rr], ll);
            // cout << "l[" << ll << "]=" << l[ll] << endl;
        }
        hed = 1;
        ed = 1;
        q[1] = 0;
        n++;
        a[n] = 0;
        for (int i = 1; i <= n; i++)
        {
            dp[i] = dp[q[hed]] + a[i];
            while (hed <= ed && dp[q[ed]] > dp[i])
            {
                ed--;
            }
            q[++ed] = i;
            while (q[hed] < l[i])
            {
                hed++;
            }
        }
        cout << dp[n] << endl;
    }
    return 0;
}
```

---


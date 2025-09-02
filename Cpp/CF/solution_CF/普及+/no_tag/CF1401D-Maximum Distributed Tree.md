# Maximum Distributed Tree

## 题目描述

给定一棵 $n$ 个节点，$n-1$ 条边的树。你可以在每一条树上的边标上边权，使得：

1. 每个边权都为 **正整数**；
2. 这 $n-1$ 个边权的 **乘积** 等于 $k$；
3. 边权为 $1$ 的边的数量最少。

定义 $f(u,v)$ 表示节点 $u$ 到节点 $v$ 的简单路径经过的边权总和。你的任务是让 $\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^{n} f(i,j)$ 最大。

最终答案可能很大，对 $10^9+7$ 取模即可。

$k$ 有可能很大，输入数据中包含了 $m$ 个质数 $p_i$，那么 $k$ 为这些质数的乘积。

## 样例 #1

### 输入

```
3
4
1 2
2 3
3 4
2
2 2
4
3 4
1 3
3 2
2
3 2
7
6 1
2 3
4 6
7 3
5 1
3 6
4
7 5 13 3```

### 输出

```
17
18
286```

# 题解

## 作者：Lynkcat (赞：11)

一道比较水的贪心题。

考虑计算某一条边对答案的贡献，显然是这条边左边的点 $\times$ 右边的点 $\times$ 边权。

那么我们显然可以把每条边 左边的点 $\times$ 右边的点 扔进堆里。

如果 $m<=n$ 那么每次直接贪心取最大的那个与堆顶匹配计算答案。

如果 $m>n$ 那么把多出来的最大的合并到一起，转化成 $m<=n$ 即可。

```
#include<bits/stdc++.h>
#define int long long
#define N 100005
#define mo 1000000007
using namespace std;
int cnt,head[N],size[N],ans,n,m,mx,T,x,y,tp,a[N];
priority_queue <int,vector<int>,less<int> >q;
struct
{
	int to,nx;
}e[N<<1];
void ad(int x,int y)
{
	cnt++;
	e[cnt].to=y;
	e[cnt].nx=head[x];
	head[x]=cnt;
}
void dfs(int k,int fa) 
{
	size[k]=1;
	for (int i=head[k];i;i=e[i].nx)
	  if (e[i].to!=fa)
	  dfs(e[i].to,k),size[k]+=size[e[i].to];
}
void dfs1(int k,int fa)
{
	for (int i=head[k];i;i=e[i].nx)
	  if (e[i].to!=fa)
	  {
	  	q.push(size[e[i].to]*(n-size[e[i].to]));
	  	dfs1(e[i].to,k);
	  }
}
signed main()
{
	cin>>T;
	while (T--)
	{
		cin>>n;cnt=ans=mx=0;
		for (int i=1;i<=n;i++) head[i]=0;
		for (int i=1;i<n;i++)
		{
			cin>>x>>y;
			ad(x,y);
			ad(y,x);
		}
		dfs(1,0);
		dfs1(1,0);
		cin>>m;
		for (int i=1;i<=m;i++) 
		{
			cin>>a[i];
		}
		sort(a+1,a+m+1);
		n--;
		if (m>n) 
		{
		    for (int i=n+1;i<=m;i++) (a[n]*=a[i])%=mo;
		    m=n;
		}
		while (!q.empty())
		{
			tp=q.top();q.pop();
			(ans+=max(1ll,a[m--])*tp%mo)%=mo;
			if (m<0) m=0;
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：jun头吉吉 (赞：6)

# CF1401D 【Maximum Distributed Tree】

## 题意
给定一棵树，你必须用以下方式给$n−1$条标记上一个整数

- 每个整数大于$0$
- $n-1$条边上整数的乘积等于$k$
- $1$的数量尽可能少

定义$f(u,v)$为$u$到$v$的简单路径上的边权和，请最大化$\sum_{i=1}^n\sum_{j=i+1}^nf(i,j)$

由于值很大，请对$10^9+7$取模

## 题解

~~根据某CF惯用套路~~，我们可以分别先统计每条边的贡献。若我们定义$size_x$是以$x$为根的子树大小，那么$i\to fa_i$这条变上经过的简单路径一共有$size_i\times(n-size_i)$条

此时我们可以得出一个很显然的结论：**越大的数乘以越大的数得到更大的数**，因此我们需要尽量把大的数给前面。但因为又要保证$1$的数量尽可能少，因此我们需要分类讨论：

1. $m\le n-1$，可以贪心把大的贡献乘以大的因数
2. $m>n-1$，那么必定有多余的，因此我们可以把最大的给第一大的贡献直到满足1.的条件，在跑一边1.

## 代码
```cpp
 //#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){
	    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
	}
	template <typename T>inline void read(T& t){
	    t=0;int f=0;char ch=getc();
	    while (!isdigit(ch)){
	        if(ch=='-')f = 1;
	        ch=getc();
	    }
	    while(isdigit(ch)){
   	    	t=t*10+ch-48;
   	    	ch = getc();
   		}
		if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){
	    read(t);read(args...);
	}
}
namespace out{
	char buffer[1<<21];
	int p1=-1;
	const int p2 = (1<<21)-1;
	inline void flush() {
		fwrite(buffer,1,p1+1,stdout),
		p1=-1;
	}
	inline void putc(const char &x) {
		if(p1==p2)flush();
		buffer[++p1]=x;
	}
	template <typename T>void write(T x) {
		static char buf[15];
		static int len=-1;
		if(x>=0){
			do{
    			buf[++len]=x%10+48,x/=10;
    		}while (x);
		}else{
    		putc('-');
			do {
    			buf[++len]=-(x%10)+48,x/=10;
			}while(x);
		}
		while (len>=0)
			putc(buf[len]),--len;
	}
}
using namespace std;
#define int long long
int t,n,m,u,v;const int maxn=1e5+10;
vector<int>e[maxn];
#define pb push_back
int sz[maxn],fa[maxn];
vector<long long>val,pri;
const long long mod=1e9+7;
void dfs(int u){
	sz[u]=1;
	for(auto v:e[u])
		if(v!=fa[u]){
			fa[v]=u;
			dfs(v);
			sz[u]+=sz[v];
		}
	if(u!=1)val.pb(sz[u]*(n-sz[u]));
}bool cmp(int a,int b){
	return a>b;
}
signed main(){
	in::read(t);
	while(t--){
		in::read(n);
		val.clear();pri.clear();
		for(int i=1;i<=n;i++)
			e[i].clear(),sz[i]=0;
		for(int i=1;i<n;i++)
			in::read(u,v),e[u].pb(v),e[v].pb(u);
		fa[1]=0;dfs(1);
		sort(val.begin(),val.end(),cmp);
		in::read(m);
		for(int i=1;i<=m;i++){
			int a;in::read(a);
			pri.pb(a);
		}sort(pri.begin(),pri.end(),cmp);
		long long ans=0;
		if(m<=n-1){
			//无法所有填满
			for(int i=0;i<m;i++){
				val[i]*=pri[i];
				val[i]%=mod;
			} 
		}else{
			//尽量给大的
			while(pri.size()>=n){
				val[0]*=pri[0];val[0]%=mod;
				pri.erase(pri.begin());
			} 
			for(int i=0;i<pri.size();i++){
				val[i]*=pri[i];
				val[i]%=mod;
			} 
		}
		for(auto v:val)
			ans+=v,ans%=mod;
		out::write(ans);
		out::putc('\n');
	}out::flush();
}
```
~~打CF时忘打等号抱灵了~~

---

## 作者：奇米 (赞：3)

# 题解 - $\mathrm{CF1401D}$

## 题目意思

[题目传送门](https://www.luogu.com.cn/problem/CF1401D)

## $\mathrm{Sol}$

简单树上贪心

我们肯定考虑一条边的权值 $v_i$ 左边有 $ls$ 个点右边就 $(n-ls)$ 个点，那么这条边的贡献为 $ls(n-ls)\times v_i$

那么我们肯定尽量让大的权值的贡献最大，从大到小排个序累加一下即可，剩下的就是简单模拟一下。

时间复杂度：$O(n\log n)$

## $\mathrm{Code}$

```cpp
const int N=2e5+5;

int n,m,siz[N],head[N],cnt,P[N],S[N],bo[N],cwy,ans;

struct Node
{
	int nex,to;
};
Node e[N<<1];

inline void jia(int u,int v)
{
	e[++cnt].nex=head[u];
	head[u]=cnt;
	e[cnt].to=v;
}

inline void dfs(int u,int fa)
{
	siz[u]=1;
	GO(i,u)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		S[++cwy]=siz[v]*(n-siz[v]);//记录每条边的贡献
	}
}

inline bool Cmp(int x,int y) { return x>y; }
inline void Add(int &x,int y) { x+=y; if(x>=mod) x-=mod; }

signed main()
{
	int Q;
	io.read(Q);
	for (;Q--;)
	{
		io.read(n);
		For(i,1,n) head[i]=0,siz[i]=0;
		cwy=cnt=ans=0;
		For(i,1,n-1)
		{
			int x,y;
			io.read(x),io.read(y);
			jia(x,y);
			jia(y,x);
		}
		io.read(m);
		For(i,1,m) io.read(P[i]);
		dfs(1,0);
		sort(P+1,P+m+1,Cmp);
		sort(S+1,S+cwy+1,Cmp);//分别从大到小排序
		if(m<n)
		{
			For(i,m+1,n) P[i]=1;//不足n-1条边就用1补齐
			For(i,1,n-1) Add(ans,P[i]*S[i]%mod);
			io.write((ans+mod)%mod);
			puts("");
		}
		else 
		{
			int st=m-n+2;
			int tot=1ll;
			For(i,1,st) tot=tot*P[i]%mod;
			ans=tot*S[1]%mod;
            //否则把前面几个大的合并记录贡献
			For(i,2,n-1) Add(ans,P[st+i-1]*S[i]%mod);
			io.write((ans+mod)%mod);
			puts("");
		}
	}
	return 0;
}
	
```


---

## 作者：huayucaiji (赞：2)

贪心题石锤。

这个题有一个突破口，就是我们可以先用一遍 $\text{dfs}$ 来求出所有边在答案 $\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^{n} f(i,j)$ 中的贡献次数。所以我们可以有以下的式子：
$$\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^{n} f(i,j)=\sum\limits_{(u,v\in E)}con_{(u,v)}\times w_{(u,v)}$$

其中 $con_{(u,v)}$ 表示 $(u,v)$ 这条边被经过次数，$w_{(u,v)}$ 表示 $u,v$ 这条边的边权。


如果我们以 $1$ 为根，$size_u$ 表示以 $u$ 为根的子树的大小。那么连接 $u,v$，且 $u$ 为 $v$ 的父亲的这条边对答案的贡献就是 $con_{(u,v)}=size_u\times (n-size_u)$。

我们再来维护边权。有两种情况，我们分别讨论

- 如果 $m<n-1$ 那么一定会有边权为 $1$ 的边出现。那么为了让 $1$ 最少（题目要求），我们只有唯一解
- 否则我们可以让一些质因子合并，构造出 $n-1$ 个边权。那么我们为了让答案最大，一定是把最大的 $m-n+2$ 个边权堆在一起。证明很简单，就是因为如果我们有 $a>b,k>0$，那么 $k\cdot a>k\cdot b$。最后给 $w,con$ 数组排个序即可。

**注意，对于 $con$ 数组，先排序在取模；对于 $w$ 数组，按顺序处理，由于数字太大在处理时就要取模，千万别排序！！！**

```cpp
//Don't act like a loser.
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=1e5+10,mod=1e9+7;

int n,m;
int p[maxn],a[maxn],h[maxn],cnt,w[maxn],sz[maxn],con[maxn],tot;

struct edge {
	int v,next;
}e[maxn<<1];

void addedge(int u,int v) {
	e[++cnt].v=v;
	e[cnt].next=h[u];
	h[u]=cnt;
}
void insert(int u,int v) {
	addedge(u,v);
	addedge(v,u);
}

void dfs(int u,int fa) {
	sz[u]=1;
	for(int i=h[u];i;i=e[i].next) {
		int v=e[i].v;
		
		if(v!=fa) {
			dfs(v,u);
			sz[u]+=sz[v];
		}
	}
	if(fa!=0) {
		con[++tot]=sz[u]*(n-sz[u]);//不着急取模
	}
}

signed main() {
	int T=read();
	while(T--) {
		n=read();
		fill(h+1,h+n+1,0);
		cnt=0;
		for(int i=1;i<n;i++) {
			insert(read(),read());
		}
		m=read();
		fill(w,w+n+1,0);
		for(int i=1;i<=m;i++) {
			p[i]=read();
		}
		sort(p+1,p+m+1);//这里要先排序
		
		if(n-1<m) {//第一种
			for(int i=1;i<n-1;i++) {
				w[i]=p[i];
			}
			w[n-1]=p[n-1];
			for(int i=n;i<=m;i++) {
				w[n-1]=w[n-1]*p[i]%mod;
			}
		}
		else {//第二种
			for(int i=1;i<=m;i++) {
				w[i]=p[i];
			}
			for(int i=m+1;i<n;i++) {
				w[i]=1;
			}
			sort(w+1,w+n);
		}
		
		tot=0;
		dfs(1,0);//维护con
		
		int ans=0;
		
		sort(con+1,con+n);
		for(int i=1;i<n;i++) {
			ans+=con[i]%mod*w[i]%mod;//贪心
			ans%=mod;
		}
		cout<<ans<<endl;
	}
	return 0;
}

```

**这里放一个拓展。因为在比赛时我有一个朋友把 product 理解为 sum，所以浪费了很多时间。~~不是无中生友qwq~~。大家看到这篇题解可以想一想如果是 sum 怎么做，可以在评论里交流一下~**

---

## 作者：123zbk (赞：1)

需要考虑每一条边的贡献。从 $u$ 到 $v$ 这条边所产生的贡献就是 $size_i\times(n-size_i)\times$ 当前边的边权。

现在考虑边权怎么分配。我们用一个贪心的思想，要想乘积之后加和的结果最大，就要优先使大数乘以大数。所以我们把所有边的 $size\times(n-size)$ 从大到小排序，然后将边权按从大到小依次和其匹配。

但是要分两种情况：

如果 $m\le n-1$，就是现在的质数个数比边的个数小，那就先将所有的质数先都匹配上，剩下的边权视为 $1$。

如果 $m>n-1$，那就把多出来的数全部乘一起当成第一个数，剩下的依次匹配即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5,mod=1e9+7;
int head[maxn],sz[maxn],tot,n,m,u,v,sum,x,T;
vector <int> a,ans;
struct edge
{
    int to,nxt;
}e[maxn<<1];
void add(int u,int v)
{
    ++tot;
    e[tot].to=v;
    e[tot].nxt=head[u];
    head[u]=tot;
}
void dfs(int u,int fa)
{
    sz[u]=1;
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==fa)
        {
            continue;
        }
        dfs(v,u);
        sz[u]+=sz[v];
    }
    ans.push_back(sz[u]*(n-sz[u]));
}
void clear()
{
    sum=tot=0;
    ans.clear(),a.clear();
    memset(sz,0,sizeof(sz));
    memset(head,0,sizeof(head));
}
signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        clear();
        scanf("%lld",&n);
        for(int i=1;i<n;i++)
        {
            scanf("%lld%lld",&u,&v);
            add(u,v);
            add(v,u);
        }
        dfs(1,0);
        sort(ans.begin(),ans.end(),greater<int>());
        scanf("%lld",&m);
        for(int i=1;i<=m;i++)
        {
            scanf("%lld",&x);
            a.push_back(x);
        }
        sort(a.begin(),a.end(),greater<int>());
        if(m<=n-1)
        {
            for(int i=0;i<m;i++)
            {
                ans[i]*=a[i];
                ans[i]%=mod;
            }
        }
        else
        {
            while(a.size()>n-1)
            {
                ans[0]=ans[0]*a[0]%mod;
                a.erase(a.begin());
            }
            for(int i=0;i<a.size();i++)
            {
                ans[i]=ans[i]*a[i]%mod;
            }
        }
        for(int i=0;i<ans.size();i++)
        {
            sum=(sum+ans[i])%mod;
        }
        printf("%lld\n",sum);
    }
    return 0;
}
```

---

## 作者：xuezhe (赞：1)

首先转化结果式子为计算每条边的贡献：$\sum_{i} w_i \cdot c_i$，其中 $w_i$ 为我们为第 $i$ 条边赋的边权，$c_i$ 为第 $i$ 条边会被计算到的次数，即两边的点数的乘积。

可以发现应尽可能把大的质因子放在 $c_i$ 更大的位置。

容易想到一个贪心：尽可能把更大的质因子放在 $c_i$ 更大的边上。

然后好像也没什么好说的了，就讲一下分类两种情况：

第一种是 $m<n$，即质因子的数量不超过边数，直接把边数从大到小排序，质因子从大到小排序，一一对应即可，没有对应的 $w_i=1$。

第二种是 $m \ge n$，则把最大的 $m-n+1$ 全部给 $c_i$ 最大的那条边，剩下的按上面的分法。

单组数据时间复杂度 $O(n + m \log m)$。

Code:
```cpp
typedef long long ll;

const int P(1000000007);

vector<int> edge[100005];

int T,n,m,p[60005],siz[100005],f[100005];
ll qwq[100005];

void dfs(int x,int f){
    siz[x]=1;
    for(int &y:edge[x])
        if(y!=f){
            dfs(y,x);
            siz[x]+=siz[y];
        }
    qwq[x]=(ll)(n-siz[x])*siz[x];
    return;
}

int main(){
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i)
            edge[i].clear();
        int u,v;
        for(int i=1;i<n;++i){
            cin>>u>>v;
            edge[u].pb(v);
            edge[v].pb(u);
        }
        dfs(1,0);
        sort(qwq+1,qwq+1+n);
        reverse(qwq+1,qwq+1+n);
        for(int i=1;i<n;++i)
            qwq[i]%=P;
        cin>>m;
        for(int i=1;i<=m;++i)
            cin>>p[i];
        sort(p+1,p+1+m);
        reverse(p+1,p+1+m);
        int res(0);
        if(m<=n-1){
            for(int i=1;i<=m;++i)
                (res+=(ll)p[i]*qwq[i]%P)%=P;
            for(int i=m+1;i<n;++i)
                (res+=qwq[i])%=P;
        }else{
            for(int i=1;i<n;++i)
                f[i]=1;
            for(int i=1;i<=m-(n-1);++i)
                f[1]=(ll)f[1]*p[i]%P;
            for(int i=1;i<n;++i)
                f[i]=(ll)f[i]*p[(m-(n-1))+i]%P;
            for(int i=1;i<n;++i)
                (res+=(ll)f[i]*qwq[i]%P)%=P;
        }
        cout<<res<<'\n';
    }
    return 0;
}
```

---

## 作者：Drest (赞：0)

# [CF1401D] Maximum Distributed Tree 题解

## 传输门

[luogu](https://www.luogu.com.cn/problem/CF1401D)
| 
[codeforces](https://codeforces.com/problemset/problem/1401/D)

# 解题思路

考虑每条边的贡献，很显然为 $size_{u_i} \times size_{v_i} \times w_i$，这里 $w_i \in p$，那么我们就很容易想到让**尽可能大的** $size_{u_i} \times size_{v_i}$ 匹配**大的** $p_i$，这样贡献和才能最大。

那么，就可以将 $size_{u_i} \times size_{v_i}$ **从大到小**排序，再把 $p$ 从大到小排序，直接匹配即可。

不过这里需要注意的是，序列 $p$ 的大小可能大于边数，那么这时候我们取 $p$ 中最大的几个合并一下，保证 $m \le n - 1$ 即可。

# AC 代码

这里代码使用 `vector` 实现排序功能。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9 +7;
const int N = 1e6 +10;
vector<int> q;
vector<int> g[N];
int sz[N];
vector<int> e;
int n, m, ans;
void dfs(int x, int fa) { // 跑一遍图，找点的大小
    sz[x] = 1;
    for (int i : g[x]) {
        if (i == fa) continue;
        dfs(i, x);
        sz[x] += sz[i];
    }
    if (x != 1)  // 存边
        e.push_back(sz[x] * (n - sz[x]));
}
bool cmp(int a,int b){
    return a > b;
}

signed main() {
    int t;
    cin >>t;
    while (t--) {
        cin >> n;

        ans = 0;
        for (int i = 1; i <= n; i++)
            g[i].clear();
        e.clear();
        q.clear();

        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        cin >> m;
        for (int i = 1; i <= m; i++) {
            int p;
            cin >> p;
            q.push_back(p);
        }
        dfs(1, 0);
        sort(e.begin(), e.end(), cmp);
        sort(q.begin(), q.end(), cmp);
        while (m >= n) { // 合并
            int x = q[0];
            q.erase(q.begin());
            q[0] = q[0] * x % mod;
            m--;  // 注意这里需要 m-- (卡了我半小时)
        }
        int cnt = 0;
        while (!q.empty()) {
            int x = q[0];
            q.erase(q.begin());
            ans += x * e[cnt] % mod;
            ans %= mod;
            cnt++;
        }
        while (cnt < e.size()) {
            ans += e[cnt] % mod;
            ans %= mod;
            cnt++;
        }
        cout << ans << '\n';
    }
}
```

---

## 作者：Targanzqq (赞：0)

想了几分钟发现不会，一看题解发现了**贪心**两个字以后果断开写。

首先我们统计其中一条边 $(u,v,w)(dep_u<dep_v)$ 的贡献。我们可以发现，$u$ 子树内的点，和 $u$ 子树外的点之间的路径一定经过这条边。因此这条边的贡献就是 $sz_u(n-sz_u)\times w$，其中 $sz$ 表示子树大小。

然后我们考虑，如果对于更大的 $sz_u(n-sz_u)$，我们让它乘上一个更大的 $w$ 答案会更优。这样我们就得到了贪心策略。

考虑 $m$ 和 $n$ 的关系：如果 $m< n$，那一定有至少 $n-m-1$ 条边的边权是 $1$，我们把这些边权为 $1$ 的边补上。若 $m\ge n$，那么我们让最大的边乘起来，直到边数等于 $n-1$。然后我们按照上面的策略贪心分配边权即可。时间复杂度 $O(n\log n)$，复杂度瓶颈在于排序。

源代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;

int n,m,p[200005]; 
vector<int> t[200005];

vector<int> e;
int sz[200005],ans;

void dfs(int u,int fa){
	sz[u]=1;
	for(auto i:t[u]){
		if(i==fa)continue;
		dfs(i,u);
		e.push_back(sz[i]*(n-sz[i]));
		sz[u]+=sz[i];
	}
}

signed main(){
ios::sync_with_stdio(false);
  int T;
  cin>>T;
  while(T--){
	cin>>n;
	for(int i=1;i<=n;i++){
		t[i].clear();
		sz[i]=0;
	}
	e.clear();
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		t[u].push_back(v);
		t[v].push_back(u);
	}
	dfs(1,0);
	sort(e.begin(),e.end());
	cin>>m;
	for(int i=1;i<=m;i++)cin>>p[i];
	for(int i=m+1;i<n;i++)p[i]=1;
	sort(p+1,p+max(n,m+1));
	for(int i=m-1;i>=n-1;i--){
		p[i]=(p[i]*p[i+1])%mod;
	}
	for(int i=n-1;i>=1;i--){
		ans+=(p[i]*e[i-1])%mod;
		ans%=mod;
	}
	cout<<ans<<"\n";
	ans=0;
    }
}

```

---

## 作者：Dtw_ (赞：0)

# solution
首先看到这种式子，显然是不能暴力直接求的，所以我们可以先考虑假设我们知道边权了，如何计算这个。

我们可以单独的对于每一条边计算这条边贡献了几次，但是这样算不太好求，但我们可以把边权转为点权计算。为什么是对的呢？因为这是一棵树，不存在一个点属于多条边。

记 $sz_u$ 为 $u$ 的子树大小，贡献次数为 $sz_u\times (n-sz_u)$，为什么呢？因为如果要计算这个点被经过了几次，一定是从他的子树内选一个，子树外选一个，所以总方案数是 $sz_u \times (n - sz_u)$。

那现在处理出来这个之后就要处理权值了。考虑怎样最大呢？一定是最大的边权经过最多的次数，所以直接排序贪心就行。

但是有一种情况是 $m > n-1$ 所以我们有多余的边权可以放置，那显然就是让多了的乘起来，然后转化为上面的情况，那一定是最大的乘起来，然后就做完了。
# Code

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define fi first
#define se second

#define int long long

#define pii pair<int, int>

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 1e9 + 7;

const int N = 1e6 + 10;

int n, m;

vector<int> G[N];

priority_queue<int> q;

int sz[N], a[N];

void dfs(int u, int fa)
{
	sz[u] = 1;
	for(auto v : G[u])
	{
		if(v == fa) continue;
		dfs(v, u);
		sz[u] += sz[v];
		q.push(sz[v] * (n - sz[v]));
	}
}

void solve()
{
	cin >> n;
	for(int i=1; i<=n; i++) G[i].clear();
	for(int i=1; i<n; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
	cin >> m;
	for(int i=1; i<=m; i++) cin >> a[i];
	sort(a + 1, a + m + 1);
	reverse(a + 1, a + m + 1);
	int res = 0;
	if(m <= n - 1)
	{
		int i = 1;
		while(!q.empty())
		{
			if(i <= m)
			{
				res = (res + q.top() * a[i] % P) % P;
			}
			else res = (res + q.top()) % P;
			q.pop();
			i++;
		}
	}
	else
	{
		int o = 1;
		for(int i=1; i<=m-n+2; i++)
		{
			o = o * a[i] % P;
		}
		int i = m - n + 2;
		a[i] = o;
		while(!q.empty())
		{
			res = (res + q.top() * a[i] % P) % P;
			q.pop();
			i++;
		}
	}
	cout << res << endl;
}

signed main()
{
	fst
    int T;
    cin >> T;
    while(T--) solve();
	return 0;
}




```

---

## 作者：Star_F (赞：0)

一道树上的贪心问题。

## 题目大意：
给你一个 $n$ 个节点的树，让你对 $n-1$ 条边进行填数。有以下要求：

1. 填的数大于 $0$。
2. 填的所有数的乘积为 $k$。
3. 填 $1$ 的数尽量少。

定义 $f(u,v)$ 表示节点 $u$ 到节点 $v$ 的简单路径经过的边权总和。求 $\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^{n} f(i,j)$ 最大值。

## 题目分析：
对于求某些东西的最大值的题目，我们可以考虑拆分贡献。考虑每天边对答案的贡献。

有一个贪心策略是给遍历次数最多的边分配最大的数，这样能保证答案为最大值。那我们如何求出每条边的遍历次数呢？

可以手动推一下，想遍历这条边，可以从这条边左边的点遍历到右边的点，根据乘法原理，对于每条左边的点，可以任选一个右边的点进行匹配，所以每条边的遍历次数就是左边点的数量 $\times$ 右边点的数量。按照这个值从大到小排序，然后依次给遍历次数最多的边分配最大的权值。

这里有一个细节就是如果 $m>n$，那我们可以把多余的数都乘到第 $n$ 个数即可。

代码就不给了，因为要从大到小所以可以排序也可以用堆维护。

---

## 作者：qiliu (赞：0)

## 思路

这道题的思路还是比较显然的。因为题目要求的是一种分配边权方式，所以我们考虑每一条边对答案的贡献。

事先声明：

- 由于本人不想再给边单独标号，所以在下文及 code 中，边 $i$ 的意义是从节点 $i$ 开始指向他的父亲节点的一条边。

- 默认节点 1 为这棵树的根。

每一条边会出现在许多点之间的简单路径上从而对答案贡献多次，所以我们设 $e_i$ 为边 $i$ 对答案贡献的次数，设 $val_i$ 为每个边分到的边权，于是这道题就相当于让我们最大化 $\sum_{i=1}^{n-1}e_i\times val_i$。

我们先考虑如何处理 $e_i$。很显然的，如果一对点的简单路径穿过边 $i$，那么他们肯定一个在节点 $i$ 极其子树中，另一个在除了 $i$ 和他子树之外的点。所以我们设 $size_i$ 表示 $i$ 的子树（包括他本身）的大小，于是显然有 $e_i=size_i\times(size_1-size_i)$。

然后考虑如何分配边权。显然对于贡献次数多的边我们分配更大的 $p_i$ 是更优的。但是我们需要额外考虑一下 $m \gt n-1$ 的情况，这时我们发现一条边上可能乘上多个 $p_i$，此时如果一个 $p_i$ 要对答案贡献最大，那么就要那些和他乘在同一项里的其他 $p_j$ 最大，要满足这一点，不难发现要把多余的所有 $p_i$ 乘在一起再进行决策。

## code


```cpp
#include<bits/stdc++.h>
#define int long long
#define DEBUG(x) cerr<<#x<<'='<<x<<endl
#define endl '\n'
using namespace std;
inline int rd()
{
    char t=getchar();
    int f=1,x=0;
    while(t<'0'||t>'9')
    {
        if(t=='-')f=-1;
            t=getchar();
    }
    while(t>='0'&&t<='9')
        x=x*10+t-'0',t=getchar();
    return x*f;
}
inline void wt(int t)
{
    if(t<0)
        putchar('-'),t=-t;
    if(t>9)
        wt(t/10);
    putchar(t%10+'0');
    return;
}
const int N=1e5+100,M=6e4+100,MOD=1e9+7;
int n,m;
int p[N];//同题目中的p
vector<int>a[N];//建边
int e[N];//同上文中的e
int siz[N];//同上文中的size
int dfs(int x,int fa){//预处理size数组
    siz[x]=1;
    for(int i=0;i<a[x].size();i++){
        int v=a[x][i];
        if(v==fa)continue;
        siz[x]+=dfs(v,x);
    }
    return siz[x];
}
void get_e(int x,int fa){//预处理e数组
    for(int i=0;i<a[x].size();i++){
        int v=a[x][i];
        if(v==fa)continue;
        get_e(v,x);
        e[v]=siz[v]*(siz[1]-siz[v]);//这里不要取模，不然无法保证正确性（会 WA on #5）
    }
}
bool cmp(int xx,int yy){
    return xx>yy;
}
signed main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int T=rd();
    while(T--){
        n=rd();
        memset(e,0,sizeof(e));
        memset(p,0,sizeof(p));//多测记得清空
        for(int i=0;i<=n;i++)a[i].clear();
        for(int i=1;i<n;i++){
            int u=rd(),v=rd();
            a[u].push_back(v);
            a[v].push_back(u);
        }
        m=rd();
        for(int i=1;i<=m;i++)
            p[i]=rd();
        for(int i=m+1;i<=n;i++)p[i]=1;
        dfs(1,0);
        get_e(1,0);
        // cerr<<'a';
        sort(e+1,e+1+n,cmp);
        sort(p+1,p+1+m,cmp);
        int beginn=1;
        while(m>=n){//上文中提到，要把多余的p乘到一起。这里最终是把他们乘到了p[beginn]
            ++beginn;
            p[beginn]*=p[beginn-1];
            p[beginn]%=MOD;//别忘了取模
            m--;
        }
        int ans=0;
        for(int i=1;i<=n;i++){
            ans+=e[i]*p[beginn++]%MOD;//别忘了取模
            ans%=MOD;//别忘了取模
        }
        wt(ans);
        putchar('\n');//记得换行
    }
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}
```
希望有帮到你。

---

## 作者：Infinity_G (赞：0)

钦定树根为 $1$，考虑 $u-fa_u$ 这条边，任意一条 $u$ 子树内和子树外的点的路径都会包含这条边，所以这条边被经过的次数为

$$s_u\times(n-s_u)$$

接下来考虑如何分配这 $m$ 个质数，显然大的数分配尽量大的数，但同时要满足边权为 $1$ 的边的数量最少，所以我们先一个一个分配，剩下的给最大的数即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100005
#define M 60005
const int p=1e9+7;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int t,n,m,u,v,s[N],a[M],res,ans;
ll f[N];
vector<int> g[N];
void dfs(int x,int fa)
{
	s[x]=1;
	for(auto i:g[x])
		if(i^fa) dfs(i,x),s[x]+=s[i];
	f[x]=1ll*s[x]*(n-s[x]);
}
bool cmp(ll x,ll y)
{
	return x>y;
}
int main()
{
	t=read();
	while(t--)
	{
		n=read(),ans=0;
		for(int i=1;i<=n;i++)
			g[i].clear();
		for(int i=1;i<n;i++)
		{
			u=read(),v=read();
			g[u].push_back(v);
			g[v].push_back(u);
		}
		dfs(1,0);
		sort(f+1,f+n+1,cmp);
		m=read();
		for(int i=1;i<=m;i++)
			a[i]=read();
		sort(a+1,a+m+1,cmp);
		for(int i=n-1;i>1;i--)
		{
			if(m>=i) ans=(ans+f[i]%p*a[m--]%p)%p;
			else ans=(ans+f[i]%p)%p;
		}
		res=f[1]%p;
		do{res=1ll*res*a[m]%p;}while(--m);
		printf("%d\n",(ans+res)%p);
	}
	return 0;
}
```

---

## 作者：Xseventh (赞：0)

一道有点意思的树上贪心题。


------------
### 分析一波
这是一棵树，让我们标边权，定义 $f(u,v)$ 表示节点 $u$ 到节点 $v$ 的简单路径经过的边权总和，使$\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^{n} f(i,j)$ 最大，同时满足这三个条件：
1. 每个边权都为 **正整数**；
2. 这 $n-1$ 个边权的 **乘积** 等于 $k$( $k$ 给你分解质因数了）；
3. 边权为 $1$ 的边的数量最少。

另外，答案还要取模$10^9+7$。

题意明白了，我们看这三个条件。一条件保证正整数，这其实帮我们简化了题目。再看二条件，我刚看到 $k$ 时还在想这怕不是要分解质因数，结果CF直接就帮我们分解了，那么我们就可以直接往下看了。

关键在三条件， $1$ 的数量最少，那么我们进行一个分类讨论：
1. 当 $m <= n - 1$ 时，所有的边权应为 $(n-1)-m$ 个 $1$ 以及剩下 $m$ 个质因数，这样保证 $1$ 最少。
2. 当 $m > n - 1$ 时，需拿出 $m - (n - 1)$ 个质因数作为乘数合并至其它边权，同时保证了没有边权为 $1$ 的边。

回到问题开头，要求边权总和，必须先求出每条边被使用了几次，可以用一个 $temp$ 数组来表示。因为这是一棵树，对于一条边，它的被使用次数为其**左边点数量乘右边点数量**，这可以通过一次 $dfs$ 实现。我们求出了 $temp$ 数组，接下来就要用到贪心的思路了，对于质因数数组与 $temp$ 数组， 大的元素与大的元素，小的元素与小的元素匹配一定优于大的元素与小的元素，大的元素与小的元素匹配。即两个数组都按升序排序，同下标一一相乘求出贡献即可。

------------
### Code

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

#define int long long

using namespace std;

const int N = 2e5 + 10;
const int M = 6e4 + 10;
const int Mod = 1e9 + 7;

int t, n, m, ans;
int primes[M], v[N], deep[N];
int h[N], e[N], ne[N], idx;
bool st[N];
struct node {
	int a, b, c;
}p[N];

void add(int a, int b) {
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

bool cmp(node a, node b) {
	return a.c < b.c;
}

void dfs(int x) {
	for (int i = h[x]; ~i; i = ne[i]) {
		int j = e[i];
		if (!st[j]) {
			st[j] = true;
			dfs(j);
			deep[x] += deep[j];
		}
	}
}

signed main() {	
	scanf("%lld", &t);
	
	while (t --) {
		idx = 0, ans = 0;
		memset(h, -1, sizeof h);
		memset(st, false, sizeof st);
		
		scanf("%lld", &n);
		
		for (int i = 1; i < n; i ++) {
			scanf("%lld%lld", &p[i].a, &p[i].b);
			add(p[i].a, p[i].b), add(p[i].b, p[i].a);
		}
		
		scanf("%lld", &m);
		
		for (int i = 1; i <= m; i ++) scanf("%lld", &primes[i]);
		
		for (int i = 1; i <= n; i ++) deep[i] = 1;
		
		st[1] = true;
		dfs(1);
		
		for (int i = 1; i < n; i ++) p[i].c = min(deep[p[i].a], deep[p[i].b]) * (n - min(deep[p[i].a], deep[p[i].b]));
		
		sort(p + 1, p + n, cmp);
		
		sort(primes + 1, primes + 1 + m);
		
		n --;
		
		if (m <= n) {
			for (int i = 1; i <= n - m; i ++) v[i] = 1;
			for (int i = n - m + 1; i <= n; i ++) v[i] = primes[i - (n - m)];
		}
		else {
			v[n] = 1;
			for (int i = 1; i < n; i ++) v[i] = primes[i];
			for (int i = n; i <= m; i ++) v[n] = v[n] * primes[i] % Mod;
		}
		
		for (int i = 1; i <= n; i ++) ans = (ans + p[i].c % Mod * v[i] % Mod) % Mod;
		
		printf("%lld\n", ans);
	}
	
	return 0;
}
```

---

## 作者：_HwH_ (赞：0)

### [传送门](https://www.luogu.com.cn/problem/CF1401D)

## 分析
我们要最大化边权求和： $\sum_{i=1}^{n-1}\sum_{j=i+1}^{n}{f(i,j)}$

其中 $f(i,j)$ 表示树上从 $i$ 节点走到 $j$ 节点的简单路径的边权和

那么贪心的讲，我们对于走过次数最多的边赋予最高的权值必然是最优的，给出证明：
#### 证明
设有最大边权和次大边权 $k_1$ ， $k_2$ ，走过次数最多的边的次数和次多的边的次数 $sum_1$ ， $sum_2$

那么若证 $k_1 \times sum_1 + k_2 \times sum_2 > k_2 \times sum_1 + k_1 \times sum_2$

即证 ： $(k_1 - k_2) \times (sum_1 - sum_2) > 0$

而 $k_1 > k_2$ ， $sum_1 > sum_2$ ，故不等式必然成立

那么我们把这个不等式类推到 $n$ 项 ， 即 ：设边权从大到小为 $k_1 , k_2 , …… , k_n$ ， 边被遍历到的次数从大到小为 $sum_1 , sum_2 , sum_3 , …… ,sum_n$

则有：
$$
k_1 \times sum_1 + k_2 \times sum_2 + …… + k_n \times sum_2 \geq ……… \geq k_1 \times sum_n + k_2 \times sum_{n-1} + …… + k_n \times sum_1
$$ 
，即由[排序不等式](https://baike.baidu.com/item/%E6%8E%92%E5%BA%8F%E4%B8%8D%E7%AD%89%E5%BC%8F/7775728?fr=aladdin)，成立

排序不等式证明：

![80cb39dbb6fd5266d016f1ef6051802bd40734fa98bc.png](https://i.loli.net/2020/11/28/jq7HoxT2p6DvgIE.png)

## Solution
那么我们可以对每一条边进行考虑，在这一条边左边的点（包括边的端点）的数量与右边的点的数量的乘积，即为这条边在路径中被走过的总次数，那么我们可以那一个堆来从大到小记录每条边被走过的次数

当 $k$ 的质因子的数量小于等于边数的时候，为了满足使边权为 1 的边的数量最少的要求，直接将质因子从大到小排序后，每次从堆中（按边的遍历次数从大到小）取出一个数与之相乘，则总和即为最大值

当 $k$ 的质因子数量大于边数的时候，由上述分析中得到的结论，我们只要把质因子从大到小相乘，然后将乘过的因子删去，直到因子的数量最后剩下 $n-1$ 个（即边数），则将上述因子的乘积作为其最大边权，其余 $n-2$ 个因子为其他的边权，按照 $k$ 小于等于边数的时候处理即可


## Code
```cpp
#include<iostream>
#include<cstdio>
#include<math.h>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
#define ll long long

const ll mod=1e9+7;
const ll maxn=1e5+10;
ll t,n,m,ans;
ll p[maxn],s[maxn];
std::vector<ll> e[maxn]; 
std::priority_queue<ll> q;

inline void cle()
{
	memset(s,0,sizeof(s));
	memset(p,0,sizeof(p));
	ans=0;
	for(int i=1;i<=n;i++) e[i].clear();
	while(q.size())
	{
		q.pop();
	}
}

inline void dfs(ll x,ll f)
{
	s[x]=1;
	for(int i=0;i<e[x].size();i++)
	{
		ll y=e[x][i];
		
		if(y==f) continue;
		
		dfs(y,x);
		
		s[x]+=s[y];
	}
}

inline void ddfs(ll x,ll f)//计算每条边作为经过的次数
{
	for(int i=0;i<e[x].size();i++)
	{
		ll y=e[x][i];
		
		if(y==f) continue;
		
		q.push(s[y]*(n-s[y]));
		
		ddfs(y,x);
	}
}

inline bool cmp(ll a,ll b)
{
	return a>b;
}

int main(void)
{
	scanf("%lld",&t);
	
	while(t--)
	{
		cle();//多组输入，记得清空
		scanf("%lld",&n);
		
		for(int i=1;i<=n-1;i++)
		{
			ll x,y;
			scanf("%lld %lld",&x,&y);
			e[x].push_back(y);
			e[y].push_back(x);
		}
		
		scanf("%lld",&m);
		for(int i=1;i<=m;i++) scanf("%lld",p+i);
		
		dfs(1,0);
		ddfs(1,0);
		
		std::sort(p+1,p+m+1,cmp);
		
		if(m<=(n-1))//因子数小于等于边数
		{
			ll top=1;
			while(q.size())
			{
				if(top<=m) (ans+=q.top()*p[top])%=mod;
				else (ans+=q.top())%=mod;
				
				top++;
				q.pop();
			}
		}
		else//因子数大于边数
		{
			ll top=m-n+2;
			ll sum=1;
			for(int i=1;i<=(m-(n-1))+1;i++)
			{
				(sum*=p[i])%=mod;
			}
			p[top]=sum;
			
			while(q.size())
			{
				(ans+=q.top()*p[top])%=mod;
				q.pop();
				top++;
			}
		}
		
		printf("%lld\n",ans);
	}
	
	return 0;
}
```


---

## 作者：cirnovsky (赞：0)

## 题意简述

感觉翻译挺简洁的就直接贺过来了。

给定一棵 $n$ 个节点，$n-1$ 条边的树。你可以在每一条树上的边标上边权，使得：

1. 每个边权都为 **正整数**；
2. 这 $n-1$ 个边权的 **乘积** 等于 $k$；
3. 边权为 $1$ 的边的数量最少。

定义 $f(u,v)$ 表示节点 $u$ 到节点 $v$ 的简单路径经过的边权总和。你的任务是让 $\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^{n} f(i,j)$ 最大。

最终答案可能很大，对 $10^9+7$ 取模即可。

$k$ 有可能很大，输入数据中包含了 $m$ 个质数 $p_i$，那么 $k$ 为这些质数的乘积。

## 题解

之前没怎么做过的套路题，活生生想了一个小时，不过想出来过后回想还是挺简单的。写篇题解记录一下人生。

首先考虑如何计算 $\sum_{i=1}^{n-1}\sum_{j=i+1}^{n}f(i,j)$。

可以考虑对边计算贡献。

对于一条边 $(u,v)\in E$，那么 $F_{u,v}=S_{v}\times(n-S_{v})$。其中 $F_{u,v}$ 表示边 $(u,v)$ 对答案贡献的次数，$S_{u}$ 表示点 $u$ 的 $|\{\operatorname{subtree}(u)\}|$。

那么就有一个显然的贪心策略，把 $k$ 的质因子比较大的就分配给贡献次数比较多的边，那么对质因子和边贡献次数降序排序即可。

剩下的就是一些分类讨论的问题，就是根据边的数量和质因子个数的大小关系看是补 $1$ 还是把大的乘起来。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define mod ( 1000000007 )

using namespace std;
typedef long long LL;

const int MAXN = 1e5 + 5;

template<typename _T>
void read( _T &x ){
	x = 0; char c = getchar( ); _T f = 1;
	while( c < '0' || c > '9' ){ if( c == '-' )	f = -1; c = getchar( ); }
	while( c >= '0' && c <= '9' ){ x = ( x << 3 ) + ( x << 1 ) + ( c & 15 ); c = getchar( ); }
	x *= f;
}

template<typename _T>
void write( _T x ){
	if( x < 0 ){ putchar( '-' ); x = -x; }
	if( x > 9 )	write( x / 10 );
	putchar( x % 10 + '0' );
}

int N, M;
int tot; 
LL fur[MAXN], cont[MAXN], times[MAXN];
vector<int> Graph[MAXN];

void getID( int u, int lst ){
	fur[u] = 1;
	for( unsigned i = 0; i < Graph[u].size( ); ++ i ){
		int v = Graph[u][i];
		if( v == lst )	continue;
		getID( v, u ); fur[u] += fur[v];
		cont[++ tot] = fur[v] * ( N - fur[v] );
	}
}

void clearIt( ){
	tot = 0;
	memset( Graph, 0, sizeof( Graph ) );
	memset( cont, 0, sizeof( cont ) );
	memset( times, 0, sizeof( times ) );
	memset( fur, 0, sizeof( fur ) );
}

signed main( ){
	int T; read( T );
	while( T -- > 0 ){
		clearIt( );
		read( N );
		for( int i = 1, u, v; i < N; ++ i ){
			read( u ); read( v );
			Graph[u].push_back( v );
			Graph[v].push_back( u );
		}
		getID( 1, 0 ); read( M );
		for( int i = 1; i <= M; ++ i )	read( times[i] );
		sort( times + 1, times + 1 + M, greater<LL>( ) );
		sort( cont + 1, cont + N, greater<LL>( ) );
		LL Ans = 0;
		if( M < N ){
			for( int i = M + 1; i <= N; ++ i )	times[i] = 1;
			for( int i = 1; i < N; ++ i )	Ans = ( Ans + ( cont[i] * times[i] ) % mod ) % mod;
		}
		else{
			Ans = cont[1];
			for( int i = 1; i <= M - N + 2; ++ i )	Ans = Ans * times[i] % mod;
			for( int i = 2; i < N; ++ i )	Ans = ( Ans + ( cont[i] * times[M - N + i + 1] ) % mod ) % mod;
		}
		write( Ans ), putchar( '\n' );
	}
	return 0;
}
```

---

## 作者：K_Madoka (赞：0)

易想出一个简单的贪心方案：拿最大的权值乘上最大的经过次数

然后如果$m>n$，我们就把前面最大的权值一起乘起来

如果$m<=n$，我们发现数不够了，就要迫不得已地补上1

最后按照前面的贪心策略算出答案即可

```cpp
#define MAXN 200010
const ll mod=1e9+7;
struct EDGE{ll nxt,to;}edge[MAXN<<1];
ll q,n,m,p[MAXN],head[MAXN],siz[MAXN],t[MAXN],tot,ans;
void add_edge(ll u,ll v){edge[++tot].nxt=head[u];edge[tot].to=v;head[u]=tot;}
void init(){
    memset(edge,0,sizeof(edge));
    memset(t,0,sizeof(t));
    memset(p,0,sizeof(p));
    memset(head,0,sizeof(head));
    tot=0;ans=0;
}
void dfs(ll u,ll fa){
    siz[u]=1;
    for(int i=head[u];i;i=edge[i].nxt){
        ll v=edge[i].to;
        if(v==fa)continue;
        dfs(v,u);
        siz[u]+=siz[v]; //注意用万能头不能用siz，否则冲突CE
    }
    t[u]=siz[u]*(n-siz[u]); //注意此处不能取膜，否则顺序会改变影响答案
}
int main(){
    cin>>q;
    while(q--){
        init();
        cin>>n;
        for(int i=1;i<n;i++){
            ll u,v;
            cin>>u>>v;
            add_edge(u,v);
            add_edge(v,u);
        }
        cin>>m;
        for(int i=1;i<=m;i++)cin>>p[i];
        dfs(1,0);    //计算经过次数，dfs
        for(int i=m+1;i<n;i++)p[i]=1;
        sort(p+1,p+max(n-1,m)+1);  //
        for(int i=n;i<=m;i++)  //合并top
            p[n-1]=(p[n-1]*p[i])%mod;
        sort(t+2,t+n+1);    //从小到大排序
        for(int i=n-1;i>=1;i--)  //计算答案
            ans=(ans+p[i]%mod*t[i+1]%mod)%mod;
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：lndjy (赞：0)

考场上做出来的，上了一波分（

对于第一个条件，很好满足。

第二个条件是它们的乘积为 $k$，这个就要处理一下 $p$ 了：

当 $m<n-1$ 时，要填上 $1$ 直到 $m=n-1$。

当 $m>n-1$ 时，要把两个最大的合并成一个新的数，值为两个数的积，直到 $m=n-1$。合并最大的原因在后面。

这样第三个条件也满足了，因为这样不会出现把两个数合并然后产生新的一个 $1$。

然后我们得到了 $n-1$ 个数，现在的问题是如何分配给每条边才能让答案最大。

考虑每条边对答案有多少次贡献。一条路径被经过，仅当起点是它左边的一个点，终点是它右边的一个点。然后把最大的边权分给出现次数最多的就可以了。

dfs 预处理一下每个子树的大小，记为 $sz_k$ ，那么左边的节点数就是 $sz_{to_i}$，右边是 $n-sz_{to_i}$，乘起来就是出现多少次。然后存起来排序就可以计算了。

```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1e5+5,mod=1e9+7;
struct edge
{
	int to,nxt;
}e[N*2];
long long n,cnt,m,head[N],sz[N];
long long p[N];
vector<long long> v;
void add(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs(int now,int fa)
{
	sz[now]=1;
	for(int i=head[now];i;i=e[i].nxt)
	{
		if(e[i].to==fa) continue;
		dfs(e[i].to,now);
		sz[now]+=sz[e[i].to];
		v.push_back(sz[e[i].to]*(n-sz[e[i].to]));
	}
}
void clear()
{
	cnt=0;
	memset(head,0,sizeof head);
	v.clear();
}
void solve()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int a,b;
		cin>>a>>b;
		add(a,b);
		add(b,a);
	}
	cin>>m;
	for(int i=1;i<=m;i++)
	cin>>p[i];
	sort(p+1,p+m+1);
	while(m>n-1)
	{
		m--;
		p[m]*=p[m+1];
		p[m]%=mod;
	}
	while(m<n-1)
	{
		p[++m]=1;
	}
    if(p[m]==1)
	sort(p+1,p+m+1);
	dfs(1,0);
	sort(v.begin(),v.end());
	long long ans=0;
	for(int i=v.size()-1;i>=0;i--)
	{
		ans+=(v[i]%mod)*p[i+1];
		ans%=mod;
	}
	cout<<ans<<endl;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		clear();
		solve();
	}
	return 0;
}
```


---


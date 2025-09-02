# [ARC105C] Camels and Bridge

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc105/tasks/arc105_c

$ 1 $ から $ N $ の番号がついた $ N $ 頭のラクダがいます。

ラクダ $ i $ の体重は $ w_i $ です。

あなたはラクダたちに隊列を組ませ、$ M $ 個のパーツからなる橋を渡らせようとしています。

あなたは橋を渡る前にラクダたちの隊列を決め(番号の昇順となる必要はありません)、ラクダどうしを任意の非負の実数の間隔で並ばせることができます。 ラクダたちはこの決められた間隔を保って橋を渡ります。

橋の $ i $ 番目のパーツは長さ $ l_i $ で耐荷重は $ v_i $ です。 パーツ内部(両端を除く)にいるラクダたちの体重の総和が $ v_i $ より大きくなると、橋は崩落してしまいます。

橋が崩落しないようにラクダたちを渡らせることが可能かどうかを判定し、可能ならばそのときの先頭のラクダと末尾のラクダの距離としてありうる値の最小値を求めてください。 これは整数になることが証明できるので、整数で出力してください。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 2\ \leq\ N\ \leq\ 8 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ w_i,l_i,v_i\ \leq\ 10^8 $

### Sample Explanation 1

\- 例えば、先頭から順に $ 1,3,2 $ の順番に並べ、ラクダどうしの間隔をそれぞれ $ 0,10 $ にすることで橋が崩落しないようにラクダたちを渡らせることが可能です。 - パーツ $ 1 $ ではラクダ $ 1,3 $ あるいはラクダ $ 2 $ のみがパーツの内部にいる状態が起こります。どちらもパーツの内部にいるラクダたちの体重の総和がパーツ $ 1 $ の耐荷重である $ 4 $ 以下のため、橋が崩落することはありません。 - パーツ $ 2 $ ではラクダ $ 1,3 $ あるいはラクダ $ 2 $ のみがパーツの内部にいる状態が起こります。どちらもパーツの内部にいるラクダたちの体重の総和がパーツ $ 1 $ の耐荷重である $ 6 $ 以下のため、橋が崩落することはありません。 - ラクダどうしの間隔が $ 0 $ でもよいこと、パーツの内部はパーツの両端を含まないことに注意してください。

### Sample Explanation 2

\- どのようにしても橋が崩落してしまう場合は `-1` を出力してください。

## 样例 #1

### 输入

```
3 2
1 4 2
10 4
2 6```

### 输出

```
10```

## 样例 #2

### 输入

```
2 1
12 345
1 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
8 1
1 1 1 1 1 1 1 1
100000000 1```

### 输出

```
700000000```

## 样例 #4

### 输入

```
8 20
57 806 244 349 608 849 513 857
778 993
939 864
152 984
308 975
46 860
123 956
21 950
850 876
441 899
249 949
387 918
34 965
536 900
875 889
264 886
583 919
88 954
845 869
208 963
511 975```

### 输出

```
3802```

# 题解

## 作者：dd_d (赞：4)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/16869608.html)
### 题意  
给定 $n$ 只骆驼和每条骆驼的重量 $a_i$。  
这些骆驼要通过一条路，这条路被分为 $m$ 个部分，每个部分的长度为 $l_i$，限重为 $v_i$。同时经过这部分的骆驼的重量和不能超过限重，否则就会坍塌。  
你可以指定这 $n$ 只骆驼的顺序和两两之间的距离，问第一只骆驼和最后一只的最短距离。如果走不了，输出 $-1$。  
$n \leq 8,m \leq 10^5,l_i,r_i,v_i \leq 10^8$。
### Sol  
看到 $n$ 很小，考虑暴力一点的做法。  
首先记一个 $w_s$ 表示当前骆驼集合为 $s$ 时需要隔开的距离。  
然后暴力枚举骆驼的顺序，记 $dp_i$ 表示前 $i$ 只骆驼的最短距离。直接转移即可。  
时间复杂度 $O(n!n^2)$。  
### Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define lowbit(x) (x&(-x))
using namespace std;
inline char gc()
{
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
uint32_t y=rnd();//normally y will in [0,2^32)
const int N=1e5+10;
int n,a[N],l[N],v[N],w[N],p[N],dp[N],ans,m;
signed main()
{
	n=read(); m=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1;i<=m;i++) l[i]=read(),v[i]=read();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (a[i]>v[j]) return puts("-1"),0;
	for (int S=1;S<(1<<n);S++)
	{
		int s=0;
		for (int i=1;i<=n;i++)
			if ((S>>(i-1))&1) s+=a[i];
		for (int i=1;i<=m;i++)
			if (s>v[i]) w[S]=max(w[S],l[i]);
	}
	for (int i=1;i<=n;i++) p[i]=i; ans=0x3f3f3f3f;
	do
	{
		dp[0]=0;
		for (int i=2;i<=n;i++)
		{
			int now=1<<(p[i]-1); dp[i]=0;
			for (int j=i-1;j;j--) now|=1<<(p[j]-1),dp[i]=max(dp[i],dp[j]+w[now]);
		}
		ans=min(ans,dp[n]);
	}while(next_permutation(p+1,p+n+1));
	writeln(ans);
}




```

---

## 作者：Daeyr_Xu (赞：2)

**思路：状压动规，深度优先搜索**

从题目中看出 $n\le8$，由此可以看出，此题可以用状压动规。

首先输入骆驼的数量和每条骆驼的重量…~~（废话）~~，并判断最大的骆驼重量，毕竟若最重的骆驼过不了，这条队伍就垮了！于是返回 $-1$。

然后是枚举骆驼在桥上的状态，（例如：若 $n=3$，$101$ 就代表了第一只和第三只骆驼在桥上）累计该桥段骆驼的总重量，记录该状态桥段最长单个承载限制长度，即限重小于其总重的桥中最长的长度，就是在此状态下第一个和最后一个骆驼相距的最短距离（这里可能有点抽象，望被理解）。

其次是~~人人喜爱的~~搜索环节：搜索并记录全部排列方式，时间复杂度 $O(n!)$。

接下来是状压部分：设 $dp_{i,j}$ 为第 $i$ 只骆驼和第 $j$ 只骆驼的最短距离，则最后的答案为 $\min(dp_{1,n})$。

$dp_{i,j}$ 的初始化为原来记录的该排列状态的桥段最长单个承载长度。

故转移方程： 

$dp_{i,j}=\max\limits_{i+1 \le k \le j-1} (dp_{i,k}+dp_{k,j})$ 

（注意这里的“取最大”是指桥段最长承载限制长度，不是最短距离）。

综上，时间复杂度 $O(n!n^3+nm)$，可以通过此题（可喜可贺），代码如下：



```cpp
#include<bits/stdc++.h>
#define int long long //数据范围较大，记得long long 
using namespace std;
const int N = 1e5+5;
int n,m,a[10],l[N],v[N],len[1<<10],ans=INT_MAX;
int vis[10],c[10],dp[10][10]; //dp[i][j]为第i只骆驼和最后第j只的最短距离 
void check(){
	//初始化为原来记录的该排列状态的桥段最长承载长度（limit_len） 
	for (int i=1;i<=n;i++){
		int g=(1<<(c[i]-1));
		for (int j=i+1;j<=n;j++){
			g += (1<<(c[j]-1));
			dp[i][j]=len[g];
		}
	}
	//转移方程：dp[i][j]=max{dp[i][k]+dp[k][j]}(i+1<=k<=j-1) 
	for (int i=n;i>=1;i--)
		for (int j=i+2;j<=n;j++)
			for (int k=i+1;k<=j-1;k++)
				dp[i][j] = max(dp[i][j],dp[i][k]+dp[k][j]);
	//最后的答案为min{dp[1][n]}； 
	ans = min(ans,dp[1][n]);
}
void dfs(int x){ //搜索并记录全部排列方式 
	if(x==n+1){
		check();
		return ;
	}
	for (int i=1;i<=n;i++)
		if(!vis[i]){
			vis[i]=1;
			c[x] = i; //记录排列方式 
			dfs(x+1);
			vis[i]=0; // 回溯 
		}
}
signed main(){
//	freopen("camel.in","r",stdin);
//	freopen("camel.out","w",stdout);
	cin >> n >> m;
	int maxn(0);
	for (int i=1;i<=n;i++){
		cin >> a[i];
		maxn = max(maxn,a[i]); //判断最大的骆驼重量 
	}
	for (int i=1;i<=m;i++){
		cin >> l[i] >> v[i];
		//特判最重的骆驼是否能通过，否则输出-1 
		if (v[i]<maxn){
			cout << "-1" << '\n';
			return 0;
		}
	}
	//枚举在桥上的骆驼状态
	for (int i=0;i<=(1<<n)-1;i++)
		if(__builtin_popcount(i)>1){
			int val(0);
			//累计该桥段骆驼的总重量
			for (int j=0;j<n;j++)
				if ((1<<j)&i) val+=a[j+1]; 
			//记录该状态桥段最长承载长度（limit_len）
			for (int j=1;j<=m;j++)
				if (val>v[j]) len[i]=max(len[i],l[j]);
		}
	dfs(1);//搜索 
	cout << ans;
	return 0;
}
```

---

## 作者：Petit_Souris (赞：2)

很像是 NOIP T2 难度会考的题目，很符合我对 CNOI 的想象。

起手一个 $n\le 8$，一个全排列就排上去了。现在我们已经知道了顺序，要求首尾距离的最小值。我们可以建立一个类似最长路的结构：设 $d_i$ 为 $1$ 和 $i$ 之间的最短距离，那么对于一个区间 $[l,r]$ 和限制 $(L,V)$，如果 $[l,r]$ 的重量和超过了 $V$，那么 $d_l+L\ge d_r$，从 $l$ 向 $r$ 连一条长度为 $L$ 的边，那么 $1\to n$ 的最长路就是最小距离。

这样得到了一个 $\mathcal O(n!n^2m)$ 的做法，无法通过。但是我们发现，我们每次满足的一定是 $L\le s$ 的一些限制，且我们只需要保留这些限制中最紧的一个即可。那么我们可以按照 $L$ 排序，求出前缀最大值。这样每次只要进行一个二分就行了，时间复杂度 $\mathcal O(n!n^2\log m)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=1e5+9,INF=1e16;
ll n,m,a[N],ans=INF,id[N],sum[N],pre[N],dis[N];
pii b[N];
vector<pii>to[N];
void adde(ll x,ll y,ll z){
    to[x].push_back({y,z});
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),m=read();
    rep(i,1,n)a[i]=read(),id[i]=i;
    rep(i,1,m)b[i].second=read(),b[i].first=read();
    rep(i,1,n){
        rep(j,1,m){
            if(a[i]>b[j].first)return puts("-1"),0;
        }
    }
    sort(b+1,b+m+1);
    rep(i,1,m)pre[i]=max(pre[i-1],b[i].second);
    do{
        rep(i,1,n)sum[i]=sum[i-1]+a[id[i]],dis[i]=-INF,to[i].clear();
        dis[1]=0;
        rep(i,1,n){
            rep(j,i+1,n){
                ll s=sum[j]-sum[i-1];
                ll l=1,r=m,pos=0;
                while(l<=r){
                    ll mid=(l+r)>>1;
                    if(b[mid].first<s)pos=mid,l=mid+1;
                    else r=mid-1;
                }
                if(pos){
                    ll v=pre[pos];
                    adde(i,j,v);
                }
            }
        }
        rep(i,1,n){
            for(pii es:to[i]){
                ll j=es.first,k=es.second;
                dis[j]=max(dis[i]+k,dis[j]);
            }
        }
        ans=min(ans,dis[n]);
    }while(next_permutation(id+1,id+n+1));
    if(ans==(ll)1e16)write(-1);
    else write(ans);
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：_edge_ (赞：2)

来自官方题解。

看到 $n$ 这么小，首先需要想到的是全排列，这样能确定他的顺序，然后我们再来考虑如何 check 最小距离。

思考这么一件事情，对于两个点 $i,j$ 设 $i<j$，那么他们两个所拥有的限制就是对于一条限制 $k$，如果 $sum_j-sum_{i-1} \ge s[k]$，那么他们两个之间的距离必须是 $\ge v[k]$，然后可以很好的发现这东西是一个 DAG，然后我们在这张图上跑拓扑排序，最长路就解决该问题了。

这里处理的时候有点细节是，不能一个一个枚举限制，利用二分答案和前缀 max 可以很快速建边。

时间复杂度为 $O(n! \times n^2 \times \log m)$。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e5+5;
const int INFN=15;
struct _node_data{
    int v,s;
}aa[INF<<1];
int n,m,a[INF],p[INF],sum[INF],res=1e18,vis[INF],Max1[INF],in[INF];
int Map[INFN][INFN],dis_[INFN];
queue <int> q;
void solve() {
    memset(dis_,0,sizeof dis_);
    memset(Map,0,sizeof Map);
    // for (int i=1;i<=n;i++) cout<<p[i]<<" ";
    // cout<<"\n";
    for (int i=1;i<=n;i++) sum[i]=sum[i-1]+a[p[i]],in[i]=0;
    for (int i=1;i<=n;i++) {
        for (int j=i+1;j<=n;j++) {
            int v=sum[j]-sum[i-1];
            int l=1,r=m,ans=-1;
            while (l<=r) {
                int Mid=(l+r)>>1;
                if (aa[Mid].s<v) l=(ans=Mid)+1;
                else r=Mid-1;
            }
            if (ans==-1) continue;
            // cout<<i<<" "<<j<<" "<<p[i]<<" "<<p[j]<<" "<<Max1[ans]<<" fad?\n";
            Map[i][j]=Max1[ans];
            in[j]++;
        }
    }

    for (int i=1;i<=n;i++)
        if (!in[i]) q.push(i);
    while (q.size()) {
        int x=q.front();q.pop();
        for (int v=1;v<=n;v++) {
            if (!Map[x][v]) continue;
            dis_[v]=max(dis_[v],dis_[x]+Map[x][v]);
            if (!--in[v]) q.push(v);
        }
    }
    res=min(res,dis_[n]);
    return ;
}
void DFS(int x) {
    if (x>n) {
        solve();
        return ;
    }
    for (int i=1;i<=n;i++) {
        if (vis[i]) continue;
        vis[i]=1;p[x]=i;
        DFS(x+1);
        vis[i]=0;
    }
    return ;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;int Max=0,Min=1e18;
    for (int i=1;i<=n;i++) cin>>a[i],Max=max(Max,a[i]);
    for (int i=1;i<=m;i++) cin>>aa[i].v>>aa[i].s,Min=min(Min,aa[i].s);
    if (Max>Min) {cout<<"-1\n";return 0;}
    sort(aa+1,aa+1+m,[](_node_data xx,_node_data yy) {return xx.s<yy.s;});
    for (int i=1;i<=m;i++) Max1[i]=max(Max1[i-1],aa[i].v);
    DFS(1);
    cout<<res<<"\n";
    return 0;
}
```


---

## 作者：FRZ_29 (赞：1)

# [ARC105C] Camels and Bridge 题解
出自梦熊比赛后，梦熊比赛出原题了，忘周知。  
[也许更好的阅读体验](https://www.cnblogs.com/FRZ29/p/18327643)  
## 思路
全排列，差分约束，二分。  

### 全排列
 $n \leq 8$ ，且要指定顺序，易想到用全排列枚举所有状态。  

### 差分约束
在全排列之后，需要求得每种状态的最短距离。定义所有骆驼的编号的集合为 $S$ ，所有路的部分的编号的集合为 $E$，定义数组 $sum,dis$ , $sum_i$ 表示 $\sum_{j = 1}^ia_j$ , $dis_i$ 表示从起点到点 $i$ 的最短距离， 则对于每对 $i, j(i,j \in S, i \lt j)$ ，应该有若 $sum_j - sum_{i - 1} \geq v_k$ ,则 $dis_j - dis_i \geq l_k(k \in E)$ 。 转换一下，即若$sum_j - sum_{i - 1} \geq v_k$ ,则 $dis_i + l_k \leq dis_j(k \in E)$ , 很明显的差分约束条件，跑差分约束就行。

### 二分
跑差分约束需要建边。
对每个路的部分按 $v$ 从小到大排序，对于每个 $dv = sum_j - sum_{i - 1}$, 二分最大的 $v_k \lt dv$ , 此时用所有 $l_i(1 \leq i \leq k)$ 建边等效与用最大的 $l_i$ 建边。用前缀 max 可以 $O(1)$ 的建边。

总时间复杂度为 $O(n!n^2\log m + m\log m)$ 。 

[代码](https://www.luogu.com.cn/paste/nyzuokad)

---

## 作者：xxseven (赞：1)

这是一篇主席树题解。   

判无解很简单，如果有一个桥的限重小于最重的骆驼的重量，那么必然走不过去。 

发现骆驼的顺序是一个极难确定的东西，又因为 $n$ 的范围只有 $8$，我们可以直接枚举全排列。

但现在问题又出现了：我们虽然有了骆驼的顺序，但是我们还需要确定在该顺序下骆驼的位置。因为我们枚举全排列已经有 $n!$ 的复杂度，我们需要尽快求出这个值。

首先有一个显然的贪心策略：当我们在最后增加一只骆驼时，如果能放在离上一匹骆驼更近的位置，那么放在更近位置肯定不劣。

接下来考虑我们增加一只骆驼时会发生什么。    
我们发现，增加一只骆驼后，当前序列的任何一个后缀都有可能不满足当前的限制。对于一个后缀，所有限重小于其总重的桥都会对其造成限制，而限制最大的是其中长度最长的桥。  
所以对于每个后缀，我们求出它的总重，要查询的就是限重小于其总重的桥中最长的长度。  

对于这个问题，我们可以采用主席树轻松解决：  
先对所有桥按照限重升序排序，之后依次将限重作为权值插入到主席树中，每插入一个桥新建一个版本，这样只选取限重小于某个数的桥就可以转换为一个版本上的查询，查找最大值即可。  
~~话说数据结构真暴力啊，要什么直接丢进去然后查就行了~~

时间复杂度 $O(n! n^2 \log m + m \log m)$，可以通过此题。

下面是代码：
```cpp
#include<bits/stdc++.h>
#define debug puts("NOIpRP++")
#define mid (L+R>>1)
using namespace std;
const int M=10,N=1e5+6;
int n,m,a[M],b[N],c[N],bm;
struct edge{
	int l,v;
	bool operator <(const edge &b) const{
		return v<b.v;//升序排序，之后按此顺序插入到主席树中
	}
}f[N]; 

void init(){
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=m;++i){
		cin>>f[i].l>>f[i].v;
		b[i]=f[i].l;
		c[i]=f[i].v;
	}
	sort(b+1,b+m+1);
	sort(c+1,c+m+1);
	sort(f+1,f+m+1);
	bm=unique(b+1,b+m+1)-b-1;
	for(int i=1;i<=m;++i){
		f[i].l=lower_bound(b+1,b+bm+1,f[i].l)-b;
	}//离散化可以减少常数，虽然这题不太需要
}
struct node{
	int l,r,val;
}t[N<<5];
int idx,rt[N];
void update(int &now,int pre,int L,int R,int x){
	now=++idx;
	t[now]=t[pre];
	t[now].val++;
	if(L==R) return;
	if(x<=mid) update(t[now].l,t[pre].l,L,mid,x);
	else update(t[now].r,t[pre].r,mid+1,R,x);
}
int qry(int pos,int L,int R){//主席树查询最大值
	if(L==R) return b[L];
	if(t[t[pos].r].val>=1) return qry(t[pos].r,mid+1,R);
	return qry(t[pos].l,L,mid);
}
int ans=1e15,used[M],dis[M],wei[M];
void dfs(int lv){
	if(lv==n+1){
		ans=min(dis[n],ans);	
		return;
	}
	for(int i=1;i<=n;++i){
		if(used[i]) continue;
		used[i]=1;
		wei[lv]=wei[lv-1]+a[i];//前缀和优化计算总重
		int nxt=0;
		for(int res,pos,j=1;j<lv;++j){
			if(wei[lv]-wei[j-1]<c[1]) continue;//没有限制，直接continue
			pos=lower_bound(c+1,c+m+1,wei[lv]-wei[j-1])-c-1;
			res=qry(rt[pos],1,bm);
			nxt=max(nxt,dis[j]+res);
		}
		dis[lv]=nxt;
		dfs(lv+1); 
		used[i]=0;
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	init();
	for(int i=1;i<=n;++i){
		if(a[i]>c[1]){ //如果存在一个桥单只骆驼都走不过去，那么无解
			cout<<-1; return 0;
		}
	}
	for(int i=1;i<=m;++i){
		update(rt[i],rt[i-1],1,bm,f[i].l);
	}
	dfs(1);
	cout<<ans;
	return 0;
}

```

---

## 作者：User_Unauthorized (赞：1)

## 题意

给定 $N$ 个重物，其中第 $i$ 个重物的重量为 $w_i$。现在要将其排成一排，可以任意指定相邻两个重物的距离。

同时给定 $M$ 个限制，其中第 $i$ 个限制为 $(l_i, v_i)$，表示要求不存在长度为 $l_i$ 的线段，使得其包括的重物重量之和大于 $v_i$。

最小化重物间的最大距离或报告无解。

- $2 \le N \le 8$
- $1 \le M \le 10^5$
- $1 \le w_i, l_i, v_i \le 10^8$

## 题解

首先，若 $\max\limits_{i = 1}^{N} w > \min\limits_{i = 1}^{M} v_i$，那么一定无解，反之一定有解。下文中假设一定有解。

由于 $N$ 的值很小，所以可以考虑枚举重物之间的排列顺序，然后依次计算 $N!$ 种排列的最小化的最大距离。

考虑如何计算，不妨设 $f_{i}$ 表示第 $i$ 个重物到第一个重物的最小距离，那么有转移

$$f_{i} = \max\limits_{j = 1}^{i - 1} \left\{f_j + L\left(\sum\limits_{k = j}^{i}w_i\right)\right\}$$

其中 $L(x)$ 表示一段总重量为 $x$ 的线段的最短长度。

现在问题转化为了如何快速求出 $L(x)$，发现 $L(x)$ 可以表示为：

$$\max\limits_{1 \le i \le M \land v_i \le x} l_i$$

因此我们可以将所有限制按 $v_i$ 的大小升序排序，那么求 $L(x)$ 时只需要二分出最大的满足 $v_i \le x$ 的 $i$ 后查询前缀最大值即可。

时间复杂度 $\mathcal{O}(N!N^2\log M + M \log M)$，空间复杂度 $\mathcal{O}(N + M)$，可以通过。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::pair<valueType, valueType> ValuePair;
typedef std::vector<ValuePair> PairVector;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, M;

    std::cin >> N >> M;

    ValueVector W(N + 1, 0);

    for (valueType i = 1; i <= N; ++i)
        std::cin >> W[i];

    PairVector A(M + 1);

    for (valueType i = 1; i <= M; ++i)
        std::cin >> A[i].second >> A[i].first;

    {
        valueType maxW = std::numeric_limits<valueType>::min(), minV = std::numeric_limits<valueType>::max();

        for (valueType i = 1; i <= N; ++i)
            maxW = std::max(maxW, W[i]);

        for (valueType i = 1; i <= M; ++i)
            minV = std::min(minV, A[i].first);

        if (maxW > minV) {
            std::cout << -1 << std::endl;

            return 0;
        }
    }

    std::sort(A.begin() + 1, A.end());

    ValueVector max(M + 1, 0);

    for (valueType i = 1; i <= M; ++i)
        max[i] = std::max(max[i - 1], A[i].second);

    auto calc = [&](valueType sum) -> valueType {
        valueType l = 1, r = M, ans = 0;

        while (l <= r) {
            valueType mid = (l + r) / 2;

            if (A[mid].first < sum) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        return max[ans];
    };

    ValueVector P(N + 1, 0);

    std::iota(P.begin(), P.end(), 0);

    valueType ans = std::numeric_limits<valueType>::max();

    do {
        ValueVector F(N + 1, 0);

        F[0] = 0;
        for (valueType i = 1; i <= N; ++i) {
            F[i] = 0;

            valueType sum = W[P[i]];

            for (valueType j = i - 1; j >= 1; --j) {
                sum += W[P[j]];

                F[i] = std::max(F[i], F[j] + calc(sum));
            }
        }

        ans = std::min(ans, F[N]);
    } while (std::next_permutation(P.begin() + 1, P.end()));

    std::cout << ans << std::endl;
}
```

---

## 作者：肖翔 (赞：1)

思路：二分 + DP

首先 $ n $ 这么小，且要安排骆驼顺序，想到先全排列枚举。

问题变成如何安排骆驼间距。

记 $ dp_{i} $ 表示前 $ i $ 个骆驼所需要的距离。

则显然的 $ dp_{i}=max\{dp_{j}+len(j,i )|j \leqslant i\} $

（注意，这里为了保证所有骆驼可以通过所有桥，取的应该是最大值，下面的最大值同理。）

问题变为给定了一组骆驼，怎么求 $ len(i,j) $

此时骆驼总重 $ sum $ 是一定的。

发现它只对 $ v_{i} \leqslant sum$ 的桥有要求，要满足 $ len(i,j) \geqslant  l_{i} $


~~长得像个二维偏序~~


不考虑这种玩意，反正排序去掉一重限制肯定要的。

按重量排序，用 $ sum $ 作关键字二分，找重量小于等于 $ sum $ 的桥，得到一个位置 $  pos $

即求 $ ans=max\{ l_{i}|i\leqslant pos\} $ 

排序完二分并暴力遍历后面的桥加卡常似乎可做（机房有人过）。

这里给一个标准一点的做法：


发现对于每个位置，他的 $ ans $ 是固定的，就是前面的 $l_{i}$ 的最大值。

这个完全可以预处理出来，递推一下预处理是 $ O(m) $ 的。

（我的实现里为了偷懒，直接把这个预处理出来的东西赋值给 $ l_{i} $ 了）

还有就是当只有一匹骆驼自己上桥也会塌时无解。

考虑最重的骆驼和最弱的桥即可。

综上，可以做到 $ O( n!\times n^2 \times \log m)$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
struct edge{
	int l,v;
}b[maxn];
int n,m;int w[maxn];
inline bool cmp(edge a,edge b){
	if(a.v==b.v)return a.l<b.l;
	return a.v<b.v;
}int a[maxn];
int dp[maxn];int sum[maxn];
int ans=1<<30;
inline int len(int x){
	int l=0,r=m+1,mid;
	while(l+1!=r){
		mid=l+r>>1;
		if(b[mid].v<x)l=mid;
		else r=mid;
	}
	return b[l].l;
}
inline void sol(){
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+w[a[i]];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			dp[i]=max(dp[i],dp[j]+len(sum[i]-sum[j-1]));
		}
	}
	ans=min(ans,dp[n]);
	return;
}
inline void make(int step);
int Max,Min=pow(2,30);
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&w[i]),Max=max(Max,w[i]);
	for(int i=1;i<=m;i++)scanf("%d%d",&b[i].l,&b[i].v);
	sort(b+1,b+m+1,cmp);
	for(int i=1;i<=m;i++){
		Min=min(Min,b[i].v);
		b[i].l=max(b[i-1].l,b[i].l);
	}
	if(Max>Min){
		puts("-1");
		return 0;
	}
	make(1);
	cout<<ans;
}
bool vis[maxn];
inline void make(int step){
	if(step==n+1){
		sol();
		return;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			vis[i]=1;
			a[step]=i;
			make(step+1);
			vis[i]=0;
			a[step]=0;
		}
	}
	return;
}
```


---

## 作者：Dovish (赞：1)

## 题解
首先，我们对题目中关于重量的限制做一个转换：对于一个确定的骆驼序列的任意一个区间，如果其总重量大于 $v_i$，则其长度至少为 $l_i$。

知道了这样的限制之后，我们做一次区间 DP 就可以求出整个序列的最小合法长度了。

这样，我们枚举排列，对于每一个区间 check，然后区间 DP，但是复杂度是 $O(n!(n^2m+n^3))$。

考虑优化：对于任意一个区间在求限制的时候其实与其内部的顺序无关，只与其总重量相关。

那我们就可以预处理用状压表示出每一种骆驼集合，这样做就是 $O(n!n^3+2^nm)$，可以通过。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=a;i<=b;++i)
#define low(i,a,b) for(register int i=a;i>=b;--i)
#define edge(i,u) for(int i=head[u];i;i=e[i].next)
using namespace std;
const int N=10,M=1e5+10,inf=1e18,base=100;
int a[N],n,m;
int l[M],v[M];
int limit[1<<N];
int maxn;
int c[N],vis[N];
int f[10][10];
int ans=inf;
void check()
{
	rep(i,1,n)
	{
		int g=(1<<(c[i]-1));
		rep(j,i+1,n)
		{
			g+=(1<<(c[j]-1));
			f[i][j]=limit[g];
		}	
	}
	low(i,n,1)
	rep(j,i+2,n)
	{
		rep(k,i+1,j-1)
		f[i][j]=max(f[i][j],f[i][k]+f[k][j]);
	}
	ans=min(ans,f[1][n]);
}
void dfs(int deep)
{
	if(deep==n+1)
	{
		check();
		return;
	}
	rep(i,1,n)
	if(!vis[i])
	{
		vis[i]=1;
		c[deep]=i;
		dfs(deep+1);
		vis[i]=0;
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	rep(i,1,n)
	cin>>a[i],maxn=max(maxn,a[i]);
	rep(i,1,m)
	{
		cin>>l[i]>>v[i];
		if(v[i]<maxn)
		{
			cout<<-1;
			return 0;
		}//特判无解的情况
	}
	rep(i,0,(1<<n)-1)
	if(__builtin_popcount(i)>1)
	{
		int val=0;
		rep(j,0,n-1)
		if((1<<j)&i)
		val+=a[j+1];
		rep(j,1,m)
		{
			if(val>v[j])limit[i]=max(limit[i],l[j]);
		}
	}
	dfs(1);
	cout<<ans<<'\n';
}
```

---

## 作者：yingxilin (赞：0)

# [ARC105C] Camels and Bridge 题解

https://www.luogu.com.cn/problem/AT_arc105_c

记：这是24年夏天在北京梦熊写的（模拟赛撞原），希望这年夏天 fowever 。

## sol
首先 $n$ 很小，所以可以去暴力枚举顺序，也就是全排列。　

$W_s$ 表示排列为 $s$ 时的间距。又令 $f_i$ 为前 $i$ 只的最优决策，即最短距离，然后直接状态转移。

核心代码
```cpp
do{
        f[0]=0;
        FOR(i,2,n)
        {
            int now=1<<(p[i]-1);
            f[i]=0;
            for(int j=i-1;j;j--)
            {
                now|=1<<(p[j]-1);
                f[i]=max(f[i],f[j]+w[now]);//这里是状态转移方程
            }
        }
        ans=min(ans,f[n]);
    }while(next_permutation(p+1,p+n+1));
```

## 总代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int p[10];
const int N=1e5+5;
int f[N];
int w[N];
int a[N];
int v[N];
int l[N];
#define inf 0x3f3f3f3f
int ans=inf;
#define FOR(i,_l,_r) for(int i=_l;i<=_r;i++)
int main()
{
    cin>>n>>m;
    FOR(i,1,n) cin>>a[i];
    FOR(i,1,m) cin>>l[i]>>v[i];
    FOR(i,1,n)
        FOR(j,i,m)
        {
            if(a[i]>v[j])
            {
                puts("-1");
                return 0;
            }
        }
    FOR(S,1,(1<<n)-1)
    {
        int len=0;
        FOR(i,1,n) if((S>>(i-1))&1) len+=a[i];
        FOR(i,1,m) if(len>v[i]) w[S]=max(w[S],l[i]);
    }
    FOR(i,1,n) p[i]=i;
    do{
        f[0]=0;
        FOR(i,2,n)
        {
            int now=1<<(p[i]-1);
            f[i]=0;
            for(int j=i-1;j;j--)
            {
                now|=1<<(p[j]-1);
                f[i]=max(f[i],f[j]+w[now]);//这里是状态转移方程
            }
        }
        ans=min(ans,f[n]);
    }while(next_permutation(p+1,p+n+1));
    cout<<ans;
    return 0;   
}
```

---

## 作者：Frictional (赞：0)

## 题意
$n$ 只骆驼排好队，每两个骆驼之间有一定距离的间隔（间隔可以为0），每个骆驼有一个重量，有 $m$ 座桥，每座桥有一个长度 $l_i$ 和限重 $v_i$。求所有排列中，第一只骆驼和最后一只骆驼的最短距离。
## 解法
因为 $n\leqslant 8$，所以我们可以直接全排列骆驼的排列顺序。之后我们假设前面所有的骆驼都已经计算完了距离，当前要考虑第 $i$ 个骆驼（第一个骆驼直接放就行，所以这是一个类似数学归纳的证明）。显然骆驼在合法的放置情况下，与前一个骆驼距离越小越好。一个骆驼的放置要合法，那就要去看他的重量后缀和 $A_j$，长度为 $l_j$，那对于任意长度小于等于 $l_j$ 的桥他的承重都要大于等于 $A_j$。那我们就预处理出来所有的 $A_j$，所有承重小于等于 $A_j$ 的桥的最长长度。之后我们就能求出来第 $i$ 个骆驼与前几个骆驼的距离。

## Code

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define db double
#define U unsigned
#define P pair<int,int>
#define int long long
#define pb push_back
#define MP make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define debug(x) cerr<<#x<<'='<<x<<endl
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define gc getchar()
#define pc putchar
using namespace std;
inline int rd(){
    int x=0,f=1;
    char ch=gc;
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
    while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
    return x*f;
}
inline void wr(int x){
    if(x<0) x=-x;
    if(x>9) wr(x/10);
   pc((x%10)^48);
}
int n,m;
const int M=1e5+5;
int a[10];
map<int,int>maxx;
struct node{
    int l,v;
}f[M];
int tmp,tmp2=1e15;
void init(int now,int sum){
    if(now>n){
        FOR(i,1,m) if(f[i].v<sum) maxx[sum]=MAX(maxx[sum],f[i].l);
        return ;
    }
    init(now+1,sum);
    init(now+1,sum+a[now]);
}
int p[10];
void solve(){
    sort(a+1,a+1+n);
    int ans=1e15;
    do{
        memset(p,0,sizeof(p));
        int SumTemp;
        FOR(i,2,n){
            SumTemp=a[i];
            ROF(j,i-1,1){
                SumTemp+=a[j];
                p[i]=MAX(p[j]+maxx[SumTemp],p[i]);
            }
        }
        ans=MIN(ans,p[n]);
    }while(next_permutation(a+1,a+1+n));
    cout<<ans;
}
int minn=1e15;
signed main(){
    // freopen("camel.in","r",stdin);
    // freopen("camel.out","w",stdout);
    n=rd(),m=rd();
    FOR(i,1,n) a[i]=rd(),tmp=MAX(tmp,a[i]);
    FOR(i,1,m){
        f[i].l=rd(),f[i].v=rd();
        minn=MIN(minn,f[i].v);
    }
    if(minn<tmp){
        cout<<-1;
        return 0;
    }
    init(1,0);
    solve();
    // fclose(stdin);
    // fclose(stdout);
    return 0;
}
```

---

## 作者：laoliu12345 (赞：0)

## AT_arc105_c
### 题目思路
首先判断是否无解，很明显当骆驼重量的最大值大于桥承重的最小值时，我们无论如何也无法使得其通过此桥，故此时输出  -1。然后状压预处理当状态为  $i$  的骆驼合并到一起时所需的最小距离（是不是有点类似**差分约束**？这题差分约束也可做，但此处暂且不提）。

主体部分可以直接用   $O(n!)$  的时间复杂度枚举全排列，对于每个排列都单独进行 DP，状态转移方程   $f_j = \max(f_j,f_k+ maxl_i )$，其中   $i$  指此排列中  $j$  到  $k$  在原排列中所压成的状态，  $maxl_i$  在上文中已经预处理过。所以本题的时间复杂度就是  $O(2^nm+n! \times n^2)$  了。然后就可以愉快的写代码了。
### 题目代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100010;
struct edge{
	int l,w;
}e[N];
int n,m;
int v[15];
int maxl[N],s[15];
int f[15];
int minn=1e13;
int mi=1e11,ma=-1;
void work()
{
	memset(f,0,sizeof f);
	for(int i=1;i<=n;i++)
	{
		int sum=1<<(s[i]-1);
		for(int j=i-1;j;j--)
		{
			sum|=1<<(s[j]-1);
		    f[i]=max(f[i],f[j]+maxl[sum]);
		}
	}
	minn=min(minn,f[n]);
	return ;
}
signed main()
{
	//freopen("camel.in","r",stdin);
	//freopen("camel.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	    scanf("%lld",&v[i]),ma=max(ma,v[i]);
	for(int i=1;i<=m;i++)
	    scanf("%lld%lld",&e[i].l,&e[i].w),mi=min(mi,e[i].w);
	if(ma>mi)
	{
		cout<<-1<<endl;
		return 0;
	}
	for(int i=0;i<1<<n;i++)
	{
		int sum=0;
		for(int j=1;j<=n;j++)
		    if(i>>(j-1)&1)
		        sum+=v[j];
		for(int j=1;j<=m;j++)
		    if(sum>e[j].w)
		        maxl[i]=max(maxl[i],e[j].l);
	}
	for(int i=1;i<=n;i++)
	    s[i]=i;
	while(next_permutation(s+1,s+n+1))
	{
//		for(int i=1;i<=n;i++)
//		    cout<<s[i]<<" ";
//		cout<<endl;
		work();
	}
	printf("%lld\n",minn);
	return 0;
}
```

---

## 作者：時空 (赞：0)

### $\texttt{camel}$
[Link](https://www.luogu.com.cn/problem/AT_arc105_c)

选自梦熊模拟赛赛后补题。梦熊模拟赛出原题，望周知。

赛时想到了全排列，但是不会线性 $check$，遗憾离场。

解：看到 $n$ 这么小，很容易想到正解复杂度里会带一个 $n!$。

那么考虑全排列。

先预处理出一个 $w$，$w_s$ 表示骆驼集合为 $s$ 时，需要隔开的距离。

全排列枚举骆驼的顺序。

接下来考虑怎么线性 $check$。

考虑状压 DP。记 $dp_i$ 表示前 $i$ 只骆驼的最短距离。

然后就比较板了，转移即可。

注意到当一头骆驼的重量比一座桥的限重还大时无解，特判一下即可。

```cpp
for (ll S = 1; S < (1 << n); S ++ )
{
	ll T = 0;
	for (ll j = 1; j <= n; j ++ )
	{
		if ((S >> (j - 1)) & 1) T += camel[j];
	}
	for (ll j = 1; j <= m; j ++ )
	{
		if (T > B[j].v) w[S] = max(w[S], B[j].l);
	}
}
for (ll i = 1; i <= n; i ++ ) p[i] = i;
ll Ans = 1e18;
do
{
	dp[0] = 0;
	for (ll i = 2; i <= n; i ++ )
	{
		ll now = 1 << (p[i] - 1); dp[i] = 0;
		for (ll j = i - 1; j; j -- )
		{
			now |= 1 << (p[j] - 1);
			dp[i] = max(dp[i], dp[j] + w[now]);
		}
	}
	Ans = min(Ans, dp[n]);
}while(next_permutation(p + 1, p + n + 1));
cout << Ans << '\n';for (ll S = 1; S < (1 << n); S ++ )
{
	ll T = 0;
	for (ll j = 1; j <= n; j ++ )
	{
		if ((S >> (j - 1)) & 1) T += camel[j];
	}
	for (ll j = 1; j <= m; j ++ )
	{
		if (T > B[j].v) w[S] = max(w[S], B[j].l);
	}
}
for (ll i = 1; i <= n; i ++ ) p[i] = i;
ll Ans = 1e18;
do
{
	dp[0] = 0;
	for (ll i = 2; i <= n; i ++ )
	{
		ll now = 1 << (p[i] - 1); dp[i] = 0;
		for (ll j = i - 1; j; j -- )
		{
			now |= 1 << (p[j] - 1);
			dp[i] = max(dp[i], dp[j] + w[now]);
		}
	}
	Ans = min(Ans, dp[n]);
}while(next_permutation(p + 1, p + n + 1));
cout << Ans << '\n';
```

---

## 作者：Halberd_Cease (赞：0)

首先判断无解，如果任意一个部分的承重能力小于最大的骆驼重，则无解，其余情况有解。

考虑两个或者以上的骆驼之间的距离需要满足什么条件，设这些骆驼之间的距离为 $l$，那么这一群骆驼能过桥的充要条件是对于每一个长度大于 $l$ 的部分，承重能力均大于骆驼的总重量。

然后我们就可以发现，在骆驼群的重量递增时，前后所需的长度是单调不降的。

将所有的限制条件整合，表示成如“长度为 $l$ 的部分最多可以塞下质量和为 $w$ 的骆驼”的形式。

然后枚举骆驼顺序的全排列，讨论每一种情况，二分查找当前骆驼和前面的骆驼之间距离需要满足的关系（因为所需长度和骆驼重量是单调递增的，所以找到限制的最小质量，就找到了最小的距离），把每一种情况最前与最后的距离求出来，所有情况取最小就可以了。

[submission](https://atcoder.jp/contests/arc105/submissions/54715114)

---


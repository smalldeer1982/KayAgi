# [WFOI - 01]  刷题 （problem）

## 题目背景

简化题意：[$\texttt{Link}$](https://www.luogu.com.cn/paste/ievt77rm)。

## 题目描述

你初始能力为 $0$。

现在有 $n$ 个题库，每个题库的题有同一个难度 $a_i$，并且题目数量可以视为无限多。现在你要刷 $m$ 道题，每道题都是所有题中你选择出来的一道。

假设你目前做到的题目难度是 $x$，则：

当你的能力比这个题大或等于此题时，你将花费你的能力以攻破此题（此时你的能力减去 $x$）；否则，你将认真钻研此题，钻研出此题后能力增加 $x$（此时不会导致能力减少）。

现在你想知道你做 $m$ 题后能力最大值。由于你的小伙伴也要刷题，所以**有多次询问**，询问之间相互独立，也就是说每次询问的能力初值为 $0$。

## 说明/提示

- **样例 $1$ 解释：**
	
    当 $m=1$ 时，依次选择 $6$；

	当 $m=2$ 时，依次选择 $4,6$；
    
    当 $m=3$ 时，依次选择 $1,4,6$；
- **样例 $2$ 解释：** 

    当 $m=1$ 时，依次选择 $1$；

	当 $m=2$ 时，依次选择 $1,1$；

**本题采用 Subtask 捆绑测试。**

  Subtask 编号 | $n\le$ | $m\le$ | $T\le$
  :-: | :-: | :-: | :-: |
  **Subtask #0 ($5\texttt{pts}$)** | $5$ | $5$ | $100$ |
  **Subtask #1 ($10\texttt{pts}$)** | $5$ | $5$ | $10^5$ |
  **Subtask #2 ($10\texttt{pts}$)** | $200$ | $200$ | $100$ |
  **Subtask #3 ($15\texttt{pts}$)** | $200$ | $200$ | $10^5$ |
  **Subtask #4 ($10\texttt{pts}$)** | $200$ | $10^{18}$ | $10^5$ |
  **Subtask #5 ($50\texttt{pts}$)** | $2000$ | $10^{18}$ | $10^5$ |
  
对于 $100\%$ 的数据，$1 \le T \le 10^5$，$1 \le n\le 2000$，$1 \le m \le 10^{18}$，$\forall i,0 \le a_i \le 2000$。

## 样例 #1

### 输入

```
5 3
1 2 3 4 6
1
2
3```

### 输出

```
6
10
11```

## 样例 #2

### 输入

```
1 2
1
1
2```

### 输出

```
1
0```

# 题解

## 作者：€€£ (赞：15)

容易发现，最大的答案 $<2 \times a_{max}$​

容易发现，一个点若能够在 $x$ 时刻到达，则一定能在 $x+2$ 时刻到达

于是我们将一个点拆点，拆成奇数步到达以及偶数步到达

之后我们再连边并预处理出最短路

然后直接在线回答即可

---

## 作者：Wf_yjqd (赞：10)

补去年的作业题，交了两页才过，特此纪念

------------

考虑最优情况不会超过 $2\times\max(a_1,a_2,...,a_n)-1$，题目中取 $3999$ 即可。

考虑建图，共 $4000$ 个点，最多 $8\times10^6$ 条边。

如果走 $m$ 条边能到达 $x$，那么连续做两次最难的题，一加一减抵消，得到走 $m+2$ 条边一定也能到达 $x$。

于是对于任意一个点，$\operatorname{bfs}$ 维护奇数和偶数布走到的最短路。

这样当给定 $m$ 时，我们只需要枚举奇数和偶数布走到最优情况的最短路分别需要多少。

当无法取到最大值时，走 $m$ 步最大能走到哪个点，这一步可以维护一个奇数或偶数布的前缀最大值。

------------

说的简单，写起来还是很出错的。。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,bool> p;
static char buf[100],*p1=buf,*p2=buf,obuf[100],*p3=obuf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,100,stdin),p1==p2)?EOF:*p1++
#define putchar(x) (p3-obuf<100)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
template<typename item>
inline void read(register item &x){
    x=0;register int f=1;register char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c-'0'),c=getchar();
    x*=f;
}
static char cc[100];
template<typename item>
inline void print(register item x){ 
	register int len=0;
	if(x<0)x=-x,putchar('-');
    if(x==0)putchar('0');
	while(x)cc[len++]=x%10+'0',x/=10;
	while(len--)putchar(cc[len]);
}
//没必要快读快写，调试的时候TLE了，原因不在此
const int maxn=4084;
struct Node{
    int to,ne;
}e[maxn*maxn/2];
ll m;
int n,T,a[maxn],dis[maxn][2],ans[maxn];
int head[maxn],ecnt=1;
void add(int u,int v){
    e[ecnt]={v,head[u]};
    head[u]=ecnt++;
    return ;
}
queue<p> q;
void bfs(int x){
    memset(dis,0x7f,sizeof(dis));
    dis[x][0]=0;
    q.push({x,0});
    p t;
    while(!q.empty()){
        t=q.front();
        q.pop();
        for(int i=head[t.first];i;i=e[i].ne){
            if(e[i].to!=x&&dis[e[i].to][t.second^1]>1e9){//罪魁祸首，3999->1e9,TLE+MLE->AC
                dis[e[i].to][t.second^1]=dis[t.first][t.second]+1;
                q.push({e[i].to,t.second^1});
            }
        }
    }
    return ;
}
int main(){
    read(n);
    read(T);
    for(int i=1;i<=n;i++)
        read(a[i]);
    for(int i=0;i<=3999;i++)
        for(int j=1;j<=n;j++)
            if(i>=a[j])
                add(i,i-a[j]);
            else if(i+a[j]<=3999)
                add(i,i+a[j]);
    bfs(0);
    for(int i=1;i<=3999;i++){
        if(dis[i][0]<=3999)
            ans[dis[i][0]]=i;
        if(dis[i][1]<=3999)
            ans[dis[i][1]]=i;
    }
    for(int i=2;i<=3999;i++)
        ans[i]=max(ans[i],ans[i-2]);//前缀
    while(T--){
        read(m);
        if(m>3999)
            print(ans[m&1?3999:3998]);
        else
            print(ans[m]);
        putchar('\n');
    }
    fwrite(obuf,p3-obuf,1,stdout);
    return 0;
}
//tjn&&lyn--1314
```


---

## 作者：YellowBean_Elsa (赞：10)

经历了 NOIp2021 的洗礼，看啥都像 dp。。。

那这道题就差不多了

一个能力值 $x$ 通过一个 $a_i$ 可以转化到另一个能力值 $y$，而这个转化的条件只与 $x$ 和 $a_i$ 谁大谁小有关。

所以我们考虑 $dp_i$ 表示得到能力值 $i$ 至少要几次操作，这样每个转化就变成了一条从 $i$ 到 $j$ 的“边”，而剩下的问题就是最短路啦。

唯一要解决的就是 $m$ 可能很大

那么我们注意到 $ans<2a_n$，其中 $a_n$ 是 $a$ 中最大的一项，那么最短路肯定也不会很大。

用最短路走到 $x$ 后，$m$ 次操作剩下的步数“划水”就行了，也就是说不停地操作 $a_n$，这样每 $2$ 次操作后就会回到 $\,x$。但这需要到 $x$ 的步数与 $m$ 奇偶性相同，所以处理最短路时要把奇最短路和偶最短路都处理出来。

Over. 见代码

```cpp
//coder: YB-Elsa of Ahtohallan
#include<bits/stdc++.h>
#define fu(i,a,b) for(register int i = a, I = (b) + 1; i < I; ++i)
#define fd(i,a,b) for(register int i = a, I = (b) - 1; i > I; --i)
using namespace std;
typedef long long ll;
const int N=2022;

inline int read(){
    int x=0;char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
    return x;
}int n,T,a[N];
ll dp[N<<1][2];
//dp[i][p] 表示做出i的最小步数（p表示步数奇偶性） 
//dp[i+a[k]] <- dp[i]+1 (i<a[k])
//dp[i-a[k]] <- dp[i]+1 (i>=a[k]) 
queue<int> q;
ll m;bool flg;
signed main(){
//	freopen("frozen.in","r",stdin);
	n=read(),T=read();
	fu(i,1,n)a[i]=read();
	//无聊的小优化 
	sort(a+1,a+n+1);
	n=unique(a+1,a+n+1)-a-1;
	//spfa处理最短路 
	memset(dp,0x7f,sizeof(dp));
	dp[0][0]=0;
	q.push(0);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		fu(i,1,n){
			if(x<a[i]){
				flg=0;
				if(dp[x+a[i]][0]>dp[x][1]+1){
					dp[x+a[i]][0]=dp[x][1]+1;
					q.push(x+a[i]);flg=1;
				}if(dp[x+a[i]][1]>dp[x][0]+1){
					dp[x+a[i]][1]=dp[x][0]+1;
					if(!flg)q.push(x+a[i]);
				}
			}else{
				flg=0;
				if(dp[x-a[i]][0]>dp[x][1]+1){
					dp[x-a[i]][0]=dp[x][1]+1;
					q.push(x-a[i]);flg=1;
				}if(dp[x-a[i]][1]>dp[x][0]+1){
					dp[x-a[i]][1]=dp[x][0]+1;
					if(!flg)q.push(x-a[i]);
				}
			}
		}
	}
	while(T--){
		scanf("%lld",&m);
		fd(i,a[n]<<1,0)
			if(dp[i][m&1LL]<=m){
				printf("%d\n",i);
				break;
			}
	}
    return 0;
}
```


---

## 作者：starrylasky (赞：8)

~~看着大佬们都用牛逼算法，蒟蒻表示不明白~~
# Solution : dp

考虑dp,设 $f_{i,j}$ 为做了 $j$ 题的能力值为 $i$ ，很容易可以得到状态转移方程
$f_{i,j}=f_{i,j}|f_{i+a_k,j-1}|f_{i-a_k,j-1}$

显然复杂度是 $n\cdot max_M$ ，显然过不了。

通过打表我们发现在做 $5$ 题及以内~~我也不知道具体是多少反正很小就对了~~就可以完成对能达成的能力值的覆盖，所以在完成覆盖后并不需要重复做，只需要记录当前的题数，大于等于这个题数就输出最大能力值就对了，其余的在动态规划过程中记录答案， $O(1)$ 查询即可。

[实测跑的就慢那么亿点点](https://www.luogu.com.cn/record/66047038)


```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;

const int N=4e3+1;
int n,a[2001],ans[N];
bool dp[N][2001];//dp[i][j]第 j 天的能力值为i 

inline long long read() { long long X=0; bool flag=1; char ch=getchar(); while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();} while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}  if(flag) return X; return ~(X-1);}
inline void print(int X) { if(X<0) {X=~(X-1); putchar('-');} if(X>9) print(X/10); putchar(X%10+'0'); }


signed main()
{
	n=read(); int m=read(); int day=2005;
	for(re int i=1;i<=n;++i) a[i]=read();
	sort(a+1,a+1+n);
	dp[0][0]=true;
	if(n!=1)
	{
		for(re int j=1;j<=2000;++j)//第几天 
		{
			for(re int i=0;i<=a[n]*2-1;++i)//现在的能力
			{
				for(re int k=1;k<=n;++k)//第几套 
				{
					if(i+a[k]<4000) dp[i][j]=dp[i][j]|dp[i+a[k]][j-1];//是-得到的 
					if(i-a[k]<a[k]&&i-a[k]>=0) dp[i][j]=dp[i][j]|dp[i-a[k]][j-1];
					//是+得到的 
				}
			}
			int cnt=0;
			for(re int i=0;i<2*a[n];++i) if(dp[i][j]){ans[j]=i;++cnt;}
			if(cnt==a[n]*2) {day=j; break;}
		}
	}
	while(m--)
	{
		long long k=read();
		if(k>=day&&n!=1) cout<<a[n]*2-1<<endl;
		else
		{
			if(n==1)
			{
				print(k%2==1?a[1]:0); puts("");
			}
			else
			{
				print(ans[k]); puts("");	
			}
		}	
	}
	return 0;
}
/*
10
6 19 34 35 56 63 82 82 83 99
*/
```


---

## 作者：伟大的王夫子 (赞：4)

这题实际上跟 [P5663 [CSP-J2019] 加工零件](https://www.luogu.com.cn/problem/P5663)  有异曲同工之妙。

~~然而我比赛时却没有做出 P7997。~~

这两题的整体思路都是利用奇偶性 + 最短路进行的判断。

首先，根据题目所给的规则，最后的到的数在 $[0, 2 \times \max a - 1]$ 之间。所以说实际上我们要求的也就是 $0$ 到这几个数的单源最短路。

我们在看一下 $m$ 的范围，足足有 $10^{18}$，但这只不过是为了吓唬人的。因为总共可行的数最多也只有 4000 个。我们想到利用奇偶性。对于一个整数 $y$，如果存在一个 $x$ 使得在 $x$ 步内能到达 $y$，使得 $x \le m$ 并且 $x$ 与 $m$ 除以 2 的余数相同，那么显然我们可以在刚好 $m$ 步内到达 $y$。（剩下的 $m - x$ 步只需在相邻两个节点来回走动即可）

```cpp
#include <bits/stdc++.h>
using namespace std;
template <class T>
inline void Rd(T &x) {
    x = 0;
    bool f = 0;
    char ch = getchar();
    while (!isdigit(ch)) f |= ch == '-', ch = getchar();
    while (isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    if (f)
        x = -x;
}
typedef long long ll;
int n, m, Q, a[2005], maxa;
ll f[4005][2];
bool v[4005][2];
vector<int> e[4005];
int main() {
    Rd(n), Rd(Q);
    for (int i = 1; i <= n; ++i) Rd(a[i]), maxa = max(maxa, a[i]);
    for (int i = 0; i <= 2 * maxa - 1; ++i)
    	for (int j = 1; j <= n; ++j) 
    		e[i].push_back(i >= a[j] ? i - a[j] : i + a[j]);
	memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    queue<pair<int, bool> > q;
    v[0][0] = 1;
    q.push(make_pair(0, 0));
    while (q.size()) {
    	int x = q.front().first;
    	bool p = q.front().second;
    	q.pop();
    	for (int i = 0; i < e[x].size(); ++i) {
    		int y = e[x][i];
    		if (v[y][p ^ 1]) continue;
    		f[y][p ^ 1] = f[x][p] + 1;
    		v[y][p ^ 1] = 1;
    		q.push(make_pair(y, p ^ 1));
		} 
	}
	while (Q--) {
		ll m;
		Rd(m);
		for (int i = 2 * maxa - 1; i >= 0; --i)
			if (f[i][m & 1] <= m) {
				printf("%d\n", i);
				break;
			}	
	}
    return 0;
}
```

---

## 作者：C6H14 (赞：2)

## 一点废话

[题目传送门](https://www.luogu.com.cn/problem/P7997)

[My blog](https://www.luogu.com.cn/blog/128433/#)

%%%[czk](https://www.luogu.com.cn/user/121908)，边听课边打月赛

## 思路

一个明显的结论：能力值最多不会超过 $2 \cdot \max a_i-1$。

又一个明显的结论：我们连续两次选择难度最高的题做，能力值不变

那么能力值的范围只可能是 $0,1,\dots 2 \cdot \max a_i-1$，最多有 $4000$ 种不同的能力值。

假设当前能力值为 $x$，那么选择第 $i$ 道题后能力值将变成一个固定的值，于是考虑建图搞。

将能力值作为节点，对于第 $i$ 题，将 $0$ 到 $a_i-1$ 中的每个节点 $x$ 向 $x+a_i$ 连一条有向边，将 $a_i$ 到 $2 \cdot \max a_i-1$ 中的每个节点 $x$ 向 $x+a_i$ 也连一条有向边。

然后以 $0$ 为起点，跑奇偶图最短路，统计一下答案即可。

## 代码
```cpp
struct edge
{
	int v,n;
} e[8000005];
ll n,m,t,a[2005],l,h[4005],d[4005][2],maxn,ans[1000005][2];
inline void add(int u,int v)
{
	e[++l].v=v,e[l].n=h[u],h[u]=l;
}
queue<int> q,s;
int main()
{
	n=read(),t=read();
	for (int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+1+n);
	for (int i=1;i<=n;++i)//建图
	{
		for (int j=0;j<a[i];++j)
			add(j,j+a[i]);
		for (int j=a[i];j<2*a[n];++j)
			add(j,j-a[i]);
	}
	memset(d,0x3f,sizeof(d));//最短路
	d[0][0]=0;
	q.push(0),s.push(0);
	while (!q.empty())
	{
		int t=q.front(),r=s.front();
		q.pop(),s.pop();
		for (int b=h[t];b;b=e[b].n)
		{
			int v=e[b].v;
			if (d[v][r^1]<=d[t][r]+1)
				continue;
			d[v][r^1]=d[t][r]+1;
			q.push(v),s.push(r^1);
		}
	}
	for (int i=0;i<=2*a[n];++i)//统计答案
	{
		if (d[i][0]==d[4001][0])
			d[i][0]=-1;
		if (d[i][1]==d[4001][0])
			d[i][1]=-1;
	}
	for (int i=0;i<=2*a[n];++i)
	{
		maxn=max(maxn,max(d[i][0],d[i][1]));
		if (d[i][0]!=-1)
			ans[d[i][0]][d[i][0]&1]=i;
		if (d[i][1]!=-1)
			ans[d[i][1]][d[i][1]&1]=i;
	}
	for (int i=1;i<=maxn;++i)
		ans[i][0]=max(ans[i][0],ans[i-1][0]),ans[i][1]=max(ans[i][1],ans[i-1][1]);
	while (t--)
	{
		m=read();
		if (m>=maxn)
			write(ans[maxn][m&1],'\n');
		else
			write(ans[m][m&1],'\n');
	}
	return 0;
}

```


---

## 作者：expecto__patronum (赞：1)

# 思路：
容易知道到达的值范围是 $[0,2×mx)$。

考虑把每个值当作点，然后拆点。

分别表示奇数次到达 $[0,4000)$ 和偶数次到达的点 $[4000,8000)$ 建边。

然后从 $4000$ 出发，跑最短路。
# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull; 
const int N=2e3+5,M=1e4+5,inf=0x3f3f3f3f,mod=1e9+7;
const int hashmod[4] = {402653189,805306457,1610612741,998244353};
#define mst(a,b) memset(a,b,sizeof a)
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define x first
#define y second
#define pb emplace_back
#define SZ(a) (int)a.size()
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=a;i>=b;--i)
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr) 
void Print(int *a,int n){
	for(int i=1;i<n;i++)
		printf("%d ",a[i]);
	printf("%d\n",a[n]); 
}
template <typename T>		//x=max(x,y)  x=min(x,y)
void cmx(T &x,T y){
	if(x<y) x=y;
}
template <typename T>
void cmn(T &x,T y){
	if(x>y) x=y;
}
int h[M],cnt;
struct node{
	int to,nt;
}e[M*2000];
void add(int u,int v){
	e[++cnt]={v+4000,h[u]},h[u]=cnt;
	e[++cnt]={v,h[u+4000]},h[u+4000]=cnt;
}
ll f[M];
int a[N],mx;
//4000*2000*2
int main(){
	int n,t;
	scanf("%d%d",&n,&t);
	rep(i,1,n) scanf("%d",&a[i]),cmx(mx,a[i]);
	mx<<=1;
	for(int i=0;i<mx;i++)
		rep(j,1,n)
				if(i>=a[j]) add(i,i-a[j]);
				else add(i,i+a[j]);
	mst(f,0x3f);
	f[4000] = 0;
	queue<int>q;q.push(4000);
	while(!q.empty()){
		int u = q.front();q.pop();
		for(int i=h[u];i;i=e[i].nt){
			int v = e[i].to;
			if(f[v]>f[u]+1)
			{
				f[v] = f[u] + 1;
				q.push(v);
			}
		}
	}
	while(t--){
		ll x;scanf("%lld",&x);
		//printf("x=%lld\n",x);
		if(x&1){
			for(int i=3999;i>=0;--i){
				if(f[i]<=x){
					printf("%d\n",i);break;
				}
			}
		}
		else {
			for(int i=7999;i>=4000;--i){
				if(f[i]<=x){
					printf("%d\n",i-4000);break;
				}
			}			
		}
	}
	return 0;
};

```
[博客](https://blog.csdn.net/weixin_45750972/article/details/122362022)

---

## 作者：nullqtr_pwp (赞：0)

### 简化题意

你有一个长为 $n$ 的数组 $a$，你有一个整数 $x$。每次你可以选择一个数 $a_i$，若数 $x\ge a_i$，则 $x$ 会变成 $x-a_i$，否则变成 $x+a_i$。

求在选恰好 $m$ 个数的情况下最终 $x$ 值的最大值。

### Solution

多组询问，询问之间互相独立，每次询问 $x$ 初值为 $0$。
记 $\max{a_i}=mx$

对于每次查询，若 $m\ge n$，则经验值最大应该是 $2mx-1$，所以实际上 $\bm {m\le 4\times 10^3}$

一个值 $x$ 通过增或减 $a_i$ 转化成 $y$，与 $y$ 和 $a_i$ 的大小关系有关。对于每一个点和 $x$ 和每一个值 $a_i$，所有的经验值作为点。通过设定值作为边来转化。建边方式如下：

若 $x\ge a_i$，建边 $x-a_i$

否则，建边 $a_i+x$

以节点 $0$，作为起点（这个人的初始值是 $0$），对 $0$ 与所有的经验值（即 $a_i$）连边 $a_i$。

因为对于所有的 $n$ 都有 $n\rightarrow n+2$，所以要分为奇数和偶数，对此从 $0$ 开始跑奇偶图最短路即可。

---

## 作者：Little09 (赞：0)

首先假设 $a$ 中最大的是 $A$，那么你达到的值一定不会达到 $2\times A$。因为当你达到 $A$ 及以上时，你就必须要减去一个值，无法上升了。

考虑到如果你在第 $i$ 天达到了 $x$，那么你在第 $i+2$ 天也可以达到 $x$。证明就是用两次 $A$ 相互抵消。所以对于每个 $x$，你要算出第一个奇数和偶数 $i$ 满足在第 $i$ 天可以到达 $x$。

你会发现这个和 [[CSP-J2019] 加工零件](https://www.luogu.com.cn/problem/P5663) 非常相似。只要把图建出来，跑一遍奇偶最短路就行了。由于边权都是 $1$，你可以使用 BFS 做到 $O(nA)$ 的复杂度。

最后对于每个询问，在奇数和偶数里找一下 lower_bound 就好了。

```cpp
// By: Little09
// Problem: T216142 [WFOI - 01]  刷题 （problem）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T216142?contestId=58414
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf=2000000000000000000; 
int n,T;
const int N=2e3+5;
int a[N],MAX;
ll ans[N*4];
vector<int>t[N*4];
inline ll read()
{
    ll F=1,ANS=0;
	char C=getchar();
    while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
    while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
    return F*ANS;
}
void add(int x,int y)
{
	t[x].push_back(y);
}
queue<int>q;
bool used[N*4];
void bfs()
{
	for (int i=1;i<=4*MAX;i++) ans[i]=inf;
	used[0]=1,ans[0]=0;
	q.push(0);
	while (!q.empty())
	{
		int u=q.front();
		q.pop();
		for (int i=0;i<t[u].size();i++)
		{
			int v=t[u][i];
			if (used[v]) continue;
			ans[v]=ans[u]+1;
			q.push(v);
			used[v]=1;
		}
	}
}
ll w[N*2],r[N*2];
int main()
{
	n=read(),T=read(),MAX=10;
	for (int i=1;i<=n;i++) a[i]=read(),MAX=max(MAX,a[i]);
	for (int i=0;i<2*MAX;i++)
	{
		for (int j=1;j<=n;j++)
		{
			if (i<a[j]) add(i,i+a[j]+2*MAX),add(i+2*MAX,i+a[j]);
			else add(i,i-a[j]+2*MAX),add(i+2*MAX,i-a[j]);
		}
	}
	bfs();
	for (int i=MAX*2-1;i>=0;i--)
	{
		w[i]=ans[i];
		if (i!=MAX*2-1) w[i]=min(w[i+1],w[i]);
	}
	for (int i=MAX*4-1;i>=MAX*2;i--)
	{
		r[i-MAX*2]=ans[i];
		if (i!=MAX*4-1) r[i-MAX*2]=min(r[i-MAX*2+1],r[i-MAX*2]);
	}
	while (T--)
	{
		ll x=read();
		int u;
		if (x%2==0) u=upper_bound(w,w+MAX*2,x)-w-1;
		else u=upper_bound(r,r+MAX*2,x)-r-1;
		printf("%d\n",u);
	}
	return 0;
}
```


---

## 作者：ricky0916 (赞：0)

考虑建图。

我们对于每一个点 $ u $ 和数字里的元素 $a_i$，进行如下建边：

1. 若 $ u<a_i $，则建一条由 $ u $ 到 $ u+a_i $ 的有向边。

1. 若 $ u\geq a_i $，则建一条由 $ u $ 到 $ u-a_i $ 的有向边。

那么若能从节点 $ 0 $ 经过 $ m $ 条边到节点 $ u $，则可以通过做 $ m $ 题让初始能力到达 $ u $。显然大于等于 $ 2\times \max\limits_{1\le i\le n} a_i -1$ 的 $ u $ 是没用的，所以最多 $ 4000 $ 个点。

考虑节点 $ 0 $ 到节点 $ u $ 的最短路，设为 $ d $。

则对于一个大于 $ d $ 的数 $ m $，仅需满足 $m\equiv d \pmod2$ 就可以从 $0$ 到 $ u $，所以预处理 $ 0 $ 到每一个节点的奇的最短路和偶的最短路即可（BFS）。

然后可以先暴力求好 $ m=1,2,3......4000 $ 时的答案。

在询问时，如果 $ m\le 4000 $ 则输出预处理的答案，否则判断是否是奇数，若是则输出 $ m=3999 $ 的答案，不是则输出 $ m=4000 $ 的答案。

可优化至 $ \operatorname{O}(\max \ a_i+4000+T) $，我的代码是 $\operatorname{O}(4000\times \max \ a_i+T) $。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
static char buf[1000000],*pa=buf,*pd=buf;
static char buf2[1000000],*pp=buf2;
#define getchar() pa==pd&&(pd=(pa=buf)+fread(buf,1,1000000,stdin),pa==pd)?EOF:*pa++
inline void pc(char ch){
	if(pp-buf2==1000000) fwrite(buf2,1,1000000,stdout),pp=buf2;
	*pp++=ch;
}
void pcc(){
	fwrite(buf2,1,pp-buf2,stdout);
	pp=buf2;
}
inline long long read(){
	long long x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x;
}
inline void write(int x){
	static int sta[20];
	int top=0;
	if(x<0) pc('-'),x=-x;
	do{
		sta[top++]=x%10,x/=10;
	}while(x);
	while(top) pc(sta[--top]+48);
}
inline int mn(int x,int y){
	return x<y?x:y;
}
inline int mx(int x,int y){
	return x>y?x:y;
}
inline void asdf(int &x,int &y){
	x^=y^=x^=y;
}
int t,n,a[20010],mxx,step[40010][2],mxxx[10010];
bool vis[40010][2];
long long m;
vector<int>g[40010];
struct node{
	int x;
	bool fl;
};
int main(){
	n=read();
	t=read();
	for(int i=1;i<=n;i++) a[i]=read(),mxx=mx(mxx,a[i]);
	for(int i=0;i<=(mxx<<1)-1;i++){
		for(int j=1;j<=n;j++){
			g[i].push_back(i<a[j]?i+a[j]:i-a[j]);
		}
	}
	queue<node>q;
	q.push((node){0,0});
	vis[0][0]=1;
	memset(step,0x3f3f3f3f,sizeof(step));
	step[0][0]=0;
	while(!q.empty()){
		node u=q.front();
		q.pop();
		bool tmp=step[u.x][u.fl]&1;
		for(int i=0;i<g[u.x].size();i++){
			if(!vis[g[u.x][i]][tmp^1]){
				vis[g[u.x][i]][tmp^1]=1;
				step[g[u.x][i]][tmp^1]=step[u.x][u.fl]+1;
				q.push((node){g[u.x][i],tmp^1});
			}
		}
	}
	for(int i=4000;i>=0;i--){
		int fl=i&1;
		for(int j=(mxx<<1)-1;j>=0;j--){
			if(step[j][fl]<=i){
				mxxx[i]=j;
				break;
			}
		}
	}
	while(t--){
		m=read();
		if(m<=4000) write(mxxx[m]);
		else{
			if(m&1) write(mxxx[3999]);
			else write(mxxx[4000]);
		}
		pc('\n');
	}
	pcc();
	return 0;
}

```


---


# Analysis of Pathes in Functional Graph

## 题目描述

有一个 $n$ 个点 $n$ 条边的带权有向图（点编号 $0\sim n-1$），每个点有且仅有一条出边，对于每个点 $i$ 求出由 $i$ 出发走过 $k$ 条边，这 $k$ 条边权值的最小值与这 $k$ 条边权值之和。

## 样例 #1

### 输入

```
7 3
1 2 3 4 3 2 6
6 3 1 4 2 2 3
```

### 输出

```
10 1
8 1
7 1
10 2
8 2
7 1
9 3
```

## 样例 #2

### 输入

```
4 4
0 1 2 3
0 1 2 3
```

### 输出

```
0 0
4 1
8 2
12 3
```

## 样例 #3

### 输入

```
5 3
1 2 3 4 0
4 1 2 14 3
```

### 输出

```
7 1
17 1
19 2
21 3
8 1
```

# 题解

## 作者：Dilute (赞：7)

## 一道非常好的练倍增的题目

思路很简单，就是倍增处理出每个点往后$2^i$个点的路径权值和与最小值，同时要注意一下$k$要用`longlong`存，否则会挂掉

如果不会倍增的右转百度找其他博客去吧……我这里就不赘述了
```cpp
#include<bits/stdc++.h>

using namespace std;

int Son[100010][50];
long long Ans[100010][50];
int Min[100010][50];

long long Solve1(int Cur, long long k){ // 求出Cur向后k条路径的权值和
	if(k == 0)
		return 0;
	int xx = 0;
	long long x = 1; // 由于2 ^ xx 会爆int，所以应当开一个变量专门存
	while(x <= k)
		xx++, x <<= 1;
	xx--;
	x >>= 1;
	return Ans[Cur][xx] + Solve1(Son[Cur][xx], k - x);	
}

int Solve2(int Cur, long long k){ // 求出Cur向后k条路径的权值最小值
	if(k == 0)
		return 2147483647;
	int xx = 0;
	long long x = 1; // 与上面同理
	while(x <= k)
		xx++, x <<= 1;
	xx--;
	x >>= 1;
	return min(Min[Cur][xx], Solve2(Son[Cur][xx], k - x));	
}

int main(){
	int n;
	long long k;
	scanf("%d %I64d", &n, &k);
	for(int i = 0; i < n; i++)
		scanf("%d", &Son[i][0]);
	for(int i = 0; i < n; i++)
		scanf("%I64d", &Ans[i][0]), Min[i][0] = Ans[i][0];
	for(int t = 1; t <= 40; t++) // 预处理出第2^i辈儿子
		for(int i = 0; i < n; i++)
			Son[i][t] = Son[Son[i][t-1]][t-1];
	for(int t = 1; t <= 40; t++) // 预处理往后$2^i$个点的路径权值之和
		for(int i = 0; i < n; i++)
			Ans[i][t] = Ans[i][t-1] + Ans[Son[i][t-1]][t-1];
	for(int t = 1; t <= 40; t++) // 预处理往后$2^i$个点的路径权值最小值
		for(int i = 0; i < n; i++)
			Min[i][t] = min(Min[i][t-1], Min[Son[i][t-1]][t-1]);
	for(int i = 0; i < n; i++)
		printf("%I64d %d\n", Solve1(i, k), Solve2(i, k));
}
```

---

## 作者：王权贵哥 (赞：4)

## **倍增**

每个点只有一个有且只有一条出边，则路径唯一，可以依次往下搜，用倍增优化
建立在树上倍增法思想，让fat[x,k]保存x的2^k辈祖先、x到祖先所经过路径的最小值及路径和三个变量,最后统一更新。
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<stack>
using namespace std;
const int num=1e5+5;
typedef long long ll;
struct Node{
	// data表示祖先，Min表示路径最小值，N表示路径和 
	ll data,Min,N;
};
ll head[num],ver[2*num],edge[num*2],Next[2*num],tot=0;
void add(ll x,ll y,ll z){
	ver[++tot]=y;edge[tot]=z;Next[tot]=head[x];head[x]=tot;
}Node fat[num][45];ll t;
void bfs(ll h){
	queue<ll>q;q.push(h);
	while(!q.empty()){
		ll x=q.front();q.pop();
		if(fat[x][0].data!=-1)continue;
		for(ll i=head[x];i;i=Next[i]){
			ll y=ver[i];
			fat[x][0].data=y;fat[x][0].Min=fat[x][0].N=edge[i];
			q.push(y);
		}
	}
}
int main(){
	ll n,m,i,j,k;scanf("%lld%lld",&n,&m);
	ll a[num];t=(ll)(log(m)/log(2))+1;
	for(i=0;i<n;i++){
		scanf("%lld",&a[i]);
	}for(i=0;i<n;i++){
		scanf("%lld",&j);add(i,a[i],j);
	}for(i=0;i<n;i++){
		fat[i][0].data=-1;
	}for(i=0;i<n;i++){
		if(fat[i][0].data==-1){
			bfs(i);
		}
	}//更新fat[][]
    for(j=1;j<=t;j++){
		for(i=0;i<n;i++){
			fat[i][j].data=fat[fat[i][j-1].data][j-1].data;
			fat[i][j].Min=min(fat[fat[i][j-1].data][j-1].Min,fat[i][j-1].Min);
			fat[i][j].N=fat[i][j-1].N+fat[fat[i][j-1].data][j-1].N;
		}
	}for(i=0;i<n;i++){
		ll temp=m,hh=i,ans=-1,h=0;
		for(j=t;j>=0;j--){
			if(pow(2,j)<=temp){
				temp-=pow(2,j);h+=fat[hh][j].N;
				if(ans!=-1)
				ans=min(ans,fat[hh][j].Min);
				else
				ans=fat[hh][j].Min;
				hh=fat[hh][j].data;
			}
		}printf("%lld %lld\n",h,ans);
	}
}
```


---

## 作者：Galex (赞：3)

这题是属于倍增板子了吧。

用 $sn[i][j]$ 表示第 $i$ 个节点的第 $2^j$ 个儿子是谁，$ds[i][j]$ 表示第 $i$ 个节点的后 $2^j$ 条边的边权和是多少，$mn[i][j]$ 表示第 $i$ 个节点的后 $2^j$ 条边的边权的最小值是多少。

显然 $sn[i][0]=son[i]$（$son[i]$ 表示 $i$ 节点出边指向的边），$ds[i][0]=sn[i][0]=dis[i]$（$dis[i]$ 表示 $i$ 节点出边的长度）。

转移也很简单：
```cpp
void upd(int i, int j){
	sn[i][j] = sn[sn[i][j - 1]][j - 1];
	ds[i][j] = ds[i][j - 1] + ds[sn[i][j - 1]][j - 1];
	mn[i][j] = min(mn[i][j - 1], mn[sn[i][j - 1]][j - 1]);
}
```
最后就是寻找答案，用倍增去找就行：

```cpp
int getsum(int p, int k){
	int sum = 0;
	for (int i = 40; i >= 0; i--)
		if (pw[i] <= k)
			k -= pw[i], sum += ds[p][i], p = sn[p][i];
	return sum;
}

int getmin(int p, int k){
	int sum = 9e18;
	for (int i = 40; i >= 0; i--)
		if (pw[i] <= k)
			k -= pw[i], sum = min(sum, mn[p][i]), p = sn[p][i];
	return sum;
}
```
那么这题就结束了。

完整代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

int n, k;
int sn[100005][45], ds[100005][45], mn[100005][45], pw[45];

void upd(int i, int j){
	sn[i][j] = sn[sn[i][j - 1]][j - 1];
	ds[i][j] = ds[i][j - 1] + ds[sn[i][j - 1]][j - 1];
	mn[i][j] = min(mn[i][j - 1], mn[sn[i][j - 1]][j - 1]);
}

int getsum(int p, int k){
	int sum = 0;
	for (int i = 40; i >= 0; i--)
		if (pw[i] <= k)
			k -= pw[i], sum += ds[p][i], p = sn[p][i];
	return sum;
}

int getmin(int p, int k){
	int sum = 9e18;
	for (int i = 40; i >= 0; i--)
		if (pw[i] <= k)
			k -= pw[i], sum = min(sum, mn[p][i]), p = sn[p][i];
	return sum;
}

signed main() {
	n = read(), k = read();
	pw[0] = 1;
	for (int i = 1; i <= 40; i++)
		pw[i] = pw[i - 1] << 1;
	for (int i = 1; i <= n; i++)
		sn[i][0] = read() + 1;
	for (int i = 1; i <= n; i++)
		mn[i][0] = ds[i][0] = read();
	for (int j = 1; pw[j] <= k; j++)
		for (int i = 1; i <= n; i++)
			upd(i, j);
	for (int i = 1; i <= n; i++)
		printf("%lld %lld\n", getsum(i, k), getmin(i, k));
	return 0;
}
```


---

## 作者：jiazhichen844 (赞：2)

# 简要题意
有一个 $n$ 个点，$n$ 条边的有向图，边有边权，对于每个点 $i$，让你走 $k$ 条边，求经过的最大边权和边权和。
# 思路分析
## 暴力算法
对于每个点单独求，令 $f_i$ 为从 $i$ 走向的点，$w_i$ 为此边边权。

统计答案时，令 $pos=i$，每次走 $1$ 步，即依次求出答案，继续跳跃。

最后 $sum$，$minn$ 即为答案。

代码局部：
```cpp
for(int i=1;i<=n;i++)
{
    long long sum=0,minn=INT_MAX,pos=i;
    for(int j=1;j<=k;j++)
    {
    	sum+=w[pos];
        minn=min(minn,w[pos]);
        pos=f[pos];
    }
    cout<<sum<<" "<<minn<<endl;
}
```
## 优化
刚刚那个算法，时间复杂度 $O(nk)$，直接爆炸。

考虑优化，发现答案满足区间可加性，于是倍增。

令 $go_{i,j}$ 为从 $i$ 点开始走 $2^j$ 步到哪，$sum_{i,j}$ 为从 $i$ 点开始走 $2^j$ 步的边权和，$minn_{i,j}$ 为从 $i$ 点开始走 $2^j$ 步的边权最小值。

易得：$go_{i,0}=i\quad go_{i,1}=f_{pos}\quad go_{i,j}=go_{go_{i,j-1},j-1}$。

$sum_{i,0}=0\quad sum_{i,1}=w_{pos}\quad sum_{i,j}=sum{i,j-1}+sum_{go_{i,j-1},j-1}$。

$minn_{i,1}=w_{pos}\quad minn_{i,j}=min(minn_{i,j-1},minn_{go_{i,j-1},j-1})$。

此时可以二进制拆分 $k$，每次跳 $2^x$ 步，利用预处理的 $go$，$sum$，$minn$ 数组，快速跳跃，求出答案。

时间复杂度等同于二进制拆分，为 $O(n \log k)$，空间复杂度$O(n \log n)$。
## AC code
~~十年 OI 一场空，不开 long long 见祖宗~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[200005];
long long w[200005];
long long x; 
long long go[200005][45];
long long minn[200005][45];
long long sum[200005][45];
long long getsum(int pos)
{
	long long g=x,c=1;
	long long s=0;
	while(g)
	{
		if(g%2)
		{
			s+=sum[pos][c];
			pos=go[pos][c];
		}
		c++;
		g/=2;
	}
	return s;
}
long long getmin(int pos)
{
	long long g=x,c=1;
	long long mint=LONG_LONG_MAX;
	while(g)
	{
		if(g%2)
		{
			mint=min(mint,minn[pos][c]);
			pos=go[pos][c];
		}
		c++;
		g/=2;
	}
	return mint;
}
int main()
{
	int n;
	cin>>n>>x;
	for(int i=1;i<=n;i++)
		cin>>f[i],f[i]++;
	for(int i=1;i<=n;i++)
		cin>>w[i];
	for(int i=1;i<=n;i++)
		go[i][0]=i,go[i][1]=f[i];
	for(int i=2;i<=40;i++)
		for(int j=1;j<=n;j++)
			go[j][i]=go[go[j][i-1]][i-1];
	for(int i=1;i<=n;i++)
		sum[i][1]=w[i];
	for(int i=2;i<=40;i++)
		for(int j=1;j<=n;j++)
			sum[j][i]=sum[j][i-1]+sum[go[j][i-1]][i-1];
	for(int i=1;i<=n;i++)
		minn[i][1]=w[i];
	for(int i=2;i<=40;i++)
		for(int j=1;j<=n;j++)
			minn[j][i]=min(minn[j][i-1],minn[go[j][i-1]][i-1]);
	for(int i=1;i<=n;i++)
		cout<<getsum(i)<<" "<<getmin(i)<<endl;
}
```

---

## 作者：water_tomato (赞：2)

~~为什么这么裸的题是紫题。~~

## 题意
注意权值最小值指的是这 $k$ 条边中权值最小的那条边的值就好，题意叙述的很清楚了。另外注意点号是从 $0$ 开始的。
## 解析
一看数据范围, $1 \le k \le 10^{10}$ ,很显然正常跑跑不了，既然要快速跑，而本题中又没有对边的权值进行改变，再给了**每个点有且仅有一条出边**，很容易就能想到**倍增**。

但这道题的关键在于，怎样倍增才是最方便的。显然，如果先建图再倍增，非常麻烦且多次一举。对于倍增，我们只要知晓**初值**，就可能进行倍增操作了。而本题中很显然所给出的边的权值既是权值和的初值，又是权值最小值的初值，因此我们无须建图，再输入完数据后就可能直接进行倍增。

而查询时，我们只要像跑lca一样大块的优先查掉就可以了。

## 时间复杂度
倍增的预处理的时间复杂度是 $O(n\log k)$ ,每次查询操作的时间复杂度是 $O(\log k)$，会进行 $n$ 次操作，因此最终时间复杂度为 $O(n\log k)$ ，非常优良。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100005
using namespace std;
int minn[N][36],f[N][36],son[N][36],n,k;
inline void solve(int u){//查询 
	int ans=0,Min=1e18;
	int K=k;
	for(int i=35;i>=0;i--){
		if((1ll<<i)<=K){
			ans+=f[u][i];
			Min=min(Min,minn[u][i]);
			u=son[u][i];
			K-=(1ll<<i);
		}
	}
	printf("%lld %lld\n",ans,Min);
}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=0;i<n;i++) scanf("%lld",&son[i][0]);
	for(int i=0;i<n;i++){scanf("%lld",&f[i][0]);minn[i][0]=f[i][0];}
	for(int j=1;j<=35;j++){//预处理 
		for(int i=0;i<n;i++){
			son[i][j]=son[son[i][j-1]][j-1];
			f[i][j]=f[i][j-1]+f[son[i][j-1]][j-1];
			minn[i][j]=min(minn[i][j-1],minn[son[i][j-1]][j-1]);
		}
	}
	for(int i=0;i<n;i++){
		solve(i);
	}
	return 0;
}
```


---

## 作者：tZEROちゃん (赞：1)

考虑倍增。

$O(nk)$ 的暴力做法是显然的。由于每个点只有一条出边，我们沿着这条唯一的路径向前统计 $k$ 个节点即可。

显然这个复杂度无法通过本题。

考虑用一种类似 LCA 的倍增来优化这个算法。我们记录 $nxt_{i,j}$ 表示对第 $i$ 个点而言，跳 $2^j$ 次到达的点，$mn_{i,j}$ 表示后 $2^j$ 条边的最小权值，$sum_{i,j}$ 次跳到的后 $2^j$ 条边的边权和。

转移是简单的。代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1e5 + 5, M = 40;
int n, k;
int nxt[N][M], sum[N][M], mn[N][M];
int a[N], w[N];

void dfs(int pos, int &ans1, int &ans2) {
  for (int i = 35; i >= 0; --i) {
    if ((k >> i) & 1) {
      ans1 += sum[pos][i];
      ans2 = min(ans2, mn[pos][i]);
      pos = nxt[pos][i];
    }
  }
}

signed main() {
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    cin >> nxt[i][0];
  }
  for (int i = 0; i < n; ++i) {
    cin >> sum[i][0];
    mn[i][0] = sum[i][0];
  }
  for (int j = 1; j <= 33; ++j) {
    for (int i = 0; i < n; ++i) {
      nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
      sum[i][j] = sum[i][j - 1] + sum[nxt[i][j - 1]][j - 1];
      mn[i][j] = min(mn[i][j - 1], mn[nxt[i][j - 1]][j - 1]);
    }
  }
  for (int i = 0; i < n; ++i) {
    int ans1 = 0, ans2 = 1e9;
    dfs(i, ans1, ans2);
    cout << ans1 << ' ' << ans2 << '\n';
  }
}
```

---

## 作者：菲斯斯夫斯基 (赞：1)

## CF702E Analysis of Pathes in Functional Graph 题解

一眼**倍增**。看到题目中的 $1\le k\le10^{10}$ 就可以很快反应是用倍增了。

定义 $fa_{i,j}$ 为从第 $i$ 个点开始，指向的第 $2^j$ 个点的编号。数组 $sum_{i,j}$ 和 $mi_{i,j}$ 含义差不多，分别存的是**权值和**以及**权值的最小值**，对应我们要求的答案。

接下来就很好求啦，跟倍增的板子差不多。主要的细节是节点的编号是从 $0$ 开始的，以及这题需要使用 `long long`。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,k,x;
int fa[N][50],sum[N][50],mi[N][50];
void ask(int x)
{
	int m=k,ans1=0,ans2=1e18;
	//ans1存和，ans2存最小值 
	for(int i=35;i>=0;i--)
		if(m>=(1LL<<i))
		{
			ans1+=sum[x][i];
			ans2=min(ans2,mi[x][i]);
			x=fa[x][i];
			m-=1LL<<i;
			//一步步求出下一个节点、和、最小值 
		}
	cout<<ans1<<' '<<ans2<<endl;
}
signed main()
{
	memset(mi,127,sizeof(127));
	cin>>n>>k;
	for(int i=0;i<n;i++)
	{
		cin>>x;
		fa[i][0]=x;
	}
	for(int i=0;i<n;i++)
	{
		cin>>x;
		sum[i][0]=x;
		mi[i][0]=x;
	}
    //初始化j=0的情况 
	for(int j=1;j<=35;j++)
		for(int i=0;i<n;i++)
		{
			fa[i][j]=fa[fa[i][j-1]][j-1];
			sum[i][j]=sum[i][j-1]+sum[fa[i][j-1]][j-1];
			mi[i][j]=min(mi[i][j-1],mi[fa[i][j-1]][j-1]);
			//倍增转移 
		}
	for(int i=0;i<n;i++)
		ask(i);
	return 0;
}

```

---

## 作者：BFSDFS123 (赞：0)

怎么被我薄杀了，这么不牛？

观察到每一个节点只有一个子节点，且 $k$ 很大，不难想到倍增。

考虑维护 ``son[i][j]``、``sum[i][j]``、``minn[i][j]``，分别代表节点 $i$ 向下走 $2^j$ 步到达的节点，此间经过的边权和，此间经过的边权最小值。

维护平凡，询问平凡，套模板即可。

你跟我说这 2100？

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define DEP 38
#define ll long long
#define eps 1e-8
const int inf=1e18;
const int Maxn=1e5+10;
int n,k;
int sons[Maxn][40];
int sum[Maxn][40],minn[Maxn][40];
int work1(int x,int k)
{
	int ans=0;
	for(int i=DEP;i>=0;i--)
	{
		if((1ll<<i)<=k)
		{
//			cout<<"i="<<i<<","<<(1ll<<i)<<","<<k<<endl;
			ans+=sum[x][i];
//			cout<<"ans="<<ans<<endl;
			x=sons[x][i];
			k-=(1ll<<i); 
		}
	}
	return ans;
}
int work2(int x,int k)
{
	int ans=inf;
	for(int i=DEP;i>=0;i--)
	{
		if((1ll<<i)<=k)
		{
			ans=min(ans,minn[x][i]);
			x=sons[x][i];
			k-=(1ll<<i);
		}
	}
	return ans;
}
signed main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
	{
		int son;
		scanf("%lld",&son);son++;
		sons[i][0]=son;
	}
	for(int i=1;i<=n;i++)
	{
		int w;
		scanf("%lld",&w);
		minn[i][0]=w;
		sum[i][0]=w;
	}
	for(int j=1;j<=DEP;j++)
	{
		for(int i=1;i<=n;i++)
		{
			sons[i][j]=sons[sons[i][j-1]][j-1];
		}
	}
	for(int j=1;j<=DEP;j++)
	{
		for(int i=1;i<=n;i++)
		{
			sum[i][j]=sum[i][j-1]+sum[sons[i][j-1]][j-1];
			minn[i][j]=min(minn[i][j-1],minn[sons[i][j-1]][j-1]);
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		int p=i;
		printf("%lld %lld\n",work1(p,k),work2(p,k));
	}
	return 0;
}

```

---

## 作者：快斗游鹿 (赞：0)

## 思路

简单倍增。

注意到每个点只有一条出边。设 $f_{i,j}$ 表示第 $i$ 个点走 $2^j$ 步到达的点的编号，$mi_{i,j}$ 表示第 $i$ 个点走 $2^j$ 步能走到的最小值，$sum_{i,j}$ 表示第 $i$ 个点走 $2^j$ 步所走过的边权和。则有：

$f_{i,j}=f_{f_{i,j-1},j-1}$。

$mi_{i,j}=\min(mi_{i,j-1},mi_{f_{i,j-1},j-1})$。

$sum_{i,j}=sum_{i,j-1}+sum_{f_{i,j-1},j-1}$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,k,f[N][40],mi[N][40],sum[N][40],ans,minn;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
void solve(int x){
	int kk=k,minn=1e9,ans=0;
	for(int i=35;i>=0;i--){
		if((1ll<<i)<=kk){
			minn=min(minn,mi[x][i]);
			ans+=sum[x][i];
			kk-=(1ll<<i);
			x=f[x][i];
		}
	}
	printf("%lld %lld\n",ans,minn);
}
signed main(){
	n=read();k=read();
	for(int i=1;i<=n;i++){
		f[i][0]=read()+1;
	}
	for(int i=1;i<=n;i++){
		mi[i][0]=read();
		sum[i][0]=mi[i][0];
	}
	for(int j=1;j<=35;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
			mi[i][j]=min(mi[i][j-1],mi[f[i][j-1]][j-1]);
			sum[i][j]=sum[i][j-1]+sum[f[i][j-1]][j-1];
			//cout<<mi[i][j]<<" "<<sum[i][j]<<endl;
		}
	}
	for(int i=1;i<=n;i++){
		solve(i);
	}
	return 0;
}

```


---

## 作者：MiniLong (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF702E)

[原题](https://codeforces.com/problemset/problem/702/E)

## 思路

一道很水的倍增板子题。

因为题目要求维护 **权值和** 和 **权值最小值**，并且 **每个节点有且仅有 $1$ 个儿子**，所以用倍增维护即可。

$f_{i,j}$ 表示节点 $i$ 的第 $2^j$ 级儿子。

$sum_{i,j}$ 表示节点 $i$ 到第 $2^j$ 级儿子的路径权值和。

$minx_{i,j}$ 表示节点 $i$ 到第 $2^j$ 级儿子的路径权值最小值。

显然，状态转移就是普通的倍增。

$ f_{i,j} = f_{f_{i,j-1},j-1} $

$ sum_{i, j} = sum_{i, j-1} + sum_{f_{i, j-1}, j-1} $

$ minx_{i, j} = \min( minx_{i, j-1}, minx_{f_{i, j-1}, j-1} )$

总复杂度 $O(n \log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace fastio{
    template<typename T> inline void read(T &t){
        int x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -f;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t);
        read(args...);
    }
    template<typename T> void write(T t){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10);
        putchar(t % 10 + '0');
    }
    template<typename T, typename ... Args> void write(T t, Args... args){
        write(t), putchar(' '), write(args...);
    }
    template<typename T> void writeln(T t){
        write(t);
        puts("");
    }
};
using namespace fastio;
typedef pair<int, int> PII;
const int N = 1e5 + 5;
int n, k;
int son[N], w[N], f[N][40], sum[N][40], minx[N][40], ans = 2e9, ak;
bool vis[N];
PII find(int x){
    int res = 0, p = k, mn = 1e18;
    for(int i = 35; i >= 0; --i){
        if((1ll << i) > p) continue;
        res += sum[x][i], mn = min(mn, minx[x][i]), x = f[x][i];
        p -= (1ll << i);
    }
    return {res, mn};
}
signed main(){
    read(n, k);
    for(int i = 1; i <= n; ++i){
        read(son[i]);
        son[i]++, f[i][0] = son[i];
    }
    for(int i = 1; i <= n; ++i) read(w[i]), sum[i][0] = minx[i][0] = w[i];
    for(int i = 1; i <= 35; ++i){
        for(int j = 1; j <= n; ++j){
            f[j][i] = f[f[j][i-1]][i-1];
            sum[j][i] = sum[j][i-1] + sum[f[j][i-1]][i-1];
            minx[j][i] = min(minx[j][i-1], minx[f[j][i-1]][i-1]);
        }
    }
    for(int i = 1; i <= n; ++i){
        PII t = find(i);
        write(t.first, t.second), puts("");
    }
    return 0;
}
```

---

## 作者：myster1ous (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF702E)

## 题目大意

给出一个 $n$ 个点 $n$ 条边的带权有向图，且每个点的出度均为一，要你求出每个点按边的方向继续走 $k$ 步的路径的权值和和最小边权值。

## 数据范围

$1 \le n \le 10^5$，$1 \le k \le 10^{10}$。

## 题目解法

_这道题目是一个倍增的裸题。_

我们用 `f[i][j]` 表示点 $i$ 按照边的方向走 $2^j$ 步最终走到的点，`m[i][j]` 表示点 $i$ 按照边的方向走 ${2^j}$ 步的路径的最小边权值，`s[i][j]` 表示点 $i$ 按照边的方向走 $2^j$ 步的路径的权值和。

$k$ 一定能被分解为若干个二的整数幂，考虑分解。

用若干 `s[i][j]` 数组的加和就可以计算出路径权值和，同理，若干 `m[i][j]` 数组的最小值就可以计算出路径最小边权值。（由于计算时还需要一个指针跟着路径所以需要 `f` 数组。）

所以原问题现在就只需要计算出 `s` 和 `m` 和 `f` 数组了。

`f[i][j]` 可以转化为先按照边的方向走 $2^{j - 1}$ 步再走 $2^{j - 1}$ 步（因为 $2^{j - 1} + 2^{j - 1} = 2^{j}$），所以 `f[i][j] = f[f[i][j - 1]][j - 1]`。

`s[i][j]` 可以转化为把路径分为两个长度为 $2^{j - 1}$ 的路径，分别求出权值和后再加即可，所以 `s[i][j] = s[f[i][j - 1]][j - 1] + s[i][j - 1]`。`m[i][j]` 同理，只需把加号改为 `min` 即可。

初始化 `f[i][0]` 等于从 $i$ 开始走 $2^0 = 1$ 步走到的点即为出边所到达的点；初始化 `s[i][0]` 等于从 $i$ 开始走 $1$ 步走过的路径的权值和即为出边的权值，`m[i][0]` 一样。

## 题目坑点

1. $k \le 10^{10}$ 所以需要开 $64$ 位整数。
2. 题目中点编号从 $0$ 开始，为了符合习惯所以直接将输入 $+1$。

## 完整代码

```cpp
#include <bits/stdc++.h>
#define maxn 131072
#define maxm 50
#define int int64_t // 坑点 1
using namespace std;
int n, k;
int w[maxn], e[maxn], f[maxn][maxm], m[maxn][maxm], s[maxn][maxm];
void init(int, int);
int SumEdge(int, int, int);
int MinEdge(int, int, int);
signed main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> e[i], e[i] += 1; // 坑点 2
    for (int i = 1; i <= n; i++)
        cin >> w[i], f[i][0] = e[i], m[i][0] = s[i][0] = w[i];
    for (int i = 1; i <= 40; i++)
        for (int j = 1; j <= n; j++)
            init(i, j); // 进行初始化
    for (int i = 1; i <= n; i++)
        cout << SumEdge(i, k, 40) << " " << MinEdge(i, k, 40) << "\n"; // 输出结果
    return 0;
}
void init(int x, int idx) {
    if (f[idx][x] != 0) return; // 若已经初始化则直接 return
    f[idx][x] = f[f[idx][x - 1]][x - 1], m[idx][x] = min(m[idx][x - 1], m[f[idx][x - 1]][x - 1]), s[idx][x] = s[idx][x - 1] + s[f[idx][x - 1]][x - 1]; // 状态转移
    init(x, e[idx]); // 初始化下一个点
}
int SumEdge(int x, int left_k, int last_power) {
    for (int i = last_power; i >= 0; i--)
        if (left_k >= (1LL << i)) // 由于是 long long 类型所以需要 1LL << i
            return SumEdge(f[x][i], left_k - (1LL << i), i) + s[x][i]; // 继续计算规模更小的问题
    return 0;
}
int MinEdge(int x, int left_k, int last_power) { // 和 SumEdge 函数差不多。
    for (int i = last_power; i >= 0; i--)
        if (left_k >= (1LL << i))
            return min(MinEdge(f[x][i], left_k - (1LL << i), i), m[x][i]);
    return 0x3f3f3f3f3f3f3f3fLL; // 由于是 long long 类型所以是 8 个 3f 还有 LL 后缀。
}
```

---

## 作者：Nephren_Sakura (赞：0)

前言：这题真的有紫题难度吗（（

题目传送门：[link](https://www.luogu.com.cn/problem/CF702E)

很明显有一个暴力的做法：因为每个点只有一条出边，对于每个点直接暴力跳 $k$ 次，一边跳一边求最小值与权值和，时间复杂度 $O(N \times K)$。

同上，因为只有一条出边，那么可以预处理出 $dp_{i,j}$ 表示从第 $i$ 个点开始跳 $2^j$ 条边的权值和与最小值，在跳的时候直接二进制拆分求解即可。时间复杂度 $O(N \times \log K)$。

注意：

1.十年 OI 一场空，不开 long long 见祖宗。

2.点的编号从 $0$ 开始

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n=read(),k=read(),mini[100005][40],dp[100005][40],sum[100005][40];
int pw(int x){
    int k=1;
    for(int i=1; i<=x; i++)
        k*=2;
    return k;
}
signed main(){
    for(int i=1; i<=n; i++)
        dp[i][0]=read()+1;//我的点编号从 0 开始
    for(int i=1; i<=n; i++)
        mini[i][0]=sum[i][0]=read();
    for(int j=1; j<=38; j++)
        for(int i=1; i<=n; i++){
            dp[i][j]=dp[dp[i][j-1]][j-1];
            sum[i][j]=sum[dp[i][j-1]][j-1]+sum[i][j-1];
            mini[i][j]=min(mini[i][j-1],mini[dp[i][j-1]][j-1]);
        }//倍增预处理
    for(int i=1; i<=n; i++){
        int ls=k,m=1e18,s=0,l=i;
        for(int j=38; j>=0; j--)//从高到低枚举每一位
            if(ls>=pw(j)){
                ls-=pw(j);
                s+=sum[l][j];
                m=min(m,mini[l][j]);
                l=dp[l][j];
            }
        cout<<s<<' '<<m<<endl;
    }
}
```

---

## 作者：万弘 (赞：0)

图是一个基环内向树(森林),按照套路,先处理环,再处理树边.

但其实这题很简单,直接倍增即可.  
$fa(i,j)$表示$u$走$2^k$步后到达的位置,$fsum(i,j)$表示路径上权值和,$fmx(i,j)$表示路径上最小值.

$fa(i,j)=fa(i-1,fa(i-1,j))$ ,另外两个值一起维护即可.  
查询的时候从大到小枚举$i$,若$k$的第$i$位是1就往上跳,维护答案就好.  
时空复杂度$\mathcal O(n\log n)$
```cpp
/**********/
#define MAXN 100011
ll fa[51][MAXN],fsum[51][MAXN],fmx[51][MAXN];
int main()
{
    ll n=read(),k=read();
    for(ll i=1;i<=n;++i)fa[0][i]=read();
    for(ll i=1;i<=n;++i)fsum[0][i]=fmx[0][i]=read();
    for(ll i=1;i<=60;++i)
        for(ll j=1;j<=n;++j)
        {
            ll nxt=fa[i-1][j];
            fa[i][j]=fa[i-1][nxt];
            fsum[i][j]=fsum[i-1][j]+fsum[i-1][nxt];
            fmx[i][j]=min(fmx[i-1][j],fmx[i-1][nxt]);
        }
    for(ll u=1;u<=n;++u)
    {
        ll s=0,mx=INF,pos=u,x=k;
        for(ll i=60;i>=0;--i)
            if((x>>i)&1)s+=fsum[i][pos],umin(mx,fmx[i][pos]),pos=fa[i][pos];
        printf("%lld %lld\n",s,mx);
    }
    return 0;
}
```

---


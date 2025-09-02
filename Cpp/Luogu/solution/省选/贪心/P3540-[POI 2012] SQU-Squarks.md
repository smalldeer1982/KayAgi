# [POI 2012] SQU-Squarks

## 题目描述

**译自 POI 2012 Stage 3. Day 0「[Squarks](https://szkopul.edu.pl/problemset/problem/lo_jOsVfQ4ajCSHxFGZS27W-/site/?key=statement)」**

给定 $n$ 个不同的正整数两两的和，求这 $n$ 个正整数的所有可能。

## 说明/提示

对于 $32\%$ 的数据保证 $n \le 20$ 且任何两个正整数的和不超过 $2000$.

对于所有数据保证 $n \le 300$ 且任何两个正整数的和不超过 $10^8$.

翻译与 checker 来自于 [LibreOJ](https://loj.ac/p/2698)。

## 样例 #1

### 输入

```
4
3 5 4 7 6 5```

### 输出

```
1
1 2 3 4```

# 题解

## 作者：TIMEONLY (赞：10)

## 题意(~~题面上的有毒~~)
给出一个$n$，和$n*(n-1)/2$个数,求用$n$个互不相同的正整数两两相加正好等于这$n*(n-1)/2$个数,要求输出方案数和所有方案。
## 题解

### 定义

假设$m=n*(n-1)/2$,这$m$个数中第$i$个数的为$v_i$,n个数中第$i$个数为$x_i$,并且$x_i$是单调递增的。

先给$v$排个序。

------------
### 已知$x_1$求所有的$x$

**先假设我们已经知道$x_1$。**

可以轻易看出

$v_1=x_1+x_2$

$v_2=x_1+x_3$

因为$v_1$是$v$中的最小值,而$x_1+x_2$是$x$中数两两组合的最小值,要使得$x$两两组合得出$v$,$v_1$必须等于$x_1+x_2$。

$v_2$为$v$中的次小值,推导类比上面。

那么这样的话,就可以用解方程的形式解出$n=3$的情况了。

那么$n>3$的情况呢？

继续推导

$v_3=x_1+x_4$

$v_4=x_1+x_5$


如果上面的式子成立,我们就可以用这样的方式在知道$x1$的前提下不断的用$x[i+1]=v_i-x_1$的方式得出每个$x$的值,继而得到答案。


但是很明显,上面我们推导出来的性质并不适用于当$i>2$的情况,因为我们不能确保$x_1+x_4$是x两两组合出来后的第$4$小值,可能会出现$x_2+x_3$<$x_1+x_4$的情况。

那么想想用什么方法让上面的性质成立

因为只有$x_j+x_k$  $(j<k<i)$有可能小于$x_1+x_i$的值,那么我们考虑把所有的$x_j+x_k$  $(j<k<i)$剔除掉,即每当我们求出一个$x_i$,我们就将$x_j+x_i$的值从$v$中删除掉,这样就可以保证我们推导的式子成立了。


------------
### 如何求$x_1$

我们已知

$v_1=x_1+x_2$

$v_2=x_1+x_3$

如果我们能够知道$x_2+x_3$的值那么就可以列方程组解出$x1,x2,x3$的值了

因为$x_2+x_3$的值只可能大于$x_1+x_j(j<=n)$的值，这样的值有$n$个,$n=300$,不大，可以考虑枚举$x_2+x_3=vi$的值,枚举到$n$结束,每枚举一个值就解一次方程,然后求得$x_1$的值,再用$x_1$的值求得所有$x$,如果当前值成立,计入答案，问题就解决了!!!


------------

## 代码
记得考虑$x_1$的值不符合条件的情况

时间复杂度不高，用的map映射
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=5e4+10;
const int M=301;

int n,m,ans;
int x[M][M];
int v[N],tot[N],cost[N];

map<int,int>mp;//直接开数组空间开不下,map映射值为v的数的数量 

void init_v()//预先处理好v 
{
	scanf("%d",&n);
	m=n*(n-1)/2;
	for(int i=1;i<=m;i++)
	scanf("%d",&v[i]);
	sort(v+1,v+m+1);//排序 
	for(int i=1;i<=m;i++)//映射v[i]的值的位置,便于以后统计剩余数量 
	{
		if(!mp[v[i]]) mp[v[i]]=i;//v[i]没有出现过，给予新位置(也可以开个cnt,然后mp[v[i]]=++cnt,我比较懒)
		tot[mp[v[i]]]++;
	}
}

bool check(int a,int b,int c)//判断是否需要继续计算 
{
	if(a<=0||b<=0||c<=0) return 0;
	if(a>=b||a>=c||b>=c) return 0;
	if(x[ans][1]==a&&x[ans][2]==b&&x[ans][3]==c) return 0;//防止重复的数导致重复同样的答案,ans还没加，这是上一次算出的答案 
	ans++;
	x[ans][1]=a;x[ans][2]=b;x[ans][3]=c;//符合条件,更新x[1],x[2],x[3]
	return 1;
}

bool getx()//判断x1,x2,x3是否符合条件,并且求出剩下的x 
{
	bool flag=0;
	memset(cost,0,sizeof(cost));
	//去掉x1,x2,x3组成的数
	cost[mp[x[ans][1]+x[ans][2]]]++;
	cost[mp[x[ans][1]+x[ans][3]]]++;
	cost[mp[x[ans][2]+x[ans][3]]]++;
	
	int now=3;
	
	for(int i=4;i<=n&&!flag;i++)//从4开始,小于4的已经处理好了
	{
		while(tot[mp[v[now]]]-cost[mp[v[now]]]==0) now++;//找到还没被使用的最小的数
		x[ans][i]=v[now]-x[ans][1];
		for(int j=1;j<i;j++)//去掉x[1]~~x[i-1]与x[i]组成的数 
		{
			int pos=mp[x[ans][i]+x[ans][j]];
			cost[pos]++;
			if(cost[pos]>tot[pos]) flag=1;//不符合条件 
		}
	}
	return flag;
}

void solve()
{
	int t1=v[1];//x1+x2;
	int t2=v[2];//x1+x3;
	for(int i=3,a,b,c;i<=n;i++)//i从3枚举,不会遍历到t1和t2 
	{
		b=(v[i]-t2+t1)/2;//小学的解方程
		c=v[i]-b;a=t1-b;
		if(check(a,b,c)) ans-=getx();
	}
	//输出答案 
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++)
	{
		for(int j=1;j<=n;j++)
		printf("%d ",x[i][j]);
		puts("");
	}
}

int main()
{
	init_v();
	solve();
	return 0;
}
```
这题不看题解的话还是有点难度的


---

## 作者：Alex_Wei (赞：8)

> *[P3540 [POI2012]SQU-Squarks](https://www.luogu.com.cn/problem/P3540)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

将给出的 $s_i$ 和要求的 $x_i$ 都从大到小排序，$s_1=x_1+x_2$，$s_2=x_1+x_3$，这一点显然。

先考虑已知一些数时，如何推出剩下来的数：假设 $x_1\sim x_r$ 已知，它们两两相加可以形成一些和 $t_j$，用**可重集** $s$ 减去**可重集** $t$，我们能得到一个最大数 $s_p$，它只能是 $x_1+x_{r+1}$ 的和，否则与 $s_p$ 的最大性违背。

因此，我们断言**如果确定 $x_1$**，那么可以在 $\mathcal{O}(n^2\log n)$ 的时间内得到整个 $x_i$：找到**可重集** $s\backslash t$（$t$ 的定义如上）中最大的数 $s_p$，反推出 $x_{r+1}$，用 $x_{r+1}$ 与 $x_1\sim x_r$ 的和更新 $t$，再找到下一个最大的 $s_{p'}\in s\backslash t'$ 反推出 $x_{r+2}$，以此类推。根据 $s_p$ 的单调性可以用指针维护 $p$。$\log$ 由用 $x_{r+1}+x_i$ 通过 `map` 打标记产生（代码用了 `priority_queue`）。特别的，若求出的 $x_{r+1}\geq x_r$ 或 $x_{r+1}\leq 0$ 或 $t\nsubseteq S$ 则**钦定的 $x_1$ 无解**。

接下来考虑如何求 $x_1$：注意到 $x_2+x_3$ 仅有可能小于 $x_1+x_i\ (2\leq i\leq n)$，因此 $x_2+x_3$ 在从大到小排过序后的 $s$ 中下标不会超过 $n$。考虑直接枚举这个下标从而解出 $x_1,x_2$ 和 $x_3$。

综上，时间复杂度三方对数。由于大部分下标很快无解，因此常数非常小。

```cpp
const int N = 300 + 5;
int n, m, a[N * N >> 1];
uint mp[N * N * 35];
void s(int x) {mp[x >> 5] |= 1u << (x & 31);}
bool query(int x) {return mp[x >> 5] >> (x & 31) & 1;}
vector <vint> ans;

int main(){
	cin >> n, m = n * (n - 1) >> 1;
	for(int i = 1; i <= m; i++) a[i] = read(), s(a[i]);
	sort(a + 1, a + m + 1), reverse(a + 1, a + m + 1);
	for(int i = 3; i <= n; i++) if(i == 3 || a[i] != a[i - 1]) {
		static int x[N], sum; sum = a[1] + a[2] + a[i];
		if(sum & 1) continue; x[1] = (sum >> 1) - a[i];
		if(x[1] < n) continue;
		priority_queue <int> q; bool ok = 1;
		for(int j = 2, p = 1; j <= n && ok; j++) {
			while(!q.empty() && q.top() == a[p]) q.pop(), p++;
			x[j] = a[p] - x[1];
			if(x[j] >= x[j - 1] || x[j] < 0) ok = 0;
			for(int k = 1; k < j && ok; k++) ok &= query(x[k] + x[j]), q.push(x[k] + x[j]); 
		} if(ok) {vint p; for(int j = n; j; j--) p.pb(x[j]); ans.pb(p);}
	}
	cout << ans.size() << endl, rev(ans);
	for(vint it : ans) {for(int p : it) cout << p << " "; cout << endl;}
	return flush(), 0;
}
```

---

## 作者：JMercury (赞：4)

因为前几天全是POI的题，所以那天随机到一个，今天才做了~~（还是开O2过的）~~

------------

给$n$个互不相同的数两两之和，求这$n$个数。

首先我想到了我小学做的，**已知三个数两两之和，求这三个数**，这个很好做。那么延伸到这一题，应该怎么做呢？

记原数组为$a[\ ]$，$a[\ ]$内两两之和数组为$sum[\ ]$。先给$sum[\ ]$从小到大排序，并令$a[\ ]$也是从小到大的，那么

$$a[1]+a[2]=sum[1]$$

$$a[1]+a[3]=sum[2]$$

如果能知道$a[2]+a[3]$的值（我们记这个值为$sum[p]$），有两个好处。

1.此时可以计算出$a[1],a[2],a[3]$的值；

2.此时$a[1]+a[4]$一定**是$sum[\ ]$内除了$sum[1],sum[2],sum[p]$内的最小值**，从而可以计算出$a[4]$，进而可以将$a[2]+a[4],a[3]+a[4]$都枚举出来，这样就又可以出$a[5]$，以此类推。

综上，枚举$p$即可

这里我用了multiset。既支持取出最小的元素，还可以添加重复的元素，还支持删除（额，但是可能就是因为这个所以TLE了）

然后这里还有几个剪枝（额，像这样暴力枚举，也可以认为是搜索了吧x）

1.如果$a[1],a[2],a[3]$求不出（不是整数，不是正数），返回

2.如果找不到对应的元素，返回

3.如果新求出的$a[i]$不比$a[i-1]$大，返回

附上代码（不开O2只能90分但我实在没有办法了，求巨巨指导x）

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
const int maxn=310;
using namespace std;

int n,tot;
int a[maxn],sum[maxn*maxn];
int cnt,ans[maxn][maxn];
multiset<int> S;

void solve(int p)
{
    S.clear();
    memset(a,0,sizeof(a));
    for(int i=1;i<=tot;i++) S.insert(sum[i]);
    int s=sum[1]+sum[2]+sum[p];
    if(s%2==1) return;
    a[1]=s/2-sum[p];a[2]=s/2-sum[2];a[3]=s/2-sum[1];
    if(a[1]<0 || a[2]<0 || a[3]<0) return; ///剪枝1
    S.erase(S.find(sum[1]));S.erase(S.find(sum[2]));S.erase(S.find(sum[p]));
    for(int i=4;i<=n;i++)
    {
        a[i]=*S.begin()-a[1];
        if(a[i-1]>=a[i]) return; ///剪枝3
        for(int j=1;j<i;j++)
            if(S.count(a[j]+a[i]))
                S.erase(S.find(a[j]+a[i]));
            else return; ///剪枝2
    }
    cnt++;
    for(int i=1;i<=n;i++)
        ans[cnt][i]=a[i];
}

int main()
{
    scanf("%d",&n);tot=n*(n-1)/2;
    for(int i=1;i<=tot;i++) scanf("%d",&sum[i]);
    sort(sum+1,sum+tot+1);
    for(int i=3;i<=n;i++) if(i==3 || sum[i]!=sum[i-1]) solve(i); ///不能重复枚举一样的sum[p]值（这不叫剪枝，因为这会导致答案错误！！）
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;i++)
    {
        for(int j=1;j<=n;j++)
            printf("%d ",ans[i][j]);
        printf("\n");
    }
    return 0;
}
```


---

## 作者：Tmbcan (赞：3)

## [P3540 [POI2012] SQU-Squarks](https://www.luogu.com.cn/problem/P3540)

### 题目描述
有 $N$ 个数，给出一个序列 $X_N$ 表示每两个数的和。求排序去重后这 $N$ 个数所有可能的情况。

### 思路
我们设原数从小到大排序后为序列 $a_N$。  
首先想到最暴力的方法：枚举全排列，期望得分 20 分。  

思考，如果我们可以通过确定某些 $a$，就能求出整个 $a_N$，那么就可以减少全排列的枚举次数。
  
我们先对 $X_N$ 从小到大排序，那么有 $X_1 = a_1+a_2$，$X_2 = a_1+a_3$。此时如果我们枚举 $X_i = a_2+a_3$，就可以分别求出 $a_1$、$a_2$、$a_3$。  
当我们能够确定 $a_1$、$a_2$、$a_3$ 后，考虑如何求出 $a_4\sim a_N$。    

在 $X_N$ 中，如果去掉 $X_1$、$X_2$ 和 $X_i=a_2+a_3$，那么剩下的 $X$ 中的最小值就是 $a_1+a_4$ 的值，从而我们可以求出 $a_4$。推广一下我们就可以求出整个序列 $a_N$。

因为 $X_N$ 可能重复且需要排序，所以我们用 `multiset` 存储 $X_N$（或者写平衡树），当每次求出一个 $a_j$ 时，判断其对于 $X_N$ 是否合法即可。

注意枚举 $a_2+a_3$ 的值的时候，有重复的要判掉，不然会多算重复的情况。~~（因为这个一直没过第一个点）~~。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<climits>
#include<cstdlib>
#include<vector>
#include<set>
using namespace std;
typedef long long ll;
template <typename T>
inline void read(T&x){//快读
	int w=0;x=0;
	char ch = getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') w=1;
		ch = getchar();
	}
	while(ch>='0'&&ch<='9'){
		x = (x<<1)+(x<<3)+(ch^48);
		ch = getchar();
	}
	if(w) x=-x;
}
template <typename T,typename...Args>
inline void read(T&t,Args&...args){
	read(t);read(args...);
}
const int N = 300;
int n,m,cnt;
int X[N*N];
vector < vector <int> > ans;
vector <int> a;
multiset <int> s;	
int main(){
	// freopen("in.in","r",stdin);
	// freopen("out.out","w",stdout);
	read(n);m = n*(n-1)/2;
	for(int i=1;i<=m;++i) read(X[i]);
	sort(X+1,X+1+m);
	a.resize(n+1);
	for(int k=3;k<=n;++k){
		s.clear();
		if(X[k]==X[k-1]) continue;//判掉重复的情况
		a[1] = (X[1]+X[2]-X[k]) >> 1;
		a[2] = X[1]-a[1];
		a[3] = X[2]-a[1];
		if(a[1]<=0 || a[2]<=0 || a[3]<=0) continue;//都要大于零
		for(int i=3;i<=m;++i) if(i!=k) s.insert(X[i]);//不算X[k]
		int f = 0;
		for(int i=4;i<=n && !f;++i){
			a[i] = (*s.begin())-a[1];
			if(a[i]<=0) f = 1;
			for(int j=1;j<=i-1 && !f;++j){//判断a[j]是否重复
				if(s.find(a[i]+a[j])==s.end()) f=1;
				else s.erase(s.find(a[i]+a[j])); 
			}
		}
		if(f) continue;
		ans.push_back(a);//存答案
	}
	printf("%d\n",ans.size());
	for(int i=0;i<ans.size();++i){
		for(int j=1;j<=n;++j){
			printf("%d ",ans[i][j]);
		}
		putchar('\n');
	}
	// fclose(stdin);
	// fclose(stdout);
	return 0;
}

```

---

## 作者：CQ_Bab (赞：1)

# 前言
这道题有 [双倍经验](https://www.luogu.com.cn/problem/P1286)。
# 思路
首先我们可以发现对于最小的两个 $a_1$ 和 $a_2$ 一定是 $x_1+x_2$ 与 $x_1+x_3$ 注意这里的 $x$ 已经从小到大排序了，那么我们可以发现如果知道了 $x_2+x_3$ 等于 $a$ 中的谁就可以求出 $a_1,a_2,a_3$ 了。那么我们有通过观察发现每次可以将已经求出的数任意组合然后将他们的和从 $a$ 中删去，然后所剩的 $a$ 中最小的一定是 $x_1+x_{now}$ 这个 $now$ 表示现在确定到了 $now-1$，然后再用 $x_{now}$ 与前面的组合然后从 $a$ 中删去即可。

当不能在 $a$ 中找到 $x_{now}+x_i$ 时则说明 $x_2+x_3$ 不能为现在这个数，这个可以用一个 multiset 来维护，时间复杂度 $O(n^3\times \log(m))$，有人可能会问为什么是 $n^3$ 而不是 $n^2\times m$ 因为我们发现比 $x_2+x_3$ 小的最多有 $n-1$ 个，毕竟只有 $x_1+x_i$ 可能会比 $x_2+x_3$ 小。

注意：因为这道题要求 $x$ 都是正整数所以需要判断每一个求出来的数是否都 $>0$ 即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define il inline
#define PII pair<int,int>
#define rep(i,x,y) for(register int i=x;i<=y;++i)
#define rep1(i,x,y) for(register int i=x;i>=y;--i) 
#define x first
#define y second

il int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
int n;
const int N=3e2+10;
multiset<int>s;
int a[44900];
int res;
int arr[N];
int ans[44900][N];
unordered_map<int,int>mp;
il void solve(){
	n=read();
	rep(i,1,n*(n-1)/2) a[i]=read();
	int m=n*(n-1)/2;
	sort(a+1,a+1+m);
	rep(i,3,n) {
		int k=a[i];
		if(mp.count(k)) continue;
		mp[k]=1;
		arr[1]=(a[1]+a[2]-k)/2;
		s.clear();
		if(arr[1]<=0) break;
		rep(j,3,m) s.insert(a[j]);
		s.erase(s.find(k));
		arr[2]=a[1]-arr[1];
		arr[3]=a[2]-arr[1];
		if(arr[2]<=0||arr[3]<=0) continue;
		int f=0;
		rep(k,4,n) {
			arr[k]=(*s.begin())-arr[1];
			if(arr[k]<=0) {
				f=1;
				break;
			}
			rep(l,1,k-1) {
				if(s.find(arr[l]+arr[k])==s.end()) {
					f=1;
					break;
				}
				s.erase(s.find(arr[l]+arr[k]));
			}
			if(f) break;
		}
		if(f) continue;
		res++;
		int idx=0;
		rep(j,1,n) ans[res][++idx]=arr[j];
	}
	printf("%d\n",res);
	rep(i,1,res) {
		rep(j,1,n) printf("%d ",ans[i][j]);
		puts("");
	}
	return ;
}
signed main(){
	solve();
	return 0;
}
```

---

## 作者：Richard_Whr (赞：1)

如果我们知道这 $\binom{n}{2}$ 个对的相对大小关系，我们就可以轻松解出所有数。

考虑对所有对建图，有绝对大小关系的从小到大连边，注意只连限制最紧的边，这样可以化简图结构。

具体就是在不出界且 $i<j$ 的情况下连边：$(\{i,j\},\{i+1,j\})$，$(\{i,j\},\{i,j+1\})$。

容易得出这个相对大小关系排列一定是一个合法拓扑序。

考虑拓扑序产生多解的原因是我们同时有两个以上当前入度为 $0$ 的点在队列中，我们需要钦定这些点的大小关系。

画一张 $n=5$ 或 $6$ 的图模拟一下，你就会发现：

第一个肯定是 $(1,2)$，第二个肯定是 $(1,3)$，然后第一次产生同时两个入队的时候是 $(1,4)$ 和 $(2,3)$。

此时分类讨论：

如果 $(2,3)$ 应该是第三个，那么此时可以解出 $x_1,x_2,x_3$ 的值。然后第四个一定是 $(1,4)$ 又可以解出来 $x_4$……。

在这之后，虽然队列中仍可能存在多个点等待扩展，但是只有一个二元组中有未知数，其余都是已知数，他们的排名是确定的。

因此可以直接把他们的值和排序后的给定数组做双指针踢掉相同的值，第一个不同的位置就是含未知二元组的排名。

然后我们就能确定这个未知数。

以此类推我们可以确定所有未知数。

如果 $(1,4)$ 是第三个，我们什么也得不到，而且还需要继续比较 $(1,5),(2,3)$，如果仍是 $(1,5)$ 小，需要继续比较 $(1,6),(2,3)$……

但是可以发现的是一旦确定了 $(2,3)$ 的值，按照刚刚说的做法可以直接推出剩下的所有值。

因此我们得出最终结论：只要确定了 $(2,3)$ 的排名，即可确定剩下的所有值。

因此直接枚举 $(2,3)$ 的排名即可，模拟拓扑排序后得出数列再检验就行了。

注意去重。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;
typedef pair<int,PII> PIII;
const int N=3e2+10,M=1e3+10;
int a[N];
int n,m;
int s[N*N];
vector<int> ans[N];
int tot;
set<vector<int>> Set;
bool st[N][N];

priority_queue<PIII,vector<PIII>,greater<PIII>> q;
void upd(int i,int j,int k)
{
	if(j+1<k && !st[i][j+1]) q.push({a[i]+a[j+1],{i,j+1}}),st[i][j+1]=true;
	if(i+1<j && !st[i+1][j]) q.push({a[i+1]+a[j],{i+1,j}}),st[i+1][j]=true;
}

bool check(int k)
{
	memset(a,0,sizeof a),memset(st,0,sizeof st);
	a[1]=s[1]+s[2]-s[k];a[1]/=2;
	a[2]=s[1]-a[1],a[3]=s[2]-a[1];
	for(int j=3;j<k;j++) a[j+1]=s[j]-a[1];
	int cur=k+1,now=k+1;//下一个的和，待确定的未知数
	
	upd(2,3,now);
	while(now<=n)
	{
		while(q.size() && q.top().first==s[cur])
		{
			auto tp=q.top();
			int i=tp.second.first,j=tp.second.second;
			q.pop();
			upd(i,j,now);
			cur++;
		}
		a[now]=s[cur]-a[1];
		upd(1,now,now+1);
		now++,cur++;
	}
	while(q.size()) q.pop();
	for(int i=1;i<=n;i++) 
	{
		if(a[i]<=0) return false;
		if(i>1 && a[i]<a[i-1]) return false;
	}
	vector<int> S;
	for(int i=1;i<=n;i++) 
	{
		for(int j=i+1;j<=n;j++)
		{
			S.push_back(a[i]+a[j]);
		}
	}
	sort(S.begin(),S.end());
	int i=1;
	for(auto v:S) 
	{
		if(s[i]!=v) return false;
		i++;
	}
	return true;
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n;
	m=n*(n-1)/2;
	for(int i=1;i<=m;i++) cin>>s[i];
	
	sort(s+1,s+1+m);
	
	for(int i=3;i<=n;i++) 
	{
		if(i>3 && s[i]==s[i-1]) continue;
		if(check(i))
		{
			tot++;
			for(int j=1;j<=n;j++) ans[tot].push_back(a[j]);
		}
	}
	
	cout<<tot<<"\n";
	for(int i=1;i<=tot;i++)
	{
		for(auto v:ans[i]) cout<<v<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Cure_Wing (赞：1)

[P3540 [POI2012] SQU-Squarks](https://www.luogu.com.cn/problem/P3540)

### 解法

首先我们我们对读入的若干个和进行从小到大排序，得到有序数列 $a_{1\sim\frac{n\times(n-1)}{2}}$。

在定义答案序列为 $b_{1\sim n}$，并且 $b_i$ 从小到大排序。

那么如果我们知道了 $b_1$，由于此时 $a$ 中最小值一定是 $b_1+b_2=a_1$，那么 $b_2$ 我们就知道了。

此时我们把 $b_1+b_2$ 从原序列中去除，那么剩下的最小值一定是 $b_1+b_3$，于是我们就知道了 $b_3$。

接下来我们要求 $b_4$，那么我们会想知道 $b_1+b_4$，而可能比 $b_1+b_4$ 小的有 $b_2+b_3,b_1+b_3$，把它们删掉后 $a$ 中的最小值就一定是 $b_1+b_4$，$b_4$ 也知道了。

以此类推，$b$ 数组就求解出来了，而且单调不降。

但是我们不知道 $b_1$。

回到最初的条件，我们一定知道的是 $b_1+b_2=a_1$，因为它最小；$b_1+b_3=a_2$，因为它次小。但是这个方程组有三个未知数，只有两个方程，不能解。于是想到去找 $b_2+b_3$ 的值，这样就可以解出这三个数了。而 $b_2+b_3$ 一定存在于 $a$ 中，可以暴力枚举寻找。

但是这样总复杂度 $O(n^2\times n^2)=O(n^4)$，显然超时。

仔细想想，$b_2+b_3$ 在 $a$ 数组的位置一定不会特别靠后，因为比它小的只可能有 $b_1+b_i$，所以 $b_2+b_3$ 的位置一定在前 $n$ 位之内。也就是说我们枚举的时候只需要枚举前 $3\sim n$ 个位置就可以了，复杂度降为 $O(n^3)$。

但是这些只是可能的情况，在计算过程中和序列求解后序列不一定会合法或存在甚至重复，要注意特判和检验。

实现的时候这里用了 `multiset` 维护 $a$ 数组，实际复杂度 $O(n^3\log^2n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<map>
using std::cin;using std::cout;
constexpr int N=305;
int n,a[N*N],m,ans[N][N],cnt,s[N*N],c;
std::map<int,int>p;
signed main(){
	freopen("problem.in","r",stdin);
	freopen("problem.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n;m=n*(n-1)/2;
    for(int i=1;i<=m;++i) cin>>a[i];
    std::sort(a+1,a+m+1);
    for(int o=3;o<=n;++o){//枚举 b2+b3 的可能值
        std::multiset<int>q;
        for(int i=1;i<=m;++i) q.insert(a[i]);
        int b=(a[1]+a[2]+a[o])/2;
        ans[cnt][1]=b-a[o];ans[cnt][2]=b-a[2];ans[cnt][3]=b-a[1];//求解前三个数
        if(ans[cnt][1]<=0||p[ans[cnt][1]]) continue;//特判元素不合法或重复出现（因为 b 求解出来一定单调不降，所以第一个数为正 b 可能合法，但其非正 b 一定不合法）
        //至于重复出现的序列只需判第一个数，根据上面的方程求解，会发现 b1 决定所有的 bi
        p[ans[cnt][1]]=1;
        bool flag=1;
        for(int i=1;i<3;++i)
            for(int j=i+1;j<=3;++j){
                auto k=q.find(ans[cnt][i]+ans[cnt][j]);
                if(k==q.end()){//特判无解
                    flag=0;
                    break;
                }
                q.erase(k);//删除可能小于 b1+b4 的数。
            }
        if(!flag) continue;
        for(int i=4;i<=n;++i){
            ans[cnt][i]=*q.begin()-ans[cnt][1];
            q.erase(q.begin());
            for(int j=2;j<i;++j){
                auto w=q.find(ans[cnt][j]+ans[cnt][i]);
                if(w==q.end()){//特判无解
                    flag=0;
                    break;
                }
                q.erase(w);//删除可能小于 b1+b(i+1) 的数。
            }
            if(!flag) break;
        }
        if(flag){//检验序列是否合法
            c=0;
            for(int i=1;i<n;++i)
                for(int j=i+1;j<=n;++j)
                    s[++c]=ans[cnt][i]+ans[cnt][j];
            std::sort(s+1,s+c+1);
            for(int i=1;i<=m;++i){
                if(s[i]!=a[i]){
                    flag=0;
                    break;
                }
            }
        }
        cnt+=flag;
    }
    cout<<cnt<<'\n';//有序输出答案
    for(int i=0;i<cnt;++i)
        for(int j=1;j<=n;++j)
            cout<<ans[i][j]<<(j==n?'\n':' ');
    return 0;
}
```

---

## 作者：BF_AlphaShoot (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P3540)

首先要对所给序列 $sum$ 升序排序。

设 $x_i$ 为所求原序列从小到大排列后第 $i$ 个元素，考虑这样的图：

$x_1+x_2\quad x_2+x_3\quad x_3+x_4\quad x_4+x_5\cdots\quad x_{n-1}+x_n$

$x_1+x_3\quad x_2+x_4\quad x_3+x_5\quad\cdots\quad x_{n-2}+x_n$

$x_1+x_4\quad x_2+x_5\quad\cdots\quad x_{n-2}+x_n$

$\vdots$

$x_1+x_{n-1}\quad x_2+x_n$

$x_1+x_n$

不难发现：$x_1+x_2$ 与 $x_1+x_3$ 一定分别是所给序列中第 $1、2$ 小，即 $sum_1、sum_2$。既然确定了这两个式子，我们还需要 $x_2+x_3$ 才能解出 $x_1、x_2、x_3$ 的值。发现 $n\leqslant300$，所以直接暴力枚举是否满足即可。

当得出 $x_1、x_2、x_3$ 后，其余的和数中 $x_3+x_4$ 最小，由此得出 $x_4$ 的值并能找出 $x_2+x_4、x_1+x_4$ ，再找其余的和数中最小的 $x_4+x_5$……以此类推，每次对应一列最底层的和数都会成为最小，推广即可。

View code：

```cpp
#include<bits/stdc++>
using namespace std;

#define ri register int
#define il inline

const int INF=0x3f3f3f3f,N=310;
int n,m,cnt;
int sum[N*N],p[N*N],ans[N][N];
bool b[N*N];

il ll read(){
    ll x=0,y=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            y=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*y;
}

il bool cmp(int x,int y){
    return x<y;
}

il void check(int x){
	memset(b,0,sizeof(b));
	if((sum[1]+sum[2]+sum[x])&1)
        return;
	p[1]=(sum[1]+sum[2]+sum[x])/2-sum[x];
	p[2]=sum[1]-p[1];
	p[3]=sum[2]-p[1];
	b[1]=b[2]=b[x]=true;
	for(ri i=4,j=3;i<=n;i++){
		while(j<=m&&b[j])
			j++;
		if(j>m)
			return;
		p[i]=sum[j]-p[1];
		b[j]=true;
		for(ri k=2;k<i;k++){
			if (p[k]>p[i])
				return;
			int v=p[k]+p[i],l=lower_bound(sum+1,sum+m+1,v)-sum,lb=l;
			if(sum[l]!=v)
				return;
			while(lb&&sum[lb]==sum[l])
				lb--;
			lb++;
			while(lb<=m&&sum[lb]==sum[l]&&b[lb])
				lb++;
			if(sum[lb]!=sum[l]||b[lb]) return;
			l=lb;
			b[l]=true;
		}
	}
	cnt++;
	for(ri i=1;i<=n;i++)
		ans[cnt][i]=p[i];
}

signed main(){
    n=read();
    m=(n*(n-1))>>1;
    for(ri i=1;i<=m;i++)
        sum[i]=read();
    sort(sum+1,sum+m+1,cmp);
    for(ri i=3,j=i;i<=m;i=j){
		check(i);
		while(j<=m&&sum[j]==sum[i])
			j++;
	}
	printf("%d\n",cnt);
	for(ri a=1;a<=cnt;a++)
		for(ri b=1;b<=n;b++){
			printf("%d",ans[a][b]);
			if(b==n)
				printf("\n");
			else
				printf(" ");
		}
    return 0;
}
```

---

## 作者：zzzyyyyhhhhh (赞：0)

假设这 $N$ 个数是 $b_1, b_2, \dots, b_N$，已知的两两和有：
- $b_1 + b_2, b_1 + b_3, b_1 + b_4, \dots$
- $b_2 + b_3, b_2 + b_4, \dots$
   
 
核心思路是，首先利用前三个数的和来确定其中两个数的具体值。通过一个简单的公式，可以从两两和中推导出第一个数：  
$$b_1 = \frac{S_{12} + S_{13} - S_{23}}{2}$$
其中 $S_{12}$ 表示 $b_1 + b_2$，$S_{13}$ 表示 $b_1 + b_3$，$S_{23}$ 表示 $b_2 + b_3$。通过这个公式，我们可以得到 $b_1$，随后可以推出 $b_2, b_3$，再根据后续的和继续推导剩下的数。

我们从第三个数开始，检查它是否可以生成有效解。若符合所有条件，则将其作为一组解存储。

为避免重复解的出现，使用集合来存储数列解，这样可以自动去除重复的解，并保证解按字典序排序。由于题目要求字典序从大到小输出，我们可以利用 `greater` 来实现这一点。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=310;
int n;
set<array<int,N>,greater<array<int,N> > > ans;
int a[N*N],now;

void work(int x) 
{
    array<int,N> b;
    b[1] = (a[1] + a[2] - a[x]) / 2;
    multiset<int> tmp;
    
    // 将所有两两和存入multiset中方便查找和删除
    for(int i=1; i<=n*(n-1)/2; i++) 
    {
        tmp.insert(a[i]);
    }
    
    for(int i=2; i<=n; i++) {
        b[i] = (*tmp.begin()) - b[1];  // 推导出 b[i] 的值
        for(int j=1; j<i; j++) {
            // 验证b[i]和b[j]的和是否存在于给定的两两和集合中
            if(tmp.find(b[i]+b[j]) != tmp.end()) 
            {
                tmp.erase(tmp.find(b[i]+b[j]));  // 若存在则删除
            } 
            else 
            {
                return;  // 如果发现不合法的和，直接退出
            }
        }
    }
    
    ans.insert(b);  // 若合法则插入答案集合
}

signed main() 
{
    cin >> n;
    for(int i=1; i<=n*(n-1)/2; i++) 
    {
        cin >> a[i];
    }
    
    // 对所有两两和进行排序
    sort(a+1, a+1+n*(n-1)/2);
    
    // 尝试不同的 b[3]，逐步构造可能的解
    for(int i=3; i<=n; i++) 
    {
        if(a[1] + a[2] > a[i] && ((a[1] + a[2] - a[i]) % 2) == 0) 
        {
            work(i);  // 如果条件满足则构造解
        }
    }
    
    cout << ans.size() << '\n';  // 输出解的个数
    for(auto i: ans) 
    {
        for(int j=1; j<=n; j++) 
        {
            cout << i[j] << ' ';  // 输出每个解
        }
        cout << '\n';
    }
}
```

---

## 作者：tder (赞：0)

You can view the [English version](https://www.luogu.com/article/ggbqd4jm/) of this solution.

> 参考了 [this](https://www.luogu.com/article/v58iq4p8)。

我第一眼看这题的时候，首先想到了通过求 $\sum a_i$ 再推导的方式，然后发现当 $n>3$ 时没前途了。

不妨令序列单调不减，即 $a_i\le a_{i+1}$。

把这些和列出来：

$$
\begin{array}{}
a_1+a_2 & a_1+a_3 & a_1+a_4 & \cdots & a_1+a_n \\
 & a_2+a_3 & a_2+a_4 & \cdots & a_2+a_n \\
 & & a_3+a_4 & \cdots & a_3+a_n \\
 & & & \ddots & \vdots \\
 & & & & a_{n-1}+a_n
\end{array}
$$

显然的，有 $a_1+a_2$ 是其中最小的。于是，当知道 $a_1$ 时能确定 $a_2$。我们在表中删去第 $1$ 列，此时又有 $a_1+a_3$ 是最小的，那便可以确定 $a_3$。以此类推，我们仅需知道 $a_1$ 便可推出完整序列。用 multiset 维护之，复杂度 $\mathcal{O}(n^2\log n)$。

问题转化为如何确定 $a_1$。

一种显然的方法是枚举 $1\le a_1\le\lfloor\frac{a_1+a_2}2\rfloor$。这么做复杂度为 $\mathcal{O}(V\cdot n^2\log n)$，可通过 [P1286](/problem/P1286)。

考虑最开始的思路，当 $n=3$ 时我们是可以简单的通过求和再推导算出完整序列。而 $a_1+a_2$ 为最小值，$a_1+a_3$ 为次小值，仅有 $a_2+a_3$ 不确定。不难发现，其一定为前 $n$ 小的，这是由于只有表中第一行可能比它小。于是枚举即可。

复杂度 $\mathcal{O}(n^3\log n)$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e5 + 5;
int n, m, b[N]; vector<int> a;
vector<vector<int>> ans;
multiset<int> s;
void work() {
	s.clear();
	for(int i = 1; i <= m; i++) s.insert(b[i]); // cout<<"insert "<<b[i]<<endl;
	// for(int i : s) cout<<i<<" "; cout<<endl;
	for(int i = 1; i <= n; i++) {
		// cout<<i<<" qwq"<<endl;
		for(int j = 0; j < i - 2; j++) {
			// cout<<i - 2<<" & "<<j<<endl;
			if(!s.count(a[i - 2] + a[j])) return;
			s.extract(a[i - 2] + a[j]); // cout<<"erase "<<a[i - 2] + a[j]<<endl;
		}
		if(i <= 3) continue;
		// for(int j : s) cout<<j<<" "; cout<<endl;
		int k = *s.begin(), t = k - a.front();
		// cout<<t<<endl;
		if(t <= 0 || t < a.back()) return;
		a.push_back(t);
	}
	ans.push_back(a);
}
signed main() {
	cin>>n; m = n * (n - 1) / 2;
	for(int i = 1; i <= m; i++) cin>>b[i];
	sort(b + 1, b + m + 1);
	int x = b[1], y = b[2], z = b[3];
	for(int i = 3; i <= n; i++, z = b[i]) {
		int t = (x + y + z) / 2; a = {t - z, t - y, t - x};
		if(a.front() <= 0) continue;
		// cout<<"a = {"<<a[0]<<", "<<a[1]<<", "<<a[2]<<"}"<<endl;
		work();
	}
	sort(ans.begin(), ans.end(), greater<vector<int>>());
	ans.erase(unique(ans.begin(), ans.end()), ans.end());
	cout<<ans.size()<<endl;
	for(auto i : ans) {
		for(auto j : i) cout<<j<<" ";
		cout<<endl;
	}
}
```

---

## 作者：_maze (赞：0)

这题结论很散但是很好推。所以我会以一个一个性质作为题解主线。

下文中我们定义序列 $a$ 为从小到大排序过后的询问序列，$b$ 为从小到大排序过后的原序列。

## 性质一

> $a_1=b_1+b_2$，且 $a_2=b_1+b_3$。

最小的两个数相加肯定最小，对于 $b_1+b_3$，发现除了把这个数变为 $b_1+b_2$ 外，都会把两数之和变大。所以它为第二小。

## 性质二

> 若 $b_1+b_3$ 和为 $x$，则可求出 $b_1,b_2,b_3$。

如果知道了 $b_1 + b_3$，那么实际上三个等式可以构成三元一次方程组。直接解即可。

## 性质三

> 将 $b$ 的前 $i$ 个数两两之和从 $a$ 中删除后，$a$ 中最小值为 $b_1+b_{i+1}$。

仿照性质一后半证法，对于 $b_1+b_{i+1}$，我们不能将 $b_{i+1}$ 变成更小的数，因为我们已经将 $b$ 中前 $i$ 个数两两之和从 $a$ 中删除了。我们也不能将 $b_1$ 变成更小的数，因为它是 $b$ 序列中最小的数。所以得证。

其实性质一后半部分就是性质三的一个特殊情况。

## 解法

通过以上三个推导，其实我们已经有一个解法了。

根据性质一与性质二，我们可以枚举 $b_1+b_3$ 的值，然后解出 $b_1,b_2,b_3$，接着根据性质三，递推后面的 $b$ 序列即可。

由于这个方程结构特殊，我们不需要高斯消元。而对于删除操作，哈希表精细实现可以达到 $O(n)$，但是我摆了，用了一点代码技巧，时间复杂度多了一些，总体是 $O(n^2\log n)$ ~~但还跑挺快~~。具体看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 305;
int read(int t = 0, bool f = 1, char c = 0) {
	while(!isdigit(c = getchar())) f = c^45;
	while(isdigit(c)) t = (t << 1) + (t << 3) + (c ^ 48), c = getchar();
	return f ? t: -t;
}
int n;
array<int, N * (N - 1) / 2> a;
vector<vector<int>> ans;
struct hash {
  multiset<int> s;//谁正经写哈希啊
  void ins(int u) { s.insert(u); }
  void del(int u) { s.erase(s.lower_bound(u)); }
  int count(int u) { return *s.lower_bound(u) == u ? 1 : 0; }
  void clear() { s.clear(); }
  int mn() { return *s.begin(); }
}h;
void solve(int u, int v = a[1], int w = a[2]) {
  if ((u + v + w) % 2 == 1) return ;
  h.clear();
  vector<int> p;int sum = (u + v + w) >> 1, x = sum - u;
  for (int i = 1; i <= n * (n - 1) / 2; ++i) h.ins(a[i]);
  p.push_back(sum - u), p.push_back(sum - w), p.push_back(sum - v); 
  h.del(u), h.del(w), h.del(v); 
  for (int i = 4; i <= n; ++i) {
    int mn = h.mn(), d = mn - x;
    for (auto v : p) {
      if (h.count(v + d) == 0) return ;
      h.del(v + d);
    }
    p.push_back(d);
  }
  sort(p.begin(), p.end());
  ans.push_back(p);
}
signed main() {
  n = read();
  for (int i = 1; i <= n * (n - 1) / 2; ++i) a[i] = read();
  sort(a.begin() + 1, a.begin() + (n * (n - 1) / 2) + 1);
  for (int i = 3; i <= n; ++i) if (i == 3 || a[i] != a[i - 1]) solve(a[i]);// 注意相同解要删除
  printf("%ld\n", ans.size());
  for (auto p : ans) {
    for (auto v : p) printf("%d ", v);
    puts("");
  }
  return 0;
}
```


---

## 作者：_Kenma_ (赞：0)

# P3540 解题报告

## 前言

模拟赛 T3。

很不错的性质题，写起来也有一定难度。

感觉很 OI。

## 思路分析

首先，我们把目标序列记为 $a$，把给出的序列记为 $x$。

钦定 $a,x$ 都是单调不降的。

不难发现：

$$x_1=a_1+a_2$$

$$x_2=a_1+a_3$$

然后考虑如果确定了 $a_2+a_3$ 的值，那么 $a_1,a_2,a_3$ 都是确定的了。

当 $a_1,a_2,a_3$ 的值都确定后，我们把 $a_1,a_2,a_3$ 两两相加的和从 $x$ 中删去，这样，序列 $x$ 中最小的元素是 $a_1+a_4$，这样就能确定 $a_4$ 的值。

以此类推，当 $i \ge 3$ 时，$a_1,a_2,a_3,\cdots,a_i$ 的值能够唯一确定 $a_{i+1}$ 的值。

因此，当 $a_1,a_2,a_3$ 的值确定时，整个序列 $a$ 是唯一的。

再推得，当 $a_2+a_3$ 的值确定时，整个序列 $a$ 是唯一的。

所以只需要枚举 $a_2+a_3$ 的值，然后模拟上面求解的过程，判断求解出的 $a$ 是不是合法即可。

整体复杂度 $O(n^3\log m)$。

## 代码实现

这道题不用按字典序排序什么的，代码写了是因为模拟赛有要求。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans,a[1000005],b[1000005],dfn[1000005];
multiset<int> s;
map<int,int> mp;
vector<int> v[1000005];
bool cmp(int x,int y){
	return x<y;
}
bool cmp2(int x,int y){
	for(int i=0;i<v[x].size();i++){
		if(v[x][i]>v[y][i]) return true;
		if(v[x][i]<v[y][i]) return false;
	}
	return true;
}
signed main(){
	//freopen("data3.in","r",stdin);
	//freopen("WA3.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	m=n*(n-1)/2;
	for(int i=1;i<=m;i++){
		cin>>a[i];
	}
	sort(a+1,a+m+1);
	for(int i=3;i<=n;i++){
		int k=a[i];
		if(mp.count(k)){
			continue;
		}
		mp[k]=1;
		b[1]=(a[1]+a[2]-k)/2;
		if(b[1]<=0) break;
		s.clear();
		for(int j=3;j<=m;j++){
			s.insert(a[j]);
		}
		s.erase(s.find(k));
		b[2]=a[1]-b[1];
		b[3]=a[2]-b[1];
		if(b[2]<=0 || b[3]<=0) continue;
		bool flag=false;
		for(int j=4;j<=n;j++){
			b[j]=(*s.begin())-b[1];
			if(b[j]<=0){
				flag=true;
				break;
			}
			for(int t=1;t<j;t++){
				if(s.find(b[t]+b[j])==s.end()){
					flag=true;
					break;
				}
				s.erase(s.find(b[t]+b[j]));
			}
			if(flag){
				break;
			}
		}
		if(flag){
			continue;
		}
		ans++;
		for(int j=1;j<=n;j++){
			v[ans].push_back(b[j]);
		}
	}
	for(int i=1;i<=ans;i++){
		sort(v[i].begin(),v[i].end(),cmp);
	}
	for(int i=1;i<=ans;i++) dfn[i]=i;
	sort(dfn+1,dfn+1+ans,cmp2);
	cout<<ans<<'\n';
	for(int i=1;i<=ans;i++){
		for(int j=0;j<v[dfn[i]].size();j++){
			cout<<v[dfn[i]][j]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

## 后记

挺有意思的一道题。

可能需要一定的逻辑推理能力。

---


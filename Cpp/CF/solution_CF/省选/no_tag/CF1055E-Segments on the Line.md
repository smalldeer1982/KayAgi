# Segments on the Line

## 题目描述

给定一个整数序列 $a_1, a_2, \ldots, a_n$，以及该序列的 $s$ 个区间 $[l_j, r_j]$（其中 $1 \le l_j \le r_j \le n$）。

你需要恰好选择 $m$ 个区间，使得被至少一个区间覆盖的 $a_i$ 组成的多重集合的第 $k$ 小值尽可能小。如果无法选择 $m$ 个区间使得多重集合中元素数量不少于 $k$，输出 $-1$。

多重集合的第 $k$ 小值指的是将多重集合中的元素按非降序排列后，第 $k$ 个元素的值。

## 说明/提示

在第一个样例中，一种可行的方案是选择第一个和第三个区间。它们一共覆盖了序列中的三个元素（除了第三个元素以外的所有元素）。这样，被覆盖元素的第 $2$ 小值为 $2$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1055E/be333fc67d60280dc550835545d694b9e06ec26a.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 3 2 2
3 1 3 2
1 2
2 3
4 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 2 1 1
1 2 3 4 5
2 4
1 5
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5 3 3 5
5 5 2 1 1
1 2
2 3
3 4
```

### 输出

```
-1
```

# 题解

## 作者：Lgx_Q (赞：3)

[orz](https://www.luogu.com.cn/problem/CF1055E)

答案具有单调性。

二分这个答案 $mid$。

接下来 DP。

由于本人太菜，不能想到题解区大佬们最简洁跑最快的做法。

于是先观察性质。发现如果一条线段被另一条线段包含，那么一定不会选他。

所以我们排序去掉这样的线段。

这时剩下的线段左右端点都单调递增。

所以，鄙人设 $f_{i,j}$ 表示已经选了 $i$ 条线段，最后一条是第 $j$ 条，选出的点的最多个数。

设 $s_i$ 表示第 $1...i$ 个点中权值小于等于 $mid$ 的点的个数。

转移部分：对于 $f_{i,j}$，上一条线段可以与 $j$ 重叠可以不重叠。

不重叠：对于一个决策 $k(r_k<l_j)$，计算为 $f_{i,j}=f_{i-1,k}+s_{r_j}-s_{l_j-1}$。

重叠：对于一个决策 $k(r_k≥l_j)$，计算为 $f_{i,j}=f_{i-1,k}+s_{r_j}-s_{r_k}$。注意不需要判断包含关系。

由于左端点和右端点都递增，所以可以维护单调队列保存“重叠”部分的决策。每当一个决策出队时，加入“不重叠”部分的决策。用一个变量维护“不重叠”部分的决策的最大值即可。

时间 $O(nm\log a)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn=1510;
ll L,n,m,k,a[maxn],s[maxn],q[maxn],l,r,lo,hi,f[maxn][maxn];
struct qj
{
	ll l,r;
}b[maxn];
bool cmp(qj a,qj b)
{
	return a.l<b.l;
}
bool check(ll mid)
{
	for(ll i=1;i<=L;i++)
		s[i]=s[i-1]+(a[i]>mid?0:1);
	memset(f,0xcf,sizeof f);
	for(ll i=1;i<=n;i++) f[1][i]=s[b[i].r]-s[b[i].l-1];
	for(ll i=2;i<=m;i++)
	{
		l=1,r=0;
		for(ll j=i,mx=-1e17;j<=n;j++)
		{
			while(l<=r&&f[i-1][j-1]-s[b[j-1].r]>f[i-1][q[r]]-s[b[q[r]].r]) --r;
			q[++r]=j-1;
			while(l<=r&&b[q[l]].r<b[j].l)
			{
				mx=max(mx,f[i-1][q[l]]);
				++l;
			}
			f[i][j]=max((l<=r?s[b[j].r]-s[b[q[l]].r]+f[i-1][q[l]]:(ll)(-1e17)),mx+s[b[j].r]-s[b[j].l-1]); 
		}
	}
	for(ll i=m;i<=n;i++)
		if(f[m][i]>=k) return true;
	return false;
}
int main()
{
	scanf("%lld%lld%lld%lld",&L,&n,&m,&k);
	for(ll i=1;i<=L;i++) scanf("%lld",&a[i]);
	for(ll i=1;i<=n;i++)
		scanf("%lld%lld",&b[i].l,&b[i].r);
	sort(b+1,b+1+n,cmp);
	ll tot=0;
	for(ll i=1;i<=n;i++)
		if(!tot||b[tot].r<b[i].r) b[++tot]=b[i];
	n=tot;
	m=min(m,n);
	lo=1,hi=1e9;
	while(lo<=hi)
	{
		ll mid=lo+hi>>1;
		if(check(mid)) hi=mid-1;
		else lo=mid+1;
	}
	if(lo>1e9) lo=-1;
	printf("%lld",lo);
	return 0;
}
```

---

## 作者：Jay142753869 (赞：2)

原题传送门：[luogu](https://www.luogu.com.cn/problem/CF1055E)，[CF](https://codeforces.com/problemset/problem/1055/E)。  
题意：给定给 $n$ 个点，以及 $m$ 条线段，选择 $s$ 条线段，使得至少被一个线段覆盖的点的坐标从小到大排序后，第 $k$ 大最小，没有则输出 $-1$。  
第 $k$ 大最小显然考虑二分，每次验证当前的 $mid$是否有大于等于$k$个数小于  $mid$。  
验证我们用dp来验证，复杂度是 $O(nmslogn)$。  
这还不是最优解，这里用背包可以把 $m$ 优化掉了，我们找到每个点的 $next$， $next$代表包含这个点的最右端。就不难得到dp方程，这个时候 $m$ 已经没用了。  
最终复杂度 $O(nslogn)$。   
 _Code_
 ```cpp
#include<bits/stdc++.h>
#define maxn 2020
using namespace std;
struct node{
	int l,r;
}emm[maxn];
int a[maxn],b[maxn],n,s,m,k,sum[maxn],dp[maxn][maxn],nt[maxn];
bool check(int mid)
{
    for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+(a[i]<=mid);
    for(int i=0;i<=s;i++)
		for(int j=0;j<=n;j++)
			dp[i][j]=0;
    for(int i=1;i<=s;i++){//dp
        for(int j=1;j<=n;j++)
			dp[i][j]=max(dp[i][j],dp[i-1][j]);
        for(int j=1;j<=n;j++)
			if(nt[j])
				dp[i][nt[j]]=max(dp[i][nt[j]],dp[i-1][j-1]+sum[nt[j]]-sum[j-1]);
        for(int j=1;j<=n;j++)
			dp[i][j]=max(dp[i][j],dp[i][j-1]);
    }
    return dp[s][n]>=k;
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&k);
    for(int i=1;i<=n;i++) 
		scanf("%d",&a[i]),b[i]=a[i];
    for(int i=1;i<=m;i++) 
		scanf("%d%d",&emm[i].l,&emm[i].r);
    for(int i=1;i<=m;i++) 
		for(int j=emm[i].l;j<=emm[i].r;j++)
			nt[j]=max(nt[j],emm[i].r);
    sort(b+1,b+n+1);
	int l=1,r=n,mid,ans=-1;
    while(l<=r){//二分答案 
        mid=(l+r)>>1;
        if(check(b[mid])) ans=b[mid],r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans);
    return 0;
}
 ```

---

## 作者：极寒神冰 (赞：1)

考虑二分答案 $x$，问题就可以转化成，通过 $m$ 条线段覆盖了多少 $\le x$ 的数字。

考虑使用 dp 计算这个东西。令 $dp_{i,j}$ 表示前 $i$ 个点中已经选了 $j$ 条线段，转移考虑要么直接与上一个段重叠，要么不重叠（忽略包含的情况，因为这只意味着可以选择少于 $m$ 段）。在重叠的情况下，选择上一个段显然是最优的，而不重叠时直接找包含这个点的左端点最左显然是对的。

```cpp
int n,m,s,k;
int a[1555];
int l[1555],r[1555];
int dp[1555][1555];
int check(int x)
{
    memset(dp,0,sizeof(dp));
    R(i,1,n)
    {
        int lst=i+1,ss=0;
        R(j,1,s) if(l[j]<=i&&i<=r[j]) ckmin(lst,l[j]);
        R(j,lst,i) if(a[j]<=x) ++ss;
        R(j,1,m) dp[i][j]=max(dp[i-1][j],dp[lst-1][j-1]+ss);
    }
    return dp[n][m]>=k;
}
signed main()
{
    n=read(),s=read(),m=read(),k=read();
    R(i,1,n) a[i]=read();
    R(i,1,s) l[i]=read(),r[i]=read();
    int l=1,r=1000000000,best=-1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid)) best=mid,r=mid-1;
        else l=mid+1;
    }
    writeln(best);
}
```



---

## 作者：daniEl_lElE (赞：1)

二分排名为 $k$ 的点，将所有 $\leq mid$ 的点设为 $1$，否则为 $0$。

问题转化为是否能用至多 $m$ 个线段覆盖，使得覆盖的所有点的和 $\geq k$。

考虑 $dp_{i,j}$ 表示看到第 $i$ 个位置用了 $j$ 个线段去覆盖，覆盖点的的最大值。

转移显然可以从每个线段右端点枚举选择这个线段以及上一步的位置。这样做是 $O(ns^2)$ 的，无法通过。

容易发现转移的系数是区间的和，于是可以线段树上存 $dp_{i,j}$ 减去 $i$ 位置的前缀和，转移只需要求一个后缀的 $\max$ 即可。复杂度 $O(ns\log n)$。

总复杂度 $O(ns\log n\log V)$，这样是很难过的，离散化做到 $O(ns\log^2n)$ 就比较容易过了。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define double long double
#define mid ((l+r)>>1)
using namespace std;
vector<int> vc[1505];
int a[1505],tag[1505],pre[1505],f[1505][1505],lsh[1505];
struct sgt{
	int f[6005];
	void build(int i,int l,int r){
		f[i]=-1e9;
		if(l==r) return ;
		build(i*2,l,mid),build(i*2+1,mid+1,r);
	}
	void change(int i,int l,int r,int pos,int cg){
		if(l==r){
			f[i]=max(f[i],cg);
			return ;
		}
		if(pos<=mid) change(i*2,l,mid,pos,cg);
		else change(i*2+1,mid+1,r,pos,cg);
		f[i]=max(f[i*2],f[i*2+1]);
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		if(qr<=mid) return qry(i*2,l,mid,ql,qr);
		if(ql>mid) return qry(i*2+1,mid+1,r,ql,qr);
		return max(qry(i*2,l,mid,ql,qr),qry(i*2+1,mid+1,r,ql,qr));
	}
}tree[1505];
signed main(){
	int n,s,m,k; cin>>n>>s>>m>>k;
	for(int i=1;i<=n;i++) cin>>a[i],lsh[i]=a[i];
	sort(lsh+1,lsh+n+1);
	for(int i=1;i<=n;i++) a[i]=lower_bound(lsh+1,lsh+n+1,a[i])-lsh;
	for(int i=1;i<=s;i++){
		int l,r; cin>>l>>r;
		for(int j=l;j<=r;j++) tag[j]=1;
		vc[r].push_back(l);
	}
	for(int i=1;i<=n;i++) sort(vc[i].begin(),vc[i].end()); 
	int tot=0; for(int i=1;i<=n;i++) tot+=tag[i];
	if(tot<k){
		cout<<-1;
		return 0;
	}
	int L=1,R=n+1;
	while(L<R){
		int M=(L+R)>>1;
		for(int i=1;i<=n;i++) pre[i]=pre[i-1]+(a[i]<=M);
		memset(f,0,sizeof(f));
		for(int i=0;i<=m;i++) tree[i].build(1,0,n);
		tree[0].change(1,0,n,0,0);
		for(int i=1;i<=n;i++){
			for(int j=0;j<=m;j++){
				f[i][j]=f[i-1][j]; 
				if(j){
					f[i][j]=max(f[i][j],f[i][j-1]);
					for(auto v:vc[i]){
						f[i][j]=max(f[i][j],tree[j-1].qry(1,0,n,v-1,i-1)+pre[i]);
						break;
					}
				}
				tree[j].change(1,0,n,i,f[i][j]-pre[i]);
			}
		}
		if(f[n][m]<k) L=M+1;
		else R=M;
	}
	if(L==n+1){
		cout<<-1;
		return 0; 
	}
	cout<<lsh[L];
	return 0;
}

```

---

## 作者：_Clown_ (赞：0)

# E.Segments on the Line
$\mathtt{Difficulty}$=$\mathtt{2500}$

不难想到二分答案 $x$，验证是否有 $k$ 个及以上个受到的伤害小于 $x$。

对于这个问题，我们考虑 $\texttt{dp}$。

不妨设 $dp_{i,j}$ 表示前 $i$ 个点已经选择了 $j$ 条剑气。

转移考虑要么直接与上一个段重叠，要么不重叠（忽略包含的情况，因为这只意味着可以选择少于 $m$ 段）。

重叠的情况下，选择上一个段显然是最优的。

不重叠的情况下，直接找包含这个点的左端点最左显然是最优的。
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int N,M,S,K,A[10001],L[10001],R[10001],Dp[5001][5001];
inline bool Check(int X)
{
	register int i,j;memset(Dp,0,sizeof(Dp));
	for(i=1;i<=N;i++)
	{
		register int Last(i+1),Sum(0);
		for(j=1;j<=M;j++)if(L[j]<=i&&R[j]>=i)Last=min(Last,L[j]);
		for(j=Last;j<=i;j++)Sum+=(A[j]<=X);
		for(j=1;j<=S;j++)Dp[i][j]=max(Dp[i-1][j],Dp[Last-1][j-1]+Sum);
	}
	return Dp[N][S]>=K;
}
int main(void)
{
	BetterIO;
	register int i;cin>>N>>M>>S>>K;
	for(i=1;i<=N;i++)cin>>A[i];
	for(i=1;i<=M;i++)cin>>L[i]>>R[i];
	register int Left(1),Right(1000000000),Ans=-1;
	while(Left<=Right)
	{
		register int Middle=Left+Right>>1;
		if(Check(Middle))Ans=Middle,Right=Middle-1;
		else Left=Middle+1;
	}
	cout<<Ans<<endl;
	return 0;
}
```

---


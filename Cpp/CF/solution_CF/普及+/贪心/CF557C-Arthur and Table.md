# Arthur and Table

## 题目描述

Arthur has bought a beautiful big table into his new flat. When he came home, Arthur noticed that the new table is unstable.

In total the table Arthur bought has $ n $ legs, the length of the $ i $ -th leg is $ l_{i} $ .

Arthur decided to make the table stable and remove some legs. For each of them Arthur determined number $ d_{i} $ — the amount of energy that he spends to remove the $ i $ -th leg.

A table with $ k $ legs is assumed to be stable if there are more than half legs of the maximum length. For example, to make a table with $ 5 $ legs stable, you need to make sure it has at least three (out of these five) legs of the maximum length. Also, a table with one leg is always stable and a table with two legs is stable if and only if they have the same lengths.

Your task is to help Arthur and count the minimum number of energy units Arthur should spend on making the table stable.

## 样例 #1

### 输入

```
2
1 5
3 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
2 4 4
1 1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6
2 2 1 1 3 3
4 3 5 5 2 1
```

### 输出

```
8
```

# 题解

## 作者：gesong (赞：12)

题目传送门：[CF557C Arthur and Table](https://www.luogu.com.cn/problem/CF557C)。
# 思路

正难则反，我们需要最小化移走的腿的能量值，可以转化成最大化保留的腿的能量值。

我们将每一个长度相同的腿存入一个 vector 中，我们从大到小枚举每一个长度，对于每一个长度，根据贪心思想我们一定会选择**所有**这些点并将其设为 $x$，则还可以选择 $x-1$ 个椅子，直接在剩下的椅子中暴力选择前 $x-1$ 大的能量值即可，这里可以用 multiset 解决。

综上，我们就解决了最大化保留的腿的能量值这个问题，我们只需要将所有的能量值减去我们求出的答案即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N],b[N];
multiset<int,greater<int> >s;
vector<int>c[N];
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
main(){
	int n=read(),sum=0,ans=1e18;
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1;i<=n;i++) b[i]=read(),sum+=b[i],s.insert(b[i]);
	for (int i=1;i<=n;i++) c[a[i]].push_back(b[i]);
	for (int i=1;i<N;i++) sort(c[i].begin(),c[i].end(),greater<int>());
	for (int i=N;i>0;i--) if (!c[i].empty()){
		for (auto j:c[i]) s.erase(s.find(j));
		int sum1=0;
		for (auto j:c[i]) sum1+=j;
		int len=c[i].size()-1;
		if (s.size()<=len){
			for (auto i:s) sum1+=i;
			ans=min(ans,sum-sum1);
		} 
		else{
			for (auto i:s){
				if (!len) break;
				sum1+=i;
				len--;
			} 
			ans=min(ans,sum-sum1);
		}
	}
	cout <<ans;
	return 0;
}

```

---

## 作者：Allanljx (赞：1)

## 思路
将输入按 $l$ 从小到大排序，然后将 $d$ 的后缀和记录一下。 $dp_{i,j}$ 表示前 $i$ 个数，$d$ 小于等于 $j$ 的数的个数，这个也可以预处理出来。开个桶记录一下 $d$。然后枚举最长的腿的长度，大于它的腿肯定要拿走，小于的也要拿走一部分，由于 $l$ 已经排序过了，所以可以快速求出分界位置。这时就可以用到之前的后缀和和 $dp$ 了。最后取个最小值就行。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans=INT_MAX;
struct node
{
	int l,d;
}a[100005],b[100005];
int t[100005];
int dp[100005][205];
int hz[100005];
bool cmp(node aa,node bb) 
{
	return aa.l<bb.l;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].l;
	for(int i=1;i<=n;i++) cin>>a[i].d;
	for(int i=1;i<=n;i++) t[a[i].l]++;//桶 
	sort(a+1,a+n+1,cmp);//排序 
	for(int i=n;i>=1;i--) hz[i]=hz[i+1]+a[i].d;//后缀和 
	for(int i=1;i<=n;i++)//dp 
	{
		for(int j=1;j<=200;j++) dp[i][j]+=dp[i-1][j];
		dp[i][a[i].d]++;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=200;j++) dp[i][j]+=dp[i][j-1];
	}
	int now=n+1,now1=n;
	for(int i=100000;i>=1;i--)
	{
		if(!t[i]) continue;
		int sum=0;
		while(now>0)//分界 
		{
			if(a[now-1].l==i) break;
			now--;
		}
		while(now1>0)//分界 
		{
			if(a[now1].l<i) break;
			now1--;
		}
		sum+=hz[now];
		int d=now1-(t[i]-1);//要删的腿的个数 
		if(d<0) d=0;
		for(int j=1;j<=200;j++)
		{
			if(dp[now1][j]<d)
			{
				sum+=(dp[now1][j]-dp[now1][j-1])*j;
			}
			else
			{
				sum+=(d-dp[now1][j-1])*j;
				break;
			}
		}
		ans=min(ans,sum);
	}
	cout<<ans;
}
```

---

## 作者：Mobius127 (赞：1)

日常颓无脑题。。。

[题目传送门](https://www.luogu.com.cn/problem/CF557C)

题目要求**剩下的腿中最长的腿的数目要超过一半**，自然想到枚举最长的腿的长度。 --> $O(L)$

既然已经选定最长的腿，那我们必定需要把所有比它长的都去掉，因此还得排个序取后缀和。--> $O(nlog_2n+n)$

此时还有一个问题，去掉长的腿后，我们仍需要去掉一些短的腿才能满足题目要求。

那么，我们要去掉多少呢？

因为只需达到一半，所以我们拿该长度最早出现的位置 - 有多少个这样长度的腿即可。

我们已经处理完要减掉多少条腿，但我们还不知道应该减哪些腿。

答案很显然，若我们要减去 $x$ 条腿，只需减去长度短的中花费前 $x$ 小的腿即可。由于值域很小，我们完全可以直接 $O(nD)\ DP$ 出第 $i$ 个前各种花费的腿的数量 $f_{i, j}$。这样求答案的时间复杂度就变成了 $O(LD)$ 了。

总复杂度：$O(nlog_2n+nD+LD)$

### 

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#define int long long
#define gc() getchar()
#define min(a, b) (a<b?a:b)
#define N 100005
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
inline ll read(){
	char ch=gc();int x=0, f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=gc();}
	return x*f;
}
int n;
struct LEG{
	int l, d;
	bool operator < (const LEG &A) const{
		return l<A.l;
	}
}wood[N];
int f[N][205], suf[N], ans=INF, cnt[N];
int first[N], last[N];
bool u[N];
signed main(){
	scanf("%lld", &n);
	for(int i=1; i<=n; i++) wood[i].l=read();
	for(int i=1; i<=n; i++) wood[i].d=read();
	sort(wood+1, wood+n+1);
	for(int i=n; i>=1; i--) suf[i]=suf[i+1]+wood[i].d;
	for(int i=1; i<=n; i++){
		u[wood[i].l]=1;
		if(!first[wood[i].l]) first[wood[i].l]=i;
		last[wood[i].l]=i;
		for(int j=1; j<=200; j++)
			f[i][j]=f[i-1][j];
		f[i][wood[i].d]++;
	}
	for(int i=1; i<=wood[n].l; i++){
		if(!u[i]) continue;int ret=suf[last[i]+1];
		int less=first[i]-(last[i]-first[i]+1);
		for(int j=1; j<=200&&less>0; j++){
			if(f[first[i]-1][j]<=less)
				ret+=f[first[i]-1][j]*j, less-=f[first[i]-1][j];
			else ret+=less*j, less=0;
		}
		ans=min(ans, ret);
	}
	printf("%lld", ans);
	return 0;
}
/*
in:
10
1 1 3 4 5 6 7 8 9 10
10 10 4 2 3 4 2 2 2 2
out:
21
附一组数据 
*/
```


---

## 作者：szhqwq (赞：1)

## $\tt{Solution}$

考虑贪心。

将这些腿以 $l_i$ 为关键字排序、去重并计数，以下均在预处理之后的序列上讨论。

我们可以去枚举长度最长的腿 $l_x$，那么对于 $x < i \le n$，这些腿的长度均大于 $l_x$，是一定要拿掉的。

对于 $1 \le i < x$，我们只需要保证 $x - 1$ 严格小于长度为 $l_x$ 的腿的个数 $cnt_{l_x}$，才能满足题目条件。若 $x - 1 < l_x$，则不需要拿掉任何的腿；否则，只需要拿掉 $d_i$ 前 $(x - 1) - (cnt_{l_x} - 1)$ 小的腿即可。

这个东西可以用权值线段树维护，但是我直接大力主席树上去。

代码：[Link](https://codeforces.com/contest/557/submission/278361040)

---

## 作者：AK_heaven (赞：0)

### [CF557C](https://www.luogu.com.cn/problem/CF557C)

题目中的意思是从整个集合当中选出一个最优子集，满足最长的柱子的数量严格大于其他柱子的数量，并且权值和最大。

由于值域很小，所以考虑枚举最长的柱子，由贪心可得，最长的柱子必定全部选择，然后按照权值从大到小依次选择更短的柱子。

其中枚举最长柱子是 $O(n)$ 的，如果开一个桶来装比最长柱子小的柱子的权值分布情况的话，可以做到 $O(1)$ 的单权值查询，总时间复杂度 $O(n \log n + n d)$。

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF557C)

对于大众来说权值线段树的入门题，一道写起来让我破防的题目。

首先很套路的固定最大值 $x$，这时候考虑什么时候答案最小。

首先所有大于 $x$ 的腿我们要删掉，记这个和为 $s$。其次发现，删掉长度等于 $x$ 的腿必然是不优的，因为删去了长度等于 $x$ 的腿代表我还要删掉更多长度小于 $x$ 的腿来满足条件。

假设长度为 $x$ 的腿有 $len$ 个，如果小于 $x$ 的腿的数量 $p\leq len-1$ 的话，说明不用删掉长度小于 $x$ 的腿就能满足条件，这时候算出 $s$ 是容易的。

如果 $p>len-1$ 的话，这就说明我们需要删掉长度小于 $x$ 代价前 $p-len+1$ 小的所有腿，如果我们从前往后扫值域的话，就发现我们还要会维护单点修改。

观察到 $d$ 很小，可以考虑权值线段树解决，维护对于每种代价出现的次数以及和，我们要找到前 $p-len+1$ 小的话直接在上面做线段树二分就行。

找到对应位置以后剩下就是一个求和的事情了，写了两只 $\log$ 的劣解。

可能是太久没写OI了，前前后后写了很久，破防了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
struct node{
	int sum,num;
}d[N];
vector<int> g[N];
int l[N],D[N],n,sum,num,prelst,ans=INT_MAX,now,V=100000;
void update(int l,int r,int s,int t,int p){
	if(l<=s&&t<=r){
		d[p].num++,d[p].sum+=s;return ;
	}
	int mid=(s+t)>>1;
	if(l<=mid)	update(l,r,s,mid,p<<1);
	if(r>mid)	update(l,r,mid+1,t,p<<1|1);
	d[p].num=d[p<<1|1].num+d[p<<1].num,d[p].sum=d[p<<1|1].sum+d[p<<1].sum;
}
int Querynum(int l,int r,int s,int t,int p){
	if(l>r)	return 0;
	if(l<=s&&t<=r)	return d[p].num; 
	int mid=(s+t)>>1,ans=0;
	if(l<=mid)	ans+=Querynum(l,r,s,mid,p<<1);
	if(r>mid)	ans+=Querynum(l,r,mid+1,t,p<<1|1);
	return ans;
}
int Query(int s,int t,int p,int num){
	if(s==t)	return s;
	int mid=(s+t)>>1,ans=-1;
	if(Querynum(1,mid,1,200,1)>=num)	ans=Query(s,mid,p<<1,num);
	else if(Querynum(1,t,1,200,1)>=num)	ans=Query(mid+1,t,p<<1|1,num);
	return ans;
}
int Querysum(int l,int r,int s,int t,int p){
	if(l>r)	return 0;
	if(l<=s&&t<=r)	return d[p].sum;
	int mid=(s+t)>>1,ans=0;
	if(l<=mid)	ans+=Querysum(l,r,s,mid,p<<1);
	if(r>mid)	ans+=Querysum(l,r,mid+1,t,p<<1|1);
	return ans;
}
void Add(int x){
	for(int i=0;i<g[x].size();i++)	update(g[x][i],g[x][i],1,200,1);
	now+=g[x].size();
}
int main()
{
	int prelst1=0;
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>l[i];
	for(int i=1;i<=n;i++)	cin>>D[i],g[l[i]].push_back(D[i]),prelst+=D[i],prelst1+=D[i];
	for(int i=1;i<=V;i++){
		num=0,sum=0;
		if(g[i].size()==0)	continue;
		for(int j=0;j<g[i].size();j++)	prelst-=g[i][j];
		int len=g[i].size(),pre=len*2-1;
		if(now+g[i].size()<=pre){ans=min(ans,prelst),Add(i);continue;}
		if(g[i].size()==1){ans=min(ans,prelst1-g[i][0]),Add(i);continue;}
		int Q=Query(1,200,1,now-(pre-len));
		ans=min(ans,prelst+Querysum(1,Q-1,1,200,1)+(now+len-pre-Querynum(1,Q-1,1,200,1))*Q),Add(i);
	} 
	cout<<ans<<endl;
	return 0;
}
/*
10
20 1 15 17 11 2 15 3 16 3
129 114 183 94 169 16 18 104 49 146
*/ 

```

---

## 作者：Code_AC (赞：0)

刚一个同学用优先队列倒着搞切了这道题，他的思路挺好的，但刚发现了另外一种线段树搞的方法，发篇题解分享一下。

题意就不多说了。

首先，我们看复杂度，题目数据范围是 $1\leqslant n \leqslant 10^5$，那么一种 $\mathcal{O}(n\log n)$ 会是比较可能的。

然后分析题目可以想到一个方法：从小到大枚举我们要留下的最长桌腿的长度 $i$，将长度大于 $i$ 的桌腿全删掉，此时考虑一下是否删够了，即我们枚举到的 $i$ 的数量是否超过了剩下数量的一半，超过就直接更新答案好了，没满足就还得从比 $i$ 小的里面删。

然后就来到了本题的关键部分：
**该如何筛选比 $i$ 小的桌腿呢？**

显然，若假设还需删 $k$ 条，那么肯定是在小的里面找消耗能量前 $k$ 小的删掉。教练第一反应是平衡树，但太难写也太难调，所以我们这里考虑到用权值线段树。

取所有代价中的最大值 $maxd$，以 $1\sim maxd$ 为值域建立权值线段树，在此过程中我们要记录两个量，$sum_i$ 是子树中所有代价之和，$num_i$ 是子树中桌腿的数量。

然后我们要保证有序，就在枚举的同时，将每一次枚举完的桌腿都插到树里，将小的往左插，大的往右插。

```cpp
int t[MAXN<<2],num[MAXN<<2];

inline void pushup(int p)
{
    t[p]=t[p<<1]+t[p<<1|1];
    num[p]=num[p<<1]+num[p<<1|1];
    return;
}

inline void change(int p,int l,int r,int k)//在线段树上插入一根代价为k的桌腿
{
    if(l==r)
    {
        num[p]++,t[p]+=k;
        return;
    }
    int mid=(l+r)>>1;
    if(k<=mid) change(p<<1,l,mid,k);
    else change(p<<1|1,mid+1,r,k);
    pushup(p);
}

inline int ask(int p,int l,int r,int k)//查询区间内前k小的代价总和
{
    if(l==r) return l*k;
    int mid=(l+r)>>1;
    if(num[p<<1]==k) return t[p<<1];
    else if(num[p<<1]>k) return ask(p<<1,l,mid,k);
    else return t[p<<1]+ask(p<<1|1,mid+1,r,k-num[p<<1]);
}

```

我们可以用一个 vector 来将桌腿高度相同的代价存在一起，后面就方便从小到大枚举。

```cpp
for(int i=1;i<=n;i++)
{
    d[i]=read();maxd=max(maxd,d[i]);
    V[l[i]].push_back(d[i]);sum+=d[i];//累加所有代价
}
for(int i=1;i<=maxl;i++)
    if(V[i].size())
    {
        cnt+=V[i].size();
        for(int j=0;j<V[i].size();j++) sum-=V[i][j];//将枚举自身减掉,每次都是剩比自己更大的
        if(cnt>V[i].size()) add=ask(1,1,maxd,cnt-V[i].size()*2+1);//若不够，则去小的里面找
        else add=0;
        ans=min(ans,sum+add);//更新答案
        for(int j=0;j<V[i].size();j++) change(1,1,maxd,V[i][j]);
    }
```

AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+5;
const int INF=0x7f7f7f7f7f7f7f7f;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

int n;
vector<int>V[MAXN];
int t[MAXN<<2],num[MAXN<<2];

inline void pushup(int p)
{
    t[p]=t[p<<1]+t[p<<1|1];
    num[p]=num[p<<1]+num[p<<1|1];
    return;
}

inline void change(int p,int l,int r,int k)
{
    if(l==r)
    {
        num[p]++,t[p]+=k;
        return;
    }
    int mid=(l+r)>>1;
    if(k<=mid) change(p<<1,l,mid,k);
    else change(p<<1|1,mid+1,r,k);
    pushup(p);
}

inline int ask(int p,int l,int r,int k)
{
    if(l==r) return l*k;
    int mid=(l+r)>>1;
    if(num[p<<1]==k) return t[p<<1];
    else if(num[p<<1]>k) return ask(p<<1,l,mid,k);
    else return t[p<<1]+ask(p<<1|1,mid+1,r,k-num[p<<1]);
}

int l[MAXN],d[MAXN];

signed main()
{
    n=read();int maxl=-1,maxd=-1;int ans=INF,sum=0,cnt=0,add;
    for(int i=1;i<=n;i++) l[i]=read(),maxl=max(maxl,l[i]);
    for(int i=1;i<=n;i++)
    {
        d[i]=read();maxd=max(maxd,d[i]);
        V[l[i]].push_back(d[i]);sum+=d[i];
    }
    for(int i=1;i<=maxl;i++)
        if(V[i].size())
        {
            cnt+=V[i].size();
            for(int j=0;j<V[i].size();j++) sum-=V[i][j];
            if(cnt>V[i].size()) add=ask(1,1,maxd,cnt-V[i].size()*2+1);
            else add=0;
            ans=min(ans,sum+add);
            for(int j=0;j<V[i].size();j++) change(1,1,maxd,V[i][j]);
        }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：yzh_Error404 (赞：0)

首先看到长度最长的腿的数目要超过一半直接可以想到枚举最长的桌腿。

题目让我们拆桌腿，那我们就~~套路化的~~放桌腿。

因为所有的能量都是正的，所以放的桌腿肯定越多越好。

对于每一个枚举到的最长的桌腿，肯定要将这个长度的桌腿全部选上，然后可以附带一些长度没他长的桌腿。

具体做法是首先按长度排序，用两个堆记录当前长度之前的所有能量，并且保证小根堆中的所有数都大于大根堆中的数，若当前最长桌腿的数量为 $s$，那么附带的桌腿数量为 $s-1$，通过弹出和插入小根堆使他的长度为 $s-1$，这时，小根堆中的所有数就是选的所有桌腿的能量。

代码实现：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+5;
struct node
{
    int l,d;
}e[MAXN];
priority_queue<int,vector<int>,greater<int> >q1;
priority_queue<int,vector<int>,less<int> >q2;
inline bool cmp(node a,node b)
{
    if(a.l==b.l)return a.d<b.d;
    return a.l<b.l;
}
ll n,eg,ans,sum=0;
signed main()
{
    scanf("%lld",&n);
    for(register int i=1;i<=n;i++)
        scanf("%d",&e[i].l);
    for(register int i=1;i<=n;i++)
        scanf("%d",&e[i].d),eg+=e[i].d;
    ans=eg-e[1].d;
    for(register int i=1;i<=n;i++)
        ans=min(ans,eg-e[i].d);
    sort(e+1,e+1+n,cmp);
    for(register int i=1;i<=n;)
    {
        int j=i,now=e[i].d;
        while(e[j+1].l==e[i].l&&j+1<=n)now+=e[++j].d;
        ans=min(ans,eg-now);
        int len=j-i;//这是可以附带的桌腿数
        while(q1.size()<len&&!q2.empty()){q1.push(q2.top());sum+=q2.top();q2.pop();}
        while(q1.size()>len){q2.push(q1.top());sum-=q1.top();q1.pop();}//通过插入和弹出来使小根堆中恰好有len个数
        ans=min(ans,eg-now-sum);
        for(register int k=i;k<=j;k++)
        {
            if(q2.empty()||e[k].d>q2.top())q1.push(e[k].d),sum+=e[k].d;//依旧要满足小根堆中的所有数大于大根堆中的所有数
            else q2.push(e[k].d);
        }
        i=j+1;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

套路地，枚举最后的最大值，这个可以做到 $O(V_a)$，$V=10^5$。

接下来考虑最大值为 $m$ 时，如何计算花费。

先对原序列按照 $a_{i}$ 升序排序，方便处理。

+ 对于 $a_i>m$，显然必须删去，也就是可以记录一个 $b_i$ 的后缀和 $s$，操作到 $i$ 时 $s\gets s-b_i$。

+ 其次，$a_i<m$ 的，设有 $p$ 个，$a_i$ 在原 $a$ 序列中出现 $q$ 次，就应该删去 $p-(q-1)=p-q+1$ 个。出于贪心的思想，删最小的那些。看到值域这么小，可以使用桶把 $b_i$ 塞进去，每次从小到大扫一遍扫出 $(p-q+1)$ 个。这是 $O(V_b)$ 的。

对于一个 $a_i$，将上述两种情况合并即可。

考虑实现。我们可以在 $a_{i}\not =a_{i+1}$ 时统计答案。此时，第一种情况的花费就是记录到现在的后缀和。第二种情况，$p=i-t_{a_i},q=t_{a_i}$，故需要删除 $(i-2\times t_{a_i}+1)$ 个数。至于怎么删说过了。

为了防止和当前的 $a_i$ 相等的 $a_j$ 的 $b_j$ 影响结果，我们等统计完答案再把这一段塞进桶。

```cpp
#include <stdio.h>
#define rep(i,l,r) for(i=l;i<=r;++i)
//using ll=long long;
const int V=205;
int t[V],v[V],tt[100005];
class Etinorally
{
public:
	int x,y;
	inline const bool operator<(const Etinorally &other)const
	{
		return x<other.x;
	} 
}e[100005]; 
inline int solve(int divv)
{
	if(divv<=0)
		return 0;
	int i,ret=0;
	rep(i,1,V)
	{
		if(t[i]>divv)
		{
			ret+=divv*i;
			return ret;
		}else
		{
			ret+=t[i]*i;
			divv-=t[i];
		}
//		printf("::%d %d\n",i,divv);
	}
	return ret;
}
//cnt-t[div]+1<=t[i]
int n,i,j,ret;
#include <algorithm>
inline int min(int x,int y){return x<y?x:y;}
int main()
{ 
	int sum=0;
	ret=1<<25;
	scanf("%d",&n);
	rep(i,1,V)
		t[i]=0;
	rep(i,1,100000)
		tt[i]=0;
	rep(i,1,n)
		scanf("%d",&e[i].x);
	rep(i,1,n)
		scanf("%d",&e[i].y);
	rep(i,1,n)
		++tt[e[i].x];
	std::sort(e+1,e+n+1);
	rep(i,1,n)
		sum+=e[i].y;
	rep(i,1,n)
	{
		sum-=e[i].y;
		if(e[i].x==e[i+1].x)
			continue;
//			printf("%d %d\n",sum,i-2*tt[e[i].x]);
		ret=min(ret,sum+solve(i-2*tt[e[i].x]+1));
		rep(j,i-tt[e[i].x]+1,i)
			++t[e[j].y];
	}
	printf("%d\n",ret);
	return 0;
}

```

---


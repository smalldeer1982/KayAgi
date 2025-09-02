# [ABC373E] How to Win the Election

## 题目描述

现在正在举行一场选举，有 $N$ 位候选人，编号为 $1, 2, \ldots, N$。目前已经有 $K$ 张选票，其中一些已经被计入。

到目前为止，第 $i$ 位候选人已经获得了 $A_i$ 票。

在所有选票被计完后，如果某位候选人的得票数比他们多的候选人数少于 $M$，那么该候选人将被当选。可能会有多位候选人同时当选。

对于每个候选人，求出他们需要从剩余的选票中获得的最少票数，以确保无论其他候选人获得多少票，他们都能当选。

具体来说，对于每个 $i = 1, 2, \ldots, N$，解决以下问题：

确定是否存在一个非负整数 $X$，其不超过 $K - \displaystyle{\sum_{i=1}^{N}} A_i$，并满足以下条件。如果存在，找出满足条件的最小 $X$。

- 如果候选人 $i$ 获得了 $X$ 张额外选票，那么候选人 $i$ 将始终当选。

## 说明/提示

- $1 \leq M \leq N \leq 2 \times 10^5$。
- $1 \leq K \leq 10^{12}$。
- $0 \leq A_i \leq 10^{12}$。
- $\displaystyle{\sum_{i=1}^{N} A_i} \leq K$。

## 样例 #1

### 输入

```
5 2 16
3 1 4 1 5```

### 输出

```
2 -1 1 -1 0```

## 样例 #2

### 输入

```
12 1 570
81 62 17 5 5 86 15 7 79 26 6 28```

### 输出

```
79 89 111 117 117 74 112 116 80 107 117 106```

# 题解

## 作者：dayz_break404 (赞：10)

挺需要细心的一道题。
### 题目分析 
显然答案具有单调性，考虑进行二分答案。

记当前的第 $i$ 个人已经获得了 $a_i$ 张选票，考虑如何计算当前第 $i$ 个人的答案。假设当前二分的答案是 $mid$，即当前的第 $i$ 个人可以多拥有 $mid$ 张选票，考虑贪心，我们应该优先将剩余的选票给与第 $i$ 个人选票差距更小的，直到比第 $i$ 个人更多的人数达到 $m$ 个，若剩余的选票不够，则二分的答案是可行的，反之则不可行。

具体地，可以先复制一份原数组，并对其进行升序排序，然后在排序后的数组中二分找到第一个严格大于 $a_i+mid$ 的，记为 $x$。考虑计算将第 $i$ 个人落选所需要的剩余选票应该为：
$$\sum_{j=n-m+1}^{x-1}a_i+mid-a_j$$

很明显代价可以通过维护排序后数组的前缀和求出。

但这里要注意一个问题，有可能我们计算代价的区间 $[n-m+1,x-1]$ 是包含了 $i$ 的，所以这个时候需要将区间左端点向左移一个单位，计算新区间的贡献并减去第 $i$ 个人的贡献即可。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
const int maxn=2e5+20;
ll n,m,a[maxn],k,sum[maxn],l,r,ans,b[maxn];
inline int check(int id,ll mid){
	ll now=k-sum[n]-mid;
	int x=upper_bound(a+1,a+1+n,b[id]+mid)-a-1;//区间右端点
	int y=n-m+1;//区间左端点
	if(n==m) return 1;//坑点
	if(n-x>=m) return 0;//已经大于了m个人
	if(a[y]>b[id]) return 1ll*(x-y+1)*(b[id]+mid+1)-(sum[x]-sum[y-1])>now;//区间不包含第i个人
	return 1ll*(x-y+1)*(b[id]+mid+1)-(sum[x]-sum[y-2]-b[id])>now;
}
int main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++) a[i]=read(),b[i]=a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=n;i++){
		l=0,r=k-sum[n],ans=1e16;
		while(l<=r){
			ll mid=l+r>>1;
			if(check(i,mid)) ans=mid,r=mid-1;
			else l=mid+1;
		}
		if(ans==1e16) printf("-1 ");
		else printf("%lld ",ans);
	}
	puts("");
	return 0;
}
```

---

## 作者：HasNoName (赞：2)

### 思路
不难发现票数如果多于正确票数则一定有解，少于则一定无解，故想到二分正确票数。

先对每个人的当前票数从大到小排序。

对于第 $i$ 个人，二分其需要增加的票数为 $k$，二分当前值在原序列中的位置，即找到一个合适的 $l$ 使 $A_l\le A_i+k$，$A_{l-1}>A_i+k$。

考虑如果想让第 $i$ 个人不上当选，则至少要让除第 $i$ 个人以外的前 $M$ 个人当选，可以使用前缀和计算。

还需要特判 $M=N$ 的情况，全部输出 $0$ 即可，不特判会挂一个点。

所以这题细节还是比较多的，每一步必须考虑完善。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+14;
struct T
{
	ll a,w;//a表示权值，w表示位置
}a[N];
ll ans[N],f[N],p,n,m;
bool cmp(T a,T b)
{
	return a.a>b.a;
}
bool ok(int k,ll x)
{
	if(a[k].a+x<a[m].a)return 0;
	ll l=1,r=m,mid;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(a[k].a+x>=a[mid].a)r=mid;
		else l=mid+1;
	}
	return (a[k].a+x+1)*(m-l+1)-(f[m]-f[l-1])+//若让k点不当选，则前m个点的票数至少为a[k]+x+1
(k<=m&&m<n)*(a[k].a+x+1-a[m+1].a-x-1)>p-x;//特判当先点本身票数当选情况下的增值
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m>>p;
	for(int i=1;i<=n;i++)
	{
		ll x;
		cin>>x;
		a[i].a=x;
		a[i].w=i;
		p-=x;
	}
	sort(a+1,a+n+1,cmp);//从大到小排序
	for(int i=1;i<=n;i++)f[i]=f[i-1]+a[i].a;//前缀和
	for(int i=1;i<=n;i++)
	{
		if(a[i].a+p<a[m].a)
		{
			ans[a[i].w]=-1;
			continue;
		}
		ll l=0,r=p,mid;
		while(l<r)//二分答案
		{
			mid=(l+r)>>1;
			if(ok(i,mid))r=mid;
			else l=mid+1;
		}
		ans[a[i].w]=l;
	}
	if(m==n)memset(ans,0,sizeof(ans));//特判
	for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
	cout<<'\n';
	return 0;
}
```

---

## 作者：shanxinhan (赞：2)

# 题解：AT_abc373_e [ABC373E] How to Win the Election

## 思路

在本文中，记 $K$ 为题目中的 $K- \sum_{i=1}^{N} A_i$。

对于每一个候选人 $i$，二分他获得的额外选票 $mid$，问题就转换为，**除了当前处理的候选人外，票数最大的 $M$ 个候选人在补上剩余票数 $K-mid$ 后，能否都大于  $A_{i}+mid$**？

可以发现，在按票数从小到大排序后，如果一个候选人的票数本来就大于 $A_{i}+mid$，他就不需要额外补票了。因此，我们只需要二分找到最后一个票数不足 $A_{i}+mid$ 的候选人，记他的下标为 $pos$,判断从第 $N-M+1$ 个候选人到他能否补票到 $A_{i}+mid$ 即可。也就是判断

$$\sum_{j=N-M+1}^{pos} A_{i}+mid-A_j \le K$$

注意，如果 $N=M$，直接输出 $N$ 个 $0$ 就行。~~不这样特判会错一个测试点的。~~

时间复杂度 $O(N\log_N\log_K)$。

## ~~简短的~~代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,k,a[N],b[N];
int sum[N];
bool check(int x,int mid){
	int pos=lower_bound(b+1,b+1+n,x+mid+1)-b-1;
	if(pos<n-m)return 0;
	return (x+mid+1)*(pos-n+m)-(sum[pos]-sum[n-m-1]-max(x,b[n-m]))>k-mid;
}
signed main(){
	cin>>n>>m>>k;
	if(n==m){
		for(int i=1;i<=n;i++)
			cout<<0<<' ';
		return 0;
	}
	for(int i=1;i<=n;i++)
		cin>>a[i],k-=a[i];
	memcpy(b,a,sizeof(a));
	sort(b+1,b+1+n);
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+b[i];
	for(int i=1;i<=n;i++){
		int l=0,r=k+1;
		while(l<r){
			int mid=(l+r)/2;
			if(check(a[i],mid))r=mid;
			else l=mid+1;
		}
		if(l<=k)cout<<l<<' ';
		else cout<<-1<<' ';
	}
	return 0;
}

---

## 作者：TainityAnle (赞：2)

AT_abc373_e

#### 题目描述

有 $N$ 个人选举，其中前 $M$ 名会入选，一共 $k$ 票，第 $i$ 个人已得了 $A_i$ 票。求第 $i$ 个人至少再得多少票就一定能入选，若不可能，输出 $-1$。

---

#### 思路

设剩余选票数 $k-\textstyle{\sum_{i=1}^{N}} A_i$ 为 $L$。

首先特判 $-1$ 的情况：如果把所有剩余选票都给第 $i$ 个人，第 $i$ 个人还是进不了前 $M$，就一定不行。  
接下来二分答案每个人所需的得票数，从 $0$ 到 $L$。这个过程是 $\Theta(\log k)$ 的，所以判断函数要求 $\Theta(\log N)$。一下是判断函数中的操作。

设当前二分到的 $mid$ 为 $x$，当前这个人加上 $x$ 选票后总票数为 $nw$。  
现在希望知道 $nw$ 在原数组中的排名，可以将 $A$ 数组用另一个数组 $B$ 存下来，将数组 $B$ 排序后使用 stl 库中自带的 upper_bound() 函数，查找第一个大于等于 $nw$ 的数。这个地方建议使用 upper_bound()，因为如果原数列中没有这个数，那么这个数要是加到序列中的排序应该等于第一个大于的数原来的排序。

---

## 作者：wei2013 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc373_e)
## 思路：
麻烦的二分套二分。

先看第一层二分的单调性，如果 $mid$ 越大（$mid$ 是指第 $i$ 个人多拿到的票数），那么所能排到前 $m$ 名的概率就越大，具有单调性。

判断二分是否正确的条件：考虑贪心，在最坏情况下，比此时获得票数后更小的 $m$ 个数按照与 $a_i+mid$ 的差值从小到大排序后的顺序每个都获得了 $a_i+mid-a_j+1$ 票，即设 $r$ 为第一个大于 $a_i+mid$ 的下标，则在最坏情况下的被超过所需票数，为：

$$\sum_{j=n-m+1}^{j<x}a_i+mid-a_j $$

如果超过了剩余票说明此时的 $mid$ 合法，否则不合法，加上一个前缀和优化，即可 $\mathcal{O(1)}$ 处理。

时间复杂度：$\mathcal{O(n\log{n}\log{k})}$。

## code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200005],b[200005],p[200005],n,m,k;
bool check(int id,int val){
	int rm=k-val,l=n-m+1,r=upper_bound(a+1,a+n+1,b[id]+val)-a-1;
	if(n-r>=m){
		return 0;
	}
	if(a[l]>b[id]){
		return (r-l+1)*(b[id]+val+1)-(p[r]-p[l-1])>rm;
	}
	return (r-l+1)*(b[id]+val+1)-(p[r]-p[l-2]-b[id])>rm;
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];
	}
	if(n==m){
		for(int i=1;i<=n;i++){
			cout<<0<<" ";
		}
		return 0;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		p[i]=p[i-1]+a[i];
	}
	k-=p[n];
	for(int i=1;i<=n;i++){
		int l=0,r=k,ans=1e18;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(i,mid)){
				r=mid-1;
				ans=mid;
			}else{
				l=mid+1;
			}
		}
		if(ans==1e18){
			cout<<-1<<" ";
		}else{
			cout<<ans<<" ";
		}
	}
	return 0;
}


```

---

## 作者：zhoumurui (赞：0)

### 题面展示

有 $N$ 名候选人（编号为 
$1,2,\dots,N$）参加选举。共有 
$K$ 张选票，其中部分选票已被统计。截至目前，候选人 
$i$ 获得了 $A_i$ 张选票。

计票结束后，候选人 $i$（$1 \le i \le N$）当选当且仅当得票数多于他们的候选人少于 $M$。可能有多名候选人当选。

请为每位候选人找出：他至少需要再获得多少选票才能保证当选。如果他不可能当选，输出 `-1`。

### 解题思路

建议评绿/蓝。

思路是对于每位候选人，对他还要获得的选票数量进行二分，`check(i,k)` 即为候选人 $i$ 在额外获得 $k$ 张选票后，是否能保证当选。单调性显然。

`check(i,k)` 的实现思路是尝试给除了候选人 $i$ 以外的 $M$ 名目前得票最多的候选人票，让他们超过候选人 $i$，让候选人 $i$ 无法当选。如果做不到，候选人 $i$ 必然当选。

实现方式是将候选人票数从大到小排序并计算前缀和，二分计算剩余票数能让多少个候选人超过候选人 $i$。即本题解做法是二分套二分。

### 核心代码展示

```cpp
struct node{
    int v,id,ans;
    bool operator <(const node b)const{
        return v>b.v;
    }
}a[200005];
bool cmp(node a,node b){
    return a.id<b.id;
}
int p[200005];//从小到大
int s[200005];//从大到小的前缀和
int last;//剩余票数
bool chk(int i,int mid,int ok,int to,int t){
    int have=s[mid]-s[ok]-(mid>=i?(s[i]-s[i-1]):0);
    int need=(mid-ok-(mid>=i?1:0))*to;
    return need-have<=t;
}
bool check(int i,int z){
    int v=a[i].v+z;
    int ok=n-(upper_bound(p+1,p+1+n,v)-p-1);
    int t=last-z;
    int l=ok,r=n,mid;
    while (l<r){
        mid=(l+r+1)/2;
        if (chk(i,mid,ok,v+1,t))l=mid;
        else r=mid-1;
    }
    //cout<<a[i].v<<" "<<z<<" "<<r<<endl;
    if (r>=i)return r-1<m;
    else return r<m;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin>>n>>m>>k;
    last=k;
    for (int i=1;i<=n;i++){
        cin>>a[i].v;
        a[i].id=i;
        last-=a[i].v;
    }
    sort(a+1,a+1+n);
    for (int i=1;i<=n;i++){
        s[i]=s[i-1]+a[i].v;
        p[n-i+1]=a[i].v;
    }
    for (int i=1;i<=n;i++){
        int l=0,r=last,mid;
        if (!check(i,last)){
            a[i].ans=-1;
        }
        else{
            while (l<r){
                mid=(l+r)/2;
                if (check(i,mid))r=mid;
                else l=mid+1;
            }
            a[i].ans=r;
        } 
    }
    sort(a+1,a+1+n,cmp);
    for (int i=1;i<=n;i++){
        cout<<a[i].ans<<" ";
    }
    return 0;
}

---

## 作者：WuMin4 (赞：0)

## [\[ABC373E\] How to Win the Election](https://atcoder.jp/contests/abc373/tasks/abc373_e)

## 思路

比较难调的二分。

将 $A$ 数组排序，很容易想到对于每个 $i$ 二分 $X$。检查 $X$ 是否成立可以贪心。一开始 $A_j>A_i+X$ 的人要先算进满足人数，剩下的人可以二分，对于第 $x\sim y$ 人要满足 $A_x,A_{x+1}\cdots A_y>A_i+X$ 所需的最小票数即为 $(y-x+1)\times(A_i+X+1)-\sum_{z=x}^y A_z$，可以前缀和优化，最后判断满足人数是否 $\le M$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,c[200005],ans[200005],b[200005];
struct node{
	int x,id;
}a[200005];
bool cmp(node x,node y){
	return x.x<y.x;
}
bool check(int x,int md){
	int ls=lower_bound(b+1,b+1+n,a[x].x+md+1)-b;
	int sy=m-(n-ls+1),syp=k-md;//sy为剩下的人，syp为剩下的票
	//减去本身大于x获得的票数的人
	if(sy<=0) return 0;
	int l=x+1,r=ls,ANS=0,mid;
	while(l<=r){
		mid=(l+r)/2;
		if((ls-mid)*(a[x].x+md+1)-(c[ls-1]-c[mid-1])<=syp)
			r=mid-1,ANS=mid;
		else
			l=mid+1;
	}
	if(ANS!=0)
		sy-=(ls-ANS),syp-=(ls-ANS)*(a[x].x+md+1)-(c[ls-1]-c[ANS-1]);
	else
		return 1;
	if(sy<=0) return 0;
	l=1,r=x-1,mid,ANS=x;
	while(l<=r){
		mid=(l+r)/2;
		if((x-mid)*(a[x].x+md+1)-(c[x-1]-c[mid-1])<=syp)
			r=mid-1,ANS=mid;
		else
			l=mid+1;
	}
	sy-=(x-ANS);
	if(sy<=0) return 0;
	//以i为分界线分两段二分
	return 1;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i].x,k-=a[i].x,a[i].id=i;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
		c[i]+=a[i].x,b[i]=a[i].x;
	for(int i=1;i<=n;i++)
		c[i]+=c[i-1];//处理前缀和
	for(int i=n;i>=1;i--){
		int l=0,r=k,mid,ANS=-1;
		while(l<=r){//二分额外获得的票
			mid=(l+r)/2;
			if(check(i,mid))
				r=mid-1,ANS=mid;
			else
				l=mid+1;
		}
		ans[a[i].id]=ANS;
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：under_the_time (赞：0)

## 题意

> 有 $n$ 个人和 $k$ 张选票，初始第 $i$ 个人已经有 $a_i$ 张选票（相当于现在还剩 $k-\sum a_i$ 张选票）。第 $i$ 个人最终晋级，当且仅当最终票数大于 $i$ 的票数的人的人数 $<m$。求每个人至少再获得多少选票后这个人一定晋级，或报告剩余选票不够。
>
> $1\le m\le n\le 2\times 10^5$，$1\le k\le 10^{12}$，$0\le a_i\le 10^{12}$。

## 解法

考虑对每个人进行二分答案。不妨先让 $k\gets k-\sum a_i$，即 $k$ 表示剩余的选票。对于第 $i$ 个人，假设我们二分到他还需 $x$ 票，那么场上还剩下 $k-x$ 票。显然对于所有满足 $a_j>a_i+x$ 的 $j$，他们不需要额外票数就可以算在比 $i$ 多的 $m$ 个人里，设这些人有 $m_0$ 个，那么至少还需 $m-m_0$ 个人票数比 $a_i+x$ 多；而对于这 $m_0$ 个人，最坏情况下他们没有获得更多的选票，把选票留给 $\le a_i+x$ 的人。观察到只要比 $a_i+x$ 大 $1$，即票数达到 $a_i+x+1$ 那么这个人就可以算在 $m$ 个人里，那我们贪心地选择**不**比 $a_i+x$ **大**的前 $m-m_0$ 个人，把 $k-x$ 张票分到他们身上使得这些人的票数达到 $a_i+x+1$；若 $k-x$ 不够分那么 $x$ 就合法，否则不合法。

我们考虑对 $a$ 从大到小排序并求出前缀和 $s$，这样我们就可以二分找比 $a_i+x$ 大的人和小于等于 $a_i+x$ 的人。这里有个细节：当 $a_i$，即他自己被视为 $m-m_0$ 个人中时我们不能取 $a_i$，再往后取一个舍去 $a_i$ 即可。代码挺难写的。时间复杂度 $O(n\log ^2n)$，因为要二分答案 + 二分查找。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 2e5 + 5;
ll k, sum[maxn], a[maxn], b[maxn]; int n, m;
int main() {
	scanf("%d %d %lld", &n, &m, &k);
	for (int i = 1; i <= n; i ++) 
		scanf("%lld", &a[i]), b[i] = a[i], k -= b[i];
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i ++) sum[i] = sum[i - 1] + b[i];
	for (int i = 1; i <= n; i ++) {
		ll l = 0, r = k, ans = -1;
		while (l <= r) {
			ll mid = (l + r) >> 1ll;
			int pos = upper_bound(b + 1, b + n + 1, a[i] + mid) - b; // 找到比 a[i]+mid 大的人，他们不需要更多选票就可以薄纱 i
			int x = m - (n - pos + 1); // 剩下还需要多少人达到 m 个人
			// cout << a[i] + mid << ' ' << x << '\n';
			if (x <= 0) { l = mid + 1; continue; } // 如果已经够了那么 mid 显然不够大
			int pos0 = pos - 1, L = pos0 - x;  // [pos-x-1,pos-1] 就是所有 <=a[i]+mid 中前 x 大的人
			if (L < 0) { ans = mid, r = mid - 1; continue; } // 若人数不够那么 mid 直接合法
			ll z = 0;
			if (b[L + 1] <= a[i] && a[i] <= b[pos0]) { // 特判一下 a[i] 在 [pos-x-1,pos-1] 中的情况
				if (L - 1 < 0) { ans = mid, r = mid - 1; continue; }
				L --, z = a[i];
			}
			ll s = x * (a[i] + mid + 1) - (sum[pos0] - sum[L] - z);
			if ((k - mid) < s) { ans = mid, r = mid - 1; continue; }
			l = mid + 1;
		} printf("%lld ", ans);
	}
	return 0;
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

[更好的体验。](https://www.cnblogs.com/Jh763878/p/18444228)

二分套二分。（感觉是一个很麻烦的做法。）

题目问的是让额外给的票最少，考虑二分答案。

设二分的答案为 $x$，该候选人原来的得票为 $v$，想要超过他至少要 $x+v+1$。

同时用前缀和维护区间和。

第一种情况为该候选人在前 $m$ 个人中，如下图所示。

![logo](https://cdn.luogu.com.cn/upload/image_hosting/lku327ed.png)

绿色箭头为被讨论的人，蓝色箭头表示 $x+v+1$ 在原数组中的位置，蓝勾的则是最劣情况下超过当前候选人的人。

可以计算出蓝勾位置原来的和与最劣下和的差，是否够分配。

蓝色箭头指向位置可以二分。（其实是我不会 lower_bound。）

第二种情况是当前候选人不在前 $m$ 位，那么无脑选前 $m$ 中小于 $x+v+1$ 的即可。

其实两种情况相差不大，但赛时代码又臭又长。

特别鸣谢：Daniel234 在赛时的口头鼓励，虽然毫无用处，但他与 *1300 斗智斗勇始终印象深刻。

（二）

AC 代码。

```cpp
// LUOGU_RID: 179341441
//2024-09-28 20:13:53
#include<bits/stdc++.h>
#define db double
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define mkp make_pair
#define pii pair<int,int>
#define int long long
using namespace std;
bool MBE;
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f; 
}
const int mxn=2e5+10;
int ans[mxn],s,n,m,k,sum[mxn];
struct node{
	int val,pos;
}a[mxn];
bool cmp(node x,node y){
	return x.val>y.val;
}
int query1(int pos,int x){
	int t=a[pos].val+x+1,p=k-x,ss;
	int l=1,r=m+1,ans=1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(a[mid].val<=t)ans=mid,r=mid-1;
		else l=mid+1;
	}
	if(ans==pos){
		ans++;
		ss=sum[m+1]-sum[ans-1];
		return (k-x)<t*(m-ans+2)-ss;
	}
	ss=sum[m+1]-sum[ans-1]-a[pos].val;
	return (k-x)<t*(m-ans+1)-ss;
}
int query2(int pos,int x){
	if(a[pos].val+x<a[m].val)return 0;
	int l=1,r=m,ans=1,p=a[pos].val+x+1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(a[mid].val<=p)ans=mid,r=mid-1;
		else l=mid+1;
	}
	int ss=sum[m]-sum[ans-1];
	return (k-x)<p*(m-ans+1)-ss;
}
signed main(){
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=read(),m=read(),k=read();
    if(n==1){
    	puts("0");
    	return 0;
    }
    if(m==n){
    	for(int i=1;i<=n;i++)
    		printf("0 ");
    	return 0;
    }
    for(int i=1;i<=n;i++){
    	a[i]=(node){read(),i};
    	s+=a[i].val;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
    	sum[i]=sum[i-1]+a[i].val;
    k-=s;
    for(int i=1;i<=m;i++){
    	int l=0,r=k,res=-1;
    	while(l<=r){
    		int mid=(l+r)>>1;
    		if(query1(i,mid))r=mid-1,res=mid;
    		else l=mid+1;
    	}
    	ans[a[i].pos]=res;
	}
	for(int i=m+1;i<=n;i++){
    	int l=0,r=k,res=-1;
    	while(l<=r){
    		int mid=(l+r)>>1;
    		if(query2(i,mid))r=mid-1,res=mid;
    		else l=mid+1;
    	}
    	ans[a[i].pos]=res;
	}
	for(int i=1;i<=n;i++)
		printf("%lld ",ans[i]);    
	bool MED;
    cerr<<(&MED-&MBE)/1048576.0<<" MB, "<<1000*clock()/CLOCKS_PER_SEC<<" ms\n";
    return 0;
}
```

---

## 作者：Wei_Han (赞：0)

一开始又读错题了，然后差点写红温。

这种题经典做法就是二分答案，我们需要对每一个人都这么做，那么此时的复杂度就已经 $O(n\log n)$ 了，所以我们的 check 不能再遍利每一个人求了，假设我们现在已经二分出给这个人分 $mid$ 票，那么剩下的票数就是 $k - mid$ 票，次数 $k$ 指剩余的总票数，对数组排序，我们先找出在这种情况下就已经大于 $a_x+mid$ 的人，排序后数组是单调的，所以可以直接二分。第二步我们找小于他的，但是可以用 $k-mid$ 票给他补上来的，此处我们可以记前缀和，然后向前二分找最远到哪里需要补的票是小于等于 $k-mid$ 的。但是这里需要减去我们当前选的这个人，记一下新位置，判断减掉就好了，具体实现看代码。

复杂度 $O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define pr putchar('\n')
#define pp putchar(' ')
#define pii pair<ll,ll>
#define pdi pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(register int i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(register int i = a ; i >= b ; -- i )
#define pb push_back
#define fi first
#define se second
//#pragma GCC optimize(2)
using namespace std;
 typedef long long ll;
//typedef int ll;
//typedef __int128 ll;
typedef double db;
const int N=1e6+5,M=2e6+1;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll n,m,k,x,y,sum,a[N],pre[N];
struct node{ll ai,id;}b[N];
inline bool cmp(node x,node y){return x.ai<y.ai;} 
inline bool check(ll midd,ll py,ll bnow){
	ll l=1,r=n;
	while(l<r){
		ll mid=l+r>>1;
		if(b[mid].ai<=midd) l=mid+1;
		else r=mid;
	}
	if(b[l].ai<=midd) l=n+1;
	ll len=n-l+1;
	ll now=l-1;
	l=1,r=now;
	while(l<r){
		ll mid=l+r>>1;
		if((midd+1)*(now-mid+1-(bnow<=now&&bnow>=mid))-(pre[now]-pre[mid-1]-b[bnow].ai*(bnow<=now&&bnow>=mid))<=py) r=mid;
		else l=mid+1;
	}
	if(midd+1-b[now].ai>py) l=now+1;
	len+=now-l+1-(bnow<=now&&bnow>=l);
	return len<m;
}
unordered_map<ll,ll> mp;
signed main(){
	read(n),read(m),read(k);
	fo(1,i,n) read(a[i]),b[i]={a[i],i},k-=a[i];sort(b+1,b+1+n,cmp);fo(1,i,n) pre[i]=pre[i-1]+b[i].ai,mp[b[i].id]=i;b[n+1].ai=INF,pre[n+1]=pre[n]+b[n+1].ai;
	fo(1,i,n){
		ll l=0,r=k;
		while(l<r){
			ll mid=l+r>>1;
			if(check(mid+a[i],k-mid,mp[i])) r=mid;
			else l=mid+1;
		}
		if(!check(k+a[i],0,b[i].id)) wr(-1),pp;
		else wr(l),pp;
	}	
	pr;
	return 0;
}

``````

---

## 作者：SkyWave (赞：0)

# [E](https://atcoder.jp/contests/abc373/tasks/abc373_e)

## 思路

对每一位候选者 $i$ 来说，给 $i$ 的票数 $X$ 越多自然越容易当选，所以我们自然考虑二分最小的 $X$。

考虑每个候选者 $i$，check 给 $i$ $mid$ 票时 $i$ 是否可以当选的时候实际上就是在 check 除了正在考虑的候选者 $i$，票数最多的 $M$ 位候选者的票数是否都可以利用剩余的票数（$K - \sum_{i=1}^{N} A_i - mid$）达到 $A_i + mid + 1$ 票，如果可以那么说明 $i$ 不能当选，否则 $i$ 可以当选。

先将 $A$ 升序排序后，朴素的 check 实现每次都需要扫 $M$ 位候选者计算，考虑全部 $n$ 位候选者时总复杂度是 $O(N \times (\log K) \times M)$，无法接受。

考虑优化 check，注意到 check 等价于在算这样一个式子：

$(\sum_{j=N-M}^{N} \max((A_i + mid + 1) - A_j, 0)) -  [i>n-m] \times max(A_i + mid + 1 - A_i, 0) - [i \leq n - m] \times max(A_i + mid + 1 - A_{n-m}, 0)$

因为 $A$ 被升序排序过了，所以注意到这个 $\sum_{j=N-M}^{N} \max((A_i + mid + 1) - A_j, 0)$ 存在有一条分界线使得分界线以前对 $\max((A_i + mid + 1) - A_j, 0)$ 的贡献都是 $A_i + mid + 1$，以后都是 $0$。这条分界线显然是可以在 $A$ 上二分找到的，设这条分界线前的下标在 $P$ 处，那么目标就变成了加速计算 $\sum_{j=N-M}^{P} A_i + mid + 1 - A_j$，这个是经典的，可以转换成 $(P - N - M + 1) \times (A_i + mid + 1) - \sum_{j=N-M}^{P}  A_j$，那么这个 $\sum_{j=N-M}^{P}  A_j$ 就能通过预处理前缀和求出了。

最终复杂度为 $O(N \times (\log K) \times (\log N))$，可以接受。

## 实现

有一些实现需要特判 $N=M$ 的情况，否则 check 会因为数组访问越界产生 UB。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 200000 + 1;

ll a[N], b[N], pre[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, m;;
	cin >> n >> m;
	if (n == m) {
		for (int i = 1; i <= n; ++i) {
			cout << "0" << " \n"[i == n];
		}
		return 0;
	}
	ll k;
	cin >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	memcpy(b + 1, a + 1, sizeof(ll) * n);
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; ++i) {
		pre[i] = pre[i - 1] + b[i];
	}
	ll rem = k - pre[n];
	
	auto check = [=](int x, ll mid) {
		ll tar = a[x] + mid + 1;
		if (lower_bound(b + 1, b + n + 1, a[x]) - b <= n - m) {
			int idx = (int)(lower_bound(b + n - m + 1, b + n + 1, tar) - b - 1);
			return 1ll * (idx - (n - m)) * tar - (pre[idx] - pre[n - m]) > rem - mid;
		}
		int idx = (int)(lower_bound(b + n - m, b + n + 1, tar) - b - 1);
		return 1ll * (idx - (n - m - 1)) * tar - (pre[idx] - pre[n - m - 1]) - max(tar - a[x], 0ll) > rem - mid;
	};
	
	for (int i = 1; i <= n; ++i) {
		ll l = 0, r = rem;
		while (l <= r) {
			ll mid = (l + r) >> 1;
			if (check(i, mid)) {
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		cout << (l > rem ? -1ll : l) << " \n"[i == n];
	}
	return 0;
}
```

---

## 作者：_WRYYY_ (赞：0)

[ABC373 题解合订版（A~F）。](https://www.cnblogs.com/wryyy-233/p/18439686)

考虑将 $\{A\}$ 按大小排序，可知只要加上剩余选票后大小能大于等于第 M 个的选票就一定有解，反之一定无解。

接着考虑如何最小化答案，我们令 $i$ 为当前参选人（排序后），$res$ 表示剩余选票数，$x$ 表示给 $i$ 用了多少选票，$len$ 表示加上选票后会被重新超过至少要多少人，$pos$ 表示第一个小于等于 $A_i+x$ 的人的位置，$sum_{l,r}=\sum_{i=l}^rA_i$（排序后）。

则 $x$ 合法当且仅当以下式子成立：

$$
\large sum_{pos-len+1,pos}+res-x<len(A_i+x+1)
$$

上式的含义表示 $len$ 个人的总选票和剩余可使用选票加起来不能满足使每个人都超过 $A_i+x$，也即第 $i$ 个参选人不会被 $len$ 个人超越，依然在前 $M$ 位当中。

至于为什么上式不成立时这样一定能分配成功，这是因为，这些人的选票都小于第 $i$ 个人的，所以总能找到一种分配方式。

显然知道 $x$ 就可以知道 $pos$，知道 $pos$ 就可以知道 $len$，所以可以对 $x$ 二分答案，再对 $pos$ 二分。

时间复杂度 $O(n\log_2^2n)$。

## Code：

这个人在写 E 的时候异常火大，所以代码很难看，仅供对拍用，不建议看。

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
#define ull unsigned long long
#define m_p make_pair
#define m_t make_tuple
#define N 200010
using namespace std;
using namespace __gnu_pbds;
ll a[N], sn[N];
pair<ll, int> p[N];
map<ll, ll> c;
int solve(int l, int r, ll w)
{
	int mid, ans = r;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (p[mid].first > w)
		{
			ans = mid - 1;
			r = mid - 1;
		}
		else
			l = mid + 1;
	}
	return ans;
}
signed main()
{
	// auto ___IN___ = freopen("dc.in", "r", stdin);
	// auto ___OUT___ = freopen("test.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n, m;
	ll k, sum = 0, les, aim, len, xx, l, r, mid;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		p[i] = m_p(a[i], i);
		sum += a[i];
		c[a[i]] = LONG_LONG_MAX;
	}
	if (m == n)
	{
		for (int i = 1; i <= n; i++)
			cout << "0 ";
		return 0;
	}
	les = k - sum;
	sort(p + 1, p + 1 + n);
	for (int i = 1; i <= n; i++)
		sn[i] = sn[i - 1] + p[i].first;
	aim = p[n - m + 1].first;

	ll ans = 0;
	for (int i = 1; i <= n - m; i++)
	{
		auto [val, id] = p[i];
		l = 0;
		r = les;
		ans = les + 1;
		while (l <= r)
		{
			mid = l + r >> 1;
			xx = solve(1, n, val + mid);
			len = xx - (n - m + 1) + 1;
			sum = sn[xx] - sn[n - m];
			if (xx >= (n - m + 1) && sum + les - mid - len * (val + mid) < len)
			{
				ans = mid;
				r = mid - 1;
			}
			else
				l = mid + 1;
		}
		c[val] = min(c[val], ans);
	}
	for (int i = n - m + 1; i <= n; i++)
	{
		auto [val, id] = p[i];
		l = 0;
		r = les;
		ans = les;
		while (l <= r)
		{
			mid = l + r >> 1;
			xx = solve(1, n, val + mid);
			len = xx - (n - m);
			sum = sn[xx] - sn[n - m - 1] - val;
			if (sum + les - mid - len * (val + mid) < len)
			{
				ans = mid;
				r = mid - 1;
			}
			else
				l = mid + 1;
		}
		c[val] = min(c[val], ans);
	}
	for (int i = 1; i <= n; i++)
		if (c[a[i]] > les)
			cout << "-1 ";
		else if (c[a[i]] < 0)
			cout << "0 ";
		else
			cout << c[a[i]] << " ";
	return 0;
}
```

---


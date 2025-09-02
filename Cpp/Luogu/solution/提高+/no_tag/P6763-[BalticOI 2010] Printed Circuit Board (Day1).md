# [BalticOI 2010] Printed Circuit Board (Day1)

## 题目描述

你现在有无数个平面直角坐标系，给定 $N$ 条线段，每条线段连接 $(X_{i,1},0)$ 和 $(X_{i,2},H)$（$H$ 是一个正数，不过并不给定，解题也并不需要），要求将这些线段放置在平面直角坐标系上，不能有任意两条线段相交。

求最小需要多少平面直角坐标系才能容纳这些线段。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，$1 \le N\le 10^5$，$0 \le X_{i,1},X_{i,2} \le 10^6$。所有的 $X_{i, 1}$ 互不相同，所有的 $X_{i,2}$ 互不相同。也即，没有两个端点在同一位置。

#### 说明

翻译自 [BalticOI 2010 Day1 C Printed Circuit Board](https://boi.cses.fi/files/boi2010_day1.pdf)。

## 样例 #1

### 输入

```
2
1 1
3 3```

### 输出

```
1```

## 样例 #2

### 输入

```
2
1 3
3 1```

### 输出

```
2```

# 题解

## 作者：Hoks (赞：2)

## 前言
[题目链接](https://www.luogu.com.cn/problem/P6763)，[个人博客内食用更佳](https://www.luogu.com.cn/blog/hhhgan/solution-p6763)。
## 思路分析
我们优先考虑两条线段不相交的条件是什么：

![](https://cdn.luogu.com.cn/upload/image_hosting/6ryjm5vm.png)

如图，可以得到是：
$$x_{i1}<x_{j1} and x_{i2}<x_{j2}$$

所以题目就被转化成了一个二维偏序问题。

首先考虑用按第一个坐标排序的方法去掉一维。

接着根据[ Dilworth 定理](https://baike.baidu.com/item/%E7%8B%84%E5%B0%94%E6%B2%83%E6%96%AF%E5%AE%9A%E7%90%86/18900593)可以把题目转化为一个求第二维的最长上升子序列的问题。

[~~不会 Dilworth 定理的戳这里看第二问。~~](https://www.luogu.com.cn/problem/P1020)
## 代码
```cpp
#include <bits/stdc++.h>
#define int	long long
using namespace std;
struct node{int x,y;}a[100010];
int n,dt,pos;
int q[100010];
static char buf[1000000],*paa=buf,*pd=buf;
#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
inline int read(void){
    int x(0),t(1);char fc(getchar());
    while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
    while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
    return x*t;
}
inline void print(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
bool cmp(node x,node y){return x.x<y.x;}
signed main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i].x=read(),a[i].y=read();
    sort(a+1,a+1+n,cmp);q[++dt]=a[1].y;
    for(int i=2;i<=n;i++)
        if(a[i].y<q[dt]) q[++dt]=a[i].y;
        else
        {
            int pos=dt,l=1,r=n;
            while(l<=r)
            {
                int mid=(l+r)>>1;
                if(a[i].y>=q[mid]) pos=min(pos,mid),r=mid-1;
                else l=mid+1;
            }
        q[pos]=a[i].y;
    }
    print(dt);
    return 0;
}
```


---

## 作者：JK_LOVER (赞：2)

## 题意
给你 $n$ 条线段，求问至少要多少个直角坐标系，才可以保证线段两两不相交。[$qwq$](https://www.luogu.com.cn/blog/xzc/solution-p6763)
## 分析
线段不相交的条件是什么？

- 当一条线段的两个端点都小于另一条线段的两个端点。
$$
X_{i1}<X_{j1} \ \&\& \ X_{i2}<X_{j2}
$$
那么这道题就转化为偏序问题。可以先对 $X_{1}$ 排序，这样就只需要考虑 $X_2$ 的偏序关系了。根据 $\text{Dilworth定理}$ 。直接做一个最长下降子序列就可以了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 101010;
int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
int n;
struct Node{int x,y;}s[N];
int q[N],top = 0;
bool cmp(Node a,Node b){
	return a.x < b.x;
}
int main()
{
	n = read();
	for(int i = 1;i <= n;i++) s[i].x = read(),s[i].y = read();
	sort(s+1,s+1+n,cmp);
	for(int i = 1;i <= n;i++)
	{
		if(!top || q[top] > s[i].y) q[++top] = s[i].y;
		else{
			int l = 1,r = top,pos = top;
			while(l<=r){
				int mid = l + r >> 1;
				if(s[i].y >= q[mid]){
					pos = min(pos,mid);
					r = mid-1;
				}
				else l = mid+1;
			}
			q[pos] = s[i].y;
		}
	}
	cout<<top<<endl;
	return 0;
}
```


---

## 作者：TemplateClass (赞：1)

考虑第 $i$ 条线段和第 $j$ 条线段相交的含义是什么，不难发现实际上就是：

$$X _ {i, 1} < X _ {j, 1} \text{ and } X _ {i, 2} < X _ {j, 2}$$

首先对第一维排序，这样就一定能满足第一个条件，然后我们按排序后的顺序加入平面直角坐标系中（如果不按顺序就不一定有 $X _ {i, 1} < X _ {j, 1}$ 了）。因此我们只需要保证每个平面直角坐标系上的线段都有 $X _ {i, 2} < X _ {j, 2}$，也就是每个平面直角坐标系上的线段的第二维按顺序来看都是上升的。

由于我们是按顺序加入的，所以先后顺序没变，于是我们不难发现每个平面直角坐标系的线段第二维在原排序过后的线段序列中都是一个上升子序列，于是问题就变为了如何划分这个序列成多个子序列。由于我们希望平面直角坐标系的数量最小，所以我们不难想到让每个子序列都是最长的，也就是最长上升子序列。

问题再次转化为将这个序列划分成尽可能少的最长上升子序列的个数，这个很典，使用 Dilworth 定理：对于任意有限偏序集，其最大反链中元素的数目必等于最小链划分中链的数目。对于这题说人话就是将这个序列划分成尽可能少的最长上升子序列的个数等于这个序列的最长不上升子序列的长度。

因此我们只需要求出排序后那个序列的第二维的最长不上升子序列的长度即可，这个同样很典，使用一个类似 P1020 的 $O(n \log n)$ 的 dp 即可完成，不会的跳转那题题解。

```cpp
#include<iostream>
#include<utility>
#include<algorithm>

typedef std::pair<int, int> pii;
constexpr int N = 1e5 + 5;

int n; pii x[N]; int dp[N], ans = 0;

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin >> n;
	for(int i = 1; i <= n; ++i) {
		std::cin >> x[i].first >> x[i].second;
	}
	std::sort(x + 1, x + n + 1);
	
	for(int i = 1; i <= n; ++i) {
		int l = 0, r = ans + 1;
		while(r - l > 1) {
			int mid = l + r >> 1;
			if(dp[mid] >= x[i].second) l = mid;
			else r = mid;
		}
		ans = std::max(ans, l + 1); dp[l + 1] = x[i].second;
	}
	std::cout << ans << "\n";
	
	return 0;
}
```

---

## 作者：fish_love_cat (赞：0)

蛤？蓝？

---

首先容易发现线段 $i,j$ 相交必须满足 $l_i>l_j,r_i<r_j$。

于是想到我们可以按照 $l$ 降序排序。

这样题目就转变成按顺序加入分组，并实时要求每个平面直角坐标系上的线满足 $r$ 降序排序。

注意到这个可以直接上一个 $O(n\log n)$ 的 DP，事实上就是 P1020 的第二问。

那么做完了，注意端点可能为 $0$。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct fish{
    int x,y;
}a[100005];
bool cmp(fish x,fish y){
    return x.x>y.x;
}
int dp[100005],ans;
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i].x>>a[i].y,a[i].x++,a[i].y++;
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        if(dp[ans]<a[i].y){
            ans++;
            dp[ans]=a[i].y;
            continue;
        }
        dp[lower_bound(dp+1,dp+1+ans,a[i].y)-dp]=a[i].y;
    }
    cout<<ans;
    return 0;
}
```

来做这题事实上是随机跳题跳出来的（）

---

## 作者：ADNAP (赞：0)

### Solution
首先两条线段相交的充要条件是 $(x_{1,1} < x_{2,1}) \operatorname{xor} (x_{1,2} < x_{2,2}) = true$。

这是一个二维偏序问题，用第一维排序，第二维用树状数组来维护即可，观察也可发现是求第二维的最长上升子序列。

我们将第一维从大到小排序。然后从前往后扫第二维，对于 $i$，$f_i = \max(f_j+1)$，其中 $x_{j,2} < x_{i,2}$ 且 $j < i$，然后再将 $f_i$ 塞到树状数组 $x_{i,2}$ 的位置即可。

### Code
```
#include <bits/stdc++.h>
using namespace std;
typedef int ll;
const ll N=1e5+1e2,D=1e6+1e2;
ll n,mxD;
struct Data
{
    ll x1,x2;
    bool operator < (const Data&P)const
    {
        return x1>P.x1;
    }
}a[N];
ll tr[D];
ll lowbit(ll x)
{
    return x&(-x);
}
void modify(ll x,ll v)
{
    for(ll i=x;i<=mxD;i+=lowbit(i))
        tr[i]=max(tr[i],v);
}
ll query(ll x)
{
    ll res=0;
    for(ll i=x;i;i-=lowbit(i))
        res=max(res,tr[i]);
    return res;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(ll i=1;i<=n;i++)
    {
        cin>>a[i].x1>>a[i].x2;
        a[i].x2++;
        mxD=max(mxD,a[i].x2);
    }
    sort(a+1,a+n+1);
    ll ans=0;
    for(ll i=1;i<=n;i++)
    {
        ll tmp=query(a[i].x2);
        ll res=tmp+1;
        ans=max(ans,res);
        modify(a[i].x2,res);
    }
    cout<<ans;
}
```

---

## 作者：serene_analysis (赞：0)

果然是没学明白，前几天刚学的 $\text{Dilworth}$ 定理根本想不起来。

---

简要题意：给出 $n$ 条线段，每条线段 $i$ 为 $(x_{i1},0)$ 到 $(x_{i2},H)$。**对于所有线段，这个 $H$ 都相同**。求最少需要的平面数量，使得将所有线段各放入某个平面后，所有平面内的线段两两不相交。

$1 \le n \le 10^5,1 \le x \le 10^6$。

分析： $\text{Dilworth}$ 定理，简单 DP。

考虑什么时候不相交。简单思考发现两条线段 $i,j(x_{i1}<x_{j1})$ 不相交当且仅当 $x_{i2}<x_{j2}$。将线段按照 $x_1$ 排序，那么只需要考虑 $x_2$。

根据题目，我们要求的是最少的满足条件的平面个数。观察到 $<$ 是一个偏序关系，可以使用 $\text{Dilworth}$ 定理 _最小链覆盖数等于最长反链的长度_ ，将问题转化为求最长的序列 $a_1,a_2,\cdots,a_k$ 使得对于 $\forall i \in [2,k]$ 有 $a_{i-1}>a_i$，也即最长下降子序列长度。

[JK_LOVER](https://www.luogu.com.cn/user/227824) 使用的是二分法优化，这里给出线段树优化 DP 的代码。

```cpp
#include<algorithm>
#include<assert.h>
#include<cstdio>
typedef long long ll;
const int maxn=1e5+5;
const int maxa=1e6+5;
struct xds{
	struct node{
		int l;
		int r;
		int mx;
	}tree[maxa*4];
	void build(int i,int l,int r){
		tree[i].l=l;
		tree[i].r=r;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(i*2,l,mid);
		build(i*2+1,mid+1,r);
		return;
	}
	void modify(int i,int wz,int k){
		if(tree[i].l==tree[i].r){
			tree[i].mx=k;
			return;
		}
		if(tree[i*2].r>=wz)modify(i*2,wz,k);
		else modify(i*2+1,wz,k);
		tree[i].mx=std::max(tree[i*2].mx,tree[i*2+1].mx);
		return;
	}
	int getmax(int i,int l,int r){
		if(tree[i].l>=l&&tree[i].r<=r)return tree[i].mx;
		int mx=0;
		if(tree[i*2].r>=l)mx=std::max(mx,getmax(i*2,l,r));
		if(tree[i*2+1].l<=r)mx=std::max(mx,getmax(i*2+1,l,r));
		return mx;
	}
}sgt;
struct line{
	int stx;
	int enx;
}lin[maxn];
int n;
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&lin[i].stx,&lin[i].enx);
		lin[i].stx+=2;
		lin[i].enx+=2;
	}
	std::sort(lin+1,lin+n+1,[](line now,line oth){
		return now.stx<oth.stx;});
	sgt.build(1,1,maxa-2);
	for(int i=1;i<=n;i++){
//		printf("getmax:%d,%d\n",lin[i].enx+1,maxa-2);
		int res=sgt.getmax(1,lin[i].enx+1,maxa-2)+1;
//		printf("res=%d\n",res);
		sgt.modify(1,lin[i].enx,res);
	}
	printf("%d",sgt.tree[1].mx);
	return 0;
}
/*
4
1 6
2 2
3 3
4 4
*/
/*
5
3 0
2 2
4 4
1 3
0 1
*/
```

希望这篇题解能够帮助到你！

---


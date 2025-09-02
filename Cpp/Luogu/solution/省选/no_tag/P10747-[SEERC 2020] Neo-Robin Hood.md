# [SEERC 2020] Neo-Robin Hood

## 题目描述

你是一个大盗，镇上一共有 $n$ 户人家，对于每户人家 $i$，你在如下的选择里选一样。

- 盗窃他的 $m_i$ 元钱，他会对你起仇恨。

- 给他 $p_i$ 元钱，他会让你盗窃的一个人取消对你的仇恨。

- 什么也不做。

初始时你没有钱，你想知道，在没人对你有仇恨且你手中的钱非负的情况下，你最多能盗窃多少户人家。

注：你可以按任意顺序依次访问每户人家。

## 样例 #1

### 输入

```
5
2 3 4 5 6
1 2 3 4 5```

### 输出

```
2```

## 样例 #2

### 输入

```
4
1 2 4 2
5 6 9 7
```

### 输出

```
0```

## 样例 #3

### 输入

```
4
9 19 6 5
20 3 16 19
```

### 输出

```
1```

# 题解

## 作者：oMin0 (赞：5)

建议降蓝。

## 分析

首先警示后人，题目并不要求你按照 $1\sim n$ 的顺序依次操作，你可以按任意顺序做选择，感觉它没说明白。

考虑这样一件事情，假如我们盗窃了 $i$，然后用 $j$ 取消仇恨，那么最优策略必然满足 $m_i-p_j\geq m_j-p_i$，否则可以交换对这两人执行的操作。

这意味着按照 $m_i+p_i$ 排序后，被盗窃的人家和被贿赂的人家存在一个分界点。我们枚举分界点，那然后一定是对前缀 $m_i$ 的前 $k$ 大盗窃，并给后缀 $p_i$ 的前 $k$ 小送钱。用二分+主席树即可做到 $O(n\log^2 n)$，不过更好写的办法是先二分答案 $ans$，然后用堆维护固定 $k$ 的前 $k$ 小信息，具体实现见代码。

## 代码

```cpp
/*
  author: honglan0301
  Sexy_goodier _ xiaoqing
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
using namespace std;
#define int long long
#define endl "\n"

int n,m[100005],p[100005],bh[100005];
bool cmp(int x,int y) {return m[x]+p[x]>m[y]+p[y];}

int sumq[100005],sumh[100005];
bool ck(int k)
{
	priority_queue <int,vector<int>,greater<int>> Q;
	int ns=0;
	for(int i=1;i<=n;i++)
	{
		if(Q.size()<k) Q.push(m[bh[i]]),ns+=m[bh[i]];
		else 
		{
			int nr=Q.top(); ns-=nr; Q.pop(); ns+=max(nr,m[bh[i]]); Q.push(max(nr,m[bh[i]]));
		}
		sumq[i]=ns;
	//	cout<<i<<" "<<sumq[i]<<endl;
	}
	ns=0; while(!Q.empty()) Q.pop();
	for(int i=n;i>=1;i--)
	{
		if(Q.size()<k) Q.push(p[bh[i]]),ns+=p[bh[i]];
		else 
		{
			int nr=Q.top(); ns-=nr; Q.pop(); ns+=max(nr,p[bh[i]]); Q.push(max(nr,p[bh[i]]));
		}
		sumh[i]=-ns;
		//cout<<i<<" "<<sumh[i]<<endl;
	}
	for(int i=k;i+k<=n;i++) if(sumq[i]>=sumh[i+1]) return 1; return 0;
}

signed main()
{
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>m[i];
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=n;i++) bh[i]=i; sort(bh+1,bh+n+1,cmp);
	for(int i=1;i<=n;i++) p[i]=-p[i];
	int l=1,r=n/2;
	while(l<=r) {int mid=(l+r)>>1; if(ck(mid)) l=mid+1; else r=mid-1;} 
	cout<<r<<endl;
}
```

---

## 作者：porse114514 (赞：3)

# [P10747 [SEERC2020] Neo-Robin Hood](https://www.luogu.com.cn/problem/P10747) 题解
楼下的题解第一遍看理解了好一会，我来写一份更详细的。

## 正解：二分加排序

1. 因为每一户人家只能进行一次操作，所以最多也只能偷 $\lfloor n/2 \rfloor$ 户人家（因为最后不能有仇恨）。

2. 由于题目没有说按顺序操作，所以可以考虑这样一件事：如果对 $i,\,j$ 进行操作，那么 $m_i-p_j \geq m_j-p_i$，要不然的话还不如反过来，所以我们移一下项，得：$m_i+p_i \geq m_j+p_j$，所以我们就可以开一个结构体，按照 $m_i+p_i$ 排序。

3. 如果不能偷 $i$ 户人家，那么一定不能偷大于 $i$ 户人；如果能偷 $i$ 户人家，那么一定能偷小于 $i$ 户人，所以我们考虑从 $0$ 到 $\lfloor n/2 \rfloor$ 二分。

### 关于为什么二分
不知道有没有人和我当时一样，不理解为什么要二分，这里我就说一下。

我们并不是按照排序一个一个操作，而是寻找 $mid$ 前的 $m_i$ 的最大值与 $mid$ 后的 $p_i$ 的最小值，这样才能保证最优，所以需要二分。

关于寻找 $mid$ 前的 $m_i$ 的最大值与 $mid$ 后的 $p_i$ 的最小值，用一个优先队列（dalao好像都说堆）就可以了。

### 关于 check 小细节
代码中的 check 部分中可以全部入队再扫一下，但看了楼下大佬的写法之后，采用了前 $k$ 个入队，其他替换的方法。这种方法的正确性是有保障的，因为 $k$ 一定不会大于 $\lfloor n/2 \rfloor$（具体原因见前文），所以就算前 $k$ 个都没有贡献，后面也能换回来。

而且这样代码会快一些。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//不开long long见祖宗
const int maxn = 100010;
struct family{//结构体
	int m,p;
}f[maxn];
int n,m[maxn],p[maxn],l,r,mid,t,mm,money1[maxn],money2[maxn];
bool cmp(family x,family y)
{
	return x.m + x.p > y.m + y.p;
}
bool check(int k)
{
	priority_queue<int,vector<int>,greater<int> > q;//大根堆
	t = 0;
	for(int i = 1;i <= n;i++)
	{
		if(q.size() < k) 
		{
			q.push(f[i].m);//入队
			t += f[i].m;
		}
		else 
		{
			mm = q.top();q.pop();//替换更大的m
			t -= mm;
			t += max(mm,f[i].m);
			q.push(max(mm,f[i].m));
		}
		money1[i] = t;//此时的钱
	}
	priority_queue<int> qq;//小根堆
	t = 0;
	for(int i = n;i >= 1;i--)
	{
		if(qq.size() < k)
		{
			qq.push(f[i].p);//入队
			t += f[i].p;
		}
		else
		{
			mm = qq.top();qq.pop();//替换更小的p
			t -= mm;
			t += min(mm,f[i].p);
			qq.push(min(mm,f[i].p));
		}
		money2[i] = t;//扣的钱
	}
	for(int i = k;i + k <= n;i++)
	{
		if(money1[i] >= money2[i + 1]) return 1;//如果花的钱没有偷的多，就return 1
	}
	return 0;
}
signed main()
{
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		cin >> f[i].m;
	}
	for(int i = 1;i <= n;i++)
	{
		cin >> f[i].p;
	}//初始化
	sort(f + 1,f + 1 + n,cmp);//排序
	l = 1,r = n / 2;
	while(l <= r)//二分
	{
		mid = (l + r) >> 1;
		if(check(mid)) l = mid + 1;
		else r = mid - 1;
	}
	cout << r << '\n';
	return 0;//又切一道紫
}
```

---

## 作者：xxseven (赞：2)

很好的贪心题目。

首先考虑两个人 $i,j$。如果你偷了 $i$ 的钱，去找 $j$ 赎罪，那么赚的钱是 $m_i-p_j$。如果调换顺序，那么就能赚到 $m_j-p_i$。

当偷 $i$ 不劣时有 $m_i-p_j \ge m_j-p_i$，移项则有 $m_i+p_i \ge m_j+p_j$。

这启示了我们将所有人按 $m+p$ 升序排序，这样**一定存在一个分界点**，分界点之前的人不会被偷，分界点之后的人不会被给钱。

显然答案具有单调性，那么我们二分答案 $k$，用堆对于原序列的每个**后缀**维护前 $k$ 大 $m$ 的和，对每个**前缀**维护前 $k$ 小 $p$ 的和，之后枚举分界点，如果存在一个分界点使得偷的钱不比送的钱少，那么答案 $k$ 合法。

二分的下界为 $0$，上界为 $\lfloor\frac{n}{2}\rfloor$，单次 check 的复杂度为 $O(n \log n)$，因此总复杂度为 $O(n \log ^2 n)$，可以通过此题。

下面是~~几乎是最劣解~~的代码：


```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e5+6;
struct node{
	int m,p;
	bool operator < (const node &b) const{
		return m+p<b.m+b.p; 
	}
}f[N];
int n,a[N],b[N];
//a[i]:后缀i个人能偷的钱 b[i]：前缀i个人需要花的钱 
bool check(int k){
	priority_queue<int,vector<int>,greater<int> > qa;
	priority_queue<int> qb;
	int now=0;
	for(int i=n;i>=1;--i){
		qa.push(f[i].m); now+=f[i].m;
		if(qa.size()>k) {
			now-=qa.top(); qa.pop();
		}
		a[i]=now;
	}	
	now=0;
	for(int i=1;i<=n;++i){
		qb.push(f[i].p); now+=f[i].p;
		if(qb.size()>k) {
			now-=qb.top(); qb.pop();
		}
		b[i]=now;
	}
	for(int i=k;i+k<=n;++i){ //枚举分界点 
		if(b[i]<=a[i+1]) return true;
	}
	return false;
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;++i) cin>>f[i].m;
	for(int i=1;i<=n;++i) cin>>f[i].p;
	sort(f+1,f+n+1);
	int L=1,R=n/2,ans=0;
	while(L<=R){
		int mid=(L+R>>1);
		if(check(mid)) L=mid+1,ans=mid;
		else R=mid-1;
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：xiaoliebao1115 (赞：0)

水紫石锤。

首先要读对题目，我读错的不太一样，给 $p_i$ 元钱，他会**让一个人**取消仇恨，还要注意的是每户人家只会有**一次**操作，还有题目求的是最多盗窃多少户人家，而不是能获得最多的钱数。我这个小傻子读错的有亿点多。

如果我用 $p_j$ 抵消 $m_i$ 那么贡献是 $m_i-p_j$，如果反着来就是 $m_j-p_i$，那么我们肯定取贡献较大的选。因为获得更多的钱，有利于偷更多的人。

所以移项之后就是 $m_j+p_j\le m_i+p_i$，我们按照 $m_i+p_i$ 的大小从小到大排序即可，那么一定是靠后的被靠前的取消仇恨。

然后我们用二分就可以求得答案，二分偷几个人，假设偷了 $x$ 个人。然后枚举一个分界点，从分界点后去偷，分界点前去取消仇恨。

那么我们在分界点前选择最小的 $x$ 个 $p_i$，后面选最大的 $x$ 个 $m_i$ 就行了，可以用堆维护。

代码还是放一下吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int nn=1e5+5,mzhxi=1e15;
int n,ans,a[nn];
struct node{
	int m,p;
};
node x[nn];
inline bool cmp(node l1,node l2){
	return l1.m+l1.p<l2.m+l2.p;
}
inline bool check(int k){
	priority_queue<int> q;
	int s=0;
	for(int i=1;i<=n;i++){
		if(q.size()<k){
			q.push(x[i].p);
			s+=x[i].p;
		}
		else if(q.top()>x[i].p){
			s-=q.top();
			q.pop();
			q.push(x[i].p);
			s+=x[i].p;
		}
		a[i]=s;
		if(q.size()<k) a[i]=mzhxi;
	}
	s=0;
	while(!q.empty()) q.pop();
	for(int i=n;i>=1;i--){
		if(q.size()<k){
			q.push(-x[i].m);
			s+=x[i].m;
		}
		else if(-q.top()<x[i].m){
			s-=(-q.top());
			q.pop();
			q.push(-x[i].m);
			s+=x[i].m;
		}
		if(q.size()==k){
			if(s>=a[i-1]&&i>=2) return 1;
		}
	}
	return 0;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i].m;
	for(int i=1;i<=n;i++) cin>>x[i].p;
	sort(x+1,x+n+1,cmp);
	int l=1,r=n/2;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1,ans=mid;
		else r=mid-1;
	}
	cout<<ans<<endl;
	return 0;
}
```
最优解第三，未加快读。

---

## 作者：Petit_Souris (赞：0)

一拍脑袋题。

首先要读对题！操作的顺序是任意的。~~点名【数据删除】~~

假设我们偷了 $i$ 的钱，并用 $j$ 抵消仇恨，那么会贡献 $m_i-p_j$ 块钱（可能是负数）。如果我们交换 $i,j$ 的操作，会贡献 $m_j-p_i$。那么我们发现当 $m_i-p_j<m_j-p_i$ 的时候，应当交换 $i,j$ 的操作，这样保持偷到的人家数量相同且剩下的钱更多。

由这个调整，发现我们一定会将所有人家 $m_i+p_i$ 从小到大排序，从一个分界点分开，在前缀中选择 $p_i$ 前 $k$ 小的用来取消仇恨，在后缀中选择 $m_i$ 前 $k$ 大的偷窃（$k$ 是自己选择的，即为答案）。容易发现答案具有单调性，所有可以二分 $k$，现在问题变为求出前缀 / 后缀 $k$ 大 / 小，直接对顶堆即可。时间复杂度 $\mathcal O(n\log^2n)$。

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
const ll N=2e5+9;
ll n,a[N],b[N],id[N],pre[N],suf[N];
bool chk(ll mid){
    priority_queue<ll,vector<ll>,greater<ll> >q1;
    ll sum=0;
    rep(j,1,n){
        ll i=id[j];
        if((ll)q1.size()<mid)sum+=a[i],q1.push(a[i]);
        else{
            ll v=q1.top();
            if(v<a[i])sum+=a[i]-v,q1.pop(),q1.push(a[i]);
        }
        pre[j]=sum;
    }
    priority_queue<ll>q2;
    sum=0;
    per(j,n,1){
        ll i=id[j];
        if((ll)q2.size()<mid)sum+=b[i],q2.push(b[i]);
        else{
            ll v=q2.top();
            if(v>b[i])sum+=b[i]-v,q2.pop(),q2.push(b[i]);
        }
        suf[j]=sum;
    }
    rep(i,1,n){
        if(i>=mid&&n-i>=mid){
            if(pre[i]-suf[i+1]>=0)return 1;
        }
    }
    return 0;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read();
    rep(i,1,n)a[i]=read();
    rep(i,1,n)b[i]=read();
    iota(id+1,id+n+1,1);
    sort(id+1,id+n+1,[&](ll x,ll y){
        return a[x]+b[x]>a[y]+b[y];
    });
    ll l=1,r=n/2,ans=0;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(chk(mid))ans=mid,l=mid+1;
        else r=mid-1;
    }
    write(ans);
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---


# Max GEQ Sum

## 题目描述

现在你有一个由 $n$ 个整数组成的数组 $a$，$(i,j)$ 满足条件当且仅当 $\max (a_i,a_{i+1},\cdots,a_j)\ge a_i+a_{i+1}+\cdots+a_j$，其中 $1\le i\le j\le n$。问是否所有 $(i,j)$ 都满足要求。

## 样例 #1

### 输入

```
3
4
-1 1 -1 2
5
-1 2 -3 2 -1
3
2 3 -1```

### 输出

```
YES
YES
NO```

# 题解

## 作者：2020HZ06 (赞：18)

目前这题的题解均使用了时间复杂度为 $O(n \log n)$ 的 ST 表或线段树之类的解法，其实我们可以用单调栈做到 $O(n)$。

我们首先要找出每个数作为最大值的区间。显然，我们只要把区间分成左右两段，分别进行单调栈即可。

然后，我们要在每个数的左右两端分别求出它延伸出去能得到的最大和（不包含这个数），如果左右两端的最大和中有一个大于 $0$ ，那么答案显然是 NO。

这时我们发现，单调栈里的任何一个元素满足：**它向左/右延伸的最大和一定小于等于零**。为什么呢？因为它既然被放入栈中，就说明它一定是一个满足要求的元素（不然直接 break 掉就行了）。因此，我们只需在弹栈的时候判断当前元素延伸到栈顶元素的这一段区间和是否大于零即可（如果把栈顶元素左/右的不在栈中的元素加进来值显然不会增大）。

对于求区间和，我们可以预处理出前缀和与后缀和。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
long long a[200005],sumq[200005],sumh[200005];
bool b;
struct node
{
	long long val;
	int wz;
};
stack<node>s;
int main()
{
	long long max_;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		sumq[0]=0;
		for(int i=1;i<=n;i++) sumq[i]=sumq[i-1]+a[i];//前缀和
		sumh[n+1]=0;
		for(int i=n;i>=1;i--) sumh[i]=sumh[i+1]+a[i];//后缀和	
		b=0;
		while(!s.empty()) s.pop();
		for(int i=1;i<=n;i++)//从左向右单调栈
		{
			max_=0;
			while(!s.empty()&&s.top().val<=a[i])
			{
				max_=max(max_,sumq[i-1]-sumq[s.top().wz-1]);//判断是否满足条件
				s.pop();
			}
			if(max_>0)
			{
				b=1;
				break;
			} 
			s.push(node{a[i],i});
		}
		while(!s.empty()) s.pop();
		for(int i=n;i>=1;i--)//从右向左单调栈
		{
			max_=0;
			while(!s.empty()&&s.top().val<=a[i])
			{
				max_=max(max_,sumh[i+1]-sumh[s.top().wz+1]);
				s.pop();
			}
			if(max_>0)
			{
				b=1;
				break;
			} 
			s.push(node{a[i],i});
		}
		if(b) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```


---

## 作者：AmamiyaYuuko (赞：15)

看到题解区线段树横行，给一个不用码线段树的做法。

首先可以求出 $a_i$ 作为最大值的区间 $[l_i, r_i]$，这个可以用单调栈在 $O(n)$ 的时间里求出。

接下来只需要求 $[l_i, r_i]$ 中跨越了 $i$ 的最大子段和。用线段树是容易做的，但是 ST 表更好写。具体来说，考虑 $a_i$ 的前缀和 $pre_i$ 和后缀和 $suf_i$，用 ST 表维护 $pre_i$ 和 $suf_i$ 的区间最大值，那么 $[l_i, r_i]$ 中跨越了 $i$ 的最大子段和就是 $\max \limits_{i \le r \le r_i} pre_r - pre_{i - 1} + \max \limits_{l_i \le l \le i} suf_i - suf_{i + 1} - a_i$。如果这个数大于 $a_i$，就找到了一个不合法的区间。

时间复杂度 $O(n \log n)$。

---

## 作者：lingfunny (赞：12)

## CF1691D [link](https://codeforces.com/contest/1691/problem/D)

~~[Rd795 题解](https://280800.blog.luogu.org/codecraft-22-and-codeforces-round-795-div-2-post)滞销，帮帮我（误~~

首先对于这个式子，不难注意到左边的 $\max$ 只有 $O(n)$ 种取值，所以想到枚举最大值是一件很自然的事。

那么可以变成枚举一个最大值 $(\mathrm{pos}, v)$，然后记 $\mathrm{minL}$ 和 $\mathrm{maxR}$ 为它能向左向右最长能延申到的地方。

经典把 $\sum_{i=L}^{R}a_i$ 拆成前缀和做，变成 $s_R-s_{L-1}$，式子右边由「和 $L,R$ 有关」变成「和 $L$ 有关」和「和 $R$ 有关」两部分，可以直接单独对 $L$ 和 $R$ 考虑。

问题变成在 $[\mathrm{minL}-1,\mathrm{pos})$ 中找一个 $s$ 最小的，在 $[\mathrm{pos}, \mathrm{maxR}]$ 中找一个 $s$ 最大的，这样能使 $\mathrm{Sum}$ 尽可能大，换句话说使条件尽可能不成立。关于最大最小 st 表就可以完美解决。

问题变成如何对于一个 $(\mathrm{pos}, v)$ 找 $\mathrm{minL}$ 和 $\mathrm{maxR}$，是个经典问题。

可以考虑把这 $n$ 个数用链表将相邻的两个数连在一起，然后从小到大枚举最大值，每次枚举完一个值，就把这个值删去，更新链表。

这样每个数在链表上的左右的数就是第一个大于（等于）它的值了，因为比它小都删掉了，换句话说它们直接确定了 $\mathrm{minL}-1$ 和 $\mathrm{maxR}+1$。

关于一个小细节：如果两个数值相等的时候，枚举的时候是有序的，不能保证 $\mathrm{minL}$ 和 $\mathrm{maxR}$ 是严格大于自己的，换句话说此时其实还可以再往左右延申（因为是左右可能是等于自己的，等于的话就可以再延申）。但这并不会影响答案，因为一段区间如果能成为答案，它一定会在某次枚举的时候被统计到。~~为什么？留作思考题吧。~~

~~在码量上我已经赢太多了~~

```cpp
// Problem: D. Max GEQ Sum
// From: Codeforces - CodeCraft-22 and Codeforces Round #795 (Div. 2)
// URL: https://codeforces.com/contest/1691/problem/D
// Time: 2022-05-31 22:35
// Author: lingfunny

#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int mxn = 2e5+10;

int n, a[mxn], tot, pos[mxn], lg[mxn], p[mxn], L[mxn], R[mxn];
LL s[mxn], mis[20][mxn], mxs[20][mxn];
inline LL Qmi(int L, int R) {
	int k = lg[R-L+1];
	return min(mis[k][L], mis[k][R-(1<<k)+1]);
}
inline LL Qmx(int L, int R) {
	int k = lg[R-L+1];
	return max(mxs[k][L], mxs[k][R-(1<<k)+1]);
}

inline void solve() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", a+i), s[i] = s[i-1] + a[i], p[i] = i, L[i] = i-1, R[i] = i+1;
	for(int i = 1; i <= n; ++i) mis[0][i] = s[i-1];
	for(int i = 1; i <= n; ++i) mxs[0][i] = s[i];
	for(int i = 1; i <= lg[n]; ++i)
	for(int j = 1; j <= n - (1<<i) + 1; ++j)
	mis[i][j] = min(mis[i-1][j], mis[i-1][j+(1<<(i-1))]),
	mxs[i][j] = max(mxs[i-1][j], mxs[i-1][j+(1<<(i-1))]);
	sort(p+1, p+n+1, [&](int x, int y) { return a[x] < a[y]; });
	for(int i = 1; i <= n; ++i) {
		int u = p[i];
		R[L[u]] = R[u], L[R[u]] = L[u];
		if(a[u] < Qmx(u, R[u]-1) - Qmi(L[u]+1, u)) return puts("NO"), void();
	}
	puts("YES");
}

int main() {
	lg[0] = -1;
	for(int i = 1; i < mxn; ++i) lg[i] = lg[i>>1] + 1;
	int tt;
	scanf("%d", &tt);
	while(tt--) solve();
}
```



---

## 作者：jasonliujiahua (赞：2)

# CF1691D Max GEQ Sum


## 题意简述：

给定数列 $a_1,a_2,\cdots,a_n$，判断该数列是否满足条件：
$$\forall 1\le i\le j\le n,$$
$$\max_{k=i}^{j} a_k \ge \sum_{k=i}^{j} a_k$$


## 题目分析：
### Step 1：
对于“所有区间最值”的问题（如 [CF817D](https://www.luogu.com.cn/problem/CF817D) )，有一个很套路的做法:用单调栈维护每个值作为最大值所管的区间，即：左边最近的比当前数大的数的位置到右边最近的比当前数大的数的位置。所以只需开一个单调递减的栈，正着扫一遍找出左边最后一个比当前数大的数，然后倒着扫一遍找出右边的。

### Step 2：
设第 $i$ 个数管的区间为 $[l[i],r[i]]$。
当我们找到当前数作为最大值的区间时，$i,j$ 的范围与 $\max_{k=i}^{j} a_k$ 已经确定：
$$l[x] \le i \le x \le j \le r[x]$$
$$ \max_{k=i}^{j} a_k=a_x$$
其中 $x$ 为当前枚举到的数。剩下的任务就是要处理
$$\sum_{k=i}^{j} a_k$$
了。显然要使所有 $(i,j)$,$\max_{k=i}^{j} a_k \ge \sum_{k=i}^{j} a_k$ 都成立，只需 $\sum_{k=i}^{j} a_k$ 的最大值小于等于当前数即可。而一段区间 $[l,r]$ 可以看做前缀和相减：$sum[r]-sum[l-1]$，因此我们的任务变成了维护
$$sum[j]-sum[i-1]$$
的最大值。为了让上式取最大值，$sum[j]$ 应取最大值，而 $sum[i-1]$ 则要取最小值。
如果设
$$\operatorname{MAX}=\max_{k=i}^{r[i]} sum[i]$$
$$\operatorname{MIN}=\min_{k=l[i]-1}^{i-1} sum[i]$$
$\sum_{k=i}^{j} a_k$ 的最大值就是 $\operatorname{MAX}-\operatorname{MIN}$。
$\operatorname{MAX}$ 和 $\operatorname{MIN}$ 显然是一段区间的前缀和 $\operatorname{sum}$ 数组的最大/小值，因此考虑用 $\operatorname{ST}$ 表维护。


最后说一句：这题记得开long long。


## 参考代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=2e5+10;
ll t,n,nn,a[maxn],sum[maxn],st1[maxn][50],st2[maxn][50];
ll s[maxn],top,l[maxn],r[maxn];
/*
st1维护前缀和的区间最大值，st2则维护最小值。
s是单调栈，top为栈顶。
[l[i],r[i]]为以a[i]作为最大值的最大区间。
*/
void init()
{
    cin>>n;
    nn=log2(n)+1;
    for(int j=1;j<=nn;j++)
        for(int i=0;i<=n;i++)
            st2[i][j]=1e9;
    for(int i=1;i<=n;i++) 
    {
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];//前缀和
    }
    for(int i=0;i<=n;i++)
        st1[i][0]=st2[i][0]=sum[i];
}
ll query1(int x,int y)//查询sum的区间最大值
{
    int z=log2(y-x+1);
    return max(st1[x][z],st1[y-(1<<z)+1][z]);
}
ll query2(int x,int y)//查询sum的区间最小值
{
    int z=log2(y-x+1);
    return min(st2[x][z],st2[y-(1<<z)+1][z]);
}
void ST()
{
    for(int j=1;j<=nn;j++)
    {
        for(int i=0;i+(1<<(j-1))<=n;i++)
        {
            st1[i][j]=max(st1[i][j-1],st1[i+(1<<(j-1))][j-1]);
            st2[i][j]=min(st2[i][j-1],st2[i+(1<<(j-1))][j-1]);
        }
    }
}
void work1()
{
    top=0;
    for(int i=1;i<=n;i++)//左边最近的比a[i]大的数
    {
        while(top && a[s[top]]<=a[i]) top--;
        l[i]=s[top]+1;//+1是因为[l[i],r[i]]为闭区间
        s[++top]=i;
    }
    top=0;
    for(int i=n;i;i--)//右边最近的比a[i]大的数
    {
        while(top && a[s[top]]<=a[i]) top--;
        int x=s[top];
        if(x==0) x=n+1;
        r[i]=x-1;
        s[++top]=i;
    }
}
bool work2()
{
    for(int i=1;i<=n;i++)
    {
        ll MAX=query1(i,r[i]);
        ll MIN=query2(l[i]-1,i-1);
        if(MAX-MIN>a[i]) return 0;
        //只要有一个不满足条件就return 0;
    }
    return 1;
}
int main()
{
    cin>>t;
    while(t--)
    {
        init();
        ST();
        work1();//处理l[i],r[i]
        if(work2()) puts("YES");
        else puts("NO");
    }
    return 0;
}
```



---

## 作者：Morgen_Kornblume (赞：2)

本文同步发表于我的 cnblogs，点击此处获得更佳食用体验：[链接](https://www.cnblogs.com/Lucky-Yukikaze/p/16333227.html)

## 正文：

赛时大寄，最后十分钟没有调出来，下大分！

### 题意简述

给你一个正负数都有的序列，试判断是否对于所有的子区间都有区间和大于等于区间最大值成立。

有多组数据。

### 解法：

考虑怎么样的情况下让这个不等式不成立，那无非是区间最大值取正数，然后让区间和尽量大。

于是不难想到，我们可以对于每一个正数，考虑他作为区间最大值的情况，然后在它可以做最大值的区间内找区间最大和，然后与当前这个正数比较来判断。

区间最大和可以用一个保存了前缀和的线段树来实现查询；一个正数可以做最大值的区间即前一个比他大的数和后一个比他大的数所夹区间（若没有这样的数就去序列的首或尾），寻找这个区间的过程可用单调栈来实现。

具体操作详见代码。

```cpp
/*
  Author:Lucky_Yukikaze

*/
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define re register
#define pb push_back
#define mp make_pair
#define pf pop_front
#define pob pop_back
#define fr front
#define bk back

using namespace std;
typedef pair<int,int> pii;
typedef long double ld;
typedef pair<ll,ll> pll;

namespace Morgen{

	inline int fr(){
		int res=0;bool sig=false;char tp=getchar();
		while(!isdigit(tp)){
			if(tp=='-')sig=!sig;
			tp=getchar();
		}
		while(isdigit(tp)){
			res=(res<<1)+(res<<3)+tp-'0';
			tp=getchar();
		}
		if(sig)res=-res;
		return res;
	}
	
	int T;
	int n;
	ll a[200010];
	ll qzh[200010];
	int pre[200010],nex[200010];
	struct element{
			ll minn,maxx;
	}dat[800010];
	struct segt{
		
		
		
		void build(int nowa,int l,int r){
			if(l==r){
				dat[nowa].minn=dat[nowa].maxx=qzh[l];return;
			}
			int mid=(l+r)>>1;
			build(nowa<<1,l,mid);
			build(nowa<<1|1,mid+1,r);
			dat[nowa].maxx=max(dat[nowa<<1].maxx,dat[nowa<<1|1].maxx);
			dat[nowa].minn=min(dat[nowa<<1].minn,dat[nowa<<1|1].minn); 
		}
		
		element query(int nowa,int l,int r,int tl,int tr){
			if(tl<=l&&r<=tr)return dat[nowa];
			int mid=(l+r)>>1;
			element res1,res2,res;
			res1=res2=(element){(ll)1e18,(ll)-1e18};
			if(tl<=mid)res1=query(nowa<<1,l,mid,tl,tr);
			if(tr>mid)res2=query(nowa<<1|1,mid+1,r,tl,tr);
			return (element){min(res1.minn,res2.minn),max(res1.maxx,res2.maxx)};
		}
			
	}sg;
	
	void main(){

		cin>>T;
		
		while(T--){
			cin>>n;
			qzh[0]=0;
			for(int i=1;i<=n;i++){
				cin>>a[i];
				qzh[i]=qzh[i-1]+a[i];
			}
			sg.build(1,0,n);
			stack<pair<int,int>>stk;
			for(int i=1;i<=n;i++){
				if(a[i]>0){
					while((!stk.empty())&&stk.top().first<a[i]){
						nex[stk.top().second]=i-1;
						stk.pop();
					}
					if(!stk.empty())pre[i]=stk.top().second;
					else pre[i]=0;
					stk.push(mp(a[i],i));
				} 
			}
			while(!stk.empty())nex[stk.top().second]=n,stk.pop();
			bool flag=true;
			for(int i=1;i<=n;i++){
				if(a[i]>0){
					element qf=sg.query(1,0,n,pre[i],i),hf=sg.query(1,0,n,i,nex[i]);
					ll sm=qzh[i]-qf.minn+hf.maxx-qzh[i];
					if(a[i]<sm){
						flag=false;
						break;
					}
				}
			}
			if(flag==false)cout<<"NO"<<endl;
			else cout<<"YES"<<endl;
		}
	}

};

signed main(){
	//ios::sync_with_stdio(false);
	//cin.tie(nullptr);cout.tie(nullptr);

	Morgen::main();

	return 0;
}



```


---

## 作者：lmgoat (赞：2)

考虑对于每个 $a_i$ 它会作为某段区间的最大值的那些区间。记 $lst_i$ 表示最大的满足 $j<i$ 且 $a_j>a_i$ 的 $j$，$nxt_i$ 表示最小的满足 $j>i$ 且 $a_j>a_i$ 的 $j$。所以对于每个 $i$，$a_i$ 作为区间最大值的区间的左端点的取值范围就是 $[lst_i+1,i]$，右端点的取值范围是 $[i,nxt_i-1]$。求 $lst_i$ 和 $nxt_i$ 可以用 ST 表加二分。

固定了不等式的左边之后只需要找到最大的右边，如果有任意区间满足左边小于右边就是 NO。区间和就是右端点的前缀和减左端点减一的前缀和，所以只要找到前缀和最大的右端点和前缀和最小的减一后的左端点减一下就是最大的区间和。实现同样可以用 ST 表。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int read() {
	int x(0),f(0);
	char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
const int N=200005,inf=1e18;
int n,a[N],sum[N],lst[N],nxt[N],f[30][N];
void init() {
    for(int i=1;i<=n;++i) f[0][i]=a[i];
    int t=log(n)/log(2)+1;
    for(int i=1;i<=t;++i) 
    for(int j=1;j<=n-(1<<i)+1;++j)
        f[i][j]=max(f[i-1][j],f[i-1][j+(1<<(i-1))]);
}
inline int ask(int l,int r) {
	if(r<1) return 0;
	int res=-inf;
	if(l<1) l=1,res=0;
	int k=log(r-l+1)/log(2);
	res=max(res,max(f[k][l],f[k][r-(1<<k)+1]));
	return res;
}
int st[30][N][2];
void build() {
    for(int i=1;i<=n;++i) st[0][i][0]=st[0][i][1]=sum[i];
    int t=log(n)/log(2)+1;
    for(int i=1;i<=t;++i) 
    for(int j=1;j<=n-(1<<i)+1;++j)
        st[i][j][0]=max(st[i-1][j][0],st[i-1][j+(1<<(i-1))][0]),st[i][j][1]=min(st[i-1][j][1],st[i-1][j+(1<<(i-1))][1]);
}
inline int askma(int l,int r) {
	if(r<1) return 0;
	int res=-inf;
	if(l<1) l=1,res=0;
	int k=log(r-l+1)/log(2);
	res=max(res,max(st[k][l][0],st[k][r-(1<<k)+1][0]));
	return res;
}
inline int askmi(int l,int r) {
	if(r<1) return 0;
	int res=inf;
	if(l<1) l=1,res=0;
	int k=log(r-l+1)/log(2);
	res=min(res,min(st[k][l][1],st[k][r-(1<<k)+1][1]));
	return res;
}
signed main() {
	int _=read();
	while(_--) {
		n=read();
		for(int i=1;i<=n;++i) a[i]=read(),sum[i]=sum[i-1]+a[i];
		for(int i=1;i<=n+3;++i) lst[i]=nxt[i]=0;
		build();
		init();
		for(int i=1;i<=n;++i) {
			int l=1,r=i-1,mid,res=0;
			while(l<=r) {
				mid=(l+r)>>1;
				if(ask(mid,i-1)>a[i]) res=mid,l=mid+1;
				else r=mid-1;
			}
			lst[i]=res;
		}
		for(int i=1;i<=n;++i) {
			int l=i+1,r=n,mid,res=n+1;
			while(l<=r) {
				mid=(l+r)>>1;
				if(ask(i+1,mid)>a[i]) res=mid,r=mid-1;
				else l=mid+1;
			}
			nxt[i]=res;
		}
		bool flag=0;
		for(int i=1;i<=n;++i)
			if(a[i]<askma(i,nxt[i]-1)-askmi(lst[i],i-1)) {
				flag=1;
				break;
			}
		if(flag) puts("NO");
		else puts("YES");
	}
	return 0;
}
```


---

## 作者：EDqwq (赞：1)

这是一个我自我感觉良好的做法。

首先，考虑枚举每一个数作为区间的 $max$ 。

一个数为这个数列中一个区间的 $max$ ，假设这个数为 $a_i$ ，在这个数左边的比这个数小的第一个数叫做 $a_{k1}$ ，在这个数右边比这个数大的第一个数叫做 $a_{k2}$ ，那么这个区间必然是区间 $[k1,k2]$ 的 **子区间** （包括 $[k1,k2]$ 本身）。


处理每一个数的 $k1$ 和 $k2$ ，这个可以使用 ST 表搭配二分完成，难度很低，这里不细讲。

现在我们获得了可取区间的范围，那么如果我们需要在这个区间内选一个子区间让这个子区间的和大于这个区间的最大值（也就是我们枚举的值），只有选这个区间 **包含枚举的这个数的最大值** 才是最优。

由于有包含该数的限制，所以考虑使用前缀和，前缀和表示区间 $[l,r]$ 的和的方式是 $pre_r - pre_l$ ，而在这里 $r$ 必须**大于等于**枚举的最大值的下标，而 $l$ 必须 **小于** 枚举的最大值的下标。

如果要让 $pre_r - pre_l$ 最大，那么 $pre_r$ 必须尽量大， $pre_l$ 必须尽量小。

在此情况下，前缀和数组被分为了两个部分。使用 ST 表处理前缀和数组区间最大和最小值就行了。对于左或右没有大于它的数的情况，特判（也就是可以随意取值）。

```cpp
/*
   深山踏红叶，耳畔闻鹿鸣
   飘摇风雨中，睹物思故乡
      可叹，落叶飘零
*/

#include<bits/stdc++.h>

#define int long long
#define mem(x,y) memset(x,y,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int n;

struct node{
	int dp[300010][23];
	
	void init(int* k,int stu){
		for(int i = 1;i <= n;i ++)dp[i][0] = k[i];
		for(int j = 1;(1 << j) <= n;j ++){
			for(int i = 1;(i + (1 << (j - 1))) <= n;i ++){
				if(stu == 1)dp[i][j] = max(dp[i][j - 1],dp[i + (1 << (j - 1))][j - 1]);
				else dp[i][j] = min(dp[i][j - 1],dp[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	
	int query(int l,int r,int stu){
		if(l == r && l == 0)return 0;
		if(l > r){
			if(stu == 1)return -1e9;
			return 1e9;
		}
		int s = 1e9;
		if(l == 0 && stu == 2)s = 0;
		l = (l == 0 ? 1 : l);
		int k = log2(r - l + 1);
  	    if(stu == 1)return max(dp[l][k],dp[r - (1 << k) + 1][k]);
  	    else return min(s,min(dp[l][k],dp[r - (1 << k) + 1][k]));
	}
}st[3];

int t;
int a[1000010];
int pre[1000010];
int l[1000010],r[1000010];

void solve(){
	n = read();
	for(int i = 1;i <= n;i ++)a[i] = read();
	for(int i = 0;i <= n + 10;i ++)pre[i] = 0;
	for(int i = 1;i <= n;i ++)pre[i] = pre[i - 1] + a[i];
	st[0].init(a,1);
	st[1].init(pre,1);
	st[2].init(pre,2);
	for(int i = 0;i <= n + 10;i ++)l[i] = 0,r[i] = n + 1;
	for(int i = 1;i <= n;i ++){
		int L,R,mid;
		L = 1,R = i - 1;
		int ans = -1;
		while(L <= R){
			mid = (L + R) / 2;
			if(st[0].query(mid,i - 1,1) > a[i])L = mid + 1,ans = mid;
			else R = mid - 1;
		}
		if(ans != -1)l[i] = ans;
		L = i + 1,R = n;
		ans = -1;
		while(L <= R){
			mid = (L + R) / 2;
			if(st[0].query(i + 1,mid,1) > a[i])R = mid - 1,ans = mid;
			else L = mid + 1;
		}
		if(ans != -1)r[i] = ans;
	}
	bool flag = false;
	for(int i = 1;i <= n;i ++){
		int ll = l[i] + 1;
		int rr = r[i] - 1;
		int v1 = st[2].query(ll - 1,i - 1,2);
		int v2 = st[1].query(i,rr,1);
		if(v2 - v1 > a[i])flag = true;
	}
	if(flag)puts("NO");
	else puts("YES");
}

signed main(){
    cin>>t;
    while(t --)solve();
}
```

---

## 作者：GI录像机 (赞：1)

更新：修正题目大意。

## 题目大意：

给定一个数列 $a$，判断 $\forall 1\le i\le j\le n,\max(a_i,\cdots,a_j)\geq a_i+\cdots+a_j$ 是否为真命题，是则输出 `YES`，否则输出 `NO`。

## 思路：

我们可以找到每个数作为最大值的区间，然后使右边的式子最大化，也就是找到这个数为最大值的区间的最大子段和，比较该数与最大子段和。

那如果最大子段和不包含我们所找最大值呢？没有影响，因为如果我们所要找的最大子段和中的最大值，一定是小于我们所找的最大值的，所以不会造成误判。

找每个数作为最大值的区间可以使用单调栈，~~但我喜欢线段树~~。区间最大子段和也可以通过线段树实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10;
int v[N], t = read(), n, lll[N], rrr[N];
struct Node {
	int suml, sumr, sum, num;
} a[N << 2];
struct Edge {
	int maxn;
} b[N << 2], c[N << 2];
void pushup1(int pos) {
	a[pos].num = a[pos << 1].num + a[pos << 1 | 1].num;
	a[pos].suml = max(a[pos << 1].suml, a[pos << 1].num + a[pos << 1 | 1].suml);
	a[pos].sumr = max(a[pos << 1 | 1].sumr, a[pos << 1 | 1].num + a[pos << 1].sumr);
	a[pos].sum = max(a[pos << 1].sum, max(a[pos << 1 | 1].sum, a[pos << 1].sumr + a[pos << 1 | 1].suml));
}
void pushup2(int pos) {
	b[pos].maxn = max(b[pos << 1].maxn, b[pos << 1 | 1].maxn);
}
void pushup3(int pos) {
	c[pos].maxn = max(c[pos << 1].maxn, c[pos << 1 | 1].maxn);
}
void build1(int pos, int l, int r) {
	if (l == r) {
		a[pos].num = a[pos].suml = a[pos].sumr = a[pos].sum = v[l];
		return;
	}
	int mid = (l + r) >> 1;
	build1(pos << 1, l, mid);
	build1(pos << 1 | 1, mid + 1, r);
	pushup1(pos);
}
void build2(int pos, int l, int r) {
	if (l == r) {
		b[pos].maxn = -0x3f3f3f3f;
		return;
	}
	int mid = (l + r) >> 1;
	build2(pos << 1, l, mid);
	build2(pos << 1 | 1, mid + 1, r);
	pushup2(pos);
}
void build3(int pos, int l, int r) {
	if (l == r) {
		c[pos].maxn = -0x3f3f3f3f;
		return;
	}
	int mid = (l + r) >> 1;
	build3(pos << 1, l, mid);
	build3(pos << 1 | 1, mid + 1, r);
	pushup3(pos);
}
void add2(int pos, int l, int r, int L, int k) {
	if (l == L && L == r) {
		b[pos].maxn = k;
		return;
	}
	int mid = (l + r) >> 1;
	if (L <= mid)add2(pos << 1, l, mid, L, k);
	else add2(pos << 1 | 1, mid + 1, r, L, k);
	pushup2(pos);
}
void add3(int pos, int l, int r, int L, int k) {
	if (l == L && L == r) {
		c[pos].maxn = k;
		return;
	}
	int mid = (l + r) >> 1;
	if (L <= mid)add3(pos << 1, l, mid, L, k);
	else add3(pos << 1 | 1, mid + 1, r, L, k);
	pushup3(pos);
}
Node query1(int pos, int l, int r, int L, int R) {
	if (L <= l && r <= R)return a[pos];
	int mid = (l + r) >> 1;
	Node lson, rson, ans;
	ans.num = 0;
	if (L <= mid)lson = ans = query1(pos << 1, l, mid, L, R);
	if (mid + 1 <= R)rson = ans = query1(pos << 1 | 1, mid + 1, r, L, R);
	if (L <= mid && mid + 1 <= R) {
		ans.num = lson.num + rson.num;
		ans.suml = max(lson.suml, rson.suml + lson.num);
		ans.sumr = max(rson.sumr, lson.sumr + rson.num);
		ans.sum = max(lson.sum, max(rson.sum, lson.sumr + rson.suml));
	}
	return ans;
}
int query2(int pos, int l, int r, int k) {
	if (l == r)return l;
	int mid = (l + r) >> 1;
	if (b[pos << 1 | 1].maxn > k)return query2(pos << 1 | 1, mid + 1, r, k);
	else if (b[pos << 1].maxn > k)return query2(pos << 1, l, mid, k);
	return 0;
}
int query3(int pos, int l, int r, int k) {
	if (l == r)return l;
	int mid = (l + r) >> 1;
	if (c[pos << 1].maxn > k)return query3(pos << 1, l, mid, k);
	else if (c[pos << 1 | 1].maxn > k)return query3(pos << 1 | 1, mid + 1, r, k);
	return n + 1;
}
signed main() {
	while (t--) {
		bool flag = 0;
		n = read();
		for (int i = 1; i <= n; i++)v[i] = read();
		if (n == 1) {
			puts("YES");
			continue;
		}
		build1(1, 1, n);
		build2(1, 1, n);
		build3(1, 1, n);
		for (int i = 1; i <= n; i++) {
			lll[i] = query2(1, 1, n, v[i]) + 1;
			add2(1, 1, n, i, v[i]);
		}
		for (int i = n; i >= 1; i--) {
			rrr[i] = query3(1, 1, n, v[i]) - 1;
			add3(1, 1, n, i, v[i]);
		}
		for (int i = 1; i <= n; i++) {
			if (flag)break;
			Node cnt = query1(1, 1, n, lll[i], rrr[i]);
			if (cnt.sum > v[i])flag = 1;
		}
		if (flag)puts("NO");
		else puts("YES");
	}
	return 0;
}
```


---


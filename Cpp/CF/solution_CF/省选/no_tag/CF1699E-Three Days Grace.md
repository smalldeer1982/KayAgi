# Three Days Grace

## 题目描述

给定一个初始有 $n$ 个元素的可重复集合 $A$，其中每个元素都在 $1$ 到 $m$ 之间。  

每次操作可以将 $A$ 中的一个元素（称之为 $x$）从 $A$ 中删除，然后在 $A$ 中加入两个元素 $p,q$，满足 $p\cdot q=x$ 且 $p,q>1$。

显然每次操作后 $A$ 的大小会增加 $1$。  

定义 $A$ 的平衡值为 $A$ 中的最大值减去最小值，求任意次操作（可以是 $0$ 次）后最小可能的平衡值。

## 样例 #1

### 输入

```
4
5 10
2 4 2 4 2
3 50
12 2 3
2 40
6 35
2 5
1 5```

### 输出

```
0
1
2
4```

# 题解

## 作者：YGB_XU (赞：50)

写这篇题解是因为本人在写题的时候，洛谷的所有题解和 CF 的官方题解全都看不懂。费了好大劲全部理解之后，决定尝试写一篇细致的题解帮助后人。

首先对于题目中的可重集，如果有相同的数，显然可以对其进行相同的分解，使得去重不影响答案。

我们的目标是让最后的**极差最小**，在固定了拆分后所有数字值域的一端后，值域的另一端随之变化。是**双指针**。

这里给出一个动态规划 $dp_{i,j}$ 表示将 $j$ 这个数拆分后，如果要求拆出来的数都大于等于 $i$，那么这些数的最大值的最小值是多少。遵从上面双指针的思想，$i$ 就相当于固定了的值域最小值，答案即 $\min\{ \max\{ dp_{i,j} \}(j\in A)-i\}(1\le i\le \min(a_k))$，注意 $i$ 的范围限制来自拆分完之后最小的数显然要小于等于原可重集中的最小数。

接着考虑转移。

如果 $i\nmid j$ 显然有

$$dp_{i,j}=dp_{i+1,j}$$

因为不可能拆出来 $i$，那么值域里含不含 $i$ 没有区别。

如果 $i\mid j$，且 $i^2\le j$ 有

$$dp_{i,j}=\min(dp_{i,j},dp_{i,j/i})$$

注意这里有条件，原因是拆出来一个 $i$ 之后要保证剩下的数字都大于等于 $i$。

显然第一维应该倒序枚举，作为双指针中的左端点。

巧妙的优化来了：转移只需要用到第一维比当前大 $1$ 或者相等的部分，所以把第一维删去。发现第一种转移可以忽略，第二种转移只会在整除时进行，即便不考虑第二个条件，转移的总次数也是 $m$ 的调和级数级别，可以接受。此外，注意到第二种转移需要的是第一维相同，而第二维比自己小的位置，因此需要第二维比自己小的位置已经被得出，在实现上只需从小到大枚举第二维即可。

另一件巧妙的事情是由于动态规划的意义，第二维相同，而第一维减小的情况下，dp 值将单调不升。那么双指针的右端点只会随左端点下降而单调不升。在维护它的时候可以维护一个 dp 值的桶，让这个指针向下一直扫到存在的位置。

时间复杂度 $O(m\log m)$

详见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
	int ret=0,f=1;
	char c=getchar();
	while(c<'0'||'9'<c){
		if(c=='-') f=-1;
		c=getchar();
	}
	while('0'<=c&&c<='9'){
		ret=(ret<<1)+(ret<<3)+(int)(c-'0');
		c=getchar();
	}
	return ret*f;
}

const int NR=1e6+5,MR=5e6+5;
int a[NR],dp[MR],buc[MR];//buc为dp值的桶
bool flag[MR];

inline void solve(){
	int n,m;
	n=read();m=read();
	for(int i=1;i<=m;i++) flag[i]=false,buc[i]=0;
	int minn=m;
	for(int i=1;i<=n;i++) a[i]=read(),flag[a[i]]=true,minn=min(minn,a[i]);
	for(int i=1;i<=m;i++){
		dp[i]=i;
		if(flag[i]) buc[i]++;//即buc[dp[i]]++
	}
	int maxx=m,ans=m;//右端点和极差
	for(int i=m;i>=1;i--){
		if(1ll*i*i<=m){//需要保证i*i<=m才可能产生转移
			for(int j=i*i;j<=m;j+=i){//m调和级数
				if(flag[j]) buc[dp[j]]--;
				dp[j]=min(dp[j],dp[j/i]);
				if(flag[j]) buc[dp[j]]++;
			}
		}
		while(!buc[maxx]) maxx--;
		if(i<=minn) ans=min(ans,maxx-i);
	}
	cout<<ans<<'\n';
}

int main(){
	int t=read();
	while(t--) solve();
	return 0;
}
```


---

## 作者：I_am_Accepted (赞：14)

~~这是 DP 吗？啊？~~

由于我们要分解后**极差最小**，相当于**固定最小值**后求**最小的最大值**。

设我们当前定的最小值为 $mn$，$f_x$ 表示 $x$ 分解成不小于 $mn$ 后最大的因数的最小值（若 $x<mn$ 则无意义），显然我们要的是 
$$
\max_{x\in A}f_x
$$
我们将 $mn$ 从大至小递减，每个答案取最小值即为最后输出。

考虑如何快速将 $mn+1$ 转移到 $mn$。我们惊奇地发现，只有 $mn$ 的倍数的 $f$ 才会改变，即
$$
f_x=\min(f_x,f_{x/mn})
$$
注意这里 $f_{x/mn}$ 为变换过的，即若 $x$ 中含多个 $mn$，则其实是
$$
f_x=\min(f_x,f_{x/mn},f_{x/mn^2},f_{x/mn^3},\dots)
$$
这样我们就以调和级数 $O(m\log m)$ 的复杂度解决本题。

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define N 5000010
int n,m,f[N],t[N],pos,ans;
bool a[N];
inline void upd(int id,int val){
	if(a[id]){
		t[f[id]]--;
		t[f[id]=val]++;
		while(!t[pos]) pos--;
	}else{
		f[id]=val;
	}
}
void work(){
	scanf("%d%d",&n,&m); 
	fill(a+1,a+1+m,0);
	fill(f+1,f+1+m,m+1);
	fill(t+1,t+2+m,0);
	int x;
	For(i,1,n){
		scanf("%d",&x);
		a[x]=1;
	}
	For(i,1,m) if(a[i]) t[m+1]++;
	ans=pos=m+1;
	Rof(i,m,1){
		upd(i,i);
		For(j,i,m/i) if(f[i*j]>f[j]) upd(i*j,f[j]);
		if(pos<=m) ans=min(ans,pos-i);
	}
	printf("%d\n",ans);
}
int main(){
	int T;scanf("%d",&T); 
	while(T--)work();
return 0;}
```

---

## 作者：myee (赞：5)

### 前言

CF 我勇往直下，直播下饭，成功 div.2 快速切完 ABC 后 E 题屡次写挂！

### 思路

从大到小确定 $1\sim m$ 中每个数本身而言对每个左端点（下界）对应的最小右端点（上界）。

这显然只在因子作下界处改变答案（为什么？因为**非因子不可能成为这个数的分解结果**），故可以调和级数复杂度枚举，用更小部分的答案更新它本身。

且最大从 $\sqrt m+1$ 开始枚举即可，因为 $\min\{a,\frac ba\}\le\sqrt b$，大于 $\sqrt m$ 的分解方案仅**分解成本身**一种。

维护变化可以用 $O(m)-O(1)-O(\sqrt m)$ 的分块根号平衡一下，因为修改为 $O(m\log m)$ 次，而查询只有 $O(\sqrt m)$ 次。

复杂度为 $O(n+m\log m)$，可以通过。

注意特判一下最小数大于 $\sqrt m$ 的情况时的答案。

### Code

```cpp
// Problem: E. Three Days Grace
// Contest: Codeforces - Codeforces Round #804 (Div. 2)
// URL: https://codeforces.com/contest/1699/problem/E
// Memory Limit: 256 MB
// Time Limit: 4000 ms

#include <bits/stdc++.h>
typedef long long llt;
typedef unsigned uint;typedef unsigned long long ullt;
typedef bool bol;typedef char chr;typedef void voi;
typedef double dbl;
template<typename T>bol _max(T&a,T b){return(a<b)?a=b,true:false;}
template<typename T>bol _min(T&a,T b){return(b<a)?a=b,true:false;}
template<typename T>T lowbit(T n){return n&-n;}
template<typename T>T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T>T lcm(T a,T b){return(a!=0||b!=0)?a/gcd(a,b)*b:(T)0;}
template<typename T>T exgcd(T a,T b,T&x,T&y){if(b!=0){T ans=exgcd(b,a%b,y,x);y-=a/b*x;return ans;}else return y=0,x=1,a;}
template<typename T>T power(T base,T index,T mod)
{
    T ans=1%mod;
    while(index)
    {
        if(index&1)ans=ans*base%mod;
        base=base*base%mod,index>>=1;
    }
    return ans;
}
uint Ans[5000005];bol S[5000005];
namespace S2
{
    uint B;
    uint Sum[6000005],W[5000005];
    voi build(uint m)
    {
        B=sqrt(m)+1;
        for(uint i=0;i<=B*B;i++)Sum[i]=0;
        for(uint i=0;i<=B;i++)W[i]=0;
    }
    voi add(uint v){Sum[v]++,W[v/B]++;}
    voi del(uint v){Sum[v]--,W[v/B]--;}
    uint find()
    {
        for(uint i=B;~i;i--)if(W[i])for(uint j=B-1;~j;j--)if(Sum[i*B+j])return i*B+j;
        return-1;
    }
};
int main()
{
    uint t;
    scanf("%u",&t);
    while(t--)
    {
        uint n,m,x=-1,ans=-1;
        scanf("%u%u",&n,&m);uint w=sqrt(m)+10;
        S2::build(m);
        for(uint i=1;i<=m;i++)Ans[i]=i,S[i]=false;
        for(uint i=0,v;i<n;i++)scanf("%u",&v),_min(x,v),S[v]=true;
        for(uint i=1;i<=m;i++)if(S[i])S2::add(Ans[i]);
        if(x>w)_min(ans,S2::find()-x);
        for(uint q=w;q;q--)
        {
            for(uint i=q*q;i<=m;i+=q)
            {
                if(S[i])S2::del(Ans[i]);
                _min(Ans[i],std::max(q,Ans[i/q]));
                if(S[i])S2::add(Ans[i]);
            }
            if(q<=x)_min(ans,S2::find()-q);
        }
        printf("%u\n",ans);
    }
    return 0;
}
```



---

## 作者：老莽莽穿一切 (赞：5)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16457670.html)

---

[**CF link**](https://codeforces.com/problemset/problem/1699/E)

[**你谷 link**](https://www.luogu.com.cn/problem/CF1699E)

一道非常巧妙的 dp 题，但是顺着思路水到渠成并不是完全无迹可寻。

首先观察到题面中答案的形式是最值相减，提醒我们使用双指针的思想，即枚举最小值的过程中动态单调维护最大值，同时注意到本题中的操作类型是将一个数拆成两个数相乘的形式，所以可以想到是从大到小枚举，且思考加入控制了最大值，则要将比最大值大的数拆开，不是很好控制拆成那些数，拆的数的数量，所以考虑从大到小枚举最小值，同时控制最大值。

接下来考虑如何去控制最大值，如字面意思一般，我们希望让最大值尽量小，但是有不能在分解过程中产生比我们确定的最小值更小的值，单纯的用贪心似乎并不适合解决这个问题，所以我们考虑使用 dp。

本着求什么设什么的原则，我们设 $f_{i,x}$ 表示满足能将 $x$ 分解成多个数相乘且所有数都被包含在区间 $[i,v]$ 内的最小的 $v$，在具体实现过程中状态中的第一维 $i$ 可以压掉。接下来考虑转移，首先可以想到肯定是从大到小枚举 $i$，对于每个 $i$，任何一个 $x$ 的分解只有几种可能，要么根本不能分出 $i$，要么分出几个 $i$，要么能分不分，分别考虑转移，前后两种转移都是直接继承上一次的答案，$i$ 那维压掉后即不变，中间的转移考虑到一个数不一定只分出一个 $i$，所以可以考虑使用类似多重背包的优化，正向枚举直接转移，$f_x=\min\{f_x,f_\frac xi\}$。

然后我们发现上面的转移过程中 $f$ 数组随 $i$ 变小是单调变小的，即最大值不会变大，我们就可以进行上面的双指针，对于每个集合中存在的 $x$，标记 $f_x$，然后用一个指针指向最后一个标记，标记位置单调前移，每次计算答案，[代码](https://codeforces.com/contest/1699/submission/163163645)实现难度不大。

---

## 作者：Rem_CandleFire (赞：2)

对于此类对数列进行操作，求极差的最值的问题，考虑**双指针**。

即，枚举（限定）一个最小值，求操作后**数列的最大值**的最小值。不妨先设此最小值为 $k$。

于是我们可以对数列中的数进行分解，对于一个数 $x=p\times q$，显然应该使 $p,q\le k$，否则对答案没有贡献。

我们设 $f_i$ 为将 $i$ 拆分为大于等于 $k$ 的数的乘积，这些数中最大值的最小值。则有 $f_i=\min(f_i,f_{i/k})(i^2\le k)$。

注意到当我们**从大到小枚举 $k$ 时，$f_i$ 的值单调不升**，于是开一个桶记录，最后 $ans=\min(ans,mx-k)$。

[AC code](https://www.luogu.com.cn/paste/t9tjrpbg)

---

## 作者：Sellaris (赞：2)

- 妙妙 DP 捏。令 $\mathit{dp}_{i}$ 表示集合中数字 $i$ 可以变成哪个数。

- 是以值域为基础进行枚举。因为要使极差最小，于是发现应该 **从大到小** 枚举因数，再枚举这是哪个数的因数来进行动态规划。

- 同时发现贪心的性质,一个数 $x$ 拆分成接近 $\sqrt{x}$ 是更优的。注意 **从大到小枚举值域根号内的因数是为了正确的转移顺序** 。又因为答案所求 **极差** 的最小值，所以转移时对一个数 $x \geq \sqrt{x}$ 的部分取最小值 。 

- 枚举时左指针是因数，右指针是集合中最大值，同时用一个数组维护这个数有多少个，没有则更新右指针。枚举完每个因数来更新答案为左右指针的值域差。注意刚开始多重集有多个只需考虑一个。

- 更详情参见注释。

```cpp
///*****Sellaris*****///
//#pragma once
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include <bits/stdc++.h>
//#include <bits/extc++.h>
#define int long long
using namespace std;
//using namespace __gnu_pbds;
const int maxn=5e6+10;
inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
    return ret*f; //x=(x<<1)+(x<<3)+(ch^48);
}
int a[maxn]={0};
int f[maxn];
int b[maxn];
int dp[maxn];
int n;int m;
    /*
    n个1-m的数 
    a原数组 
	f数组是有没有这个数
	b数组是现在这个i有多少个 
	dp数组是i能变成的值 
	
	*刚开始有多个只需考虑1个
	 
	*/
inline void solve(){
    n=read();m=read();
    for(int i=1;i<=m;i++) f[i]=b[i]=0,dp[i]=i;
    int l=LLONG_MAX;
    int r=LLONG_MIN;
	for(int i=1;i<=n;i++) {
		a[i]=read();
		f[a[i]]=b[a[i]]=1;
		l=min(l,a[i]),r=max(r,a[i]);
	}
	int res=r-l;//注意dp枚举方式 
	for(int i=sqrt(m);i>=1;i--){//从大到小枚举因数
		for(int j=i;j<=m;j+=i){//枚举是哪个数的因数 
			if(f[j]) b[dp[j]]--;//如果有这个数，分解 
			if(dp[j/i]>=i) dp[j]=min(dp[j],dp[j/i]);//维护dp[i] 能变成的值 
			if(f[j]) b[dp[j]]++;
		}
		while(b[r]==0) r--;//维护右指针 
		res=min(res,r-min(i,l));//更新答案 
	}
	cout<<res<<"\n";
}
signed main(){
    //std::ios::sync_with_stdio(false);std::cin.tie(NULL);std::cout.tie(NULL);
    //freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int t=read();
	while(t--){
		solve();
	}
    return 0;
}




```


---

## 作者：Felix72 (赞：1)

相当不错的题，考验了分层 DP 思想的运用。

询问的是极差，则通常的做法是固定一个端点求另一个端点的最值。尝试固定右端点，此时对全体自然数，有 DP 数组 $f_i$ 表示令 $i = s_1 \times s_2 \times \dots \times s_k$，所有可能的拆分中，$\max{s}$ 小于右端点的情况下 $\min{s}$ 的最大值。

我们可以对每个乘数分层转移，类似背包 DP 中的物品顺序对答案无影响这一性质。这刚好契合右端点从左往右移这一过程。

对于左端点，套上双指针即可线性维护。总复杂度 $O(n\ln n)$，对于有 $1$ 的情况加以贪心特判。

---

## 作者：Tjqq (赞：1)

## 两个 log 无脑做法
朴素 dp 是显然的，具体可以看看第一篇题解，这里不再赘述。

由于 CF 机子很快，并不需要第二个性质，直接上线段树维护最大值就能过了。

### code
```
//created by fqr & cyx in 2025
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
#define ll long long
#define pb emplace_back
int ff,Ch;
template <typename T> inline void rd(T &x) {
    x=0,ff=1,Ch=getchar();
    while((Ch<'0'||Ch>'9') && Ch!='-') Ch=getchar();
    if(Ch=='-')Ch=getchar(),ff=-1;
    while(Ch>='0' && Ch<='9') {
        x=(x<<1)+(x<<3)+Ch-'0';
        Ch=getchar();
    }
    x*=ff;
}
template <typename T,typename ...Args> inline void rd(T &x,Args &...args) {
    rd(x), rd(args...);
}
using namespace std;
const int N=5e6+5;
int n,m;
int a[N]; 
namespace sgt {
	#define ls x<<1
	#define rs x<<1|1
	int mx[N<<2];
	void build(int x,int l,int r,vector<int> &cnt) {
		if(l==r) return mx[x]=cnt[l]?1e9:0,void();
		int mid=l+r>>1;
		build(ls,l,mid,cnt),build(rs,mid+1,r,cnt);
		mx[x]=max(mx[ls],mx[rs]);
	}
	void upd(int x,int l,int r,int pos,int val) {
		if(l==r) return mx[x]=val,void();
		int mid=l+r>>1;
		if(pos<=mid) upd(ls,l,mid,pos,val);
		else upd(rs,mid+1,r,pos,val);
		mx[x]=max(mx[ls],mx[rs]);
	}
}
void Solve() {
	rd(n),rd(m);
	vector<int> cnt(m+1),dp(m+1);
	for(int i=1; i<=n; i++)
		rd(a[i]),cnt[a[i]]++;
	sgt::build(1,1,m,cnt);
	int ans=1e9;
	for(int i=m; i>=1; i--) {
//		dp[i]=i;
//		for(int j=1; j<=m; j++) {
//			if(j%i==0 && i*i<=j)
//				dp[j]=min(dp[j],dp[j/i]);		
//			if(cnt[j]) mx=max(mx,dp[j]);
//		}
		dp[i]=i;
		if(cnt[i]) sgt::upd(1,1,m,i,dp[i]);
		if(1ll*i*i<=m) {
			for(int j=i*i; j<=m; j+=i) {
				if(cnt[j] && dp[j]>dp[j/i]) sgt::upd(1,1,m,j,dp[j/i]);
				dp[j]=min(dp[j],dp[j/i]);
			}
		}
//		cout<<"!" <<sgt::mx[1]<<'\n';
		ans=min(ans,sgt::mx[1]-i);
	}
	printf("%d\n",ans);
}
signed main() {
#ifdef LOCAL
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
#endif
	int T;
    rd(T);
    while(T--) Solve();
	return 0;
}
/*
dp[i][j]将数字j拆成>=i的数后最大值的最小值 
4
5 10
2 4 2 4 2
3 50
12 2 3
2 40
6 35
2 5
1 5
*/

```

---

## 作者：MortisM (赞：1)

[传送门](https://codeforces.com/contest/1699/problem/E)
## 题目大意
有一个大小为 $n$ 的 `multiset`，里面每个数都在 $1$ 到 $m$ 之间。你可以做任意次操作，每次将一个数 $x$，分解成 $p,q>1$，满足 $x=pq$，然后将 $x$ 从 `multiset` 中删除，将 $p,q$ 加入 `multiset`。

求操作结束后 `multiset` 中最大值和最小值之差的最小值。
## 思路
这个题一看就不会做，因为它要求 $\max a_i-\min a_i$。因为左右断点都在动，所以想起来就很难受。

解决这个问题的办法就是枚举左端点 $L$，求最小的右端点 $R$。即枚举 `multiset` 中的最小值，求最大值的最小值。

此时可以设 $dp(i,j)$ 表示将 $j$ 拆分因子后最小因子为 $i$ 的情况下的最大因子。

对于一个 $k\ge i$，且 $dp(k,\frac{j}{i})\ge i$，$dp(i,j)$ 可以由 $dp(k,\frac{j}{i})$ 转移过来。

时间复杂度 $O(m\log m)$。

[Code](https://www.luogu.com.cn/paste/q6fkcjl0)

---

## 作者：SegTree (赞：0)

枚举最小值，考虑最大值向右单调移动，不妨想到双指针。

相当于判定对于集合内的数 $x$，可以被 $[l,r]$ 中的数乘起来表示出。

如果做可行性 dp 比较困难，难以支持带删。

于是改成计数 dp，求 $dp_i$ 为表示出 $i$ 的方案数，则只需要做完全背包的删插问题。

具体来说，在插入 $x$ 的时候顺序枚举 $x$ 的倍数，令 $dp_i\gets dp_i+dp_{i/x}$，删除 $x$ 的时候倒序枚举 $x$ 的倍数，令 $dp_i\gets dp_i-dp_{i/x}$，在修改顺便过程中维护 $\sum_{x\in S}[dp_x>0]$ 的值，达到 $|S|$ 即合法。

复杂度为调和级数。

---

## 作者：happybob (赞：0)

题意：

给定一个初始有 $n$ 个元素的可重复集合 $A$，其中每个元素都在 $1$ 到 $m$ 之间。  

每次操作可以将 $A$ 中的一个元素（称之为 $x$）从 $A$ 中删除，然后在 $A$ 中加入两个元素 $p,q$，满足 $p \times q=x$ 且 $p,q>1$。

显然每次操作后 $A$ 的大小会增加 $1$。  

定义 $A$ 的平衡值为 $A$ 中的最大值减去最小值，求任意次操作（可以是 $0$ 次）后最小可能的平衡值。

$1 \leq n \leq 10^6$，$1 \leq m \leq 5 \times 10^6$。时限 $4$ 秒，空间限制 $256$ MB。

解法：

为了最小化极差，不妨枚举最小值 $x$，求出将所有数因数分解，每个因数都至少为 $x$ 时因数的最大值最小是多少。

考虑 DP，记 $f_{i,j}$ 表示将 $j$ 因数分解，每个因数都至少为 $i$，最大因数最小是多少。容易发现若 $i$ 不是 $j$ 的因数，有 $f_{i,j}=f_{i+1,j}$，同时若 $i \mid j$ 且 $i^2 >j$，此时 $\dfrac{j}{i} < i$，已经无法分解因数，所以 $f_{i,j} = j$，否则必有 $f_{i,j}=f_{i,\frac{j}{i}}$，意思是先将 $j$ 除以 $i$ 然后继续分解。

逆序枚举 $i$，发现 ${f_{i,j}}_{\max}$ 单调不升，维护 $f$ 的出现次数的桶双指针即可。复杂度 $O(m \log m+n)$。

[Submission Link.](https://codeforces.com/problemset/submission/1699/290544196)

---

## 作者：NKL丶 (赞：0)

## Description

给出一个大小为 $n$ 的多重集 $S$，现对其进行若干次操作，每次操作可选择其中一个元素 $S_i$，将其分解为 $p \times q$ 的形式，然后将 $S_i$ 弹出，加入 $p$ 和 $q$。问最终多重集内元素的极差的最小值。（$1 \leq n \leq 10^6,1 \leq S_i \leq m\leq 5 \times 10^6$）

## Solution

首先易知多重集内的重复元素对答案无影响，可先去重。

由于极差与元素的最大值、最小值有关，我们每次枚举最小值，调整最大值来进行计算。

设 $f_{minn,i}$ 表示当目前最小值为 $minn$ 时将 $i$ 分解后可得最大因子的最小值，不难发现我们最终的答案就是 $\max\limits_{minn \leq m} \max\limits_{i \in S} f_{minn,i}$。

我们倒序枚举 $minn$，然后进行转移。

不难发现，当我们从 $minn+1$ 转移到 $minn$ 时，对于所有的 $f_i$，只会有是 $minn$ 的倍数的位置发生改变，即此时有 $f'_{minn,i}=\min\limits_{minn^x|i}f_{i/minn^x}\qquad(minn \mid i)$。

所以总体的复杂度为调和级数 $O(m \log m)$。

## [code](https://www.luogu.com.cn/paste/4yer74mi)

---


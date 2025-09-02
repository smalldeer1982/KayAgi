# Timetable

## 题目描述

有两个公交车站，分别记为 A 和 B，每天有 $n$ 辆公交车从 A 开往 B。从 A 到 B 的最短路径需要 $t$ 单位时间，但有些公交车可能会选择更长的路线。此外，公交车在途中允许相互超车。

在每个车站，都有一个按时间排序的公交车到达时刻列表。对于 A 站，这个列表为 $a_1 < a_2 < \ldots < a_n$，对于 B 站，这个列表为 $b_1 < b_2 < \ldots < b_n$。公交车总是按照时刻表从 A 出发并到达 B，但到达 B 的顺序可能与出发顺序不同。我们称某种到达顺序是“合法”的，如果每辆公交车到达 B 的时间至少比其离开 A 的时间晚 $t$ 单位时间。

已知对于每辆在 $a_i$ 时刻从 A 出发的公交车，其在 B 站最晚可能到达的时刻为 $b_{x_i}$，即在时刻表中的第 $x_i$ 个。换句话说，对于每个 $i$，存在一种合法的到达顺序，使得第 $i$ 辆出发的公交车到达 B 时排在第 $x_i$ 位（其他公交车的到达顺序可以任意），但不存在合法顺序使得第 $i$ 辆出发的公交车到达 B 时排在第 $x_i+1$ 位。

形式化地说，我们称排列 $p_1, p_2, \ldots, p_n$ 是合法的，如果对于所有 $i$ 都有 $b_{p_i} \ge a_i + t$。那么 $x_i$ 就是在所有合法排列中 $p_i$ 的最大值。

现在给定序列 $a_1, a_2, \ldots, a_n$ 和 $x_1, x_2, \ldots, x_n$，但未给出到达 B 站的时刻表。请你找出任意一个满足条件的 B 站时刻表 $b_1, b_2, \ldots, b_n$，或者判断不存在这样的时刻表。

## 说明/提示

以第一个样例和输出的时刻表 $b_1, b_2, \ldots, b_n$ 为例。

为了使 $x_1 = 2$，公交车可以按顺序 $(2, 1, 3)$ 到达。为了使 $x_2 = 2$ 和 $x_3 = 3$，公交车可以按顺序 $(1, 2, 3)$ 到达。$x_1$ 不能为 $3$，因为排列 $(3, 1, 2)$ 和 $(3, 2, 1)$（即第 $1$ 辆公交车到达第 $3$ 个）都不合法（有公交车到达得太早），$x_2$ 不能为 $3$，原因类似。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 10
4 6 8
2 2 3
```

### 输出

```
Yes
16 17 21 
```

## 样例 #2

### 输入

```
2 1
1 2
2 1
```

### 输出

```
No
```

# 题解

## 作者：极寒神冰 (赞：5)

首先可以发现一定有一个合法的排列为$p_i=i$，因此如果对于某个$i$出现了$x_i<i$，显然此时一定无解。此外还可以得出$b_i\ge a_i+t$。

考虑$x_i=c$代表什么，这意味着存在一个排列$p$，其中第$i$辆公交车的出现时刻为$b_c$，而此时$i+1\sim c$的公交车会去哪里？那么此时有一种贪心的构造方式：
$$
i\to c,i+1\to i,i+2\to i-1,\cdots,c\to c-1
$$
显然这已经是最优的了。

因此考虑初始化$b_i=a_i+t$。

然后扫一遍记录当前$mx=\max\{a_i \}$，若$mx>i$，则要$b_i=b_{i+1}$并且将$b_{i+1}$加$1$。

最后再判断一下每个数能否到达对应的$x_i$即可。

```
inline void evil(){puts("No");exit(0);}
int n,t;
int a[222222],x[222222];
int b[222222];
signed main()
{
    n=read(),t=read();
    R(i,1,n) a[i]=read();
    R(i,1,n) 
    {
        x[i]=read();
        if(x[i]<i) evil();
    }
    R(i,1,n) b[i]=a[i]+t;
    int mx=0;
    R(i,1,n) 
    {
        mx=max(mx,x[i]);
        if(mx>i) b[i]=b[i+1],++b[i+1];
    }
    for(int L=1,R=1;L<=n;L++)
    {
        if(R<=L) R=L+1;
        while(R<=n&&a[R]+t<=b[R-1]) ++R;
        if(x[L]!=R-1) evil();
    }
    puts("Yes");
    R(i,1,n) printf("%lld ",b[i]); puts("");
}

```

---

## 作者：Hoks (赞：0)

## 前言
简单题。

摘自 [杂题选做](https://www.luogu.com.cn/training/597433)。
## 思路分析
首先要一眼给无解瞪出来。

这一点其实比较显然。

我们考虑，怎么样的一个 $p$ 序列最容易满足。

那肯定就是 $p=(1,2,3,4,5,\dots,n)$ 的时候，最容易满足。

证明很简单，这里只考虑感性理解的角度。

考虑交换 $p$ 的两项 $i,j(i<j)$，那如果这样满足的话，就说明：
$$b_j\ge a_i+t,b_i\ge a_j+t$$
那这个时候根据 $a_i<a_j,b_i<b_j$，我们可以推得：
$$b_j>b_i\ge a_j+t,b_i\ge a_j+t>a_i+t$$
所以交换前的 $p$ 序列也是合法的。

也就是说，只要我们能找到一个合法的 $p$ 序列，那么 $p=(1,2,3,4,5,\dots,n)$ 就一定合法。

那这个时候的 $x_i\ge i$ 就很显然了。

那么对于 $x_i<i$ 的输入，显然不可能构造了。

接着我们去尝试构造 $x_i>i$ 的情况。

还是想下最优的，也就是更容易满足的情况是什么？

那肯定是我们只变动这一个，一次满足一个 $x_i$ 最优。

假设我们变动的是序列 $p$ 的第 $i$ 项，需要把这项变成 $j$。

这时我们来考虑 $[i+1,j]$ 这一段该怎么填 $[i,j-1]$ 这些数。

因为 $a,b$ 都是严格递增的，所以设我们有 $x$ 这一项无法满足，用了更后面的数去满足了。

那么我们可以得到 $b_x<a_x+t<a_{x+k}+t(k>0,x+k\le n)$。

也就是如果这一项无法满足上，后面的他也肯定满足不上了，那最优的肯定是满足上这项最简单。

也就是，我们钦定 $i$ 这位选为 $j$ 后，把原本填的 $i,i+1,\dots,j-1$ 全部向后平移一位最优。

代码实现就很简单了，按照上面思路实现最后 check 一下生成的是不是满足条件的序列就行。
## 代码

```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
constexpr int N=5e5+10,V=2e5,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,t,mx,a[N],b[N],c[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r0'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void solve()
{
    n=read(),t=read();for(int i=1;i<=n;i++) b[i]=a[i]=read()+t;
    for(int i=1;i<=n;i++)
    {
        c[i]=read();
        if(c[i]<i) return put("No");
    }
    for(int i=1;i<=n;i++) 
    {
        mx=max(mx,c[i]);
        if(mx>i) b[i]=b[i+1],b[i+1]++;
    }
    for(int l=1,r=1;l<=n;l++)
    {
        if(r<=l) r=l+1;
        while(r<=n&&a[r]<=b[r-1]) r++;
        if(c[l]!=r-1) return put("No");
    }put("Yes\n");for(int i=1;i<=n;i++) print(b[i]),put(' ');
}
signed main()
{
    int T=1;
    // T=read();
    while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1039A)

## 思路

给出一种非常弱智的线段树解法。

设初始的 $ans_i=a_i+t$，则序列：$p_i=i$ 一定满足条件，容易发现若 $x_i<i$ 肯定无解。

如果我们想要让 $x_i$ 满足条件，那么一种构造方式就是令 $p_j=j-1\ (i<j \le x_i)$，所以对于所有的 $ans_{j-1}$ 都要满足 $ans_{j-1} \ge a_{j}+t$，一种弱智的想法就是直接线段树区间覆盖。

最后注意判断一下无解，如果发现当前的 $x_i$ 可以取到更大，那么也是无解的。

如此模拟即可。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mid ((l+r)>>1)
#define sqr(x) ((x)*(x))
#define all(x) (x).begin(),(x).end()
#define Tim ((double)clock()/CLOCKS_PER_SEC)
#define lowbit(x) (x&-x)
int const N=2e5+10;
int a[N],x[N],ans[N];
struct Segment_Tree{
	#define ls (x<<1)
	#define rs (x<<1|1)
	int c[N<<2],lazy[N<<2];
	inline void pushdown(int x){
		lazy[ls]=lazy[rs]=1;
		c[ls]=c[rs]=1;
		lazy[x]=0;
	}
	inline void update(int x,int l,int r,int ll,int rr){
		if (ll<=l && r<=rr){lazy[x]=c[x]=1;return;}
		if (lazy[x]) pushdown(x);
		if (ll<=mid) update(ls,l,mid,ll,rr);
		if (mid<rr) update(rs,mid+1,r,ll,rr);
	}
	inline int query(int x,int l,int r,int p){
		if (l==r) return c[x];
		if (lazy[x]) pushdown(x);
		if (p<=mid) return query(ls,l,mid,p);
		else return query(rs,mid+1,r,p);
	}
}T;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,t;cin>>n>>t;
	for (int i=1;i<=n;++i) cin>>a[i];
	for (int i=1;i<=n;++i) cin>>x[i];
	for (int i=1;i<=n;++i){
		if (x[i]<i){cout<<"No\n";return 0;}
		if (i==x[i]) continue;
		T.update(1,1,n,i,x[i]-1);
	}
	for (int i=1;i<=n;++i){
		ans[i]=a[i]+t;
		ans[i]=max(ans[i-1]+1,ans[i]);
		if (T.query(1,1,n,i)) ans[i]=max(ans[i],a[i+1]+t);
	}
	for (int i=1;i<=n;++i)
		if (x[i]!=n && ans[x[i]]>=a[x[i]+1]+t){cout<<"No\n";return 0;}
	cout<<"Yes\n";
	for (int i=1;i<=n;++i) cout<<ans[i]<<' ';
	cout<<'\n';
	return 0;
}
```

---

## 作者：liuyifan (赞：0)

## 一道较简单的构造题

思路:对于每一个i(1<=i<=n),x[i]>=i,所以设第i个车可以停在x[i]处,则对于j(i<j<=x),令车j停在j-1处,即b[j-1]>=a[j]+t.然后直接构造即可,构造不了就输出NO.

code:
```
#include<bits/stdc++.h>
#define ll long long//注意数据范围,int会炸(同NOIP2018普及T2) 
#define reg register//玄学加速作用 
using namespace std;
ll a[200005],b[200005],x[200005],n,t,tmp;//long long警告! 
int main()
{
	scanf("%lld%lld",&n,&t);//不加lld会听取WA声一片 
	for(reg int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(reg int i=1;i<=n;i++)scanf("%lld",&x[i]);//同上 
	for(reg int i=1;i<=n;i++)
    if(x[i]<x[i-1]||x[i]<i)return puts("NO"),0;//无法构造,输出NO 
    for(reg int i=1;i<=n-1;i++)b[i]=a[i+1]+t-!(x[i]==x[i+1]);
    b[n]=a[n]+t+1;
    tmp=n;//构造完成 
    for(reg int i=n;i>=1;i--)
    {
        if(tmp!=x[i]||b[i]<=b[i-1])return puts("NO"),0;//构造不对就输出NO 
        if(b[i-1]-a[i]<t)tmp=i-1;
    }//检验构造 
    puts("YES");
    for(reg int i=1;i<=n;i++)printf("%lld ",b[i]);//输出构造后的方案 
    return 0;
}
```
## 为了不变棕,拒绝抄袭

---


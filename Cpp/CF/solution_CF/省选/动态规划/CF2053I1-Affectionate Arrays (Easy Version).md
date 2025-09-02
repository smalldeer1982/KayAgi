# Affectionate Arrays (Easy Version)

## 题目描述

你是信的开头，诗的内容，童话的结尾。

—— ilem，[《勾指起誓》](https://www.bilibili.com/video/BV1Jb411U7u2/)



本题是简单版问题。两个版本的区别在于，此版本中你需要计算数组的最小长度。只有当你解决了所有版本的问题时才能进行 hack 操作。

Iris 珍视一个整数数组 $a_1, a_2, \ldots, a_n$。她知道这个数组有一个有趣的性质：所有元素的最大绝对值不超过所有元素的和，即 $\max(\lvert a_i\rvert) \leq \sum a_i$。

Iris 定义数组的**无聊值**为其最大子数组$^{\text{∗}}$和。

Iris 的生日即将到来，Victor 打算送她另一个数组 $b_1, b_2, \ldots, b_m$ 作为礼物。出于某些看似明显的原因，他决定数组 $b_1, b_2, \ldots, b_m$ 应满足以下条件：

- $a_1, a_2, \ldots, a_n$ 必须是 $b_1, b_2, \ldots, b_m$ 的子序列$^{\text{†}}$。
- 两个数组的和相同，即 $\sum\limits_{i=1}^n a_i = \sum\limits_{i=1}^m b_i$。
- 数组 $b$ 的无聊值尽可能小。
- 在所有具有最小无聊值的数组中，数组 $b$ 的长度（即 $m$）尽可能小。此时，Iris 将立刻理解他的心意！

即使有上述约束，可能的礼物仍然太多。因此 Victor 请你计算满足所有条件的数组 $b_1, b_2, \ldots, b_m$ 的长度 $\boldsymbol{m}$。他承诺：如果你成功帮助他，他会与你分享 Iris 的生日蛋糕。

注意：由于输入规模较大，你可能需要针对此问题进行优化。

例如，在 C++ 中，只需在 main() 函数开头添加以下代码：

```cpp
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}
```

$^{\text{∗}}$ 若数组 $c$ 可通过删除数组 $d$ 开头和末尾的若干（可能为零或全部）元素得到，则称 $c$ 是 $d$ 的子数组。

$^{\text{†}}$ 若序列 $c$ 可通过删除序列 $d$ 中任意位置的若干（可能为零或全部）元素得到，则称 $c$ 是 $d$ 的子序列。

## 说明/提示

第一个测试用例中，$a=[1, 2, 3, 4]$。唯一满足所有条件的数组 $b$ 是 $[1, 2, 3, 4]$，因此输出 4。

第二个测试用例中，$a=[2, -3, 2, 2]$。可能的数组 $b$ 包括 $[1, 2, -3, 2, -1, 2]$ 和 $[2, 1, -3, 2, -1, 2]$，因此输出 6。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
4
1 2 3 4
4
2 -3 2 2
10
2 -7 6 3 -1 4 2 -5 8 -4
20
4 -2 4 3 -2 1 5 2 3 6 -5 -1 -4 -2 -3 5 -3 1 -4 1```

### 输出

```
4
6
14
25```

# 题解

## 作者：IvanZhang2009 (赞：6)

注意到 $\max(|a_i|)\le \sum a_i$ 的限制。经过合理猜测可以发现 $b$ 最大子段和最小就是 $\sum a_i$，取整个序列即可得到。考虑一个深刻的充要条件：设 $s=\sum a_i$，则 $b_i$ 的任意前缀和值域都在 $[0,s]$。

- 考虑一个前缀 $a_{1\dots k}$ 的和 $<0$，则取后面的部分的和超过了 $s$。
- 考虑一个前缀 $a_{1\dots k}$ 的和 $>s$，则取这段前缀的和超过了 $s$。
- 满足值域限制的条件下，一个子段和可以描述成两个前缀和相减的形式，显然这个差也在 $[-s,s]$ 中。

所以这是充要的。我们考虑直接对前缀和设计 dp：$f_{i,j}$ 表示长度为 $i$ 的前缀加若干个数得到和为 $j$ 的前缀，最少需要添加多少个数。考虑转移，需要观察题目的特殊性质：考虑每两个数之间以及头尾的总共 $n+1$ 个空挡，只会在每个空挡里填恰好一个数。我们不妨把开头的空用来初始化状态，令 $f_{0,i}=[i>0]$。之后转移的时候首先要求 $a_{i}+j'\in[0,s]$，然后才能找到 $k$ 令 $f_{i-1,j}\rightarrow f_{i,j+a_i+k}$。时间复杂度 $O(ns^2)$，不可接受。也可以注意到这个转移是一个区间和、区间 min 的形式，可以做到 $O(ns)$。

考虑把 $f$ 数组打个表看看，可以发现对于 $i$ 固定时，同一个 $f_{i,j}$ 在 $ j\in[0,s]$ 时只有不超过两个不同的值，且更小的那个形成一段区间。考虑归纳证明，初始时只有 $0,1$ 的不同值，且值为 $0$ 的构成区间 $[0,0]$。转移时先 ban 掉一段区间（要求 $j'+a_i\in[0,s]$），此时值更小的仍然是区间（但是可能使全局相等，需要特殊处理），然后转移后值仍然等于更小值的点相当于把原区间沿着 $a_i$ 方向平移（不加更多数，保留 $f$ 值），于是仍然是区间，可以发现剩下的部分答案都是更小值加一。我们直接 $O(1)$ 维护这些区间可以维护出 $f$ 数组最后的值，求出 $f_s$ 即是最小长度 $-n$。于是在 $O(n)$ 时间内解决了最小长度。

下面是代码。很短吧！

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int         long long
#define pii         pair<int,int>
#define all(v)      v.begin(),v.end()
#define pb          push_back
#define REP(i,b,e)  for(int i=(b);i<(int)(e);++i)
#define over(x)     {cout<<(x)<<endl;return;}
int n,s;
int a[3000005];
void Main() {
	cin>>n;s=0;
	REP(i,0,n)cin>>a[i],s+=a[i];
	int cur=0,l=0,r=0;
	REP(i,0,n){
		int L=max(0ll,-a[i]),R=min(s,s-a[i]);
		if(max(L,l)<=min(r,R))l=max(l,L),r=min(r,R);
		else l=L,r=R,++cur;
		l+=a[i];r+=a[i];
		l=max(l,0ll);r=min(r,s);
		if(l>r)l=0,r=s,++cur;
	}
	over(cur+n+(r!=s))
}
void TC() {
    int tc=1;
    cin>>tc;
	while(tc--){
		Main();
		cout.flush();
	}
}
signed main() {
	return cin.tie(0),cout.tie(0),ios::sync_with_stdio(0),TC(),0;
}
```

当然这篇题解到这里还没有结束。原题是一个计数，但是因为各种原因被删掉了。这里也一起分享出来。

原 std 的做法是假的。注意到在 I1 的做法中，我们在原序列的空隙中插入新的数，但是如果我们**钦定方案不同当且仅当其插入的方式不同**，即把一个 $x$ 插在原序列中一个 $x$ 的左边和右边，在原定义中算同一种序列，但是在新版题意中认为这不算同一种。如何解决这个改变题意后的问题呢？

> 扩展 I1 的做法，考虑方案数的转移，设 $g_{i,j}$ 为同定义下的方案数。区间平移的部分，$g$ 的转移仍然是区间平移，并在下文称之为【特殊区间】。不妨考虑 $a_i>0$ 的情况，一开始 ban 掉的是 $[0,a_i-1]$ 的部分，而后面补进来这部分的时候，这些的 $g$ 值都相等，等于原本 $g$ 中 $f$ 更大的所有值的 $g$ 和。而对于既不是这一块又不是特殊区间的部分，将会在原值的基础上加上上面对应的 $g$ 和。
>
> 总结一下就是前后缀删点，前后缀加值为 $0$ 的连续段，对非特殊区间做区间加。我们不进行区间平移，而是维护 $tag$ 表示区间的平移量即可把问题静态化，做到 $O(s\log s)$，但是仍然不可接受。
>
> 我们观察转移的过程，发现少有单点操作，都是对着整段的区间做操作，例如前后缀塞一个连续段，前后缀删连续段，这启发我们不仅是 $f$，$g$ 的值也可以形成若干段连续段。经过打表验证，可以发现 $g$ 的值确实形成 $O(n)$ 个连续段。由于要支持前后缀操作，我们直接开一个 `deque` 维护所有连续段的所有信息，包括左右端点和每个点的 $g$ 值。为了维护信息，我们需要维护：$tpos$ 表示当前区间整体平移的偏移量；$l,r$ 表示特殊区间为 $[l+tpos,r+tpos]$；$tv_1,tv_2$ 表示特殊和非特殊区间的全局加的标记（需要支持这些全局加）；$s_1,s_2$ 表示特殊和非特殊区间的权值和（需要支持整体加，而加的值就是非特殊区间的答案和）。注意到这些都可以在维护 `push`，`pop` 操作的同时维护出来。一个大细节是 pop 区间后可能会出现全局 $f$ 相等的情况，即 $[l,r]$ 变成整区间，此时会用到维护的非特殊区间的全局加标记和全局和，所以才两个都要维护。每个连续段被插入一次删除一次，`push` 次数为 $n$，于是时间复杂度均摊 $O(n)$。可以讨论 $a_i$ 的正负性转移。

给出我的实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MOD         998244353
#define int         long long
#define pii         pair<int,int>
#define all(v)      v.begin(),v.end()
#define pb          push_back
#define REP(i,b,e)  for(int i=(b);i<(int)(e);++i)
#define over(x)     {cout<<(x)<<endl;return;}
#define deal(v)     sort(all(v));v.erase(unique(v.begin(),v.end()),v.end())
#define lbound(v,x) lower_bound(all(v),x)-v.begin()
struct interval{
	int l,r,g;
	int calc(int tg=0){return ((r-l+1)*(tg+g))%MOD;}
};
int n,s;
int a[3000005];
#define inside(x) (x.l>=l&&x.r<=r)
void Main() {
	cin>>n;s=0;
	REP(i,0,n)cin>>a[i],s+=a[i];
	if(s<*max_element(a,a+n))assert(0)
	if(s<-*min_element(a,a+n))assert(0);
	if(!s)over(1)
	deque<interval>dq;
	dq.pb({0,0,1});dq.pb({1,s,1});
	int tpos=0,tval=0,l=0,r=0,sum1=1,sum2=s,tv2=0;
	REP(i,0,n){
		if(a[i]>=0){
			while(dq.size()&&dq.back().l+tpos>s-a[i]){
				if(inside(dq.back()))sum1-=dq.back().calc(tv2);
				else sum2-=dq.back().calc(tval);
				dq.pop_back();
			}
			if(dq.back().r+tpos>s-a[i]){
				if(inside(dq.back()))sum1-=(dq.back().g+tv2)*(dq.back().r+tpos-(s-a[i]))%MOD;
				else sum2-=(dq.back().r+tpos-(s-a[i]))*(tval+dq.back().g)%MOD;
				dq.back().r=s-a[i]-tpos;
			}
			sum1=(MOD+sum1%MOD)%MOD;
			sum2=(MOD+sum2%MOD)%MOD;
			r=min(r,s-a[i]-tpos);
			if(l>r){
				l=dq.front().l;r=dq.back().r;
				sum1=sum2;sum2=0;tv2=tval;tval=0;
			}
			if(a[i])dq.push_front({dq[0].l-a[i],dq[0].l-1,(MOD-tval)%MOD});
			tpos+=a[i];(tval+=sum1)%=MOD;(sum2+=sum1*(s+1-(r-l+1)))%=MOD;
		}else{
			a[i]*=-1;
			while(dq.size()&&dq.front().r+tpos<a[i]){
				if(inside(dq.front()))sum1-=dq.front().calc(tv2);
				else sum2-=dq.front().calc(tval);
				dq.pop_front();
			}
			if(dq.front().l+tpos<a[i]){
				if(inside(dq.front()))sum1-=(dq.front().g+tv2)*(a[i]-dq.front().l-tpos)%MOD;
				else sum2-=(a[i]-dq.front().l-tpos)*(dq.front().g+tval)%MOD;
				dq.front().l=a[i]-tpos;
			}
			sum1=(MOD+sum1%MOD)%MOD;
			sum2=(MOD+sum2%MOD)%MOD;
			l=max(l,a[i]-tpos);
			if(l>r){
				l=dq.front().l;r=dq.back().r;
				sum1=sum2;sum2=0;tv2=tval;tval=0;
			}
			dq.push_back({dq.back().r+1,dq.back().r+a[i],(MOD-tval)%MOD});
			tpos-=a[i];(tval+=sum1)%=MOD;(sum2+=sum1*(s+1-(r-l+1)))%=MOD;
		}
	}
    cout<<(dq.back().g+(inside(dq.back())?tv2:tval))%MOD<<endl;
}
void TC() {
    int tc=1;
    cin>>tc;
	while(tc--){
		Main();
		cout.flush();
	}
}
signed main() {
	return cin.tie(0),cout.tie(0),ios::sync_with_stdio(0),TC(),0;
}
```

其实这篇题解到这里还是没有结束。作为名义上的 writer，出锅之后我还得修，于是考虑原版题意的计数。能否改进 std 的做法呢？尝试对于同一个数的连续段 dp，发现似乎很困难。irris 和我都放弃了。

我们从问题的本质上入手。不妨直接对着序列 $b$ 做 dp，并把子序列的限制放到状态中。设 $f(i,j,k)$ 表示填了 $b$ 序列的前 $i$ 项，匹配序列 $a$ 最多能匹配 $j$ 项，当前前缀和为 $k$ 的方案数。我们不妨先套用 I1 的 dp 求出这个最小长度 $m$，这样状态数是 $O(mns)=O(n^2s)$。转移时可以枚举下一个数填什么，是 $O(s)$ 的。提供一个代码主要部分。

```cpp
int n;
int a[3000005];
int dp[105][105][1005];
int s;
int qlen(){
	int cur=0,l=0,r=0;
	REP(i,0,n){
		int L=max(0ll,-a[i]),R=min(s,s-a[i]);
		if(max(L,l)<=min(r,R))l=max(l,L),r=min(r,R);
		else l=L,r=R,++cur;
		l+=a[i];r+=a[i];
		l=max(l,0ll);r=min(r,s);
		if(l>r)l=0,r=s,++cur;
	}
	return cur+(r<s)+n;
}
void Main() {
	cin>>n;
	REP(i,0,n)cin>>a[i];
	s=accumulate(a,a+n,0ll);
	int m=qlen();
	REP(i,0,m+1){
		REP(j,0,n+1){
			REP(l,0,s+1)dp[i][j][l]=0;
		}
	}
	dp[0][0][0]=1;
	REP(i,0,m){
		REP(j,0,n+1){
			REP(l,0,s+1)if(dp[i][j][l]){
				REP(p,-l,s-l+1){
					int j2=j+(j<n&&a[j]==p);
					(dp[i+1][j2][l+p]+=dp[i][j][l])%=MOD;
				}
			}
		}
	}
	cout<<dp[m][n][s]<<endl;
}
```

可以发现这个 $O(s)$ 转移容易做到 $O(1)$。具体地，我们转移 $f(i,j,k)$，先接收所有 $f(i-1,j,l)$ 的值（毕竟都可以加一个数得到），然后再考虑其它特殊的。如果加入一个数之后可以匹配，就减掉 $f(i-1,j,l-a_j)$。如果是加入一个数之后匹配了，就加上 $f(i-1,j-1,l-a_{j-1})$。时间复杂度 $O(n^2s)$。

```cpp
int n;
int a[3000005];
int dp[105][105][1005];
int s;
int qlen();//和上面相同，省略
void Main() {
	cin>>n;
	REP(i,0,n)cin>>a[i];
	s=accumulate(a,a+n,0ll);
	int m=qlen();
	REP(i,0,m+1){
		REP(j,0,n+1){
			REP(l,0,s+1)dp[i][j][l]=0;
		}
	}
	dp[0][0][0]=1;
	REP(i,0,m){
		REP(j,0,n+1){
			int sum=0;
			REP(l,0,s+1){
				sum+=dp[i][j][l];
			}
			REP(l,0,s+1){
				dp[i+1][j][l]=sum;
				if(j<n&&l>=a[j]&&l-a[j]<=s)dp[i+1][j][l]-=dp[i][j][l-a[j]];
				if(j>0&&l>=a[j-1]&&l-a[j-1]<=s)dp[i+1][j][l]+=dp[i][j-1][l-a[j-1]];
				(dp[i+1][j][l]+=MOD)%=MOD;
			}
		}
	}
	cout<<dp[m][n][s]<<endl;
}
```

考虑原做法的连续段想法。我们把 $s$ 那一维用连续段刻画，即将其划分成 $\rm{poly}(n)$ 个方案数相同的连续段，然后利用归并的方式合并即可。细节相当于把 $f(i,j-1)$ 和 $f(i,j)$ 分别平移对应距离后相减，然后做全局加。时间复杂度 $O(n^{k+2})$，其中长度为 $s$ 的数组可以划分成 $O(n^k)$ 段。$k$ 具体是多少我也不太懂，反正至少是 $2$。

```cpp
int n;
int a[3000005];
int s;
struct structures{
    int l,r,val;
};
#define vs vector<structures>
vs f[30005],g[30005];
int qlen();//和上面相同，省略
vs mover(vs a,int x){
    if(!x)return a;
    vs b;
    if(x>0)b.pb({0,x-1,0});
    for(auto [l,r,val]:a){
        int L=l+x,R=r+x;
        L=max(L,0ll);R=min(R,s);
        if(L<=R)b.pb({L,R,val});
    }
    if(x<0)b.pb({s+x+1,s,0});
    return b;
}
vs operator -(vs a,vs b){
    vector<int>t;
    int x=0,y=0,n=a.size(),m=b.size();
    while(x<n&&y<m){
        if(a[x].l==b[y].l)t.pb(a[x].l),++x,++y;
        else if(a[x].l<b[y].l)t.pb(a[x++].l);
        else t.pb(b[y++].l);
    }
    while(x<n)t.pb(a[x++].l);
    while(y<m)t.pb(b[y++].l);
    n=t.size();t.pb(s+1);
    vs c(n,{0,0,0});
    REP(i,0,n)c[i].l=t[i],c[i].r=t[i+1]-1;
    x=0;
    for(auto [l,r,val]:a){
        while(c[x].r<l)++x;
        while(x<n&&c[x].l>=l&&c[x].r<=r)c[x].val+=val,++x;
    }
    x=0;
    for(auto [l,r,val]:b){
        while(c[x].r<l)++x;
        while(x<n&&c[x].l>=l&&c[x].r<=r)c[x].val+=MOD-val,++x;
    }
    REP(i,0,n)c[i].val%=MOD;
    a.clear();
    int lstval=-1;
    for(auto [l,r,val]:c){
		if(val==lstval)a[a.size()-1].r=r;
		else a.pb({l,r,lstval=val});
	}
    return a;
}
void Main() {
	cin>>n;
	REP(i,0,n)cin>>a[i];
	s=accumulate(a,a+n,0ll);
	int m=qlen();
    REP(i,0,n+1){
        f[i].clear();
        g[i].clear();
        if(i)g[i]=vs(1,{0,s,0});
        else{
            g[i].pb({0,0,1});g[i].pb({1,s,0});
        }
    }
    REP(i,0,m){
        for(int j=n;j>=0;--j){
            int sum=0;
            for(auto [l,r,val]:g[j])(sum+=(r-l+1)%MOD*val)%=MOD;
            vs s1=j<n? mover(g[j],a[j]):vs(1,{0,s,0}),s2=j? mover(g[j-1],a[j-1]):vs(1,{0,s,0});
            g[j]=s2-s1;
            for(auto &l:g[j])(l.val+=sum)%=MOD;
        }
    }
    int x=g[n].size()-1;
	cout<<g[n][x].val<<endl;
}
```

然后再加入最优性。注意到对于一个 $i$，使 $f$ 有值的 $j$ 一定是一个前缀 $j\le R_i$。这可以理解为，给定你 $i$ 个可以加入的数，最多能匹配 $a$ 中的几位。这个翻转之后可以变成：对于 $a$ 的每个前缀，它最少添加几位。

同理，$j$ 也应该有下界 $j\ge L_i$。这可以理解为，对于这个后缀，你只有若干个数可以加，最长能匹配的后缀，也就是最短需要能匹配的前缀。可以通过倒着做一样的 dp 解决。根据“两个数之间只能插一个”的理论，可以发现 $R_i-L_i+1\le 2$，也就是对于一个 $i$ 只有最多 $2$ 个 $j$ 是有用的。只转移这些，可以证明 $s$ 那一维只有 $O(n^2)$ 且跑不满个连续段，于是时间复杂度 $O(n^3)$。

```cpp
int n;
int a[3000005];
int s;
int mnm[3000005],mxm[3000005];
struct structures{
    int l,r,val;
};
#define vs vector<structures>
vs f[3000005],g[3000005];
int m;
int qlen(){
	int cur=0,l=0,r=0;
    mnm[0]=0;
	REP(i,0,n){
		int L=max(0ll,-a[i]),R=min(s,s-a[i]);
		if(max(L,l)<=min(r,R))l=max(l,L),r=min(r,R);
		else l=L,r=R,++cur;
		l+=a[i];r+=a[i];
		l=max(l,0ll);r=min(r,s);
		if(l>r)l=0,r=s,++cur;
        mnm[i+1]=cur+i+1;
	}
	return cur+(r<s)+n;
}
void getdp_back(){
	int cur=0,l=0,r=0;
    mxm[n]=m;
	for(int i=n-1;i>=0;--i){
		int L=max(0ll,-a[i]),R=min(s,s-a[i]);
		if(max(L,l)<=min(r,R))l=max(l,L),r=min(r,R);
		else l=L,r=R,++cur;
		l+=a[i];r+=a[i];
		l=max(l,0ll);r=min(r,s);
		if(l>r)l=0,r=s,++cur;
        mxm[i]=m-n-cur+i;
	}
}
vs mover(vs a,int x){
    if(!x)return a;
    vs b;
    if(x>0)b.pb({0,x-1,0});
    for(auto [l,r,val]:a){
        int L=l+x,R=r+x;
        L=max(L,0ll);R=min(R,s);
        if(L<=R)b.pb({L,R,val});
    }
    if(x<0)b.pb({s+x+1,s,0});
    return b;
}
vs operator -(vs a,vs b){
    vector<int>t;
    int x=0,y=0,n=a.size(),m=b.size();
    while(x<n&&y<m){
        if(a[x].l==b[y].l)t.pb(a[x].l),++x,++y;
        else if(a[x].l<b[y].l)t.pb(a[x++].l);
        else t.pb(b[y++].l);
    }
    while(x<n)t.pb(a[x++].l);
    while(y<m)t.pb(b[y++].l);
    n=t.size();t.pb(s+1);
    vs c(n,{0,0,0});
    REP(i,0,n)c[i].l=t[i],c[i].r=t[i+1]-1;
    x=0;
    for(auto [l,r,val]:a){
        while(c[x].r<l)++x;
        while(x<n&&c[x].l>=l&&c[x].r<=r)c[x].val+=val,++x;
    }
    x=0;
    for(auto [l,r,val]:b){
        while(c[x].r<l)++x;
        while(x<n&&c[x].l>=l&&c[x].r<=r)c[x].val+=MOD-val,++x;
    }
    REP(i,0,n)c[i].val%=MOD;
    a.clear();
    int lstval=-1;
    for(auto [l,r,val]:c){
		if(val==lstval)a[a.size()-1].r=r;
		else a.pb({l,r,lstval=val});
	}
    return a;
}
void Main() {
	cin>>n;
	REP(i,0,n)cin>>a[i];
	s=accumulate(a,a+n,0ll);
	m=qlen();getdp_back();
    REP(i,0,n+1){
        g[i].clear();
        if(i)g[i]=vs(1,{0,s,0});
        else{
            g[i].pb({0,0,1});g[i].pb({1,s,0});
        }
    }
	int xl=0,xr=0;
    REP(i,0,m){
    	int lxl=xl,lxr=xr;
    	while(xl<=n&&mxm[xl]<i+1)++xl;
    	while(xr+1<=n&&mnm[xr+1]<=i+1)++xr;
        for(int j=xr;j>=xl;--j){
            ++cnt;
            int sum=0;
            for(auto [l,r,val]:g[j])(sum+=(r-l+1)%MOD*val)%=MOD;
            vs s1=j<n? mover(g[j],a[j]):vs(1,{0,s,0}),s2=j? mover(g[j-1],a[j-1]):vs(1,{0,s,0});
            g[j]=s2-s1;
            for(auto &l:g[j])(l.val+=sum)%=MOD;
        }
        REP(i,lxl,xl)g[i]=vs(1,{0,s,0});
    }
    int x=g[n].size()-1;
	cout<<g[n][x].val<<endl;
}
```

很抱歉实力有限，当天的补救中我只能做到这了。当时是赶工到凌晨五点才写完的这个东西，第二天发现没人会更优的，做不到 $3\times 10^6$ 的范围，于是只能删掉这个题了。

如果大家有更好的想法欢迎沟通。

---

## 作者：Daniel1234 (赞：4)

写篇题解记录一下考场思路。

# 思路

首先我们发现将折线图画出来，一定是一条起点为 $(0,0)$，而终点为 $(n, sum)$ 的折线。

所以猜测最终所有前缀都在 $0 \sim sum$ 之间。

从前往后考虑每一位，记录当前前缀，当前插入次数，维护的话就是加入 $a_{i+1}$，看有没有超出 $[0,sum]$，超出的话答案加 $1$，当前前缀变为超出边界。

然后测样例，发现假完了，于是我们想到可以记录 $l,r$，表示当前所有可行前缀中的最小可能值和最大可能值。

转移的话注意需要插入时插入的数不能爆出边界。

# code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T, n;
int a[3000005];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> T;
    while(T--){
        cin >> n;
        int sum = 0;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            sum += a[i];
        }
        int ans = 0;
        int l = 0, r = 0;
        for(int i = 1; i <= n; i++){
            int pl = l, pr = r;
            l += a[i], r += a[i];
            if(l < 0)l = 0;
            if(r > sum)r = sum;
            if(l > r){
                ans++;
                l = max(0ll, a[i]), r = min(sum, sum + a[i]);
            }
        }
        ans += r < sum;
        ans += n;
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：MarSer020 (赞：2)

Irris 怎么这么会出题 /bx

$\Large\text{Solution}$

定义 $sum=\sum a_i,s_i=\sum\limits_{j=1}^ia_i$。

首先观察到有 $b$ 的最大子段和至少为 $sum$，考虑能不能使其为 $sum$。

我们发现 $b$ 相当于在 $a$ 的基础上插入若干个数，那么我们可以先令所有 $b_i=a_i$，然后在每个满足 $s_i\not\in[0,sum]$ 的位置 $i$ 前面插入一个值 $x\in[-sum,sum]$，使得 $s_{i-1}+x,s_i+x\in[0,sum]$，然后令 $\forall j\in[i,n],s_i\leftarrow s_i+x$。注意到由于有 $\max(\lvert a_i\rvert)\le sum$，那么 $\lvert s_i-s_{i-1}\rvert=\lvert a_i\rvert\le sum$，故这样的 $x$ 恒存在。最后在 $m$ 位置之后插入 $sum-s_m$ 即可使得 $b$ 满足题目中得条件。

我们通过给出构造证明了 $b$ 的最大子段和为 $sum$。类似的，我们可以设出 $f_{i,j}$ 表示现在考虑到 $s_i$，且对于 $p\in[i,n],s_p=j+\sum\limits_{k=1}^pa_k$ 时，最少插入多少个数。那么有 $f_{i,j}=\min\{f_{i-1,j},\min\limits_{k\ne j}\{f_{i-1,k}\}+1\}$。于是我们得到了一个时间复杂度为 $O(n^2V)$ 的做法。

考虑进一步优化这个做法，容易证明对于每个 $f_i$ 有 $\max\{f_i\}-\min\{f_i\}\le1$，且较小的一种数值形成一段连续的区间。那么我们每次维护较小值形成的区间即可。时间复杂度 $O(n)$。

$\Large\text{Code}$

```cpp
#include<bits/stdc++.h>
#define int int64_t
using namespace std;
int n,T,a[3000005],pl,pr,val;
int32_t main(){
	ios::sync_with_stdio(0),cin.tie(0),cin>>T;
	while(T--){
		cin>>n,pl=pr=val=0;
		for(int i=1;i<=n;i++)
			cin>>a[i],a[i]+=a[i-1];
		for(int i=1,l,r;i<=n+1;i++){
			if(i<=n)
				l=max(-a[i-1],-a[i]),r=min(a[n]-a[i-1],a[n]-a[i]);
			else
				l=r=0;
			pl=max(pl,l),pr=min(pr,r);
			if(pl>pr)
				pl=l,pr=r,val++;
		}
		cout<<val+n<<'\n';
	}
	return 0;
}
```

---


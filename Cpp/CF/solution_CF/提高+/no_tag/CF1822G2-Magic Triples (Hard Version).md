# Magic Triples (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version, $ a_i \le 10^9 $ .

For a given sequence of $ n $ integers $ a $ , a triple $ (i, j, k) $ is called magic if:

- $ 1 \le i, j, k \le n $ .
- $ i $ , $ j $ , $ k $ are pairwise distinct.
- there exists a positive integer $ b $ such that $ a_i \cdot b = a_j $ and $ a_j \cdot b = a_k $ .

Kolya received a sequence of integers $ a $ as a gift and now wants to count the number of magic triples for it. Help him with this task!

Note that there are no constraints on the order of integers $ i $ , $ j $ and $ k $ .

## 说明/提示

In the first example, there are $ 6 $ magic triples for the sequence $ a $ — $ (2, 3, 5) $ , $ (2, 5, 3) $ , $ (3, 2, 5) $ , $ (3, 5, 2) $ , $ (5, 2, 3) $ , $ (5, 3, 2) $ .

In the second example, there is a single magic triple for the sequence $ a $ — $ (2, 1, 3) $ .

## 样例 #1

### 输入

```
7
5
1 7 7 2 7
3
6 2 18
9
1 2 3 4 5 6 7 8 9
4
1000 993 986 179
7
1 10 100 1000 10000 100000 1000000
8
1 1 2 2 4 4 8 8
9
1 1 1 2 2 2 4 4 4```

### 输出

```
6
1
3
0
9
16
45```

# 题解

## 作者：Hisaishi_Kanade (赞：7)

[easy version](https://www.luogu.com.cn/blog/Etinorally/solution-cf1822g1)。

发现 $n$ 范围相同，和 easy ver. 类似的，当 $a_i\le 10^6$ 依然可以根号猛冲。

当 $10^6<a_i\le10^9$ 时我们要另辟蹊径在仍在 $\sqrt {10^6}$ 范围内求解。

我们发现，对于 $a_i\in[10^6,10^9]$，乘上一个不超过 $10^3$ 的数则必然超过 $V=10^9$。那么我们还是枚举 $b$，只不过不是到 $\sqrt {a_i}$ 而是 $\dfrac V {a_i}$。

这样可以证明无论 $a_i$ 取范围内何值，都可以在 $10^3$ 的枚举级别求解。

换种角度理解就是类似于根号分治，钦定阈值 $k$，$a_i\le k$ 则枚举到根号，$a_i>k$ 则枚举到 $\dfrac V{a_i}$。复杂度是 $O(n\max(\sqrt k,\dfrac Vk))$。在这里，当 $k=10^6$ 取到最小值。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for(i=l; i<=r; ++i)
int n, i, j, t, x;
using ll=long long;
map<ll, ll> q;
ll va, ti;
const int Block=1e6, V=1e9;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		q.clear();
		scanf("%d", &n);
		rep(i, 1, n)
		{
			scanf("%d", &x);
			++q[x];
		}
		ll ret=0;
		for(auto& nxt : q)
		{
			va=nxt.first; ti=nxt.second;
			ret+=ti*(ti-1)*(ti-2);
			if(va<Block)
			{
				for(j=1; j*j<va; ++j)
				{
					if(j!=1 && va%j==0 && q.count(va/j) && q.count(va*j))
						ret+=q[va/j]*ti*q[va*j];
					if(va%j==0 && q.count(j) && q.count(va/j*va))
						ret+=q[j]*ti*q[va/j*va];
				}
				if(j!=1 && j*j==va && q.count(j) && q.count(va*j)) ret+=q[j]*ti*q[va*j];
			}else
			{
				for(j=2; va*j<=V; ++j)
					if(va%j==0 && q.count(va/j) && q.count(va*j))
						ret+=q[va/j]*ti*q[va*j];
			}
		}
		printf("%lld\n", ret);
	}
}
```

---

## 作者：2018ljw (赞：4)

考虑枚举中间项的值 $a_j$。

关注到值域 $V=10^9$ 时，一个数因子不超过 $1344$ 个，所以考虑一些复杂度 $\sum d(a)$ 的东西。

发现公比 $b$ 一定是 $a_j$ 的约数，所以考虑再枚举这个公比 $b\mid a_j$，这样三项均可确定，$b\neq 1$ 时只需把出现次数乘在一起，$b=1$ 时单独计算即可。

现在问题来了：怎么找约数。

根号肯定不行，Pollard's Rho 虽然可以但写着麻烦。考虑值域分治。

设定阈值 $B$，当 $a\le B$ 时采用根号暴力分解。当 $a>B$ 时，关注到有用的 $b$ 最多不超过 $\frac VB$ 个，直接暴力枚举。

这样的复杂度是 $\sqrt B+\frac VB$，在 $B=V^{\frac 23}=10^6$ 时取到最优。总复杂度 $O(n\sqrt[3]V)$。

然后是一些优化。

$a\le B$ 的部分可以通过线性筛预处理最小质因子做到 $O(\log a)$ 分解质因数，然后爆搜合并，可以优化掉 $\le B$ 部分的根号。这样 $B$ 就可以开的更大，单次复杂度为 $\max_{i\le B}\{d(i)\}+\frac VB$，前者可近似视为 $\sqrt[3]B$，这样时间复杂度 $O(n\sqrt[4]V)$，空间复杂度 $O(V^{\frac 34})$。

代码是 $O(n\sqrt[3]V)$ 的版本，由于用 `unordered_map` 当桶所以时间卡的比较紧。[link](https://codeforces.com/contest/1822/submission/209146197)。



---

## 作者：_•́へ•́╬_ (赞：4)

## 思路

先去重。

直接枚举最小值和公比。

理想的枚举量大概是酱紫的：
$$
\sum\limits_{i=1}^{200000}\sqrt{10^9\over i}
$$
这个当然是能过的。

遗憾的是这里是 CF，有多测。实际是酱紫的：
$$
10^4\times\sum_{i=1}^{20}\sqrt{10^9\over i}
$$
这个能过就怪了。所以对于 $n$ 比较小的数据，跑 $\mathcal O(n^2)$ 的做法。

优化：这个题统计一个数出现了几次，必然带 $\log$。但是，如果原序列中没出现过这个数，就不需要数它。这个 `bitset` 一下就好了。快些。

其实这个题枚举最小的，中间的，最大的，都能做。

## code

```cpp
#include<stdio.h>
#include<algorithm>
#include<bitset>
#define int long long
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int t,n,m,a[200009],b[200009],ans;bitset<1000000001>v;
struct __readt__{inline __readt__(){read(t);}}_readt___;
inline int count(const int&i)
	{return v[i]?upper_bound(a,a+n,i)-lower_bound(a,a+n,i):0;}
main()
{
	read(n);for(int i=0;i<n;read(a[i++]));
	sort(a,a+n);for(int i=0;i<n;b[i]=a[i],++i);
	m=unique(b,b+n)-b;ans=0;
	for(int i=0;i<m;v[b[i++]]=1);
	for(int i=0,cnt;i<m;++i)cnt=count(b[i]),ans+=cnt*(cnt-1)*(cnt-2);
	if(m<100)
	{
		for(int i=0,cnt;i<m;++i)
		{
			cnt=0;
			for(int j=i+1;j<m&&b[j]*(b[j]/b[i])<=1000000000;++j)
				if(!(b[j]%b[i]))cnt+=count(b[j])*count(b[j]*(b[j]/b[i]));
			ans+=cnt*count(b[i]);
		}
		goto nxt;
	}
	for(int i=0,cnt;i<m;v[b[i++]]=0)
	{
		cnt=0;
		for(int j=2,u;b[i]*j*j<=1000000000;++j)
		{
			u=count(b[i]*j);
			if(u)cnt+=u*count(b[i]*j*j);
		}
		ans+=cnt*count(b[i]);
	}
	nxt:printf("%lld\n",ans);if(--t)main();
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

[//]:#(我是弱智。)

枚举中间项 $x$，公比为 $y$，那么要求 $\dfrac{x}{y},x,xy$ 都要存在，即 $x\in a,y\mid x,xy\le V$。

若枚举 $x$ 的因子作为 $y$，复杂度为 $\sqrt x$；若利用 $xy\le V$ 枚举合法 $y$，复杂度为 $\dfrac{V}{x}$。

如何平衡两部分复杂度？经典技巧：阈值分治。取 $T=V^{\frac{2}{3}}$，当 $x\le T$ 跑第一种，否则跑第二种。

时间复杂度：$O(nV^{\frac{1}{3}})$。

# Code

```cpp
#include<bits/stdc++.h>
std::map<int,int>mp;
int T,n;
long long ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		mp.clear();
		for(int i=1,x;i<=n;++i)
			scanf("%d",&x),++mp[x];
		ans=0;
		for(const auto&i:mp){
			ans+=i.second*(i.second-1ll)*(i.second-2);
			if(i.first<=1000000){
			for(int j=2;j*j<=i.first;++j){
				if(i.first%j)continue;
				ans+=(mp.count(i.first/j)?mp[i.first/j]:0)*1ll*i.second*(mp.count(i.first*j)?mp[i.first*j]:0);
				if(j*j!=i.first&&1ll*i.first*i.first/j<=1000000000)
					ans+=(mp.count(j)?mp[j]:0)*1ll*i.second*(mp.count(1ll*i.first*i.first/j)?mp[1ll*i.first*i.first/j]:0);
			}
			if(i.first!=1&&i.first<=31622)ans+=(mp.count(1)?mp[1]:0)*1ll*i.second*(mp.count(i.first*i.first)?mp[i.first*i.first]:0);
			}else{
			for(int j=2;i.first*j<=1000000000;++j)
				if(!(i.first%j))
					ans+=(mp.count(i.first/j)?mp[i.first/j]:0)*1ll*i.second*(mp.count(i.first*j)?mp[i.first*j]:0);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：kkxacj (赞：0)

有趣的根号分治。

#### 思路

转化一下限制变为 $a_i \times b = a_j,a_j\times b=a_z$，设 $t = 10^9,T = 10^6$。

很容易想到的一个暴力是 `map` 存权值为 $v$ 的数出现了几次，然后枚举一个 $b$，然后枚举其中一个数，我枚举的是 $a_j$，由于值域 $\le t$，每个数的复杂度为 $\frac{t}{a_i} $。

发现 $b$ 一定为 $a_i$ 的因数，考虑求出所有 $a_i$ 的因数去计算，每个数的复杂度 $\sqrt{a_i} $。

每个数的复杂度就是 $\sqrt{a_i} $ 或者 $\frac{t}{a_i} $。

发现当 $a_i \le T$，考虑跑 $\sqrt{a_i} $ 的，否则跑 $\frac{t}{a_i} $ 的，时间复杂度大致为 $n\times \sqrt{T} \times \log$，$\log$ 是因为 `map`。

**code**


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
const int N = 2e5+10,M = 1e9;
int n,t,a,ans,b,bj,l,i;
map<int,int>mp;
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(t); b = 1e6;
	while(t--)
	{
		mp.clear();
		read(n); ans = 0; 
		for(int i = 1;i <= n;i++) read(a),mp[a]++; 
		for(auto& nxt : mp)
		{
			i = nxt.first,l = nxt.second;
			if(l >= 2) ans += l*(l-1)*(l-2);
			if(i >= b)
			{
				for(int j = 1;j*i <= M;j++)
					if(i%j==0)
					{
						if(j != 1 && mp.count(i/j) && mp.count(i*j)) ans += l*mp[i/j]*mp[i*j];
					}
			}
			else
			{
				for(int j = 1;j*j <= i;j++)
					if(i%j==0)
					{ 
						if(j != 1 && mp.count(i/j) && mp.count(i*j)) ans += l*mp[i/j]*mp[i*j];
						if(i/j != j && mp.count(j) && mp.count(i*i/j)) ans += l*mp[j]*mp[i*i/j];
					}
			} 
		}
		print(ans),pc('\n'); 
	}
	flush();
	return 0;
}
```

---

## 作者：FireRain (赞：0)

# 思路

考虑将 $a_i \leq 10^6$ 与 $a_i > 10^6$ 的情况分别计算。

发现当 $a_i \leq 10^6$ 时，可以通过枚举 $a_i$ 的因子解决，复杂度是 $\Theta(\sqrt n)$ 的。

其次当 $a_i > 10^6$ 时，可以通过枚举 $b$ 解决，复杂度是 $\Theta(\sqrt n)$ 的。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

int n;

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void solve(){
    map<int,int> vis;
    int ans = 0;
    n = read();
    for (re int i = 1;i <= n;i++){
        int x;
        x = read();
        vis[x]++;
    }
    for (auto it = vis.begin();it != vis.end();it++){
        int num = it -> first,cnt = it -> second;
        if (cnt >= 3) ans += cnt * (cnt - 1) * (cnt - 2);
        if (num <= 1e6){
            int i;
            for (i = 1;i * i < num;i++){
                if (i != 1 && num % i == 0){
                    int x = num / i,y = num * i;
                    if (vis.count(x) && vis.count(y)) ans += cnt * vis[x] * vis[y];
                }
                if (num % i == 0){
                    int x = i,y = num / i * num;
                    if (vis.count(x) && vis.count(y)) ans += cnt * vis[x] * vis[y];
                }
            }
            if (i != 1 && i * i == num){
                int x = i,y = num * num / i;
                if (vis.count(x) && vis.count(y)) ans += cnt * vis[x] * vis[y];
            }
        }
        else{
            for (re int i = 2;num * i <= 1e9;i++){
                if (num % i) continue;
                int x = num / i,y = num * i;
                if (vis.count(x) && vis.count(y)) ans += cnt * vis[x] * vis[y];
            }
        }
    }
    printf("%lld\n",ans);
}

signed main(){
    int T;
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## EV

下文中 $V$ 为 $a_i$ 的最大值。

我们对于每个值 $i\in[1,V]$ 都记录其在 $a$ 中出现的次数 $cnt_i$，这个我们可以用 `map` 来实现。

因为我们的 $n$ 和 $V$ 都不大，我们可以枚举 $a_j$ 是哪一个值，然后再去枚举 $b$ 的值。因为题目要求 $a_i \times b=a_j$，$a_i$ 是整数，所以我们的 $b$ 一定是 $a_j$ 的因子，故我们只需要枚举 $a_j$ 的因子即可。又因为 $V$ 比较小，所以 $a_j$ 的因子个数也在可以枚举的范围之内。

枚举一个 $a_j$ 的因子（不一定是质因子哦）的复杂度是 $\sqrt{V}$ 的，所以总的复杂度是 $O(n\sqrt V)$ 的，可过简单版。

---

## HV

下文中 $V$ 为 $a_i$ 的最大值。

加强版与简单版的区别就是 $V$ 的大小不同。简单版 $V=10^6$，加强版 $V=10^9$。没有写过简单版的可以去看看，也许可以打开一点思路。

[www.luogu.com.cn](https://www.luogu.com.cn/problem/CF1822G1)

我们考虑简单版是怎么做的——我们枚举 $a_j$ 和 $b$，其中 $b$ 是从 $a_j$ 的因子中枚举的。那么对于 $a_j<10^6$，我们还是可以使用简单版的做法。可是对于 $10^6<a_j≤V$，我们明显无法使用 $O(n\sqrt V)$ 的复杂度过去了。

我们想想我们在简单版中为什么 $b$ 会在 $a_j$ 的因子中枚举呢？因为我们使用了条件 $a_i \times b=a_j$。可是我们还不是有另一个条件吗？$a_j \times b=a_k$！我们知道 $a_k≤V$，所以对于 $10^6<a_j≤V$，我们的 $b$ 明显是 $<10^3$ 的！我们直接枚举即可。这样的复杂度是 $O(n\times \frac{V}{E})(E=10^6)$ 的。

所以对于这道题，时间复杂度为 $O(n\times\max( \frac{V}{E},\sqrt{E}))(E=10^6)$。

## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
const int E=1e6;
const int M=1e9;

#define rd read()
inline int read() {
    int xx = 0, ff = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            ff = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}
inline void write(int out) {
    if (out < 0)
        putchar('-'), out = -out;
    if (out > 9)
        write(out / 10);
    putchar(out % 10 + '0');
}


int n,K,m;
int a[N],stk[N],top,T;
map<int,int>cnt;
int ans;

int prime[E],notprime[E],tot;

void init(){
	cnt.clear();
}

void solve(){
	for(auto &t : cnt){
        int val=t.first,cntt=t.second;
        ans+=cntt*(cntt-1)*(cntt-2);
        if(val>=E){
            for(int j=2; val*j<=M; ++j)
                if(val%j==0 && cnt.count(val/j) && cnt.count(val*j))
                    ans+=cnt[val/j]*cntt*cnt[val*j];
        }else{
			int j;
            for(j=1; j*j<val; ++j){
                if(j!=1 && val%j==0 && cnt.count(val/j) && cnt.count(val*j))
                    ans+=cnt[val/j]*cntt*cnt[val*j];
                if(val%j==0 && cnt.count(j) && cnt.count(val/j*val))
                    ans+=cnt[j]*cntt*cnt[val/j*val];
            }
            if(j!=1 && j*j==val && cnt.count(j) && cnt.count(val*j)) ans+=cnt[j]*cntt*cnt[val*j];
            
        }
    }
}

signed main() {
	
	T=rd;
	while(T--){
		n=rd;
		init();
		ans=0;
		for(int i=1;i<=n;i++){
			a[i]=rd;
			cnt[a[i]]++;
		}
		solve();
		cout<<ans<<endl;
	}

	return 0;
}

```


注意，如果我们用 `unordered_map` 是会 TLE 的。



---

## 作者：mango2011 (赞：0)

其实啦，本题没有那么复杂~~只是恐怖的大佬们太强了~~，我的做法应该是比较简单的：

理性分析：

第一步：准备工作。

使用一个桶 $t$（不仅限于数组）来记录每一个数出现的次数（$t_i$ 表示 $i$ 出现的次数），并且开一个数组 $b$ 记录所有出现的数。

第二步：计算答案。

枚举最后一个数，设枚举到了某个数 $x$，把答案拆成两部分：

第一部分：$1\le b\le1000$ 

第二部分：$1\le 10^6 h\le x$（ $h$ 表示最小的数）。

理性分析复杂度：

第一部分的复杂度很明显合格。

由于 $x\le10^9$，所以第二部分中的 $h$ 不超过 $1000$。

复杂度正确。

接下来逐个击破：

第一部分：设 $j$ 满足 $x\equiv0\pmod {j^2}$，那么答案就可以加上 $t_x\times t_{\frac{x}{j}}\times t_{\frac{x}{j^2}}$。

第二部分：设 $h$ 满足 $x\equiv0\pmod h$，并且 $\frac{x}{h}$ 是完全平方数。那么答案可以加上 $t_x\times t_{\sqrt{xh}}\times t_h$。

快乐实现：

实现的时候主要是用到了上面的思路，不过还要特判某些情形 (至于是哪些情形，留给读者思考)。

回顾反思：

本人在实现过程中犯了好多不该犯的错误，错了好多次。希望大家能不像我一样，一遍通过！


---


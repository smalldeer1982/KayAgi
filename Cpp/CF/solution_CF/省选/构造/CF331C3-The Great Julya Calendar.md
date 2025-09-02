# The Great Julya Calendar

## 题目描述

Yet another Armageddon is coming! This time the culprit is the Julya tribe calendar.

The beavers in this tribe knew math very well. Smart Beaver, an archaeologist, got a sacred plate with a magic integer on it. The translation from Old Beaverish is as follows:

"May the Great Beaver bless you! May your chacres open and may your third eye never turn blind from beholding the Truth! Take the magic number, subtract a digit from it (the digit must occur in the number) and get a new magic number. Repeat this operation until a magic number equals zero. The Earth will stand on Three Beavers for the time, equal to the number of subtractions you perform!"

Distinct subtraction sequences can obviously get you different number of operations. But the Smart Beaver is ready to face the worst and is asking you to count the minimum number of operations he needs to reduce the magic number to zero.

## 说明/提示

In the first test sample the minimum number of operations can be reached by the following sequence of subtractions:

  $ 24→20→18→10→9→0 $

## 样例 #1

### 输入

```
24
```

### 输出

```
5```

# 题解

## 作者：Terry2022 (赞：6)

**题意**：

定义对一个数 $x$ 的一次操作为选出它十进制下中的某一位数字 $y$，令 $x$ 变为 $x-y$

给定一个数 $n$，求最小的操作数使得 $n$ 变为 $0$

**思路**：

先考虑暴力 $\mathrm{dp}$，设 $f_{i}$ 表示 $i$ 所需要的操作数，有转移 $f_i=1+\min{f_{i-x}}$，其中 $x$ 为 $i$ 的某一位数字

可以发现一个结论：每一次操作一定是选择最大的数位，证明可以看另一篇题解

$\mathrm{dp}$ 转移变为 $f_{i}=1+f_{i-Dmax(i)}$，$Dmax(i)$ 表示 $i$ 在十进制表示下的最大的数字

这个暴力转移只能处理 $n\le 10^6$ 的情况，但是注意到 $1\le Dmax(i)\le 9$，范围很小，考虑使用矩阵优化转移

设 $(x,y)=[x\not =y]?0:1$，$x=Dmax(i+1)$，有转移：
$$
\begin{aligned}

&\begin{bmatrix}
  (1,x)&  (2,x)& (3,x) & (4,x) & (5,x) & (6,x) & (7,x) & (8,x) & (9,x) &1\\
  1& 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0\\
  0&  1&  0&  1& 0 & 1 & 0 & 1 & 0 & 0\\
  0&  0&  1&  0&  0&  0&  0&  0&  0&0 \\
  0&  0&  0&  1&  0&  0&  0&  0&  0&0 \\
  0&  0&  0&  0&  1&  0&  0&  0&  0&0 \\
  0&  0&  0&  0&  0&  1&  0&  0&  0&0 \\
  0&  0&  0&  0&  0&  0&  1&  0&  0&0 \\
  0&  0&  0&  0&  0&  0&  0&  1&  0&0 \\
  0&  0&  0&  0&  0&  0&  0&  0&  0&1 \\ 
  
\end{bmatrix}
\times
\begin{bmatrix}
f_{i}\\
f_{i-1}\\
f_{i-2}\\
f_{i-3}\\
f_{i-4}\\
f_{i-5}\\
f_{i-6}\\
f_{i-7}\\
f_{i-8}\\
1
\end{bmatrix}
=
\begin{bmatrix}
f_{i+1}\\
f_{i}\\
f_{i-1}\\
f_{i-2}\\
f_{i-3}\\
f_{i-4}\\
f_{i-5}\\
f_{i-6}\\
f_{i-7}\\
1
\end{bmatrix}
\end{aligned}
$$
设 $T_{i+1}$ 为从第 $i$ 个列矩阵转移到第 $i+1$ 个列矩阵的转移矩阵，则第 $n$ 个列矩阵为 $T_n\times \cdots \times T_{10}\times F_9=F_n$

注意到转移矩阵实质上只有 $9$ 个，且只跟数位最大值有关，可以联想到数位 $\mathrm{dp}$

虽然矩阵乘法没有交换率，但是数位 $\mathrm{dp}$ 其实就是从小到大进行的，两者相契合

设 $g_{i,j}$ 表示现在数位 $\mathrm{dp}$ 到了第 $i$ 位，此时数位最大值为 $j$，可以得到转移：$g_{i,j}=\prod_{i=1}^{ed}g_{i-1,\max(j,i)}$，$ed$ 表示该位能填的上界

直接 $\mathrm{dfs}$ 求出 $g$ 最后乘上初始列矩阵就可以得到答案，注意转移矩阵不包括 $T_1$ 到 $T_9$，同时 $n\le 9$ 要特判，细节可以看代码

时间复杂度为 $O(10^3\log n\times 9\times 9)$

$10^3$ 是矩阵乘法，$\log n\times 9$ 是数位 $\mathrm{dp}$ 的状态数，$9$ 是 $\mathrm{dp}$ 转移

**代码**：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
#define int long long
const int Q=25;
const int INF=(1<<30);
typedef long long ll;
#define rg register int
#define cint const register int
//char Buf[1<<21],*P1=Buf,*P2=Buf;
//#define gc() (P1==P2&&(P2=(P1=Buf)+fread(Buf,1,1<<21,stdin),P1==P2)?EOF:*P1++)
#define gc() getchar()
inline bool ig(const char c){return c>=48&&c<=57;}
inline void read(int &oi){char c;int f=1,res=0;while(c=gc(),(!ig(c))&&c^'-');c^'-'?res=(c^48):f=-1;while(c=gc(),ig(c))res=res*10+(c^48);oi=f*res;}
inline void print(int oi){char io[23];int l=0;if(oi<0)putchar('-'),oi=~oi+1;do io[++l]=(oi%10+48);while(oi/=10);for(;l;--l)putchar(io[l]);}
inline void write(cint oi,const char c){print(oi);putchar(c);}
inline int max(cint x,cint y){return x>y?x:y;}
const int Lim=10;
struct mat{
	int a[Lim][Lim];mat()=default;
	mat(cint X){for(rg i=0;i<Lim;++i)for(rg j=0;j<Lim;++j)a[i][j]=0;for(rg i=0;i<Lim;++i)a[i][i]=X;}
	inline mat operator*(const mat&rhs)const{
		mat res;for(rg i=0;i<Lim;++i)for(rg j=0;j<Lim;++j)res.a[i][j]=0;
		for(rg i=0;i<Lim;++i)for(rg k=0;k<Lim;++k)for(rg j=0;j<Lim;++j)res.a[i][j]+=a[i][k]*rhs.a[k][j];
		return res;
	}
};
mat f[Q][Q],st;
bool vst[Q][Q];
int a[Q],len;
inline mat set(cint vl){
	mat res;for(rg i=0;i<Lim;++i)for(rg j=0;j<Lim;++j)res.a[i][j]=0;
	for(rg i=1;i<Lim-1;++i)res.a[i][i-1]=1;
	res.a[Lim-1][Lim-1]=1;res.a[0][Lim-1]=1;res.a[0][vl-1]=1;return res;
}
inline mat dfs(cint len,cint mx,cint lim,cint zr){
	if(len==0)return set(mx);
	if(!lim&&vst[len][mx])return f[len][mx];
	f[len][mx]=mat(1);vst[len][mx]=1;cint ed=lim?a[len]:9;
	for(rg i=0;i<=ed;++i)f[len][mx]=dfs(len-1,max(mx,i),lim&&(i==ed),zr&&(!i))*f[len][mx];
	return (len==1&&zr)?mat(1):f[len][mx];
}
inline void solve(cint x){
	if(x<=9)return write(x==0?0:1,'\n');
	for(rg t=x;t;a[++len]=t%10,t/=10);
	mat res=dfs(len,0,1,1);
	for(rg i=0;i<Lim;++i)for(rg j=0;j<Lim;++j)st.a[i][j]=0;
	for(rg i=0;i<Lim;++i)st.a[i][0]=1;
	write((res*st).a[0][0],'\n');
}
int n;
signed main(){
	read(n);solve(n);
	return 0;
}
```



---

## 作者：MyukiyoMekya (赞：4)

设 $f(n)$ 为将 $n$ 变为 $0$ 的最小操作次数，$D(n)$ 为 $n$ 的数位形成的集合。

有个 naive 的 dp：$f(n)=1+ \min_{d\in D(n)} \{f(n-d)\}$，边界条件 $f(0)=0$。

我们可以归纳证明 $f(n)$ 具有单调性：$f(n)\ge f(n-1)$

显然有 $f(1)=1\ge 0 = f(0)$

那么现在已知 $\forall  1\le i <n, f(i)\ge f(i-1)$

设 $k=\max \{D(n)\},l=\max\{D(n-1)\}$，显然有 $l\ge k-1$

那么根据单调性可得

 $f(n-1)=1+\min_{d\in D(n-1)}\{f(n-1-d)\}=1+f(n-1-l)=f(n-(l+1))$

又根据 $l+1\ge k$ 可得 $f(n-(l+1))\le 1+f(n-k)$

所以有 $f(n-1)\le 1+f(n-k)$，

又因为没人会傻到操作 $n\leftarrow n-0$ ，所以 $k>1$ ，

所以根据单调性可得 $f(n)=1+f(n-k)$，整理可得 $f(n)\ge f(n-1)$，证毕。

所以 dp 方程简化了：$f(n)=1+f(n-\max\{D(n)\})$，也就是说，贪心取是对的。

然后我们来考虑怎么快速模拟这个过程：

$524\rightarrow 519\rightarrow 510\rightarrow 505\rightarrow 500$，其实这个过程是可以优化的。

我们可以记状态 $f(d,n)=(x,y)$ 表示目前能使用的最大数位为 $d$ ，要把 $n$ 变成非正整数的操作次数为 $x$ ，$n$ 变成的数为 $y$。

那么假设现在要求 $524$ 的，那么 $f(0,524)$ ，我们把它快速变成 $500$，

那么就是 $f(\max\{0,5\},24)=(4,0)$，就是把那个 $24$ 通过前面的最大数位变成非正整数，

然后我们继续进行 $500 $ 的剩下的操作 $f(0,\lfloor \frac{524}{500}\rfloor \times 500 + 0)$。

$n<10$ 的时候特判。

由于每次操作可以把数变成 $xxxxx000000$  或者原数后缀或者 $xxxxx999999x$，

所以对于每个 $d$ ，$n$ 的数量不超过 $12$ ，所以复杂度对的。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
#define ln std::puts("")
#define pb push_back
#define MP std::make_pair
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
#define fi first
#define se second
std::map<std::pair<int,int> ,std::pair<int,int> > f;
inline std::pair<int,int> dfs(std::pair<int,int> u)
{
	if(u.se<10)return MP(u.fi||u.se,u.se-std::max(u.fi,u.se));
	if(f.count(u))return f[u];
	reg int p=1;
	while(p<=u.se/10)p*=10;
	std::pair<int,int> low=dfs(MP(std::max(u.fi,u.se/p),u.se%p));
	std::pair<int,int> hig=dfs(MP(u.fi,u.se/p*p+low.se));
	return f[u]=MP(low.fi+hig.fi,hig.se);
}
signed main(void)
{
	int n;read(n),write(dfs(MP(0,n)).fi),ln;
}
```



---

## 作者：喵仔牛奶 (赞：3)

# Description

给你一个 $n$，每次减去一个数位，求最少几次减完。

对于所有数据，$n\le 10^{18}$。

# Solution

对于这种类似最短路的题，先大眼观察一下。你发现，这个 $f(n)$ 大抵是随着 $n$ 变大而不降的。那每次减最大的数位就是最优策略。

这样直接模拟可以通过 C1。

考虑 DP，想一想怎么设状态。考虑把一个数 $n$ 分成除最高位的部分 $x$ 和 $n-x$。但是这样 $n$ 的最高位会产生影响，于是我们把最高也设进去。但是有了前面位的影响，可能会把 $n$ 减到 $<0$，于是再开一个 DP 数组存最后的 $n$。

设 $f_{x,n}$ 为前面的位最大为 $x$ 时使 $n=0$ 的最小步数，$g_{x,n}$ 为减完后的 $n$。

转移时，取出最大的 $v$ 使得 $10^v\le n$，记 $t=10^v$，我们分成 $n\bmod t$ 和 $n-(n\bmod t)$ 两部分。于是我们分成了两个子问题。

但是如果 $n\bmod t=0$，那么就会无限循环。所以对于这种情况，我们手动操作一次，这样 $n\bmod t$ 就不为 $0$ 了。我们成功把原问题分成了 $n$ 更小的问题。

转移：
- 若 $n\bmod t=0$：
  - 记 $p=f_{x,n-\max(x,\lfloor n/t\rfloor)},q=g_{x,n-\max(x,\lfloor n/t\rfloor)}$；
  - $f_{x,n}=p+1$，$g_{x,n}=q$。
- 否则：
  - 记 $p=f_{\max(x,\lfloor n/t\rfloor),n\bmod t},q=g_{\max(x,\lfloor n/t\rfloor),n\bmod t}$；
  - $f_{x,n}=p+f_{x,n-(n\bmod t)+q}$，$g_{x,n}=g_{x,n-(n\bmod t)+q}$。

对于 $n\le 9$：
- 若 $n=0$，$f_{x,n}=g_{x,n}=0$。
- 否则，$f_{x,n}=1$，$g_{x,n}=n-\max(x,n)$。

记搜实现即可。分析一下复杂度：
- 每次的 $n$，要么是原来的 $n$ 的后缀，要么是 $\overline{999\dots99x}$（若干个 $9$ 加上最后一位）。所以 $n$ 只有 $\mathcal{O}(\lvert\Sigma\rvert\log n)$ 种（其中 $\Sigma$ 是字符集）。
- 而 $x$ 只有 $\lvert\Sigma\rvert$ 种，故总状态数为 $\mathcal{O}(\lvert\Sigma\rvert^2\log n)$。
- 每次求出 $t$ 需要 $\mathcal{O}(\log n)$，不过这玩意可以轻松做到 $\mathcal{O}(1)$。
- 总复杂度为 $\mathcal{O}(\lvert\Sigma\rvert^2\log^2 n)$，精细实现可以做到 $\mathcal{O}(\lvert\Sigma\rvert^2\log n)$。

# Code

```cpp
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	LL n; unordered_map<LL, pii> f[10];
	pii dfs(LL x, LL n) {
		if (!n) return {0, 0};
		if (n <= 9) return {1, n - max(x, n)};
		if (f[x].count(n)) return f[x][n];
		LL t = 1; while (t <= n / 10) t *= 10;
		if (n % t == 0) {
			auto [p, q] = dfs(x, n - max(x, n / t));
			return {p + 1, q};
		}
		auto [p, q] = dfs(max(x, n / t), n % t);
		auto [A, B] = dfs(x, n / t * t + q);
		return f[x][n] = {p + A, B};
	}
	int main() {
		cin >> n;
		cout << dfs(0, n).fi << '\n';
		return 0;
	}
}
```

---

## 作者：Purslane (赞：3)

# Solution

设答案为 $dp_n$。稍微有经验的选手可以一眼看出 $dp$ 具有单调性，则得出其转移方程式：

$$
dp_n = dp_{n - \text{maxval}(n)}
$$

其中 $\text{mxval}(n)$ 为 $n$ 的数位中的最大数。

考虑对于 $n$，在第一位一定的情况下，我们实际上可以忽略这一位，同样的可以忽略第二维：只需要把这几位的最大值记录下来即可。

因此设 $f(mx,n) = (a,b)$ 表示：我们只考虑 $n$，在 $n$ 前面被删掉的数位中，最大的数是 $mx$，则 $n$ 最后被删成一个自然数，用了多少步，剩下来多少。

为啥这样复杂度是对的？考虑你的每一步操作，要么是 $n$ 的后缀，要么是好多个 $9$、只有最后一个数除外，那么总的状态个数是 $O(\Sigma \log n)$ 的，$\Sigma$ 表示字符集大小。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
map<pair<int,int>,pair<int,int>> mp;
pair<int,int> f(int mx,int n) {
	if(mp.count({mx,n})) return mp[{mx,n}];
	if(n<=9) {
		if(n<mx) return mp[{mx,n}]={n,0};
		if(n==0) return mp[{mx,n}]={0,0};
		return mp[{mx,n}]={0,1}; 
	}
	int cnt=0,hbt=1,tval=n; while(n/hbt>=10) hbt*=10;
	roff(i,n/hbt,0) {
		auto pr=f(max(mx,i),tval%hbt);
		cnt+=pr.second,tval=i*hbt+pr.first;
		if(i) cnt++,tval-=max(mx,i);
	}
	return mp[{mx,n}]={tval,cnt};
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int n; cin>>n;
	cout<<f(0,n).second;
	return 0;
}
```

---

## 作者：littlebug (赞：2)

线代还是太强大了，第一次看见数位 dp 模拟矩阵快速幂优化 dp 的 /bx /bx

这篇题解主要是详细讲一下大佬 @[Terry2022](https://www.luogu.com.cn/user/202556) 的[线代做法](https://www.luogu.com.cn/article/bbhit84v)。

## Solution

> 首先证明个东西。
> 
> 考虑最普通的 dp，设 $f_i$ 为从 $0$ 到 $i$ 的最少步骤（就是把题目中的操作倒过来），则 $f_i = \min \limits _{x \in d(i)} \{ f_{i-x} \} + 1$
> 
> 我们发现 $f_i$ 满足单调性！证明考虑归纳法，首先 $f_1 = 1 > f_0 = 0$。那么假设 $\forall 0 \le i < n , f_i \ge f_{i-1}$，又因为显然有 $l=\max\{ d(n-1) \} \ge \max \{ d(n) \}-1$，于是有 $f_n \ge f_{n-1}$。其中 $d(x)$ 表示 $x$ 的所有数位。
>
> 于是转移方程就变成了 $f_i = f_{\max \{ d(i) \}} + 1$！

观察到，$\max \{ d(i) \}$ 的取值集合是固定且很小的，所以考虑用矩阵优化，设 $d'(x)$ 表示 $x$ 是 $(1)$ 否 $(0)$ 等于 $\max \{ d(i+1) \}$，则有：

$$
\begin{bmatrix}
d'(1) & d'(2) & d'(3) & d'(4) & d'(5) & d'(6) & d'(7) & d'(8) & d'(9) & 1 \\
1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\
0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 1 \\
\end{bmatrix}
\times
\begin{bmatrix}
f_i \\
f_{i-1} \\
f_{i-2} \\
f_{i-3} \\
f_{i-4} \\
f_{i-5} \\
f_{i-6} \\
f_{i-7} \\
f_{i-8} \\
1
\end{bmatrix}
=
\begin{bmatrix}
f_{i+1} \\
f_i \\
f_{i-1} \\
f_{i-2} \\
f_{i-3} \\
f_{i-4} \\
f_{i-5} \\
f_{i-6} \\
f_{i-7} \\
1
\end{bmatrix}
$$

~~嗯搬的，懒得打了。~~

然后因为转移矩阵不是固定的，似乎就不可以做了，但是注意到转移矩阵只与 $i+1$ 的最大**数位**有关，于是可以想到数位 dp！

关于正确性，虽然矩阵乘法不满足交换律，但是在数位 dp 的时候可以从低位到高位 dp，那么就满足了从小到大了，不会改变矩阵乘法的顺序。

于是，设 $g_{i,j}$ 为考虑从低到高前 $i$ 位，**第 $i$ 及第 $i$ 位以前的最大位**是 $j$ 时，要求出 $0$ 到当前数位所能表示的最大数的 $f$ 值所需要的**转移矩阵之积**。

那么如何转移呢？因为这是数位 dp，所以考虑在求一个 $g_{i,j}$ 的时候，相当于把可能的所有位数为 $i-1$ 的 $g$ 值乘起来，毕竟人家是转移矩阵嘛，举个例子：

> 若要求 $6737151$ 的 $g$ 值，那么相当于把这些部分的转移矩阵乘起来：
>
> $0 \sim 999999 , 1000000 \sim 1999999 , \dots , 6000000 \sim 6737151$。
>
> 继续，例如在求 $2000000 \sim 2999999$ 的时候，相当于固定一个最高位 $2$（所有的转移都能取 $2$），求 $0 \sim 999999$ 的 $g$ 值，也就对应了 $g_{6,2}$。

于是，这便满足了数位 dp 的常见状态，所以就有转移：

$$
g_{i,j} = \prod _{0 \le k \le lim} g_{i-1,\max(j,k)}
$$

其中，$lim$ 表示数位 $i$ 所能取到的最大值。

然后这样做就可以了，复杂度为 $O(|\Sigma|^3 \times |\Sigma| \times \log(n|\Sigma|)) \approx 6.3 \times 10^5$，其中 $|\Sigma|^3$ 是矩阵乘法，$|\Sigma|$ 是 dp 转移，$\log(n|\Sigma|)$ 是数位 dp 的状态数。

## Code

数位 dp 细节一大坨，调了一下午才调出来 www

```cpp
class matrix ... // 此处省略 6737151 行矩阵类板子

int n;
matrix <int> g[20][10],tmp[20][10];
bitset <10> vis[20];
int a[20],len;

il matrix <int> dp(int i,int j,bool op,bool zr)
{
	if(!op && vis[i][j]) return g[i][j];
	!op && (vis[i][j]=1);
	
	matrix <int> &t=op?tmp[i][j]:g[i][j];
	
	if(!i)
	{
		t=matrix<int>();
		t[0][j-1]=t[0][9]=t[9][9]=1;
		rep(x,1,8) t[x][x-1]=1;
		return t;
	}
	
	if(i==1 && zr) return t=matrix<int>(10,10,1);
	
	t=matrix<int>(10,10,1);
	int mx=op?a[i]:9;
	rep(x,0,mx) t=dp(i-1,max(j,x),op && x==mx,zr && !x)*t;
	
	return t;
}

signed main()
{
	read(n);
	if(n<=9) return cout<<(n!=0),0;
	len=0; int _n=n; while(_n) a[++len]=_n%10,_n/=10;
	
	matrix <int> t=dp(len,0,1,1);
	matrix <int> p(10,1);
	rep(i,0,9) p[i][0]=1;
	t*=p;
	
	write(t[0][0]);
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：SnowTrace (赞：2)

好题。

首先观察到的性质是一定每次减去最大的。

考虑归纳。

设 $f(n)$ 表示让 $n$ 变成 $0$ 的最小步数，归纳假设是 $f(n)$ 单增。

从 $n$ 到 $n+1$，数位最大值最多增加 $1$，由归纳假设可以得到 $f(n+1) \geq f(n)$。

然后我们考虑快速维护这个过程。

$n = 10^{12}$ 时，考虑折半，计算前一半对后一半的贡献，$dp_{i,j}$ 表示前面的最大数位是 $i$，要让 $j<=0$ 的最小步数，注意到因为前面对后面也有贡献，所以 $j$ 减到最后可能小于 $0$，所以还要记录最终 $j$ 是什么数字。

然后计算 $j\leq10^6$ 的情况就可以直接做。

注意到这里面（前面那一部分）有很多状态都是多余的，其实也就是有用的状态要么是最后有若干个 $9$（或者有一个后缀全是 $0$ ），要么是原数的一个后缀。

那我们做折半肯定不优了，因为左右的状态数不同。

$n = 10^{18}$，继续思考。

我们每次把最高位和后面的数分离，然后计算。

状态和前面的一样，用记忆化搜索实现。

按照前面所说的，知道状态数应该是 $O(|\sum| \log n)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<pair<int,int>,pair<int,int> >mp;
pair<int,int> dfs(int mx,int x){
	if(x<10)return {(mx>0) or (x>0),x-max(mx,x)};
	if(mp.count({mx,x}))return mp[{mx,x}];
	int xx = 1;while(xx<=x/10)xx*=10;
	auto ansa = dfs(max(mx,x/xx),x%xx);
	auto ansb = dfs(mx,x-x%xx+ansa.second);
	return mp[{mx,x}] = {ansa.first+ansb.first,ansb.second};
}
signed main(){
	int n;cin >> n;
	cout << dfs(0,n).first << endl;
	return 0;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：1)

题意：给你一个数 $n\le10^{18}$，每次操作可以减去 $n$ 当前任意一个数位，求 $n$ 变为 $0$ 所需最小操作次数。

首先有一个重要性质就是每次取最大的数位一定是最优的。因为如果减去这一位之后并没有造成退位，那其它位也不会比这个更优；如果造成了退位，下一次减的结果就一定是继续退位或者个位变为 $0$，而其它位两步之内也最多做到一样的效果。

接下来就可以直接进行数位 dp：$f_{mx,n}$ 表示前面的最大数位为 $mx$，现在要把 $n$ 减为 $\le9$，所需的最小步数以及剩下的数。

把当前 $n$ 的最高位取出，把剩下部分先减至最少，然后计算最高位以及减至最少后的结果。

```cpp
pll calc(ll mx,ll n){
	if(n<10) return{mx||n,n-max(mx,n)};// 达到了最终状态
	if(mp.count({mx,n})) return mp[{mx,n}];
	ll x=1;while(x<=n/10) x*=10;//最高位
	pll l=calc(max(mx,n/x),n%x),r=calc(mx,n-n%x+l.val);
	return mp[{mx,n}]={l.stp+r.stp,r.val};
}
```

---

## 作者：Hoks (赞：0)

## 前言
鸽了不知道多久的题，好玩好玩好玩。

摘自[杂题选做 Part 4. dp](https://www.luogu.com.cn/training/660942)。
## 思路分析
首先来看 [C1](https://www.luogu.com.cn/problem/CF331C1)。

不难发现每次贪心的减掉最大的数位一定是最优的。

所以直接预处理出 $[1,10^6]$ 每个数中最大的数位暴力减就可以了。

然后来考虑 [C2](https://www.luogu.com.cn/problem/CF331C2)。

在 C2 中 $n\le 10^{12}$，$O(n)$ 的做法并不能通过。

感性的感觉一下，操作在 $n$ 很大的时候很多部分都是重复的（因为每次操作减的数的范围很小只有 $[0,9]$）。

可以考虑数位 dp，不过这里介绍一种比较无脑的做法。

因为后面的很多部分都是相同的，所以我们直接把 $n$ 分割为前后两段 $x,y$，满足数 $x$ 和数 $y$ 拼接可以得到 $n$。

考虑 $x$ 对 $y$ 的贡献。

在 $y>0$ 时，$x$ 并不会发生任何变化，所以对 $y$ 的贡献就是使 $y$ 的数位 $\max$ 要与 $x$ 的数位 $\max$ 取 $\max$。

考虑到数位只有 $[0,9]$ 这些选法，不妨用 $f_{y,k}$ 表示数 $y$，数位要对 $k$ 取 $\max$ 时的最小操作次数。

这个部分不难线性处理出。

然后来考虑对 $x$ 的影响。

在一次将 $y$ 减到小于 $0$ 的数后，$x$ 要退位也就是减一。

然后我们发现对于 $x-1$，对 $y$ 的影响的计算方法其实和 $x$ 是一样的。

所以我们只需要记录下来在 $y$ 减完会变成什么数，然后让 $x-1$ 就可以了。

也就是设 $t_{y,k}$ 表示数 $y$，数位要对 $k$ 取 $\max$ 时减完的余数。

那么我们的状态就是从 $x,y\rightarrow x-1,f_{y,k}$ 其中 $k$ 为 $x$ 的数位 $\max$。

而 $x,y$ 的贡献是 $f_{y,k}$ 这点我们是已知的。

所以对 $x$ 不断减一不断做然后累加答案就行了。

需要注意的点是当 $t_{y,k}=0$ 时要刻意减一个 $k$ 使得 $x$ 退位。

然后是平衡复杂度的问题，总的复杂度为 $O((x+y)M)$，其中 $M$ 表示数字种类数，在本题为 $10$，基本不等式可以得到显然是 $x=y=10^6$ 时最优。

比较难以理解，可以看一看[代码](https://codeforces.com/contest/331/submission/316641032)。

首先来看 [C3](https://www.luogu.com.cn/problem/CF331C3)。

在 C3 中 $n\le 10^{18}$，即使是上面的根号平衡复杂度也无法通过了，那还能怎么办呢？

其实我们注意到，因为你每次减的数字只有 $[1,9]$，所以除了最开始的那个 $y$ 是 $n$ 的末尾几位，剩下的 $y$ 在最后一次退位的时候都是形如 $\overline{99999k}$ 形式的，其中 $k$ 是一个数字。

所以这个 $y$ 可能的取值其实也只有 $9$ 种。

再附加上 $x$ 对 $y$ 的贡献，总共不到 $100$ 种，是可以都预处理的。

具体的，我们把 $n$ 划分为 $x,y$，其中 $y$ 是后 $12$ 位，$x$ 是前面剩下的数位。

那么对于 $x$ 我们仍然沿用 C2 的思想做，$x,y\rightarrow x-1,t_{y,k}$ 转移。

对于 $y$，因为 $y$ 的值域扩展到了 $10^{12}$，所以我们直接套用 C2 代码对 $f_{y,k},t_{y,k}$ 进行计算。

根据上文所述，C3 比起 C2 新增的 $f_{y,k},t_{t,k}$ 不超过 $100$ 种，扔 `map` 里记忆化一下就好了。

代码也很相像，大概就是粘贴一遍再改一下。

复杂度 $O(M^3B)$，其中 $B$ 是划分阈值，本题取了 $10^6$，而 $M$ 是数字种类数，本题为 $10$，跑的飞快。
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=1e6+10,M=1e5+10,V=2e2+10,lim=1e6,LIM=1e12,LLIM=1e18,mod=998244353,INF=0x3f3f3f3f3f3f3f3f;
int n,ans,mx[N],f[N][10],t[N][10];
map<pair<int,int>,pair<int,int>>mp;
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
	inline bool chk(char c) { return !(c=='#'||c=='.'||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline pair<int,int> solve(int n,int mxx)
{
	if(mp.count({n,mxx})) return mp[{n,mxx}];
	int ans=0;if(n==1e12) n--,ans++;
	int l=n/lim,r=n%lim;
	while(l>=0)
	{
		int Mx=max(mx[l],mxx);
		ans+=f[r][Mx];if(!l) break;
		if(!t[r][Mx]) ans++,r=lim-Mx;
		else r=lim+t[r][Mx];l--;
	}int Mx=max(mx[l],mxx);
	return mp[{n,mxx}]={ans,t[r][Mx]};
}
inline void solve()
{
	n=read();for(int i=1;i<lim;i++) mx[i]=max(mx[i/10],i%10);
	for(int j=0;j<10;j++) for(int i=1;i<lim;i++)
	{
		f[i][j]=f[max(0ll,i-max(mx[i],j))][j]+1;
		if(i-max(mx[i],j)<0) t[i][j]=i-max(mx[i],j);
		else t[i][j]=t[i-max(mx[i],j)][j];
	}if(LLIM==n) n--,ans++;int l=n/LIM,r=n%LIM;
	while(l>=0)
	{
		auto [a,b]=solve(r,mx[l]);ans+=a;if(!l) break;
		if(!b) ans++,r=LIM-mx[l];else r=LIM+b;l--;
	}print(ans);
}
signed main()
{
	int T=1;
//	T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：Moeebius (赞：0)

> duel 到的题，神秘复杂度做法，但是比较好想（？）

如果 $n \le 10^6$ 那么我们直接 dp。

注意到 dp 具有单调性因此我们可以直接转移，即 $f_i \gets f_{mx_i} + 1$，其中 $mx_i$ 表示 $i$ 在十进制下的最大数码。

---

如果 $n \le 10^{12}$ 我们没法直接 dp 了。

但是注意到退位发生得很少；考虑将前 $6$ 位后 $6$ 位分开，后 6 位 dp 的时候多记一维 $j$，表示前 $6$ 位最大数码是 $j$，转移变为 $f_{i,j} \gets f_{\max\{mx_i, j\}}$。每次查 $f$ 数组找到退位完变成哪个数，直接跳过去，并且让前 $6$ 位的值减去 $1$。这样是 $O(\sqrt n \sigma)$ 的，其中 $\sigma = 10$。

---

如果 $n \le 10^{18}$ 我们没法根号做了。

但是注意到 $f$ 数组中被查到的位置并不是很多，因为退位完只有 $9$ 种情况。还是拿出前 $6$ 位，第一次退位的结果暴力在后 $12$ 位跑上面的根号做法；之后有可能被查到的 $f$ 只有 $O(\sigma ^2)$ 种（$9$ 种不同的 $i$ 和 $10$ 种不同的 $j$），直接拿上面的根号做法预处理。

预处理 $10^6$ 以内每个数的最大数码，复杂度 $O(\sigma ^2 n^{1/3})$，常数不大，可以通过本题。

注意当 $n=10^{18}$ 时有 $19$ 位，要先手动减 $1$。

[这里是代码。](https://codeforces.com/contest/331/submission/282633926)

---

## 作者：Daniel1234 (赞：0)

# 思路

简单...题？

那就来个复杂的做法（

一眼数位 dp。

状态：$dp_{i,j,k}$ 表示现在要从 $00...000$（$j$ 个 0）到 $99...999$（$j$ 个9）的第 $k$ 位，而且此时前缀中的数的状态为 $i$，（$i$ 为 $0 \sim 2^{10}-1 $ 中的一个数）。

转移就更“简单”了，只要拆成 $10$ 段，而段都与段可以从前面转移过来，而且段内转移可以从上一个 dp 转移过来，具体细节见代码。

时间复杂度较大，常数不能太大。

# 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int dp[1<<10][20][15][15];
int base[19];
int n;
int f[25];
int g[1005];
int used[1005];
void chkmin(int &x, int y){
    if(x == -1)x = y;
    else x = min(x, y);
}
void run(int st, int en, int have, int op){
    if(en < 10)for(int i = 0; i < 10; i++)f[i] = -1;
    for(int i = st; i <= en; i++)f[i] = -1;
    if(op)f[st] = 0;
    for(int i = st+op; i <= en; i++){
        for(int j = 1; j < 10; j++){
            if(i%10 == j || (have >> j&1)){
                if(i - j >= 0 && f[i-j] != -1){
                    chkmin(f[i], f[i-j]+1);
                }
            }
        }
    }
}
int zh(int x){
    int ans = 0;
    while(x){
        ans |= (1<<x%10);
        x /= 10;
    }
    return ans;
}
signed main(){
    cin >> n;
    g[0] = 0;
    for(int i = 1; i <= 1000; i++){
        g[i] = 1e9;
        for(int j = 0; j < 10; j++){
            if(zh(i)>>j&1){
                g[i] = min(g[i - j] + 1, g[i]);
            }
        }
    }
    if(n <= 1000){
        cout << g[n] << endl;
        return 0;
    }
    base[0] = 1;
    for(int i = 1; i <= 18; i++)base[i] = base[i - 1] * 10;
    for(int i = 0; i < (1<<10); i++){
        for(int j = 0; j < 10; j++){
            run(j, 9, i, 1);
            for(int k = 0; k < 10; k++){
                dp[i][1][j][k] = f[k];
            }
        }
    }
    for(int i = 2; i <= 18; i++){
        for(int j = 0; j < (1<<10); j++){
            for(int k = 0; k < 10; k++){
                for(int w = 0; w < 10; w++)f[w] = dp[j][i-1][k][w];
                for(int num = 0; num < 9; num++){
                    run(10, 19, j | (1<<num+1), 0);
                    for(int w = 0; w < 10; w++){
                        f[w] = f[w + 10];
                    }
                    int g[10];
                    for(int p = 0; p < 10; p++)g[p] = -1;
                    for(int p = 0; p < 10; p++){
                        for(int w = 0; w < 10; w++){
                            if(f[p] == -1 || dp[j|(1<<num+1)][i-1][p][w] == -1)continue;
                            chkmin(g[w], f[p] + dp[j|(1<<num+1)][i-1][p][w]);
                        }
                    }
                    for(int p = 0; p < 10; p++){
                        f[p] = g[p];
                    }
                }
                for(int w = 0; w < 10; w++){
                    dp[j][i][k][w] = f[w];
                }
            }
        }
    }
    int nw = 0;
    int fr = -1;
    while(nw <= n){
        int ok = 0;
        for(int i = 18; i >= 1; i--){
            if(nw + base[i] - 1 <= n){
                if(fr == -1){
                    for(int j = 0; j < 10; j++){
                        f[j] = dp[0][i][0][j];
                    }
                    fr = 1;
                }else{
                    run(10, 19, zh(nw), 0);
                    for(int j = 0; j < 10; j++){
                        f[j] = f[j + 10];
                    }
                    int g[10];
                    for(int j = 0; j < 10; j++){
                        g[j] = -1;
                    }
                    for(int st = 0; st < 10; st++){
                        for(int k = 0; k < 10; k++){
                            if(f[st]==-1||dp[zh(nw)][i][st][k]==-1)continue;
                            chkmin(g[k], f[st] + dp[zh(nw)][i][st][k]);
                        }
                    }
                    for(int j = 0; j < 10; j++)swap(f[j], g[j]);
                }
                nw += base[i];
                ok = 1;
                break;
            }
        }
        // cout << nw << endl;
        // for(int i = 0; i < 10; i++)cout << f[i] << " ";
        // cout << endl;
        if(!ok)break;
    }
    run(10, 19, zh(nw), 0);
    cout << f[n - nw+10] << endl;
    return 0;
}
```

---

## 作者：Prean (赞：0)

很牛逼的状态（

贪心比较显然，每次减去数位中最大的数。

证明：如果没减退位那么别的数都做不到，如果减退位了那么下一个要么继续退位要么个位为 $0$，而别的数两步以内一定没有前者大或者也为 $0$。

设 $f(d,n)$ 表示一个二元组 $(x,y)$，表示在可以使用 $d$ 这个数位的前提下（就是高位中数位最大的那个），将 $n$ 减为非正整数需要 $x$ 步，且这个非正整数为 $y$。

设有 $m$ 满足 $10^m\leq n<10^{m+1}$。那么每次令最高位减去 $1$，削掉这一部分的“血皮”，然后继续削剩下的。

于是就有血皮的部分是 $X=f(\max(d,\lfloor\frac{n}{10^m}\rfloor),n\bmod 10^m)$，剩下的部分就是 $oth=f(d,10^m\times\lfloor\frac{n}{10^m}\rfloor+X_y)$，结果就是 $f(d,n)=(X_x+oth_x,oth_y)$。

至于状态总数不会证。不过跑得飞快，在 CF 上面才 30ms。
```cpp
#include<cstdio>
#include<map>
typedef long long ll;
struct pr{
	ll cnt,num;pr(const ll&cnt=0,const ll&num=0):cnt(cnt),num(num){}
	inline bool operator<(const pr&it)const{return num==it.num?cnt<it.cnt:num<it.num;}
};std::map<pr,pr>f;
inline ll max(const ll&a,const ll&b){return a>b?a:b;}
inline ll Find(const ll&n){ll t(1);while(t*10ull<=n)t*=10;return t;}
inline pr F(const int&d,const ll&n){
	if(n<10)return pr(d||n,n-max(d,n));if(f.find(pr(d,n))!=f.end())return f[pr(d,n)];const ll&m=Find(n);
	const pr&x=F(max(d,n/m),n%m),&oth=F(d,m*ll(n/m)+x.num);return f[pr(d,n)]=pr(oth.cnt+x.cnt,oth.num);
}
signed main(){ll n;scanf("%lld",&n);printf("%lld",F(0,n).cnt);}
```

---


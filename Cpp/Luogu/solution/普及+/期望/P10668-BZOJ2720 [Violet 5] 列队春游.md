# BZOJ2720 [Violet 5] 列队春游

## 题目描述

给定正整数数列 $h_1,h_2,\cdots,h_n$。设 $p$ 为 $1\sim n$ 的随机排列。

定义 $h'_i=h_{p_i}$。定义 $\mathrm{pre}_i$ 为最大的 $j\lt i$ 满足 $h'_j\ge h'_i$（如果不存在，规定为 $0$）。

求出 $\displaystyle \sum_{i=1}^n (i-\mathrm{pre}_i)$ 的期望值，保留两位小数输出。

## 说明/提示

对于 $20\%$ 的数据，$1\leq n\leq 10$；

对于 $50\%$ 的数据，$1\leq n\leq 70$，且 $h_i$ 互不相同；

对于 $100\%$ 的数据，保证 $1\leq n\leq 300$，$1\leq h_i\leq 1000$。

## 样例 #1

### 输入

```
3
3 2 1```

### 输出

```
4.33```

# 题解

## 作者：Pursuing_OIer (赞：13)

## BZOJ2720 [Violet 5] 列队春游 题解  
### Problem  
对于一个数列 $S$，$S_0= \infty$，设对于 $S_i$，$S_{a_i}$ 是 $S_i$ 之前第一个大于等于 $S_i$ 的数。给定 $S$ 中的元素，求 $\sum_{i=1}^{n}(i-a_i)$ 的期望。  
### Solution  
我们考虑对于每一种身高的学生，分别统计期望。显然，对于身高为 $h$ 的学生，只有身高为 $h-1$ 及以下的学生可以产生贡献，且每个人产生的贡献都是 $1$。  
设对于当前的 $h$，共有 $s$ 个可以产生贡献的学生，剩下便有 $n-s$ 个学生（包括当前索要贡献的学生）。这些学生之间共 $n-s+1$ 个空。而一个学生想要产生贡献，就必须恰好站在索要贡献的学生之前的空里，贡献为 $\frac{1}{n-s+1}$ 。若身高为 $h$ 的学生共有 $b$ 个，则此类学生对所有身高为 $h$ 的学生所产生的贡献为 $\frac{s \times b}{n-s+1}$。  
另外，每个人不论如何都有 $1$ 的贡献，应当加上。  
实现时，可以记录每种身高学生的个数并依次累加贡献，时间复杂度为基于身高值域的线性复杂度。  
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b[2000],sum,maxn;
double ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a);
		++b[a];
		maxn=max(maxn,a);
	}
	for(int i=1;i<=maxn;++i){
		ans+=1.0*sum*b[i]/(n-sum+1)+b[i];
		sum+=b[i];
	}
	printf("%.2lf",ans);
	return 0;
}
```

---

## 作者：___Furina___ (赞：8)

## 题目大意（原题面）：
建议先读一遍[原题面](https://imgse.com/i/2rLdxI)，再来看这篇题解
## 题解：
首先我们要知道，随机排列后，整个序列的 $\sum E_i$ 相当于对于每一个人求期望后累和。

那么我们不如单独来考虑第 $i$ 个人的期望 $E_i$。

假设目前有 $sum$ 个人比 $i$ 个人**更矮**，我们不妨从这 $sum$ 个人中先随便选出一个人 $j$ 进行计算。

由于对于第 $j$ 人而言，如果它要被第 $i$ 人计算到，那么在剩余的 $n-sum$ 个人中，也就是 $n-sum+1$ 个空位，第 $j$ 人一定要刚好在第 $i$ 人前一个位置。如果第 $j$ 人不在第 $i$ 人前一个位置，由于其他人都比第 $i$ 人更高或等高，那么第 $i$ 人一定看不到第 $j$ 人。

那么对于第 $j$ 人而言，他对第 $i$ 人产生贡献的概率为 $\frac{1}{n-sum+1}$，期望为 $1\times\frac{1}{n-sum+1}$，那么共有 $sum$ 人比第 $i$ 人更矮，总期望就为 $sum\times 1\times \frac{1}{n-sum+1}$。

当然，就算一个人前面有没有比他更矮的人，一个人也总有 $1$ 的贡献。

所以，我们只需要直接维护一下每个人有多少个比他更矮的人就可以了，我们可以从小到大统计答案，以实时维护 $sum$ 的大小。

时间复杂度：$O(h)$，$h$ 为值域。
### 代码如下：
```cpp
#include<bits/stdc++.h>
#define N 10000010
#define I_love_Furina return//奇怪的码风
#define forever 0
#define foreverr 1
#define Endl endl
#define endl '\n'
#define FIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define db double
using namespace std;
int n,t[N],sum,maxn;
db ans;
signed main(){
    IOS;//FIO("")
    cin>>n;
	for(int i=1,x;i<=n;i++)cin>>x,t[x]++,maxn=max(maxn,x);//统计每种数出现了多少次
	for(int i=1;i<=maxn;i++)ans+=1.0*sum*t[i]/(n-sum+1)+t[i],sum+=t[i];//统计贡献并且维护sum
    printf("%.2lf",ans);
    I_love_Furina forever;
}
```
完结撒花（点赞）！

---

## 作者：Add_Catalyst (赞：4)

# BZOJ2720: 列队春游（带有部分分）

---

## 思路&代码

### 20pts

爆搜即可。

```cpp
#include<bits/stdc++.h>
#define FOR(i,a,b) for(register int i=(a);i<=(b);++i)
#define DOR(i,a,b) for(register int i=(a);i>=(b);--i)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
using namespace std;
const int N=70;
int n;
int a[N];
double ans;
bool vis[N];
int p[N];
inline int check(){
	int sum=0;
	FOR(i,1,n)DOR(j,i-1,0)if(p[j]>p[i]&&~(sum+=i-j))break;
	return sum;
}
void dfs(int u){
	if(u>n)return ans+=check(),void();
	FOR(i,1,n)if(!vis[i])p[u]=a[i],vis[i]=1,dfs(u+1),vis[i]=0;
}
signed main(){
	cin>>n;
	FOR(i,1,n)cin>>a[i];
	p[0]=INF,dfs(1);
	FOR(i,1,n)ans/=i;
	cout<<fixed<<setprecision(2)<<ans<<endl;
	return 0;
}
```

### 50pts

注意到条件：

> 所有的 $h_i$ 互不相同。

那么变成了一道关于全排列的题目。

我们假设现在总共有 $n$ 个人排成一队，那我们直接把最高的那个人放到中间，此时队伍的两边就全部无关联了，那么我们就可以记录 DP 数组 $f_i$ 表示对于一个 $i$ 个人进行排队的队列，视野总期望是多少，则，得到转移方程：
$$
f_i = \frac{\sum_{j=1}^{i}(f_{j-1}+f_{i-j}+j)}{i}
$$
其中，$f_{j-1},f_{n-j}$ 分别是左右两边的期望，$j$ 是该次视野。

```cpp
#include<bits/stdc++.h>
#define FOR(i,a,b) for(register int i=(a);i<=(b);++i)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
using namespace std;
const int N=3e2+10;
const double EPS=1e-8;
int n;
double f[N];
double dfs(int len){
	if(len<2)return (double)(len>0);
	if(f[len]>EPS)return f[len];
	double res=0;
	FOR(i,1,len)res+=(dfs(i-1)+dfs(len-i)+i);
	return f[len]=res/len;
}
signed main(){
	cin>>n;
	cout<<fixed<<setprecision(2)<<dfs(n)<<endl;
	return 0;
}
```

### 100pts

（$cnt_i$ 表示小于 $a_i$ 的数的个数）

#### $O(n^3)$ 

我们直接枚举每个人，对于他们自己对期望的贡献进行计算，最后累加，除上总方案数。

在对每个人进行枚举时，我们再枚举在每个位置时的贡献，最后枚举“视野”，也就是单次贡献，就可以清楚明了地算出每种情况的方案数了。

设当前第 $i$ 个人，在第 $j$ 个位置，视野是 $k$，我们就可以分情况讨论：

1. $j+k>n$：方案数为 $\operatorname{A}_{cnt_i}^{k-1} \cdot (j-1)!$；
2. $j+k \le n$：方案数为 $\operatorname{A}_{cnt_i}^{k-1} \cdot (n - k - 1)! \cdot (n - cnt_i -1)$。

那么再乘上 $k$ 就是答案了。

```cpp
#include<bits/stdc++.h>
#define L_D long double
#define FOR(i,a,b) for(register int i=(a);i<=(b);++i)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
using namespace std;
const int N=3e2+10;
int n;
int a[N],cnt[N];
L_D fact[N],sum;
inline L_D A(int n,int m){return fact[n]/fact[n-m];}
signed main(){
	cin>>n;fact[0]=1.0;
	FOR(i,1,n)cin>>a[i],fact[i]=fact[i-1]*i;
	sort(a+1,a+n+1);
	FOR(i,1,n)cnt[i]=lower_bound(a+1,a+n+1,a[i])-a-1;
	FOR(i,1,n)FOR(j,1,n)FOR(k,1,min(n-j,cnt[i])+1)
		sum+=A(cnt[i],k-1)*k*(j+k==n+1?fact[j-1]:(n-cnt[i]-1)*fact[n-k-1]);
	sum/=fact[n];
	cout<<fixed<<setprecision(2)<<sum<<endl;
	return 0;
}
```

（这种方法较易理解，但数据范围大的话就爆掉了……）

#### $O(n^2)$ 

我们对上面的式子进行优化，改变枚举方式：设当前第 $i$ 个人，视野是 $j+1$ 。

依旧是分类讨论：

1. 前面没有比他高的：$\sum_{j=0}^{cnt_i} \operatorname{A}_{cnt_i}^{j} \cdot (n-j+1)! \cdot (j+1)$；
2. 相反：$\sum_{j=0}^{cnt_i} \operatorname{A}_{cnt_i}^{j} \cdot (n - cnt_i - 1) \cdot (n-j+1) \cdot (j+1) \cdot (n-j-2)!$。

```cpp
#include<bits/stdc++.h>
#define D double
#define FOR(i,a,b) for(register int i=(a);i<=(b);++i)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
using namespace std;
const int N=3e2+10,M=1e3+10;
int n;
int a[N],id[M];
D ans;
signed main(){
	cin>>n;
	FOR(i,1,n)cin>>a[i];
	sort(a+1,a+n+1);
	FOR(i,1,n){
		D p=1.0;
		id[a[i]]=(!id[a[i]]?i:id[a[i]]);
		FOR(j,1,n-1)ans+=p*1.0*(n-j+1)/n,p*=1.0*(id[a[i]]-j)/(n-j);
		ans+=p/n;
	}
	cout<<fixed<<setprecision(2)<<ans<<endl;
	return 0;
}
```

（极致压行……有些许转换，自行理解）

#### $O(n)$​ 

我们再继续优化上面的方法，但是主要运用数学知识。

##### 法 1

改变枚举方式：设当前第 $i$ 个人，求他的总贡献。

那么我们再反过来想：第 $i$ 个人的总贡献，就是所有人对他的贡献。

我们将所有大于等于 $a_i$ 的数提出来，独立排列，那么总共有 $(n-cnt_i)!$ 种方法，此时我们把一个小于 $a_i$ 的数揪出来，放在 $a_i$ 前面，其余随便放，这个小于 $a_i$ 的数对 $a_i$ 的贡献就 ***至少*** 是 $1$。

所以，总答案就是 $\frac{cnt_i \cdot (n-cnt_i)! \cdot \operatorname{A}_n^{cnt_i-1}}{n}+1$，化简可得：$\frac{n+1}{n-cnt_i+1}$。

##### 法 2

从期望的定义入手：

> 设离散型随机变量 $X$ 的分布律为 $P_{ X = x_k } = p_k,k \in N^* $，若级数 $\sum_{k=1}^{\infty} |x_k| \cdot p_k < +\infty$，记 $E_X = \sum_{k=1}^{\infty} x_k \cdot p_k$。则称 $E_X$ 为随机变量 $X$ 的数学期望。

那么在此题中，期望定义式应为：
$$
E = \sum_{i=1}^{n} i \cdot P_{L=i}
$$
其中 $L$ 表示视野。

那么，我们通过我 ~~不太懂的~~ 概率学知识，可以得到：
$$
E = \sum_{i=1}^{n} P_{L \ge i}
$$
那么，依旧是枚举：当前是第 $i$ 个人，求其总贡献。

设除他自己之外，身高不小于他的有 $k$ 个人，则：
$$
\begin{aligned}
E_i & = \sum_{i=1}^n \frac{(n-i+1)\operatorname{A}_{n-i}^{k}}{\operatorname{A}_{n}^{k+1}} \\
E_i & = \sum_{i=1}^n \frac{(n-i+1)\frac{(n-i)!}{(n-i-k)!}}{\frac{n!}{(n-k-1)!}} \\
E_i & = \frac{(n-k-1)!}{n!} \sum_{i=1}^n {\frac{(n-i+1)!}{(n-i-k)!}} \\
E_i & = \frac{(n-k-1)!(k+1)!}{n!} \sum_{i=1}^n {\frac{(n-i+1)!}{(n-i-k)!(k+1)!}} \\
E_i & = \frac{(n-k-1)!(k+1)!}{n!} \sum_{i=1}^n \operatorname{C}_{n-i+1}^{k+1} \\
E_i & = \frac{(n-k-1)!(k+1)!}{n!} \operatorname{C}_{n+1}^{k+2} \\
E_i & = \frac{n+1}{k+2} \\
\end{aligned}
$$

```cpp
#include<bits/stdc++.h>
#define D double
#define FOR(i,a,b) for(register int i=(a);i<=(b);++i)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
using namespace std;
const int N=3e2+10,M=1e3+10;
int n,sum;
int a[N],cnt[M];
D ans;
signed main(){
	cin>>n;
	FOR(i,1,n)cin>>a[i],++cnt[a[i]];
	FOR(i,1,M-5)
		ans+=1.0*cnt[i]*(n+1)/(n-sum+1),sum+=cnt[i];
	cout<<fixed<<setprecision(2)<<ans<<endl;
	return 0;
}
```

其实法 1 与 法 2 在本质上是一样的。

---

## 启发

### 新增知识

$$
\begin{aligned}
E & = \sum_{i=1}^{n} i \cdot P_{L=i} \\
E & = \sum_{i=1}^{n} P_{L \ge i} \\
\end{aligned}
$$

### 思想

求期望，概率相关题目时，不要被 DP 限制住了思维，可以通过数学推导来求解。

---

---

## 作者：Charlie_ljk (赞：4)

- [博客园](https://www.cnblogs.com/Charlieljk/p/18275480)。

# 思路分析

首先对于每一个 $i$，可以处理不小于其的个数与小于其的个数（不包括自己），为了方便，分别表示成 $big_i$ 和 $small_i$。

对于每一个小朋友，枚举其所在位置 $j$，其站在这里的概率为 $\dfrac{1}{n}$。

第三层循环枚举其视野，即 $pre_i$，为了方便用 $k$ 表示，当然 $k\le j$ 那么我们需要：

1. 其前 $k-1$ 个人都比他矮。
2. 第 $k$ 个人不低于他。

那么显然满足条件 $1$ 的概率为 $\dfrac{A_{small_i}^{k-1}}{A_{n-1}^{k-1}}$。

满足第 $2$ 个条件的概率为 $\dfrac{big_i}{n-k}$，即去了其自身和他前面 $k-1$ 个人，剩下 $n-k$ 个人中站在其前第 $k$ 个人身高不小于他的概率。

那么综上所述对于一般情况下，对于第 $i$ 个小朋友，他站在第 $j$ 个位置，$pre_i=k$ 时，其对于期望的贡献为：
$$\dfrac{1}{n}\times\dfrac{A_{small_i}^{k-1}}{A_{n-1}^{k-1}}\times\dfrac{big_i}{n-k}\times k$$

同时其还存在特殊情况，没有人能挡住他，即 $j=k$ 时，要单独计算其贡献，此时贡献就是没有人能挡住他的概率 $\times$ 其站在这个位置上的概率 $\times$ 此时视野，和之前的区别就是没了其前第 $k$ 个人不比他低的概率了，那么就是：
$$\dfrac{1}{n}\times\dfrac{A_{small_i}^{j-1}}{A_{n-1}^{j-1}}\times j$$

# 复杂度优化

此时的复杂度约为 $O(n^4)$，虽然跑不满但是不允许，我们发现 $\dfrac{A_{small_i}^{k-1}}{A_{n-1}^{k-1}}$ 在一次 $i$ 的循环中除了 $k$ 这个变量别的变量始终不变，故此可以递推，从而使复杂度降为 $O(n^3)$。

递推式很简单，每次 $k+1$ 时使其 $\times\dfrac{small_i-k+1}{n-k}$ 即可。

**注意**： $\dfrac{A_{small_i}^{k-1}}{A_{n-1}^{k-1}}$ 不可能为负，所以为负时另其为 $0$ 或直接结束本轮循环即可。

# 代码如下

```cpp
#include<bits/stdc++.h>
// #define int long long 
#define endl '\n'
#define sort stable_sort
using namespace std;
const int N=310;
template<typename Tp> inline void read(Tp&x)
{
    x=0;register bool z=true;
    register char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') z=0;
    for(;'0'<=c&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
    x=(z?x:~x+1);
}
void wt(int x){if(x>9)wt(x/10);putchar((x%10)+'0');}
void write(int x){if(x<0)putchar('-'),x=~x+1;wt(x);}
int n,h[N],d[N];
double ans;
double P(int d,int m,int n)
{
    int up=1,down=1;
    for(int i=d-m+1;i<=n-m;i++) up*=i;
    for(int i=d+1;i<=n;i++) down*=i;
    return (double)up/(double)down;
}
signed main()
{
    read(n);
    for(int i=1;i<=n;i++) read(h[i]);
    sort(h+1,h+1+n);
    for(int i=1;i<=n;i++)
    {
        int t=lower_bound(h+1,h+1+n,h[i])-h;
        d[i]=t-1;  
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            double p=1; int v=d[i];
            for(int k=1;k<=j-1;k++)
                ans+=(double)k*p*(double)(n-d[i]-1)/(double)(n-k)/(double)(n),
                p*=(double)(v)/(double)(n-k),
                v-=(v>0);
            ans+=(double)(j)*(double)(p)/(double)(n);
        }
    printf("%.2lf",ans);
}
```

---

## 作者：Fire_Raku (赞：2)

[P10668 BZOJ2720 [Violet 5] 列队春游](https://www.luogu.com.cn/problem/P10668)

期望

考虑每个元素什么情况下会产生贡献，然后分别贡献到答案中。当当前枚举的数 $h_i$ 在 $i$ 与 $pre_i$ 之间有一个数字时那么会有对当前方案会有 $1$ 的贡献。不妨将严格小于 $h_i$ 的数的数量记为 $s_i$，则大于等于 $h_i$ 的数有 $n-s_i$。

**计算每个方案 $h_i$ 产生的贡献**。先看 $i$ 与 $pre_i$ 之间的数产生给 $h_i$ 的贡献，将大于等于 $h_i$ 的数随机排列有 $(n-s_i)!$ 种。然后任意取**一个**小于 $h_i$ 的数放到 $i$ 和 $pre_i$ 之间都会产生同样的贡献 $1$，有 $s_i$ 种取法，剩下的数插进去随便排列，有 $A_{n}^{s_i-1}$ 种，根据乘法原理，$i$ 与 $pre_i$ 之间的数会产生贡献 $(n-s_i)!s_iA_{n}^{s_i-1}$，由于求的是期望，所以除以一个 $n!$：
$$
\frac{(n-s_i)!s_iA_{n}^{s_i-1}+n!}{n!}=\frac{(n-s_i)!s_iA_{n}^{s_i-1}}{n!}+1
$$
**加 $n!$ 的原因**是不论有没有数对每个排列 $h_i$ 与 $pre_i$ 都至少有 $1$ 的贡献。再整理化简得到：
$$
\frac{n+1}{n-s_i+1}
$$
这是其中一个 $h_i$ 的贡献，答案对于每个数都求一次累加即可。

就是从求一个方案的所有位置的贡献，到枚举每个 $h_i$ 求贡献，到枚举 $i$ 和 $pre_i$ 之间的其中一个数累加贡献。

复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define pii std::pair<int, int>
#define mk std::make_pair
#define fi first
#define se second
#define pb push_back

using i64 = long long;
using ull = unsigned long long;
const i64 iinf = 0x3f3f3f3f, linf = 0x3f3f3f3f3f3f3f3f;
const int N = 1010;
int n;
int cnt[N];
double ans;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
	std::cin >> n;
	int mx = 0;
	for (int i = 1; i <= n; i++) {
		int a;
		std::cin >> a;
		cnt[a]++;
		mx = std::max(mx, a);
	}

	int sum = 0;
	for (int i = 1; i <= mx; i++) {
		if(!cnt[i]) continue;
		ans += 1.0 * (n + 1) / (n - sum + 1) * cnt[i];
		sum += cnt[i];
	}
	std::cout << std::fixed << std::setprecision(2) << ans << "\n";

	return 0;
}
```

---

## 作者：hexz01 (赞：1)

# 题解：P10668 BZOJ2720 [Violet 5] 列队春游

## 题意

给定正整数序列 $h_1,h_2,\dots,h_n$，将这个数列随机打乱。对于每个 $i$，定义 $pre_i$ 是最大的 $j$ 使得 $j<i$ 且 $h[j]>=h[i]$（不存在则为 $0$）。求 $\sum_{i=1}^n(i-pre_i)$ 的期望，保留两位小数。

## 思路

首先考虑对于每个 $i$，怎么给 $i-pre_i$ 产生贡献。因为 $pre_i$ 是最靠近 $i$ 的大于等于 $h_i$ 的位置，所以我们肯定希望 $i$ 前面都是小于 $h_i$ 的数。

基于这个想法，枚举 $nowh$，设当前共有 $x$ 个数比 $nowh$ 小，有 $y$ 个数等于 $nowh$。

因为所有 $x$ 个人都要站在 $n-x+1$ 个人中，身高为 $nowh$ 的 $y$ 个人前面，所以贡献为 $x$，概率为 $\frac{y}{n-x+1}$，所以期望为 $\frac{x \times y}{n-x+1}$。

另外这道题有一个易错点，因为 $pre_i<i$ 所以每个人都有 $1$ 的初始贡献。

## 算法

总结下算法流程：

1. 拿一个桶记下来每个数的个数。
2. 遍历值域，累加前缀和，也就是上文的 $x$，当前个数就是 $y$，把答案加上 $\frac{x \times y}{n-x+1}+y$。
3. 输出答案，保留两位小数。

## code

``` cpp
#include <iostream>
using namespace std;
int n, max1=0, pre=0;
int h[2007], cnt[1007];
double ans=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>h[i];
		cnt[h[i]]++;
		max1=max(max1, h[i]);
	}
	for(int i=1;i<=max1;i++){
		ans+=(1.0*cnt[i]*pre)/(n-pre+1)+cnt[i];
        pre+=cnt[i];
    }
	printf("%.2f\n", ans);
	return 0;
}
```

---

## 作者：YeShangqwq (赞：1)

P10668 列队春游

好题。加深了我对期望的认识。

题意：给一个序列。定义 $h$ 为其所有位置，到其前面的第一个大于等于他的位置的距离之和。问其所有排列的 $h$ 的期望值。

首先，对于一个位置 $i$，他的贡献为前面比他小于的连续人数 +1。设其为 $f_i$，设 $d_j$ 是位置 $j$ 对 $f_i$ 的贡献。$p_j$ 是 $j$ 对 $i$ 有贡献的概率。则 $f_i=1+\sum\limits_{j,a_j<a_i} p_j$。

考虑算 $p_j$，$p_j=\frac{S(j\to i)}{n!}$。这里，$S(j\to i)$ 表示 $j$ 能对 $i$ 有贡献的方案数。则我们发现不好算，于是考虑先把 $j$ 和 $i$ 视为一个人，之后往里面插入剩下的比 $i$ 小的其他的元素，这样，我们发现是不重不漏的计算出所有可行的排列了。记 $s$ 为小于 $a_i$ 的元素个数，则也就是 

$$(n-s)!A_{n}^{s-1}$$

 于是将其除以总排列数，就得到了 $p_j=\frac 1 {n-s+1}$。那么相同的高度，我们发现，可以打包起来计算，然后如果我们按照高度从小到大枚举，发现前面的 $p_j$，都是一样的，于是每次加上 $\frac{s\times cnt_i}{n-s+1}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, h[301], b[1001];
int main() {
  int mx = 0;
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> h[i], ++b[h[i]], mx = max(mx, h[i]);
  double ans = 0;
  int sum = 0;
  for (int i = 1; i <= mx; ++i) {
    if(b[i]) ans += 1. * sum * b[i] / (n - sum + 1), sum += b[i];
  }
  printf("%.2lf", ans + n);
  return 0ll;
}
```

---


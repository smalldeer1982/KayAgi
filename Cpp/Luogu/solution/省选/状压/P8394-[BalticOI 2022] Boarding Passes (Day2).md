# [BalticOI 2022] Boarding Passes (Day2)

## 题目描述

在成功遵守当地的风俗之后，你正好赶上了轮船的出发时间。然而，你没有想到会有那么多人前往吕贝克！由于你不想在颁奖仪式上迟到（你还需要一些时间将你所有偷来的艺术品存放在旅店里），你想加快轮船的登船速度。

船上有一排 $n$ 个座位，共 $n$ 名乘客预订了所有座位。每位乘客都有一张船票，上面写着他们的指定座位和 $g$ 个登船组中的一组。

登船时，一次会叫一个组的乘客登船。每个登船组内的乘客将以随机顺序登船，即对于所有可能的登船顺序，出现概率相等。每位乘客可以在第一个座位的前面或最后一个座位的后面登船，然后在另一位乘客登船前移到他们的指定座位。

你确定这个过程中，当一个乘客要经过已经入座的乘客时最耗时（装有所有这些领带的行李在过道上是一个相当大的障碍）。幸运的是，你在附近的储物柜里发现了一件工作人员的制服，所以你可以决定各组乘客的登船顺序，并在登船开始前告诉每位乘客，是要从所有座位的前面还是后面登船。

编写一个程序，利用船票信息计算出在登船过程中，如果你确定了登船组的登船顺序，并将乘客分配到最前面和后面时，一个乘客要经过已经入座的乘客的次数的最小值的期望。

### 注意

给定一个登船组的登船顺序，并将乘客分配到最前面和后面时，一个乘客要经过已经入座的乘客的次数的期望被定义为：
$$1\cdot p_1+2\cdot p_2+3\cdot p_3+\ldots$$
其中 $p_k$ 是登船时一个乘客要经过已经入座的乘客的次数恰好为 $k$ 的概率。换句话说，这是每个登船组中所有可能的乘客登船顺序中一个乘客要经过已经入座的乘客的平均次数。


## 说明/提示

对于所有数据，满足 $1\le g\le 15$，$1\le n \le 10^5$。

## 样例 #1

### 输入

```
AACCAA
```

### 输出

```
1
```

## 样例 #2

### 输入

```
HEHEHEHIHILOL
```

### 输出

```
7.5
```

## 样例 #3

### 输入

```
ONMLKJIHGFEDCBAABCDEFGHIJKLMNO
```

### 输出

```
0
```

# 题解

## 作者：7KByte (赞：3)

这题题意有点不清楚。就是我们需要在所有人开始上船之前就确定小组顺序和每个人的方向。而不是在知道小组中每个人的顺序后再决策。

观察到 $g$ 很小，考虑直接状压。同时我们可以用调整法简单证明，对于一个小组的人，肯定存在分割点，左边的人从左边上，右边的人从右边上。

那么我们就需要快速计算贡献，如果组 $x$ 在组 $y$ 前面，产生的贡献是二元组 $(i,j)$ 数量满足 $i < j$ 且 $s_i=x,s_j = y$，注意如果 $j$ 选择从右边上则相反。

我们直接跑个前缀和 $f_{x,y,i}$ 表示组 $x$ 在组 $y$ 前面，$y$ 的前 $i$ 个数选择从左边上的贡献。对右边同理。

对于组内贡献，依然按上面的定义，只不过贡献变成 $\frac{f_{x,y,i}}{2}$。

状压 DP，然后转移的时候枚举分割点。由于 $f$ 函数是个凸包，所以可以二分答案求出最优分割点。时间复杂度 $\mathcal{O}(m^2n + 2^mm^2\log n)$。

```cpp
#define N 100005
int n, a[15][N], sz[N], m = 14, s = (1 << 15) - 1; LL f[N], u[15][15][N], v[15][15][N], c[15][N];
char ch[N];
LL calc(int w,int p,int x){
	LL sum = 0;
	rep(i, 0, m)if(1 & (w >> i))sum += u[p][i][x] * 2;
	return sum + u[p][p][x];
}
LL value(int w,int p,int x){
	LL sum = 0;
	rep(i, 0, m)if(1 & (w >> i))sum += v[p][i][x] * 2;
	return sum + v[p][p][x];
}
LL g(int w,int p,int x){
	return calc(w, p, x) + value(w, p, x + 1);
}
int main() {
	scanf("%s", ch + 1);
	n = strlen(ch + 1);
	rp(i, n){
		int op = ch[i] - 'A';
		c[op][i]++, a[op][++sz[op]] = i;
		rep(j, 0, m)c[j][i] += c[j][i - 1];
	}
	rep(x, 0, m)rep(y, 0, m){
		rp(i, n){
			u[x][y][i] = u[x][y][i - 1];
			if(ch[i] - 'A' == x)u[x][y][i] += c[y][i - 1];
		}
		pr(i, n){
			v[x][y][i] = v[x][y][i + 1];
			if(ch[i] - 'A' == x)v[x][y][i] += c[y][n] - c[y][i];
		}
	}
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	rep(i, 0, s - 1)rep(j, 0, m)if(! (1 & (i >> j))){
		int t = i | (1 << j);
		int l = 0, r = sz[j] - 1, ed = sz[j];
		while(l <= r){
			int mid = (l + r) >> 1;
			if(g(i, j, a[j][mid]) < g(i, j, a[j][mid + 1]))ed = mid, r = mid - 1;
			else l = mid + 1;
		}
		cmn(f[t], f[i] + g(i, j, a[j][ed]));
	}
	cout << f[s] / 2;
	if(f[s] & 1)pc('.'), pc('5');
	return 0;
}
```

---

## 作者：Alex_Wei (赞：3)

> [P8394 「BalticOI 2022 Day2」Boarding Passes](https://www.luogu.com.cn/problem/P8394)

一道不算难的状压。

根据期望的线性性，将组 $A$ 上船的代价拆成 $A$ 内部所有人之间的代价以及其它所有已经上船的组对 $A$ 产生的代价。

对于组 $A$ 而言，必然存在一个分界点 $p$ 满足位置 $\leq p$ 的人从左边上船，$> p$ 的人从右边上船。考虑如果 $i < j$ 且 $i$ 从右边上船，$j$ 从左边上船，容易证明将它们调整为 $i$ 从左边上船，$j$ 从右边上船代价必然减小。

假设在 $p$ 处分割时从左边上船的人数为 $x$，则从右边上船的人数为 $|A| - x$。考虑任意两对从左边上船的人，当位置在左边的人先于位置在右边的人上船时，会产生 $1$ 的代价。因为随机排列中某两个数具有特定的前后顺序的概率相等，均为 $\dfrac 1 2$，所以分割方案 $p$ 的组内贡献为 $c_A = \dfrac {x(x - 1) + (|A| - x)(|A| - x - 1)} 4$。不妨改变 $p$ 的定义为在 $A_p$ 处分割，也就是前 $p$ 个人从左边上船，后 $|A| - p$ 个人从右边上船，则 $c_A$ 是关于 $p$ 的二次函数，且具有下凸性。

考虑某一组 $B$ 对 $A$ 的贡献。如果 $A_i$ 从左边上船，那么它的贡献是 $< A_i$ 的 $B$ 的数量，从右边同理。因此，预处理出 $f_{B, A, p}$ 表示如果在 $A_p$ 处分割，那么 $B$ 对在左边上船的 $A$ 的总贡献，$g_{B, A, p}$ 表示 $B$ 对在右边上船的 $A$ 的总贡献。预处理枚举任意两组和分隔位置，时间复杂度 $\mathcal{O}(g ^ 2n)$ 或 $\mathcal{O}(gn)$，视实现细节程度而定。

考虑 $A_p$ 和 $A_{p + 1}$，因为 $< A_{p + 1}$ 的 $B$ 的数量显然不小于 $< A_p$ 的 $B$ 的数量，所以 $f_{B, A}$ 具有下凸性。同理 $g_{B, A}$ 具有下凸性。

因为我们只关心有哪些组此时已经上船，而非它们具体的上船顺序，自然考虑状压 DP $ans_S$ 表示上船的组的集合为 $S$ 时的最小代价。转移枚举不属于 $S$ 的组 $A$，然后每个可能的分割点以及每个 $B\in S$，容易计算贡献。这样暴力的时间复杂度为 $\mathcal{O}(2 ^ g gn)$（有个 $g$ 可以被均摊分析掉，但是没啥影响），无法接受。

但注意到 $c_A$，$f_{B, A}$，$g_{B, A}$ 均下凸，所以贡献单峰（显然，下凸是比单峰更强的条件），三分最优分割点位置即可。时间复杂度 $\mathcal{O}(2 ^ g g ^ 2\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool Mbe;
constexpr int N = 1e5 + 5;
template <class T> inline void cmin(T &x, T y) {x = x < y ? x : y;}
int n, mx;
char s[N];
vector<int> buc[N];
long long f[15][15][N], g[15][15][N];
long long ans[1 << 15];
bool Med;
int main() {
  fprintf(stderr, "%.3lf\n", (&Mbe - &Med) / 1048576.0);
  // freopen("passes.in", "r", stdin);
  // freopen("passes.out", "w", stdout);
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for(int i = 1; i <= n; i++) {
    mx = max(mx, (int) (s[i] - 'A') + 1);
    buc[s[i] - 'A'].push_back(i);
  }
  for(int i = 0; i < mx; i++)
    for(int j = 0; j < mx; j++)
      if(i != j) {
        for(int k = 1, cur = 0; k <= n; k++) {
          f[i][j][k] = f[i][j][k - 1];
          if(s[k] == i + 'A') cur++;
          if(s[k] == j + 'A') f[i][j][k] += cur;
        }
        for(int k = n, cur = 0; k; k--) {
          g[i][j][k] = g[i][j][k + 1];
          if(s[k] == i + 'A') cur++;
          if(s[k] == j + 'A') g[i][j][k] += cur;
        }
      }
  memset(ans, 0x3f, sizeof(ans));
  ans[0] = 0;
  for(int i = 0; i < 1 << mx; i++) {
    for(int j = 0; j < mx; j++)
      if(i >> j & 1 ^ 1) {
        int l = 0, r = buc[j].size();
        auto calc = [&](int p) {
          int pos = p ? buc[j][p - 1] : 0;
          int back = buc[j].size() - p;
          long long tot = 1ll * p * (p - 1) + 1ll * back * (back - 1);
          tot >>= 1;
          for(int k = 0; k < mx; k++)
            if(i >> k & 1)
              tot += f[k][j][pos] + g[k][j][pos + 1] << 1;
          return tot;
        };
        while(l + 2 < r) {
          int m1 = l + r >> 1, m2 = m1 + 1;
          if(calc(m1) <= calc(m2)) r = m2;
          else l = m1;
        }
        long long coef = 1e18;
        for(int p = l; p <= r; p++) cmin(coef, calc(p));
        cmin(ans[i | (1 << j)], ans[i] + coef);
      }
  }
  printf("%.3lf\n", ans[(1 << mx) - 1] * .5);
  return 0;
}
```

---

## 作者：yangchenxiao (赞：2)

首先一定要注意题意是安排旅客的方式是不能随着排列的方式而改变的，因此变成选择期望下的最优位置，而不是算出最优值的期望。

最后计算的方法是很明显的，只需要一个状压就可以解决，但是转移时需要计算贡献 $f[i][S]$ 表示第 $i$ 类人在集合 $S$ 中的人已经在船上时的期望贡献。

考虑期望怎么计算，以左边的人为例，可以发现先来的人贡献 $1$，后到的人贡献 $0$，自己这组的人贡献期望为 $0.5$，这样一来可以做到 $O(n)$ 计算出一种局面的答案。

决策一定是把左边的一些人分到左边，右边同理，考虑对于一种分割点 $pos$，那么答案由两部分造成，以左边为例，为 $S$ 中每个 $i$ 左边的人对 $i$ 的贡献 $1$，以及互相的贡献。  
- 前者可以预处理 $f[i][j][k]$ 表示第 $j$ 类对第 $i$ 类前 $k$ 个人的贡献和是多少，询问时 $O(G)$ 计算。  
- 后半部分则是定值，为 $\frac{pos(pos-1)}{2}$。

考虑怎样快速确定最优分界点是怎样的——通过观察发现两部分贡献均为单谷的。对于第一种，如果把左右贡献分别写成函数，那么可以发现切线斜率都是单调变化，那么合起来是单谷函数。第二部分的二次函数也显然是单谷的。因此直接通过三分就可以确定最优决策点。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define int long long
const int maxn=1e5+5;
const double inf=1e18;
int n,id[maxn],a[maxn],m,all;
double f[15][15][maxn],g[15][15][maxn],ans=inf,mem[15][maxn],F[maxn];
vector<int>has[maxn];
char s[maxn];
double calc(int id,int pos,int S){
	double res=0,cur=has[id].size()-pos-1;
	for(int i=0;i<=m;i++)if(S>>i&1)res+=f[id][i][pos]+g[id][i][pos+1];
	res+=pos*(pos+1)/4.0,res+=cur*(cur-1)/4.0;
	return res;
}
double calc(int id,int S){
	int l=-1,r=has[id].size()-1;double res=inf;
	while(l<r){
		int lmid=l+(r-l)/3,rmid=r-(r-l)/3;
		double w1=calc(id,lmid,S),w2=calc(id,rmid,S);
		res=min(res,min(w1,w2));
		if(w1>w2)l=lmid+1;else r=rmid-1;
	}
	res=min(res,min(calc(id,l,S),calc(id,r,S)));
	return res;
}
void domin(double &a,double b){if(a>b)a=b;}
signed main(){
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++)a[i]=s[i]-'A',m=max(m,a[i]),has[a[i]].pb(i);
	all=(1<<m+1)-1;
	for(int i=0;i<=m;i++)for(int j=0;j<=m;j++){
		for(int k=1,sum=0,id=0;k<=n;k++){
			sum+=a[k]==j;
			if(a[k]==i)f[i][j][id]=f[i][j][id-1]+sum,id++;
		}
		for(int k=n,sum=0,id=has[i].size()-1;k>=1;k--){
			sum+=a[k]==j;
			if(a[k]==i)g[i][j][id]=g[i][j][id+1]+sum,id--;
		}
	}
	for(int i=0;i<=m;i++)if(has[i].size()){
		for(int S=0;S<=all;S++){
			if(S>>i&1)continue;
			mem[i][S]=calc(i,S);
		}
	}
	for(int i=1;i<=all;i++)F[i]=inf;
	for(int S=0;S<all;S++)for(int i=0;i<=m;i++)if(!(S>>i&1))domin(F[S|1<<i],F[S]+mem[i][S]);
	printf("%.2lf",F[all]);
	return 0;
}
```

---

## 作者：_ZSR_ (赞：0)

### [P8394 [BalticOI 2022 Day2] Boarding Passes](https://www.luogu.com.cn/problem/P8394)

先考虑暴力一点的做法。我们枚举第 $i$ 组上船之前已经上船的组的集合 $sta$，依次枚举上船的人 $j$，假设他左边有 $a$ 个 $sta$ 组的，有 $b$ 个 $i$ 组的，右边的分别为 $c,d$，那么他从左侧上船的贡献为 $a+0.5 \times b$，从右侧上船的贡献为 $c+0.5 \times d$。但是这样复杂度太高了，无法接受。

首先，我们看看有没有什么是可以预处理的。不难发现，我们可以求出 $val_{i,j,k}$ 表示第 $i$ 组已经上船，第 $j$ 组有 $k$ 个人从左边上船，其他从右边上船对第 $i$ 组造成的打扰期望是多少。这个很好求，直接枚举 $j$ 的每一个人，不断加上前缀中第 $i$ 组的人数和后缀中第 $i$ 组的人数。

枚举第 $i$ 组上船之前已经上船的组的集合 $sta$ 实际上就是一个状压 $dp$，这个不好优化，考虑优化后面枚举每一个人从哪一侧上船的部分。感性理解一下，我们会发现每一组一定是第一个人到第 $k$ 个人从左边上，然后第 $k+1$ 个人到最后一个人从右边上。那么我们令 $cost_{i,j,k}$ 表示在 $j$ 之前已经上船的组的集合为 $i$，有 $k$ 个人从左边上船的最小打扰期望。打个表可以发现，这是一个关于 $k$ 的凹函数，因此我们可以三分或者倍增找到最小值，这样复杂度就可以接受了。

code 
```
#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
const int N=1e5+10,M=20;
int n,m;
char str[N];
int val[M][M][N];
vector<int> pos[M];
int id[30],sum[N],vis[N];
ld f[1<<15];
inline ld calc(int x)//同组之间造成的打扰
{
    return (ld)x*(x-1)/4;
}
inline ld calc(int sta,int i,int j)
{
    ld res=0;
    for (int k=1;k<=m;++k) if (sta>>(k-1)&1) res+=val[k][i][j];
    int size=(int)pos[i].size();
    res+=calc(j)+calc(size-j);
    return res;
}   
inline ld calc(int sta,int i)
{
    int k=0;
    for (int j=(1<<16);j;j>>=1)
    {
        if (k+j<=(int)pos[i].size()&&calc(sta,i,k+j)<calc(sta,i,k+j-1)) k+=j;
    }
    return calc(sta,i,k);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>str+1;
    n=strlen(str+1);
    for (int i=1;i<=n;++i) 
    {
        if (!id[str[i]-'A']) id[str[i]-'A']=++m;
        pos[id[str[i]-'A']].emplace_back(i);
    }
    for (int i=1;i<=m;++i)
    {
        memset(vis,0,sizeof vis);
        for (int j:pos[i]) vis[j]=true;
        for (int j=1;j<=n;++j) sum[j]=sum[j-1]+vis[j];
        for (int j=1;j<=m;++j)
        {
            if (i==j) continue;
            int cur=0;
            for (int k=0;k<(int)pos[j].size();++k)
            {
                cur+=sum[pos[j][k]];
                val[i][j][k+1]+=cur;
            }
            cur=0;
            for (int k=(int)pos[j].size()-1;k>=0;--k)
            {
                cur+=sum[n]-sum[pos[j][k]];
                val[i][j][k]+=cur;
            }
        }
    }
    fill(f,f+(1<<m),1e18);
    f[0]=0;
    for (int i=0;i<(1<<m);++i)
    {
        for (int j=1;j<=m;++j)
        {
            if (i>>(j-1)&1) continue;
            f[i|(1<<j-1)]=min(f[i|(1<<j-1)],f[i]+calc(i,j));
        }
    }
    cout<<setiosflags(ios::fixed)<<setprecision(3);
    cout<<f[(1<<m)-1]<<endl;
    return 0;
}
```


---


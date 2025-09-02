# [ICPC 2014 WF] Buffed Buffet

## 题目描述

自助餐厅里有 $n$ 种食物，分为两大类，为 “离散食物”和“连续食物”。你可以通过吃食物来获得收益。

离散食物用 $(w,t_0,\Delta t)$ 描述。对于这种食物，你只能吃整数个，每个重为 $w$。吃的第一个收益为 $t_0$，后面每吃一个收益减少 $\Delta t$。具体的，吃的第 $i$ 个这种食物 （从 $1$ 开始标号），收益为 $t_0-(i-1)\Delta t$。

连续食物用 $(t_0,\Delta t)$ 描述。对于这种食物，你可以吃任意食物的重量。如果你吃的重量为 $w$，获得的收益是 $t_0w-\dfrac{1}{2}\Delta t w^2$。

你现在要吃重量和 **恰好** 为 $W$ 的食物。最大化你的收益。

## 说明/提示

$n\le 250,W\le 10000$。

对于离散食物，满足 $1\le w\le 10000$。

对于所有食物，满足 $0\le t_0,t\le 10000$。

## 样例 #1

### 输入

```
2 15
D 4 10 1
C 6 1
```

### 输出

```
40.500000000
```

## 样例 #2

### 输入

```
3 15
D 4 10 1
C 6 1
C 9 3
```

### 输出

```
49.000000000
```

## 样例 #3

### 输入

```
2 19
D 4 5 1
D 6 3 2
```

### 输出

```
impossible
```

# 题解

## 作者：FangZeLi (赞：12)

## Link

[P6893 [ICPC2014 WF]Buffed Buffet](https://www.luogu.com.cn/problem/P6893)

## Solution

显然这个问题看着就非常背包。

注意到食物其实分成两类，贡献分别是离散和连续的。

回想一下我们初学DP时，有个非常重要的结论：01背包不可以贪心，但是分数背包可以。

那么作用到这题上，我们分开考虑这两种物品。

对于不连续的，我们设计一个背包；对于连续的，我们设计一个贪心。

先考虑相对复杂一点的背包：

设 $f_{i,j}$ 表示前 $i$ 种菜吃了 $j$ 克时可获得的最大美味值，则有转移：
$$
f_{i,j}=\max_{0\le k \le \lfloor\frac{j}{w_i}\rfloor}(f_{i-1, j - kw_i}+\sum_{n=1}^k(t_i - (n - 1)\Delta t_i))
$$
直接转移要枚举 $i$，$j$，$k$，复杂度大概是 ${\mathcal O}(dw^2)$。肯定是过不去的，T​飞了，那么肯定是考虑优化。

这个背包虽然是两维的，但是熟悉背包的你肯定知道，$i$ 这一维实际上是“假”的。或者说，$i$某种程度上只起到了一个标记版本的作用。那么这样的话，我们就可以往一维DP的各种优化的角度考虑。

状态上是不太能压缩了。考虑优化转移的过程，利用一下决策单调性，先把式子拆一下：
$$
f_{i,j}=\max_{0\le k \le \lfloor\frac{j}{w_i}\rfloor}(f_{i-1, j - kw_i}+kt_i-\dfrac{\Delta t_ik(k-1)}2)
$$
然后你发现这个东西长得非常的斜率优化，于是我们往这个方面考虑：
$$
f_j = \max_{0\le k \le \lfloor\frac{j}{w}\rfloor}(g_{j - kw}+kt-\dfrac{\Delta tk(k-1)}2)
$$
我们把下标关于$w_i$的同余类分开考虑，变换下标，记 $i' = \lfloor\dfrac{i}{w}\rfloor$，则有：
$$
\begin{aligned}
f_j &= \max_{0\le i \le j}(g_i + (j - i)t - \dfrac{\Delta t(j-i)(j-i-1)}2) \\
&= \max_{0\le i \le j}(g_i + jt - it - \dfrac{\Delta t}2(j^2-2ij+i^2-j+i)) \\
&= \max_{0\le i \le j}(g_i - it - \dfrac{\Delta t}2i(i+1) + \Delta tij) + jt - \dfrac{\Delta t}2j(j-1) \\
g_i - it - \dfrac{\Delta t}2i(i + 1) &= - \Delta tj \times i + f_j - jt + \dfrac{\Delta t}2j(j-1)
\end{aligned}
$$
这个式子就可以斜率优化做了，复杂度 $\mathcal{O}(dw)$。

然后考虑连续的贪心部分。

我们每次都取当前美味值最大的，然后，当两种食品的美味值相等的时候，我们“合并”这两种食品。

具体的，当两种美味值分别为$a$，$b$的连续食品合并的时候，新食品的美味值就是 $\dfrac1{\frac{1}a + \frac{1}b}$，那么这部分的复杂度是 $\mathcal{O}(d + w)$。

最后枚举下多少给离散，多少给连续，就做完了。

## Code

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>

#define _D 260
#define _W 10010
#define _INF 1e18
#define _EPS 1e-10

struct C {
	int t, dt;
};
struct D {
	int w, t, dt;
};

bool inline operator <(const C& left, const C& right) {
	return left.t > right.t;
}

int d, w;

int ccnt, dcnt;
C fdc[_D];
D fdd[_D];

namespace workD {
	int curt, curdt, curw, r;
	double f[_W], tmp[_W];
	
	std::deque<int> q;
	
	double inline x(int p) {
		return 1.0 * p;
	}
	double inline y(int p) {
		return tmp[p * curw + r] - 1.0 * p * curt - 0.5 * curdt * p * (p + 1);
	}
	double inline slope(int left, int right) {
		double lx = x(left), rx = x(right), ly = y(left), ry = y(right);
		return (ry - ly) / (rx - lx == 0 ? _EPS : rx - lx);
	}
	
	void ins(int p) {
		while (q.size() > 1 && slope(q[q.size() - 2], q.back()) < slope(q[q.size() - 2], p)) {
			q.pop_back();
		}
		q.push_back(p);
	}
	void del(double k) {
		while (q.size() > 1 && slope(q.front(), q[1]) > k) {
			q.pop_front();
		}
	}

	void add(int wi, int t, int dt) {
		curw = wi, curt = t, curdt = dt;
		for (int i = 1; i <= w; i++) {
			tmp[i] = f[i];
			f[i] = -_INF;
		}
		for (r = 0; r < wi; r++) {
			q.clear();
			for (int j = 0; j * wi + r <= w; j++) {
				ins(j);
				del(-1.0 * dt * j);
				int i = q.front();
				f[j * wi + r] = std::max(f[j * wi + r], tmp[i * wi + r] + 1.0 * (j - i) * t - 1.0 * (j - i) * (j - i - 1) / 2 * dt);
			}
		}
	}

	void calc() {
		for (int i = 1; i <= w; i++) {
			f[i] = -_INF;
		}
		for (int i = 1; i <= dcnt; i++) {
			add(fdd[i].w, fdd[i].t, fdd[i].dt);
		}
	}
}
namespace workC {
	double f[_W];

	void calc() {
		if (ccnt == 0) {
			for (int i = 1; i <= w; i++) {
				f[i] = -_INF;
			}
			return;
		}
		std::sort(fdc + 1, fdc + ccnt + 1);
		int pt = 1;
		double curv = fdc[1].t, curdt = fdc[1].dt, curw = 0, cursum = 0;
		pt++;
		for (int i = 1; i <= w; i++) {
			while (curw < 1.0 * i) {
				if (pt > ccnt || curv - curdt * (i - curw) > 1.0 * fdc[pt].t) {
					cursum += curv * (i - curw) - 0.5 * (i - curw) * (i - curw) * curdt;
					curv -= curdt * (i - curw), curw = i;
				} else {
					double q = (curv - 1.0 * fdc[pt].t) / curdt;
					cursum += curv * q - 0.5 * q * q * curdt;
					curv = fdc[pt].t, curw += q;
					curdt = 1.0 / (1.0 / curdt + 1.0 / (fdc[pt].dt != 0 ? fdc[pt].dt : _EPS));
					pt++;
				}
			}
			f[i] = cursum;
		}
	}
}

int main() {
	scanf("%d%d", &d, &w);
	while (d--) {
		char tp[10];
		scanf("%s", tp);
		switch (tp[0]) {
			case 'D':
				++dcnt;
				scanf("%d%d%d", &fdd[dcnt].w, &fdd[dcnt].t, &fdd[dcnt].dt);
				break;
			case 'C':
				++ccnt;
				scanf("%d%d", &fdc[ccnt].t, &fdc[ccnt].dt);
				break;
		}
	}
	workC::calc(), workD::calc();
	double ans = -_INF;
	for (int i = 0; i <= w; i++) {
		ans = std::max(ans, workC::f[i] + workD::f[w - i]);
	}
	if (ccnt == 0 && ans < -1e16) {
		puts("impossible");
	} else {
		printf("%.10lf\n", ans);
	}
	return 0;
}
```

## Inspiration

我认为这一道题目处理方法整体来说比较自然，没有太过于需要“想象力”的步骤，基本上说是按部就班。

核心结论：

- 背包有一维实际上不重要，故可以看成一维的然后斜率优化
- 两种连续的食品在美味值相同时可以合并

---

## 作者：do_while_true (赞：6)

对于离散的食物，$w$ 相同的只留下美味值最大的 $W/w$ 个，因为再多了也没用不会更优。所以一共只有 $\sum_{i=1}^n \frac{W}{i}=\mathcal{O}(W\log n)$ 这样暴力背包复杂度就是 $\mathcal{O}(W^2\log n)$。

然后考虑连续的怎么做。枚举离散的占了 $w$ 的重量，那么连续的一定是先取不断吃最美味的，直到最美味的和次美味的一样好吃，这样这两个食物就可以看成一个了。加入其中两个 $\Delta t$ 分别是 $x,y$，稍微推推能推出新的食物的 $\Delta t$ 为 $\frac{xy}{x+y}$。

所以总复杂度就是 $\mathcal{O}(W^2\log n+Wn)$。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double ld;
typedef pair<int,int>pii;
typedef pair<ld,ld>pdd;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
const int N=10010;
const ll inf=0x3f3f3f3f3f3f3f3f;
int n,m,W;
pdd lx[N],b[N];
vpii vec[N],ls;
ll f[N];
ld calc(pdd x,ld y){
	return x.fi*y-0.5*x.se*y*y;
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n,W);
	for(int i=1;i<=W;i++)f[i]=-inf;
	for(int i=1;i<=n;i++){
		int w,t,dt;
		char c=getchar();while(c<'A'||c>'Z')c=getchar();
		if(c=='D'){
			read(w,t,dt);
			vec[w].pb(mp(t,dt));
		}
		else{
			read(t,dt);
			lx[++m]=mp(t,dt);
		}
	}
	sort(lx+1,lx+m+1,[](const pdd &x,const pdd &y){return x>y;});
	for(int o=1;o<=W;o++)if(vec[o].size()){
		vi a;
		for(auto i:vec[o])
			for(int j=1;j<=W/o;j++)
				a.pb(i.fi-(j-1)*i.se);
		nth_element(a.begin(),a.begin()+W/o,a.end(),[](const int &x,const int &y){return x>y;});
		for(int i=0;i<W/o;i++)
			for(int j=W;j>=o;j--)
				if(f[j-o]!=-inf)
					cmax(f[j],f[j-o]+a[i]);
	}
	if(m==0){
		if(f[W]==-inf)puts("impossible");
		else cout << f[W] << '\n';
		return 0;
	}
	ld ans;
	for(int o=0;o<=W;o++){
		for(int i=1;i<=m;i++)b[i]=lx[i];
		ld sum=f[o],rem=W-o;
		for(int i=1;i<=m;i++){
			if(i<m){
				ld delta=(b[i].fi-b[i+1].fi)/b[i].se;
				if(rem>delta){
					sum+=calc(b[i],delta);
					rem-=delta;
					ld x=b[i].se,y=b[i+1].se;
					b[i+1].se=(x*y*y+x*x*y)/((x+y)*(x+y));
				}
				else{
					sum+=calc(b[i],rem);
					break;
				}
			}
			else sum+=calc(b[i],rem);
		}
		if(o==0)ans=sum;
		else cmax(ans,sum);
	}
	printf("%.10lf\n",ans);
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：scp020 (赞：2)

# P6893 [ICPC2014 WF] Buffed Buffet 题解

感觉就是两个题硬揉在一起的缝合题，不太好评价。

## 解法

将问题拆成两个完全独立的部分。

对于离散食物，不难想到把每每个物品拆成若干物品做 01 背包，最坏复杂度为 $\mathcal{O}(nw^2)$（取决于每个物品的重量）。

考虑如何优化这个背包。不难发现所有重量为 $i$ 的物品中只有 $\dfrac{w}{i}$ 个可以对答案产生贡献，所以我们只取这些物品做背包即可，时间复杂度 $\mathcal{O}(nw \log w)$，其中 $\log$ 来自调和级数。

对于连续食物，我们可以贪心，将所有食物按照初始收益排序，称当前食物为目前初始收益最好的食物。不难发现吃当前食物一定不会使答案更劣。如果吃了一定数量的当前食物使当前食物和下一个食物的初始收益相同时，我们可以合并两个食物，设当前食物衰变常量（机翻的）、下一个食物衰变常量、合并后食物的衰变常量分别为 $t_1,t_2,t$，则可列出 $t_0 \times w - \dfrac{1}{2} \times \dfrac{t_1}{t_1 + t_2} \times w^2 + t_0 \times w - \dfrac{1}{2} \times \dfrac{t_2}{t_1 + t_2} \times w^2 = t_0 \times w - \dfrac{1}{2} t \times w^2$，所以 $t = \dfrac{t_1 \times t_2}{t_1 + t_2}$。

最后将两个部分合并就行了。

## 代码

```cpp
#include<bits/stdc++.h>
namespace fast_IO
{
    /**
     * useless things
     */
};
using namespace fast_IO;
#define int long long
#define double long double
const int N=300,W=10010;
int n,w;
double ans=LONG_LONG_MIN;
struct Discrete // 离散
{
    int f[W];
    std::vector< std::pair<int,int> > v[W];
    std::vector<int> tmp;
    inline void add(const int w0,const int t0,const int delt)
    {
        v[w0].push_back(std::make_pair(t0,delt));
    }
    inline void solve()
    {
        memset(f,128,sizeof(f)),f[0]=0;
        for(int i=1;i<=w;i++)
            if(!v[i].empty())
            {
                tmp.clear();
                for(int j=0;j<v[i].size();j++)
                    for(int k=1;k<=w/i;k++) tmp.push_back(v[i][j].first-(k-1)*v[i][j].second);
                std::nth_element(tmp.begin(),tmp.begin()+w/i,tmp.end(),std::greater<int>());
                for(int j=0;j<w/i;j++)
                    for(int k=w;k>=i;k--) if(f[k-i]!=-9187201950435737472) f[k]=std::max(f[k],f[k-i]+tmp[j]);
            }
    }
};
struct Continuous // 连续
{
    double f[W],last;
    std::vector< std::pair<int,int> > v;
    std::vector< std::pair<double,double> > tmp;
    inline void add(const int t0,const int delt)
    {
        v.push_back(std::make_pair(t0,delt)),tmp.push_back(std::make_pair(0,0));
    }
    inline void solve()
    {
        memset(f,0,sizeof(f));
        std::sort(v.begin(),v.end(),std::greater< std::pair<int,int> >());
        for(int i=1;i<=w;i++)
        {
            last=i;
            for(int j=0;j<v.size();j++) tmp[j]=v[j];
            for(int j=0;j<v.size();j++)
                if(j+1<v.size())
                {
                    if(last>(tmp[j].first-tmp[j+1].first)/tmp[j].second)
                        f[i]+=((tmp[j].first-tmp[j+1].first)/tmp[j].second)*
                        (tmp[j].first-0.5*tmp[j].second*((tmp[j].first-tmp[j+1].first)/tmp[j].second)),
                        last-=(tmp[j].first-tmp[j+1].first)/tmp[j].second,
                        tmp[j+1].second=tmp[j].second*tmp[j+1].second/(tmp[j].second+tmp[j+1].second);
                    else
                    {
                        f[i]+=last*(tmp[j].first-0.5*tmp[j].second*last);
                        break;
                    }
                }else f[i]+=last*(tmp[j].first-0.5*tmp[j].second*last);
        }
    }
};
Discrete dis;
Continuous con;
char ch;
signed main()
{
    in>>n>>w;
    for(int i=1,w0,t0,delt;i<=n;i++)
    {
        in>>ch;
        if(ch=='C') in>>t0>>delt,con.add(t0,delt);
        else in>>w0>>t0>>delt,dis.add(w0,t0,delt);
    }
    con.solve(),dis.solve();
    if(con.v.empty())
    {
        if(dis.f[w]==-9187201950435737472) std::cout<<"impossible";
        else std::cout<<std::fixed<<std::setprecision(7)<<dis.f[w];
        return 0;
    }
    for(int i=0;i<=w;i++) if(dis.f[i]!=-9187201950435737472) ans=std::max(ans,dis.f[i]+con.f[w-i]);
    std::cout<<std::fixed<<std::setprecision(7)<<ans;
    return 0;
}
```

---

## 作者：forest114514 (赞：1)

### P6893 [ICPC2014 WF] Buffed Buffet

二合一好题，~~都二合一了还好题~~。

首先离散食物只能背包，设 $f_{i}$ 表示吃了 $i$ 重量食物的最大收益。

转移显然是 $f^{'}_{i}=\max \limits_{jw\leq i}f_{i-jw}+jt_0-\frac{1}{2}j(j-1)\Delta t$，显然权值函数 $w(j)=jt_0-\frac{1}{2}j(j-1)\Delta t$ 是凸的，有决策单调性，可以直接按余数分类做到 $O(nW\log W)$，相似的题 **LOJ6039. 「雅礼集训 2017 Day5」珠宝** 也是权值贪心后是凸的，也能决策单调性分治。

然后连续食物这玩意和可分割的背包一样，所以直接贪心，但是考虑怎么处理两个东西当前收益相等，重量和变化量不同的情况。在微小的时刻显然可以看做同时吃了两个物品使得产生了相同的收益变化量，即吃完后还是当前顺时收益相等。

比如 $(t_0,\Delta t),(t_0,\Delta T)$ 显然有 $t_0-a\Delta t=t_0-b\Delta T\to a=x_0\Delta T,b=x_0\Delta t$ 此时吃了 $a+b=x_0(\Delta T+\Delta t)$ 的食物，变化了 $x_{0} \Delta T\Delta t$ 的美味度，所以变成了一个 $(t_0,\frac{\Delta T\Delta t}{\Delta T+\Delta t})$ 的新物品。

对每个整数重量算出连续食物的贡献，最后做一个 $O(W)$ 合并即可。

时间复杂度 $O(nW\log W)$，瓶颈在第一部分的 DP。

代码：

```cpp
#define int LL
#define pii pair<db,db>
#define double db
const int N=255,M=1e4+100;
int n,W;
int w,t0,dt;
int f[M],g[M];
int calc(int j){
	return j*t0-j*(j-1)*dt/2;
}
void solve(int l,int r,int L,int R,int C){
	if(l>r) return;
	int mid=l+r>>1,p=L;
	rep(i,L,min(R,mid)) if(f[C+mid*w]<g[C+i*w]+calc(mid-i)&&g[C+i*w]!=-INF) f[C+mid*w]=g[C+i*w]+calc(mid-i),p=i;
	solve(l,mid-1,L,p,C);
	solve(mid+1,r,p,R,C);
}
pii ele[N];
int tot;
db val[M];
bool _ED;
signed main(){
	fprintf(stderr,"%.20lf MB\n",(&_ST-&_ED)/1048576.0);
	//ios::sync_with_stdio(false);
	//cin.tie(0);cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n,W);
	rep(j,1,W) f[j]=-INF,val[j]=-INF;
	f[0]=val[0]=0;
	rep(i,1,n){
		char op=gc();gc();
		if(op=='D'){
			read(w,t0,dt);if(w>W) continue;
			swap(f,g);rep(j,0,W) f[j]=-INF;
			rep(st,0,w-1) solve(0,(W-st)/w,0,(W-st)/w,st);
		}
		else read(t0,dt),ele[++tot]={t0,dt};
	}
	if(!tot&&f[W]==-INF) return puts("impossible"),0;
	sort(ele+1,ele+1+tot,[](pii x,pii y){return x.fi>y.fi;});
	double cur=0,nxt=1,sum=0;
	ele[tot+1]={-INF,-INF};
	rep(i,1,tot){
		double t0=ele[i].fi,dt=ele[i].sc;
		while(nxt<=W&&t0-(nxt-cur)*dt>=ele[i+1].fi){
			double del=(nxt-cur);
			val[(int)nxt]=sum+t0*del-dt*del*del/2;
			sum=val[(int)nxt],cur=nxt,t0-=del*dt,nxt+=1;
		}
		if(i==tot) break;
		double del=(t0-ele[i+1].fi)/dt;
		sum+=t0*del-dt*del*del/2,cur+=del;
		ele[i+1].sc=dt*ele[i+1].sc/(dt+ele[i+1].sc);
	}
	db ans=-INF;
	rep(i,0,W) ans=max(ans,val[W-i]+f[i]);
	printf("%.10Lf\n",ans);
	fprintf(stderr,"%.4lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}
```

---

## 作者：Astatinear (赞：0)

### [P6893 [ICPC 2014 WF] Buffed Buffet](https://www.luogu.com.cn/problem/P6893)

注意到离散事物是容易的，将所有重量为 $w$ 的放在一起（对于一个食物把 $t_0-(i-1)\times \Delta t$ 都放进去），显然只有最大的 $\frac{W}{i}$ 是有效的，复杂度为调和级数：$\mathcal{O}(W^2\ln W)$。

考虑如何算连续食物。好了又不会了，感觉这几个凸壳合并很难办啊。

显然有贪心策略，一直吃收益最高的，直到当前收益与次高的相同。但是发现到了这里就不太好进行下去了。

考虑对于两种食物，$(t_0,\Delta t_1),(t_0,\Delta t_2),\Delta t_1\not= \Delta t_2$，考虑他们怎么样的比例吃最优：如果 $(t_0,\Delta t_i)$ 吃了 $w_i$ 的重量，那么显然在 $t_0-\Delta t_1\times w_1=t_0-\Delta t_2\times w_2$ 时最优。（类似于一个微元的思想，每次选瞬时收益更多的）此时得到的收益是：$t_0\times w_1-\frac{1}{2}\Delta t_1w_1^2+t_0\times w_2-\frac{1}{2}\Delta t_2 w_2^2$。

注意到 $\frac{w_1}{w_2}=\frac{\Delta t_2}{\Delta t_1}$。令 $w_1=k\times \Delta t_2,w_2=k\times \Delta t_1$。

带回收益：$t_0\times k\times (\Delta t_2+\Delta t_1)-\frac{1}{2}\Delta t_1k^2\Delta t_2^2-\frac{1}{2}\Delta t_2k^2\Delta t_1^2$

可以等效看作是对于食物 $(t_0,\frac{\Delta t_1\times \Delta {t_2}}{\Delta t_1+\Delta t_2})$，吃了 $k\times (\Delta t_1+\Delta t_2)$ 的重量。

也就是说，对于 $t_0$ 相同的两个食物，我们可以看作是一个的等效的食物 $(t_0,\frac{\Delta t_1\times \Delta {t_2}}{\Delta t_1+\Delta t_2})$。

那么回到我们的贪心策略，如果收益与次高的相同了，也就相当于当前 $t_0$ 相同了，那么可以将这两者进行等效合并，然后等到收益到后面和次次高相同，再进行合并，以此贪心。

注意到你要将离散食物和连续食物的重量和价值进行合并，所以算连续食物的复杂度应该是 $\mathcal{O}(nW)$。

发现可以通过，这个等效的思想还是很重要的。

---

## 作者：wgyhm (赞：0)

## Description

https://www.luogu.com.cn/problem/P6893

## Solution

首先显然把离散和连续拆成两个问题，最后 $O(W)$ 合并求最小值即可。

对于离散的，有 $f_{i,j}=\min f_{i-1,j-kw}+F(k)$，$F(k)=kt_0+k(k-1)\Delta t$。

可以把 $F(k)$ 看成 $w(i-k+1,i)$。显然 $w$ 满足四边形不等式，包含的小于相交的。考虑把 $f$ 分成关于 $w$ 的同余系之后分治做决策单调性即可。复杂度 $O(nW\log W)$。似乎有斜率优化做法，但是分治更好写。

对于连续的，观察到二次函数是凸的，其实可以看成 $n$ 个凸函数做 $(\max,+)$ 卷积。考虑闵可夫斯基和的过程，把每个函数的导数画出来，每次拿最大的一段，算一下重量为 $j$ 的时候的面积。复杂度 $O(n\log n+W)$，瓶颈在排序。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define maxn 10005
#define put() putchar('\n')
#define Tp template<typename T>
#define Ts template<typename T,typename... Ar>
using namespace std;
Tp void read(T &x){
    int f=1;x=0;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    x*=f;
}
namespace Debug{
	Tp void _debug(char* f,T t){cerr<<f<<'='<<t<<endl;}
	Ts void _debug(char* f,T x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	#define gdb(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
#define fi first
#define se second
#define mk make_pair
const int mod=1e9+7;
int power(int x,int y=mod-2) {
	int sum=1;
	while (y) {
		if (y&1) sum=sum*x%mod;
		x=x*x%mod;y>>=1;
	}
	return sum;
}
int n,m;
int cnt1,cnt2;
struct node {
	int w,t,dt;
}d[maxn],c[maxn];
bool cmp(node x,node y) {return x.t>y.t;}
const int inf=1e16;
namespace solve1 {
	int n;
	int f[maxn],g[maxn],h[maxn];
	int id;
	int F(int i,int k) {
		if (k<0) return -inf;
		return k*d[i].t-(k*(k-1)/2)*d[i].dt;
	}
	void solve(int l,int r,int L,int R) {
		if (l>r||L>R) return ;
		int mid=l+r>>1,p=L,i;
		for (i=L;i<=R&&i<=mid;i++) 
			if (h[mid]<g[i]+F(id,mid-i)) h[mid]=g[i]+F(id,mid-i),p=i;
		solve(l,mid-1,L,p);
		solve(mid+1,r,p,R); 
	}
	void main(void) {
		n=cnt1;
		int i,j,k,cnt;
		for (i=1;i<=m;i++) f[i]=g[i]=-inf;
		for (i=1;i<=n;i++) {
			int w=d[i].w;id=i;
			for (k=0;k<w;k++) {
				cnt=0;
				for (j=k;j<=m;j+=w) ++cnt,g[cnt]=f[j],h[cnt]=-inf;//g[0]=-inf;
				solve(1,cnt,1,cnt);
				for (j=k;j<=m;j+=w) f[j]=h[(j-k)/w+1];
			}
		}
	}
}
namespace solve2 {
	int n;
	double f[maxn];
	void main(void) {
		n=cnt2;
		int i,j=0;
		sort(c+1,c+1+n,cmp);
		for (i=1;i<=m;i++) f[i]=-inf;f[0]=0;
		c[n+1].t=0;
		double las=0,now,sii=0,si=0,res=0;
		for (i=1;i<=n;i++) {
			double k=c[i+1].t;
			if (c[i].dt!=0) {
				sii+=1.0*c[i].t*c[i].t/c[i].dt;
				si+=1.0*c[i].t/c[i].dt;
				res+=1.0/c[i].dt;
				now=si-k*res;
				now=min(now,(double)m);
				if (i==n) now=m;
				for (;j<=now;j++) {
					double k=1.0*(si-j)/res;
					f[j]=0.5*(sii-k*k*res);
				}
			}
			else {
				now=m;
				for (;j<=now;j++) {
					double k=c[i].t,l=1.0*si-k*res;
					f[j]=0.5*(sii-1.0*k*k*res)+(j-l)*c[i].t;
				}
			}//特判
			if (now>=m) break;
		}
	}
}
signed main(void){
	char ch;int i;
	read(n);read(m);
	for (i=1;i<=n;i++) {
		cin>>ch;
		if (ch=='D') ++cnt1,read(d[cnt1].w),read(d[cnt1].t),read(d[cnt1].dt);
		else ++cnt2,read(c[cnt2].t),read(c[cnt2].dt);
	}
	solve1::main();
	solve2::main();
	double ans=-inf;
	for (i=0;i<=m;i++) ans=max(solve1::f[i]+solve2::f[m-i],ans);
	if (ans<-1e14) puts("impossible");
	else printf("%.10lf\n",ans);
	return 0;
}
//i=begin && g++ $i.cpp -o $i -std=c++14 && ./$i
```



---

## 作者：DaiRuiChen007 (赞：0)

# P6893 题解

[Problem Link](https://www.luogu.com.cn/problem/P6893)

**题目大意**

> 有 $n$ 种物品，分为连续的和离散的：
>
> - 对于连续的物品，取 $w$ 的体积，代价为 $\int_0^w (t_0-x\Delta t)\mathrm dx=t_0w-\dfrac 12\Delta t w$。
> - 对于离散的物品，每取一个，占据 $w$ 的体积，第 $i$ 个的代价为 $t_0-(i-1)\Delta t$。
>
> 求恰好取 $m$ 的体积时可能获得的最大代价。
>
> 数据范围 $n\le 250,m\le 10^4$。

**思路分析**

先考虑对离散物品做背包，朴素暴力把每个物品拆成 $\dfrac mw$ 个物品跑背包是 $\mathcal O(nm^2)$ 的，但注意到对于体积相同的物品，我们只要权值最大的 $\dfrac mw$ 个，这样总的物品数就是调和级别的，时间复杂度 $\mathcal O(m^2\log n)$，常数较小，足以通过本题。

然后考虑连续的物品，我们只要考虑其占据的体积总和是 $[0,m]$ 之间整数的情况即可。

容易发现连续物品占据的体积和代价的关系是一个凸壳，那么我们实际上就是要求若干二次函数的闵可夫斯基和。

考虑闵可夫斯基和的结论，我们可以把二次函数拆成充分多段一次函数，然后按斜率排序。

注意到在拆分出的一次函数数量足够多的时候，这等价于把每个二次函数倒数 $\ge \lambda$ 的一段占据 $x$ 轴的长度求出来，记为 $f(\lambda)$。

那么我们二分找到 $f(\lambda)=i$ 的点即可知道连续物品占据体积为 $i$ 时的最大代价和，事实上，这等价于在 $f(\lambda)\in[0,i]$ 范围内与 $y$ 轴围成的面积。

时间复杂度 $\mathcal O(m^2\log n+mn\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=255,MAXW=1e4+5;
const ll inf=1e18;
const double V=1e8,eps=1e-7;
struct info { int t,d; } a[255];
vector <info> itm[MAXW];
ll dp[MAXW];
int tot,W,n;
double check(double k) { //how many f(x)>=k
	double ans=0;
	for(int i=1;i<=n;++i) if(a[i].t>=k) {
		if(!a[i].d) return inf;
		ans+=(a[i].t-k)/a[i].d;
	}
	return ans;
}
signed main() {
	cin>>tot>>W;
	for(int w,t,d;tot--;) {
		char p; cin>>p;
		if(p=='D') cin>>w>>t>>d,itm[w].push_back({t,d});
		else cin>>t>>d,a[++n]={t,d};
	}
	memset(dp,-0x3f,sizeof(dp)),dp[0]=0;
	for(int w=1;w<=W;++w) if(itm[w].size()) {
		vector <int> vals;
		for(auto p:itm[w]) for(int i=1;i<=W/w;++i) vals.push_back(p.t-p.d*(i-1));
		sort(vals.begin(),vals.end(),greater<int>()),vals.resize(W/w);
		for(int v:vals) for(int i=W;i>=w;--i) dp[i]=max(dp[i],dp[i-w]+v);
	}
	if(!n&&dp[W]<-inf) return puts("impossible"),0;
	double ans=-inf;
	for(int w=0;w<=W;++w) if(dp[w]>=-inf) {
		double l=-V,r=V;
		while(r-l>eps) {
			double mid=(l+r)/2;
			if(check(mid)>=W-w) l=mid;
			else r=mid;
		}
		double tmp=dp[w]+(W-w)*r;
		for(int i=1;i<=n;++i) if(a[i].t>=r&&a[i].d) {
			double s=(a[i].t-r)/a[i].d;
			tmp+=(a[i].t*s-a[i].d*s*s/2)-s*r;
		}
		ans=max(ans,tmp);
	}
	printf("%.8lf\n",ans);
	return 0;
}
```

---


# Trucks and Cities

## 题目描述

有 $n$ 个城市沿着一条公路分布，可以看作在一条直线上。第 $i$ 个城市距离原点 $a_i$ 千米。所有城市都位于原点的同一侧。有 $m$ 辆卡车需要从一个城市开到另一个城市。

每辆卡车由 $4$ 个整数描述：起始城市 $s_i$，终点城市 $f_i$，每公里油耗 $c_i$，以及最多可加油次数 $r_i$。第 $i$ 辆卡车每行驶一公里将消耗 $c_i$ 升油。

当卡车到达某个城市时，可以进行加油（在城市之间的路途中无法加油）。第 $i$ 辆卡车最多可以加油 $r_i$ 次。每次加油都会将油箱加满。所有卡车出发时油箱都是满的。

所有卡车的油箱容量均为 $V$ 升。你需要求出最小的 $V$，使得所有卡车都能在不超过允许加油次数的情况下到达目的地。

## 说明/提示

我们详细分析一下各个询问：

1. 第 $1$ 辆卡车需要从 $2$ 号城市到 $7$ 号城市，中途不能加油，因此油箱容量至少需要 $50$。
2. 第 $2$ 辆卡车需要从 $2$ 号城市到 $17$ 号城市，可以在路径上的任意城市加油，因此油箱容量至少需要 $48$。
3. 第 $3$ 辆卡车需要从 $10$ 号城市到 $14$ 号城市，中间没有城市，因此油箱容量至少需要 $52$。
4. 第 $4$ 辆卡车需要从 $10$ 号城市到 $17$ 号城市，只能加油一次，最优方案是在 $14$ 号城市（第 $5$ 个城市）加油，因此油箱容量至少需要 $40$。
5. 第 $5$ 辆卡车与第 $4$ 辆描述相同，因此油箱容量也至少需要 $40$。
6. 第 $6$ 辆卡车需要从 $2$ 号城市到 $14$ 号城市，可以加油两次：第一次在 $2$ 号或 $3$ 号城市，第二次在 $4$ 号城市，因此油箱容量至少需要 $55$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7 6
2 5 7 10 14 15 17
1 3 10 0
1 7 12 7
4 5 13 3
4 7 10 1
4 7 10 1
1 5 11 2
```

### 输出

```
55
```

# 题解

## 作者：ywy_c_asm (赞：11)

这题可以拿暴力乱搞日过去……

首先有个$O(nm\log ans)$的暴力就是对每个车二分答案，然后贪心的去加油走。最后把每个车去最大值即可。

这样应该是过不去的，考虑一些奇怪的优化：

①考虑到我们是要取最大值，所以我们在二分一个车的答案之前，先判断一下这个车的答案是不是没有之前已经更新的最大答案大，不然就不用求这个车的答案了。另外这样按顺序暴力的话可以把所有车$random\_shuffle$一下以达到期望更好的效果……

②判定的时候并不用$O(n)$走一遍每个位置，我们每次用二分来加速。

~~然后你会发现这暴力跑的飞快~~

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	typedef struct _n {
	    int s;
	    int t;
	    int v;
	    int lim;
	} node;
	node ints[300001];
	int pos[444];
	int mx[444][444];
	inline int Tanxin(int x, ll v) {
	    if (mx[ints[x].s][ints[x].t] * (ll)ints[x].v > v)
	        return (0);
	    int cur = ints[x].s;
	    int tot = 0;
	    while (cur != ints[x].t && tot <= ints[x].lim) {
	        if ((ll)ints[x].v * (pos[ints[x].t] - pos[cur]) <= v)
	            return (1);
	        int ans = cur + 1, l = cur + 1, r = ints[x].t - 1;
	        while (l <= r) {
	            int mid = (l + r) >> 1;
	            if ((ll)ints[x].v * (pos[mid + 1] - pos[cur]) > v)
	                ans = mid, r = mid - 1;
	            else
	                l = mid + 1;
	        }
	        tot++;
	        cur = ans;
	    }
	    if (tot > ints[x].lim)
	        return (0);
	    return (1);
	}
	void ywymain() {
	    srand(19260817);
	    int n = get(), m = get();
	    for (register int i = 1; i <= n; i++) pos[i] = get();
	    for (register int i = 1; i <= m; i++) {
	        ints[i].s = get();
	        ints[i].t = get();
	        ints[i].v = get();
	        ints[i].lim = get();
	    }
	    for (register int i = 1; i <= n; i++) {
	        int maxn = 0;
	        for (register int j = i + 1; j <= n; j++) maxn = max(maxn, pos[j] - pos[j - 1]), mx[i][j] = maxn;
	    }
	    random_shuffle(ints + 1, ints + 1 + m);
	    ll maxn = 0;
	    for (register int i = 1; i <= m; i++) {
	        if (Tanxin(i, maxn))
	            continue;
	        ll ans = ints[i].v * (ll)(pos[ints[i].t] - pos[ints[i].s]);
	        ll l = max((ll)mx[ints[i].s][ints[i].t] * ints[i].v, maxn + 1), r = ans;
	        while (l <= r) {
	            ll mid = (l + r) >> 1;
	            if (Tanxin(i, mid))
	                ans = mid, r = mid - 1;
	            else
	                l = mid + 1;
	        }
	        maxn = max(maxn, ans);
	    }
	    cout << maxn << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：tzc_wk (赞：9)

> 题意：给出 $n$ 个城市的坐标 $a_1,a_2,\dots,a_n$。有 $m$ 辆卡车，第 $i$ 辆从 $s_i$ 走到 $t_i$，每走一格需要耗 $c_i$ 的油。每辆车初始油量为 $V$（$V$ 题目中不会给出），你可以在城市的位置加油，最多加 $k_i$ 次油，每次加油你的油量都会变回 $V$。你需要求出最小的 $V$ 使得每辆车都可以成功完成它的旅行。

> $2 \leq n \leq 400$，$1 \leq m \leq 250000$

题解：区间 dp + two pointers

原题面有些难以下手，不过我们可以将题目进行转换：如果有一辆卡车从 $s$ 行驶到 $t$，每行驶一格需要耗 $c$ 的油，最多可以加 $k$ 次油，那么成功行驶需要的油箱的最小值为：以城市为端点，划分为 $k+1$ 段，它们中长度最大的段的最小值，再乘上 $c$ 就是油箱的大小。最后对于每辆卡车答案取一个 $\max$ 就可以了。

那么怎么求上面所说的值呢？我们设 $dp[i][j][k]$ 为从第 $i$ 个城市到第 $j$ 个城市划分为 $k$ 段的最大的一段的最小值。转移也不难想：枚举最靠右一段的左端点 $l$，那么 $dp[i][j][k]=\min\limits_{l=i}^j \max (dp[i][l][k-1],a[j]-a[l])$。

但是这个转移是 $\mathcal O(n^4)$ 的，完全不可能过得去。但是不难发现一个事情：$dp[i][l][k-1]$ 随 $l$ 的增大而增大，$a[j]-a[l]$ 随 $l$ 的增大而减小。因此就可以想到一定有一个断点 $l'$ 使得对于 $l<l'$，$dp[i][l][k-1] \leq a[j]-a[l]$，对于 $l \geq l'$，$dp[i][l][k-1] \geq a[j]-a[l]$。我们可以用类似 two pointers 的方法 $\mathcal O(1)$ 更新 $l$，这样我们其实只是在 $l$ 与 $l-1$ 之间取较小值。就可以降到 $\mathcal O(n^3)$ 了。

另：$400 \times 400 \times 400$ 的数组会 $\texttt{MLE}$，因此需要滚动数组。

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int dp[405][405][2],a[250005],b[250005],c[250005],d[250005],n=read(),m=read(),t[405];
vector<int> q[250005];
int ans=0;
signed main(){
	fz(i,1,n)	t[i]=read();
	fz(i,1,m){
		a[i]=read();
		b[i]=read();
		c[i]=read();
		d[i]=read();
		d[i]++;
		d[i]=min(d[i],b[i]-a[i]);
		q[d[i]].push_back(i);
	}
	fillbig(dp);
	fz(i,1,n)	fz(j,i,n)	dp[i][j][1]=t[j]-t[i];
	fz(k,1,n-1){
		foreach(it,q[k]){
			ans=max(ans,dp[a[*it]][b[*it]][k&1]*c[*it]);
		}
		fz(i,1,n){
			dp[i][i][(k+1)&1]=0;
			int l=i;
			for(int j=i+1;j<=n;j++){
				while(dp[i][l][k&1]<t[j]-t[l])	l++;
				dp[i][j][(k+1)&1]=min(dp[i][l][k&1],t[j]-t[l-1]);
//				cout<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<dp[i][j][(k+1)&1]<<endl;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
/*
10 10
2 3 4 8 9 10 12 13 15 19
3 8 3 1
3 4 3 2
1 9 2 1
1 9 3 1
6 10 2 1
3 9 2 0
3 7 2 1
2 3 3 0
3 9 2 0
4 10 3 0
*/
```

---

## 作者：白简 (赞：7)

### 题目大意
有 $n$ 个城市坐落在一条数轴上，第 $i$ 个城市位于位置 $a_i$。

城市之间有 $m$ 辆卡车穿行。每辆卡车有四个参数：$s_i$ 为起点编号，$f_i$ 为终点编号，$c_i$ 表示每行驶 $1$ 个单位长度需要消耗的油量，$r_i$ 表示可以在路途中加油的次数。

当卡车到达一个城市的时候可以将油加满（当然也可以不加），在路中无法加油，但是路途中总加油次数不能超过 $r_i$。

所有卡车的油箱都是一样大的，我们称它的容积为 $V$。试求一个最小的 $V$，使得对于所有的卡车都存在一种方案，在路途中任意时刻油箱内的油量大于等于 $0$ 且路途中总加油次数小于等于 $r_i$ 的情况下从起点城市到达终点城市。
### 思路
模拟赛 T3，考场思路是直接二分，对每辆车进行二分，答案取每辆车答案的最大值，时间复杂度 $\operatorname{O}(nm \log n)$。

这样显然会 TLE，我们考虑优化。

1. 考虑判一下记录的答案能否支持当前这辆车走完全程，如果可以，那就不用二分这辆车了，因为它的答案一定比原先的答案小，计算出来也不会更新答案。
2. 对于第一条情况，我们把每辆车的顺序打乱重排能获得更优的期望复杂度。

跑的飞快，直接薄纱正解。
### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 550;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while( ch < '0' || ch > '9' ) {if( ch == '-' ) f=-1;ch=getchar();}
    while( ch >= '0' && ch <= '9' ) {x=x*10+(ch-48);ch=getchar();}
    return x*f;
}

int n,m;

long long pos[N];

struct Trip{
    int s,t;
    long long c,r;
}a[250500];

int Max[N][N];

int i;

bool Check(long long &V) {
    long long dis,need,times = 0,remain = V;

    if(Max[a[i].s][a[i].t] * a[i].c > V)
        return 0;

    for(int j = a[i].s;j < a[i].t; j++) {
        dis = pos[j + 1] - pos[j];
        need = dis * a[i].c;

        if(need <= remain) 
            remain -= need;
        else {
            times ++;
            remain = V - need;
        }
    }

    if(times > a[i].r)
        return 0;
    

    return 1;
}

int main() {
#ifdef ONLINE_JUDGE == 1
    freopen("drive.in","r",stdin);
    freopen("drive.out","w",stdout);
#endif
    n = read();
    m = read();

    for(int i = 1;i <= n; i++) 
        pos[i] = read();

    for(int i = 1;i <= m; i++) {
        a[i].s = read();
        a[i].t = read();
        a[i].c = read();
        a[i].r = read();
    }

    for(int i = 1;i <= n; i++){
        long long maxn = 0;
        for(int j = i + 1;j <= n; j++) {
            maxn = max(maxn,pos[j] - pos[j - 1]);
            Max[i][j] = maxn;
        }
    }

    random_shuffle(a + 1,a + m + 1);

    long long ans = 0;

    for(i = 1;i <= m; i++) {
        if(Check(ans))
            continue;

        long long l = max(Max[a[i].s][a[i].t] * a[i].c,ans + 1);
        long long r = (pos[a[i].t] - pos[a[i].s]) * a[i].c;
        long long mid,res = r;

        while(l <= r) {
            mid = (l + r) >> 1;

            if(Check(mid)) {
                r = mid - 1;
                res = mid;
            }
            else 
                l = mid + 1;
        }

        ans = max(ans,res);
    }
    
    cout << ans << "\n";
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```

---

## 作者：Sol1 (赞：5)

一句话题意：长度为 $n$ 的序列 $a_{[1,n]}$，$m$ 次查询，每次查询给定 $l,r,c,k$，你需要选出一个序列 $l<b_1<b_2<\cdots<b_k<r$，使得 $\max\limits_{1\leq i<k}a_{b_{i+1}}-a_{b_i}$ 最小。设这个值为 $v$，输出所有询问的 $c\cdot v$ 取 $\max$。$n\leq 400,m\leq 2.5\times 10^5$。

$n$ 很小，所以考虑区间 DP。

于是有一个很显然的状态：设 $f(i,j,k)$ 为区间 $[i,j]$ 中，选 $k$ 个点，最大间距的最小值。

然后去考虑最后一个点。

如果最后一个点是 $l$，那么前面的贡献自然是 $f(i,l,k-1)$，最后一段的贡献是 $a_j-a_l$，于是就有如下转移：

$$f(i,j,k)=\min_l\max\{f(i,l,k-1),a_j-a_l\}$$

然后你就得到了一个 $O(n^4)$ 的优秀做法！

这个 $f$ 有明显的单调性：$i,k$ 不变时，$f(i,j,k)\leq f(i,j+1,k)$。并且 $a_j-a_l>a_j-a_{l+1}$。

那么可以看出最小值取在两个函数图像交点的地方。

然后发现随着 $j$ 的移动，这两个函数图像的交点也是单调递增的。

所以在枚举 $j$ 的时候搞个指针暴力爬，每次直接用这个指针转移。

然后你就得到了一个时空 $O(n^3)$ 的优秀做法！

为了优化空间，可以调换枚举顺序，先枚举 $k$，把每一次询问按照 $k$ 开个邻接表存起来，就可以滚动了。

最终时间 $O(n^3+m)$，空间 $O(n^2+m)$。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline long long Abs(const long long& x) {return (x > 0 ? x : -x);}
inline long long Max(const long long& x, const long long& y) {return (x > y ? x : y);}
inline long long Min(const long long& x, const long long& y) {return (x < y ? x : y);}

int dp[2][405][405], s[250005], t[250005], c[250005], r[250005], n, m, a[405];
vector <int> v[405];

inline void Read() {
	n = qread(); m = qread();
	for (int i = 1;i <= n;i++) a[i] = qread();
	for (int i = 1;i <= m;i++) {
		s[i] = qread();
		t[i] = qread();
		c[i] = qread();
		r[i] = qread();
		v[r[i] + 1].push_back(i);
	}
}

inline void Solve() {
	memset(dp[0], 0x3f, sizeof(dp[0]));
	long long minv = 0;
	for (int i = 1;i <= n;i++) dp[0][i][i] = 0;
	for (int i = 1;i <= n + 1;i++) {
		memset(dp[i & 1], 0x3f, sizeof(dp[i & 1]));
		for (int j = 1;j <= n;j++) dp[i & 1][j][j] = 0;
		for (int j = 1;j <= n;j++) {
			int idx = j;
			for (int k = j + 1;k <= n;k++) {
				while (idx < k && a[k] - a[idx + 1] > dp[!(i & 1)][j][idx + 1]) idx++;
				dp[i & 1][j][k] = Min(Max(dp[!(i & 1)][j][idx], a[k] - a[idx]), Max(dp[!(i & 1)][j][idx + 1], a[k] - a[idx + 1]));
			}
		}
		int siz = v[i].size();
		for(int j = 0;j < siz;j++) {
			int id = v[i][j];
			int dist = dp[i & 1][s[id]][t[id]];
			//printf("%d %lld\n", id, 1ll * dist * c[id]);
			minv = Max(minv, 1ll * dist * c[id]);
		}
	}
	printf("%lld", minv);
}

int main() {
	Read();
	Solve();
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}

```

---

## 作者：irris (赞：4)

存在非 dp 的做法。令 $V$ 是值域的平方，因为答案最大值是 $c_i \times a_n$。

如果只有一辆车，可以二分做到 $\mathcal O(n\log V)$ 判定。

那这样就有人会去写 $\mathcal O(nm \log V)$，算一下是 $6\times 10^9$ 的样子，松一松可能能过。

但是我们有更好的二分方法——我们不用对每辆车都二分一遍，因为我们要求的只是 $m$ 辆车的答案 max。

回忆一个经典结论：对于长度为 $k$ 的随机排列，前缀最大值的个数是 $\mathcal O(\log k)$。

> **证明**：考虑 $x$ 若产生贡献，我们把 $x \sim k$ 这 $k - x + 1$ 个数按顺序提出来，发现 $x$ 肯定是这 $k - x + 1$ 个数中的第一个数，概率为 $\dfrac{1}{k-x+1}$。全部加起来，$\dfrac11+\dfrac12+\dots+\dfrac1k$，积分可知是 $\mathcal O(\log k)$ 量级的。

这启发我们给 $m$ 辆车 shuffle，然后对于每辆车，**先用之前的答案判定它的答案是不是前缀最大值，如果是，再进行二分**。根据上面的证明，这种做法的期望复杂度为 $\mathcal O(n\log m \log V + m \log V)$，可以通过。

---

## 作者：是个汉子 (赞：4)

### Solution

设 $f[i][j][k]$ 表示一辆每公里耗油量为 $1$ 的货车从 $i$ 到 $j$ 中途加 $k$ 次油最小的油箱容量。枚举起点 $st$ 和加油的次数 $k$ ，这样就固定了两维，显然有DP方程：
$$
f[i][j][k]=\min\limits_{i\leq p\leq j}(\max(f[i][p][k-1],a[j]-a[p]))
$$
这是 $O(n^4)$ 的，但是我们发现 $p$ 增加的时候， $f[i][p][k-1]$ 是单增的， $a[j]-a[p]$ 是单减的，所以可以找出区间的决策点，即对整个区间进行分治。

然后复杂度就变成了 $O(n^3)$ 。

#### 代码

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long

using namespace std;
const int N=405;
int n,m,a[N],f[N][N][N];//f[i][j][k]代表i到j分成k+1段

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

void solve(int st,int k,int l,int r,int ql,int qr){
    if(l>r) return ;
    int mid=(l+r)>>1,opt=0,temp=0;
    for(int i=ql;i<=min(qr,mid);i++)
        if(!opt||max(a[mid]-a[i],f[st][i][k-1])<temp)
            temp=max(a[mid]-a[i],f[st][i][k-1]),opt=i;
    f[st][mid][k]=temp;
    solve(st,k,l,mid-1,ql,opt);
    solve(st,k,mid+1,r,opt,qr);
}

int main(){
    n=read();m=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++) f[i][j][0]=a[j]-a[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            solve(i,j,i+1,n,i+1,n);
    ll ans=0;
    for(int i=1;i<=m;i++){
        int s=read(),t=read(),c=read(),r=read();
        ans=max(ans,1ll*f[s][t][r]*c);
    }
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：xiezheyuan (赞：2)

## 思路

首先考虑朴素的思路：设 $f(i,j,k)$ 表示汽车从 $i$ 开到 $j$ 中途加 $k$ 次油的最小代价。

转移的话可以枚举第 $k-1$ 次加油的位置，前面做一次后面做一次。

也就是：

$$
f(i,j,k)=\begin{cases}
c(a_j-a_i) & k = 0\\
\min\limits_{s=i}^{j}\max(f(i,s,k-1),f(i,s,0)) & \text{otherwise}
\end{cases}
$$

时间复杂度是惊人的 $O(n^4)$。难以通过本题。

考虑到 $f(i,s,0)$ 满足四边形不等式。则 $f(i,j,k)$ 固定 $k$ 时亦满足四边形不等式。我们可以使用决策单调性优化。

具体来说固定 $i,k$ 找 $j$。我们分治找最优决策点。然后下一层的最优决策点一定在上一层最优决策点的左右两侧。

把 $c$ 提出来做到 $O(1)$ 单次询问。

于是我们就在 $O(n^3\log n+m)$ 的优秀时间复杂度内实现了本题。

## 关键代码

注意：

- 十年 OI 一场空，不开 `long long` 见祖宗。
- 本题卡空。请妥善思考何时应该开 `long long`，何时不需要开。

```cpp
const int N = 405;
int f[N][N][N],a[N];

int n,m;

int w(int ql,int k,int x,int y){
	return max(a[y]-a[x], f[ql][x][k-1]);	
}

void dp(int ql,int k,int l,int r,int sl,int sr){
	if(l>r) return;
	int mid = ((l+r)>>1),s=sl;
	for(int i=sl;i<=min(sr,mid-1);i++){
		if(w(ql,k,i,mid) < w(ql,k,s,mid)) s=i;
	}
	f[ql][mid][k]=w(ql,k,s,mid);
	dp(ql,k,l,mid-1,sl,s);
	dp(ql,k,mid+1,r,s,sr);
}

signed main(){
	io>>n>>m;
	for(int i=1;i<=n;i++) io>>a[i];
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++) f[i][j][0]=a[j]-a[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) dp(i,j,i,n,i,n);
	}
	long long ans=0;
	while(m--){
		long long s,t,c,r;
		cin>>s>>t>>c>>r;
		ans = max(ans, f[s][t][r]*c);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Eon_Sky (赞：1)

#### [$\color{blueviolet}\text{CF 杂题集（点我）}$](https://www.cnblogs.com/Eon-Sky/p/17763683.html)

#### [$\color{red}\text{博客内食用效果更佳（点我）}$](https://www.luogu.com.cn/blog/Eon/solution-cf1101f)

## 主体思路：二分+随机化性质

## 复杂度：$O(n \log m \log V + m\log V)$

## 完整思路

用到了一个奇妙 Trick。

对于每辆车可以考虑二分油箱容量，进行贪心验证，每次不能走了就加油，最后判断加油次数是否小于限制即可。

如果暴力二分是 $nm\log V$ 的，不太能接受，发现其中有一些答案是无用的，比如前 $i - 1$ 辆卡车的答案为 $ans$，第 $i$ 辆卡车在 $ans$ 的情况下合法，我们就无需计算 $i$ 的答案。

这样有了一些小剪枝，但发现当答案单调上升的时候复杂度仍然会卡到上界，考虑随机化优化一下。

有如下结论：对于长度为 $n$ 的随机序列，前缀最大值的个数为 $O(\log n)$。

> 证明是简单的。对于一个**排名**为 $x$ 的数字，需要保证所有比它大的数字都要出现在其后面，则其为一个前缀最大值。我们将排名依次为 $x, x + 1, \dots , n$ 的数字作为一个子序列拿出来，$x$ 为前缀最大值的概率等价为 $x$ **在这个子序列中是第一个数的概率**，所以有其概率为 $\frac{1}{n - x + 1}$。期望个数即 $\frac{1}{1} + \frac{1}{2} + \dots + \frac{1}{n}$，积分后可以得到是 $O(\log n)$ 的。

所以我们对于每辆卡车随机赋权值，并按照权值排序，这样得到的前缀答案最大值期望个数为 $O(\log m)$，所以总期望复杂度为 $O(n \log m \log V + m\log V)$，可以接受。

## 代码实现需要注意的地方：

- 油箱容量需要开 **long long**。

- 二分的上界是值域的平方级别的，需要开到 $10^{18}$。

## 参考代码：

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int UIT;
typedef double DB;
typedef pair<int, int> PII;

#define fi first
#define se second
//--------------------//
const int N = 400 + 5, M = 25e4 + 5;
const LL V = 1e18;

int n, m, p[N];

struct Track {
    int s, t, c, r;
    UIT key; // 随机赋的权值
} t[M];

bool cmp(Track x, Track y) {
    return x.key < y.key;
}

mt19937 Eon(998247);

bool check(Track now, LL v) { // 贪心验证
    int cnt = 0; LL nv = v;
    for (int i = now.s + 1; i <= now.t; i++) {
        if (1LL * now.c * p[i] > v) // 如果消耗大于油箱容量则无解
            return false;
        if (1LL * now.c * p[i] > nv) // 需要加油则加油
            nv = v, cnt++;
        nv -= 1LL * now.c * p[i];
    }
    return cnt <= now.r; // 判断是否合法
}
//--------------------//
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &p[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d%d", &t[i].s, &t[i].t, &t[i].c, &t[i].r), t[i].key = Eon(); // 随机赋权
    for (int i = n; i >= 1; i--)
        p[i] -= p[i - 1]; // 分解为每段的距离
    sort(t + 1, t + m + 1, cmp);
    LL ans = 0;
    for (int i = 1; i <= m; i++) {
        if (check(t[i], ans)) // 如果已经合法则没必要做
            continue;
        LL l = ans + 1, r = V;
        while (l <= r) {
            LL mid = l + r >> 1;
            if (check(t[i], mid))
                ans = mid, r = mid - 1;
            else
                l = mid + 1;
        }
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：5k_sync_closer (赞：0)

来点神秘做法，复杂度是对的，而且会比 DP 优。

考虑逐个二分，发现复杂度 $O(nm\log V)$ 寄了。

考虑加点剪枝，发现若某段行程的答案 $\le$ 当前答案则不用对它二分，而这个判断可以 $O(n)$ 完成。

此时只会在每个前缀最大值处二分，发现答案递增还是会寄，

于是使用小杀招，shuffle 所有行程，此时前缀最大值只有 $\log m$ 个，总复杂度 $O(n\log m\log V+nm)$。

```cpp
#include <cstdio>
#include <random>
#include <algorithm>
#define int long long
using namespace std;
int n, m, z, R, a[250050];
struct Q
{
    int s, t, c, r;
} q[250050];
bool C(int o, int k)
{
    for (int i = q[o].s, z = 0, p = 0; i < q[o].t; ++i)
    {
        if (q[o].c * (a[i + 1] - a[i]) > k)
            return 0;
        if (z + q[o].c * (a[i + 1] - a[i]) > k)
        {
            if (++p > q[o].r)
                return 0;
            z = q[o].c * (a[i + 1] - a[i]);
        }
        else
            z += q[o].c * (a[i + 1] - a[i]);
    }
    return 1;
}
signed main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", a + i);
    for (int i = 1; i <= m; ++i)
        scanf("%lld%lld%lld%lld", &q[i].s, &q[i].t, &q[i].c, &q[i].r), R = max(R, q[i].c * (a[q[i].t] - a[q[i].s]));
    shuffle(q + 1, q + m + 1, default_random_engine());
    for (int i = 1, l, r, M; i <= m; ++i)
        if (!C(i, z))
        {
            for (l = z, r = R; l <= r;)
                if (C(i, M = l + r >> 1))
                    r = M - 1;
                else
                    l = M + 1;
            z = l;
        }
    printf("%lld", z);
    return 0;
}
```


---

## 作者：int_R (赞：0)

模拟赛 T3，感觉挺一眼的。

定义 $f_{i,j,k}$ 为从 $i$ 到 $j$ 中间加了 $k$ 次油，中间 $k+1$ 段路程最大值最小为多少。

答案为 $\max\limits_{i=1}^{m} (f_{s_i,t_i,r_i}\times c_i)$。

朴素转移方式：

$$f_{i,j,k}=\begin{cases}a_j-a_i & k=0\\ \min\limits_{c=i+1}^{j} \max(f_{i,c,k-1},a_j-a_c) & k>0\end{cases}$$

状态数 $O(n^3)$，单次转移 $O(n)$，总时间复杂度 $O(n^4)$ 寄了。考虑优化转移。

将 $f_{i,j,k}$ 的最优决策点记为 $c$，即 $f_{i,j,k}$ 是由 $f_{i,c,k-1}$ 转移过来的。将 $f_{i,j+1,k}$ 的决策点记为 $c'$，容易发现 $c'\geq c$。

很容易感性理解，但作为题解还是应当给出证明。

如果 $f_{i,j+1,k}$ 从 $c$ 转移过来，应为 $\max(f_{i,c,k-1},a_j-a_c+a_{j+1}-a_j)\leq\max(f_{i,c,k-1},a_j-a_c)+a_{j+1}-a_j= f_{i,j,k}+a_{j+1}-a_j$。

若现在 $c'<c$，从 $c'$ 转移过来即为 $\max(f_{i,c',k-1},a_j-a_{c'}+a_{j+1}-a_j)\leq \max(f_{i,c',k-1},a_{j}-a_{c'})+a_{j+1}-a_j$。

若 $\max(f_{i,c',k-1},a_{j}-a_{c'})<f_{i,j,k}$ 那么 $c$ 就不是 $f_{i,j,k}$ 的最优决策点了，所以 $\max(f_{i,c',k-1},a_{j}-a_{c'})\geq f_{i,j,k}$，即 $c'$ 不可能比 $c$ 优。

所以我们并不需要每次从 $i+1$ 开始枚举 $c$，只需要从上一个的最优决策点继续往后枚举，这样均摊转移复杂度 $O(1)$，总时间复杂度 $O(n^3)$。据说有很优的非 DP 做法。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
    return x*f;
}
const int MAXN=410;
int n,m,p[MAXN][MAXN],tot;
long long ans,a[MAXN],f[80210][MAXN];
int main()
{
    n=read(),m=read();
    for(register int i=1;i<=n;++i) a[i]=read();
    for(register int i=1;i<=n;++i)
        for(register int j=i+1;j<=n;++j)
            p[i][j]=++tot,f[p[i][j]][0]=a[j]-a[i];
    for(register int k=1;k<=n;++k)
        for(register int i=1;i<=n;++i)
        {
            int cur=i+1;
            for(register int j=i+1;j<=n;++j)
            {
                while(cur<j&&max(f[p[i][cur]][k-1],a[j]-a[cur])>=max(f[p[i][cur+1]][k-1],a[j]-a[cur+1])) ++cur; 
                f[p[i][j]][k]=max(f[p[i][cur]][k-1],a[j]-a[cur]);
            }
        }
    while(m--)
    {
        int s=read(),t=read(),c=read(),r=read();
        ans=max(ans,1ll*f[p[s][t]][r]*c);
    }
    cout<<ans<<'\n';
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```

---

## 作者：lfxxx (赞：0)

考虑设计一个 dp 状态 $dp_{i,j,k}$ 表示从城市 $i$ 到城市 $j$ 加油 $k$ 次单位路程花费单位油量所需要的最小油箱容量，不难发现 $c$ 这个限制只要在最后的时候乘到答案上就可以了，因为无论如何同一辆车油量耗费是一样的，所以只用计算单位油量耗费就行了，所以下面考虑怎么转移这个 dp 方程。

有 $dp_{i,j,k} = \min(\max(dp_{i,p,k-1},a_j - a_p))$ 又因为 $a_j - a_p$ 满足四边形不等式，所以原 dp 具有决策单调性，考虑分治优化即可。

时间复杂度 $O(n^3 \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 405;
int dp[maxn][maxn][maxn];//从城市 i 到城市 j 加油 k 次单位油耗位 1 的最小邮箱大小
int a[maxn];
void solve(int l,int r,int L,int R,int i,int k){
	if(l>r) return ;
	int mid=(l+r)>>1;
	int mi=1e9+7,p=L;
	for(int j=max(L,i);j<=min(R,mid);j++){
		if(max(dp[i][j][k-1],a[mid]-a[j])<mi){
			mi=max(dp[i][j][k-1],a[mid]-a[j]);
			p=j;
		}
	}
	dp[i][mid][k]=mi;
	solve(l,mid-1,L,p,i,k);
	solve(mid+1,r,p,R,i,k);
}   
long long n,m,ans;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++) dp[i][j][0]=a[j]-a[i];
	for(int i=1;i<=n;i++){
		for(int k=1;k<=n;k++){
			solve(1,n,1,n,i,k);
		}
	}
	for(int i=1;i<=m;i++){
		int s,t,r;
		long long c;
		cin>>s>>t>>c>>r;
		ans=max(ans,dp[s][t][r]*c);
	}
	cout<<ans;
}
```


---

## 作者：intel_core (赞：0)

观察到数据范围里 $n$ 很小但 $m$ 很大。

记 $f_{l,r,k}$ 为从 $l$ 到 $r$ ，加油 $k$ 次，两次加油之间里程的最大值 的最小值（出发时加油不计入其中）。

如果直接区间 $\text{DP}$ 的话，复杂度是 $O(n^4)$ 的。

很明显，对于区间划分问题，一定是决策单调的。

具体来说，令 $g_{l,r,k}$ 满足 $f_{l,r,k}=max \{ f_{l,g_{l,r,k},k-1},a[r]-a[g_{l,r,k}] \}$，即第 $k$ 次加油在 $g_{l,r,k}$ 时 $f_{l,r,k}$ 取等。

那么一定满足 $g_{l,r-1,k} \le g_{l,r,k} \le g_{l+1,r,k}$。

这样就可以愉快地 $O(n^3)$ 求出 $f$ 数组了。

求询问 $s,t,c,r$ 的答案也很简单，就是 $f_{s,t,r} \times c$。

但是，空间只有 $\text{256MB}$，所以需要用一个滚动数组，把 $k$ 那一维滚掉。

只需要把所有的询问按照 $r$ 升序排序，求完 $f_k$ 之后就把所有 $r=k$ 的询问处理了。

总复杂度 $O(n^3+m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=410;
const int MR=3e5+10;
#define int long long
int n,m,a[NR],ans;
int f[2][NR][NR],g[NR][NR];

struct task{
	int l,r,c,x;
	bool operator <(const task &T)const{
		return x<T.x;
	}
}t[MR];

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)
		scanf("%lld%lld%lld%lld",&t[i].l,&t[i].r,&t[i].c,&t[i].x),t[i].x=min(t[i].x,max(0ll,t[i].r-t[i].l-1));
	sort(t+1,t+1+m);
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)f[0][i][j]=a[j]-a[i];
	int idx=1;
	while(idx<=m&&!t[idx].x)ans=max(ans,f[0][t[idx].l][t[idx].r]*t[idx].c),idx++;
	for(int i=1;i<=n;i++){
		int now=i&1,pre=now^1;
		for(int j=1;j+i+1<=n;j++)
			g[j][j+i+1]=j+i,f[now][j][j+i+1]=max(f[pre][j][j+i],a[j+i+1]-a[j+i]);
		for(int len=i+2;len<n;len++)
			for(int l=1,r;l+len<=n;l++){
				r=l+len;f[now][l][r]=1e18;
				for(int j=g[l][r-1];j<=g[l+1][r];j++)
					if(f[now][l][r]>max(f[pre][l][j],a[r]-a[j]))g[l][r]=j,f[now][l][r]=max(f[pre][l][j],a[r]-a[j]);
			}
		while(idx<=m&&t[idx].x==i)
			ans=max(ans,f[now][t[idx].l][t[idx].r]*t[idx].c),idx++;
		if(idx>m)break;
	}
	cout<<ans<<endl;
	return 0;
} 
```

---


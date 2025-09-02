# [CEOI 2018] Lottery

## 题目背景

译自 CEOI2018 Day1 T3. [Lottery](https://ceoi2018.pl/wp-content/uploads/2018/08/lot.pdf)。

## 题目描述

**请注意特殊的内存限制。**

长期以来，你一直是 Bytelotto 的忠实粉丝，但你的家人一直告诉你所有这样的游戏都是在浪费钱。你觉得这肯定是因为他们缺少技巧。你有一个很棒的计划，每个人都将很快看到你赢得游戏。

游戏类型很多，你对其中之一感兴趣：Bitlotto。游戏规则很简单，每天随机抽取一个数字作为中奖数字。你记下了连续 $n$ 天的中奖数字 $a_1, a_2, \ldots, a_n$。你确信这当中存在某种规律，尤其是连续 $l$ 天的区间中。你的家人仍然不相信你，所以说服他们的唯一方法是可靠的数学。

一共有 $n-l+1$ 个长度为 $l$ 的区间。第 $i$ 个区间从 $i$ 开始，因此它包含元素 $a_i, a_{i+1}, \ldots, a_{i+l-1}$。定义两个区间的距离为他们对应位置上的数字不相等的数量。形式化地说，第 $x$ 个区间与第 $y$ 个区间的距离为满足 $a_{x+i}\ne a_{y+i}$ 的位置 $i\ (0\le i < l)$ 的数量。然后我们定义两个区间是 $k$-相似的当且仅当这两个区间的距离不超过 $k$。

现在给出连续 $n$ 天的中奖数字和 $q$ 个询问，每个询问给出一个整数 $k_j$，你需要对序列中的每个长度为 $l$ 的区间，求出与该区间 $k_j$-相似的区间个数（不包括本身）。

## 说明/提示

#### 样例解释

整个序列有五个长度为 $2$ 的区间：

- 第一个区间包含 $1$ $2$；
- 第二个区间包含 $2$ $1$；
- 第三个区间包含 $1$ $3$；
- 第四个区间包含 $3$ $2$；
- 第五个区间包含 $2$ $1$。

共有两个询问。

第一个询问 $k=1$。第一个和第三个区间——$1$ $2$ 和 $1$ $3$——只有第二个位置不同，所以他们的距离为 $1$。类似地，第一个和第四个区间——$1$ $2$ 和 $3$ $2$——只有第一个位置不同，所以他们的距离为 $1$。与第一个区间 $1$-相似的区间只有这两个，所以第一个数输出 $2$。

第二个询问 $k=2$，所有区间都是 $2$-相似的。

#### 数据规模与约定

对于 $100\%$ 的数据，$1\le n\le 10^4,\ 1\le a_i\le 10^9,\ 1\le q\le 100,\ 0\le k_j\le l$。

所有测试数据被划分成若干个有附加限制的子任务，每个子任务中包含若干测试点。

| 子任务 | 附加限制 | 分值 |
| :--------: | :------------: | :--: |
|    $1$     |  $n \le 300$  | $25$ |
|    $2$     | $n \le 2000$  | $20$ |
|    $3$     | $q=1, k_1=0$ | $20$ |
|    $4$     |     $q=1$      | $15$ |
|    $5$     |   无附加限制   | $20$ |

## 样例 #1

### 输入

```
6 2
1 2 1 3 2 1
2
1
2```

### 输出

```
2 1 1 1 1
4 4 4 4 4```

# 题解

## 作者：7KByte (赞：3)

考虑到 $N\le 10^4$ ，显然是 $\mathcal{O}(N^2)$ 可过。

所以我们可以直接枚举两个区间计算贡献。

显然如果我们知道两两区间的距离，可以直接前缀和 $\mathcal{O}(NQ)$ 求出最终答案。

现在我们计算两两区间的距离，直接枚举并匹配是 $\mathcal{O}(N^3)$ ，但是不难发现 $([l_1, r_1], [l_2, r_2])$ 和 $([l_1+1, r_1+1], [l_2 + 1, r_2 + 1])$ 只有头尾两位不同，我们枚举 $l_1$，和差 $l_2 - l_1$，然后可以递推出所有结果。

时间复杂度 $\mathcal{O}(N^2+NQ)$。

```cpp
/*
    Author : SharpnessV
    Right Output ! & Accepted !
*/
#include<bits/stdc++.h>
//#define int long long

#define rep(i, a, b) for(int i = (a);i <= (b);i++)
#define pre(i, a, b) for(int i = (a);i >= (b);i--)
#define rp(i, a) for(int i = 1; i <= (a); i++)
#define pr(i, a) for(int i = (a); i >= 1; i--)
#define go(i, x) for(auto i : x)

#define mp make_pair
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define ze(p) memset(p, 0, sizeof(p))
#define mem(p, x) memset(p, x, sizeof(p))
#define YES puts("YES")
#define NO puts("NO")
#define si(x) (int)(x).size()
#define db cerr
#define pc putchar
#define el putchar('\n')

using namespace std;
const double eps = 1e-15, pi = 3.1415926535897932385;
typedef long long LL;
typedef pair<int,int> Pr;
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}, inf = 0x7fffffff;

//char buf[1<<22],*p1=buf,*p2=buf;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read(){
    int x = 0;bool f = 1;char ch = getchar();
    while(!isdigit(ch))f = ('-' == ch ? 0 : 1), ch = getchar();
    while(isdigit(ch))x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    if(f)return x;return -x;
}
inline LL Read(){
    LL x = 0;bool f = 1;char ch = getchar();
    while(!isdigit(ch))f = ('-' == ch ? 0 : 1), ch = getchar();
    while(isdigit(ch))x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    if(f)return x;return -x;
}
int gcd(int x,int y){return y ? gcd(y, x % y) : x;}
int lcm(int x,int y){return x / gcd(x, y) * y;}
#define P 1000000007
//#define P 998244353
#define bas 229
inline void ad(int &x, int y){x += y; if(x >= P) x -= P;}
inline void su(int &x, int y){x -= y; if(x < 0) x += P;}
inline void cmn(int &x,int y){if(y < x) x = y;}
inline void cmx(int &x,int y){if(y > x) x = y;}

int Pow(int x, int y){
	if(y < 0)return Pow(Pow(x, P - 2), -y);
	int now = 1 ;
	for(;y;y >>= 1, x = 1LL * x * x % P)if(y & 1) now = 1LL * now * x % P;
	return now;
}
#define N 10005
int n, m, l, a[N], ans[102][N], k[N], mat[N], w[N];
int main(){
	//int T = read();while(T--)solve();
	//freopen("INPUT","r",stdin);
	n = read(), l = read();
	rp(i, n)a[i] = read();
	m = read();
	rp(i, m)w[i] = k[i] = read();
	sort(k + 1, k + m + 1);
	rp(i, m)mat[k[i]] = i;
	mat[l + 1] = m + 1;pre(i, l, 0)if(!mat[i])mat[i] = mat[i + 1];
	//rep(i, 0, l)printf("%d ",mat[i]);el;
	rep(i, 1, n - l){
		int sum = 0;
		rep(j, 0, l - 1)sum += a[1 + j + i] != a[1 + j];
		//cout<<"ss "<<i + 1<<" "<<sum<<endl;
		rep(j, 0, n - l - i){
			ans[mat[sum]][1 + j]++, ans[mat[sum]][i + j + 1] ++;
			sum -= a[1 + j] != a[1 + i + j];
			sum += a[j + l + 1] != a[i + j + l + 1];
		} 
	}
	rp(i, m)rp(j, n - l + 1)ans[i][j] += ans[i - 1][j];
	rp(i, m){rp(j, n - l + 1)printf("%d ",ans[mat[w[i]]][j]);el;}
	return 0;
}

```

---

## 作者：fight_for_humanity (赞：2)

#### [题目](https://www.luogu.com.cn/problem/P6360)

暴力处理每两个区间的距离，时间复杂度 $O(n^2l)$，空间也撑不住。

对于题目中的定义，我们自然发现两个区间的“距离”计算是可继承的，即 $[l1,r1]$ 与 $[l2,r2]$，到 $[l1+1,r1+1]$ 与 $[l2+1,r2+1]$。

对于每一组移动区间，其相对位置是不变的。

那么我们就有实现：

- 枚举起始的 $l2$，每次的 $l1$ 最开始都为 $1$。
- 先统计 $[1,l]$ 与 $[l2,l2+l-1]$ 的结果 $tot$。
- 右移区间，每次：
    1. 左区间少了个 $a[l1]$，右区间少了个 $a[l2]$，若二者不同，则 `--tot`。
    1. 左区间多了个 $a[r1+1]$，右区间多了个 $a[r2+1]$，若二者不同，则 `++tot`。
    1. 记入 $cnt$ 数组，`cnt[i][j]` 表示对于区间 $[i,i+l-1]$ 的结果为 $j$ 的区间的数量。

由于我们可以将 $cnt$ 中的 $j$ 这维离散化，那么空间就变为 $O(nq)$，再加上可以用 `short`，空间就十分优秀了。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
short cnt[10010][105];
short trans[10010],r[105];
int n,l,a[10010],q,b[105];
int main(){
	scanf("%d%d",&n,&l);
	for(int i = 1;i<=n;++i)scanf("%d",&a[i]);
	scanf("%d",&q);
	for(int i = 1;i<=q;++i)scanf("%d",&r[i]),b[i] = r[i];
	sort(b+1,b+q+1);
	int siz = unique(b+1,b+q+1)-b-1;
	for(int i = 1;i<=q;++i)r[i] = lower_bound(b+1,b+siz+1,r[i])-b;
	int pos = 1;
	for(int i = 1;i<=n;++i){
		while(pos <= siz && b[pos] < i)++pos;
		trans[i] = pos;
	}
//	sign();
//	for(int i = 1;i<=n;++i)cout << trans[i] << " ";
//	puts(""),sign();
	for(int i = 2;i+l-1<=n;++i){
		int tot = 0;
		for(int j = 1;j<=l;++j)if(a[j] != a[i+j-1])++tot;
		++cnt[i][trans[tot]];
		++cnt[1][trans[tot]];
		for(int j = 1;i+l-1+j<=n;++j){
			// -a[j] +a[j+l]
			// -a[i+j-1] +a[i+j+l]
			if(a[j] != a[i+j-1])--tot;
			if(a[j+l] != a[i+j+l-1])++tot;
			++cnt[i+j][trans[tot]];
			++cnt[j+1][trans[tot]];
		}
	}
	for(int i = 1;i<=n-l+1;++i)
		for(int j = 1;j<=siz;++j)cnt[i][j] += cnt[i][j-1];
	for(int i = 1;i<=q;++i){
		for(int j = 1;j<=n-l+1;++j)printf("%d ",cnt[j][r[i]]);
		puts("");
	}
	return 0;
}
/*
继承
[l1,r1]
[1,l]
[i,i+m-1]

[j,j+l-1]
[i+j-1,i+j+l-2]
*/

```

---

## 作者：Add_Catalyst (赞：1)

# P6360 [CEOI2018] Lottery 题解

---

## 题意分析

给一段长度为 $n$ 的数列 $\{ a_i \}$，子段长度 $l$，$q$ 个询问。

每次询问输入 $k$，求与每一段长度为 $l$ 的子段数字差别个数 $\le k$ 的子段个数（除自己外）。

---

## 思路分析

首先，直接暴力比较每一个子段，再用前缀和统计，可以做到时间复杂度 $O(n^2l)$，空间复杂度 $O(n^2)$。

考虑优化：观察数据范围：$1 \le n \le 10^4,1 \le q \le 10^2$，那么程序是可以支持时间复杂度 $O(n^2)$ 的算法的。

于是我们双指针移动区间进行比较，每次钦定两个子段的距离即可，最后前缀和，时间复杂度 $O(n^2)$，空间复杂度 $O(n^2)$。

可是，“**请注意特殊的内存限制**”，空间复杂度 $O(n^2)$ 是不行的，那怎么办呢？

我们发现 $O(nq)$ 的空间复杂度是可以的，那么我们离线询问，直接将中间没有询问的差值叠加到一旁的询问即可。

---

## CODE

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define ll long long
#define max(a,b) ((a)<(b)?(b):(a))
#define min(a,b) ((a)>(b)?(b):(a))
#define tomax(a,b) ((a)=max((a),(b)))
#define tomin(a,b) ((a)=min((a),(b)))
#define RCL(a,b,c,d) memset((a),(b),sizeof(c)*(d))
#define FOR(i,a,b) for(register int i=(a);i<=(b);++i)
#define DOR(i,a,b) for(register int i=(a);i>=(b);--i)
#define EDGE(g,i,u,x) for(register int (i)=(g).h[(u)],(x)=(g).v[(i)];(i);(i)=(g).nxt[(i)],(x)=(g).v[(i)])
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
using namespace std;
constexpr int N=1e4+10,Qr=1e2+10;
int n,m,Q;
int a[N],b[Qr],k[Qr],id[N];
int ans[Qr][N];
signed main(){
	cin>>n>>m;
	FOR(i,1,n)cin>>a[i];
	cin>>Q;
	FOR(i,1,Q)cin>>k[i],b[i]=k[i];
	sort(b+1,b+Q+1),b[0]=unique(b+1,b+Q+1)-b-1;
	FOR(i,1,b[0])id[b[i]]=i;
	id[m+1]=b[0]+1;
	DOR(i,m,0)if(!id[i])id[i]=id[i+1];
	FOR(len,1,n-m){
		int sum=0,it=1;
		FOR(i,1,n-len-m+1){
			for(;it<=i+m-1;++it)sum+=(a[it]!=a[it+len]);
			++ans[id[sum]][i],++ans[id[sum]][i+len];
			sum-=(a[i]!=a[i+len]);
		}
	}
	FOR(i,1,b[0])FOR(j,1,n-m+1)ans[i][j]+=ans[i-1][j];
	FOR(i,1,Q){
		FOR(j,1,n-m+1)cout<<ans[id[k[i]]][j]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：内拉组里 (赞：0)

# Pts 25

先敲暴力。

$ \Theta (N^2) $ 枚举区间，然后 $ \Theta (L) $ 计算距离。

非常简单。

## Analyses：

> 总时间复杂度 $ \Theta (N^2 L) $。
>
> 总空间复杂度 $ \Theta (N) $。

***

# Pts 100

首先观察暴力枚举的过程，

对于两组区间 $ [l_1,r_1] \sim [l_2,r_2] $ 和 $ [l_1 + 1,r_1 + 1] \sim [l_ + 1,r_2 + 1] $，

发现 $ [l_1 + 1,r_1] $ 和 $ [l_2 + 1,r_2] $ 这两部分进行了重复计算，故考虑直接继承，

因此需要考虑的只有 $ l_1 $ 与 $ l_2 $ 和 $ r_1 + 1 $ 与 $ r_2 + 1 $ 的关系。

若 $ l_1 $ 与 $ l_2 $ 不同，则距离 $ dist - 1 $。

同样地，若 $ r_1 + 1 $ 与 $ r_2 + 1 $ 不同，则 $ dist + 1 $。

直接定长区间扫一遍，然后把答案直接记进桶里，最后跑一遍前缀和即可。

## Analyses：

> 总时间复杂度 $ \Theta ((N + Q)N) $。
>
> 总空间复杂度 $ \Theta (NQ) $。

# Code：

```cpp
/* reference : @ZLOJ.luzexi[art] */
/* key : section [l1,r1],[l2,r2] with equal length have similar parts */
#include	<algorithm>
#include	<iostream>
#include	<vector>
using namespace std;
constexpr int maxn = 1e4+4;
constexpr int maxq = 104;

namespace pts25
{
	int n, q, l;
	int a[maxn];
	
	signed main (void)
	{
		cin >> n >> l;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		cin >> q;
		while (q--)
		{
			int k;
			cin >> k;
			for (int i = 1; i + l - 1 <= n; i++)
			{
				int ans = 0;
				for (int j = 1; j + l - 1 <= n; j++) if (i != j)
				{
					int dist = 0;
					for (int t = 1; t <= l; t++)
					{
						if (a[i + t - 1] != a[j + t - 1])
							dist++;
					}
					if (dist <= k)
						ans++;
				}
				cout << ans << ' ';
			}
			cout << endl;
		}
		return 0;
	}
}

namespace pts100
{
	int n, l, q;
	int a[maxn];
	int k[maxq];
	vector<int> b;
	int ans[maxn][maxq];
	
	signed main (void)
	{
		cin >> n >> l;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		cin >> q;
		for (int i = 1; i <= q; i++)
		{
			cin >> k[i];
			b.push_back(k[i]);
		}
		sort (b.begin(), b.end());
		b.resize(unique (b.begin(), b.end()) - b.begin());
		for (int i = 1; i <= q; i++)
			k[i] = lower_bound (b.begin(), b.end(), k[i]) - b.begin();
		for (int i = 2; i + l - 1 <= n; i++)
		/* enumerate l2 */
		{
			int dist = 0;
			for (int j = 1; j <= l; j++)
			/* compare [1,l] and [i,i + l - 1] directly */
			{
				if (a[1 + j - 1] != a[i + j - 1])
					dist++;
			}
			ans[1][lower_bound (b.begin(), b.end(), dist) - b.begin()]++;
			ans[i][lower_bound (b.begin(), b.end(), dist) - b.begin()]++;
			for (int j = 1; i + j + l - 1 <= n; j++)
			/* move forward to [1 + j,1 + j + l - 1] and [i + j,i + j + l - 1] */
			{
				if (a[1 + j - 1] != a[i + j - 1])			/* check the lost one */
					dist--;
				if (a[1 + j + l - 1] != a[i + j + l - 1])	/* check the newcome one */
					dist++;
				ans[1 + j][lower_bound (b.begin(), b.end(), dist) - b.begin()]++;
				ans[i + j][lower_bound (b.begin(), b.end(), dist) - b.begin()]++;
			}
		}
		for (int i = 1; i + l - 1 <= n; i++)
		{
			for (int j = 1; j < b.size(); j++)
			{
				ans[i][j] += ans[i][j - 1];
			}
		}
		for (int i = 1; i <= q; i++)
		{
			for (int j = 1; j + l - 1 <= n; j++)
			{
				cout << ans[j][k[i]] << ' ';
			}
			cout << endl;
		}
		return 0;
	}
}

signed main (void)
{
	return pts100::main ();
}
```

---

## 作者：qwer6 (赞：0)

这道题我们初一看似乎并不好写，考虑多组询问的常见套路：预处理。

这很符合我们的直觉，首先使用一个 $O(n^2)$ 的时间复杂度枚举两个区间 $i,j$，然后 $O(l)$ 地求出距离 $dis$，将 $cnt_{dis,i}$ 和 $cnt_{dis,j}$ 加一，最后对于每一个区间做一次前缀和即可得到答案。

但是这样时间复杂度显然爆炸，我们想想如何优化。

我们肯定尝试 $O(1)$ 求出距离，但是如果我们固定一个区间 $i$，在已知 $i,j$ 的距离的情况下，也不好求出 $i,j+1$ 的距离，因为位置变了，原来有贡献的数可能不再有贡献，原来没有贡献的数可能有贡献，不好考虑。

所以我们考虑其他递推方式，我们发现，对于在已知 $i,j$ 的距离的情况下，我们可以容易求出 $i+1,j+1$ 的距离，改变的只有 $a_i,a_j$ 的贡献和 $a_{i+l},a_{j+l}$ 的贡献，可以 $O(1)$ 求解。

上面的做法时间复杂度 $O(n^2)$，空间复杂度 $O(n^2)$，空间复杂度显然无法接受，还要优化空间。

考虑离线处理询问，将所有操作离线并且离散化，对于一个距离 $dis$，找到第一个不小于 $dis$ 的位置，加在这个位置就可以了，空间复杂度为 $O(nq)$。

```c++
/*by qwer6*/
#include<bits/stdc++.h>
#define Nxt puts("")
#define Spa putchar(32)
#define Pline puts("------------------------------")
namespace FastIO{
	int write_top,read_f,read_x;
	char read_char;
	int write_st[20];
	inline int read(int &a){
		read_char=getchar();
		read_f=1;
		a=0;
		while(!isdigit(read_char)){
			if(read_char=='-')read_f=-1;
			read_char=getchar();
		}
		while(isdigit(read_char)){
			a=(a<<1)+(a<<3)+(read_char^48);
			read_char=getchar();
		}
		return a=a*read_f;
	}
	inline int read(){
		read_char=getchar();
		read_f=1;
		read_x=0;
		while(!isdigit(read_char)){
			if(read_char=='-')read_f=-1;
			read_char=getchar();
		}
		while(isdigit(read_char)){
			read_x=(read_x<<1)+(read_x<<3)+(read_char^48);
			read_char=getchar();
		}
		return read_x*read_f;
	}
	inline void write(int x){
		if(x<0)putchar('-'),x=-x;
		write_top=0;
		do{
		   write_st[++write_top]=x%10;
		   x/=10;
		}while(x);
		while(write_top)putchar(write_st[write_top--]+'0');
		return ;
	}
	inline void tomax(int &a,int b){
		if(a<b)a=b;
		return ;
	}
	inline void tomin(int &a,int b){
		if(a>b)a=b;
		return ;
	}
}
using namespace FastIO;
using namespace std;
const int N=1e4+5;
int n,l,q,tot;
int a[N],ans[105][N],tmp[105],K[105],id[N];
signed main(){
	read(n),read(l);
	for(int i=1;i<=n;i++)read(a[i]);
	read(q);
	for(int i=1;i<=q;i++)tmp[i]=read(K[i]);
	sort(tmp+1,tmp+q+1);
	tot=unique(tmp+1,tmp+n+1)-tmp-1;
	tmp[tot+1]=l+1;
	for(int i=1,j=1;i<=l;i++){
		while(i>tmp[j])j++;
		id[i]=j;
	}
	for(int i=1,dis;i<=n-l;i++){
		dis=0;
		for(int x=0;x<l;x++)
			if(a[1+x]!=a[1+i+x])
				dis++;
		ans[id[dis]][1]++;
		ans[id[dis]][1+i]++;
		for(int x=2;x+i<=n-l+1;x++){
			if(a[x-1]!=a[x+i-1])dis--;
			if(a[x+l-1]!=a[x+i+l-1])dis++;
			ans[id[dis]][x]++;
			ans[id[dis]][x+i]++;
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=q;j++)ans[j][i]+=ans[j-1][i];
	for(int i=1;i<=q;i++){
		for(int j=1;j<=n-l+1;j++)write(ans[id[K[i]]][j]),Spa;
		Nxt;
	}
}
```

---

## 作者：iPhoneSX (赞：0)

# 题解 


---

## 赛时思路

首先想到的是如何求每个两个区间的“距离”，也就是不同元素的个数。$O(n)$ 遍历肯定太慢，考虑到两区间重合的部分会被遍历太多次，就会发现如果已经知道了从第 $x$ 个元素开始的区间和从第 $y$ 个元素开始的区间之间的距离 $d_{x,y}$，可以 $O(1)$ 求出 $d_{x+1,y+1}=d_{x,y}−[a_x \ne a_y]+[a_x+l \ne a_y+l]$ 于是定义 $ans_{i,j}$ 表示和第 $i$ 个元素开头的区间，距离为 $j$ 的区间有多少个。$O(n)$ 求出 $d_{1,1+c}$，$O(n)$ 求出后面所有相差 $c$ 个元素的区间之间的距离。最终答案便是求 $ans_i$ 的前缀和。于是在考场上傻乎乎地写出了如下代码，只有 $45$ 分。
```cpp
//45分错误代码
read(n,l);
for(int i=1;i<=n;++i){
  read(a[i]);
}
for(int i=2;i<=n-l+1;i++){
  int pre=0;
  for(int x=i,y=1;x<=i+l-1,y<=l;++x,++y){
    if(a[x]!=a[y]){
      pre++;
    }
  }
  ans[1][pre]++;
  ans[i][pre]++;
  for(int x=i+1,y=2;x<=n-l+1;++x,++y){
    if(a[x-1]!=a[y-1]){
      pre--;
    }
    if(a[x+l-1]!=a[y+l-1]){
      pre++;
    }
    ans[x][pre]++;
    ans[y][pre]++;
  }
}
``````
## 赛后补题

被卡空间了。询问的次数 $q$ 很小，要把 $ans$ 数组的第二维优化到 $q$。可以把所有查询离线下来离散化，然后记录一下每一种距离 $k$ 属于哪一次查询。空间复杂度 $O(nq)$，时间 $O(n^2)$。
```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<iostream>
#include<list>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
#define ll long long
#define DBG(x) cout << #x << "=" << x << endl
#define inf 0x3f3f3f3f
#define mod 1000000007
#define N 10005
using namespace std;
template <typename T>
void read(T& x) {
    x = 0;
    ll t = 1;
    char ch;
    ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            t = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    x *= t;
}
template <typename T, typename... Args>
void read(T& first, Args&... args) {
    read(first);
    read(args...);
}
template <typename T>
void write(T y) {
    T x = y;
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}
template <typename T, typename... Ts>
void write(T arg, Ts... args) {
    write(arg);
    if (sizeof...(args) != 0) {
        putchar(' ');
        write(args...);
    }
}
int n,l,a[N],q,k[105],b[105],vis[N],ans[N][105],op[N];
int main(){
	read(n,l);
	for(int i=1;i<=n;++i){
		read(a[i]);
	}
	read(q);
	for(int i=1;i<=q;++i){
		read(k[i]);
		b[i]=k[i];
	}
	sort(b+1,b+q+1);
	int len=unique(b+1,b+q+1)-(b+1);
	for(int i=1;i<=q;i++){
		k[i]=lower_bound(b+1,b+len+1,k[i])-b;
	}
	int pos=1;
	for(int i=0;i<=n;i++){
		if(pos<=len&&b[pos]<i){
			pos++;
		}
		op[i]=pos;//统计每个距离属于哪一次查询	
	}
	for(int i=2;i<=n-l+1;i++){
		int pre=0;
		for(int x=i,y=1;x<=i+l-1,y<=l;++x,++y){
			if(a[x]!=a[y]){
				pre++;
			}
		}
		ans[1][op[pre]]++;
		ans[i][op[pre]]++;
		for(int x=i+1,y=2;x<=n-l+1;++x,++y){//x，y是两个区间的头
			if(a[x-1]!=a[y-1]){
				pre--;
			}
			if(a[x+l-1]!=a[y+l-1]){
				pre++;
			}
			ans[x][op[pre]]++;
			ans[y][op[pre]]++;
		}
	}
	for(int i=1;i<=n-l+1;i++){
		for(int j=1;j<=len;j++){
			ans[i][j]+=ans[i][j-1];
		}
	}
	for(int i=1;i<=q;i++){
		for(int j=1;j<=n-l+1;j++){
			write(ans[j][k[i]]);
			putchar(' ');
		}
		putchar('\n');
	}
    return 0;
}
``````

---

## 作者：xixisuper (赞：0)

# P6360 [CEOI2018] Lottery 题解

集训时讲了这道题，来写一下题解当笔记。

## 思路

注意到这些区间有一个这样的性质：设 $x,y$ 对应的距离为 $f(x,y)$，假设 $f(x,y)$ 已知，则我们可以 $O(1)$ 计算得到 $f(x+1,y+1)$，有 $f(x+1,y+1)=f(x,y)-[a_x \not=a_y]+[a_{x+l}\not=a_{y+l}]$。

于是我们有这样的策略，先暴力算出所有的 $f(1,j)$，时间复杂度 $O(n^2)$，然后推出所有的 $f(x,y)$ 时间复杂度为 $O(n^2)$，最后统计的时候开数组记得把询问离散化，空间复杂度为 $O(qn)$，时间复杂度 $O(n^2)$。

## 代码

代码很短，重在思考（比赛时没有想到 $10^4$ 能用 $O(n^2)$ 屮过去）。

```cpp
#include <iostream>
#include <algorithm>
#define ll int
using namespace std;
const ll N=10002;
const ll Q=102;
inline ll read(){
  register ll f=1,x=0;
  register char c=getchar();
  while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
  while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
  return x*f;
}
ll n,l,A[N],q,ans[N][Q];
ll chg[N],ask[N],lis[N];
int main(){
	n=read(),l=read();
	for(ll i=1;i<=n;i++) A[i]=read();
	q=read();
	for(ll i=1;i<=q;i++){
		ask[i]=read();
		lis[i]=ask[i];
	}
	sort(lis+1,lis+1+q);
	ll nq=unique(lis+1,lis+1+q)-lis-1;
	ll tp=1;
	for(ll i=1;i<=n;i++){
		while(tp<=nq&&i>lis[tp]) tp++;
		chg[i]=tp;
	}
	for(ll i=2;i+l-1<=n;i++){
		ll d=0;
		for(ll j=0;j<l;j++) if(A[1+j]!=A[i+j]) d++;
		ans[1][chg[d]]++,ans[i][chg[d]]++;
		for(ll j=1;j+i<=n-l+1;j++){
			d=d-(A[j]!=A[i+j-1])+(A[j+l]!=A[i+j-1+l]);
			ans[1+j][chg[d]]++,ans[i+j][chg[d]]++;
		}
	}
	for(ll i=1;i<=n-l+1;i++)
		for(ll j=1;j<=nq;j++) ans[i][j]+=ans[i][j-1];
	for(ll i=1;i<=q;i++){
		for(ll j=1;j<=n-l+1;j++) printf("%d ",ans[j][chg[ask[i]]]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：XuYueming (赞：0)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/P6360)。

[更好的体验](https://www.cnblogs.com/XuYueming/p/18316425)。

## 题意简述

给出序列 $a_1 \ldots a_n$ 和常数 $l \leq n$，定义：

$$
\operatorname{dis}(i, j) = \sum _ {k = 0} ^ {l - 1} [a_{i + k} \neq a_{j + k}] \qquad (i, j \in [1, n - l + 1])
$$

每次询问一个 $k$，求对于所有 $i \in [1, n - l + 1]$，求 $\sum \limits _ {j \neq i} [\operatorname{dis}(i, j) = k]$。

## 题目分析

暴力不用说，考虑如何优化。这类问题我们思考能不能省略重复的计算。例如，对于 $l_1 \sim r_1$ 和 $l_2 \sim r_2$ 的 $\operatorname{dis}$ 已经求出，那么对于 $l_1 + 1 \sim r_1 + 1$ 和 $l_2 + 1 \sim r_2 + 1$ 的 $\operatorname{dis}$ 只需要在原来基础上减去 $[l_1 \neq l_2]$，再加上 $[r_1 + 1 \neq r_2 + 1]$。是 $\Theta(1)$ 的。

具体地讲，对于这两个区间，它们的差值的可能性是 $\Theta(n)$ 的，我们枚举这个差值，然后将这两个区间向右平移，用上述算法计算，并累加。注意到这样会不重不漏地统计到每一个区间的答案。时间复杂度 $\Theta(n ^ 2)$。

另外，由于特殊的空间限制，不妨将询问离线并离散化，空间复杂度就降到了 $\Theta(nq)$。

## 代码

略去了快读快写。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n, m, q, val[10010];
int cnt[110][10010];
int qry[110], rq[110], who[10010];

signed main() {
	fread(buf, 1, MAX, stdin);
	read(n), read(m);
	for (int i = 1; i <= n; ++i) read(val[i]);
	read(q);
	for (int i = 1; i <= q; ++i) read(qry[i]), rq[i] = qry[i];
	sort(rq + 1, rq + q + 1);
	for (int i = 1; i <= q; ++i) who[rq[i]] = i;
	who[m + 1] = q + 1;
	for (int i = m; i >= 0; --i) !who[i] && (who[i] = who[i + 1]);
	for (int i = 1; i + m <= n; ++i) {  // 两个区间的差
		int tot = 0;
		for (int j = 1; j <= m; ++j) tot += val[j] != val[j + i];
		for (int l1 = 1, r1 = m, l2 = 1 + i, r2 = m + i; r2 <= n; ++l1, ++l2, ++r1, ++r2) {
			++cnt[who[tot]][l1], ++cnt[who[tot]][l2];
			tot -= val[l1] != val[l2];
			tot += val[r1 + 1] != val[r2 + 1];
		}
	}
	for (int i = 1; i <= q; ++i)
		for (int j = 1; j + m - 1 <= n; ++j)
			cnt[i][j] += cnt[i - 1][j];
	for (int i = 1; i <= q; ++i) {
		for (int j = 1; j + m - 1 <= n; ++j)
			write(cnt[who[qry[i]]][j]), putchar(' ');
		putchar('\n');
	}
	fwrite(obuf, 1, o - obuf, stdout);
	return 0;
}
```

## 后记 & 反思

考虑重复计算并优化是关键。另外，枚举两个区间的位置关系，并做到不重不漏的统计也是值得注意的。

---


# Let Me Teach You a Lesson (Hard Version)

## 题目描述

这是一个难度较高的版本。与简单版本的唯一区别在于 $t$ 和 $n$ 的约束条件。只有当你同时解决了两个版本的问题时，才能进行 hack。

Arthur 正在给他著名的 $2n$ 位骑士上课。和其他学生一样，他们成对坐在桌前，但出于习惯，他们是围成一个圆圈坐的。第 $2i-1$ 位骑士和第 $2i$ 位骑士坐在同一张桌子上。

每位骑士都有一个智力值，用整数表示。我们用 $a_i$ 表示第 $i$ 位骑士的智力值。Arthur 希望所有桌子的总智力值的最大差值尽可能小。更正式地说，他希望最小化 $\max\limits_{1 \le i \le n} (a_{2i-1} + a_{2i}) - \min\limits_{1 \le i \le n} (a_{2i-1} + a_{2i})$。

然而，骑士守则只允许交换圆圈中相对位置的骑士，也就是说，Arthur 可以同时执行 $a_i := a_{i+n}$，$a_{i+n} := a_i$，其中 $1 \le i \le n$。Arthur 可以进行任意次数这样的交换。请问他能达到的最小差值是多少？

## 说明/提示

在第一个测试用例中，Arthur 可以交换第 $2$ 位和第 $4$ 位骑士。这样两张桌子的总智力值都是 $10$。

在第三个测试用例中，Arthur 不需要进行任何操作，每张桌子的总智力值都是 $11$。

在第四个测试用例中，Arthur 可以交换编号为 $2$ 和 $5$ 的骑士，得到的差值为 $2$。可以证明无法取得更优的结果。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
2
6 6 4 4
1
10 17
3
1 10 1 10 1 10
3
3 3 4 5 5 4
5
1 2 3 4 5 6 7 8 9 10```

### 输出

```
0
0
0
2
4```

# 题解

## 作者：一只绝帆 (赞：5)

> 有一个长为 $2n$ 的序列，从 $1$ 开始标号，其中 $i\in[1,n],(2i-1,2i)$ 两个位置绑定为一组，你可以任意执行交换 $i$ 与 $i+n$ 位置上的值（$i\in[1,n]$），使得每组的和的极差最小。
> 
> $n\le 10^5,a_i\le 10^9$。

首先你需要秒掉 $2\mid n$，每组与其对面的组放到一起考虑，选择极差更小的方案即可。

然后我们看 $2\nmid n$，此时我们发现交换的路径用类似一笔画的方式联通了整个图，但太乱了，我们可以重新排列这些组使得交换对面元素变成交换相邻元素，这样交换两个元素造成的影响就被限制在了一个小范围里。

你发现所有组的可能的值只有 $\le 4n$ 种，所以我们可以双指针限制值域，或者枚举最小值使最大值最小。

不妨先考虑后一种，你发现相邻两个组合并之后如果想再与其它组合并，并不需要关心全部的信息，只需要关心左边是否交换，右边是否交换，组内最小的最大值。

把左边是否交换，右边是否交换记在状态里，这就是一个 $(\max,\min)$ 矩乘，这是赛时 jiangly 的思路。

也可以采用双指针的思路，其实就是把 $(\max,\min)$ 矩乘换成 $(\text{or},\text{and})$ 之类的 $01$ 矩阵乘法。

---

## 作者：xfrvq (赞：2)

*2900。

首先 $n$ 为偶数是简单的。将 $a_{1\cdots 2n}$ 拆为 $\frac n2$ 组数 $(a_{2i-1},a_{2i},a_{2i-1+n},a_{2i+n})$，每一组要么前两个、后两个配，要么第一四个、第二三个配。由于和固定，贪心地找两数最接近的配对方案。

$n$ 为奇数情况。考虑验证 $\min\ge l,\max\le r$ 是否合法。对于每一个位置有换/不换两种选择，每一组就有两个位置分别换/不换的四种情况。一种情况的和 $\notin[l,r]$ 就不合法。2-SAT 判断是否存在合法解即可。

注意到 $l,r$ 的可能取值仅有 $4n$ 个，且 $l$ 增加 $r$ 不降。于是暴力双指针枚举。总复杂度 $O(n^2)$，可通过 $n=2000$ 的 E1。

动态增加/减少限制的 2-SAT 不可做。考虑转化。重排序列，让**每组 $\{a_i,a_{i+n}\},\{a_{2i-1},a_{2i}\}$ 相邻**（**注意到它们本来就是一个环**）。如 $1\sim10$ 重排为 $1,2,7,8,3,4,9,10,5,6$。这样问题仍然是 $\{a_{2i-1}+a_{2i}\}$ 极差最小，但修改变成交换 $\{a_{2i},a_{2i+1}\}$ 或 $\{a_1,a_{2n}\}$。

还是双指针枚举 $l,r$，但用一个 dp 代替 2-SAT。设 $b_{i,0/1,0/1}\in\{0,1\}$ 为第 $i$ 对数，$a_{2i-1}$ 是否与 $a_{2i-2}$ 对调，$a_{2i}$ 是否与 $a_{2i+1}$ 对调后，是否符合当前 $l,r$。设 $f_{i,0/1,0/1}\in\{0,1\}$ 代表 **$a_1$ 是否与 $a_{2n}$ 对调**，$a_{2i}$ 是否与 $a_{2i+1}$ 对调后，前 $i$ 对数是否存在合法解。使用 $b$ 值完成转移。如果 $f_{n,0,0}=1$ 或 $f_{n,1,1}=1$，说明逻辑闭环，全局有合法解。

dp 过程可以写成 $b$ 值的 $\mathrm{or,and}$ 矩阵乘法。单点修改全局矩阵乘积，线段树维护，总复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int C,n,a[N],P[N],Q[N],m,v[N * 4],b[2][2][N];
vector<tuple<int,int,int>> V[N * 4];

#define lc (i * 2)
#define rc (lc + 1)
#define mid ((L + R) / 2)
#define id int i = 1,int L = 1,int R = n

using mat = array<array<bool,2>,2>;

mat T[N * 4];

mat mul(mat a,mat b){
	mat c = mat();
	for(int i = 0;i < 2;++i)
		for(int j = 0;j < 2;++j)
			for(int k = 0;k < 2;++k) c[i][j] |= a[i][k] && b[k][j];
	return c;
}

void upd(int x,int y,int z,bool v,id){
	if(L == R) return T[i][y][z] = v,void();
	x <= mid ? upd(x,y,z,v,lc,L,mid) : upd(x,y,z,v,rc,mid + 1,R);
	T[i] = mul(T[lc],T[rc]);
}

bool chk(){ return T[1][0][0] || T[1][1][1]; }

int main(){
	for(scanf("%d",&C);C--;){
		scanf("%d",&n);
		for(int i = 1;i <= 2 * n;++i) scanf("%d",a + i);
		if(n % 2 == 0){
			int mx = 0,mn = 2e9;
			for(int i = 1;i <= n;i += 2){
				int x1 = a[i] + a[i + 1],y1 = a[i + n] + a[i + n + 1];
				int x2 = a[i + n] + a[i + 1],y2 = a[i] + a[i + n + 1];
				if(x1 > y1) swap(x1,y1);
				if(x2 > y2) swap(x2,y2);
				if(y1 < y2) mx = max(mx,y1),mn = min(mn,x1);
				else mx = max(mx,y2),mn = min(mn,x2);
			}
			printf("%d\n",mx - mn);
			continue;
		}
		for(int i = 1,j = 1,k = 0;i <= n;++i){
			Q[P[j] = ++k] = j,++j,Q[P[j] = ++k] = j;
			j += j <= n ? n : -n;
		}
		Q[0] = Q[2 * n],Q[2 * n + 1] = Q[1],m = 0;
		for(int i = 1;i <= n;++i)
			for(int j = 0;j < 2;++j)
				for(int k = 0;k < 2;++k) v[++m] = a[Q[i * 2 - 1 - j]] + a[Q[i * 2 + k]];
		sort(v + 1,v + m + 1);
		m = unique(v + 1,v + m + 1) - v - 1;
		for(int i = 1;i <= n;++i)
			for(int j = 0;j < 2;++j)
				for(int k = 0;k < 2;++k)
					V[lower_bound(v + 1,v + m + 1,a[Q[i * 2 - 1 - j]] + a[Q[i * 2 + k]]) - v].emplace_back(i,j,k);
		int ans = 2e9;
		fill(T,T + 4 * n + 1,mat());
		for(int i = 1,j = 0;i <= m;++i){
			for(;j < m && !chk();++j) for(auto[x,y,z] : V[j + 1]) upd(x,y,z,1);
			if(!chk()) break;
			ans = min(ans,v[j] - v[i]);
			for(auto[x,y,z] : V[i]) upd(x,y,z,0);
		}
		for(int i = 1;i <= m;++i) V[i].clear();
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Albert_van (赞：2)

[题](https://www.luogu.com.cn/problem/CF1995E2) [题](https://mirror.codeforces.com/problemset/problem/1995/E2)。尝试用 desks 和交换关系将 knights 连接起来：

![](https://s3.bmp.ovh/imgs/2024/07/30/136e9c95f7d2e171.png)

（$n=4$）不难发现，$n$ 为偶数时整张图被分为 $\frac n2$ 个大小为 $4$ 的连通块。交换操作只会影响本块中两个 desk 的 $a_i+a_{i+1}$，所以对每个块分别选择进行一次/不进行交换，从而让两个 desk 差距最小即可。

若 $n$ 为奇数，整张图构成一个环。从 knight $1$ 开始沿着环走一遍，重新标号 knights 和 desks（以 $n=5$ 为例）：

![](https://s3.bmp.ovh/imgs/2024/07/30/32121c0cefcf8fc7.png)

求极差的一个套路是双指针确定值域并判断可行性。考虑如何在 $[L,R]$ 下判断是否存在一组交换方案满足 $\min\{a_i+a_{i+1}\}\ge L,\max\{a_i+a_{i+1}\}\le R$。这显然单调：$[L,R]$ 的扩增不会破坏原来方案的合法性。

对于 desk $k$，其存在 $4$ 种状态：编号较小的 knight（记为 $p(k)$）是否留在原地未被交换、编号较大者（$q(k)$）同理。考虑 $k$ 对 desk $k+1$ 的影响在于 $q(k)$ 和 $p(k+1)$ 的交换状态必须一致，这启发我们使用矩乘。

具体地，对 desk $k$ 建立 $2\times 2$ 的 $0/1$ 矩阵 $A(k)$，$A(k)_{0,*}$ 代表 $p(k)$ 被交换走了，$A(k)_{1,*}$ 代表 $p(k)$ 没有被交换，$A(k)_{*,0}$ 代表 $q(k)$ 被交换走了，$A(k)_{*,1}$ 同理；矩阵中元素表示在 $a_{p(k)}+a_{q(k)}\in[L,R]$ 的限制下，本行列所代表的交换方案是否可行。

手动模拟知，这一矩阵构造可以通过左乘合并：对于 $B=A(s)\times A(s+1)\times \cdots\times A(t)$，令 $l=p(s),r=q(t)$，$B_{i,j}$ 即表示：在 $l$ 是否未被交换走（$i=1/0$）、$r$ 是否未被交换走（$j=1/0$）的前提下，是否能在 desk $s$ 到 desk $t$ 这段区间内构造出合法交换方案，满足每个 desk $k\in[s,t]$ 均有 $a_{p(k)}+a_{q(k)}\in[L,R]$。

因为每个 desk 只有 $4$ 种状态，所以 $L$ 和 $R$ 只有 $4n$ 种取值。双指针后线段树维护矩乘结果，移动指针要求修改若干个叶子上的矩阵。判断合法性的方法为：若根节点的矩阵 $C$ 满足 $C_{0,0}=1\lor C_{1,1}=1$，则能够在 knight $1$ 和 knight $2n$ 的交换状态相同前提下，构造出 desk $1$ 到 desk $n$ 的方案，也即 $[L,R]$ 合法。

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=414514;

namespace sgt{
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)
	struct mtr{
		bool a[2][2];
		mtr operator*(const mtr &t)const{
			mtr r;memset(r.a,0,4);int tp;
			for(int i=0;i<2;++i) for(int k=0;k<2;++k){
				tp=a[i][k];for(int j=0;j<2;++j) r.a[i][j]|=(t.a[k][j]&tp);
			}
			return r;
		}
	}s[N];
	void upd(int now,int ln,int rn,int p,bool f1,bool f2,bool v){
		if(ln==rn) return s[now].a[f1][f2]=v,void();
		int mid=ln+rn>>1;
		if(p<=mid) upd(ls(now),ln,mid,p,f1,f2,v);
		else upd(rs(now),mid+1,rn,p,f1,f2,v);
		s[now]=s[ls(now)]*s[rs(now)];
	}
	bool chk(){return s[1].a[0][0]|s[1].a[1][1];}
}

struct stt{int d;bool f1,f2;};

vector<stt> vc[N];

int val[N];

namespace Disc{
	struct nod{int v;stt s;}a[N];int n;
	void ins(int v,stt s){a[++n]=(nod){v,s};}
	int dsc(){
		sort(a+1,a+n+1,[](nod x,nod y){return x.v<y.v;});
		int c=0;for(int i=1;i<=n;++i) vc[c+=(a[i].v!=a[i-1].v)].push_back(a[i].s),val[c]=a[i].v;
		return c;
	}
}

int a[N];

int main()
{
	int T;scanf("%d",&T);while(T--){
		int n;scanf("%d",&n);
		for(int i=1;i<=n<<1;++i) scanf("%d",a+i);
		if(n&1^1){
			int L=2e9,R=0;
			for(int i=1;i<n;i+=2){
				int l=a[i]+a[i+1],r=a[i+n]+a[i+n+1];
				if(l>r) swap(l,r);
				int p=a[i]+a[i+1+n],q=a[i+1]+a[i+n];
				if(p>q) swap(p,q);
				R=max(R,min(r,q));L=min(L,max(l,p));
			}
			printf("%d\n",R-L);continue;
		}
		for(int i=1;i<=n;++i){
			int k1=(i&1)?i:n+i,k2=k1+1,
				o1=(k1-1+n)%(n<<1)+1,o2=(k2-1+n)%(n<<1)+1;
			Disc::ins(a[k1]+a[k2],(stt){i,1,1});
			Disc::ins(a[k1]+a[o2],(stt){i,1,0});
			Disc::ins(a[o1]+a[k2],(stt){i,0,1});
			Disc::ins(a[o1]+a[o2],(stt){i,0,0});
		}
		int m=Disc::dsc(),ans=2e9;
		for(int l=1,r=0;l<=m;++l){
			while(r<m&&!sgt::chk()){
				++r;for(auto[d,f1,f2]:vc[r]) sgt::upd(1,1,n,d,f1,f2,1);
			}
			if(!sgt::chk()) break;
			ans=min(ans,val[r]-val[l]);
			for(auto[d,f1,f2]:vc[l]) sgt::upd(1,1,n,d,f1,f2,0);
		}
		printf("%d\n",ans);
		for(int i=1;i<=m;++i) vc[i].clear();
		memset(sgt::s,0,n<<4);Disc::n=0;
	}
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF1995E2)

**题目大意**

> 给定 $a_1\sim a_{2n}$，可以选择交换 $a_i,a_{i+n}$，最小化 $\max(a_{2i-1}+a_{2i})-\min(a_{2i-1}+a_{2i})$。
>
> 数据范围：$n\le 10^5$。

**思路分析**

最小化极差难以维护，可以考虑枚举 $\min(a_{2i-1}+a_{2i})$，目标变成最小化 $\max(a_{2i-1},a_{2i})$。

有一个朴素的 dp：$f_{i,0/1}$ 表示考虑了 $a[1,i]$，是否交换了 $a_{i},a_{i+n}$ 的方案。

转移为形如 $(\max,\min)$ 矩阵乘法，而 $\min(a_{2i-1}+a_{2i})$ 相当于限定有一些转移是不可以选用的。

那么我们从小到大枚举可能的 $\min(a_{2i-1}+a_{2i})$，可以使用的转移越来越少，只有 $\mathcal O(n)$ 次修改，用线段树维护动态 dp 的过程即可。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=2e9+5;
struct Mat {
	array <array<int,2>,2> a;
	Mat() { a={inf,inf,inf,inf}; }
	inline friend Mat operator *(const Mat &u,const Mat &v) {
		Mat w;
		for(int i:{0,1}) for(int j:{0,1}) {
			w.a[i][j]=min(max(u.a[i][0],v.a[0][j]),max(u.a[i][1],v.a[1][j]));
		}
		return w;
	}
};
const int MAXN=2e5+5;
int n,a[MAXN][2];
Mat f[MAXN];
struct zKyGt1 {
	Mat tr[1<<19];
	int N;
	void init() {
		for(N=1;N<=n;N<<=1);
		for(int i=1;i<(N<<1);++i) tr[i].a={0,inf,inf,0};
		for(int i=1;i<=n;++i) tr[i+N]=f[i];
		for(int i=N-1;i;--i) tr[i]=tr[i<<1]*tr[i<<1|1];
	}
	void upd(int x) {
		for(tr[x+N]=f[x],x=(x+N)>>1;x;x>>=1) tr[x]=tr[x<<1]*tr[x<<1|1];
	}
}	T;
void solve() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i][0]);
	for(int i=1;i<=n;++i) scanf("%d",&a[i][1]);
	vector <array<int,4>> op;
	if(n%2==0) {
		for(int i=1;i<=n;++i) {
			if(i%2==0) { f[i].a={0,0,0,0}; continue; }
			for(int x:{0,1}) for(int y:{0,1}) {
				int l=a[i][x]+a[i+1][y],r=a[i][x^1]+a[i+1][y^1];
				f[i].a[x][y]=max(l,r);
				op.push_back({min(l,r),i,x,y});
			}
		}
	} else {
		a[n+1][0]=a[1][1],a[n+1][1]=a[1][0];
		for(int i=1;i<=n;++i) {
			for(int x:{0,1}) for(int y:{0,1}) {
				if(i&1) f[i].a[x][y]=a[i][x]+a[i+1][y];
				else f[i].a[x][y]=a[i][x^1]+a[i+1][y^1];
				op.push_back({f[i].a[x][y],i,x,y});
			}
		}
	}
	T.init();
	int ans=inf;
	sort(op.begin(),op.end());
	for(auto it:op) {
		Mat &I=T.tr[1];
		int v=min(I.a[0][0],I.a[1][1]);
		if(v==inf) break;
		ans=min(ans,v-it[0]);
		f[it[1]].a[it[2]][it[3]]=inf;
		T.upd(it[1]);
	}
	printf("%d\n",ans);
}
signed main() {
	int _; scanf("%d",&_);
	while(_--) solve();
	return 0;
}
```

---

## 作者：Petit_Souris (赞：1)

首先发现 $n$ 为偶数的情况非常容易解决：因为 $(i,i+1)$ 和 $(i+n,i+n+1)(i\le n)$ 恰好是两组内交换，所以只有两种匹配方案，一定会选择差比较小的那组，因为和是一个定值，所以差小的方案一定同时满足最大值更小、最小值更大。

当 $n$ 为奇数时，有一个简单的 $\mathcal O(n^2)$ 做法：我们发现可能的和只有 $4n$ 种，做一个双指针，每次用 2-SAT 判断合法性。

但是这个思路不是很好优化，因为加边 / 删边的 2-SAT 难以维护。但是我们可以试着考虑 dp。

我们不妨做一个重排，使得交换 $(i,i+n)$ 的操作变成交换 $(2i,2i+1)$ 或 $(2n,1)$。举个例子，当 $n=5$，我们按照 $1,2,7,8,3,4,9,10,5,6$ 的顺序排列。现在在双指针的基础上容易想出一个 dp：$dp_{i,u}$ 表示前 $i$ 组数，上一组是否交换，是否合法。一个转移是合法的当且仅当和在目前两个指针的范围内。

这时候优化就很简单了：考虑动态 dp，用线段树维护矩阵乘积，这样只会进行 $\mathcal O(n)$ 次修改，$\mathcal O(n)$ 次查询全局乘积。时间复杂度为 $\mathcal O(n\log n)$。

启示：当遇到一些比较好用复杂模型解决的问题不好优化的时候，请寻其本，观察一些最基础的性质简化问题。（在这题中就是观察到你每次确定一组是否交换之后相邻组的状态可以直接转移）

乐子：我一遍写完代码直接过编译过样例，结果 wa 了两发 test 2，因为我最简单的偶数情况写挂了。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=2e5+9,INF=1e11;
ll T,n,a[N],b[N],tmp[N<<2],cnt;
struct M{
    bool a[2][2];
    void clear(){
        memset(a,0,sizeof(a));
    }
}tr[N<<2],mtr[N];
M operator*(const M&a,const M&b){
    M c;c.clear();
    rep(k,0,1){
        rep(i,0,1){
            rep(j,0,1)c.a[i][j]|=(a.a[i][k]&b.a[k][j]);
        }
    }
    return c;
}
struct Node{
    ll p,u,v;
};
vector<Node>vec[N<<2];
void Build(ll x,ll l,ll r){
    tr[x].clear();
    if(l==r)return ;
    ll mid=(l+r)>>1;
    Build(x<<1,l,mid);
    Build(x<<1|1,mid+1,r);
}
void Pushup(ll x){
    tr[x]=tr[x<<1]*tr[x<<1|1];
}
void Upd(ll x,ll l,ll r,ll u){
    if(l>u||r<u)return ;
    if(l==r)return tr[x]=mtr[u],void();
    ll mid=(l+r)>>1;
    Upd(x<<1,l,mid,u);
    Upd(x<<1|1,mid+1,r,u);
    Pushup(x);
}
bool chk(){
    return tr[1].a[0][0]||tr[1].a[1][1];
}
void solve(){
    n=read();
    rep(i,1,n*2)a[i]=read();
    if(n==1)return puts("0"),void();
    if(!(n&1)){
        ll mx=-INF,mn=INF;
        rep(i,1,n){
            if(i&1){
                ll d1=a[i]+a[i+1];
                ll d2=a[i+n]+a[i+1+n];
                ll p1=a[i]+a[i+1+n];
                ll p2=a[i+n]+a[i+1];
                if(abs(d1-d2)<abs(p1-p2)){
                    mx=max({d1,d2,mx});
                    mn=min({d1,d2,mn});
                }
                else {
                    mx=max({p1,p2,mx});
                    mn=min({p1,p2,mn});
                }
            }
        }
        write(mx-mn),putchar('\n');
        return ;
    }
    ll cur=1,len=0;
    rep(i,1,n*2){
        b[++len]=a[cur];
        if(i&1)cur++;
        else if(cur>n)cur-=n;
        else cur+=n;
    }
    cnt=0;
    rep(i,1,n*2){
        if(i&1){
            ll pa=(i==1?n*2:i-1),pb=i,qa=i+1,qb=(i==n*2-1?1:i+2);
            tmp[++cnt]=b[pa]+b[qa];
            tmp[++cnt]=b[pa]+b[qb];
            tmp[++cnt]=b[pb]+b[qa];
            tmp[++cnt]=b[pb]+b[qb];
        }
    }
    sort(tmp+1,tmp+cnt+1);
    cnt=unique(tmp+1,tmp+cnt+1)-tmp-1;
    rep(i,0,cnt+1)vec[i].clear();
    rep(i,1,n*2){
        if(i&1){
            ll pa=(i==1?n*2:i-1),pb=i,qa=i+1,qb=(i==n*2-1?1:i+2),id=0;
            id=lower_bound(tmp+1,tmp+cnt+1,b[pa]+b[qa])-tmp;
            vec[id].push_back({i/2+1,1,0});
            id=lower_bound(tmp+1,tmp+cnt+1,b[pa]+b[qb])-tmp;
            vec[id].push_back({i/2+1,1,1});
            id=lower_bound(tmp+1,tmp+cnt+1,b[pb]+b[qa])-tmp;
            vec[id].push_back({i/2+1,0,0});
            id=lower_bound(tmp+1,tmp+cnt+1,b[pb]+b[qb])-tmp;
            vec[id].push_back({i/2+1,0,1});
        }
    }
    Build(1,1,n);
    rep(i,0,n+1)mtr[i].clear();
    ll r=0,ans=INF;
    rep(l,1,cnt){
        while(r<cnt&&!chk()){
            r++;
            for(Node u:vec[r]){
                mtr[u.p].a[u.u][u.v]=1;
                Upd(1,1,n,u.p);
            }
        }
        if(chk())ans=min(ans,tmp[r]-tmp[l]);
        for(Node u:vec[l]){
            mtr[u.p].a[u.u][u.v]=0;
            Upd(1,1,n,u.p);
        }
    }
    write(ans),putchar('\n');
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    T=read();
    while(T--)solve();
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：DerrickLo (赞：0)

$n$ 是偶数的情况是容易的，只会在 $a_i,a_{i+1},a_{i+n},a_{i+n+1}$ 这四个数变化，所以对于每个 $i$，贪心地选择差较小的两组即可。

而 $n$ 是奇数的情况，我们发现无论如何操作，$a_{2i-1}+a_{2i}$ 这种数最多只有 $4n$ 个，所以考虑枚举最小值，然后通过双指针找到最大值最小是多少，再进行计算。接下来考虑怎么判断是否可以使得所有 $a_{2i-1}+a_{2i}$ 都在 $[l,r]$ 内。先考虑 dp，枚举第 $1$ 位是 $0$ 还是 $1$，然后记 $f_{i,0/1}$ 表示考虑到第 $i$ 位，第 $i$ 位有没有交换是否可行，则转移只需要枚举 $k$ 然后看一下 $f_{i-1,k}$ 能否转移到 $f_{i,j}$ 即可，这个只需要分 $i$ 的奇偶性判断。然后我们发现由 $f_{i-1}$ 转移到 $f_i$ 是一个矩阵的形式，而这 $n$ 个矩阵我们不难发现最多改变 $\mathcal O(n)$ 个数，所以只需要维护单点修改，全局矩阵乘积即可。使用线段树，时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[200005],b[800005],m;
int ff(int x){return(x<=n)?x+n:x-n;}
int nxt(int x){if(x%2==0)return x-1;return x+1;}
struct nd{int j,k,l;}; 
vector<nd>ve[400005],ve2[400005];
class Segment_Tree{
public:
	struct tree{
		int l,r,a[2][2];
	}tr[400005];
	void pushup(int u){
		for(int i=0;i<2;i++)for(int j=0;j<2;j++)tr[u].a[i][j]=0;
		for(int i=0;i<2;i++)for(int j=0;j<2;j++)for(int k=0;k<2;k++)tr[u].a[i][j]|=tr[u<<1].a[i][k]&tr[u<<1|1].a[k][j]; 
	}
	void build(int u,int l,int r){
		tr[u]={l,r,{0,0,0,0}};
		if(l==r)return;
		int mid=l+r>>1;
		build(u<<1,l,mid),build(u<<1|1,mid+1,r);
		pushup(u);
	}
	void update(int u,int x,int a,int b,int c){
		if(tr[u].l==tr[u].r){tr[u].a[a][b]=c;return;}
		int mid=tr[u].l+tr[u].r>>1;
		if(x<=mid)update(u<<1,x,a,b,c);
		else update(u<<1|1,x,a,b,c);
		pushup(u);
	}
}sgt;
void add(int x){for(auto v:ve[x])sgt.update(1,v.j,v.k,v.l,1);}
void del(int x){for(auto v:ve2[x])sgt.update(1,v.j,v.k,v.l,0);}
bool check(int x,int y){
	auto t=sgt.tr[1].a;x=b[x],y=b[y];
	for(int i=0;i<2;i++){
		int xx=t[0][0]*(!i)+t[1][0]*i,yy=t[0][1]*(!i)+t[1][1]*i;
		if(xx&&a[n]+a[1+(!i)*n]>=x&&a[n]+a[1+(!i)*n]<=y)return 1;
		if(yy&&a[2*n]+a[1+(!i)*n]>=x&&a[2*n]+a[1+(!i)*n]<=y)return 1;
	}
	return 0;
}
signed main(){
	cin>>t;
	int pcnt=0;
	while(t--){
		cin>>n,m=0,pcnt++;
		for(int i=1;i<=2*n;i++)cin>>a[i];
		if(n==1){cout<<"0\n";continue;}sgt.build(1,2,n);
		if(n%2==0){
			int mn=1e18,mx=-1e18;
			for(int i=1;i<=n/2;i++){
				int x=a[2*i-1]+a[2*i],y=a[n+2*i-1]+a[n+2*i];
				int z=a[2*i-1]+a[n+2*i],w=a[n+2*i-1]+a[2*i];
				if(abs(x-y)<abs(z-w))mn=min(mn,min(x,y)),mx=max(mx,max(x,y));
				else mn=min(mn,min(z,w)),mx=max(mx,max(z,w)); 
			}
			cout<<mx-mn<<"\n";continue;
		}
		for(int i=1;i<=2*n;i++){
			b[++m]=a[i]+a[nxt(i)];
			b[++m]=a[i]+a[nxt(ff(i))];
			b[++m]=a[i]+a[ff(nxt(i))];
			b[++m]=a[i]+a[ff(nxt(ff(i)))];
		}
		sort(b+1,b+m+1),m=unique(b+1,b+m+1)-b-1;
		for(int i=1;i<=m;i++)ve[i].clear(),ve2[i].clear();
		for(int i=2;i<=n;i++)for(int j=0;j<2;j++)for(int k=0;k<2;k++){
			int xx=(i&1)?a[i+(!j)*n]+a[i-1+(!k)*n]:a[i+j*n]+a[i-1+k*n];
			int pp=lower_bound(b+1,b+m+1,xx)-b,qq=upper_bound(b+1,b+m+1,xx)-b-1;
			ve[pp].push_back({i,k,j}),ve2[qq].push_back({i,k,j});
		}
		int j=1,ans=1e18;add(1);
		for(int i=1;i<=m;i++){
			while(j<m&&!check(i,j))j++,add(j);
			if(check(i,j))ans=min(ans,b[j]-b[i]);del(i);
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：0)

先考虑 $n\le 2000$ 怎么做。一个自然的想法是把可以交换的点进行连边，并在每个 $2i-1,2i$ 之间也连边。可以发现如果 $n$ 是偶数，会连出若干四元环，这部分是简单的，考虑每个四元环只有两种本质不同取值方法，因为环上数总和一定，直接取极差更小的即可。

然后考虑奇数，这时图会变成一个大环，极差是不好做的，我们考虑枚举 $\max$ 是哪一组，并顺便枚举与该组有关的两边的交换情况。然后我们的目的就是确定最大的合法 $\min$。由于这时环被我们破成了链，所以可以直接简单地 dp。设 $f_{i,0/1}$ 表示考虑到第 $i$ 条边，这条边连接的两个数不换/换即可。该部分核心代码如下，时间复杂度 $O(n^2)$：


```cpp
for(int i=pos+2;;i+=2){
        //getid 是找环上第 i 个点对应到原数组的编号
        c++;int w;
        if(c>n-1)break;

        w=a[getid(i-1)]+a[getid(i-2)];
        if(w<=mx)ckmx(f[c][0],min(f[c-1][0],w));

        w=a[getid(i)]+a[getid(i-2)];
        if(w<=mx)ckmx(f[c][1],min(f[c-1][0],w));

        w=a[getid(i-1)]+a[getid(i-3)];
        if(w<=mx)ckmx(f[c][0],min(f[c-1][1],w));

        w=a[getid(i)]+a[getid(i-3)];
        if(w<=mx)ckmx(f[c][1],min(f[c-1][1],w));
    }
```



然后发现转移形如 $(\min,\max)$ 矩阵乘法。可以直接用线段树维护。由于贡献与枚举的最大值有关，所以考虑按照最大值从小到大进行处理，这样转移矩阵需要修改的点总量是 $O(n)$ 的。总时间复杂度 $O(n\log n)$。

---

## 作者：Hoks (赞：0)

## 前言
菜猫猫的第二场 VP 中写不出来的题。

摘自 [杂题选做](https://www.luogu.com.cn/training/597433)。
## 思路分析
感觉这种题就很不常规，不好入手。

考虑手玩观察一下。

然后就会注意到重点，只能交换 $a_i$ 和 $a_{i+n}$。

考虑把能交换的数都连边连起来，并把 $2i-1$ 和 $2i$ 连起来。

此时我们给 $2n$ 个数连了 $n$ 条边且没有重边，必然会有环。

此时我们发现图的形态与 $n$ 的奇偶性有关：
1. $n$ 为偶数时：

    我们会发现整个图恰好是一个个的四元环组成的。

    那么对于每个四元环，可以取到的值恰好有 $4$ 种。

    取到极差最小的情况也就是取中间的两种值的情况，直接处理就行了。
2. $n$ 为奇数时：

    此时我们发现整个图恰好是一个大环。

    我们考虑怎么处理这个大环。

    环肯定要破开，而对于极差这种东西感觉也很难做。

    考虑对于极差的问题。

    我们不难发现对于一对数，最多只会有 $4$ 种取值，这四种取值也就分别是**不换+不换/换+不换/不换+换/换+换**。

    那么总共可能的取值也就只有 $4n$ 种。

    考虑使用双指针，用双指针枚举出目前值域区间 $[l,r]$。

    显然的是如果 $[l,r]$ 是可行的，那么 $[l,r+1]$ 也肯定是可行的，然后考虑尽可能的把 $l$ 往又移到不可行就行了。

    那我们现在要做到的就是一个复杂度在 $O(n)$ 以内的判断可行性。

    这个环太乱了，先给它捋直一点。

    具体的我们考虑把有边的点放在一起，然后把环拍成序列。

    比如 $n=7$ 时，得到的序列就是：
    $$1-2,9-10,3-4,11-12,5-6,13-14,7-8$$

    然后来考虑破环成链，由上面观察出来的性质我们知道每组都只有 $4$ 种可能性，但是会被上一组换不换影响。

    那么我们直接枚举第一组换不换的状态，然后按顺序尝试对后面的组操作。

    具体的我们使用 dp 来进行转移，$f_{i,0/1}$ 表示对于第 $i$ 组，和下一组连的那个数**有/无**交换过。

    此时的转移方程式也比较简单了，~~因为懒~~笔者就不多赘述了。

    那么直接用这个 dp 写一个 check 大力双指针移就可以做到 $O(n^2)$ 了。

    接着考虑优化。

    我们发现其实每次这个 dp 转移就相当于是之前那个 dp 值 and 上这种组合的情况下值是否在区间里。

    那么这样的话我们可以考虑把 dp 递推转化为矩阵乘法。

    转化为 and/or 矩阵乘法后就可以用线段树来维护修改。

    考虑我们扩展/缩小区间的时候只是在把一个转移矩阵里的 $0/1$ 互换。

    所以可以先存下来每个转移的值在哪个临界值会变动，然后遍历修改就行了。

    因为值的数量只有 $4n$，所以复杂度还是一只 log 的，可能常数略大。
## 代码
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define get(x) (lower_bound(c+1,c+1+tot,x)-c)
#define int long long
using namespace std;
constexpr int N=4e5+10,M=4,V=2,INF=0x3f3f3f3f3f3f3f3f;
struct Matrix
{
    bool a[V][V];Matrix(){memset(a,0,sizeof a);}
    Matrix operator * (const Matrix &b)const
    {
        Matrix t;
        for(int i=0;i<V;i++) for(int j=0;j<V;j++)
            for(int k=0;k<V;k++) t.a[i][j]|=a[i][k]&b.a[k][j];
        return t;
    }
}ept,d[N],t[N<<2];
int n,tot,a[N],b[N],c[N];vector<tuple<int,int,int>>e[N];
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
inline void clear(int p,int l,int r){t[p]=ept;if(l==r) return;clear(ls,l,mid);clear(rs,mid+1,r);}
inline void modify(int p,int l,int r,int x)
{
    if(l==r) return t[p]=d[x],void();
    (mid>=x)?(modify(ls,l,mid,x)):(modify(rs,mid+1,r,x));
    t[p]=t[ls]*t[rs];
}
inline void solve()
{
    n=read();for(int i=1;i<=n<<1;i++) a[i]=read();tot=0;if(n==1) return put("0\n");
    if(n%2==0)
    {
        int mn=INF,mx=-INF;
        for(int i=2;i<=n;i+=2)
        {
            int b[M]{a[i]+a[i-1],a[i+n]+a[i-1],a[i]+a[i-1+n],a[i+n]+a[i-1+n]};
            sort(b,b+M);mn=min(mn,b[1]);mx=max(mx,b[2]);
        }print(mx-mn);put('\n');return;
    }int x=1;b[x]=1;
    while(1)
    {
        b[x+1]=((b[x]-1)^1)+1;x++;if(x==n<<1) break;
        if(b[x]>n) b[x+1]=b[x]-n;
        else b[x+1]=b[x]+n;x++;
    }
    for(int i=1;i<=n<<1;i++) if(i&1)
    {
        int lst=i==1?n<<1:i-1,nxt=i+1==n<<1?1:i+2;
        c[++tot]=a[b[i]]+a[b[i+1]];c[++tot]=a[b[lst]]+a[b[i+1]];
        c[++tot]=a[b[i]]+a[b[nxt]];c[++tot]=a[b[lst]]+a[b[nxt]];
    }sort(c+1,c+1+tot);tot=unique(c+1,c+1+tot)-c-1;
    for(int i=1;i<=tot;i++) e[i].clear();
    for(int i=1;i<=n<<1;i++) if(i&1)
    {
        int lst=i==1?n<<1:i-1,nxt=i+1==n<<1?1:i+2;
        e[get(a[b[i]]+a[b[i+1]])].emplace_back(i/2+1,0,0);
        e[get(a[b[lst]]+a[b[i+1]])].emplace_back(i/2+1,1,0);
        e[get(a[b[i]]+a[b[nxt]])].emplace_back(i/2+1,0,1);
        e[get(a[b[lst]]+a[b[nxt]])].emplace_back(i/2+1,1,1);
    }int r=0,ans=INF;clear(1,1,n);for(int i=1;i<=n;i++) d[i]=ept;
    for(int l=1;l<=tot;l++)
    {
        while(r<tot&&!(t[1].a[0][0]||t[1].a[1][1])){r++;for(auto [i,j,k]:e[r]) d[i].a[j][k]=1,modify(1,1,n,i);}
        if(t[1].a[0][0]||t[1].a[1][1]) ans=min(ans,c[r]-c[l]);for(auto [i,j,k]:e[l]) d[i].a[j][k]=0,modify(1,1,n,i);
    }print(ans),put('\n');
}
signed main()
{
    int T=read();while(T--) solve();
    genshin:;flush();return 0;
}
```

---


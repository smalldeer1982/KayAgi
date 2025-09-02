# [JOIST 2023] 议会 / Council

## 题目背景

本题子任务编号如果为 0 表示样例，如果是非 0 的一位数表示满足对应的子任务，如果是两位数表示同时满足这两个子任务。

## 题目描述

#### 题目翻译

在 JOI 市议会中，有 $N$ 名议员，编号从 $1$ 到 $N$。议会将召开会议，议员们将对 $M$ 项提案进行表决，编号为 $1$ 到 $M$。如果 $A_{i,j}=1$，则议员 $i (1≤i≤N)$ 将对提案 $j (1≤j≤M)$ 表决肯定票。如果 $A_{i,j}=0$，则议员 $i$ 将对提案 $j$ 表决否定票。

JOI 市议会的程序如下所示。

+ 在 $N$ 名议员中，通过抽签随机选择主席。

+ 主席将在除了主席以外的其他 $N−1$ 名议员中选择副主席。

+ 将对 $M$ 项提案进行表决。除了主席和副主席以外的其他 $N−2$ 名议员，每人对每个提案均投票支持或反对。如果大多数议员（即肯定票大于等于 $⌊\dfrac{N}{2}⌋$）投票赞成，则议会将批准该提案。其中 $⌊x⌋$ 表示不超过 $x$ 的最大整数。

市长 K 希望议会尽可能地批准更多的提案。市长 K 收集了议员的信息并知道每个议员在每个提案上的表决结果。

请编写程序，在给定议员投票信息的情况下，计算每个议员作为主席时议会可以批准的提案数量的最大可能值。

## 说明/提示

该样例满足子任务 $1, 2, 4, 5, 6, 7$ 的限制。

**【样例解释 #2】**

该样例满足子任务 $1, 2, 5, 6, 7$ 的限制。

**【样例解释 #3】**

该样例满足子任务 $1, 2, 4, 5, 6, 7$ 的限制。

**【样例解释 #4】**

该样例满足所有子任务的限制。

**【数据范围】**

对于所有测试数据，$3 \le N \le 3 \times 10 ^ 5$，$1 \le M \le 20$，$0 \le A_{i, j} \le 1$，保证所有输入均为整数。

|子任务编号|分值|限制|
|:-:|:-:|:-:|
|$1$|$8$|$N \le 300$|
|$2$|$8$|$N \le 3000$|
|$3$|$6$|$M \le 2$|
|$4$|$19$|$M \le 10$|
|$5$|$15$|$M \le 14$|
|$6$|$22$|$M \le 17$|
|$7$|$22$|无|

## 样例 #1

### 输入

```
3 3
1 0 0
1 1 0
1 1 1
```

### 输出

```
3
3
2
```

## 样例 #2

### 输入

```
4 12
1 1 1 0 1 1 0 1 0 1 1 0
1 1 0 1 1 0 1 1 1 1 1 0
0 0 1 1 1 0 0 0 0 0 1 1
1 0 0 0 1 1 1 1 1 0 0 0
```

### 输出

```
5
4
6
6
```

## 样例 #3

### 输入

```
16 4
0 0 0 0
0 0 0 1
0 0 1 0
0 0 1 1
0 1 0 0
0 1 0 1
0 1 1 0
0 1 1 1
1 0 0 0
1 0 0 1
1 0 1 0
1 0 1 1
1 1 0 0
1 1 0 1
1 1 1 0
1 1 1 1
```

### 输出

```
3
3
3
2
3
2
2
1
3
2
2
1
2
1
1
0
```

## 样例 #4

### 输入

```
4 2
1 0
0 1
1 1
1 1
```

### 输出

```
2
2
1
1
```

# 题解

## 作者：anthonyaaabc (赞：4)

提供一个不太一样的做法，没有使用高维前缀和之类的二进制处理的工具。

首先注意到 $m$ 很小，可以大概猜想一下复杂度可能是对 $m$ 的指数级的做法。首先可以思考一下对于第 $i$ 个人作为主席的情况下，他最优的情况下应该选择谁作为自己的副主席。对于每一个提案，假设把当前的主席扔掉之后，如果投票人数已经严格小于需求的数量，则这个提案一定不会通过。类似的，如果一个提案严格大于需求数量，则这个提案一定会通过。关键就是那些恰好等于需求数量的提案。

如果我们将那些恰好等于的提案状压成一个二进制数，则问题被转换成找到一个二进制数，使得两个数 $x$ ，$y$ 的按位与的 $1$ 的个数尽量小。

然后我没有想到怎么使用任何二进制处理的方法解决这个问题。考虑为什么最基础的暴力很慢，每次添加一个人的时候相当于一次修改操作，我们每次查询的时候都得枚举 $ 2^m $ 的代价，再加上我们枚举主席的复杂度，复杂度就来到了 $O(n 2^m)$ 。注意到我们的修改操作非常的快，这是没有必要的，我们只会修改 $O(n)$ 次，于是考虑平衡修改与查询的复杂度。考虑将一个状态 $x$ 分成两段，修改的时候枚举查询的时候前半段的可能，并更新对应的后半部分不变的最小答案，查询的时候枚举后半段即可将查询和修改都平衡到 $O(2^{m/2})$ 的。对于主席不能将自己选为副主席的处理在这个做法里是非常容易的，直接正着扫一遍，只处理 $i < j$，然后倒着扫一遍，只处理 $i > j $。
复杂度为 $O(n2^{m/2})$ ，代码好写常数很小。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300005;
const int bk=(1<<10)-1;
int n,m;
int a[N][21];
int vl[(1<<10)+5][(1<<10)+5],p;
int num[N];
int val[N];
int ans[N];
int cnt[(1<<10)+5];
void insert(int num)
{
    int half=num&bk;
    int res=num>>10;
    for(int i=0;i<1024;i++)
    {
        vl[i][res]=min(vl[i][res],cnt[half&i]);
    }
}
int get(int x)
{
    int half=x&bk;
    int res=x>>10;
    int val=1e9+7;
    for(int i=0;i<1024;i++)
    {
        val=min(val,vl[half][i]+cnt[res&i]);
    }
    return val;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=0;i<1024;i++)
    {
        cnt[i]=__builtin_popcount(i);
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
            if(a[i][j])
            {
                num[j-1]++;
                val[i]|=(1<<j-1);
            }
        }
    }
    m=20;

    memset(vl,0x3f,sizeof(vl));
    insert(val[1]);
    int mid=n>>1;
    for(int i=2;i<=n;i++)
    {
        int sum=0;
        for(int j=0;j<m;j++)
        {
            if((val[i]>>j)&1)num[j]--;
        }
        int tmp=0;
        for(int j=0;j<m;j++)
        {
            if(num[j]>=mid)sum++;
            if(num[j]==mid)tmp|=(1<<j);
        }
        ans[i]=max(ans[i],sum-get(tmp));
        for(int j=0;j<m;j++)
        {
            if((val[i]>>j)&1)num[j]++;
        }
        insert(val[i]);
    }

    memset(vl,0x3f,sizeof(vl));
    insert(val[n]);
    for(int i=n-1;i>=1;i--)
    {
        int sum=0;
        for(int j=0;j<m;j++)
        {
            if((val[i]>>j)&1)num[j]--;
        }
        int tmp=0;
        for(int j=0;j<m;j++)
        {
            if(num[j]>=mid)sum++;
            if(num[j]==mid)tmp|=(1<<j);
        }
        
        ans[i]=max(ans[i],sum-get(tmp));
        for(int j=0;j<m;j++)
        {
            if((val[i]>>j)&1)num[j]++;
        }
        insert(val[i]);
    }
    for(int i=1;i<=n;i++)
    {
        cout<<ans[i]<<'\n';
    }
}
```

---

## 作者：541forever (赞：4)

好像官方题解的时间复杂度是 $O(m^22^m)$ 的，这里介绍一种爆标的 $O(m2^m + nm)$ 的做法。

可以发现，当主席已经确定时，副主席的确立只会影响那些恰好被投了 $\lfloor {n \over 2} \rfloor$ 票的议案。此时，我们需要找到最小的 $j$,设 $a_i$ 为 $i$ 号议员投的票的状态，$S$ 表示此时有哪些票被投了 $\lfloor {n \over 2} \rfloor$ 票。则我们需要对每个 $i$ 找到一个 $j$ 使得 $a_j \& S$ 最小。

可以发现 $a_j$ 一定是 $a_j \& S$ 的超集，而 $a_j \& S$ 一定是 $S$ 的子集。不难想到对 $a_j$ 做一遍高维后缀和然后再做一遍高维前缀和。但是直接用 $a_i$ 表述出来的状态并不优，因为我们要维护的时最小值，正难则反，考虑将每个 $a_i$ 取反设其为 $b_i$ 求 $b_i \& S$ 的最大值。那么做法就呼之欲出了，我们可以先对 $b_i$ 做一遍高维后缀和，维护的信息 $g1_{S}$ 和 $g2_{S}$ 是可以到 $S$ 这个状态的两个 $i$。接着再对 $g1,g2$ 做高维后缀和，对于每个 $S$ 维护的 $g1_{S},g2_{S}$ 表示 $a_{g1_{S}} \& S,a_{g2_{S}} \& S$ 最大的那两个数。

最后直接对每个 $i$ 统计答案即可。

[Code](https://www.luogu.com.cn/paste/1mhkkmbe)

---

## 作者：Nangu (赞：2)

好题喵，非常推荐大家来做做。

以下记 $i$ 为主席的编号，$j$ 为副主席的编号。

考虑一个朴素的暴力：记 $c_k$ 表示第 $k$ 项提案在 $n$ 个议员中被同意的次数，每次枚举 $i, j$，将 $i, j$ 对 $c$ 数组的贡献减去，再暴力统计答案，时间复杂度是 $O(n^2m)$。

我们发现去掉任何一个议员对 $c_k$ 的贡献只有可能是 $0$ 或 $-1$。在枚举完 $i$ 后，记减掉 $i$ 的贡献后新的 $c$ 数组为 $b$，则：

1. $b_k>⌊\dfrac{n}{2}⌋$：不管 $j$ 的状态如何，这个议案肯定可以被批准。
2. $b_k=⌊\dfrac{n}{2}⌋$：只有 $j$ 表决否决票的时候，这个议案才可以被批准。
3. 其它情况，这个议案一定不可能被批准。

第二类情况这相当于给定一个集合 $S$，求除 $i$ 外 $n-1$ 个集合中与 $S$ 的交的元素个数的最大值。

这个问题有两种解决方法，一种是 FWT，但由于其同一编号的答案可能会进行多次转移，因此转移的时候需要判编号，比较麻烦。

另一种做法，设 $f_{i, j, k}$ 表示枚举了前 $i-1$ 位的贡献，此时前 $i-1$ 位的状态为 $j$，且只有后 $m-i$ 位状态为 $k$ 的议员被计算过了贡献。转移就枚举第 $i$ 位是否在最终的集合中，细节见代码。

最终复杂度：$O(nm+m2^m)$。

代码：
```cpp
#include<bits/stdc++.h>
#define rep(i, j, k) for(int i=(j); i<=(k); ++i)
#define per(i, j, k) for(int i=(j); i>=(k); --i)
using namespace std;
namespace DEBUG{
  template<class T> void _debug(const char *s, T x) {cout<<s<<'='<<x<<endl;}
  template<class F, class... Nxt> void _debug(const char *s, F x, Nxt... nxt){
  int d=0;
  while(*s!=',' || d) d+=*s=='(', d-=*s==')', cout<<*s++;
    cout<<'='<<x<<',';
    _debug(s+1, nxt...);
  }
  #define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
} using namespace DEBUG;
using pa=pair<int, int>;
const int N=3e5+7, M=(1<<20)+3, inf=1e9;
int n, m, st, buc[22], sum, v[N];
pa f[21][M];
char s[N][22];
bool bit(int s, int k){return s>>k&1;}

pa operator+(const pa x, const int i){return pa(x.first+i, x.second+i);}
pa operator+(pa x, pa y){
  if(x.first<y.first) swap(x, y);
  x.second=max(x.second, y.first);
  return x;
}

signed main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m, st=(1<<m)-1;
  rep(i, 0, m) rep(j, 0, M-1) f[i][j]=pa(-inf, -inf);
  rep(i, 1, n){
    rep(j, 0, m-1){
      cin>>s[i][j];
      v[i]<<=1;
      if(s[i][j]=='0') v[i]|=1;
      else ++buc[j];
    }
    f[0][v[i]]=f[0][v[i]]+pa(0, -inf);
  }
  
  rep(i, 0, m-1){
    rep(s, 0, st){
      f[i+1][s]=f[i+1][s]+(f[i][s]+bit(s, i));
      f[i+1][s^1<<i]=f[i+1][s^1<<i]+f[i][s];
    }
  }

  rep(i, 1, n){
    sum=0;
    int x=0;
    rep(j, 0, m-1){
      int tmp=buc[j];
      if(s[i][j]=='1') --tmp;
      tmp-=n/2, x<<=1;
      if(tmp>=1) ++sum;
      else if(tmp==0) x|=1;
    }
    int y=__builtin_popcount(v[i]&x);
    if(f[m][x].first==y) sum+=f[m][x].second;
    else sum+=f[m][x].first;
    cout<<sum<<'\n';
  }
}

---

## 作者：TernaryTree (赞：2)

很好的 sos-dp 练手题。

首先我们可以把 $M$ 个 $0/1$ 看做二进制压在一个数里，称作“状态”。

不妨令 $i$ 为主席。若此时提案 $j$ 的选票 $\gt \left\lfloor\dfrac N2\right\rfloor$，则无论怎么选副主席，$j$ 都能被通过。同理，若选票 $\lt \left\lfloor\dfrac N2\right\rfloor$，则无论怎么选，$j$ 都无法通过。于是我们只关心那些选票 $=\left\lfloor\dfrac N2\right\rfloor$ 的提案。

假设主席为 $i$ 时选票为 $\left\lfloor\dfrac N2\right\rfloor$ 的提案状态为 $s_i$。我们选 $j\ (j\neq i)$ 作为副主席，此时答案应为 $(\lnot a_j)\ \&\ s_i$。令 $b_i=\lnot a_i$，问题转换为找一个 $j$ 使得 $s_i\ \& \ b_j$ 最大。这里等价于在 $s_i$ 的子集内枚举这个最大值更新，即高位前缀和。同时需要次大值，因为 $i\neq j$。

前缀和之前的状态应该是什么呢，也就是这个状态 $s$ 是不是一个 $b_i$ 的子集。这里高维后缀和就行，也需要存两个值，不过任意存就行了。

复杂度 $\Theta(NM+M2^M)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)
#define gc getchar
#define pc putchar

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;

const int maxn = 1e6 + 10;
const int maxm = 22;
const bool multidata = 0;

int read() {
	int x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

void write(int x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write(x / 10), pc(x % 10 + '0');
}

int n, m, msk, tmp;
int a[maxn], b[maxn], c[1 << maxm];
int p[1 << maxm];
pii f[1 << maxm], g[1 << maxm];
int cnt[maxm];
int S;

bool cmp(int x, int y) {
	return p[b[x] & S] > p[b[y] & S];
}

pii merge(pii x, pii y) {
	vector<int> u;
	if (x.fs) u.push_back(x.fs); if (x.sc) u.push_back(x.sc);
	if (y.fs) u.push_back(y.fs); if (y.sc) u.push_back(y.sc);
	sort(u.begin(), u.end(), cmp); u.resize(unique(u.begin(), u.end()) - u.begin());
	pii ans;
	if (u.size() >= 2) ans = {u[0], u[1]};
	else ans = {(u.size() ? u[0] : 0), 0};
	return ans;
}

void fake_main() {
	pii x;
	n = read(), m = read(), msk = (1 << m) - 1;
	rep(i, 1, n) rep(j, 0, m - 1) a[i] |= ((tmp = read()) << j), cnt[j] += tmp;
	rep(i, 1, n) b[i] = msk ^ a[i], g[b[i]] = merge(g[b[i]], {i, 0});
	rep(i, 0, m) rep(s, 0, msk) if (!(s >> i & 1)) g[s] = merge(g[s], g[s ^ (1 << i)]);
	rep(s, 0, msk) f[s] = g[s], p[s] = __builtin_popcount(s);
	rep(i, 0, m) rep(s, 0, msk) if (s >> i & 1) S = s, f[s] = merge(f[s], f[s ^ (1 << i)]);
	rep(i, 1, n) {
		int s = 0, ans = 0, qwq = 0;
		rep(j, 0, m - 1) {
			tmp = cnt[j] - (a[i] >> j & 1);
			if (tmp == n / 2) s |= (1 << j);
			else if (tmp > n / 2) ++ans;
		}
		if (f[s].fs == i) write(ans + p[b[f[s].sc] & s]), pc('\n');
		else write(ans + p[b[f[s].fs] & s]), pc('\n');
	}
}

signed main() {
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}
```

---

## 作者：CatFromMars (赞：1)

被 cornercase 杀爆了，特此写题解，警钟敲烂。

很容易发现到，对于 $i$ 为主席，去掉它的提案。剩下的提案次数 $> \lfloor{\dfrac{n}{2}}\rfloor$ 就肯定能选上，小于就肯定不行，因此有用的只有恰好等于 $\lfloor{\dfrac{n}{2}}\rfloor$ 的情况。~~所以这个看上去就很有性质的除以 2 骗哥们呢。~~

然后问题就化成很典的形式，我们令 $B_i$ 为每个人提案，$A_i$ 为其补集，令 $x$ 为主席，$S_x$ 为恰好等于 $\lfloor\dfrac{n}{2}\rfloor$ 的提案集合。则是要求出 $\max\{\operatorname{popcount}(S_x\&A_y), y\not=x\}$。这个 $y\not=x$ 可以通过记录最大值和次大值消掉这条约束，所以只需要求出 $\max\{\operatorname{popcount}(S_x\&A_y)\}$ 即可（次大值同理）。

这是一个很经典的高维前缀和形式，但是我对这个并不太熟悉，所以要详细的说下 qwq。接下来我们认为二进制数最低位为 1（这样就会有一个 $0$ 作为空位了）。$f(i, T)$ 代表 $1\sim i$ 位中，与 $T$ 的前 $1\sim i$ 位与的 $\operatorname{popcount}$ 最大值。$T$ 的后 $(i + 1)\sim m$ 位代表原始的 $A_i$。

转移的时候考虑 $T$ 的第 $i$ 是否为 $1$，再讨论 $A$ 的第 $i$ 位是否为 $1$。根据定义很容易写出转移，比如 $T$ 的第 $i$ 位和 $A$ 的第 $i$ 位均为 $1$，那么 $f[i, T]$ 可以用 $f[i - 1, T] + 1$ 转移。详见注释。

一个卡了我很久的 corner case：边界条件显然是 $f(0, A_i) = 0$。但是如果 $A_i$ 出现了两次及以上，那么次大值也要赋为 $0$！能犯这种错误我也是神人了。樂。

```cpp
#include <bits/stdc++.h>
#define popc __builtin_popcount
using namespace std;
const int L = 23;
const int N = 5e5;
const int inf = 1e5;
int f[2][(1 << L) + 3][2];
int n, m;
int B[N + 10], A[N + 10], cnt[L + 3];
void upd(int i, int j, int val) {
//f[i][j][0] 最大，f[i][j][1] 次大
	if(val >= f[i][j][0]) {
		f[i][j][1] = f[i][j][0];
		f[i][j][0] = val;
	}
	else if(val > f[i][j][1]) 
		f[i][j][1] = val;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		int x = 0;
		for(int j = 0; j < m; j++) {
			cin >> x;
			B[i] |= (x * (1 << j));
			cnt[j] += x;
		}
		A[i] = (1 << m) - 1 - B[i];
	}

	memset(f, -0x3f, sizeof(f));
	for(int i = 1; i <= n; i++) {
		if(!f[0][A[i]][0]) f[0][A[i]][1] = 0;
//杀爆我的 corner case
		f[0][A[i]][0] = 0;
	}

	for(int i = 1; i <= m; i++) {
		for(int S = 0; S < (1 << m); S++)
			f[i % 2][S][0] = f[i % 2][S][1] = -inf;
		for(int S = 0; S < (1 << m); S++) {
			if((S >> (i - 1)) & 1) {
				upd(i % 2, S, f[(i - 1) % 2][S][0] + 1);//S 第 i 位 1，A 第 i 位 1
				upd(i % 2, S, f[(i - 1) % 2][S][1] + 1);
				upd(i % 2, S, f[(i - 1) % 2][S ^ (1 << (i - 1))][0]);//S 第 i 位 1，A 第 i 位 0
				upd(i % 2, S, f[(i - 1) % 2][S ^ (1 << (i - 1))][1]);
			}
			else {
				upd(i % 2, S, f[(i - 1) % 2][S ^ (1 << (i - 1))][0]);//S 第 i 位 0，A 第 i 位 1
				upd(i % 2, S, f[(i - 1) % 2][S ^ (1 << (i - 1))][1]);
				upd(i % 2, S, f[(i - 1) % 2][S][0]);//S 第 i 位 0，A 第 i 位 0
				upd(i % 2, S, f[(i - 1) % 2][S][1]);
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		int re = 0, S = 0;
		for(int k = 0; k < m; k++) {
			int w = cnt[k] - ((B[i] >> k) & 1);
			if(w > n / 2) re++;
			else if(w == n / 2) S |= (1 << k);
		}

		int pc = popc(S & A[i]);
		int a = f[m % 2][S][0], b = f[m % 2][S][1];
		if(a == pc) a = b;
		cout << a + re << '\n';
	}
}
```

---

## 作者：_lbw_ (赞：1)

# Preface

现有那篇题解有点抽象，但是他居然是对的。

我来个我想的 $\mathcal{O}(m^22^m+nm)$ 的做法，其实这个东西用来做这个题有点太复杂了。

# Part 1

我们设 $p=n/2$ 下取整，问题实际上就是每个提案删掉 chairperson 和 deputy chairperson 的贡献是否还 $\geq p$。

然后设提案初始通过人数为 $s_i$，先将 $s_i<p$ 的和 $s_i>p+1$ 的删去，因为这些提案的通过状态已经确定。

然后我们设 $rS_i$ 表示第 $i$ 个人通过的提案的状态压缩，考虑先枚举 chairperson，然后又会使一些提案的状态确定，最后剩下来的提案如果 deputy chairperson 通过则最后贡献是 $0$，我们设剩下来的提案的状态压缩为 $qS_i$。

问题至此转化为求 $\forall i\max_{j\not=i}|qS_i\& rS_j|$，暴力求解可得 $m^2$ 的做法。

# Part 2 for 78pts

我们考虑如何求这个东西，枚举 $qS_i\& rS_j=S$，可以先对 $qS$ 做高维前缀或得到 $S$，然后在值为 $1$ 的位置将值置为 $\textsf{popcount}(S)$，再做一遍高维后缀 max。

但这样漏掉了 $j\not=i$ 的限制。

此时做一次计算复杂度为 $\mathcal{O}(m2^m)$，无法缺 1 分治。

于是我们考虑分块，计算整块对单点的贡献与块间贡献。

设块长为 $B$，时间复杂度 $\mathcal{O}(nB+m2^m\dfrac{n}B)$，取 $B=\sqrt{m2^m}$ 得到最优时间复杂度 $\mathcal{O}(n\sqrt{m2^m})$。

# Part 2 for 100pts

显然，这种方法已经考虑到头了。

但是我们发现答案其实一定是 $\leq m$ 的，又因为我们不好扣除 $i$ 自己的贡献，于是将算 $\max$ 转为算方案。

我们照着上面的流程算一遍方案，但是发现会算重，因为高维前缀和时不仅仅计算了 $S$，还有 $S$ 的子集，怎么办呢？

考虑容斥。

我们先详细的阐述一遍上述流程，先将 $qS$ 的集合幂级数记作 $f$，高维前缀和得到 $S$，然后加上一位占位符，做高维后缀和得到 $g_{p,S}$。

接下来我们分析若原来的 $S$ 答案为 $f$，现在答案为 $g$，$f$ 和 $g$ 的关系。

$g_i$ 一定由 $j\geq i$ 的 $f_j$ 得到，容易发现其实是在 $j$ 位里任选 $i$ 位出来做，也就是说：

$$g_i=\sum\limits_{j=i}^n f_j \binom{j}{i}$$

二项式反演得：

$$f_i=\sum\limits_{j=i}^n g_j (-1)^{j-i}\binom{j}{i}$$

于是我们成功得出了方案数数组，扣除当前位的贡献后枚举答案判断 $f_i$ 是否大于 $0$ 即可。

这个做法可以扩展到有多个位置不选的情况。

时间复杂度 $\mathcal{O}(m^22^m+nm)$。

注意开 unsigned long long 以避免取模。

```cpp
#define ull unsigned long long
#define mem(x,val)memset(x,val,sizeof x)
#define D(i,j,n)for(register int i=j;i>=n;i--)
#define E(i,now)for(register int i=first[now];i;i=e[i].nxt)
#define F(i,j,n)for(register int i=j;i<=n;i++)
#define DL(i,j,n)for(register ll i=j;i>=n;i--)
#define EL(i,now)for(register ll i=first[now];i;i=e[i].nxt)
#define FL(i,j,n)for(register ll i=j;i<=n;i++)
ll read(){
	ll ans=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')ans=ans*10+c-'0',c=getchar();
	return ans*f;
}
mt19937 rnd(her1);
const int maxn = 3e5+5;
ll n,m,s[25],ans[maxn],T;
ll rS[maxn],bit[1<<20],qS[maxn];
bool _233[maxn][25],val[maxn][25];
ull f[1<<20],C[25][25],g[25][1<<20];
IV cadd(ll&x,ll val){x=(x+val)%cht;}
IV cmax(ll&x,ll val){x<val?x=val,0:0;}
ll w[maxn],wl[maxn],wr[maxn],orz[maxn];
IV print(ll S,char c=' '){F(i,0,m-1)putchar((S>>i&1)+'0');putchar(c);}
int main(){
	n=read();m=read();C[0][0]=1;
	F(i,1,n)F(j,0,m-1)_233[i][j]=read(),s[j]+=_233[i][j];
	F(i,0,20){C[i][0]=C[i][i]=1;F(j,1,i-1)C[i][j]=C[i-1][j]+C[i-1][j-1];}
	ll p=n/2,tt=0;
	F(j,0,m-1){
		if(s[j]<p)continue;if(s[j]>=p+2){T++;continue;}
		F(i,1,n)val[i][tt]=_233[i][j];s[tt++]=s[j];
	}
	m=tt;
	F(i,1,n)F(j,0,m-1)if(!val[i][j])rS[i]|=(1<<j);
	ll S=(1<<m)-1;F(s,1,S)bit[s]=bit[s>>1]+(s&1);
	F(i,1,n){
		ans[i]=T;
		F(j,0,m-1){
			if(s[j]==p&&val[i][j]);
			else if(s[j]==p+1&&!val[i][j])ans[i]++;
			else qS[i]|=(1<<j);
		}
	}
	F(i,1,n)f[rS[i]]++;
	F(i,0,m-1)F(s,0,S)if(!(s>>i&1))f[s]+=f[s^(1<<i)];

	F(s,0,S)g[bit[s]][s]+=f[s];
	F(p,0,m)F(i,0,m-1)F(s,0,S)if(s>>i&1)g[p][s]+=g[p][s^(1<<i)];
	F(s,0,S)F(p,0,m-1){
		F(k,p+1,m)g[p][s]+=((k-p&1)?-1:1)*C[k][p]*g[k][s];
	}
	F(i,1,n){
		g[bit[qS[i]&rS[i]]][qS[i]]--;
		D(j,m,0)if(g[j][qS[i]]){orz[i]=j;break;}
		g[bit[qS[i]&rS[i]]][qS[i]]++;
	}
	F(i,1,n)printf("%lld\n",orz[i]+ans[i]);
	return 0;
}
```









---

## 作者：fzitb7912 (赞：0)

题解摘自[做题记录](https://www.luogu.com.cn/article/3frkfgyz)。

## 分析

对于第 $i$ 个人当总统的情况，可以发现当去掉第 $i$ 个人的所有投票后，因为赞成的票数不会增加，所以当第 $j$ 项投票的赞成票数量小于 $\lfloor \frac{n}{2}\rfloor$ 时，是不可能有贡献的。而当数量大于 $\lfloor \frac{n}{2}\rfloor$ 时，在最坏情况下也不会小于 $\lfloor \frac{n}{2}\rfloor$，所以是一定有贡献的。

那么现在只需要考虑等于 $\lfloor \frac{n}{2}\rfloor$ 的情况。记其下标集合为 $s$。现在考虑对于一个人 $j$，那么他的贡献将是：$-\sum\limits_{x\in s}^{} [a_{j,x}=1]$。可以将 $s$ 看作一个二进制数，其中 $x \in s$ 的位置为 $1$，记为 $t$，那么贡献就是 $-|t  \cup a_j|$。所以现在对于第 $i$ 个人当总统的情况，我们就只需要解决除了 $i$ 以外 $|t \cup a_j|$ 的最小值。$j \ne i$ 这个限制很弱，统计最小和次小就行了。

现在问题就变成求 $|x \cup a_i|$ 的最小值。因为 $a_i$ 是 $x \cup a_i$ 的超集，$x\cup a_i$ 是 $x$ 的子集。所以我们可以考虑先处理前半部分再处理后半部分。但是如果取 $\min$ 的话就会出现 $x$ 的答案变成 $0$ 的情况。因为空集是 $a_i$ 的子集同时也一定是 $x$ 的子集。如果我们将 $a_i$ 取反，求 $|x \cup b_i|$ 的最大值，再拿 $|x|$ 减去，就可以用两遍 SOS DP 解决了。时间复杂度 $O(m2^m)$。

这里只针对了最大值，实际上为了保证 $i \ne j$ 还需要记录次大值。证明可行简单。参考 CSP-J 2024 T4 题解。

注意记录最大值和次大值的时候，需要保证这两个值的编号不同。

## 代码

```cpp
il pii get1(pii x,pii y){
	vector<int> v;v.clear();
	v.push_back(x.x),v.push_back(x.y),v.push_back(y.x),v.push_back(y.y);
	sort(v.begin(),v.end(),[](int x,int y){
		return __builtin_popcount(b[x])>__builtin_popcount(b[y]);
	});
	unique(v.begin(),v.end())-v.begin();
	return {v[0],((int)v.size())==1?0:v[1]};
}
il pii get2(pii x,pii y,int s_){
	vector<int> v;v.clear();
	v.push_back(x.x),v.push_back(x.y),v.push_back(y.x),v.push_back(y.y);
	sort(v.begin(),v.end(),[s_](int x,int y){
		return __builtin_popcount(b[x]&s_)>__builtin_popcount(b[y]&s_);
	});
	unique(v.begin(),v.end())-v.begin();
	return {v[0],((int)v.size())==1?0:v[1]};
}

il void solve(){
	n=rd,m=rd,T=(1ll<<m)-1;
	for(re int i=1;i<=n;++i){
		b[i]=T;
		for(re int j=1;j<=m;++j){
			int x=rd;
			a[i][j]=x,cnt[j]+=x;
			if(x==1) b[i]^=(1ll<<(j-1));
		}
		f[b[i]]=get1(f[b[i]],{0,i});
	}
	for(re int i=0;i<m;++i)
	for(re int j=0;j<(1ll<<m);++j)
	if(!((j>>i)&1)) f[j]=get1(f[j],f[j^(1ll<<i)]);
	for(re int i=0;i<m;++i)
	for(re int j=0;j<(1ll<<m);++j)
	if((j>>i)&1) f[j]=get2(f[j],f[j^(1ll<<i)],j);
	for(re int i=1;i<=n;++i){
		int x=0,sum=0;
		for(re int j=1;j<=m;++j){
			int Cnt=cnt[j]-a[i][j];
			if(Cnt>(n/2)) ++sum;
			else if(Cnt==(n/2)) ++sum,x|=(1ll<<(j-1));
		}
		sum-=__builtin_popcount(x);
		pii s=f[x];
		int Max=0;
		if(s.x!=i) Max=max(Max,1ll*__builtin_popcount(x&b[s.x]));
		if(s.y!=i) Max=max(Max,1ll*__builtin_popcount(x&b[s.y]));
		sum+=Max;
		printf("%lld\n",sum);
	}
    return ;
}
```

---

## 作者：_Luminescence_ (赞：0)

重新学了一遍高维前缀和/sos-dp，深刻理解了！以下内容是在知道本题要 sos-dp 后独立思考得出的。

注意到，钦定一个人为主席后，对于此时得票数大于 $\lfloor \frac{n}{2} \rfloor$ 的议案，不管怎么选副主席，均能通过；对于此时得票数小于 $\lfloor \frac{n}{2} \rfloor$ 的议案，不管怎么选副主席，均不能通过。所以需要考虑的只有此时得票数恰好等于 $\lfloor \frac{n}{2} \rfloor$ 的议案。

记 $S_i$ 为：钦定 $i$ 为主席后，得票数等于 $\lfloor \frac{n}{2} \rfloor$ 的议案集合。记 $T_i$ 为 $i$ 的投票状态取反后的状态。记 $base_i$ 为：钦定 $i$ 为主席后，此时得票数大于 $\lfloor \frac{n}{2} \rfloor$ 的议案的个数。那么对于 $i$ 的答案，形式化表述即为：

$base_i+\max_{T_j \bigcap S_i} \mid T_j \bigcap S_i \mid$

这是一个我们熟知的高维前缀 $\max$ 的形式。但是我们还要对 $T_j$ 这个条件进行限制，所以不能直接做高维前缀 $\max$。接下来考虑如何处理这个限制：注意到，$T_j$ 是 $T_j \bigcap S_i$ 的超集，而 $T_j \bigcap S_i$ 又是  $S_i$ 的子集。那么，我们可以先以 $T_j$ 为基础做一遍高维后缀 $\max$（即超集 $\max$），再做一遍高维前缀 $\max$ 即可。这样就能保证枚举到的集合同时满足是 $S_i$ 和 $T_j$ 的子集这两个条件，因此是合法的。

因为本题还要求主席与副主席的编号不同，所以在转移的时候，不仅要维护最大值和最大值编号，还要维护次大值及其编号。写起来有点令人暴躁。

[题交记录](https://loj.ac/s/2032773)

---


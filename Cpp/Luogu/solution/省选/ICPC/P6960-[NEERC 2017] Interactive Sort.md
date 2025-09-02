# [NEERC 2017] Interactive Sort

## 题目描述

Heidi 正在分析一个特殊的设备。该设备以一个 $a$ 作为输入，并使用以下伪代码和存储在设备中的一些整数 $d$ 和 $n$ 计算 $a^d \bmod n$：

```
modPow(a, d, n) {
  r = 1;
  for (i = 0; i < 60; ++i) {
    if ((d & (1 << i)) != 0) {
      r = r * a % n;
    }
  a = a * a % n;
  }
}
```

注意，伪代码假设整数可以是任意大小，$<<$ 表示按位左移，$&$ 表示按位与，% 表示取模。

设备不会告诉 Heidi 计算结果。然而，Heidi 可以测量计算所需的时间。她知道只有模 $n$ 的乘法（上述伪代码中的第 5 行和第 7 行）需要可测量的时间，其他所有行可以假设为 0 纳秒。

此外，她知道将 $x$ 和 $y$ 模 $n$ 相乘需要 $(\text{bits}(x) + 1) \cdot (\text{bits}(y) + 1)$ 纳秒，其中 $\text{bits}(x)$ 是 $x$ 的二进制表示中不含前导零的位数，更正式地，$\text{bits}(x) = \lceil \log_2 (x + 1) \rceil$。

Heidi 知道整数 $n$，但不知道整数 $d$。她想通过将不同的整数 $a$ 作为输入提供给设备，并测量每个 $a$ 的计算时间来找到 $d$。

她知道 $n$ 和 $d$ 是通过以下方式选择的：首先，两个具有 30 位二进制表示的素数 $p$ 和 $q$（换句话说，在 $2^{29}$ 和 $2^{30} - 1$ 之间）被独立且均匀地随机选择。然后计算 $n = p \cdot q$。然后计算 $m = \varphi(n) = (p-1) \cdot (q-1)$。然后在 $1$ 到 $m - 1$ 之间均匀随机选择 $d$，使其与 $m$ 互质。

# 交互协议

首先，测试系统写入整数 $n$——设备使用的模数。注意，$n$ 和隐藏的数字 $d$ 保证是按照上述过程生成的。

你的解决方案应打印两种类型的请求：

- “? a” 告诉设备以 $a$ 作为输入。$a$ 必须是 $0$ 到 $n-1$ 之间的整数。测试系统会返回设备计算 `modPow(a , d , n)` 所需的时间（以纳秒为单位）。

- “! d” 告诉你的程序已确定的 $d$ 值。

不要忘记在每次请求后刷新输出！

你的解决方案必须发出恰好一个第二种类型的请求，该请求必须是最后一个请求，并且解决方案在发出该请求后必须正常终止。

你的解决方案最多可以发出 $30,000$ 个第一种类型的请求。

你的解决方案将在 $30$ 个测试用例上运行，每次运行处理一个 $(n , d)$ 对。对于每个测试用例，数字 $n$ 和 $d$ 是固定的，并且是使用上述过程生成的。下面的例子不是以这种方式生成的，因此不会用于测试你的解决方案；它仅用于说明输入/输出格式并为计算时间的合理性检查提供一个 sanity check。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
>
>
<
>
<
<
```

### 输出

```
? 1 1
? 1 2
? 1 3
? 2 1
? 2 2
? 2 3
! 4 2 1 3 5```

# 题解

## 作者：EuphoricStar (赞：3)

NOIP 模拟赛 T2。随机化交互好题。

令 $a$ 为原题面中的 $e$，$b$ 为原题面中的 $o$。

显然可以使用 $\left\lceil\frac{n}{2}\right\rceil$ 次询问求出 $a$ 中任意其中一个元素的值，全部问一遍 $a_i$ 和 $b_j$ 的大小关系即可。但是这样很浪费。

考虑我们求出了一个 $a_i$，我们还知道了所有 $b_j$ 和这个 $a_i$ 的大小关系。那么经过这 $n$ 次询问后，$b$ 被分成了两个值域的“块”，我们知道两个块的值域的 $[l, r]$ 和它们包含哪些位置。

那么当我们求每一个 $a_i$，$b$ 中的一个块会分成两个，除非 $n$ 为偶数且 $a_i = n$，这种情况特判即可。通过二分我们可以知道 $a_i$ 可能在哪**两个**块中。二分 `check` 时和块内任意一个 $b_j$ 比较即可。得到这两个块后，暴力把块中每个元素都比较一遍，就可以把其中一个块分成两个，同时也能知道 $a_i$ 的值。

现在问题是询问次数没有保证。考虑以一个随机的顺序问 $a_i$，问完 $i$ 个 $a$ 后每个块的期望大小约为 $\frac{n}{2i}$，暴力问两个块，最坏就是期望问 $\frac{n}{i}$ 次。再加上二分的次数 $\sum\limits_{i = 1}^n \log_2i$，$n = 10000$ 时期望询问次数约为 $1.45 \times 10^5$。实际会略大，但是能过。

```cpp
const int maxn = 10050;

int n, a[maxn], b[maxn], p[maxn];

struct node {
	int l, r;
	vector<int> ps;
};

void solve(int _n) {
	n = _n;
	node u;
	u.l = 1;
	u.r = (n + 1) / 2 * 2 - 1;
	for (int i = 1; i <= (n + 1) / 2; ++i) {
		u.ps.pb(i);
	}
	vector<node> vc;
	vc.pb(u);
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	for (int i = 1; i <= n / 2; ++i) {
		p[i] = i;
	}
	shuffle(p + 1, p + n / 2 + 1, rnd);
	for (int i = 1; i <= n / 2; ++i) {
		int l = 0, r = (int)vc.size() - 1;
		while (r - l + 1 > 2) {
			int mid = (l + r) >> 1;
			if (ask(p[i], vc[mid].ps[0])) {
				l = mid;
			} else {
				r = mid;
			}
		}
		bool flag = 1;
		for (int j = l; j <= r; ++j) {
			vector<int> v1, v2;
			for (int x : vc[j].ps) {
				if (ask(p[i], x)) {
					v1.pb(x);
				} else {
					v2.pb(x);
				}
			}
			if (v1.empty() || v2.empty()) {
				continue;
			}
			flag = 0;
			if (j) {
				a[p[i]] = vc[j - 1].r + 1;
			}
			a[p[i]] += (int)v1.size() * 2;
			node u;
			u.l = a[p[i]] + 1;
			u.r = vc[j].r;
			vc[j].r = a[p[i]] - 1;
			vc[j].ps = v1;
			u.ps = v2;
			vc.insert(vc.begin() + j + 1, u);
			break;
		}
		if (flag) {
			a[p[i]] = n;
		}
	}
	for (node u : vc) {
		b[u.ps[0]] = u.l;
	}
	vector<int> v1, v2;
	for (int i = 1; i <= n / 2; ++i) {
		v1.pb(a[i]);
	}
	for (int i = 1; i <= (n + 1) / 2; ++i) {
		v2.pb(b[i]);
	}
	report(v1, v2);
}
```


---

## 作者：RedreamMer (赞：3)

[$\huge\texttt{P6960}$](https://www.luogu.com.cn/problem/P6960)

[$\texttt{In my cnblogs}$](https://www.cnblogs.com/RedreamMer/p/14550108.html)

标签：二分、分块思想，~~平衡树~~

## 题意

交互题。

有 $[1,n]$ $n$ 个数字，按奇偶分为两部分，显然偶数有 $\lfloor \frac{n}{2} \rfloor$ 个，奇数有 $\lceil \frac{n}{2}\rceil$ 个，两部分打乱。

每次可以询问偶数部分第 $i$ 个数和奇数部分 $j$ 个数之间的大小关系，问在 $300000$ 次内求出所有位置的数。

$n \le 10000$

## 思路

看到询问次数大概是 $n$ 范围的 $10$ 多倍，~~以及交互题的特性~~，联想到二分。

而我们又可以发现一个美好的性质，将某个偶数与所有奇数做一次询问操作不但能确定这个偶数的大小，还能将所有的奇数按这个大小划分成两部分。

暴力一点，我们直接做 $\mathcal O((\frac{n}{2})^2)$ 次询问，偶数和奇数都可以确定下来。

这显然不能通过此题，~~这时你会发现二分还没用~~。

这个方法的最大缺陷是对于所有的偶数的询问都没有**较好地**联系起来（询问得到的信息只使确定奇数更方便，并没有为之后的偶数的询问提供便捷），考虑怎样优化这部分。

（以下所述“区间”均为部分奇数最大值与最小值构成的区间）

假设第一次偶数已经将奇数划分为 $A,B$ 两部分，而第二个偶数的询问 $\lceil \frac{n}{2}\rceil$ 次，显然只能将其中一个区间划分成两小部分，对于另一个区间**无任何作用**，因为对于另一个区间，返回的**都是**大于或小于。

当询问更多时，后面的偶数的询问大多数都是无意义的。

因此，我们只要找到偶数所属（被包含的那个奇数区间）的那个区间的奇数，再在其中为其划分。

但是，因为我们一开始并不知道那个偶数的大小，我们只能二分所有区间，因为要比较，所以我们定义一个区间的标记值为任意一个奇数的值，所有区间的这个值显然是**单调的**。

我们拿偶数与之二分比较，**但是**它所属的那个区间可能返回是大于也可以是小于，但**必定是**单调的区间的分界线，所以我们把分界线的两个区间都拿来做一次划分操作，也只会增加常数级的询问。

为了更好地维护二分（即你划分了一个区间之后还要维护其单调性，这显然是普通的数组无法维护的），因为蒟蒻不理解为什么其他题解里面vector一个个冒泡排序时间复杂度是合理的，我使用了清新的平衡树维护：）。

注意：为了避免讨论奇数个数等于偶数个数的情况，我们多加一个奇数在数组末尾然后每次询问它的时候都直接返回 `<`。

算一下询问的复杂度：$\mathcal O(n)=\sum_{i=1}^{i\le \frac{n}{2}} \frac{2n}{i} + \log i =\mathcal O(n\log n)$。 (期望复杂度)

时间复杂度：$\mathcal O(n)=\sum_{i=1}^{i\le \frac{n}{2}} \log^2 i=\mathcal O(n\log n)$。

## 代码

```cpp
int a, id, root, ans[N + 10], h[N + 10];
bool fake;
char opt;
vector<int> e[N + 10], L, R;
struct node
{
    int val, ls, rs, rnd, siz;
} s[N + 10];

inline int New(int n)
{
    s[++id].val = n;
    s[id].ls = s[id].rs = 0;
    s[id].rnd = rand();
    s[id].siz = 1;
    return id;
}

inline void up(int n) { s[n].siz = s[s[n].ls].siz + s[s[n].rs].siz + 1; }

inline void split(int n, int val, int &x, int &y)
{
    if (!n)
    {
        x = y = 0;
        return;
    }
    if (s[n].val <= val)
        x = n, split(s[n].rs, val, s[n].rs, y);
    else
        y = n, split(s[n].ls, val, x, s[n].ls);
    up(n);
}

inline int merge(int x, int y)
{
    if (!x || !y)
        return x + y;
    if (s[x].rnd < s[y].rnd)
    {
        s[x].rs = merge(s[x].rs, y);
        up(x);
        return x;
    }
    else
    {
        s[y].ls = merge(x, s[y].ls);
        up(y);
        return y;
    }
}

inline void ins(int n)
{
    int x, y;
    split(root, n - 1, x, y);
    root = merge(merge(x, New(n)), y);
}

inline int val(int rt, int n)
{
    int res, now = rt;
    while (1)
    {
        if (s[s[now].ls].siz >= n)
            now = s[now].ls;
        else if (n == s[s[now].ls].siz + 1)
            return s[now].val;
        else
            n -= s[s[now].ls].siz + 1, now = s[now].rs;
    }
}

inline void query(int l, int r)
{
    if (r == (a + 1) / 2 && fake)
    {
        opt = '<';
        return;
    }
    cout << "? " << l << ' ' << r << endl;
    fflush(stdout);
    cin >> opt;
}

inline bool solve(int n, int i)
{
    L.clear();
    R.clear();
    for (int j = 0; j < e[n].size(); j++)
    {
        query(i, e[n][j]);
        if (opt == '>')
            L.PB(e[n][j]);
        else
            R.PB(e[n][j]);
    }
    if (!L.size() || !R.size())
        return false;
    ans[i] = n + (L.size() - 1) * 2 + 1;
    ins(ans[i] + 1);
    e[n] = L;
    e[ans[i] + 1] = R;
}

inline void solvepair(int l1, int l2, int i)
{
    bool res = solve(l1, i);
    if (res)
        return;
    solve(l2, i);
}

signed main()
{
    // freopen("in1.in", "r", stdin);
    ios::sync_with_stdio(0);
    a = read();
    if ((a & 1) == 0)
        a++, fake = 1;
    ins(1);
    for (int i = 1; i <= (a + 1) / 2; i++)
        e[1].PB(i);
    for (int i = 1; i <= a / 2; i++)
    {
        int l = 1, r = i, l1 = -1, l2 = -1;
        while (l <= r)
        {
            int mid = (l + r) >> 1, tmp = val(root, mid);
            query(i, e[tmp][0]);
            if (opt == '<')
                r = mid - 1, l2 = tmp;
            else
                l = mid + 1, l1 = tmp;
        }
        if (l1 == -1)
            solve(l2, i);
        else if (l2 == -1)
            solve(l1, i);
        else
            solvepair(l1, l2, i);
    }
    cout << "! ";
    for (int i = 1; i <= a / 2; i++)
        cout << ans[i] << ' ';
    for (int i = 1; i <= a; i += 2)
        h[e[i][0]] = i;
    for (int i = 1; i <= (a + 1) / 2; i++)
        cout << h[i] << ' ';
    return 0;
}
```

---

## 作者：JWRuixi (赞：3)

### 题意

给定 $n$，交互库有两个分别包含 $1 \sim n$ 的偶数和奇数的序列 $a, b$（打乱后），你可以询问 `x y`，交互库返回 $a_x, b_y$ 的大小关系（询问不超过 $Q$），请你还原两个数组。

$n \le 10^4, Q \le 3 \times 10^5$，提交地址：<https://www.luogu.com.cn/problem/P6960>。

加强：$Q \le 2 \times 10^5$，提交地址：<http://www.gdfzoj.com:23380/contest/878/problem/8643>。

### 分析

$Q = (\dfrac{n}{2})^2$ 的暴力是 trivial 的，假设我们真的这样询问，那么我们需要考虑能从前面的询问中得到什么信息。

通过这样的询问，我们能将 $b$ 数组分为两部分：小于 $a_i$ 和大于 $a_i$。但我们发现两次询问既有相同的部分，又有不同的部分，而通过大量的询问得到相同的信息就有点劣了，我们考虑在此基础上优化。

我们认为目前按照已经询问过的 $a$ 将 $b$ 划分成若干个值域集合，但每个集合内的对应关系还不确定，有个显然的想法是考虑二分当前的 $a$ 属于哪个集合。

因为不确定对应关系，所以要询问整个段，随机下询问次数约为 $\sum \dfrac{n\log(i + 1)}{i + 1}$ 大概是 $n \ln n \log n$，因为常数较小，足以通过本题。

但是注意到，如果我只每段取一个样本考察，那么误差至多为 $1$，略微调整就能找到真正的目标。这样的询问次数就是 $\sum (\log(i + 1) + \dfrac{n}{i + 1})$，就能将询问次数卡到 $1.45 \times 10^5$（~~足以通~过 GDFZOJ 上的加强数据~~）。

### Code

提交记录：<https://paste.ubuntu.com/p/cqcTr6Bnd4/>（$Q \le 2 \times 10^5$），<https://paste.ubuntu.com/p/HzDRYgdSmC/>（$Q \le 3 \times 10^5$）。

---

## 作者：mskqwq (赞：0)

有趣的交互，但感觉这个数据随机提示性太强了，改成交互库不自适应的话就好些了。

首先我们可以问 $\lfloor \dfrac n 2 \rfloor$ 次确定一个奇数的具体值，同时我们还能把偶数的序列分成两部分：大于这个奇数和小于这个奇数。假如我们确定了 $k$ 个奇数，那么偶数序列就会被分成 $k+1$ 分。当 $k$ 比较大时，如果我们想再确定一个奇数，那么把偶数序列全跟它比较一次实在太浪费了。考虑在这 $k+1$ 个部分上二分，我们在一个块内随便问一个位置，就能知道这个奇数所在的块的位置是 $\le $ 这个块还是 $\ge$ 这个块，最后剩不超过两个块时暴力找。由于数据随机，所以复杂度为 $O(\sum \dfrac n i)=O(n \ln n)$。

实现可以偷懒使用 vector，不需要平衡树。

```cpp
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>
#define fi first
#define se second
#define ep emplace
#define MISAKA main
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define _rep(i,a,b) for(int i=a;i>=b;--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char ch=getchar();int f=1,x=0;
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=1e5+10,mod=998244353;
int a[N],p[N],e[N],o[N],n,m;
struct node{int l,r,v;
    node(int a=0,int b=0,int c=0){l=a,r=b,v=c;}
};vector<node> v;
bool ask(int x,int y){
    printf("? %d %d\n",x,y);fflush(stdout);
    char c[5];scanf("%s",c);
    return c[0]=='>';
}
void misaka(){
    n=read(),m=(n+1)/2,n-=m;
    if(n+m==1){printf("! 1");return;}
    rep(i,1,n) p[i]=i;
    v.eb(0,0,0);v.eb(1,n,0);
    rep(i,1,m){
        int l=1,r=v.size()-1,f=0;
        while(r-l>1){
            int mid=l+r>>1;
            if(ask(p[v[mid].l],i)) r=mid;
            else l=mid;
        }
        rep(t,l,r){
            vector<int> L,R;
            int x=v[t].l,y=v[t].r,c=v[t].v;
            rep(j,x,y){
                if(ask(p[j],i)) R.eb(p[j]);
                else L.eb(p[j]),c++;
            }
            if(L.size()&&R.size()){
                o[i]=2*c+1;
                int k=L.size();
                rep(j,x,x+k-1) p[j]=L[j-x];
                rep(j,x+k,y) p[j]=R[j-x-k];
                v[t].r=x+k-1;
                v.ep(v.begin()+t+1,node(x+k,y,c));
                f=1;break;
            }
        }
        if(!f){
            if(ask(1,i)) o[i]=1;
            else o[i]=n+m;
        }
    }
    for(auto [l,r,v]:v)if(l) e[p[l]]=2*v+2;
    printf("! ");
    rep(i,1,n) printf("%d ",e[i]);fflush(stdout);
    rep(i,1,m) printf("%d ",o[i]);fflush(stdout);
}
bool __ed;
signed MISAKA(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs  ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB\n",abs(&__st-&__ed)/1024./1024);});
    #endif
    
    int T=1;
    while(T--) misaka();
    return 0;
}
```

---

## 作者：Yansuan_HCl (赞：0)

有一个暴力是，对每个偶数询问它和所有奇数的大小关系。这样两个询问之间没有共同信息。

每次询问，根据结果可以把奇数按大小划分成两段。$i$ 次询问能分成 $2i$ 段。不妨先二分确定这个偶数在哪个段：有若干个返回 `>` 的，一个既有 `>` 又有 `<` 的，若干个返回 `<` 的。若每段采样一个，则找到的最后一个 `>` 可能是第一种也可能是第二种；若是第一种，则第二种在第一种的后面一段。

找到段之后，由于段内没有任何信息，只好暴力询问。随机情况下，期望段长是 $O(n/2i)$，每次期望询问 $O(n/i)$。总询问复杂度即为 $O(n\ln n)$。

---


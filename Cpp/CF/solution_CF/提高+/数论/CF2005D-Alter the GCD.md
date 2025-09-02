# Alter the GCD

## 题目描述

You are given two arrays $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ .

You must perform the following operation exactly once:

- choose any indices $ l $ and $ r $ such that $ 1 \le l \le r \le n $ ;
- swap $ a_i $ and $ b_i $ for all $ i $ such that $ l \leq i \leq r $ .

Find the maximum possible value of $ \text{gcd}(a_1, a_2, \ldots, a_n) + \text{gcd}(b_1, b_2, \ldots, b_n) $ after performing the operation exactly once. Also find the number of distinct pairs $ (l, r) $ which achieve the maximum value.

## 说明/提示

In the first, third, and fourth test cases, there's no way to achieve a higher GCD than $ 1 $ in any of the arrays, so the answer is $ 1 + 1 = 2 $ . Any pair $ (l, r) $ achieves the same result; for example, in the first test case there are $ 36 $ such pairs.

In the last test case, you must choose $ l = 1 $ , $ r = 2 $ to maximize the answer. In this case, the GCD of the first array is $ 5 $ , and the GCD of the second array is $ 1 $ , so the answer is $ 5 + 1 = 6 $ , and the number of ways is $ 1 $ .

## 样例 #1

### 输入

```
5
8
11 4 16 17 3 24 25 8
8 10 4 21 17 18 25 21
4
6 4 24 13
15 3 1 14
2
13 14
5 8
8
20 17 15 11 21 10 3 7
9 9 4 20 14 9 13 1
2
18 13
15 20```

### 输出

```
2 36
3 2
2 3
2 36
6 1```

# 题解

## 作者：xishanmeigao (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF2005D)

扫左端点 $l$，对于右边形成本质不同的 $\log V$ 个 $\gcd$ 区间的右端点依次考虑。设它们分别为 $r_1<r_2<\dots <r_t$。

对两个序列分别求出本质不同的后缀 $\gcd$ 以及其左端点，找到 $(r_{j-1},r_j]$ 之间的所有这样的左端点 $p_k$ 依次考虑。此时序列被分割为 $[1,l)\cup [l,p_k]\cup (p_k,n]$，选择方案有 $p_{k+1}-p_k$ 种。

时间复杂度 $\mathcal{O}(n\log^2 V)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;

const int N=2e5+10,M=33;

int n,a[N],b[N],lg[N];
int ta[N],tb[N],tA,tB,ida[N],idb[N];
pii fa[N][M],fb[N][M],sufa[N],sufb[N];
int Sufa[N],Sufb[N],Prea[N],Preb[N];
pii pr[N]; int cnt;	
bool flag;

struct node
{
	int mx; LL cnt;

	friend node operator + (const node &A,const node &B)
	{
		node C;
		if(A.mx>B.mx) C=A;
		else if(A.mx<B.mx) C=B;
		else C={A.mx,A.cnt+B.cnt};
		return C;
	}
}ans;

int gcd(int x,int y)
{
	if(y==0) return x;
	return gcd(y,x%y);
}

struct ST
{
	int st[N][M];

	void prework()
	{
		for(int j=1; j<=lg[n]; j++)
			for(int i=1; i+(1<<j)-1<=n; i++)
				st[i][j]=gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	}

	int ask(int l,int r)
	{
		if(l>r) return 0;
		int k=lg[r-l+1];
		return gcd(st[l][k],st[r-(1<<k)+1][k]);
	}
}A,B;

inline int ask(int pd,int l,int r)
{
	if(pd==1) return A.ask(l,r);
	return B.ask(l,r);
}

inline void solve(int *a,pii (*f)[M],int *t,int &T,pii *suf,int *id,int pd)
{
	cnt=0;
	for(int i=n; i>=1; i--)
	{
		t[i]=0;
		pr[++cnt]={a[i],i};
		for(int j=1; j<=cnt; j++)
			pr[j].fi=gcd(pr[j].fi,a[i]);
		pr[0]={0,0};
		for(int j=1; j<=cnt; j++)
			if(pr[j].fi!=pr[j-1].fi)
				f[i][++t[i]]=pr[j];
		for(int j=1; j<=t[i]; j++)
			pr[j]=f[i][j];
		cnt=t[i];
		reverse(f[i]+1,f[i]+1+t[i]);
	}

	id[n+1]=0;
	suf[0]={0,n+1};
	suf[T=1]={a[n],n}; id[n]=T;
	for(int i=n-1; i>=1; i--)
	{
		id[i]=T;
		if(ask(pd,i,n)==suf[T].fi) continue;
		suf[T].se=i+1;
		suf[++T].fi=ask(pd,i,n);
		id[i]=T;
	}
	suf[T].se=1;
}

inline void mian()
{
	cin>>n;
	for(int i=1; i<=n; i++)
		cin>>a[i], A.st[i][0]=a[i];
	for(int i=1; i<=n; i++)
		cin>>b[i], B.st[i][0]=b[i];

	A.prework(); B.prework();

	solve(a,fa,ta,tA,sufa,ida,1); solve(b,fb,tb,tB,sufb,idb,2);

	Prea[0]=Preb[0]=0;
	for(int i=1; i<=n; i++)
	{
		Prea[i]=gcd(Prea[i-1],a[i]);
		Preb[i]=gcd(Preb[i-1],b[i]);
	}
	Sufa[n+1]=Sufb[n+1]=0;
	for(int i=n; i>=1; i--)
	{
		Sufa[i]=gcd(Sufa[i+1],a[i]);
		Sufb[i]=gcd(Sufb[i+1],b[i]);
	}

	for(int i=1; i<=n; i++)
	{
		vector <pii> R;
		int pa=1,pb=1;
		while(pa<=ta[i] && pb<=tb[i])
		{
			if(fa[i][pa].se<fb[i][pb].se) R.push_back(fa[i][pa++]);
			else if(fa[i][pa].se>fb[i][pb].se) R.push_back(fb[i][pb++]);
			else R.push_back(fa[i][pa++]), pb++;
		}
		while(pa<=ta[i]) R.push_back(fa[i][pa++]);
		while(pb<=tb[i]) R.push_back(fb[i][pb++]);
		int lst=i;
		for(auto [V,j]:R)
		{
			pa=ida[j+1], pb=idb[j+1];
			int nowa=A.ask(i,j),nowb=B.ask(i,j);
			vector <pii> P;
			while(pa<=tA && pb<=tB && sufa[pa].se-1>=lst && sufb[pb].se-1>=lst)
			{
				if(sufa[pa].se>sufb[pb].se) P.push_back(sufa[pa++]);
				else if(sufa[pa].se<sufb[pb].se) P.push_back(sufb[pb++]);
				else P.push_back(sufa[pa++]), pb++;
			}
			while(pa<=tA && sufa[pa].se-1>=lst) P.push_back(sufa[pa++]);
			while(pb<=tB && sufb[pb].se-1>=lst) P.push_back(sufb[pb++]);
			if(!P.size() || (P.size() && P.back().se-1!=lst)) P.push_back({0,lst+1});	

			int len=P.size();
			for(int k=0; k<len; k++)
			{
				int p=P[k].se-1,tmp=(k==0? j+1:P[k-1].se-1)-p;
				int cura=gcd(gcd(Prea[i-1],nowb),Sufa[p+1]);
				int curb=gcd(gcd(Preb[i-1],nowa),Sufb[p+1]);
				ans=ans+(node){cura+curb,(LL)tmp};
			}
			lst=j+1;
		}
	}

	cout<<ans.mx<<" "<<ans.cnt<<"\n";
	ans.mx=ans.cnt=0;
}	

int main()
{
	// freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);

	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	lg[1]=0;
	for(int i=2; i<=N-10; i++)
		lg[i]=lg[i>>1]+1;

	int T; cin>>T;
	while(T--) mian();	
	
	return 0;
}
```

---

## 作者：WhisperingWillow (赞：1)

此题解为无脑算法。

考虑会划分成不多个前缀 $\gcd$ 均不同段。

在相同段中，判断交换优不优秀即可。



```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
template <class T>
void write(T x)
{
    static int stk[30];
    if (x < 0)
        putchar('-'), x = -x;
    int top = 0;
    do
    {
        stk[top++] = x % 10, x /= 10;
    } while (x);
    while (top)
        putchar(stk[--top] + '0');
}
template <class T>
void write(T x, char lastChar) { write(x), putchar(lastChar); }
template <typename T>
void chkmx(T &x, T y) { x = max(x, y); }
typedef long long ll;
inline int gcd(int a, int b)
{
    if (!a | !b)
        return a + b;
    int az = __builtin_ctz(a);
    int bz = __builtin_ctz(b);
    int z = min(az, bz);
    a >>= az, b >>= bz;
    while (a ^ b)
    {
        int diff = b - a;
        az = __builtin_ctz(diff);
        b = min(a, b), a = abs(diff) >> az;
    }
    return a << z;
}
int f[18][200020];
int g[18][200020];
int x[2][200020];
int y[2][200020];
inline void solve()
{
    int n;
    read(n);
    int a[n + 1] = {};
    int b[n + 1] = {};
    for (int i = 1; i <= n; i++)
        read(a[i]);
    for (int i = 1; i <= n; i++)
        read(b[i]);
    auto GCD = [&](int l, int r, bool flag)
    {
        if (l > r)
            return 0;
        int p = __lg(r - l + 1);
        return gcd((flag ? g : f)[p][l], (flag ? g : f)[p][r - (1 << p) + 1]);
    };
    for (int i = 1; i <= n; i++)
        f[0][i] = a[i];
    for (int j = 1; j < 18; j++)
    {
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[j][i] = gcd(f[j - 1][i], f[j - 1][i + (1 << j - 1)]);
    }
    for (int i = 1; i <= n; i++)
        g[0][i] = b[i];
    for (int j = 1; j < 18; j++)
    {
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            g[j][i] = gcd(g[j - 1][i], g[j - 1][i + (1 << j - 1)]);
    }
    for(int i = 0; i <= n + 1; ++ i){
        x[0][i] = GCD(i, n , 0);
        x[1][i] = GCD(i, n , 1);
        y[0][i] = GCD(1, i, 0);
        y[1][i] = GCD(1, i , 1);
    }
    int ans = 0;
    ll sum = 0;
    for (int i = 1; i <= n; i++)
    {
        int ga = 0, gb = 0, fa = 0, fb = 0;
        int pos = i;
        while (pos <= n)
        {
            // ga = gcd(gcd(GCD(1, i - 1, 0), GCD(i, pos, 1)), GCD(pos + 1, n, 0));
            // gb = gcd(gcd(GCD(1, i - 1, 1), GCD(i, pos, 0)), GCD(pos + 1, n, 1));
            ga = GCD(i, pos, 1);
            gb = GCD(i, pos, 0);
            fa = x[0][pos + 1];
            fb = x[1][pos + 1];
            int L = pos, R = n;
            int np = pos;
            auto check = [&](int p)
            { return GCD(i, p, 1) == ga &&
                     GCD(i, p, 0) == gb &&
                     x[0][p + 1] == fa &&
                     x[1][p + 1] == fb; };
            while (L <= R)
            {
                int mid = L + R >> 1;
                if (check(mid))
                    L = (np = mid) + 1;
                else
                    R = mid - 1;
            }
            int ta = gcd(gcd(y[0][i - 1], ga), fa);
            int tb = gcd(gcd(y[1][i - 1], gb), fb);
            // cout << i << " " << np << " " << n << endl;
            // cout << ta << " " << tb << endl;
            if (ta + tb > ans)
                ans = ta + tb, sum = 0;
            if (ta + tb == ans)
                sum += np - pos + 1;
            pos = np + 1;
        }
    }
    write(ans, ' ');
    write(sum, '\n');
    // write(s.size(), '\n');
}
int main()
{
    int t;
    read(t);
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：xyvsvg (赞：0)

提供一种简单做法。

我们倒着考虑 $l$，显然区间 $\gcd$ 至多变化 $O(log V)$ 次，因此四元组 
$$(\gcd(a_l,a_{l+1},...,a_r),\ \gcd(a_{r+1},...,a_n),\ \gcd(b_l,b_{l+1},...,b_r),\ \gcd(b_{r+1},...,b_n))$$ 
也至多 $O(\log V)$ 个。

不妨直接用 ```map``` 维护不同的段的个数（显然我们只关心 $\gcd$，而不关心具体值），倒序扫描的同时记录答案即可。

答案也可以直接用 ```map``` 维护，非常方便。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
typedef long long ll;
void solve()
{
    int n;
    cin>>n;
    vector<int>a(n+10),b(n+10);
    vector<int>pa(n+10),pb(n+10);
    vector<int>sa(n+10),sb(n+10);
    for(int i=1;i<=n;++i)
        cin>>a[i],pa[i]=gcd(pa[i-1],a[i]);
    for(int i=1;i<=n;++i)
        cin>>b[i],pb[i]=gcd(pb[i-1],b[i]);
    map<P,ll>mp;
    map<int,ll>ans;
    for(int l=n;l;--l)
    {
        sa[l]=gcd(sa[l+1],a[l]);
        sb[l]=gcd(sb[l+1],b[l]);
        map<P,ll>nxt;
        for(auto[p,d]:mp)
        {
            auto[x,y]=p;
            nxt[{gcd(x,a[l]),gcd(y,b[l])}]+=d;
        }
        swap(nxt,mp);
        ++mp[{gcd(a[l],sb[l+1]),gcd(b[l],sa[l+1])}];
        for(auto[p,d]:mp)
        {
            auto[x,y]=p;
            ans[gcd(pa[l-1],y)+gcd(pb[l-1],x)]+=d;
        }
    }
    cout<<ans.rbegin()->first<<' '<<ans.rbegin()->second<<endl;
}
signed main()
{
    int t;
    cin>>t;
    while(t--)
        solve();
    return 0;
}

```

---

## 作者：喵仔牛奶 (赞：0)

## Solution

可能比较简单的写法。

令 $f(a,l,r)$ 为 $a_l,a_{l+1},\cdots,a_r$ 的 $\gcd$，$l>r$ 则为 $0$。

倒序枚举 $l$，可以发现对于所有 $r$，四元组 $(f(a,l,r),f(a,r+1,n),f(b,l,r),f(b,r+1,n))$ 只有 $\mathcal O(\log V)$ 种。使用 map 维护所有可能的四元组及其个数即可。

复杂度 $\mathcal O(n\log^2V)$。

## Code

```cpp
#include <bits/stdc++.h>
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
	const int N = 2e5 + 5;
	struct node {
		int A1, A2, B1, B2;
		node mdf(int x, int y) const { return {__gcd(A1, x), A2, __gcd(B1, y), B2}; }
		int calc(int x, int y) const { return __gcd(x, __gcd(B1, A2)) + __gcd(y, __gcd(A1, B2)); }
		bool operator < (node x) const {
			return make_tuple(A1, A2, B1, B2) < make_tuple(x.A1, x.A2, x.B1, x.B2);
		}
	};
	int n, rs, a[N], b[N], pr1[N], pr2[N]; LL ct; map<node, int> s;
	void upd(int x, int y) {
		if (rs < x) rs = x, ct = 0;
		if (rs == x) ct += y;
	}
	int main() {
		cin >> n, rs = 0, s.clear();
		REP(i, 1, n) cin >> a[i], pr1[i] = __gcd(pr1[i - 1], a[i]);
		REP(i, 1, n) cin >> b[i], pr2[i] = __gcd(pr2[i - 1], b[i]);
		int sf1 = 0, sf2 = 0;
		DEP(i, n, 1) {
			map<node, int> t;
			for (auto [x, y] : s)
				t[x.mdf(a[i], b[i])] += y;
			t[{a[i], sf1, b[i], sf2}] ++;
			for (auto [x, y] : t)
				upd(x.calc(pr1[i - 1], pr2[i - 1]), y);
			s.swap(t), sf1 = __gcd(sf1, a[i]), sf2 = __gcd(sf2, b[i]);
		}
		cout << rs << ' ' << ct << '\n';
		return 0;
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	int T = 1; cin >> T;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：huangleyi0129 (赞：0)

有如下经典结论：设 $g_i$ 为 $a_i$ 的前/后缀 $\gcd$ ，则 $g_i$ 的取值只有 $O(\log V)$ 种。

考虑 $l$ 从右向左做扫描线。

设：

$ga_i=\gcd(a_l,\cdots,a_i),gb_i=\gcd(b_l,\cdots,b_i)$

$fa_i=\gcd(a_{i+1},\cdots,a_n),fb_i=\gcd(b_{i+1},\cdots,b_n)$

动态维护 $ga_i,gb_i$ 和本质不同的数对 $(ga_i,gb_i,fa_i,fb_i)$。

显然只有 $O(\log V)$ 对。

且是一个不断单点删除，前缀加数的过程。

使用链表维护，时间复杂度 $O(n\log^2V)$。

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int a[N],b[N],R[N],qa[N],qb[N],ga[N],fa[N],gb[N],fb[N],n,ans;
long long cnt;
void solve()
{
	ans=cnt=0;
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i],qa[i]=__gcd(qa[i-1],a[i]),ga[i]=gb[i]=0,R[i]=i+1;
	for(int i=1;i<=n;++i)
		cin>>b[i],qb[i]=__gcd(qb[i-1],b[i]);
	int it,pre,u;
	a[n+1]=b[n+1]=fa[n+1]=fb[n+1]=0;
	for(int i=n;i>=1;--i)
	{
		it=i;
		fa[i]=__gcd(fa[i+1],a[i+1]),fb[i]=__gcd(fb[i+1],b[i+1]);
		while(it<=n)
			ga[it]=__gcd(ga[it],a[i]),gb[it]=__gcd(gb[it],b[i]),it=R[it];
		it=i+1,pre=i;
		while(it<n)
		{
			if(ga[it]==ga[R[it]]&&gb[it]==gb[R[it]]&&fa[it]==fa[R[it]]&&fb[it]==fb[R[it]])
				R[pre]=R[it],it=pre;
			pre=it,it=R[it];
		}
		pre=i-1,it=i;
		while(it<=n)
		{
			u=__gcd(qa[i-1],__gcd(gb[it],fa[it]))+__gcd(qb[i-1],__gcd(ga[it],fb[it]));
			if(u>ans)
				ans=u,cnt=it-pre;
			else if(u==ans)
				cnt+=it-pre;
			pre=it,it=R[it];
		}
	}
	cout<<ans<<' '<<cnt<<'\n';
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：beauty_son_whm (赞：0)

令 $M$ 为序列 $a$ 和 $b$ 中的最大值。

#### 先找到答案的最大值
###### 

定义 $p_i$ 和 $q_i$ 分别为 序列 $a$ 和 $b$ 的前缀 $\gcd$，$r_i$ 和 $z_i$ 为序列 $a$ 和 $b$ 的后缀 $\gcd$，对于所有的 $i>1$，我们有 $p_i=p_{i-1}$ 或者 $p_i\leq p_{i-1}/2,(\ p_{i-1}\ | \ p_i\ )$，所以说，我们最多有 $\log_2M$ 种不同的 $p_i$，$q_i$ 也是相同情况，后缀的情况和前缀相同。

不妨设我们当前选择的区间为 $[l,r]$，$a_{l\sim r},b_{l\sim r}$ 的最小公约数分别为 $X,Y$，则答案为 $\gcd(p_{l-1},Y,r_{r+1})+\gcd(q_{l-1},X,z_{r+1})$。若此时 $p_{l-1}=p_l,q_{l-1}=q_l$，那么选择区间 $[l+1,r]$ 更加优秀，因为 $X,Y$ 都会变为原来自己的倍数，其他部分不变，答案会更大，上面已经证明不同的 $p_i,q_i$ 有 $O(\log_2M)$ 种，那么我们就存在一种 $O(n\log^2M)$ 的做法，枚举一个右端点 $r$，枚举前面的不同的左端点，找到最大值。

#### 再对答案计数
###### 

我们先对所有的 $l>1,r<n$ 进行计数，令 $ca=\gcd(p_{l-1},Y,r_{r+1}),cb=\gcd(q_{l-1},X,z_{r+1})$。易知 $ca,cb$ 分别为 $a_1,b_1$ 的约数。那么我们就可以枚举 $ca$，再用 $ans-ca$ 得出 $cb$，这样的复杂度是 $O(\sqrt M)$。然后可以 $dp_{i,0/1/2}$，表示当前我考虑了前 $i$ 个数，$0/1/2$ 分别表示：当前没有选择左端点，选择了左端点没有选择右端点，左右端点都选择了。转移的时候只需要考虑当前你放在 $a$ 或 $b$ 的数 $X$ 是否把 $ca$ 或 $cb$ 整除即可。不用担心得出的答案会比我们得出的答案大，因为这样就不满足答案的最大性了。时间复杂度为 $O(nM^{1/3}+T\sqrt M +n\log^2M)$，其中 $M^{1/3}$ 表示一个数的因数个数。时间复杂度爆炸了，我们考虑分治，若 $n<100$ 直接 $n^2 \log M$ 暴力。若 $n\geq100$，再用上述方法。


# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define pc putchar
#define ll long long
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48),ch=getchar();}
    return x*f;
}
int n;
inline void work(){
    n=read();
    vector<int>a(n+5);
    vector<int>b(n+5);
    vector<int>prea(n+5);
    vector<int>preb(n+5);
    vector<int>nxta(n+5);
    vector<int>nxtb(n+5);
    for(int i=1;i<=n;i++) a[i]=read(),prea[i]=__gcd(a[i],prea[i-1]);
    for(int i=n;i>=1;i--) nxta[i]=__gcd(a[i],nxta[i+1]); 
    for(int i=1;i<=n;i++){
    	b[i]=read();
		preb[i]=__gcd(b[i],preb[i-1]);
	}
    for(int i=n;i>=1;i--) nxtb[i]=__gcd(b[i],nxtb[i+1]);
    if(n<=100){
        int ans=0,tot=0;
        for(int i=1;i<=n;i++){
            int now1=0,now2=0;
            for(int j=i;j<=n;j++){
                now1=__gcd(now1,a[j]);
                now2=__gcd(now2,b[j]);
                int ret=__gcd(now1,__gcd(preb[i-1],nxtb[j+1]))+__gcd(now2,__gcd(prea[i-1],nxta[j+1]));
                if(ans<ret){
                    ans=ret,tot=1;
                }
                else if(ans==ret) tot++;
            }
        }
        cout<<ans<<" "<<tot<<endl;
    }
    else{
        int ans=0;
        ll tot=0;
        {
            vector<int>v1;
            for(int i=1;i<=n;i++){
                if(!(preb[i]==preb[i-1]&&prea[i]==prea[i-1])) v1.push_back(i);
            }
            for(int l:v1){
                int now1=0,now2=0;
                for(int r=l;r<=n;r++){
                    now1=__gcd(now1,a[r]);
                    now2=__gcd(now2,b[r]);
                    ans=max(ans,__gcd(prea[l-1],__gcd(now2,nxta[r+1]))+__gcd(preb[l-1],__gcd(now1,nxtb[r+1])));
                }
            }
        }
        {
            if(prea[n]+preb[n]==ans) tot++;
            for(int j=1;j<n;j++){
                if(__gcd(preb[j],nxta[j+1])+__gcd(prea[j],nxtb[j+1])==ans) tot++;
            }
            for(int j=n;j>1;j--){
                if(__gcd(preb[j-1],nxta[j])+__gcd(prea[j-1],nxtb[j])==ans) tot++;
            }
        }
        {
            auto solve=[&](int ca,int cb)->ll{
                vector<array<ll,3>>dp(n+1);
                dp[0][0]=1;
                for(int i=0;i<n;i++){
                    bool flag=1;
                    if(a[i+1]%ca) flag=0;
                    if(b[i+1]%cb) flag=0;
                    if(flag){
                        dp[i+1][0]+=dp[i][0];
                        dp[i+1][2]+=dp[i][2];
                    }
                    flag=1;
                    if(a[i+1]%cb) flag=0;
                    if(b[i+1]%ca) flag=0;
                    if(flag&&i+1>1&&i+1<n){
                        dp[i+1][1]+=dp[i][0];
                        dp[i+1][1]+=dp[i][1];
                        dp[i+1][2]+=dp[i][1];
                        dp[i+1][2]+=dp[i][0];
                    }
                }
                return dp[n][2];
            };
            for(int ca=1;ca*ca<=a[1];ca++){
                if(a[1]%ca) continue;
                if(ca<ans&&b[1]%(ans-ca)==0) tot+=solve(ca,ans-ca);
                if(ca*ca==ans) continue;
                if(a[1]/ca<ans&&b[1]%(ans-a[1]/ca)==0) tot+=solve(a[1]/ca,ans-a[1]/ca);
            }
        }
        cout<<ans<<" "<<tot<<endl;
    }
    return ;
}
signed main(){
    int T=read();
    while(T--){
        work();
    }
    system("pause");
    return 0;
}
```

---


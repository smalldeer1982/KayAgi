# Divide OR Conquer

## 题目描述

给定一个由 $[a_1, a_2, \ldots, a_n]$ 组成的数组，其中每个元素都是 $0$ 到 $10^9$ 之间的整数。你需要将该数组划分为若干个连续的段（也可以只划分为一个段），使得每个元素恰好属于一个段。

设第一个段为 $[a_{l_1}, a_{l_1 + 1}, \ldots, a_{r_1}]$，第二个段为 $[a_{l_2}, a_{l_2+ 1}, \ldots, a_{r_2}]$，……，最后一个段为 $[a_{l_k}, a_{l_k+ 1}, \ldots, a_{r_k}]$。由于每个元素都应恰好属于一个段，所以 $l_1 = 1$，$r_k = n$，并且对于每个 $i$（$1 \le i \le k-1$），都有 $r_i + 1 = l_{i+1}$。划分还需满足以下条件：$f([a_{l_1}, a_{l_1 + 1}, \ldots, a_{r_1}]) \le f([a_{l_2}, a_{l_2+ 1}, \ldots, a_{r_2}]) \le \dots \le f([a_{l_k}, a_{l_k+1}, \ldots, a_{r_k}])$，其中 $f(a)$ 表示数组 $a$ 所有元素的按位或（bitwise OR）。

请计算有多少种不同的划分方式，并输出对 $998\,244\,353$ 取模的结果。如果两个划分方式对应的 $[l_1, r_1, l_2, r_2, \ldots, l_k, r_k]$ 序列不同，则认为它们是不同的划分方式。

## 说明/提示

在前两个样例中，任何一种划分方式都是合法的。

在第三个样例中，有三种合法的划分方式：

- $k = 3$；$l_1 = 1, r_1 = 1, l_2 = 2, r_2 = 2, l_3 = 3, r_3 = 3$；得到的数组为 $[3]$、$[4]$、$[6]$，且 $3 \le 4 \le 6$；
- $k = 2$；$l_1 = 1, r_1 = 1, l_2 = 2, r_2 = 3$；得到的数组为 $[3]$ 和 $[4, 6]$，且 $3 \le 6$；
- $k = 1$；$l_1 = 1, r_1 = 3$；只有一个数组 $[3, 4, 6]$。

如果将数组划分为 $[3, 4]$ 和 $[6]$，则第一个数组的按位或为 $7$，第二个数组的按位或为 $6$，$7 > 6$，因此这种划分方式不合法。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
5
1000 1000 1000 1000 1000```

### 输出

```
16```

## 样例 #3

### 输入

```
3
3 4 6```

### 输出

```
3```

# 题解

## 作者：xyvsvg (赞：5)

提供一种实现非常简单的做法：

注意到如果序列一个端点固定，那么另一端点移动造成的区间 $\operatorname{OR}$ 的变化最多 $O(\log V)$ 次。

考虑使用 dp 求解，不难想到设 $f_{i,S}$ 表示以 $i$ 为右端点，且最后一段区间 $\operatorname{OR}$ 为 $S$ 的方案数。

于是我们直接使用 ```map``` 维护已有的合法区间（因为已有的区间 $\operatorname{OR}$ 上当前的数不会影响合法性），如何新加区间呢？我们可能会选择二分下一个端点，不过二分还是太难写了（况且可能还需要 ST 表）。我们不妨直接维护不合法的区间（显然也只有 $O(\log V)$ 个），每次转移时顺便把当前已经成为合法区间的维护一下即可。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
const int mod=998244353;
struct mint
{
    int x=0;
    mint operator+=(const mint&o)
    {
        x+=o.x;
        if(x>=mod)
            x-=mod;
        return *this;
    }
};
signed main()
{
    int n;
    cin>>n;
    map<int,mint>dp;
    map<P,mint>wt;
    dp[0].x=1;
    for(int i=1;i<=n;++i)
    {
        int x;
        cin>>x;
        map<int,mint>nxt;
        map<P,mint>wait;
        for(auto[p,d]:wt)
        {
            auto[a,b]=p;
            b|=x;
            if(a<=b)
                nxt[b]+=d;
            else
                wait[{a,b}]+=d;
        }
        for(auto[p,d]:dp)
            nxt[p|x]+=d;
        for(auto[p,d]:nxt)
            wait[{p,0}]+=d;
        swap(dp,nxt);
        swap(wt,wait);
    }
    cout<<accumulate(dp.begin(),dp.end(),mint(),[&](mint d,const pair<int,mint>&p){return d+=p.second;}).x;
    return 0;
}

```

---

## 作者：ifffer_2137 (赞：1)

典的不能再典的题。
### 题意
序列划分成若干子段使得子段按位或不降，求方案数。
### 分析
考虑暴力，设 $dp_{i,j}$ 表示到第 $i$ 个数，最后一段左端点为 $j$ 的方案数，暴力枚举最后一段转移，复杂度 $O(n^2)$。

我们希望优化这个东西，考察按位或的性质，容易发现在固定右端点扩展左端点的时候按位或的变化次数是 $O(\log V)$ 的，原因是每一个 bit 只会被修改至多一次。所以我们不妨对于每一个右端点，将向左按位或变化的位置存下来，对没变的区间一起考虑，这样状态数只有 $O(n\log V)$ 了。而找到这些变化的位置，二分套 ST 表即可，时间两 log。

然后考虑转移，我们每次是从一个区间转移过来，要求最后一段小于等于我们当前的状态，是朴素的二维数点，先把所有子段按位或的值离散化，再提前把询问差分挂上去，扫描线转移的时候 BIT 维护即可，时间复杂度 $O(n\log n\log V)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
#define mkpr make_pair
#define x first
#define y second
#define popcnt __builtin_popcountll
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=0;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
	return w?x:-x;
}
template<class T1,class T2>inline bool Cmn(T1 &x,T2 y){if(y<x)return x=y,1;return 0;}
template<class T1,class T2>inline bool Cmx(T1 &x,T2 y){if(y>x)return x=y,1;return 0;}
template<class T>inline void Dbg(T *a,int l,int r){for(int i=l;i<=r;i++)cout<<a[i]<<' ';cout<<'\n';}
mt19937 rnd(time(NULL));
constexpr int inf=0x3f3f3f3f;
constexpr int maxn=2e5+5;
constexpr int maxm=5e3+5;
constexpr int mod=998244353;
constexpr int base=2137;
constexpr int V=1e9;
constexpr int H=18;
constexpr int W=31;
constexpr int Z=26;
constexpr double eps=1e-9;
inline int Redu(int x){return x-(x>=mod)*mod;}
inline void Add(int &x,int y){x=x+y-(x+y>=mod)*mod;}
inline void _Add(int &x,ll y){x=(x+y)%mod;}
inline void Del(int &x,int y){x=x-y+(x-y<0)*mod;}
inline void _Del(int &x,ll y){x=(x-y)%mod;x+=(x<0)*mod;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int Pow(int a,int x){int s=1;for(;x;x>>=1,a=1ll*a*a%mod)if(x&1)s=1ll*s*a%mod;return s;}
bool Mem1;
class Sparse_Table{
private:
	int lg[maxn];
	int f[maxn][H];
public:
	void init(int n,const int *a){
		for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
		for(int i=1;i<=n;i++) f[i][0]=a[i];
		for(int j=1;j<H;j++) for(int i=1;i+(1<<j)-1<=n;i++) f[i][j]=f[i][j-1]|f[i+(1<<(j-1))][j-1];
	}
	int query(int l,int r){
		int s=lg[r-l+1];
		return f[l][s]|f[r-(1<<s)+1][s];
	}
}st;
class Fenwick_Tree{
private:
	int n,c[maxn*W];
public:
	void init(int x){n=x;}
	void add(int x,int k){for(;x<=n;x+=x&-x)Add(c[x],k);}
	ll qry(int x){ll s=0;for(;x;x-=x&-x)s+=c[x];return s;}
}tr;
int n;ll ans;
int a[maxn];
int pos[maxn][W],val[maxn][W];
int dp[maxn][W];
int t[maxn*W],tt;
struct ask{
	int i,j,op,k;
	ask(){}
	ask(int I,int J,int O,int K){i=I,j=J,op=O,k=K;}
};
vector<ask> Aq[maxn];
void Init(){}
void Clear(){}
void Mymain(){
	Clear();
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	st.init(n,a);
	for(int i=1;i<=n;i++){
		pos[i][0]=i,t[++tt]=val[i][0]=a[i];
		for(int j=1,cur=a[i];pos[i][j-1]>1;j++){
			int l=1,r=pos[i][j-1]-1;
			while(l<=r){
				int mid=(l+r)>>1;
				if(st.query(mid,i)>cur) pos[i][j]=mid,l=mid+1;
				else r=mid-1;
			}
			cur=st.query(pos[i][j],i);
			t[++tt]=val[i][j]=cur;
		}
	}
	sort(t+1,t+tt+1),tt=unique(t+1,t+tt+1)-t-1;
	for(int i=1;i<=n;i++) for(int j=0;j<W;j++) if(pos[i][j]) val[i][j]=lower_bound(t+1,t+tt+1,val[i][j])-t;
	for(int i=1;i<=n;i++){
		for(int j=0;j<W-1;j++){
			int l=pos[i][j+1],r=pos[i][j];
			if(l>=r) continue;
			if(l) Aq[l-1].push_back(ask(i,j,0,val[i][j]));
			if(r) Aq[r-1].push_back(ask(i,j,1,val[i][j]));
		}
	}
	tr.init(tt),tr.add(1,1);
	for(ask q:Aq[0]){
		if(q.op) Add(dp[q.i][q.j],1);
		else Del(dp[q.i][q.j],1);
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<W-1;j++){
			if(!pos[i][j]) continue;
			tr.add(val[i][j],dp[i][j]);
		}
		for(ask q:Aq[i]){
			if(q.op) _Add(dp[q.i][q.j],tr.qry(q.k));
			else _Del(dp[q.i][q.j],tr.qry(q.k));
		}
	}
	for(int i=0;i<W;i++) ans+=dp[n][i];
	cout<<ans%mod<<'\n';
}
bool Mem2;
signed main(){
	#ifdef LOCAL
	assert(freopen("data.in","r",stdin));
	assert(freopen("test.out","w",stdout));
	#endif
	cin.tie(0),cout.tie(0);
	Init();int _=1;
	while(_--) Mymain();
	// cerr<<"Time: "<<1000.0*clock()/CLOCKS_PER_SEC<<" ms\n";
	// cerr<<"Memory: "<<(&Mem1-&Mem2)/1024.0/1024.0<<" MB\n";
	return 0;
}
```

---

## 作者：OrinLoong (赞：1)

首先有一个 $O(N^2V)$ 的 dp：设 $dp_{i,s}$ 为考虑前 $i$ 个元素，最后一段或和为 $s$ 的方案数。转移为 $dp_{i,s}=\sum_{t=0}^s dp_{j,t}$。显然 $s$ 的取值只有 $i$ 种，并且这个求和可以用树状数组优化，使总复杂度降至 $O(N^2\log V)$。  
这样设状态无法进一步优化。此时我们要上一个关键引理：  
> 一个序列的所有前/后缀中，或和互不相同的前/后缀最多只有 $\log V$ 个。  
> 正确性显然：前/后缀扩展时，或和仅可能发生一类变化——若干位上的 $0$ 变成 $1$。这一过程最多进行 $\log V$ 次，因此或和最多产生 $\log V$ 种。

由此，我们发现只有 $N\log V$ 次转移是不同的。记区间 $[l,r]$ 的或和为 $ors(l,r)$，于是我们将可以一起转移的状态合起来记为 $seg_{s,l,r}$，表示 $\forall i\in [l,r],ors(s,i)=ors(s,l)$。这里我们可以用 ST 表加二分的方法在 $O(N\log V\log N)$ 的时间复杂度内处理出这些 $seg$。（具体来说，外层循环 $s$，内层使用双指针记录当前的 $l$，用二分找对应的 $r$。  
我们将这些 $seg$ 按照其或和 $ors(s,l)$ 为第一关键字，$s$ 为第二关键字排序。对于每一个 $seg$，我们执行 $\forall i\in [l,r],dp_i+=dp_s$——由于排序后或和、位置的顺序，能转移到当前状态的 dp 值在当前是不重不漏出现的，因此我们的 dp 只用记录位置维了。初始化 $dp_0=1$。不难看出这是一个区间转移，所以我们写个区间加树状数组维护 dp 数组。总时间复杂度 $O(N\log N\log V)$。  
代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long lolo;
const int MaxN=2e5+5,Mod=998244353;
int N,A[MaxN],lg2[MaxN],scnt;
struct anob{int s,l,r,v;}S[MaxN<<5];
int cntzero(int x){
    int res=0;for(int i = 0;i < 30;i++)
    {res+=(x&(1<<i))^1;}return res;
}
void muladd(int &x,int y,int p){x+=y;if(x>=p)x-=p;}
void log_prework(int n){for(int i = 2;i <= n;i++)lg2[i]=lg2[i/2]+1;}
struct SpraseTable{
    int t[MaxN][18];
    void prework(int a[],int n){
        for(int i = 1;i <= n;i++)t[i][0]=a[i];
        for(int i = 1;i < 18;i++)for(int j = 1;j+(1<<i)-1<=n;j++)
        {t[j][i]=t[j][i-1]|t[j+(1<<(i-1))][i-1];}
    }
    int getres(int l,int r){
        int tmp=lg2[r-l+1];
        return t[l][tmp]|t[r-(1<<tmp)+1][tmp];
    }
}SprTb;
struct BinidTr{
    int t[MaxN];
    void init(int n){memset(t,0,sizeof(t));}
    int lowbit(int x){return x&(-x);}
    void add(int p,int x,int n){while(p<=n)muladd(t[p],x,Mod),p+=lowbit(p);}
    void addupd(int l,int r,int x,int n){add(l,x,n+1);add(r+1,Mod-x,n+1);}
    int gts(int p){int res=0;while(p){muladd(res,t[p],Mod),p-=lowbit(p);}return res;}
}BidTr;
int check(int s,int l,int r,int val){
    int mid,res;while(l<=r){
        mid=(l+r)>>1;(SprTb.getres(s,mid)==val)?
        (res=mid,l=mid+1):r=mid-1;
    }
    return res;
}
bool cmp(anob a,anob b){return a.v==b.v?a.s<b.s:a.v<b.v;}
int main(){
    scanf("%d",&N);
    for(int i = 1;i <= N;i++)scanf("%d",&A[i]);
    log_prework(N);SprTb.prework(A,N);
    for(int i=1,p,q,cur;i <= N;i++){
        p=i,cur=A[i];while(p<=N){
            cur|=A[p],q=check(i,p,N,cur);
            S[++scnt]={i,p,q,cur},p=q+1;
        }
    }
    sort(S+1,S+scnt+1,cmp);
    for(int i = 1;i <= scnt;i++){
        auto [cs,cl,cr,cv]=S[i];
        BidTr.addupd(cl,cr,cs==1?1:BidTr.gts(cs-1),N);
    }
    printf("%d",BidTr.gts(N));
    return 0;
}
```
fun fact：实际上你把 $l$ 作为第二关键字排序也是能过的。

---

## 作者：LittleDrinks (赞：1)

## [D. Divide OR Conquer](https://codeforces.com/problemset/problem/2038/D)

先有两个观察。

第一，本题需要完成一种分组的工作，因此初步的想法是套用分组 DP 的方程。记 $dp(i,x)$ 表示对区间 $[1,i]$ 进行分组，并且最后一组恰好为 $x$ 的分组方案。

第二，$\mathbin{\rm{OR}}$ 操作后的结果具有单调性，且从任意位置向前、向后最多只有 $\log_210^9$ 种取值，因此，上述 $dp(i,x)$ 的状态数其实是有限的。

然后考虑状态如何转移。

如果继续套用分组 DP 的想法，我们会希望枚举上一组的终点 $j$，此时有状态转移方程：

$$dp(i,x)=\displaystyle\sum_{j=1}^{i-1}\sum_{y=0}^{x}dp(i,y)$$

这时我们会发现一件难搞的事情，对于每个 $j$，它向前都可能有 $\log_210^9$ 个不同的 $y$ 的取值，暴力转移单次的复杂度是 $O(n)$，并且合并操作比较艰难。（听说可以用主席树实现，但会 MLE，我太菜了不知道这里有没有靠谱的实现方法）

于是，这种每次即时从前方进行 pull 型的转移宣告倒闭了，最主要的原因是我们需要同时利用倒数两个区间的 $\rm{OR}$ 值才能进行转移。从这点出发进行修改，我们可以将 pull 型的转移转为 push 型的转移。

具体而言，假设我们已经获取了位置 $i$ 的方案数 $dp(i,x)$，以这个 $\rm{OR}$ 值为 $x$ 的区间 $[k,i]$ 作为倒数第二个区间，向后枚举最后一个 $\rm{OR}$ 值为 $y$ 的区间 $[i+1,r]$。此时我们容易写出状态转移方程：

$$dp(r,y)\overset{+}{\leftarrow} \sum_{x\leq y}dp(i,x)$$

记 $(r_j,x_j)$ 表示区间 $\rm{OR}$ 值为 $x_j$ 的、右端点最小的区间为 $[i+1,r_j]$。对 $x$ 升序排序。不难发现，区间 $[r_j,r_{j+1})$ 的更新方式是相同的。这一部分可以用差分数组实现，因为这个差分数组上有若干个 $x$ 的取值，也可以理解为一根扫描线从左往右扫。

![](https://cdn.luogu.com.cn/upload/image_hosting/je8nhp5f.png)

提供一种我的实现方法，用 st 表求区间 $\rm{OR}$ 值，用 `map<int,int>` 实现扫描线 $dp$ 和差分数组 $d[N]$。初始时 $d[0][0]=1$，$d[1][0]=-1$，从 $i=0$ 开始，每个位置使用一个指针维护 $s$ 的值，向后二分找到 $(r_j,x_j)$，更新 $d[r[j]][x[j]]$ 和 $d[r[j+1]][x[j+1]]$，扫描线移到最右侧时，扫描线上所有值加和即为答案。

#### [AC 代码](https://codeforces.com/contest/2038/submission/292439503)

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N=2e5+5, I=20, MOD=998244353;
int n;
map <int,int> s, d[N];

void add(int &x, int y)
{
    x = (x + y) % MOD;
}

struct ST {
    int st[N][I+5], Log[N];
    void init() {
        for (int i = 1; i <= n; ++i) { cin >> st[i][0]; }
        Log[1] = 0;
        for (int i = 2; i <= n+1; ++i) { Log[i] = Log[i/2] + 1; }
        for (int i = 1; i <= I; ++i) { 
            for (int j = 0; j+(1<<(i-1)) <= n; ++j) {
                st[j][i] = st[j][i-1] | st[j+(1<<(i-1))][i-1];
            }
        }
    }
    int query(int L, int R) {
        int s = Log[R-L+1];
        return st[L][s] | st[R-(1<<s)+1][s];
    }
} st;

int nxt(int L, int p)
{
    int x = st.query(L, p);
    int ll=p, rr=n+1, mid;
    while (ll != rr-1) {
        mid = (ll + rr) >> 1;
        if (st.query(L, mid) > x) { rr = mid; }
        else                      { ll = mid; }
    }
    return rr;
}

int main()
{
    cin >> n; st.init();
    s[0] = 1;
    d[1][0] = -1;
    for (int i = 0; i <= n; ++i) {
        // 更新前缀和
        for (auto [x, v]: d[i]) {
            add(s[x], v);
        }
        // 删除值为0的节点，节约空间
        for (auto it=s.begin(); it!=s.end();) {
            if (it->second == 0) { it=s.erase(it); }
            else                 { ++it; }
        }
        // 向后更新差分数组
        int r = i+1;
        int lx=-1, ls=-1, sv=0;
        auto it=s.begin();
        while (r <= n) {
            int x = st.query(i+1, r);
            while (it!=s.end() && it->first <= x) { add(sv, it->second); ++it; }
            add(d[r][x], sv);
            if (lx != -1) {
                add(d[r][lx], MOD-ls);
            }
            lx=x; ls=sv;
            r = nxt(i+1, r);
        }
    }
    int ans=0;
    for (auto [x, v]: s) { add(ans, v); }
    cout << ans << endl;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

给定一个长度为 $n$ 的序列 $a$，你需要将其分成任意段，使得每一段的按位或的结果不降，求方案数。答案对 $998,244,353$ 取模。

$1\leq n\leq 2\times 10^5,0\leq a_i\leq 10^9$。

## 思路

什么神奇 dp 题。下文中，$V$ 均指值域。

首先有一个比较显然的 dp，设 $f(i,s)$ 表示考虑到前缀 $[1,i]$，最后一段的按位或的结果为 $s$ 的方案数，时间复杂度高达 $O(n^2V)$ 难以接受，稍加优化（应该）可以做到 $O(n^2\log V)$ 同样难以接受。然后你可以发现这个 dp 优化已经到瓶颈了，难以继续优化。

考虑转换 dp 顺序，原本我们的顺序是先 $i$ 再 $s$，这样子很不好，改为先 $s$ 再 $i$，于是我们可以将所有段存起来，计算出它们的按位或的结果，将所有段按照按位或为第一关键字，左端点为第二关键字，右端点为第三关键字排序。可以发现此时转移非常简单，就是 $f_r\leftarrow f_r+f_{l-1}$。时间复杂度 $O(n^2\log n)$ 难以接受。

上一个关键引理：

> 一个序列的所有前缀中，按位或结果互不相同的前缀最多只有 $O(\log V)$ 个。

证明也很简单，因为相邻的互不相同的按位或结果最多多一个二进制位。另外提一句，按位与和 $\gcd$ 也有类似的性质，可以尝试做一下 [2024 ICPC 昆明邀请赛 E. 学而时习之](https://codeforces.com/gym/105386/problem/E)。

于是我们可以将枚举的段缩减到 $O(n\log V)$ 个，不过这样贡献的 $f_r$ 就从单点变成了区间，可以找一个支持区间加单点查询的数据结构维护（比如树状数组）即可。

时间复杂度 $O(n\log n\log V)$。

## 代码

轻微卡常。

```cpp
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
using namespace std;

constexpr int mod = 998244353;
int Add(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int Sub(int x, int y){ return (x - y) < 0 ? (x - y + mod) : (x - y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }

const int N = 2e5 + 5;
int n, a[N];

struct node{
    int l, r;
    mutable int v;
    node(int _l, int _r, int _v) : l(_l), r(_r), v(_v) {}
    bool operator<(const node &rhs) const {
        return l == rhs.l ? r < rhs.r : l < rhs.l;
    }
};

set<node> st;
vector<node> vct;

struct kcr{
    int p, l, r, v;
    kcr(int _p, int _l, int _r, int _v) : p(_p), l(_l), r(_r), v(_v) {}
    bool operator<(const kcr &rhs) const {
        return (v == rhs.v) ? p < rhs.p : v < rhs.v;
    }
};

vector<kcr> rgs;

int t[N];

void update(int p, int v){
    while(p <= n) t[p] = Add(t[p], v), p += lowbit(p);
}

int query(int p){
    int ans = 0;
    while(p) ans = Add(ans, t[p]), p -= lowbit(p);
    return ans;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=n;i;i--){
        st.emplace(i, i, a[i]), vct.clear();
        for(auto& [l, r, v] : st) v |= a[i];
        for(auto [l, r, v] : st) vct.emplace_back(l, r, v);
        st.clear();
        for(size_t j=1;j<vct.size();j++){
            if(vct[j].v == vct[j - 1].v) vct[j].l = vct[j - 1].l, vct[j - 1].r = -1;
        }
        for(auto [l, r, v] : vct){
            if(~r) st.emplace(l, r, v), rgs.emplace_back(i, l, r, v);
        }
    }
    sort(rgs.begin(), rgs.end());
    for(auto& [p, l, r, v] : rgs){
        int f = (p == 1) ? 1 : query(p - 1);
        update(l, f), update(r + 1, mod - f);
    }
    cout << query(n) << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：TTpandaS (赞：0)

前缀 or 只会变化至多 $\log V$ 次。所以对于每个 $i$ 都可以快速找到所有转折点 $j$，那么就可以令 $ f_{i,x}$ 表示前 $i$ 个数分段，在 $i$ 截止，最后一段值为 $x$ 的方案数。用主席树加权值线段树维护，但是他把空间卡了。所以考虑记下这一段与上一段的状态动态填，这样的话分界点最多 $2\log$ 个，就可以暴力转移了。

代码里面把主席树写法也放上了，读者可以试试卡卡空间。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,mod=998244353;
int T=1;
int n,a[N];
int st[N][20],Log[N];
int ans;
int askor(int l,int r){
	if(l>r){
		return 0;
	}
	int k=Log[r-l+1];
	return st[l][k]|st[r-(1<<k)+1][k];
}
/*
struct tree{
	int lc,rc;
	int sum;
}t[N*210];
int num,root[N];
int newnode(int p){
	num++;
	t[num]=t[p];
	return num;
}
void pushup(int p){
	t[p].sum=(0ll+t[t[p].lc].sum+t[t[p].rc].sum)%mod;
}
void add(int &p,int l,int r,int x,int y){
	p=newnode(p);
	if(l==r){
		t[p].sum=(0ll+t[p].sum+y)%mod;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid){
		add(t[p].lc,l,mid,x,y);
	}
	else{
		add(t[p].rc,mid+1,r,x,y);
	}
	pushup(p);
}
int ask(int p1,int p2,int l,int r,int L,int R){
	if(!p2){
		return 0;
	}
	if(L<=l&&r<=R){
		return (0ll+t[p2].sum-t[p1].sum+mod)%mod;
	}
	int mid=(l+r)>>1,res=0;
	if(L<=mid){
		res=(0ll+res+ask(t[p1].lc,t[p2].lc,l,mid,L,R))%mod;
	}
	if(mid+1<=R){
		res=(0ll+res+ask(t[p1].rc,t[p2].rc,mid+1,r,L,R))%mod;
	}
	return res;
}
*/
map<pair<int,int>,int> dp,DP;
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		st[i][0]=a[i];
	}
	for(int i=2;i<=n;i++){
		Log[i]=Log[i/2]+1;
	}
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j]=st[i][j-1]|st[i+(1<<j-1)][j-1];
		}
	}
	/*
	add(root[1],0,(1<<30)-1,0,1);
	for(int i=1;i<=n;i++){
		root[i+1]=root[i];
		int R=i+1;
		while(R>1){
			int tot=askor(R-1,i);
			int l=1,r=R-1,L=0;
			while(l<=r){
				int mid=(l+r)>>1;
				if(askor(mid,i)==tot){
					L=mid;
					r=mid-1;
				}
				else{
					l=mid+1;
				}
			}
			//[L,R-1]~i = tot
			int res=ask(root[max(0,L-1)],root[R-1],0,(1<<30)-1,0,tot);
//			cout<<i<<":["<<L<<','<<R-1<<"]"<<' '<<tot<<' '<<res<<endl;
			if(i==n){
				ans=(0ll+ans+res)%mod;
			}
			else{
				if(res){
					add(root[i+1],0,(1<<30)-1,tot,res);
				}
			}
			R=L;
		}
	}
	*/
    dp[{0,a[1]}]=1;
    for(int i=2;i<=n;i++){
        DP.clear();
        for(auto [it,tot]:dp){
            auto [lstval,val]=it;
            if(lstval<=val){
            	DP[{val,a[i]}]=(DP[{val,a[i]}]+tot)%mod;
				DP[{0,a[i]|val}]=(DP[{0,a[i]|val}]+tot)%mod;
			}
            else{
            	if(lstval>(val|a[i])){
            		DP[{lstval,val|a[i]}]=(DP[{lstval,val|a[i]}]+tot)%mod;
				}
            	else{
            		DP[{0,val|a[i]}]=(DP[{0,val|a[i]}]+tot)%mod;
				}
			}
        }
        dp.swap(DP);
    }
    for(auto [it,tot]:dp){
        if(it.first<=it.second){
        	ans=(ans+tot)%mod;
		}
    }
	cout<<ans<<'\n';
}
signed main(){
//	cin>>T;
	while(T--){
		solve(); 
	}
	return 0;
}
```

---

## 作者：_jimmywang_ (赞：0)

什么？你怎么知道我赛时被假做法硬控了两个小时无缘已经会了的 F 和 I？然后赛后观察小码量做法发现我是小丑？

---------------------

返璞归真。考虑 $dp[i]$ 为以 $i$ 结尾的方案数。但是这样的话从左往右转移时转移顺序是会出问题的，因为缺少上一段区间按位或和的信息，我们不知道往下转移会去哪。

那怎么办？答案是不从左往右转移了。

假设我们手里有一个包含所有区间 $[l,r]$ 以及这个区间的按位或和 $s$（用 $(l,r,s)$ 表示）的集合，利用这堆东西怎么转移呢？

按照 $s$ 为第一关键字， $l$ 为第二关键字，$r$,为第三关键字把这些东西排序，按照顺序转移 $dp_{l-1}+dp_{r}\to dp_{r}$ 即可（$dp_0=1$）。

这是为什么呢？因为区间衔接的先后关系只与**按位或和**还有**端点**决定，确定这个顺序后直接转移就是对的。

好的你发现这玩意 $O(n^2\log n)$，怎么办呢？

你发现对于一个 $l$，本质不同的 $s$ 只有 $O(\log n)$ 个，这是由于你的 $r$ 增大的过程中，$s$ 的每个二进制位最多变化一次。因此我们可以记录 $(s,i,l,r)$ 表示一段极长的 $[l,r]$，使得 $[i,l],[i,l+1],\dots,[i,r]$ 的区间按位或和都是 $s$。这样只有 $O(n\log n)$ 组，求法多样。

按照 $s$ 为第一关键字， $i$ 为第二关键字排序，转移的时候对每个 $x\in[l,r]$ 执行 $dp_{i-1}+dp_x\to dp_x$。你发现这是区间加，所以你写一棵树状数组就过去了。

总复杂度 $O(n\log^2 n)$。好玩。

我比较蠢，使用简单的 st 表 + 二分。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll int
#define f(i,a,b) for(ll i=a;i<=b;i++)
#define wt int tt=d;while(tt--)
#define py puts("Yes")
#define pn puts("No")
#define pritnf printf
#define edfl endl
#define fe(i,e) for(int i=0;i<e.size();i++)
#define vi vector<ll>
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d rd()
#define pb push_back
ll qp(ll a,ll b,ll p){
	ll ans=1;while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;b>>=1;
	}return ans;
}ll n,m;
ll a[200010];
ll st[200010][20];
ll lg[200010];
ll get(ll l,ll r){
	ll L=r-l+1,Lg=lg[L];
	return (st[l][Lg]|st[r-(1<<Lg)+1][Lg]);
}
vector<array<ll,4> > w;
const ll mod=998244353;
ll t[200010];
#define lb(x) (x&(-x))
void add(ll x,ll v){
	while(x<=n){(t[x]+=v)%=mod;x+=lb(x);}
}ll ask(ll x,ll res=0){
	while(x)(res+=t[x])%=mod,x-=lb(x);
	return res%mod;
}
int main(){
	n=d;
	f(i,1,n)st[i][0]=a[i]=d;
	// f(i,1,n)cout<<a[i]<<" ";cout<<endl;
	f(j,1,19)f(i,1,n){
		if(i+(1<<(j-1))>n)st[i][j]=st[i][j-1];
		else st[i][j]=(st[i][j-1]|st[i+(1<<(j-1))][j-1]);
	}f(i,2,n)lg[i]=lg[i/2]+1;
	f(i,1,n){
		ll p=i;
		while(1){if(p>n)break;
			ll o=get(i,p);
			ll l=p,r=n;
			while(l<r){
				ll mid=l+r+1>>1;
				if(get(i,mid)==o)l=mid;
				else r=mid-1;
			}w.pb({get(i,r),i,p,r});p=r+1;
		}
	}sort(begin(w),end(w));
	for(auto x:w){
		ll v=x[1]==1?1:ask(x[1]-1);
		add(x[2],v),add(x[3]+1,mod-v);
	}cout<<ask(n);
	return 0;
}
```

---

## 作者：gdf_yhm (赞：0)

### [CF2038D. Divide OR Conquer](https://codeforces.com/contest/2038/problem/D)

[my blog](https://yhddd123.github.io/post/2024-2025-icpc-nerc-southern-and-volga-russian-regional-contest-zuo-ti-ji-lu/)

### 思路

对于右端点 $i$，合法的值 $x$ 的左端点区间 $[l,r]$ 只有 $O(\log V)$ 个。二分加 st 表找出来。$dp_{i,x}=\sum_{l\le j\le r}\sum_{y\le x}dp_{j-1,y}$。 扫描线 $i$，离散化后树状数组维护 $\le x$ 的 dp 值之和。对于 $i$ 的区间 $[l,r]$，$dp_{i,x}$ 在扫到 $l-1$ 时减去  $\le x$ 的 dp 值之和，扫到 $r$ 时加上 $\le x$ 的 dp 值之和，扫到 $i$ 时加到树状数组里。

复杂度 $O(n\log n\log V)$。

### code

```cpp
int n,a[maxn],ans;
int f[18][maxn];
int calc(int l,int r){
	int k=__lg(r-l+1);
	return f[k][l]|f[k][r-(1<<k)+1];
}
struct node{
	int l,r,x,f;
};
int lsh[maxn<<5],len;
vector<node> ask[maxn];
vector<pii> add[maxn],del[maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
#define lb(x) (x&(-x))
int tree[maxn<<5];
void upd(int x,int w){while(x<=len)inc(tree[x],w),x+=lb(x);}
int que(int x){int res=0;while(x)inc(res,tree[x]),x-=lb(x);return res;}
void work(){
	n=read();
	for(int i=1;i<=n;i++)f[0][i]=a[i]=read();
	for(int j=1;j<18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)f[j][i]=f[j-1][i]|f[j-1][i+(1<<j-1)];
	}
	for(int i=1;i<=n;i++){
		int p=i;
		while(p){
			int l=1,r=p,res=p;
			while(l<=r){
				int mid=l+r>>1;
				if(calc(mid,i)==calc(p,i))res=mid,r=mid-1;
				else l=mid+1;
			}
			ask[i].pb({res,p,calc(p,i),0});
			lsh[++len]=ask[i].back().x;
			p=res-1;
		}
	}
	ask[0].pb({0,0,0,1});lsh[++len]=0;
	sort(lsh+1,lsh+len+1);len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<ask[i].size();j++){
			ask[i][j].x=lower_bound(lsh+1,lsh+len+1,ask[i][j].x)-lsh;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<ask[i].size();j++){
			int l=ask[i][j].l-1,r=ask[i][j].r-1,x=ask[i][j].x;
			del[l].pb({i,j}),add[r].pb({i,j});
		}
	}
	for(int i=0;i<=n;i++){
		for(auto[i,j]:del[i])inc(ask[i][j].f,mod-que(ask[i][j].x));
		for(int j=0;j<ask[i].size();j++)upd(ask[i][j].x,ask[i][j].f);
		for(auto[i,j]:add[i])inc(ask[i][j].f,que(ask[i][j].x));
	}
	for(auto[l,r,x,f]:ask[n])inc(ans,f);
	printf("%lld\n",ans);
}
```

[https://codeforces.com/contest/2038/submission/292313212](https://codeforces.com/contest/2038/submission/292313212)

---


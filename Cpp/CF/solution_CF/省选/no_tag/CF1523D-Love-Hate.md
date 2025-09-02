# Love-Hate

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523D/3bd36ba93bf29dd4f1bc9d42f11348613b292b67.png)William is hosting a party for $ n $ of his trader friends. They started a discussion on various currencies they trade, but there's an issue: not all of his trader friends like every currency. They like some currencies, but not others.

For each William's friend $ i $ it is known whether he likes currency $ j $ . There are $ m $ currencies in total. It is also known that a trader may not like more than $ p $ currencies.

Because friends need to have some common topic for discussions they need to find the largest by cardinality (possibly empty) subset of currencies, such that there are at least $ \lceil \frac{n}{2} \rceil $ friends (rounded up) who like each currency in this subset.

## 说明/提示

In the first sample test case only the first currency is liked by at least $ \lceil \frac{3}{2} \rceil = 2 $ friends, therefore it's easy to demonstrate that a better answer cannot be found.

In the second sample test case the answer includes $ 2 $ currencies and will be liked by friends $ 1 $ , $ 2 $ , and $ 5 $ . For this test case there are other currencies that are liked by at least half of the friends, but using them we cannot achieve a larger subset size.

## 样例 #1

### 输入

```
3 4 3
1000
0110
1001```

### 输出

```
1000```

## 样例 #2

### 输入

```
5 5 4
11001
10101
10010
01110
11011```

### 输出

```
10001```

# 题解

## 作者：OMG_wc (赞：12)

题意：一共有 $m$ 个元素，给你 $n$ 个集合，每个集合的元素不超过 $15$ 个。求出一个元素个数最多的集合 $T$  是至少 $\lceil n/2 \rceil$ 个集合的子集。



随机地选 $K$ 个集合，然后对其中的每个集合，枚举它的子集作为答案 。

因为最终 $T$ 是至少 $\lceil n/2 \rceil$ 个集合的子集，那么 $K$ 个集合都不在这  $\lceil n/2 \rceil$ 个集和重的概率为 $\frac{1}{2^K}$。取 $K=50$ ，概率为 $8.88178*10^{-16}$，已经足够低了。

具体操作是，随机选一个集合 $S$，把他拥有的元素编号存下来，然后求一下所有 $n$ 个集合只含这些元素的**新集合**，用一个`f`数组记录每种新集合的个数。 然后需要计算每个新集合的超集有多少个，暴力枚举是 $O(3^p)$  的，用高维前缀和来DP可以做到 $O(p\cdot2^p)$。

时间复杂度 $O(nm+K(m+np+p\cdot2^p))$。


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 200005;

LL a[N];
char s[100];
int f[1 << 15];
int main() {
    int n, m;
    scanf("%d%d%*d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        for (int j = 0; j < m; j++) {
            if (s[j] == '1') a[i] ^= 1LL << j;
        }
    }
    mt19937 g(time(0));
    uniform_int_distribution<int> u1(0, n - 1);
    LL ans = 0;
    int T = 50;
    while (T--) {
        vector<int> b;
        LL ak = a[u1(g)];
        for (int i = 0; i < m; i++) {
            if (ak >> i & 1) b.push_back(i);
        }
        memset(f, 0, sizeof f);
        for (int i = 0; i < n; i++) {
            int t = 0;
            for (int j = 0; j < b.size(); j++) {
                if (a[i] >> b[j] & 1) {
                    t ^= 1 << j;
                }
            }
            f[t]++;
        }

        for (int i = 0; i < b.size(); i++) {
            for (int j = 0; j < 1 << b.size(); j++) {
                if ((j >> i & 1) == 0) f[j] += f[j ^ 1 << i];
            }
        }
        int now = 0;
        for (int i = 0; i < 1 << b.size(); i++) {
            if (f[i] * 2 >= n && __builtin_popcount(i) > __builtin_popcount(now)) now = i;
        }
        if (__builtin_popcount(now) > __builtin_popcountll(ans)) {
            ans = 0;
            for (int i = 0; i < b.size(); i++) {
                if (now >> i & 1) ans ^= 1LL << b[i];
            }
        }
    }
    for (int i = 0; i < m; i++) {
        printf("%d", ans >> i & 1);
    }
    putchar('\n');
    return 0;
}
```







---

## 作者：Super_Cube (赞：4)

# Solution

很智慧啊。

注意到最终答案是至少 $\dfrac{n}{2}$ 个人的子集，那随机一个人，枚举所有其子集作为答案进行判断的错误率为 $\dfrac{1}{2}$，也就是说如果随机 $10$ 个人，错误率仅有 $\dfrac{1}{2^{10}}$，不到千分之一。在 CF 上这道题一共 $263$ 个测试点，一次性全部正确的概率为 $\left(1-\dfrac{1}{2^{10}}\right)^{263}\approx0.7734$，只要运气不算太差，是可以一发入魂的。

对于随机到的那个人，把他喜欢的货币类型存下来。这时对于所有人，只保留在刚刚存下的货币中有对应喜欢的货币类型。最后枚举保存下的货币类型中的所有子集，如果其超集大小不小于 $\dfrac{n}{2}$ 说明该集合合法，拿去更新答案。

由于数据范围较小，时限宽松，求超集大小可以直接 $O(3^p)$。当然，利用类似高位前缀和的写法可以做到 $O(2^p)$。

# Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
std::mt19937 rnd(time(0));
std::vector<int>v;
int s[32768];
ll a[200005];
int n,m,q,ans;
ll path;
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;++i){
		getchar();
		for(int j=0;j<m;++j)
			if(getchar()=='1')a[i]|=1ll<<j;
	}
	for(int T=10;T;--T){
		static ll lim;lim=a[rnd()%n+1];
		v.clear();
		for(int i=0;i<m;++i)
			if(lim>>i&1)v.push_back(i);
		memset(s,0,(1<<v.size())<<2);
		for(int i=1,k;i<=n;++i){
			k=0;
			for(int j=0;j<v.size();++j)
				if(a[i]>>v[j]&1)k|=1<<j;
			++s[k];
		}
		for(int j=0;j<v.size();++j)
			for(int i=0;i<(1<<v.size());++i)
				if(~i>>j&1)s[i]+=s[i|(1<<j)];
		for(int i=0;i<(1<<v.size());++i)
			if((s[i]<<1)>=n&&__builtin_popcount(i)>ans){
				ans=__builtin_popcount(i);
				path=0;
				for(int j=0;j<v.size();++j)
					if(i>>j&1)path|=1ll<<v[j];
			}
	}
	for(int i=0;i<m;++i)
		putchar(48|(path>>i&1));
	return 0;
}

```

---

## 作者：子丑 (赞：4)

一个比较假的暴搜剪枝，貌似是可以被 hack 的。但是随机数据应该没问题（×）

对于每种货币，用 `bitset` 保存喜欢它的人。如果喜欢一种货币的人数小于一半，那这个货币一定不会在答案中。随后对剩余的货币进行搜索。由于货币要被所有人喜欢，所以我们可以再用一个 `bitset` 来保存喜欢当前搜到所有货币的人的集合。最关键的点在于，**如果这个集合的大小小于总人数的一半，那么就能够进行剪枝**（可行性剪枝）。另外加两个最优答案剪枝，不再赘述。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, a, b) for(int i(a), i##up(b); i<=i##up; ++i)
#define rer(i, a, b) for(int i(a), i##dn(b); i>=i##dn; --i)
#define ree(e, u, v) for(int e=ehead[u], v=eto[e]; e; v=eto[e=enxt[e]])

inline int read(int t=0, bool f=1, char c=0) {
	while(!isdigit(c=getchar())) f=c^45;
	while(isdigit(c)) t=(t<<1)+(t<<3)+(c^48), c=getchar();
	return f? t: -t;
}
const int N=2e5+5, M=62;

int n, m, p, ans;
char s[M];

int item[M], its, mnx;
bool chos[M], anss[M];
bitset<N> lik[M], ful;
void dfs(int k, int nw, bitset<N> may) {
	if(ans==mnx||k+its-nw<=ans||may.count()*2<n) return;
	if(k>ans) ans=k, memcpy(anss, chos, sizeof(anss));
	rep(i, nw+1, its) chos[item[i]]=1, dfs(k+1, i, may&lik[item[i]]), chos[item[i]]=0;
}

int main() {
	n=read(), m=read(), p=read();
	rep(i, 1, n) rep(j, scanf("%s", s+1), m) lik[j][i]=s[j]^48;
	rep(i, 1, m) if(lik[i].count()*2>=n) item[++its]=i;
	rep(i, (mnx=min(its, p), ful.set(), dfs(0, 0, ful), 1), m) printf("%d", anss[i]);
}
```

复杂度比较假，勿 D。

---

## 作者：meyi (赞：4)

我们先从这道题的简化版本入手：已知最终答案为一位朋友的子集和这位朋友的编号，求最终答案。

将所有人对货币的喜爱情况只保留该朋友喜欢的货币，便可以 $O(2^p)$ 状压dp了。

那么问题来了：我们如何知道这位朋友的编号？

由于本题要求的是**一半以上的**朋友同时喜欢的货币，所以我们随机一个朋友，最终答案不是该朋友的子集的概率为 $\frac{1}{2}$，若我们随机 30 个**对货币的喜爱情况不同的朋友**，则我们运气差到没有找到答案的概率为 $9\times10^{-10}$，~~这比你被陨石砸中的概率还小几个数量级~~。

若我们随机 $t$ 次，则总时间复杂度为 $O(t(2^p+n))$，合理范围内的 $t$ 可以通过本题。

至于赛后产生的大量 `Successful hacking attempt`，从 `generator` 来看，有这样几种情况：

1. 未考虑每次随机的朋友**对货币的喜爱情况应是不同的**，否则会造成重复计算，我们使用 `set` 去重即可解决。

2. 根据你的随机数种子，预判你会选哪些数，于是叉掉了你的代码，这种情况只要把种子改的不止有当前时间就能解决。

UPD:

1. 修改了一些学术性错误

2. 因为原来的代码被叉了，所以对 `hack` 的相关内容进行了修改

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxn=2e5+10,mod=998244353;
#define pb push_back
mt19937 rnd;
int ans1,b[maxn],f[maxn],m,n,p;
string ans2,e,s[maxn];
set<string>ft;
map<string,bool>vis;
int main(){
	ll sd=time(0)%mod;
	sd=(sd<<15)%mod;
	sd=sd*sd%mod;
	rnd.seed(sd);
	clock_t st=clock();
	scanf("%d%d%d",&n,&m,&p);
	for(ri i=1;i<(1<<p);++i)b[i]=b[i-(i&-i)]+1;
	uniform_int_distribution<int>lim(1,n);
	for(ri i=1;i<=n;++i)cin>>s[i],ft.insert(s[i]);
	random_shuffle(s+1,s+n+1);
	for(ri i=0;i<m;++i)e+='0';
	ans2=e;
	while(clock()-st<=2500){
		ri x=lim(rnd);
		if(vis[s[x]])continue;
		vis[s[x]]=true;
		vector<int>pos;
		for(ri i=0;i<m;++i)
			if(s[x][i]=='1')
				pos.pb(i);
		memset(f,0,sizeof f);
		for(ri i=1;i<=n;++i){
			ri tmp=0;
			for(ri j=0;j<pos.size();++j){
				tmp<<=1;
				if(s[i][pos[j]]=='1')tmp|=1;
			}
			++f[tmp];
		}
		for(ri i=0;i<pos.size();++i)
			for(ri j=0;j<(1<<pos.size());++j)
				if(j&(1<<i))
					f[j^(1<<i)]+=f[j];
		for(ri i=1;i<(1<<pos.size());++i)
			if(f[i]*2>=n&&b[i]>b[ans1]){
				ans1=i;
				ans2=e;
				for(ri j=pos.size()-1,k=i;~j;--j,k>>=1)
					if(k&1)
						ans2[pos[j]]='1';
			}
		
	}
	cout<<ans2;
	return 0;
}
```

---

## 作者：SSerxhs (赞：3)

考虑如果已知 $x$ 必须喜欢这个集合应该怎么做。那么需要考虑的只有 $x$ 喜欢的 $15$ 个元素，算一下每个人喜欢哪些元素，子集卷积看一下哪些子集出现次数超过一半就可以了。

由于有 $\frac{n}{2}$ 个人喜欢答案集合，任选足够多个可以极大概率选到这些人。那么随机选取就可以了，这里选了 $80$ 个。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned int ui;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
std::mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
inline int sj(int n)
{
	unsigned int x=rnd();
	return x%n+1;
}
#define rand fst
template<typename typC> void read(register typC &x)
{
	register int c=getchar(),fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
template<typename typC, typename... Args> void read(typC &first, Args& ... args) {
	read(first);
	read(args...);
}
template<typename typC> void read(register typC *a,int num)
{
	for (register int i=1;i<=num;i++) read(a[i]);
}
template<typename typC> void write(register typC x)
{
	if (x<0) putchar('-'),x=-x;
	static int st[100];
	register int tp=1;
	register typC y;st[1]=x%10;x/=10;
	while (x) y=x/10,st[++tp]=x-y*10,x=y;++tp;
	while (--tp) putchar(st[tp]|48);
}
template<typename typC> void write(register typC *a,register int num)
{
	for (register int i=1;i<=num;i++) write(a[i]),putchar(i==num?10:32);
}
template<typename typC> typC ab(register typC x)
{
	if (x<0) return -x;
	return x;
}
#define space(x) write(x),putchar(32)
#define enter(x) write(x),putchar(10)
struct Q
{
	int u,v;
	Q(int a=0,int b=0):u(a),v(b){}
	bool operator<(const Q &o) const {return v<o.v;}
};
const int N=1e6+2,M=1e6+2,inf=1e9;
ll b[N],y,z;
int a[1<<15],d[100],pc[1<<15];
ll ta;
int T,n,m,tp,p,c,i,j,k,x,ans,ksiz,ks;
bool ed[N];
void fwt(int *a,int n)
{
	int i,j,k,l;
	for (i=1;i<n;i=l)
	{
		l=i<<1;
		for (j=0;j<n;j+=l) for (k=0;k<i;k++)
		{
			a[j|k]=(a[j|k]+a[j|k|i]);
		}
	}
}
int main()
{
	//ios::sync_with_stdio(false);
	read(n,m,p);
	for (i=1;i<1<<15;i++) pc[i]=pc[i>>1]+(i&1);
	for (i=1;i<=n;i++)
	{
		c=getchar();
		while (c<48||c>57) c=getchar();
		for (j=1;j<=m;j++) b[i]|=(c-48ll)<<m-j,c=getchar();
	}
	for (int ii=1;ii<=min(80,n);ii++)
	{
		x=rnd()%n+1;
		while (ed[x]) x=rnd()%n+1;
		//printf("x=%d\n",x);
		ed[x]=1;y=b[x];tp=0;
		for (j=0;j<m;j++) if (1ll<<j&y) d[tp++]=j;
		assert(tp<=15);
		memset(a,0,sizeof(a));
		for (i=1;i<=n;i++)
		{
			z=b[i]&y;k=0;
			for (j=0;j<tp;j++) if (1ll<<d[j]&z) k|=1<<j;
			++a[k];//printf("ik %d %d\n",i,k);
		}
		//write(a-1,1<<tp);
		fwt(a,1<<tp);
		//write(a-1,1<<tp);
		for (i=0;i<1<<tp;i++) if (a[i]>=(n+1>>1)&&ans<pc[i])
		{
			ans=pc[i];ta=0;
			for (j=0;j<tp;j++) if (1<<j&i) ta|=1ll<<d[j];
		}
	}
	for (i=m-1;i>=0;i--) if (1ll<<i&ta) printf("1"); else printf("0");
}


```

---

## 作者：pigstd (赞：2)

我的智力有问题，迟早要退役。

---

首先把每个人转化成一个二进制数。

注意到至少要有 $\frac n 2$，那么随机选一个数答案是他的子集的概率就至少 $\frac 1 2$，随机选若干个之后就能保证正确性。

然后发现子集最多 $2^p$ 个，枚举子集的复杂度是可以接受的，就把问题转化成对于每个子集 $s$，算出有多少个 $i$ 满足 $a_i \And s =s$。

这个东西很像 FWT 的形式，可惜值域是 $2^m$ 做不了，~~然后我就不会做了，看来我是真的傻逼。~~

注意到，如果随机到的是 $a_x$，那么显然如果二进制中第 $j$ 位为 $0$，那么无论其他的数第 $j$ 位是什么都是没有影响的。有因为不为 $0$ 的位数最多 $p$ 位，那么完全可以不管为 $0$ 的位数，剩下的 $p$ 位值域就是 $2^p$，FWT 一下就可以了。

时间复杂度 $\mathcal{O}(T\times p \times (2^p+n))$，$T$ 表示随机的次数。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rand rnd
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define WT int T=read();while(T--) 
#define NO puts("NO");
#define YES puts("YES");
using namespace std;

inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

const int M=2e5+10;
int n,m,p,a[M],b[M],bt[M],pp,maxn,ans;

struct poly
{
	int f[M];
	void clear(){memset(f,0,sizeof(f));}
}fwt;

void AND(poly &a,int x,int cnt)
{
	int n=1<<cnt;
	for (int o=2,k=1;o<=n;o<<=1,k<<=1)
		for (int i=0;i<n;i+=o)
			for (int j=0;j<k;j++)
				a.f[i+j]+=a.f[i+j+k]*x;
}

int get(int x)
{
	int res=0;
	for (int i=0;i<m;i++)
		if (x&(1ll<<i))res++;
	return res;
}

void work(int x)
{
	fwt.clear();int cnt=0;
	for (int i=0;i<m;i++)
		if (a[x]&(1ll<<i))bt[++cnt]=i+1;
	for (int i=1;i<=n;i++)
	{
		b[i]=0;
		for (int j=1;j<=cnt;j++)
			if (a[i]&(1ll<<(bt[j]-1)))b[i]+=1ll<<(j-1);
		fwt.f[b[i]]++;
	}
	AND(fwt,1,cnt);
	for (int i=0;i<(1<<cnt);i++)
		if (fwt.f[i]>=(n+1)/2&&get(i)>maxn)
			maxn=get(i),ans=i,pp=x;
}

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

signed main()
{
	srand(20061010);
	n=read(),m=read(),p=read();
	for (int i=1;i<=n;i++)
	{
		string s;cin>>s;
		for (int j=0;j<m;j++)
			a[i]+=(1ll<<j)*(s[j]-'0');
	}int T=50; work(n);
	while(T--)
	{
		int x=rand()%n+1;
		work(x);
	}int cnt=0;
	for (int i=0;i<m;i++)
		if (!(a[pp]&(1ll<<i)))cout<<"0";
		else
		{
			if (ans&(1ll<<cnt))cout<<"1";
			else cout<<"0";
			cnt++;
		}
	return 0;
}
```

---

## 作者：TTpandaS (赞：1)

考虑暴力：枚举答案集合，与 $n$ 个人依次比对，判断包含的人的数量是否大于 $\dfrac{n}{2}$。

考虑剪枝：

1. 如果当前包含的人数已经大于等于 $\dfrac{n}{2}$，跳出循环。

2. 如果当前包含的人数加剩下的人数仍然小于 $\dfrac{n}{2}$，跳出循环。

3. 如果一些位置所有人都是 $1$，那么这些位置必选，枚举答案集合时不用考虑这些位置。

4. 一个位置可能被包含在答案集合中当且仅当有大于等于 $\dfrac{n}{2}$ 的人对应该位置为 $1$，将这些位置提取出来，仅枚举这些位置为答案。

5. 如果当前答案等于 $15$ 或等于可能成为答案的合法位置总数，跳出循环。

6. 将对合法位置喜好相同的人合并。

7. 如果一个人的喜好满足要求，预先更新答案。

8. 如果当前枚举答案集合大小大于 $15$ 或小于最优答案，跳过。

9. 如果执行次数大于 $7.5 \times 10^8$，跳出循环。

加入上述剪枝即可通过此题。

---

## 作者：无名之雾 (赞：1)

[devans](https://www.luogu.com.cn/user/199139) 在 CF 杂题选讲里讲到的一道有趣题。

## 思路

### 官方随机化做法
题意还是很明确的。再不看数据范围的情况下很容易想状压 $\text{dp}$ 。然而 $2\times 10^5$ 的 $n$ 就证明了本题需要用更加巧妙的方法去做。

寻找突破口，根据直觉我们会发现：“人数不小于 $\lceil\dfrac{n}{2}\rceil$ 个”，这句应该作为本题的突破口。

由于包含最终答案的集合一定不小于 $\lceil\dfrac{n}{2}\rceil$ 个，那么倘若我们知道了其中一个人，那么就可以只看那个人所喜欢的不超过 $15$ 种货币，用简单的状压即可求得最优解。

而我们如何去找着一个人呢？

我们只需随机选取 $s$ 次，那么抽不到的概率就为 $2^{-s}$，基本可以视为正确的。


### 爆搜减枝做法

我们一开始先把喜欢人数小于要求的货币去除，显然，这样能把枚举的货币状态降到  $2^{30}$，然后用 $\text{bitset}$ 存喜欢每一种货币的人的状态，暴力搜索货币状态，把不合法的剪枝掉。


## 代码

tips：随机数不要用 `rand()` 生成。因为 CF 评测机貌似是基于 $\text{windows}$ 系统。`rand()` 生成的随机数上限只有 $32767$。

### 官方正解

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define ull unsigned long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
inline void out(int x){
    if(x==0){putchar('0');return;}
	int len=0,k1=x,c[10005];
	if(k1<0)k1=-k1,putchar('-');
	while(k1)c[len++]=k1%10+'0',k1/=10;
	while(len--)putchar(c[len]);
}
int rrrr=114514; 
inline int randd(){
	rrrr^=(rrrr<<3);
	rrrr^=(rrrr>>2);
	rrrr^=(rrrr<<5);
	rrrr%=1023853;
	return abs(rrrr);
}
const int N=2e5+5,M=64,INF=INT_MAX;
int cnt1(ull n){return __builtin_popcountll(n);}
int cnt1i(ull n){return __builtin_popcount(n);}
void set1(ull &n,ull p){n|=(1ull<<p);}
void set0(ull &n,ull p){n&=(-1ull-(1ull<<p));}
int query(ull &n,ull p){return (n>>p)&1ull;} 
ull mp[N],ans;
int v[M],a[N<<3];
signed main(){
	int n=read(),m=read(),p=read();
	for(int i=1;i<=n;i++){
		char buf[M];
		cin>>buf;
		for(int j=0;j<m;j++){
			if(buf[j]=='1')set1(mp[i],j);
			rrrr*=buf[j];
			rrrr+=buf[j];
	        rrrr%=1023853;
		}
	}
	//srand(time(0));
	for(int t=1;t<=135;t++){
		int u=randd()%n+1,vcnt=0; 
		memset(a,0,sizeof(a));
		for(int j=0;j<m;j++){
			if(query(mp[u],j))v[vcnt++]=j;
		}
		if(vcnt<=cnt1(ans))continue;
		for(int i=1;i<=n;i++){
			ull s=0ull;
			for(int j=0;j<vcnt;j++){
				if(query(mp[i],v[j]))set1(s,j);
			}
			a[s]++;
		}
		for(int j=0;j<vcnt;j++){
			for(int i=(1<<vcnt)-1;i>=0;i--){
			 	if(i&(1<<j))a[i^(1<<j)]+=a[i];
			}
		}
		for(int i=0;i<(1<<vcnt);i++){
			if(a[i]>=(n+1)/2&&cnt1i(i)>cnt1(ans)){
				ans=0ull;
				for(int j=0;j<vcnt;j++){
					if(i&(1<<j))set1(ans,v[j]);
				}
			}
		}
	}
	for(int i=0;i<m;i++)cout<<query(ans,i);
	return 0;
}
```


### 爆搜减枝
```cpp
#pragma GCC target("avx")
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
inline void out(int x){
    if(x==0){putchar('0');return;}
	int len=0,k1=x,c[10005];
	if(k1<0)k1=-k1,putchar('-');
	while(k1)c[len++]=k1%10+'0',k1/=10;
	while(len--)putchar(c[len]);
}
const int N=2e5+5; 
int n,m,p,tot,sum[65],Id[65],stak,ans;
bool cho[65],answ[65],mp[N][65];
bitset<N>bit[65],sta[65];
char maze[65];
void dosaka2(int id,int pre){
	if(id+(tot-pre)<=ans||sta[id].count()<(n+1)/2)return ;
	if(id>ans){ans=id;for(int i=1;i<=m;i++)answ[i]=cho[i];}
	for(int j=pre+1;j<=tot;j++){
		sta[id+1]=sta[id]&bit[j];
		cho[Id[j]]=1;dosaka2(id+1,j);cho[Id[j]]=0;
		if(ans==min(tot,p))return ;
	}
}
signed main(){
	n=read(),m=read(),p=read();
	for(int i=1;i<=n;i++){
		scanf("\n%s",maze+1);
		for(int j=1;j<=m;j++)if(maze[j]=='1')mp[i][j]=1,sum[j]++;
	}
	for(int i=1;i<=m;i++)if(sum[i]>=(n+1)/2)Id[++tot]=i;
	for(int i=1;i<=tot;i++)for(int j=1;j<=n;j++)bit[i][j]=mp[j][Id[i]];
	for(int i=1;i<=n;i++)sta[0][i]=1;dosaka2(0,0);
	for(int i=1;i<=m;i++)printf("%d",answ[i]);puts("");
	return 0;
}
```

---

## 作者：qiaochenya (赞：0)

# D. Love Hate 题解

## 题目大意
给你 $n$ 个集合，有 $m$ 个元素种类，每个集合最多 $p$ 个元素。

要你求出一个元素个数最多的集合 $t$ ，满足 $t$ 是 $\geq \lceil \frac{n}{2} \rceil$ 个集合的子集。

$1\le n\le 2\times 10^5,\ 1\le p\le m\le 60, \ 1\le p\le 15$。

## 思路
没学过高维前缀和（sos dp），学完再写这道题。

最直观的想法就是全部元素都导进来，反向高维前缀和求一遍子集，如果 $dp_{mask} \geq \lceil \frac{n}{2} \rceil$ ，那么 $dp_{mask}$ 就可以和 $ans$ 的 $1$ 的数量取 $\max$。

但是复杂度 $O(2^{m} \cdot m)$ ，并且 $dp$ 数组也不能搞这么大的空间，时间和空间都不允许。

注意到一个集合的元素最多只有 $p$ 个， $p$ 很小。

那么我们可以先从 $n$ 个集合中，选定一个集合，假设它是 $\geq \lceil \frac{n}{2} \rceil$ 个集合当中的一个。
    
有了这个集合限制了其它集合的的位数，如果这个集合的这位为 $0$ ，那么其它集合的这位只能是 $0$ ，能从 $1 \rightarrow (1,\ 0)$ 的只有选定集合为 $1$ 的位，那么我们只需枚举选定集合为 $1$ 的位数，最多 $p$ 个，那么复杂度就从 $O(2^{m} \cdot m) \rightarrow O(2^{p} \cdot p)$。

那么如何从 $n$ 中选这个集合出来？并且如果选出来的集合不在答案 $\geq \lceil \frac{n}{2} \rceil$ 个集合当中的一个怎么办。

我们可以随机选 $50$ 次，那么每次这个集合不在答案的概率为 $\frac{1}{2}$ ，${\frac{1}{2}}^{50} = 8.881784197001252 \cdot 10^{-16}$ 概率很小。

所以直接随机 $50$ 次做，每次做一次高维前缀和，更新答案，这题就做完了。

复杂度 $O(50 \cdot 2^{p} \cdot p)$。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long i64;

mt19937 rng {chrono::steady_clock::now().time_since_epoch().count()};

const int N = 2E5 + 10, B = 50, M = 1 << 17;
int n, m, p;
i64 a[N];
int b[N], dp[M];

signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	
	cin >> n >> m >> p;
	for (int i = 1; i <= n; i++) {
		string t; cin >> t;
		for (int j = 0; j < m; j++) if (t[j] == '1') {
			a[i] |= 1ll << j;
		}
	}
	vector<int> ans;
	for (int tc = 0; tc < B; tc++) {
		int idx = rng() % n + 1;
		vector<int> v;
		for (int i = 0; i < m; i++) if (a[idx] >> i & 1) {
			v.push_back(i);
		}
		memset(dp, 0, sizeof dp);
		for (int i = 1; i <= n; i++) {
			b[i] = 0;
			for (int j = 0; j < v.size(); j++) {
				b[i] |= (a[i] >> v[j] & 1) << j;
			}
			dp[b[i]]++;
		}
		for (int i = p; i >= 0; i--) {
			for (int j = 0; j < (1 << p); j++) if (!(j >> i & 1)) {
				dp[j] += dp[j ^ (1 << i)];			
			}
		}
		for (int i = 0; i < (1 << p); i++) if (dp[i] >= (n + 1) / 2) {
			if (__builtin_popcount(i) > ans.size()) {
				ans.clear();
				for (int j = 0; j < v.size(); j++) {
					if (i >> j & 1) {
						ans.push_back(v[j]);
					}
				}
			}
		}
	}

	string res = string(m, '0');
	for (auto x : ans) {
		res[x] = '1';
	}
	cout << res << "\n";
	
	return 0;
}
```

---


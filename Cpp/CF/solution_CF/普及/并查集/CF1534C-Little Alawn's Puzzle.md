# Little Alawn's Puzzle

## 题目描述

When he's not training for IOI, Little Alawn enjoys playing with puzzles of various types to stimulate his brain. Today, he's playing with a puzzle that consists of a $ 2 \times n $ grid where each row is a permutation of the numbers $ 1,2,3,\ldots,n $ .

The goal of Little Alawn's puzzle is to make sure no numbers on the same column or row are the same (we'll call this state of the puzzle as solved), and to achieve this he is able to swap the numbers in any column. However, after solving the puzzle many times, Little Alawn got bored and began wondering about the number of possible solved configurations of the puzzle he could achieve from an initial solved configuration only by swapping numbers in a column.

Unfortunately, Little Alawn got stuck while trying to solve this harder problem, so he was wondering if you could help him with it. Find the answer modulo $ 10^9+7 $ .

## 说明/提示

The two possible puzzle configurations for example $ 1 $ are:

- $ [1,4,2,3] $ in the first row and $ [3,2,1,4] $ in the second;
- $ [3,2,1,4] $ in the first row and $ [1,4,2,3] $ in the second.

## 样例 #1

### 输入

```
2
4
1 4 2 3
3 2 1 4
8
2 6 5 1 4 3 7 8
3 8 7 5 1 2 4 6```

### 输出

```
2
8```

# 题解

## 作者：wmrqwq (赞：7)

# 题目链接

[CF1534C Little Alawn's Puzzle](https://www.luogu.com.cn/problem/CF1534C)

# 题意简述

给定两个排列 $a,b$，你可以进行的操作为交换一列中的两个数字，你需要求出操作后能够满足没有相同数字在同一行的数阵能的个数并对 $10^9+7$ 取模。

# 解题思路

我们先举两个例子：

```
1 2 3 4 5
1 2 3 4 5
```

这个例子的方案数很显然，可以抽象成一个五位的 $01$ 字符串的方案数，答案为 $2^5$。

```
1 2 3 4 5
3 1 2 4 5
```

这个例子我们发现，要是条件成立，一定会去交换第 $1 \sim 3$ 位的数字或不交换第 $1 \sim 3$ 位的数字，一定会去交换第 $4$ 位的数字或不交换第 $4$ 位的数字，一定会去交换第 $5$ 位的数字或不交换第 $5$ 位的数字，答案为 $2^3$。

而这个例子我们可以用一张图表示：

![](https://cdn.luogu.com.cn/upload/image_hosting/n0qb7ir4.png)

通过上面两个例子，容易看出，答案一定是 $2$ 的正整数次幂，然后我们可以将问题转化成每次连接 $a_i,b_i$ 两个点，记连通块的数量为 $x$，容易看出最后答案是 $2^x$，最后我们直接用并查集维护即可。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,ans,a[400010],u[400010],v[400010];
long long find(long long x)
{
	if(a[x]==x)
		return x;
	return a[x]=find(a[x]);
}
#define mod (int)1e9+7
#define lowbit(x) x&-x
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
int main()
{
	IOS;
	cin>>t;
	while(t--)
	{
		ans=1;
		cin>>n;
		for(int i=1;i<=n;i++)
			a[i]=i;
		for(int i=1;i<=n;i++)
			cin>>u[i];
		for(int i=1;i<=n;i++)
			cin>>v[i];
		for(int i=1;i<=n;i++)
			a[find(u[i])]=find(v[i]);
		map<int,int>mp;
		for(int i=1;i<=n;i++)
			if(!mp[find(i)])
				mp[find(i)]=1,ans*=2,ans%=mod;	
		cout<<ans<<endl;
	}
	QwQ;
}
```

---

## 作者：Acc_Robin (赞：7)

注意到，我们每次可以选择交换的一定是一个循环置换。

考虑到每个循环置换有交换和不交换两种情况，那么答案即为 $2^{cnt}$，其中 $cnt$ 指循环置换数。

如何求解循环置换数？

考虑并查集，把每一个 $a_i$ 向 $b_i$ 连边，最终的连通块个数就是循环置换数。

使用按稚合并和路径压缩可以达到 $O(n\alpha(n))$，代码中仅使用了路径压缩，复杂度 $O(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
#define int long long
    const int N = 4e5+10;
    int n,T[N],a[N],r;
    int find(int x){
        return T[x]=T[x]==x?x:find(T[x]);
    }
    void unit(int x,int y){
        if((x=find(x))!=(y=find(y)))T[y]=x;
    }
    const int mod = 1e9+7;
    int qpow(int a,int b){
        int r=1;
        for(;b;b>>=1,a=a*a%mod)if(b&1)r=r*a%mod;
        return r%mod;
    }
    void work(){
        cin>>n,r=0;
        for(int i=1;i<=n;i++)cin>>a[i],T[i]=i;
        for(int i=1,x;i<=n;i++)cin>>x,unit(a[i],x);
        for(int i=1;i<=n;i++)r+=T[i]==i;
        cout<<qpow(2,r)<<'\n';
    }
#undef int
}
int main(){
    int T;
    for(cin>>T;T--;)Acc::work();
    return 0;
}

```

---

## 作者：StayAlone (赞：3)

### 题意

给定两行，每行是 $n$ 个数的排列，可以将同一列的第一行的数与第二行的数交换。请问有多少交换方法使得每一行、每一列没有重复的数。由于答案可能很多，输出答案模 $10^9 + 7$ 的值。

### 瞎扯
发现 SSerxhs 奆佬管理的思路和我一样诶，~~我只得把那份题解编得详细一点了。~~

### 思路

把每一列第一行与第二行的数连一条**有向边**，样例一比较简单，下图是样例二连起来的样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/l5q30nim.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

设有 $x$ 个环，则答案是 $2^x$ 种方案。  
故因为上图有 $3$ 个环，答案是 $2^3 = 8$ 种。

原因很好理解：  

1. 每个环有选与不选两种方案，而不是点数个方案，因为如果要选择这个环，必须把环上所有点交换防止某一行的数字重复。

2. 想到环是因为如有有 $a \to b$，则必须有 $b \to a$，因此，目标是找有多少情况使得**选择某些数换下来，而换上去的那些数正好就是最开始选择的那些数。** 正好满足环的条件。  

[AC code记录](https://www.luogu.com.cn/record/51778110)

```cpp
#include <bits/stdc++.h>
#define ll long long
#define fr(i, l, r) for (int i = l; i <= r; ++i)
using namespace std;
int t, n; int a[400010], a2[400010], vis[400010], cnt;
const int mod = 1e9 + 7;
vector <int>link[400010]; // 存图用邻接矩阵会爆空间，然而其实每个数的出度都是 1

void dfs(int now)
{
	if (!vis[link[now][0]]) vis[link[now][0]] = true, dfs(link[now][0]);
	else
	{
		cnt++; return;
	}
}

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n); cnt = 0;
		fr(i, 1, n) scanf("%d", a + i), vis[i] = false;
		fr(i, 1, n) scanf("%d", a2 + i), link[a[i]].push_back(a2[i]);
		fr(i, 1, n) if (!vis[i]) vis[i] = true, dfs(i);
		int ans = 1;
		fr(i, 1, cnt) ans = ans * 2 % mod; // 边乘边模，不会爆 int
		printf("%d\n", ans);
		fr(i, 1, n) link[i].clear(); // CF 第一次交没清空，亏死了
	}
	return 0;
}
```

---

## 作者：SSerxhs (赞：2)

记 $pa(i)$ 表示 $i$ 在 $a_i$ 出现的下标，$pb(i)$ 同理。

如果强制交换第 $i$ 列，那么必定要交换第 $pa(b_i)$ 列，否则会导致第一行出现两个 $b_i$。此时把 $pa(b_i)$ 作为新的强制交换列继续考虑这个问题，可以发现直到某一次强制交换列是前面已经考虑过的一列时才会停止。

如果看成一张图，从 $a_i$ 向 $b_i$ 连边，那么相当于每个点各有一条出边入边，且某个点改变会导致其所在环的所有点改变。因此自由元个数 $x$ 和环个数相等，答案即为 $2^x$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned int ui;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
#define range(x) (x).begin(),(x.end())
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
const int p=1e9+7;
const db eps=1e-9;
inline void inc(register int &x,const int y)
{
	if ((x+=y)>=p) x-=p;
}
inline void dec(register int &x,const int y)
{
	if ((x-=y)<0) x+=p;
}
inline int ksm(register int x,register int y)
{
	register int r=1;
	while (y)
	{
		if (y&1) r=(ll)r*x%p;
		x=(ll)x*x%p;
		y>>=1;
	}
	return r;
}
priority_queue<int> ONLYYFORRCOPYY;
priority_queue<int,vector<int>,greater<int> > ONLYYFORRCOPYY__;
struct Q
{
	int u,v;
	Q(int a=0,int b=0):u(a),v(b){}
	bool operator<(const Q &o) const {return v<o.v;}
};
const int N=1e6+2,M=1e6+2,inf=1e9;
char s[N];
int a[N],b[N],pa[N],pb[N];
bool ed[N];
int T,n,m,c,i,j,k,x,y,z,ans,la,ksiz,ks;
int main()
{
	//ios::sync_with_stdio(false);
	cout<<setiosflags(ios::fixed)<<setprecision(15);
	T=1;
	read(T);
	while (T--)
	{
		read(n);
		read(a,n);
		read(b,n);ans=1;
		for (i=1;i<=n;i++) pa[a[i]]=i,pb[b[i]]=i,ed[i]=0;
		for (i=1;i<=n;i++) if (!ed[i])
		{
			x=a[i],y=b[i];ed[i]=1;
			while (y!=x)
			{
				y=pa[y];
				ed[y]=1;
				y=b[y];
			}
			ans=(ll)ans*2%p;
		}enter(ans);
	}
}
```

---

## 作者：fush (赞：1)

## 题目链接
[洛谷题目链接](https://www.luogu.com.cn/problem/CF1534C)  
[CF题目链接](https://codeforces.com/problemset/problem/1534/C)
## 题目简述
有两行数，都是 $n$ 的排列，你可以交换一列上的两个数。问，有多少个数阵中一行中没有同样的两个数。答案对 $10 ^ {9} + 7$ 取模。
## 解题思路
我们先看个样例：

1 2 3 4 5  
5 3 4 2 1

如果我们要将第一列交换，为了满足规则，必然要将第五列交换。 

我们设 $a_i$ 表示第一行的第 $i$ 个数, $m_i$ 表示第二行中 $i$ 的位置。 

那么我们交换第 $i$ 列，就必须交换第 $m_{a_i}$ 列，然后一直交换，直到第 $m_{a_i}$ 列已经被交换了，这就是一个置换环。

设有 $k$ 个置换环，则答案是 $2^k  \bmod (10^9 + 7)$。


## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod = 1e9 + 7;
const int N = 4e5 + 10;
int a[N], b[N], m[N];
bool vis[N];
int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        memset(vis, 0, sizeof vis);
        for(int i = 1; i <= n;i ++)
        cin >> a[i];
        for(int i = 1; i <= n; i++)
        cin >> b[i], m[b[i]] = i;
        long long ans = 1;
        for(int i = 1; i <= n; i++){
            if(vis[a[i]])continue;
            ans *= 2, ans %= mod;
            for(int j = i; !vis[a[j]]; j = m[a[j]])
            	vis[a[j]] = 1;
        }
        cout << ans << endl;
    }
}
```

---

## 作者：Dfkuaid (赞：1)

考虑一下交换情况，显然会有相互影响的列，而这样的列最终一定会连成环，而每个环一共只可能有 $2$ 种情况，所以假如一共有 $k$ 个环，答案应当为 $2^k$。

下面来看怎么找环。

我们准备两个数组 ```a[2][N]``` 和 ```p[2][N]```，其中 ```a``` 数组存储数值，```p``` 数组存储每一行每一个数所在的位置。由于最初给出的数列是和法数列，所以相冲突的数必然不在同一行。

我们只需要找到一个未访问过的列，将这一列标记为已访问，再去寻找这一列第二行的数在第一行哪里出现，进行递归，直到访问到一个已访问的列，说明形成了环，计数加一，退出递归。重复这个过程，直到所有列都被访问。

由于仅有 $n$ 列，每列只会访问一次，所以找环是均摊 $O(1)$ 总体 $O(n)$ 的时间复杂度。


``` cpp
const int N = 500010;
const int MOD = 1e9 + 7;
const int INF = 0x3fffffff;

int t,n,a[2][N],v[N],p[2][N],ans = 1;

inline void get_ring(int k,int f){
    if (v[k]) return;
    v[k] = 1;
    get_ring(p[f][a[f ^ 1][k]],f);
}

int main(){
    scanf("%d",&t);
    while (t --){
        mset(v,0);ans = 1;
        scanf("%d",&n);
        for (int i = 1;i <= n;i ++){
            scanf("%d",&a[0][i]);
            p[0][a[0][i]] = i;
        }
        for (int i = 1;i <= n;i ++){
            scanf("%d",&a[1][i]);
            p[1][a[1][i]] = i;
        }
        for (int i = 1;i <= n;i ++)
          if (!v[i]){
              (ans <<= 1) %= MOD;
              get_ring(i,0);
          }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：SDqwq (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1534C)

# $\texttt{Description}$

一个 $2\times n$ 的矩阵，可以操作任意次，每次操作是交换某一列上的 $2$ 个数字，经过操作之后，有多少种同一行没有相同数字的情况。方案数对 $10^9+7$ 取模。

# $\texttt{Solution}$

这是一道好题（当然是对于我这种屑来说）。

- 我们知道，我们交换的一定是某些整个的循环置换。

- 循环置换的意思就是在这个置换里面的每个数都出现了 $2$ 次，可以理解为是一个封闭的块。

- 假设有 $cnt$ 个循环置换，那么答案其实就是 $\sum\limits_{i=0}^{cnt}C_{cnt}^i$，这个应该是很好理解（代码实现中写的是这种）。但是还有另外一种简单的求法，就是 $2^{cnt}$，为什么呢？因为每个都有选或不选两种情况。

- 至于如何求出 $cnt$，有两种方法：

	- 直接 dfs，这里我选择了 dfs。
    
    - 并查集，将给出的矩阵每列的两个数合并，再统计连通块数量即可。
    
时间复杂度：$\mathcal{O}(n\log n)$

# $\texttt{Code}$

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <map>

using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;
inline int Min (int x, int y) {return x < y ? x : y;}
inline int Max (int x, int y) {return x > y ? x : y;}

int a[400005], b[400005];
bool vis[400005];
map<int, int> mp;

inline ll quickPow (ll a, ll k, ll p) {
	ll res = 1;
	a %= p;
	while (k) {
		if (k & 1)
			res = res * a % p;
		k >>= 1;
		a = a * a % p;
	}
	return res;
}

inline ll inv (ll x, ll p) {
	return quickPow(x, p - 2, p);
}

inline void dfs (int i) {
	if (vis[b[i]])
		return;
	vis[b[i]] = true;
	dfs(mp[b[i]]);
}

int main () {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, cnt = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]), mp[a[i]] = i;
		for (int i = 1; i <= n; i++)
			scanf("%d", &b[i]);
		memset(vis, false, sizeof(vis));
		for (int i = 1; i <= n; i++)
			if (!vis[a[i]]) {
				vis[a[i]] = true;
				dfs(i);
				cnt++;
			}
		ll ans = 1, tot = 1ll * cnt, fac = 1;
		for (int i = 1; i <= cnt; i++) {
			fac = fac * i % mod;
			ans = (ans + tot * inv(fac, mod) % mod) % mod;
			tot = tot * (cnt - i) % mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：jiangtaizhe001 (赞：1)

[题目传送门](https://codeforces.com/problemset/problem/1534/C)
## 题目大意
给出一个 $2\times n$ 的矩阵，要求交换这个矩阵之中同一列的两个数字（当然可以交换多次，也可以不换），交换后要求每一行每一列都不能有相同的数字。求方法数量除以 $10^9+7$ 的余数。  
## 题目解析
如果有一列有相同的数字，肯定是 $0$。  
现在考虑一下答案不为 $0$ 的情况。  
由于每一行都是一个全排列，所以我们需要在交换的时候保证有一个数字从上面换到了下面，那么这个数字肯定要再换上去一个，这样我们就可以发现，有几列必须同时换,我们可以通过搜索来确定必须一起交换的列，这样就可以把所有的 $n$ 列分成 $x$ 个部分，由于这 $n$ 个数字都是全排列，所以不存在某一列不属于这 $x$ 部分，答案显然就是 $2^x$。
搜索的时候我们可以开个桶来优化查找的过程。

代码：
```cpp
#include<cstdio>
#include<cstring>
#define maxn 400039
#define MOD 1000000007
using namespace std;
//#define debug
typedef int Type;
typedef long long ll;
inline Type read(){
	Type sum=0;
	int flag=0;
	char c=getchar();
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-') c=getchar(),flag=1;
	while('0'<=c&&c<='9'){
		sum=(sum<<1)+(sum<<3)+(c^48);
		c=getchar();
	}
	if(flag) return -sum;
	return sum;
}
int T,n,a[maxn],b[maxn];
int vis[maxn],t[maxn],ans;
ll pow(int a,int x){
	ll res=1,tmp=a;
	while(x){
		if(x&1) res=res*tmp%MOD;
		tmp=(tmp*tmp)%MOD;
		x>>=1;
	}
	return res;
}
int check(){
	for(int i=1;i<=n;i++)
	    if(a[i]==b[i]) return 1;
	return 0;
}
void dfs(int x){
	if(vis[x]) return;
	vis[x]=1;
	dfs(t[a[x]]);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
    T=read();
	while(T--){
    	n=read(); ans=0;
    	for(int i=1;i<=n;i++) a[i]=read();
    	for(int i=1;i<=n;i++) b[i]=read();
    	if(check()){
    		printf("0\n");
    		continue;
		}
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++)
		    t[b[i]]=i;
		for(int i=1;i<=n;i++)
		    if(!vis[i]){
		    	dfs(i);
				ans++;
			}
		printf("%lld\n",pow(2,ans));
	}
	return 0;
}
```

---

## 作者：czh___ (赞：0)

### 思路：
1. 每一个闭环，可以选择翻转对应的 $a_i$ 与 $b_i$，也可以选择不翻转，所以每个环有两种选择，最后答案为 $2^k$ （$k$ 为环的次数），而且 $k$ 至少为 $1$。

2. 每个闭环里面出现的 $i$ 是不会再出现在其他闭环里的，如果出现一个小闭环（不是一整个数组），那么说明一定还有其他的小闭环。

3. 循环里面的是最核心的内容，多想想！

上代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Mod=1e9+7,N=400001;
int a[N],b[N],to[N];
bool vis[N];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) 
			scanf("%d",&a[i]),vis[i]=0;
		for(int i=1;i<=n;i++) 
			scanf("%d",&b[i]),to[a[i]]=b[i]; 
		int ans=1;
		for(int i=1;i<=n;i++){
			if(vis[i]) 
				continue;
			vis[i]=1;
			ans=(2ll*ans)%Mod;
			int p=i; 
			while(!vis[to[p]]) 
				p=to[p],vis[p]=1;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

[改编于](https://blog.csdn.net/qq_52313416/article/details/120955144?ops_request_misc=%257B%2522request%255Fid%2522%253A%25229568261E-F23D-4DDA-98B9-2B82788C7D6A%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=9568261E-F23D-4DDA-98B9-2B82788C7D6A&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-120955144-null-null.142^v100^pc_search_result_base5&utm_term=Little%20Alawns%20Puzzle&spm=1018.2226.3001.4187)

---

## 作者：HerikoDeltana (赞：0)

# C Little Alawn's Puzzle

[CF1534C Little Alawn's Puzzle](https://www.luogu.com.cn/problem/CF1534C)

## 题意简述

题目给出一个 $2 \times n$ 的数阵，问你在经过操作之后，能够满足**没有相同数字在同一行**的数阵能有多少个。

你可以进行的操作就是**交换一列中的两个数字**。

由于答案可能会很大，所以你需要在输出之前模上 $10^9+7$，并且每个测试点有多组数据。

## 思路简述

我们可以先来观察一下样例。

可以发现假如我们交换任意一列的两个数，其它的所有的拥有这两个数之一的列也都会被影响到，否则将出现矛盾。

于是可以发现，其实每一组相关联的列都构成了一个环，于是我们可以建图来查环。

由于我脑袋比较直就随手写了个并查集，最后查一下有几个集即可。


## Code


```cpp
#include <bits/stdc++.h>
#define Heriko return
#define Deltana 0
#define S signed
#define LL long long
#define R register
#define I inline
#define CI const int
#define mst(a, b) memset(a, b, sizeof(a))
#define ON std::ios::sync_with_stdio(false)
using namespace std;
I void fr(LL & x)
{
    LL f=1;
    char c=getchar();
    x=0;
    while(c<'0' or c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while (c>='0' and c<='9') 
    {
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    x*=f;
}
I void fw(LL x)
{
    if(x<0) putchar('-'),x=-x;
    static LL stak[35];
    LL top=0;
    do
    {
        stak[top++]=x%10;
        x/=10;
    }
    while(x);
    while(top) putchar(stak[--top]+'0');
    putchar('\n');
}
CI MXX=2e6+5,mod=1e9+7;
LL t,n,f[MXX],a1[MXX],ans,os[MXX];
LL find(LL x)
{
    if(x!=f[x]) f[x]=find(f[x]);
    Heriko f[x];
}
I void uni(LL a,LL b)
{
    f[find(a)]=find(b);
}
I LL powermod(LL a,LL n,LL m)
{
	if(n==0) Heriko 1%m;
	LL x=powermod(a,n/2,m);
	LL res=x*x%m;
	if(n%2!=0) res=res*a%m;
	Heriko res;
}
S main()
{
    fr(t);
    while(t--)
    {
        fr(n);f[n+n+1]=ans=0;
        //整齐划一的 for
        for(R LL i=1;i<=n+n;++i) f[i]=i;
        for(R LL i=1;i<=n+n;++i) fr(a1[i]);
        for(R LL i=1;i<=n;++i) uni(a1[i],a1[i+n]);
        for(R LL i=1;i<=n+n;++i) os[i]=0;
        for(R LL i=1;i<=n+n;++i) os[find(i)]++;
        for(R LL i=1;i<=n;++i) if(os[i]) ans++;
        fw(powermod(2,ans,mod));
    }
    Heriko Deltana;
}
```

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：   

涉及算法：**并查集**。  

为什么要使用并查集：

- 因为交换只能是列交换，并且保证不与别的重复
- 我们通过观察题目发现，某些列之间互为限制关系  
- 即如果某列序列排序方式固定，则被限制的列也为固定的
- 此时我们会发现只有两种（一个互相限制的集合列）   

既然如此，我们将这每个集合看作为一个联通分量。   
用并查集枚举有几个连通分量。     
特别的，一列中的两个数肯定互相限制。     

如果我们有 $ans$ 个联通分量。  
则答案为 $2^{ans}$ 。   

> 注意：一定要开 long long    

### Solution:

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int long long
const int N=4e5+50;
const int mod=1e9+7;
int t,n;
int p[N],a[N],b[N];
int find(int x){
	if(x!=p[x]) return p[x]=find(p[x]);
	return p[x]; 
}
int qbow(int a,int b,int m)
{
    ll ans=1;
    while(b>0)
    {
        if(b%2!=0)
            ans=ans*a%m;
        a=a*a%m;
        b=b>>1;  
    }
    ans %= m;
    return ans;
}
signed main()
{
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;++i) scanf("%lld",&a[i]),p[i]=i;
		for(int i=1;i<=n;++i) {
			scanf("%lld",&b[i]);
			int fx=find(a[i]),fy=find(b[i]);
			if(fx!=fy){
				p[fx]=fy;
			}
		}
		int ans=0;
		for(int i=1;i<n;++i){
			int fx=find(i),fy=find(i+1);
			if(fx!=fy){
				ans++;
				p[fx]=fy;
			}
		}
		printf("%lld\n",qbow(2,ans+1,mod));
	}
}
```

---


# Jeff and Brackets

## 题目描述

Jeff loves regular bracket sequences.

Today Jeff is going to take a piece of paper and write out the regular bracket sequence, consisting of $ nm $ brackets. Let's number all brackets of this sequence from $ 0 $ to $ nm $ - $ 1 $ from left to right. Jeff knows that he is going to spend $ a_{i\ mod\ n} $ liters of ink on the $ i $ -th bracket of the sequence if he paints it opened and $ b_{i\ mod\ n} $ liters if he paints it closed.

You've got sequences $ a $ , $ b $ and numbers $ n $ , $ m $ . What minimum amount of ink will Jeff need to paint a regular bracket sequence of length $ nm $ ?

Operation $ x\ mod\ y $ means taking the remainder after dividing number $ x $ by number $ y $ .

## 说明/提示

In the first test the optimal sequence is: $ ()()()()()() $ , the required number of ink liters is $ 12 $ .

## 样例 #1

### 输入

```
2 6
1 2
2 1
```

### 输出

```
12
```

## 样例 #2

### 输入

```
1 10000000
2
3
```

### 输出

```
25000000
```

# 题解

## 作者：Lgx_Q (赞：2)

[orz](https://www.luogu.com.cn/problem/CF351C)

容易想到一种非常暴力的DP：$f_{i,j}$ 表示前 $i$ 个位置中还有 $j$ 个未匹配的左括号，此时的最小代价。

很明显这样的 DP 时间复杂度为 $O(n^2m^2)$ 级别。

发现对于每 $n$ 个位置，代价固定，不妨把 $n\times m$ 个位置分成 $m$ 个块，每个块有 $n$ 个位置。

每次转移不妨思考最后一个块的状态。设 $f_{i,j}$ 表示前 $i$ 个块中还有 $j$ 个左括号，此时的最小代价。枚举第 $i$ 个块的状态，设 $g_{i,j,k}$ 表示一个块中前 $i$ 个位置中，有 $j$ 个未匹配的右括号（允许有未匹配的右括号）,左括号数量与右括号数量的差为 $k$，此时的最小代价。可以采用更新地推的方式计算 $g$ 数组，时间复杂度 $O(n^3)$。

显然 $f_{i,j}+\min_{q=0}^{j}\{g_{n,q,k}\}\rightarrow f_{i+1,j+k}$

$q$ 和 $k$ 可以分开枚举。但是，这样的时间复杂度仍然是 $O(m^2n^2)$。

我们发现，这 $n$ 个块顺序没有关系，每个块 **左括号与右括号的差** 的顺序没有关系。

比如 $t_1,t_2,t_3,t_4,t_5$ 为五个块左括号与右括号之差。

如果说 $t_1=7,t_2=5,t_3=9,t_4=-9,t_5=-12$，为什么不先把 $t_5$ 排在 $t_2,t_3$ 之间呢？这样一来，总体所需的状态最多为 $12$。

普遍地说，对于一个状态 $f_{i,j}$，如果 $j>n$，那么下一个转移的块 **左括号与右括号的差** 就应该为负数（如果不是，迟早都要出现一个负数，因为最终答案是 $f_{m,0}$），发现这样做并不影响答案，而第二维的状态数只有 $2n$。

时间直接变成 $O(mn^3)$。

直接矩阵乘法加速，时间复杂度 $O(n^3\log m)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn=50;
ll n,m,x[maxn],y[maxn],g[maxn][maxn][maxn];
struct mat
{
	ll dat[maxn][maxn];
	const mat operator*(const mat tmp) const
	{
		mat ans;
		memset(ans.dat,0x3f,sizeof ans.dat);
		for(ll i=0;i<=2*n;i++)
			for(ll j=0;j<=2*n;j++)
				for(ll k=0;k<=2*n;k++)
					ans.dat[i][j]=min(ans.dat[i][j],dat[i][k]+tmp.dat[k][j]);
		return ans;
	}
}a,ans;
int main()
{
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++) scanf("%lld",&x[i]);
	for(ll i=1;i<=n;i++) scanf("%lld",&y[i]);
	memset(g,0x3f,sizeof g);
	g[0][0][n]=0;
	for(ll i=0;i<n;i++)
		for(ll j=0;j<=i;j++)
			for(ll k=n-i;k<=n+i;k++)
			{
				g[i+1][j][k+1]=min(g[i+1][j][k+1],g[i][j][k]+x[i+1]);
				g[i+1][max(j,n-k+1)][k-1]=min(g[i+1][max(j,n-k+1)][k-1],g[i][j][k]+y[i+1]);
			}
	memset(ans.dat,0x3f,sizeof ans.dat);
	memset(a.dat,0x3f,sizeof a.dat);
	for(ll i=0;i<=2*n;i++)
	{
		for(ll j=max(0ll,i-n);j<=min(2*n,i+n);j++)
		{
			for(ll k=0;k<=i;k++)
			{
				a.dat[i][j]=min(a.dat[i][j],g[n][k][j-i+n]);
			}
		}
		ans.dat[i][i]=0;
	}
	while(m)
	{
		if(m&1) ans=ans*a;
		a=a*a;
		m>>=1;
	}
	printf("%lld",ans.dat[0][0]);
	return 0;
}//
```

---

## 作者：MyukiyoMekya (赞：2)


这题可以出个加强版，这里有一个时间复杂度 $\mathcal O(n\log n)$ 的做法，基于[comment-719265](https://codeforces.com/blog/entry/9070?#comment-719265)。

设 $($ 为 $+1$, $)$ 为 $-1$ ，对每个 $\mod n = i$ 的位置上的括号拿出来考虑,发现要使得它尽可能合法,那么一定是先左括号再右括号,就是形如 $\texttt{(((((....)))))}$。

那么还是贪心。

我们假设一开始全部都是左括号，然后肯定是贪心先换更换代价更小的右括号。那么就先按更换代价排个序,然后从后往前能填就填。能否填的判定条件就是前缀和 $\min < 0$。

我们需要一些快速的方法来维护，有点小麻烦，我们先来挖掘一些性质。

首先是每个 $\mod n = i$ 的位置形如 $\texttt{(((((....)))))}$ ，然后我们把原序列称为 $m$ 段，设 $G_i$ 表示第 $i$ 段的和，那么 $G$ 的前缀和一定是先增后减的，可以类比凸函数加起来一定是个凸函数。那么由此我们设 $S_i$ 表示括号序列前 $i$ 个的和，那么 $S_{x},S_{n+x},S_{2n+x},\cdots $ 也是个先增后减的。所以说我们只需要维护每个 $x$ 的两个最低点就好了。设右括号填的个数是 $v$ ，那么可以列出来 $n$ 个不等式求 $v$ 的上界。注意上界取到 $m$ 的时候要特判第一块，因为 $S_{0\sim n-1}$ 可能会小于 0，或者说就是这些凸函数都有两个最低点，最前面的块就是最前面的最低点。

哦，还有，对于 $0\le i < n$ 贪心加右括号时，$v$ 对 $0\sim i-1$ 和 $i\sim n-1$ 的最后一段的前缀和有个 $O(1)$ 的差距，分别处理一下就好了。 

所以说，开两棵线段树维护 $S_{0\sim n-1}$ 和 $S_{(m-1)n\sim mn-1}$ ，然后支持区间 $\min$ 和区间加就好了。

二次元 @加藤惠 先生有一个 nb 的结论：在 $n$ 为偶数的时候，第 $i(0\le i < n)$ 的位置填的右括号个数一定是下面之一：$0,m-1,m$ ，我不会证。

```cpp
// This code wrote by chtholly_micromaker(Myukiyomekya)
#include <bits/stdc++.h>
#define reg
#define int long long
#define ALL(x) (x).begin(),(x).end()
#define mem(x,y) memset(x,y,sizeof x)
#define sz(x) (int)(x).size()
#define ln putchar('\n')
#define lsp putchar(32)
#define pb push_back
#define MP std::make_pair
#define MT std::make_tuple
#ifdef _LOCAL_
#define dbg(x) std::cerr<<__func__<<"\tLine:"<<__LINE__<<' '<<#x<<": "<<x<<"\n"
#define dprintf(x...) std::fprintf(stderr,x)
#else
#define dbg(x) 42
#define dprintf(x...) 42
#endif
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,b,a) for(int i=(b);i>=(a);--i)
typedef std::pair<int,int> pii;
typedef std::vector<int> poly;
template <class t> inline void read(t &s){s=0;
signed f=1;char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();;s*=f;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
static int buf[50],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');}
inline void setIn(std::string s){freopen(s.c_str(),"r",stdin);return;}
inline void setOut(std::string s){freopen(s.c_str(),"w",stdout);return;}
inline void setIO(std::string s=""){setIn(s+".in");setOut(s+".out");return;}
template <class t>inline bool ckmin(t&x,t y){if(x>y){x=y;return 1;}return 0;}
template <class t>inline bool ckmax(t&x,t y){if(x<y){x=y;return 1;}return 0;}
inline int lowbit(int x){return x&(-x);}
const int MaxN=1e6+50;
const int inf=1e18;
int a[MaxN],p[MaxN],n,m;
struct SegTR
{
#define lson (u<<1)
#define rson (u<<1|1)
	int a[MaxN<<2],lazy[MaxN<<2];
	inline void pushup(int u){a[u]=std::min(a[lson],a[rson]);}
	inline void buildtr(int u,int l,int r,int base=0)
	{
		if(l==r)return a[u]=l+base,void();
		int mid=(l+r)>>1;
		buildtr(lson,l,mid,base),buildtr(rson,mid+1,r,base),pushup(u);
	}
	inline void Add(int u,int k){a[u]+=k,lazy[u]+=k;}
	inline void pushdown(int u){
		if(lazy[u])Add(lson,lazy[u]),Add(rson,lazy[u]),lazy[u]=0;}
	inline void modify(int u,int l,int r,int ql,int qr,int k)
	{
		if(ql>qr)return;
		if(ql<=l&&r<=qr)return Add(u,k);
		pushdown(u);
		int mid=(l+r)>>1;
		if(ql<=mid)modify(lson,l,mid,ql,qr,k);
		if(mid<qr)modify(rson,mid+1,r,ql,qr,k);
		pushup(u);
	}
	inline int ask(int u,int l,int r,int ql,int qr)
	{
		if(ql>qr)return inf;
		if(ql<=l&&r<=qr)return a[u];
		pushdown(u);
		int mid=(l+r)>>1;
		if(ql>mid)return ask(rson,mid+1,r,ql,qr);
		if(mid>=qr)return ask(lson,l,mid,ql,qr);
		return std::min(ask(lson,l,mid,ql,qr),ask(rson,mid+1,r,ql,qr));
	}
}pre,suf;
signed main(void)
{
	read(n,m);
	int x,ans=0;
	rep(i,1,n)read(a[i]),ans+=a[i]*m;
	rep(i,1,n)read(x),a[i]=x-a[i],p[i]=i;
	std::sort(p+1,p+n+1,[&](int x,int y){return a[x]<a[y];});
	pre.buildtr(1,1,n),suf.buildtr(1,1,n,n*(m-1));
	rep(i,1,n)
	{
		int pos=p[i];
		int ret=std::min(suf.ask(1,1,n,1,pos-1)/2+1,suf.ask(1,1,n,pos,n)/2);
		ckmin(ret,m);
		if(pre.ask(1,1,n,pos,n)<=1)ckmin(ret,m-1);
		if(ret)
		{
			ans+=ret*a[pos];
			suf.modify(1,1,n,1,pos-1,-(ret-1)*2),
			suf.modify(1,1,n,pos,n,-ret*2);
			if(ret==m)pre.modify(1,1,n,pos,n,-2);
		}
	}
	write(ans),ln;
	return 0;
}

```

---

## 作者：xcxcli (赞：2)

[链接](https://www.luogu.com.cn/problem/CF351C)

容易得到 $O(nm)$ 的 dp 方程 $f_{j,i}=\begin{cases}\min(f_{j-1,i+1}+L_j,f_{j-1,i-1}+R_j)&i>0\\f_{j-1,1}+R_j&i=0\end{cases}$，其中 $f_{j,i}$ 表示到第 $j$ 个位置、有 $i$ 个左括号未被匹配的最小代价，$L_j,R_j$ 分别表示此时加上左右括号的代价。$f_{0,0}=0,f_{0,i}=+\infty(i>0)$。

我们可以类似矩阵乘法一样定义向量 $B_n$ 与矩阵 $S_{n,n}$ 的乘法 $*$：

> 向量 $A=S*B$，其中 $A_i=\min\limits_{j=0}^wS_{i,j}+B_j$。

我们希望定义 $S*T$ 使得 $A=S*(T*B)=(S*T)*B$。由于 $A_i=\min\limits_{j=0}^w(S_{i,j}+\min\limits_{k=0}^w(T_{j,k}+B_k))=\min\limits_{k=0}^w(\min\limits_{j=0}^w(S_{i,j}+T_{j,k})+B_k)$，那么我们如下定义即可满足上面条件：

> $(S*T)_{i,k}=\min\limits_{j=0}^w(S_{i,j}+T_{j,k})$ 

因为 $\forall B$，一方面 $R*(S*(T*B))=R*((S*T)*B)=(R*(S*T))*B$，另一方面 $R*(S*(T*B))=(R*S)*(T*B)=((R*S)*T)*B$，可以得到：

> $R*(S*T)=(R*S)*T$

即 $*$ 满足结合律，于是我们可以使用快速幂来计算它。

对于本题，显然 $A=\begin{bmatrix}f_{j,0}\\f_{j,1}\\\vdots\\f_{j,w}\end{bmatrix},S_j=\begin{bmatrix}+\infty&R_j&+\infty&\cdots&+\infty\\L_j&+\infty&R_j&&\vdots\\+\infty&L_j&+\infty\\\vdots\\+\infty&\cdots\end{bmatrix},B=\begin{bmatrix}f_{j-1,0}\\f_{j-1,1}\\\vdots\\f_{j-1,w}\end{bmatrix}$。

最终答案 $ans=((S_{n-1}*\cdots*S_0)^m*\begin{bmatrix}0\\+\infty\\\vdots\\+\infty\end{bmatrix})_{0}=(S_{n-1}*\cdots*S_0)^m_{0,0}$。

---

剩下的问题就是 $w$ 需要取多少，根据原 CF Tutorial 的说法，$w$ 取 $2n$，但 $w$ 只用取到 $n$ 就能过，但我不会证/kel，大家可以看看[这里](https://codeforces.com/blog/entry/9070)下面的一个评论 comment-147879，不知道对不对。

细节：$ans$ 最大能到 $10*20*10^7=2*10^9$，如果不使用 unsigned int 或 long long，需使用 $-1$ 作为 $+\infty$。

```cpp
#include<stdio.h>
#define int unsigned int
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-48,c=getchar();
	return k;
}
void Min(int&x,int y){x=x<y?x:y;}
int n,m,w,a[21],b[21],f[21][21];
struct Mat{
	int x[21][21];
	Mat operator*(const Mat&b)const{
		Mat a;
		for(int i=0;i<=n;++i)for(int j=0;j<=n;++j){
			a.x[i][j]=2e9;
			for(int k=0;k<=n;++k)Min(a.x[i][j],x[i][k]+b.x[k][j]);
		}
		return a;
	}
}A,B;
Mat Pow(Mat x,int a){
	Mat s(x);--a;
	while(a){
		if(a&1)s=s*x;
		x=x*x,a>>=1;
	}
	return s;
}
void Get(int a,int b){for(int i=0;i<=n;++i)A.x[i+1][i]=a,A.x[i][i+1]=b;}
signed main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	n=rd(),m=rd();
	for(int i=0;i<n;++i)a[i]=rd();
	for(int i=0;i<n;++i)b[i]=rd();
	for(int i=0;i<=n;++i)for(int j=0;j<=n;++j)A.x[i][j]=2e9;
	Get(a[0],b[0]),B=A;
	for(int i=1;i<n;++i)Get(a[i],b[i]),B=A*B;
	B=Pow(B,m),printf("%u\n",B.x[0][0]);
	return 0;
}
```

另外，本题数据可加强到 $n\le100,m\le1*10^{18},0\le a_i,b_i<10^9+7$，答案膜 $10^9+7$。


---

## 作者：sSkYy (赞：1)

# [CF351C Jeff and Brackets](https://www.luogu.com.cn/problem/CF351C)

> 广义矩阵加速 DP

## 题意

构造一个长度为 $n×m$ 的合法括号序列。

第 $i$ 个位置上的左括号代价为 $a_{i\bmod n}$，右括号代价为 $b_{i\bmod n}$。
​
求最小代价。（$1\leq n\leq 20,1\leq m\leq 10^7$）

## 题解

我们设 $f_{i,j}$ 为到第 $i$ 的位置、有 $j$ 个左括号未被匹配的最小代价。

显然有：

$$
f_{i,j}=
\left\{
\begin{aligned}
&\min ( f_{i-1,j-1}+a_{i\bmod n},f_{i-1,j+1}+b_{i\bmod n} )&j>0\\
&f_{i-1,1}+b_{i\bmod n}&j=0
\end{aligned}
\right.
$$

其中 $f_{0,0}=0,f_{0,j}=+\infin(j\neq 0)$。

这里有一个很关键的性质，就是 $j\leq n$。

> 证明（口胡版）：若有一段 $n+1$ 个连续的左括号，已经覆盖了模 $n$ 意义下的所有下标，那么一定存在一个右括号能与对应模 $n$ 下的下标相同的左括号交换，满足交换后序列仍然合法，且代价不变。

因此时间复杂度是 $O(n^2m)$ 的。

---

考虑优化。

发现转移是存在周期的，周期为 $n$，即模 $n$ 意义下相同的 $i$ 对应的转移方程形式上是一样的，所以各个周期内的转移方程是一样的，可以用矩阵加速。

> 形式上，在第一个周期内，将 $f_{i,0},f_{i,1},\dots,f_{i,n}$ 打包成一个向量 $A$，将转移抽象成一个矩阵，那么你就可以求出 $0 \rightarrow n$ 的转移矩阵 $T$，又因为总长度恰好是 $n\times m$，所以答案就在 $T^m$ 中。 

具体的，对于第一周期 $0\rightarrow n$，我们设 
$$
A_i=
\begin{bmatrix}
f_{i,0}\\f_{i,1}\\\vdots\\f_{i,n}
\end{bmatrix},
M_i=
\begin{bmatrix}
+\infty&b_i & +\infty & \cdots & +\infty \\
a_i &+ \infty & b_i  & +\infty & \vdots \\
+\infty & a_i & +\infty & b_i\\
\vdots & +\infty & a_i &\ddots\\
+\infty & \cdots
\end{bmatrix}
$$

定义 $(\min,+)$ 为 广义矩阵乘法 $A_{i,j}*B_{i,j}$，其中 $C_{i,j}=\min_{k=0}^{n} (A_{i,k} + B_{k,j})$。

则前面的转移方程可表示为 $A_i=M_i*A_{i-1}$。

进一步的，有 $A_{n}=M_{n-1}*\dots*M_2*M_1*A_0$。

根据各个周期转移方程相同，有 
$$
A_{2n}=M_{n-1}*\dots*M_2*M_1*A_n\\A_{3n-1}=M_{n-1}*\dots*M_2*M_1*A_{2n}\\ \dots
$$

联立起来得到：$A_{mn}=(M_{n-1}*\dots*M_2*M_1)^m*A_0$

其中 $A_0=\begin{bmatrix}
0\\+\infin\\\vdots\\+\infin
\end{bmatrix}$，答案为 $f_{mn,0}=(M_{n-1}*\dots*M_2*M_1)^m_{0,0}$。

用矩阵快速幂计算即可，时间复杂度为 $O(n \log m)$。

## 代码

代码使用了封装矩阵和保险防越界的写法，直观易读。

`long long` 建议怕爆就全开，反正没有 `MLE` 的风险。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N=25;
const int INF=1e18;

int n,m;
int a[N],b[N];

struct mat{
    int m[N][N];
    
    int* operator [] (size_t i) {return m[i];}
    const int* operator [] (size_t i) const {return m[i];}

    mat() {for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) m[i][j]=INF;}
    mat operator * (const mat& b) const {
        mat res;
        for(int i=0;i<=n;i++)
            for(int k=0;k<=n;k++){
                if(m[i][k]==INF) continue;
                const int a=m[i][k];
                for(int j=0;j<=n;j++) res[i][j]=min(res[i][j],a+b[k][j]);
            }
        return res;
    }
    mat operator ^ (int b) const {
        mat res,a=(*this);
        res.init();
        while(b){
            if(b&1) res=res*a;
            a=a*a,b>>=1;
        }
        return res;
    }
    void init(){
        for(int i=0;i<=n;i++) 
            for(int j=0;j<=n;j++)
                if(i==j) m[i][j]=0;
                else m[i][j]=INF; 
    }
    void build(int a,int b){for(int i=0;i<=n;i++) m[i+1][i]=a,m[i][i+1]=b;}
};

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];

    mat M,T;
    T.init();
    for(int i=0;i<n;i++){
        M.build(a[i],b[i]);
        T=M*T;
    }
    cout<<(T^m)[0][0];
    return 0;
}
```

---

## 作者：lilong (赞：0)

设 $f_{i,j}$ 表示前 $i$ 位，还有 $j$ 个左括号未匹配，则有转移：

$$
f_{i,j}=f_{i,j+1}+b_i,j=0\\
f_{i,j}=\min(f_{i,j-1}+a_i,f_{i,j+1}+b_i),j>0\\
$$

由于 $a,b$ 的循环周期是 $n$，故最多有效的未匹配的左括号是 $n$ 个（再多就重复了），只需要考虑 $f_{i,0},f_{i,1},\cdots,f_{i,\min(i,n)}$。根据广义矩阵乘法的定义，上述转移可以写成广义矩阵乘法形式：

$$
\left[
\begin{array}{}
 f_{i,0}\\
 f_{i,1}\\
 \vdots\\
 f_{i,n}
\end{array}
\right]
=
\left[
\begin{array}{}
+\infty & b_i & +\infty & \cdots & +\infty\\
a_i & +\infty & b_i & \cdots & +\infty\\
+\infty & a_i & +\infty & \cdots & +\infty\\
\vdots & \vdots & \ddots & \vdots & \ddots\\
+\infty & \cdots & a_i & +\infty & b_i\\
+\infty & \cdots & +\infty & a_i & +\infty\\
\end{array}
\right]

\left[
\begin{array}{}
 f_{i-1,0}\\
 f_{i-1,1}\\
 \vdots\\
 f_{i-1,n}
\end{array}
\right]
$$

其中 $a_i,b_i$ 在最靠近对角线的两条直线上。由于广义矩阵对乘法满足结合律，故可以做到 $O(n^3\log m)$。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define inf 1e18
#define N 25
#define int long long
using namespace std;
int n,m,a[N],b[N];
struct Matrix{
    int mat[N][N];
    Matrix(){
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                mat[i][j]=inf;
        return;
    }
    Matrix operator*(Matrix A){
        Matrix C;
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)
                for(int k=0;k<=n;k++)
                    C.mat[i][j]=min(C.mat[i][j],mat[i][k]+A.mat[k][j]);
        return C;
    }
}Y;
Matrix qp(Matrix A,int b){
    Matrix C;
    for(int i=0;i<=n;i++)
        C.mat[i][i]=0;
    while(b){
        if(b&1)C=C*A;
        b>>=1;
        A=A*A;
    }
    return C;
}
signed main(){
    cin>>n>>m;
    for(int i=0;i<=n;i++)
        Y.mat[i][i]=0;
    for(int i=0;i<n;i++)
        cin>>a[i];
    for(int i=0;i<n;i++)
        cin>>b[i];
    for(int i=0;i<n;i++){
        Matrix X;
        for(int j=0;j<n;j++){
            if(j+1<=n){
                X.mat[j+1][j]=a[i];
                X.mat[j][j+1]=b[i];
            }
        }
        Y=X*Y;
    }
    Y=qp(Y,m);
    cout<<Y.mat[0][0];
    return 0;   
}
```

---


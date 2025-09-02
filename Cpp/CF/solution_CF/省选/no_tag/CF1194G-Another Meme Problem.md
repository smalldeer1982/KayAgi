# Another Meme Problem

## 题目描述

CF1194G 另一个MEME问题  
称一个分数$\frac xy$“优秀”指存在至少一个分数$\frac{x'}{y'}=\frac x y$，
$1\le x',y'\le9$且$x$和$y$的十进制表示法中分别包含$x'$和$y'$。例如，$\frac{26}{13}$是“优秀”的，因为$\frac{26}{13}=\frac21$。  
你的任务是计算当$1\le x,y\le n$时有多少“优秀”的分数$\frac xy$。由于答案可能很大，因此你只需输出答案对$998244353$取模后的值。

## 说明/提示

$1\le n<10^{100}$（记得用高精度）

## 样例 #1

### 输入

```
42
```

### 输出

```
150
```

## 样例 #2

### 输入

```
3141592653589793238462643383279
```

### 输出

```
459925407
```

# 题解

## 作者：_edge_ (赞：2)

贡献官方题解。

对于任意一个好的分数 $\dfrac{x}{y}$ 一定能够变成一个**不可约**分数 $\dfrac{a}{b}$，请注意，这里的 $\dfrac{a}{b}$ 不是题面的 $\dfrac{x'}{y'}$。

那么我们尝试枚举这个不可约分数 $\dfrac{a}{b}$，最终答案一定是变成 $\dfrac{za}{zb}$，然后我们需要统计的就是这个 $z$ 的贡献。

现在我们可以数位 DP 了，由于该题有大整数乘上一个小于 $10$ 的数，所以我们需要从低位往高位做，对于 $\le n$ 的事实上我们可以另外存一个状态 $0/1/2$ 表示已经填的位数和 $n$ 的关系。

那么我们理清楚状态，大致需要存的是位数，分子，分母的进位，以及和 $n$ 的关系。

还有一个是数码影响，由于我们枚举的是不可约分数，比如枚举的是 $\dfrac{1}{2}$ 如果很单纯的统计这个分数产生的贡献会统计不了 $\dfrac{2}{4}$ 的贡献，所以我们需要把 $\dfrac{a \times c}{b \times c}$ 也顺带统计进去，那么我们只需要把这些分数也拿出来统计他们的数码是否出现。

一点小常数优化就是可以直接枚举 $a>b$ 然后乘 $2$ 即为答案。

还有就是，这个题用超级多维 dp，所以实际上可以直接压到 map 或者哈希表里面搞。

```cpp
#include <bits/stdc++.h>
#define int long long 
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int INF=105;
const int INFN=15;
const int Mod=998244353;
string s1;
int len;
int res;
struct _node_data{
	int a1,a2,a3,b1,b3;
	// a -> 分子进位为 a1,
	// a2 (0 n>x) (1 n=x) (2 n<x)
	// a3 出现的数码 
	
	// b -> 分母进位为 b1
	// b3 为出现的数码 
	bool operator < (const _node_data &x) const {
		if (x.a1!=a1) return x.a1<a1;
		else if (x.a2!=a2) return x.a2<a2;
		else if (x.a3!=a3) return x.a3<a3;
		else if (x.b1!=b1) return x.b1<b1;
		else return x.b3<b3;
	}
};
pii num[INF];
void print(_node_data xx) {
	cout<<xx.a1<<" "<<xx.a2<<" "<<xx.a3<<" "<<xx.b1<<" "<<xx.b3<<" endl\n";
}
void solve(int l,int r) {
	vector < map <_node_data,int> >f(103);
	int tot=0;
	for (int p=1;p<=9;p++) 
		if (l*p<=9 && r*p<=9) 
			num[++tot]={l*p,r*p};
	
	f[0][{0,1,0,0,0}]=1;
	for (int i=0;i<len;i++) {
		for (auto y:f[i]) {
			auto x=y.fi;
//			cout<<x.a1<<" "<<x.a2<<" "<<x.a3<<" "<<x.b1<<" "<<x.b3<<" endl\n"; 
			for (int j=0;j<=9;j++) {
				int a1=(x.a1+j*l)/10,b1=(x.b1+j*r)/10,a2=x.a2,a3=x.a3,b3=x.b3;
				int xx=(x.a1+j*l)%10,yy=(x.b1+j*r)%10;
				if (xx>s1[i+1]-'0') a2=2;
				else if (xx<s1[i+1]-'0') a2=0;
				
				for (int q=1;q<=tot;q++)
					if (num[q].fi==xx) a3|=(1<<(q-1));
				
				for (int q=1;q<=tot;q++)
					if (num[q].se==yy) b3|=(1<<(q-1));
				f[i+1][{a1,a2,a3,b1,b3}]+=f[i][x];
				f[i+1][{a1,a2,a3,b1,b3}]%=Mod;
			}
		}
	}
	int ans=0;
	for (auto x:f[len]) {
		auto i=x.fi;
		if (i.a1 || i.b1) continue;
		if (i.a2==2) continue;
//		print(i);
//		cout<<f[len][i]<<" yiw?\n";
		for (int j=0;j<tot;j++)
			if ((i.a3>>j)&1 && (i.b3>>j)&1)	{
				ans+=f[len][i],ans%=Mod;
				break;
			}
	}
	res+=ans*2%Mod;res%=Mod;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>s1;len=s1.size();s1=" "+s1;
	for (int i=1;i<=len;i++) res=(res*10+s1[i]-'0')%Mod;
	for (int l=1,r=len;l<=r;l++,r--) swap(s1[l],s1[r]);
//	solve(2,1);
	for (int x=1;x<=9;x++) {
		for (int y=1;y<x;y++) {
			if (__gcd(x,y)>1) continue;
			solve(x,y);
		}
	}
	cout<<res<<"\n";
	return 0;
}
```


---

## 作者：Purslane (赞：2)

# Solution

考虑 $\dfrac{x}{y}$ 的**实际值**的情况总数是非常小的，我们可以枚举它。值得注意的是，虽然最终 $\dfrac{6}{9}$ 看起来和 $\dfrac{2}{3}$ 完全一样，但是有些数对可能只能对应其中的一个。因此我们可以把本质相同的数归为一类。

然后考虑如果 $\dfrac{x}{y}=\dfrac{p}{q}$，其中 $p$ 和 $q$ 是互质的整数，那么必定可以把 $(x,y)$ 写成 $(pt,qt)$ 的形式，其中 $t \in \mathbb{N+}$。那么考虑枚举 $t$。

> 我原先考虑枚举 $x$，让它乘上 $\dfrac{q}{p}$，后来发现这是相当愚蠢的。因为人在算术的时候，除法是从高位往低位进行的，乘法是从低位往高位进行的，二者不能达成共识。

然后设计一个比较 simple 的数位 Dp。设 $dp_{len,s_1,s_2,flg,S_1,S_2}$ 表示考虑了 $t$ 的最后 $len$ 位，两个数（$p$ 和 $q$）对下一位的进位分别是 $s_1$ 和 $s_2$，其中较大者的当前后 $len$ 位是否超过了 $n$ 的当前后 $len$ 位，$p$ 和 $q$ 中出现过的数集分别是 $S_1$ 和 $S_2$ 的方案数。但是，不太能过的了，因为你这样需要记录 $2^{18}$ 个信息。

然后你发现 $x=y$ 的情况必然是对的，因此我们可以钦定 $p<q$，而且这时候我们只想出现的情况数不超过 $4$ 对。那么我们只需要记录 $2^8$ 个信息。但是别急，我们发现，如果有一对匹上了，我们就不用管了。因此实际上每一对也只有 $3$ 种情况。因此你就可以把信息量改成 $3^4$ 种。（这个进一步优化参考了别人的题解，orz）

卡卡常应该能过。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+5,MOD=998244353;
int v,ans,len,dp[MAXN][10][10][2][100];
string n;
int m,ud,pw[100];
pair<int,int> pq[MAXN];
int add(int st,int v1,int v2) {
	if(st==ud) return ud;
	ffor(i,1,m) {
		if(v1==pq[i].first) {
			if(st/pw[i-1]%3==0) st+=pw[i-1];
			else if(st/pw[i-1]%3==2) return ud;
		}
		if(v2==pq[i].second) {
			if(st/pw[i-1]%3==0) st+=2*pw[i-1];
			else if(st/pw[i-1]%3==1) return ud;
		}
	}
	return st;
}
void solve(int p,int q) {
	memset(dp,0,sizeof(dp));
	m=9/q; ffor(x,1,9/q) pq[x]={x*p,x*q};
	ud=pw[m];
	ffor(i,0,9) dp[len][i*p/10][i*q/10][(i*q%10>n[len]-'0')][add(0,i*p%10,i*q%10)]++;
	roff(i,len,2) {
		ffor(s1,0,8) ffor(s2,0,8) ffor(tag,0,1) ffor(st,0,ud) ffor(nw,0,9) dp[i-1][(nw*p+s1)/10][(nw*q+s2)/10][(((nw*q+s2)%10)>(n[i-1]-'0'))|(((nw*q+s2)%10)==(n[i-1]-'0')&&tag)][add(st,(nw*p+s1)%10,(nw*q+s2)%10)]+=dp[i][s1][s2][tag][st];
		ffor(s1,0,8) ffor(s2,0,8) ffor(tag,0,1) ffor(st,0,ud) dp[i-1][s1][s2][tag][st]%=MOD;
	}
	ans=(ans+dp[1][0][0][0][ud])%MOD;
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n,n="&0"+n,len=n.size()-1;
	pw[0]=1,pw[1]=3,pw[2]=9,pw[3]=27,pw[4]=81;
	ffor(x,1,9) ffor(y,x+1,9) if(__gcd(x,y)==1) solve(x,y);
	ffor(i,1,len) v=(v*10+n[i]-'0')%MOD;
	ans=(ans*2+v)%MOD;
	cout<<ans;
	return 0;
}
```

---

## 作者：ax_by_c (赞：0)

首先肯定考虑枚举 $(x',y')$，但是一个数可能对应多个 $(x',y')$，这是无法避免的。怎么办呢？考虑枚举最简的 $(X,Y)$，发现除了 $(1,1)$ 之外最多只有 $4$ 种可能的 $(x',y')$。而 $(1,1)$ 即为两数相同，直接给答案加上 $n$ 即可。

接下来考虑数位 DP，只需设计条件来判断 $\frac{x}{y}=\frac{X}{Y}$ 和出现可能的 $(x',y')$ 即可。

对于第一个条件，考虑记 $s=xY-Xy$，则 $s=0$ 等价于 $\frac{x}{y}=\frac{X}{Y}$。如果是从低位到高位 DP 的话，只要每个时刻 $s$ 的个位都为零且最后为零即可。不难发现在任意时刻 $s\in[-100,100]$。

对于第二个条件，考虑记出现过的 $x',y'$，但是这样是 $2^8$。但是只要出现一对 $(x',y')$ 就不用记了，所以是 $3^4$。

计算一下状态数，能过。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll mod=998244353;
const int N=105;
const int M=5;
const int S=105;
const int V=200;
int n,xs[M],ys[M],m;
int msk,s1[S],s2[S],sid[S][S];
char aa[N];
ll ans,rem[N][V][S][2][2];
ll dfs(int u,int x,int y,int sm,int s,bool vis1,bool vis2){
	if(!u){
		if(!sm&&s==-1&&!vis1&&!vis2)return 1;
		return 0;
	}
	if(rem[u][sm+100][s+1][vis1][vis2]!=-1)return rem[u][sm+100][s+1][vis1][vis2];
	ll ans=0;
	rep(x_,0,9)rep(y_,0,9){
		int sm_=sm+x_*y-y_*x;
		if(sm_%10)continue;
		int s_=s;
		if(s_!=-1){
			int sx_=s1[s_],sy_=s2[s_];
			rep(i,1,m)if(x_==xs[i])sx_|=(1<<(i-1));
			rep(i,1,m)if(y_==ys[i])sy_|=(1<<(i-1));
			if(sx_&sy_)s_=-1;
			else s_=sid[sx_][sy_];
		}
		bool vis1_=vis1,vis2_=vis2;
		if(x_<aa[u]-'0')vis1_=0;
		if(x_>aa[u]-'0')vis1_=1;
		if(y_<aa[u]-'0')vis2_=0;
		if(y_>aa[u]-'0')vis2_=1;
		ans=(ans+dfs(u-1,x,y,sm_/10,s_,vis1_,vis2_))%mod;
	}
	return rem[u][sm+100][s+1][vis1][vis2]=ans;
}
void slv(){
	scanf("%s",aa+1);
	for(int i=1;aa[i];i++)n=i;
	rep(i,1,n)ans=(ans*10+aa[i]-48)%mod;
	rep(x,1,9)rep(y,1,9){
		if(!(x==1&&y==1)&&__gcd(x,y)==1){
			m=0;
			xs[++m]=x,ys[m]=y;
			while(xs[m]+x<=9&&ys[m]+y<=9)m++,xs[m]=xs[m-1]+x,ys[m]=ys[m-1]+y;
			msk=0;
			rep(i,0,(1<<m)-1)rep(j,0,(1<<m)-1)if(!(i&j))msk++,s1[msk]=i,s2[msk]=j;
			rep(i,1,msk)sid[s1[i]][s2[i]]=i;
			rep(a1,0,n+1)
			rep(a2,-100,100)
			rep(a3,-1,msk)
			rep(a4,0,1)
			rep(a5,0,1)
			rem[a1][a2+100][a3+1][a4][a5]=-1;
			ans=(ans+dfs(n,x,y,0,0,0,0))%mod;
			rep(i,1,msk)sid[s1[i]][s2[i]]=0;
		}
	}
	printf("%lld\n",ans);
}
void main(){
	int T=1;
//	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	string __name="";
	if(__name!=""){
		freopen((__name+".in").c_str(),"r",stdin);
		freopen((__name+".out").c_str(),"w",stdout);
	}
	ax_by_c::main();
	return 0;
} 
```

---

## 作者：TJmyf (赞：0)

### 完全没思路的可学习[数位 DP](https://oi-wiki.org/dp/number/)。

这里我们使用一下按比设 $k$ 的思想，在枚举 $x'$ 和 $y'$ 的情况下去 DP 求 $g=\frac x{x'}=\frac y{y'}$ 的方案数，这样一定能满足 $\frac xy=\frac {x'}{y'}$。

显然计算时要满足第二个条件，在 $x$ 中出现 $x'$ ，在 $y$ 中出现 $y'$ ，这个需要加到 DP 里当作状态去求。

但是我们考虑到 $\frac{42}{21}$ 这个好数，这里他既能被 $x'=2,y'=1$ 算一次，又能被 $x'=4,y'=2$ 算一次，所以考虑把比值相等的一起算，只要满足一组 $x',y'$ 即可。

设计数位 DP 状态： $f_{i,s_0,s_1,s_2,s_3,s_4}$ ，其中 $i$ 代表从低到高枚举到了第 $i$ 位， $s_0$ 代表和上界的关系（ $0$ 代表小于上界， $1$ 代表等于上界， $2$ 代表大于上界）， $s_1$ 代表 $g×x$ 的进位，$s_2$ 代表 $g×x$ 已经出现了那些数字的装压状态， $s_3$ 代表 $g×y$ 的进位，$s_4$ 代表 $g×y$ 已经出现了那些数字的装压状态。

我们发现任意 $x<y$ 的好数，都有唯一与之对应的 $x>y$ 的好数，所以我们可以算一半，当然 $x=y$ 都是好数，再加上即可。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=110,p=998244353; 
inline int gcd(int X,int Y){return Y?gcd(Y,X%Y):X;}
int n,ans,a[maxn],upr[maxn];
char str[maxn];
struct node
{
	int s[5];
	//s0=0代表低位小于界限，s0=1代表低位等于界限，s0=2代表低位大于界限 
	//s1代表第一个数的进位
	//s2代表第一个数出现的数码
	//s3代表第二个数的进位
	//s4代表第二个数出现的数码
	node(int *S){for(int i=0;i<5;i++) s[i]=S[i];}
	node(int A,int B,int C,int D,int E){s[0]=A,s[1]=B,s[2]=C,s[3]=D,s[4]=E;}
};
inline bool operator < (node X,node Y)
{
	for(int i=0;i<5;i++) if(X.s[i]!=Y.s[i]) return X.s[i]<Y.s[i];
	return 0;
}
map<node,int> f,nf;
inline int solve(int u,int v)
{
	memset(upr,0,sizeof(upr));
	int sy=0;
	for(int i=n;i>=1;i--)//除法算上界，sy剩余 
	{
		sy=sy*10+a[i];
		if(sy>=v) upr[i]=sy/v,sy%=v;
	}
	int use[3][10];
	memset(use,0x3f,sizeof(use));
	int siz=0;
	for(int i=1;i<10;i++) if(v*i<10) use[1][u*i]=i-1,use[2][v*i]=i-1,siz++;
	f.clear();
	f[node(1,0,0,0,0)]=1;
	for(int i=0;i<n;i++)
	{
		for(pair<node,int> zt:f)
		{
			int s[5],ns[5];
			for(int j=0;j<5;j++) s[j]=zt.first.s[j];
			for(int j=0;j<10;j++)
			{
				if(j>upr[i+1]) ns[0]=2;
				else if(j<upr[i+1]) ns[0]=1;
				else ns[0]=s[0];
				//第一个数g*x 
				int np=s[1]+j*u;
				ns[1]=np/10;
				np%=10;
				ns[2]=s[2];
				if(use[1][np]<10) ns[2]|=(1<<use[1][np]);
				//第二个数g*y 
				np=s[3]+j*v;
				ns[3]=np/10;
				np%=10;
				ns[4]=s[4];
				if(use[2][np]<10) ns[4]|=(1<<use[2][np]);
				nf[node(ns)]=(nf[node(ns)]+zt.second)%p;
			}
		}
		f=nf;
		nf.clear();
	}
	int res=0;
	for(int i=1;i<(1<<siz);i++)
		for(int j=1;j<(1<<siz);j++)
			if(i&j)
				res=(0ll+res+f[{0,0,i,0,j}]+f[{1,0,i,0,j}])%p;
	return res;
}
int main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	reverse(str+1,str+n+1);
	for(int i=1;i<=n;i++) a[i]=str[i]-'0';
	for(int x=1;x<10;x++)
	{
		for(int y=x+1;y<10;y++)
		{
			if(gcd(x,y)!=1) continue;
			ans=(ans+solve(x,y))%p;
		}
	}
	ans=(ans+ans)%p;
	int m10=1;
	for(int i=1;i<=n;i++) ans=(ans+1ll*m10*a[i])%p,m10=m10*10ll%p;
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：_lbw_ (赞：0)

可能有的人（比如我）看到这个限制觉得很震惊啊，这不直接写最简就行了吗。

但是还有一个限制就是说 $x$ 里面必须有 $x'$，所以说我们必须对于 $x',y'\in[0,9]$ 都算。

但是这样会算重。

我们将化简完相同的 $\dfrac {x'} {y'}$ 分为一组，可以看出除了 $x'=y'$ 那一组其他的组大小 $\leq4$。

于是我们特判掉这一组，然后将其他组分别计算。

依然考虑数位 dp，这次我们先设 $x=tx',y=ty'$ 接下来可知 $t\leq \min(\dfrac n{x'},\dfrac n{y'})$ 然后只需要让 $x'\in tx',y'\in ty'$ 即可。

但这里涉及到了 $tx'$ 于是我们考虑模拟竖式乘法，所以从低位到高位计算。

记录 $f(i,\Delta x,\Delta y,S_1,S_2,p)$ 为做到第 $i$ 位，进位分别为 $\Delta x,\Delta y$，数字集合分别为 $S_1,S_2$，$p=0/1/2$ 表示当前与原数是 $<$ 还是 $=$ 还是 $>$。

这样出现一个问题 $S_1,S_2$ 太大了，但我们发现其实对于每一组只要记 $4$ 个数，但这样记录的数量还是高达 $2^8$ 次方，有什么办法呢？

我们回归 $S_1,S_2$ 的原本含义，容易发现只要有一位相同就可行了，于是我们意识到可以将状态记成这样：

$f(i,\Delta x,\Delta y,S_1,S_2,p,t)$ 别的都一样，$t$ 表示有无出现过相同位而 $S_1\cap S_2=\varnothing$。

然后我们将状态数乘上一开始枚举的组数（计算得有 $28$ 个组），将计算次数大量上估后可以得到 $28\times 100\times 10^2\times 3^4\times 3\times 2=1.3608\times 10^8$，非常可过。




---


# Banh-mi

## 题目描述

JATC很喜欢吃越式法包(一种越南食品)。他总是把它当早餐吃，因为他实在是太喜欢了。这天早上，像以往一样，他买了一个越式法包，并且决定以一种特殊的方法吃掉它。  
首先，他把越式法包分为$n$块，并把它们排成一行，从$1$到$n$标号。对于每一块，他定义第$i$块的_口感_为$x_i∈\{0,1\}$。JATC正准备将它们一个接一个地吃掉。每一次，他随意选择剩下的一块吃掉。比如说他选择了第$i$块，那么他的_愉悦度_就会增加$x_i$，并且所有剩下的块的_口感_也会增加$x_i$。最初，JATC的_愉悦度_等于0。  
举个例子，假设$3$块越式法包的_口感_分别为$[0,1,0]$。如果JATC先吃掉第二块，他的_愉悦度_会变为$1$，其余块的_口感_则变为$[1,\_,1]$。接下来如果他吃掉第一块，他的_愉悦度_会变为$2$，剩下的块的_口感_变为$[\_,\_,2]$。吃掉最后一块后，JATC的_愉悦度_变为$4$。  
然而，他不想吃掉所有的越式法包块儿，想留一些以后吃。他给了你$n$个询问，每个询问由两个整数$l_i$和$r_i$组成。对于每个询问，请告诉他当他以某种顺序吃掉区间$[l_i,r_i]$的所有块后，最大的愉悦度是多少。  
每个询问都是互相独立的。由于答案可能很大，请对$10^9+7$取模。

## 说明/提示

对第1个询问：一种最佳的方案顺序为：$1,4,3,2$。  
对第2个询问：以$3,4$或$4,3$的顺序都可以得到同样的答案。  
任何顺序都能够得到相同的答案。

## 样例 #1

### 输入

```
4 2
1011
1 4
3 4
```

### 输出

```
14
3
```

## 样例 #2

### 输入

```
3 2
111
1 2
3 3
```

### 输出

```
3
1
```

# 题解

## 作者：封禁用户 (赞：5)

## 题解：CF1062C Banh-mi

### 解题思路

在拿走一个数字后，其余数字就会加上这个数字。通过观察可得，运用**贪心**策略，每次都拿当前最大的数字就可以了。

再来看数据范围，$10^5$ 的数据，$10^5$ 次询问，明显 $O(n^2 q)$ 是过不了的。我们研究其余性质，因为初始是 $01$ 串，所以增加的必然是 $2^k$，其中 $k \in \mathbb{Z}$。下面展示了一个全部为 $1$ 的 $6$ 位数字串每次拿取得到的数字：



|第几次取|$1$|$2$|$3$|$4$|$5$|$6$|
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|**取到的数**|**$1$**|**$1+1=2$**|**$1+1+2=4$**|**$1+1+2+4=8$**|**$\cdots=16$**|**$\cdots=32$**|

总结以上两个结论，我们先取所有原本的 $1$，再取所有原本的 $0$。又因为：

$$\sum_{i=1}^{k} 2^i=2^{k+1}-1$$

所以若区间内有 $p$ 个 $1$，$q$ 个 $0$，那么我们的公式为：

$$ans=(2^p-1)*2^q$$

~~既然都讲清楚了，这两个公式我就不证了~~。由此，我们便可以**快速幂**解决以上问题，但此时复杂度仍为 $O(n t \log n)$（$n$ 为数字串长度，$t$ 为询问次数），不能通过。

我们用**前缀和**快速统计 $p$ 和 $q$ 的个数，便可将复杂度降低至 $O(n + t \log n)$。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
long long n , t , b[100005] , l , r , p , q, ansa , ansb;
bool a[100005];
string s;
long long ksm(long long a , long long b)
{
	long long cnt = 1;
	while(b)
	{
		if(b & 1)
		{
			cnt = cnt * a % 1000000007;
		}
		b >>= 1;
		a = a * a % 1000000007;
	}
	return cnt;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> t;
	cin >> s;
	for(int i = 1 ; i <= n ; i++)
	{
		if(s[i - 1] == '1')
		{
			a[i] = 1;
		}
		b[i] = b[i - 1] + a[i];
	}
	while(t--)
	{
		cin >> l >> r;
		p = b[r] - b[l - 1];
		q = r - l - p + 1;
		ansa = ksm(2 , p) - 1;
		ansb = ksm(2 , q);
		cout << ansa * ansb % 1000000007 << '\n';
	}
	return 0;
}
```

[AC 记录](https://codeforces.com/contest/1062/submission/276735115)。RMJ 爆炸时期，直接引用 CF 的记录。

---

## 作者：K_H_Z (赞：3)

## 题解: CF1062C 

[题目传送门](https://www.luogu.com.cn/problem/CF1062C)

此题是一道贪心题，明显每次选择最美味的部分吃掉，可使后续美味值最大。

为防止超时，可考虑前缀和及快速幂优化。

用一个数组记录前序数组值最初为 $1$ 的数组数量，设最后求和时的 $l$ 和 $r$ 范围内前序数组值最初为 $1$ 的累计和为 $x$。则前序数组值最初为一的答案为 $2^x-1$。而再将加上前序数组值最初为 $0$ 的和，在最初为 $0$ 的数量为 $x$ 时刚好为当前答案乘 $2^x$。以此便可以把 $O(n^2)$ 转为 $O(n)$。

最后再用快速幂将一次询问的复杂度降至 $O(\log{n})$ 便能完成。

码风不好，敬请见谅。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];
long long mod=1e9+7;//模数
long long ans;//答案
long long fast(int x,int y)//快速幂
{
	int need=1;
	if(y==0) return 1;
	while(y>1)
	{
		if(y%2) need=need%mod*x%mod;//指数为奇数时用need记录
		x=x%mod*x%mod;//底数做平方运算
		y/=2;//将指数分成两半
	}
	return x%mod*need%mod;//要小心题目卡范围，不要忘记%mod
}
int main()
{
	int n,i,m,l,r;
	string s;
	cin>>n>>m;
	cin>>s;
	for(i=0;i<n;i++)
	{
		if(s[i]=='1') a[i+1]++;//计数
		a[i+1]+=a[i];//实现前缀和
	}
	for(i=1;i<=m;i++)
	{
		ans=0;
		scanf("%d%d",&l,&r);
		ans+=fast(2,a[r]-a[l-1])-1;//一的累计和
		ans%=mod;
		ans*=fast(2,r-l-a[r]+a[l-1]+1);//零的累计和
		ans%=mod;
		//cout<<ans<<endl;
	}
	return 0;
}
```
第一次写题解，求过。

---

## 作者：szr666 (赞：3)

我这里推荐一下[我的博客](https://www.luogu.org/blog/szr666--blog/)

在博客里观看更美观哦~

[题目](https://www.luogu.org/problem/CF1062C)
------------

------------

华丽的分割线
# 解析

先用前缀和统计出以i为前缀中1的个数,则可O(1)求出[l,r]中1的个数

设x=[l,r]中1的个数=sum[r]-sum[l-1],y=[l,r]中0的个数=r-l+1-x

对于区间[l,r],将x个1放到前面,y个0放到后面

如11111100000,首先一定选择当前口感最好的,这样其他的口感也会更好

先把x个1选完,再把y个0选完,

对于x个1,第一次选1,第二次则选2(1+1),第三次为4(2+2)

一共能选x次,第x次为2^(x-1),所以选x个1的愉悦度为

1+2+4+……+2^(x-1)=2^x-1=S(根据等比数列求和公式)

对于y个0,在吃完x个1后均变为S,第一次选S,第二次则选2S(S+S),第三次为4S(2S+2S)

一共能选y次,第y次为2^(y-1)S,所以选y个0的愉悦度为

S+2S+4S+……+2^(y-1)S=(2^y-1)S=(2^y-1)(2^x-1)

所以答案为两次相加(2^y-1)(2^x-1)+2^x-1=(2^y)(2^x-1)

# 代码

```cpp
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
void read(int &x)
{
	x=0;
	int f;
	f=1;
	char c;
	c=getchar();
	while((c<'0'||c>'9')&&c!='-')
	{
		c=getchar();
	}
	if(c=='-')
	{
		c=getchar();
		f=-1;
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	x=x*f;
}
ll sum[200000];
char s[200000];
const ll p=(1e9)+7;
ll power(ll y)
{
	ll ans,x;
	ans=1;
	x=2;
	while(y!=0)
	{
		if(y&1)
		{
			ans=ans*x%p;
		}
		x=x*x%p;
		y>>=1;
	}
	return ans;
}
int main()
{
	int n,q,i,l,r;
	ll x,y;
	read(n);
	read(q);
	scanf("%s",s);
	for(i=0;i<n;i++)
	{
		sum[i+1]=sum[i]+s[i]-'0';
	}
	for(i=1;i<=q;i++)
	{
		read(l);
		read(r);
		x=sum[r]-sum[l-1];
		y=r-l+1-x;
		printf("%lld\n",((power(x)-1)*power(y))%p);
	}
}
```


---

## 作者：Suiseiseki (赞：2)

其实对于这道题我们很容易想到将1全部放在前面，将0放在后面统计。

那么很明显对于每一个$[l,r]$我们不能排序的（~~送你一车TLE~~），这是便很容易地想到前缀和来求区间$[l,r]$中1的个数。

那么问题又来了，我知道了1的个数后还是不能暴力算，必须要推出一个公式来进行$O(1)$时间复杂度的问题解答。

可以进行一系列的推理得到一个公式（~~其实我也不会推啦~~)

令区间$[l,r]$中的1的个数为$x$,令$S={2^x-1}$

那么即可得出$ans={S+(S*{(2^{r-l+1-x}-1)})}$

接下来就可以愉快地打代码啦：

```cpp
#include <cstdio>
#define Mod 1000000007
int sum[100005];
int a[100005];
int ksm(int x,int y){//快速幂，不用解释了吧
	int ans=1;
	while(y){
		if(y&1){
			ans=(int)((long long)ans*x%Mod);
		}
		y>>=1;
		x=(int)((long long)x*x%Mod);
	}
	return ans;
}
int main(){
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%1d",&a[i]);
		sum[i]+=sum[i-1]+a[i];//和数组
	}
	int l,r;
	int ans;
	while(q--){
		scanf("%d%d",&l,&r);
		ans=ksm(2,sum[r]-sum[l-1])-1;
		if(ans==-1){
			ans+=Mod;
		}
		ans=(int)(((long long)ans+((long long)ans*((ksm(2,r-l+1+sum[l-1]-sum[r])-1+Mod)%Mod))%Mod)%Mod);//可能不需要加这么多Mod的，但是我手残
		printf("%d\n",ans);//愉快地输出
	}
	return 0;
}
```

---

## 作者：zym20249_ (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF1062C)

## 题意
有 $n$ 个食物，美味程度为 $0$ 或 $1$，当你吃了一个食物后，其他没吃的食物都会增加，增加的数为你现在所吃的美味程度。输出最后你所吃的美味程度的和。有 $q$ 次查询每次要吃区间为 $[l,r]$ 的食物。

## 思路
我们利用贪心的想法，每次有先吃大的，每次查看最大的，因为吃大的会给其他的增加更多的美味程度，可以先将数组排序，但是直接枚举会超时，应使用快速幂来进行求解。

---

## 作者：OIerJiang_1017 (赞：2)

## [CF1062C 题目传送门](https://www.luogu.com.cn/problem/CF1062C)

## 题目大意
有 $n$ 份食物，编号为 $1$ 到 $n$，定义第 $i$ 份食物的美味值为 $x_i \in${$0,1$}。现在要逐个吃掉这 $n$ 份食物，在每一步中，吃掉第 $i$ 份食物则能量值将增加 $x_i$ 并且剩下的所有食物的美味程度也会增加 $x_i$。初始能量值为 $0$。有 $q$ 个查询，每个查询给定两个整数 $l$ 和 $r$，目标是查询：如果按某种顺序吃掉编号在区间 $[l,r]$ 上所有食物，获得的最大能量值是多少。所有的查询相互独立，查询的答案对 $10^9+7$ 取模后输出。

## 解决思路
拿走数字 $a$ 后，其余数字就会加上 $a$。通过观察可得，运用**贪心**策略，每次拿当前**最大**的数字即可。不过此时的时间复杂度为 $\Theta(nt \log n)$
需要用**前缀和**将复杂度降低为 $\Theta (n+t \log n)$。

## 代码展示
```cpp
#include<bits/stdc++.h>
#define ll long long
//不开long long见祖宗 
using namespace std;

const int N = 1e5 + 10;
const int mod = 1e9 + 7;
ll n, T, a[N], f[N];
string s;

ll ksm(ll a, ll b)
{
	ll mul = 1;
	while(b)
	{
		if(b % 2 == 1) mul = mul * a % mod;
		b /= 2;
		a = a * a % mod;
	}
	return mul;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> n >> T >> s;
	for(int i = 1; i <= s.size(); i++) 
	{
		if(s[i-1] == '1') f[i] = 1;
		a[i] = a[i-1] + f[i];//前缀和 
	}
	while(T--)
	{
        int l, r;
		cin >> l >> r;
		ll p = a[r] - a[l - 1];
		ll q = r - l - p + 1;
		ll a1 = ksm(2, p) - 1;
		ll a2 = ksm(2, q);
		cout << a1 * a2 % M << "\n";
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

## 思路

考虑区间内有 $i$ 个 $1$，$j$ 个 $0$，答案是多少。

有一种明显的贪心策略，就是每次选择最大的进行添加。这样才能给后面尽可能多的贡献。显然，前 $i$ 次均会使用 $1$。且每次之后 $1$ 均会翻倍。那么所有 $1$ 给出的贡献就是 $\sum_{k=0}^{i-1}2^k=2^i-1$。

同样的，考虑后面 $j$ 次选 $0$ 的贡献。前 $i$ 次会让每个 $0$ 变为 $2^i-1$，和 $1$ 那边同样的，总共贡献为 $(2^i-1)\times(2^j-1)$。

答案就是 $(2^i-1)\times 2^j$。

那么下一个问题就是统计区间内 $0/1$ 的数量。这边有三种解法：前缀和，线段树，莫队。线段树还可以支持区间 $0/1$ 的修改。下方代码为线段树解法。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
#define ls i*2
#define rs i*2+1
#define Ls ls,l,mid
#define Rs rs,mid+1,r
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
int a[100005];
struct node{
	int f0[1000005],f1[1000005];
	void build(int i,int l,int r){
		if(l==r){
			f0[i]=(a[l]==0);
			f1[i]=(a[l]==1);
			return ;
		}
		build(Ls),build(Rs);
		f0[i]=f0[ls]+f0[rs];
		f1[i]=f1[ls]+f1[rs];
	} 
	int qry0(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f0[i];
		if(ql>r||qr<l) return 0;
		return qry0(Ls,ql,qr)+qry0(Rs,ql,qr);
	}
	int qry1(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f1[i];
		if(ql>r||qr<l) return 0;
		return qry1(Ls,ql,qr)+qry1(Rs,ql,qr);
	}
}tree;
signed main(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		char c;
		cin>>c;
		a[i]=(c=='1');
	}
	tree.build(1,1,n);
	while(q--){
		int l,r;
		cin>>l>>r;
		int num0=tree.qry0(1,1,n,l,r),num1=tree.qry1(1,1,n,l,r);
		cout<<(qp(2,num1)-1)*(qp(2,num0))%mod<<endl;
	}
	return 0;
}
```

---


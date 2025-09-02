# AquaMoon and Chess

## 题目描述

你有一个长为 $n$ 的棋盘,这个棋盘上有一些棋子,你可以进行如下操作:

如果第 $i + 2$ 个位置是空的,且第 $i + 1$ 个位置非空,则可以将第 $i$ 个位置的棋子挪到第 $i + 2$ 个位置 ($i + 2 \leq n$).

如果第 $i - 2$ 个位置是空的,且第 $i - 1$ 个位置非空,则可以将第 $i$ 个位置的棋子挪到第 $i - 2$ 个位置 ($i - 2 \geq 1$).

现在将给出一个棋盘的初始状态,求可以通过上述操作可以到达的状态数,你可以进行任意次操作,答案对 $998244353$ 取模.

## 样例 #1

### 输入

```
6
4
0110
6
011011
5
01010
20
10001111110110111000
20
00110110100110111101
20
11101111011000100010```

### 输出

```
3
6
1
1287
1287
715```

# 题解

## 作者：lanos212 (赞：22)

首先考虑最基础的地方，1 在棋盘中是怎么移动的。

![](https://cdn.luogu.com.cn/upload/image_hosting/bnxnc25t.png)

跳来跳去看起来有些繁琐，我们考虑对操作进行简化:

![](https://cdn.luogu.com.cn/upload/image_hosting/ipbw7470.png)

这样操作就变成了 **选择连续的 11 然后左右移动**。

考虑这么一种特殊的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/apvojozq.png)

如果棋盘上都是 11，显然它们都可以自由左右移动，那么就可以转化成是棋盘中放若干个 11 有多少种方案，这是排列组合的模板题，如果我们把所有 11 看扁成 1，如果有 $a$ 个 1，总共有 $n$ 个格子，那么答案显然是 $\binom{n}{a}$。那么如果有 $a$ 个 11，总共有 $n$ 个格子，如果要转化成前者那就是把看扁的格子去掉，也就是 $n-a$ 个格子，答案是 $\binom{n-a}{a}$。

但是棋盘上不一定都能划分成若干个 11，那么我们就要考虑划分后留下的 1 和 11 有一些什么关系。

![](https://cdn.luogu.com.cn/upload/image_hosting/dp9hzmn0.png)

我们发现当 11 和 1 贴贴的时候，可以把 11 拆出来一个 1 和右边的 1 合并，这是一个棘手的问题，因为我们是打算把 11 看作一个整体而不可拆分的。

但是如果我们在这个步骤里加上一个中间过程，就可以避免这种现象了。

![](https://cdn.luogu.com.cn/upload/image_hosting/9ud2cq15.png)

如果看作中途 11 和 1 交换了前后位置，而不是把 11 拆了，就可以继续使用前面的整体思想了。

观察上图中的 11 其实还是在自由移动的，去掉了 1 也是可以到达原来的那些位置，但是再看上图中的第 2，3 步，虽然 11 移动了位置，但是在棋盘上 11 在 1 的前后都是同一种方案，所以也就相当于棋盘上每出现一个 1，棋盘还要去掉一个格子。

那么当有$a$ 个 11，$b$ 个 1，棋盘上有 $n$ 格的时候，还是可以按照前面特殊情况的方法得到答案，此时答案为 $\binom{n-a-b}{a}$。

完结撒花 qwq，代码太丑就不放了（）。

如果不会写组合数的计算，那么可以参考下这个公式：

$\binom{m}{n} = \frac{m!}{n!(m-n)!}$

如果不知道在取模的情况下怎么除以一个数，那么可以做下这题：

[P3811 【模板】乘法逆元](https://www.luogu.com.cn/problem/P3811)

在取模的情况下除以一个数就相当于乘上这个数的逆元。

---

## 作者：Mo_Han136 (赞：11)

[题目链接](https://www.luogu.com.cn/problem/CF1545B)

## 题目描述

给一个长为 $n$ 格的棋盘，棋盘上每格放或不放棋子，分别记为 $1$ 和 $0$ 。棋子可以越过与之相邻的一个棋子跳到另一侧的空格中，求棋盘上棋子的布局可能数。

## 题解

可以注意到一个非常明显的特点：关于一对相邻的 $1$ ，即 $11$ ,可以在棋盘上自由移动，不需要也不可能分开。

因此我们可以将棋盘上所有的 $1$ 分别看作自由移动的 $11$ 和无法 **自由移动** 的 $1$ 。

而对于相邻的奇数个 $1$ ，在他移动时，可以看做 $11$ 向前跳到下一个 $0$ 并将 $1$ 向后挤一格，如：

![UDROJ4TKB_IVM_YBM_X@5J2.png](https://i.loli.net/2021/07/20/OMZT4bhf8BYE9s1.png)

由此可见，在棋盘上， $11$ 只会跳到与之相邻或只隔1个棋子的 $0$ ，而 $1$ 在棋盘上的移动是被动的，因此影响棋盘布局的只有 $11$ 和 $0$ ，我们可以忽略 $1$ 的影响。

设 $11$ 的数量为 $a$ ， $0$ 的数量为 $b$ 。则答案就是两者的组合顺序，即 $C^a_{a+b}$ 。

## 实现

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(int i=a,i##end=b;i>=i##end;--i)
using namespace std;
bool Handsome;
const int M=1e5+5,P=998244353;
int n,F[M],INV[M];
char s[M];
int FAST(int x,int y){
	int res=1;
	for(;y;y>>=1){
		if(y&1)res=1ll*res*x%P;
		x=1ll*x*x%P;
	}
	return res;
}
void init(){
	F[0]=INV[0]=1;
	rep(i,1,1e5)F[i]=1ll*F[i-1]*i%P;
	INV[100000]=FAST(F[100000],P-2);
	drep(i,99999,1)INV[i]=1ll*INV[i+1]*(i+1)%P;
}
int C(int x,int y){return 1ll*F[x]*INV[y]%P*INV[x-y]%P;}
void solve(){
	scanf("%d%s",&n,s+1);
	int p=1,a=0,b=0;
	for(;p<=n;++p){
		if(s[p]=='1' && s[p+1]=='1'){
			++a;++p;
		}
		else if(s[p]=='0')++b;
	}
	printf("%d\n",C(a+b,b));
}
bool Most;
int main(){
//	printf("%.2lfMB\n",(&Most-&Handsome)/1024.0/1024.0);
	init();
	int t;scanf("%d",&t);
	while(t--)solve();
	return 0;
}
```

$\mathcal{By}\quad\mathcal{Most}\ \mathcal{Handsome}$

$\mathcal{2021.07.20}$

---

## 作者：Tx_Lcy (赞：8)

这是某组合数学大师给我的一道题，不得不说是一道很有意思的题。

[题目传送门](https://www.luogu.com.cn/problem/CF1545B)
## 思路
做这道题，最重要的就是发现 $\verb!11!$ 这一条性质。例如 $\verb!11010!$，可以转化出来的有：$\verb!11010!$，$\verb!01110!$，$\verb!01011!$ 三种。我们发现两个 $\verb!1!$ 始终是贴在一起的，所以我们不妨把字符串分成三个部分：$a$ 个 $\verb!1!$，$b$ 个 $\verb!11!$，$c$ 个 $\verb!0!$。我们发现 $\verb!1!$ 是跟着 $\verb!11!$ 的移动被动移动的，所以 $\verb!1!$ 在哪里对答案没有任何影响，我们只需要处理 $\verb!11!$ 和 $\verb!0!$ 的情况，我们又发现它们可以互换位置，一共有 $a+c$ 个位置，其中 $a$ 个位置要给 $\verb!11!$，那答案不就出来了，为：$C_{a+c}^{a}$。
## 代码
```cpp
//A tree without skin will surely die. 
//A man without face is invincible.
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
int const N=1e6+10;
int fac[N],inv[N],a[N];
int const p=998244353;
inline int qpow(int a,int b){
    int ans=1;
    while (b){
        if (b&1) ans*=a,ans%=p;
        a*=a,a%=p,b>>=1;
    }
    return ans;
}
inline int C(int n,int m){return fac[n]*qpow(fac[m],p-2)%p*qpow(fac[n-m],p-2)%p;}
signed main(){
    ios::sync_with_stdio(false);
    cout.tie(0),cout.tie(0);
    int T;cin>>T;
    fac[0]=1;
    for (rint i=1;i<=100000;++i) fac[i]=fac[i-1]*i,fac[i]%=p;
    while (T--){
        int n;cin>>n;
        string s;cin>>s;s=" "+s;
        for (rint i=1;i<=n;++i) a[i]=(s[i]=='1');
        int count11=0,count0=0;
        for (rint i=1;i<=n;++i){
            if (a[i]==1 && a[i+1]==1) ++count11,++i;
            count0+=(!a[i]);
        }
        cout<<C(count11+count0,count11)<<'\n';
    }
    return 0;
}


```


---

## 作者：dztlb (赞：6)

一个重大性质： $11$ 可以任意移动，定义 $11$ 为一个自由元
 
 然后我就陷入了 DP 的深渊，似乎可以先找连通块然后分奇偶讨论，偶数拆成自由元，奇数就是自由元+单点，把单点再分开计算，合并推推组合数式子，预处理一下前缀和和组合数就可以 $O(n)$ 了。
 
上面的 DP 不美观的地方就是单点的处理很复杂，无后效性也只能通过各种钦定来保证，赛时并没有很好的优化。

DP 为何消不掉单点？因为自由元在通过一个单点时会改变这个单点的位置。但其实我们还是能够消掉单点。

我们先钦定 $111$ 的情况是自由元在右，单点在左，毕竟最终方案数只统计一次。这样我们发现，只要确定了所有自由元的位置，单点的位置必然确定。而单点必然占一个位置。至此我们消掉了单点（单点位置不再重要，只用关注数量）设有 $m$ 个自由元，$n$ 个 $0$ 位，那么自由元能处在的位置总数 $n+m$，最终答案就是 $C^m_{n+m}$，至此我们预处理 $O(n\log M)$ 预处理阶乘与阶乘逆元（$M$ 为模数）就可以 $O(n)$ 求得此题答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
inline long long read(){
	long long x=0,f=1; char s;
	while((s=getchar())<'0'||s>'9') if(s=='-') f=-1;
	while(s>='0'&&s<='9') x=(x<<3)+(x<<1)+(s^'0'),s=getchar();
	return x*f;
}
typedef long long ll;
const int maxn=100005;
const int mod=998244353;
int t,n;
char s[maxn];
bool ok[maxn];
ll qpow(ll b,ll k) {
    if (k==0) return 1;
    long long ans=1;
    while(k){
        if (k&1) ans=ans*b%mod;
        k>>=1,b=(b*b)%mod;
    }
    return ans;
}
ll co[maxn],op[maxn];
void init(){
	co[0]=1,op[0]=1;
	for(int i=1;i<=100000;++i){
		co[i]=(co[i-1]*i)%mod;
		op[i]=(op[i-1]*qpow(i,mod-2))%mod;//阶乘逆元 
	}
}
int main(){
	init();
	t=read();
	while(t--){
		int a=0,b=0;
		memset(ok,0,sizeof(ok));
		n=read();
		scanf("%s",s+1);
		for(int i=1;i<n;++i){
			if(!ok[i]&&!ok[i+1]&&s[i]=='1'&&s[i+1]=='1'){
				ok[i]=1,ok[i+1]=1,a++;
			}else if(s[i]=='0') ++b;
		}
		if(s[n]=='0') ++b;
		printf("%lld\n",(((co[a+b]*op[a])%mod)*op[b])%mod);
	}
	
	return 0;
}
```


---

## 作者：Suzt_ilymtics (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1545B)

[更差的阅读体验](https://www.cnblogs.com/Silymtics/p/solution-CF1545B.html)

### Solution

你拿到这个题后开始手模它这个操作。

你发现，对于一个 `11` 移动的时候就相当于整体左移或者右移。

我们假设让它右移，如果它右边是一个 `0`，那么它右移就相当于和这个 `0` 交换位置。如果它右边是一个 `1`，~~实际并不能右移~~，但也可以看做它和这个 `1` 交换了一下位置。

那不难看出，和 `0` 交换位置时会产生新的状态，和 `1` 交换位置时并不会产生新的状态。

也不难看出，每一组 `11` 在整个序列中都是可以自由移动的。那么我们不妨将每个 `11` 都划分成一个整体，对于那些单独的 `1` 就直接扔掉。

那么对于剩下的 `11` 和 `0`，显然可以随便安排他们的位置。

设有 $x$ 个 `11` 和 $y$ 个 `0`，总排列数位 $(x+y)!$，因为有重复状态所以再除以 $x! y!$，也就是说答案为 $\binom{x+y}{x}$。

直接预处理一个阶乘和逆元就可以 $\mathcal O(1)$ 计算了。

至于 $x$ 和 $y$ 从原串中暴力找就可以。

### Code

```cpp
/*
Work by: Suzt_ilymtics
Problem: 不知名屑题
Knowledge: 垃圾算法
Time: O(能过)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define int long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 2e5+50;
const int INF = 1e9+7;
const int mod = 998244353;

int T, n;
int fac[MAXN], inv[MAXN];
char s[MAXN];

int read(){
    int s = 0, f = 0;
    char ch = getchar();
    while(!isdigit(ch))  f |= (ch == '-'), ch = getchar();
    while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
    return f ? -s : s;
}

void Init() {
    int M = 200000;
    fac[0] = fac[1] = inv[0] = inv[1] = 1;
    for(int i = 2; i <= M; ++i) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    }
    for(int i = 2; i <= M; ++i) {
        inv[i] = inv[i - 1] * inv[i] % mod; 
    }
}

int C(int n, int m) {
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

signed main()
{
	Init();
    T = read();
    while(T--) {
        n = read();
        cin >> s + 1;
        int y = 0, x = 0;
        for(int i = 1; i <= n; ++i) if(s[i] == '0') y++;
        for(int i = 2; i <= n; ++i) {
            if(s[i] == '1' && s[i - 1] == '1') {
                x++, s[i] = s[i - 1] = '0';
            }
        }
        printf("%lld\n", C(x + y, x));
    }
    return 0;
}

```

---

## 作者：封禁用户 (赞：1)

[cf 传送门](http://codeforces.com/problemset/problem/1545/B)

一道组合数学题。

想象一下，如果只有连续的两个 $\texttt{1}$。

那么这两个 $\texttt{1}$ 就可以去到这个串上的任何一个位置。

而多余的 $\texttt{1}$ 直接去掉处理就行了。

题目经过这样处理后，就成功转化成了一道组合数学题。

答案就是 $\binom{tot+cnt}{tot}$。

其中 $tot$ 是 $\texttt{11}$ 的数量，$cnt$ 是 $\texttt{0}$ 的数量。

附上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,ans,j=1,t,m,a[100001],tot,cnt;
const long long mod=998244353;
string aa;
long long ksm(long long a,long long b){
	ans=1;
	while(b){
		if(b&1)
			ans=(ans*a)%mod;
		b>>=1;
		a=(a*a)%mod;	
	}
	return ans;
}
long long C(long long a,long long b){
	if(a<b)
		return 0;
	if(a==b)
		return 1;
	if(b>a-b)
		b=a-b;
	long long A=1,B=1;
	for(int i=0;i<b;i++){
		A=(A*(a-i))%mod;
		B=(B*(b-i))%mod;
	}
	return A*ksm(B,mod-2)%mod;
}
long long lc(long long n,long long m){
	if(m==0)
		return 1;
	return C(n%mod,m%mod)*lc(n/mod,m/mod);
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		cin>>aa;
		long long f=0;tot=0,cnt=0;
		for(int i=0;i<n;i++){
			a[i]=aa[i]-'0';
			if(a[i]==1){
				f++;
				if(f==2)f=0,cnt++;
			}else tot++,f=0;
		}
		cout<<lc(tot+cnt,tot)<<endl;
	}
	return 0;
}//
```

---

## 作者：KSToki (赞：1)

一道比较有趣的阴间思维题，代码其实很简单。
# 题目大意
给定一个长度为 $n$ 的 $01$ 串表示初始状态，每次可以进行操作，如果一个 $1$ 旁边有另一个 $1$ 则可到达另一相邻的位置，需保证到达的位置在界内且为 $0$，问有多少合法的状态数，答案模 $998244353$。
# 题目分析
乍一看没什么入手的地方，我们先简化一下，假设所有 $1$ 都是两两成对挨在一起的，那么可以依次操作这两个 $1$ 到达任何没有其它 $1$ 的地方。这样我们可以把它们绑在一起，统计总对数 $m$，将剩余的 $0$ 插空，得到的答案全是合法的，答案为 $C(n-m,m)$，等价于在 $n-m$ 的空地上放 $m$ 对绑在一起的棋子。

那如果有奇数个在一起的呢？首先它要单一个出来，剩下的按偶数处理，那么这些单出来的 $1$ 将棋盘划成了一段一段的。手玩一下可以发现，如果某对棋子从左边过来，在前的棋子会与该单棋子形成新的对继续移动，相当于把这个单棋子向左移了 $2$ 格。那么就可以通过每段中棋子的数量与初始状态相比得出单 $1$ 的位置，即单 $1$ 不影响结果，直接扔掉即可。
# 代码
```
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,a[100001],jc[100001],inv[100001],tn,rm;
const int Mod=998244353;
I int ksm(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1)
			res=1ll*res*x%Mod;
		x=1ll*x*x%Mod;
		y>>=1;
	}
	return res;
}
I int C(int x,int y)
{
	return 1ll*jc[x]*inv[x-y]%Mod*inv[y]%Mod;
}
int main()
{
	T=read();
	jc[0]=inv[0]=1;
	for(R int i=1;i<=100000;++i)
	{
		jc[i]=1ll*jc[i-1]*i%Mod;
		inv[i]=ksm(jc[i],Mod-2);
	}
	while(T--)
	{
		n=read();
		for(R int i=1;i<=n;++i)
			scanf("%1d",&a[i]);
		tn=rm=0;
		for(R int i=1;i<=n;++i)
		{
			if(a[i]==0)
			{
				++tn;
			}
			else
			{
				if(i+1<=n&&a[i+1])
				{
					++tn;
					++rm;
					++i;
				}
			}
		}
		putint(C(tn,rm));
	}
	return 0;
}
```

---

## 作者：Acfboy (赞：1)

赛时对着这个题爆肝两小时，然后收获 wrong answer on pretest 1。

观察这个移动，发现两个一组队就可以移来移去，没有限制。唯一会落下一个的情况就是在遇到了奇数个 $1$ 连在一起。  
赛场上想了很久怎么处理 $1$ 的移动但未果，于是来考虑 $0$ 的移动，发现 $0$ 总是跨越俩 $1$，那么可以按照 $1$ 为间隔对 $0$ 分组，然后对于奇数组合偶数组分别考虑，相当于“把 $a$ 个球放进 $b$ 个盒子里，可以为空，有多少种方案”这样的问题，答案就是 $a+b-1 \choose b-1$，即将每一个盒子都补上一个，插板后再减掉。

然而这样是连样例都过不了的，因为 $0$ 是能跨的时候必然跨俩 $1$，但不是所有的时候都能跨。  
但是这是一个好的思路，我们可以用对 $1$ 以 $0$ 为间隔分组来解决这个问题。显然俩 $1$ 可以为一组，但是还是老问题，剩余的 $1$ 怎么处理？ 答案很简单：不用处理。  因为按照 $0$ 分组后可以发现，落下的那个 $1$ 虽然相对于其它的 $1$ 位置发生了变化，但是相对于 $0$ 是没有变的。  

最后还得验证一下这是不是能对应所有情况，不然就得重蹈前面的覆辙了。由于我们考虑的是 $1$，所以每个移动都是可以进行的，同样，也不可能有更多的移动。  
那么就统计一下 $1$ 的组数，记为 $a$，然后再统计 $0$ 的个数，记为 $b$，最后答案就是 ${a+(b+1) - 1 \choose (b+1)-1} = {a+b \choose b}$ 了。

代码。

```cpp
#include <cstdio>
#define int long long
const int N = 200005, MAX = 200000, P = 998244353;
int fac[N], inv[N], T, t[N], n;
char st[N];
int Pow(int a, int b) {
    int an = 1;
    for ( ; b; b >>= 1, a = a * a % P)
        if (b & 1) an = an * a % P;
    return an;
}
int C(int n, int m) {
    if (m > n) return 0; 
    return fac[n] * inv[m] % P * inv[n-m] % P;
}
signed main() {
    fac[0] = 1;
    for (int i = 1; i <= MAX; i++) fac[i] = fac[i-1] * i % P;
    inv[MAX] = Pow(fac[MAX], P-2);
    for (int i = MAX; i >= 1; i--) inv[i-1] = inv[i] * i % P;
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld%s", &n, st+1);
        int n0 = 0,m0 = 0;
        for (int i = 1; i <= n; i++) t[i] = 0, m0 += st[i] == '0';
        for (int i = 2; i <= n; i++)
        	if (st[i] == '1' && st[i-1] == '1' && 	!t[i-1])	
        		t[i] = t[i-1] = 1, n0++;
        printf("%lld\n", C(n0+m0, m0));
    }
    return 0;
}
```

~~这题居然才 1900 TwT~~

---

## 作者：fsy_juruo (赞：1)

考查一次「移动」操作，我们不难发现：这个操作等价于将相邻的一对 ``1`` 进行移位。

如 ``110 -> 011``，等价于将 ``11`` 整体移动一位。

故我们可以考虑将 ``11`` 编为一个棋子，简记为 ``A``。并规定 ``A`` 可以与相邻的 ``0`` 交换。

但是上述方法无法解决存在相邻奇数个 ``1`` 的情况，故我们考虑记 ``10`` 为 ``B``。

简单模拟后不难发现，``A`` 与 ``B`` 之间也可以交换位置，而 ``B`` 与 ``B``，``B`` 与 ``0`` 不行。故我们得出以下结论：

将读入的棋盘按以下方式编码：对于任意一段连续的 ``1``，如果其长度 $l$ 为偶数，将其编为 $\frac{l}{2}$ 个 ``A``，否则加上后面的 ``0``，编为 $l/2$ 个 ``A`` 和一个 ``B``。（有特殊情况，最后会提到）剩下的 ``0`` 保留。

则：

(1) ``A`` 没有任何位置限制。

(2) ``B`` 与 ``0`` 之间的位置关系不能被破坏。

故这个问题就被转化为：有 $len$ 个位置，要填入 $a$ 个 ``A``，余下位置填 ``B``，``0``。``A`` 可以随意摆放，而所有的 ``B``，``0`` 之间必须严格符合某种位置关系。

显然，上述问题的答案为 $\binom{len}{a}$：``A`` 有 $\binom{len}{a}$ 种填法，而确定了 ``A`` 的填法之后，``B``，``0`` 的填法也就唯一确定了。

故只需要将读入的棋盘照上述编码为由 ``A``，``B``，``0`` 组成的字符串，就可以求出答案。

还有一个问题：如果编码到最后出现 ```...01``` 的情况怎么办？不难发现最后的 ``1`` 可以忽略，对答案没有影响。

注意预处理阶乘与其逆元，时间复杂度 $O(tn)$。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define LD long double
#define reg register
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
template <typename T>
inline void read(T &x) {
	x = 0; T f = (T) 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) {if(c == '-') f = -f;}
	for(; isdigit(c); c = getchar()) x = x * 10 + c - 48;
	x *= f;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x); read(args...);
}
template <typename T>
inline void write(T x) {
	if(x < 0) {x = -x; putchar('-');}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T>
inline void writesp(T x, char sp = ' ') {write(x); putchar(sp);}

const int maxN = 1e5 + 10, LIM = 1e5, P = 998244353;
int t, n, fac[maxN], facinv[maxN];
char str[maxN];
int pow_mod(int a, int b = P - 2, int p = P) {
	int sum = 1;
	while(b) {
		if(b & 1) sum = 1ll * sum * a % p;
		a = 1ll * a * a % p;
		b >>= 1;
	}
	return sum;
}
int main() {
	fac[0] = fac[1] = 1;
	_rep(i, 2, LIM) fac[i] = 1ll * fac[i - 1] * i % P;
	facinv[LIM] = pow_mod(fac[LIM]);
	_per(i, LIM - 1, 1) facinv[i] = 1ll * facinv[i + 1] * (i + 1) % P;
	facinv[0] = 1;
	read(t); 
	while(t--) {
		read(n);
		scanf("%s", str + 1);
		int len = 0, flg = 0, a = 0;
		_rep(i, 1, n) {
			if(str[i] == '1') {
				++flg;
				if(flg == 2) {
					++len;
					++a;
					flg = 0;
				}
			} else {
				++len; flg = 0;
			}
		}
		int ans = 1ll * fac[len] * facinv[a] % P * facinv[len - a] % P;
		writesp(ans, '\n');
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

### 此题约等于组合数
#### 分析题目：
若有两个 1 连在一起，那么它可以移到任意位置。   
否则，它根本**不能动** → 我们也不用考虑它。   
我们可以把两个 1 缩成一个 1，一个 1 我们不管它  
至于 0 的个数，我们也统计一下。   
```cpp
int p1=0,p2=0;
for (int i=0;i<n;i++)
	if (a[i]=='0') p1++;//统计'0'
	else if (a[i]=='1'&&a[i+1]=='1')
		i++,p2++;//统计连续两个的'1'
      //i++,小技巧； 跳过到下一个的下一个
```
接下来，通过理解题目，我们知道 $ans=C_{p1+p2}^{p2}$ 于是乎组合数模板套上就行了。     
#### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
const int p=998244353;
using namespace std;
int t,n; char a[100005];
int kkk(int a,int b){
	int tmp=1;
	while (b){
		if (b&1) tmp=(tmp*a)%p;
		b>>=1; a=(a*a)%p; 
	} return tmp;
}
int C(int n,int m,int p){
	if (n<m) return 0;
	if (n==m) return 1;
	if (n-m<m) m=n-m;
	int a=1,b=1;
	for (int i=0;i<m;i++){
		a=a*(n-i)%p;
		b=b*(m-i)%p;
	} return a*kkk(b,p-2)%p;
}
signed main(){
	scanf("%lld",&t);
	while (t--){
		scanf("%lld",&n);
		scanf("%s",a);
		int p1=0,p2=0;
		for (int i=0;i<n;i++)
			if (a[i]=='0') p1++;
			else if (a[i]=='1'&&a[i+1]=='1')
				i++,p2++;
		printf("%lld\n",C(p1+p2,p2,p));
	}
	return 0;
}
```

---


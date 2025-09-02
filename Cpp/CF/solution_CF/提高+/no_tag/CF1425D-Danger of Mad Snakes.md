# Danger of Mad Snakes

## 题目描述

Mr. Chanek The Ninja is one day tasked with a mission to handle mad snakes that are attacking a site. Now, Mr. Chanek already arrived at the hills where the destination is right below these hills. The mission area can be divided into a grid of size $ 1000 \times 1000 $ squares. There are $ N $ mad snakes on the site, the i'th mad snake is located on square $ (X_i, Y_i) $ and has a danger level $ B_i $ .

Mr. Chanek is going to use the Shadow Clone Jutsu and Rasengan that he learned from Lord Seventh to complete this mission. His attack strategy is as follows:

1. Mr. Chanek is going to make $ M $ clones.
2. Each clone will choose a mad snake as the attack target. Each clone must pick a different mad snake to attack.
3. All clones jump off the hills and attack their respective chosen target at once with Rasengan of radius $ R $ . If the mad snake at square $ (X, Y) $ is attacked with a direct Rasengan, it and all mad snakes at squares $ (X', Y') $ where $ max(|X' - X|, |Y' - Y|) \le R $ will die.
4. The real Mr. Chanek will calculate the score of this attack. The score is defined as the square of the sum of the danger levels of all the killed snakes.

Now Mr. Chanek is curious, what is the sum of scores for every possible attack strategy? Because this number can be huge, Mr. Chanek only needs the output modulo $ 10^9 + 7 $ .

## 说明/提示

Here is the illustration of all six possible attack strategies. The circles denote the chosen mad snakes, and the blue squares denote the region of the Rasengan:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1425D/5a0ae1573d7d9d31c9abffd632aa62031298b56e.png)So, the total score of all attacks is: $ 3.600 + 3.600 + 4.900 + 3.600 + 10.000 + 8.100 = 33.800 $ .

## 样例 #1

### 输入

```
4 2 1
1 1 10
2 2 20
2 3 30
5 2 40```

### 输出

```
33800```

# 题解

## 作者：Fairicle (赞：7)

观察到数据范围，可以发现做法应该是个 $N^2$ 的。考虑计算每对蛇 $(i,j)$ 对答案的贡献，必定有 $(...+B_i+B_j+...)^2$ 这样的形式。

提出与这两项都有关的式子，那么只有 $2B_iB_j$。考虑计算同时包含 $i,j$、只包含 $i$、只包含 $j$ 的攻击圈个数，记为 $X,Y,Z$。

那么就可以计算 $i,j$ 同时出现的方案个数，也就能计算贡献。

有同时包含 $i,j$ 的攻击圈：$\dbinom{n}{m}-\dbinom{n-X}{m}$

没有同时包含 $i,j$ 的攻击圈，简单容斥得到：$\dbinom{n-X}{m}-\dbinom{n-X-Y}{m}-\dbinom{n-X-Z}{m}+\dbinom{n-X-Y-Z}{m}$

得到方案数给它乘个 $2B_iB_j$ 就行啦。

当然如果 $i=j$ 的话给它乘个 ${B_i}^2$，所以需要判一下。

巨丑无比的code：
```cpp
#include"bits/stdc++.h"
using namespace std;
#define ri register int
#define ll long long
#define N 2010
#define mod 1000000007
ll n,m,r,x[N],y[N],a[N],s[N][N],ans;
ll fac[N],inv[N];
inline ll ksm(ll x,int y){
	ll res=1;
	while(y){
		if(y&1) res*=x,res%=mod;
		x*=x,x%=mod;
		y>>=1;
	}
	return res;
}
inline void calc(){
	inv[0]=inv[1]=fac[0]=fac[1]=1;
	for(ri i=2;i<=n;++i) fac[i]=1ll*i*fac[i-1]%mod,inv[i]=ksm(fac[i],mod-2);
	for(ri i=1;i<=1010;++i) for(ri j=1;j<=1010;++j){
		s[i][j]+=s[i][j-1]+s[i-1][j]-s[i-1][j-1];
	}
}
inline ll C(int m,int n){
	if(n<0||m<0||m>n) return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
inline int calc_pre(int x,int y,int _x,int _y){
	x=max(1,x),_x=min(1000,_x),y=max(1,y),_y=min(1000,_y);
	if(x>_x||y>_y) return 0;
	return s[_x][_y]-s[x-1][_y]-s[_x][y-1]+s[x-1][y-1];
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>r;
	for(ri i=1;i<=n;++i) cin>>x[i]>>y[i]>>a[i],s[x[i]][y[i]]++;
	calc();
	for(ri i=1;i<=n;++i)
	for(ri j=i;j<=n;++j){
		//calc the squares containing both snakes
		int minx=max(x[i],x[j])-r,miny=max(y[i],y[j])-r,maxx=min(x[i],x[j])+r,maxy=min(y[i],y[j])+r;
		ll num=calc_pre(minx,miny,maxx,maxy);
		ll cnt1=(C(m,n)-C(m,n-num)+mod)%mod;
		//calc separately
		ll calc1=calc_pre(x[i]-r,y[i]-r,x[i]+r,y[i]+r)-num,calc2=calc_pre(x[j]-r,y[j]-r,x[j]+r,y[j]+r)-num;
		ll tot=n-num;
		ll cnt2=(C(m,tot)-C(m,tot-calc1)-C(m,tot-calc2)+C(m,tot-calc1-calc2))%mod;
		if(cnt2<0) cnt2+=mod;
		if(i==j) ans=(ans+a[i]*a[i]%mod*cnt1%mod)%mod;
		else ans=(ans+2ll*a[i]*a[j]%mod*(cnt1+cnt2)%mod)%mod;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：出言不逊王子 (赞：3)

观察题意，问的既然是“每一种贡献之和”，那就考虑每一种贡献本身的样子和他出现了几次。

对于一种方案，如果他是 $(\sum_{i=1}^k a_i)^2$，那么我们可以把这个式子拆开变成 $\sum_{i=1}^k a_i^2+\sum_{i=1}^k\sum_{j=1}^k[i\neq j]\times 2\times  a_i\times a_j$。

也就是说，最终答案可以被拆分成两个部分：

- 相同的 $a_i$ 的平方。
- 不同的两个 $a_i$ 的乘积。

考虑如何计算这两种答案的出现次数。

对于第一种答案，我们考虑能碰到他的所有的笼子的数量，可以二维前缀和求出，记为 $q$。

从那些蛇身上扔一个笼子都能碰到这条蛇。相应地，从剩余 $n-q$ 条蛇上扔一个笼子就碰不到了。

那么 $a_i$ 的平方出现的方案数就是总的方案数减去不合法的方案数，为 $C_n^m-C_{n-q}^m$。

那为什么不是 $C_q^m$ 呢？

因为对于一种方案，我们只要让 $q$ 个当中**至少一个**碰到这条蛇即可，而 $C_q^m$ 是记录这 $q$ 个当中选出 $m$ 个的方案数，满足的是这 $m$ 个笼子全部都抓到了这条蛇。

那对于第二种答案，我们记能**同时碰到这两条蛇**的笼子的数量为 $q$，只能碰到 $i$ 的数量为 $x$，只能碰到 $j$ 的数量为 $y$。

那么能同时碰到两条蛇的方案数就是 $C_n^m-C_{n-q}^m$。

那么能在**不同的两个笼子里**碰到两条蛇的方案数呢？

首先我们肯定有**不同时碰到**两条蛇的，所以方案里边加了一个 $C_{n-q}^m$。

然后在这个条件下，那些没法碰到 $i$ 的有 $n-x-q$ 个，所以答案要减去一个 $C_{n-x-q}^m$。

同理可知答案要减去一个 $C_{n-y-q}^m$。

但是我们把没法碰到 $i$ 也没法碰到 $j$ 的计算了两次，所以要加上 $C_{n-x-y-q}^m$。

最终 $2\times a_i\times a_j$ 出现的方案数是 $C_{n-q}^m-C_{n-x-q}^m-C_{n-y-q}^m+C_{n-x-y-q}^m$。

注意取模细节。

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=2001,inf=1e9+7;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int n,m,a[N],pos[N][N],r,qpos[N][N],res;
int ksm(int a,int b){
    int ans=1;while(b){if(b&1) ans=ans*a%inf;a=a*a%inf;b=b>>1;}
    return ans;
}
int fac[N+1],inv[N+1],x[N],y[N];
int c(int d,int u){if(u>d||d<0||u<0) return 0;return fac[d]%inf*inv[u]%inf*inv[d-u]%inf;}
int qsum(int x1,int y1,int x2,int y2){
	x1=max(x1,1ll),y1=max(y1,1ll);
	x2=min(x2,N-1),y2=min(y2,N-1);
	if(x1>x2||y1>y2) return 0;
	return qpos[x2][y2]-qpos[x2][y1-1]-qpos[x1-1][y2]+qpos[x1-1][y1-1];
}
int trans(int i){
	int quans=qsum(x[i]-r,y[i]-r,x[i]+r,y[i]+r);//包括i的圈数
	int fastot=c(n,m),nothing=c(n-quans,m);
	int cnt=(fastot-nothing+inf)%inf;//至少有一个有i的方案数
	int cnt2=0;//(nothing-c(n-quans*2,m)-c(n-quans*2,m)+c(n-quans*3,m)+inf*2)%inf;
	return (cnt+cnt2)%inf;
}
signed main(){
	fac[0]=inv[0]=1;fs(i,1,N,1)fac[i]=fac[i-1]*i%inf;
    inv[N]=ksm(fac[N],inf-2);ft(i,N-1,1,-1)inv[i]=inv[i+1]*(i+1)%inf;
	n=read(),m=read(),r=read();//m是m个摸虫机 
	fs(i,1,n,1){
		x[i]=read(),y[i]=read();a[i]=read(); 
		pos[x[i]][y[i]]++;
	}
	fs(i,1,N-1,1) fs(j,1,N-1,1) qpos[i][j]=qpos[i-1][j]+qpos[i][j-1]-qpos[i-1][j-1]+pos[i][j];
	fs(i,1,n,1){
		(res+=(a[i]*a[i]%inf*trans(i)%inf))%=inf;
		fs(j,i+1,n,1){
			int quaninij=qsum(max(x[i],x[j])-r,max(y[i],y[j])-r,min(x[i],x[j])+r,min(y[i],y[j])+r);
			int quanini=qsum(x[i]-r,y[i]-r,x[i]+r,y[i]+r)-quaninij;//i nomi
			int quaninj=qsum(x[j]-r,y[j]-r,x[j]+r,y[j]+r)-quaninij;//j nomi
			int fastot=c(n,m),nothing=c(n-quaninij,m);
			int cnt=(fastot-nothing+inf)%inf;
			(cnt+=(((nothing-c(n-quaninij-quanini,m)+inf)%inf-(c(n-quaninij-quaninj,m)-c(n-quaninij-quanini-quaninj,m)+inf*2)%inf+inf)%inf))%=inf;
			(res+=(2*a[i]%inf*a[j]%inf*cnt%inf))%=inf; 
		}
	}
	cout<<res;
	return 0;
}
//考虑每个圈子所带来的贡献总和 
//考虑对于单点的贡献 
//要么在一个方案里是两个不同的圈，要么是一个相同的圈
//注意到他只能丢到蛇的身上去
//那么我们可以润出来，这种圈圈的方案数是S
//那么有几种情况呢？ 
//那么我们有几种方案数可以取到S中的一个呢？
//总数-完全没取到的
//下一种情况：同时取到包含i与j的并且没有取到S
//完全没取到的-(完全没取到包含j的+完全没取到包含i的-完全没取到包含i和j的) 
```

---

## 作者：jasonliujiahua (赞：1)

# [CF1425D](https://www.luogu.com.cn/problem/CF1425D)

## Solution

~~一篇比较与众不同的题解~~

### Step 1：
首先对所有方案求和肯定考虑对于每一项算贡献。对于一种方案，设其覆盖了 $a_1\sim a_k$，有：
$$\left(\sum_{i=1}^ka_i
\right)^2=\sum_{i=1}^k a_i^2+\sum_{i=1}^n\sum_{j=1}^{i-1}2a_ia_j=\sum_{i=1}^k a_i^2+\sum_{i=1}^n\sum_{j\neq i}a_ia_j$$

因此分别考虑 $a_i^2$ 即 $a_i$ 被多少种方案覆盖以及每一对 $(i,j)$ 被多少种方案覆盖。

### Step 2：

设 $b_i$ 表示有多少个点可以覆盖 $i$，即 $i$ 所代表的矩形能覆盖多少点；$c_{i,j}$ 表示有多少个点可以同时覆盖 $i,j$，即 $i,j$ 所代表的两个矩形的交内有多少个点。这两个数组用二位前缀和很好处理。

$a_i^2$ 的出现次数显然好算，即 $\binom{n}{m}-\binom{n-b_i}{m}$。注意到这里不好直接算，因此启示我们正难则反。

接下来处理一对 $(i,j)$ 被覆盖的次数。有了上面的经验，考虑容斥。设 $B_i$ 表示能覆盖 $i$ 的点组成的集合，$A_{C}=\{X|\exists x\in C \ s.t.\ x\in X\}$，即与 $C$ 有交的方案构成的集合（仔细注意一下这个定义），答案即为

$$|A_{B_i}\cap A_{B_j}|=|A_{B_i}|+|A_{B_j}|-|A_{B_i}\cup A_{B_j}|$$
$$=|A_{B_i}|+|A_{B_j}|-|A_{B_i\cup B_j}|$$

由 $A_C=\binom{n}{m}-\binom{n-|C|}{m}$ 可知：

$$|A_{B_i}\cap A_{B_j}|=\binom{n}{m}-\binom{n-|B_i|}{m}+\binom{n}{m}-\binom{n-|B_j|}{m}-\left(\binom{n}{m}-\binom{n-|B_i\cup B_j|}{m}\right)$$
$$=\binom{n}{m}-\binom{n-|B_i|}{m}-\binom{n-|B_j|}{m}+\binom{n-|B_i\cup B_j|}{m}$$

### Step 3：

按理说我们已经可以得出答案了，但是有一些细节和比较本质的东西我将在这里详细说明一下。这道题能解决的本质就是上一步中的 $A_{B_i}\cup A_{B_j}=A_{B_i\cup B_j}$。想要证明此式只需构造双射即可，即：若 $x\in A_{B_i}\cup A_{B_j}$ 则 $x\in A_{B_i\cup B_j}$，且反过来也成立。证明较为简单，不再赘述。让我们思考一下为什么会有如此优雅地结论。原因可能是 $A$ 集合的定义中的 $\exists$、$\cup$ 和“或”三者具有相似的本质导致的结果。根据这个分析，如果将 $\exists$ 改成 $\forall$、将 $\cup$ 改成 $\cap$ 也会有类似的结论。而且再提一嘴我们显然也可以证明 $A_{B_i}\cap A_{B_j}\neq A_{B_i\cap B_j}$，答案就不会直接是 $\binom{n}{m}-\binom{n-|A_i\cap A_j|}{m}$ 了。


## 参考代码
```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e3+10,N=1000,p=1e9+7;
int n,m,r,ans,sum[maxn][maxn],inv[maxn],jc[maxn],ijc[maxn],b[maxn],c[maxn][maxn];
struct snake
{
	int x,y,val;
}a[maxn];
inline int query(int x,int y,int xx,int yy)
{
	if(x>xx || y>yy) return 0;
	return sum[xx][yy]-sum[x-1][yy]-sum[xx][y-1]+sum[x-1][y-1];
}
void init()
{
	jc[0]=ijc[0]=1;
	for(int i=1;i<maxn;i++)
	{
		if(i==1) inv[i]=1;
		else inv[i]=(p-p/i)*inv[p%i]%p;
		jc[i]=jc[i-1]*i%p;
		ijc[i]=ijc[i-1]*inv[i]%p;
	}
	cin>>n>>m>>r;
	for(int i=1;i<=n;i++) 
	{
		cin>>a[i].x>>a[i].y>>a[i].val;
		sum[a[i].x][a[i].y]=1; 
	}
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	for(int i=1;i<=n;i++)
		b[i]=query(max(1ll,a[i].x-r),max(1ll,a[i].y-r),min(N,a[i].x+r),min(N,a[i].y+r));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			c[i][j]=query(max(1ll,max(a[i].x-r,a[j].x-r)),max(1ll,max(a[i].y-r,a[j].y-r)),min(N,min(a[i].x+r,a[j].x+r)),min(N,min(a[i].y+r,a[j].y+r)));
}
inline int C(int x,int y)
{
	if(x<y) return 0;
	return jc[x]*ijc[y]%p*ijc[x-y]%p;
}
void work()
{
	for(int i=1;i<=n;i++) //ai^2
	{
		int num=(C(n,m)-C(n-b[i],m)+p)%p;
		ans=(ans+num*a[i].val%p*a[i].val%p)%p;
	}
	for(int i=1;i<=n;i++) //2*ai*aj
	{ 
		for(int j=1;j<=n;j++)
		{
			if(i==j) continue;
			int num=(C(n,m)-C(n-b[i],m)-C(n-b[j],m)+C(n-b[i]-b[j]+c[i][j],m)+4*p)%p;
			ans=(ans+a[i].val*a[j].val%p*num%p)%p;
		}
	}
	cout<<ans;
}
signed main()
{
	init();
	work();
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

一道计算方式很具有启发意义的题。

对于这种“选中产生贡献”的题，明显是需要对每个点算对总答案的贡献。但是由于“和的平方”的存在，这很难实现。

所以不妨在上面思路的基础上稍作改良：对每两个点算对总答案的贡献。不难发现，贡献的次数即为两个点都被选中的情况数。设 $a,b,c$ 分别为包含第一个点，包含第二个点和两个点都包含的方案数。则这两个点贡献的次数即为 $C_n^m-C_{n-a}^m-C_{n-b}^m+C_{n-(a+b-c)}^m$。再乘上一个 $B_i\times B_j$，即为**有序对** $(i,j)$ 的贡献。

小贴士：

1. 可以发现 $i=j$ 的情况也可以套用上面的式子，就不用分类讨论了。

2. 计算包含点的数量可以用前缀和实现。

3. 要预处理逆元，否则会超时。

code：

```cpp
using namespace my_std;
const int N=2e3+7,M=-1,inf=0x3f3f3f3f,mod=1e9+7;
int n,m,k,x[N],y[N],c[N],f[N],inv[N],s[N][N];
const int mx=1e3;
inline int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)
			ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return ret;
}
inline int Cnm(int x,int y){
	if(x<0||y<0||x<y)
		return 0;
	return 1ll*f[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int get_dis(int i,int j){
	return max(abs(x[i]-x[j]),abs(y[i]-y[j]));
}
inline int calc(int i,int j){
	int X1=min(min(x[i]+k,x[j]+k),mx),X2=max(max(x[i]-k,x[j]-k),1),Y1=min(min(y[i]+k,y[j]+k),mx),Y2=max(max(y[i]-k,y[j]-k),1);
	if(X1<X2||Y1<Y2)
		return 0;
	return s[X1][Y1]-s[X1][Y2-1]-s[X2-1][Y1]+s[X2-1][Y2-1];
}
void solve(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&x[i],&y[i],&c[i]);
		s[x[i]][y[i]]++;
	}
	for(int i=1;i<=mx;i++){
		for(int j=1;j<=mx;j++)
			s[i][j]+=s[i-1][j];
	}
	for(int i=1;i<=mx;i++){
		for(int j=1;j<=mx;j++)
			s[i][j]+=s[i][j-1];
	}
	f[0]=1,inv[0]=1;
	for(int i=1;i<=n;i++){
		f[i]=1ll*f[i-1]*i%mod;
		inv[i]=qpow(f[i],mod-2);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)
				ans=(ans+1ll*c[i]*c[i]%mod*(Cnm(n,m)-Cnm(n-calc(i,i),m)+mod)%mod)%mod;
			else 
				ans=(ans+1ll*c[i]*c[j]%mod*(Cnm(n,m)-Cnm(n-calc(i,i),m)-Cnm(n-calc(j,j),m)+Cnm(n-(calc(i,i)+calc(j,j)-calc(i,j)),m)+2ll*mod)%mod)%mod;
		}
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		solve();
}
```

---

## 作者：intel_core (赞：0)

我们知道所有方案的贡献一定都是形如 $(B_{i_1}+B_{i_2}+\cdots +B_{i_k})^2$ 的形式，所以最后算到总贡献里要么是 $xB_i^2$ ，要么是 $xB_iB_j$ 的形式，所以我们只需要求出所有 $B_i^2$ 和 $B_iB_j$ 对总贡献的系数即可。

我们现在钦定 $B_i ,B_j$ ，考虑有多少种方案有一个攻击圈同时包含 $i$ 和 $j$。

考察这个攻击圈目标的位置，可以发现目标一定在以 $i$ 蛇和 $j$ 蛇为中心，$R$ 为半径的正方形 的交集中。所以我们可以前缀和整个棋盘内蛇的数量，$O(1)$ 求出可能的攻击圈的目标。

记包含 $i$ 的攻击圈数量为 $x$，包含 $j$ 的攻击圈数量为 $y$，包含 $i,j$ 之一的攻击圈数量为 $z$，考虑正难则反，把 $m$ 个圈不同时包含排除，可以得到合法的方案数是 $C_n^m-C_{n-x}^m-C_{n-y}^m+C_{n-z}^m$，总贡献就是 $(C_n^m-C_{n-x}^m-C_{n-y}^m+C_{n-z}^m)\times 2B_iB_j$。

再考虑 $B_i^2$ 对答案的贡献，类似的，求出可能的攻击圈目标数 $cnt$，贡献就是 $B_i^2 \times (C_n^m-C_{n-cnt}^m)$。

总复杂度 $O(n^2)$，记得开 `long long` 。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int NR=2e3+10;
const int MOD=1e9+7;
int n,m,r,a[NR],x[NR],y[NR],cnt[NR][NR],c[NR][NR],ans; 
int calc(int x1,int y1,int x2,int y2){
	x1=max(x1,1ll);y1=max(y1,1ll);
	x2=min(x2,1000ll);y2=min(y2,1000ll);
	if(x1>x2||y1>y2)return 0;
	return cnt[x2][y2]+cnt[x1-1][y1-1]-cnt[x1-1][y2]-cnt[x2][y1-1];
}
void upd(int &x,int y){(x+=y%MOD)%=MOD;}
int cal(int k){return calc(x[k]-r,y[k]-r,x[k]+r,y[k]+r);}
int sum(int i,int j){
	return cal(i)+cal(j)-calc(max(x[i],x[j])-r,max(y[i],y[j])-r,min(x[i],x[j])+r,min(y[i],y[j])+r);
}

signed main(){
	cin>>n>>m>>r;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i]>>a[i],cnt[x[i]][y[i]]++;
	for(int i=1;i<=1000;i++)
		for(int j=1;j<=1000;j++)cnt[i][j]+=cnt[i-1][j]+cnt[i][j-1]-cnt[i-1][j-1];
	c[0][0]=1;
	for(int i=1;i<=n;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			int x=cal(i),y=cal(j),z=sum(i,j);
			upd(ans,2*a[i]*a[j]%MOD*(c[n][m]-c[n-x][m]-c[n-y][m]+c[n-z][m]));
		}
	for(int i=1;i<=n;i++)
		upd(ans,a[i]*a[i]*(c[n][m]-c[n-cal(i)][m]));
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Yansuan_HCl (赞：0)

## 题意

选中一条蛇，则周边与其切比雪夫距离不超过 $R$ 的蛇都会被选中。每种选法的贡献为**每条被选的蛇的权值和**的平方。

## 题解

把平方展开，一定存在形如 $B_iB_j$ 的项。

枚举 $(i,j)$，计算有多少种选法存在 $(i,j)$。有两种情况：

1. 选中一条蛇，则可以同时套住两条蛇；
2. 选中两条蛇，分别套住。

先二维前缀和算出第一种的蛇数记为 $Z$。则存在其中一条的情况可以容斥，即 $\displaystyle \binom{n}{m}-\binom{n-Z}{m}$。

第二种蛇数同理可以二维前缀和计算，记为 $X$、$Y$。需要注意：第二种方案选出的蛇不能同时套住 $(i,j)$。方案数为 $\displaystyle \binom {n-Z} m - \binom{n-Z-X} m - \binom{n-Z-Y} m + \binom{n-Z-X-Y}{m}$。

## 代码

```cpp
const ll P = 1000000007;
const int N = 2003;
ll fac[N], ifac[N];
ll qpow(ll x, ll t) { ll v = 1; while (t) { if (t & 1) (v *= x) %= P; (x *= x) %= P; t >>= 1;} return v; }
void genFac() {
    fac[0] = ifac[0] = 1;
    U (i, 1, N - 1) fac[i] = fac[i - 1] * i % P;
    ifac[N - 1] = qpow(fac[N - 1], P - 2);
    D (i, N - 2, 1) ifac[i] = ifac[i + 1] * (i + 1) % P;
}
ll C(ll n, ll m) {
    if (m > n || m < 0 || n < 0) return 0;
    return fac[n] * ifac[m] % P * ifac[n - m] % P;
}

ll n, m, r, x[N], y[N], a[N];
int g[N][N];

int sum(int xp, int yp, int xq, int yq) {
	xp = max(xp, 1); yp = max(yp, 1);
	xq = min(xq, N - 1); yq = min(yq, N - 1);
	if (xp > xq || yp > yq) return 0;
	return g[xq][yq] - g[xp - 1][yq] - g[xq][yp - 1] + g[xp - 1][yp - 1];
}

int main() {
    // 计算的是总和。
	// (\sum a_i)^2:: \sum a_i^2 + \sum a_ia_j
	genFac();
	// 选中 a_ia_j 的方案数：|i|+|j|-|i||j|
	rd(n, m, r);
	U (i, 1, n) {
		rd(x[i], y[i], a[i]);
		++g[x[i]][y[i]];
	}
	U (i, 1, N - 1) U (j, 1, N - 1)
		g[i][j] += g[i - 1][j] + g[i][j - 1] - g[i - 1][j - 1];

	ll ans = 0;
	U (i, 1, n) U (j, 1, n) {
		int cIJ = sum(max(x[i], x[j]) - r, max(y[i], y[j]) - r, min(x[i], x[j]) + r, min(y[i], y[j]) + r),
			cI = sum(x[i] - r, y[i] - r, x[i] + r, y[i] + r) - cIJ,
			cJ = sum(x[j] - r, y[j] - r, x[j] + r, y[j] + r) - cIJ;
		ll fA = (C(n, m) - C(n - cIJ, m) + P) % P;
		ll fB = (C(n - cIJ, m) - C(n - cIJ - cI, m) - C(n - cIJ - cJ, m) + C(n - cIJ - cI - cJ, m) + P * 2) % P; // 选出单独 ci 和 cj
		(ans += a[i] * a[j] % P * (fA + fB)) %= P;
	}
	printf("%lld", ans);
}
```

---


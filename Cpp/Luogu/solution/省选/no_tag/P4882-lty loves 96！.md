# lty loves 96！

## 题目背景

众所周知，$lty$非常喜欢$96$这两个数字（想歪的现在马上面壁去），更甚于复读~~（人本复）~~！

## 题目描述

由于爱屋及乌，因此，$lty$对于那些含有$96$的数也非常喜欢，而这里的含有不是一般的含有，而是具有以下性质的含有（三条都需要满足）：
* 这个数为一个$N$位数，且没有前置零
* 这个数中至少要出现$M$次$9$和$6$（例：$986996$中出现了$5$次，$9$出现了$3$次，$6$出现了$2$次，共计$5$次）
* 这个数存在连续的三位$A$,$B$,$C$，满足下面任意一条
	* $A+B+C$为$9$或$6$
	* $(A^2+B^2)$%$C$为$9$或$6$，如果$C$为$0$，则该条件视为不满足

## 说明/提示

对于10%的数据，$N<=6$

对于40%的数据，$N<=18$

对于100%的数据，$N<=50$，$0<=M<=N$


## 样例 #1

### 输入

```
3 1```

### 输出

```
16```

# 题解

## 作者：crpboy (赞：5)

看到只有递推版数位dp，来一发记搜版的数位dp（感觉会比递推好写很多），造福一下记搜党。

开始这道题前先说一句，题面有点模糊，事实上**只要**有任意连续$3$位$A,B,C$满足条件，就可以看做是满足条件$3$，而不是所有的$A,B,C$都满足条件才算满足条件$3$。

我们设$f[i][j][k][l][ok(0/1)]$表示做到第$i$位，有$j$个$6$或$9$，上一个是$k$，上上个是$l$，是否满足条件$3$的总方案数。

那么只需要搜索的时候判一下当前的数字和$k,l$是否满足第三点，更新一下是否满足条件就可以了。

具体还是看代码吧，注释还是很详细的。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=55;

namespace bignum
{
	#define re register
	const int base=10000;
	struct big
	{
		int a[15],n;
		big(const int x=0){memset(a,0,sizeof(a)),n=0;if(x)n=1,a[1]=x;}
		inline friend big operator+(const big &x,const big &y)
		{
			big ans;ans.n=max(x.n,y.n);
			for(re int i=1;i<=ans.n;i++)
			{
				ans.a[i]+=x.a[i]+y.a[i];
				if(ans.a[i]>=base)ans.a[i+1]++,ans.a[i]-=base;
			}
			while(ans.a[ans.n+1])ans.n++;
			return ans;
		}
		inline friend void operator+=(big &x,const big &y){x=x+y;}
	};
	inline void write(big x)
	{
		if(!x.n){putchar('0');return;}
		printf("%d",x.a[x.n]);
		for(re int i=x.n-1;i;i--)printf("%04d",x.a[i]);
	}
	#undef re
}using namespace bignum;
//压位高精

int n,m;
bool vis[N][N][12][12][2];//vis表示当前状态是否被访问过
big f[N][N][12][12][2];
big zero=0,one=1;
big dfs(int step,int cnt,int pre,int ppre,bool ok)//做到第几位，有几个6/9，上一位，上上位，是否满足条件3
{
	if(!step)return cnt>=m&&ok?one:zero;
	if(vis[step][cnt][pre][ppre][ok])return f[step][cnt][pre][ppre][ok];
	big res=0;
	for(int i=(step==n?1:0);i<=9;i++)
	{
		if(pre!=-1&&ppre!=-1)
		{
			int sum=pre+ppre+i,mod=!i?0:(pre*pre+ppre*ppre)%i;
			res+=dfs(step-1,cnt+(i==9||i==6),i,pre,ok||(sum==9||sum==6||mod==9||mod==6));//利用i,pre,ppre计算出来的sum,mod更新布尔变量ok
		}
		else res+=dfs(step-1,cnt+(i==9||i==6),i,pre,ok);//如果是数的前两位，就无法组成形如A,B,C的连续数字，因此不需要判断ok是否满足条件
	}
	vis[step][cnt][pre][ppre][ok]=true;
	return f[step][cnt][pre][ppre][ok]=res;
}

int main()
{
	cin>>n>>m;
	bool flag=false;
	if(n<=2)flag=true;//特判n<=2的情况，此时不需要考虑第三个条件，因此默认为true
	write(dfs(n,0,-1,-1,flag));
	return 0;
}
```

---

## 作者：Autream (赞：3)

#### 题意简述
求出位数为 $N$ 的满足以下条件的数的个数。

- 数字中 $9$ 和 $6$ 的个数和为 $M$。

- 存在连续三位数字 $A,B,C$，满足 $A+B+C$ 或 $(A^2+B^2) \operatorname{mod} C$ 为 $9$ 或 $6$。
---
#### 题目分析
数位 DP。

考虑设 $dp_{pos,sum,last1,last2,last3,flag}$ 表示当前填到第 $pos$ 位，有 $sum$ 个 $6$ 和 $9$，前三个数字分别是 $last1,last2,last3$ 的情况下是否满足条件。

注意性质 $2$ 中的 $(A^2+B^2) \operatorname{mod} C =9$ 或 $6$，因为一位数除以一位数不可能等于 $9$，所以相当于只用判断余数为 $6$ 的情况。

**注意：因为本题数据很大，且没有取模，所以要用高精度**

---
#### AC Code
```cpp
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)a[i]=read()
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define il inline
#define ss second
#define ff first
#define itn int
int read() {
    char ch=getchar();
    int r=0,w=1;
    while(ch<'0'||ch>'9') w=ch=='-'?-1:w,ch=getchar();
    while(ch>='0'&&ch<='9') r=r*10+ch-'0',ch=getchar();
    return r*w;
}
struct huge {//高精度
    int a[15],len;
    huge(const int x=0) {
        mem(a,0);
        len=0;
        if(x) {
            len=1;
            a[1]=x;
        }
    }
    friend huge operator+(const huge& x,const huge& y) {
        huge ans(0);
        ans.len=std::max(x.len,y.len);
        rep(i,1,ans.len) {
            ans.a[i]+=x.a[i]+y.a[i];
            if(ans.a[i]>=10000) {
                ans.a[i]-=10000;
                ans.a[i+1]++;
            }
        }
        while(ans.a[ans.len+1]) {
            ans.len++;
        }
        return ans;
    }
    friend huge operator+=(huge& x,const huge& y) {
        x=x+y;
    }
};
void print(huge x) {
    if(!x.len) {
        putchar('0');
        return;
    }
    printf("%d",x.a[x.len]);
    dep(i,x.len-1,1) {
        printf("%04d",x.a[i]);
    }
}
CI N=1e5+5;
int n,m,a[50];
bool vis[55][55][10][10][2];//用来做记搜的标记
huge dp[55][55][10][10][2];
huge _0=0,_1=1;
huge dfs(int pos,int sum,int last1,int last2,bool flag1,int st) {
    if(pos>n) {
        if(sum>=m&&flag1&&!st) {//只有满足条件才返回1
            return _1;
        }
        return _0;
    }
    if(vis[pos][sum][last1][last2][flag1]&&!st) {
        return dp[pos][sum][last1][last2][flag1];
    }
    int down=0;
    huge ans=_0;
    if(pos==1) {
        down=1;
    }
    rep(i,down,9) {
        a[pos]=i;
        if(pos<3) {//last1,last2,last3不全不为-1
            ans=ans+dfs(pos+1,sum+(i==6||i==9),i,last1,0,st&&!i);
        } else {
            ans=ans+dfs(pos+1,sum+(i==6||i==9)/*记录6，9的个数*/,i,last1,flag1||((i+last1+last2)==9||(i+last1+last2)==6)||i&&(last2*last2+last1*last1)%i==6/*判断性质2*/,st&&!i);
        }
    }
    if(!st) {
        vis[pos][sum][last1][last2][flag1]=1;
        dp[pos][sum][last1][last2][flag1]=ans;
    }
    return ans;
}
huge solve(int x) {
    mem(dp,-1);
    return dfs(1,0,0,0,0,1);
}
signed main() {
    n=read(),m=read();
    print(solve(n));
    return 0;
}
```

---

## 作者：DPair (赞：2)

提供一种不用高精度的做法（或者说高精度的特殊写法）。

## 【思路】
首先判断这是一道数位 DP。

设 $dp[x][cnt][a][b][ck=0/1]$ 表示到了第 $i$ 位，有 $cnt$ 个 $96$ ，前前一位是 $a$，前一位是 $b$ ，目前存不存在满足题意的连续三位的方案数。

转移方程很简单，按题意转移即可，这不是本题的重点，个人感觉本题主要烦在高精。

然后估计答案会很大，开了`__int128` 交上去，仍然挂了。

但是转念一想答案也不会太大，我又懒得写高精，怎么办呢？

可以写一个只有两位的高精，由于本题只有加法，压位可以压很多，我压了 $30$ 位。

然后就很好写了，在原先的基础上改一下输出 + 重载加法就做完了，而且码量小跑得快。

具体实现看代码，应该一眼就能看懂。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() printf("I am a cheater!I AK IOI!%c", 10)
template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
typedef __int128 LL;
LL limit = 1;
inline void init(){for (register int i = 1;i <= 30;i ++) limit *= 10;}//似乎不能正常初始化？
template <typename T>
inline void fprint(T x){
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}
inline char next_char(){
    char ch = getchar();
    while(ch == 9 || ch == 10 || ch == 32) ch = getchar();
    return ch;
}

struct int256{//实际上远远不到2^256
    LL x, y;
    int256(LL tmp1 = 0, LL tmp2 = 0) : x(tmp1), y(tmp2){}
    inline void print(char ch){
        LL tmp1 = x, tmp2 = y;
        if(tmp1) {
            fprint(tmp1);
            LL tmp = limit / 10;
            while(y < tmp) putchar(48), tmp /= 10;
            if(tmp2 > 0) fprint(tmp2, ch);
            else putchar(ch);
        }
        else fprint(tmp2, ch);
    }
    inline int256 operator + (const int256 &b) const{return int256(x + b.x + ((y + b.y) / limit), (y + b.y) % limit);}
};

int256 dp[55][55][11][11][2];
bool vis[55][55][11][11][2];
int n, m;
int256 dfs(int x, int cnt, int a, int b, bool ck){
    if(x > n) return int256(0, cnt >= m && ck);
    if(vis[x][cnt][a][b][ck]) return dp[x][cnt][a][b][ck];
    vis[x][cnt][a][b][ck] = 1;
    int fst = (x == 1)? 1 : 0;
    int256 ret;
    for (register int i = fst;i <= 9;i ++){
        ret = ret + dfs(x + 1, cnt + (i == 6 || i == 9), b, i, ck || ((x >= 3) && (a + b + i == 6 || a + b + i == 9 || (i && (((a * a) + (b * b)) % i == 6 || ((a * a) + (b * b)) % i == 9)))));//状态转移，就一行。
    }
    return dp[x][cnt][a][b][ck] = ret;
}

int main(){
    init();
    read(n);read(m);
    dfs(1, 0, 0, 0, 0).print(10);
}
```

---

## 作者：Wolfycz (赞：2)

这题是个数位dp题~~（本来N<=18）~~

好像有人对题意不太明白，这题要满足三个大点，满足第三个大点只需满足任意一个小点，ABC是连续的，从高到低的三位数

设$f[i][j][x][y][0/1]$代表枚举到第$i$位，有$j$位为6或9，第$i,i-1$位为$x,y$，是否满足条件

转移的话不难，当x,y,z不满足条件时：
$$f[i][j][x][y][0]+=f[i-1][j-check(i)][y][z][0],f[i][j][x][y][1]+=f[i-1][j-check(i)][y][z][0]$$
其中$check(i)$是判断$i$是否为6或9
否则：
$$f[i][j][x][y][1]=f[i-1][j-check(i)][y][z][0]+f[i-1][j-check(i)][y][z][1]$$

至于$f$数组的类型

int？10pts；long long？30pts；int 128？ 85pts（用int 128的真的是大佬，让我猝不稽防，还好只有85pts，逃）

肯定是要用高精度的啦~

不过如果没有压位，那就是0分（64M也是我干的，有人考试的时候被卡了吗，逃），但是只需要压任意几位就不会MLE了

``` cpp
/*program from Wolfycz*/
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define inf 0x7f7f7f7f
#define sqr(x) ((x)*(x))
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for (;ch<'0'||ch>'9';ch=getchar())	if (ch=='-')	f=-1;
	for (;ch>='0'&&ch<='9';ch=getchar())  x=(x<<1)+(x<<3)+ch-'0';
	return x*f;
}
inline void print(int x){
	if (x>=10)	 print(x/10);
	putchar(x%10+'0');
}
const int N=51;
const int digit=8;
const int base=1e8;
const int maxn=10;
struct Bignum{
	int len,v[maxn];
	Bignum(){len=1,memset(v,0,sizeof(v));}
	void init(){v[0]=1;}
	void write(){
		printf("%d",v[len-1]);
		for (int i=len-2;~i;i--)	printf("%0*d",digit,v[i]);
		putchar('\n');
	}
}f[N][N][10][10][2];
Bignum operator +(const Bignum &x,const Bignum &y){
	Bignum z;
	z.len=max(x.len,y.len);
	for (int i=0;i<=z.len;i++)	z.v[i]+=x.v[i]+y.v[i],z.v[i+1]+=z.v[i]/base,z.v[i]%=base;
	while (z.v[z.len])	z.v[z.len+1]+=z.v[z.len]/base,z.v[z.len]%=base,z.len++;
	return z;
}
bool T(int x){return x==9||x==6;}
void Inc(Bignum &x,Bignum y){x=x+y;}
void prepare(){
	for (int i=0;i<10;i++)
		for (int j=0;j<10;j++)
			f[2][T(i)+T(j)][i][j][0].init();
	for (int i=3;i<N;i++){
		for (int x=0;x<10;x++){
			for (int y=0;y<10;y++){
				for (int z=0;z<10;z++){
					for (int l=0;l<i;l++){
						Inc(f[i][l+T(x)][x][y][1],f[i-1][l][y][z][1]);
						if (T(x+y+z)||(z&&T((sqr(x)+sqr(y))%z)))
							Inc(f[i][l+T(x)][x][y][1],f[i-1][l][y][z][0]);
						else	Inc(f[i][l+T(x)][x][y][0],f[i-1][l][y][z][0]);
					}
				}
			}
		}
	}
}
void solve(int n,int m){
	if (n==1){
		printf(!m?"9\n":"2\n");
		return;
	}
	if (n==2){
		printf(!m?"90\n":m==1?"34\n":"4\n");
		return;
	}
	Bignum res;
	for (int x=1;x<10;x++)
		for (int y=0;y<10;y++)
			for (int l=m;l<=n;l++)
				Inc(res,f[n][l][x][y][1]);
	res.write();
}
int main(){
	prepare();
	int n=read(),m=read();
	solve(n,m);
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

一眼数位 dp。

设 $dp_{i,j,x,y,0/1}$ 表示正在填从高到低的第 $i$ 位，之前有 $j$ 个 $6$ 或 $9$，上一位是 $x$，上上位是 $y$，是否已满足条件。

那么枚举当前位要填的数字 $k\in[[i=n],9]$，继续往下递归求解就好了。边界情况为 $i=0$ 时若 $j\ge m$ 且已满足条件答案为 $1$，否则为 $0$。

需要注意的是 $n$ 可能小于 $3$，此时总共都没有 $3$ 位用来判断，直接 ~~打表~~ 把条件设为已被满足。

看到这里，相信此时你已经能打出下面这份代码。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
ll dp[55][55][15][15][2];
int n,m;
ll dfs(int dep,int cnt,int pre1,int pre2,int ok){
	if(!dep)return cnt>=m&&ok;
	ll&res=dp[dep][cnt][pre1+1][pre2+1][ok];
	if(~res)return res;
	res=0;
	for(int i=(dep==n);i<=9;++i)
		if(~pre2)
			res+=dfs(dep-1,cnt+(i==6||i==9),i,pre1,ok||(i+pre1+pre2==6||i+pre1+pre2==9||(i&&((pre1*pre1+pre2*pre2)%i==6||(pre1*pre1+pre2*pre2)%i==9))));
		else res+=dfs(dep-1,cnt+(i==6||i==9),i,pre1,ok);
	return res;
}
int main(){
	memset(dp,-1,sizeof(dp));
	scanf("%d%d",&n,&m);
	printf("%lld",dfs(n,0,-1,-1,n<=2));
	return 0;
}
```

哪里有问题吗？

不妨输入个稍大一点的数据：`40 0`，然后你发现它输出了负数。

乐。

好吧，说明爆 `long long` 了。于是你兴致冲冲地换上了 `__int128` 并打了个输出模板，再次输入了 `40 0`，然后它又输出负数了。

所以打高精吧。

---

## 作者：Rainybunny (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[$luogu$](https://www.luogu.org/problem/P4882).
# 题解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~本文卒章显志...~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;一道比较板的数位$DP$题. 令状态$f(x,cnt,A,B,0/1)$表示**确定 ( 从高位起 ) 第$x$数字前, 已经有$cnt$个$6/9$, 前两个数字分别是$A,B$, 是否已经满足条件$3$的合法数字总数**. 状态转移也比较简单, 我们只需要考虑第$x$位数字对$cnt$和条件$3$的影响就行了. 所以:  
$$f(x,cnt,A,B,k)=\sum_{i=[x=1]}^9f(x+1,cnt+chk_1(i),B,i,k\vee chk_2(A,B,i))$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;其中, $chk_1(i)$表示$i$是否是$6/9$;  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;( 即$chk_1(i)=([i=6]\vee[i=9])$. )  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$chk_2(A,B,i)$表示有序对$(A,B,i)$是否满足条件$3$.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;( 即$chk_2(A,B,i)=(chk_1(A+B+i)\vee[i\not=0\wedge chk_2((A^2+B^2)\%i)])$. )  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑边界情况, 当$x=n+1$是, 数字已经全部确定, 判断是否合法即可. 故有:  
$$f(n+1,cnt,A,B,k)=[m\le cnt]\vee k$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;最后, 告诉大家一个噩耗, 本题要写高精$QwQ!$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;上记搜代码:
```cpp
#include <cstdio>
#include <cstring>

#define Int register int

const int MAXN = 50;
int n, m;
bool Vis[MAXN + 5][MAXN + 5][11][11][2] = {};
/*
Vis用于记忆化, 由于我用A/B=-1表示还不存在前面的数字, 在存储时把A, B都加一.
即f ( x, cnt, A, B, k ) -> Vis[x][cnt][A + 1][B + 1][k]. 
*/

struct BigInt { // 高精需要压位存储 
	static const int MOD = 10000;
	int l, num[20];
	BigInt () {
		l = 1, memset ( num, 0, sizeof num ); 
	}
	BigInt ( int x ) {
		l = 0, memset ( num, 0, sizeof num );
		while ( x ) num[++ l] = x % MOD, x /= MOD;
		l += ! l;
	}
	inline void Print () const {
		printf ( "%d", num[l] );
		for ( Int i = l - 1; i; -- i ) printf ( "%04d", num[i] );
		putchar ( '\n' );
	}
	inline int& operator [] ( const int Key ) {
		return num[Key];
	}
	friend inline BigInt operator + ( BigInt a, BigInt b ) {
		BigInt ret ( 0 );
		int x = 0;
		while ( ret.l <= a.l || ret.l <= b.l ) {
			ret[ret.l] = a[ret.l] + b[ret.l] + x;
			x = ret[ret.l] / MOD;
			ret[ret.l ++] %= MOD;
		}
		if ( x ) ret[ret.l] = x;
		while ( ! ret[ret.l] && ret.l > 1 && -- ret.l );
		return ret;
	}
	friend inline BigInt& operator += ( BigInt& a, BigInt b ) {
		return a = a + b;
	}
} F[MAXN + 5][MAXN + 5][11][11][2] = {}; // 状态所对应的值, 存储规则同Vis 

inline bool chk ( const int x ) { return x == 6 || x == 9; } 

inline BigInt DFS ( const int x, const int Cnt, const int A, const int B, const bool cdt3 ) {
	if ( x > n ) return m <= Cnt && cdt3; // 边界判定 
	if ( Vis[x][Cnt][A + 1][B + 1][cdt3] ) return F[x][Cnt][A + 1][B + 1][cdt3]; // 记忆化 
	BigInt ret ( 0 );
	for ( Int i = x == 1; i <= 9; ++ i ) {
		if ( ~ A && ~ B ) { // 存在前两位数 
			int s = A + B + i, md = i ? ( A * A + B * B ) % i : -1;
			ret += DFS ( x + 1, Cnt + chk ( i ), B, i, cdt3 || chk ( s ) || chk ( md ) );
		} else { // 不存在, 则对cdt3无影响 
			ret += DFS ( x + 1, Cnt + chk ( i ), B, i, cdt3 );
		}
	}
	Vis[x][Cnt][A + 1][B + 1][cdt3] = true;
	return F[x][Cnt][A + 1][B + 1][cdt3] = ret;
}

inline void Work () {
	scanf ( "%d %d", &n, &m );
	DFS ( 1, 0, -1, -1, n <= 2 ).Print (); // 初始状态n <= 2, 由于此时规则3无效, 视为全部合法 
}

int main () {
	Work ();
	return 0;
}
```

---
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;警告, 本文正经环节已结束, 赶快去做题$x$.  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;#关于我为什么想做这道题#:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"这道题, 嗯...就我一个人把$lty$拼成了洛天依?"  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"题面好像对我家天依不太友善$x$." ( 满脸黑线. )  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$...$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"$woc$看我把这道题切了写篇题解! 锦依卫啊, 让我看到你们的双手!" ( 丧心病狂. )

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/献上亿枚滑稽.

---


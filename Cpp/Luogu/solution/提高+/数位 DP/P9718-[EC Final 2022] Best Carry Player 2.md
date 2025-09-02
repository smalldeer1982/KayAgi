# [EC Final 2022] Best Carry Player 2

## 题目描述

给定一个正整数 $x$，找到最小的正整数 $y$，使得 $x+y$ 的 $\textbf{进位}$ 数量恰好为 $k$。

我们按照十进制中的列加法进行相加，就像我们在小学时所做的那样。例如，下面的加法中有两次进位。

![](https://cdn.luogu.com.cn/upload/image_hosting/pfnper3r.png)

## 样例 #1

### 输入

```
4
12345678 0
12345678 5
12345678 18
990099 5```

### 输出

```
1
54322
999999999987654322
9910```

# 题解

## 作者：___w (赞：5)

#### [P9718 [EC Final 2022] Best Carry Player 2](https://www.luogu.com.cn/problem/P9718)

进位这东西只能是从低位到高位考虑的吧，每位进不进位会影响下一位要填的数。

考虑数位 dp，从低位向高位填数字，设计状态 $f_{i,j,p}$ 表示当前第 $i$ 位，填完第 $i$ 个数字共进了 $j$ 位，当前这位是否有向前进 $1$，其中 $0$ 表示没有，$1$ 表示有。

这里设 $x$ 从右到左第 $i$ 位的值为 $a_i$，位权为 $w_i$（下标从 $1$ 开始编号）。

显然有

$$
f_{i,j,0}=\min\begin{cases}
  f_{i-1,j,1} & a_i<9 \\
  f_{i-1,j,0}
\end{cases}
$$

$$
f_{i,j,1}=\min\begin{cases}
  f_{i-1,j-1,1}+w_i(10-a_i-1) \\
  f_{i-1,j-1,0}+w_i(10-a_i) & a_i>0
\end{cases}
$$

但是这里题目要求的是正整数，不能为 $0$，但是注意到当答案为 $0$ 当且仅当 $k=0$，特判下就好了。

但是在写代码的时候被下面数据薄纱了

```cpp
1
100000000000000000 18
```

原因是后面连续的 $0$ 不能提供进位，而且整个答案的长度就会变得很长，会爆 ```long long```，因此我们只需把后面连续的 $0$ 去掉并最后加在答案上即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define ll long long
#define space putchar(' ')
#define enter putchar('\n')
using namespace std;

inline int read() {
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') f = c == '-' ? -1 : f, c = getchar();
	while (c >= '0' && c <= '9') x = (x<<3)+(x<<1)+(c^48), c = getchar();
	return x*f;
}

inline void write(int x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x/10);
	putchar('0'+x%10);
}

const int N = 20;
int lim = 19, a[N], w[N], f[N][N][2];

inline void upd(int &x, int y) { x = y < x ? y : x; }

inline void solve() {
	int x = read(), k = read(), cnt = 0;
	if (!k) {
		while (x%10 == 9) ++cnt, x /= 10;
		return (void)(write(w[cnt+1]), enter);
	}
	while (x%10 == 0) ++cnt, x /= 10;
	for (int i = 1; i <= lim; ++i) a[i] = x%10, x /= 10;
	memset(f, 0x3f, sizeof(f)), f[0][0][0] = 0;
	for (int i = 1; i <= lim; ++i)
		for (int j = 0; j <= k; ++j) {
			upd(f[i][j][0], f[i-1][j][0]);
			if (a[i] < 9) upd(f[i][j][0], f[i-1][j][1]);
			if (!j) continue;
			upd(f[i][j][1], f[i-1][j-1][1]+w[i]*(10-a[i]-1));
			if (a[i]) upd(f[i][j][1], f[i-1][j-1][0]+w[i]*(10-a[i]));
		}
	write(f[lim][k][0]);
	while (cnt--) write(0); enter;
}

signed main() {
	w[1] = 1;
	for (int i = 2; i <= lim; ++i) w[i] = w[i-1]*10;
	int t = read();
	while (t--) solve();
	return 0;
}
```

---

## 作者：disangan233 (赞：4)

考场上 +3 的代码，怎么糊了个最优解。

可以发现 $1\sim 8$ 都可以每一位独立讨论进位。

- 对于 $0$，必须要 $y$ 当前位是 $9$ 且前一位进位才可以进位；
- 对于 $9$，如果前一位有进位，那么无论 $y$ 是多少都会进位；
- 所以对于一段连续的 $9$，可能导致进位数 $>k$ 的情况。

直接从小到大贪心每一位是不对的，考虑 $99909990$，$k=4$ 的例子，答案为 $101000$。

去除最后的 $0$ 后，直接取最低 $k$ 位：

- 如果第 $k$ 位进位前面不是 $9$，那么直接构造；
- 前面是一段 $9$ 时，为了让 $y$ 最小，让这段 $9$ 取最低的进位，从高到低构造至刚好进位数 $=k$ 为止；
- 如果最后刚好是 $0$，往前找到第一个非 $0$ 处更新这段 $9$，然后重复构造；
- 如果 $k$ 大于位数，往前补 $9$，注意特判 $k=0$。

时间复杂度 $O(T\log_{10} x)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define in inline
#define ld long db
namespace fast_io
{
	char buf[1<<12],*p1=buf,*p2=buf,sr[1<<23],z[23],nc;int C=-1,Z=0,Bi=0,ny;
	in char gc() {return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<12,stdin),p1==p2)?EOF:*p1++;}
	in ll read()
	{
		ll x=0;ny=1;while(nc=gc(),(nc<48||nc>57)&&nc!=EOF)if(nc==45)ny=-1;Bi=1;if(nc<0)return nc;
		x=nc-48;while(nc=gc(),47<nc&&nc<58&&nc!=EOF)x=(x<<3)+(x<<1)+(nc^48),Bi++;return x*ny;
	}
	in db gf() {int a=read(),y=ny,b=(nc!='.')?0:read();return (b?a+(db)b/pow(10,Bi)*y:a);}
	in int gs(char *s) {char c,*t=s;while(c=gc(),c<=32);*s++=c;while(c=gc(),c>32)*s++=c;return s-t;}
	in void ot() {fwrite(sr,1,C+1,stdout);C=-1;}
	in void flush() {if(C>1<<22) ot();}
	template <typename T>
	in void write(T x,char t)
	{
		int y=0;if(x<0)y=1,x=-x;while(z[++Z]=x%10+48,x/=10);
		if(y)z[++Z]='-';while(sr[++C]=z[Z],--Z);sr[++C]=t;flush();
	}
	in void write(char *s) {int l=strlen(s);for(int i=0;i<l;i++)sr[++C]=*s++;sr[++C]='\n';flush();}
}
using namespace fast_io;
const int N=1e5+5;
int T,n,k;
ll pw[20];
char s[20],t[20];
void upd(int l,int r)
{
	t[r]='9'-s[r]+'0'+1,k--;
	for(int i=l;i<r;i++)
	t[i]='9'-s[i]+'0',k--;
	if(l>1&&t[l-1]>'0') t[l-1]--;
}
void output(int l,int r)
{
	for(int i=l;i<=n;i++) if(!t[i]) t[i]='0';
	while(t[l]=='0') l++;
	puts(t+l);
}
int main()
{
	pw[0]=1;for(int i=1;i<20;i++) pw[i]=pw[i-1]*10;
	T=read();
	while(T--)
	{
		memset(s,0,sizeof(s)),memset(t,0,sizeof(t));
		n=gs(s+1),k=read();
		if(!k)
		{
			int op=0;
			for(int i=n;i;i--) if(s[i]^'9')
			{
				printf("%lld\n",pw[n-i]);
				op=1;break;
			}
			if(!op) printf("%lld\n",pw[n]);
			continue;
		}
		int r=n;while(s[r]=='0') r--;
		int l=r-k+1;
		if(l<1)
		{
			for(int i=r+1;i<=n;i++) t[i]='0';
			upd(1,r);
			while(k--) putchar('9');
			puts(t+1);
			continue;
		}
		if(l==1||s[l-1]^'9')
		{
			upd(l,r);output(l,r);
			continue;
		}
		while(l>1&&s[l-1]=='9') l--; //99999xxxxxxx000
		while(k)
		{
			int i=r-k+1;
			if(s[i-1]^'9') {upd(i,r);continue;}
			while(s[i-1]=='9') i--;
				int j=i+k-1;
				while(s[j]=='0') j--;
				if(i>j) continue;
				upd(i,j),i=j;

		}
		output(l,r);
	}
    return 0;
}
/*
2
999901 5
919991 6

1
999990000099999 10
---
10000000001
---
10999910000

1
100919919990991119 8
---
9008900
*/
```

---

## 作者：Ericnoi (赞：1)

# P9718 题解

[题目传送门](https://www.luogu.com.cn/problem/P9718)

# 思路
看到这惊人的数据范围，就知道这道题是数位 DP 没跑了。数位 DP 的基本套路就是记搜。要想记搜我们首先需要定义状态空间。

我们定义 $dp_{i,j,k}(k\in \{0,1\})$ 为最低的 $i$ 位**正好**进位 $j$ 次所需要的最小加数。$k$ 表示第 $i$ 位会不会产生进位。

我们令 $dp_{0,0,0}=0,dp_{0,j,k}(j\neq 0\lor k\neq 0)=+\infty,dp_{i,j,k}(j<0)=+\infty$。令 $a_i$ 为从低到高的第 $i$ 位，于是我们可以列出转移方程如下：

$$dp_{i,j,0}= \min(\min_{x=0}^{9-a_i}(10^{i-1}\times x+dp_{i-1,j,0}), \min_{x=0}^{8-a_i}(10^{i-1}\times x+dp_{i-1,j,1}))$$

$$dp_{i,j,1}= \min(\min_{x=10-a_i}^{9}(10^{i-1}\times x+dp_{i-1,j-1,0}), \min_{x=9-a_i}^{9}(10^{i-1}\times x+dp_{i-1,j-1,1}))$$

然后在框架上记忆化搜索一下即可，实际实现的时候还要考虑前导零问题。

但是，你会发现还会有很多阴间数据使你过不了这道题。下面我将列出一些我造的数据，你可以很容易地发现自己的程序里全是漏洞：

Hack 1:
```
input:
1
100000000000000000 18
output:
99999999999999999900000000000000000
```
后面跟随的一大串 $0$ 会使得程序爆 ```unsigned long long```。我们将结尾的 $0$ 提取出来计算完成后用字符的形式输出即可。

其次输出的前半部分 $999999999999999999$ 会爆 ```long long```，但是正好不爆 ```unsigned long long```，所以说程序中要使用 ```unsigned long long``` 并注意不要使 ```unsigned long long``` 溢出了（这么阴间的题到底是谁想的）。

Hack 2:
```
input:
1
99099 3
output:
1010
```
这告诉我们直接从小到大贪心是不可取的，因为题目要求**正好** $k$ 次。

Hack 3:
```
input:
1
1090 0
output:
1
```
在通过了 Hack 1 之后，你是不是应该特判一下 $k = 0$ 的情况？从后往前找第一个不等于 $9$ 的数位即可。如果你没有特判的话，我猜你的程序输出了 $10$ 或 $100$。第 $2$ 个、第 $3$ 个测试点就含有类似的数据。

Hack 4:
```
input:
2
99999 0
9 0
output:
100000
10
```
如果特判时你的 $a$ 数组忘记先清空了，你将会在第 $15$ 个测试点栽跟头。

这就是我犯的所有错误，希望可以帮助到大家。如果你有被 Hack 到，就给我的题解点个赞吧。

# AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define LIMIT (ULLONG_MAX)
#define fill(x, y) memset(x, y, sizeof(x))
#define chkmax(x, y) ((x) = max((x), (y)))
#define chkmin(x, y) ((x) = min((x), (y)))
#define isnumber(x) (((x) >= '0') && ((x) <= '9'))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template<typename T>
inline T read(T &x) {
	T f = 1; x = 0; char s = getchar();
	while(!isnumber(s)) {if(s == '-') f = -1; s = getchar();}
	while(isnumber(s)) x = (x << 1) + (x << 3) + (s ^ '0'), s = getchar();
	return x *= f;
}
template<typename T>
inline void print(T x, char suf = 0, int base = 10) {
	if(x < 0) {putchar('-'); x = -x;}
	if(x >= base) print(x / base, 0, base);
	putchar(48 ^ (x % base));
	if(suf) putchar(suf);
}
int cx = 1;
const int N = 20;
ull a[N], pow10[N]; // pow10[i] = 10^(i-1)
ull dp[N][N][2][2];
bool vis[N][N][2][2];
ull dfs(int p, int k, bool carry, bool st) {
	if(k < 0) return LIMIT; // 不合法的状态
	if(p == 0) {
		if(!st) return LIMIT;
		if(carry) return LIMIT;
		if(k == 0) return 0; // 合法
		return LIMIT;
	}
	ull& ref = dp[p][k][carry][st];
	if(vis[p][k][carry][st]) return ref;
	vis[p][k][carry][st] = 1;
	ull res = LIMIT;
	for(int i = 0 ; i <= 9 ; i++) { // not carry
		if(carry) {
			if(i + a[p] <= 9) continue;
			ull x = dfs(p - 1, k - 1, 0, st || (i != 0));
			if(x != LIMIT) chkmin(res, pow10[p] * i + x);
		}
		else {
			if(i + a[p] >= 10) continue;
			ull x = dfs(p - 1, k, 0, st || (i != 0));
			if(x != LIMIT) chkmin(res, pow10[p] * i + x);
		}
	}
	for(int i = 0 ; i <= 9 ; i++) { // carry
		if(carry) {
			if(i + a[p] + 1 <= 9) continue;
			ull x = dfs(p - 1, k - 1, 1, st || (i != 0));
			if(x != LIMIT) chkmin(res, pow10[p] * i + x);
		}
		else {
			if(i + a[p] + 1 >= 10) continue;
			ull x = dfs(p - 1, k, 1, st || (i != 0));
			if(x != LIMIT) chkmin(res, pow10[p] * i + x);
		}
	}
	return ref = res;
}
void count(int x, int k) {
	int tot = 0, cnt = 0;
    fill(a, 0x0);
	if(k == 0) { // 特判
		while(x) {
			a[++tot] = x % 10;
			x /= 10;
		}
		int p = 1;
		while(a[p] == 9) p++;
		putchar('1');
		for(int i = 1 ; i < p ; i++) {
			putchar('0');
		}
		putchar('\n');
		return ;
	}
	while(x % 10 == 0) { // 去0
		x /= 10;
		cnt++;
	}
	fill(a, 0x0);
	while(x) {
		a[++tot] = x % 10;
		x /= 10;
	}
	pow10[1] = 1;
	for(int i = 2 ; i <= 18 ; i++) {
		pow10[i] = pow10[i-1] * 10;
	}
	ull ans = LIMIT;
	fill(vis, 0x0);
	chkmin(ans, dfs(18, k, 0, 0));
	fill(vis, 0x0);
	chkmin(ans, dfs(18, k, 1, 0));
	if(ans == LIMIT) {
		puts("-1");
		return ;
	}
	print(ans);
	while(cnt--) { // 加0
		putchar('0');
	}
	putchar('\n');
}
void solve() {
	int n, k;
	read(n), read(k);
	count(n, k);
}
signed main() {
    read(cx);
    while(cx--) {
        solve();
    }
    // cerr << clock() - st_t << "ms" << endl; 
    return 0;
}
```

---

## 作者：lfxxx (赞：1)

比较好的一道题目。

对于每一次询问，考虑数位 $dp$，具体来说定义状态 $dp_{i,j}$ 表示考虑前 $i$ 位 **恰好** 有 $j$ 个进位并且第 $i$ 位有进位的最小代价，转移分为从上一位转移或者从前面的位置转移两种，第一种可以省掉一个上一位进位的 $1$ 第二种需要保证转移来的位置不会对后面一个位置产生额外的进位，且第二种转移能否成立之与 $j$ 有关，所以不妨把 $j$ 相同的状态放在一起取最小值，便可以做到单次 $\log^2 V$，因此总的时间复杂度就是 $O(T \log^2 V)$。

```cpp
#include<bits/stdc++.h>
#define int __int128
namespace IO{
	const int SIZE=1<<21;
	static char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=oS+SIZE-1;
    int qr;
    char qu[55],c;
    bool f;
	#define getchar() (IO::iS==IO::iT?(IO::iT=(IO::iS=IO::ibuf)+fread(IO::ibuf,1,IO::SIZE,stdin),(IO::iS==IO::iT?EOF:*IO::iS++)):*IO::iS++)
	#define putchar(x) *IO::oS++=x,IO::oS==IO::oT?flush():0
	#define flush() fwrite(IO::obuf,1,IO::oS-IO::obuf,stdout),IO::oS=IO::obuf
	#define puts(x) IO::Puts(x)
	template<typename T>
    inline void read(T&x){
    	for(f=1,c=getchar();c<48||c>57;c=getchar())f^=c=='-';
    	for(x=0;c<=57&&c>=48;c=getchar()) x=(x<<1)+(x<<3)+(c&15); 
    	x=f?x:-x;
    }
    template<typename T>
    inline void write(T x){
        if(!x) putchar(48); if(x<0) putchar('-'),x=-x;
        while(x) qu[++qr]=x%10^48,x/=10;
        while(qr) putchar(qu[qr--]);
    }
    inline void Puts(const char*s){
    	for(int i=0;s[i];i++)
			putchar(s[i]);
		putchar('\n');
	}
	struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}
using IO::read;
using IO::write;
using namespace std;
int x,k;
int dp[50][50];
int _pow[50];
int mini[50];
int inf;
inline int jin(int x,int y){
	int s1=0,s2=0;
	int i=1,ret=0;
	while(x||y){
		s1=s1+(x-(x/10)*10)*_pow[i-1];
		s2=s2+(y-(y/10)*10)*_pow[i-1];
		if(s1+s2>=_pow[i]) ret++;
		x/=10,y/=10;
		i++;
	}
	return ret;
}
void work(){
    read(x);
    read(k);
    if(k==0){
        int res=1;
        while(x%10==9){
            res*=10;
            x/=10;
        }
        write(res);
        return ;
    }    
    vector<int> dight;
    int X=x;
    while(x>0){
        dight.push_back(x%10);
        x/=10;
    }
    while(dight.size()<=36){
        dight.push_back(0);
    }
    for(int i=0;i<=40;i++)
        for(int j=0;j<=40;j++) dp[i][j]=(int)inf,mini[i]=(int)inf;
    for(int i=0;i<dight.size();i++){
        if(dight[i]!=0) dp[i][1]=min(dp[i][1],(10-dight[i])*_pow[i]);
        if(i==0) continue;
        for(int j=1;j<=k;j++){
            if(dp[i-1][j-1]<inf) dp[i][j]=min(dp[i][j],dp[i-1][j-1]+(10-dight[i]-1)*_pow[i]);
            if(dight[i]!=0&&mini[j-1]<inf) dp[i][j]=min(dp[i][j],mini[j-1]+(10-dight[i])*_pow[i]);
        }            
        for(int j=1;j<=k;j++) if((X/_pow[i])%10!=9) mini[j]=min(mini[j],dp[i-1][j]);
    }
    int ans=inf;
    for(int i=0;i<=36;i++){
    	if(dp[i][k]>=inf) continue;
        if(jin(X,dp[i][k])==k){
            ans=min(ans,dp[i][k]);
        }
    }
    write(ans);
    return ;
}
signed main(){
    _pow[0]=1;
    for(int i=1;i<=36;i++) _pow[i]=_pow[i-1]*10;
    inf=_pow[36];
    int t;
    read(t);
    while(t--) work(),putchar('\n');
}

```


---

## 作者：TLE_AK (赞：0)

#### 题意
给定一个数 $x(1 \le x \le 10^{18})$，求最小的正整数 $y$ 使 $x+y$ 正好进 $k(0 \le k \le 18)$ 次位。
## 思路
首先看到如此大的范围，又因为**每次进位会影响后面的变化**，考虑数位dp。
数位dp最常见的便是记忆化搜索，考虑状态设 $f(i,j,0/1)$ 表从个位起第 $i$ 位已经进位了 $j$ 次，这一位要不要进 $1$ 此时满足条件的最小值。 

考虑转移：让每位的值最小（$A_i$ 指 $x$ 的第 $i$项）。  
当 $k=0$ 时，因为没有贡献，所以直接取 $0$，可以从 $f(i-1,j,0)$ 和 $f(i-1,j,1)$ 转移，但要注意当 $A_i$ 为 $9$ 时，不能从 $f(i-1,j,1)$ 转移（因为会进位了）。  
当 $k=1$ 时，会在该位上产生一定贡献，可以由 $f(i-1,j-1,0)+(10-A_i) \times 10^{i-1}$ 和 $f(i-1,j,1)$ 转移而来，同理，当转移 $f(i-1,j-1,0)$ 时，$A_i > 0$。

最后下限可以确定为 $f(0,0,0=0)$，由于 $y$ 最大为 $18+18=36$ 位，所以直接开搜就行！

爆`long long`？使用`__int128`即可！
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

namespace acac
{
	__int128 dp[50][22][4];
	char A[210],B[210];
	int len,k;
	
	
	
	__int128 ksm(int k)//快速幂（pow是double的） 
	{
		__int128 ans=1,bs=10;
		while(k)
		{
			if(k&1)ans*=bs;
			bs*=bs;
			k>>=1;
		}
		return ans;
	}
	
	void write(__int128 x)//__int128快写 
	{
		char a=x%10;
		if(x>9)write(x/10);
		cout<<char(a+'0');
	}
	
	__int128 inf=ksm(38);
	
	__int128 dfs(int w,int now,int jw)//记搜（第几位，进几次位，要不要进1） 
	{
		if(!w)return (!now&&!jw)?0:inf;
		if(now==-1)return inf;//不存在 
		if(dp[w][now][jw]!=-1)return dp[w][now][jw];
		//cout<<w<<' '<<now<<' '<<jw<<endl;
		dp[w][now][jw]=inf;
		//方程转移 
		if(!jw)dp[w][now][jw]=dfs(w-1,now,0);
		if(!jw&&A[w]<'9')dp[w][now][jw]=min(dp[w][now][jw],dfs(w-1,now,1));
		if(jw)dp[w][now][jw]=min(dp[w][now][jw],dfs(w-1,now-1,1)+(9-A[w]+'0')*ksm(w-1));
		if(jw&&A[w]>'0')dp[w][now][jw]=min(dp[w][now][jw],dfs(w-1,now-1,0)+(10-A[w]+'0')*ksm(w-1));
//		if(w==9)write(dp[w][now][jw]),cout<<' '<<w<<' '<<now<<' '<<jw<<endl;
		return dp[w][now][jw];
	}
	 
	

	int main()
	{
		int t;
		scanf("%lld",&t);
		while(t--)
		{
			scanf("%s%lld",B+1,&k);
			len=strlen(B+1);
			memset(dp,-1,sizeof(dp));
			for(int i=1;i<=40;i++)//注意初始化！ 
			{
				A[i]='0';
				
			}
			for(int i=1;i<=len;i++)
			{
				A[i]=B[len-i+1];
			}
			if(k>0)write(dfs(38,k,0));//最多36位,但求稳 
			else//特判k=0 
			{
				long long ans=1;
				for(int i=1;i<=len+1;i++)
				{
					if(A[i]<'9')
					{
						cout<<ans;
						break;
					}
					ans*=10; 
				}
			}
			cout<<'\n';
			
		}
		return 0;
	}
}
#undef int
int main()
{
	acac::main();
	return 0;
}
```

---

## 作者：under_the_time (赞：0)

## 题意

> 给定一个数 $x$，求出最小的 $y$，使得在十进制下 $x$ 与 $y$ 相加的过程中恰好进位 $k$​ 次。
>
> $1\le x\le 10^{18}$。

## 解法

如此巨大的数据范围提示我们使用数位 dp。因为进位操作是从低位到高位发生的，所以我们考虑从最低位开始 dp，显然没有上界的限制。令 $f(u,v,0/1)$ 表示：已经从低到高扫了 $u$ 位、其中发生了 $v$ 次进位、当前位是否需要向前进 $1$ 的情况下，所需要的最小的 $y$。初始值其余为 $+\infty$，$f(0,0,0)=0$。转移时枚举 $u$ 和 $v$，转移方程如下：

- 对于不进位的情况（即该位加完后小于 $10$），如果上一位没有进位，显然将 $y$ 的这一位设为 $0$ 是最优的，即

$$
f(u,v,0)\gets\min\big(f(u,v,0),f(u-1,v,0)\big)
$$

- 令 $x$ 的第 $i$ 位为 $X(i)$，如果 $X(u)<9$，那么就可以容纳一次进位，然后将 $y$ 当前位设为 $0$。即

$$
f(u,v,0)\gets\min\big(f(u,v,0),f(u-1,v,1)\big)~~~~~~\big(X(u)<9\big)
$$

- 而对于进位的情况（即该位加完后大于等于 $10$，最优的方案显然是正好等于 $10$），如果上一位进位了，那么 $y$ 的这一位应该设为 $9-X(u)$，即

$$
f(u,v,1)\gets\min\big(f(u,v,1),f(u-1,v-1,1)+(9-X(u))\times10^{u-1}\big)
$$

- 其中 $\times10^{u-1}$ 是为了与当前位对齐。类似的，如果 $X(u)>0$，那么该位就可以设置为 $10-X(u)$，即

$$
f(u,v,1)\gets\min\big(f(u-1,v-1,0)+(10-X(u))\times10^{u-1}\big)~~~~~~(X(u)>0)
$$

注意最终需要的位数是无法确定的，所以 $u$ 要尽可能往大了枚举。最终答案即为 $f(u_{\max},k,0)$。

## 实现

实现的细节还是很多的。读入 $x$ 的时候可以用类似快读的方法直接读成数组形式。但是如果遇到 $k=0$ 即不发生任何进位的情况，而 $y$ 又要求是正整数，此时进行特判：我们从低位到高位找，找到 $x$ 中第一个不为 $9$ 的位置，然后把 $x$ 的这个位置设为 $1$，其余都设为 $0$ 即为答案。

如果遇到 $x$ 低位处有特别多的 $0$，这些 $0$ 显然无法产生进位的贡献，而如果直接记录就会爆 `long long`。所以我们就先把这些低位的 $0$ 全部取出，等到输出答案时再进行处理。$u_{max}$ 取到 $19$ 就行，遇到 $x$ 高位不够的地方就在高位添 $0$，这样就可以涵盖所有情况。

由于是多组数据，一定要做好初始化。单组数据时间复杂度为 $O(\log_{10}n\times k)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 20;
#define ll long long
const ll inf = 1e18;
int T; int X[maxn],k;
void read(int *A) {
    char c; memset(A,0,sizeof(A)); 
    for (c = getchar();c < '0' || c > '9';c = getchar());
    for (;c >= '0' && c <= '9';c = getchar())
        A[++ A[0]] = c - '0'; // 这里我把位数存在 A[0] 处
}
ll f[maxn][maxn][2], w; string pre;
int main() {
    cin >> T;
    while (T --) {
        read(X); cin >> k;
        if (k == 0) { // 特判
            ll ans = 1;
            for (;X[0] && X[X[0]] == 9;X[0] --,ans *= 10);
            cout << ans << '\n'; continue;
        }
        pre = "\n"; // 取出低位的 0
        for (;X[0] && X[X[0]] == 0;pre = '0' + pre,X[X[0] --] = 0);
        reverse(X + 1,X + X[0] + 1); // 从低位开始处理
        for (int i = 0;i < maxn;i ++)
            for (int j = 0;j < maxn;j ++)
                f[i][j][0] = f[i][j][1] = inf;
        f[0][0][0] = 0, w = 1; // 没有填数，没有进位
        for (int i = 1;i < maxn;i ++, w *= (i < maxn) * 10ll) 
            for (int j = 0;j <= k;j ++) {
                f[i][j][0] = min(f[i][j][0],min(
                    f[i - 1][j][0],
                    (X[i] < 9 ? f[i - 1][j][1] : inf)
                ));
                if (j > 0) {
                    f[i][j][1] = min(f[i][j][1],min(
                        f[i - 1][j - 1][1] + w * (9ll - X[i]),
                        (X[i] > 0 ? f[i - 1][j - 1][0] + w * (10ll - X[i]) : inf)
                    ));
                }
            }
        cout << f[maxn - 1][k][0] << pre;
    }
    return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：0)

此篇题解收录于 [EC Final 2022 笔记](https://www.luogu.com.cn/blog/hokarikanae/ec-final-2022-bi-ji)。

经典按位贪心 + 卡常 + 分类讨论烂题。

首先判 $k=0$。选取最小的 $x$ 的非 $9$ 位，在那位 $+1$ 即可。这样做的好处是之后不需要再特别考虑 $y\neq 0$ 了。

接下来假设 $k>0$。注意到 $x$ 末尾 $0$ 是没用的，不可能提供进位，$y$ 必然在这位选 $0$，直接去掉最后再输出一车 $0$ 即可。

然后发现解总是存在且不会超过 long long。按位贪心考虑取什么值，即枚举 $x\times 10^y$ 的 $x$，具体来说考虑 $10^{y-1}$ 是否向 $10^y$ 进位，求出 $10^y$ 前面的进位（暴力算），对于 $10^{y-1}$ 及之后的，若强制 $10^{y-1}$ 是否向 $10^y$ 进位，则紧靠 $10^{y-1}$ 之后的 $0$ 都必须进位，其他无所谓；若强制 $10^{y-1}$ 是否不向 $10^y$ 进位，则紧靠 $10^{y-1}$ 之后的 $9$ 都必须不进位，其他无所谓。那么求出在选上 $x$ 的时候可能得到的答案集合，包含 $k$ 就贪心地选，否则考虑 $x+1$。

时间复杂度 $\Theta(T\log^2 Vw),w=10$，卡卡常数可以过。

[for reference only.](https://www.luogu.com.cn/paste/vmlbh7gf)

---


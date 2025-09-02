# Keyboard Purchase

## 题目描述

You have a password which you often type — a string $ s $ of length $ n $ . Every character of this string is one of the first $ m $ lowercase Latin letters.

Since you spend a lot of time typing it, you want to buy a new keyboard.

A keyboard is a permutation of the first $ m $ Latin letters. For example, if $ m = 3 $ , then there are six possible keyboards: abc, acb, bac, bca, cab and cba.

Since you type your password with one finger, you need to spend time moving your finger from one password character to the next. The time to move from character $ s_i $ to character $ s_{i+1} $ is equal to the distance between these characters on keyboard. The total time you have to spend typing the password with a keyboard is called the slowness of this keyboard.

More formaly, the slowness of keyboard is equal to $ \sum\limits_{i=2}^{n} |pos_{s_{i-1}} - pos_{s_i} | $ , where $ pos_x $ is position of letter $ x $ in keyboard.

For example, if $ s $ is aacabc and the keyboard is bac, then the total time of typing this password is $ |pos_a - pos_a| + |pos_a - pos_c| + |pos_c - pos_a| + |pos_a - pos_b| + |pos_b - pos_c| $ = $ |2 - 2| + |2 - 3| + |3 - 2| + |2 - 1| + |1 - 3| $ = $ 0 + 1 + 1 + 1 + 2 = 5 $ .

Before buying a new keyboard you want to know the minimum possible slowness that the keyboard can have.

## 说明/提示

The first test case is considered in the statement.

In the second test case the slowness of any keyboard is $ 0 $ .

In the third test case one of the most suitable keyboards is bacd.

## 样例 #1

### 输入

```
6 3
aacabc
```

### 输出

```
5
```

## 样例 #2

### 输入

```
6 4
aaaaaa
```

### 输出

```
0
```

## 样例 #3

### 输入

```
15 4
abacabadabacaba
```

### 输出

```
16
```

# 题解

## 作者：tanao (赞：14)

先将相邻元素的$pair$存下来，保存为$cnt$

$cnt$数组构建代码：
```cpp
for(int i=1;i<n;++i)
	cnt[s[i]-'a'][s[i+1]-'a']++,
	cnt[s[i+1]-'a'][s[i]-'a']++;
for(int i=0;i<m;++i)
   cnt[i][i]=0;
```


考虑$dp$，$dp[s]$表示当前状态为$s$，$keyboard$前($s$中$1$的个数)的元素为$s$中的元素的最小代价

举个栗子，假设$s=011010(f,e,d,c,b,a)$，对应集合$\{b,d,e\}$,那么我们可以知道最终排列的前$3$个元素是$b,d,e$，但是排列顺序未知

初始化：$dp[0]=0,dp[i]=inf\;(i>1)$

转移：假设要加入$i$元素

$one=s$中$1$的个数

$sum=(\Sigma_{element\;j\;belongs\;to\;s}cnt[i][j]-\Sigma_{element\;j\;not\;belongs\;to\;s}cnt[i][j])*one$

$dp[s|(1<<i)]=\min\{dp[s]+sum\}$


$sum$表示加入$i$元素的代价，元素在最终字母表中的位置就是它们的加入顺序


考虑两个元素$i,j$(假设$i$在右$j$在左)产生的$cost=cnt[i][j]*(pos_i-pos_j)$,拆开此式得到$cost=cnt[i][j]*pos_i-cnt[j][i]*pos_j$,发现前一项与$i$明显相关，后一项与$j$明显相关，于是可以分开维护，每次$dp$时只用将自己产生的$cost$加入$dp[i]$，不用管其他元素的$cost$

于是分类讨论一下，假设现在加入元素$i$
（参考上式：$cost=cnt[i][j]*pos_i-cnt[j][i]*pos_j$）

$1.$对于已经加入的元素$j$，$pos_j\le pos_i$,$i$在右边，那么$sum+=cnt[i][j]*pos_i$

$2.$对于还未加入的元素$j$，$pos_j\ge pos_i$,$i$在左边，那么$sum-=cnt[i][j]*pos_i$

$sum$计算的代码如下
```cpp
int sum=0;
for(int j=0;j<m;++j)
	if((1<<j)&s)sum+=cnt[i][j]*one;
	else sum-=cnt[j][i]*one;
```

$dp$转移的代码如下：
```cpp
memset(dp,0x3f,sizeof dp);
dp[0]=0;
for(int s=0;s<(1<<m);++s)
{
	int one=0;
	for(int i=0;i<m;++i)if((1<<i)&s)++one;
	for(int i=0;i<m;++i)if(((1<<i)&s)==0)
	{
		int sum=0;
		for(int j=0;j<m;++j)
			if((1<<j)&s)sum+=cnt[i][j]*one;
			else sum-=cnt[j][i]*one;
		dp[s|(1<<i)]=min(dp[s|(1<<i)],dp[s]+sum);
	}
}
```


完整代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAX_N 1100000
using namespace std;
int n,m,dp[MAX_N],cnt[30][30];
char s[MAX_N];
int main()
{
	cin>>n>>m>>s+1;
	for(int i=1;i<n;++i)
		cnt[s[i]-'a'][s[i+1]-'a']++,cnt[s[i+1]-'a'][s[i]-'a']++;
	for(int i=0;i<m;++i)cnt[i][i]=0;
	memset(dp,0x3f,sizeof dp);
	dp[0]=0;
	for(int s=0;s<(1<<m);++s)
	{
		int one=0;
		for(int i=0;i<m;++i)if((1<<i)&s)++one;
		for(int i=0;i<m;++i)if(((1<<i)&s)==0)
		{
			int sum=0;
			for(int j=0;j<m;++j)
				if((1<<j)&s)sum+=cnt[i][j]*one;
				else sum-=cnt[j][i]*one;
			dp[s|(1<<i)]=min(dp[s|(1<<i)],dp[s]+sum);
		}
	}
	cout<<dp[(1<<m)-1]<<endl;
	return 0;
}
```





















---

## 作者：whiteqwq (赞：10)

[CF1238E Keyboard Purchase](https://www.luogu.com.cn/problem/CF1238E)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1750388)

## 题意
- 给定一个长度为$n$的密码，且其由前$m$个小写字母组成；
- 在输入密码的过程中，你的手指需要在密码相邻的两个字母在键盘上的位置移动，缓慢度为这两个位置的距离；
- 对于一个键盘，输入密码的缓慢度为输入密码的缓慢度之和，请设计一个键盘，让缓慢度最小。
- 数据范围：$1\leqslant n\leqslant 10^5,1\leqslant m\leqslant 20$。

## 分析
状压dp。

看到这么小的$m$，我们就可以大概猜出要压这个$m$，于是套路的设计状态：$f_i$为设计的键盘（不需要设计完）用到的所有字母压缩起来是$i$的最小缓慢度。

但是有一个问题，对于这个状态，我们不能知道它字母的顺序，所以并不能统计答案。

我们要设计一种无后效性的dp：每一次装一个字母就直接统计出来它的所有贡献（费用提前思想）。

考虑装一个字母的贡献：会让所有相邻且一个装了一个没装的字母对距离加一，这样我们就可以快速地统计出来答案了。

设$cnt_{i,j}$为$i,j$相邻的状态数，很容易统计出来，然后就是套路的状压dp了。

## 代码
代码非常简短，记得开$\text{long long}$。
```
for(int i=1;i<n;i++)
	cnt[s[i]-96][s[i+1]-96]++,cnt[s[i+1]-96][s[i]-96]++;
st=(1<<m)-1;
f[0]=0;
for(int i=1;i<=st;i++){
	int sum=0;
	f[i]=inf;
	for(int j=1;j<=m;j++)
		for(int k=j+1;k<=m;k++)//不统计重复
			if(((i>>(j-1))&1)^((i>>(k-1))&1))//j在键盘上或k在键盘上
				sum+=cnt[j][k];
	for(int j=1;j<=m;j++)
		if((i>>(j-1)&1))
			f[i]=min(f[i],f[i^(1<<(j-1))]+sum);
}
printf("%lld\n",f[st]);
```

---

## 作者：Ynoi (赞：6)

这里是模拟退火做法

不保证每次代码提交都正确

我们先处理出来任意两个字母之间需要移动的次数

这样对于任意一种排列就可以$O(m^2)$的时间算出需要移动的距离

然后我们使用模拟退火

模拟退火就不详细说了，一个较高的初温，较高概率接受较差的解，然后不断降低温度，较低概率接受较差的解。

```
#include<bits/stdc++.h>
using namespace std;
 
#define MAXN 100005
#define MAXM 22
#define db double 
 
char s[MAXN];
int n,m;
int a[MAXM][MAXM];
int f[1<<20];
int c[MAXN];
 
void rd()
{
	cin >> n >> m;;
	scanf("%s",s+1);
	for(int i = 1; i < n; i ++) 
		a[s[i]-'a'+1][s[i+1]-'a'+1] ++;
}
 
db sj() {
	return ((db)(rand()*rand()%19260817))/(db)19260817;
}
 
int an = 0x3f3f3f3f;
 
int get()
{
	int ans = 0;
	for(int i = 1; i <= m; i ++)
		for(int j = 1; j <= m; j ++)
			ans += abs(c[i]-c[j])*a[i][j];
	if(ans < an) an = ans;
	return ans;
}
 
db mnth(db t,db dt,db tt)
{
	int an = 0;
	for(;t >= tt; t = t*dt)
	{
		int x = rand()%m+1,y = rand()%m+1;
		int ls = get();	
		swap(c[x],c[y]);
		int ans = get();
		if(ans < ls || exp((db)(ans - ls)/t) < sj()*10)
			;
		else
			swap(c[x],c[y]); 		 
	}
	for(int i = 1; i <= 2333; i ++)
	{
		int x = rand()%m+1,y = rand()%m+1;
		int ls = get();	
		swap(c[x],c[y]);
		int ans = get();
		if(ans < ls)
			;
		else
			swap(c[x],c[y]); 
	} 
} 
 
 
signed main()
{
	srand(time(0));
	rd();
	for(int i = 1; i <= m; i ++)
		c[i] = i;
	mnth(100000000,0.9997,0.000001);
	cout<<an;
	return 0;
}
```

这是我比赛时写的代码，然后竟然神奇的过了pretest

后来我自己去hack了自己=-=

随机一组极限数据就叉掉了。。。

所以说，还是要调调参的

过了pretest之后我怕fst去调参，增大delta，多次退火的方式但是都`WA on test 4` 可见第一次提交的时候rp有多好=-=

这是我现在的代码，极限随机数据本地大概对拍20几组才会挂=-=

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 100005
#define MAXM 22
#define db double 

char s[MAXN];
int n,m;
int a[MAXM][MAXM];
int f[1<<20];
int c[MAXN];

void rd()
{
	cin >> n >> m;;
	scanf("%s",s+1);
	for(int i = 1; i < n; i ++) 
		a[s[i]-'a'+1][s[i+1]-'a'+1] ++;
}

db sj() {
	return ((db)(rand()*rand()%19260817))/(db)19260817;
}

int an = 0x3f3f3f3f;

int get()
{
	int ans = 0;
	for(int i = 1; i <= m; i ++)
		for(int j = 1; j <= m; j ++)
			ans += abs(c[i]-c[j])*a[i][j];
	if(ans < an) an = ans;
	return ans;
}

void mnth(db t,db dt,db tt)
{
	int an = 0;
	for(;t >= tt; t = t*dt)
	{
		int x = rand()%m+1,y = rand()%m+1;
		int ls = get();	
		swap(c[x],c[y]);
		int ans = get();
		if(ans < ls || exp((db)(ans - ls)/t) < sj()*10)
			;
		else
			swap(c[x],c[y]); 		 
	}
	for(int i = 1; i <= 23333; i ++)
	{
		int x = rand()%m+1,y = rand()%m+1;
		int ls = get();	
		swap(c[x],c[y]);
		int ans = get();
		if(ans < ls)
			;
		else
			swap(c[x],c[y]); 
	} 
} 

signed main()
{
	srand(time(0));
	rd();
	for(int i = 1; i <= m; i ++)
		c[i] = i;
	mnth(10000,0.9997,0.0000001);
	mnth(10000,0.9997,0.0000001);
	mnth(100000,0.9997,0.0000001);
	mnth(100000,0.9998,0.0000001);
	mnth(100000,0.9998,0.0000001);
	mnth(100000,0.9999,0.0000001);
	
	cout<<an;	
	return 0;
}

```


---

## 作者：Sol1 (赞：3)

首先看到这个 $m=20$ 就肯定能想到是状压 DP。

那么我们就先定义一个二进制状态 $s$，其中第 $0$ 位是 $1$ 表示 $\texttt{a}$ 已经存在在键盘上，$0$ 表示不存在；类似的，第 $1$ 位表示 $\texttt b$，第 $2$ 位表示 $\texttt c$，依次类推。

然后来思考如何转移。

首先转移显然是从一个状态 $s$，将一个 $0$ 位变成 $1$，表示在目前的键盘上“push_back”了一个字符。

下面定义 $c_{x,y}$ 为有多少个位置是字符 $x$ 与字符 $y$ 相邻，$p_x$ 为字符 $x$ 在键盘上面的位置。

然后对于任意一个字符 $y$，设它的位置在 $p_y$，如果它在键盘上，产生的 _slowness_ 为 $c_{x,y}\cdot(p_x-p_y)$，否则其 _slowness_ 为 $c_{x,y}\cdot(p_y-p_x)$。

但是一个很严重的问题是我们不知道 $p_y$ 是几。

所以从贡献考虑，一个字符 $x$ 对它之前的字符的贡献是 $c_{x,y}p_x$，对它后面的字符的贡献是 $-c_{x,y}p_x$。

这样我们就提前计算出对于一个状态 $s$ 和所有的字符 $x$，它的 $\sum c_{x,y}$ 的值是多少，每次转移的时候直接用这个值来转移即可。这个值可以使用另外一个状压 DP 来做。

这样这道题就做完了，时间复杂度 $O(n+2^m\cdot m)$。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

string s;
int cnt[25][25], n, m, dp[1050005], delt[1050005][25];

inline int Count(int v) {
	register int ans = 0;
	while (v) {
		ans += (v & 1);
		v >>= 1;
	}
	return ans;
}

inline void Read() {
	n = qread(); m = qread();
	for (register int i = 1;i <= n;i++) {
		register char c = getchar();
		while (c < 'a' || c > 'z') c = getchar();
		s += c;
	}
}

inline void Prefix() {
	for (register int i = 0;i < n - 1;i++) {
		cnt[s[i + 1] - 'a'][s[i] - 'a']++;
		cnt[s[i] - 'a'][s[i + 1] - 'a']++;
	}
}

inline void Solve() {
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	for (register int i = 1;i < (1 << m);i++) {
		for (register int j = 0;j < m;j++) {
			delt[i][j] = delt[i ^ (i & -i)][j] + cnt[(int)log2(i & -i)][j];
		}
	}
	for (register int i = 0;i < (1 << m);i++) {
		register int pos = Count(i) + 1;
		for (register int j = 0;j < m;j++) {
			if (!(i >> j & 1)) {
				register int nxt = i | (1 << j);
				dp[nxt] = Min(dp[nxt], dp[i] + pos * (delt[i][j] - delt[((1 << m) - 1) ^ nxt][j]));
			}
		}
	}
	printf("%d", dp[(1 << m) - 1]);
}

int main() {
	Read();
	Prefix();
	Solve();
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}
```

---

## 作者：Kelin (赞：3)

## [题意](https://blog.csdn.net/BeNoble_/article/details/102480123)
一个只包含前$m$个字母的长度为$n$的字符串$s$

对于一个包含前$m$个字母的排列，设$pos_c$表示字母$c$在排列中的位置

求一个排列使得$\sum_{i=2}^n|pos_{s[i]}-pos_{s[i-1]}|$最小，输出最小值即可

---

## 题解
设$cnt_{x,y}$表示字母$x,y$有多少次相邻（特别的$cnt_{x,x}=0$）

那么就是最小化$\sum_{i=1}^m\sum_{j=1}^{i-1}cnt_{i,j}|pos_i-pos_j|$

注意到$m$只有$20$，可以考虑状压，设全集为$T$

对于一个集合$s$，假设新加入一个字母$x$，我们就把$x$放在排列的$|s|$位（由于是绝对值的差，全员的位置都$-1$不影响结果）

可以证明这样做是能取到所有最优情况的，因为扩展到集合$s$时，$s$中每个字母放在最后的情况都会被算到

那么把$x$加入集合的代价为$\sum_{y\in s}cnt_{y,x}(|s|-pos_y)$

$($**注意**此时是无法暴力存下位置然后枚举转移的，因为可能会有很多**总代价相同**的排列，时间复杂度可以达到$O(m^32^m+n)$ $)$

设$sum_{s,x}=\sum_{y\in s}cnt_{y,x}$，这个是可以预处理出来的

主要考虑后面减去的$pos_y$如何转化

而由于我们无法存下位置，所以只能在$x$上面想如何处理

假设再新加入一个字母$z$，则其代价中与$x$有关的就只有$-cnt_{z,x}pos_x$这一项

而此时$pos_x=|s|$，其中$z\in T-s$

所以对于所有的$z$，$x$的贡献和就为$-|s|\times sum_{T-s,x}$

所以$\sum_{y\in s}cnt_{x,y}(|s|+1-pos_y)$就可以等价转化为$|s|\times(sum_{s,x}-sum_{T-s,x})$

于是设$f_s$表示集合$s$的等价代价的最小和，那么

$$f_{s|x}=\min_{x\notin s}f_{s}+|s|\times(sum_{s,x}-sum_{T-s,x})$$

时间复杂度$O(m2^m+n)$

```cpp
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
const int N=1e5+5,M=25,S=(1<<21)+5;
typedef long long ll;
int n,m,T,Mi[M],cnt[M][M];
int f[S],Log[S],cntBit[S],sumC[S][M];
char s[N];
int main(){
	#ifndef ONLINE_JUDGE
		file("s");
	#endif
	scanf("%d %d\n",&n,&m);
	gets(s+1);T=(1<<m)-1;
	fp(i,2,n)
		++cnt[s[i]-'a'][s[i-1]-'a'],
		++cnt[s[i-1]-'a'][s[i]-'a'];
	fp(i,0,m)cnt[i][i]=0;
	Mi[0]=1;Log[0]=-1;
	fp(i,1,m-1)Mi[i]=Mi[i-1]<<1;
	fp(s,1,T){
		Log[s]=Log[s>>1]+1;
		cntBit[s]=cntBit[s>>1]+(s&1);
		int y=Log[s&(-s)];
		fp(x,0,m-1)sumC[s][x]=sumC[s^Mi[y]][x]+cnt[x][y];
	}
	memset(f,127,sizeof f);f[0]=0;
	fp(s,0,T)fp(i,0,m-1)if(!(s&Mi[i]))
		cmin(f[s|Mi[i]],f[s]+cntBit[s]*(sumC[s][i]-sumC[T^s][i]));
	printf("%d\n",f[T]);
return 0;
}
```

---

## 作者：lahlah (赞：2)

[CF1238E Keyboard Purchase](https://www.luogu.org/problem/CF1238E)

# 题目大意
给定$n$和$m$,表示给出一个长度为$n$的小写字母串，其中的每个字母的大小不会超过第$m$个小写字母

前$m$个小写字母：$a, b, c, ...$($m$个)


然后可以改变前$m$个小写字母的相对位置，有$m!$种可能，每一种可能的值是给出的字符串的每两个相邻位置的字母的相对位置的和

求这个最小值是多少

# 题解
一开始一直以为要把相对位置表示出来才行，然后发现自己naive了


考虑状压dp，$f[S]$表示被选入的字母集合为$S$

考虑如何转移

$|pos_{i} - pos_{i+1}|$ 即两个相对位置的差可以看做$st[i]$ 和 $st[i+1]$这两个字母被选入集合的时间差

然后每次转移的贡献就是集合内的字母和集合外的字母相邻的对数


然后DP即可

code:
```cpp

#include<bits/stdc++.h>
using namespace std;
int n, m, mp[25][25], f[1 << 22], g[1 << 22];
char st[100005];
int main() {
	scanf("%d%d", &n, &m);
	scanf("%s", st + 1);
	for(int i = 2; i <= n; i ++) {
		mp[st[i] - 'a'][st[i - 1] - 'a'] ++;
		mp[st[i - 1] - 'a'][st[i] - 'a'] ++;//预处理两个字母相邻的对数
	}
	for(int S = 0; S < (1 << m); S ++) 
		for(int i = 0; i < m; i ++)
			if((1 << i) & S)
				for(int j = 0; j < m; j ++)
					if(!((1 << j) & S))
						g[S] += mp[i][j];//算S集合内的字母与集合外的字母相邻的对数
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for(int S = 0; S < (1 << m); S ++)	
		for(int i = 0; i < m; i ++)//把i选入集合
			if(S & (1 << i)) f[S] = min(f[S], f[S ^ (1 << i)] + g[S ^ (1 << i)]);//转移
	printf("%d", f[(1 << m) - 1]);//输出即可
	return 0;
}
```

妙啊！！


---

## 作者：Mier_Samuelle (赞：1)

### 题意

给定一个长度为 $n$ 的字符串 $s$，由字母表中的前 $m$ 个小写字母构成。

对于任意一个 $m$ 个小写字母的排列，记字母 $x$ 在排列的位置为 $p_x$，则该排列的缓慢度为 $\sum\limits_{i=2}^n |p_{s_i}-p_{s_{i-1}}|$。

求所有排列的缓慢度的最小值。

**数据范围**：$1 \le n \le 10^5$，$1 \le m \le 20$。

### 解法

显然是一个状态压缩题。

注意到 $m \le 20$，很小，可以从它入手设计状态。那么我们定义状态如下：

- $dp_S$ 为包含集合 $S$ 中字母的排列的最小缓慢度。
- 例如 $dp_{\texttt{11001}}$ 为包含 $\texttt{a,d,e}$ 的排列的最小缓慢度。

接下来我们考虑如何转移。

以下记 $c_{x,y}$ 为相邻的字母 $x,y$ 的对数，$p_x$ 为字母 $x$ 在排列中的位置。

转移时我们将 $S$ 的某一位由 $0$ 变为 $1$，表示在排列的末尾添加了一个字母，我们记这个添加的字母为 $x$。

对于任意一个字母 $y$，$x$ 与 $y$ 对缓慢度的贡献为 $c_{x,y} \cdot |p_x-p_y|$，即：

- 如果 $x$ 在 $y$ 的右侧（此时 $y$ 已在排列中），那么它们对缓慢度的贡献为 $c_{x,y} \cdot (p_x-p_y)$，其中 $x$ 单独的贡献为 $c_{x,y} \cdot p_x$。
- 如果 $x$ 在 $y$ 的左侧（此时 $y$ 不在排列中），那么它们对缓慢度的贡献为 $c_{x,y} \cdot (p_y-p_x)$，其中 $x$ 单独的贡献为 $-c_{x,y} \cdot p_x$。

因此，转移时我们可以依次计算 $x$ 与每个可能的 $y$ 的贡献中 $x$ 单独的贡献，并将这些值累加得到 $V$。状态转移方程：

$$dp_{S'}=\min\lbrace dp_S+V\rbrace$$

其中 $S'$ 为新的集合 $S$。初始时 $dp_0=0$，其它 $dp$ 为正无穷。

空间复杂度 $O(m^2+2^m)$，时间复杂度 $O(2^m \cdot m^2)$。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e5 + 10, MAXM = 30, MAXS = 1 << 20;
int cnt[MAXM][MAXM], dp[MAXS];
signed main(){
	memset(dp, 0x3f, sizeof(dp));
	string s;
	int n, m;
	cin >> n >> m >> s;
	s = " " + s;
	for (int i = 1;i <= n - 1;i++) cnt[s[i] - 'a'][s[i + 1] - 'a']++, cnt[s[i + 1] - 'a'][s[i] - 'a']++;
	for (int i = 0;i <= m - 1;i++) cnt[i][i] = 0;
	dp[0] = 0;
	for (int st = 0;st <= (1 << m) - 1;st++){
		int k = __builtin_popcount(st); //集合 S 中 1 的数量
		for (int i = 0;i <= m - 1;i++){
			if (!((st >> i) & 1)) continue;
			int val = 0; //计算贡献
			for (int j = 0;j <= m - 1;j++){
				if (i != j && ((st >> j) & 1)) val += cnt[i][j] * k;
				else val -= cnt[i][j] * k;
			}
			dp[st] = min(dp[st], dp[st - (1 << i)] + val);
		}
	}
	cout << dp[(1 << m) - 1] << endl;
	return 0;
}
```

[CF 通过记录](https://codeforces.com/contest/1238/submission/305434056)

### 闲话

其实还有 $O(2^m \cdot m)$ 的做法。

可以在转移前将贡献预处理出来，这样转移的时候可以省去计算贡献的 $O(m)$ 的复杂度。

对于这道题来说 $O(2^m \cdot m^2)$ 已经足够。如果你对更优的做法感兴趣，~~可以去看其它题解~~。

---

## 作者：wrzSama (赞：1)

## 题意

给定一个长度为 $n$ 的字符串 $s$，其字符均为前 $m$ 个字母。请构造一种这 $m$ 个字母的排列，则打印这个字符串的代价为 $\sum_{i=1}^{n-1} \lvert pos_{s_i}-pos_{s_{i-1}} \rvert$，$pos_x$ 表示字母 $x$ 在排列中的位置。请输出打印字符串 $s$ 的最小代价。

## 思路

我们考虑对每一种字母是否已经放在排列中进行状态压缩，$dp_i$ 表示排列状态为 $i$ 时的最小代价，若 $i \& 2^{j-1} \neq 0$ 则说明字母 $j$ 已经放在了排列中。

然后，我们考虑转移，每次将一个没出现过的字母加在排列的末尾。因为我们不知道每一个状态中字母的具体顺序，所以我们必须在转移即加入一个字母的时候提前计算这个字母与后面加入排列的字母的不需要的代价。

具体地，若加入了字母 $j$，对于所有的不在排列中字母 $k$ ，应该令当前的 $dp_i$ 减去 $t_{i \oplus 2^{j-1}} \times c_{j,k}$，其中 $t_x$ 表示 $x$ 的 $2$ 进制表示有多少个 $1$ 即此时排列的长度，$c_{x,y}$ 表示在字符串 $s$ 中字母 $x$ 和字母 $y$ 相邻的次数。这是因为到这里我们可以确定在前 $t_i$ 个字母中有 $t_{\oplus 2^{j-1}}$ 个字母不会夹在字母 $j$ 和字母 $k$ 之间。

同时在加入一个字母时，我们要计算它与之前已经加入排列的字母的代价，即对于所有的已经在排列中的字母 $k$，令当前的 $dp_i$ 加上 $t_{\oplus 2^{j-1}} \times c_{j,k}$。这是因为此时不看字母 $j$ 和字母 $k$ 后面的字母还剩下 $t_{\oplus 2^{j-1}}$ 个字母对它们在排列中的距离有影响。

这样通过 $1$ 加 $1$ 减，我们刚好计算出了字母 $j$ 和字母 $k$ 的距离对答案的贡献。最后，我们输出所有字母都加进排列时的最小代价，即 $dp_{2^m-1}$ 就行了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int read_result=0,is_below_0=0;
	char now_ch=0;
	while(!isdigit(now_ch))
	{
		is_below_0|=now_ch=='-';
		now_ch=getchar();
	}
	while(isdigit(now_ch))
	{
		read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);
		now_ch=getchar();
	}
	return is_below_0?-read_result:read_result;
}
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
inline int lowbit(int x)
{
	return x&(-x);
}
int n,m,c[25][25],t[2000005],dp[2000005];
string s;
int main()
{
	n=read();
	m=read();
	cin>>s; 
	for(int i=1;i<n;++i)
	{
		if(s[i]==s[i-1]) continue;
		++c[s[i]-'a'][s[i-1]-'a'];
		++c[s[i-1]-'a'][s[i]-'a'];
	}
	for(int i=1;i<(1<<m);++i)
	{
		dp[i]=1e9;
		t[i]=t[i^lowbit(i)]+1;
	}
	for(int i=0;i<(1<<m);++i)
	{
		for(int j=0;j<m;++j)
		{
			if(!((1<<j)&i)) continue;
			int sum=0;
			for(int k=0;k<m;++k)
			{
				if((1<<k)&(i^(1<<j))) sum+=c[j][k]*t[i^(1<<j)];
				else sum-=c[j][k]*t[i^(1<<j)];
			}
			dp[i]=min(dp[i],dp[i^(1<<j)]+sum);
		}
	}
	write(dp[(1<<m)-1]);
	return 0;
}
```


---

## 作者：xixiup (赞：1)

## 先分析一波

我们可以发现，这道题的 $m \leqslant 20$，众所周知，英文中有 $26$ 个字母，但是这里只使用了前 $20$ 个，所以肯定有鬼。

## 分享思路

由于 $m \leqslant 20$，我们可以考虑状压 $DP$。

设 $dp_i$ 为状态为 $i$ 时的答案，$pd_{i,j}$ 为键 $i$ 与键 $j$ 相邻的个数。

举个栗子：对于 $m=5$ 的情况，$dp_{10}$ 的含义：$10=\left( 01010 \right)_2$，故 $dp_{10}$ 表示在集合 $\left[ e,d,c,b,a \right]$ 中将字母 $b$ 和 $d$ 摆在前 $2$ 个时的最优答案。

但是若两个键不相邻，我们如何处理答案呢？

考虑计算距离的公式（先假设 $pos_i>pos_j$）：
$$
\boxed{\left| pos_i-pos_j \right| \times ma_{i,j}}
$$
拆开得到：
$$
\boxed{pos_i \times ma_{i,j}-pos_j \times ma_{i,j}}
$$
又由于我们的 $ma_{i,j}$ 是预处理得到的，故我们可以将两部分分开处理。

于是就可以得到如下式子：
$$
\boxed{dp_i=\max(dp_i,dp_j+\sum\limits _{k=0}^{m-1}ma_{i,j}\left.\right|((i>>k)\&1=1) \times cnt-\sum\limits _{k=0}^{m-1}ma_{i,j}\left.\right|((i>>k)\&1=0)\times cnt}
$$
其中 $cnt = \sum\limits_{k=0}^{m-1}((i>>k)\&1)$，$j$ 为 $i$ 在任意一个为 $1$ 的二进制位上改为 $0$ 得到。

然后就可以很愉快地 $DP$ 了。

## 代码展示

（代码里所有数组含义与前文或体面一致）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxm=22;
int n,m,pd[maxm][maxm],dp[1<<maxm];
string s;
int main(){
	cin>>n>>m>>s;
	for(int i=1;i<n;i++){
		pd[s[i]-'a'][s[i-1]-'a']++;
		pd[s[i-1]-'a'][s[i]-'a']++;
	}
	for(int i=0;i<m;i++){
		pd[i][i]=0;
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for(int i=1;i<(1<<m);i++){
		int cnt=0;
		for(int j=0;j<m;j++){
			if(((i>>j)&1)==1){
				cnt++;
			}
		}
		for(int j=0;j<m;j++){
			if(((i>>j)&1)==1){
				int sum=0;
				for(int k=0;k<m;k++){
					if(j!=k&&((i>>k)&1)==1){
						sum+=pd[j][k]*cnt;
					}
					else{
						sum-=pd[j][k]*cnt;
					}
				}
				dp[i]=min(dp[i],dp[i-(1<<j)]+sum);
			}
		}
	}
	cout<<dp[(1<<m)-1];
	return 0;
}
```


---

## 作者：xukuan (赞：1)

**使用算法分析**

一看数据范围$m \leq 20$，就差没把状压贴脸上了

然后Educational Div2的E题是不会出状压搜索的，而且$m \leq 20$的数据范围搜索分分钟就TLE掉，那么考虑状压dp

我们用$Count(i)$表示$i$中$1$的个数

我们用$f_i$表示当前状态为$i$，keyboard中前$Count(s)$的元素均为$s$中的元素的最小代价

**无后效性**

我们用$cnt_{i,j}$表示元素i和元素j相邻的次数，那么转移的时候增加的价值$就变成了i与j之间的相邻次数*(集合的相邻元素之和-集合外的相邻元素之和)$

**状态转移方程**

我们发现加入元素j的时候，$f_{i|(1<<j)}=min \{f_i+sum\}$，其中$sum$表示往集合i中加入j元素的代价，计算公式为$sum=(\sum_{k \in i} cnt_{j,k}-\sum_{k \notin i} cnt_{j,k})*Count(i)$

**循环边界条件**

$i \in [0,2^m)$

$j,k \in [0,m)$

**时间复杂度**

时间复杂度为$(2^m*m^2)$，有卡常，注意不要开long long。

---

## 作者：nofind (赞：1)

题意:https://www.luogu.org/problem/CF1238E

做法来自:https://www.cnblogs.com/LLTYYC/p/11642956.html

看见m这么小,显然状压

设$f[s]$表示键盘上已经放好的字符集为$s$的最小代价

转移就枚举下一个字符是那个

考虑如何计算代价

考虑新加入一个字符,那么对于所有在串中相邻的字符(x,y),如果$x\in s,y\notin s$,那么x和y之间距离会增加1(**代价提前计算的方法**)

设$cnt[i][j]$表示$i$和$j$相邻的点对数,枚举$i\in s,j\notin s$,代价加上$cnt[i][j]$

这样就可以$O(m^22^m)$做了

考虑优化计算代价

设$h[s]$表示满足$i\in s,j\notin s$的相邻点对的$cnt[i][j]$之和,$g[i][s]$表示$i$到$s$中的点$j$的$cnt[i][j]$之和$(i\notin s)$

$g[i][s]=g[i][s\ xor\ lowbit(s)]+cnt[i][lowbit(s)]$

$h[s]=\sum\limits_{i\in s}g[i][all\ xor\ s]$

转移就变为:$f[s|2^i]=min(f[s|2^i],f[s]+h[s])$

code:
```
#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) (x&-x)
const int maxn=1e5+10;
const int maxm=20;
int n,m;
int f[1<<maxm],h[1<<maxm],pos[1<<maxm];
int cnt[maxm][maxm],g[maxm][1<<maxm]; 
char s[maxn];
int main()
{
	scanf("%d%d%s",&n,&m,s+1);
	for(int i=1;i<n;i++)cnt[s[i]-'a'][s[i+1]-'a']++,cnt[s[i+1]-'a'][s[i]-'a']++;
	for(int i=0;i<m;i++)pos[1<<i]=i;
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int i=0;i<m;i++)
		for(int s=1;s<(1<<m);s++)//s:1->all
			if(!(s&(1<<i)))g[i][s]=g[i][s^lowbit(s)]+cnt[i][pos[lowbit(s)]];
	for(int s=0;s<(1<<m);s++)
		for(int i=0;i<m;i++)
			if(s&(1<<i))h[s]+=g[i][((1<<m)-1)^s];
	for(int s=0;s<(1<<m);s++)
		for(int i=0;i<m;i++)
			if(!(s&(1<<i)))f[s|(1<<i)]=min(f[s|(1<<i)],f[s]+h[s]);
	printf("%d",f[(1<<m)-1]);
	return 0;
}
```


---

## 作者：Soulist (赞：1)

非常奇妙的一道状压$dp$

~~想到状压后特别自闭的想了很久.......~~

首先是两个点之间的位移次数可以$O(n)$预处理出来，于是问题主要在于分配位置上

然后就有一个非常骚的搞法了

我们可以将每个点选/不选状压一下，但是这样肯定是不能维护选取的位置的

可以强制让被选入集合的元素的位置偏小，当然这样是对的，但是这样还需要额外维护每个点的位置复杂度仍然$O(m!)$

这样做之后可以将位置看作选入集合的时间，这样一样是对的，于是位置之差就可以转化为时间之差

考虑将两个点之间被选入的时间之差拆开，比如选$a$的时间是$t_a$，选$b$的时间为$t_b$，那么可以将$|t_b-t_a|$拆开变成$1+1...+1$

你会惊人的发现这个东西是可以累加的，于是每次加点实际上是将集合内所有元素与集合外的所有元素的遍历时间之差都$+1$，然后这样$dp$即可

当然要预处理出来每个状态$\rm ($集合$\rm S)$与其外的元素的位移次数总和即可，这个东西的复杂度是$O(m^2*2^m)$，不过跑不满

转移的话就枚举选谁即可，复杂度$O(m*2^m)$

复杂度$O(m^2*2^m+n)$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 1e5 + 5 ; 
const int M = 21 ; 
int n, m, f[1 << M], dp[1 << M], cnt[M][M] ;
char s[N] ;
int G( char x ) {
	return x - 'a' ;
}
signed main()
{
	n = gi(), m = gi() ;  
	scanf("%s", s + 1 ) ;
	rep( i, 1, n - 1 ) ++ cnt[G(s[i])][G(s[i + 1])], ++ cnt[G(s[i + 1])][G(s[i])] ;
	int maxn = ( 1 << m ) - 1, t = m - 1 ; 
	rep( i, 1, maxn ) {
		rep( j, 0, t ) {
			if( ( ( 1 << j ) & i ) ) 
			rep( k, 0, t ) {
				if( !( ( 1 << k ) & i ) )
				f[i] += cnt[j][k] ; 
			}
		}
	}
	memset( dp, 63, sizeof(dp) ), dp[0] = 0 ;
	rep( i, 1, maxn ) {
		rep( j, 0, t ) {
			if( ( 1 << j ) & i )
			dp[i] = min( dp[i ^ ( 1 << j )] + f[i], dp[i] ) ;
		}
	}
	printf("%d\n", dp[maxn] ) ;
	return 0 ;
}

```


---

## 作者：Priestess_SLG (赞：0)

很典的。理论上这东西可以模拟退火，但是 CF 就算了（设 $f_i$ 表示使用了 $i$ 集合内所有字母，最少需要花费多少时间，但是不太好直接转移。

于是考虑转化。若第 $i$ 个被插入的和第 $j$ 个被插入的字符相邻，则贡献 $|j-i|$ 可以被理解为选入集合的时间戳的绝对值。设当前枚举到 $i$ 集合，想要加入 $j$ 元素，则对答案造成的贡献就是所有不在集合内的元素和所有在集合内的元素相邻的元素对数（那个贡献其实就是每一次都 $+1$）。

直接转移时间复杂度明显超标。考虑费用提前计算，再设 $g_i$ 表示 $i$ 集合对答案的贡献，这个东西随便算一算就行了。然后再转移 $f_i$ 数组，时间复杂度为 $O(n+2^mm^2)$，可以通过。[代码](https://codeforces.com/contest/1238/submission/300802169)。

---

## 作者：Mr_Skirt (赞：0)

这道题可以使用随机化算法（如模拟退火，随机爬山），作为如果想不出正解的情况下的替代方案。

之所以随机化搜索可行，因为满足以下条件：
- 暴力搜索解代价过高
- 评估函数时间复杂度代价小
- 搜索状态表示和转移比较容易

我们的目标是最小化
$$
f(s)=\sum\limits_{i=2}^{n} |pos_{s_{i-1}} - pos_{s_i} |
$$

显然我们只需要稍微改动$s$的排列就能对$f(s)$产生较大影响，那么如果我们每一步都交换某两个排列的顺序，得到一个$f(s')$。然后每次都保留使得$f(s')$最小的那个状态，是不是就能得到一个比较优的解？

实际上这个算法就是爬山算法，对于单峰函数来说很容易得出全局最优解。但是对于多数需要求解的函数（比如这个），爬山算法很容易进入一个局部最优解而无法到达全局最优解的情况。

想要解决这个问题也很简单，可以使用模拟退火等算法。这里我要介绍的就是**随机爬山算法**（**Random-restart hill climbing**），它基于爬山算法，只不过会进行多次。每次开始爬山之前都选一个随机状态进行爬山，这样进行下去我们可以得到很多局部最优解。只要次数够多，总有一个会是全局最优解。对于本题来说，我们的状态就是$s$的排列，所以爬山每次我们都`random_shuffle`一下$s$。

这道题的评估函数也很好写，因为能对$f(s)$参与贡献的只有相邻的点，这些点组成的点对最多只有$m^2$个不同的，于是我们可以用`map`给这些点对计数，然后$O(m^2logm)$就可以求出$f(s)$。

总而言之，这道题是一道很好的随机化算法练手题，虽然在cf这样有system test的比赛里面使用随机化有点危险，但是只要你爬山次数够多，随机种子选得好（~~脸不黑~~），基本上是不会错的。


参考代码（随机爬山，只取了算法的关键部分）

```cpp
char text[MAXN];
map<pair<char, char>, int> cnt;
int pos[255];
mt19937 mt(19260817);

// 估价函数
int eval() {
    int v = 0;
    for (auto p : cnt)
        v += p.second * abs(pos[p.first.first] - pos[p.first.second]);
    return v;
}
int hill_climbing() {
    bool swp;
    int ans = eval();
    do {
        swp = false;
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                swap(pos[i], pos[j]);
                int e = eval();
                if (e < ans)
                    swp = true, ans = e;
                else
                    swap(pos[i], pos[j]);
            }
        }
    } while (swp);
    // 如果没有出现新的状态使得f(s)更小，就说明到达了局部最优解
    return ans;
}

void shuffle(int* a, int sz) {
    for (int i = sz - 1; i >= 0; i--) {
        int j = mt() % (i + 1);
        swap(a[i], a[j]);
    }
}
int search() {
    int ans = INF2;
    for (int i = 0; i < 400; i++) {
        shuffle(pos, m);
        ans = min(ans, hill_climbing());
    }
    return ans;
}

int main() {
#ifdef LOCALLL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    scanf("%s", text);
    for (int i = 1; i < n; i++) cnt[{text[i - 1] - 'a', text[i] - 'a'}]++;
    for (int i = 0; i < m; i++) pos[i] = i;
    printf("%d\n", search());
    return 0;
}

```

---

## 作者：linbinwu (赞：0)

**题解：**

记$f[i]$为已经安装的键状态为$i$的情况下，移动距离之和的最小值

记$v[i][j]$为 从键盘上的$i$转移到$j$的次数

如果当次安装$j$键，并且键盘上已经有$k-1$个键已经安上去，那么未安装$m-k$个键 与 已安装$k$个键 之间的距离就多了1

不妨记，$cnt$为 未安装的键 与 已安装的键 经过增加一个键之后 增加的转移距离

那么就有了状态转移方程
$f[i] = \displaystyle\min_{j=1}^m(f[i],f[i⊕(1<<j)]+cnt)$

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 1e5 + 10;

int N, M;
char s[MAX];
int v[25][25], f[1 << 20];

int main() {
    scanf("%d%d%s", &N, &M, s + 1);
    for (int i = 1; i <= N - 1; i++) {
        int x = s[i] - 'a', y = s[i + 1] - 'a';
        v[x][y]++, v[y][x]++;
    }
    memset(f, 0x3f, sz(f));
    f[0] = 0;
    int mx = (1 << M) - 1;
    for (int i = 0; i <= mx; i++) {

        int cnt = 0;//计算当次贡献
        for (int j = 0; j < M; j++)
            for (int k = j + 1; k < M; k++)
                if ((i >> j & 1) ^ (i >> k & 1))//已安装 和 未安装 之间的距离加1
                    cnt += v[j][k];

        for (int j = 0; j < M; j++)
            if (i >> j & 1)//属于该状态
                f[i] = min(f[i], f[i ^ (1 << j)] + cnt);
    }
    cout << f[mx] << endl;

    return 0;
}
```


---


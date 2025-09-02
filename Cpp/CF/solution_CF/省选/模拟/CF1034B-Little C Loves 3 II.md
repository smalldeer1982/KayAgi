# Little C Loves 3 II

## 题目描述

**题目大意：**

给定一个$n\times m$的棋盘，每次可以在上面放一对棋子$(x,y)(x',y')$，要求$\mid x-x'\mid+\mid y-y'\mid==3$，问最多可以放多少**个**棋子

## 样例 #1

### 输入

```
2 2
```

### 输出

```
0```

## 样例 #2

### 输入

```
3 3
```

### 输出

```
8```

# 题解

## 作者：18Michael (赞：11)

## 题意

给定一个 $n\times m$ 的棋盘，每次可以在上面放一对棋子 $(x,y)$，$(x',y')$，要求 $|x-x'|+|y-y'|=3$，问最多可以放多少个棋子。

## 题解

本题中的「一对棋子」本质上只有如下两种摆放方式。

1. $||x-x'|-|y-y'||=3$。

![](https://cdn.luogu.com.cn/upload/image_hosting/crfhwr33.png)

2. $||x-x'|-|y-y'||=1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/5rzpa10f.png)

我们用这两种摆放方式可以凑出如下四种完整的棋盘。

1. $1\times6$

![](https://cdn.luogu.com.cn/upload/image_hosting/vu3a4kol.png)

2. $2\times4$

![](https://cdn.luogu.com.cn/upload/image_hosting/lrmwcz9o.png)

3. $2\times5$

![](https://cdn.luogu.com.cn/upload/image_hosting/dozq7ifp.png)

4. $3\times4$

![](https://cdn.luogu.com.cn/upload/image_hosting/k7ejdtwd.png)

当 $n$，$m$ 足够小时，情况可能会有些特殊，我们先单独考虑这些情况。

### 情况 1 ： $n=1$ 或 $m=1$

不难发现只能使用第 $1$ 种摆法。

每 $6$ 个为一循环节，剩下 $x$ 个格若多于 $3$ 个又可以放 $x-3$ 对。

所以答案为 $\lfloor\dfrac{\max(n,m)}{6}\rfloor\times6+\max(0,\max(n,m)\mod6-3)\times2$。

### 情况 2 ： $n=2$ 或 $m=2$

不妨设 $n=2$。

此时，若 $m=4a+5b+6c$ 有自然数解，则 $2\times m$ 的棋盘可以用 $a$ 个 $2\times4$ 的棋盘，$b$ 个 $2\times5$ 的棋盘和 $2c$ 个 $1\times6$ 的棋盘拼成，答案为 $n\times m$。

不难得出只有 $m=2,3,7$ 时无解。 

所以 $n=m=2$ 时，答案为 $0$；$n=2,m=3$ 或 $m=2,n=3$ 时，答案为 $4$；$n=2,m=7$ 或 $m=2,n=7$ 时，答案为 $12$；否则答案为 $n\times m$。

### 情况 3 ： $2|n,n\ge4,m\ge3$ 或 $2|m,m\ge4,n\ge3$

不妨 $2|n$，$n=2k$。

若 $m\ne3,7$，则可以由 $k$ 个 $2\times m$ 的棋盘拼成，答案为 $n\times m$。

若 $m=7$，则可以用 $k$ 个 $2\times5$ 的棋盘和 $1$ 个 $2\times2k$ 的棋盘拼成，答案为 $n\times m$。

若 $m=3,2|k$，设 $k=2t$，则 $n=4t$，可以用 $t$ 个 $3\times4$ 的棋盘拼成，答案为 $n\times m$。

若 $m=3,2\nmid k$，设 $k=2t+1$，则 $n=4t+2\ge6$，可以用 $(t-1)$ 个 $3\times4$ 的棋盘和 $3$ 个 $1\times6$ 的棋盘拼成，答案为 $n\times m$。

所以这类情况答案均为 $n\times m$。

### 情况 4 ： $2\nmid n,2\nmid m,n\ge3,m\ge3$

不难发现答案一定不超过 $n\times m-1$，且借助 $1\times6$ 的棋盘可知一定情况下，$n\times m$ 的棋盘与 $(n\mod6)\times(m\mod6)$ 的棋盘等价。

#### 情况 4.1 ： $n\mod6=3$ 或 $m\mod6=3$

不妨设 $n\mod6=3$，则这等价于 $n=3,m\ge3$。

对于任意大等于 $3$ 的奇数 $m$，我们总可以按如下方法递归地构造出如下图形。

![](https://cdn.luogu.com.cn/upload/image_hosting/u3go8ym8.png)

$m=3$：

![](https://cdn.luogu.com.cn/upload/image_hosting/mox8faio.png)

$m=5$：

![](https://cdn.luogu.com.cn/upload/image_hosting/9ae5puyf.png)

$m=7$：

![](https://cdn.luogu.com.cn/upload/image_hosting/nk0pdva1.png)

$m=9$：

![](https://cdn.luogu.com.cn/upload/image_hosting/yn65p2yk.png)

对于最后一个图形我们可以这样摆放棋子：

![](https://cdn.luogu.com.cn/upload/image_hosting/clmgblol.png)

此时总共放了 $n\times m-1$ 个棋子，达到最优状态，故答案为 $n\times m-1$。

#### 情况 4.2 ： $n\mod6=5$ 或 $m\mod6=5$

不妨设 $n\mod6=5$，则这等价于 $n=5,m\ge3$。

借助 $2\times5$ 的棋盘可知，这等价于 $1\times5$ 的棋盘。

而 $1\times5$ 的棋盘上最多可摆放 $4$ 个棋子，此时总共放了 $n\times m-1$ 个棋子，达到最优状态，故答案为 $n\times m-1$。


#### 情况 4.3 ： $n\mod6=1$ 且 $m\mod6=1$

这等价于 $n=m=1$，此时总共放了 $n\times m-1$ 个棋子，达到最优状态，故答案为 $n\times m-1$。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n,m,ans;
template<class T>void read(T &x)
{
	x=0;int f=0;char ch=getchar();
	while(ch<'0' || ch>'9')f|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x=f? -x:x;return ;
}
inline LL max(LL a,LL b)
{
	return a>b? a:b;
}
int main()
{
	read(n),read(m);
	if(n==1 || m==1)return 0&printf("%lld",(max(n,m)/6)*6+max(0,(max(n,m)%6)-3)*2);
	if(n==2 && m==2)return 0&printf("0");
	if((!(n&1) && m>=3) || (!(m&1) && n>=3))return 0&printf("%lld",((n*m)/2-((n==2 && m==3) || (m==2 && n==3) || (n==2 && m==7) || (m==2 && n==7)))*2);
	if((n%6)==3 || (m%6)==3)return 0&printf("%lld",((n*m)/2)*2);
	if((n%6)==5 || (m%6)==5)return 0&printf("%lld",((n*m)/2)*2);
	return 0&printf("%lld",((n*m)/2)*2);
}
```


---

## 作者：HansLimon (赞：8)

# 简单找规律
	
	这种题看着也没啥思路，不如好好模拟找规律。
首先先考虑一件事，输出答案中只能是2的倍数，因此当n\*m为奇数(即n、m都是奇数)时，输出结果 -1(-1 没搞懂没关系，往下看就是了qwq)

那我们就开始从小数据入手，快快乐乐找规律。

### Sit1. 1行多列
------------
由题意，每次选的两个格子的曼哈顿距离为3，说白了就是两个格子之间要有2个格子的空隙，一行(列)格子时就很简单。

就像是这样
![CF1034B 1](https://s2.ax1x.com/2019/10/08/ufG5Js.png)
然后接着填下去
![CF1034B 2](https://s2.ax1x.com/2019/10/08/ufJK6P.png)
然后一直一直......

这个时候我们再判定一下格子数少于等于3的情况，直接输出0就是了。

**那么第一部分：**
```cpp
if (n == 1)
	if (!(m%6))printf("%lld", m);
	else if (m%6 <= 3)printf("%lld", m - m%6);
	else printf("%lld", m - (6 - m%6));
```
哦，对，因为可以单独一行或单独一列所以我们在**读入后**还需要这样：
	
    if (n > m)swap(n, m);
### Sit2. 2行多列
------------
这里就使劲找规律qwq，具体流程：
![CF1034B 3](https://s2.ax1x.com/2019/10/08/ufUFgA.png)
这里推2主要是因为2比较特殊，这里也并没有完，还需要继续推

(~~考试时我就只推到了这然后以为找到了正解qwq~~**我太菜了**)

那么，**这一部分**的代码：
```cpp
else if (n == 2 && m == 2)putchar('0');
else if (n == 2 && m == 3)putchar('4');
else if (n == 2 && m == 7)printf("12");
```
这里是结合了$ Sit3. $的结论的，看不懂没关系啦~
### Sit3. 多行多列
###### 不想推了的说
同样的，我们继续**找规律**可以得出这个玩意：

|  行列   | 3   | 4   | 4   | 6   | 7   | 8   | ... |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 3   | 8   | 12  | 14  | 18  | 20  | 24  | ... |
| 4   | 12  | 16  | 20  | 24  | 28  | 32  | ... |
| ... | ... | ... | ... | ... | ... | ... | ... |

这里的规律显而易见，就是我们最开始所说的$ n*m(-1) $
```cpp
else if (n%2 && m%2)printf("%lld", n*m-1);
else printf("%lld", n*m);
```
就是这样。
### Par. 代码
```cpp
#include <cstdio>

long long n, m;

int main(){
	freopen("three.in", "r", stdin);
	freopen("three.out", "w", stdout);
	scanf("%lld %lld", &n, &m);
	if (n > m)n ^= m ^= n ^= m;//高级的swap 但是不建议用
	if (n == 1)
		if (!(m%6))printf("%lld", m);
		else if (m%6 <= 3)printf("%lld", m - m%6);
		else printf("%lld", m - (6 - m%6));
	else if (n == 2 && m == 2)putchar('0');
	else if (n == 2 && m == 3)putchar('4');
	else if (n == 2 && m == 7)printf("12");
	else if (n%2 && m%2)printf("%lld", n*m-1);
		else printf("%lld", n*m);
	return 0;
}
```
就相当于把之前几个部分的代码合了起来qwq

最后 祝大家
# CSP-S RP+++

---

## 作者：WarningQAQ (赞：5)

##### ~~这道题手画根本就搞不出来，能手画找到规律的都是欧皇。。~~

------------
### 分析：
每个点都可能会与周围距离为 $3$ 的点配对，从而放下棋子。

但当你在另一个位置放棋子时，若其周围距离为 $3$ 的点与之前放棋子的点冲突，那该如何解决？

问题突然变成二分图最大匹配，我们把方格看成点构成一张图跑二分图匹配即可。

**BUT~~T~~！**

若 $n$ ， $m$ 小于 $100$ 还好说，此题的 $n$ ， $m$ 是爆炸级别的，根本没法跑复杂度平方级别的算法，那就用刚刚写的程序打表找找规律吧。

这里又有一个很神奇的地方，当 $n$ 和 $m$ 为奇数的时候，输出 $ n\times m-1$；

当其中一个为偶数的时候，输出 $n\times m$ 。

**BUT~~T~~！**

当 $n$ 和 $m$ 小于 $20$ 的时候，这种情况就不在符合。

所以对 $n$ 和 $m$ 小于 $20$ 的情况，跑二分图匹配，其余的按照规律输出即可。~~（还不如好好找规律）~~

补充: 对与 $n=1$ 或者 $m=1$ 的情况要特殊处理下，明显 $1\times 6$ 的矩阵可以摆满棋子，所以答案为 $6\times \lfloor\frac{m}{6}\rfloor+2\times max\{ (m\bmod\ 6)- 3,0\} $。


------------

$\text{code\;:}$
```cpp
#include "cstdio"
#include "cstring"
#include "queue"
#include "map"
#define pii std::pair<int, int>
#define oo 0x3f3f3f3f
#define M 2000
const int dr[] = {3, 2, 1, 0, -3, -2, -1, 0, 2, 1, 0, -3, -2, -1};
const int dc[] = {0, 1, 2, 3, 0, 1, 2, 3, -1, -2, -3, 0, -1, -2};
long long n, m;
int cnt, g[M][M];
std::map<pii, int> MAP;
inline int FIND(pii p)
{
	if (MAP.count(p))
		return MAP[p];
	return MAP[p] = ++cnt;
}
int sx, sy;
inline void build()
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			for (int k = 0; k < 14; ++k)
			{
				int ni = i + dr[k], nj = j + dc[k];
				if (ni < 0 || ni >= n || nj < 0 || nj >= m)
					continue;
				g[FIND(pii(i, j))][FIND(pii(ni, nj))] = 1;
				sy++;
			}
		}
}
int zx[M], zy[M];
int dx[M], dy[M], dis;
bool vis[M];
inline bool bfs()
{
	std::queue<int> Q;
	dis = oo;
	memset(dx, -1, sizeof dx);
	memset(dy, -1, sizeof dy);
	for (int i = 1; i <= sx; i++)
		if (zx[i] == -1)
			Q.push(i), dx[i] = 0;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		if (dx[u] > dis)
			break;
		for (int v = 1; v <= sy; v++)
			if (g[u][v] && dy[v] == -1)
			{
				dy[v] = dx[u] + 1;
				if (zy[v] == -1)
					dis = dy[v];
				else
				{
					dx[zy[v]] = dy[v] + 1;
					Q.push(zy[v]);
				}
			}
	}
	return dis != oo;
}
inline bool dfs(int u)
{
	for (int v = 1; v <= sy; v++)
		if (!vis[v] && g[u][v] && dy[v] == dx[u] + 1)
		{
			vis[v] = 1;
			if (zy[v] != -1 && dy[v] == dis)
				continue;
			if (zy[v] == -1 || dfs(zy[v]))
			{
				zy[v] = u;
				zx[u] = v;
				return 1;
			}
		}
	return 0;
}
inline int work()
{
	int res = 0;
	memset(zx, -1, sizeof zx);
	memset(zy, -1, sizeof zy);
	while (bfs())
	{
		memset(vis, 0, sizeof vis);
		for (int i = 1; i <= sx; i++)
			if (zx[i] == -1 && dfs(i))
				res++;
	}
	return res;
}
int main()
{
	scanf("%lld%lld", &n, &m);
	if (n > m)
		std::swap(n, m);
	if (n == 1)
		printf("%lld", 6 * (m / 6) + 2 * std::max(m % 6 - 3, 1ll * 0));
	else if (n <= 20 && m <= 20)
	{
		sx = n * m;
		sy = 0;
		build();
		printf("%d", work());
	}
	else
	{
		if (n % 2 == 0 && m % 2 == 0)
			printf("%lld", n * m);
		else if (n % 2 == 0 && m % 2 || n % 2 && m % 2 == 0)
			printf("%lld", n * m);
		else
			printf("%lld", n * m - 1);
	}
	return 0;
}
```


---

## 作者：Leap_Frog (赞：1)

神必特判。  

以下讨论基于 $n\le m$

#### Case 1.
$n=1$ 显然，我们以 $6$ 为循环节，如图
```
1 2 3 1 2 3 4 5 6 4 5 6
```
（相同数字代表相互匹配，下同

#### Case 2.
$n=2$ 我们可以凑成 $4k$ $5k$ $6k$ 的形式，分别如下图
```
1 2 3 4
3 4 1 2
```

```
1 2 3 4 2
5 4 1 5 3
```
（感谢神 kai指导 提供这种情况，笔者想不出来

```
1 2 3 1 2 3
4 5 6 4 5 6
```

因为裴蜀定理，$4a+5b=x$ 肯定有解。  
因为这里需要 $a\ge 0,b\ge 0$ ，所以需要特判一下 `1 2 3 7`  

#### Case 3.
$n\ge 3$ ，根据上面两种构造，显然基本能填满（最多留一格，具体不证明

### Coding.
```cpp
//愿你和你重要的人能够重逢！
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:0;
}
int n,m;
int main()
{
	read(n),read(m);if(n>m) swap(n,m);//4+5+6
	if(n==1) return printf("%d\n",m/6*6+(max(0,m%6-3)<<1)),0;
	if(n>=3) return printf("%lld\n",1ll*n*m-((n&1)&(m&1))),0;
	if(m<=2) return puts("0");else if(m==3) return puts("4"),0;
	if(m==7) return puts("12"),0;else return printf("%d\n",m<<1),0;
}
```

---

## 作者：lfxxx (赞：0)

给出一个简单的证明。

首先我们判掉 $\min(n,m) = 1,2$，然后我们声称 $\min(n,m) \geq 3$ 时总是存在 $n \times m - (n \times m \bmod 2)$ 的方案。

由于可以黑白染色转化为二分图最大匹配模型，所以其实我们要证明的是存在对于数量更少的那一方颜色的完美匹配。

当 $3 \leq \min(n,m) \leq 5$ 时，只存在 $6$ 种情况，通过网络流可以搜出完美匹配方案，对于 $\min(n,m) > 5$ 的情况，我们不断地对 $n,m$ 中更小的那一方分治构造，最后分治树的所有叶子都满足 $3 \leq \min(n,m) \leq 5$，而在分治的过程中只会有一侧产生至多一个点的损耗，故原命题成立。

---

## 作者：wangyibo201026 (赞：0)

## 思路

石堆爱做结论题。

下文令 $n \le m$。

我们断言，若格子数为奇数时答案为 $nm - 1$，否则答案为 $nm$。

我们注意到当 $n \ge 3$ 时这个结论是对的。

当 $n = 1$ 时，我们发现每 $6$ 个可以构成一个循环节，对于余数大小单独考虑即可。

当 $n = 2$ 时，我们发现除开 $m = 2, 3, 7$ 之外都是符合规律的，特殊考虑即可。

写点特判这个题就过了。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;

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

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

bool ST;

int n, m;

bool ED;

void Solve () {
  cin >> n >> m;
  if ( n > m ) {
    swap ( n, m );
  }
  if ( n == 1 ) {
    if ( m % 6 == 0 ) {
      cout << m / 6 * 6;
    }
    else if ( m % 6 == 1 ) {
      cout << m / 6 * 6;
    }
    else if ( m % 6 == 2 ) {
      cout << m / 6 * 6;
    }
    else if ( m % 6 == 3 ) {
      cout << m / 6 * 6;
    }
    else if ( m % 6 == 4 ) {
      cout << m / 6 * 6 + 2;
    }
    else if ( m % 6 == 5 ) {
      cout << m / 6 * 6 + 4;
    }
  }
  else if ( n == 2 ) {
    if ( m == 2 ) {
      cout << 0;
    }
    else if ( m == 3 ) {
      cout << 4;
    }
    else if ( m == 7 ) {
      cout << 12;
    }
    else {
      if ( ( n * m ) & 1 ) {
        cout << n * m - 1;
      }
      else {
        cout << n * m;
      }
    }
  }
  else {
    if ( ( n * m ) & 1 ) {
      cout << n * m - 1;
    }
    else {
      cout << n * m;
    }
  }
}

signed main () {
#ifdef judge
  cout << ( double ) ( &ST - &ED ) / 1024.0 / 1024.0 << " MB" << '\n';
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 思路

看到这道题时，第一思路就是网络流，结果一看数据 $10^{9}$ 直接转向找规律。

**主要思路：神秘特判。** 

首先，下面的结论基于 $n\le m$。

### Case 1.

当 $n=1$ 时，易得的是我们可以以 $6$ 为循环节构造。

### Case 2.

当 $n=2$ 时，我们可以构造出 $4a,5a,6a$ 的形式。

易得，通过裴蜀定理得 $ax+5y=z$ 是一定有解的。

### Case 3.

当 $n>2$ 时，一定有解，很易得，就不给予证明了。

## AC Code


```
#include<bits/stdc++.h>
using namespace std;
//#define int long long
int n, m;
signed main() {
	cin >> n >> m;
	if (n > m)swap(n, m);
	if (n == 1)cout << m / 6 * 6 + (max(0, m % 6 - 3) << 1);
	else if (n > 2)cout << 1ll * n*m - ((n & 1) & (m & 1));
	else if (m <= 2)cout << 0;
	else if (m == 3)cout << 4;
	else if (m == 7)cout << 12;
	else cout << (m << 1);
	return 0;
}
```

---

## 作者：Kaenbyou_Rin (赞：0)

**前情提要：记得开 long long 。**



------------

其实我一开始的思路是网络流，但看到数据范围 $(1 \leq n,m \leq 10^9)$ 果断放弃。

这个范围很自然的想到找规律（以下默认 $n \leq m$)。

首先考虑 $n = 1$：

我们发现，当  $m \leq 3$ 时，棋子数等于 $0$，当 $4 \leq m \leq 5$ 时，棋子数等于 $m - 3$，当 $m = 6$ 时，棋子数等于 $6$。所以我们可以做出猜测：
```cpp
if(n==1){
 if((m%6)==0){
  printf("%lld\n",m);
  return 0;
 }
 if(m%6<=3){
  printf("%lld\n",m-m%6);
  return 0;
 }
 printf("%lld\n", m-(6-m%6));
 return 0;
}	
```
很显然，当 $m$ 大于 $6$ 时，我们可以通过将 $m$ 模 $6$ 转换成上文论述的状态。



------------

接下来考虑 $n = 2$：

我们手推发现，在当 $4 \leq m \leq 6$ 时都可以放满，所以我们特判 $m = 2$,$m = 3$ 和 $m = 7$，然后将前三种状态拼凑得出当 $8 \leq m \leq 11$ 时都可以放满，所以后面也都可以放满。（在当前状态后面加上 $1$ 个 $2 \times 4$ 的格子即可，并且仍是放满的状态。）

现在考虑 $n \ge 3$：

我们知道 $3 \times 3$ 的格子放不满，而且正好可以在中间剩下一个空格。而 $3 \times 5$ 可以看成一个满放 $2 \times 3$ 加上一个中间空一格的 $3 \times 3$,像这样继续在后面加上 $2 \times 2$ 的格子，就可以推知：

```cpp
if(n%2&&m%2) printf("%lld\n",n*m-1);
```

而当格子为偶数时，多余的空格都可以通过 $0 \times 3$ 的摆放方法补全。即满放。

于是我们得到了代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,m;
	scanf("%lld %lld",&n,&m);
	if(n>m) swap(n,m);
	if(n==2&&m==2){
		puts("0");
		return 0;
	}
	if(n==2&&m==3){
		puts("4");
		return 0;
	}
	if(n==2&&m==7){
		puts("12");
		return 0;
	}
	if(n==1){
		if((m%6)==0){
			printf("%lld\n",m);
			return 0;
		}
		if(m%6<=3){
			printf("%lld\n",m-m%6);
			return 0;
		}
		printf("%lld\n", m-(6-m%6));
		return 0;
	}	
    if(n%2&&m%2) printf("%lld\n",n*m-1);
	else printf("%lld\n", n*m);
	return 0;
}
```



---


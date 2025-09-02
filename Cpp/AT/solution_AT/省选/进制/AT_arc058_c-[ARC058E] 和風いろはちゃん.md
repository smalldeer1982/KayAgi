# [ARC058E] 和風いろはちゃん

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc058/tasks/arc058_c

日本の誇る美しいリズムとして、五七五というものがあります。 いろはちゃんは、数列から五七五を探すことにしました。でもこれは簡単だったので、XYZを探すことにしました。

長さ $ N $ の、それぞれの値が $ 1～10 $ の数列 $ a_0,\ a_1,\ ...,\ a_{N-1} $ を考えます。このような数列は全部で $ 10^N $ 通りありますが、そのうちXYZを含むものは何通りでしょう？

ただし、XYZを含むとは以下のように定義されます。

- $ a_x\ +\ a_{x+1}\ +\ ...\ +\ a_{y-1}\ =\ X $
- $ a_y\ +\ a_{y+1}\ +\ ...\ +\ a_{z-1}\ =\ Y $
- $ a_z\ +\ a_{z+1}\ +\ ...\ +\ a_{w-1}\ =\ Z $

を満たす $ 0\ ≦\ x\ <\ y\ <\ z\ <\ w\ ≦\ N $ が存在する。

なお、答えは非常に大きくなることがあるので、答えは $ 10^9+7 $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- $ 3\ ≦\ N\ ≦\ 40 $
- $ 1\ ≦\ X\ ≦\ 5 $
- $ 1\ ≦\ Y\ ≦\ 7 $
- $ 1\ ≦\ Z\ ≦\ 5 $

### Sample Explanation 1

$ \{5,7,5\} $ という数列のみが条件を満たします。

## 样例 #1

### 输入

```
3 5 7 5```

### 输出

```
1```

## 样例 #2

### 输入

```
4 5 7 5```

### 输出

```
34```

## 样例 #3

### 输入

```
37 4 2 3```

### 输出

```
863912418```

## 样例 #4

### 输入

```
40 5 7 5```

### 输出

```
562805100```

# 题解

## 作者：友人A_lie_of_April (赞：20)

### 样例输入

```
4 5 7 5
```
 
### 样例输出
```
34
```

## 先从正面思考

**朴素算法**：预处理出l长的字符总和为s的方案数（例如，2的长度下组合成5，有05、14、23、32、41、50,6种方案），考虑枚举x、y、z、w的值进行dp转移。但是在枚举过程中会出现许多次重复计算（例如 4 5 5 5的输入，在枚举中5 5 5  5的字串被计算了2次）。

为什么会产生重复计算呢？因为在枚举中，会有一个字串**有多个子串满足俳句**的要求。

## 从反面进行考虑

既然一个字串有多个字串满足俳句的话会被重复计算，那么我们只需要算出**没有子串满足俳句**的字串数，再用**总的字串数**减去这个值。

那么n位数字，就有10^n种字串数。

### 先划分状态

我们用i来表示状态转移到第i位，用二进制码表示枚举字串的结尾的状态。

我们将十进制数j，转化为第j位为1的二进制码，例如4->1000。如果4后面加上一个2变成4 2，我们用100010表示，即将4的二进制码向前移动2位，再加上10。同时这个二进制码第6位为1，即代表**末尾两个数**和为6，第2位为1，代表**最末尾的数**为2，用6减去2得4，可以得到**末尾第二个数**为4。

同理举个例子：如果我们枚举到5 3 4 我们得到二进制串 100001001000，这个二进制串可以表示**结尾可表示的数字**有12（12位上为1）、7（7位上为1）、4（4位上为1）、5（12-7=5）、3（7-4=3）、8（12-4=8），这样我们就把5 3 4这三个数字可以组成的情况都包含进去了。

原题中，最大状态为5+7+5=17位所以最多要枚举2^17种状态，在空间范围之内。

### 再来谈转移

我们先枚举i（0<=i<=n）表示当前在第几位，然后我们再枚举2^17的状态。
```
for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=sum;j++)//枚举状态
		{
			if(dp[i-1][j]==0) continue;
			for(int k=1;k<=10;k++)//枚举第i位添加的数字
			{
				int now=(j<<k)|(1<<k-1);//上面提到的二进制码转移
				now&=sum;//防止now溢出
				if((now&end)!=end)//如果状态存在俳句则不进行转移
					dp[i][now]=(dp[i][now]+dp[i-1][j])%mod;
			}
		}
	}
```

注意dp[0][0]=1

### 详细细节请参考代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int n,x,y,z;
int end;
int sum;
long long dp[45][1<<18];
long long ans=1,mod=1e9+7;

int main()
{
	freopen("haiku.txt","r",stdin);
	scanf("%d%d%d%d",&n,&x,&y,&z);
	memset(dp,0,sizeof dp);
	end=1<<x+y+z-1;
	end=end|(1<<y+z-1);
	end=end|(1<<z-1);//end记录满足俳句的状态
	sum=(1<<(x+y+z))-1;
	dp[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		ans*=10;
		ans%=mod;
		for(int j=0;j<=sum;j++)
		{
			if(dp[i-1][j]==0) continue;
			for(int k=1;k<=10;k++)
			{
				int now=(j<<k)|(1<<k-1);//上面提到的二进制码转移
				now&=sum;//防止now溢出
				if((now&end)!=end)//如果状态存在俳句则不进行转移
					dp[i][now]=(dp[i][now]+dp[i-1][j])%mod;
			}
		}
	}
	for(int j=0;j<=sum;j++)
		ans=(ans-dp[n][j]+mod)%mod;//用总字串数减去不满足俳句字串数
	printf("%lld",ans);
	return 0;
}
```





---

## 作者：Werner_Yin (赞：17)

*谨以此文纪念2021年我的第一篇题解以及一位文化课选手（无意中看到题目）在想了3天后（当然是一边搞文化课一边想）终于解决了这道题，然后一发最优解（目前的）*

upd:

* 1.7 修改部分笔误

[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/solution-arc058e.html)
# 题意

求满足

* $\forall i \in [0,n-1],a[i] \in [1,10]$
* $\exists x,y,z,w , 0 \leq x < y < z < w \leq n,\sum_{i=x}^{y-1}=X,\sum_{i=y}^{z-1}=Y,\sum_{i=z}^{w-1}=Z$

长度为 $n$ 数组 $a$

$\texttt{Data Range:}n\leq 40,X\leq 5,Y\leq 7,z\leq 5$

# Solution

开始想从 $n$ 下手，然而不太好搞，无意中看到 $X,Y,Z$ 范围$X+Y+Z <= 17$,范围挺像状压的，然后就有思路了。

从左往右扫 $a$ 数组的每一位来确定答案，那状压什么呢？

我们定义最后我们找的的满足条件的数组中$[x,w-1]$ 为我们**需要的部分**（当然，一个数组可以有多个这种部分），如图(即有颜色的部分）。

![](https://cdn.luogu.com.cn/upload/image_hosting/wuy1at9t.png)

而匹配的部分为$[x,y-1]$ 或者 $[x,z-1]$ , 即黄色部分 或者 黄色 + 蓝色的部分

我们要记录的是，所有可能的 需要的部分 剩下未匹配上的末尾和的可能值。

这个值一定十分小（$X+Y+Z <= 17$),状压一下就行了。

复杂度 $\texttt{O(}2^{X+Y+Z}nt\texttt{)}$ , 其中 $t = 10$。

# Code

为了节省空间，于是用了滚动数组。

为了方便转移，开了两个数组 ， $f$ 代表的是还没有完成匹配的方案数， $g$ 是代表完成匹配的方案数。

具体见代码吧。

```cpp
const int mod = 1e9+7;
const int MAXN = 1<<17;

int ok,s[20],x,y,z,n,ful;
int top,f[2][MAXN],g[2],ans;

void add(int &x,int y){x=x+y;if(x>=mod) x-=mod;}

int getstu(int stu,int num){
    //获取新状态
	int newstu = 0;
	for(int i = 0;i + num < x+y+z;i++){
		if(stu >> i & 1){
			if(s[i + num - 1] - s[i] > 0) continue;
            //如果剩下部分的和大于我们所需要的（漏匹配），肯定不行
			newstu |= 1<<(i + num);
		}
	}
	if(num <= x) newstu |= 1<<(num-1);
	return newstu;
}

int main (){
	scanf("%d %d %d %d",&n,&x,&y,&z);
	s[x-1] = s[x+y-1] = s[x+y+z-1] = 1;
	for(int i = 1;i < x+y+z;i++) s[i] = s[i-1] + s[i];
    //前缀和方便判断
	ok = 1<<(x+y+z-1); ful = 1<<(x+y+z);
	f[0][0] = 1;
	for(int o = 0,i = 1;i <= n;i++,o = o^1){
		memset(f[o^1],0,sizeof(f[o^1]));
		g[o^1] = g[o] * 10ll % mod;
        //已经完成匹配的方案数
		for(int stu = 0;stu < ful;stu++)
			if(f[o][stu]){
				for(int j = 1;j <= 10;j++){
					int ns = getstu(stu,j);
					if(ns & ok) add(g[o^1],f[o][stu]);
					else add(f[o^1][ns],f[o][stu]);
				}
			}
		if(i == n) ans = g[o^1];
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：AsunderSquall (赞：16)

~~被xyx的生成函数和tyy的置换群论搞懵了，所以来做一做不用推式子的计数题~~
# 题意  
给定 $X,Y,Z$，求长度为 $n$ 的序列 $\{a_i\}$，序列中每个数为 $1 \sim10$ 的数，求这样的序列个数，满足$\exists \ 0\le x<y<z<w \le n$，使得  
$$\sum_{i=x}^ya_i=X,\sum_{i=y+1}^z=Y,\sum_{i=z+1}^w=Z$$

数据范围$X\le5,Y\le7,Z\le 5,n \le 40$

# 思路
我最开始的思路是枚举 $3$ 个区间的长度和起始点，但是这样会算重，如果要加限定条件的话会非常不好搞，而容斥好像又行不通。  
发现 $X+Y+Z\le17$，考虑状压。  

我们要设计一种状压方案，储存一段和不超过 $17$ 的数。  
我们考虑到，将 $k$ 拆成若干个 $>0$ 的有序的数之和的方案数为$2^{k-1}$，意思是我们把 $k$ 当成 $k$ 个 $1$ ，然后每一位之间可以选择分割或者不分割。  
同理，对应到状压状态上，第 $i$ 位上为 $1$ 说明在第 $i$ 和 $i+1$位之间选择分割，也就是说存在一个前缀和为 $i$。  
举个例子，我们把 $17$ 分成 $5,7,5$，对应的压缩是`00001000000100001`，第 $5,12,17$位为 $1$，说明存在$5,12,17$的前缀和。  
这样压缩可以快速判断某个前缀和或者后缀和是否存在，考虑到一般的DP是从前往后搜的，我们这里构造后缀和。  
这有一个非常方便的应用——快速查询是否是可以使序列满足条件。  
只要你的这一段压缩同时存在这$Z,Y+Z,X+Y+Z$这些后缀和，那么就满足题意。  

接下来要考虑的是怎么快速转换这个压缩方式。当加入一个新数 $t$ 的时候，我们将原数左移 $t$ 位然后加上 `1<<(t-1)`。

（研究了挺久，说了这么半天P话，结果搞出来的东西被第一篇题解一下子就搞掉了，感觉很不爽，不过没有关系，这个能够体现出我的思路）

然后我们发现“存在”这个东西还是不好搞，考虑用全部减去不合法。  
全部的方案数为$10^n$，不合法的方案数用DP。  

设 $dp_{i,j}$ 表示枚举到第 $i$ 位，当前最后几位为 $j$ 的不合法方案数。    `chk(x)` 为 $x$ 是否为**不**合法状态。  
然后我们枚举下一位填的是什么，是否合法进行转移。

代码
```
#include<bits/stdc++.h>
#define int long long
#define rd(x) x=read()
using namespace std;
const int N=45;
const int maxn=(1<<18);
const int mod=1e9+7;
inline int read(){int x=0,f=1;char ch=getchar();while (ch>'9'||ch<'0'){if (ch=='-')f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline int ksm(int x,int y,int z){int ret=1;while (y){if (y&1) ret=(ret*x)%z;x=(x*x)%z;y>>=1;}return ret;}
inline int ksm(int x,int y){int ret=1;while (y){if (y&1) ret=(ret*x)%mod;x=(x*x)%mod;y>>=1;}return ret;}
inline int INV(int x){return ksm(x,mod-2);}

int n,X,Y,Z,ans;
int dp[N][maxn];
inline bool getbit(int x,int i){return x>>(i-1)&1;}
inline bool chk(int x)//检验x是否不合法
{
    if (!getbit(x,Z)) return 1;
    if (!getbit(x,Y+Z)) return 1;
    if (!getbit(x,X+Y+Z)) return 1;
    return 0;
}
signed main()
{
    rd(n);rd(X);rd(Y);rd(Z);
    
    dp[0][0]=1;
    for (int i=1;i<=n;i++)
        for (int j=0;j<(1<<(X+Y+Z));j++)
            for (int k=1;k<=10;k++)
            {
                int u=(j<<k)+(1<<(k-1));
                u&=(1<<(X+Y+Z))-1;
                if (chk(u)) dp[i][u]+=dp[i-1][j],dp[i][u]%=mod;
            }
    ans=ksm(10,n);
    for (int i=0;i<(1<<(X+Y+Z));i++) {ans+=mod-dp[n][i];ans%=mod;}
    cout<<ans<<endl;
}
```

---

## 作者：陈刀仔 (赞：11)

[题目链接][1]
一道状态压缩好题

首先，我们观察数据，可以发现$X,Y,Z$非常小，我们可以考虑状压，或者暴力枚举

我们先可以往暴力枚举枚举上想一想，我们可以枚举断点$x,y,z,w$的位置，然后预处理背包跑出$f[i]$表示有$i$个元素的数列能够有多少种方式拼出$i$的容量

然而这显然是不正确的，因为你在枚举到一种情况的$x,y,z,w$的位置时，**你在$x,y,z,w$之外的位置上的元素都是可以随便选择的**，然而这肯定会算重

我们没法这么做了，就可以去考虑一下状压

仍然没什么头绪，因为你还要考虑$x,y,z,w$的位置，这就很麻烦。

我们有一个关键的变形，首先我们由于会算重，所以就可以转换为**总方案数减去不带俳句子串的方案数**

怎样保证每个状态之间不重并且小巧地表示状态？我们又需要一个变形，**我们从考虑断点之间可以拼出对应的值转换为记下选出的所有元素可以拼出的所有值的集合**，状态$st$表示为当它从右往左数第$i$位是$1$时，表示**当前选数方案的后缀和集合**中可以找到$i$

如果在当前状态中可以找到$z,y+z,x+y+z$，那么这个状态已经包含了一个俳句，他以后转移出来的状态都一定会含有俳句，然而我们想要求的是**所有不会含有俳句的方案数**，所以这个拥有了俳句的状态就不能用于转移，为了方便，我们就把该状态$st$的$f[st]$记为$0$

我们记下数组$f[i][st]$表示在第$i$位上状态为$st$的方案数，剩下的转移是显然的
  [1]: https://www.luogu.com.cn/problem/AT1975

---

## 作者：crashed (赞：6)

&emsp;&emsp;**去往[原博客](https://www.cnblogs.com/crashed/p/13413765.html)食用更佳。**
# 题目
&emsp;&emsp;[点这里](https://www.luogu.com.cn/problem/AT1975)看题目。   
# 分析
&emsp;&emsp;首先，由于仅仅是 " 存在 " 这一条限制很容易导致计重，且总方案数就是 $10^n$ 。我们就可以考虑求补集，也就是不存在的情况。     
&emsp;&emsp;然后有一个很显然的 DP :   
&emsp;&emsp;$f(i,S)$：序列长度为 $i$ ，此时序列的**和 $\le X + Y + Z$ 的极长后缀**的状态为 $S$ 的方案数。   
&emsp;&emsp;举一个关于极长后缀的例子：   
```
    X=2,Y=5,Z=4
    ... 1 3 ( 2 5 3 )
```   
&emsp;&emsp;括号内的就是状态需要的极长后缀。    
&emsp;&emsp;那么怎么存下来这个后缀呢？   
## 暴力
&emsp;&emsp;写个搜索找一下方案数：   
```cpp
    void DFS( const int su )
    {
    	if( su > X + Y + Z ) return ;
    	++ cnt;
    	for( int i = 1 ; i <= 10 ; i ++ )
    		DFS( su + i ); 
    }
```   
&emsp;&emsp;得到结果：   
```
    input: X = 5, Y = 7, Z = 5
    output: cnt = 130624
```   
&emsp;&emsp;因而，实际上， $S$ 的状态数不会太多。我们可以全部搜索出来之后，建立 $S$ 和序号的映射关系。对于每个 $S$ ，我们可以直接得到它加了一个字符之后的转移，再进行 DP 。   
&emsp;&emsp;顺带一提， $S$ 也可以直接被压缩成 ```long long``` 范围内的数，方便 ```map``` 使用。    
&emsp;&emsp;时间复杂度最大是 $O(130642 \times 10\times n)$ ，有点卡，不过还好。   
## 优雅解法
&emsp;&emsp;我们假想出一条长度为 $X+Y+Z$ 的空格子列。那么一个数 $x$ 就相当于涂掉了连续的 $x$ 个格子。我们就只需要判断：第 $X$ 个格子是不是某次填涂的末尾？第 $X + Y$ 个格子是否是某次填涂的末尾？第 $X+Y+Z$ 个格子是否是某次填涂的末尾？     
&emsp;&emsp;进而可以想到一个状态压缩的方法：对于一个数 $x$ ，我们就把 $[1,x)$ 的格子留空，把第 $x$ 个格子涂上颜色，标记这里是一次填涂的尾巴。这样我们就可以利用位运算快速查出当前状态是否合法。   
&emsp;&emsp;煮几个栗子：   
```
    input: X = 3, Y = 2, Z = 4 => 001010001
    原序列         转化为格子        转化后的序列
    1 1 1 3 2 1 => 1 1 1 001 01 1 => 111001011    
                                       ^ x   ^    mismatched
    1 2 2 3 1   => 1 01 01 001 1  => 101010011    
                                       ^ ^   ^        matched
```      
&emsp;&emsp;这样应该就可以理解了。 DP 的时间复杂度是 $O(10\times n2^{X+Y+Z})$ 。    
&emsp;&emsp;~~这个方法理论复杂度要大一些，不过暴力被卡常了~~   
# 代码
&emsp;&emsp;~~因为一些你知道的原因~~，这里给出 Vjudge 上的 AC 记录。  
## 暴力
&emsp;&emsp;[ AC 记录](https://vjudge.net/solution/26629535)。
```cpp
#include <map>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long LL;
const int mod = 1e9 + 7;
const int MAXN = 45, MAXS = 2e6 + 5; 

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

map<LL, int> state;

int f[MAXN][MAXS];
int trans[MAXS][11];
int seq[MAXN], siz;
int cnt = 0;
int N, X, Y, Z;
bool legal[MAXS];

void add( int &x, const int v ) { x = ( x + v >= mod ? x + v - mod : x + v ); }

void DFS( const int su, const LL H )
{
	if( su > X + Y + Z ) return ;
	state[H] = ++ cnt;
	for( int i = 1 ; i <= 10 ; i ++ )
		DFS( su + i, H * 10 + i ); 
}

bool chk()
{
	int s[MAXN] = {};
	for( int i = 1 ; i <= siz ; i ++ ) s[i] = s[i - 1] + seq[i];
	bool flag = false;
	for( int i = 1 ; i <= siz ; i ++ )
		if( s[i] == X )
		{ flag = true; break; }
	if( ! flag ) return false;
	flag = false;
	for( int i = 1 ; i <= siz ; i ++ )
		if( s[i] == X + Y )
		{ flag = true; break; }
	if( ! flag ) return false;
	return s[siz] == X + Y + Z;
}

int push( const int c )
{
	int su = 0, l;
	for( l = siz ; l ; su += seq[l --] )
		if( c + su + seq[l] > X + Y + Z )
			break;
	LL val = 0;
	for( int j = l + 1 ; j <= siz ; j ++ )
		val = val * 10 + seq[j];
	if( c <= X + Y + Z ) val = val * 10 + c;
	return state[val];
}

void init( const int su )
{
	if( su > X + Y + Z ) return ;
	legal[++ cnt] = chk();
	for( int i = 1 ; i <= 10 ; i ++ ) trans[cnt][i] = push( i );
	for( int c = 1 ; c <= 10 ; c ++ )
		seq[++ siz] = c, init( su + c ), siz --;
}

int main()
{
	read( N ), read( X ), read( Y ), read( Z );
	DFS( 0, 0 ); 
	cnt = 0; init( 0 );
	
	f[0][1] = 1;
	for( int i = 0 ; i < N ; i ++ )
		for( int k = 1 ; k <= cnt ; k ++ )
			if( f[i][k] && ! legal[k] )
				for( int c = 1 ; c <= 10 ; c ++ )
					if( trans[k][c] && ! legal[trans[k][c]] )
						add( f[i + 1][trans[k][c]], f[i][k] );
	int ans = 1;
	for( int i = 1 ; i <= N ; i ++ )
		ans = 10ll * ans % mod;
	for( int i = 1 ; i <= cnt ; i ++ )
		if( ! legal[i] )
			add( ans, mod - f[N][i] );	
	write( ans ), putchar( '\n' );
	return 0;
}
```
## 优雅的解法
&emsp;&emsp;[ AC 记录](https://vjudge.net/solution/26608382)。   
```cpp
#include <cstdio>

const int mod = 1e9 + 7;
const int MAXN = 45, MAXS = ( 1 << 17 ) + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

int f[MAXN][MAXS];
int N, X, Y, Z, st, all;

int bit( const int i ) { return 1 << i - 1; }
bool chk( const int S ) { return ( S & st ) == st; }
void add( int &x, const int v ) { x = ( x + v >= mod ? x + v - mod : x + v ); }
int insert( const int S, const int v ) { return ( S << v | bit( v ) ) & all; }

int main()
{
	read( N ), read( X ), read( Y ), read( Z );
	int up = 1 << X + Y + Z;
	all = ( bit( X + Y + Z ) << 1 ) - 1;
	st = bit( Z ) | bit( Y + Z ) | bit( X + Y + Z );
	
	f[0][0] = 1;
	for( int i = 0 ; i < N ; i ++ )
		for( int S = 0 ; S < up ; S ++ )
			if( f[i][S] && ! chk( S ) )
				for( int k = 1, T ; k <= 10 ; k ++ )
					if( ! chk( T = insert( S, k ) ) )
						add( f[i + 1][T], f[i][S] );
	int ans = 1;
	for( int i = 1 ; i <= N ; i ++ )
		ans = 10ll * ans % mod;
	for( int S = 0 ; S < up ; S ++ )
		if( ! chk( S ) )
			add( ans, mod - f[N][S] );
	write( ans ), putchar( '\n' );
	return 0;
}
```


---

## 作者：Sampson_YW (赞：5)

一个很自然的做法（

称一个序列为好串，当且仅当能被划分成三个连续段，每个连续段之和分别为 $X, Y, Z$。

发现 $X, Y, Z$ 很小，考虑把所有好串搜出来，根据插板法，一共有 $2^{X+Y+Z-3}$ 个。

然后要求的就是至少有一个子串为好串的序列。很明显是 AC 自动机经典题（

具体地，对所有好串建出 AC 自动机。然后设 $f_{i,j,0/1}$ 表示填了 $i$ 个数，在自动机上匹配到了状态 $j$，匹配过/没有匹配过一个好串的方案数。答案就是每个状态上，填了 $n$ 个数并且匹配过一个好串的方案数之和。

复杂度 $O(|\Sigma|n2^{X+Y+Z})$。[code](https://www.luogu.com.cn/paste/511jggcb)

---

## 作者：Gavin·Olivia (赞：4)

###   已经有大佬发了反向思考的题解了，我来补一个正向思考的
首先，我们来看一下数据范围 $(3≤n≤40,1≤x≤5,1≤y≤7,1≤z≤5)$

$3≤x+y+z≤17$,是一个十分小的范围，对于这种$20$以下的范围，我们选择状压。

$i$表示我们当前的状态，当$i$从右往左数第$k+1$位为$1$时，表示当前所填的所有数的和可能为$k$。$ne[i][j]$表示当前状态为$i$，下一位填$k$时我们所能够得到的状态。为了防止溢出，当$ne[i][j]>(1<<x+y+z)$时，我们要把它降到$1<<x+y+z$；

动态转移方程$f[i][ne[j][k]]=(f[i][ne[j][k]]+f[i-1][j])$%$m$;
($f[i][j]$表示第$i$位状态为$k$时的方案数）

接下来，上代码！（程序冗杂，仅供参考，不要取笑）
```cpp
#include<bits/stdc++.h>
 using namespace std;
 int m=1000000007,n,x,y,z;
 unsigned long long f[41][131075],ne[131075][11],i,j,k;
 int main()
{
    scanf("%d%d%d%d",&n,&x,&y,&z);
    y+=x; z+=y;
    for(i=1;i<=1<<z;i++)
     for(j=1;j<=10;j++)
      {
        ne[i][j]=1;
        for(k=0;k+j<=z;k++)if(i&(1<<k))
         if(!(k<x&&k+j>x)&&!(k<y&&k+j>y))
         //如果原本小于x或小于x+y但加上j后超过了，那么数列就不是俳句，预处理ne数组的时候要特别注意一下
          ne[i][j]|=1<<(j+k);
        if((i==(1<<z))||ne[i][j]>=1<<z)ne[i][j]=1<<z;
      }
    f[0][1]=1;
    for(i=1;i<=n;i++)
     for(j=1;j<=1<<z;j++)
      for(k=1;k<=10;k++)
       f[i][ne[j][k]]=(f[i][ne[j][k]]+f[i-1][j])%m;
    cout<<f[n][1<<z];
    return 0;
}
```

---

## 作者：洁咪 (赞：4)

一道很神奇的状压 DP。  
正面考虑存在满足条件的数列不好处理（因为思考一下就会发现无法去重），所以尝试从反面思考。  
考虑计算出不满足条件的数列的数量，再用总数减去它即得到答案。

于是考虑记录下末尾的情况：  
若最末尾的数为 $p$，则其状态为二进制下 $p$ 位为 $1$ 的二进制数。若再加入一个数 $q$，则将状态右移 $q$ 位再将第 $q$ 位设为 $1$。  
如果末尾三个数是 $x$，$y$，$z$，那么这样记录下来的状态中为 $1$ 的位数就是 $z$，$y+z$ 和 $x+y+z$。由此就可以判断末尾的三位数了。

举个例子吧，比如末尾是 $\texttt{575}$，那么：  
* 先加入 $5$，状态变为 $\texttt{10000}$。
* 再加入 $7$，状态变为 $\texttt{100001000000}$。
* 再加入 $5$，状态变为 $\texttt{10000100000010000}$。

设 ```f[i][j]``` 表示填到第 $i$ 位，状态为 $j$ 的不合法的方案数有几种，枚举数字转移即可。边界条件 ```f[0][0]=1```。  
最后用总方案数 $10^n$ 减去每种状态的不合法方案数就得到合法答案了。

------------
Code：
```cpp
#include<bits/stdc++.h>
const int p=1e9+7;
using namespace std;
typedef long long ll;

int n,x,y,z,goal,tot;
ll f[50][(1<<20)],ans;
int main() {
//	freopen("AT1975.in","r",stdin);
//	freopen("AT1975.out","w",stdout);
	scanf("%d%d%d%d",&n,&x,&y,&z);
	tot=(1<<x+y+z)-1;// 获取状态上限 
	goal|=1<<x+y+z-1;
	goal|=1<<y+z-1;
	goal|=1<<z-1;// 获取目标状态 
	
	f[0][0]=1;
	for(int i=1; i<=n; i++) {
		for(int j=0; j<=tot; j++) {
			int s;
			for(int k=1; k<=10; k++) {
				s=(j<<k)|(1<<k-1);// 移位得新状态 
				s&=tot;// 去除超出限制位数的状态 
				if((s&goal)==goal) continue;
				(f[i][s]+=f[i-1][j])%=p;
			} 
		}
	}
	
	ans=1;
	for(int i=1; i<=n; i++) (ans*=10)%=p;
	for(int i=0; i<=tot; i++) ans=(ans-f[n][i]+p)%p;
	printf("%lld\n",ans);
	
	return 0;
}

```


---

## 作者：james1BadCreeper (赞：2)

数据范围很小，因此考虑想得暴力一点。当后缀和超过 $X+Y+Z$ 时，再记录就没有意义（因为好区间不可能再被选取到），这样直接状压后缀和序列（将后缀和中出现的数存储起来），便可以简单判断是否出现了好区间。

如果从满足条件的区间考虑，会发现一个序列不一定只有一个好区间，这样很容易导致算重。因此对答案取补集，考虑计算没有满足条件的子区间的方案数。

设 $f_{i,j}$ 表示考虑序列前 $i$ 位，当前后缀和状压后为 $j$。转移时采用刷表法，枚举最后一个填的数，计算新的后缀和，如果满足条件便统计答案。


```cpp
#include <bits/stdc++.h>
using namespace std; 
const int P = 1000000007; 
inline void add(int &x, int t) { x += t; if (x >= P) x -= P; if (x < 0) x += P; }

int n, X, Y, Z, f[42][1 << 17]; 
bool check(int x) {
	if (!(x >> Z - 1 & 1)) return 1; 
	if (!(x >> Y + Z - 1 & 1)) return 1; 
	if (!(x >> X + Y + Z - 1 & 1)) return 1; 
	return 0; 
}

int main(void) {
	scanf("%d%d%d%d", &n, &X, &Y, &Z); 
	int ans = 1; f[0][0] = 1; 
	for (int i = 1; i <= n; ++i) {
		ans = 10ll * ans % P; 
		for (int j = 0; j < 1 << X + Y + Z; ++j)
			for (int k = 1; k <= 10; ++k) {
				int u = ((j << k) + (1 << k - 1)) & ((1 << X + Y + Z) - 1); 
				if (check(u)) add(f[i][u], f[i - 1][j]); 
			}
	}
	for (int i = 0; i < 1 << X + Y + Z; ++i) add(ans, -f[n][i]); 
	return !printf("%d\n", (ans + P) % P); 
}
```

---

## 作者：ListenSnow (赞：1)

[原题链接](https://www.luogu.com.cn/problem/AT1975)

## 题意

 若 $a=\{a_1,a_2,\cdots a_n\}$ 存在 $1\le x<y<z<w\le n+1$ 满足 $\sum\limits_{i=x}^{y-1}a_i=X,\sum\limits_{i=y}^{z-1}a_i=Y,\sum\limits_{i=z}^{w-1}a_i=Z$ 时，则称数列 $a$ 是**好的**。

-求在所有长度为 $n$ 且 $a_i\in\mathbb{N}^{+}\cap[1,10]$ 的 $10^n$ 个序列 $a$ 中，有多少个序列是**好的**，答案对 $10^9+7$ 取模。

#### 数据范围

 $3\le n\le40$，$1\le X\le5$，$1\le Y\le7$，$1\le Z\le5$。


## 思路

发现本题直接统计合法的序列很难解决去重问题，考虑容斥，即用总的方法数出不合法的方案数。

由于 $a \in [1,10]$，总的方案数就是 $10^n$。注意到 $X+Y+Z \leq 17$。可以考虑状压。

假设当前枚举的数为 $i$，那么加上这个数后序列是否合法，就是看是否原序列的**后缀**是否满足 $x+y+z-i$，$y+z-i$,$z-i$ 都出现了。那么就可以设 $f[i][j]$ 表示当前枚举到第 $i$ 个数，当前枚举的序列后缀状态为 $j$ 时的不合法序列方案数。

对于一个状态 $j$，它在二进制表示下的第 $i$ 位为 $1$ 就表示存在一个后缀为 $i$，当加入一个新的数 $k$ 时，后缀 $i$ 就更新为了 $k$，只需要将原状态向前移动 $k$ 位再把 $2^k$ 加进状态即可。由于 $X+Y+Z \leq 17$，大于 $17$ 的后缀就没有必要考虑了，可以直接略去。而为了避免出现合法序列，自然后缀中不能同时出现 $x+y+z$，$y+z$ 和 $z$，在转移的时候只需要判断一下当前状态是否包含了该合法状态即可。

## code:

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm> 
using namespace std;
const int N=55,mod=1e9+7,M=1<<20;
int n,m,x,y,z,f[N][M],ans;
int main()
{
//	freopen("seq.in","r",stdin);
//	freopen("seq.out","w",stdout);
	scanf("%d%d%d%d",&n,&x,&y,&z);ans=1;m=(1<<x+y+z)-1;
	for(int i=1;i<=n;i++) ans=1ll*ans*10%mod;
	int state=((1<<x+y+z-1))|((1<<y+z-1))|(1<<z-1);f[0][0]=1;
	for(int i=1;i<=n;i++)
	    for(int j=0;j<=m;j++)
	        if(f[i-1][j]&&(j&state)!=state)
	            for(int k=1;k<=10;k++)
	            {
	            	f[i][((j<<k)|(1<<k-1))&m]+=f[i-1][j];
	            	f[i][((j<<k)|(1<<k-1))&m]%=mod;
				}
	for(int i=0;i<=m;i++)
	    if((i&state)!=state)
	    {
	    	ans=(ans-f[n][i]+mod)%mod;
		}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：zhylj (赞：1)

将一个正整数 $X$ 划分为若干有标号的正整数之和相当于在 $X$ 个 $1$ 之间放置任意个隔板，故方案数为 $2^{X-1}$。所以合法的 $X,Y,Z$ -Haiku 的总数为 $2^{X+Y+Z-3}$ 个。

我们可以暴力把所有合法串搜出来，直接建个 AC 自动机。容易补集转化为求不合法的方案数，然后设 $f_{i,u}$ 表示长度为 $i$ 的串匹配到状态 $u$ 的方案数，直接 dp 即可，时间复杂度 $\mathcal O(2^{X+Y+Z}n^2)$.

```cpp
const int N = 5e5 + 5, Len = 50, Mod = 1e9 + 7;

int QPow(int a, int b) {
	int ret = 1, bas = a;
	for(; b; b >>= 1, bas = 1LL * bas * bas % Mod)
		if(b & 1) ret = 1LL * ret * bas % Mod;
	return ret;
}

int n;

int tr[N][11], fail[N], node_cnt; bool flag[N];
void Insert(int s[], int len) {
	int cur = 0;
	for(int i = 0; i < len; ++i) {
		if(!tr[cur][s[i]]) tr[cur][s[i]] = ++node_cnt;
		cur = tr[cur][s[i]];
	}
	flag[cur] = true;
}
std::queue <int> que;
void Build() {
	for(int i = 1; i <= 10; ++i)
		if(tr[0][i]) que.push(tr[0][i]);
	while(!que.empty()) {
		int u = que.front(); que.pop();
		for(int i = 1; i <= 10; ++i) {
			if(tr[u][i]) {
				fail[tr[u][i]] = tr[fail[u]][i];
				que.push(tr[u][i]);
			} else tr[u][i] = tr[fail[u]][i];
		}
	}
}
int f[Len][N];
void Dp() {
	f[0][0] = 1;
	for(int i = 0; i < n; ++i)
		for(int u = 0; u <= node_cnt; ++u)
			for(int c = 1; c <= 10; ++c) {
				int v = tr[u][c];
				if(flag[v]) continue;
				f[i + 1][v] = (f[i + 1][v] + f[i][u]) % Mod;
			}
}

int s[Len], cnt;
void Dfs(int cur, int res_X, int res_Y, int res_Z) {
	if(!res_Z) {
		Insert(s, cur);
		++cnt;
	} else if(!res_Y) {
		for(int i = 1; i <= res_Z; ++i) {
			s[cur] = i;
			Dfs(cur + 1, 0, 0, res_Z - i);
		}
	} else if(!res_X) {
		for(int i = 1; i <= res_Y; ++i) {
			s[cur] = i;
			Dfs(cur + 1, 0, res_Y - i, res_Z);
		}
	} else {
		for(int i = 1; i <= res_X; ++i) {
			s[cur] = i;
			Dfs(cur + 1, res_X - i, res_Y, res_Z);
		}
	}
}

int main() {
	int X, Y, Z;
	rd(n, X, Y, Z);
	Dfs(0, X, Y, Z);
	Build(); Dp();
	int ans = 0;
	for(int i = 0; i <= node_cnt; ++i)
		ans = (ans + f[n][i]) % Mod;
	ans = (QPow(10, n) - ans + Mod) % Mod;
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Benzenesir (赞：0)

>- 若 $a=\{a_1,a_2,\cdots a_n\}$ 存在 $1\le x<y<z<w\le n+1$ 满足 $\sum\limits_{i=x}^{y-1}a_i=X,\sum\limits_{i=y}^{z-1}a_i=Y,\sum\limits_{i=z}^{w-1}a_i=Z$ 时，则称数列 $a$ 是**好的**。
>- 求在所有长度为 $n$ 且 $a_i\in\mathbb{N}^{+}\cap[1,10]$ 的 $10^n$ 个序列 $a$ 中，有多少个序列是**好的**，答案对 $10^9+7$ 取模。
>- $3\le n\le40$，$1\le X\le5$，$1\le Y\le7$，$1\le Z\le5$。

编程兔有没有母亲啊，敢把这种东西放到山东普及补测来。

首先第一反应拆分数，然后我 `rush` 了一下发现过不了样例，因为这样一定会出现重复的问题，一个序列可能有多次匹配。

那接下来根据数据范围来猜算法了，不是搜索就是状压。

我们对于一个串被多次统计的问题，第一个想法就是找出一个代表的来统计，但是我们发现这是非常困难的。

这里我们统计不符合要求的串。

怎么统计呢，我们有一个废话的结论，我们枚举字符串的结束，对于一个有俳句的串，其一定有一个后缀符合要求。

如果直接枚举，判定很容易，但我们如果想一次统计多个串是否符合要求，那就需要进行分类。

我们发现，在上一个 `DP` 中，算重的原因是一个状态在判定为合法后会继续计算，我们如果想去掉这个问题只可能上容斥，但这个容斥过于不伦不类，无法实现，所以我们想到了**状压**。

我们先考虑对整个数组进行状压，考虑怎么把不是二进制的数压到二进制。

我们这么考虑，对于一个数 $i$，就把原来的状态左移 $i$ 位，然后再填上一个 1 就可以了，初始状态设为 1。

这样我们就可以判了，对于 $X,Y,Z$ 也这样构造出一个这样的串，称为基本串，同时对于每个串的每一个后缀，看一看两个与起来是不是还是基本串。

好的，这里的状压已经可以保证不重不漏了，接下来是优化复杂度。

假设我们枚举到了第 $i$ 位，那明显，每个状态只有最后的 $X+Y+Z+1$ 是有效的。

所以我们直接舍弃超出范围的位就可以了，这里的操作其实就是将一整个状态归入其末尾的状态。

这个题提醒了我们，状压是可以压正数的，同时状压的状态可以简化，可以归纳。

```c++
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ld long double
#define inf 0x7ffffff
#define int ll

using namespace std;
const int mod=1e9+7;
int n,x,y,z;
int ed,f[50][(1<<17)+10];
int tot,ans;

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
	cin >> n >> x >> y >> z;
	f[0][0]=1;
	tot=(1<<(x+y+z))-1;
	ed|=1<<(x-1);
	ed=((ed<<(y))|(1<<(y-1)));
	ed=((ed<<(z))|(1<<(z-1)));
	ans=1;
	for(int i=1;i<=n;++i){
		ans=(ans*10)%mod;
		for(int j=0;j<=tot;++j){
			if(f[i-1][j]==0) continue ;
			for(int k=1;k<=10;++k){
				int s=((j<<k)|(1<<(k-1)));
				s&=tot;
				if((s&ed)!=ed) {
					f[i][s]=(f[i][s]+f[i-1][j])%mod;
				}
			}
		}
	}
	for(int i=0;i<=tot;++i)
		ans=(ans-f[n][i]+mod)%mod;
	cout << ans<<endl;
	
	return 0;
} 
```

---


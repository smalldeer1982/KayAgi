# MUTDNA - DNA

## 题目描述

我们发现了一种新型 $DNA$ ,这种 $DNA$ 只由 $N$ 个字母 $A$ 构成,在一次辐射中这种 $dna$  变成了由总共 $N$ 个字母  $A$ 和 $B$ 构成,在辐射中只会发生两种异变： 1.将某个任意位置字母反转 ,例如：将第 $K$  位置的 $A$ 变为 $B$ ，或将  $B$ 变为  $A$ . 2.将  $1$ 到 $K$ 位置上的所有字母反转， $1≤K≤N$ 并且  $K$  可以任选. 请你计算将全  $A$  序列转化为最终序列需要最少多少次异变.每发生一个  $1$  异变或  $2$  异变都计入一次总异变数.

## 样例 #1

### 输入

```
1:
4
ABBA```

### 输出

```
1:
2```

# 题解

## 作者：北咸冥鱼 (赞：5)

看了一下**前面一篇题解**，自我感觉写的更加简洁易懂一点，就来讲一下吧~~（废话）~~

这道题显然是一道**DP**，因为可以前缀变换，
所以我们可以吧问题转换为求前i个数全部转换为A和全部转换为B所需的最小操作数，分别用fa[i]和fb[i]记录，

则：当s[i]='A'时，fa[i]由fa[i-1]推出，fb[i]既可由fb[i-1]推出，
也可由fa[i]做一次前缀变换推出，s[i]='B'时同理
```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long min(long long x,long long y){return x<y?x:y;}
int n,fa[1100000],fb[1100000];
char s[1100000];
int main()
{	
	scanf("%d",&n);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
		if(s[i]=='A') fa[i]=fa[i-1],fb[i]=min(fb[i-1]+1,fa[i]+1);
        							//两种状态转移方法
		else fb[i]=fb[i-1],fa[i]=min(fa[i-1]+1,fb[i]+1); 
	printf("%d",min(fa[n],fb[n]+1));
	return 0;
}

```

---

## 作者：那一条变阻器 (赞：4)

## 来发记忆化搜索的题解

------------

先想搜索思路，先是肯定从后往前搜，因为后面为A的，肯定不动，如果一个点为B，那么肯定要么反转前面全部，要么单独反转，最后到第一个点的时候，看为A还是B的，A的话$return 0$，否则$return 1$。然后就可以记忆化，$f[i][j]$表示第$j$个点为$i$（0为A，B为1）时的最优解，最后输出就行。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int f[2][1000010] , a[1000010];
void dfs(int now , int tot){	//tot为转化了几次 
	int x = a[now] ^ tot;	//看经过tot次转化变成了什么 
	if(f[x][now] != 0x3fffff) return;
	if(!x){
		dfs(now - 1 , tot);
		f[x][now] = f[a[now - 1] ^ tot][now - 1];	//更新 
	}else{
		dfs(now - 1 , tot ^ 1);
		f[x][now] = f[a[now - 1] ^ (tot ^ 1)][now - 1];
		dfs(now - 1 , tot);
		f[x][now] = min(f[x][now] , f[a[now - 1] ^ tot][now - 1]);	//更新 
		f[x][now]++;	//要旋转 
	}
}
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		f[0][i] = f[1][i] = 0x3fffff;	//初始化 
		char s;
		cin >> s;
		if(s == 'A') a[i] = 0;	//转化为0，1 
		else a[i] = 1;
	}
	f[0][1] = 0 , f[1][1] = 1;	//边界 
	dfs(n , 0);
	cout << f[a[n]][n];	//输出 
	return 0;
}
/*
12
AAABBBAAABBB
*/
```


---

## 作者：YingLi (赞：3)

题意显然，要么单点异或要么前缀异或。

所以可以想到前缀异或和。

但是这个题不能用前缀。比如BBAA，前缀异或和是1010，但实际上第一个B我们并不需要操作，第二个1的操作对前缀有效可以直接覆盖；同理，AABB，前缀异或和是0010，但事实上需要操作两次。再结合题目本身就是前缀有效，所以我们用的应该是**后缀异或和**。

后缀异或和上每个1都代表一次前缀操作。如果是两个1相邻，就等效于修改了一个单点，操作一次即可。所以贪心找相邻的1即可。

代码很短，没啥好解释的。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<map>
#define maxn 1000006
using namespace std;
typedef long long ll;
int read() {
	int x = 0, f = 1, ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
	return x * f;
}

int n, a[maxn], ans = 0;
char s[maxn];
signed main() {
	n = read(); scanf("%s", s); s[n] = 'A';
	for(int i = n - 1; i >= 0; i--) a[i] = (s[i] != s[i + 1]? 1 : 0);
	for(int i = 0; i < n; i++) if(a[i] && a[i + 1]) {ans++, a[i] = 0, a[i + 1] = 0;} else if(a[i]) ans++, a[i] = 0;
	printf("%d\n", ans);
	return 0;
}
/*
20
ABABAABBBBBBAABABAAA
*/

```


---

## 作者：MuYC (赞：1)

这一道题的动态规划算法已经有了，然而，我在这里写出一个稍微优化的动态规划（也没有优化吧，但是好处理）

首先这道题，它要求将全A序列转为给出序列，其实我们还可以把现在序列改回全A序列，这是没有影响的，我们可以将A标记位0，B标记为1,然后可以将连续的一段A或者B缩减成一个点，并且那个点的权值就树A或者B出现的数量，然后就快乐的动规吧。。

我们开两个动归数组：一个记录将此序列转化为全A序列的最小次数，	一个dp1记录将反序目标序列转化为全A序列的步数（反序只将原序列中的A变成B，B变成A）

例如：AAABBBAAABBB，反序的就是BBBAAABBBAAA

开dp1是因为这个DNA需要两种操作：将一个A(B)变成B(A)，将一段A(B)变成B(A)
dp1就是为了维护将这一段1～k反转之后的序列

dp1表示的就是将的反序的目标数组转化为全A数组的最小步数

然后就可以愉快的dp了

可以得到一个动态转移方程式：
```cpp
if(fl[i] == 0)dp[i]=dp[i-1],dp1[i]=min(dp1[i-1]+sum[i],1+dp[i]);
		if(fl[i] == 1)dp1[i]=dp1[i-1],dp[i]=min(dp[i-1]+sum[i],1+dp1[i]);
```
# CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,t=0;
int sum[1000000+5];
char a[1000000+5];
int dp[1000000+5];
int dp1[1000000+5];
int fl[1000000+5];
int main(){
	cin>>n;char ch=getchar();
	for (int i = 1 ; i <= n; i ++){
		char ch=getchar();a[i]=ch;
	}
	for (int i = 1 ; i <= n;  i ++){
		int j = i ;
		while(a[i] == a[i+1])i++;
		t++,fl[t]=a[j]-'A',sum[t]=i-j+1;
	}
	for (int i = 1 ; i <= t ; i ++){
		if(fl[i] == 0)dp[i]=dp[i-1],dp1[i]=min(dp1[i-1]+sum[i],1+dp[i]);
		if(fl[i] == 1)dp1[i]=dp1[i-1],dp[i]=min(dp[i-1]+sum[i],1+dp1[i]);
	}
	cout<<dp[t];
	return 0;
}
```


---

## 作者：ddwqwq (赞：1)

蒟蒻我自己研发了一种未经证明，可能错误的dp方式。但是毕竟AC了，可见至少是个近似算法。。。  
f(i,j)表示处理前i个字母，且最后一位进行了j次前缀翻转，需要的最少操作次数。   
显然~~（无敌的“显然证明法”）~~，j大于2的情形无须考虑。我们在转移的时候，考虑把前一位的前缀操作“拉长”，使之覆盖当前位。  
我想想怎么大概地解释为何只需考虑j小于等于2的情形。很明显，最后的答案中一定不会有某一个位置存在大于1次的前缀翻转（因为两个可以消掉），但是如果只考虑j小于等于1的情形，某些转移会存在“模糊性”（希望这个词足够准确），无法得出正确答案。但是，在引入j等于2的情形后，我们会发现这种“模糊性”消失了！也就是说，一定可得到正确答案（希望如此）。读者可以自行考虑一下两种转移的区别，毕竟使用某个算法之前，至少要说服自己，让自己觉得它是正确的。。   
有了状态描述之后，就是转移方程了。这个可以直接看代码（代码中用f表示同样的意思，在函数"DP"中）。
```
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <math.h>
#include <cstring>
#include <time.h>

#pragma warning(disable:4996)
#define INF 2000000005//2 * 10^9
#define lowbit(a) ((a)&-(a))
inline long long max(long long a, long long b)
{
	return a > b ? a : b;
}
inline long long min(long long a, long long b)
{
	return a < b ? a : b;
}

const int MAXN = 1000005;

int N;
char s[MAXN];
int f[MAXN][3];

void DP()
{
	N = strlen(s + 1);
	if (s[1] == 'A')
	{
		f[1][0] = 0;
		f[1][1] = f[1][2] = 2;
	}
	else
	{
		f[1][0] = f[1][1] = 1;
		f[1][2] = 3;
	}
	for (int i = 2; i <= N; i++)
	{
		if (s[i] == 'A')
		{
			f[i][0] = min(f[i - 1][0], min(f[i - 1][1], f[i - 1][2]));
			f[i][1] = min(f[i - 1][0] + 2, min(f[i - 1][1] + 1, f[i - 1][2] + 1));
			f[i][2] = min(f[i - 1][0] + 2, min(f[i - 1][1] + 2, f[i - 1][2]));
		}
		else
		{
			f[i][0] = min(f[i - 1][0], min(f[i - 1][1], f[i - 1][2])) + 1;
			f[i][1] = min(f[i - 1][0] + 2, min(f[i - 1][1], f[i - 1][2]));
			f[i][2] = min(f[i - 1][0] + 3, min(f[i - 1][1] + 2, f[i - 1][2] + 1));
		}
	}
	printf("%lld", min(f[N][0], min(f[N][1], f[N][2])));
}

int main()
{
	scanf("%d%s", &N, s + 1);
	DP();

	system("pause");
	return 0;
}
```

---

## 作者：Bpds1110 (赞：0)

一眼的 DP。

考虑用 $dp_{i, 0 / 1}$ 分别 $1 \sim i$ 位所有都为 $A / B$ 的情况下的最少操作次数。

对于每个 $dp_{i, 0 / 1}$，都可以从上一位推出。

例如，假设当前位为 $A$，那么 $dp_{i, 0} \gets \min\{ dp_{i - 1, 0}, dp_{i - 1, 1} + 1\}$。表示可以从前 $i - 1$ 位全是 $A$ 得到，或者全是 $B$ 再进行翻转得到。同理，$dp_{i, 1} \gets \min\{ dp_{i - 1, 1} + 1, dp_{i - 1, 1} + 1\}$，考虑到 $i$ 全变为 $B$ 的情况。

以此类推，求出当前为 $B$ 的所有情况。目标状态为 $dp_{n, 0}$ 或 $dp_{n, 1} + 1$，即全变为 $B$ 再进行一次翻转。


```cpp
#include <bits/stdc++.h>
 
const int N = 1e6 + 100;
char a[N];
int n, dp[N][3];
 
int main ( ) {
    std::cin >> n >> a + 1;
    for (int i = 1; i <= n; ++ i) {
        if (a[i] == 'A') {
            dp[i][0] = std::min(dp[i - 1][0], dp[i - 1][1] + 1);
            dp[i][1] = std::min(dp[i - 1][0] + 1, dp[i - 1][1] + 1);
        }
        else {
            dp[i][0] = std::min(dp[i - 1][0] + 1, dp[i - 1][1] + 1);
            dp[i][1] = std::min(dp[i - 1][0] + 1, dp[i - 1][1]);
        }
    }
    std::cout << std::min(dp[n][1] + 1, dp[n][0]);
    return 0;
}
```


---

## 作者：SUNCHAOYI (赞：0)

第二种操作是从 $1$ 开始修改的，也就是修改一段前缀，考虑递推。由于操作可逆，所以我们可以转换为将读入的串变为全 `A` 串所需的最小变换次数。

设 $f_{i,0}$ 表示前 $i$ 个字符均为 `A` 时的最小变换次数，设 $f_{i,1}$ 表示前 $i$ 个字符均为 `B` 时的最小变换次数。在处理第 $i$ 个字符时，前 $i - 1$ 个字符只有全 `A` 或全 `B` 两种情况，而我们现在可以将前 $i$ 个字符变为全 `A` 或全 `B`。令第 $i$ 个字符是 `A`，进行分类讨论：

- $f_{i - 1,0} \to f_{i,0}$ 不需要操作，直接在末尾添上 `A`。

- $f_{i - 1,0} \to f_{i,1}$ 添上 `A` 后将区间 $[1,i]$ 进行翻转。

- $f_{i - 1,1} \to f_{i,0}$ 将区间 $[1,i - 1]$ 进行翻转，之后添上 `A`。

- $f_{i - 1,1} \to f_{i,1}$ 将区间 $[1,i - 1]$ 进行翻转，之后将 `A` 变为 `B` 并添上。操作等价于 $f_{i,0} \to f_{i,1}$。

若第 $i$ 个字符是 `B` 同理。最后的要求全为 `A` 串，答案也就是 $\min (f_{n,0},f_{n,1} + 1)$。

由于 $f_{i,0},f_{i,1}$ 只与 $f_{i - 1,0},f_{i - 1,1}$ 有关，所以我们可以将 $f$ 数组的第一维滚掉，即空间上的一个优化。

最后代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e6 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,f[2][2];
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();
	for (int i = 1;i <= n;++i)
	{
		char ch;scanf ("%c",&ch);
		if (ch == 'A') f[1][0] = min (f[0][0],f[0][1] + 1),f[1][1] = min (f[1][0],f[0][1]) + 1;//f[1][0] 之前已经算出，直接使用
		else f[1][1] = min (f[0][1],f[0][0] + 1),f[1][0] = min (f[1][1],f[0][0]) + 1;
		f[0][0] = f[1][0],f[0][1] = f[1][1];
	}
	printf ("%d\n",min (f[0][0],f[0][1] + 1));
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}

```

---

## 作者：happybob (赞：0)

显然一个 DP，考虑设 ${f1}_i$ 表示将前 $i$ 个字符转换成**目标字符串**的最小次数，${f2}_i$ 表示将前 $i$ 个字符转换成**与目标字符串正好相反**的最小次数。那么容易推出，${f1}_i$ 与 ${f2}_i$ 都可以通过前一个状态，即 ${f1}_{i-1}$ 与 ${f2}_{i-1}$ 推出，复杂度 $O(n)$。

具体转移方程请看代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;

const int N = 1e6 + 5;
int f1[N], f2[N];
int n;
string s;

int main()
{
	scanf("%d", &n);
	cin >> s;
	f1[1] = (s[0] == 'A' ? 0 : 1);
	f2[1] = (s[0] == 'A' ? 1 : 0);
	for (int i = 2; i <= n; i++)
	{
		if (s[i - 1] == 'A')
		{
			f2[i] = f2[i - 1] + 1;
			f1[i] = min(f1[i - 1], f2[i] + 1);
			f2[i] = min(f2[i], f1[i] + 1);
		}
		else
		{
			f2[i] = f2[i - 1];
			f1[i] = min(f1[i - 1] + 1, f2[i] + 1);
			f2[i] = min(f2[i], f1[i] + 1);
		}
	}
	printf("%d\n", min(f1[n], f2[n] + 1));
	return 0;
}
```


---

## 作者：高冷 (赞：0)

首首首首首先，楼下那篇题解是qxq巨爷写的，请看我的题解的同学都去%%%qxq大佬
（蒟蒻我先溜了）

首先显而易见这道题目可以用dp的思想。

我们将两种操作（前缀、单个变换）分开处理，于是可以推出方程

f[i]=min(f[i],f[i-1]+q=='A'?0:1);//单点修改

f[i]=min(f[i],……………………………);//前缀修改 

而上面……的部分，不但难想，而且时间复杂度也很高。

于是我们就想到，前缀修改其实就是将前 i 个字符反转了一下，所以我们可以把整个串反转，同时dp原串、反转后的串，这样我们在进行前缀修改的时候，可以直接从另一串中得到前i-1个字符反转后的dp值。


---

```cpp
#include <algorithm> //STL通用算法
#include <cmath> //定义数学函数
#include <cstdio> //定义输入/输出函数
#include <iostream> //数据流输入/输出
#include <cstring> //字符串处理
#include <string> //字符串类
#include <ctime> //定义关于时间的函数
#define itn int
#define fro for
#define ll long long
#define reg register
#define inf 1234567890
/*#include <bitset> //STL位集容器
#include <cstype> //字符处理
#include <cerrno> //定义错误码
#include <complex> //复数类
#include <clocale> //定义本地化函数
#include <cstdlib> //定义杂项函数及内存分配函数
#include <deque> //STL双端队列容器
#include <exception> //异常处理类
#include <fstream> //文件输入/输出
#include <functional> //STL定义运算函数(代替运算符)
#include <limits> //定义各种数据类型最值常量
#include <list> //STL线性列表容器
#include <map> //STL映射容器
#include <iomanip> //参数化输入/输出
#include <ios> //基本输入/输出支持
#include <iosfwd> //输入/输出系统使用的前置声明
#include <istream> //基本输入流
#include <ostream> //基本输出流
#include <queue> //STL队列容器
#include <set> //STL集合容器
#include <sstream> //基于字符串的流
#include <stack> //STL堆栈容器
#include <stdexcept> //标准异常类
#include <streambuf> //底层输入/输出支持
#include <utility> //STL通用模板类
#include <vector> //STL动态数组容器
#include <cwchar.h>//宽字符处理及输入/输出
#include <cwctype.h> //宽字符分类*/

using namespace std;

int ans;

int max(int x,int y){
	return x>y?x:y;
}

int min(int x,int y){
	return x<y?x:y;
}

int read(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0' || ch>'9'){if (ch=='-')f=-1;ch=getchar();}
    while ('0'<=ch && ch<='9'){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

void write(int x){
	int buf[50];
    if (x<0) putchar('-'),x=-x;
    buf[0]=0;
    while (x) buf[++buf[0]]=x%10,x/=10;
    if (!buf[0]) buf[0]=1,buf[1]=0;
    while (buf[0]) putchar('0'+buf[buf[0]--]);
}

int f1[1001000],f2[1001000];//f1为原串
char q;

int main(){
	memset(f1,63,sizeof f1);
	memset(f2,63,sizeof f2);
	int n=read();
	f1[0]=f2[0]=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%c",&q);
		
		if (q=='A')
		{
			f1[i]=min(f1[i],f1[i-1]);
			f1[i]=min(f1[i],f2[i-1]+2);
		}
		else
		{
			f1[i]=min(f1[i],f1[i-1]+1);
			f1[i]=min(f1[i],f2[i-1]+1);
		}
		
		if (q=='B')
		{
			f2[i]=min(f2[i],f2[i-1]);
			f2[i]=min(f2[i],f1[i-1]+2);
		}
		else
		{
			f2[i]=min(f2[i],f2[i-1]+1);
			f2[i]=min(f2[i],f1[i-1]+1);
		}
	}
/*	for (int i=1;i<=n;i++) cout<<f1[i]<<" ";
	cout<<endl;
	for (int i=1;i<=n;i++) cout<<f2[i]<<" ";
	cout<<endl;*/
	cout<<f1[n];
	return 0;
}
```



---


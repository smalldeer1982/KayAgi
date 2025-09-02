# Modulo Sum

## 题目描述

# 题面描述

给出 $1$ 个长度为 $n$ 的序列，以及 $1$ 个正整数 $m$。问这个原序列中是否存在非空子序列，使其元素之和能被 $m$ 整除。

## 样例 #1

### 输入

```
3 5
1 2 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
1 6
5
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4 6
3 1 1 3
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
6 6
5 5 5 5 5 5
```

### 输出

```
YES
```

# 题解

## 作者：江户川·萝卜 (赞：16)

### 主要思路：抽屉原理+01背包

看到子序列的和我们马上想到 01背包，可是这么大的 $n$ 使我们无从下手。

这道题要求子序列之和能否为 $m$ 的倍数，也就是 $\bmod m$ 后为 $0$。

因为若干数之和再取模相当于把每个数取模后求和再取模，所以我们可以把每一个数先模 $m$。

子数组是子序列的特殊形式...然后子数组是前后两个前缀和之差...前缀和共有n个...！

当前缀和对于 $m$ 取模后的值只可能在 $[0,m)$ 之间，也就是 $m$ 种可能值。

这时候就要运用到小学二年级就学过的 ~~(雾)~~ 抽屉原理了！

这里我们要用到它的一条原理：

>把多于n个的物体放到n个抽屉里，则至少有一个抽屉里的东西不少于两件。

那我们把 $n$ 个前缀和的值放到 $m$ 个可能值里，如果 $n>m$ ，则必有相同值！

当两个相同值作差，结果为 $0$，也就是说，它们中间的这一个区间之和必是 $m$ 的倍数！

好了，$n>m$ 的情况解决完了，剩下就只有 $n\le m$ 的情况了。

整合一下此时的数据范围：

$1\le n \le m \le 10^3$

$n$ 大大缩小，可以使用 01背包 求解了。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,a[1005];
bool f[1005][1005],yn;
int main(){
	scanf("%d%d",&n,&m);
	if(n>m){
		puts("YES");
		return 0;
	}
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),a[i]%=m;
	for(int i=1;i<=n&&!yn;i++){
		f[i][a[i]]=1;
		for(int j=1;j<=m;j++){
			f[i][j]|=f[i-1][j];
			f[i][(j+a[i])%m]|=f[i-1][j];
		}
		yn|=f[i][0];
	}
	if(yn) puts("YES");
	else puts("NO");
	return 0;
}
```

---

## 作者：rui_er (赞：11)

根据抽屉原理，我们知道：如果 $n > m$，设 $s_i=\sum\limits_{j=1}^ia_j$，则必然存在 $1\le i < j\le n$ 使得 $s_i\bmod m=s_j\bmod m$，也就是 $\sum\limits_{k=i+1}^ja_k\bmod m=0$。

因此 $n > m$ 必然有解，我们只需要考虑 $n\le m$ 的情况，此时 $n\le 10^3$。

我们假设 $dp_{i,j}$ 表示考虑在前 $i$ 个数中选数，是否可能使得它们的和除以 $m$ 的余数为 $j$，初始状态 $dp_{i,a_{i}}=1$，枚举每个数和余数进行转移即可。

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
using namespace std;
typedef long long ll;
const int N = 1e3+5; 

int n, m, a[N], dp[N][N];
template<typename T> void chkmin(T &x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T &x, T y) {if(x < y) x = y;}

int main() {
	scanf("%d%d", &n, &m);
	if(n > m) return puts("YES")&0;
	rep(i, 1, n) {
		scanf("%d", &a[i]);
		a[i] %= m;
		if(!a[i]) return puts("YES")&0;
		dp[i][a[i]] = 1;
	}
	rep(i, 1, n) {
		rep(j, 0, m-1) {
			dp[i][j] |= dp[i-1][j];
			dp[i][(j+a[i])%m] |= dp[i-1][j];
		}
		if(dp[i][0]) return puts("YES")&0;
	}
	puts("NO");
	return 0;
}
```

---

## 作者：wsyhb (赞：6)

## 前言

本题解将会介绍一种题解区无人提到的，更无脑的做法。

## 题意简述

给定 $n$ 个数 $a_1,a_2,\cdots,a_n$，判断是否存在非空子集，其元素和为 $m$ 的倍数。

**数据范围**：$1 \le n \le 10^6$，$2 \le m \le 10^3$，$0 \le a_i \le 10^9$。

## 题解

子集和是经典 **0/1 背包问题**，可以轻松做到 $O(nm)$ 的时间复杂度。（因为和要 $\bmod \; m$，所以值域其实是 $O(m)$ 的）

由于题目只要求判断是否存在，所以可以用 **bitset** 优化，做到 $O(\dfrac{nm}{w})$ 的时间复杂度。

考虑将大小为 $v \; (0 \le v < m)$ 的物品加入背包，设原本的 bitset 为 `f`，由于是在 $\bmod \; m$ 意义下进行背包，所以新的 bitset 应为 `f|f<<v|f>>(m-v)`。（对于 $x+v \ge$ bitset 大小的 $x$，其贡献要通过右移 $m-v$ 位体现）

滚动一下 bitset，空间复杂度为 $O(m)$。

## 代码

注意一下实现的细节。

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e3+5;
bitset<1000> dp[2];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		int v;
		scanf("%d",&v);
		v%=m;
		int y=i&1,x=y^1;
		dp[y]=dp[x]|(dp[x]<<v)|(dp[x]>>(m-v));
		dp[y][v]=true;
	}
	for(int i=0;i<1000;i+=m)
	{
		if(dp[n&1][i])
		{
			puts("YES");
			return 0;
		}
	}
	puts("NO");
	return 0;
}
```

## 后记

说句闲话，鸽巢原理（又称抽屉原理/狄利克雷原理）是小学人教版六年级课本中的内容：

![](https://cdn.luogu.com.cn/upload/image_hosting/1mc8dnwz.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/6n8vc8sh.png)

~~应该不会有人不会吧~~

---

## 作者：Tan_Wei_Ye (赞：6)

介绍一种不用**脑子**的做法：

如果你和我一样，没想到结论，没关系，我们可以**暴力**。

### 步骤：
1. 直接把输入的 $a_i \bmod m$ 的结果存入一个 ```map``` 里。
1. 枚举 $ 0 \sim m$，按照 ```map``` 的值搞一个多重背包多出来，并用二进制优化。
1. 跑一遍 ```dp``` 。

时间复杂度：$O(n \log_2m)$

如果你用 ```bool``` 数组代替 ```map``` 的话，可以做到 $O(n)$ 。

上代码:
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
const int M=1e3+10;
int n,m,a[M],cnt,ans;
bool f[2][M];//滚动数组压缩空间
map<int,int> s;
signed main()
{
//========== step 1 ==========//
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=n;i++)
		scanf("%d",&x),s[x%m]++;
	if(s[0]) return puts("YES"),0;
//========== step 2 ==========//
	for(int i=0;i<m;i++)
	{
		if(!s.count(i)) continue;
		for(int j=0;(1<<j)<=s[i];j++)//二进制优化，时间复杂度正确的核心
		{
			a[++cnt]=(i*(1<<j))%m;
			s[i]-=(1<<j);
		}
		if(s[i])
			a[++cnt]=(i*s[i])%m;
	}
//========== step 3 ==========//
	for(int i=1;i<=cnt;i++)
	{
		f[i&1][a[i]]=1;
		for(int j=1;j<m;j++)
		{
			f[i&1][(j+a[i])%m]|=f[i&1^1][j];
			f[i&1][j]|=f[i&1^1][j];
		}
		ans|=f[i&1][0];
		memset(f[i&1^1],0,sizeof f[i&1^1]);//清空数组，不然会影响答案
	}	
	if(ans) puts("YES");
	else puts("NO");
}	
```

---

## 作者：mahao2002 (赞：3)

### 首先，蒟蒻的我要先膜一下机房的诸位dalao
前情提要：下午dyx dalao讲数论，然而我太弱了只听懂这一道

------------
### 此题考点为抽屉原理+背包 
#### 首先是抽屉原理
抽屉原理定义为：
##### 把多于n+1个的物体放到n个抽屉里，则至少有一个抽屉里的东西不少于两件。
代入本题中我们可以发现，当得到这个序列的n个前缀和%m时，一定会出现两个相同的数，这两个前缀和相减得到的序列和一定可以被m整除。因此，当n>m时我们可以特判为序列和一定可以被m整除，从而将n的范围从1e6缩小到1e3。
#### 其次是背包
特判后，n和m的数据范围都是1e3，n方可过，直接用简单的背包dp即可求解。
```
#include<cstdio>
using namespace std;
int n,m,a[1000010],f[1010][1010],ch;
//a数组完全可以开1e3的，但是我太弱了&&太懒所以先输入后特判的……
//刚开始还没看出来结果数组开小了re了三次……
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	if(n>m) 
	{
		printf("YES\n");
		return 0;
	}
	for(int i=1;i<=n&&!ch;i++)
	{
		a[i]%=m;
		f[i][a[i]]=1; //序列中必须有数，因此不能从0状态转移
		for(int j=1;j<=m&&!ch;j++)
		{
			f[i][j]|=f[i-1][j];//不取这个数
			f[i][(j+a[i])%m]|=f[i-1][j];//取这个数
			if(f[i][0]) ch=1;
		}
	}
	if(ch) printf("YES\n"); //好像输出Yes也能过？
	else printf("NO\n");
	return 0;
}
```

---

## 作者：Fengxiang008 (赞：2)

### 算法分析：

这很明显是一个 01 背包。


### 策略：


1. 把 $a_i$ 视为物品，每个物品要么选，要么不选。
     
2. 定义状态： $dp_{i,j}$ 表示前 $i$ 个物品可选，且元素之和模 $m$ 的余数是否为 $j$。

3. 状态转移方程：

```cpp
if(dp[i-1][j] == true)//前 i-1 个数可选，且元素之和是否为 j
{
	dp[i][j] = true;
	dp[i][(j+a[i])%m] = true;
}
```


4. 最后判断 $dp_{n,0}$ 是否等于 $true$。

正常解法到这就结束了。

**当然，这远远不够，如果不优化的话，上述方法会 TLE+MLE**。

所以还需要接下来的步骤：

5. 当 $ n \ge m$ 时，根据 **抽屉原理**，一定有两段区间的元素之和模 $m$ 同余，那么一定能选一个子序列，能被 $m$ 整除。 

### 上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool dp[1005][1005];
int n, m, a[10000005];
int main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		a[i] %= m;
	}
	if(n >= m)//已解释
	{
		cout << "YES";
		return 0;
	}
	for(int i = 1; i <= m; i++)//枚举 物品
	{
		dp[i][a[i]] = true;
		for(int j = 0; j <= m-1; j++)
		{
			if(dp[i-1][j] == true)//已解释
			{
				dp[i][j] = true;
				dp[i][(j+a[i])%m] = true;
			}
		}
	}
	if(dp[n][0] == true)
		cout << "YES";
	else
		cout << "NO";
	return 0;
}

```


---

## 作者：Edmundino (赞：1)

# 题意

```
给出 1 个长度为 n 的序列，以及 1 个正整数 m。问这个原序列中是否存在非空子序列，使其元素之和能被 m 整除。
```


# 分析

首先，我要给大家讲一下一个奥数问题

### 抽屉问题

题目：给你$n$个小球

问最多要多少个抽屉来装这些小球

保证一定有两个球在同一个抽屉

过程：我们先要把$n$放入$n$个抽屉中

这时，每个小球都在不同的抽屉了

当我们拿走一个抽屉

此时，就要一个球被抛弃了

他要再找个抽屉

但是剩下的抽屉里都有一个小球

所以那个小球就只好跟一个小球在同一抽屉里了

此时就满足了题目要求

所以答案是$n-1$个抽屉

现在我们再回来看这道题

有$n$个数，要对$m$取余

所以：当$n>m$时，必有两个数对$m$取余是相等的，

所以此时必定是`YES`

在深入看看：

当$n==m$时

有两种情况：

$1$没有两个数对$m$取余是相等的

此时必有一个数对$m$取余为$0$

$2$没有一个数对$m$取余为$0$

此时必有两个数对$m$取余是相等的

所以当$n>=m$时输出`YES`

再看$n<m$的情况

此时就是一个背包问题

而且复杂度为$O(n\times m)$

但是$n<m$就是$n,m<1000$

所以$01$背包就解决了

# 代码

### 背包部分

```cpp
	for(int i=1;i<=n;i++)
	{
		dp[i][a[i]%m]=1;
		for(int j=0;j<m;j++)
		{
			if(dp[i-1][j]==1)
			{
				dp[i][j]=1;
				dp[i][(j+a[i])%m]=1;
			}
		}
	}
```
$dp[i][j]$表示到第$i$个数$j$对$m$取余的结果

如果$j$ $mod$ $m==0$那$dp[i][j]=1$

否则，$dp[i][j]=0$

### 最后送上完整$AC$代码

```cpp
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>

using namespace std;

const int N=1e6+50,M=1e3+50;

int n,m,q[N],a[N],bo[N],dp[M][M];

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	if(n>=m)
	{
		cout<<"YES";
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		dp[i][a[i]%m]=1;
		for(int j=0;j<m;j++)
		{
			if(dp[i-1][j]==1)
			{
				dp[i][j]=1;
				dp[i][(j+a[i])%m]=1;
			}
		}
	}
	if(dp[n][0]!=0)
	{
		cout<<"YES";
		return 0;
	}
	else
	{
		cout<<"NO";
		return 0;
	}
}
```


---

## 作者：aRenBigFather (赞：1)

一个简单的类似于筛法的算法

乱搞搞就出来了

先对输入的数取模，然后计算取模后每个数的个数

然后用类似素数筛法的思想标记当前数i能新组成的数有多少

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000010;
const int maxm = 1010;
ll n,m;
int a[maxn];
int bukkit[maxm];//桶，记录每个数出现次数 
bool modflag[maxm];//整体能 组成数%m 的标记 
bool tmpflag[maxm];//当前nowcan下能组成的 新的数%m 的标记 
int main(){
    scanf("%lld%lld",&n,&m);
    memset(bukkit,0,sizeof bukkit);
    memset(modflag,0,sizeof modflag);
    for(int i=1;i<=n;i++) {
        scanf("%d",a+i);
        if(a[i] % m == 0){
            puts("YES");
            return 0;
        }
        bukkit[a[i]%m]++;
    }
    for(int i=1;i<=m;i++){
        if(bukkit[i]){
        	memset(tmpflag,0,sizeof tmpflag);
            for(int j=1;j<=bukkit[i];j++){
                ll nowcan = 1ll * i * j % m;
                if(nowcan == 0){
                    puts("YES");
                    return 0;
                }
                tmpflag[nowcan] = true;
                for(int k=1;k<=m;k++){
                    if(modflag[k]){
                        tmpflag[(k + nowcan)%m] = true;
                        if((k + nowcan)%m == 0){
                            puts("YES");
                    		return 0;
                        }
                    }
                }
            }
            for(int kk=1;kk<=m;kk++){
                if(tmpflag[kk]) {
                    modflag[kk] = true;
                }
            }
        }
    }
    puts("NO");
    return 0; 
} 
```

---

## 作者：Maxwang (赞：0)

这道题简单的鸽巢原理+dp

首先，什么是鸽巢原理？

> 把多于n+1个的物体放到n个抽屉里，则至少有一个抽屉里的东西不少于两件。

这道题也是这样，因为 mod 运算所具有的性质，即和的膜等于膜的和，首先我们把序列中的数先取模，缩小值域，再取做模运算之后序列的子集，这里这个序列，就像鸽巢原理中的 $n$ 个鸽子，值域 $[1,m]$ 就是抽屉，所以说一定有多个相同数存在，相对应的，其区间 $\sum^{i\leq r}_{i=l}a_i$ 一定存在 $m$ 的倍数或者 $0$（取过膜，0 也可以）。

故当 $m\leq n$ 时，一定存在一个子集，令$\sum^{i\leq r}_{i=l}a_i \bmod m = 0$，直接输出`YES`即可。

然后剩下的问题就是 $n,m\leq 10 ^3$ 的了，$\operatorname{O}(n^2)$ 的 dp 也可以能够轻松解决，写一个 01 背包即可。

##### Tips：
可以利用滚动数组优化，但是本蒟蒻还没有想出能压缩到一维的办法（菜死了）

`|=` 是位运算中的或运算+赋值，主要作用是既可以完成接下来的转移，还能不影响以前的转移，特判也是可以的。

`goto`是跳转符，跳转到指定的位置，和 `exit(0)` 一样常用方便。

上代码
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>

using namespace std;

#define rint register int
#define isnum(x) ('0' <= (x) && (x) <= '9')
template<typename tint>
inline void readint(tint& x) {
	int f = 1; char ch = getchar(); x = 0;
	for(; !isnum(ch); ch = getchar()) if(ch == '-') f = -1;
	for(; isnum(ch); ch = getchar()) x = x * 10 + ch - '0';
	x *= f;
}

const int MAXM = 1e3 + 99;

int n,k;
int a[MAXM],f[2][MAXM];
int main()
{
	readint(n),readint(k);
	if(n >= k)
		goto AC;
	for(rint i = 1;i <= n;i++)
	{
		rint x;
		readint(x);
		x %= k;
		if(x == 0)
		goto AC;
		a[i] = x;
	}
	for(rint i = 1;i <= n;i++)
	{
		f[i & 1][a[i]] = 1; 
		for(rint j = 0;j < k;j++)
		{
			f[i & 1][j] |= f[(i - 1) & 1][j];
			f[i & 1][(j + a[i]) % k] |= f[(i - 1) & 1][j];
			
		}
		if(f[i & 1][0])
		goto AC;
	}
	
	goto AK;
	
	AC:
		puts("YES");
		return 0;
		
	AK:
		puts("NO");
		return 0;
}
```

---

## 作者：_Felix (赞：0)

首先，我们发现n的范围非常大，m在1000以内。

我们知道，n>=m时，一定有一段数字和能被m整除。

所以，讨论n<m的情况。n在1000以内。

背包。dp[i][j]表示前i个数中取，和除以m余数为j的。

```
for(int i=1;i<=n;i++){
	dp[i][a[i]]=1;
	for(int j=0;j<m;j++){
		if(dp[i-1][j]==1){
			dp[i][j]=1;
			dp[i][(j+a[i])%m]=1;//别写j+a[i]，万一炸了呢
		}
	}	
}
```


完整的：
```
#include<bits/stdc++.h>
using namespace std;
int a[1005];
bool dp[1005][1005];
int main(){
	int n,m;
	cin>>n>>m;
	if(n>=m) printf("YES");
	else{
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			a[i]%=m;
		}
		for(int i=1;i<=n;i++){
			dp[i][a[i]]=1;
			for(int j=0;j<m;j++){
				if(dp[i-1][j]==1){
					dp[i][j]=1;
					dp[i][(j+a[i])%m]=1;
				}
			}	
		}
		if(dp[n][0]==1) printf("YES");
		else printf("NO");
	}
	return 0;
} 
```
最后%出题人和楼下神仙！

---


# [HAOI2011] Problem c

## 题目描述

给 $n$ 个人安排座位，先给每个人一个 $1\thicksim n$ 的编号，设第 $i$ 个人的编号为 $a_i$（不同人的编号可以相同）。

接着从第一个人开始，大家依次入座，第 $i$ 个人来了以后尝试坐到 $a_i$，如果 $a_i$ 被占据了，就尝试 $a_i+1$，$a_i+1$ 也被占据了的话就尝试 $a_i+2$……，如果一直尝试到第 $n$ 个都不行，该安排方案就不合法。

然而有 $m$ 个人的编号已经确定（他们或许贿赂了你的上司...），你只能安排剩下的人的编号，求有多少种合法的安排方案。

由于答案可能很大，只需输出其除以 $M$ 后的余数即可。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证
- $1 \leq T \leq 10$。
- $1 \leq n \leq 300$， $0 \leq m \leq n$， $2 \leq M \leq 10^9$。
- $1 \leq p_i$、$q_i \leq n$。
- $p_i$ 互不相同。 

## 样例 #1

### 输入

```
2
4 3 10
1 2 2 1 3 1
10 3 8882
7 9 2 9 5 10```

### 输出

```
YES 4
NO```

# 题解

## 作者：Log_x (赞：25)

---
## Solution
- 先考虑无解的情况，我们记 $s[i]$ 表示已经确定的 $m$ 人中编号 $\ge i$ 的人数。
- 那么如果存在 $s[i] > n - i + 1$，显然无解。
- 进一步的，对于有解的情况我们可以想到一个状态 $f[i][j]$，表示剩余 $n - m$ 人中编号 $\ge i$的人已经确定 $j$ 个人的编号的方案数，则：$$f[i][j] = \sum \limits_{k = 0}^j f[i + 1][j - k] \times C_j^k (0 \le j \le n - s[i] - i + 1)$$
- 即表示在已经确定 $j - k$ 人编号的情况下，再选择 $k$ 人确定编号为 $i$。
- 因为每个人都是互不相同的个体，所以对于任意一种方案，交换一些人的编号也算作不同的方案，因此还有乘上 $C_j^k$，表示 $j$ 个人任选 $k$ 人确定编号为 $i$。
- 答案即为 $f[1][n - m]$，时间复杂度 $O(Tn^3)$。

## Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

namespace inout
{
	const int S = 1 << 20;
	char frd[S], *ihed = frd + S;
	const char *ital = ihed;
	
	inline char inChar()
	{
		if (ihed == ital)
			fread(frd, 1, S, stdin), ihed = frd;
		return *ihed++;
	}
	
	inline int get()
	{
		char ch; int res = 0; bool flag = false;
		while (!isdigit(ch = inChar()) && ch != '-');
		(ch == '-' ? flag = true : res = ch ^ 48);
		while (isdigit(ch = inChar()))
			res = res * 10 + ch - 48;
		return flag ? -res : res; 
	}
};
using namespace inout;

typedef long long ll;
const int N = 305;
int f[N][N], sum[N], c[N][N];
int n, m, T, Mod, x; 

int main()
{	
//	freopen("c.in", "r", stdin);
//	freopen("c.out", "w", stdout);
	
	T = get();
	while (T--)
	{
		memset(sum, 0, sizeof(sum));
		memset(f, 0, sizeof(f));
				
		n = get(); m = get(); Mod = get();
		for (int i = 1; i <= m; ++i)
			x = get(), ++sum[get()];
		
		bool flag = false;
		for (int i = n; i; --i)
		{
			sum[i] += sum[i + 1];
			if (sum[i] > n - i + 1) 
			{
				flag = true;
				break;
			}
		}
		if (flag)
		{
			puts("NO");
			continue;
		}
		
		for (int i = 0; i <= n; ++i) c[i][0] = 1;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= i; ++j)
				c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % Mod;
	
		f[n + 1][0] = 1;
		for (int i = n; i; --i)
			for (int j = 0, jm = n - sum[i] - i + 1; j <= jm; ++j)
				for (int k = 0; k <= j; ++k)
					f[i][j] = ((ll)f[i][j] + (ll)f[i + 1][j - k] * c[j][k]) % Mod;
		printf("YES %d\n", f[1][n - m]); 
	}
	
//	fclose(stdin); fclose(stdout);
	return 0;
} 
```

---

## 作者：Hongse_Fox (赞：10)

[题目链接](https://www.luogu.com.cn/problem/P2523)
# 零.前记
~~组合数的预处理出现了负数下标，导致一开O2就炸，调了好几天~~
# 一.思路
## 1.无解
如果一个人的编号为$i$，那么他只能坐$i,i+1...n$的位置上，这里一共有$n-i+1$个座位

可是如果这$n-i+1$个座位都挤满了人，这道题就无解了

换言之，如果编号必须$>=i$的人数比$n-i+1$还要大，那么肯定非法

那么我们可以用$num_i$来记录编号必须为$i$的人数，$sum_i$记录$num$的后缀和

我们会发现$sum_i$就是编号必须$>=i$的人数，即若$sum_i>n-i+1$，直接输出NO

## 2.有解
### i.算法选择
n最多才到300，理论复杂度应该是$O(n^3)$

而加上这是一道统计合法方案数的题目，不难想到要用动态规划
### ii.状态设定
首先必要的一维肯定是第几个座位

在处理无解的情况时，我们发现编号$>=i$的人数也对答案产生了影响，因此第二维表示编号$>=i$的人数

综合起来$f_{i,j}$表示到第$i$个座位，编号$>=i$的人数为j的情况数

### iii.转移方程
在n个人之中，有一些自由人，他们的编号对前面的座位没有影响，但是对后面的座位有影响，因此我们要放弃正推，开始反推

我们可以先用$tot$来表示自由人总数，$tot$应该等于$n-m$

不妨假设在第$i$个座位有$k$个人，编号$>=i$的人数为$j$，那么上个状态应该是$f_{i+1,j-k}$

上一个状态中，编号$>=i+1$的总人数为$j-k$，其中有$sum_{i+1}$个人是固定人，自由人的数量应该为$j-k-sum_{i+1}$，而自由人总数为$tot$，因此剩下可供使用的自由人数量为$tot-j+k+sum_{i+1}$

在这$k$个人中，有$num_i$个人是已经固定了的，剩下的$k-num_i$个人要征用自由人来填补空位

在$tot-j+k+sum_{i+1}$个自由人中选取$k-num_i$个人，方案数为$C(tot-j+k+sum_{i+1},k-num_i)$

因此从递推方程为：
$$f_{i,j}=f_{i+1,j-k}\times C(tot-j+k+sum_{i+1},k-num_i)$$

### iv.边界
在先前的无解判断中，我们提到过编号$>=i$的人数不可以超过$n-i+1$，而第$i$个编号至少有$num_i$个人，因此在第$i$号座位，$j \in[num_i,n-i+1]$

而在第$i+1$座位，$j-k>=sum_{i+1}$，再加上$k>=num_{i}$，可以得到$k \in[num_{i},j-sum_{i+1}]$

### v.最终公式
将上述的式子全部结合起来，可以得到最终的转移方程：
$$f_{i,j}=\sum_{k=num_i}^{j-sum_{i+1}}f_{i+1,j-k} \times C(tot-j+k+sum_{i+1},k-num_i)$$

### vi.答案输出
最后的答案为$f_{1,n}$，即编号$>=1$的人数为$n$的方案数
# 二、实现细节
## 组合数预处理
模数不断在变，且不一定为质数，老式的用快速幂预处理阶乘和逆元再$O(1)$求组合数的方法不再适用

在这道题里面，由于数据不算大，可以对于每组数据用$O(n^2)$跑一个递推求组合数

式子为：
$$C(i,j)=C(i-1,j-1)+C(i-1,j)$$

# 三.代码
```cpp
#include<cstdio>
#include<cctype>
inline int R(){//快读 
	int r=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return r;
}
int n,m,tot,M,num[305],t,sum[305],q;//tot:自由人数量,num[i]:编号必须为i的数量,sum[i]:num的后缀和 
int f[305][305],c[305][305];//f[i][j]:有i个人的编号>=j的情况数 
int main(){
	t=R();
	for(register int qwq=1;qwq<=t;qwq++){
		for(register int i=1;i<=n;i++) num[i]=0;
		n=R();m=R();M=R();
		bool flag=1; 
		for(register int i=1;i<=m;i++){
			q=R();q=R();
			num[q]++;
		}
		sum[n]=num[n];sum[n+1]=0;
		for(register int i=n-1;i>=1;i--) sum[i]=sum[i+1]+num[i];
		for(register int i=1;i<=n;i++) if(sum[i]>n-i+1) {flag=0;break;}
		if(flag==0){puts("NO");continue;}//如果存在不合法情况就输出NO
		tot=n-m;//自由人数量为n-m
		for(register int i=0;i<=n;i++){//预处理组合数 
			c[i][0]=1;
			for(register int j=1;j<=n;j++){
				c[i][j]=c[i-1][j-1]+c[i-1][j];
				c[i][j]%=M;
			}
		}
		for(register int i=1;i<=n+1;i++)
			for(register int j=0;j<=n;j++) f[i][j]=0;
		f[n+1][0]=1;//编号>=n+1人数为0的情况数为1
		for(register int i=n;i>=1;i--){//枚举第几号 
			for(register int j=sum[i];j<=n-i+1;j++){//枚举大于等于i的人数 
				for(register int k=num[i];k<=j-sum[i+1];k++){//枚举当前的人数 
					f[i][j]=(1ull*f[i+1][j-k]*c[tot+k+sum[i+1]-j][k-num[i]]+f[i][j])%M;
				}
			}
		}
		printf("YES %d\n",f[1][n]);//编号>=1的人数为n的情况数即为最终答案 
	}
	return 0; 
}
```
# 四.后记
本题主要考察对状态的设计，在动态规划中，一定要选择正确的状态，才可以省掉一部分打代码的时间和程序的运行时间。

一定要三思再下手

Finally，谢谢大家

[更好的阅读体验](https://www.luogu.com.cn/blog/HongseFox/solution-p2523)

---

## 作者：i207M (赞：8)

**题意**

给n个人安排座位，先给每个人一个1~n的编号，设第i个人的编号为ai（不同人的编号可以相同），接着从第一个人开始，大家依次入座，第i个人来了以后尝试坐到ai，如果ai被占据了，就尝试ai+1，ai+1也被占据了的话就尝试ai+2，……，如果一直尝试到第n个都不行，该安排方案就不合法。然而有m个人的编号已经确定(他们或许贿赂了你的上司...)，你只能安排剩下的人的编号，求有多少种合法的安排方案。由于答案可能很大，只需输出其除以M后的余数即可。

首先，判断无解的情况：

设$s[i]$为i及之后已经确定编号的人数和，如果$s[i]>n-i+1$那么一定是不够坐的；

~~判断无解之后要立刻输出，不然判断ans为0的方法，会在方案数是p的倍数时被卡掉~~

然后考虑DP

设$f[i][j]$表示考虑到第i个人（从后往前），有j个没有强制编号的人被确定了编号的方案数；

转移$f[i-1][j+k-hv[i]]+=f[i][j]\times C_{n-m-j}^{k-hv[i]}$

（$hv[i]$是必选的人数）枚举这这里放几个人的编号，由于是选择，要乘上组合数；

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<deque>
#include<ctime>
#include<climits>
using namespace std;
#define ll long long
#define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pairint pair<int,int>
#define mem0(x) memset((x),0,sizeof (x))
#define mem1(x) memset((x),0x3f,sizeof (x))
il char gc()
{
    static const int BS = 1 << 22;
    static unsigned char buf[BS], *st, *ed;
    if (st == ed) ed = buf + fread(st = buf, 1, BS, stdin);
    return st == ed ? EOF : *st++;
}
#define gc getchar
template<class T>void in(T &x)
{
    x = 0;
    bool f = 0;
    char c = gc();
    while (c < '0' || c > '9')
    {
        if (c == '-') f = 1;
        c = gc();
    }
    while ('0' <= c && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = gc();
    }
    if (f) x = -x;
}
#undef gc
#define pb push_back
#define N 305
#define int ll
int n, m, md;
int fac;
int hv[N];
int s[N];
int f[N][N];
il void clear()
{
    mem0(hv);
    mem0(f);
    mem0(s);
}
int c[N][N];
signed main()
{
#ifdef M207
    freopen("in.in", "r", stdin);
#endif
    int t;
    in(t);
    while(t--)
    {
        clear();
        in(n), in(m), in(md);
        c[0][0] = 1;
        for(ri i = 1; i <= n; ++i)
        {
            c[i][0] = 1;
            for(ri j = 1; j <= i; ++j)
                c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % md;
        }
        for(ri i = 1, a, b; i <= m; ++i)
        {
            in(a), in(b);
            hv[b]++;
        }
        bool no = 0;
        for(ri i = n; i >= 1; --i)
        {
            s[i] = s[i + 1] + hv[i];
            if(s[i] > n - i + 1)
            {
                no = 1;
                break;
            }
        }
        if(no)
        {
            puts("NO");
            continue;
        }
        f[n][0] = 1; // sum(i+1) of have judged people, not pre judged
        // ans is f[0][n]
        for(ri i = n, mx; i >= 1; --i)
            for(ri j = 0; j <= n; ++j)
                if(f[i][j])
                {
                    mx = n - i + 1 - j - s[i + 1];
                    for(ri k = hv[i]; k <= mx; ++k)
                        (f[i - 1][j + k - hv[i]] += f[i][j] * c[n - m - j][k - hv[i]]) %= md;
                }
        printf("YES %lld\n", f[0][n - m]);
    }
    return 0;
}
```



---

## 作者：Star_Cried (赞：3)

## P2523 Problem c/P1386 座位安排

双倍经验，双倍快乐。

### 题意

给n个人安排座位，大家依次入座，第i个人来了以后尝试坐到$a_i$并顺次向后尝试。如果一直尝试到第n个都不行，该安排方案就不合法。然而有m个人的编号已经确定，你只能安排剩下的人的$a$，求有多少种合法的安排方案模mod。

### 做法

* 首先我们判无解的情况。设$sum_i$表示已确定的m个人中编号不小于i的人的个数。
* 显然当有一个$sum_i$大于$n-i+1$时无解，因为会顺次出去。
* 而显然如果没有这样一个sum一定就是有解的。



* 然后我们进行DP，设状态$f[i][j]$表示在剩下的$n-m$个人中编号不小于i的人中已确定j个人的方案数。那么有转移：

$$f[i][j] = \sum \limits_{k = 0}^j f[i + 1][j - k] \times C_j^k (0 \le j \le n - sum[i] - i + 1)$$

含义为已确定i+1~n人中的j-k个人的方案又确定了j中的k个人。注意这里的j不能超过$n-sum[i]-i+1$，即i后可选的人的数量。

其中，乘组合数的原因是上一步具体选定的人是未定的，其实就相当于在j里随便选k个。

边界为$f[n+1][0]=1$。曾试过$f[n][1]=f[n][0]=1$然后发现n有可能被指定为m中的。所以这也是等价的。

注意因为模数不一样每次必须单独求组合数。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
#define int long long
using namespace std;
inline int read(){
	int x=0,w=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=305;
	int n,m,mod,f[maxn][maxn],C[maxn][maxn],sum[maxn]; 
	inline void work(){
		memset(sum,0,sizeof sum);
		memset(f,0,sizeof f);
		n=read(),m=read(),mod=read();
		for(int i=1;i<=m;i++)read(),sum[read()]++;
		for(int i=n;i;i--){
			sum[i]+=sum[i+1];
			if(sum[i]>n-i+1)return (void)puts("NO");
		}
		for(int i=0;i<=n;i++)C[i][0]=1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		f[n+1][0]=1;
		for(int i=n;i;i--)
			for(int j=0;j<=n-sum[i]-i+1;j++)
				for(int k=0;k<=j;k++)f[i][j]+=f[i+1][j-k]*C[j][k]%mod,f[i][j]%=mod;
		printf("YES %lld\n",f[1][n-m]);
	}
}
signed main(){
	int T=read();
	while(T--)star::work();
	return 0;
}
```



---

## 作者：cz666 (赞：3)

# 思路：

### 状态: 

$f[i][j]$ 表示当前已经排好了后面 $i$ 个座位,处理掉了 $j$ 个平民的方案数。

### 转移: 

$f[i][j]=f[i][j]+C[j][k]*f[i+1][j-k](i<=n,j<=n-i+1-sum[i],k<=j)$。
  
#### 解释: 
  
表示当前想插入第 $i$ 个座位的人有 $k$ 个能对 $f[i][j]$ 有的贡献(因为只有最多 $j$ 个位置能供摆放，所以 $k$ 要小于等于 $j$ )。
    
这是个排列的问题，就相当于在后面 $j$ 个位置上放上 $k$ 个平民，组合数问题求解即可。
    
最后 $f[i][j]$ 累加上面各种情况的方案数就可以了。
    
### 初始:

$f[n+1][1$ ~ $n]=0,f[n+1][0]=1$ 。

#### 解释: 

 $n$ 个人排完第 $n+1$ 个位置，自然只有在 $0$ 个人已经排好的时候方案数为 $1$ ，其余全都不可能出现。
 
### 答案:

 $f[1][n-m]$ 。
 
#### 解释: 

答案就是第一个座位排完以后(即所有座位都排好了)的合法方案数。

### 备注：

**切记初始化！切记初始化啊！~~不初始化炸到见祖宗~~**

# 代码实现：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int res=0,pd=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')pd-=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){res=(res<<1)+(res<<3)+ch-'0';ch=getchar();}
	return res*pd;
}
inline void write(int x){
	if (x<0){putchar('-');x=-x;}
	if (x>=10) write(x/10);
	putchar(x%10|'0');
}
inline void Yes(int x){
	putchar('Y');putchar('E');putchar('S');
	putchar(' ');write(x);putchar('\n');
}
inline void No(){
	putchar('N');putchar('O');
	putchar('\n');
}
/*
状态:f[i][j]表示当前已经排好了后面i个座位,处理掉了j个平民的方案数 
转移:f[i][j]=f[i][j]+C[j][k]*f[i+1][j-k](i<=n,j<=n-i+1-sum[i],k<=j).
  解释: 
	表示当前想插入第i个座位的人有k个能对f[i][j]有的贡献(因为只有最多j个位置能供摆放，所以k要小于等于j).
	这是个排列的问题，就相当于在后面j个位置上放上k个平民，组合数问题求解即可.
	最后f[i][j]累加上面各种情况的方案数就可以了. 
初始:f[n+1][1~n]=0,f[n+1][0]=1.
  解释: 
    n个人排完第n+1个位置，自然只有在0个人已经排好的时候方案数为1，其余全都不可能出现.
答案:f[1][n-m].
  解释: 
    第一个座位排完以后(即所有座位都排好了)的合法方案数. 
*/
int sum[303],C[303][303],f[303][303];
signed main(){
	int T=read();
	while(T--){
		int n=read(),m=read(),M=read();
		for (int i=0;i<=n+1;++i) sum[i]=0;
		for (int i=0;i<=n;++i) for (int j=0;j<=n;++j) f[i][j]=0;
		for (int i=0;i<=300;++i){
			C[i][0]=C[i][i]=1;
			for (int j=1;j<i;++j) C[i][j]=(C[i-1][j-1]+C[i-1][j])%M; 
		}
		for (int i=1;i<=m;++i){int x=read();sum[read()]++;}
		for (int i=n;i>=1;--i) sum[i]+=sum[i+1];//后缀和以判断是否合法 
		for (int i=1;i<=n;++i) if (sum[i]>n-i+1){No();goto loop;}//排不下不合法 
		for (int i=0;i<=n;++i) if (i) f[n+1][i]=0;else f[n+1][i]=1;
		for (int i=n;i>=1;--i) for (int j=0;j<=n-i+1-sum[i]&&j>=0;++j)
		 for (int k=0;k<=j;++k) f[i][j]=(f[i][j]+C[j][k]*f[i+1][j-k])%M;
		Yes(f[1][n-m]);
		loop:;
	}
	return 0;
}
```


---

## 作者：IcyFoxer_XZY (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P2523)

#### 第十篇题解！！！好开心！！！$o(*￣▽￣*)ブ$



------------------------------------分割线--------------------------------------


### 分析：

序列合法的充要条件就是：大于等于 1 数的个数不超过 $n$ ，大于等于 2 数的个数不超过 $n-1$ ，...... ，大于等于 $i$ 的数不超过 $n-i+1$ ，大于等于 $n$ 的数的个数不超过 $1$ 。

我求出 $res[i]$ 表示大于等于 $i$ 的数还能用几个。

那么现在就是数一数有多少序列，满足大于等于 $1$ 的数的个数不超过 $res[i]$ 。

下图是一种合法方案，蓝色的 “进度条” 的结束位置就代表了实际中这个位置填了什么数字，上面的一排 $4$ ，$3$ ，$2$ ，$1$ 表示的是 “大于等于 $1$ 的不超过 $4$ 个，大于等于 $2$ 的不超过 $3$ 个，大于等于 $3$ 的不超过 $2$ 个，大于等于 $4$ 的不超过一个” ：

![](https://img-blog.csdnimg.cn/20200216090207816.png)

下图是一种不合法方案，大于等于 $1$ 的最多有一个，但是他却有两个：

![](https://img-blog.csdnimg.cn/20200216090541790.png)

$f_{ij}$ 表示所有的 “进度条” 都在 $i$ 或 $i$ 之前 “截止” ，并且在 $i$ “截止” 的进度条有 $j$ 个的方案数。

$f_{ij}=\sum\limits_{k=lj}^nf_{i-1},k\dbinom{k}{j}$

代码一不小心删了 qwq ，找时间 update qwq。

Bye！

---

## 作者：KAMIYA_KINA (赞：0)

## Tag

动态规划，计数，组合数学。

## Description

求一个长度为 $n$ 的序列 $\{a_n\}$，要求大于 $x$ 的 $a_i$ 的数量不能超过 $n-x+1$  个，并且有一些 $a_i$ 是给定的，求有多少个序列满足这个条件。

给定的 $a_i$ 数量为 $m$，并且每一次测试模数为给定的 $M$。

$\texttt{data range:}1\leq n \leq 300,0 \leq m \leq n, 2\leq M \leq 10^9$.

## Solution

我的描述已经解释了一定的题目，根据这个条件我们很容易就可以想出设 $s_i$ 为大于等于 $i$ 中有多少个编号，然后这个 $s_i$ 显然是不能大于 $n-i+1$ 的。

根据这个限制，我们可以得到一个很朴素的转移方程：
$$
f_{i,j} =\sum_k\dbinom{j}{k}f_{i+1,j-k}
$$
解释一下，这里的  $f_{i,j}$ 表示的是第 $i$ 个位置，$j$ 表示这个位置后面有 $j$ 个人。

那么我们对于上一个状态，无非就是将上一个状态中有 $j-k$ 个人的情况，然后从我要选的 $j$ 个人里面抽取 $k$ 个人出来站到第 $i$ 个位置上，那么方案就很显然了。

对于限制的情况，我们只用考虑第 $i$ 位之后已经确定的位置，那么就是说我们可以站在第 $i$ 个位置的人就会减少，所以 $j$ 的上界就是 $n-s_i-i+1$。

然后由于模数一直在变化，所以要用递推式解出组合数。
$$
\dbinom nm=\dbinom {n-1}m+\dbinom {n-1}{m-1}
$$
所以最后的答案就是 $f_{1,n-m}$。

做完了，时间复杂度 $O(n^3)$，可以通过本题。

---

## 作者：dAniel_lele (赞：0)

## Solution

实际难度绿~蓝？个人感觉没有紫的难度。

首先，我们先将已经排好的人所在的位置的 $num$ 值增加 $1$。

考虑 $dp_{i,j}$ 表示**从后往前**看到第 $i$ 个人，已经放置了 $j$ 个已经排好序以外的人。当我们扫到每一个位置时，将原来设置为 $0$ 的 $maxv$ 增加 $1$，并减去当前位置的 $num$ 值。若这个值小于 $0$，则说明没有满足要求的方案，直接输出 $0$。否则，尝试转移。考虑将 $k$ 个人排在这位，则 $dp_{i,j}=\sum_{k=0}^jdp_{i+1,j-k}\times C_{n-m-j+k}^k$。直接递推即可，复杂度 $O(Tn^3)$。这个数取最大时等于 $2.7\times10^8$，在 $3.0s$ 的时间限制下可以通过，事实上，开不开 $O2$ 最多用时也就 $500ms$ 左右。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int f[605][605],dp[305][305];
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,m,M;
		cin>>n>>m>>M;
		f[0][0]=1;
		for(int i=1;i<=600;i++){
			f[i][0]=1;
			for(int j=1;j<=i;j++){
				f[i][j]=(f[i-1][j]+f[i-1][j-1])%M;
			}
		}
		int num[n+1];
		for(int i=1;i<=n;i++) num[i]=0;
		for(int i=1;i<=m;i++){
			int p,q;
			cin>>p>>q;
			num[q]++;
		}
		memset(dp,0,sizeof(dp));
		dp[n+1][0]=1;
		int k=n-m,mmax=0,ok=1;
		for(int i=n;i>=1;i--){
			mmax++;
			mmax-=num[i];
			if(mmax<0){
				ok=0;
				break;
			}
			for(int j=0;j<=mmax;j++){
				for(int kk=0;kk<=j;kk++){
					dp[i][j]=(dp[i+1][j-kk]*f[k-(j-kk)][kk]%M+dp[i][j])%M;
				}
			}
		}
		if(ok) cout<<"YES "<<dp[1][k]<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
} 
```

---

## 作者：LCGUO (赞：0)

写在题解之前：感谢 $\texttt{rfy}$ 大佬的讲解。

---

我们考虑一个合法的方案满足的条件，即对于任意一个编号 $i$ 的数，都需要保证编号小于等于 $i$ 的人数大于等于 $i$。

~~反正法：反正它是对的。~~

反证法：假设编号小于等于 $i$ 的人数小于 $i$。  
那么，编号大于 $i$ 的人数就大于 $n-i$ 后面的人数就超出限制，所以不合法。

所以我们用 $s_i$ 来表示编号小于等于 $i$ 的人数，如果不合法则直接输出 NO。

同时，用 $num_i$ 来记录编号为 $i$ 位上有几个人。

考虑用 dp 来进行状态转移。

设 $f(i,j)$ 表示有 $j$ 个人的编号小于等于 $i$ 的情况。

我们设编号确定为 $i$ 的有 $k$ 人，所以编号小于 $i$ 的也就有 $j-k$ 个人，而且第 $i$ 位要从非限制的人中选 $k-num_i$ 位，就可以得到：

$f(i,j)=f(i,j)+f(i-1,j-k) \times C(s_i-j+k-num_i,k-num_i)$

最后的答案就是 $f(n,n)$。

$p.s.$ YES 和 NO 一定要大写QAQ。

---

代码如下：

```cpp
#include<bits/stdc++.h>
#define rint register int
using namespace std;
inline int read(){
    int s=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=0;c=getchar();}
    while(c>='0'&&c<='9')s=(s<<1)+(s<<3)+c-48,c=getchar();
    return f?s:-s;
}
int n,m,Mod,f[310][310],C[310][310];
int num[310],s[310];
void pre_work(){	
    C[0][0]=C[1][0]=C[1][1]=1;
    for(rint i=2;i<=n;i++){
        C[i][0]=1;
        for(rint j=1;j<=n;j++)
            C[i][j]=1ll*(C[i-1][j]+C[i-1][j-1])%Mod;
    }
}
int main(){
    int T=read();
    while(T--){
        memset(num,0,sizeof num);
        memset(s,0,sizeof s);
        memset(f,0,sizeof f);
        n=read(); m=read(); Mod=read();
        pre_work();
        for(rint i=1;i<=m;++i) read(),num[read()]++;
        s[0]=n-m;
        bool flag(1);
        for(rint i=1;i<=n;++i){
            s[i]=s[i-1]+num[i];
            if(s[i]<i){
                flag=0; break;
            }
        }
        if(!flag){
            printf("NO\n");
            continue;
        }
        f[0][0]=1;
        for(rint i=1;i<=n;++i)
            for(rint j=max(i,num[i]);j<=s[i];++j)
                for(rint k=num[i];k<=j-i+1;++k)
                    f[i][j]=1ll*(f[i][j]+1ll*f[i-1][j-k]*C[s[i]-num[i]-j+k][k-num[i]]%Mod)%Mod;
        printf("YES %d\n",f[n][n]);
    }
    return 0;
}

```

---


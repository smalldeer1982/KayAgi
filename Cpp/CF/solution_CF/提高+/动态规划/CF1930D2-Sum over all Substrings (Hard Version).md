# Sum over all Substrings (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is the constraint on $ t $ and $ n $ . You can make hacks only if both versions of the problem are solved.

For a binary $ ^\dagger $ pattern $ p $ and a binary string $ q $ , both of length $ m $ , $ q $ is called $ p $ -good if for every $ i $ ( $ 1 \leq i \leq m $ ), there exist indices $ l $ and $ r $ such that:

- $ 1 \leq l \leq i \leq r \leq m $ , and
- $ p_i $ is a mode $ ^\ddagger $ of the string $ q_l q_{l+1} \ldots q_{r} $ .

For a pattern $ p $ , let $ f(p) $ be the minimum possible number of $ \mathtt{1} $ s in a $ p $ -good binary string (of the same length as the pattern).

You are given a binary string $ s $ of size $ n $ . Find $ $$$\sum_{i=1}^{n} \sum_{j=i}^{n} f(s_i s_{i+1} \ldots s_j). $ $  In other words, you need to sum the values of  $ f $  over all  $ \\frac{n(n+1)}{2} $  substrings of  $ s $ .</p><p> $ ^\\dagger $  A binary <span class="tex-font-style-it">pattern</span> is a string that only consists of characters  $ \\mathtt{0} $  and  $ \\mathtt{1} $ .</p><p> $ ^\\ddagger $  Character  $ c $  is a mode of string  $ t $  of length  $ m $  if the number of occurrences of  $ c $  in  $ t $  is at least  $ \\lceil \\frac{m}{2} \\rceil $ . For example,  $ \\mathtt{0} $  is a mode of  $ \\mathtt{010} $ ,  $ \\mathtt{1} $  is not a mode of  $ \\mathtt{010} $ , and both  $ \\mathtt{0} $  and  $ \\mathtt{1} $  are modes of  $ \\mathtt{011010}$$$.

## 说明/提示

In the first test case, the only $ \mathtt{1} $ -good string is $ \mathtt{1} $ . Thus, $ f(\mathtt{1})=1 $ .

In the second test case, $ f(\mathtt{10})=1 $ because $ \mathtt{01} $ is $ \mathtt{10} $ -good, and $ \mathtt{00} $ is not $ \mathtt{10} $ -good. Thus, the answer is $ f(\mathtt{1})+f(\mathtt{10})+f(\mathtt{0}) = 1 + 1 + 0 = 2 $ .

In the third test case, $ f $ equals to $ 0 $ for all $ 1 \leq i \leq j \leq 5 $ . Thus, the answer is $ 0 $ .

## 样例 #1

### 输入

```
4
1
1
2
10
5
00000
20
11110110000000111111```

### 输出

```
1
2
0
346```

# 题解

## 作者：Gold14526 (赞：5)

$\rm Problem(Hard\ Version):$[Sum over all Substrings](https://www.luogu.com.cn/problem/CF1930D2)

### 题意

对于长度均为 $m$ 的 $01$ 串 $p,q$，称 $q$ 是 $p$-good 的当且仅当对于每一个 $i\in[1,m]$，在 $q$ 中有一个区间 $[l,r]$ 满足 $l\le i\le r$ 且 $p_i$ 是 $q_lq_{l+1}q_{l+2}\dots q_r$ 中的众数（这里众数指区间中出现次数**不少于**一半的数）。

给定一个长度为 $n$ 的 $01$ 串 $s$，称 $f(p)$ 为 $p$-good 序列中最少的 $1$ 的数量，求：

$$\sum\limits_{1\le l\le n}\sum\limits_{l\le r\le n}f(s_ls_{l+1}s_{l+2}\dots s_r)$$

$\text{Easy Version:}1\le n\le 100$。

$\text{Hard Version:}1\le n\le 10^6$。

### 做法

#### Easy Version

反过来想，对于一个 $q$ 序列，$p$ 序列有哪些地方可以填 $1$。

对于 $q$ 序列里一个全是 $1$ 的区间 $[l,r]$，设 $len=r-l+1$，那么在 $p$ 的 $[l-len,r+len]$ 这个区间里都可以填 $1$。

如果在 $[l-len,l-1]$ 或是 $[r+1,r+len]$ 中还有零散的 $1$ 呢？

不如把它们都拼到 $[l,r]$ 旁边，例如 $[r+1,r+len]$ 中的 $1$，拼到 $r$ 的右侧的话，在 $[l,r]$ 右边能放的 $1$ 都还能放，左边还能多放几个，$[l-len,l-1]$ 中的也是同理。

于是我们发现一个长度为 $len$ 的区间若是都填了 $1$，那么 $p$ 中就有一个长度为 $3len$ 的区间都可以填 $1$。

于是，在 $q$ 中填 $1$ 个 $1$，可以让连续三个 $p$ 中的位置都能填 $1$。

考虑 $dp$，设 $dp_i$ 为在 $q$ 的前 $i$ 位中至少要几个 $1$。

如果第 $i$ 位为 $0$，就不需要额外再填 $1$ 了，也就是 $dp_i=dp_{i-1}$。

否则的话，填一个 $1$ 来保证三个位置，即 $dp_i=dp_{i-3}+1$。

于是，我们可以求出每一个前缀的答案，也就是 $\sum\limits_{1\le r\le n}f(s_1s_2s_3\dots s_r)$。

对于 $1\le l\le n$ 的每一个 $l$ 都求出 $[l,n]$ 每一个前缀的答案，即为：

$$\sum\limits_{1\le l\le n}\sum\limits_{l\le r\le n}f(s_ls_{l+1}s_{l+2}\dots s_r)$$

也就是答案。

时间复杂度 $O(n^2)$。

#### Hard Version

这里提供一个比较笨的做法。

发现转移可以写成矩阵乘形式，即当 $s_i=0$ 时，有：

$$\begin{bmatrix}dp_{i-3} & dp_{i-2} & dp_{i-1} & 1\end{bmatrix}\begin{bmatrix}0 & 0 & 0 & 0\\ 1 & 0 & 0 & 0\\ 0 & 1 & 1 & 0 \\ 0 & 0 & 0 & 1\end{bmatrix}=\begin{bmatrix}dp_{i-2} & dp_{i-1} & dp_i & 1\end{bmatrix}$$

当 $s_i=1$ 时，有：

$$\begin{bmatrix}dp_{i-3} & dp_{i-2} & dp_{i-1} & 1\end{bmatrix}\begin{bmatrix}0 & 0 & 1 & 0\\ 1 & 0 & 0 & 0\\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 1\end{bmatrix}=\begin{bmatrix}dp_{i-2} & dp_{i-1} & dp_i & 1\end{bmatrix}$$

考虑把前缀和 $sum$ 也加进去。

当 $s_i=0$ 时：

$$\begin{bmatrix}dp_{i-3} & dp_{i-2} & dp_{i-1} & sum_{i-1} & 1\end{bmatrix}\begin{bmatrix}0 & 0 & 0 & 0 &0\\ 1 & 0 & 0 & 0 & 0 \\ 0 & 1 & 1 & 1 & 0 \\ 0 & 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 0 & 1\end{bmatrix}=\begin{bmatrix}dp_{i-2} & dp_{i-1} & dp_i & sum_i & 1\end{bmatrix}$$

当 $s_i=1$ 时：

$$\begin{bmatrix}dp_{i-3} & dp_{i-2} & dp_{i-1} & sum_{i-1} & 1\end{bmatrix}\begin{bmatrix}0 & 0 & 1 & 1 &0\\ 1 & 0 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 & 0 \\ 0 & 0 & 0 & 1 & 0 \\ 0 & 0 & 1 & 1 & 1\end{bmatrix}=\begin{bmatrix}dp_{i-2} & dp_{i-1} & dp_i & sum_i & 1\end{bmatrix}$$

它能快速地求出一段前缀的答案，于是只需要求出每一段后缀的乘积即可，时间复杂度 $O(\xi^3n)$，其中 $\xi$ 为矩阵边长，本做法中 $\xi=5$。

### 代码

```cpp
#include<bits/stdc++.h>
#define cint const int
#define iint inline int
#define ll long long
#define cll const long long
#define ill inline long long
using namespace std;
iint read()
{
	int num=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+(ch-'0');
		ch=getchar();
	}
	return num;
}
struct matrix{
	short n,m;
	ll a[5][5];
}emp,f,dp[2],mul;
void init()
{
	emp.n=emp.m=f.m=dp[0].n=dp[0].m=dp[1].n=dp[1].m=5;
	f.n=1;
	for(short i=0;i<5;++i)
	{
		for(short j=0;j<5;++j)
		{
			emp.a[i][j]=f.a[i][j]=dp[0].a[i][j]=dp[1].a[i][j]=0;
		}
	}
	f.a[0][4]=1;
	for(short i=0;i<5;++i)
	{
		emp.a[i][i]=1;
	}
	dp[0].a[1][0]=dp[0].a[2][1]=dp[0].a[2][2]=dp[0].a[2][3]=dp[0].a[3][3]=dp[0].a[4][4]=1;
	dp[1].a[1][0]=dp[1].a[2][1]=dp[1].a[0][2]=dp[1].a[0][3]=dp[1].a[3][3]=dp[1].a[4][2]=dp[1].a[4][3]=dp[1].a[4][4]=1;
	mul=emp;
}
matrix operator*(matrix x,matrix y)
{
	matrix z;
	z.n=x.n;
	z.m=y.m;
	for(short i=0;i<z.n;++i)
	{
		for(short j=0;j<z.m;++j)
		{
			z.a[i][j]=0;
			for(short k=0;k<x.m;++k)
			{
				z.a[i][j]+=x.a[i][k]*y.a[k][j];
			}
		}
	}
	return z;
}
int n;
bool a[1000001];
ll ans;
void solve()
{
	init();
	n=read();
	char ch;
	cin>>ch;
	ans=0;
	a[1]=ch-'0';
	for(int i=2;i<=n;++i)
	{
		a[i]=getchar()-'0';
	}
	for(int i=n;i>=1;--i)
	{
		mul=dp[a[i]]*mul;
		ans+=(f*mul).a[0][3];
	}
	printf("%lld\n",ans);
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int T=read();
	while(T--)solve();
	return 0;
}
```

---

## 作者：selcouth (赞：5)

### CF1930D2 Sum over all Substrings (Hard Version)

#### 题目大意

有两个 01 串 $p$ 和 $q$，$p_i$ 为 $q$ 在区间 $[l, r]$ 的区间众数，并且满足 $l \le i \le r$。使用 $|q|$ 表示 01 串 $q$ 中 $1$ 的个数，我们需要求出给出的 01 串 $s$ 中每个字串对应的 $1$ 个数最小的 $q$ 的 $1$ 个数之和。  



#### 简单版思路

简单版：[Sum over all Substrings (Easy Version)](https://www.luogu.com.cn/problem/CF1930D1)

简单版和本题之间的差别只在于数据大小，对于小数据，我们可以使用贪心的思路解决。

先考虑以下的情况：当 $p$ 为 $111$ 时，我们可以发现 $|q|$ 最小的 $q$ 为 $010$；当 $p$ 为 $100$ 时，我们也可以让 $q$ 为 $010$。$p_1$ 对应区间 $q[1, 2]$，$p_2$ 对应区间 $[2, 3]$ 或 $[1,2]$，$p_3$ 对应区间 $[2, 3]$。

因此我们不难发现，当 $p_i$ 为 $1$ 时，我们可以跳过考虑其后 $2$ 位的值，因为只需要让 $q_{i+1}=1$ 可以同时满足 $p_i$，$p_{i+1}$，$p_{i+2}$。

这样我们就可以暴力枚举子串，执行贪心策略，时间复杂度为 $O(n^2)$：

```cpp
cin >> n >> s;
int ans = 0;
s = ' ' + s;
for(int i = 1; i<=n; i++)
{
    for(int j = i; j<=n; j++)
    {
        string p = s.substr(i, j);
        int st = 0;
        p = ' ' + p;
        for(int k = 1; k<=j-i+1; k++)
        {
            if(p[k] == '1')
            {
                ans++;
                k += 2;
            }
        }
    }
}

cout << ans << '\n';
```



#### 本题思路

有了简单版的基础，我们就不难得出本题的做法了。

考虑 dp，定义 $f_i$ 表示所有以 $i$ 为结尾的子串对答案的贡献。由于以 $i$ 为结尾的子串个数共有 $i$ 个，若 $p_i$ 为 $1$，则对答案的贡献就为 $i$，并且我们可以直接跳过考虑前两个（只需要让 $q_{i-1}=1$），因此得出状态转移方程：
$$
f_i = \begin{cases}
f_{i-3} + i \quad (s_i = 1) \\
f_{i-1} \quad (s_i = 0)
\end{cases}
$$
最后答案就是 $\sum_{i=1}^n f_i$，时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6+10;
int t, n, f[maxn];
// f[i] 表示以 i 为结尾的区间中 g 的和
string s;

signed main()
{
    cin >> t;
    while(t--)
    {
        cin >> n >> s;
        int ans = 0;
        s = ' ' + s;
        
        f[0] = 0;
        for(int i = 1; i<=n; i++)
        {
            if(s[i] == '1')
            {
                f[i] = f[max(i-3, 0ll)]+i;
                // 当前为 1，则对整个答案的贡献为
                // 以 i 为右端点的子区间数量，即 i
            }
            else f[i] = f[i-1];
        }

        for(int i = 1; i<=n; i++)
            ans += f[i];
        
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：IGA_Indigo (赞：1)

建议先看一下我 [Sum over all Substrings (Easy Version)](https://www.luogu.com.cn/problem/CF1930D1) 的贪心做法了解一下题意。

这里面有一个结论，就是每一个 $q$ 中的 $1$ 可以换掉 $p$ 中相邻的三个 $1$，详见[Easy Version 的题解](https://www.luogu.com.cn/article/x5jsmj1g)。
## 题目大意
定义两个 01 串 $p$ 和 $q$，对于所有的 $p_i$，存在 $q$ 中有一个区间使得 $p_i$ 是这个区间的众数，这个 $q$ 被称为好的串，求所有 $p$ 的子串中 $1$ 最少的 $q$ 里的 $1$ 的个数之和。
## 大体思路
考虑 DP，显然有四个状态，是距离上一个 $1$ 的距离，距离 $0$、$1$、$2$ 和 $\ge 3$。

状态也非常好转移，在我们从 $1$ 至 $n$ 遍历的时候，每一个状态都往前推一个。

$gx$ 表示贡献，$gs$ 表示距离‘$1$’的当前合法距离的个数。

遇到 $1$ 的时候，距离为 $0$ 的离 $1$ 距离个数和贡献都要清零，距离为 $3$ 的（也就是没有被换掉的 $1$）上一个 $1$ 距离个数和贡献变成距离为 $0$ 刚刚的个数和贡献。

每次答案等于四个状态的贡献加起来即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long gs[5],gx[5];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		string s;
		cin>>s;
		s=' '+s;
		long long ans=0;
		gs[0]=1;//初始化一下个数 
		for(int i=1;i<=n;i++){
			gs[0]+=gs[1];
			gs[1]=gs[2];
			gs[2]=gs[3];//往后走一个，三个状态都要往前推一个
			gs[3]=0;//大于等于三的属实是没影响了直接清零即可
			gx[0]+=gx[1];//贡献也一样转移 
			gx[1]=gx[2];
			gx[2]=gx[3];
			gx[3]=0;
			if(s[i]=='1'){//如果遇到一个
				gs[3]=gs[0];//处理一下大于等于三和0的状态 
				gx[3]=gx[0]+gs[0];
				gx[0]=0;//当前的位置就为1，所以贡献和个数清零 
				gs[0]=0;
			}
			ans+=gx[0]+gx[1]+gx[2]+gx[3];
			gs[0]++; 
		}
		for(int i=0;i<=4;i++){
			gs[i]=0;
			gx[i]=0;//数组清零 
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：phigy (赞：0)

## 前言


- ~~可以考虑套用 CF1943F 的做法~~。
- 本文 D2 做法可能会有些价值。

## D1

注意到 $k$ 个连续的 $1$ 可以覆盖 $3k$ 个位置。

但是实际上分开放 $k$ 个 $1$ 肯定不比连续放 $k$ 个 $1$ 劣。

因此从前往后贪心的遇到未被覆盖的 $1$ 的位置，就在下一个位置放 $1$ 是正确的。

记录当前距离上一个放的 $1$，超过 $3$ 需要 $1$ 就在下一个位置放一个 $1$，实际产生的效果就是需要我们重置维护的距离上一个 $1$ 的距离即可。

```cpp
#include <bits/stdc++.h>
 
#define REN (1000000)
#define MAXN (REN+5)
 
using namespace std;
 
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(!isdigit(c)) {if(c=='-') {f=-1;} c=getchar();}
    while(isdigit(c))  {x=x*10+c-'0';      c=getchar();}
    return x*f;
}
void write(int x)
{
    if(x<0) {putchar('-');x=-x;}
    if(x>9) {write(x/10);}
    putchar(x%10+'0');
}
 
int T;
int n;
int a[MAXN];
int pre[MAXN],suf[MAXN];
signed main()
{
    int i,j,k;
    T=read();
    while(T--)
    {
        n=read();
        for(i=1;i<=n;i++) {char c;cin>>c;a[i]=c-'0';}
        long long ans=0;    
        for(i=1;i<=n;i++)
        {
            int res=0,lst=-1;
            for(j=i;j<=n;j++)
            {
                lst--;
                if(a[j]&&lst<0) {lst=2;res++;}
                ans+=res;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```

## D2

注意到我们记录的距离实际有效的只有四种 $0,1,2,\ge 3$。

因此我们同时记录所有开头到当前位置每种有效距离的数量和贡献即可。

也就是当前位置没往后一个，四种距离的变化就后移一下，并添加一个新的开头，实际效果就是 $\ge 3$ 的数量加一。

当我们遇到一个 $1$ 我们就把未被覆盖的前缀情况也就是距离 $\ge 3$ 的数量和贡献导到 $0$。

```cpp
#include <bits/stdc++.h>

#define REN (1000000)
#define MAXN (REN+5)
#define int long long

using namespace std;

inline int read()
{
    int x=0,f=1;char c=getchar();
    while(!isdigit(c)) {if(c=='-') {f=-1;} c=getchar();}
    while(isdigit(c))  {x=x*10+c-'0';      c=getchar();}
    return x*f;
}
void write(int x)
{
    if(x<0) {putchar('-');x=-x;}
    if(x>9) {write(x/10);}
    putchar(x%10+'0');
}

int T;
int n;
int a[MAXN];
int lst[4];
int num[4];
signed main()
{
    int i,j,k;
    T=read();
    while(T--)
    {
        n=read();
        for(i=1;i<=n;i++) {char c;cin>>c;a[i]=c-'0';}
        int ans=0;    
        fill(lst,lst+4,0);fill(num,num+4,0);
        lst[0]=1;
        for(i=1;i<=n;i++)
        {
            lst[0]+=lst[1];lst[1]=lst[2];lst[2]=lst[3];lst[3]=0;
            num[0]+=num[1];num[1]=num[2];num[2]=num[3];num[3]=0;
            if(a[i]) {lst[3]=lst[0];num[3]=num[0]+lst[0];num[0]=lst[0]=0;}
            ans+=num[0]+num[1]+num[2]+num[3];
            lst[0]++;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```

## 后话

- 用矩阵的做法也挺好，可以参考其它题解。
- 官方做法和本文做法本质相同，但是我觉得他的推导出发点不易找到。

---


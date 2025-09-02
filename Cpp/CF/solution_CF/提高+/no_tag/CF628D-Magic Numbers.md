# Magic Numbers

## 题目描述

Consider the decimal presentation of an integer. Let's call a number d-magic if digit $ d $ appears in decimal presentation of the number on even positions and nowhere else.

For example, the numbers $ 1727374 $ , $ 17 $ , $ 1 $ are 7-magic but $ 77 $ , $ 7 $ , $ 123 $ , $ 34 $ , $ 71 $ are not 7-magic. On the other hand the number $ 7 $ is 0-magic, $ 123 $ is 2-magic, $ 34 $ is 4-magic and $ 71 $ is 1-magic.

Find the number of d-magic numbers in the segment $ [a,b] $ that are multiple of $ m $ . Because the answer can be very huge you should only find its value modulo $ 10^{9}+7 $ (so you should find the remainder after dividing by $ 10^{9}+7 $ ).

## 说明/提示

The numbers from the answer of the first example are $ 16 $ , $ 26 $ , $ 36 $ , $ 46 $ , $ 56 $ , $ 76 $ , $ 86 $ and $ 96 $ .

The numbers from the answer of the second example are $ 2 $ , $ 4 $ , $ 6 $ and $ 8 $ .

The numbers from the answer of the third example are $ 1767 $ , $ 2717 $ , $ 5757 $ , $ 6707 $ , $ 8797 $ and $ 9747 $ .

## 样例 #1

### 输入

```
2 6
10
99
```

### 输出

```
8
```

## 样例 #2

### 输入

```
2 0
1
9
```

### 输出

```
4
```

## 样例 #3

### 输入

```
19 7
1000
9999
```

### 输出

```
6
```

# 题解

## 作者：_Atyou (赞：12)

## 算法： 数位DP

------------

### 补充一点翻译没讲清楚的事：

1. 位数从左往右数
2. 答案对1000000007取模
3. 是指只有偶数项为d， 奇数项不能为d

剩下的就是很套路的数位DP

f[i][j]表示第i位 前i位的数对m取模为j的答案个数

介于l比较大，不建议将 l-1 后求[1, r] - [1, l-1]

可以将 [1, r] - [1, l] 求出来后单独判断l是否满足条件，满足条件的话答案+1即可


代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define reg register
#define ll long long
const int N = 2000 + 5, M = 1e9 + 7;

ll f[N][N], m, d, ans, bit[N], len;
char l[N], r[N];

ll dfs(int pos, ll sum, bool flag) {
    if (pos==-1) return sum==0;
    if (!flag && f[pos][sum]!=-1) return f[pos][sum];
    ll res=0;
    for (reg int i=0, up=flag?bit[pos]:9; i<=up; ++i) {
           if ((len-pos)&1) { if (i==d) continue; }
           else { if (i!=d) continue; }
        (res+=dfs(pos-1, (sum*10+i)%m, flag&&(i==up)))%=M;
    }
    return flag?res:f[pos][sum]=res;
}

ll calc(char *x) {
    len=strlen(x);
    for (reg int i=0; i<len; ++i) bit[len-i-1]=x[i]-'0';
    return dfs(len-1, 0, 1);
}

int check() { //单独处理l
    ll sum=0; len=strlen(l);
    for (reg int i=0; i<len; ++i) {
        int x=l[i]-'0';
        if ((i+1)&1) { if (x==d) return 0; }
        else { if (x!=d) return 0; }
        (sum=sum*10+x)%=m;
    }
    return sum==0;
}

int main() {
    memset(f, -1, sizeof(f));
    scanf("%lld%lld", &m, &d);
    scanf("%s", l);
    scanf("%s", r);
    ans=calc(r)-calc(l);
    ans+=check();
    printf("%lld\n", (ans+M)%M);
    return 0;
}

```



---

## 作者：Ginger_he (赞：10)

# 题目描述
给定 $m,d,l,r$，求符合以下条件的数 $x$ 的个数：  
- $l\le x\le r$  
- $x$ 的偶数位是 $d$，奇数位不是 $d$
- $m|x$  

答案对 $10^9+7$ 取模。
# 题解
比较套路的**数位 dp**，我们传三个参数 $k,x,p$ 进入 dfs，分别表示枚举到第 $k$ 位，当前数模 $m$ 的余数，以及这一位填的数有没有限制，用 $f$ 数组**记忆化**即可。  
## 注意
- 偶数位填的 $d$ 不能超过当前位能填的最大值。
- $a$ 数组是从高位往低位存的，dfs 也要从高位往低位搜，这与平常的数位 dp 不太一样。
- 众所周知，数位 dp 运用了**前缀和**（也可以说是差分）的思想，即 $\mathrm{cnt}(l,r)=\mathrm{cnt}(1,r)-\mathrm{cnt}(1,l-1)$。但对于这道题，我们是用数组记录 $l$，在减一的过程中可能出现退位，还要打一遍高精度减法，比较麻烦（增加码量）。因此，这道题最好的解法是先算出 $\mathrm{cnt}(1,r)-\mathrm{cnt}(1,l)$，再单独判断 $l$ 是否符合条件。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=1e9+7;
int m,d,len,a[2005];
ll f[2005][2005];
char l[2005],r[2005];
ll dfs(int k,int x,int p)
{
    if(k>len)
        return x?0:1;//当前数要整除m 
    if(!p&&f[k][x]!=-1)
        return f[k][x];
    int y=p?a[k]:9;//当前位可取的最大值 
    ll res=0;
    if(k&1)
    {
        for(int i=0;i<=y;i++)
        {
            if(i==d)
                continue;
            res=(res+dfs(k+1,(x*10+i)%m,p&&(i==y)))%mod; 
        }
    }//奇数位 
    else
    {
        if(d<=y)
            res=(res+dfs(k+1,(x*10+d)%m,p&&(d==y)))%mod;
    }//偶数位 
    if(!p)
        f[k][x]=res;//如果没有限制就记忆化 
    return res;
}
ll divide(char *s)
{
    len=strlen(s+1);
    for(int i=1;i<=len;i++)
        a[i]=s[i]-'0';
    return dfs(1,0,1);
}
bool check(char *s)
{
    len=strlen(s+1);
    int x=0;
    for(int i=1;i<=len;i++)
    {
        int y=s[i]-'0';
        x=(x*10+y)%m;
        if(i&1)
        {
            if(y==d)
                return false;
        }
        else
        {
            if(y!=d)
                return false;
        }
    }
    return !x;
}//单独判断l 
int main()
{
	memset(f,-1,sizeof(f));//初始化一遍即可，memset效率很低
    scanf("%d%d%s%s",&m,&d,l+1,r+1);
    printf("%lld\n",(divide(r)-divide(l)+check(l)+mod)%mod);
    return 0;
}
```
# 后记
这题的细节还是挺多的，特别感谢 [@xqh07](https://www.luogu.com.cn/user/333785) 为我提供了那么多需要注意的地方。

---

## 作者：Link_Cut_Y (赞：6)

很典的一道数位 dp 题，但是硬给我卡了半个钟头。可能是题解里唯一的非记搜。

好的好的，我以后写记搜，不污染大家的眼睛了。

------------

一看到整除很自然可以想到维护余数。

设 $f_{i, j, 0/1. 0/1}$ 表示在第 $i$ 位，已经填的数 $\bmod\  m = k$，前面是否卡上界，前面是否卡下界。

转移的时候枚举下一位填什么（如果下一位是偶数为就默认填 $d$），分类讨论转移即可。

代码如下：

```cpp
#include <iostream>
#include <cstring>
#define int long long
		
using namespace std;
		
const int N = 100010;
const int mod = 1e9 + 7;
int n, m, d;
char l[N], r[N];
int f[2010][2010][2][2];
signed main() {
	scanf("%lld%lld", &m, &d);
	scanf("%s", l + 1);
	scanf("%s", r + 1);
	n = strlen(l + 1);
	
	for (int i = l[1] - '0'; i <= r[1] - '0'; i ++ ) if (i != d)
		f[1][i % m][i == r[1] - '0'][i == l[1] - '0'] ++ ;
	for (int i = 1; i < n; i ++ ) {
		if (i + 1 & 1) {
			for (int j = 0; j <= 9; j ++ ) {
				if (j == d) continue;
				for (int k = 0; k < m; k ++ ) {	
					int w = (k * 10 + j) % m;
					(f[i + 1][w][0][0] += f[i][k][0][0]) %= mod;
					if (j < r[i + 1] - '0') 
						(f[i + 1][w][0][0] += f[i][k][1][0]) %= mod;
					if (j > l[i + 1] - '0')
						(f[i + 1][w][0][0] += f[i][k][0][1]) %= mod;
					if (j < r[i + 1] - '0' and j > l[i + 1] - '0')
						(f[i + 1][w][0][0] += f[i][k][1][1]) %= mod;
					if (j == r[i + 1] - '0')
						(f[i + 1][w][1][0] += f[i][k][1][0]) %= mod;
					if (j == r[i + 1] - '0' and j > l[i + 1] - '0')
						(f[i + 1][w][1][0] += f[i][k][1][1]) %= mod;
					if (j == l[i + 1] - '0')
						(f[i + 1][w][0][1] += f[i][k][0][1]) %= mod;
					if (j == l[i + 1] - '0' and j < r[i + 1] - '0')
						(f[i + 1][w][0][1] += f[i][k][1][1]) %= mod;
					if (j == l[i + 1] - '0' and j == r[i + 1] - '0')
						(f[i + 1][w][1][1] += f[i][k][1][1]) %= mod;
				}
			}
		}
		else {
			for (int k = 0; k < m; k ++ ) {
				int w = (k * 10 + d) % m;
				(f[i + 1][w][0][0] += f[i][k][0][0]) %= mod;
				if (d < r[i + 1] - '0')
					(f[i + 1][w][0][0] += f[i][k][1][0]) %= mod;
				if (d > l[i + 1] - '0')
					(f[i + 1][w][0][0] += f[i][k][0][1]) %= mod;
				if (d < r[i + 1] - '0' and d > l[i + 1] - '0')
					(f[i + 1][w][0][0] += f[i][k][1][1]) %= mod;
				if (d == r[i + 1] - '0')
					(f[i + 1][w][1][0] += f[i][k][1][0]) %= mod;
				if (d == r[i + 1] - '0' and d > l[i + 1] - '0')
					(f[i + 1][w][1][0] += f[i][k][1][1]) %= mod;
				if (d == l[i + 1] - '0')
					(f[i + 1][w][0][1] += f[i][k][0][1]) %= mod;
				if (d == l[i + 1] - '0' and d < r[i + 1] - '0')
					(f[i + 1][w][0][1] += f[i][k][1][1]) %= mod;
				if (d == l[i + 1] - '0' and d == r[i + 1] - '0')
					(f[i + 1][w][1][1] += f[i][k][1][1]) %= mod;
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < 2; i ++ )
		for (int j = 0; j < 2; j ++ )
			(ans += f[n][0][i][j]) %= mod;
	printf("%lld\n", ans);
	return 0;
}
```

~~好了好了别喷了，我知道我写的丑。~~

---

## 作者：He_Ren (赞：5)

非常明显的数位dp

因为之前并没有写过数位dp（只是知道这个算法），所以比赛的时候就没有写出来

写的时候需要注意的点：

- 位数从左往右算
- _所有_ 偶数位都是$d$，_所有_ 奇数位都不是$d$
- 要判前导零（代码里并没有写进状态里而是直接判断的）

我花时间比较久的一个代码错误，是状态里的```state```变量在更新状态之前就改变了

就是，一开始使用

```cpp
sta = (sta*10)%m;
```

后来又直接使用```sta```：

```cpp
if(!lim) dp[pos][sta]=tmp;
```

导致出错，调了比较长时间才发现

**使用变量之前，检查该变量是否被修改过**

此外，要区分```%m```和```%mod```，在这里也出过错

```cpp
#include<cstdio>
#include<cstring>
typedef long long ll;
const int MAXN = 2e3 + 5;
const int MAXM = 2e3 + 5;
const int mod = 1e9 + 7;

int n,m,d;
char a[MAXN],b[MAXN];

ll pw[MAXN];
ll dp[MAXN][MAXM];

ll gao(char s[],int pos,int sta,bool lim)
{
	if(pos>n) return !sta;
	if(!lim && dp[pos][sta]!=-1) return dp[pos][sta];
	
	int nxt = sta*10%m, up = lim? s[pos]: 9;
	ll tmp=0;
	if((pos&1) == 0)
	{
		if(lim && d>up) return 0;
		tmp=gao(s, pos+1, (nxt+d)%m, lim&&d==up);
		if(!lim) dp[pos][sta]=tmp;
		return tmp;
	}
	for(int i=(pos==1); i<=up; ++i)
	{
		if(i==d) continue;
		tmp = (tmp+gao(s, pos+1, (nxt+i)%m, lim&&i==up))%mod;
	}
	if(!lim) dp[pos][sta]=tmp;
	return tmp;
}

int main(void)
{
	memset(dp,-1,sizeof(dp));
	
	scanf("%d%d%s%s",&m,&d,a+1,b+1);
	n=strlen(a+1);
	pw[0]=1;
	for(int i=1; i<=n; ++i) pw[i]=pw[i-1]*10%mod;
	for(int i=1; i<=n; ++i) a[i]-='0', b[i]-='0';
	
	ll ans = gao(b,1,0,1) - gao(a,1,0,1);
	//printf("a: %lld\nb: %lld\n",gao(a,1,0,1),gao(b,1,0,1));
	bool flag=1;
	int tmp=0;
	for(int i=1; i<=n; ++i)
	{
		if((i&1)==0 && a[i]!=d)
		{
			flag=0;
			break;
		}
		if((i&1) && a[i]==d)
		{
			flag=0;
			break;
		}
		tmp = (tmp*10+a[i])%m;
	}
	if(flag && !tmp) ++ans;
	if(ans<0) ans+=mod;
	else if(ans>=mod) ans%=mod;
	
	printf("%d",(int)ans);
	return 0;
}
```


---

## 作者：hsfzLZH1 (赞：5)

题目大意：如果一个数，它的从高到低的第偶数位上都是$d$，而其他位上没有$d$，则称这个数为$d-magic$数。求区间$[l,r]$内的是$d-magic$数同时是$m$的倍数的数量。（$0\le d\le 9$,$l\le r\le 10^{2000}$）

我们将求区间$[l,r]$内满足题目要求条件的数的数量的问题转化成求两个区间$[1,r][1,l-1]$内满足条件的数的数量的差，这是**数位$DP$**问题的常规套路。

考虑求区间$[1,x]$内求$d-magic$数数量的一般形式。我们定义$f[i][j][k]$为当前剩余$i$位需要规划，其中$j$表示这前$i$位取模$m$的余数，$k$表示当前规划到了第奇数还是偶数位。那么，我们可以得出状态转移方程：

$f[i-1][(j*10+now)~mod~m][1-k]+=f[i][j][k]$ 当前位填入数码$now$。

边界条件是$f[0][0][0/1]=1,f[0][not~0][0/1]=0$。

我们用$dfs$过程求出$f$数组的值。由于其中的同一值$i$，$j$，$k$均相等的情况会出现，所以用**记忆化**减少计算量。

需要注意的一点是，如果当前的位置填入的是前导$0$，判断当前位置奇偶的$k$的值不应当改变。

代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
#define int long long
const int maxn=2010;
const int mod=1000000007;
int m,d,f[maxn][maxn][2][2];
char a[maxn],b[maxn],c[maxn];
vector<int>dim;
int dfs(int x,int mode,int l,bool op,bool zero)
{
    if(!x)return mode==0?1:0;
    if(!op&&~f[x][mode][l][zero])return f[x][mode][l][zero];
    int maxx=op?dim[x]:9,ret=0;
    if((l-x+1)&1)
    {
        if(op&&dim[x]<d)return 0;
        return dfs(x-1,(mode*10+d)%m,l,op&(d==maxx),zero);
    }
    for(int i=0;i<=maxx;i++)if(i!=d)
    {
        if(zero&&i==0)ret=(ret+dfs(x-1,mode*10%m,1-l,op&(i==maxx),true))%mod;
        ret=(ret+dfs(x-1,(mode*10+i)%m,l,op&(i==maxx),false))%mod;
    }
    if(!op)f[x][mode][l][zero]=ret;
    return ret;
}
int solve(char*x)
{
    int l=strlen(x);
    dim.clear();dim.push_back(-1);
    for(int i=l-1;i>=0;i--)dim.push_back(x[i]-'0');
    return dfs(dim.size()-1,0,dim.size()&1,1,1);
}
main()
{
    memset(f,-1,sizeof f);
    scanf("%I64d%I64d%s%s",&m,&d,a,b);
    int l=strlen(a);
    for(int i=0;i<l;i++)c[i]=a[l-1-i];
    c[0]--;
    for(int i=0;i<l;i++)if(c[i]<'0')c[i+1]--,c[i]+=10;
    if(c[l]=='0')l--;
    for(int i=l;i>=0;i--)a[l-i-1]=c[i];
    printf("%I64d\n",(solve(b)-solve(a)+mod)%mod);
    return 0;
}
```

---

## 作者：xqh07 (赞：4)

# 算法：数位dp


# 题目描述：

给出 $m ,d , l ,r$ ,求满足下列条件的数 $x$ 的个数。

1.  $x\in [l,r]$；

2. 从左到右数， $x$ 偶位为 $d$ ，奇位非 $d$； 

3. $m\mid x$；

答案对 $10^9+7$ 取模。

# 思路：

使用**搜索+记忆化**，传入参数 $p,q,r$ ，

分别表示枚举到第 $p$ 位（从右往左），当前数 $\bmod$  $m$  余数 $q$ ,及填的此位是否有进位限制 $r$ 。

# 注意：

1.偶数位填 $d$ 时要检验是否超过当前最大值 $k$ ;

2.注意到数据范围，必须用**字符串**形式输入;

3.注意到我们平时数位dp是从后往前搜的，此时将字符数组存入后，必须进行**翻转**;

4.数位dp的惯常操作就是 $ans = \left  [ 1,r \right  ]  - \left  [ 1,l-1 \right  ]$ ,但用这种方法输入难以进行 $-1$ 的操作，所以在要在 $ans = \left  [ 1,r \right  ]  - \left  [ 1,l \right  ]$ 基础上单独开一函数检查 $l$ 的情况；



5.~~细节很多，心态不能崩！~~

# code：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const long long mod = 1000000007;
int m, d, a[2005], len, res1, res2;
long long f[2005][2005][2];
char s[2005];
long long dfs(int p, int q, int r)
{
	if(!p)
		return !q ? 1 : 0;
	if(f[p][q][r] != -1)
		return f[p][q][r];
	long long res = 0;
	int k = r ? a[p] : 9;
	if((len - p) & 1)
	{
		if(d > k)return 0;
		res = (res + dfs(p - 1, (q * 10 + d) % m, r && (d == k))) % mod;
		return f[p][q][r] = res % mod;
	}
	else
	{
		for(int i = 0; i <= k; i++)
		{
			if(i == d)
				continue;
			res = (res + dfs(p - 1, (q * 10 + i) % m, r && (i == k))) % mod;
		}
		return f[p][q][r] = res % mod;
	}
}
int check()
{
	int sum = 0;
	for(int i = len; i >= 1; i--)
	{
		if((len - i + 1) & 1)
		{
			if(a[i] == d)return 0;
		}
		else
		{
			if(a[i] != d)return 0;
		}
		sum = (sum * 10 + a[i]) % m;
	}
	return !sum;
}
signed main()
{
	scanf("%lld%lld", &m, &d);
	memset(f, -1, sizeof(f));
	scanf("%s", s + 1);
	len = strlen(s + 1);
	for(int i = 1; i <= len; i++)
	{
		a[i] = s[len - i + 1] - '0';
	}
	res1 = dfs(len, 0, 1);
	int cnt = check();
	memset(f, -1, sizeof(f));
	scanf("%s", s + 1);
	len = strlen(s + 1);
	for(int i = 1; i <= len; i++)
	{
		a[i] = s[len - i + 1] - '0';
	} 
	res2 = dfs(len, 0, 1);
	printf("%lld\n", (res2 - res1 + cnt + mod) % mod);
	return 0;
}
```
# 后记：
~~不要问为什么我的代码和博客与[Ginger_he](https://www.luogu.com.cn/user/379058)的为什么这么像。~~

---

## 作者：_fairytale_ (赞：2)

对于这种跟数字的构成有关的计数题，我们考虑数位 DP。

数位 DP 的实现方式主要是记忆化搜索，一般来说，传进来的参数有 $now,lead,limit$，分别表示当前搜索到第 $now$ 位，是否有前导零，是否有最大值限制。

这里着重讲一下 $limit$ 。

比如，我们要搜索 $1\sim114514$ 中有多少个满足某条件的数，当前搜索到第 $3$ 位，没有前导零，但是前面我们搜索的结果是 $11$ ，因此我们下一位只能是 $0\sim4$。但如果前面搜索的结果是 $10$ ，我们的下一位就可以是 $0\sim9$ 中的任何数。

这里还要注意一点：当存在前导零或最大值限制时，我们不能进行记忆化，这样 DP 值会偏小。上面的例子就是一个很好的解释。

这里放一个板子。
```cpp
#define ll long long
int stac[maxn],tot;
ll dp[maxn][maxn];
//注意拆数是倒着拆的，比如123，拆出来的stac[1-3]={3,2,1} 
ll dfs(int now/*当前在第now位*/,/*题目限制*/,bool lead/*前导零*/,bool limit/*当前位最大值限制*/){
	if(now>tot){
		if(/*满足条件*/)return 1;
		else return 0;
	}
	if(dp[now][/*其他条件*/]!=-1&&!limit&&!lead)return dp[now][/**/];
    ll res=0;
    int mx=(limit?stac[tot-now+1]:9);
    for(int i=0;i<=mx;++i){
    	res+=dfs(now+1,/**/,lead&&(i==0),limit&&(i==mx));
	}
	if(!lead&&!limit)dp[now][/**/]=res;
	return res;
}
ll solve(int num){
	tot=0;
	while(num){
		stac[++tot]=num%10;
		num/=10;
    }
    memset(dp,-1,sizeof(dp));
    return dfs(1,/**/,true,true);
}
ll solve(string num) {
	tot=0;
	int len=num.length();
	while(tot<len) {
		tot++;
		stac[tot]=num[len-tot]-'0';
	}
	memset(dp,-1,sizeof(dp));
	return dfs(1,/**/,true,true);
}
```
在本题中，我们只需要记录当前数模 $m$ 的余数，在奇数和偶数位分别对下一位的数字加入特判即可。

关于数位 DP 的统计答案，因为我们搜索时比较容易获取 $[1,num]$ 的答案，故而我们采取前缀和的思想，求出 $[1,r]$ 和 $[1,l-1]$ 的答案，再将它们相减。

但对于本题而言，$10^{2000}$ 的数据范围下，写高精度减法并不是明智的选择，因此我们考虑算出 $[1,r],[1,l]$ 的答案，再单独判断 $l$ 是否满足条件。

其实本题并不需要记前导零，但是~~我套板子所以写了~~。

```cpp
#include<bits/stdc++.h>
#define re register
#define ll long long
#define maxn 3010
#define mod 1000000007
using namespace std;
int m,d;
int stac[maxn],tot;
ll dp[maxn][maxn];
ll dfs(int now,int rem,bool lead,bool limit) {
	if(now>tot) {
		if(!rem){
			return 1;
        }
		else return 0;
	}
	if(dp[now][rem]!=-1&&!limit&&!lead)return dp[now][rem];
	ll res=0;
	int mx=(limit?stac[tot-now+1]:9);
	if(now&1) {
		for(int i=0; i<=mx; ++i) {
			if(i==d)continue;
			res=(res+dfs(now+1,(rem*10+i)%m,lead&&(i==0),limit&&(i==mx)))%mod;
		}
	}
	else{
		if(mx<d)return 0;
		res=dfs(now+1,(rem*10+d)%m,lead&&(d==0),limit&&(d==mx))%mod;
	}
	if(!lead&&!limit)dp[now][rem]=res;
	return res;
}
ll solve(string num) {
	tot=0;
	int len=num.length();
	while(tot<len) {
		tot++;
		stac[tot]=num[len-tot]-'0';
	}
	memset(dp,-1,sizeof(dp));
	return dfs(1,0,true,true);
}
ll chck(string s) {
    ll tmp=0;
    int len=s.length();
    for(re int i=0;i<len;++i){
    	tmp=(tmp*10+s[i]-'0')%m;
    	if(i&1){
    		if(s[i]-'0'!=d)return 0;
		}
    	else if(s[i]-'0'==d)return 0; 
	}
	if(tmp)return 0;
	return 1;
}
string l,r;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
    cin>>m>>d>>l>>r;
    cout<<((solve(r)-solve(l)+chck(l))%mod+mod)%mod;
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：2)

+ 对于限制一：设 $F(i)$ 表示 $[1,i]$ 中符合条件的数的个数，原问题可以写成 $F(r)-F(l-1)$，但是对这么大一个数进行减法是很无聊的。我们不妨设 $P(x)$ 表示判断 $x$ 是否符合条件即 $P(x)=[\text{x 符合条件}]$。这样就变成 $F(r)-F(l)+P(l)$。
+ $P(l)$ 是简单的，直接模拟就可以了。重点在于 $F(l)$ 和 $F(r)$。
+ 对于限制二：首先发现我们读进来数字就是从高到低排的，那么 dp 的时候直接看 dep 的奇偶性就可以了。 
+ 对于限制三：发现 $m$ 其实也不是很大，这个时候就考虑设 $f_{i,j}$ 表示前 $i$ 位没有限制的，满足 $x\bmod m=j$ 的 $x$ 的个数，然后经典的数位 dp 就好了。

```cpp
// LUOGU_RID: 115773805
#include <bits/stdc++.h>
using ll=long long;
#define rep(i,l,r) for(i=l;i<=r;++i)
using namespace std;
const int N=2005,p=1e9+7;
int f[N][N],rs[N];
char l[N],r[N];
int cnt,d,i,m;
inline ll dp(bool limit,int dep,int pre)
{
//	printf("ldp, %d %d %d\n",limit,dep,pre);
	if(dep>cnt)return pre%m==0;
	else if(!limit && f[dep][pre]!=-1)return f[dep][pre];
	else
	{
		int nxt=limit?rs[dep]:9,i,ret=0;
//		printf("nld, %d %d %d\n",nxt,limit,dep);
		if(dep%2==0)
			{if(d<=nxt)ret=dp(limit&&(d==nxt),dep+1,(pre*10+d)%m)%p;}
		else
			for(i=0;i<=nxt;++i)if(i!=d)
				(ret+=dp(limit&&(i==nxt),dep+1,(pre*10+i)%m))%=p;
		if(!limit)f[dep][pre]=ret;
		return ret;
	}
}
inline ll solve(char* str)
{
//	printf("str,%s\n",str+1);
	rep(i,1,cnt)rs[i]=str[i]^'0';
//	printf("%d %d rs\n",rs[1],rs[2]);
	return dp(1,1,0);
}
inline const bool check()
{int sum=0;
	rep(i,1,cnt)
	{
		sum=(sum*10+(l[i]^'0'))%m;
//		printf("%d %d\n",sum,l[i]^'0');
		if(i&1)if((l[i]^'0')==d)return false;
		else;
		else if((l[i]^'0')!=d)return false;
		else;
	}
//	printf("ok");
	return sum==0;
}
int main()
{
	memset(f,-1,sizeof f);
	scanf("%d %d %s %s",&m,&d,l+1,r+1);cnt=strlen(l+1);
//	printf("%s %s\n")
//	printf("%d %lld %lld %lld\n",cnt,solve(l),solve(r),check());
	printf("%lld",((check()+solve(r)-solve(l))%p+p)%p);
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：2)

**【题目分析】**

既然你点开了本题，那么就默认你会数位 dp。（如果不会的话参考 [P2657](https://www.luogu.com.cn/problem/P2657) 及其推荐题目。）

我们设 $f_{pos,sum,lim}$ 表示截至第 $pos$ 位，目前数字和取余 $m$ 的结果为 $sum$，有无最高位限制状态为 $lim$ 时的答案，初始化为 $-1$。每次进入搜索函数，如果该状态下 $f \ne 0$，直接返回这个值。接下来枚举每一位数字，根据题意可得到代码。但是需要注意的是，**一定要取模！** 本题不仅需要取模 $10^9+7$，还需要在计算 $sum$ 时取余 $m$
，否则就会发生越界。

由于本题是高精度整数读入，我们采取字符串逐位转换的方式，此时特别注意 $l-1$ 的处理。

具体细节见代码。

**【完整代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
int f[2005][2005][2],m,d,num[2205],n;
const int mod = 1e9+7;
string l,r;
int dfs(int pos,int sum,int lim){
	if(f[pos][sum][lim] != -1) return f[pos][sum][lim];
	if(pos == n) return (sum == 0);
	int up = lim?num[pos+1]:9;//数位 dp 判断上限的通用方式
	int ans = 0;
	for(int i = (pos == 0 ? 1:0);i <= up;i ++){
      //注意取模
		if((pos+1) % 2 == 1 && i != d) ans = (ans + dfs(pos+1,(sum*10+i)%m,(lim && i== up))) % mod;
		else if((pos+1) % 2 == 0 && i == d) ans = (ans + dfs(pos+1,(sum*10+i)%m,(lim && i == up))) % mod;
	}
	return f[pos][sum][lim] = ans;
}
int work(string s,int k){
	memset(f,-1,sizeof(f));
	for(int i = 0;i < s.size();i ++) num[i+1] = (int)(s[i] - '0');
	n = s.size();
	if(k == 1){//这一段的目的是将 l-1
		int i = n;
		num[i] --;
		while(num[i] == -1){
			num[i] = 9;
			num[--i] -- ;
		}
		
	}
	return dfs(0,0,1);
}
int main(){
	cin >> m >> d;
	cin >> l >> r;
	cout << (work(r,0)-work(l,1)+mod)%mod;//注意，输出也要取模！！！
	return 0;
}
```

---

## 作者：Silence_water (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF628D)

数位 DP 题，较为套路。

定义状态 $\mathrm{dp[pos][res]}$ 表示当前填到第 $\mathrm{pos}$ 位，模 $m$ 余数为 $\mathrm{res}$，满足题意的数的个数。当 $\mathrm{pos=0}$ 且 $\mathrm{res=0}$ 时，计入总数。

由于记忆化搜索时是从高位往低位填，但对应的下标为 $\mathrm{len}$ 到 $1$，所以第 $\mathrm{pos}$ 位从题目角度看应为第 `len-pos+1` 位。

**Q** ：$[l,r]$ 范围内的数字并不能存在前导零，否则奇偶位数无法判断。故需要判断前导零，这样状态中就应该再加一维，变成 $\mathrm{dp[pos][len][res]}$，才能防止状态的重复。但这样空间就到达了 $\mathrm{O(2000^3)}$，必定会 MLE。

**A** ：确实如此。但是题目中提到了：**保证 $l,r$ 位数相同。**因此如果我们不管前导零，那么那些不合法的状态的数，去除前导零后的位数一定是比 $l,r$ 的位数都要小的，而这些数在统计 $l$ 和 $r$ 的时候都会被计算，相减后就会被抵消，因此不合法的状态都会被剔除，无需考虑前导零。

根据题目奇偶位限制，对应写出一下代码：

```cpp
for(int i=0;i<=up;i++)
{
	int wei=(len-pos+1);
	ll tmp=0;
	if(wei&1)
	{
		if(i!=d)tmp=dfs(pos-1,len,(res*10+i)%m,limit&&i==up);
	}
	else
	{
		if(i==d)tmp=dfs(pos-1,len,(res*10+i)%m,limit&&i==up);
	}
	ans=(ans+tmp)%mod;
}
```

注意到数据范围：$1\le l\le r\le10^{2000}$。因此 $l$ 和 $r$ 是以字符串形式读入的。普通的 `solve(r)-solve(l-1)` 因为 `l-1` 的难以实现而行不通。

因此我们需要单独判断 $l$ 是否满足条件，直接模拟即可。注意位数与读入时下标间的不同。

```cpp
ll solve_for_l()
{
	int len=strlen(l),res=0;
	for(int i=0;i<len;i++)
	{
		int ss=(l[i]^48);
		if((i+1)&1)
		{
			if(ss==d)return 0;
		}
		else
		{
			if(ss!=d)return 0;
		}
		res=(res*10+ss)%m;
	}
	return res==0;
}
```

因此答案即为 `solve(r)-solve(l)+solve_for_l()`，注意取模细节。

---

## 作者：joe_zxq (赞：1)

# 思路

这是一道数位 DP 的板子题，只需要对 $x,mod,lim,tp$ 进行记忆化搜索即可。

其中 $x$ 指计算到了第几位，$mod$ 指当前数模 $m$ 的余数，$lim$ 指填这一位是否收到限制，$tp$ 指是在给 $l$ 还是 $r$ 进行数位 DP。

# 注意

- 一定要开 long long。
- 题目中的奇数位和偶数位指的是**从左往右**。若下标是从 $0$ 开始的，一定要注意修改。
- 记忆化数组的初始化应设为 $-1$，而不是 $0$，否则可能会因为无解陷入死循环。
- 最后输出时，有可能模了 $1000000007$ 之后的第二个答案比第一个答案小，若直接相减会导致错误。需要将第二个答案加上 $1000000007$ 后再去减第一个答案。

# 代码

附上 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[2023],b[2023];
long long f[2023][2023];
const long long MOD=1e9+7;
long long len,m,d;
long long dp(long long x,long long mod,bool lim,bool tp){
	if(x==len)return (mod==0);
	else if(!lim&&f[x][mod]!=-1)return f[x][mod];
	long long ans=0;
	if(lim){
		for(long long i=0;i<=(tp?b[x]:a[x]);i++){
			if(x%2&&(i!=d))continue;
	     	if(x%2==0&&(i==d))continue;
			ans+=dp(x+1,(mod*10+i)%m,(i==(tp?b[x]:a[x])),tp);
			ans%=MOD;
		}
	}else{
		for(long long i=0;i<=9;i++){
			if(x%2&&(i!=d))continue;
	     	if(x%2==0&&(i==d))continue;
			ans+=dp(x+1,(mod*10+i)%m,0,tp);
			ans%=MOD;
		}
	}
	return f[x][mod]=ans;
}
int main(){
	cin>>m>>d;
    string l,r; cin>>l>>r;
	len=(long long)l.size();
    for(long long i=0;i<len;i++){
    	a[i]=l[i]-'0';
	}
	for(long long i=len-1;i>=0;i--){
		if(a[i]>0){
			a[i]--;
			break;
		}else{
			a[i]=9;
		}
	}
	for(long long i=0;i<len;i++){
    	b[i]=r[i]-'0';
	}
	for(long long i=0;i<2020;i++){
		for(long long j=0;j<2020;j++){
			f[i][j]=-1;
		}
	}
	long long ans1=dp(0,0,1,0);
	for(long long i=0;i<2020;i++){
		for(long long j=0;j<2020;j++){
			f[i][j]=-1;
		}
	}
	long long ans2=dp(0,0,1,1);
	printf("%lld",(ans2+MOD-ans1)%MOD);
	return 0;
}
```

 

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF628D)     
很水的数位 dp 题。    
## 题意
定义一类数如下：   
- 数位上从左往右数，偶数位上的数码为 $d$，奇数位上的不为 $d$。     
- $m$ 是这个数的因子。   

现在让你求出 $[l,r]$ 中这类数的个数。    
## 解法
发现数据范围极大，不能用暴力解决，那么我们就可以采用数位 dp。   
我们可以维护 $3$ 个值：dp 层数，当前数字模 $m$ 的结果，是否在奇数位上。    
因为需要维护位数的奇偶性，所以我们应该**从高位到低位**进行遍历。     
先考虑偶数位上的情况：显然地，在偶数位上不可能出现前导零，所以不需考虑这种情况。但是如果我们一直是贴着上界进行的 dp，那么再填上 $d$ 可能会超出去，这里我们进行特判即可。   
接下来是奇数位上的情况：首先有一种特殊情况，即这一位现在要填 $0$ 但是仍在前导 $0$ 状态下并且和 $d$ 相等，这种情况**需要继续往下转移**。转移需要注意奇数位上的状态不变，即不对数位的奇偶性造成影响。除去这个特例，剩下数位与 $d$ 相等的情况直接跳过即可。    
其他情况就正常向下转移即可。    
还有一点细节问题：由于上下界过大，而统计区间里的数字个数需要将下界减 $1$。这里可以不写高精度：我们算出 $(l,r]$ 的结果再对 $l$ 进行特判即可。    
[CODE](https://www.luogu.com.cn/paste/rd4al234)

---

## 作者：stupid_collie (赞：0)

### 算是比较常规的一个**数位 DP** 吧。
题目要求，在 $[l,r]$ 范围之内寻找偶数位是 $d$ 并且能够被 $m$ 整除的数。那么，我们在枚举的过程中，就可以根据当前枚举到的那一位判断，如果当前位为偶数位，那么考虑在数字的该位上填上 $d$，反之，就按照常规数位 DP 的思路从 $0$ 到最高能取到的数字进行枚举。

在动态规划的过程中，我们维护一个模数 $tot$，表示当前数字到该位对 $m$ 取模之后的模数，并将这个模数作为 DP 数组的第二个状态保存起来。

注意一件事情：该题中的数据范围很大（$l$ 和 $r$ 可以达到 $10^{2000}$！），因此，我们不能采取一般的方式读入，而是要将他们存入到一个字符串当中，并逐位写入到 $num$ 数组当中。

最后，由于我们所求的范围包括 $l$ 和 $r$ 两个端点，但我们在最后做差的过程中，将 $l$ 端点的信息截掉了。因此，我们要额外写一个函数，判断当前的 $l$ 端点是否是一个符合条件的数。

AC代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long

const int maxn = 3e3 + 9,modd = 1e9 + 7;
using namespace std;

int f[maxn][maxn];
int num[maxn],m,d,len;

string s1,s2;

int dfs(int po,int tot,bool limit,bool zero){
  if(po<=0)return !tot;
  if(!zero&&!limit&&f[po][tot]!=-1)return f[po][tot];
  int res = 0,lim = limit?num[po]:9;
  if((len-po+1)&1){//判断当前位的奇偶性，注意我们是从后往
  		//前枚举，因此当前位应该是从高到低的第 len-po+1 位
    for(int i = 0;i<=lim;i++)
      if(i!=d)
        res += dfs(po-1,(tot*10+i)%m,limit&&(i>=lim),zero&&!i);
  }else{
    if(lim>=d)
      res += dfs(po-1,(tot*10+d)%m,limit&&(d>=lim),zero&&!d);
  }

  if(!limit&&!zero)f[po][tot] = res%modd;
  return res%modd;
}

//对于两个端点，计算答案
int calc(const string &s){
  len = s.size();
  for(int i = 1;i<=len;i++){
    num[i] = s[len-i] - '0';
  }
  return dfs(len,0,1,1);
}

//判断l是否为一个符合条件的数字
int valid(const string &s){
  int sum = 0;
  for(int i = 0;i<s.size();i++){
    sum = (sum*10+s[i]-'0')%m;
    if(i&1&&s[i]-'0'!=d)return 0;
    if(!(i&1)&&s[i]-'0'==d)return 0;
  }
  return !sum;
}

signed main(){
  memset(f,-1,sizeof f);
  cin>>m>>d>>s1>>s2;
  //最后的最后，注意取模之后相减可能会出现负数的情况，因此要先加上模数在取模
  printf("%lld\n",(calc(s2) - calc(s1) + valid(s1) + modd)%modd);
}
```

---

## 作者：hxhhxh (赞：0)

## 大意

给定一个区间 $ [l,r] $ 和两个正整数 $ m,d $ ，求区间内 $ m $ 的倍数且偶数位（从高位往低位数，奇数位同理）为 $ d $ ，奇数位不为 $ d $ 。

## 思路

数位`dp`。不过我和其他题解不同，我直接计算 $ [l,r] $ 区间的答案。

设 $ f[i][j][k(0/1)][l(0/1)] $ 表示前 $ i $ 位模 $ m $ 余 $ j $ ，是否达到下界（ $ k $ ），是否不大于上界（ $ l $ ）。

然后就可以正常地数位`dp`了。奇数位强制不为 $ d $ ，枚举范围就是 $ [l,d-1],[d+1,r] $ ，其中 $ l = \begin{cases} 0 & (k = 0)\\a_i & (k=1) \end{cases} , r = \begin{cases} 9 & (l = 0)\\b_i & (l = 1) \end{cases} $ 。偶数位强制选 $ d $ ，如果 $ d $ 不在 $ [l,r] $ 范围内就什么都做不了。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int n,m,d,a[2005],b[2005],dp[2005][2005][2][2];
char aa[2005],bb[2005];
bool vis[2005][2005][2][2];
int dfs(int x,int y,bool dw,bool up){
	if(vis[x][y][dw][up]) return dp[x][y][dw][up];
	vis[x][y][dw][up]=true;
	if(x==n+1){
		if(y==0) return dp[x][y][dw][up]=1;
		return dp[x][y][dw][up]=0;
	}
	int ans=0;
	if(x&1){
		int l,r;
		if(dw) l=a[x];
		else if(x==1) l=1;
		else l=0;
		if(up) r=b[x];
		else r=9;
		for(int i=l;i<=r;i++) if(i!=d) ans=(ans+dfs(x+1,(y*10+i)%m,(i==a[x])&&dw,(i==b[x])&&up))%mod;
	}
	else if(!((dw&&d<a[x])||(up&&b[x]<d))) ans=(ans+dfs(x+1,(y*10+d)%m,(d==a[x])&&dw,(d==b[x])&&up))%mod;
	return dp[x][y][dw][up]=ans;
}
signed main(){
	cin>>m>>d;
	scanf("%s\n%s",aa+1,bb+1);
	n=strlen(aa+1);
	for(int i=1;i<=n;i++) a[i]=aa[i]-'0';
	for(int i=1;i<=n;i++) b[i]=bb[i]-'0';
	printf("%lld",dfs(1,0,1,1));
	return 0;
}

```

---

## 作者：EricWay1024 (赞：0)

# 数位DP

很显然是数位DP了。这里首先化归成求对任意给定$n$，求小于等于$n$的魔法数（magic nubmer）的数量，然后即可求出$[L+1, R]$区间上的魔法数的数量，再对$L$进行特判即可得到结果。数位DP的详解在[这里](https://www.luogu.com.cn/blog/EricWay1024/shuo-wei-dp)，给出了数位DP的常见模板，即记忆化搜索状态包括当前考虑位数$x$，前序影响决策的状态$st$和已枚举的前面所有数位是否均和$n$对应的位相等$op$。

本题所需要计数的魔法数进行了两个限制，分别实现如下：


## 条件1

奇数位不能是$d$，偶数位只能是$d$。这个限制在我们每一步枚举所取数字的时候需要考虑位数$x$的奇偶即可：

- 当$x$是偶数位时，该位只能取$d$，但注意如果此时$op$为$1$且$n$对应的数位小于$d$，则不能选择任何数字。
- 当$x$是奇数位时，该位在一般数位DP选择范围的基础上应该挖去$d$。

注意由于是从最高位开始算奇数位或偶数位，其实这样直接算出来的答案并不严格是我们的定义。例如，考虑小于$99$的7-魔法数，按此法会将$7$考虑在内，虽然按定义并不如此。然而，由于我们最后要算的是一个区间的值，且题目保证$L$和$R$位数相等（初看奇怪的一个限制），这就意味着在这个区间内的奇数位/偶数位均可以按照$L$或者$R$从高到低的位数来看，而位数小于$L$和$R$的所有数字，只要保持计数时标准一致，无论是什么计数结果，都会在随后的减法中被消去。此法因而在本题是奏效的，也就不需要在$x$之外引入新的状态参量。

## 条件2

该数应当是$m$的倍数。根据模的性质，考虑将前序选择的数位模$m$后的值记录下来。这里其实有两种做法，可以像大多数题解一样逐步记录，也可以提前维护$10^k \mod m$的数组，从而直接记录前序数位真正的数值模$m$后的结果。考虑完所有数字后，需要判断前序和模$m$是否和$0$相等。

## 其他

其他确实就没什么了。要注意的是题目说的奇数位、偶数位都是以1为首位的，但是操作`vector`的时候下标是从0开始的，所以要么添一位，要么把题目里面的奇偶反过来。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,from,to) for(register int i=from;i<=to;++i)
#define For(i,to) for(register int i=0;i<to;++i)
typedef long long ll;
inline ll read(){
    ll x=0; ll sign=1; char c=getchar();
    while(c>'9' || c<'0') {if (c=='-') sign=-1;c=getchar();}
    while(c>='0' && c<='9'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*sign;
}

const long long M = 1000000007ll;
ll m, d;
vector<int> l, r;
ll f[2020][2020][2];
ll ten[2020]; // 10^i % m

void init() {
    ten[0] = 1;
    rep(i, 1, 2004) {
        ten[i] = ten[i - 1] * 10ll;
        ten[i] %= m;
    }
}

inline void read_vec(vector<int> &dim) {
    char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    while(c >= '0' && c <= '9') {
        dim.push_back(c - '0');
        c = getchar();
    }
}

ll dp(int x, int st, int op, vector<int> &dim) {
    int s = dim.size();
    if (x == s) return (st == 0);

    ll &ret = f[x][st][op];
    if(ret > -1) return ret;
    ret = 0;
    int p = s - x - 1;
    if (!(x & 1)) {
        int maxx = op ? dim[x] : 9;

        rep(i, 0, maxx) {
            if (i == d) continue;
            int nst = (st + ((ten[p] * i) % m)) % m;
            ret += dp(x + 1, nst, op & (i == dim[x]), dim);
            ret %= M;
        }
    } else {
        if (op && dim[x] < d) return 0;
        else {
            int i = d;
            int nst = (st + ((ten[p] * i) % m)) % m;
            ret = dp(x + 1, nst, op & (i == dim[x]), dim);
        }
    }
    ret %= M;
    return ret;

}

ll solve(vector<int> &dim) {
    memset(f, -1, sizeof(f));
    return dp(0, 0, 1, dim);
}

int judge(vector<int> &dim) {
    ll sm = 0;
    int s = dim.size();
    For(i, s) {
        if(!(i & 1) && (dim[i] == d)) {
            return 0;
        }
        if((i & 1) && (dim[i] != d)) {
            return 0;
        }
        int p = s - i - 1;
        sm += ten[p] * dim[i];
        sm %= m;
    }
    if (sm != 0) return 0;
    else return 1;
}

int main() {
#ifdef D
    freopen("CF628D.in", "r", stdin);
#endif
    m = read(); d = read();
    read_vec(l); read_vec(r);

    init();

    ll res = solve(r) - solve(l) + judge(l);
    res %= M; res += M; res %= M;
    cout << res << "\n";

    return 0;
}
```


---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF95D)

# 题解

典型数位 $DP$ 题。

记 $f(x)$ 为 $[0,x]$ 中有多少满足条件的数，那么答案即为 $f(r)-f(l-1)$，但是由于我们的 $l\le 10^{1000}$，计算 $l-1$ 是肯定不理想的。

所以我们可以模仿 [这道题](https://www.luogu.com.cn/problem/CF628D) 的思路，先计算 $f(r)-f(l)$，再特判 $l$ 是否合法。

现在问题变成如何计算 $f(x)$.

考虑设计函数 `dfs()`，首先，根据数位 $DP$，一定有的参数是当前的位置 `pos`，其次是是否抵达最大值 `rl`，但是这道题与前一幸运数字有关，那么我们需要设计一维记录前一幸运数字的距离 `d`，但是我们还需知道当前的状态是否已经合法了，即是否已经有两幸运数字距离不超过 $k$ 了，所以我们还需增加一维 `ok` 记录当前状态合法情况。

汇总一下，我们设计函数 `dfs(pos,d,ok,rl)` 表示当前位置为 $pos$，前一幸运数字与下一幸运数字最多还可以差的距离，为 $0$ 不合法，以及 `ok` 表示当前状态是否合法，`rl` 表示是否触及上界。

函数的转移，如果当前的位置要填幸运数字，那么下一状态为 `dfs(pos-1,k,ok||d>0,rl&(i==up))`

如果不填幸运数字，那么下一状态为 `dfs(pos-1,Max(d,0),ok,rl&&(i==up))`

其中 $d$ 与 $0$ 取最大值的原因是我们需要用另外一维记录 $d$，如果 $d$ 为负数很难处理，同时，对于所有 $d<0$ 的情况，其实都是一样的——即上一幸运数字已经无法对状态合法性产生影响，故可以全部合并为一个状态，即距离已经超过，表现为 $d=0$.

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13485413.html
```



---


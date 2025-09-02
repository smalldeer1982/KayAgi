# [USACO12NOV] Balanced Cow Breeds G/S

## 题目描述

Farmer John usually brands his cows with a circular mark, but his branding iron is broken, so he instead must settle for branding each cow with a mark in the shape of a parenthesis -- (.  He has two breeds of cows on his farm: Holsteins and Guernseys.  He brands each of his cows with a

parenthesis-shaped mark.  Depending on which direction the cow is facing, this might look like either a left parenthesis or a right parenthesis.

FJ's N cows are all standing in a row, each facing an arbitrary direction, so the marks on the cows look like a string of parentheses of length N. Looking at this lineup, FJ sees a remarkable pattern: if he scans from left to right through just the Holsteins (in the order they appear in the sequence), this gives a balanced string of parentheses; moreover, the same is true for the Guernseys!  To see if this is truly a rare event, please help FJ compute the number of possible ways he could assign breeds to his N cows so that this property holds.

There are several ways to define what it means for a string of parentheses to be "balanced".  Perhaps the simplest definition is that there must be the same total number of ('s and )'s, and for any prefix of the string, there must be at least as many ('s as )'s.  For example, the following strings are all balanced:

() 
(()) 
()(()()) 

while these are not:

)( 
())( 
((()))) 

给一个只有左右括号的字符串，然后用 `H`、`G` 两种字符来标记这个序列，所有标记 `H` 的括号可以组成一个正确的括号序列，所有 `G` 标记的括号也组成一个正确的括号序列，然后输出这种标记方案的总数 $\operatorname{mod} 2012$ 的值。

## 说明/提示

The following breed assignments work:

(()) 
HHHH
(()) 
GGGG
(()) 
HGGH
(()) 
GHHG
(()) 
HGHG
(()) 
GHGH
 
感谢@CREEPER\_ 提供翻译


## 样例 #1

### 输入

```
(()) 
```

### 输出

```
6 
```

# 题解

## 作者：DengDuck (赞：7)

不知道为啥我的代码格外短。

首先根据题目给出的定义，我们可以考虑进行一个转化，把左括号看成 $1$，右括号看成 $-1$，这样合法括号序列可以看成任意前缀和非负，区间和为 $0$ 的序列。

我们由此可以列出一个 $\mathcal O(n^3)$ 的动态规划方案：

$f_{i,j,k}$ 表示染色到第 $i$ 项，黑色前缀和为 $j$，白色前缀和为 $k$ 的方案。

转移如下：

$$
f_{i,j,k}=f_{i-1,j-A_i,k}+f_{i-1,j,k-A_i} 
$$

边界条件为 $f_{0,0}=1$。

$A_i$ 表示经过转换之后我们的数组的第 $i$ 项。

其实有用的状态并不多，剪剪枝卡卡空间可以过。

但是这个时间复杂度不够优秀，我们考虑进一步化简。

我们发现对于一个 $i$ 而言，有用的 $j+k$ 是不变的，为数组 $A$ 的前 $i$ 项的前缀和，这点观察式子也可以发现。

所以我们只维护 $j$ 一维，保证 $k$ 不为负数即可。

$$
f_{i,j}=f_{i-1,j-A_i}+f_{i-1,j} 
$$

$k$ 非负如何保证？我们发现 $k=sum-j$，其中 $sum$ 是当前前 $i$ 项的前缀和，我们只要保证 $j\leq sum$ 即可。

时间复杂度降为 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e3+5;
const LL mod=2012;
LL n,f[N][N],sum,a[N];
char s[N];
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='(')a[i]=1;
		else a[i]=-1;
	}
	f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		sum+=a[i];
		for(int j=0;j<=sum;j++)
		{
			f[i][j]=f[i-1][j];
			if(0<=j-a[i])f[i][j]+=f[i-1][j-a[i]];
			f[i][j]%=mod;
		}
	}
	printf("%lld",f[n][0]);
}
```

---

## 作者：sxd666888 (赞：6)

所以，我用了dp转移，开两个状态：

      前一个  代表 H 还没匹配的前括号数；
      后一个  代表 G 还没匹配的前括号数；
再把空间滚一滚，讨论一下是  ‘（’  还是    ‘)’   ,放  H  还是  G  ，大力转移；

具体见代码（蒟蒻第一篇题解，希望能过qwq）；（有点丑不要介意）

```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
using namespace std;
const int mod=2012;
char s[1005];
int n,f[1005][1005],g[1005][1005];//f是之前的状态，g是当前的状态。
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	int oo=0;
	f[0][0]=1;//开始自然一个都没有。。
	for(int i=1;i<=n;++i)
	{
		if(s[i]=='(')
		{
			oo++;//oo维护还没匹配的左括号总数。
			for(int j=0;j<=oo;++j)
			{//j枚举的是 H 的左括号还没匹配的数量。
				if(j) g[j][oo-j]=(g[j][oo-j]+f[j-1][oo-j])%mod;//左括号变成 H
				if(oo-j) g[j][oo-j]=(g[j][oo-j]+f[j][oo-j-1])%mod;//左括号变成 G
			}
		}
		else if(s[i]==')')
		{
			oo--;//同上
			for(int j=0;j<=oo;++j)
			{//同上
				g[j][oo-j]=(g[j][oo-j]+f[j+1][oo-j])%mod;//一个 H 被匹配掉了
				g[j][oo-j]=(g[j][oo-j]+f[j][oo-j+1])%mod;//一个 G 被匹配掉了
			}
		}
		for(int j=0;j<=oo;++j) f[j][oo-j]=g[j][oo-j],g[j][oo-j]=0;//滚存一下
	}
	printf("%d",f[0][0]);//最后肯定没有不匹配的，所以直接输出f[0][0]。
	return 0;
}
```

---

## 作者：hame (赞：2)

# 题目大意
对于一个括号序列，求它能被拆成两个合法括号序列的方案数对 $2012$ 取模。
# 可以用的方法
## 1.暴力
直接开两个栈 $A$ 和 $B$，枚举一个括号能被放在栈 $A$ 还是栈 $B$。统计答案即可。

DFS 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,char> a,b;
map<string,int> vis;
int top_a,top_b,lsum_a,lsum_b;
int n,tot;
char cow[1401];
string a_num,b_num;
const string c;
void dfs(int k)
{
	vis[c]=0;
	if(k>n) tot=(tot+(top_a-lsum_a<=lsum_a&&top_b-lsum_b<=top_b&&vis[a_num]+vis[b_num]!=-2))%2012,vis[a_num]=vis[b_num]=-1;
	else
	{
		if(top_a-lsum_a<=lsum_a)
		{
			a[++top_a]=cow[k];
			string last=a_num;
			a_num=a_num+cow[k];
			lsum_a+=(cow[k]=='(');
			dfs(k+1);
			a_num=last;
			lsum_a-=(cow[k]=='(');
			top_a--;
		}
		if(top_b-lsum_b<=lsum_b)
		{
			b[++top_b]=cow[k];
			string last=b_num;
			b_num=b_num+cow[k];
			lsum_b+=(cow[k]=='(');
			dfs(k+1);
			b_num=last;
			lsum_b-=(cow[k]=='(');
			top_b--;
		}
	}
}
int main()
{
	scanf("%s",cow+1),n=strlen(cow+1);
	dfs(1);
	cout<<tot;
	return 0;
}
```

这时，你会发现：**TLE**！

为什么？

看一下 $n$ 的范围：
>$1 \le n \le 1000$

这能过才怪了！（毕竟，DFS 的时间复杂度为爆炸性的 $O(2^n)$，在 $n$ **一定大**的时候会超时）

因此，我们可以用 DP 解决这个问题。
## 2.DP 求解
### 插入知识
先插播一个小知识：

对于一个括号序列，我们可以每读入一个左括号就把它当成 $1$，每读入一个右括号就把它当成 $-1$。这样，就可以判断这是不是一个合法括号序列：只要判断它是不是“总和为 $0$”且“任意**前缀和**都不为负数”即可。

代码也很简单：

```cpp
string b;	//被处理的括号序列，假定已经输入好了
int bl=b.size()-1;	//被处理的括号序列长度
map<int,int> a;		//将要转化成只含-1与1的序列
for(int i=1;i<=bl;i++)
{
	if(b[i-1]=='(') a[i]=1;
	else a[i]=-1;
}
```

这是一个很简单的 trick，十分实用。
### 思路
> 注意：我的思路参考了[这位大佬的题解](https://www.luogu.com.cn/article/lc8934du)。

我们定义：
>定义 $dp_{i,j}$ 为第 $i$ 个位置，被扔到栈 $A$ 的位置和为 $j$。

由于有如下数量关系：

> 序列总和等于被扔到栈 $A$ 的位置和与被扔到栈 $B$ 的位置和之和。

所以，我们不需要再开多一维（主要是浪费空间），转移即为经典的选或不选，枚举两维后直接转移即可。

也可以理解成：

>选的情况：
>$$
>dp_{i,j}=dp_{i-1,j}+dp_{i-1,j-a_{i}}
>$$
>不选的情况：
>$$
>dp_{i,j}=dp_{i-1,j}
>$$
核心代码：

```cpp
dp[0][0]=1;	//初始化
for(int i=1;i<=n;i++)
{
	for(int j=0;j<=sum[i];j++)
	{
		if(j>=a[i]) dp[i][j]=dp[i-1][j]+dp[i-1][j-a[i]];	//选
		else dp[i][j]=dp[i-1][j];	//不选
	}
}
```

时间复杂度为 $O(n^2)$，可以通过。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define mo 2012
using namespace std;
int n;
string s1;
map<int,map<int,int> > dp;
map<int,int> a,sum;
signed main()
{
	cin>>s1,n=s1.size();
	for(int i=1;i<=n;i++) a[i]=(s1[i-1]=='(')-(s1[i-1]==')'),sum[i]=sum[i-1]+a[i];		//处理前缀和
	dp[0][0]=1;	//初始化
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=sum[i];j++)
		{
			if(j>=a[i]) dp[i][j]=(dp[i-1][j]%mo+dp[i-1][j-a[i]]%mo)%mo;	//选
			else dp[i][j]=dp[i-1][j]%mo;	//不选
			dp[i][j]%=mo;	//不要忘记取模
		}
	}
	cout<<dp[n][0];
	return 0;
}
```

---

## 作者：CaoSheng_zzz (赞：2)

不难发现本题对于合法的括号序列是只在乎有没有足够的括号去匹配，并不在乎括号的具体位置。

那么我们可以考虑定义左括号的权值为 $x$ 右括号的权值为 $- x$，那么一个合法的括号序列相加之后的权值和为 $0$。

当我们定义了上述的东西，那么就不难推出 DP，定义 $f_{k,i,j}$ 为我们当前取到了第 $k$ 个括号权值为 $now$，$H$ 序列所有括号的权值和相加为 $i$，$G$ 序列的括号权值和相加为 $j$，那么状态转移方程就为 $f_{k , i , j} = f_{k - 1 , i - now , j} + f_{k - 1 , i , j - now}$。

但是由于时间复杂度大致为 $\Omicron(n^3)$ 所以在赛时有可能不注意会 TLE~~（也许可以卡过）~~，所以我们可以考虑优化。

不难发现当前 $k$ 个括号的权值前缀和为 $sum$ 的时候，$j = sum - i$ 所以我们只需要维护 $i$ 这一维保证 $j \geqslant 0$ 就可以了，所以时间复杂度为 $\Omicron(n^2)$ 了。

又由于我们有一维以 $sum$ 循环所以 $|x|$ 越小越好且 $x$ 不能为 $0$，所以我们定义 $x = 1$。

Code：

```cpp
signed main() {
	scanf("%s" , cap + 1) ; n = strlen(cap + 1) ; f[0][0] = 1 ;
	for(int i=1 ; i<=n ; i++) a[i] = cap[i] == '(' ? x : - x ;
	for(int k=1 ; k<=n ; k++) {
		sum += a[k] ;
		for(int i=0 ; i<=sum ; i++) f[k][i] = (f[k - 1][i] + ((i - a[k]) >= 0 ? f[k - 1][max(i - a[k] , 0)] : 0)) % mod ;
	}
	return output(f[n][0]) , 0 ;
}
```

---

## 作者：信守天下 (赞：2)

## [洛谷传送门](https://www.luogu.com.cn/problem/P3058)
## 思路
首先看到这个题，考虑搜索。

用两个栈存括号，对每一个括号分别搜分给 $H$ 栈还是 $G$ 栈。

关于括号匹配为什么用栈，详见 [P1944 最长括号匹配](https://www.luogu.com.cn/problem/P1944)。

状态总数是 $2^{N}$，$N$ 最大 $1000$，显然过不去。

此时考虑动态规划。

令 $dp[i][j][k]$ 表示前 $i$ 个字符中，$H$ 栈剩余 $j$ 个未匹配的左括号， $G$ 栈中剩余 $k$ 个。
 
则
$\begin{cases}dp[i][j][k] = dp[i - 1][j - 1][k] + dp[i - 1][j][k - 1] & s[i] = ( \\ dp[i][j][k] = dp[i - 1][j - 1][k] + dp[i - 1][j][k - 1] & s[i] =\ ) \end{cases}$

需要注意的是，在 $s[i] = ($ 的转移中，$i,\ j$ 必须大于 $0$，因为 $-1$ 个括号是不合法的。

但是，考虑空间复杂度，是一个 $O(N^3)$ 的数组，开不下。

发现转移时，每一次只和上一个阶段的状态有关，所以可以滚动数组优化。

空间复杂度 $O(N^2)$，可以通过此题。

但是，还有更好的做法吗？

我们可以发现，有很多状态是不合法的，加大了空间的开支。

根据前 $i$ 个字符中左括号和右括号的数量以及 $H$ 中的左括号数量 $j$，一定可以计算出有且仅有一个合法的 $k$。

所以，可以预处理前缀区间的左括号和右括号数量，枚举 $i$ 和 $j$ ，计算出合法的 $k$ 进行计算。

这样就可以将 $k$ 这一维也优化掉了。

总时间复杂度 $O(N^2)$。

总空间复杂度 $O(N)$。
## code
~~~cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int kMaxN = 1e3 + 1;
const int Mod = 2012;
int dp[2][kMaxN];
int l[kMaxN], r[kMaxN];
string s;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> s;
  for (int i = 1; i <= s.size(); i++) {  // 预处理左右括号数量
    l[i] += l[i - 1] + (s[i - 1] == '(');
    r[i] += r[i - 1] + (s[i - 1] == ')');
  }
  dp[0][0] = 1;
  for (int i = 1; i <= s.size(); i++) {
    for (int j = 0; j <= i; j++) {       // 枚举类型一左括号数量
      if (j > l[i] - r[i]) {
        break;
      }
      dp[i & 1][j] = 0;
      if (s[i - 1] == '(') {
        if (j > 0) {
          dp[i & 1][j] = (dp[i & 1][j] + dp[(i - 1) & 1][j - 1]) % Mod;
        }
        if (l[i] - r[i] - j > 0) {
          dp[i & 1][j] = (dp[i & 1][j] + dp[(i - 1) & 1][j]) % Mod;
        }
      } else {
        dp[i & 1][j] = (dp[i & 1][j] + dp[(i - 1) & 1][j + 1] + dp[(i - 1) & 1][j]) % Mod;
      }
    }
  }
  cout << dp[s.size() & 1][0] << '\n';
  return 0;
}
~~~

---

## 作者：huhexuan (赞：1)

简单题。

看到括号序列，经典 trick 是直接将左括号赋值为 $1$，将右括号赋值为 $-1$，判断是否为括号序列的方法就是判断该区间的区间和是否为 $0$，且所有的前缀和都非负数。

此时需要一些注意力。

发现当该序列为合法括号序列时，一定存在解，于是产生了一些启发。

定义 $dp_{i,j}$ 为第 $i$ 个位置，标记为 H 的位置和为 $j$，由于前缀和一定，所以 G 的和也就确定了，不需要再开一维。

转移即为经典的选或不选，枚举两维后直接转移即可。

代码如下：

```cpp
#include<bits/stdc++.h> 
#define int long long 
using namespace std;
int n,a[1005],dp[1005][1005],sum[1005];
string s;
const int MOD=2012; 
signed main()
{ 
	cin>>s;
	n=s.size();
	for(int i=0;i<n;i++) a[i+1]=(s[i]=='('?1:-1),sum[i+1]=sum[i]+a[i+1];
	if(sum[n]!=0)//不判一样 
	{
		cout<<0;
		return 0;
	}
	dp[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=sum[i];j++)
		{
			//选或不选进行转移 
			dp[i][j]=dp[i-1][j]; 
			if(j>=a[i]) dp[i][j]+=dp[i-1][j-a[i]],dp[i][j]%=MOD;
		}
	}
	cout<<dp[n][0];
    return 0;
}

---

## 作者：Melo_DDD (赞：1)

只配做绿 DP。

容易发现当且仅当原序列合法的时候有方案。

判断原序列合法用非常经典的方法，左括号赋值为 $1$，右括号是 $-1$，合法的充要条件是序列的和为零且不存在负的前缀和。

注意到当一种 ``H`` 的方案确定时，``G`` 的方案也随之确定，所以只用考虑 ``H`` 即可。

我们设 $dp_{i,j}$ 表示到了第 $i$ 个位置，涂 ``H`` 的括号的和是 $j$ 的方案数。最后输出 $dp_{n,0}$。

### code

```cpp
int main () {
	std :: cin >> s ;
	int n = s.size () ;
	bool cant (0) ;
	f (i ,1 ,n ,1) {
		a[i] = (s[i - 1] == '(' ? 1 : - 1) ,sum[i] = sum[i - 1] + a[i] ; 
		if (sum[i] < 0) cant = true ; 
	} if (cant || sum[n] != 0) return puts ("0") ,0 ;
	dp[0][0] = 1 ;
	f (i ,1 ,n ,1) {
		f (j ,0 ,sum[i - 1] ,1) // 不选 i，直接继承
			dp[i][j] = dp[i - 1][j] ;
		f (k ,std :: max (a[i] ,0) ,sum[i] ,1) 
			(dp[i][k] += dp[i - 1][k - a[i]]) %= mod ; // 注意不能从小于 0 的不合法状态转移 
	}
	std :: cout << dp[n][0] << '\n' ;
	return 0 ;
}
```

---

## 作者：george0929 (赞：1)

$O(n^3)$ 艹过。

令 $dp_{i,j,k}$ 表示到第 $i$ 位，标有字符 `H` 的左括号比右括号多 $j$ 个，标有字符 `G` 的左括号比右括号多 $k$ 个。

转移时，分当前字符标 `H` 或 `G` 两种情况讨论。

若原字符串第 $i$ 为 `(`，则

$$dp_{i,j,k}=dp_{i-1,j-1,k}+dp_{i-1,j,k-1}$$

若原字符串第 $i$ 为 `)`，则

$$dp_{i,j,k}=dp_{i-1,j+1,k}+dp_{i-1,j,k+1}$$

需要滚动数组节约空间。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=2012;
string s;
int dp[2][505][505];
int main(){
	cin>>s;
	int n=s.length();
	s="#"+s;
	dp[0][0][0]=1;
	for(int I=1;I<=n;I++){
		int i=I%2;
		for(int j=0;j<=min(500,I);j++){
			for(int k=0;k<=min(500,I);k++){
				//G
				dp[i][j][k]=0;
				if(s[I]=='('){
					if(j!=0) dp[i][j][k]=(dp[i][j][k]+dp[!i][j-1][k])%mod;
				}else{
					dp[i][j][k]=(dp[i][j][k]+dp[!i][j+1][k])%mod;
				}
				//H
				if(s[I]=='('){
					if(k!=0) dp[i][j][k]=(dp[i][j][k]+dp[!i][j][k-1])%mod;
				}else{
					dp[i][j][k]=(dp[i][j][k]+dp[!i][j][k+1])%mod;
				}
			}
		}
	}
	cout<<dp[n%2][0][0];
}
```

---

## 作者：fight_for_humanity (赞：1)

[Better experience](https://www.cnblogs.com/fight-for-humanity/p/18357516)。

对于括号类问题，研究其合法性时，一个重要的性质就是这一路过来都合法（和栈类似）。

套路地，将 $\texttt{(}$ 看做 $+1$，$\texttt{)}$ 看做 $-1$，那么该序列合法就是其所有前缀和都 $\ge 0$。设计 dp，$dp[i][j][k]$ 表示标记了前 $i$ 个数，$A$ 序列的前缀和为 $j$，$B$ 序列的前缀和为 $k$ 的方案数。

$$
dp[i][j][k] = dp[i-1][j-a_i][k] + dp[i-1][j][k-a_i]
$$

这里自然保证了 $j,k \ge 0$。

但是时间复杂度是 $O(n^3)$。

观察到 $j+k = sum$ 这一特征，即 $i,j$ 已知足以知 $k$。

去掉 $k$ 这一维，有转移：

$$
dp[i][j] = dp[i-1][j-a_i] + dp[i-1][j]
$$

这里保证 $sum-j \ge 0$ 即可。

#### CODE

```CPP
#include<bits/stdc++.h>
using namespace std;
const int mod = 2012;
char s[1010];
int n,a[1010],f[1010][1010];
inline int add(int x,int y){ return x + y >= mod ? x + y - mod : x + y; }
inline void toadd(int &x,int y){ x = add(x,y); }
int main(){
	scanf("%s",s+1);
	n = strlen(s+1);
	for(int i = 1;i<=n;++i){
		if(s[i] == '(')a[i] = 1;
		else a[i] = -1;
	}
	f[0][0] = 1;
	for(int i = 1,sum = 0;i<=n;++i){
		sum += a[i];
		for(int j = 0;j<=sum;++j){
			f[i][j] = f[i-1][j];
			if(sum - j >= 0)toadd(f[i][j],f[i-1][sum-j]);
		}
	}
	printf("%d",f[n][0]);
	return 0;
}
```

#### 总结

对于有效信息的提取有利于优化 dp。

---

## 作者：John_Smith (赞：1)

这是我们的模拟赛赛题，真没想到自己能赛场上能过蓝题。

这个是 $O(n^2)$ 算法。当然小常数 $O(n^3)$ 完全没问题。

-----

以下是正篇：

我们大概能猜到，答案不为 $0$ 的充要条件是原串为合法括号串。

我们使最初所有括号属于 ```H```，然后从中选出一部分括号放到 ```G``` 中，这种选取的方案就是所求。

回忆一下如何判断一个括号串是否合法：

```cpp
int tmp=0;
rep(i,1,n)
{
	if(str[i]=='(')++tmp;
	else
	{
		if(!tmp){puts("0");return 0;}
		else --tmp;
	}
	b[i]=tmp;
}
if(tmp){puts("0");return 0;}
```

如果我们从原串中选出一个字符串（记为 $s_G$），那么如果将剩下的字符串（记为 $s_H$）扔到上面过程中，我们发现：

* 上面过程中的 ```tmp``` 在中途不会到达 $0$

* 上面过程中的 ```tmp``` 最终会到达 $0$

对于 $s_G$ 同理。

所以，我们首先预处理出原串在每个位置的 $tmp$。

然后，我们设计状态 $f_{i,j}$ 代表当前已经处理到第 $i$ 个字符（原串中前面的 $n-1$ 个字符已经判断了是否选择），而当前 $s_G$ 的 ```tmp``` 为 $j$。

当前 $s_G$ 能取的左括号数量最多为 ```tmp```，所以 $j$ 要小于此值。

假如当前字符为 ```(```，那么：

* 将其放入 $s_G$，$s_H$ 的 ```tmp``` 会减一，$s_H$的 ```tmp``` （也就是 $j$）会加一；

* 将其放入 $s_H$，$s_H$ 的 ```tmp``` 不变，$s_H$的 ```tmp``` （也就是 $j$）不变。

也就是说，此时：

$$f_{i,j}=f_{i-1,j-1}+f_{i-1,j}$$

我们也容易得出对于 ```)``` 的情况。

于是，我们很容易写出一下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
#define read() Read<int>()
#define write Write<int>
#define writesp Writesp<int>
#define writeln Writeln<int>
template<typename T>
inline T Read()
{
	bool f=0;T x=0;char ch;
	do{ch=getchar();f|=(ch=='-');}while(!isdigit(ch));
	do{x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}while(isdigit(ch));
	return f?-x:x;
}
template<typename T>
inline void Write(T x)
{
	if(x<0){putchar('-');write(-x);return;}
	if(x>9)write(x/10);
	putchar(x%10+48);
}
template<typename T> inline void Writeln(T x){Write(x);puts("");}
template<typename T> inline void Writesp(T x){Write(x);putchar(' ');}
const int maxn=1005;
char str[maxn];
int f[maxn][maxn];
int sum[maxn];
int b[maxn];
const int mod=2012;
signed main()
{
	scanf("%s",str+1);
	int n=strlen(str+1);
	int tmp=0;
	rep(i,1,n)
	{
		if(str[i]=='(')++tmp;
		else
		{
			if(!tmp){puts("0");return 0;}
			else --tmp;
		}
		b[i]=tmp;
	}
	if(tmp){puts("0");return 0;}
	f[0][0]=1;
	rep(i,1,n)
	{
		if(str[i]=='(')
			rep(j,0,b[i])
			{
				if(j!=0)f[i][j]=(f[i-1][j-1]+f[i-1][j])%mod;
				else f[i][j]=f[i-1][j];
			}
		else
			rep(j,0,b[i])
			{
				f[i][j]=(f[i-1][j+1]+f[i-1][j])%mod;
			}
	}
	writeln(f[n][0]);
	return 0;
}
```

本题结束。是不是非常简单？

---

## 作者：Adove (赞：1)

这题的滚动数组完全可以只留一维

因为另一维能且仅能根据当前总数量推得

因而到某位为止下未匹配为定值的有且仅有一个元素

故我们可以直接略去最后一维

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=1005;
const int MOD=2012;

int n;
char ch[MAXN];
int f[2][MAXN];

int main()
{
	scanf("%s",ch+1);n=strlen(ch+1);
	f[0][0]=1;int ct=0;
	for(int i=1;i<=n;++i){
		memset(f[i&1],0,sizeof(f[i&1]));
		if(ch[i]=='('){
			++ct;
			for(int j=0;j<=ct;++j){
				if(j>0) f[i&1][j]=(f[i&1][j]+f[i&1^1][j-1])%MOD;
				if(j<ct) f[i&1][j]=(f[i&1][j]+f[i&1^1][j])%MOD;
			}
		}else{
			--ct;
			for(int j=0;j<=ct;++j){
				f[i&1][j]=(f[i&1][j]+f[i&1^1][j+1]+f[i&1^1][j])%MOD;
			}
		}
	}printf("%d\n",f[n&1][0]);
	return 0;
}
```

---

## 作者：lukelin (赞：1)

这道题我用的是搜索算法，很朴实的记搜，可能其他大佬有更好的算法（比如DP），但我作为一个DFS_lover的同学，也就打打深搜了\...

好了废话不多说，下面是某位蒟蒻（当然是我）的代码（快读这种东西嘛，~~懒得复制了~~）
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

string A;
int a[1005], len;
int z_num[1005], o_num[1005];
int _h, _g;
//在H/G组的第i为，多余括号为k的情况有没有搜索过，如果搜索过了，那么记录当前答案
int _H[1005][1005];
int _G[1005][1005];

int DFS(int i)
{
	if (i == len && _h == 0 && _g == 0)
		return 1;
	else if (i == len)
		return 0;
	int sum1 = 0, sum2 = 0;
    //记忆化搜索，避免同样的情况算多次
	if (_H[i][_h] != -1)
		sum1 = _H[i][_h];
	if (_G[i][_g] != -1)
		sum2 = _G[i][_g];
	if (a[i] == 1){
		if (_h > 0 && _H[i][_h] == -1)
		{
			_h--;
			sum1 += DFS(i+1);
			_h++;
		}
		if (_g > 0 && _G[i][_g] == -1) 
		{
			_g--;
			sum2 += DFS(i+1);
			_g++;
		}
	}
	else{
		if (_h + 1<= o_num[len - 1] - o_num[i] && _H[i][_h] == -1)
		{
			_h++;
			sum1 += DFS(i + 1);
			_h--;
		}
		if (_g + 1 <= o_num[len - 1] - o_num[i] && _G[i][_g] == -1)
		{
			_g++;
			sum2 += DFS(i+1);
			_g--;
		}
	}
	_H[i][_h] = sum1;
	_G[i][_g] = sum2;
	return ((sum1 + sum2) % 2012);
}

int main()
{
	cin >> A;
	if (A[0] == ')')
	{
		printf("0\n");
		return 0;
	}
	len = A.length();
	int i;
    //初始化z_num是废的懒得删了
	if (A[0] == '(')
	{
		a[0] = 0;
		z_num[0] = 1;
		o_num[0] = 0;
	}
	else
	{
		a[0] = 1;
		z_num[0] = 0;
		o_num[0] = 1;
	}
	memset(_H[0], -1, sizeof(_H[0]));
	memset(_G[0], -1, sizeof(_G[0]));
	for (i = 1; i < len; i++)
	{
		memset(_H[i], -1, sizeof(_H[i]));
		memset(_G[i], -1, sizeof(_G[i]));
		if (A[i] == '(')
		{
			a[i] = 0;
			z_num[i] = z_num[i-1]+1;
			o_num[i] = o_num[i-1];
		}
		else
		{
			a[i] = 1;
			z_num[i] = z_num[i-1];
			o_num[i] = o_num[i-1]+1;
		}
	}
    //_h表示H组中多余的左括号数量，_g同理
	_h = _g = 0;
	printf("%d", DFS(0));
	return 0;
}
```

---

## 作者：IAKIOIpwp (赞：0)

### 前言：

不知道为什么，看了题目，又看了讨论中的翻译，一直没有理解题意，可能是翻译的不完整或者翻译的不对。

但看完样例解释后，我总算理解了题意。

### 算法：

第一眼看就知道是动态规划。

对于我这个蒟蒻来说，做动态规划一直都很费时间。

### 思路：

根据题面描述，我们考虑对这个括号序列进行转换。

把左括号看成 $1$，把右括号看成 $-1$，那么合法的括号序列就变成了任意前缀和非负且区间之和等于 $0$ 的一个序列。

既然已经把括号序列进行转换了，那么我们就可以开始推状态转移方程了。

由于题目中写了字母串长度小于等于 $1000$，限制为 $1$ 秒，所以我们只能用 $O(N^{2})$ 的做法。

那怎么优化呢？当然是用前缀和啦。

我们把 H 看做染黑色，把 G 看做染白色，那么对于前 $i$ 项染色来说，若黑色前缀和为 $j$ 则白色前缀和为 $j-a_i$。

由此我们可以列出一个时间复杂度为 $O(n^{2})$ 的状态转移方程：

$$dp_{i,j}=dp_{i-1}+dp_{i-1,j-a_i}$$

如果 $j-a_i$ 为负数呢？ 只需特判一下就可以了。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=2012;
int n,dp[2001][2001],sum,a[2001];
char s[2001];
int main(){
	cin>>s+1;
	n=strlen(s+1);
	for(int i=1;i<=n;i++){ //进行转换 
		if(s[i]=='(') a[i]=1;
		else a[i]=-1;
	}
	dp[0][0]=1; //初始化 
	for(int i=1;i<=n;i++){
		sum+=a[i];
		for(int j=0;j<=sum;j++){
			dp[i][j]=dp[i-1][j]; //现设置初始值，满足要求在加 
			if(0<=j-a[i]) dp[i][j]+=dp[i-1][j-a[i]]; //特判 
			dp[i][j]%=mod; //取模 
		}
	}
	dp[n][0]%=mod; //最后再去一次，以防万一 
	cout<<dp[n][0];
	return 0;
}
```

---

## 作者：Rose_Melody (赞：0)

## Solution - Balanced Cow Breeds G/S
[题目链接](https://www.luogu.com.cn/problem/P3058)

### 题目分析

**这是一道动态规划的好题**

根据题面描述，我们考虑对这个括号序列进行转换：把左括号看做 $1$,右括号看做 $-1$, **合法的括号序列**就转换成：序列所有前缀和非负，且区间之和等于 $0$ 的一个序列。

现在我们开始考虑动态转移方程 。 由于 $|S|\le1000$，我们要找到一个时间复杂度为 $O(n^{2})$ 的做法。

不妨把 H 看做染黑色，把 G 看做染白色，对于前 $i$ 项染色来说，若黑色前缀和为 $j$，则白色前缀和为 $j-a_{i}$（$a_{i}$ 表示转换后数组的第 $i$ 项），并初始化 $f_{0,0}=1$，我们就可以列出一个时间复杂度为 $O(n^{2})$ 的方程： 

$$f_{i,j}=f_{i-1,j}+f_{i-1,j-a_{i}}$$  

维护 $j-a_{i}$ 非负，只需特判一下即可。

### AC 代码


```cpp
//P3058 
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e3 + 5 ;
const int Mod = 2012 ;
int n , f[N][N] , cnt , a[N] ;
string s;
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> s ;
	n = s.size(); 
	s = ' ' + s; //为了让字符串的下标从 1 开始
	for(int i = 1;i <= n;i ++){
		if(s[i] == '(') a[i] = 1;
		else a[i] = -1;//转换
	}
	f[0][0] = 1;//初始化
	for(int i = 1;i <= n;i ++){
		cnt += a[i] ; // cnt 存前 i 项的前缀和
		for(int j = 0;j <= cnt;j ++){
			f[i][j] = f[i-1][j];
			if(j - a[i] >= 0){
				f[i][j] += f[i-1][j - a[i]] ;
			}
			f[i][j] %= Mod ;
		}
	}
	cout << f[n][0] ;
	return 0;
}
```

---


# [ABC305G] Banned Substrings

## 题目描述

给定一个由 $M$ 个长度不超过 $6$ 的仅由字母 $\texttt a$ 和 $\texttt b$ 组成的非空字符串集合 $S=\{s_1, s_2, ..., s_M\}$。

求有多少个字符串 $T$ 满足以下条件：

- 长度为 $N$ 且仅由字母 $\texttt a$ 和 $\texttt b$ 组成。
- 对于任意 $s_i\in S$，$T$ 中不包含 $s_i$ 作为连续的子串。

由于答案可能很大，所以对 $998244353$ 取模。

## 说明/提示

$1\leq N\leq 10^{18}$

$1\leq M\leq 126$

$N$ 和 $M$ 是整数。

$s_i$ 是由字母 $a$ 和 $b$ 组成的长度不超过 $6$ 的非空字符串。

$s_i \neq s_j$（$1\leq i<j\leq M$）。

## 样例 #1

### 输入

```
4 3
aab
bbab
abab```

### 输出

```
10```

## 样例 #2

### 输入

```
20 1
aa```

### 输出

```
17711```

## 样例 #3

### 输入

```
1000000007 28
bbabba
bbbbaa
aabbab
bbbaba
baaabb
babaab
bbaaba
aabaaa
aaaaaa
aabbaa
bbaaaa
bbaabb
bbabab
aababa
baaaba
ababab
abbaba
aabaab
ababaa
abbbba
baabaa
aabbbb
abbbab
baaaab
baabbb
ababbb
baabba
abaaaa```

### 输出

```
566756841```

# 题解

## 作者：Disjoint_cat (赞：6)

[Luogu](https://www.luogu.com.cn/problem/AT_abc305_g)，[Atcoder](https://atcoder.jp/contests/abc305/tasks/abc305_g)。

# ABC305G Banned Substrings

## 题意

给定正整数 $n$ 和 $m$ 以及 $m$ 个字符串 $s_1\sim s_m$。

求满足以下条件的，长度为 $n$，只含字母 $\texttt{a}$ 和 $\texttt{b}$ 的字符串 $S$ 的个数 $\bmod\ 998244353$：

- $\forall1\le i\le m$，$s_i$ 不是 $S$ 的连续字串。

$n\le10^{18},m\le126,s_i$ 只含字母 $\texttt{a}$ 和 $\texttt{b}$，$L=\left\vert s_i\right\vert\le6$。

## 解法

完全不需要 AC 自动机。

### 朴素

显然想到 dp，令 $dp_{i,T}$ 为长度为 $i$，最后 $5$ 个字母为 $T$ 的符合条件的字符串个数。

转移不难写，时间复杂度为 $\Theta(n\cdot2^{L-1})$。

### 正解

$n$ 很大，要把这个 $n$ 优化掉。

看到这种递推式的题，想到矩阵优化。

先搞出转移矩阵 $M$。

如果一个状态 $X$ 可以转到另一个状态 $Y$（当然不能让某个 $s_i$ 成为子串），令 $M_{X,Y}=1$，否则 $M_{X,Y}=0$。

然后我们算出 $M^{n-5}$，把结果的所有点的值加起来即可。

（如果 $n\le5$，直接特判并暴力枚举即可。）

时间复杂度 $\Theta(\log n\cdot(2^{L-1})^3)$。

## Code

[Here](https://atcoder.jp/contests/abc305/submissions/42169340)

---

## 作者：Neil_Qian (赞：6)

# [ABC305G] Banned Substrings 题解

## 题目描述

给定 $m$ 个仅由 `a` 和 `b` 构成的长度不超过 $6$ 的字符串 $s_i$，问有多少个长度**恰好**为 $n$ 的仅由 `a` 和 `b` 构成的字符串 $t$，使得任意的 $i$ **不满足** $s_i$ 是 $t$ 的子串（即连续子序列）。$n\le 10^{18},m\le126$。

## 解决方案

### 暴力

暴力不用说了吧，枚举每个位置即可，时间复杂度为 $O(2^n\times \sum|s_i|)$。

### 一些提示

多模式串匹配？AC自动机啊！

$n\le 10^{18}$？矩阵快速幂啊！

### 正解

一种估计与众不同的做法。（请先阅读提示）

多模式串匹配，先将所有 $s_i$ 构建到AC自动机上，并且计算失配指针。设 $ch_{i,0/1}$ 表示当前结点为 $i$，下一个字符为 `a` 或 `b` 的下一个结点（可能是失配）。因为所有字符串长度在 $6$ 以内，所以AC自动机的结点数不到 $2^7<130$。显然，字符串 $t$ 的匹配情况与在AC自动机上所在的结点有关。

求方案数，想到动态规划。$dp_{i,j}$ 表示长度为 $i$，在AC自动机 $j$ 结点。采用刷表法 $dp_{i,j}$ 可以推到 $dp_{i+1,ch_{j,0/1}}$，前提是 $ch_{j,0/1}$ 不是一个字符串的成功匹配结点，即没有结束标记。然后就可以愉快地动态规划了！

但是，$n\le 10^{18}$，这有点离谱了吧！想想动态规划的优化方法：单调队列、斜率、四边形不等式......需要优化力度很大，而且转移简单，那不就是矩阵快速幂优化动态规划吗？很容易从上面的实则得到转移矩阵，然后矩阵快速幂就可以了。设AC自动机上有 $cnt$ 个结点，则时间复杂度为 $O(cnt^3logn)$，可以通过。

### 一些可能的错误

注意：AC自动机要跳失配指针，所以结束标记要随着失配指针传递！

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
const ll MOD=998244353,N=132;string s;queue<ll> q;
ll n,m,ch[N][2],fail[N],u,cnt,ret,i,j,k;bool suc[N];
struct mat{
	ll n,m,a[N][N];
	mat(){memset(a,0,sizeof(a));}
	mat operator *(const mat b){
		mat res;res.n=n,res.m=b.m;
		for(i=0;i<=n;i++)for(j=0;j<=b.m;j++)for(k=0;k<=m;k++)
			(res.a[i][j]+=a[i][k]*b.a[k][j]%MOD)%=MOD;
		return res;
	}
}x,ans;
inline void insert(const string str){//插入字符串
	u=0;
	for(char c:str){
		if(!ch[u][c-'a'])ch[u][c-'a']=++cnt;
		u=ch[u][c-'a'];
	}
	suc[u]=1;
}
inline void build(){//构建fail指针
	for(i=0;i<2;i++)if(ch[0][i])q.push(ch[0][i]);
	while(!q.empty()){
		u=q.front(),q.pop(),suc[u]|=suc[fail[u]];//一个易错点
		for(i=0;i<2;i++)
			if(ch[u][i])fail[ch[u][i]]=ch[fail[u]][i],
				q.push(ch[u][i]);
			else ch[u][i]=ch[fail[u]][i];
	}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>n>>m;//读入优化
	while(m--)cin>>s,insert(s);
	build(),x.n=x.m=ans.n=cnt,ans.m=0,ans.a[0][0]=1;
	for(i=0;i<=cnt;i++)if(!suc[i])//构建矩阵
		for(j=0;j<2;j++)x.a[ch[i][j]][i]++;
	while(n){//矩阵快速幂
		if(n&1)ans=x*ans;
		x=x*x,n>>=1;
	}
	for(i=1;i<=n;i++)ans=x*ans;
	for(i=0;i<=cnt;i++)if(!suc[i])(ret+=ans.a[i][0])%=MOD;//统计答案
	return cout<<ret<<"\n",0;
}
```


---

## 作者：_•́へ•́╬_ (赞：3)

典。

## 思路

把禁止串放一起建 AC 自动机。

设 $f_{i,j}$ 表示长度为 $i$ 的串匹配到 AC 自动机的第 $j$ 个点且还没出现过禁止串的方案数。

矩阵加速即可。

## [code](https://atcoder.jp/contests/abc305/submissions/42150967)

```cpp
#include<stdio.h>
#include<deque>
#define N 777
#define mod 998244353
using namespace std;
long long n;int m,sz,tre[N][2],fail[N],sum;char s[9];bool ban[N];
struct matrix
{
	int a[N][N];
	inline void operator*=(const matrix&kkk)
	{
		int ans[N][N]={};
		for(int i=0;i<=sz;++i)for(int j=0;j<=sz;++j)if(a[i][j])
			for(int k=0;k<=sz;++k)
				ans[i][k]=(ans[i][k]+(long long)(a[i][j])*kkk.a[j][k])%mod;
		for(int i=0;i<=sz;++i)for(int j=0;j<=sz;++j)a[i][j]=ans[i][j];
	}
}a,ans;
main()
{
	scanf("%lld%d",&n,&m);
	for(int j;m--;)
	{
		scanf("%s",s);j=0;
		for(int i=0;s[i];j=tre[j][s[i++]!='a'])
			if(!tre[j][s[i]!='a'])tre[j][s[i]!='a']=++sz;
		ban[j]=1;
	}
	fail[tre[0][0]]=fail[tre[0][1]]=0;deque<int>q;
	if(tre[0][0])q.emplace_back(tre[0][0]);
	if(tre[0][1])q.emplace_back(tre[0][1]);
	for(int i;q.size();)
	{
		i=q.front();q.pop_front();ban[i]|=ban[fail[i]];
		if(tre[i][0])fail[tre[i][0]]=tre[fail[i]][0],
			q.emplace_back(tre[i][0]);
		else tre[i][0]=tre[fail[i]][0];
		if(tre[i][1])fail[tre[i][1]]=tre[fail[i]][1],
			q.emplace_back(tre[i][1]);
		else tre[i][1]=tre[fail[i]][1];
	}
	for(int i=0;i<=sz;++i)if(!ban[i])
		++a.a[i][tre[i][0]],++a.a[i][tre[i][1]];
	ans.a[0][0]=1;
	for(;n;n>>=1,a*=a)if(n&1)ans*=a;
	for(int i=0;i<=sz;++i)if(!ban[i])sum=(sum+ans.a[0][i])%mod;
	printf("%d",sum);
}
```



---


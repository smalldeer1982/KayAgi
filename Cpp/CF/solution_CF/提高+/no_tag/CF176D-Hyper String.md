# Hyper String

## 题目描述

Paul Erdős's prediction came true. Finally an alien force landed on the Earth. In contrary to our expectation they didn't asked the humans to compute the value of a Ramsey number (maybe they had solved it themselves). They asked another question which seemed as hard as calculating Ramsey numbers. Aliens threatened that if humans don't solve this problem in less than 2 hours they will destroy the Earth.

Before telling the problem they introduced the concept of Hyper Strings. A Hyper String is made by concatenation of some base strings. Suppose you are given a list of base strings $ b_{1},b_{2},...,b_{n} $ . Now the Hyper String made from indices list $ i_{1},i_{2},...,i_{m} $ is concatenation of base strings $ b_{i1},b_{i2},...,b_{im} $ . A Hyper String can be very large and doing operations on it is very costly for computers.

The aliens asked humans to compute the length of the longest common sub-sequence of a Hyper String $ t $ with a string $ s $ .

## 说明/提示

The length of string $ s $ is the number of characters in it. If the length of string $ s $ is marked as $ |s| $ , then string $ s $ can be represented as $ s=s_{1}s_{2}...\ s_{|s|} $ .

A non-empty string $ y=s[p_{1}p_{2}...\ p_{|y|}]=s_{p1}s_{p2}...\ s_{p|y|} $ ( $ 1<=p_{1}&lt;p_{2}&lt;...&lt;p_{|y|}<=|s| $ ) is a subsequence of string $ s $ . For example, "coders" is a subsequence of "codeforces".

## 样例 #1

### 输入

```
2
cba
dgh
2
1 2
aedfhr
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
b
a
5
1 2 1 2 1
aaa
```

### 输出

```
2
```

# 题解

## 作者：tong2324919503jl (赞：3)

考虑 $\text{dp}$ 状态。

$dp[pre][len]$ 考虑到 $s$ 的前缀为 $pre$，其与 $t$ 的最大公共子序列为 $len$ 的最小前缀。

考虑转移。

$dp[pre][len]=\min(dp[pre-1][len]$，在 $dp[pre-1][len-1]$ 右面最靠左的和 $s[pre]$ 相同的位置）。

为了 $O(1)$ 转移考虑预处理两个数组。

$dp1[i][j][k]$ 表示在 $b[i]$ 字符串上的第 $j$ 个位置右面最靠左的字符为 $k$ 的位置。

$dp2[i][k]$ 表示在 $t[i]$ 右面含有字符 $k$ 的最靠左的位置。

然后就可以通过这道题了。
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<vector>
#include<set>
#include<algorithm>
#define er -'a'+1
#define inf 0x3f3f3f3f
#define maxn 2010
using namespace std;
namespace lin
{
	string s;
	string t[maxn];
	struct linlin
	{
		int lin[30];
	};
	struct jialin
	{
		int num,id;
		jialin(){}
		jialin(int _num,int _id){
			num=_num,id=_id;
		}
		friend bool operator < (jialin xx,jialin yy)
		{
			return xx.num>yy.num;
		}
	};
	set<jialin>st;
	set<jialin>::iterator it;
	vector<linlin> dp1[maxn];
	int wjll[maxn][30];
	int dp2[maxn][30];
	int dp[maxn][maxn];//dp[pre][len]考虑到s的前缀为pre,其与t的最大公共子序列为len的最小前缀 
	int vist[40];
	int vis[30];
	int a[maxn],sum[maxn];
	int query(int x,int op)
	{
		if(x==inf) return inf;
		it=st.lower_bound(jialin(x,20060913));
		jialin tmp=*it;
		int tt=tmp.id;
		if(sum[tt]==x)
			tt--;
		int sw=x-sum[tt<0?0:tt];
		if(sw>0)
			if(dp1[a[tt+1]][sw-1].lin[op])
			{
				return sum[tt]+dp1[a[tt+1]][sw-1].lin[op];
			}
		tt=dp2[tt+1][op];
		if((int)(t[a[tt]][0] er)==op)
			return sum[tt-1]+1;
		if(dp1[a[tt]][0].lin[op])
		{
			return sum[tt-1]+dp1[a[tt]][0].lin[op];
		}
		return inf;
	}
	int love(int wjl)
	{
		int n,m;
		ios::sync_with_stdio(false);
    	cin.tie(NULL);
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>t[i];
			int siz=t[i].size();
			for(int j=0;j<siz;j++)
				wjll[i][t[i][j] er]=1;
		}
		cin>>m;
		st.insert(jialin(0,0));
		for(int i=1;i<=m;i++)
		{
			cin>>a[i];
			sum[i]=sum[i-1]+(int)t[a[i]].size();
			st.insert(jialin(sum[i],i));
		}
		for(int i=m;i>=0;i--)
		{
			for(int j=1;j<=26;j++)
				dp2[i][j]=vist[j];
			for(int j=1;j<=26;j++)
				if(wjll[a[i]][j])
					vist[j]=i;
		}
		for(int i=1;i<=n;i++)
		{
			int siz=t[i].size();
			memset(vis,0,sizeof(vis));
			for(int j=siz-1;j>=0;j--)
			{
				linlin tmp;
				for(int z=1;z<=26;z++)
					tmp.lin[z]=vis[z];
				dp1[i].push_back(tmp);
				vis[t[i][j] er]=j+1;
			}
			reverse(dp1[i].begin(),dp1[i].end());
		}
		cin>>s;
		int nn=s.size();
		memset(dp,0x3f,sizeof(dp));
		dp[0][0]=0; 
		linlin tmp;
		memset(tmp.lin,0,sizeof(tmp.lin)); 
		dp1[0].push_back(tmp);
		for(int i=1;i<=nn;i++)
		{
			for(int j=0;j<=nn;j++)
			{
				if(i==3&&j==3)
					i++,i--;
				dp[i][j]=dp[i-1][j];
				if(j!=0)
					dp[i][j]=min(dp[i][j],query(dp[i-1][j-1],s[i-1] er));
			}
		}
		for(int i=nn;i>=0;i--)
		{
			if(dp[nn][i]!=inf)
			{
				cout<<i;
				return wjl;
			}
		}
		return wjl;
	}
}
signed main()
{
	return lin::love(0);
}
```


---

## 作者：Lgx_Q (赞：2)

[o](https://www.luogu.com.cn/problem/CF176D) [rz](https://codeforces.com/problemset/problem/176/D)

题意：有 $n$ 个字符串 $a_1...a_n$，总长度不超过 $10^6$。现在给出长度为 $m$ 的数列 $id_1...id_m$，构造字符串 $A=a_{id_1}+a_{id_2}+...+a_{id_m}$，其中 $+$ 表示两个字符串相连。给出字符串 $B$，求 $\operatorname{LCS}(A,B)$。$|B|,n,m\le2000$

分析：

最直接最简单的方法就是设 $f_{i,j}$ 表示 $A$ 中前 $i$ 个字符和 $B$ 中前 $j$ 个字符的 $\operatorname{LCS}$，但是容易 T。

发现答案不超过 $|B|$~~（q~~，于是利用贪心，即 **换量优化DP**~~（别查了，自己起的名）~~，这个技巧也是非常常见的。

交换数值，设 $f_{i,j}$ 表示整个 $A$ 字符串和 $B$ 中前 $i$ 个字符，共匹配了 $j$ 个字符（LCS），此时 $A$ 中最后一个匹配的字符位置是多少。

这时可以利用 $f_{i,j}$ 更新 $i+1$ 阶段的状态。首先 $B_j$ 可以不选：$f_{i+1,j}\leftarrow f_{i,j}$

如果选择 $B_j$ 匹配，就需要在 $A$ 中 $f_{i,j}$ 的位置之后找一个等于 $B_j$ 的字符 $A_p$：$f_{i+1,j+1}\leftarrow p$。

查找可以预处理自动机。

由于我 ~~（lgj）~~ 的 $f_{i,j}$ 存的是**整个 $A$ 的位置**
，所以还要二分一下这个位置属于哪个字符串，会加一个 $\log$。

总时间 $O(|B|^2\log m+26(10^6+m))$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=2010;
ll n,m,len[maxn],id[maxn],P[26][maxn],f[maxn][maxn],sum[maxn];
char s[maxn*500];
vector<ll>p[26][maxn];
ll Next(ll i,ll j,ll c)
{
	++j;
	if(j>len[id[i]]) j=1,++i;
	if(i>m) return 0;
	if(p[c][id[i]][j]) return sum[i-1]+p[c][id[i]][j];
	++i;
	if(P[c][i]) return sum[P[c][i]-1]+p[c][id[P[c][i]]][1];
	return 0;
}
ll belong(ll x)
{
	return lower_bound(sum,sum+1+m,x)-sum;
}
int main()
{
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		len[i]=strlen(s+1);
		for(ll j=0;j<26;j++) p[j][i].resize(len[i]+1);
		for(ll j=len[i];j;j--)
		{
			for(ll k=0;k<26;k++) p[k][i][j]=(j==len[i]?0:p[k][i][j+1]);
			p[s[j]-'a'][i][j]=j;
		}
		sum[i]=sum[i-1]+len[i];
	}
	scanf("%lld",&m);
	for(ll i=1;i<=m;i++)
	{
		scanf("%lld",&id[i]);
		sum[i]=sum[i-1]+len[id[i]];
	}
	scanf("%s",s+1);
	ll L=strlen(s+1);
	for(ll i=m;i;i--)
	{
		for(ll j=0;j<26;j++)
			if(p[j][id[i]][1]) P[j][i]=i;
			else P[j][i]=P[j][i+1];
	}
	for(ll i=0;i<26;i++) P[i][0]=P[i][1];
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	for(ll i=0;i<L;i++)
	{
		for(ll j=0;j<=i;j++)
		{
			if(f[i][j]>1e15) break;
			f[i+1][j]=min(f[i+1][j],f[i][j]);
			ll x=belong(f[i][j]),y=f[i][j]-sum[x-1];
			ll p=Next(x,y,s[i+1]-'a');
			if(p) f[i+1][j+1]=min(f[i+1][j+1],p);
		}
	}
	for(ll i=L;~i;i--)
		if(f[L][i]<1e15)
		{
			printf("%lld",i);
			break;
		}
	return 0;
}
```

---

## 作者：__stick (赞：2)


## 题意
直接粘的翻译。

给定 $n(n \le 2000)$ 个小写英文字母组成的字符串 ${a_i}$，总长度不超过 $10 ^ 6$。再给定一个长度为 $m(m \le 2000)$ 的正整数序列 ${b_i}(1 \le b_i \le n)$，定义 $A = a_{b_1} + a_{b_2} + ... + a_{b_M}$，其中$+$表示字符串的连接。最后给定一个小写英文字母组成的字符串 $B(|B| \le 2000)$，求 $A$ 和 $B$ 的最长公共子序列长度。

## 思路                                              

首先意识到 A 的长度会达到 $10^9$ 级别（不保证 b 中元素互不相同），不可能存到状态里暴力建出来跑 dp，所以只能分别处理形成  A 的每一个子串，但在状态中记录在 A 的位置就已经不够用了，而这又是我们转移所必须的。这里有个背包中经常使用的技巧，既然这个题答案不大，那就可以将答案存到状态里，将在 A 中的位置存到 dp 数组中，所以状态就变成了 $F[i][j]$ 表示考虑到 B 的第 $i$ 位，答案是 $j$ ，在A 中的位置最小是多少（用一个 pair 表示 是形成 A 的第几个字符串，以及在当前这个中的位置）。

然后就考虑转移的问题，可以看到即使我们做了转化，状态数也已经到了  $10^6$  级别，所以转移必须是的 $O(1)/O(\log n)$，对于每一个状态    $F[i][j]$，有两种情况，要不向 $F[i+1][j]$ 转移，此时不选 B 这一位的字符，所以直接转移，第二种是选 B 这一位的字符，这时候就要在 A 中找到除了已经匹配部分第一个与 $B_{i+1}$  相等的位置了，这个可以预处理出每个子串中各个字符出现的位置，然后二分第一个大于当 前位置的位置，如果在这个串中没有就去下一个串中接着二分，复杂度可能会退化成 $O(m)$，所以预处理一个 $nxt[i][ch]$  数组，表示当前  后第一个 ch 字符的位置，这样在当前中没找到，就可以去下一个中找，最多找两个，复杂度就得到了保证。

然后输出的时候就看最大的 $F[|B|][j]$ 不是正无穷的 $j$ 就行了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline bool cmax(T& a,const T& b){return a<b?a=b,1:0;}
template<typename T>
inline bool cmin(T& a,const T& b){return b<a?a=b,1:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
const int MAXN=2006;
const int mod=1e9+7;
const int INF=mod;
string s[MAXN];
int b[MAXN];
char t[MAXN];
pii F[MAXN][MAXN];
vi pos[MAXN][26];
int nxt[MAXN][26];
inline pii getnxt(pii u,char c)
{
	int p=u.first,x=u.second;
	vi& uvi=pos[b[p]][c];
	auto ii=upper_bound(uvi.begin(),uvi.end(),x);
	if(ii==uvi.end())
	{
		//cerr<<"!!!";
		vi& vvi=pos[b[nxt[p+1][c]]][c];
		if(vvi.empty())return {INF,INF};
		else return {nxt[p+1][c],vvi.front()};
	}
	else return {p,*ii};ii};//注意这里返回的不是在给出的第几个串中，而是在给出序列 b 的哪一个
}
int main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(20);
	int n;cin>>n;
	s[0]=" ";
	for(int i=1;i<=n;i++)cin>>s[i],s[i]=' '+s[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<s[i].size();j++)
			pos[i][s[i][j]-'a'].push_back(j);
	int m;cin>>m;
	for(int i=1;i<=m;i++)cin>>b[i];
	for(int j=0;j<26;j++)nxt[m+1][j]=m+1;
	for(int i=m;i;i--)
		for(int j=0;j<26;j++)
		if(pos[b[i]][j].size())nxt[i][j]=i;
		else nxt[i][j]=nxt[i+1][j];
	cin>>t+1;
	int len=strlen(t+1);
	for(int i=0;i<=len;i++)
		for(int j=0;j<=len;j++)
			F[i][j]=make_pair(INF,INF);
	for(int i=0;i<=len;i++)F[i][0]={0,0};
	auto u=getnxt({3,1},'a');
	
	for(int i=0;i<len;i++)
		for(int j=0;j<=i;j++)
		{
			if(F[i][j]!=(pii){INF,INF})
			{//	cerr<<i<<' '<<j<<'\n';
				cmin(F[i+1][j],F[i][j]);
				pii u=F[i][j];
				if(u.first==m&&u.second+1==s[b[m]].size())continue;
			
			//	cerr<<u.first<<' '<<u.second<<'\n';
				auto v=getnxt(u,t[i+1]-'a');
			//	cerr<<"!\n";
			//	cerr<<u.first<<' '<<u.second<<'\n';
			//	cerr<<v.first<<' '<<v.second<<'\n';
				cmin(F[i+1][j+1],v);
			}
		}
	
	int ans=len;
	while(ans>0&&F[len][ans]==(pii){INF,INF})ans--;
	cout<<ans;
	return 0;
}
```


---


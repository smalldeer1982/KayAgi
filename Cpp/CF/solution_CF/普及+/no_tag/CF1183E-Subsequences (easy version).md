# Subsequences (easy version)

## 题目描述

The only difference between the easy and the hard versions is constraints.

A subsequence is a string that can be derived from another string by deleting some or no symbols without changing the order of the remaining symbols. Characters to be deleted are not required to go successively, there can be any gaps between them. For example, for the string "abaca" the following strings are subsequences: "abaca", "aba", "aaa", "a" and "" (empty string). But the following strings are not subsequences: "aabaca", "cb" and "bcaa".

You are given a string $ s $ consisting of $ n $ lowercase Latin letters.

In one move you can take any subsequence $ t $ of the given string and add it to the set $ S $ . The set $ S $ can't contain duplicates. This move costs $ n - |t| $ , where $ |t| $ is the length of the added subsequence (i.e. the price equals to the number of the deleted characters).

Your task is to find out the minimum possible total cost to obtain a set $ S $ of size $ k $ or report that it is impossible to do so.

## 说明/提示

In the first example we can generate $ S $ = { "asdf", "asd", "adf", "asf", "sdf" }. The cost of the first element in $ S $ is $ 0 $ and the cost of the others is $ 1 $ . So the total cost of $ S $ is $ 4 $ .

## 样例 #1

### 输入

```
4 5
asdf
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 6
aaaaa
```

### 输出

```
15
```

## 样例 #3

### 输入

```
5 7
aaaaa
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
10 100
ajihiushda
```

### 输出

```
233
```

# 题解

## 作者：wucstdio (赞：7)

emmmm，反正就是数据范围不同所以我就直接说hard版的题解了。

首先我们希望选出来的$k$个字符串长度尽可能长，因为这样代价小。

所以我们考虑对于每一个$i$，算出来长度为$i$的本质不同的字符串的数量。这样最后贪心选取就行了。

考虑一个$O(26n^2)$的DP。

我们设$f[i][j][c]$表示前$i$个字符，长度为$j$，最后一个字符为$c$的数量。

为了去重，如果$s[i]=c$那么就只能让字符串的结尾为$i$，否则就任意。

考虑转移。考虑$s[i]$是否等于$c$可得：

$$f[i][j][c]=\begin{cases}f[i-1][j][c]&\text{if $s[i]\neq c$}\\\sum_{c'}f[i-1][j-1][c']+[j=1]&\text{else}\end{cases}$$

令$s[i][j]=\sum_{c}f[i][j][c]$，直接转移即可，时间复杂度$O(26n^2)$

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
int n;
ll k,f[105][105][26],s[105][105],ans;
char t[105];
int main()
{
	scanf("%d%I64d",&n,&k);
	scanf("%s",t+1);
	for(int i=1;i<=n;i++)
	{
		f[i][1][t[i]-'a']=1;
		for(int j=1;j<=i;j++)
		{
			for(int c=0;c<26;c++)
			{
				if(c+'a'==t[i])f[i][j][c]+=s[i-1][j-1];
				else f[i][j][c]+=f[i-1][j][c];
				if(f[i][j][c]>k)f[i][j][c]=k;
				s[i][j]+=f[i][j][c];
			}
			if(s[i][j]>k)s[i][j]=k;
		}
	}
	s[n][0]=1;
	for(int i=n;i>=0;i--)
	{
		if(s[n][i]>k)
		{
			ans+=k*(n-i);
			k=0;
			break;
		}
		ans+=s[n][i]*(n-i);
		k-=s[n][i];
	}
	if(k)
	{
		printf("-1\n");
		return 0;
	}
	printf("%I64d\n",ans);
	return 0;
}
```

---

## 作者：decoqwq (赞：4)

递推求解

令$f[i][j]$代表以$i$位置结尾长度为$j$的不同子串个数，并记录每一个字母上次出现的位置$las[i]$

可以得到，如果这个字母是第一次出现，那么$f[i][j]=f[i-1][j]+max(f[i-1][j-1],1ll);$

否则$f[i][j]=f[i-1][j]+f[i-1][j-1]-f[las[a[i]]-1][j-1];$(减去相同的情况)

然后从长到短取不同子串即可
```cpp
#include <bits/stdc++.h>
using namespace std;
long long f[110][110];
char a[110];
map<char,int> las; 
int main()
{
    int n,k;
    cin>>n>>k;
    scanf("%s",a+1);
    f[n][0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            if(las[a[i]]==0)
            {
                f[i][j]=f[i-1][j]+max(f[i-1][j-1],1ll);
            }
            else
            {
                f[i][j]=f[i-1][j]+f[i-1][j-1]-f[las[a[i]]-1][j-1];
            }
        }
        las[a[i]]=i;
    }
    long long ans=0;
    for(int i=n;i>=0;i--)
    {
        if(k<=f[n][i])
        {
            ans+=k*(n-i);
            k=0;
            break;
        }
        k-=f[n][i];
        ans+=f[n][i]*(n-i);
    }
    cout<<(k>0?-1:ans);
}
```

---

## 作者：Frozencode (赞：3)

楼上的大佬们都说了hard版的解法，我就老老实实讲下easy版的做法 （~~比hard版容易理解~~）


不难看出子序列长度越大，代价越小，那么我们自然想到每次肯定是把长度大的先统计掉，这就有点像BFS时每次都处理同一个深度的节点。

然后我们就可以~~脑洞大开~~类比到BFS上去。以原始序列作为根节点，每个节点都指向其删除任意一个字符后所得到的子序列。按子序列长度扩展BFS，最后在搜索到第k个节点时输出答案就行了~

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=500010;
const ll INF=2147483647;
ll n,k,ans;
string a,cur,icur;
queue<string> q;
set<string> s;
int main()
{
    cin>>n>>k;
    cin>>a;
    s.insert(a);
    q.push(a);
    while(!q.empty())
    {
        cur=q.front();
        q.pop();
        for(int i=0;i<cur.size();i++)
        {
            icur=cur;
            icur.erase(i,1);
            if(s.size()<k&&!s.count(icur))//如果有k个点或者这个子序列出现过就不用再入队了。
            {
                s.insert(icur);
                q.push(icur);
                ans+=n-icur.size();//统计代价。
            }
        }
    }
    if(s.size()<k)//没有k个子序列，无解。
    {
        cout<<"-1";
    }
    else cout<<ans;
    return 0;
}
```


---

## 作者：封禁用户 (赞：1)

## 题解：CF1183E Subsequences (easy version)

抽象 Easy version $2000$ 但 Hard version $1900$。

来[这里](https://www.luogu.com.cn/article/fr7axc24)。

### 解题思路

明显**贪心**，**优先选择长度更长的子序列**。

求不同长度的不同子序列可以 **dp 解决**。

设 $dp_{i,j}$ 表示前 $i$ 个字符中长度为 $j$ 的子序列数量。

如果不考虑本质不同的子序列，则有 $dp_{i,j} = dp_{i - 1,j} + dp_{i - 1,j - 1}$。

考虑最后一位的情况：如字符串 `abc`，那么从 `ab` 转移到所有字符 `c` 时都相同。

所以减去 $dp_{pre_i - 1 , j-1}$ 即可，其中 $pre_i$ 表示 $S_i$ 上一次出现的位置，如果没有出现过默认为 $0$。

所以最终的 dp 公式为：$dp_{i,j} = dp_{i - 1,j} + dp_{i - 1,j - 1} - dp_{pre_i - 1 , j-1}$。

所以长度为 $x$ 的子序列的个数为 $dp_{n , x}$。

如果出现以下情况：

$$k - 1 > \sum_{i = 1}^{n} dp_{n,i}$$

则无解，否则从多至少选择即可。

记得开 **long long**！

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
long long n , k , p , dp[105][105] , ans;
char s[105];
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> s[i];
	}
	for(int i = 0 ; i <= n ; i++)
	{
		dp[i][0] = 1;
	}
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= i ; j++)
		{
			dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
			for(int k = i - 1 ; k >= 1 ; k--)
			{
				if(s[i] == s[k])
				{
					dp[i][j] -= dp[k - 1][j - 1];
					break;
				}
			}
		}
	}
	for(int i = n ; i >= 0 ; i--)
	{
		ans += min(dp[n][i] , k) * (n - i);
		k -= min(dp[n][i] , k);
		if(!k)
		{
			break;
		}
	}
	if(k)
	{
		cout << "-1";
	}
	else
	{
		cout << ans;
	}
	return 0;
}
```

---

## 作者：wmrqwq (赞：0)

vp 到的。

# 题目链接

[CF1183E Subsequences (eazy version)](https://www.luogu.com.cn/problem/CF1183E)

[CF1183H Subsequences (hard version)](https://www.luogu.com.cn/problem/CF1183H)

# 解题思路

考虑动态规划。

设 $dp_{i,j}$ 表示考虑到字符串前 $i$ 个字符中选取的字符长度为 $j$ 的**不同**的子序列数量。

于是我们就有以下转移：

$dp_{i,j} = dp_{i-1,j} + dp_{i-1,j-1} - dp_{lst_{i},j-1}$。

其中，$lst_{i}$ 表示字符串的第 $i$ 个字符上一次出现在哪里。

然后大力将 dp 结果贪心选取即可。

**注意**，$dp_{n,i}$ 可能会小于 $0$，贪心前需要先将 $dp_{n,i}$ 和 $0$ 取最大值，不然就会 Wrong Answer on test #35。

时间复杂度 $O(n^2)$，足以通过 Eazy ver 和 Hard ver。

# 参考代码

```cpp
/*
Tips:

你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
打 cf 不要用 umap！！！

记住，rating 是身外之物。

该冲正解时冲正解！

Problem:

算法：

思路：

*/
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
//ll pw(ll x,ll y,ll mod){if(x==0)return 0;ll an=1,tmp=x;while(y){if(y&1)an=(an*tmp)%mod;tmp=(tmp*tmp)%mod;y>>=1;}return an;}
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
ll _t_;
void _clear(){}
/*
dp,

dp[i][j]表示前i个字符中长度为j的不同的子序列数量 
*/
ll n,m;
ll dp[110][110],ans;
string s;
ll lst[310],pre[310];
ll f(char x){
	return x-'a';
}
void solve()
{
	_clear();
	cin>>n>>m>>s;
	s=' '+s;
	forl(i,1,n)
		pre[i]=lst[f(s[i])],lst[f(s[i])]=i;
	forl(i,0,n)
		dp[i][0]=1;
	forl(i,1,n)
		forl(j,1,i)
		{
			dp[i][j]=dp[i-1][j]+dp[i-1][j-1];
			if(pre[i])
				dp[i][j]-=dp[pre[i]-1][j-1];
		}
	forr(i,n,0)
	{
		Max(dp[n][i],0ll);
		if(m>=dp[n][i])
			ans+=(n-i)*dp[n][i],m-=dp[n][i];	
		else
			ans+=(n-i)*m,m=0;
	}
	if(m==0)
		cout<<ans<<endl;
	else
		cout<<-1<<endl;
}
int main()
{
	IOS;
	_t_=1;
// 	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：qczrz6v4nhp6u (赞：0)

Eazy \*2000 绿，Hard \*1900 蓝，世界名画。

貌似是一种与现有做法不同的 DP？

### Solution

一个显然的想法是将所有长度的子序列求出来，按长度从大到小贪心计算贡献，正确性一目了然。

然而我们只关心长度为 $i$ 的子序列数量，所以我们考虑设计一种算法来求出每种子序列的数量。

考虑 DP。设 $f_{i,j}$ 表示长度为 $i$，结尾为 $j$（此处设 $\texttt{a}=1,\texttt{b}=2,\cdots,\texttt{z}=26$）的**本质不同**子序列个数。

当我们扫到 $c$ 的时候，考虑更新每一个 $f_{x,c}$。

显然将长度为 $x-1$ 的子序列后拼上 $c$ 就能得到长度为 $x$，以 $c$ 结尾的子序列，同时归纳可得这些子序列本质不同。那么有：

$$f_{x,c}=\sum_{i=0}^{26}f_{x-1,i}$$

初值 $f_{0,0}=1$。

容易发现前缀和可以优化掉一个常数，复杂度为 $O(n^2)$。

实际上不前缀和也没事，反正 $n\le 100$ 随便碾过。

### Code

```cpp
#include<bits/stdc++.h>
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
using namespace std;
using ll=long long;
using ull=unsigned long long;
char buf[1<<20],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
Tp inline void read(T& x){
    x=0;char c=getchar();bool f=0;
    for(;c<48||c>57;c=getchar())c=='-'&&(f=1);
    for(;c>47&&c<58;c=getchar())x=(x<<1)+(x<<3)+(c^48);
    f&&(x=-x);
}
Ts inline void read(T& x,_T&... y){read(x),read(y...);}
Tp inline void assign(T *a,int n,T b){while(n--)*a++=b;}
Tp inline void copy(T *a,T *b,int n){while(n--)*a++=*b++;}
Tp inline void ckmin(T &a,T b){b<a&&(a=b);}
Tp inline void ckmax(T &a,T b){a<b&&(a=b);}
const int N=1e2+5;
int n;ll K;
char str[N];
ll f[N][26],s[N];
int main(){
	scanf("%d%lld%s",&n,&K,str+1);
	s[0]=f[0][0]=1;
	for(int p=1;p<=n;p++)
		for(int i=n;i>=1;i--){
			s[i]-=f[i][str[p]-'a'];
			f[i][str[p]-'a']=s[i-1];
			s[i]+=f[i][str[p]-'a'];
		}
	ll ans=0;
	for(int i=n;i>=0&&K;i--)
		ans+=min(s[i],K)*(n-i),K-=min(s[i],K);
	if(!K)printf("%lld\n",ans);
	else printf("-1\n");
	return 0;
}
```

---


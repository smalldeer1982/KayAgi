# Reconstruction

## 题目描述

There is a hidden array $ a_1, a_2, \ldots, a_n $ of length $ n $ whose elements are integers between $ -m $ and $ m $ , inclusive.

You are given an array $ b_1, b_2, \ldots, b_n $ of length $ n $ and a string $ s $ of length $ n $ consisting of the characters $ \texttt{P} $ , $ \texttt{S} $ , and $ \texttt{?} $ .

For each $ i $ from $ 1 $ to $ n $ inclusive, we must have:

- If $ s_i = \texttt{P} $ , $ b_i $ is the sum of $ a_1 $ through $ a_i $ .
- If $ s_i = \texttt{S} $ , $ b_i $ is the sum of $ a_i $ through $ a_n $ .

Output the number of ways to replace all $ \texttt{?} $ in $ s $ with either $ \texttt{P} $ or $ \texttt{S} $ such that there exists an array $ a_1, a_2, \ldots, a_n $ with elements not exceeding $ m $ by absolute value satisfying the constraints given by the array $ b_1, b_2, \ldots, b_n $ and the string $ s $ .

Since the answer may be large, output it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, we can see that the following array satisfies all constraints, thus the answer is $ 1 $ :

1. $ \texttt{P} $ — $ {[\color{red}{\textbf{1}},3,4,2]} $ : sum of $ 1 $ .
2. $ \texttt{S} $ — $ {[1,\color{red}{\textbf{3},4,2}]} $ : sum of $ 9 $ .
3. $ \texttt{P} $ — $ {[\color{red}{1,3,\textbf{4}},2]} $ : sum of $ 8 $ .
4. $ \texttt{P} $ — $ {[\color{red}{1,3,4,\textbf{2}}]} $ : sum of $ 10 $ .

In the second test case, it can be shown that no array $ a $ with all $ |a_i| \leq m = 10^9 $ satisfies all constraints.

## 样例 #1

### 输入

```
6
4 10
PSPP
1 9 8 10
4 1000000000
????
1 1 1 4000000000
8 1000000000
?P?SSP?P
-857095623 -1424391899 -851974476 673437144 471253851 -543483033 364945701 -178537332
4 7
PPSS
4 2 1 3
9 20
?????????
1 2 3 4 5 6 7 8 9
3 1000000000
P??
-145463248 -974068460 -1287458396```

### 输出

```
1
0
2
1
14
1```

# 题解

## 作者：_fairytale_ (赞：7)

这么唐的题我场上为啥不会做？？？


令 $s_0=\text{P},s_{n+1}=\text{S},b_0=0,b_{n+1}=0$。

思考 $s$ 确定时，$s_{i-1}$ 和 $s_{i}$ 对数组 $a$ 有什么限制，分四种情况讨论：

1. $\text{PP}:a_i=b_i-b_{i-1}$。
2. $\text{SP}:$ 令 $a$ 数组的和为 $sum$，则 $a_i+a_{i-1}+sum=b_i+b_{i-1}$。
3. $\text{PS}:sum=b_{i-1}+b_i$ 。
4. $\text{SS}:a_i=b_{i}-b_{i+1}$。

发现如果我们知道了 $sum$，那么问题就很简单了。事实上，在约定了 $s_0$ 和 $s_{n+1}$ 之后，$s$ 中必然存在一个 $\text{PS}$，通过 $\text{PS}$，我们就可以确定 $sum$。

但是 $s$ 中有问号，我们可以通过枚举 $\text{PS}$ 的位置得到 $sum$。

接下来用一个简单的 DP 解决即可：

设 $f_{i,0/1}$ 表示考虑了 $s$ 的前 $i$ 个位置，第 $i$ 位填了 $\text{P/S}$ 的合法方案数，若 $s_{i-1}$ 与 $s_i$ 满足对应的要求就从 $f_{i-1,s_{i-1}}$ 转移到 $f_{i,s_i}$，详见代码。

当然这里可能有一个问题，我们只满足了以上的限制和 $|a_i|\le m$，这样的约束下一定存在一个合法的 $a$ 吗？

答案是肯定的。考虑从所有 $\text{PS}$ 中间处把串分开，这样分出来的每一段一定是 $i$ 个 $\text{S}$ 拼上 $j$ 个 $\text{P}$ 的形式，其中 $i,j\ge 0$，并且当且仅当 $i=0$ 或 $j=0$ 时这一段对应的 $a$ 唯一确定，其余情况，只需满足 $|a|\le m$ 和每一段中 $\text{SP}$ 的约束即可。

时间复杂度 $\mathcal O(n^2)$。

```cpp
#include<bits/stdc++.h>
bool Mst;
#define ll long long
#define rep(x,qwq,qaq) for(int (x)=(qwq);(x)<=(qaq);++(x))
using namespace std;
#define maxn 2010
#define mod 998244353
int T;
int n,m;
ll ans;
char ch[maxn];
ll b[maxn];
map<ll,int>mp;
int f[maxn][2];
void add(int &x,int y){
	x+=y;
	if(x>mod)x-=mod;
}
void solve(){
	cin>>n>>m;
	cin>>(ch+1);
	ch[0]='P',ch[n+1]='S';
	b[n+1]=0;
	rep(i,1,n)cin>>b[i];
    mp.clear();
	ans=0; 
	rep(_,0,n){
    	if(ch[_]=='S'||ch[_+1]=='P')continue;
    	ll sum=b[_]+b[_+1];
    	if(mp.count(sum))continue;
		mp[sum]=1;
		f[0][0]=1;//[0/1]->[P/S]
		rep(i,1,n+1){
			f[i][0]=f[i][1]=0;
			if(ch[i]!='S'){
				//PP
				if(abs(b[i]-b[i-1])<=m)add(f[i][0],f[i-1][0]);
				//SP
				ll mx=b[i]+b[i-1]-sum;
				mx=mx/2+(mx%2);
				if(abs(mx)<=m)add(f[i][0],f[i-1][1]); 
			}
			if(ch[i]!='P'){
				//PS
				if(b[i-1]+b[i]==sum)add(f[i][1],f[i-1][0]);
				//SS
				if(abs(b[i]-b[i-1])<=m)add(f[i][1],f[i-1][1]);
			}
		}
		ans=(ans+f[n+1][1])%mod;
	}
	cout<<ans<<'\n';
}
bool Med;
signed main() {
	cerr<<(&Mst-&Med)/1024.0/1024.0<<" MB\n";
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>T;
	while(T--)solve(); 
	return 0;
}
```

---

## 作者：Fesdrer (赞：4)

对于一个对 $s$ 赋值的合法方案，我们可以确定这一方案下 $a$ 中所有数的总和。这是因为如果 $s_1=\texttt{S}$ 或 $s_n=\texttt{P}$，我们就可以得到所有数的总和，否则的话 $s$ 中一定存在子串 `PS`，也可以得到所有数的总和。由以上的分析可以得到，可能可以成为 $a$ 中所有数的总和的数为：$b_1,b_1+b_2,b_2+b_3,\cdots,b_{n-1}+b_n,b_n$ 这 $n+1$ 个数。

因此我们依次考虑这 $n+1$ 个数。假设当前考虑的数为 $sum$，我们需要计算出使得 $a$ 中所有数的总和为 $sum$ 的合法 $s$ 的方案数。观察到我们可以根据 $sum$ 把所有后缀限制转变为前缀限制。考虑 DP，设 $f_{i,0/1}$ 表示考虑到第 $i$ 位且第 $i$ 位的 $s$ 填 `P` 或 `S` 的方案数，转移则枚举 $i-1$ 位填什么。如果 $i-1$ 和 $i$ 位填 `PP`，则能够转移过来当且仅当 $b_i-b_{i-1}\in[-m,m]$，如果填 `SP`，则限制是 $b_i-(sum-b_{i-1})\in[-2m,2m]$，如果填 `PS` 则限制是 $b_{i-1}+b_i=sum$，如果为 `SS` 则限制是 $(sum-b_i)-(sum-b_{i-1})\in[-m,m]$。当然还有一些边界条件。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=5e3+5,P=998244353;
int T,n,f[N][2],ans;
long long b[N],sum,m;
char s[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>(s+1);
		for(int i=1;i<=n;i++)	cin>>b[i];
		b[n+1]=b[n+2]=b[n+3]=0;
		ans=0;
		unordered_set<long long> st;st.clear();
		for(int _=1;_<=n+1;_++){
			sum=b[_]+b[_-1];
			if(st.find(sum)!=st.end())	continue;
			st.insert(sum);
			f[1][0]=(b[1]>=-m&&b[1]<=m);
			f[1][1]=(b[1]==sum);
			if(s[1]=='P')	f[1][1]=0;
			if(s[1]=='S')	f[1][0]=0;
			for(int i=2;i<=n;i++){
				f[i][0]=f[i][1]=0;
				if(b[i]-b[i-1]>=-m&&b[i]-b[i-1]<=m)	f[i][0]=(f[i][0]+f[i-1][0])%P;
				if(b[i]-(sum-b[i-1])>=-2*m&&b[i]-(sum-b[i-1])<=2*m)	f[i][0]=(f[i][0]+f[i-1][1])%P;
				if(b[i-1]==sum-b[i])	f[i][1]=(f[i][1]+f[i-1][0])%P;
				if(sum-b[i]-(sum-b[i-1])>=-m&&sum-b[i]-(sum-b[i-1])<=m)	f[i][1]=(f[i][1]+f[i-1][1])%P;
				if(s[i]=='P')	f[i][1]=0;
				if(s[i]=='S')	f[i][0]=0;
			}
			if(b[n]==sum)	ans=(ans+f[n][0])%P;
			if(b[n]>=-m&&b[n]<=m)	ans=(ans+f[n][1])%P;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：TTpandaS (赞：3)

令 $f_{i,0/1}$ 表示第 $i$ 位为 $P/S$ 的方案数，由 $f_{i-1,0/1}$ 转移而来。

如果第 $i-1$ 位和第 $i$ 位为 $P,P$，那么 $b_i-b_{i-1}=a_i$，需要满足 $-m \leq a_i \leq m$。

如果第 $i-1$ 位和第 $i$ 位为 $P,S$，那么 $b_i+b_{i-1}=a_{i-1}+a_i+\sum a$，需要满足 $- 2 \times m \leq a_{i-1}+a_i \leq 2 \times m$。

如果第 $i-1$ 位和第 $i$ 位为 $S,P$，那么 $b_i+b_{i-1}=\sum a$。

如果第 $i-1$ 位和第 $i$ 位为 $S,S$，那么 $b_{i-1}-b_i=a_i$，需要满足 $-m \leq a_i \leq m$。

因此如果确定 $\sum a$ 就可以 $O(n)$ 进行 dp。

考虑如何确定 $\sum a$，也就是要找到第 $i-1$ 位和第 $i$ 位为 $S,P$，那么 $b_i+b_{i-1}=\sum a$。直接枚举 $i$ 即可。

---

## 作者：SnowTrace (赞：2)

简单题。

把这个后缀和拆成前缀作差。

我们首先想到，题目相当于它给你若干个式子形如：

$pre_{s_i} = k_i,pre_n-pre_{s_i} = k_i$，要构建出一个合法的序列。

假如说我们对于所有出现过的 $s_i$，都已经知道了 $pre_{s_i}$ 的值，那么判断是否能构造出一组解其实就是考虑将 $s_i$ 排序，然后判断相邻两项间是否存在 $|pre_{s_i}-pre_{s_{i-1}}|\leq m(s_i-s_{i-1})$ 不成立则无解。

那么我们想要知道每个 $pre_{s_i}$ 的值，其实相当于我们需要知道 $pre_n$ 的值，如果能固定 $pre_n$ 的值问题就能解决。

注意到，对于状态（题目中给出的字符串） $S$ 的任意可能情况，都存在一个 $i$ 使得 $s_i = P,s_{i+1} = S$，（我们这里不妨钦定边界情况中 $s_0 = P,s_{n+1} = S$），也就是说对于任意可能的情况，你都能固定 $pre_n$ 的值，也就是 $a_i+a_{i+1}$，因为这个相当于 $i$ 的前缀和 $i+1$ 的后缀拼到一起。

统计当前 $pre_n$，考虑选择最小的 $i$ 进行统计，钦定一段前缀都是 $P$，后面的任选。计数只需要记录上一个位置选了 $P$ 还是 $S$ 即可，转移很简单。

```cpp
/**/
#include<bits/stdc++.h>
using namespace std;
#define double long double
#define lowbit(x) (x&(-x))
#define int long long
const int mod = 998244353;
int dp[2005][2];int n,m;
int a[2005];char s[2005];
void solve(){
	cin >> n >> m;
	for(int i = 1;i<=n;i++)cin >> s[i];
	for(int i = 1;i<=n;i++)cin >> a[i];
	int ans = 0;
	for(int i = 1;i<=n;i++){
		if(s[i] !='P'){
			int sum = a[i-1]+a[i];
			for(int j =0;j<=n;j++)dp[j][0] = dp[j][1] = 0;
			//考虑钦定前缀一段是 p ，最后一个是 s，对后面的东西进行dp
			//1代表S 0 代表P 
			//根据一些观察我们只需要保证相邻的两项合法. 
			dp[i][1] = 1; 
			for(int j = i;j<n;j++){
				if(s[j+1]!='P'){
					int s1 = sum-a[j];
					int s2 = sum-a[j+1];
					if(abs(s1-s2)<=m){
						dp[j+1][1] = (dp[j+1][1]+dp[j][1])%mod;
					}
					s1 = a[j];
					if(s1 == s2){
						dp[j+1][1] = (dp[j+1][1]+dp[j][0])%mod;
					}
				}
				if(s[j+1]!='S'){
					int s1 = sum-a[j];
					int s2 = a[j+1];
					if(abs(s1-s2)<=2*m){
						dp[j+1][0] = (dp[j+1][0]+dp[j][1])%mod;
					}
					s1 = a[j];
					if(abs(s1-s2)<=m){
						dp[j+1][0] = (dp[j+1][0]+dp[j][0])%mod;
					}
				}
			}
			int s1 = sum-a[n];
			if(abs(s1-sum)>m)dp[n][1] = 0;
			if(a[n]!=sum)dp[n][0] = 0;			
			ans = (ans+dp[n][0]+dp[n][1])%mod; 
		}
		
		
		if(s[i] == 'S')break;
		if(abs(a[i]-a[i-1])>m)break;
	}
	int ok = 1;
	for(int i = 1;i<=n;i++)if(abs(a[i]-a[i-1])>m or s[i] == 'S')ok =0;
	ans = (ans+ok)%mod; 
	cout << ans << endl;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t;cin>> t;
	while(t--){
		solve();
	} 
	return 0;
}
```

---

## 作者：happybob (赞：0)

注意到一个事实是对于最终确定的 $s$ 和 $b$，我们总能得到 $a$ 序列总和。证明显然。

考虑枚举 $a$ 序列总和，必然是 $b_i+b_{i+1}$ 或 $b_1$ 或 $b_n$。然后进行 DP，记 $f_{i,0/1}$ 表示当前考虑了确定了字符串前 $i$ 个字符，且最后一个选的是前缀或后缀的方案数。转移考虑四种情况分类讨论，其中 PS 要求和为定值，SS 要求相减绝对值在 $m$ 内。其余都类似，可以做到 $O(1)$ 转移。总复杂度 $O(n^2)$。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <array>
#include <format>
#include <print>
#include <set>
using namespace std;

using ll = long long;

const int N = 2e3 + 5;
const ll MOD = 998244353ll;

int n, m, t;
string s;
array<ll, N> b;
array<array<ll, 2>, N> f;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	for (int _ = 1; _ <= t; _++)
	{
		cin >> n >> m >> s;
		s = " " + s;
		for (int i = 1; i <= n; i++) cin >> b[i];
		auto check = [&](const ll x)
			{
				return abs(x) <= m;
			};
		auto check2 = [&](const ll x)
			{
				return abs(x) <= 2ll * m;
			};
		set<ll> sum;
		ll ans = 0ll;
		for (int i = 1; i < n; i++) sum.insert(b[i] + b[i + 1]);
		sum.insert(b[1]), sum.insert(b[n]);
		for (auto& sh : sum)
		{
			for (int i = 1; i <= n; i++) f[i][0] = f[i][1] = 0ll;
			if (s[1] == 'P')
			{
				if (!check(b[1])) continue;
				f[1][0] = 1ll;
			}
			else if (s[1] == 'S')
			{
				if (b[1] != sh) continue;
				f[1][1] = 1ll;
			}
			else
			{
				f[1][0] = (check(b[1]));
				f[1][1] = (b[1] == sh);
			}
			for (int i = 2; i < n; i++)
			{
				// case1: SS
				if (check(b[i - 1] - b[i]) && s[i] != 'P') f[i][1] = f[i - 1][1];
				// case2: PS
				if (b[i - 1] + b[i] == sh && s[i] != 'P') f[i][1] = (f[i][1] + f[i - 1][0]) % MOD;
				// case3: SP
				if (check2(b[i] + b[i - 1] - sh) && s[i] != 'S') f[i][0] = f[i - 1][1];
				// case4: PP
				if (check(b[i] - b[i - 1]) && s[i] != 'S') f[i][0] = (f[i][0] + f[i - 1][0]) % MOD;
			}
			// case1: SS
			int i = n;
			if (check(b[i - 1] - b[i]) && s[i] != 'P' && check(b[i])) f[i][1] = f[i - 1][1];
			// case2: PS
			if (b[i - 1] + b[i] == sh && s[i] != 'P' && check(b[i])) f[i][1] = (f[i][1] + f[i - 1][0]) % MOD;
			// case3: SP
			if (b[i] == sh && check2(b[i] + b[i - 1] - sh) && s[i] != 'S') f[i][0] = f[i - 1][1];
			// case4: PP
			if (check(b[i] - b[i - 1]) && b[i] == sh && s[i] != 'S') f[i][0] = (f[i][0] + f[i - 1][0]) % MOD;
			ans = (ans + f[n][0] + f[n][1]) % MOD;
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---


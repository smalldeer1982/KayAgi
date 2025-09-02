# [ABC295F] substr = S

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc295/tasks/abc295_f

$ T $ 個のテストケースについて、数字のみからなる文字列 $ S $ と正整数 $ L,R $ が与えられるので、以下の問題を解いてください。

正整数 $ x $ に対して $ f(x)= $ ( $ x $ を ( 先頭に $ 0 $ を含まないように ) 書き下した文字列の連続部分列のうち $ S $ と合致するものの個数 ) と定義します。

例えば $ S= $ `22` であるとき、$ f(122)\ =\ 1,\ f(123)\ =\ 0,\ f(226)\ =\ 1,\ f(222)\ =\ 2 $ となります。

このとき、 $ \displaystyle\ \sum_{k=L}^{R}\ f(k) $ を求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ T\ \le\ 1000 $
- $ S $ は数字のみからなる長さ $ 1 $ 以上 $ 16 $ 以下の文字列
- $ L,R $ は $ 1\ \le\ L\ \le\ R\ <\ 10^{16} $ を満たす整数
 
### Sample Explanation 1

この入力には $ 6 $ 個のテストケースが含まれます。 - $ 1 $ つ目のケースは $ S= $ `22` $ ,L=23,R=234 $ です。 - $ f(122)=f(220)=f(221)=f(223)=f(224)=\dots=f(229)=1 $ - $ f(222)=2 $ - 以上より、このケースに対する答えは $ 12 $ です。 - $ 2 $ つ目のケースは $ S= $ `0295` $ ,L=295,R=295 $ です。 - $ f(295)=0 $ となることに注意してください。

## 样例 #1

### 输入

```
6
22 23 234
0295 295 295
0 1 9999999999999999
2718 998244353 9982443530000000
869120 1234567890123456 2345678901234567
2023032520230325 1 9999999999999999```

### 输出

```
12
0
14888888888888889
12982260572545
10987664021
1```

# 题解

## 作者：spider_oyster (赞：5)

不会期望的我瑟瑟发抖转向 F。

先简化一下，显然有 $\sum_{k=L}^{R} f_{k}=\sum_{k=0}^{R}f_{r}-\sum_{k=0}^{L}f_{l-1}$。

于是我们思考怎么求 $\sum_{k=0}^{x} f_{k}$。


------------


我们设字符串 $s$ 是 字符串 $t$ 的子串。

因为 $1\leq |s| \leq 16$，所以我们可以枚举一下 $s$ 在 $t$ 中的位置。

因为这里字符串都是由数字组成，所以我们可以二分一个数，让这个数把 $s$ 夹进去，$s$ 在这个位置的贡献就是二分的这个数 -1。

------------

我们拿样例 $1$ 举例：

$s=22,l=23,y=234$；我们此时 $solve(r)$：

$s$ 第一个字符在第二位：$?22$，最大能填进去的数是 $2$，此时有三个满足条件，$t=22(022),122,222$，所以这个位置的贡献就是 $3$。

$s$ 第一个字符在第三位：$22?$，最大能填进去的数是 $9$，此时有十个满足条件，$t=220,221,222,223...,229$，所以这个位置的贡献是 $10$。

于是 $solve(r)=3+10=13$。然后 $solve(l)=1$，因为只能填 $22$ 进去。
所以最终答案 $solve(r)-solve(l)=12$。

------------
我们再特判一下 $s_{0}=0$ 的情况，此时 $t$ 最前面必须填数。

设 $s$ 最后一个字符在第 $p$ 位，就少去了 $10^p$ 种方案。

------------
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n;
ll pw[17]; 
string s;

//由于二分 填进去的数 不方便统计答案，我们直接二分 方案数。 
ll find(ll x,ll l)
{
	//x=??????
	//t=???sss...s???
	//     l     r
	int r=l-s.size();
	if(s[0]=='0') x+=pw[r]; //减去 10^r 种方案，填进去的数就加 10^r 
	return x/pw[r]*pw[l]+stoll(s)*pw[r]+x%pw[r]; 
}

ll solve(ll x)
{
	ll res=0;
	for(int i=s.size();i<=16;i++)//枚举 s 第一位的位置 
	{
		if(find(0,i)>x) continue; 
		ll l=1,r=pw[16-s.size()],ans;//二分方案数 
		while(l<=r)
		{
			ll mid=l+r>>1;
			if(find(mid-1,i)<=x) ans=mid,l=mid+1;
			else r=mid-1;
    	}
    	res+=ans;
	}
	return res;
}

int main()
{
	pw[0]=1;for(int i=1;i<=16;i++) pw[i]=pw[i-1]*10;
	int t;cin>>t;
	while(t--)
	{
		ll l,r;cin>>s>>l>>r;
		cout<<solve(r)-solve(l-1)<<'\n';
	}
}
```


---

## 作者：Crane_w (赞：3)

### F

数位 dp

我们有一个经典的转换

$S(x) = \sum_{i =1}^xf(x)$

$Ans = S(R) - S(L-1)$

可以简化成求 $0-X$ 的 $f$ 值



#### Solution 1

我们来看一组数据 `s=49` 那么可以匹配 s 的数字是形如
\
`??49??` \
`????49`

我们枚举 $s$ 最低位位于第 $i$ 位 (代表$10^i$) ， 计算出每一位的贡献， 求和即可

怎么计算第 i 位有多少中 s 的匹配数呢？

设 $s$ 于第 2 位 

第 1 个 $s$ 的匹配为  `490`

第 23 个 $s$ 的匹配为 `2492`

第 114514 个 $s$ 的匹配为 `11451493`

......

发现了什么， 第 i 个匹配数删去 $s$ 后， 恰好为 $i - 1$

##### Solution 11

可以枚举每一位， 二分第 $i$ 个匹配数是否在范围内，求和即可

复杂度 $O(DlogD)$  $D$ means the number of digits in $s$ 

##### Solution 12

省去二分, 直接枚举求范围统计答案

复杂度 $O(D)$

```cpp
long long solve(string S, long long N){
  long long x = stoll(S);
  vector<long long> TEN(18);
  TEN[0] = 1;
  for (int i = 0; i < 17; i++){
    TEN[i + 1] = TEN[i] * 10;
  }
  int M = S.size();
  long long ans = 0;
  for (int i = 0; i <= 17 - M; i++){
    long long N2 = N;
    if (S[0] == '0'){
      N2 -= TEN[M + i];
    }
    N2 -= x * TEN[i];
    if (N2 > 0){
      long long q = N2 / TEN[M + i];
      long long r = N2 % TEN[M + i];
      ans += q * TEN[i];
      ans += min(r, TEN[i] - 1) + 1;
    }
  }
  return ans;
}
```



#### Solution 2 dfs

经典的数位 dp 板子，但是有一点变化， 匹配时要用到 kmp / Z 函数

```cpp
int n, m, l, r;
string s;
int num[maxn], len, f[20][20][20], kmp[maxn];
int dfs(int pos, int lim, int mt, int sum, int f0) {
	if (pos == 0) {
		return sum;
	}
	if (!lim && !f0 && f[pos][mt][sum] != -1) {
		return f[pos][mt][sum];
	}
	int up = (lim ? num[pos] : 9), res = 0;
	
	for (int i = 0; i <= up; i++) {
		int t1 = mt, t2 = sum;
		if (!f0 || i != 0) {
			while(t1 && s[t1 + 1] - '0' != i){
				t1 = kmp[t1];
			}
			if (s[t1 + 1] - '0' == i) t1++;
			if (t1 == n) t2++, t1 = kmp[t1];
		}
		res += dfs(pos - 1, lim && i==up, t1, t2, f0 && i==0);
	}
	if (!lim && !f0) {
		return f[pos][mt][sum]= res;
	} else return res;
}
int calc(int x) {
	len = 0;
	while(x) {
		num[++len] = x % 10;
		x /= 10; 
	}
	return dfs(len, 1, 0, 0, 1);
}
void solve() {
	memset(f, -1, sizeof(f));
	cin >> s >> l >> r;
	n = sz(s); s = " " + s;
	rep_(i, 0, n) kmp[i] = 0;
	for (int i = 2, j = 0; i <= n; i++) {
		while(j && s[j + 1] != s[i]) j = kmp[j];
		if (s[j + 1] == s[i]) j++;
		kmp[i] = j; 
	}
	cout << calc(r) - calc(l - 1) << endl;
}
```


---

## 作者：Unnamed114514 (赞：0)

首先，若直接枚举 $[l,r]$ 中的每一个元素，那么显然是超时的。观察到 $f(k)$ 与 $k$ 的数位有关，容易想到数位 dp。

按照数位 dp 的思路，记录 $now$ 表示当前枚举到的位数，$flg$ 表示是否可以取超过原数组 $now$ 这一位的值，同时，记录 $s$ 的长度为 $len$，假设当前枚举的是 $i$，我们来考虑一下枚举数位的第几种情况：

1. 如果当前枚举的这个数仅仅是前导 $0$，那么是不能进行匹配的，所以此时我们直接记录一个 $chk$ 表示是否是前导 $0$，那么此时我们枚举的情况就是 $chk=0$ 且 $i=0$。

2. 当前已经遍历完成了 $s$ 这整个字符串，那么此时就要开始下一次匹配，但是请注意，此时并不是从头开始匹配，因为可能有一个位置 $p$ 可以保证从 $i$ 开始往后的字符和从 $p$ 开始往后的字符全部相等，此时我们是从 $p$ 开始遍历。那么我们做一次字符串匹配就可以了，但是位数比较少，所以可以直接暴力匹配。所以想到记录 $tot$ 为当前匹配到的位数，那么此时 $tot=len$。同时，因为匹配完了，所以此时的答案还要加上我们新的 `dfs` 的方案数，所以我们开一个结构体存储二元组，分别表示方案数和答案。

3. 此时可以继续匹配，即 $i=s_{tot}$，那么直接匹配下一位即可。

4. 失配。此时同 $len=tot$ 的情况，直接在前面暴力跑一次字符串匹配即可。

综上，记录 `dfs(now,tot,flg,chk)` 表示当前位，当前匹配到的位数，是否可以超过原数该位对应的是，是否为前导 $0$，此时直接记忆化 $dp_{now,tot}$ 即可

令 $b$ 为进制，时间复杂度为 $O(b\times \log_{b}^4r)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int T,l,r,len,a[20];
struct node{
	int cnt,ans;
}dp[20][20];
bool vis[20][20];
node dfs(int now,int tot,bool flg,bool chk){
	if(!now)
		return node({1,(tot==len)});
	if(flg&&chk&&vis[now][tot])
		return dp[now][tot];
	node res=node({0,0});
	int up=(flg?9:a[now]);
	for(int i=0;i<=up;++i){
		if(!chk&&!i){
			node p=dfs(now-1,0,flg|(i<a[now]),0);
			res.cnt+=p.cnt,res.ans+=p.ans;
			continue;
		}
		if(tot==len){
			bool _=1;
			for(int j=1;j<len;++j){
				bool check=1;
				for(int i=0;i+j<len;++i)
					if(s[i]!=s[i+j]){
						check=0;
						break;
					}
				if(check&&i==s[len-j]-'0'){
					_=0;
					node p=dfs(now-1,len-j+1,flg|(i<a[now]),1);
					res.cnt+=p.cnt,res.ans+=p.ans+p.cnt;
					break;
				}
			}
			if(_){	
				node p=dfs(now-1,(i==s[0]-'0'),flg|(i<a[now]),1);
				res.cnt+=p.cnt,res.ans+=p.ans+p.cnt;
			}
		} else{
			if(i==s[tot]-'0'){
				node p=dfs(now-1,tot+1,flg|(i<a[now]),1);
				res.cnt+=p.cnt,res.ans+=p.ans;
			} else{
				bool _=1;
				for(int j=1;j<tot;++j){
					bool check=1;
					for(int i=0;i+j<tot;++i)
						if(s[i]!=s[i+j]){
							check=0;
							break;
						}
					if(check&&i==s[tot-j]-'0'){
						_=0;
						node p=dfs(now-1,tot-j+1,flg|(i<a[now]),1);
						res.cnt+=p.cnt,res.ans+=p.ans;
						break;
					}
				}
				if(_){	
					node p=dfs(now-1,(i==s[0]-'0'),flg|(i<a[now]),1);
					res.cnt+=p.cnt,res.ans+=p.ans;
				}
			}
		}
	}
	if(flg&&chk)
		dp[now][tot].cnt=res.cnt,dp[now][tot].ans=res.ans,vis[now][tot]=1;
	return res;
}
inline int solve(int x){
	int cnt=0;
	while(x){
		a[++cnt]=x%10;
		x/=10;
	}
	return dfs(cnt,0,0,0).ans;
}
signed main(){
	cin>>T;
	while(T--){
		cin>>s>>l>>r;
		len=s.size();
		memset(vis,0,sizeof(vis));
		cout<<solve(r)-solve(l-1)<<endl;
	}
	return 0;
}
```

---

## 作者：Alarm5854 (赞：0)

题意：求出 $[l,r]$ 内所有不含前导零的整数中包含数字串 $|S|$ 的次数之和。

提供一种和官方题解不一样的做法——数位 dp。

我们考虑到没有必要完整记录最后的 $|S|$ 位是什么，因为首先复杂度爆炸，其次是有很多状态是等价的，那么就可以考虑记录当前这个数与 $S$ 的匹配程度，这个，就可以用 KMP 算法实现，也就是说，先求出 border 数组，再进行记忆化搜索，就可以实现。

那么，记忆化搜索需要带进去什么参数呢？首先是位数 $cur$，这个是数位 dp 一定会用到的。然后是与本题有关的匹配程度 $sm$，以及数位 dp 也很可能用到的两个布尔变量记录是否为前导零，以及是否与当前数相等。

考虑转移：枚举下一位是什么数字，然后相应地去改变匹配程度，如果发现匹配程度达到了 $|S|$，那么说明匹配到了，给答案加上之后数字的种类数并把匹配程度降低为其 border。

最后求一个区间的满足条件的数的数量很容易想到拆成两端前缀去求。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll T,n,l,r,len,num[22],pw[22],nxt[22],a[22];
char s[22];
ll f[22][22][2][2];
ll dfs(ll cur,ll sm,ll pre,ll eq){
	ll& res=f[cur][sm][pre][eq];
	if(~res)
		return res;
	res=0;
	if(cur>len)//贡献已经提前计算过了
		return 0;
	for(ll i=0;i<10;++i){
		if(eq&&i>a[cur])
			break;
		if(pre&&!i)//前导零是不会对匹配程度造成贡献的
			res+=dfs(cur+1,sm,pre,0);
		else{
			int j=sm;
			while(j&&(s[j+1]^48)!=i)
				j=nxt[j];
			if((s[j+1]^48)==i)
				++j;
			if(j==n){
				j=nxt[j];
				if(eq&&i==a[cur])//累计贡献
					res+=num[cur+1]+1;
				else
					res+=pw[len-cur];
			}
			res+=dfs(cur+1,j,0,eq&&(i==a[cur]));
		}
	}
	return res;
}
ll calc(ll x){
	if(!x)
		return 0;
	memset(f,-1,sizeof(f));
	len=0;
	while(x){
		a[++len]=x%10;
		x/=10;
	}
	reverse(a+1,a+len+1);
	num[len+1]=0;
	for(ll i=len;i;--i)//预处理卡着上限的最后的len-i+1位的可填数数量减一（有零）
		num[i]=num[i+1]+pw[len-i]*a[i];
	return dfs(1,0,1,1);
}
void solve(){
	scanf("%s%lld%lld",s+1,&l,&r);
	n=strlen(s+1);
	for(int i=2,j=0;i<=n;++i){
		while(j&&s[i]!=s[j+1])
			j=nxt[j];
		if(s[i]==s[j+1])
			++j;
		nxt[i]=j;
	}
	ll x=calc(r);
	ll y=calc(l-1);
	printf("%lld\n",x-y);
}
int main(){
	pw[0]=1;
	for(ll i=1;i<=16;++i)//预处理最后i位随便填的数量
		pw[i]=pw[i-1]*10;
	scanf("%lld",&T);
	while(T--)
		solve();
	return 0;
}
```

---


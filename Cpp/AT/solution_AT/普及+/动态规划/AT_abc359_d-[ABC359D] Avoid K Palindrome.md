# [ABC359D] Avoid K Palindrome

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc359/tasks/abc359_d

`A`, `B`, `?` からなる $ N $ 文字の文字列 $ S $ が与えられます。

正整数 $ K $ が与えられます。 `A`, `B` からなる文字列 $ T $ が次の条件を満たすとき、$ T $ は**良い文字列**であるということにします。

- $ T $ の長さ $ K $ の連続する部分文字列で、回文であるものが**存在しない**。
 
$ S $ に含まれる `?` の個数を $ q $ 個とします。 $ q $ 個の `?` をそれぞれ `A`, `B` のどちらかに置き換えて得られる文字列は $ 2\ ^\ q $ 通りありますが、その中に良い文字列がいくつあるか求めてください。

ただし、答えは非常に大きくなる場合があるので、$ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 2\leq\ K\leq\ N\leq\ 1000 $
- $ K\leq\ 10 $
- $ S $ は `A`, `B`, `?` からなる文字列
- $ S $ の長さは $ N $
- $ N,K $ は整数
 
### Sample Explanation 1

与えられた文字列の中に `?` は $ 2 $ 個あります。 $ 2 $ 個の `?` をそれぞれ `A`, `B` のどちらかに置き換えて得られる文字列は次の $ 4 $ 通りあります。 - `ABAAABA` - `ABAABBA` - `ABBAABA` - `ABBABBA` このうち、最初の `ABAAABA` 以外の $ 3 $ つの文字列は、長さ $ 4 $ の回文 `ABBA` を連続する部分文字列として含むため、良い文字列ではありません。 よって、`1` を出力してください。

### Sample Explanation 2

良い文字列の個数を $ 998244353 $ で割った余りを求めることに注意してください。

### Sample Explanation 3

`?` をどのように置き換えても良い文字列にならないこともあります。

## 样例 #1

### 输入

```
7 4
AB?A?BA```

### 输出

```
1```

## 样例 #2

### 输入

```
40 7
????????????????????????????????????????```

### 输出

```
116295436```

## 样例 #3

### 输入

```
15 5
ABABA??????????```

### 输出

```
0```

## 样例 #4

### 输入

```
40 8
?A?B??B?B?AA?A?B??B?A???B?BB?B???BA??BAA```

### 输出

```
259240```

# 题解

## 作者：WanderingTrader (赞：12)

基础状压 dp。

由于 $k\le 10$，且每个位置上只可能有两种情况，放 A 或放 B，因此考虑状压 dp.

设 $f(i,p)$ 表示已经放完前 $i$ 个字符，其中最后 $k$ 个的放置情况为二进制数 $p$ 的方案数，令放 A 为 $0$，放 B 为 $1$.

转移时如果 $i<k$，则必然不可能出现长度为 $k$ 的回文串。如果 $i\ge k$，判断 $p$ 在二进制下（只看最低的 $k$ 位）是不是一个回文数即可。

一些辅助函数：
```cpp
// 考虑通配符的字符比较，相同为true，不同为false
bool cmp(char a,char b)
{
    if(a=='?'||b=='?') return true;
    return a==b;
}
// 判断p在二进制下的最低k位是否构成回文数
bool is_palin(int p)
{
    for(int i=0;i<(k>>1);++i)
    {
        if((p>>i&1) != (p>>(k-i-1)&1))
            return false;
    }
    return true;
}
```

全部代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=1e3+5;
const int K=1030;
const LL MOD=998244353;
int n,k;
LL f[N][K],ans;
int ptn;
string s;
bool cmp(char a,char b)
{
    if(a=='?'||b=='?') return true;
    return a==b;
}
bool is_palin(int p)
{
    for(int i=0;i<(k>>1);++i)
    {
        if((p>>i&1) != (p>>(k-i-1)&1))
            return false;
    }
    return true;
}
int main()
{
    cin>>n>>k>>s;
    ptn=(1<<k)-1;
    f[0][0]=1;
    for(int i=1;i<=n;++i)
        for(int p=0;p<=ptn;++p) if(f[i-1][p])
            for(int c=0;c<2;++c) if(cmp(c+'A',s[i-1]))
            {
                if(i<k) (f[i][((p<<1)&ptn)|c]+=f[i-1][p])%=MOD;
                else
                {
                    int PTN=((p<<1)&ptn)|c;
                    if(!is_palin(PTN))
                        (f[i][PTN]+=f[i-1][p]) %= MOD;
                }
            }
    for(int j=0;j<=ptn;++j)
        (ans+=f[n][j]) %= MOD;
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：zengziqvan (赞：5)

## 题目大意

给你一个长度为 $n$ 的字符串 $S$，其中只包含 `A`、`B`、`?` 三种字符，将所有的 `?` 字符换成 `A` 或 `B` 字符。可以得到一个新的字符串 $T$。若 $T$ 的任意长度为 $k$ 的子串都不是回文的，则称 $T$ 是好的。求一共有多少种替换 `?` 字符的方案，使替换完的字符串是好的。

## 题目分析

设 $dp_{i,S}$ 表示考虑到第 $i$ 位，最后 $k$ 位填的状态为 $S$ 的方案数。

由于 $k$ 只有 $10$，故我们可以用二进制状压来映射 $k$ 位的只含 `A`、`B` 的所有的字符串，并预处理出所有二进制数对应的字符串是否是回文的，可以用 dfs 找。

```c++
void dfs(int x,string S,int res) {
	if(x>k) {
		mp[S]=res;//map映射
		ck[res]=S;
		can[res]=!check(S);//can判定是否是回文的（不是回文则为 1）
		return ;
	}
	res<<=1;
	string T=S+"A";
	dfs(x+1,T,res);
	res|=1;
	T=S+"B";
	dfs(x+1,T,res);
}
```
为了下文叙述方便，这里设所有满足 `can` 为 $1$ 的长度为 $k$ 的二进制的集合为 $P$。

初始状态： $\forall s\in P,dp_{k,s}=1$。其他为 $0$。

转移方程：$dp_{i,S}=dp_{i-1,(S>>1)|(1<<(k-1))}+dp_{i-1,(S>>1)}$。

答案：$\sum_{s\in P} dp_{n,s}$。

**注意**：上述转移必须**切合实际**，也就是说状态 $S$ 要满足原串的限制。

```c++
#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
//#define int long long
//#define double long double
#define FOR(i,l,r) for(int i=l;i<=r;++i)
#define ROF(i,r,l) for(int i=r;i>=l;--i)
#define mkp make_pair
#define fr first
#define se second
#define pb push_back
#define cmax(a,b) a=max(a,b)
#define cmin(a,b) a=min(a,b)
using namespace std;
void IOS() {
	ios::sync_with_stdio(false);
	cin.tie(0);
}
void Document() {
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
inline int read(){
	int s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+(ch^48);ch=getchar();}
	return s*w;
}
inline void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
const int Mo=998244353;
int n,k,dp[1100][(1<<10)+1],can[(1<<10)+1];
string s;
map<string,int>mp;//用来映射
map<int,string>ck;
bool check(string s) {//判定是否回文
	int z=k/2;
	s=" "+s;
	for(int i=1;i<=z;++i) 
		if(s[i]!=s[k-i+1]) return 0;
	return 1;
}
void dfs(int x,string S,int res) {
	if(x>k) {
		mp[S]=res;
		ck[res]=S;
		can[res]=!check(S);
		return ;
	}
	res<<=1;
	string T=S+"A";
	dfs(x+1,T,res);
	res|=1;
	T=S+"B";
	dfs(x+1,T,res);
}
bool pre(int l,int r,string t) {//与原串对比判定可行性
	t=" "+t;
	for(int i=1;i<=k;++i,++l) {
		if(s[l]=='?') continue;
		if(s[l]!=t[i]) return 0;
	}
	return 1;
}
main() {
	cin>>n>>k;
	cin>>s;s=" "+s;
	dfs(1,"",0);
	FOR(i,1,(1<<k)-1) if(can[i]&&pre(1,k,ck[i])) dp[k][i]=1;
	FOR(i,k+1,n) {
		FOR(S,1,(1<<k)-1) {
			if(!can[S]) continue;
			if(!pre(i-k+1,i,ck[S])) continue;
			int T=S>>1;
			if(can[T]&&(s[i-k]!='B')) (dp[i][S]+=dp[i-1][T])%=Mo;
			T|=(1<<(k-1));
			if(can[T]&&(s[i-k]!='A')) (dp[i][S]+=dp[i-1][T])%=Mo;
		}
	}
	int ans=0;
	FOR(S,1,(1<<k)-1) {
		if(can[S]) (ans+=dp[n][S])%=Mo;//不合法的没转移过来，所以可以不用判可行性。
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Genius_Star (赞：2)

### 思路：

注意到 $k \le 10$，考虑状压，令 `A` 为 $0$，`B` 为 $1$，`?` 为 $2$。

令 $dp_{i,S}$ 表示对于前 $i$ 位时后面 $k$ 位状态为 $S$ 的方案数，令 $T$ 表示当前全状态，则：

$$S=(T_{i-k+1} T_{i-k+2} \cdots T_i)_2$$

因为状态较为复杂，考虑刷表转移。

即可以对于当然的 $S$，求出下一个字符填 $c$ 会使得 $S'$ 为回文串，如下：

$$dp_{i+1,\lfloor \frac{S}{2} \rfloor + 2^{c \operatorname{xor} 1}} \gets dp_{i+1,\lfloor \frac{S}{2} \rfloor + 2^{k-1} \times (c \operatorname{xor} 1)} + dp_{i,S}(T_{i+1} \ne c)$$

若随意填都不会是回文串，可以全部转移：

$$\begin{cases} dp_{i+1,\lfloor \frac{S}{2} \rfloor} \gets dp_{i+1,\lfloor \frac{S}{2} \rfloor} + dp_{i,S} & T_{i+1} = 0 || T_{i+1}=2 \\ dp_{i+1,\lfloor \frac{S}{2} \rfloor + 2^{k-1}} \gets dp_{i+1,\lfloor \frac{S}{2} \rfloor + 2^{k-1}} + dp_{i,S} & T_{i+1}=1 || T_{i+1} = 2\end{cases}$$

这是对于 $i>k$ 的情况，对于 $i=k$ 和 $i<k$ 的情况基本类似，这里就不多说了。

时间复杂度为 $O(Nk2^k)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef long long ll;
const ll N=1050,mod=998244353;
mt19937 R(time(0));
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,k,ans;
char a[N];
ll dp[N][N];
string s,t,g;
ll check(ll x,ll i){
	ll h=min(i,k),sum=0;
	bool F=(h==k);
	s="";
	while(h--){
		sum++;
		if(sum!=1||!F)
		  s+=(x&1ll)+'0';
		x>>=1ll;
	}
	g=s;
	s=g+"1";
	t=s;
	reverse(t.begin(),t.end());
//	cerr<<i<<' '<<s<<' '<<t<<'\n';
	if(s==t)
	  return 1;
	s=g+"0";
	t=s;
	reverse(t.begin(),t.end());
	if(s==t)
	  return 0;
	return 2;	
}
int main(){
	n=read(),k=read();
	scanf("%s",a+1);
	if(a[1]=='A'||a[1]=='?')
	  dp[1][0]=1;
	if(a[1]=='B'||a[1]=='?')
	  dp[1][1]=1;
	for(int i=1;i<n;i++){
		for(int j=0;j<(1ll<<k);j++){
			if(!dp[i][j])
			  continue;
			if(i+1<k){
				if(a[i+1]=='A'||a[i+1]=='?')
				  dp[i+1][j]=Add(dp[i+1][j],dp[i][j]);
				if(a[i+1]=='B'||a[i+1]=='?')
				  dp[i+1][j+(1ll<<i)]=Add(dp[i+1][j+(1ll<<i)],dp[i][j]);
			}
			else if(i+1==k){
				ll op=check(j,i);
				if(op==2){
					if(a[i+1]=='A'||a[i+1]=='?')
					  dp[i+1][j]=Add(dp[i+1][j],dp[i][j]);
					if(a[i+1]=='B'||a[i+1]=='?')
					  dp[i+1][j+(1ll<<i)]=Add(dp[i+1][j+(1ll<<i)],dp[i][j]);			
				}
				else{
					if(a[i+1]-'A'!=op){
						op^=1ll;
						dp[i+1][j+(op<<i)]=Add(dp[i+1][j+(op<<i)],dp[i][j]);
					}
				}				
			}
			else{
				ll op=check(j,i);
				if(op==2){
					if(a[i+1]=='A'||a[i+1]=='?')
					  dp[i+1][j>>1ll]=Add(dp[i+1][j>>1ll],dp[i][j]);
					if(a[i+1]=='B'||a[i+1]=='?')
					  dp[i+1][(j>>1ll)+(1ll<<(k-1))]=Add(dp[i+1][(j>>1ll)+(1ll<<(k-1))],dp[i][j]);			
				}
				else{
					if(a[i+1]-'A'!=op){
						op^=1ll;
						dp[i+1][(j>>1ll)+(op<<(k-1))]=Add(dp[i+1][(j>>1ll)+(op<<(k-1))],dp[i][j]);
					}
				}	
			}
		}
	}
	for(int i=0;i<(1ll<<k);i++)
	  ans=Add(ans,dp[n][i]);
	write(ans);
	return 0;
}
```

---

## 作者：_AyachiNene (赞：2)

~~难点在于隐藏的数据范围。~~
# 思路：
$A$ 和 $B$ 可以用 $0$ 或 $1$ 来表示，看到 $k\leq10$ 容易想到状压 dp。设 $f_{i,j}$ 表示 $s$ 的前 $i$ 个字符，最后 $k$ 个状态为 $j$ 的方案数。转移显然，把上个状态的后 $k-1$ 位提出来，在接上当前这一位，接得到当前状态，在判下可行性即可。对于实现的细节，我把合法的状态先预处理出来，在 dfs 把初值预处理出来就好了。
# Code:
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'a'||ch>'z')ch=getch();while(ch>='a'&&ch<='z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
const int mod=998244353;
int n,m;
string s;
int ans;
int f[1145][1<<11];
int vis[1<<11];
void dfs(int x,int sub)
{
	if(x>m)
	{
		if(vis[sub]) f[m][sub]=1;
		return;
	}
	if(s[x]=='?') dfs(x+1,sub|(1<<(x-1))),dfs(x+1,sub);
	else
	{
		if(s[x]=='A') dfs(x+1,sub);
		else dfs(x+1,sub|(1<<(x-1)));
	}
}
signed main()
{
	cin>>n>>m>>s;
	s=' '+s;
	for(int i=0;i<(1<<m);i++)
	{
		int flag=1;
		for(int j=1;j<=m;j++)
			if((bool)(i&(1<<(j-1)))!=(bool)(i&(1<<(m-j)))) flag=0;
		vis[i]=!flag;
	}
	dfs(1,0);
	for(int i=m+1;i<=n;i++)
		for(int j=0;j<(1<<m);j++)
		{
			if(!vis[j]) continue;
			int sub=0;
			for(int k=2;k<=m;k++) if(j&(1<<(k-1))) sub|=(1<<(k-2));
			if((s[i]=='?'||s[i]=='A')&&vis[sub]) f[i][sub]=(f[i][sub]+f[i-1][j])%mod;
			if((s[i]=='?'||s[i]=='B')&&vis[sub|(1<<(m-1))]) f[i][sub|(1<<(m-1))]=(f[i][sub|(1<<(m-1))]+f[i-1][j])%mod;
		}
	int ans=0;
	for(int i=0;i<(1<<m);i++)
		if(vis[i]) ans=(ans+f[n][i])%mod;
	write(ans);
	flush();
}

```

---

## 作者：joe_zxq (赞：1)

# Part 1 - 题目翻译

给你一个长度为 $N$ 的字符串 $S$，由字符 `A`、`B` 和 `?` 组成。

同时给你一个正整数 $K$。如果满足以下条件，由 `A` 和 `B` 组成的字符串 $T$ 将被视为**好字符串**：

- 在 $T$ 中，**没有**长度为 $K$ 的连续子串是回文字符串。

设 $q$ 是 $S$ 中的 `?` 的个数。将 $S$ 中的每个 `?` 替换为 `A` 或 `B`，可以得到 $2^q$ 个字符串。请找出其中有多少个字符串是好字符串。

这个数目可能非常大，所以请对 $998244353$ 取模。

# Part 2 - 算法思路

因为 $K$ 的范围比较小，考虑状压 DP。

令 $dp_{i,s}$ 为填完了 $i$ 位，从第 $i-K+1$ 位到第 $i$ 位的子串是 $s$ 的好字符串数量。

对于每一个 $i$，枚举 $s$，首先判断这个字符串是否可以放在这里，即是否与 $S$ 中的字符冲突。然后判断 $s$ 是否回文。

如果既不冲突又不回文，考虑 DP 的转移。根据 $s$ 计算上一位的子串 $s'$，即将 $s$ 的最后一位删掉，根据 $S_{i-K}$ 判断在前面加上 `A`、`B` 还是两者皆可。那么 DP 的转移就是 $dp_{i,s} = dp_{i-1,s'}$。

最后答案就是所有第 $N$ 位的 DP 值之和。

# Part 3 - 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll k, n;
const ll mod = 998244353;
string s;
map<string, ll> dp[1024];

int main() {

	cin >> n >> k >> s;
	s = "?" + s;
	for (ll i = k; i <= n; i++) {
		for (ll j = 0; j <= (1 << k) - 1; j++) {
			string r = "";
			for (ll t = k; t >= 1; t--) {
				if (j & (1 << t - 1)) {
					r += 'B';
				} else {
					r += 'A';
				}
			}
			bool ok = 1, ok2 = 0;
			for (ll t = i - k + 1; t <= i; t++) {
				if (s[t] != '?' && s[t] != r[t - (i - k + 1)]) {
					ok = 0;
					break;
				}
			}
			
			if (!ok) {
				continue;
			}
			for (ll i = 0; i < k; i++) {
				if (r[i] != r[k - i - 1]) {
					ok2 = 1;
					break;
				}
			}
			if (!ok2) {
				continue;
			}
			string qa = r, qb = r;
			qa.pop_back();
			qb.pop_back();
			qa = 'A' + qa;
			qb = 'B' + qb;
			if (i == k) {
				dp[i][r] = 1;
				continue;
			}
			if (s[i - k] == '?') {
				dp[i][r] += dp[i - 1][qa] + dp[i - 1][qb];
				dp[i][r] %= mod;
			} else if (s[i - k] == 'A') {
				dp[i][r] += dp[i - 1][qa];
				dp[i][r] %= mod;
			} else {
				dp[i][r] += dp[i - 1][qb];
				dp[i][r] %= mod;
			}
		}
	}
	ll ans = 0;
	for (ll j = 0; j <= (1 << k) - 1; j++) {
		string r = "";
		for (ll t = k; t >= 1; t--) {
			if (j & (1 << t - 1)) {
				r += 'B';
			} else {
				r += 'A';
			}
		}
		ans += dp[n][r];
		ans %= mod;
	}
	cout << ans;

	return 0;
}
```

---

## 作者：Liyunze123 (赞：1)

# 思路
我们设 `A` 是二进制 $0$，`B` 是二进制 $1$。

考虑 DP。

设 $dp_{i,j}$ 表示前 $i$ 个字母，最后 $k$ 个字母的二进制表示是 $j$，没有回文串的方法数。

转移分情况考虑。

对于所有的 $x$ 满足 $dp_{i-1,x}$ 有值，会转移到 $dp_{i,2x|y\bmod2^k}$，$|$ 指位运算或，如果 $s_i$ 是字母，$y$ 是对应的 $0$ 或 $1$，否则，$y$ 可以等于零也可以等于一。

当 $i \ge k$ 时，如果 $2x|y\bmod2^k$ 的二进制是回文串，转移失败。否则 $dp_{i,2x|y\bmod2^k}$ 加上 $dp_{i-1,x}$。

初始化：$dp_{0,0}=1$。
# 代码
```
#include<bits/stdc++.h>
#define buyao using
#define wan namespace
#define yuanshen std
buyao wan yuanshen;
//祝加入team75739的人AKIOI
const int mod=998244353,N=1<<11;
int n,k,dp[N][N],a[N],t[N][N],b[N][N],p[N],ans;
char s[N];
int check(int i){
	int t=0,a[20]={0};
	while(i)a[++t]=i%2,i/=2;
	for(int w=1,x=k;w<x;w++,x--)if(a[w]!=a[x])return 1;
	return 0;
}
int main(){
    scanf("%d%d%s",&n,&k,s),p[0]=1,dp[0][0]=1;
    for(int w=0;w<n;w++)if(s[w]!='?')a[w+1]=s[w]-'A';else a[w+1]=2;
    for(int w=1;w<=n;w++){
    	if(w<k)
    		if(a[w]==2)for(int x=1;x<=p[w-1];x++)t[w][++p[w]]=t[w-1][x]<<1,t[w][++p[w]]=(t[w-1][x]<<1)|1,dp[w][t[w][p[w]-1]]+=dp[w-1][t[w-1][x]],dp[w][t[w][p[w]]]+=dp[w-1][t[w-1][x]];
    		else for(int x=1;x<=p[w-1];x++)t[w][++p[w]]=(t[w-1][x]<<1)|a[w],dp[w][t[w][p[w]]]+=dp[w-1][t[w-1][x]];
		else
			if(a[w]==2)
				for(int x=1;x<=p[w-1];x++){
					int d=(t[w-1][x]<<1)%(1<<k);
					if(check(d)){
						if(!b[w][d])t[w][++p[w]]=d,b[w][d]=1;
						dp[w][d]+=dp[w-1][t[w-1][x]],dp[w][d]%=mod;
					}
					d|=1;
					if(check(d)){
						if(!b[w][d])t[w][++p[w]]=d,b[w][d]=1;
						dp[w][d]+=dp[w-1][t[w-1][x]],dp[w][d]%=mod;
					}
				}
			else for(int x=1;x<=p[w-1];x++){
					int d=((t[w-1][x]<<1)|a[w])%(1<<k);
					if(check(d)){
						if(!b[w][d])t[w][++p[w]]=d,b[w][d]=1;
						dp[w][d]+=dp[w-1][t[w-1][x]],dp[w][d]%=mod;
					}
				}
	}
	for(int w=0;w<(1<<k);w++)ans=(ans+dp[n][w])%mod;
	printf("%d",ans);
    return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

状压 dp 题。

### 思路

对于每个字符 $s_i$：

- 如果 $s_i$ 不为 `A`，那么它可以是 `B`。我们要把这个状态算进去。
- 如果 $s_i$ 不为 `B`，那么它可以是 `A`。我们要把这个状态算进去。

令 $dp_{i,j}$ 表示当前枚举到了第 $i$ 位，往前 $k$ 位的二进制表示为一个 01 串 $t$，这个 01 串十进制表示为 $j$。若 $s$ 的从 $i$ 倒数第 $p$ 位为 `A`，则 $t$ 的倒数第 $p$ 位为 $0$，反之为 $1$。显然 $j<2^k$。

每次我们新加进来一个字符，都要把最前面的字符踢掉，然后把新的字符补进来。我们可以 $\operatorname{O}(1)$ 地完成这个操作。令上一个 $j$ 为 $j_1$，新更新的 $j$ 为 $j_2$，则 $j_2=(2\times j_1)-2^k+\operatorname{get}(ch)$，其中 $ch$ 为当前的字符，$\operatorname{get}$ 函数的返回值为：

- 若 $ch$ 不为 `A`，$\operatorname{get}$ 函数返回 $1$。
- 若 $ch$ 不为 `B`，$\operatorname{get}$ 函数返回 $0$。

特别地，如果 $ch$ 为 `?`，说明两种都可能，两种都要计算。

状态转移方程显然，因为可能有多个原来不相同的 $j_1$ 转移到相同的 $j_2$，所以：$dp_{i,j_2}=(dp_{i-1,j_1}+dp_{i,j_2})\bmod 998244353$。



注意到我们需要要求它不为回文串。因此在程序开始时，我们要预处理出所有可能的回文串对应的 $j$ 值，如果我们发现转移出的 $j_2$ 代表的字符串是回文串，我们要把它舍去。

### 代码

```
#include<iostream>
#define int long long
using namespace std;
int dp[1005][1055],whe[1055];
int n,k;
string s;
int mier[]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};
int get(int _){
	if(_%2)return _/2+1;
	else return _/2;
}
char ask(int y){
	if(y%2)return 'B';
	return 'A';
}
int reget(char ch){
	if(ch=='A')return 0;
	return 1;
}
void init(){
	int p=get(k);
	for(int i=0;i<=mier[k]-1;i++){
		string t="                    ";
		int q=i,cnt=k;
		for(int i=1;i<=k;i++){
			t[cnt--]=ask(q%2);
			q/=2;
		}
		bool f=1;
		for(int i=1;i<=p;i++){
			if(t[i]!=t[k-i+1]){
				f=0;
				break;
			}
		}
		if(f==1)whe[i]=1;
	}
}
signed main(){
	cin>>n>>k>>s;s=' '+s;
	init();
	if(s[1]!='B')dp[1][0]=1;
	if(s[1]!='A')dp[1][1]=1;
	for(int i=2;i<k;i++){
		for(int j=0;j<mier[k];j++){
			int y=0;
			if(s[i]!='B')dp[i][j<<1]=(dp[i][j<<1]+dp[i-1][j])%998244353;
			if(s[i]!='A')dp[i][(j*2)+1]=(dp[i][(j*2)+1]+dp[i-1][j])%998244353;
		}
	}
	for(int i=k;i<=n;i++){
		for(int j=0;j<mier[k];j++){
			int y=0;
			if(s[i]!='B'&&(!whe[(j*2)&(mier[k]-1)]))dp[i][(j*2)&(mier[k]-1)]=(dp[i][(j*2)&(mier[k]-1)]+dp[i-1][j])%998244353;
			if(s[i]!='A'&&(!whe[((j*2)+1)&(mier[k]-1)]))dp[i][((j*2)+1)&(mier[k]-1)]=(dp[i][((j*2)+1)&(mier[k]-1)]+dp[i-1][j])%998244353;
		}
	}
	int ans=0;
	for(int i=0;i<mier[k];i++)ans+=dp[n][i];
	cout<<ans%998244353;
	return 0;
}
```

### 提示

- 代码中运用了位运算，是一种极好的卡常方法。
- 本题答案较大，需要开 `long long`。

### 时间复杂度

预处理是 $\operatorname{O}(2^kk)$ 的。我们枚举字符串的十进制值是 $\operatorname{O}(2^k)$ 的，判断回文是 $\operatorname{O}(k)$ 的。

dp 是 $\operatorname{O}(2^kn)$ 的。首先我们枚举 $i$，是 $\operatorname{O}(n)$ 的。然后我们枚举 $j_1$，是$\operatorname{O}(2^k)$ 的。

总体复杂度为 $\operatorname{O}(2^kn)$，可以通过本题。

---

## 作者：hh弟中弟 (赞：0)

### [AT_abc359_d [ABC359D] Avoid K Palindrome](https://www.luogu.com.cn/problem/AT_abc359_d)
看到 $k\le 10$，考虑状压，字母 `A` 代表 $0$，字母 `B` 代表 $1$，`?` 都可以代表，设 $f_{i,s}$ 表示到达第 $i$ 个位置，最后 $k$ 个字母的状态为 $s$ 时的方案数。\
显然有转移方程 $f_{i,s}=f_{i-1,\frac{s}{2}+2^{k-1}}+f_{i-1,\frac{s}{2}}$，继承了前 $k-1$ 位的状态，check 一下状态 $s$ 是否合法即可，具体实现看代码。
```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=2e3+50,mod=998244353;
char st[N];
int n,k,f[N][N];
bool vis[N];
inline int mo(int x){return x<0?(x%mod+mod)%mod:(x>=mod?x%mod:x);}
inline bool check(int l,int r,int s){
	int x=s;
	for(int i=r;i>=l;--i){
		int zc=s&1;s>>=1;
		if(st[i]=='?')continue;
		if(st[i]-'A'!=zc)return false;
	}
	return (!vis[x]);
}
signed main(){
	// freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
	std::cin>>n>>k>>(st+1);
	if(k==1){std::cout<<0<<'\n';exit(0);}
	vis[0]=1;
	for(int i=0;i<(1<<k)-1;++i){
		int a[11],b[11];
		for(int i=1;i<=k;++i)a[i]=b[i]=0;
		int len=0,x=i;
		while(x)len++,a[len]=b[len]=(x&1),x>>=1;
		len=k;
		std::reverse(b+1,b+len+1);
		int tot=0;
		for(int j=1;j<=len;++j)tot+=a[j]==b[j];
		if(tot==len)vis[i]=1;
		f[k][i]=check(1,k,i);
	}
	int ans=0;
	for(int i=k+1;i<=n;++i)
		for(int s=0;s<(1<<k)-1;++s)
			if(check(i-k+1,i,s)){
				int x=s>>1;
				f[i][s]=mo(f[i][s]+f[i-1][x+(1<<k-1)]+f[i-1][x]);
			}
	for(int s=0;s<(1<<k)-1;++s)ans=mo(ans+f[n][s]);
	std::cout<<ans<<'\n';
}
```

---

## 作者：Sorato_ (赞：0)

# ABC359D Avoid K Palindrome

## 题目大意

给定一个长度为 $N$ 的字符串 $S$，由 `A`，`B` 或 `?` 组成。可以在 `?` 处任意填 `A` 或 `B`。再给定一个常数 $K$，问有多少种填法可以使 $S$ 的每一个长度为 $K$ 的子串都不是回文串，即成为一个好串。

## Solve

注意到 $K\leq10$，考虑暴力 $\text{DFS}$ 或状压 $\text{DP}$。由于状态转移比较直观，这里用状压。

令 $dp_{i,s}$ 表示 $S$ 的前 $i$ 位是好串，以 $i$ 结尾的长度为 $K$ 的子串状态为 $s$ 的方案数。$s$ 二进制下的第 $j$ 位为 $1$ 表示 $S$ 对应的这一位是 `A`，否则是 `B`。

对于遍历到的 $i$，枚举第 $i-1$ 位的状态 $now$，进行状态转移。

- 若 $S_i$ 为 `A` 或 `?`，则第 $i$ 位的状态 $nxt$ 为 $now$ 删去最左侧的一位，左移一位，再将对应 $S_i$ 的最右侧的一位变为 $1$，二进制表示为 `now<<1&(1<<k)-1|1`。
- 若 $S_i$ 为 `B` 或 `?`，则第 $i$ 位的状态 $nxt$ 为 $now$ 删去最左侧的一位，左移一位，二进制表示为 `now<<1&(1<<k)-1`。

若 $nxt$ 不是回文，则令 $dp_{i,nxt}$ 加上 $dp_{i-1,now}$。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
#define mod 998244353
int n,m,dp[1010][1024]={1},res,ans,k;
char s[1010];
bool f[1024];//预处理出哪些状态不是回文串
signed main()
{
	n=read();m=1<<(k=read());
	scanf("%s",s+1);
	for(int now=0;now<m;now=-~now)
	{
		f[now]=0;
		for(int i=0;i<(k>>1);i=-~i)
			if((now>>i&1)^(now>>(k-1-i)&1))
			{
				f[now]=1;
				break;
			}
	}
	for(int i=1;i<=n;i=-~i)
		for(int now=0;now<m;now=-~now)
		{
			int nxt=now<<1&m-1;
			if(s[i]=='A'||s[i]=='?')
				if(i<k||f[nxt|1])//i<k时特判
					dp[i][nxt|1]=(dp[i][nxt|1]+dp[i-1][now])%mod;//注意取模
			if(s[i]=='B'||s[i]=='?')
				if(i<k||f[nxt])
					dp[i][nxt]=(dp[i][nxt]+dp[i-1][now])%mod;
		}
	for(int now=0;now<m;now=-~now)
		ans=(ans+dp[n][now])%mod;
	return printf("%lld",ans),0;
}
```

---

## 作者：Clique (赞：0)

因为 $K$ 很小，考虑暴力枚举字符串的最后 $K-1$ 位进行状态压缩 DP（进行一个映射：$A\to 0$，$B\to 1$）：令 $f_{i,S}$ 表示处理到第 $i$ 位，字符串的最后 $K-1$ 位对应的二进制数为 $S$，有多少种合法的填法。只需暴力枚举并转移即可，时间复杂度 $O(N2^K)$。记得特殊处理一下整个字符的前 $K-1$ 位的答案。

[赛时提交记录](https://atcoder.jp/contests/abc359/submissions/54826982)

---

## 作者：Special_Tony (赞：0)

# 题解
因为 $k\le10$，所以可以把 $\text A$ 当 $0$，$\text B$ 当 $1$ 进行状压 dp。$dp_{i,(j\times2+x)\&(2^k-1)}=dp_{i-1,j}$，其中 $\&$ 表示按位与（$\&2^k-1$ 是因为只需要判断后 $k$ 位就行），$x$ 表示可以转移的方案（如 $\text A$ 只能选 $0$，$\text B$ 只能选 $1$，$\text ?$ 两种都可以选），转移的前提条件是这个字符串不是回文串。最后答案就是 $\sum\limits_{j=0}^{2^k-1}dp_{n,j}$。
# 代码
```cpp
# pragma GCC optimize("Ofast,no-stack-protector")

# pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

# include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef pair <int, int> pii;

const int mod = 998244353;

int n, k, dp[1005][1050], sum;

string a;

bitset <1050> hw;

bool check (int x) {

	for (int i = 0; i < k; ++ i)
		if ((x >> i & 1) != (x >> (k - i - 1) & 1))
			return 1;

	return 0;

}

int main () {

	ios::sync_with_stdio (0);

	cin.tie (0);

	cout.tie (0);

	cin >> n >> k >> a;

	for (int i = 0; i < 1 << k; ++ i)
		hw[i] = check (i);

	dp[0][0] = 1;

	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < 1 << k; ++ j) {

			if (a[i] != 'B' && (i < k - 1 || hw[(j << 1) & ((1 << k) - 1)]))
				dp[i + 1][(j << 1) & ((1 << k) - 1)] += dp[i][j], dp[i + 1][(j << 1) & ((1 << k) - 1)] %= mod;

			if (a[i] != 'A' && (i < k - 1 || hw[((j << 1) + 1) & ((1 << k) - 1)]))
				dp[i + 1][((j << 1) + 1) & ((1 << k) - 1)] += dp[i][j], dp[i + 1][((j << 1) + 1) & ((1 << k) - 1)] %= mod;

		}

	for (int i = 0; i < 1 << k; ++ i)
		sum += dp[n][i], sum %= mod;

	cout << sum;

	return 0;

}
```

---


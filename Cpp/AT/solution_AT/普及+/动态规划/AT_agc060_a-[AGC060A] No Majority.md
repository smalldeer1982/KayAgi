# [AGC060A] No Majority

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc060/tasks/agc060_a

英小文字からなる文字列 $ x $ が以下の条件を満たすとき，$ x $ を**よい**文字列と呼ぶことにします．

- $ x $ の長さ $ 2 $ 以上の (連続する) 部分文字列は，すべて以下の条件を満たす．
  - その部分文字列内で過半数を占める文字が存在しない．
 
例えば，`acbca` はよい文字列ではありません． これは，部分文字列 `cbc` のなかで `c` が過半数を占めているからです．

英小文字と `?` からなる長さ $ N $ の文字列 $ S $ が与えられます． それぞれの `?` を好きな英小文字に置き換ることで，$ S $ をよい文字列にしたいです． $ S $ をよい文字列にする方法が何通りあるかを $ 998244353 $ で割ったあまりを求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 5000 $
- $ S $ は英小文字と `?` からなる長さ $ N $ の文字列
 
### Sample Explanation 1

`aab`, `abb` 以外の方法が条件を満たします．

## 样例 #1

### 输入

```
3
a?b```

### 输出

```
24```

## 样例 #2

### 输入

```
3
a?a```

### 输出

```
0```

## 样例 #3

### 输入

```
20
ugsyakganihodnwmktgi```

### 输出

```
1```

## 样例 #4

### 输入

```
20
??a???h?m?y?ts???tl?```

### 输出

```
444225229```

# 题解

## 作者：_JellyFish_ (赞：9)

#  1. 题意
 
 一个由问号与小写字母组成的长度为 $N$ 的字符串 $S$，可以将问号替换为小写字母，保证替换完成的字符串中没有一个连续子串中的某一个字母数量大于字串长度一半。求出所有可能的情况数对 $998244353$ 取余。
 
#  2. 分析
## 2.1 性质
不难发现，形同 `aa`，`aba` 一类的字符串都是不合法的，通过第 $2$ 类 长度为 $3$ 的字串，我们可以看出：只要保证字符串的所有长度为 $3$ 的字串都合法，我们就可以保证字符串整体合法。
## 2.2 状态
考虑dp，不难设出第一维状态 $i$ 为前 $i$ 个字符，考虑 $2.1$ 中推出的性质，我们只需要记录 $i-1$ 与 $i-2$ 位字符是什么，即可保证当前字符串合法。最后设出状态：

$dp_{i,j,k}$ 表示前 $i$ 个字符中，第 $i-1$ 位字符串为 $j$，第 $i$ 位字符串为 $k$ 的所有情况和。

## 2.3 转移
三重循环枚举 $i,j,k$ 是用来枚举前 $i-1$ 位字符填成了什么样子，第四重循环 $l$ 枚举当前第 $i$ 位字符填什么，转移易得：

$dp_{i,j,k}=\sum{dp_{i-1,j,l}}(l\ne j,l\ne k)$

# 3.代码

```cpp
#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
int n,dp[5005][30][30],ans;
char s[5005];
int main(){
	cin>>n>>(s+1);
	dp[0][26][26]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=26;j++)
			for(int k=0;k<=26;k++)
				if(dp[i-1][j][k])
					for(int l=0;l<26;l++)
						if((s[i]=='?'||s[i]==l+'a')&&l!=j&&l!=k)
							dp[i][k][l]=(dp[i][k][l]+dp[i-1][j][k])%mod;
	for(int i=0;i<=26;i++)for(int j=0;j<=26;j++)ans=(ans+dp[n][i][j])%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：MiRaciss (赞：1)

首先“绝大部分”的意思是超过一半，也就是说不能出现一个子串其中的某种字符超过这个子串大小的一半。

我们考虑一个子串如果有字符出现数量超过一半了，把这个字符分成两半，如果两半的长度大于等于 2，那么一定有一半满足其中某种字符出现数量超过一半。

所以这样分下去，问题就转换成了在任何一个长度为 2 或长度为 3 的子串中，均不能出现两个相同字符。

然后就 dp 就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll Mod=998244353;

ll dp[5005][30][30];
char s[200005];
int n;

int main(){
	cin>>n;
	cin>>(s+1);
	for(int i=1;i<=26;i++) for(int j=1;j<=26;j++)
		if((s[1]=='?'||s[1]-'a'+1==i)&&(s[2]=='?'||s[2]-'a'+1==j)&&i!=j) dp[1][i][j]=1;
	for(int i=3;i<=n;i++) for(int j=1;j<=26;j++) for(int k=1;k<=26;k++) for(int l=1;l<=26;l++)
		if(j!=k&&k!=l&&j!=l) if(s[i]=='?'||s[i]-'a'+1==j) dp[i-1][k][j]+=dp[i-2][l][k],dp[i-1][k][j]%=Mod;
	ll ans=0;
	for(int j=1;j<=26;j++) for(int k=1;k<=26;k++) ans+=dp[n-1][j][k],ans%=Mod;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ZLCT (赞：0)

# [AGC060A] No Majority
怎么都是 $O(|\sum|^3\times n)$ 的暴力，这里给一个也很简单的优化。\
注：此处 $|\sum|=26$ 表示字符集大小。
## 题目翻译
给定一个字符串，把其中的 `?` 任意换成小写字母，要求没有一个子串中出现同一个字符出现次数**大于**子串长度一半的方案数。
## solution
我们从两个字符开始考虑，那显然满足条件的充要条件就是互不相等。\
三个字符的充要条件也比较明显，只要没有两个字符相等即可。\
那我们这里就有个想法，只要我们满足任意三个里都不存在重复数字是不是就可以满足条件？当然这个并不显然，至于如何能想到可以考虑若存在不满足条件的子串，一定是左右两个字符相同，并且不满足的字符一定是这个字符，这样可以使长度（分母）尽可能小，相同字符个数（分子）尽可能大，这样可以使的比值尽可能大于 $\frac{1}{2}$，那继续举几个不合法的例子你会发现必有连续三个存在同样字符。那我们来证明一下。\
首先必要性不必多说，若存在连续三个中有两个字符相等，这本身就不合法了。\
那充分性我们考虑上面说的极端情况，假设字符串长度为 $3n+1$，首尾都是目标字符，那由于连续三个中都没有相同字符，所以最多只有 $n+1$ 个相同字符，此时如果想 $\frac{n+1}{3n+1}>\frac{1}{2}$，那移项变成 $2n+2>3n+1$，也就是 $n<1$，这显然不符合题意。\
那 $O(n\times|\sum|^3)$ 的做法也就出来了，设 $f_{i,j,k}$ 表示前 $i$ 个字符，倒数第二个是 $j$，最后一个是 $k$，直接暴力枚举最近三个字符转移，代码最后统一给出。\
但是这太不优雅了，我们考虑优化一下。\
首先状态由于只与最近三个有关，所以空间可以滚动数组优化到 $3\times 26^2$，当然由于本身状态就很少，所以这个优化没什么意思。\
那时间怎么优化呢？\
我们考虑容斥，我们现在枚举了这一位的 $k$ 和上一位的 $j$，那只要上上一位 $w$ 不是 $j$ 或 $k$ 我们就可以转移，而我们每次如果都去枚举一遍 $w$ 就会很浪费，所以我们可以每次枚举前预处理
$$
sum_j=\sum\limits_{0\le c<26,c\ne j} f_{i-1,c,j}
$$
那每次更新只需要 $f_{i,j,k}=sum_j-f_{i-1,k,j}$ 就可以 $O(1)$ 转移。那么总复杂度就降低到了 $O(n\times|\sum|^2)$。
## code
### 不优化的暴力做法。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5050;
const int mod=998244353;
char s[N];
int n;
int f[N][27][27];
signed main(){
    scanf("%lld%s",&n,s+1);
    for(int i=0;i<26;++i){
        for(int j=0;j<26;++j){
            if(i==j)continue;
            if(s[1]!='?'&&s[1]-'a'!=i)continue;
            if(s[2]!='?'&&s[2]-'a'!=j)continue;
            f[2][i][j]=1;
        }
    }
    for(int i=3;i<=n;++i){
        for(int nc=0;nc<26;++nc){
            if(s[i]!='?'&&s[i]-'a'!=nc)continue;
            for(int ppc=0;ppc<26;++ppc){
                if(ppc==nc)continue;
                for(int pc=0;pc<26;++pc){
                    if(ppc==pc||nc==pc)continue;
                    f[i][pc][nc]+=f[i-1][ppc][pc];
                    f[i][pc][nc]%=mod;
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<26;++i){
        for(int j=0;j<26;++j){
            ans+=f[n][i][j];
            ans%=mod;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```
### 优化后的做法
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5050;
const int mod=998244353;
char s[N];
int n;
int f[N][27][27],pre[27];
signed main(){
    scanf("%lld%s",&n,s+1);
    for(int i=0;i<26;++i){
        for(int j=0;j<26;++j){
            if(i==j)continue;
            if(s[1]!='?'&&s[1]-'a'!=i)continue;
            if(s[2]!='?'&&s[2]-'a'!=j)continue;
            f[2][i][j]=1;
        }
    }
    for(int i=3;i<=n;++i){
        for(int j=0;j<26;++j){
            pre[j]=0;
            for(int k=0;k<26;++k){
                if(j==k)continue;
                pre[j]+=f[i-1][k][j];
                pre[j]%=mod;
            }
        }
        for(int nc=0;nc<26;++nc){
            if(s[i]!='?'&&s[i]-'a'!=nc)continue;
            for(int lc=0;lc<26;++lc){
                if(lc==nc)continue;
                f[i][lc][nc]=(pre[lc]-f[i-1][nc][lc]+mod)%mod;
            }
        }
    }
    int ans=0;
    for(int i=0;i<26;++i){
        for(int j=0;j<26;++j){
            ans+=f[n][i][j];
            ans%=mod;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：sxq9 (赞：0)

## 读题
阅读题目，题面说不能有一种字符在长度 $\ge2$ 的子串中出现。

那么我们先考虑长度为 2 的情况：

显然，如果不同，就合法，相同就不合法。

我们再来考虑长度 3 的情况：

如果有两个相同，就不合法，否则就合法。

然后我们就可以看大一点了。

如果一个子串是不合法的那么一定是属于以下两种情况之一：

1. 有两个相邻的字符一样
1. 没有两个相邻的字符一样

第一种情况很好看出，那我们先看第二种。

如果相邻的都不同，那么观察每个长度为 3 的子串，如果有存在形如 aba 的字符串，那么显然不成立。

如果不存在形如 aba 的字符串，那么一定合法，证明如下：

如果不存在形如 aba 的字符串，那么一个字符在字符串中出现的次数最多为 $\lfloor \frac{n}{3} \rfloor$，那么一定是合法的。

## 思路

考虑 dp，因为我们只要看有没有连续的三个字符不合法，那我们就可以枚举当前位的前两个字符和当前位即可。

1. 数组意义：$dp_{i,j,k}$ 表示在第 $i$ 位前，第 $i-1$ 位为 $j$，第 $i$ 位为 $k$ 的情况数量。
2. 转移：从第一位枚举到第 $n$ 位。
3. 方程：$dp_{i,j,k}=\sum\limits_{x=1}^{26}dp_{i-1,x,j}$
4. 初始值： $dp_{0,0,0}=1$，这样可以保证后面有数。
5. 答案：$\sum dp_{n}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5010],dp[5010][30][30];
int main(){
	int n;
	char x;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
		if(x=='?')a[i]=-1;
		else a[i]=x-'a'+1;
	}
	dp[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=26;j++){
			for(int k=0;k<=26;k++){
				if(dp[i-1][j][k]){//j!=k
					for(int l=1;l<=26;l++){
						if(l!=j&&l!=k&&(a[i]==l||a[i]==-1)){
							dp[i][k][l]+=dp[i-1][j][k];
							dp[i][k][l]%=998244353;
							if(dp[i][k][l]==0)dp[i][k][l]=998244353;
						}
					}
				}
			}
		}
	}
	int s=0;
	for(int i=1;i<=26;i++){
		for(int j=1;j<=26;j++){
			s+=dp[n][i][j];
			s%=998244353;
		}
	}
	cout<<s;
	return 0;
}
```

---

## 作者：highkj (赞：0)

# 思路
我们首先能够发现一个性质，只要所有长度为 $3$ 的串满足条件，那么这个串都能满足条件。

然后我们就能定义状态 $f_{i,j,k}$ 表示现在到了第 $i$ 位且第 $i$ 位填 $j$ 第 $i-1$ 位填 $k$ 的方案数，然后我们可以在循环中枚举第 $i,i-1,i-2$ 位分别填什么，这里用 $a,b,c$ 代替。

我们的状态转移方程就是 $f_{i,a,b}=f_{i,a,b}+f_{i-1,b,c}$ 当然这里需要满足条件 $s_i$ 为问号或等于 $s_i$ 并且 $a=s_i$，然后我们发现这里的 $a,b,c$ 分别不同才行。

最后答案为 $\sum_{i=0}^{25}\sum_{j=0}^{25} f_{n,i,j}$ 。

# AC代码
```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(fasle);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
#define pai(a,x,y) sort(a+x,a+y+1)
using namespace std ;
il int qmi(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=(res*a);
		a=a*a;
		b>>=1;
	}
	return res;
}
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
string s;
const int N=5100,mod=998244353;
int f[N][27][27],n;
fire main() {
	cin>>n;
	cin>>s;
	s=" "+s;
	f[0][26][26]=1;
	rep(i,1,n) {
		rep(j,0,26) {
			rep(k,0,26) {
				rep(x,0,25) if((s[i]=='?'||s[i]-'a'==x)&&x!=j&&x!=k) f[i][x][j]=(f[i][x][j]+f[i-1][j][k])%mod;
			}
		}
	}
	int res=0;
	rep(i,0,25) {
		rep(j,0,25) {
			res=(res+f[n][i][j])%mod;
		}
	}
	print(res);
	return false;
}

```

---

## 作者：MurataHimeko (赞：0)

我们有经典“小凯的疑惑“，$2$ 和 $3$ 最大的无法表示出的数字是 $1$。那么我们只需要关注长度为 $2$ 和 $3$ 的子串。

同时注意到，$\lfloor \frac{2}{2} \rfloor = \lfloor \frac{3}{2} \rfloor$，所以我们只需要关注长度为 $3$ 的子串。

设 $f_{i,j,k}$ 表示到了第 $i$ 个位置，前两个位置分别为 $j,k$。转移是简单的。

代码：

```cpp

char s[N];
int n;
int f[N][27][27];
int a[N], vis[N][27];
 
int main () {
    scanf("%d %s", &n, s+1);
    re(i, n) {
        if(s[i] == '?') a[i] = 0;
        else a[i] = s[i] - 'a' + 1;
    }
    re(i, n) {
        if(!a[i]) re(j, 26) vis[i][j] = 1;
        else vis[i][a[i]] = 1;
    }
    re(i, 26) {
        if(!vis[1][i]) continue;
        re(j, 26) {
            if(vis[2][j]) {
                if(i == j) continue;
                f[2][j][i] = 1;
            }
        }
    }
    rep(i, 3, n) {
        re(j, 26) {
            if(!vis[i][j]) continue;
            re(l, 26) {
                re(r, 26) {
                    if(j == l || j == r) continue;
                    f[i][j][l] = (f[i][j][l] + f[i-1][l][r]) % mod;
                }
            }
        }
    }
    int ans = 0;
    re(i, 26) re(j, 26) {
        ans = (ans + f[n][i][j]) % mod;
    }
    printf("%d", ans);
}
```


---

## 作者：wind_seeker (赞：0)

~~模拟赛少判断一种情况给我莽过去了，结果洛谷前面几发寄了。~~

### 思路

常规思路，拿到题目想性质。

考虑这个数列其实需要满足两个充要条件：

1. 相邻的两个字母不一样。

2. 隔一个字母不一样。

第一个还是很好理解的，第二个小小证明一下。  

考虑对于一个偶数长度的子串，显然满足第一个情况以后就不会不合法了。

考虑对于一个奇数的子串，在满足第一种情况以后，当且仅当某一字母满足开头是他，结尾是他，中间隔一个是他时才会出现不合法，而这个时候，开头三个字母长度的子串必然是不合法的，那么我们保证隔一个字母也不一样，就保证了长度为 $3$ 的子串的合法性，也保证了所有奇数子串的合法性。

最后只要分类讨论字母是否为 `?` 即可递推。

### code

```cpp
/* let life be like summer flowers	*/
/* by wind_seeker					*/
/* 2023-04-22 10:42					*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5010,mod=998244353;

inline int read(){
	int res=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) res=(res<<3)+(res<<1)+(c^48);
	return res*f;
}

int n,a[N],ans;
int dp[N][30][30];//dp_{i,x,y}记录第i位填x,第i-1位填y的方案数

signed main(){
	//只需要满足两个情况即可
	//1:相邻不相同
	//2:隔一个不相同
	//freopen("strstr.in","r",stdin);
	//freopen("strstr.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		char c=getchar();
		while(c!='?'&&(c<'a'||c>'z')) c=getchar();
		a[i]=c;
	}
	//处理1
	if(a[1]=='?') for(int i=1;i<=26;i++) dp[1][i][0]=1;
	else dp[1][a[1]-'a'+1][0]=1;
	//处理2
	if(a[2]=='?') for(int i=1;i<=26;i++) for(int j=1;j<=26;j++) {if(i!=j) dp[2][i][j]=dp[1][j][0];}
	else for(int j=1;j<=26;j++) if(a[2]-'a'+1!=j) dp[2][a[2]-'a'+1][j]=dp[1][j][0];
	//处理3~n
	for(int i=3;i<=n;i++){
		for(int k=1;k<=26;k++){
			if(a[i]!='?'&&a[i]-'a'+1!=k) continue;
			for(int x=1;x<=26;x++){
				if(x==k) continue;
				for(int y=1;y<=26;y++){
					if(y==k||y==x) continue;
					dp[i][k][x]=(dp[i][k][x]+dp[i-1][x][y])%mod;
				}	
			}
		}
	}
	for(int i=1;i<=26;i++) for(int j=1;j<=26;j++) ans=(ans+dp[n][i][j])%mod;
	printf("%lld\n",ans);
	return 0;
}
/*
3
a?b
*/
```

---

## 作者：HMZHMZHMZ (赞：0)

不难发现，一个字符串是合法的当且仅当任意相同的字符在字符串内的距离 $> 2$。证明如下。

如果距离 $=1$，那么一定存在一个形如 $aa$ 的字串，不合法。

如果距离 $=2$，那么一定存在一个形如 $aba$ 的字符串，也不合法。

如果距离 $>2$，那么在一个长度为 $x$ 的字符串中，相同字符出现次数最多为 $1 + \lfloor \frac{x-1}{3} \rfloor $，明显 $\leq \frac{x}{2}$。

所以我们可以设 $f_{i,j,k}$ 表示第 $i$ 位为 $j$，第 $i-1$ 位为 $k$ 的方案数。转移显然。

时间复杂度 $O(n \times 26^3 )$，可以通过。

```cpp
 #include<bits/stdc++.h>
#define ll long long
#define int long long
#define vi vector<int>
#define pii pair<int,int>
#define pb(x) push_back(x)
#define lowbit(x) x&-x
using namespace std;
const int N=5555;
const int mod=998244353;
ll ans;
int n,m,T,f[26][26][N];
inline int read(){
	int s=0,f=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch<='9'&&ch>='0') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return f?-s:s;
}
char ch[N];
inline void add(int& x,int y){x+=y;if(x>=mod) x-=mod;}
signed main(){
	n=read();
	scanf("%s",ch+1);
	for(register int i=0;i<26;++i){
		if(ch[1]!='?'&&ch[1]-'a'!=i) continue;
		for(register int j=0;j<26;++j){
			if(ch[2]!='?'&&ch[2]-'a'!=j) continue;
			if(i==j) continue;
			f[i][j][2]=1;
		}
	}
	for(register int i=3;i<=n;++i){
		for(register int j=0;j<26;++j){
			for(register int k=0;k<26;++k){
				if(j==k) continue;
				for(register int l=0;l<26;++l){
					if(l!=j&&l!=k&&(ch[i]=='?'||ch[i]-'a'==l)){
						add(f[k][l][i],f[j][k][i-1]);
					}
				}
			}
		}
	}
	for(register int i=0;i<26;++i) for(register int j=0;j<26;++j) add(ans,f[i][j][n]);
	cout<<ans;
	return 0;
}
```

---

## 作者：zhanghao233 (赞：0)

# 题目大意
* 对于 $x$ 的每一个长度大于等于 $2$ 的连续子串，都没有某一种字符的数量大于字串长度的一半。

# 性质
显然形如 ```aa```，```aba``` 的字符串不合法。而 $4\le n$ 的情况可以看作上面举例情况的变种，而且显然合法的字符串中的子字符串一定合法。

所以只要保证长度为 $3$ 的所有子字符串都合法，那么字符串就合法。

# 思路
我们先遍历 $s$ 串，对于每一个加入的字符如果前面的字符串合法，则只需要判断新加入的字符与之组合合不合法即可。

所以我们需要知道前面两个字符。

即：$f_{i,j,k}$ 表示前 $i$ 个字符且第 $i-1$ 的字符为 $j$，第 $i$ 的字符为 $k$ 的合法字符串总数。

$f_i$ 等于所有 $f_{i-1}$ 的合法字符串的总数，即：

$f_{i,j,k}=\sum f_{i-1,j,k},(s_i\neq j,s_i\neq k)$

---


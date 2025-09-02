# [AGC020E] Encoding Subsets

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc020/tasks/agc020_e

次のような、`0` と `1` からなる文字列をエンコードする規則を考えます。

- 文字列 `0`、`1` はそれぞれ `0`、`1` とエンコードできる。
- 文字列 $ A $、$ B $ をそれぞれ $ P $、$ Q $ とエンコードできる場合、文字列 $ AB $ を $ PQ $ とエンコードできる。
- 文字列 $ A $ を $ P $ とエンコードできる場合、$ K\ \geq\ 2 $ を正の整数として、文字列 $ AA...A $（$ A $ を $ K $ 個連結したもの）を `(`$ P $`x`$ K $`)` とエンコードできる。

例えば、文字列 `001001001` は `001001001`、`00(1(0x2)x2)1`、`(001x3)` などとエンコードすることができ、この他のエンコード方法も存在します。

また、次の条件が満たされるとき、文字列 $ A $ は文字列 $ B $ の *サブセット* であると呼びます。

- $ A $ と $ B $ は長さが等しく、どちらも `0` と `1` からなる。
- $ A_i $ = `1` であるようなすべての添字 $ i $ に対して、$ B_i $ = `1` でもある。

`0` と `1` からなる文字列 $ S $ が与えられます。$ S $ のすべてのサブセットについて、それぞれをエンコードする方法が何通り存在するか求め、それらの個数の総和を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 100 $
- $ S $ は `0` と `1` からなる。

### Sample Explanation 1

$ S $ のサブセットは $ 4 $ 個存在し、 - `011` は `011`、`0(1x2)` とエンコードできます。 - `010` は `010` とエンコードできます。 - `001` は `001`、`(0x2)1` とエンコードできます。 - `000` は `000`、`0(0x2)`、`(0x2)0`、`(0x3)` とエンコードできます。 したがって、$ S $ のすべてのサブセットについてのエンコード方法の個数の総和は $ 2\ +\ 1\ +\ 2\ +\ 4\ =\ 9 $ 通りです。

### Sample Explanation 2

今回は $ S $ のサブセットは $ 1 $ 個しか存在しませんが、$ 10 $ 通りの方法でエンコードできます。

### Sample Explanation 4

結果を $ 998244353 $ で割ったあまりを出力することを忘れずに。

## 样例 #1

### 输入

```
011```

### 输出

```
9```

## 样例 #2

### 输入

```
0000```

### 输出

```
10```

## 样例 #3

### 输入

```
101110```

### 输出

```
156```

## 样例 #4

### 输入

```
001110111010110001100000100111```

### 输出

```
363383189```

# 题解

## 作者：installb (赞：17)

## AGC020E

[题](https://atcoder.jp/contests/agc020/tasks/agc020_e)  

我是先想的如果 `1` 不能变 `0` 应该怎么做，明显是个区间 DP。  
$f_{i,j}$ 代表 $[i,j]$ 方案数，$g_{i,j}$ 代表缩成一个括号（以及只有一个字符的情况，`0` 或 `1`）$f$ 转移的时候枚举最后一个括号位置。$g$ 转移就枚举区间长度 $len$ 的约数（$len$ 除外）把这些缩成一个括号。  

这题 $f$ 还是一样的转移方式，不过算 $g$ 的时候不同了，需要转移自的 $f$ 需要是所有截取部分 AND 起来的值，可能会产生新的字符串，所以 DP 状态里就记字符串而不是区间了，记忆化搜索即可。  

这个东西看起来复杂度很大但其实是对的，首先 $f$ 刷出来的 $f$ 不用考虑，因为 $f$ 刷出来的 $f$ 刷出来的 $f$ 一定都是原来 $f$ 的字串，还只有 $n$ 个。而 $f$ 也会产生 $g$，并且 $f$ 的每一个子串都会产生一个 $g$ 的计算，而 $g$ 又会产生新的 $f$，这些产生出来的 $f$ 是必须全部重新算的。

但是每次产生出来的 $f$ 长度至多是原来 $g$ 的一半，三次 $g$ 产生 $f$ 操作以后，长度就必定 $\leq 13$ 了。长度为 $n$ 的 01串只有 $2^n$ 个，当 $n\leq 13$ 的时候这其实并不大。

所以我们只需要考虑 $g$ 变 $f$ 一次和两次的情况就行了，而且分成 $f$ 的次数两次乘起来还得小于 $8$，不然就长度太小了。其实最后生成的串可以看作是最早的原串取了几个字串拼起来的，这里用两次操作长度都减半举例好了。  

![YJbb0s.png](https://s1.ax1x.com/2020/05/11/YJbb0s.png)  

只用 $i,j,k$ 就可以表示一个状态，那么状态数不会超过 $n^3$。  
两次分别为分两段和分三段其实是一样的，状态数也只有 $n^3$ 级别种。  
实际值是远小于理论值的。

一共有 $n^3+2^{\frac{n}{8}}$ 个状态，转移用时 $n^2$，时间复杂度 $O(n^5+n^2 2^{\frac{n}{8}})$  

代码写得很丑（）  

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <string>
using namespace std;
typedef long long LL;
const LL N = 998244353;

map <string,LL> mp[2];
string u;

LL f(LL id,string s){
	if(mp[id].find(s) != mp[id].end()) return mp[id][s];
	LL ret = 0,len;
	len = s.length();
	if(id){
		for(LL i = 0;i < len;i ++) ret = (ret + f(1,s.substr(0,i)) * f(0,s.substr(i,len))) % N;
		mp[id][s] = ret; return ret;
	}
	else{
		for(LL i = 1;i < len;i ++){
			if(len % i) continue;
			string t = "";
			for(LL j = 0;j < i;j ++) t += '1';
			for(LL j = 0;j < len;j += i){
				for(LL k = 0;k < i;k ++){
					if(s[j + k] == '0') t[k] = '0';
				}
			}
			ret += f(1,t); ret %= N;
		}
		mp[id][s] = ret; return ret;
	}
}

int main(){
	mp[0][""] = mp[1][""] = 1;
	mp[0]["0"] = 1; mp[0]["1"] = 2;
	mp[1]["0"] = 1; mp[1]["1"] = 2;
	cin >> u;
	cout << f(1,u) << '\n';
	return 0;
}
```

---

## 作者：关怀他人 (赞：15)

#### Solution
考虑对于一个固定的$0/1$串如何求解方案数，可以通过区间dp，设$f_{l,r}$表示将区间$[l,r]$编码的方案数，$g_{l,r}$表示将区间$[l,r]$编码成单个字符或由一个括号括起来（允许嵌套）的方案数，转移时考虑第一位是否编码成一个字符
$$
\begin{aligned}
f_{l,r}&=\sum_{k=l}^{r-1}g_{l,k}f_{k+1,r}\\
g_{l,r}&=\sum_{d|r-l+1} [d为[l,r]的循环节]f_{l,l+d-1}
\end{aligned}
$$

接下来考虑原问题，设$f_S$表示$S$及其所有子集的方案数，
在$g$的转移中枚举$d$后将划分出的子串并起来再进行转移，使用map来存储并记忆化搜索即可。

复杂度$T(n)=\sum_{i=1}^n(n-i+1)(1+\sum_{d|i}(i+T(d))$，简单打个表可以发现当$n=100$时，$T(n)=243422222$，能过。
#### Code
```cpp
/*
Problem : 
Algorithm : 
Status : 
*/
#include<bits/stdc++.h>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#define DEBUG cerr << "Passing Line " << __LINE__<< " in Function [" << __FUNCTION__ << "].\n";
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
template<class T> inline bool checkMax(T &a,const T &b) {return a < b ? a = b,1 : 0;}
template<typename T, typename...Args> inline void checkMax(T &a,const Args...arg) {checkMax(a,max(arg...));}
template<class T> inline bool checkMin(T &a,const T &b) {return a > b ? a = b,1 : 0;}
template<typename T, typename...Args> inline void checkMin(T &a,const Args...arg) {checkMin(a,min(arg...));}

const int INF = 0x3f3f3f3f;
const ll llINF = 1e18;
const int MOD = 998244353;
const int MAXN = 105;

void addmod(int &x,int y) {x += y; if(x >= MOD) x -= MOD;}
void submod(int &x,int y) {x -= y; if(x < 0) x += MOD;}
int add(int x,int y) {addmod(x,y); return x;}
int sub(int x,int y) {submod(x,y); return x;}

string s;
map<string,int> f,g;

int GetG(string s);

int GetF(string s){
    if(s == "") return 1;
    if(f.count(s)) return f[s];
    int n = s.length(), res = 0;
    for(int i = 1;i <= n;i++)
        addmod(res,1ll * GetG(s.substr(0,i)) * GetF(s.substr(i,n - i + 1)) % MOD);
    return f[s] = res;
}

int GetG(string s){
    if(s == "") return 1;
    if(s == "0") return 1;
    if(s == "1") return 2;
    if(g.count(s)) return g[s];
    int n = s.length(), res = 0;
    for(int d = 1;d < n;d++){
        if(n % d != 0) continue;
        string t = "";
        for(int i = 0;i < d;i++){
            bool x = 1;
            for(int j = i;j < n;j += d) x &= s[j] - '0';
            t += x + '0';
        }
        addmod(res,GetF(t));
    }
    return g[s] = res;
}

int main(){
    cin >> s;
    printf("%d\n",GetF(s));
    return 0;
}
```

---

## 作者：Natori (赞：9)

容易发现，原题实际上就是问一个$0/1$串 $s(|s|<=100)$ 被压缩的总方案数.


------------


设答案为 $f(s)$ ，其中 $s$ 是**整个**$0/1$串。

显然转态数有一个上界: $2^l$，其中 $l=|s|$。

考虑状态转移：

对于 $s$ 的最后一个字符 $c$ ，它可以参与压缩，也可以不参与压缩。~~废话，但很重要~~

那么考虑分类讨论，最后用**加法原理**合并两种情况的总方案数：

$c$ 不参与压缩时，方案数为:

$
f(s)=\begin{cases}
f(s-c),& \text{c='0'}\\
f(s-c)\times 2,&\text{c='1'}
\end{cases}
$


$c$ 参与压缩时，可以 $O(l^2)$ 暴力枚举 $c$ 所在压缩的最后一段，

设压缩串为 $t$ ，压缩成了 $k$ 个，则这一段可以记作  $t×k$，
方案数为 $f(s)=f(t)\times f(s-t\times k)$。

但是经过仔细观察，你会发现**状态数难以抵达上界，
实际需要的状态数远远小于理论上界**，

因此可以使用**记忆化搜索**，只递归求需要的状态，降低时间复杂度。

同时可以用 **std::map** 降低空间复杂度，同时查找方便。

因为01串总长度不超过 $100$，所以可以直接使用 **__int128** 代替$0/1$串。

贴下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int128 BIT;
typedef long long ll;
const int L=110;
const ll mod=998244353;
map<BIT,ll>mp[L];
char str[L];
ll dfs(int l,BIT s){
	if(l==0)
		return 1;
	if(mp[l].count(s))
		return mp[l][s];
	//最后一个字符不参与压缩 
	ll f=dfs(l-1,s>>1)*((s&1)+1)%mod;
	BIT _1=0,_2=0;
	//枚举最后一个字符参与压缩时的状态 
	for(int i=1;i<=l;i++){
		_1=(_1<<1)|1;
		_2=s&_1;
		for(int j=i+i;j<=l;j+=i){
			(f+=1ll*dfs(i,_2&=s>>(j-i))*dfs(l-j,s>>j))%=mod;
		}
	}
	mp[l][s]=f;
	return f;
}
int main(){
	cin>>str;
	int l=strlen(str);
	BIT S=0;
	for(int i=l;i--;)
		S=(S<<1)|(str[i]=='1');
	cout<<dfs(l,S);
	return 0;
}
```

萌新的第一篇题解，望多多关照，若有误恳请指出。

---

## 作者：MortisM (赞：7)

# 前言
模拟赛爆蛋题……

# 题意
这道题就是说你有一个 01 串 $s$，你可以对他进行一系列的压缩，每次压缩如下：

+ 找到 $s$ 的一个字串，把它压缩成 $\ge 2$ 个相同的串拼起来。

注意，这道题可以二次压缩。

问压缩这个串（包含它的子集，这里子集值每一个字符都 $\leq$ $s$ 中的字符的串）一共最终可能得到多少个不同的字符串，输出模 $998244353$。

# 做法
这道题做法还是比较套路，现场想到了这个做法，但是因为时间安排的原因没有来得及最后做出来。

对于字符串压缩的题，比较经典的一类套路就是区间 DP。

我们先考虑一个简单版本的问题：

> 有一个 $s$，求它最终有多少种不同的压缩结果。

对于这个简单的问题，我们可以考虑区间 DP，设 $dp(l,r)$ 表示 $s$ 中 $[l,r]$ 一共有多少种压缩的可能，转移如下：
$$
dp(l,r) = \sum_{i=l}^{r-1}dp(l, i)\cdot dp(i + 1,r)
$$
当然，还需要枚举 $r-l+1$ 的所有质因子来判断是否可以直接压缩。

这样，我们就得到了一个 $O(N^3\sqrt N)$ 的 DP，看似解决了这个问题。

但是稍加分析我们不难发现这个做法实际上存在明显的漏洞，比如 $s=000000$ 的情况，它会将 $(00)(00)(00)$ 这种结果统计很多次，那么这个做法就锅了。

可是这是否意味着区间 DP 就不行呢？其实不是。“在哪里跌倒就在哪里爬起”，我们来认真分析一下这个做法到底锅在哪里。

不难看出这个做法实际上就是会将划分成很多块的串算很多次，那么怎么解决这个问题呢？

其是，解决这个问题的本质就是我们希望能钦定一种顺序，使得一种方案只能唯一对应到一种划分。

说到这里，就容易得出解决的方案了，我们需要每次只拆出来第一个直接压缩的（**不同于前面的就是这里钦定是直接压缩的**），就可以做到不重不漏。

对于刚刚举的那个反例，$(00)(00)|(00)$ 这种划分就失效了，因为 $(00)(00)$ 这个部分不是直接压缩的，而是拆成两端来分别压缩。

我们现在来重构这个 DP 状态，可以设 $f(l,r)$ 表示上面的 DP 状态（即 $s[l\cdots r]$ 的压缩方案数），另设一个 $g(l,r)$ 表示必须直接压缩的方案数。

转移就变得显然了：

$$
f(l,r) = \sum_{i=l}^{r-1} g(i,l)\cdot f(l+1,r)
$$

另外枚举 $r-i+1$ 的因子并从 $f$ 转移到 $g$ 即可。

考虑完这个问题。做原问题就顿时变得轻松了不少。

我们原问题也设 $f(S)$ 和 $g(S)$ 表示 $S$ 的子集的能压缩方案的和。

$f(S)$ 的转移与上面类似：
$$
f(S)=\sum_i g(s[l\cdots i])\cdot f(s[i+1 \cdots r])
$$

考虑 $g(S)$ 怎样计算，我们发现 $g(S)$ 的转移不在要求每一个循环节都相等，而是把每个循环节看成二进制数，按位与起来的 $f$ 转移过来。

形式化地：

$$
g(S) = \sum_{i | |S|}f(S[1\cdots i] \& S[i+1,\cdots,2i]\&\cdots)
$$

最终的答案就是 $f(S)$，这个 DP 的过程可以用记忆化搜索优化。

时间复杂度为 $O(N^3\sqrt N)$。

# 程序
注：我的程序是 $O(N^4)$，瓶颈为枚举因子，可以将其改为 $O(N^3\sqrt N)$，但是这样也可以通过（因为状态数远远不到）。

```cpp
#include<bits/stdc++.h>
#define sz(x) (int)(x.size())
#define LL long long
#define pii pair<int, int>
#define pLL pair<LL, LL>
using namespace std;
template<typename T>inline void chmax(T &a,T b){a = max(a, b);}
template<typename T>inline void chmin(T &a,T b){a = min(a, b);}
const int MOD = 998244353;
map<string, int> F, G;
int f(string s);
int g(string s) {
	if(s == "" || s == "0") return 1;
	if(s == "1") return 2;
	if(G.count(s)) return G[s];
	int &res = G[s], len = sz(s);
	for(int i = 1; i < len; i++) if(len % i == 0) {
		string cur = string(i, '1');
		for(int j = 0; j < len; j += i){
			for(int k = 0; k < i; k++) chmin(cur[k], s[j + k]);
		}
		res = (res + f(cur)) % MOD;
	}
	return res;
}
int f(string s) {
	if(s == "" || s == "0") return 1;
	if(s == "1") return 2;
	if(F.count(s)) return F[s];
	int &res = F[s], len = sz(s);
	for(int i = 1; i <= len; i++) res = (res + 1LL * g(s.substr(0, i)) * f(s.substr(i)) % MOD) % MOD;
	return res;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n; string s;
	cin >> s;
	cout << f(s) << endl;
	return 0;
}
```

---

## 作者：极寒神冰 (赞：4)

由于直接对S的所有子集求和并不是很好弄，所以考虑计算在“解码”时成为S的子集的数量。

令$f(S)$表示字符串为S时的答案。

考虑如何去计算$f$。编码字符串的第一个字符有两种选择。

- 是数字$0$或者$1$。显然这个字符与字符串其他部分的编码并没有关系，所以有$f(S_{2\ldots |S|})$种方法编码其余部分。如果$S_1=1$，则答案为这个值$\times 2$，因为编码字符串的第一个字符可以是$0$或$1$。同样，如果$S_1=0$，那么答案为$\times 1$，因为编码字符串的第一个字符串只能是$0$。
- 是一个左括号（。在此情况下，此编码字符串的开头是$(P\times K)$，其中$P$是某个字符串$A$的编码。遍历正整数$K$和$|A|$满足$K\cdot |A|\leq |S|$，同时需要$AA\ldots A$（$K$个$A$拼起来）是$S_{1\ldots K|A| }$的子集。这等价于$A$同时是$S_{1\ldots|A|},S_{|A|+1\ldots2|A|},\cdots,S_{(K-1)|A|+1\ldots K|A|}$的子串。这等价于$A$是所有这些字符串的$\wedge$。并且还有$f(S_{K|A|+1\ldots|S|})$种方法编码其余部分。

因此$f(S)$的递推式子不难推出
$$
f(S)=(1+S_1)f(S_{2\ldots |S|})+\sum_{|A|=1}^{|S|} \sum_{K=1}^{\lfloor\frac{|S|}{|A|}\rfloor} f(g(S,K,|A|))\times f(S_{K|A|+1\ldots |S|})
$$
其中$g(S,K,|A|)$表示$S_{1\ldots |A|} \wedge S_{|A|+1\ldots 2|A}  \wedge \ldots  \wedge S_{(K-1)|A|+1\ldots K|A|}$。

通过记忆化来计算$f(S)$。$f$将会调用多少个不同的参数？显然上界看上去为$O(2^{|S|})$，但事实上该解决方案十分快速。

具体证明可以查看官方题解。

下面附上感性理解：

如果字符串长度最多为12，那么不同的字符串个数为$2^{13}-2$种。可以证明对于长度$> 12$，最多有$O(n^2)$种方法调用$f$。事实上，状态数最多为$O(N^3+2^{N/8})$其中$N^3$前面有一个小常数。（其他题解有讲大概怎么推的）

```c++
#define lll __int128
map<pair<lll,int>,int>f;
char s[111];
int n;
int dfs(pair<lll,int> now)
{
	if(!now.se) return 1;
	if(f.count(now)) return f[now];
	int ans=dfs(mkp(now.fi>>1,now.se-1))*((now.fi&1)+1)%mod;
	R(A,1,now.se>>1) 
	{
		lll S=((lll)1<<A)-1,tmp=now.fi,sum=tmp&S;
		tmp>>=A;sum&=tmp&S;tmp>>=A;
		for(int K=now.se-A-A;K>=0;K-=A,sum&=tmp&S,tmp>>=A) 
			ans=(ans+1ll*dfs(mkp(sum,A))*dfs(mkp(tmp,K)))%mod;
	}
	return f[now]=ans;
}
signed main()
{
	scanf("%s",s);
	n=strlen(s);
	lll S=0;
	R(i,0,n-1) S=S<<1|(s[i]-'0');
	writeln(dfs(mkp(S,n)));
}
```



---

## 作者：heyongxin (赞：4)

记忆化

设G(s)为s的所有子集的表示法，要求表示法不可分割（左右均为括号，或长度为1）

设F(s)为s的所有子集的表示法。

计算G(s)枚举K，K必须是s长度的约数，把几段按位与起来，然后调用F即可。

计算F(s)枚举s的一个前缀t，答案增加G(t)*F(s-t)。

为什么状态数很小呢？

比较短的字符串数目有限，长度<=l 的字符串个数只有$2^{l+1}$-1个
比较长的字符串数目有限，长度> l的字符串个数只有n*$(n/l)^{2}$个。
因为必须是若干段长度为l 的按位与。
代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
string s;
map<string,int>f;
map<string,int>g;
int F(string s);
int G(string s)
{
	if(g.find(s)!=g.end())
	return g[s];
	if(s.size()==1)
	return g[s]=s[0]-'0'+1;
	for(int i=1;i<s.size();++i)
	{
		if(s.size()%i==0)
		{
			string t;
			for(int j=0;j<i;++j)
			{
				int r=1;
				for(int k=0;k<s.size()/i;++k)
				if(s[i*k+j]=='0')
				r=0;
				t+=(char)(r+'0');
			}
			g[s]=(g[s]+F(t))%mod;
		}
	}
	return g[s];
}
int F(string s)
{
	if(f.find(s)!=f.end())
	return f[s];
	for(int i=1;i<=s.size();++i)
	f[s]=(f[s]+1ll*F(s.substr(0,s.size()-i))*G(s.substr(s.size()-i,i))%mod)%mod;
	return f[s];
}
int main()
{
	cin>>s;
	f[""]=1;
	cout<<F(s)<<endl;
	return 0;
}
```

---

## 作者：tzc_wk (赞：3)

[Atcoder 题面传送门](https://atcoder.jp/contests/agc020/tasks/agc020_e) & [洛谷题面传送门](https://www.luogu.com.cn/problem/AT3859)

首先先考虑如果没有什么子集的限制怎样计算方案数。明显就是一个区间 $dp$，这个[恰好一年前](https://www.luogu.com.cn/record/31807323)就做过类似的[题目](https://www.luogu.com.cn/problem/P2470)了。我们设 $f_{l,r}$ 为压缩 $[l,r]$ 的方案数，$g_{l,r}$ 表示压缩 $[l,r]$，并且**强制要求 $[l,r]$ 必须用括号括起来**的方案数，那么 $f_{l,r}$ 转移显然可以枚举第一段括号的位置，即 $f_{l,r}=\sum\limits_{k=l-1}^rg_{l,k}f_{k+1,r}$。$g_{l,r}$ 转移就枚举循环节长度 $len$，即 $g_{l,r}=\sum f_{l,l+len-1}[len\ \text{为}\ s[l...r]\ \text{的循环节}]$。

接下来考虑加上“子集”这个条件之后怎样计算答案，还是设 $f_{l,r}$ 表示将 $[l,r]$ 所有子集压缩的方案数之和，$g_{l,r}$ 表示将 $[l,r]$ 所有子集压缩，并且强制要求 $[l,r]$ 必须用括号括起来的方案数。显然 $f$ 还是一样的转移方式，算 $g$ 的时候就有些不同了，我们枚举 $r-l+1$ 的所有约数 $len$，并考虑 $s[l...r]$ 中每一段长度为 $len$ 的字符串，即 $s[l...l+len-1],s[l+len...l+2len-1]\dots$，我们将这 $\dfrac{r-l+1}{len}$ 个字符串每一位 **AND** 起来，然后求它的 $f$ 值就行了，可以用记忆化搜索实现。

这个算法复杂度看起来不太对。但这只是看起来，事实上这样写即可通过此题。我们粗略估计一下可得 $T(n)=\sum\limits_{i=1}^n(n-i+1)(\sum\limits_{d\mid i}(i+T(\dfrac{i}{d})))$，稍微打个表即可发现这个 $T(n)$ 并不会特别大，因此这样写是没问题的。

这题告诉我们看到 $n\le 100$ 不要习惯性地想 $n^4$ 或 $n^3\log n$，有的复杂度奇怪的解法也可以通过这种小数据。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MOD=998244353;
map<string,int> f,g;
string s;
int calcg(string s);
int calcf(string s){
	if(s==""||s=="0") return 1;
	if(s=="1") return 2;
	if(f.count(s)) return f[s];
	int ret=0;for(int i=1;i<=s.size();i++){
		string s1,s2;
		for(int j=0;j<i;j++) s1+=s[j];
		for(int j=i;j<s.size();j++) s2+=s[j];
		ret=(ret+1ll*calcg(s1)*calcf(s2))%MOD;
	} return f[s]=ret;
}
int calcg(string s){
	if(s==""||s=="0") return 1;
	if(s=="1") return 2;
	if(g.count(s)) return g[s];
	int ret=0;
	for(int i=1;i<s.size();i++){
		if(s.size()%i) continue;string t="";
		for(int j=0;j<i;j++){
			int flg=1;
			for(int k=j;k<s.size();k+=i) flg&=(s[k]-'0');
			t+=(flg^48);
		} ret=(ret+calcf(t))%MOD;
	} return g[s]=ret;
}
int main(){
	cin>>s;printf("%d\n",calcf(s));
	return 0;
}
```



---

## 作者：hhoppitree (赞：2)

#### 题意简述

定义一个 $\texttt{01}$ 串的压缩是满足以下方式的字符串变化过程：

- $0\rightarrow0$，$1\rightarrow1$；
- 如果 $A\rightarrow P$ 以及 $B\rightarrow Q$ 合法，则 $A+B\rightarrow P+Q$ 也合法；
- 如果 $S=\underbrace{A+A+\cdots+A}_{n\text{ 个 }A\small(n\le2)}$，则 $S\rightarrow(A\times n)$ 合法，其中 $\texttt{()×}$ 均为字符，$n$ 为数字且算作一个字符。

定义 $\texttt{01}$ 串 $T$ 是 $S$ 的子集当且仅当

- $|T|=|S|$；
- $\forall T_i=1,S_i=1$。

现在给定一个长度为 $n$ 的 $\texttt{01}$ 串 $S$，求其所有子集的合法压缩方案数量的和，对 $P=998244353$ 取模。

对于全部数据，$N\le100$。

#### 题目解法

先考虑**对于单个 $T$**，它的合法压缩方案数量，类似括号串上的区间 $\texttt{DP}$，我们可以设 $f_{l,r}$ 表示压缩区间 $[l,r]$ 内的字符的方案数，$g_{l,r}$ 表示压缩区间 $[l,r]$ 内的字符为单个字符或由一个括号括起来（允许嵌套）的方案数，则易得如下转移方程：
$$
\begin{aligned}f_{l,r}&=\sum\limits_{k=l}^{r-1}g_{l,k}f_{k+1,r}\\g_{l,r}&=\sum\limits_{d\mid(r-l+1)}[d \text{ 为 } [l,r] \text{ 的循环节长度}]f_{l,l+d-1}\end{aligned}
$$
对于 $S$ 的所有子集的求和，可以直接将 $f_S$ 定义为 $S$ 的所有子集的压缩方案数，类似可以定义 $g_S$，直接**记忆化搜索**即可，时间复杂度 $T(n)=\sum\limits_{i=1}^{n}\Big(n-i+1\Big)\left(1+\sum\limits_{d|i}\Big(i+T(d)\Big)\right)$，当 $n=100$ 时 $T(n)=243422222$，能通过本题。

#### 总结

考虑单个对象后拓展到整体是常见套路，有时不需要有复杂度容易证明的做法。

---

## 作者：xht (赞：1)

## [Encoding Subsets](https://atcoder.jp/contests/agc020/tasks/agc020_e)

### 题意

- 对于一个 $0/1$ 串，我们可以将其按如下方式编码：
  - $0/1$ 串 $0$ 可以被编码为 $\texttt{0}$，$0/1$ 串 $1$ 可以被编码为 $\texttt{1}$。
  - 若 $0/1$ 串 $A$ 可以被编码为 $P$，$0/1$ 串 $B$ 可以被编码为 $Q$，则 $0/1$ 串 $AB$ 可以被编码为 $PQ$。
  - 若 $0/1$ 串 $A$ 可以被编码为 $P$，对于 $k \ge 2$，$0/1$ 串 $A^k$ 可以被编码为 $\texttt{(}P\texttt{x}k\texttt{)}$。
- 显然一个 $0/1$ 串可能有多种编码方案。
- 定义 $0/1$ 串 $A$ 是 $0/1$ 串 $B$ 的子集，当且仅当 $A$ 和 $B$ 长度，且对于所有 $A_i = 1$ 的 $i$ 满足 $B_i = 1$。
- 给定 $0/1$ 串 $S$，求出所有 $S$ 的子集的编码方案数之和。
- $|S| \le 100$，答案对 $998244353$ 取模。

### 题解

考虑对于一个固定的 $0/1$ 串如何求解方案数，考虑区间 DP，设 $f_{l,r}$ 表示将区间 $[l,r]$ 编码的方案数，$g_{l,r}$ 表示将区间 $[l,r]$ 编码成单个字符或由一个括号括起来（允许嵌套）的方案数，则转移有：
$$
f_{l,r}=\sum_{k=l}^{r-1}g_{l,k} f_{k+1,r}
$$

$$
g_{l,r}=\sum_{d|r-l+1} [d为[l,r]的循环节]f_{l,l+d-1}
$$

考虑原问题，直接拿字符串来定义状态，在 $g$ 的转移中枚举 $d$ 后对划分出的子串取并进行转移即可。

由于状态数并不多，时间复杂度 $\mathcal O(能过)$。

### 代码

```cpp
map<string, modint> f, g;

modint F(string s);

modint G(string s) {
	if (g.find(s) != g.end()) return g[s];
	int n = s.size();
	modint ans;
	for (int d = 1; d < n; d++) {
		if (n % d) continue;
		string t = "";
		for (int i = 0; i < d; i++) {
			bool c = 1;
			for (int j = i; j < n; j += d) c &= s[j] - '0';
			t += c + '0';
		}
		ans += F(t);
	}
	return g[s] = ans;
}

modint F(string s) {
	if (f.find(s) != f.end()) return f[s];
	int n = s.size();
	modint ans;
	for (int i = 1; i <= n; i++)
		ans += G(s.substr(0, i)) * F(s.substr(i, n));
	return f[s] = ans;
}

int main() {
	string s;
	rds(s);
	f[""] = 1, g[""] = 1, g["0"] = 1, g["1"] = 2;
	print(F(s));
	return 0;
}
```

---

## 作者：XRRRRcode (赞：1)

# 题解
首先考虑 DFS 暴力，方案总数可以表示为：$g(t) \times g(s-t \times k)$，暴力枚举 $x$ 所在压缩的最后一行，所以得出时间复杂度 $O(len^2)$，明显过不了所有的点。我们继续分析，可以考虑记忆化搜索，剪枝优化后时间复杂度可以大大降低。同时，我们可以使用散列表降低空间复杂度。这样优化以后，根据状态转移方程可以看出转移所需时间复杂度为 $O(len \log_{2}{len})$，基本上已经达到了最优解。最后贴上代码。
# 代码
```cpp
#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
map<long long,int> mp[105];//map映射方便维护
char s[105];//也可以使用string
int dfs(int l,long long ans)//记忆化搜索
{
    if(!l)
        return l;
    if(mp[l].count(ans))
        return mp[l][ans];//懂的都懂
    int sum=dfs(l-1,ans/2)*(ans%2+1)%mod;
    long long x=0,y;
    for(int i=1;i<=l;i++)
    {
        x=x<<1|1;//位运算很快乐
        y=ans&x;
        for(int j=2*i;j<=l;j+=i)
            sum=(sum+1ll*dfs(i,y&=ans>>j-i)*dfs(l-j,ans>>j))%mod;//状态转移方程
    }
    return mp[l][ans]=sum;//不是==而是=
}//时间复杂度相当炸裂，但还真能过
int main()
{
    long long ans=0;
    cin>>s;
    int l=strlen(s),i;
    for(i=1;i--;)
        ans=ans<<1|(s[i]=='1');//众所周知，位运算速度超快
    cout<<dfs(1,ans)<<endl;
	return 0;
}
```


---

## 作者：xfrvq (赞：1)

[$\tt Link$](/problem/AT3859)。

[有一道题](/problem/P4302) 也是字符串的压缩，但是要求的是压缩后的最短长度，然后做法是区间 $\tt DP$。故考虑区间 $\tt DP$（应该比较显然看出）。

我们先把问题弱化：去掉“包含”的条件，对单个字符串求答案。

考虑如刚刚那题，记录 $f_{l,r}$ 代表一个区间的答案。

但是这一个不够（我考场上在这里挣扎了许久），还要用 $g_{l,r}$ 代表 **不是由多个压缩合并而成的压缩的答案**。

转移不难。

+ $f_{l,r}$ 的转移：枚举断点 $k\in[l,r)$，$f_{l,r}=\sum g_{l,k}f_{k+1,r}$。
+ 原因：如果使用 $f$ 来代替这个式子里面的 $g$，那样会算重。
+ $g_{l,r}$ 的转移：枚举 $k\in[1,r-l+1]$ 使得 $S_{l\cdots l+k-1}$ 是 $S_{l\cdots r}$ 的循环节（即它会重复很多遍），$g_{l,r}=\sum f_{l,l+k-1}$。
+ 原因：$g$ 的来源就是每一种可能的循环节情况之和。

考虑原问题。

我们不妨用一个字符串 $S$ 代替原先的状态 $\{l,r\}$，代表 $S$ 的答案。

+ $f_S$ 的转移：类似的套路枚举断点，然后直接 `string::substr` 找到 $[l,k]$ 和 $(k+1,r]$ 的两个子串。
+ $g_S$ 的转移：有点改变（但是不难想），枚举一个可能的循环的位置 $k$（只需要满足 $k\mid r-l+1$ 即可）然后考虑有一个字符串 $T$ 作为循环节，对于它的任意一位
1. 找到每个 $T$ 需要覆盖上的字符串 $T^{\prime}$ 的对应位。
1. 如果全部都是 $1$，那这一位就可以取到 $1$（如果有一位是 $0$，根据“包含”的规则，无法将其改变成 $1$。）
1. 一定可以取到 $0$（如果有一位是 $1$，根据“包含”的规则，可以将其改变成 $1$。）
+ 找到对于每个可能的 $k\mid r-l+1$，对应的循环节字符串 $T$ 的 $1$ 的个数 $x$，那么 $g_{l,r}=\sum2^xf_T$。
+ 原因：$2^x$ 可以代表 $T$ 包含几个字符串（原因：这些位置有两种选择，其它位置有一种选择）

对于状态的存储，考虑记忆化搜索，然后 `unordered_map<string,int>` 解决。

---

## 作者：Digital_Sunrise (赞：1)

[link](https://www.luogu.com.cn/problem/AT3859)

## 前言

此篇博客主要补充说明和细节

题意简化：

求 $S$ 包含的字符串被压缩后得到的不同字符串总数量，

当一个字符串 $T$ 被字符串 $S$ 包含，

当且仅当 $|T|=|S|$ 且 $S$ 为 $0$ 的位置 $T$ 也为 0 。

## 思路

一眼望去要么是区间 dp 要么是数位 dp ，

数位是没可能的，那只能是区间 dp 。

~~但是我模拟赛考场写了一个贪心结果假了。~~

设一个数组 $dp$ ，其中 $dp_s$ 表示对于 $01$ 串 $s$ （没错，参数是一个字符串），其包含的字符串被压缩后得到不同字符串的总数量。


那么对于 $s$ 的最后一个字符 $c$ ，拆成两部分看：参与压缩与不参与压缩，

如果 $c$ 不参与压缩，那么得到的数量 $sum1$ 满足下式：

$$

sum_1=
\begin{cases}
dp_{s-c} & S[c]=0\\
dp_{s-c}\times 2 & S[c]=1
\end{cases}
$$

其中 $s-c$ 即为 $s$ 去除最后一位所得的字符串。

注意到当 $S[c] =1$ 时 $sum_1=dp_{s-c\times}2$ 是因为此时被 $S$ 包含的字符串 $T$ 在此位有 $0$ 和 $1$ 两种选择。

如果 $c$ 不参与压缩，那么枚举 $s$ 最后一个循环节的长度 $l$ 。

每当枚举到一个长度为 $l$ 的压缩串 $t$ 与其在 $s$ 尾部往前数的次数 $k$ ，

参加压缩得到的数量 $sum_2 +=dp_t \times dp_{s-t\times k}$ ，

最后 $dp_s=sum_1+sum_2$ ，

考虑用记忆化搜索实现。

## 实现

现在，我们需要把遇到的困难解决。

1. 怎么存字符串

因为 $n\le 100$ ，可以使用 `__int128` 状态压缩。

2. $dp$ 数组空间开不下

发现很大一部分情况都被排除掉了，导致了空间的极大浪费，

所以考虑用 $map$ 储存，设 $map_{i,j}$ 表示当前处理到了第 $i$ 位，字符串状态为 $j$ 的压缩数量，代替 $dp_j$ 发挥作用。

现在，你可以愉快的去写代码了！

我的代码就不放了，状态压缩写得比较鬼畜。。。


---

## 作者：artofproblemsolving (赞：1)

直接上分析：

考虑将 $g(s)$ 作为状态，显然状态数有一个上界:   $2^{|s|}$。
 
考虑转移：对于 $s$ 的最后一个字符 $x$，它要么不参与压缩，要么参与压缩。

不参与压缩的话，方案数就是 ``g*(s-x)*(x=='1'?2:1)``，否则，$O(len^2)$ 复杂度暴力枚举 x 所在压缩的最后一段（记为 $t*k$），方案数就是 ``g(t)*g(s-t*k)``。

进一步分析：

观察几组数据后，发现状态数难以达到上界，实际需要的讨论数量远小于理论上界。怎么办？

我们可以通过**记忆化搜索**的方法，只去考虑会使用到的状态，这样时间复杂度将大大降低。

如果灵活运用散列表，则可以同时降低空间复杂度。

代码如下：

```
#include <bits/stdc++.h>
using namespace std;
map<__int128,int>mp[1005];
int l;
char s[1005];
int dfs(int l,__int128 k){//递归寻找状态
	if(!l) return 1;
	if(mp[l].count(k)) return mp[l][k];
	int sum=dfs(l-1,k/2)*(k%2+1)%998244353;
	__int128 x=0,y;
	for(int i=1;i<=l;i++){
		x=x<<1|1;y=k&x;
		for(int j=2*i;j<=l;j+=i) sum=(sum+1ll*dfs(i,y&=k>>j-i)*dfs(l-j,k>>j))%998244353; //转移
	} 
	return mp[l][k]=sum;
}
int main(){
	cin>>s;
	l=strlen(s);
	__int128 k=0;
	for(int i=l;i--;) k=k<<1|(s[i]=='1');
	cout<<dfs(l,k)<<endl;
    return 0;
}
```


---

## 作者：qiqing (赞：1)

## Encoding Subsets 

> **题意**：
> 定义``01``串压缩为：
>
> * $0\rightarrow 0$，$1\rightarrow 1$
>
> * 若$S=\underbrace{A+A+\cdots +A}_{n个(n\geqslant2)}$，则$S\rightarrow (A\times n)$合法，比如$0111\rightarrow 0(1\times 3)$
>
> * 若$A\rightarrow C$，$B\rightarrow D$合法，则$A+B\rightarrow C+D$合法~(+表示字符串拼接)~，比如$00\rightarrow (0\times 2)$，$11\rightarrow (1\times 2)$合法，则$0011\rightarrow (0\times 2)(1\times 2)$合法
>
> 定义``01``串$B\subseteq A$当且仅当：
>
> * $|A|=|B|$
>
> * $\forall B_i=1$，$A_i=1$ 
>
> 比如$\{000\}\subseteq \{011\}$，$\{010\}\subseteq \{011\}$
>
> 对于给定``01``串S，求它所有子集的合法变化结果总数

### 题解

如果**不考虑子集**，问题就是字符串压缩总方案数

考虑**区间DP**

设$\texttt {f[l][r]}$表示子串$\texttt {[l,r]}$的总方案数，$\texttt {g[l][r]}$表示子串$\texttt {[l,r]}$的压缩后的方案数

*压缩后*是子串$\texttt {[l,r]}$是$\texttt {(A}\times \texttt {n)}$的形式，或长度为$\texttt 1$

容易考虑到$\texttt {f[i][i] = g[i][i] = 1}$，转移有

$\texttt {f[l][r] = g[l][r] + }\displaystyle\sum_{\texttt {i=1}}^{\texttt {r-1}} \texttt {f[l][i]}\times\texttt {f[i + 1][r]}$

$\texttt {g[l][r] =}\displaystyle\sum_{\texttt {d|(r-l+1)}}\texttt {f[l][l + d - 1]}$($\texttt {[l,l+d-1]}$是$\texttt{[l,r]}$的循环节)


答案就是$\texttt {f[1][n]}$

如果**考虑所有子集**，DP的状态就要转成字符串

设$\texttt {f[S]}$表示字符串$\texttt S$所有子集的总方案数，$\texttt {g[S]}$表示字符串$\texttt S$所有子集的压缩方案数

容易考虑到$\texttt {f[""] = g[""] = 1}$，$\texttt {f["0"] = g["0"] = 1}$，$\texttt {f["1"] = g["1"] = 2}$，转移有

$
\texttt {f[S] = }\displaystyle\sum_{\texttt T\subseteq \texttt S} \texttt {g[T]}\times \texttt {f[S - T]}
$

$
\texttt {g[S] = }\displaystyle\sum_{\texttt {T}}\texttt {f[T]}
$($\texttt {T}$是$\texttt {S}$的循环节)

答案就是$\texttt {f[原串]}$

---


# [ARC180A] ABA and BAB

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc180/tasks/arc180_a

`A`, `B` からなる長さ $ N $ の文字列 $ S $ が与えられます．

あなたは以下の $ 2 $ 種類の操作を好きな順序で $ 0 $ 回以上繰り返すことができます．

- $ S $ の中で `ABA` となっている (連続した) 部分を選び，それを `A` で置き換える．
- $ S $ の中で `BAB` となっている (連続した) 部分を選び，それを `B` で置き換える．
 
操作後の $ S $ としてあり得る文字列の個数を $ 10^9+7 $ で割ったあまりを求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 250000 $
- $ S $ は `A`, `B` からなる長さ $ N $ の文字列
 
### Sample Explanation 1

操作後の $ S $ としてあり得るのは以下の $ 2 $ 種類の文字列です． - `ABAB`: $ 0 $ 回の操作を行うことでこの文字列を得ることができます． - `AB`: $ S= $`ABAB` の $ 1 $ 文字目から $ 3 $ 文字目までが `ABA` となっています．これを `A` で置き換えると $ S= $`AB` となります． なお，$ S= $`ABAB` の $ 2 $ 文字目から $ 4 $ 文字目までが `BAB` となっているので，これを `B` に置き換える操作も可能です． ただし，その結果得られる `AB` は重複して数えないことに注意してください．

### Sample Explanation 2

操作を $ 1 $ 度も行うことができません．

### Sample Explanation 4

$ 10^9+7 $ で割ったあまりを求めるのを忘れないようにしてください．

## 样例 #1

### 输入

```
4
ABAB```

### 输出

```
2```

## 样例 #2

### 输入

```
1
A```

### 输出

```
1```

## 样例 #3

### 输入

```
17
BBABABAABABAAAABA```

### 输出

```
18```

## 样例 #4

### 输入

```
100
ABAABAABABBABAABAABAABABBABBABBABBABBABBABBABBABBABBABBABBABBABBABAABABAABABBABBABABBABAABAABAABAABA```

### 输出

```
415919090```

# 题解

## 作者：Ratio_Y (赞：15)

## 思路
首先一个浅显易得的结论，当 $A$ 或 $B$ 连续出现时，我们可以将它们分成两段，每段都可以看作一个独立事件，结果数只和每个独立事件的样本点有关。

我们设独立事件共有 $tot$ 个，每个独立事件的样本点为 $w_i$，则显然有 $ans=\prod_{i=1}^{tot} w_i$。

接下来该找 $w_i$ 的值了。先打表找规律，发现 `ABA` 和 `ABAB` 的种类数均为 2，`ABABA` 和 `ABABAB` 的种类数均为 3。浅推一下，可以得到一个由 $A$ 和 $B$ 交替出现总计长度为 $n$ 的串的全部样本点为 $\lceil {\frac{n}{2}} \rceil$，那么答案也就呼之欲出了。

## 实现要点
定义一个变量 $flag$ 用来记录上一个出现的字符以判断是否到达两个独立事件的边界。

AtCoder 不能使用 `cin>>s+1` 的操作，我们只能从下标为 0 开始输入。

开 `long long`，防止爆 `int`。

## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Ratio=0;
const int N=250005;
const int mod=1e9+7;
int len,n,tot,w[N];
char ch[N];
bool flag;
long long ans=1;
void Wsolve()
{
	if(n&1) n++;int res=n/2;//手动向上取整
	w[++tot]=res; 
}
int main()
{
	scanf("%d",&len);cin>>ch;n=1;
	if(ch[0]=='A') flag=1;
	else flag=0;
	for(int i=1;i<len;i++)
		if((flag&&ch[i]=='B')||(!flag&&ch[i]=='A')) flag^=1,n++;
		else Wsolve(),n=1;
	Wsolve();//最后可能有未截止的独立事件
	for(int i=1;i<=tot;i++)
		ans=ans*w[i]%mod;
	printf("%lld\n",ans);
	return Ratio; 
}
```
------------
完结撒花~

欢迎大家光临 [$My\,Blogs$](https://www.cnblogs.com/Ratio-Yinyue1007)~

---

## 作者：longhaoyuan (赞：2)

审核大神放过我。
## 题意
一个由 `A` 和 `B` 组成的字符串，每次可以将 `ABA` 压缩为 `A` 或 `BAB` 压缩为 `B`。问：任意次操作（可以为 $0$）后，有多少种可能的字符串。
## 思路
这个题目很复杂，因为操作次数和操作位置都是很烦人的干扰条件。所以咱们考虑几种简单情况：
1. `AAAAA...AAA`，很明显，一次都不能操作。
2. `BBBBB...BBB`，同 (1.)。
3. `ABABABABABAB`，我们暂且称其为“交叉字符串”。下面神奇的事情发生了：我们无论如何操作，它永远会变成长度减少 $2$ 的“交叉字符串”，且首尾字符不改变。

有了以上结论后，我们再次回到一开始的“任意字符串”。我们发现：任何由 `A` 和 `B` 组成的字符串都可以由多个“交叉字符串”组成。而每两个“交叉字符串”衔接的地方就是上述 (1.) 和 (2.) 的情况，即无法操作。所以一个“任意字符串”的操作一定是多个“交叉字符串”在操作。

因此求出每个“子交叉字符串”的可能变化并根据乘法原理再相乘，即可求出“任意字符串”的所有可能变化的个数。那“交叉字符串”的可能变化怎么算？简单，根据 (3.) 中的结论，$总可能变化数=\frac{长度}{2}$ 。

Demo:
```cpp
//100pts
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double dbl;
const ll mod = 1e9+7;

ll n;
string s;
ll ans = 1LL;

int main(){
	scanf("%lld", &n); cin >> s;
	s = s + s.back(); n++;
	int last = 0;
	for (int i = 1; i < n; i++){
		if (s[i] == s[i-1]){
			int dis = i - last;
			ans *= (dis + 1) / 2;
			ans %= mod;
			last = i;
		}
	}
	printf("%lld", ans);
    return 0;
}
```

---

## 作者：Binah_cyc (赞：2)

[题目传送门]( https://www.luogu.com.cn/problem/AT_arc180_a) 

## 题目分析

arc 经典人类智慧题。

前置知识：乘法原理。

简单介绍一下，就是如果两个事件之间互不干扰，则它们的方案数总和就是它们各自的方案数的乘积。

为了方便，我们将 `ABABA` 这样的串叫做**模板串**。

先思考一个简单情况：一段极长的连续的 `ABABA` 或 `BABAB` 的方案数。

我的思考过程：

 `ABA`，`ABAB` 有两种方案；`ABABA`，`ABABAB` 有三种方案；`ABABABA`，`ABABABAB` 有四种方案。

找到规律了么？设该模板串的长度为 $n$，那么它的方案数为 $\lceil {n \over 2} \rceil$。

简单证明一下，如果有 $k$ 个 `ABA` 这样的串，那么它就有 $k+1$ 种方案，并且在结尾添加一个 `B` 不会影响方案数，因为我们是计算有多少个 `ABA` 转换了，而长度为 $n$ 的模板串有 $\lceil {n \over 2 } \rceil -1$ 个 `ABA` ，所以就有 $\lceil {n \over 2} \rceil$ 个方案。

接下来，思考更一般的形式，我们会发现，两个模板串之间互不干扰，所以应使用乘法原理。

接下来是代码时间！

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long//不开long long见祖宗
const int mod=1e9+7;
int n,ans=1;
char c[250005];
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	int sze=0;
	for(int i=1; i<=n; i++)
	{
		cin>>c[i];
		if(c[i]!=c[i-1]) sze++;//计算该模板串的长度
		else ans=(((sze/2)%mod+sze&1)%mod*ans)%mod,sze=1;//计算贡献
	}
	ans=(((sze/2)+sze&1)%mod*ans)%mod;//别忘了最后一个模板串的贡献
	cout<<ans;
	return 0;
}
```

---

## 作者：Tjaweiof (赞：2)

# AT_arc180_a 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_arc180_a)

容易发现，一段 `ABA..BA` 只能变成 `A`、`ABA`、`ABABA`、……，`BAB..AB` 同理。设长度为 $l$，那么结果只有 $\frac{l+1}2$ 种。最后把所有答案相乘即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
const int mod = 1e9 + 7;
int n, a[250001], cnt;
string s;
long long ans = 1;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	cin >> s;
	s = " " + s;
	for (int i = 1; i <= n; i++){
		if (s[i] == 'A'){
			a[i] = 1;
		} else {
			a[i] = 2;
		}
		if (!(i & 1)){
			a[i] ^= 3;
		}
	}
	cnt = 1;
	for (int i = 2; i <= n; i++){
		if (a[i] == a[i - 1]){
			cnt++;
		} else if (cnt){
			ans *= (cnt + 1) >> 1;
			ans %= mod;
			cnt = 1;
		}
	}
	ans *= (cnt + 1) >> 1;
	ans %= mod;
	cout << ans;
	return 0;
}

```

---

## 作者：__Cby___ (赞：1)

## 思路
我们从前往后每次找出极长的一段 `ABAB...` 或 `BABA...`，很明显相邻两段是无法合并的，根据乘法原理计算每段可形成的形态的个数最后乘起来即可。  
`ABAB...` 或 `BABA...` 的形态个数我们可以用递推来预处理。设 $dp_i$ 表示长度为 $i$ 的 `ABAB...` 或 `BABA...` 的形态个数。递推式为：$dp_i=dp_{i-2}+1$。$dp_1$ 和 $dp_2$ 显然要初始化为 $1$。
## 代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
char a[250005];
long long int dp[250005];
int main() 
	dp[1] = 1;
	dp[2] = 1;
	for (int i = 1; i <= 250000; i++)dp[i] = dp[i - 2] + 1;
	long long int n;
	cin >> n;
	for (int i = 1; i <= n; i++)cin >> a[i];
	char lst = a[1];
	long long int ls = 1;
	long long int sum = 1;
	for (int i = 2; i <= n; i++) {
		if (a[i] == 'A') {
			if (lst == 'B')ls++;
			else {
				sum *= dp[ls];
				ls = 1;
			}
		}
		if (a[i] == 'B') {
			if (lst == 'A')ls++;
			else {
				sum *= dp[ls];
				ls = 1;
			}
		}
		lst = a[i];
		sum %= 1000000007;
	}
	sum *= dp[ls];
	sum %= 1000000007;
	cout << sum << endl;

	return 0;
}
```

---

## 作者：Targanzqq (赞：1)

### 主要思路：dp
遇到这种对于每个**形态**只统计一次的题，我们可以考虑加点式的 dp，就是每加一个点统计一次贡献。

令 $f_i$ 表示枚举到第 $i$ 个点的总形态数。我们从左到右每到一个点，我们让它继承它上一个点的贡献，即 $f_i=f_{i-1}$，表示枚举到这个点，**不选**这个点的贡献。

如果选这个点，我们考虑如果它能和前面的某些点发生转移，转移之后就变成了原来出现过的形态，而这种形态被 $f_{i-2}$ 包括了，所以我们加上 $f_{i-2}$ 的贡献。但是此时如果第 $i-1$ 个点也可以转移的话，那 $f_{i-3}$ 的贡献就被重复计算了，我们还要再减掉。

此时我们可以开一个数组 $v_i$ 表示第 $i$ 个点是否能与前面的点转移，而这个数组有个比较显然的性质，就是如果它不能与前面两个点转移，那么它在前面的点转移后，也不能与前面其他点转移。

```cpp
#include<bits/stdc++.h>
#define int long long
#define p 1000000007
using namespace std;

int n,f[300005],v[300005];
string s;

signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	cin>>s;
	f[0]=1;
	for(int i=1;i<n;i++){
		f[i]=f[i-1]; 
		if(i>=2&&s[i]!=s[i-1]&&s[i-1]!=s[i-2]){
			f[i]+=f[i-2];
			v[i]=1;
			if(v[i-1])f[i]-=f[i-3];
		}
		f[i]=(f[i]+p)%p;
	}
	cout<<f[n-1];
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

注意到一段长度为 $l$ 的 `ABABABA...`，设其能变化为 $f_l$ 种形态，可以注意到 $f_l = f_{l-2}+1$，递推即可。

那么我们可以将字符串中所有这种交替的找出来，根据乘法原理，答案为 $\prod_{i=1}^ k f_{l_i}$。

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef long long ll;
typedef double db;
const ll N=250005,mod=1e9+7;
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
ll n,s1,s2,ans=1,sum;
ll a[N],f[N];
char s[N];
ll qpow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1ll)
		  ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1ll;
	}
	return ans;
}
int main(){
	f[0]=f[1]=f[2]=1;
	for(int i=3;i<N;i++)
	  f[i]=f[i-2]+1;
	n=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
	  a[i]=s[i]-'A';
	for(int i=1;i<=n;i++){
		if(i==1)
		  sum=1;
		else{
			if(a[i]^a[i-1]==1)
			  sum++;
			else{
				ans=ans*f[sum]%mod;
				sum=1;
			}
		}
	}
	write(ans*f[sum]%mod);
	return 0;
}
```

---

## 作者：nightwatch.ryan (赞：1)

### 思路
我们可以将原来的字符串分成几段。遍历原来的字符串，如果前一个字符与当前字符一样，那么就用一个新字符串记录，否则继续在当前字符串尾部添加。最后计算每一个字符串的贡献，设字符串长度为 $size$，则这个字符串的贡献是 $\lfloor \dfrac{size+1}{2} \rfloor$，将这些贡献乘起来即可。

注意要对 $10^9+7$ 取模。
### 代码
```cpp
#include<iostream>
#define int long long
const int mod=1e9+7;
int read(){
 int x=0,t=1;char ch=getchar();
 while(ch<'0'||ch>'9'){if(ch=='-')t=-1;ch=getchar();}
 while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
 return x*t;
}
#define rd read()
#define N 250005
std::string t[N];
signed main(){
	int n=rd,idx=1;std::string s;
	std::cin>>s;
	s=" "+s;
	for(int i=1;i<=n;i++)
		if(s[i]==s[i-1])t[++idx]=s[i];
		else t[idx]+=s[i];
	int ans=1;
	for(int i=1;i<=idx;i++)
		if(t[i].size())
			ans=ans*((t[i].size()+1)/2)%mod;
	std::cout<<ans;
}
```

---

## 作者：201012280925LSY (赞：0)

## 题意
给出一段只有 `A`、`B` 的字符串，同时可以将其中为 `ABA` 的子串变为 `A`，`BAB` 的子串变为 `B`，要求经过若干次这样的操作后，能够形成几个不同的字符串（该字符串可以包含 `ABA` 或 `BAB`）。
## 思路
先来研究几个样例：

```ABA```

显然答案有 `ABA`、`A` 两种。

```ABABA```

答案有 `ABABA`、`ABA`、`A` 三种。

```ABABABA```

答案有 `ABABABA`、`ABABA`、`ABA`、`A` 四种。

所以规律就是：对于这种 `A`、`B` 交替出现的字符串，答案为 $\frac{n+1}{2}$。

根据这个规律，我们可以把给出的字符串分成几个部分（中间是连续的 `A` 或 `B`）。

例如第三个样例：

```BBABABAABABAAAABA```

可以被分成 `BABAB`、`ABABA`、`ABA`。通过乘法原理，我们可以把三个部分的答案乘起来，即可得到最终答案。即 $\frac{5+1}{2}\times\frac{5+1}{2}\times\frac{3+1}{2}=18$。

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
long long n,ans=1,sum=1;//从一开始，答案至少为1。
string st;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>st;
    for(int i=1;i<st.size();i++)//从一开始，避免越界。
    {
        if(st[i]!=st[i-1])sum++;//交替出现。
		else
		{
			if(sum%2==0)sum--;//若是偶数，说明是记录到了类似 ABABAB 的字符串，需要减一。
			ans*=(((sum+1)/2)%MOD);
			ans%=MOD;//记得取模。
			sum=1;
		}
    }
    if(sum!=1)ans*=(((sum+1)/2)%MOD),ans%=MOD;//如果结尾是AB交替出现的字符串。
    cout<<ans%MOD;
    return 0;
}
```
[记录](https://www.luogu.com.cn/record/163626541)

---

## 作者：incra (赞：0)

### Solution
不难发现每一个操作都是把字符串中删去若干个 $\texttt{AB}$，且满足 $\texttt{AB}$ 前面的字符是 $\texttt{B}$ 或者后面的字符是 $\texttt{A}$。

那么显然可以考虑一段连续的 $\texttt{AB}$ 组成的序列，答案就是所有连续极长段能保留的 $\texttt{AB}$ 的数量的积，设这段 $\texttt{AB}$ 左侧的字符为 $l$，右侧字符为 $r$，这段一共有 $c$ 个 $\texttt{AB}$。

若 $l=\texttt{B}$ 那么能从左侧删除，可以留下 $0\sim c$ 个 $\texttt{AB}$。

若 $r=\texttt{A}$ 那么能从右边删除，可以留下 $0\sim c$ 个 $\texttt{AB}$。

若上面两条都不满足，则只能从中间删，只能留下 $1\sim c$（读者自证不难）。

然后把能留下的 $\texttt{AB}$ 数量乘起来就完事了。
### Code
[Link](https://atcoder.jp/contests/arc180/submissions/55017163)。

---

## 作者：imljw (赞：0)

## 题目
有一个长为 $n$  的由 `A`  和  `B`  构成的字符串 $s$，你可以选择进行以下两种操作任意次(包括 $0$ 次)：

- 把该字符串的一个子串 `ABA` 替换为 `A`。

- 把该字符串的一个字串 `BAB` 替换为 `B`。

问通过上面两种操作，有多少种可能的s字符串，把答案对  $10 ^ 9 + 7$  取余并输出。

$1 \le n \le 250000$。

$s$ 是由 $A$ 与 $B$ 组成的字符串。
## 思路
我们可以很容易地发现，对于连续的 `AB` 和 `BA`，如 `BABABAB`，可以进行连续操作，等价于每次删一个 `AB` 或  `BA`，所以我么就可以把每一个长度大于 $2$ 的连续 `AB` 串的长度统计出来，非常明显，统计过的不重复统计。

举个栗子，`ABABABABBAB`，就只统计前面 `ABABABAB`，`BAB`，不统计 `ABA`，易得长度为 $n$ 的长串，可操作次数为 $\frac{n - 1}{2}$，不相交的长串明显是互相独立的，根据乘法原理，设每个长串的长度为 $b_1$ $\dots$ $b_n$，则答案就是 $\displaystyle \prod_{i=1}^{n}  \mathop{}\!\mathrm{\frac{b_i}{2} + 1} $。
## 代码
考时代码，仅供参考。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
long long an=1,mod=1e9+7;//答案明显会在过程中爆int。
char s[250005];
int main(){
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;i++){
		int j=i+1;
		while(j<=n&&s[j]!=s[j-1])j++;//统计超长AB串。
		j--;
		if(j-i>1)an*=((j-i)/2+1);//如果长度>2,统计答案。
		s[j]=s[i];
		i=j;//统计过的不重复统计。
		an%=mod;
	}
	printf("%lld",an);
	return 0;
```

---

## 作者：linjunye (赞：0)

### 思路
容易发现，如果我们能把原串分解成互不干扰的部分，那么，我们就可以用乘法原理求解。

什么部分是干扰的？什么部分是不干扰的？

如 `ABA` 与 `BAB` 就是互相干扰的部分 ，因为拼接后的 `ABABAB` 的方案数比分别计算 `ABA` 和 `BAB` 的方案数再相乘不同，可以自己手动尝试一下。

容易发现，我们可以将连续的 `AB` 串分为一个部分，证明如下（并不严谨）：

如果我们不能将连续的 `AB` 串分为一个部分，那么有两种可能：
- 这个串的其中一个子串会被两个部分分解。
- 这个串和与它相邻的串是互相干扰的。
#### 第一种可能
上面提到，这样的两个部分互相干扰（比如 `ABA` 与 `BAB`，将 `ABA` 替换成 `A`，或者是将 `BAB` 替换成 `B`，对于原串来讲，只有一种方案数），所以我们不能将这样的一个字串分成两部分。

如果把这个子串变成是单独的一部分，会有如下情况（这里的原串指上面的连续 `AB` 串）：
- 这个子串就是原串：没有任何事。
- 这个子串不是原串：那么必将还有其他子串，相邻的两个子串又是更大的子串的分解，根据上面的说法，是不行的。所以，这两个子串又需要并成一个串。

通过最终的不断合并，终究会合并成原串。

所以，这个串的其中一个子串不会被两个部分分解。
#### 第二种可能
我们刚才一直在说 __干扰__ ，意思似乎手造一造就懂了，但是在这里不行，我们需要 __更严谨__ 的定义。

什么串是互相干扰的？通过刚才讲解的第一种可能，我们发现，互相干扰的串满足一种性质：

- 虽然两个串好像可以互相单独计算，但是一些方案对于原串来讲，就只有一种方案数。

我们发现，如果这两个串拼接后，是一个连续的 `AB` 串，那么，你不管是对左边还是对右边做操作，都一样。

为什么哪？

观察替换：

- `ABA` $\rightarrow$ `A`。
- `BAB` $\rightarrow$ `B`。

这不就是删除一个 `AB` 串吗？

那么，一个连续的 `AB` 串对左边或对右边做操作，就都等价于删掉一个 `AB` 串。

由于连续 `AB` 串是由若干个 `AB` 串加某些字符组成，做出以下分类讨论：

- 没有加任何字符。删除任意地方的一个 `AB` 串还是由若干 `AB` 串组成，并没有改变顺序。
- 有时开头多一个 `B`，或结尾多一个 `A`，或两个都有。但我们也只是删除中间的字符（够不到），所以依旧是若干个 `AB` 串加这些字符组成，并没有改变它们的顺序。

这里的顺序仅仅是指 `AB` 串与多余字符之间的位置关系。

刚刚我们说了，如果这两个串拼接后，是一个连续的 `AB` 串，那么，你不管是对左边还是对右边做操作，都一样。

所以，如果这两个串拼接后是一个连续的 `AB` 串，它们互相干扰，反之不干扰（这里我就不证明了，可以按照我的方法试着证明）。

如果这两个串拼接后是一个连续的 `AB` 串，那么，我们找的连续 `AB` 串不应该是这个，这是不可能的。

所以，这个串和与它相邻的串是不互相干扰的。

综上所述，我们可以将连续的 `AB` 串分为一个部分。

那么，剩下的就是一个问题了：

- 连续 AB 串的方案数是多少？

容易发现，每次操作都是删除一个 `AB` 串，好像是 $\lfloor\frac{|s|}{2}\rfloor+1$，但是变形终究是变形，形变意不变，当 $|s|\bmod 2=0$ 时，是没有空串的，没有 $+1$。

但是 $|s|\bmod 2=1$ 时，有 $+1$。

怎么办？

很简单，变成 $\lceil\frac{|s|}{2}\rceil$ 就行了。

为了编码简便，可以变成 $\lfloor\frac{|s|+1}{2}\rfloor$。
### 代码
代码 $30$ 行，蕴含着我们的人类智慧！
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n;
string s;
string t;
int ans=1;
int cal(string t){
	//cal蕴含着我们的人类智慧（cal的可行性，什么条件下使用cal，cal的计算过程）
	return (t.size()+1)/2;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	cin>>s;
	for(int i=0;i<n;i++){
		if(t!=""&&t[t.size()-1]==s[i]){//不是连续AB串了 
			ans=(ans*cal(t))%mod;//乘法原理 
			t="";
		}
		t+=s[i];
	}
	ans=(ans*cal(t))%mod;//最后可能还有剩余 
	cout<<ans;
	return 0;
}

```

---


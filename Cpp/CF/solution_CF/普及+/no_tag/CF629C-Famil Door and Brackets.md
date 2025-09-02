# Famil Door and Brackets

## 题目描述

As Famil Door’s birthday is coming, some of his friends (like Gabi) decided to buy a present for him. His friends are going to buy a string consisted of round brackets since Famil Door loves string of brackets of length $ n $ more than any other strings!

The sequence of round brackets is called valid if and only if:

1. the total number of opening brackets is equal to the total number of closing brackets;
2. for any prefix of the sequence, the number of opening brackets is greater or equal than the number of closing brackets.

Gabi bought a string $ s $ of length $ m $ ( $ m<=n $ ) and want to complete it to obtain a valid sequence of brackets of length $ n $ . He is going to pick some strings $ p $ and $ q $ consisting of round brackets and merge them in a string $ p+s+q $ , that is add the string $ p $ at the beginning of the string $ s $ and string $ q $ at the end of the string $ s $ .

Now he wonders, how many pairs of strings $ p $ and $ q $ exists, such that the string $ p+s+q $ is a valid sequence of round brackets. As this number may be pretty large, he wants to calculate it modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample there are four different valid pairs:

1. $ p= $ "(", $ q= $ "))"
2. $ p= $ "()", $ q= $ ")"
3. $ p= $ "", $ q= $ "())"
4. $ p= $ "", $ q= $ ")()"

In the second sample the only way to obtain a desired string is choose empty $ p $ and $ q $ .

In the third sample there is no way to get a valid sequence of brackets.

## 样例 #1

### 输入

```
4 1
(
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 4
(())
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4 3
(((
```

### 输出

```
0
```

# 题解

## 作者：火羽白日生 (赞：7)

> 给定一个长度为 $m$ 的括号字符串，在其前后加上左右括号使其为 `有效` 的括号字符串，求方案数。

> 其中 `有效` 定义为：

> * 左右括号数量相等。

> * 对于任意一个前缀总有左括号数量大于等于右括号数量。

发现 $n-m\leq 2000$，考虑基于 $n-m$ 的 DP。

设 $f_{i,j}$ 为前 $i$ 个字符，左括号数量减去右括号数量为 $j$ 的方案数。

起始有：$f_{0,0}=1$。

转移有：

$$f_{i,j}=f_{i-1,j-1}+f_{i-1,j+1}$$

对于长度为 $i$ 的括号字符串，它只能由长度为 $i-1$ 的括号字符串加上左括号或右括号转移而来，所以就是上面的式子。

接下来枚举符合条件的 $\texttt P$ 和 $\texttt Q$，用乘法原理计算答案。

第一层枚举 $\texttt P$ 的长度，第二层枚举 $\texttt P$ 左括号减去右括号的数量。

首先要满足 $\texttt P$ 中左括号减右括号的数量能补得完 $\texttt S$ 所有前缀中右括号减左括号数量最多的前缀。

然后再满足 $\texttt Q$ 中右括号减左括号的数量能补得完 $\texttt P$ 和 $\texttt S$ 中左括号减右括号的数量。

此时 $\texttt P$ 的方案数显然是 $f_{i,j}$，主要是 $\texttt Q$ 的方案数。

显然 $\texttt Q$ 的长度为 $n-m-i$，想到左右括号可以等价，那么就把原串反转来看，那么最终方案数就是 $f_{n-m-i,j+cnt}$ （$cnt$ 为 $\texttt S$ 中左括号比右括号多的数量）。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout);
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(y,x,sizeof(x))
	
	const int maxn=2e3+5,maxm=1e5+5,mod=1e9+7;
	
	int n,m,cnt,minn=0x3f3f3f3f,ans;
	int f[maxn][maxn];
	char s[maxm];
	
	inline int main(){
		n=read(); m=read();
		scanf("%s",s+1);
		f[0][0]=1;
		for(int i=1;i<=2000;i++){//get f
			f[i][0]=f[i-1][1];
			for(int j=1;j<=i;j++)
				f[i][j]=(f[i-1][j-1]+f[i-1][j+1])%mod;
		}
		for(int i=1;i<=m;i++){//clac delta num['(']-num[')'] of S
			if(s[i]=='(') cnt++;
			else cnt--;
			minn=min(minn,cnt);//max of delta num[')']-num['('] of S
		}
		for(int i=0;i<=n-m;i++)//for length of P
			for(int j=0;j<=i;j++)//for delta num['(']-num[')'] of P 
				if(j+minn>=0 && j+cnt<=n-m-i)//be sure that num['('] of P and num[')'] of Q are enough
					ans=(ans+1ll*f[i][j]*f[n-m-i][j+cnt]%mod)%mod;
		printf("%d\n",ans);
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：Anins (赞：2)

# CF629C Famil Door and Brackets

## 题意

给定一长度为 $m$ 且包含 `(` 及 `)` 的字符串 $S$ ，要求构造两个只包含 `(` 及 `)` 的字符串 $P,Q$ ，使得 $P+S+Q$ 满足以下条件：

1. $P+S+Q$ 的长度为给出的 $n$ 。

2. $P+S+Q$ 中 `(` 与 `)` 的数量相等。

3. 对于 $P+S+Q$ 中的任意位置的前缀满足 `(` 的数量不小于 `)` 的数量。

求满足构造条件的 $P,Q$ 的方案总数，并输出其对 $10^9+7$ 取余的值。

## 思路

题目中给出 $n-m \le 2000$ 且只需求出结果，故想到使用 DP 进行求解。

### 预处理

预处理 $S$ 串，求出在 $P$ 中需要补齐 `(` 的最小数量，使得 $P+S$ 满足条件 $3$ 。

### 动态规划

设状态 $f(i,j)$ 表示为前 $i$ 个字符中 `(` 与 `)` 之差为 $j$ 的方案总数。

因为 $0 \le n \le 2000$ 所以我们只需求出 $2000$ 以内的所有情况的值即可。

对于状态转移有：

- 起始为 $f(0,0)=1$ 

- 转移方程为 $\large{f(i,j)=f(i-1,j+1)+f(i-1,j-1)}$

### 计算结果

1. 枚举 $P$ 的长度 $i$ 。

2. 枚举 $P$ 中的 `(` 与 `)` 之差，要求 `(` 与 `)` 之差满足对于 $S$ 中任意位置前缀都满足 `(` 大于 `)` 数量。

3. 则 $Q$ 的长度为 $n-m-i$ ，验证能否构造出 $Q$ 使得 $P+S+Q$ 满足所有条件。
4. 若满足则通过 **乘法原理** 统计对于该长度的 $P$ 的所有构造方案数量，并通过 **加法原理** 统计对所有方案进行求和。

更多详情请看代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 1e9+7;
ll n, m, minn, ans, z, f[2005][2005];
string S;
int main() {
	cin >> n >> m >> S; //n表示需构造字符串长度， m为初始字符串长度
	for (int i = 0; i < (int)S.length(); i++) {
		S[i] == '(' ? z++ : z--; //对s中的前i个字符的括号抵消情况进行判断
		minn = min(z, minn); //求S中'('缺失最多的情况
	}
	f[0][0] = 1; //f[0][0]只有一种情况就是字符串为空
	for (int i = 1; i <= 2000; i++) { //枚举长度，依次增加
		f[i][0] = f[i - 1][1]; //(0-1)<0所以无需计算
		for (int  j = 1; j <= i; j++) //枚举'('与')'之差
			f[i][j] = (f[i - 1][j - 1] + f[i - 1][j + 1]) % mod;
	}
	for (int i = 0; i <= n - m; i++) //枚举P的长度，其中'n-m'指P和Q的总长度
		for (int  j = 0; j <= i; j++) //枚举在P中'('与')'的差
			if (j + minn >= 0 && j + z <= (n - m - i)) 
			/*使P中'('与')'的差能够满足补齐S中少的'(' 且 使构造的Q能使P+S+Q中'('')'数量相等，即Q的长度不小于P+S中'('与')'的差*/
				ans = (ans + (f[i][j] * f[n - m - i][j + z]) % mod) % mod;
	cout << ans << endl;
	return 0;
}
```
完结撒花！

---

## 作者：Hisaishi_Kanade (赞：2)

首先这个题只是求方案，大概可以猜到是 dp 了。

看看数据范围，特意给出了 $n-m\le 2000$ 应该是基于这个东西了。

我们考虑，设 $f_{i,j}$ 表示写了 $i$ 个括号，`(` 个数减去 `)` 个数为 $j$ 的方案数。

显然的对于 $f_{i,j}$ 的 $i$，我写左括号那么方案数时 $f_{i,j}$ 从 $f_{i,j-1}$ 转移过来，写右括号自然从 $f_{i,j+1}$ 转移。

综上就有 $f_{i,j}=f_{i,j-1}+f_{i,j+1}$。

接下来考虑对 $P,Q$ 的方案合并统计。

首先枚举出 $P$ 的长度 $l_p$，显然 $Q$ 的长度是 $n-m-l_p$。

接下来就是枚举 $P$ 中 `(` 个数减去 `)` 个数 $d_p$，整个序列的左括号右括号个数是相同的，因为 $d_p+d_q+d_s=0$ 那么 $Q$ 中两者之差自然就是 $d_q=-d_p-d_s$。但是如果这个显然是非正数。因为如果 $d_q>0$，则 $d_p+d_s<0$，这个时候 $Q+S$ 这个部分已经不合法了。

$f$ 的下标我们自然是不希望为负。发现，其实左括号减去右括号为 $x$ 的每个方案，左括号变成右括号，右括号变成左括号，便对应 $-x$ 的方案。

也就是 $f_{i,-x}=f_{i,x}$。

所以对于枚举出来的 $P$，$Q$ 的方案为 $f_{n-m-l_p,d_p+d_s}$。

乘法原理求出这种情况方案，再加法原理，做完了。

```cpp
/*
设 f[i][j] 表示前 i 个，cnt[(]-cnt[)] 的数量为 j 的方案数。
这个可以做出 P,Q 的样子啊。
接下来枚举 P 的长度，lp+lq+ls=n
然后枚举 P 的 cnt[(]-cnt[)] 的值。
需要满足 dertap+dertaq+dertas=0
左右翻转一下一样的，直接乘法原理即可。
比如枚举出 p[lp][dertap]，那么 lq=n-ls-lp, dertaq=-dertas-dertap->dertap+dertas
*/
#include <bits/stdc++.h>
#define int long long
#define rep(i,l,r) for(i=l;i<=r;++i)
using namespace std;
const int N=100005,p=1e9+7;
int f[2015][2015];
char str[N];
int i,j,x,mrex=p,n,m,ret;
inline void pre()
{
	f[0][0]=1;
	rep(i,1,2005)
	{
		f[i][0]=f[i-1][1];
		rep(j,1,i)f[i][j]=(f[i-1][j-1]+f[i-1][j+1])%p;//,printf("%d %d %d\n",i,j,f[i][j]);
	}
	return ;
}
inline int gmax()
{
	rep(i,1,m)
	{
		if(str[i]=='(')++x;else --x;
		mrex=min(mrex,x);
	}
	return mrex;
}
inline int solve()
{
	pre();
	gmax();
//	if(n>2000)printf("%d %d\n",x,mrex);
	rep(i,0,n-m)
		rep(j,0,i)
		{
			if(j>=-mrex && j+x<=n-m-i)
			{
//				printf("%d %d %d %d %d %d\n",i,j,f[i][j],n-m-i,j+x,f[n-m-i][j+x]);
				(ret+=(f[i][j]*f[n-m-i][j+x])%p)%=p;
			}
//			printf("%d %d %d\n", i, j, ret);
		}
	printf("%lld",ret);
	return 0;
}
signed main()
{
	scanf("%d %d %s", &n, &m, str+1);
	solve();
	return 0;
}
```

---

## 作者：water_tomato (赞：2)

## 题意

给出一个长度为 $m$ 的括号串，在其前后增添字符构造长度为 $n$ 的合法括号串，求方案数。满足 $n-m \le 2000$。

## 解析

容易发现这是一道 dp 且复杂度基于 $n-m$。

我们已知中间的那条括号串 $S$，需要构造出左边的 $P$ 和右边的 $Q$（当然也可能为空）。通过 dp 方程转移时，考虑需要满足的两个条件，及 '(' 和 ')' 的数量以及前缀。由于对于任何前缀，均满足 '(' 的数量大于等于 ')' 的数量，我们可以定义 $f_{i,j}$ 为 $i$ 个字符，'(' 的数量减去 ')' 的数量为 $j$ 的总方案数。

求出 $f$ 数组后，接着我们可以枚举 $P$ 和 $Q$，考虑他们所需要满足的条件。

- 如果 $S$ 中有一段前缀 ')' 比 '(' 多，那么 $P$ 显然是需要弥补的（即 '(' 要比 ')' 多），而所最少需要弥补的数量就为 ')' 比 '(' 多最多的那个前缀。
- $P$ 和 $S$ 总的 '(' 的数量减去 ')' 的值不能比 $Q$ 长，这是显然的。

如此我们容易地枚举了 $P$ 和 $Q$，计算贡献显然就是乘法原理。$P$ 的价值显而易见为 $f_{i,j}$，而 $Q$ 的价值为 $f_{n-m-i,j+tmp}$( $tmp$ 为 $S$ 中 '(' 的数量减去 ')' 的值)。为什么呢？我们可以逆向思维，从后往前构筑 $Q$，那么前缀条件的定义就反了一下，也就自然得到了这个式子，应当可以自行理解。

将每组的 $P$ 和 $Q$ 的贡献乘起来再累加即可得到答案

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=2050;
const int M=2e5+5;
const int mod=1e9+7;	
int n,m,f[N][N],minn,ans,tmp;//f 表示 i 个字符，j=num'(' - num')'
char s[M];
signed main(){
	scanf("%lld%lld",&n,&m);
	scanf("%s",s+1);
	f[0][0]=1; 
	for(int i=1;i<=2000;i++){//保证前缀和满足的情况下的方案数 
		f[i][0]=f[i-1][1];
		for(int j=1;j<=i;j++){
			f[i][j]=(f[i-1][j-1]+f[i-1][j+1])%mod;
		}
	}
	for(int i=1;i<=m;i++){//统计右括号最多比左括号多的，左边要补；
		if(s[i]=='(') tmp++;//以及 num'(' - num')'   
		else tmp--;
		minn=min(tmp,minn);
	}
	for(int i=0;i<=n-m;i++){
		for(int j=0;j<=i;j++){
			if(j+minn>=0&&j+tmp<=n-m-i){//左边及给出的串保证前缀符合且前缀不会大到右边补不回来 
				ans=(ans+(f[i][j]*f[n-m-i][j+tmp])%mod)%mod;//逆向思维 
			}
		}
	}
	printf("%lld\n",ans); 
	return 0;
}
```



---

## 作者：OE_AiHAn (赞：1)

## [CF629C](https://codeforces.com/contest/629/problem/C)
蒟蒻的第一篇题解，写的不好请大佬指教。>w<

### 题意
给定长度为 $m$ 的仅含 `(` 和 `)` 的字符串，为其左右补上两个字符串使其达到指定长度 $n$ 且合法, 需补足字符串合计长度 $n - m$ 满足 $n - m \le 2000$。

### 解析
字符串合法条件为：
>左右括号总数相等；
>
>从左数起在任意位置上左括号数量不小于右括号数量。

首先思考下左侧的合法状况，设 $f^1_{i,j}$ 为前 $i$ 个字符使用了 $j$ 个 `(` 时的方案数，有 $f^1_{0,0} = 1$，得到状态转移方程为：
$$f^1_{i,j} = f^1_{i - 1, j - 1} + f^1_{i - 1, j}$$
然后思考下另一侧，题意表明左右括号总数相等，且从左数起一定有左括号数 $l$ 不小于右括号数 $r$，即
$$l \ge r$$
可化成
$$\frac{n}{2} - l \le \frac{n}{2} - r$$
即从右数起在任意位置上右括号数量不小于左括号数量。由此，可设 $f^2_{p, q}$ 为从右数起前 $p$ 个字符使用了 $q$ 个 `)` 时的方案数，状态转移方程同上。

最后，枚举左右状态并利用乘法原理即可算出答案，设需补足的右括号共为 $tr$ 个，对于任意状态下都有 $p = n - m - i$ 和 $q = tr - (i - j)$。

### 代码
```c++
#include<bits/stdc++.h>
#define LL long long 

using namespace std;

vector<vector<LL> > dp1(2005, vector<LL>(2005, 0)), dp2(2005, vector<LL>(2005, 0));
LL mod = 1000000007;
//要开long long，不然#4可能会炸精度

signed main()
{
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

	LL n, m, tl = 0, tr, nl = 0, nr = 0, ml = 0, mr = 0, ans = 0;
	string s;
	cin >> n >> m;
	getline(cin, s);
	getline(cin, s);

	for (int i = 0; i < m; i++)
	{
		tl += s[i] == '(';
		nl += 2 * (s[i] == ')') - 1; //计算当前右左括号数量差
		ml = max(ml, nl); //存储最大差值
						  //左方插入字符串左右括号数量差至少达到ml
	}
	//反向遍历一次计算左右括号数量差值，作用同上
	for (int i = m - 1; i > -1; i--)
	{
		nr += 2 * (s[i] == '(') - 1;
		mr = max(mr, nr);
	}

	if (tl > n / 2 || m - tl > n / 2 || n & 1)
	{
		//将完全不合法的情况直接排除
		cout << "0";
		return 0;
	}
	tl = n / 2 - tl;
	tr = n - m - tl;
	//tl和tl分别表示外部插入字符串总共需要的左右括号数量

	//计算左侧合法情况
	dp1[0][0] = 1;
	for (LL i = 1; i <= min(n - m, tl * 2); i++)
		for (LL j = 0; j <= min(i, tl); j++)
			if (i - j <= j && i - j <= tr)
				dp1[i][j] = (dp1[i - 1][j - 1] + dp1[i - 1][j]) % mod;

	//计算右侧合法情况
	dp2[0][0] = 1;
	for (LL i = 1; i <= min(n - m, tr * 2); i++)
		for (LL j = 0; j <= min(i, tr); j++)
			if (i - j <= j && i - j <= tl)
				dp2[i][j] = (dp2[i - 1][j - 1] + dp2[i - 1][j]) % mod;

	//乘法原理计算答案
	for (int i = 0; i <= n - m; i++)
		for (int j = 0; j <= i; j++)
			if (j - (i - j) >= ml && tr - (i - j) - (tl - j) >= mr) //判断左右侧的左右括号数是否达到要求
				ans = (ans + dp1[i][j] * dp2[n - m - i][tr - i + j]) % mod;

	cout << ans;
}
```

最后祝各位顺利AC。  >w<

---


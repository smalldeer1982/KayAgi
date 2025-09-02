# Strange Operation

## 题目描述

Koa the Koala has a binary string $ s $ of length $ n $ . Koa can perform no more than $ n-1 $ (possibly zero) operations of the following form:

In one operation Koa selects positions $ i $ and $ i+1 $ for some $ i $ with $ 1 \le i < |s| $ and sets $ s_i $ to $ max(s_i, s_{i+1}) $ . Then Koa deletes position $ i+1 $ from $ s $ (after the removal, the remaining parts are concatenated).

Note that after every operation the length of $ s $ decreases by $ 1 $ .

How many different binary strings can Koa obtain by doing no more than $ n-1 $ (possibly zero) operations modulo $ 10^9+7 $ ( $ 1000000007 $ )?

## 说明/提示

In the first sample Koa can obtain binary strings: $ 0 $ , $ 00 $ and $ 000 $ .

In the second sample Koa can obtain binary strings: $ 1 $ , $ 01 $ , $ 11 $ , $ 011 $ , $ 101 $ and $ 0101 $ . For example:

- to obtain $ 01 $ from $ 0101 $ Koa can operate as follows: $ 0101 \rightarrow 0(10)1 \rightarrow 011 \rightarrow         0(11) \rightarrow 01 $ .
- to obtain $ 11 $ from $ 0101 $ Koa can operate as follows: $ 0101 \rightarrow (01)01 \rightarrow 101 \rightarrow         1(01) \rightarrow 11 $ .

Parentheses denote the two positions Koa selected in each operation.

## 样例 #1

### 输入

```
000```

### 输出

```
3```

## 样例 #2

### 输入

```
0101```

### 输出

```
6```

## 样例 #3

### 输入

```
0001111```

### 输出

```
16```

## 样例 #4

### 输入

```
00101100011100```

### 输出

```
477```

# 题解

## 作者：w4p3r (赞：28)

### 一丶思路

考虑一个合法的字符串$t$有什么性质。

首先$t$是$s$的一定子序列。~~（废话）~~

其次$t$的$1$的数量一定小于等于$s$的$1$的数量。~~（也是废话）~~

其次对于$t$的数量为$p$的一**段**$0$，一定也能在$s$中找到数量为$q$的一**段**$0$，使得$q>=p$（**我们在下文称这种关系叫匹配**）。并且$t$任意两端$0$在$s$对应的位置之间要满足$1$的数量大于等于在$t$中这两段之间$1$的数量。

最后一点，$t$的前缀$0$必须匹配$s$的前缀$0$，$t$的后缀$0$必须匹配$s$的后缀$0$。

（如果没理解可以想一想/画个例子看看）

此时对于一个$t$，我们肯定有很多种匹配的方案。但假设我们还要往$t$后面加字符的话，哪种方案可以使我们加尽量多的字符呢？

贪心地想，我们对于$t$每一段$0$，让其匹配$s$中最前面的一段合法的$0$，这样一定是最优的，而且**这种贪心保证了我们计算方案不会算重**。

此时如果我们按$0/1$段去$DP$，就可以做到$O(n^2)$的时间复杂度了（记录匹配到哪一段和当前长度）。但是很遗憾$O(n^2)$并不能通过此题，所以我们寻求一种更简单的方法。

我们考虑单个字符的去$DP$。我们可以发现，我们并不关心$t$的当前长度，我们只关心$t$在$s$匹配到了哪一位。所以假设$f[i][j]$表示我们现在匹配到了$s$第$i$个字符，当前$t$的最后一位是$j$的方案数。

如何转移呢？考虑求出一个$next[i][j]$表示在匹配到$s$的第$i$位后选$j$会匹配到的位置。

那么$DP$方程就是十分简单的$f[i][p]->f[next[i][j]][j]$了。（箭头表示有贡献）

那么$next$数组如何求呢？

如果$j=1$，那么其求的就是$s$中下一位$1$的位置。

如果$j=0$，如果$s[i]=1$或者$s[i+1]=0$，那么其就等于下一位$0$的位置。否则假设$i$所在的这段$0$有$p$个$0$，在$i$后面找到最小的$x(s[x]=0)$使得$x$所在的段的$0$数量大于$p$，且$x$是这一段的开头。则$next[i][j]=x+p$。（这个东西可以用一个单调栈求）。

至于前缀$0$和后缀$0$的问题，我们可以特判一下，并强制第$1$位/最后$1$位选$1$即可。

然后我们就完美地解决了该题，时间复杂度$O(n)$。

### 二丶代码


```cpp
//Badwaper gg
#include<bits/stdc++.h>
#define inf 1e9
#define eps 1e-6
#define mp make_pair
#define pb push_back
#define re register ll
#define fr first
#define sd second
#define FOR(i,a,b) for(re i=a;i<=b;i++)
#define REP(i,a,b) for(re i=a;i>=b;i--)
#define lowbit(x) x&(-x)
#define Z(x) (x>=mod?x-mod:x)
#define N 1000010
#define pa pair<int,int>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
inline ll read()
{
	char ch=getchar();
	ll s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
const int mod=1e9+7;
int f[N][2],Next[N][2];
int n;char s[N];int a[N];
struct node
{
	int l,r,len;
}p[N],st[N];
int tot,top;
inline int check(){FOR(i,1,n)if(a[i]==1)return 0;return 1;}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);
	FOR(i,1,n)a[i]=s[i]-'0';int t=n+1,x=0,y=0;
	if(check()){printf("%d\n",n);return 0;}//全是0要特判
	FOR(i,1,n){if(a[i]==1){x=i;break;}}
	REP(i,n,1){if(a[i]==1){y=n-i+1;break;}}
	REP(i,n,0)
	{
		Next[i][1]=t;
		if(a[i]==1)t=i;
	}//直接找下一位1的位置
	t=n+1;
	Next[0][0]=n+1;//强制第一位选1
	REP(i,n,1)
	{
		if(a[i]==1)Next[i][0]=t;
		if(a[i]==0)t=i;
	}
	FOR(i,1,n){if(a[i]==0&&a[i+1]==0)Next[i][0]=i+1;}
	for(re l=1,r;l<=n;l=r+1)
	{
		r=l;
		if(a[l]==1)continue;
		while(a[r+1]==0&&r+1<=n)r++;
		p[++tot]=(node){(int)l,(int)r,(int)r-(int)l+1};
	}//求出每一段0
	REP(i,tot,1)
	{
	    while(top&&p[i].len>=st[top].len)top--;//维护单调栈
		if(!top){Next[p[i].r][0]=n+1;st[++top]=p[i];continue;}
		else {Next[p[i].r][0]=st[top].l+p[i].len;st[++top]=p[i];}
	}
	f[0][0]=1;int ans=0;
	FOR(i,0,n)
	{
		FOR(j,0,1)FOR(k,0,1)
		{
			if(Next[i][k]<=n)f[Next[i][k]][k]=Z(f[i][j]+f[Next[i][k]][k]);
		}
		ans=Z(ans+f[i][1]);//强制最后一位选1
	}
	ans=1LL*ans*x%mod*y%mod;//把前缀/后缀0的贡献加上
	printf("%d\n",ans);
	return 0;
}
```
**如果你觉得这篇题解对你有帮助，那你可以点个赞支持我一下qwq。如果你对题解有任何问题/认为我的题解有任何问题，可以私信/在评论区发出来，当然如果你对我的题解有任何意见/建议也欢迎指出。我会尽我全力把我题解写到最好的qwq**

---

## 作者：Alex_Wei (赞：27)

> B. [CF1383E Strange Operation](https://www.luogu.com.cn/problem/CF1383E) *2800

考虑一次操作的本质。

若为 $00$，$10$ 或 $01$ 则 $0$ 的个数减 $1$，否则 $1$ 的个数减 $1$。

直接对操作序列计数难以去重，因此一般均考虑对最终得到的 $01$ 串计数。

我们发现每次操作可以减少相邻两个 $1$ 之间的 $0$ 的个数，或直接删掉下标相邻的两个 $1$ 之间用于填放 $0$ 的空隙，于是尝试设相邻两个 $1$ 之间 $0$ 的个数序列为 $a$，注意开头和结尾的连续若干个 $0$ 也要算上。举例，若 $s = \texttt {001011001}$，则 $a = \{2, 1, 0, 2, 0\}$。

显然，一个 $a$ 和一个 $01$ 串一对应。因此考虑对 $a$ 序列计数。

设原 $01$ 串相对应的序列为 $b$。尝试探究 $a$ 能被 $b$ 生成的充要条件。

这个有点困难，我们先观察一次操作对 $b$ 的影响，再反推条件。显然，每次操作可以将 $b$ 的某个不为 $0$ 的数减 $1$，或者删掉 **不在开头或结尾** 的 $0$。

发现 $a$ 的两端元素的取值相对独立，因为在操作过程中它们一直不会被删去（换言之，**直接删去某个数是导致重复的罪魁祸首**。若不可以删去数，答案显然为 $\prod\limits_{i = 1} ^ {|b|} (b_i + 1)$）。根据乘法原理，答案首先乘上 $a_1$ 和 $a_{|a|}$ 的取值范围，即 $(b_1 + 1)(b_{|b|} + 1)$。接下来忽略掉 $a$ 的两端和 $b$ 的两端。

根据操作的具体内容，不难得到 $a$ 被 $b$ 生成的充要条件：存在序列 $i$ 满足 $1 \leq i_1 < \cdots < i_{|a|} \leq |b|$，使得 $a_j \leq b_{i_j}(1\leq j \leq |a|)$。

容易判定 $a$ 被 $b$ 生成，形如子序列自动机。记录指针 $p$ 表示当前 $b$ 匹配到的位置，初始值为 $0$。贪心找到大于 $p$ 的最小的位置 $q$ 使得当前 $a$ 匹配到的位置 $a_j \leq b_q$，令 $j$ 加 $1$ 且 $p \gets q$。重复该过程直到 $j > |a|$（成功）或 $q$ 不存在（失败）。

根据判定过程就可以 DP 了。设 $f_i$ 表示匹配到 $b_i$ 的序列 $a$ 的个数。$a$ 的长度不影响转移，所以无需记录。

两种转移方法，一是枚举下一个 $a$ 值是什么，并匹配到相应位置 $j(i < j)$，$f_i$ 贡献给 $f_j$，但这样太劣了。直接考虑 $f_i$ 对 $f_j(i < j)$ 的贡献系数，不难发现，当 $a$ 值小于等于 $b_{i + 1} \sim b_{j - 1}$ 当中任何一个数时，匹配在 $j$ 之前停止。因此贡献系数为 $\max\left(0, b_j - \max\limits_{p = i + 1} ^ {j - 1} b_p\right)$。

因为贡献系数主要与 $j$ 有关，从 $i$ 转移过去的角度考虑不方便。转换角度，$j$ 受到 $i$ 的贡献。

有 $i, j$ 之间的最大值，容易想到单调栈。维护从左（栈底）到右（栈顶）递减的单调栈，那么当前栈中存储的所有元素即可以影响到 $\max\limits_{p = i + 1} ^ {j - 1} b_p$ 的 $b_1 \sim b_{j - 1}$ 的 **后缀最大值 $p_1 < \cdots < p_c$**。

我们发现，对于 $i\in [p_{k - 1}, p_k)$，它们对 $f_j$ 的贡献系数都是 $b_{p_k}$。而对于 $\geq b_j$ 的 $p_k$，$p_k$ 左边的元素显然无法贡献至 $f_j$。而弹栈时只会弹出 $\leq b_j$ 的栈顶，因此直接在弹栈的时候计算贡献即可。

需要使用前缀和优化求出一段区间的 $f$ 值之和。时间复杂度线性。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
const int mod = 1e9 + 7;
char s[N];
int n, lft, rt, sum, ans = 1;
int top, stc[N], pos[N], f[N];
int main() {
	cin >> s + 1, n = strlen(s + 1);
	lft = 1, rt = n;
	while(lft <= n && s[lft] == '0') lft++;
	while(rt && s[rt] == '0') rt--;
	if(lft > rt) cout << n << endl, exit(0);
	stc[0] = 1e9, pos[0] = f[1] = 1;
	for(int i = lft, cnt = 2; i < rt; cnt++) {
		int p = i + 1, L = 1;
		while(s[p] == '0') p++, L++;
		int res = 0, ht = 0, ps = cnt - 1;
		while(L > stc[top]) {
			res = (res + 1ll * (f[ps] - f[pos[top] - 1] + mod) * (L - ht)) % mod;
			ht = stc[top], ps = pos[top--] - 1;
		}
		res = (res + 1ll * (f[ps] - f[pos[top] - 1] + mod) * (L - ht)) % mod;
		ans = (ans + res) % mod;
		f[cnt] = (res + f[cnt - 1]) % mod;
		stc[++top] = L;
		pos[top] = cnt;
		i = p;
	}
	cout << 1ll * ans * lft % mod * (n - rt + 1) % mod << endl;
	return 0;
}
```

---

## 作者：Soulist (赞：12)


给定一个 01 串 $a$，$n=|a|$，你可以执行不超过 $n-1$ 次操作，每次为选择一个 $i\in [1,|a|)$，然后令 $a_i=\max\{a_i,a_{i+1}\}$，将 $a_{i+1}$ 删除。

求你可以得到多少个串，答案对 $10^9+7$ 取模。

$\rm Sol:$

感觉挺套路的。

考虑怎么样的一个串可以得到，首先发现一组 $01$ 和 $10$ 都只能删 $0$，$11$ 和 $00$ 删的是谁我们其实不太关心。

然后发现最后剩余的串是 $S$ 的子序列，然后发现一个 $1$ 能被删除当且仅当这个 $1$ 满足其两端存在至少一个 $1$

于是对于 $S$ 的子序列 $T$，其能够生成，当且仅当其中两个相邻的 $0$ 之间没有 $1$，然后假设以 $0$ 开头/结尾，那么前缀/后缀没有 $1$

直接做不太好做，考虑进一步简化信息，对于相邻的两个 $1$，我们记 $pre_i$ 表示第 $i$ 个 $1$ 和第 $i-1$ 个 $1$ 之间的 $0$ 的数量，同时补充结尾段（可以为 $0$，如果 $S$ 中不存在 $1$ 特判），这样串 $S$ 变成了一个序列 $\{pre\}$ 接下来我们考虑如何判定一个串 $T$ 能否生成。

类似的将 $T$ 变成一个这样的序列，不难发现 $T$ 合法当且仅当：

1. $T$ 的开头和结尾元素比 $S$ 的开头/结尾元素小。
2. 对于 $T$ 的中间部分，可以与 $S$ 匹配，即 $S$ 存在一个子序列 $\{b\}$ 满足 $b$ 的对应元素均大于等于 $T$ 的对应元素。

那么可以类似于子序列自动机的做法来 dp，去除开头/结尾部分后，对中间部分进行 dp。

考虑在位置 $i$ 填入 $j$ 时，从 $k$ 处转移的条件为 $[k+1,i-1]$ 这个区间内不存在 $pre_x\ge j$，那么可以维护一下对于每个 $j$，最大的满足条件的 $x$ 即可（每次处理完一个 $i$ 后暴力更新即可）。

然后用前缀和优化一下转移，就做完了。复杂度是 $\mathcal O(\sum pre_i)=\mathcal O(n)$

不难发现这个算法默认序列中存在至少一个 $1$，所以要特判全 $0$

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 1e6 + 5 ; 
const int P = 1e9 + 7 ; 
int n, m, pre[N], w[N], dp[N], sum[N], a[N] ; 
char s[N] ; 
signed main()
{
	cin >> (s + 1), n = strlen(s + 1) ; 
	rep( i, 1, n ) a[i] = s[i] - '0' ; 
	int ff = 0 ; 
	rep( i, 1, n ) 
		( a[i] == 1 ) ? pre[++ m] = ff, ff = 0 : ++ ff ; 
	pre[++ m] = ff ;
	if( m == 1 ) { cout << n << endl ; exit(0) ; }
	int ans = (pre[1] + 1) * (pre[m] + 1) % P ; 
	rep( i, 0, n ) w[i] = 1 ; 
	sum[1] = dp[1] = 1 ; 
	for(re int i = 2; i < m; ++ i) {
		int L = w[0] ; 
		for(re int j = 0; j <= pre[i]; ++ j) 
			L = w[j], dp[i] = (dp[i] + sum[i - 1] - sum[L - 1] + P) % P ; 
		for(re int j = 0; j <= pre[i]; ++ j) w[j] = i ; 
		sum[i] = (sum[i - 1] + dp[i]) % P ; 
	}
	ans = ans * sum[m - 1] % P ; 
	cout << ans << endl ; 
	return 0 ;
}
```


---

## 作者：piggy123 (赞：8)

把最劣解抢了，但是不一样的 $\Theta(n)$ 做法（喜）。

题意转化为将这个序列分为若干段，每段的权值为最大值，求有多少种可能的权值序列。

对于操作序列计数会算重复的问题，我们考虑直接对于结果计数。考虑判定一个数列是否是可以达到的，容易发现我们可以取可以达到这个字符串的的最短前缀，如果这个数列以 $1$ 结尾，那么一定可以一直向后拓展；如果以 $0$ 结尾，那么这个 $0$ 一定来自于最后的连续的 $0$，而我们发现最后的连续的 $0$ 分成的段数独立，所只需要开始时去掉，最后乘上可能的段数即可。

综上，我们需要计算以每个 $1$ 结尾的以这个前缀为最短前缀的可达数列数量。我们可以贪心，令当前位置为 $i$，当前数量的这个 $1$ 后面有 $j$ 个 $0$，那么我们只需要找到 $i$ 之后的第一个 $0$ 的数量 $\geq j$ 的空隙即可。这可以对空隙大小数组求每个后缀的最大前缀得出。

我们断言：这个数组的每个后缀的最大前缀的个数和为 $\Theta(n)$，所以模拟这个操作是正确的。

证明如下：令这个数组为 $a$，则 $\sum a=\Theta(n)$，假设整个数组的前缀最大值有 $k$ 个，则他们的和是 $\Theta(k^2)$ 的，则最多有 $\Theta(n-k^2)$ 个贡献为 $k$，则这个个数为 $\Theta(nk-k^3)$ 级别，求导得当 $k=\Theta(\sqrt{n})$ 时该式有最小值为 $\Theta(n)$。

代码如下：https://codeforces.com/contest/1383/submission/257305778

---

## 作者：Watware (赞：8)

注意到原操作等价于把数列划分为若干段，每段的最小值组成一个新数列，求可以得到的不同的新数列的个数，显然可以动态规划。由于不同的操作序列得到相同的新数列算作一种答案，我们要想一种办法只保留一些合法的操作序列，使得每一种新数列与每一种操作一一对应，以达到不重不漏的目的。

将原序列相邻的同颜色段合并考虑，由于 $0$ 和 $1$ 取 $\operatorname{max}$ 之后就没有了，于是中间隔了 $0$ 的全 $1$ 段可以合并，我们考虑一个贪心，先去除原序列开头结尾的全 $0$ 段：这样之后显然操作后的序列前后都是 $1$，则开头结尾的全 $0$ 段对答案的贡献就是乘上其长度加 $1$。

对于每一个操作后的数列，我们尝试找到原数列最短的一个前缀来通过操作得到它，那么由极小性，显然是满足不重不漏一一对应的，思考这个贪心过程是怎么样的：对于后数列中新加入的一段连续的 $0$，我们找到原数列最靠前的长度大于其的连续的全 $0$ 段来匹配其，然后删掉从开头到这一段的结尾；对于后数列中新加入的一段连续的 $1$，我们从原数列开头开始，往后统计 $1$ 的数量，直到足够为止，然后删除。$01$ 交替地贪心，就可以得到一个极小前缀，我们称这个前缀“刚好”能够得到后数列。

考虑一个 $dp$，$f_i$ 表示“刚好”能由 $1$ 到 $i$ 得到的数列的个数，考虑在这些数列后面加上一个 $0$ 或 $1$。如果当前是 $0$，那么如果要添加 $1$，只需要跳到后面最近的 $1$ 处，如果要添加 $0$，如果下一个数还是 $0$ 那么就直接转移到下一个数，否则找到最近的一段比当前段 $0$ 长的全 $0$ 段，将本段中的 $0$ 全部搬到下一段，然后再往后跳一位；如果当前是 $1$，那么下一个 $0$ 或者下一个 $1$ 都只要找到后面最近的 $0$ 或 $1$ 转移即可。预处理出原序列每一位跳到下一个 $0$ 和 $1$ 的位置，然后 $O(n)\ dp$ 即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int M = 1010000, P = 1e9 + 7;
int n, a[M], b[M], f[M], nxt[M], bl[M];
int t1[M], t0[M], stk[M], tmp[M];
bool c[M], v[M];
char s[M];
int main() {
    scanf(" %s", s), n = strlen(s);
    for (int i = 0; i < n; i++) v[i] = s[i] == '1';
    for (int i = 0; i < n; i++) {
        if (!i || s[i] != s[i - 1]) a[++a[0]]++, c[a[0]] = s[i] == '1', b[a[0]] = i;
        else a[a[0]]++;
        bl[i] = a[0];
    }
    if (a[0] == 1) return !printf("%d\n", a[1]);
    b[a[0] + 1] = n + 1;
    for (int i = a[0]; i > 0; i--) {
        if (c[i]) continue;
        while (stk[0] && a[stk[stk[0]]] <= a[i]) stk[0]--;
        if (!stk[0]) tmp[i] = -1;
        else tmp[i] = b[stk[stk[0]]];
        stk[++stk[0]] = i;
    }
    for (int i = 0; i < n; i++)
        if (v[i])
            t1[i] = (i < n - 1 && v[i] == v[i + 1]) ? i + 1 : (bl[i] + 2 <= a[0] ? b[bl[i] + 2] : -1),
            t0[i] = bl[i] + 1 <= a[0] ? b[bl[i] + 1] : -1;
        else
            t0[i] = (i < n - 1 && v[i] == v[i + 1]) ? i + 1 : (tmp[bl[i]] == -1 ? -1 : tmp[bl[i]] + a[bl[i]]),
            t1[i] = bl[i] + 1 <= a[0] ? b[bl[i] + 1] : -1;
    int st = c[1] ? b[1] : b[2], vp = !c[1] ? a[1] + 1 : 1;
    f[st] = 1;
    for (int i = st; i < n; i++) {
        if (t0[i] != -1) f[t0[i]] = (f[t0[i]] + f[i]) % P;
        if (t1[i] != -1) f[t1[i]] = (f[t1[i]] + f[i]) % P;
    }
    int ans = 0, vg = !c[a[0]] ? a[a[0]] + 1 : 1;
    for (int i = 0; i < n; i++)
        if (v[i]) ans = (ans + f[i]) % P;
    printf("%lld\n", 1ll * ans * vg % P * vp % P);
    return 0;
}
```


---

## 作者：AsunderSquall (赞：5)

**题意**  

给一个 $01$ 串，可以进行若干次操作，每次操作选择两个相邻的数字变成它们的或，求能生成几种本质不同的 $01$ 串，对 $10^9+7$ 取模。

**题解**  
 
看了看 CF 官方题解，好像比当前题解区的所有题解都更简洁（指代码）。 

首先考虑设 $p_i$ 表示，第 $i$ 个位置往前有连续的 $p_i$ 个 $0$，显然 $p_i=0$ 的点说明 $a_i=1$。 

考虑用类似子序列自动机的东西进行匹配，我们用原串 $s$ 的前 $i$ 个字符生成了目标串 $w$ 的前 $j$ 个字符，**并且 $w$ 中的前 $j$ 个字符已经有至少一个 $1$ 了（这个条件用来保证能够进行合法的匹配构造）**。  
- 如果 $w_{j+1}=1$，那么我们需要找到 $s$ 中的下一个 $1$，即 $p_t=0$。  
- 如果 $w_{j+1}=0$，并且 $w$ 最后已经有了 $k$ 个连续的 $0$，那么我们需要找到 $s$ 中下一个 $p_t=k+1$。  
- 如果 $w$ 的长度就是 $j$，没有下一位了，还需要注意如果当前的这段 $0$ 已经是 $w$ 的最后一段 $0$ 了，那么这段 $0$ 的长度不能超过 $s$ 最后一段 $0$ 的长度，才能有 $1$ 的贡献。

考虑从后往前扫，设 $f_i$ 表示 $i$ 往后这个后缀可以构成的 $01$ 串的方案数，用 $la_i$ 表示当前后面的第一个 $p_t=i$ 的位置，然后用上述匹配方式进行转移。    

最后因为我们是假设 $w$ 中已经至少有一个 $1$ 了，所以不能直接输出 $f_1$，而是要输出第一个 $1$ 的值乘上前面 $0$ 的个数 $+1$。  

还有，如果 $s$ 全部都是 $0$ 需要特判。


**代码**  
核心代码 $3$ 行。  
```cpp
for (int i=1;i<=n;i++) if (s[i]=='0') p[i]=p[i-1]+1;
for (int i=n;i>=1;i--) f[i]=(f[la[p[i]+1]]+f[la[0]]+(p[i]<=p[n]))%mod,la[p[i]]=i;
if (la[0]) cout<<f[la[0]]*la[0]%mod<<endl;else cout<<n<<endl;
```

---

## 作者：chenxia25 (赞：4)

![](https://s1.ax1x.com/2020/07/27/aFE4oR.png)  
![](https://s1.ax1x.com/2020/07/27/aFEqyD.png)

就没啥好说的了……u1s1 使我做出来的题目组成的序列不是所有题目组成的序列的前缀的比赛都不是好比赛（暴论

比赛结束前40min一直在肝这个E……结果没肝出来……然而还是在赛后三天独立肝出来了……

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/CF1383E) & [CF题目页面传送门](https://codeforces.com/contest/1383/problem/E)

>题意见洛谷/xyx

首先把操作转化一下：若$a_i$和$a_{i+1}$中有至少一个$\texttt1$，则留下来一个$\texttt1$删掉另一个，否则任意删掉一个$\texttt0$。可以理解为，相邻两个字符打架，$\texttt1$是要比$\texttt0$厉害的，一定能干掉$\texttt0$。

不难想到，可以将$a$分成若干个相等段，这样就是一段$\texttt1$，一段$\texttt0$（设第$i$段是$v_i$个$c_i$）……然后就是一脸DP的样子。

考虑设$dp_i$表示第$i$个相等段一直到最后组成的01串，通过若干次操作，并且保持第一个字符不变的情况下，能产生多少个不同的01串。边界：$dp_{m+1}=1$，其中$m$为相等段的个数；目标：$\begin{cases}dp_1&m=1\lor c_1=\texttt1\\dp_1+dp_2&\text{otherwise}\end{cases}$。然后倒着DP。这个状态对于老司机来说设计的还是挺自然的。此题的难点在于转移，会把人脑子烧坏。

分两种情况：

1. 第$i$段为$\texttt0$。不难发现：若第$i$段后面有段的话，第$i$段与第$i+2$往后的段是不能够发生关系的（互相独立），因为，中间第$i+1$段$\texttt1$是怎么也删不光的，于是$dp_{i}=v_idp_{i+1}$；而后面没有段的话，稍微想一下就会发现也满足上面那个方程；
1. 第$i$段为$1$。此时第$i$段和第$i+2$段往后是可能发生关系的，因为有可能把中间那段$\texttt0$全部干掉来实现前面和后面的合并。那么我们枚举的01串的开头的$\texttt1$的数量$x$。对于$x$，贪心的思想告诉我们，尽可能地用前面的$\texttt1$凑是最好的，因为这样的话需要把从左往右数第$x$个$\texttt1$所在的段及前面的$\texttt1$段（达到了要合并的段数的下限）全部合并起来，然后就只有后面是不确定的，加上后面的DP值，而后面的串越长，DP值肯定就越大（方案越全）。接下来仔细考虑这种情况如何转移。

   对于每个$x$，设从$i$开始从左往右数第$x$个$\texttt1$所在的段为$j$，考虑从第$2$段开始后面的情况：
   1. 后面啥也没有了。那么只有$1$种情况；
   1. 后面只有一个$\texttt0$段，这个是在$dp_{j+1}$里没有考虑到的，因为在$dp_{j+1}$里是不可能把后面的$\texttt1$全删掉的，而考虑$dp_i$的时候可以，方案最全的方法是把所有的$\texttt1$段全部合并并删的只剩$x$个，中间的$\texttt0$干掉，只留最后一部分$\texttt0$。由于最后一部分也可以随意删，那么有$[c_m=\texttt0]v_m$；
   1. 后面有至少$2$段。那么若$j+1<m$直接套$dp_{j+1}$。
   
   综上，$dp_i=\sum\limits_{j=i}^m[c_j=\texttt1]v_j(1+[c_m=\texttt0]v_m+[j+1<m]dp_{j+1})$。这个方程直接算会T，优化很容易，two-pointers即可。
   
然后就会发现样例4过不去。然后就发现，前面那个贪心的思想假掉了……一个反例是：$a=\texttt{101001}$，在DP到$dp_1$时，$x=1$的情况下，考虑不到$\texttt{1001}$，而实际上是有的。问题出现在哪儿？第$2$段的$\texttt0$的数量被上限$v_{j+1}$限住了。不过这个假是可以解决的，不像某些辛辛苦苦写了几个小时发现救不了……………………

考虑再枚举第$2$段的$\texttt0$的个数$y$，由于$\texttt0$是不可合并的，我们要找的是$j$后面最前面（这个还是基于贪心的思想）的$c_k=\texttt0,v_k\geq y$的第$k$段（要把中间的$\texttt1$全部合并，$\texttt0$全部干掉），而不是$k=j+1$。对于每个$y$，都有一个贡献值，于是维护这个基于$y$的贡献值序列，每次更完一个$\texttt0$段的DP值就修改这个序列，然后计算$\texttt1$段的DP值时就全体求和。一个暴力的想法是直接大力线段树区间赋值，$\mathrm O(n\log n)$。然而其实只需要维护一个栈即可，每个元素是一个（区间，值）的二元组，由于每个赋值操作最多会被弹出一次，$\mathrm O(n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define X first
#define Y second
#define mp make_pair
const int mod=1000000007;
const int N=1000000;
int n;
char a[N+5]; 
vector<pair<int,bool> > v;//相等段序列 
int dp[N+1];
pair<pair<int,int>,int> stk[N];int top;//栈 
int main(){
	scanf("%s",a+1);
	n=strlen(a+1);
	for(int i=1,ie;i<=n;i=ie+1){//预处理v 
		ie=i;while(ie+1<=n&&a[ie+1]==a[i])ie++;
		v.pb(mp(ie-i+1,a[i]^48));
	}
//	reverse(v.begin(),v.end());
	int sum=0,now=0,las=!v.back().Y*v.back().X;
	dp[v.size()]=1;//边界 
	for(int i=v.size()-1;~i;i--){//转移 
		if(v[i].Y==0){
			dp[i]=1ll*v[i].X*dp[i+1]%mod;
			while(top&&stk[top-1].X.Y<=v[i].X)(now-=1ll*(stk[top-1].X.Y-stk[top-1].X.X+1)*stk[top-1].Y%mod)%=mod,top--; 
			if(top)(now-=1ll*(v[i].X+1-stk[top-1].X.X)*stk[top-1].Y%mod)%=mod,stk[top-1].X.X=v[i].X+1;//维护栈 
			stk[top++]=mp(mp(1,v[i].X),(i<v.size()-1)*dp[i+1]),(now+=(i<v.size()-1)*dp[i])%=mod;
//			for(int j=0;j<top;j++)printf("[%d,%d]:%d ",stk[j].X.X,stk[j].X.Y,stk[j].Y);puts("");
		}
		else
			dp[i]=(sum+=1ll*v[i].X*(1+las+now)%mod)%=mod;
//		cout<<dp[i]<<"\n";
	}
	if(v.size()==1)cout<<(dp[0]+mod)%mod;
	else if(v[0].Y==1)cout<<(dp[0]+mod)%mod;
	else cout<<((dp[0]+dp[1])%mod+mod)%mod;//目标 
	return 0;
} 
```

---

## 作者：Purslane (赞：2)

# Solution

简单 *2800 题。

考虑先判定合不合法。

我们可以重新改写一下我们的操作：

1. 删掉任意位置的 $\texttt 0$；
2. 如果有相邻的 $\texttt 1$，可以删掉一个。

然后考虑判定。

显然，我们需要满足**首尾的 $\texttt 0$ 比原串要少**。因为新串的 $\texttt 0$ 连续段必定是在原串的基础上删数。

然后考虑将 $\texttt 0$ 连续段和原串匹配，使得选择两个连续段之间的 $\texttt 1$ 比原相邻 $\texttt 0$ 连续段之间 $\texttt 1$ 的个数多。

我们贪心的选择，只要能在原长的限制内完成匹配即可。

因此设 $dp_i$ 表示，我们匹配到了原串中第 $i$ 个 $\texttt 0$ 连续段的方案数。

假设新的串下一个 $\texttt 0$ 连续段有 $t$ 个，转移到 $dp_k$，需要满足 $len_k \ge t$。同时，为了保证不贪心的选择 $(i,k)$ 中间的其他连续段，设 $x$ 为最大的 $x \in (i,k)$ 使得 $len_x \ge t$，则有两个连续段之间 $1$ 的个数应当比 $i$ 和 $x$ 中夹的 $1$ 要多。容易使用单调栈维护这个过程。

代码写得很丑陋：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10,MOD=1e9+7;
int n,dp[MAXN],pre[MAXN],ans,tot,Dp[MAXN],psl[MAXN];
string S; 
struct INFO {int lim,pos,pre;};
stack<INFO> st;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>S,n=S.size(),S="&"+S;
	ffor(i,1,n) pre[i]=pre[i-1]+S[i]-'0';
	int cnt=1,pos=1;
	ffor(i,1,n) if(S[i]=='0') cnt++,pos++; else break ;
	tot=1,dp[1]=cnt,ans=(ans+dp[1]*max(1ll,pre[n]))%MOD;
	st.push({n+1,0,0});
	if(cnt!=1) st.push({cnt-1,1,0});
	Dp[1]=dp[1];
	int lstlen=0;
	roff(i,n,1) if(S[i]=='0') lstlen++; else break ;
	while(pos<=n) {
		int nxt=pos,len=0,lst=0;
		while(nxt<=n&&S[nxt]=='1') nxt++;
		if(nxt==n+1) break ;
		while(nxt<=n&&S[nxt]=='0') nxt++,len++;
		++tot;
		while(1) {
			auto pr=st.top();
			if(pr.lim<=len) ans=(ans+(Dp[pr.pos]*(pre[nxt-1]-pr.pre)%MOD+(Dp[tot-1]-Dp[pr.pos])%MOD*pre[nxt-1]%MOD-psl[tot-1]+psl[pr.pos])%MOD*max(0ll,min(lstlen,pr.lim)-lst))%MOD,dp[tot]=(dp[tot]+(Dp[pr.pos]*(pre[nxt-1]-pr.pre)%MOD+(Dp[tot-1]-Dp[pr.pos])%MOD*pre[nxt-1]%MOD-psl[tot-1]+psl[pr.pos])%MOD*(pr.lim-lst))%MOD,st.pop(),lst=pr.lim;
			else {
				ans=(ans+(Dp[pr.pos]*(pre[nxt-1]-pr.pre)%MOD+(Dp[tot-1]-Dp[pr.pos])%MOD*pre[nxt-1]%MOD-psl[tot-1]+psl[pr.pos])%MOD*max(0ll,min(len,lstlen)-lst))%MOD,
				dp[tot]=(dp[tot]+(Dp[pr.pos]*(pre[nxt-1]-pr.pre)%MOD+(Dp[tot-1]-Dp[pr.pos])%MOD*pre[nxt-1]%MOD-psl[tot-1]+psl[pr.pos])%MOD*(len-lst))%MOD,lst=len;
				break ;
			}
		}
		st.push({len,tot,pre[nxt-1]});
		pos=nxt;
		ans=(ans+dp[tot]*(pre[n]-pre[nxt-1]))%MOD;
		Dp[tot]=(Dp[tot-1]+dp[tot])%MOD;
		psl[tot]=(psl[tot-1]+dp[tot]*pre[nxt-1])%MOD;
	}
	cout<<((ans-(pre[n]==0))%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：2)

特判全 $\mathtt 0$ 串。

能生成的一定是原串的子序列，满足存在一个定位 $i_1,\dots,i_m$ 使得：

* 存在 $s_{i_k}=\mathtt 1$，即该子序列不全 $\mathtt 0$。
* 若 $s_{i_{k}}=s_{i_{k+1}}=\mathtt 0$，则 $i_k+1=i_{k+1}$。换句话说，值为 $\mathtt 0$ 的段在原串的定位是一个区间。
* 若 $s_{i_1}=\mathtt 0$，则 $i_1$ 在前缀 $\mathtt 0$ 中。
* 若 $s_{i_m}=\mathtt 0$，则 $i_m$ 在后缀 $\mathtt 0$ 中。

先将原串前后缀 $\mathtt 0$ 删去，最后答案只需乘上 $(len_{\text{pre=0}}+1)(len_{\text{suf=0}}+1)$。于是只要满足前两条限制。

考虑用类似子序列自动机的转移，构建定位和子序列的双射。

$\mathtt 1$ 的转移是朴素的，直接指向下一个值为 $\mathtt 1$ 的位置即可。

发现 $\mathtt 0$ 的转移需要依赖于这个 $\mathtt 0$ 段的长度 $L$，并指向原串下一个的长度至少 $L$ 的 $\mathtt 0$ 区间。

这样不行，所以考虑反悔贪心（失配找下一个）状物：

* 若当前位置值为 $\mathtt 1$，直接跳到下一个值为 $\mathtt 0$ 的位置。
* 若当前位置值为 $\mathtt 0$：
  * 若右一个位置为 $\mathtt 0$，向右跳一步。
  * 否则我们通过当前位置向左连续 $\mathtt 0$ 的个数知道接下来要找的长度 $L$，跳到下一个的长度至少 $L$ 的 $\mathtt 0$ 区间左端点 $+L-1$ 的位置。

怎么维护向右找到长度至少为 $L$ 的第一个 $\mathtt 0$ 区间：

维护位置数组 $pos_i$。$n\to 1$ 遍历位置 $i$，若该位置为一个长度为 $x$ 的 $\mathtt 0$ 区间的左端点，则 $\forall y\le x,pos_y:=i$。时间复杂度总和不大于串长。

复杂度线性。

---

## 作者：RedLycoris (赞：1)

题目大意：

给你一个长度为 $n$ 的字符串 $s$。

每一次操作，可以选择一个位置（不为最后一位），然后删除它和它后面一位，在原来的位置上填上他们的或。每次操作会使 $n-1$。

问你执行最多 $n-1$ 次操作后能得到多少不同的串。

题解：

根据套路，就可以把相同的数分成一段一段的。又因为是或，所以我们可以认为 $1$ 永远比 $0$ 强，就统计相邻两个 $1$ 之间 $0$ 的个数。（记第 $i$ 段为 $cnt_i$，有 $m$段）

考虑操作过程：

如果选择的是两个 $1$，那么段数会 $-1$，但由于反正间隔都是 $0$ 个 $0$了，我们就可以不用管了。**（有问题，后面会提到）**

反之，删除的肯定是一个 $0$，就当那一段的 $0$ 个数 $-1$。

然后我们就相当于：统计数组 $a$ 的个数，满足 $a_i \le cnt_i$ 了

吗？

不，这题不会这么简单，因为很显然会重复计算。

所以，我们考虑怎么去重：

**前面推的时候，对于选择了两个 $1$ 的情况，很难自圆其说是不是？**

我们对这一块重新考虑下。

令 $dp_i$ 表示考虑到 $cnt_i$ 时的方案数。

为了去重，当 $dp_i$ 由 $dp_k$ 转移过来的时候，需要满足对于所有的 $k+1 \le j \le i-1,cnt_j<cnt_i$，这样就限制了多次转移的情况，而且不会使答案遗漏。

处理 $k$ 的话，打个标记就好了。

最后用前缀和优化把复杂度从 $O(n^2)$ 降到 $O(n)$

Code:

```cpp
string s;
const int mxn=1e6+6;
int cnt[mxn],m,n;
const ll md=1000000007;
ll sum[mxn],dp[mxn];
int pos[mxn];
inline void add(ll&x,ll y){
	x+=y;
	if(x>=md)x-=md;
	if(x<0)x+=md;
	if(x>=md)x-=md;
	if(x<0)x+=md;
}
inline void solve(){
	cin>>s;n=s.size();
	s=s+"1";
	for(int i=0,j=0;i<s.size();++i){
		for(;j<s.size() and s[j]=='0';)++j;
//		cerr<<"? "<<i<<' '<<j<<'\n';
		cnt[++m]=j-i;
		i=j;
		j=i+1;
	}
	if(m==1){
		cout<<n<<'\n';
		return;
	}
//	for(int i=1;i<=m;++i)cerr<<cnt[i]<<' ';cerr<<'\n';
	ll ans=(cnt[1]+1)*1ll*(cnt[m]+1)%md;
	sum[1]=1,dp[1]=1;
	for(int i=1;i<=n;++i)pos[i]=1;
	for(int i=2;i<m;++i){
		for(int j=0;j<=cnt[i];++j)add(dp[i],sum[i-1]-sum[pos[j]-1]);
		for(int j=0;j<=cnt[i];++j)pos[j]=i;
		add(sum[i],sum[i-1]+dp[i]);
	}
	cout<<(ans*1ll*sum[m-1])%md<<'\n';
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=1;
	//cin>>T;
	for(;T--;)solve();
	return 0;
}
```

---

## 作者：Mashu77 (赞：0)

若对操作的序列计数，此题难以处理。我们通过一些转换，对可以得到的串计数。

利用 
$1$
 将串划分，记录每段 
$0$
 的数量。如 
$001010011$
 就是 
$\{
2
,
1
,
2
,
0
,
0
\}$。那么可行的操作就是将一个大于 
$0$
 的数减 
$1$，或删除一个不在头尾的 
$0$。于是一个串与一个序列一一对应。下面我们对序列计数。

头尾不删，则可以扔掉，最后乘上系数 
$(
a_
1
+
1
)
(
a_
n
+
1
)$。此时可知一个长为 
$m$
 的序列 
$b$
 可行的充要条件：存在 
$i_
1
<
i_
2
<
⋯
<
i_
m$
 满足 
$∀
j
∈
[
1
,
m
]
,
b_
j
≤
a_{
i_
j}$。用类似子序列自动机的方式判断。每次向后找到第一个大于等于 
$b_
j$
 的位置并移动指针。

然后可以 
dp
。设 
$f_
i$
 表示指针在 
$i$，每次枚举下一个放的数。则有 
$f_i=\sum\limits_{j<i}f_j+\max(0,a_i-\max\limits_{k=j+1}^{i-1}a_k)$。单调栈可做到 
$O
(
n
)$。

---

## 作者：BreakPlus (赞：0)

+ 考虑建立删除方法与最终获得串的一一映射。

+ 先判断能否通过删除得到某个串。可以把操作倒过来，变成加数，然后发现 $1$ 的左右可以任意加数，$0$ 的左右只能加 $0$。

+ 判断过程可以通过贪心的方式刻画。从左往右扫描我们想要判断的串，并设一个在原串上的指针，表示当前匹配到哪里。

+ 任意时刻我们都希望指针尽量靠前。

+ 当加进来一堆 $1$，我们只需要不断找到指针所在位置的下一个 $1$ 与其匹配。因为 $1$ 的左右可以加入任何东西。

+ 当加进来一堆 $0$（设有 $x$ 个），我们发现它们所匹配的位置之间不能夹杂着 $1$（因为 $0$ 的左右只能产生 $0$）。

+ 为了保证它是一个一一映射，我们只需要找到下一段连续的 $0$，使得连续的 $0$ 的个数 $\ge x$，并把指针移到那里去。

+ 具体地，先将原串按照一段 $0$、一段 $1$ 交替划分，分成一些段，设 $f_i$ 表示当前匹配到第 $i$ 段，当前构造的答案串以 $1$ 结尾；$g_i$ 表示以 $0$ 结尾。

+ 发现不管 $j(j < i)$ 为何值，$g_j \to f_i$ 的转移系数都为 $len_i$（第 $i$ 段的长度）。假设新添一段长度为 $k$ 的连续的 $1$，发现 $k$ 一定恰好有 $len_i$ 种取值（不难理解）。

+ $g_i$ 的转移也容易写出，单调栈+前缀和优化一下即可做到 $\mathcal{O}(n)$。

[code link](https://codeforces.com/contest/1383/submission/258363395)

```cpp
char str[1000005];
ll n,v[1000005],seq[1000005],f[1000005],g[1000005],cnt;
ll sum[1000005];
ll stk[1000005], tp;
void solve(){
	scanf("%s", str+1); n=strlen(str+1);
	str[0]='#';
	for(ll i=1;i<=n;i++) {
		if(str[i] != str[i-1]){
			v[++cnt] = str[i]-'0'; seq[cnt]=1;
		}else seq[cnt]++;
	}
	if(v[1]==0) g[1] = seq[1]; else f[1] = seq[1]; sum[1] = f[1];
	seq[0] = 1e18;
	stk[tp=1] = 0; ll sumg = g[1];
	if(v[1]==0) stk[++tp] = 1;
	for(ll i=2;i<=cnt;i++){
		if(v[i]==1){
			f[i] = sumg * seq[i] % mod;
			f[i] = (f[i] + seq[i]) % mod;
		}else{
			g[i] = (sum[i-1] + mod - sum[stk[tp]]) * seq[i] % mod;
			while(seq[i] > seq[stk[tp]]){
				g[i] = (g[i] + (sum[stk[tp]] + mod - sum[stk[tp-1]]) * (seq[i] - seq[stk[tp]])) % mod;
				tp--;
			}
			stk[++tp] = i;
		}
		sumg = (sumg + g[i]) % mod;
		sum[i] = (sum[i-1] + f[i]) % mod;
	}
	ll wans = 0;
	for(ll i=1;i<=cnt;i++)
		if(v[i]==1) wans += f[i];
	
	if(v[cnt]==0 && cnt==1){
		printf("%lld\n", seq[1]);
		return;
	} 
	if(v[cnt]==0) printf("%lld\n",(wans*seq[cnt]+wans)%mod);
	else printf("%lld\n",wans%mod);
}
```

---

## 作者：7KByte (赞：0)

不难发现一次操作就是选两个位置并将它们取 ``or``。

然后是非常经典的操作，匹配。类似于子序列自动机。没有做过类似的可能很难想到这一点。

那么显然对于一个答案串，它的最优匹配点是唯一的，简单来说就是贪心的取最前面的。

那么我们可以定义状态 $f[i][j]$ 表示长度为 $i$ 的答案串，匹配到 $s$ 的第 $j$ 个位置。

事实上我们并不关心答案串的长度，直接保留 $f[i]$ 表示匹配到 $i$ 的方案数也可以不重不漏，因为和子序列自动机相同，最优匹配点不同两个子序列一定不相同。

现在只用考虑向当前串后面加上 $0/1$ 。

加上 $1$，最优匹配点移动到下一个 $1$ 的位置。

当前串最后为 $1$ 或者后面一个位置为 $0$，那么答案串加上 $0$ ，最优匹配点一定到下一个 $0$ 的位置。

上面两个都不难理解，因为我们可以把连续一段 $0/1$ 保留任意个，有 $1$ 相邻的 $0$ 可以随便删。

对于当前位置为 $0$ 而后面一个位置是 $1$，我们要给答案串也加上 $0$ ，这时如果选择下一个 $0$，那么两个 $0$ 之间的 $1$ 无法消掉。所以我们只有选择后面连续的一段 $0$。这可以用单调栈维护做到线性，时间复杂度 $\mathcal{O}(N)$。

```cpp
/*
    Author : SharpnessV
    Right Output ! / Accepted !
*/
#include<bits/stdc++.h>

#define rep(i, a, b) for(int i = a;i <= b;i++)
#define pre(i, a, b) for(int i = a;i >= b;i--)
#define rp(i, a) for(int i = 1; i <= a; i++)
#define pr(i, a) for(int i = a; i >= 1; i--)
#define go(i, x) for(auto i : x)

#define mp make_pair
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define ze(p) memset(p, 0, sizeof(p))
#define YES puts("YES")
#define NO puts("NO")
#define si(x) (int)(x).size()

using namespace std;
const double eps = 1e-15, pi = 3.1415926535897932385;
typedef long long LL;
typedef pair<int,int> Pr;
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}, inf = 0x7fffffff;

//char buf[1<<22],*p1=buf,*p2=buf;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(!isdigit(ch))f = ('-' == ch ? -1 : 1), ch = getchar();
    while(isdigit(ch))x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    if(~f)return x;return -x;
}
int gcd(int x,int y){return y ? gcd(y, x % y) : x;}
int lcm(int x,int y){return x / gcd(x, y) * y;}
#define P 1000000007
inline void ad(int &x, int y){x += y; if(x >= P) x -= P;}
inline void su(int &x, int y){x -= y; if(x < 0) x += P;}
int Pow(int x, int y){
	if(y < 0)return Pow(Pow(x, P - 2), -y);
	int now = 1 ;
	for(;y;y >>= 1, x = 1LL * x * x % P)if(y & 1) now = 1LL * now * x % P;
	return now;
}
#define N 1000005
char s[N];int n, p[N], q[N], top, f[N], g[N][2];
int main(){
	//int T = read();while(T--)solve();
	scanf("%s", s + 1);
	n = strlen(s + 1);
	bool flag = true;
	rp(i, n)flag &= s[i] == '0';
	if(flag){printf("%d\n", n);return 0;}
	int l = 1, r = n, k = 0;
	while('0' == s[l])l++;
	while('0' == s[r])r--;
	pre(i, r, l){
		g[i][1] = k;
		if('1' == s[i])k = i;
	}
	k = 0;
	pre(i, r, l){
		if(s[i + 1] == '0' || s[i] == '1')g[i][0] = k;
		if(s[i] == '0')k = i;
	}
	int sum = 0;
	//rep(i, l, r)printf("%d ",g[i][0]);putchar('\n');
	rep(i, l, r){
		if(s[i] == '0'){
			sum++;
			while(top && p[top] < sum)g[q[top]][0] = i, top--;
		}else if(sum){
			p[++top] = sum, q[top] = i - 1, sum = 0;
		}
	}
	f[l] = 1;int ans = 0;
	rep(i, l, r){
		if('1' == s[i])ad(ans, f[i]);
		rep(x, 0, 1)if(g[i][x])
			ad(f[g[i][x]], f[i]);
	}
	printf("%lld\n", 1LL * ans * l % P * (n - r + 1) % P);
	return 0;
}

```

---

## 作者：tzc_wk (赞：0)

[Codeforces 题目传送门](https://codeforces.com/contest/1383/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1383E)

Yet another 自己搞出来的难度 $\ge 2800$ 的题

介绍一个奇奇怪怪的 $n\log n$ 的做法。首先特判掉字符串中全是 $0$ 的情况，这种情况答案显然为 $n$。我们假设字符串中 $1$ 的位置为 $p_1,p_2,\cdots,p_k$。考虑当我们已经求出了 $s[1...p_i]$ 可以得到多少个不同的 01 串后，怎样求出 $s[1...p_{i+1}]$ 可以得到多少个不同的 01 串。

- 显然原来 $s[1...p_i]$ 可以得到的子串，也可以通过 $s[1...p_{i+1}]$ 得到，因为我们可以将 $p_{i+1}$ 与 $p_{i+1}-1$ 合并，$p_{i+1}-1$ 与 $p_{i+1}-2$ 合并，……，$p_i+1$ 与 $p_i$ 合并，这样我们就合并得到了 $s[1...p_i]$。对于 $s[1...p_i]$ 可以得到的子串 $t$，再通过 $s[1...p_i]\to t$ 的合并方式即可合并得到 $t$。
- 对于原来 $s[1...p_i]$ 可以得到的子串 $t$，在其后面添上 $j(0\le j\le p_{i+1}-p_i-1)$ 个 $0$ 和一个 $1$ 得到的字符串也可以被合并出来，因为我们可以按照 $s[1...p_i]\to t$ 的合并方式合并 $s[1...p_{i+1}]$ 的前 $p_i$ 位，然后把最后一段 $00...01$ 合并只剩 $j$ 个 $0$ 和 $1$ 个 $1$。

假设 $dp_i$ 为 $[1...p_i]$ 可以得到多少个 01 串，照这样讲，难道就有 $dp_{i+1}=(p_{i+1}-p_i)\times dp_i$ 吗？

非也，不然您觉得这题咋就能放到 D1E 呢/ww

这样做的问题是，会出现重复计算的字符串，比方说 $s=\texttt{10101}$，那么当我们计算 $s[1...p_i]$ 可以得到的子串（第一类）时会统计到字符串 $\texttt{101}$，而 $s[1...p_i]$ 还可以得到一个字符串 $\texttt{1}$，在 $\texttt{1}$ 后面添上一个 $0$ 和一个 $1$ 后也能得到 $\texttt{101}$，也就是说 $\texttt{101}$ 被统计了两次。

怎样避免这种情况呢？显然这种算重的情况只会发生在第一类与第二类之间，因为每一类内部的字符串是不会算重的（对于上述转移中的第一种情况，原来 $s[1...p_i]$ 根据我们 $dp$ 状态的定义已经“本质不同”了，不会重复计算，而对于上述转移中的第二种情况，要么最后一段 $0$ 的个数 $j$ 不同，要么去掉最后一段 $00...01$ 之后，得到的可以通过 $s[1...p_i]$ 合并得到的子串不同，也不会算重），也就是说算重的字符串只可能是对于某个 $s[1...p_i]$ 得到的 $t$，它加上 $j$ 个 $0$ 和一个 $1$ 后得到的字符串照样可以通过 $s[1...p_i]$ 得到。因此我们可以转化为统计有多少个可以被 $s[1...p_i]$ 的字符串，它最后一段 $00...01$ 中 $0$ 的个数在 $[0,p_{i+1}-p_i-1]$ 中。

考虑换个状态设计，$dp_{i,j}$ 表示考虑 $[1...p_i]$ 的字符串，有多少个满足最后一段 $00...01$ 中 $0$ 的个数为 $j$，这样一来转移就比较明显了，记 $S=\sum\limits_{j}dp_{i,j}$，对于 $j>p_{i+1}-p_i-1$，显然用第二种情况转移得来的字符串不可能得到最后一段 $j$ 个 $0$ 的 01 串，故 $dp_{i+1,j}=dp_{i,j}$，对于 $j\le p_{i+1}-p_i-1$，第一种情况贡献 $dp_{i,j}$ 个字符串，第二种情况贡献 $S$ 个字符串，但根据上面的推论还有 $dp_{i,j}$ 个字符串被算重，故 $dp_{i+1,j}=S+dp_{i,j}-dp_{i,j}=S$，还有一个小问题，就是对于形如 $000...01$ 的字符串，它不能通过某个可以通过 $s[1...p_i]$ 得到的字符串加上若干个 $0$ 和一个 $1$ 得到（因为它去掉最后一段 $00...01$ 后就得到空串了，而空串不可能被我们得到），而显然如果 $\begin{matrix}\underbrace{000...00}1\\j\text{个}0\end{matrix}$ 能够被 $s[1...p_i]$ 得到，那么 $j\le p_1-1$。也就是说对于 $j\le p_1-1$，字符串 $\begin{matrix}\underbrace{000...00}1\\j\text{个}0\end{matrix}$ 被包含在了 $dp_{i,j}$ 中，但事实上它没有被重复统计，故被重复统计的只有 $dp_{i,j}-1$ 个，即 $dp_{i+1,j}=S+dp_{i,j}-(dp_{i,j}-1)=S+1$，于是我们有状态转移方程：

$$dp_{i+1,j}=\begin{cases}S+1&j\le\min(p_1-1,p_{i+1}-p_i-1)\\S&p_1\le j\le p_{i+1}-p_i-1\\dp_{i,j}&j>p_{i+1}-p_i-1\end{cases}$$

这样暴力复杂度是平方的，但借鉴 CF115E 的套路第一维显然可以去掉，用线段树维护第二维，只需实现一个区间赋值和全局求和，复杂度 $n\log n$。

又一次抢了最劣解（bushi

```cpp
const int MOD=1e9+7;
const int MAXN=1e6;
char str[MAXN+5];int n;
struct node{int l,r,sum,lz;} s[MAXN*4+5];
void pushup(int k){s[k].sum=(s[k<<1].sum+s[k<<1|1].sum)%MOD;}
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;s[k].lz=-1;if(l==r) return;
	int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
}
void pushdown(int k){
	if(~s[k].lz){
		s[k<<1].sum=1ll*(s[k<<1].r-s[k<<1].l+1)*s[k].lz%MOD;
		s[k<<1|1].sum=1ll*(s[k<<1|1].r-s[k<<1|1].l+1)*s[k].lz%MOD;
		s[k<<1].lz=s[k].lz;s[k<<1|1].lz=s[k].lz;s[k].lz=-1;
	}
}
void modify(int k,int l,int r,int x){
	if(l>r) return;
	if(l<=s[k].l&&s[k].r<=r){
		s[k].sum=1ll*(s[k].r-s[k].l+1)*x%MOD;
		s[k].lz=x;return;
	} pushdown(k);int mid=s[k].l+s[k].r>>1;
	if(r<=mid) modify(k<<1,l,r,x);
	else if(l>mid) modify(k<<1|1,l,r,x);
	else modify(k<<1,l,mid,x),modify(k<<1|1,mid+1,r,x);
	pushup(k);
}
int main(){
	scanf("%s",str+1);n=strlen(str+1);
	int fst=0;for(int i=1;i<=n;i++) if(str[i]^48){fst=i;break;}
	if(!fst) return printf("%d\n",n),0;int pre=fst;
	build(1,0,n);modify(1,0,fst-1,1);
	for(int i=fst+1;i<=n;i++) if(str[i]^48){
		int len=i-pre,sum=s[1].sum;
		modify(1,0,min(fst,len)-1,(sum+1)%MOD);
		modify(1,min(fst,len),len-1,sum);
		pre=i;
	} printf("%d\n",1ll*s[1].sum*(n-pre+1)%MOD);
	return 0;
}
```

~~似乎有线性的做法？被微分了/kk~~

接下来就是大部分题解中提到的线性做法了，考虑什么样的字符串可以被得到，对于一个 $01$ 串 $t$，它可以被 $s$ 得到的充要条件是：

- $t$ 第一段 $0$ 的长度 $\le$ $s$ 第一段 $0$ 的长度
- $t$ 最后一段 $0$ 的长度 $\le$ $s$ 最后一段 $0$ 的长度
- 假设 $t$ 中间有 $y$ 段 $0$，长度分别为 $g_1,g_2,\cdots,g_y$，$s$ 中间有 $x$ 段 $0$，长度分别为 $f_1,f_2,\cdots,f_x$，则存在 $1\le p_1\le p_2\le\cdots\le p_y\le x$ 满足 $g_{i}\le f_{p_i}$。

前两个条件显然可以轻松判断，但是第三个条件貌似有些棘手，我们考虑用一个“匹配”的思想解释上面的内容，我们在扫描 $t$ 的过程中维护一个指针 $p$，表示最小的满足当前 $t$ 的前缀 $t[1...i]$ 能够从 $s[1...j]$ 得到的 $j$。我们考虑加入一个字符会对 $p$ 产生什么影响，若加入一个 $1$，那么 $p$ 显然会移动到 $j$ 下一个 $1$ 的位置，若加入一个 $0$，则分三种情况：

- 若 $s_p='1'$，那么 $p$ 会移动到下一个 $0$ 的位置
- 若 $s_p='0'$，且 $s_{p+1}='0'$，那么 $p$ 显然会移动到 $p+1$
- 若 $s_p='0'$，且 $s_{p+1}='1'$，那么意味着这段 $0$ 的个数超过了当前指针所在的 $0$ 的段的长度，也就是说这段 $0$ 不够用了。我们记当前 $p$ 所在 $0$ 段为 $s[L...R]$，那么我们就找到离当前 $0$ 段最近的 $0$ 段 $s[l...r]$，满足 $r-l+1>R-L+1$，并将指针移动到 $l+R-L+1$ 的位置。这个稍微想想即可想明白。

如果在上面的过程中 $p$ 无法再移动了，则说明无法匹配，否则可以匹配。我们考虑以此为 $dp$ 状态进行转移。我们先预处理出 $nxt_{i,j}$ 表示当前指针在 $i$ 处，新加入一个字符 $j$ 后指针会移动到哪儿，这显然可以单调栈求出。然后设 $dp_{i,j}$ 表示当前指针在 $i$ 处，最后一位为 $j$ 的方案数，枚举下一位的值 $k$ 然后转移到 $dp_{nxt_{i,k},k}$ 即可。最后我们强制令最后一位为 $1$，即统计所有 $dp_{i,1}$ 的和，再乘上 $s$ 中第一段 $0$ 的长度和最后一段 $0$ 的长度即可。

时间复杂度线性。

```cpp
const int MAXN=1e6;
const int MOD=1e9+7;
char s[MAXN+5];pii seg[MAXN+5];int pcnt=0;
int n,nxt[MAXN+5][2],dp[MAXN+5][2];
void add(int &x,int y){((x+=y)>=MOD)&&(x-=MOD);}
int main(){
	scanf("%s",s+1);n=strlen(s+1);int fst=0,lst=0;
	for(int i=1;i<=n;i++) if(s[i]^48){fst=i;break;}
	for(int i=n;i;i--) if(s[i]^48){lst=i;break;}
	if(!fst) return printf("%d\n",n),0;
	for(int l=1,r;l<=n;l=r+1){
		r=l;if(s[l]^48) continue;
		while(s[r]^49&&r<=n) r++;seg[++pcnt]=mp(r-1,r-l);
	} int pre=n+1;
	for(int i=n;i;i--){nxt[i][1]=pre;if(s[i]^48) pre=i;}
	pre=n+1;
	for(int i=n;i;i--){
		if(s[i]^49) pre=i;
		else nxt[i][0]=pre;
	}
	for(int i=1;i<=n;i++) if((s[i]^49)&&(s[i+1]^49))
		nxt[i][0]=i+1;
	stack<pii> stk;
	for(int i=pcnt;i;i--){
		while(!stk.empty()&&stk.top().se<=seg[i].se) stk.pop();
		if(!stk.empty()) nxt[seg[i].fi][0]=stk.top().fi-stk.top().se+1+seg[i].se;
		else nxt[seg[i].fi][0]=n+1;stk.push(seg[i]);
	}
//	for(int i=1;i<=n;i++) printf("%d %d\n",nxt[i][0],nxt[i][1]);
	dp[fst][1]=1;int ans=0;
	for(int i=fst;i<=n;i++) for(int j=0;j<2;j++){
		for(int k=0;k<2;k++) if(nxt[i][k]<=n) add(dp[nxt[i][k]][k],dp[i][j]);
		if(j==1) add(ans,dp[i][j]);
	} printf("%d\n",1ll*ans*fst%MOD*(n-lst+1)%MOD);
	return 0;
}
```



---


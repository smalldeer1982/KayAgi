# [AGC031B] Reversi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc031/tasks/agc031_b

$ N $ 個の石が一列に並んでいて、左から $ i $ 個目の石は色 $ C_i $ で塗られています。

すぬけ君は、以下の操作を $ 0 $ 回以上の任意の回数行います。

- 同じ色で塗られている $ 2 $ つの石を選ぶ。それらの石の間に置かれている石をすべて、選んだ石と同じ色で塗りかえる。

最終的な石の色の列としてありうるものの個数を $ 10^9+7 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ C_i\ \leq\ 2\times\ 10^5(1\leq\ i\leq\ N) $
- 入力はすべて整数である

### Sample Explanation 1

以下の $ 3 $ 通りの石の色の列を作ることができます。 - 操作を行わないことで、$ (1,2,1,2,2) $ - $ 1,3 $ 番目の石を選んで操作を行うことで、$ (1,1,1,2,2) $ - $ 2,4 $ 番目の石を選んで操作を行うことで、$ (1,2,2,2,2) $

## 样例 #1

### 输入

```
5
1
2
1
2
2```

### 输出

```
3```

## 样例 #2

### 输入

```
6
4
2
5
4
2
4```

### 输出

```
5```

## 样例 #3

### 输入

```
7
1
3
1
2
3
3
2```

### 输出

```
5```

# 题解

## 作者：封禁用户 (赞：3)

### 思路：

这是一个需要 $O(n)$ 复杂度的计数问题，所以想到线性 $\texttt{DP}$。

带取模的 $\texttt{DP}$ 常看前继贡献。设 $f_i$ 为前 $i$ 个的合法方案数，转移有两种情况：

- $c_i = c_{i-1}$ 时，$f_i$ 直接继承 $f_{i-1}$ 的答案。

- $c_i \neq c_{i-1}$ 时，$f_i + f_{pre_i} \to f_i$。

然后是边界，直接 $1 \to f_0$。

题目要求每一次染色都应在两个颜色相同的石头之间，方便转移，进一步降低复杂度，开一个桶 $pre_i$ 统计第 $i$ 个石头前面离他最近的与它颜色相同的石头的编号。（记住，在每次转移完成后必须要及时维护）

代码需要私信。

---

## 作者：AmamiyaYuuko (赞：2)

考虑 DP。设 $f(i)$ 表示前 $i$ 个石子的方案数，初始有 $f(0) = 1$。

然后我们分情况讨论。如果 $c_i = c_{i - 1}$，显然有 $f(i) = f(i - 1)$。

如果 $c_i \ne c_{i - 1}$，先考虑用不到第 $i$ 个石子的情况，这部分对答案的贡献是 $f(i - 1)$，然后再考虑用到了第 $i$ 个石子的情况，那么必须存在一个 $j < i$ 使得 $c_j = c_i$，这个 $j$ 对 $f(i)$ 的贡献就是 $f(j - 1)$。用一个桶维护 $\sum \limits_{c_i = c_j} f(j - 1)$ 就可以做到 $O(n)$。

代码：

```cpp
int main() {
    read(n);
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
        f[i] = f[i - 1];
        if (a[i] != a[i - 1]) {
            f[i] += s[a[i]], f[i] %= mod;
            s[a[i]] += f[i - 1], s[a[i]] %= mod;
        }
    }
    printf("%lld\n", f[n]);
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

动态规划。

看数据范围，$1 \le N \le 2 \times 10^5(1 \le i \le N)$，那我们就考虑用桶来存数字的下标。

然后当前的方案数，仅与 $a_{i - 1}$ 和上一块和当前相同颜色石头有关，那我们就可以得出转移方程：

**注意：如果当前石块的上一块颜色相同的石块的下标是 ${i - 1}$ 的话就没必要存，不然就重复了。**

如果没有颜色相同的石块：

$$dp_{i} = dp_{i-1}$$

否则：

$$dp_{i} = dp_{i - 1} + dp_{v_{a_{i}}}$$

$v$ 数组存的是上一块颜色相同石块的下标。


如果当前没有颜色相同的石块，那么现在的方案数，就是上一块石头的方案数。否则，就是上一块石头的方案数加上一块颜色相同的石头的方案数。

**Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define re rd()
#define MOD 1000000007

inline int rd()
{
	int jya = 0, tl = 1; char mntxy_bjc_wcnmm = getchar();
	while(!isdigit(mntxy_bjc_wcnmm)) {if(mntxy_bjc_wcnmm == '-') tl = -1; mntxy_bjc_wcnmm = getchar();}
	while(isdigit(mntxy_bjc_wcnmm)) {jya = jya * 10 + mntxy_bjc_wcnmm - '0'; mntxy_bjc_wcnmm = getchar();}
	return tl * jya;
}

int n, a[200100], dp[200100], v[200100];

int main()
{
	n = re;
	for(int i = 1; i <= n; i ++) a[i] = re;
	dp[0] = 1;
	for(int i = 1; i <= n; i ++)
	{
		if(v[a[i]] != 0 && v[a[i]] != i - 1) dp[i] = (dp[i - 1] + dp[v[a[i]]]) % MOD;
		else dp[i] = dp[i - 1];
		v[a[i]] = i;
	}
	cout << dp[n];
	return 0;
}
```

---

## 作者：wangqinyan (赞：1)

这题思路与代码实现其实都很简单。

# **题目思路**

这道题就是一道非常简单的动态规划。我们可以用一个数组来记录在第 ``i`` 个石块之前离他最近的相同的石块的下标。当在这个石块之前没有与他相同的石块时，将 $f_{i}$ 的答案更新为 $f_{i-1}$ 即可。否则，将 $f_{i}$ 的答案更新为 $f_{i}$ 加上与离他最近的相同的石块的区间长度即可，具体可见代码。

# **注意点**

如果在第 ``i`` 个石块之前离他最近的相同的石块是这个石块的前一个石块的话，区间里没有其他石块，不需要更新 $f_{i}$ 的答案。输出时，答案要对 $1000000007$ 取模。

# **代码**
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,b=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')b=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*b;
}
inline void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10^48);
	return;
}
const long long MOD=1e9+7;
long long a[200010],f[200010],p[200010],n;
int main()
{
//    freopen(".in","r",stdin);
//    freopen(".out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	f[0]=1;
	for(int i=1;i<=n;i++)
	{
		f[i]=f[i-1];
		if(p[a[i]]!=0&&p[a[i]]!=i-1)
		f[i]+=f[p[a[i]]];
		f[i]%=MOD;
		p[a[i]]=i;
	}
	cout<<f[n];
//    fclose(stdin);
//    fclose(stdout);
	return 0;
}


 
```
感谢观看！

---

## 作者：The_jester_from_Lst (赞：1)

简易动态规划。

我们首先设 $f_i$ 为操作至第 $i$ 位时的方案总数，设 $l_i$ 为上一次出现颜色 $i$ 的位置。这里我们考虑两种情况：

1. 不对当前石块进行操作，有 $f_i=f_{i-1}$。


2. 对当前石块进行染色操作，则从上一次出现 $a_i$ 的下标到当前下表 $i$ 的范围内都变成了 $a_i$，即 $f_i=f_{l_i}$。注意染色操作只有在颜色为 $i$ 的石头已经出现过**且不是在上一位**时才能进行，不然没有意义。

每次更新 $l_{a_i}=i$，最后输出 $f_n$ 即可。

附上代码：
```cpp
#include<bits/stdc++.h>
#define JYAAKIOI -1
#define int long long
#define pii pair<int,int>
#define rg register
#define mk make_pair
#define il inline
#define fr front()
#define ep empty()
#define pp pop()
#define mod 1000000007
using namespace std;
il int rd(){
	int jya=0,tl=1;char jyt=getchar();
	while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
	while(isdigit(jyt)){jya=jya*10+(jyt-'0');jyt=getchar();}
	return jya*tl;
}
il void wr(int jjy){
	if(jjy<0)putchar('-'),jjy=-jjy;
	if(jjy>9)wr(jjy/10);
	putchar(jjy%10+48);
}
int n,a[200086],f[200086],l[200086];
signed main(){
	memset(l,JYAAKIOI,sizeof l);
	n=rd();
	f[0]=1;
	for(int i=1;i<=n;++i){
		a[i]=rd();
		f[i]=f[i-1];
		f[i]%=mod;
		if(l[a[i]]!=-1&&l[a[i]]!=i-1){
			f[i]+=f[l[a[i]]];
			f[i]%=mod;
		}
		l[a[i]]=i;
	}
	wr(f[n]);
	return 0;
}
```


---

## 作者：concert_B (赞：1)

# [AT_agc031_b [AGC031B] Reversi](https://www.luogu.com.cn/problem/AT_agc031_b) 题解

## 算法：DP

很棒的 dp 题。

证明：

 - 显然，无论过去状态与决策如何，对前面的决策所形成的状态而言，余下的诸决策构成的必定是最优策略。即符合最优化原理。
 
 - 一旦当前状态确定，则此后过程的演变不再受该状态影响。即符合无后效性原则。

可以用 DP。

证毕。

## 实现方案

设前 $i$ 块石头所有可能的石头排列方案数为 $dp_i$。

设 $fa_a$ 为 $a$ 上一次出现的位置。

由于每个状态仅有两种转移方式：实施操作或不实施操作。

那么转移方程为：

$$dp_i \gets \begin{cases} dp_{i-1}&i = 1 \\ dp_{i-1}+ dp_{fa_{a_i}}&i > 1  \end{cases}$$

当然，必须保证 $fa_{a_i}=i-1$ 不成立。

## 复杂度

显然，为 $O(n)$。

## CODE
```cpp
#include<iostream>
#define int long long
const int N=2e5+5;
const int mod=1e9+7; 
int dp[N];
int fa[N];
int n;
signed main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0),std::cout.tie(0);
	std::cin>>n;
	for(int i=1;i<=n;i++){
		int a;
		std::cin>>a;
		dp[i]=i==1?1:dp[i-1];
		dp[i]+=fa[a]==i-1?0:dp[fa[a]];
		dp[i]%=mod;
		fa[a]=i;
	}
	std::cout<<dp[n];
	return 0;
}

```
## 完结撒花

---

## 作者：Dream__Sky (赞：1)

考虑 DP。

设 $dp_i$ 为到第 $i$ 个点共有多少种方案。

有两种转移方式，一种是不使用区间推平，那么 $dp_i=dp_{i-1}$。

如果能使用区间推平，即之前出现过 $a_i$ 这个数。我们设 $vis_x$ 为 $x$ 上一次出现的位置，那么转移方程有 $dp_i=dp_{vis_{a_i}-1}$。

由于不区间推平随时都合法，总结一下就是：

- $vis_{a_i}$ 有值时，$dp_i=dp_{i-1}+dp_{vis_{a_i}-1}$。
- 否则,$dp_i=dp_{i-1}$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10,MOD=1e9+7;
int n,a[N],f[N],vis[N];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	f[0]=1;
	for(int i=1;i<=n;i++)
	{
		f[i]=f[i-1];
		if(vis[a[i]]&&vis[a[i]]!=i-1) f[i]=(f[i]+f[vis[a[i]]])%MOD;
		vis[a[i]]=i;
	}
	
	cout<<f[n];
	return 0;
}
```


---

## 作者：ccxswl (赞：1)

# [AGC031B] Reversi 

$f_i$ 表示 $[1,i]$ 的石头有多少种排列方案数，$near_{c_i}$ 表示最近一次颜色 $c_i$ 出现的位置。

如果第 $i$ 块石头与前面的合并可以形成 $f_{near_{c_i}}$ 种答案，如果不与前面合并则形成 $f_{i-1}$ 种答案。

那么显然有：
- $near_{c_i} \neq i-1$ 时，$f_i=f_{near_{c_i}}+f_{i-1}$。
- $near_{c_i} = i-1$ 时，$f_i=f_{i-1}$。

复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

int read() {
	int x;
	scanf("%d", &x);
	return x;
}

const int maxN = 2e5 + 7, mod = 1e9 + 7;

int n, c[maxN];
int f[maxN], near[maxN];

int main() {
	n = read();
	f[0] = 1;
	for (int i = 1; i <= n; i++) {
		c[i] = read();
		f[i] = f[i - 1];
		if (near[c[i]] && near[c[i]] != i - 1)
			f[i] = (f[i] + f[near[c[i]]]) % mod;
		near[c[i]] = i;
	}
	cout << f[n] << '\n';
}
```

---

## 作者：_maojun_ (赞：1)

首先一眼看上去以为是区间 dp，然后发现根本不可能跑得过去。

然后想到维护前缀的状态就可以做了，$dp[i]$ 表示前 $1\sim i$ 的方案数。

考虑转移，如果不选则方案数为 $dp[i-1]$。设上一个 $x$ 的位置为 $lst_x$，则选的方案数就是 $lst_x$ 的方案数，因为这个区间已经被推平了。

然后就做完了，一边递推就可以了，复杂度 $O(n)$。

注意这样如果出现相同的连续颜色正确性会出现问题，所以应该先去重一下（连续的一段颜色显然可以缩掉而不会影响答案）。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;

const int MAXN=2e5+5,MOD=1e9+7;
int n,a[MAXN],dp[MAXN],lst[MAXN];
inline int add(int u,int v){return u+v<MOD?u+v:u+v-MOD;}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	n=unique(a+1,a+n+1)-a-1;	// 去重
	dp[0]=1;
	for(int i=1;i<=n;i++){
		dp[i]=dp[i-1];
		if(lst[a[i]]){
			int j=lst[a[i]];
			dp[i]=add(dp[i],dp[j]);
		}
		lst[a[i]]=i;			// 记录上次出现的位置
	}
	printf("%d\n",dp[n]);
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

# [AGC031B] Reversi


## 思路

开始感觉又是一道排列组合的题目，但后面发现貌似不是。

我们发现，如果我们对区间 $[l,r]$ 进行染色，我们就不能再对区间 $[l-a,r+b](a,b≥0)$ 进行染色了，因为这样会导致这种情况与直接对区间 $[l-a,r+b]$ 染色的情况重合。

同样，如果在原数组（我们叫它 $a$ 数组）中，$a_i=a_j$，但是我们之前执行了操作覆盖了 $a_i$ 或者 $a_j$，那么我们就不能对区间 $[i,j]$ 进行染色了。这样看上去还挺复杂的，所以我们貌似不能用排列组合去做。

所以我们考虑用 $dp$ 去做

## dp 设计

我们定义 $dp_{i}$ 为染色到第 $i$ 个石子的方案数。接下来我们考虑如何进行转移。

我们分情况讨论。

对于 $a_i=a_{i-1}$ 的情况，很容易知道 $dp_i=dp_{i-1}$，因为对于这个区间我们是否染色结果都一样。

对于 $a_i≠a_{i-1}$ 的情况，如果不对 $a_j\sim a_i$ 这个区间进行染色（$a_j$ 是 $a_i$ 前面的与 $a_i$ 颜色相同的石子），那么 $dp_i=dp_{i-1}$。

否则我们就要对 $a_j\sim a_i$ 进行染色。那么染色后的贡献就是 $dp_{j-1}$，因为我们从 $j-1$ 转移过来，要么 $[j,i]$ 区间保持原样，要么都染成 $a_i$ 的颜色。

当然，与 $a_i$ 颜色相同的 $a_j$ 可能有不止一个，所以我们要维护与 $a_i$ 颜色相同的 $a_j$ 有哪些。这样不太好维护，所以因为我们只需要用到 $dp_{j-1}$，我们只需要维护与 $a_i$ 颜色相同的所有 $a_j$ 对应的 $dp_{j-1}$ 之和即可。当然，这里的 $j$ 一定在 $i$ 之前，所以我们可以在从前往后 $dp$ 的过程中维护这个和。

至于怎么维护，因为颜色种类 $≤2\times 10^5$，所以我们用一个桶即可。

## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,MOD=1e9+7;

int a[N],n,b,x,y,T,ans,dp[N],ton[N],res,idx,cnt;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	
	dp[0]=1;
	for(int i=1;i<=n;i++){
		if(a[i]==a[i-1])dp[i]=dp[i-1];
		else{
			dp[i]=dp[i-1];
			dp[i]+=ton[a[i]];
			dp[i]%=MOD;
			ton[a[i]]+=dp[i];
			ton[a[i]]%=MOD;
		}
	}
	cout<<dp[n]<<endl;
	return 0;
}

```






---

## 作者：5k_sync_closer (赞：0)

设 $f_i$ 表示 $[1,i]$ 的石头能形成多少种序列，$p_i$ 表示当前 $i$ 的最后一次出现，

若不合并 $i$ 到 $p_{a_i}$，能形成 $f_{i-1}$ 种序列，若合并 $i$ 到 $p_{a_i}$，能形成 $f_{p_{a_i}}$ 种序列，

所以

$$
f_i=
\begin{cases}
f_{p_{a_i}}+f_{i-1}&p_{a_i}\ne0,p_{a_i}\ne i-1\\
f_{i-1}&\text{otherwise}
\end{cases}
$$

```cpp
#include <cstdio>
#define int long long
int n, p[5000050], f[5000050];
signed main()
{
    scanf("%lld", &n);
    for (int i = f[0] = 1, x; i <= n; ++i)
    {
        scanf("%lld", &x);
        f[i] = f[i - 1];
        if (p[x] && p[x] != i - 1)
            f[i] = (f[i] + f[p[x]]) % 1000000007;
        p[x] = i;
    }
    printf("%lld", f[n]);
    return 0;
}
```


---

## 作者：Aewrxuk (赞：0)

题目链接：[[AGC031B] Reversi](https://atcoder.jp/contests/agc031/tasks/agc031_b)。

考场上一直在想这道题是不是应该找到什么通用规律去解，后来发现好像想不出来，然后就骗了 $10$ 分，正解应该是线性 dp，只需要一维 dp 即可，我们用 `f[i]` 表示枚举到第 $i$ 个石头时的方案数，那么这时应该分类讨论，如果这块石头和它前一块石头颜色相同，那么这两块石头的贡献方案数就是相同的，因为靠前的石头方案数已经更新过，所以只需要传递一下即可：

```
if(c[i]==c[i-1]) f[i]=f[i-1];
```
如果不是这种情况，我们就要将当前石头和之前所有相同颜色的石头之间染上色，思考一下，我们可以直接加上据他最近的石头的位置的方案数，因为我们之前也是这样推过来的，所以这样就可以涵盖所有的新方案数，再传递一下 `f[i-1]` 即可，这一步具体可以看代码实现，应该挺好理解的……

代码实现：
```cpp
const int mod=1e9+7;

int n;

int c[5000010],now[5000010],pre[5000010],f[5000010];

int main()
{
	// file("a.in");
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i=1;i<=n;i++)
	{
		cin >> c[i];
		pre[i]=now[c[i]];
		now[c[i]]=i;
	}
	f[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(c[i]==c[i-1]) f[i]=f[i-1];
		else f[i]=(f[pre[i]]+f[i-1])%mod;
	}
	cout << f[n]%mod << '\n';
	return 0;
}
```

---

## 作者：Tastoya (赞：0)

# [AGC031B] Reversi

## 题面翻译
有 $N$ 块石头摆成一行，从左数第 $i$ 块石头的颜色是 $C_i$。

现在すぬけ会进行 $0$ 次或若干次如下操作：选取两块颜色相同的石头并将两块石头之间的所有石头都染成与这两块石头相同的颜色。

求最终所有可能的石头排列方案数，答案对 $10^9 + 7$ 取模。

### 思路
考虑 DP。

考虑第 $i$ 个石头，如果第 $i$ 个石头不修改，方案数仍为 $dp_{i-1}$；如果第 $i$ 个石头修改，那么贡献就是第 $i$ 个石头与前面所有颜色相同石头进行操作的可能操作数。

记 $\operatorname{pre}_i$ 为上一个与 $i$ 颜色相同石头的位置。

所以转移方程为
$$dp_i=dp_{i-1}+dp_{\operatorname{pre}_i}$$
### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 5005000;
const int Mod = 1e9 + 7;

int n;

int a[N];

int cnt,col[N];

int dp[N],last[N];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for(int i = 1;i <= n; i++) {
        cin >> a[i];
    }
    
    for(int i = 1;i <= n; i++) {
        if(a[i] != a[i - 1]) {
            cnt ++;
            col[cnt] = a[i];
        }
    }

    dp[0] = 1;
    for(int i = 1;i <= cnt; i++) {
        dp[i] = dp[i - 1];

        if(last[col[i]]) {
            int j = last[col[i]];
            dp[i] = (dp[i] + dp[j]) % Mod;
        }

        last[col[i]] = i;
    }

    cout << (dp[cnt] + Mod) % Mod << "\n";
    return 0;
}
```

---

## 作者：cppcppcpp3 (赞：0)

## 思路：

一道套路的 dp。

首先，由于每一次染色都必须两个颜色相同的石头间进行，所以我们可以先处理出每一个石头，在它前面且与它最近的同色石头位置，记作 $lst_i$。特别地，对于前面没有同色石头的石头 $x$，不妨令 $lst_x=x$。

设计状态： $dp_{i}$ 为前 $i$ 个数经过若干次题述操作可以得到的不同方案数。根据定义，得到初始化：$dp_0=dp_1=1$。

从 $2$ 起顺序枚举 $i$。对于整数 $i \in [2,n]$，可以分为两种情况：

第一种，当 $lst_i=i$ 时，显然 $i$ 不能作为染色的区间的端点，因此方案数 $dp_i=dp_{i-1}$；而 $lst_i=i-1$ 时，染色 $[i-1,i]$ 对序列不会有任何改变，故方案数仍为 $dp_{i-1}$。

第二种，可以不选择把 $i$ 选入染色区间，方案数为 $dp_{i-1}$；也可以染色 $[lst_i,i]$，那么之后只需处理 $[1,lst_i]$，情况数就是 $dp_{lst_i}$。此时有 $dp_i=dp_{i-1}+dp_{lst_i}$。

最终答案为 $dp_n$，复杂度 $O(n)$。

## 代码：
```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=2e5+5;
const int p=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return x*f;
}

int n,a[N],dp[N],lst[N],b[N];

main(){
	n=wrd();
	for(int i=1;i<=n;++i){
		a[i]=wrd();
		if(b[a[i]]) lst[i]=b[a[i]],b[a[i]]=i;
		else lst[i]=b[a[i]]=i;
	}

	dp[0]=dp[1]=1;
	for(int i=2;i<=n;++i){
		dp[i]=dp[i-1];
		if(lst[i]!=i && lst[i]!=i-1) (dp[i]+=dp[lst[i]])%=p;
	}	
	
	return printf("%lld",dp[n]),0;
}
```

---

## 作者：Novelist_ (赞：0)

个人感觉本题还是比较水的，就是一道新手动态规划，顶多黄。
# 本文定义
$f_i$：表示到第 $i$ 块石头有几种方案。  
$Last_i$：表示上一块颜色 $i$ 的位置。  
注：后文所有 $Last_i$ 均用 $l_i$ 代替。  
$a_i$：表示第 $i$ 块石头颜色。
# 思路
对于每块石头，我们都有两种情况，就是染色与不染色。

* 第一种：不染色。直接让 $f_i$ 继承上一块石头的值。

* 第二种：染色。$f_i$ 就是 $f_i-1 + f_li$。

值得注意的地方是每次计算后就要莫一下。

$l_i$ 的值每次更新为 $a_i$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,j,a[200002],last[200002],f[200002];
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin>>n;
  for(i=1;i<=n;++i)
  cin>>a[i];
  f[1]=1;//单独一块石头就只有一种情况，无论染或不染
  last[a[1]]=1;//第一块石头第一次出现在1
  for(i=2;i<=n;++i)//从第二块石头开始dp
  {
  	f[i]=f[i-1]%1000000007;//第一种情况
  	if(a[i]!=a[i-1]&&last[a[i]])//第二种
  	f[i]=(f[i]+f[last[a[i]]])%1000000007;
//  	else if(a[i]==a[i-1])last[a[i]]=i;
  	last[a[i]]=i;
  }
  cout<<f[n]%1000000007;
  return 0;
}
```

---


# 「MCOI-06」Distinct Subsequences

## 题目描述

给定一个由小写字符构成的字符串 $S$。

令一个字符串的价值为该串的**本质不同**非空子序列个数，其中子序列可以为整体。

求 $S$ **所有**子序列的价值和。答案对 $10^9+7$ 取模。

## 说明/提示

#### 数据规模与约定

**本题采用捆绑测试。**

 - Subtask 1（5 pts）：$|S|\le 11$。
 - Subtask 2（10 pts）：$|S|\le 22$。
 - Subtask 3（20 pts）：$|S|\le 100$ 并 $S$ 仅由 `a`，`b` 两个字符构成。
 - Subtask 4（30 pts）：$|S|\le 5000$。
 - Subtask 5（35 pts）：无特殊限制。

对于 $100\%$ 的数据，$1\le |S|\le 10^6$，保证 $S$ 仅由小写字符构成。

## 样例 #1

### 输入

```
ab```

### 输出

```
5```

## 样例 #2

### 输入

```
sapnap```

### 输出

```
593```

## 样例 #3

### 输入

```
abcbdabcbabcd```

### 输出

```
938773```

## 样例 #4

### 输入

```
tobeornottobethatisthequestion```

### 输出

```
769276982```

# 题解

## 作者：耶梦加得 (赞：13)

~~总觉得就我一个人没有把问题转换成贡献~~

设 $dp[i]$ 为前 $i$ 位的答案。

为了方便理解，我们把每一个 子序列 看作一个集合，（为了方便之后表述，我们定义这个集合的 集合名 为这个子序列）。

集合里的元素是它 本质不同的非空子序列 ，则这个集合的价值就是它的大小，$dp[i]$ 就是 $s_{[1,i]}$ 的所有子序列的 集合大小 之和。


对于 $i + 1$，设第 $i + 1$ 位上的字符为 $p$，首先我们可以什么都不做，那么现在的答案依然是 $dp[i]$。

其次，对于 $s_{[1,i]}$ 的任意子序列，可以在其后添加字符 $p$，构成了若干个新的集合，这些集合的大小之和现在是 $dp[i]$（因为是复制过来的，元素还是那些元素，只是集合名多了个 $p$）。

容易想到，对于上一段所述的每一个集合，可以在其中每一个元素之后添加字符 $p$，这样就又得到了 $dp[i]$ 个新的元素。现在总价值有 $3 * dp[i]$。

但是有两个问题需要考虑。

首先，对于一个集合，如果它的集合名第一次加入 $p$，那么这个集合会多出一个单独的元素 $p$。这相当于在一个空的子序列之后拼接一个 $p$，而这是我们需要额外考虑的（因为集合里原先只有 **非空**子序列）。

假如在 $[1, i]$ 中 $p$ 字符出现了 $cnt_p$ 次，那么一共有 $2^{i - cnt_p}$ 个集合满足这样的条件（对于每一个不是 $p$ 的字符，选或者不选），也就是说说 $dp[i + 1]$ 要额外加上 $2^{i-cnt_p}$

另外，在元素后添加 $p$ 之后可能会出现重复的元素。比如说原先集合中存在 $sa,s,a$，倘若添加字符 $a$，那么就会变成 $sa, s, a, saa, sa, aa$
，其中 $sa$ 是重复元素。容易发现这样的重复只发生在原先结尾就为 $p$ 的元素上。

我们“退一步”想，假设这个发生冲突的集合是 $s_{[1,j]}$，我们先假设 $s_j$ 为 $p$，那么每一个结尾为 $p$ 的元素都可以认为是在 $j$ 时刻被加入的。

如果在 $j$ 时刻之前就已经有结尾为 $p$ 的元素，假设为 $s1$，令子序列 $s2 = s1 - p$（表示去掉结尾的 $p$ ~~虽然不清楚有没有这种运算~~）。

容易知道，要么这个子序列为空，要么这个子序列也同样存在于这个集合中。

那么我们可以认为在 $j$ 时刻在 $s2$ 后拼接上了 $p$，替换了原来的 $s1$。

（类似于，“此位置已存在名为 s1 且扩展名为 p 的项目。您要用正在移动的项目来替换它吗？“）

也就是说，发生冲突的元素个数就等于 $dp[j - 1]$。

对于 $j$ 之后，不以 $p$ 结尾的集合，由于我们会复制元素，这之中的每个集合也都会发生 $dp[j - 1]$ 次冲突，而这样的集合共有 $2^{i - j + 1 - cnt_{j, i, p}}$ 个。

（$cnt_{j, i, p}$ 表示从 $j$ 到 $i$ 有多少个 $p$。）


综上，$dp[i + 1] = 3dp[i] + 2^{i - cnt_{1,i,p}} - \sum_{j \le i, s_j = p}dp[j - 1]*2^{i - j + 1 - cnt_{j,i,p}}$

后面那个和式，可以通过对每个字符分别记录一个 $del[p]$ 来维护，在每一位上都进行一次 $O(|\Sigma|)$ 的更新，令 $del[s_i]$ += $dp[i]$，并且对于所有 $p \ne s_i$ 有 $del[p]$ *= $2$。总复杂度 $O(n|\Sigma|)$ 。

```
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
const long long mod = 1000000007;
inline int read() {
    register int x = 0, f = 1; register char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = x * 10 + ch - 48; ch = getchar();}
    return x * f;
}
template<class T>inline T mmin(register T x, register T y) {
    return x > y ? y : x;
}
template<class T>inline T mmax(register T x, register T y) {
    return x > y ? x : y;
}
int n;
long long dp[1000007];
int lst[37], cnt[37];
long long del[37];
char ch[1000007];
inline long long power(long long a, long long b) {
    long long ret = 1ll;
    for(; b; b >>= 1) {
        if(b & 1) ret = ret * a % mod;
        a = a * a % mod;
    }
    return ret;
}
signed main() {
    scanf("%s", ch + 1);
    n = strlen(ch + 1);
    dp[1] = 1; cnt[ch[1] - 'a'] = 1;
    for(int i = 2; i <= n; ++i) {
        int x = ch[i] - 'a';
        dp[i] = dp[i - 1] * 3 % mod;
        dp[i] = (dp[i] - del[x] % mod + mod) % mod;
        dp[i] = (dp[i] + power(2, i - cnt[x] - 1)) % mod;
        //这里的快速幂是可以避免的，但是这样写方便点（反正不会T
        for(int j = 0; j < 26; ++j) if(j != x) del[j] = del[j] * 2 % mod;
        del[x] = (del[x] + dp[i - 1]) % mod;
        ++cnt[x];
    }
    printf("%lld\n", dp[n]);
    return 0;
}

```


---

## 作者：Little09 (赞：11)

**此做法对字符集大小没有限制**。也就是说，这道题可以加强，将字符串改为数列。

一个字符串的价值为该串的本质不同非空子序列个数。如果直接给定一个字符串，怎么求它的价值？我们考虑这样一个算法：

定义 $det[x]$ 表示以字符 $x$ 结尾的子序列个数。那么从 $1$ 开始依次扫过去，对于扫到的每个字符 $x$，我们只要把 $det[x]$ 替换为 $sum+1$ 就行了，$sum$ 表示当前所有 $det$ 的和。

也就是 $x$ 可以和任何一组拼接形成字符串，也可以自己单独形成。

考虑这个问题，要求所有子序列的价值和。如果转化为期望，就是对于扫到的每个 $x$，随机选择更新 $det[x]$ 或者不更新，求最后的期望 $sum$。

对于此处的期望，容易发现怎么做的概率都是相等的，因此可以直接相加取平均数。

得出期望之后乘上 $2$ 的 $|S|$ 次方就行了。

代码很好写。目前最优解，23ms。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e6+5;
char a[N];
const ll mod=1e9+7,inv2=500000004;
ll n,sum,tot=1,det[30];
inline void add(int x)
{
	ll tmp=det[x];
	det[x]=(sum+1+det[x])*inv2%mod;
	sum=(sum+sum-tmp+sum+1)*inv2%mod;
	sum=(sum+mod)%mod;
}
int main()
{
	scanf("%s",a+1);
	n=strlen(a+1);
	for (int i=1;i<=n;i++) add(a[i]-'a'),tot=(tot*2)%mod;
	cout << sum*tot%mod << endl;
	return 0;
}
```


---

## 作者：LJ07 (赞：4)

简单题。

套路地考虑每个子序列对于答案的贡献。

那么对于该子序列中相邻的两个位置 $i<j$，则必须有在 $(i,j)$ 中没有出现 $s_j$。

那么就容易了。

令 $dp_i$ 表示以 $i$ 为结尾的子序列对于 $s_{1\cdots i}$ 的贡献，$S{c,(i,j]}$ 表示在 $(i,j]$ 中 $s_x=c$ 的 $x$ 的个数。

转移方程：$dp_i=\sum_{j<i} dp_j\times 2^{i-j-S_{s_j,(j,i]}}$。

发现这个转移是跟当前的字符有关的，所以优化是容易的。

开 $26$ 个桶。$g_i$ 表示若当前字符是 $i$ 的贡献。

最后答案就是 $\sum dp_i\times 2^{n-i}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int P(1e9+7);
int n,ans,g[26],pw2[1000005]{1};
char s[1000005];
int main()
{
	scanf("%s",s+1),n=strlen(s+1);
	for(int i(1);i<=n;++i) pw2[i]=(pw2[i-1]<<1)%P;
	for(int i(0);i<26;++i)g[i]=1;
	for(int i(1),f,c;i<=n;++i)
	{
		f=g[c=s[i]-97];
		(ans+=1ll*f*pw2[n-i]%P)%=P;
		for(int j(0);j<26;++j)if(c!=j)g[j]=(g[j]<<1)%P;
		for(int j(0);j<26;++j)(g[j]+=f)%=P;
	}
	printf("%d",ans);
}
```

应该能用线段树维护 $g$ 解决字符集更大的问题。

---

## 作者：intel_core (赞：4)

##### 这应该是月赛有史以来最简单的 $\text{Div2.D}$ 了吧（小声   
##### 我语文不是很好，可能说的有点绕，大家可以看代码理解一下



------



首先，我们将原序列每个子序列 的所有子序列 取出，本质相同的保留下标最靠前的    
显然，我们直接考虑原序列的子序列再去考虑 子序列的子序列 产生的贡献是非常困难的 

所以我们换个方法，假设我们现在选定了一个子序列，那么它能在多少个 原序列的子序列 中产生贡献    

依次考虑选定序列的每个字母在原序列中的位置，依次设为 $p_1,p_2,...,p_m$    
再设这些字母依次为 $c_1,c_2,...,c_m$

> 引理：任意 $k\in [1,m)$ ，满足任意 $i \in (c_k,c_{k+1})$ 有 $s_i \ne c_{k+1}$     

简证：如果存在 $i \in (c_k,c_{k+1})$ 使得 $s_i = c_{k+1}$ ，由于我们考虑贡献的原则，选定的子序列对该子序列无贡献    

那么再考虑在原序列中去选被当前选定子序列贡献的子序列    
* 首先，$p_1$ 之前的下表中，对应字母和 $c_1$ 相同的不能选，其余随便   
* 类似地，介于 $p_k$ 和 $p_{k+1}$ 之间的字母中，和 $c_{k+1}$ 相同的不能选   
* 在 $p_m$ 之后的下标中可以随便选     

但是如此考虑仍然很难实现至非指数级别，继续考虑优化    

由于上述最后一条记录好最后一个下标后非常好处理，我们把产生贡献序列按照最后一个下标 $P$ 分开考虑    

从 $P=1$ 开始，依次考虑：   
* $P=1$ ，显然答案为 $1$   
* 假设当前我们已经考虑完了前 $k$ 个，接下来考虑第 $k+1$ 个   
	1. 如果考虑只有一个字符的情况，直接算即可   
   2. 如果长度 $\ge 2$ ，考虑倒数第二个下标为 $i$ ，前缀和 $O(1)$ 算出与 $s_{k+1}$ 相同的字母，同样可以直接递推    
   
只不过，这样做是 $O(n^2)$ 的，能获得 $\text{65 pts}$ 的高分
   
接下来考虑如何优化成 $O(n)$      

首先，注意到刚才的第二条中 $2$ 的指数只与区间长度和区间内单一字母的个数有关系    
由于现在咱们的 $|\sum|=26$ ，所以可以在扫这个字符串的时候，记录一个数组 $f_c$ ，表示当前字母如果是 $c$ 那么长度 $\ge 2$ 时答案是多少
   
在从左往右扫的时候，每次扫到一个字母时，将其余字母对应的 $f$ 全部 $\times 2$ ，接着将以当前字母结尾的答案加到对应的 $f$ 中  
   
这样做显然是 $O(|\sum|n)$ 的，但为什么是对的？    
   
相当于我们把求答案时的 $\times 2$ 放到了更新 $f$ 时    
如果细品一下可以发现能用 $|\sum|$ 换掉一个复杂度里的 $n$ 的原因其实是递推式里指数的特殊性质
   
综上，我们在 $O(|\sum|n)$ 的时间内解决了这道题     



----



附上简要算法流程：    
1. 处理字符出现次数前缀和   
2. 从 $1$ 开始依次扫每个字符，扫的时候维护：  
 * $f_c$ 表示如果下一个字符是 $c$ 那么答案是多少    
 * $g_i$ 表示考虑产生贡献的子序列最后一个下表是 $i$ 的 **去掉尾部贡献的** 答案   
 1. $g_i=f_{s_i}+2^{i-calc(1,i,s_i)}$ ，这里 $calc(l,r,x)$ 表示 $s_l,s_{l+1},...,s_r$ 中有多少个 $x$
 2. $f_j \times =2|j \ne s_i$ ，$f_j +=g_i$    
3. 最后 $ans= \sum_{i=1}^n g_i \times 2^{n-i}$   

附上极短无比的代码，变量名可能和前述稍有区别    

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int NR=1e6+10;
const int MOD=1e9+7;
int n,f[NR],cnt[NR][30];
int s[NR],c[30],ans;
char str[NR];

int quickpow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=(res*x)%MOD;
		x=(x*x)%MOD;
		y>>=1;
	}
	return res;
}

int calc(int l,int r,int k){return cnt[r][k]-cnt[l-1][k];}

signed main(){
	scanf("%s",str+1);
	n=strlen(str+1);
	for(int i=1;i<=n;i++)s[i]=str[i]-'a'+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=26;j++)cnt[i][j]=cnt[i-1][j];
		cnt[i][s[i]]++;
	}
	for(int i=1;i<=n;i++){
		f[i]=(quickpow(2,i-calc(1,i,s[i]))+c[s[i]])%MOD;
		for(int j=1;j<=26;j++){
			if(j!=s[i])c[j]=(c[j]<<1)%MOD;
			c[j]=(c[j]+f[i])%MOD;
		}
		ans=(f[i]*quickpow(2,n-i)+ans)%MOD;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Yansuan_HCl (赞：2)

考虑每个子序列能作为多少个子序列的第一个本质不同非空子序列。

我们钦点第一个子序列为贪心地匹配，即遇到一个要求的字符就加入（即子序列自动机的顺序）。那么，对于子序列 $s$ 中 $s_j=s_i$ 且 $[j+1,i-1]$ 中不存在 $s_i$：我们要求**包含它的子序列**中，该段中间也没有 $s_i$，以此避免算重。

设 $f(i)$ 表示以 $i$ 结尾的子序列能作为**原序列的本质不同序列**。要求中间相同的 $c$ 不能被选入原串的本质不同子序列，可以得到 $f(i)=\sum 2^{i-j-cnt(s_i)}f(j)$，其中 $cnt(c)$ 代表 $[j+1,i-1]$ 中 $s_i$ 的个数。

用前缀和优化。令 $\text{sum}_{c}(i)$ 表示以 $i$ 结尾字符 $c$ 的个数。即可以用前缀和优化：不妨设 $g(c)=\sum_j2^{-j+cnt_c(j)}f(j)$，则 $f(i)=2^{i-cnt_{s_i}(i)}g(s_i)$。时间复杂度 $O(n\Sigma)$。 

```cpp
const int N = 1000006;
const ll P = 1000000007, INV2 = (P + 1) / 2;
char s[N]; int n;
ll p2[N * 2], i2[N * 2];
ll g[26], sum[N][26];

int main() {
	p2[0] = i2[0] = 1;
	scanf("%s", s + 1); n = strlen(s + 1);
	U (i, 1, n) {
		U (c, 0, 25) sum[i][c] = sum[i - 1][c];
		++sum[i][s[i] - 'a'];
	}
	
	U (i, 1, n * 2)
		p2[i] = p2[i - 1] * 2 % P,
		i2[i] = i2[i - 1] * INV2 % P;
	
	U (c, 0, 25) g[c] = 1;
	ll ans = 0, f = 0;
	U (i, 1, n) { int c = s[i] - 'a';
		f = p2[i - sum[i][c]] * g[c] % P;
		(ans += f * p2[n - i]) %= P;
		U (x, 0, 25)
			(g[x] += f * i2[-sum[i][x] + i]) %= P;
	}
	printf("%lld", ans);
}
```

---

## 作者：lqsy002 (赞：1)

## 题目大意

给出一个字符串，求它的所有子序列的本质不同子序列个数。[题目链接](https://www.luogu.com.cn/problem/P7888)。

## 解题思路

1. 考虑每个子序列产生的贡献，为了防止算重子序列，对于字符串 $T$ 对字符串 $S$ 产生贡献，当且仅当 $T$ 中没有任何一个字符能在 $S$ 上匹配到更前的位置。

2. 设 $f_{i}$ 表示以位置 $i$ 结尾的子序列产生的贡献和，$g_{i}$ 表示目前以字符 $i$ 结尾的贡献和。

3. 每次 $f$ 直接用 $g$ 来做，然后再用 $f$ 更新 $g$ 即可。

## 参考代码

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll N=1e6+10,mod=1e9+7;
ll n,ans,g[26],pw[N];
char s[N];
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>(s+1);
	n=strlen(s+1);
	for(int i=0;i<26;++i)
        g[i]=1;
	pw[0]=1;
    for(ll i=1;i<=n;++i)
        pw[i]=pw[i-1]*2%mod;
	for(ll i=1;i<=n;++i){
		ll c=s[i]-'a',f=g[c];
		ans=(ans+f*pw[n-i])%mod;
		for(ll j=0;j<26;++j)
			if(j==c)
                g[j]=(g[j]+f)%mod;
			else 
                g[j]=(g[j]*2ll+f)%mod;
	}
    cout<<ans;
	return 0;
}
```

---

## 作者：yukimianyan (赞：1)


## solution
考虑如何求出一个字符串的价值？

令 $f_i$ 表示以字符 $i$ 为结尾有多少个本质不同的非空子序列。

增量法，每次加入字符 $r$，将 $f_r$ 修改为 $1+\sum_{i}f_i$，表示将之前所有以 $r$ 为结尾的子序列都接上 $r$，最后补上单独的 $r$。

我们可以将这样的过程表示为矩阵：（假设只有 $3$ 个字符，加入字符 $1$）

$$\begin{bmatrix}
f_0 &f_1 &f_2 &1
\end{bmatrix}\times
\begin{bmatrix}
1 &1 &0 &0\\
0 &1 &0 &0\\
0 &1 &1 &0\\
0 &1 &0 &1
\end{bmatrix}=
\begin{bmatrix}
f'_0 &f'_1 &f'_2 &1
\end{bmatrix}.
$$

回到原问题，要求所有子序列的价值之和。我们考虑用二项式展开的集合意义：形如

$$(a_1+1)(a_2+1)(a_3+1)=1+a_3+a_2+a_2a_3+a_1+a_1a_3+a_1a_2+a_1a_2a_3.$$

这样的东西可以求出所有子集的积的和。我们将 $a_i$ 换成矩阵，$1$ 换成单位矩阵，那么这个东西可以通过左式去算：

$$
\begin{bmatrix}0 &0 &1\end{bmatrix}
\left(
  \begin{bmatrix}1 &0 &0\\0 &1 &0\\0 &0 &1\\\end{bmatrix}+
  \begin{bmatrix}1 &0 &0\\1 &1 &0\\1 &0 &1\\\end{bmatrix}
\right)
\left(
  \begin{bmatrix}1 &0 &0\\0 &1 &0\\0 &0 &1\\\end{bmatrix}+
  \begin{bmatrix}1 &1 &0\\0 &1 &0\\0 &1 &1\\\end{bmatrix}
\right).
$$

结果的和就是样例一的答案。

暴力是 $O(n|\Sigma|^2)$ 的，但是我们发现这个矩阵只有 $O(n)$ 个有效值，因此复杂度降为 $O(n|\Sigma|)$，可以通过。

## code

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <numeric>
#include <algorithm>
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr,##__VA_ARGS__)
#else
#define debug(...) void(0)
#endif
typedef long long LL;
const int P=1e9+7;
void red(LL&x){x=(x%P+P)%P;}
int n;
char buf[1000010];
vector<LL> append(vector<LL> f,int r){
	LL sum=accumulate(f.begin(),f.end(),0ll)%P;
	vector<LL> g(27);
	for(int i=0;i<27;i++){
		red(g[i]=f[i]);
		if(i==r) red(g[i]=sum);
		red(g[i]+=f[i]);
	}
	return g;
}
void print(vector<LL>&f){
//	for(LL x:f) debug("%lld ",x);
//	puts("");
}
int main(){
//	#ifdef LOCAL
//	 	freopen("input.in","r",stdin);
//	#endif
	scanf("%s",buf+1),n=strlen(buf+1);
	vector<LL> f(27,0); f[26]=1;
	for(int i=1;i<=n;i++) f=append(f,buf[i]-'a'),print(f);
	printf("%lld\n",accumulate(f.begin(),prev(f.end()),0ll)%P);
	return 0;
}

```

---

## 作者：A2_Zenith (赞：0)

考虑我们判定 $S'$ 是否是 $T$ 的子序列的过程。我们有这样一个贪心：假设我们现在匹配到了 $S'$ 的第 $i$ 位，其与 $T$ 的第 $j$ 位匹配。我们想要匹配 $S'$ 的第 $i+1$ 位。不难发现，我们找到最小的 $k$ 使得 $k>j$，$T_k = S'_{i+1}$ 即可。这个贪心的正确性比较显然。

好，那我们尝试去设计一个 DP。我们设 $dp_{i}$ 满足：对于所有以 $S_i$ 结尾的子序列 $s$，$dp_i =$ 字符串 $T$ 的数量，使得 $s$ 与 $T$ 的匹配过程符合上文所述且 $T$ 的最后一位与 $s$ 的最后一位匹配。

这是容易的。我们尝试枚举 $s$ 的上一位 $= S_j$。那么转移方程是：

$$dp_i = \sum\limits_{j=1}^{i-1}dp_j \times 2^{\sum\limits_{k \in (i,j)}[S_k \ne S_i]}$$

在总答案中，对于 $dp_i$，$T$ 其实后面可以在 $[i+1,n]$ 中选一段接起来作为最终答案。总的答案是 $\sum\limits_{i=1}^ndp_i \times 2^{n-i}$。

把这个限制写成前缀和的形式：

令 $G_{i,c}$ 为 $[1,i]$ 中 $c$ 的个数。将转移的柿子写为

$$dp_i = \sum\limits_{j=1}^{i-1}dp_j \times 2^{i-1-j-G_{i-1,S_i}+G_{j,S_i}}$$

我们尝试分离一下变量：

$$\frac{dp_i}{2^{i-1 - G_{i-1,S_i}}} = \sum\limits_{j=1}^{i-1}dp_j \times 2^{-j+G_{j,S_i}}$$

左边只与 $i$ 有关，右侧可以维护所有可能的 $S_i$ 的取值（有字符集大小 $=26$ 种），变为只与 $j$ 有关。

看到前缀和形式联想到前缀和优化。

如此，我们便可以设 $F_{k,c} = \sum\limits_{j=1}^kdp_{j} \times 2^{-j+G_{j,c}}$。容易知道，$dp_i = 2^{i-1 - G_{i-1,S_i}}F_{i-1,S_i}$。做完了！复杂度是 $O(\Sigma n)$ 的。

---


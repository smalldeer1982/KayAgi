# [PA 2022] Drybling Bajtessiego

## 题目描述

**题目译自 [PA 2022](https://sio2.mimuw.edu.pl/c/pa-2022-1/dashboard/) Runda 3 [Drybling Bajtessiego](https://sio2.mimuw.edu.pl/c/pa-2022-1/p/baj/)**

Bytessi 因是世界足坛最好的锋线（和球员）而广为人知。为了即将到来的世界杯，他编制了一份 $n$ 种运球方式的清单，其中每次运球可以用一串字母 `L` 和 `P` 来描述，表示他用左脚和右脚触球的顺序。

如果一个球员用左脚和右脚触球次数相等，我们就称这种运球方式是**平衡的**。此外，如果对于给定的这种运球方式，如果任意一个初始部分（前缀），满足左脚触球次数不少于右脚触球次数，就称这种运球方式是**左利脚的**。由于 Bytessi 是左利脚，他认为如果一种运球方式即平衡又左利脚，那么这种运球方式是**极佳的**。

世界杯是一个特殊的比赛，世界上最好的球员都会来参赛。出于这个原因，Bytessi 需要准备更多的运球方式。他决定使用一种简单的方式把运球方式增加到 $n^2$ 种——对于初始列表中每一对运球方式（可以相同），新的运球方式用这两种运球方式直接相连来描述。换句话说，他会先使用第一种运球方式运球，然后接着用第二种运球方式运球。

在激烈的比赛中，很容易忘记一些本应进行的触球，所以 Bytessi 最后的运球方式将是他最初想的运球方式的一个非空的子序列。换句话说，最后的运球方式将通过删除他想进行的运球方式中的一些（也许没有，但不是全部）字母来得到。其余字母的顺序必须保持不变。

最终采用的运球方式将是极佳的，如果这样的话 Bytessi 会非常高兴。他现在想知道，对于新清单中的每一种运球方式，他可以意外地进行多少种可能的极佳运球方式。由于这个数字可能非常大，Bytessi 只需要知道将这个数字除以 $10^9+7$ 的余数。请帮 Bytessi 解决这个问题。

注意：Bytessi 感兴趣的是其原始运球方式的子序列可以得到多少种不同的极佳运球，而不是从原始运球的描述中划掉字母而得到极佳运球的方法的数量。

## 说明/提示

对于 $100\%$ 的数据，满足：

$1\le n\le 600$，

每种运球方式的长度不超过 $600$。

## 样例 #1

### 输入

```
4
LLPLPP
PPLP
LLP
P
```

### 输出

```
29 9 8 5
8 2 2 1
11 4 3 2
4 1 1 0
```

# 题解

## 作者：phigos (赞：5)

## 题意简化

给出 $n$ 个 $len\leq600$，仅由 $L$ 和 $P$ 构成的字符串，将 $L$ 看做左括号，$P$ 看做右括号。

求任意两个串 $a$ 和 $b$ 收尾相接后，本质不同的合法括号序列的个数。

## 思路

设左括号价值为 $1$，右括号价值为 $-1$，那么一个序列合法的充要条件是：

1. 任意前缀的价值和非负

2. 总价值为 $0$

3. 任意后缀的价值和非正

考虑将 $a$ 与 $b$ 拼接后的序列的一个子序列分成前缀和后缀，使得前缀在 $a$ 中，后缀在 $b$ 中，那么就可以分别在 $a$ 和 $b$ 中求出价值为 $k$ 和 $-k$ 的子序列的方案数。

### dp

对于 $a$ 串，设 $front_{a,j,k,0/1/2}$ 表示 $a$ 串中，考虑**前** $j$ 位，价值和为 $k$，且以左括号 $/$ 右括号 $/$ 空串结尾的方案数。

对于 $b$ 串，设 $back_{b,j,k,0/1/2}$ 表示 $b$ 中，考虑**后** $len-j+1$ 位，价值和为 $-k$，且以左括号 $/$ 右括号 $/$ 空串开头的方案数。

**初始化**

显然，初始为空串，只有一种情况，即：
$$
front_{a,0,0,2}=1
$$
$$
back_{b,0,0,2}=1
$$

**考虑如何转移**

若当前位置 $j$ 为 $'('$：
$$
front_{a,j,k,0}\gets front_{a,j-1,k-1,0/1/2}
$$
$$
back_{b,j,k,0}\gets back_{b,j+1,k+1,0/1/2}
$$
若当前位置 $j$ 为 $')'$：
$$
front_{a,j,k,1}\gets front_{a,j-1,k+1,0/1/2}
$$
$$
back_{b,j,k,1}\gets back_{b,j+1,k-1,0/1/2}
$$

### 去重

但如果直接将 $front$ 和 $back$ 乘起来统计答案**会重复**。

![](https://cdn.luogu.com.cn/upload/image_hosting/c6bzst7d.png)

如图，选择 $a$ 中 $p$ 左侧加上 $b$ 以 $j$ 开头的情况，会和选择 $a$ 中以 $p$ 结尾加上 $b$ 中 $j$ 右侧的情况重复。

因此还需要一个数组 $g_{a,j,k,0/1,0/1}$ 表示 $a$ 串中，考虑前 $j$ 位，价值和为 $k$，$j$ 右侧是否有左括号，是否有右括号的方案数。

设 $l/r$ 为 $j$ 右侧剩余的左or右括号数，就有：

$j$ 位置为左括号：
$$
g_{a,j,k,l>0,r>0}\gets g_{a,j-1,k,l>0,r>0}+front_{a,j-1,k-1,0/1/2}-front_{a,j-1,k,0}
$$
$j$ 位置为右括号：
$$
g_{a,j,k,l>0,r>0}\gets g_{a,j-1,k,l>0,r>0}+front_{a,j-1,k+1,0/1/2}-front_{a,j-1,k,1}
$$
像这样，只要 $a$ 串后面没有 $b$ 串开头的括号，就不会出现上面的重复情况。

### 统计答案

设答案为 $ans$。

若 $b$ 串以左括号开头，那么 $a$ 的末尾不能有左括号；
若 $b$ 串以右括号开头，那么 $a$ 的末尾不能有右括号；
若 $b$ 串为空串，那么 $a$ 没有限制。
$$
ans\gets (g_{a,n,k,0,0}+g_{a,n,k,0,1})\times back_{b,1,k,0}
$$
$$
ans\gets (g_{a,n,k,0,0}+g_{a,n,k,1,0})\times back_{b,1,k,1}
$$
$$
ans\gets (g_{a,n,k,0,0}+g_{a,n,k,0,1}+g_{a,n,k,1,0}+g_{a,n,k,1,1})\times back_{b,1,k,2}
$$
### 空间优化

不难发现，三个 $dp$ 数组都要开到 $n^3$，喜提MLE。

但是，对于 $j$ 这一维，我们每次转移都只用到了前一位的结果，并且统计答案只用到 $j=n$，因此可以通过调整循环的方向压掉 $j$ 这一维。

时间复杂度为 $O(n^3)$，可以通过本题。

**记得取模！！！**

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf (1ll<<60)
using namespace std;
const int N=605,mod=1e9+7;
int n,front[N][N][3],back[N][N][3],g[N][N][2][2];
char s[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>(s+1);
		int num=strlen(s+1);
		int l=0,r=0;
		for(int j=1;j<=num;j++) s[j]=='L'?l++:r++;//j右侧左/右括号的个数
		front[i][0][2]=1;
		back[i][0][2]=1;
		g[i][0][(bool)l][(bool)r]=1;
		for(int j=1;j<=num;j++){//正序处理前缀
			if(s[j]=='L'){l--;
				for(int k=600;k>=1;k--){
					(g[i][k][(bool)l][(bool)r]+=front[i][k-1][0]+front[i][k-1][1]+front[i][k-1][2]-front[i][k][0]+mod)%=mod;
					(front[i][k][0]=front[i][k-1][0]+front[i][k-1][1]+front[i][k-1][2])%=mod;
				}
			}else{r--;
				for(int k=0;k<600;k++){
					(g[i][k][(bool)l][(bool)r]+=front[i][k+1][0]+front[i][k+1][1]+front[i][k+1][2]-front[i][k][1]+mod)%=mod;
					(front[i][k][1]=front[i][k+1][0]+front[i][k+1][1]+front[i][k+1][2])%=mod;
				}
			}
		}
		for(int j=num;j>=1;j--){//倒序处理后缀
			if(s[j]=='L')
				for(int k=0;k<600;k++)
					(back[i][k][0]=back[i][k+1][0]+back[i][k+1][1]+back[i][k+1][2])%=mod;
			else
				for(int k=600;k>=1;k--)
					(back[i][k][1]=back[i][k-1][0]+back[i][k-1][1]+back[i][k-1][2])%=mod;
		}
	}
	for(int i=1;i<=n;i++){//枚举a串
		for(int j=1;j<=n;j++){//枚举b串
			int ans=mod-1;
			for(int k=0;k<=600;k++){
				(ans+=(g[i][k][0][0]+g[i][k][0][1])*back[j][k][0]%mod)%=mod;
				(ans+=(g[i][k][0][0]+g[i][k][1][0])*back[j][k][1]%mod)%=mod;
				(ans+=(g[i][k][0][0]+g[i][k][0][1]+g[i][k][1][0]+g[i][k][1][1])*back[j][k][2]%mod)%=mod;
			}
			cout<<ans<<' ';
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：small_john (赞：3)

## 思路

把 `L` 当成左括号，`P` 当成右括号，题目就是求 $n$ 个括号串两两拼接后的本质不同合法括号子序列的个数。

套路的，设左括号权值为 $1$，右括号权值为 $-1$，一个括号串合法的条件就是权值和为 $0$，任意前缀权值和非负，以及任意后缀权值和非正。

设 $f_{i,j,k,0/1/2}$ 为第 $i$ 个串，前 $j$ 个位置，权值和为 $k$，以左括号、右括号结尾或者是空串的方案数，$g_{i,j,k,0/1/2}$ 为第 $i$ 个串，以 $j$ 开头的后缀，权值和为 $-k$，以左括号、右括号开头或者是空串的方案数。

初始时 $f_{i,0,0,2},g_{i,|s_i|+1,0,2}$ 为 $1$。

由于要求本质不同，所以在前缀中选子序列的时候尽量靠后选，在后缀中选子序列的时候尽量靠前选。考虑转移。

- 当前字符为左括号，则有 $f_{i,j,k,0}=f_{i,j-1,k-1,0/1/2}$，$g_{i,j,k,0}=g_{i,j+1,k+1,0/1/2}$，$f_{i,j,k,1/2},g_{i,j,k,1/2}$ 直接继承上一位的值；
- 当前字符为右括号，则有 $f_{i,j,k,1}=f_{i,j-1,k+1,0/1/2}$，$g_{i,j,k,1}=g_{i,j+1,k-1,0/1/2}$，$f_{i,j,k,0/2},g_{i,j,k,0/2}$ 直接继承上一位的值。

但是这样算还是有重复，比如说 $s_i$ 的最后一个字符是左括号，$s_j$ 的第一个字符也是左括号，此时将 $s_j$ 拼在 $s_i$ 后时选 $s_i$ 最后的左括号或选 $s_j$ 开头的左括号是等价的。

考虑在选的时候尽量选 $s_i$ 里的，即如果 $s_i$ 中没有左括号可以往后添 $s_j$ 开头才能选左括号，右括号同理。

设 $h_{i,k,0/1,0/1}$ 为第 $i$ 个串，选的子序列的最后一个位置后面有没有左括号、右括号，权值和为 $k$ 的方案数。

统计时考虑维护 $cnt_{0/1}$ 表示是否还有左括号、右括号。对于同一种 $(cnt_0,cnt_1)$，尽量选靠右的，对于不同的，只统计原来没有出现过的。

- 当前第 $j$ 个字符为左括号，则 $h_{i,k,cnt_0,cnt_1}$ 加上 $f_{i,j-1,k-1,0/1/2}-f_{i,j-1,k,0}$；
- 当前第 $j$ 个字符为右括号，则 $h_{i,k,cnt_0,cnt_1}$ 加上 $f_{i,j-1,k+1,0/1/2}-f_{i,j-1,k,1}$。

统计答案时枚举 $s_i$ 选择的子序列权值为 $k$，$s_j$ 选择的子序列权值为 $-k$。

- 后一半的第一个字符是左括号，答案加上 $h_{i,k,0,0/1}\times g_{j,1,k,0}$。
- 后一半的第一个字符是右括号，答案加上 $h_{i,k,0/1,0}\times g_{j,1,k,1}$。
- 后一半选的是空串，答案加上 $h_{i,k,0/1,0/1}\times g_{j,1,k,2}$。

记得注意空间开销，将 $f,g$ 滚一下，以及去掉空串。

时间复杂度 $O(n^3)$，有较大的常数。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 605,mod = 1e9+7;
int n,f[N][N][3],g[N][N][3],h[N][N][2][2],L[N]; 
string s;
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i = 1;i<=n;i++)
	{
		cin>>s;
		int cnt1 = 0,cnt2 = 0;
		L[i] = s.size();
		for(int j = 0;j<L[i];j++) cnt1+=(s[j]=='L'),cnt2+=(s[j]=='P');		
		f[i][0][2] = h[i][0][cnt1>0][cnt2>0] = 1;
		for(int j = 0;j<L[i];j++)
		{
			if(s[j]=='L')
			{
				cnt1--;
				for(int k = L[i];k;k--)
				{
					(h[i][k][cnt1>0][cnt2>0]+=f[i][k-1][0]+f[i][k-1][1]+f[i][k-1][2]+mod-f[i][k][0])%=mod;
					f[i][k][0] = (f[i][k-1][0]+f[i][k-1][1]+f[i][k-1][2])%mod;
				}
			}
			else
			{
				cnt2--;
				for(int k = 0;k<L[i];k++)
				{
					(h[i][k][cnt1>0][cnt2>0]+=f[i][k+1][0]+f[i][k+1][1]+f[i][k+1][2]+mod-f[i][k][1])%=mod;
					f[i][k][1] = (f[i][k+1][0]+f[i][k+1][1]+f[i][k+1][2])%mod;
				}
			}
		}
		g[i][0][2] = 1;
		for(int j = L[i]-1;~j;j--)
			if(s[j]=='L') for(int k = 0;k<L[i];k++) g[i][k][0] = (g[i][k+1][0]+g[i][k+1][1]+g[i][k+1][2])%mod;
			else for(int k = L[i];k;k--) g[i][k][1] = (g[i][k-1][0]+g[i][k-1][1]+g[i][k-1][2])%mod;
	}
	for(int i = 1;i<=n;i++,cout<<'\n')
		for(int j = 1;j<=n;j++)
		{
			int ans = -1;
			for(int k = 0;k<=min(L[i],L[j]);k++)
				(ans+=(h[i][k][0][0]+h[i][k][0][1])*g[j][k][0]+(h[i][k][0][0]+h[i][k][1][0])*g[j][k][1]+(h[i][k][0][0]+h[i][k][0][1]+h[i][k][1][0]+h[i][k][1][1])*g[j][k][2])%=mod;
			cout<<(ans+mod)%mod<<' ';
		}
	return 0;
}
```

---

## 作者：VainSylphid (赞：3)

非常好题。提供更简洁的做法。

题意：给定 $n$ 个括号串，对于任意一对 $i,j$，求 $s_i+s_j$ 的本质不同合法括号子序列的个数。

大家都知道把左括号换成 $1$，右括号换成 $-1$，则合法括号串和为 $0$ 且任意前后缀和均非负。容易想到设计这样一个 dp：设 $f(a,j,k,op)$ 表示考虑第 $a$ 个串的前 $j$ 位，选出的子序列的前缀和均非负，和为 $k$ 且最后一个字符是 $op$ 的方案数。其中 $op=0$ 表示左括号，$op=1$ 表示右括号，$op=2$ 表示空串。

转移考虑就当前位置的字符如果是 $op$ 就从 $f(a,j-1,k-1,*)$ 转移（注意这里不能从 $f(a,j-1,k,op)$ 转移，因为要算本质不同的子序列），否则就从 $f(a,j-1,k,op)$ 转移，这是非常经典的，容易证明这样的 dp 恰好统计了所有本质不同的子序列。

类似的我们可以 dp 出 $g(a,j,k,op)$ 表示第 $a$ 个串的后 $j$ 位，选出的子序列的后缀和均非负，和为 $k$ 且开头字符是 $op$ 的方案数。我的代码里用 $op=0$ 表示右括号，$op=1$ 表示左括号，$op=2$ 表示空串，可能会有点绕。

然后用 $f(a,\lvert s_a\rvert,k,*)\times g(b,\lvert s_b\rvert,k,*)$ 贡献答案即可，记得去掉空串。

然后你写出来会发现完全不对！怎么回事呢？我们考虑随便画一个合法序列（画个图就很清晰，我懒得贴图了），然后在 $s_a$ 中应该可以取出它的一段前缀，$s_b$ 中应该可以取出它的一段后缀，你发现如果取出的极长前缀和极长后缀如果有重合的部分 $s$，我们多算了 $\lvert s\rvert$ 次。

比如说这里我们能取出一个极长前缀 `((())((` 和一个极长后缀 `))(()())`，那么 `((())(()())` 这个串被算了 $5$ 次，重合部分为 `))((`，长度为 $4$。

喜欢数数的小朋友这时候可能会想到经典的连通块点数减边数容斥。我们考虑减掉从 $s_a$ 中取出一段前缀，$s_b$ 中取出一段后缀（均不必是极长的），且将拼接处的两个相同字符重叠后可以得到一个合法括号串的方案数。例如前缀 `((()` 和后缀 `)))`，叠在一起变成 `((()))`。

我们考察这样的贡献，发现就是 $f(a,\lvert s_a\rvert,k+1,0)\times g(a,\lvert s_a\rvert,k,1)$ 和 $f(a,\lvert s_a\rvert,k,1)\times g(a,\lvert s_a\rvert,k+1,0)$，也就是考虑重合的字符是左括号还是右括号，如果是左括号，前缀应该比后缀大 $1$，如果是右括号，前缀应该比后缀小 $1$。

这样就不需要额外写一个 dp 了，时间复杂度依然是 $O(n^2\lvert s\rvert+n\lvert s\rvert^2)$，但是代码非常短。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 1000000007;
ll n,len[605],f[605][605][3],g[605][605][3];
char s[605][605];
int main()
{
	scanf("%lld",&n);
	for(ll i = 1;i <= n;i++)
		scanf("%s",s[i] + 1),len[i] = strlen(s[i] + 1);
	for(ll i = 1;i <= n;i++)
	{
		f[i][0][2] = g[i][0][2] = 1;
		for(ll j = 1;j <= len[i];j++)
		{
			if(s[i][j] == 'L')
				for(ll k = j;k;k--)
					f[i][k][0] = (f[i][k - 1][0] + f[i][k - 1][1] + f[i][k - 1][2]) % mod;
			else
				for(ll k = 0;k < j;k++)
					f[i][k][1] = (f[i][k + 1][0] + f[i][k + 1][1] + f[i][k + 1][2]) % mod;
		}
		for(ll j = 1;j <= len[i];j++)
		{
			if(s[i][len[i] - j + 1] == 'P')
				for(ll k = j;k;k--)
					g[i][k][0] = (g[i][k - 1][0] + g[i][k - 1][1] + g[i][k - 1][2]) % mod;
			else
				for(ll k = 0;k < j;k++)
					g[i][k][1] = (g[i][k + 1][0] + g[i][k + 1][1] + g[i][k + 1][2]) % mod;
		}
	}
	for(ll i = 1;i <= n;i++)
		for(ll j = 1;j <= n;j++)
		{
			ll ans = 0;
			for(ll k = 0;k <= 600;k++)
			{
				ans = (ans + f[i][k][2] * (g[j][k][0] + g[j][k][1]) + (f[i][k][0] + f[i][k][1]) * (g[j][k][0] + g[j][k][1] + g[j][k][2])) % mod;
				ans = (ans - (f[i][k + 1][0] * g[j][k][1] + f[i][k][1] * g[j][k + 1][0]) % mod + mod) % mod;
			}
			printf("%lld%c",ans," \n"[j == n]);
		}
    return 0;
}
```

---

## 作者：Rosaya (赞：2)

### 题意

给定 $n$ 个长度不超过 $lim=600$ 的括号序列。

对于所有 $i,j$，求出 $s_i+s_j$ 的非空合法子序列数量对 $10^9+7$ 取模的值。

其中 $s+t$ 表示将字符串 $t$ 接到 $s$ 后面形成的字符串。

### 思路

将左括号记为 $1$，右括号记为 $-1$。

序列合法当且仅当所有前缀权值和 $\ge 0$，并且整个序列权值和 $=0$。

而这个子序列会划分为两个区间，前缀给 $i$，后缀给 $j$。

我们考虑拼接一个前缀和后缀。

对于 $i$ 的子序列，提供前缀序列，需要任意一个前缀权值和 $\ge 0$。

对于 $j$ 的子序列，提供后缀序列，我们发现翻转 (reverse) 再反转 (flip) 后跟前缀一样，也就是任意一个后缀和 $\le 0$。

子序列不能重复，于是我们记 $f_{i,j,0/1/2}$ 表示前 $i$ 个数，前缀和为 $j$，强制以左括号，右括号或是空序列结尾的方案数。

容斥是十分简单的，大概就是 $f_{i,j,0} \leftarrow f_{i,j-1,0/1/2}$ 这样的，后缀同理。

接下来就是容斥分界点。

我们考虑什么时候能将后缀的开头移动到前缀末尾。

记 $h_{i,0/1,0/1}$ 表示权值和为 $i$ 的序列尽量往当前序列的前端匹配，当前序列末尾是否有左括号，是否有右括号的方案数。

如果当前有左括号的空余，那么 $j$ 的子序列不能以左括号开头，右括号同理。

统计答案就非常简单了，记得减去空集。

总复杂度 $O(n^2lim+lim^2n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll mod=1e9+7;

int n,len,x,y;
ll ans,f[605][605][3],g[605][605][3],h[605][605][2][2];
char s[605];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>(s+1);
        len=strlen(s+1);

        for(int j=1;j<=len;j++)
        {
            if(s[j]=='L')
                x++;
            
            if(s[j]=='P')
                y++;
        }

        f[i][0][2]=1;
        h[i][0][x>0][y>0]=1;
        for(int j=1;j<=len;j++)
        {
            if(s[j]=='L')
            {
                x--;
                for(int k=600;k;k--)
                {
                    h[i][k][x>0][y>0]=(h[i][k][x>0][y>0]+f[i][k-1][0]+f[i][k-1][1]+f[i][k-1][2]-f[i][k][0]+mod)%mod;
                    f[i][k][0]=(f[i][k-1][0]+f[i][k-1][1]+f[i][k-1][2])%mod;
                }
            }

            if(s[j]=='P')
            {
                y--;
                for(int k=0;k<600;k++)
                {
                    h[i][k][x>0][y>0]=(h[i][k][x>0][y>0]+f[i][k+1][0]+f[i][k+1][1]+f[i][k+1][2]-f[i][k][1]+mod)%mod;
                    f[i][k][1]=(f[i][k+1][0]+f[i][k+1][1]+f[i][k+1][2])%mod;
                }
            }
        }

        g[i][0][2]=1;
        for(int j=len;j;j--)
        {
            if(s[j]=='L')
            {
                for(int k=0;k<600;k++)
                    g[i][k][0]=(g[i][k+1][0]+g[i][k+1][1]+g[i][k+1][2])%mod;
            }

            if(s[j]=='P')
            {
                for(int k=600;k;k--)
                    g[i][k][1]=(g[i][k-1][0]+g[i][k-1][1]+g[i][k-1][2])%mod;
            }
        }
    }

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            ans=mod-1;

            for(int k=0;k<=600;k++)
            {
                ans=(ans+(h[i][k][0][0]+h[i][k][0][1])*g[j][k][0])%mod;
                ans=(ans+(h[i][k][0][0]+h[i][k][1][0])*g[j][k][1])%mod;
                ans=(ans+(h[i][k][0][0]+h[i][k][0][1]+h[i][k][1][0]+h[i][k][1][1])*g[j][k][2])%mod;
            }

            cout<<ans<<' ';
        }

        cout<<'\n';
    }

    return 0;
}
```

---

## 作者：cool_milo (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P9258)

容斥做法对我这种退役多时，脑子有点不太好使的老年选手有点太过超前了，怎么办呢？

我们可以来点不需要脑子的简单做法。

## 基本思想

首先考虑暴力。每次把所求的两个串拼接到一起，直接 dp。根据本质不同子序列类题目的通用做法，设 $dp_{j,0/1,k}$ 表示 dp 处理到第 $j$ 个字符，最后一个字符是 L 或者 P，目前 L 的个数减去 P 的个数是 $k$ 的方案数。

由于要求本质不同，所以我们对于每一种子序列，在它出现的最靠后的位置统计它。规定每次只能从目前的最后一个 L 和最后一个 P 转移。就能保证统计到所有子序列。每个串的 dp 复杂度是 $O(|S|^2)$ 的，总复杂度 $O(n^2|S|^2)$，无法通过本题。

注意到可以滚动数组，空间复杂度可以做到 $O(|S|)$ 。

```cpp
for(int j = 1; j <= len[i]; j++) {
	memset(tmp, 0, sizeof tmp);
	for(int k = 0; k < N - 1; k++) {
		int w = Add(dp[i][0][k], dp[i][1][k]);
		if(arr[i][j] == 'L') {
			tmp[0][k + 1] = w; 
			tmp[1][k] = dp[i][1][k];
		}
		else {
			if(k) {
				tmp[1][k - 1] = w;
			}
			tmp[0][k] = dp[i][0][k];
		}
	}
	if(arr[i][j] == 'L') {
		Inc(tmp[0][1], 1);
	}
	memcpy(dp[i], tmp, sizeof tmp);
}
```

我们思考这个做法为什么很浪费时间。对于一个拼接的串，它的第一部分其实每次的 dp 都一样。并且如果把第一部分运行结束后的的 dp 数组视为 $2|S|$ 个变量，在第一部分变化时，第二部分可以视为 **对这些变量执行了相同的线性变换**，我们要做的就是根据这个思想分别处理两个部分，然后简单合并即可。

## 具体实现

显然我们只用求出最后的 $dp_{|S|,1,0}$。那么我们就把 $dp_{|S|,1,0}$ 写成 $k_1x_1 + k_2x_2 + \cdots + k_nx_n + b$ 的形式。初始化 $f_{|S|,1,0}$ 为1，把第一次 dp 的贡献方式完全倒转过来，逆推 $k_1\sim k_n$ 。每一次逆推的复杂度是 $O(|S|^2)$ 的。

注意到其实我们不用单独求出 $b$，因为根据我们的 dp 过程，b 的本质是 **起点不在第一部分的所有串的数量**，那么就是第二部分单独的 $dp_{|S|,1,0}$。所以其实 $k_1x_1 + k_2x_2 + \cdots + k_nx_n$ 是求出了 **起点在第一部分的所有串的数量**。

最后枚举两个部分，用 $f_{|S_2|,0/1,k}$ 乘上 $dp_{|S_1|,0/1,k}$ 累加即可。

复杂度 $O(n^2|S| + n|S|^2)$。

## code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P = 1e9+7;
const int N = 605;
template<typename T>inline void read(T &a)
{
	a = 0;
	int f = 1;
	char c = getchar();
	while(!isdigit(c))
	{
		if(c == '-')	f = -1;
		c = getchar();
	}
	while(isdigit(c))
		a = a * 10 + c - 48,c = getchar();
	a *= f;
}

template<typename T,typename ...L> inline void read(T &a,L &...l)
{
	read(a),read(l...);
}

inline int Mul(int a, int b) {
	return (long long)a * b % P;
} 

inline int Add(int a, int b) {
	return a + b >= P ? a + b - P : a + b;
}

inline void Inc(int &a, int b) {
	a = Add(a, b);
}

int n, dp[N][2][N], f[N][2][N], tmp[2][N], ans[N][N], len[N];
char arr[N][N];

int main() {
	read(n);
	for(int i = 1; i <= n; i++) {
		scanf("%s", arr[i] + 1);
		len[i] = strlen(arr[i] + 1);
	}
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= len[i]; j++) {
			memset(tmp, 0, sizeof tmp);
			for(int k = 0; k < N - 1; k++) {
				int w = Add(dp[i][0][k], dp[i][1][k]);
				if(arr[i][j] == 'L') {
					tmp[0][k + 1] = w; 
					tmp[1][k] = dp[i][1][k];
				}
				else {
					if(k) {
						tmp[1][k - 1] = w;
					}
					tmp[0][k] = dp[i][0][k];
				}
			}
			if(arr[i][j] == 'L') {
				Inc(tmp[0][1], 1);
			}
			memcpy(dp[i], tmp, sizeof tmp);
		}
	}
	
	//计算最后每个位置贡献到ans的系数。
	
	for(int i = 1; i <= n; i++) {
		f[i][0][0] = f[i][1][0] = 1;
		for(int j = len[i]; j >= 1; j--) {
			memset(tmp, 0, sizeof tmp);
			for(int k = 0; k < N - 1; k++) {
				if(arr[i][j] == 'L') {
					if(k) {
						Inc(tmp[0][k - 1], f[i][0][k]); 
						Inc(tmp[1][k - 1], f[i][0][k]);
					}
					Inc(tmp[1][k], f[i][1][k]); 
				}
				else {
					Inc(tmp[0][k + 1], f[i][1][k]);
					Inc(tmp[1][k + 1], f[i][1][k]);
					Inc(tmp[0][k], f[i][0][k]);
				}
			}
			memcpy(f[i], tmp, sizeof tmp); 
		}
	} 
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			for(int k = 0; k < N; k++) {
				Inc(ans[i][j], Add(Mul(dp[i][0][k], f[j][0][k]), Mul(dp[i][1][k], f[j][1][k])));
			}
			Inc(ans[i][j], dp[j][1][0]);//在右边已经出现过 
			printf("%d ", ans[i][j]);
		}
		puts("");
	}
}
```

---

## 作者：Microscopic_WaXeR (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P9258)

PA 题还是太优秀了

# 做法思路

我们考虑刻画本质不同的子序列。

先考虑我们如何判定一个字符串 $T$ 是否是 $S$ 的子序列，这个我们可以通过贪心的一位一位配对来解决，也就是说将 $T$ 尽量往前放。

所以我们有一种方法可以不重不漏的刻画这个子序列，也就是将其尽量往前放。我们令 $f_{i,j,k}$ 表示当前是第 $i$ 个字符串，此时已经放到了第 $j$ 位，子序列中 $L$ 的个数减去 $P$ 的个数为 $k$ 有多少种方案。

转移就可以表示成 $f_{i,j,k} = \sum_{j=i-1}^{j\ge0} f_{i,j-1,k\pm1} [j+1\,\texttt{到}\,i-1\,\texttt{中没有跟}\,s_{i,j}\,\texttt{相同的字符}]$。 

其中 $k$ 的加减一取决于 $s_{i,j}$ 是什么，中括号为艾弗森约定。

这时这个题就基本做完了，拼接就需要前一个串剩下的后缀中没有出现后一个串最前面的一个字符，也就是说我们先正着做一遍，存下答案，再反着做一遍，同时计算答案就好了。

此时要注意空串等细节。

# 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define F(x,y,z) for(int x=(y);x<=(z);x++)
using namespace std;
const int N = 610, mod = 1e9 + 7;
bool st;
int n, len[N], pre[N];
ll f[N][N], sum[N][N], bef[N][N][2], ans[N][N];
ll bac[N][2];
char s[N][N];
bool ed;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> (s[i] + 1);
        len[i] = strlen(s[i] + 1);
    }

    for (int i = 1; i <= n; i++) {
        int lstP = 0, lstL = 0;

        for (int j = 1; j <= len[i]; j++) {
            if (s[i][j] == 'P') {
                pre[j] = lstP;
                lstP = j;
            } else {
                pre[j] = lstL;
                lstL = j;
            }
        }

        f[0][0] = 1;
        sum[0][0] = 1;

        for (int j = 1; j <= len[i]; j++) {
            for (int k = 0 + (s[i][j] == 'L'); k <= len[i] - (s[i][j] == 'P'); k++) {
                if (pre[j] == 0) {
                    if (s[i][j] == 'L')
                        f[j][k] = sum[j - 1][k - 1];
                    else
                        f[j][k] = sum[j - 1][k + 1];
                } else {
                    if (s[i][j] == 'L')
                        f[j][k] = (sum[j - 1][k - 1] - sum[pre[j] - 1][k - 1] + mod) % mod;
                    else
                        f[j][k] = (sum[j - 1][k + 1] - sum[pre[j] - 1][k + 1] + mod) % mod;
                }

                sum[j][k] = (sum[j - 1][k] + f[j][k]) % mod;
            }

            if (s[i][j] == 'L')
                sum[j][0] = sum[j - 1][0];
            else
                sum[j][len[i]] = sum[j - 1][len[i]];
        }

        for (int k = 0; k <= len[i]; k++) {
            bef[i][k][0] = (sum[len[i]][k] - ((lstL) ? sum[lstL - 1][k] : 0) + mod) % mod;
            bef[i][k][1] = (sum[len[i]][k] - ((lstP) ? sum[lstP - 1][k] : 0) + mod) % mod;
        }

        for (int j = 1; j <= n; j++)
            ans[i][j] = sum[len[i]][0] - 1;
    }

    for (int i = 1; i <= n; i++) {
        reverse(s[i] + 1, s[i] + 1 + len[i]);
        int lstP = 0, lstL = 0;
        bac[0][0] = bac[0][1] = 0;

        for (int j = 1; j <= len[i]; j++) {
            bac[j][0] = bac[j][1] = 0;

            if (s[i][j] == 'P') {
                pre[j] = lstP;
                lstP = j;
            } else {
                pre[j] = lstL;
                lstL = j;
            }
        }

        f[0][0] = 1;
        sum[0][0] = 1;

        for (int j = 1; j <= len[i]; j++) {
            for (int k = 0 + (s[i][j] == 'P'); k <= len[i] - (s[i][j] == 'L'); k++) {
                if (pre[j] == 0) {
                    if (s[i][j] == 'P')
                        f[j][k] = sum[j - 1][k - 1];
                    else
                        f[j][k] = sum[j - 1][k + 1];
                } else {
                    if (s[i][j] == 'P')
                        f[j][k] = (sum[j - 1][k - 1] - sum[pre[j] - 1][k - 1] + mod) % mod;
                    else
                        f[j][k] = (sum[j - 1][k + 1] - sum[pre[j] - 1][k + 1] + mod) % mod;
                }

                if (s[i][j] == 'L')
                    bac[k][0] = (bac[k][0] + f[j][k]) % mod;
                else
                    bac[k][1] = (bac[k][1] + f[j][k]) % mod;

                sum[j][k] = (sum[j - 1][k] + f[j][k]) % mod;
            }

            if (s[i][j] == 'L')
                sum[j][len[i]] = sum[j - 1][len[i]];
            else
                sum[j][0] = sum[j - 1][0];
        }

        for (int j = 1; j <= n; j++)
            for (int k = 0; k <= min(len[i], len[j]); k++) {
                ans[j][i] = (ans[j][i] + bef[j][k][0] * bac[k][0] % mod + bef[j][k][1] * bac[k][1] % mod) % mod;
            }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << ans[i][j] << ' ';

        cout << '\n';
    }

    return 0;
}
```
###### 代码经过了 loj 美化，不然~~太丑了~~

---


# 「SWTR-4」Lining up

## 题目背景

作为班长的小 S 在指挥操场上的一群同学排队，Lining up 可不是一件容易的事情。

## 题目描述

操场上有排成一列的 $n$ 个同学，每个同学要么是男生，用 ```B``` 表示；要么是女生，用 ```G``` 表示。

我们定义两个相邻的同学的满意度如下：

- 如果两个相邻的同学的性别相同，那么就会像普通同学一样聊天，产生 $0$ 点满意度。

- 如果前面的同学是男生，后面的同学是女生，那么就不会有任何事件发生。同学们都很活跃，他们不希望这么无聊，产生 $-b$ 点满意度。

- 如果前面的同学是女生，后面的同学是男生，那么他们就会聊得很开心，产生 $a$ 点满意度。

由于小 S 是近视眼，所以他无法分辨有些同学的性别，用 ```?``` 表示。

为了提高自己在大家心目中的地位，小 S 想保证所有相邻同学的满意度之和不小于 $m$。

他想知道满足“所有相邻同学的满意度之和不小于 $m$”的概率是多少，对 $10^9+7$ 取模。

## 说明/提示

【样例 $1$ 说明】

共有 $1$ 个满足题意的队形 $\tt BGB$。概率为 $\frac{1}{2} \bmod (10^9+7)=500000004$。

【样例 $2$ 说明】

共有 $6$ 个满足题意的队形 $\tt BBB,BGB,GBB,GBG,GGB,GGG$。概率为 $\frac{6}{8} \bmod (10^9+7)=750000006$。

【样例 $5$ 说明】

真实答案为 $\dfrac{29}{64}$。

【数据范围与约定】

**本题使用捆绑测试。**

Subtask 编号 | $n\leq$ | 特殊性质 | 分数
:-: | :-: | :-: | :-:
$1$ | $2020$ | 没有```?``` | $8$
$2$ | $20$ | 无 | $17$
$3$ | $250$ | 无 | $29$
$4$ | $2020$ | $a=1,b=1$ | $10$
$5$ | $2020$ | 无 | $36$

对于全部数据，$2 \leq n \leq 2020$，$1 \leq |m| \leq 10^{12}$，$1 \leq a,b \leq 10^9$，$s_i \in \tt{\{B,G,?\}}$。

**请注意特殊的空间限制。**

【Tips】

如果你不会对分数取模，可以看看[这里](https://www.luogu.com.cn/problem/P2613)。

【Source】

[Sweet Round 04](https://www.luogu.com.cn/contest/26414)$\ \ $D

idea：[ET2006](https://www.luogu.com.cn/user/115194)，std：[Isaunoya](https://www.luogu.com.cn/user/96580)，验题：[Isaunoya](https://www.luogu.com.cn/user/96580) & [FrenkiedeJong21](https://www.luogu.com.cn/user/203968) & [chenxia25](https://www.luogu.com.cn/user/138400)

## 样例 #1

### 输入

```
3 1 2 1
BG?
```

### 输出

```
500000004```

## 样例 #2

### 输入

```
3 -1 4 3
???
```

### 输出

```
750000006```

## 样例 #3

### 输入

```
5 5 7 3
G??B?
```

### 输出

```
625000005```

## 样例 #4

### 输入

```
6 10 9 4
??GB??
```

### 输出

```
937500007```

## 样例 #5

### 输入

```
20 20 15 10
B?G?B?G?????BBBG?GG?
```

### 输出

```
78125001```

# 题解

## 作者：Alex_Wei (赞：8)

Upd on 2020.10.7 修改一个小 typo。

[题面传送门](https://www.luogu.com.cn/problem/P6212)

Subtask $1$：没啥好说的，记得开 long long。

---

- 接下来的前置知识：有理数取模 [P2613](https://www.luogu.com.cn/problem/P2613)。

Subtask $2$：我们设问号的个数为 $y$，明显可以 $2^y$ 暴力枚举问号是 $\texttt{B\ or\ G}$，计算出符合条件的情况数 $x$，答案就是 $\large\frac{x}{2^y}$，对 $10^9+7$ 取模就行了。

时间复杂度：上界为 $\mathcal{O(2^n)}$。

---

- 接下来我们只讨论如何得到符合条件的情况数，前置知识：基础 DP。

Subtask $3$：考虑 $4$ 维 DP，$f_{i,j,k,p}$ 表示前 $i$ 位同学组成了 $j$ 个 $\texttt{GB}$，$k$ 个 $\texttt{BG}$，且当前位为 $p$（$p=0$ 时为 $\texttt{G}$，$p=1$ 时为 $\texttt{B}$）共有多少种情况，其中 $i\in[1,n],j\in[1,n],k\in[1,n],p\in\{0,1\}$。转移方程：

$$f_{i,j,k,0}=\begin{cases}0&s_i=\texttt{B}\\f_{i-1,j,k-1,1}&s_{i-1}=\texttt{B},s_i=\texttt{G}\\f_{i-1,j,k,0}&s_{i-1}=\texttt{G},s_i=\texttt{G}\\f_{i-1,j,k-1,1}+f_{i-1,j,k,0}&s_{i-1}=\texttt{?}\ ,s_i=\texttt{G}\end{cases}$$

$f_{i,j,k,1}$ 的转移方程和上面类似，不再赘述。

最后枚举所有 $j,k$，如果 $j\times a-k\times b\ge m$，情况数就加上 $f_{n,i,j,0}+f_{n,i,j,1}$。

时间复杂度：$\mathcal{O(n^3)}$。

---

- 下文中，我们设 $x$ 为 $\texttt{GB}$ 的个数，$y$ 为 $\texttt{BG}$ 的个数。

Subtask $4$：其实这个 Subtask 是引导你走向正解的（逃

该 Subtask 就是在求最后的 $x-y\ge m$ 共有多少种情况。

这就不由地让我们提出一个问题：$x$ 与 $y$ 到底有什么关系？它们的差的范围是多少？

如果你想到这个问题，那么恭喜你，你离 AC 本题不远了！

现在的你只需要挖掘出这个性质：**在任何时刻，$|x-y|\leq 1$**。

应该挺好理解的吧 qwq，举个例子：如果现在有一个转折点 $\texttt{BG}$，那么下一个转折点一定不可能是 $\texttt{BG}$，因为中间一定经过一个 $\texttt{GB}$ 的转折。说的再通俗一点，就是 $\texttt{BG.....BG}$ 的省略号中一定有 $\texttt{GB}$ 的转折。

所以这就引出了 Subtask $5$ 的解法：仍然是 $4$ 维 DP，$f_{i,j,k,p}$ 表示前 $i$ 位同学，$x$ 的值为 $j$，**$x-y+1$ 的值为 $k$**，且当前位为 $p$（$x,y,p$ 的定义上文有说明）共有多少种情况，其中 $i\in[1,n],j\in[1,n],k\in\{0,1,2\},p\in\{0,1\}$。

这样，时间复杂度就被我们压缩成了 $\mathcal{O(n^2)}$。

注意到空间只有 $8\texttt{MB}$，滚动数组优化一下即可。

感谢验题人 [Isaunoya](https://www.luogu.com.cn/user/96580) 倾情赞助的 std，因为出题人写的 std 锅掉了。

```cpp
// powered by c++11
// by Isaunoya
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7 ;
int qpow(int x , int y) {
	int res = 1 ;
	for( ; y ; y >>= 1 , x = 1ll * x * x % mod)
		if(y & 1)
			res = 1ll * res * x % mod ;
	return res ;
}
int inv(int x) {
	return qpow(x , mod - 2) ;
}

int n , a , b ;
long long m ;
const int maxn = 2020 + 0202 ;
int arr[maxn] ;
int dp[2][maxn][3][2] ;
// i
// j * a
// -(j-k+1)
void del(int & x) {
	if(x >= mod) x -= mod ;
}
void addGB(int i) {
	int p = i & 1;
	for(int j = 0 ; j < i ; j ++)
		for(int k = 0 ; k < 2 ; k ++) {
			dp[p][j][k][0] += dp[p ^ 1][j][k + 1][1] ;
			del(dp[p][j][k][0]) ;
		}
}
void addBG(int i) {
	int p = i & 1;
	for(int j = 1 ; j < i ; j ++) 
		for(int k = 1 ; k < 3 ; k ++) {
			dp[p][j][k][1] += dp[p ^ 1][j - 1][k - 1][0] ;
			del(dp[p][j][k][1]) ;
		}
}
void addBB(int i) {
	int p = i & 1;
	for(int j = 0 ; j < i ; j ++)
		for(int k = 0 ; k < 3 ; k ++) {
			dp[p][j][k][1] += dp[p ^ 1][j][k][1] ;
			del(dp[p][j][k][1]) ;
		}
}
void addGG(int i) {
	int p = i & 1;
	for(int j = 0 ; j < i ; j ++)
		for(int k = 0 ; k < 3 ; k ++) {
			dp[p][j][k][0] += dp[p ^ 1][j][k][0] ;
			del(dp[p][j][k][0]) ;
		}
}

int main() {
// code begin.
	cin >> n >> m >> a >> b ;
	for(int i = 1 ; i <= n ; i ++) {
		char c ;
		cin >> c ;
		if(c == '?') arr[i] = 2 ;
		if(c == 'B') arr[i] = 1 ;
		if(c == 'G') arr[i] = 0 ;
	}
	if(arr[1] < 2) dp[1][0][1][arr[1]] = 1 ;
	else dp[1][0][1][1] = dp[1][0][1][0] = 1 ;
	for(int i = 2 ; i <= n ; i ++) {
		for(int j = 0 ; j < i ; j ++)
			for(int k = 0 ; k < 3 ; k ++)
				dp[i & 1][j][k][0] = dp[i & 1][j][k][1] = 0;
	// 0 - G
		if(arr[i] == 0 && arr[i - 1] == 0) addGG(i) ;
		if(arr[i] == 0 && arr[i - 1] == 1) addGB(i) ;
		if(arr[i] == 0 && arr[i - 1] == 2) addGG(i) , addGB(i) ;
	// 1 - B
		if(arr[i] == 1 && arr[i - 1] == 0) addBG(i) ;
		if(arr[i] == 1 && arr[i - 1] == 1) addBB(i) ;
		if(arr[i] == 1 && arr[i - 1] == 2) addBB(i) , addBG(i) ;
	// 2 - ?
		if(arr[i] == 2 && arr[i - 1] == 0) addGG(i) , addBG(i) ; // ?G
		if(arr[i] == 2 && arr[i - 1] == 1) addBB(i) , addGB(i) ; // ?B
		if(arr[i] == 2 && arr[i - 1] == 2) { // ??
			addBG(i) , addBB(i) ;
			addGB(i) , addGG(i) ;
		}
	}
	int cnt = 0 ;
	for(int i = 1 ; i <= n ; i ++)
		if(arr[i] == 2) ++ cnt ;
	int ans = 0 ;
	for(int j = 0 ; j <= n ; j ++) 
		for(int k = 0 ; k < 3 ; k ++) {
			if(1ll * j * a - 1ll * (j - k + 1) * b >= m) {
				ans += dp[n & 1][j][k][0] ;
				del(ans) ;
				ans += dp[n & 1][j][k][1] ;
				del(ans) ;
			}
		}
	cout << 1ll * ans * inv(qpow(2 , cnt)) % mod << '\n' ;
	return 0 ;
// code end.
}
```

---

## 作者：我怂了 (赞：0)

## 题意简述
对于一个由 `B`、`G` 组成的序列，存在一个 `BG` 的相邻两位使得收益减少 $b$，存在一个 `GB` 相邻使得收益增加 $a$。

对于一个由 `B`、`G`、`?` 组成的序列，将 `?` 随机替换为前两种，求总的收益不小于 $m$ 的概率。
## 解题思路
不难发现样本空间 $|\Omega|=2^w$ 其中 $w$ 为 `?` 的个数。所以考虑统计合法的基本事件个数。

对于极小的数据：$O(n2^w)$ 枚举，统计答案。

对于更大的数据：明显是个 dp。

考虑一个相对暴力的方式：记 $dp_{i,w,j,k}$ 为前 $i$ 个位置中有 $j$ 个 $+a$、$k$ 个 $-b$ 位置，并且这一位为 `B`($w=1$）或是 `G`（$w=0$）的方案数。

记输入的字符串为 $s$。

转移方程：
$$dp_{i,1,j,k}=dp_{i-1,1,j,k}+dp_{i-1,0,j-1,k}(s_i\ne \text{G})$$
$$dp_{i,0,j,k}=dp_{i-1,0,j,k}+dp_{i-1,1,j,k-1}(s_i \ne \text{B})$$
最后挨个枚举计算 $dp_{n,0,j,k}$ 和 $dp_{n,1,j,k}$ 中的合法情况统计答案即可。

时间复杂度是...... $O(n^3)$ 吧？也许。反正确乎是过去不的。

考虑优化：发现如果把 `B` 看作 $1$，`G` 看作 $0$，那么收益就相当于原序列的差分序列中 $1$ 的个数乘上 $a$ 再减去 $-1$ 的个数乘上 $b$。

差分序列的前缀和（第一项的差分钦定为 $0$）就相当于 $+a$、$-b$ 的数量之差。

那么我们发现这个前缀和（记为 $S_i$）的范围很奇妙：$|S_i|\le1$，因为如果第一项是 $0$，那么 $S_i$ 就相当于这一项；如果是 $1$，那么 $S_i$ 就相当于这一项减去 $1$。

所以说上方 dp 方程中有 $|j-k|\le1$，而同时又有 $j+k\le n$。于是乎便可以列一个新的 dp：$dp_{i,w,p,q}$，其中 $p$、$q$ 表示上面方程中 $j+k$ 和 $j-k$。统计答案的时候通过类似解方程组把 $j$、$k$ 解出来。

如果 $aj-bk\ge m$ 则方案合法。

最后，由于 8MB 的伟大空间限制，请使用滚动数组。

由于计数题的优越性质，请使用 `long long`。

转移方程见下方代码（很醒目的一坨，不用注释也能一眼看见 qwq，还有为了简化编码 $q$ 的 $-1$ 情况用 $2$ 代替）：

```cpp
#include<bits/stdc++.h>

using namespace std;
const int maxn=2021;
typedef long long ll;
const ll p=1e9+7;
int dp[2][2][maxn][3],n,m,a,b;
char q[maxn];
ll cnt;
ll ksm(ll x,ll y){
	ll r=1;
	while(y){
		if(y&1){
			r=r*x%p;
		}
		y>>=1;
		x=x*x%p;
	}
	return r;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>a>>b;
	cin>>(q+1);
	if(q[1]=='?'){
		cnt++;
		dp[1][1][0][0]=dp[1][0][0][0]=1;
	}
	else if(q[1]=='G'){
		dp[1][0][0][0]=1;
	}
	else{
		dp[1][1][0][0]=1;
	}
	int cur=1;
	for(int i=2,pre=1;i<=n;pre^=1,i++){
		cur^=1;
		dp[cur][1][0][0]=dp[pre][1][0][0];
		dp[cur][0][0][0]=dp[pre][0][0][0];
		for(int i=1;i<=n;i++){
			dp[cur][1][i][0]=(dp[pre][1][i][0]+dp[pre][0][i-1][2])%p;
			dp[cur][1][i][1]=(dp[pre][1][i][1]+dp[pre][0][i-1][0])%p;
			dp[cur][1][i][2]=dp[pre][1][i][2];
			dp[cur][0][i][0]=(dp[pre][0][i][0]+dp[pre][1][i-1][1])%p;
			dp[cur][0][i][1]=dp[pre][0][i][1];
			dp[cur][0][i][2]=(dp[pre][0][i][2]+dp[pre][1][i-1][0])%p;
		}
		int r=100;
		if(q[i]=='B'){
			r=0;
		}
		else if(q[i]=='G'){
			r=1;
		}
		else{
			cnt++;
		}
		if(r<=1){
			for(int i=0;i<=n;i++){
				for(int j=0;j<=2;j++){
					dp[cur][r][i][j]=0;
				}
			}
		}
	}
	cnt=ksm(2,cnt);
	cnt=ksm(cnt,p-2);
	ll ans=0;
	for(int i=0;i<=n;i++){
		if(i&1){
			if((i>>1)*a-((i>>1)+1)*b>=m){
				for(int j=0;j<=2;j++){
					ans=(dp[cur][0][i][j]+dp[cur][1][i][j]+ans)%p;
				}
			}
			else if(((i>>1)+1)*a-(i>>1)*b>=m){
				ans=(ans+dp[cur][0][i][1]+dp[cur][1][i][1])%p;
			}
		}
		else{
			if((i>>1)*a-(i>>1)*b>=m){
				ans=(ans+dp[cur][0][i][0]+dp[cur][1][i][0])%p;
			}
		}
	}
	ans=ans*cnt%p;
	cout<<ans;
}
```

---


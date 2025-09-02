# Divide, XOR, and Conquer

## 题目描述

You are given an array of $ n $ integers $ a_1, a_2, \ldots, a_n $ .

In one operation you split the array into two parts: a non-empty prefix and a non-empty suffix. The value of each part is the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of all elements in it. Next, discard the part with the smaller value. If both parts have equal values, you can choose which one to discard. Replace the array with the remaining part.

The operations are being performed until the length of the array becomes $ 1 $ . For each $ i $ ( $ 1 \le i \le n $ ), determine whether it is possible to achieve the state when only the $ i $ -th element (with respect to the original numbering) remains.

Formally, you have two numbers $ l $ and $ r $ , initially $ l = 1 $ and $ r = n $ . The current state of the array is $ [a_l, a_{l+1}, \ldots, a_r] $ .

As long as $ l < r $ , you apply the following operation:

- Choose an arbitrary $ k $ from the set $ \{l, l + 1, \ldots, r - 1\} $ . Denote $ x = a_l \oplus a_{l + 1} \oplus \ldots \oplus a_k $ and $ y = a_{k + 1} \oplus a_{k + 2} \oplus \ldots \oplus a_{r} $ , where $ \oplus $ denotes the bitwise XOR operation.
- If $ x < y $ , set $ l = k + 1 $ .
- If $ x > y $ , set $ r = k $ .
- If $ x = y $ , either set $ l = k + 1 $ , or set $ r = k $ .

For each $ i $ ( $ 1 \le i \le n $ ), determine whether it is possible to achieve $ l = r = i $ .

## 说明/提示

In the first test case, it is possible to achieve $ l = r = i $ for any $ i $ from $ 1 $ to $ n $ :

- for $ i=1 $ : $ [1; 6] \rightarrow [1; 4] \rightarrow [1; 1] $ ;
- for $ i=2 $ : $ [1; 6] \rightarrow [1; 3] \rightarrow [2; 3] \rightarrow [2; 2] $ ;
- for $ i=3 $ : $ [1; 6] \rightarrow [1; 3] \rightarrow [3; 3] $ ;
- for $ i=4 $ : $ [1; 6] \rightarrow [1; 4] \rightarrow [4; 4] $ ;
- for $ i=5 $ : $ [1; 6] \rightarrow [5; 6] \rightarrow [5; 5] $ ;
- for $ i=6 $ : $ [1; 6] \rightarrow [6; 6] $ .

Let's take a closer look at $ i = 2 $ . Initially $ l = 1 $ , $ r = 6 $ .

1. We can choose $ k = 3 $ and set $ r = k = 3 $ since $ (3 \oplus 2 \oplus 1) = 0 \ge 0 = (3 \oplus 7 \oplus 4) $ ;
2. Next, we can choose $ k = 1 $ and set $ l = k + 1 = 2 $ since $ 3 \le 3 = (2 \oplus 1) $ ;
3. Finally, we can choose $ k = 2 $ and set $ r = k = 2 $ since $ 2 \ge 1 $ .

## 样例 #1

### 输入

```
6
6
3 2 1 3 7 4
5
1 1 1 1 1
10
1 2 4 8 4 1 2 3 4 5
5
0 0 0 0 0
5
1 2 3 0 1
1
100500```

### 输出

```
111111
10101
0001000000
11111
11001
1```

# 题解

## 作者：樱雪喵 (赞：13)

为什么不会做呢。/hsh

区间 DP，设 $f_{i,j}$ 表示区间 $[i,j]$ 能否被保留。发现转移是 $O(n)$ 的，总时间复杂度为 $O(n^3)$。

考虑优化转移，先观察异或的性质。设 $s_{l,r}$ 表示区间 $[l,r]$ 的异或和。

考虑区间 $[l,k]$ 什么情况下能从 $[l,r]$ 转移过来 $(k<r)$，那么若 $s_{l,r}$ 的第 $x$ 位为 $0$，不论 $s_{l,k}$ 的这位取几都与另外一半相等。而 $s_{l,r}$ 这位是 $1$ 时，如果这是最高位的 $1$，那 $s_{l,k}$ 这位自然也必须取 $1$；否则因为 $s_{l,k}$ 前面已经比另一半大了，这一位取值无限制。

则 $[l,k]$ 能从 $[l,r]$ 转移过来当且仅当 $s_{l,k}$ 在 $\operatorname{highbit}(s_{l,r})$ 位上是 $1$。

维护 $L_i$ 表示以 $i$ 为左端点，所有**能被保留**区间出现的 $\operatorname{highbit}$ 值按位或的结果，转移条件为 $s_{i,j}\land L_i \neq 0$。从左侧转移同理，转移复杂度变为 $O(1)$。

注意特判。

```cpp
const int N=1e4+5;
int T,n,a[N];
int s[N],L[N],R[N],ans[N];
il int highbit(int x) {return (x!=(1ll<<62))?(1ull<<(63-__builtin_clzll(x))):(1ll<<62);}
il int sum(int l,int r) {return (s[r]^s[l-1])?(s[r]^s[l-1]):(1ll<<62);}
signed main()
{
	T=read();
	while(T--)
	{
		n=read();
		for(int i=1;i<=n;i++) a[i]=read(),L[i]=0,R[i]=0;
		for(int i=1;i<=n;i++) s[i]=s[i-1]^a[i];
		L[1]|=highbit(sum(1,n)),R[n]|=highbit(sum(1,n)),ans[1]=1;
		for(int len=n-1;len;len--)
		{
			for(int i=1;i<=n-len+1;i++)
			{
				int j=i+len-1;
				int flag=(((sum(i,j)|(1ll<<62))&L[i])|((sum(i,j)|(1ll<<62))&R[j]));
				if(flag) L[i]|=highbit(sum(i,j)),R[j]|=highbit(sum(i,j));
				if(len==1) ans[i]=(flag>0);
			}
		}
		for(int i=1;i<=n;i++) printf("%lld",ans[i]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：SnowTrace (赞：6)

*2600 确实神啊。

但是你就算是要卡 $O(n^2\log n)$ 为啥不放 $6000$ 要放 $10000$？让我一度以为是大常数 2log 的算法，导致想题的时候是一点没想到区间 dp 上。

比较 $naive$ 的想法是直接区间 dp，但是转移是 $O(n)$ 的显然无法接受。

于是需要分析性质。

我们考虑 $x \oplus y \leq x$ 这个式子的性质。

（可以把 $x$ 看成分裂出来的区间异或和， $y$ 是原区间的异或和）

巧的是，$x \oplus y \leq x$ 当且仅当 $x$ 在 $y$ 最高位上是 $1$。

（$y = 0$ 需要特判）

我们可以记录对于固定一个左端点的合法区间中每个区间异或和的最高位的集合，然后每次转移的时候查询是否存在其中的一个最高位，使得 $x$ 在这一位上为 $1$。右端点同理。

发现这样做还是不优，我们考虑把所有的最高位可能性压位在一个数中，设为 $mask$，那么 $mask$ 与 $x$ 的与运算结果只要不是 $0$，就代表 $x$ 的这段区间是合法的。

小 trick：$O(1)$ 查询一个数的最高位可以用 stl 函数，见代码。

$dp$ 数组显然是不用记录的，因为最后的转移和 $dp$ 数组无关了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int L[10005],R[10005],okl[10005],okr[10005];
bool ans[10005];
int a[10005],pre[10005],n;
inline int highbit(int x){
	return (1ull<<(63-__builtin_clzll(x)));
}void solve(){
	cin >>n;
	for(int i = 0;i<=n;i++)L[i] = R[i] = okl[i] = okr[i] =0 ;
	for(int i= 1;i<=n;i++)cin >>a[i];
	for(int i = 1;i<=n;i++)pre[i] = pre[i-1]^a[i];
	if(pre[n])L[1]|=highbit(pre[n]),R[n]|=highbit(pre[n]);
	else okl[1] = 1,okr[n] = 1;
	if(n == 1){
		cout << 1 << '\n';return;
	}
	for(int len = n-1;len>=1;len--){
		for(int l = 1;l+len-1<=n;l++){
			int r = l+len-1;
			int sum = pre[r]^pre[l-1],hb = highbit(sum);
			if(okl[l] or okr[r] or (sum&L[l]) or (sum&(R[r]))){
				if(sum)L[l]|=hb,R[r]|=hb;
				else okl[l] = okr[r] = 1;
				if(len == 1)ans[l] = 1;//dp[l][r] = 1;
			}else if(len == 1)ans[l] = 0;
		}
	}for(int i = 1;i<=n;i++)cout << ans[i];cout << endl;
}
signed main(){
	int t;cin >> t;
	while(t--){
		solve();
	}
	
	return 0;
}
```


---

## 作者：Drimpossible (赞：6)

~~ctj过了这道题，感觉tj里都写得不是很清楚，于是自己也来写一发~~
## 思路：
### 暴力：
首先我们可以想到一个看起来很对的暴力，用记忆化搜索做区间 DP，但是我们没办法确定一个之前无法保留的区间后面有没有可能被保留，所以一个区间有可能被访问很多次总的时间复杂度大概是 $O(n^3)$，空间 $O(n^2)$，难以接受

### 正解：
我们考虑一个能保留的区间 $[l,r]$ 如何 转移到其子区间 $[l,k] (l \leq k < r)$（由于 $[k,r]$ 的情况和 $[l,k]$ 一样，就不分开讨论了）

设 $s_{x,y}$ 表示 $[x,y]$ 区间的异或和，$hibit(x)$ 为 $x$ 在二进制下的最高位 **1**。

$\because s_{l,r}=s_{l,k} \oplus s_{k+1,r}$

$\therefore hibit(s_{l,r})= \max(hibit(s_{l,k}) , hibit(s_{k+1,r}))$

如果 $[l,k]$ 能被保留只能是 $hibit(s_{l,k})=hibit(s_{l,r})$

想到这里这道题就已经做完了一半了，我们用一个数组 $L_i$ 表示以 $i$ 为左端点的每一个区间异或和的最高位，每次遇到一个新的可行的区间 $[i,j]$ 就把当前区间异或和的最高位按位或到 $L_i$ 里（$R_i$ 同理），每次只要 $L_i \& s_{i,j}$ 或者 $R_j\& s_{i,j}$ 不为零，那么这个区间就是可行的。

注意异或和为 $0$ 是可以保留的。

实现细节看代码吧：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e4+5;
int T,n,a[N],s[N];
int hibit(int x){
    if(x==(1ll<<62))return (1ll<<62);//特判零
    return 1ull<<(63-__builtin_clzll(x)/*这个函数返回的是二进制下前导零的个数*/);
}
int sum(int l,int r){
    if((s[r]^s[l-1])==0)return (1ll<<62);//特判零的情况，将零默认为最大值
    return s[r]^s[l-1];
}
int l[N],r[N],ans[N];
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i],s[i]=s[i-1]^a[i];
		for(int i=1;i<=n;i++)
			l[i]=r[i]=0;
		l[1]|=hibit(sum(1,n)),r[n]|=hibit(sum(1,n));
		for(int len=n-1;len>=1;len--){
			for(int i=1;i+len-1<=n;i++){
				int j=i+len-1;
				int flag=(((sum(i,j)|(1ll<<62))&l[i])|((sum(i,j)|(1ll<<62))&r[j]));//因为我们区间长度从大到小，所以当前l[i]存的是右端点在j后面的信息
				if(flag)l[i]|=hibit(sum(i,j)),r[j]|=hibit(sum(i,j));
				if(len==1)ans[i]=(flag>0);
			}
		}
		for(int i=1;i<=n;i++)cout<<ans[i];
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Pengzt (赞：6)

[CF1863F](https://www.luogu.com.cn/problem/CF1863F)

$\mathcal{O}(n^3)$ 的区间 dp 是好想的，不过是从大区间转移到小区间，考虑怎么进行优化。

状态是难以进行优化的了，从转移入手。

令 $s_i=\sum\limits_{j=1}^{i}a_j$。

对于两个区间 $[l,p)$ 和 $[p,r]$。令 $x=s_{p-1}\oplus s_{l-1}$，$y=s_r\oplus s_{p-1}$。

因为直接对 $x$，$y$ 考虑是麻烦的，需要找出一个定值。令 $z=x\oplus y=s_r\oplus s_{l-1}$。首先 $x=y$ 是容易的，即 $z=0$。考虑什么时候 $x<y$，即有 $z\oplus y<y$，容易得到当且仅当 $y$ 在 $z$ 的最高位是 $1$ 的时候满足条件。这是已经可以对于 所有 $i$ 记录出以 $i$ 为左 / 右端点，所有能被保存下来的区间中是否存在异或和的 $\text{highbit}=k$，这时由于枚举的 $len$ 递减，所以一定是正确的。这是已经优化到 $\mathcal{O}(n^2\log V)$ 了。

最后一步的优化十分显然，因为判断以 $i$ 为端点的区间存储的是 $\log V$ 个 bool 类型的数，然后是找是否有能保存下来的区间的 $\text{highbit}$ 满足和 $s_r\oplus s_{l-1}$ 的与不为 $0$，这就可以直接将二进制压成一个 long long 了，注意特判一下区间和为 $0$ 的情况。

时间复杂度：$\mathcal{O}(n^2)$。

[评测记录](https://www.luogu.com.cn/record/123921487)

---

## 作者：OccDreamer (赞：4)

### 简要题意

你有两个指针 $l,r$ 初始时 $l=1,r=n$。

你可以操作若干次知道 $l=r$。

每次操作你可以选择一个整数 $k \in [l,r)$，记 $x=\bigoplus_{i=l}^k a_i,y=\bigoplus_{i=k+1}^r a_i$。

- 如果 $x \leq y$，你可以令 $l=k+1$。
- 如果 $x \geq y$，你可以令 $r=k$。

现在你需要对于每一个整数 $i \in [1,n]$，求最后能否使 $l=r=i$。

$n \leq 10000$，$0 \leq a_i < 2^{60}$。

### 做法

我们设 $f_{x,y}$ 表示是否可以令 $l=x,r=y$。

首先我们考虑一个区间 $[x,y]$ 可以到达，那么什么样的区间可以被它转移到。

设 $q=\bigoplus_{i=l}^r a_i$。

1. 如果 $q=0$，那么区间 $[x,y]$ 可以转移到 $[x,x],[x,x+1]\dots [x,y-1]$ 和 $[x+1,y],[x+2,y]\dots [y,y]$。
2. 如果 $q \neq 0$，我们设 $h=\operatorname{highbit}(q)$。
	- 考虑左端点右移转移到 $[t,y]$，那么必然有 $\bigoplus_{i=t}^y a_i \operatorname{and} h \neq 0$。
    - 考虑右端点左移转移到 $[x,t]$，那么必然有 $\bigoplus_{i=x}^t a_i \operatorname{and}h \neq 0$。

考虑按照区间长度从大到小枚举 $x,y$，然后看 $f_{x,y}$ 是否可以被转移到。

首先一个区间 $[l,r]$ 能转移到 $[x,y]$ 首先要有 $l=x$ 或者 $r=y$。

然后就是 $\operatorname{highbit}(\bigoplus_{i=l}^r a_i) \operatorname{and} (\bigoplus_{i=x}^ya_i) \neq 0$。

我们记录两个辅助转移的数组 $L,R$，分别表示用来转移 $l=x$ 和 $r=y$ 的情况。

看一个区间 $[x,y]$ 是否可以被转移到只需要看 $\operatorname{highbit}(\bigoplus_{i=l}^r a_i) \operatorname{and} L_x \neq 0$ 和 $\operatorname{highbit}(\bigoplus_{i=l}^r a_i) \operatorname{and} R_y \neq 0$ 就行，两者满足其一即可转移。

如果求出了一个区间 $[x,y]$ 可以到达，那么我们只需要令 $L_x=L_x \operatorname{or} \operatorname{highbit}(\bigoplus_{i=l}^r a_i)$，$R_y=R_y \operatorname{or} \operatorname{highbit}(\bigoplus_{i=l}^r a_i)$ 即可。

放个代码可能好理解一些。

```cpp
#include<bits/stdc++.h>

#define ll long long

using namespace std;

const int MAXN = 1e5+5;
const int mod = 200003;

int n;
int c[MAXN], tot;

ll stateL[MAXN], stateR[MAXN];

bool dp[10002][10002];

ll a[MAXN], pre[MAXN];

inline ll rebuild(ll x){
	tot=0;
	while(x){
		c[++tot]=x&1;
		x>>=1;
	}
	while(tot<=60) c[++tot]=0;
	reverse(c+1,c+1+tot); x=0;
	for(int i=1;i<=tot;++i) x+=(ll)c[i]<<(i-1);
	return x;
}

inline ll lowbit(ll x){return x & -x;}

inline void solve(){	
	cin >> n; ll v;
	for(int i=1;i<=n;++i) stateL[i]=stateR[i]=0;
	for(int i=1;i<=n;++i) cin >> a[i], a[i]=rebuild(a[i]), pre[i]=pre[i-1]^a[i];
	for(int i=1;i<=n;++i) for(int j=i;j<=n;++j) dp[i][j]=0; dp[1][n]=1;
	for(int len=n;len>=1;--len){
		for(int l=1, r=l+len-1;r<=n;++l, ++r){
			v=pre[r]^pre[l-1]; v|=1ll<<61;
			dp[l][r]|=((stateL[l]&v)!=0);
			dp[l][r]|=((stateR[r]&v)!=0);
			if(dp[l][r]) stateL[l]|=lowbit(v), stateR[r]|=lowbit(v);
		}
	}	
	for(int i=1;i<=n;++i) putchar('0'+dp[i][i]); putchar(10);
	return ;
}

int main(){
	int t; cin >> t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：LSC666 (赞：3)

题目传送门：[CF1863F](https://www.luogu.com.cn/problem/CF1863F)

# 定义
- $s(l, r)$ 表示 $l$ 到 $r$ 异或和。

- 区间 $[l, r]$ 合法当且仅当它可以由 $[1, n]$ 缩小得来。

- $\operatorname{highbit}(x)$ 表示保留 $x$ 在二进制下的最高位，其余换为 $0$。比如 $\operatorname{highbit}(45) = \operatorname{highbit}((101101)_2) = (100000)_2 = 32$。

# 解题
想一下在大区间 $[l, r]$ 中选择小区间 $[l, k]$ 的条件是什么？

是 $s(l, k) \ge s(k+1, r)$。

试比较 $a=s(l, k)$ 和 $b=s(k+1, r)$ 大小。

从二进制考虑。假如 $a$ 和 $b$ 前面有一些数位是相同的，到了第 $d$ 位才出现分别，由于异或运算，第 $d$ 位自然是 $s(l, r)$ 的最高位。那么，要使 $a>b$（选左边），$a$ 的第 $d$ 位必须是 $1$；如果要选右边，$b$ 的第 $d$ 位必须是 $1$ 。

特殊情况：$s(l, r)=0$，此时 $s(l, k) = s(k+1, r)$，选哪边都行。

因此，选择左边区间 $[l, k]$ 的条件是：

$$
\operatorname{highbit}(s(l, r)) \& s(l, k) \ne 0 \lor s(l, r)=0
$$

选右边区间同理。

用区间dp，从大区间往小推。对于每个小区间$[x, y]$，如果我们找到任意一个已知合法的区间 $[x, r] (r>y)$ 或者 $[l, y] (l<x)$，且满足上面的条件，就可以推出 $[x, y]$ 也是合法的。

可以把所有以$l$为左端点的合法区间的 highbit 信息压到一个数 $hl[l]$ 中，把所有以$r$为右端点的合法区间的 highbit 信息压到一个数 $hr[r]$ 中，全部按位或起来即可。

这样，转移方程如下，其中布尔值 $f(l, r)$ 表示区间 $[l, r]$ 合法性：

$$ 
f(l, r) = (s(l, r) \ \& \ hl[l] \ne 0) \ or \ (s(l, r) \ \& \ hr[r] \ne 0) 
$$

由于区间长度从大往小算，$hl,hr$只会记录比当前区间长度长的信息。

但是要注意判断 $s(l, r)=0$ 情况，一旦计算到某个 $s(l, r)=0$，就标记：所有以$l$为左端点的区间、以$r$为右端点的区间都合法！（下面代码用 anyl、anyr 表示这个标记）

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ofor(i, a, b) for (register int i = a; i < b; i++)
#define cfor(i, a, b) for (register int i = a; i <= b; i++)
#define bfor(i, a, b) for (register int i = a; i >= b; i--)
#define set0(a) memset(a, 0, sizeof(a));
#define X 10005
typedef long long ll;

int T, n;
ll a[X];
ll sum[X]; // 异或前缀和 
ll hl[X], hr[X];
// hl[l]是二进制数，其中从右往左第d位上的数，表示：
// 所有以l为左端点的区间中，有/没有一个合法区间的异或和的最高位为d。
// hr[r]表示所有以r为右端点的区间中，……
bool anyl[X], anyr[X]; // anyl[l] = 1，表示任何以l为左端点的区间都能取 

inline ll highbit(ll x) {
	return 1ll << (63 - __builtin_clzll(x)); // 内置函数
}
inline ll xor_sum(int l,int r) {
	return sum[r] ^ sum[l - 1];
}

int main() {
	cin >> T;
	while (T--) {
		set0(hl);
		set0(hr);
		set0(anyl);
		set0(anyr);
		cin >> n;
		cfor (i, 1, n) cin >> a[i];
		
		cfor (i, 1, n) sum[i] = sum[i - 1] ^ a[i];
		
		int r;
		ll xs;
		bool f;
		bfor (len, n, 1) {
			cfor (l, 1, n - len + 1) {
				r = l + len - 1;
				xs = xor_sum(l, r);
				f = (xs & hl[l]) or (xs & hr[r]);
				if (anyl[l] or anyr[r]) f = true;
				if (len == n) f = true;
				if (len == 1) cout << f;
				// 区间dp，f表示区间[l, r]是否合法，不需要用数组存
				if (f) {
					hl[l] |= highbit(xs), hr[r] |= highbit(xs);
					if (xs == 0) anyl[l] = anyr[r] = true; // 如果异或和为0，那么选左边右边都可以 
				}
			}
		}
		cout << endl;
	}
	
	return 0;
}
```

---

## 作者：hfjh (赞：3)

# F. Divide, XOR, and Conquer

## 题意

有一个长为 $n$ 的数组 $a_1, a_2, \cdots, a_n$。

在每次操作中，你可以把数组分成两段，留下一段，扔掉另一段，要求前者的异或和不小于后者的。重复操作，直到只剩下一个数为止。

对于每个 $i$，问最后剩下来的可不可能是第 $i$ 个数。

有 $t$ 组数据。$1 \le t \le 10\ 000$，$1 \le n \le 10\ 000$，$1 \le a_i \le 2^{60}$，$\sum n \le 10\ 000$。

## 题解

先考虑 $O(n^3)$ dp。

设 $f_{i,j}$ 表示区间 $[i,j]$ 是否可以被留下来。

转移就是：

$$
f_{i,j} = \bigwedge_{k=j + 1}^n (f_{i,k} \vee [\bigoplus_{l=i}^ja_j \ge \bigoplus_{l=j + 1}^ka_l])
$$

如何优化？

我们考虑 $f_{i,j}$ 直接转移。

设一个大区间 $[l,r]$ 异或和**最高位**是 $w$，可以被分割成 $[l,k]$ 和 $[k+1,r]$ 并且:

保留前一段**当且仅当** $[l,k]$ 的异或和 $w$ 位为 $1$。

保留后一段**当且仅当** $[k+1,r]$ 的异或和 $w$ 位为 $1$。

> 因为当 $[l,r]$ 的异或和最高位为 $w$ 时，大于 $w$ 的位 $[l,r]$ 和 $[k+1,r]$ 相同，而 $w$ 这一位 $[l,k]$ 为 1，那么 $[k + 1, r]$ 必定为 0。后一段同理。

我们记录 $L_i$ 是一个 60 位二进制数，第 $w$ 位为 1 表示以 $i$ 开头的某个可保留区间最高位为 $w$。

同理我们记录 $R_i$，第 $w$ 位为 1 表示以 $i$ 结尾的某个可保留区间最高位为 $w$。

从大到小考虑每个区间，区间 $[l,r]$ 合法当且仅当 $(\bigoplus_{i=l}^r \wedge L_l) \vee (\bigoplus_{i=l}^r \wedge R_r) = 1$。

若当前区间合法还需要用这个区间更新一下 $L_l,R_r$。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 1e4 + 10; 
const ll inf = (1ll << 62);
int t, n, r;
ll a[N], p[N], L[N], R[N], now;
ll highbit(ll x){
	if(x == inf) return inf;
	return (1ll << (63 - __builtin_clzll(x)));
}
void input(){
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i], p[i] = p[i - 1] ^ a[i];
}
ll js(int l, int r){
	if((p[r] ^ p[l - 1]) == 0) return inf; 
	return (p[r] ^ p[l - 1]);
}
void op(){
	L[1] |= highbit(js(1, n));
	R[n] |= highbit(js(1, n)); 
	for(int len = n - 1; len >= 1; --len){
		for(int l = 1; l <= n - len + 1; ++l){
			r = l + len - 1;
			if(( (js(l, r) | inf) & L[l]) || ((js(l, r) | inf) & R[r])){
				L[l] |= highbit(js(l, r));
				R[r] |= highbit(js(l, r));
			}
		}
	}
}
void output(){
	for(int i = 1; i <= n; ++i){
		now = highbit(a[i]);
		if(( (a[i] | inf) & L[i]) || ((a[i] | inf) & R[i]))cout<<1;	
		else cout<<0;
	}
	cout<<'\n';
}
void qk(){
	for(int i = 1; i <= n; ++i) L[i] = R[i] = 0;
}
int main(){
	cin.tie(0)->sync_with_stdio(false);
	cin >> t;
	while(t--){
		qk();
		input();
		
		op();
		output();
	}
	return 0;
}
```

---

## 作者：hanjinghao (赞：3)

# 思路

一个很直接的想法是记录 $ f_{i,j} $ 表示 $ [i,j] $ 这段区间是否能被保存下来。由于转移需要 $ O(n) $，总时间复杂度为 $ O(n ^ 3) $。

分析异或的性质：$ x \oplus y = x $ 当且仅当 $ y = 0 $。$ x \oplus y \lt x $ 当且仅当 $ x $ 在 $ y $ 的最高位那一位是 $ 1 $。

我们可以对于每一个 $ i $，记录以 $ i $ 为左端点/右端点的**能被保存下来的区间**中，是否有区间的异或和的最高位是 $ j $，这样转移的时间复杂度就是 $ O(\log V) $，其中 $ V $ 为值域。

继续优化。我们可以把那些最高位或起来，用一个变量存储，转移的时候判断这个变量和**当前区间的异或和**按位与的结果是否为零即可。这样转移的时间复杂度就被优化到了 $ O(1) $，总时间复杂度为 $ O(n ^ 2) $。

# 代码

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

template < typename T >
inline const void read(T &x)
{
	bool flg = x = 0;
	char c;
	while ((c = getchar()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = getchar()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline const void write(T x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = x % 10 | 48;
		x /= 10;
	}while (x);
	while (len)
		putchar(OUTPUT[len--]);
}

template < typename T >
inline const void writesp(const T x)
{
	write(x);
	putchar(32);
}

template < typename T >
inline const void writeln(const T x)
{
	write(x);
	putchar(10);
}

const int N = 10005;
ull a[N], s[N], bl[N], br[N];
bool vl[N], vr[N];
char str[N];

int main()
{
	int T;
	read(T);
	while (T--)
	{
		int n;
		read(n);
		for (int i = 1; i <= n; ++i)
		{
			read(a[i]);
			s[i] = s[i - 1] ^ a[i];
			vl[i] = vr[i] = bl[i] = br[i] = 0;
			str[i] = '0';
		}
		if (n == 1)
		{
			puts("1");
			continue;
		}
		str[n + 1] = '\0';
		if (s[n]) bl[1] = br[n] = (1ull << (63 - __builtin_clzll(s[n])));
		else vl[1] = vr[n] = 1;
		for (int len = n - 1; len; --len)
			for (int l = 1, r; (r = l + len - 1) <= n; ++l)
				if (vl[l] || vr[r] || (bl[l] & (s[r] ^ s[l - 1])) || (br[r] & (s[r] ^ s[l - 1])))
				{
					if (l == r) str[l] = '1';
					ull tmp = s[r] ^ s[l - 1];
					if (tmp)
					{
						ull num = (1ull << (63 - __builtin_clzll(tmp)));
						bl[l] |= num;
						br[r] |= num;
					}
					else vl[l] = vr[r] = 1;
				}
		puts(str + 1);
	}
	return 0;
}
```

---

## 作者：灵茶山艾府 (赞：2)

## 一

首先，有如下 $\mathcal{O}(n^3)$ 区间 DP 写法：

从 $f(1, n)$ 开始递归。

对于 $f(L,R)$，枚举在 $[L,R]$ 中的下标 $k$：

- 如果 $[L,k]$ 中的异或和比 $[k+1,R]$ 中的异或和大，则往下递归 $f(L,k)$，表示我们可以得到子数组 $[L,k]$。
- 如果 $[L,k]$ 中的异或和比 $[k+1,R]$ 中的异或和小，则往下递归 $f(k+1,R)$，表示我们可以得到子数组 $[k+1,R]$。
- 如果一样大，则往下递归 $f(L,k)$ 以及 $f(k+1,R)$，表示子数组 $[L,k]$ 和 $[k+1,R]$ 都可以得到。

如果递归到 $L=R$ 的状态，则说明能通过操作得到 $a_L$。

如何优化这个区间 DP？

## 二

从 $f(i,j)$ 的角度上看，需要知道：

- 是否存在 $R$，使得我们可以从 $f(i,R)$ 递归到 $f(i,j)$。
- 是否存在 $L$，使得我们可以从 $f(L,j)$ 递归到 $f(i,j)$。

当然，前提是我们能递归到 $f(i,R)$ 或者 $f(L,j)$。

如果可以 $\mathcal{O}(1)$ 算出能否递归到 $f(i,j)$，就可以用 $\mathcal{O}(n^2)$ 的时间顺利通过本题。

设 $s_1$ 为下标在 $[i,R]$ 的元素异或和，$s_2$ 为下标在 $[i,j]$ 的元素异或和。

如果可以从 $f(i,R)$ 递归到 $f(i,j)$，说明 $[j+1,R]$ 的异或和小于等于 $s_2$，即 $s_1 \operatorname{xor} s_2 \le s_2$。

什么情况下 $s_1 \operatorname{xor} s_2 \le s_2$ 成立呢？

## 三

首先考虑特殊情况，如果 $s_1 = 0$，那么 $s_1 \operatorname{xor} s_2 \le s_2$ 恒成立。

如果 $s_1 > 0$，**从高到低**考虑每个比特位：

- 如果 $s_1$ 这一位是 $0$，那么 $s_2$ 这一位是 $0$ 是 $1$ 都可以，并且没法判断 $s_1 \operatorname{xor} s_2$ 和 $s_2$ 谁大谁小。
- 如果 $s_1$ 这一位是 $1$，那么 $s_2$ 这一位也必须是 $1$，且此时 $s_1 \operatorname{xor} s_2 < s_2$ 成立。如果 $s_2$ 这一位是 $0$，那么 $s_1 \operatorname{xor} s_2 > s_2$。由于确定清楚了大小关系，所以考虑到此就可以盖棺定论了。由于我们是从高到低遍历的，所以 $s_1$ 的**最高位**的 $1$ 必须在 $s_2$ 中。

根据 [从集合论到位运算](https://leetcode.cn/circle/discuss/CaOJ45/)，用集合语言描述，我们要满足：集合 $s_1$ 是空集，或者集合 $s_1$ 的最大元素一定在集合 $s_2$ 中。如果不满足该条件，则 $s_1 \operatorname{xor} s_2 > s_2$，我们无法从 $f(i,R)$ 递归到 $f(i,j)$。

对于 $[i,j+1], [i,j+2], \cdots, [i,n-1]$ 中的**能递归到的区间**，计算每个区间的异或和，把异或和的二进制视作集合，把集合的最大元素，记录到集合 $\textit{rightBits}$ 中。如果有异或和是 $0$，则直接把 $\textit{rightBits}$ 标记为 $-1$。
如果 $\textit{rightBits}=-1$ 或者 $\textit{rightBits}$ 和 $s_2$ 的交集不为空，即 $\textit{rightBits} \operatorname{and} s_2 \ne 0$，则说明我们可以递归到 $f(i,j)$。

上面讨论的是从 $f(i,R)$ 递归到 $f(i,j)$ 的情况，对于从 $f(L,j)$ 递归到 $f(i,j)$ 的情况也同理。

下面 Go 代码下标从 $0$ 开始。

```go
package main
import ("bufio";."fmt";"math/bits";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	var T, n int
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &n)
		sum := make([]int, n+1)
		for i := 1; i <= n; i++ {
			Fscan(in, &sum[i])
			sum[i] ^= sum[i-1]
		}
		leftBits := make([]int, n)
		for i := 0; i < n; i++ {
			rightBits := 0
			for j := n - 1; j >= i; j-- {
				s2 := sum[j+1] ^ sum[i]
				ok := i == 0 && j == n-1 || // 递归入口
					rightBits < 0 || rightBits&s2 != 0 ||  // 能从 f(i,R) 递归到 f(i,j)
					leftBits[j] < 0 || leftBits[j]&s2 != 0 // 能从 f(L,j) 递归到 f(i,j)
				if ok {
					if s2 == 0 {
						leftBits[j] = -1
						rightBits = -1
					} else {
						high := 1 << (bits.Len(uint(s2)) - 1)
						leftBits[j] |= high
						rightBits |= high
					}
				}
				if j == i {
					if ok {
						Print("1")
					} else {
						Print("0")
					}
				}
			}
		}
		Println()
	}
}
```

**时间复杂度**：$\mathcal{O}(n^2)$。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---


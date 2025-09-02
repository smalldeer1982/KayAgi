# [ARC155E] Split and Square

## 题目描述

对于由非负整数组成的集合 $X$，我们定义 $f(X)$ 为：所有可以表示为 $X$ 中两个整数（可以是相同的整数）按位异或（$\mathrm{XOR}$）得到的非负整数组成的集合。例如，当 $X=\lbrace 1,\ 2,\ 4\rbrace$ 时，$f(X)=\lbrace 0,\ 3,\ 5,\ 6\rbrace$。

给定一个包含 $N$ 个小于 $2^M$ 的非负整数组成的集合 $S=\lbrace A_1,\ A_2,\ \dots,\ A_N\rbrace$。

你可以进行如下操作任意次：

- 将 $S$ 分成两个集合 $T_1$ 和 $T_2$（允许 $T_1$ 或 $T_2$ 为空集）。然后，用 $f(T_1)$ 与 $f(T_2)$ 的并集替换 $S$。

请你求出将 $S$ 变为 $\lbrace 0\rbrace$ 所需的最小操作次数。

按位异或（$\mathrm{XOR}$）运算的定义如下：对于非负整数 $A$、$B$，$A\oplus B$ 的二进制表示中，每一位 $2^k$（$k\geq 0$）上的数，如果 $A$ 和 $B$ 在该位上只有一个为 $1$，则该位为 $1$，否则为 $0$。

例如，$3\oplus 5=6$（二进制表示为 $011\oplus 101=110$）。
一般地，$k$ 个非负整数 $p_1,p_2,p_3,\dots,p_k$ 的按位异或定义为 $(\dots((p_1\oplus p_2)\oplus p_3)\oplus\dots\oplus p_k)$，并且可以证明其结果与顺序无关。

## 说明/提示

## 限制条件

- $1\leq N\leq 300$
- $1\leq M\leq 300$
- $0\leq A_i<2^M$
- $A_i\ (1\leq i\leq N)$ 互不相同
- 每个 $A_i$ 都以恰好 $M$ 位的二进制形式给出（如果 $A_i$ 的二进制位数不足 $M$，则会补前导零）
- 所有输入均为整数

## 样例解释 1

第一次操作时，将 $T_1=\lbrace 0,1\rbrace$，$T_2=\lbrace 2,3\rbrace$，则 $f(T_1)=\lbrace 0,1\rbrace$，$f(T_2)=\lbrace 0,1\rbrace$，因此 $S$ 被替换为 $\lbrace 0,1\rbrace$。第二次操作时，将 $T_1=\lbrace 0\rbrace$，$T_2=\lbrace 1\rbrace$，则 $S=\lbrace 0\rbrace$。无法在少于 $2$ 次操作内将 $S$ 变为 $\lbrace 0\rbrace$，所以答案为 $2$。

## 样例解释 2

第一次操作时，将 $T_1=\lbrace 155\rbrace$，$T_2=\lbrace\rbrace$，则 $S$ 变为 $\lbrace 0\rbrace$。操作时允许 $T_1$ 或 $T_2$ 为空集。

## 样例解释 3

初始时 $S=\lbrace 0\rbrace$，无需进行任何操作。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 2
00
01
10
11```

### 输出

```
2```

## 样例 #2

### 输入

```
1 8
10011011```

### 输出

```
1```

## 样例 #3

### 输入

```
1 2
00```

### 输出

```
0```

## 样例 #4

### 输入

```
20 20
10011011111101101111
10100111100001111100
10100111100110001111
10011011100011011111
11001000001110011010
10100111111011000101
11110100001001110010
10011011100010111001
11110100001000011010
01010011101011010011
11110100010000111100
01010011101101101111
10011011100010110111
01101111101110001110
00111100000101111010
01010011101111010100
10011011100010110100
01010011110010010011
10100111111111000001
10100111111000010101```

### 输出

```
10```

# 题解

## 作者：鲤鱼江 (赞：3)

机房有仙人随手切了，诡异。

看到诡异异或，首先考虑一下线性基，记集合 $X$ 的线性基为 $\operatorname{Base}(X)$。

我们先用线性基表示集合 $S$，记其线性基上元素为 $e_{1\dots k}$。

假如 $S$ 被分成了 $T_1$ 和 $T_2$ 两个集合，不难发现若 $T_1$ 包含了 $k$ 个线性基上元素（基底），$\operatorname{Base}(f(T_1))$ 大小一定不小于 $k-1$。

证明：假设包含了 $e_{1\dots k}$，那么拿出 $e_1 \oplus e_2,e_1\oplus e_3,\dots,e_1 \oplus e_k$，显然其任意一个子集异或都不为零。

然后如果 $0\in T_1$，那么 $\operatorname{Base}(f(T_1))=k$，这是显然的。

所以如果 $S$ 中有 $0$，那么每次分出的两个集合最多有一个集合其线性基小于其分到的基底的数量。

然后我们可以证明每次操作都能使 $|\operatorname{Base}(f(T_1))\cup\operatorname{Base}(f(T_2))|=|\operatorname{Base}(S)|-1$。

考虑构造证明，把集合内每个数用线性基上的元素表示出来，所有需要 $e_1$ 的全部扔到 $T_1$ 否则扔到 $T_2$，分析一下发现证毕。

那么 $S$ 没有 $0$ 怎么办呢，也是容易的，只需要证明：

1. $S$ 在进行一次操作后必定含有 $0$，这是容易证明的。
2. 如果 $S$ 不含 $0$，不难发现给 $S$ 中所有数异或上同一个数，$f(S)$ 不变，所以让他们全部异或上 $a_1$ 即可。

所以我们可以直接让集合里边的所有数全部与第一个数异或，求出其线性基大小。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int B=310;
bitset<B>a[B];int n,m;

struct Base{
	bitset<B>v[B];int cnt;
	inline void ins(bitset<B> x){
		for(int i=m;~i;--i){
			if(x[i]){
				if(v[i].any()) x^=v[i];
				else{++cnt;v[i]=x;return ;}
			}
		}
	}
}b;
char x;

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;for(int i=1;i<=n;++i){for(int j=0;j<m;++j){cin>>x;a[i][j]=x-'0';}}
	if(n==1){cout<<(a[1].any()?1:0)<<endl;return 0;}
	for(int i=2;i<=n;++i) b.ins(a[1]^a[i]);
	cout<<b.cnt<<endl;
	return 0;
}
```

---

## 作者：Coward2008 (赞：3)

题意：你有一个初始集合 $S$，然后你每次操作可以把 $S$ 分成两个集合 $T_1$ 和 $T_2$ 。令 $f(T)$ 表示 $\{i \oplus j|i\in T,j\in T \}$ ，则 $S'=f(T_1) \cup f(T_2)$ ,把 $S$ 变为 $S'$ 。

求最小操作数，使得 $S$ 变成 $\{0\}$ 。

题解：

考虑一次操作后线性基大小的变化。令 $S$ 中的数线性基为 $e_1,e_2,…,e_n$ （这些数都出现在 $S$ 中）， $T_1$ 中包含 $e_1,e_2,…,e_m$ ，$T_2$ 中包含 $e_{m+1},e_{m+2},…,e_n$ 。

则 $e_1 \oplus e_2,e_1 \oplus e_3,…,e_1\oplus e_m,e_{m+1}\oplus e_{m+2},…,e_{m+1}\oplus e_n$ ，这些数一定是无法被互相表示的。所以大小至少为 $n-2$ 。

另一方面，我们有这样的构造：把 $S$ 中每个数都表示成，$e_1$ 到 $e_n$ 中的数的一个子集。如果含有 $e_1$ ，则分到 $T_1$ ，否则分到 $T_2$ ,显然此时线性基大小至多为 $n-1$ 。

考虑什么时候大小为 $n-2$ 。通过 $e_1 \oplus e_2,e_1 \oplus e_3,…,e_1\oplus e_m,e_{m+1}\oplus e_{m+2},…,e_{m+1}\oplus e_n$ 这些数，我们可以得到所有满足：

$e_1,e_2,...,e_m$ 中选了偶数个，$e_{m+1},e_{m+2},…,e_n$ 中选了偶数个表示出来的数。我们不能使 $S'$ 含有其他数。

则分进 $T_1$ 的数必须满足：$e_1,e_2,...,e_m$ 中选了奇数个，$e_{m+1},e_{m+2},…,e_n$ 中选了偶数个。$T_2$ 同理。

所以，一个数能分进 $T_1$ 或 $T_2$ ，当且仅当它在 $e_1$ 到 $e_n$ 中选了奇数个。

综上，经过一次操作后线性基大小减少 $2$ ，当且仅当：$S$ 中所有数都能用奇数个线性基里的数表示出来。

但是，经过至少一次操作后的 $S$ 含有 $0$ ,所以一定无法减少 $2$ 。我们只需要判断初始的 $S$ 是否满足条件即可。

复杂度是求线性基的复杂度： $O(nm^2/w)$ ，其中 $m$ 表示 $S$ 中的数值域在 $[0,2^m)$ 之间。

---

## 作者：william555 (赞：2)

看到异或，从线性基的角度考虑。如果 $S$ 包含 $0$，不放令 $0$ 分到 $T1$ 中，那么$T1 \subseteq f(T1)$，且线性基不变。但是我们可以在 $T2$ 上进行操作，如果只将所有包含某个基底的数都放入 $T2$，那么这个基底在 $T2$ 中就会被消去，线性基的大小恰好变小 1。可以发现一次确实不能消掉多个基底，所以如果 $S$ 包含 $0$，那么答案就是线性基的大小。

对于 $S$ 不包含 $0$ 的情况，发现如果在最开始将每个数都异或上一个相同的值，那么一次操作之后的结果不会改变（每两个数异或的时候被抵消了），而进行了一次操作以后 $S$ 必定包含 $0$。所以我们只需要在开始时每一个数都异或上第一个数，第一个数就变成了 $0$，再求出线性基大小即为答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=305;
int n,m;
char s[N];
bitset<N> a[N],b[N];
int cnt,mark[N];
void insert(bitset<N> x){
	for(int i=0;i<m;i++){
		if(x[i]){
			if(!mark[i]){
				b[i]=x;cnt++,mark[i]=1;
				return;
			}else x^=b[i];
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	bool flag=1;
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		for(int j=0;j<m;j++)a[i][j]=s[j]-'0';
		if(a[i].count())flag=0;
	}
	for(int i=1;i<n;i++)a[i]^=a[n];
	for(int i=1;i<n;i++)insert(a[i]);
	if(!flag)cnt=max(cnt,1);
	cout<<cnt<<endl;
	return 0;
}
```

---

## 作者：yizhiming (赞：1)

怎么会有人手写支持位运算的二进制数组啊。。。

[$Link$](https://www.luogu.com.cn/problem/AT_arc155_e)

## 题目大意

给定一个长为 $n$ 的集合 $S$，初始有 $n$ 个元素 $a_i$，定义 $f(T)$ 表示集合 $T$ 中所有数两两异或（可以相同）所能表示出的集合。

定义一次操作时将 $S$ 划分成 $T_1,T_2$ 两集合，可以为空，然后再令 $S = f(T_1) \cup f(T_2)$，问最少需要多少次操作，才能使得 $S$ 中只含有 $0$。

$1\leq n,m\leq 300,a_i <2^m$。

## 题目分析

集合异或相关，考虑线性基。

线性基有哪些性质？原本序列中的数可以由线性基上若干数异或表示出来，这个性质有什么用呢？

我们假设 $a_i$ 由 $a_{p_1},a_{p_2},\dots,a_{p_k}$ 异或出来，考虑将 $a_{p_1}$ 消掉，那么是不是将原序列中所有能够被 $a_{p_1}$ 与若干次其他玩意异或出来表示的数扔到同一个集合，进行一次操作之后就会把原本的 $a_{p_1}$ 的贡献删掉。

但是另外一个集合怎么办呢？我们发现扔到另外一个集合中的信息可能会丢失。

此时不难想到一个性质，若 $0\in T$，$f(T)$ 中实际有价值，或者说需要通过上述方式消掉的数的个数并未改变，因为存在 $0$，所以信息并未丢失，当然相互异或也不会增多。

但是貌似并不是像其他题解那样的包含关系，因为 $f(T)$ 中可能没有 $0$。

所以每次只要保证存在一个 $0$，那么我们就可以将一个关键权值能够更新的全部扔到一个集合中，$0$ 和其余的信息扔到另外一个中，如果每次都有 $0$ 的话，总的操作次数显然时关键权值，即线性基大小次。

现在问题在于如何保证每次有 $0$。

不难发现将 $T$ 中所有元素全都异或上一个数，$f(T)$ 是不会发生改变的，所以如果一开始全都异或上 $a_i$，答案是不会发生改变的，但是求起来更简单，并且，由于异或的两个数可以相同，所以进行一次操作后集合中一定会有 $0$，所以只要保证集合一开始有 $0$，就能再任意时刻保证有 $0$，那么最终答案就是线性基大小。

## Code

维护一下线性基即可，建议写 bitset，而不是像我这样手动重载。。。

样例还是挺良心的，当 $n=1$ 时，$a_1$ 经过异或一定会变成 $0$，但若 $a_1$ 一开始不为 $0$，则需要一次操作，特判一下就好。

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 305;
int n,m;
struct num{
	bool val[N];
	num operator^(const num&a){
		num res;
		for(int i=1;i<=m;i++){
			res.val[i] = val[i]^a.val[i];
		}
		return res;
	}
}sum[N],a[N];
char s[N];
bool flg,vis;bool pla[N];
void ins(num x){
	for(int i=1;i<=m;i++){
		if(x.val[i]){
			if(pla[i]){
				x = x^sum[i];
			}else{
				sum[i] = x;
				pla[i] = 1;
				break;
			}
		}
	}
}
int main(){
	n = read();m = read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		flg = 0;
		for(int j=1;j<=m;j++){
			a[i].val[j] = s[j]-'0';
			flg|=(a[i].val[j]);
		}
		if(!flg){
			vis = 1;
		}
	}
	if(n==1){
		if(vis==1){
			cout<<0<<"\n";
		}else{
			cout<<1<<"\n";
		}
		return 0;
	}
	num res = a[1];
	for(int i=2;i<=n;i++){
		a[i] = a[i]^res;
	}
	for(int i=2;i<=n;i++){
		ins(a[i]);
	}
	int ans = 0;
	for(int i=1;i<=m;i++){
		ans+=(pla[i]);
	}
	cout<<ans<<"\n";
	return 0;
}

```

没有看懂官方题解是啥，但是洛谷的另外几篇确实好懂。

---

## 作者：Leasier (赞：1)

看到两个子集相互异或，考虑线性基。我们可以将 $S$ 中仅含 $0$ 转化为 $S$ 的**线性基大小**为 $0$。

于是我们可以考虑能否每次消掉一些基底。

注意到若 $S$ 中有 $0$，我们可以通过一次操作消掉一个基底——即把含某个基底的元素放到 $T_1$ 中，剩下的（**包括 $0$**）放到 $T_2$ 中，此时刚刚提到的基底会被消掉，又因为 $T_2$ 中有 $0$ 则其基底不变。显然我们不能消掉两个或更多的基底。

那假如 $S$ 中没有 $0$ 呢？我们考虑将 $A$ 中的每个元素异或上 $A_1$，就转化为了上面的情况。在 $n > 1$ 时显然答案不变，因为进行第一次操作时我们异或上的 $A_1$ 会被消掉。

- 感觉是相当高妙的化归法！

于是我们令 $B_i = A_i \operatorname{xor} A_1$，求出 $B$ 的线性基个数即可。时间复杂度为 $O(nm)$。

注意特判 $n = 1$。

代码：
```cpp
#include <iostream>
#include <bitset>

using namespace std;

bool vis[307];
bitset<307> bs1[307], bs2[307];

inline bool insert(bitset<307> bs, int n){
	for (int i = n - 1; i >= 0; i--){
		if (bs[i]){
			if (!vis[i]){
				vis[i] = true;
				bs2[i] = bs;
				return true;
			} else {
				bs ^= bs2[i];
			}
		}
	}
	return false;
}

int main(){
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		cin >> bs1[i];
	}
	if (n == 1){
		if (bs1[1].any()){
			cout << 1;
		} else {
			cout << 0;
		}
		return 0;
	}
	int ans = 0;
	for (int i = 2; i <= n; i++){
		if (insert(bs1[i] ^ bs1[1], m)) ans++;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc155_e)

**题目大意**

> 设 $S$ 是由 $n$ 个 $m$ 位二进制数组成的集合，定义 $f(S)$ 表示 $\{i\oplus j\mid i,j\in S\}$。
>
> 一次操作可以选定 $T\subseteq S$，使得 $S\gets f(T)\cup f(S\setminus T)$，求使得 $S=\{0\}$ 的最小操作次数。
>
> 数据范围：$n,m\le 300$。

**思路分析**

这种问题先考虑 $S$ 的线性基 $e_1\sim e_k$，设最终 $e_1\sim e_s\in T,e_{s+1}\sim e_k\in S\setminus T$。

那么我们知道 $f(T)$ 包含 $e_1\oplus e_2\sim e_1\oplus e_s$，并且他们之间线性无关（任取一个子集显然异或和不为 $0$）。

那么 $f(T)$ 线性基大小 $\ge s-1$，同理 $f(S\setminus T)$ 线性基大小 $\ge k-s-1$，因此线性基大小每次至多 $-2$。

然后我们分析每次线性基大小减小的下界，假如我们只想让新的 $S$ 线性基大小减一，这是简单的，把 $S$ 里的数唯一表示成 $e_1\sim e_k$ 的异或和，表示方式中包含 $e_1$ 的全部放进 $T$。

那么容易证明 $f(T)\cup f(S)$ 的张成空间维度 $\le k-1$（可以用 $e_2\sim e_k$ 表示所有数）。

那么这样操作每次线性基大小至少 $-1$。

再进一步分析：注意到操作一次之后 $0\in S$，且以后该性质一直成立，不妨假设在操作的时候 $0,e_1\sim e_k\in T$，那么 $f(T)$ 依然满足这个条件，那么 $f(T)$ 的线性基大小 $\ge k$.

那么第二次操作以及之后每次操作不可能令 $f(T),f(S\setminus T)$ 的线性基大小同时 $-1$，因此每一步都只可能令线性基大小 $-1$。

那么我们只要特殊处理第一次操作，我们又发现令 $S$ 的每个数异或上 $S_0$（某个元素）显然不会影响 $f(T),f(S\setminus T)$ 的值，那么这样我们就又转化成了 $0\in S$ 的情况。

因此我们只要求出这个新集合的线性基大小即可，`std::bitset` 优化一下。

时间复杂度 $\mathcal O\left(\dfrac{nm^2}\omega\right)$。

**代码呈现**

``` cpp
#include<bits/stdc++.h>
using namespace std;
typedef bitset<305> bi;
int n,m;
bi a[305],x[305];
bool vis[305];
bool ins(bi v) {
	for(int i=m-1;~i;--i) if(v[i]) {
		if(!vis[i]) return x[i]=v,vis[i]=true;
		else v^=x[i];
	}
	return false;
} 
signed main() {
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i];
	if(n==1) return cout<<(a[1].any()?1:0)<<"\n",0; 
	int ans=0;
	for(int i=2;i<=n;++i) ans+=ins(a[i]^=a[1]);
	cout<<ans<<"\n";
	return 0;
} 
```

---


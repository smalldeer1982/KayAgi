# [ABC025D] 25個の整数

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc025/tasks/abc025_d

高橋君は縦 $ 5 $ マス、横 $ 5 $ マスの盤面に $ 1 $ から $ 25 $ までの整数を $ 1 $ つずつ書き込もうとしています。

高橋君は以下の条件をすべて満たすように整数を配置しようと考えています。

- 整数は各マスに $ 1 $ つずつ割り当てる。
- 縦または横に連続する $ 3 $ つの整数をどのように取り出しても、それらは昇順または降順になっていない。すなわち、上から $ i\ (1\ ≦\ i\ ≦\ 5) $ 番目、左から $ j\ (1\ ≦\ j\ ≦\ 5) $ 番目のマスに書かれた整数を $ n_{i,j} $ としたとき、以下の $ 2 $ 条件が成立する。
- $ n_{i,j}\ ＜\ n_{i+1,j}\ ＜\ n_{i+2,j} $ あるいは $ n_{i,j}\ ＞\ n_{i+1,j}\ ＞\ n_{i+2,j} $ を満たす整数組 $ (i,j)\ (1\ ≦\ i\ ≦\ 3,\ 1\ ≦\ j\ ≦\ 5) $ が存在しない。
- $ n_{i,j}\ ＜\ n_{i,j+1}\ ＜\ n_{i,j+2} $ あるいは $ n_{i,j}\ ＞\ n_{i,j+1}\ ＞\ n_{i,j+2} $ を満たす整数組 $ (i,j)\ (1\ ≦\ i\ ≦\ 5,\ 1\ ≦\ j\ ≦\ 3) $ が存在しない。


すでにいくつかのマスについては、どの整数を書き込むかは決まっています。あなたの課題は、上記の条件を満たすような残りの整数の配置の総数を計算することです。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- データセット $ 1 $ において、すべての入力には、$ x_{i,j}\ ≠\ 0 $ を満たす整数組 $ (i,j)\ (1\ ≦\ i\ ≦\ 5,\ 1\ ≦\ j\ ≦\ 5) $ が $ 17 $ 個以上存在する。データセット $ 1 $ に正解した場合は、$ 30 $ 点が与えられる。
- 追加制約のないデータセット $ 2 $ に正解した場合は、上記とは別に $ 70 $ 点が与えられる。

### Sample Explanation 1

\- まだ書かれていない整数は $ 6,\ 11,\ 12,\ 13,\ 14,\ 24 $ の $ 6 $ つです。以下の $ 2 $ 通りが、条件を満たす配置です。 14121527131116122202541963239181017245218 14131527121116122202541963239181017245218

### Sample Explanation 2

\- どのように残りを書いても条件を満たします。

### Sample Explanation 3

\- どのように置いても条件を満たさない場合があります。

### Sample Explanation 4

\- すでにすべての整数の配置が決まっている場合もあります。

## 样例 #1

### 输入

```
0 0 15 2 7
0 0 16 1 22
20 25 4 19 0
3 23 9 18 10
17 0 5 21 8```

### 输出

```
2```

## 样例 #2

### 输入

```
10 14 13 15 11
16 0 17 0 18
0 19 0 20 9
21 12 22 0 23
0 24 0 25 0```

### 输出

```
40320```

## 样例 #3

### 输入

```
1 2 3 4 5
6 7 8 9 10
11 12 13 14 15
16 17 18 19 20
0 0 0 0 0```

### 输出

```
0```

## 样例 #4

### 输入

```
1 25 2 24 3
23 4 22 5 21
6 20 7 19 8
18 9 17 10 16
11 15 12 14 13```

### 输出

```
1```

# 题解

## 作者：zac2010 (赞：11)

考虑从小到大加入每种权值，同时维护一个状压数组 $f$。

具体的，我们对于在输入矩形中出现过的数，直接转移；否则枚举当前的数放在哪一位，判断合法性之后转移就行了。

判断合法其实有一种比较简便的方法，每次加入一个数时，如果他在某个三元组的中间位置，且左右的点恰好填了一个，那么就证明这个三元组是单调的，当前方案不合法。每个三元组都会在加入中间元素时被判断一次。

这样做的复杂度保证在于：矩阵中至少已经填了 $5$ 个数。分析一下不难发现它可以做到 $O(20\times 2^{20})$。我的代码中采用了一种时间略高，但实现简便的方法。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); ++i)
#define FR(i, a, b) for(int i = (a); i >= (b); --i)
using namespace std;
const int p = 1e9 + 7;
int x, id[27], f[1 << 25];
bool check(int s, int i){
	if(i % 5 && i % 5 < 4 && (s >> i - 1 & 1 ^ s >> i + 1 & 1)) return 0;
	return !(i / 5 && i / 5 < 4 && (s >> i - 5 & 1 ^ s >> i + 5 & 1));
}
int main(){
	fill(id, id + 26, -1), f[0] = 1;
	FL(i, 0, 24) scanf("%d", &x), x? (id[x] = i) : 0;
	FL(s, 1, (1 << 25) - 1){
		int b = __builtin_popcount(s);
		if(~id[b]){if(check(s, id[b]))
			(f[s] += f[s ^ (1 << id[b])]) %= p;
		}
		else FL(i, 0, 24) if(check(s, i))
			(f[s] += f[s ^ (1 << i)]) %= p;
	}
	printf("%d\n", f[(1 << 25) - 1]);
	return 0;
}
```


---

## 作者：rui_er (赞：8)

\*3006。

数据范围明示状压 DP，但是涉及到填数不好直接状压，因为我们对每个格子只能记录一个二进制位，不可能知道每个数都在什么位置。

不妨换个思路，不难想到一个二进制位可以用来记录这个位置是否已经填数，只需要利用上这个信息。注意到我们不关心具体填的数是多少，只关心偏序关系，因此可以从小到大填数。

从小到大填数时，不存在长度为 $3$ 的单调数列等价于：填的位置左右填数状态相同，且上下填数状态相同（填数状态指是否已经填数）。可以根据这一点判断填数是否合法，并完成转移。

时间复杂度 $\mathcal O(2^nn)$，其中 $n=25$。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
	uniform_int_distribution<int> dist(L, R);
	return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const int mod = 1e9+7;

int a[25], pos[25], dp[1<<25];

void calc(int S, int k) {
	int x = k / 5, y = k % 5;
	if(0 < x && x < 4 && ((S >> (k - 5)) & 1) != ((S >> (k + 5)) & 1)) return;
	if(0 < y && y < 4 && ((S >> (k - 1)) & 1) != ((S >> (k + 1)) & 1)) return;
	dp[S] = (dp[S] + dp[S^(1<<k)]) % mod;
}

int main() {
	memset(pos, -1, sizeof(pos));
	rep(i, 0, 24) {
		scanf("%d", &a[i]);
		if(a[i]) pos[a[i]-1] = i;
	}
	dp[0] = 1;
	rep(S, 1, (1<<25)-1) {
		int u = __builtin_popcount(S) - 1;
		if(pos[u] >= 0) calc(S, pos[u]);
		else rep(i, 0, 24) if((S >> i) & 1) calc(S, i);
	}
	printf("%d\n", dp[(1<<25)-1]);
	return 0;
}
```

---

## 作者：cosf (赞：5)

## [ABC025D](https://www.luogu.com.cn/problem/AT_abc025_d) [25 个整数](https://atcoder.jp/contests/abc025/tasks/abc025_d)

### 思路

看完题目，首先想到的可能是暴力搜索。像 [数独](https://www.luogu.com.cn/problem/P1784) 这样的题目，能想到暴力是很正常的。

但是，**这是道黑题**，用那种低级的方法一定过不了。

所以，我们可以用 **状压 dp**。

怎么状压？一般来说，有两种思路。第一种是记录哪些格子被填了，另一种是记录哪些数字被填了。

对于第二种，我们发现这样记录的信息不够（因为格子与其上下左右的格子都有关系），或者说难转移。所以应该使用第一种。

因为第一种没有记录具体填什么，所以填数要有顺序，例如从小到大或从大到小。事实上，两种都可以，所以这里从从小到大的方面来考虑。

这意味着，假如对于一个状态 $i$，它有 $p_i$ 个位置为 $1$，那么当前填的数就必当是 $p_i$（这 $p_i$ 个数是 $1, \dots, p_i$）。

### 如何转移？

对于每一个状态 $i(1 \le i \lt 2^{25})$，设 $i$ 在二进制中有 $p_i$ 个 $1$。

如果 $p_i$ 已经被事先填好了，位置是 $mp_i$（即输入时填了），那么 $dp_i=dp_{(i\oplus2^{mp_i})}$（假设可行）。这是因为，$i\oplus 2^{mp_i}$ 正好是除了 $p_i$ 没填的状态。**但是**，有一个问题：如果 $i$ 中的第 $mp_i$ 为 $0$ 会怎么样呢（即不填这个格子）？显然，此时 $i\oplus 2^{mp_i} \gt i$，处理 $dp_i$ 时 $dp_{(i\oplus 2^{mp_i})}$ 还是 $0$ 呢。

如果 $p_i$ 没有被事先填好，则我们可以去枚举它的位置，并且对于所有可能的位置 $m$，做 $dp_i+dp_{(i\oplus 2^m)}\to dp_i$（假设可行）。

### 可行性判断？

我们讨论一下横向（左右）的判断（纵向同理）。

如果一个格子在边缘，那么它必当不会成为一个单调数列的中间。所以可以不讨论。

如果它在中间，则我们可以发现，如果它左边和右边只填了一个，那么填了的那个格子上的数会小于它自己的数，而没填的将来会填个比它大的，所以这种情况是不行的。如果它左边和右边要么都填了，要么都没填，显然它不会是单调的。

复杂度：$O(2^{n}n)$，此处 $n=25$，时间复杂度是正确的。常数大也没所谓，因为时限为 `5s`。

### 一些实现方法

本段可以跳过并直接看代码。

 - `stl` 里面有一个函数，叫做 `__builtin_popcount`（`__libcpp_popcount` 是间接调用它的函数，但用不了，很奇怪），可以计算一个整数在二进制内 $1$ 的个数。
 - $2^{25}=33554432, 2^{25}\times 4 \mathtt{bytes} < 2^{28} \mathtt{bytes}=256\mathtt{MB}$，可以直接存 $dp$ 数组。

### [参考代码](https://www.luogu.com.cn/record/108441168)

```cpp
#define pop(x) __builtin_popcount(x)
#define MOD (1000000007)

int dp[1 << 25]; // 存数组
int mp[30]; // 存输入地图

void add(int i, int p) // i 为当前状态，p 为当前填的数的位置
{
    int x = p % 5; // 横向判断
    int y = p / 5; // 纵向判断
    if (x && x < 4 && (i >> (p - 1) & 1 ^ i >> (p + 1) & 1)) // (p - 1) 即它左边的格子，(p + 1) 即它右边的。
    {
        return;
    }
    if (y && y < 4 && (i >> (p - 5) & 1 ^ i >> (p + 5) & 1)) // (p - 5) 为上，(p + 5) 为下。
    {
        return;
    }
    dp[i] = (dp[i] + dp[i ^ (1 << p)]) % MOD; // 记得模数
}

int main()
{
    for (int i = 1; i <= 25; i++)
    {
        int c;
        cin >> c;
        mp[c] = i; // 如果 c 为 0 也没所谓。
    }
    dp[0] = 1; // 初始化
    for (int i = 1; i < 1 << 25; i++) // dp
    {
        int p = mp[pop(i)];
        if (p)
        {
            add(i, p - 1); // 只能填这个位置。注意要 -1!!
        }
        else
        {
            for (int j = 0; j < 25; j++) // 枚举
            {
                if (i & (1 << j))
                {
                    add(i, j);
                }
            }
        }
    }
    cout << dp[(1 << 25) - 1] << endl; // 结果。也要 -1!!
    return 0;
}
```

---

`update:` 参考代码有点问题，却因语言特性卡过去了。现在的代码没问题了。


---

## 作者：樱雪喵 (赞：3)

看数据范围 $25$ 个格子 $20$ 个空位，确定是状压。  
考虑从小到大填数的过程，设 $f_i$ 表示点集 $i$ 中的位置已经被填过了数，其余位置还没有填。因为我们钦定了从小往大填，状态 $i$ 下最后一个填的数就是 $i$ 中 $1$ 的个数。  
那么填这个数的限制条件就是它不会在横向或竖向上形成单调数列。  
以横向为例，填在位置 $x$ 不合法当且仅当 $x$ 左右恰好已经有一个位置被填了。因为已经被填那个位置肯定比当前数小，没被填那个位置最后填的东西一定比当前数大。  
转移的时候判断一下合法性，时间复杂度为 $O(n 2^n)$，取决于实现方式 $n$ 取 $20$ 或 $25$。 

```cpp
const int N=(1<<25)+5,M=30;
const int mod=1e9+7;
int n=5,bel[M];
int f[N],mp[M];
il void add(int &x,int y) {x+=y;if(x>=mod) x-=mod;}
il bool check1(int x)
{
    if(x-n>=0&&x+n<n*n)
    {
        int u=mp[x-n],d=mp[x+n];
        if(u&&d&&(u<mp[x]&&mp[x]<d||u>mp[x]&&mp[x]>d)) return 0;
    }
    if(x%n>0&&x%n<n-1)
    {
        int l=mp[x-1],r=mp[x+1];
        if(l&&r&&(l<mp[x]&&mp[x]<r||l>mp[x]&&mp[x]>r)) return 0;
    }
    return 1;
}
il bool check2(int x,int s)
{
    int u=0,d=0,l=0,r=0;
    if(x-n>=0&&x+n<n*n) u=s>>x-n&1,d=s>>x+n&1;
    if(x%n>0&&x%n<n-1) l=s>>x-1&1,r=s>>x+1&1; 
    return !(u^d||l^r);
}
int main()
{
    memset(bel,-1,sizeof(bel));
    for(int i=0;i<n*n;i++) mp[i]=read(),bel[mp[i]]=i;
    for(int i=0;i<n*n;i++) if(!check1(i)) {printf("0\n");return 0;} 
    f[0]=1;
    for(int i=1;i<(1<<n*n);i++)
    {
        int cnt=0;
        for(int j=0;j<n*n;j++) if(i>>j&1) cnt++;
        if(bel[cnt]!=-1) 
        {
            if(check2(bel[cnt],i)) f[i]=f[i^1<<bel[cnt]];
            continue;
        }
        for(int j=0;j<n*n;j++) if(i>>j&1)
        {
            if(!mp[j]&&check2(j,i)) add(f[i],f[i^(1<<j)]);
        }
    }
    printf("%d\n",f[(1<<n*n)-1]);
    return 0;
}
```

---

## 作者：liuenyin (赞：2)

### [ABC025D](https://www.luogu.com.cn/problem/AT_abc025_d)

### 分析:

（部分思路来自 [这篇题解](https://www.luogu.com.cn/blog/cosf/A40-ABC025D) ，在此感谢）

首先想到暴力搜索（类似数独问题），但是这种方法的问题就在于时间复杂度过高（约 $O(n!)$），显然无法通过。

再看题目，$5 \times 5$ 的网格和 $5s$ 的时限，可以想到状态压缩 DP。

因为状压只能表示出每个数填了没填，因此 DP 的时候需要有顺序，这里采用从小到大填。

对于状态 $S$，$S$ 在二进制中 $1$ 的个数即为当前要填的数（记为 $t$），若 $t$ 预先被填了（设位置为 $p_t$），则 $\large{ f_S\gets f_{(i \oplus 2^{p_t})}}$，即除了 $t$ 没有填的状态。否则，枚举 $t$ 的位置，并且对于可行的位置 $p$，有 $\large f_i \gets f_i +f_{(i \oplus 2^p)}$。边界条件 $f_0 =1$。

对于判断可行性，横向和纵向的差不多，因此这里只讨论横向的。如果一个格子在边缘，那么必然不会成为一个单调数列的中间项，可以不讨论。否则，如果左面或者右面只填了一个数（由于 DP 顺序，必然比当前数小），另外一面必然比当前数大，因此不可以。如果两面都填了，那么也可以填当前数。

时间复杂度 $O(n2^n)$，空间复杂度 $O(2^n)$，其中 $n=25$，均可通过。

### 代码

[原站记录](https://atcoder.jp/contests/abc025/submissions/45432123)

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=25;
const int M=1e9+7;
int c[N+5];//网格,c[i]表示数字i填的位置 
int f[(1<<N)];//dp 
//f[S] 中 S二进制从右往左第i位表示数字i是否填写过 

inline void add(int S,int place){
	if(place%5>0 and place%5<4 and ((S>>(place-1)&1)^(S>>(place+1)&1))){
		//在中间              两边只填了一个数字 
		return;
	} 
	if(place/5>0 and place/5<4 and ((S>>(place-5)&1)^(S>>(place+5)&1))){
		return;
	}
	f[S]=(f[S]+f[S^(1<<place)])%M;
	//cout<<f[S]<<" "<<S<<" "<<place<<endl;
}

int main(){
	for(int i=1;i<=25;i++){
		int tmp;cin>>tmp;
		c[tmp]=i;
	}
	int end=(1<<N);
	f[0]=1;
	for(int i=1;i<end;i++){
		int plc=c[__builtin_popcount(i)];
		//当前应该填的数字的位置 
		if(plc!=0){
			//已经填过了，只能填这个位置 
			add(i,plc-1);
		} 
		else{
			for(int j=1;j<=25;j++){
				if(i&(1<<(j-1))){
					add(i,j-1);
				}
			}
		}
	//	cout<<f[i]<<" ";
	} 
	cout<<f[end-1]<<endl; //记得换行!!!
	return 0;
}

```

---

## 作者：james1BadCreeper (赞：2)

想要填一个数需要判断上下左右的数，不太好搞。让填数变得有一点规律：从小到大开始填数，这样判断是否合法只需要检查其上下左右四个位置是否填了数即可（要么左右都填了数，要么都没填）。

枚举已经填了的位置，将其状压为 $S$。当前要填的数是 $S$ 中 $1$ 的个数。如果这个数已经被填了，那么只能将这个位置填进去，否则可以在 $S$ 中任选一个位置填。

理论时间复杂度 $O(n2^n)$，其保证了已经填了至少 $5$ 个数，所以可以通过。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int P = 1000000007; 

int w[30];
int f[1 << 25]; 
inline void add(int x, int y) { 
	if (0 < y % 5 && y % 5 < 4 && (x >> y - 1 & 1 ^ x >> y + 1 & 1)) return; 
	if (4 < y && y < 20 && (x >> y - 5 & 1 ^ x >> y + 5 & 1)) return; 
	f[x] = (f[x] + f[1 << y ^ x]) % P; 
}

int main(void) {
	f[0] = 1; 
	for (int i = 0, x; i < 25; ++i) scanf("%d", &x), w[x] = i + 1;
	for (int i = 1; i < 1 << 25; ++i) { // 填写所有位置 i，按照填的个数进行 DP（从小到大填数） 
		int p = w[__builtin_popcount(i)]; 
		if (p) add(i, p - 1); 
		else {
			for (int j = 0; j < 25; ++j) 
				if (i >> j & 1) add(i, j); 
		}
	}
	printf("%d\n", f[(1 << 25) - 1]); 
	return 0;
}
```

---

## 作者：Gmt丶FFF (赞：2)

数据范围可以看出能状压 dp。

如果压缩选择的数，感觉会很难处理偏序关系，考虑压缩选了的位置，然后从小到大选，如果在选这个数前，选了左边的数，但没选右边的数，很明显后面选右边的数肯定会比这个数大，然后就成了一个偏序关系，所以可以得到结论。

这个位置可以选，当且仅当：

没有只选了上，下，或只选了左，右中的一个数（边缘的数特殊考虑，很明显选边缘的数不会受到偏序限制），简单来说，上下两个数要么都选，要么都不选，左右同理。

然后状态压缩 dp 即可，dp 方程很简单，就不再陈述。

对于一个数字的二进制下的 $1$ 的个数，可以用 __builtin_popcount 快速计算，效率十分高。

注意空间优化，只能开一个 int 类型的 dp 数组，还有注意最后输出要换行。

时间复杂度：$O(2^n\times n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=25;
const int mod=1e9+7;
int a[N],p[N],f[1<<N];
inline bool check(int p,int k)
{
	int t1=k-1,t2=k+1,t3=k-5,t4=k+5;
	if(k>4&&k<20&&((1&(p>>t3))^(1&(p>>t4))))return false;
//	if(p==5)cout<<((1<<t1)&p)<<" "<<((1<<t2)&p)<<endl;
	if(k%5!=0&&k%5!=4&&((1&(p>>t1))^(1&(p>>t2))))return false;
	return true;
}
int main()
{
	for(int i=0;i<25;i++)p[i]=-1;
	for(int i=0;i<25;i++)
	{
		scanf("%d",&a[i]);
		if(a[i])p[a[i]-1]=i;
	}
	f[0]=1;
	for(int j=0;j<(1<<25)-1;j++)
	{
		int i=__builtin_popcount(j);
		int st=0,ed=24;
		if(p[i]!=-1)st=ed=p[i];
//		cout<<s[t[j]]<<" "<<st<<" "<<ed<<" !\n";
		for(int k=st;k<=ed;k++)
		{
			if((1<<k)&j)continue;
			if(!check(j,k))continue;
//			if(t[j]==5)cout<<t[j]<<" "<<k<<" "<<(now|(1<<k))<<" "<<endl; 
			f[j|(1<<k)]+=f[j];
			f[j|(1<<k)]%=mod;
			
		}
//		if(t[j]==5)cout<<t[j]<<" "<<f[t[j]]<<endl<<endl;
//		if(j==16)return 0;
	}
	printf("%d\n",f[(1<<25)-1]);
	return 0;
}
/*
1 3 2 5 4
11 13 12 15 14
6 8 7 10 9
21 23 22 25 24
16 18 17 20 19
*/
```


---

## 作者：kkkfc0114514 (赞：0)

考虑状压。

先把二维平面映射到一个一维数组，即把一个 $5 \times 5$ 的二维平面映射到一个长 $25$ 位的一维数组方便状压。

然后，设 $f_S$ 为状压状态为 $S$ 的方案总数。之后从小到大填数。对于已经被 hhoppitree 填好的数直接转移，否则，枚举每一个没有被填写位置，如果这个位置的左边和右边同时被填数或没有同时被填数，即 $i + 1$ 位和 $i - 1$ 位同时被填数或没有同时被填数，上面和下面同时被填数或没有同时被填数，即 $ i + 5$ 位和 $i - 5$ 位同时被填数或没有同时被填数，则这个位置是合法的，可以从这个位置转移。

具体细节看代码，有注释。

# code

```cpp
#include <bits/stdc++.h>
namespace SXL {
    constexpr int MOD = 1e9 + 7;
    int f[1 << 25];
    int x,idx[30];
    int check(int s,int i) { // 检查函数
        if(i % 5 != 0 && i % 5 != 4) { // 判断是否处在边界
            if(((s >> (i - 1)) & 1) ^ ((s >> (i + 1)) & 1)) { // 判断两边是否同时有数或同时没有数
                return 0;
            }
        }
        if(i / 5 != 0 && i / 5 != 4) { // 判断是否处在边界
            if(((s >> (i - 5)) & 1) ^ ((s >> (i + 5)) & 1)) { // 判断上下是否同时有数或同时没有数
                return 0;
            }
        }
        return 1;
    }
    void main() {
        memset(idx,-1,sizeof(idx));
        f[0] = 1;
        for(int i = 0;i < 25;i++) {
            scanf("%d",&x);
            if(x) idx[x] = i;
        }
        for(int s = 1;s < (1 << 25);s++) {
            int b = __builtin_popcount(s); // __builtin_popcount：统计s的二进制中 '1' 的个数
            if(~idx[b]) { // 如果这个数已经被hhoppitree填写了
                if(((s >> idx[b]) & 1) && check(s,idx[b])) {
                    f[s] += f[s ^ (1 << idx[b])]; // 直接转移
                    f[s] %= MOD;
                }
            } else { // 否则
                for(int i = 0;i < 25;i++) { // 枚举这个数填写的位置
                    if(((s >> i) & 1) && check(s,i)) {
                        f[s] += f[s ^ (1 << i)];
                        f[s] %= MOD;
                    }
                }
            }
        }
        printf("%d\n",f[(1 << 25) - 1]);
    }
}
int main() {
    SXL::main();
    return 0;
}
```

---

## 作者：z_yq (赞：0)

# 写在前面
作业题，但是差点看成搜索了，这种题目就是难想算法，其他都简单。
# 做法
这道题目如果搜索会变成卡评测……所以只能想别的做法，因为数据范围比较小，所以我们可以状压。\
状压的做法很简单，我们从小到大去放到这个五宫格里面。这样就会更好判断这个东西是否合法。例如：如果这个数左边的两个格子都放了数，那么这个格子就是非法的，所以，如果这个格子上下左右的两边都是放了数的，那么就是非法的，所以我们可以很快的判断是否合法，其他的和普通装压没有什么区别，别的题解也讲的很清楚了。
# Code
```cpp
#include<bits/stdc++.h>
#define ll int
using namespace std;
const ll Mod=1e9+7;
ll a[26],n,vis[26],dp[1<<25];
inline void check(ll x,ll y)
{
    if(y%5!=4 && y%5!=0 && ((x&(1<<y-1))!=0)^((x&(1<<y+1))!=0)) return;
    if(y/5!=4 && y/5!=0 && ((x&(1<<y-5))!=0)^((x&(1<<y+5))!=0)) return;
    dp[x]+=dp[x^(1<<y)];dp[x]%=Mod;
}
int main()
{
    for(int i=0;i<25;i++) vis[i]=-1;
    for(int i=0;i<25;i++) 
    {
        cin>>a[i];
        if(a[i])
            vis[a[i]-1]=i;
    }
    dp[0]=1;
    for(int i=1;i<(1<<25);i++)
    {
        ll tmp=__builtin_popcount(i)-1;
        if(vis[tmp]!=-1){if((i&(1<<vis[tmp]))!=0) check(i,vis[tmp]);}
        else for(int j=0;j<25;j++) if((i&(1<<j))!=0 && a[j]==0) check(i,j);
    }
    cout<<dp[(1<<25)-1]%Mod<<endl;
    return 0;
}

```

---

## 作者：Ming_dao (赞：0)

**题解**

第一眼是一个搜索，但是显然会超时。

发现 $x$ 只有 $25$ 想到了状压。

考虑状压的顺序和转移。

对于题目形如 $a \le b\le c$ 和 $c \le b\le a$ 不难想到通过从小到大的插入顺序来插入数就可以简单判断。

既然想到了插入数，显然可以枚举所有的可能分布，用  $O(1)$ 直接判断当前状态是否合法。

**深入理解**

为什么我们只需判断单次操作是否合法？显然，插入这个点合法的情况，不一定是全局的合法情况。但是，所有限制条件的交集情况一定是合法的，这个交集也就是我们要找的答案。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long

int f[1<<25];
int vis[26];

const int mod=1e9+7;

void add(int i,int p){
	int x=p%5;
	int y=p/5;
	if(0<x&&x<4&&((i>>(p-1))&1)!=((i>>(p+1))&1))return;
	if(0<y&&y<4&&((i>>(p-5))&1)!=((i>>(p+5))&1))return;
	(f[i]+=f[i^(1<<p)])%=mod;
}

int main() {
	memset(vis, -1, sizeof(vis));
	for(int i=0;i<=24;i++) {
		int a;
		scanf("%d", &a);
		if(a) vis[a-1] = i;
	}
	f[0] = 1;
	for(int S=1;S<=(1<<25)-1;S++) {
		int u = __builtin_popcount(S) - 1;
		if(vis[u] >= 0) add(S, vis[u]);
		else for(int i=0;i<=24;i++) if((S >> i) & 1) add(S, i);
	}
	printf("%d\n", f[(1<<25)-1]);
	return 0;
}
```

---

## 作者：nynkqh_yzp (赞：0)

这题最多只有 $25$ 个数，所以肯定可以用状压解决，但是状压只能判断之前有没有放数，那么我们就可以从小到大依次放数，就只需要判断有没有连续三个位置都选了的情况。

时间复杂度 $O(2^n \times n)$。
```
#include <bits/stdc++.h>
using namespace std;
int f[1<<25],s[26],mo=1000000007,v[26];
void jr(int a,int b){
	if(b%5!=0&&b%5!=4&&((a&(1<<b-1))!=0)^((a&(1<<b+1))!=0))
		return;
	if(b/5!=0&&b/5!=4&&((a&(1<<b-5))!=0)^((a&(1<<b+5))!=0))
		return;
	f[a]=(f[a]+f[a^(1<<b)])%mo;
}
int main(){
	for(int i=0;i<25;i++)
		v[i]=-1;
	for(int i=0;i<25;i++){
		scanf("%d",&s[i]);
		if(s[i]!=0)
			v[s[i]-1]=i;
	}
	f[0]=1;
	for(int i=1;i<(1<<25);i++){
		int an=0,j=i;
		while(j){
			an+=(j&1);
			j=j>>1;
		}
		an--;
		if(v[an]!=-1){
			if((i&(1<<v[an]))!=0)
				jr(i,v[an]);
		}
		else{
			for(int k=0;k<25;k++)
				if((i&(1<<k))!=0&&s[k]==0)
					jr(i,k);
		}
	}
	printf("%d\n",f[(1<<25)-1]);
	return 0;
}
```


---


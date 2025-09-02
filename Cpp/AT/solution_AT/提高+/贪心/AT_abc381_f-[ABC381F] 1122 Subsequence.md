# [ABC381F] 1122 Subsequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc381/tasks/abc381_f

正整数からなる（空でも良い）数列 $ X=(X_1,X_2,\ldots) $ が以下の $ 3 $ つの条件をすべてみたすとき、かつそのときに限り、$ X $ を **1122 数列** と呼びます。  
（1122 数列の定義はD問題と共通です。）

- $ \lvert\ X\ \rvert $ は偶数である。ここで、$ \lvert\ X\ \rvert $ は $ X $ の長さを表す。
- $ 1\leq\ i\leq\ \frac{\lvert\ X\ \rvert}{2} $ をみたす整数 $ i $ について、$ X_{2i-1} $ と $ X_{2i} $ は等しい。
- 各正整数は $ X $ に現れないか、ちょうど $ 2 $ 回現れるかのどちらかである。すなわち、$ X $ に含まれる正整数は $ X $ にちょうど $ 2 $ 回ずつ登場する。

正整数からなる長さ $ N $ の数列 $ A=(A_1,A_2,\ldots,A_N) $ が与えられるので、$ A $ の **（連続でなくても良い）部分列** であって、1122 数列であるようなもののうち最長のものの長さを出力してください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ \leq\ 20 $
- 入力はすべて整数

### Sample Explanation 1

例えば $ A $ の部分列として、$ 1,4,5,6 $ 項目をとると $ (1,1,2,2) $ となりますが、これは長さが $ 4 $ の 1122 数列となっています。 これより長い部分列であって、1122 数列の条件をみたすようなものは存在しないため、$ 4 $ を出力します。

## 样例 #1

### 输入

```
7
1 3 3 1 2 2 1```

### 输出

```
4```

## 样例 #2

### 输入

```
1
20```

### 输出

```
0```

# 题解

## 作者：__Allen_123__ (赞：113)

你是一名因水平原因而遗憾退役的 OIer。退役之际，你正努力寻找和拼接着你在 OI 生涯中的回忆。

> 按顺序，你有 $n$ 片关于 OI 的记忆，每一片用一个数字 $a_i(1\le a_i\le 20)$ 代表，数字相同代表记忆内容相近。
>
> 你想把其中最具有代表性的记忆拼接在一起，可以不在原序列中连续。具体地，你要求出一个 $a$ 的可不连续的子序列，其中两片相近的记忆（$a_i=a_j$）需要在子序列中连续。同时，你不想让过多重复的记忆进入，所以每一片记忆的内容只会出现 $0$ 次或 $2$ 次。
>
> 请求出你所获得的回忆子序列的最长长度。

你马上想到，可以使用状压求出分别是否选择了 $20$ 种内容。记 $S$ 为当前状态的二进制值，从低到高第 $i$ 位为 $1$ 代表已经被选择，为 $0$ 代表未被选择。

你考虑从小到大枚举 $S$，并记录能达到这种状态的最小的下标 $f_i$（如果无法达到，$f_i=\infty$）。你很显然地发现，对于一个状态 $S$，通过枚举往后延展回忆的内容编号（$1\sim 20$）来进行转移即可高效地完成。

具体地，设当前状态为 $S$（$f_S\ne \infty$），被延展的回忆内容编号为 $x$（$S$ 开始时从低到高第 $i$ 位不能为 $1$），则新状态的编号为 $S'=S+2^{x-1}$。$S$ 能够向 $S'$ 转移的充要条件，即是在 $f_S$ 之后，仍然有两个下标 $j,k$ 满足 $a_j=a_k=a_{f_i}$，且 $k<f_{S'}$，则此时即可让 $f_{S'}=k$。

你也发现暴力地求出 $j,k$ 是低效的，于是你预处理了一个 $nxt_{i,j}$，代表从下标 $i$ 开始下一个值为 $j$ 的下标，于是解决了这道题。

[你的代码](https://atcoder.jp/contests/abc381/submissions/60110724)。

你成功地把你 OI 生涯中最具代表性的事物留在了脑海中，可你却仍感空虚。仅用至多 $40$ 片回忆来代表这近乎数万的记忆，未免有所片面。因为，你的 OI 生涯里有太多美好。

回望这些回忆，你忽而感到它们在破碎。正因缺少了什么，或是前因后果，或是平凡琐事，你感觉它们都失去了意义。越往深入去想，你的自我怀疑越深，情绪也越崩溃。可于千钧一发之际，你似乎找到了一切的答案，它能够串联起你的整个 OI 生涯，不遗留，也无遗憾。

这就是你热爱 OI 的心。

---

## 作者：kkxacj (赞：4)

#### 思路

观察到值域 $\le 20$，容易想到状压 `dp`，由于每个值只能选一次，状态 $S$ 为若二进制下第 $i$ 位为 $1$，则表示选了第 $i$ 种值，记 $f_S$ 为状态为 $S$ 是至少要前多少个点，没有就赋为 $10^9$，表示取不到。

先预处理 $a_{i,j}$ 表示 $i$ 及其后面的点值为 $j$ 第一次出现在哪里，没有赋为 $0$，之后直接枚举一个 $i$，然后再枚举加入 $i$ 里没出现的值 $j$，若 $a_{f_{i,j}+1}$ 不为 $0$ 且 $a_{a_{f_{i,j}+1},j}$ 不为 $0$，则 $f_{i+j} = \min\left(f_{i+j},a_{a_{f_{i,j}+1},j}\right)$。

最后对于每个合法的状态，即值不为 $10^9$ 的，算一下颜色数，求出最大值乘 $2$ 就行了。

**code**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf1) + fread(buf1, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf1[1 << 23], *p1 = buf1, *p2 = buf1, ubuf[1 << 23], *u = ubuf;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 2e5+10,M = 21;
int n,a[N],last[N][M+2],f[(1<<M)+10],ans,sum;//状态为i是至少用前j个点 
signed main()
{
	read(n);
	for(int i = 1;i <= n;i++) read(a[i]);
	for(int i = n;i >= 1;i--) 
	{
		for(int j = 1;j < M;j++)
			last[i][j] = last[i+1][j];
		last[i][a[i]] = i;
	}
	for(int i = 0;i < (1<<M);i++) f[i] = 1e9; 
	f[0] = 1;//初值 
	for(int i = 0;i < (1<<M);i++)
		if(f[i] != 1e9)
		for(int j = 1;j < M;j++)
			if((i&(1<<(j-1))) == 0 && last[f[i]][j] != 0 && last[last[f[i]][j]+1][j] != 0)
				f[i+(1<<(j-1))] = min(f[i+(1<<(j-1))],last[last[f[i]][j]+1][j]);
	for(int i = 0;i < (1<<M);i++)
	{
		sum = 0;
		if(f[i] == 1e9) continue;
		for(int j = 1;j < M;j++)
			if((i&(1<<(j-1)))) sum++;
		ans = max(ans,sum*2);
	}
	print(ans); flush();
	return 0;
}
/*
7
3 1 3 2 2 1 1
*/
```

---

## 作者：Union_Find (赞：3)

观察到 $a_i \le 20$，考虑状压。

因为要求子序列不能有重复的数字，所以可以用二进制存贮状态，当前位为 $1$ 就是数字已出现在子序列中。设 $f_{i,s}$ 表示前 $i$ 个数，状态为 $s$ 是否可行。转移是 $O(1)$ 的，总时间复杂度是 $O(n2^{20})$ 的。

我们观察到这个状态有很多无用状态，可以优化。设 $_s$ 表示状态为 $s$ 时，子序列最右端下标最小为多少。这样子就可以通过此题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n = rd(), a[N], f[(1 << 20) + 5], ans, t[25][N], c[25];
il ll nxt(ll x, ll col){return lower_bound(t[col] + 1, t[col] + c[col] + 1, x) - t[col];}
int main(){
	for (int i = 1; i <= n; i++) a[i] = rd() - 1, t[a[i]][++c[a[i]]] = i;
	for (int s = 1; s < (1 << 20); s++) f[s] = 1e18;
	for (int s = 0; s < (1 << 20); s++){
		if (f[s] < 1e18){//求 ans
			ll sum = 0;
			for (int i = 0; i < 20; i++) sum += (bool)(s & (1 << i));
			ans = max(ans, sum);
		}else continue;//剪枝
		for (int i = 0; i < 20; i++){
			if (s & (1 << i)) continue;
			ll p = nxt(f[s], i);
			if (p + 1 <= c[i]) f[s | (1 << i)] = min(f[s | (1 << i)], t[i][p + 1]);
		}
	}
	printf ("%lld", ans + ans);
	return 0;
}

```

---

## 作者：MattL (赞：2)

赛时无法写出。太蠢了。

状压 dp。

---

观察不一定连续。容易想到 dp 表示前 $i$ 个数的最大答案。但要不就超时，要不无法记录有没有用过。

经过上面的思考，发现本题难点在于记录有没有用过。

要记录有没有用过，观察 $1\leq a_i \leq 20$（下文记 $1\leq a_i \leq W$），$\mathcal O(W!)$ 是按顺序记录的，但显然无法通过。故只能记录有没有用过。我们设 $dp_{S}$ 表示答案序列有集合 $S$ 中的所有数最短需要序列前 $dp_{S}$ 个数。但是这时候转移需要考虑顺序。

怎么办呢？我们可以枚举转移到上一个状态少了哪个数，这样子就是使用状态集合转移到一个元素数更小的转移状态集合，无后效性，可以 dp。时间复杂度 $\mathcal O(W2^W)$。

另外，为了转移方便，我们还要记录从某个位置开始某一个数的下一次出现位置。用 $nxt_{i,j}$ 表示在第 $i$ 的位置，下一个 $j$ 的出现位置。预处理复杂度 $\mathcal O(n2^W)$。

总时间复杂度 $\mathcal O((n+W)2^W)$。

综上可写出转移方程：

$$dp_i=\min_{j=1}^W nxt_{nxt_{dp_{i-2^j},j},j}$$

具体实现见代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define f(i,n) for(int i=1;i<=n;i++)
#define f_(i,n) for(int i=n;i>=1;i--)
#define ff(i,a,b) for(int i=a;i<=b;i++)
const int N=2e5+10,M=20;
int n,a[N],nxt[N][M],f[1<<M],ans,cnt;
int main(){
	cin>>n;
	f(i,n)cin>>a[i],a[i]--;//值域改成0到W-1方便使用
	ff(i,0,M-1)nxt[n][i]=nxt[n+1][i]=n+1;//边界初始化
	f_(i,n){//逆序预处理
		ff(o,0,M-1)nxt[i-1][o]=nxt[i][o];
		nxt[i-1][a[i]]=i;
	}f[0]=0;f(i,(1<<M)-1){//直接从小到大枚举即可实现集合元素数量从小到大
		f[i]=n+1;cnt=0;
		ff(o,0,M-1)if(i&(1<<o)){cnt++;//目前集合有 o 这个数
			f[i]=min(f[i],nxt[nxt[f[i^(1<<o)]][o]][o]);
		}if(f[i]<=n)ans=max(ans,cnt);
	}cout<<ans*2<<endl;//答案为集合元素数乘2
    return 0;
}
```

---

## 作者：MrPython (赞：2)

感觉这种题就是很套路的玩意，但是想了好久，还是做题做少了。

从贪心的角度考虑，假设我钦定了要选某个数，我该选哪一个呢？显然选择靠前的肯定不会比靠后的更劣。我们当然要选所有能选的数中最靠前的两个。

使用状压 dp，设 $f_S$ 表示已经选择过的数字集合为 $S$ 时最靠后的已选数位置。我们先预处理出每个数出现的位置，每次转移的时候用二分查找找到最靠前的两个即将添加的数字，往后更新。

```cpp
#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
#include <unordered_set>
#include <vector>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t n;
  fin >> n;
  vector<ui> a(n);
  for (ui& i : a) fin >> i, --i;
  array<vector<size_t>, 20> apr;
  for (size_t i = 0; i < n; ++i) apr[a[i]].emplace_back(i);
  vector<size_t> f(1u << 20, numeric_limits<size_t>::max() / 2);
  f[0] = 0;
  for (size_t b = 0; b < f.size(); ++b)
    for (size_t i = 0; i < 20; ++i)
      if (!((1u << i) & b)) {
        auto it = lower_bound(apr[i].begin(), apr[i].end(), f[b]);
        if (it != apr[i].end() && next(it) != apr[i].end())
          f[(1u << i) | b] = min(f[(1u << i) | b], *next(it) + 1);
      }
  ui ans = 0;
  for (size_t b = 0; b < f.size(); ++b)
    if (f[b] != numeric_limits<size_t>::max() / 2)
      ans = max<ui>(ans, popcount(b));
  fout << ans * 2;
  return 0;
}
```

---

## 作者：include13_fAKe (赞：2)

赛时口胡了 E 觉得时间不够了就没写，把 F 切了，没想到这让我的 $\texttt{Performance}$ 提升到了 $\color{0000ff}{1727}$，Rating $826\to 959$，对于自己来说是一次突破。

## 思路

看到 $A_i\le 20$ 就可以往状压方向考虑了。为什么连续两场 ABC F 题都是状压呢。

以下令 $m=\max\left \{ A_i \right \} $。

考虑状压 $dp$，$dp_i$ 表示选的数的状态为 $i$ 时至少要有 $A$ 数组的前多少位，若不能取到，建议将初值赋成极大值。

因为每一次都要取两个数，所以要预处理从每一个数的位置开始的出现两次这个数的位置。

举个例子：

$$[{\color{red}1},3,3,1,2,2,1]$$

从红色的 $1$ 往后，下一个出现一个 $1$ 的位置是第 $4$ 个数；下一个出现两个 $1$ 的位置是第 $7$ 个数。

从红色的 $1$ 往后，下一个出现一个 $2$ 的位置是第 $5$ 个数；下一个出现两个 $2$ 的位置是第 $6$ 个数。

从红色的 $1$ 往后，下一个出现一个 $2$ 的位置是第 $2$ 个数；下一个出现两个 $2$ 的位置是第 $3$ 个数。

通过反向预处理可以在 $O(nm)$ 时间复杂度中处理完，需要开 $nxt1,nxt2$ 两个二维数组。

状压 $dp$ 可以枚举每一个状态从之前哪一个状态转移而来。仅仅是将某一个二进制数位上的 $0$ 变成了 $1$。可枚举的状态数最多为 $m$，枚举它们的 $nxt2$ 即可。

时间复杂度 $O(nm+2^mm)$。因为 $m\le20$，所以 $2^mm^2$ 不可行。

代码很好写，一遍就过了，机房有人一直没调出来，怎么回事呢。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+15;
const int M=2e6+15;	//二进制状态数  
const int K=20;
int a[N];
int dp[M];	//dp 数组  
int nxt1[N][K];	//下一个  
int nxt2[N][K];	//下一个的下一个  
int n;
int include13=0;
int popcount(int x){
	if(x<2)	return x;
	return popcount(x/2)+(x%2);
}
signed main(){
	memset(nxt1,0x3f,sizeof(nxt1));
	memset(nxt2,0x3f,sizeof(nxt2));
	memset(dp,0x3f,sizeof(dp));
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int j=K;j>=1;j--){
		for(int i=n;i>=0;i--){
//			nxt1[i][j]=-1;
			if(nxt1[i+1][j]<1e6){
				nxt1[i][j]=nxt1[i+1][j];
			}
			if(a[i+1]==j){
				nxt1[i][j]=i+1;
			}
		}
	}
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=K;j++){
//			cout<<nxt1[i][j]<<' ';
//		}
//		cout<<endl;
//	}
//	cout<<endl;
	for(int i=0;i<=n;i++){
		for(int j=1;j<=K;j++){
			if(nxt1[i][j]<1e6){
				nxt2[i][j]=nxt1[nxt1[i][j]][j];
			}
		} 
	}
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=K;j++){
//			cout<<nxt2[i][j]<<' ';
//		}
//		cout<<endl;
//	}
//	cout<<endl;
	dp[0]=0;
	for(int i=1;i<(1<<20);i++){
		for(int j=0;j<=19;j++){//dp[i] 的第 j 位转移  
			if(i&(1<<j)){
				int lst=i-(1<<j);
				if(dp[lst]<1e6)	dp[i]=min(dp[i],nxt2[dp[lst]][j]);
			}
		}
//		cout<<dp[i]<<endl;
	}
	for(int i=1;i<(1<<20);i++){
		if(dp[i]<1e6){
			include13=max(include13,popcount(i));
		}
	}
	cout<<include13*2<<endl;
	return 0;
} //ABC381F 
```

---

## 作者：DengDuck (赞：1)

我们注意到这种序列其实就是形如 `AABBCCDD` 的形态而且数字不能反复出现。

数字不能反复出现好像不是很好做，但是注意到 $A_i\leq 20$，所以我们想到：

不考虑“数字不能反复出现”的条件，但是我们记录一个状压集合 $S$ 表示所有序列中出现过的数字，那么如果一个 $S$ 存在方案，就说明我们有一种大小为 $2\text{Popcount}(S)$ 的方案，其中 $\text{Popcount}$ 表示 二进制下 $1$ 的数量。

$2^{20}$ 其实已经很大了，容不下多一维 $i$ 表示处理到第几位，所以不太能线性 DP。

我们这么想，对于一个状压 $S$，我们肯定贪心地希望它最右位置尽可能在左边，这样我们后面拓展字符就有更多的空间。

所以我们设 $F_{S}$ 表示存在 $S$ 的方案最右的位置的最小值，然后枚举下一个添加什么数字转移就行。

添加下一个数字显然直接把这个数字在我们右边的最近的两个拉过来就行了。


```cpp
#include<bits/stdc++.h>
#define PC __builtin_popcount
#define pb push_back
using namespace std;
const int N=2e5+5;
const int M=20;
int n,A[N],F[(1<<M)+5],Ans,Nxt[M],R[N][M];
vector<int>P[M+5];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&A[i]);A[i]--;
	}
	memset(Nxt,27,sizeof(Nxt));
	for(int i=n;i>=0;i--)
	{
		for(int j=0;j<M;j++)R[i][j]=Nxt[j];
		Nxt[A[i]]=i;
	}
	memset(F,27,sizeof(F));
	F[0]=0;
	for(int S=0;S<(1<<M);S++)
	{
		int t=F[S];
		if(t>n)continue;
		for(int i=0;i<M;i++)
		{
			int k=R[t][i];
			if(k>n)continue;
			k=R[k][i];
			F[S|(1<<i)]=min(F[S|(1<<i)],k);
		}
		Ans=max(Ans,PC(S)*2);
	}
	printf("%d\n",Ans);
}
```

---

## 作者：ran_qwq (赞：1)

每种数字只能出现零或二次，即出现状态只有 $2^V$ 种，结合 $V\le20$，考虑状压 dp。

朴素的 dp 是 $dp_{i,s}$ 表示前 $i$ 个位置，出现状态能否为 $s$，这里强制数成对出现。转移是朴素的，时间复杂度 $O(n2^V)$。

考虑优化，把第一维压掉，可行性问题转化为最优性问题。设 $dp_{s}$ 为出现状态为 $s$ 可行的最小的 $i$。现在新加一个数 $j$，二分找 $dp_s$ 后两个 $j$ 的位置 $p$，如果有则 $dp_{s\cup j}\leftarrow p$。

时间复杂度 $O(2^VV\log n)$ 或 $O(n\log n+2^VV)$。

```cpp
#include<bits/stdc++.h>
#define il inline
#define ui unsigned int
#define ll long long
#define ull unsigned ll
#define lll __int128
#define db double
#define ldb long double
#define pii pair<int,int>
#define vi vector<int>
#define vpii vector<pii>
#define fir first
#define sec second
#define gc getchar
#define pc putchar
#define mst(a,x) memset(a,x,sizeof a)
#define mcp(a,b) memcpy(a,b,sizeof b)
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define pct __builtin_popcount
using namespace std;
const int N=2e5+10,M=20,INF=0x3f3f3f3f,MOD=998244353;
const ll INFll=0x3f3f3f3f3f3f3f3f;
il int rd() {int x=0,f=1; char ch=gc(); while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=gc();} while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=gc(); return x*f;}
il ll rdll() {ll x=0; int f=1; char ch=gc(); while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=gc();} while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=gc(); return x*f;}
il void wr(int x) {if(x==INT_MIN) return printf("-2147483648"),void(); if(x<0) return pc('-'),wr(-x); if(x<10) return pc(x+'0'),void(); wr(x/10),pc(x%10+'0');}
il void wrll(ll x) {if(x==LLONG_MIN) return printf("-9223372036854775808"),void(); if(x<0) return pc('-'),wrll(-x); if(x<10) return pc(x+'0'),void(); wrll(x/10),pc(x%10+'0');}
il void wr(int x,char *s) {wr(x),printf("%s",s);}
il void wrll(ll x,char *s) {wrll(x),printf("%s",s);}
il int vmod(int x) {return x>=MOD?x-MOD:x;}
il int vadd(int x,int y) {return vmod(x+y);}
il int vsub(int x,int y) {return vmod(x-y+MOD);}
il int vmul(int x,int y) {return 1ll*x*y%MOD;}
il int qpow(int x,int y) {int res=1; for(;y;y>>=1,x=vmul(x,x)) if(y&1) res=vmul(res,x); return res;}
il void cadd(int &x,int y) {x=vmod(x+y);}
il void csub(int &x,int y) {x=vmod(x-y+MOD);}
il void cmul(int &x,int y) {x=vmul(x,y);}
il void cmax(int &x,int y) {x<y&&(x=y);}
il void cmaxll(ll &x,ll y) {x<y&&(x=y);}
il void cmin(int &x,int y) {x>y&&(x=y);}
il void cminll(ll &x,ll y) {x>y&&(x=y);}
int n,ans,a[N],dp[1<<M]; vi v[M];
void QwQ() {
	n=rd(),mst(dp,0x3f),dp[0]=0;
	for(int i=1;i<=n;i++) a[i]=rd(),v[a[i]-1].pb(i);
	for(int i=0;i<1<<M;i++) for(int j=0;j<M;j++) if(dp[i]!=INF&&!(i>>j&1)) {
		auto p=ub(v[j].begin(),v[j].end(),dp[i]);
		if(p!=v[j].end()&&next(p)!=v[j].end()) cmin(dp[i|(1<<j)],*next(p));
	}
	for(int i=0;i<1<<M;i++) if(dp[i]!=INF) cmax(ans,pct(i)*2);
	wr(ans,"\n"); 
}
signed main() {
//	freopen("in.in","r",stdin),freopen("out.out","w",stdout);
	int T=1; while(T--) QwQ();
}
```

---

## 作者：huangrenheluogu (赞：1)

致敬传奇四发罚时 ABC381F！

考虑状态 $S$ 表示前面选择数字的状态。以及 $(S,x)$ 表示选择连续的 $S$ 集合内的数字，和一个数字 $x$。总共状态数是 $\mathcal{O}(2^V)$ 的，其中 $V=20$。

枚举每一位，尝试是否存在新的转移，每个东西只转移 $1$ 次，复杂度 $\mathcal{O}(n+2^V)$。

```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int N = 1 << 20 | 5;
int n, a[N], cnt[N], ans;
bool vis[N], vvis[N][20];
vector<int> vec[N];
vector<pii> Vec[N];
inline void upd(int x){
    for(int i = 0; i < 20; i++){
        if(x >> i & 1) continue ;
        vec[i].push_back(x);
    }
}
int main(){
    // freopen("data.in", "r", stdin);
    // freopen("code.out", "w", stdout);
    cin >> n;
    vis[0] = 1;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        a[i]--;
    }
    for(int i = 0; i < 20; i++){
        vec[i].push_back(0);
    }
    for(int i = 1; i <= n; i++){
        // printf("%d\n", i);
        for(pii x : Vec[a[i]]){
            if(vis[x.fi]) continue ;
            // printf("test1 : %d\n", x);
            vis[x.fi] = 1;
            upd(x.fi);
        }
        Vec[a[i]].clear();
        for(int x : vec[a[i]]){
            if(vvis[x][a[i]]) continue ;
            // printf("test2 : %d %d\n", x, i);
            vvis[x][a[i]] = 1;
            Vec[a[i]].push_back({x | (1 << a[i]), a[i]});
        }
        vec[a[i]].clear();
    }
    for(int s = 1; s < 1 << 20; s++){
        cnt[s] = cnt[s ^ (s & -s)] + 1;
        if(vis[s]) ans = max(ans, cnt[s] * 2);
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：zhouruoheng (赞：1)

首先 $a$ 的值域很小只有 $20$，可以支持 $2^{20}$，考虑用状压 dp。

状态 $s$，当 $s$ 二进制下后面第 $i$ 为 $1$ 时，表示 $i$ 计算在答案中。$s$ 的贡献为 $2\times \lvert s\rvert$。

设 $f(s)$ 表示状态为 $s$ 时，右端点的最小值。当 $f(s) \le n$ 时说明 $s$ 合法，可以贡献答案。

$f(s)$ 只能由 $t=s-2^{i}$ 的 $f(t)$ 转移过来，显然 $f(s)$ 是 $f(t)$ 后面的第二个 $i$ 的位置。若不存在第二个 $i$ ，令 $f(s)=n+1$ 表示不合法。设 $ne(i,j)$ 表示数组 $a$ 在 $[i+1,n]$ 中第一个 $j+1$ 的位置，则有 $\displaystyle f(s)=\min_{0 \le i < \lvert s\rvert}(ne(ne(f(t),i),i))$。

预处理所有 $ne(i,j)$ 还是比较好办的，直接看代码吧。


``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>

using namespace std;
typedef long long ll;
const int N=2e5+5,M=20,S=1<<20;
int n;
int a[N],ne[N][M];
int f[S];
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=0;i<M;i++) ne[n][i]=ne[n+1][i]=n+1;
    for(int i=n-1;i>=0;i--)
    {
        for(int j=0;j<M;j++) ne[i][j]=ne[i+1][j];
        ne[i][a[i+1]-1]=i+1;
    }
    for(int i=0;i<S;i++) f[i]=n+1;
    f[0]=0;
    int ans=0;
    for(int i=0;i<S;i++)
    {
        int cnt=0;
        for(int j=0;j<M;j++)
            if(i&(1<<j)) 
            {
                cnt+=2;
                f[i]=min(f[i],ne[ne[f[i^(1<<j)]][j]][j]);
            }
        if(f[i]<=n) ans=max(ans,cnt);
    }
    cout<<ans<<'\n';
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif 
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    solve();
    return 0;
}

```

---

## 作者：xixisuper (赞：1)

# AT_abc381_f [ABC381F] 1122 Subsequence 题解

我是弱智，赛时挂了 5 发 D，没来的及打 F，糖丸了。

## 思路

注意到值域很小，我们考虑状压。

设 $f_S$ 表示字符集为 $S$ 的子序列出现最后一个字符的位置的最小值是多少。于是我们可以枚举 $S$ 中的每一个位置 $i$，判断其是否可以是这个子序列的最后一个数。

详细的说就是预处理出来对于每个数来说，每个位置往后离其最近的一个数在哪个位置上，我们只需要判断我们枚举的那个数是否在 $n$ 以内出现就可以了。

我们设 $V$ 表示这个数列的值域，则总时间复杂度就是 $O(nV+V\cdot 2^V)$，能够通过此题。

## 代码

赛时没打，赛后 5min 写出来，糖丸了。

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;
const ll N=2e5+10;
const ll V=21;
const ll MX=(1LL<<20);
ll nxt[V][N],a[N],n,f[MX+10];
inline ll lowbit(ll x){return x&(-x);}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(ll i=1;i<=n;i++) cin>>a[i];
	for(ll i=n+1;i>=0;i--){
		for(ll j=1;j<=20;j++){
			if(i==n+1) nxt[j][i]=n+1;
			else{
				nxt[j][i]=nxt[j][i+1];
				if(i<n&&a[i+1]==j) nxt[j][i]=i+1;
			}
		}
	}
	ll ans=0;
	for(ll i=1;i<MX;i++){
		if(i==lowbit(i)){
			for(ll j=0;j<20;j++){
				if((i>>j)&1){
					f[i]=nxt[j+1][nxt[j+1][0]];
					if(f[i]==n+1) f[i]=0;
				}
			}
			if(f[i]) ans=max(ans,1LL);
		}
		else{
			ll cnt=0;
			f[i]=n+1;
			for(ll j=0;j<20;j++){
				if((i>>j)&1){
					cnt++;
					if(!f[i^(1LL<<j)]) continue;
					f[i]=min(f[i],nxt[j+1][nxt[j+1][f[i^(1LL<<j)]]]);
				}
			}
			if(f[i]==n+1) f[i]=0;
			else ans=max(ans,cnt);
		}
	}
	cout<<ans*2;
	return 0;
}
```

---

## 作者：george0929 (赞：1)

闲话：赛时写了两发贪心，全错，感觉要糖丸了。

本题考查的主要是**动态规划的状态设计优化**。

注意到值域较小，考虑状压 DP，朴素的 DP 状态为 $f_{i,S}$ 表示以 $i$ 结尾，序列中的数构成集合 $S$ **是否可行**。但这样显然会 MLE。

注意到 DP 状态是“是否可行”，也就是说我们存的是布尔值，非常浪费。针对这种问题的一个常见套路是优化 DP 状态的设计：**将 DP 的一维放到 DP 值上。**

具体的，令 $f_{S}$ 表示序列中的数构成集合 $S$ 的**最小结尾**，转移显然。

```cpp
#include<bits/stdc++.h>
using namespace std;
int nx[200005][25],pos[25],a[200005],dp[1048605];
int main(){
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=20;i++) pos[i]=n+1;
	for(int i=n;i>=0;i--){
		for(int j=1;j<=20;j++) nx[i][j]=pos[j];
		pos[a[i]]=i;
	}
	int ans=0;
	for(int s=0;s<1048576;s++){
		for(int i=1;i<=20;i++){
			if(s&(1<<(i-1))){
				int p=dp[s^(1<<(i-1))];
				if(p>n) continue;
				int nxt=nx[nx[p][i]][i];
				if(!nxt||nxt>n) continue;
				dp[s]=min(dp[s],nxt);
			}
		}
		if(dp[s]<=n) ans=max(ans,__builtin_popcount(s)*2);
	}
	cout<<ans;
}
```

---

## 作者：LEE114514 (赞：0)

## 思路

观察到值域小的离谱，考虑状压。

因为 $n$ 很大，所以考虑复杂度里不要让 $2^V$ 和 $n$ 直接相乘。

设 $f_{sta}$  表示状态为 $sta$ 时最小下标，其中状态的定义是 $\sum_{i=1}^{20}{2^{i-1} \times [i 连续出现两次]}$，通俗的说就是已经合法放进了哪些数。那么每次转移枚举最后一个出现两次的数 $j$，尝试用严格在 $f_{sta \oplus 2^{j-1}}$ 后出现的第二个 $j$ 的位置来更新 $f_{sta}$。

显然，可以使用二分实现。不过由于值域很小，也可以对于每个点维护每个值下一次在何处出现。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int nxt[maxn][20];
int lst[20];
int f[1<<20];
int n,a[maxn];
int res;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",a+i),--a[i];
	for(int i=0;i<20;++i) lst[i]=n+1,nxt[n+1][i]=n+1;
	for(int i=n;i>=0;--i){
		for(int j=0;j<20;++j) nxt[i][j]=lst[j];
		lst[a[i]]=i;
	}
	memset(f,63,sizeof f);
	f[0]=0;
	for(int i=0;i<(1<<20);++i){
		for(int j=0;j<20;++j){
			if(!((i>>j)&1)) continue;
			int sta=i^(1<<j);
			if(f[sta]>n) continue;
			if(nxt[nxt[f[sta]][j]][j]<=n) f[i]=min(f[i],nxt[nxt[f[sta]][j]][j]);
		}
	}
	for(int i=0;i<(1<<20);++i) if(f[i]<=n) res=max(res,2*__builtin_popcount(i));
	printf("%d",res);
}
```

---

## 作者：zzy0618 (赞：0)

注意到 $A_i\le 20$。

这意味着我们可以状压，每一位表示这个数是否出现过。具体的，$f_{s}$ 表示 $s$ 这个状态最少需要多长的 $A$ 数组前缀。对于一个 $i\not \in s$，$f_s$ 可以更新 $f_{s|1<<i}$，值为 $f_s$ 后第二个 $i$ 的位置。最终如果一个 $f_s\le n$，它能够更新答案。

笔者赛时卡了一下，就是为什么一定再 $f_s$ 之后取两个而不是可能在这之前。其实不用担心，由于状压 DP 能够解决顺序问题，这种情况会被另一个 $f_s$ 考虑到。

设 $m=20$，$O(mn)$ 处理每个位置后面每个数第一次出现的位置，$O(m2^m)$ 状压 DP，足够通过此题。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,a[N],f[N][21],g[1<<22],ans;
int calc(int x){
	int k=0;
	while(x)++k,x-=x&-x;
	return k;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int j=1;j<=20;++j)
		f[n][j]=n+1;
	for(int i=n-1;i>=0;--i){
		for(int j=1;j<=20;++j){
			f[i][j]=f[i+1][j];
		}f[i][a[i+1]]=i+1;
	}
	memset(g,0x3f,sizeof(g));g[0]=0;
	for(int s=0;s<(1<<20);++s){
		if(g[s]<=n)ans=max(ans,calc(s)*2);
		if(g[s]>n)continue;
		for(int j=0;j<20;++j){
			if(s&(1<<j))continue;
			int t=f[g[s]][j+1],tt=f[t][j+1];
			if(tt>n||tt==0)continue;
			g[s|(1<<j)]=min(g[s|(1<<j)],tt);
		}
	}cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：HNOIRPplusplus (赞：0)

给定一个长度为 $N$ 的序列 $A$，其中 $1\le A_i\le 20$。选出它最长的子序列，满足这个子序列中的值成对相邻出现，且一种值只出现了一对。求出最长的长度。

看到 $1\le A_i\le 20$，考虑状压。

---
考场上的时候有一个显然错误的方法，即为设 $dp_{i, \text{mask}, k}$ 表示目前考虑到第 $i$ 位，状态为 $\text{mask}$，目前有一个 $k$ 还没有匹配的情况。

我们直接假设 $dp_\text{mask}$ 表示当前的子序列里面已经有 $\text{mask}$ 里面的值的情况下，子序列的最后一位在原序列里面最靠左可以在哪里，其中 $\text{mask}$ 是一个 $0$ 到 $2^{20}-1$ 的状压二进制整数。  
贪心地想，包含同样的值的子序列，结束的地方当然越靠左越好。

由于长的序列一定是由短的序列构成的，所以我们每一次都是从 $\operatorname{popcount}$ 更小的状态转移到 $\operatorname{popcount}$ 大 $1$ 的状态。此处 $\operatorname{popcount}$ 表示一个二进制数中 $1$ 的个数，所以这个结论是也很显然的。

我们设 $nxt_{i,j}$ 表示位置 $i$ 后第一个值为 $j$ 的位置。则 $nxt_{(nxt_{i, j}) + 1, j}$ 就是 $i$ 后第二个值为 $j$ 的位置。

所以，每次我们可以枚举一个 $\text{mask}$ 中没有的值。假设该值为 $j$，则 $\text{mask} \operatorname{\&} 2^{j-1}$ 为 $0$。其中 $\operatorname{\&}$ 表示按位与运算。  
然后，令 $dp_{\text{mask} + 2^{j-1}} \leftarrow nxt_{(nxt_{dp_{\text{mask}}, j}) + 1, j}$。也就是 $dp_{\text{mask}}$ 后面的第二个 $j$ 的位置就是 $dp_{\text{mask} + 2^{j-1}}$ 的值，如同字面意思。

主要是状态设计是平常有一点不常用的另一种想法，想通了该题可能比 E 还简单一些。

``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1500005;

int a[N], nxt[N][25];
int dp[N], pc[N];

signed main() {
  int n;
  cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for(int i = n; i; i--) {
    for(int j = 1; j <= 20; j++) {
      nxt[i][j] = nxt[i + 1][j];
    }
    nxt[i][a[i]] = i;
  }
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= 20; j++) {
      if(nxt[i][j]) {
        nxt[i][j] = nxt[nxt[i][j] + 1][j];
      }
    }
  }
  dp[0] = 0;
  for(int i = 1; i < (1 << 20); i++) {
    dp[i] = n + 1;
    pc[i] = pc[i >> 1] + (i & 1);
  }
  for(int popc = 0; popc < 20; popc++) {
    for(int j = 0; j < (1 << 20); j++) {
      if(pc[j] == popc) {
        for(int i = 1; i <= 20; i++) {
          if(!(j & (1 << i - 1)) && nxt[dp[j] + 1][i]) {
            dp[j | (1 << i - 1)] = min(dp[j | (1 << i - 1)], nxt[dp[j] + 1][i]);
          }
        }
      }
    }
  }
  int ans = 0;
  for(int j = 0; j < (1 << 20); j++) {
    if(dp[j] <= n) {
      ans = max(ans, pc[j]);
    }
  }
  cout << ans * 2;
}
```

---

## 作者：无名之雾 (赞：0)

场上玄妙操作想出来的题目。

## 思路

仔细观察数据值域，可以发现 $a_i\le 20$ 所以不妨考虑状压 dp，~~也是我唯一会的一种 dp~~。

一种显然的状态设计是 $f_{i,S}$ 定义为以 $i$ 结尾所构成的集合 $S$ 是否可行。但是这样不太好做。

考虑如何优化，我们可以选择优化掉一维。

定义 $f_S$表示 $S$ 这个集合结束的最小位置。

考虑如何转移，我们发现这时候直接转移需要考虑转移的顺序。

实际上解决下来也十分简单，我们只需要枚举转移到上一个状态索要删除的数。可以 dp。然后就基本做完了。

实现的话，我们令一个 $b_{i,j}$ 表示序列 $i$ 到 $n$ 中 $j$ 第一次出现的位置。

最终方程就是：

$$dp_S=\min\{ b_{b_{f_{S-j},j},j} \}$$


时间复杂度：$O(V(n+2^V))$。

[submission](https://atcoder.jp/contests/abc381/submissions/60079309)

---

## 作者：Zeoykkk (赞：0)

# ABC381F. 1122 Subsequence

>我们称长度为 $n$ 的序列 $a$ 是好序列，当且仅当：
>
>* $n$ 为偶数；
>* $\forall 1\leq i \leq \frac{n}{2}, a[2i - 1] = a[2i]$ 均成立；
>* $a$ 中每种数都出现恰好 $2$ 次。
>
>给定序列 $a$，求最长的好的子序列的长度。$n \leq 2\times 10^5, 1\leq a_i \leq20$。

## Sol：状压 DP

因为 $a_i \leq 20$，容易想到状压 DP，定义 $dp(S)$ 代表最小的 $i$ 满足 $a[1, i]$ 中存在好子序列，使得集合 $S$ 中的元素都在该子序列中。若不存在这样的 $i$，则钦定 $dp(S) = \infty$。

答案为 $\max_{S = 1}^{2^{V} - 1}[dp(S) \leq n] \times \text{bitcount}(S) \times 2$，其中 $V$ 代表值域，$\text{bitcount}(x)$ 代表 $x$ 二进制位上 $1$ 的个数。

定义 $nxt(i, j)$ 代表最小的 $k$ 满足 $k > i, a_k = j$，若不存在这样的 $k$，则钦定 $nxt(i, j) = \infty$。可以 $O(nV)$ 预处理。

转移枚举集合 $S$ 是少了哪一种元素从 $S'$ 中转移过来的，即：
$$
dp(S) = \min_{S'}(nxt(nxt(dp(S'), x), x)),S' = S - \{x\},x\in S
$$
显然转移是 $O(V)$ 的。

时间复杂度：$O(V(n + 2^V))$，其中 $V$ 代表值域。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define pb push_back
#define endl '\n'
using ll = long long;
const ll mod = 1000000007;
const ll INF = 1ll << 60;
const int inf = 1 << 30;
const int N = 200010;
const int V = 20;

int n, a[N];
void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<vector<int>> nxt(n + 5, vector<int>(V + 5, n + 1));
    a[n + 1] = inf;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 1; j <= 20; ++j) {
            nxt[i][j] = nxt[i + 1][j];
            if (a[i + 1] == j) nxt[i][j] = i + 1;
        }
    }
    vector<int> dp(1 << V, n + 1);
    dp[0] = 0;
    int ans = 0;
    for (int S = 1; S < (1 << V); ++S) {
        for (int i = 0; i < V; ++i) {
            if (S >> i & 1) {
                dp[S] = min(dp[S], nxt[nxt[dp[S ^ (1 << i)]][i + 1]][i + 1]);
            }
        }
        if (dp[S] <= n) {
            ans = max(ans, __builtin_popcount(S) * 2);
        }
    }
    cout << ans << endl;
}
signed main(void) {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int Test = 1;
    // cin >> Test;
    while (Test--) solve();
    return 0;
}
```

---

## 作者：Night_sea_64 (赞：0)

我在最不可能只过 ABCDF 的一场只过了 ABCDF。

首先，我们在选子序列的时候要考虑到一个数的出现次数。再看到 $A_i\le20$ 就启发我们状压 dp。

如果状压 dp，那显然设计的 dp 状态就不能和数列中的下标有关。于是可以想出一个状态：$f_k$ 表示达到 $k$（表示每个值是否被选的 $01$ 串），子序列的末尾最靠前可以在哪里。

dp 时枚举最后选择的那个值（应该占据已选出的子序列的最后两个位置），设为 $i$，然后看去掉 $i$ 对应的子问题 dp 出的位置，后面再取最靠近的两个 $i$。

每个位置后面最靠近的某个值只需预处理即可搞定。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[200010],nxt[200010][25];
int f[1050010];
int m=20;
int ans=0;
int main()
{
  cin>>n;
  for(int i=1;i<=n;i++)
  {
    cin>>a[i];
    a[i]--;
  }
  for(int i=n;i>=0;i--)
  {
    for(int j=0;j<20;j++)
      if(i>0&&a[i]==j)nxt[i][j]=i;
      else nxt[i][j]=nxt[i+1][j];
  }
  for(int k=1;k<(1<<m);k++)
  {
    f[k]=1e9;
    for(int i=0;i<20;i++)
      if(k&(1<<i))
      {
        int pos=f[k^(1<<i)];
        if(pos==1e9)continue;
        if(nxt[pos+1][i]>0&&nxt[nxt[pos+1][i]+1][i]>0)
          f[k]=min(f[k],nxt[nxt[pos+1][i]+1][i]);
      }
    if(f[k]<1e9)ans=max(ans,__builtin_popcount(k)*2);
  }
  cout<<ans<<endl;
  return 0;
}
```

---

## 作者：cppcppcpp3 (赞：0)

# 题意

定义一个正整数序列 $\{b_1,b_2,\cdots,b_m\}$ 为 **1122 数列** 当且仅当序列满足以下所有条件：

1. $m\equiv 0\pmod 2$
2. 对于所有 $1\le i\le \frac{m}{2}$ 的整数 $i$，满足 $b_{2i-1}=b_{2i}$。
3. 在 $b$ 中出现过的整数恰好出现 $2$ 次。

给出长度为 $n$ 的序列 $a$，求出 $a$ 的（可以不连续）子序列中，是 **1122 数列** 的序列的长度最大值。

$1\le n\le 2\times 10^5,1\le a_i\le 20$

# 思路

比较简单的状压 dp，还好场切了。

假设我们现在尝试构造一个合法序列。称 $a_i$ 的值为颜色，用一次颜色 $x$ 表示将两个满足 $a_i=x$ 的不同下标加入序列末尾。由条件 3 每种颜色至多会被使用一次。同时我们每次往序列末尾添加某个颜色，只关注**用过的最大下标**（即加入颜色前序列末尾的下标），以及**哪些颜色已经被用过**，而由于颜色数 $m\le 20$，把这个信息记录下来是可行的。

考虑大概按照这个每次向序列末尾添加一个颜色的过程 dp，把我们关注的两样东西记入状态：记 $f(i,S)=0/1$ 表示顺次考虑到末尾下标为 $i$ 的序列，使用颜色的集合为 $S$ 是否可行（注意到序列长度即 $2|S|$，不用记录什么“最大长度”）。转移枚举一个没用过的颜色 $x$ 加到末尾，贪心地选取 $i$ 之后最近的两个下标 $j,k$ 且 $j<k,a_j=a_k=x$，转移到 $f(k,S\cup\{x\})$。状态数 $O(n2^m)$。

考虑优化状态。实际上你往一个前面已经决定好的序列末尾加入一个颜色，只关心的是颜色的**集合**，这些用过的颜色**怎么排列是不重要的**。而且 bool 的状态太浪费了，完全可以把 $i$ 扔进状态对应的值里面去，即对同样颜色集合构成的序列只取末尾最靠前的转移。此时状态变为 $f_S$，表示使用颜色集合为 $S$ 的合法序列，**序列末尾下标的最小值**。转移类似枚举 $x$，取最前的两个下标 $j,k$ 满足 $f_S<j<k,a_j=a_k=x$，更新 $f_{S\cup \{x\}} \to \min(f_{S\cup \{x\}},k)$。

最终 $ans=\max\limits_{f_S\le n}|S|$，时间复杂度 $O(m2^m\log n)$，对数来自二分求 $j,k$。

[My Submission](https://atcoder.jp/contests/abc381/submissions/60070738)

---

## 作者：liuziqin (赞：0)

## 思路

由于 $A_i \le 20$，因此考虑状压。

我们设 $f_s$ 为当前状态为 $s$，最后一个数字的位置为 $f_s$。

我们对于每一个 $i$ 求出所有的右边距离它最近的数字 $j$ 的位置，记为 $nxt_{i,j}$。

解下来考虑如何转移，由于直接转移枚举的状态过多，因此考虑递推转移。考虑对于一个状态 $s$ 往里面添加一个数 $j$。这时将 $f_{s|(2^j)}$ 更新为向右距离 $f_s$ 第二近的 $j$ 即可。

最后如果 $f_s\le n$ 就取 $s$ 二进制下 1 的数量即可。
## Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2000005;
int a[N],nxt[N][25];
int dp[N];
int popcnt(int u){
	int ans=0;
	while(u){
		ans+=u%2;
		u/=2;
	}
	return ans;
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]--;
	}
	for(int i=0;i<20;i++)nxt[n+1][i]=n+1;
	for(int i=n;i>=0;i--){
		for(int j=0;j<20;j++)nxt[i][j]=nxt[i+1][j];
		if(i)nxt[i][a[i]]=i;
	}//预处理nxt[i][j]
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for(int i=0;i<(1<<20);i++){
		if(dp[i]>n)continue;
		for(int j=0;j<20;j++){
			if(i&(1<<j))continue;
			int t=nxt[dp[i]][j];
			if(t>=n)continue;
			t=nxt[t+1][j];
			if(t>n)continue;
			dp[i|(1<<j)]=min(dp[i|(1<<j)],t);
		}//转移
	}
	int ans=0;
	for(int i=1;i<(1<<20);i++)if(dp[i]<=n)ans=max(ans,popcnt(i)*2);//计算贡献
	cout<<ans<<"\n";
}
```

---

## 作者：11400F (赞：0)

看到 $A_i \le 20$，我们很自然的就会想到状态压缩。

我们要选一些数，两个数两个数的选，每一个数只能选 $1$ 次。于是我们就可以用一个二进制数来表示一种选项。这个数的第 $i$ 位上为 $1$ 就相当于选了数 $i$，第 $i$ 位上为 $0$ 就相当于是没有选这个数 $i$。而 $2^{20} = 1048576$，所以并不会炸空间。

现在我们考虑如何转移。我们存一个数组 $dp$，表示每一个状态的最小右端点位置。因为很显然的，这个右端点位置越往左，那么肯定是越优的。因为这会给其他的数留下更多的选择空间。

我们对于每一个状态，一个二进制数 $k$（表示哪些数已经被选过了）枚举 $1 \sim 20$ 的每一个数，记他为 $j$。那么当前加进去的状态就是 $2^{j-1}$。因为每一个数只能选一次，所以如果 $k$ 里面包含 $2^{j-1}$，也就是 $k \And 2^{j-1} > 0$，那么就只能跳过，因为这个数已经被选过了。

然后因为我们要在 $k$ 状态后面选数 $j$，那么就只能在位置 $dp_k$ 后面选头两个值为 $j$ 的数。这个可以用数组 $O(n)$ 预处理。然后如果选不到后面的两个值为 $j$ 的数，那么就跳过。如果选到了，那么就把第二个 $j$ 的位置 $pos$ 给提出来，设新的状态 $stat$ 为状态 $k$ 和数 $j$ 合并起来的 $k +2^{j-1}$，那么 $dp_{stat} = \min(dp_{stat}, pos)$。因为这个位置是可以被选的，然后最终答案 $ans = \max(ans, \text{popcount}(stat))$。这里的 $\text{popcount}$ 指的就是一个二进制数里 $1$ 的个数，转换到集合上，就是选了几个数。最后输出 $2\times ans$ 即可。

最后看边界。先 memset dp 数组值为无穷大。首先我们设 $dp_0 = 0$ 的。因为啥都不选的话，最小右端点位置肯定是 $0$。然后如果这个状态之前没有选，也就是值为无穷大的话，那么后面的也就不可能存在了。所以直接跳过。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+35;
int a[N];
int latest[N][21];
int n;
const int MAXN = (1<<21);
int ans[MAXN];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin>>n;
    memset(ans, 0x3f, sizeof ans);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=n;i>=1;i--){
        for(int j=1;j<=20;j++){
            latest[i][j] = latest[i+1][j];
        }
        latest[i][a[i]] = i;
    }
    int rans = 0;
    ans[0] = 0;
    for(int i=0;i<(1<<20);i++){
        if(ans[i] == 0x3f3f3f3f) continue;
        for(int j=1;j<=20;j++){
            int now = (1<<(j-1));
            if(now&i) continue;
            int fstpos = latest[ans[i]+1][j];
            int secpos = latest[fstpos+1][j];
            if(fstpos == 0 || secpos == 0)
                continue;
            int stat = i|now;
            ans[stat] = min(ans[stat], secpos); 
            rans = max(rans, __builtin_popcount(stat));
        }
    }
    cout<<rans * 2;
    return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

值域这么小，直接状压不难想到。

因为一个数最多出现 $2$ 次，那么我们定义状态 $s$ 表示每个数是否出现过 $2$ 次。则我们需要维护所有的 $s$。不难发现，对于一个状态 $s$，我们再在其基础上新加 $2$ 个 $x$ 后，贪心地尽可能使结尾下标最小。这样将会有更多的可能匹配空间。

那么就能直接定义状态函数 $f_{s}$ 表示出现状态为 $s$ 时，子序列结尾的最小下标。那么新加一个 $x$ 就只需要找到 $f_{s}$ 后面第一个和第二个 $x$ 出现的下标了。而一个状态 $s$ 合法的判断仅有 $f_{s} \le n$。直接转移可以做到 $O(V2^V)$，我写的 $O(V2^V \log n)$。

## 代码

```cpp
il void solve(){
	n=rd;
	for(re int i=1;i<=n;++i) a[i]=rd,x[a[i]].push_back(i);
	for(re int i=n;i>=1;--i){
		if(!lst[a[i]]) nxt[i]=n+1;
		else nxt[i]=lst[a[i]];
		lst[a[i]]=i;
	}
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(re int s=0;s<(1ll<<20);++s)
	for(re int i=1;i<=20;++i)
	if(!((s>>(i-1))&1)){
		int s_=(s|(1ll<<(i-1)));
		auto w=upper_bound(x[i].begin(),x[i].end(),f[s]);
		if(w!=x[i].end()&&nxt[*w]!=n+1)
			f[s_]=min(f[s_],nxt[*w]);
	}
	int Max=0;
	for(re int s=0;s<(1ll<<20);++s) 
	if(f[s]<=n) Max=max(Max,(int)__builtin_popcountll(s));
	printf("%lld\n",Max*2);
    return ;
}
```

---

## 作者：__Floze3__ (赞：0)

## 思路

我们看到这道题 $n$ 的范围给的很大，但值域很小，说明最终选出的数不会很多。这其实我们考虑选了哪些数，并从中得出答案。具体的，我们设 $f_{st}$ 表示在选了的数的状态为 $st$ 时，最后一个数最靠左的位置。很显然，位置越靠左，能够选的空间更大，一定不劣。那么我们只需要状压 dp，枚举新状态要选的最后一个数是什么，从之前状态的最后一个位置之后找到前两个数即可。设值域为 $V$，通过预处理可以做到 $O(V2^V)$，不过直接二分的 $O(V2^V \log n)$ 也可通过。

## 代码

[赛时提交链接](https://atcoder.jp/contests/abc381/submissions/60079175)

---

## 作者：I_will_AKIOI (赞：0)

这个人在 21:39:47 调了出来，粘错样例误以为寄了没交上去。

发现 $a_i$ 的范围只有 $20$，同时也可以发现一个贪心，就是尽可能选最近的数。预处理出 $nxt_{i,j}$ 表示从 $i$ 往后第一个 $j$ 的下标。然后进行贪心，发现会炸。

从这个 $20$ 我们还可以联想到状压 dp。把这个贪心算法进行修改，改成 $f_s$ 表示选出 $s$ 这个集合中每个元素下标最大值的最小值，接着枚举 $i$，也就是上一步选择的数，接着就可以进行转移，$f_s$ 需要从 $f_{s-2^i}$ 选出两个数，也就是往后跳两步，因此转移方程就行 $f_s\leftarrow nxt_{nxt_{f_{s-2^i}},i}$，注意这里如果不存在下一个数字需要跳过。

```cpp
#include<bits/stdc++.h>
#define N 200005
#define M 20
#pragma GCC optimize("O3")
using namespace std;
int n,now,ans,a[N],vis[M],nxt[N][M],f[1<<M];
int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]--;
	for(int i=n;i>=0;i--)
	{
		for(int j=0;j<M;j++) nxt[i][j]=((vis[j]==0)?n+1:vis[j]);
		vis[a[i]]=i;
	}
	memset(f,63,sizeof(f));
	f[0]=0;
	for(int i=1;i<(1<<M);i++)
	{
		for(int j=0;j<M;j++)
		{
			if(!(i&(1<<j))) continue;
			if(f[i-(1<<j)]>n) continue;
			if(nxt[f[i-(1<<j)]][j]==n+1) continue;
			if(nxt[nxt[f[i-(1<<j)]][j]][j]==n+1) continue;
			f[i]=min(f[i],nxt[nxt[f[i-(1<<j)]][j]][j]);
		}
	}
	for(int i=0;i<(1<<M);i++) if(f[i]<=n) ans=max(ans,__builtin_popcount(i)*2);
	cout<<ans;
	return 0;
}
```

---


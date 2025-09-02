# [ABC145F] Laminate

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc145/tasks/abc145_f

$ 10^9 $ 行 $ N $ 列の白色グリッドのいくつかのマスを黒く塗って、アートを製作します。  
 現時点では、左から $ i $ 列目については下から $ H_i $ 個のマスを黒く塗り、その列の残りのマスは塗らない予定です。  
 アートの製作を開始する前に、あなたは $ K $ 個以下の列 ($ 0 $ 個でもよい) を選び、それらの列に対する $ H_i $ の値を $ 0 $ 以上 $ 10^9 $ 以下の好きな整数に変更できます。  
 変更後の値は列ごとに個別に選べます。

その後、あなたは次の操作を繰り返すことで変更後のアートを製作します。

- ある行の連続する $ 1 $ マス以上のマスを選んで黒く塗る。(すでに黒く塗られたマスを再び塗ってもよいが、塗らないことにしたマスを塗ってはならない。)

この操作を最小で何回行う必要があるか求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 300 $
- $ 0\ \leq\ K\ \leq\ N $
- $ 1\ \leq\ H_i\ \leq\ 10^9 $
- 入力はすべて整数である。

### Sample Explanation 1

例えば、$ H_3 $ の値を $ 2 $ に変更した上で以下のような操作を行うと、$ 3 $ 回の操作で変更後のアートを製作することができます。 - 下から $ 1 $ 行目の左から $ 1 $ 列目から $ 4 $ 列目までのマスを黒く塗る。 - 下から $ 2 $ 行目の左から $ 1 $ 列目から $ 3 $ 列目までのマスを黒く塗る。 - 下から $ 3 $ 行目の左から $ 2 $ 列目のマスを黒く塗る。

## 样例 #1

### 输入

```
4 1
2 3 4 1```

### 输出

```
3```

## 样例 #2

### 输入

```
6 2
8 6 9 1 2 1```

### 输出

```
7```

## 样例 #3

### 输入

```
10 0
1 1000000000 1 1000000000 1 1000000000 1 1000000000 1 1000000000```

### 输出

```
4999999996```

# 题解

## 作者：StudyingFather (赞：13)

容易看出 $k=0$ 的情况就是考了两次的积木大赛。

对于第 $i$ 列，分两种情况：

- 该列比前一列高：此时会产生 $h_i-h_{i-1}$ 的贡献。
- 该列比前一列矮或相等：此时不会产生贡献。

现在给了能更改高度的机会，我们怎么做呢？

对于一列，容易看出，将其改变为最左边的一列的高度最优（这一列就对答案不产生贡献了）。这种操作其实相当于删除了这一列。

问题变成了我们从 $n$ 列中选 $n-k$ 列，最优解是多少。

设 $f(i,j)$ 表示我们选了 $j$ 列，所有选择的列中最左边为第 $i$ 列的最优答案。

容易得转移方程：

$$
f_{i,j}=\min_{p=i+1}^{n} f_{p,j-1}+\min\{0,h_i-h_p\}
$$

时间复杂度为 $O(n^3)$。

```cpp
// Problem : F - Laminate
// Contest : AtCoder Beginner Contest 145
// URL : https://atcoder.jp/contests/abc145/tasks/abc145_f
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 1024 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <cstring>
#include <iostream>
using namespace std;
long long f[305][305];
int h[305];
int main()
{
 int n,k;
 long long ans=1e18;
 cin>>n>>k;
 for(int i=1;i<=n;i++)
  cin>>h[i];
 memset(f,63,sizeof(f));
 if(n==k)
 {
  cout<<0<<endl;
  return 0;
 }
 for(int i=n;i;i--)
 {
  f[i][1]=h[i];
  for(int j=2;j<=n-k;j++)
   for(int p=i-1;p;p--)
    f[p][j]=min(f[p][j],f[i][j-1]+max(0,h[p]-h[i]));
 }
 for(int i=1;i<=n;i++)
  ans=min(ans,f[i][n-k]);
 cout<<ans<<endl;
 return 0;
}
```

---

## 作者：Yang818 (赞：4)

## 题目背景

很多人看完题目后第一个反应就是：这不是 CCF 最喜欢的那道考了两次的积木大赛吗？没错，本题中当 $k=0$ 时，就是积木大赛原题。但可惜，$k$ 在本题中会到300。

## 分析

简单的分析一下，如果后面那列比前面那列矮或者相等，前面在处理的时候就会顺便把这一列处理掉，所以不用管；但是如果后面那列比前面这列高，就需要考虑这一列是否需要改动。因为可以改成任意值，所以可以当成把这一列直接删掉，不对两边产生影响。

那我们改怎么用好这个改动的机会呢？

## 转移方程

又分析可得，其实我们就是要从 $n$ 列中找出 $n-k$ 列，并且使得 $n-k$ 列的处理次数是最少的。

$f_{i,j}$ 表示前 $i$ 列，保留 $j$ 列的最小开销。

$$f_{i,j}=\min_{1\leq pre \leq i}{f_{pre,j-1}+\max{0,h_i-p_i}}$$

~~本题上一篇题解的转移方程写错了~~

其中 $pre$ 表示前面一列。取 $0$ 和 $h_i-p_i$ 的较大值是为了避免负数的产生。

不知道有没有人发现：上面的这个转移方程又一个隐含的条件就是不删第 $i$ 列。因此，我们在输出答案的时候不能只输出 $f_{n,n-k}$，还需要从 $n-k$ 到 $n$ 遍历一下，找出最优解。

## 代码
~~还要代码吗？~~
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MXN=305;
int n,k,h[MXN];
long long g_f[MXN][MXN],ans=3e11;//别忘记开long long

int main(){
	cin>>n>>k;
	k=n-k;
	for(int i=1;i<=n;i++){
		cin>>h[i];
	}
	memset(g_f,0x3f,sizeof(g_f));
	g_f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			for(int pre=0;pre<i;pre++)
				g_f[i][j]=min(g_f[i][j],g_f[pre][j-1]+max(0,h[i]-h[pre]));//转移方程
		}
	}
	for(int i=k;i<=n;i++){
		ans=min(ans,g_f[i][k]);//重新遍历
	}
	cout<<ans<<endl;
	return 0;
}
```
望通过，谢谢



---

## 作者：ln001 (赞：2)

## 题意
给定 $n$ 个积木，每个积木均有高度 $a_i$，你有至多 $k$ 次机会修改任意积木的高度。修改全部完成后，每次操作可以将**连续的**若干积木高度减一，高度**不能出现负数**，求将所有积木的高度全部降为 $0$ 的最少操作步数。

## 做法
称 $b_i$ 为 $a_i$ 的差分数组。

当 $k = 0$ 时，答案为 $\sum _{i = 1} ^ n \max(0, b_i)$，[证明在这。](https://www.luogu.com.cn/article/d6a9cblj#:~:text=%E5%A6%82%E6%9E%9Cf%5Bi,%E6%89%80%E4%BB%A5ans%E4%B8%8D%E5%8F%98)

手模样例可以发现，若修改第 $x$ 个积木是优秀的，则一定是将它的高度修改为**左侧最近的未被修改的积木**的高度。

更进一步的，考虑从左到右逐个积木进行修改，在修改积木 $x$ 优秀的情况下一定是将其修改为积木 $x - 1$ 的高度。这样操作相当于和左侧捆绑，一起被操作，即自己不单独产生贡献了，答案肯定最优秀。

考虑 dp，设 $f_{i, j}$ 表示考虑完所有编号不超过 $i$ 的柱子，有 $j$ 个柱子产生了贡献，该情况下的最少操作步数。

转移时枚举上一个柱子的编号即可。

答案为 $f_{n, n - k}$，复杂度三次方。

---

## 作者：Getaway_Car (赞：1)

想必大家都会积木大赛。

若修改 $h_i$，考虑如何让它带来的贡献最小。根据积木大赛的结论，只需让 $h_i' \in [\min\{h_{i - 1}, h_{i + 1}\}, \max\{h_{i - 1}, h_{i + 1}\}]$，这个位置就不会带来任何的贡献，可以认为我们删除了第 $i$ 个位置。显然，$\forall i \in [1, n]$，总存在 $h_i'$ 满足以上条件。

那么问题就变成了，原本有 $n$ 个位置，可以删除最多 $k$ 个位置，求最小答案。于是自然而然地想到了 DP。

设 $dp_{i, j, k}$ 表示现在在第 $i$ 个位置，删除了 $j$ 个位置，上一个没有被删除的位置是 $k$ 的最小答案。转移方程：

$$
dp_{i, j, k} =
\left\{
\begin{aligned}
& dp_{i - 1, j - 1, k},\ k \in [0, i) \newline
& \min_{p \in [0, i)}\{dp_{i - 1, j, p} + \max\{h_i - h_p, 0\}\},\ k = i
\end{aligned}
\right.
$$

时间复杂度 $O(n^3)$。

[提交记录](https://atcoder.jp/contests/abc145/submissions/65585483)。

---

## 作者：Union_Find (赞：1)

本题解提供 $O(n^2\log n)$ 做法。

这种带修改的题可以先考虑不修改时怎么做。很简单可以想到，对于第 $i$ 列，如果 $h_i \le h_{i-1}$，那么第 $i$ 列就没有贡献，因为在前一列消除时一起消除即可。如果 $h_i > h_{i - 1}$，那么会产生 $h_i - h_{i - 1}$ 的贡献。

而如果有修改，我一开始想的是直接设为 $0$，但后来发现可能会隔断，使答案变大。

所以应该使得他在尽量不产生额外贡献的情况下修改是最好的。最容易想到的是令 $h_i = h_{i - 1}$，这样子就相当于将第 $i$ 列和第 $i - 1$ 列合并了，这一列的贡献就没了，相当于从原序列中抽出了一列。

这样我们就相当于从 $n$ 列中选出 $n - k$ 列，使得答案最小。容易想到 dp。

设 $f_{i,j}$ 表示前 $i$ 列选了 $j$ 列的最小答案。枚举上一次选的是哪一列。

$$f_{i,j} = \min \begin{Bmatrix}f_{k,j-1}+a_i-a_k(a_k < a_i)
  \\f_{k,j-1}(a_k \geq a_i)
\end{Bmatrix}$$

这样子就是 $O(n^3)$ 的，已经可以通过此题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 305
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n, k, a[N], f[N][N], ans = 1e18;
int main(){
	n = rd(), k = rd();
	for (int i = 1; i <= n; i++) a[i] = rd();
	memset (f, 0x3f, sizeof f);f[0][0] = 0;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= i; j++){
		for (int k = 0; k < i; k++)
			f[i][j] = min(f[i][j], f[k][j - 1] + (a[k] < a[i] ? a[i] - a[k] : 0));
	}for (int i = 0; i <= n; i++) ans = min(ans, f[i][n - k]);
	printf ("%lld\n", ans);
	return 0;
}

```

如果只是想过这题的可以撤了，接下来是 $O(n^2\log n)$。

考虑优化时间复杂度。我们发现如果我们把 $a_i$ 作为下标，转移的时候相当于两次区间最小值再求最小值。所以我们考虑使用线段树进行单点修改，区间求最小值。

因为两个式子不同，我们建立两种线段树。又因为 $j$ 的值会影响式子，所以给每个 $j$ 建立线段树。这样子我们就需要 $2n$ 个线段树。每次进行修改和查询，这样子就是 $O(n^2\log n)$ 的了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 305
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n, k, a[N], b[N], lisan[N], cnt, f[N][N], ans = 1e18;
struct ST{
	ll tr[N << 2];
	il void init(){memset (tr, 0x3f, sizeof tr);}
	void add(ll p, ll l, ll r, ll x, ll k){
		if (l == r) return tr[p] = min(tr[p], k), void(0);
		ll mid = (l + r) >> 1;
		if (x <= mid) add(p << 1, l, mid, x, k);
		else add(p << 1 | 1, mid + 1, r, x, k);
		tr[p] = min(tr[p << 1], tr[p << 1 | 1]); 
	}ll ask(ll p, ll l, ll r, ll nl, ll nr){
		if (nl <= l && r <= nr) return tr[p];
		ll mid = (l + r) >> 1, ans = 1e18;
		if (nl <= mid) ans = min(ans, ask(p << 1, l, mid, nl, nr));
		if (nr > mid) ans = min(ans, ask(p << 1 | 1, mid + 1, r, nl, nr));
		return ans;
	}
}t1[N], t2[N];
int main(){
	n = rd(), k = rd();
	for (int i = 1; i <= n; i++) a[i] = rd(), lisan[i] = a[i];
	sort (lisan + 1, lisan + n + 2);
	cnt = unique(lisan + 1, lisan + n + 2) - lisan - 1;
	for (int i = 1; i <= n; i++) b[i] = lower_bound(lisan + 1, lisan + cnt + 1, a[i]) - lisan;
	for (int i = 0; i <= n; i++) t1[i].init(), t2[i].init();
	t1[0].add(1, 1, cnt, 1, 0), t2[0].add(1, 1, cnt, 1, 0);
	memset (f, 0x3f, sizeof f);
	f[0][0] = 0;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= i; j++){
			f[i][j] = min(t1[j - 1].ask(1, 1, cnt, 1, b[i]) + a[i], t2[j - 1].ask(1, 1, cnt, b[i], cnt));
		}for (int j = 1; j <= i; j++){
			t1[j].add(1, 1, cnt, b[i], f[i][j] - a[i]), t2[j].add(1, 1, cnt, b[i], f[i][j]);
		}
	}for (int i = 0; i <= n; i++) ans = min(ans, f[i][n - k]);
	printf ("%lld\n", ans);
	return 0;
}

---

## 作者：大眼仔Happy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc145_f)

原来就我没做过[积木大赛](https://www.luogu.com.cn/problem/P1969)。

好了，现在做完了。然后发现 $K=0$ 的时候就是积木大赛。那 $K>0$ 呢？于是我又想到，最好就是改变某一条柱子，使得尽可能小的影响，那怎么修改呢？直接改成上一条柱子的长度就行了。那这一条柱子就没有贡献，相当于是不存在了。

于是我们把题目转化为，找 $N-K$ 条柱子，使得答案最小。显然就是一个 dp。设 $f_{i,j}$ 表示考虑了前 $i$ 个，并且选取第 $i$ 个，选取了 $j$ 个。方程就直接写了，自己推一下不难：

$$f_{i,j}=\min_{l<i} \Big\{f_{l,j-1}+\max(h_i-h_l,0)\Big \}$$

时间复杂度显然的 $O(N^3)$，不知道也不想知道能不能做到 $O(N^2)$，反正能过就行。管他呢。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=305;
#define ll long long
int inline read()
{
	int num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
int n,m;
ll h[N],f[N][N],ans=9e18;
int main(){
	n=read();m=n-read();
	if(!m)return printf("0"),0;
	for(int i=1;i<=n;i++)h[i]=read();
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int l=0;l<i;l++)
				f[i][j]=min(f[i][j],f[l][j-1]+max(h[i]-h[l],0ll));
	for(int i=1;i<=n;i++)ans=min(ans,f[i][m]);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Flash_Man (赞：1)

相当于从 $n$ 个中选出 $n-k$ 个统计答案。定义 $f(i,j)$ 表示最后一个选第 $i$ 个，已经选了 $j$ 个的最少操作次数。
$$
f(i,j)=\min_{p<i}\{f(p,j-1)+\max\{h_i-h_p,0\} \}
$$

```cpp
#include <bits/stdc++.h>
#define int long long
const int N = 300 + 3, inf = 1e18;
int n, k, h[N], f[N][N], ans = inf;
signed main() {
	scanf("%lld%lld", &n, &k), k = n - k;
	if (!k) return puts("0"), 0;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= k; j++) f[i][j] = inf;
	f[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &h[i]);
		for (int j = 1; j <= k; j++)
			for (int p = 0; p < i; p++)
				f[i][j] = std::min(f[i][j], f[p][j - 1] + std::max(h[i] - h[p], 0ll));
	}
	for (int i = 1; i <= n; i++) ans = std::min(ans, f[i][k]);
	printf("%lld\n", ans);
	return 0;
}
```

---


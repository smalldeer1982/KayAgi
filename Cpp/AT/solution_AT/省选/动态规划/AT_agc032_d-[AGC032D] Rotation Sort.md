# [AGC032D] Rotation Sort

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc032/tasks/agc032_d

$ \{\ 1,\ \ldots,\ N\ \} $ の順列 $ p\ =\ (p_1,\ \ldots,\ p_N) $ が与えられます。 あなたは、次の 2 種類の操作を好きな順序で繰り返し行うことができます。

- コスト $ A $ を支払う。 整数 $ l $ と $ r $ ($ 1\ \leq\ l\ <\ r\ \leq\ N $) を自由に選び、$ (p_l,\ \ldots,\ p_r) $ を左にひとつシフトする。 すなわち、$ p_l,\ p_{l\ +\ 1},\ \ldots,\ p_{r\ -\ 1},\ p_r $ をそれぞれ $ p_{l\ +\ 1},\ p_{l\ +\ 2},\ \ldots,\ p_r,\ p_l $ へ置き換える。
- コスト $ B $ を支払う。 整数 $ l $ と $ r $ ($ 1\ \leq\ l\ <\ r\ \leq\ N $) を自由に選び、$ (p_l,\ \ldots,\ p_r) $ を右にひとつシフトする。 すなわち、$ p_l,\ p_{l\ +\ 1},\ \ldots,\ p_{r\ -\ 1},\ p_r $ をそれぞれ $ p_r,\ p_l,\ \ldots,\ p_{r\ -\ 2},\ p_{r\ -\ 1} $ へ置き換える。

$ p $ を昇順にソートするために必要な総コストの最小値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 5000 $
- $ 1\ \leq\ A,\ B\ \leq\ 10^9 $
- $ (p_1\ \ldots,\ p_N) $ は $ \{\ 1,\ \ldots,\ N\ \} $ の順列である。

### Sample Explanation 1

$ (p_1,\ p_2,\ p_3) $ を左にひとつシフトすると、$ p\ =\ (1,\ 2,\ 3) $ となります。

### Sample Explanation 2

例えば、次のように操作を行えばよいです。 - $ (p_1,\ p_2,\ p_3,\ p_4) $ を左にひとつシフトする。 すると、$ p\ =\ (2,\ 3,\ 1,\ 4) $ となる。 - $ (p_1,\ p_2,\ p_3) $ を右にひとつシフトする。 すると、$ p\ =\ (1,\ 2,\ 3,\ 4) $ となる。 このとき、総コストは $ 20\ +\ 30\ =\ 50 $ です。

## 样例 #1

### 输入

```
3 20 30
3 1 2```

### 输出

```
20```

## 样例 #2

### 输入

```
4 20 30
4 2 3 1```

### 输出

```
50```

## 样例 #3

### 输入

```
1 10 10
1```

### 输出

```
0```

## 样例 #4

### 输入

```
4 1000000000 1000000000
4 3 2 1```

### 输出

```
3000000000```

## 样例 #5

### 输入

```
9 40 50
5 3 4 7 6 1 2 9 8```

### 输出

```
220```

# 题解

## 作者：installb (赞：18)

## AGC032D

这个做法应该比较简洁吧。

首先每一个数至多跑一次（从左往右或者从右往左或者不跑）因为如果让它跑两次相当于第一次就跑到第二次结束那地方就行，位置是可以任意选择的。  

我们先假定左移和右移**费用相同**，然后把数分成两类，**被移动**了和**未被移动**。显然，未被移动的数必须构成一个**上升子序列**，那些移动的数分为三种情况，我们对每一个移动的数分别考虑，假设这个移动的数为第 $i$ 个数 $a_i$。  

先任意找一个可行方案（已经把所有数分为被移动和未被移动）出来。

- 1.未被移动的数中存在 $j$，$j<i$ 且 $a_j>a_i$  
这个数应该往左移  
- 2.未被移动的数中存在 $j$，$j>i$ 且 $a_j<a_i$  
这个数应该往右移  
注意：由于子序列是上升的，**上面两种情况不可能同时出现**。  
- 3.上两种情况均不出现
这种情况在最优解种不可能出现，因为可以把这个数归到子序列里去，把它变成未被移动的数。

答案就是被移动的数的数量最小值乘以费用，前者等于总数减去最长上升子序列长度。

然后看左右移不同的情况，可以 dp 了，状态 $dp_i$ 代表将第 $i$ 个数选为**未被移动的数**，且前 $i$ 个数能够构成上升子序列（也就是这些数都已经被决定是哪一类了）时，最小需要的总花费。

决策变量 $j$ 枚举上一个处在上升子序列中的数是哪个，然后统计 $j$ 和 $i$ 中该左移和该右移的数分别有多少个。  

对于这个统计，只要倒序枚举 $j$，两个变量就完事，左移的数看起来不好统计，其实只要把上文所述的第一种、第三种情况都当成左移的数就可以了，也就是 $a_k<a_i$ 即左移 $k$。

然后代码出奇的短。

```cpp
using namespace std;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;

LL n,l,r;
LL a[5005],dp[5005];

int main(){
	memset(dp,0x3f,sizeof(dp));
	cin >> n >> r >> l;
	for(LL i = 1;i <= n;i ++){ cin >> a[i]; a[i] ++; }
	a[0] = 1; dp[0] = 0; a[n + 1] = n + 2;
    // 这里为了方便做把排列种每个数都加上 1 了
	for(LL i = 1;i <= n + 1;i ++){
		LL sr = 0,sl = 0;
		for(LL j = i - 1;j >= 0;j --){
			if(a[j] < a[i]) dp[i] = min(dp[i],dp[j] + r * sr + l * sl);
			if(a[j] > a[i]) sr ++; if(a[j] < a[i]) sl ++;
		}
	}
	cout << dp[n + 1] << endl;
	return 0;
}
```

---

## 作者：zzw4257 (赞：10)

>(转化后)给定一个排列$\{p_i\}$,你可以花费 $A$ 把一个元素插入到原始位置右侧的任何一个位置，$B$ 移动到左侧，求让排列升序的最小代价

首先证明一个引理:

>每个元素要么不操作，要么操作一次

考虑反证，假设一个元素做了多次操作并且其中两次操作实现了位置上 $x\to y$ 的变换，那么保证其余元素相对顺序不影响情况下，可以替换成一次

那么对所有的元素可以分成两类：动了的和没动的

再证明一个引理

>把不动的元素按照初始位置顺序取出是一个上升序列

考虑 $dp$ 这个序列

设 $f_{i,j}$ 表示对 $[1,i]$ 的操作状态已经确定，最后一个不动的元素的**值**是 $j$的最小代价

考虑两种情况

- $a_i>j$ 
	- $i$选择不动:$f_{i-1,j}\to f_{i,a_i}$
   - $i$选择右移:$f_{i-1,j}+A\to f_{i,j}$
- $a_i<j$
	- $i$只能左移:$f_{i-1,j}+B\to f_{i,j}$
    
解释一下要动的两个转移

首先理解一下，规定出来这个不动序列相对顺序是不变的，因此他们本质是一些层次，你在满足相对顺序后，选择动的点是可以在选择到的层次中随意排列的到自己的最后位置的，所以不要在意这些位置到底是什么时候移动并且到哪里的，你甚至可以把他们丢到整个序列确定之后再放到终止位置

对$a_i<j$我们能够理解$a_i$必须要向左跨过$j$，怎么到的终止位置随便

$a_i>j$则很有趣，设$a_x=j$,容易发现若$i$要左移$(x,i)$位置一定存在一个$> a_i$的，那么这个值$v$一定$>j$，因此一定会在一个状态$f_{i-1,v}$中转移到$i$左移的情况，所以这里我们钦定他右移是没有问题的

给一个小例子:

`1 2 3 5 4`

当你划分成

`1| 2| 3| 5 4`

时确实不会考虑到 $4$ 左移的情况

但

`1| 2| 3| 5| 4`

就会了

```cpp
#include<bits/stdc++.h>
#define N 5001
#define int long long
#define INF 0x3f3f3f3f3f3f3f3fll
using namespace std;
int n,A,B,a[N],ans=INF,f[N][N];
signed main(void){
	int i,j,mx,v;scanf("%lld%lld%lld",&n,&A,&B);
	for(i=1;i<=n;++i)scanf("%lld",a+i);
	memset(f,INF,sizeof f);
	for(f[0][0]=0,mx=a[i=1];i<=n;++i,mx=max(mx,a[i])){
		for(j=0;j<=mx;++j){
			v=f[i-1][j];
			if(a[i]>j)f[i][a[i]]=min(f[i][a[i]],v),f[i][j]=min(f[i][j],v+A);
			else f[i][j]=min(f[i][j],v+B);
		}
	}for(i=0;i<=n;++i)ans=min(ans,f[n][i]);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：EuphoricStar (赞：7)

设 $b_i$ 为 $i$ 在排列 $p$ 中的位置。那么每次操作相当于选择一个 $p_i$，将 $b_{p_i}$ 增加至 $k \in [i + 1, n]$，$b_{p_{i + 1}}, b_{p_{i + 2}}, \ldots, b_{p_k}$ 减少 $1$，花费 $A$；或者将 $b_{p_i}$ 减少至 $k \in [1, i - 1]$，$b_{p_{i - 1}}, b_{p_{i - 2}}, \ldots, b_{p_k}$ 增加 $1$，花费 $B$。

这样看起来还不是很好做，因为一次操作的影响太大了。注意到**我们只关心 $b_i$ 的相对大小关系**，$b_i$ 具体是什么不重要，因此我们考虑改变一下操作的描述：可以将 $b_{p_i}$ 增加或减少至**任意实数** $k \in [0, n + 1)$，花费分别为 $A, B$。

至此容易知道每个 $b_i$ 最多改变一次，且我们的目标是使得 $b$ 递增。容易设计一个 dp，$f_{i, j}$ 为操作后 $b_i \in [j, j + 1)$ 的花费最小值。

有转移：

- $\forall k \in [0, j], f_{i, j} \gets f_{i - 1, k} + \begin{cases} A & b_i \le j \\ B & b_i > j \end{cases}$，表示 $b_i$ 取 $(j, j + 1)$ 的小数。
- $\forall k \in [0, j - 1], f_{i, j} \gets f_{i - 1, k} + \begin{cases} A & b_i < j \\ 0 & b_i = j \\ B & b_i > j \end{cases}$，表示 $b_i$ 取整数 $j$。

容易维护 $f_i$ 的前缀 $\min$ 做到 $O(n^2)$。

[code](https://atcoder.jp/contests/agc032/submissions/43710259)

---

## 作者：Miraik (赞：4)

我觉得这个D比最近某些场次的AB简单的多。。。

考虑这个操作的本质，就是把一个数字往后插入，耗费 $A$ 的代价；把一个数字往前插入，耗费 $B$ 的代价。

那显然一个数最多操作一次，不操作的部分一定单调递增，那我们直接 DP 那个不操作的部分就好了。

设 $f_{i,j}$ 表示当前处理到第 $i$ 个数，留下的最后一个数为 $j$ 的最小代价。

$f_{i,j}=\begin{cases}f_{i-1,j}+A&a_i>j\\f_{i-1,j}+B&a_i<j\\f_{i-1,k} \space (k<a_i)&a_i=j\end{cases}$

直接转移即可，时间复杂度 $O(n^2)$。

用一个线段树做区间加区间求 $\min$ 还可以做到 $O(n \log n)$。

---

## 作者：Kinandra (赞：3)

标签: DP, 线段树

将一个区间最左边的数到区间最右边等价与把一个数向右移动. 也就是说我们可以花费 $A$ 右移一个数, 花费 $B$ 左移一个数. 易知每个数最多只需要移动一次.

设 $f(i,j)$ 表示扫描完前 $i$ 个元素, 把 $>j$ 的数全部右移(这些数可以通过适当调整从而保证升序), 其余数(要求包含 $j$ )为升序的最小花费.

转移很简单, 假设第 $i+1$ 个数为 $x$ , 有三种转移:

- $j<x$
  - 把 $x$ 接在 $j$ 后:  $f(i,j)\to f(i,x)$ 
  - 右移 $x$ :  $f(i,j)+A\to f(i,j)$
- $j>x$ 
  - 左移 $x$ 到一个合适的位置: $f(i,j)+B\to f(i,j)$

细品发现: 第一种转移相当于对一个前缀查询最小值和单点修改, 第二, 三种转移相当于区间加. 线段树维护即可.

时间复杂度 $\mathcal O(n\log n)$ .

```cpp
#include <bits/stdc++.h>
#define inf 10000000000000ll
using namespace std;
int read();
int n, a, b;

#define root 0, n, 1
#define ls l, mid, k << 1
#define rs mid + 1, r, k << 1 | 1
struct Seg {
    long long tmn[400005], tag[400005];
    void Tag(int k, long long v) { tmn[k] += v, tag[k] += v; }
    void psd(int k) {
        Tag(k << 1, tag[k]), Tag(k << 1 | 1, tag[k]), tag[k] = 0;
    }
    void update(int k) { tmn[k] = min(tmn[k << 1], tmn[k << 1 | 1]); }
    void build(int l, int r, int k) {
        if (l == r) return tmn[k] = l ? inf : 0, void();
        int mid = l + r >> 1;
        build(ls), build(rs), update(k);
    }
    void modi(int l, int r, int k, int p, long long v) {
        if (l == r) return tmn[k] = v, void();
        psd(k);
        int mid = l + r >> 1;
        p <= mid ? modi(ls, p, v) : modi(rs, p, v), update(k);
    }
    long long qry(int l, int r, int k, int st, int en) {
        if (st > r || en < l) return inf;
        if (st <= l && en >= r) return tmn[k];
        psd(k);
        int mid = l + r >> 1;
        return min(qry(ls, st, en), qry(rs, st, en));
    }
    void add(int l, int r, int k, int st, int en, int v) {
        if (st > r || en < l) return;
        if (st <= l && en >= r) return Tag(k, v);
        psd(k);
        int mid = l + r >> 1;
        add(ls, st, en, v), add(rs, st, en, v), update(k);
    }
} seg;

int main() {
    n = read(), a = read(), b = read();
    seg.build(root);
    for (int i = 1, x; i <= n; ++i) {
        x = read(), seg.modi(root, x, seg.qry(root, 0, x));
        seg.add(root, 0, x - 1, a), seg.add(root, x + 1, n, b);
    }
    printf("%lld\n", seg.qry(root, 0, n));
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
int read() {
    int x = 0, f = 1;
    char c = gc;
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x * f;
}
```

---

## 作者：zhujiahao114514 (赞：2)

我觉得这个 D 比 C 简单。

# 题意
先理解一下题意，把一个点向左向右移动。但是移动的代价不一样，求将原序列变成上升的序列的最小代价。


# 思路
首先注意到最优解中没有被移动的数肯定会构成一个极长上升子序列，（这是一个很重要的性质）。所以如果我们决定好了哪些数没被移动，剩下的数移动方向就确定了。代价也就确定了。

1. 若他比之前一个不动的点小，则要把他花费b的代价前移。
   
2. 若他比之后一个不动的点大，则要把他花费a的代价后移

3. 其他情况，则他是不动点的一员。

可以考虑动态规划。

设 $f_{i}$ 表示考虑前 $i$ 个数，并且第 $i$ 个数在选出的子序列中时的最小代价。转移从后往前枚举 $j$ 时我们需要维护区间中往两侧移的个数，再乘上花费的代价，就可以求出来了。

综上所述，根据上述性质，可以直接通过当前数是否大于  $a_{i}$ 来判断。时间复杂度 $O(n^{2})$ ，可以通过本题。

# code
~~~
#include<bits/stdc++.h>
using namespace std;
int n,aa,b;
long long a[5005];
long long dp[5005]; 
int main()
{
	cin>>n>>aa>>b;
	for(int i=1;i<=n;i++) cin>>a[i];
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0; 
	a[n+1]=n+1;   //方便处理
	for(int i=1;i<=n+1;i++)
	{
		long long sl=0,sr=0;
		for(int j=i-1;j>=0;j--)
		{
  			if(a[j]<a[i]) dp[i]=min(dp[i],dp[j]+aa*sr+b*sl);   //计算代价，有sr个向后移的，sl个向前移的
			if(a[j]>a[i]) sr++;  //统计向后移动的个数
			if(a[i]>a[j]) sl++;  //统计向前移动的个数
		}
	}
	cout<<dp[n+1];
	return 0;
}

~~~

请管理员大大给过。

---

## 作者：Velix (赞：2)

小清新DP题，思路不难。

---
将操作的理解一下，可以转换成任意插入，但是插入到左边和右边的代价不一样，求变成上升序列的最小代价。

首先是一个显而易见的结论，整个序列中若有一些数没有被操作过，那么这些数一定构成一个上升子序列。

那么DP的想法就自然出来了，设 $f_i$ 表示以 $i$ 为结尾的上升子序列，然后递推。

现在考虑转移。（以下默认 $i<j$）

- 对于 $a_j>a_i$，其对 $f_i$ 的贡献为 $A$；
- 对于 $a_j<a_i$，其对 $f_i$ 的贡献为 $B$；

可能有人已经想到了：不对啊，你这个递推式在存在 $j<k<i$ 且 $a_j<a_k<a_i$ 的时候就不行了啊，最优时 $k$ 不会移动，假算法！

事实上， $f_k$ 已经将 $k$ 不移动的方案包括在内了，答案不会因此而出现错误。

因此最终的递推式为

$$f_i=\min\limits_{j<i,a_j<a_i}f_j+(A\sum\limits_{k=j+1}^{i-1}[a_k<a_i]+B\sum\limits_{k=j+1}^{i-1}[a_k>a_i])$$

后面的式子可以倒序递推，用一个变量维护。

为了方便统计答案，可以在排列的最后插入一个 $n+1$。

时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define N 5010
typedef long long ll;
using namespace std;
ll f[N],n,a[N],A,B;
int main()
{
	cin>>n>>A>>B;
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	memset(f,0x3f,sizeof f);
	f[0]=0;a[n+1]=n+1;
	for(int i=1;i<=n+1;i++)
	{
		ll cnt=0;
		for(int j=i-1;j>=0;j--)
			if(a[j]<a[i])f[i]=min(f[i],f[j]+cnt),cnt+=A;
			else cnt+=B;
	}
	cout<<f[n+1];
}
```


---

## 作者：shiruoyu114514 (赞：1)

一种与众不同的做法。

首先 $A$ 操作相当于把一个数往右移，$B$ 操作相当于把一个数往左移。

我们考虑从小往大考虑值。具体来说，讨论最小值所在位置怎么操作。

1. 不动。此时要求最小值左边的所有位置都往右移动。由于它们能等到另一边排好序之后统一往右移动到它们应该在的位置，所以额外的代价只有把左边东西往右挪以及把右边原本的排好的代价。

2. 往左移。此时额外的代价只需要其它位置排好就行了。

根据这个思想，我们能够设计一种 DP：令 $dp_{i,j}$ 为排好值在 $[i,n]$，并且原本位置在 $[j,n]$ 的最小代价。

转移方程：

不动：

$$dp_{i,j} \leftarrow cnt_{j,r_i,i}A+dp_{i+1,r_i+1}$$

往左移：

$$dp_{i,j} \leftarrow B[cnt_{j,n,i}\neq cnt_{j,n,i+1}]+dp_{i+1,j}$$

其中 $cnt_{p,q,i}$ 为原始数列中下标在 $[p,q]$ 间值大于 $i$ 的值的个数，$r_i$ 满足 $p_{r_i}=i$。

时间复杂度 $O(n^2)$。


```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long

int n,a,b;
const int maxn=5000;

int dp[maxn+5][maxn+5];
int P[maxn+5];
int pos[maxn+5];
int cnt[maxn+5][maxn+5];
//前 j 个数大于等于 i 的数有多少个 

int calcnum(int gre,int l,int r){
	return cnt[gre][r]-cnt[gre][l-1];
}

signed main(){
	cin>>n>>b>>a;
	for(int i=1;i<=n;i++){
		cin>>P[i];
		pos[P[i]]=i;
		cnt[P[i]][i]++;
	}
	for(int i=n;i>=1;i--){
		for(int j=1;j<=n;j++){
			cnt[i][j]+=cnt[i+1][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cnt[i][j]+=cnt[i][j-1];
		}
	}
	for(int p=n;p>=1;p--){
		for(int v=n;v>=1;v--){
			if(calcnum(v,p,n)==calcnum(v+1,p,n)){
				dp[p][v]=dp[p][v+1];
				continue;
			}
			int Pos=pos[v];
			dp[p][v]=min(dp[p][v+1]+a,dp[Pos+1][v]+b*calcnum(v+1,p,Pos));
			//cout<<p<<" "<<v<<" "<<dp[p][v]<<"\n";
		}
	}
	cout<<dp[1][1];
}
```

---

## 作者：o51gHaboTei1 (赞：1)

#### D

感觉没有 C 困难。

我们考虑一个数显然不会移动超过 $1$ 次，因为如果移动超过 $1$ 次那还不如直接移动到那个位置去，或者将其放在最后操作啥的都行！

这样每个数只有可能动或不动了。我们发现对于移动的数也可以默认它们进行了一次移动后就不会动了，否则也可以通过上述的调整法进行调整。

并且不动的数构成一个上升子序列，否则存在逆序对一定会使原序列不是上升的。

一个直观的想法是我们直接枚举不动的最长上升子序列，然后子序列内相邻两数之间夹的数都可以唯一确定向左移还是向右移，然后就可以计算代价了。不难想到用 dp 辅助这个过程，

于是我们想到设 $dp_{i,0/1}$ 表示前 $i$ 个数确定动或不动时第 $i$ 个数动/不动的最小代价，但是发现假如要转移只可能能枚举 $dp_{j,0/1}$，还转移不了！我们考虑换一换状态的设计。

设 $dp_{i,j}$ 表示前 $i$ 个数确定好动/不动时，最后一个不动的数值为 $j$ 的最小代价。

讨论。若 $a_i > j$，则 $dp_{i,a_i} \leftarrow dp_{i - 1,j},dp_{i,j} \leftarrow dp_{i-1,j} + A$；

若 $a_i < j$，则 $dp_{i,j} \leftarrow dp_{i-1,j} + B$。

显然就是对应的必须向右移动或是向左移动。

这里有一个想要细讲的地方：在 $a_i > j$ 时，我们选择了 $dp_{i,j} \leftarrow dp_{i-1,j} + A$ 的转移，对于两个固定不动的数之间夹的数记为 $a,b$，如果出现了 $a_i > a$，但我们没选择 $a_i$ 作为不动的数而是选择了 $b$，那么显然 $a_i > b$ 不然也可以贪心地加入当前状态，必须向右移动；对于最后一个固定不动的数之后的数，设为 $c$ 如果后面有 $a_i > c$，则显然我们也可以贪心地令 $a_i$ 不动。则最后固定的数 $c$ 之后所有的 $a_i$ 都保证 $a_i < c$，必须向左移动。

时空复杂度 $O(n ^ 2)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
#define ll long long
const int Len = 5e3 + 5;
const ll Inf = 1e15;
int n,m,a[Len],A,B;
ll dp[Len][Len];
/*dp_{i,j} 前 i 个确定最后一个值是 j。
对于 a_i > j,dp_{i,a_i} = dp_{i-1,j},dp_{i,j} = dp_{i - 1,j} + A
a_i < j,dp_{i,j} = dp_{i-1,j} + B 
*/
int main()
{
	scanf("%d %d %d",&n,&A,&B);
	for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
	for(int i = 0 ; i <= n ; i ++) for(int j = 0 ; j <= n ; j ++) dp[i][j] = Inf;
	dp[1][a[1]] = 0;
	dp[1][0] = A;
	for(int i = 2 ; i <= n ; i ++) 
	{
		for(int j = 0 ; j <= n ; j ++)
		{
			if(a[i] > j) dp[i][a[i]] = min(dp[i - 1][j] , dp[i][a[i]]) , dp[i][j] = min(dp[i][j] , dp[i - 1][j] + A);
			else dp[i][j] = min(dp[i][j] , dp[i - 1][j] + B);
		}
	}
	ll as = Inf;
	for(int i = 0 ; i <= n ; i ++) as = min(as , dp[n][i]);
	printf("%lld\n",as);
	return 0;
}
```

---

## 作者：Mirasycle (赞：0)

本题如果直接去思考变动序列的变化情况，其实是比较难做的。我们并不知道该把目前的数移到哪个位置，因为后面的其他数字变动会影响当前的数字移动的位置。

所以转化思路，我们考虑哪些是不动了。确定不动的序列（这是一个单调递增的数列）的之后，其他数字根据相对大小关系就可以确定往前放还是往后放，付出 $A$ 或 $B$ 的代价。

设 $f_{i,j}$ 表示处理了前面 $i$ 个数，当前不动序列的最后一个数字为 $j$。根据 $a_i$ 和 $j$ 大小关系，还有是否选择 $a_i$ 作为不动序列来转移。

$$f_{i,j}=\begin{cases}
f_{i-1,j}+A&a_i>j\\
f_{i-1,j}+B&a_i<j\\
\min\limits_{k<a_i} f_{i-1,k}&a_i=j
\end{cases}$$

可能咋一看第一个转移有点小问题，就是 $a_i>j$ 不一定是要往后放啊，可能后面的移动到前面这个的位置就正确了。但其实这个决策是被包含在了第三个方程里面所以这个转移没有问题。

本题数据小，直接暴力转移 $O(n^2)$ 即可。

---

## 作者：zifanwang (赞：0)

考虑确定哪些点不动，这些点一定构成一个单调递增子序列，那么对于剩下的点：

- 若在它之前存在一个不动点大于它，则需要花费 $b$ 的代价向前移动。
- 若在它之后存在一个不动点小于它，则需要花费 $a$ 的代价向后移动。
- 如果两个都不存在，则它一定可以加入不动点序列。

考虑 dp，记 $f_{i,j}$ 表示考虑完前 $i$ 个数，最后一个不动点的值为 $j$ 的最小代价，直接转移时间复杂度 $\mathcal O(n^2)$，加个线段树优化可以做到 $\mathcal O(n\log n)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 5003
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rept(i,a,b) for(int i=(a);i<(b);++i)
using namespace std;
int n,a,b,d[mxn];
ll ans=1e18,f[mxn][mxn];
signed main(){
	scanf("%d%d%d",&n,&a,&b);
	rep(i,1,n)scanf("%d",&d[i]);
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	rep(i,1,n){
		ll mn=1e18;
		rep(j,0,n){
			if(j<d[i])f[i][j]=f[i-1][j]+a;
			else if(j>d[i])f[i][j]=f[i-1][j]+b;
			else f[i][j]=mn;
			mn=min(mn,f[i-1][j]);
		}
	}
	rep(i,0,n)ans=min(ans,f[n][i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：lupengheyyds (赞：0)

## 题面

给定一个排列。
你可以花 $A$ 的代价把一个数往左移任意距离；花 $B$ 的代价把一个数往右移任意距离。
要把整个排列排序至少需要多少代价。

$n\le 5000$

## 题解

分析过程可知，答案一定为一个上升序列不动，其他数左右移动，于是令 $dp_{i}$ 表示考虑前 $i$ 个数，让以 $i$ 结尾的上升子序列不动，其余数移动的方案数，则有：

$$
dp_{i}=\min_{j<i}dp_j+res_{j+1,i-1}
$$

其中 $res_{i,j}$ 表示将 $[i,j]$ 中的数移动至两边的权值，令 $res_{0,i,j}$ 表示区间 $[i,j]$ 不得不向左移的数的数量，$res_{1,i,j}$ 表示区间 $[i,j]$ 中不得不向右移的数的数量，有：

$$
\begin{aligned}
&res_{0,i,j}=res_{0,i,j-1}+[a_j<a_{i-1}]\\
&res_{1,i,j}=res_{1,i-1,j}+[a_i<a_{j+1}]\\
&res_{i,j}=res_{0,i,j}\times B+res_{1,i,j}\times A+(j-i+1-res_{0,i,j}-res_{1,i,j})\times \min(A,B)
\end{aligned}
$$

于是 $\mathcal O(n^2)$ 可解

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int NN=5e3+5,MOD=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
int dp[NN],res[2][NN][NN],ans[NN][NN],n,A,B,a[NN];
signed main(){
	cin>>n>>A>>B;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			res[0][i+1][j]=res[0][i+1][j-1]+(a[j]<a[i]);
	for(int i=n;i>=1;i--)
		for(int j=i-1;j>=1;j--)
			res[1][j][i-1]=res[1][j+1][i-1]+(a[j]>a[i]);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ans[i][j]=res[0][i][j]*B+res[1][i][j]*A;
			int len=j-i+1;
			ans[i][j]+=(len-res[0][i][j]-res[1][i][j])*min(A,B);
		}
	}	
	memset(dp,0x3f,sizeof dp);
	dp[0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			if(a[j]<a[i]){
				int tmp=dp[i];
				dp[i]=min(dp[i],dp[j]+ans[j+1][i-1]);
			}
		}
	}
	int fans=INF;
	for(int i=1;i<=n;i++)fans=min(fans,dp[i]+ans[i+1][n]);
	cout<<fans;
	return 0;
}
```

---

## 作者：IYSY2009I (赞：0)

首先发现一个性质：如果一种方式是最优解，那么排列中的某个数要么不移动，要么只移动一次。

进一步探索可以得到：假如我们已经确定了哪些数字是原封不动的（当然这些数字组成了一个上升的子序列），那么其它数字向左移动还是向右移动也可以知道。

因此我们可以设 $f_i$ 表示已经考虑了前 $i$ 个数字（第 $i$ 个数字不动）的最小花费。然后转移就考虑上一个固定的数是什么。假如 $p_i<p_j$ 且 $i<j$ 我们就可以用 $f_i+cost$ 更新 $f_j$，其中 $cost$ 表示移动 $i$ 和 $j$ 之间的花费，所以接下来怎么求 $cost$ 就是个问题。

对于一个要移动的数 $x$，如果 $x>i$，那么就向右移动，否则往左移动。

这个时候就有问题了，对于 `1 2 3`，假如 `1 3` 是固定的，那么 `2` 怎么移呢？

答案是无论怎么移动都不优（都不可能更新答案），所以当作向右移动就可以了。

代码实现时注意 `dp` 数组的初始化和边界条件。

代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int p[5005];
long long dp[5005];
int main(){
	int n;
	long long a,b;
	scanf("%d%lld%lld",&n,&a,&b);
	for(int i=1;i<=n;i++){
		scanf("%d",&p[i]);
		dp[i]=1e18;
	}
	long long ans=1e18;
	long long cst=0;
	for(int i=1;i<=n;i++)
		dp[i]=(i-1)*a;
	dp[1]=0;
	for(int i=1;i<=n;i++){
		cst=0;
		for(int j=i+1;j<=n;j++){
			if(p[j]>p[i]){
				dp[j]=min(dp[j],dp[i]+cst);
				cst+=a;
			}
			else cst+=b;
		}
		ans=min(ans,dp[i]+cst);
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：xht (赞：0)

## [Rotation Sort](https://atcoder.jp/contests/agc032/tasks/agc032_d)

### 题意

- 给定一个 $1 \sim n$ 的排列 $p$，你要将其变成升序。
- 有两种操作：
  - 选择一个 $l,r$ 满足 $1 \le l < r \le n$，将 $p_{l\dots r}$ 替换为 $p_{l+1\dots r},p_l$，代价为 $a$。
  - 选择一个 $l,r$ 满足 $1 \le l < r \le n$，将 $p_{l\dots r}$ 替换为 $p_{r},p_{l\dots r-1}$，代价为 $b$。
- 求最小代价。
- $n \le 5\times 10^3$。

### 题解

显然操作等价于将某个数左移或者右移。

考虑 DP，设 $f_{i,j}$ 表示考虑前 $i$ 个数，其中最后一个没有被移动的数为 $j$ 的最小代价，分 $a_i > j$ 和 $a_i < j$ 转移即可，时间复杂度 $\mathcal O(n^2)$。

### 代码

```cpp
const int N = 5e3 + 7;
const ll inf = 1e18;
int n, a, b, p[N];
ll f[N][N], ans = inf;

int main() {
	rd(n, a, b), rda(p, n);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			f[i][j] = inf;
	f[0][0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= n; j++)
			if (p[i] > j)
				f[i][j] = min(f[i][j], f[i-1][j] + a),
				f[i][p[i]] = min(f[i][p[i]], f[i-1][j]);
			else f[i][j] = min(f[i][j], f[i-1][j] + b);
	for (int i = 0; i <= n; i++) ans = min(ans, f[n][i]);
	print(ans);
	return 0;
}
```

---

## 作者：SentoAyaka (赞：0)

提供一个不一样的 $O(n^2\log n)$ 做法。

观察操作形式，发现我们可以任选区间，转化成选择一个数，将其任意地插入到左边/右边，代价为 $B/A$ 。

对于一个序列，我们考察当前最小值，方便的我们设为 $1$。

对于 $1$ 及前面部分，我们有两种选法：

- 将 $1$ 插入到序列最前面。
- 将前面所有数插入到 $1$ 后面。注意插入是任意的，于是我们可以贪心的将 $1$ 后面部分操作到有序后再逐一插入前面的所有数。

发现这两种选择都是递归到子问题，考虑 dp。

设 $f_{i,j}$ 表示以 $i$ 开始的后缀，只考虑 $\ge j$ 的字符，使其升序的最小花费。

先通过主席树找到当前最小值 $x$，及其出现位置 $p$。

对于第一种转移，$f_{i,j}\leftarrow f_{i,x+1}+B$。

对于第二种转移，$f_{i,j}\leftarrow f_{p+1,x+1}+A\times cnt$。其中 $cnt$ 表示 $i\sim p-1$ 中 $\ge x$ 的数的个数，主席树计算即可。

注意当 $p=i$ 时也即 $i$ 前面没有数时不进行第一种转移，优化时间。

代码中 dp 用记忆化搜索实现。

```cpp
#include<bits/stdc++.h>
#define db double
#define int ll
#define ll long long
#define ull unsigned long long
#define pb emplace_back
#define MP make_pair
#define pii pair<int, int>
#define vec vector<int>
#define fi first
#define se second
#define ls(k) t[k].lc
#define rs(k) t[k].rc
#define CLK (double)clock()/(double)CLOCKS_PER_SEC
using namespace std;
mt19937 rnd(time(0));
inline int read(){
    register int x=0,f=1;
    register char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
inline void write(register int x){
    if(x<0){putchar('-');x=-x;}
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const int N=5005,inf=1e18;
int n,A,B,a[N],pos[N],rt[N],tot,f[N][N];
struct node{int lc,rc,sum;}t[N*40];
void modify(int p,int &q,int lt,int rt,int pos){
    t[q=++tot]=t[p],t[q].sum++;
    if(lt==rt)return ;
    int mid=lt+rt>>1;
    if(pos<=mid)modify(ls(p),ls(q),lt,mid,pos);
    else modify(rs(p),rs(q),mid+1,rt,pos);
}
int query(int p,int q,int lt,int rt,int qx,int qy){
    if(t[q].sum-t[p].sum==0||qx>rt||qy<lt)return 0;
    if(lt==rt)return lt;
    if(qx<=lt&&rt<=qy){
        int mid=lt+rt>>1;
        if(t[ls(q)].sum-t[ls(p)].sum==0)return query(rs(p),rs(q),mid+1,rt,qx,qy);
        else return query(ls(p),ls(q),lt,mid,qx,qy);;
    }
    int mid=lt+rt>>1,tmp=query(ls(p),ls(q),lt,mid,qx,qy);;
    if(tmp)return tmp;
    else return query(rs(p),rs(q),mid+1,rt,qx,qy);
}
int count(int p,int q,int lt,int rt,int qx,int qy){
    if(qx>rt||qy<lt)return 0;
    if(qx<=lt&&rt<=qy)return t[q].sum-t[p].sum;
    int mid=lt+rt>>1;
    return count(ls(p),ls(q),lt,mid,qx,qy)+count(rs(p),rs(q),mid+1,rt,qx,qy);
}
int dfs(int i,int j){
    if(i>=n||j>n)return 0;
    if(f[i][j]!=-1)return f[i][j];
    int x=query(rt[n+1],rt[i],1,n,j,n),p=pos[x];
    if(!x)return 0;
    int cnt=count(rt[p],rt[i],1,n,x+1,n),res=cnt?B+dfs(i,x+1):inf;
    res=min(res,cnt*A+dfs(p+1,x+1));
    return f[i][j]=res;
}
void MAIN(){
    n=read(),A=read(),B=read();
    for(int i=1;i<=n;i++)a[i]=read(),pos[a[i]]=i;
    for(int i=n;i>=1;i--)modify(rt[i+1],rt[i],1,n,a[i]);
    memset(f,-1,sizeof f);cout<<dfs(1,1);
}
signed main(){
    freopen("read.in","r",stdin);
//	freopen("write.out","w",stdout);
    int T=1;while(T--)MAIN();
//  printf("\nTIME:%lf\n",(double)clock()/CLOCKS_PER_SEC);
    return 0;
}
```


---

## 作者：lzk5627 (赞：0)

orz线段树Dra

这题考虑设状态 $f_{i,j}$ 表示考虑了前 $i$ 个数,其中 $\le j$ 的数都已经变成升序了,而 $>j$ 的数都选择的往右的最小代价

然后就有转移

* $j< a_i$ ,$f_{i,j}=f_{i-1,j} + B$ 
* $j> a_i$ ,$f_{i,j}=f_{i-1,j} + A$
* $j = a_i$ ,$f_{i,j}=f_{i,k},k<a_i$

发现第一个和第二个都可以直接转移,而第三个就是一个前缀最小值,所以可以在
$O(n^2)$的复杂度内解决,当然如果把第一个和第二个看做区间加,用线段树维护也是可以的,但是没有必要

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
long long s[N],p[N],f[N];
int n,A,B;
int main(){
	freopen("1.out","w",stdout);
	freopen("1.in","r",stdin);
	memset(f,23,sizeof(f));
	scanf("%d%d%d",&n,&A,&B),f[0]=0;
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);
		for(int j=0;j<=n;j++)
			if(j)	p[j]=min(p[j-1],f[j]);
			else	p[j]=f[j];
		for(int j=0;j<=x;j++)	f[j]+=A;
		for(int j=x+1;j<=n;j++)	f[j]+=B;
		f[x]=min(f[x],p[x]);
	}
	long long ans=f[n+1];
	for(int i=0;i<=n;i++)	ans=min(ans,f[i]);
	printf("%lld\n",ans);
	return 0;
}

```

---


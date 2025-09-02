# [ARC140C] ABS Permutation (LIS ver.)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc140/tasks/arc140_c

$ (1,\dots,N) $ の順列 $ P=(P_1,P_2,\ldots,P_N) $ の**嬉しさ**を以下で定義します。

- 長さ $ N-1 $ の数列 $ A=(A_1,A_2,\ldots,A_{N-1}) $ を、$ A_i\ =\ |P_i-P_{i+1}|(1\leq\ i\ \leq\ N-1) $ で定める。 $ A $ の最長狭義単調増加部分列の長さを $ P $ の嬉しさとする。

$ P_1\ =\ X $ を満たす順列 $ P $ のうち、嬉しさが最大になるものを一つ出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ X\ \leq\ N $
- 入力は全て整数

### Sample Explanation 1

$ A=(1,2) $ となるので、$ P $ の嬉しさは $ 2 $ です。これが達成可能な嬉しさの最大であるため、出力は条件を満たします。

### Sample Explanation 2

$ A=(1,1) $ となるので、$ P $ の嬉しさは $ 1 $ です。これが達成可能な嬉しさの最大であるため、出力は条件を満たします。

## 样例 #1

### 输入

```
3 2```

### 输出

```
2 1 3```

## 样例 #2

### 输入

```
3 1```

### 输出

```
1 2 3```

# 题解

## 作者：loser_seele (赞：2)

一个很不错的构造题。

首先不难想到答案的上界为 $ N-1 $，即 $ A=\{1,2,...,N-1\} $。下面假设 $ N $ 总是奇数。

于是考虑如何构造出这样的 $ A $，当 $ A $ 的长度为偶数且 $ X=\frac{N}{2}+1 $ 的时候显然可以构造出 $ \{X+1,X,X+2,X-1,...,1,N\} $ 即可。

如果 $ X $ 不为这个值，上面的构造就失效了。

但发现还有一种答案为 $ N-2 $ 的构造方案：将除了 $ X $ 外的数分为 $ L,R $ 两个部分，满足 $ L_1<L_2<...<L_{\frac{N}{2}}<R_1<R_2<...<R_{\frac{N}{2}} $，然后将 $ L,R $ 两两配对。

所以最后答案为 $ \{X,L_{\frac{N}{2}},R_1,...,L_1,R_{\frac{N}{2}} \} $。

$ N $ 为偶数的情况类似，不详述。

时间复杂度 $ \mathcal{O}(n) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
const int N = 4e5+5;
int n,x;
vector<int> ans;
void solve()
{
	cin>>n>>x;
	cout<<x<<' ';
	for(int i=1;i<=n;++i) 
	if(i!=x) 
	ans.push_back(i);
	if(n%2==0 && x==n/2) 
	reverse(ans.begin(), ans.end());
	int t=(n-2)/2;
	for(int i=1;;i++)
	{
		cout<<ans[t]<<' ';
		if(i % 2==1)
		t=i+t;
		else 
		t=t-i;
		if(t<0 || t>n-2)
		break;
	}
}
int main()
{
	solve();
}
```


---

## 作者：DHeasy (赞：1)

先说结论，答案至少为 $n-2$。

接下来考虑构造。

如果 $x$ 是 $n$ 的一半，可以构造 $x,x-1,x+1,\cdots,1,n$，发现这样答案一定最大。

如果 $x$ 不是 $n$ 的一半，考虑第二个数构造 $n$ 的一半，然后在像上一个一样构造，注意 $x$ 不要算重了。

#### 如果 $n$ 为偶数

这样需要分类讨论 $n$ 的一半是 $\frac{n}{2}$ 还是 $\frac{n}{2}+1$。然后再做。

还有一些细节，具体参考代码。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
inline ll read(){
	ll res=0ll,f=1;
	char c;
	for(;(c=getchar())<'0'||c>'9';c=='-'?f=-f:0);
	while(c>='0' && c<='9') res=(res<<1) + (res<<3) + c-'0',c=getchar();
	return res*f;
}
inline ll Max(re ll x,re ll y){return x>y?x:y;}
inline ll Min(re ll x,re ll y){return x<y?x:y;}
inline void cmax(re auto &x,re auto y){x=Max(x,y);}
inline void cmin(re auto &x,re auto y){x=Min(x,y);}
/*-----------------*/
const int N=2e5+10;
int n,x,a[N];
int main(){
	n=read();x=read();a[1]=x;
	if(n&1){
		if((n+1)/2==x){
			for(re int i=x-1,j=2;i;i--,j+=2) a[j]=i;
			for(re int i=x+1,j=3;i<=n;i++,j+=2) a[j]=i;
		}
		else if(x<(n+1)/2){
			a[2]=(n+1)/2;
			for(re int i=a[2]+1,j=3;i<=n;i++,j+=2) a[j]=i;
			for(re int i=a[2]-1,j=4;i;i--,j+=2){
				if(i==x) i--;
				if(i) a[j]=i;
				else break;
			}
		}
		else if(x>(n+1)/2){
			a[2]=(n+1)/2;
			for(re int i=a[2]-1,j=3;i;i--,j+=2) a[j]=i;
			for(re int i=a[2]+1,j=4;i<=n;i++,j+=2){
				if(i==x) i++;
				a[j]=i;
			}
		}
	}
	else{
		if(n/2==x){
			for(re int i=x+1,j=2;i<=n;i++,j+=2) a[j]=i;
			for(re int i=x-1,j=3;i;i--,j+=2) a[j]=i;
		}
		else if(n/2+1==x){
			for(re int i=x-1,j=2;i;i--,j+=2) a[j]=i;
			for(re int i=x+1,j=3;i<=n;i++,j+=2) a[j]=i;
		}
		else if(x<n/2){
			a[2]=n/2+1;
			for(re int i=a[2]-1,j=3;i;i--,j+=2){
				if(i==x) i--;
				if(i) a[j]=i;
				else break;
			}
			for(re int i=a[2]+1,j=4;i<=n;i++,j+=2) a[j]=i;
		}
		else{
			a[2]=n/2;
			for(re int i=a[2]+1,j=3;i<=n;i++,j+=2){
				if(i==x) i++;
				a[j]=i;
			}
			for(re int i=a[2]-1,j=4;i;i--,j+=2) a[j]=i;
		}
	}
	for(re int i=1;i<=n;i++) printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：KaruAWA (赞：1)

看到题目应该比较容易想到以下两点：

1. 贪心地让 $b$ 相邻两项之间的差越小越好
2. $a$ 数组一个增一个减更优，因为这样一定比单增或者单减能覆盖到更多数

于是有个简单的想法，从 $n$ 开始，尽可能地一个增一个减，如果做不到的话就单增或者单减，直到再也无法添新的项。实际上这样做是不对的，比方说要求长度为 $5$ 的排列要从 $1$ 开始，按照之前的想法找到的最优的序列是 $1\;2\;4\;3\;5$，这时候 $b$ 的 LIS 是 $2$。而构造序列 $1\;3\;4\;2\;5$ 的 LIS 是 $3$，这种做法非常不牛。

从第二点我们可以想到，如果能从 $\lfloor\frac{m}{2}\rfloor$ 或者 $\lceil\frac{m}{2}\rceil$ 开始能加或者能减的数目是最多的，而且应该恰能遍历每一个数，所以如果 $n$ 不是这两个之一的话，$b$ 的 LIS 应该是 $m-2$，否则是 $m-1$。由于后者已经是 $b$ 的 LIS 的最大值了，而前者若不是最优的话，表示每个数都可以为 LIS 做贡献，而除非开头是之前提到的两个数之一的话这是不可能的，所以前者也是最优的。

而究竟是从 $\lfloor\frac{m}{2}\rfloor$ 还是 $\lceil\frac{m}{2}\rceil$ 开始呢？我们先讨论 $n<\lfloor\frac{m}{2}\rfloor$ 的情况（大于的时候也可以按下述过程推出）。首先考虑这时候的过程实际上是一个大于 $\lfloor\frac{m}{2}\rfloor$ 的数接一个 $\lfloor\frac{m}{2}\rfloor$ 的数，我们要让这两部分的数尽可能接近（除去开头的数，相差的个数不超过 $1$）

1. $m$ 是奇数。如果选 $\lfloor\frac{m}{2}\rfloor$，那么左半边只剩 $\lfloor\frac{m}{2}\rfloor-2$ 个数，而右半边还有 $\lfloor\frac{m}{2}\rfloor$ 个数。但如果选 $\lceil\frac{m}{2}\rceil$ 的话，左半边只剩 $\lfloor\frac{m}{2}\rfloor-1$ 个，右半边也剩 $\lfloor\frac{m}{2}\rfloor-1$ 个，
2. $m$ 是偶数。如果选 $\lfloor\frac{m}{2}\rfloor$，那么左半边剩 $\lfloor\frac{m}{2}\rfloor-2$ 个数，右半边有 $\lfloor\frac{m}{2}\rfloor+1$ 个数。但如果选 $\lceil\frac{m}{2}\rceil$ 的话，左半边剩 $\lfloor\frac{m}{2}\rfloor-1$ 个，右半边剩 $\lfloor\frac{m}{2}\rfloor$ 个。

因此总结一下构造过程就是：

1. 如果 $n<\lfloor\frac{m}{2}\rfloor$，就把 $n$ 改到 $\lceil\frac{m}{2}\rceil$；如果 $n>\lfloor\frac{m}{2}\rfloor$，就把 $n$ 改到 $\lfloor\frac{m}{2}\rfloor$。
2. 先增 $i$ 再减 $i+1$ 地来构造，如果发现遇到了 $n$，就将间隔数再加一。

感觉这题的做法还是有点意思的。关键在于能否想到一定从 $\lfloor\frac{m}{2}\rfloor$ 或者 $\lceil\frac{m}{2}\rceil$ 开始最优。

---

## 作者：wangyibo201026 (赞：0)

## 思路

不知道为什么大家都要这么复杂qwq，这个题感觉很简单吧。

就是如果没有绝对值的话，我们可以构造一个 $x, x + 1, x - 1, x + 2, x - 2 ...$ 状物，这样子我们的差分数组就是 $1, -2, 3, -4, 5 ...$，不难发现加了绝对值是上升的。

然后如果这样子碰到了 $1$ 或者 $n$ 我们就一直往没有碰到边的方向走就好了。然后剩下的数随便咋放都不会影响答案，但是初始时会有两个方向，我们就选择离远的那一边条就好了。

但是我打了个暴力，发现并不是很对，观察一下，我们发现有另外一种构造方法是可以更优的：

- 先从排列中剔除 $x$，开头放 $x$，然后跳到剩余数的中间，然后左右横跳，这样子可以做到 LIS 为 $n - 1$（开始向远的那一边跳）。

但是我们发现了一个很严重的问题就是，当 $n = 4, x = 2$ 时你的东西可能是错的（我初始是往右跳），所以我们需要特判如果第一步是 $1$ 的差值我们就从中点往 $x$ 在的那边走，注意到只有当 $x = \frac{n}{2}$ 且 $n$ 为偶数时都会出现这种情况，所以就对了（其实这种情况就是可以直接跳的）。

## 代码

```cpp
void Solve () {
  cin >> n >> x;
  ans.push_back ( x );
  g.push_back ( 0 );
  for ( int i = 1; i <= n; i ++ ) {
    if ( i != x ) {
      g.push_back ( i );
    }
  }
  int pos = n / 2, p = 1, cnt = 1;
  ans.push_back ( g[pos] );
  if ( ( n - 1 ) & 1 && x < g[pos] ) {
    p = -1;
  }
  while ( ans.size () < n ) {
    pos += p * cnt;
    ans.push_back ( g[pos] );
    p *= -1, cnt ++;
  }
  for ( int x : ans ) {
    cout << x << " ";
  }
}
```

---

## 作者：HasNoName (赞：0)

### 思路

将 $N$ 的奇偶性分类讨论。

若 $N$ 为奇数，且 $X=\Big\lceil\dfrac{N}{2}\Big\rceil$，则将从 $X$ 到 $N$ 的数和从 $X-1$ 到 $1$ 的数交替排列就是答案。否则再分 $X<\Big\lceil\dfrac{N}{2}\Big\rceil$ 和 $X>\Big\lceil\dfrac{N}{2}\Big\rceil$ 两种情况，将 $a$ 中第 $2$ 个数到第 $N$ 个数从 $N$ 去掉 $X$ 后中间的数到 $N$ 和剩下的数按类似于 $X=\Big\lceil\dfrac{N}{2}\Big\rceil$ 的方法交叉摆放就是答案。

$N$ 为偶数的方法和 $N$ 为奇数的方法类似。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int a[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>n>>m;
	if(n&1)//N为奇数
	{
		int u=n/2+1;
		if(m==u)//X=⌈N/2⌉
		{
			int t=u;
			for(int i=1;i<=n;i+=2)a[i]=t++;
			t=u-1;
			for(int i=2;i<=n;i+=2)a[i]=t--;
		}
		else
		{
			a[1]=m;
			if(m<u)//由于不可能构造出b的最长上升子序列为N-1的情况，故考虑构造b的最长上升子序列的N-2的情况
			{
				int t=u+1;
				for(int i=3;i<=n;i+=2)a[i]=t++;
				t=u+1;
				for(int i=2;i<=n;i+=2)
				{
					t--;
					if(t==m)t--;
					a[i]=t;
				}
			}
			else
			{
				int t=u-1;
				for(int i=2;i<=n;i+=2)
				{
					t++;
					if(t==m)t++;
					a[i]=t;
				}
				t=u-1;
				for(int i=3;i<=n;i+=2)a[i]=t--;
			}
		}
	}
	else//N为偶数
	{
		int u=n/2;
		if(m==u)//N为偶数时有两种方法b的最长上升子序列为N-1
		{
			int t=u;
			for(int i=1;i<=n;i+=2)a[i]=t--;
			t=u+1;
			for(int i=2;i<=n;i+=2)a[i]=t++;
		}
		else if(m==u+1)
		{
			int t=u+1;
			for(int i=1;i<=n;i+=2)a[i]=t++;
			t=u;
			for(int i=2;i<=n;i+=2)a[i]=t--;
		}
		else//和N为奇数的方法类似
		{
			a[1]=m;
			if(m<u)
			{
				int t=u+1;
				for(int i=2;i<=n;i+=2)a[i]=t++;
				t=u+1;
				for(int i=3;i<=n;i+=2)
				{
					t--;
					if(t==m)t--;
					a[i]=t;
				}
			}
			else
			{
				int t=u;
				for(int i=3;i<=n;i+=2)
				{
					t++;
					if(t==m)t++;
					a[i]=t;
				}
				t=u;
				for(int i=2;i<=n;i+=2)a[i]=t--;
			}
		}
	}
	for(int i=1;i<=n;i++)cout<<a[i]<<' ';
	cout<<'\n';
	return 0;
}
```

---


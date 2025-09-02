# [ARC094E] Tozan and Gezan

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc094/tasks/arc094_c

非負整数からなる数列 $ A,B $ が与えられます。 $ A,B $ の長さはともに $ N $ であり、$ A $ の値の総和と $ B $ の値の総和は等しいです。 $ A $ の $ i $ 項目は $ A_i $ であり、$ B $ の $ i $ 項目は $ B_i $ です。

とざん君とげざん君は、以下の操作を繰り返します。

- もし $ A,B $ が列として等しいなら、繰り返しを終了する
- そうでない場合、まずとざん君が $ A $ の正の要素を $ 1 $ つ選び、$ 1 $ 減らす
- その後、げざん君が $ B $ の正の要素を $ 1 $ つ選び、$ 1 $ 減らす
- その後、ペットの高橋君に飴を $ 1 $ つ食べさせる

とざん君は繰り返しが終了するまでに高橋君に食べさせる飴の個数を最大に、げざん君は最小にしたいです。 両者最適に操作を行ったとき、高橋君に食べさせる飴の個数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ ×\ 10^5 $
- $ 0\ \leq\ A_i,B_i\ \leq\ 10^9(1\leq\ i\leq\ N) $
- $ A,B $ の値の総和は等しい
- 入力はすべて整数である

### Sample Explanation 1

両者最適に操作を行ったとき、操作は以下のように進みます。 - とざん君は $ A_1 $ を $ 1 $ 減らす。 - げざん君は $ B_1 $ を $ 1 $ 減らす。 - 高橋君に飴を $ 1 $ つ食べさせる。 - とざん君は $ A_2 $ を $ 1 $ 減らす。 - げざん君は $ B_1 $ を $ 1 $ 減らす。 - 高橋君に飴を $ 1 $ つ食べさせる。 - $ A,B $ が等しくなったので終了する。

## 样例 #1

### 输入

```
2
1 2
3 2```

### 输出

```
2```

## 样例 #2

### 输入

```
3
8 3
0 1
4 8```

### 输出

```
9```

## 样例 #3

### 输入

```
1
1 1```

### 输出

```
0```

# 题解

## 作者：loveJY (赞：3)

upd in 2020/12/1: 已重新排版

# 简要题意

输入数组A,B,满足$sum_A=sum_B$(A,B和相同)

定义一轮游戏为

1. 判断A,B数组是否相等(对应下标位置值相同),如果相等,则结束
2. Tozan可以将A数组一个大于0的值-1
3. Gezan可以将B数组一个大于0的值-1
4. Takahashi吃一个糖,然后返回1

现在Tozan想最大化Takahashi吃的糖数,Gezan想最小化,问最后Takahashi吃的糖数

# 题解

问题等价于Tozan让数组的和最后最小,Gezan则是最大

不难发现,如果A数组有位置i的值小于B数组位置j的值,那那个位置最后一定能被Tozan减成0

因为A数组某位置大于0且小于B数组对应位置的值的时候,我们的Tozen至少可以在Gezan对该位置操作一次后接着减

比如:
```
1: 2 3

2: 1 2

3: 0 1 

```


所以答案至少加上所有A数组中,$A<B$位置的值和

然后再来看看$A>B$的位置

你会发现无论如何Tozan都最后都能把他们消到只剩一个非0的位置

因为只需要保留那个最后要消掉的$A>B$位置的数

然后其他位置的数Tozan排着消除即可

一定不会中途突然A数组等于B数组,至少有我们保留的一个位置不同(而且Gezan也不能让他相同,因为A的更大)

那之后,我们发现只需要判断留下哪个位置最优

其实就是对应A,B数组位置的值差最大的那个

因为Gezan一定可以用类似于截击Tezan的方法---一定不动最后要保留的位置,减法操作都给其他位置用

比如

```
   A B
1. 3 2
   1 2
   
2. 3 2
   0 1
   
3. 2 2
   0 0

```

又因为两数组和相同,所以我们Gezan的这个策略一定不会因为提前把其他数都减成0而无法操作,所以也一定能做到

# AC代码

```cpp


#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 2e5 + 7;
int n, a[MAXN], b[MAXN];
ll S;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i], &b[i]);
		S += a[i];
	}
	ll ans = 0;
	for(int i = 1; i <= n; ++i) {
		if(b[i] < a[i])
			ans = max(ans, S - b[i]);
	}
	printf("%lld\n", ans);
	return 0;
}

```


---

## 作者：focus_aurora (赞：2)

## 思路

博弈论。

分析样例和操作，发现如下事实。

如果 $a_i < b_i$ 时，第一个人想要增加操作次数，会优先选择将 $a_i$ 变成 $0$，第二个人会紧接着将 $b_i$ 也变成 $0$。总共用了 $b_i$ 步。

如果 $a_i > b_i$ 时，第一个人不能先把 $a_i$ 变成 $0$，第二个人先会$b_i$ 变成 $0$。总共用了 $a_i-b_i$ 步。

如果 $a_i = b_i$ 时，停止操作。

综上所述，结果是 $ \sum_{i=1}^{n}a_i-\max_{i=1}^n\{b_i\} $。

## 代码

```
#include<bits/stdc++.h>
#define int long long//不开long long见祖宗
using namespace std;
const int N=2e5+5;
int a[N],b[N];
int sum=0;
int maxn=0;
signed main(){
	int n;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i],&b[i]);
		sum+=a[i];//求ai的和
	}
	for(int i=1;i<=n;i++){
		if(a[i]>b[i]){
			maxn=max(maxn,sum-b[i]);//求最大值
		}
	}
	printf("%lld",maxn);
	return 0;//好习惯
} 
```

---

## 作者：QWQ_jyc (赞：2)

我们可以把一个数据分为 $3$ 种情况。

$\bullet$ $a_i=b_i$ 时，无法操作。

$\bullet$ $a_i<b_i$ 时，因为为了增加操作次数，第一个人一定会让 $a_i$ 变成 $0$，所以第二个人肯定也会让 $b_i$ 也变为 $0$，因此用了 $b_i$ 步。

$\bullet$ $a_i>b_i$ 时，因为第一个人肯定无法将 $a_i$ 变为 $0$。所以会用  $a_i-b_i$ 步。

于是可以看出答案就是每个 $b_i$ 相加的总和减去某一满足 $a_i>b_i$ 的 $b_i$ 的最大值。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[114514],b[114514],s,m;
int main() {
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		s+=a[i];
	}
	for(int i=1;i<=n;i++) {
		if(b[i]<a[i])
			m=max(m,s-b[i]);
	}
	cout<<m<<endl;
	return 0;
}
```


---

## 作者：gyyyyx (赞：2)

简单分析一下不难得出，如果某个位置的数 $a_i<b_i$ 那一定可以把 $a_i$ 取到 $0$。

再看 $a_i>b_i$ 的位置。

先手一定可以选择一个位置不动，一直取其它，直到其它为 $0$。

这种策略后手没有办法阻止，因为操作只有减，后手不可能不断加让先手不动的那个位置 $a_x$ 与 $b_x$ 相同。

但不动的那个位置先手只能取到 $b_i$，也就是说只能取 $a_i-b_i$ 次。

所以答案就是所有 $a_i$ 的和减去某个满足 $a_x>b_x$ 的 $b_x$。

而先手为了让答案最大化，一定会让 $b_x$ 最小，所以就打个擂台取 $b_x$ 最小值就行了。

代码：

```cpp#include<bits/stdc++.h>
#define N 200005
using namespace std;
int n,a[N],b[N];
long long S,ans;
int main(){
	scanf("%d",&n);
	for(int i(1);i<=n;++i){
		scanf("%d%d",a+i,b+i);
		S+=a[i];
	}
	for(int i(1);i<=n;++i)
		if(a[i]>b[i]) ans=max(ans,S-b[i]);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：1)

## AT_arc094_c [ARC094E] Tozan and Gezan 题解
### 思路：
这一题我们分情况来看：

- $a_i=b_i$ 时，无法操作。
- $a_i<b_i$ 时，如果第一个人想尽可能的增加次数，那一定是把 $a_i$ 减到 $0$，此时 $b_i$ 为了和 $a_i$ 相等也需要变为 $0$，所以用了 $b_i$ 步。
- $a_i>b_i$ 时，此时 $a_i$ 不能变为 $0$，要保证 $b_i$ 操作次数最小，也就是 $0$ 次，所以用了 $a_i-b_i$ 步。

综上所述，我们可以得知答案为 $a$ 数组的和（由于要减一个 $b$ 数组的元素，再加上两数组和相同，于是我们选择 $a$ 数组）减去一个满足 $a_y>b_y$ 的 $b_y$，而先手为了使答案最大化一定会选择最小的 $b_y$，于是我们只要找出 $b_i$ 的最小值以及 $a$ 数组的和再相减即可。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, a[200005], b[200005];
int sum=0,maxi=0;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i];
		sum+=a[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]>b[i])
		{
			maxi=max(maxi,sum-b[i]);
		}
	}
	cout<<maxi<<endl;
	return 0;
}
```

[AC记录](https://atcoder.jp/contests/arc094/submissions/44377077)


---

## 作者：TemplateClass (赞：0)

根据 $a _ i$ 和 $b _ i$ 的大小关系进行分类讨论：

- 当 $a _ i = b _ i$ 时，不能操作。
- 当 $a _ i < b _ i$ 时，第一个人会先把 $a _ i$ 变成 $0$，然后第二个人才会把 $b _ i$ 变成 $0$，也就是一共有 $b _ i$ 次操作。
- 当 $a _ i > b _ i$ 时，第一个人不能先把 $a _ i$ 变成 $0$，此时 $b _ i$ 会被第二个人优先变成 $0$，也就是说一共 $a _ i - b _ i$ 次操作。

总结一下，答案就是 $\sum a _ i$ 再减去满足 $a _ i > b _ i$ 的最小 $b _ i$，若不存在这样的 $b _ i$，则输出 $0$。

```cpp
#include<iostream>
#include<algorithm>

typedef long long ll;
typedef unsigned long long ull;

constexpr int N = 2e5 + 5;
constexpr int INF = 0x3f3f3f3f;

int n, a[N], b[N]; ll sum = 0ll, min = INF;

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin >> n;
	for(int i = 1; i <= n; ++i) {
		std::cin >> a[i] >> b[i]; sum += a[i]; 
		min = (a[i] > b[i] ? std::min(min, 1ll * b[i]) : min);
	}
	
	std::cout << (min == INF ? 0 : sum - min) << "\n";
	
	return 0;
}
```

---

## 作者：_WF_ (赞：0)

## 题目大意：

  给两个序列 $A$ 和 $B$，长度均为 $N$。小 $T$ 和小 $G$ 在玩一个游戏，小 $T$ 先手，小 $G$ 后手。
  
  两个序列完全相等（即对于任意的 $i$ 都有 $ A_i = B_i$）的时候游戏停止。
  
  不然，小 $T$ 选择一个 $A_i$ 减 $1$，小 $G$ 选择一个 $B_i$ 减 $1$ 。
  
  小 $T$ 想使游戏进行的步数尽可能多，小 $G$ 想使游戏进行的步数尽可能少。
  
  双方都采用最优策略，问最后游戏停止的时候经过了多少步？
  题目保证：
  $$
\sum_{i = 1}^{N} A_i = \sum_{i = 1}^{N} B_i
$$
即 $A$，$B$ 中的所有元素的和相等。
## 题目分析：
  设满足 $A_i > B_i $ 的点的最小值为 $K$。

  直接输出：
  $$\sum_{i = 1}^{N} B_i - K$$
## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int main(){
    bool tf=1;
    long long ans=0,lalal=(1<<30);
    cin>>n;
    for (long long u=1;u<=n;u++){
        long long a,b;
        cin>>a>>b;
        if (a!=b) tf=0;
        ans=ans+a;
        if (a>b) lalal=min(lalal,b);
    }
    if (tf) printf("0");
    else printf("%lld\n",ans-lalal);
}
```

---

## 作者：maple_trees_112 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_arc094_c)


## 思路

这道题的确有一些玄妙，我们来讲讲思路。

$a_i$ 有多少种情况都行，但是第一个选择的人一定是把它归零的。
两个数组的总和相等，要是第一个人不能把任意一个元素清零，那么第二个人一定能把其他任意一个元素清零。

其次，本题的意思其实就是让第 $1$ 个人尽可能增加操作，第 $2$ 个人尽可能减少操作，所以我们要考虑最坏的情况。

先考虑 $a_i$ $>$ $b_i$ ，一眼就能看出不可能存在 $a_j$ $\le$ $b_j$（当 $i$  $\ne$ $j$）的操作，第 $1$ 个人会减去( $a_i$ ，$b_i$ )，当 $b_i$ 最小时，第 $2$ 个人最后减去( $a_i$ ，$b_i$ )因为如果减去了这个 $b_i$ 会使得差更大，这样 $a_i$ 就需要更多的步数才能追上，这样一来目的也达成了。

到这里，答案是不是呼之欲出了。好了，上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[10000010],b[10000010],n,sum,maxn;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		sum+=a[i];
	}
	for(int i=1;i<=n;i++)
   	{
		if(a[i]>b[i])
  		{
			maxn=max(maxn,sum-b[i]);
		}
	}
	cout<<maxn<<endl;
	return 0;
}
}
```


---

## 作者：qiuqiuqzm (赞：0)

# [ARC094E] Tozan and Gezan 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_arc094_c)

## 题目大意
有两个数组，里面数据都是非负的，它们数据个数和总和都是相等的。两个人要进行如下操作：

1. 若两个数组相等，则停止操作。
2. 第一个人在 $a$ 数组任选一个数，将其 $-1$。
3. 第二个人在 $b$ 数组任选一个数，将其 $-1$。

第一个人想尽可能的增加操作次数，第二个人想尽可能的减少操作次数。求在最优情况下的操作次数。

## 分析
* 对于每一个数据，我们可以分成 $3$ 种情况：
 1. $a_i=b_i$ 时。此时无法操作。
 2. $a_i<b_i$ 时。此时第一个人一定会让 $a_i$ 变成 $0$，这样才能尽可能的增加操作次数。而第二个人肯定迟早也会让 $b_i$ 随着 $a_i$ 变为 $0$ 也变为 $0$，此时用了 $b_i$ 步。
 3. $a_i>b_i$ 时。此时第一个人肯定无法将 $a_i$ 变为 $0$。就会用 $a_i-b_i$ 步。
* 综合 $3$ 种情况，答案就是所有 $b_i$ 的总和(总和相同，哪个都行)减去某一满足 $a_i>b_i$ 的 $b_i$ 的值的最大值(因为先手为了让操作次数更多，肯定会让这个 $b_i$ 更小，只要选最小的 $b_i$ 即可，减完之后就变成了最大值)。

## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXX=200005;
int n,a[MAXX],b[MAXX];
long long sum=0,ans=0;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i];
		sum+=b[i]; //总和
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]>b[i])
			ans=max(ans,sum-b[i]); //求答案
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Silence_World (赞：0)

# 思路

想了好久呜呜，想出来之后感觉这道题确实挺妙的，首先无论所 $a_{i}$ 有多少情况，第一个人肯定是要把他给归到零，因为这样第二个人会运用大把的步数把       $b_{i}$ 归到零，这样是最优的，也就是整个程序的基值就是所有 $a_{i}$ 的值，~~那如果这个第一个人当老阴 13~~，趁我们不注意给大的 $a_{i}$ 疯狂减，最后到零，相当于我们亏了一个 $b_{i}$ 的操作，且得不偿失，所以我们还要判断   $a_{i}$ 比 $b_{i}$ 大时该怎么办，首先，我们用判断每个 $b_{i}$ 的情况，用基值减去 $b_{i}$，判断最大值，这样既能满足第一个人的最好情况，这样即让步数最大，情况最优，~~也不用担心被阴拉！~~

# 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[10000005];
int b[10000005];
main()
{
	int n;
	cin>>n;
	int sum=0;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		sum+=a[i];
	}
	int max1=0;
	for(int i=1;i<=n;i++){
		if(a[i]>b[i]){
			max1=max(max1,sum-b[i]);
		}
	}
	cout<<max1<<endl;
    return 0;
}
```


---

## 作者：qfpjm (赞：0)

# 题解

- 一看就像是博弈论。

- $\sum A_i=\sum B_i$ 只是用来保证双方同时减到和为零。

- 从我们从 $A_i,B_i$ 的大小关系入手。显然对于甲，当 $A_i>B_i$ 时，他显然不会在存在 $A_j\leq B_j(i\ne j)$ 时操作。甲会最后减 $(A_i,B_i)$ 当且仅当 $A_i>B_i$ 且 $B_i$ 最小。乙最后减 $(A_i,B_i)$ 也是当且仅当 $A_i>B_i$ 且 $B_i$ 最小，是因为如果减去了这个 $B_i$ 会使得差更大，$A_i$ 需要更多步才能追上，从而会使得操作次数变大。

- 设 $Sum=\sum A_i$，因为上述原因，所以 $Sum-\min\{B_i\}$ 既是上界，也是下界，所以这就是最终答案。需要注意特判一下 $A_i,B_i$ 两两相等的情况。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, a[200010], b[200010];
long long ans;

int main()
{
	cin >> n;
	bool flag = 1;
	for (int i = 1 ; i <= n ; i ++)
	{
		cin >> a[i] >> b[i];
		if (a[i] != b[i])
		{
			flag = 0;
		}
	}
	if (flag)
	{
		puts("0");
		return 0;
	}
	int minn = 2e9;
	for (int i = 1 ; i <= n ; i ++)
	{
		ans += a[i];
		if (a[i] > b[i])
		{
			minn = min(minn, b[i]);
		}
	}
	cout << ans - minn;
}
```


---


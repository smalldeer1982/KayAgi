# Mike and distribution

## 题目描述

Mike has always been thinking about the harshness of social inequality. He's so obsessed with it that sometimes it even affects him while solving problems. At the moment, Mike has two sequences of positive integers $ A=[a_{1},a_{2},...,a_{n}] $ and $ B=[b_{1},b_{2},...,b_{n}] $ of length $ n $ each which he uses to ask people some quite peculiar questions.

To test you on how good are you at spotting inequality in life, he wants you to find an "unfair" subset of the original sequence. To be more precise, he wants you to select $ k $ numbers $ P=[p_{1},p_{2},...,p_{k}] $ such that $ 1<=p_{i}<=n $ for $ 1<=i<=k $ and elements in $ P $ are distinct. Sequence $ P $ will represent indices of elements that you'll select from both sequences. He calls such a subset $ P $ "unfair" if and only if the following conditions are satisfied: $ 2·(a_{p1}+...+a_{pk}) $ is greater than the sum of all elements from sequence $ A $ , and $ 2·(b_{p1}+...+b_{pk}) $ is greater than the sum of all elements from the sequence $ B $ . Also, $ k $ should be smaller or equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF798D/063c1ec1fbcd406bc727adffa50b1420ca2cf4be.png) because it will be to easy to find sequence $ P $ if he allowed you to select too many elements!

Mike guarantees you that a solution will always exist given the conditions described above, so please help him satisfy his curiosity!

## 样例 #1

### 输入

```
5
8 7 4 8 3
4 2 5 3 7
```

### 输出

```
3
1 4 5
```

# 题解

## 作者：MuYC (赞：19)

#### 前言

很妙的思维题。

考察知识点：贪心

2021/1/10 修改了一些错误，麻烦管理重新审核。

#### 题意

给定 $A,B$ 两个长度为 $n$ ( $n <= 10 ^ 5$)的数组，数组中的元素都为正整数，即 $1 <= A_i,B_i <= 10 ^ 9$。 现在要求你选择出一个下标集合

$P$ = {$p_1,p_2$,...$p_{k}$} ( $k <= n / 2 + 1$) 。 

假设 $A$ 数组中所有元素和为 $sumA$ , $B$ 数组中所有元素和为 $sumB$ ,选出的 $P$ 集合满足 

+ $\sum_{p_i ∈ P}{A_{p_i}} * 2 > sumA$
+ $\sum_{p_i ∈ P}{B_{p_i}} * 2 > sumB$

现在你需要输出一个满足条件的集合 $P$。

#### 思路

想必看完题目大家都知道是贪心了。不用说，这个题目让我们选择最多 $n / 2 + 1$ 个数，而且 $A_i,B_i$都是正整数 ，本着 “不嫖白不嫖”的原则，我们直接构造一个大小为 $n / 2 + 1$ 的集合就好了。

题目给定的是 $n / 2 + 1$ 个下标，但是只要求选出的这几个数的和的两倍大于原数组的和。

~~有蹊跷~~

不妨考虑先满足 $A$ 数组的条件，在满足 $A$ 数组的条件的情况下尽量满足 $B$ 数组的答案。

首先为了尽量满足 $A$ 数组的条件，我们先把这两个数组存为一个结构体 $T$，按照 $A_i$ 的大小排序（要记录它们在原数组中的下标）。

肯定是不能单纯的选出前 $n / 2 + 1$ 个的，如果你这么选择你就 $too$ $young$ $too$ $simple$ 了。

这个 $n / 2 + 1$ 的 $+ 1$ 让人很不爽，于是我们就先选出 $T[1]$ 这个结构体节点对应在原数组中的下标。

然后我们现在要在剩下的 $n - 1$ 个数里面选出 $n / 2$ 个数，这 $n / 2$ 个数的和 $* 2$ 要 **大于等于** 原数组的和。

（因为选了第一个，第一个的 $1 <= A_i,B_i$ ，所以是**大于等于**）

这时候我们就要想，要选择怎么样的 $n / 2$ 个呢？

这时候，笔者想了 $10min$ 后发现一个做法：

剩下的所有数里面可以分组考虑，因为是选出 $n / 2$ 个嘛，也就是两个里面要选出一个来。

不妨把 $T[2],T[3]$ 归为一组 , $T[4],T[5]$ 归为一组，依此类推。

然后我们惊喜的发现，只要 $T[2],T[3]$ 中任意选一个， $T[4],T[5]$ 中任意选一个......这样选择下去无论如何一定能够满足 $A$ 数组的条件。

为什么呢？这种问题的证明实际上只要考虑最坏的情况，也就是最后选择的是:

$T[3],T[5],T[7]$...(一共选择 $n / 2$ 个数)，这样考虑，$T[1] >= T[2] , T[3] >= T[4] , T[5] >= T[6]......$

最后因为我们选了一手 $T[1]$ ，所以选出来的和 $* 2$ 一定大于 $sumA$ , 能满足数组 $A$ 的条件。

知道了这个之后，这个题目就豁然开朗了。因为实际上 每一组 我们任意选对 $A$ 数组的条件都没有影响了。

只要考虑对于 $B$ 数组是否满足条件就行了。那么我们不妨在每一组里面选出 $B_i$ 较大的就行了。

还是因为我们选了一手 $T[1]$ 这样子的话, $B$ 数组就能保证最后的答案就是合法的了！

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int n;
struct Node {
    int id,dataA,dataB;
    bool operator < (const Node &P) { return P.dataA < dataA; }//重载一手运算符
} T[MAXN];

inline int read() {
    int x = 0 , flag = 1;
    char ch = getchar();
    for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch =='-')flag = -1;
    for( ; ch >= '0' && ch <= '9' ; ch = getchar())x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}

int main()
{
    n = read();
    for(int i = 1 ; i <= n ; i ++)
    T[i].dataA = read();
    for(int i = 1 ; i <= n ; i ++)
    T[i].dataB = read(), T[i].id = i;//记得要存放下标
    sort(T + 1 , T + 1 + n);//按照A[i]的从小到大排序
    cout << n / 2 + 1 << endl;
    cout << T[1].id << " ";//先选出第一个
    for(int i = 2 ; i <= n ; i += 2) {
        if(T[i].dataB < T[i + 1].dataB) cout << T[i + 1].id << " ";//每组中哪个 B[i] 大就选哪个
        else cout << T[i].id << " ";
    }
    return 0;
}
```

#### 总结

对于这种看到 $n / 2, * 2$字眼的题目，考虑分组处理。

~~感觉贪心和排序经常一起用啊，无排序不贪心~~

---

## 作者：Remake_ (赞：7)

 随 机 化 t x d y
 
 我们都知道这个题想满足题目给定的条件是非常容易的
 
 但是最关键的是我们无法找到一组一定合法的解
 
 所以我们就可以使用随机化辣
 
 每次随机打乱原数列
 
 然后按这个新的数列贪心地取前$\frac{n}{2}+1$个数
 
 判断一下是否合法就行了，不合法的话继续随机打乱直到找到一组合法解就完事了
 
 由于贪心的正确率很高，所以随机化的时间是可以保证的qwq

 代码：
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
#define _ 0
#define timeused() (double)clock()/CLOCKS_PER_SEC
#define Set(a) memset(a,0,sizeof(a))
#define rep(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define repp(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define debug() assert(0)
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x){
    T f=1;x=0;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
    x*=f;
    return x;
}
ll rd(){ll x;rd(x);return x;}
ll n,sumA,sumB;
struct node{
    ll a,b,i;
}a[1000005];
bool check(){
    ll suma=0,sumb=0;
    rep(i,1,n/2+1){
        suma+=a[i].a;
        sumb+=a[i].b;
    }
    return suma*2>sumA&&sumb*2>sumB;
}
int main(){
    n=rd();
    rep(i,1,n){
        a[i].a=rd();
        sumA+=a[i].a;
    }
    rep(i,1,n){
        a[i].i=i;
        a[i].b=rd();
        sumB+=a[i].b;
    }
    printf("%lld\n",n/2+1);
    while(114514){
        random_shuffle(a+1,a+n+1);
        if(check()){
            rep(i,1,n/2+1) printf("%lld ",a[i].i);
            return 0;
        }
    }
    return ~~(0^_^0);
}
```


---

## 作者：littleseven (赞：3)

# CF 798D Mike and distribution

**题目链接：**[洛谷 CF 798D Mike and distribution](https://www.luogu.org/problem/CF798D)	[CF 798D Mike and distribution](https://codeforces.com/problemset/problem/798/D)

**算法标签:**  `贪心`、`思维`

## 题目描述：

给两个长度为 $n$ 的数列$A,B$，要求至多选择 $\lfloor \frac{n}{2} \rfloor+1 $ 个下标，使得 $A$ 数组中选出的数的和的两倍大于 $sumA$ ， $B$ 数组中选出的数的和的两倍大于 $sumB$ 

## 题解：

**贪心 + 思维！！！！**

模拟赛T1，三个小时没有搞出正解	[擦汗.jpg]

既然题目中让我们最多选择 $\lfloor \frac{n}{2} \rfloor+1$ ，并且没有要求最小，那么不妨我们就取 $\lfloor \frac{n}{2} \rfloor+1$ 个值，显然这是对的（不要白不要啊……）。

之后我们考虑假如只有一个数列，这道题就变得很简单，排序之后找出前 $\lfloor \frac{n}{2} \rfloor+1$ 个再判一下就可以。

那么对于两个数列怎么办？？？

现在我们来考虑这个神奇的 $\lfloor \frac{n}{2} \rfloor+1$ ，本着给你就不白给的原则，我们会发现，这是什么

​		——	两两分组再加一个

虽然很奇妙且扯皮淡雅，但是这的确是真的啊（考场上怎么可能 $yy$ 出来？？？）

又因为排序可以处理两个数列中的一个，那么两两分组就可以处理第二个。   [肯定.jpg]

------

用结构体 $node[~].a, node[~].b, node[~].id$ 存下来 $A，B$ 数组和当前这对数在初始数列的位置。

首先按照数列$A$从大到小给结构体排序，我们就得到了一个 $node[1].a \ge node[2].a \ge node[3].a \dots \ge node[n].a$ 的有序结构体，这样我们保证前 $\lfloor \frac{n}{2} \rfloor+1$ 个$A$之和一定比剩下的$A$之和大。

之后我们假设先选择 $node[1]$，之后对于后边的每一对值（两个值），选择其中 $B$ 更大的一个，即对于$node[2].b$，$node[3].b$，选出更大的一个；对于 $node[4].b，node[5].b$ ，选出更大的一个……

这时反观 $A$ 的正确性，由于我们会发现 $node[1].a \ge max(node[2].a, node[3].a),min(node[2].a, node[3].a) \ge max(node[4].a, node[5].a) \dots$

所以现在 $A$ 的正确性也是可以保证的。

之后就可以愉快的码代码了   ！！！    [开心.jpg]

## AC代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define setI(x) freopen(x".in", "r", stdin); 
#define setO(x) freopen(x".out", "w", stdout); 
#define setIO(x) setI(x) setO(x)

char *p1, *p2, buf[100000];

typedef long long ll;

#define nc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1 ++ )

ll rd() {
	ll x = 0, f = 1;
	char c = nc();
	while (c < 48) { 
		if (c == '-') { 
			f = -1;
		}
		c = nc();
	}
	while (c > 47) {
		x = (((x << 2) + x) << 1) + (c ^ 48);
		c = nc();
	}
	return x * f;
}

const int N = 100010;

typedef long long ll;

struct Node {
	ll a, b;
	int id;
} node[N];

bool cmp(Node A, Node B) {
	if (A.a == B.a) {
		return A.b > B.b;
	}
	return A.a > B.a;
}

int n;

int main() {
	// setIO("game")
	n = rd();
	for (int i = 1; i <= n; i ++ ) {
		node[i].a = rd();
		node[i].id = i;
	}
	for (int i = 1; i <= n; i ++ ) {
		node[i].b = rd();
	}
	sort(node + 1, node + 1 + n, cmp);
	printf("%d\n", (n / 2) + 1);
	printf("%d ", node[1].id);
	for (int i = 2; i <= n; i += 2) {
		ll nowb = node[i].b;
		ll nxtb = node[i + 1].b;
		if (nowb > nxtb) {
			printf("%d ", node[i].id);
		}
		else {
			printf("%d ", node[i + 1].id);
		}
	}
	return 0;
}
```



---

## 作者：封禁用户 (赞：2)

### 算法
随机化，贪心。

### 思路
首先，为了让和更大，每次应该保证选满 $\lfloor\frac{n}{2} \rfloor+1$ 个下标。

可以考虑随机化。

每次打乱 $a,b$ 数组，取前 $\lfloor\frac{n}{2} \rfloor+1$ 位判断是否满足条件即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+7;
int n,suma,sumb;

struct node{
	int a,b,id;
}p[N];

bool check(){
	int t1=0,t2=0;
	for(int i=1;i<=n/2+1;++i)
		t1+=p[i].a,t2+=p[i].b;
	return (2*t1>suma)&&(2*t2>sumb);
}

signed main(){
	srand(time(0));
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>p[i].a,suma+=p[i].a;
	for(int i=1;i<=n;++i)
		cin>>p[i].b,sumb+=p[i].b;
	for(int i=1;i<=n;++i)
		p[i].id=i;
	while(true){
		random_shuffle(p+1,p+1+n);
		if(check())
			break;
	}
	cout<<n/2+1<<"\n";
	for(int i=1;i<=n/2+1;++i)
		cout<<p[i].id<<" ";
}
```

---

## 作者：傅思维666 (赞：2)


## 题解：

~~2019.10.22模拟赛40分场~~

一看就是道贪心的题。这自然不必说。重点在于如何建立贪心策略和维护贪心的正确性（也是把本蒟蒻卡的死死的点）。

先来理解一下题意：要选出$n/2+1$对数，使得这些数的二倍比原数列和还大。

于是我们得到了一个结论：这些数是**按对**选的，也就是**绑定**选择。

根据这个思路，我们想到了构建结构体解决问题。

因为我们输出的时候要输出数组下标，所以我们不仅维护每个位置的数（a和b），而且还要构建一个映射关系，即要把数对的位置也存进结构体。这些都是基础操作，我就不多说了。

~~考场上直接写了爆搜加部分分骗了40~~

后来看了正解，加上一些自己的理解和证明，得出了这篇辣鸡博客。

我曾经$YY$过，贪心总是和排序结合在一起的，这道题当然不会例外。但是我们这道题的排序有一些困难，难点还是在于**绑定选择**。我们能通过对$A$数列或$B$数列排序来维护有解的情况，但是我们并无法构建一种可行的排序，使得在维护$A$序列的同时还维护$B$序列的正确性。

于是我们“退而求其次”，我们只维护$A$序列，然后~~乱搞搞~~尽量维护$B$序列的正确性，能行就行，不行拉倒。

然后我们建一个结构体$num[i].a.b.id$，分别存$A,B$序列的值以及序号。之后按照$A$序列进行排序，根据贪心原则，我们选靠前的项一定对答案贡献更大。那我们就直接考虑$B$序列。

这里的贪心策略与正常的贪心略有不同。对于这种题目，我们经常会被拐进：对于每个物品，选还是不选的误区。于是我们便走进了一个死胡同，发现好像怎么证明都无法得出正确的答案。所以，我们提出一种全新的贪心选择的思路（应该也比较常见）：**对于一对物品，选第一个还是第二个。**

于是，我们先选$num[1]$（因为个数是$n/2+1$），然后对于之后的每对物品，选择其中$num[i].b$值更大的那个。这就是正确的贪心决策了。

怎么证明呢？

因为我们是按$A$关键词排序，所以得出的序列肯定是$A$大的在前面，因为我们是**捆绑选择**。所以我们在$A$序列有序的基础上按对选择$B$,得出的答案一定是最优的。

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1e5+1;
int n,tot,ans[maxn];
struct node
{
	int a,b,id;
}num[maxn];
bool cmp(node a,node b)
{
	return a.a>b.a;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&num[i].a);
		num[i].id=i;
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i].b);
	sort(num+1,num+n+1,cmp);
	int cnt=n/2+1;
	ans[++tot]=num[1].id;
	for(int i=2;i<=n;i+=2)
	{
		if(num[i].b>num[i+1].b)
			ans[++tot]=num[i].id;
		else 
			ans[++tot]=num[i+1].id;
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
		printf("%d ",ans[i]);
	return 0;
}
```



---

## 作者：kingho11 (赞：1)

我们今天老师上课讲了这道题，觉得很妙，于是来写一篇题解。

本文将要介绍此题的贪心做法，当然这题可以用随机数过掉。

## 思路：
看到“至多选择 $\frac{1}{2}n+1$ 个下标”这句话，发现我们只要够贪的话，把 $\frac{1}{2}n+1$ 个下标都选了是没问题的，所以我的思路就着手于这里。

考虑先排序（按 $a_i$ 为关键字从大到小排），排完序后我们选前 $\frac{1}{2}n+1$ 个 $a_i$ 肯定是没有问题的，但是这样子就无法确保算出的 $b_i$ 的大小了。

当然排序后的 $a_1$ 是一定要选的，这样可以让我们选出的 $a_i$ 较大，剩下的 $n-1$ 个元素怎么办呢，我们考虑将其两两分组，（即 $a_2,a_3$ 一组，$a_4,a_5$一组，以此类推）当然，可能会多出来一个，不过这并不影响，我们只要把多出来的这个也选上即可。

为什么这样选不会超过 $\frac{1}{2}n+1$ 个呢？

我们可以通过分类讨论来证明。

若 $n$ 为偶数，则会选择 $(1+\left \lfloor \frac{n-1}{2} \right \rfloor +1)=1+\frac{1}{2}n-1+1=1+\frac{1}{2}n$ 个，此时不多不少刚刚好。

若 $n$ 为奇数，则会选择 $1+\frac{n-1}{2}=1+\left \lfloor \frac{1}{2}n \right \rfloor$ 个，也是满足的

接下来，我们就来考虑一组里面怎么选择，可以发现，我们就算全都选择一组里面 $a$ 较小的，即选择 $a$ 数组的奇数项，也可以满足 $2(a_1+a_3+a_5...a_k)>sumA（k=\left \lfloor \frac{1}{2}n \right \rfloor \times 2）$ 因为我们已经排过序了，所以一定满足 $a_1>a_2,a_3>a_4,a_5>a_6...$，也就是说，我们选择的数一定会比剩下的数大，同理如果 $n$ 是奇数的话，我们还可以多选一个 $a_n$ ~~好贪啊~~。

那么在此基础上如果交换一组中选择的元素的话，因为我们一开始就是选一组中最小值，所以把他和另一个的值互换，一定是对我们选择出来的和有利的，也就是会扩大我们选出来的数的和。

至此，我们证明了只需要按组选择，第一个和多出来的（如果有）都选上，组里是可以任意选的。

那么这样对于怎么在满足选出的 $a_i$ 的总和 $>sumA$ 的前提下，选出 $b_i$ 的选法就很简单了，我们只需要在一组中选择 $b_i$ 较大的那一个即可，如何证明此时选出的 $b_i$ 的和的两倍一定 $>sumB$ 呢，依旧考虑分类讨论，如下：

  若 $n$ 是奇数，我们可以确保我们不会选择到 $b$ 数组中较小的 $\frac{n-1}{2}$ 个数，注意是较小！！，因为我们还有第一个呢，若它是较小的一半，那么两倍的已选择的和也会大于 $sumB$，如果是在较大的更不用说了。![](https://cdn.luogu.com.cn/upload/image_hosting/4ag2fova.png)
  
  若 $n$ 是偶数，我们会选择到按 $a_i$ 为关键字从大到小排序后的第一个和最后一个 $b$ 元素，此时我们又会选择到分组中较大的 $b_i$，容易证明，此时选择出来的 $b_i$ 的两倍 $>sumB$。至于怎么证明，大家可以像我上面那样画一个图出来，自己推导一下会理解得更加深刻。

至此，这道题全部做完啦！！

## CODE:

最后给出代码。

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct uuu{
	int a,b,pos;
}a[N];
int n;
bool cmp(uuu a,uuu b)
{
	return a.a>b.a;
}
vector <int> ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].a;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].b;
		a[i].pos=i;
	}
	sort(a+1,a+1+n,cmp);//按a_i为关键字排序 
	ans.push_back(a[1].pos);//无论如何第一个都要选 
	for(int i=2;i<=n;i+=2)
	{
		if(a[i].b>a[i+1].b)
		{
			ans.push_back(a[i].pos);
		}else
		{
			ans.push_back(a[i+1].pos);
		}
	}
	cout<<ans.size()<<"\n";//输出 
	for(int i=0;i<ans.size();i++)
	{
		cout<<ans[i]<<" ";
	}
}
```

## 总结：
总结一下，感觉还是挺好的思维题，不过感觉评蓝有点高

---

## 作者：翼德天尊 (赞：1)

不妨先按照 $a_i$ 降序排序，使思考变得更加自然。

其实【选出数之和的二倍大于总和】可以转化为【选出数之和大于未选数之和】，即，我们只需要确定一种方案，使得选出的 $a_i$ 和没选的 $a_i$、选出的 $b_i$ 和没选的 $b_i$ 两两构成偏序关系，就成功了。

不妨直接取走最大的 $a_i$ 与其对应的 $b_i$。此时对于剩下的 $n-1$ 个数，我们还可以取走 $\left\lfloor\frac{n}{2}\right\rfloor$ 个，不妨前后两两分成一组，此时组与组之间的 $a_i$ 构成偏序关系，且 $a_1$ 和第一组的 $a_2,a_3$ 构成偏序关系。于是我们直接对于每一组取 $b_i$ 较大的那个即可满足条件。

**体现了对于约束角度的转化。**没事先排个序整理下集合也是个不错的习惯。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int n;
bool vis[N];
struct node{
    int x,y,id;
}p[N];
int read(){
    int w=0,f=1;
    char ch=getchar();
    while (ch>'9'||ch<'0') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9') {
        w=(w<<3)+(w<<1)+(ch^48);
        ch=getchar();
    }
    return w*f;
}
bool cmp(node x,node y){
    return x.x>y.x;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    n=read();
    for (int i=1;i<=n;i++){
        p[i].x=read(),p[i].id=i;
    }
    for (int i=1;i<=n;i++) p[i].y=read();
    sort(p+1,p+1+n,cmp);
    cout<<n/2+1<<"\n";
    // for (int i=1;i<=n;i++) cout<<p[i].x<<" "<<p[i].y<<"\n";
    vis[p[1].id]=1;
    for (int i=2;i<=n;i+=2)
        if (p[i].y>p[i+1].y) vis[p[i].id]=1;
        else vis[p[i+1].id]=1;
    for (int i=1;i<=n;i++)
        if (vis[i]) cout<<i<<" ";
    return 0;
}
```

---

## 作者：Code_星云 (赞：1)

要选一些值，使其和的两倍要大于综合，可以化为要选一些值，使得选了的值要大于没选的值。

要满足两维的条件，首先至少要满足 $A$ 的条件，因此把元素按照  $a_i$ 从大到小排。由于要选 $\left\lfloor\dfrac{n}{2}\right\rfloor + 1$ 个值，我们先把第一个值选了，即在剩下的当中选 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 个。因此我们把剩下的值两两相邻分组。我们发现，对于每一组，不管选那一个值，最终总能满足 $A$ 的条件，因为我们选了第一个值。然后若我们在每一组总选 $b_i$ 大点的那个值，最终也能满足 $B$ 的条件。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
#define int long long

const int N = 100005;
struct node{
	int a, b, id;
}p[N];
int n;

bool cmp(node rhs1, node rhs2){
	return rhs1.a > rhs2.a;
}
signed main(){
	scanf("%lld", &n);
	printf("%lld\n", n / 2 + 1);
	for(int i = 1; i <= n; i ++){
		p[i].id = i;
		scanf("%lld", &p[i].a);
	}
	for(int i = 1; i <= n; i ++) scanf("%lld", &p[i].b);
	sort(p + 1, p + n + 1, cmp);
	printf("%lld ", p[1].id);
	for(int i = 2; i <= n; i += 2){
		if(p[i].b > p[i + 1].b) printf("%lld ", p[i].id);
		else printf("%lld ", p[i + 1].id);
	}
	return 0;
}
```


---

## 作者：elbissoPtImaerD (赞：1)

差点身败名裂。

第一反应是，两个维度，**考虑先保证 $a$ 一定满足，然后考虑 $b$ 最优。**  
想先选一些数，然后调整。  
发现这样调整不了。  
然后卡住了。

然后发现根本不需要调整，考虑本题的特点：选取 $\lfloor \frac n2 \rfloor+1$ 个下标，**满足这些下标的数之和大于剩下的数的和**。

这就明示**两两分组**了！

保证 $a$ 自然是：先将二元组 $(a_i,b_i)$ 按 $a$ 降序排列，$\lfloor \frac n2 \rfloor+1$ 的 $+1$ 用来选 $(a_1,b_1)$，然后将二元组按下标奇偶分组，每组选一个即可。

$b$ 的最优自然是选取每一组中 $b_i$ 较大的那个。

```cpp
void Solve()
{
	rd(n);
	for(int i=0;i<n;++i) rd(a[i].a),a[i].c=i+1;
	for(int i=0;i<n;++i) rd(a[i].b);
	sd stable_sort(a,a+n,[](const wt&x,const wt&y){return x.a>y.a;});
	prt(n/2+1,'\n'),wri(a[0].c);
	for(int i=1;i<n;i+=2) wri(a[i+(a[i].b<a[i+1].b)].c);
	return;
}
```

[$\color{green}{\checkmark}$](https://codeforces.com/contest/798/submission/207476062)。

---

## 作者：Furina_Saikou (赞：0)

# 题意

给定两个长度 $n$ 的序列，求最多 $\lfloor\dfrac{n}{2}\rfloor+1$ 个下标 $p_i$ 使得 $\sum a_{p_i}\times 2>\sum a_i$ 且  $\sum b_{p_i}\times 2>\sum b_i$。

# 思路

因为 $a_i,b_i$ 的范围都是正整数，所以取得越多满足条件的可能性越大，但是光按照 $a_i$ 排序或按照 $b_i$ 排序无法保证正确性。所以我们可以使用随机化，随机打乱数组顺序，每次取前 $\lfloor\dfrac{n}{2}\rfloor+1$ 个数，如果满足大于，直接输出它们在原数组的下标，否则我们继续打乱。

贪心的解法虽然不对，但是由于我们运用了随机化的方法，让每一次贪心的结果不一定相等，又因为题目只要求构造一个满足大于的序列而不要求最优解，随意随机化算法可以在不枚举全排列的情况下以较快的时间找出合法的序列。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=114514;
struct node{
	int x,y;
}a[N];
int n,b[N],suma,sumb;
signed main()
{
	mt19937 rd(chrono::system_clock::now().time_since_epoch().count());
	cin>>n;
	for(int i=1;i<=n;suma+=a[i].x,i++)cin>>a[i].x;
	for(int i=1;i<=n;sumb+=a[i].y,i++)cin>>a[i].y;
	for(int i=1;i<=n;i++)b[i]=i;
	while(1145141919810ll)
	{
		shuffle(b+1,b+n+1,rd);
		for(int j=1,sum1=a[b[1]].x,sum2=a[b[1]].y;j<=n/2+1;j++,sum1+=a[b[j]].x,sum2+=a[b[j]].y)
        if(sum1*2>suma&&sum2*2>sumb)
		{
			cout<<j<<"\n";
			for(int i=1;i<=j;i++)cout<<b[i]<<" ";
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：ivyjiao (赞：0)

虽然说这题正经贪心能过，但是我并没有看出来，于是，随机化，启动！

容易证明这题一定有解，这里就不说了。

每次把下标打乱一下，然后 check 这组下标是否合法即可，正确就直接输出，否则重新打乱直到找到合法解。

这题正确率的证明方法同 [P1489 猫狗大战](https://www.luogu.com.cn/problem/P1489)，~~反正正确率很高直观感受一下就行~~，大概就是一种合法的方案两个选中的下标互相交换不会影响方案的合法性，两个未选中的下标互相交换也不会影响方案的合法性，所以正确率很高。

注意开 long long！

双倍经验：[CF23C](https://www.luogu.com.cn/problem/CF23C)，[CF798D](https://www.luogu.com.cn/problem/CF798D)。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100001],b[100001],c[100001],suma,sumb;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],c[i]=i,suma+=a[i];
    for(int i=1;i<=n;i++) cin>>b[i],sumb+=b[i];
    while((double)clock()<CLOCKS_PER_SEC*0.99){
        random_shuffle(c+1,c+1+n);
        int cnt1=0,cnt2=0;
        for(int i=1;i<=n/2+1;i++) cnt1+=a[c[i]],cnt2+=b[c[i]];
        if(cnt1*2>suma&&cnt2*2>sumb){
            cout<<n/2+1<<endl;
            for(int i=1;i<=n/2+1;i++) cout<<c[i]<<" ";
            return 0;
        }
    }
}
```

---

## 作者：hgoicjl (赞：0)

```cpp
#include <bits/stdc++.h>
using namespace std;
struct ns
{
	int a;
	int b;
	int num;
};
int cmp(const ns &a,const ns &b)
{
	return a.a>b.a;
}
int n,num; 
ns lis[100102];
int main ()
{
	cin>>n;
	num=n/2+1;
	for(int i=1;i<=n;i++)
	{	
		cin>>lis[i].a;
		lis[i].num=i;	
	}
	for(int i=1;i<=n;i++)	
		cin>>lis[i].b;
	sort(lis+1,lis+n+1,cmp);
	cout<<num<<endl<<lis[1].num;
	for(int i=1;i<=num-1;i++)
	{	
		if(lis[2*i].b>lis[2*i+1].b)	
			cout<<' '<<lis[2*i].num;
		else
			cout<<" "<<lis[2*i+1].num; 
	}
	return 0;
}
```
### 题意：
给两个长度为n的数列A,B，要求至多选择n/2+1个下标，使得A数组中选出的数的和的两倍大于sumA，B数组中选出的数的和的两倍大于sumB
### 算法：贪心
### 解决思路：
使得A数组中选出的数的和的两倍大于sumA，B数组中选出的数的和的两倍大于sumB既选出的和大于剩下的和

定义结构体，lis[i].a表示数列a中第i个；lis[i].b表示数列b中第i个；lis[i].num表示在原数列的位置

对lis.a从大到小排列，有lis[1].a>=lis[2].a>=lis[3].a....先选取lis[1]，为保证选出的和大于剩下的和，从lis[2].b,lis[3].b选出较大的，同理下推，从lis[4].b,lis[5].b选出较大的，满足b数列选出的和大于剩下的和

而对于a数列，有lis[1].a>=max(lis[2].a,lis[3].a),min(lis[2].a,lis[3].a>=max(lis[4].a,lis[5].a)...满足a数列选出的和大于剩下的和

将选出数lis[i].num输出即可

---

## 作者：泠小毒 (赞：0)

# Mike and distribution
给两个长度为n的数列A,B，要求至多选择n/2+1个下标，使得A数组中选出的数的和的两倍大于sumA，B数组中选出的数的和的两倍大于sumB
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190517/)

[博客园(同步更新)](https://www.cnblogs.com/muronglin/p/hgoi-20190517.html)
## 解法
按a序列排序，然后2个2个取，注意的是要先取最大的那一个

可以保证都大于一半
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int x,y,num;}a[100010];
int n,cnt,ans[100010];
int cmp(node x,node y){return x.x==y.x?x.y>y.y:x.x>y.x;}
int main()
{
	scanf("%d",&n),cnt=0;
	for(int i=1;i<=n;i++)scanf("%d",&a[i].x);
	for(int i=1;i<=n;i++)scanf("%d",&a[i].y);
	for(int i=1;i<=n;i++)a[i].num=i;
	sort(a+1,a+1+n,cmp),ans[++cnt]=a[1].num;
	for(int i=2;i<=n;i+=2)
	{
		if(a[i].y>a[i+1].y)ans[++cnt]=a[i].num;
		else ans[++cnt]=a[i+1].num;
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)printf("%d ",ans[i]);
	return 0;
}
```

---


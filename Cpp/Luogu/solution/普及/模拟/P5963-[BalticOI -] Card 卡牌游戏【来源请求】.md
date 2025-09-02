# [BalticOI ?] Card 卡牌游戏【来源请求】

## 题目描述

你手上有 $n$ 张卡牌，要求将其填入框中，使得结果最小。

每张卡有两面：即每张卡有两个数字。$6$ 不能当作 $9$ 使用，同理，$9$ 也不能当作 $6$ 使用。

框与框之间有计算符号。计算符号以 `-` 和 `+` 间隔。

例如：当 $n=8$ 时，填入的框格式为：-O+O-O+O-O+O-O+O。

填入卡牌时，不一定需要按照卡牌和框的顺序进行填写（即可以进行位置的调换）。

## 说明/提示

样例一的解释：

框的格式为：-O+O-O+O-O+O。  

第一个框将第一张卡牌的 $4$ 填入；第二个框将第六张卡牌的 $-8$ 填入；  
第三个框将第三张卡牌的 $7$ 填入；第四个框将第五张卡牌的 $-3$ 填入；  
第五个框将第四张卡牌的 $5$ 填入；第六个框将第二张卡牌的 $-7$ 填入。

此时可以得到的结果为 $-34$ 是最小的。

---

对于 $30\%$ 的数据，满足 $n\leq 8$ 。  
对于 $100\%$ 的数据，满足 $n\leq 528360$ 且 $|A_i|,|B_i|\leq 10^7$。

## 样例 #1

### 输入

```
6
-8 12
0 5
7 -3
10 -7
-2 7
1 4```

### 输出

```
-34```

# 题解

## 作者：Keids (赞：6)

# **P5963 [BalticOI ] Card 卡牌游戏**

题目传送门：<https://www.luogu.com.cn/problem/P5963>

简述题意：给定 $n$ 对数和一定的加减符号，每组数中取出一个进行运算，问得到的最小值是多少。

求最值，想到 $dp$ 和贪心做法。但是仔细读题会发现,$dp$ 无法解决这个问题，因为时间效率不行，于是思考如何贪心。

对于两组数 {$x_i,y_i$} 与 {$x_j,y_j$}，因为加减符号一定，所以我们有两种选择。

假设 $x$ 为较大的数，$y$ 为较小的数，那么：

情况一：$-x_i+y_j$；

情况二：$-x_j+y_i$；

假设我们取了情况一，因为满足条件，所以我们可以得到：

$(-x_i+y_j)<(-x_j+y_i)$

发现不等式两边下标不同，不妨改变一下式子的形式，将两边的 $x$ 的位置交换一下：

$(x_j+y_j)<(x_i+y_i)$

这时我们就会惊奇的的发现，这不就是二者的和吗？

所以我们可以得出结论：

当一组数的和的值大于另一组时，我们选择让和大的那一组作为减数，小的那一组作为加数。

代码实现也很简单，对于原序列按和从小到大排序，取前 $(n/2)$ 组数作为加数，后面的作为减数。

（记得开 long long）

完整代码：

```c++
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
const int N=5e6+10;
int n;
struct node{
	ll a,b,sum;
}x[N];
bool cmp(node xw,node yw){
	return xw.sum<yw.sum;//按和排序
}
ll ans=0;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&x[i].a,&x[i].b);
		x[i].sum=x[i].a+x[i].b;
	}
	sort(x+1,x+n+1,cmp);
	for(int i=1;i<=n/2;i++){
		ans+=min(x[i].a,x[i].b);//前 n/2 个作为加数
 	}
	for(int i=n/2+1;i<=n;i++){
		ans-=max(x[i].a,x[i].b);// 后面的作为减数
	}
	printf("%lld",ans);//输出结果
	return 0;
}
```



---

## 作者：HohleFeuerwerke (赞：5)

~~供题人自己来水一波题解。~~

[题目](https://www.luogu.com.cn/problem/P5963)在此。

## 前言

本题曾经是供题人自己上课时老师给供题人的。那次老师讲的是贪心。

本题贪心标签就是由此而来的。但是，本题和贪心还是有那么一点点得关系的。

不知道大家知不知道贪心有一种方法叫微调法。

## 正文

#### 关于样例

样例强度很高。

所以可以这样理解题面：我现在就有 $6$ 张卡，每张卡的正反面数就是按照样例来的。

这时可以尝试：因为要使得结果最小：

如果减号框里填大数：
$$0+(-2)+1-12-10-7=-30>-34$$

如果加号框里填小数：
$$(-8)+(-7+)+(-3)-5-7-4=-34$$

咦？好像对了？

交上去，试试看吧，我没试过。~~拿不到分的。~~

---

#### 部分分

$n\leq 8$ ？？？

毅然暴力，结果复杂度 $O(n!2^n)$，应该可以卡着时限过。
$$8!\cdot2^8=10321920$$

交上去，试试看吧，我没试过。~~只有30分的。~~

---

#### 正解

对于每张卡，令 $sum_i=A_i+B_i$ 且 $A_i>B_i$。

对于任意两张卡 $i$ 和 $j$ $(i,j∈\{1,2,3,...,n\})$，若 $sum_i>sum_j$：

因为 $A_i+B_i>A_j+B_j$ ，则 $B_j-A_i<A_j-B_i$。

这个结论可以推广：因为要结果最小，所以尽量使 $sum_i$ 较大的 $A_i$ 放在减号框里，否则总可以通过交换卡片位置并反转使得结果更小，原因见上。

所以得到贪心策略：取卡牌 $sum$ 值大的一半的 $A_i$ 放在减号框内，$sum$ 值小的一半的 $B_i$ 放在加号框内。此时的结果最小。

实现过程：按照 $sum$ 值排序后，计算。策略如上。

```cpp
#include<iostream>
#include<algorithm>
#pragma GCC optimize(3)
#define MAXN 5000005
#define int long long
using namespace std;
int n,ans;
struct card{
	int a,b,sma,big,sum;
}a[MAXN];
bool cmp(card a,card b){
	return (a.sum>b.sum);
}
signed main(){
    ios::sync_with_stdio(false);
    cout.tie(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].a>>a[i].b;
		a[i].sum=a[i].a+a[i].b;
		if(a[i].a>a[i].b)
			a[i].sma=a[i].b,a[i].big=a[i].a;
		else
			a[i].big=a[i].b,a[i].sma=a[i].a;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=(n+1)/2;i++) ans-=a[i].big;
	for(int i=(n+1)/2+1;i<=n;i++) ans+=a[i].sma;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：qwq自动机 (赞：4)

solution for [BalticOI 2005 Card](/problem/P5963)

---

题意简述就不放了，上面有链接，我直接讲思路。

首先显然考虑暴力。深搜枚举每张卡片放正面 / 反面以及位置，然后更新答案和最大值。这种做法的复杂度为 $O(n!\cdot 2^n)$，可以卡时限过掉 30pts。

代码就不放了。不过好像这里可以加上一些奇怪的剪枝？

---

这里就直接讲正解吧。

首先容易~~从题目标签~~看出此题需要贪心，但是显然如果我们将大的填在减号后面的框里，小的填在加号框里，有时是不能得到最优解的（具体可以看 @[TO_the_End](/user/368225) 题解里面的 Hack 数据）。

首先令每张牌两面最大的数为 $A_i$，最小的数为 $B_i$，那么显然在减号后面的框里的数必定是 $B_{\text{什么东西}}$，而加号框后面的数必定是 $A_{\text{什么东西}}$（容易证明qwq）。

那么考虑两个相邻的框，假设为“-O+O”的情况。设最优解时填入两个框中的牌编号为 $i$ 和 $j$，则可知此时两个框的情况必是 $-A_i+B_j$ 或 $-A_j+B_i$。不妨设填入的情况是 $-A_i+B_j$，那么这个数必定比 $-A_j+B_i$ 小（想想为什么 =w=），即：

$$
\begin{array}{ll}
&\quad-A_i+B_j<-A_j+B_i\\
&\Rightarrow A_i+B_i>A_j+B_j
\end{array}
$$

所以若设 $sum_i=A_i+B_i$，可以发现减号框中牌的 $sum$ 必定比加号框中牌的 $sum$ 大。那么我们就可以把牌按照 $sum$ 排序，然后取 $sum$ 大的那一半作为减号框中的牌（然后将 $A$ 填入），剩下的作为加号框中的牌（然后将 $B$ 填入）。如果排序用快排之类的话那么复杂度是时 $O(n\log n)$ 空 $O(n)$，考虑到 $n\leq 5\times10^5$，显然能够通过。

---

下面上代码（但是不要 ctj 哦~）！

C++:

```cpp
#include <algorithm>
#include <iostream>
struct Card
{
    long long a, b;
    bool operator<(const Card &c) const // 重载运算符，当然可以写一个另外的 cmp 函数
    {
        return a + b > c.a + c.b; // 按 sum 从大到小排序
    }
} a[500010];
int main()
{
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i].a >> a[i].b;
    std::sort(a + 1, a + 1 + n); // 排序
    long long ans = 0;
    for (int i = 1; i <= (n + 1) / 2; i++) // 取 sum 大的一半填入减号框
        ans -= std::max(a[i].a, a[i].b);
    for (int i = (n + 1) / 2 + 1; i <= n; i++) // 剩下的填入加号框
        ans += std::min(a[i].a, a[i].b);
    std::cout << ans;
    return 0;
}
```

Python：

```python
class Card:
    def __init__(self, valA, valB):
        self.a = valA
        self.b = valB

def getKey(card):
    return card.a + card.b

n = int(input())
cards = []
for i in range(n):
    s = input().split()
    cards.append(Card(int(s[0]), int(s[1])))
cards.sort(key = getKey, reverse = True)
ans = 0
for i in range((n + 1) // 2):
    ans = ans - max(cards[i].a, cards[i].b)
for i in range((n + 1) // 2, n):
    ans = ans + min(cards[i].a, cards[i].b)
print(ans)
```

当然，上面的代码都是不能 AC 的：C++ 会 RE #6，Python 会 TLE #6、MLE #9。为什么呢？因为 #6 的 $n$ 是大于 $5\times 10^5$，而 Python 的速度十 · 分 · 感 · 人 =w=（#9 亲测 $n=5\times10^5$）。到底怎么改能 AC 呢？C++ 把数组稍微开大一点点，然后 Python 的话……~~换 C++ 吧 /xk~~。

---

## 作者：WinterRain208 (赞：3)

题解 P5963 [BalticOI2005] Card 卡牌游戏

### 题意概述

在若干个用加减号链接的框框里放入卡牌，每张卡拍有正反两面。

输出防止后表达式的最小值，数据$5e5$。

考虑$dp$，情况不满足后效性，排除，主要想如何贪心（良心出题人给出了标签）。

### 做法

大的数字全部填在减号框框里，排序时以$max(A_i,B_i)$作为第一关键字。

同理可得小的数字全填在加号框里，排序时以$min(A_i,B_i)$作为第一关键字。

可得上面两种算法都是不正确的。我们可举出反例$hack$（下面这组是前者）。

```
3
2 1
3 1  
4 -10

```
输出-5，正确答案为-12，同理可得后者的$hack$数据。

搜索。

深搜判断位置及正反面，对于每个卡片$card_i$，枚举位置$place_i$和正反面$face_i$。

前者复杂度为$O(n!)$，后者为$O(2_n)$，可以通过百分之三十的数据，代码不放了。

这个算法的缺点就是时间不够。

考虑正确的贪心。

设$sum_i=A_i+B_i(A_i>B_i)$

设$sum_i>sum_j$($i$不等于$j$)

则有$A_i+B_i>A_j+B_j$

移项得$A_i-B_j>A_j-B_i$

于是又有$B_j-A_i<A_j-B_i$

为了使表达式最小，我们按$sum_i$排序，从大到小，前一半取$A_i$，后一半取$B_i$。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,r) for(int i=j;i<=r;++i)
#define D(i,j,r) for(int i=j;i>=r;--i)
#define INF 0x3f3f3f3f

using namespace std;
const int N=5e6+5;

long long read(){
	long long f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<3)+(x<<1)+s-'0';s=getchar();}
	return x*f;
}

inline void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
	return;
}
struct card{
	long long tot,a,b,big,small;
}c[N];

bool cmp(card x,card y){
	return x.tot>y.tot;
}

long long n,ans=0; 
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	F(i,1,n){
		cin>>c[i].a>>c[i].b;
		c[i].tot=c[i].a+c[i].b;	
		if(c[i].a>c[i].b)c[i].big=c[i].a,c[i].small=c[i].b;
		else c[i].big=c[i].b,c[i].small=c[i].a;
	}
	sort(c+1,c+1+n,cmp);
	F(i,1,n)
		if(i<=(n+1)/2)ans-=c[i].big;
		else ans+=c[i].small;
	cout<<ans;
    return 0;
}

```

我没有用快读是因为用快读WA了一个点。

点赞！谢谢！

---

## 作者：AKPC (赞：2)

贪心板子题。
### 思路
假设 $n=2$，给出的两张卡牌为 $\{x_1,y_1\},\{x_2,y_2\}$。对于任意的 $i$，我们设定 $x_i\geq y_i$。

因为表达式有加有减，显然，较大的数用来减，较小的数用来加是最好的。那么，对于 $\{x_1,y_1\},\{x_2,y_2\}$ 这两张牌，有两个方案：$-x_1+y_2$ 和 $-x_2+y_1$。

若 $-x_1+y_2 \leq -x_2+y_1$，则根据不等式的性质，移项后变为 $x_1+y_1 \geq x_2+y_2$。

同理，若 $-x_1+y_2 > -x_2+y_1$，则根据不等式的性质，移项后变为 $x_1+y_1 < x_2+y_2$。

显然，在 $n=2$ 的时候，当 $A$ 卡牌两面的和大于 $B$，我们选用 $A$ 卡牌较大的数来减，$B$ 较小的用来加。

那么我们将问题延伸到 $n > 2$ 该怎么办呢？很简单，选用卡牌数字之和前 $\dfrac{n}{2}$ 小的卡牌中较小的数加，剩余的卡牌较大数加即可。注意开 long long！
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,ans;
struct node{int a,b,x;}d[5000001];
inline bool cmp(node o,node p){return o.x<p.x;}
signed main(){
	cin>>n;
	for (register int i=1;i<=n;i++) cin>>d[i].a>>d[i].b,d[i].x=d[i].a+d[i].b;
	sort(d+1,d+n+1,cmp);
	for (register int i=1;i<=n/2;i++) ans+=min(d[i].a,d[i].b);
	for (register int i=n/2+1;i<=n;i++) ans-=max(d[i].a,d[i].b);
	cout<<ans;
	return 0;
}
```

---

## 作者：改名但没卡67 (赞：2)

写一个题解里没有的思路。

题意：

你手上有 n 张卡牌，要求将其填入框中，使得结果最小。

每张卡有两面：即每张卡有两个数字。666 不能当作 999 使用，同理，999 也不能当作 666 使用。

框与框之间有计算符号。计算符号以 - 和 + 间隔。

例如：当 $n=8n=8n=8$ 时，填入的框格式为：-O+O-O+O-O+O-O+O。

填入卡牌时，不一定需要按照卡牌和框的顺序进行填写（即可以进行位置的调换）。

首先考虑暴力（~~然后发现暴力就能过~~），考虑 $30pts$ 的暴力，非常简单，直接 DFS 搜索就好了（~~但我考场上不会写暴力~~）。

然后考虑如何优秀的过了这道题，首先很简单的一个想法，每个牌尽量选择对答案贡献大的一面，贡献大小通过他们的绝对值判断。

然后我们想，加号和减号是有固定个数的，那我们如何取舍呢？很容易想出计算出每张牌的差值，也就是它每一面的差值（这个差值的定义在下面有提及），然后按差值排序，先让差值大的选择更优的一面，等到需要的符号不够了再选择较差的一面。

需要的符号就是能让这个牌的贡献为负数或者为零。

对于符号相同的，差值为它们绝对值的和，而对于符号相反的，差值为他们绝对值的差。

这种贪心为啥正确呢？

很显然，如果差值大的话，你选择贡献小的与选择贡献大的对答案造成的贡献之差就是他们的差值。所以我们为了总体上对答案的贡献尽量大，要以差值大的优先选择。但是符号不够的话，我们为了让这张牌对答案的影响尽量小，要选择这张牌绝对值小的一面，也就是差的一面，这样是最优的。

还有什么不懂得可以私信问我，很简单的一道题，稍微想想就好。

下面放上代码吧。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#define int long long
#define rad scanf
using namespace std;
const int kM = 1e6 + 10;
int n;
struct js
{
	int a, b, cha, you, lue;
}a[kM];
int ans, zf, ff;
bool cmp(js x, js y)
{
	return x.cha > y.cha;
}
signed main()
{
//	freopen("arcaea.in", "r", stdin);
//	freopen("arcaea.out", "w", stdout);
	rad("%lld", &n);
	if(n % 2 == 0)
	{
		zf = ff = n / 2;
	}
	else
	{
		zf = n / 2, ff = n / 2 + 1;
	}
	for(int i = 1; i <= n; i++)
	{
		rad("%lld%lld", &a[i].a, &a[i].b);
		if((a[i].a * a[i].b) >= 0)
		{
			a[i].cha = abs(a[i].a + a[i].b);
		}
		else
		{
			a[i].cha = max(abs(a[i].a), abs(a[i].b)) - min(abs(a[i].a), abs(a[i].b));
		}
		if(abs(a[i].a) > abs(a[i].b))
		{
			a[i].you = a[i].a;
			a[i].lue = a[i].b;
		}
		else
		{
			a[i].you = a[i].b;
			a[i].lue = a[i].a;
		}
	}
	sort(a + 1, a + 1 + n, cmp);
	for(int i = 1; i <= n; i++)
	{
		if(a[i].you >= 0)
		{
			if(ff > 0)
			{
				ff--;
				ans -= abs(a[i].you);
				continue;
			}
		}
		else if(a[i].you <= 0)
		{
			if(zf > 0)
			{
				zf--;
				ans -= abs(a[i].you);
				continue;
			}
		}
		if(a[i].lue >= 0)
		{
			if(ff > 0)
			{
				ff--;
				ans -= abs(a[i].lue);
			}
			else
			{
				zf--;
				ans += abs(a[i].lue);
			}
			continue;
		}
		else
		{
			if(zf > 0)
			{
				zf--;
				ans -= abs(a[i].lue);
			}
			else
			{
				ff--;
				ans += abs(a[i].lue);
			}
		}
	}
	cout<<ans;
	return 0;
}
/*
6
-8 12
0 5
7 -3
10 -7
-2 7
1 4
*/
```


---

## 作者：Teto_etf (赞：0)

### 题目大意

$n$ 组数对，从每组中取一个数进行设定好的加减运算，最小化结果。

### 思路分析

本题的正解是 **贪心**。

首先亮出结论：将 $n$ 组数对 $(x_1,y_1),\cdots,(x_n,y_n)$ 按照 $x_i+y_i$ 作为关键字从小到大排序。将前一半数对取小一点的数加到结果，将后一半数对取大一点的数减到结果。

### 证明

取第 $i$ 和第 $j$ 组数对。根据题面，加减号是如下设定的：

```
-O+O-O+O-O+O-O+O-...
```

所以**因为加减号是交替设定的**，所以两组数对**只能一加一减**。我们容易发现一组数对里两个数的大小关系对结果没有影响，所以我们可以大胆假设数对的第一个数大于等于第二个数。

形式化地来讲，两组数对只有两种情况，$y_i-x_j$ 或 $y_j-x_i$。（为什么 $y_i$ 是加而 $x_i$ 是减？**因为要想结果最小，应该让较小的数减较大的数，而我们规定了第一个数 $\textbf{x}$ 大于等于第二个数 $\textbf{y}$，所以 $\textbf{y}$ 要在前。**）

当我们选了一个数对，根据题面要求（应该最小化结果），所以这就代表着我们选的数对小于或等于另一个数对。

不妨设我们选了第一种情况，$x_i-y_j$，有如下不等式：

$$y_i-x_j \le y_j-x_i$$

整理得

$$y_i+x_i \le y_j+x_j$$

可以发现，这就是开始时的两组数对的和的大小关系。

推广到一般的数组情况，就可以得出开始时的结论了：

> 将 $n$ 组数对 $(x_1,y_1),\cdots,(x_n,y_n)$ 按照 $x_i+y_i$ 作为关键字从小到大排序。将前一半数对取小一点的数加到结果，将后一半数对取大一点的数减到结果。

### 坑点

我开了 $5 \times 10^5$ 的数组过不去，要开两倍空间才能过。

要开 `long long` 才能过。开 `int` 只有 $30$ 分。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
using namespace std;

int n;
const int maxn = 5e5 + 10;
int mini = 0;

struct G { int x, y, sum; } group[maxn << 1];

inline bool cmp(G A, G B) { return A.sum < B.sum; }

signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        group[i].x = x, group[i].y = y, group[i].sum = x + y;
    }
    
    sort(group + 1, group + n + 1, cmp);
    
    for (int i = 1; i <= n / 2; i++) mini += min(group[i].x, group[i].y);
    for (int i = n / 2 + 1; i <= n; i++) mini -= max(group[i].x, group[i].y);
    cout << mini << endl;
    return 0;
}
```

---

## 作者：whx2009 (赞：0)

* [传送门](https://www.luogu.com.cn/problem/P5963)
## 本题思路：
这道题很多人一看就蒙逼了，感觉很简单，他要求最小值就直接把小的放到 $-$ 前面，大的放到 $+$ 前面，负数直接放到 $+$ 号前面，这样输出就最小了。

可是怎么样知道这组数字到底是放 $+$ 还是放 $-$ 呢？我去试了一下样例就发现了一个小技巧，我们只需要把这两个数字相加记录他们的和，只要和小的直接把这组数中间小的放到 $+$ 中（因为和小的要么这里面有负数，要么数字十分小，放进去都能被后面的大数所抵），和大的直接把这组数中最大的放到 $-$ 后面（因为和大的一定会有一个很大的数，放进去一定能保证结果最小）。这样输出就可以了。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
struct f{
	int x,y,sum;
}a[500001];
int cut(f x,f y){return x.sum<y.sum;}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;
		a[i].sum=a[i].x+a[i].y;//记录和
	}
	sort(a+1,a+n+1,cut);//排序
	for(int i=1;i<=n/2;i++) ans+=min(a[i].x,a[i].y);//加最小的
	for(int i=n/2+1;i<=n;i++) ans-=max(a[i].x,a[i].y);//加最大的
	cout<<ans;
	return 0;//完结撒花！！！
}
```
* 请勿抄袭

---

## 作者：xxxxxzy (赞：0)

一眼贪心 ~~标签是贪心~~。

肯定不是简单贪心，那就多半是排序不等式贪心了。

设两张卡牌 $A,B$ 双面分别为 $a_{1},a_{2},b_{1},b_{2}$。

不妨设 $a_{1}>a_{2},b_{1}>b_{2}$，肯定拿最大的数拿取减，最小的数拿去加。

$A$ 拿去减，贡献为 $-a_{1}+b_{2}$，$B$ 拿去减时，贡献为 $-b_{1}+a_{2}$。

那么用 $A$ 来减的充要条件就是 $-a_{1}+b_{2}<-b_{1}+a_{2}$。

移项得 $b_{1}+b_{2}<a_{1}+a_{2}$。

然后就可以进行排序，由于 $n$ 为奇数时减号会多一个，所以从 $1$ 到 $\left \lfloor \frac{n}{2} \right \rfloor $ 就是要加的，从 $\left \lfloor \frac{n}{2} \right \rfloor $ 到 $n$ 就是要减的。

这就做完了。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
struct s{
	int a,b;
}tt[1000005]; 
bool cmp(s p,s q){
	return p.a+p.b<q.a+q.b;
}
int n,ans;
signed main(){
    cin>>n;
    for(int i=0;i<n;i++) cin>>tt[i].a>>tt[i].b;
    sort(tt,tt+n,cmp);
    for(int i=0;i<n/2;i++) ans+=min(tt[i].a,tt[i].b);
	for(int i=n/2;i<n;i++) ans-=max(tt[i].a,tt[i].b);
	cout<<ans; 
}
```



---

## 作者：Ferdina_zcjb (赞：0)

看到最值，在联系题目，可以想到贪心。

穷举只有 30 分，此处就不提了，时间复杂度 $\mathcal O(n! \times 2^n)$。

# 贪心
设 $num_i$ 表示 $A_i+B_i$。

有如下结论：当 $num_i$ 相对于其他值较大时，尽量进行减运算（即 $- \max(A_i,B_i)$），反之较小时，进行加运算（即 $+ \min(A_i,B_i)$）。

因此，只需要用数组进行记录 $A_i$ 与 $B_i$ 和 $num_i$ 的值，在以 $num_{1,2 ... n}$ 的值从小到大进行排序，前 $\lfloor\frac{n}{2}\rfloor$ 为进行减运算的值，则后 $\lceil\frac{n}{2}\rceil$ 为进行加运算的值。 

贪心的证明：

设有两个数集 $\{a_i,b_i\}$，$\{a_j,b_j\}$ $(a > b)$。

不妨先设：
$$-a_i+b_j<-a_j+b_i$$

$$\downarrow$$

$$b_j+a_j < b_i+a_i$$

即：

$$num_j < num_i$$

得出上述结论。

代码如下，时间复杂度 $\mathcal O(n \log n)$：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
    int a,b,num;
}ABC[5000001];
bool cmp(const node a,const node b){return a.num < b.num;}//cmp即以num的值从小到大排序。
int n,sum;
signed main(){
    scanf("%lld",&n);
    for(int i = 1;i <= n;++i){
        scanf("%lld%lld",&ABC[i].a,&ABC[i].b);
        ABC[i].num = ABC[i].b+ABC[i].a;
    }
    sort(ABC+1,ABC+n+1,cmp);
    int l = 1,r = n;//l为前(n/2)的数组下标，则r为后 ceil(n/2)的数组下标。
    while(l <= r){
        if(l == r)sum -= max(ABC[l].a,ABC[l].b);//分类讨论。
        else sum = sum + min(ABC[l].a,ABC[l].b) - max(ABC[r].a,ABC[r].b);
        l++,r--;
    }
    printf("%lld",sum);
}
```


---

## 作者：lidundun (赞：0)

# Card 卡牌游戏
大概的思路如下：把输入的 $a$ $b$ 求和存到 $s$ 里，再用 $max$ 和 $min$ 把 $a$ 和 $b$ 的最大最小值存起来（结构体）。

将整个结构体大到小排序后，将 $ans$ 加上前（包括） $(n+1)/2$ 项的 $mn$ ，减掉后面所有项的 $mx$ ，输出即可。
# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans;//数据太大，int只能过#3
struct cmd{
	int a;
	int b;
	int s;
	int mn;
	int mx;
}t[5000010];
bool cmp(cmd a,cmd b){
	if(a.s>b.s)  return 1;
	else  return 0;
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&t[i].a,&t[i].b);
		t[i].s=t[i].a+t[i].b;
		t[i].mx=max(t[i].a,t[i].b);
		t[i].mn=min(t[i].a,t[i].b);
	}
	sort(t+1,t+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		if(i<=(n+1)/2)  ans-=t[i].mx;
		else  ans+=t[i].mn;
	}
	printf("%lld",ans);
}
```


---


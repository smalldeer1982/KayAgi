# Maximum Sum on Even Positions

## 题目描述

给定一个包含 $n$ 个元素的序列（下标从 $0$ 到 $n-1$），你可以选择一个连续区间进行翻转，使得翻转过后的序列偶数项的总和（即 $a_0,a_2,\ldots,a_{2k}$ 的和，其中 $k=\lfloor \dfrac{n-1}{2} \rfloor$）最大。

## 样例 #1

### 输入

```
4
8
1 7 3 4 7 6 2 9
5
1 2 1 2 1
10
7 8 4 5 7 6 8 9 7 3
4
3 1 2 1```

### 输出

```
26
5
37
5```

# 题解

## 作者：b6e0_ (赞：8)

[CF题面传送门](https://codeforces.com/contest/1373/problem/D) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1373D) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1373D)

如果想翻转使得答案更大，那么就要考虑奇数位与偶数位的数之间的差。这里分成两种情况分别计算取$\max$：$a_1-a_0,a_3-a_2,a_5-a_4\cdots$和$a_1-a_2,a_3-a_4,a_5-a_6\cdots$。

下面我们就要求：在一个序列$a$中，找出一个区间$[l,r]$使得$\sum_{i=l}^{r}a_i$最大。这就是一个经典问题：最大子段和。最大字段和有两种做法：扫描或dp。这里就讲比较方便的扫描方法。

扫描其实是一个贪心。如果发现某一个点的前缀和变成负数了，那么明显不能要前面这个区间，否则会拉低后面的区间。所以，得出以下做法：累加前缀和，每累加一个就比$\max$，如果累加成负数了就清零。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200010];
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,i,ans1=0,ans2=0,sum=0,ans=0;
		cin>>n;
		for(i=0;i<n;i++)
		{
			cin>>a[i];
			if(!(i&1))
				ans+=a[i];//先统计偶数位
		}
		vector<int>aa,b;//上面数组用了a的名称，所以这儿用aa
		for(i=1;i<n;i+=2)
			aa.push_back(a[i]-a[i-1]);
		for(i=0;i<aa.size();i++)
		{
			sum+=aa[i];//累加
			if(sum<0)//如果为负数
				sum=0;//清零
			ans1=max(ans1,sum);//比max
		}
		for(i=2;i<n;i+=2)
			b.push_back(a[i-1]-a[i]);
		sum=0;
		for(i=0;i<b.size();i++)
		{
			sum+=b[i];//累加
			if(sum<0)//如果为负数
				sum=0;//清零
			ans2=max(ans2,sum);/比max
		}
		cout<<ans+max(ans1,ans2)<<endl;
	}
	return 0;
}
```
时间复杂度为$O(n)$。

---

## 作者：Keith_2006 (赞：6)

## CF1373D Maximum Sum on Even Positions 题解

#### 一道难度不是很大的题目

---

### 题目大意

给你一串**从 $0$ 开始**的序列，你有一次机会翻转一个连续子序列，求翻转过后偶数位和的最大值。

---

### 题目分析

题目中说数列下标 $0$ 到 $n-1$，我这里改成了 $1$ 到 $n$。注意此时原来 $a_0,a_2,\ldots,a_{2k}$ 这些位置就变为了 $a_1,a_3,\ldots,a_{2k+1}$，即新数列的奇数项。

容易如果翻转的长度为奇数，那么此时奇数项和偶数项的和是不变的。这是因为相互交换的几组数据的下标奇偶性是相同的，那么翻转后数列奇数项或偶数项上的数不变。

如果翻转的长度为偶数，那么相当于在那个区间中，奇数项和偶数项进行了调换，那么奇数项的总和增加量即为调换区间中每一个偶数项减去奇数项之差的和。

举个例子，对于 $1,1,4,5,1,4$ 这个序列，翻转第二项到第五项，得到 $1,1,5,4,1,4$。奇数项的增加量为 $5+1-4-1=(1-4)+(5-1)=1$。

我们以两个连续的数位为一组进行分组。容易发现，根据分组方式和序列长度的奇偶性，有以下四种情况。
![](https://cdn.luogu.com.cn/upload/image_hosting/cyismciz.png)

对于由横线相连的两项，计算偶数项减去奇数项的值，得到一个新的序列 $b$。容易发现，这个序列表示的就是奇偶项调换后奇数项和的增加值。

如果我们选择这个 $b$ 序列中的一项，就相当于我们在 $a$ 序列中选择了对应的两项，这两项在被翻转的子序列中。

因此，为了让调换后奇数项的总和最大，我们需要让每一个数对的贡献总和最大（也就是 $b$ 序列中的值之和最大）。又因为调换的是连续的区间，所以这个问题就转化成了 $b$ 序列中的一个**最大连续子区间和**的问题，可以利用简单的 DP 解决。两种分组方式取最大值即为答案。

复杂度分析：预处理的分组和 DP 都是 $\mathcal{O}(n)$ 的，所以总复杂度为 $\mathcal{O}(n)$。

---

### 代码实现

总体来说需要稍微细心一点，多做一些判断和分类，循环条件和初始值不要写错。我这里采取了相对复杂但是易懂的写法。

注意开 `long long`。

以及，使用这种写法由于循环比较多，常数有点大，最好优化一下常数。（快读，少 `memset` 等）

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>

#define ll long long

using namespace std;

inline ll read() {
	ll x=0,f=1;
	char ch=getchar();
	while (!isdigit(ch)) {if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return x*f;
}

const int N=2e5+5;

ll a[N],b1[N],b2[N],f1[N],f2[N]; //需要开 long long
int cnt1,cnt2;

int main() {
	int t=read();
	while (t--) {
		memset(f1,0,sizeof(f1));
		memset(f2,0,sizeof(f2));
		cnt1=cnt2=0;
		int n=read();
		for (int i=1;i<=n;i++) {
			a[i]=read();
		}
        //分类计算 b 数组
		if (n&1) {
			for (int i=1;i<=n-2;i+=2) {
				b1[++cnt1]=a[i+1]-a[i];
			}
			for (int i=2;i<=n-1;i+=2) {
				b2[++cnt2]=a[i]-a[i+1];
			}
		} else {
			for (int i=1;i<=n-1;i+=2) {
				b1[++cnt1]=a[i+1]-a[i];
			}
			for (int i=2;i<=n-2;i+=2) {
				b2[++cnt2]=a[i]-a[i+1];
			}
		}
		f1[0]=0;
		for (int i=1;i<=cnt1;i++) {
			f1[i]=max(b1[i],f1[i-1]+b1[i]); //最大连续子区间和
		}
		ll res1=-1e15;
		for (int i=1;i<=cnt1;i++) {
			res1=max(res1,f1[i]);
		}
		f2[0]=0;
		for (int i=1;i<=cnt2;i++) {
			f2[i]=max(b2[i],f2[i-1]+b2[i]); //最大连续子区间和
		}
		ll res2=-1e15;
		for (int i=1;i<=cnt2;i++) {
			res2=max(res2,f2[i]);
		}
		ll ans=0;
		for (int i=1;i<=n;i++) {
			if (i%2==1) ans+=a[i];
		}
		if (res1<0&&res2<0) printf("%lld\n",ans); //如果翻转还不如不翻转，就输出本来的奇数项和
		else printf("%lld\n",ans+max(res1,res2));
	}
	return 0;
}
```

---

完结撒花qwq

如果觉得有帮助不妨点个赞，如果写得不好也欢迎指出。（毕竟我是个大菜鸡）

---

## 作者：cyh_toby (赞：2)

# 题意

原题：[CF1373D 【Maximum Sum on Even Positions】](https://www.luogu.com.cn/problem/CF1373D)

大概就是给定一下标从 $0$ 开始的序列，可以任意翻转但仅限一次某一个区间，问最终偶数位上的数的和最大是多少。

# 分析

方便起见，我们把序列转换为下标从 $1$ 开始。那么题目变成求奇数位上的和最大值。

假设翻转区间 $\big[l\,,\,r\big]$ 。显然 $l$ 与 $r$ 奇偶性相同时等于没有操作。所以显然我们要么选择 $l$ 与 $r$ 奇偶性不同的区间翻转，要么不翻转。

记整个序列**奇数位**上和为 $sum$ ，翻转的区间中偶数位上和为 $sum_0$ ，奇数位上和为 $sum_1$ 。

根据上述结论，如果要翻转，我们肯定会选择奇偶不同的 $l$ 和 $r$。这意味着，翻转必定使得翻转区间内 奇数位上数的和 与 偶数位上数的和 交换。则答案为 $sum + sum_0 - sum_1$ 。因此需要最大化 $sum_0 - sum_1$ 。用前缀和表达就是最大化 $\big(s_0[r] - s_0[l-1]\big) - \big(s_1[r] - s_1[l-1]\big)$ ，其中 $s_0$ 表示前缀中偶数位上的和，$s_1$ 表示前缀中奇数位上的和。

考虑把奇数位上的数变成其相反数，那么上式转化为 $s[r] - s[l-1]$ ，其中 $s$ 表示变更后的序列的前缀和。为了方便，我们记 $R = r\,,\,L = l-1$ 。所以转换为求 $s[R] - s[L]$ 的最大值，其中满足 $0 \le L < R \le n$ **并且** $L\,,R\,$ **奇偶性相同**。又注意到 $L = R$ 意味着不翻转，故也是合法取值方案。因此最终答案就是：

$$sum + \max\limits_{0\le L \le R \le n\,,\,L\text{和}R\text{奇偶相同}} \bigg(s[R] - s[L\bigg)$$

显然这个最大值可以遍历一遍 $s$ 数组就能线性计算。至于奇偶相同这个条件，分开存奇、偶的相关参数并分开计算即可。具体见代码。

# 细节处理

注意 $L = l-1$ ，因此 $0 \le L$ 而非 $1 \le L$ 。

# 源码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5;
typedef long long ll;

int n;
ll a[N], s[N];
ll ans;

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		ans = 0;
		
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &a[i]);
			if (i % 2 == 1) {
				s[i] = s[i-1] - a[i];
				ans += a[i];
			}
			else
				s[i] = s[i-1] + a[i];
		}
		
		ll tmp1 = 1e15, tmp0 = 1e15, res = -1e15;
		for (int i = 0; i <= n; i++) {
			if (i % 2 == 1) {
				tmp1 = min(tmp1, s[i]);
				res = max(res, s[i] - tmp1);
			}
			else {
				tmp0 = min(tmp0, s[i]);
				res = max(res, s[i] - tmp0);
			}
		}	
		
		printf("%lld\n", ans + res);
	}
	
	return 0;
}
```






---

## 作者：do_while_true (赞：2)

[$\color{RoyalBlue}\text{题目链接}$](https://codeforces.com/contest/1373/problem/D)

可能影响阅读的点:

1.本文中除代码外下标默认从 $0$ 开始


------------

纸上模拟一下倒置一段子区间，发现如果子区间内的偶数位置有替换，则一定是都替换成它们相邻的奇数位置。

什么意思呢，打个比方我们的原序列为

$$\color{red}1\color{black}\ \ 7\color{red}\ \  3\color{black}\ \ \boxed{4\color{red}\ \  7\color{black}\ \ 6\color{red}\ \ 2\color{black}}\ \ 9$$

红色位置即为我们会算进答案的位置。

我们来把下标 $3$ 到 $6$ 进行倒置。

$$\color{red}1\color{black}\ \ 7\color{red}\ \  3\color{black}\ \ \boxed{2\color{red}\ \  6\color{black}\ \ 7\color{red}\ \ 4\color{black}}\ \ 9$$

$7$ 被踢下去，但是它旁边的 $4$ 上来了，$2$ 被踢下去，但是它旁边的$6$ 上来了。
 
也就是说当序列长度为偶数的时候，原偶数位置的数就会都被替换成奇数位置。

即序列 $a_l,a_{l+1},a_{l+2}...a_r$

被倒置时，$a_i$ 到达了 $a_{l+r-i}$ ，因为序列长度为偶数，所以 $l+r$ 为奇数，则 $i$ 的奇偶性一定比换后的 $l+r-i$ 奇偶性不同。所以会产生偶数位置都会被替换成奇数位置的数。

当 $l$ 为奇数， $r$ 为偶数的时候，序列中对答案的贡献会减去每个 $a_i$ ($i$ 为偶数) 都会加上每个 $a_{i-1}$。

反之，都会加上每个 $a_{i+1}$。

所以我们发现对答案的贡献是一个子段和 $\ $ (偶数位减去，奇数位加起来) $\ $ 的形式。

则我们处理出每个 $a_i$($i$ 为偶数) 和它前一位的差，跑最大子段和即可处理出当 $l$ 为奇数，$r$ 为偶数时对答案的最大贡献。

同样的处理每个 $a_i$($i$ 为偶数) 和它后一位的差跑最大子段和，两个取 $\max$ 算进答案里即可。

[$\mathcal{Code}$](https://codeforces.com/contest/1373/submission/85034948)

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
int T,n;
ll a[200010];
ll dp[200010],b[200010],cnt;
ll dp2[200010],b2[200010],cnt2;
unsigned ll sum,sum2,ans;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		ans=cnt=cnt2=sum=sum2=0;
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++) {
			if(i%2==0)
				b[++cnt]=a[i]-a[i-1];
			else
				ans+=a[i];
			if(i%2==0&&i!=n)
				b2[++cnt2]=a[i]-a[i+1];
			dp2[i]=dp[i]=0;
		}
		for(int i=1;i<=cnt;i++) {
			dp[i]=max(b[i],dp[i-1]+b[i]);
			dp2[i]=max(b2[i],dp2[i-1]+b2[i]);
			if(dp[i]>0) sum= 1llu*dp[i]>sum ? 1llu*dp[i] : sum;
			if(dp2[i]>0) sum= 1llu*dp2[i]>sum ? 1llu*dp2[i] : sum;
		}
		ans += sum>=0 ? sum : 0;
		printf("%llu\n",ans);
	}
	return 0;
}
```

---

## 作者：Thomas_mum (赞：1)

不得不说这道题有无数个做法  
我的方法应该算暴力或模拟，如果想要打更优雅的程序~~本蒟蒻不会，可以找[他](https://www.luogu.com.cn/user/843733)问问看~~。    
~~我的语文不咋好 若有错句错词还请包涵~~。
# 思路
题中说明只能旋转一次，我们可以将其理解成两种情况：  
1. 旋转区间长为奇数。  
2. 旋转区间长为偶数。

面对第 一 种情况我们可以发现：偶数位上的数字并没有发生改变，故不用进行考虑。

而另外一组就相当于一段区间内 奇数位与偶数位颠倒。

综上所述 我们只需要找到一段区间满足以下条件，再用这段区间内**奇数位减偶数位的差**加上**偶数位的和**就行了。

条件：  
1. 奇数位减偶数位的差最大。  
2. 旋转区间长为偶数。

我们再进一步简化：


$n$ 为任何数时，都有两列更换方式（每个偶数可以选择与前面的奇数交换（代码中情况一）或与其后面的奇数交换（代码中情况二））。  
如自造样例：  
```
3
1 2 3 
```
可以 $1$ 和 $2$ 更换；  
也可以 $3$ 和 $2$ 更换。   

# 代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int _;  //即t
int n;  //同题
long long a[200010];
int main()
{
	cin>>_;
	while(_--)
	{
		cin>>n;
		memset(a,0,sizeof(a));
		long long x=0,y=0;
		long long maxx=0;
		long long a_test=0;
		for(int i=0;i<n;i++)
		{
			cin>>a[i];
			if(i%2==0) y+=a[i];//偶数累计
		}
		for(int i=1;i<n;i+=2)//奇数
		{
			x+=a[i]-a[i-1];//情况壹
			maxx=max(maxx,x);
			if(x<0) x=0;
		}
		x=0;
		for(int i=2;i<n;i+=2)//偶数
		{
			x+=a[i-1]-a[i];//情况贰
			maxx=max(maxx,x);
			if(x<0) x=0;
		}
		cout<<y+max(maxx,1ll*0)<<endl;
	}
}
```
# 温馨提示
下标从 $0$ 到 $n - 1$。  
不建议将代码中三个循环合在一起，会很乱，不容易调对。

---

## 作者：Scintilla (赞：1)

挺简单的一道 D 题。

特别喜欢这场比赛，码量也不大，也没有那种特别细节特别多的恶心题，很适合我这种蒟蒻，好评！

### 题意简述

给你一个序列，你最多能把它的一个子**串**翻转一次，求操作后序列偶数位上的数字和的最大值。注意，**数字下标从零开始**。

### 解题思路

我觉得自己讲得不大清楚，不懂的可以结合代码理解。

考虑一次翻转会带来什么。

我们不必关心下标的具体值，而只用关心其奇偶性。简单推敲后发现，若序列长度是奇数，那么相当于什么也没有发生；反之，就是把该序列内数字下标的奇偶性全都反过来了。

那好啊，问题就被我们转化成了求序列的长度为偶数的子串中奇数下标上的数减偶数下标上的数的最大值。记这个序列为 $\{a_n\}$，及 $sub_i = a_i - a_{i - 1}, sum = \sum\limits_{0 \leq i < n, 2|i}a_i$。我分了两种情况讨论，分类的标准是字串左端点的下标是奇数还是偶数。

若为偶数，问题就转化成了求序列 $\{sub_1, sub_3, \dots\}$ 的和最大的子串。这就简单了，贪心即可。用 $now_i$ 来记录当前值，$nmax$ 记录最大子串和，遍历序列，每次
$$now_i = max\{now_{i - 1} + a_i, 0\}, nmax = max\{nmax, now_i\}$$
即可（想想为什么）。$now_i$ 可以直接用一个变量代替；因为可以不翻转，$nmax$ 的初值要赋 $0$。

若为奇数，还是一样的，只不过序列变成了 $\{-sub_2, -sub_4, \dots\}$，同样更新 $nmax$。

最后，输出 $sum + nmax$ 即可。然后我们就愉快地解决了这个问题，时间复杂度 $O(n)$，可以轻松通过。

放上丑陋的代码：
```cpp
#include <bits/stdc++.h>

using namespace std;

#define il inline
#define re register
#define Rep(i, s, e) for (re int i = s; i <= e; ++i)
#define Dep(i, s, e) for (re int i = s; i >= e; --i)
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)

typedef long long ll;

const int N = 200010;

il int read() {
    int x = 0; bool f = true; char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = false; c = getchar();}
    while (isdigit(c)) x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? x : -x;
}

int tc;

int n, a[N], sub[N];

int main() {
    
    tc = read();
    
    while (tc--) {
        n = read();
        ll sum = 0, nmax = 0, now = 0, noww = 0;
        Rep(i, 0, n - 1) {
            a[i] = read();
            if (!(i & 1)) {
            	sum += a[i];
            	if (i) {
            		noww = max(0ll, noww + a[i - 1] - a[i]);
                	nmax = max(nmax, noww);
				}
			}
            else {
                now = max(0ll, now + a[i] - a[i - 1]);
                nmax = max(nmax, now);
            }
        }
        printf("%lld\n", sum + nmax);
    }
    
    return 0;
}
```


---

## 作者：mraymes (赞：1)

本文将同步到 [Hexo 博客](https://mraymes.github.io/).

本题给定了一个数组 $a_0, a_1, \cdots, a_{n - 1}$, 求翻转一段连续区间之后, 下标为偶数的所有数之和最大.

可以转换一下思路: 选定一段区间之后, 那段区间内取的是下标为奇数的数之和而不是下标为偶数的数之和. 这样就可以用 DP 来解决.

需要注意的是, 如果区间的长度为奇数, 那么头与尾的数必须要舍弃一个.

举个例子 (以下红色标注的是计入最终答案的数, 框是选择的区间):

$$\color{red}a_0, \color{none}\boxed{\color{none}{a_1}, \color{red}a_2, \color{none}a_3, \color{red}a_4, \color{none}a_5}, \color{red}a_6, \color{none}a_7$$

这是错误的:

$$\color{red}a_0, \color{none}\boxed{\color{red}{a_1}, \color{none}a_2, \color{red}a_3, \color{none}a_4, \color{red}a_5}, \color{red}a_6, \color{none}a_7$$

正确:

这种取法相当于区间 $[1, 4]$ 翻转
$$\color{red}a_0, \color{none}\boxed{\color{red}{a_1}, \color{none}a_2, \color{red}a_3, \color{none}a_4, \color{none}a_5}, \color{red}a_6, \color{none}a_7$$

这种取法相当于区间 $[2, 5]$ 翻转
$$\color{red}a_0, \color{none}\boxed{\color{none}{a_1}, \color{none}a_2, \color{red}a_3, \color{none}a_4, \color{red}a_5}, \color{red}a_6, \color{none}a_7$$

还有一种避免像上面的错误情况出现, 那就是避免选奇数长度的区间, 但由于这样太麻烦, 所以可以分两种情况 DP: 一种是头取的情况, 另一种是尾取的情况. 具体见代码.

```cpp
// 注意, 代码中的下标一律从 1 开始
// 所以奇偶性与题面中一律相反
// 下面注释中的 "下标" 一律指题面中的下标
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int cnt_test;
int n;
ll a[200001];
ll f[200001][4]; // DP
// 第二维:
// 0: 所选区间左侧的数 (下标为偶数)
// 1: 所选区间内的第一个数取, 最后一个数不取 (下标为奇数)
// 2: 所选区间内的第一个数不取, 最后一个数取 (下标为奇数)
// 3: 所选区间右侧的数 (下标为偶数)
ll ans;

template <typename T>
inline T read() {
    T x = 0;
    T multiplier = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            multiplier = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch & 15);
        ch = getchar();
    }
    return x * multiplier;
}

int main() {
    cnt_test = read<int>();
    while (cnt_test--) {
        n = read<int>();
        for (int i = 1; i <= n; i++) {
            a[i] = read<ll>();
            f[i][0] = f[i][1] = f[i][2] = f[i][3] = 0; // 初始化
        }
        for (int i = 1; i <= n; i++) {
            if (!(i & 1)) { // 当前下标为奇数
                f[i][1] = f[i - 1][0] + a[i];
                if (i == 2) {
                    f[i][2] = a[i];
                }
                if (i >= 4) {
                    f[i][2] = f[i - 3][0] + a[i];
                    f[i][1] = max(f[i][1], f[i - 2][1] + a[i]);
                    f[i][2] = max(f[i][2], f[i - 2][2] + a[i]);
                }
            } else { // 当前下标为偶数
                if (i == 1) { // 特判, 以防超界
                    f[i][0] = a[i];
                } else if (i >= 3) { // 直接转移
                    f[i][0] = f[i - 2][0] + a[i];
                }
                if (i >= 3) {
                    // 所选区间内的最后一个数取, 因此从上一个数转移
                    f[i][3] = f[i - 1][2] + a[i];
                }
                if (i >= 5) {
                    f[i][3] = max(
                        { f[i][3], f[i - 3][1] + a[i], f[i - 2][3] + a[i] });
                    // max 内的值分别表示:
                    // f[i][3] 原来的值
                    // 所选区间内最后一个数不取, 因此从当前位置之前的第三个数转移
                    // 直接从上一个下标为偶数的数转移
                }
            }
        }

        ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = max({ ans, f[i][0], f[i][1], f[i][2], f[i][3] });
        }
        printf("%lld\n", ans);
    }
    return 0;
}

```


---

## 作者：Starry_Ocean (赞：0)

### 思路与想法

刚看到这个题目，一眼想到使用动态规划。于是，记 $dp(i)$ 表示修改前 $i$ 项所能获得的最大答案。显然 $dp(0) = a_0$，答案是 $dp(n-1)$。显然，该方案是一种错误的贪心方案，因为状态数不够，无法记录哪个数被调整过哪个数没有被调整过。于是乎，我们重新定义状态数组。记 $dp(i,0/1)$ 表示对于前 $i$ 项而言，没有修改的情况为 $dp(i,0)$，反之为 $dp(i,1)$。显然，这个做法也是错误的，因为状态转移方程无法表示。因此，我们考虑两数之间差的关系。这里先给出一些非常显然的结论：如果修改的子序列的长度是奇数，那么数列奇数项之和与偶数项之和仍然相等。如果修改的子序列的长度是偶数，奇数项的总和的增加量为该序列内每一个偶数项减去奇数项之差的和。对于序列长度奇偶性，分组方式，可以分为如下四种：

- 对于偶数项序列，可以从第 0 项开始，分为 $\frac {n}{2}$ 个字段。
  
- 对于偶数项序列，可以从第 1 项开始，分为 $\frac {n}{2}-1$ 个字段。
 
- 对于奇数项序列，可以从第 0 项开始，分为 $\frac {n-1}{2}$ 个字段。

- 对于奇数项序列，可以从第 1 项开始，分为 $\frac {n-1}{2}$ 个字段。

对于相邻的两项，做差，记为序列 $b$，这个序列表示的是奇偶项调换后偶数项和的增加值。最后为了满足题目的条件，我们需要使偶数项之和最大。即：求 $b$ 序列中一个最大的连续子段之和。即线性动态规划。

### 时间复杂度分析

在该做法中，动态规划部分的时间复杂度是 $O(n)$，总的时间复杂度是 $O(nt)$。因为 $n \le 2 \times 10^5$ 且 $\sum n \le 2 \times 10^5$，所以该做法能够通过本题。

### 注意事项

- 要开 `long long`。

- 注意求最大的连续子段之和数组初始化。

- 不要对序列 $b$ 进行 `memset`，亲测会被卡。

- 下标从 1 开始，求奇数项，以防数组越界。


### 核心代码

```cpp
        cin>>n;
		for(ll i = 1;i <= n;++i) cin>>a[i];
		memset(f,0,sizeof f);
		memset(g,0,sizeof g);
		cnt1=cnt2=0;
		if(n%2==1){
			for(ll i = 1;i <= n-2;i+=2){
				cnt1++;
				b1[cnt1]=a[i+1]-a[i];
			}
			for(ll i = 2;i <= n-1;i+=2){
				cnt2++;
				b2[cnt2]=a[i]-a[i+1];
			}
		}
		else {
			for(ll i = 1;i <= n-1;i+=2){
				cnt1++;
				b1[cnt1]=a[i+1]-a[i];
			}
			for(ll i = 2;i <= n-2;i+=2){
				cnt2++;
				b2[cnt2]=a[i]-a[i+1];
			}
		}
		ll ans1=-1e18;
		for(ll i = 1;i <= cnt1;++i){
			f[i]=max(f[i-1]+b1[i],b1[i]);
			ans1=max(ans1,f[i]);
		}
		ll ans2=-1e18;
		for(ll i = 1;i <= cnt2;++i){
			g[i]=max(g[i-1]+b2[i],b2[i]);
			ans2=max(ans2,g[i]);
		}
		ll ans=0;
		for(ll i = 1;i <= n;++i) if(i%2==1) ans+=a[i];
		if(max(ans1,ans2)<0) cout << ans << "\n";
		else cout << ans+max(ans1,ans2) << "\n";
```

---

## 作者：WydnksqhbD (赞：0)

# [CF1373D Maximum Sum on Even Positions](https://www.luogu.com.cn/problem/CF1373D) 题解
**前置说明：本题中的下标从 $1$ 开始。**
## 思路
本题思路有点难想到，如下：

设翻转区间 $[l,r]$。首先来探究实例，就拿样例来说吧：

$$1,7,3,4,7,6,2,9$$

此时和为 $1+3+7+2=13$。

如果 $l=3,r=7$，会发现翻转之后，和并没有变化：

$$\color{red}{1,7,}\color{lime}{2,6,7,4,3,}\color{red}{9}$$

（此时和为 $1+2+7+3=13$，仍然没有变化）

这是怎么回事呢？

经过测试，你会发现只要 $l$ 与 $r$ 同奇偶，和就不会有任何变化。并且在测试的时候，你会发现一个很重要的点：**翻转区间时，其实只是翻转了 $[l,r]$ 之间的奇数位和偶数位。**

于是，我们就可以使用前缀和记录**奇数位与偶数位的差**，再使用类似于**最大子段和**的方式得到答案。

但是，你以为这道题就完了？

如果**什么都不翻转**反而是最大的呢？

所以我们还得加上判断的语句。

思路大概就是这样了，实在没理解的看代码吧：

（本方法时间复杂度 $O(t\times n)$）

```cpp
//万能头也能用。
#include<cstdio>
#include<iostream>
using namespace std;
typedef long long ll;
const int N=2e5+5;
const ll M=1e15;
int n;
ll a[N],s[N];
ll max(ll n1,ll n2)
{
	if(n1>=n2)
	{
		return n1;
	}
	else
	{
		return n2;
	}
}
ll min(ll n1,ll n2)
{
	if(n1<=n2)
	{
		return n1;
	}
	else
	{
		return n2;
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--) //每次先判断再-1，刚好t次。使用此法写代码还是挺方便的。
	{
		scanf("%d",&n);
		ll ans=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			if(i%2)
			{
				s[i]=s[i-1]-a[i]; //前缀和。
				ans=ans+a[i]; //咳咳咳咳咳。。。
			}
			else
			{
				s[i]=s[i-1]+a[i];
			}
		}
		ll pre=-M,min1=M,min2=M; //M是什么？看上面的常量↑。
		for(int i=0;i<=n;i++)
		{
			if(i%2)
			{
				min1=min(min1,s[i]);
				pre=max(pre,s[i]-min1);
			}
			else
			{
				min2=min(min2,s[i]);
				pre=max(pre,s[i]-min2);
			}
		}
		printf("%lld\n",ans+pre);
	}
	return 0;
}
```

最后：[P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)

[Accepted 记录](https://www.luogu.com.cn/record/141958346)

---


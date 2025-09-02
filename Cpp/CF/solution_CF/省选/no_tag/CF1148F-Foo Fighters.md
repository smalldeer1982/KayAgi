# Foo Fighters

## 题目描述

给定 $n$ 个物品。每个物品有两个整数属性：$val_i$（其价格）和 $mask_i$。保证所有价格的总和初始时不为零。

你需要选择一个正整数 $s$。所有物品随后会被如下方式修改：

- 将 $mask_i$ 和 $s$ 都看作二进制表示，
- 计算 $s$ 与 $mask_i$ 的按位与（即 $s\,\&\,mask_i$），
- 如果 $s\,\&\,mask_i$ 的二进制表示中有奇数个 $1$，则将 $val_i$ 替换为 $-val_i$；否则 $val_i$ 不变。

你需要找到一个整数 $s$，使得经过上述修改后，所有价格的总和改变符号（如果原本为负，则变为正；如果原本为正，则变为负，不能变为零）。总和的绝对值可以任意。

## 说明/提示

在第一个样例中，除了掩码为 $151$ 的物品外，所有物品的价格都会改变符号。

因此它们的总和会改变符号：初始为 $24$，修改后为 $-28$。

在第二个样例中，唯一的物品会改变价格，因此总和会改变符号。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
17 206
-6 117
-2 151
9 93
6 117
```

### 输出

```
64
```

## 样例 #2

### 输入

```
1
1 1
```

### 输出

```
1
```

# 题解

## 作者：OuOu2021 (赞：11)

这是一道不错的贪心题，解决问题的关键在于如何找到贪心策略，满足无后效性

------------

### 题意解释：

你有 $n$ 个物品，每个物品有两个权值 $val_i$ 和 $mask_i$ 。

你可以选择一个数 $s$ ，然后修改所有数的 $val$ ，如果 $s&mask_i$有奇数个 $1$ 就把 $val_i$ 变成 $−val_i$ 。

输出一个 $s$ ，使得权值和符号变反，绝对值任意（非$0$）。
100%数据$2<=n<=3e5,1<=m<=3e5$


------------

### 看下样例

$5$

$17\;206\qquad(11001110)_2$

$-6\;117\qquad(01110101)_2$

$-2\;151\qquad(10010111)_2$

$9 \;\;\;93 \qquad(01011101)_2$

$6\;117\qquad(01110101)_2$

解释：$64(01000000)_2$可以。因为这样会把 $ 17,-6,9,6 $ 取反了，结果是$-28$，原来是$24$，符号相反


------------

### 思考过程

- 这是一道构造题，用按位贪心的方法解决

- 首先发现那个奇数个1的奇特判断可以变成：每确定一个1就变一次，这样就减少了不少麻烦，复杂度也减小一个$log$。

- 按$mask$的最高位来做，把物品按照$mask$最高位的位数来分类。从0到61考虑每一类，这样保证了无后效性：把高位s设为1或0，不会对以前造成任何影响，相当于低位已经被确定了

- 这样，我们试图使每一类都与$sum$异号，这样总和就异号了。

- 具体来说就是看这一类的总和，如果与$sum$同号就把s的这一位变成1，再把所有这一位为1的数都取反

- 复杂度O(63N)

------------

### Talk is cheap,give me the code!
```cpp
#include <bits/stdc++.h>
#define ll long long
#define ri register int
using namespace std;
const int maxn=3e5+10;
struct objects{ll val, mask,id;}obj[maxn];
ll n,s,sum;
inline ll read(){
	ll f=1,sum=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))sum=sum*10+(ch^48),ch=getchar();
	return f*sum;
}
int main(){
	n=read();
	for(int i=1;i<=n;i=-~i)obj[i].val=read(),obj[i].mask=read();
	for(int i=1;i<=n;i=-~i){
		for(int j=0;j<=62;j=-~j)if((obj[i].mask>>j)&1)obj[i].id=j;
		sum+=obj[i].val;
	}
	if(sum<0)for(int i=1;i<=n;i=-~i)obj[i].val*=-1;//默认从正变为负
	for(int i=0;i<=62;i=-~i){
		ll tmp=0;
		for(int j=1;j<=n;j=-~j)if(obj[j].id==i)tmp+=obj[j].val;
		if(tmp>0){
			s|=(1ll<<i);
			for(int j=1;j<=n;j=-~j)if((obj[j].mask>>i)&1)obj[j].val*=-1;
		}
	}
	printf("%lld\n",s);
	return 0;
}
```

------------

### NY OIer出品

---

## 作者：AuCloud (赞：6)

挺**神奇**的一道黑题

# 题意

给你很多数对a,b，要求找出一个数s，满足在 $ s $&$ b_i $有奇数个1时$a_i$取负，使得最终$a_i$的和与原先$a_i$的和的符号相反

# 思路

首先看到位运算就应该想到按位是独立的

所以按位枚举应该是没跑了/

接下来就要考虑怎么枚举能让当前决定不存在对后面的影响

这里是**与**操作，一个比较优秀的性质就是一个数与上另一个数时只有**低于它最高位的位数才会被影响**

像$(00000110)_2$，他只会受到$2^0,2^1,2^2$这三位的影响，其他位根本没他啥事

所以从0~62枚举**最高位**就可以保证后面所作的更改不会影响到前面的决策

还有一个比较重要的就是`有奇数个1`看起来十分~~丑陋~~，要想个办法把它变得正常

由于是取相反数，所以可以想到$(-1)^n$的形式，即每次决定变化时把当前位为1的对应的a值取负就行

每次枚举到一个位的时候将所有最高位为这个数的数字加起来，若这个和与原和符号相同，说明将这位 置成1是有意义的，否则是没有意义的

然后将**所有**这个位为1的值取相反数就行

这样就保证了当前决策只会对后面的状态造成影响。

为了偷懒，如果原先的和为负数，则把他们全都取反，变成正数，就可以少一个特判了

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[300001], m[300001], hi[300001];
signed main()
{
	int n;
	cin >> n;
	int ans = 0, sum = 0;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i] >> m[i];
		int x = m[i];
		while(x)
		{
			x >>= 1;
			hi[i]++;
		}
		sum += a[i];
	}
	if(sum < 0)
	{
		for(int i = 1; i <= n; i++) a[i] *= -1;
	}
	for(int i = 0; i <= 62; i++)
	{
		int qwq = 0;
		for(int j = 1; j <= n; j++)
		{
			if(m[j] & (1ll << i) && hi[j] - 1 == i) qwq += a[j];//其实第一条判断没有用，是我之前的错误做法留下来的
		}
		if(qwq > 0)
		{
			for(int j = 1; j <= n; j++)
			{
				if(m[j] & (1ll << i)) a[j] *= -1;
			}
			ans += (1ll << i);
		}
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：rui_er (赞：4)

有点毒瘤的贪心题，当然也可能是我太菜了。

---

翻译的挺清楚的了，直接说思路：

我们考虑在读入时顺便把每个数的 $mask$ 权值的**二进制最高位**预处理出来，同时统计权值和。由于正数变负数和负数变正数本质上是一样的，为了方便考虑，如果 $val$ 权值和为负数，将所有 $val$ 取相反数。

随后考虑如何贪心：

枚举每一位，统计**二进制最高位为该位**的所有数的 $val$ 权值和。如果这个权值和小于或等于零，那么没有修改该位的必要，因为修改不会使总权值增加，反而可能减少。如果最高位为该位的权值和大于零，那么修改该位比不修改更优。在答案变量中将该位置为 $1$，并且枚举所有数修改即可。

以上为正解，复杂度 $O(n\log{x})$，$x$ 为变量范围（$2^{62}-1$）。

**坑点：贪心时必须从低位到高位枚举每一位进行更新，否则后面的更改可能导致更高位的决策被干扰，得不到正确答案！**

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 3e5+5, bit = 62;

ll n, ans;
struct Node {ll val, mask, bits;}a[N];

int main() {
	scanf("%llu", &n);
	for(ll i=1;i<=n;i++) {
		scanf("%lld%lld", &a[i].val, &a[i].mask);
		ans += a[i].val;
		for(ll _=bit;_+1;_--) if((a[i].mask >> _) & 1) {a[i].bits = _; break;}
	}
	if(ans < 0) for(ll i=1;i<=n;i++) a[i].val = -a[i].val;
	ans = 0;
	for(ll _=0;_<=bit;_++) {
		ll s = 0;
		for(ll i=1;i<=n;i++) s += (a[i].bits == _) * a[i].val;
		if(s <= 0) continue;
		ans |= (1LL << _);
		for(ll i=1;i<=n;i++) a[i].val *= ((a[i].mask >> _) & 1) ? -1 : 1;
	}
	printf("%lld\n", ans);
//	puts("----------\nDEBUG: "); for(ll i=1;i<=n;i++) printf("%lld\n", a[i].val);
	return 0;
}
```

---

## 作者：luogubot (赞：2)

给定 $n$ 个二元组 $(a_i,s_i)$，选择一个数 $S$，然后把所有 $S\operatorname{and}s_i$ 有奇数个 1 的 $a_i$ 变为相反数，使得最终 $\sum a_i$ 与初始的符号相反。保证初始元素和不为 0。

$1\leq n\leq 3\times 10^5$，$0<s_i<2^{62}$，$|a_i|\leq 10^9$。

默认初始和是正数。

考虑按照 $s_i$ 的最高位分类，依次从小到大处理 $s_i\leq 2^k$ 的子问题，保证 $s_i\leq 2^k$ 的新的 $a_i$ 之和是非正数。当 $k=0$ 时，若 $s_i\leq 2^0$ 的 $a_i$ 之和是正数，那么我们把 $S$ 的最低位设为 1，否则设为 0；当 $k>0$ 时，若 $2^{k-1}<s_i\leq 2^{k}$ 的 $a_i$ 是正数则将这一位设为 1，否则设为 0。注意此时的 $a_i$ 可能在 $S$ 更低位的决策中被修改了，需要更新。

这样，当每一组都处理完之后，由于初始元素和不为 0，那么至少有一组中初始的和不为 0，最终的元素和就一定小于 0。

时间复杂度 $O(n\log S)$，[提交记录](https://codeforces.com/contest/1148/submission/161460878)。



---

## 作者：Leap_Frog (赞：1)

### P.S.
刚开始打开了这场的 H 题，然后被题解劝退……  
然后退而求其次，打开了 G 题，发现还是不会。  
继而打开了 F 题，发现有点思路了。  
说明 xtw 还是 ![](//xn--9zr.tk/no)  

### Problem.
~~感觉描述复杂了，可以略过~~  
有 $n$ 个物品，每个物品权值为 $v_i$，标签为 $a_i$。  
$$\forall S\in\mathbb N,i\in[1,n],w_i=\left([\text{bitcount}(a_i\ \text{and}\ s)\equiv1\pmod2]\times2-1\right)\times v_i$$  
你需要选出一个 $s$，使得有下式子成立。  
$$\frac{|\sum_{i=1}^nv_i|}{\sum_{i=1}^nv_i}+\frac{|\sum_{i=1}^nw_i|}{\sum_{i=1}^nw_i}=0$$  

### Solution.
首先，如果全局和为负，我们对每一个位地权值取相反数，与原题等价。  
那么题目转化成了需要让权值和从正变负。  
首先，这边有一个 $\text{and}$ 符号，那么我们肯定需要考虑按位。  
如果我们从高向低考虑，前面某一位是会影响后面的，具有后效性，对dp/贪心不利。  
那么我们只能从低向高考虑。  
我们可以在某一个数最高位计算它的贡献。  
首先，当前的决策对后面位的影响可以在后面“反悔”。  
而与此同时，当前的决策不会影响到比它低位的值，不具有后效性。  
所以我们考虑 ~~dp~~贪心。  
在每一位，对当前这位确定的所有数，如果和正就对它们全部取反，否则不变。  
然后可以证明这样虽然不一定取到最小值，但是肯定能使和变负。  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:0;
}/*}}}*/
int n,v[300005],mb[300005];ll sm,a[300005],rs;
int main()
{
	read(n);for(int i=1;i<=n;i++) read(v[i]),read(a[i]),sm+=v[i];
	if(sm<0) for(int i=1;i<=n;i++) v[i]=-v[i];
	for(int i=1;i<=n;i++) for(ll x=a[i];x;x>>=1) mb[i]++;
	for(int i=0;i<63;i++)
	{
		ll sm=0;for(int j=1;j<=n;j++) if(mb[j]==i+1) sm+=v[j];
		if(sm>0) {rs|=1ll<<i;for(int j=1;j<=n;j++) if((a[j]>>i)&1) v[j]=-v[j];}
	}
	return printf("%lld\n",rs),0;
}
```

---

## 作者：Chenaknoip (赞：0)

这是一道构造题，考虑按位填数。

首先先求出 $\sum val_i$。如果是负数，则将 $val_i$ 符号取反，使得 $\sum val_i$ 变为正数方便操作。

设答案为 $ans$，则根据按位与运算的特性，它的二进制第 $i$ 位只会影响 $mask_i$ 的**二进制最高位的位置**大于等于 $i$ 的数。此外，若 $ans$ 的低 $i-1$ 位已经确定，则改变第 $i$ 位会将 $\sum _{ppp(mask_i)=i} val_i$ 的符号翻转，其中 $ppp(x)$ 表示 $x$ 的二进制表示中 $1$ 的个数。

所以考虑贪心，当枚举到 $ans$ 的二进制第 $i$ 位时，求出 $sum=\sum _{ppp(mask_i)=i} ((-1)^{ppp(mask_i \& ans)}val_i)$。如果它是正数，则将 $ans$ 的第 $i$ 位取 $1$，使得总和变为负数；否则将 $ans$ 的第 $i$ 位取 $0$。

提交记录：[304575940](https://codeforces.com/contest/1148/submission/304575940)

---

## 作者：Yuby (赞：0)

# CF1148F

[题面](https://www.luogu.com.cn/problem/CF1148F)

点数：2700

## 分析

异常神仙的题。

先摆出贪心策略吧。首先，如果总和小于 0，可以将所有的数取反。我们考虑每个 $mask_i$ 二进制下为 1 的最高位，记录为 $h_i$。从低到高考虑答案上的每一个二进制位。当前考虑第 $j$ 位，若 $sum=\sum\limits_{h_i=j} a_i>0$，这一位就是 1，然后我们就把所有 $mask_i\land  2^j=2^{j}$ 的数的价值取反，然后考虑下一位 。

这种思路或许可以这样理解，现在总和大于 0。我们把所有 $h_i$ 相等的算为一类。既然我们要让总和异号，不妨尝试使一类都异号，于是我们遇到一个同号的就把他变成异号。这时我们处理的答案不会对前面已经选择的类造成影响，即对于第 $j$ 位和第 $i$ 位，如果 $j>i$ 那么 $j$ 的选择不会对 $i$ 中的和造成影响，因为 $h_x=i$ 的第 $j$ 位不可能是 1，也就不会有影响。因此从低位向高位考虑没有后效性。如果所有的类都异号，那么总和必然异号。

复杂度：$O(n\log mask_i)$。

核心代码：

```cpp
const ll MAXN=3e5+7;
ll n,a[MAXN],b[MAXN],h[MAXN];
int main()
{
 	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=read();ll sum=0;
    for(ll i=1;i<=n;i++)
    {
    	a[i]=read(),b[i]=read();
    	sum+=a[i];
    	for(ll j=62;j>=0;j--)if((b[i]>>j)&1)
    	{
    		h[i]=j;break;
		}
	}
	if(sum<0)for(ll i=1;i<=n;i++)a[i]=-a[i];
	ll ans=0;
	for(ll j=0;j<=62;j++)
	{
		ll res=0;
		for(ll i=1;i<=n;i++)if(h[i]==j)res+=a[i];
		if(res>0)
		{
			ans|=(1ll<<j);
			for(ll i=1;i<=n;i++)if((b[i]>>j)&1)a[i]=-a[i];
		}
	}
	write(ans);
	return 0;
}
```



---


# Mio and Lucky Array

## 题目描述

Mio 有一个包含 $n$ 个整数的数组 $a$，以及一个包含 $m$ 个整数的数组 $b$。

Mio 可以对 $a$ 进行如下操作：

- 选择一个尚未被选择过的整数 $i$（$1 \leq i \leq n$），然后对 $a$ 执行如下修改：将 $a_i$ 加 $1$，将 $a_{i+1}$ 减 $2$，将 $a_{i+2}$ 加 $3$，依此类推。形式化地说，对于 $i \leq j \leq n$，将 $(-1)^{j-i} \cdot (j-i+1)$ 加到 $a_j$ 上。

Mio 想要将 $a$ 变换，使其包含 $b$ 作为一个子数组。你能回答她是否可以做到，并给出一组操作方案（如果可能）吗？

如果通过删除若干（可能为零或全部）开头元素和若干（可能为零或全部）结尾元素后，$b$ 能从 $a$ 得到，则称 $b$ 是 $a$ 的一个子数组。

## 说明/提示

在第一个测试用例中，序列 $a = [1,2,3,4,5]$。一种可行的方案是在 $i=1$ 处进行一次操作（$a_1$ 加 $1$，$a_2$ 减 $2$，$a_3$ 加 $3$，$a_4$ 减 $4$，$a_5$ 加 $5$）。此时 $a$ 变为 $[2,0,6,0,10]$，其中包含 $b=[2,0,6,0,10]$ 作为子数组。

在第二个测试用例中，序列 $a = [1,2,3,4,5]$。一种可行的方案是在 $i=4$ 处进行一次操作（$a_4$ 加 $1$，$a_5$ 减 $2$）。此时 $a$ 变为 $[1,2,3,5,3]$，其中包含 $b=[3,5,3]$ 作为子数组。

在第三个测试用例中，序列 $a = [-3, 2, -3, -4, 4, 0, 1, -2]$。一种可行的方案如下：

- 选择 $i=8$ 进行操作，此时 $a$ 变为 $[-3, 2, -3, -4, 4, 0, 1, -1]$。
- 选择 $i=6$ 进行操作，此时 $a$ 变为 $[-3, 2, -3, -4, 4, 1, -1, 2]$。
- 选择 $i=4$ 进行操作，此时 $a$ 变为 $[-3, 2, -3, -3, 2, 4, -5, 7]$。
- 选择 $i=3$ 进行操作，此时 $a$ 变为 $[-3, 2, -2, -5, 5, 0, 0, 1]$。
- 选择 $i=1$ 进行操作，此时 $a$ 变为 $[-2, 0, 1, -9, 10, -6, 7, -7]$。

最终 $a$ 变为 $[-2, 0, 1, -9, 10, -6, 7, -7]$，其中包含 $b=[10, -6, 7, -7]$ 作为子数组。

在第四个测试用例中，无法将 $a$ 变换为包含 $b$ 作为子数组的形式。

在第五个测试用例中，无法将 $a$ 变换为包含 $b$ 作为子数组的形式。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
5
2 0 6 0 10
5
1 2 3 4 5
3
3 5 3
8
-3 2 -3 -4 4 0 1 -2
4
10 -6 7 -7
5
1 2 3 4 5
4
1 10 1 1
5
0 0 0 0 0
2
10 12```

### 输出

```
1
1 
1
4 
5
1 3 4 6 8 
-1
-1```

# 题解

## 作者：DeaphetS (赞：18)

题目链接：[1704G - Mio and Lucky Array](https://codeforces.com/contest/1704/problem/G)

题目大意：给定数组 $a,b$，可以对 $a$ 的每个位置 $i$ 进行 $0$ 或 $1$ 次操作。每次操作可以令所有 $j\ge i$ 的 $a_j$ 加上 $(-1)^{j-i}\cdot(j-i+1)$（对应每个位置的变化量为 $1,-2,3,-4,\cdots$），问是否可以让 $a$ 存在一个**连续**子序列与 $b$ 相同。

为了方便起见，我们默认下标从 $0$ 开始。

首先要注意到，在一次操作后，$a_i+2a_{i-1}+a_{i-2}$ 的值是不变的（除了边界部分）。要问为什么能注意到，心路历程大概如下：

- 看到变化量是 $1,-2,3,-4,\cdots$ 有点烦，因为有一个 $(-1)^k$ 的影响因素在，所以在想如果把偶数位取反就可以把变化量变成 $1,2,3,\cdots $ 了。
- 如果变化量是 $1,2,3,\cdots$ 的话，那么取一个二阶差分就可以找到一个不变量。二阶差分的式子为 $d_i=(a_{i}-a_{i-1})-(a_{i-1}-a_{i-2})=a_i-2a_{i-1}+a_{i-2}$。
- 发现与其取反后二阶差分，不如直接在式子上进行更改，把对应系数取反。于是就找到了原操作的不变量 $a_i+2a_{i-1}+a_{i-2}$。

那么令 $f_i=a_i+2a_{i-1}+a_{i-2}$，观察在对 $i$ 进行一次操作后 $f$ 的变化情况。可以发现每次操作只是把 $f_i$ 的值加上了 $1$，其余位置的值不做更改。

在这里就需要思考一下在操作过后如何判断 $a$ 的一个起始位置为 $st$，长度为 $m$ 的子序列是否与 $b$ 相同了。类似地，令 $g_i=b_i+2b_{i-1}+b_{i-2}$，那么两个序列相等当且仅当下式成立：
$$
\begin{cases}
f_{st+i}=g_i &  i\ge 2 \\ 
a_{st+i}=b_i &  i= 0,1
\end{cases}
$$
由于 $f_i$ 的值最多加一，所以第一个式子有机会成立当且仅当 $g_i = f_{st+i}$ 或 $g_i = f_{st+i}+1$。考虑利用 `bitset` 判断所有 $st$ 是否可以合法。

为了判断一个起点是否合法，暴力的话可以有如下代码：

```cpp
for(int st=0;st<=n-m;st++)
    for(int i=2;i<m;i++)
        ok[st]&=(f[st+i]==g[i])|(f[st+i]==g[i]-1);
```

既然要利用 `bitset`，就需要改变枚举的先后顺序，以便一次性对所有的 $st$ 进行赋值操作：

```cpp
for(int i=2;i<m;i++)
    for(int st=0;st<=n-m;st++)
        ok[st]&=(f[st+i]==g[i])|(f[st+i]==g[i]-1);
```

于是对数组 $f$ 开 `vector`，对每个数值记录数组内有哪些位置等于指定值，就可以快速进行处理：

```cpp
for(int i=2;i<m;i++){
    bitset<N>t;
    for(auto j:d[g[i]])t[j]=1;
    for(auto j:d[g[i]-1])t[j]=1;
    ok&=t>>i;
}
```

当然为了避免超时，还需要对每个相同的 $g_i$ 分批进行处理，排序后双指针即可。

这样我们就能在 $O(\frac{n^2}{W})$ 的复杂度内完成对应判断，接下去就需要考虑如何判断头两位的值是否可以满足条件。

对每个符合条件的 $st$，我们设 $d_0=b_0-a_{st},d_1=b_1-a_{st+1}$。可以发现，每次若有操作令 $a_{st}$ 加上 $k>0$，那么对应的 $a_{st+1}$ 就会减去 $k+1$，减 $k$ 时同理。也就是说，每当 $a_{st}$ 的值增加一次，对应的 $d_0+d_1$ 就会减一，反之亦然。于是我们可以通过 $d_0+d_1$ 的值来判断 $a_{st}$ 的值增加与减少的次数之差，特别地对于只有 $a_{st+1}$ 加一的情况，我们把它看成 $a_{st}$ 的值减少了 $0$。

这样一来，我们就需要判断在加法操作与减法操作的差为 $k$ 的情况下，是否存在一种操作方式使得 $a_{st}$ 能够到达指定的值，这其中可选的操作为 $-0,+1,-2,+3,\cdots ,+(-1)^{st}\cdot (st+1)$。

注意到，由于所有的减法操作减去的都是偶数，所以 $d_0$ 的奇偶性就决定了加法或减法操作次数的奇偶性（二者操作次数的差为定值）。另外，当确定了加减法的次数 $x,y$ 后，可以 $O(1)$ 贪心计算得出对应操作次数能够得到的最大值以及最小值 $l,r$，且可以证明，在 $ [l,r]$ 之间与 $l,r$ 奇偶性相同的值都可以取到。我们来看下确定 $x,y$ 后对应的最大值和最小值是什么。

设最大的加法操作为 $+M$，那么贪心取最大的 $x$ 个加法以及绝对值最小的 $y$ 个减法，对应的最大值为：

 $\sum_{i=0}^{x-1}(M-2i)-\sum_{i=0}^{y-1}2i=Mx-x(x-1)-y(y-1)$

同样设绝对值最大的减法操作为 $-M'$，那么贪心取最小的 $x$ 个加法以及绝对值最大的 $y$ 个减法，对应的最小值为：

 $\sum_{i=0}^{x-1}(2i+1)-\sum_{i=0}^{y-1}(M'-2i)=x^2-M'y+y(y-1)$

可以发现在上述式子中，$y=x+k$，而 $M,M'$ 是由 $st$ 确定的定值。于是对于每个 $st$，最大值和最小值都是与 $x$ 有关的二次函数，计算出系数后对应的极值都可以使用初中数学知识解出来（开心的话也可以三分）。这样我们就能够通过 $k$ 的取值以及 $d_0$ 的奇偶性确定 $x$ 的取值范围，从而得知操作后的值的范围，完成判断。

关于构造的部分，直接暴力找到一个满足条件的 $x$ 然后贪心即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200010
#define LL long long
int T,n,m,a[N];
LL b[N],f[N];
pair<LL,int>g[N];
bitset<N>ok,t;
map<LL,vector<int>>mp;
LL F(LL A,LL B,LL C,LL x){return A*x*x+B*x+C;}
bool check(int st)
{
	LL d0=b[0]-a[st],d1=b[1]-a[st+1];
	LL k=d0+d1,M=st&1?st:(st+1),M_=st&1?(st+1):st;
	LL nx=st/2+1,ny=(st+3)/2;
	LL l=max(0ll,-k),r=min(nx,ny-k);
	LL o=d0&1;

	if(l%2!=o)l++;
	if(r%2!=o)r--;
	if(l>r)return false;
	
	LL A=-2,B=M-2ll*k+2,C=k-k*k;
	LL x0=-B/(2ll*A);
	LL mn=1e18,mx=-mn;
	for(LL i=x0-5;i<=x0+5;i++)if(i%2==o && l<=i && i<=r)mx=max(mx,F(A,B,C,i));
	mx=max(mx,F(A,B,C,l));
	mx=max(mx,F(A,B,C,r));
	
	A=2,B=2ll*k-M_-1,C=k*k-(M_+1)*k;
	x0=-B/(2ll*A);
	for(LL i=x0-5;i<=x0+5;i++)if(i%2==o && l<=i && i<=r)mn=min(mn,F(A,B,C,i));
	mn=min(mn,F(A,B,C,l));
	mn=min(mn,F(A,B,C,r));
	
	if(d0>mx || d0<mn)return false;
	
	LL x=-1;
	for(LL i=l;i<=r;i++)if(i%2==o){
		mn=F(A,B,C,i);
		mx=F(-2,M-2ll*k+2,k-k*k,i);
		if(mn<=d0 && d0<=mx){x=i;break;}
	}
	
	set<int>ans;
	LL s=0,y=x+k;
	for(LL i=0;i<x;i++)s+=2ll*i+1,ans.insert(st-2ll*i);
	for(LL i=0;i<y;i++)s-=2ll*i,ans.insert(st-2ll*i+1);
	for(LL i=x-1;i>=0 && s<d0;i--){
		s-=2ll*i+1;
		ans.erase(st-2ll*i);
		while(s+M>d0)M-=2;
		s+=M;
		ans.insert(st-M+1);
		M-=2;
	}
	
	for(LL i=y-1;i>=0 && s>d0;i--){
		s+=2ll*i;
		ans.erase(st-2ll*i+1);
		while(s-M_<d0)M_-=2;
		s-=M_;
		ans.insert(st-M_+1);
		M_-=2;
	}
	
	for(LL i=2;i<m;i++)if(f[st+i]==g[i].first-1)ans.insert(st+i);
	printf("%d\n",(int)ans.size());
	for(auto i:ans)printf("%d ",i+1);
	printf("\n");
	return true;
}
void init()
{
	mp.clear();
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",&a[i]),ok[i]=1;
	scanf("%d",&m);
	for(int i=0;i<m;i++)scanf("%lld",&b[i]);
	for(int i=2;i<n;i++)mp[f[i]=a[i]+2*a[i-1]+a[i-2]].push_back(i);
	for(int i=2;i<m;i++)g[i]=make_pair(b[i]+2ll*b[i-1]+b[i-2],i);
	sort(g+2,g+m);
	for(int i=2;i<m;){
		t.reset();
		for(auto j:mp[g[i].first])t[j]=1;
		for(auto j:mp[g[i].first-1])t[j]=1;
		int j=i;
		while(j<m && g[j].first==g[i].first)ok&=t>>g[j].second,j++;
		i=j;
	}
	for(int i=2;i<m;i++)g[i]=make_pair(b[i]+2ll*b[i-1]+b[i-2],i);
	for(int i=0;i<=n-m;i++)if(ok[i])
		if(check(i))return;
	printf("-1\n");
}
int main()
{
	scanf("%d",&T);
	while(T--)init();
}
```

求二次函数极值的部分为了省脑子直接在实际极值点的左右选 $10$ 个位置暴力比较判断了，实际上是可以通过计算得出对应位置的。

另外，初步确定满足第一个条件的 $st$ 也可以通过多项式乘法来解决，但由于本弱不会所以才用的 `bitset`。

---

## 作者：周子衡 (赞：2)

这个形如 $+1,-2,+3,...$ 的操作比较复杂，我们考虑简化它。考虑下面这个变换：

- 对序列 $x=(x_1,...,x_m)$，定义 $\operatorname{M}x=(x'_1,...,x'_m)$ 为对 $x$ 进行一次 $\operatorname{M}$ 操作的结果，其中：
- - $x'_1=x_1,x'_2=x_2$。
  - $x'_i=x_{i-2}+2x_{i-1}+x_i(3\leq i\leq n)$。
  
设计这个变换的缘由是：如果我们对某个 $i\geq 3$ 执行了题目中所给的操作，那么对 $\operatorname{M}x$ 的影响只是给 $(\operatorname{M}x)_i$ 加了 $1$。读者可以自行验证。另外显然可知：序列 $a,b$ 相等当且仅当 $\operatorname{M}a,\operatorname{M}b$ 相等。

考虑去判定能否将原序列 $a$ 的某个区间 $[l,r]$ 变为 $b$（其中$r-l+1=m$）。考虑在原序列每种操作对 $\operatorname{M} a_{l...r}=(t_1,...,t_m)$ 的影响。下面用 $i$ 表示操作位置。记 $\operatorname{M}(b_1,...,b_m)=(s_1,...,s_m)$。

- $i > r$：无影响。
- $l+2\leq i\leq r$：将 $t_{i-l+1}$ 加 $1$。
- $i\leq l+1$：$t_1$ 加上 $(-1)^{l-i}\times(l+1-i)$，$t_2$ 加上 $(-1)^{l+1-i}\times (l+2-i)$。

注意到对 $i\geq 3$，我们只能通过操作 $i+l-1$ 来影响 $t_i$。这要求对每个 $i\geq 3$，$t_i=s_i$ 或 $t_i+1=s_i$。同时，在满足了这些条件之后，我们便可以不管 $t_3\sim t_m$ 了。我们着重来讨论 $t_1,t_2$。

考虑我们在 $[1,l+1]$ 内选了哪些位置。方便起见，对每次在位置 $i$ 的操作，设 $x=l+2-i$。这么做的好处是，能大大简化我们的计算和表述。现在我们考虑来选 $x$ 而不是选 $i$。$x$ 的范围也是 $[1,l+1]$，且选一个 $x$ 意味着：

- $x$ 是奇数：$t_2$ 加 $x$，$t_1$ 减 $(x-1)$。
- $x$ 是偶数：$t_2$ 减 $x$，$t_1$ 加 $(x-1)$。

则可知原问题等价于：在 $[1,l+1]$ 的全体奇数中选一个集合 $O$，全体偶数中选一个集合 $E$，使得 $|O|-|E|$ 是一个给定值，且 $O$ 的元素和减去 $E$ 的元素和是另一个给定值。

考虑这样一个问题：假如已经确定 $|O|=a,|E|=b$，构造一组 $(O,E)$ 使得 $O$ 的元素和减 $E$ 的元素和为某个给定值。注意到我们可以选择 $[1,l+1]$ 中的最大的 $a$ 个奇数和最小的 $b$ 个偶数，来得到一个最大的差；也可以反过来，得到一个最小的差。则：全部在这个最小差和最大差之间的、且和最小差同奇偶性的整数全都能表示出来。（这是因为我们可以每次挪动 $E$ 或 $O$ 中的一个元素，让其增大 $2$ / 减小 $2$。）

回到原问题。不妨设 $|O|=a$，可以解出 $a$ 的范围，判断范围里是否有奇偶性符合的即可。

------------------

最后我们来看看怎么快速处理全部区间。$t_1,t_2$ 单次的计算是 $O(\log n)$（或 $O(1)$）的，无需担心。我们只需要看看怎么快速处理 $t_3\sim t_m$ 的匹配问题。注意到对于两个整数序列 $a_1,...,a_n$ 和 $b_1,...,b_n$，以下两个条件等价：

- 对每个 $i$，$b_i=a_i$ 或 $b_i=a_i+1$。
- $\sum_{i=1}^n(b_i-a_i)(b_i-a_i-1)=0$。

将下面的式子拆开，FFT 即可。总时间复杂度 $O(n\log n)$。

**后记**

怎么感觉这题是一点一点拼出来的……

---

## 作者：极寒神冰 (赞：0)

令 $A_i=a_i+2a_{i-1}+a_{i-2},B_i=b_i-2b_{i-1}+b_{i-2}$，然后可以发现对于任意位置 $i$ 进行操作，除了 $A_{i}$ 将会变成 $A_i+1$，其他位置的数值均不变。因此对 $a$ 的操作，对 $A$ 即单点操作。

可以发现，以下条件等同于 $b[1,m]$ 可以与 $a[k+1,k+m]$ 匹配。

$$
\begin{cases}
b_1=a_{k+1}\\
b_1+b_2=a_{k+1}+a_{k+2}\\
B_i=A_{k+i}(i\ge 3)
\end{cases}
$$

对于 $i\le k+2$，对于 $i$ 位置的操作有 $a_{k+1}+a_{k+2}\leftarrow a_{k+1}+a_{k+2}+(-1)^{k-i}$。因此第二个条件限制了前 $k+2$ 位置间奇数位置和偶数位置之间操作次数差异。当对 $i$ 进行操作时，$a_{k+1}\leftarrow a_{k+1}+(k-i+2)\times (-1)^{k-i}$。

于是问题就转化成了使用 $-0,+1,-2,\cdots,(-1)^nn$ 让减法操作次数（使 $a_{k+1}$ 减小的操作）减去加法操作次数为 $a$，并且最后的 $a_{k+1}$ 应该为 $b$。

然后可以观察在某个位置进行一次操作后，$i$ 及 $i+1$ 位置上的数字变化（设其分别为 $x,y$）。

$$
\begin{vmatrix} 
x &  0 &+1&-2&+3&-4\\ 
x+y & +1&-1&+1&-1&+1
\end{vmatrix}
$$

为了方便可以先把所有减法操作做了，之后再撤销（重新添加，即这样均变成加法操作）。这样就得到 $a_{i}+a_{i+1}$ 等于什么，然后就得到了 $x+y,x$ 等于多少，然后前两个条件就可以转化成：$a\leftarrow a+\lfloor\frac{k+1}{2}\rfloor+1,b\leftarrow b+\sum\limits_{i=0}^{\lfloor\frac{k+1}{2}\rfloor} 2i$   其中 $a$ 表示需要选择 $a$ 个（即 $x+y$），$b$ 表示选择的和是 $b$（即 $x$）。

所有满足 $\sum\limits_{i=0}^{a-1} i\le b\le \sum\limits_{i=k+1-a}^{k+1}$ 的 $b$ 都是合法且容易构造出来的。

然后考虑第三个条件，构造函数 $f(k)=\sum\limits_{i=3}^m (B_i-A_{i+k})(B_i-A_{i+k}-1)$。显然 $B_i=A_{i+k}$ 或 $B_i=A_{i+k}+1$ 时上式为 $0$。而 $B_i$ 是否等于 $A_{i+k}$ 代表着我们是否要对 $i+k$ 位置进行操作，即 $B_i=A_{i+k}$ 时不需要操作，$B_i=A_{i+k}+1$ 时进行一次操作， 否则上式一定 $>0$。并且可以发现 $b[1,m]$ 可以与 $a[k+1,k+m]$ 匹配上时一定有 $f(k)=0$。考虑如何计算 $f$。

$$
f(k)=\sum_{i=3}^m A_{i+k}^2+B_i^2-2A_{i+k}B_i-B_i+A_i
$$

对于 $A_{i+k}B_i$，这是一个卷积形式，可以转化为多项式乘法，使用 FFT 求解，而其他项显然是可以简单求出的。

考虑到 $f(k)$ 的值很大，如果使用 NTT，可能需要测试几个不同的素数来避免 hack，这部分时间复杂为 $\mathcal O(n\log n)$。

并且可以通过 bitset 来找到满足第三个条件的 $k$，时间复杂度为 $\mathcal O(\frac{n^2}{\omega})$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define qwq printf("qwq\n");
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
using namespace std;
const int mod=998244353;
const int _G=646;
const int invG=208611436;
const int G_pw=1<<20;
inline int fix(int a,int p=mod)
{
	a=(a%p+p)%p;
	return a;
}
inline int add(int a,int b,int p=mod)
{
	a+=b;
	if(a>=p) a-=p;
	return a; 
}
inline int dec(int a,int b,int p=mod)
{
	a-=b;
	if(a<0) a+=p;
	return a;
}
inline int mul(int a,int b,int p=mod)
{
	ll c=1ll*a*b%mod;
	return fix(c,p);
}
inline int fpow(int a,int b=mod-2,int p=mod)
{
	int ret=1;
	while(b)
	{
		if(b&1) ret=mul(ret,a,p);
		a=mul(a,a,p);
		b>>=1;
	}
	return ret;
}
inline ll calc(ll l,ll r,ll k)
{
	if(r<l) return 0;
	ll t=(r-l)/k+1;
	ll tmp=1ll*l*t+t*(t-1)/2*k;
	return tmp;
}
inline ll get_mn(ll a,ll b)
{
	b=(a+1)/2-b;
	return calc(1,a,2)-calc(a-b+1,a,1);
}
inline ll get_mx(ll a,ll b)
{
	b=(a+1)/2-b;
	return calc(1,a,2)-calc(1,b,1);
}
struct fu
{
	void NTT(vector<ll>&a,bool rev)
	{
		int n=(int)a.size();
		for(int i=1,j=0;i<n;i++)
		{
			int bit=n>>1;
			for(;j>=bit;bit>>=1) j-=bit;
			j+=bit;
			if(i<j) swap(a[i],a[j]);
		}
		for(int len=2;len<=n;len<<=1)
		{
			int tG=rev?invG:_G;
			for(int i=len;i<G_pw;i<<=1) tG=1ll*tG*tG%mod;
			for(int i=0;i<n;i+=len)
			{
				int w=1;
				for(int j=0;j<len/2;j++)
				{
					int u=a[i+j],v=mul(a[i+j+len/2],w);
					a[i+j]=add(u,v);
					a[i+j+len/2]=dec(u,v);
					w=mul(w,tG);
				}
			}
		}
		if(rev)
		{
			int invn=fpow(n);
			//cout<<invn<<endl;
			R(i,0,n-1) a[i]=mul(a[i],invn);
		}
	}
	vector<ll>poly_mult(vector<ll>a,vector<ll>b)
	{
		int t=(int)(a.size()+b.size());
		int tt=1;
		while(tt<t) tt<<=1;
		vector<ll>c(tt);
		a.resize(tt),b.resize(tt);
		// cout<<"NTT:"<<endl;
		// for(auto x:a) cout<<x<<" ";
		// cout<<endl;
		NTT(a,0),NTT(b,0);

		R(i,0,tt-1) c[i]=mul(a[i],b[i]);
		NTT(c,1);
		return c;
	}
};
int n,m;
bitset<200010>vis;

void solve()
{
	vis.reset();
	cin>>n;
	vector<ll>a(n);
	R(i,0,n-1) cin>>a[i];
	cin>>m;
	vector<ll>b(m);
	R(i,0,m-1) cin>>b[i];
	if(m>2)
	{
		vector<ll>A(n-2),B(m-2),c;
		R(i,0,n-2-1) A[i]=a[i]+2*a[i+1]+a[i+2],c.emplace_back(A[i]);
		R(i,0,m-2-1) B[i]=b[i]+2*b[i+1]+b[i+2],c.emplace_back(B[i]),c.emplace_back(B[i]+1);
		reverse(B.begin(),B.end());
		sort(c.begin(),c.end());
		c.resize(unique(c.begin(),c.end())-c.begin());
		for(ll &x:A) x=lower_bound(c.begin(),c.end(),x)-c.begin()+1;
		for(ll &x:B) x=lower_bound(c.begin(),c.end(),x)-c.begin()+1;

		fu f;
		auto C=f.poly_mult(A,B);
		// for(auto x:C) cout<<x<<" ";
		// cout<<endl; 
		ll s=0;
		R(i,0,m-2-1) s=add(s,mul(A[i],A[i]+1)),s=add(s,mul(B[i],B[i]-1));
		R(i,0,n-m)
		{
			int p=m+i-3;
			if(s!=add(C[p],C[p])) vis[i]=1;
			s=dec(s,mul(A[i],A[i]+1));
			if(i<n-m) s=add(s,mul(A[i+m-2],A[i+m-2]+1));
		}
	}
	R(i,0,n-m) if(!vis[i])
	{
		R(j,0,1)
		{
			ll t=a[i]+a[i+1]-b[0]-b[1]+j;
			if(t>(i+2)/2) continue;
			if(t<-(i+1)/2) continue;
			if(a[i]+get_mn(i+1,t)>b[0]) continue;
			if(a[i]+get_mx(i+1,t)<b[0]) continue;
			R(k,0,m-2-1) if(a[i+k]+2*a[i+k+1]+a[i+k+2]!=b[k]+2*b[k+1]+b[k+2]&&a[i+k]+2*a[i+k+1]+a[i+k+2]+1!=b[k]+2*b[k+1]+b[k+2])
			{
				vis[i]=1;
			}
			if(vis[i]) continue;
			vector<int>ans;
			if(j) ans.emplace_back(i+1);
			R(k,0,m-2-1) if(a[i+k]+2*a[i+k+1]+a[i+k+2]!=b[k]+2*b[k+1]+b[k+2])
			{
				ans.emplace_back(i+k+2);
			}
			ll ddd=b[0]-a[i];
			for(int k=i+1;k>=1;k--)
			{
				ll dc=((k&1)?k:-k),dd=((k&1)?1:-1);
				if(get_mn(k-1,t)<=ddd&&ddd<=get_mx(k-1,t))
				{

				}
				else
				{
					ans.emplace_back(i-k+1);
					ddd-=dc,t-=dd;
				}
			}
			cout<<ans.size()<<'\n';
			for(int x:ans) cout<<x+1<<' ';
			cout<<endl;
			return;
		}
	}
	cout<<-1<<endl;
}	
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int _;
	cin>>_;
	while(_--) solve();
}
```


---


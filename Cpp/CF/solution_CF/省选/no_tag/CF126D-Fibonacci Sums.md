# Fibonacci Sums

## 题目描述

Fibonacci numbers have the following form:

 $ F_{1}=1, $   $ F_{2}=2, $   $ F_{i}=F_{i-1}+F_{i-2},i>2. $ Let's consider some non-empty set $ S={s_{1},s_{2},...,s_{k}} $ , consisting of different Fibonacci numbers. Let's find the sum of values of this set's elements:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF126D/5ab7141541105d7a2a0738fb86760948628a7a20.png)Let's call the set $ S $ a number $ n $ 's decomposition into Fibonacci sum.

It's easy to see that several numbers have several decompositions into Fibonacci sum. For example, for $ 13 $ we have $ 13,5+8,2+3+8 $ — three decompositions, and for $ 16 $ : $ 3+13,1+2+13,3+5+8,1+2+5+8 $ — four decompositions.

By the given number $ n $ determine the number of its possible different decompositions into Fibonacci sum.

## 说明/提示

Two decompositions are different if there exists a number that is contained in the first decomposition, but is not contained in the second one. Decompositions that differ only in the order of summands are considered equal.

## 样例 #1

### 输入

```
2
13
16
```

### 输出

```
3
4
```

# 题解

## 作者：MCAdam (赞：10)

[题目](https://www.luogu.com.cn/problem/CF126D)

题意：$T$次询问，询问将$n$分解成斐波那契数列中互不相同的数的方案

这里的斐波那契数列第一项为$1$,第二项为$2$

$T\leq 10^5\quad n\leq 10^{18}$

~~又一道奇奇怪怪的题~~

首先求出$10^{18}$以内有$88$项，因为题目要求不能选取数列中同一个数，不妨把$n$先表示成一个$01$串，串上第$i$位表示是否取第$i$项

先不管怎么得到这个串，考虑如何从这个串推出其他合法的串串

如果这个串的某一位为$1$,并且它前两位为$0$,那么可以通过让前两位为$1$,这一位为$0$得到一个新的方案

考虑当前这一位的$1$和上一个$1$之间有$cnt$个$0$,那么当前这一位的$1$有$\frac{cnt}{2}+1$种方案。加$1$是不变化的方案，除以$2$是因为，每次变化后下一个能变化的$1$的位置往前偏移两位

并且每一个可拆分的$1$，如果将其拆分它上一位一定为$1$，原因和上面一样：每次变化后下一个能变化的$1$的位置往前偏移两位

记$v[i]$表示串串中第$i$个$1$的位是哪一位

设$f[i][0/1]$表示串串中第$i$个$1$是否取的合法方案数

$\displaystyle f[i][1]=f[i-1][0]+f[i-1][1]\quad$  

当前这一个取，上一个可以取/不取

$\displaystyle f[i][0]=f[i-1][0]\times \frac{v[i]-v[i-1]}{2}+f[i-1][1]\times \frac{v[i]-v[i-1]-1}{2}$

当前这一个不取，上一个不取，中间就有$v[i]-v[i-1]$个$0$（上一个的上一位一定是$1$）；上一个取，中间就有$v[i]-v[i-1]-1$个$0$

最后一个问题：如何得到这个串串？

为了保证答案没有遗漏，这个串所包含的项数应该是最少的，这样才能推出所有的方案

>首先证明：任何一个数都能表示成不同的斐波那契数的和

>采用数学归纳法证明：首先对于$n=1$时成立

>假定对于任意$k<n$都成立，如果$n$本身是一个斐波那契数显然成立

>如果不是，那么一定存在$fib_m<n<fib_{m+1}$

>即$0<n-fib_m<fib_{m-1}$

>根据归纳法：$n-fib_m$能表示成不同的菲波那切数数之和，并且因为它小于$fib_m$，所以这里面没有包含$fib_m$，所以给它加上$fib_m$就得到了$n$

根据上面这个结论，知道了我们需要的串串一定存在，并且还可以依据上述结论贪心地找出项数最小的表示方法

因为要项数最小，所以要让取的数尽可能地大，所以每次不断找到一个最大的$fib_m<n$，$n$减掉它，就得到了这个串串

时间复杂度$O(T\times 88)$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#define ll long long
using namespace std;
int v[100];
ll fib[100],f[100][2];
int main()
{
	fib[1]=1,fib[2]=2;
	for(int i=3;i<=88;i++)
		fib[i]=fib[i-1]+fib[i-2];
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int cnt=0; ll n;
		scanf("%lld",&n);
		for(int i=88;i>=1;i--)
			if(n>=fib[i]) v[++cnt]=i,n-=fib[i];
		reverse(v+1,v+cnt+1);
		f[1][0]=(v[1]-1)/2,f[1][1]=1;//第一如果取方案就是1，如果不取就是前面0的个数除以2 
		for(int i=2;i<=cnt;i++)
		{
			f[i][1]=f[i-1][0]+f[i-1][1];
			f[i][0]=f[i-1][0]*((v[i]-v[i-1])/2)+f[i-1][1]*((v[i]-v[i-1]-1)/2);
		}
		printf("%lld\n",f[cnt][0]+f[cnt][1]);
	}
	return 0;
}
```


---

## 作者：S00021 (赞：4)

### 题意

计算一个整数被分解成若干个各不相等的 Fibonacci 数列中的数的方案 , $T \le 10^5,n \le 10^{18}$.


### Sol

只是存一份档，放在洛谷上给自己看，管理看不顺眼可以不过审。

首先有一个假方法，绕了我很久，方法很暴力，就是直接记 $\text{dp}_n$（用 map 存）表示 $n$ 的拆分方案，然后记忆化搜索转移，很不幸，它连 1e8 都跑不出来。

然后要想着优化对吧，所以我们先预处理出 $5 \times 10^5$ 的 dp 值，然后感觉上 1e18 的范围应该几步也能跑下来，但是又 G 了，因为 1e18 还是要减去二三十个斐波那契数才能到 $5\times 10^5$ ，还是没有大优化。

事实上这个方法是个死胡同，那我们先不想 dp ，先想我们最直观的感受是什么，我们先把问题特殊化（常用 trick ），如果我们要求使用斐波那契数最少的方案呢？这就是个经典题了，我们直接贪心。

那么，推广到原题，我们可不可以使用贪心+调整的思路呢？很遗憾，不可以，我们有一个不可忽略的限制就是使用的斐波那契数不能重复，你如果把一个大数调成了若干个小数之和相当于又对后面造成了影响，G 了；那么我们可不可以找到这个问题的“阶段”把它分拆成若干个子问题呢？很容易想到的是每个斐波那契数的拆分方案处理出来然后乘一乘，可这样又有刚才同样的问题了。

然后走投无路的我们又回到了 dp 上，很自然的一个思路是将 dp 与那个最原始的贪心（直接简单粗暴地定义为使用斐波那契数最少）结合起来，事实上这是别无选择的，为什么呢？因为我想了这么久我已经注意到了 dp 的缺点就是他只是把斐波那契数看成一个普通的数列，对这个数列背包，而没有利用 $\text{fib}_i=\text{fib}_{i-1}+\text{fib}_{i-2}$ 这个性质（单纯的背包自然无法处理这种线性递推）；而贪心的缺点在于它只注意到了斐波那契数列，却没有注意到斐波那契数列以外的限制（数不能相同，求的是方案数而不是最小）。

**所以，两种方法都太片面了，我们必须对它们取其精华去其糟粕**，不然没得玩。

于是我们设计了这样一个充满人类智慧的 dp （这就是积累吗…凭自己独立想只想出了一半就是 $f_i$ ，没想到那个 0/1 ）：我们考虑设贪心存储的那个最优斐波那契数序列为 $v_1,v_2...v_k$ 且 $v_1+v_2+…+v_k=n$ ， 且 $f_{i,0/1}$表示对 $v_1,v_2…v_i$ 表示出的数拆分的方案数，0/1 表示选/不选第 $i$ 项，设计这个 0/1是因为我如果不选 $v_i$ 但是这一位又要有其他位来管就会有不一样的情况。然后怎么转移呢？我们发现难点在不选第 $i$ 项时其他位如何表示出第 $i$ 项，这个时候斐波那契数列终于不再是个普普通通的数列了，他有 $\text{fib}_i=\text{fib}_{i-1}+\text{fib}_{i-2}=\text{fib}_{i-1}+\text{fib}_{i-3}+\text{fib}_{i-4}=...$，即每次能移动的位向低位移动两位。

这样就好办了，只需注意注意我移着移着不能和下一个1碰起来，我们就可以有转移式 

$$f_{i,0}=f_{i-1,0}\times \dfrac{v_i-v_{i-1}}{2}+f_{i-1,1}*\dfrac{v_{i}-v_{i-1}-1}{2}$$
（默认下取整），以及 $f_{i,1}=f_{i-1,0}+f_{i-1,1}$。

这样完了吗？其实还是有可探寻的地方，我们能保证上面那个式子一定是不重不漏的吗？**这不是显然的**，重点还是在 $f_{i,0}$ 的计算上，我们可不可以有一种方法使得 $\text{fib}_{i-1}$ 不取而依然表示出 $\text{fib}_i$ 呢？答案是不可以的，这样要用到重复的元素。

终于做完了。

所以，这种题看的不是代码是思维，真的，如果自己没有真心用心想过，一定会质疑为什么他是 `*2300` 而不是 `*1300` …

而只有那些喜欢做无用功的人，那些傻子，那些如我一般智力平平的 蒟蒻 OIer 们，才会知道这题的难啊。

可是，有谁关心过他们想东西时走的那许多弯路呢？

我曾经也以为，*3000 也不要用什么高深的知识，但是却渐渐明白 ，那些禀赋极高的人终究是极少数，我们没有看到大多数平平无奇的人为了那些看起来轻飘飘的文字与代码消耗了多少个日日夜夜，如果只是以轻松的表象来取悦自己的内心，将那些题解肆意玩弄，抄袭，何必呢？

如果您觉得我 naive ，您大可以把这个标签页关闭，那是您的自由。但我想，每一个如我一般，卑微、渺小、羸弱，而又渴望刺破苍穹的 OIer ，在第一次，第二次独立面对这些时，心中，都会有些许感触吧。

凡事得失兼备，万物圆缺常存。而走过的这些弯道，这些思考，这些难过，这些执着，又未尝不会在未来的某一时刻，凝聚成胸中风云，激荡万千？愿你，也愿我，能够在以后漫漫长路风雨兼程时，尚能有一份思考的冲动。让那不灭的激情，似光，似火，似萤，点亮黑暗，冲破囹圄。

我们，一起共勉，愿向着彼岸，手牵手走向明天。

衷心感谢您，在我最迷茫的时刻，读完了这篇文章，我已经感受到了那份隔着屏幕的慰藉与期许，也希望您的未来，将会大放异彩。

唱出你的热情，伸出你的双手，让我们期待明天会更好！

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
int T,n,s[101],f[101][2]; 
vector<int>vi;
signed main(){
	scanf("%lld",&T); s[0]=s[1]=1;
	for(int i=2;i<=90;i++) 
		s[i]=s[i-1]+s[i-2]; s[0]=0;
	while(T--){
		scanf("%lld",&n); vi.clear(); 
		for(int i=90;i;i--){
			if(n>=s[i]) n-=s[i],vi.pb(i);
			f[i][0]=f[i][1]=0;
		}reverse(vi.begin(),vi.end()); int ln=(int)vi.size();
		f[0][0]=(vi[0]-1)/2,f[0][1]=1;
		for(int i=1;i<ln;i++){
			f[i][1]=f[i-1][0]+f[i-1][1];//this indicates that fib[v[i]] has already been obtained and as a result the previous bits dont need change
			f[i][0]=f[i-1][0]*((vi[i]-vi[i-1])/2)+f[i-1][1]*((vi[i]-vi[i-1]-1)/2);
		}printf("%lld\n",f[ln-1][0]+f[ln-1][1]);
	}return 0;
}
```


---

## 作者：JustPureH2O (赞：2)

[更好的阅读体验](https://justpureh2o.cn/artcles/126)

题目地址：[CF 126D](https://www.luogu.com.cn/problem/CF126D)

## 前置 齐肯多夫定理

齐肯多夫定理的内容是：

> 任何正整数都可以被表示成若干不连续的斐波那契数之和（$F_1$ 除外）

而对于一个正整数，我们可以按照二进制分解的策略：先贪心地找到一个最大的 $k$ 满足 $F_{k-1}<n<F_k$，然后用 $n$ 减去 $F_{k-1}$，以此类推直到减为 $0$。

斐波那契数列一般定义为：$\{1,1,2,3,5,8,13,\dots\}$，这里我们做一个整体左移，本文所述的斐波那契数列应是数列 $\{1,2,3,5,8,13,\dots\}$，也就是 $F_1=1,F_2=2,F_3=3$。

类比二进制，齐肯多夫分解是可以用一个 $0/1$ 串表示出来的。例如：$28=21+3+1=F_7+F_3+F_1$。因此它的齐肯多夫拆分就是：$(1000101)_F$。

不难发现，按照贪心策略计算出的拆分是不会存在相邻的两个 $1$ 的。因为一旦出现连续的 $1$，都可以遵循斐波那契数的定义把它变为一个更大的斐波那契数。

## 回归正题

假如我们现在已经得到了一个齐肯多夫拆分，如何计算题目要求的方案总数呢？

可以利用“标准齐肯多夫拆分中不存在相邻 $1$”的结论。对于原串的一个模式串 `*100*`（星号代表任意 $0/1$ 串），我们可以拆成 `*011*`。如果在末尾的 $1$ 后还有更多的 $0$，那其实也是可以再次拆分的。

注意到要求方案数，考虑动态规划。我们用 $A_i$ 表示拆分中第 $i$ 个 $1$ 的出现位置，并令状态转移方程为 $f_{i,0/1}$，表示选择是否删除 $A_i$ 位后的总方案数。

接下来考虑当前状态从何而来。如果选择不删当前这一位，答案只能从前一位 $1$ 那里贡献而来，也即 $f_{i,0}=f_{i-1,0}+f_{i-1,1}$。

如果选择删除这一位，对于接下来的操作，我们仍然可以选择删除或不删除。发现删到最后整个字符串一定是像 `101010101` 这样交错排列的。于是可以得到：

$$
\begin{aligned}
f_{i,0}&=f_{i-1,0}+f_{i-1,1}
\\f_{i,1}&=f_{i-1,0}\times\lfloor\frac{A_i-A_{i-1}-1}{2}\rfloor+f_{i-1,1}\times\lfloor\frac{A_i-A_{i-1}}{2}\rfloor
\end{aligned}
$$

```cpp
#include <bits/stdc++.h>
 
#define N 90
using namespace std;
 
typedef long long ll;
 
vector<int> pos;
ll fib[N];
ll dp[N][2];
 
void init() {
    fib[1] = fib[2] = 1;
    for (int i = 3; i < N; i++) fib[i] = fib[i - 1] + fib[i - 2];
}
 
int solve(ll x) {
    pos.clear();
    for (int i = N - 1; i >= 1; i--) {
        if (!x) break;
        if (fib[i] <= x) {
            x -= fib[i];
            pos.push_back(i - 1);
        }
    }
    reverse(pos.begin(), pos.end());
    return pos.size();
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    int t;
    cin >> t;
    init();
    while (t--) {
        memset(dp, 0, sizeof dp);
 
        ll x;
        cin >> x;
        int len = solve(x);
        dp[0][0] = 1;
        dp[0][1] = (pos[0] - 1) / 2;
        for (int i = 1; i < len; i++) {
            dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
            dp[i][1] = dp[i - 1][0] * ((pos[i] - pos[i - 1] - 1) / 2) + dp[i - 1][1] * ((pos[i] - pos[i - 1]) / 2);
        }
        cout << dp[len - 1][1] + dp[len - 1][0] << endl;
    }
    return 0;
}
```

[CF 通过记录](https://codeforces.com/contest/126/submission/288986966)

$\texttt{The End}$

---

## 作者：abruce (赞：2)

首先考虑把这个数化为齐肯多夫式的斐波那契表示，即设 $n=\sum\limits_{i=1}^m Fib_ia_i$，其中 $a_m=1,\forall a_i\in \{0,1\}$，若 $a_i=1$ 则 $a_{i+1}=0$。我们可以用贪心算法构造这个表示。  
得到这个表示之后，我们知道 $Fib_i=Fib_{i-1}+Fib_{i-2}$，我们可以把某些位上的 $1$ 化为靠前连续的两个 $1$，以此类推。由此，我们可以得到一个 dp。我们从高到低考虑，设 $g_{i,0/1/2}$ 为处理到 $i$ 位，当前剩余几位待填充（若将一个 $Fib_i$ 分解为 $Fib_{i-1}$ 和 $Fib_{i-2}$，则剩余 $2$ 位未填充）。考虑转移。  
若第 $i$ 位在原先的表示中有值，那么 $g_{i,0}=g_{i+1,0}$（保持不动），$g_{i,2}=g_{i+1,0}+g_{i+1,1}$（分解，此时 $i$ 这位空出，可以供填充）。  
若第 $i$ 位在原先表示中无值，那么 $g_{i,0}=g_{i+1,0}+g_{i+1,1}$（有一个空供填充），$g_{i,1}=g_{i+1,2}$（越过 $i$ 这一位剩余 $1$ 需填充），$g_{i,2}=g_{i+1,1}$（将这位填充之后立刻将其分解）。  
时间复杂度 $O(t\log n)$  
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int lim=88;
ll f[lim+1],g[lim+1][3],n;
int t,a[lim+1];
int main() {
	scanf("%d",&t),f[0]=f[1]=1;
	for(int i=1; i<=lim; i++)f[i]=f[i-1]+f[i-2];
	while(t--) {
		int m=0;
		scanf("%lld",&n),memset(g,0,sizeof(g)),memset(a,0,sizeof(a));
		for(int i=lim; i; i--)if(n>=f[i])n-=f[i],a[i]=1,m?0:m=i;
		g[m+1][0]=1;
		for(int i=m; i; i--) {
			if(!a[i])g[i][0]=g[i+1][0]+g[i+1][1],g[i][1]=g[i+1][2],g[i][2]=g[i+1][1];
			else g[i][2]=g[i+1][0]+g[i+1][1],g[i][0]=g[i+1][0];
		}
		printf("%lld\n",g[1][0]);
	}
	return 0;
}
```

---

## 作者：bluewindde (赞：0)

做法同 [P4133 [BJOI2012] 最多的方案](https://www.luogu.com.cn/problem/P4133)。

记忆化搜索，设 $f(x, k)$ 表示当前考虑 $F_k$，需要分解的数是 $k$，分类讨论

- 若 $x = 0$，则 $f(x, k) = 1$；
- 若 $k = 1$，则 $f(x, k) = 0$；
- 若 $x < F_k$，则 $f(x, k) = f(x, k - 1)$；
- 若 $x > F_1 + F_2 + F_3 + \cdots + F_{k - 1} = F_{k + 1} - 1$，则 $f(x, k) = f(x - F_k, k - 1)$，因为此时不分解出 $F_k$ 就一定无解；
- 否则，$f(x, k) = f(x - F_k, k - 1) + f(x, k - 1)$。

### 时间复杂度分析

考虑势能分析，设 $\Phi(n, k)$ 表示计算 $f(x, k)$ 时 $x$ 的最大可能值。

断言：要么 $\Phi(n, k) < F_{k + 1}$，要么 $\Phi(n, k)$ 在常数次迭代内可以满足前述情况。

> **证明**
>
> 边界情况令 $\Phi(n, k) = n$，接下来假设 $k > 2$。
>
> 考虑在转移过程中说明断言成立。
>
> - 若 $x < F_k$，则 $\Phi(n, k - 1) < F_k$ 满足断言；
> - 否则，分类 $f(x, k) = f(x, k - 1) + f(x - F_k, k - 1)$ 中的两项。注意此时 $F_k \leqslant x < F_{k + 1}$，所以
>   1. 对于 $f(x - F_k, k - 1)$，有 $0 \leqslant x - F_k < F_{k - 1}$，满足断言。进一步，其继续迭代一次仍满足断言；
>   2. 对于 $f(x, k - 1)$，下一次迭代必然走向 $f(x - F_{k - 1}, k - 2)$，此时 $F_{x - 2} \leqslant x - F_{k - 1} < F_{k - 1}$ 满足断言。
>
> 断言成立。
>
> Q.E.D.

**推论**

设 $\phi = \frac {\sqrt 5 - 1} 2$，则当 $k$ 足够大时，每两次迭代至少使势能变为原来的 $2 \phi^2 \approx 0.764$。

> **证明**
>
> $k$ 足够大时，斐波那契数列相邻两项比值 $\frac {F_k} {F_{k + 1}} = \phi$。
>
> 继续上一个证明的分类讨论：
> 
> - 第一类情况中，一次迭代使得势能变为原来的 $\phi$，两次即为 $\phi^2$；
> - 第二类情况中，两次迭代使得势能变为原来的 $2 \phi^2$，两种子情况分别贡献 $\phi^2$；
> - 特殊地，如果第一类情况后接着第二类情况，三次为 $2 \phi^3$，平均一次 $(2 \phi^3)^{\frac 2 3} = \sqrt[3]4 \phi^2 < 2 \phi^2$。
>
> 因此势能至少变为 $2 \phi^2$。
>
> Q.E.D.

所以，总迭代次数约为 $-2\log_{2 \phi^2}(n) \sim 2\log_{1.309}(n) \sim O(\log_{1.309}(n))$，时间复杂度正确。

注意 $k$ 较小时，比值大于 $2 \phi^2$，但由于该估计本身较松，对时间复杂度没有太大影响。

为了减小常数，使用 `gp_hash_table` 存储答案，每组数据前需要清空哈希表。时间复杂度 $O(T \log_{1.309}(n))$。

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <iostream>

#define int long long

using namespace std;
using namespace __gnu_pbds;

int fib[100];

struct hs {
    inline int operator()(const pair<int, int> &x) const {
        return x.first ^ x.second;
    }
};

gp_hash_table<pair<int, int>, int, hs> mp;
static inline int dfs(int x, int k) {
    if (x == 0)
        return 1;
    if (k == 1)
        return 0;
    auto it = mp.find({x, k});
    if (it != mp.end())
        return it->second;
    if (x < fib[k])
        return mp[{x, k}] = dfs(x, k - 1);
    if (fib[k + 1] - 1 < x)
        return mp[{x, k}] = dfs(x - fib[k], k - 1);
    return dfs(x - fib[k], k - 1) + dfs(x, k - 1);
}

static inline void solve() {
    int n;
    cin >> n;
    mp.clear();
    cout << dfs(n, 88) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    fib[1] = fib[2] = 1;
    for (int i = 3; i <= 88; ++i)
        fib[i] = fib[i - 1] + fib[i - 2];
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

首先要知道 [Zeckendorf's Theorem](https://en.wikipedia.org/wiki/Zeckendorf%27s_theorem)，即任何一个正整数都可以被表示为若干个不连续的斐波那契数的和。更确切的来说，任意正整数 $n$，都可以找到至少一个单调递增的序列 $a_1,a_2,\ldots,a_k$ 使得 $\forall i\in[1,k),a_{i+1}-a_i\ge 2$，且 $\sum\limits_{i=1}^k F_{a_i}=n$，其中 $F_i$ 为 Fibonacci 数的第 $i$ 项。

然后可以直接贪心的分解 Fibonacci 数，得到一个 Fibonacci 生成序列，设这个序列的元素从小到大分别为 $a_1,a_2,\ldots,a_k$，则可以知道，其实只有下面三种情况是合法的转移：

+ 选择当前数
+ 选择当前数的前一个
+ 选择当前数的前一个的前一个

可以证明如果当前连续三个数都不选，那么剩下的数一定无法凑出剩余的 $n$ 的部分。证明显然，直接套用 Fibonacci 数的基础性质即可。

然后考虑一个简单的 dp：设 $f_{i,0/1}$ 表示前 $i$ 项中，第 $i$ 项不选 / 选，方案数是多少。那么显然若选择第 $i$ 项，则上一项选择 / 不选择无所谓，即 $f_{i,1}\leftarrow f_{i-1,1}+f_{i-1,0}$，如果不选第 $i$ 项，则若上一个不选，则上上个就必须选。同样的套路分两类讨论答案即可。可以线性转移，具体见代码。时间复杂度为 $O(n)$，可以通过。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 300010;
int a[N], F[N], f[N][2];
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int T;
    cin >> T;
    F[1] = 1, F[2] = 2;
    for (int i = 3; i <= 90; ++i) F[i] = F[i - 1] + F[i - 2];
    while (T--) {
        int n, idx = 0;
        cin >> n;
        for (int i = 90; i; --i)
            if (n >= F[i]) n -= F[i], a[++idx] = i;
        sort(a + 1, a + idx + 1);
        f[1][1] = 1, f[1][0] = (a[1] - 1) / 2;
        for (int i = 2; i <= idx; ++i) {
            f[i][1] = f[i - 1][0] + f[i - 1][1];
            f[i][0] = f[i - 1][0] * ((a[i] - a[i - 1]) / 2) + f[i - 1][1] * ((a[i] - a[i - 1] - 1) / 2);
        }
        cout << f[idx][0] + f[idx][1] << '\n';
    }
    return 0;
}


```

---


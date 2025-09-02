# [ARC152C] Pivot

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc152/tasks/arc152_c

$ N $ 項からなる数列 $ a_1,a_2,\ldots,a_N $ があります。 あなたはこれから、この数列に以下の操作を好きな回数行うことができます。（$ 1 $ 回も行わなくてもよいです。）

- その時点の数列から項を $ 1 $ つ選び、その値を $ s $ とする。 次に、全ての $ 1\leq\ i\leq\ N $ に対して、$ a_i $ を $ 2s-a_i $ で置き換える。 ただし、この操作によって、数列に負の値を持つ項が生じてはならない。
 
あなたは、数列の項の最大値をできるだけ小さくしたいと考えています。 適切に操作を行った場合の、数列の項の最大値はいくつになるでしょうか。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ a_1\ <\ a_2\ <\ \ldots\ <\ a_N\ \leq\ 10^9 $
- 入力される値はすべて整数である
 
### Sample Explanation 1

$ s=3 $ として操作を行うと、数列は $ (5,3,0) $ になります。このとき最大値は $ 5 $ です。 数列に負の項が生じてはいけないという条件の下で、これ以上数列の項の最大値を小さくすることはできませんので、$ 5 $ と答えてください。

### Sample Explanation 2

$ s=400 $ として操作を一度行うほか、$ s=500 $ として操作を行った後、$ s=300 $ としてもう一度操作を行うなどの方法が考えられます。

## 样例 #1

### 输入

```
3
1 3 6```

### 输出

```
5```

## 样例 #2

### 输入

```
5
400 500 600 700 800```

### 输出

```
400```

# 题解

## 作者：Gorenstein (赞：10)

### 题意

给定一个严格单增的正整数序列 $a$。你可以执行以下操作任意次（包括 $0$ 次）：
- 选择序列中的一个数 $s$，然后对于序列中的每个数 $a_i$，将其替换为 $2s-a_i$。注意，只有当操作后序列中不存在负数时，该操作才可以被执行。

你希望通过执行若干次操作使序列的最大值尽可能地小。请求出这个最小化的最大值。

------------

将序列画到数轴上。考虑每一次操作的实质，可以发现其实质为选取数轴上的一个点，并将所有点以该点为对称中心翻转。

由此我们可以得到两条性质：
- 进行任何一次操作，其最大值与最小值之差不变。
- 不论如何操作，点分布的整体形态不变，即要么和初始的分布相同，要么是初始分布翻转后的结果。

对于第二条性质而言，设其中提到的两种分布形态为状态 $A$ 和 $B$，并令初始状态为 $A$，则每次操作要么使序列从状态 $A$ 变为状态 $B$，要么使其从状态 $B$ 变回状态 $A$。这启发我们每个点对于最小值的贡献只有两种情况，且和奇偶性有关。

不妨先考虑第一次操作。设操作的数为 $a_i$，则翻转后原先的最大值变为最小值，即最小值由 $a_1$ 变为了 $2a_i-a_n$。也即，操作 $a_i$ 对最小值的贡献为 $a_1+a_n-2a_i$。不妨令其为 $b_i=\left|a_1+a_n-2a_i\right|$。

进一步，设现在某次操作后为状态 $A$，则相当于对点进行整体平移 $x$ 的位置，易见即使平移过后，操作 $a_i$ 的贡献仍然为 $a_1+a_n-2a_i$。而对于状态 $B$，易见其贡献只是上值的相反数。因此我们可以断言：对于 $a_i$ 的操作，要么使最小值增加 $b_i$，要么使最小值减少 $b_i$，且符号取决于该次操作的编号的奇偶性。

考虑一种情况。假设我想在奇数次操作的时候对 $a_i$ 进行操作，但很不巧现在需要进行的又是第偶数次，怎么办呢？这时我们可以直接对 $a_n$ 进行操作，这样再操作就是第奇数次了。而消除 $a_n$ 操作的方法也很简单，在某个时候再进行一次操作把序列翻回来即可。

综上所述，我们将问题转化为了：给定序列 $b$，求将 $a_1$ 加上 $b_1,b_2,\dots,b_n$ 的线性组合后能够得到的最小非负值。

根据裴蜀定理，$b_1,b_2,\dots,b_n$ 的非负线性组合的最小值为 $\gcd(b_1,b_2,\dots,b_n)$（不妨设其为 $d$），且其他非负线性组合均为其倍数。因此 $a_1\bmod d$ 就是能够得到的最小值。再将其加上原序列最大值与最小值的差即是能够得到的最大值。

[***code***](https://www.luogu.com.cn/paste/uwjtchuh)

------------
官方题解和该题解的做法是本质相同的。如果你不理解，只需将该题解的 $a_n-a_1$ 换进官方题解。

---

## 作者：Alex_Wei (赞：7)

设 $d = a_n - a_1$，考虑 $n = 2$ 的情况，发现任意时刻 $a_1$ 可对 $d$ 取模。因此，答案即 $a_1\bmod d$ 的最小值加上 $d$。

通过不断选最大值将所有点拉到一个足够远的地方，消除不可以碰到负轴的限制。

考虑到选 $a_i$ 做轴会将最小值改变 $(2a_i - a_n) - a_1$，而因为 $a_1\equiv a_n\pmod d$，所以最小值模 $d$ 会改变 $2(a_i - a_1)$。但操作后 $a_1$ 和 $a_n$ 交换了相对位置，此时再选择 $a_i$ 则会抵消掉前一次操作。没有关系，在两次操作之间操作一次端点即可。

换言之，如果 $a_i$ 在某个奇数次被操作，又在某个偶数次被操作，则这两次操作可以抵消。我们只需要在操作之间插入不改变 $a_1\bmod d$ 的两端操作，即可让每个 $a_i$ 对 $a_1\bmod d$ 的贡献取到任意倍 $2(a_i - a_1)$。

根据裴蜀定理，$a_1\bmod d$ 的最小值即 $\gcd(d, 2(a_i - a_1))$。时间复杂度 $\mathcal{O}(n)$。[代码](https://atcoder.jp/contests/arc152/submissions/36888421)。

---

## 作者：_ZSR_ (赞：4)

### [[ARC152C] Pivot](https://www.luogu.com.cn/problem/AT_arc152_c)

假设第 $i$ 次选择的数的下标为 $b_i$。

第一次操作：$a={2a_{b_1}-a_1,2a_{b_1}-a_2,\dots,2a_{b_1}-a_n}$。

第二次操作：$a={2a_{b_1}-2a_{b_2}+a_1,2a_{b_1}-2a_{b_2}+a_2,\dots,2a_{b_1}-2a_{b_2}+a_n}$。

不难发现，每次操作会使得 $a_1$ 加上或减去 $2 \times (a_{b_i}-a_1)$。那么令 $c_i=2 \times (a_{b_i}-a_1)$，$a_{1min}=a_1-\sum c_i \times d_i$。根据裴蜀定理，$\sum c_i \times d_i=k \times gcd(c_1,c_2,\dots,c_m)$，所以 $a_{1min}=a_1 \bmod gcd(c_1,c_2,\dots,c_m)$。同理可得 $a_{nmin}$。

将序列放到数轴上之后会发现，每次操作其实就是选择一个数，其它数则以它为轴翻转。那么最大值和最小值的差是不变的。前面已经说了怎么求 $a_{1min}$ 和 $a_{nmin}$，那么答案就是两个里面更小的那个加上 $a_n-a_1$。

code 
```
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n;
int a[N];
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;++i) scanf("%d",&a[i]);
    int g=0,d=0;
    for (int i=1;i<=n;++i) 
    {
        g=gcd(2*(a[i]-a[1]),g);
        d=gcd(2*(a[i]-a[n]),d);
    }
    printf("%d\n",min(a[1]%g,a[n]%d)+a[n]-a[1]);
    return 0;
}
```


---

## 作者：Emptilife (赞：3)

在数轴上考虑，易得一次操作相当于选定对称轴翻转。

任意时刻只存在两种相对状态——原状态和翻转状态，且和操作奇偶性相关。

令 $d=a_n-a_1$，通过不断以最小值为轴翻转，可知任意时刻 $a_1$ 可对 $d$ 取模。

不断以最大值为轴翻转，可以剔除 $a_i\ge 0$ 的限制。

考察以 $a_i$ 为轴翻转，最小值由 $a_1\to 2a_i-a_n$，增加了 $2a_i-a_1-a_n$，由于 $a_1$ 同余 $a_n\pmod d$，对 $a_1\bmod d$ 的贡献即 $2(a_i-a_1)$。再操作一次会相互抵消。

通过不断以最大值为轴翻转，可以剔除操作奇偶性的限制。

由裴蜀定理可得，$2(a_i-a_1)$ 的线性组合为 $k\cdot \gcd(d,\gcd_i2(a_i-a_1))$。故 $a_1$ 最小可以达到 $a_1\bmod \gcd(d,\gcd_i 2(a_i-a_1))$。


---

## 作者：Charlie_ljk (赞：1)

发现不论如何操作，满足 $a_i-a_j$ 的值恒不变，设 $d=a_n-a_1$。

钦定序列为升序排序，若另 $s=a_i$，则有 $a_1'=2\times a_i-a_n$。

对于 $a_1\ge 0$ 的限制，不放直接求 $a_1\bmod d$，最后答案为 $a_n'=a_1'\bmod d+d$。

由此 $a_1\equiv a_n\pmod d$，所以有 $2a_i-a_n\equiv 2(a_i-a_1)$，固有 $a_1'=a_1+2(a_i-a_1)$，其中 $a_i-a_1$ 恒不变。

对于一个 $a_i$，只需另下一次操作不再取 $a_i$ 为 $s$ 就不会恢复原来状态，故 $a_i$ 可以贡献任意个 $2(a_i-a_1)$。

考虑每个 $a_i$ 的贡献，设 $a_1+x\times 2(a_i-a_1)=rd+c$，$r$ 为任意倍数，$c$ 表示最后的 $a_1'\bmod d$，移项有 $rd-x\times 2(a_i-a_1)=a_1-c$，根据裴蜀定理，有 $\gcd(2(a_i-a_1),d)\mid(a_1-c)$，为使 $c$ 最小取最大倍数的 $\gcd(2(a_i-a_1),d)$ 即可。循环 $a_i$ 取最小值，答案初始值为 $a_n$。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define endl '\n'
#define sort stable_sort
using namespace std;
const int N=2e5+10,B=1e9+7;
template<typename Tp> inline void read(Tp&x)
{
    x=0;register bool z=true;
    register char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') z=0;
    for(;'0'<=c&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
    x=(z?x:~x+1);
}
template<typename T,typename ...Tp> inline void read(T &x,Tp &...y){read(x);read(y...);}
template<typename Tp> inline void wt(Tp x)
{if(x>9)wt(x/10);putchar((x%10)+'0');}
template<typename Tp> inline void write(Tp x)
{if(x<0)putchar('-'),x=~x+1;wt(x);}
template<typename T,typename ...Tp> inline void write(T x,Tp ...y){write(x);putchar(' ');write(y...);}
int n,a[N],ans;
signed main()
{
    read(n);
    for(int i=1;i<=n;i++) read(a[i]);
    int d=a[n]-a[1];
    ans=a[n];
    for(int i=1;i<=n;i++)
    {
        int s=__gcd(2*(a[i]-a[1]),d);
        int x=a[1]/s;
        ans=min(ans,a[1]-s*x+d);
    }
    write(ans);
}
```

---

## 作者：E_M_T (赞：0)

观察到性质：两个数在进行若干次操作后差不变。

设目前操作 $x$，有 $a_i\gets 2x-a_i$。操作前后两数差值均为 $|a_i-x|$。

于是可以看作是在数轴上操作，操作 $x$ 则相当于在数轴上以 $x$ 为对称轴翻转。

钦定数组升序，设操作后的序列为 $a'$。

则翻转后数组的最大值和最小值都一定是 $a_1'$ 或 $a_n'$，奇数次翻转则最小值为 $a_n'$，偶数次为 $a_1'$。

考虑第一次操作 $x$，最**小**值从 $a_1$ 变为 $2x-a_n$，贡献（原最小值和现最小值的差）为 $|a_1+a_n-2x|$。

然后你发现第二次、第三次也是这个贡献，一次加一次减，符号和奇偶性相关。

令 $p_i=|a_1+a_n-2a_i|$，表示操作 $a_i$ 的贡献。

由于操作被看成了翻转，所以有一个显然性质是：翻转两次相同的 $x$ 之后贡献会被抵消，所以 $p_i$ 的符号可以是任意的，次数可以是任意的。

假设想改变操作 $x$ 的奇偶性，则连续操作三次 $x$ 即可，前后两次贡献会被抵消，中间一次的奇偶性会被改变。

所以操作后 $\min(a_i)$ 的最小值为 $a_1+\sum\limits_{i-1}^n p_ix_i$ 的非负最小值，$x_i\in \mathbb{Z}$。

由裴蜀定理得知 $k=\sum\limits_{i-1}^n p_ix_i$ 的 $x_i$ 有解时当且仅当 $k\mid \gcd(p_i)$。


即求 $a_1+d\times \gcd(p_i)$ 的非负最小值，$d\in \mathbb{Z}$。

显然答案为 $a_1\bmod \gcd(p_i)$。

注意到题目要求的是最大值。因为最大最小值的差恒定，所以将这个问题的答案加上 $a_n-a_1$ 就是最大值。

```cpp
n=read();
F(i,1,n) a[i]=read();
F(i,1,n) b[i]=abs(a[1]+a[n]-2*a[i]);
int g=0;
F(i,1,n) g=sd __gcd(g,b[i]);
put(a[n]-a[1]+a[1]%g);
```

---

## 作者：liangbowen (赞：0)

[blog](https://www.cnblogs.com/liangbowen/p/18344918)。可能是很简单的，但是我实在是不会这种神秘题 /ll /ll。

---

+ Conclusion1. 记 $d=a_n-a_1$，则极差始终等于 $d$。证明显然。
+ Conclusion2. 操作极值时，最小值始终变化为 $d$，并且可以进行无限次这样的变化。证明显然。

> 题意转变：最小化 $(\texttt{最小值} \bmod d)$，且最小值始终非负，输出这个值 $+d$。

由 Conclusion2，可以通过提前加上充分多个 $d$ 来避免负数的问题。

> 题意转变：最小化 $(\texttt{最小值} \bmod d)$，输出这个值 $+d$。

操作 $x$ 可以使 $a_1\to 2x-a_1$，即 $a_1$ 加上了 $2(x-a_1)$，再操作下原本的 $a_n$ 就可以使最小值加上 $2(x-a_1)$。

同理，我们也可以使最小值减去 $2(x-a_1)$。于是我们有：

+ Conclusion3. 最小值可以任意加减 $2(a_i-a_1)$ 无限次。

由裴蜀定理，线性组合这些东西，可以使最小值任意加减 $g=\gcd\{d, 2(a_2-a_1), 2(a_3-a_1), \cdots, 2(a_n-a_1)\}$ 次，答案即 $(a_1\bmod g) + d$。模拟即可。$O(n)$。

---

## 作者：Erica_N_Contina (赞：0)

# [ARC152C] Pivot
[blog here](https://ntsc.blog.luogu.org/solution-at-arc152-c)

## 思路

### 初步想法（题意理解）

我们考虑 $ s=a_k $ 的情况。操作之后，$ a_1\sim a_n $ 变成 $ 2\times a_k-a_1\sim2\times a_k-a_n $，其中 $ a_k $ 变成 $ a_k $。

由于我们可以进行任意次操作，所以我们认为序列 $a$ 是随机的。此时我们考虑怎么样选择那个 $ a_k $ 才能使得这个序列的最大值最小化。很显然，我们要使得 $ a_k $ 尽可能小，同时保证 $ 2\times a_k≥\min(a_{1\sim n}) $。很显然，我们应该选择 $ a_1\sim a_n $ 中最靠近 $ 2\times \min(a_{1\sim n}) $ 且大于等于 $ 2\times \min(a_{1\sim n}) $ 的数。这样的话这个序列的最大值就会靠近 $ \min(a_{1\sim n}) $。但如果要模拟的话，肯定是不行的，所以我们考虑正解。

### 差值结论

我们从数学的角度来考虑每一次操作：选择序列里面的一项 $ a_k $，对于每一个数列里面的每一项 $ a_i $，将 $ a_i $ 替换为 $ 2a_k -a_i $，就相当于在数轴上以 $ a_k $ 为对称轴，将整个数轴进行翻转。由此我们可以得到一个性质：**无论任何操作，序列中最大值和最小值的差值不变。**我们记录这个差值为 $ d $。

既然知道了这点，我们就可以暂时把问题转化为：求进行若干次操作后序列中的最小值最小为多少。

### 每次操作对于 $ a_i $ 的影响

我们距离进行说明（这里是罗马数字，$ ii $ 表示第 $ 2 $ 次操作选择的 $ s $ 在 $ a $ 中对于的下标）。

|操作次数||||
|-|-|-|-|
| $ 0 $ | $ a_1 $ | $ a_2 $ | $ \dots $ |
| $ i $ | $ 2a_i-a_1 $ | $ 2a_i-a_2 $ | $ \dots $ |
| $ ii $ | $ 2(2a_i-a_{ii})-(2a_i-a_1)=2a_i-2a_{ii}+a_1 $ | $ 2a_i-2a_{ii}+a_2 $ | $ \dots $ |

对于 $ a_1 $，进行 $ N $ 次操作后的值为 $ 2\times[s_N-s_{N-1}+\dots+(-1)^{N}\times a_1] $。

此时，序列中每个数的最终值就只和初始值和操作次数N有关了。由于题目保证 $ a_1\ <\ a_2\ <\ \ldots\ <\ a_N $，所以我们只需要考虑 $ a_1 $ 和 $ a_n $ 在进行 $ N $ 次操作后的值即可，$ a_2\sim a_{n-1} $ 的最终值一定在 $ a_1 $ 和 $ a_n $ 之间，我们不需要考虑。（由于序列会进行若干次翻转，所以我们不知道 $ a_1 $ 和 $ a_n $ 那个才是答案序列中的最小值，所以两者我们都要考虑）。

我们发现，第 $ i $ 次操作我们将 $ a_1 $ 加上了 $ 2\times(-1)^i\times(a_1-s_i) $（这里的 $ s_i $ 指的是第 $ i $ 次操作选择的那个数，但整个数已经不是从上一次操作完的序列中选择的，而是从初始序列中选择的）。

### 计算最小值

我们可以表达出 $ a_1 $ 的最终值 $ a'_1=\sum\limits_{i=1}^{N\in\N}[2\times(-1)^i\times(a_1-s_i)]+a_1 $。很显然，现在我们只需要知道 $ \sum\limits_{i=1}^{N\in\N}[2\times(-1)^i\times(a_1-s_i)] $ 的最小值是多少即可。

### 裴蜀定理


设 $a,b$ 是不全为零的整数，则存在整数 $x,y$，使得 $ax+by=\gcd(a,b)$。

重点来了，根据裴蜀定理，我们可以知道 $ \sum\limits_{i=1}^{N\in\N}[2\times(-1)^i\times(a_1-s_i)]\subset \{x|x=k\gcd(2a_1-2a_1,2a_2-2a_1,\dots,2a_n-2a_1),k\in \N\} $。

所以 $ a'_1=a_1+k\gcd(2a_1+a_1,\dots,2a_n-2a_1) $，因为 $ a'_1>0 $ 且求其最小值，所以 $ \min(a'_1)=a_1\mod\gcd(2a_1+2a_1,\dots,2a_n-2a_1) $。

同理，$ \min(a'_n)=a_n\mod\gcd(2a_1+2a_n,\dots,2a_n-2a_n) $。

那么我们知道了 $ \min(a'_1) $ 和 $ \min(a'_n) $ 后，还不能直接输出它们的最大值。因为我们仅仅知道了当 $ a'_1 $ 取最小时的 $ a'_1 $，此时 $ a'_1 $ 肯定在序列的最前面（从小到大排序），那么根据**序列中最大值和最小值的差值不变**，我们就知道了此时序列中的最大值为 $ a'_1+d $。同理，当 $ a'_n $ 取最小值时，序列中的最大值为 $ a'_n+d $ 。然后我们在这两个值之间取最小值才对。

## 代码

```C++
/*////////ACACACACACACAC///////////
	  . Coding by Ntsc .
	  . ToFind Chargcy .
	  . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>

//数据类型
#define ll long long
#define ull unsigned long long
#define db double
#define endl '\n'
//命名空间
using namespace std;
//常量
const int N=2e5+5;
const int M=1e3;
const int MOD=903250223;
const int INF=1e9;
//变量
int n,m,d,a[N],y[N],ans;

signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	d=a[n]-a[1];
	int g1=0;
	for(int i=1;i<=n;i++){
		g1=__gcd(g1,2*a[i]-2*a[1]);
	}
	int g2=0;
	for(int i=1;i<=n;i++){
		g2=__gcd(g2,2*a[i]-2*a[n]);
	}
	ans=min(a[1]%g1,a[n]%g2)+d;

	printf("%d\n",ans);
	return 0;
}
```






---

## 作者：_Life_ (赞：0)

### 题意

有一个长为 $n$ 的序列 $a$。每次可以从 $a$ 中选取一个数字 $s$，将 $a_i$ 变换为 $2s-a_i$，**不允许过程中产生负数**。求任意次（包括零）操作后，$\max(a)$ 的最小值。

$2\leq n \leq 2\times 10^5$

$1\leq a_1 \leq a_2 \leq \cdots \leq a_n \leq 10^9$

### 题解

操作不会改变两数之差，所以 $d=a_n-a_1$ 值不变。

$\max(a)=\min(a)+d$

假设第 $i$ 次操作选择的数下标为 $p_i$。

初始：$a=\left\{ a_1,a_2,\cdots,a_n \right\}$

第一次操作：$s=a_{p_1},a=\left\{ 2a_{p_1}-a_1,2a_{p_1}-a_2,\cdots,2a_{p_1}-a_n \right\}$

第二次操作：$s=2a_{p_1}-a_{p_2},a=\left\{ 2a_{p_1}-2a_{p_2}+a_1,2a_{p_1}-2a_{p_2}+a_2,\cdots,2a_{p_1}-2a_{p_2}+a_n \right\}$

第三次操作：$s=2a_{p_1}-2a_{p_2}+a_{p_3},a=\left\{ 2a_{p_1}-2a_{p_2}+2a_{p_3}-a_1,2a_{p_1}-2a_{p_2}+2a_{p_3}-a_2,\cdots,2a_{p_1}-2a_{p_2}+2a_{p_3}-a_n \right\}$

以此类推，每次操作可以将 $a_1$ 加/减 $2a_{p_i}-2a_1$。

$w_i=2a_i-2a_1$

$a'_1=a_1+\sum \mu_iw_i(\mu_i\in\N)$

根据裴蜀定理，$\sum\mu_iw_i = \left\{ x| x=k\gcd w_i,k\in\N \right\}$。

$a_{1\min}=a_1 \bmod \gcd w_i$

用同样的方法可以得到 $a_{n\min}$。

因为一次操作会翻转整个序列的大小关系，所以 $\min(a)=\min(a_1,a_n)$。

根据 $\max(a)=\min(a)+d$ 可以得到答案。

### 代码
```cpp
#include<bits/stdc++.h>
//#define int long long
//#define mod 1000000007
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
using namespace std;
typedef pair<int,int> pii;
void setIn(string s){freopen(s.c_str(),"r",stdin);}
void setOu(string s){freopen(s.c_str(),"w",stdout);}
void setIO(string s){setIn(s+".in"),setOu(s+".out");}
template<class T>void chkmax(T &a,T b){a=max(a,b);}
template<class T>void chkmin(T &a,T b){a=min(a,b);}
template<class T>T read(T &x)
{
	x=0;T f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*=f;
}
template<class T,class ...L>void read(T &x,L &...l){read(x),read(l...);}
template<class T>void write(T x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9){write(x/10);}putchar(x%10+'0');
}
template<class T>void write(T x,char c){write(x),putchar(c);}
int n,a[200005],g,ans=0x3f3f3f3f;
signed main()
{
	read(n);
	rep(i,1,n)read(a[i]);

	g=0;
	rep(i,1,n)g=__gcd(g,2*a[i]-2*a[1]);
	chkmin(ans,a[1]%g+a[n]-a[1]);

	g=0;
	rep(i,1,n)g=__gcd(g,2*a[n]-2*a[i]);
	chkmin(ans,a[n]%g+a[n]-a[1]);

	write(ans);
}
```

---


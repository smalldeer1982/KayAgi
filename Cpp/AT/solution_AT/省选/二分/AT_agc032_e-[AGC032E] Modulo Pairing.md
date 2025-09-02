# [AGC032E] Modulo Pairing

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc032/tasks/agc032_e

$ M $ を正整数とします。

$ 2\ N $ 個の整数 $ a_1,\ a_2,\ \ldots,\ a_{2\ N} $ が与えられます。 ここで、各 $ i $ について $ 0\ \leq\ a_i\ <\ M $ です。

$ 2\ N $ 個の整数を $ N $ 組のペアに分けることを考えます。 このとき、各整数はちょうど $ 1 $ つのペアに属さなければなりません。

ペア $ (x,\ y) $ の *醜さ* を $ (x\ +\ y)\ \mod\ M $ と定義します。 $ N $ 組のペアの醜さの最大値を $ Z $ としたとき、$ Z $ の最小値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^9 $
- $ 0\ \leq\ a_i\ <\ M $

### Sample Explanation 1

例えば、$ (0,\ 5),\ (2,\ 3),\ (4,\ 9) $ とペアを作ればよいです。 このとき、ペアの醜さはそれぞれ $ 5,\ 5,\ 3 $ となります。

### Sample Explanation 2

$ (1,\ 9),\ (1,\ 9) $ とペアを作ればよいです。 このとき、ペアの醜さはともに $ 0 $ です。

## 样例 #1

### 输入

```
3 10
0 2 3 4 5 9```

### 输出

```
5```

## 样例 #2

### 输入

```
2 10
1 9 1 9```

### 输出

```
0```

# 题解

## 作者：小粉兔 (赞：37)

先把 $a$ 从小到大排序，对于每一对 $(i, j)$，把 $i, j$ 用一条线连起来。

如果 $a_i + a_j < M$，则用蓝色线，如果 $a_i + a_j \ge M$，则用红色线。

那么我们可以证明，一定存在一种最优情况，满足：

- 存在一个分界点，使得它左右两侧没有匹配，也就是没有连线经过分界点。
- 只考虑分界点左侧，则最小的数和最大的数连线，第二小的数和第二大的数连线，以此类推。
- 分界点右侧也是一样，最小的和最大的连线。
- 分界点左侧的线的颜色都是蓝色，分界点右侧的线的颜色都是红色。

用图表示就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/u0ff2q88.png)

怎么证明它是对的呢？可以使用调整法。

考虑两个数对，如果它们同色但不包含，或者它们异色但不相离，则可以调整成满足条件且不更劣的情况。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/s6ozmx7t.png)

令四个数从左到右为 $a, b, c, d$，注意到 $a \le b \le c \le d$。

以及两个不等式：对于 $x, y$（$x \le y$），它们之间的线的权值 $w$ 满足：  
如果线是蓝色的，则 $w \ge y$；如果线是红色的，则 $w < x$。

反复使用这些不等式，即可得出调整后的情况不会更劣的结论。以右侧第三种情况为例：

- 令线 $a \sim d$ 的权值为 $x$，线 $b \sim c$ 的权值为 $y$。
- 因为 $y \ge c \ge a > x$，所以这种情况的权值较大值为 $y$。
- 考虑调整后的情况，因为线 $b \sim c$ 变成了 $b \sim a$，而 $a \le c$，所以线还是蓝色的。
- 因为线 $d \sim a$ 变成了 $d \sim c$，而 $c \ge a$，所以线还是红色的。
- 接下来证明权值较大值不会变得更大：
- 考虑线 $a \sim b$，其权值为 $a + b \le b + c = y$。
- 考虑线 $c \sim d$，其权值为 $c + d - M < c \le b + c = y$。
- 所以权值都不会变得更大，证毕。

其他情况的证明类似。

那么得到了这个结论后，如何计算答案呢？如果枚举分界点，然后计算答案是 $\mathcal O (N^2)$ 的，不能接受。

我们弱化一下条件：每条线 $x \sim y$ 都可以染蓝色，权值为 $x + y$，但是要染红色时必须有 $x + y \ge M$。

则可以发现：在满足条件的情况下，分界点越往左，答案越优，但是如果太往左了，就会导致分界点右侧不满足条件。

那么我们二分一下这个分界点即可。

时间复杂度为 $\mathcal O (N \log N)$，[评测链接](https://atcoder.jp/contests/agc032/submissions/10547824)。

---

## 作者：OIer_ljb (赞：10)

~~NOIP 模拟赛 T1 ，场切 *3400 祭~~

做法不算排序复杂度 $O(n)$，~~但是懒得写基排~~。

首先我们发现一对权值 $(x,y)$ 合并后新的权值有两种情况： $x+y$ 或者 $x+y-M$，如果是后面一种需要满足 $x+y>M$。

然后我们考虑，假如我们已经知道了答案，那么所有比答案大的权值 $x$ 必然被合并到某对 $(x,y)$ 使得新的权值为 $x+y-M$，那么排序后这些 $x$ 在 $a$ 序列中是一个后缀。

于是我们考虑把 $a_i-M$ 也加入 $a$ 序列然后排序，这样有什么用处呢？

我们发现这个新的序列任何一个长度为 $n$ 的连续子序列都包含了原序列的所有数，其中为负数的值表示你这个值需要匹配之后新的权值 $>M$。

于是我们在新序列上枚举左端点，那么对于这个新的子序列，它的最优答案显然是从两端向中间匹配（因为你不用像官方题解那样考虑取模之后变小的情况），当然，如果你匹配的时候出现了负数值，那么,相当于说明你这一对匹配的权值和 $<M$，这个匹配显然是不行的。

于是你 $O(n^2)$ 做完了，然后考虑优化，发现这个子序列左端点越左越好，问题就是如何找到最左的左端点。

我赛时想到一个感觉很神仙的做法：

考虑从中间往两边扩展，初始 `l=mid,r=mid+1`，每次扩展就是 `l--,r++`。对于当前的一对 $(l,r)$，如果 $a_l+a_r<0$，那么 `l++,r++`，这样显然是可行的。

证明：考虑归纳证明，初始情况时，$a_l$ 是负数，$a_r$ 和 $a_{r+1}$ 都不是负数，那么显然可行。

当 $(l,r)$ 满足条件时，考虑 $(l-1,r+1)$，由于 $a_l+a_r\ge0$，那么 $a_l+a_{r+2}\ge 0$，内部的其他点也同理，所以 $(l,r+2)$ 一定是一个合法匹配，所以得证！

然后直接做就行了，复杂度 $O(n\log n)$。

代码贼短。

```C++
#include<bits/stdc++.h>
#define usefile(p) freopen(#p".in","r",stdin),freopen(#p".out","w",stdout);
#define fo(i,a,b) for(int i=(a);i<=(b);++i)
#define fu(i,a,b) for(int i=(a);i<(b);++i)
#define fd(i,a,b) for(int i=(a);i>=(b);--i)
#define pb push_back
#define ll long long
using namespace std;
const int N=2e5+5;
int n,m,a[N<<1],k;
int main()
{
	scanf("%d%d",&n,&m);int nn=n<<1;k=nn<<1;
	fo(i,1,nn)scanf("%d",&a[i]),a[i+nn]=a[i]-m;
	sort(a+1,a+k+1);
	int anss=0;
	int l=nn+1,r=nn;
	while(r-l+1<nn)
	{
		--l;++r;
		if(a[l]+a[r]<0)++l,++r;
	}
	while(l<=r)anss=max(anss,a[l]+a[r]),++l,--r;
	printf("%d",anss);
	return 0;
}
```

---

## 作者：Thaumaturge (赞：7)

并不会做 $D$，但是会做 $E$。（

首先看到最小可以考虑二分答案，获得每个数可以与之匹配的其他数，跑一般图最大匹配，就获得了一个 $O(n^3\log n)$ 的优秀做法。

但这对正解并没有什么帮助。

从一个更简单的模型开始考虑：令 $M$ 无穷大，答案将会是怎样的。

显然是贪心地将 $a_i$ 与 $a_{2n-i+1}$ 进行配对。

但是带上了 $M$ 后，就可能因为某些配对的权值变小了而导致答案发生变化。那我们来观察一下具体会怎样变化。

先将原序列从小到大排个序。

对于两个配对 $(a_1,a_2),(a_3,a_4)$，假设 $a_1<a_2<a_3<a_4$，可以推出几个结论：

①$\max(a_2+a_3,a_1+a_4) \leq \max(a_1+a_3,a_2+a_4)$

这也是第一个贪心成立的原因，并且说明：将权值没有减去 $M$ 的配对提出来，一定形如一个括号嵌套，否则不优。

②$\max(a_2+a_3-M,a_1+a_4-M)\leq \max(a_1+a_3-M,a_2+a_4-M)$（废话）

但这能说明权值减去了 $M$ 的配对同样会形成括号嵌套。

接下来的结论比较重要：

③$\max(a_3+a_4-M,a_1+a_2)\leq \max(a_2+a_4-M,a_1+a_3)\leq max(a_1+a_4-M,a_2+a_3)$

④$\max(a_3+a_4-M,a_1+a_2)\leq \max(a_2+a_3-M,a_1+a_4)\leq \max(a_2+a_4,a_1+a_3-M) \leq  \max(a_3+a_4,a_1+a_2-M)$

这是因为 $a_i-M<0$。可以将括号中任意 $a_i-M$ 的一项消去后比较大小

然后就可以用 $\max$ 里不带 $M$ 的项和别的项比大小了。

这说明的是：一个减去 $M$ 的配对，无论是与不减去 $M$ 的交叉，包含，被包含，还是在其前方，都是不优的。

这样我们大概就知道一个最优的配对长啥样了：存在一个分界线，将减去 $M$ 与不减 $M$ 的配对划分开来，且这两种配对都形如括号嵌套。

显然我们希望减去 $M$ 的配对越多越好，也即最小化分界线位置。那我们对每个数， check 一下他的合法分界线能到的最左边的位置，取个 $\max$ 就求出了分界线。

$O(n\log n)$，基排+单调性可以做到$O(n)$。

```cpp
/*************************************************************************
	> File Name: AGC032E.cpp
	> Author: The-Out-Land
	> Mail: 2264454706@qq.com 
	> Created Time: 2021年01月20日 星期三 20时37分48秒
 ************************************************************************/

#include <bits/stdc++.h>

#define enter putchar('\n')
#define space putchar(' ')
#define re register
#define N 300010

using namespace std;

inline int max(int x,int y){return (x>y?x:y);}

inline int min(int x,int y){return (x<y?x:y);}

int mod;

inline int read(){
	int x=0;char c=getchar();bool y=1;
	for(;c<'0' || c>'9';c=getchar()) if(c=='-') y=0;
	for(;c>='0' && c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	if(y) return x;
	return -x;
}

int n,a[N],tar[N],cs,fans;

inline int add(int x){if(x<0) return x+mod;return (x>=mod?x-mod:x);}

inline void Input(){
	n=read();mod=read();
	n<<=1;
	fans=0;
	for(re int i=1;i<=n;++i) a[i]=read();
	return;
}

inline void solve(){
	sort(a+1,a+n+1);
	cs=0;
	for(re int i=1;i<=n;++i) tar[i]=lower_bound(a+1,a+n+1,mod-a[i])-a,cs=max(cs,tar[i]-n+i);
	if(!(cs&1)) ++cs;
	cs=min(cs,n+1);
	for(re int i=1;i<cs;++i) fans=max(fans,add(a[i]+a[cs-i]));
	for(re int i=cs;i<=n;++i)fans=max(fans,add(a[i]+a[n+cs-i]));
	cout<<fans<<endl;
	return;
}

int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	Input();
	solve();
	return 0;
}
```



---

## 作者：louhao088 (赞：7)

水黑。

如果没有模数，那么很自然贪心策略是最大的加最小的，次大加次小，一直下去。

有了模数，我们很自然发现，将这个数列排序后，它一定会分成两段，一段相加不超过模数，一段相加超过模数，而且两段之间一定是最大加最小，这样一定不会使答案变劣。而且如果两个点都能满足这个性质一定要把这个点放向越左边越好，这样肯定比在右边优。

有了这些性质，我们就可以二分找这个分割点。

时间复杂度 $O(n \log n)$ 。


------------
代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define re register
const int maxn=2e5+5;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,ans,a[maxn];
bool check(int x)
{
	int res=0;
	for(int i=1;i<=x;i++)
	{
		if(a[i]+a[x-i+1]>=m)return 1;
		res=max(a[i]+a[x-i+1],res);
	}
	for(int i=x+1;i<=2*n;i++)
	{
		if(a[i]+a[2*n-i+x+1]<m)return 0;
		res=max(res,a[i]+a[2*n-i+x+1]-m);
	}
	ans=min(ans,res);return 1;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();ans=m-1;
	for(int i=1;i<=2*n;i++)a[i]=read();
	sort(a+1,a+2*n+1);
	int l=0,r=n;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(check(2*mid))r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
 	return 0;
}

```



---

## 作者：ty_mxzhn (赞：6)

好题！

套路的考虑排序后画出连线，则发现不劣的匹配一定形如如下形式：（蓝色是 $<m$，红色是 $\ge m$）

![](https://cdn.luogu.com.cn/upload/image_hosting/u0ff2q88.png)

（这个图是贺的）

证明考虑调整法。具体的，枚举四个点之间的匹配方式，则最后的不劣形式一定形如前两个匹配蓝后两个匹配红，或者嵌套着匹配同色对。此处不再赘述。

考虑枚举分界点，则复杂度为 $O(n^2)$，过不去。

如何优化？考虑蓝其实不用满足 $x+y<m$，反正这样答案变大又不是变小。

所以我们尽量靠左，但是右边的红还是有限制的。连续的限制考虑二分，则此题得解。

---

## 作者：ModestCoder_ (赞：5)

首先想到的当然是二分答案+贪心

但是正解二分的并不是答案

**结论：最终的正确答案一定存在一个分界点，满足**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201101111041836.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70#pic_center)
蓝线表示$x+y<M$
红线表示$x+y>=M$

给出证明

情况1：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201101111544643.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70#pic_center)

任意两个数加起来都$<M$的情况，Ⅰ最优

令从左到右分别为$a<b<c<d$

计算出三种方案的价值

Ⅰ:$max(a+d,b+c)$

Ⅱ:$max(a+b,c+d)=c+d>a+d,b+c,即Ⅱ>Ⅰ$

Ⅲ:$max(a+c,b+d)=b+d>a+d,b+c,即Ⅲ>Ⅰ$

证毕

情况2：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201101112009497.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70#pic_center)任意两个数加起来都$>=M$的情况，Ⅰ最优

在证明之前先要发现，因为每个数$<M$

所以对于任意$x+y>=M,x+y-M<min(x,y)$

Ⅰ:$max(a+d,b+c)-M$

Ⅱ:$max(a+b,c+d)-M$

Ⅲ:$max(a+c,b+d)-M$

其实变成了情况1的证明

情况3：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201101112320242.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70#pic_center)
Ⅰ:$max(a+d-M,b+c)=b+c$
Ⅱ:$max(a+b,c+d-M)=max(a+b,e)(e为<c的一个数)$
Ⅱ$<$Ⅰ

情况4：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201101112551980.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70#pic_center)
Ⅰ:$max(b+d-M,a+c)=a+c$

Ⅱ:$max(a+b,c+d-M)=max(a+b,e)(e为小于c的一个数)$

Ⅱ$<$Ⅰ

情况5：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020110111272250.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70#pic_center)
Ⅰ:$max(b+c-M,a+d)=a+d$

Ⅱ:$max(a+b,c+d-M)=max(a+b,e)(e为<c的一个数)$

Ⅱ$<$Ⅰ

所有情况都罗列了

结论就证明好了

所以正确答案一定满足最开始说的那种情况，分界点左边全是蓝线，最大最小相连，次大次小相连……，右边全是红线，最大最小相连，次大次小相连……

然后分界点是越小越好，合法的分界点越小，左右两边的权值越小，同时的左边越可能满足蓝线

所以答案就一定是合法的最小的分界点

二分分界点，找到最小的就行了

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 200010
using namespace std;
int a[maxn], n, m;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

bool check(int mid){
	for (int i = mid + 1, j = n; i <= j; ++i, --j) if (a[i] + a[j] < m) return 0;
	return 1;
}

int main(){
	n = read() << 1, m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	sort(a + 1, a + 1 + n);
	int l = 0, r = n >> 1, ans = 0;
	while (l <= r){
		int mid = (l + r) >> 1;
		if (check(mid << 1)) ans = mid << 1, r = mid - 1; else l = mid + 1;
	}
	int sum = 0;
	for (int i = 1, j = ans; i <= j; ++i, --j) sum = max(sum, a[i] + a[j]);
	for (int i = ans + 1, j = n; i <= j; ++i, --j) sum = max(sum, a[i] + a[j] - m);
	printf("%d\n", sum);
	return 0;
}
```





---

## 作者：pufanyi (赞：5)

我们首先我们有：
$$
(x+y)\bmod m=\begin{cases}
x+y&x+y\le m\\
x+y-m&x+y>m
\end{cases}
$$

接下来我们看几种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/0he3y4vz.png)

如果我们有 $x_1\le x_2\le x_3\le x_4$，那么我们有这样 $4$ 中情况：

第一种，$x_3+x_4<m$，那显然 $(x_1,x_4),(x_2,x_3)$ 更优。

第二种，$x_1+x_2\ge m$，和第一种一样。

第三种，$\begin{cases}x_1+x_3<m\\x_2+x_4\ge m\end{cases}$，考虑到 $x_2+x_4-m<x_2$，故有 $\max\{x_1+x_3,x_2+x_4-m\}=x_1+x_3$，而考虑到 $\begin{cases}x_1+x_2\le x_1+x_3\\x_3+x_4-m<x_3\end{cases}$，故有 $\max\{x_1+x_3,x_2+x_4-m\}\ge \max\{x_1+x_2,x_3+x_4-m\}$。所以 $(x_1,x_2),(x_3,x_4)$ 一定比 $(x_1,x_3),(x_2,x_4)$ 优。

我们再来看 $(x_1,x_4),(x_2,x_3)$ 的情况。如果有 $\begin{cases}x_1+x_4\ge m\\x_2+x_3\ge m\end{cases}$，那就有 $\begin{cases}x_1+x_4-m<x1\\x_2+x_3-m<x_2\end{cases}$，所以 $\max\{x_1+x_4-m,x_2+x_3-m\}<x_2\le \max\{x_1+x_2,x_3+x_4-m\}$，此时 $(x_1,x_4),(x_2,x_3)$ 的方案更优。但是如果有 $x_1+x_4\le m$ 或是 $x_2+x_3\le m$，则答案将会更大。

第四种，$\begin{cases}x_1+x_4<m\\x_2+x_3<m\\x_3+x_6\ge m\\x_4+x_5\ge m\end{cases}$。根据前面的讨论，我们仅需比较 $(x_1,x_4),(x_2,x_3),(x_5,x_6)$ 和 $(x_1,x_2),(x_3,x_4),(x_5,x_6)$ 即可，不难发现 $\begin{cases}x_1+x_2\le x_1+x_4\\x_3+x_6-m<x_3\le x_2+x_3\\x_4+x_5-m\le x_5+x_6-m\end{cases}$，于是 $\max\{x_1+x_2,x_3+x_6-m,x_4+x_5-m\}\le \max\{x_1+x_4,x_2+x_3,x_5+x_6-m\}$。

根据第一、二、三种情况，我们发现，最终的划分结果肯定是被分成两部分，左边部分最小的匹配，次大的和次小的匹配……右边也这样匹配。其中左边所有的匹配 $(x,y)$ 都有 $x+y<m$，右边的匹配 $(x,y)$ 都有 $x+y\ge m$。

根据第四种情况，我们可以发现蓝色的匹配数越多越好，于是我们考虑二分蓝色的匹配数量，最终确定答案。



---

## 作者：TH911 (赞：3)

> [题目传送门](https://www.luogu.com.cn/problem/AT_agc032_e)
>
> [个人Blog同步链接](https://cfyy.us.kg/2024/11/20/1/)

## 题意分析

***证明参见”相关证明“部分。***

给定 $n,m$ 和 $2n$ 个正整数 $a_1,a_2,a_3,\cdots,a_{2n}$，将其分为 $n$ 对，两两组成一队。若 $x,y$ 为一对，则其权值为 $(x+y)\bmod m$。

如果没有 $\bmod m$ 这一个条件，那么其实很简单，将 $a_1\sim a_{2n}$ 排序后”最大值与最小值相加求最大和“即可。

**但是这里需要取模**。

考虑到 $0\leq a_i<m$，那么就有 $0\leq x+y<2m$。因此，每一对 $(x,y)$ 的权值 $(x+y)\bmod m$ 仅仅有两种可能：$x+y$ 和 $x+y-m$。

那思路就很明显了，我们要想使权值和的最大值最小，那么就让每一对 $(x,y)$ 的权值尽可能平均。

但这如何实现呢？

将 $a_1\sim a_{2n}$ 排序后，我们一定可以找到一个位置 $p$，使得 $[1,p]$ 存在配对方案使得所有配对 $(a_i,a_j)$ 满足 $a_i+a_j<m$， $[p+1,2n]$ 存在配对方案使得所有配对 $(a_i,a_j)$ 满足 $a_i+a_j\geq m$。

然后将这两段分别进行“最大值与最小值相加”即可求得最大最小权值，答案即 ：

$$
\large \max\left(\max\limits_{i=1}^{\left\lfloor\frac p2\right\rfloor}(a_i+a_{p-i+1}),\max\limits_{i=p+1}^{\left\lfloor\frac {2n+p}2\right\rfloor}(a_i+a_{2n-i+1}-m)\right)
$$

## 相关证明

### 约定

$a_1,a_2,a_3,\cdots,a_{2n}$ 均已排序，且单调不降。

对于配对 $(a_i,a_j)$，若 $a_i+a_j<m$，记 $(a_i,a_j)$ 为 $x$ 型配对；若 $a_i+a_j\geq m$，记 $(a_i,a_j)$ 为 $y$ 型配对。

记 $a[l,r]$ 为序列 $a_l,a_{l+1},a_{l+2},\cdots,a_{r-1},a_r$。

**$a[1,p],a[p+1,2n]$ 均有可能不存在，以下暂不考虑此情况，参见引理 $5$**。

### 引理 $1$

引理 $1$：$y$ 型配对越多越好，即 $p$ 越小越好。

考虑到对于所有 $y$ 型配对 $(a_i,a_j)$，其权值均为 $a_i+a_j-m$。

又因为要求最大值最小，所以使 $a_i+a_j$ 尽可能平均，使得**能够组成的 $y$ 型配对都组成 $y$ 型配对**，以此实现尽可能平均的目的。

***

### 引理 $2$

引理 $2$：一定存在整数 $p\in[1,2n]$ 使得序列 $a$ 分为两段 $a[1,p],a[p+1,2n]$，其中 $a[1,p]$ 只存在 $x$ 型配对，$a[p+1,2n]$ 只存在 $y$ 型配对。

证明：

我们不妨从 $(a_i,a_j)$ 的角度来思考。

若 $a_i+a_j<m$，我们记 $(a_i,a_j)$ 为 $x$ 型配对；若 $a_i+a_j\geq m$，我们记 $(a_i,a_j)$ 为 $y$ 型配对。

那么便转化为：找到 $p$，使 $[1,p]$ 均为 $x$ 型配对，$[p+1,2n]$ 均为 $y$ 型配对。

考虑到一个事实：若 $(a_i,a_j)$ 为一对，则 $a_i+a_j$ 的值不会因为 $a_i,a_j$ 的位置改变而改变。

因此更改顺序不影响答案。

那么我们就可以将所有 $x$ 型配对放至 $[1,p]$，将所有 $y$ 型配对放至 $[p+1,2n]$。

即：存在整数 $p\in[1,2n]$ 使得序列 $a$ 分为 $a[1,p],a[p+1,2n]$ 且满足 $a[1,p]$ 可被划分为 $\dfrac p2$ 个 $x$ 型配对，$a[p+1,2n]$ 可被划分为 $\dfrac {2n-p}{2}$ 个 $y$ 型配对。

***

### 引理 $3$

引理 $3$：最终答案为 $\large \max\left(\max\limits_{i=1}^{\left\lfloor\frac p2\right\rfloor}(a_i+a_{p-i+1}),\max\limits_{i=p+1}^{\left\lfloor\frac {2n+p}2\right\rfloor}(a_i+a_{2n-i+1}-m)\right)$。

证明：

因为要求最大值尽可能的小，因此使和的值尽可能平均。即对于两段都采取”最大值与最小值配对“的方案。

故，正确性得证。

***

### 引理 $4$

引理 $4$：存在整数 $p$，使得 $a[1,p]$ 均为 $x$ 型配对，$a[p+1,2n]$ 均为 $y$ 型配对且**无需改变 $a$ 的元素顺序**。

证明：

由引理 $2$，一定能够将 $a$ 划分为 $a[1,p],a[p+1,2n]$。

考虑到 $a$ 单调不降。

因此我们可以 $n\sim1$ 尝试 $p$ 值，结合引理 $1$，最后一个成立的 $p$ 即为最终 $p$，且满足本引理。

***

### 引理 $5$

引理 $5$：当 $a[1,p]$ 或 $a[p+1,2n]$ 不存在时，答案仍然正确。

1. $a[1,p]$ 不存在。

   即不存在 $x$ 型配对，答案显然正确。

2. $a[p+1,2n]$ 不存在。

   即不存在 $y$ 型配对，答案显然正确。

***

### 引理 $6$

引理 $6$：$p$ 可以二分求得。

**需要注意的是，我们是在 $p$ 可以更小的时候尝试让 $p$ 更小。**

由于我们对 $a$ 进行了排序，因此 $a$ 具有单调性。

结合引理 $1$，本引理得证。

***

### 最终结论

（具体请参见代码注释）

结合引理 $1\sim6$，可得出以下最终结论。

对 $a$ 排序以后二分 $p$ 值直到 $p$ 不满足 $a[1,p],a[p+1,2n]$ 的定义即可。

最终答案即（$p'$ 代表最后一个合法 $p$ 值）：

$$
\large \max\left(\max\limits_{i=1}^{\left\lfloor\frac {p'}2\right\rfloor}(a_i+a_{p'-i+1}),\max\limits_{i=p'+1}^{\left\lfloor\frac {2n+p'}2\right\rfloor}(a_i+a_{2n-i+1}-m)\right)
$$

## AC 代码

```cpp
//#include<bits/stdc++.h>
#include<algorithm> 
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<string>
#include<vector>
#include<cmath>
#include<ctime>
#include<deque>
#include<queue>
#include<stack>
#include<list>
using namespace std;
const int N=1e5;
int n,m,ans=2147483647,a[(N<<1)+1];
//check:是否可以使p更小
bool check(int x){//就用x代替p吧......
	x=(x<<1);
	int pl=0;
	for(int i=1;i<=x;i++){
		if(a[i]+a[x-i+1]>=m)return true;//a[1,p]依然存在x型配对
		pl=max(pl,a[i]+a[x-i+1]);
	}
	for(int i=x+1;i<=(n<<1);i++){
		if(a[i]+a[(n<<1)-i+x+1]<m)return false;//已经不满足y型配对的定义
		pl=max(pl,a[i]+a[(n<<1)-i+x+1]-m);
	}ans=min(ans,pl);
	return true;
}
int main(){
	/*freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);*/
	
	scanf("%d %d",&n,&m);
	for(int i=1;i<=(n<<1);i++)scanf("%d",a+i);
	sort(a+1,a+(n<<1)+1);
	int l=0,r=n;//注意是二分[0,n],需要考虑不存在的情况
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))r=mid-1;
		else l=mid+1;
	}printf("%d\n",ans);
 	
	/*fclose(stdin);
	fclose(stdout);*/
	return 0;
}
```

---

## 作者：_Cheems (赞：3)

记 $(a,b)$ 表示 $(a+b)\bmod m$。

首先让 $a_i$ 从小到大排，假如没有取模就是让第 $i$ 大和第 $i$ 小这样搭配。

那么加上取模，因为 $\forall a_i <m$，所以有个小性质：$a_i+a_j-m< a_i,a_j$。

回顾一开始的贪心策略我们是怎么证明的，是对 $a\le b\le c\le d$ 进行讨论，本题也可以这样试试：

经过尝试发现，$(a,c),(b,d)$ 是无论如何都不优的。

证明：

* 若 $a+c\ge m$：数对同时减 $m$ 直接比较就好，那么 $(a,d)\le (b,d)$，$(b,c)\le (a,c)$，调整后不劣。

* 反之，若 $b+d<m$：同上，$(a,c),(b,d),(a,d),(b,c)<m$，所以调整后不劣。 

* 反之：则 $(b,d)<b\le a+c=(a,c)$，那么其最值被 $(a,c)=a+c$ 取到。同理，对于方案 $(a,b),(c,d)$，其最值被 $(a,b)=a+b$ 取到。显然 $(a,b)\le (a,c)$，所以调整后不劣。

综上，所有数对只能有包含关系，不能交叉。

（蒟蒻做到这就不会推了 qwq。）

然后发现，$\max((a,d),(b,c))\le \max((a,b),(c,d))$ 在绝大多数情况下都满足。具体而言，只要所有数对同时 $<m$ 或 $\ge m$ 即可（即同时减去一个值）。

对其余情况（减去的数不同）讨论：

若 $a+d\ge m,b+c<m$，那么 $\max((a,d),(b,c))=b+c$，$\max((a,b),(c,d))=a+b$，拆开更优。另一种情况同理。

结合以上讨论，若存在两个数对减去的数不一样，那么它们不可能包含；若相等，则必然包含。

于是，必然存在一种最优划分可以找到一个分界点，拆分为两区间，满足左边数对都 $<m$，右边都 $\ge m$，且同一区间内都是最大最小两两相配的。

暴力枚举是平方的，怎么优化？放开限制，允许 $(a,b)$ 只在 $a+b\ge m$ 时减去 $m$。令右边都减去 $m$，容易发现，右边越大越优，但是太大了就会非法。

二分计算即可，复杂度 $O(n\log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;

#define pir pair<int, int>
const int N = 2e5 + 5, inf = 2e9 + 5;
int n, mod, a[N];

inline pir calc(int l, int r){
	pir p = {inf, 0}; //max初值不要设成-2e9，后面又减了1e9会爆int 
	for(int i = l, j = r; i < j; ++i, --j) 
		p.first = min(p.first, a[i] + a[j]), p.second = max(p.second, a[i] + a[j]);
	return p;
}
signed main(){
	cin >> n >> mod;
	for(int i = 1; i <= n << 1; ++i) scanf("%d", &a[i]);
	sort(a + 1, a + 1 + (n << 1));
	int l = 0, r = n + 1, mid;
	while(l + 1 < r){
		mid = (l + r) >> 1;
		if(calc(2 * mid - 1, n << 1).first >= mod) r = mid;
		else l = mid; 
	}	
	r = 2 * r - 1;
	cout << max(calc(1, r - 1).second, calc(r, n << 1).second - mod);
	return 0;
}
```

---

## 作者：约瑟夫用脑玩 (赞：3)

看到没人丢 $O(n)$ 的，我来写一发偏理解性的题解，~~真实模拟凡人做题的全过程~~。

首先不考虑 $\bmod M$ 的情况，有一个众所周知的结论是将 $a$ 排序，匹配 $(a_1,a_{2N}),(a_2,a_{2N-1}),\dots$，即匹配 $(a_i,a_{2N+1-i})$ 最优。

贺张图表示就是：![](https://cdn.luogu.com.cn/upload/image_hosting/jz2sdtt8.png)

现在考虑一些数加起来过后会减去一个 $M$，我们称较大数和较小数匹配中较大数为右端点，较小数为左端点。

我们肯定贪心地希望把**尽可能多**的右端点取最大的点匹配一些左端点来减去 $M$，剩下的数实在减不了 $M$ 就再按上面的策略匹配。

为了使减去 $M$ 的匹配尽可能多，我们让最大的数匹配一个最小且和 $\ge M$ 的数，将它们俩删去进行后面的匹配。

画张图就是：![](https://cdn.luogu.com.cn/upload/image_hosting/cumj84iy.png)

(红色点表示和 $\ge M$ 的匹配的端点，中间的黑色点表示可能省略了一些点)

~~虽然能过一半以上的点但你连样例 1 都过不了~~，问题出在哪里？我们选择的左端点离右端点太远了导致中间一些点增大了最后匹配时的贡献，手玩一下发现选择左端点和右端点贴着一定更优，于是我们就将它们贴在一起。

贺张图表示就是：![](https://cdn.luogu.com.cn/upload/image_hosting/u0ff2q88.png)

~~点开题解发现正解就是这样~~，严谨证明可以参考其他题解。

然后我们要找到尽可能多的匹配能减去 $M$，由于这些匹配都是贴在一起的，一种方便的实现是找到这些匹配的中点位置，或者说找到匹配的下标和是多少。

即：![](https://cdn.luogu.com.cn/upload/image_hosting/zsxrfoxd.png)

找图中的 $i+j$ 应该等于多少。

显然 $i+j$ 越小最后选到的点越多，对于每个右端点确定最小的左端点后能确定最小的 $i+j$ 能取到这个匹配，都能取到就取所有中的最大，具体可看代码。

然后初始的排序上个基排，时间复杂度 $O(n)$。

代码：

```
int B[Mx+5];
inline void Sort(int *A,int n)
{
	register int *i,j,sa[256]={0},sb[256]={0},sc[256]={0},sd[256]={0};
	for(i=A+n;i!=A;i--)sa[(*i)&255]++,sb[((*i)>>8)&255]++,sc[((*i)>>16)&255]++,sd[((*i)>>24)&255]++;
	for(j=1;j<256;j++)sa[j]+=sa[j-1],sb[j]+=sb[j-1],sc[j]+=sc[j-1],sd[j]+=sd[j-1];
	for(i=A+n;i!=A;i--)B[sa[(*i)&255]--]=*i;
	for(i=B+n;i!=B;i--)A[sb[((*i)>>8)&255]--]=*i;
	for(i=A+n;i!=A;i--)B[sc[((*i)>>16)&255]--]=*i;
	for(i=B+n;i!=B;i--)A[sd[((*i)>>24)&255]--]=*i;
}
int n,M,a[Mx+5],vst[Mx+5];
signed main()
{
	#ifndef ONLINE_JUDGE
	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	#endif
	int i,j,mx=0,mxp=0;
	n=read()<<1;M=read();
	for(i=1;i<=n;a[i++]=read());
	Sort(a,n);
	for(i=n,j=1;i;i--)
	{
		for(;j<=n&&a[j]+a[i]<M;j++);
		ckmx(mxp,j-(n-i));//算的其实是第一个和≥M的匹配的左端点
	}mxp|=1;
	for(i=1;i<(j=mxp-i);i++)ckmx(mx,a[i]+a[j]);
	for(i=mxp;i<(j=n+mxp-i);i++)ckmx(mx,a[i]+a[j]-M);
	writenum(mx,10);return output;
}
```

---

## 作者：OrinLoong (赞：1)

原题链接：[洛谷传送门](https://www.luogu.com.cn/problem/AT_agc032_e)  
在博客园中阅读：[传送门](https://www.cnblogs.com/OrinLoong/p/18662113)
### 前言
这大概率是本题所有题解笔记里面推导过程最为详细的一篇。纵然此题代码简单且感性理解不难，然而若是想提升自己的数学逻辑推导能力，那么不妨跟着这篇题解推理一遍本题的所有结论。

### 题意简述
给定 $2\times N$ 个整数 $a_i$，满足 $0\le a_i<M$。需要把这些整数分成 $N$ 对，每一对 $(x,y)$ 的权值为 $(x+y)\bmod M$。我们定义，一种分配方案的权值为所有整数对权值中的最大值。求分配方案权值的最小可能值。

$N\le 10^5,M\le 10^9$。

### 解决方案
不妨先考虑没有取模操作时的情况。显然我们先排个序，让最大的和最小的一对，次大的和次小的一对，依此类推，这样如括号嵌套的方案是最优的。也即 $\forall a_1\le a_2\le a_3\le a_4$，$(a_1,a_4)$ 一组，$(a_2,a_3)$ 一组最优。

> 记 $(a_1,a_4)$ 权值为 $p$，$(a_2,a_3)$ 权值记为 $q$。
>
> 首先，$(a_1,a_2)$ 一组，$(a_3,a_4)$ 一组显然不优。  
> 接下来，$(a_1,a_3)$ 一组（其权值记为 $p'$），$(a_2,a_4)$ 一组（其权值记为 $q'$）显然也不优：
> 1. 若 $p\ge q$，则 $q'=p+(a_2-a_1)\ge p$，不优。
> 2. 若 $p\le q$，则 $q'=q+(a_4-a_3)\ge q$，不优。
>
> 综上证毕。

啊但是现在加入了取模操作，怎么办呢？

首先我们发现，仍然有 $\max((a_1+a_4-M),(a_2+a_3-M))\le\max((a_1+a_3-M),(a_2+a_4-M))\le\max((a_1+a_2-M),(a_3+a_4-M))$。

> 不等式两边同增同减。显然。

这说明对于最终被取模的数对中的数，最优的方案也是如括号嵌套的。

接下来我们推导出：$\max((a_3+a_4-M),(a_1+a_2))\le\max((a_2+a_4-M),(a_1+a_3))\le\max((a_1+a_4-M),(a_2+a_3))$。

> 显然有 $a_i-M<0$。  
> $\because a_1+a_2\le a_1+a_3,a_3+(a_4-M)<a_3+a_1$  
> $\therefore \max((a_3+a_4-M),(a_1+a_2))\le\max((a_2+a_4-M),(a_1+a_3))$  
> $\because a_2+(a_4-M)\le a_2+a_3,a_1+a_3\le a_2+a_3$  
> $\therefore \max((a_2+a_4-M),(a_1+a_3))\le、max((a_1+a_4-M),(a_2+a_3))$

又推导出 $\max((a_3+a_4-M),(a_1+a_2))\le\max((a_2+a_3-M),(a_1+a_4))$。

> $\because a_1+a_2\le a_1+a_4,a_3+(a_4-M)<a_3+a_1$  
> $\therefore \max((a_3+a_4-M),(a_1+a_2))\le\max((a_2+a_3-M),(a_1+a_4))$

这告诉我们，需要取模的数对一定完全在不需要取模的对后面。因此，整体的匹配形成了这样一种形状：

![pECgGqg.png](https://s21.ax1x.com/2025/01/09/pECgGqg.png)

也就是说，以某个下标 $k$ 为界，$[1,k)$ 的元素间互相拉数对，$[k,2\times N]$ 的元素间互相拉数对。

不过，这两部分的分界线怎么确定呢？实际上，这个分界线越靠左越好；也就是说我们要尽可能地从不减 $M$ 的那些数对中匀出能减去 $M$ 的一对对数。为什么呢？

半感性半理性地理解一下。左边的答案肯定不会更劣，因为删除一些元素不可能让这个集合通过加法规则组合出来的最大值变大；右边的答案也不会更劣，具体来说见下文：

> 显然我们肯定是尝试将数对里更大的元素拎出去，因为如果把更小的元素拎出去都行，那拎大的肯定更行且更有利于最小化答案。
>
> 这样，设我们调整之前的数对为 $(a_1,a_2)$ 和 $(b_1,b_2)$，且 $a_1\le a_2,b_1\le b_2$。那么调整之后的数对就是 $(a_1,b_1)$ 和 $(a_2,b_2)$。
>
> 现在我们需要证明 $\max((a_1+b_1),(a_2+b_2-M))\le\max((a_1+a_2),(b_1+b_2))$。
>
> 显然 $a_2+b_2-M<a_2<a_1+a_2$。
> 又 $a_1+b_1>a_1+a_2$ 当且仅当 $b_1>a_2$。此时 $a_1+b_1\le a_2+b_1<b_1+b_2$。
> 由此得证。

现在考虑代码实现。首先 $O(NlogN)$ 做法显然，二分就行了；但是我们有更优美的 $O(N)$ 做法。考虑这样一种单调性，对于元素 $a_i$ 来说总是存在一个下标 $x_i$ 使得 $a_i+a_{[x_i,2\times N]}\ge M,a_i+a_{[1,x_i)}\le$，且对于 $i<j$，$x_i\ge x_j$。于是我们就可以用双指针扫一遍，求解所有的 $x_i$。而对于 $a_i$ 来说 $k_i=i-(N-x_i)$ 就是保证它合法的最左分界线。最终确定的分界线即为 $\max k_i$（注意，如果此结果是个偶数还要加一）。排序可以用基数排序做到 $O(N)$。

### 代码
除排序之外 $O(N)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MaxN=1e5+5;
int M,N,A[MaxN<<1];
void maxxer(int &x,int y){x=max(x,y);}
int main(){
    scanf("%d%d",&N,&M);
    for(int i = 1;i <= N*2;i++)scanf("%d",&A[i]);
    sort(A+1,A+N*2+1);A[N*2+1]=M;int bkp=0;
    for(int i=1,j=N*2+1;i<=N*2;i++){
        while(A[j-1]+A[i]>=M)j--;
        maxxer(bkp,i-(N*2-j));
    }
    if(bkp%2==0)bkp++;int ans=0;
    for(int i=1,j=bkp-1;i<j;i++,j--)maxxer(ans,(A[i]+A[j])%M);
    for(int i=bkp,j=N*2;i<j;i++,j--)maxxer(ans,(A[i]+A[j])%M);
    printf("%d",ans);
    return 0;
}
```

### 反思与总结
思考过程上，我们先从平常没有取模的情况开始思考起，然后推广到多出一个限制的情况，这是一种由平常到特别的思想。除此之外，本题关于序和最优性的大量结论还需要一定的推导能力。最后代码实现注意一些细节就行。

---

## 作者：Macesuted (赞：1)

[View in my blog](https://www.macesuted.cn/article/agc032e/)

---

[题面](https://atcoder.jp/contests/agc032/tasks/agc032_e)

# 题意

给你 $2 \times n$ 个整数 $a_i(0 \le a_i < m)$，你需要最小化将它们两两分组后每组之和对 $m$ 取模后的最大值。

$n \le 10^5,~m \le 10^9$

# 分析

看到让最大值最小化，我们先考虑二分最终的答案，每次检查是否存在一种方案使得配对后每对之和对 $m$ 取模后小于限制 $lim$。

考虑对于一个 $lim$，若存在合法方案，则将 $a_i$ 数组从小到大排序后一定有一种合法方案可以由下面的方法构造：

![](https://img-kysic-1258722770.file.myqcloud.com/a39997c6f6e5417094c7a9a31f8620ef/714d5736b93d2.png)

蓝色的边连接的两个点相加之和 $sum \in [0,~lim]$，绿色的边连接的两个点相加之和 $sum \in [M,~M+lim]$。该方案即为将序列从某一点断开为两个序列，左序列间全部使用蓝边进行匹配，右序列中全部使用绿边进行匹配。

---

考虑证明可以不存在蓝线与绿线相交的情况，假设存在四个位置 $i_1,~i_2,~i_3,~i_4$ 满足 $0 \le a[i_1]+a[i_3] \le lim,~m \le a[i_2]+a[i_4] \le m+lim$。

1. $a[i_2] \le a[i_3]$，所以 $0 \le a[i_1]+a[i_2] \le a[i_1]+a[i_3] \le lim$。
2. $a[i_3] \ge a[i_2]$，所以 $a[i_3]+a[i_4] \ge a[i_2]+a[i_4] \ge m$。而 $a[i_3] \le lim-a[i_1] \le lim,~a[i_4] \le m$，所以 $a[i_3]+a[i_4] \le m+lim$。

由于可以不存在蓝线与绿线相交的情况，所以我们可以将整个序列先分为左右两个序列，左序列内只连蓝线，右序列内只连绿线。

---

考虑证明同颜色线可以不相交，以左区间为例：假设存在四个位置 $i_1,~i_2,~i_3,~i_4$ 满足 $a[i_1]+a[i_3] \le lim,~a[i_2]+a[i_4] \le lim$。

1. $a[i_1]+a[i_3] \le a[i_1]+a[i_4] \le a[i_2]+a[i_4]$，所以 $a[i_1]+a[i_4] \le lim$。
2. $a[i_1]+a[i_3] \le a[i_2]+a[i_3] \le a[i_2]+a[i_4]$，所以 $a[i_2]+a[i_3] \le lim$。

所以在左右序列中不会出现有线相交的情况，即 $i$ 位置一定与 $len-i+1$ 位置匹配（$len$ 为序列长度）。

---

通过上面的证明我们可以确定该构造方案的合法性。

如果直接在二分答案中通过该方式判断限制是否合法，由于该方案中“将序列分为左右序列”操作需要再进行一次二分答案，所以总时间复杂度为 $O(nlgnlgm)$，可能可以通过本题（并没有试过）。

仔细分析发现先二分出答案再通过该构造方法判断合法性有较大的浪费，因为该构造方案不仅能够判断合法性，同时也可算出满足条件的最优答案。所以我们可以考虑直接通过二分找出最佳的断开左右序列的位置，计算该位置上的答案即可。

考虑找到一个尽量小的位置 $t$ 将原序列分为左右两个序列，同时满足两边序列都可以通过上述方法构造出方案，则该 $t$ 值对应的方案一定为最优方案。因为在左右序列均合法的前提下，$t$ 越小，左序列最大和与右序列最大和显然越小，即总答案一定越小。

二分出最小的符合条件的 $t$ 即可，时间复杂度 $O(nlgn)$。

# 代码

[View on Github](https://github.com/Macesuted/Code/blob/main/AtCoder/agc032_e.cpp)

```cpp
/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
// fread
}  // namespace io
using io::getch;
using io::getstr;
using io::putch;
using io::putstr;
using io::read;
using io::write;

#define maxn 200005

int a[maxn], n, m, ans = 0x3f3f3f3f;

bool check(int lim) {
    int maxVal = 0;
    for (register int i = 1, j = 2 * lim; i < j; i++, j--) maxVal = max(maxVal, a[i] + a[j]);
    for (register int i = 2 * lim + 1, j = 2 * n; i < j; i++, j--) {
        if (a[i] + a[j] < m) return false;
        maxVal = max(maxVal, a[i] + a[j] - m);
    }
    ans = min(ans, maxVal);
    return true;
}

int main() {
    n = read<int>(), m = read<int>();
    for (register int i = 1; i <= 2 * n; i++) a[i] = read<int>();
    sort(a + 1, a + 2 * n + 1);
    int l = 0, r = n;
    check(0);
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        check(mid) ? r = mid : l = mid;
    }
    check(r);
    write(ans), putch('\n');
    return 0;
}
```

---

## 作者：xht (赞：1)

## [Modulo Pairing](https://atcoder.jp/contests/agc032/tasks/agc032_e)

### 题意

- 给定模数 $m$ 和 $2n$ 个整数，你要将这些整数分成 $n$ 对。
- 对于每一对 $(x,y)$，其权值为 $(x+y) \bmod m$。
- 你要最小化这 $n$ 对权值的最大值。
- $n \le 10^5$，$m \le 10^9$。

### 题解

有结论：按从小到大排序后，一定存在一个最优解，是以某个位置为界，两边分别首位匹配，满足左边每一对的和都 $< m$，右边每一对的和都 $\ge m$。

二分这个位置，时间复杂度 $\mathcal O(n \log n)$。

### 代码

```cpp
const int N = 2e5 + 7;
int n, m, a[N], ans;

inline bool pd(int o) {
	for (int i = o << 1 | 1; i <= n << 1; i++)
		if (a[i] + a[((n+o)<<1|1)-i] < m) return 0;
	return 1;
}

int main() {
	rd(n, m), rda(a, n << 1);
	sort(a + 1, a + (n << 1 | 1));
	int l = 0, r = n;
	while (l < r) {
		int d = (l + r) >> 1;
		if (pd(d)) r = d;
		else l = d + 1;
	}
	int p = l << 1;
	for (int i = 1; i <= p; i++)
		ans = max(ans, a[i] + a[p+1-i]);
	for (int i = p + 1; i <= n << 1; i++)
		ans = max(ans, a[i] + a[(n<<1|1)+p-i] - m);
	print(ans);
	return 0;
}
```

---


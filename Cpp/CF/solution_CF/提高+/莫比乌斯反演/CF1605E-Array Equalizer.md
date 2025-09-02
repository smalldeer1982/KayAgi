# Array Equalizer

## 题目描述

## 题面描述
Jeevan 有两个长度为 $n$ 的数组：$a$ 和 $b$。他有以下两种操作：

+ 选择一个 $k$（$1 \le k \le n$），对所有满足 $1 \leq i \leq n$ 并且 $1 \le i \times k \le n$ 的 $i$，令 $a_{ik}=a_{ik} + 1$。
+ 选择一个 $k$（$1 \le k \le n$），对所有满足 $1 \leq i \leq n$ 并且 $1 \le i \times k \le n$ 的 $i$，令 $a_{ik}=a_{ik} - 1$。


不幸的是，他忘记了 $b_1$，因此他会向你提问 $q$ 次，每次给出一个 $x$，表示：

- 如果 $b_1 = x$，那么把 $a$ 变为 $b$ 至少需要几次操作？

## 样例 #1

### 输入

```
2
3 7
-1 5
3
1
4
3```

### 输出

```
2
4
2```

## 样例 #2

### 输入

```
6
2 5 4 1 3 6
-1 4 6 2 3 5
3
1
8
4```

### 输出

```
10
29
9```

# 题解

## 作者：Cry_For_theMoon (赞：10)

对我这种不懂 $\mu$ 函数什么的人来说这个题做起来远不止 2400* ()

具体做法和 45dino 的一样，这里主要讲一个官方题解和洛谷题解都没有提到的结论的证明。

首先我们令 $c_i=a_i-b_i$。不难发现本题的调整过程是 $1\rightarrow n$ 逐项调整的，在 $i$ 处执行操作调整之前，$i$ 的因数 $d$ 可能会对它做出影响。我们设 $f_i$ 是在第 $i$ 处做的操作次数（可能为负），显然 $f_1=|c_1|,f_2=|c_2-f_1|$，我们都不难看出：

$$f_i=c_i-\sum_{d|i,d\neq i}f_d$$

答案为 $f$ 绝对值之和。

问题是 $f_1$ 每次是不确定的，我们要快速计算 $f$ 的和，那么就得想办法把它搞成 $c$ 的形式。我不是很理解怎么观察到 $\mu$ 的结论的，在我看来提供一个方向的话，就是这里这个 $d|n$ 让我们想到可能和 $\mu$ 有关，然后质数 $p$ 的 $f$ 值是显然易见为 $f_p=|c_p-c_1|$ 的，那么我们研究几个非质数 $4,6,8,10,12$，比如说 $f_6=|c_6-f_3-f_2-f_1|=|c_6-(c_3-c_1)-(c_2-c_1)-c_1|$ 这样的展开它们，然后就大概能猜到这个结论了：

$$f_i=\sum_{d|i}\mu(\frac{i}{d})c_d$$

但是我是来证明这个玩意的：

对于任何一个 $k\rightarrow n$ 的转移，显然最后 $f_n$ 中，$c_k$ 的体现是可能会在某些 $f_m$ 中，满足 $k\mid m\mid n$ 的，这样 $f_m$ 的式子里可能会有 $c_k$，然后又体现在 $f_n$ 的式子里。

显然 $m=kl$，其中 $l\mid (g=\frac{n}{k})$。

我们来研究 $\mu(g)\neq 0$ 的情况，其实就是 $g$ 没有次数大于 $1$ 的质因数。我们设有 $\alpha$ 个，记这种情况下 $k\rightarrow n$ 的贡献为 $f(\alpha)$，注意这里的 $f$ 和上文意义不同。

显然 $f(1)=-1$，这意味着 $g$ 为质数，那么 $f_n$ 里关于 $c_k$ 的只有减 $f_k$ 这一项，而 $f_k=(c_k-...)$。

我们来探究 $f(2)$ 的值。此时发现 $g$ 有两个不同的质因数 $p,q$，$l$ 的值有三种：$1,p,q$。对于 $l=1$，显然贡献还是 $-1$，对于 $l=p/q$，显然贡献变成了 $1$。此时 $f(2)=1$。

对于 $f(3)$ 是同理的，$\omega(l)=0/1/2$ 的方案数各有 $1/3/3$ 种（$w(n)$ 是 $n$ 的不同质因数个数），$f(3)=-1+3f(1)-3f(2)=-1$。

到这里，我们可以考虑归纳了，假设 $f(\alpha)=(-1)^{\alpha}$ 对于 $\alpha \lt n$ 成立，那么 $f(n)$ 就是二项式系数 $\dbinom{n}{i}$ 里，$i$ 为奇数的项之和和 $i$ 为偶数的项之和，众所周知这个值是 $0$。但是注意到我们不能把 $\omega(g)$ 个质数全部选择了，所以要去掉 $1$，而 $\alpha$ 的奇偶性恰好决定了这个 $1$ 是减掉还是加上。所以答案不是 $1$ 就是 $-1$，而刚才提到 $g$ 的质因数两两不同所以 $\mu(g)\neq 0$ 时，确实 $k\rightarrow n$ 的贡献是 $\mu(g)c_k$。

好的让我们证明 $g$ 带平方质因子的时候 $k$ 不会对 $n$ 产生影响。其实是类似的，我们发现研究 $g=p^2$ 的时候贡献确实为 $0$，$g=p^2q$ 的时候也是 $0$（$p,q$ 为不同质数），那么可以归纳证明 $\mu(l)=0$ 的时候不产生贡献，产生贡献的 $l$ 只可能是 $\mu(l)\neq 0$ 的，所以你可以抹掉 $g$ 的质因子的那些次数，然后又变成了二项式系数的奇数项和偶数项之差问题，但是此时 $\dbinom{n}{n}$ 可以选择了所以结果为 $0$，那么最后贡献还是 $0$。

其实这个证明还是需要自己去感性理解一下的，因为有些东西我不太能够表述出来，不过也许这是一个经典的莫反 trick 之类的？

代码我就不放了，和 45dino 的没啥区别。

#### update：发现我傻逼了，证的极其麻烦，刚学了莫反学了个寂寞。

我们看这个式子：

$$f_i=c_i-\sum_{d|i,d\neq i}f_d$$

就是 

$$c_i=\sum_{d|i}f_d$$

就是说，$c$ 是 $f$ 的和函数。根据莫比乌斯反演：

$$f_i=\sum_{d|i}\mu(\frac{i}{d})c_d$$

完事...

---

## 作者：45dino (赞：5)

假如 $q=1$，即已知 $b_1$，如何求值？

首先把问题简化，设 $c_i=b_i-a_i$，那么每次操作实际上是在对 $c_i$ 加加减减，最后要变成 $0$，从 $c_1$ 到 $c_n$ 依次考虑。

对于 $c_1$ 来说，将 $c_1$ 变成 $0$ 的代价为 $|c_1|$。

对于 $c_i\space(i\neq1)$来说，在“主动”操作它之前，会被 $l\space(l|i)$ “被动”操作。

从最简单的情况考虑问题，当 $i$ 为质数的时候，易得代价为 $|c_i-c_1|$。当 $i=6$ 的时候，代价为 $|c_6-(c_3-c_1)-(c_2-c_1)-c_1|=|c_6-c_3-c_2+c_1|$。事实上，将 $c_i$ 变成 $0$ 的代价为：
$$f(i)=|\sum_{l|i}\mu(\frac i l)\times c_l|$$
那么总答案就是。
$$\sum_{i=1}^n|\sum_{l|i}\mu(\frac i l)\times c_l|$$
关于莫比乌斯函数$(\mu)$，详见[P4450](https://www.luogu.com.cn/problem/P4450)

如果直接算，单次的时间复杂度是 $\Theta(n\log n)$。考虑如何带修。

先把 $f(2),f(3),...,f(n)$ 中除了 $l=1$ 的值算出来（即$f'(i)=\sum_{l|i,l\neq1}\mu(\frac i l)\times c_l$），那么每次修改只要把 $\mu(\frac i 1)\times c_1$ 加进 $f(i)$ 再取个绝对值再求和就是答案。但这并没有在根本上解决问题，因为单次时间复杂度为 $\Theta(n)$，无法通过。

由于 $\mu(i)\in\{-1,0,1\}$，可以将 $f'(i)$ 按照 $\mu(i)$ 的值分成三类，对于 $\mu(i)=0$，直接取绝对值并相加即可，对于另外两种情况，以 $\mu(i)=-1$ 为例。

首先将 $f'(i)$ 从小到大排序：

![](https://cdn.luogu.com.cn/upload/image_hosting/dhvw696b.png)

其中直线代表 $0$，低于直线的点在取绝对值的时候会被翻上去。

减去 $c_1$ 后，这个图可能会变成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/v3lbenf8.png)

二分一下此时在直线下有多少个点，即有多少个 $f'(i)<c_1$，即可在 $\Theta(1)$ 的复杂度下算出答案。对于 $\mu(i)=1$ 亦然。

因此，本题的复杂度为 $\Theta(q\log n)$。

[参考代码](https://codeforces.com/contest/1605/submission/135173624)

---

## 作者：_SeeleVollerei_ (赞：4)

看各位大佬都用的 $\mu$，我来讲另一种生草的做法。

首先考虑一组询问的情况，有一个很显然的做法。

首先肯定是让 $a_i$ 减去 $b_i$，然后变成一个将 $a_i$ 变成 $0$ 的问题 ，然后考虑从左往右，显然要贪心的搞，比如第一步，只有 $1$ 能控制它自己，所以先直接把 $1$ 清零，然后就可以忽视 $1$ 了，这时候 $2$ 又只有它能控制自己了，以此类推。

然后模拟一下这个过程，我们可以发现答案就是每个位置对自己清零时，自己那个数的绝对值的和。有一个很暴力的做法，把每个数上的最终值用未知数表示出来。比如手动模拟一下就会是 $1\to a_1,2\to a_2-a_1,3\to a_3-a_1,6\to a_6-a_3-a_2+a_1$。这玩意用一个类似多项式的东西似乎可以直接存下来。

但是 $a_{[2...n]}$ 都是已知的，也就是说，比如 $a_6-a_3-a_2+a_1$，前面三项的值我们是可以算出来的，所以每个数都可以变成 $A-Ba_1$ 或 $A+Ba_1$ 的形式 $(B > 0)$。如果 $B=0$ 就直接在一开始直接统计就行了。

我们考虑绝对值，以 $A-Ba_1$ 为例，当 $a_1\ge \frac{A}{B}$ 时， $|A-Ba_1|=Ba_1-A$，否则 $|A-Ba_1|=A-Ba_1$ ，所以我们将每个数按照 $\frac{A}{B}$ 排序即可，然后把询问离线下来，对 $a_1-qx$ 排序，然后用一个双指针，同时统计所有 $a1\ge \frac{A}{B}$ 的 $A$ 和 $B$ 的和，以及所有 $a1 < \frac{A}{B}$ 的 $A$ 和 $B$ 的和即可。$A+Ba_1$ 同理。

具体看代码实现。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const int N=2e5+5;
int n;
LL a[N],f1[N],ss;
inline int Read(){
	char ch;
	int f=1;
	while((ch=getchar())<'0'||ch>'9')
		if(ch=='-') f=-1;
	int x=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
		x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
inline void Print(const LL x,const char ch='\n',const bool flg=1){
	if(x<0){
		putchar('-');
		return Print(-x,ch,flg);
	}
	if(x>=10) Print(x/10,ch,0);
	putchar(x%10+48);
	if(flg) putchar(ch);
	return ;
}
inline LL Abs(const LL x){
	return x>0?x:-x;
}
struct Node{
	LL a,b;
}sub[N],add[N],subbig,subsmall,addbig,addsmall;
// sub 是 A-Ba1 的数  add 是 A+Ba1 的数
//subbig subsmall 分别表示 对于 A-Ba1 a/b >= a1 和 a/b < a1 的 a 和 b 的和
//addbig addsmall 同理
int cntsub,cntadd;
inline bool Cmp(const Node x,const Node y){
	return x.a*y.b<y.a*x.b;
}
inline void Init(){
	n=Read();
	for(register int i=1;i<=n;i++)
		a[i]=Read();
	Read();
	for(register int i=2;i<=n;i++){
		int b=Read();
		a[i]-=b;
	}
	f1[1]=1;
	for(register int i=2;i<=n;i++)
		f1[i]--;
	for(register int i=2;i<=n;i++){
		if(f1[i]==0) ss+=Abs(a[i]);
		if(f1[i]<0){
			++cntsub;
			sub[cntsub].a=a[i];
			sub[cntsub].b=-f1[i];
		}
		if(f1[i]>0){
			++cntadd;
			add[cntadd].a=a[i];
			add[cntadd].b=f1[i];
		}
		for(register int j=i+i;j<=n;j+=i){
			a[j]-=a[i];
			f1[j]-=f1[i];
		}
	}
	sort(sub+1,sub+cntsub+1,Cmp);
	sort(add+1,add+cntadd+1,Cmp);
	return ;
}
int id[N],q;
LL ans[N],qa1[N];
inline bool Cmp1(const int x,const int y){
	return qa1[x]<qa1[y];
}
inline void Solve(){
	q=Read();
	for(register int i=1;i<=q;i++){
		id[i]=i;
		qa1[i]=a[1]-Read();
	}
	sort(id+1,id+q+1,Cmp1);
	int jsub=0,jadd=0;
    //[1...jsub]是 a/b <= x 的
    //[1...jadd]是 -a/b<=x 的
	for(register int i=1;i<=cntsub;i++){
		if(sub[i].b*qa1[id[1]]>=sub[i].a){
			jsub=i;
			subsmall.a+=sub[i].a;
			subsmall.b+=sub[i].b;
		}
		else{
			subbig.a+=sub[i].a;
			subbig.b+=sub[i].b;
		}
		ans[id[1]]+=Abs(sub[i].a-sub[i].b*qa1[id[1]]);
	}
	for(register int i=1;i<=cntadd;i++){
		if(-add[i].b*qa1[id[1]]>=add[i].a){
			jadd=i;
			addsmall.a+=add[i].a;
			addsmall.b+=add[i].b;;
		}
		else{
			addbig.a+=add[i].a;
			addbig.b+=add[i].b;
		}
		ans[id[1]]+=Abs(add[i].a+add[i].b*qa1[id[1]]);
	}
	for(register int i=2;i<=q;i++){
		while(jsub<cntsub&&sub[jsub+1].b*qa1[id[i]]>=sub[jsub+1].a){
			jsub++;
			subsmall.a+=sub[jsub].a;
			subsmall.b+=sub[jsub].b;
			subbig.a-=sub[jsub].a;
			subbig.b-=sub[jsub].b;
		}
		while(jadd>=1&&-add[jadd].b*qa1[id[i]]<add[jadd].a){
			addbig.a+=add[jadd].a;
			addbig.b+=add[jadd].b;
			addsmall.a-=add[jadd].a;
			addsmall.b-=add[jadd].b;
			jadd--;
		}
		LL sum1,sum2,sum3,sum4;
		sum1=Abs(subsmall.a-subsmall.b*qa1[id[i]]);
		sum2=Abs(subbig.a-subbig.b*qa1[id[i]]);
		sum3=Abs(addsmall.a+addsmall.b*qa1[id[i]]);
		sum4=Abs(addbig.a+addbig.b*qa1[id[i]]);
		ans[id[i]]=sum1+sum2+sum3+sum4;
	}
	for(register int i=1;i<=q;i++)
		Print(ans[i]+ss+Abs(qa1[i]));
        //注意最后要加上 b=0 的数 以及 a1
	return ;
}
int main(){
	Init();
	Solve();
	return 0;
}
```

完结撒花。

---

## 作者：intel_core (赞：3)

感觉我的思考方式和其他题解的不太一样）

首先，操作顺序明显是可以换的；所以我们把 $i=1$ 的操作换到最前面，进行完这些操作之后，相当于第一个位置就不变了。

因此执行 $i=1$ 操作的次数是固定的；类似的可以知道，只要不对同一个 $i$ 既做 `increase` 又做 `decrease` 那么一定是最优策略。

想通了这个问题，下面考虑如何回答这个阴间询问。

很明显，应该先令 $d_i=a_i-b_i$，简化一下问题。

由前面的结论，我们应该先构造一种可以使 $d_i$ 归零的操作，然后消掉操作过程中自相矛盾（既做 `increase` 又做 `decrease`）的操作。

由于询问变的只是第一个数，显然应该先考虑如何把 $d_2,d_3,\cdots,d_n$ 全归零。

一个一个模拟消掉 $d_2,d_3,\cdots,d_n$ 的过程，显然是 $O(n \log n)$ 的。

然后我们还应该求出使 $(1,0,0,\cdots,0)$ 归零的操作。

设 $x_i$ 表示消掉 $d_2,d_3,\cdots,d_n$ 的过程中对第 $i$ 位进行的操作（如果 `increase` 就为正，`decrease` 就为负）；设 $y_i$ 为消掉 $(1,0,0,\cdots,0)$ 过程中对第 $i$ 位进行的操作

现在回答询问就变得非常简单：设 $d_1=k$，那么答案就是 $\sum_{i=1}^n |x_i+k\times y_i|$。

但是这么直接枚举肯定是不行的；我们考虑把绝对值拆掉。

分成两半处理前缀和可以轻松解决这个问题；只需要 $O(\log n)$ 一次二分找到绝对值内正负的交界处就可以。

综上，复杂度 $O(n\log n)$，代码很丑就不放了。

---

## 作者：high_sky (赞：2)

# CF1605E Array Equalizer 题解分析

## 思路

设 $x_i$ 表示在第 $i$ 个数上面进行 $x_i$ 次操作（要么全正，要么全负），那么我们有以下关系式：
$$
a_j+\sum_{i|j}x_i=b_j
$$
移项可得：
$$
\sum_{i|j}x_i=b_j-a_j
$$
令 $\delta_i=b_i-a_i$，有：
$$
\sum_{i|j}x_i=\delta_j
$$
套用莫比乌斯反演：
$$
x_i=\sum_{d|i}\mu\left(\frac i d\right)\delta_d
$$
将 $d=1$ 提出：
$$
x_i=\delta_1\mu(i)+\sum_{d|i,d\geq 2}\mu\left(\frac i d\right)
$$
于是我们令：$f(i)=\sum_{d|i,d\geq 2}\mu\left(\frac i d \right)$，这个可以 $\mathcal{O}(n\log n)$ 得到。

我们欲求：
$$
\sum_{i=1}^n|x_i|
$$
将 $i=1$ 提出来，得到：
$$
|\delta_1|+\sum_{i=2}^n|x_i|
$$
将 $x_i$ 代入有：
$$
|\delta_1|+\sum_{i=2}^n|\delta_1\mu(i)+f(i)|
$$
由于 $b_1$ 会给出，所以 $\delta_1$ 是知道的。

我们会发现这个绝对值似乎很难处理，但是我们注意到 $\mu(i)$ 只有三种取值情况：$1,-1,0$。

如果我们将里面的绝对值化成 $|a-b|$，其中 $a$ 是定值，$b$ 会变化，那么这个我们可以考虑排序加二分得到正负来处理。

于是：

- 对于 $\mu(i)=1$，则要加的值为 $|\delta_1+f(i)|$，令 $p=-f(i)$，我们就是求 $|\delta_1-p|$ 了。
- 对于 $\mu(i)=-1$，则要加的值为 $|-\delta_1+f(i)|$，两边加个负号变成：$|\delta_1-f(i)|$，令 $q=f(i)$，我们就是求 $|\delta_1-p|$ 了。
- 对于 $\mu(i)=0$，则直接用一个变量加上 $|f(i)|$ 这个答案。

最后我们可以得到一个 $p$ 数组和 $q$ 数组，排完序后得到前缀和，询问时进行二分获取值即可。

时间复杂度 $\mathcal{O}(n\log n+m\log n)$，其中 $m$ 是询问次数。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#define int long long
#define N 200005
using namespace std;
int C,n,m,a[N],b[N],q[N],T,delta[N],mu[N],prime[N],cnt,f[N];
bool vis[N];
vector<int> t1,t2,sumt1,sumt2; 
void init(int n){
	mu[1] = 1;
	for (int i = 2;i <= n;i ++) {
		if (!vis[i]) prime[++cnt] = i,mu[i] = -1;
		for (int j = 1;j <= cnt && prime[j] * i <= n;j ++) {
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = -mu[i];
		}
	}
}
int calc(vector<int>& arr,vector<int>& pre,int x) {
	int nArr = arr.size();
    int pos = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
    int l = x * pos - pre[pos];
    int r = (pre[nArr] - pre[pos]) - x * (nArr - pos);
//    cout << l << ' ' << r << endl;
    return l + r;
}
signed main(){
	cin >> n;
	init(n + 2);
	for (int i = 1;i <= n;i ++) scanf("%lld",&a[i]);
	for (int i = 1;i <= n;i ++) scanf("%lld",&b[i]);
	for (int i = 2;i <= n;i ++) delta[i] = b[i] - a[i];
	for (int i = 2;i <= n;i ++)
		for (int j = i;j <= n;j += i)
			f[j] += mu[j / i] * delta[i];
	int sumans = 0;
	for (int i = 2;i <= n;i ++) {
		if (mu[i] == -1) t1.push_back(f[i]);
		else if (mu[i] == 1) t2.push_back(-f[i]);
		else sumans += abs(f[i]);
	}
	stable_sort(t1.begin(),t1.end()),stable_sort(t2.begin(),t2.end()); 
//	cout << sumans << endl;
	vector<int> sumt1(t1.size() + 1, 0), sumt2(t2.size() + 1, 0);
    for (int i = 0;i < t1.size();i ++) sumt1[i + 1] = sumt1[i] + t1[i];
    for (int i = 0;i < t2.size();i ++) sumt2[i + 1] = sumt2[i] + t2[i];
//    cout << t1.size() << ' ' << t2.size() << endl;
//    for (int i = 1;i <= t1.size();i ++)cout << sumt1[i] << "\n"[i != t1.size()];
//    for (int i = 1;i <= t2.size();i ++) cout << sumt2[i] << "\n"[i != t2.size()];
	cin >> m;
	for (;m --;) {
		scanf("%lld",&b[1]);
		int del = b[1] - a[1];
		int ans = calc(t1,sumt1,del) + calc(t2,sumt2,del) + sumans;
//		cout << calc(t1,sumt1,del) << ' ' << calc(t2,sumt2,del) << "{}";
		printf("%lld\n",ans + abs(del));
	}
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

不妨令 $b_1 = x$，$c_i = b_i - a_i$ 是一个关于 $x$ 的一次函数，不妨设对位置 $i$ 的操作变化量为 $d_i$，显然有 $c_i = \sum_{j|i} d_j$，所以可以通过 $c_i$ 来还原 $d_i$，具体来说从一开始令 $d_i \gets  d_i + c_i$ 并令 $d_{i \times j} \gets d_{i \times j} - d_i$。解出来 $d_i$ 也是一个关于 $x$ 的一次函数，最优的策略下步数肯定是 $\sum |d_i|$，考察每个式子对 $x$ 的贡献为一个区间加绝对值一次函数，讨论正负性拆开一次函数后可以用差分简单维护每个位置的系数和常数，时间复杂度 $O(n \log n + V)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5+114;
struct node{
    int k,c;
    node(int K=0,int C=0){
        k=K,c=C;
    }
    node operator-(const node &x)const{
        return node(k-x.k,c-x.c);
    }
    node operator+(const node &x)const{
        return node(k+x.k,c+x.c);
    }
}f[maxn],g[maxn];
int a[maxn],b[maxn];
int n;
const int maxv = 1e6+114;
int d1[maxv];
int d2[maxv];
void add(int l,int r,int k,int c){
    if(l>r) return ;
    if(r>1e6) r=1e6;
    d1[l]+=k;
    d1[r+1]-=k;
    d2[l]+=c;
    d2[r+1]-=c;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    f[1]=node(1,-a[1]);
    for(int i=2;i<=n;i++){
        f[i]=node(0,b[i]-a[i]);
    }
    for(int i=1;i<=n;i++){
        g[i]=g[i]+f[i];
        for(int j=2;j*i<=n;j++) g[i*j]=g[i*j]-g[i];
    }
    //\sum|kx+c|
    for(int i=1;i<=n;i++){
        if(g[i].k==0){
            add(1,1e6,0,g[i].c>0?g[i].c:-g[i].c);
            continue;
        }
        if(g[i].k<0) g[i].k*=-1,g[i].c*=-1;
        if(g[i].c>=0) add(1,1e6,g[i].k,g[i].c);
        else{
            add(1,-g[i].c/g[i].k,-g[i].k,-g[i].c);
            add(-g[i].c/g[i].k+1,1e6,g[i].k,g[i].c);
        }
    }
    for(int i=1;i<maxv;i++) d1[i]+=d1[i-1],d2[i]+=d2[i-1];
    int q;
    cin>>q;
    while(q--){
        int x;
        cin>>x;
        cout<<d1[x]*x+d2[x]<<'\n';
    }
    return 0;
}
```

---

## 作者：Hanx16Kira (赞：0)

# Array Equalizer

[Luogu CF1605E](https://www.luogu.com.cn/problem/CF1605E)

## Solution

题目没有要求判断无解，那么先想如何构造一种通解。考虑枚举每次修改的起始位置（即每次修改的 $k$），容易发现调换每次修改的顺序不会使得答案发生变化，所以不妨从小到大枚举 $k$。如果当前修改的是 $k$，那么前 $k-1$ 个数一定已经修改完成了，否则之后的修改都无法操作到前面这 $k-1$ 个数。因此正确的贪心方法就是从小到大依次使得每个 $a_i=b_i$，直接暴力模拟的话就是 $\mathcal O(qn\log n)$。

令 $+1$ 操作的贡献为 $1$，$-1$ 操作的贡献为 $-1$，那么设 $f_i$ 表示 $a_i$ 修改到 $b_i$ 所用的修改次数，设 $c_i=a_i-b_i$，有：

$$
f_i=c_i-\sum\limits_{d\mid i\land d\neq i}f_d
$$

因为每次修改影响的是 $c_1$，因此考虑将 $f$ 用 $c$ 表示。

移项得：

$$
c_i=\sum\limits_{d\mid i}f_d
$$

用迪利克雷卷积来表示就是 $c=f*I$。那么对这个式子使用莫比乌斯反演得到 $f=c*\mu$，即：

$$
f_i=\sum\limits_{d\mid i}c_i\cdot \mu(\dfrac{i}{d})
$$

将 $c_1$ 项提出，有：

$$
f_i=\left(\sum\limits_{d\mid i\land d\neq 1}c_i\cdot\mu(\dfrac i d)\right)-c_1\cdot\mu(i)
$$

答案显然是 $\displaystyle\sum\limits_{i=1}^n|f_i|$。

由于存在绝对值，因此考虑讨论 $f_i$ 的正负。令 $v_i=\displaystyle\sum\limits_{d\mid i\land d\neq 1}c_i\cdot\mu(\dfrac i d)$，显然 $v_i$ 可以 $\mathcal O(n\log n)$ 预处理得出。那么按照 $\mu(i)$ 的三种取值进行分讨：

- 当 $\mu(i)=0$ 时，$f_i$ 与 $c_1$ 无关，可以预处理直接算出。
- 当 $\mu(i)=1$ 或 $\mu(i)=-1$ 时，将 $v_i$ 排序，那么所有 $f_i<0$ 的 $i$ 是一个前缀，$f_i\ge 0$ 的 $i$ 是一个后缀，因此直接二分找到分界点即可。

总时间复杂度为 $\mathcal O(n\log n+q\log n)$。

```cpp
// Cirno is not baka!
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define Rof(i, a, b) for (int i = (a); i >= (int)(b); --i)
#define FILE(filename) { \
    freopen(#filename ".in", "r", stdin); \
    freopen(#filename ".out", "w", stdout); \
}
#define All(x) x.begin(), x.end()
#define rAll(x) x.rbegin(), x.rend()
#define pii pair<int, int>
#define fi first
#define se second
#define i64 long long
#define mkp make_pair
#define int long long
#define epb emplace_back
#define pb push_back
using namespace std;

const int _N = 2e5 + 5, mod = 1e9 + 7, inf = 1e9;
template<typename T> void Max(T &x, T y) {x = max(x, y);}
template<typename T> void Min(T &x, T y) {x = min(x, y);}

namespace BakaCirno {
    int N, M, A[_N], B[_N];
    bitset<_N> flag;
    vector<int> prim;
    int mu[_N];
    void InitPrime(int n) {
        mu[1] = 1;
        For(i, 2, n) {
            if (!flag[i]) {
                prim.epb(i);
                mu[i] = -1;
            }
            for (int j : prim) {
                if (i * j > n) break;
                flag[i * j] = 1;
                if (i % j == 0) {mu[i * j] = 0; break;}
                mu[i * j] = -mu[i];
            }
        }
    }
    int val[_N];
    int t1[_N], tot1, t2[_N], tot2, sum3;
    int pre1[_N], pre2[_N], suf1[_N], suf2[_N];
    void Init() {
        InitPrime(N);
        For(i, 2, N) for (int j = i; j <= N; j += i)
            val[j] += mu[j / i] * (A[i] - B[i]);
        For(i, 2, N) {
            if (mu[i] == 0) sum3 += abs(val[i]);
            if (mu[i] == 1) t1[++tot1] = val[i];
            if (mu[i] == -1) t2[++tot2] = val[i];
        }
        sort(t1 + 1, t1 + tot1 + 1), sort(t2 + 1, t2 + tot2 + 1);
        For(i, 1, tot1) pre1[i] = pre1[i - 1] + t1[i];
        For(i, 1, tot2) pre2[i] = pre2[i - 1] + t2[i];
        Rof(i, tot1, 1) suf1[i] = suf1[i + 1] + t1[i];
        Rof(i, tot2, 1) suf2[i] = suf2[i + 1] + t2[i];
    }
    int Solve(int x) {
        int res = sum3 + abs(A[1] - x), L, R;
        L = 1, R = tot1;
        while (L <= R) {
            int mid = (L + R) >> 1;
            if (t1[mid] + A[1] - x >= 0) R = mid - 1;
            else L = mid + 1;
        }
        res += (x - A[1]) * R - pre1[R] + suf1[L] + (tot1 - L + 1) * (A[1] - x);
        L = 1, R = tot2;
        while (L <= R) {
            int mid = (L + R) >> 1;
            if (t2[mid] - A[1] + x >= 0) R = mid - 1;
            else L = mid + 1;
        }
        res += (A[1] - x) * R - pre2[R] + suf2[L] - (tot2 - L + 1) * (A[1] - x);
        return res;
    }
    void _() {
        cin >> N;
        For(i, 1, N) cin >> A[i];
        For(i, 1, N) cin >> B[i];
        Init();
        cin >> M;
        For(i, 1, M) {
            int x; cin >> x;
            cout << Solve(x) << '\n';
        }
    }
}

signed main() {
    // FILE(test);
    cin.tie(0)->sync_with_stdio(0); int T = 1;
    // cin >> T;
    while (T--) BakaCirno::_();
    // fout.flush();
}
```

---

## 作者：zztqwq (赞：0)

手玩样例可知，不考虑对后面的影响直接按照 $1,2,3,\cdots,n$ 的次序依次调整是最优的方案。令 $c_i=a_i-b_i$，那么总代价显然可以写成：

$$
\sum_{x=1}^n \left|c_x-\sum_{y|x\text{ and }y\not=x}\mu\left(\frac{x}{y}\right)c_y\right|
$$

由于修改的是 $c_1$，所以对于每个 $x\not=1$ 将 $c_1$ 拆出来：

$$
\left|c_x-\sum_{y|x\text{ and }y\not=x\text{ and }y\not=1}\mu\left(\frac{x}{y}\right)c_y-\mu(x)c_1\right|
$$

令 $v_x=c_x-\sum_{y|x\text{ and }y\not=x\text{ and }y\not=1}\mu\left(\frac{x}{y}\right)c_y$，那么要求的就是：

$$
|c_1|+\sum_{x=2}^n |v_x-\mu(x)c_1|
$$

对于 $\mu(x)$ 的三个取值分别维护一下即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
const int N=3e5+10;
int mu[N],pri[N],cnt;bool vis[N];
void init(int n)
{
	mu[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!vis[i])pri[++cnt]=i,mu[i]=1;
		for(int j=1;j<=cnt&&1ll*pri[j]*i<=n;j++)
		{
			vis[pri[j]*i]=1;
			if(i%pri[j]==0){mu[i*pri[j]]=0;break;}
			else mu[i*pri[j]]=-mu[i];
		} 
	}
}
int a[N],b[N],c[N];vi v[N];
ll a1[N],a2[N],a3[N];int c1,c2,c3;
ll sum1,sum2[N],sum3[N];
ll val[N];
int main()
{
	int n=read();init(n);
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read(); 
	for(int i=2;i<=n;i++)c[i]=a[i]-b[i];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;1ll*i*j<=n;j++)
			v[i*j].pb(i);
	}
	for(int i=2;i<=n;i++)
	{
		val[i]=c[i];
		for(auto x:v[i])
		{
			if(x==i||x==1)continue;
			val[i]-=mu[i/x]*c[x];
		}
	}
	for(int i=2;i<=n;i++)
	{
		if(mu[i]==0)a1[++c1]=val[i];
		else if(mu[i]==1)a2[++c2]=val[i];
		else a3[++c3]=val[i];
	}
	sort(a2+1,a2+c2+1),sort(a3+1,a3+c3+1);
	for(int i=1;i<=c2;i++)sum2[i]=sum2[i-1]+a2[i];
	for(int i=1;i<=c3;i++)sum3[i]=sum3[i-1]+a3[i];
	for(int i=1;i<=c1;i++)sum1+=abs(a1[i]);
//	for(int i=1;i<=n;i++)printf("%lld ",val[i]);puts("!!");
	int Q=read();
	while(Q--)
	{
		b[1]=read();
		c[1]=a[1]-b[1];
		
//		ll ans=abs(c[1]);
//		for(int i=2;i<=n;i++)ans+=abs(val[i]-mu[i]*c[1]),printf("ans+=abs(%lld - %d*%d)\n",val[i],mu[i],c[1]);
//		printf("%lld!!\n",ans);
		
		ll ans=sum1+abs(c[1]);
		
		int pos=lower_bound(a2+1,a2+c2+1,(ll)c[1])-a2;
		if(pos<=c2){
			ans+=sum2[c2]-sum2[pos-1];
			ans-=1ll*(c2-pos+1)*c[1];
		}
		if((--pos)>0){
			ans-=sum2[pos];
			ans+=1ll*pos*c[1];
		}
		
		pos=lower_bound(a3+1,a3+c3+1,(ll)-c[1])-a3;
		if(pos<=c3){
			ans+=sum3[c3]-sum3[pos-1];
			ans+=1ll*(c3-pos+1)*c[1];
		}
		if((--pos)>0){
			ans-=sum3[pos];
			ans-=1ll*pos*c[1];
		}
		
		printf("%lld\n",ans);
	}
}
```

---


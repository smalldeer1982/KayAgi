# Ideal Farm

## 题目描述

Theofanis decided to visit his uncle's farm. There are $ s $ animals and $ n $ animal pens on the farm. For utility purpose, animal pens are constructed in one row.

Uncle told Theofanis that a farm is lucky if you can distribute all animals in all pens in such a way that there are no empty pens and there is at least one continuous segment of pens that has exactly $ k $ animals in total.

Moreover, a farm is ideal if it's lucky for any distribution without empty pens.

Neither Theofanis nor his uncle knows if their farm is ideal or not. Can you help them to figure it out?

## 说明/提示

For the first and the second test case, the only possible combination is $ [1] $ so there always will be a subsegment with $ 1 $ animal but not with $ 2 $ animals.

## 样例 #1

### 输入

```
4
1 1 1
1 1 2
100 50 200
56220 47258 14497```

### 输出

```
YES
NO
NO
YES```

# 题解

## 作者：vectorwyx (赞：22)

[或许更好的阅读体验（？](https://www.cnblogs.com/vectorwyx/p/15375249.html)

很神奇的贪心。我们要做的其实是尽量构造一个序列，使得其不存在一个和为 $k$ 的连续子段。考虑插板法的思路，现在有 $s$ 个球 $s+1$ 个空隙，其中第 $0,s$ 个空隙必须选，我们需要从 $1\sim s-1$ 这些空隙里选出 $n-1$ 个空隙，使得它们两两间的距离不为 $k$。 

先转为最多能选多少个空隙，显然位置膜 $k$ 不同余的空隙是相互独立的，把膜 $k$ 同余的空隙抽出来组成 $k$ 条数轴，我们要做的就是对每条数轴上的点赋值 $0/1$，要求 $1$ 与 $1$ 不能相邻，问最多有多少个 $1$。贪心，每条数轴肯定是 $1010101$ 这样交替选，但由于第 $0$ 个空隙和第 $s$ 个空隙已经被钦定了，所以它们所在的数轴要进行一些调整，不过这些调整对于数量是不会有影响的：首先如果它们所在数轴的长度为奇数那么无影响；否则，如果 $0$ 和 $s$ 不在同一条数轴上（即 $k\nmid s$），那么只需要把 $01$ 取反，在同一条数轴上（即 $k\mid s$ ）只需要把最后的 $10$ 改成 $01$，比如 $1010$ 改成  $1001$ 就没事了。只有一种情况是例外的：$0,s$ 在同一条数轴上且这条数轴上只有 $0,s$ 这两个点，这对应 $k=s$ ，先判掉就行。

综上，我们把原问题等价转化为了若干条独立的数轴上选最多的不相邻的点（实际上就是链最大独立集），给出了最优决策并证明了其正确性。现在来计算答案：如果第 $i$ 条数轴的长度 $len_i$ 为偶数，那么贡献为 $\lfloor\frac{len_i}{2}\rfloor$，否则贡献为 $\lfloor\frac{len_i}{2}\rfloor+1$。有 $s\%k+1$ 条数轴长度为 $\lfloor\frac{s}{k}\rfloor+1$，其余数轴长度为  $\lfloor\frac{s}{k}\rfloor$，对于 $\lfloor\frac{s}{k}\rfloor$ 的奇偶性分类讨论一下就好了。

题外话：很多人的构造策略可能是先放 $k-1$ 个 $1$ 再放 $1$ 个 $k+1$ 交替进行。注意到最开始 $1010101$ 交替选是等价于这个决策的，尽管有些情况下并不一定正确，但它所选出的 $1$ 的数量一定是正确的（换句话说，一定有其他的决策与其答案相同且没有决策更优），所以根据这个判一下够不够放也是对的。

代码如下（码字不易，点个赞再走好不好QAQ）：
```cpp
#include<bits/stdc++.h>
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
#define sml(x,y) x=min(x,y)
#define big(x,y) x=max(x,y)
#define mk make_pair
#define pb push_back
#define ll long long
#define db double
#define int ll
using namespace std;
inline void out(int *a,int l,int r){fo(i,l,r) printf("%d ",*(a+i));puts("");}
inline int read(){ int x=0,f=1; char ch=getchar(); while(!isdigit(ch)){ if(ch=='-') f=-1; ch=getchar(); } while(isdigit(ch)){ x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); } return x*f; }

signed main(){
	int T=read();
	while(T--){
		int s=read(),n=read(),k=read();//s/k:数轴长度 
		if(s==k) puts("Yes");
		else{ 
			int x;
			if(s/k&1) x=k*(s/k+1)/2; 
			else x=(s%k+1)*(s/k/2+1)+(k-s%k-1)*(s/k/2);
			puts(x>n?"No":"Yes");
		} 
		//else if(n/k*k*2+n%k<=s) puts("No");
		//else puts("Yes");
	} 
	return 0;
}
/*
5
1 1 1
1 1 2
100 50 200
56220 47258 14497
87077 86130 86130
-------------------------
Y
N
N
Y
Y
*/
```


---

## 作者：SnowTrace (赞：6)

duel 的时候随机到这个题，这题都做不出来，真是太菜了。

---

考虑不满足条件时最小的和是多少。

我们先来手磨几组数据，看下面这一组：

$s = 10,n = 5,k = 1$

构造序列 $a = \{2,2,2,2,2\}$ 就可以让他不满足条件。

我们得到一点点启发，这件事情可能和一个数模 $k$ 的结果有一点关系。

我们考虑把问题表示成前缀和作差，那么，如果两个前缀的和 $s1,s2$ 模 $k$ 不同余，他们必然凑不出一个 $k$。

显然只要 $n\geq k+1$ 的时候就必定会出现同余的两个前缀，那么我们这个时候可以让它们之间的差最小，也就是等于 $2k$，这样一定最小。

实际上我们构造的前缀和序列是：

$\{1,2,3,...,k,2k+1,2k+2,2k+3,...,4k+1\}$

原序列是: $\{1,1,1,...,k+1,1,1,1,...,k+1\}$

容易证明这个序列里的和处处取到最小值，所以我们只需要判断 $s$ 和这个序列的大小关系即可。

有一个 corner case 是 $s = k$，显然这个时候永远都可以。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
void solve(){
	int s,n,k;cin >> s >> n >> k;
	int tt = 2*k*(n/k)+n%k;
	if(s == k){
		cout << "YES" << endl;return; 
	}if(s>=tt){
		cout << "NO" << endl;
	}else cout <<"YES" << endl;
}
signed main(){
	int t;cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：WitheredZeal (赞：5)


## 题意  

给三个整数 $s,n,k$。  
你需要判断，是否任意一个正整数序列 $a_1,a_2,\cdots a_n$，使得 $\sum _{i=1}^n a_i =s$，都存在一个子段和为 $k$。  


## 题解  

这题好憨啊，就这能当 div2 only 的 F？  
首先考虑将任意转化为存在，实际上就是求，是否存在一个一个正整数序列 $a_1,a_2,\cdots a_n$，使得 $\sum _{i=1}^n a_i =s$，并且没有子段和为 $k$。  

求一下前缀和，那么就是有 $n+1$ 个互不相同的数 $0<s_1<s_2<\cdots< s_n=s$，他们两两作差的结果没有 $k$。 

实际上只需要求最多能选出几个，然后和 $n$ 比较一下大小即可。

我们考虑模 $k$ 同余的一组数 $c,k+c,2k+c \cdots tk+c$ 肯定是类似隔一个选一个，最多能选 $\lfloor \frac {t+1} 2 \rfloor$ 个。

这样就做完了。




## 代码

```cpp
void DOIT()
{
	rd(s);rd(n);rd(k);
	if (s<k) puts("NO");else if (s==k) puts("YES");
	else 
	{
		m=k*(s/k/2);
		m+=min(k,s%(k*2));
		m-=(s/k)%2;
		if (m>=n) puts("NO");else puts("YES");
	}
}
```

---

## 作者：PragmaGCC (赞：4)

## 题目大意

判断 $s$ 个球是否可以被分到 $n$ 个盒子（盒子非空）里，使得对于每一种分法，都存在一段区间的球总数为 $k$。

## 题解

首先，如果 $s=k$，显然成立。如果 $s<k$，显然不成立。

题目问的是区间和为 $k$，我们考虑转换成前缀和进行计算。

令 $f_i$ 表示前 $i$ 个盒子中的球的数量。因为盒子非空，所以 $f_i$ 互不相同，且 $f_n \le s$。

所以题目可以转换成：在 $[1,s]$ 中取 $n$ 个数 $f_1,f_2,\dots,f_n$，使得 $\exists i>j\in[1,n],f_i-f_j = k$。

我们可以对所有取值进行分组：将 $i,i+k$ 分为一组，这样每 $2k$ 个取值中最多取 $k$ 个。分完组以后剩下的零头也可以取。

这样我们就得到了最多可以取多少个，记为 $t$。

如果 $t < n$，说明无论怎么去，都至少有两个数在同一组内，即一定有两个数的差为 $k$。

反之，一定存在一种排列不满足题意。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define int long long
signed main(void) {
    int T;
    scanf("%lld", &T);
    for (int s, n, k; T; T--) {
        scanf("%lld%lld%lld", &s, &n, &k);
        if (s == k) printf("YES\n");
        else if (s < k) printf("NO\n");
        else {
            int k2 = k * 2, sk = min(s % k2, k - 1); // 注意到奇数倍 k 是不能取的，这里要-1
            printf((s / k2 * k + sk < n) ? "YES\n" : "NO\n");
        }
    }
}
```



---

## 作者：__Star_Sky (赞：2)

## Description
给你三个整数 $s,n,k$，问对于任意长度为 $n$ 的且满足 $\sum\limits_{i=1}^{n}a_i=s$ 且 $\forall a_i\in[1,n],a_i>0$ 的数列 $a$ 是否都有 $\exists l\in[1,n],r\in[l,n],\sum\limits_{i=l}^{r}a_i=k$。如果是，输出 `YES`,否则输出 `NO`。

多组数据，数据组数 $T\le10^5$。$1\le s,n,k\le10^{18},n\le s$
## Solution
提供一个更加简单的思路。

首先根据题意，显然当 $s<k$ 时一定不满足条件，当 $s=k$ 时一定满足条件。

来看 $s>k$ 的情况。此时可以将问题转化为能否构造出一个数列使得 $\forall l\in[1,n],r\in[l,n],\sum\limits_{i=l}^{r}a_i\ne k$。由于需要满足 $\forall a_i\in[1,n],a_i>0$，因此我们可以先把 $a$ 数列的每个位置都先填上一个 $1$。此时观察这个数列，发现在 $a_k$ 这个位置满足 $\sum\limits_{i=1}^{k}a_i=k$，不符合我们构造数列的规则。对此我们可以将 $a_k$ 的位置加上一个 $k$，这样一来 $a_1$ 到 $a_{k-1}$ 的值都是 $1$，$a_k$ 的值变成了 $k+1$，这样前面 $k$ 个数无法拼凑出 $k$ 了。加上其它数也是可以的，但是 $a_k$ 一定至少要变成 $k+1$，否则还是可以拼凑出 $k$。进一步，我们可以发现，每当处于 $k$ 的某个倍数 $p\times k$ 时都会出现 $\sum\limits_{i=p\times k-k+1}^{p\times k}a_i=k$ 的情况，这时候我们都需要将 $a_{p\times k}$ 的值加上 $k$。当然在其它地方加上 $k$ 也是可以的，但是根据贪心策略，显然在加 $p\times k$ 处不会使总花费变多，是更优的。如果觉得有点抽象，可以看一下这张图：
![](https://cdn.luogu.com.cn/upload/image_hosting/bblcv1vf.png?x-oss-process=image/resize,m_lfit,h_1000,w_3000)

$a$ 数列 $n$ 个位置包含 $\lfloor\frac{n}{k}\rfloor$ 个 $k$ 的倍数。由于剩下的部分不到完整的 $k$ 个数因此不用考虑。每次遇到一个 $k$ 的倍数都要使那个位置上的数加上 $k$，一共要加 $\lfloor\frac{n}{k}\rfloor\times k$。由于已经给 $a$ 数列每个位置填了 $1$，因此 $s$ 的值还剩 $s-n$。如果 $s-n\ge \lfloor\frac{n}{k}\rfloor\times k$，说明我们可以构造出反例，输出 `NO`，否则输出 `YES`。

## Code
```
#include<bits/stdc++.h>
#define LL long long
using namespace std;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		LL s,n,k;
		scanf("%lld%lld%lld",&s,&n,&k);
		if(s<k) puts("NO");
		else if(s==k) puts("YES");
		else
		{
			if(s-n>=n/k*k) puts("NO");
			else puts("YES");
		}
	}
	return 0;
}
```

---

## 作者：5ab_juruo (赞：1)

[可能更好的体验](https://5ab-juruo.oier.space/post/solution-cf1594f)

vp 的时候压哨过了，做法好像还不太一样，纪念一下。

感觉这个题 div2 压轴确实有点奇怪。。。

---

即要求给出不 lucky 的构造。

考虑当 $n=k$ 时的如下构造：令 $a_i=1$（$1\le i< n$）且 $a_n=k+1$。显然这样是满足要求的。扩展到一般情况，即：

$$
a_i=\begin{cases}k+1&k\mid i\\1&\text{Otherwise.}\end{cases}
$$

显然这样是满足要求的。且这样是和最小的一种方案。证明如下：

对于一个长度为 $k$ 的序列，共有 $k+1$ 个前缀和，则必然有两个和关于 $k$ 余数一样，即一定有一段的和是 $k$ 的倍数。显然这个数不能是 $0$ 或 $k$，所以和最小时，整段的和应该为 $2k$。上述构造显然可以满足这个要求。

注意到这只是当 $n\ge k$ 最小的情况。如果出现了一个 $k+1$，则当 $s$ 大于等于这个最小情况的和时，只需要将剩下的加到这个 $k+1$ 上即可。

当 $n<k$ 时。注意到只有 $s=k$ 的情况需要特判为 `YES`，其余情况下，根据上面的证明，$n<k$ 的时候前缀和可以做到模 $k$ 两两不同，此时不存在和为 $k$ 的连续子序列。

非常好写：

```cpp
/* name: 1594-r747_F
 * author: 5ab
 * created at: 22-08-12 15:04
 */
#include <iostream>
using namespace std;

typedef long long ll;

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	ll n, s, k;
	int cas;
	
	cin >> cas;
	while (cas--)
	{
		cin >> s >> n >> k;
		if (n < k)
		{
			if (s == k)
				cout << "YES\n";
			else
				cout << "NO\n";
			continue;
		}
		if (s >= (n / k) * (k * 2) + (n % k))
			cout << "NO\n";
		else
			cout << "YES\n";
	}
	
	return 0;
}
```

---

## 作者：luogubot (赞：1)

题意略。

由于每个数至少是 1，不能有区间和为 $k$，考虑相邻的 $k$ 个数的和至少是多少才能保证一定不存在和为 $k$ 的区间。把 $0,1,\cdots ,k$ 位置的前缀和拖出来，那么 $i,i+k$ 不能同时选。当 $s<2k$ 时，只有不超过 $k$ 对位置 $(i,i+k)$，但是有 $k+1$ 个前缀和的点，所以一定会发生冲突；当 $s=2k$ 时，可以构造 $k-1$ 个 $1$，$1$ 个 $k+1$ 来完成，于是这种策略显然是最优的，那么 $s$ 能至多处理 $k\lfloor\frac{s}{2k}\rfloor+\min(s\bmod 2k,k-1)$ 个位置，当其不小于 $n$ 时就可以构造使得其答案为 `NO`。

特殊的，当 $s=k$ 时答案为 `YES`。

---

## 作者：pufanyi (赞：1)

由于是区间问题，我们考虑先将其转换为两点问题。考虑 $b_i=\sum_{j=1}^i a_i$，于是我们有 $\begin{cases}b_0=0\\b_n=s\end{cases}$。如果存在一对 $\left<i,j\right>$ 满足 $b_j-b_i=k$，那显然这个农场是幸运的。由于 $a_i>0$，每一个 $b_i$ 都是两两不同的。于是问题就转化成了，在 $1\sim s$ 中选出 $n$ 个数，使得这些数中不存在 $k$，且不存在一对 $\left<i,j\right>$ 满足 $j-i=k$。

下面我们贪心地考虑最多能选出多少个满足条件的数。

考虑到不能有 $k$ 这个条件，我们把 $k$ 的倍数和不是 $k$ 的倍数的数分开讨论，对于不是 $k$ 倍数的数，如果我们选了 $x$，那我们就不能选 $x+k$ 了（如果 $x+k\le s$ 的话）。于是我们考虑对每 $2k$ 个划分为一段，这样除了最后一段不满的，就有 $\left\lfloor\frac{s}{2k}\right\rfloor$ 段，而每一段我们可以贪心地选择 $1\sim k-1$，这样保证了最后留下的 $s\ \mathrm{mod}\ 2k$ 个数能尽量多取，于是这对于不是 $k$ 倍数的数，这 $\left\lfloor\frac{s}{2k}\right\rfloor$ 段可以选择 $\left\lfloor\frac{s}{2k}\right\rfloor\cdot(k-1)$ 个数。然后我们考虑是 $k$ 倍数，由于不能选择 $k$，我们只能选择 $2k$ 的倍数。这样这 $\left\lfloor\frac{s}{2k}\right\rfloor$ 段我们就能选取 $\left\lfloor\frac{s}{2k}\right\rfloor$ 个数。于是前 $\left\lfloor\frac{s}{2k}\right\rfloor$ 段一共最多能选取 $\left\lfloor\frac{s}{2k}\right\rfloor\cdot k$ 个数。

然后我们考虑最后留下的 $s\ \mathrm{mod}\ 2k$ 个数，我们不难发现最多只能选这里面前 $k-1$ 个数了（第 $k$ 个数不能选了是因为我们已经选了原序列中第 $k\cdot \left\lfloor\frac{s}{2k}\right\rfloor$ 个数了）。因此，这一部分最多能选 $\min\left\{s\ \mathrm{mod}\ 2k, k - 1\right\}$ 个数。

然而上面那段忘记了一个条件，那就是第 $s$ 个数是必须要选的，因为 $b_n=s$。但是大部分情况下这没有关系，因为如果第 $s$ 个数没有选的话，那我们肯定选择了第 $s-k$ 个数（因为我们是贪心选最多的，如果第 $s-k$ 个数和第 $s$ 个数都不选的话，那就不是最优的了，因为可以选一个使所选数加一），于是我们把第 $s-k$ 个数删去，选择第 $s$ 个数即可。唯一的影响在于如果当 $s=k$ 的时候，那既然第 $s$ 个数一定要选，那么答案就只能是 `YES` 了。

所以，我们最终只要比较 $\left\lfloor\frac{s}{2k}\right\rfloor\cdot k+\min\left\{s\ \mathrm{mod}\ 2k, k - 1\right\}$ 与 $n$ 的大小即可得出答案。

---

## 作者：Little09 (赞：1)

原题是把 $s$ 个东西放到 $n$ 个箱子里，要求每个箱子不空，请问是不是满足所有放法都存在一个子段和为 $k$。

考虑长度为 $n$ 的序列 $a$ 是放置的数组，求出前缀和数组 $b$，转化为 $b$ 中元素两两不同且存在两个数差 $k$。也容易转化到在 $0\sim s$ 中选 $n+1$ 个数，其中 $0$ 和 $s$ 必选，是否存在一种选数方案，使得不存在两个数相差 $k$。若有这样的方案，那么就不合法。

我们直接把 $0\sim s$ 里相差 $k$ 的数两两连边，问题也就是这个图的最大独立集。发现这个图是若干条链，讨论一下链的长度就行了。

```cpp
ll s,n,k;
void work()
{
	cin >> s >> n >> k;
	if (k>s)
	{
		printNO;
		return;
	}
	if (k==s)
	{
		printYES;
		return;
	}
	ll t=(s+1)%k,a=(s+1)/k;
	ll ans=t*((a+2)/2)+(k-t)*((a+1)/2);
	if (n+1<=ans) printNO;
	else printYES;
}
```

哦对了，vp 的时候 5ab 压哨绝杀，膜拜。

---

## 作者：SnowFlavour (赞：0)

# 思路 1
考虑到我们其实就是要找到一种方式，使得没有办法让一个区间等于 $k$。我们考虑极端情况，首先放 $k-1$ 个 $1$，再放 $1$ 个 $k+1$，重复这个过程直到放满。其实就变成了能不能把这个方式放好。这个思路可以做到 $O(1)$ 判断。

由于我们是以 $k-1$ 个 $1$ 和 $1$ 个 $k+1$ 为一组，所以他的循环周期就是 $k$。那么，如果最后还剩下一部分，就全都放 $1$，因为反正加不到 $k$。那么，我们其实就需要这么多个：
$$k \left \lfloor \frac{n}{k}  \right \rfloor +n $$
而我们实际有 $s$ 个，比较即可。

这个做法比较快，但是需要注意一个特判：
> 当 $s=k$ 的时候，答案是 `YES`，原因显然。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int main(){
    int tt;
    cin>>tt;
    for(int h=1;h<=tt;h++){
        long long s,n,k;
        cin>>s>>n>>k;
        if(k==s)cout<<"YES"<<endl;
        else if(s-n>=n/k*k)cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
}
```
结论题一般代码都很简单，所以我应该不需要加注释了罢

# 思路 2（无代码）
这个思路我是听别人告诉我的，自己还没有实现。

转化一下题意，就是有 $s$ 个元素，左右各插一个板子，再从中间插 $n-1$ 个板子，把这些元素分成 $n$ 个部分。这样就相当于没有两个板子的差距是 $k$。

注意到在这里，两个位置不同余的板子是不用考虑的，所以我们只要对于所有位置满足 $a_i \equiv a_j\pmod k$ 的集合进行枚举即可。我们会发现，其实最后每种同余的情况只能拿到 $\left \lfloor \cfrac{x}{2} \right \rfloor$ 个，其中 $x$ 这种同余的情况的可能板子的数量。不过其实真正实现的时候我们只要算出来枚举的情况就行，没必要大动干戈真的枚举一遍，这样我们对答案求和就行。复杂度略高。代码还没写出来，有兴趣自行尝试。

---

## 作者：iPhoneSX (赞：0)

## 结论题
看到这个题 $s$， $n$， $k$ 都很巨大，猜想一定能 $O(1)$ 判断一个农场是不是可行。

首先有几种情况绝对不行，即 $k>s$ 时，$s<n$ 时以及 $\lfloor \frac{s}{n} \rfloor>k$  时。非常容易证明，所以不再多讲。

再考虑最少需要多少奶牛，才能做出一组使任何一个区间的和都不等于 $k$ 的方案。先把 $n$ 个篱笆每个放一只奶牛，这样会有一个长度为 $k$ 的区间和为 $k$。若给区间内的任意篱笆加上 $x$，则会有一个它的一个长度为 $k-x$ 的子区间和为 $k$，所以最少需要在其中一个篱笆上加上 $k$，才能保证整个长度为 $k$ 的区间内不存在任何子区间和为 $k$。于是有了一种构造方法：每隔 $k-1$ 个奶牛数为 $1$ 的篱笆，放一个奶牛数为 $k+1$ 的篱笆。  

这种策略最少的奶牛数为 $n+\lfloor \frac{n}{k} \rfloor*k$。如果这个数量小于等于 $s$，那么这个农场一定是不可行的。剩下的情况都可行。

代码如下，很简短：
```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<iostream>
#include<list>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
#define ll long long
#define DBG(x) cout << #x << "=" << x << endl
#define inf 0x3f3f3f3f
#define mod 1000000007
#define N 1000005
using namespace std;
template <typename T>
void read(T& x) {
    x = 0;
    ll t = 1;
    char ch;
    ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            t = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    x *= t;
}
template <typename T, typename... Args>
void read(T& first, Args&... args) {
    read(first);
    read(args...);
}
template <typename T>
void write(T y) {
    T x = y;
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}
template <typename T, typename... Ts>
void write(T arg, Ts... args) {
    write(arg);
    if (sizeof...(args) != 0) {
        putchar(' ');
        write(args...);
    }
}
ll t,s,n,k;
int main(){
	read(t);
	for(int i=1;i<=t;i++){
		read(s,n,k);
		if((k>s)||(s<n)||(s/n>k)||(k>n&&k!=s)){
			cout<<"NO"<<endl;
		}
		else{
			if(k<=n&&n+(n/k)*k<=s){
				cout<<"NO"<<endl;
			}
			else{
				cout<<"YES"<<endl;
			}
		}
	}
    return 0;
}
``````

---


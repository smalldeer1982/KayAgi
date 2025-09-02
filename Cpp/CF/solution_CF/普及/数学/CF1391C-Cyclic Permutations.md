# Cyclic Permutations

## 题目描述

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

Consider a permutation $ p $ of length $ n $ , we build a graph of size $ n $ using it as follows:

- For every $ 1 \leq i \leq n $ , find the largest $ j $ such that $ 1         \leq j < i $ and $ p_j > p_i $ , and add an undirected edge between node $ i $ and node $ j $
- For every $ 1 \leq i \leq n $ , find the smallest $ j $ such that $ i         < j \leq n $ and $ p_j > p_i $ , and add an undirected edge between node $ i $ and node $ j $

In cases where no such $ j $ exists, we make no edges. Also, note that we make edges between the corresponding indices, not the values at those indices.

For clarity, consider as an example $ n = 4 $ , and $ p =       [3,1,4,2] $ ; here, the edges of the graph are $ (1,3),(2,1),(2,3),(4,3) $ .

A permutation $ p $ is cyclic if the graph built using $ p $ has at least one simple cycle.

Given $ n $ , find the number of cyclic permutations of length $ n $ . Since the number may be very large, output it modulo $ 10^9+7 $ .

Please refer to the Notes section for the formal definition of a simple cycle

## 说明/提示

There are $ 16 $ cyclic permutations for $ n = 4 $ . $ [4,2,1,3] $ is one such permutation, having a cycle of length four: $ 4 \rightarrow 3 \rightarrow 2 \rightarrow 1 \rightarrow 4 $ .

Nodes $ v_1 $ , $ v_2 $ , $ \ldots $ , $ v_k $ form a simple cycle if the following conditions hold:

- $ k \geq 3 $ .
- $ v_i \neq v_j $ for any pair of indices $ i $ and $ j $ . ( $ 1 \leq i < j \leq k $ )
- $ v_i $ and $ v_{i+1} $ share an edge for all $ i $ ( $ 1 \leq i < k $ ), and $ v_1 $ and $ v_k $ share an edge.

## 样例 #1

### 输入

```
4```

### 输出

```
16```

## 样例 #2

### 输入

```
583291```

### 输出

```
135712853```

# 题解

## 作者：绝顶我为峰 (赞：9)

~~本题有多种推柿子方法，都可以通过本题~~

### 方法一：暴力+ OEIS

暴力算出前 10 项的值，直接丢进 OEIS 查询，希望能有

~~然后居然真的有~~

[就是这个序列](https://oeis.org/A059204)

发现这个序列通项公式是 $f(n)=n!-2^{n-1}$ ，写出来，没了（

~~但是这个方法的缺点是在考场上并不能使用~~

---

### 方法二：找规律

发现只要找到一组 $i,j,k$，使得 $i<j<k,a_i>a_j,a_k>a_j$，那么序列就是合法的

容易得出如果一个序列是不合法的，当且仅当这个序列是单峰的

序列总数为 $n!$，单峰序列怎么计算呢？

考虑枚举峰值，显然峰值处只能是序列最大值，我们设峰值在第 $i$ 位

然后我们考虑其他数字的位置，显然我们要把剩下的 $n-1$ 个数分成两组，一组有 $i-1$ 个数，另一组有 $n-i$ 个数，那么答案就是 $\tbinom{n-1}{i-1}$

总的不合法序列数： $\sum_{i=1}^n\tbinom{n-1}{i-1}=\sum_{i=0}^{n-1}\tbinom{n-1}{i}=2^{n-1}$

这个式子和上面找到的通项公式是一致的

---

## 作者：寒鸽儿 (赞：7)

#### 思路及一些证明

~~十分毒瘤的一道题目 , 10号打vp和tommy两个人弄了1个多钟头才弄出来。~~

通过对于顺序数据及小数据的枚举不难发现 , 如果是一个单峰或者单调的排列 , 那么就没有环 , 否则一定有。  

下面来证明(以下 , 单峰包括单调) : (证明过于毒瘤不想看的可以跳过)

$\texttt{Axiom1}$  

非单峰序列一定能被划分为若干个单峰序列。

$\texttt{Lemma1}$

在 $n$ 个节点的无向连通图中要存在环 , 至少要包含 $n$ 条边。  

$\texttt{Prof.}$ 

连通图中 , 若仅含 $n - 1$ 条边则是树 , 再加入更多的边形成环。  

$\texttt{Lemma2}$  

由题中方式生成的排列必为连通图。  

$\texttt{Theorem1}$  

生成的图含有环当且仅当排列为非单峰(包括单调 , 即这个峰在排列的一端)。  

$\texttt{Prof.}$ 先证必要性 , 再证充分性。  

必要性证明 :   $\texttt{i.e}.$ 对于形成环的图必为非单峰排列。  

$\texttt{Proof:}$ 由反证法  

以反证为目的假设存在单峰排列能形成有环的图。

对于单峰的排列 , 显然在峰的左侧每个下标为 $i$ 结点只向  $i+1$ 连一条边 , 因为右边的点的值都小于它。在峰的右侧每个下标为 $i$ 结点只向  $i-1$ 连一条边。峰不主动向其它点连边。这样总共只有 $n - 1$ 条边。由 $\texttt{Lemma1}$ 及 $\texttt{Lemma2}$ , 这样生成的图必然是一棵树。$\texttt{Contradiction!}$

则假设不成立 , 原命题成立。  $\texttt{Q.E.D.}$

充分性证明 $\texttt{i.e.}$ 非单峰排列生成的图中必定存在环。

$\texttt{Proof:} $ 对于长度为 $n$ 的排列。由 $\texttt{Axiom1}$ 将非单峰排列划分为若干个单峰子断。在每个单峰子段由 $\texttt{Lemma1}$ 和 $\texttt{Lemma2}$ 为一棵树 , 而谷中的元素将树连接成一棵更大的树。这样就有 $n - 1$ 条边。对于多个峰 , 峰之间显然存在大小关系。以最小的峰为例 , 它将与相邻的更大的峰有一个连边。这样至少有了 $\geqslant n$ 条边。由 $\texttt{Lemma1}$ , 这样的图中必然存在环。$\texttt{Q.E.D.}$

$\texttt{Q.E.D.}$



那么本题就是求非单峰排列的数量。正难则反 , 我们考虑求出单峰排列的数量 , 用全排列数 $n!$ 减去之。  

对于大小为 $n$ 的排列 , 假设峰在第 $k$ 个位置 , 即$p_k = n$。将剩下的元素分配到 $1...k-1$ 和 $k+1, ..., r$ 两个部分。分配完成后由于定序只有一种排列方案。分配的方式就是将 $1,...,n-1$ 分配到两个集合中 , 即 $\binom{n}{k-1}$ 种方法。  

记 $f(n)$ 为大小为 $n$ 的单峰排列个数 , 则 : 
$$
f(n) = \sum_{k \in [1,n]} \binom{n-1}{k-1} = 2^{n - 1}
$$
故答案即为 $n! - 2^{n-1}$ 

#### code

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll p = 1000000007;

ll gen(int n) {
	ll ans = 1, dd = 1;
	for(int i = 1; i <= n; ++i) ans = ans * i % p;
	for(int i = 1; i < n; ++i) dd = dd * 2 % p;
	return ((ans - dd) % p + p) % p;
}

int main() {
	int n;
	cin >> n;
	cout << gen(n) << endl;
	return 0;
}
```



---

## 作者：KSToki (赞：6)

这是一道数学题，我好像跟巨佬们的思路都不太一样。对于所有的排列，我们分为 $2$ 种情况：$1$ 在或不在第 $1$ 或第 $n$ 个位置。

如果 $1$ 不在第 $1$ 或第 $n$ 个位置，那么其必然会与前后两个数连一条边，而这两个数不相等（即有大小关系），这两个数也会连一条边，形成环。所以 $1$ 不在第 $1$ 或第 $n$ 个位置的所有情况都成立共有 $(n-1)!\times(n-2)$ 个这样的排列。

如果 $1$ 在第 $1$ 或第 $n$ 个位置，那么这两个位置等价，我们讨论一种情况将答案乘 $2$ 即可。此时我们剩下 $n-1$ 个连续的位置，$2$ 成为了新的 $1$，继续讨论即可，边界为 $n=1$、$n=2$ 时答案为 $0$。

代码中用的是递推，预处理阶乘，记得 `long long`。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
const ll Mod=1e9+7;
ll jc[1000001]={1},f[1000001];
int main()
{
	cin>>n;
	for(register int i=1;i<=n;++i)
	    jc[i]=jc[i-1]*i%Mod;
	for(register int i=3;i<=n;++i)
	    f[i]=(jc[i-1]*(i-2)%Mod+2*f[i-1])%Mod;
	cout<<f[n]<<endl;
	return 0;
}
```


---

## 作者：引领天下 (赞：2)

答案题~~OEIS题~~。

solution:

直接暴力跑出 n 较小的几个数据，甩到 OEIS 上去搜。

然后你会发现搜到了一个通项公式： $n!-2^{n-1}$ 。

于是直接暴力求就好了。

接下来我们说一下如何证明这个东东：

直接正向考虑有哪些情况会成环比较困难，我们从反面考虑。

通过对题面的观察，我们发现当一个排列不成环的时候， $1$ 要么在第 $1$ 位，要么在第 $n$ 位。

同理 $2$ 要么在剩下的 $n-1$ 位中的第一位，要么在最后一位……

如此下去，知道最后一个数只有一种放法（前面的 $n-1$ 个位置确定了，第 $n$ 个数的位置也就随之确定了）。

于是不合法的方案数为 $2^{n-1}$ 。

方案总数为 $A^n_n=n!$ 。

故合法的方案数量为 $n!-2^{n-1}$ 。

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int main(){
	register int n;
	scanf("%d",&n);
	register long long ans=1,res=1;
    for (register int i=1;i<=n;i++)ans=1ll*ans*i%mod;
	for (register int i=2;i<=n;i++)res=(res<<1)%mod;
    ans=(ans+mod-res)%mod;
    printf("%d\n",ans);
}
```

---

## 作者：人间凡人 (赞：1)

一眼看去就像是一道找规律题，然后我们发现此题形式为输入一个数，输出一个数。

$ok$，话不多说，开始了暴力找规律。

苦苦手打暴力中 $...$

若 $n=3$	输出 $2$ 若 $n=4$	输出 $16$

若 $n=5$	输出 $104$ 若 $n=6$	输出 $688$

若 $n=7$	输出 $4976$ 若 $n=8$ 输出 $40192$

~~菜死的我推了半天仍然找不出啥规律~~

只好求助了一下 **OEIS**

![](https://cdn.luogu.com.cn/upload/image_hosting/j65b4emh.png?x-oss-process=image)

可见 $a(n)=n!-2^{(n-1)}$       

### OK!

**注意:** 因为有减号，所以可能会出现负数的情况，别忘了考虑！

$Code:$
```cpp
#include<bits/stdc++.h>
#define Mod 1000000007
using namespace std;
long long ans,n,sum;
int main(){
    scanf("%lld",&n);
    ans=sum=1;
    for(int i=2;i<=n;i++)ans=ans*i%Mod;	//求n!
    for(int i=1;i<n;i++)sum=sum*2%Mod;	//求2的幂
    ans=((ans-sum)%Mod+Mod)%Mod;  //防止为负数
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：te5555 (赞：1)

## 题目描述
对于一个$n$的排列p，构造一个图，连接$i j$，当且仅当 $j$是最大的小于$i$的数且满足$p_j>p_i$或者$j$是最小的大于$i$的数且满足$p_j>p_i$ ，边是无向边，当这个图中有至少一个三元以上的环时，我们称这个排列是好的，求$n$的排列中好的排列的数量

## 分析
注意到对于排列中第$i$个数,我们要找的前面第一个比他大的和后面第一个比他大的

我们不妨画一个折线图来看看

例如，$p=\{3,1,2,4\}$

![](https://cdn.luogu.com.cn/upload/image_hosting/ak94mz6z.png)

发现连的边有$(1,2),(1,3),(2,4),(2,3)$

把这些边连上
![](https://cdn.luogu.com.cn/upload/image_hosting/yqhzimgp.png)

我们发现成环了

**大胆猜测，只要有凹的排列，就必然有环**

证明很简单：一个极小值必然与左右连边，右边的数必然与左边连，这样至少有三元环

于是问题就很简单了，我们都知道排列个数，那么只需要减去不满足条件的排列即可

一个不是好的排列没有在中间的极小值，也就是说它是凸的（单调的我们也认为是凸的）

凸排列最大值必然为单峰，考虑最大值左边的排列，由于是单调的，不需要考虑顺序，设最大值在第$i$位，则左边的方案数为$\left( \begin{array}{c}
	n-1\\
	i-1\\
\end{array} \right) $

所有不符合条件的方案数为
$$ \sum_{i=0}^{n-1}{\left( \begin{array}{c}
	n-1\\
	i\\
\end{array} \right) =2^{n-1}}$$

故
$$
ans=n!-2^{n-1}
$$

---

## 作者：Ryo_Yamada (赞：1)

结论题。比赛的时候推来推去推假了，最后勉强过的/kk

理解题意：对于 $i$ ，找到最大的 $j$ 满足 $a_i < a_j, i < j$ ，建无向边 $i-j$。找到最小的 $j$ 满足 $a_i < a_j, j < i$ ，建无向边 $i-j$。

对于 $n$ 的全排列，有多少种排列建图后有环。

发现中间最大的向两边递减的不行，如 $2, 4, 5, 3, 1$。这种情况有 $2 ^ {n-1}$ 种，所以答案就是 $A^n_n - 2 ^ {n-1}=n! - 2 ^ {n-1}$。

$\text{Code}$：

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

const int mod = 1e9 + 7;

long long ksm(long long b, long long p) {
	long long ret = 1;
	while(p) {
		if(p & 1) {
			ret = (ret * b) % mod;
		}
		p >>= 1;
		b = (b * b) % mod;
	}	
	return ret;
}//快速幂

long long k[1000005];

int main() {
	long long n;
	cin >> n;
	k[0] = 1;
	for(int i = 1; i <= n; i++) k[i] = k[i - 1] * i % mod;//计算阶乘
	long long m = k[n];
	long long ans = ((m - ksm(2, n - 1) + mod) % mod);
	cout << ans << endl;
	return 0;
}

```


---

## 作者：czh___ (赞：0)

### 题目大意：
给定一个 $n$，表示一个序列的长度，这个序列必须是 $1$ 到 $n$ 排列组合的某个序列。然后求对于一个 $n$ 而言有几个序列是**好**的。分析题意可以发现，一个序列存在**谷**表示序列是好的。即序列存在 $X + a$，$X$，$X + b$（$a，b > 0$），那么这本身就可以构成一个环，满足题意。由于答案可能很大要对 $10^9+7$ 取模。

### 简析：
首先打表找规律，可以得到前几项：
1. $n = 1$ 时，$ans = 0$。
2. $n = 2$ 时，$ans = 0$。
3. $n = 3$ 时，$ans = 2$。
4. $n = 4$ 时，$ans = 16$。

然后我们看看 $3$ 的时候的序列，合法的将会加粗：

1 2 3

1 3 2

**2 1 3**

2 3 1

**3 1 2**

3 2 1

根据题意，只要出现谷即为合法的，我们把 $3$ 的序列都加 $1$，然后去推导 $4$ 的序列。首先 $3$ 的序列每个元素加 $1$，不影响最后的答案，因为上述提到的 $X$ 是为任意自然数。加一后得：

2 3 4

2 4 3

**3 2 4**

3 4 2

**4 2 3**

4 3 2

然后我们用排列组合的方式插入 $1$（以 2 3 4 为例），可以得到：

(1) 2 3 4

**2 (1) 3 4**

**2 3 (1) 4**

2 3 4 (1)

然后这里可以发现！！！只要 $1$ 不是头尾，那必然就是合法态！$3$ 的序列每一个组合都可以这样推导。所以设某一个序列 $n$ 共有 $k$ 个排列组合，那么 $k+1$ 必然有大于 $k \times (n - 2)$ 种。每一种组合都加 $1$，然后把 $1$ 插入到不是头尾的位置。
当然还有另外一种情况，就是本身就已经是合法态，那么插入到头尾也是合法的，比如这样：

**(1) 4 2 3**

**4 2 3 (1)**

所以，设 $n$ 的序列的有k种排列组合方式，且 $k$ 中有 $ans$ 个合法态，那么 $n+1$ 的就会有 $(k \times (n - 2) + ans \times 2)$ 种方案。左边的对应在中间插入 $1$ 的方案计数，右边的 $ans \times 2$ 对应的是原先合法态末尾的方案。加在一起然后递推即可。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	ll n,ans=0;
	cin>>n;
	ll k=2;
	for(int i=3;i <= n;i++) {
		ans=(k*(i-2)+ans*2)%MOD;
		k=k*i%MOD;
	}
	cout<<ans;
    return 0;
}
```

[改编于](https://blog.csdn.net/qq_44754132/article/details/108229076?ops_request_misc=&request_id=&biz_id=102&utm_term=Cyclic%20Permutations&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-108229076.142^v100^pc_search_result_base5&spm=1018.2226.3001.4187)

---

## 作者：Fairicle (赞：0)

首先考虑只有 $3$ 个顶点的情况。可以发现只有当 $p_2<p_1$ 且 $p_2<p_3$ 时可以构成环。

那么推而广之，对于 $n>3$，只需要有任意一个 $k$ 满足 $p_k<p_{k+1}$ 且 $p_k<p_{k-1}$，即需要有一个谷。

考虑计算这样的方案数，发现正面做不是很好做，考虑排除不合法的方案。不合法的方案就是先递增后递减（可以看做在 $0$ 和 $n+1$ 的位置都放了一个 $0$）。

那么只需要考虑最大值在不同位置的情况，加起来即可。

当最大值在第 1 位时，剩下 $n-1$ 个数需要在左边选 0 个数，在右边选 $n-1$  个数排出单调递减的序列，有 $C^{0}_{n-1}*C^{n-1}_{n-1}$ 种方法也就是 $C^{0}_{n-1}$。

当最大值在第 2 位时，剩下 $n-2$ 个数要在左边选出一个数，右边选出 $n-2$ 个数，即 $C^{1}_{n-1} * C^{n-2}_{n-2}$ 也就是 $C^{1}_{n-1}$。

当最大值在第 3 位时，同理有 $C^{2}_{n-1}$ 种方法...

所以不合法方案数是$\sum_{i=0}^{n-1}C^{i}_{n-1}$。

根据二项式定理我们可以知道这个式子是 $(1+1)^{n-1}$。

但是这个需要一点点数学基础，所以不妨换个角度思考。这个式子的直观意义就是，从 $n-1$ 个数中取 $0,1,2,...,n-1$ 个数的方案数之和。那么问题就可以转化为——有 $n-1$ 个数，每个数可以取或不取，有多少种方案数。那么对于每个数都有两种选择，根据乘法原理可以很轻松的得到这样的方案数是 $2^{n-1}$。

于是，合法方案数就是总方案减去不合法的，即 $n!-2^{n-1}$。

代码很好写，就不给了。

---

## 作者：过往梦魇之殇 (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1391C)

~~前置芝士：OEIS大法~~

**思路简述：**

做题时也没想过怎么去严谨证明啊 ~~（然后被爆d了qwq）~~

思路就是先暴力打出前几项$n$的值，

然后丢进$OEIS$搜，

找到通项公式$n=n!-2^{n-1}$

然后进行计算即可。

~~不会的自行bfs~~

但是好像不太好？证明可以去看楼顶神犇的题解。

**代码展示：**
```cpp
#include<bits/stdc++.h>
#define int long long
#define re register
using namespace std;
const int modd=1e9+7;
int n,mul,fac;
signed main(){
    scanf("%lld",&n);
    mul=fac=1;
    for(re int i=2;i<=n;++i){
        mul=(mul*2)%modd;
        fac=(fac*i)%modd;
    }
    int ans=fac-mul;
    if(ans<0){
        ans+=modd;
    }
    printf("%lld\n",ans);
    return 0;
}
```
> $Thanks$ $For$ $Watching!$

---

## 作者：tengkaize (赞：0)

实际画一下就容易发现当有一段数字**先单减后单增**时一定会出现循环，换句话说出现了“山谷”就是符合要求的排列。

这种排列有个名字叫 non-unimodal permutations，[OEIS 上有](https://oeis.org/A059204)，有 $n$ 个数字的这种排列数量为 $n!-2^{n-1}$，所以我们输出 $n!-2^{n-1}\pmod{10^9+7}$ 即可。

证明这个结论需要一点反向思考，直接求 non-unimodal permutations 的数量不易，用 $1\sim n$ 的全排列数量减 unimodal permutations (**整个排列**先单增后单减) 的数量即为所求。

要求前面有 $k+1\ (0\le k\le n - 1)$ 个数是单增的，后面剩下的 $n-k$ 个数是单减的排列数量，因为大小顺序固定，所以等价于求 $n-1$ 中选 $k$ 的组合数，即 $\binom{n-1}{k}$

把所有 $\binom{n-1}{k}$ 加起来即为 $n$ 个数的 unimodal permutations 的数量，为

$$\sum_{k=0}^{n-1}\binom{n-1}{k}$$

运用二项式定理可得原式等于 $2^{n-1}$，证毕

代码如下

```cpp
#include <cstdio>

using namespace std;

typedef long long ll;

void r(ll& i) {
    i = 0;
    int c = getchar();
    for (; c < '0' || '9' < c; c = getchar())
        ;
    for (; '0' <= c && c <= '9'; c = getchar())
        i = i * 10 + (c - '0');
}

constexpr ll MOD = 1000000007;

ll n;
ll fact[1000001] = {1}, p2[1000001] = {1};

int main() {
    r(n);
    for (ll i = 1; i <= n; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
        p2[i] = p2[i - 1] * 2 % MOD;
    }
    printf("%lld\n", ((fact[n] - p2[n - 1]) % MOD + MOD) % MOD);
    return 0;
}
```


注：

- 第四段的 $k+1$ 其实是个细节问题，主要看你怎么处理单增和单减的分界点
- OEIS 神器，用暴力把 $n=5$ 的情况求出来查一下就出来了
- 考场上当然是猜结论啊，~~谁证啊~~
- cyclic permutations = non-unimodal permutations

---

## 作者：kradcigam (赞：0)

我们考虑什么样的情况没有环。

首先，有一个性质是这样的：对于任意的 $i(i\geq 3)$，如果 $a_i$ 是前 $i$ 个数中的最大数或最小数，就必定没有环。

如果证明呢？我们考虑反证法。

假设对于任意一个 $z(z\geq 3)$ 如果它不是前 $z$ 个数中的最大数或最小数的话，就必定有一个 $x$ 是最小的满足 $a_x<a_z$ 的数，$y$ 是最大满足 $a_y>a_z$ 的数。那么 $x \leftrightarrow z,y \leftrightarrow z$。

下面，我们分情况讨论：

- 如果 $x>y$，那么 $y$ 必定为最大的满足 $a_y > a_x$ 的数，因为 $a_y > a_z$ 然后 $a_z > a_x$；

- 如果 $x<y$，那么 $x$ 必定为最小的满足 $a_x < a_y$ 的数，因为 $a_x < a_z$ 然后 $a_z < a_y$。

证毕。

然后我们考虑这样的序列有多少种，我们这么考虑，第 $n$ 个数可能是 $1\sim n$ 中的最大数或最小数。

- 如果是最大数，那么剩余的数为 $1\sim n-1$；
- 如果是最小数，那么剩余的数位 $2\sim n$。

我们把剩下的数想象成一个双端队列，问题等价于让你求这个队列让你从左边取或右边取，一共有多少种取法。

我们每次可以从左边取或右边取，一共去 $n$ 次，所以答案为 $2^n$。

所以，这题的答案为总的排列数 $n!$ 减去不合法的排列数 $2^n$。

```cpp
const ll mod=1e9+7;
ll pw(ll x,ll y){
	ll ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}return ans;
}
int work(){
	ll n,ans=1;read(n);
	for(int i=1;i<=n;i++)ans=ans*i%mod;
	ans=(ans-pw(2,n-1)+mod)%mod;//防止负数
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：白鲟 (赞：0)

## 题目分析
这题面很长……大概就是每个点朝两侧第一个大于它的位置连边，问有环的方案数。  

大概思考一下，可以发现对于某个点，若左右两边都有大于它的数，那么必定存在环。那么我们要计算这样的方案数，容易想到使用总方案数减去没有这样的一组数存在的方案数。  

而什么情况不存在这样的一组数呢？答案是这个排列是类似于“合唱队形”的，也就是先递增再递减。而中间的峰值明显应该为 $n$。那么对于除了 $n$ 外的 $n-1$ 个数，每个数都有两种放法：在 $n$ 左侧或在 $n$ 右侧，且若所有数关于 $n$ 的相对位置确定后，整个排列实际上已经确定了——因为要遵循序列的单调性。那么显然，不存在这样一组数的方案数总共为 $2^{n-1}$。而 $n$ 个数的排列总数为 $n!$，故答案即为 $n!-2^{n-1}$。  

## 代码
记得 `long long`。
```cpp
#include<cstdio>
using namespace std;
const int mod=1e9+7;
int n,ans=1,t=1;
int main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;++i)
	{
		ans=(long long)ans*i%mod;
		t=((long long)t<<1)%mod;
	}	
	printf("%d",(ans-t+mod)%mod);
	return 0;
}
```

---


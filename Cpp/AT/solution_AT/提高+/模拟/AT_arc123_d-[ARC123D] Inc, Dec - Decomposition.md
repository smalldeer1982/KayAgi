# [ARC123D] Inc, Dec - Decomposition

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc123/tasks/arc123_d

整数列 $ A\ =\ (A_1,\ \ldots,\ A_N) $ が与えられます。

整数列 $ B\ =\ (B_1,\ \ldots,\ B_N) $ および $ C\ =\ (C_1,\ \ldots,\ C_N) $ の組であって、以下の条件を満たすものを考えます：

- $ 1\leq\ i\leq\ N $ に対して $ A_i\ =\ B_i\ +\ C_i $ が成り立つ。
- $ B $ は広義単調増加である。つまり $ 1\leq\ i\leq\ N-1 $ に対して $ B_i\leq\ B_{i+1} $ が成り立つ。
- $ C $ は広義単調減少である。つまり $ 1\leq\ i\leq\ N-1 $ に対して $ C_i\geq\ C_{i+1} $ が成り立つ。

$ \sum_{i=1}^N\ \bigl(\lvert\ B_i\rvert\ +\ \lvert\ C_i\rvert\bigr) $ としてありうる最小値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ -10^8\leq\ A_i\leq\ 10^8 $

### Sample Explanation 1

最小値を与える整数列 $ B $, $ C $ として、例えば次があります： - $ B\ =\ (0,\ 0,\ 5) $ - $ C\ =\ (1,\ -2,\ -2) $ $ \sum_{i=1}^N\ \bigl(\lvert\ B_i\rvert\ +\ \lvert\ C_i\rvert\bigr)\ =\ (0+1)\ +\ (0+2)\ +\ (5+2)\ =\ 10 $ となっています。

### Sample Explanation 2

最小値を与える整数列 $ B $, $ C $ として、例えば次があります： - $ B\ =\ (0,\ 1,\ 2,\ 4) $ - $ C\ =\ (5,\ 3,\ 1,\ 1) $

### Sample Explanation 3

最小値を与える整数列 $ B $, $ C $ として、例えば次があります： - $ B\ =\ (-3) $ - $ C\ =\ (-7) $

## 样例 #1

### 输入

```
3
1 -2 3```

### 输出

```
10```

## 样例 #2

### 输入

```
4
5 4 3 5```

### 输出

```
17```

## 样例 #3

### 输入

```
1
-10```

### 输出

```
10```

# 题解

## 作者：Rosabel (赞：6)

稍微有点变式的 Slope Trick。不过还是很板。

这里默认大家都学过 Slope Trick 了。若没学过请跳转 CF13C。

考虑对 $b_i$ 作为 dp 值进行 dp。由于 $b_i+c_i=a_i$，所以 $b_i$ 一旦确定下来那么 $c_i$ 也随之确定。

观察取不同值的 $b_i$ 会对答案造成什么影响。当 $a_i\ge 0$ 时，

- 对于区间 $[-\infty,0]$，贡献是 $-b_i+c_i=a_i-2b_i$。即一个斜率为 $-2$ 的一次函数。
- 对于区间 $[0,a_i]$，贡献是 $b_i+c_i=a_i$。即一个斜率为 $0$ 的一次函数。
- 对于区间 $[a_i,+\infty]$，贡献是 $b_i-c_i=2b_i-a_i$。即一个斜率为 $2$ 的一次函数。

可以发现贡献是一个分段一次下凸函数，转折点在 $0,a_i$。同理，当 $a_i\le 0$ 时，贡献也是一个分段一次下凸函数，转折点在 $a_i,0$。

由于这些转折点的斜率变化均一样，所以可以通过维护转折点找到最优答案。

然后观察 $b_i$ 和 $c_i$ 的限制。$b_i$ 的限制即 $b_{i-1}\le b_i$。$c_i$ 的限制可以转化为 $b_{i-1}+(a_i-a_{i-1})\le b_i$。即 $b_i\ge b_{i-1}+\max(a_i-a_{i-1},0)$。对于后面的权值 $w=\max(a_i-a_{i-1},0)$，将 $i-1$ 和 $i$ 相对转折点差 $-w$ 个单位（在直线上看就是将 $[i,n]$ 的所有转折点整体向左平移 $w$ 个单位）可以将问题简化为 $b_{i-1}\le b_i$。然后就是 Slope Trick 板子了。实现是 $\Theta(n\log n)$ 的，瓶颈在优先队列。

[code](https://atcoder.jp/contests/arc123/submissions/58556830)

---

## 作者：Mikazuki_Munechika (赞：2)

我们首先可以钦定 $b_i \geq 0$ 且 $c_i \leq 0$ ，可以证明这个方案是一直合法的，如果 $ c_i > 0$ 则可以加到  $b_i$ 上去，反之亦然。

按照这个方案来算，我们发现 $\forall i \in [2,n]$ ，有 $b_i = b_{i-1}$ 或者 $c_i = c_{i-1}$ ，至于改变的是哪个，由 $a_i$ 与 $a_{i-1}$ 的大小关系决定。

此时答案就是关于 $b_1$ 的一个函数，因为 $b_i$ 可以 表示为 $b_1 + delta$ 产生，并且 $c_i$ 可以表示为 $c_1 + delta$ ，当 $i=1$ 时，$c_1=-b_1$，所以 $c_i$ 就可以表示为 $-b_1 + delta$ ，其绝对值也就是 $|b_1 - delta|$ 。所以答案就是一个 $\sum|b_1-p_i|$ 的形式，其中 $p_i$ 就是原先记录的 $a_i$ 和 $b_i$ ，答案的最小值也就是 $b_i = p_i$ 的中位数时的结果，带入即可。

---

## 作者：ZnPdCo (赞：2)

> 题目大意：给出长为 $n$ 的序列 $a$，构造长为 $n$ 的序列 $b,c$，要求：
>
> - $b$ 非严格递增。
> - $c$ 非严格递减。
> - $b_i+c_i=a_i$ 。
>
> 最小化 $\sum_{i=1}^n |b_i|+|c_i|$。

我们有一个结论：最优解一定满足 $\forall i$，$b_i=b_{i-1}\lor c_i=c_{i-1}$。关于这一点，目前题解区有部分证明错误了。下面是正确的证明过程：

考虑反证法，对于一个合法序列，假设 $b_x<b_{x+1}\land c_x>c_{x+1}$，我们定义两种操作：

- 操作 $1$：把 $b_1\sim b_x$ 加一，$c_{1}\sim c_x$ 减一；
- 操作 $2$：把 $b_{x+1}\sim b_n$ 减一，$c_{x+1}\sim c_n$ 加一。

上述两种操作都不会影响答案的合法性，而其中必定会有一个操作可以使得答案不会更劣：

- 当 $b_x< 0$ 时，操作 $1$ 不会更劣，因为 $\forall i\le x$，$|b_i|$ 只会减少 $1$，而 $|c_i|$ 最多增加 $1$。
- 当 $0<b_{x+1}$ 时，操作 $2$ 不会更劣。

所以**最优解一定满足** $\forall i$，$b_i=b_{i-1}\lor c_i=c_{i-1}$。假如我们确定了 $b_1$，得到了 $c_1$，就可以计算出整个序列：

当 $a_{i-1}\le a_i$ 时，令 $b_i\gets b_{i-1}+a_i-a_{i-1}$；当 $a_{i-1}>a_i$ 时，令 $c_i\gets c_i+a_i-a_{i-1}$。

问题是我们不知道 $b_1$ 的具体值，考虑模拟退火，可以通过。原因是上述方法得出的答案是单峰的，接下来进行证明：

上述转移方法实际上就是：

- $b_i\gets b_{i-1}+\max(0,a_i-a_{i-1})$；
- $c_i\gets c_{i-1}+\max(0,a_{i-1}-a_i)$。

答案是 $|b_1|+|a_1-b_1|+|b_1+\max(0,a_i-a_{i-1})|+|a_1-b_1+\max(0,a_{i-1}-a_i)|+\cdots$ 的形式。

实际上这个式子就是类似于：$\sum |x-p_i|$ 的一个式子，显然这个式子是单峰的。所以答案是单峰的。为了时间复杂度正确，写了三分：

```cpp
#include <bits/stdc++.h>
#define ll __int128
#define N 200010
using namespace std;
ll n, a[N], ans = -1;
ll calc(ll x) {
    ll b = x, c = a[1] - b, res = abs(b) + abs(c);
    for(int i = 2; i <= n; i++) {
        if(a[i] >= a[i - 1]) b += a[i] - a[i - 1];
        else c -= a[i - 1] - a[i];
        res += abs(b) + abs(c);
    }
    if(ans != -1) ans = min(ans, res);
    else ans = res;
    return res;
}
int main() {
    read(n);
    for(int i = 1; i <= n; i++) {
        read(a[i]);
    }
    ll l = -1e18, r = 1e18;
    while(l <= r) {
        ll mid = (l + r) / 2;
        ll midl = mid - 1;
        ll midr = mid + 1;
        calc(mid);
        if(calc(midl) < calc(midr)) {
            r = midl;
        } else {
            l = midr;
        }
    }
    write(ans);
}
```

---

## 作者：James0602 (赞：2)

[AT_arc123_d](https://www.luogu.com.cn/problem/AT_arc123_d)

**题目大意** ：给定序列 $A$，构造序列 $B,C$ 使得 $\forall i,A_i=B_i+C_i$，并且 $B$ 非严格递增，$C$ 非严格递减。最小化 $\sum_{i=1}^n(|B_i|+|C_i|)$。

首先有一个比较显然的贪心，就是如果说 $A_i>A_{i+1}$，则 $B_{i+1}=B_i,C_{i+1}=C_{i}+A_{i+1}-A_{i}$，否则 $C_{i+1}=C_i,B_{i+1}=B_i+A_{i+1}-A_{i}$。

证明：考虑反证法，假设 $\exists i,B_{i+1}>B_i\land C_{i+1}<C_i$，则将 $B_{i+1}-1,C_{i+1}+1$ 答案一定不会更劣。于是一直重复上述操作使得 $B_i=B_{i+1}$ 或 $C_{i}=C_{i+1}$。

接着我们考虑确定 $B_1,C_1$。一种感性一点的方式是使用三分，但有一种 $O(n)$ 的做法。

因为每次 $B,C$ 的增量是一定的，于是我们设 $B_{i+1}=B_{i}+p_{i+1}$，$C_{i+1}=C_i+q_{i+1}$。 

考虑设 $B_1=x,C_1=A_1-x$，于是我们就可以将 $B_i,C_i$ 用含 $x$ 的式子表示出来，接着将其带入原式，得 $\sum |x-u_i|+|v_i-x|=\sum|x-u_i|+|x-v_i|$，其中 $u_i,v_i$ 已知。

于是问题转化为考虑求 $\sum |x-a_i|$ 的最小值，其中 $a$ 已知。显然的想法是 $x$ 取所有 $a$ 的中位数。

考虑证明，不妨设 $a$ 非严格递增，则可以发现当 $x$ 在 $[a_1,a_n]$ 中优于在外面，并且在其中任意一个位置都有 $|x-a_1|+|x-a_n|=a_n-a_1$，于是可以将 $a_n,a_1$ 去掉，接着考虑 $a_2,a_{n-1}$，以此类推。


---

## 作者：shinkuu (赞：0)

感觉 slope trick 运用的不太熟练啊。不过还是创过去了。

首先考虑题目中给出的限制即 $b_i\le b_{i+1},c_i\ge c_{i+1}$，因为 $b_i+c_i=a_i$，转化成 $b_{i+1}\ge\max(a_{i+1}-a_i,0)+b_i$。

然后观察到 $|b_i|+|c_i|\le|b_i+c_i|=|a_i|$，当且仅当 $b_i,c_i$ 同正负的时候取得等号，否则若 $b_i>\max(a_i,0)$ 会多出 $b_i-\max(a_i,0)$，若 $b_i<\min(a_i,0)$ 会多出 $\min(a_i,0)-b_i$。

然后就可以考虑暴力 dp 算最少多出多少。$dp_{i,j}$ 表示当前枚举到第 $i$ 个数，$b_i=j$ 的最小代价。则 $dp_{i,j}=\min_{k<j-\max(a_i-a_{i-1},0)} dp_{i-1,k}+c(i,j)$。$c(i,j)$ 是上面提到的多出的贡献。

考虑优化。容易发现对于一个 $i$，$c(i,j)$ 形如一条斜率为 $-1$ 的射线拼上一段 $y=0$ 的线段再拼上一条斜率为 $1$ 的射线。容易联想到 slope trick。

考虑设 $f_{i,j}=\min_{k<j-\max(a_i-a_{i-1},0)}dp_{i,k}$，维护 $f_i$。不难发现 $f_i$ 单调不增。考虑斜率为 $-1$ 的射线对 $f_i$ 的影响，显然就是在 $\min(a_i,0)-1$ 的位置插入了一个折点。对于斜率为 $1$ 的，若会影响到当前最小值的那一段，则会删掉最后一个折点，再在 $\max(0,a_i)-1$ 位置插入一个折点，同时令最左侧最小值的位置为 $p$，则使答案增加 $(p-\max(a_i,0)+1)\times 2$。

此外每次 $k<j-\max(a_i-a_{i-1},0)$ 也就是整体向右平移一段距离，打个标记维护即可。

code：

```cpp
int n,m;
multiset<ll> st;
void Yorushika(){
	read(n);
	ll ans=0,d=0,lst=0;
	rep(i,1,n){
		int x;read(x);
		if(i>1){
			d+=max(x-lst,0ll);
		}
		int l,r;
		if(x>=0){
			l=0,r=x;
		}else{
			l=x,r=0;
		}
		ans+=abs(x);
		if(st.size()&&*prev(st.end())+d>=r){
			ans+=(*prev(st.end())+d-r+1)*2;
			st.erase(prev(st.end()));
			st.insert(r-d-1);
		}
		st.insert(l-1-d);
		lst=x;
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---


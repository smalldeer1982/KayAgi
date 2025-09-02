# [ARC126C] Maximize GCD

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc126/tasks/arc126_c

$ N $ 項からなる正整数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ が与えられます。あなたはこの数列に対して、次の操作を $ 0 $ 回以上 $ K $ 回以下行うことができます：

- $ i\in\ \{1,2,\ldots,N\} $ をひとつ選び、$ A_i $ に $ 1 $ を加える。

操作後の $ \gcd(A_1,\ A_2,\ \ldots,\ A_N) $ としてありうる最大値を求めてください。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 3\times\ 10^5 $
- $ 1\leq\ K\leq\ 10^{18} $
- $ 1\ \leq\ A_i\leq\ 3\times\ 10^5 $

### Sample Explanation 1

例えば以下のようにして、$ \gcd(A_1,\ A_2,\ A_3)\ =\ 5 $ を実現できます。 - $ i\ =\ 1 $ に対して $ 2 $ 回、$ i\ =\ 2 $ に対して $ 1 $ 回、$ i=3 $ に対して $ 1 $ 回の操作を行う。合計の操作回数は $ 4 $ 回で、$ K=6 $ 以下である。 - 操作の結果、$ A_1\ =\ 5 $, $ A_2\ =\ 5 $, $ A_3\ =\ 10 $ となり、$ \gcd(A_1,\ A_2,\ A_3)\ =\ 5 $ である。

### Sample Explanation 2

操作を一度も行わないことで、$ \gcd(A_1,\ A_2,\ A_3)\ =\ 10 $ を実現できます。

## 样例 #1

### 输入

```
3 6
3 4 9```

### 输出

```
5```

## 样例 #2

### 输入

```
3 4
30 10 20```

### 输出

```
10```

## 样例 #3

### 输入

```
5 12345
1 2 3 4 5```

### 输出

```
2472```

# 题解

## 作者：Avocadooo (赞：10)

题目大意就不再阐述了。

显然，当我们的 $ K $ 足够大时，我们可以直接将所有 $ A_i $ 都加到 $ A_{\max} $。然后如果仍然满足 $ K\geq N $，直接将所有的数一起加直到 $ K<N $。

如样例三：

```
Sample Input 3
5 12345
1 2 3 4 5
```

先用 $ 10 $ 次操作将 $ A_i $ 全变成 $ 5 $。然后整体每次加 $ 1 $。最后答案即为：

```
Sample Output 3
2472
```

考虑 $ K $ 不足以使得 $ A_i $ 全部相等的情形。但答案不具有单调性，不可二分。观察到 $ A_i \leq 3 \times 10^{5} $，那么显然满足 $ \gcd(A_1,A_2,\cdots,A_N)\leq 3 \times 10^5 $。考虑暴力枚举答案，并在相对较低的复杂度下判断是否可行。

接下来是如何判断。我们假设现在需要判断 $ x=\gcd(A_1,A_2,\cdots,A_N) $ 时是否满足最小操作次数小于等于 $ K $。

对于其中一个 $ A_i $，变为 $ x $ 的倍数需要 $ x-(A_i \bmod x) $ 次操作。那么总操作次数是：

$$ \sum\limits_{i=1}^n x-(A_i \bmod x) $$

$$ nx-\sum\limits_{i=1}^n (A_i \bmod x) $$

把 $ A_i $ 丢到桶里（这里 $ W $ 是值域）：

$$ nx-\sum\limits_{k=1}^{W} (k \bmod x)t_k $$

$ nx $ 的值显然可以 $ O(1) $ 求得，考虑如何求后半部分。

观察到 $ t_k $ 的系数 $ (k \bmod x) $ 具有周期性，如下图（以 $ x=8 $ 为例）：

![](https://s21.ax1x.com/2024/03/28/pFo9KzQ.png)


但这样有点难以计算，试着把上图延长一下，如下：

![](https://s21.ax1x.com/2024/03/28/pFoCifU.png)

显然绿色的区域是一个平行四边形（画的有点不标准，可以感性理解一下）。


先预处理出：

$$ c(m)=\sum\limits_{i=1}^mi\times t_i $$

$$ F(m)=\sum\limits_{i=1}^m t_i $$

与埃筛类似，枚举 $ x $ 的倍数 $ kx $。在区间 $ (kx-x,kx] $ 中的贡献即为

$$ c(kx)-c(kx-x)-(k-1)\times (F(kx)-F(kx-x)) $$

当然，如果 $ (W \bmod x) \neq 0 $，最后一段的贡献特殊处理一下即可。与上式类似。

总时间复杂度 $ \Theta(W \log \log W) $。代码如下：

```cpp
#include<bits/stdc++.h>
#define int ll
typedef long long ll;
using namespace std;
const int N=1000005;
int n,maxx;
int a[N],t[N],c[N],S[N];
ll k,delta,ans;
signed main()
{
	scanf("%lld %lld",&n,&k);
	for(int i=1;i<=n;i++) 
		scanf("%lld",a+i),maxx=max(a[i],maxx),++t[a[i]],++S[a[i]];
	for(int i=1;i<=n;i++) delta+=maxx-a[i];
	if(k>=delta) return printf("%lld\n",1ll*maxx+(k-delta)/(1ll*n)),0;
	for(int i=1;i<=maxx;i++) c[i]=c[i-1]+S[i]*i,t[i]+=t[i-1];
	for(int i=maxx;i>=1;i--)
	{
		ans=i*n;
		for(int j=i;j<=maxx;j+=i) ans-=(c[j]-c[j-i]-(j/i-1)*i*(t[j]-t[j-i]));
		if(maxx%i!=0) ans-=(c[maxx]-c[maxx/i*i]-(maxx/i)*i*(t[maxx]-t[maxx/i*i]));
		if(ans<=k) return printf("%lld\n",i),0;
	}
}
```

---

## 作者：Rolling_star (赞：5)

如果能把数列的所有数补到最大值的话，则说明直接向上加即可，直接输出。

如果这样的话说明 $\gcd(a_1,a_2,\cdots,a_n)\le \max a_i$。

如果想让数列的 $\gcd$ 被 $x$ 整除的话，说明数列的每一项都被 $x$ 整除，所以其最小操作次数为：

$$\sum_{i=1}^{n}x-(a_i\bmod x)$$

如果这个次数 $\le k$ 的话，说明 $x$ 是满足条件的 $\gcd$。

但是答案并没有单调性，考虑展开这个式子：

$$
\begin{aligned}
\sum_{i=1}^{n}x-(a_i\bmod x)&=nx-\sum_{i=1}^{n}(a_i\bmod x)\\
&=nx-\sum_{i=1}^{\max a_i}(i\bmod x)cnt_i
\end{aligned}
$$

其中 $cnt_i$ 为数 $i$ 出现的次数，后面的 $(i\bmod x)$ 是以 $x$ 为周期的，所以考虑维护一个 $\displaystyle f_n = \sum_{i=1}^{n} i\cdot cnt_i$ 和一个 $\displaystyle g_n = \sum_{i=1}^{n} cnt_i$，然后对于每个 $((k-1)x,kx]$ 来说它的贡献为 $kx\cdot (g_{kx}-g_{(k-1)x})-(f_{kx}-f_{(k-1)x})$ 求解即可，时间复杂度为 $O(nH_n)=O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define N 600005
#define int long long
using namespace std;

int n,k,a[N],Gcd,maxn,sum,cnt[N],f[N],g[N];

signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        scanf("%lld",a+i),maxn=max(a[i],maxn),cnt[a[i]]++;
    for(int i=1;i<=N-5;i++) f[i]=f[i-1]+cnt[i],g[i]=g[i-1]+cnt[i]*i;
    for(int i=1;i<=n;i++) sum+=maxn-a[i];
    if(sum<=k){
        cout<<maxn+(k-sum)/n;
        return 0;
    }
    for(int i=maxn;i>=1;i--){
        int tmp=0;
        for(int j=1;(j-1)*i<=maxn;j++)
            tmp+=(f[i*j-1]-f[i*(j-1)])*i*j-(g[i*j-1]-g[i*(j-1)]);
        if(tmp<=k){
            printf("%lld\n",i);
            return 0;
        }
    }
}
```

---

## 作者：do_while_true (赞：4)

把 $k$ 能够把所有的 $A$ 都添到 $\max A$ 的情况特判掉，这样答案只可能 $\leq \max A$．

开个桶，用前缀和维护值域上的 $A$ 的个数，$A$ 的和，枚举每一个可能的答案 $x$，然后枚举 $x$ 的倍数，可以快速统计所需的最小代价：假设枚举到 $kx$，要统计 $((k-1)x,kx]$ 区间内的花费，就是 $kx\cdot cnt-sum$．

复杂度是调和级数的。


```cpp
#include<iostream>
#include<cstdio>
#define int long long
typedef long long ll;
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 600010;
int n, mx, a[N], b[N];
ll s1[N], s2[N];
ll k;
signed main() {
	read(n); read(k);
	for(int i = 1; i <= n; ++i) read(b[i]), ++a[b[i]], mx = Max(mx, b[i]);
	ll sum = 0;
	for(int i = 1; i <= 2 * mx; ++i) s1[i] = s1[i-1] + a[i], s2[i] = s2[i-1] + a[i] * i;
	for(int i = 1; i <= n; ++i) sum += mx-b[i];
	if(sum <= k) {
		printf("%lld\n", mx+(k-sum)/n);
		return 0;
	}
	for(int i = mx; i > 1; --i) {
		sum = 0;
		for(int j = 1; (j-1) * i <= mx; ++j) {
			int ct = s1[j*i-1] - s1[(j-1)*i];
			sum += ct * j * i;
			sum -= s2[j*i-1] - s2[(j-1)*i];
		}
		if(sum <= k) {
			printf("%d\n", i);
			return 0;
		}
	}
	puts("1");
	return 0;
}
```

---

## 作者：出言不逊王子 (赞：2)

不难发现，如果 $K$ 非常大，那么我们将有条件将每个数都变成相同的，非常大的数。

此时这个数组的和是 $K+\sum a_i$，因为每个数都相等，所以每个数都是 $\dfrac{K+\sum a_i}n$ 下取整。

什么时候我们不能这么做呢？当 $K$ 不够大时。

我们要保证 $K$ 大到每个数都能变得一样，所以这个公式满足时，要求 $\sum (\dfrac{K+\sum a_i}n-a_i)\le K$ 且 $\dfrac{K+\sum a_i}n\ge \max a_i$。

将 $a$ 排序，得 $a_n=\max a_i$，则 $K\ge na_n-\sum a_i=\sum(a_n-a_i)$。

写的时候式子推错得到 $K\ge \sum a_i$ 了，但是好像交上去也能过。

我们发现 $a_i$ 很小，说明 $\gcd a_i$ 也很小，这启发我们枚举 $\gcd$。

考虑当 $K$ 取到下界时的答案是 $\dfrac{\sum a_n-a_i+a_i}{n}=a_n$，所以我们最终的答案也小于等于 $a_n=3\times 10^5$。

枚举这个答案，我们需要做的就是把每个数变为最小的这个答案的倍数。

因为我们排过序了，所以每个最终会被改成的数对应的 $a_i$ 是一段区间，可以通过二分得出。

那复杂度不会太大吗？

不会，因为最终要被修改的数最多 $\sum \dfrac{a_n}i=a_n\log a_n$ 个，一次二分也才一个 $\log$，正好能过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
inline int read(){
	int w=0,x=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')x=-1;c=getchar();}
	while(c>='0'&&c<='9'){w=w*10+c-'0';c=getchar();}
	return w*x;
}
const int N=400001,inf=1e9+7;
int n,k,sum,a[N],pre[N],cnt[N];
signed main(){
//	freopen("x.in","r",stdin);
	n=read(),k=read();fs(i,1,n,1) a[i]=read(),pre[i]=pre[i-1]+a[i],cnt[a[i]]++;
	sort(a+1,a+n+1);//答案上界2an
	fs(i,1,n,1) sum+=(a[n]-a[i]);
//	assert(cnt[500]==500);
	if(k>=sum) return printf("%lld",(k+pre[n])/n),0;
	a[n+1]=inf;
	ft(res,2*a[n],1,-1){//枚举这个res 
		int tot=0,cur=1,now=res;
		while(cur<=n){
			int pos=upper_bound(a+cur,a+n+1,now)-a-1;//最后一个小于等于我的 
			//[cur,pos]都满足ai\le now
			tot+=(pos-cur+1)*now;
			tot-=(pre[pos]-pre[cur-1]);
			cur=pos+1; if(cur>n) break;
			while(a[cur]>now) now+=res;//如果不行的话，这里优化成倍增，要求 
		}
	//	clog<<res<<"?";
		if(tot<=k) return printf("%lld",res),0;
	} 
//	ft(res,a[n],1,-1){
//		int p=n,tot=0,tot2=0;//不是gcd倍数的数的个数 
//		fs(cur,res,a[n],res) p-=cnt[cur];
//		tot+=res*p;
//	//	fs(i,1,a[n],1) tot-=cnt[i]*(i-i/p);
//		
//	}
	//假设i=ak+b，则pk%i=pk-(p-1)k-b，也就是k-b 
	return 0;
}
//如果k很大，那么答案显然
//(sum+k)/n
//要保证k大于每一个这个-ai
//也就是k>\sum_{i=1}^n (sum+k-ai)/n=((n-1)sum+k)/n
//(n-1)/nk>(n-1)/nsum
//k>sum
//考虑答案上界
//2sum/n，也就是2ai
//5 15 1 2 3 4 5
//答案应该是6
//那么答案非常小，从大到小跑一遍就好
//然后怎么做
//这个是50分的
//3 9982
//4 6 7	
//好像可以啊，你可以每次二分跑，因为res的倍数太少了，所以可以跳的完
//600000开局，然后就是要跳到底，一次搞定
//那会不会一次跳一个？
//考虑小于2ai的倍数一共就那么多 
//考虑300000 44999850000
//(150000个1) 150000个300000  

```

---

## 作者：白简 (赞：2)

设 $a_x$ 为数列 $a$ 中的最大值。

一般来说，与其处理 $x | \gcd(A_1,\dots,A_N)$ ，处理 $x = \gcd(A_1,\dots,A_N)$ 更加容易。这是因为后者能够被分解为各个元素：$\forall i,x | A_i$。

因此，我们将解决下面这个问题而不是原来的问题。

> 寻找 $x$ 的最大值，这样就有可能在运算后得到 $x | \gcd(A_1,\dots,A_N)$。

假设 $K$ 足够大，能够使得序列中每一个值都加到 $a_{\max}$，那我们就先把每个值都加到 $a_{\max}$，剩下的操作数再平均分配到每一个元素。

如果 $K$ 不能使得序列中每一个值都加到 $a_{\max}$，我们能够发现，答案的最大值不超过 $a_{\max}$，也就是不超过 $3 \times 10^5$。

这个范围我们完全可以从大到小枚举 $x$ 的值。

如何枚举 $x$ 的值？

设 $k$ 为一个整数，并且计算出对于所有 $A_i$ 能够满足 $(k - 1)x < A_i \leq kx$ 的操作数。

我们可以计算出一个值域 $\left(kx - x,kx \right]$ 内 $A_i$ 的个数和 $A_i$ 的和。由于是静态的，直接前缀和统计就可以。

这样枚举中找到满足需要的操作次数不大于 $K$ 的 $x$ 的最大值。

---

## 作者：User_Unauthorized (赞：2)

## 题意
给定一个序列 $A$，每次操作可以使 $A_i + 1$（$i \in \left[1, n\right]$，$K$ 次操作的 $i$ 可以不同），最多可以做 $K$ 次。问 $\gcd{A_1, A_2, ..., A_n}$ 的最大值。

## 题解
首先，如果 $K$ 可以把当前序列中所有的数都加到 $A_{\max}$，那就全部加到 $A_{\max}$，在此基础上同步对所有数相加即可。

如果 $K$ 不足以把当前序列中所有的数都加到 $A_{\max}$，那么可以发现最后的答案 $Ans \le A_{\max}$，因为 $A_{\max} \le 3 \times 10^5$，所以可以直接枚举判断当前答案是否成立。

可以把原题的条件进行转化
$$\gcd{A_1, A_2, ..., A_n} = Ans \Rightarrow Ans \mid {A_1, A_2, ..., A_n}$$

又因为题目要求的是最大值，所以从大到小枚举即可。接下来考虑如何判定。

设当前枚举的答案是 $x$，那么对于序列中的数 $A_i$，它应当被加到 $kx \ge A_i$，考虑枚举 $k$ 进行判定，使用前缀和记录序列中一定值域中的数的个数和和即可求解。

设 $M = A_{\max}$，则最终的复杂度为 $\mathcal{O}(N + M \times \sum\limits_{i = 1}^{M} \dfrac{1}{i}) = \mathcal{O}(N + M \log M)$。

## Code
```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

class TreeArray {
public:
    typedef ValueVector container;
private:
    valueType size;
    container data;

    static valueType lowBit(valueType x) {
        return x & -x;
    }

public:
    explicit TreeArray(valueType n) : size(n), data(size + 1, 0) {};

    void insert(valueType pos, valueType key) {
        while (pos < size) {
            data[pos] += key;

            pos += lowBit(pos);
        }
    }

    valueType sum(valueType pos) const {
        valueType result = 0;

        while (pos > 0) {
            result += data[pos];

            pos -= lowBit(pos);
        }

        return result;
    }
};

constexpr valueType \maxA = 6e5 + 5;

int main() {
    std::ios_base::sync_with_stdio(false);

    valueType N, K;

    std::cin >> N >> K;

    if (N == 1) {
        valueType A;

        std::cin >> A;

        std::cout << (A + K) << std::endl;

        return 0;
    }

    ValueVector source(N);

    for (auto &iter: source)
        std::cin >> iter;

    TreeArray sum(\maxA), count(\maxA);

    valueType \max = 0;

    for (auto const &iter: source) {
        \max = std::\max(\max, iter);

        sum.insert(iter, iter);
        count.insert(iter, 1);
    }

    typedef std::function<bool(valueType)> CheckFunction;

    CheckFunction check = [\max, &sum, &count, K](valueType n) -> bool {
        valueType result = 0;

        for (valueType i = n; i <= \max + n; i += n)
            result += i * (count.sum(i) - count.sum(i - n)) - (sum.sum(i) - sum.sum(i - n));

        return result <= K;
    };

    valueType const minK = N * \max - sum.sum(\max);

    if (K >= minK) {
        std::cout << (\max + (K - minK) / N) << std::endl;
    } else {
        for (valueType i = \max; i >= 1; --i) {
            if (check(i)) {
                std::cout << i << std::endl;

                return 0;
            }
        }
    }
    return 0;
}
```

---

## 作者：int_R (赞：1)

场切模拟赛 T3。

设最后的数组是 $b$，答案为 $ans$，$M=\max\limits_{i=1}^{n} a_i$。

首先当 $k\geq M\times n -\sum\limits_{i=1}^{n} a_i$ 时，这时情况肯定是 $ans=b_1=b_2=\cdots =b_n$。所以我们当做都先加到 $M$，需要 $ M\times n -\sum\limits_{i=1}^{n} a_i$ 次操作，剩下的尽可能平均分下去，最多还可以加 $\left\lfloor \dfrac{k-(M\times n -\sum\limits_{i=1}^{n} a_i)}{n}\right\rfloor$，答案即为 $M+\left\lfloor \dfrac{k-(M\times n -\sum\limits_{i=1}^{n} a_i)}{n}\right\rfloor$。

否则，$ans<M$，考虑从高到低枚举答案 $x$，若要使得 $\gcd\limits_{i=1}^{n} b_i=x$，因为是从高到低枚举，所以只需要满足 $\forall i\in[1,n],x\mid b_i$，那么每个 $a_i$ 都需要加到大于等于它的最小的 $x$ 的倍数，所需要的操作次数和即为 $\sum\limits_{i=1}^{n}\left\lceil \dfrac{a_i}{x}\right\rceil\times x-a_i$。

当然如果直接这么操作是 $O(n^2)$ 的，考虑优化，对一个 $x$，我们枚举它的倍数 $k$，操作次数和即为 $\sum\limits_{x\mid k} k\times [k-x< a_i\leq x] -\sum\limits_{i=1}^{n} a_i$，我们使用前缀和优化一下，设 $t_i$ 表示 $\sum\limits_{j=1}^{n} [a_j\leq i]$，则式子变为$\sum\limits_{x\mid k} k\times (t_k-t_{k-x}) -\sum\limits_{i=1}^{n} a_i$，判断是否小于 $k$ 即可。

这样最坏时间复杂度为 $O(\sum\limits_{i=1}^{n} \dfrac{M}{i})=O(n\log n)$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=3e5+10;
int t[MAXN];long long n,k,a[MAXN],sum;
int main()
{
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0); 
	cin>>n>>k;
	for(register int i=1;i<=n;++i) cin>>a[i],t[a[i]]++,sum+=a[i];//t 是桶
	sort(a+1,a+1+n);for(register int i=1;i<=a[n];++i) t[i]+=t[i-1];//对桶做前缀和
	if(a[n]*n-sum<=k)//第一种情况
	{
		k-=a[n]*n-sum;
		cout<<a[n]+k/n<<'\n';
		return 0;
	}
	for(register int i=a[n];i>1;--i)
	{
		long long ans=0;
		for(register long long x=i;x-i<a[n];x+=i) ans+=(((x<=a[n])?t[x]:n)-t[x-i])*x;//计算操作次数和
		ans-=sum;if(ans<=k){cout<<i<<'\n';return 0;}
	}
	cout<<"1\n";return 0;
}
```


---

## 作者：5k_sync_closer (赞：0)

特判掉最终 $\gcd>\max\limits_{i=1}^na_i$ 的情况，这部分是平凡的。

倒序枚举最终 $\gcd$ 为 $g\in[1,\max\limits_{i=1}^na_i]$，考虑怎么判断 $\gcd$ 能否取得 $g$。

发现若 $\forall i,g|a_i$ 则 $g=\gcd\limits_{i=1}^na_i$。（反证法：一定有 $g|\gcd\limits_{i=1}^na_i$，而若 $\gcd\limits_{i=1}^n>g$ 则枚举 $g'=\gcd\limits_{i=1}^n$ 时程序已经结束。）

$\forall p,gp\le\max\limits_{i=1}^na_i$ 统计将 $(gp,g(p+1)]$ 间的数都改为 $g(p+1)$ 的代价，开桶容易做到单次 $O(1)$。

若总代价 $\le k$，则 $\gcd$ 可以取得 $g$。复杂度 $O(\sum\limits_{i=1}^W\dfrac Wi)=O(W\log W)$。

```cpp
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
int n, m, k, s, a[300050], c[300050];
signed main()
{
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", a + i), ++c[a[i]], s += a[i], m = max(m, a[i]);
    for (int i = 1; i <= 300000ll; ++i)
        c[i] += c[i - 1];
    if (k >= n * m - s)
    {
        k -= n * m - s;
        printf("%lld", m + k / n);
        return 0;
    }
    for (int i = m, z; i; --i)
    {
        z = 0;
        for (int j = i; j - i <= 300000ll; j += i)
            z += j * (c[min(j, 300000ll)] - c[j - i]);
        if (z - s <= k)
        {
            printf("%lld", i);
            return 0;
        }
    }
    return 0;
}
```


---

## 作者：jijidawang (赞：0)

对于一个 GCD $d$，当且仅当满足
$$k\ge\sum_{i=1}^n(d-a_i\bmod d)\iff \left\lceil\dfrac{k+\sum a_i}d\right\rceil\ge\sum_{i=1}^n\left\lceil\dfrac{a_i}d\right\rceil$$
时 $d$ 可以作为一个合法解。

如果 $d>\max a_i$ 那么 $d\le\left\lfloor\dfrac{k+\sum a_i}n\right\rfloor$ 所以如果 $\left\lfloor\dfrac{k+\sum a_i}n\right\rfloor>\max a_i$ 则答案为 $\left\lfloor\dfrac{k+\sum a_i}n\right\rfloor$。

那么剩下的情况必有 $d\le\max a_i $，只需要快速对所有 $d$ 计算 $\displaystyle\sum_{i=1}^n\left\lceil\dfrac{a_i}d\right\rceil$ 即可。

令 $\displaystyle G(x)=\sum_{i=1}^n[a_i\ge x]$，那么不难发现 $\displaystyle\sum_{i=1}^n\left\lceil\dfrac{a_i}d\right\rceil=\sum_{i\ge 1}G(1+di)$。

$G$ 可以通过在值域上前缀和求出，后者的时间复杂度可以由调和级数分析，那么问题被以 $O(v\log v)$ 的时间复杂度解决，其中 $v$ 是值域，可以通过。

---


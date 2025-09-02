# 「SiR-1」Bracket

## 题目背景

> Everything that kills me makes me feel alive.

## 题目描述

Mirika 有一个长度为 $n$ 的括号序列 $s$。

对于一个括号序列 $S$，Mirika 可以执行两种操作：

- 变换：选择一个位置 $i$ 满足 $1 \leq i \leq \lvert S \rvert$，使得 $S$ 变为 $S_iS_{i+1}\cdots S_{\lvert S\rvert}S_1S_2\cdots S_{i-2}S_{i-1}$。
- 插入：在这个序列的 **任意位置** 插入一个括号（左右括号均可）。

Mirika 定义括号序列 $S$ 的权值 $f(S)$ 为能将这个括号序列变成一个合法括号序列所需的最小操作数。

其中，合法括号序列的定义为：

+ 空串为 合法括号序列。
+ 若 $\texttt A$ 为 合法括号序列，则 $\texttt{(A)}$ 为 合法括号序列。
+ 若 $\texttt A, \texttt B$ 均为 合法括号序列，则 $\texttt{AB}$ 也为 合法括号序列。

现在 Mirika 想要求出：

$\sum_{l=1}^n \sum_{r=l}^n f(s[l,r])$

其中 $s[l,r]$ 表示由 $s_l,s_{l+1},\cdots,s_r$ 形成的连续子序列。

但是 Mirika 太菜了不会算，于是只好求助于你。

## 说明/提示

### 样例解释

对于 $s = \texttt{())(}$：

+ 考虑 $s[1,4]=\texttt{())(}$。执行变换操作 $i=4$，有 $\texttt{())(} \Rightarrow \texttt{(())}$，其中 $\texttt{(())}$ 是合法括号序列，故 $f(s[1, 4]) = 1$。可以证明不存在更优的策略。
+ 考虑 $s[2,4]=\texttt{))(}$。执行变换操作 $i=2$，再在序列开头插入一个左括号，有 $\texttt{))(} \Rightarrow \texttt{)()} \Rightarrow \texttt{()()}$，其中 $\texttt{()()}$ 是合法括号序列，故 $f(s[2, 4]) = 2$。可以证明不存在更优的策略。

### 数据规模与约定

**本题采用捆绑测试。**

+ Subtask 0（15 pts）：$n \leq 400$，$\sum n \leq 800$。
+ Subtask 1（20 pts）：$n \leq 2\times 10^3$，$\sum n \leq 4\times 10^3$。
+ Subtask 2（5 pts）：$s$ 内不含有右括号。
+ Subtask 3（10 pts）：对于所有整数 $1\le i < n$，有 $s_i \neq s_{i+1}$。
+ Subtask 4（30 pts）：$n \leq 2\times 10^5$，$\sum n \leq 5\times 10^5$。
+ Subtask 5（20 pts）：无特殊限制。

对于所有数据，$1 \leq T \leq 10000$，$1 \leq n \leq 2 \times 10^6$，$1 \leq \sum n \leq 2 \times 10^7$。

## 样例 #1

### 输入

```
5
2
((
4
())(
5
()(()
5
()()(
15
()())(())))()()```

### 输出

```
4
11
16
12
241```

# 题解

## 作者：Miraik (赞：14)

首先考虑给定一个长度为 $n$ 的括号序列，我们将它变成一个合法括号序列的最优策略是什么样的。

首先有两个性质：

1. 我们只会做最多一次变换操作。

证明：显然，多次变换操作可以合为一次。

2. 设这个序列有 $A$ 个左括号，$B$ 个右括号，那么必然存在一种变换方案，使得变换后有 $\min(A,B)$ 组括号被匹配。换句话说，就是左括号和右括号中个数较少的全部被匹配到。

证明：不妨设 $A \ge B$，把左括号看作 $1$，右括号看作 $-1$，然后再得到一个前缀和数组 $c$。然后选择数组中最小值所在位置 $x$，通过变换使得 $x$ 这个位置移到新序列的末尾。

如果有右括号没匹配上左括号，就说明存在一个位置 $i$ 使得 $c_i<0$。

对于 $x$ 之后的任意位置 $y$ 都有 $c_x<c_y$，那么把 $[x+1,n]$ 变换到序列开头，这部分必然使得整体的 $c$ 数组增加。

而变换前 $[1,x]$ 这部分在变换后的 $c$ 值增加量是完全一致的（也就是变换前的 $c_n-c_x$）。因此 $c_x$（相当于变换后的 $c_n$）依然是这部分的最小值。又因为 $A \ge B$，我们可以知道 $c_x$ 此时就是 $A-B \ge 0$。

因此结论得证。$A < B$ 的情况是类似的，不再赘述。有了这两个性质，这题就可做了。因为我们发现如果一个序列的匹配数没有达到上界 $\min(A,B)$ 的话，我们把它循环移位一下必然不劣。因此最后的答案就是 $\sum\limits_{l=1}^{n} \sum\limits_{r=l}^{n} \lvert A[l, r] - B[l, r]\rvert+g(l,r)$，其中 $A,B$ 意义同上，$g(l,r)$ 表示序列的匹配数是否达到上界（是为 $0$，不是为 $1$）。

- $n \leq 400$，$\sum n \leq 800$

暴力枚举 $l,r$，再暴力计算，时间复杂度 $O(n^3)$。

- $n \leq 2\times 10^3$，$\sum n \leq 4\times 10^3$

暴力枚举 $l$，$r$ 从 $l$ 开始向后拓展，在拓展的过程中维护括号匹配情况以及 $A,B$，计算 $[l,r]$ 的贡献。时间复杂度 $O(n^2)$。

- 特殊性质：所有括号都是左括号

此时容易发现就是求 $\sum\limits_{l=1}^{n} \sum\limits_{r=l}^{n} r-l+1$。这就是 $\sum\limits_{i=1}^n (n-i+1) \times i$ 啊。如果您是数学带师的话还可以直接看出这个东西就是 $n+2 \choose 3$（考虑组合意义）。

- 特殊性质：对于所有整数 $1\le i < n$，有 $s_i \neq s_{i+1}$

所有可能的子串只有四种形态：$\texttt{()()} \cdots \texttt{()}$，$\texttt{)()} \cdots \texttt{()}$，$\texttt{)()} \cdots \texttt{()(}$ 和 $\texttt{()()} \cdots \texttt{()(}$。其中只有第三种 $g(l,r)=1$，容易做到线性计算。

- $n \leq 2\times 10^5$，$\sum n \leq 5\times 10^5$


此时我们再整理整理式子，让它变成 $\sum\limits_{l=1}^{n} \sum\limits_{r=l}^{n}   |c_r-c_{l-1}| + \sum\limits_{l=1}^{n} \sum\limits_{r=l}^{n} g(l,r)$。

前面那个部分可以直接把 $c$ 排序后快速计算 $\sum\limits_{r=0}^{n} \sum\limits_{l=0}^{r}   c_r-c_l$ 即可。对于后面那个，我们考虑把 $g(l,r)$ 转化成更优秀的条件。

关键性质：$g(l,r)=1$ 等价于：$\min\{c_l,c_{l+1},\cdots,c_{r-1}\} < \min(c_{l-1},c_r)$。

证明：

$\min\{c_l,c_{l+1},\cdots,c_{r-1}\} < c_{l-1}$ 可以看作至少一个右括号失配。

$\min\{c_l,c_{l+1},\cdots,c_{r-1}\} < c_{r}$ 可以看作至少一个左括号失配。

由之前得到的性质 2，容易知道这是 $g(l,r)=1$ 的充要条件。

直接硬莽 $\min\{c_l,c_{l+1},\cdots,c_{r-1}\} < \min(c_{l-1},c_r)$ 有点困难，我们将其转化为 $\min\{c_l,c_{l+1},\cdots,c_{r-1}\} < c_{l-1} < c_r$ 和 $\min\{c_l,c_{l+1},\cdots,c_{r-1}\} < c_r \le c_{l-1}$ 两种情况的方案数之和。

一般化地，我们枚举 $l$，找到最小的 $pos_{l}$ 满足 $\min\{c_{l+1},c_{l+2},\cdots,c_{pos_l}\} < c_{l}$，再查询满足 $x>pos_l$ 且 $c_x>c_{l}$ 的 $x$ 个数，就可以算出满足 $\min\{c_{l+1},c_{l+2},\cdots,c_{r-1}\} < c_{l} < c_r$ 的方案数了。另一种情况同理。

使用单调栈求出 $pos_i$，后面的部分本质上是二维偏序，可以离线树状数组，总时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4000005;
int n,m,sum[N],tmp[N],a[N],top,stc[N];
ll ts,ans; char str[N];
struct BIT{
	int c[N];
	#define lowbit(x) (x&(-x))
	inline void clr(){ for(int i=1;i<=n*2+1;i++) c[i]=0; }
	inline void update(int x){ while(x<=n*2+1) c[x]++,x+=lowbit(x); }
	inline int query(int x){ int res=0; while(x) res+=c[x],x-=lowbit(x); return res; }
}T;
struct Q{
	int x,val;
	bool operator < (const Q &a) const { return x<a.x; }
}q[N];
inline void calc(int op){ // op=0:a[l]<=a[r],op=1:a[l]<a[r] 满足 min(a[l+1],...,a[r-1])<a[l]
	top=m=0;
	for(int i=n;i;i--){
		while(top && a[i]<=a[stc[top]]) top--;
		if(top) q[++m]={stc[top],a[i]};
		stc[++top]=i;
	}
	sort(q+1,q+m+1);
	for(int i=m,j=n;i;i--){
		while(j>=q[i].x) T.update(a[j]+n+1),j--;
		ans+=n-j-T.query(q[i].val+n+op);
	}
	T.clr();
}
inline void solve(){
	scanf("%d%s",&n,str+1);
	for(int i=1;i<=n;i++)
		sum[i+1]=sum[i]+(str[i]=='('?1:-1);
  	// 为了方便，我在这里直接把 c[0] 放在前面，后面统计贡献就全部是 1 下标了
	ans=ts=0; n++;
	for(int i=1;i<=n;i++) tmp[i]=sum[i];
	sort(tmp+1,tmp+n+1);
	for(int i=1;i<=n;i++) ans+=1ll*(i-1)*tmp[i]-ts,ts+=tmp[i]; // 求第一部分的贡献
	for(int i=1;i<=n;i++) a[i]=sum[i]; calc(0);
	for(int i=1;i<=n;i++) a[i]=sum[n-i+1]; calc(1);
	printf("%lld\n",ans);
}
int main(){
	int tc; scanf("%d",&tc);
	while(tc--) solve();
	return 0;
}
```

- $1 \leq n \leq 2 \times 10^6$，$1 \leq \sum n \leq 2 \times 10^7$

$g(l,r)=1$ 的统计稍显麻烦，我们正难则反。

考虑 $g(l,r)=0$ 等价于 $\min\{c_l,c_{l+1},\cdots,c_{r-1}\} \ge \min(c_{l-1},c_r)$，我们不妨对 $g(l,r)=0$ 的情况计数。

那么这个式子等价于 $c_{l-1}\le \min\{c_l,c_{l+1},\cdots,c_{r}\}$ 或  $c_{r}\le \min\{c_{l-1},c_l,\cdots,c_{r-1}\}$。

发现一个重要的事实：在 $c_{l-1} \neq c_r$ 时，我们上面的这个或式不可能同时满足！且 $c_{l-1} = c_r$ 时，这两个式子必然同时满足或不满足。

另外我们还注意到：$c_{i+1}=c_i \pm 1$。

于是 $c_l \le \min\{c_{l+1},c_{l+2},\cdots,c_{r}\}$ 可以直接等价于 $(c_l-1) \notin \{c_{l+1},c_{l+2},\cdots,c_{r}\}$！

那么容易发现对于一个 $c_i$，其向左和向右延伸的贡献为一段连续的区间，那么这个区间我们都不需要单调栈了（上面实际上也不用），用一个桶就可以轻松求出，且在 $c_{l-1} \neq c_r$ 时，其贡献必然被 $c_{l-1}$ 向右的区间和 $c_r$ 向左的区间中的**恰好一个**统计到！

那么我们直接将所有贡献区间统计起来，就统计好了所有 $c_{l-1} \neq c_r$ 的贡献，而 $c_{l-1}=c_r$ 的贡献则被我们计算了两遍。

于是我们现在需要再减掉所有 $c_{l-1}=c_r$ 的贡献。依旧是注意到 $c_{i+1}=c_i \pm 1$，于是我们发现 $c_{l-1}=c_r$ 有贡献当且仅当不存在 $i$ 满足 $l \le i \le r$ 且 $c_i=c_{l-1}-1$。那么我们发现对于每一种 $c_i$ 其出现的位置又可以依此划为一段一段，而每一段出现次数为 $cnt$ 的贡献即为 $ cnt \choose 2$。这个部分线性扫一遍即可完成，具体实现也可以参照代码。（代码比题解清楚.jpg）

至于前面的部分 $\sum_{r=0}^{n} \sum_{l=0}^{r}   c_r-c_l$ 中计算怎么做到线性？$c_i$ 的值域是 $[-n,n]$ 的，于是直接桶排序即可。

于是我们做到了时间复杂度 $O(n)$，且实现非常简洁。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4000005;
int n,m,sum[N],tmp[N],cnt[N],lst[N];
ll ts,ans; char str[N];
inline void solve(){
    scanf("%d%s",&n,str+1);
    for(int i=1;i<=n;i++)
        sum[i+1]=sum[i]+(str[i]=='('?1:-1);
    // 为了方便，我在这里直接把 c[0] 放在前面，后面统计贡献就全部是 1 下标了
    ans=ts=0; n++;
    for(int i=1;i<=n;i++) tmp[i]=sum[i];
	for(int i=1;i<=n+n;i++) cnt[i]=0;
    for(int i=1;i<=n;i++) cnt[tmp[i]+n]++;
    for(int i=1,j=0;i<=n+n;i++)
		for(int t=1;t<=cnt[i];t++) ans+=1ll*j*(i-n)-ts,ts+=i-n,j++;
	// 求第一部分的贡献
	ans+=1ll*n*(n-1)/2;
	for(int i=0;i<=n+n;i++) lst[i]=n+1;
    for(int i=n;i;i--){
    	int r=lst[sum[i]+n-1]-1;
    	ans-=r-i;
    	lst[sum[i]+n]=i;
	}
	for(int i=0;i<=n+n;i++) lst[i]=0;
	for(int i=1;i<=n;i++){
		int l=lst[sum[i]+n-1]+1;
		ans-=i-l;
		lst[sum[i]+n]=i;
	}
	// 求第二部分的贡献
	for(int i=1;i<=n+n;i++) cnt[i]=0;
	for(int i=1;i<=n;i++){
		cnt[sum[i]+n]++;
		if(i==n||sum[i]>sum[i+1]){
			ans+=1ll*cnt[sum[i]+n]*(cnt[sum[i]+n]-1)/2;
			cnt[sum[i]+n]=0;
		}
	}
	for(int i=1;i<=n+n;i++) if(cnt[i]) ans+=1ll*cnt[i]*(cnt[i]-1)/2; 
	// 第二部分在 c[l]=c[r] 时会算重 
    printf("%lld\n",ans);
}
int main(){
    int tc; scanf("%d",&tc);
    while(tc--) solve();
    return 0;
}
```

顺带一提，这题的做法真的很多很多。

---

## 作者：zyc070419 (赞：7)

# P9356 「SiR-1」Bracket 题解

首先我们来先考虑一下如何计算一个给定的 $f(s[1,n])$。

一般括号序列的题目都是比较套路的将 $\texttt{(}$ 赋值为 $1$，将 $\texttt{)}$ 赋值为 $-1$，然后求一下前缀和记为 $sum_i$，那么一个括号序列是合法的当且仅当 $\forall i\in[1,n],sum_i\ge 0$。

然后观察本题的操作可以发现由于操作二是任意地进行循环位移，所以我们最多进行一次操作二（因为任意两次操作二都可以合并成一次），那么我们接下来只用考虑需要进行几次操作一、什么时候进行操作二。

引理一：

> 如果 $sum_n=0$ 那么我们一定可以通过最多一次操作二使得该序列合法。

证明：

我们记 $sum_p=\min_{i=1}^{n}sum_i$，所以 $\forall i\in[1,n]sum_i-sum_p\ge0$。

如果 $sum_p\ge 0$，那么显然引理一得证，下面考虑 $sum_p<0$ 的情况。

由于 $sum_n=0$，因此 $\sum_{i=p+1}^{n}a_i=sum_n-sum_p=-sum_p$，那么如果我们将 $s[p+1,n]$ 移动到最前面，则新的 $\{sum_i'\}$ 就满足：
$$
\begin{cases}
sum'_i=sum_{i+p}-sum_p\ge0,&i\in[1,n-p]\\
sum'_i=sum_{i-p}+sum_{n-p}\ge0,&i\in[n-p+1,n]
\end{cases}
$$
故此时的括号序列合法。综上所述引理一得证。

所以说对于一个括号序列 $s[l,r]$，如果我们最后不管是否需要都进行一次操作二，那么他变成合法序列的操作数就是 $|sum_r-sum_{l-1}|+1$，故本题要求的答案为：
$$
ans=\sum_{l=1}^{n}\sum_{r=l}^{n}f(s[l,r])=\dfrac{n(n+1)}{2}+\sum_{l=1}^{n}\sum_{r=l}^{n}|sum_r-sum_{l-1}|
$$
求这个式子的话可以分成两类，$sum_r\ge sum_{l-1}$ 和 $sum_r<sum_{l-1}$，然后分别计算答案，这个可以用值域树状数组在 $\mathcal O(n\log n)$ 的时间复杂度内完成，具体的，记 $val_i,num_i$ 表示当前的 $\sum_{l=1}^{r}sum_{l-1}[sum_{l-1}\le i]$ 和 $sum_{l=1}^{r}[sum_{l-1}\le i]$，然后对于以 $r$ 结尾的区间的贡献就是：$(num_{sum_r}\times sum_r-val_{sum_r})+(val_{inf}-(num_{inf}-num_{sum_r})\times sum_r)$。

但是这一部分其实是可以在 $\mathcal O(n)$ 的时间复杂度内完成的，因为我们关心的只是所有二元组 $(x,y)$ 的 $|sum_y-sum_x|$ 的和（$x\in[0,n],y\in[0,n]$），并不关心 $x,y$ 的大小关系，因此我们可以直接按照 $sum_i$ 的值从小到大排序，答案就是：
$$
\sum_{i=0}^{n}(sum_i\times i- \sum_{j=0}^{i-1}sum_{j})
$$
这是可以 $\mathcal O(n)$ 求解的，而由于 $sum_i\in[-n,n]$，所以说可以桶排，排序复杂度也是 $\mathcal O(n)$，故总复杂度 $\mathcal O(n)$。

这一部分说完了，接下来只剩一个问题，求出不需要进行操作二的区间的个数 $tot$。那么最终的答案 $res=ans-tot$。

引理二：

> 一个括号序列 $s[1,n]$ 进行完操作一后不需要进行操作二的充要条件是 $sum_n=\min_{i=1}^{n}sum_i$ 或 $\min_{i=1}^{n}sum_i\ge0$。

证明：

这里我们记 $mn=\min_{i=1}^{n}sum_i$，进行完操作一之后序列长度为 $m$。首先容易想到一个贪心的策略：**我们在进行操作一的时候，如果要加入 $\texttt{(}$ 一定是将它放到序列最前面，否则将它放到序列最后面**，这样我们才能让进行操作一之后的前缀和序列 $\{sum'_i\}$ 的值尽可能的大，然后我们分两类来考虑。

第一种，当 $mn\ge 0$ 时，这时我们只在序列后面加入 $\texttt{)}$，并且最终 $sum'_m=0$，而显然 $sum'_i\ge sum'_m,i\in[n+1,m]$，因此当 $mn\ge0$ 时该括号序列不需要进行操作二。

第二种，当 $mn<0$ 时，这时候如果 $sum_n\ge 0$ 显然需要进行操作二，而当 $sum_n<0$ 时会在序列前方加入 $-sum_n$ 个 $\texttt{(}$，那么就有 $sum'_{i-sum_n}=sum_i-sum_n,i\in[1,n]$，而要保证 $sum'_i\ge 0,i\in[1,m]$，故 $sum_i-sum_n\ge 0,i\in[1,n]$，也即 $mn-sum_n\ge 0$，因此只有当 $sum_n=mn$ 时才不需要进行最后一次操作二。

综上所述，不需要进行操作二需要满足 $sum_n=mn\wedge mn\ge 0$。

接下来我们考虑如何统计原题目中各个子序列中满足上述条件的序列的数量。由于上述条件涉及到区间最小值，所以说很容易想到用单调栈去维护，然后枚举右端点，将右端点不断向右移动。现在我们记 $st$ 为一个维护 $sum_i,i\in[0,r]$ 的单调栈，里面的值单调递增，$st$ 里存的是下标，即 $st_{top}=r$。

那么对于 $mn=sum_n$ 这个条件，显然需要满足 $l\in(st_{top-1},r]$，区间个数为 $r-st_{top-1}$，复杂度 $\mathcal O(n)$。

而对于 $mn\ge 0$，我们需要分段考虑，总的个数为：
$$
\sum_{i=1}^{top-1}\sum_{j=st_{i-1}}^{st_i}[sum_{st_i}\ge sum_j]
$$
这个式子可以用值域树状数组维护，复杂度 $\mathcal O(n\log n)$，但可以继续优化。

如果我们记 $pre_i$ 为它插入单调栈时他前面的那一个数的下标，则如果 $i$ 此时在单调栈中那么他对 $r$ 这个右端点的答案的贡献就是 $\sum_{j=pre_i+1}^{i}[sum_i\ge sum_j]$。而又由于每一个值 $i\in[1,n]$，他的 $pre_i$ 的值只有一个，所以它的贡献也是唯一确定的，因此只要我们能 $\mathcal O(n)$ 求出所有 $\sum_{j=pre_i+1}^{i}[sum_i\ge sum_j]$ 就行了，而这个式子其实和我们维护单调栈的过程十分类似——维护单调栈是将 $[pre_i+1,i-1]$ 之间所有 $sum_j\ge sum_i$ 的 $j$ 给 $pop$ 掉了，而 $\sum_{j=pre_i+1}^{i}[sum_i\ge sum_j]=i-pre_i-\sum_{j=pre_i+1}^{i-1}[sum_i \le sum_j]+\sum_{j=pre_i+1}^{i-1}[sum_i=sum_j]$，这样就可以轻松 $\mathcal O(n)$ 去维护了，具体的：

记 $val_i$ 为 $\sum_{j=pre_i+1}^{i-1}[sum_i\le sum_j]$，$ex_i=\sum_{j=pre_i}^{i-1}[sum_i=sum_j]$，$S$ 为插入 $i$ 时所有弹出栈的下标的集合，则：
$$
val_i=\sum_{j\in S}val_j+1,ex_i=\sum_{j\in S}(ex_j+1)[sum_j=sum_i]
$$
那么答案就是 $\sum_{i=1}^{top-1}st_i-st_{i-1}-val_i+ex_i$，再稍微维护一下前缀和即可，如果不清楚的话可以看一下代码中的 `tot[i]`。这样我们就做到了 $\mathcal O(n)$ 的时间复杂度。

好了到这里这道题就差不多结束了，这里有 $\mathcal O(n\log n)$ 的 **[代码](https://www.luogu.com.cn/paste/icj8vmzh)** 和 $\mathcal O(n)$ 的 **[代码](https://www.luogu.com.cn/paste/m8gndjz0)**。

---

## 作者：uid_310801 (赞：4)

首先考虑一个括号串的权值是什么：

example：`(()())))(`。

运用一个常见套路，将 `(` 看作 $1$，将 `)` 看作 $-1$，对其求前缀和，然后得到如下的一个折线图：

![](https://cdn.luogu.com.cn/upload/image_hosting/qvkmy8hj.png)

那么对于一个长度为 $n$ 的括号串，它合法当且仅当：

1. $\forall i\in[1,n],s_i\ge0$。
2. $s_n=0$。


我们可以通过 2 操作，在结尾加一些括号，使得 $s_n$ 变为 $0$，就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/9np9bhj1.png)

这里花费的代价是 $|s_n|$。当然，如果 $\exists i\in[1,n],s_i<0$，仅仅这样并不能让括号串变合法。但是我们还有 1 操作可以用！

我们找到 $s_i$ 最小的地方，然后在这里对其进行 $1$ 操作。看看会发生什么：

![](https://cdn.luogu.com.cn/upload/image_hosting/mfp2p545.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/lawrzele.png)

这样，仅仅通过一次操作，我们就将所有不合法的位置变合法了！

但是，这样一定最优吗？

我们再考虑这样一个串：`(()())))`。

![](https://cdn.luogu.com.cn/upload/image_hosting/8kohy3fb.png)

当然可以通过上面的方法，用 $3$ 次操作将其变合法。

![](https://cdn.luogu.com.cn/upload/image_hosting/p8r22oxh.png)

但是，我们可以通过在最前面加左括号，只用 $2$ 次就使其合法，最终的括号串也是上面的样子。

总结一下：要使一个括号串变合法，

1. 至少需要 $|s_n|$ 次操作使得 $|s_n|=0$。  

2. 如果 $\exists i\in[1,n],s_i<0$ 并且 $s_n≠\min_{1\le i\le n}{s_i}$，则还需要额外的一次操作。

发现了这些性质，先打个 $O(n^2)$ 的暴力，发现有 35 分，证明这个想法是对的，就可以愉快的优化了。

---

枚举左端点，设其为 $l$，可以这么算贡献：

第一步，算出 $\sum_{i=l}^n|s_i-s_{l-1}|$，累加到答案中。 

第二步，找出第一个 $s_p<s_{l-1}$ 的 $p$，如果存在，答案加上 $n-p+1$，表示这之后每个串都要考虑它是否需要用操作 1。   

第三步，减去 $\sum_{i=p}^n[s_i=min_{l\le j \le i}s_j]$。

不妨倒着枚举 $l$，分步考虑：

第一步，开个桶记录当前每个值的个数，当前的绝对值之和，当前 $s_i\ge s_{l-1}$ 的 $i$ 的个数。由于每移动一位，$s_{l-1}$ 的变化值为 $1$，所以可以 $O(1)$ 求出。  

第二步，还是开个桶，记录每个值最新一次出现的位置，直接查询即可，也是 $O(1)$。  

第三步，用单调栈预处理出来每个地方的值即可。这里预处理复杂度是 $O(n)$ 的。

综上，整个问题可以在 $O(n)$ 的时间复杂度内解决，而且代码很短。

注意：桶要开两倍大小。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2e6+10;
ll T,n,a[N],hi[N],cnt[N<<1],fst[N<<1];
char str[N];
stack<ll> s;
signed main(){
	scanf("%lld",&T);
	while(T--){
		ll ans=0,sum=0,cz=0;
		scanf("%lld",&n);
		scanf("%s",str+1);
		for(int i=1;i<=n;i++)	a[i]=a[i-1]+((str[i]=='(')?1:-1);
		for(ll i=n;i>=0;i--){
			while(!s.empty()&&s.top()>a[i]){
				s.pop();
			}
			hi[i]=s.size();
			s.push(a[i]);
		}
		while(!s.empty())	s.pop();
		for(ll l=n;l>=1;l--){
			cnt[a[l]+n]++;
			fst[a[l]+n]=l;
			cz++;
			if(a[l-1]<a[l]){
				sum+=cz;
				sum-=(n-l+1)-cz;
				cz+=cnt[a[l-1]+n];
			}
			else{
				cz-=cnt[a[l]+n];
				sum-=cz;
				sum+=(n-l+1)-cz;
			}
			ans+=sum;
			if(fst[a[l-1]+n-1]!=0){
				ll p=fst[a[l-1]+n-1];
				ans+=(n-p+1)-hi[p-1];
			}
		}
		for(ll i=1;i<=n;i++){
			cnt[a[i]+n]=fst[a[i]+n]=0;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：irris (赞：4)

## Preface

甜橙好闪，拜谢甜橙。来一发验题人题解。

~~其实这题是出题人看错题后对着 CF1750E 出的，头图里的「只有一笔」指的是 oi 生只有这一道题。~~

## Solution

直接考虑线性做法。

我们需要计数两个问题：

+ 1. 每个区间需要增加多少个括号：

对于一个有 $x$ 个 $\texttt ($，$y$ 个 $\texttt )$ 的区间，我们 **至少** 需要增加 $\lvert x - y \rvert$ 个括号才能让它匹配（下面会证该至少可以取到）。

如果我们以 $\texttt ($ 为 $-1$，$\texttt )$ 为 $1$ 做前缀和序列 $c_0 \dots c_n$，那么容易得到 $y - x$ 就是 $c_r - c_{l - 1}$。我们要求所有 $1 \leq l \leq r \leq n$ 的相减绝对值贡献，其实就是求所有 $\color{red}0 \color{normal}\leq l - 1 \color{red}\lt \color{normal} r \leq n$ 的相减绝对值贡献。

排序后，我们可以 $\mathcal O(1)$ 算出每个 $c_i$ 在式子里要加多少次，要减多少次，所以可以 $\mathcal O(n)$ 算出。注意到值域是 $-n \sim n$ 的，所以桶排即可线性。

+ 2. 每个区间需不需要位移。

通过 Rayne 引理的形式，我们可以证明每个括号区间任意旋转一次（**显然旋转任意次可以合并为一次**）肯定能够匹配。更具体地，只有至少一个左括号失配和至少一个右括号失配，才需要旋转，证明显然：

> + 因为你在上文的最优情况下只会加同一种括号，故而只能最多改变一种括号的失配状况；
> + 位移一次后至少多了一对匹配的括号，比增加操作更优。

但是你发现不会计数需要位移的区间个数（其实大概也是能做的，不过我懒得想。）**因此，正难则反**，考虑计数不需要位移的区间个数，这等于 **没有右括号失配**的区间个数 加上 **没有左括号失配**的区间个数 再减去 **完全匹配**的区间个数，因为完全匹配的区间会被算两遍。

作为熟练的括号序列做题人，我们考虑 dp。设 $f_r$ 表示对于所有 $1 \leq l \leq r$，满足 $[l, r]$ 没有右括号失配的区间个数。转移有：

+ 若 $S_r = \texttt ($，则 $f_r = f_{r - 1} + 1$；
+ 否则 $f_r = f_{lst_{c_r}} + 1$，其中 $lst_x$ 表示上一个 $u$ 满足 $c_u = x$，可以在扫一遍进行 dp 的同时用桶维护。

可以结合图示更好理解这一 dp 过程的正确性。

![](https://cdn.luogu.com.cn/upload/image_hosting/j6ff945n.png)

对于没有左括号失配，我们同理设计状态：

设 $g_l$ 表示对于所有 $l \leq r \leq n$，满足 $[l, r]$ 没有左括号失配的区间个数。转移有：

+ 若 $S_l = \texttt )$，则 $g_l = g_{l + 1} + 1$；
+ 否则 $g_l = g_{lst_{c_{l - 1}} + 1} + 1$，其中 $lst_x$ 表示下一个 $u$ 满足 $c_u = x$，同样可以在扫一遍进行 dp 的同时用桶维护。

以上可以自己画图理解。至于求完全匹配的区间个数，同样可以 dp 处理，留作习题。

总时间复杂度 $\mathcal O(n)$，绝世好题。

## Code

~~抽象程度顶级，我都怀疑这是不是我写的代码了。~~

```cpp
#include <bits/stdc++.h>
#define MAXN 4000005
int c[MAXN], cnt[MAXN], lst[MAXN], f[MAXN], g[MAXN];
void solve() {
	int N; std::string S; std::cin >> N >> S; long long ans = 1ll * N * (N + 1) / 2;
	++cnt[c[0] = N]; for (int i = 1; i <= N; ++i) ++cnt[c[i] = c[i - 1] + (S[i - 1] == '(' ? -1 : 1)];
	for (int i = 0, q = 0, p = N << 1; i <= p; ++i) { while (cnt[i]--) ans += (2ll * (q++) - N) * i; cnt[i] = 0; }
	memset(f, 0, sizeof(int) * (N + 5)), memset(g, 0, sizeof(int) * (N + 5)), memset(lst, 0, sizeof(int) * (N + 2 << 1));
	for (int r = 1; r <= N; ++r) ans += (g[r] = ((lst[c[r]] || c[r] == N) && S[r - 1] == ')' ? g[lst[c[r]]] + 1 : 0)) - (f[r] = (S[r - 1] == '(' ? f[r - 1] + 1 : (lst[c[r]] || c[r] == N) ? f[lst[c[r]]] + 1 : 0)), lst[c[r]] = r;
	memset(f, 0, sizeof(int) * (N + 5)), memset(lst, 0, sizeof(int) * (N + 2 << 1));
	for (int l = N; l; --l) ans -= (f[l] = (S[l - 1] == ')' ? f[l + 1] + 1 : lst[c[l - 1]] ? f[lst[c[l - 1]] + 1] + 1 : 0)), lst[c[l]] = l; std::cout << ans << '\n';
}
int main() { std::ios::sync_with_stdio(false); std::cin.tie(nullptr), std::cout.tie(nullptr); int T; std::cin >> T; while (T--) solve(); return 0; }
```

---

## 作者：Lgx_Q (赞：2)

绝世好题！！！

周末忘了月赛，我在众多人民的催促下肝出了这道题。

考虑一个括号序列最终匹配完后，必定会在左边留下若干个右括号，右边留下若干个左括号。如果同时存在左括号和右括号，那么可以通过 “变换” 操作来把右边的左括号移到左边去，消掉相等数量的左右括号。

设这个括号序列匹配完后留下了 $L$ 个左括号和 $R$ 个右括号，则代价

$$cost=\begin{cases} |L-R|+1 & L>0,\space R>0 \\ |L-R| & \text{otherwise} \end{cases}$$

回归题目。不难想到，应把 $cost$ 中的 $|L-R|$ 和 $+1$ 拆成两部分。设字符串 $s$ 中每个子串的 $|L-R|$ 的和为 $sum$，$L$ 和 $R$ 都非 $0$ 的子串个数为 $cnt$，则

$$ans=sum+cnt$$

先求 $sum$。对于一个子串，设其匹配的括号对数为 $X$，左括号个数为 $Ls$，右括号个数为 $Rs$，则：

$|L-R|=|(Ls-X)-(Rs-X)|=|Ls-Rs|$

于是直接求左括号个数与右括号个数的差的绝对值即可。我突然想到一题：[$\text{CF1750E}$](https://www.luogu.com.cn/problem/CF1750E)

把左括号看成 $1$，右括号看成 $-1$，做个前缀和，设前缀和数组为 $a$，那么子串 $[l,r]$ 的贡献为 $|a_r-a_{l-1}|$。

把 $a_0,a_1,...,a_n$ 排个序，就能去掉绝对值。由于数据过大，需要用桶排。

接下来求 $cnt$，即同时存在未匹配的左括号和右括号的子串个数。

考虑枚举子串左端点 $i\space(l=i)$，先求出以 $i$ 开始往右找，第一个未匹配的右括号位置 $p_i$。对答案有贡献的子串的右端点必定在 $[p_i,n]$ 范围内。算 $p_i$ 很简单，记录一个位置数组 $pos$，$pos(x)$ 表示当前 $[l,n]$ 中 $a_y=x$ 的最小的 $y$。那么 $p_i$ **即为 $a_y=a_{l-1}-1$ 的最小的 $y$**，即 $pos(a_{l-1}-1)$。

然后我们发现直接算有点困难，这时我想起另一道题：[$\text{CF1762F}$](https://www.luogu.com.cn/problem/CF1762F)

考虑 DP。设 $f(i)$ 表示以 $i$ 为左端点 $l=i$ 时的满足条件的子串个数。

此时 $p_i$ 就是我们的 DP 基准值。考虑找出从 $p_i+1$ 开始的第一个未匹配的右括号位置 $p'=p_{p_i+1}$，因为未匹配的右括号具有的优良性质，我们只需要求出有多少个满足条件的 $r\in[p,p'-1]$，剩下就直接从 $f(p_i+1)$ 转移。

现在的问题即为如何计算上述满足条件的 $r$ 的个数。再次根据未匹配右括号的优良性质，可以直接设 $Sum(i)$ 为右多少个满足条件的 $r\in[i,p_{i+1}-1]$。发现当 $a_r>a_i$ 时，$r$ 才符合条件。

$p_{i+1}$ 这个位置是除了 $i$ 的第一个未匹配的右括号，因此任何一个 $x\in [i,p_{i+1}-1]$，都满足 $a_x\ge a_i$。用 $K_i$ 表示 $r\in[i,p_{i+1}-1]$ 且 $a_r=a_i$ 的 $r$ 的个数，那么 $Sum(i)=p_{i+1}-i-K_i$，即我们只需要计算 $K_i$。

利用后缀和相减，给 $p_{i+1}$ 这个位置挂一个标记，离线扫一遍即可得到 $K$，进而算出 $Sum$。

最后直接转移

$$f(i)=Sum(i)+f(p_i+1)$$

$$cnt=\sum_{i=1}^nf(i)$$

$$ans=sum+cnt$$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn=2e6+10;
ll t,n,a[maxn],cnt[maxn*2],ans,g[maxn],sum[maxn],head[maxn],tot,w[maxn*2],f[maxn];
char s[maxn];
struct node
{
	ll x,nxt;
}b[maxn];
void insert(ll p,ll x)
{
	b[++tot]=(node){x,head[p]};
	head[p]=tot;
}
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%s",&n,s+1);
//		memset(sum,0,sizeof sum);
//		memset(g,0,sizeof g);
		//memset(head,0,sizeof head);
		//memset(w,0,sizeof w);
		//memset(f,0,sizeof f);
		//memset(cnt,0,sizeof cnt);
		for(ll i=0;i<=n*2;i++) cnt[i]=0;
		++cnt[n];
		head[n+1]=0;
		for(ll i=1;i<=n;i++)
		{
			head[i]=0;
			a[i]=a[i-1]+(s[i]=='('? 1:-1);
			++cnt[a[i]+n];
		}
		ans=tot=0;
		for(ll i=0,j=0,k=0;i<=n*2;i++)
		{
			ans+=i*j*cnt[i]-k*cnt[i];
			j+=cnt[i]; k+=cnt[i]*i;
			cnt[i]=0; w[i]=n+1;
		}
		g[n+1]=n+1; sum[n+1]=f[n+1]=f[n+2]=0;
		for(ll i=n;i;i--)
		{
			w[a[i]+n]=i;
			++cnt[a[i]+n];
			if(a[i-1]>-n) g[i]=w[a[i-1]-1+n];
			else g[i]=n+1;
			insert(g[i+1],i);
			sum[i]=cnt[a[i]+n];
		}
		for(ll i=0;i<=n*2;i++) cnt[i]=0;
		for(ll i=n;i;i--)
		{
			++cnt[a[i]+n];
			for(ll j=head[i];j;j=b[j].nxt)
			{
				ll x=b[j].x;
				sum[x]-=cnt[a[x]+n];
			}
		}
		for(ll i=n;i;i--)
		{
			sum[i]=g[i+1]-i-sum[i];
			f[i]=sum[g[i]]+f[g[i]+1];
			ans+=f[i];
			//printf("f[%lld] = %lld\n",i,f[i]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---


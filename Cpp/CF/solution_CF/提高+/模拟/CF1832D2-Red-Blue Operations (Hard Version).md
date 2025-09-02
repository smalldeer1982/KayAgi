# Red-Blue Operations (Hard Version)

## 题目描述

The only difference between easy and hard versions is the maximum values of $ n $ and $ q $ .

You are given an array, consisting of $ n $ integers. Initially, all elements are red.

You can apply the following operation to the array multiple times. During the $ i $ -th operation, you select an element of the array; then:

- if the element is red, it increases by $ i $ and becomes blue;
- if the element is blue, it decreases by $ i $ and becomes red.

The operations are numbered from $ 1 $ , i. e. during the first operation some element is changed by $ 1 $ and so on.

You are asked $ q $ queries of the following form:

- given an integer $ k $ , what can the largest minimum in the array be if you apply exactly $ k $ operations to it?

Note that the operations don't affect the array between queries, all queries are asked on the initial array $ a $ .

## 样例 #1

### 输入

```
4 10
5 2 8 4
1 2 3 4 5 6 7 8 9 10```

### 输出

```
3 4 5 6 7 8 8 10 8 12```

## 样例 #2

### 输入

```
5 10
5 2 8 4 4
1 2 3 4 5 6 7 8 9 10```

### 输出

```
3 4 5 6 7 8 9 8 11 8```

## 样例 #3

### 输入

```
2 5
2 3
10 6 8 1 3```

### 输出

```
10 7 8 3 3```

# 题解

## 作者：spider_oyster (赞：11)

ch-translater 来了。

先相信，再相信。

$k<n$ 很简单，不讲。

### 先说性质。

>- 每个数在【最终加】（最后一次加）之前，一定比原数小。于是我们要让【最终加】最大。

>- 【最终加】的条件是当前数之前被操作偶数次。

>- 【操作】（对同一个数连续进行两次操作）会令一个数变化 $1$。由上述性质，只会有 $-1$ 【操作】。

### 考虑将操作反过来。

先对数组里每个数进行【最终加】。

于是将 $a_i$ 从小到大排序，则前 $n$ 次操作最优是让 $a_i+k-i+1$。发现 $k$ 是常量，可以提出来，让最后输出答案时再加 $k$，以降低耦合度。

于是构造数组 $b_i=a_i-i+1$，并记 $b$ 的前缀最小值数组 $p$，再记 $b$ 数组和为 $s$。

这时还剩余 $k-n$ 个操作。

#### 若 $k \bmod 2=n \bmod 2$：

剩下偶数次操作。根据性质，这时会对执行 $(k-n)/2$ 次 【操作】。

前 $n$ 次操作后当前最小值为 $mi=p_n$。

注意这时对非最小值操作不会影响答案。于是可以【操作】 $s-mi\times n$ 次。

【操作】完后，会发现所有数相同了，这时再对 $n$ 个数整体进行【操作】。

 答案：$k+mi-\lceil \frac{(k-n)/2-(s-mi\times n)}{n}  \rceil$。
 
#### 若 $k \bmod 2\ne n\bmod 2$：

会多出一次操作。这东西很恶心，会令【最终加】少一次。考虑舍弃 $a_n$ 的【最终加】。

此时最小值为 $mi=\min(p_{n-1}+k,a_n)$。

同时注意 $s$ 的变化。

剩下的计算与 $k \bmod 2=n\bmod 2$ 相同。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
 
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,q;cin>>n>>q;
    vector<int> a(n+1),p(n+1,2e9);
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a.begin()+1,a.end());
    p[1]=a[1];
    for(int i=2;i<=n;i++) p[i]=min(p[i-1],a[i]-i+1);
    int s=0;
    for(int i=1;i<=n;i++) s+=a[i]-i+1;
    for(int i=1;i<=q;i++)
    {
        int k;cin>>k;
        if(k<n) cout<<min(p[k]+k,a[k+1])<<' ';//只对前 k 个数进行【最终加】
        else if(k%2==n%2) cout<<p[n]+k-(int)ceil(max(0ll,(k-n)/2-(s-p[n]*n))*1.0/n)<<' ';
        else
        {
            int mi=min(p[n-1],a[n]-k);//由于最终答案+k,所以把 min(p[n-1]+k,a[n]) 变一下
            int _s=s+n-1-k-mi*n;//注意 a[n]-n+1 变为 a[n]-k
            cout<<mi+k-(int)ceil(max(0ll,(k-n+1)/2-_s)*1.0/n)<<' ';
        }
    }
}
```


---

## 作者：2018ljw (赞：8)

线性做法。

首先判掉 $n=1$ 的极端情况，这时直接计算值即可。

显然每个数的操作序列是值递增的加减循环。若一个数被操作了正偶数次，那么其值一定小于初值，是不优的。

所以我们希望每个数最后被操作奇数次或不操作，而显然当 $n\ge 2$ 时这是很容易达成的，只需要控制被操作的数个数的奇偶性即可。

先考虑，假设我们知道要对特定的 $x$ 个数做操作，如何最优化操作分配。

对于一个被操作的数，我们将其被操作的时间序列 $t_1\dots t_{2x+1}$ 划分为若干组。$t_{2i}$ 与 $t_{2i-1}$ 分为一组，$t_{2x+1}$ 单成一组。发现有且仅有最后一组是正贡献，其余组均为负贡献。

为了让负贡献尽可能小，令 $t_{2i}=t_{2i-1}+1$，这样每组负贡献就只有 $-1$ 了。为了让正贡献尽量大，即让所有的 $t_{2x+1}$ 尽可能大，只需要取最后几次操作即可。并且为了最大化最小值，越小的数分配到的应该越大。

接下来有一个很 trival 的想法：二分答案 $mid$，得到哪些数要被操作。如果奇偶性不对就挑一个 $\ge mid$ 的数操作一次。然后整个序列分摊负贡献，计算操作次数够不够，以及能不能摊开。

这个二分是很显然的，复杂度 $O(n\log n+q\log V)$。

但对于一个静态的序列，每次都二分未免有些过于浪费了吧？

$k<n$ 时直接贪，否则我们可以把操作序列转化成如下形式：

1. 让 $a_i$ 加上 $k-i+1$。
2. 执行 $\frac {k-n}2$ 次，最大的数 $-1$。

根据之前分组思想，这样一定是最优的分配。

需要注意的是，若 $k-n$ 为奇数，则最初不让 $a_n$ 加上 $k-n+1$。这样一定是优秀的，否则一定有某个位置操作了偶数次，更小的数小于初值不如最大的数等于初值。

这样视 $k-n$ 的奇偶性，我们可以得到两种序列 $b,c$，其中 $b_i=a_i-i+1$，$c_i=\begin{cases}a_i-i+1&i\neq n\\a_n&i=n\end{cases}$。

这里近似的相当于把全局 $+k$ 提了出来。需要注意如果是真正的全局 $+k$ 的话需要让 $c_n=a_n-k$。但因为 $k$ 是变量不方便预处理，所以我们先不减去。

然后处理操作 $2$，不难发现分为三个阶段。

1. 所有数减到 $\min\{a_i\}$。
2. 每次全局 $-1$，消耗 $2n$ 次操作数。
3. 若还有剩余的操作数，则单点 $-1$。

计算操作 $2$ 唯二需要知道的是，二阶段的初值是多少，以及一阶段一共花了多少步。对于二三阶段，有了这些信息可以直接 $O(1)$ 算。而花费步数为元素之和减去最小值的 $n$ 倍，初值为序列最小值。

那么维护 $b_{1\dots n}$ 与 $c_{1\dots n-1}$ 的 $\min$ 和元素和，每次计算 $c$ 序列的时额外计算 $c_n-k$ 即可。

若 $k-n$ 为偶数则用 $b$ 序列计算，否则用 $c$ 序列计算，最后记得加上 $k$。单次询问复杂度 $O(1)$。

发现 $b,c$ 序列只有最后一项不同，所以只需要维护前 $n-1$ 项，最后一项基于 $k-n$ 分讨一下，复杂度上没优化，但可以精简写法。

复杂度瓶颈在排序，可使用基数排序做到近似 $O(n+q)$。

需要注意减法占用两次操作次数，各种计算里别忘了乘除 $2$。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
const int base=40000;
using namespace std;
int n,a[200001],b[200001];
int key[200001],cnt[40001];
int pre[200001];
int getkey(int x,int k){
	while(k-->1)x/=base;
	return x%base;
}
void srt(){
	int i,j;
	for(i=1;i<=3;i++){
		memset(cnt,0,sizeof(cnt));
		for(j=1;j<=n;j++)key[j]=getkey(a[j],i),cnt[key[j]]++;
		for(j=1;j<base;j++)cnt[j]+=cnt[j-1];
		for(j=n;j;j--)b[cnt[key[j]]--]=a[j];
		for(j=1;j<=n;j++)a[j]=b[j];
	}
}
long long sum;
int mn,k;
int calc_1(){return a[1]-k/2+(k&1)*k;}
int calc_lsr(){return min(a[k+1],pre[k]+k);}
int calc(){
	long long rsum=sum;
	int rmn=mn,val=a[n];
	if((n-k)&1)val-=k;
	else val-=n-1;
	rsum+=val;rmn=min(rmn,val);
	long long use=rsum-1ll*n*rmn;
	int res=rmn+k;
	k-=n;if(k&1)k++;
	if(use*2>=k)return res;
	k-=use*2;
	int st=k/n/2;
	res-=st;k-=st*n*2;
	if(k)res--;
	return res;
}
int main(){
	int i,j,q;
	scanf("%d%d",&n,&q);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	srt();
	for(i=1;i<n;i++)b[i]=a[i]-i+1;
	mn=b[1];
	for(i=1;i<n;i++){
		sum+=b[i];
		mn=min(mn,b[i]);
		pre[i]=mn;
	}
	while(q--){
		scanf("%d",&k);
		int res;
		if(n==1)res=calc_1();
		else if(k<n)res=calc_lsr();
		else res=calc();
		printf("%d ",res);
	}
}
```

---

## 作者：inc1ude_c (赞：6)

看到“最小值的最大值”，考虑二分答案 $x$，判断能否在恰好 $k$ 次内将最小值变为 $x$。

将 $a$ 升序排序，看一下有多少个数小于 $x$，记个数为 $c$。$x$ 可才是最终序列最小值，所以要把这些小于 $x$ 的给消灭掉，具体就是给最小的加上一次最大的操作，即进行操作使之变为 $a'_1=a_1+k,a'_2=a_2+k-1,\cdots,a'_c=a_c+k-c+1$。

但如果都这么做了，还是无法避免出现小于 $x$ 的元素，那么就无解。

否则，还要用掉 $k-c$ 次操作，可以发现给一个数连续操作两次会让其 $-1$，所以把操作那前 $c$ 个数，因为我们刚刚粗略地操作后会让数大于 $x$，实际上让数与 $x$ 齐平即可，所以看看超出了 $x$ 多少，超了多少就连续两次操作多少次。

记 $s=\sum_{i=1}^ca'_i-x$，那么可以操作 $s\times 2$ 次。

再看看这 $k-c-s\times 2$ 次操作，记该数为 $h$。

- 如果 $n=c$，已经无数可操作，无解。

- 如果 $h$ 是奇数，那么全加在一个数上，由于操作数是奇数所以这个数一定是变大的。

- 如果 $h$ 是偶数，如果 $n-c\ge2$，那么把 $h$ 分成两个奇数，选两个数分别加奇数次

- 否则，将这 $h$ 次操作搞在最大的 $a_n$ 上，即看看 $a_n-\frac{h}{2}$ 是不是 $\ge x$。

---

## 作者：hgzxwzf (赞：6)

### [CF1832D2](https://www.luogu.com.cn/problem/CF1832D2)
一个数只有被操作奇数次才会加，一定是能构造出一组使所有数都大于等于它原本的值的方案的，这样肯定最优。

对于 $a_i$，设选它的操作为 $b_{1},b_2,\dots,b_k$，$a'_i=\sum_{j=1}^k(-1)^{j+1}b_j$，$k$ 一定是奇数，为了让 $\sum_{j=1}^{k-1}(-1)^{j+1}b_j$ 更小，最优的策略是使得 $b_j-b_{j-1}=1$。

现将 $a$ 按从小到大排序，二分答案 $x$。

二分得到 $<x$ 的数的个数 $c$。越小的数要加得越多，所以最优方案中，对于 $i\le c$，最后一次对 $i$ 操作为 $k-i+1$，即 $a_i'=a_i+k-i+1$。如果 $\min_{j=1}^ca'_j<x$，那么无力回天了。否则，还要用掉剩下的 $k-c$ 次操作，设 $s=\sum_{j=1}^ca'_j-x$，前 $c$ 个数可以承担 $2\times s$ 此操作，还剩 $k-c-2\times s$ 次操作分配给后面的 $n-c$ 个数。

- $n-c=0$，无解。
- 如果 $k-c-2\times s$ 是奇数，全操作在一个数上，它一定会加。
- 如果 $n-c\ge 2$，可以选两个数分别操作奇数次。
- 否则，判断 $a_n-\frac{k-c-2\times s}{2}$ 是否 $\ge x$ 即可。

[代码](https://codeforces.com/contest/1832/submission/205714793)。


---

## 作者：Kingna (赞：5)

看着大佬们强大到我看不懂的做法，本蒟蒻只能自己研究。


## 思路
答案具有单调性，考虑二分答案 $x$。可以知道， $a$ 数组中所有小于 $x$ 的数，需要进行一波操作使得它大于等于 $x$。设小于 $x$ 的数从小到大为 $a_1,a_2,\cdots,a_m$，然后贪心的分配数 $1,2,\cdots,k$。

---

**贪心策略：**

对于一个数 $a_i$，我们假设最后分配给它的数有 $t$ 个，那么有：
$$a_i'=a_i+p_1-p_2+\cdots+(-1^{1-t\bmod2})p_t$$

因为 $p_1<p_2<\cdots<p_t$，所以当 $t$ 为奇数时值变大，偶数时值变小。显然，所有小于 $x$ 的数都要分配奇数个。

将 $k,k-1,\cdots,k-m+1$ 这 $m$ 个数依次分配到 $a_1,a_2,\cdots,a_m$，得到 $a_1',a_2',\cdots,a_m'$，如果这些数的最小值依然小于 $x$，那肯定没救了（想一想，为什么）。

如果还有救，那么我们继续分配 $1,2,3,\cdots,k-m$，考虑用大于等于 $x$ 的 $a_{m+1},a_{m+2},\cdots,a_n$ 来救援。

若 $k-m\le n-(m+1)+1$，即 $k\le n$。$1,2,3,\cdots,k-m$ 每个数都可以单独使用一个 $a_i$，救援成功。

若 $k-m$ 为奇数，可以直接将 $1$ 至 $k-m$ 所有数塞到同一个剩余 $a_i$ $^{\dagger}$
中（保证不减），但如果连一个剩余的都没了，绝对失败。（因为所有小于 $x$ 的 $a_i$ 都要分配奇数个）

若 $k-m$ 为偶数，可以分成两个奇数来塞到剩余 $a_i$ 中，若剩余 $a_i$ 没有两个空位，此时可以用大招来最后一波挽救。把 $1$ 至 $k-m$ 拆成 $+1,-2,+3,-4$ 这样的形式，每次代价为 $-1$，且这样代价最小。此时只需要直接去抵消所有大于 $x$ 的 $a_i$，但如果 $a_i$ 全都变为 $x$ 了还没抵消完，没救咧。

$^{\dagger}$：剩余 $a_i$ 指 $a_{m+1},a_{m+2},\cdots,a_n$，同一个剩余 $a_i$ 指 $a_{m+1},a_{m+2},\cdots,a_n$ 中其中一项。

## 代码
这道题很有价值，结合代码慢慢体会。

```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 5;

int n, q, k, a[N], sum[N], b[N], pref_mn[N], pref_b[N];

int check(int x) {
	int cnt = lower_bound(a + 1, a + n + 1, x) - a - 1;
	if (cnt == 0) {
		if (n == 1 && k % 2 == 0) return a[1] - k / 2 >= x;
		return 1;
	}
	if (pref_mn[cnt] + k < x) return 0;
	if (k <= n) return 1;
	if ((k - cnt) % 2 == 1) return n > cnt;
	if ((n - cnt) >= 2) return 1;
	else {
		int tmp = pref_b[cnt] + k * cnt + sum[n] - sum[cnt] - n * x;
		return tmp >= (k - cnt) / 2;
	}
	
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
	for (int i = 1; i <= n; i++) b[i] = a[i] - i + 1, pref_b[i] = pref_b[i - 1] + b[i];
	pref_mn[1] = b[1];
	for (int i = 2; i <= n; i++) pref_mn[i] = min(pref_mn[i - 1], b[i]);
	
	while (q--) {
		cin >> k;
		int l = -1e18, r = 1e18;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			if (check(mid)) l = mid;
			else r = mid - 1;
		}
		cout << l << ' ';
	}
}
```

---

## 作者：Loser_Syx (赞：2)

挺牛的题。

要求最小值最大，首先考虑二分。

我们考虑翻蓝再翻红这个操作带来的收益是负的，而要使能“浪费”的操作次数最多，那么一定要负的最小也就是 $-1$。即翻蓝之后马上翻红，收益是 $-1$。

我们不妨根据二分的 $x$，划分为两类。一类是 $a_i < x$ 的，这类要求对他们的最后一次操作一定得加，而且总值还得 $\geq x$。相对的，对于 $a_i \geq x$ 的数，就是上述“浪费次数”的类型。

对于第一类，贪心安排，我们将其从小到大排序，对于越小的，我们令他去加越大的 $k$，换而言之，对于 $i$，我们令他加上 $k-i+1$，使得答案尽可能大。

但是这也是最大的情况了，如果还是无法满足这个值 $\geq x$，便是无解。具体可以维护 $a_i -i+1$ 的 $\min$，然后判断 $k+ \min\geq x$ 即可。

剩下的情况，将会有几个数多出来的情况，可以考虑把这些多的全部浪费掉，设有 $m$ 个 $< x$ 的数，则可以浪费 $w=2 \times (\sum_{i=1}^m a_i-i+1 + mk)$ 次，这是好维护的。

那么显然，我们剩下有 $s=k-m-w$ 次操作，对 $s\ (s > 0)$ 值以及 $m$ 分类讨论。

- $m=n$

  无解。

- $s \bmod 2=1$

  操作可以全给一个数。且 $s > \frac{s}{2}$故有解。

- $n-m \geq 2$

  操作分为两个 $s \bmod 2=1$ 给两个数，有解。

- $n-m=1$

  操作只能给一个数，所以直接判 $a_n - x \geq \frac{s}{2}$。

瓶颈在二分和内层 check 找到第一个 $a_i \geq x$ 的数的二分。复杂度 $O(n \log^2 n)$。

[code](https://codeforces.com/contest/1832/submission/289930316)。

---

## 作者：zrl123456 (赞：1)

现在才发现已经一个半月没写题解了。  

[Red-Blue Operations (Hard Version) ](https://www.luogu.com.cn/problem/CF1832D2)  

题目考察：二分，前缀和（极值），贪心，排序。  
题目简述：  
给你一个序列 $\{a_n\}$，还有一个初始值均为 $0$ 的序列 $\{b_n\}$，有 $q$ 次询问，每次询问若有 $k$ 次操作，对于第 $i$ 次操作（$i\in[1,k]$），选择一个 $j\in[1,n]$，使得 $a_j$ 加上 $(1-num_j\bmod 2)\times i$ 后再将 $num_j$ 加 $1$，最后求 $\displaystyle\min_{i=1}^na_i$ 的最大值。  
数据范围：
- $1\le n,q\le 2\times 10^5$
- $\forall i\in[1,n],1\le a_i\le 10^9$
- $1\le k\le 10^9$
---
显然，一个数被操作奇数次才可能被加。  
> 注释 $1$：对于 $\{x_{2k}\}$,$\forall i\in[1,2k),x_i<x_{i+1}$，则 $\forall i\in[1,k],x_{2k-1}-x_{2k}<0$，其和显然小于 $0$。  

所以说，为了让 $x_{2k-1}-x_{2k}$ 更大，我们让 $x_{2k-1}-x_{2k}=-1$，即对一个数的操作一定是一个区间。  

考虑二分答案，二分数组最小值 $x$。在二分前将序列升序排序，以便我们快速找到小于数组最小值的数，这件事我们可以用二分实现。  
二分找到小于该数的的数目 $sum$ 后，贪心的想，我们肯定要把最后一次操作作用在第一个数上，如果这样，我们只能对他做 $1$ 次操作。  
> 注释 $2$：如果我们对其做 $3$ 次操作，那么贡献为 $k-(k-1)+(k-2)=k-1<k$。

那么这样的话，$\forall i\in[1,sum]$,$a_i$ 将会变为 $a_i+(k-i+1)$，如果 $\displaystyle\min_{i=1}^{sum}a_i+k-i+1<x$，则无法达到目标。  
  > 注释 $3$：对于 $a_i+k-i+1$ 我们可以将 $k$ 提出，在一开始（排序后！排序后！排序后！）对 $a_i-i+1$ 做前缀最小值，在 `check` 函数内再将 $k$ 加回。

这时还剩 $k-sum$ 次操作，在前面的 $sum$ 个数上应该会有一些数比 $x$ 要大，那么在那些数上进行 $2$ 次操作，使该数减 $1$。  
> 注释 $4$：若所有的数都比要求的数要小（$sum=n$）且剩余操作数为奇数，则需要撤销一个数的操作凑成偶数，但实际无法撤销任何一个数，故无法达到要求。
> 
> 注释 $5$：若 $num_i=\sum_{j=1}^ia_i+k-i+1$，则在这些数上的操作数为 $2(num_{sum}-sum\times x)$，维护 $num_i$ 的方法类比注释 $3$。

设还剩 $lft=k-sum-2(num_{sum}-sum\times x)$ 次操作，那么剩下的就要在 $i\in[sum+1,n]$ 的 $a_i$ 上操作了。  
> 注释 $6$：$lft\le 0$，直接判定可达到要求即可。
>
> 注释 $7$：若剩余一些操作（$lft>0$）且无剩余数（$sum=n$），则判定无法达到要求。

若 $lft\bmod 2=1$，则在一个数上操作一定会增加，证明请类比注释 $1$。  
否则因为奇数加奇数为偶数，那么如果剩余两个数（$n-sum\ge 2$）则在两个数上分别操作奇数次，证明仍然类比注释 $1$。  
否则只剩 $1$ 个数，判定 $\displaystyle a_n-\frac{lft}{2}$ 是否大于等于 $x$ 即可。  

[代码](https://www.luogu.com.cn/paste/hvi65lay)

---

## 作者：E1_de5truct0r (赞：1)

拙劣的 $O(n \log^2 n)$ 做法，但是好想！

首先它让求最小值最大，肯定是二分答案。那么复杂度就至少是 $O(q \log n)$ 了，我们最多还剩一只 $\log$ 来判断我们二分的最小值是否可行。

假设二分的答案是 $x$。

通过手玩可知，最优策略显然是 $k \rightarrow a_1,(k-1) \rightarrow a_2,\dots,(k-n+1)\rightarrow a_n$。如果 $k<n$，那么就把前 $k$ 个处理了。

我们需要快速求出这些数的最小值是多少。假设 $b_i$ 是后来的值，不难发现如果发生了修改，则 $b_i=(k-i+1)+a_i=(k+1)+(a_i-i)$，否则 $b_i=a_i$。很明显这两个的最小值都是容易在预处理后单次 $O(\log n)$ 内求出的。

但是如果 $k>n$，我们达不到这个上界。这个时候我们每添加两个相邻的奇数和偶数操作，就会使答案减少 $1$、操作次数减少 $2$。
如果剩余操作次数是偶数次，那么直接一对一对处理就好了；否则
我们需要减小一个数的值。我们不妨减小到最大的 $a_n$ 上，然后就是暴力了。

我们需要求出 $(\sum b_i-xn) \times 2$ 的值，这是我们能容纳的最大的额外操作次数。如果容纳不下就寄了，否则就证明可以达到这个值。

复杂度 $O(n \log^2 n)$。

[Code & Submission](https://codeforces.com/contest/1832/submission/224182671)

---

## 作者：orz_z (赞：1)

由 `D1` 的结论，将最后 $n$ 个操作倒序加入原数组，然后每个数用偶数次操作，每两次操作 $-1$，最后可能剩下一个操作，加到最大数上。

感性理解，由于要使得最后的操作是 $+$，那么前面一定是 $+-+-+-$ 排列的，那么每次 $-1$ 最优。

考虑二分答案。

考虑“最后 $n$ 个操作倒序加入原数组”的操作，记 $a_i'$ 为 $a_i+k-i+1$，则 $a_i$ 变为 $a_i'$。

记 $<x$ 的数有 $c$ 个，如果 $\min_{j=1}^{c}a_j'<x$，那么无解。

否则，用掉 $c$ 次操作，剩下 $k-c$ 次，设 $s=\sum_{j=1}^{c}a_j'$，则前 $c$ 个数可消耗掉 $2s$ 次操作，那么剩下 $k-c-2s$ 次操作分给后面 $n-c$ 个数。

如果 $n-c=0$，无解。

如果 $k-c-2s$ 为奇数，那么全部分给一个数，显然增加，必然有解。

如果 $n-c\ge 2$，那么选择两个数分别操作奇数次，由上，必然有解。

否则，剩下偶数次操作，只能分给一个数，那么 $a_n$ 必须减去 $\frac{k-c-2s}{2}$，判断是否 $\ge x$ 即可。

时间复杂度 $\mathcal O(q\log k)$。

---

## 作者：ka_da_Duck (赞：0)

分情况讨论。

- $k\le n$ 时，
  
  我们容易想到给一个位置不断地更新，但是这样明显不是最优解，那么，我们可以利用题目所给的每一个的初始红色。

  先把数组从大到小进行排序，再从前往后依次给 $a_i$ 加上 $1,2,\ldots, k$，最后扫一遍求出最大值，时间复杂度 $O(n\log n)$。
  
- $k>n$ 时，

  先消耗 $n$ 次操作，对其按照 $k\le n$ 的做法更新，此时所有位置都是蓝色的。我们对每个数做偶数次操作，每两次操作 $+1$，最后可能剩下一个操作（减），我们把它丢给最大的，再计算最大值。如果 $k-n$ 是偶数，那就要减 $\dfrac{k-n}{2}$，如果是奇数，就减 $\dfrac{k-n+1}{2}$，时间复杂度 $O(1)$。

最终的时间复杂度就是 $O(n\log n+k)$。

代码

```cpp
#include <bits/stdc++.h>
#define int long long
 
using namespace std;
const int maxn = 3e5 + 20;
 
int n, q, s, x, o, ans;
int a[maxn], f[maxn];
 
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) cin >> a[i], s += a[i];
	sort(a + 1, a + n + 1);
	fill(f + 1, f + n + 10, 1e18);
	for (int i = 1; i <= n; ++i) f[i + 1] = min(f[i], a[i]) + 1;
	while (q--) {
		cin >> x;
		if (x < n) cout << min(f[x + 1], a[x + 1]) << ' ';
		else {
			ans = 0, o = s;
			if (!((x - n) & 1)) {
				ans = f[n + 1] + x - n;
				o += n * (x * 2 - n + 1) / 2 - (x - n) / 2;
			} else {
				ans = min(f[n] + x - n + 1, a[n]);
				o += (n - 1) * (x * 2 - n + 2) / 2 - (x - n + 1) / 2; 
			}
			cout << min(ans, o / n) << ' ';
		} 
	}
}

```

---

## 作者：Erotate (赞：0)

考虑二分答案。

记二分的值为 $x$，设 $a$ 数组中小于 $x$ 的数共有 $c$ 个，那么显然我们把 $a$ 数组从大到小排序后，对于前 $c$ 个数，要把它变为 $a_i = a_i + k - i + 1$，如果此时还存在 $a_i < x$ 那么直接返回，因为没有办法使得它更大了。

考虑剩下的 $k - c$ 次操作，如果满足 $k - c \leq n - c$ 即 $k \leq n$，也就是每一个剩下的数都能加上一个数，此时显然符合要求。

否则我们按 $k - c$ 的奇偶性来讨论：

1. $k - c$ 为奇数，可以直接在一个数上进行完这 $k - c$ 次操作。因为这 $k - c$ 次操作的数是连续的，如果都在同一个数上进行操作，那么它的操作序列必然是 $+-+-+- \dots +$，前 $k - c - 1$ 次操作，每两次操作会使这个数减一，也就是最后一共会加上 $k - c - \frac{k - c - 1}{2} = \frac{k - c + 1}{2}$，显然这是个正数，满足要求。但如果没有剩下可以操作的数了，那么必然失败。

2. $k - c$ 为偶数，可以把它分成两个奇数，按上面的方法选两个数来操作。如果找不到两个这样的数，考虑把每一个大于 $x$ 的 $a_i$ 都分配一段连续的操作，这样对于一个数还是每两次操作减一。如果每一个数分配完后，也就是每一个数都减成 $x$ 了，还有剩余的操作，那么就失败了，否则就是成功的。


```cpp
const int N = 2e5 + 5, inf = 2e9 + 1;
int n, q, k, a[N], sum[N], b[N], premn[N], preb[N];
bool check(int x){
	int cnt = lower_bound(a + 1, a + n + 1, x) - a - 1;
	if(!cnt){
		if(n != 1 || k & 1) return 1;
		return a[1] - k / 2 >= x;
	}
	if(premn[cnt] + k < x) return 0;
	if(k <= n) return 1;
	if(k - cnt & 1) return n > cnt;
	if(n - cnt >= 2) return 1;
	else return preb[cnt] + k * cnt + sum[n] - sum[cnt] - n * x >= (k - cnt) / 2; 
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
	n = read(), q = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
	premn[0] = inf;
	for(int i = 1; i <= n; ++i){
		b[i] = a[i] - i + 1;
		preb[i] = preb[i - 1] + b[i];
		premn[i] = min(premn[i - 1], b[i]);
	}
	while(q--){
		k = read();
		int l = -1e18, r = 1e18, ans = 0;
		while(l <= r){
			int mid = l + r >> 1;
			if(check(mid)){
				ans = mid;
				l = mid + 1;
			}else r = mid - 1;
		}
		write(ans), putchar(' ');
	}
    return 0;
}
```

---

## 作者：Leasier (赞：0)

当 $k \leq n$，一个显然的贪心是：对于第 $i \leq k$ 小的值加上 $k - i + 1$。

当 $k > n$，由于无论加减，变化量的绝对值单调递增，我们不难发现：

- 设 $a_i$ 被操作了 $cnt_i$ 次，分别为 $b_1, -b_2, \cdots, (-1)^{cnt_i - 1} b_{cnt_i}$。
- 若 $cnt_i$ 为奇数，$a_i$ 最终不小于原值；否则，$a_i$ 最终不大于原值。

一个简单的想法是让 $a_i$ **全部不小于原值**，但这并不一定可以实现。

若有两个 $a_i, a_j$ 小于原值，我们将 $a_i$ 的最后一次操作移到 $a_j$ 上即可。于是至多只有一个 $a_i$ 小于原值。

1. $k \equiv n \pmod 2$

此时我们可以让 $a_i$ 全部不小于原值。

对于一个 $a_i$，考虑**分组配对**：我们将 $(b_{2j - 1}, b_{2j})$ 分组配对，则组内贡献为负。我们希望负的尽量小，于是考虑让 $b_{2j} - b_{2j - 1} = 1$；对于最后一次操作 $b_{cnt_i}$，其贡献为正，我们希望正的尽量大，于是我们把**此时**第 $j$ 小的值加上 $k - j + 1$。

于是一个 naive 的想法就是在前面的 $\frac{k - n}{2}$ 对操作中把大的数改小使之尽量平均，然后再排序加上正贡献。

直接模拟的时间复杂度为 $O(qn \log n)$，可以通过 Easy Version，但仍不够优秀。

考虑把整个过程“**对偶**”一下：我们先把**一开始**第 $j$ 小的数加上 $k - j + 1$；然后每次选出最大的 $a_i$ 减 $1$。

这个东西的实质就是：

- 减到全部相同之前 $\min$ 不变。
- 减到全部相同以后整体减。

于是容易通过预处理快速求解。

2. $k \not\equiv n \pmod 2$

此时我们必须选出一个 $a_i$，使之小于原值。

考虑延续“对偶”后的结果：不难发现唯一的区别在于我们需要选择一开始最大的数不加。

于是类似地处理即可。

综上，时间复杂度为 $O(n \log n + q)$。

代码：
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int a[200007], b[200007], preb[200007], sufa[200007];
ll sumb[200007];

int main(){
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++){
		b[i] = a[i] - i + 1;
	}
	preb[0] = 0x7fffffff;
	for (int i = 1; i <= n; i++){
		preb[i] = min(preb[i - 1], b[i]);
		sumb[i] = sumb[i - 1] + b[i];
	}
	sufa[n + 1] = 0x7fffffff;
	for (int i = n; i >= 1; i--){
		sufa[i] = min(sufa[i + 1], a[i]);
	}
	for (int i = 1; i <= q; i++){
		int k;
		ll ans;
		cin >> k;
		if (k <= n){
			ans = min(preb[k] + k, sufa[k + 1]);
		} else {
			int min_val;
			ll sum, t;
			if (k % 2 == n % 2){
				min_val = preb[n];
				sum = sumb[n];
			} else {
				int lst = a[n] - k;
				min_val = min(preb[n - 1], lst);
				sum = sumb[n - 1] + lst;
			}
			ans = k + min_val;
			t = (k - n + 1) / 2 - (sum - (ll)n * min_val);
			if (t > 0) ans -= (t - 1) / n + 1;
		}
		cout << ans << " ";
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：0)

首先，如果一个点变成蓝色，在下一次立刻把它变成红色最优。这样对这个点造成的影响是减 $1$。直观感受一下，这样能最小化损失。并且在最后几次操作，可以把大部分甚至所有点变成蓝色。具体地，特判 $m \le n$ 的情况后，如果 $m$ 和 $n$ 奇偶性相同，最后 $n$ 次操作会把所有点变成蓝色，否则最后 $n - 1$ 次操作会把其中 $n - 1$ 个点变成蓝色。

考虑二分。设二分最小值为 $x$。首先可以确定最后 $n$ 或 $n - 1$ 次操作的对象，一定是让最小值加 $m$，次小值加 $m - 1$，以此类推。所以可以先对原数组排序，然后根据奇偶性分类讨论。

- 如果 $m,n$ 奇偶性相同，如果 $\min\limits_{i=1}^n a_i + m - i + 1 - x < 0$ 就寄了，因为就算对这个值不进行减 $1$，它都无法达到 $x$；然后如果 $\sum\limits_{i=1}^n a_i + m - i + 1 - x < \frac{m - n}{2}$ 也寄了，因为需要 $\frac{m - n}{2}$ 次对其中某个元素减 $1$，如果满足这个条件就不够减；否则可行。

- 如果 $m,n$ 奇偶性不同，最后会剩一个值加不了。这个值取 $a_n$ 显然最优。在接下来的判断需要对 $a_n$ 特殊处理。如果 $a_n < x$ 或者 $\min\limits_{i=1}^{n-1} a_i + m - i + 1 - x < 0$ 或者 $a_n - x + \sum\limits_{i=1}^{n-1} a_i + m - i + 1 - x < \frac{m - (n - 1)}{2}$ 就寄了，否则可行。

直接暴力判断可以[通过 D1](https://codeforces.com/contest/1832/submission/206414836)。考虑优化。发现要判断的值只与 $\sum\limits_{i=1}^n a_i - i$ 和 $\min\limits_{i=1}^n a_i - i$ 有关，可以做到 $O(1)$ 判断。~~但是我急急忙忙敲了个整体二分才发现（~~

[这个](https://codeforces.com/contest/1832/submission/206416183)是整体二分的实现。

---


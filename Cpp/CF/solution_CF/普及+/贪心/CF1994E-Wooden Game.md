# Wooden Game

## 题目描述

### 题目大意

给定一个有根树森林 $K=\left\{T_1,T_2,\dots,T_k\right\}$。Timofey 可以移除森林中任意树的子树，然后将其加入森林。

求 Timofey 通过任意次操作，所能得到的 
$$
\bigvee_{i=1}^{|K|}\left|T_i\right|
$$
的最大值，其中 $\bigvee$ 表示按位或。

## 样例 #1

### 输入

```
3
1
1


2
4
1 2 2
6
1 1 3 1 3
1
10
1 2 2 1 1 5 7 6 4```

### 输出

```
1
7
10```

# 题解

## 作者：jhdrgfj (赞：5)

唐题。放在 C 就是个 *1300。


考虑对于一棵树每次删去一个叶子节点，这样我们就能取到任意一个小于等于其节点个数的数。

又因为在能对答案产生贡献的情况下，在高位上或一定比在低位上或更优，所以直接枚举每棵树最终选择的数，贪心去 $\max$ 即可。 

代码压一下行还不到 300B。唐。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	int t;
	cin>>t;
	while (t--){
		int n,ans=0;
		cin>>n;
		for (int i=1;i<=n;i++){
			int sz,c=ans;
			cin>>sz;
			for (int j=1;j<=sz;j++){
				ans=max(c|j,ans);
			}
			for (int j=1;j<sz;j++){
				cin>>c;
			}
		}
		cout<<ans<<endl;
	}
}


```

---

## 作者：Bad_Luck_No_Fun (赞：3)

### 题目描述

一个森林里有 $n$ 棵树，每一棵的大小为 $siz_i$ ，给定了每棵树的形态，每次砍掉一棵子树，最终砍掉整个森林，求每次砍掉的大小做或运算后的值最大为多少。

### 思路

~~和 D 一样是个诈骗题。。。~~

首先，对于每棵树，它产生的最大贡献为 $siz_i$。

下面证明一下，设 $x=\sum_{i=1}^k x_i$。

首先最高位肯定会被保留在 $x_{1,2,3,...,k}$ 中的一个，否则不优，不妨钦定最高位为第 $w$ 位，且 $x_1$ 继承了最高位。

所以 $x-2^w=(x_1-2^w)+\sum_{i=2}^k x_i$，此时结果 $ans=2^w+(x_1-2^w)|x_2|x_3|...|x_k$

同理  $x-2^w$ 也会有最高位，不保留同样不优，就这样一位一位拆除。最终发现 $ans_{max}=x$。

接着再考虑多个树的情况。

这个情况可以贪心，对于每一位，如果答案的这一位已经是 $1$，就把这一位以后的所有位都赋值为 $1$ 。很容易证明这个贪心的正确性。

### $Code$

```cpp
# include<bits/stdc++.h>
using namespace std;
const int N = 2e6 + 6;
# define int long long
int T, n;
int a[N];
void solve() 
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		int trash;
		for(int j = 1; j < a[i]; j++)
		{
			cin >> trash;
		}
	}
	sort(a + 1, a + n + 1, greater <int> ());
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 23; j >= 0; j--)
		{
			int x = (ans >> j) & 1;
			int y = (a[i] >> j) & 1;
			if(!y)
			{
				continue;
			}
			if(!x)
			{
				ans |= (1ll << j);
			}
			else
			{
				ans |= ((1ll << j) - 1);
				break;
			}
		}
	}
	cout << ans << endl;
}
signed main(){
	ios::sync_with_stdio(0);
	cin >> T;
	while(T--)
	{
		solve();
	}
	return 0;
}


```

---

## 作者：liugh_ (赞：0)

## [Wooden Game](https://codeforces.com/contest/1994/problem/E)

若只有 $1$ 棵树，由 $s_1\mid s_2\mid\ldots\mid s_k\le s_1+s_2+\ldots+s_k$ 可知不分割最优。有多棵树时，贪心地令最大的树不分割，以大小**降序**考虑剩下的树，记 $x$ 为当前考虑到树的大小。

贪心地从高位到低位考虑，若当前答案 $cur$ 的第 $k$ 位是 $0$ 且 $x$ 的第 $k$ 位是 $1$，显然 $cur$ 直接或上  $2^k$ 最优，对 $x$ 的低位没有影响；若 $cur$ 的第 $k$ 位和 $x$ 的第 $k$ 位都是 $1$，再或上 $2^k$ 显然不优，但我们可以或上 $2^k-1$，这样第 $0\sim k-1$ 位都变成 $1$，$x$ 的低位必然不会再产生贡献。

于是构造这样一个 $x'$：设 $x\text{ and }cur$ 的最高位为 $2^k$，$x'$ 高于第 $k$ 位的部分与 $x$ 相同，$x'$ 的第 $k$ 位为 $0$，第 $0\sim k-1$ 位为 $1$。$x'$ 一定能由 $x$ 达到，因为每次删去一个叶子能构造出 $[0,x]$ 中的所有数，也即树的形态是无用信息。时间复杂度 $O(n\log n)$。

```cpp
sort(&a[1],&a[n]+1,greater<>());int ans=0;
for(int i=1;i<=n;i++)for(int k=20;k>=0;k--)if(a[i]>>k&1){
	if(ans>>k&1)ans|=(1<<k)-1;
	else ans|=1<<k;
}
```

---

## 作者：lhc0707 (赞：0)

挺诈骗的题，想通性质就很好做了。

性质 1：显然 $k=1$ 时的答案就是这棵树的节点数。

性质 2：我们可以通过砍叶子结点的方式得到 $1$ 到 $siz$ 的所有数值。

想通以上两点，问题就变成了如何选数，也就是最终结果需要这个 $siz$ 的哪几位做出贡献。一位一位考虑就可以了。设当前考虑到 $h$ 位，如果 $ans$ 的 $j$ 位为 $0$，则让 $ans$ 或上 $2^j$，否则让 $ans$ 贪心地或上 $2^{j-1}$。复杂度 $O(N\log N)$，可过。[code](https://codeforces.com/contest/1994/submission/273455065)。

---

## 作者：2huk (赞：0)

> - 给定由 $n$ 棵树组成的森林，第 $i$ 棵树的大小为 $a
>   _i$。你可以进行若干次操作，每次操作你可以选择某棵树的某个子树并将其删除。求最终被删除的子树的大小的按位或和的最大值。

当 $n = 1$ 时，即只有一颗树时，答案为这颗树的大小 $a_1$。考虑证明。

> 令每次删除的子树大小为 $s_1, s_2, \dots, s_m$，显然 $\sum s_i = n$。二进制逐位考虑。令 $t_i$ 表示有多少 $s_j$ 的第 $i$ 位为 $1$。那么它们的或和为 $\sum 2^i[t_i > 0]$，它们的和为 $\sum 2^it_i$。显然 $[t_i > 0] \le t_i$，所以它们的或和 $\le$ 它们的和，即这种方案得到的答案 $\le n$，即这种方案得到的答案 $\le$ 一次全部删除得到的答案。所以一次删除完是最佳方案。

考虑普遍情况。

若我们删除这棵树的一个叶节点，那么这颗树的大小会减小 $1$。那么我们可以通过多次删除叶节点的操作，使这棵树的大小成为 $1 \sim m$ 中的任意值。

那么答案为所有这些 $1 \sim m_i$ 的数的最大或和。贪心从高到低枚举每一位，并计算答案中的这一位是否有可能是 $1$：

- 若第 $i$ 位为 $1$ 的 $m_j$ 数量 $\ge 2$，那么我们可以让一个 $m_j$ 不变，让另一个一直减 $1$ 直到其第 $i$ 位变为 $0$。那么此时的或和中，第 $i$ 位及以下都是 $1$ 了。结束即可。
- 若第 $i$ 位为 $1$ 的 $m_j$ 数量 $= 1$，那么这个数不变。答案的第 $i$ 位是 $1$。
- 若第 $i$ 为为 $1$ 的 $m_j$ 数量 $= 0$，那么选不了。答案的第 $i$ 位是 $0$。

复杂度 $\mathcal O(n \log V)$，其中 $V$ 是值域。

```cpp
int solve() {
	cin >> n;
	
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++ i ) {
		cin >> a[i];
		for (int j = 0; j + 1 < a[i]; ++ j ) {
			int x; cin >> x;
		}
		for (int j = 0; j < 30; ++ j )
			cnt[j] += (a[i] >> j & 1);
	}
	
	int res = 0;
	for (int j = 29; ~j; -- j )
		if (cnt[j] >= 2) {
			res |= (1 << j + 1) - 1;
			break;
		}
		else if (cnt[j] == 1) res |= (1 << j);
	
	return res;
}
```

---

## 作者：c1120241919 (赞：0)

### CF1994E

十分有趣的题目。

可以发现对于一棵树，不停的删叶子可以让你做到 $[1,n]$  全部取到。

因为位运算，就可以考虑贪心，对于大小从大到小取，先考虑贪心取 $n$，再找到第一个与之前选取的答案同时取 $1$ 的地方，把后面都都改成 $0$ 即可。

例如：$10000\to01111$。

容易证明贪心是对的。

[提交记录](https://codeforces.com/contest/1994/submission/271920691)

---

## 作者：Disjoint_cat (赞：0)

# CF1994E

唉，没赶上上分场。（VP rk ~80）

## 题意

给出 $k$ 棵树，每次可以选一个点将其子树删除，求所有操作中子树大小按位或的最大值。

下设 $a_i$ 为第 $i$ 棵树大小，$n=\sum a_i$。则 $k,n\le10^6$。

## 题解

诈骗题。

首先考虑一棵树对答案的贡献。根据 $x\operatorname{or}y\le x+y$，一个数的贡献一定 $\le a_i$。啥你说咋构造？疯狂砍叶节点砍到那么多然后全删了就得了。

所以你会发现树的形态屁用没有。只用对于每个 $i$ 选一个 $\le a_i$ 的正整数，使它们的按位或最大就行了。

然后这是一个典题。。。你每次考虑最大数的最高位，如果这一位已经有贡献那么要这一位是不优的，所以可以直接把后面的位全部贡献上。否则你把最高位贡献上是最优的。随便维护下就行了。

时间复杂度 $\Theta(k\log k+n)$。其中 $n$ 来自输入。（

[VP 时 submission](https://codeforces.com/contest/1994/submission/271866238)

## Bonus

证明算法时间复杂度是 $\Theta(n)$ 的。（也就是证明 $\Theta(k\log k)\le\Theta(n)$。）

---

## 作者：Eznibuil (赞：0)

首先，一棵树的贡献与形态无关。证明：假设 $s_1+\cdots+s_m=n$，那么必然有 $s_1\operatorname{or}\cdots\operatorname{or}s_m\le n$。所以在单独考虑一棵时，必然直接删掉整棵最优。

那么如果有多棵树构成了森林呢？考虑贪心，维护一个答案 $x$，每次对于一棵树大小为 $n$，找到最大的整数 $y$ 使 $y\le n$ 且 $x\operatorname{and}y=0$，然后令 $x\gets x\operatorname{or}y$ 即可。最优性证明：对于两棵树大小为 $n_1$ 和 $n_2$，容易发现 $n_1\operatorname{and}n_2$ 最高的为 $1$ 的二进制位之下，答案的二进制位都是 $1$；假设答案的第 $x$ 个二进制位为 $0$，那么 $n_1\operatorname{or}\cdots\operatorname{or}n_k$ 和 $n_1+\cdots+n_k$ 在比 $x$ 高的位都是相等的，那么如果要答案的 $x$ 位变成 $1$，比 $x$ 高的某个为 $1$ 的位势必要变为 $0$，反而变劣。

现在的问题是如何找到 $y$，当然是暴力枚举，显然是线性的。时间复杂度 $O(\sum n)$。
```c
main(k,n,i,s){for(scanf("%*d");~scanf("%d",&k);printf("%d\n",s))for(s=0;k--;s|=n)for(scanf("%d",&n),i=n;--i;s&n?n=i:0)scanf("%*d");}
```

---

## 作者：Redshift_Shine (赞：0)

## 5. Wooden Game / 绿

有个由 $k$ 棵树组成的森林，每次可以移除任意一个节点为根的子树，求所有移除的子树大小的最大或值。

可以移除叶子。也就是说，一个大小为 $x$ 的子树对答案的贡献可以是 $[1,x]$ 中的任意一个整数。

它给的树结构压根就没有用。

时间复杂度 $O(n)$。

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1e6 + 10;
int n, a[N], t, res;
void run()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
        for (int j = 1; j < a[i]; j++)
            scanf("%*d");
    }
    sort(a + 1, a + n + 1);
    t = 1;
    for (; t < a[n]; t = t * 2 + 1)
        ;
    res = 0;
    for (int i = n; i; i--)
    {
        while ((t > a[i]) or (t & res))
            t--;
        res |= t;
    }
    printf("%d\n", res);
}
int main()
{
    int T = 1;
    scanf("%d", &T);
    while (T--)
        run();
}
```

---


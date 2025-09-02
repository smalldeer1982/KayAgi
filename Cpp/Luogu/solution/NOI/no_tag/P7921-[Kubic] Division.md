# [Kubic] Division

## 题目背景

建议先看 F 题题目背景。

## 题目描述

你有一个**可重集**，初始其中只有一个正整数 $n$。

你每次可以选择当前在集合中的一个正整数 $x$ 并删去，再指定一个正整数 $y$（不要求在集合中）满足 $x>y$，并往集合中加入 $y$ 和 $x-y$。

你需要保证在**任意时刻**，集合中的最大值**严格小于**集合中的最小值的 $2$ 倍。

求出你**最多**能进行多少次操作，并**输出构造方案**。

**输入数据保证最多能进行的操作次数不超过 $10^6$**。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^9$。

||分值|$n$|
|:-:|:-:|:-:|
|$\operatorname{Subtask}1$|$10$|$\le 10$|
|$\operatorname{Subtask}2$|$20$|$\le 100$|
|$\operatorname{Subtask}3$|$30$|$\le 10^6$|
|$\operatorname{Subtask}4$|$40$|无特殊限制|

### 评分方法

以下情况将会使你在该测试点获得 $0$ 分：

- 输出格式不满足要求。

- 输出多余信息（包括空格和换行符）

- 构造的方案操作次数与标准答案不同。

- 构造的方案不符合题目要求。

- 时间超限。

如果没有上述情况，你在该测试点获得满分。

**保证 SPJ 占用不超过 $100\operatorname{ms},10\operatorname{MB}$**

### 样例解释 1

一种操作过程如下：

`8`

`3 5`

`2 3 3`

可以证明没有更优的方案。

### 样例解释 2

一种操作过程如下：

`30`

`12 18`

`8 10 12`

`6 6 8 10`

`5 5 6 6 8`

`4 4 5 5 6 6`

可以证明没有更优的方案。

## 样例 #1

### 输入

```
8```

### 输出

```
2
8 3
5 2```

## 样例 #2

### 输入

```
30```

### 输出

```
5
30 12
18 8
12 6
10 5
8 4```

# 题解

## 作者：Mophie (赞：11)

来水一发题解。个人感觉黑题有点虚高。

我们先猜测一下最终状态是什么。

设最终状态是 $a_1, a_2, ..., a_n$，且 $a_1 \le a_2 \le... \le a_n$。

那么很显然，这个状态成立当且仅当：

- 每次能够挑选最小的两个数合并起来，然后每个时刻最小值的两倍均严格大于最大值。

然后呢，就可以得到：

- $a_1+a_2 < 2 \times a_3, a_3 + a_4 < 2 \times a_5$…… 这些限制条件。

所以说必然不能有 $a_1 = a_2 = a_3$ 或者 $a_3 = a_4 = a_5$ 之类的。

相当于说只能满足每个数出现次数 $\le 2$ 或者 $1 + 3$ 的形式。

我们先只考虑全部 $\le 2$ 的情况。

那么假设 $a_n = k$，那么显然 $a_1 > \frac{k}{2}$ 的。

考虑填满后再删去一些数，那么先拿一个 $k = 6$ 手玩一下。发现可以使减少和等于 $0,4,5,6,8,9,10,11.....$

最重要的特点是中间隔的是 $1,2,3,7...$

首先如果上面这样构造能构造的出来的话，必然是最优的且合法的（这个很好证吧）。

然后考虑把 $1+3$ 的情况给塞回去，发现可以通过减少一个最小数，多一个另外的数来达到这个目的。

那么此时就可以除了 $7$ 以外全部处理完了。

最后想想这个 $7$，手推一下可以想到放到下一次弄必然不劣。

那么就把这个 $7$ 放到下面特判即可。

具体细节见代码。

### Code：

```cpp
/*
   长弓背负，仙女月鹫，
   梦中徐来，长夜悠悠。
   今宵共君，夜赏囃子，
   盼君速归，长夜悠悠。
   睡意袭我，眼阖梦徭，
   睡意袭我，意归襁褓。
   手扶卓揭，仙女水狃，
   盼君速归，长夜悠悠。
   今宵共君，戏于西楼，
   盼君速归，长夜悠悠。
   睡意袭我，涟锜池留，
   睡意袭我，意归海角。
					                  ——《ever17》
*/
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int sum = 0, nega = 1;
	char ch = getchar();
	while (ch > '9'||ch < '0')
	{
	    if (ch == '-') nega = -1;
		ch = getchar();
	}
	while (ch <= '9'&&ch >= '0') sum = sum * 10 + ch - '0', ch = getchar ();
	return sum * nega;
}
const int N = 1e5 + 9;
int n, pep, res;
int cnt[N]; 
queue<int> q;
int ansx[N], ansy[N];
inline int val(int x) {return x * (x + 1) / 2;}
signed main()
{
	n = read();
	for (int i = 1; i <= n; i++)
	{
		int p = i / 2;
		int v = (val(i) - val(p)) * 2;
		p++;
		if(v < n && n - v <= i - p)
		{
			for (int j = p; j <= i; j++) cnt[j] = 2;
			cnt[p]--, cnt[p + n - v]++;
			res = 0;
			for (int j = p; j <= i; j++)
				for (int k = 1; k <= cnt[j]; k++) 
				{
					q.push(j); res += j;
				}
			while(!q.empty())
			{
				int x = q.front(); q.pop(); 
				if(q.empty()) break;
				int y = q.front(); q.pop();
				ansx[++pep] = x + y, ansy[pep] = x;
				q.push(x + y);
			}
			cout << pep << endl;
			for (int j = pep; j >= 1; j--) printf("%lld %lld\n", ansx[j], ansy[j]);
			return 0;
		} 
		if(v >= n && (v - n >= p || v - n == 0))
		{
		//	cout << v << " " << i << endl;
			if(v - n == i + 1 && i % 2 == 0) continue;
			for (int j = p; j <= i; j++) cnt[j] = 2;
			if(v - n == 0) ;
			else if(v - n <= i) cnt[v - n]--;
			else if(v - n <= i + p) cnt[p]--, cnt[v - n - p]--;
			else if(v - n <= i * 2) cnt[i]--, cnt[v - n - i]--;
			else if(v - n <= i * 2 + p) cnt[i]--, cnt[p]--, cnt[v - n - i - p]--;
			else cnt[i]--, cnt[i - 1]--, cnt[p] = 0;
			res = 0;
			for (int j = p; j <= i; j++)
				for (int k = 1; k <= cnt[j]; k++) 
				{
					q.push(j); res += j;
				}
			if(res != n) continue;
			while(!q.empty())
			{
				int x = q.front(); q.pop(); 
				if(q.empty()) break;
				int y = q.front(); q.pop();
				ansx[++pep] = x + y, ansy[pep] = x;
				q.push(x + y);
			}
			cout << pep << endl;
			for (int j = pep; j >= 1; j--) printf("%lld %lld\n", ansx[j], ansy[j]);
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：2022dyx (赞：2)

感觉顶多是紫？

正向地想 DP 显然没啥前途，优化到 $O(n)$ 都很困难，所以我们考虑将整个过程倒着考虑，由最终的一些数合并成 $n$，答案就是最终数的个数减一。首先有一个比较显然的性质，每次合并一定只能操作最小的两个数，否则合并的结果变得更加不均匀，使答案变劣。

下面要发掘一些比较显然的性质。首先，最终的最大数一定严格小于最小数的二倍（废话），在此基础上，什么情况会导致合并的过程中违背题意呢？由于我们每次合并的都是最小数，若合并后剩下的最小数不等于原最小数，那合并出的数一定严格小于剩下最小数的二倍，所以要违背题意只能是在最小数剩余数量至少三个的时候合并。换句话说，若数 $i$ 的排名为奇数，则其数量不超过 $2$，若数 $i$ 的排名为偶数，则其数量不超过 $3$。（数 $i$ 的排名定义为小于 $i$ 的数的个数 $+1$）。

在不考虑 $3$ 个数的情况下，我们最终的序列会形如 $i,i,i+1,i+1,...,2i-1,2i-1$，由于这里任何数的排名都为奇数，所以若想让某个数出现 $3$ 次，必须在它前面取出一个数，因此数出现 $3$ 次不能改变答案，只能用来调整总和至 $n$。

我们枚举最终序列的最小值，则在要求每个数只能出现 $2$ 次的情况下其能达到的最大值可以计算出来，有最大值 $m=3i^2-i$，我们将其与 $n$ 比较，分为下面四种情况。 
- $m+i\le n$：在全都出现 $2$ 次的情况下最多只能让 $i$ 变为 $2i-1$ 从而增加 $i-1$，因此若增加 $i-1$ 都不行那就是不行了。
- $m\le n<m+i$：通过将 $i$ 变为更大的数可以任意增加 $0$ 到 $i-1$，所以这部分直接变就行。
- $m-i<n<m$：$n$ 比 $m$ 小了，因此我们不得不删除一个数，这个删除的数属于 $[i,2i-1]$，而我们在这部分需要减少的数属于 $[1,i-1]$，二者没有交集，因此这部分做不到。
- $m-2i<n\le m-i$：同上，删除的数位于 $[i,2i-1]$，一定能做到，直接删就行。
- $n\le m-2i$：我们不得不删除至少 $2$ 个数了。假设我们一直删直到 $<n$ 为止得到的数为 $k$，那么 $n-k$ 一定小于 $2i-1$，否则我们就不必删最后一个了。而通过两次将 $i$ 移为大数的操作，我们能够增加 $0$ 到 $2(i-1)=2i-2$ 中的任何数，因此这样移动就可以。

由于将 $i$ 变大会使得能选的数减少，一定不优，所以只要找到第一个可行的 $i$ 就停止，方案输出直接扔到堆里模拟即可。

由于判断每一个 $i$ 是否可行的代价是 $O(1)$，$i$ 的数量在 $O(\sqrt n)$，所以判断部分的时间复杂度为 $O(\sqrt n)$，而模拟部分由于合并操作的数量为 $\frac{n}{i}=O(\sqrt n)$，单次操作复杂度为堆操作的 $O(\log n)$，因此总复杂度为 $O\sqrt n\log n)$，可以通过本题。

事实上，由于题目的限制，我们可以抛弃堆而直接将操作生成的数往后放，此时复杂度降为 $O(\sqrt n)$。

---

## 作者：Cindy_Li (赞：0)

初始有一张长为 $n$ 的纸条，每次操作选择一张纸条，撕成长度为正整数的两部分。要求任意时刻，最长纸条的长度严格小于最短纸条长度的两倍。

**key：正难则反。**

考虑最终结束状态是什么样子，倒着合并纸条能否满足限制。

1. 每次一定合并最短和次短（如果不合并最短，一定不合法，否则也肯定不优）。
2. 任意时刻，最短、次短、第三短不能相同 $\Rightarrow$ 一个数可以出现三次，当且仅当它前面有奇数个数。

不妨暂且认为每个数出现两次，则最终序列形如：`i,i,i+1,i+1,...,2i-1,2i-1`。

发现一个数要出现三次，则必须在它前面删掉一个数，故这种操作不改变序列长度，只能用来调整总和。

有几种调整方式：
1. $ans$ 不变，$sum\to sum+[0,i-1]$：删一个 $i$，后面加一个数
2. $ans\to ans-1$，$sum\to sum-[i,2i-1]$：随便删一个数。
3. $ans\to ans-2$，$sum\to sum-[2i,4i-2]$：随便删两个数。
4. $ans\to ans-3$，$sum\to sum-[4i-1,5i-2]$：删掉一个 $i$，一个 $2i-1$ 和随便一个数。
5. 还有一种神秘调整方式：删掉两个 $2i-1$，然后重复上面的操作，这样可以补 $sum'-[1,(i-1)-1]$ 这个空缺。
6. 发现一个 hack `9 -> 4 5` ，需要在 `3 3 4 4 5 5` 中删掉 $4$ 个数，其他情况大抵是都可以解决的。

从小到大枚举 $i$，找到一个合法的就一定是答案。

```c++
const int N=1e6+5;
int cnt[N];
multiset<int> s;
int res[2][N];
inline void print(int l,int r){
    rep(i,l,r) rep(j,1,cnt[i]) s.insert(i);
    int ans=0;
    while(s.size()>1){
        int u=*s.begin();s.erase(s.begin());
        int v=*s.begin();s.erase(s.begin());
        res[0][++ans]=u+v,res[1][ans]=u;
        s.insert(u+v);
    }
    printf("%d\n",ans);
    reverse(res[0]+1,res[0]+ans+1);
    reverse(res[1]+1,res[1]+ans+1);
    rep(i,1,ans){
        printf("%d %d\n",res[0][i],res[1][i]);
    }
}
inline void solve(){
    rep(r,1,n){
        int l=r/2+1;
        int sum=(l+r)*(r-l+1);
        if(sum<=n && n-sum<=r-l){
            rep(j,l,r) cnt[j]=2;
            cnt[l]--,cnt[n-sum+l]++;
            print(l,r);
            break;
        }
        if(sum>n && sum-n>=l){
            rep(j,l,r) cnt[j]=2;
            if(sum-n<=r) cnt[sum-n]--;
            else if(sum-n<2*l) continue;
            else if(sum-n<=l+r) cnt[l]--,cnt[sum-n-l]--;
            else if(sum-n<=2*r) cnt[r]--,cnt[sum-n-r]--;
            else if(sum-n<=5*l-2) cnt[l]--,cnt[r]--,cnt[sum-n-l-r]--;
            else cnt[l]-=2,cnt[r]--,cnt[sum-n-2*l-r]--;
            print(l,r);
            break;
        }
    }
}
```

---


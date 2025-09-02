# Another Wine Tasting Event

## 题目描述

After the first successful edition, Gabriella has been asked to organize a second wine tasting event. There will be $ 2n - 1 $ bottles of wine arranged in a row, each of which is either red wine or white wine.

This time, Gabriella has already chosen the type and order of all the bottles. The types of the wines are represented by a string $ s $ of length $ 2n - 1 $ . For each $ 1 \le i \le 2n - 1 $ , it holds that $ s_i = \texttt{R} $ if the $ i $ -th bottle is red wine, and $ s_i = \texttt{W} $ if the $ i $ -th bottle is white wine.

Exactly $ n $ critics have been invited to attend. The critics are numbered from $ 1 $ to $ n $ . Just like last year, each critic $ j $ wants to taste an interval of wines, that is, the bottles at positions $ a_j, \, a_j + 1, \, \dots, \, b_j $ for some $ 1 \le a_j \le b_j \le 2n - 1 $ . Moreover, they have the following additional requirements:

- each of them wants to taste at least $ n $ wines, that is, it must hold that $ b_j - a_j + 1 \ge n $ ;
- no two critics must taste exactly the same wines, that is, if $ j \ne k $ it must hold that $ a_j \ne a_k $ or $ b_j \ne b_k $ .

Gabriella knows that, since the event is held in a coastal region of Italy, critics are especially interested in the white wines, and don't care much about the red ones. (Indeed, white wine is perfect to accompany seafood.) Thus, to ensure fairness, she would like that all critics taste the same number of white wines.

Help Gabriella find an integer $ x $ (with $ 0 \le x \le 2n - 1 $ ) such that there exists a valid assignment of intervals to critics where each critic tastes exactly $ x $ white wines. It can be proved that at least one such $ x $ always exists.

## 说明/提示

In the first sample, there are $ 5 $ critics and $ 2 \cdot 5 - 1 = 9 $ bottles of wine. A possible set of intervals that makes each critic taste $ 2 $ white wines is the following: $ [2, 6], $ $ [1, 6], $ $ [4, 8], $ $ [1, 5], $ $ [3, 7] $ . Note that all intervals contain at least $ 5 $ bottles.

In the second sample, there is $ 1 $ critic and $ 2 \cdot 1 - 1 = 1 $ bottle of wine. The only possible interval is $ [1, 1] $ , which gives $ x = 0 $ .

## 样例 #1

### 输入

```
5
RWWRRRWWW```

### 输出

```
2```

## 样例 #2

### 输入

```
1
R```

### 输出

```
0```

# 题解

## 作者：Ruizhangj (赞：3)

结论就是 $ans=\max_{i=1}^{n}w(i,i+n-1)$ ，其中 $w(l,r)$ 表示 $[l,r]$ 中 W 的个数。

令 $w(k,k+n-1)=ans$ 。
对于所有 $l<k$ ，一定可以找到一个右端点使得 $w(l,R_l)=ans$ ，并且 $R_l\leq k+n-1$ ；
对于所有 $r>k+n-1$ ，一定能够找到一个左端点使得 $(L_r,r)=ans$ ，并且 $L_r\geq l$ 。
所以至少能够找到 $n$ 个 $w(l,r)=ans$ 的区间。

---

## 作者：skyskyCCC (赞：1)

## 前言。
构造题，但是我喜提最劣解。
## 分析。
由“请求出满足条件的 $x$ 若有多解，则输出任意一个”这句话中考虑，我们选择构造。

设 $g\left(l,r\right)$ 是 $l$ 到 $r$ 这一段区间的白酒数量。假设当 $l$ 取 $k$ 的时候，此时 $g\left(k,k+n-1\right)$ 最大为 $x$。

那从 $1$ 到 $k-1$ 的点开始喝的话，他们也可以喝到 $x$ 瓶白酒。可以从第 $i$ 个点喝到第 $k+n-1$ 个点，反正肯定有 $x$ 瓶白酒能喝。同时，他们品酒的数量一定 $\geq\left(k+n-1\right)-k+1=n$ 否则 $k$ 就不是最优的点了，所以这样可以满足 $1-k-1=k$ 的人全都恰好喝到 $x$ 瓶酒。且喝的酒的数量 $\geq n$ 那么对于 $k+n$ 到 $n$ 也一样。

我们假设 $l\left[i\right]$ 是以 $i$ 为起点，喝到 $x$ 瓶酒的**最小**序列长度，同时 $r\left[i\right]$ 是以 $i$ 为终点，喝到 $x$ 瓶酒的**最小**序列长度，那么就有 $l\left[1\right],l\left[2\right], l\left[3\right],\ldots \left[k,k+n-1\right],r\left[k+n\right],r\left[k+n+1\right]\ldots n$ 的形式。

其中，除了 $[k,k+n-1]$ 之外的每一个点都可以对应一个序列，并且由于每个的起点和终点不一样，所以没有任意两个品酒师喝的一样，所以这样的话我们能选出的序列总个数就是 $2\times n-1-(k+n-1-k+1)+1=n$ 正好。所以构造成功。

答案就是 $ans=\max \{g\left(l,l+n-1\right)\} \left(l\in\left[1,n\right]\right)$ 的结果。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n;
string s;
int sum,ans;
int main(){
	cin>>n>>s;
	s=' '+s;
	for(int i=1;i<=2*n-1;i++){
		if(s[i]=='W'){
			sum++;
		}
		//cout<<"ans:"<<ans<<"\n";
		//cout<<"sum:"<<sum<<"\n";
		ans=max(ans,sum);
		if(i>=n){
		    sum-=(s[i-n+1]=='W');
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```
## 后记。
这道题还蛮有意思的，注意细节即可。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Leasier (赞：0)

这种东西肯定要考虑构造一组特殊解。

考虑尝试把 $r - l + 1 \geq n$ 变成钦定其中某个 $r - l + 1 = n$，则我们可以得出对应的 $x$。

我们期待的 $[l, r]$ 肯定也不是随便某一个就行，比如说我们钦定其为 $x$ 最小者。

但我们很快就会发现这样有问题。比如说 $x = 0$ 时，我们可以构造 $n$ 个 `R` 与 $n - 1$ 个 `W` 的拼接，然后就寄了……

转而考虑钦定其为 $x$ 最大者，然后我们来考虑如何构造：

- $\forall 1 \leq l' < l$，指派一个 $r' \leq r$ 即可。
- $\forall r < r' \leq 2n - 1$，指派一个 $l' \geq l$ 即可。

显然此时 $[l', r']$ 均符合长度限制。

前缀和求出 $x$ 即可。时间复杂度为 $O(n)$。

代码：
```cpp
#include <stdio.h>

int sum[2000007];
char s[2000007];

inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	int n, m, ans = 0;
	scanf("%d", &n);
	scanf("%s", &s[1]);
	m = n * 2 - 1;
	for (int i = 1; i <= m; i++){
		sum[i] = sum[i - 1] + (s[i] == 'W' ? 1 : 0);
	}
	for (int i = 1; i <= n; i++){
		ans = max(ans, sum[i + n - 1] - sum[i - 1]);
	}
	printf("%d", ans);
	return 0;
}
```

---


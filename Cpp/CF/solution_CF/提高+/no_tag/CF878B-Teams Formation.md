# Teams Formation

## 题目描述

This time the Berland Team Olympiad in Informatics is held in a remote city that can only be reached by one small bus. Bus has $ n $ passenger seats, seat $ i $ can be occupied only by a participant from the city $ a_{i} $ .

Today the bus has completed $ m $ trips, each time bringing $ n $ participants. The participants were then aligned in one line in the order they arrived, with people from the same bus standing in the order of their seats (i. e. if we write down the cities where the participants came from, we get the sequence $ a_{1},a_{2},...,a_{n} $ repeated $ m $ times).

After that some teams were formed, each consisting of $ k $ participants form the same city standing next to each other in the line. Once formed, teams left the line. The teams were formed until there were no $ k $ neighboring participants from the same city.

Help the organizers determine how many participants have left in the line after that process ended. We can prove that answer doesn't depend on the order in which teams were selected.

## 说明/提示

In the second example, the line consists of ten participants from the same city. Nine of them will form a team. At the end, only one participant will stay in the line.

## 样例 #1

### 输入

```
4 2 5
1 2 3 1
```

### 输出

```
12
```

## 样例 #2

### 输入

```
1 9 10
1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 2 10
1 2 1
```

### 输出

```
0
```

# 题解

## 作者：RBI_GL (赞：2)

### 题意：

给出一个长为 $n$ 的序列，将其重复 $m$ 次，连续相等的 $k$ 的个元素可以被消除，问最后剩余多少个元素。

### 思路：

首先我们先考虑单个串，如果单个串中有恰好 $k$ 的倍数个连续相同字符，那么我们应该先将其消除，那么第一步我们遍历数组，这里我们需要用到一个 $pair$ 数组,数组中前面存数值，后面存个数。

这样如果我们遍历到的数字和前一个相同也就是找到了连续相同的，我们只需要给顶部的元素的 ```st[top].second+1```，如果发现和前一个元素不同说明已经不连续相同了，这时候我们再把这个数放进去，这样的好处就是我们 $pair$ 数组中用一个数字和其个数代表了连续相等的串，这样我们只需要判断 ```st[i].second%k``` 是否等于 $0$ 就可以。

这样对于初始串的处理就结束了，我们就得到的消去连续的后的单个串的个数我们记为 $rec$。

然后我们观察，发现对于每两个串相连，其实就是一个串的首尾相连把连续相同的k个消去，这样我们还是对一个串处理，我们继续处理 $pair$ 数组。

用两个下标 $l$，$r$ 从两边向中间缩，如果两头数字相同并且，他们的个数之和恰好是 $k$ 的倍数，那么这一堆全都可以消去，这样我们让 ```l++，r++```，记录下消除的个数，一直到两头数字不能完全消除为止。

用 $while$ 循环实现，每个串消除的首尾总个数记为 $rec2$，同时我们发现第一个串的首和最后一个串尾可能不会接触，那么我们可以确定一定会减去 $m-1$ 个 $rec2$。

接下来分两种情况讨论即可：

- 只剩下了一种数字

- 剩下多种数字


注意要开 ```long long```。


### Code:


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[100005];
pair<ll,ll> st[100005];
ll top,n,m,k,l,r,rec,rec2;
ll ans;
int main() {
	scanf("%lld%lld%lld",&n,&k,&m);
	for(ll i=1; i<=n; i++) scanf("%lld",&a[i]);
	for(ll i=1; i<=n; i++) {
		if(!top || st[top].first!=a[i]) st[++top]=make_pair(a[i],1);
		else st[top].second=(st[top].second + 1)%k;
		if(st[top].second==0) top--;
	}
	for(ll i=1; i<=top; i++) rec += st[i].second;
	l=1,r=top;
	while(l<r && st[l].first==st[r].first && (st[l].second+st[r].second)%k==0) {
		rec2 += st[l].second+st[r].second;
		l++;
		r--;
	}
	if(l==r) {
		if(st[l].second*m%k==0) ans -= rec2;
		ans += m*rec-rec2*(m-1)-(st[l].second*m/k*k);
	} else {
		if(st[l].first==st[r].first) rec2 += (st[l].second+st[r].second)/k*k;
		ans=m*rec-rec2*(m - 1);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：bai_tang (赞：2)

只要有信念，就一定能成功！
- 这里有一个不需要脑子的乱搞，或许涉及一些比较有趣的性质。

### [题意](https://www.luogu.com.cn/problem/CF878B)
一个长度为 $n$ 的数列重复 $m$ 次，然后一直把连续 $k$ 个出现的数删掉，问最后剩下多少个数，$n\le 10^5,m,k\le 10^9$。

### 乱搞
容易想到 $O(nm)$ 的做法，然后改进一些就有如下乱搞：

- 如果 $k\ge 2n$，特判所有数是否相同，得出答案。
接下来设定两个参数 $G=90,S=7$。
- 如果 $m\le G$，暴力 $O(nm)$ 算出答案。
- 如果 $m>G$，暴力 $O(nG)$ 算出 $0,1,2,\cdots G$ 个段拼接而成的长度 $f(0),f(1),\cdots ,f(G)$，计算其差分 $g(i)=f(i)-f(i-1)$，寻找到$g(x)$ 在 $S$ 以后出现的最短循环节，并且利用这个循环节预测 $f(m)$，复杂度 $O(G^2+nG)$，[代码](https://www.luogu.com.cn/paste/x6pi62uw)。

实测令 $G=30,S=2$ 仍然可以通过 CodeForces 的全部数据。

---

## 作者：wangyibo201026 (赞：0)

一道很不错的 case 题。

## solution

个人写法可能与题解有所差异。

首先注意到这样一件事情：我肯定是先把恰好能够删完的段全部删掉（可能存在连锁反应），最后存在的元素一定都是会留下来的，绝对不可能再次产生连锁反应。

不妨将 $m$ 个重复序列先处理前两个的消除关系，由于序列都是相同的，我们可以寻找一下规律。

发现如果 $m = 2$ 时是好做的，我们先将原序列最简化，即删去部分 $\ge k$ 的段的元素，这个过程我们可以用一个栈进行存储。然后对于两个序列的合并，我们可以往第一个序列里不断插入第二个序列的元素段，进行同样的步骤进行合并。

现在考虑如何合并，我们进行分类讨论：

情况 $1$：两个序列合并直接被消没了，此时如果 $m$ 为偶数，答案为 $0$，否则答案为 $n$。

情况 $2$：两个序列合并只有一个元素，此时直接暴力计算即可。

情况 $3$：两个序列合并有两个及以上元素，这一部分还是比较棘手的。考虑到一个性质，开头两个序列合并消掉的段数绝对不会超过原本序列的段数，也就是说我第一次消掉了 $cnt$ 个元素，那么第二次也只会消掉 $cnt$ 个元素，所以合并 $m - 1$ 次之后会消掉 $cnt \times (m - 1)$ 个数，简单计算就做完了。

然后对于每个 case，需要注意一下即使边界段没有消完也可以消掉一部分，别漏算了。

维护这个东西用栈反而不太好处理，在处理自身消段的时候，我们使用 deque 进行维护。

## code

就不放代码了。

---


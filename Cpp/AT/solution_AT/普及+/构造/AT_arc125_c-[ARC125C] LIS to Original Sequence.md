# [ARC125C] LIS to Original Sequence

## 题目描述

# [ARC125C] LIS to Original Sequence


[problemUrl]: https://atcoder.jp/contests/arc125/tasks/arc125_c

给定一个长度为 $k$ 的序列 $A_1,A_2,\cdots,A_n$，试求出长度为 $n$ 的序列 $P$，使得 $P$ 的最长上升子序列为 $A_1,A_2,\cdots,A_n$，且 $P$ 的字典序最小。


## 样例 #1

### 样例输入 #1

```
3 2
2 3
```

### 样例输出 #1

```
2 1 3
```

## 样例 #2

### 样例输入 #2

```
5 1
4
```

### 样例输出 #2

```
5 4 3 2 1
```

## 说明/提示

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_1\ <\ A_2\ <\ \cdots\ <\ A_K\ \leq\ N $
- 输入的所有值均为整数。

### 样例一解释

当 $P=（2，1，3）$ 或 $（2，3，1）$ 时，$P$ 的最长上升子序列与 $A$ 一样。 其中，$（2，1，3）$的字典序最小。

## 样例 #1

### 输入

```
3 2
2 3```

### 输出

```
2 1 3```

## 样例 #2

### 输入

```
5 1
4```

### 输出

```
5 4 3 2 1```

# 题解

## 作者：int_R (赞：3)

场切模拟赛 T1。

思路为在给定序列中插入不在给定序列中的数。重点是字典序最小。

对于一个数 $x<A_1$，我们不能将它放在 $A_1$ 之前，因为这样会使最长上升子序列的长度变长，我们只能退而求其次的将它放在 $A_1$ 之后。

但可能会有若干个数小于 $A_1$，我们只需要将最小的那个放在 $A_1$ 之后，因为字典序要最小；其他的数我们又不能将其放在后面了，同样的原因——会使最长上升子序列长度变长。

所以流程就大概出来了：

1.放入一个给定序列中的数 $A_i$。

2.将不属于给定序列中最小的且小于 $A_i$ 的数放入序列。

但是要特殊处理 $A_k$，因为我们不能按照那个思路把剩下的数升序放在最后面，所以将剩下的数和 $A_k$ 按照降序顺序放在最后即可。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=2e5+10;
int n,k,a[MAXN],cur=1,q[MAXN],tot;
bool vis[MAXN];
int main()
{
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	cin>>n>>k;
	for(register int i=1;i<=k;++i) cin>>a[i],vis[a[i]]=true;
	for(register int i=1;i<=n;++i) if(!vis[i]) q[++tot]=i;//处理出来不在给定序列中的数
	for(register int i=1;i<k;++i)
	{
		cout<<a[i]<<' ';//放入a[i]
		if(cur<=tot&&q[cur]<a[i]) cout<<q[cur++]<<' ';//注意要小于a[i]!
	}
	q[++tot]=a[k];sort(q+cur,q+tot+1);//特殊处理a[k],其实没有必要排序
	while(tot>=cur) cout<<q[tot--]<<' ';//剩下的降序放
	return 0;
} 
```


---

## 作者：under_the_time (赞：2)

## 题意

> 给定长度为 $k$ 的正整数序列 $a$，保证 $a$ 单调递增；要求构造一个长度为 $n$（$n\ge k$）的排列 $p$，使得 $a$ 为 $p$ 的最长上升子序列之一且字典序最小。
>
> $1\le k\le n\le 2\times 10^5$。

## 解法

显然在 $a_1$ 出现前不能出现比 $a_1$ 小的，而且要求字典序最小所以 $a_1$ 一定填在 $p_1$ 上；同理 $a_k$ 出现后也不能再出现比 $a_k$ 大的。来手模一组数据：

```
14 5
3 6 7 9 12
```

首先令 $p_1\gets a_1$。接着我们填上最小的元素 $1$，即 $p_2\gets 1$。然后 $p_3\gets a_2$，后面填上没填过的最小的元素 $2$，以此类推。但是在把 $a_3$ 即 $7$ 填入时，$3$ 是 $a$ 中的元素，不能填，故填 $4$。在 $p_7\gets a_4,p_8\gets 5$ 时，由于 $a_5$ 即 $12$ 后面不能再出现比 $12$ 大的元素，所以 $14,13$ 一定要在 $a_5$ 之前填上；观察到之前填入的非 $a$ 中的元素已有 $k-1$ 即 $4$ 个且这些数字比后填入的非 $a$ 元素要小，如果令 $p_9\gets 13,p_{10}\gets 14$ 以追求字典序较小，会导致当前的最长上升子序列长度为 $k+1$（$p_2,p_4,p_6,p_8,p_9,p_{10}$），若改动前面填的数会导致字典序变大（“字典序最小/最大”总是优先使靠前的元素越小/越大），故这部分我们要从大到小填，即 $p_9\gets 14,p_{10}\gets 13$，接着 $p_{11}\gets a_5$。发现还剩下 $11,10,8$ 三个元素，同理从大到小填到 $a_5$ 后面。

所以最终的 $p=\{3,{\color{gray}1},6,{\color{gray}2,}7,{\color{gray}4,}9,{\color{gray}5,}{\color{orange}14,13,}12,{\color{green}11,10,8}\}$，黑色的是 $a$ 中元素，灰色的是紧接着 $a_i$ 填入的，橙色的是 $>a_k$ 所以填在 $a_k$ 之前的，绿色的是剩下没填的。整个过程我们都将除 $a$ 其他的最长上升子序列的长度控制在与 $a$ 等长。总结一下填的方法：

1. 填 $a_i$，然后填一个没填过的不在 $a$ 中的最小的元素，**如果这个元素比** $a_i$ **大就不填**，如果这个元素比 $a_{i+1}$ 小就会使最长上升子序列的长度 $>k$；如果这个元素比 $a_{i+1}$ 大，填入后的字典序不如不填。
2. 一直按照这个方法填，到 $a_k$ 时把 $>a_k$ 的元素从大到小先填入，然后填 $a_k$，最后把剩余的所有没填的元素从大到小填。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int a[maxn], k, n, p[maxn];
namespace Table { // 用来找不属于 a 的且没出现过的最大 & 最小元素
	bool vis[maxn]; int L, R;
	void init() { L = 1, R = n; }
	void add(int x) { vis[x] = 1; }
	int findL() { // vis 中的元素只会从 0 变到 1，所以可以这么做
		for (; L <= n && vis[L]; L ++);
		return L;
	}
	int findR() {
		for (; R > 0 && vis[R]; R --);
		return R;
	}
} using namespace Table;
int main() {
	scanf("%d %d", &n, &k), init();
	for (int i = 1; i <= k; i ++)
		scanf("%d", &a[i]), add(a[i]); // 这样 a[i] 就取不到了
    int pos = 0; // 表示当前填到哪了
	for (int i = 1; i < k; i ++) {
		p[++ pos] = a[i];
		if (findL() < a[i])
			add(p[++ pos] = findL());
	}
	for (; findR() > a[k]; add(p[++ pos] = findR()));
	for (p[++ pos] = a[k]; findR() > 0; add(p[++ pos] = findR()));
	for (int i = 1; i <= n; i ++)
		printf("%d ", p[i]);
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：2)

写个暴力，造几组小数据，观察规律发现，答案总是形如 $a_1(b_1)a_2(b_2)a_3(b_3)\dots a_{k-1}(b_{k-1})+\{c\}$

（其中 $+$ 表示序列拼接，$b_i$ 表示小于 $a_i$ 且之前没出现过的最小数，$c$ 为之前没出现过的数降序排序的结果）

$a_1(b_1)a_2(b_2)a_3(b_3)\dots a_{k-1}(b_{k-1})$ 中不存在长度 $>k-1$ 的上升子序列，可以保证 $\{a_k\}$ 是答案的 LIS。

```cpp
#include <cstdio>
int n, k;
bool b[200050];
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1, x, p = 1; i < k; ++i)
    {
        scanf("%d", &x);
        printf("%d ", x);
        b[x] = 1;
        while (b[p])
            ++p;
        if (p < x)
            printf("%d ", p), b[p] = 1;
    }
    for (int i = n; i; --i)
        if (!b[i])
            printf("%d ", i);
    return 0;
}
```


---

## 作者：NKL丶 (赞：2)

## Description 

给出一个长度为 $K$ 的上升序列 $A$，构造出一个长度为 $N$ 的**字典序最小**的排列，使得 $A$ 是该排列的 LIS（若原排列有多个 LIS 且 $A$ 为其中之一也是合法的）。（$1 \leq K \leq N \leq 2 \times 10^5$，$1 \leq A_i  \leq N$）

## Solution

考虑贪心。

不妨令 $A$ 的补集为 $B$ ，对于每个 $A_i$，我们都在 $B$ 中寻找**未被填入的小于当前 $A_i$ 的数**（若没有则跳过），在最终序列的 $A_i$ 后加入这个数，可以证明此时是符合题意的字典序最小的方案。

注意特殊处理 $A_K$，倒序输出所有尚未加入最终序列的数字。（包括在 $B$ 中的数）

## [Code](https://www.luogu.com.cn/paste/r4p5ncs6)

---

## 作者：hh弟中弟 (赞：2)

模拟赛 t1  [题目](https://www.luogu.com.cn/problem/AT_arc125_c)

题目大意为给出一个长度为 $k$ 的最长上升序列，求 $1$ 到 $n$ 合法排列中字典序最小的一个。

不难思考当给出的 $k$ 为 $1$ 时，直接将 $1$ 到 $n$ 倒序输出即可，所以特判；

然后从 $1$ 遍历到 $k-1$（$k$ 要特判）先将第 $i$ 个数输出，然后去找比第 $i$ 个数小的数中最小的那个（且没有被输出过）以此类推知道遍历到第 $k-1$ 个数。

$k$ 要特判是因为将比第 $k$ 个数大的数先输出，从而保证不改变最长上升序列，所以接下来只用将 $1$ 到 $n$ 中没有输出的数倒序输出就完成了。

附代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200086],ans[200086],vis[200086];
int main(){
	int n,k;cin>>n>>k;
	for(int i=1;i<=k;i++){
		cin>>a[i];
	}
	if(k==1){
		for(int i=n;i>=1;i--)cout<<i<<' ';
		return 0;
	}											//特判 
	int w=1;
	for(int i=1;i<k;i++){
		cout<<a[i]<<' ';vis[a[i]]=1;
		if(w<a[i]&&!vis[w])cout<<w<<' ',vis[w]=1;		//当w比a[i]小时输出 
		while(w<a[i+1]&&vis[w])w++;					//更新w的值 
	}
	for(int i=n;i>=1;i--){
		if(!vis[i])cout<<i<<' ';					//最后倒序输出 
	}
}
```

蒟蒻的第一篇题解，求过

update on 24.2.17：今天无意间看到，发现代码不对，好像是之前防止别人he，故意为之（唐氏），fixed。

---

## 作者：Rolling_star (赞：2)

考虑一个明显字典序不是最小但是满足条件的构造：

$$(a_1,a_1-1,\cdots,1),(a_2,a_2-1,\cdots,a_1+1),\cdots,(n,n-1,\cdots,a_{n-1}+1)$$

每一组只会向后一组贡献 $1$ 的最长上升子序列长度，但是这个字典序明显不是最小的，但是可以根据这种构造改进。

构造步骤为：

1. 一开始将 $[1,a_1)$ 加入集合 $B$。
2. 将 $a_i$ 加入构造的序列。
3. 取出当前集合 $B$ 中的最小数字加入序列，如果没有则不加入。
4. 将 $(a_i,a_{i+1})$ 加入集合 $B$。
5. 重复 $2\sim4$ 步直到 $i=k$。
6. 将 $[a_k,n]$ 加入集合 $B$。
7. 将集合 $B$ 中的元素倒序加入序列。

因为是每次取 $B$ 中最小的数，所以能保证字典序最小，对于 $a_i$ 到 $a_{i+1}$ 的每一个数因为是倒序的，一共有 $k$ 组这样的数，所以能保证最长上升子序列长度为 $k$。


```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;

int n,k,a[N],b[N],tot,now,num[N];

int main(){
    cin>>n>>k;
    for(int i=1;i<=k;i++)
        scanf("%d",a+i);
    for(int i=1;i<a[1];i++) b[++tot]=i;
    now=1;
    for(int i=1;i<k;i++){
        if(now<=tot) num[i]=b[now++];
        for(int j=a[i]+1;j<a[i+1];j++) b[++tot]=j;
    }
    for(int i=1;i<k;i++){
        printf("%d ",a[i]);
        if(num[i]) printf("%d ",num[i]);
    }
    for(int i=n;i>=a[k];i--)
        printf("%d ",i);
    for(int i=tot;i>=now;i--)
        printf("%d ",b[i]);
}
```

---

## 作者：Trump_ (赞：1)

由于题目里面让求**字典序最小**，因此我们可以隐约的想到做法：贪心。

我们现在将一个 $1$ 到 $n$ 的数列分成输入的数和除输入以外的数。然后我们再将 $a_k(k>1)$ 的最长上升子序列分成两个部分：$a_1,a_2,a_3,\dots,a_{k-1}$ 和 $a_k$。

## Part 1（第一个序列）

对于一个数 $x$，如果它小于 $a_i$，则 $x$ 一定不可以放在 $a_i$ 前面，因为它会造成最长上升子序列的长度增大，因此我们只能把它放在 $a_i$ 后面序列。

如果我们放多个比 $a_i$ 小的数在 $a_i$ 后面，让它们顺序排，会使最长上升子序列变长；如果我们让它们逆序排，不符合字典序最小的要求，所以只能放一个。

接下来对 $a_1$ 到 $a_{k-1}$ 进行操作即可。

## Part 2（第二个序列）

先来说说我们为什么分成两个序列。我们如果对于 $a_k$ 依照上面处理的方式处理的话。我们后面剩下的数该怎么处理呢？$a_k$ 后面的数不可能再比 $a_k$ 大，那样的话会使最长上升子序列的长度变长，所以 $a_k$ 后面的数一定要比 $a_k$ 的值小。这样，我们处理后一个序列的方式就出现了。将我们插剩下的数与 $a_k$ 进行排序，逆序输出就行。

## Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

int n, k, a[5211314];
int num[5211314], sum, pos = 1;

int main() {
	cin >> n >> k;
	for (int i = 1; i <= k; ++ i) {
		cin >> a[i];
	}
	for (int i = 1, now = 1; i <= n; ++ i) {
		if (i != a[now]) {
			num[++ sum] = i;
			//将不是输入的数从小到大存起来 
		}
		else now ++;
	}
	num[sum + 1] = 1e9;//防止在下面的if里一直输出0 
	for (int i = 1; i <= k - 1; ++ i) {
		cout << a[i] << " ";
		if (num[pos] < a[i]) {
			//找不在输入序列里第一个比a[i]小的数,插入到前面
			//可以得到字典序最小 
			cout << num[pos] << " ";
			pos ++;
		}
	}
	if (pos <= sum) {
		//特殊处理a[k] 
		for (int i = sum; i >= pos; -- i) {
			if (a[k] > num[i]) {
				cout << a[k] << " ";
				a[k] = -1;
			}
			cout << num[i] << " ";
		}
		if (a[k] != -1) {
			cout << a[k] << endl;
		}
		//将剩下的数从大到小输出 
	}
	else {
		cout << a[k];
		//只剩下a[k]的情况特殊看 
	}
	return 0;
}
```



---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc125_c)

# 前置知识

[贪心](https://oi-wiki.org/basic/greedy/) | [构造](https://oi-wiki.org/basic/construction/)

# 解法

对于任意一个未加入序列 $P$ 的数 $x<A_{i}(1 \le i \le k-1)$，如果其放在了 $A_{i}$ 的前面，会导致最长上升子序列长度加一，从而不符合题目要求。因此我们需要把 $x$ 放在 $A_{i}$ 后面，同理，为符合题目要求，我们仅选择放最小的那一个。

当 $i=k$ 的时候，如果我们仍按照如上的思路，会导致剩下的数只能升序依次加入序列 $P$，使得最长上升子序列长度变长，从而不符合题目要求。因此我们选择将其倒序输出，来保证最长上升子序列长度不变。
  - 之所以选择对 $i=k$ 的情况进行特判，是为了满足字典序最小的要求。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define sort stable_sort 
#define endl '\n'
int a[300001],vis[300001];
deque<int>q;
int main()
{
    int n,k,i;
    cin>>n>>k;
    for(i=1;i<=k;i++)
    {
        cin>>a[i];
        vis[a[i]]=1;
    }
    for(i=1;i<=n;i++)
    {
        if(vis[i]==0)
        {
            q.push_back(i);
        }
    }
    for(i=1;i<=k-1;i++)
    {
        cout<<a[i]<<" ";
        if(q.empty()==0&&q.front()<a[i])
        {
            cout<<q.front()<<" ";
            q.pop_front();
        }
    }
    while(q.empty()==0&&q.back()>a[k])
    {
        cout<<q.back()<<" ";
        q.pop_back();
    }
    q.push_back(a[k]);
    while(q.empty()==0)
    {
        cout<<q.back()<<" ";
        q.pop_back();
    }
    return 0;
}
```

---

## 作者：白简 (赞：0)

首先考虑 $k = 1$，唯一的方案就是倒序输出 $1$ 到 $n$。

我们可以想到，这道题的方法是向已经确定的序列 $A$ 中插入其他数。

对于一个数 $x(x < A_i)$，是不能把它放在 $A_i$ 前的，不然会使最长上升子序列的长度变大。

为了保证字典序最小，我们得把能放在 $A_i$ 后的最小的数放它后边。

最后要特殊处理 $A_k$，把剩下没有加入答案序列的部分倒序输出。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 200500;

int n,k;
int a[N],t[N];

int main() {
    cin >> n >> k;
    for(int i = 1;i <= k; i++) {
        cin >> a[i];
        t[a[i]] ++;
    }
    if(k == 1) {
        for(int i = n;i >= 1; i--)
			cout << i << " ";
        return 0;
    }
    
    int cur = 1;
    while(cur <= n && t[cur])
        cur ++;
    
    for(int i = 1;i < k; i++) {
        cout << a[i] << " ";

        if(cur < a[i]) {
            t[cur] ++;
            cout << cur << " ";
            cur ++;
        }

        while(cur <= n && t[cur])
            cur ++;
    }

    for(int i = n; i >= 1; i--) {
        if(!t[i] || i == a[k])
            cout << i << " ";
    }
    return 0;
}
```

---


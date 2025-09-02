# Cubes

## 题目描述

Let's imagine that you're playing the following simple computer game. The screen displays $ n $ lined-up cubes. Each cube is painted one of $ m $ colors. You are allowed to delete not more than $ k $ cubes (that do not necessarily go one after another). After that, the remaining cubes join together (so that the gaps are closed) and the system counts the score. The number of points you score equals to the length of the maximum sequence of cubes of the same color that follow consecutively. Write a program that determines the maximum possible number of points you can score.

Remember, you may delete no more than $ k $ any cubes. It is allowed not to delete cubes at all.

## 说明/提示

In the first sample you should delete the fifth and the sixth cubes.

In the second sample you should delete the fourth and the seventh cubes.

In the third sample you shouldn't delete any cubes.

## 样例 #1

### 输入

```
10 3 2
1 2 1 1 3 2 1 1 2 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10 2 2
1 2 1 2 1 1 2 1 1 2
```

### 输出

```
5
```

## 样例 #3

### 输入

```
3 1 2
1 1 1
```

### 输出

```
3
```

# 题解

## 作者：E1_de5truct0r (赞：2)

## 思路

这道题容易发现一个性质：$\sum_{j=1}^{m} cnt_j = n$，其中 $cnt_j$ 表示第 $j$ 种颜色的数量。

那么这道题其实就很好解决了：

首先，因为必须是同种颜色，我们可以枚举当前找的颜色 $i$。

然后，这就变成了基础双指针题目。我们让一个 $l$ 和 $r$ 记录是哪两个颜色中间。然后双指针不断跳，记录当前的最长子串是多少，然后取 $\max$ 即可。时间复杂度 $O(n)$。

注意：不能从 1 到 n 直接枚举，否则复杂度会退化为 $O(nm)$。因此，要用到链表的相关思想（或者说就是一个链式前向星）。在我的代码里，$head_i$ 表示 $i$ 颜色的起始点，$nxt_i$ 表示和 $i$ 颜色相同的下一个点的位置。运用方法同链式前向星。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int head[200005],lst[200005],nxt[200005],a[200005];
int main()
{
	int n,m,k; cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(!lst[a[i]]) head[a[i]]=i,lst[a[i]]=i; // 如果在之前没有和 a[i] 颜色相同的，那么就记一下 head
		else nxt[lst[a[i]]]=i,lst[a[i]]=i; // 否则，就更新上一个的 nxt。
		//lst 数组记录的是当前颜色上一次出现的位置，是为了方便更新 nxt 数组用的。
	}
	int ans=0;
	for(int i=1;i<=m;i++) // 枚举颜色
	{
		int l,r,cnt=1; l=r=head[i]; // 初始化 l,r,cnt。
		do
		{
			r=nxt[r]; cnt++; // 每次向后跳一个颜色
			while(r-l+1-cnt>k) l=nxt[l],cnt--; // 这一段里数的数量减去要保留的颜色的数量，就是要删去的数量。
			if(cnt>ans) ans=cnt; // 更新答案
		}while(nxt[r]); //只有这样写才能保证不重不漏，其他方法似乎或多或少可能会 WA。
	}
	printf("%d",min(ans,n)); // 特判 n==1 的情况，这个时候我的程序似乎会输出 2，所以和 n 取 min。
	return 0;
}
```

---

## 作者：Dream__Sky (赞：1)

题意要求删除 $k$ 个数后，求出最长的连续子串。那么首先考虑枚举子串中可能出现的每种颜色，对每一种颜色再进行处理。

我们记录下每一种颜色的下标（可以用 `vector` 存）。那如果要构成一个连续子串，就要删除每两个相同颜色中间的这些颜色，使左右两个相同颜色拼在一起。又发现，删除的个数是给定的，那我们可以用双指针维护。

双指针的右端点不停右移，直到与当前的左端点之间，需要删除的数超过了 $k$ 个，那么为了符合要求，再将左端点右移，在不停移动的过程中找最长子串的长度。

所有颜色需要枚举到的下标有 $n$ 个，再把它均分到每一次双指针操作中，复杂度即为 $O(n)$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k,maxn;
vector<int> v[100010]; 
int check(int x)
{
	int len=v[x].size();
	int l=0,r=0,ans=0;
	while(l<=r&&r<=len)
	{
		while(r<len&&v[x][r]-v[x][l]-(r-l)<=k) r++;
		ans=max(ans,r-l);
		l++;
	}
	return ans;
}
int main()
{
	cin>>n>>m>>k;
	for(int i=1,x;i<=n;i++) 
	{
		cin>>x;
		v[x].push_back(i);
	}
	
	for(int i=1;i<=m;i++)
		maxn=max(maxn,check(i));
	
	cout<<maxn;
	return 0;
}


```


---

## 作者：SerokSSR (赞：1)

## CF180E

### 题意简述

现有一数列 $a_1,a_2,…,a_n (1\leqslant a_i \leqslant m)$，求在最多删去 $k$ 个位置的数后，所能获得的最长连续子段的长度，要求该子段中所有数均相同．

### 解答

枚举每种颜色，这样问题就可被简化为对于每种颜色，求出其修改后的最长合法子段，可用尺取法求解。

尺取法与单调队列有关，应用范围比较小，要求原问题在满足条件的情况下，长度越长，答案越好。利用双指针 $l,r$ 及队列思想，对于同一个 $l$ 让 $r$ 尽可能延伸至最远，得到一个答案区间，$r$ 已到达最远后将与 $l$ 有关的信息弹出，对于多个答案区间找出最优解。

更详细的解释请看[这里](https://www.baidu.com/s?ie=UTF-8&wd=%E5%B0%BA%E5%8F%96%E6%B3%95)

### 代码

将原数列分块，对每种颜色建立链表，枚举时直接访问。

链表的每个节点存储该颜色块的左右端点。

```
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

const int N = 220000, M = 110000;

struct node {
	int l, r, next;
} a[N];

int tmp[M], n, m, k, h[M];

int main() {
	
	freopen("cf180e.in", "r", stdin);
	
	scanf("%d%d%d", &n, &m, &k);
	
	int f = 0, tot = 0, ans = 0;
	for(int i=1, c; i<=n; ++i) {
		scanf("%d", &c);
		if(f == c) a[tot].r = i;
		else {
			a[++tot] = (node) {i, i, c, 0};
			if(h[x]) a[tmp[c]].next = tmp[c] = tot;
			else h[x] = tmp[x] = tot;
			f = c;
		}
	}
	
	for(int i=1; i<=m; ++i) {
		if(h[i] == 0) continue; // 无该颜色
		int L = h[i], R = h[i], f = 0, sum = a[h[i]].r - a[h[i]].l + 1;
		for(; L; L = a[L].next) {
			for(; a[R].next and f + a[a[R].next].l - a[R].r - 1 <= k; R = a[R].next) 
				f += a[a[R].next].l - a[R].r - 1, 
				sum += a[a[R].next].r - a[a[R].next].l + 1;	
			ans = max(ans, sum); // 统计
			sum -= a[L].r - a[L].l + 1; // 弹出
			f -= a[a[L].next].l - a[L].r - 1;
		}
	}
	
	printf("%d\n", ans);
	
	return 0;
} 
```
### 都看到这儿了，不点个赞再走？
orz


---

## 作者：COsm0s (赞：0)

考虑二分答案。

将每个值 $val$ 的位置记录下来，记为 $vec_{val}$ 数组。

那么只要 $\exists val$，使得 $vec_{val,it+len}-vec_{val, it}+1-len\leq k$ 即可。

此式相当于在出现了 $len$ 个 $val$ 的区间内，需要删去区间长度减 $val$ 个数才能做到连续且相同。

我们二分 $len$ 长度。

复杂度 $\Theta((n+m)\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
namespace Jelly {
	const int N = 2e5 + 5, inf = 0x3f3f3f3f;
	int n, m, k, x;
	vector<int> vec[N >> 1];
	bool check(int mid) {
		for (int i = 1; i <= m; i ++)
			for (int j = 0; j + mid - 1 < vec[i].size(); j ++)
				if (vec[i][j + mid - 1] - vec[i][j] + 1 - mid <= k)
					return true;
		return false;
	}
	int main() {
		cin >> n >> m >> k;
		for (int i = 1; i <= n; i ++) cin >> x, vec[x].emplace_back(i);
		int l = 0, r = n + 1, ans = 1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid)) l = mid + 1, ans = mid;
			else r = mid - 1;
		}
		cout << ans << '\n';
		return 0;
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
//	cin >> T;
	while (T --) Jelly::main();
	return 0;
}
```


---

## 作者：⚡小林子⚡ (赞：0)

NOIp 前写个题解攒攒 rp。

------------

### Description：

给定 $\{a_n\}$（ $a_i\in[1,m]$ ），求删除至多 $k$ 个数后序列最长连续相同元素段长。 $n\leq 2\times10^5$ ， $m\leq 1\times10^5$ 。[link](https://www.luogu.com.cn/problem/CF180E)

------------

### Solution：

显然答案存在单调性，考虑二分。

使用 vector 记录每个值出现的位置，记为 $p$ 。对于 check 我们遍历值域，当前 check 合法的条件为存在一组 $(num,l)$ 满足 $p_{num,r}-p_{num,l}+1-mid\leq k$ ，其中 $r=l+mid-1$ （在出现了 $mid$ 个 $num$ 的区间内，需要删去区间长度减 $mid$ 个数才能做到连续且相同），这样单次 check 的复杂度是线性的。

时间复杂度 $\Theta((m+n)\log n)$ ，比 two-pointers 慢点但是好想好写。

------------

```cpp
#include<bits/stdc++.h>
#define inl inline
#define debug puts("dxsuki")
using namespace std;
typedef long long ll;
inl ll rd();
const int N=2e5+5,M=1e5+5;
int n,m,k,a[N];
vector<int>p[M];
inl bool check(int mid){
	for(int i=1;i<=m;i++)
		for(int j=0;j+mid-1<p[i].size();j++)
			if(p[i][j+mid-1]-p[i][j]+1-mid<=k)
				return 1;
	return 0;
}
int main(){
	n=rd();m=rd();k=rd();
	for(int i=1;i<=n;i++)
		a[i]=rd(),p[a[i]].push_back(i);
	int l=1,r=n+1,ans=0;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1,ans=mid;
		else r=mid;
	}
	printf("%d",ans);
	return 0;
}
inl ll rd(){
	char chh=getchar();bool ff=0;ll xx=0;
	for(;chh<48||chh>57;chh=getchar())ff=chh==45?!ff:ff;
	for(;chh>=48&&chh<=57;chh=getchar())xx=(xx<<3)+(xx<<1)+chh-48;
	return ff?-xx:xx;
}
```


---


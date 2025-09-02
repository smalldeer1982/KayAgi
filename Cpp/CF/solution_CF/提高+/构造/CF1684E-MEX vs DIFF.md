# MEX vs DIFF

## 题目描述

给你一个大小为n的数组a，保证数组内元素非负，你可以执行以下操作k次：

在一次操作中将数组内任意一个数字改为任何一个非负整数。

现在定义这个数组的成本为DIFF(a)−MEX(a)，其中 DIFF(a) 为a数组内元素去重后的数量，  MEX(a) 为数组中未出现的元素中最小的元素，
举个例子，MEX( { 1 , 2 , 3 } )=0 , MEX( { 0 , 1 , 2 , 4 , 5 } ) = 3。

现在给你数组a，求能实现的最小成本。

## 说明/提示

在第一个测试用例中，不需要任何操作来最小化 DIFF-MEX 的值。

在第二个测试用例中，可以将 5 替换为 1 。 数组 a 变为[ 0 , 2 , 4 , 1 ] , DIFF = 4，MEX=MEX( { 0 , 1 , 2 , 4 } )=3 ，所以答案是 1.

在第三个测试用例中，一个可能的数组 a 的变形是[ 4 , 13 , 0 , 0 , 13 , 1 , 2 ]，其中 DIFF = 5，MEX = 3。

在第四个测试用例中，一个可能的数组 a 的变形是 [ 1 , 2 , 3 , 0 , 0 , 0 ] 。

## 样例 #1

### 输入

```
4
4 1
3 0 1 2
4 1
0 2 4 5
7 2
4 13 0 0 13 1337 1000000000
6 2
1 2 8 0 0 0```

### 输出

```
0
1
2
0```

# 题解

## 作者：lingfunny (赞：7)

# [1684E. MEX vs DIFF](https://codeforces.com/problemset/problem/1684/E) *2100

题意：给 $n$ 个数，最多可以改 $k$ 个数，请最小化 $\operatorname{DIFF}-\operatorname{MEX}$。

首先观察性质，然后做。

1. 性质 1：$k$ 次修改一定会用完。证明：因为用了不可能使得答案更劣。
2. 性质 2：要修改，一定会修改成 $\operatorname{MEX}$。证明：修改成其它的没有意义，就算之后会用到，那先用到也没差。因为没有 $\operatorname{MEX}$ 这个数，所以一定要有人顶替它。
3. 由上面两个性质，可以得出最后的 $\operatorname{MEX}$  是固定的，先写个 `for` 跑出 $\operatorname{MEX}$。现在只需要 $\operatorname{DIFF}$ 最小即可。
4. 贪心。因为你会改的数是 $k$ 个，要让 $\operatorname{DIFF}$ 减少，只能选择让 $\ge \operatorname{MEX}$ 的数变成 $<\operatorname{MEX}$ 的。按照每个数出现的次数贪心即可。

```cpp
// Problem: E. MEX vs DIFF
// From: Codeforces - Codeforces Round #792 (Div. 1 + Div. 2)
// URL: https://codeforces.com/problemset/problem/1684/E
// Time: 2022-06-05 10:27
// Author: lingfunny

#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mxn = 1e5+10;

int n, k, a[mxn], b[mxn], tot;
int MEX, lft, diff, cgb;

// k 次修改一定要全用完
// 要修改，一定会修改成 MEX
// 问题就是修改哪些数变成 MEX
// 可以找到不管修改谁 ，修改 k 次后，MEX 最大为多少
// 看起来答案的 MEX 不变，于是看怎么删能让 diff 最少
struct node {
	int val, cnt;
	inline bool operator < (const node &rhs) const {
		int fu = val < MEX, fv = rhs.val < MEX;
		if(fu != fv) return fu > fv;
		return cnt > rhs.cnt;
	}
};
priority_queue <node> Q;

inline void solve() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i) scanf("%d", a+i);
	sort(a+1, a+n+1);
	for(int i = 1; i <= n; ++i) b[i] = a[i];
	tot = unique(b+1, b+n+1) - b - 1;
	MEX = 0, lft = k, diff = tot, cgb = n;
	// lft 剩下次数 diff 不同个数 cgb 可改动的数
	for(int i = 1; i <= tot && cgb; ++i) {
		while(b[i] != MEX && lft && cgb) ++MEX, --lft, --cgb, ++diff;
		if(b[i] == MEX && cgb) ++MEX, --cgb;
	}
	for(int i = 1; i <= n;) {
		int x = a[i], cnt = 0;
		while(x == a[i] && i <= n) ++cnt, ++i;
		if(cnt && x >= MEX) Q.push({x, cnt});
	}
	while(Q.size()) {
		auto [val, cnt] = Q.top(); Q.pop();
		if(lft + cnt <= k) --diff, lft += cnt;
	}
	while(Q.size()) Q.pop();
	printf("%d\n", diff - MEX);
}

int main() {
	int tt;
	scanf("%d", &tt);
	while(tt--) solve();
}
```

---

## 作者：ScottSuperb (赞：5)

## 解法分析
分享一种可能比较新奇的贪心做法。此做法的关键在于将 $\operatorname{MEX}$ 和 $\operatorname{DIFF}$ 分开处理，而不是同时处理。下文中提到的“方块”“塔”等概念仅为了使解法更加直观，实际上不用这些概念也可以解释。  
我们可以利用计数排序的原理把数据整理成类似下图的样子，其中方块下方数字表示数值，方块个数表示数量：  
![](https://cdn.luogu.com.cn/upload/image_hosting/hfaj6jr1.png)  
我们可以发现，修改一个数字（一次操作）相当于把一个方块移动了位置。而若称一个位置堆叠的方块为一个“塔”（至少一个方块）， 方块数量为高度，那么显然 $\operatorname{DIFF}$ 为所有塔的数量，$\operatorname{MEX}$ 为第一个空对应的数值即其左边所有塔的数量，于是成本就变成了第一个空右边所有塔的数量。这样一来，减少成本的方式就有了两种：一种是使第一个空靠后，另一种是使第一个空右边的塔变少。于是一举两得的操作出现了：用后面的方块依次填补前面的空。这样在搬走后面的塔的同时也可以让第一个空后移。由于有 $k$ 次操作，所以最多能填 $k$ 个空，我们只需在填空的同时删除用于存储数组的 map 的元素即可，可以保证剩下来的元素就是第一个空后面的塔。接下来就是贪心的操作，按出现次数分类记录下这些塔，从少到多移走方块，可以保证剩下来的塔最少。  
>注：这里对解法进行进一步解释说明。在检索能填的空时，“能填 $k$ 个空”表示**最多**需要 $k$ 次操作能填满这些空。检索完后处理后面的塔是为了用后面的方块去填前面的空以减小答案。因此检索空时若发现后面没有塔了，就无需再检索了，因为此时**必定**能在 $k$ 次操作内使答案为 $0$。

## 代码
读写函数定义已省略。
```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	int t = read(), n, k, ans, i, j;
	map<int, int> m, c;
	while (t--) {
		n = read(), k = read(), ans = 0, m.clear(), c.clear();
		while (n--)
			++m[read()];
		for (i = 0, j = 0; m.size() && (i < k || m[j]); m.erase(j++))
			if (!m[j] && i < k)
				++i;
		m.erase(j);
		ans = m.size();
		for (auto ii : m)
			++c[ii.second];
		for (auto ii : c)
			if (ii.first <= k)
				j = min(ii.second, k / ii.first), ans -= j, k -= j * ii.first;
			else
				break;
		write(ans, '\n');
	}
	return 0;
}
```

---

## 作者：LinkZelda (赞：3)

> 给定一个长度为 $n$ 的序列 $a$，你可以替换其中 $k$ 个数，求进行完操作后序列 $\rm DIFF-MEX$ 值的最小值。$\rm DIFF$ 为序列中不同的数的个数，$\rm MEX$ 为序列中最小的没出现过的非负整数。

我们发现序列的 $\rm MEX$ 值肯定 $\leq n$，所以可以考虑枚举每个 $\rm MEX$ 进行计算。

假设现在枚举的 $\rm MEX$ 为 $x$，那么我们要满足这个条件就需要把 $a_i$ 在值域上 $[0,x-1]$ 范围内没出现过的数给填上。

对于一个出现次数 $>1$ 的数，我们填一个空使 $\rm MEX$ 加 $1$，$\rm DIFF$ 也加 $1$，总的贡献为 $0$。对于一个出现次数 $=1$ 的数，$\rm DIFF$ 不变，$\rm MEX$ 加 $1$ 对答案贡献为 $-1$。所以我们肯定是优先拿 $[x+1,+\infty)$ 中出现次数较小的数来填空。

考虑维护一棵值域线段树，下标是出现次数，每个位置存这个出现次数的出现次数以及出现次数之和，每次我们线段树上二分数一下可以取到多少种数为 $0$ 即可。

时间复杂度为 $O(n\log n)$。[代码](https://www.luogu.com.cn/paste/dpkpw4xn)

---

## 作者：modfisher (赞：2)

## 思路
注意到一个序列的权值实质上是：大于序列 $\text{mex}$ 的数的种类数。这很容易证明。

更直观地，把这些数标在数轴上，那么权值就是第一个没有数的位置的后面的数的种类数。

修改一个数，可以看做是把一个数从数轴上挪到另一个位置。显然，用这些数去填上数轴上的“窟窿”会比放在一个已经有数的位置更优。不妨从小往大扫，找出前 $k$ 个“窟窿”，那么这之前的数就不必移动了，把这之后的 $k$ 个数填到前面来即可。

当然，这 $k$ 个数不是随便选的。我们希望后面剩下来的数的种类数尽可能少。因此要优先选出现次数少的数。

如此模拟即可。复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 5;

int a[maxn], c[maxn];
map<int, int> mp;

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		int n, k;
		scanf("%d %d", &n, &k);
		for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
		sort(a + 1, a + n + 1);
		int x = n + 1, k2 = k;
		a[0] = -1;
		for(int i = 1; i <= n; i ++){
			int y = max(a[i] - a[i - 1] - 1, 0);
			if(y <= k2) k2 -= y;
			else{
				x = i;
				break;
			}
		}
		for(int i = x; i <= n; i ++) mp[a[i]] ++;
		int m = unique(a + x, a + n + 1) - a - 1;
		for(int i = x; i <= m; i ++) c[i] = mp[a[i]];
		sort(c + x, c + m + 1);
		int ans = m - x + 1;
		for(int i = x; i <= m; i ++){
			if(k >= c[i]) ans --, k -= c[i];
			else break;
		}
		printf("%d\n", ans);
		mp.clear();
	}
	return 0;
}
```

---

## 作者：MujinH (赞：2)

# 思路

首先，观察题面可得，最优情况应该是集合中只出现 $0,1,2,3\cdots$ 的连续数字，重复并不影响答案，所以我们考虑贪心选择使得题目给出序列尽可能接近理想序列。

对于每个元素，只考虑改变它本身或者在它前面加入一些数字使得数列连续。

对于额外加入的数字，我们考虑在后面减掉，也是采用贪心，尽可能减少元素种类数，这里使用**优先队列**。

整体做法就是采用两段贪心，第一段在 $1\sim n-k$，第二段从第一个不能操作的数开始到结尾。

# Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
using ll=long long;
const int N=1e5+50;

int n,k,idx,cnt;//idx:当前这一项应该的数值,cnt表示用了后面多少个元素来补齐
int arr[N];
priority_queue<int,vector<int>,greater<int>> q;

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);idx=cnt=0;
		for(int i=1;i<=n;i++) scanf("%d",&arr[i]);
		sort(arr+1,arr+1+n);
		if(k>=n){
			printf("0\n");
			continue;
		}
		int i=1,flag=0;
		for(;i<=n-k;i++){
			while(arr[i]!=idx&&k>0) idx++,k--,cnt++;//把前面的补齐
			if(arr[i]==idx) idx++;//当前数字已满足要求
			else if(k>0) k--,arr[i]=idx,idx++;//当前数字不满足要求但可以改变
			else{
				flag=1;//当前数字不满足要求且不能改变
				break;
			}
			int j=i;//跳过重复数字
			while(j<=n&&arr[j]==arr[i]) j++;
			i=j-1;
		}
		if(!flag){//没有剩下的
			printf("0\n");
			continue;
		}
		//剩下的特殊处理,从之前断点处接着处理
		for(;i<=n;i++){
			int res=0;
			int j=i;
			while(j<=n&&arr[j]==arr[i]) res++,j++;//记录重复数字的个数
			q.push(res);
			i=j-1;
		}
		while(!q.empty()&&cnt>=q.top()){//前面用了cnt个元素,我们考虑贪心,让剩下的元素的种类数尽可能少
			cnt-=q.top();
			q.pop();
		}
		printf("%d\n",(int)q.size());
		while(!q.empty()) q.pop();//用完清空是好习惯
	}
	return 0;
}

```


---

## 作者：Polaris_Australis_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1684E)

## 题意

给定 $n$ 个元素的数组 $a$，最多可修改 $k$ 次，每次把数组中的一个值该为任意非负整数，求 $\text{DIFF}(a)-\text{MEX}(a)$，其中 $\text{DIFF}(a)$ 表示 $a$ 数组中元素的种类数，$\text{MEX}(a)$ 表示数组中没出现过的最小非负整数。

## 做法

首先根据式子，因为左连续中的种类数恰好是 $\text{MEX}(a)$，所以所求的答案为修改后数组不包含在左连续内的元素的种类数最小值。然后就很容易想到贪心，想办法让这个值最小，有两种手段：

1. 用不包含在左连续内的元素去填到左面；
2. 把 $\text{MEX}(a)$ 扩大，让他包含的元素种类更多，覆盖其他元素。

继续分析，发现两种手段可以合并：求出仅走 $k$ 步能够得到的最大的 $\text{MEX}(a)$，尽可能用比 $\text{MEX}(a)$ 大的元素往左面填，并且尽可能用个数较少的种类填，以保证剩余的种类数最少，如果可以把比 $\text{MEX}(a)$ 大的元素都用光，结果为 $0$，否则结果为剩余的种类数。

## 实现

1. 求出最大 $\text{MEX}$：找到不大于 $n-1$ 的数中所有不存在的数，从小往大填 $k$ 个，求出左连续长度即为 $\text{MEX}$。
2. 统计答案：只考虑比 $\text{MEX}$ 大的数，如果这些数不足 $k$ 个，答案为 $0$，否则贪心，取种类最小的数，取够 $k$ 个，看还剩多少种数字，即为答案。

PS：很好的贪心思维题！

## 代码

```cpp
// Problem: E. MEX vs DIFF
// Contest: Codeforces - Codeforces Round #792 (Div. 1 + Div. 2)
// URL: https://codeforc.es/contest/1684/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
#define db double
using namespace std;
namespace Std {
inline void maxy(int &x, int y) { x = max(x, y); }
inline void miny(int &x, int y) { x = min(x, y); }
inline int lowbit(int x) { return x & (-x); }
template <typename tp>
void read(tp &x) {
  x = 0;
  tp nev = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') nev = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = (x << 1) + (x << 3) + (c ^ 48);
    c = getchar();
  }
  x *= nev;
}
template <typename tp>
void write(tp x) {
  if (x < 0) {
    putchar('-');
    write(-x);
    return;
  }
  if (x / 10) write(x / 10);
  putchar((x % 10) ^ 48);
}
int t, n, now, num1, num2, a[200010], b[200010], c[200010], cnt, k;
bool mark[200010];
int main() {
  read(t);
  while (t--) {
    for (int i = 0; i < n; ++i) mark[i] = 0;
    a[0] = -1;
    read(n);
    read(k);
    cnt = 0;
    now = 0;
    for (int i = 1; i <= n; ++i) {
      read(a[i]);
    }
    sort(a + 1, a + 1 + n);
    num1 = 0;
    for (int i = 1; i <= n; ++i) {
      if (a[i] < n) {
        mark[a[i]] = 1;
      }
      if (a[i] != a[i - 1]) {
        b[++cnt] = a[i];
        c[cnt] = 1;
      } else {
        ++c[cnt];
      }
    }
    if (!k) {
      for (int j = 0; j < n; ++j) {
        if (!mark[j]) {
          num2 = j;
          break;
        }
      }
      printf("%lld\n", cnt - num2);
      continue;
    }
    int kk = k;
    for (int i = 0; i < n && kk; ++i) {
      if (!mark[i]) {
        --kk;
        mark[i] = 1;
      }
      if (!kk) {
        for (int j = i + 1; j <= n; ++j) {
          if (!mark[j]) {
            num2 = j - 1;
            break;
          }
        }
      }
      if (i == n - 1) num2 = n - 1;
    }
    if (num2 == n - 1)
      puts("0");
    else {
      num1 = 0;
      for (int i = 1; i <= cnt; ++i) {
        if (b[i] > num2) {
          num1 = i;
          break;
        }
      }
      if (!num1) {
        puts("0");
        continue;
      }
      sort(c + num1, c + 1 + cnt);
      int sum = 0;
      for (int i = num1; i <= cnt; ++i) sum += c[i];
      int ans = 0, nm = 0;
      for (int i = cnt; i >= num1; --i) {
        if (nm >= sum - k) break;
        ++ans, nm += c[i];
        if (nm >= sum - k) break;
      }
      printf("%lld\n", ans);
    }
  }
  return 0;
}
}  // namespace Std
#undef int
int main() { return Std::main(); }
```


---

## 作者：pengyule (赞：1)

有两种操作：
1. 用后面的数填补当前的 $mex$，以增大 $mex$
2. 把后面的数合并到已经有的数上，以减小 $diff$

就单次操作的贡献而言，前者的贡献至少为 $1$，后者的贡献至多为 $1$，因而优先考虑操作 1。  
这部分代码如下：

```cpp
for(int i=1;i<=n;i++)a[i]=read(),mp[a[i]]++;
int mex=0,Need=0,Already=0;
for(int i=0;i<=n;i++){
	if(i)Already+=!!mp[i-1];
	if(i&&!mp[i-1]){
		Need++;
		if(Need>K||Need>n-Already)break;
	}
	mex=i;
}
```

现在我们已经确定了 $mex$，只需对 $\ge mex$ 的位上的数使用操作 2，按照出现次数从小到大的顺序操作。  
这部分代码如下：

```cpp
vector<int>vec;
for(map<int,int>::iterator it=mp.lower_bound(mex);it!=mp.end();it++)
	vec.push_back(it->second);
sort(vec.begin(),vec.end());
int diff=vec.size();
for(int i:vec){
	if(K>=i)K-=i,diff--;
	else break;
}
cout<<diff<<'\n';
```

---

## 作者：王熙文 (赞：1)

竟然能自己想到 >1900 的题了。

## 思路

提供一个无脑思路。

考虑枚举 $\text{mex}$，那么在 $[0 , \text{mex}-1]$ 中没有出现过的数都需要被在 $[0,\text{mex}-1]$ 出现次数 $\ge 2$ 或在 $[\text{mex},+\infty)$ 中出现次数 $\ge 1$ 的数替换。

发现用在 $[\text{mex},+\infty)$ 且出现次数最少的一些数替换更优，因为这些数可以全替换完，会使 $\text{diff}$ 减一，而在 $[0 , \text{mex}-1]$ 中的数因为必须出现所以无法使 $\text{diff}$ 减一。

将在 $[\text{mex},+\infty)$ 的数的出现次数放进一个数据结构里，现在要最大化在不同数的个数（因为每有一个数用完了就会使 $\text{diff}$ 减一）。二分个数 $x$，则求前 $x$ 小的次数总和，与需要替换的数的个数比较。对于剩下的位置，只能用在 $[\text{mex},+\infty)$ 剩下的一些数（没法取完一个数）和 $[0 , \text{mex}-1]$ 的次数 $\ge 2$ 的数了。这些不会使 $\text{diff}$ 变化。

现在转化成一个数据结构问题：

* 插入数；（倒序枚举 $\text{mex}$，对于当前到的 $\text{mex}$ 这个数出现次数要放进去）

* 查询前 $k$ 小的数总和。

这个问题可以用平衡树+值域树状数组解决，具体方法如下：

值域树状数组维护 $\le x$ 的数总和以及个数，平衡树用来查询排名为 $k$ 的数。

插入直接做。

查询先求出排名为 $k$ 的数，记为 $a$，然后在值域树状数组上查询 $\le a$ 的数的总和。但这样会多算几个 $a$，所以这个总和在减去 $\le a$ 的数的个数减 $k$ 倍的 $a$ 即可。

## 参考代码

有一些细节：

* 首先需要记录 $[0 , \text{mex}-1]$ 中没有出现过的数的个数，如果这个数大于 $k$ 则当前的 $\text{mex}$ 一定不行。

* 其次要记录可以替换的数的个数（在 $[0,\text{mex}-1]$ 出现次数 $\ge 2$ 或在 $[\text{mex},+\infty)$ 中出现次数 $\ge 1$ 的数的个数），如果这个数小于$[0 , \text{mex}-1]$ 中没有出现过的数的个数，即无法替换完，也不行。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k;

int a[100010];

map<int,int> cnt;

struct BIT
{
	int tot,root;
	struct tree
	{
		int x,pri;
		int lc,rc;
		int siz,cnt;
	} tree[100010];
	int get_new(int x)
	{
		tree[++tot].x=x,tree[tot].pri=rand();
		tree[tot].lc=tree[tot].rc=0;
		tree[tot].siz=tree[tot].cnt=1;
		return tot;
	}
	void upd_siz(int p)
	{
		tree[p].siz=tree[tree[p].lc].siz+tree[p].cnt+tree[tree[p].rc].siz;
	}
	void zig(int &p)
	{
		int son=tree[p].lc;
		tree[p].lc=tree[son].rc;
		tree[son].rc=p;
		tree[son].siz=tree[p].siz;
		upd_siz(p);
		p=son;
	}
	void zag(int &p)
	{
		int son=tree[p].rc;
		tree[p].rc=tree[son].lc;
		tree[son].lc=p;
		tree[son].siz=tree[p].siz;
		upd_siz(p);
		p=son;
	}
	void insert(int &p,int x)
	{
		if(!p)
		{
			p=get_new(x);
			return;
		}
		++tree[p].siz;
		if(x==tree[p].x) ++tree[p].cnt;
		else if(x<tree[p].x)
		{
			insert(tree[p].lc,x);
			if(tree[tree[p].lc].pri<tree[p].pri) zig(p);
		}
		else
		{
			insert(tree[p].rc,x);
			if(tree[tree[p].rc].pri<tree[p].pri) zag(p);
		}
	}
	int get_val(int p,int x)
	{
		if(!p) return 0;
		if(x<=tree[tree[p].lc].siz) return get_val(tree[p].lc,x);
		else if(x<=tree[tree[p].lc].siz+tree[p].cnt) return tree[p].x;
		else return get_val(tree[p].rc,x-tree[tree[p].lc].siz-tree[p].cnt);
	}
} bst;

int tree1[100010],tree2[100010];

void upd(int cnt)
{
	int wz=cnt;
	while(wz<=n+1)
	{
		tree1[wz]+=cnt;
		++tree2[wz];
		wz+=wz&-wz;
	}
}

pair<int,int> get_sum(int wz)
{
	int ans1=0,ans2=0;
	while(wz)
	{
		ans1+=tree1[wz];
		ans2+=tree2[wz];
		wz-=wz&-wz;
	}
	return {ans1,ans2};
}

int nowins;

void ins(int cnt) // 添加一个后面的数（>=mex 的数）
{
	++nowins;
	bst.insert(bst.root,cnt);
	upd(cnt);
}

int get_ksum(int k) // 后面的数前 k 个的和
{
	if(!k) return 0;
	if(k>nowins) return 1e9;
	int shu=bst.get_val(bst.root,k); // 求出排名为 k 的数
	pair<int,int> szsz=get_sum(shu);
	// szsz.first 是 <=shu 的所有数之和，szsz.second 是 <=shu 的数的个数
	return szsz.first-shu*(szsz.second-k);
}

int main()
{
	int t; cin>>t; while(t--)
	{
		cnt.clear();
		bst.tot=bst.root=0;
		nowins=0;
		cin>>n>>k;
		memset(tree1,0,(n+2)*4),memset(tree2,0,(n+2)*4);
		int dif=0;
		for(int i=1; i<=n; ++i)
		{
			cin>>a[i];
			dif+=(!cnt[a[i]]);
			++cnt[a[i]];
		}
		int nowuse=0,cnt_tian=0; // 当前可以给 0~mex-1 填充的数的个数；0~mex-1 需要填充的个数
		for(auto it=cnt.begin(); it!=cnt.end(); ++it) // 此时 mex=n+1
		{
			if((it->first)>n) // >mex 的贡献
			{
				ins(it->second);
				nowuse+=(it->second);
			}
			else // <=mex 需要填的
			{
				if(it->second) nowuse+=(it->second)-1;
			}
		}
		for(int i=0; i<=n; ++i) cnt_tian+=(cnt[i]==0);
		int ans=1e9;
		for(int mex=n; mex>=0; --mex) // 从上往下枚举 mex
		{
			if(cnt[mex]) ins(cnt[mex]),++nowuse; // 之前只有 cnt[mex]-1 个可以填，现在变成 cnt[mex] 了
			else cnt_tian-=(cnt[mex]==0);
			if(cnt_tian<=k && nowuse>=cnt_tian) // 满足条件
			{
				int nowdif=dif;
				int l=0,r=1e9,mid,aans;
				while(l<=r)
				{
					mid=(l+r)>>1;
					if(get_ksum(mid)<=cnt_tian) aans=mid,l=mid+1;
					else r=mid-1;
				}
				nowdif+=get_ksum(aans)-aans; // 对于每个后面的，次数为 k，贡献为 k-1
				nowdif+=cnt_tian-get_ksum(aans); // 剩下的就得用后面零散的数和前面的数填了（此时每个数都会产生一个贡献）
				ans=min(ans,nowdif-mex);
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1683E 题解



## 思路分析

注意到有如下的观察：

> 观察：
>
> 最优方案一定是每次修改 $a_i$ 为当前序列的 $\operatorname{mex}$。
>
> 显然如果修改的 $a_i<\operatorname{mex}$，那么其对答案的贡献至多是 $0$，显然，做这样的一次操作肯定是不优的。
>
> 假如修改 $a_i$ 且 $a_i>\operatorname{mex}$，那么一定会把 $a_i$ 修改成另一个 $a_j$ 的值，那么每种情况对答案的贡献为：
>
> | $a_i\gets x$            | $cnt_{a_i}>1$                                                | $cnt_{a_i}=1$                                                |
> | ----------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
> | $x=\operatorname {mex}$ | $\operatorname{mex}\gets\operatorname{mex}+\delta+1,\operatorname{diff}\gets\operatorname{diff}+1$，贡献为 $\delta$. | $\operatorname{mex}\gets\operatorname{mex}+\delta+1,\operatorname{diff}\gets\operatorname{diff}$，贡献为 $\delta+1$. |
> | $x=a_j$                 | $\operatorname{mex}\gets\operatorname{mex},\operatorname{diff}\gets \operatorname{diff}$，贡献为 $0$. | $\operatorname{mex}\gets\operatorname{mex},\operatorname{diff}\gets \operatorname{diff-1}$，贡献为 $1$. |
>
> 其中 $\delta$ 为序列 $a$ 中从 $\operatorname{mex}+1$ 开始最多的连续自然数的数量，显然 $\delta\ge 0$。
>
> 那么我们发现把每次 $a_i$ 赋成 $\operatorname{mex}$ 一定不弱于把 $a_i$ 赋成某个其他的 $a_j$ 的值。

那么根据上面的分析，我们应该每次修改一个 $>\operatorname{mex}$，而且注意我们修改的**每一个** $a_i$ 都应该大于**最终**的 
$\operatorname{mex}$，否则 $a_i$ 对答案的贡献也是 $\le 0$ 的。

那么为了求出 $\operatorname{mex}$，我们可以运用二分：二分 $\operatorname{mex}=t$，计算需要多少次修改，与还剩下可修改的数的个数以及 $k$ 进行对比即可。

再求出了 $\operatorname{mex}$ 之后，我们把所有可以修改的数拿出来，显然我们要从 $cnt$ 小的到 $cnt$ 大的贪心选数修改，因为这样我们可以修改尽可能多的 $cnt=1$ 的数从而获得更多的 $\delta+1$。

显然可以用一个小根堆维护这个过程，注意如果小根堆已经删空了，说明此时所有数 $<\operatorname{mex}$，那么直接输出 `0`。

时间复杂度 $\Theta(n\log n)$。

## 代码呈现

```cpp
// LUOGU_RID: 98398708
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+1;
int a[MAXN],n,k;
map <int,int> cnt;
inline bool check(int mex) {
	vector <bool> vis(mex,false);
	int tot=0,lim=0;
	for(int i=1;i<=n;++i) {
		if(a[i]<mex) vis[a[i]]=true;
		else ++lim;
	}
	for(int i=0;i<mex;++i) {
		if(!vis[i]) {
			++tot;
			if(tot>k||tot>lim) return false;
		}
	}
	return true;
}
inline int count(int mex) {
	vector <bool> vis(mex,false);
	int tot=0;
	for(int i=1;i<=n;++i) if(a[i]<mex) vis[a[i]]=true;
	for(int i=0;i<mex;++i) if(!vis[i]) ++tot;
	return tot;
}
inline void solve() {
	int mex=0,diff=0;
	scanf("%d%d",&n,&k);
	cnt.clear();
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		++cnt[a[i]];
	}
	int l=0,r=n;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid)) mex=mid,l=mid+1;
		else r=mid-1;
	}
	priority_queue <int,vector<int>,greater<int> > q;
	for(auto p:cnt) {
		++diff;
		if(p.first>mex)	q.push(p.second);
	}
	int lim=count(mex);
	for(int i=1;!q.empty()&&i<=lim;++i) {
		int x=q.top(); q.pop();
		if(x>1) ++diff,q.push(x-1);
	}
	if(q.empty()) puts("0");
	else printf("%d\n",diff-mex);
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：bugmaker3243 (赞：0)

# 基本分析

首先注意到原式有两个关键元素：$\operatorname{MEX}$ 和 $\operatorname{DIFF}$。

欲使原式最小，则 $\operatorname{MEX}$ 应越大越好，$\operatorname{DIFF}$ 应越小越好。

假设最终的 $\operatorname{MEX}(a)=x$，则：
- 每次操作一定是将 $\geq x$ 的元素变为 $<x$ 的元素。
- $k$ 次操作一定全部用完。

进一步拓展第一个性质，可以发现：每次操作一定是将一个 $\geq x$ 的元素转化为 $\operatorname{MEX}$，此操作可使 $\operatorname{MEX}$ 至少增加 $1$。

又因为增加 $\operatorname{MEX}$ 和减少 $\operatorname{DIFF}$ 并不矛盾。

由以上两点，可知最终的 $\operatorname{MEX}$ 即为可以达到的最大 $\operatorname{MEX}$，而答案可以转化为最终 $\geq x$ 的数的种类。

# 具体实现

用 $\operatorname{map}$ 统计每个数的出现次数，定义 $sum_i=sum_{i-1}+$ [ $map_i$ ]。

设最终的 $\operatorname{MEX}(a)=x$，显然 $x\leq n$ 且 $x$ 为最大的满足 $i-sum_i+1\leq k$ 的 $i$ 。

于是暴力求出 $x$，在转化过程中优先转化出现次数小的数，这样可以尽可能将更多种数转化完，即使 $\operatorname{DIFF}$ 减少的尽可能多。

于是用优先队列或者 $set$ 维护出现次数最小的数，维护当前的 $\operatorname{DIFF}$ 即可。

时间复杂度 $O(N\log N)$，当前 $90ms$ 暂列最优解。

# 代码（请勿抄袭）

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define P pair<int,int>
using namespace std;
int t,n,k,maxn,ans,a[N],sum[N];
map<int,int>m;
set<P>s;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		m.clear();
		s.clear();
		maxn=ans=0;//多组数据，记得初始化 
		scanf("%d %d",&n,&k);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),m[a[i]]++;//统计出现次数 
		sum[0]=m[0]?1:0;
		for(int i=1;i<=n;i++) sum[i]=(m[i]?sum[i-1]+1:sum[i-1]);
		for(int i=1;i<=n;i++) if(i+1-sum[i]<=k) maxn=max(maxn,i);//暴力找最终的MEX 
		for(auto x:m)
			if(x.first>maxn&&x.second)
				s.insert(make_pair(x.second,x.first)),ans++;//统计有几种数 
		while(!s.empty()&&k>0)
		{
			P tmp=*s.begin();
			s.erase(s.find(tmp));
			if(k>=tmp.first) ans--;
			k-=tmp.first;//模拟转化并维护答案 
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---


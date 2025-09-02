# Anya and Cubes

## 题目描述

Anya loves to fold and stick. Today she decided to do just that.

Anya has $ n $ cubes lying in a line and numbered from $ 1 $ to $ n $ from left to right, with natural numbers written on them. She also has $ k $ stickers with exclamation marks. We know that the number of stickers does not exceed the number of cubes.

Anya can stick an exclamation mark on the cube and get the factorial of the number written on the cube. For example, if a cube reads $ 5 $, then after the sticking it reads $ 5! $, which equals $ 120 $.

You need to help Anya count how many ways there are to choose some of the cubes and stick on some of the chosen cubes at most $ k $ exclamation marks so that the sum of the numbers written on the chosen cubes after the sticking becomes equal to $ S $. Anya can stick at most one exclamation mark on each cube. Can you do it?

Two ways are considered the same if they have the same set of chosen cubes and the same set of cubes with exclamation marks.

## 说明/提示

In the first sample the only way is to choose both cubes and stick an exclamation mark on each of them.

In the second sample the only way is to choose both cubes but don't stick an exclamation mark on any of them.

In the third sample it is possible to choose any of the cubes in three ways, and also we may choose to stick or not to stick the exclamation mark on it. So, the total number of ways is six.

## 样例 #1

### 输入

```
2 2 30
4 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 2 7
4 3
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 1 1
1 1 1
```

### 输出

```
6
```

# 题解

## 作者：liangbowen (赞：29)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF525E)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16795772.html)

比较套路的折半搜索。代码实现略微繁琐。

## 思路

每个数有三个状态：不选、选 $a_i$、选 $a_i !$。

数据范围 $n \le 26$，暗示着爆搜，但是 $3^{26}$ 会爆炸。这时可以使用神仙搜索：$\text{meet in the middle}$。

折半搜的含义很显然：把序列分成两半，左右分别爆搜，再考虑合并左右答案。

首先看左边的搜索。这个很容易，不就是普通的爆搜吗！

```cpp
int n, k, a[N], mid; //mid = n / 2
LL s, ans;
short choose[N];
LL fac(int x) //求 x!  如果太大了（大于s了）就返回 -114514 
{
	LL mul = 1;
	for (int i = x; i; i--) //太大时，倒序枚举可以更快返回-114514 
	{
		if (mul > s / i) return -114514;
		//这里有一个细节，需要先判-114514再乘。
		//因为mul很容易爆LL，一不小心乘个i，可能就爆了。
		//因此，if (mul * i > s) 可以移项转化为 if (mul > s / i) 就万无一失了。 
		//当然，直接开__int128也行，毕竟现在CCF允许使用它。 
		mul *= i;
	}
	return mul;
}
map <pil, int> mp; //mp[mk(cnt, sum)]表示：使用了多少次阶乘、和是多少
map <LL, bool> vis; //vis[sum]表示：sum有无出现过 
void chk()
{
	LL sum = 0;
	int cnt = 0;
	for (int i = 1; i <= mid; i++)
		if (choose[i] == 1)
		{
			if (sum + a[i] > s) return;
			sum += a[i];
		}
		else if (choose[i] == 2)
		{
			LL ai = fac(a[i]);
			if (ai == -114514 || cnt + 1 > k || sum + ai > s) return; //看有没有超过k和s 
			sum += ai, cnt++;
		}
	mp[mk(cnt, sum)]++, vis[sum] = true;
}
void dfs(int x)
{
	if (x > mid) {chk(); return;}
	for (int i = 0; i < 3; i++) choose[x] = i, dfs(x+1); //0表示不选，1表示选a[x]，2表示选a[x]阶乘 
}
```

然后考虑右边的爆搜。

```cpp
void DFS(int x) //和dfs()极其相似，只不过更改了边界条件与chk() 
{
	if (x > n) {CHK(); return;}
	for (int i = 0; i < 3; i++) choose[x] = i, DFS(x+1); 
}
```

$\operatorname{CHK()}$ 的含义是将左右答案合并，计算最终答案。

和 $\operatorname{chk()}$ 也很相似，不同点只有边界与统计答案的部分。

理解了左边就很容易理解右边。

```cpp
void CHK() //和chk()极其相似，只不过最后更改成了统计答案 
{
	LL sum = 0;
	int cnt = 0;
	for (int i = mid + 1; i <= n; i++) //不同点 
		if (choose[i] == 1)
		{
			if (sum + a[i] > s) return;
			sum += a[i];
		}
		else if (choose[i] == 2)
		{
			LL ai = fac(a[i]);
			if (ai == -114514 || cnt + 1 > k || sum + ai > s) return;
			sum += ai, cnt++;
		}
	if (vis.count(s - sum)) ans += calc(k - cnt, s - sum); //不同点
} 
```

最后输出答案即可。

时间复杂度大约是 $O(3^{\frac{n}{2}} \times \log_3^\frac{n}{2})$。由于是折半搜，时间大约是普通爆搜开根。

可见 $\text{meet in the middle}$ 并不是玄学算法，它是有时间保证的。

重点是它**和普通爆搜很相似**，要多处理一点东西罢了。这也是它在 OI 界小有名气的原因。

## 完整代码

[link](https://codeforces.com/contest/525/submission/175890539)。

希望能帮助到大家！

---

## 作者：岚雪 (赞：16)

首先我们一眼就能看出来这道题的思路是$\text{meet\ in\ the\ middle}$~~`好吧其实是因为yanQval直接提供了思路`~~。

注意到对于每个数都有三种状态：不选，选，选且阶乘，故直接$\text{dfs}$的复杂度为$3^n$，而采用$\text{meet\ in\ the\ middle}$的话是$\displaystyle{2\times 3^{\frac{n}{2}}}$，刚好能卡进时间范围内。

首先我们介绍一个$\text{C++11STL}$神器就是$\text{unordered\_map}$，写法与$\text{map}$完全一样，但是这个东西比$\text{map}$快的不止一点，$\text{map}$的查询复杂度是$\text{O(log n)}$的，但这个的查询复杂度是常数时间。当然神奇的$\text{\_\_gnu\_pbds}$里面的$\text{gp\_hash\_table}$跟这个差不多快~~`反正NOIP考试都tm不给用`~~

然后就是常规操作了……

首先预处理阶乘数组。

```
fact[1] = 1ll;
    for (int i = 2; i <= 20; i ++)
        fact[i] = fact[i - 1] * i;
```

对于前一半，每一个状态我们记录下两个值，一个是目前用了几个阶乘符号，一个是目前的和，即$\text{unordered\_map<long long, long long>M[MAXN]}$，其中$\text{M[k][i]}$表示前一半的数使用了$\text{k}$个阶乘符号，得到的和为$\text{i}$的方案数。

```
unordered_map<long long, long long>M[MAXN];
void dfs1(int now, int end, long long S, int used) {
	if (used > k)
		return ;
    if (now > end) {
    	M[used][S] ++;
        return ;
    } 
    dfs1(now + 1, end, S, used);
    dfs1(now + 1, end, S + a[now], used);
    if (a[now] <= 20)
        dfs1(now + 1, end, S + fact[a[now]], used + 1);
}
// 下面是调用语句
dfs1(1, n / 2, 0, 0);
```

对于后一半，我们采用与前一半相同的递归方式，不同的是对于每个状态，我们只需要判断前一半所得到的所有状态中，有没有能与之对应并组成答案的，最后再加上可行方案数即可。

### 这里要特别说一句，不一定要用到$\text k$个阶乘符号，小于等于$\text k$就可以了。

```
void dfs2(int now, int end, long long S, int used) {
	if (used > k)
		return ;
    if (S > s)
        return ;
    if (now > end) {
    	for (int i = 0; i <= k - used; i ++) 
		    ans += M[i][s - S]; 
        return ;
    }
	dfs2(now + 1, end, S, used);
	dfs2(now + 1, end, S + a[now], used);
	if (a[now] <= 20)
		dfs2(now + 1, end, S + fact[a[now]], used + 1);
}
```

由于我们用了更强大的数据结构，所以不需要任何优化。（我不是针对$\text{Pascal}$党，但是$\text{STL}$真的可以为所欲为）

贴一发完整代码：
```
#include <bits/stdc++.h>
using namespace std;

const int N = 30;

unordered_map<long long, long long>M[N];
long long fact[N];
int n, k, a[N];
long long s, ans;
void dfs1(int now, int end, long long S, int used) {
	if (used > k)
		return ;
    if (now > end) {
    	M[used][S] ++;
        return ;
    } 
    dfs1(now + 1, end, S, used);
    dfs1(now + 1, end, S + a[now], used);
    if (a[now] <= 20)
        dfs1(now + 1, end, S + fact[a[now]], used + 1);
}
void dfs2(int now, int end, long long S, int used) {
	if (used > k)
		return ;
    if (S > s)
        return ;
    if (now > end) {
    	for (int i = 0; i <= k - used; i ++) 
		    ans += M[i][s - S]; 
        return ;
    }
	dfs2(now + 1, end, S, used);
	dfs2(now + 1, end, S + a[now], used);
	if (a[now] <= 20)
		dfs2(now + 1, end, S + fact[a[now]], used + 1);
}
int main() {
	freopen("CF525E.in", "r", stdin);
	freopen("CF525E.out", "w", stdout); 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k >> s;
    fact[1] = 1ll;
    for (int i = 2; i <= 20; i ++)
        fact[i] = fact[i - 1] * i;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];
    dfs1(1, (n + 1) / 2, 0, 0);
    dfs2((n + 1) / 2 + 1, n, 0, 0);
    cout << ans << endl;
    return 0;
}

```

---

## 作者：ForgotDream_CHN (赞：7)

# CF525E Anya and Cubes

### 题意

给出 $n(1 \le n \le 25)$ 个元素的序列 $a$ 与整数 $k(0 \le k \le n)$，要求将序列中最多 $k$ 个数变为其阶乘后选取数字使得其和为 $s(1 \le s \le 10^{16})$ 的方案数。

### 思路

一眼便能看出又要搜索求解了，我们先考虑不加任何优化的搜索。

对于序列中的每一个数，存在三种可能：  

1. 不选；
2. 直接选；
3. 变成其阶乘后再选。

那么总的时间复杂度为 $3^{25} = 2.5 \times 10^{12}$，无法接受。

如何降低时间复杂度呢？

我们注意到如果搜索的数字只有 $n/2$ 个的话，时间复杂度为 $3^{13} = 1.5 \times 10^6$，可以接受。

于是我们考虑折半搜索，即先搜出前面一半数字的可能总数，用一个 hash 表或 `map` 存下来后，再对后一半数字进行搜索，最后找出匹配的总数。时间复杂度就为 $O(3^{13})$。

实现的细节都在代码里了。

### 代码

```cpp
#include <iostream>
#include <cstdio>
#include <unordered_map>

using namespace std;

typedef long long ll;

unordered_map<ll, ll> m[30];   // 使用了 unordered_map，比普通的 map 快，但这道题好像不卡 map？
// m[i][j] 代表用了 i 个阶乘符号，总和为 j 的方案数
int n, k;
ll ans;   // 答案开 long long 好习惯
ll s, a[30];
ll fac[30];

// 对前一半数字进行搜索
void dfs1(int cur = 1, int cnt = 0, ll sum = 0) {   // 当前处理到第 cur 个数字，用了 cnt 个阶乘符号，总和为 sum
	if (cur >= n / 2 + 1) {   // 当搜索的数字个数达到 n / 2 时，统计后退出搜索
		m[cnt][sum]++;
		return;
	}
	dfs1(cur + 1, cnt, sum);   // 不取当前数字
	if (sum + a[cur] <= s) dfs1(cur + 1, cnt, sum + a[cur]);   // 直接取当前数字
	if (a[cur] <= 19 && sum + fac[a[cur]] <= s && cnt < k) dfs1(cur + 1, cnt + 1, sum + fac[a[cur]]);   // 将当前数字变成其阶乘后再取
	// 这里要注意，由于 s <= 1e16，而 19！ 已经远大于 1e16，所以当当前数字大于19没有必要搜（而且再大的话 long long 也存不下）
	// 记得判断 cnt < k
	return;
}

// 对后一半数字进行搜索
void dfs2(int cur = n / 2 + 1, int cnt = 0, ll sum = 0) {   // 同 dfs1
	if (cur >= n + 1) {
		// 这道题不要求用完所有的！
		// 所以当已经搜完了整个序列时，所有满足 i + cnt <= k 并且 j + sum = s 的 m[i][j] 都需要计入总数
		for (int i = 0 ; i + cnt <= k; i++) {
			if (m[i].count(s - sum))
				ans += m[i][s - sum];
		}
		return;
	}
	dfs2(cur + 1, cnt, sum);
	if (sum + a[cur] <= s) dfs2(cur + 1, cnt, sum + a[cur]);
	if (a[cur] <= 19 && sum + fac[a[cur]] <= s && cnt < k) dfs2(cur + 1, cnt + 1, sum + fac[a[cur]]);
	return;
}

void solve() {
	fac[0] = 1;
	for (int i = 1; i <= 19; i++) fac[i] = fac[i - 1] * i;   // 预处理阶乘
	dfs1(), dfs2();
	cout << ans << endl;
	return;
}

int main() {
	cin >> n >> k >> s;
	for (int i = 1; i <= n; i++) cin >> a[i];
	solve();
	return 0;
}
```

---

## 作者：MoonCake2011 (赞：5)

例题:[Anya and Cubes](https://www.luogu.com.cn/problem/CF525E).

大水紫题.

此题是一个子集和问题的变种。

现在有三个选择:选，不选，选并把它阶乘一下。

这样，时间复杂度高达 $O(3^{26})$。

因为 $S$ 不超过`long long`，所以只有 $a_i \le 20$ 才有权利去阶乘。

我们采用双向搜索。

合并是个难题。

我们尝试建立一个`unordered_map` (C++11) 数组把前半段的结果标记(注意重复)下来，第 $i$ 个`unordered_map`数组表示用 $i$ 个阶乘得到的集合产生的标记。

接着，把后半段得到的结果对其进行匹配。

设后半段的某个结果需用到的阶乘数为`p`,选到的数的总和为`sum`。

我们设 $1 \le x \le k-p$。

我们统计第 $x$ 个`unordered_map`的 $S-sum$ 项的个数.

提前预处理阶乘，我们成功 AC。

[代码](https://www.luogu.com.cn/paste/3edmdtuu).

---

## 作者：quarmer (赞：5)


### 思路
首先爆搜思路很好想，每个数要么选它本身，要么选它的阶乘，要么不选，这样复杂度上界是 $O(3 ^ n)$ 的，显然会超时。

然后我们就可以想到神器：**折半搜索**

思路就是，先爆搜从 $1$ 到 $\frac{n}{2}$ ，用一个二维数组 $a[num][sum]$ 来表示用了 $num$ 个阶乘，和为 $sum$ 的方案数。

然后第二次搜索从 $\frac{n}{2}$ 到 $n$，与第一次相结合，得到答案，像这样

```
for(int i = 0 ; i <= k - num ; i++)
	if(a[i][s - sum])ans += a[i][s - sum];
```

$num$ 和 $sum$ 表示后一半用了 $num$ 个阶乘，组成的和为 $sum$ 。题目中没有说阶乘必须用完，所以需要一个循环来枚举一下用了多少个阶乘。此时 a 数组中已经存了前一半的结果，我们只需要看一下后一半有没有能与前一半结合组成和为 $s$ 的，累加即可。

此时复杂度为 $O(3 ^ \frac{n}{2})$ 可以承受。

### 细节
 
a 数组开普通数组显然的空间不够，所以要开 map。但 $O(3 ^ \frac{n}{2})$ 已经超过 $10 ^ 6$，在乘上一个 map 的 $\log$ 会超时。所以我们要用 unordered_map，这相当于一个哈希表，查询复杂度是 $O(1)$ 的，这样就可以很轻松的过了。

至于阶乘，像这样预处理一下数组就好了。
```cpp
js[1] = 1 ;
for(int i = 2 ; i <= 19 ; i++)js[i] = js[i - 1] * i ;
```
最后记得开 long long。

### 代码

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
#include<stack>
#include<vector>
#include<set>
#include<unordered_map>
using namespace std;
#define int long long
int a[1005] ;
int js[30] ;
int n, k, s ;
int mid ;
int ans ;
unordered_map<long long, int>mp[30];
void dfs1(int x, int num, int sum){
	if(x > mid){
		mp[num][sum]++ ;
		return ;
	}
	dfs1(x + 1, num, sum) ; //不选
	if(sum + a[x] <= s)dfs1(x + 1, num, sum + a[x]) ; //选它本身
	if(num < k && a[x] <= 19 && sum + js[a[x]] <= s)dfs1(x + 1, num + 1, sum + js[a[x]]) ; //选它的阶乘
}
void dfs2(int x, int num, int sum){
	if(x > n){
		for(int i = 0 ; i <= k - num ; i++)if(mp[i][s - sum])ans += mp[i][s - sum];
		//统计答案
		return ;
	}
	dfs2(x + 1, num, sum) ; //不选
	if(sum + a[x] <= s)dfs2(x + 1, num, sum + a[x]) ; //选它本身
	if(num < k && a[x] <= 19 && sum + js[a[x]] <= s)dfs2(x + 1, num + 1, sum + js[a[x]]) ; //选它的阶乘
}
signed main(){
	js[1] = 1 ;
	for(int i = 2 ; i <= 19 ; i++)js[i] = js[i - 1] * i ; 
	//预处理阶乘数组，根据 s 的大小比 19！大的就可以直接不考虑了
	cin >> n >> k >> s; 
	for(int i = 1 ; i <= n ; i++)cin >> a[i] ;
	mid = n >> 1 ;
	dfs1(1, 0, 0) ;
	dfs2(mid + 1, 0, 0) ;
	cout << ans ;
	return 0 ;
}
```

---

## 作者：小黑AWM (赞：4)

# 啊啊啊啊，终于A掉这题了，蒟蒻人生第一道紫题！

?**首先感谢~~yanQval~~老师提供的meet-in-middle思路帮助，（虽然怎么用前缀和卡进去我是真的没听懂……），其次感谢的~~chen_zhe~~和~~WorldBest牛顿~~提供快读模板帮助，还要感谢Kato_Megumi开源的AC source提供的启发。
**

***

### 咱们先来谈谈思路，这个最重要了。

首先，引入概念，meet-in-middle：meet in middle 又称折半搜索，是一种特殊的搜索技巧，它是分治思想
的一种体现。
具体来说，能够使用的情况大多是用若干变量，你要给每个变量一个取
值，最终满足一些要求。
如果我们直接搜索，那么复杂度就是可能的情况数，但一些题目我们可
以将这些变量分为两部分，对于每个部分我们分别使用暴力的搜索方法
去搜索，然后两部分搜索结束之后，我们想办法使用一些数据结构将两
部分的信息合并。这样复杂度就成功降到了 原状态数。需要注意的是，如果我们合并的时候采用了暴力合并，即两两枚举，那 么不难发现，复杂度又重新回到了原来的复杂度，所以算法的重点类似 于分治法，在于如何合并。-----来自yanQval课件搜索ex

那么一看题面，不难发现，每个数有，不选、选上、选上并阶乘三种状态，且序列长26，那么爆搜的最差复杂度就是$3^{26}$肯定爆炸。

那么通过巧妙的meet-in-middle我们就把这题变成了$ 2 \times 3 ^{\frac{13}{2}}$(假装map O(1))，所以问题就是如何合并呢？

很有趣的方法，我们通过把左半边的所有情况枚举出来（$3 ^{\frac{n}{2}}$）然后把能 **_形成的每一种和的方案数抛到一个对应阶乘数的map里面去便于查询_** （敲黑板划重点），再枚举右半边的所有情况，然后** _把整体的和减去枚举出的右半边的和，那就是这右半边需要的左半边的和_** 然后在map中查询答案加上这些种数就可以了。
![配图解释](https://cdn.luogu.com.cn/upload/pic/35338.png)

然后这题细节也非常非常的多，这里稍微讲一下如何处理"!"，其实也很容易开27个map就好了，这组数用几个阶乘号就放第几个map。其他坑点具体看代码我都加了注释。

```cpp
#include <cstdio>
#include <iostream>
#include <map>
#pragma GCC optimize(3)//O3开关
#define ll long long
using namespace std;
map<ll,ll> ma[30];//一个左半边的所有数的和到能出这个和的方案数的映射，供合并
ll fact[21]={1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,6227020800,87178291200,1307674368000,20922789888000,355687428096000,6402373705728000,121645100408832000,2432902008176640000};//只需要预处理出够用的阶乘就够了，由于S<=10^16在long long以内，所以我们可以直接打表写1-20的阶乘，显然够了,(一个有效剪枝太大的根本不用判要不要加阶乘)
const int maxn=30;
int r,k,half,lim;
ll S,a[maxn],ans;//划重点开long long,不开一片WA
inline char nc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline ll read()
{
    char ch=nc();long long sum=0;
    while(!(ch>='0'&&ch<='9'))ch=nc();
    while(ch>='0'&&ch<='9')sum=(sum<<1)+(sum<<3)+ch-48,ch=nc();
    return sum;
}//感谢chen_zhe和World_Best牛顿提供的快读帮助
void dfs1(ll sum,int t,int m){// sum 当前凑出的和，t 用了几个阶乘号(魔法棒)可以给左边用，m 现在用到第几个数字(cube)
    if(m==half+1){
        ma[t][sum]++;
        return;
    }
    dfs1(sum,t,m+1);
    if(a[m]+sum<=S)
        dfs1(sum+a[m],t,m+1);
    if(a[m]<=lim&&fact[a[m]]+sum<=S&&t<k)
        dfs1(sum+fact[a[m]],t+1,m+1);
}
void dfs2(ll sum,int t,int m){ // sum 当前凑出的和，t 还剩几个阶乘号(魔法棒)可以给左边用，m 现在用到第几个数字(cube)
    if(m==half){//在第二个方向狂扫到half的时候进行合并操作
        for(int i=0;i<=t;i++)
            if(ma[i].count(sum))ans+=ma[i][sum];//就这一步if卡进去了2s的时限！
        return;}
    if(a[m]<=lim&&sum-fact[a[m]]>=0&&t>=1)
        dfs2(sum-fact[a[m]],t-1,m-1);
    if(a[m]<=sum)
        dfs2(sum-a[m],t,m-1);//这里我是直接把S，k减掉，这样就不用再合并的时候再求一次左半边需要的长度了。
    dfs2(sum,t,m-1);
}
int main(){
    lim=19;
    r=read();
    k=read();
    S=read();
    for(int i=1;i<=lim;i++)
        if(fact[i+1]>S)
        {lim=i;break;}
    for(int i=1;i<=r;i++)
        a[i]=read();
    if(r==1){
        if(a[1]==S)ans++;
        if(a[1]<=lim&&fact[a[1]]==S)ans++;
        cout<<ans;
        return 0;
    }
    ans=0;
    half=r>>1;
    for(int i=0;i<=r;i++)
        ma[i].clear();
    dfs1(0,0,1);
    dfs2(S,k,r);//这真的很Skr
    cout<<ans;
    return 0;
}
```
最长用时只有499ms嘻嘻嘻
# 大力安利洛谷网校

---

## 作者：OldVagrant (赞：3)

## 题意简述
给定 $n$ 个正整数，你有 $k$ 个操作符，每次可以把给定的某一个数 $a_i$ 变为 $a_i!$，对每个数只能使用一次。你要选出一些数，使得其和为 $S$，求在使用不多于 $k$ 个操作符的情况下有多少种方案，两种方案相同当且仅当两种方案中所选的数相同，且使用操作符的对象全部相同。    
$1\le n\le 25,1\le a_i\le 10^9,1\le S\le 10^{16},0\le k\le n$
## Solution
~~第一道独立完成的搜索紫题~~   
首先看搜索部分：   
每个数有三种可能：不选，选了不用操作符，选了且用操作符，爆搜复杂度为 $O(3^n)$,显然无法接受。   
考虑剪枝，阶乘的增长速度是很快的，$19!$ 就已经远远大于 $10^{16}$，所以只可能给小于等于 $18$ 的数使用操作符。但如果 $\forall  i\in [1,n],a_i<19$，那么这个剪枝就是无用的，还要加其他优化。  
通过观察和思考，可以发现在本题中搜到的状态都可以用二元组 $(x,sum)$ 表示（$x$ 是已经使用的操作次数，$sum$ 是选中的数的总和），每个状态都可以通过前半部分和后半部分的状态组合而成，所以可以使用折半搜索，将搜索部分的时间复杂度降为 $O(3^{\lceil\frac{n}{2}\rceil})$。但是状态就要加一维表示这个状态所属的部分，变为三元组 $(x,sum,f)$，其中 $f\in [0,1]$，0 表示属于前半部分，1 表示属于后半部分。在搜索的同时把搜索到的每个状态记录下来，状态的总个数同样是 $O(3^{\lceil\frac{n}{2}\rceil})$ 的，可以用结构体数组存下来。   
然后看计数部分：   
先对所有状态按照 $sum$ 为第一关键字升序排序，$x$ 为第二关键字升序排序。然后从前往后扫，每遇到一个新的 $sum$ 值，就二分找到 $S-sum$ 所在的区间，再用尺取法统计答案，具体的看下面的代码。这里要注意两点，当 $sum=S-sum$ 时要注意特判，否则会重复统计，还有就是方案只能由一个 $f=1$ 的状态和一个 $f=0$  的状态组合而成，统计时要注意去掉不合法的，可以用两个前缀和数组分别存下来前 $i$ 个状态里有多少个 $f=1$ 的状态，有多少个 $f=0$ 的状态，计数时可以用上。 
总时间复杂度 $O(3^{\lceil\frac{n}{2}\rceil}\log3^{\lceil\frac{n}{2}\rceil})$，空间复杂度 $O(3^{\lceil\frac{n}{2}\rceil})$，足以通过。
## Code
二分是用倍增写的，~~很少见但是正确性没问题~~。
```c
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int a[26],lim,n,tot,num,cnt=1,qzh[2][3000001];
ll jc[26],S;
struct sta{
	int k;
	ll sum;
	bool tp;
	bool operator<(sta& b){
		return sum==b.sum?k<b.k:sum<b.sum;
	}
}s[3000001];
void dfs_1(int x,int ma,int k,ll sum){//搜前半部分
	if(x>ma){
		s[++tot]=(sta){num-k,sum,0};
		return;
	}dfs_1(x+1,ma,k,sum);
	if(sum+a[x]<=S) dfs_1(x+1,ma,k,sum+a[x]);
	if(k&&a[x]<=cnt&&sum+jc[a[x]]<=S) dfs_1(x+1,ma,k-1,sum+jc[a[x]]);
}
void dfs_2(int x,int ma,int k,ll sum){//搜后半部分
	if(x>ma){
		s[++tot]=(sta){num-k,sum,1};
		return;
	}dfs_2(x+1,ma,k,sum);
	if(sum+a[x]<=S) dfs_2(x+1,ma,k,sum+a[x]);
	if(k&&a[x]<=cnt&&sum+jc[a[x]]<=S) dfs_2(x+1,ma,k-1,sum+jc[a[x]]);
}
signed main(){
	cin>>n>>num>>S;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1),jc[1]=1;
	while(jc[cnt]<=S) cnt++,jc[cnt]=jc[cnt-1]*cnt;//预处理阶乘数组
	cnt--,s[0].sum=-1,lim=n+1>>1,dfs_1(1,lim,num,0),dfs_2(lim+1,n,num,0),sort(s+1,s+tot+1),s[tot+1].sum=-1;
	int l,r,k=1<<(int)log2(tot),p,q;
	ll left,ans=0;
	for(int i=1;i<=tot;i++) qzh[1][i]=qzh[1][i-1]+s[i].tp,qzh[0][i]=qzh[0][i-1]+(s[i].tp^1);//预处理前缀和数组
	for(int i=1;i<=tot;i++){
		if(s[i].sum!=s[i-1].sum){//每遇到一个新的sum值
			left=S-s[i].sum,p=q=i,l=r=0;
			for(int j=k;j;j>>=1) if(l+j<=tot&&s[l+j].sum<left) l+=j;
			l++;
			for(int j=k;j;j>>=1) if(r+j<=tot&&s[r+j].sum<=left) r+=j;
        //二分出S-sum对应的区间 [l,r]，然后暴力往后扫，找到sum对应的区间[p,q]
			while(s[q].sum==s[p].sum) q++;
			i=--q;
			if(p>r) continue;//当p>r时说明这个sum已经被前面的统计过了
			if(s[p].sum==s[l].sum){//如果[l,r]和[p,q]是同一区间
				while(p<=r){
					while(r>=p&&s[p].k+s[r].k>num) r--;//移动指针直到r的x值与p的x值之和不大于操作次数上限k
					if(r<l) break;//如果r移动到区间外了就break
					while(p<=r&&s[p].k+s[r].k<=num) ans+=qzh[s[p].tp^1][r]-qzh[s[p].tp^1][p],p++;//把[p+1,r]中所有和p的f值不同的状态统计入答案，并移动指针，直到p的x值和r的x值之和大于k
				}
			}else{
				while(p<=q&&l<=r){
					while(r>=l&&s[p].k+s[r].k>num) r--;//同上
					if(r<l) break;
					while(p<=q&&s[p].k+s[r].k<=num) ans+=qzh[s[p].tp^1][r]-qzh[s[p].tp^1][l-1],p++; //把[l,r]中所有和p的f值不同的状态统计入答案，并移动指针，同上
				}
			}
		}
	}cout<<ans;
	return 0;
}
```


---

## 作者：Ofnoname (赞：3)

又是一道不一样的折半搜索。

首先认真读题，一个数只能用一次阶乘的（不然没法做），那么每个数就有三种情况（选，不选，选且阶乘）。并且`S`有$10^{16}$，最多只有$19!$，所以`a[i]<=19`时才会考虑阶乘（为了保险可以写20）。

我们左右边的和要斗出`S`，那么应该左半边应记录能斗出数`sum`的所有情况，如果用`vector`记录，那么`sum`的情况多打$2^{25}$，极易`MLE`。此时我们发现左右两半能斗出`S`的条件是他们用的阶乘魔法数之和小于`K`，那么我们只记录使用了`now`个魔法且和为`sum`的方案数即可。

```cpp
#include <bits/stdc++.h>
#define long long long
using namespace std;

unordered_map <long, long> M[31];

int N, K, mx;
long S, ans, a[31], fac[23] = {1};

void DFS1(int i, long sum, int now)
{
	if (now > K || sum > S) return;
	if (i > N/2)
	{
		M[now][sum]++;
		return;
	}
	DFS1(i+1, sum, now);
	DFS1(i+1, sum + a[i], now);
	if (a[i] < 20) DFS1(i+1, sum + fac[a[i]], now+1);
}

void DFS2(int i, long sum, int now)
{
	if (now > K || sum > S) return;
	if (i > N)
	{
		for (int i = 0; i <= K-now; i++)//右半使用了now个，左半最多使用K-now个 
			ans += M[i][S - sum]; 
		return;
	}
	DFS2(i+1, sum, now);
	DFS2(i+1, sum + a[i], now);
	if (a[i] < 20) DFS2(i+1, sum + fac[a[i]], now+1);
}

int main()
{
	cin >> N >> K >> S, mx = N >> 1;
	for (int i = 1; i <= N; i++)
		cin >> a[i];
	for (int i = 1; i <= 19; i++)
		fac[i] = fac[i-1] * i;
	DFS1(1, 0, 0), DFS2(mx+1, 0, 0);
	cout << ans << endl;
}
```

---

## 作者：wjyyy (赞：2)

   考虑暴力。

   在这个题中，每个数有3种决策，分别是**不选、选上、加阶乘且选上**。根据样例，这个题好像没有考虑加阶乘且不选的情况，在统计答案时少进入一种情况就可以了。

   如果每个数有三种决策，那么完全枚举的话时间复杂度是$3^n$，当$n=26$时是无法通过的。而因为我们要求的是等式左边（若干个数之和）等于等式右边（给定值）。所以我们可以考虑先搜前$\lfloor \frac n2\rfloor$个，再搜后$\lceil \frac n2\rceil$个。把前面搜出来的结果挂到一个hash表上，每次搜到相同的值++。

   hash就是压缩了空间使得数据范围很大的但是个数不是特别大的数被存在一个较小的空间里，每次查询一个数就要去它模一个固定数的余数的那个剩余系中去找有没有相应的数。

   同时，在搜索的过程中，我们如果保证每次数值都会改变（即不搜0的情况），那么到一个dfs阶段，都可以统计一次答案，表示没被搜到的都是0。相当于一棵dfs树上的每个节点都统计了答案，这样减少了冗余0的叶子，优化了常数。

   因为$S≤10^{16}$，而$18! \le 10^{16}\le 19!$，所以添加阶乘的数，只能不超过18。因此long long预处理出18以内的阶乘。对于$O(3^\frac n2)$的复杂度，可行性剪枝就没有必要了（如果搜到的数已经大于S就一定不合法），所以我没有加。

   ```cpp
#include<cstdio>
#include<cstring>
struct node//链表
{
    long long n;
    int v;
    node *nxt;
    node(long long n,int v)
    {
        this->n=n;
        this->v=v;
        nxt=NULL;
    }
    node()
    {
        nxt=NULL;
    }
}head[27][100003],*tail[27][100003];
long long a[30],s,n,k;
long long fct[20],now;
void dfs(int x,int num)//前一半
{

    int flag=0;
    long long tmp=now%100003;
    node *p=&head[num][tmp];
    while(p->nxt)
    {
        p=p->nxt;
        if(p->n==now)
        {
            p->v++;
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        tail[num][tmp]->nxt=new node(now,1);
        tail[num][tmp]=tail[num][tmp]->nxt;
    }
    if(x>n/2)
        return;
    for(int i=x;i<=n/2;i++)
    {
        now+=a[i];
        dfs(i+1,num);//可以加可行性剪枝
        now-=a[i];

        if(a[i]<=18)//判断范围
        {
            now+=fct[a[i]];
            dfs(i+1,num+1);
            now-=fct[a[i]];
        }
    }
}
long long sum=0;
void dfs2(int x,int num)
{
    for(int i=0;i<=k-num;i++)//查表
    {
        node *p=&head[i][((s-now)%100003+100003)%100003];
        while(p->nxt)
        {
            p=p->nxt;
            if(p->n==s-now)
            {
                sum+=p->v;
                break;
            }
        }
    }
    if(x>n)
        return;
    for(int i=x;i<=n;i++)
    {
        now+=a[i];
        dfs2(i+1,num);
        now-=a[i];

        if(a[i]<=18)
        {
            now+=fct[a[i]];
            dfs2(i+1,num+1);
            now-=fct[a[i]];
        }
    }
}
int main()
{
    fct[0]=1;
    for(int i=0;i<100003;i++)
        for(int j=0;j<=26;j++)
            tail[j][i]=&head[j][i];
    for(int i=1;i<=18;i++)
        fct[i]=fct[i-1]*i;
    scanf("%d%d%lld",&n,&k,&s);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n/2;i++)//搜前一半
    {
        now=a[i];
        dfs(i+1,0);
        if(a[i]<=18)
        {
            now=fct[a[i]];
            dfs(i+1,1);
        }
    }
    tail[0][0]->nxt=new node(0,1);//算一种0的情况
    tail[0][0]=tail[0][0]->nxt;
    for(int i=n/2+1;i<=n;i++)
    {
        now=a[i];
        dfs2(i+1,0);
        if(a[i]<=18)
        {
            now=fct[a[i]];
            dfs2(i+1,1);
        }
    }
    now=0;
    dfs2(n+1,0);//同样算一种0的情况
    printf("%I64d\n",sum);
    return 0;
}
```


---

## 作者：COsm0s (赞：1)

## $\mathcal{solution}$

+ 先考虑最简单的爆搜。

  很显然每个数只有三种取法：即**不取**，取其**本身**，和取其**阶乘**。

  复杂度为 $\Theta{(3^{n})}$。对于 $n\leq 26$ 来说，毫无疑问会超时。

+ 我们考虑一种搜索技巧，即 $\text{meet in middle}$。

  $\text{meet in middle}$ 的思想就是将整个需要搜索的序列平均分成两半，将两者分别处理。
  
  在本题中，我们可以先将序列的前 $\lfloor \frac{n}{2} \rfloor$ 爆搜，将所得的所有和的结果放在 Hash 表中（代码中使用 unordered_map），在后 $\lfloor \frac{n}{2} \rfloor$ 爆搜中，进行匹配。
  
+ 可以进行一个小优化。注意到 $18!$ 为 $6402373705728000$，这已经超过了 $S$ 的 $10^{16}$ 限制。

  所以当 $a_i$ 超过 $18$ 的时候，我们可以放弃阶乘这一选项。
  
+ 复杂度 $\Theta{(2 \times3^{\frac{n}{2}})}$，当然实际实现时由于 unordered_map 的不确定性，可能略高。

## $\mathcal{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//不开 long long 见祖宗
const int N = 30;
unordered_map<int, int> mp[N];
int a[N], fac[N], n, k, s, ans;
void dfs(int depth, int p, int sum) {
	if (p > k || sum > s) return ;
	if (depth > n / 2) {
		mp[p][sum] ++;
		return ;
	}
	dfs(depth + 1, p, sum + a[depth]);
	dfs(depth + 1, p, sum);
	if (a[depth] <= 20) dfs(depth + 1, p + 1, sum + fac[a[depth]]);
}
void work(int depth, int p, int sum) {
	if (p > k || sum > s) return ;
	if (depth > n) {
		for (int i = 0; i + p <= k; i ++)
			ans += mp[i][s - sum];
		return ;
	}
	work(depth + 1, p, sum + a[depth]);
	work(depth + 1, p, sum);
	if (a[depth] <= 20) work(depth + 1, p + 1, sum + fac[a[depth]]);
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> k >> s;
	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		cin >> a[i];
	for (int i = 1; i <= 20; i ++)
		fac[i] = fac[i - 1] * i;
	dfs(1, 0, 0);
	work(n / 2 + 1, 0, 0);
	cout << ans << '\n';
	return 0;
}
```


---

## 作者：pokefunc (赞：1)

### 题意

给你一个长为 $n$ 的序列，你有 $k$ 次机会可以把其中的任意一个数变为它的阶乘，问有多少种选数的方案使得选出的这些数之和为 $S$。

$k \le n \le 26$，$S \le 10^{16}$

### 题解

$ \rm meet in middle$ 练手题。

考虑最朴素的爆搜，每个数有 $4$ 种状态（不选，选，不选且阶乘，选且阶乘），$4^{26}$ 绝对会寄。

略加思考，不选还阶乘干嘛。优化为 $3^{26}$，但还是寄了。

但是如果能 $\rm meet in middle$ 一半就只要 $3^{13}$，就能过了。

定义 $f(i,j)$ 为前一半和为 $i$ 阶乘次数为 $j$ 的方案数，$g(i,j)$ 为后一半的方案数，答案为 $\sum_{i \in [0..S],j+p \le k} f(i,j)g(S-i,p)$。

考虑怎么合并答案。

直接分开搜然后暴力合并肯定会寄（相当于没优化）。

考虑把前一半的值存到数组里，但是前一半的值就能爆 `int`，直接数组也寄了。

但是每一半只有 $3^{13}$ 种状态，所以直接请出无敌的 `map`/`unordered_map`。

另外，$20!=2432902008176640000$，因此任何 $\ge 20$ 的数都没有阶乘的必要了（直接就爆了）。

记得开 `long long`。

```cpp
#include<cstdio>
#include<unordered_map>
#define int long long //《邪  教  行  为》
inline int read(){int x(0),op(0);char ch=getchar();while(ch<'0'||ch>'9')op|=(ch==45),ch=getchar();while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();return op?-x:x;}
int fac[25],n,m,S,mid,ans;
int a[36];
using std::unordered_map;
unordered_map<int,int> g[30];
void dfs1(int x,int sum,int r){ //x代表决策到第几个数，sum代表当前部分和，r代表阶乘次数
    if(sum>S||r>m)return;
    if(x==mid+1){g[r][sum]++;return;}
    dfs1(x+1,sum,r);
    dfs1(x+1,sum+a[x],r);
    if(a[x]<20)dfs1(x+1,sum+fac[a[x]],r+1);
}
void dfs2(int x,int sum,int r){
    if(sum>S||r>m)return;
    if(x==n+1){for(int i=0;i<=m-r;++i)ans+=g[i][S-sum];return;}
    dfs2(x+1,sum,r);
    dfs2(x+1,sum+a[x],r);
    if(a[x]<20)dfs2(x+1,sum+fac[a[x]],r+1);
}
signed main(){
    fac[0]=1;
    for(int i=1;i<=20;++i)fac[i]=fac[i-1]*i; //预处理阶乘
    n=read(),m=read(),S=read();
    for(int i=1;i<=n;++i)a[i]=read();
    mid=n>>1;
    dfs1(1,0,0);dfs2(mid+1,0,0);
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：喵仔牛奶 (赞：1)

由于 $n\leq26$，而 $3^{26}$ 会 TLE，我们可以使用一种叫做 $\text{meet in middle}$ 的算法。

将 $[1,n]$ 的数据分为 $[1,k],[k+1,n]\quad(k=\lfloor\frac{n}{2}\rfloor)$ 然后对两部分分别求出答案合并即可。具体来说，就是第一部分搜索 $[1,k]$，将答案存进 ```unordered_map``` 里，第二次搜索直接使用第一次搜索的值。

需要注意的是，由于 $S\leq10^{16}$，而 $20!>10^{16}$，所以如果 $a_i\leq20$ 再阶乘即可，否则一定无解。

细节见注释：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 30;
unordered_map<ll, ll> S[N]; // S[i][j]表示保存[1,k]和使用了i次阶乘且和为j的方案。
ll a[N], fac[N], n, k, s, ans;
void dfs1(int pos, int p, ll sum) {
	if (p > k || sum > s) return;
	if (pos > n / 2) {
		S[p][sum] ++; // 方案加1。
		return;
	}
	dfs1(pos + 1, p, sum + a[pos]);
	dfs1(pos + 1, p, sum);
	if (a[pos] <= 20) dfs1(pos + 1, p + 1, sum + fac[a[pos]]); // a[i]<=20再阶乘。
}
void dfs2(int pos, int p, ll sum) {
	if (p > k || sum > s) return;
	if (pos > n) {
		for (int i = 0; i + p <= k; i ++)
			ans += S[i][s - sum]; // 不需要用完，所以枚举答案。
		return;
	}
	dfs2(pos + 1, p, sum + a[pos]);
	dfs2(pos + 1, p, sum);
	if (a[pos] <= 20) dfs2(pos + 1, p + 1, sum + fac[a[pos]]); // a[i]<=20再阶乘。
}
int main() {
	cin >> n >> k >> s, fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		cin >> a[i];
	for (int i = 1; i <= 20; i ++)
		fac[i] = fac[i - 1] * i; // 预处理阶乘。
	dfs1(1, 0, 0);
	dfs2(n / 2 + 1, 0, 0);
	cout << ans << '\n';
	return 0;
}
```


---

## 作者：Dr_Gilbert (赞：1)

# CF525E Anya and Cubes

【题目大意】

有一长度为 $n$ 的序列 $\{a\}$，可以进行最多 $k$ 次操作，每次操作可以指定 $i$，并将 $a_i$ 变成 $a_i!$。求从操作后的序列中选取若干个数，选出的数总和为 $S$ 的方案数。

$a_i\le10^9,1\le n \le 25, 0\le k \le n,S\le10^{16}$。

首先，看到 $a_i$ 的范围是 $10^9$ 时可能会被吓到，因为这么大的阶乘是不可算的。然而注意到 $S\le 10^{16}$，如果需要通过进行操作达到 $S$，那么操作后的数一定不能大于 $S$，因此通过计算可得 $19!>10^{16}$，所以如果需要进行操作，那么操作的数一定小于 $19$。

这样的话不难想到一个朴素搜索，DFS 时记录一下当前选择的数字和以及操作的执行次数，搜完统计答案即可。每一项都有 $3$ 种状态，时间复杂度 $\mathcal O(3^n)$。

可以发现，搜索过程中，各项之间的状态都是相互独立的，不会对其他状态产生影响，所以不妨进行折半搜索，先搜索前半部分，再搜索后半部分并统计答案。由于操作有数量限制，所以可以使用 $k$ 个 `unordered_map` ，则 $mp[k][x]$ 表示只搜索前一半，使用 $k$ 次操作的情况下，和为 $x$ 的方案数，前一半搜索时直接累加即可。后半部分搜到结尾时，由于并没有要求 $k$ 次操作必须全部执行，所以需要枚举每个可能的操作数量，将方案数累加到答案中。

算法的时间复杂度为 $\mathcal O(3^{\lfloor \frac{n}{2}\rfloor}+k\cdot 3^{\lceil \frac{n}{2}\rceil})$，可以通过本题。代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=30;
unordered_map<int,int> mp[30];
int a[N],fac[N],n,k,s,ans;
void dfs1(int x, int sum, int cnt){
	if (sum>s||cnt>k) return;
	if (x>n/2){
		mp[cnt][sum]++;return;
	} 
	dfs1(x+1,sum+a[x],cnt);dfs1(x+1,sum,cnt);
	if (a[x]<=19&&sum+a[x]<=s) 
		dfs1(x+1,sum+fac[a[x]],cnt+1);
	return;
} 
void dfs2(int x, int sum, int cnt){
	if (sum>s||cnt>k) return;
	if (x>n){
		int tmp=s-sum;
		for (int i=k;i>=cnt;i--){
			ans+=mp[i-cnt][tmp];
		}
		return;
	} 
	dfs2(x+1,sum+a[x],cnt);dfs2(x+1,sum,cnt);
	if (a[x]<=19&&sum+a[x]<=s) 
		dfs2(x+1,sum+fac[a[x]],cnt+1);
	return;
}
signed main(){
	ios::sync_with_stdio(0); 
	cin>>n>>k>>s;fac[0]=1;
	for (int i=1;i<=19;i++){
		fac[i]=fac[i-1]*i;
	}
	for (int i=1;i<=n;i++) cin>>a[i];
	dfs1(1,0,0);dfs2(n/2+1,0,0);
	cout<<ans;return 0;
}
```



---

## 作者：Unnamed114514 (赞：0)

每个数都有三种状态：

- 不选

此时对答案没有贡献。

- 选，但是不加感叹号

此时对答案贡献 $a_i$。

- 选，并且加上感叹号

此时对答案的贡献是 $a_i!$。

$n\le25$，那么我们可以考虑直接进行爆搜，但是，时间复杂度 $O(3^n)$ 直接 T 飞。

此时我们可以发现一个事情：因为我们要求的是和，所以可以用前一半的搜索答案和后一半的搜索答案匹配即可。

那么我们就可以使用折半搜索：把前一半的数字和后一半的数字用 `vector` 存储下来，然后再使用二分。

时间复杂度 $O(3^{\frac{n}{2}}+k^23^{\frac{n}{2}}\log3^{\frac{n}{2}})$。

最后还要注意一点，那就是二分的时候要保证序列有序，所以就是要先对 `vector` 进行排序。

[AC Code](https://codeforces.com/problemset/problem/525/E)

---

## 作者：piggy123 (赞：0)

又是一道完全独立思考的水紫题。

刚开始看到数据范围： $N\leq 25$ 状压？爆搜？

再开始读题，发现是 $01$ 枚举的进化版，选择一个子集，其中每个元素 $a$ 有**一次**（这里翻译不完整）可以变为 $a!$ （$a$ 的阶乘）的机会，求总和为 $S$ 的方案数。也就是说，这一题每种元素有三种状态：选，不选，选阶乘。

于是如果暴力枚举的话，复杂度变为 $3^n\approx10^{11}$ ，显然会爆炸。

所以考虑折半搜索，先搜索 $[1,\frac{n}{2}]$ 区间，用 unordered_map 保存所有状态使用的阶乘数量与和，再搜索 $[\frac{n}{2}+1,n]$ 区间，暴力枚举还可以使用的阶乘数量，统计答案即可。

这里还有一个小问题，即阶乘会爆 ll 的问题，我们发现 $19!\approx10^{16}$ ，而 $1\leq S\leq 10^{16}$ ，即 $19$ 以上的数都不用考虑阶乘，所以预处理到 $19$ 即可。

AC Code：
```
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll a[55],fc[30],ans=0,n,m,k;
unordered_map<ll,ll> lft[55];

void dfs(ll now,ll sm,ll use){
	if (now==n/2+1){
		lft[use][sm]++;
		return;
	}
	dfs(now+1,sm,use);
	if (sm+a[now]>m)return;
	dfs(now+1,sm+a[now],use);
	if (a[now]>=19||sm+fc[a[now]]>m)return; // 剪枝 
	dfs(now+1,sm+fc[a[now]],use+1);
}

void dfs2(ll now,ll sm,ll use){
	if (now==n+1){
		for (register ll i=0;i<=k-use;i++){
			ans+=lft[i][m-sm];
		}
		return;
	}
	dfs2(now+1,sm,use);
	if (sm+a[now]>m)return;
	dfs2(now+1,sm+a[now],use);
	if (a[now]>=19||sm+fc[a[now]]>m)return; // 剪枝 
	dfs2(now+1,sm+fc[a[now]],use+1);
}

int main(){
	cin >> n >> k >> m;
	for (register ll i=1;i<=n;i++){
		cin >> a[i];
	}
	fc[0]=1;
	for (register ll i=1;i<=19;i++)fc[i]=fc[i-1]*i;
	dfs(1,0,0);
	dfs2(n/2+1,0,0);
	cout << ans;
	return 0;
}

```


---

## 作者：demon_yao (赞：0)

## 思路
显然，对于每个数，我们都有三种选择策略：选，不选，使用阶乘。如果考虑暴力dfs的话，显然会有许多无用的状态，这大大的浪费了我们的时间。所以，我们想到了神马呢？

### MEET-IN-MIDDLE ！

也就是所谓的折半搜索，这样可以剪枝大量的无用状态。
设左边状态的和为$tmp$,那么右边的和应该为$s-tmp$.这样我们就可以暴力枚举左边的和,并找到右边与之相对应的和，记为一种合法的方案。所有方案相加就是我们最终的答案啦qwq。

### 几个注意点
1.因为$s$最大只有$10^{16}$,而$20!$就已经超过了$s$的最大值，所以只有对于小于$20$的数我们才考虑选择阶乘。

2.STL大法好！在这里我们使用了unorderded_map，可以大大的节省我们的查询时间。

3.注意要预处理阶乘，这样可以节省大量时间。

4.$m[k][tmp]$表示目前已经使用了$k$个$!$,且和为$tmp$的方案数。
```cpp



#include<bits/stdc++.h>
using namespace std;
int n,k,mid;
int a[66];
long long jc[66];long long ans,s;
unordered_map<long long ,long long> m[33];
void dfs(int now,int end,long long sum,int used,int flag)
{
	if(used>k) return;
	if(flag==0){
		if(now>end){
			m[used][sum]++;
			return;
		}
	}
	else{
		if(sum>s) return;
		if(now>end){
			for(int i=0;i<=k-used;i++) ans+=m[i][s-sum];
			return ;
		}	
	}
	dfs(now+1,end,sum,used,flag);
	dfs(now+1,end,sum+a[now],used,flag);
	if(a[now]<=20) dfs(now+1,end,sum+jc[a[now]],used+1,flag);
}
int main()
{
	cin>>n>>k>>s;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	jc[1]=1;
	for(int i=2;i<=20;i++) jc[i]=jc[i-1]*i;
	mid=n>>1;
	dfs(1,mid,0,0,0);
	dfs(mid+1,n,0,0,1);
	cout<<ans;
	return 0;
}
```
完结撒花 qwq !!

---

## 作者：Nephren_Sakura (赞：0)

题目传送门：[link](https://www.luogu.com.cn/problem/CF525E)。

这题翻译有一个坑点，就是一个数只能用一次阶乘，[这个帖子](https://www.luogu.com.cn/discuss/391599)说明了。

首先看到 $n \le 26$，考虑暴搜。

对于这题，每一个点有三种状态：

1. 不选。

2. 选。

3. 选并且阶乘。

如果直接搜是 $O(3^n)$ 的，显然炸掉。

对于这种搜索题但是时间炸掉，除了玄学剪枝以外有两种优化方法：

1. 迭代加深搜索。

2. 折半搜索。

对于本题，考虑直接折半搜索。

设 $mp[i][j]$ 表示用恰好 $j$ 个阶乘可以组成 $i$ 的方案数，先把前一半的 $mp$ 暴搜出来，然后后一半再搜一次，只是后一半这一次直接统计答案。

时间复杂度是 $O(3^{\frac{n}{2}})$ 的。

具体的实现看代码吧：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9'){
		if (ch=='-')
			f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-48;
		ch=getchar();
	}
	return x*f;
}
inline void put(int x)
{
    if (x > 9) put(x / 10);
    putchar(x % 10 + 48);
}//远古时期的代码，快读快输我现在已经不用了
int n=read(),k=read(),s=read(),ans,a[1000005];
unordered_map<int,int> mp[1000005];
int hp(int x){
	int res=1ll;
	for(int i=2ll; i<=x; i++)
		res*=i;
	return res;
}//求 x!，也可以预处理
void dfs(int nw_cur,int nw_sum,int nw_k){
	if(nw_k>k||nw_sum>s)
		return;
	if(nw_cur>n/2){
//		if(nw_k<=k&&nw_sum==s)
//			ans++;
		mp[nw_k][nw_sum]++;
		return;//统计 mp
	}
	dfs(nw_cur+1,nw_sum,nw_k);
	dfs(nw_cur+1,nw_sum+a[nw_cur],nw_k);
	if(a[nw_cur]<=19)
		dfs(nw_cur+1,nw_sum+hp(a[nw_cur]),nw_k+1);
}
void dfs2(int nw_cur,int nw_sum,int nw_k){
	if(nw_k>k||nw_sum>s)
		return;
	if(nw_cur>n){
//		if(nw_k<=k&&nw_sum==s)
//			ans++;
		for(int i=0; i<=k-nw_k; i++)
			ans+=mp[i][s-nw_sum];
		return;//统计答案
	}
	dfs2(nw_cur+1,nw_sum,nw_k);
	dfs2(nw_cur+1,nw_sum+a[nw_cur],nw_k);
	if(a[nw_cur]<=19)
		dfs2(nw_cur+1,nw_sum+hp(a[nw_cur]),nw_k+1);
}
signed main(){
	for(int i=1; i<=n; i++)
		a[i]=read();
		// 
	dfs(1,0,0);//
	dfs2(n/2+1,0,0);
	cout<<ans;
	return 0;
}
```

---


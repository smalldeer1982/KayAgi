# Watch the Videos

## 题目描述

Monocarp wants to watch $ n $ videos. Each video is only one minute long, but its size may be arbitrary. The $ i $ -th video has the size $ a_i $ megabytes. All videos are published on the Internet. A video should be downloaded before it can be watched. Monocarp has poor Internet connection — it takes exactly $ 1 $ minute to download $ 1 $ megabyte of data, so it will require $ a_i $ minutes to download the $ i $ -th video.

Monocarp's computer has a hard disk of $ m $ megabytes. The disk is used to store the downloaded videos. Once Monocarp starts the download of a video of size $ s $ , the $ s $ megabytes are immediately reserved on a hard disk. If there are less than $ s $ megabytes left, the download cannot be started until the required space is freed. Each single video can be stored on the hard disk, since $ a_i \le m $ for all $ i $ . Once the download is started, it cannot be interrupted. It is not allowed to run two or more downloads in parallel.

Once a video is fully downloaded to the hard disk, Monocarp can watch it. Watching each video takes exactly $ 1 $ minute and does not occupy the Internet connection, so Monocarp can start downloading another video while watching the current one.

When Monocarp finishes watching a video, he doesn't need it on the hard disk anymore, so he can delete the video, instantly freeing the space it occupied on a hard disk. Deleting a video takes negligible time.

Monocarp wants to watch all $ n $ videos as quickly as possible. The order of watching does not matter, since Monocarp needs to watch all of them anyway. Please calculate the minimum possible time required for that.

## 样例 #1

### 输入

```
5 6
1 2 3 4 5```

### 输出

```
16```

## 样例 #2

### 输入

```
5 5
1 2 3 4 5```

### 输出

```
17```

## 样例 #3

### 输入

```
4 3
1 3 2 3```

### 输出

```
12```

# 题解

## 作者：Alex_Wei (赞：11)

每部电影的下载时间肯定会算满，唯一可以节省时间的地方在于同时观看和下载电影。我们先将观看电影的时间也算上，即令初始答案为 $n + \sum a_i$。

考虑观看顺序 $b_1, b_2, \cdots, b_n$。如果 $a_{b_i} + a_{b_{i + 1}}\leq m$，则代价减少 $1$。我们希望找到排列 $b$ 使得这样的 $i$ 尽量多。

将 $a$ 从小到大排序，假设有 $k$ 对这样的 $i$，选择最小的 $k + 1$ 个数构造 $k + 1, 1, k, 2, \cdots$ 是最优的，它保证了相邻两个数之和的 $\max$ 最小。二分检查即可。

简化二分过程，可以双指针做到除排序外 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1765/submission/185238200)。

---

## 作者：hanjinghao (赞：2)

题意：

有 $ n $ 个视频，第 $ i $ 个视频的大小为 $ a_i $。你有一块容量为 $ m $ 的硬盘。每一个视频必须先花费 $ a_i $ 的时间下载下来，保存在硬盘里（占据硬盘 $ a_i $ 的空间），才能观看。观看一个视频花费的时间为 $ 1 $。

此外，还有几个注意点：

一、任何时候，硬盘被占据的空间必须小于等于 $ m $。

二、一个视频在看完之后可以立刻删除，把占据的 $ a_i $ 的空间释放掉。删除这件事情不需要花费时间。

三、不能同时下载超过一个视频，也不能同时观看超过一个视频。但是可以在下载某个视频的同时，观看其他已经保存在硬盘里的视频。

你可以按任何顺序下载和观看这 $ n $ 个视频，问看完所有视频，最少需要花费多长时间。

$ 1 $ ${\leq}$ $ n $ ${\leq}$ $ 2 $ $\times$ $ 10 ^ 5 $；$ 1 $ ${\leq}$ $ m $ ${\leq}$ $ 10 ^ 9 $；$ 1 $ ${\leq}$ $ a_i $ ${\leq}$ $ m $

=======================================================

无论按什么顺序，每个视频的下载时间是固定的。会变化的只有观看所用的时间（如果一个视频是在另一个视频的下载过程中观看的，那么这 $ 1 $ 单位时间就不需要计入答案，否则需要计入答案）。

一定有一种最优方案，满足在任意时刻，硬盘里不超过两个视频。证明：假设在硬盘里本来有一个视频，新下载一个视频的时候可以把本来的这个视频观看掉，然后立刻删除（删除视频一定不会使答案变劣）。也就是说，只要硬盘里有两个视频，一定有一个视频可以在另一个视频下载的时候被观看掉。

我们可以先将视频从小到大排序。用三个变量 $ l,r,cur $ 表示 $ 1 $ 到 $ l - 1 $、$ r + 1 $ 到 $ n $ 这些视频已经下载完，目前考虑到第 $ l $ 个和第 $ r $ 个视频，硬盘里存有一个大小为 $ cur $ 的视频。分类讨论如下：

一、如果第 $ r $ 个视频能装得下，就把第 $ r $ 个视频下载下来，同时把原本存在硬盘里的视频观看掉并删除。这一步需要花费 $ a_r $ 的时间。此时，硬盘里就存有第 $ r $ 个视频。

二、如果第 $ r $ 个视频装不下，而第 $ l $ 个视频能装得下，就把第 $ l $ 个视频下载下来，同时把原本存在硬盘里的视频观看掉并删除。这一步需要花费 $ a_l $ 的时间。此时，硬盘里就存有第 $ l $ 个视频。

三、如果 $ l, r $ 两个视频都装不下，就只能先花费 $ 1 $ 单位时间把原本存在硬盘里的视频观看掉并删除，然后再把第 $ r $ 个视频下载下来。

最后硬盘里会留有一个视频，再花费 $ 1 $ 单位时间把这个视频观看掉即可。

详见代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, m, a[N];
long long ans;

int main()
{
	read(n);
	read(m);
	for (register int i = 1; i <= n; ++i)
		read(a[i]);
	if (n == 1)
	{
		writeln(a[1] + 1);
		return 0;
	}
	sort(a + 1, a + n + 1);
	int l = 1, r = n, cur = 0;
	while (1)
	{
		if (l > r) break;
		if (cur)
		{
			if (cur + a[r] <= m)
			{
				ans += a[r];
				cur = a[r];
				--r;
				continue;
			}
			if (cur + a[l] <= m)
			{
				ans += a[l];
				cur = a[l];
				++l;
				continue;
			}
			++ans;
			ans += a[r];
			cur = a[r];
			--r;
			continue;
		}
		ans += a[r];
		cur = a[r];
		--r;
	}
	if (cur) ++ans;
	writeln(ans);
	return 0;
}

```

---

## 作者：jiayixuan1205 (赞：1)

## 题解：CF1765D Watch the Videos
### 题意分析
我们可以发现，减少总时间的方式是在观看前一部电影时就开始下载下一部电影。因此若每两部电影间拥有重叠部分，就可以使得总时间减少 $1$。因此题目就转化为了构造一种序列的排序方式使得相邻两项之间尽可能地有重叠，答案即为 $\sum\limits_{i=1}^n a_i$ 的值减去总的重叠数。

那么如何统计最多的重叠数量呢？容易想到将数组排好序后从前往后一大一小一大一小摆动着排列，优先匹配大的。但是看一眼样例三，可以发现，如果直接双指针扫描过去，如果一大一小无法成功匹配，那么会直接把两个都用加一的代价直接消耗掉。但是事实上更优秀的方案是将两个小的重叠起来。

那么可以怎么办呢？

让我们来稍微改装一下这个双指针算法。我们考虑，首先在可以匹配成功的时候，肯定是一大一小交叉匹配最优。但是在不可以匹配的时候，这种一大一小的交叉匹配相当于是浪费了一个匹配不上的小的。于是我们可以在不能匹配成功的时候直接把这个大的扔到后面去，也就是直接跳过这个大数，用下一个更小的大数去试图匹配。

因为越向中间挪大数越大小数越小，可以证明如果这个大数与当前小数无法匹配，它肯定不能与其他的产生匹配，于是当前策略最优。
### 复杂度
双指针遍历整个序列，时间复杂度 $O(n)$。
### 代码展示
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e5+10;
int n,m;
int a[N];
int ans=0,tot=0;
int last=0;

inline bool cmp(int x,int y)
{
    return x>y;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++) ans+=a[i]+1;
    int l=1,r=n;
    while(l<r)
    {
        if(last==0)
        {
            if(a[l]+a[r]<=m)
            {
                l++;
                tot++;
                last=1;
            }
            else
            {
                l++;
            }
        }
        else
        {
            if(a[l]+a[r]<=m) 
            {
                r--;
                tot++;
                last=0;
            }
            else
            {
                l++;
            }
        }
    }
    cout<<ans-tot<<'\n';
    return 0;
}
```

---

## 作者：ybc2026lhy (赞：1)

首先将所有的 $a_i$ 排序。由于思考题目的时间是无法节省的，我们的主要目标为尽量多的在思考题目时放弃题。从 $a_i$ 的最大值开始考虑，若此时 $a_{max}+a_{min}>m$，则在思考完 $a_{max}$ 后，必须花费 1 的时间放弃该题，再去思考其他问题，否则，思考完 $a_{max}$ 后立刻思考 $a_{min}$，而之后的 $a_{min}$
由于可以满足最大值，所以也可以满足任何元素。

可以发现两种情况分别对应 $n-1$
与 $n-2$ 两种子问题，可以双指针处理。

---

## 作者：qwq___qaq (赞：0)

答案至少为 $\sum a$。

所以要最小化 $+1$ 的数量。

这个时候问题等价于将 $a$ 重排，然后求 $a_i+a_{i-1}\le m$ 的数量。

然后你先给 $a$ 排序，维护一个双端队列。

如果没有匹配的肯定就直接删掉。

考虑经典套路：大的匹配小的。

因此，如果有匹配的话，你就找那个最小的来匹配就可以了，因为你当前配对的是最大的。

---

## 作者：aeiouaoeiu (赞：0)

我们通过连边 $u\rightarrow v$ 表示在观看第 $u$ 个视频的同时下载第 $v$ 个视频，那么这 $n$ 个视频就可以变为 $k$ 条单向的链，所需时间为 $s+k$，其中 $s=\sum a_i$。

可以发现如果有边 $u\rightarrow v$，那么必须满足 $a_u+a_v\le m$，所以我们可以从目前仍没有连边的任意一个点开始不断地找可连边的点，然后把连上边的点删除，最后统计这些可连边的点，即为 $k$，可以使用 multiset 实现可连边点的查找。
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=200005;
const ll inf=0x3f;
ll n,m,a[maxn],ans;
multiset<ll> s;
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll T=1;
	//cin>>T;
	for(int tcs=1;tcs<=T;tcs++){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			s.insert(a[i]),ans+=a[i];
		}
		ll u,v;
		for(;!s.empty();){
			ans++,u=*s.rbegin(),s.erase(prev(s.end()));
			for(;!s.empty();){
				if(s.upper_bound(m-u)==s.begin()) break;
				v=*prev(s.upper_bound(m-u)); //v 为可连边的点
				s.erase(prev(s.upper_bound(m-u)));
				u=v;
			}
		}
		cout<<ans;
	}
	return 0;
}
```

---


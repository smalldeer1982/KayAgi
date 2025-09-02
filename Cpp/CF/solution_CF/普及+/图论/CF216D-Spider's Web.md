# Spider's Web

## 题目描述

这个蛛网有 $n$ 条主线，将整张蛛网分成 $n$ 个区域，我们按照顺时针的顺序从 $1$ 到 $n$ 编号，其中 $n$ 号区域与 $1$ 号区域相邻。

对于第 $i$ 个区域，两条主线之间有 $k_{i}$ 条蛛丝相连，蛛丝两端到中心的距离相等，第 $j$ 条蛛丝两端到中心的距离为 $p_{i,j}$。这些蛛丝将该区域分成 $k_{i}$ $-$ $1$ 个扇区，如果某个扇区两侧的主线上蛛丝端点的个数不相等，则这个扇区是不稳定的。

现在给出整张蜘蛛网的结构，计算有多少个不稳定的扇区。

## 样例 #1

### 输入

```
7
3 1 6 7
4 3 5 2 9
2 8 1
4 3 7 6 4
3 2 5 9
3 6 3 8
3 4 2 9
```

### 输出

```
6```

# 题解

## 作者：Wf_yjqd (赞：1)

一眼二分板子。

其实可以双指针，但对整体复杂度也没啥影响。。

------------

考虑对于每个扇片，二分然后容斥求出左右两个主线上有多少个蛛丝的端点在扇片距中心点的区间内。

比较两边是否相同即可。

复杂度 $\operatorname{O}(\sum k\times\log{\sum k})$。

------------

板子没啥好说的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int lyh=1e3+84;
int n,k,x,ans;
vector<int> adl[lyh],adr[lyh];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&k);
        for(int j=1;j<=k;j++){
            scanf("%d",&x);
            adl[i].push_back(x);
            adr[i%n+1].push_back(x);
        }
    }
    for(int i=1;i<=n;i++){
        sort(adl[i].begin(),adl[i].end());
        sort(adr[i].begin(),adr[i].end());
    }
    for(int i=1;i<=n;i++)
        for(auto j=adl[i].begin();j!=prev(adl[i].end());j++)
            if(lower_bound(adr[i].begin(),adr[i].end(),*next(j))-lower_bound(adr[i].begin(),adr[i].end(),*j)!=lower_bound(adl[i%n+1].begin(),adl[i%n+1].end(),*next(j))-lower_bound(adl[i%n+1].begin(),adl[i%n+1].end(),*j))
                ans++;
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：Leaper_lyc (赞：0)

~~这题有绿？难度虚高？~~

很显然的一个问题：求出有多少个扇环左边点数和右边点数不相等。

类似差分思想，二分出左边**小于等于**上届的点数，以及二分出**小于**下届的点数，二者相减就得到了上下界之间的点数。

右边同理。

可以使用 STL 里的 `lower_bound()` 和 `upper_bound()` 使代码更简便。

注意不保证输入的数据递增。

区间是环状的，注意边界。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, ans;
vector <int> a[N];
signed main() {
	cin >> n;
	for (int i = 1, m; i <= n; i++) {
		cin >> m;
		for (int j = 1, k; j <= m; j++) {
			cin >> k;
			a[i].push_back(k);
		}
		sort(a[i].begin(), a[i].end());
	}
	for (auto i : a[n]) a[0].push_back(i);
	for (auto i : a[1]) a[n + 1].push_back(i);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < (int)a[i].size(); j++) {
			int x1 = lower_bound(a[i - 1].begin(), a[i - 1].end(), a[i][j]) - a[i - 1].begin();
            int y1 = upper_bound(a[i - 1].begin(), a[i - 1].end(), a[i][j - 1]) - a[i - 1].begin() - 1;
			int x2 = lower_bound(a[i + 1].begin(), a[i + 1].end(), a[i][j]) - a[i + 1].begin();
            int y2 = upper_bound(a[i + 1].begin(), a[i + 1].end(), a[i][j - 1]) - a[i + 1].begin() - 1;
			if (x1 - y1 != x2 - y2) ans++;
		}
	}
	cout << ans;
}
```

---

## 作者：_HMZ_ (赞：0)

## 解题思路：

我们先开一个 vector $e_i$，代表第 $i$ 个大块端点的值。

然后对于每一个区域，二分它左边有几个端点在区域内，右边同理。

因为数据说不保证有序，所以要先排个序。

这里介绍一个 STL 神器，lower_bound 和 upper_bound。

手写二分容易炸，这题和同学比手速的时候我的二分是炸了还写的慢。

lower_bound 用法大概是这样的，`lower_bound(a+1,a+1+n,b)`。

其中 $a$ 是二分的数组，$n$ 是数组长度，写法类似 sort。

最后的 $b$ 是你要二分的数。注意这个东西返回一个指针。

那么 upper 和 lower 的区别是什么呢？

很简单，lower 返回第一个大于等于的位置，upper 返回第一个大于的位置。

又怎么统计答案呢？

这里可以利用前缀和的思想，一个区域在 $r$ 以内的个数减去在 $l$ 以内的个数就是 $l$ 到 $r$ 的个数。

## AC代码：
```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n,ans;
vector<int> e[100005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int u;
		cin>>u;
		for(int j=1;j<=u;j++)
		{
			int v;
			cin>>v;
			e[i].push_back(v);
		}
		sort(e[i].begin(),e[i].end());//注意二分数组一定要有序。
	}
	for(int i=1;i<=n;i++)
	{
		int len=e[i].size(),beg=(i==1?n:i-1),nxt=(i==n?1:i+1);
		for(int j=1;j<len;j++)
		{
			int t1=(lower_bound(e[beg].begin(),e[beg].end(),e[i][j])-e[beg].begin())-(upper_bound(e[beg].begin(),e[beg].end(),e[i][j-1])-e[beg].begin()-1)+1;
        		//t1就是左边的端点。
			int t2=(lower_bound(e[nxt].begin(),e[nxt].end(),e[i][j])-e[nxt].begin())-(upper_bound(e[nxt].begin(),e[nxt].end(),e[i][j-1])-e[nxt].begin()-1)+1;
            		//t2就是右边的。
			if(t1!=t2)
				++ans;//统计答案
		}
	}
	cout<<ans;
	return 0;
}
```


---


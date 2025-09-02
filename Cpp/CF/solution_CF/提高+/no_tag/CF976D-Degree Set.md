# Degree Set

## 题目描述

给你一个长度为  $n$  的正整数序列  $d_1, d_2, \cdots, d_n$ （ $d_1 < d_2 < \cdots < d_n$ ）。要求你构造一个满足以下条件的无向图：

1. 有恰好  $d_n + 1$  个点；
2. 没有自环；
3. 没有重边；
4. 总边数不超过  $10^6$ ；
5. 它的度数集合等于  $d$ 。

点从  $1$  标号至  $d_n + 1$ 。

图的度数序列是一个长度与图的点数相同的数组  $a$ ，其中  $a_i$  是第  $i$  个顶点的度数（与其相邻的顶点数）。

图的度数集合是度数序列**排序后去重**的结果。

保证有解，要求输出符合条件的图。

## 样例 #1

### 输入

```
3
2 3 4
```

### 输出

```
8
3 1
4 2
4 5
2 5
5 1
3 2
2 1
5 3
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
4
1 2
1 3
1 4
2 3
```

# 题解

## 作者：宇道人 (赞：5)

[My blog](https://taoist-yu.github.io/2019/01/20/Codeforces-976D%20Degree%20Set/)

# 两个结论
1. 对于一个顶点数为n的完全图，度数集合为{n-1}
~~~
    证明：
    n完全图中每个顶点都与另外n-1个点有连边
    即，n完全图中有n个度数为n-1的顶点
    度数集合为{n-1}
~~~
2. 对于一个顶点数为n个顶点的图，取k∈[1,n]，令[1,k]中所有顶点与图中所有顶点连边，则[1,k]中所有顶点度数为n-1，[k+1,n]中所有顶点度数为k。
~~~
    证明：
    1.对于顶点v∈[1,k]
    v与图中除自身外所有n-1个顶点都有连边，度数为n-1.
    2.对于顶点v∈[k+1,n]
    v与[1,k]中所有顶点连边，度数为k
    度数集合为{k,n-1}
~~~
其中结论1是结论2的特例（取k = n）

# 题目分析
&emsp;&emsp;
我们现在d[n]+1个顶点，需要将其构造成一个度数集为{d[1],d[2]....d[n]的无向图}
<br>&emsp;&emsp;
考虑结论2，我们令[ 1，d[1] ]中所有顶点与图上所有顶点连边，则可得[ 1, d[1] ]中所有顶点度数为d[n]，剩下所有顶点度数为d[1]。我们将图中顶点划分为3个部分
~~~
1. [ 1, d[1] ]中所有顶点度数为d[n]。
2. [ d[1]+1, d[n-1]+1 ]中所有顶点度数为d[1]。
3. [ d[n-1]+2, d[n] ]中所有顶点度数为d[1]。
~~~
&emsp;&emsp;此时我们的度数集合为{d[1], d[n]}, 接下来只需要在第2部分中连边，使得度数集合中出现d[2],d[3]...d[n-1]即可。
<br>&emsp;&emsp;
问题转化为：构造一个顶点数为d[n-1]-d[1]+1的无向图，使其度数集为{d[2]-d[1]，d[3]-d[1]，....d[n-1]-d[1]},这是一个与原问题类似的规模更小的问题，可以重复上述操作。

# 核心代码
我们每次都将1~d[1]中顶点与图上所有顶点连边，然后忽略1~d[1]与d[n-1]+2~d[n]+1,在区间d[2]~d[n-1]+1上重复同样的操作。
~~~cpp
    //当前的最左端区间与最右端区间
    int left = 1, right = n;
    //记录边数
    int cot = 0;
    while (left <= right)
    {
        for (int i = d[left - 1] + 1; i <= d[left]; i++)
            for (int j = i+1; j <= d[right] + 1; j++)
            {
                ans.push_back(edge(i,j));
                cot++;
            }
        left++;
        right--;
    }
~~~

# 完整代码
~~~cpp
#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <list>
#include <string.h>
using namespace std;

int d[310] = {};

struct edge
{
    int u;
    int v;
    edge(int u, int v)
    {
        this->u = u;
        this->v = v;
    }
};
list<edge> ans;

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> d[i];

    int l = 1, r = n;
    int cot = 0;
    while (l <= r)
    {
        for (int i = d[l - 1] + 1; i <= d[l]; i++)
            for (int j = i+1; j <= d[r] + 1; j++)
            {
                ans.push_back(edge(i,j));
                cot++;
            }
        l++;
        r--;
    }

    cout<<cot;
    for(edge a : ans)
    {
        cout<<endl<<a.u<<' '<<a.v;
    }
    return 0;
}
~~~


---

## 作者：TernaryTree (赞：4)

这个题真没 $2500$ 吧……

考虑如何构造度数集合为 $\{x,y\}$ 的图，$x<y$。

在 $y+1$ 个点里面选 $x$ 个点，每个点向其他 $y$ 个点连边，则选中的 $x$ 个点度数为 $y$，没选中的点度数为 $x$。

然后我们就解决掉了一个最大值和一个最小值，并且让所有需要的度数都减去了 $x$。

双指针做就行了。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e3 + 10;
typedef pair<int, int> pii;

int n, tot = 1;
int d[maxn];
pii e[maxn * maxn];
int cnt;

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> d[i];
	int l = 1, r = n;
	while (l <= r) {
		int c = d[l], k = d[r];
		for (int i = tot; i <= tot + c - 1; i++) {
			for (int j = i + 1; j <= tot + k; j++) {
				e[++cnt] = {i, j};
			}
		}
		tot += c;
		for (int i = l + 1; i <= r - 1; i++) d[i] -= c;
		l++, r--;
	}
	cout << cnt << endl;
	for (int i = 1; i <= cnt; i++) cout << e[i].first << " " << e[i].second << endl;
	return 0;
}

```

---

## 作者：skyskyCCC (赞：0)

## 前言。
第一道一次通过的 $2500$ 但是感觉码量到不了 $2500$ 的样子。显然根据题目要求，我们需要构造出一个图。
## 分析。
直接按照题目的意思来。先建点，然后考虑度数，再连边。如果我们对于前 $d_1$ 个点向所有其它的点连边，则现在有 $d_1$ 个点的度数为 $d_n$ 同时其它点的度数就是 $d_1$。那么此时我们对于这些点，即度数为 $d_n$ 和 $d_1$ 的点就可以不进行进一步的操作。那么此时我们观察整个我们连成的图，因为没有自环和重边，所以我们对于度数为 $d_n$ 的 $d_n-d_{n-1}$ 个点也不能再操作了。所以此时我们只要构造出 $d_2-d_1,d_3-d_1,\dots,d_{n-1}-d_1$ 的问题了。直接进行暴力配对即可。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int n,d[1000005];
int l=1,r;
int sizee;
struct node{
    int x,y;
}a[1000005];
int main(){
	cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>d[i];
	}
	r=d[n]+1;
    for(int i=1,j=n;i<=(n>>1);i++,j--){
        for(int k=1;k<=d[i];k++){
        	for (int z=l;z<r-k+1;z++){
        		a[++sizee].x=r-k+1;
				a[sizee].y=z;
			}
		}
        l+=d[j]-d[j-1];
		r-=d[i];
        for(int k=i+1;k<j;k++){
        	d[k]-=d[i];
		}
    }
    if(n&1){
        for(int i=l;i<=r;i++){
            for(int j=l;j<i;j++){
			    a[++sizee].x=i;
				a[sizee].y=j;
			}
        }
    }
    cout<<sizee<<"\n";
    for(int i=1;i<=sizee;i++){
    	cout<<a[i].x<<" "<<a[i].y<<"\n";
	}
    return 0;
}
```
## 后记。
虽然说 $n$ 很小，但是 $20$ 个数据点我是没想到。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Tachibana_Kimika (赞：0)

### 题目解析
本题给定 $n$ 个数 $d_1\dots d_n$，要求我们构造一张无向图满足有 $d_n+1$ 个点，无自环无重边，且每个点的度数集合为 $d$。

因为要求有的点度数为 $d_n$，那么这些点一定和其他点都有边，假设有 $k$ 个点度数为 $d_n$，那么其他 $d_n+1-k$ 个点度数均为 $k$。我们发现如果这个 $k$ 为 $d$ 数组里的其他数，我们就可以同时解决两种度数，我们暂且将 $k$ 设为 $d_1$。

经过第一次操作后，我们可以直接将那 $d_1$ 个点全部忽略，因为他们已经满了，不会再连边了，于是相当于把 $d$ 数组中的第 $n$ 项忽略，并且因为每个点度数均为 $d_1$，所以相当于 $d$ 数组每个数都减去了 $d_1$。

现在 $d$ 数组最大的数是 $d_{n-1}-d_1$，因为只有点数为 $d_{n-1}-d_1+1$ 时我们才能重复上面的操作，选取几个点和其他所有点都连边，所以我们再次忽略 $d_n+1-d_1-(d_{n-1}-d_1+1)$ 个点，也就是 $d_n-d_{n-1}$ 个点，换句话说，就是只考虑这 $d_n+1-d_1$ 个点中的 $d_{n-1}-d_1+1$ 个。因为 $d_{n-1}\lt d_n$，所以忽略的点数时钟大于 1，也就是一定会有一个点被忽略，注意到只有被忽略的点度数才为 $d_1$。

根据以上操作，我们可以把每个 $d_i$ 和 $d_{n-i+1}$ 配对，循环加边即可。

由此，我们可以写出代码。代码微压行。
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int d[N];
int ans[N][2],cnt;

int main(){
	int n; cin>>n; 
	for(int i=1;i<=n;i++) cin>>d[i];
	for(int i=1;n-i+1>=i;i++)//枚举i进行配对
		for(int j=d[i-1]+1;j<=d[i];j++)//所有要连上其他所有点的点
			for(int k=j+1;k<=d[n-i+1]+1;k++)//枚举他们要连上什么点
				ans[++cnt][0]=j,ans[cnt][1]=k;//加边
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
		cout<<ans[i][0]<<" "<<ans[i][1]<<endl;
}

```

---


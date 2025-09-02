# Destroying Bridges

## 题目描述

There are $ n $ islands, numbered $ 1, 2, \ldots, n $ . Initially, every pair of islands is connected by a bridge. Hence, there are a total of $ \frac{n (n - 1)}{2} $ bridges.

Everule lives on island $ 1 $ and enjoys visiting the other islands using bridges. Dominater has the power to destroy at most $ k $ bridges to minimize the number of islands that Everule can reach using (possibly multiple) bridges.

Find the minimum number of islands (including island $ 1 $ ) that Everule can visit if Dominater destroys bridges optimally.

## 说明/提示

In the first test case, since no bridges can be destroyed, all the islands will be reachable.

In the second test case, you can destroy the bridge between islands $ 1 $ and $ 2 $ . Everule will not be able to visit island $ 2 $ but can still visit island $ 1 $ . Therefore, the total number of islands that Everule can visit is $ 1 $ .

In the third test case, Everule always has a way of reaching all islands despite what Dominater does. For example, if Dominater destroyed the bridge between islands $ 1 $ and $ 2 $ , Everule can still visit island $ 2 $ by traveling by $ 1 \to 3 \to 2 $ as the bridges between $ 1 $ and $ 3 $ , and between $ 3 $ and $ 2 $ are not destroyed.

In the fourth test case, you can destroy all bridges since $ k = \frac{n \cdot (n - 1)}{2} $ . Everule will be only able to visit $ 1 $ island (island $ 1 $ ).

## 样例 #1

### 输入

```
6
2 0
2 1
4 1
5 10
5 3
4 4```

### 输出

```
2
1
4
1
5
1```

# 题解

## 作者：zcr0202 (赞：4)

## 题目大意

给你一棵树，你在一号点上，现在有人要把树的边砍掉，求你最少能参观几个点？

## 解题思路

我们发现，要让一个点脱离这棵树，那么需要割 $n-1$ 条边。所以当 $k$ 小于 $n-1$ 时，直接输出 $n$。否则我们可以把一号点脱离这棵树，此时答案就为 $1$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k, ans;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;
	cin >> T;
	while(T--) {
		cin >> n >> k;
		if(k >= n - 1) {
			cout << "1\n";
		}
		else {
			cout << n << '\n';
		}
	}
}
```

---

## 作者：luobotianle (赞：2)

由于每一个岛都有 $n-1$ 座桥与其它岛连接，所以：
- 当 $k < n-1 $ 时，无法将任何一个岛分离开来，所以此时答案为 $n$；
- 否则，我们可以将第 $1$ 座岛分离出去，答案为 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		if(k>=n-1)cout<<1;
		else cout<<n;
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Guizy (赞：2)

## Destroying Bridges

找一下规律，发现：

- 当 $k\ge n-1$ 时，答案为 $1$；
- 否则答案为 $n$。

证明：

- 当 $k\ge n-1$ 时，最优方案是把 $1$ 号岛连接其他岛的桥全部拆掉，所以答案为 $1$。

- 否则每个岛都至少有 $n-k$（因为 $k<n-1$，所以 $n-k>0$）座桥通向其他岛，所以答案为 $n$。

```cpp
cin>>n>>k;
cout<<(k>=n-1?1:n)<<"\n";
```

---

## 作者：Red_river (赞：1)

## 题目大意
这道题就是说给你一个 $n$ 和一个 $k$ ，然后让你求出一个人从一个点到其他 $n-1$ 个点能到几个点。但是有 $k$ 个点被破坏了，这个人想知道他最多能到达几个点。
#### 题意分析
其实我们可以不难发现，只要 $k$ 大于等于了 $n-1$ 的话，那这个人只能去一个点，也就是他所连接的点都被封了。而如果不满足，那么所有的点他都可以到。所以说只要满足某个条件，那么他哪也到不了，否则他哪都到得了。因为任意两个点中都有路所相连。
## CODE
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register int
#define N 50005
#define INF 2147483647
#define f(x,k,y,z) for(int x=k;x<=y;x+=z)
using namespace std;
int n,m,k,jk,ans,sum,num;
int cnt,tot,dis[N],vis[N],wis[N],f[N];
void read(int &x)
{
	x=0;int ff=1;
	char ch=getchar();
	while (ch<'0'||ch>'9')
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	x*=ff;return;
}
 
void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
 
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n);int x=0,y=0;
	for(int i=1;i<=n;i++)
	{
		read(x),read(y);
		if(y>=(x-1)) printf("%d\n",1);
		else printf("%d\n",x);
	}
	return 0;
}
```

---

## 作者：keep_shining (赞：0)

我又来水题解了！

## 题意：
有 $T$  组数据，每组输入一个 $k$ 和一个 $n$，表示有 $n$ 个岛，每座岛都与剩下的岛连接，你可以**去掉 $k$ 条边**，求你**最少**能到几个岛（你最初在 $1$ 号岛）。

## 思路：
每个岛都与剩余 $n-1$ 个岛连接，那如果你能够删掉 $n-1$ 条边，那他就只能在 $1$ 号岛了，所以如果 $k\ge n-1$，即你能删掉大于等于 $n-1$ 条边，那就输出 $1$，否则无论你删哪 $k$ 条边，他都能到剩下的 $n-1$ 个岛，那就输出 $n$。

## AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int main()
{
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        if(k>=n-1)cout<<1<<endl;
        else cout<<n<<endl;
    }
    return 0;
}
```
我自我感觉已经讲的详细了，就不加注释了。

---

## 作者：Hacker_Cracker (赞：0)

## CF1944A Destroying Bridges 题解

[站内链接](https://www.luogu.com.cn/problem/CF1944A)  [原地址](http://codeforces.com/problemset/problem/1944/A)

### Solution
分类讨论：

+ 当 $ n-1 \le k $ 时，我们可以把与  $ 1 $  号节点相连的所有节点去除，从而分离出  $ 1 $  号节点，故答案为   $ 1 $ 。
+ 当  $ k < n-1 $ 时，因为本图是**强连通的**，所以只要有一个及以上的节点和  $ 1 $ 号节点相连，从    $ 1 $  号节点就可以访问全部  $ n $  个节点。

### [AC](https://www.luogu.com.cn/record/158620388) Code
```cpp
//By:sty0948
#include <iostream>
using namespace std;
int main() {
	ios :: sync_with_stdio (false) , cin.tie (0) , cout.tie (0);
	int T;
	cin >> T;
	while (T --) {
		int n , k;
		cin >> n >> k;
		cout << ( k < n - 1 ? n : 1 ) << endl;
	}
	return 0;
}
```

---

## 作者：Dream_Mr_li (赞：0)

## Solution

可以发现，参观点的多少只有两种情况：

- 切掉与 $1$ 连接的 $n-1$ 个点，把点 $1$ 分离出去，只能参观一个岛屿。

![](https://cdn.luogu.com.cn/upload/image_hosting/hhjbwix8.png)

- 不能切掉与 $1$ 连接的 $n-1$ 个点，不能把点 $1$ 分离出去，能参观所有 $n$ 个岛屿。

![](https://cdn.luogu.com.cn/upload/image_hosting/aa1dfj9p.png)

## Code

```c++
#include<bits/stdc++.h>
#define TRACE 1
#define tcout TRACE && cout
#define int long long
#define endl '\n'
const int N=1e6+10;
using namespace std;
int t,n,k;
signed main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n>>k;
		if(k>=n-1){//判断能否切掉与 1 连接的 n-1 个点
			cout<<1<<endl;
		}else{
			cout<<n<<endl;
		}
	}
	return 0;
}

```

---

## 作者：Elhaithan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1944A)
### 思路
以最佳方式摧毁桥梁，就是摧毁 $1$ 岛所连接的桥梁。

如果 $1$ 岛所连接的桥梁都被摧毁了，那么答案为 $1$；否则，由于各个岛之间都有桥梁沟通，所以所有岛都能到达。判断是否 $k < n - 1$ 即可。
### code
```cpp
#include <cstdio>
#define int long long
void solve() {
	int T, n, k;
	scanf("%lld", &T);
	while(T --) {
		scanf("%lld%lld", &n, &k);
		if(k < n - 1) printf("%lld\n", n);
		else puts("1");
	}
}
#undef int
int main() {
	solve();	
	return 0;
}
```

---

## 作者：__lhx__ (赞：0)

每两座岛之间都有一座桥连接，所以这是一个完全图。

显然，只有将与 $1$ 直接相连的所有桥都摧毁，才能把 $1$ 岛和其余岛隔开。

否则 $1$ 岛和其他岛仍与其他岛在同一个强连通分量里
，总有一条路径连接 $1$ 岛与其他岛，此时答案为岛数 $n$ 。 

```cpp
#include<iostream>
int t,n,k;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		printf("%d\n",k<n-1?n:1);
	}
	return 0;
}
```

---


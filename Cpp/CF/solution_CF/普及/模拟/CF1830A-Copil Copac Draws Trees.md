# Copil Copac Draws Trees

## 题目描述

Copil Copac is given a list of $ n-1 $ edges describing a tree of $ n $ vertices. He decides to draw it using the following algorithm:

- Step $ 0 $ : Draws the first vertex (vertex $ 1 $ ). Go to step $ 1 $ .
- Step $ 1 $ : For every edge in the input, in order: if the edge connects an already drawn vertex $ u $ to an undrawn vertex $ v $ , he will draw the undrawn vertex $ v $ and the edge. After checking every edge, go to step $ 2 $ .
- Step $ 2 $ : If all the vertices are drawn, terminate the algorithm. Else, go to step $ 1 $ .

The number of readings is defined as the number of times Copil Copac performs step $ 1 $ .

Find the number of readings needed by Copil Copac to draw the tree.

## 说明/提示

In the first test case:

After the first reading, the tree will look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1830A/96592d8d6a7376d06a499045a206685f9a68df31.png)After the second reading:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1830A/7b7bd2d2b1a9ad0d44021bb292052bd1a2395dfd.png)Therefore, Copil Copac needs $ 2 $ readings to draw the tree.

## 样例 #1

### 输入

```
2
6
4 5
1 3
1 2
3 4
1 6
7
5 6
2 4
2 7
1 3
1 2
4 5```

### 输出

```
2
3```

# 题解

## 作者：theb0t (赞：8)

首先这道题肯定不能暴力枚举，我们要思考其他算法。

我们可以给每一条边编一个号。然后从根开始遍历这棵树，当一条边的编号比他祖先到他祖先的祖先的那条边的编号还要小时，就说明顺序错了，要再等一轮。

这个就简单了，直接 dfs 就行，注意答案要加 $1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> to[200005],id[200005];

int dfs(int x,int fa,int pre){ //x当前节点，fa上一个节点（因为是无向图），pre上一条边的编号
    int res=0;
    for(int i=0;i<to[x].size();i++){
        if(to[x][i]!=fa) res=max(res,dfs(to[x][i],x,id[x][i])+(id[x][i]<pre)); //(id[x][i]<pre)是一个布尔表达式，如果为真就加1
    }
    return res;
}
int main(){
    int T; cin>>T;
    while(T--){
        int n; cin>>n;
        for(int i=1;i<=n;i++) to[i].clear(),id[i].clear(); //注意多测清空
        for(int i=1;i<n;i++){
            int x,y;
            cin>>x>>y;
            to[x].push_back(y); to[y].push_back(x);
            id[x].push_back(i); id[y].push_back(i); //给每一条边编号
        }
        cout<<dfs(1,0,0)+1<<'\n';
    }
    return 0;
}
```

---

## 作者：Malkin_Moonlight (赞：4)

# 题解：CF1830A Copil Copac Draws Trees
# 0x00 分析
首先这题的一二步骤形成了一个循环，问循环多少次能把这棵树画完。

先拿第一组样例进行分析。

首先按题意画出 $1$ 这个顶点，进入步骤 $1$。

接下来依次按照题目给的数据绘制。

进行一次操作后变成了这样：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1830A/96592d8d6a7376d06a499045a206685f9a68df31.png)
 
我们发现这棵树并没有绘制完毕。所以 Copil Copac 还需要再执行操作。

经过第二次绘制，Copil Copac 的树变成了这样。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1830A/7b7bd2d2b1a9ad0d44021bb292052bd1a2395dfd.png)

我们发现这棵树已经绘制完毕，所以绘制这棵树所需的**执行次数**就是 $2$。

什么？还不够？
接下来我们再拿第二组样例进行分析。

还是按题意画出 $1$ 这个顶点，进入步骤 $1$。

进行一次绘制后变成了这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/8wb5fgrb.png)

第二次绘制后：
![](https://cdn.luogu.com.cn/upload/image_hosting/7go9qtnj.png)

我们发现还是没有画完。于是开始第三次绘制。

![](https://cdn.luogu.com.cn/upload/image_hosting/k83gafz2.png)

哇！终于画完了。于是答案为 $3$。现在我想你们明白了这题的意思了吧。

# 0x01 思路

但是我们想，最坏情况下这棵树会是一条链，而且正好是倒着的。

所以最坏情况下要 $n - 1$ 次操作，所以此题一定不能暴力模拟绘制过程。

所以我们想此题有没有什么性质呢？

我们先把每条边按题目给出的顺序编个号。这里我用第二个样例举例子。

![](https://cdn.luogu.com.cn/upload/image_hosting/cv9870qz.png)

仔细观察，你发现了什么？

先摆出结论：从根开始遍历这棵树，当一条边的编号比他上面那条边的编号还要小时，就无法在一轮内绘制，要再等一轮。

比如说 $2$ 到 $4$ 和 $4$ 到 $5$ 这两条边为什么能连着画，因为这两条边的编号递增。而比如 $1$ 到 $2$ 和 $2$ 到 $4$ 这两条边肯定不能在一轮内画完，因为肯定要先画 $1$ 到 $2$ 再画 $2$ 到 $4$，但是 $2$ 到 $4$ 却比 $1$ 到 $2$ 给出的早。

现在你们理解了吗？这题不能按题目模拟，否则绝对超时，要找到其他方法，最后注意答案要加 $1$ 哦。
# 0x02 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
using namespace std;
typedef long long ll;//个人习惯
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
#define endl '\n'
#define pb emplace_back
const ll MAXN = 2e5 + 5;
const ll MOD = 1e9 + 7;
const ll dx[] = {0, 0, 1, -1};
const ll dy[] = {1, -1, 0, 0};

ll T, n, a, b;

//v存边，id存编号 
vector<ll> v[MAXN], id[MAXN];

ll dfs(ll x, ll p, ll pre) { //pre代表上一条边，p代表父节点 
	ll ans = 0;
	for (int i = 0; i < v[x].size(); i++) {
		if (v[x][i] != p) {
			ans = max(ans, dfs(v[x][i], x, id[x][i]) + (id[x][i] < pre));
		}
	}
	return ans;
}
int main()
{
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) v[i].clear(), id[i].clear(); //一定别忘了清空呀 
		for (int i = 1; i < n; i++) { //n - 1条边 
			cin >> a >> b;
			v[a].push_back(b); v[b].push_back(a);
			id[a].push_back(i); id[b].push_back(i);
		}
		cout << dfs(1, 1, 0) + 1 << endl;//别忘了加上1 
	}
	return 0;
}
```
# 0x03 其他话
谢谢大家的观看和支持，如果觉得有用就点个赞吧。

---


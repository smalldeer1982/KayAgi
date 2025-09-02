# Mahmoud and Ehab and the wrong algorithm

## 题目描述

Mahmoud was trying to solve the vertex cover problem on trees. The problem statement is:

Given an undirected tree consisting of $ n $ nodes, find the minimum number of vertices that cover all the edges. Formally, we need to find a set of vertices such that for each edge $ (u,v) $ that belongs to the tree, either $ u $ is in the set, or $ v $ is in the set, or both are in the set. Mahmoud has found the following algorithm:

- Root the tree at node $ 1 $ .
- Count the number of nodes at an even depth. Let it be $ evenCnt $ .
- Count the number of nodes at an odd depth. Let it be $ oddCnt $ .
- The answer is the minimum between $ evenCnt $ and $ oddCnt $ .

The depth of a node in a tree is the number of edges in the shortest path between this node and the root. The depth of the root is 0.

Ehab told Mahmoud that this algorithm is wrong, but he didn't believe because he had tested his algorithm against many trees and it worked, so Ehab asked you to find 2 trees consisting of $ n $ nodes. The algorithm should find an incorrect answer for the first tree and a correct answer for the second one.

## 说明/提示

In the first sample, there is only 1 tree with 2 nodes (node $ 1 $ connected to node $ 2 $ ). The algorithm will produce a correct answer in it so we printed $ -1 $ in the first section, but notice that we printed this tree in the second section.

In the second sample:

In the first tree, the algorithm will find an answer with 4 nodes, while there exists an answer with 3 nodes like this: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959C/080040c1176abdd5ada4ff45524faae8f6709ce5.png) In the second tree, the algorithm will find an answer with 3 nodes which is correct: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959C/2d5dc2017c538f7d5b27b72e32312118454ea6c6.png)

## 样例 #1

### 输入

```
2
```

### 输出

```
-1
1 2
```

## 样例 #2

### 输入

```
8
```

### 输出

```
1 2
1 3
2 4
2 5
3 6
4 7
4 8
1 2
1 3
2 4
2 5
2 6
3 7
6 8```

# 题解

## 作者：attack (赞：2)

我的构造思路比较奇葩。。

大概长这样。

就是上面三个点，下面一个菊花。

![picture](https://cdn.luogu.com.cn/upload/pic/21220.png)
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<map>
using namespace std;
const int MAXN = 2 * 1e6 + 10, INF = 1e9 + 10, B = 63;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
main() { 
#ifdef WIN32
    //freopen("a.in", "r", stdin);
#endif
    int N = read();
    if(N == 2 || N == 3 || N == 4 || N == 5) printf("-1\n");
    else {
        printf("1 2\n");
        printf("1 3\n");
        printf("1 4\n");
        for(int i = 5; i <= N; i++) 
            printf("3 %d\n", i);
    }
    for(int i = 1; i <= N - 1; i++) 
        printf("%d %d\n", i, i + 1);
}
```

---

## 作者：ZSYZSYZSYZSY (赞：1)

# CF959C Mahmoud and Ehab and the wrong algorithm
## Description
我们要删除一个有 $n$ 个节点的树的所有边，删边的方式是删掉一个节点，使与其相连的边全部删除。有个人提出了最小的删点个数为：树中深度为奇数的点的个数与树中深度为偶数的点的个数的最小值。构造出一个反例树与一个满足上面关系的树。

## Solution
首先，简单画几组图可以发现，当 $n \leq 5$ 时，无论我们怎么组织树的形式，都是满足要求的，于是输出 $-1$ 即可。

当 $n > 5$ 时，构造实际需要删除的点尽可能的少，而根据题中式子算出来的多的树。考虑以下方案：将编号为偶数的点连在 $1$ 上，将编号为奇数的点连在 $2$ 上。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
	ll n;
	cin>>n;
    if(n<=5) {
		cout<<-1<<endl;
	}
    else {
    	cout<<1<<" "<<2<<endl;
    	cout<<1<<" "<<3<<endl;
    	cout<<1<<" "<<4<<endl;
        for(int i=5;i<=n;i++){
            cout<<2<<" "<<i<<endl;
		}
    }
    for(ll i=1;i<n;i++){
        cout<<i<<" "<<i+1<<endl;
	}
	return 0;
}
```


---

## 作者：Jsxts_ (赞：1)

# 题解 CF959C
[传送门](https://www.luogu.com.cn/problem/CF959C)
## 题意
现在我们要删除一个 $n$ 个节点的树的所有边，删边的方式为删掉一个节点，使与其相连的边全部删除。有个人提出了最小的删点个数为：树中深度为奇数的点的个数与树中深度为偶数的点的个数的最小值。现在请你构造出一个反例树与一个满足上面关系的树。
## 题解

我们先想第二棵树，不难发现一个菊花图就可以满足条件，如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/rhbx1w9f.png)

而第一棵树的构造，就让我们在上面那棵树上加点东西，判断能否满足反例。

我造的是在其中一个叶节点上加两个子节点，这样在 $n > 5$ 时就满足条件，可以自己推一下，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/1qtfct8k.png)

使用上面的构造方法，发现在 $n \le 5$ 时，没有反例树，就输出 -1。

代码就不给了，因为实现非常简单，主程序只有 10 行。

---

## 作者：OcTar (赞：0)

## CF959C

### 题目大意

翻译上有，但是翻译缺少了“以 $1$ 为根”。

### 题解

先要找一个反例：
- 简单画几组图可以发现，当 $n\leq 5$ 时，无论我们怎么组织树的形式，都是满足要求的，于是输出 ``-1`` 即可。

- $n\gt 5$ 时，构造实际需要删除的点尽可能的少，而根据题中式子算出来的多的树。考虑以下方案：将编号为偶数的点连在 $1$ 上，将编号为奇数的点连在 $2$ 上。（见下图 $n=10$）![](https://cdn.luogu.com.cn/upload/image_hosting/9zkvq72j.png)可以发现，该方案实际上只需要删除 $1$ 和 $2$ 两个点即可，而按照题中式子算出的答案为 $1\sim n$ 中偶数的数量，明显偏大。


接下来符合要求的例子就很好构造了，链或菊花图都可以。

以下是完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	if (n <= 5) cout << -1 << '\n';
	else {
		for (int i = 2; i <= n; i++) {
			if (i & 1) cout << 2 << " " << i << '\n';
			else cout << 1 << " " << i << '\n';
		}
	}
	for (int i = 1; i < n; i++) cout << i << " " << i + 1 << '\n';
	return 0;
}
```


---


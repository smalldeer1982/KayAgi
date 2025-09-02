# Minimal Height Tree

## 题目描述

Monocarp had a tree which consisted of $ n $ vertices and was rooted at vertex $ 1 $ . He decided to study BFS ([Breadth-first search](https://en.wikipedia.org/wiki/Breadth-first_search)), so he ran BFS on his tree, starting from the root. BFS can be described by the following pseudocode:

```
a = [] # the order in which vertices were processed
q = Queue()
q.put(1) # place the root at the end of the queue
while not q.empty():
    k = q.pop() # retrieve the first vertex from the queue
    a.append(k) # append k to the end of the sequence in which vertices were visited
    for y in g[k]: # g[k] is the list of all children of vertex k, sorted in ascending order
        q.put(y)
```
Monocarp was fascinated by BFS so much that, in the end, he lost his tree. Fortunately, he still has a sequence of vertices, in which order vertices were visited by the BFS algorithm (the array a from the pseudocode). Monocarp knows that each vertex was visited exactly once (since they were put and taken from the queue exactly once). Also, he knows that all children of each vertex were viewed in ascending order.

Monocarp knows that there are many trees (in the general case) with the same visiting order $ a $ , so he doesn't hope to restore his tree. Monocarp is okay with any tree that has minimum height.

The height of a tree is the maximum depth of the tree's vertices, and the depth of a vertex is the number of edges in the path from the root to it. For example, the depth of vertex $ 1 $ is $ 0 $ , since it's the root, and the depth of all root's children are $ 1 $ .

Help Monocarp to find any tree with given visiting order $ a $ and minimum height.

## 说明/提示

In the first test case, there is only one tree with the given visiting order:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1437D/410231d5450c97d8a337f65673d6193fef7ef91a.png)In the second test case, there is only one tree with the given visiting order as well:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1437D/7a0ba94b1eb3ad4817eb8aa8e139c5ce715f4da2.png)In the third test case, an optimal tree with the given visiting order is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1437D/aa50643bf81bba2c4eca6a0d6c99c8ba0b01c205.png)

## 样例 #1

### 输入

```
3
4
1 4 3 2
2
1 2
3
1 2 3```

### 输出

```
3
1
1```

# 题解

## 作者：yu__xuan (赞：6)

### 题目

[CF1437D Minimal Height Tree](https://www.luogu.com.cn/problem/CF1437D)

### 思路

贪心，把整个严格递增的一部分节点放到一个节点的儿子位置上是最优的。模拟这个过程。

### Code

```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#define M 200001

int t, n, a[M];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        if (n == 1) { puts("0"); continue; }
        if (n == 2) { puts("1"); continue; }
        int last = 1, now = 1, ans = 0, k = 1;
        //last 表示上一层的节点个数
        //now 表示这一层的节点个数
        for (int i = 2; i < n; ++i) {
            if (a[i] < a[i + 1]) ++now;//一段连续递增的节点
            else {//不连续递增了 
                if (k == last) ++ans;//新开了一层。
                --last;//占用一个上一层的节点
                if (last == 0) {//上一层的节点都用完了
                    k = last = now, now = 1;
                }
                else ++now;//上一层的节点没用完的话，i + 1 是本层的节点。 
            }
        }
        if (now) {
            if (k == last) ++ans;
            --last;
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：Tony102 (赞：3)

[CF1437D](https://www.luogu.com.cn/problem/CF1437D)

[更好的阅读体验My Blog](https://tony102.com/archives/56/)


### Description 

Monocarp有一棵树，可是他已经忘记了它的形态。但是他有这棵树的$bfs$序，并且对于每一个节点，$bfs$都会按照升序遍历它的子节点。现在给出这个$bfs$序，求出这棵树的最小深度。



### Solution

先观察一下这个BFS序的性质

因为它给的BFS是按照升序访问子节点的，那么对于每个点后面出现的节点，如果它后面的点比他的编号还小，说明要新开一层，否则就可以一直堆在一层

举个例子：`1 4 3 2`

`1`已经确定是根，那么`1`的第一个子节点就是`4`，观察到`4`是目前`1`的子节点中编号最小的，如果我们要把`2`也弄成`1`的子节点，那么按照BFS序，`2`应该在`4`前面出现，所以这样是不合法的，说明`2`要新开一层成为`4`的子节点



### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
 
const int SIZE = 2e5 + 5;
 
int T, n, ans;
int a[SIZE], dep[SIZE];
 
inline int read()
{
	char ch = getchar();
	int f = 1, x = 0;
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + ch - '0'; ch = getchar(); }
	return x * f;
}
 
inline void bfs()
{
    std::queue < int > q;
    memset(dep, 0, sizeof(dep));
    q.push(1);
    int pos = 2;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans = std::max(ans, dep[u]);
        int lst = pos;
        if (pos > n) break;
        while (a[pos + 1] > a[pos] && pos < n) ++ pos;
        for (int i = lst; i <= pos; ++ i) {
            dep[a[i]] = dep[u] + 1;
            q.push(a[i]);
        }
        ++ pos;
    }
}
 
int main()
{
    T = read();
    while (T --) {
        n = read();
        for (int i = 1; i <= n; ++ i) a[i] = read();
        ans = 0;
        bfs();
        for (int i = 1; i <= n; ++ i) ans = std::max(ans, dep[i]);
        printf("%d\n", ans);
    }
    return 0;
}
```



---

## 作者：ykzzldz (赞：2)

由于题目中给出的序列是按照升序排序的，所以可以将连续的一段升序序列作为一个节点的子节点。容易发现，这样一定可以使这棵树的深度最小。关于程序细节的代码有注释。

```
#include<bits/stdc++.h>
using namespace std;
int t,n,a[210000],jsq,jl,jjl;
//变量说明：jsq 表示深度，jl 表示上一层节点个数，jjl 表示这一层节点个数
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		jsq=1;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		jl=1,jjl=1;
		for(int i=2;i<n;i++){
			if(a[i]>a[i+1]){
				jl--;
				if(jl==0){//当上一层已经没有节点了，就新加一层
					jl=jjl;
					jsq++;
					jjl=1;
				}
				else jjl++;
			}
			else jjl++;
		}
		cout<<jsq<<'\n';
	}
	return 0;
}
```

---

## 作者：chichichichi (赞：2)

此处有 [翻译](https://www.luogu.com.cn/paste/ekiop79k)

根据题意得，每一个结点的子节点BFS序中是单调上升子串。

为了求最小的高度，我们要让结点的子结点数尽量多，因此我们不应该将一个单调上升子串拆分成两个结点的子结点，因为表示结点的子结点的单调上升子串的长度要尽量长。

比如我们有序列 $1,2,3,4$，我们可以得到如下几种树：

![](https://cdn.luogu.com.cn/upload/image_hosting/f8gpqho9.png)

显然第三种树的高度最小，此时结点 $1$ 的子结点序列是最长的。为了方便，下文所指的单调上升子串都是指连续的长度最长。

接下来是看层数，即深度的判断。第 $i$ 层中应当包含 $len_{i-1}$ 个单调上升子串。这 $len_{i-1}$ 个单调上升子串的长度和即为第 $i$ 层的结点数。其中，$len_{i-1}$是第 $i-1$层中的结点个数。

到这里就差不多结束了，看看代码吧

```cpp

#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=1123456;
int n,m,t;
int a[maxn];
int main(){
	scanf("%d",&t);
	while(t)
	{
		t--;
		scanf("%d",&n);
		int ans=1,cnt=0,w=0,len=0;
		scanf("%d",&a[1]);
		//w记录当前层还能容纳的子串个数
		//ans记录树的深度
		// len记录当前层的结点个数 
		for(int i=2;i<=n;i++)
		{
			scanf("%d",a+i);
			if(a[i]<a[i-1]&&!w)
			{
				ans++;
				w=len-1;
				len=1;
			}
			else if(a[i]<a[i-1])
			{
				w--;
				len++;
			}
			else{
				len++; 
			}
		}
		printf("%d\n",ans);
	}
	return 0;
} 
```

---

## 作者：Eason_cyx (赞：1)

简单题。

顺着枚举所有元素，如果比前面一个数大就和前面的放在同一个连续段，否则自己新开一个连续段。新开的连续段所在树的那一层的上一层如果还有未被使用的叶子，就可以接在这个叶子下。否则整个树的深度 $+1$，将这个连续段接在上一层的第一个叶子上。

时间复杂度 $\Theta(n)$。

[Record](https://codeforces.com/contest/1437/submission/277597557)

---

## 作者：songtaoran (赞：0)

考虑维护两个东西，$lastcnt$ 代表上一层还有多少个结点，$nowcnt$ 代表这一层现在有几个结点。**注意子结点是按升序排列的！**  
首先，对于 $lastcnt = 1$：  
1. $a_i > a_{i - 1}$，此时 $nowcnt$ 加一，代表这一层又多了一个结点。
2. $a_i < a_{i - 1}$，由于此时已经不满足子结点是升序排列的了，且上一层的父亲结点也用完了，所以层数要加一。由于加了一层，此时 $lastcnt = nowcnt$，$nowcnt = 1$。因为这一个结点也算作这一层的，所以 $nowcnt$ 要等于一。

否则：  
1. $a_i > a_{i - 1}$，此时 $nowcnt$ 加一，代表这一层又多了一个结点。
2. $a_i < a_{i - 1}$，此时已经把上一层的父亲结点用完一个了，所以 $lastcnt$ 要减一，而 $nowcnt$ 要加一，因为就算把上一层的父亲结点用完一个，这个结点还是这一层的。

> Don't talk more to me, show me your code.
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll T, n, a[200010];
int main(){
	cin >> T;
	while(T--){
		scanf("%lld", &n);
		for(ll i = 1; i <= n; i++) scanf("%lld", &a[i]);
		ll lastcnt = 1, nowcnt = 1, ans = 1;
		for(ll i = 3; i <= n; i++){
			if(lastcnt == 1){
				if(a[i] > a[i - 1]) nowcnt++;
				else{
					ans++; lastcnt = nowcnt; nowcnt = 1;
				}
			}else{
				if(a[i] > a[i - 1]) nowcnt++;
				else lastcnt--, nowcnt++;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```
[提交记录 - $300106968$](https://codeforces.com/problemset/submission/1437/300106968)

---

## 作者：Weekoder (赞：0)

### 思路

提取关键信息：每个结点的子结点是按升序遍历的。

如果想要树的层数尽量少，每一层的节点就要尽量多，而我们可以贪心地给每个结点分配尽可能多的在原序列中升序排序的 $a_i$。

比如以下样例：


```
1
7
1 2 7 6 5 4 3
```
第一层只有一个结点 $1$，而第二层就可以给 $1$ 分配一个最长的连续上升子序列 $2,7$。不能给 $1$ 分配 $2,7,6$ 或更长的子结点序列了，因为此时这些结点都不是**严格递增**的。此时记录第二层的结点数量为 $2$。接下来，继续贪心地分配**两个**最长的连续上升子序列（分别作为 $2$ 和 $7$ 的子结点），即 $6$ 和 $5$，因为它们后面的数加进来一定不能构成上升子序列。后面的 $4$ 和 $3$ 同理，分配给 $6,5$。

于是，最后树的高度即为 $4$，由于题目中记根节点的高度为 $0$，于是答案减去 $1$，输出 $3$。

这里模拟就好了，不过有一些细节需要注意。题目中的连续上升子序列需要保证尽量长，换句话说就是求**极长连续严格递增的子序列**。

代码（有些乱七八糟）：


```cpp
#include <bits/stdc++.h>

#define debug(x) (cout << #x << " " << x << "\n")

using namespace std;

using ll = long long;
 
const int N = 2e5 + 5;

int T, n, a[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    while (T --) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        int cnt = 1, ans = 0, pos = 2;
        a[n + 1] = -1e9; 
        while (pos <= n) {
            int tmp = 0;
            for (int i = 1; i <= cnt; i++) {
                while (pos < n && a[pos] < a[pos + 1]) pos ++, tmp ++;
                pos ++, tmp ++;
            }
            cnt = tmp;
            ans ++;
        }
        cout << ans << "\n";
    }
    return 0;
}

/*
 * hack 1
 * 4
 * 1 3 2 4
 * why?
 * 答案应为 2
 * 实际输出 3
 * 模拟一遍吧，看着没问题
 * 我*我是**
 * 最后一个不行也得算数量
 * hack 2
 * 5
 * 1 2 5 4 3
 * 答案应为 2
 * 实际输出 3
 * 又来？？？
 * 我*，好像会卡在那里
 * a[n + 1] = -1e9 试试
 * 循环条件似乎错了
 * ok了！！！
 * 小样例错了，艹
 * 部队，循环条件又好像没错
 * 好了好了，再测一遍
 * 错到外太空去了，test 273
 * 在讨论区搞到了 hack 3
 * 7
 * 1 2 7 6 5 4 3
 * 答案应为 3
 * 实际输出 4
 * 我服了。。。
 * 我是** 我是** 我是**
 * 重要的事情说三遍
 * 为了偷懒，写错了qwq 导致当前层节点数量统计错误
 * 终于 AC！！！！！！！！！！！！！！！！
*/
```

---

## 作者：aakennes (赞：0)

~~貌似也很氵~~

### 题目大意：

给定BFS序列，一层的BFS顺序按节点编号递增，球树的最小高度

### 思路：

很好想的贪心

记 $a_{i+1} < a_i$ 为冲突事件，对于这种事件要么挂在上层另一个没挂过点的节点下，要么新开一层，把 $i+1$ 挂在这层节点上

所以能挂就挂，遇到冲突就消耗一个上层节点，消耗完就新开一层

### 带码：

```
n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		int _floor=1,last=2,sum=0;
		for(int i=2;i<n;i++){
			if(a[i+1]<a[i]){
				if(--sum<0)_floor++,sum=i-last,last=i+1;
			}
		}
		printf("%d\n",_floor);
```

---


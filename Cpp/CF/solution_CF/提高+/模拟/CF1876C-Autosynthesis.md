# Autosynthesis

## 题目描述

Chaneka writes down an array $ a $ of $ n $ positive integer elements. Initially, all elements are not circled. In one operation, Chaneka can circle an element. It is possible to circle the same element more than once.

After doing all operations, Chaneka makes a sequence $ r $ consisting of all uncircled elements of $ a $ following the order of their indices.

Chaneka also makes another sequence $ p $ such that its length is equal to the number of operations performed and $ p_i $ is the index of the element that is circled in the $ i $ -th operation.

Chaneka wants to do several operations such that sequence $ r $ is equal to sequence $ p $ . Help her achieve this, or report if it is impossible! Note that if there are multiple solutions, you can print any of them.

## 说明/提示

In the first example, doing the operations like the example output gives the following results:

- Element $ a_2 $ gets circled $ 1 $ time.
- Element $ a_3 $ gets circled $ 2 $ times.
- The uncircled elements (ordered by their indices) are $ a_1 $ , $ a_4 $ , and $ a_5 $ . So $ r=[3,2,3] $ .
- $ p=[3,2,3] $

Therefore, $ r=p $ .

In the second example, it is impossible.

## 样例 #1

### 输入

```
5
3 4 2 2 3```

### 输出

```
3
3 2 3```

## 样例 #2

### 输入

```
3
1 2 3```

### 输出

```
-1```

# 题解

## 作者：_Fatalis_ (赞：12)

upd: 2023/10/12 修正一个小错误（感谢 @Nullptr_qwq）

给定一个长度为 $n$ 的序列 $\{a_i\}$。

你可以对这个序列进行任意次操作，每次操作选择一个下标 $i$，并圈住下标为 $i$ 的数 $a_i$。可以多次圈一个数。

请构造出一组操作方案，使得操作选出的下标序列 $\{i\}$ 等于**没有**被圈过的数构成的序列 $\{a_i\}$。

请注意，下标序列和没有被圈过的数的序列皆有序，后者按照原序列顺序依次排列。

---

假设我们令操作序列为 $\{o_i\}$，未被选中序列列为 $\{u_i\}$。

初看题面，有一个很重要的信息：操作选出的下标序列是唯一对应的。

即，要使 $o_i = u_i$，则第 $i$ 次选择的位置唯一确定为 $o_i$。

那么我们可以发现，要是某一个数 $a_i$ 要是不选，那么就只有唯一确定的 $o_j = a_i$ 的位置要被选中，并且选择的顺序要对应上 $u$​ 的位置。 $(\alpha)$

**并不**需要考虑位置对应的事，因为一个数刚好只会对应一个操作。

反过来思考，要是某个位置 $i$ 要是选中了，那么就一定会有不小于一个的 $a_j = i$ 被留在了不圈出的序列里面。 $(\beta)$

考虑抽象成图论问题。每一个数抽象成一个节点，那么变成了黑白染色问题。

令圈一次以上为黑色 $col=1$，令不圈为白色 $col = 0$。连边 $i \to a_i$，以上说法可以转换为以下的涂色问题：

- 白点后面唯一的出边到达的点必须是黑点。 $(\alpha)$
- 一个黑点的所有入边的起点中，至少有一个白点。 $(\beta)$

关于样例的涂色方案是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/tke2vbsk.png)

发现这刚好是个内向基环树或森林（每个点只有一个出度，并且环外指向环内）。

考虑在环外跑拓扑排序，依次染色，发现叶子节点必然是白色，那么考虑以下的染色方案即可跑完不含环的部分：

- 一个点是白点，则指向的节点必然是黑色。
- 若一个点儿子被拓展完进入队列时还未被染色（即所有儿子都是黑色的），那么染成白色。

图示：（黄色为白，红色为黑）

![](https://cdn.luogu.com.cn/upload/image_hosting/z7c6hw85.png)

这样构造是唯一的部分合法的（不那么构造不可能合法）。

把非环的部分跑完，考虑跑环。

如果环上有被染色，那么可以证明一定是黑色。（白色的要求是儿子全部遍历完，那么环不可能遍历完所有儿子进入队列）

两种假设：

- 要是环上全部没有被染色，那么从任意一个点开始，染成白色（染成白色是不会出现冲突，因为要是冲突会一定被染成黑色，就有部分点被染色了）。

- 要是环上有点被染色，从任意一个点有颜色的点开始。

开始后按照非环部分一样拓展。有一点小特殊，但也有一般性的是：当前点为黑色，下一个点并未被涂色时给下一个点涂为白色。

涂一圈，判断是否合法的便是在最后看首尾两个点颜色情况了。黑色和黑色撞一起是可以的，因为既然染成了黑色就一定有白色作为起点。但是两个白色就不行了。

最后检查所有白色点，对应到的就是不被选的点，找出它们对应的 $a_i$，全部依次推进答案中，输出即可。

一点小细节，环可能不止一个。

```cpp
// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

const int maxn = 1e6 + 10;
int n, in[maxn], col[maxn], to[maxn];
std::queue<int> q;
std::vector<int> ans;

tsz main() {
    read(n);
    for (int i = 1; i <= n; i++) {
        read(to[i]);
        in[to[i]]++;
    }
    memset(col, -1, sizeof(col));
    for (int i = 1; i <= n; i++) {
        if (!in[i]) q.push(i), col[i] = 0;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (!col[u]) col[to[u]] = 1;
        in[to[u]]--;
        if (in[to[u]] <= 0) {
            if (!(~col[to[u]])) col[to[u]] = 0;
            q.push(to[u]);
        }
    }
    int rt = -1;
    for (int i = 1; i <= n; i++) {
        if (in[i] > 0) {
            rt = -1;
            int u = i;
            while (to[u] != i) {
                if (~col[u]) {
                    rt = u;
                }
                u = to[u];
            }
            if (~col[u]) {
                rt = u;
            }
            if (!(~rt)) {
                col[i] = 0;
                rt = i;
            } // 找环上有颜色的起点，找不到任选起点

            u = rt;
            in[u]--;
            while (to[u] != rt) {
                if (!col[u]) {
                    col[to[u]] = 1;
                } else if (!(~col[to[u]])) {
                    col[to[u]] = 0;
                }
                in[to[u]]--;
                u = to[u];
            }
            if (!col[u] && !col[to[u]]) {
                puts("-1");
                return 0;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!col[i]) {
            ans.push_back(to[i]);
        }
    }
    writeln(ans.size());
    for (int e : ans) {
        write(e); putchar(' ');
    }
    puts("");
    return 0;
}
```



---

## 作者：zac2010 (赞：11)

考虑将所有的 $i$ 指向 $a_i$，将会建出一张基环内向树。

对于一个节点 $i$，假若最终我们未圈出它，那么我们称我们选择了 $i$ 的出边；否则是未选择。

不难发现，最终答案合法当且仅当：所有未选择出边的点，它的入边最少有一条被选择了；所有选择了出边的点，它所有的入边都没被选择。

由于所有叶节点只能选择它的出边，于是考虑对于基环树自底向上贪心，最终对于剩下的环进行处理。

无解的情况，就是在我们处理之后发现有节点并未在过程中处理成功。

代码可以使用拓扑排序简易实现。

```
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 1e6 + 10;
int n, a[N], b[N], in[N], id[N], vis[N], cnt[N];
queue<int> q;
vector<int> ans;
int main(){
    scanf("%d", &n);
    FL(i, 1, n) id[i] = i;
    FL(i, 1, n) scanf("%d", &a[i]), in[a[i]]++;
    FL(i, 1, n) if(!in[i]) q.push(i), vis[i] = 1;
    while(!q.empty()){
        int u = q.front(), v = a[u]; q.pop();
        if(vis[v]) continue; ans.emplace_back(a[u]);
        vis[v] = 1, in[a[v]]--;
        if(!in[a[v]]) vis[a[v]] = 1, q.push(a[v]);
    }
    FL(i, 1, n) if(!vis[i])
        for(int u = i; a[u] != u && !vis[a[u]]; u = a[a[u]])
        	ans.emplace_back(a[u]), vis[u] = vis[a[u]] = 1;
    FL(i, 1, n) if(!vis[i]){printf("-1\n"); return 0;}
	int tot = 0;
    for(const int &x: ans) b[x] = 1;
    FL(i, 1, n) tot += b[i];
    printf("%d\n", n - tot);
	FL(i, 1, n) if(!b[i]) printf("%d ", a[i]);
    return 0;
}
```


---

## 作者：童年的小翼龙 (赞：8)

## 题意

给你一个长度为 $n$ 的序列 $\{a_1,a_2\dots a_n\}$，满足 $\forall 1\le i\le n,1\le a_i\le n$。你要将这个序列划分成两个不交的子序列，满足其中一个子序列的下标构成的集合**等于**另一个子序列的值构成的集合。输出作为值的那一个子序列。

## 题解

将每个位置看做一个点，$i$ 向 $a_i$ 连一条有向边，由于每个点只有一个出度，所以整张图是一棵基环树，且根的位置是一个环。

我们将作为值的点称作 $1$ 类点，将作为下标的点称作 $0$ 类点。我们可以得到以下结论：

- 一个点是 $0$ 类点，当且仅当它有一个直接儿子是 $1$ 类点。
- 一个点没有直接儿子是 $1$ 类点，则它是 $1$ 类点。
- 一个点是 $1$ 类点，则它的父亲一定是 $0$ 类点。

则叶子处的点必定是 $1$ 类点。于是，我们可以对这张图进行拓扑排序，从叶子开始，考虑每个点对它父亲的影响，并将所有儿子都考虑完的点放到队列中。最后，我们只可能剩下若干个环没有考虑。这时候剩下的环分为一下几种情况：

- 若这个环中有已经确定了的 $0$ 类点，则这个环中的点一定可以合法分类。具体地：
  - 如果一个点 $i$ 是 $0$ 类点，则当 $a_i$ 是 $0$ 类点的时候，说明 $a_i$ 有一个在环外面的直接儿子是 $1$ 类点，合法；当 $a_i$ 没有被确定的时候，将$a_i$ 变为 $1$ 类点。
  - 如果一个点 $i$ 是 $1$ 类点，则 $a_i$ 是 $0$ 类点的时候合法；当 $a_i$ 未确定的时候将 $a_i$ 变为 $0$ 类点。

- 若这个环中没有已经确定了的 $0$ 类点，则当环的大小是偶数的时候交叉分类，奇数无解。

然后输出就行了。

AC Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Slongod{
const int N = 2e5+7;
int n , a[N] , f[N] , rd[N];
int main()
{
    cin >> n; for (int i = 1; i <= n; i++){cin >> a[i]; rd[a[i]]++;}
    for (int i = 1; i <= n; i++){f[i] = 1;}
    queue <int> q; for (int i = 1; i <= n; i++){if (!rd[i]){q.push(i);}}
    while(!q.empty()) {
        int u = q.front(); q.pop();
        if (f[u]){f[a[u]] = 0;}
        rd[a[u]]--;
        if (!rd[a[u]]) {
            q.push(a[u]);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (rd[i] and !f[i]) {
            int x = !f[i] , t = i;
            rd[i]--;
            do {
                t = a[t];
                if (x != f[t]) {
                    if (x == 1){x = f[t];}
                    else {f[t] = x;}
                } rd[t]--; x ^= 1;
            } while(t != i);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (rd[i] == 1) {
            rd[i]--; int x = 0;
            for (int t = a[i]; t != i; t = a[t] , x ^= 1) {
                rd[t]--; f[t] = x;
            } if (f[i] != x) {
                cout << "-1\n";
                return 0;
            }
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++){cnt += (f[i] == 1);}
    cout << cnt << '\n';
    for (int i = 1; i <= n; i++) {
        if (f[i] == 1) {
            cout << a[i] << ' ';
        }
    } cout << '\n';
    return 0;
}
}int main()
{
    ios :: sync_with_stdio(0);
    cin.tie(0) , cout.tie(0);
    return Slongod :: main();
}
```

---

## 作者：樱雪喵 (赞：7)

## Solution 1

想到了建图但没有完全想到，于是有了这个神秘做法。

题意等价于选择一个 **下标集合**，使它和 **它补集对应的值域集合** 相等。设它们分别为 $S,T$。  
由于不同位置的 $a_i$ 有可能相等，设 $|S|$ 表示 $S$ 的元素个数，则有 $|T|\le |S|$。

考虑 $|S|>|T|$ 的情况，则一定至少存在一个下标 $i\in [1,n]$，$i$ 没在值域集合里出现过。那么如果在 $S$ 集合选择下标 $i$，没法找到一个数在 $T$ 集合里与它对应。根据这一点我们可以判断哪些下标一定不选。  
对于一定不选的下标 $i$，则根据补集的定义值为 $a_i$ 的数一定在 $T$ 中被选，同时下标为 $a_{a_i}$ 的数一定在 $S$ 中被选。以此类推，只要还满足 $|S|>|T|$ 我们就可以一直把已经确定选不选的数从集合里去掉，直到 $|S|=|T|$。

考虑 $|S|=|T|$ 的情况，这等价于 $T$ 是一个 $1\sim n$ 的排列。如果把值 $a_i$ 选进 $T$，下标 $a_i$ 就必须在 $S$。限制等价于下标 $i$ 和 $a_i$ 只能选一个，连边 $i\to a_i$，判图上有没有奇环即可。

## Solution 2

一开始就考虑按 $i\to a_i$ 的方式建图，那么每个点有一条出边，图是一个内向基环树森林。

分类讨论**下标** $i$ 选不选：

- 不选点 $i$，则点 $a_i$ 一定被选。
- 选点 $i$，则至少有一个 $a_j=i$ 的下标 $a_j$ 不被选。

只考虑树上的答案，限制就变成在树上选择一些点，每个点要么儿子和父亲全被选，自己不选；要么儿子不全被选，自己被选。

显然所有叶子都不能选，从叶子向根依次考虑答案即可。然后图上就只剩下了若干个环，回到了 Solution 1 的第二种情况。

代码是 Solution 1。

```cpp
const int N=2e5+5;
int flag[N],a[N],n,cnt[N];
queue<int> q;
void dfs(int u)
{
	if(flag[a[u]]==flag[u]) {printf("-1\n");exit(0);}
	else if(flag[a[u]]!=-1) return;
	flag[a[u]]=flag[u]^1;
	dfs(a[u]);
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read(),cnt[a[i]]++;
	for(int i=1;i<=n;i++) flag[i]=-1;
	for(int i=1;i<=n;i++) if(!cnt[i]) q.push(i);
	while(!q.empty())
	{
		int u=q.front(); q.pop()，flag[u]=0;
		if(flag[a[u]]==0) {printf("-1\n");return 0;}
		int lst=flag[a[u]]; flag[a[u]]=1;
		if(lst==-1)
		{
			cnt[a[a[u]]]--;
			if(!cnt[a[a[u]]]) q.push(a[a[u]]);
		}
	}
	for(int i=1;i<=n;i++) if(flag[i]==-1) flag[i]=1,dfs(i); 
	int qwq=0;
	for(int i=1;i<=n;i++) if(!flag[i]) qwq++;
	printf("%d\n",qwq);
	for(int i=1;i<=n;i++) if(!flag[i]) printf("%d ",a[i]); 
	cout<<endl; return 0;
}
```

---

## 作者：Aleph_Drawer (赞：3)

一道可能比较套路的题目。

一开始我并没有往图的方向想。但是不妨碍得出正解。

由于嵌套下标有点多，故使用 $a[i]$ 一类的表达方式。

首先我们发现，可能存在这么一些数，使得除了自己之外其他的数都不跟**它的下标**相等。数学化一点的语言来讲就是对于 $i$，$\forall 1 \leq j \leq n, i \neq j, a[j] \neq i$。

显然，这些点是不能被圈起来的，否则肯定会造成无解。

那么这些点如果没有被圈起来，那么根据题意，他们所代表的数 $a[i]$ 就**一定要被圈起来**。

那么由于 $a[i]$ 已经被圈起来了，它所代表的**值**就不会再计入到上面的那个式子里面了，即如果对于某个数只有 $a[a[i]]$ 的值跟它的下标相等，那么这个数也是**不能被圈起来的**。

这里可能比较绕，但是相信大家应该也能看出来这里与图的联系：如果 $i$ 向 $a[i]$ 连边，不能圈起来的就是没有入边的点，而一定要被圈起来的就是这些点连接的那些点，而这些一定要被圈起来的点被圈起来之后不计入上述式子，相当于被删掉，则有可能又产生一批新的没有入边的点……这个过程可以用**队列**加上一个统计目前**计入式子的** $a[i]$ 的计数器。便能在 $O(n)$ 的时间内将所有类似的点全部处理完毕，注意不要重复加点，以及对矛盾以及自环（如果一个点不能被圈起来，但是自己又是一个自环，那么一定没有解）的处理。

此时我们剩下的，如果按照上面的连边方式，很显然就是一个个的环。我们就可以尝试交替处理：如果将 $i$ 圈起来，那么 $a[i]$ 就不能被圈起来，那么 $a[a[i]]$ 就要圈起来……显然的，如果环的点数为奇数，那势必会引起矛盾，即无解；否则那就是有解的，按照上述的方式处理即可。此处时间复杂度也为 $O(n)$。

所以总的时间复杂度为 $O(n)$。

我的写法可能细节比较多，赛时吃了三发罚时，或者叫罚分吧。

```c++
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 204;

int n, a[N], cnt[N], q[N << 1], head = 1, tail = 0;
int tag[N];
bool inq[N];
	// 0 : undef
	// 1 : white node
	// 2 : black node

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]), cnt[a[i]]++;
	for(int i = 1; i <= n; i++)
		if(!cnt[i] || (cnt[i] == 1 && a[i] == i))
			q[++tail] = i, inq[i] = 1;
	while(head <= tail) {
		int x = q[head++];
		tag[x] = 1;
		if(a[x] == x) {
			printf("-1\n");
			return 0;
		}
		if(tag[a[x]] == 1) {
			printf("-1\n");
			return 0;
		}
		if(!tag[a[x]])
			tag[a[x]] = 2,
			--cnt[a[a[x]]];
		if(!inq[a[a[x]]] && tag[a[a[x]]] == 0 && (!cnt[a[a[x]]] || (cnt[a[a[x]]] == 1 && a[a[a[x]]] == a[a[x]])))
			q[++tail] = a[a[x]], inq[a[a[x]]] = 1;
	}
	for(int i = 1; i <= n; i++) {
		if(!tag[i]) {
			int len = 1;
			int pos = i;
			while(a[pos] != i)
				++len,
				pos = a[pos];
			if(len % 2) {
				printf("-1\n");
				return 0;
			}
			int num = 2; pos = i;
			tag[pos] = num;
			while(a[pos] != i)
				num = 3 - num,
				tag[a[pos]] = num,
				pos = a[pos];
		}
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++)
		if(tag[i] == 1)
			++cnt;
	if(cnt == n)
		printf("-1\n");
	else {
		printf("%d\n", cnt);
		for(int i = 1; i <= n; i++)
			if(tag[i] == 1)
				printf("%d ", a[i]);
	}
	return 0;
}
```

---

## 作者：ganpig (赞：3)

来一个不需要建图的乱搞做法。

方便起见，把画圈称为*删除*。如果有解，那么我们可以把序列中的数分为两类：$\text{\small\color{red}删别人的数}$ 和 $\text{\small\color{blue}被别人删的数}$。根据题意显然有 $\text{\small\color{red}删别人的}$ **值**组成的集合与 $\text{\small\color{blue}被别人删的}$ **下标**组成的集合相等。我们将序列中的数一一归类就好了。

只要序列中有重复的值，一定存在若干 $[1,n]$ 之间的整数不在序列中，这些下标上的数就不可能 $\text{\small\color{blue}被别人删}$，它就只能去 $\text{\small\color{red}删别人}$。

用一个队列来存应被归为 $\text{\small\color{red}删别人的数}$ 的下标，不断取出队头元素，若其已被归类则跳过，否则将其归为 $\text{\small\color{red}删别人的数}$，并检查这个下标上的值所指向的数的状态：
- 如果已经被归为 $\text{\small\color{red}删别人的数}$，则无解；
- 如果已经被归为 $\text{\small\color{blue}被别人删的数}$，则无需操作（因为可以重复删除）；
- 如果还未被归类，则将其归为 $\text{\small\color{blue}被别人删的数}$，并维护其值在序列中的个数，当个数减少到 $0$ 时将这个值添加到队列末尾。

如果队列被取空，甚至是输入的是 $[1,n]$ 的全排列而没有重复元素，那该怎么做呢？其实只要找到第一个还没有被归类的元素，对其进行上述操作即可。

时间复杂度 $O(n)$，码量也很小。

## $\text{Code}$

```cpp
#include <bits/stdc++.h>
int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1), cnt(n + 1);
    for (int i = 1; i <= n; i++)
        std::cin >> a[i], cnt[a[i]]++;

    std::queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!cnt[i])
            q.push(i);

    int last = 0, ok = 0;
    std::vector<int> state(n + 1);
    while (true) {
        int now;
        if (q.empty()) {
            do
                last++;
            while (state[last] || state[a[last]] == 1);
            now = last;
        } else
            now = q.front(), q.pop();

        if (state[now])
            continue;

        state[now] = 1, ok++;

        if (state[a[now]] == 1) {
            std::cout << -1;
            return 0;
        }

        if (!state[a[now]]) {
            if (!--cnt[a[a[now]]])
                q.push(a[a[now]]);
            state[a[now]] = 2, ok++;
        }

        if (ok == n)
            break;
    }
    
    std::cout << std::count(state.begin(), state.end(), 1) << '\n';
    for (int i = 1; i <= n; i++)
        if (state[i] == 1)
            std::cout << a[i] << ' ';

    return 0;
}
```

---

## 作者：Spouter_27 (赞：2)

看到下标与值有关状物不要慌，首先往建图方面想。将下标向值连边，可以得到一个内向基环树森林。

题目所求相当于选择一些点，对于任意一个点 $ u $  满足下列两个条件**恰好一个**：

1. $ u $ 被选择。

2. 存在一个 $ v $ 连向 $ u $ 且 $ v $ 被选择。

分类讨论：

1. 单独的环：如果长为奇数，无解。否则交替选择。

2. 其他情况：首先对于基环树的叶子节点肯定要选择，那么该节点的父节点就不能被选择。如果一个节点的所有儿子都未被选择，那么该节点就要被选择。这样往上不断删叶子，最终可以归到只剩一个环的情况。对于这个环，如果有一个节点拥有至少一个儿子被选择，那么一定有解。否则如果环长为奇数，无解。

最后把选择的点从小到大排序，依次输出上面的值就好了。

理清思路，注意细节，实际写起来还是很顺畅的。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
#define deb(x) cerr<<"Line: "<<__LINE__<<", "<<#x<<" = "<<x<<"; \n"
#define pii pair<ll,ll>
#define mp make_pair
#define fi first
#define se second
const ll N=2e5+10;
inline ll read(){
	ll a=0,x=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	x=-x;
		c=getchar();
	}
	while(isdigit(c)){
		a=a*10+c-'0';
		c=getchar();
	}
	return a*x;
}
ll n,a[N];
vector<ll> ans;
ll du[N],vis2[N];
ll vis[N];
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		du[a[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(du[i]==0&&vis[i]==0){
			vis[i]=1;
			ll nw=i;
			while(du[nw]==0){
				vis2[nw]=1;
				if(vis[nw]==1)	ans.push_back(nw);
				du[a[nw]]--;
				if(!vis[a[nw]]){
					if(du[a[nw]]==0){
						vis[a[nw]]=-vis[nw];
					}
					else{
						if(vis[nw]==1)
							vis[a[nw]]=-vis[nw];
					}					
				}
				nw=a[nw];
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis2[i]&&vis[i]==-1){
			ll nw=i;
			while(vis[a[nw]]==0){
				vis[a[nw]]=-vis[nw];
				nw=a[nw];
				if(vis[nw]==1)	ans.push_back(nw);
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(vis[i]==0){
			ll nw=i;
			vis[nw]=1;ans.push_back(nw);
			while(vis[a[nw]]==0){
				vis[a[nw]]=-vis[nw];
				nw=a[nw];
				if(vis[nw]==1)	ans.push_back(nw);
			}
			if(vis[nw]==vis[a[nw]]){
				puts("-1");
				return 0;
			}
		}
	}
	sort(ans.begin(),ans.end());
	cout<<ans.size()<<endl;
	for(unsigned i=0;i<ans.size();i++){
		printf("%lld ",a[ans[i]]);
	}
	return 0;
}
```

spirua 可爱捏。

---

## 作者：shinkuu (赞：1)

有消愁赛时半天不会，赛后一发过了，长度还是原来的一半。怎么会是呢/kk

首先整理一下条件：

- 如果一个点 $i$ 没有被选

则没有一个没被选的点 $j$ 满足 $a_j=i$。

- 如果一个点 $i$ 被选

则存在一个没被选的点 $j$ 满足 $a_j=i$。

则我们可以发现：

- 如果一个点 $i$ 满足 $\not\exists j,a_j=i$，则这个点一定不被选。

- 如果一个点 $i$ 满足 $\exists j,a_j=i$ 且 $j$ 不被选，则这个点一定可以被选，可以直接贪心地选这个点。

- 否则这个点选不选都可以，先空着。

注意一定不要提前确定空着的点的装态，不然环上判断无解可能很麻烦或者出问题。

容易发现这样可以让 $i\to a_i$ 连边，组成内向基环树森林，先处理不在环上的，可以简单 topo。topo 到一个空着的点，则令它不选。然后环上再分类讨论：

- 该环已经至少有一个位置是强制要选

则从这个点开始推环上的答案。

- 否则

设任意一个点不选并推环上答案。

容易发现，如果此时环上相邻两个点被选的情况一样，则一定不满足条件。

否则输出答案即可。

code：

```cpp
int n,m,e[N],col[N],in[N];
bool vis[N];
queue<int> q;
void dfs(int u){
	int v=e[u];
	if(col[v]&&col[u]==1&&col[v]==1){
		puts("-1");
		exit(0);
	}
	vis[u]=true;
	if(vis[v])
		return;
	if(!col[v])
		col[v]=3-col[u];
	dfs(v);
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n){
		scanf("%d",&e[i]);
		in[e[i]]++;
	}
	rep(i,1,n){
		if(!in[i]){
			col[i]=1;
			q.push(i);
		}
	}
	while(q.size()){
		int u=q.front();
		q.pop();
		vis[u]=true;
		if(!col[u])col[u]=1;
		int v=e[u];
		if(col[u]==1)col[v]=2;
		if(!--in[v])q.push(v);
	}
	rep(i,1,n){
		if(!vis[i]&&col[i]==2)
			dfs(i);
	}
	rep(i,1,n){
		if(!vis[i]){
			col[i]=1;
			dfs(i);
		}
	}
	int ans=0;
	rep(i,1,n){
		ans+=col[i]==1;
	}
	printf("%d\n",ans);
	rep(i,1,n){
		if(col[i]==1)
			printf("%d ",e[i]);
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

这波是连绿都不会了，难绷。

---

## 作者：Graphcity (赞：1)

由于画圈的顺序并不影响最后剩下的数字，所以只需要满足画圈的下标可重集 $\{p\}$ 和剩下的数字可重集 $\{b\}$ 相同就行了。

我们考虑连一条 $a_i\to i$ 的有向边。对于每条边，如果选择一次会使 $b$ 中删去一个 $a_i$，$p$ 中加入一个 $i$；之后再选择就只会往 $p$ 中加入一个 $i$。

设 $c_i$ 为序列中 $i$ 的出现次数。显然 $b$ 中删去 $i$ 的次数加上 $p$ 中加入 $i$ 的次数要等于 $c_i$。我们对每条边的效果做出如下转化：$x\to y$ 的边第一次被选时，$c_x\gets c_x-1,c_y\gets c_y-1$。如果之后再被选，仅有 $c_y\gets c_y-1$。最终我们要求 $\forall i\in [1,n],c_i=0$。

显然每个点的入度恰好为 1，所以这张图是一棵 **外向基环树森林**。我们依次对森林中每一棵基环树做判定：

先把基环树中所有环边去掉。对于每棵树，我们按照深度从深往浅考虑。考虑到点 $x$ 时，如果 $c_x>0$，则选择一次 $a_x\to x$ 的边。如果依然有 $c_x>0$，则继续选择它，直到 $c_x$ 变成零为止。如果在过程中出现 $c_x<0$，则构造失败。

接着考虑每个环点。我们进行分类讨论：

1. **存在环点 $x$ 满足 $c_x\ge 2$**：显然 $x\to fa_x$ 的边必选。我们先选一次，然后把这条边断开，再按照先前树的方法把整个环做掉。做完之后如果还有 $c_x>0$，那就继续选 $x\to fa_x$ 的边直到 $c_x=0$。
2. **否则，存在环点 $x$ 满足 $c_x=0$**：首先整张环的 $c$ 都不超过 1，所以每条边至多选一次。对于 $c_x=0$ 的点 $x$，显然跟它相连的任何边都不能选。于是把这个点删掉，然后按照树的方法去做。
3. **如果前两条均不满足，此时对于任意环点 $x$ 都有 $c_x=1$**：如果环长为偶数，交替选边即可；如果是奇数，则构造失败。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=4e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,a[Maxn+5],fa[Maxn+5],chk[Maxn+5];
int m,h[Maxn+5],c[Maxn+5];
vector<int> ans,v[Maxn+5];

inline int pre(int x) {return x==1?m:x-1;}
inline void dfs(int x)
{
    if(c[x]<0) {printf("-1\n"); exit(0);}
    for(auto y:v[x]) if(!chk[y]) dfs(y);
    if(c[x]<0) {printf("-1\n"); exit(0);}
    if(chk[x]) return;
    if(c[x]>0) ans.push_back(x),c[x]--,c[fa[x]]--;
    while(c[x]>0) ans.push_back(x),c[x]--;
}
inline void Print()
{
    static int vis[Maxn+5];
    for(auto i:ans) vis[i]=1;
    cout<<ans.size()<<endl;
    For(i,1,n) if(!vis[i]) printf("%d ",a[i]); printf("\n");
}
inline void Solve()
{
    For(i,1,m) dfs(h[i]);
    For(id,1,m)
    {
        int x=h[id]; if(c[x]<2) continue;
        c[x]--,c[fa[x]]--,ans.push_back(x);
        for(int i=pre(id);i!=id;i=pre(i))
        {
            int a=h[i]; if(c[a]<0) {printf("-1\n"); exit(0);}
            if(c[a]>0) ans.push_back(a),c[a]--,c[fa[a]]--;
            while(c[a]>0) ans.push_back(a),c[a]--;
        }
        if(c[x]<0) {printf("-1\n"); exit(0);}
        while(c[x]>0) ans.push_back(x),c[x]--;
        return;
    }
    For(i,1,m) h[i+m]=h[i];
    For(id,1,m)
    {
        int x=h[id]; if(c[x]) continue;
        for(int l=id+1,r;l<=id+m;l=r+1)
        {
            if(c[h[l]]) {r=l; continue;}
            for(r=l;r<id+m && c[h[r+1]];++r);
            if(r-l+1&1) {printf("-1\n"); exit(0);}
            for(int i=l+1;i<=r;i+=2) ans.push_back(h[i]);
        }
        return;
    }
    if(m&1) {printf("-1\n"); exit(0);}
    for(int i=2;i<=m;i+=2) ans.push_back(h[i]);
}
inline void Topo()
{
    static int deg[Maxn+5]; queue<int> q;
    For(i,1,n) deg[fa[i]]++;
    For(i,1,n) if(!deg[i]) q.push(i);
    while(!q.empty())
    {
        int x=q.front(); q.pop();
        if(--deg[fa[x]]==0) q.push(fa[x]);
    }
    For(i,1,n) if(deg[i] && !chk[i])
    {
        m=0; for(int j=i;!chk[j];j=fa[j]) h[++m]=j,chk[j]=1;
        reverse(h+1,h+m+1); Solve();
    }
}

int main()
{
    n=read();
    For(i,1,n) v[a[i]=read()].push_back(i),fa[i]=a[i],c[a[i]]++;
    Topo(),Print();
    return 0;
}
```



---

## 作者：piggy123 (赞：0)

小丑码力做法。

首先 $i\to a_i$ 连边。显然条件等价于选择一个点的子集满足，使得任一点 $i$ 均满足以下两点之一：

1. $i$ 被选择。
2. 存在 $j$ 与 $j\to i$ 使得 $j$ 被选择。

由于每个点的出度为 $1$。所以这个图是一个基环内向森林，我们可以考虑使用基环树 DP 来解决这个问题。

对于每一个基环树连通块，我们找出环，对于环上每个点的子树做一遍树形 DP $dp_{i,0/1}$表示 $i$ 是否可以不选、选。最后汇总到环上再做一遍 DP 计算是否可以染色，这是容易的。

注意两个 DP 都需要记录方案，所以代码非常狮山，是最短解的十倍多。

Submission： [link](https://codeforces.com/contest/1876/submission/227197252)

---


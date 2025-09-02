# [JOIGST 2025] 茶话会 / Tea Party

## 题目描述

葵计划举办一场茶话会，共有包括葵在内的 $M$ 位参与者，编号为 $1$ 到 $M$。葵打算给每位参与者分发一块蛋糕和一杯红茶。

为此，葵准备了 $N$ 块蛋糕（编号 $1$ 到 $N$）和 $M$ 杯红茶（编号 $1$ 到 $M$），其中 $N \geq M$。蛋糕 $i$（$1 \leq i \leq N$）的品牌是 $A_i$，美味度是 $B_i$。红茶 $j$（$1 \leq j \leq M$）的品牌是 $C_j$，美味度是 $D_j$。

葵希望通过合理分配蛋糕和红茶，最大化所有参与者的**幸福度总和**。

分配规则如下：

葵会从 $N$ 块蛋糕中选择 $M$ 块分配给参与者（剩余蛋糕由葵在其他时间食用，不影响幸福度）。当参与者获得蛋糕 $i$ 和红茶 $j$ 时，其幸福度计算方式为：

- 若蛋糕与红茶品牌相同（$A_i = C_j$），则幸福度为 $B_i + D_j$。
- 若品牌不同（$A_i \neq C_j$），则幸福度为 $B_i$。

请计算通过优化分配蛋糕和红茶，所有参与者幸福度总和的最大值。

## 说明/提示

#### 【样例解释 #1】

葵可以按以下方式分配蛋糕和红茶，使所有参与者的幸福度总和达到最大值 $12$：

-   参与者 $1$ 获得蛋糕 $1$ 和红茶 $1$，幸福度为 $2 + 3 = 5$。
-   参与者 $2$ 获得蛋糕 $3$ 和红茶 $3$，幸福度为 $2 + 1 = 3$。
-   参与者 $3$ 获得蛋糕 $4$ 和红茶 $2$，幸福度为 $4$。

无论如何分配，所有参加者的幸福度总和都不会超过 $12$，因此输出 $12$。

该样例满足子任务 $4$ 的限制。

#### 【样例解释 #2】

该样例满足子任务 $3,4$ 的限制。

#### 【样例解释 #3】

该样例满足子任务 $1,4$ 的限制。

#### 【样例解释 #4】

该样例满足子任务 $2,4$ 的限制。

#### 【数据范围】

-   $1 \leq M \leq N \leq 200\,000$。
-   $1 \leq A_i \leq N$（$1 \leq i \leq N$）。
-   $0 \leq B_i \leq 10^9$（$1 \leq i \leq N$）。
-   $1 \leq C_j \leq N$（$1 \leq j \leq M$）。
-   $0 \leq D_j \leq 10^9$（$1 \leq j \leq M$）。
-   输入的所有值都是整数。

#### 【子任务】

1.  （$8$ 分）$D_j = 0$（$1 \leq j \leq M$）。
2.  （$19$ 分）$B_i = 0$（$1 \leq i \leq N$）。
3.  （$31$ 分）$A_i = i$（$1 \leq i \leq N$），$C_j = j$（$1 \leq j \leq M$）。
4.  （$42$ 分）无附加限制。

## 样例 #1

### 输入

```
4 3
1 1 2 3
2 1 2 4
1 1 2
3 1 1```

### 输出

```
12```

## 样例 #2

### 输入

```
5 3
1 2 3 4 5
4695 53325 57544 74342 81986
1 2 3
59037 23296 16434```

### 输出

```
232949```

## 样例 #3

### 输入

```
4 3
2 1 3 1
52 49 72 31
3 1 3
0 0 0```

### 输出

```
173```

## 样例 #4

### 输入

```
5 2
1 1 2 3 5
0 0 0 0 0
1 1
3 1```

### 输出

```
4```

# 题解

## 作者：Mindulle (赞：3)

本题考点：
- 贪心
- 排序
- 优先队列（不用也可以，只是比较方便）

很明显，我们优先选择相同类型的进行匹配。但可能会存在一种情况，即有一些价值很高的蛋糕没办法和其它的进行匹配，但其价值比匹配的还要高。我们可以先把匹配得到的价值存储起来，接着再存储单独一个蛋糕所得到的价值，最后求最大的 $m$ 项即可。

避免再次排序，可以使用优先队列解决。优先队列默认为大根堆，直接用就行了。

参考代码：（注：代码中的 $n$ 和 $m$ 和题目描述是相反的。）

- 数组排序比较函数：类型不同，编号小的优先；类型相同，价值大的优先。
```cpp
bool cmp(node x,node y){
    if(x.kind!=y.kind) return x.kind<y.kind;
	return x.val>y.val;
}
```

- 贪心：
```cpp
stable_sort(a+1,a+m+1,cmp); stable_sort(b+1,b+n+1,cmp);
priority_queue<int,vector<int>> pq;
for(i=1,j=1;i<=n and j<=m;i++){
  while(a[j].kind<b[i].kind and j<=m) pq.push(a[j].val),j++;
  if(a[j].kind==b[i].kind) pq.push(a[j].val+b[i].val),j++;
}
for(;j<=m;j++) pq.push(a[j].val);
for(i=1;i<=n;i++) ans+=pq.top(),pq.pop();
```

注意数据范围。

---

## 作者：zhangkerui2012 (赞：3)

呃···贪心的裸体。。

# 主体思想：排序+贪心
这道题是一道贪心的裸题，主体思想就是排序。。
## 题目大意
这个题的题目大意就是给几个带有权值的点，然后让你求能获得的最大效益是多少。
## 思路
我们不妨用一个结构体存储每一个点和他的权值（用结构体方便排序），然后对给定的第一组点权进行排序。
设 $ f_{i} $ 为 **第二组点中 第 $ i $ 种品牌有多少个** ，用一个大根堆（优先队列） $ q_{i} $ 来记录 **第二组点第 $ i $ 种品牌的所有点权** ，然后把第一组的点权对应加上 $ q_i $ 队首，最后再让队首出队

干说可能没法理解，这里先奉上部分代码
```cpp
cin>>n>>m;
for(int i=1;i<=n;i++)cin>>b[i].p;
for(int i=1;i<=n;i++)cin>>b[i].w;
for(int i=1;i<=m;i++）{cin>>a[i].p;f[a[i].p]++;} // f[i] 表示第二组点第 i 种品牌有多少个
for(int i=1;i<=m;i++）{cin>>a[i].w;q[a[i].p].push(a[i].w);} // 将第二组的点权加入队列
//以上是输入
stable_sort(b+1,b+n+1,cmp); // 将第一组点按照点权从大到小进行排序
for(int i=1;i<=n;i++)
{
	if(f[b[i].p]) // 如果有这种品牌的
	{
		f[b[i].p]--; // 他自己要占用一个这种品牌，所以这种品牌数要减
		b[i].w+=q[b[i].p].top(); //  加上目前最大的点权
		q[b[i].p].pop(); // 最大的点权已经用完了，所以要出队
	}
}
```
```
bool cmp(Node x,Node y)
{
	return x.w>y.w;  // 排序函数，没啥好说的
}
```
这些处理完之后呢？答案怎么求？
先不要急，由于我们把第二组的点权加到相应的第一组的点权上了，所以这里还需要进行一次排序
```cpp
stable_sort(b+1,b+n+1,cmp);
```
最后只需要枚举到 $ \min (n,m) $ 把第一组的点权加上就可以了

## 完整代码
一份方便 ~~复制~~ 的代码
```cpp
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#define int long long
using namespace std;
const int N=2e5+10;
struct Node{  // 结构体存点更具有魅力。。。
	int p;
	int w;
}a[N],b[N];
int n,m,ans;
int f[N];
bool cmp(Node x,Node y)
{
	return x.w>y.w;
}
priority_queue<int,vector<int>,less<int> >q[N]; // 大根队记录第二组点权
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);  // 可以让 cin 和 cout 变快，是一个小优化
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>b[i].p;
	for(int i=1;i<=n;i++)cin>>b[i].w;
	for(int i=1;i<=m;i++){cin>>a[i].p;f[a[i].p]++;}
	for(int i=1;i<=m;i++){cin>>a[i].w;q[a[i].p].push(a[i].w);}
	stable_sort(b+1,b+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		if(f[b[i].p])
		{
			f[b[i].p]--;
            b[i].w+=q[b[i].p].top();
			q[b[i].p].pop();
		}
	}
	stable_sort(b+1,b+n+1,cmp);
	for(int i=1;i<=min(n,m);i++)ans+=b[i].w; // 加上点权
	cout<<ans;
	return 0;
}
```
蒟蒻题解，不喜轻喷

---

## 作者：2023z (赞：2)

~~玄学题目~~

### 题意简述

有 $ n $ 块蛋糕，$ m $ 杯红茶，要分给 $ m $ 个人，每块蛋糕都有一个品牌 $ a_i $ 和美味度 $ b_i $，每杯红茶也有一个品牌 $ c_i $ 和美味度 $ d_i $。使得分完之后的**幸福度总和**最大化。

幸福度的计算法则如下：

- 如果分配到一个人的蛋糕和红茶品牌相同，则这个人的幸福度为蛋糕和红茶的美味度总和，即如果 $ a_i = c_i $，幸福度为 $ b_i + d_i $。

- 如果分配给这个人的蛋糕与红茶品牌不同，幸福度就为蛋糕的美味度，即如果 $ a_i \ne c_i $，幸福度为 $ b_i $。

### 思路

第一眼这不就普普通通贪心吗？用我的顶级思路做。首先肯定是要把那些品牌相同的蛋糕和红茶匹配的，我们要最大化幸福度总和，所以要把相同品牌那些蛋糕和红茶美味度比较大的匹配到一组，这样才能保证最大，那我就先按照编号和美味度分别给蛋糕喝红茶排序，品牌编号小的在前面，品牌编号相同就把美味度更大的放在前面。排好序后就从 $ 1 $ 到 $ n $ 去枚举蛋糕，用变量 $ j $ 表示红茶选到了第几个，让每一个蛋糕去找一个与它相同品牌的红茶，如果当前红茶的品牌与它相同，就直接匹配，然后 `b[i] += d[j]`，且 $ j $ 加一，否则因为我们是按品牌编号从小到大排序的，那前面就不可能和现在的编号匹配了，因为前面的编号更小，所以就没变化。最后再对蛋糕从大到小排个序，统计前 $ m $ 个幸福度总和输出，于是我兴致勃勃写了一份代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node {
    int s, id;
}; // s 表示美味度，id 表示品牌
int n, m, ans; // ans 是答案
node a[200010], b[200010]; // a 数组是蛋糕，b 是红茶
bool cmp1(node a, node b) { //按编号排序
    if (a.id != b.id) return a.id < b.id;
    return a.s > b.s;
}
bool cmp2(node a, node b) { //从大到小排序
    return a.s > b.s;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].id;
    }
    for (int i = 1; i <= n; i++) cin >> a[i].s;
    for (int i = 1; i <= m; i++) cin >> b[i].id;
    for (int i = 1; i <= m; i++) cin >> b[i].s;
    sort(a + 1, a + n + 1, cmp1);
    sort(b + 1, b + m + 1, cmp1); //排序
    int j = 1; // j 表示红茶选到了第 j 个
    for (int i = 1; i <= n; i++) {
        if (j > m) break; //已经把 m 个红茶分配完了
        if (a[i].id == b[j].id) { //品牌相同就分配
            a[i].s += b[j].s; //把它加进蛋糕的美味度里，好排序
            j++;
        }
    }
    sort(a + 1, a + n + 1, cmp2); //对分配好的数组进行排序
    for (int i = 1; i <= m; i++) {
        ans += a[i].s; //统计答案，选前 m 个
    }
    cout << ans << endl;
    return 0;
}
```

交上去发现 39pts，炸了。

[评测记录](https://www.luogu.com.cn/record/231997014)

看来这个思路好像有问题。~~我又要开始动用我神奇的脑子了~~。

我们来看这段代码：

```cpp
for (int i = 1; i <= n; i++) {
    if (j > m) break; //已经把 m 个红茶分配完了
        if (a[i].id == b[j].id) { //编号相同就分配
            a[i].s += b[j].s; //把它加进蛋糕的美味度里，好排序
            j++;
        }
    }
```

仔细想想，这里有什么问题？

如果这里的 $ a_i.id > b_i.id $  怎么办，是不是后面的 $ a_i.id $ 都大于当前 $ b_j.id $ 了，于是就算后面的 $ b_j.id $ 有符合条件的都不会被匹配了，所以这里出现了问题。

那我们来换个思路，因为这些东西要分给 $ m $ 个人，既然红茶有正好 $ m $ 杯，那我们就去给每杯红茶找符合条件的蛋糕。

如果我们排好序之后用暴力去枚举肯定不行，会超时 $ 1 \leq m \leq n \leq 2 \times 10^5 $，所以要另寻~~死~~其路。假设我们现在已经排好序了，要相匹配的更优，我们知道，要在同样品牌下选择美味度更大的蛋糕，我们的排序方案不仅按品牌从小到大了，而且同品牌也从大到小排序了，所以我们可以用一个 vector 来存每个品牌的每个蛋糕的下标，按美味度从大到小存（方便直接取出来用），也就是从后往前存（前文说了，同品牌下的蛋糕是按照从大到小排序的，vector 每次只能弹出最后一个元素，我们要优先美味度更大的蛋糕）。

存好后，再枚举每一杯红茶，看这个品牌的蛋糕有没有，有就直接匹配（注意是把红茶的美味度加进蛋糕里，方便后面排序），其他地方都没有区别。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node {
    long long s, id;
};
long long n, m, k, ans;
node a[200010], b[200010];
vector<long long> id[200010]; // id 是每个品牌的每个蛋糕的下标
bool cmp1(node a, node b) {
    if (a.id != b.id) return a.id < b.id;
    return a.s > b.s;
}
bool cmp2(node a, node b) {
    return a.s > b.s;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i].id;
    for (int i = 1; i <= n; i++) cin >> a[i].s;
    for (int i = 1; i <= m; i++) cin >> b[i].id;
    for (int i = 1; i <= m; i++) cin >> b[i].s;
    sort(a + 1, a + n + 1, cmp1);
    sort(b + 1, b + m + 1, cmp1);
    for (int i = n; i >= 1; i--) {
        id[a[i].id].push_back(i); //把这个品牌的蛋糕加进去
    }
    for (int i = 1; i <= m; i++) {
        if (id[b[i].id].size()) { //如果有这个品牌的蛋糕
            a[id[b[i].id].back()].s += b[i].s; //相应的蛋糕美味度加上红茶的美味度
            id[b[i].id].pop_back(); //记得弹出
        }
    }
    sort(a + 1, a + n + 1, cmp2);
    for (int i = 1; i <= m; i++) {
        ans += a[i].s;
    }
    cout << ans << endl;
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/231976336)

说实话好想把品牌写成编号，编号顺口一点 qwq。

---

## 作者：qzyz_ymh (赞：1)

题意非常简单，不做赘述。

相信大家一看题目就知道该怎么打了吧，~~不懂的看一眼标签就懂了~~。

明显的贪心，我们对于每个 $C_i$ 都去找他对应的 $B_i$ 最大的 $A_i$，那这边每组幸福度就是 $D_i + B_i$，再找一下没人要的 $A_i$，这里的幸福度是 $B_i$，最后统计一下前 $m$ 大的加上就好了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N = 1e8 + 10;
struct Node {
	int a, b;
} x[N], y[N];
int ans[N];
bool cmp(Node g, Node h) {
	if (g.a == h.a) {
		return g.b > h.b;
	}
	return g.a < h.a;
}
bool f[N];
signed main() {
	std::cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> x[i].a;
	}
	for (int i = 1; i <= n; i++) {
		cin >> x[i].b;
	}
	for (int i = 1; i <= m; i++) {
		cin >> y[i].a;
	}
	for (int i = 1; i <= m; i++) {
		cin >> y[i].b;
	}
	sort(x + 1, x + n + 1, cmp);
	sort(y + 1, y + m + 1, cmp);
	int tot = 0, j = 1;
	for (int i = 1; i <= m; i++) {
		if (x[j].a < y[i].a) {
			while (x[j].a < y[i].a) {
				j++;
				if (j > n) {
					break;
				}
			}
		}
		if (j > n) {
			break;
		}
		if (x[j].a == y[i].a) {
			tot++;
			ans[tot] = x[j].b + y[i].b;
			f[j] = 1;
			j++;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (f[i] == 0) {
			tot++;
			ans[tot] = x[i].b;
		}
	}
	sort(ans + 1, ans + tot + 1);
	int ans1 = 0;
	for (int i = tot; i > tot - m; i--) {
		ans1 += ans[i];
	}
	cout << ans1;
	return 0;
}
```

---

## 作者：_Hzq_ (赞：1)

### 题解：P13737 [JOIGST 2025] 茶话会 / Tea Party
#### 分析题意
每杯红茶都会分给一个客人，当蛋糕和红茶是一个品牌时客人获得的幸福度是 $b_i+d_j$，不同品牌时获得的幸福度为 $b_i$，求问如何分配蛋糕使得客人获得的总幸福度最高。
#### 具体做法
考虑贪心，可以分以下情况，可以发现，我们可以优先将相同品牌的美味值最大蛋糕和红茶匹配，取得一个总价值 $val$，但很容易发现，有可能有蛋糕无法被匹配，但美味值极高，那么要如何处理呢？我们只需将能匹配的按美味值从大到小优先匹配，把价值放入数组中，再把未能匹配的蛋糕的美味值也单独存进数组中，最后把数组排序，将前 $n$ 项相加即可。  
由于涉及依次放入数组，这里推荐一种数据结构——优先队列（有类似vector的插入操作，还能自动排序），具体用法见[oi-wiki](http://oi-wiki.com/lang/csl/container-adapter/#%E4%BC%98%E5%85%88%E9%98%9F%E5%88%97)。~~用set也可以。~~
#### Code
```cpp line-numbers
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+7;
struct node
{
	int kind,val;
}a[N],b[N];
struct cmp1
{
	bool operator()(int &x,int &y)
	{
		return x<y;
	}
};
int n,m,ans;
bool cmp(node x,node y)
{
	return x.kind<y.kind||(x.kind==y.kind&&x.val>y.val);
}
signed main()
{
	cin >> m >> n;
	int i,j,k;
	for(i=1;i<=m;i++) scanf("%d",&a[i].kind);
	for(i=1;i<=m;i++) scanf("%d",&a[i].val);
	for(i=1;i<=n;i++) scanf("%d",&b[i].kind);
	for(i=1;i<=n;i++) scanf("%d",&b[i].val);
	sort(a+1,a+1+m,cmp);
	sort(b+1,b+1+n,cmp);
	priority_queue<int,vector<int>,cmp1> q;
	for(i=1,j=1;i<=n&&j<=m;i++)
	{
		while(a[j].kind<b[i].kind&&j<=m) q.push(a[j].val),j++;
		if(a[j].kind==b[i].kind) q.push(a[j].val+b[i].val),j++;
	}
	for(;j<=m;j++) q.push(a[j].val);
	for(i=1;i<=n;i++) ans+=q.top(),q.pop();
	cout << ans << endl;
	return 0;
}
```

---

## 作者：_qhbd_ (赞：0)

# 题意
$N$ 块蛋糕，$M$ 杯红茶，蛋糕有值 $A_i,B_i$，红茶有值 $C_i,D_i$。选择 $M$ 块蛋糕与红茶一一配对，蛋糕 $i$ 贡献 $B_i$，若配对的蛋糕 $i$ 与红茶 $j$ 满足 $A_i=C_j$，额外贡献 $D_j$。

$M\le N\le2\times10^5$ 求最大贡献。
# 思路
考虑没有额外贡献的情况，每次贪心地取 $B$ 值更大的蛋糕更优。但本题不能采取此策略，因为蛋糕被选可能不止贡献 $B$，那么若可以明确所有蛋糕被选贡献，也就可以贪心了。 

显然，所有红茶都会被选取。于是我们这样设计，对于一块蛋糕 $i$，选取它贡献为 $B_i$，再加上 $A_i$ 对应可选取红茶 $D$ 最大值（若没有对应的红茶等效于加上 $0$）。

我们已经确定所有蛋糕被选取的贡献了，每次贪心地取贡献最大的蛋糕，统计最大贡献。注意每次选取蛋糕过后其
他蛋糕原本的贡献可能改变，一边取值一边维护即可。

具体维护使用优先队列维护不同种类 $A,C$ 值对应 $B,D$ 值，再额外开一个优先队列维护蛋糕被选贡献，每次取出一个蛋糕，再加入一个和它 $A$ 相同的蛋糕。注意每次加入蛋糕时，删除对应配对的红茶。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while('0'>ch||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,A[N],C[N];
priority_queue<int>q[N],Q[N];
priority_queue<pair<int,int>>qwq;
inline int q_top(int x){
	if(q[x].empty())return 0;
	int tmp=q[x].top();
	q[x].pop();
	return tmp;
}
long long ans;
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)A[i]=read();
	for(int i=1;i<=n;i++)Q[A[i]].push(read());
	for(int i=1;i<=m;i++)C[i]=read();
	for(int i=1;i<=m;i++)q[C[i]].push(read());
	for(int i=1;i<=n;i++)
		if(!Q[i].empty()){
			qwq.push({Q[i].top()+q_top(i),i});
			Q[i].pop();
		}
	while(m--){
		ans+=qwq.top().first;
		int i=qwq.top().second;
		qwq.pop();
		if(!Q[i].empty()){
			qwq.push({Q[i].top()+q_top(i),i});
			Q[i].pop();
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：MspAInt (赞：0)

~~这题没有题解，却是一个比较经典的贪心。~~

多次摸索后可以得到一个类似于反悔贪心的做法：

先将红茶按权值降序排序，依次匹配权值最大的同品牌蛋糕。若无法匹配则暂时丢掉。现在剩下一些蛋糕和红茶。

然后，开始反悔。对于每个红茶 $i$，都有目前的答案 $z_i=b_j+d_i$ 或 $z_i=0$。若将匹配的蛋糕 $j$ 改为 $k$，则答案增加 $b_k-z_i$。

将剩余的蛋糕按权值降序排序，红茶按 $z$ 升序排序，依次匹配。若 $b_k-z_i\le0$ 则退出。

:::info[是否有 $k,i$ 匹配的情况？]
事实上，若 $k,i$ 匹配，必然有 $b_k+d_i\le b_j+d_i$，即更劣。否则 $i$ 在初始时应与 $k$ 匹配，与 $j,i$ 匹配的假设矛盾。因此无视此情况。
:::

:::success[代码]
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int n,m;
struct node{int x,y,z;}a[N],b[N];
vector<int>h[N];
multiset<int,greater<int>>s;
long long ans;

signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i].x);
	for(int i=1;i<=n;i++)scanf("%d",&a[i].y),s.insert(a[i].y);
	for(int i=1;i<=m;i++)scanf("%d",&b[i].x);
	for(int i=1;i<=m;i++)scanf("%d",&b[i].y);
	sort(a+1,a+n+1,[](node p,node q){return p.y<q.y;});
	for(int i=1;i<=n;i++)h[a[i].x].push_back(a[i].y);
	sort(b+1,b+m+1,[](node p,node q){return p.y>q.y;});
	for(int i=1;i<=m;i++){
		int X=b[i].x,Y=b[i].y;
		if(h[X].size())b[i].z=Y+h[X].back(),s.erase(s.find(h[X].back())),h[X].pop_back();
		else b[i].z=0;
		ans+=b[i].z;
	}
	sort(b+1,b+m+1,[](node p,node q){return p.z<q.z;});
	for(int i=1;i<=m;i++){
		int p=*s.begin();
		if(p<=b[i].z)break;
		ans+=p-b[i].z;
		s.erase(s.begin());
	}
	printf("%lld\n",ans);
	return 0;
}
```
:::

---

## 作者：Circle_Table (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13737)

### 题意简述：

现有 $n$ 块蛋糕分给 $m$ 个人，另外给每人分一杯茶，如果蛋糕和茶品牌一样则茶的美味度为 $D$ 否则为 $0$。蛋糕的美味度为 $B$ 且不与其他因素相关，求分完后的美味度最大值。

### 思路：

可见蛋糕是供大于求，不一定能分完的，所以要有选择的分。分蛋糕时既要考虑其本身的美味度又要考虑能否与茶品牌相同而匹配。

由于茶不会有剩余，因此我们将美味度较高的茶优先与美味度较高的蛋糕匹配，直接修改蛋糕的美味度后对其再进行排序，将蛋糕修改后美味度前 $n$ 的相加即可。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register int
#define ios ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int N=200085;

int n,m,x=1,ans;

struct node
{
	int id,v;  // id是品牌编号,v是美味度 
}a[N],b[N];

bool cmp(node u,node v)
{
	if(u.id==v.id)return u.v>v.v; // 同样的品牌优先选美味度高的 
	return u.id<v.id;
}

bool cmpv(node u,node v)
{
	return u.v>v.v;
}

signed main()
{
	ios;cin>>n>>m;
	for(ri i=1;i<=n;i++)
	{
		cin>>a[i].id;
	}
	for(ri i=1;i<=n;i++)
	{
		cin>>a[i].v;
	}
	for(ri i=1;i<=m;i++)
	{
		cin>>b[i].id;
	}
	for(ri i=1;i<=m;i++)
	{
		cin>>b[i].v;
	}
	
	// 依据品牌编号排序,便于修改蛋糕的美味度 
	sort(a+1,a+1+n,cmp);
	sort(b+1,b+1+m,cmp);
	
	// 遍历所有蛋糕,同时用x指针遍历红茶
	for(ri i=1;i<=n&&x<=m;i++)
	{
		if(a[i].id<b[x].id)continue; // 蛋糕<红茶,无法匹配,跳过该蛋糕
		while(x<=m&&a[i].id>b[x].id)x++; // 蛋糕>红茶,移动红茶指针找同品牌
		if(x<=m&&a[i].id==b[x].id)a[i].v+=b[x++].v; //如果相等则进行修改 
	}
	
	// 依据美味度排序,从而求和
	sort(a+1,a+1+n,cmpv);
	
	for(ri i=1;i<=m;i++)
	{
		ans+=a[i].v;
	}
	cout<<ans;
	
	return 0;
}
```

完结撒花花！

---

## 作者：szh_AK_all (赞：0)

首先假设我们已经从这 $N$ 块蛋糕了选出了 $M$ 块，那分配时肯定是尽可能让品牌相同的蛋糕和红茶放在一起。所以我们先将能分配在一起的蛋糕和红茶放在一起，此时还剩下一些单独的蛋糕，将分配在一起的蛋糕和红茶按照幸福度从大到小排序，那么选取的分配在一起的蛋糕和红茶肯定是一个前缀，余下的就从单独的蛋糕里选幸福度最大的几个即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int>g[200005];
int now[200005];
int a[200005], b[200005], c[200005], d[200005];
struct node {
    int b, d;
    node(int aa = 0, int bb = 0) {
        b = aa;
        d = bb;
    }
    friend bool operator< (node l, node r) {
        return l.b + l.d > r.b + r.d;
    }
}s[200005];
struct no {
    int a, b;
    friend bool operator< (no l, no r) {
        return l.b > r.b;
    }
}ss[200005];
int tot;
multiset<int, greater<int>>s1, s2;
bool cmp(int x, int y) {
    return x > y;
}
signed main(){
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i], ss[i].a = a[i], ss[i].b = b[i];
    sort(ss + 1, ss + n + 1);
    for (int i = 1; i <= n; i++)
        a[i] = ss[i].a, b[i] = ss[i].b;
    for (int i = 1; i <= m; i++)
        cin >> c[i];
    for (int i = 1; i <= m; i++)
        cin >> d[i], g[c[i]].push_back(d[i]);
    for (int i = 1; i <= n; i++)
        sort(g[i].begin(), g[i].end(), cmp);
    int nw = 0;
    for (int i = 1; i <= n; i++) {
        s1.insert(b[i]);
        nw += b[i];
        if (s1.size() > m) {
            auto it = s1.end();
            it--;
            nw -= *it;
            s2.insert(*it);
            s1.erase(it);
        }
        if (now[a[i]] < g[a[i]].size())
            s[++tot] = node(b[i], g[a[i]][now[a[i]]]), now[a[i]]++;
    }
    sort(s + 1, s + tot + 1);
    int ans = nw, tmp = 0;
    for (int i = 1; i <= tot; i++) {
        tmp += s[i].b + s[i].d;
        if (s1.find(s[i].b) != s1.end())
            s1.erase(s1.find(s[i].b)), nw -= s[i].b;
        else
            s2.erase(s2.find(s[i].b));
        while (s1.size() < m - i) {
            if (!s2.size())
                break;
            auto it = s2.begin();
            s1.insert(*it);
            nw += *it;
            s2.erase(it);
        }
        while (s1.size() > m - i) {
            auto it = s1.end();
            it--;
            nw -= *it;
            s2.insert(*it);
            s1.erase(it);
        }
        ans = max(ans, tmp + nw);
    }
    cout << ans;
}
```

其实我写复杂了。

---

## 作者：queenbee (赞：0)

# P13737 [JOIGST 2025] 茶话会 / Tea Party 题解
## 思路
[题目传送门](https://www.luogu.com.cn/problem/P13737)，考虑先贪心保证匹配所有的 $A_i=C_i$ 保证所有能匹配的红茶都匹配，发现对于可以匹配的红茶，对与它同品牌的若干蛋糕的贡献是相同的，所以考虑将美味度从高到低匹配蛋糕和红茶，将匹配与未匹配的蛋糕美味度进行排序，选择前 $m$ 大的贡献到答案即可。
## 程序
```cpp
#include<bits/stdc++.h>	//我爱万能头 
using namespace std;
#define int long long
const int N=2e5+10;
int n,m;
struct Node{
	int a,b;
}x[N],y[N]; 
int ans;
priority_queue<pair<int,int> >q[N];	//丑陋的蛋糕美味值排序（笨办法） 
int a[N];
bool cmp(Node a,Node b){
	return a.b>b.b;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>x[i].a;
	}
	for(int i=1;i<=n;i++){
		cin>>x[i].b;
		q[x[i].a].push({x[i].b,i});
		a[i]=x[i].b;
	}	
	for(int i=1;i<=m;i++){
		cin>>y[i].a;
	}
	for(int i=1;i<=m;i++){
		cin>>y[i].b;
	}
	sort(y+1,y+m+1,cmp);
	for(int i=1;i<=m;i++){	//丑陋贪心 
		if(!q[y[i].a].empty()){
			int w=q[y[i].a].top().first;
			int pos=q[y[i].a].top().second;
			q[y[i].a].pop();
			a[pos]=w+y[i].b;
		}
	}
	sort(a+1,a+n+1); 
	for(int i=n;i>=n-m+1;i--){
		ans+=a[i];
	}
	cout<<ans;
	return 0;	//完结撒花 
}
```

---


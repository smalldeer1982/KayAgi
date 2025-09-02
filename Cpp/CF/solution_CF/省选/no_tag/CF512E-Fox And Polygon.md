# Fox And Polygon

## 题目描述

狐狸Ciel设计了一种叫“多边形”的智力游戏！它是通过把一个n变形分成三角形来进行的。目标是通过一些复杂的规则把一种分法转换成另一种分法。

n边形的一种“分法”是n - 3条不相交的对角线构成的集合。

每一步可以选择一条对角线（但不能是n边形的边）然后翻转这条对角线。

对于一条对角线AB，假设它的两边分别是三角形ABC和三角形ABD。“翻转”对角线AB，就是删除对角线AB，并添加对角线CD。

Ciel证明了对于任何一个起点和终点都有合法的翻转方式，她想让你对于任何一个n <= 1000的局面，在20000次操作内完成。

## 样例 #1

### 输入

```
4
1 3
2 4
```

### 输出

```
1
1 3
```

## 样例 #2

### 输入

```
6
2 6
3 6
4 6
6 2
5 2
4 2
```

### 输出

```
2
6 3
6 4
```

## 样例 #3

### 输入

```
8
7 1
2 7
7 3
6 3
4 6
6 1
6 2
6 3
6 4
6 8
```

### 输出

```
3
7 3
7 2
7 1```

# 题解

## 作者：Sagari (赞：14)

本题存在线性做法，时间复杂度 $O(n)$，操作次数上界为 $2n$。

仍然是考虑一个朴素的中继状态，任何状态都可以简单地转移到此状态，那么我们分别求出起始和终止态到这个中继状态的步骤，然后对于终止态到中继态的操作全部取反就可以了。

以上做法其实其他题解已经提到过，但是实现都使用了 $n^2$ 的构造法，接下来我介绍一种线性构造法。

注意到我们每次都会选择一个形如 $1-a-x-b$ 的四边形，其中 $a$ 和 $b$ 都直接与 $a$ 相连，并且 $a$，$b$ 之间有直接连边。然后对 $(a,b)$ 执行操作，就得到了 $(1,x)$ 的边。

一种做法是寻找有连边的 $(a,b)$，然后枚举 $x$ 检查是否与 $(a,b)$ 都有连边，其他部分题解是这个做法我不再多说，但这样是没有前途的 $n^2$，最多使用 bitset 优化到 $\frac {n^2}\omega$。

另外一种方法更好地利用了题目的性质，我们称与 $1$ 直接相连的点为关键点，则我们转为维护每个点与多少个关键点相连。具体的方法是当每个点成为关键点的时候我们枚举其出边，若终点还未与关键点相连，则记录下来终点与此关键点相连；否则，终点已经连向的关键点和当前关键点就形成了一组 $(a,x,b)$。现在的问题是如何检查 $(a,b)$ 是否有边相连呢？事实上，如果此时 $1$ 不与 $x$ 联通，则 $a$ 就一定与 $b$ 相连。我们对 $(a,b)$ 执行操作，然后将 $x$ 设为关键点就可以了，这里我们递归地实现。

完了。每个点和边只会被遍历一次，所以是线性。

```cpp
#include<bits/stdc++.h>
const int N=4050;
using namespace std;

#define _to e[i].to
#define fore(k) for(int i=hd[k];i;i=e[i].nx)
struct edge{
    int to,nx;
}e[N];int hd[N],S;
void add(int fr,int to){
    e[++S]=(edge){to,hd[fr]},hd[fr]=S;
}
int v[N],con[N];
vector<pair<int,int>>ans1,ans2;

int n,fl;

void push(int k){
	v[k]=-1;//已经遍历过了
	fore(k){
		if(v[_to]==0)
			v[_to]=k;
		else if(v[_to]!=-1){
			if(fl){
				if(!con[_to])ans1.push_back({k,v[_to]});
			}
			else{
				if(!con[_to])ans2.push_back({1,_to});
			}
			push(_to);
		}
	}
}

void solve(){
	memset(hd,0,sizeof(hd));S=0;
	memset(v,0,sizeof(v));
	memset(con,0,sizeof(con));
	v[1]=-1;
	for(int i=1;i<=n;i++)
		add(i,i%n+1),add(i%n+1,i);
	for(int i=1;i<=n-3;i++){
		int x,y;cin>>x>>y;
		add(x,y),add(y,x);
		if(x==1||y==1)
			con[x+y-1]=1;
	}
	fore(1)push(_to);
}

int main(){
	cin>>n;
	fl=1;solve();
//	cout<<endl;
	fl=0;solve();
	cout<<ans1.size()+ans2.size()<<endl;
	for(int i=0;i<ans1.size();i++)
		cout<<ans1[i].first<<' '<<ans1[i].second<<endl;
	for(int i=ans2.size()-1;~i;i--)
		cout<<ans2[i].first<<' '<<ans2[i].second<<endl;
}
```

稍微解释一下这个代码：

- $fl$ 代表此时操作是否是正序的，正序和逆序的操作是相反的。正序执行 $(a,b)$，逆序执行 $(1,x)$。
- `push(x)` 代表将 $x$ 设为关键点。



---

## 作者：rEdWhitE_uMbrElla (赞：6)

~~本来以为是一道奇怪的dp题，，，然而发现它不是求最小值，而是求具体方案。。。~~

有一种思路是这样的：

将这个被分成许多三角形的多边形映射成一个有根树，其中每个三角形是一个非根、非叶子节点，每条对角线是一条边，根节点和叶子节点都在多边形外。通过旋转该树直到旋转成了目标状态。目标状态可为任何一种构型的树。实际上是**先构造出初始状态下的数，然后以同样的根构造出目标状态下的树，然后旋转、计数**。请允许我用官方题解中的图。

![](https://puu.sh/e4tiX/db64342636.png)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
vector <int> e[1001];
bool have[1001];

struct node {
	int leftMark, rightMark;
	node* sonLeft, *sonRight;
	void updateMark() {
		leftMark = sonLeft->leftMark;
		rightMark = sonRight->rightMark;
	}
}*start, *want;

struct step {
	int fromA, fromB;
	int toA, toB;
};

node* addNode(int L, int R, int from) {
	node *t = new node();
	t->leftMark = L;
	t->rightMark = R;
	if(L == R+1)
		return t;
	for(int i = 0; i < e[L].size(); i++)
		if(e[L][i] != from)
			have[e[L][i]] = true;
	int M = -1;
	for(int j = 0; j < e[R].size(); j++)
		if(e[R][j] != from)
			if(have[e[R][j]])
				M = e[R][j];
	for(int i = 0; i < e[L].size(); i++)
		have[e[L][i]] = false;
	t->sonLeft = addNode(L, M, R);
	t->sonRight = addNode(M, R, L);
	return t;
}

node* input() {
	for(int i = 1; i <= n; i++)
		e[i].clear();
	for(int i = 1; i <= n-3; i++) {
		int a, b;
		cin >> a >> b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	for(int i = 1; i <= n; i++) {
		int j = i+1;
		if(i == n) j = 1;
		e[i].push_back(j);
		e[j].push_back(i);
	}
	return addNode(n, 1, -1);
}

void print(node *p, string append) {
	cout << append << p->leftMark << " " << p->rightMark << endl;
	if(p->sonLeft != NULL)
		print(p->sonLeft, append + "\t");
	if(p->sonRight != NULL)
		print(p->sonRight, append + "\t");
}

vector <step> record;

void rotateR(node *r) {
	step t;
	node *s = r->sonLeft;
	node *a = s->sonLeft;
	node *b = s->sonRight;
	node *c = r->sonRight;
	t.fromA = s->leftMark;
	t.fromB = s->rightMark;
	r->sonLeft = a;
	r->sonRight = s;
	s->sonLeft = b;
	s->sonRight = c;
	s->updateMark();
	r->updateMark();
	t.toA = s->leftMark;
	t.toB = s->rightMark;
	record.push_back(t);
}

void rotateL(node *r) {
	step t;
	node *s = r->sonRight;
	node *a = r->sonLeft;
	node *b = s->sonLeft;
	node *c = s->sonRight;
	t.fromA = s->leftMark;
	t.fromB = s->rightMark;
	r->sonLeft = s;
	r->sonRight = c;
	s->sonLeft = a;
	s->sonRight = b;
	s->updateMark();
	r->updateMark();
	t.toA = s->leftMark;
	t.toB = s->rightMark;
	record.push_back(t);
}

void rotateRT(node *p, int middle) {
	int myMiddle = p->sonLeft->rightMark;
	if(myMiddle == middle)
		return;
	if(myMiddle < middle) {
		rotateRT(p->sonLeft, middle);
		rotateR(p);
	} else if(myMiddle > middle) {
		rotateRT(p->sonRight, middle);
		rotateL(p);
	}
}

void norm(node *p) {
	if(p->leftMark - p->rightMark <= 2) return;
	int middle = (p->leftMark + p->rightMark) / 2;
	rotateRT(p, middle);
	norm(p->sonLeft);
	norm(p->sonRight);
}

int main() {
	ios :: sync_with_stdio(false);
	memset(have, 0, sizeof(have));
	cin >> n;
	start = input();
	norm(start);
	vector <step> record1 = record;
	record.clear();
	want = input();
	norm(want);
	cout << record.size() + record1.size() << endl;
	for(int i = 0; i < record1.size(); i++)
		cout << record1[i].fromA << " " << record1[i].fromB << endl;
	for(int i = record.size()-1; i >= 0; i--)
		cout << record[i].toA << " " << record[i].toB << endl;
	return 0;
}
```

~~好烦啊QAQ~~

然而还有一种简单而暴力的思路：

我们只需要进行一系列的变换使初始状态中所有的对角线变成以1号节点为端点的对角线并正序存储变换的步骤，然后在进行一系列变换使目标状态中所有的对角线也变成以1号节点为端点的对角线并**倒序存储**变换的步骤（毕竟这实际上是倒推），记一下总数并输出步骤即可

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<pii> vii;

constexpr int maxn = 1010;

int n;
bool e[maxn][maxn];

pii flip(int a, int b, bool inv) {
	int x = -1, y;
	for (int i = 0; i < n; i++)
		if (e[a][i] && e[b][i])
			if (x == -1) x = i;
			else {
				y = i;
				break;
			}
	e[a][b] = e[b][a] = false;
	e[x][y] = e[y][x] = true;
	return inv ? make_pair(x, y) : make_pair(a, b);
}

vii solve(bool inv) {
	memset(e, 0, sizeof(e));
	for (int i = 0; i < n; i++) e[i][(i + 1) % n] = e[(i + 1) % n][i] = true;
	for (int i = 0, a, b; i < n - 3; i++) {
		cin >> a >> b;
		a--;
		b--;
		e[a][b] = e[b][a] = true;
	}
	vii res;
	for (int i = 1; i < n;) {
		if (e[0][i]) {
			i++;
			continue;
		}
		int j;
		for (j = i + 1; e[0][j] == 0; j++);
		res.push_back(flip(i - 1, j, inv));
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n;
	vii a = solve(false), b = solve(true);
	cout << a.size() + b.size() << endl;
	for (int i = 0; i < (int)a.size(); i++) cout << a[i].first + 1 << " " << a[i].second + 1 << endl;
	for (int i = b.size() - 1; i >= 0; i--) cout << b[i].first + 1 << " " << b[i].second + 1 << endl;
	return 0;
}
```

~~明显简单了许多~~

---

## 作者：jjsnam (赞：5)

# 写在前面

似乎除了线性 $O(n)$ 做法就是 $O(n\log n)$？补一篇朴素的 $O(n^2)$ 做法，也便于理解其他做法。

## 前置知识

- 构造

- 模拟

## 题目描述（戳这里[查看原题](https://www.luogu.com.cn/problem/CF512E)）

- 给出一个 $n$ 边形。并给出初始的 $n-3$ 条对角线，将该多边形分成 $n-2$ 个三角形。注意任意两条对角线不相交。

- 定义 “翻转” 操作：对于对角线 $AB$，它分出来的两个三角形是 $\triangle ABC$、$\triangle ABD$，则此时删去线段 $AB$，并添加线段 $CD$。称为对角线 $AB$ 的一次 “翻转”。（如下图）
![](https://cdn.luogu.com.cn/upload/image_hosting/vcf9bnei.png)

- 给出新的一组划分该多边形的对角线集合，问如何只通过翻转操作从原集合变成新集合，输出方案数。

# 正文

一般构造题的样例都没啥用，因为会故意出的让你无法找规律，所以我们还是自己分析。以样例二为例。

## 分析

从原图到新图，其实变化的点很多，变化的线段也很多，我们很难找到一个启发性的思路让程序找到这种方法。好在没有操作次数最优等要求，我们可以务实一些。

相应的，如果很多个点不好考虑，我们尝试都归结到一个点。比如都拿 $1$ 号点，也就是让原图中的对角线分布变成起点都是 $1$，再从 $1$ 变成新图的分布形式，像这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/uu6m54hc.png)
这样，我们成功创建了一个 “中继形态”，方便我们转移。
      
接下来考虑一下如何从原图变换到中继形态。   
我们尝试枚举所有对角线（已经与 $1$ 相连就不用考虑了）对于每条对角线：
- 如果满足它的两个端点可以**与 $1$ 构成三角形**（**即可只经过一条线段到达 $1$ 点**），则判断这条线段**是否还属于另一个三角形**，如果属于的话则可以进行一次**有益**的翻转（因为成功向中继形态前进了一步）。

- 对于不完全满足上述两个条件的线段，我们尝试将它们搁置一旁，先考虑其他线段，等满足他们的条件后再进行决策。

为什么这样决策是对的？因为题目里说可以证明每个点都有合法方式（~~不是~~   

我们尝试**简单证明**一下：
我们假设**存在**一条对角线在**其他对角线都变换完成**的情况下仍不满足上述条件。由于 “翻转” 操作不会增加或减少对角线条数或三角形个数，所以这条对角线两侧一定是两个三角形。又因为其他对角线已经连接了 $1$ 点，所以一定可以与 $1$ 点构成三角形，又另一端也是三角形，一定可以进行操作，前后矛盾。

其他条件类似，可以自己意会一下，有时候猜到了结论也要坚信自己。

故我们现在掌握了向中继形态变换的方法。然而，对于目标形态，我们也通过上述方法转换成中继形态，这样是反着的，如何解决？只要记录操作步骤后逆着来一遍就行。

这样我们就确定了构造方法。

## 细节与实现

1.  如何知道两个点能否一步到达？

	定义 $G[u][v]$ 表示 $u$ 点能否一步到达 $v$。初始时多边形上相邻节点可互相一步到达；原始形态的每条对角线两端点可以互相一步到达。这些状态的值为**真**。
    
    同样的，在翻转操作中，对角线的变换也会引起一步到达状态的变换，原来的两端点不能一步到达，操作后对角线的两端点可以互相到达。由于对角线的性质，操作之间不会有影响。
   
2.	当要决策一条对角线 ${u, v}$ 时（**钦定 $u< v$**），有如下几点细节：

	- 在确定能与 $1$ 构成三角形后，另一个三角形的第三个顶点 $P$ 的选择范围满足 $P\in[u+1, v-1]$。因为超出这个区间两个三角形就会相交，而在题目定义中任意两个三角形不能有重合面积。
    - $P$ 不一定是 $u+1$ 或 $v-1$。因此我们要记录每个点能一步到达的所有点，可以相应的建边。判断时可以枚举 $u$ 所能到达的所有点 $to$，如果 $G[to][v] = true$ 且满足上一条的条件，则是一个合法端点，可以使用。
    
3.	删除和新增对角线也要对相应的边更改。
	相应的，删除可以对连接原对角线的无向边打上标记。后续决策跳过即可。不过不嫌麻烦也可以把对应位置替换为新的对角线的无向边，实现起来略复杂。
    
枚举所有对角线是 $O(n)$，然而对于第一个对角线可能要后错 $n$ 次，故上线枚举量是 $O(n^2)$ 级别。对于枚举对角线的两端点，找另一三角形的操作用链式前向星存图优化，故一次决策是 $O(m)$ 的，其中 $m$ 是边数。而满足边数总和不会过大，$\sum m$ 也是 $O(n)$ 级别，所以最终复杂度上线是 $O(n^2)$。当然幸运的话可以跑到 $O(n)$。

# 代码

枚举即后错对角线用了队列，写起来更容易懂。变量名解释在注释。

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
typedef pair<int, int> PII;
const int maxn = 1005;

bool G[maxn][maxn];//判断能否一次到达
int n;
struct Diagonal{//待操作对角线
    int u, v;
}D[maxn];
PII steps[maxn * 20];//记录步骤
int tot;
struct Edge{//图上的边
    int v, next;
    bool st;
}e[maxn << 3];
int p[maxn], len;

void add(int u, int v){
    e[len] = (Edge){v, p[u], false}, p[u] = len ++;
}

int prev(int p){//找环上前一个点
    return p == 1 ? n : p - 1;
}

int next(int p){//找环上后一个点
    return p % n + 1;
}

void init(){
    memset(p, -1, sizeof p), len = 0;
    memset(G, 0, sizeof G);
    for (int i = 1; i <= n; i ++){
        int u = i, v = next(u);
        G[u][v] = G[v][u] = true;
        add(u, v), add(v, u);
    }
}

void getMethod(int &cnt, bool st){
    init();
    cnt = 0;
    queue<Diagonal> q;
    for (int i = 1, u, v; i <= n - 3; i ++){
        cin >> u >> v;
        add(u, v), add(v, u);
        if (u > v) swap(u, v);//钦定 u < v
        D[i] = (Diagonal){u, v}, G[u][v] = G[v][u] = true;
        if (u != 1 && v != 1) q.push(D[i]);//与 1 相连没必要再操作了
    }
    while (!q.empty()){
        Diagonal D = q.front();
        q.pop();
        int u = D.u, v = D.v;
        if (!G[u][1] || !G[v][1]){//不能与 1 构成三角形
            q.push(D); 
            continue;
        }
        int temp = -1, idx = -1;//另一个三角形的第三个顶点；决策对角线的索引（方便删除）
        for (int i = p[u]; ~i; i = e[i].next){
            int to = e[i].v;
            if (to == v && !e[i].st) idx = i;
            if (to >= v || e[i].st || to == 1){
                continue;
            }
            if (G[to][v]){
                temp = to;
                break;
            }
        }
        if (temp == -1){//找不到另一个合法三角形
            q.push(D); 
            continue;
        }
        /* 删除原对角线，加入新对角线，注意图中边和一步到达状态也要更改 */
        G[u][v] = G[v][u] = false;
        G[1][temp] = G[temp][1] = true;
        e[idx].st = e[idx ^ 1].st = true;
        add(1, temp), add(temp, 1);
        /* 插入操作。如果操作要反过来翻转的对角线就是决策中新的对角线 */
        steps[++ tot] = st ? make_pair(1, temp) : make_pair(u, v), cnt ++;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    tot = 0;
    int cnt1 = 0, cnt2 = 0;
    /* now -> P1 */
    getMethod(cnt1, 0);
    /* now -> P2 */
    getMethod(cnt2, 1);
    
    /* out */
    cout << tot << endl;
    /* 原始状态到中继状态的操作方案 */
    for (int i = 1; i <= cnt1; i ++){
        cout << steps[i].first << ' ' << steps[i].second << endl;
    }
    /* 中继状态到最终状态的操作方案 注意操作步骤要反过来 */
    for (int i = tot; i > cnt1; i --){
        cout << steps[i].first << ' ' << steps[i].second << endl;
    }

    return 0;
}
```



------------



---

## 作者：Walker_V (赞：3)

# CF512E Fox And Polygon

分析题意，我们首先需要知道这样一个性质：图形的任意两种状态之间是可以相互转换的。

也就是说，没有哪种状态是初始状态不能变化到的；同理，也没有哪种状态是终止状态不能变化到的。

此外我们还可以发现，变化步骤是可以倒推的。

结合以上几点，就可以得到这道题的做法了。

首先我们需要找到一个中间状态，为了方便，我们将这个中间状态定为所有点联向$1$号点的情况。

然后我们分别求出由初始状态变化为中间状态，和由终止状态变化为中间状态的步骤。

这个找步骤的过程如下：

枚举每个点，在这个点的左右两边分别找到一个与$1$点相连的点。根据分法（划分为数个三角形）可知，这两个点必然相连。然后删去这两点间的这条对角线并存储步骤即可。

这里需要注意的是，新出现的对角线并**不一定是$1$号点和当前枚举点的连线**，所以要枚举找出这个同时与被删去对角线两端点相连的点。

再这样一次操作后，当前枚举点不一定就会与$1$号点相连，所以要循环直到$1$号点和当前点相连为止，再枚举下一个点。

用同样的方法找到由终止状态到中间状态的变化过程。注意存储的步骤是**新出现对角线的两个端点**。

最后输出所有步骤即可，其中由终止状态变化到中间状态的步骤需要倒序输出。

（但是我现在还没证明步骤数必定在$20000$之内，所以记录步骤用vector会更好）
```cpp
#include<bits/stdc++.h>
#define N 1010

using namespace std;

int n,cnt1,cnt2;
bool edge1[N][N],edge2[N][N];

struct node {
	int frm,to;
}op1[20010],op2[20010];

void Read() {
	scanf("%d",&n);
	for(int i=1;i<=n-3;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		edge1[u][v]=1;
		edge1[v][u]=1;
	}
	for(int i=1;i<=n-3;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		edge2[u][v]=1;
		edge2[v][u]=1;
	}
	return;
}

void Solve() {
	for(int i=1;i<=n;i++) {
		edge1[i][i%n+1]=1;
		edge1[i%n+1][i]=1;
		edge2[i][i%n+1]=1;
		edge2[i%n+1][i]=1;
	}

	for(int i=2;i<=n;i++) {
		while(!edge1[1][i]) {
			int su=i-1,sv,eu=0,ev; //su=i-1:i的上一个点必与1点相连 su-sv -> es-ev
			for(int j=i+1;j<=n;j++) {
				if(edge1[1][j]) {
					sv=j;
					break;
				}
			}
			for(int k=1;k<=n;k++) {
				if(edge1[su][k]&&edge1[sv][k]) {
					if(eu==0) {
						eu=k;
					}
					else {
						ev=k;
						break;
					}
				}
			}
			edge1[su][sv]=0;
			edge1[sv][su]=0;
			edge1[eu][ev]=1;
			edge1[ev][eu]=1;
			op1[++cnt1]=(node){su,sv};
			//printf("op:%d %d %d %d i:%d\n",su,sv,eu,ev,i);
		}
	}
	for(int i=2;i<=n;i++) {
		while(!edge2[1][i]) {
			int su=i-1,sv,eu=0,ev; //su=i-1:i的上一个点必与1点相连 su-sv -> es-ev
			for(int j=i+1;j<=n;j++) {
				if(edge2[1][j]) {
					sv=j;
					break;
				}
			}
			for(int k=1;k<=n;k++) {
				if(edge2[su][k]&&edge2[sv][k]) {
					if(eu==0) {
						eu=k;
					}
					else {
						ev=k;
						break;
					}
				}
			}
			edge2[su][sv]=0;
			edge2[sv][su]=0;
			edge2[eu][ev]=1;
			edge2[ev][eu]=1;
			op2[++cnt2]=(node){eu,ev};
			//printf("op:%d %d %d %d i:%d\n",su,sv,eu,ev,i);
		}
	}

	return;
}

void Print() {
	printf("%d\n",cnt1+cnt2);
	for(int i=1;i<=cnt1;i++) {
		printf("%d %d\n",op1[i].frm,op1[i].to);
	}
	for(int i=cnt2;i>=1;i--) {
		printf("%d %d\n",op2[i].frm,op2[i].to);
	}
	return;
}

int main()
{
	Read();
	Solve();
	Print();
	return 0;
}
```

---

## 作者：Aleph_Drawer (赞：2)

我们充分发扬人类智慧，考虑乱搞。

首先观察样例，在纸上画图可以得出几个性质：

> 性质 1. 已经到达目标位置的对角线不需要再进行操作

> 证明是比较简单的，考虑如果存在这种情况，那么原图和目标图一定被划分成了两个部分，由于操作前和操作后都是三角剖分（所以不会出现目标对角线相交于多边形内部的情况）所以可以划分为两个子多边形考虑。

那么我们就可以不用考虑那些已经在目标位置上的对角线了。

> 性质 2. 如果一条对角线满足可以通过一次翻转到达目标对角线，那么一定进行这个操作

> 这样贪心是对的，因为如果进行操作后，就变成了性质 1 的情况。

那么我们先对原图跑一遍，看看有没有一次操作就可以到达目标状态的情况。

考虑剩下的没有到达目标对角线的对角线。

此时发扬人类智慧，对一些比较大的生成数据（如 $n = 15$）进行模拟，发现对于剩下的对角线，如果随机翻转其中的一条对角线，则会出现大量的性质2的情况，而且都基本相邻。

再次观察题目，发现操作的上限与 $n$ 的相差达到了 $20$ 倍。

所以我们得到了一种很乱搞的做法：对于所有尚未到达目标位置的对角线，我们每次随机其中的 $20$ 个并对其进行操作，然后对于它们所在的四边形 $(a, b, c, d)$，寻找与 $a,b$ 相连的对角线，并尝试将其翻转（即如果能够翻转到目标状态，就翻转这个对角线），这样子做均摊复杂度是 $\Theta(n^2)$ 的，实际上会更小，因为跑不满。

然后我们对于上述操作多跑几遍，最后再重新检查一遍，看看还有没有剩下的一次操作达到目标状态的点。当次数 $T = 1000$ 的时候就可以通过所有数据点，此时生成的操作次数约为 $13000$ 次，大约耗费时间 $500$ 毫秒。

参考代码如下：

```c++
/* Author : Alpha_Drawer
   Problem : CF512E
*/
#include<bits/stdc++.h>
using namespace std;

const int N = 1e3 + 103;

int n, a[N][N], tgt[N][N]; // a[x][y] 表示对角线及多边形的边 (x, y), tg[x][y] 表示目标对角线
bool aimed[N]; // 表示对于对角线 i 是否已经到达目标对角线位置

struct pairs { // 对角线
	int x, y;
}eg[N], rec[N * N]; int sum = 0; // eg 表示当前对角线，rec 表示记录的答案，sum 是答案大小

pairs mp(int x, int y) { // make_pair(int, int)
	pairs a;
	a.x = x, a.y = y;
	return a;
}

pairs vt(int u, int v) { // 虚拟翻转，即对于对角线 (u, v) 求出翻转之后的对角线，但不实际操作
	int x = 0, y = 0;
	for(int i = 1; i <= n; i++)
		if(a[i][u] && a[i][v]) (x ? y : x) = i;
	return mp(x, y);
}

void transform(int pos, int u, int v) { // 翻转操作
	int x = 0, y = 0;
	for(int i = 1; i <= n; i++)
		if(a[i][u] && a[i][v]) (x ? y : x) = i;
	if(!x || !y)
		return;
	rec[++sum].x = u, rec[sum].y = v;
	a[u][v] = a[v][u] = 0; a[x][y] = a[y][x] = 1;
	eg[pos].x = x, eg[pos].y = y;
	return;
}

int main() {
	srand(time(0)); // rand() 初始化
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int x = i, y = i % n + 1;
		a[x][y] = a[y][x] = 1;
	}
	for(int i = 1; i <= n - 3; i++) {
		scanf("%d%d", &eg[i].x, &eg[i].y);
		a[eg[i].x][eg[i].y] = a[eg[i].y][eg[i].x] = 1;
	}
	for(int i = 1; i <= n - 3; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		tgt[u][v] = tgt[v][u] = 1;
	} // 输入与连边
	for(int i = 1; i <= n - 3; i++) {
		if(tgt[eg[i].x][eg[i].y]) {
			aimed[i] = 1;
			continue;
		}
		pairs res = vt(eg[i].x, eg[i].y);
		if(tgt[res.x][res.y]) {
			transform(i, eg[i].x, eg[i].y);
			aimed[i] = 1;
		}
	} // 看看有没有一次操作就可以到达目标状态的情况，有就直接操作
	int TIMES = 1000; // 随机操作次数
	for(; TIMES; --TIMES) {
		for(int tms = 1; tms <= 20; tms++) { // 每次尝试修改20条对角线
			int pos = rand() % n + 1, trt = 0;
			if(tgt[eg[pos].x][eg[pos].y])
				aimed[pos] = 1; // 性质1
			while(aimed[pos]) {
				trt++;
				pos = rand() % n + 1;
				if(tgt[eg[pos].x][eg[pos].y])
					aimed[pos] = 1;
				if(trt > 100)
					break; // 如果一直随机不到想要的边直接 break 防止浪费时间
			}
			if(trt > 100)
				continue;
			int x = eg[pos].x, y = eg[pos].y;
			transform(pos, eg[pos].x, eg[pos].y); // 对目标边进行翻转
			if(tgt[eg[pos].x][eg[pos].y])
				aimed[pos] = 1;
			for(int i = 1; i <= n; i++) {
				if(abs(x - i) > 1 && a[x][i]) {
					int fnd = 0;
					for(int j = 1; j <= n; j++) { // 寻找满足条件的对角线，下同
						if(eg[j].x == x || eg[j].x == i) {
							if(eg[j].y == x || eg[j].y == i) {
								fnd = j;
								break;
							}
						}
					}
					if(!aimed[fnd]) {
						pairs res = vt(eg[fnd].x, eg[fnd].y);
						if(tgt[res.x][res.y]) {
							transform(fnd, eg[fnd].x, eg[fnd].y);
							aimed[fnd] = 1;
						}
					}
				}
				if(abs(y - i) > 1 && a[y][i]) {
					int fnd = 0;
					for(int j = 1; j <= n; j++) {
						if(eg[j].x == y || eg[j].x == i) {
							if(eg[j].y == y || eg[j].y == i) {
								fnd = j;
								break;
							}
						}
					}
					if(aimed[fnd])
						continue;
					pairs res = vt(eg[fnd].x, eg[fnd].y);
					if(tgt[res.x][res.y]) {
						transform(fnd, eg[fnd].x, eg[fnd].y);
						aimed[fnd] = 1;
					}
				} // 对所有在这个四边形上两点的进行翻转
			}
		}
	}
	for(int i = 1; i <= n - 3; i++) {
		if(aimed[i])
			continue;
		pairs res = vt(eg[i].x, eg[i].y);
		if(tgt[res.x][res.y]) {
			transform(i, eg[i].x, eg[i].y);
			aimed[i] = 1;
		}
	} // 最后检查是否存在还可以继续翻转的情况，不放心可以多做几遍
	printf("%d\n", sum);
	for(int i = 1; i <= sum; i++) {
		printf("%d %d\n", rec[i].x, rec[i].y);
	} // 输出答案
	return 0;
}


---

## 作者：x0d5_n14R (赞：1)

# 题外话

联考中有趣的构造题，第一次赛时想出来题(~~只可惜刚开考时睡着了导致想完了没写完~~)。

# 题意

- 给你两个 $N$ 个点的多边形的三角剖分方案（将多边形划分为若干个三角形，即多边形内连边且不存在两条相交的边，连边数为 $N-3$）。
- 现在你能够进行一种操作：选择多边形内部的一条边，连接这条边所在的两个三角形对应的顶点（不难发现这样操作后这张图依然是多边形的一种三角剖分方式）。
- 要求你给出构造方案，并限制步数为 $Q$，将给出的第一种三角剖分方案转化为第二种三角剖分方案。
- 数据范围 $N \leq 1000,Q \leq 20000$。

# 分析

通过对于样例的模拟，我们发现直接设计剖分方案状态后并进行转移是极其困难的，所以需要找出一些特殊的状态来进行中间转移，而样例有了很好的提示，即除 $2$ 与 $N$ 以外的所有点向 $1$ 连边的三角剖分(下文称这种状态为菊花)，又由于操作方案是可逆的，我们就将问题转化为了如何构造出一种从菊花到任意状态(下称需要到达的状态为答案状态)的方案。

现在，我们来考虑一种简单的情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/irxm55ap.png)
此时三个点都向 $1$ 有连边且这三个点中不存在 $1$，那么我们可以直接对图中中间点与 $1$ 之间的边做一次操作变为图中虚线边。

我们来考虑一般情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/e4xlvuhd.png)
根据上面的推导我们可以猜想，如果想要满足答案状态中的两个点，那么我们需要使得这两个点之间的点(我们定义“两个点之间”为不包括 $1$ 的链上的所有点，设链长为$len = \max(a, b) - \min(a, b)$)都已经到达了答案状态，不难发现中间必然还有一个点与 $1$ 有连边而且与 $A, B$ 有连边，故我们可以进行一步操作使得 $A, B$ 满足答案状态，此时我们已构造出一种总操作数为 $2N$ 的方案。

# 算法流程

- 具体地，开一个邻接矩阵记录连边情况。

- 根据上文推出的结论，我们先将答案状态中的 $(u, v)$ 按照它们的 $len$ 上升排序，初始化连边状态($i \rightarrow i \bmod N + 1, 1 \rightarrow i$)，每次找出 $(u, v)$ 所在的四边形中的另外两点并将其连边，断开 $(u, v)$。

- 对于任意一个状态到菊花图，我们只需要重复上述算法流程后将操作倒序并取反进行即可。

- 时间复杂度 $O(N^2)$ 空间复杂度 $O(N^2)$。

# Code


*Talk is cheap, show me the code.*



```C++
/*
                  _/_/_/                _/     _/_/_/_/_/                                   _/             _/       _/_/_/_/   
                _/      _/              _/    _/                                           _/_/          _/_/      _/      _/  
_/        _/   _/        _/             _/    _/                                          _/ _/         _/ _/      _/       _/ 
 _/      _/    _/        _/             _/    _/                          _/ _/_/_/_/        _/        _/  _/      _/       _/ 
  _/    _/    _/          _/            _/    _/ _/_/_/                   _/_/       _/      _/       _/   _/      _/      _/  
   _/  _/     _/          _/     _/_/_/ _/    _/       _/                 _/         _/      _/      _/    _/      _/_/_/_/    
    _/_/      _/          _/  _/      _/_/              _/                _/         _/      _/     _/     _/      _/     _/   
   _/  _/      _/        _/   _/        _/              _/                _/         _/      _/    _/_/_/_/_/_/_/  _/     _/   
  _/    _/     _/        _/   _/        _/              _/                _/         _/      _/            _/      _/      _/  
 _/      _/     _/      _/     _/       _/    _/       _/                 _/         _/      _/            _/      _/       _/ 
_/        _/      _/_/_/         _/_/_/   _/   _/_/_/_/     _/_/_/_/_/_/  _/         _/    _/_/_/          _/      _/        _/
Problem: CF512E Fox And Polygon
Contest: Codeforces
URL: http://codeforces.com/problemset/problem/512/E
===================
Memory Limit: 256.0MB
TimeLimit: 2.0s
*/
#include <iostream>
#include <algorithm>
#define FOR(i, l, r) for (int i = l; i < r+1; i++)
#define ROF(i, r, l) for (int i = r; i > l-1; i--)

const int MAXN = 1e3+9;
using namespace std;

struct Edge {
    int u, v, dis;
}def[MAXN], to[MAXN], ans1[MAXN], ans2[MAXN], ans3[MAXN];

//-----read & write begin-----
inline int read () {
    int x = 0;bool w = 0;char ch = getchar();
    while (!isdigit(ch)) {w = (ch == '-'), ch = getchar();}
    while (isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0', ch = getchar();}
    return w ? -x : x;
}
void write (int x) {
    if (x > 9) write(x/10);
    putchar((char)(x % 10 + '0'));
}
//------read & write end------

int N, M;

inline bool cmp (const Edge &a, const Edge &b) {return a.dis < b.dis;}
inline void Read () {
    N = read();
    FOR(i, 1, N-3) {
        def[i].u = read(), def[i].v = read();
        if (def[i].u > def[i].v) swap(def[i].u, def[i].v);
        def[i].dis = def[i].v - def[i].u;
    }
    FOR(i, 1, N-3) {
        to[i].u = read(), to[i].v = read();
        if (to[i].u > to[i].v) swap(to[i].u, to[i].v);
        to[i].dis = to[i].v - to[i].u;
    }
}

bool edge[MAXN][MAXN];
inline int nxt (const int &i) {return i % N + 1;}
inline void Solve (Edge* A, Edge *B, int n, int &sz) {
    sort(A+1, A+1+n, cmp);
    FOR(i, 1, N)FOR(j, 1, N) edge[i][j] = 0;
    FOR(i, 1, N) edge[i][nxt(i)] = edge[nxt(i)][i] = 1;
    FOR(i, 3, N-1) edge[1][i] = edge[i][1] = 1;
    int cnt = 0, c1, c2;
    FOR(i, 1, n) {
        int u = A[i].u, v = A[i].v;
        if (u == 1) continue;
        c1 = c2 = 0;
        FOR(j, 1, N) {
            if (edge[u][j] && edge[j][v]) {
                if (!c1) c1 = j;
                else c2 = j;
            }
        }
        B[++cnt] = (Edge){c1, c2, max(c1, c2) - min(c1, c2)};
        edge[c1][c2] = edge[c2][c1] = 0;
        edge[u][v] = edge[v][u] = 1;
    }
    sz = cnt;
}

int main () {
	Read();
    int M1 = 0, M2 = 0;
    Solve(def, ans1, N-3, M1);
	Solve(to, ans2, N-3, M2);
    
    FOR(i, 1, N) FOR(j, 1, N) edge[i][j] = 0;
    FOR(i, 1, N) edge[i][nxt(i)] = edge[nxt(i)][i] = 1;
    FOR(i, 1, N-3) edge[def[i].u][def[i].v] = edge[def[i].v][def[i].u] = 1;

    ROF(i, M1, 1) {
        int c1 = 0, c2 = 0, u = ans1[i].u, v = ans1[i].v;
        FOR(j, 1, N) if (edge[j][u] & edge[j][v]) {
            if (!c1) c1 = j;
            else c2 = j;
        }
        ans3[M1-i+1] = (Edge){c1, c2, max(c1, c2) - min(c1, c2)};
        edge[u][v] = edge[v][u] = 1;
        edge[c1][c2] = edge[c2][c1] = 0;
    }
    write(M1+M2), putchar('\n');
    FOR(i, 1, M1) write(ans3[i].u), putchar(' '), write(ans3[i].v), putchar('\n');
    FOR(i, 1, M2) write(ans2[i].u), putchar(' '), write(ans2[i].v), putchar('\n');
	return 0;
}
```

---

## 作者：Celtic (赞：1)

来一发复杂度为 $O(\frac{n^2}{32}+n\log n)$的题解。

考虑到我们要把第一个状态转移成第二个，而且状态转移是可逆的，所以可以想到要把两个状态转移成一个中间状态，然后倒退回去。

为了方便，我们定义中间状态为所有节点都和 $1$ 号结点连边。

考虑怎么转移，显然如果两个连续的和 $1$ 相连的点不相邻，那么他们两个之间一定会有连边，不然就会出现四边形或者五边形等等。设这两个和 $1$ 相连的点为 $x,y$ ，我们可以找到这条边两边的三角形，其中一个为 $1,x,y$ 构成的三角形，还有一个我们枚举 $x,y$ 中间的点，看哪个点和 $x,y$ 都有连边，设其为 $i$ ，那么第二个三角形即为 $i,x,y$ 。

找到这两个三角形后，我们把 $x,y$之间的对角线转换成 $1,i$。

这样就完成了一次转移。

再考虑怎样能转移所有不合法（这里的不合法即不含 $1$ 的边）的边，我们从 $2$ 到 $n$ 枚举和 $1$ 有连边的点 $x$，找到下一个和 $1$ 有连边的点 $y$。如果 $x,y$ 不相邻则对这条对角线转移，转移后 $x,y$ 之间多出了一个与 $1$ 相连的点，于是将 $x$ 减一重新放入循环，直到 $x$ 的下一个与 $1$ 相连的点 与 $x$ 相邻为止。

为了快速执行插入和寻找后继操作，我们使用平衡树(`set`)来完成，即将所有与 $1$ 相连的点插入平衡树中。

在判断 $i$ 和 $x,y$ 有没有连边时我们使用 `bitset`，这样复杂度的常数又乘上了 $\frac{1}{32}$。

对于每一次枚举，他的贡献是“干掉了一条不含 $1$ 的边”，总共有 $O(n)$ 条这样的边，所有会运行 $O(n)$ 次循环，复杂度即为 $O(\frac{n^2}{32})$，再加上外面的枚举 $x$ 和平衡树操作，总复杂度为 $O(\frac{n^2}{32}+n\log n)$。

暂时的最优解
[link](https://www.luogu.com.cn/record/list?pid=CF512E&orderBy=1&status=&page=1)


$\sf{Code}$

```cpp
#include<bits/stdc++.h>
#define N 2001001
#define MAX 2001
#define re register
#define inf 1e18
using namespace std;
typedef long long ll;
typedef double db;
inline void read(re ll &ret)
{
	ret=0;re char c=getchar();re bool pd=false;
	while(!isdigit(c)){pd|=c=='-';c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
	ret=pd?-ret:ret;
	return;
}
ll n,x,y;
bitset<MAX>b[MAX],tmp;
set<ll>st;
vector<pair<ll,ll> >ans1,ans2;
inline ll work(re ll x,re ll y)
{
	tmp=b[x]&b[y];
	for(re int i=x+1;i<y;i++)
		if(tmp[i])
		{
			b[x][y]=b[y][x]=0;
			b[1][i]=b[i][1]=1;
			return i;
		}
}
signed main()
{
	read(n);
	st.insert(n),st.insert(2);
	for(re int i=2;i<=n;i++)
		b[i-1][i]=b[i][i-1]=1;
	b[1][n]=b[n][1]=1;
	for(re int i=1;i<=n-3;i++)
	{
		read(x);
		read(y);
		b[x][y]=b[y][x]=true;
		if(x==1)
			st.insert(y);
		else if(y==1)
			st.insert(x);
	}
	for(re int i=2;i<=n;i++)
	{
		if(b[1][i])
		{
			re set<ll>::iterator it=st.find(i);
			it++;
			if(it!=st.end()&&(*it)!=i+1)
			{
				re ll tmp=work(i,*it);
				ans1.push_back(make_pair(i,*it));
				st.insert(tmp);
				i--;
			}
		}
	}
	for(re int i=1;i<=n;i++)
		b[i].reset();
	st.clear();
	st.insert(n),st.insert(2);
	for(re int i=2;i<=n;i++)
		b[i-1][i]=b[i][i-1]=1;
	b[1][n]=b[n][1]=1;
	for(re int i=1;i<=n-3;i++)
	{
		read(x);
		read(y);
		b[x][y]=b[y][x]=true;
		if(x==1)
			st.insert(y);
		else if(y==1)
			st.insert(x);
	}
	for(re int i=2;i<=n;i++)
	{
		if(b[1][i])
		{
			re set<ll>::iterator it=st.find(i);
			it++;
			if(it!=st.end()&&(*it)!=i+1)
			{
				re ll tmp=work(i,*it);
				ans2.push_back(make_pair(1,tmp));
				st.insert(tmp);
				i--;
			}
		}
	}
	for(re int i=1;i<=n;i++)
		b[i].reset();
	st.clear();
	printf("%d\n",ans1.size()+ans2.size());
	for(re int i=0;i<ans1.size();i++)
		printf("%lld %lld\n",ans1[i].first,ans1[i].second);
	for(re int i=ans2.size()-1;i>=0;i--)
		printf("%lld %lld\n",ans2[i].first,ans2[i].second);
	exit(0);
}
```


---

## 作者：shao0320 (赞：1)

#### 题目大意

给你一个正$n$边形和它的$n-3$条不相交的对角线。

一次操作可以让一条对角线变成其所在的四边形（注意：因为有$n-3$条不相交的对角线，所以任意一条对角线一定包含在一个四边形里）的另一条对角线。

问一种在$20000$步之内，将一种对角线的方式变为另一种对角线的方式的操作步骤

分析：

手玩几个样例，容易发现一个性质，可以通过很多种操作将一张初始的图变成任意一种图。

还有一个性质就是操作可逆，可以通过再来一次操作变成原来的图。

容易想到的一种方法是将所有的对角线都挂到节点$1$上，然后将它变为另一张图。

由于上述性质的存在，因此可以转化为两张图，都变成所有对角线都挂到$1$上。

而将所有对角线挂到$1$号节点的方法很简单，为了方便，我们先强制规定一条对角线只能从编号小的点连到编号大的点，从$2-n$依次考虑每一个点，如果当前点的出边有很多条，如：$2\to3,2\to4$都有，那么一定是$1,2,3,4$这个几个点构成了一个四边形，如果当前点出边只有一条（设当前点为$i$），那么一定是$1,i,i+1,nxt$构成的四边形。

代码如下：

``` cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<set> 
#define N 20005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,a[N],b[N],c[N],d[N],ans1[N],ans2[N],k,ans3[N],ans4[N],kk;
set<int>st[N];
set<int>stt[N];
set<int>::iterator it;
int main()
{
//	freopen("CF512E.in","r",stdin);
//	freopen("CF512E.out","w",stdout);
	n=read();
	for(int i=1;i<=n-3;i++)
	{
		a[i]=read();
		b[i]=read();
		if(a[i]>b[i])swap(a[i],b[i]);
		st[a[i]].insert(b[i]);
	}
	//it=st[2].end();
	//it--;
	//cout<<(*it)<<endl;
	//return 0;
	for(int i=1;i<=n-3;i++)
	{
		c[i]=read();
		d[i]=read();
		if(c[i]>d[i])swap(c[i],d[i]);
		stt[c[i]].insert(d[i]);
	}
//	if(n==4)
//	{
//		cout<<1<<endl;
//		cout<<a[1]<<" "<<b[1]<<endl;;
//		return 0;
//	}
	for(int i=2;i<=n;i++)
	{
		while(st[i].size())
		{
			it=st[i].end();
			it--;
			int now=*it;
			//cout<<i<<" "<<now<<endl;
			int nxt;
			st[i].erase(now);
			//return 0;
			if(!st[i].size())
			{
				nxt=i+1;
			}
			else
			{
				it=st[i].end();it--;
				nxt=*it;
			}
			st[1].insert(nxt);
			ans1[++k]=i;
			ans2[k]=now;
		}
	}
	//cout<<"-----------"<<endl;
	for(int i=2;i<=n;i++)
	{
		while(stt[i].size())
		{
			it=stt[i].end();
			it--;
			int now=*it;
			//cout<<i<<" "<<now<<endl;
			int nxt;
			stt[i].erase(now);
			//return 0;
			if(!stt[i].size())
			{
				nxt=i+1;
			}
			else
			{
				it=stt[i].end();it--;
				nxt=*it;
			}
			stt[1].insert(nxt);
			ans3[++kk]=1;
			ans4[kk]=nxt;
		}
	}
	printf("%d\n",k+kk);
	for(int i=1;i<=k;i++)
	{
		printf("%d %d\n",ans1[i],ans2[i]);
	}
	for(int i=kk;i>=1;i--)
	{
		printf("%d %d\n",ans3[i],ans4[i]);
	}
	return 0;
}
```



---

## 作者：AuCloud (赞：1)

有意思的构造题

（不得不说CF构造题是真的太多了

# 题意

给你一个凸多边形，除了凸多边形的边之外在内部连好了$N-3$条不相交的边，将它分成了$N-2$个三角形

每次您可以选择一条内部的边，将以它为对角线的四边形的另一条对角线加入边集。并将选中的边删除

您需要在20000次变换之内从给定的初态变换为给定的终态。题目保证有解。

# 题解

一开始以为是个最优化问题+构造问题，思索之下想写个双向BFS

但是发现这个k的限制大的离谱，再结合刚刚的“双向BFS”的思路，可以比较轻松的想到确定一个中间状态即可

具体中间状态可以~~按自己喜好~~确定，这里为了好变换就设为了$\{(1,2),(1,3),...,(1,n)\}$这样的边集为中间状态

下表面考虑如何进行合理的变换：

画几个图就可以发现，没有与1连边的点一定在两个与1连过边的点中间
~~（废话~~

并且他与那两个点一定有边相连，并且那两个点一定直接相连（否则无法满足$N-2$条边的限制)

相应的，与1直接相连的点中，如果两点之间有其他点没有与1相连，则这两个点必定相连

可以证明这是个充要条件

所以可以记录与1直接相连的点集，每次排序并对不相邻的两点之间的连线进行变换，直到所有点全都连到了1上，记录操作方案

最后别忘了初态->中间态要正序输出，终态->中间态要倒序输出

就完事了

# 代码

```cpp
#include <bits/stdc++.h>
#define p(x,y) make_pair((x), (y))
using namespace std;
int ans1x[20001], ans1y[20001], ans2x[20001], ans2y[20001], tot1, tot2, tot;
int qwq[20001];
map<pair<int,int>, bool>mp;
int n;
void work1(int x, int y)
{
    for(int i = 2; i <= n; i++)
    {
        if(mp[p(x, i)] && mp[p(y, i)])
        {
            mp[p(x, y)] = mp[p(y, x)] = 0;
            mp[p(1, i)] = mp[p(i, 1)] = 1;
            qwq[++tot] = i;
            ans1x[++tot1] = x;
            ans1y[tot1] = y;
            return;
        }
    }
}
void work2(int x, int y)
{
    for(int i = 2; i <= n; i++)
    {
        if(mp[p(x, i)] && mp[p(y, i)])
        {
            mp[p(x, y)] = mp[p(y, x)] = 0;
            mp[p(1, i)] = mp[p(i, 1)] = 1;
            qwq[++tot] = i;
            ans2x[++tot2] = 1;
            ans2y[tot2] = i;
            return;
        }
    }
}
int main()
{
    cin >> n;
    for(int i = 2; i <= n; i++) mp[p(i, i - 1)] = mp[p(i - 1, i)] = 1;
    mp[p(n, 1)] = mp[p(1, n)] = 1;
    qwq[++tot] = n;
    qwq[++tot] = 2;
    for(int i = 1; i <= n - 3; i++)
    {
        int x, y;
        cin >> x >> y;
        if(x == 1) qwq[++tot] = y;
        else if(y == 1) qwq[++tot] = x;
        mp[p(x, y)] = mp[p(y, x)] = 1;
    }
    while(tot < n - 1)
    {
        sort(qwq + 1, qwq + tot + 1);
        int qqq = tot;
        for(int i = 2; i <= qqq; i++)
        {
            if(qwq[i] - qwq[i - 1] > 1) work1(qwq[i - 1], qwq[i]);
        }
    }
    tot = 0;
    mp.clear();
    memset(qwq, 0, sizeof(qwq));
    for(int i = 2; i <= n; i++) mp[p(i - 1, i)] = mp[p(i, i - 1)] = 1;
    mp[p(1, n)] = mp[p(n, 1)] = 1;
    qwq[++tot] = n;
    qwq[++tot] = 2;
    for(int i = 1; i <= n - 3; i++)
    {
        int x, y;
        cin >> x >> y;
        if(x == 1) qwq[++tot] = y;
        else if(y == 1) qwq[++tot] = x;
        mp[p(x, y)] = mp[p(y, x)] = 1;
    }
    while(tot < n - 1)
    {
        sort(qwq + 1, qwq + tot + 1);
        int qqq = tot;
        for(int i = 2; i <= qqq; i++)
        {
            if(qwq[i] - qwq[i - 1] > 1) work2(qwq[i - 1], qwq[i]);
        }
    }
    cout << tot1 + tot2 << endl;
    for(int i = 1; i <= tot1; i++)
    {
        cout << ans1x[i] << ' ' << ans1y[i] << endl;
    }
    for(int i = tot2; i >= 1; i--)
    {
        cout << ans2x[i] << ' ' << ans2y[i] << endl;
    }
    return 0;
}

```

~~其实`std::map`挺慢的，成功最劣解~~

---

## 作者：Erina (赞：1)

CF上的构造题果然名不虚传......

好了进入正题.

首先明确一点: 当构造题要求你寻找从状态A转移到状态B时, 尝试寻找特殊状态X, 使得A->X->B是很容易实现的. 这也是这种构造题的常见思路.

这一道题目的思路也正是这样.

那么X是什么呢? 就是所有点都和1相连的情况.

A->X: 

我们考虑将每一个直接和1相连的点作为$a_1, a_2, a_3......$

然后发现若$a_x+1<a_{x+1}$那么$a_x, a_{x+1}$之间必定连边.

然后我们反转这个东东.

X->B就是B->X反过来, 记住边也要反过来!

至于实现嘛, 可以用`set`奇技淫巧一波, 然后就好了. 其实代码不像楼上说的那么长, 可以写的很短.

因为之前呗吐槽了数十次码风太丑, 我这次clangformat了一下......

```
#include <iostream>
#include <bitset>
#include <queue>
#include <set>
using namespace std;
namespace fio
{
streambuf *in = cin.rdbuf();
char bb[1000000], *s = bb, *t = bb;
#define gc() (s == t && (t = (s = bb) + in->sgetn(bb, 1000000), s == t) ? EOF : *s++)
inline int read()
{
    int x = 0;
    char ch = gc();
    while (ch < 48)
        ch = gc();
    while (ch >= 48)
        x = x * 10 + ch - 48, ch = gc();
    return x;
}// 快乐读入
} // namespace fio
using fio::read;
int n;
bitset<1005> huaji[1005];
typedef pair<int, int> mp;
vector<mp> sa, sb;
set<int> alt;
int op(int x, int y)
{// 反转对应边
    bitset<1005> ax = huaji[x] & huaji[y];
    int i;
    for (i = 2; i <= n; i++)
        if (ax[i])
            break;// 暴力查找
    huaji[1][i] = huaji[i][1] = 1, huaji[x][y] = huaji[y][x] = 0;
    return i;
}
int main()
{
    n = read();
    for (int i = 1; i < n; i++)
        huaji[i][i + 1] = huaji[i + 1][i] = 1;
    huaji[1][n] = huaji[n][1] = 1;
    for (int i = 1, l, r; i <= n - 3; i++)
        l = read(), r = read(), huaji[l][r] = huaji[r][l] = 1;
    for (int i = 2; i <= n; i++)
        if (huaji[1][i])
            alt.insert(i);
    for (int i = 2; i <= n; i++)
        if (huaji[1][i])
            if (alt.upper_bound(i) != alt.end())
            {
                int nex = *alt.upper_bound(i);// 寻找下一个点
                if (nex == i + 1)
                    continue;// 没有必要反转
                sa.emplace_back(i, nex);// 记录答案
                alt.insert(op(i, nex));// 反转
                i--;
            }
    for (int i = 1; i <= n; i++)
        huaji[i].reset();
    huaji[1][n] = huaji[n][1] = 1, alt.clear();// 清空图像
    for (int i = 1; i < n; i++)
        huaji[i][i + 1] = huaji[i + 1][i] = 1;
    for (int i = 1, l, r; i <= n - 3; i++)
        l = read(), r = read(), huaji[l][r] = huaji[r][l] = 1;
    for (int i = 1; i <= n; i++)
        if (huaji[1][i])
            alt.insert(i);
    for (int i = 2; i <= n; i++)
        if (huaji[1][i])
            if (alt.upper_bound(i) != alt.end())
            {
                int nex = *alt.upper_bound(i), temp;
                if (nex == i + 1)
                    continue;
                sb.emplace_back(1, temp = op(i, nex));// 记得反向输出
                alt.insert(temp);
                i--;
            }
    cout << sa.size() + sb.size() << endl;
    for (mp it : sa)
        cout << it.first << ' ' << it.second << endl;
    for (int i = sb.size() - 1; ~i; i--)
        cout << sb[i].first << ' ' << sb[i].second << endl;// 记得反向放Q
}
```


---

## 作者：Φρανκ (赞：0)

题意：$n-3$ 条对角线将 $n$ 边形分为 $n-2$ 个三角形。给定两种分割方法和一种变换操作，求将一种变为另一种的方法。

核心思想：构造

解：

不妨将多边形的顶点编号为 $i\sim n$。对于每条对角线定义四个值 $s, e, l, r$，分别表示题面中的 $A, B, C, D$，且满足 $s<l<e, e<r<s+n$ 或 $e<r+n<s+n$。

容易发现，对于所有对角线，均有其他对角线或边连接 $s-l,e-l,s-r,e-r$。因此可以初始化 $l=s+1,r=s-1$（这里的 $0$ 指 $n$，下同），之后对于所有包含 $s$ 的对角线，若其另一端点距 $e$ 更近，就更新对应方向的 $l$ 或 $r$。

对角线的变换操作在这种形式下含义如下：$l-r$ 变为 $s-e$，$s,e$ 变为 $l,r$，再更新其他有关边的 $l$ 或 $r$。具体实现用文字描述比较困难，故在代码注释中体现。

对于初始和结束状态，分别可以计算其到 $1-3,1-4,...,1-(n-1)$ 的途径。将前者正常输出，后者反向输出即可。

代码：
```
#include <bits/stdc++.h>
using namespace std;
struct line
{
	int s, e, l, r;
}a[1001];
struct r
{
	int s, e;
}res[10001], res2[10001];
int n, cnt, flag, t, pre;
int main()
{
	cin>>n;
	for(int i=1; i<=n-3; i++)
	{
		cin>>a[i].s>>a[i].e;
		if(a[i].e<a[i].s)
			swap(a[i].s, a[i].e);
	}
	for(int i=1; i<=n-3; i++)
	{
		a[i].l=a[i].s+1;
		a[i].r=(a[i].s-2+n)%n+1;
	}//初始化初始化
	for(int i=1; i<=n-3; i++)
		for(int j=1; j<=n-3; j++)
			if(i!=j)
			{
				if(a[i].s==a[j].s && a[j].e<a[i].e)
					if(a[i].l==0 || a[i].e-a[i].l>a[i].e-a[j].e)
						a[i].l=a[j].e;//更新左侧
				if(a[i].s==a[j].s && a[j].e>a[i].e)
					if(a[i].r==0 || (a[i].r-a[i].e+n)%n>a[j].e-a[i].e)
						a[i].r=a[j].e;
				if(a[i].s==a[j].e)
					if(a[i].r==0 || (a[i].r-a[i].e+n)%n>a[j].s+n-a[i].e)
						a[i].r=a[j].s;//更新右侧
			}//初始化
	for(int i=1; i<=n-3; i++)
	{
		cnt=0;
		for(int j=1; j<=n-3; j++)
		{
			if(a[j].s==1)
				cnt++;
			if(a[j].r==1)
			{
//				cout<<j<<endl; 
//				for(int k=1; k<=n-3; k++)
//					cout<<a[k].s<<" "<<a[k].e<<" "<<a[k].l<<" "<<a[k].r<<endl;
//				cout<<endl;
				res[++flag].s=a[j].s;
				res[flag].e=a[j].e;//记录步骤
				for(int k=1; k<=n-3; k++)
					if(a[k].s==a[j].s || a[k].e==a[j].s || a[k].s==a[j].e || a[k].e==a[j].e)//l,r发生改变的只可能是共点的边
					{
						if(a[k].l==a[j].s || a[k].l==a[j].e)
							a[k].l=a[j].l;//更新l
						if(a[k].r==a[j].e || a[k].r==a[j].s)
							if(a[k].s==a[j].s || a[k].e==a[j].e)
								a[k].r=a[j].r;
							else
								a[k].r=a[j].l;//分类讨论更新r
					}
				t=a[j].s;
				a[j].s=a[j].l;
			 	a[j].l=a[j].e;
				a[j].e=a[j].r;
				a[j].r=t;
				if(a[j].s>a[j].e)
				{
					swap(a[j].s, a[j].e);
					swap(a[j].l, a[j].r);
				}//变换这条对角线本身
			}
		}
		if(cnt==n-3)//若全部调整完毕则结束
			break;
	}
//	for(int k=1; k<=n-3; k++)
//		cout<<a[k].s<<" "<<a[k].e<<" "<<a[k].l<<" "<<a[k].r<<endl;
//	cout<<endl;
	pre=flag;
	cnt=0;
	flag=0;
	t=0;//下半与上半基本同
	for(int i=1; i<=1000; i++)
	{
		a[i].e=0;
		a[i].l=0;
		a[i].r=0;
		a[i].s=0;
	}
	for(int i=1; i<=n-3; i++)
	{
		cin>>a[i].s>>a[i].e;
		if(a[i].e<a[i].s)
			swap(a[i].s, a[i].e);
	}
	for(int i=1; i<=n-3; i++)
	{
		a[i].l=a[i].s+1;
		a[i].r=(a[i].s-2+n)%n+1;
	}
	for(int i=1; i<=n-3; i++)
		for(int j=1; j<=n-3; j++)
			if(i!=j)
			{
				if(a[i].s==a[j].s && a[j].e<a[i].e)
					if(a[i].l==0 || a[i].e-a[i].l>a[i].e-a[j].e)
						a[i].l=a[j].e;
				if(a[i].s==a[j].s && a[j].e>a[i].e)
					if(a[i].r==0 || (a[i].r-a[i].e+n)%n>a[j].e-a[i].e)
						a[i].r=a[j].e;
				if(a[i].s==a[j].e)
					if(a[i].r==0 || (a[i].r-a[i].e+n)%n>a[j].s+n-a[i].e)
						a[i].r=a[j].s;
			}
	for(int i=1; i<=n-3; i++)
	{
		cnt=0;
		for(int j=1; j<=n-3; j++)
		{
			if(a[j].s==1)
				cnt++;
			if(a[j].r==1)
			{
//				cout<<j<<endl;
//				for(int k=1; k<=n-3; k++)
//					cout<<a[k].s<<" "<<a[k].e<<" "<<a[k].l<<" "<<a[k].r<<endl;
//				cout<<endl;
				res2[++flag].s=a[j].l;
				res2[flag].e=a[j].r;//但这里要记录变换完成的结果
				for(int k=1; k<=n-3; k++)
					if(a[k].s==a[j].s || a[k].e==a[j].s || a[k].s==a[j].e || a[k].e==a[j].e) 
					{
						if(a[k].l==a[j].s || a[k].l==a[j].e)
							a[k].l=a[j].l;
						if(a[k].r==a[j].e || a[k].r==a[j].s)
							if(a[k].s==a[j].s || a[k].e==a[j].e)
								a[k].r=a[j].r;
							else
								a[k].r=a[j].l;
					}
				t=a[j].s;
				a[j].s=a[j].l;
				a[j].l=a[j].e;
				a[j].e=a[j].r;
				a[j].r=t;
				if(a[j].s>a[j].e)
				{
					swap(a[j].s, a[j].e);
					swap(a[j].l, a[j].r);
				}
			}
		}
		if(cnt==n-3)
			break;
	}
	cout<<flag+pre<<endl;
	for(int i=1; i<=pre; i++)
		cout<<res[i].s<<" "<<res[i].e<<endl;//正序输出
	for(int i=flag; i>=1; i--)
		cout<<res2[i].s<<" "<<res2[i].e<<endl;//倒序输出
	return 0;
}
```

---

## 作者：Liuxizai (赞：0)

## Description

定义一个 $n$ 边形的一种分割为用 $n-3$ 条对角线将多边形分为 $n-2$ 个三角形。

对于一条对角线 $(A,B)$，记与其相邻的两个三角形为 $\triangle ABC,\triangle ABD$。

定义翻转操作为删除对角线 $(A,B)$ 并添加对角线 $(C,D)$。

容易发现任意两种分割都能够通过翻转操作相互转换。

给出起始状态 $S$ 和终止状态 $T$，要求你在 $20000$ 步内将起始状态变换为终止状态。

$n\le1000$

## Solution

既然任意两种状态之间都能够相互转换，那么我们考虑寻找一个中间状态 $M$，通过 $S\to M\to T$ 的方式完成转换。

同时我们还发现变换是可逆的，所以我们只需考虑如何将 $M$ 转换为其他状态，那么 $S\to M$ 的部分作逆变换即可。

在这道题中，最特殊的分割，我们可以考虑所有对角线都从 $1$ 出发的情况。

![](http://www.hsyoj.top/file/4/hexagon-0.png)

我们就将这种状态定义为 $M$，考虑此时从哪些对角线入手构造。

对于一条对角线 $(A,B)$ 定义 $dis$ 为 $|A-B|-1$。

不难发现，此时目标状态中所有 $dis=1$ 的对角线我们都能够通过一次翻转得到。

![](http://www.hsyoj.top/file/4/hexagon-1.png)

每做一次这样的操作，不难发现可以视作削掉了原来 $n$ 边形的一个角，边数 $-1$。

在所有 $k$ 条 $dis=1$ 的对角线构造完后，我们可以保证原来所有 $dis=2$ 的对角线在新的 $n-k$ 边形中 $dis=1$。

于是只需依次构造 $dis=1\to n-3$ 的对角线即可。

接下来考虑一下代码实现的细节，$S\to M$ 时只需考虑 $S$ 中 $dis=n-3\to1$ 的对角线，而 $M\to T$ 的部分，若想要构造 $T$ 中的一条对角线 $(P,Q)$，我们需要查询 $P,Q$ 之间还未作过翻转操作的点 $R$，对 $(1,R)$ 进行翻转操作，并将 $R$ 标记为已做过翻转操作，这一部分用 `std::set` 维护即可。

代码复杂度为 $O(n\log n)$，$\log$ 来自 `std::set`。

操作次数的上界为 $2n-6$，远低于 $20000$。

## Code

```cpp
namespace Main{
    int n, tot;
    struct line{
        int u, v;
        line() {}
        line(int u, int v): u(u), v(v) {}
    };
    vector<line> ans1[N], ans2[N];
    set<int> ext;
    void Main(){
        input(n);
        for(ri i = 0, u, v; i < n - 3; i++){
            input(u, v);
            if(u == 1 || v == 1) continue;
            if(u < v) swap(u, v);
            ans1[u - v].emplace_back(u, v);
            tot++;
        }
        for(ri i = 0, u, v; i < n - 3; i++){
            input(u, v);
            if(u == 1 || v == 1) continue;
            if(u < v) swap(u, v);
            ans2[u - v].emplace_back(u, v);
            tot++;
        }
        write(tot); puts("");
        for(ri i = N - 1; i; i--)
            for(line x: ans1[i])
                printf("%d %d\n", x.u, x.v);
        for(ri i = 3; i <= n - 1; i++) ext.emplace(i);
        for(ri i = 1; i < N; i++){
            for(line x: ans2[i]){
                set<int>::iterator iter = ext.upper_bound(x.v);
                printf("%d %d\n", 1, *iter);
                ext.erase(iter);
            }
        }
        return;
    }
} // namespace
```

---


# [CERC2017] Buffalo Barricades

## 题目描述

（西进运动时期）美国西部的一块牧场可以被表示为坐标系第一象限中的一块矩形网格。有 $n$ 头水牛在其中分布着，每一头都占据着一个单位正方形。水牛们从 $1$ 到 $n$ 编号；$j$ 号水牛位于右上角坐标为 $(x_j, y_j)$ 的单位正方形中。坐标轴表示了两条交汇于原点处的河流，阻止水牛向左下方移动。

一共有 $m$ 个殖民者接连到达，每个人都要宣称一块土地的所有权，其过程遵循以下规则：

1. 殖民者选定一个整数坐标点，并在此处安装一个栅栏柱。他选定的点必须没有被此前安装的栅栏或栅栏柱占据。并且，不存在两个栅栏柱会拥有相同的 $x$ 坐标，也不存在两个栅栏柱会拥有相同的 $y$ 坐标。
2. 从栅栏柱开始，殖民者分别朝着左侧或下侧修建水平或竖直的栅栏片段。每段栅栏都修建得尽可能长：即直到碰到了河流或另一段栅栏才停下。
3. 殖民者宣称以他的栅栏柱为右上角的，被栅栏和河流包围住的连通区域的所有权。当然，他也宣称了其中的所有水牛的所有权。注意后到来的殖民者也有可能宣称了已被先到来的殖民者宣称过的土地。

对于每个殖民者，请求出当他刚到来时，被他宣称了所有权的水牛的数量。

## 说明/提示

对于全部数据，$1 \le n, m \le 3 \times {10}^5$，$1 \le x_j, y_j, x'_j, y'_j \le {10}^9$，所有有序数对 $(x_j, y_j)$ 互不相同，所有 $x'_j$ 互不相同，所有 $y'_j$ 互不相同。

**翻译来源**：IOI 2021 集训队第一部分作业，PinkRabbit。

## 样例 #1

### 输入

```
7
1 1
4 2
6 2
5 3
2 5
4 7
7 5
4
4 4
8 2
9 6
6 5```

### 输出

```
2
1
3
2```

# 题解

## 作者：xxasmcd (赞：9)

对于这道题目给出一个例图：

![](https://cdn.luogu.com.cn/upload/image_hosting/hvlg1l88.png)

对于这个例图思路如下：

1. 每个栅栏先只计算**只被本身覆盖的点**（不被他的儿子覆盖，下面有儿子的定义）。例如上图 A 覆盖一个点，B 和 D 各覆盖两个点，C 覆盖一个点（怎么计算后面讲）。

1. **栅栏存在包含关系**，B 被 D 包含（先不管 D 被 C 栅栏挡住了），D 和 C 都被 A 包含，如果计算 A 包含了多少个点，等价于 D 包含的 +C 包含的+只被 A 包含的三部分的和。这种包含关系形成**树**结构，树结构用**父指针表示**比较方便。

1. 栅栏有时间先后关系，B 是 D 的儿子，但是因为 B 先发生，D 后发生，所以 B 的答案**不能传递累加**到父亲 D 上；上图中 D 和 A 的先后顺序从图中判断不出来，如果 D 先发生 A 后发生，则 D 的答案也不能传递到父亲 A 上，但是如果是 A 先发生，则 D 的答案需要传递到父亲 A 上。也就是说**儿子发生时间靠后才会影响父亲节点**，所以应该按照发生顺序从后往前处理，使用并查集。

1. 怎么计算每个栅栏本身覆盖的点（不被儿子覆盖）？先对所有栅栏和点按照 y 轴**由大到小**排序。上图的 x 点能被直接被哪个栅栏覆盖？肯定是被他右上角的栅栏覆盖，所以用 set 维护**已经处理**的栅栏的横坐标，找到与 x 最接近且横坐标大于等于 x 点的栅栏 D，然后令 $ cnt_{D} $ 加1。y 点貌似是被 D 覆盖，但是因为 C 在 D 之前发生，**所以实际应该算是被 C 覆盖**（D 比 C 先进入 set，因为 D 纵坐标大先处理），为了保证正确，在计算 C 栅栏时，把 C 插入 set，并且把 set 中横坐标小于 C 且发生时间在 C 之后的栅栏从 set 中删除，所以把 D 删除了，这样在处理 y 点时，set 中 C 与 y 最接近，所以 $ cnt_{C} $ 加 1。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,fa[600001],cnt[600001],ans[600001],f[600001];
struct node
{
    int x,y,t;
}p[600010];
set<pair<int,int> > s;
int find(int x)
{
    if(x==f[x])return x;
    else return f[x]=find(f[x]);
}
bool cmp(node a,node b)
{
    if(a.y!=b.y)return a.y>b.y;
    else return a.t>b.t;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>p[i].x>>p[i].y;
        p[i].t=0;
    }
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>p[i+n].x>>p[i+n].y;
        p[i+n].t=i;
    }
    sort(p+1,p+n+m+1,cmp);
    for(int i=1;i<=n+m;i++)
    {
        if(p[i].t==0)
        {
            set<pair<int,int> >::iterator it=s.lower_bound({p[i].x,p[i].t});
            if(it!=s.end())++cnt[it->second];
        }
        else
        {
            s.insert({p[i].x,p[i].t});
            set<pair<int,int> >::iterator it=s.find({p[i].x,p[i].t});
            if(++it!=s.end())fa[p[i].t]=it->second;
            while(1)
            {
                it=s.find({p[i].x,p[i].t});
                if(it==s.begin())break;
                it--;
                if(it->second>p[i].t)s.erase(it);
                else break;
            }
        }
    }
    for(int i=1;i<=m;i++)
    {
        f[i]=i;
    }
        for(int i=m;i>=1;i--)
        {
            ans[i]=cnt[find(i)];
            if(fa[i])
            {
                int x=find(i),y=find(fa[i]);
                f[x]=y,cnt[y]+=cnt[x];
            }
        }
    for(int i=1;i<=m;i++)
    {
        cout<<ans[i]<<endl;
    }
    return 0;
}

---

## 作者：wangziyue_AK (赞：3)

因为栅栏显然会把平面分成若干联通块。这道题离线后可以分成两个部分，第一部分是先找到被栅栏围成的每个联通块内的点数，第二步是算出每个栅栏柱实际围了多少个点。
## Part 1
首先每个点属于的联通块是上边界高于它的右边界最靠左的联通块。那我们把所有点和栅栏柱扔到一起按纵坐标排序，用一个按横坐标排序的 set 维护即可。但这样说不完整，因为一个栅栏柱所拥有的联通块可能被另一个放的更早的栅栏柱截胡一部分，所以我们考虑按纵坐标排序后它一旦被截胡那么在它下方它已经不会产生任何影响了，所以考虑加入一个栅栏柱后往左考虑，假如加入时间大于它就扔出 set，否则它就被拦住了，那么就停止截胡。因为所以栅栏柱至多只会被有效截胡一次，所以复杂度为  $O((n+m)\log{m})$。
## Part 2
那么我们知道每个联通块的点数后如何计算每个栅栏柱的答案呢？考虑每个栅栏柱能对它造成贡献的是它本身，以及完全属于它内部且时间晚于它的联通块。那么我们将每个栅栏柱向上边界高于它的右边界最靠左的联通块连边，建出一棵树，然后贡献就变成了子树中时间晚于它的权值和，那么我们考虑按时间排序，那么获取到子树和后它的祖先就不能获取到它的贡献了，那么就把它连向父亲的边断开。现在问题就变成了删边，求子树和。正着做难以维护，把问题反过来，就变成了加边，求子树和，用并查集即可轻松维护。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=6e5+5;
typedef pair<int,int> pii;
#define fi first
#define se second
typedef set<pii>::iterator si;
int n,m,fa[N],cnt[N],res[N],f[N];
set<pii> se;
struct xx{ 
	int x,y,t;
	inline bool operator <(const xx &ay) const{
		if(y!=ay.y) return y>ay.y;
		return t>ay.t;
	}
}a[N];
int find(int x){ return x==f[x]?x:find(f[x]); }
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].t=0;
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a[n+i].x,&a[n+i].y);
		a[n+i].t=i;
	}
	sort(a+1,a+n+m+1);
	//Part 1
	for(int i=1;i<=n+m;i++){
		pii nw={a[i].x,a[i].t};
		if(!a[i].t){
			si it=se.lower_bound(nw);
			if(it==se.end()) continue;
			cnt[(*it).second]++;
		}else{
			se.insert(nw);
			si it=se.find(nw);it++;
			if(it!=se.end()) fa[a[i].t]=(*it).second;
			while(!se.empty()){
				si it=se.find(nw);it--;
				if((*it).se>a[i].t) se.erase(it);
				else break;
			}
		}
	}
	//Part 2
	for(int i=1;i<=m;i++) f[i]=i;
	for(int i=m;i;i--){
		int x=find(i); 
		res[i]=cnt[x];
		if(!fa[i]) continue;
		int y=find(fa[i]);
		f[x]=y,cnt[y]+=cnt[x];
	}
	for(int i=1;i<=m;i++) printf("%d\n",res[i]);
	return 0;
}
```

---

## 作者：Lonelyhacker (赞：0)

学校模拟赛做到了，为梳理思路写下这篇题解。

## 题意

在平面直角坐标系的第一象限中，给你 $n$ 个“贡献点”$(x_i, y_i)$ 和 $m$ 个“检查点”$(x_i', y_i')$。“检查点”有时间顺序，每个检查点给出时都会向其左方和下方分别作水平和竖直直线，不断延伸直至与其它“检查点”发出的直线或坐标轴相交，并形成一个封闭图形。要求输出每个“检查点”在**给出时**所形成的封闭图形内包含的“贡献点”的个数。其中 $1 \le n, m \le 3 \times 10^5$。

保证点对 $(x_i, y_i)$ 两两不同，$x_i'$ 两两不同，$y_i'$ 两两不同。即“贡献点”位置不重复，“检查点”发出的直线不发生重合。

$1 \le n, m \le 3 \times 10^5$，$1 \le x_j, y_j, x'_j, y'_j \le 10^9$。

## 题解

#### Part 1：理清题意

可以通过手玩样例的方式搞懂这题想干嘛：

![](https://cdn.luogu.com.cn/upload/image_hosting/ajjzt3h9.png)

样例给的输出是：2 1 3 2。

第一个点很好理解，它圈住了两个点；第二个点也很好理解，只圈住一个点；第三个点虽然按照定义只圈到了 $(7, 5)$ 的点，但是看题目：**给出时**圈点数。而 $4$ 号“检查点”在 $3$ 号点之后才给出，所以在 $3$ 号点给出时是圈住了 $3$ 个点的。之后 $4$ 号点才把 $3$ 号点圈住的其中两个点圈住，所以答案是 $2$。

#### Part 2：解题

真的按照时间顺序，给出每个“检查点”时进行在线统计复杂度肯定会爆炸。正难则反，我们可以离线下来，求出最终情况后倒推回去。

将两种点全部按照 $(x_i, y_i, t_i)$ 的格式存起来，进行处理。

首先思考：离线后，如何找到将“贡献点”圈住的“检查点”。

一个很简单的想法：可以直接从“贡献点”（设为 $(x_0, y_0)$）的位置向右找到第一个 $x_0 \le x$ 的“检查点”。显然具有单调性，因此我们可以二分找到这个“检查点”。

但是这种想法在下面图示中就会假：（下面的叉是“贡献点”）

![](https://cdn.luogu.com.cn/upload/image_hosting/pr6sp4qm.png)

如图所示，按照上述方法找“检查点”，第一个不是我们想要的。形式化地说，在此种限制下，方法会失效：

$$
\begin{cases}
x_0 \le x_j \le x_i \\
y_i \le y_j \\
t_j \le y_j
\end{cases}
$$

因此，我们显然需要将 $(x_j, y_j)$ 从我们存储的集合中除去。我们可以令 $(x_j, y_j)$ 最先被处理，删去后便不必考虑这个“检查点”。

看到上面那么多的偏序，肯定是越少越好操作。自然而然地使用扫描线，按照 $(y_i, x_i, t_i)$ 分别为第一、二、三关键字降序排序，先消除 $y$ 的影响，这样考虑 $x$ 和 $t$ 的影响就好多了。

总结就是：碰到一个“检查点”时就删去满足上面条件的其它“检查点”。用代码实现就是直接`while`循环，找到第一个不满足条件的就`break`掉，因为后续的“检查点”绝对不可能满足上述条件，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/xxpe6rk6.png)

处理到红圈内的“检查点”时，会把打了红叉的“检查点”去掉，这样下面的小黑叉“贡献点”就不会收到影响了。

这样，我们上面的二分的想法就是正确的了。

接下来考虑两个“检查点”间的另一种情况：包含。

![](https://cdn.luogu.com.cn/upload/image_hosting/a2robp9s.png)

很简单，由于扫描线消除了 $y$ 的影响，所以我们直接找到第一个 $x_i \le x_j$ 的点 $(x_j, y_j)$ 即可。

综上，怎么从“贡献点”找到其所属的“检查点”，怎么除去其它“检查点”的影响，怎么处理包含关系这几个问题都解决了。这题就可做了。

最后倒序处理回去，处理到一个“检查点”直接找到它包含的“检查点”并加上它们的贡献，就是答案。可用并查集实现。

至于你问我这种情况：（“检查点”标的是时间，即这两个有先后顺序）

![](https://cdn.luogu.com.cn/upload/image_hosting/t22653eo.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

![](https://cdn.luogu.com.cn/upload/image_hosting/a9h6fsss.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

那么如果按你说的，在第一幅图里用这种方法，$2$ 号“检查点”找到它所包含的 $1$ 号检查点，还加上 $1$ 号点的贡献，那不就假了吗？

所以我们实现代码时耍一个小花招：在统计答案时按照时间倒序枚举，这样先处理后来的“检查点”$2$ 号，再处理“检查点”$1$ 号，就不会受影响了。

我还想过另一个问题：既然题目都提出了：保证 $x_i'$ 两两不同，$y_i'$ 两两不同，即“检查点”发出的直线不发生重合，那我们按照按照 $(y_i, x_i, t_i)$ 分别为第一、二、三关键字降序排序消除 $y$ 的影响，是不是后面的 $(x_i, t_i)$ 的排序是多余的？

我想了很久，才发现：我们排序的不止有“检查点”，还有“贡献点”啊。草。

## 代码

不懂的可以看看注释。

```cpp
#include <iostream>
#include <algorithm>
#include <set>
#define fs first
#define sc second
#define mp make_pair
#define pii pair <int, int>
using namespace std; 
const int N = 1e6+5;
int n, m, fa[N], outer[N], sum[N], ans[N];
set <pii> s;
int find(int x) { return fa[x] = fa[x] == x? x : find(fa[x]); }
void unite(int u, int v){
	int fu = find(u), fv = find(v);
	if (fu != fv){
		fa[fv] = fu;
		sum[fu] += sum[fv]; // 记得将贡献加上 
	} 
}
struct node{
	int x, y, t;
} a[2*N]; // 记得开两倍，因为贡献点和检查点都在这里面 
bool cmp(node x, node y){
	if (x.y != y.y) return x.y > y.y;
	if (x.x != y.x) return x.x > y.x;
	return x.t > y.t;
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> a[i+n].x >> a[i+n].y, a[i+n].t = fa[i] = i;
	sort(a+1, a+n+m+1, cmp);
	for (int i = 1, x, t; i <= n+m; i++){
		x = a[i].x, t = a[i].t;
		pii pr(x, t);
		if (!t){ // 贡献点 
			auto it = s.lower_bound(pr); // upper也行 
			if (it != s.end()) sum[it->sc]++; // 贡献加1 
		} else { // 检查点 
			s.insert(pr);
			auto it = s.find(pr);
			while (it != s.begin() && (--it)->sc > t){ // 不是第一个 且关系成立 
				s.erase(it); // 删掉再找一个新的 
				it = s.find(pr); // 注意这里要重新找，因为你把it删掉后再++或--是错的 
			}
			it = ++s.find(pr);
			if (it != s.end()) outer[t] = it->sc; // 处理包含关系 
		}
	}
	for (int i = m; i >= 1; i--){ // 细节倒序枚举 
		ans[i] = sum[find(i)];
		if (outer[i]) unite(i, outer[i]);
	}
	for (int i = 1; i <= m; i++) cout << ans[i] << '\n';
	
	return 0;
}
```

## 后日谈

本人第一篇紫题题解。

打 CSP-S 的 T4 就给我出这题，考试开摆，闲的慌，用原题机一搜是紫，直接给我干傻了。

---


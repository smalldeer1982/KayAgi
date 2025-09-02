# Party

## 题目描述

A club plans to hold a party and will invite some of its $ n $ members. The $ n $ members are identified by the numbers $ 1, 2, \dots, n $ . If member $ i $ is not invited, the party will gain an unhappiness value of $ a_i $ .

There are $ m $ pairs of friends among the $ n $ members. As per tradition, if both people from a friend pair are invited, they will share a cake at the party. The total number of cakes eaten will be equal to the number of pairs of friends such that both members have been invited.

However, the club's oven can only cook two cakes at a time. So, the club demands that the total number of cakes eaten is an even number.

What is the minimum possible total unhappiness value of the party, respecting the constraint that the total number of cakes eaten is even?

## 说明/提示

In the first test case, all members can be invited. So the unhappiness value is $ 0 $ .

In the second test case, the following options are possible:

- invite $ 1 $ and $ 2 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 3 $ );
- invite $ 2 $ and $ 3 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 2 $ );
- invite only $ 1 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 4 $ );
- invite only $ 2 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 5 $ );
- invite only $ 3 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 3 $ );
- invite nobody ( $ 0 $ cakes eaten, unhappiness value equal to $ 6 $ ).

 The minimum unhappiness value is achieved by inviting $ 2 $ and $ 3 $ .In the third test case, inviting members $ 3,4,5 $ generates a valid party with the minimum possible unhappiness value.

## 样例 #1

### 输入

```
4
1 0
1
3 1
2 1 3
1 3
5 5
1 2 3 4 5
1 2
1 3
1 4
1 5
2 3
5 5
1 1 1 1 1
1 2
2 3
3 4
4 5
5 1```

### 输出

```
0
2
3
2```

# 题解

## 作者：Hovery (赞：16)

# Problem

[Party](https://www.luogu.com.cn/problem/CF1711B)

题意大致为给你 $n$ 个点，各自的点权和连边关系，问：最多删去多少个点使删去的点权最小，且这些点所组成的图中有偶数条边。输出删去的点的点权总和。

# Sol

对于总边数，分为两种情况。

$1.\ m$ 为偶数，这种情况非常简单，保留所有点即可，因为边数为偶数，符合题目条件。

$2.\ m$ 为奇数，我们考虑这张图有没有什么特别的地方。

对于一条边，它会给两个点的度 $+1$ ，也就是说，度为奇数的点有偶数个（可以为 $0$ ）。

对于一个点，若一个点的度为奇数，我们可以考虑将其删除，这样剩下的边就会有偶数条。

对于两个点进行分类讨论。

考虑不相连的情况，若要使条件成立，必然其中一个点的度为奇数，另一个为偶数。

对于上面的情况显然是不优，因为点权只会是非负数，所以只删一个度为奇数的点一定会比删两个点优。

考虑两个点相邻，若要使条件成立，两个点的度之和必须为偶数。

对于一个点来说，它的一个度代表它连出去的一条边。

设删去的两个点是 $x$ 和 $y$ ，它们的度为 $a_x$ 和 $a_y$。

若删去它们，那被删去的边数就是 $a_x +a_y - 1$，减 $1$ 是因为有一条边多算了一次。

对于上面这种做法，只需要枚举每条边即可。

# Code

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define int long long
using namespace std;

int n, m, x[100010], y[100010], a[100010], ans, t;
vector<int>G[100010];

void solve()
{
	cin >> n >> m;
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i];
		G[i].clear();
	}
	for (int i = 1;i <= m;i++)
	{
		cin >> x[i] >> y[i];
		G[x[i]].pb(y[i]);
		G[y[i]].pb(x[i]);
	}
	if (m % 2 == 0)
	{
		cout << "0\n";
		return;
	}//情况一。
	ans = 1000000000000;
	for (int i = 1;i <= n;i++)
	if (G[i].size() % 2 == 1)
	ans = min(ans, a[i]);//枚举度为奇数的点。
	for (int i = 1;i <= m;i++)
	{
		if ((G[x[i]].size() + G[y[i]].size()) % 2 == 0)//枚举两个相邻的点。
		{
			ans = min(ans, a[x[i]] + a[y[i]]);
		}
	}
	cout << ans << endl;
}

signed main()
{
	cin >> t;
	while (t--)
	{
		solve();
	}
}
```

---

## 作者：IGJHL (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF1711B)

## 题意
有 $T$ 组数据，每组数据给你一组 $n, m$ 表示共有 $n$ 个人，$m$ 组朋友关系，及一个数组 $a$ 和 $m$ 组关系的具体值。其中 $a_i$ 表示当第 $i$ 人没有来参加聚会时，所带来的不快乐值。每对朋友会吃掉一个蛋糕。问在保证吃的蛋糕总数为偶数时，能达到的最小不快乐值。

## 转化
对于朋友关系及每个人，我们考虑建一个 $n$ 个顶点，$m$ 条边的无向图。其中的 $n$ 个顶点分别为 $1 \sim n$ 个人，$m$ 条边为其中的 $m$ 条朋友关系，即若两人有朋友关系，我们就在所建的图中编号对应的两点间连上一条无向边。

那么，问题就转换为了：

给出一个包含 $n$ 个点 $m$ 条边的图，及每个点的点权（$a$ 数组）。删掉一些点和有关的边，使得图中有偶数条边。求删掉的点的点权总和最小值。

## 方法
~~在这里就以文字叙述吧...~~

我们分类讨论一下。

1. $m$ 为偶数，则不需要删边或点，直接输出 $0$ 即可。
1. $m$ 为奇数，以下分三种情况讨论。

	1. 删一个点。显然，我们只能选择一个度为奇数的点。
 
   1. 删两个点。以下再分六种情况来讨论。
   
   		1. 两点度数均为偶且有边，那么能够保证删除后边为偶数个，则两点均删除。
      1. 两点度数均为奇且有边，那么能够保证删除后边为偶数个，则两点均删除。
      1. 两点度数一奇一偶但无边，如下图。
      ![](https://cdn.luogu.com.cn/upload/image_hosting/j74fjmv3.png)
      
	   虽然能够保证删除后边为偶数个，但只删除其中的奇点 $4$ 所获的不快乐值一定会更小，那么舍去这种情况。
      
      1. 对于上述三种情况下，若两点间有无边的条件相反的情况下，则删除后对边数的改变都是减少偶数条。如下图中删 $1$，$4$ 或 $5$，$7$ 或 $3$，$4$ 号点，对边数变化为偶数无用，所以也舍去这三种情况。

      ![](https://cdn.luogu.com.cn/upload/image_hosting/5injt41o.png)
      
	1. 删大于等于三个点。显然不会更优，也舍去（可以替换成只删一个或两个点的形式，不快乐值会更低）。
    
   	如下图
 		![](https://cdn.luogu.com.cn/upload/image_hosting/8bg4jz9k.png)
        
      若要删除 $5$，$6$，$1$ 号顶点，我们可以替换为只删除 $1$ 号点，也能使图中的边数边为偶数，且不快乐值更低。
      若要删除 $1$，$2$，$3$，$4$ 号顶点，我们可以转化为只删除其中的任意一个奇点。
      
      - 而若要删除更多的点，我们只需要替换为只删一个或两个点就行。
      
## 代码

      
我们发现不用把图建出来，记录每个点的度数即可。

```cpp
#include <iostream>
#include <vector>
#include <climits>

#define int long long

using namespace std;

const int N = 1e5 + 5;

int t, n, m, cnt = 0, ans = INT_MAX, a[N];

int d[N] = {0};//记录点的度数

vector <int> e[N];

int u[N], v[N];

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    
    cin >> t;

    while (t --) {
        cin >> n >> m;

        ans = INT_MAX;

        for (int i = 1; i <= n; ++ i)
            cin >> a[i], d[i] = 0;

        for (int i = 1; i <= m; ++ i) {
            cin >> u[i] >> v[i];
            
            ++ d[u[i]], ++ d[v[i]];//边的两端顶点度数加一
        }

        //m为偶
        if (m % 2 == 0) {
            cout << "0\n";

            continue;
        }
        
        //因为前面有了continue，所以不需要再加上else

        //删一个点
        for (int i = 1; i <= n; ++ i)
            if (d[i] % 2 == 1)
                ans = min(ans, a[i]);

        //删两个点
        for (int i = 1; i <= m; ++ i)
		    if ((d[u[i]] + d[v[i]]) % 2 == 0)//稍稍简化了一下，能够发现删两个点的情况都是两点度数和为偶数
			    ans = min(ans, a[u[i]] + a[v[i]]);
                
        cout << ans << "\n";
    }
    
    return 0;
}
```


------------

## Thanks For Reading


~~本来想传图的，但不知道怎么弄链接，所以就咕了。——感谢大佬帮助，我会乐。~~


---

## 作者：zhicheng (赞：3)

### 题意简述

~~比赛的时候看了10min才把题看懂，我太弱了~~

定义：一个无序对在集合中，当且仅当无序对的两个元素均在集合中。

给你一个有 $n$ 个元素的数列 $a$ 和 $m$ 个无序对，要求你在集合 $\{1,2,3,...,n\}$ 里选择一个集合（记为 $b$，记没有选的数 组成的集合为 $c$，设 $c$ 有 $x$ 个元素），使得在这 $m$ 个无序对中，在集合 $b$ 中的无序对的数量为偶数，并且对于 $i \in [1,x]$，$\sum a_{c_i}$ 最小。输出这个和。

### 思路

提供一种我赛时想出的、复杂度比官方题解稍优的、实现差不多但分析较简略的解法。

正难则反。我们设我们已经选择了所有的元素在 $b$ 里面，要删去一些元素。此时我们一定满足有 $m$ 个无序对。所以如果 $m$ 已经是偶数，就不用删，答案是 $0$。反之，我们就要在这 $m$ 个存在的对里面破坏掉奇数个。显然，如果一个元素，有奇数个无序对包含了它，那么如果我们删去这个元素，就可以破坏掉这些对，达到目标。否则我们先删除这一个元素，那么与这个元素在同一个对里的元素，现在就一定有奇数个对包含它。删去一个即可（见代码）。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int p[100010],f[100010];
struct d{
	int l,r;
}g[100010];
int main(){
	int n,a,b,ans;
	scanf("%d",&n);
	while(n--){
		ans=1e9;
		memset(f,0,sizeof(f));  //记得清空
		scanf("%d%d",&a,&b);
		for(int i=1;i<=a;i++){
			scanf("%d",&p[i]);
		}
		for(int i=1;i<=b;i++){
			scanf("%d%d",&g[i].l,&g[i].r);
			f[g[i].l]++;  //记录有几个对包含了这个元素
			f[g[i].r]++;
		}
		if(b%2==0){  //已经满足条件
			printf("%d\n",0);
			continue;
		}
		for(int i=1;i<=b;i++){
			if(f[g[i].l]%2){
				ans=min(ans,p[g[i].l]);  //情况1，有奇数个对包含这个元素
			}
			else if(f[g[i].r]%2==0){
				ans=min(ans,p[g[i].l]+p[g[i].r]);  //情况2，两个元素都有偶数个，先删第一个，再删第二个就能满足目标
			}
			if(f[g[i].r]%2){
				ans=min(ans,p[g[i].r]);  //同情况1
			}
		}
		printf("%d\n",ans);
	}
}
```

不得不说这个 Div2 B 确实跨度有点大

---

## 作者：CheemsaDoge (赞：2)

# CF1711B Party
## 原题题意
给定 $n$ 个点带点权的无向图，点权 $a_i$ 保证无重边自环，点权非负），要求删去一些点和它相连的边，使得剩下这个图的边数为偶数且删去点的点权之和最小。问删去点的点权之和最小是多少？

## 分类讨论
我们分类讨论一下。

- $m$ 为偶数，则不需要删边或点，直接输出 $0$ 即可。

- $m$ 为奇数，我们称有单数条边与其相连的点为单点，反之为双点。

  1. 删除一个点，则必须为单点（奇-偶=奇 奇-奇=偶）
  2. 删除两个点，若两点中有单点，则直接删除单点更优，所以应当删除两个双点；因为需要删除的总边数为单数，所以删除的双点应该有公共边：故删除一条边相连的两个双点满足题意。
  3. 删除三个点，不如删除一个或两个更优，故不考虑。


## 代码及注释
```cpp
/*code by Cheemsadoge*/
#include <bits/stdc++.h>
using namespace std;
template<typename T> inline void read(T &x) {
	x=0;T w=1,ch=getchar();
	while(!isdigit(ch)&&ch!='-')ch=getchar();
	if(ch=='-')w=-1,ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^'0'),ch=getchar();
	x=x*w;
}//fast input
const int MAXN=1e5+1145;
const int INF=2147483647ll;//2^31-1
struct Edge{int u,v;}edge[MAXN];	//边，u、v分别表示边相连的两点
struct Point{int val,stick,num;}point[MAXN]; //点，val表示边权（即不快乐值），stick表示与点所连的边数，num表示编号
int n,m,totr,ans=INF,wans=INF,num,a,b;
bool single[MAXN]; //判断i与i点所连的边数是否为单（是则赋值true）->single[i]即point[i].stick%2==1 
void add_edge(int u,int v){edge[++totr].u=u;edge[totr].v=v;point[v].stick++;point[u].stick++;} //加边
queue<Point>po;
void initialize()//初始化
{
		totr=0;ans=INF;wans=INF;
		memset(edge,0,sizeof(edge));
		memset(point,0,sizeof(point));
		memset(single,0,sizeof(single));	
}
int main() {
	Point u;
	int T;read(T);while(T--){
		initialize();
		read(n),read(m);		read(n),read(m);
		initialize();
		for(int i=1;i<=n;i++) read(point[i].val),point[i].num=i,po.push(point[i]);//暂时将点放入po队列，方便取用
		for(int i=1;i<=m;i++) read(a),read(b),add_edge(a,b);//加边
		if(m%2==0) {printf("0\n");continue;}//特判：若有偶数条边，则输出0.注意：不要把此句放在上两行前，否则会跳过输入
		while(!po.empty()){
			num=po.front().num;u=point[num];//等同于u=po.front; 
			if(u.stick%2) {ans=min(ans,u.val);single[u.num]=1;}//判断与点相连的边数是否为单，并将其中点权最小值存入ans
			po.pop();
		}
		for(int i=1;i<=m;i++) if((!single[edge[i].v])&&(!single[edge[i].u])) wans=min(wans,point[edge[i].u].val+point[edge[i].v].val);
		//枚举边，若所连两点的stick为复数，则将两点点权相加存入wans取最小
		printf("%d\n",min(ans,wans));//输出最小值
	}
}
```


---

## 作者：Bai_Kking (赞：1)

# 氵题鉴赏

~~注：本题解仅供和我一样的蒟蒻食用~~

## 题目翻译：

给定 $n$ 个点权分别为 $a_i$ 的点和 $m$ 条边，要求删去的某些点和它所连的边，使得图中剩余边数为**偶数**且**删去**的点权之和**最小**，求最小的点权之和。

## 思路

伪图论题，这其实是一道数学题。

### 想法一：穷举（谁会想到这种解法啊）

遍历每一个点，对于每一个点 $i$，都有删或不删 $2$ 种方案，总共有 $2^n$ 种选择。对于每一种选择，判断是否合法，再比较数值大小。

这种方法不是那么优惠，空间和时间都会**爆炸**，所以我们可以剪枝优化一下（为什么这种方法还要优化啊）。

考虑到若选择删除的点到了一定数量，就一定不是最优解了，所以可以**无脑**地选取 $\log{n}$ 作为边界进行剪枝。

但是即便这样复杂度也是相当的高。所以我们得出：这个思路不是**正解**。但其实，剪枝这个思路已经离正解不远了。

### 想法二：只删奇数

上面的想法一之所以会被我们否决，就是因为~~计算机的算力不够~~我们的想法不够成熟。

我们再考虑贪心。

题目中明显有两个约束条件：偶数，点权最小。

1. 若原图中边数为偶数，则答案为 $0$。

2. 若图中遍数为奇数，则我们考虑只用删 $1$ 个奇数点就可以了。

同时要求满足删去点权最小，那遍历每一个点，若为**奇数**，比较点权大小。

#### 推翻

这就是最终答案了吗？

理所当然认为这就是最优解，看起来是对的。

**但是**

这里举一个反例：

```
input:
5 5
1 2 3 4 5
1 2
1 3
1 4
2 3
output:
3
```

![](https://cdn.luogu.com.cn/upload/image_hosting/bu0dy2u8.png)

如上图所示

如果只考虑奇数点，我们的程序会傻乎乎地只管偶数点的情况，那就会删掉 $4$ 号点，结果就 $4$。

**但是**

我们仔细观察：如果我们删掉 $1$ 号和 $2$ 号，就会留下 $0$ 条边，满足题中的第一个约束，且现在我们删的点权之和只有 $3$，比 $4$ 小。

这是为什么呢？

原来！$1$ 号点和 $2$ 号点共用了一条公共边，使得两个偶点的总边数减 $1$。

原来！只删偶边也是可以的！

这就自然而然的引出了第三个想法——

### 想法三：分类讨论（正解）

这样我们的思路就很清晰了：

1. 奇数：先考虑只删**一个奇数点**：遍历所有点，比较出删奇数点的最小删点权。

2. 偶数：再考虑删偶数点：遍历所有边，计算出边的左右两端点的**总度数**，判断（总度数减 $1$）是否是奇数（因为两点有一条公共边所以要减 $1$），比较所有满足该性质的条件两点的点权和。

## 补充和说明

很明显，当考虑偶数点时只用考虑两个点，因为为既然两个偶点能找到满足题意，必然不用考虑三个偶点及以上；

那为什么不用考虑奇数和偶数一起的情况呢？

显然，既然一个奇数点能搞定的事情就不需要偶数点掺和。

所以综上，每次查询的时间复杂度为 $O(n+m)$，效率相当的高。

## Code

代码非常简单，甚至不需要建图。

~~（我说了这是一道伪图论题吧）~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int T,n,m;
int a[N];
int el[N],er[N];//记录每条边的左右两个端点 
int deg[N];//每个点的度数 
int main(){
//	freopen("graph.in", "r", stdin);
//	freopen("graph.out", "w", stdout); 
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			deg[i]=0;//每次询问重置数组
		}
		for(int i=1;i<=m;i++){
			scanf("%d%d",&el[i],&er[i]);
			deg[el[i]]++; deg[er[i]]++;
		}
		int minn=0x3f3f3f3f;
		if(m%2==0) minn=0;//特判：一开始边为偶数 
		//情况一:删一个奇数点(枚举所有点)
		for(int i=1;i<=n;i++){
			if(deg[i]%2) minn=min(minn,a[i]);
		}
		//情况二:删相邻两个偶数点(枚举所有边)
		for(int i=1;i<=m;i++){
			if((deg[el[i]]+deg[er[i]]-1)%2==1){
				minn=min(minn,a[el[i]]+a[er[i]]);
			} 
		}
		printf("%d\n",minn);
	}
	return 0;
}
```

完结撒花。

感谢你看到这里。

---

## 作者：IYSY2009I (赞：1)

一道质量对我来说很高的思维题。

[我的垃圾翻译](https://www.luogu.com.cn/paste/vs4fse9c)

首先，如果 $m$ 初始为偶数，那么很显然全邀请就可以，直接输出 $\texttt{0}$。

然后我们考虑 $m$ 为奇数的情况。

我们先考虑不邀请 $1$ 个人的情况，那么这个时候，我们只能不邀请一个有奇数对朋友关系的人。此时奇数 $-$ 奇数 $=$ 偶数。

我们再考虑不邀请 $2$ 个人的情况，那么这个时候，我们有两种邀请方法：

1. 不邀请两个有奇数对朋友关系且这两个人之间有朋友关系的人。此时奇数 $-$ 奇数 $-$ 奇数 $+1=$ 偶数。
1. 邀请一个有奇数对朋友关系一个有偶数对朋友关系且这两个人之间没有朋友关系的人。此时奇数 $-$ 奇数 $-$ 偶数 $=$ 偶数。但这个时候我们发现我们完全可以邀请那个有偶数对朋友关系的人。故该方法不优，舍弃。
1. 不邀请两个有偶数对朋友关系且这两个人之间有朋友关系的人。此时奇数 $-$ 偶数 $-$ 偶数 $+1=$ 偶数。

我们这个时候想一想，我们这个时候真的有可能不邀请大于等于 $3$ 个人并且是这个方案最优吗？我们发现，这是不可能的了。对于一个不邀请方案中的一组人 $(x,y)$，不管他们是什么样的情况（这里我懒得码字了，大家自己分类讨论推推），我们都可以只保留这两个人或者去掉这两个人，这样的新名单同样符合要求，且由于新名单是通过旧名单删去一些成员得到的，故新名单更优。如果新名单仍然大于等于 $3$ 个人，我们可以继续上面的操作，减少名单上不邀请的成员的数量。因此，我们只需要枚举不邀请一个人和不邀请两个人的情况，计算最小不快乐值即可。

又因为如果不邀请两个人，这两个人之间一定有朋友关系（至于为什么参见上文），所以时间复杂度为 $O(T(n+m))$。

代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
int du[100005];
int x[100005];
int y[100005];
int a[100005];
void cf(){
	int n=read(),m=read(),ans=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		ans+=a[i];
	}
	for(int i=1;i<=m;i++){
			x[i]=read(),y[i]=read();
			du[x[i]]++;
			du[y[i]]++;
		}
	if(m&1){
		for(int i=1;i<=n;i++)
			if(du[i]&1) ans=min(ans,a[i]);
		for(int i=1;i<=m;i++)
			if((du[x[i]]+du[y[i]]-1)&1) ans=min(ans,a[x[i]]+a[y[i]]);
		printf("%d\n",ans);
	}
	else printf("0\n");
	for(int i=1;i<=n;i++){
		du[i]=0;
		a[i]=0;
	}
	for(int i=1;i<=m;i++){
		x[i]=0;
		y[i]=0;
	}
	return;
}
int main(){
	int t=read();
	for(int i=1;i<=t;i++)
		cf();
	return 0;
}
```


---

## 作者：codemap (赞：1)

## 题目分析
可以将朋友关系转化成一个图，节点代表人，边表示两个人是朋友。

问题就转化为找到最大的子图，使得图中有偶数条边。

显然，当 $m$ 为偶数时，所有人都可以邀请。

当 $m$ 为奇数时，我们证明最多去掉两个人即可满足要求：

首先只要有一个点度数为奇数，则直接去掉它即可。

因此若需要去掉三个人，则三个点均须为偶节点，而它们整体度数需为奇，所以三个点内部必须连边，而任何两个偶点连边时，度数都会为奇，使得这两个点就可以满足要求，所以最优解最多为去掉两个节点。

因此，我们只需考虑去掉一个或两个节点。

一个节点时，我们只需找到生气值最小的奇节点。

两个节点时，我们只需枚举和偶节点连边的偶节点，找到最小怒气值之和。

最后取最小值即可。

枚举的复杂度只有 $O(n)$，$O(m)$ 级别，可以通过此题。

## 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int h[1000001],tot,a[1000001];
struct node
{
    int v;
    int next;
}e[1000001];
struct Node
{
    int id;
    int anger;
    int edge;
}f[1000001];
void addedge(int u,int v)
{
    tot++;
    e[tot].v=v;
    e[tot].next=h[u];
    h[u]=tot;
}
bool cmp(Node x,Node y)
{
    return x.anger<y.anger;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t,n,m,i,j,mmin,u,v,s;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        for(i=1;i<=max(m,n);i++)
        {
            f[i].edge=0;
            f[i].id=i;
            h[i]=0;
            e[i].v=0;
            e[i].next=0;
        }
        tot=0;
        for(i=1;i<=n;i++)
            cin>>f[i].anger;
        for(i=1;i<=m;i++)
        {
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
            f[u].edge++;
            f[v].edge++;
        }
        if(m%2==0)
        {
            cout<<"0\n";
            continue;
        }
        sort(f+1,f+n+1,cmp);
        for(i=1;i<=n;i++)
            a[f[i].id]=i;
        mmin=1e9;
        for(i=1;i<=n;i++)
            if(f[i].edge%2==1)
            {
                mmin=f[i].anger;
                break;
            }
        for(i=1;i<=n;i++)
        {
            if(f[i].anger>=mmin)
                break;
            if(f[i].edge%2==0)
                for(j=h[f[i].id];j;j=e[j].next)
                    if(f[a[e[j].v]].edge%2==0)
	            mmin=min(mmin,f[a[e[j].v]].anger+f[i].anger);
        }
        if(mmin==1e9)
        {
            s=0;
            for(i=1;i<=n;i++)
                s+=f[i].anger;
            cout<<s<<"\n";
        }
        else
            cout<<mmin<<"\n";
    }
    return 0;
}
```


---

## 作者：Shimotsuki (赞：1)

题意：俱乐部要邀请成员参加聚会，邀请规则如下：

- 成员们吃掉的蛋糕总数必须是偶数。

- 有些成员是朋友，一对朋友会共同吃掉一个蛋糕，而在聚会中没有朋友的人不会吃蛋糕。

- 如果没有邀请第 $i$ 位成员，则会给聚会带来 $a_i$ 的不开心值。

求一种邀请方案满足上述条件且不开心值最小，输出最小不开心值。

思路：首先可以把俱乐部成员之间的关系看成一张无向图。如果两名成员是朋友，则在两人之间建一条无向边。每名成员的朋友数就是该点的度数。设有 $m$ 对朋友，如果 $m$ 是偶数，则最小的不开心值为 $0$；如果 $m$ 是奇数，考虑如下做法：若一个点的度数为奇数，那么删掉该点边数便会成为偶数，符合要求；如果该点的度数是偶数，则删掉该点和与该点有边相连的最小不开心值点。我们只需对上述方案取删点的最小代价并输出即可解决该问题。

---

## 作者：13802919466djh (赞：0)

[更好的体验？](https://www.luogu.com.cn/blog/dujiahao123456/solution-cf1711b)

# 题意
给出一个包含 $n$ 个点 $m$ 条边的图，以及对应的点权。删掉一些点和有关的边，使得图中有偶数条边。问删掉的点的点权总和最小值。

# 解法
分类讨论。

当 $m$ 为偶数时，已经满足了条件，直接输出 $0$ 即可。

当 $m$ 为奇数时，有两种情况：第一种情况，如果一个点的度数是奇数，将它删除就会剩下偶数条边。我们枚举每个点。第二种情况，如果两个点的度数和是偶数并且之间有一条边，那么删除这两个点之后会剩下偶数条边。如果这两个点不相连，度数和只能为奇数，一定有一个点的度数是奇数，因为点权都是自然数，那么不如只删除这一个点。我们枚举每条边。

先统计一下每个点的度数。这道题就做完了。

# 代码
**Talking is cheap,show me the code.**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){int f=1,x=0;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1; ch=getchar();}while (ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}return x*f;}
inline void write(int x){if (x<0){putchar('-');x=-x;}if(x>9) write(x/10);putchar(x%10+'0');}
inline void Write(int x){write(x);putchar('\n');}
const int N=100005;
int t,n,m,cnt,ans,a[N],du[N];
struct edge{
	int u,v;
}e[N<<1];
signed main(){
	t=read();
	while (t--){
		n=read(),m=read();cnt=0;ans=2e9;
		for (int i=1;i<=n;i++)a[i]=read(),du[i]=0;
		for (int i=1;i<=m;i++){
			int u=read(),v=read();
			e[++cnt]=(edge){u,v};
			du[u]++,du[v]++;//统计度数
		}
		if (!(m&1)){Write(0);continue;}
		for (int i=1;i<=n;i++)
			if (du[i]&1)ans=min(ans,a[i]);
		for (int i=1;i<=cnt;i++)
			if (!((du[e[i].u]+du[e[i].v])&1))ans=min(ans,a[e[i].u]+a[e[i].v]);
		Write(ans);
	}
    return 0;
}
```

---

## 作者：shyr (赞：0)

### 题意

有 $n$ 个人和 $m$ 个关系，每个人有一个不满意度 $a_i$，现在有一个聚会，你可以选择邀请 $n$ 的人中的任意个人，使得最后由这些人构成的子图中，恰好有偶数条边，这个聚会的不满意度定义为没有选到的人的 $a_i$ 的总和，求出最小不满意度。

### 思路

有点清新的诈骗题。

首先如果边数本来就是偶数，那全部邀请即可，输出 $0$ 即可。

如果是奇数：

我们可以想到一个结论：子图的连边 = 原图的连边 - 没选中点的度数 + 没选中点的共同边数。

这就可以引申出一个推论：不选两个及以上互不连边的点的方案一定是不优秀的。

简单证明一下：设不选的点的度数为 $siz_i$。

- 若 $\exists{i}\in[1,n] siz_i$ 为奇数，那么根据第一个结论，只选择这个点即可。

- 若 $\forall i\in[1,n] siz_i$ 均为偶数，那么偶数加偶数仍然等于偶数，选择这些点没有意义。

那根据这个推论，我们可以对 $siz_i$ 进行分类讨论：

- 若 $siz_i$ 为奇数，直接将 $a_i$ 和备选答案取最小值即可。

- 若 $siz_i$ 为偶数，我们记录一个 $tmp_i$ 表示和 $i$ 互相连边的点中 $a_i$ 的最小值，根据第一个结论，此时不选择这两个点，最后的答案也是合法的，所以将 $tmp_i + a_i$ 和备选答案取最小值即可。

给出核心代码部分：

```
int n, m, t, u, v, a[100005], tmp[100005], in[100005]; 
int main(){
	t = read();
	while(t--){
		n = read(), m = read();
		int ans = 1e9; 
		for(int i = 1; i <= n; ++i){
			a[i] = read(); tmp[i] = 1e9; in[i] = 0;
		}
		for(int i = 1; i <= m; ++i){
			u = read(), v = read();
			tmp[u] = min(tmp[u], a[v]);
			tmp[v] = min(tmp[v], a[u]);
			in[u]++, in[v]++;
		}
		if(m % 2 == 0){
			puts("0");
			continue;
		}
		else{
			for(int i = 1; i <= n; ++i){
				if(in[i] & 1) ans = min(ans, a[i]);
				else ans = min(ans, a[i] + tmp[i]);
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
 
```

---


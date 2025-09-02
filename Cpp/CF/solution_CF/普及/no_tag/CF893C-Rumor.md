# Rumor

## 题目描述

Vova promised himself that he would never play computer games... But recently Firestorm — a well-known game developing company — published their newest game, World of Farcraft, and it became really popular. Of course, Vova started playing it.

Now he tries to solve a quest. The task is to come to a settlement named Overcity and spread a rumor in it.

Vova knows that there are $ n $ characters in Overcity. Some characters are friends to each other, and they share information they got. Also Vova knows that he can bribe each character so he or she starts spreading the rumor; $ i $ -th character wants $ c_{i} $ gold in exchange for spreading the rumor. When a character hears the rumor, he tells it to all his friends, and they start spreading the rumor to their friends (for free), and so on.

The quest is finished when all $ n $ characters know the rumor. What is the minimum amount of gold Vova needs to spend in order to finish the quest?

Take a look at the notes if you think you haven't understood the problem completely.

## 说明/提示

In the first example the best decision is to bribe the first character (he will spread the rumor to fourth character, and the fourth one will spread it to fifth). Also Vova has to bribe the second and the third characters, so they know the rumor.

In the second example Vova has to bribe everyone.

In the third example the optimal decision is to bribe the first, the third, the fifth, the seventh and the ninth characters.

## 样例 #1

### 输入

```
5 2
2 5 3 4 8
1 4
4 5
```

### 输出

```
10
```

## 样例 #2

### 输入

```
10 0
1 2 3 4 5 6 7 8 9 10
```

### 输出

```
55
```

## 样例 #3

### 输入

```
10 5
1 6 2 7 3 8 4 9 5 10
1 2
3 4
5 6
7 8
9 10
```

### 输出

```
15
```

# 题解

## 作者：Ptilopsis_w (赞：10)

## 1.思路
既然每一个人会免费告诉他的朋友，并且可以传递，所以每一堆朋友就可以看成一个整体，并查集维护朋友关系

因为要求每个整体的最小值，所以并查集维护时就可以比较新加入的这个点与原根节点，哪个比较小就把哪个作为根节点

最后查询时直接标记根节点就可以判断这个点所在整体是否已经计入答案

## 2.代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;

int n, m;
long long ans;
int a[100010];
int f[100010];
bool vis[100010];

int find(int x){ return f[x] == x ? x : f[x]=find(f[x]); }//压行是陋习 

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]), f[i] = i;
	for(int i = 1; i <= m; i++)
	{
		int x, y; scanf("%d%d", &x, &y);
		if(a[find(x)] > a[find(y)])//如果x比y大 
			f[find(x)] = find(y);  //就把y作为根节点 
		else//反之同理 
			f[find(y)] = find(x);
	}
	for(int i = 1; i <= n; i++)
	{
		if(!vis[find(i)])
		{//如果i所在集合的根节点没被标记，说明此集合未被计入答案 
			ans += a[find(i)];//累计答案 
			vis[find(i)] = true;//标记根节点 
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：EDqwq (赞：4)

~~谔评谔评！~~

### 思路：

我们想用最少的钱买秘密，就得把这个秘密卖给“最便宜的人”。

所以我们处理每个连通块，或者叫小团体（雾，找到这个团体里面“最便宜的人”，把这个秘密卖给他，处理完每一个小团体，加和即为答案。

怎么处理呢？

我们可以使用并查集，把每一个小团体的“最便宜的人”的价格保存在最大的祖先那里，合并的时候处理一下最小值，取一个min即可。

最后循环判断，当一个点是这个小团体最大的祖先（祖先为自己）时，加上它的值，因为这已经是最小值了。

***

### 代码：

```cpp
/*
  Author: EnderDeer
  Online Judge: Luogu
*/

#include<bits/stdc++.h>

#define int long long

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int n,m;
int a[100010];
int pre[100010];
int ans;

void build(){
	for(int i = 1;i <= n;i ++)pre[i] = i;
}

int find(int x){
	if(pre[x] == x)return x;
	else return pre[x] = find(pre[x]);
}

void join(int x,int y){
	int xx = find(x);
	int yy = find(y);
	if(xx != yy){
		pre[xx] = yy;
		a[yy] = min(a[xx],a[yy]);//处理这个小团体内的最小值 
	}
} 

signed main(){
	cin>>n>>m;
	build();
	for(int i = 1;i <= n;i ++)a[i] = read();
	for(int i = 1;i <= m;i ++){
		int x,y;
		x = read(),y = read();
		join(x,y);
	} 
	for(int i = 1;i <= n;i ++){
		if(find(i) == i)ans += a[i];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：BqtMtsZDnlpsT (赞：3)

传送门[CF893C Rumor](https://www.luogu.com.cn/problem/CF893C)

- 明显可以用最小生成树做。
- 首先把已经成为朋友的节点连到同一个集合内。
- 然后可以发现每个购买秘密的价值可以看做每个点与 $0$ 号节点的边（$0$ 号节点即为自己）。
- 再用最小生成树，枚举每一个点是否应该与 $0$ 号节点连边，并在未连通时加上连边的权值，这里用了Kruskal进行最小生成树。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n,m,fa[100005];
long long ans;
struct N{
	int u,v;
	inline bool operator<(N x){return u<x.u;}
}a[100005];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}//并查集
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i].u),a[i].v=i,fa[i]=i;
	sort(a+1,a+1+n);//排序
	for(int i=1,x,y;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		int fx=find(x),fy=find(y);//先把朋友连在一起
		if(fx!=fy)fa[fx]=fy;
	}
	for(int i=1;i<=n;i++)
	{
		int fx=find(a[i].v);
		if(fx!=0)fa[fx]=0,ans+=a[i].u；//每次判断是否与0号节点联通
	}
	printf("%lld",ans);
	return 0;
}
```

- #### Kruskal最小生成树：
	- 并查集
		- 刚开始的时候，森林里的每一个结点都是一个集合（也就是只有一个结点的树），之后根据题意，逐渐将一个个集合合并（也就是合并成一棵大树）。
    	- 寻找时不断查找父节点，当查找到父结点为本身的结点时，这个结点就是祖宗结点。
    	- 合并则是寻找这两个结点的祖宗结点，如果这两个结点不相同，则将其中右边的集合作为左边集合的子集（即靠左，靠右也是同一原理）。
	- Kruskal (by 机房巨佬 @$\color{red}Mine\_King$)
		1. 把所有边按顺序排序。
		1. 从第一条边开始枚举。
		1. 如果边的两端联通（用并查集判断），就跳过。
		1. 否则就加入这条边，并合并两个端点的集合。
		1. 重复3,4步直到枚举完。

---

## 作者：小小蒟弱 (赞：2)

## 思路：
按关系把人分成几个集合，求出每个集合价值最小值，就是此题的思路，很明显，用并查集。

并查集那么简单，不需要讲了吧，模板代码：

```cpp
int fa[100005], w[100005];

int Find(int x) {
	if (x == fa[x]) return x;  // 自己就是代表元
	else return fa[x] = Find(fa[x]);  // 寻找，并路径压缩 
}

void Merge(int x, int y) {
	if ((x = Find(x)) == (y = Find(y))) return ;
	fa[x] = y;  // 合并 
}

for (int i = 1; i <= n; i++)
	fa[i] = i;  // 初始化，自己就是自己的代表元
```

顺路在合并时把区间最小值求出来，方便起见，直接把所有元素最小值改为区间当前最小值，省去了那些选择代表元的事情，在合并的最后加上：
`w[x] = w[y] = min(w[x], w[y]);`即可。

## 完整代码
```cpp
#include <bits/stdc++.h>
#define int long long  // 不开 long long 见祖宗 

using namespace std;

int read() {  // 快读 
	int x = 0, k = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') k = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * k; 
} 

int fa[100005], w[100005], vis[100005];

int Find(int x) {
	if (x == fa[x]) return x;  // 自己就是代表元
	else return fa[x] = Find(fa[x]);  // 寻找，并路径压缩 
}

void Merge(int x, int y) {
	if ((x = Find(x)) == (y = Find(y))) return ;
	fa[x] = y;  // 合并 
	w[x] = w[y] = min(w[x], w[y]);
	// 直接求出一个集合内元素最小值 
}

signed main() {
	int n = read(), m = read(), ans = 0;
	for (int i = 1; i <= n; i++)
		w[i] = read(), fa[i] = i;  // 初始化，自己就是自己的代表元
	for (int i = 1; i <= m; i++) {
		int x = read(), y = read();
		Merge(x, y);  // 合并 
	}
	for (int i = 1; i <= n; i++) {
		int father = Find(i);
		if (!vis[father]) {  // 只加一次 
			ans += w[father];
			vis[father] = 1;  // 下次不加 
		}
	}
	printf("%lld", ans);
	return 0;  // 完结撒花 
}
```

---

## 作者：Arghariza (赞：1)

> 获得秘密的人会免费告诉它的所有朋友（他朋友的朋友也会免费知道）

明显使用并查集。

初始化很简单，咋合并呢？

由于最后的时候我们只用森林中每棵树最小的节点来加和，所以我们可以合并一次就把每棵树更新一次（父节点的权值为所有子节点权值中的最小值）。

这样就不用另外开一个数组来记录每一个人需要用多少钱啦，直接在原数组上进行更新操作即可。

代码里面有注释，如果还有不懂的可以百度。

```cpp
#include <bits/stdc++.h>// 万能头文件
#define int long long// 好东西，但不要忘了signed main
using namespace std;// 命名空间

int n, m, ans, s[100001], pre[100001];
// pre为并查集记录每个点的祖先的数组，
// s为这个点所在树的祖先（也就是最小值）

int getf(int root) {// 找祖先函数
    if(pre[root] == root) return root;// 如果找到了祖先直接返回
    else return pre[root] = getf(pre[root]);// 否则继续往上找，别忘记路径压缩
}

void merge(int root1, int root2) {// 合并函数
    root1 = getf(root1);// 先找到这个点的祖先
    root2 = getf(root2);// 同上
    if(root1 != root2) {// 如果俩点不在一棵树里
        pre[root2] = root1;// 合并，即一个点所在树成为另一个点所在树的子树
        s[root1] = min(s[root1], s[root2]);// 更新这棵树最小的权值
	}
}

signed main() {
	cin >> n >> m;// 输入点数与边数（也就是朋友数量）
	for (int i = 1; i <= n; i++) cin >> s[i];// 输入权值
	for (int i = 1; i <= n; i++) pre[i] = i;// 初始化，每个点都是自己的祖先
	for (int i = 1, u, v; i <= m; i++) {// 两个人变成朋友
		cin >> u >> v;// 输入两个朋友
		merge(u, v);// 合并并找到最小值
	}
	for (int i = 1; i <= n; i++) {// 计算ans
		if (getf(i) == i) ans += s[i];// 如果这个点是整棵树的根节点（最小值）就累加
	}
	cout << ans;//输出
	return 0;
}
```

---

## 作者：sinsop90 (赞：1)

一个人的朋友的朋友也能获得该信息

这不明显就是道并查集嘛

于是我们便有了以下想法:

1.在每一组朋友(朋友的朋友也算在同一组内)中找到价格的最小值

2.将所有组的最小值加起来即可

因此有了一下代码:

```
#include <bits/stdc++.h>
#define int long long
using namespace std;

int pre[100005];
int INF = 21474836487;
int n, k, mps[100005], p = 0, z = 0;
int yy[100005];
bool vis[100005];
int ans[100005], ansn;

void init() {
	for(int i = 1;i <= n;i++) {
		pre[i] = i;//并查集初始化
	}
}

int getf(int x) {//并查集模板
	if(x != pre[x]) return pre[x] = getf(pre[x]);
	else return x;
}

void com(int x, int y) {
	pre[getf(x)] = getf(y);
}
signed main() {
	cin >> n >> k;
	init();
	for(int i = 1; i <= n; i++) {
		cin >> mps[i];
		ans[i] = mps[i];
	}
	for(int i = 1; i <= k; i++) {
		int x, y;
		cin >> x >> y;
		com(x,y);
	}
	for(int i = 1;i <= n; i++) {
		if(getf(i) == i) {
			ans[i] = mps[i];//将不在任何一组的人的最小值赋为自己的价格
		}
	}
	for(int i = 1;i <= n; i++) {
		ans[getf(i)] = min(ans[getf(i)],mps[i]);//寻找每一组的最小值
	}
	for(int i = 1;i <= n; i++) {
		if(getf(i) == i) {
			ansn += ans[i];//将每一组的最小值加在一起
		}
	}
	cout << ansn << endl;
}
```


---

## 作者：Victorique_De_Blois (赞：1)

首先看到这个题目：

>那么简单，暴力随便过啊！

于是打了个暴力：

```cpp
#include<cstdio>
using namespace std;
int n,m,a[101000];
bool f[101000];
long long ans;
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;i++)
		scanf("%d",&a[i]),f[i]=true;
	for(register int i=1;i<=m;i++)
	{
		int f1,f2;
		scanf("%d",&f1);scanf("%d",&f2);
		if(a[f1]>a[f2])
			a[f1]=false;
		else
			f[f2]=false;
	}
	for(register int i=1;i<=n;i++)
	{
		if(f[i]==true)
			ans+=a[i];
	}
	printf("%lld",ans);
	return 0;
}
```
思路：给出两个关系，然后将较大的那一个标成`false`表示不选

然后wa了，因为成环了怎么办？很明显间接关系也可以传递到的

仔细想想，用并查集吧

代码：
```cpp
#include<iostream>
#include<cstdio>
#define RE register
#define inf 2147483647
int n,m;
unsigned long long ans;
int fa[100005],a[100005],re[100005];
int find(int x){
	while(x!=fa[x]) 
	{
		x=fa[x]=fa[fa[x]];
	}
    return x;
}
int main(){
	scanf("%d%d",&n,&m);
	for(RE int i=1;i<=n;++i)
		fa[i]=i,scanf("%d",&a[i]);
	int x,y;
	for(RE int i=1;i<=m;++i){
		scanf("%d%d",&x,&y);
		int f1=find(x);
		int f2=find(y);
		fa[find(x)]=find(y);
	}
	for(RE int i=1;i<=n;++i){
		if(find(i)==i){
			re[i]=inf;
		}
	}
	for(RE int i=1;i<=n;++i)
		re[find(i)]=std::min(a[i],re[find(i)]);
	for(int i=1;i<=n;++i){
		if(find(i)==i){
			ans=ans+re[i];
		}
	}
	std::cout<<ans;
	return 0;
}
```


---

## 作者：Rocket_raccoon_ (赞：1)

看到“知道秘密的人会把秘密告诉他的朋友（包括朋友的朋友）”就能看出，本题最简单的做法肯定是用并查集。   
并查集是个什么东西呢？实现起来非常简单（详见find函数，两行代码），但是可以快速的解决 集合合并 并且找出某个元素属于哪个集合的问题（通俗的说），不会的同学可以[戳这里](https://blog.csdn.net/u013546077/article/details/64509038)   
那么我们算最少花费的时候只需要加上每个联通集合的花费最小的那个人的钱数就行了，在这里我用的简单的处理方法（也不会优化），每次比较并查集头的花费和新加入的话费，如果新加入的钱较少就付钱给新加入的，用代码实现就是把并查集根的花费改成最小话费，然后不管新加入的钱是不是最少，把新加入的钱数清零（后面统计的时候去掉）。最后一遍循环把每个人的a[i]加起来就行了。    
代码如下：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long f[110000],a[110000];
long long ans;//怕爆掉，所以开的long long
int find(long long x){
	if (f[x]==x) return x;
	return f[x]=find(f[x]); 
}//并查集核心代码，兼具路径压缩和查找

int main(){
	long long i,n,m,x,y,a1,a2;
	
	cin>>n>>m;
	
	for (i=1; i<=n; i++){
		f[i]=i;//并查集的初始化
	}
	for (i=1; i<=n; i++){
		scanf("%lld",&a[i]);	
	}
	for (i=1; i<=m; i++){
		scanf("%lld %lld",&x,&y);
		a1=find(x);  a2=find(y);//找到x和y所属的集合
		if (a1!=a2){
			a[a1]=min(a[a1],a[a2]);//取最小值
			f[a2]=f[a1];
			a[a2]=0;//清零
		}
	}
	for (i=1; i<=n; i++){
		ans+=a[i];//统计
	}
	
	cout<<ans;
	
	return 0;
}
```

---

## 作者：_Kouki_ (赞：1)

### 思路：
因为朋友可以免费，所以这题是并查集。    
求最少得到的钱，要分为以下两步：   
1. 将朋友关系的人连在一块。
```cpp
/*
d 为 钱数。
这样做的目的是 保证 i 的 d[find(i)] 本块最小。
*/
	for(int i=1;i<=m;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        int fx=find(x),fy=find(y);
        /*
        当然你也可以不用这样，用 d 在 find 中
        打擂台。
        */
        if(d[fx]>d[fy]) {//合并操作
			p[fx]=fy; 
        }
		else {
			p[fy]=fx;
        }     
     }
```
2. 循环 $ ans $ 加上每个块的最小卖出值。
```cpp
    for(int i=1;i<=n;++i){
        int fa=find(i);
        if(!vis[fa]){
		ans+=d[fa];//累加
		vis[fa]=1; 
	 }
    }
```

### 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int  N=100050;
int n,m;
int p[N],d[N];
bool vis[N];
int find(int x){
    if(x!=p[x]){ 
        p[x]=find(p[x]);
    }
    return p[x];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        scanf("%d",&d[i]);
        p[i]=i;
    }
    for(int i=1;i<=m;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        int fx=find(x),fy=find(y);
        if(d[fx]>d[fy]) 
			p[fx]=fy; 
		else 
			p[fy]=fx;     
    }
    ll ans=0;
    for(int i=1;i<=n;++i){
        int fa=find(i);
        if(!vis[fa]){
			ans+=d[fa];
			vis[fa]=1; 
		}
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：xiezheyuan (赞：0)

## 思路

竟然朋友之间可以传递故事，那么，我们设两两有间接或直接的朋友关系的为一个友好集合，那么我们只要每一个友好集合买一次就好了。

那应该怎么买呢？由于题面让我们求的是【最少的价钱】，那我们可以考虑每一个集合让出钱出的最少的来买。

现在我们就要找一个数据结构维护这个集合了，需要支持：

- 连边(朋友之间）
- 找出钱出的最少的。

（我为什么想到了LCT?)

如果我们每一次连边都满足出钱少的连向出钱多的，那么就可以用并查集来维护了！

最后统计答案，只需要扫一遍，对于每一个人，如果他所在的集合中出钱最少的还没有买，那么就买。

总时间复杂的 $O(n+m\log n)$（并查集使用路径压缩优化）

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[1000005];

namespace UnionFind{
	int fa[1000005];
	int find(int x){
		if(fa[x]==x)return fa[x];
		else return fa[x]=find(fa[x]);
	}
	void merge(int x,int y){
		if(a[find(x)]>a[find(y)]){
			fa[find(x)]=find(y);
		}
		else{
			fa[find(y)]=fa[find(x)];
		}
	}
}

int n,m;
int isroot[1000005];
int ret=0;

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		UnionFind::fa[i]=i;
	}
	for(int i=1,liwenx,daniel2020;i<=m;i++){
		cin>>liwenx>>daniel2020;
		UnionFind::merge(liwenx,daniel2020);
	}
	for(int i=1;i<=n;i++){
		int rt=UnionFind::find(i);
		if(!isroot[rt]){
			ret+=a[rt];
			isroot[rt]=1;
		}
	}
	cout<<ret;
	return 0;
}
```

（其实这道题应该评绿，评蓝有点高）

---

## 作者：wangyibo201026 (赞：0)

## 思路

感觉这道题是并查集，但是不能一眼秒。

又因为要选齐 $n$ 个人，很容易想到最小生成树。

首先虚拟一个节点 $0$，将 $a_i$ 转化为边权。

第一个想法是针对于每条信息连一条边权为 $0$ 的边，但很容易证明出是假的。

我们可以针对每一条信息将并查集连接起来，再跑一遍最小生成树就可以了。

## 代码

代码：

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5 + 5;

int n, m, fa[N], sum, tot;

struct node{
	int u, v, w;
}a[N * 2];

bool cmp(node x, node y){
	return x.w < y.w;
}

int find(int x){    //并查集
	if(fa[x] == x){
		return x;
	}
	return fa[x] = find(fa[x]);
}

void unionn(int x, int y){
	x = find(x), y = find(y);
	if(x != y){
		fa[x] = y;
	}
}

signed main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		int w;
		cin >> w;
		a[++tot] = {i, 0, w};
	}
	for(int i = 1; i <= n; i++){
		fa[i] = i;
	}
	for(int i = 1; i <= m; i++){
		int u, v;
		cin >> u >> v;
		unionn(u, v);     //用并查集维护每一条信息
	}
	sort(a + 1, a + 1 + n, cmp);
	for(int i = 1; i <= n; i++){   //最小生成树，只不过这里简化了一下
		int fx = find(a[i].u);
		if(fx){
			unionn(fx, 0);
			sum += a[i].w;
		}
	}
	cout << sum;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

这道题目居然木有人发$\rm Tarjan$的题解？~~匪夷所思啊~~

这道题目一看就是$\rm Tarjan$的模板嘛。。。

算所需费用直接用暴力。。。

具体$\rm Tarjan$的定义以及思想请自行理解。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
const ll N=100005;
ll head[N],dfn[N],low[N],belong[N];
ll a[N],val[N],st[N];
ll n,m,ans,num,tot,top,col;
struct e
{
    ll nxt,to;
} edge[N*2];
using namespace std;
inline ll read()
{
    ll x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9')
    {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9')
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x*f;
}
void add(ll from,ll to)//双向边
{
    edge[++num].nxt=head[from];
    edge[num].to=to;
    head[from]=num;
}
void Tarjan(ll u)//Tarjan模板
{
    dfn[u]=low[u]=++tot;
    st[++top]=u;
    for (int i=head[u]; i; i=edge[i].nxt)
    {
        ll v=edge[i].to;
        if (!dfn[v])
        {
            Tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if (!belong[v]) low[u]=min(low[u],dfn[v]);
    }
    if (dfn[u]==low[u])
    {
        belong[u]=++col;
        while (st[top]!=u)
        {
            belong[st[top]]=col;
            top--;
        }
        top--;
    }
}
int main()
{
    n=read(),m=read();
    for (int i=1; i<=n; i++) a[i]=read();
    for (int i=1; i<=m; i++)
    {
        ll x,y;
        x=read(),y=read();
        add(x,y);
        add(y,x);//注意要双向边
    }
    for (int i=1; i<=n; i++) if (!dfn[i]) Tarjan(i);//Tarjan模板
    for (int i=1; i<=col; i++) val[i]=1e18;
    for (int i=1; i<=n; i++) val[belong[i]]=min(val[belong[i]],a[i]);//暴力
    for (int i=1; i<=col; i++) ans+=val[i];//加答案
    printf("%lld\n",ans);//输出
    return 0;
}
```

---


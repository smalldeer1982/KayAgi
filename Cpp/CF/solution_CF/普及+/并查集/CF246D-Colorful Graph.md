# Colorful Graph

## 题目描述

You've got an undirected graph, consisting of $ n $ vertices and $ m $ edges. We will consider the graph's vertices numbered with integers from 1 to $ n $ . Each vertex of the graph has a color. The color of the $ i $ -th vertex is an integer $ c_{i} $ .

Let's consider all vertices of the graph, that are painted some color $ k $ . Let's denote a set of such as $ V(k) $ . Let's denote the value of the neighbouring color diversity for color $ k $ as the cardinality of the set $ Q(k)={c_{u} : c_{u}≠k $ and there is vertex $ v $ belonging to set $ V(k) $ such that nodes $ v $ and $ u $ are connected by an edge of the graph $ } $ .

Your task is to find such color $ k $ , which makes the cardinality of set $ Q(k) $ maximum. In other words, you want to find the color that has the most diverse neighbours. Please note, that you want to find such color $ k $ , that the graph has at least one vertex with such color.

## 样例 #1

### 输入

```
6 6
1 1 2 3 5 8
1 2
3 2
1 4
4 3
4 5
4 6
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 6
4 2 5 2 4
1 2
2 3
3 1
5 3
5 4
3 4
```

### 输出

```
2
```

# 题解

## 作者：AKPC (赞：6)

本文已通过，只是纠正一下。

Update On 7.25：```unordered_map``` 用哈希实现的，是有误差的，但是更快，已纠正。感谢 @wangxuzhou 提醒。
### 思路
该题用 ```set``` 最优，但是我不用，蒟蒻只会 ```map``` 来草过本题。

简单说说 ```map``` 的性质：就是开了一个桶，可以用任意一种类型来当做下标存放某些东西。询问也很简单，跟数组是一样的访问方式，但是这比数组的容量更大，缺点是时间复杂度比普通数组更高。

相比之下，哈希可以解决时间复杂度与空间复杂度的问题，但是可能会有误差，而 ```map``` 可以完全避免这些误差，所以平时在建桶的时候，时间复杂度不大，而普通数组不能维护桶，就可以使用 ```map``` 了。

回归本题，每次建边都需要累计每个点的答案，即 $\text Q(k)$。但是这里不能重复计算同一种颜色，一种颜色只能算一次。但是如果开 $10^5\times10^5$ 的普通数组肯定炸内存，那么我们可以拿 $10^5+1$ 个 ```map``` 来存放每种颜色是否连接其他颜色。如果已经连上，不计入答案，反之计入答案之后做上标记。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[100001],ans[100001],x,y,maxn=-1,res;
map<int,bool>mp[100001];
bool tmp[100001];
signed main(){
	cin>>n>>m;
	for (int i=1;i<=n;i++) cin>>a[i],tmp[a[i]]=1;
	for (int i=1;i<=m;i++){
		cin>>x>>y;
		if (a[x]==a[y]) continue;
		if (!mp[a[x]][a[y]]) ans[a[x]]++;
		mp[a[x]][a[y]]=1;
		if (!mp[a[y]][a[x]]) ans[a[y]]++;
		mp[a[y]][a[x]]=1;
	}
	for (int i=1;i<=100000;i++) if (tmp[i]&&ans[i]>maxn) maxn=ans[i],res=i;
	cout<<res;
	return 0;
}
```


---

## 作者：wxzzzz (赞：5)

### 题意

求一种颜色 $k$，使得所有与其相邻的颜色种类最多。

### 思路

前置：map（在 [这个网页](https://www.cnblogs.com/wangxuzhou-blog/p/data-structure-preliminary.html) 往下翻）。

1. 记录下所有颜色种类。

1. 累计与每种颜色相邻的颜色种类数，用 map 去重。

1. 求最优的颜色。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, x, y, idx, cnts, ans, maxn = -1e9, c[100005], s[100005], cntc[100005];
bool flagc[100005];
map<pair<int, int>, bool> flag;
int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> c[i];

        if (!flagc[c[i]])
            s[++cnts] = c[i], flagc[c[i]] = 1;
    }

    while (m--) {
        cin >> x >> y;

        if (c[x] == c[y])
            continue;

        if (!flag[{c[x], c[y]}]) {
            cntc[c[x]]++, flag[{c[x], c[y]}] = 1;
        }

        if (!flag[{c[y], c[x]}]) {
            cntc[c[y]]++, flag[{c[y], c[x]}] = 1;
        }
    }

    sort(s + 1, s + 1 + cnts);

    for (int i = 1; i <= cnts; i++) {
        if (cntc[s[i]] > maxn) {
            maxn = cntc[s[i]], ans = s[i];
        }
    }

    cout << ans;
    return 0;
}
```

---

## 作者：chu_K (赞：4)

## 这是一道学习 std::set 的模板题。
首先看题面，然后我们可以发现：如果几个（$> 2$）颜色相同的顶点连在一起时，我们会多算，这时候就需要去重了，虽然有很多方法，但我认为还是用 `set` 最简单。

## 关于set
必须说明的是 `set` 关联式容器。 `set` 作为一个容器也是用来存储同一数据类型的数据类型，并且能从一个数据集合中取出数据，在 `set` 中每个元素的值都唯一，而且系统能根据元素的值自动进行排序。应该注意的是 `set` 中数元素的值不能直接被改变。C++ STL中标准关联容器 `set` ,  `multiset` ,  `map` , `multimap` 内部采用的就是一种非常高效的平衡检索二叉树：红黑树，也成为RB树(Red-Black Tree)。RB树的统计性能要好于一般平衡二叉树，所以被STL选择作为了关联容器的内部结构。------摘自网络

下面是 `set` 的一些操作
```c++
#include<set>
set<int> e;
a=e.begin();//    返回set容器的第一个元素
b=e.end();// 　　 返回set容器的最后一个元素
e.clear();//    　删除set容器中的所有的元素
if (e.empty());// 判断set容器是否为空
c=e.size();// 　　返回当前set容器中的元素个数
e.insert(a);//    将a插入到set中
```
而这道题，我们把所有不相同颜色的顶点丢到 `set` 里，最后扫一面取个 `max` 就行了。

## Code
```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
set<int> e[N];
int n,m,ans,u,v,a[N];
int main()
{
        cin >> n >> m;
        ans=1e9+7;
        for (int i=1; i<=n; i++) cin >> a[i],ans=min(ans,a[i]);
        for (int i=1; i<=m; i++)
        {
                cin >> u >> v;
                if (a[u]!=a[v]) e[a[u]].insert(a[v]),e[a[v]].insert(a[u]);
        }
        for (int i=1; i<=n; i++)
                if (e[a[i]].size()>e[ans].size())
                        ans=a[i];
        cout << ans << endl;
}
```

---

## 作者：shyr (赞：2)

考虑用 `set` 维护颜色为 $k$ 是不同颜色数量，容易发现均摊空间复杂度大概为 $\operatorname{O}(k\sqrt k)$，$k$ 为颜色最大值，可以通过此题。

坑点在于如果 $\forall i \in [1,k],Q(k) = 0$ 时要记录最小的颜色，统计答案时要判断有没有出现过这个颜色，当然一开始拿一个变量记也行。


代码：
```
#include<bits/stdc++.h>
using namespace std;
int n, m, a[100005], len, tong[100005];
set<int> d[100005];
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]), len = max(len, a[i]), tong[a[i]] = 1; 
	for(int i = 1, u, v; i <= m; ++i){
		scanf("%d%d", &u, &v);
		if(a[u] != a[v] && d[a[u]].find(a[v]) == d[a[u]].end()){
			d[a[v]].insert(a[u]);
			d[a[u]].insert(a[v]);
		}
	} 
	int maxn = -1, maxx = 0;
	for(int i = 1; i <= len; ++i){
		if(maxn < (int)d[i].size() && tong[i]){
			maxn = (int)d[i].size();
			maxx = i;
		}
	}
	printf("%d\n", maxx);
} 
```


---

## 作者：Ninelife_Cat (赞：1)

~~有 ```set``` 我不用，我就要用 ```map```，诶就是玩~~。

题目给出 $Q\left(k\right)$ 的定义是：

>定义 $Q\left(k\right)$ 是所有颜色为 $k$ 的所有顶点相连的不同的颜色的总数量（不包含 $k$）

那么我们只要在输入边的时候，判断这条边所连的两个顶点的颜色是否不同，再更新该顶点相连的不同颜色的数量即可。

接下来还需要去重。按照常规思路我们会拿一个 ```vis``` 数组记录某种颜色是否被计算过，但这题 $n$ 和 $c$ 的范围都是 ```1e5``` 级别的，那么就需要一个 ```1e5```$\times$```1e5``` 的二维数组，这显然会炸内存。

考虑到边数最多也只有 ```1e5``` 条，所以点的总数不超过 ```2e5``` 个，这样的话我们就可以开 $n$ 个 ```map``` 来代替二维数组了。

核心代码：

```cpp
const int N=1e5+10;
int n,m,a[N],x,y,cnt[N],f[N];//cnt记录相连不同颜色的数量
map<int,bool> vis[N];//vis[i][j]表示顶点颜色为i,相连的点的颜色为j是否被计算过
signed main()
{
	n=read();m=read();
	for(ri int i=1;i<=n;++i)
		a[i]=read(),f[a[i]]=1;//f记录这种颜色有没有出现过,如果该颜色没出现过就不能用来更新答案
	for(ri int i=1;i<=m;++i)
	{
		x=read(),y=read();
		if(a[x]==a[y]) continue;
		if(!vis[a[x]][a[y]]) ++cnt[a[x]],vis[a[x]][a[y]]=1;
		if(!vis[a[y]][a[x]]) ++cnt[a[y]],vis[a[y]][a[x]]=1;
	}
	ri int maxn=-inf,ans=-1;
	for(ri int i=1;i<N;++i)
		if(f[i]&&cnt[i]>maxn) maxn=cnt[i],ans=i;	
	cout<<ans;
	return 0;
}
```

---

## 作者：流绪 (赞：1)

每个点的颜色的范围最大是 1e5,那么我们可以开个数组来记录每个点与和他颜色不同的点的数量就行啦,然后成功 WA 啦

再读题发现了一个点可能与多个颜色相同的点相连,那么这些点应该只被记录一次,所以需要去重,那么我们可以用 set 来存,他可以帮助我们去重,接下来就枚举每一个点,选出有最多不同颜色点的最小编号就行啦

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
set<int>p[1000010];
int a[1000010];
int main()
{
	ios::sync_with_stdio(false);
	int n,m;
	cin >> n>> m;
	int minn=0x7f7f7f7f;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i];
		minn = min(minn,a[i]);//记录最小的点颜色
	}
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin >> u >> v;
		if(a[u]!=a[v])
		{
			p[a[u]].insert(a[v]);
            p[a[v]].insert(a[u]);//记录每个点连的不同色点
		}
	}
	int ans = minn;
	for(int i=1;i<=n;i++)//枚举每一个点来比较
	{
		if(p[a[i]].size() > p[ans].size())
			ans = a[i];
	}
	cout << ans;
}
```


---

## 作者：lrmlrm_ (赞：1)

# 题意

有 $ N $ 个点 ， 每个顶点对应一种颜色 ， 可以相同 。 给出连接这些顶点的 $ M $ 边 ， 定义 $ Q ( k ) $是所有颜色为 $ k $ 的所有顶点相连的不同的颜色的总数量（不包含 $ k $ ） ， 求使得 $ Q(k) $ 最大时的 $ k $ 的值 , 如果有多个 $ k $ 值满足 ， 输出最小的 $ k $ 值 。

# 思路

 [ set ](https://wenku.baidu.com/view/f185bd25bdd5b9f3f90f76c66137ee06eff94e95.html) 模板题 。
 
 以下是  set  的基本操作 :
 
 ```cpp
 set<int>se;//定义一个 set 容器
 se.clear();//清空 se 中所有的元素
 se.begin()//返回 se 中的第一个元素
 se.end()//返回 se 中的最后一个元素
 se.empty()//判断 se 是否为空
 se.insert(x)//向 se 中插入元素 x
 ...
 ```
 
 在这道题中 ， 我们只需要把所有不相同颜色的顶点插入 到  set  中 ， 再用 $ \max $ 找出其中的最大值即可 。
 
 # 代码
 
 ```cpp
 #include<bits/stdc++.h>
using namespace std;
set<int>se[100010];
int n,m,ans=2147483647,s,t;
int a[100010];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),ans=min(ans,a[i]);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&s,&t);
        if(a[s]!=a[t])se[a[t]].insert(a[s]),se[a[s]].insert(a[t]);
    }
    for(int i=1;i<=n;i++)
            if(se[a[i]].size()>se[ans].size())
                    ans=a[i];
    printf("%d",ans);
    return 0;
}
 ```

---

## 作者：Silvestorm (赞：0)

### 题目大意

[题目链接](https://www.luogu.com.cn/problem/CF246D)。

有 $N$ 个点，每个顶点对应一种颜色，可以相同。给出连接这些顶点的 $M$ 边，定义 $Q(k)$ 是所有颜色为k的所有顶点相连的不同的颜色的总数量（不包含 $k$ ），求使得 $Q(k)$ 最大时的k的值，如果有多个 $k$ 值满足，输出最小的 $k$ 值。

### 题目类型

图。

### 思路

一眼看上去是道图论题，这篇题解也是用类似图的方法过的。

要做什么，题目给的很清楚，关键是怎么做。显然如果存图存的是节点的话，无疑是舍近求远，可以直接存它的颜色，因为 $c_i$ 的值不超过 $10^5$，显然可以用桶存下。

但这就产生了一个问题，会有重边，以及自环。这需要进行处理，处理完之后，遍历一遍桶，取最大值所在的位置即可。

这道题在绿题上还是比较简单的。

### 附上代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, m, a, b, ans, tem, num[1010000], arr[100100];
vector<ll> v[100100]; // 存颜色
void solve()
{
    for (int i = 0; i < 100001; i++)
        arr[i] = -1; // 初始化桶，因为答案会有0出现，所以要赋负数
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> num[i];
        arr[num[i]] = 0; // 颜色节点存在，不管是否与其它点联通，都赋值为0
    }
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        if (num[a] != num[b]) // 去自环
        {
            v[num[a]].push_back(num[b]);
            v[num[b]].push_back(num[a]);
        }
    }

    for (int i = 0; i < 100001; i++)
    {
        arr[i] += v[i].size(); // 将Q(k)转移到桶里，这样去重边就好处理
        sort(v[i].begin(), v[i].end());
        for (int j = 1; j < v[i].size(); j++)
            if (v[i][j] == v[i][j - 1])
                arr[v[i][j]]--; // 去重边
    }
    tem = -1;
    for (int i = 0; i < 100001; i++)
    {
        if (arr[i] > tem)
        {
            ans = i;
            tem = arr[i];
        }
    }
    cout << ans << '\n';
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}
```


---

## 作者：MspAInt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF246D)

duel bot.duel bot.duel bot.

考虑对边统计。一条边如果两端颜色不同，那么会分别贡献到这两个颜色。但是一对颜色只能统计一次，所以还要开个 map 存储两两颜色之间是否相邻过。

最后取个最小的最优颜色即可。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,c[N],s[N],x[N],y[N],ans;
map<int,bool>l[N];
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&c[i]);
    for(int i=1;i<=m;i++)scanf("%d%d",&x[i],&y[i]);
    for(int i=1;i<=m;i++){
        int X=c[x[i]],Y=c[y[i]];
        if(X==Y)continue;
        if(!l[X][Y])s[X]++;l[X][Y]=1;
        if(!l[Y][X])s[Y]++;l[Y][X]=1;
    }
    s[0]=-1;
    for(int i=1;i<=n;i++)
        if(s[c[i]]>s[ans]||s[c[i]]==s[ans]&&c[i]<ans)ans=c[i]; 
    printf("%d\n",ans);
    system("pause");
    return 0;
}
```

[record](https://www.luogu.com.cn/record/123774441)

---

## 作者：Inui_Sana (赞：0)

 [题目传送门](https://www.luogu.com.cn/problem/CF246D)

解题思路：set

看到这道题，一开始想的是开一个记录每个颜色与多少个与自己不同色的点相连。每次有一条边，只要 $a_{i}$ 和 $b_{i}$ 不同，就将两种颜色数量都 $+1$。然后顺利地 wa 了。

为什么呢？

因为可能会有两条不同的边，其两对应顶点颜色相同。换句话说，可能颜色 $a$ 有两条边与颜色 $b$ 相连。

所以这题就要用到 set 进行去重。最后扫一遍取最大的 size 就行了。

代码：

```cpp
#include<cstdio>
#include<cmath>
#include<set>
using namespace std;
typedef long long ll;
const int maxn=1e5+7,inf=2147483647;
const int mod=1;
int n,m,ans,e[maxn];
set<int> box[maxn];
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&e[i]);
	ans=e[1];
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		u=e[u];v=e[v];
		if(u!=v){
			box[u].insert(v);
			box[v].insert(u);
		}
	}
	for(int i=1;i<=n;i++){
		if(box[e[i]].size()>box[ans].size()||(box[e[i]].size()==box[ans].size()&&e[i]<ans))ans=e[i];
	}
	printf("%d",ans);
}
```

---


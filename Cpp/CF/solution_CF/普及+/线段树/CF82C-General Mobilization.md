# General Mobilization

## 题目描述

The Berland Kingdom is a set of $ n $ cities connected with each other with $ n-1 $ railways. Each road connects exactly two different cities. The capital is located in city $ 1 $ . For each city there is a way to get from there to the capital by rail.

In the $ i $ -th city there is a soldier division number $ i $ , each division is characterized by a number of $ a_{i} $ . It represents the priority, the smaller the number, the higher the priority of this division. All values of $ a_{i} $ are different.

One day the Berland King Berl Great declared a general mobilization, and for that, each division should arrive in the capital. Every day from every city except the capital a train departs. So there are exactly $ n-1 $ departing trains each day. Each train moves toward the capital and finishes movement on the opposite endpoint of the railway on the next day. It has some finite capacity of $ c_{j} $ , expressed in the maximum number of divisions, which this train can transport in one go. Each train moves in the direction of reducing the distance to the capital. So each train passes exactly one railway moving from a city to the neighboring (where it stops) toward the capital.

In the first place among the divisions that are in the city, division with the smallest number of $ a_{i} $ get on the train, then with the next smallest and so on, until either the train is full or all the divisions are be loaded. So it is possible for a division to stay in a city for a several days.

The duration of train's progress from one city to another is always equal to $ 1 $ day. All divisions start moving at the same time and end up in the capital, from where they don't go anywhere else any more. Each division moves along a simple path from its city to the capital, regardless of how much time this journey will take.

Your goal is to find for each division, in how many days it will arrive to the capital of Berland. The countdown begins from day $ 0 $ .

## 样例 #1

### 输入

```
4
40 10 30 20
1 2 1
2 3 1
4 2 1
```

### 输出

```
0 1 3 2 ```

## 样例 #2

### 输入

```
5
5 4 3 2 1
1 2 1
2 3 1
2 4 1
4 5 1
```

### 输出

```
0 1 4 2 3 ```

# 题解

## 作者：lmgoat (赞：2)

## 题意简述
有一个国家有 $n$ 个城市，这 $n$ 个城市构成了一棵树。每个城市初始时有一个师的军队，第 $i$ 个师的优先级为 $a_i$。现在所有师都要沿最短路径去到首都 1 号城市。第 $i$ 条边连接的两个城市之间有一辆火车，每天可以被 $c_i$ 个师通过。如果同一天有多个师需要通过第 $i$ 条边， $a$ 值低的师先通过。从第 0 天开始算，求出每个点到达首都的时间。
## Solution
先从 1 号城市 *dfs*，记录每一个城市的前驱和这条边的 $c$ 值，从而记录最短路径。显然一个师不会受 $a$ 值比它小的师的影响，所以按 $a$ 值从小到大排序，方便处理。之后枚举每个师，顺着前驱向根走。每到一个点，只要能算出等待的时间就行了。可以暴力维护这个东西。用一个二维数组记录在每一天每个点连接其父亲的火车已经容纳了几个师。在算等待时间的时候直接从当前时间往后枚举天数，找到第一个还没装满的火车加入即可。

看上去很暴力，但能过，实际跑出来相当于常数大点的 $\Theta(n^2)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int read() {
	int f(0),x(0);
	char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
void write(int x) {
	if(x>=10) write(x/10);
	putchar(x%10+'0');
}
const int N=5005;
int n,ans[N];
int hed[N],nxt[N<<1],to[N<<1],c[N<<1],cnt;
void add(int x,int y,int cc) {nxt[++cnt]=hed[x],to[cnt]=y,c[cnt]=cc,hed[x]=cnt;}
struct node {
	int v,id;
	bool operator < (const node &y) const{
		return v<y.v;
	}
} a[N];
int fa[N],d[N];
void dfs(int x,int fath,int dd) {
	fa[x]=fath,d[x]=dd;
	for(int i=hed[x];i;i=nxt[i])
		if(to[i]!=fath) dfs(to[i],x,c[i]);
}
int b[N][N];
signed main() {
	n=read();
	for(int i=1;i<=n;++i) a[i].v=read(),a[i].id=i;
	sort(a+1,a+1+n);
	for(int i=1,x,y,cc;i<n;++i) {
		x=read(),y=read(),cc=read();
		add(x,y,cc),add(y,x,cc);
	}
	dfs(1,0,0);
	for(int i=1;i<=n;++i) {
		int x=a[i].id,res=0;
		while(x!=1) {
			for(int i=res;;++i)
				if(b[x][i]<d[x]) {
					++b[x][i],res+=(i-res)+1;
					break;
				}
			x=fa[x];
		}
		ans[a[i].id]=res;
	} 
	for(int i=1;i<=n;++i) write(ans[i]),putchar(' ');
	return 0;
}
```


---

## 作者：y_kx_b (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF82C)

$n\leqslant 5000$，看上去真的很像神奇的 dp 呢。~~（实际上就是暴力）~~

Sol1：$O(n^2\log n)$

~~还以为 $n=5000$ 就是卡这个做法的，结果我这个做法跑的比 $O(n^2\alpha(n))$ 还快/oh。~~

设 $ans_{u,v}$ 表示 $v$ 点的人向上到 $u$ 点耗时，考虑转移：$u$ 子树内的点都在 $u$ 点（到达 $u$ 点的时间都已知），我们要模拟地算出他们向上爬到 $fa_u$ 点的耗时。

那么按时间为第一关键字排序，每次把所有到达 $u$ 点时间均为 $t$ 的点按 $a_i$ 为关键字放入一个小根堆，然后 pop （$u$ 到  $fa_u$ 的边权）个点将其 $ans$ 设为 $t+1$，剩余的点可以视为是在 $t+1$ 时刻插入的，然后继续插入所有 $t+1$ 的点重复上述过程即可。（当堆里没有元素的时候我们可以直接令 $t$ 为下一个元素的 $t$。）

单次复杂度 $O(siz_u\log n)$，其中 $siz_u$ 表示 $u$ 的子树大小。总复杂度 $O(n^2\log n)$。代码实现有点复杂。[code](https://codeforces.com/contest/82/submission/224244036)。

Sol2：$O(n^2\alpha(n))$

考虑到 $a$ 大的一定不会影响 $a$ 小的，那么我们按照 $a$ 从小到大处理每个点。剩下就是模拟了：如果当前边这个时刻满了就尝试下一个时刻，在第一个不满的时刻走这条边。暴力复杂度我不会证，于是写了并查集（`fa[i]` 为大于等于 $i$ 的时刻里第一个不满的时刻）优化“找某时刻右边的第一个不满时刻”这一过程。

upd：后来发现这样写需要证明最终答案 $\leqslant n$ 才行（不然数组爆了）。感性证明一下：假设所有 $c_i$ 都为 $1$。那么考虑 $u\to fa_u$ 这条边，一定是在 $siz_u$ 的时间内把子树内所有点运完的（每次运一个）。连续性可以归纳证明（单个点当然是连续的；儿子的子树都是连续的，那第 $1$ 时刻起一直到儿子的子树运完为止必定有儿子到该点，所以不会断）。如果加大 $c_i$，答案不劣。所以每个点到根节点所花时间一定不超过 $n$。

[code](https://codeforces.com/contest/82/submission/224244565)。

解法很多，其他解法可以参照其他题解。

撒花……？

---

## 作者：lxuyinc (赞：0)

## 前言

### 注：原题解有笔误之处，再次修改，望周知。

- **“其实世上本没有翻译，看不懂的人多了，也便有了翻译。”**

## 题意

本题的题意概括简洁明了，便不多赘述。

~~其实我也不知道还能怎么解释得更好。~~


## 思路

默认一号节点为根，理想情况下，即当边权足够大的情况下，那么各点到一号节点的用时就是两点间的边数，但边权实际上限制了通过的军队数，怎么办？

### 到这里的时候，脑海里有了几种想法：

- 想到限流时，下意识就想打个网络流，但看了看题目难度，想想应该不可做，至少就我的能力而言。

- 从叶子节点出发跳祖先，每次汇合时判断是否有要留下的，但看了看时间复杂度会炸，就我自己打的暴力代码而言，不可行。

### 想到这里，思路也差不多出来了：

$n\leq 5000$ 能接受 $\operatorname O(n^2)$ 的时间复杂度，既然边跳边判断不可行，那就且先跳了再说。

我们选择从根节点开始 DFS 遍历整棵树，记录下最短路径。

一个值得思考的点,即 $a$ 值较小者不受较大者的影响，则依次进行从小到大排序。

之后就是模拟了：
暴力枚举每个点，沿着路径跳父节点，注意处理等待时间，处理时可以用一个二维数组维护边权使用程度（按题意来说就是维护火车容纳师的数量，从该天向后枚举，直到有空车可容纳），最后用一维数组储存答案便可。

## code


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e3+2;
int n,fa[N],wi[N],sum[N],h[N],cnt;
struct edge{
	int nxt,to,val;
} e[N<<1];
void add(int u,int v,int w){
	e[++cnt].nxt=h[u];
	e[cnt].to=v;
	e[cnt].val=w;
	h[u]=cnt;
}
struct node{
	int pr,id;
	friend bool operator <(node a,node b){
		return a.pr<b.pr;
	}
} s[N];
void dfs(int u,int f,int w){
	fa[u]=f;
	wi[u]=w;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f) continue;
		dfs(v,u,e[i].val);
	}
}
int dis[N][N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i].pr;
		s[i].id=i;
	}
	sort(s+1,s+1+n);
	for(int i=1,u,v,w;i<n;i++){
		cin>>u>>v>>w;
		add(u,v,w);add(v,u,w);
	}
	dfs(1,0,0);
	for(int i=1;i<=n;i++){
		int u=s[i].id,ret=0;
		while(u>1){
			for(int j=ret;;j++){
				if(dis[u][j]<wi[u]){
					dis[u][j]++;
                    ret=j+1;
					break;
				}	
			}
			u=fa[u];
			sum[s[i].id]=ret;
		}
	}
	for(int i=1;i<=n;i++) cout<<sum[i]<<" ";
	return 0;
}
```








---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF82C)
## 思路
简单题。

考虑先对点按 $a_i$ 从小到大排序，然后就变成了模拟题。

先一遍 $\verb!dfs!$ 求出每一个节点的 $pre$，然后接下来暴力跳，若该节点已经变成 $1$ 或该节点与该节点的 $pre$ 之间的边的容量已经被用完了，那么改不了，否则改为该点的 $pre$。

时间复杂度 $O(n^2)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=5e3+10;
struct node{int w,id,yuan;}w[N];
inline bool cmp(node x,node y){return x.w<y.w;}
vector<int>a[N];
int b[N][N],pre[N],q[N];
inline void dfs(int x,int fa){pre[x]=fa;for (auto v:a[x]) if (v!=fa) dfs(v,x);}
signed main(){
    //读入
    for (int i=1;i<=n;++i) 读入,w[i].id=w[i].yuan=i;
    for (int i=1;i<n;++i){
        int u,v,w;
        io.read(u);io.read(v);io.read(w);
        a[u].push_back(v);
        a[v].push_back(u);
        b[u][v]=b[v][u]=w;
    }
    dfs(1,0);
    sort(w+1,w+n+1,cmp);
    for (int p=1;p<n;++p){
        vector< pair<int,int> >rever;
        for (int i=1;i<=n;++i){
            if (w[i].id==1 || !b[w[i].id][pre[w[i].id]]) continue;
            rever.push_back({w[i].id,pre[w[i].id]});
            --b[w[i].id][pre[w[i].id]];
            --b[pre[w[i].id]][w[i].id];
            w[i].id=pre[w[i].id];
            if (w[i].id==1){q[w[i].yuan]=p;}
        }
        for (auto i:rever) ++b[i.first][i.second],++b[i.second][i.first];
    }
    for (int i=1;i<=n;++i) io.write(q[i]),io.push(' ');io.push('\n');
    return 0;
}
```


---


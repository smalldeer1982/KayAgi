# [ABC131F] Must Be Rectangular!

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc131/tasks/abc131_f

$ 2 $ 次元平面上の $ N $ 個の点があり、$ i $ 番目の点の座標は $ (x_i,\ y_i) $ です。

以下の操作を行える限り繰り返します。

- 座標 $ (a,\ b),\ (a,\ d),\ (c,\ b),\ (c,\ d) $ のうちちょうど $ 3 $ 箇所に点が存在するような整数 $ a,\ b,\ c,\ d\ (a\ \neq\ c,\ b\ \neq\ d) $ を選び、残りの $ 1 $ 箇所に点を追加する。

この操作は有限回しか行なうことができないことが証明できます。操作回数の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ x_i,\ y_i\ \leq\ 10^5 $
- $ x_i\ \neq\ x_j $ または $ y_i\ \neq\ y_j\ (i\ \neq\ j) $
- 入力は全て整数である

### Sample Explanation 1

$ a\ =\ 1,\ b\ =\ 1,\ c\ =\ 5,\ d\ =\ 5 $ とすると $ (1,\ 5) $ に点を追加することができます。これ以上操作を行うことはできないので、操作回数の最大値は $ 1 $ 回です。

### Sample Explanation 2

$ 2 $ 点しか点がないので操作を $ 1 $ 回も行うことができません。

### Sample Explanation 3

$ a\ =\ 1,\ b\ =\ 1,\ c\ =\ i,\ d\ =\ j\ (2\ \leq\ i,j\ \leq\ 5) $ の全てに対して操作を行うことができ、それ以上操作を行うことはできないので、操作回数の最大値は $ 16 $ 回です。

## 样例 #1

### 输入

```
3
1 1
5 1
5 5```

### 输出

```
1```

## 样例 #2

### 输入

```
2
10 10
20 20```

### 输出

```
0```

## 样例 #3

### 输入

```
9
1 1
2 1
3 1
4 1
5 1
1 2
1 3
1 4
1 5```

### 输出

```
16```

# 题解

## 作者：洛璟 (赞：18)

## Translate:
在一个平面上，有 $n$ 个点，每个点拥有一个坐标 $(x,y)$。若存在三个点 $(ax,ay)$，$(ax,by)$，$(bx,ay)$，且 $ax\neq bx$，$ay\neq by$ 时，若第四个点 $(bx,by)$ 不在已有的点中，则可以加入 $(bx,by)$ 这个点，求最多可以加入几个点。

## Solution:

首先看到平面等关键词时，我们首先尝试在草稿纸上画图。

以样例#3为例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/9an2ou06.png)

我们可以发现，第一列列上的每一个点，可以与第一行上的每一个点配对，直到组成一个 $5\times 5$ 的矩形。

这是特例？我们再来一个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/ubc4c5ju.png)

乍一看： ![?](https://cdn.luogu.com.cn/upload/image_hosting/yhb4u9br.png)

我们来分析一下：

首先，我们来手动处理一下前两行，不难发现我们完全可以像第一个例子一样造出一个 $2\times 4$ 的矩形，然后我们再手动模拟一下已经填满了的第二行和第三行能否结合（这边建议在草稿纸上画图），不难发现其实第三行也是可以填满的。以此类推，我们会发现，这张图最后就变成了一个 $4\times 5$ 的矩形。那这个时候，也许大家已经能够找出规律了 ~~，其实这道题就是一个填矩形的游戏。~~

但说了那么多，眼尖的同学其实一眼就能发现，题目中给出的四个点的坐标其实是可以构建一个矩形的……

以上为人脑模拟的思路，下面为代码实现过程。

那问题来了，既然是一个画矩形的题目，那么怎么判断哪一行哪一列是哪一个矩形的呢？

那么要请出我们的一个找归属关系的大佬：并查集。

并查集相关知识，不再赘述，但是我们在这里用并查集可以找出每一个矩形点最多的那一行和那一列，从而由此计算出答案。

我们把每一行、每一列都看成一个个体，那么其实我们就可以把这每一行每一列进行合并，然后通过列的个数判断这个矩形有多少行，通过行的个数判断矩形有多少列，同时对所有处于同一行、同一列的点进行合并。（可能有点绕，但事实如此）。

举个例子更容易理解吧：

![](https://cdn.luogu.com.cn/upload/image_hosting/z7213odn.png)

对于蓝色这个点，它属于第一行，那么我们就可以将第一行的祖先指向第二列，但是又因为红色点已经被遍历过，并且将其的祖先指向了第一列，那么其实我们的第二个点，便将第一个点的祖先，以及第一个点的祖先的祖先，也就是第一列的祖先，改为了第二列，后面同理，这时，整个已有的点所代表的行与列全部指向了第四列，也就是说，在第一二三四列的所有点，他们的祖先是同一人，也就代表他们在同一个集合内，那么对于每一列呢？我们可以把图旋转一下便同理了。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100010
using namespace std;
int n, fa[500010], h[500010], l[500010];
int ans;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
int find(int x)
{
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
signed main()
{
    n = read();
    for (int i = 1;i <= N + N;++i)//因为最多有1e5行和1e5列因此要全部初始化
    {
        fa[i] = i;
    }
    for (int i = 1;i <= n;++i)
    {
        int x = read(), y = read();
        int fx = find(x);
        int fy = find(y + N);
        if (fx != fy)//并
        {
            fa[fx] = fy;
        }
    }
    for (int i = 1;i <= N;++i)
    {
        ++h[find(i)];//一行最多的个数
    }
    for (int i = N + 1;i <= N + N;++i)
    {
        ++l[find(i)];
    }
    for (int i = 1;i <= N + N;++i)
    {
        ans += h[i] * l[i];
    }
    printf("%lld", ans - n);//减去一开始有的个数便是答案
    return 0;
}
```

---

## 作者：fengenrong (赞：4)

### 题意
有 $n$ 个点，假如有 $(a,b)$，$(a,d)$，$(c,b)$，$(c,d)$ 中任意 $3$ 个点，则可以添加剩下那一个点，求最多可以多放多少个点。

### 分析
首先，我们我们观察如下两张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/g1qpx0gg.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/aupv6c37.png)

图一中黑圆代表原本有的点，图二的红勾代表新增的点。我们不难发现，其实题目就是想让我们找出若干联通块，让每个联通块拼成一个长方形。

那么如何求联通块呢？我们可以用到并查集。我们可以将横坐标相同的点的编号合并，再将纵坐标相同的点的编号合并，我们就可以得到联通块了。对于每一个联通块，我们只需要用 `set` 求出横坐标和纵坐标分别有多少个不重复的坐标，也就是联通块的长度和宽度。最后我们用长度和宽度相乘，再减去联通块原有的点就是答案了。

于是，我们不难调出如下代码。
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,ans;
struct Point{
    int x,y;
}a[100005];//记录点的信息
set<int> xx[100005],yy[100005];//存每个点的横，纵坐标的可能
int father[100005],cnt[100005];//每个点的父节点和数量
bool cmp1(Point x,Point y){return x.x<y.x;}//按横坐标排
bool cmp2(Point x,Point y){return x.y<y.y;}//按纵坐标排
int find(int x){return x==father[x]?x:father[x]=find(father[x]);}//找祖先
void add(int X,int Y){
    int x=find(X),y=find(Y);
    if(x==y) return;//一样就不用合并
    father[y]=x,cnt[x]+=cnt[y];//合并
    for(auto i:xx[y]) xx[x].insert(i);//将两个点的横坐标的所有可能更新
    for(auto i:yy[y]) yy[x].insert(i);//将两个点的纵坐标的所有可能更新
}
map<pair<int,int> ,int> num;//存原本编号
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&a[i].x,&a[i].y);
        num[make_pair(a[i].x,a[i].y)]=father[i]=i,cnt[i]=1;//初始化
        xx[i].insert(a[i].x),yy[i].insert(a[i].y);//初始化
    }
    sort(a+1,a+n+1,cmp1);
    for(int i=2;i<=n;i++) if(a[i].x==a[i-1].x) add(num[make_pair(a[i].x,a[i].y)],num[make_pair(a[i-1].x,a[i-1].y)]);//合并
    sort(a+1,a+n+1,cmp2);
    for(int i=2;i<=n;i++) if(a[i].y==a[i-1].y) add(num[make_pair(a[i].x,a[i].y)],num[make_pair(a[i-1].x,a[i-1].y)]);//合并
    for(int i=1;i<=n;i++) if(find(i)==i) ans+=(xx[i].size()*yy[i].size())-cnt[i];//求答案，并累加
    printf("%lld\n",ans);
    return 0;
}
```
但是，你会发现，超时！

所以，我们必须将它优化。首先，我们可以把 `map` 删了，在结构体里多加一个变量记录原本编号，并再用数组记录原本对应的横坐标与纵坐标。其次，我们可以再合并的时候比较一下怎样合并次数更少，就用那种方法合并。

可是，依然超时。我们很容易看出，导致超时的其实就是合并后将两个点的坐标的可能更新太慢。所以我们可以记录一下每个点分别有哪些点与其合并。最后在求的时候，用搜索搜出即可。于是，我们终于调出正确代码。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,ans;
struct Point{
    int x,y,num;//num用来记录原本对应的值
}a[100005],Jl[100005];//Jl用来记录原本点的坐标
set<int> xx[100005],yy[100005];
int father[100005],cnt[100005];
bool cmp1(Point x,Point y){return x.x<y.x;}
bool cmp2(Point x,Point y){return x.y<y.y;}
int find(int x){return x==father[x]?x:father[x]=find(father[x]);}
vector<int> jl[100005];//记录每个点与其合并的点
void add(int X,int Y){
    int x=find(X),y=find(Y);
    if(x==y) return;
    if((xx[y].size()+yy[y].size())<(xx[x].size()+yy[x].size())) swap(x,y);
    father[y]=x;
    cnt[x]+=cnt[y];
    jl[x].push_back(y);//加入
}
queue<int> q;//用于后面bfs
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&a[i].x,&a[i].y);
        Jl[i].x=a[i].x,Jl[i].y=a[i].y;
        a[i].num=father[i]=i,cnt[i]=1;
    }
    sort(a+1,a+n+1,cmp1);
    for(int i=2;i<=n;i++) if(a[i].x==a[i-1].x) add(a[i].num,a[i-1].num);
    sort(a+1,a+n+1,cmp2);
    for(int i=2;i<=n;i++) if(a[i].y==a[i-1].y) add(a[i].num,a[i-1].num);
    for(int i=1;i<=n;i++)
        if(father[i]==i){
            q.push(i);
            while(!q.empty()){
                int now=q.front();
                xx[i].insert(Jl[now].x),yy[i].insert(Jl[now].y);//放入set中
                q.pop();
                for(auto i:jl[now]) q.push(i);
            }//bfs
            ans+=(xx[i].size()*yy[i].size())-cnt[i];//更新
        }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Nicrobot (赞：3)

不妨维护行与列的连通性，考虑对于点 $(x,y)$，把行 $x$ 和列 $y$ 合并在一起。最终，对于形成的每个**连通块**（不妨定义为每个集合内的**行、列的所有交点**，**而不是**框起来的部分），其内部所有空白的点一定可以与另外三个给定的点形成一个矩形；多个连通块之间的点不能形成矩形。

因此，设每个连通块包含的行和列的数量为 $a_i,b_i$，已经给定的点数量为 $sz_i$，答案即 $\sum(a_ib_i-sz_i)=(\sum a_ib_i)-n$。

并查集维护即可，代码是好写的。

---

## 作者：MspAInt (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc131_f)

题意是能够与某三个点（可以是新添加的 bot 点）形成矩形的点称为 bot 点，最多能添加几个 bot 点。

想了半个下午发现完全不能直接统计，考虑增加一个点有什么用：

![](https://cdn.luogu.com.cn/upload/image_hosting/us1k4sg2.png)

把行列连起来了。

对于一个点 $(x_i,y_i)$，我们试着把 $x_i$ 和 $y_i$ 用并查集连在一起。

发现对于一个联通块，包含在其中的行列 之间两两匹配的交点 一定对应了一个存在或不存在的 bot 点，先把这个统计出来。

容斥一下，我们想要的是不存在的点，而题目所给的 $n$ 个点显然都可以是 bot 点，减去 $n$ 就是答案。

核心思路需要长时间的画图理解，建议自行尝试。

这个题可能站在二分图四元环的角度看更能理解，希望有人能把这个口胡的东西付诸实践 /cy

Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int n,x[N],y[N],r[N],c[N],f[N];
int getfa(int x){return f[x]==x?x:(f[x]=getfa(f[x]));}
void merge(int x,int y){x=getfa(x);y=getfa(y);f[x]=y;}
ll ans;
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=2e5;i++)f[i]=i;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&x[i],&y[i]);
        merge(x[i],y[i]+1e5);
    }
    for(int i=1;i<=1e5;i++)r[getfa(i)]++;
    for(int i=1e5+1;i<=2e5;i++)c[getfa(i)]++;
    for(int i=1;i<=2e5;i++)ans+=1ll*r[i]*c[i];
    printf("%lld\n",ans-n);
    // system("pause");
    return 0;
}
```

[record](https://www.luogu.com.cn/record/135005785)

---

## 作者：MadokaKaname (赞：1)

感觉这题比较偏 CF 风格。

先脚造几组数据手玩一下，发现每一个点就像一条边一样把行和列连了起来，而每一个连起来的块内点的大小是正好填满的。

自然想到并查集。

将每一个点的 $x$ 和 $y$ 通过并查集连起来，扫的时候用 ```unordered_set``` 维护这个并查集中横坐标的个数和纵坐标的个数，两个大小相乘，最后减掉 $n$ 即可。


## code
```cpp
#include <bits/stdc++.h>
#include <unordered_set>
#define LL long long
using namespace std;
struct edge{
	LL to,nt;
}a[200005];
LL n,i,j,k,m,ans=0,cnt1=0;
LL fa[200005],cnt[200005],sum[200005],x[200005],y[200005],nxt[200005];
unordered_set<LL> st1[200005],st2[200005];
LL father(LL x){
	if(fa[x]!=x) return fa[x]=father(fa[x]);
	else return x;
}
void add(LL x,LL y){
	a[++cnt1].to=y;a[cnt1].nt=nxt[x];nxt[x]=cnt1;
}
int main() {
    scanf("%lld",&n);
    for(i=1;i<=200000;i++)
      fa[i]=i;
    for(i=1;i<=n;i++){
    	scanf("%lld%lld",&x[i],&y[i]);
    	cnt[x[i]]++;cnt[y[i]+100000]++;
    	add(x[i],y[i]);add(y[i]+100000,x[i]);
        if(father(x[i])!=father(y[i]+100000)) fa[fa[y[i]+100000]]=fa[x[i]];
	}
    for(i=1;i<=200000;i++){
    	if(i<=100000){
    		for(j=nxt[i];j;j=a[j].nt)
    		  st1[father(i)].insert(a[j].to);	 
        }
        else {
        	for(j=nxt[i];j;j=a[j].nt)
        	  st2[father(i)].insert(a[j].to);
		}
	}
	for(i=1;i<=100000;i++)
	  ans+=st1[i].size()*st2[i].size();
	printf("%lld",ans-n);
	return 0;
}

```


---

## 作者：Hughpig (赞：0)

发现直接统计加入多少个点有点难，考虑用最后的总点数减去原来的点数。

发现对于一个点，如果存在一个点和它横坐标相同，另一个点和它纵坐标相同，那么这三个点就可以再加一个点出一个四边形。新加入的点还能继续和原有的点构成长方形。

记一堆能构成长方形的点的最大集合为一个连通块。模拟一下可以发现，最后一个连通块的形态必然为一个大长方形，每行每列都被放满。

否则如果有空缺，可以在旁边找到点把空缺加进来。如果加不进来可以把空缺边上的空缺再加上。还加不进来？那么就构不成连通块了。

（这么说好像有点抽象，建议画个图理解一下）

由此可以推出即一个点能构出的长方形个数是它的连通块所在行的个数乘以所在列的个数。

拿并查集维护这个东西，把横坐标相同的点扔进一个集合，纵坐标相同的点扔进一个集合，然后对每个连通块统计行的个数和列的个数，加进答案即可。

记得最后答案要减去 $n$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define up(l,r,i) for(int i=(l);(i)<=(r);++i)

constexpr int N=1e5+9;

ll n,fa[N*2+7],a[N*2+7],b[N*2+7],ans;

ll getfa(ll x){
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}

int main()
{
	//ios_optimize();
    int TestCases=1;
    //cin>>TestCases;
    while(TestCases--){
		cin>>n;//cout<<n<<' ';
		up(1,N+N,i)fa[i]=i;
		for(int i=1;i<=n;++i){
			//cout<<i<<' ';
			ll x,y;cin>>x>>y;
			x=getfa(x),y=getfa(y+N);
			if(x!=y)fa[x]=y;
		}
		up(1,N,i)++a[getfa(i)];
		up(N+1,N*2,i)++b[getfa(i)];
		for(int i=1;i<=N*2;++i)ans+=a[i]*b[i];
		cout<<ans-n<<'\n';
    }
	return 0;
}
```

---

## 作者：cyq32ent (赞：0)

在并查集中，对于任意点 $(x,y)$，从 $r_x$ 到 $c_y$ 连边。（其中 $r_x$ 为第 $x$ 行，$c_y$ 为第 $y$ 列）

我们考虑点 $(x,y)$ 被添加的充要条件。考虑命题 $P(x,y)$ 为“并查集中 $r_x,c_y$ 在一个连通块里”；那么如果 $(x,y)$ 可以被添加，那么一定存在 $(x,y'),(x',y),(x',y')$ 在给定的点集里，或者可以被添加。这时，$r_x,c_y,r_{x'},c_{y'}$ 在同一个连通块内。反之，如果 $r_x,c_y$ 在同一个连通块内，那么它们要么直接通过某条边连接（这时这个点在给定的点集里），要么间接通过某些点连接（沿着这些点可以找到一种方法添加点 $(x,y)$）。代码很简单：

```cpp
#include<bits/stdc++.h>
using namespace std;
int64_t n,x,y,i,a,p[1<<18],q[1<<18],f[1<<18];
int F(int x){return x==f[x]?x:(f[x]=F(f[x]));}
int main(){
	cin>>n;for(;++i<=2e5;)f[i]=i;
	for(i=1;i<=n;i++)cin>>x>>y,x=F(x),y=F(y+1e5),f[x]=y;
	for(i=0;++i<=1e5;)p[F(i)]++,q[F(i+1e5)]++;
	for(i=0;++i<=2e5;)a+=p[i]*q[i];cout<<a-n;
}

```

---

## 作者：Leaper_lyc (赞：0)

将每个二元组 $(x,y)$ 看成平面直角坐标系上的点。

那么每个拓展操作就是：找到三个点作为矩阵的三个顶点，补齐最后一个顶点。

当不能操作时，所有的矩形都被补充完整了，每个联通块看上去就是一个大矩形被若干平行线和垂线分割成若干个矩形的样子。

可以发现，每个联通块的答案就是该联通块的最终的点数就是行数和列数的乘积。

考虑用并查集维护，对于点 $(x,y)$，用并查集连接行 $x$ 和列 $y$，就可以算出每个连通块的行数和列数了。

那么答案就是所有联通快的行列乘积减去本来就存在的 $n$ 个点。

代码很短：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
const int M = 1e5;
#define int long long
int n, ans = 0;
int fa[N], a[N], b[N];
inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
signed main() {
	cin >> n;
	for (int i = 1; i <= M + M; i++) fa[i] = i;
	for (int i = 1, x, y; i <= n; i++) {
		cin >> x >> y; y += M;
		x = find(x), y = find(y);
		if (x != y) fa[x] = y;
	}
	for (int i = 1; i <= M; i++) b[find(i)]++;
	for (int i = M + 1; i <= M + M; i++) a[find(i)]++;
	for (int i = 1; i <= M + M; i++) ans += a[i] * b[i];
	cout << ans - n;
}
```

---

## 作者：Expert_Dream (赞：0)

我们发现，能够合成一个长方形，肯定是有三个点，可以组合成一个直角三角形，在另一个点建一个新点。

发现这三个点有个性质。如果两个点的 $x$ 或者 $y$ 相同则归在一个集合内，那么这三个点必定会属于合并到一个集合内。

我们又发现，只有在一个集合内的点才有可能匹配并且形成新的点，但又发现，这样是会循环下去的，这些点都会互相形成新的点，直到不可以为止。

所以最后的所有点所在的连通块的点数为：$x$ 坐标的种类数乘 $y$ 坐标的种类数。

但是发现建并查集需要 $O(n^2)$。考虑优化，对于每一个 $x$ 和每一个 $y$ 单独建一个点，对于每一个点对 $(x,y)$ 他们中间建一条边，所有的 $i$ 连向 $x$ 和 $y$。

然后最后答案是所有连通块的贡献减原本的 $n$ 个贡献。

[link](https://atcoder.jp/contests/abc131/submissions/53551318)。

---


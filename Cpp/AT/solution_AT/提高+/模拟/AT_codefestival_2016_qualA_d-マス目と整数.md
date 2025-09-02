# マス目と整数

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2016-quala/tasks/codefestival_2016_qualA_d

縦 $ R $ 行、横 $ C $ 列のマス目があります。 上から $ r $ 行目、左から $ c $ 列目にあるマスを $ (r，c) $ と呼びます。

高橋君は $ N $ 箇所のマスに非負整数を書き込みました。 具体的には、各 $ 1\ <\ =i\ <\ =N $ について、マス $ (r_i，c_i) $ に非負整数 $ a_i $ を書き込みました。 その後、高橋君は居眠りを始めました。

マス目を見つけた青木君は、残りすべてのマスに整数を書き込み、高橋君を驚かせようとしています。 高橋君を驚かせるためには、マス目が次の条件を満たさなければなりません。

- 条件 $ 1 $ : 各マスには非負整数が書き込まれている。
- 条件 $ 2 $ : 縦 $ 2 $ 行、横 $ 2 $ 列の正方形をどこから取り出しても、$ (左上の整数)\ +\ (右下の整数)\ =\ (右上の整数)\ +\ (左下の整数) $ が常に成り立つ。

残りすべてのマスに書き込む整数を工夫することで、マス目が条件を満たすようにできるか判定してください。

## 说明/提示

### 制約

- $ 2\ <\ =R，C\ <\ =10^5 $
- $ 1\ <\ =N\ <\ =10^5 $
- $ 1\ <\ =r_i\ <\ =R $
- $ 1\ <\ =c_i\ <\ =C $
- $ (r_i，c_i) $ はすべて相異なる。
- $ a_i $ は整数である。
- $ 0\ <\ =a_i\ <\ =10^9 $

### Sample Explanation 1

図のように整数を書き込めばよいです。 !\[\](/img/other/code\_festival\_2016\_quala/gbanjthabot/D\_0.png)

### Sample Explanation 2

マス目には次の $ 2 $ 個の正方形があります。 - マス $ (1，1) $，$ (1，2) $，$ (2，1) $，$ (2，2) $ からなる正方形 - マス $ (1，2) $，$ (1，3) $，$ (2，2) $，$ (2，3) $ からなる正方形 左側の正方形において条件 $ 2 $ が成り立つためには、空きマスの整数は $ 40 $ でなければなりません。 すると、右側の正方形において条件 $ 2 $ が成り立たなくなります。 !\[\](/img/other/code\_festival\_2016\_quala/gbanjthabot/D\_1.png)

### Sample Explanation 3

条件 $ 2 $ が成り立つためには、空きマスの整数は $ -10 $ でなければなりません。 すると、条件 $ 1 $ が成り立たなくなります。 !\[\](/img/other/code\_festival\_2016\_quala/gbanjthabot/D\_2.png)

### Sample Explanation 4

例えば、図のように整数を書き込めばよいです。 !\[\](/img/other/code\_festival\_2016\_quala/gbanjthabot/D\_3.png)

### Sample Explanation 5

既にすべてのマスに整数が書き込まれており、条件 $ 2 $ が成り立っていません。 !\[\](/img/other/code\_festival\_2016\_quala/gbanjthabot/D\_4.png)

## 样例 #1

### 输入

```
2 2
3
1 1 0
1 2 10
2 1 20```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 3
5
1 1 0
1 2 10
1 3 20
2 1 30
2 3 40```

### 输出

```
No```

## 样例 #3

### 输入

```
2 2
3
1 1 20
1 2 10
2 1 0```

### 输出

```
No```

## 样例 #4

### 输入

```
3 3
4
1 1 0
1 3 10
3 1 10
3 3 20```

### 输出

```
Yes```

## 样例 #5

### 输入

```
2 2
4
1 1 0
1 2 10
2 1 30
2 2 20```

### 输出

```
No```

# 题解

## 作者：Randyhoads (赞：7)

## AT2033 【マス目と整数 / Grid and Integers】

### 题意

给定一个 $ R \times C $ 的矩阵，有一些位置的数已经被固定了，询问是否有一种

方案使得任意一个$ 2 \times 2 $ 的子矩阵中有对角线之和相等

### 题解


[更好的体验？](https://www.cnblogs.com/wlzs1432/p/14006374.html)


考虑化简题目要求
    
  $a_{i,j} + a_{i+1,j+1} = a_{i+1,j} + a_{i,j+1}$
   
  $a_{i,j} - a_{i,j+1} = a_{i+1,j+1} - a_{i+1,j+1}$

同理有

　$ a_{i,j} - a_{i+1,j} = a_{i,j+1} - a_{i+1,j+1} $

考虑构造 $ a_{i,j} = x_i + y_j $

如果存在可能的x序列和y序列

那么对于每个子矩阵限制条件一定满足

则原问题转化为给定一些形如 $ x_i + y_j = val_k $ 的限制，能否构造出符合条件的序列

显然任意两个 $x_i$ 之间都不影响 同理$y_i$也是

于是考虑连边，所成图一定是若干个个二分图

考虑给每个节点染色使得点权之和等于边权

按照套路，先尝试不考虑非负的限制，随便构造出一组方案

显然随便找一个点赋个权值进行染色即可，显然如果没有限制相互矛盾这样一定可以构造出一种方案

之后考虑调整一波，使得每个点非负，把每个二分图的搜索树画出来，容易发现对于一个点x,如果一个点增加了K，那么为了满足限制条件，所有点都会相应的加K或减K

所以只要在一种构造方案中有最小的 $x_i$ 和 $y_i$相加为非负数就一点有可行方案

代码很简单

```cpp
#include<bits/stdc++.h>

using namespace std;

#define LL long long

inline LL read()
{
	LL f = 1,x = 0;
	char ch;
	do
	{
		ch = getchar();
		if(ch == '-') f = -1;
	}while(ch < '0'||ch > '9');
	do
	{
		x = (x<<3) + (x<<1) + ch - '0';
		ch = getchar();
	}while(ch >= '0' && ch <= '9');
	return f*x;
} 

const int MAXN = 100000 + 10;
 
int R,C;
int N;
bool vis[MAXN<<1];
vector<pair<int,LL> >G[MAXN<<1];
LL col[MAXN<<1];
int rt[MAXN<<1],tot;
vector<int>Sta[MAXN<<1];

inline bool dfs(int x)
{
	vis[x] = 1;
	Sta[tot].push_back(x);
	bool flag = 1;
	for(int i=0;i<G[x].size();i++)
	{
		LL v = G[x][i].first,w = G[x][i].second;
		if(vis[v]){ if(col[v] + col[x] != w) return false;}
		else
		{
			col[v] = w - col[x];
			flag &= dfs(v);
			if(!flag) return false;
		}
	}
	return flag;
}

inline bool check(int x)
{
	LL res1 = 1LL<<62,res2 = 1LL<<62;
	for(int i=0;i<Sta[x].size();i++)
	{
		int v = Sta[x][i];
		if(v > R) res2 = min(res2 , col[v]);
		else res1 = min(res1, col[v]);
	}
	return res1 + res2 >= 0;
}

int main()
{
	R = read(),C = read();
	N = read();
	for(int i=1;i<=N;i++)
	{
		int x = read(),y = read(),w = read();
		G[x].push_back(make_pair(y+R,w));
		G[y+R].push_back(make_pair(x,w));
	}
	bool flag = 1;
	for(int i=1;i<=R+C;i++) if(!vis[i]) rt[++tot] = i,col[i] = 0,flag &= dfs(i);
	if(!flag) { printf("No\n");return 0;}
	for(int i=1;i<=tot;i++) flag &= check(i);
	if(!flag) printf("No\n");
	else printf("Yes\n"); 
 } 
```


---

## 作者：huangrenheluogu (赞：3)

考虑充分条件，对于 $a_{i,j},a_{i,j+1},a_{i+1,j},a_{i+1,j+1}$，则要求的充分条件是 $a_{i,j+1}-a_{i,j}=a_{i+1,j+1}-a_{i+1,j}$。就是两列之间差值相同。

考虑如果有两个位置 $(a,i,w_1),(a,j,w_2)$，则从 $i\to j$ 连 $w_2-w_1$ 的边，表示第 $j$ 列比第 $i$ 列多 $w_2-w_1$。

建图，对于一个连通块，找到一个基准点，算出每个点到这个点的相对大小，然后把所有点跑一遍暴力判断看看会不会弄成负数就好了。

需要思考的问题是对于一个位置，行、列都没有出现过，此时相当于差可以任意选择。所以不同连通块之间是不影响的。

考虑这是模拟赛题，保险起见行、列都跑了一次，其实只跑一个方向就是充要条件了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int, int>
#define fi first
#define se second
#define NO {puts("No");exit(0);}
using namespace std;
const int N = 1e5 + 5;
int n, m, k, x;
struct node{
    int a, b, c;
}a[N];
inline void chkmin(int &x, int y){
    if(x > y) x = y;
}
struct Graph{
    vector<pii> G[N];
    int dist[N], n, vis[N], minn[N], cnt;
    inline void addedge(int x, int y, int z){
        G[x].push_back({y, z});
        G[y].push_back({x, -z});
        // if(x == 12 || y == 12) cerr << x << ' ' << y << ' ' << z << endl;
    }
    inline void dfs(int x){
        vis[x] = cnt;
        chkmin(minn[cnt], dist[x]);
        for(pii e : G[x]){
            if(vis[e.fi]){
                if(dist[e.fi] != dist[x] + e.se) NO;
                continue ;
            }
            dist[e.fi] = dist[x] + e.se;
            dfs(e.fi);
        }
    }
    inline void solve(){
        for(int i = 1; i <= n; i++){
            if(!vis[i]){
                dist[i] = 0;
                cnt++;
                dfs(i);
            }
        }
    }
}L, C;
signed main(){
    // freopen("zibi.in", "r", stdin);
    // freopen("zibi.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &k);
    for(int i = 1; i <= k; i++){
        scanf("%lld%lld%lld", &a[i].a, &a[i].b, &a[i].c);
    }
    sort(a + 1, a + k + 1, [&](node x, node y){
        if(x.a == y.a) return x.b < y.b;
        return x.a < y.a;
    });
    L.n = m, C.n = n;
    for(int i = 1; i <= k; i++){
        if(a[i].a == a[i - 1].a){
            L.addedge(a[i - 1].b, a[i].b, a[i].c - a[i - 1].c);
        }
    }
    L.solve();
    // cerr << endl;
    sort(a + 1, a + k + 1, [&](node x, node y){
        if(x.b == y.b) return x.a < y.a;
        return x.b < y.b;
    });
    for(int i = 1; i <= k; i++){
        if(a[i].b == a[i - 1].b){
            C.addedge(a[i - 1].a, a[i].a, a[i].c - a[i - 1].c);
            if(a[i].a == 5387 || a[i].a == 41257){
                // cerr << "test : " << a[i].a << ' ' << a[i].b << ' ' << a[i].c << endl;
                // cerr << "test2 : " << a[i - 1].a << ' ' << a[i - 1].b << ' ' << a[i - 1].c << endl;
            }
        }
    }
    C.solve();
    // for(int i = 1; i <= m; i++){
    //     if(C.vis[i] == 5219){
    //         cerr << i << ' ' << C.dist[i] << endl;
    //     }
    // }
    // cerr << endl;
    for(int i = 1; i <= k; i++){
        x = L.minn[L.vis[a[i].b]] - L.dist[a[i].b];
        // cerr << a[i].b << ' ' << L.vis[a[i].b] << ' ' << a[i].c << ' ' << x << endl;
        if(x + a[i].c < 0) NO;
        x = C.minn[C.vis[a[i].a]] - C.dist[a[i].a];
        // cerr << a[i].a << ' ' << a[i].b << ' ' << C.vis[a[i].a] << ' ' << a[i].c << ' ' << x << endl;
        if(x + a[i].c < 0) NO;
    }
    puts("Yes");
    return 0;
}
```

---

## 作者：hellhell (赞：3)

### 题意描述

给出一个棋盘共有 $r$ 行 $ c$ 列。

棋盘上已经有一些自然数，其余位置为空格，要把整个棋盘填满。

填数需要遵守一些规则：

- 棋盘内任意一个 $2*2 $ 的方格都需要满足左上角的数字 $+$ 右下角的数字 $=$ 右上角的数字 $+$ 左下角的数字
- 所填数字必须是自然数

问是否能在遵守规则的情况下填满整个棋盘，如果能输出 $Yes$ 否则输出 $no$ 。

### 思路分析

首先我们考虑这样的一个方格。

|  a1  |  a2  |
| :--: | :--: |
|  a3  |  a4  |

根据题意可得 $a_1+a_4=a_2+a_3$ 

移项得到：

$a_1-a_2=a_3-a_4$

$a_1-a_3=a_2-a_4$

发现不同行相同列的差相同。

不同列相同行的差相同。

根据这个性质可以判断棋盘内提前给出的数能否使得整个棋盘内填满以后是合法的。

如果不合法输出 $No$ 

否则要看剩余要填的数能否使棋盘填满后合法。

可以暴力记录差，但是这样会超时，可以用带权并查集进行维护。

考虑行相同如何进行维护。

将已有棋子按照行的编号升序排序，对于行相同列不同的两个点，设列的编号为 $y_1$ ,$y_2$ 

如果 $y_1$ ,$y_2$不在同一个并查集，将两个点合并到同一并查集，同时将 $y_1$ 的父亲设为 $y_2$ 并将 $y_1$ 与父亲的差设置为两个点的权值差。

 如果在同一并查集里，说明两列已经有固定的权值差了，判断两点权值差是否等于固定差，不等于就不符合条件。

维护列相同与行同理。

如果已经给出的数字都满足条件就要看空白格子填满后能否满足条件。

因为不同行相同列的差相同，不同列相同行的差相同。所以每个格子有唯一确定的值。

找到最小的唯一确定的值 $（$每个并查集都有一个$）$ 看是否小于 0 。

枚举行父亲或者列父亲，因为每个位置有唯一确定的值，所以枚举一个即可。

这里我们枚举行父亲。

对于单独的一行和这一行的行父亲，一定存在一列有一个固定的差，通过这个固定的差可以找到父亲的最小值。

对于这个行父亲的其他的儿子，跟行父亲一定存在固定的差，找到这个最小的固定的差，就求出了最小唯一确定的值。

### 代码实现

首先考虑如何维护已有的数字

```c++
int fa1[100005];//记录行父亲
int dif1[100005];//记录列的固定差

int find1(int x){
    if(x==fa1[x])
        return x;
    tmp=find1(fa1[x]);
    dif1[x]+=dif1[fa1[x]];
    return fa1[x]=tmp;//路径压缩优化(都0202年了还有人写并查集不加路径压缩吗)
}

bool check1(int a,int b){//判断是否合法
    int fa_a=find1(p[a].y);
    int fa_b=find1(p[b].y);
    if(fa_a==fa_b){
        if(p[a].val-dif1[p[a].y]==p[b].val-dif1[p[b].y])
            return false;
        else
            return true;
    }
    else{
        int vala=p[a].val-dif1[p[a].y];
        int valb=p[b].val-dif1[p[b].y];
        fa1[fa_a]=fa_b;
        dif1[fa_a]=vala-valb;
        return false;
    }
}

int fa2[100005];//记录列父亲
int dif2[100005];//记录行的固定差

int find2(int x){
    if(x==fa2[x])
        return x;
    tmp=find2(fa2[x]);
    dif2[x]+=dif2[fa2[x]];
    return fa2[x]=tmp;
}

bool check2(int a,int b){
    int fa_a=find2(p[a].x);
    int fa_b=find2(p[b].x);
    if(fa_a==fa_b){
        if(p[a].val-dif2[p[a].x]==p[b].val-dif2[p[b].x])
            return false;
        else
            return true;
    }
    else{
        int vala=p[a].val-dif2[p[a].x];
        int valb=p[b].val-dif2[p[b].x];
        fa2[fa_a]=fa_b;
        dif2[fa_a]=vala-valb;
        return false;
    }
}
```



然后考虑如何求最小的固定差

```c++
    for(int i=1;i<=n;i++){
        int fa=find1(p[i].y);
        min1[fa]=min(min1[fa],p[i].val-dif1[p[i].y]);
    }
    for(int i=1;i<=c;i++){
        int fa=find1(i);
        min2[fa]=min(min2[fa],dif1[i]);
    }//找父亲的最小值
    for(int i=1;i<=c;i++){
        int fa=find1(i);
        if(fa==i)
            if(min1[i]+min2[i]<0){
                flag=true;
            }
    }//找唯一确定的最小值，判断是否合法
```

最后是完整代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;

int r,c;
int n;
bool flag;

struct node{
    int x;
    int y;
    int val;
}p[100005];

int min1[100005];
int min2[100005];

int fa1[100005];
int dif1[100005];

int tmp;

bool cmp1(node a,node b){
    return a.x<b.x;
}

bool cmp2(node a,node b){
    return a.y<b.y;
}

int find1(int x){
    if(x==fa1[x])
        return x;
    tmp=find1(fa1[x]);
    dif1[x]+=dif1[fa1[x]];
    return fa1[x]=tmp;
}

bool check1(int a,int b){
    int fa_a=find1(p[a].y);
    int fa_b=find1(p[b].y);
    if(fa_a==fa_b){
        if(p[a].val-dif1[p[a].y]==p[b].val-dif1[p[b].y])
            return false;
        else
            return true;
    }
    else{
        int vala=p[a].val-dif1[p[a].y];
        int valb=p[b].val-dif1[p[b].y];
        fa1[fa_a]=fa_b;
        dif1[fa_a]=vala-valb;
        return false;
    }
}

int fa2[100005];
int dif2[100005];

int find2(int x){
    if(x==fa2[x])
        return x;
    tmp=find2(fa2[x]);
    dif2[x]+=dif2[fa2[x]];
    return fa2[x]=tmp;
}

bool check2(int a,int b){
    int fa_a=find2(p[a].x);
    int fa_b=find2(p[b].x);
    if(fa_a==fa_b){
        if(p[a].val-dif2[p[a].x]==p[b].val-dif2[p[b].x])
            return false;
        else
            return true;
    }
    else{
        int vala=p[a].val-dif2[p[a].x];
        int valb=p[b].val-dif2[p[b].x];
        fa2[fa_a]=fa_b;
        dif2[fa_a]=vala-valb;
        return false;
    }
}

void init(){
    for(int i=1;i<=r;i++){
        fa2[i]=i;
        dif2[i]=0;
    }
    for(int i=1;i<=c;i++){
        fa1[i]=i;
        dif1[i]=0;
    }
}

signed main(){
    cin>>r>>c;
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        scanf("%lld%lld%lld",&p[i].x,&p[i].y,&p[i].val);
        if(p[i].val<0)
            flag=true;
    }
    memset(min1,0x3f,sizeof(min1));
    memset(min2,0x3f,sizeof(min2));
    if(flag){
        cout<<"No"<<endl;
        return 0;
    }
    sort(p+1,p+1+n,cmp1);
    for(int i=1;i<n;i++){
        if(p[i].x==p[i+1].x){
            if(check1(i,i+1)){
                flag=true;
            }
        }
    }
    if(flag){
        cout<<"No"<<endl;
        return 0;
    }
    sort(p+1,p+1+n,cmp2);
    for(int i=1;i<n;i++){
        if(p[i].y==p[i+1].y){
            if(check2(i,i+1)){
                flag=true;
            }
        }
    }
    if(flag){
        cout<<"No"<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        int fa=find1(p[i].y);
        min1[fa]=min(min1[fa],p[i].val-dif1[p[i].y]);
    }
    for(int i=1;i<=c;i++){
        int fa=find1(i);
        min2[fa]=min(min2[fa],dif1[i]);
    }
    for(int i=1;i<=c;i++){
        int fa=find1(i);
        if(fa==i)
            if(min1[fa]+min2[fa]<0){
                flag=true;
            }
    }
    if(flag){
        cout<<"No"<<endl;
        return 0;
    }
    cout<<"Yes"<<endl;
    return 0;
}
```

### 注意

要开 $long\;long$ 

不开 $long\;long$ 见祖宗。

然后今年 $CSP-S2$ 会让你知道就算你开了 $ull$ 也会见祖宗。

本文转载自：https://blog.csdn.net/bluelanzhan/article/details/83625424
有删改



---

## 作者：Take_A_Single_6 (赞：2)

似乎挺经典的，但是黑降绿就不好评，适应选手水平增长吧。。。  
显然对角和等式就是知三求一，再推一下发现可以扩展到任意一个矩形的四角，即：  
$$a_{x_1,y_1}+a_{x_2,y_2}=a_{x_1,y_2}+a_{x_2,y_1}$$  
根据经典套路建立 $r+c$ 个点表示每行和每列，坐标转化为连边，染色或者并查集。二分图染色其实可以理解为所有边权为 $1$，点权为 $0/1$，使一条边连接的点权和等于边权的一种赋值方法。那么这里我们可以让边权为 $a_{i,j}$，跑一遍染色。  
再考虑非负的限制，显然一个二分图表达的坐标权最小的一定是行最小值和列最小值相加，只要这个值非负就可以了。  
复杂度 $O(R+C)$，随便过。  
代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 200005
#define mod 1000002015
#define fir first
#define sec second
#define pr pair<int,int>
#define pb push_back
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX%10+'0');
}
int R,C,n,cl[maxn],mn1,mn2;
vector<pr>e[maxn];
bool vis[maxn];
bool dfs(int u)
{
	vis[u]=1;
	if(u>R)mn1=min(mn1,cl[u]);//列最小
	else mn2=min(mn2,cl[u]);//行最小
	for(pr v:e[u])
	{
		if(vis[v.fir])
		{
			if(cl[u]+cl[v.fir]!=v.sec)return 0;
		}
		else
		{
			cl[v.fir]=v.sec-cl[u];//染色
			if(!dfs(v.fir))return 0;
		}
	}
	return 1;
}
signed main()
{
	int x,y,z;
	R=read(),C=read(),n=read();
	for(int i=1;i<=n;i++)
		x=read(),y=read()+R,z=read(),e[x].pb(mk(y,z)),e[y].pb(mk(x,z));//注意编号
	for(int i=1;i<=R+C;i++)
	{
		if(!vis[i])
		{
			mn1=mn2=inf;
			if(!dfs(i)||mn1+mn2<0)return puts("No"),0;
		}
	}
	puts("Yes");
	return 0;
}
```

---

## 作者：XuYueming (赞：0)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/AT_codefestival_2016_qualA_d)；[AtCoder](https://atcoder.jp/contests/code-festival-2016-quala/tasks/codefestival_2016_qualA_d)。

[更好的体验](https://www.cnblogs.com/XuYueming/p/18548183)。

## 题意简述

给你一个 $n \times m$ 的矩形 $a$，其中已经有 $q$ 个位置填上了数，你需要为剩下的位置分别填上一个**非负整数**，使得最终任意一个 $2 \times 2$ 的子矩形内，左上角的数加右下角的数等于右上角的数加左下角的数，即 $\forall i\in[1,n), j\in[1,m),\ a_{i,j}+a_{i+1,j+1}=a_{i,j+1}+a_{i+1,j}$。

$n, m, q \leq 10^5$。

## 题目分析

第一步肯定是找性质，我们从 $n = 2$ 开始观察。发现合法的方案满足 $\forall j\in[1,m],\ a_{1,j}-a_{2,j}=k$，其中 $k$ 为一常数。发现这是因为由 $a_{i,j}+a_{i+1,j+1}=a_{i,j+1}+a_{i+1,j}$ 得到 $a_{i,j}-a_{i+1,j}=a_{i,j+1}-a_{i+1,j+1}$，这 $m-1$ 个等式可以等起来，也就得到 $a_{1,j}-a_{2,j}$ 为一定值。

对其推广，对于 $n \times m$ 的矩形，对于所有 $i\in[1,n)$，满足 $(i, i+1)$ 两行对应位置值之差为一定值，说明合法。（对于列有相同结论，但是任意一种都是合法的充要条件，二者可以互推，所以这里不妨仅考虑行。）

我们发现，还可以进一步拓展结论：由于 $(i,i+1), (i+1,i+2)$ 满足结论，那么 $(1, i+2)$ 也满足结论，进一步，也就是对于任意两行 $(i, j)$，它们对应位置值之差是定值。

我们想到做前缀和后，变为差分约束搞，但是显然不太对。我们想到可以使用带权并查集来维护，这种套路在带权并查集是常见的，不做赘述。可以对于每一列，依次把相邻的两个有值的位置所在的行进行合并（这里相邻指的是中间没有其他有值的位置）。

除了合并的时候无解，我们注意到题目中还有非负整数的限制。我们对于每一列的每一个有值的位置，可以通过并查集中的边，推断出和它处在同一个联通块内，所有行对应位置的值，我们仅需要保证这些能被唯一确定的点值均非负即可，剩下的位置是不确定的。那么把每个连通块路径压缩成一个菊花后，我们只需要维护并查集联通块内，到父亲边权的最值即可，这个可以预处理。具体判断逻辑见代码。

于是本题做完了，时间复杂度带一个并查集的小常数。如果使用搜索可以避免，但是会进入复杂度陷阱，拥有一个大常数。可以对于每一列新建一个虚拟点，这样可以减少码量和常数，建议在理解基础算法后再尝试理解，两种代码都给出，供读者学习。

## 代码

完整代码、虚拟点实现和最优解代码见[我的博客](https://www.cnblogs.com/XuYueming/p/18548183)。

```cpp
scanf("%d%d%d", &n, &m, &q);
for (int x, y, v; q--; ) {
    scanf("%d%d%d", &x, &y, &v);
    vec[y].emplace_back(x, v);
}
for (int i = 1; i <= n; ++i) fa[i] = i, mi[i] = 0x3f3f3f3f3f3f3f3f;
for (int i = 1; i <= m; ++i) {
    sort(vec[i].begin(), vec[i].end());
    for (int lst = 0, lv = 0; auto [x, v] : vec[i]) {
        if (lst) merge(x, lst, v - lv);
        lst = x, lv = v;
    }
}
for (int i = 1; i <= n; ++i) get(i), mi[fa[i]] = min(mi[fa[i]], d[i]);
for (int i = 1; i <= m; ++i) {
    for (auto [x, v] : vec[i]) {
        if (-d[x] + v + mi[fa[x]] < 0) return puts(BAD), 0;
    }
}
puts(OK);
```

---

## 作者：Erica_N_Contina (赞：0)

妙极了。

一开始考虑对于每一个 $2\times2$ 的方格，如果有 $≥2$ 个数（下文中的“点”和“数”是同一个概念）已经给定，那么就可以得到一组约束，然后用差分约束跑。

然后发现一组 hack，如下。

```C++
0 - 1
- - -
2 - 4
```


于是重新考虑约束。

对于一个矩阵：

```C++
a b
c d
```


我们发现满足 $a+d=c+b$，进行变换得 $a-c=b-d$。

发现第 $i$ 行和第 $i+1$ 行的差值是固定的。对于列也如此。并且这种差值有传递性：对于所有 $i,j$，第 $i$ 行和第 $j$ 行的差值是固定的，列也是如此。

再看回那个 hack，发现可以被判掉了。

于是从同一行的已知点、同一列的已知点中可以得到若干约束。我们把这些约束看成边，边权为差值。使用 dfs 检查每个联通块中是否存在矛盾（将其中一个赋值为 $0$，然后取不断更新其它点，直到出现矛盾或者联通块内所有点都被赋值）。

此时就已经解决有无解的问题了，但是还有一个条件：被填的数应当 $≥0$。还是根据上面的联通块的结果，记联通块内点i被赋值为 $w_i$，最小的 $w$ 记为 $mn$，那么对于点 $i$，就说明存在一个点的值为 $a_i-(w_i-mn)$，其中 $a_i$ 为 $i$ 的原始权值。

于是要使得 $a_i-(w_i-mn)≥0$，就应当对于每一个 $i$ 满足 $a_i≥w_i-mn$，反之无合法解。

```C++

// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Challenger: Erica N
// ----
// 
#include<bits/stdc++.h>

using namespace std;
#define rd read()
#define ull unsigned long long
#define int long long 
#define pb push_back
#define itn int
#define ps second 
#define pf first


#define rd read()
int read(){
  int xx = 0, ff = 1;char ch = getchar();
  while (ch < '0' || ch > '9'){
    if (ch == '-')ff = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')xx = xx * 10 + (ch - '0'), ch = getchar();
  return xx * ff;
}
const int N=2e5+5;
const ull P=137;
const int INF=1e18+7;
/*

策略


*/	


vector<int> tx[N],ty[N];
int x[N],y[N];
map<int,map<int,int>> a;

struct Node{
	int v,w;
};
vector<Node> e[N],g[N];
void add(itn a,int b,int v){
	// cdbg("e",a,b,v);
	e[a].pb({b,v});
	e[b].pb({a,-v});
}


void addg(int a,int b,int c){
	// cdbg("g",a,b,c);
	g[a].pb({b,c});
	g[b].pb({a,-c});
}

bitset<N> vis;

int w[N];
int stk[N],top;
int mn=0;

bool dfs(int x){
	mn=min(mn,w[x]);
	stk[++top]=x;
	int f=0;
	for(auto v:e[x]){
		if(vis[v.v]){
			if(w[v.v]!=w[x]-v.w)f=1;
		}else{
			w[v.v]=w[x]-v.w;
			vis[v.v]=1;
			f|=dfs(v.v);
		}
	}
	return f;
}




bool dfsg(int x){
	int f=0;
	for(auto v:g[x]){
		if(vis[v.v]){
			if(w[v.v]!=w[x]-v.w)f=1;
		}else{
			w[v.v]=w[x]-v.w;
			vis[v.v]=1;
			f|=dfsg(v.v);
		}
	}
	return f;
}


int limx[N],limy[N];
bitset<N> havx,havy;

signed main(){
	
	// freopen("zibi.in","r",stdin);
	// freopen("zibi.out","w",stdout);
	int n=rd,m=rd;
	int K=rd;
	for(int i=1;i<=K;i++){
		int x=rd,y=rd;
		tx[x].pb(y);
		ty[y].pb(x);
		a[x][y]=rd;
		
	}
	
	for(int x=1;x<=n;x++){
		sort(tx[x].begin(),tx[x].end());
		if(tx[x].size()<2)continue;
		for(int j=1;j<tx[x].size();j++){
			//tx[x][j]-tx[x][j-1]=a[x][y(j)]-a[x][y(j-1)]
			int y=tx[x][j-1],yy=tx[x][j];
			int v=a[x][y]-a[x][yy];
			addg(y,yy,v);
		}
	}


	for(int y=1;y<=m;y++){
		sort(ty[y].begin(),ty[y].end());
		// cdbg(y,ty[y].size());
		if(ty[y].size()<2)continue;
		for(int j=1;j<ty[y].size();j++){
			int x=ty[y][j-1],xx=ty[y][j];
			int v=a[x][y]-a[xx][y];
			add(x,xx,v);
		}
	}

	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		mn=0;
		top=0;
		vis[i]=1;
		if(dfs(i)){
			puts("No");
			exit(0);
		}
		for(int i=1;i<=top;i++){
			limx[stk[i]]=w[stk[i]]-mn;
			havx[stk[i]]=1;
		}
	}
	vis.reset();

	for(int i=1;i<=m;i++){
		if(vis[i])continue;
		mn=0,top=0;
		vis[i]=1;
		if(dfsg(i)){
			puts("No");
			exit(0);
		}
		for(int i=1;i<=top;i++){
			limy[stk[i]]=w[stk[i]]-mn;
			havy[stk[i]]=1;
		}
		
	}



	for(int i=1;i<=n;i++){
		for(auto j:tx[i]){
			if((a[i][j]<limx[i]&&havx[i])||(a[i][j]<limy[j]&&havy[j])){
				// cdbg(a[i][j],limx[i],limy[j],havx[j]);
				puts("No");
				exit(0);
			}
		}
	}


	puts("Yes");


	
}
```

---


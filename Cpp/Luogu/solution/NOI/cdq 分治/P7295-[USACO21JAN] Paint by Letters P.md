# [USACO21JAN] Paint by Letters P

## 题目描述

Bessie 最近收到了一套颜料。画布可以用一个 $N×M$ 的矩形方阵表示，其中行从上往下编号为 $1…N$，列从左往右编号为 $1…M$（$1≤N,M≤1000$）。被涂色的方格的颜色可以用一个 `A` 到 `Z` 的大写字母表示。初始时，所有方格均未被涂色，每个方格至多只能被涂色一次。

Bessie 指定了每个方格她所希望的颜色。她一笔可以将一些组成连通分量的方格涂上颜色，也就是说这些方格之间可以通过相邻方格互相到达。如果两个方格有公共边则认为它们是相邻的。

例如，$3×3$ 的画布

```
AAB
BBA
BBB
```

可以用如下四笔完成涂色：

```
...    ..B    AAB    AAB    AAB
... -> ... -> ... -> BB. -> BBA
...    ...    ...    BBB    BBB
```

使用少于四笔不可能得到最终结果。

作为一名先锋派艺术家，Bessie 只会对这个画布中的一个子矩形进行涂色。现在，她正在考虑 $Q$
个候选子矩形（$1≤Q≤1000$），每一候选给定四个整数 $x_1$、$y_1$、$x_2$ 和 $y_2$，表示由第 $x_1$ 行到第 $x_2$ 行及第 $y_1$ 列到第 $y_2$ 列的所有方格组成的子矩形。

对于每个候选子矩形，将所有子矩形内的方格都涂上所希望的颜色，并且子矩形外的方格均不涂色，最少需要涂多少笔？注意在这个过程中 Bessie 并没有真正进行任何的涂色，所以对于每个候选的回答是独立的。

注意：本题每个测试点的时间限制为默认限制的 1.5 倍，且内存限制为默认限制的 2 倍，为 512MB。 

## 说明/提示

#### 样例 1 解释

第一个候选由整个画布组成，可以用六笔完成涂色。

第二个候选的子矩形所希望的颜色为

```
ABBA
```

可以用三笔完成涂色。注意，尽管在考虑整个画布时方格 $(3,5)$ 和 $(3,8)$ 可以用一笔涂上颜色 $A$，但如果仅考虑子矩形内的方格则并非如此。 

#### 测试点性质：

 - 测试点 1-2 满足 $N,M≤50$。
 - 测试点 3-5 中，画布不包含由单一颜色所组成的环。也就是说，不存在由不同方格所组成的序列 $c_1,c_2,c_3,…,c_k$ 满足以下条件：
   - $k>2$
   - 所有的 $c_1,…,c_k$ 颜色相同。
   - 对于所有的 $1≤i<k$，$c_i$ 与 $c_i+1$ 相邻。
   - $c_k$ 与 $c_1$ 相邻。
   注意，问题描述中的 3×3 画布包含单一颜色所组成的环（左下角的四个 B）。
 - 测试点 6-8 中，每个由相同期望颜色的方格组成的连通分量均能够被一个四边平行于坐标轴的两行两列的正方形所包含。问题描述中的 $3×3$ 画布不符合这一性质（由五个 B 组成的连通分量不能被一个两行两列的正方形包含）。
 - 测试点 9-11 中，每个由相同期望颜色的方格组成的连通分量均能够被一个四边平行于坐标轴的三行三列的正方形所包含。问题描述中的 $3×3$ 画布符合这一性质。
 - 测试点 12-20 没有额外限制。

供题：Andi Qu 

## 样例 #1

### 输入

```
4 8 9
ABBAAAAA
ABAAAABA
CAADABBA
AAAAAAAA
1 1 4 8
3 5 3 8
1 3 2 4
1 4 2 5
1 1 3 3
4 4 4 4
2 6 4 8
3 5 4 6
1 6 3 8```

### 输出

```
6
3
2
1
4
1
3
2
2```

# 题解

## 作者：Endt (赞：9)

# Paint by Letters P-题解

### 题意

一个 $n\times m$ 的矩形方阵，每一方格有一种目标颜色，颜色相同相邻的方格可以一起被染色，$q$ 次询问，求出给且只给某一子矩形方阵染色需要染几次。

### 前置知识

欧拉平面图定理：$K=|V|-|E|+R-1$，$K$ 为连通块个数，$V$ 为点集，$E$ 为边集，$R$ 为区域数。

### 实现步骤

将可以一起染的连边，题目就是求联通块个数 $K$。

点和边的数量很好求，二维前缀和就能办到，瓶颈在求区域数 $R$。

我们先 $bfs$ 找到整个图的独立区域，标记好每一个空格所在的区域编号，然后给每一个区域一个标记点（当然在区域内），如果现在的子图包含了这个标记点，我们就先暂时认为这个区域是存在于图中的。如果事实上它不存在，那唯一的情况是它的边缘在这个子图之外，导致这个区域成为了最外圈的无限区域的一部分，我们可以遍历矩形的边缘，查找部分在边缘内而部分在边缘外的区域，接着检验这个区域的标记点是否在矩形内，若是，将答案减一即可。

噫！好！我们过了！

### 代码

```cpp
#include<bits/stdc++.h>

#define  Int  long long int
#define  Pub  public

using std::min;using std::max;

int n,m,q;
char p[1005][1005];
std::pair<int,int> s[1005][1005][5];

bool vis[1005][1005],siv[2000005];
int v[1005][1005],e1[1005][1005],e2[1005][1005],r[1005][1005];
int rid[1005][1005],cnt;
std::pair<int,int> t[1000005];
void dfs(int x,int y){
    if(x<0||x>n||y<0||y>m)return;
    if(vis[x][y])return;
    else vis[x][y]=1;
    if(s[x][y][3]==std::pair<int,int>{0,0})rid[x][y-1]=rid[x][y],dfs(x,y-1);
    if(s[x][y][4]==std::pair<int,int>{0,0})rid[x-1][y]=rid[x][y],dfs(x-1,y);
    if(s[x+1][y+1][1]==std::pair<int,int>{0,0})rid[x][y+1]=rid[x][y],dfs(x,y+1);
    if(s[x+1][y+1][2]==std::pair<int,int>{0,0})rid[x+1][y]=rid[x][y],dfs(x+1,y);
}

int main(){
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;++i)
        for(int j=(getchar(),1);j<=m;++j)
            p[i][j]=getchar();
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            int vvv=1,ee1=0,ee2=0;
            if(p[i][j]==p[i-1][j])s[i][j][1]={i-1,j},++ee2;
            if(p[i][j]==p[i][j-1])s[i][j][2]={i,j-1},++ee1;
            if(p[i][j]==p[i+1][j])s[i][j][3]={i+1,j};
            if(p[i][j]==p[i][j+1])s[i][j][4]={i,j+1};
            v[i][j]=v[i-1][j]+v[i][j-1]-v[i-1][j-1]+vvv;
            e1[i][j]=e1[i-1][j]+e1[i][j-1]-e1[i-1][j-1]+ee1;
            e2[i][j]=e2[i-1][j]+e2[i][j-1]-e2[i-1][j-1]+ee2;         
        }
    }
    for(int i=0;i<=n;++i){
        for(int j=0;j<=m;++j){
            if(i==0&&j==0)r[i][j]=0;
            else if(i==0||j==0)r[i][j]=1;
            else r[i][j]+=r[i-1][j]+r[i][j-1]-r[i-1][j-1];
            if(vis[i][j])continue;
            else{
                ++cnt;
                rid[i][j]=cnt;
                t[cnt]=std::pair<int,int>{i,j};
                ++r[i][j];
                dfs(i,j);
            }
        }
    }
    
    while(~--q){
        memset(siv,0,sizeof(siv));
        int x_,y_,_x,_y;
        scanf("%d%d%d%d",&x_,&y_,&_x,&_y);
        int ans=0;
        ans+=v[_x][_y]+v[x_-1][y_-1]-v[x_-1][_y]-v[_x][y_-1];
        ans-=e1[_x][_y]+e1[x_-1][y_]-e1[x_-1][_y]-e1[_x][y_];
        ans-=e2[_x][_y]+e2[x_][y_-1]-e2[x_][_y]-e2[_x][y_-1];
        ans+=r[_x-1][_y-1]+r[x_-1][y_-1]-r[x_-1][_y-1]-r[_x-1][y_-1];
        for(int i=x_;i<_x;++i)
            if(s[i][y_][3]==std::pair<int,int>{0,0})
                if(t[rid[i][y_]].first>=x_&&t[rid[i][y_]].first<_x&&t[rid[i][y_]].second>=y_&&t[rid[i][y_]].second<_y&&!siv[rid[i][y_]])
                    siv[rid[i][y_]]=1,--ans;
        for(int i=y_;i<_y;++i)
            if(s[x_][i][4]==std::pair<int,int>{0,0})
                if(t[rid[x_][i]].first>=x_&&t[rid[x_][i]].first<_x&&t[rid[x_][i]].second>=y_&&t[rid[x_][i]].second<_y&&!siv[rid[x_][i]])
                    siv[rid[x_][i]]=1,--ans;
        for(int i=x_;i<_x;++i)
            if(s[i][_y][3]==std::pair<int,int>{0,0})
                if(t[rid[i][_y]].first>=x_&&t[rid[i][_y]].first<_x&&t[rid[i][_y]].second>=y_&&t[rid[i][_y]].second<_y&&!siv[rid[i][_y]])
                    siv[rid[i][_y]]=1,--ans;
        for(int i=y_;i<_y;++i)
            if(s[_x][i][4]==std::pair<int,int>{0,0})
                if(t[rid[_x][i]].first>=x_&&t[rid[_x][i]].first<_x&&t[rid[_x][i]].second>=y_&&t[rid[_x][i]].second<_y&&!siv[rid[_x][i]])
                    siv[rid[_x][i]]=1,--ans;
        printf("%d\n",ans);
    }
    
    return 0;
}
```

---

## 作者：六楼溜刘 (赞：5)

# P7295 [USACO21JAN] Paint by Letters P

**cdq 分治**做法。

约定 $a_{i,j}$ 表示给定矩阵的第 $i$ 行第 $j$ 列。

容易发现假如我们给四连通的同色块连边，那么容易发现每一笔可以涂完一整个连通块。而方格图建边后必然是平面图。故我们要求的其实就是**矩阵内平面图连通块的数量**。

根据平面图欧拉公式，我们有 $V+F-E-1=A$，其中 $A$ 为平面图连通块数量，$V$ 为点的数量，$F$ 为面的数量（包含外面无限大的平面），$E$ 为边的数量。其实你如果不算外面的平面那么有 $V+F-E=A$。

---

此处简要证明一下平面图欧拉公式。

考虑数学归纳法，容易发现，当 $V=1,E=0$，显然成立。

然后对于任意情况，假设所有 $V'\le V,E'<E$ 的情况都成立。

考虑删掉一条边，那么就有两种情况：

1. 删掉的这条边是桥边（即删掉后变成两个连通块）

那么容易发现它变成了两个更小的情况，面数不变（桥边两侧都是外围无限大的平面），点数不变，边数减一。$V+F-E$ 的值 $+1$，而连通块数量 $+1$，符合条件。

2. 删掉的这条边不是桥边

那么连通块数量不改变。但是由于它不是桥边，那么它两侧的两个面原先必定不连通（因为有至少一边是封闭的）。删掉这条边后变为连通，且变成了一个规模更小的情况。相比新情况，$V+F-E$ 的值不变（$E'=E-1,F'=F-1$），连通块数量不改变，符合条件。

另外容易发现某个连通块内部的“面”里面有另一个连通块其实和两个连通块相互独立是等价的。

---

那么考虑如何维护 $V+F-E$ 的值。

首先 $V$ 最简单，就是矩形大小。

然后是 $E$，容易想到分成纵向边和横向边两种情况求二维前缀和。

具体来说，令 $s_{x,y}=\sum_{i=1}^x\sum_{j=1}^y[a_{i,j}=a_{i-1,j}],s_{x,y}'=\sum_{i=1}^x\sum_{j=1}^y[a_{i,j}=a_{i,j-1}]$。那么容易发现矩形 $(x_1,y_1,x_2,y_2)$ 中的横向边数就是：

$$s_{x_2,y_2}-s_{x_1,y_2}-s_{x_2,y_1-1}+s_{x_1,y_1-1}$$

注意一边是 $x_1$，另一边是 $y_1-1$，因为在 $s$ 的定义中一条横向边是挂在右边的点上的。

同理，纵向边数就是：

$$s_{x_2,y_2}'-s_{x_1-1,y_2}'-s_{x_2,y_1}'+s_{x_1-1,y_1}'$$

加起来即可。

---

接下来是最难搞的 $F$。

$F$ 能分两种情况，一种是 $2\times 2$ 的小方格。

![](https://cdn.luogu.com.cn/upload/image_hosting/r2i756xk.png)

比如上图中间蓝色的那一坨。这种中间**不包含其它点**的面可以直接前缀和维护，挂在右下角上即可。

然后是另一种中间围了其它点的空腔。

![](https://cdn.luogu.com.cn/upload/image_hosting/gjjyd8b7.png)

（其实这就是样例）比如右边红色围着蓝色的就是一个例子。

这个怎么办呢？容易发现对于这样的一个连通块，显然存在一个矩形 $(x_1',y_1',x_2',y_2')$ 恰好包含它。而这个面产生贡献当且仅当询问的矩形恰好完全包含这个矩形，即若有一个询问 $(x_1,y_1,x_2,y_2)$ 满足：$x_1<x_1',y_1<y_1',x_2>x_2',y_2>y_2'$，那么这个面会对对应询问产生贡献。

那么容易发现这是一个四维偏序，考虑 cdq 套 cdq，内层排序后用树状数组解决。

另外，我们还要考虑一下如何找到空腔。这个其实很简单，先枚举是这个空腔是哪个颜色的空腔，比如是 $c$ 颜色。那么就可以把所有 $c$ 颜色视作障碍物，其余视作平地跑 dfs 染色，途中维护四个方向的最值即可。

注意这一种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/ddyfajp1.png)

容易发现，中间的蓝色块虽然不是四连通的，但是也是同一个空穴。所以跑 dfs 染色的时候应该将八连通视作相邻，就不会出问题了。

另外，若某个空腔的边界取到了矩阵的边界，它显然是不可能产生贡献的。

---

此处简要阐述 cdq 套 cdq 怎么实现。

容易发现 cdq 的每一层是把所有点简化成了一个“左边的修改”对“右边的询问”产生贡献的形式。

那么对于第一层分治的每个区间，把左边的所有修改和右边的所有询问取出来，排序后放到新的序列上，然后对新的序列做第二层 cdq 即可。

注意这里有个问题，就是对于第一层（假设第一层是 $x_1$），若存在一修改和一询问的 $x_1$ 相等，那么应该将询问排到前面。因为若连续的 $x_1$ 横跨了第一层分治的某个区间，那么它们都会被取出来。就可能会有 $x_1=x_1'$ 的一对修改和查询产生贡献，而这是我们需要避免的。但只要把询问排到前面就能避免这种情况了，因为若询问被取出了那么对应修改必定不被取出，反之亦然。

---

然后我们就优雅地解决了这个问题，复杂度贼神奇，是 $O(q+nm|\Sigma|+(nm+q)\log^3(nm+q))$，其中第一个 $q$ 是前缀和维护可维护的信息，第二个 $nm|\Sigma|$ 中 $\Sigma$ 表示字符集，这个是寻找空腔的复杂度，第三个是求偏序的复杂度，看起来过不了，但是这个上界取的太松了，空腔数量是卡不到它的。

~~虽然但是，我目前暂居洛谷倒数第二劣解，因为这个解法确实做复杂了。~~

## code

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define forup(i,s,e) for(int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(int i=(s);i>=(e);i--)
#define y1 y114514
using namespace std;
#define gc getchar()
inline int read(){
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=1005,inf=0x3f3f3f3f;
int n,m,q;
int a[N][N];
char str[N];
int e1[N][N],e2[N][N],f[N][N];
struct query{
	int x1,y1,x2,y2,pos;
}qu[N*N+N];//存储询问矩阵与空腔矩阵，pos 为 0 表示是空腔
int cntq;
int ans[N];
int calc(int x1,int y1,int x2,int y2){//计算能前缀和维护的部分
	int _e1=e1[x2][y2]-e1[x1-1][y2]-e1[x2][y1]+e1[x1-1][y1],
		_e2=e2[x2][y2]-e2[x1][y2]-e2[x2][y1-1]+e2[x1][y1-1],
		_f=f[x2][y2]-f[x1][y2]-f[x2][y1]+f[x1][y1],
		_v=(x2-x1+1)*(y2-y1+1);
	return _v+_f-_e1-_e2;
}
int nxt[8][2]={//注意八连通
	{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}
};
int vis[N][N],u,d,l,r;
void dfs(int x,int y,int co){//dfs 涂色，维护四个方向的最值
	vis[x][y]=1;
	u=max(u,y);d=min(d,y);
	r=max(r,x);l=min(l,x);
	forup(i,0,7){
		int nx=x+nxt[i][0],ny=y+nxt[i][1];
		if(vis[nx][ny]||a[nx][ny]==co||nx<1||nx>n||ny<1||ny>m) continue;
		dfs(nx,ny,co);
	}
}
query seq[N*N+N];
int cnts;
struct BIT{
	int c[N];
	void upd(int x,int k){for(;x<=m;x+=x&-x)c[x]+=k;}
	int sum(int x){int res=0;for(;x>0;x-=x&-x)res+=c[x];return res;}
}mt;
void cdq2(int l,int r){
	if(l>=r) return;
	int mid=(l+r)>>1;
	cdq2(l,mid);cdq2(mid+1,r);
	int ll=l;
	forup(i,mid+1,r){
		if(seq[i].pos!=0){
			while(ll<=mid&&seq[ll].x2<seq[i].x2){
				if(seq[ll].pos==0){
					mt.upd(seq[ll].y2,1);
				}
				++ll;
			}
			ans[seq[i].pos]+=mt.sum(seq[i].y2-1);
		}
	}
	forup(i,l,ll-1){//记得清空树状数组
		if(seq[i].pos==0){
			mt.upd(seq[i].y2,-1);
		}
	}
	inplace_merge(seq+l,seq+mid+1,seq+r+1,[&](query a,query b){
		return a.x2<b.x2;
	});
}
void cdq(int l,int r){
	if(l>=r) return;
	int mid=(l+r)>>1;
	cdq(l,mid);cdq(mid+1,r);
	cnts=0;
	int ll=l;
	forup(i,mid+1,r){//把左侧的修改和右侧的询问取出来
		if(qu[i].pos!=0){
			while(ll<=mid&&qu[ll].y1>qu[i].y1){
				if(qu[ll].pos==0){
					seq[++cnts]=qu[ll];
				}
				++ll;
			}
			seq[++cnts]=qu[i];
		}
	}
	cdq2(1,cnts);
	inplace_merge(qu+l,qu+mid+1,qu+r+1,[&](query a,query b){//归并排序
		return a.y1>b.y1;
	});
}
signed main(){
	n=read();m=read();q=read();
	forup(i,1,n){
		scanf(" %s",str+1);
		forup(j,1,m){
			a[i][j]=(str[j]-'A');
		}
	}
	forup(i,1,n){
		forup(j,1,m){//预处理前缀和
			e1[i][j]=e1[i-1][j]+e1[i][j-1]-e1[i-1][j-1]+(a[i][j]==a[i][j-1]);
			e2[i][j]=e2[i-1][j]+e2[i][j-1]-e2[i-1][j-1]+(a[i][j]==a[i-1][j]);
			f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1]+(a[i][j]==a[i][j-1]&&a[i][j]==a[i-1][j]&&a[i][j]==a[i-1][j-1]);
		}
	}
	forup(co,0,25){//寻找每个颜色的空腔
		mem(vis,0);
		forup(i,1,n){
			forup(j,1,m){
				if(vis[i][j]||a[i][j]==co) continue;
				u=0,d=inf,l=inf,r=0;
				dfs(i,j,co);
				if(l!=1&&r!=n&&d!=1&&u!=m){
					qu[++cntq]=query{l,d,r,u,0};
				}
			}
		}
	}
	forup(Case,1,q){
		int x1=read(),y1=read(),x2=read(),y2=read();
		qu[++cntq]=query{x1,y1,x2,y2,Case};
		ans[Case]=calc(x1,y1,x2,y2);
	}
	sort(qu+1,qu+cntq+1,[&](query a,query b){
		if(a.x1!=b.x1) return a.x1>b.x1;
		return a.pos>b.pos;//注意把询问排到修改前面
	});
	cdq(1,cntq);
	forup(i,1,q){
		printf("%d\n",ans[i]);
	}
}
```

---

## 作者：mzgwty (赞：5)

如果将相邻同色点之间连上一条边，那么这是一个平面图，我们要求的就是一个子矩形内的连通块个数

那么根据平面图欧拉定理，点数+区域数-边数=连通块数（除掉无界域）

点数就是矩形面积，边数的话，我们给边定个向，在靠右或者靠下的格子上把这条边统计入总数，问题在于求区域数

如果我们把这个平面图的对偶图求出来的话，就相当于求出在询问矩形内部的点的数量

那么我们知道对偶图上一个点对应的是原图上的一个连通块

看起来不是很好统计，实际上由于我们查询的是子矩形，所以我们可以把这个连通块扩成一个矩形，即恰好包含这个连通块的最小矩形

然后问题就变成了给定 $O(nm)$ 个矩形，$Q$ 次询问被一个矩形完全包含的矩形数量，这个问题明显就是一个四维偏序。

我们先通过排序消掉一维，再通过 CDQ 分治消掉一维，复杂度乘个 $\log$。

按照一般的步骤，这时候应该要么再套一个 CDQ，要么就直接用树套树。

这显然过不去啊是不是。

注意到修改操作高达 $10^6$ 次，而询问次数只有 $10^3$ 次，我们可以考虑把这个树套树换成二维分块，然后根号平衡一下，做到 $O(1)$ 修改，$O(\sqrt{nm})$ 查询，即每层修改复杂度为 $O(nm)$，查询复杂度为 $O(q\sqrt{nm})$，$\log$ 层的总复杂度就是 $O((nm+q\sqrt{nm})\log n)$，可以过得去。

代码比较好写，没有什么细节

```cpp
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long ll;

inline int read() {
	int res=0,f=1;char ch;
	while(ch=getchar(),ch<'0'||ch>'9') if(ch=='-') f=-1;
	while(ch>='0'&&ch<='9') res=res*10+ch-'0',ch=getchar();
	return res*f;
}

inline ll readll() {
	ll res=0,f=1;char ch;
	while(ch=getchar(),ch<'0'||ch>'9') if(ch=='-') f=-1;
	while(ch>='0'&&ch<='9') res=res*10+ch-'0',ch=getchar();
	return res*f;
}

const int N=1005,M=35;

ll tot;
int n,m,q,bn,bm;
int dx[N],dy[N],ux[N],uy[N];
char s[N][N];

int deg[N][N],DX,DY,UX,UY,px[4]={0,1,0,-1},py[4]={1,0,-1,0};
int sum[N][N],id[N][N],w;

inline int calc(int dx,int dy,int ux,int uy) {
	return sum[ux][uy]-sum[ux][dy-1]-sum[dx-1][uy]+sum[dx-1][dy-1];
}

struct node {
	int x,y;
	inline node (int X=0,int Y=0) : x(X),y(Y) {}
	inline node operator - (const node &a) const {return node(x-a.x,y-a.y);}
	inline double ang() {return atan2(y,x);}
};

inline ll cross(const node &a,const node &b) {return 1ll*a.x*b.y-a.y*b.x;}

struct Edge {
	node s,t;int id;
	double ang;
	inline Edge (node S=node(),node T=node(),int I=0) : s(S),t(T),id(I),ang((T-S).ang()) {}
	inline bool operator < (const Edge &a) const {return ang<a.ang;}
}e[N*N*4];

bool vis[N][N][4];

struct Query {
	int a,b,c,d,id;
	inline Query(int A=0,int B=0,int C=0,int D=0,int I=0) : a(A),b(B),c(C),d(D),id(I) {}
}p[N*N],tmp[N*N];

inline bool cmp1(const Query &a,const Query &b) {return a.a!=b.a?a.a>b.a:a.id<b.id;}

int l;

int sze=1,vst[N*N*4],nxt[N*N*4],num[N];

inline void add(node s,node t) {e[++sze]=Edge(s,t),e[sze].id=sze;}

inline int ID(node x) {return id[x.x][x.y];}

vector <Edge> vec[N*N];

struct BLOCK {
	int c1[M][M],c2[M][N],c3[N][M],c4[N][N];
	inline void add(int x,int y,int v) {
		int bx=(x-1)/bn+1,by=(y-1)/bm+1;
		c1[bx][by]+=v,c2[bx][y]+=v,c3[x][by]+=v,c4[x][y]+=v;
	}
	inline int sum(int x,int y) {
		int bx=(x-1)/bn+1,by=(y-1)/bm+1,res=0;
		for(int i=1 ; i<bx ; ++i)
			for(int j=1 ; j<by ; ++j)
				res+=c1[i][j];
		for(int i=1 ; i<bx ; ++i)
			for(int j=(by-1)*bm+1 ; j<=y ; ++j)
				res+=c2[i][j];
		for(int i=(bx-1)*bn+1 ; i<=x ; ++i)
			for(int j=1 ; j<by ; ++j)
				res+=c3[i][j];
		for(int i=(bx-1)*bn+1 ; i<=x ; ++i)
			for(int j=(by-1)*bm+1 ; j<=y ; ++j)
				res+=c4[i][j];
		return res;
	}
}B;

void CDQ(int l,int r) {
	if(l==r) return ;
	int mid=(l+r)>>1;
	CDQ(l,mid),CDQ(mid+1,r);
	int i=l,j=mid+1,k=l;
	while(j<=r) {
		while(i<=mid&&p[i].b>=p[j].b) {
			if(!p[i].id) B.add(p[i].c,p[i].d,1);
			tmp[k++]=p[i],++i;
		}
		if(p[j].id) num[p[j].id]+=B.sum(p[j].c,p[j].d);
		tmp[k++]=p[j],++j;
	}
	for(int w=l ; w<i ; ++w) if(!p[w].id) B.add(p[w].c,p[w].d,-1);
	while(i<=mid) tmp[k++]=p[i],++i;
	for(int k=l ; k<=r ; ++k) p[k]=tmp[k];
}

inline void solve() {
	for(int x=1 ; x<=n ; ++x)
		for(int y=1 ; y<=m ; ++y)
			id[x][y]=++w;
	for(int x=1 ; x<=n ; ++x)
		for(int y=1 ; y<=m ; ++y) {
			for(int i=0 ; i<4 ; ++i) {
				int nx=x+px[i],ny=y+py[i];
				if(s[x][y]==s[nx][ny]) {
					++deg[x][y];
					if(vis[x][y][i]) continue ;
					vis[x][y][i]=vis[nx][ny][i^2]=1;
					add(node(x,y),node(nx,ny)),vec[id[x][y]].push_back(e[sze]);
					add(node(nx,ny),node(x,y)),vec[id[nx][ny]].push_back(e[sze]);
				}
			}
			sum[x][y]=sum[x-1][y]+sum[x][y-1]-sum[x-1][y-1]+deg[x][y];
		}
	for(int i=1 ; i<=w ; ++i) sort(vec[i].begin(),vec[i].end());
	for(int i=2 ; i<=sze ; ++i) {
		int Id=ID(e[i].t);
		vector <Edge>::iterator it=lower_bound(vec[Id].begin(),vec[Id].end(),e[i^1]);
		if(it==vec[Id].begin()) it=vec[Id].end();
		--it;
		nxt[i]=(*it).id;
	}
	for(int i=2 ; i<=sze ; ++i) {
		if(vst[i]) continue ;
		int mx=e[i].s.x,my=e[i].s.y,nx=mx,ny=my;
		mx=max(mx,e[i].t.x),my=max(my,e[i].t.y);
		nx=min(nx,e[i].t.x),ny=min(ny,e[i].t.y);vst[i]=1;
		ll S=cross(e[i].s,e[i].t);
		for(int j=nxt[i] ; j!=i ; j=nxt[j]) {
			vst[j]=1;
			if(j==(i^1)) {S=-1;break ;} 
			mx=max(mx,e[j].t.x),my=max(my,e[j].t.y);
			nx=min(nx,e[j].t.x),ny=min(ny,e[j].t.y);
			S+=cross(e[j].s,e[j].t);
		}
		if(S>0) p[++l]=Query(nx,ny,mx,my,0);
	}
	for(int i=1 ; i<=q ; ++i) p[++l]=Query(dx[i],dy[i],ux[i],uy[i],i);
	sort(p+1,p+l+1,cmp1);
	CDQ(1,l);
	for(int i=1 ; i<=q ; ++i) {
		DX=dx[i],DY=dy[i],UX=ux[i],UY=uy[i];
		int tot=calc(DX,DY,UX,UY);
		/*for(int p=DX ; p<=UX ; ++p) {
			if(s[p][DY]==s[p][DY-1]) --tot;
			if(s[p][UY]==s[p][UY+1]) --tot;
		}
		for(int p=DY ; p<=UY ; ++p) {
			if(s[DX][p]==s[DX-1][p]) --tot;
			if(s[UX][p]==s[UX+1][p]) --tot;
		}这一堆可以用前缀和优化*/
		printf("%d\n",(UX-DX+1)*(UY-DY+1)-tot/2+num[i]);
	}
}

int main() {
	n=read(),m=read(),q=read(),bn=sqrt(n),bm=sqrt(m);
	for(int i=1 ; i<=n ; ++i) scanf("%s",s[i]+1);
	for(int i=1 ; i<=q ; ++i) dx[i]=read(),dy[i]=read(),ux[i]=read(),uy[i]=read(),tot+=(ux[i]-dx[i]+1)*(uy[i]-dy[i]+1);
	solve();
	return 0;
}
```

---

## 作者：Leasier (赞：4)

Update on 2022.4.7：感谢 @2b7e151628ae。

前置芝士：[可撤销并查集](https://www.cnblogs.com/brady12/p/15489195.html)、[分块](https://oi-wiki.org/ds/block-array/)

考虑一个简单的暴力：$ans$ 初值为子矩形大小，将子矩形内所有相邻且颜色相同的点在可撤销并查集中连边，每遇到一对颜色相同且此前已在同一联通块中的点将 $ans$ 减一。完成所有操作后撤销。

不难发现两个相邻且相邻的边长相同的子矩形的信息是可以合并的，答案为两个子矩形单独的答案之和减去合并相邻边上的所有点产生的贡献。

于是不难想到二维分块。设横轴块长为 $\sqrt{n}$，$bel_{1, x}$ 表示横轴上 $x$ 点所属块，纵轴块长为 $\sqrt{m}$，$bel_{2, x}$ 表示纵轴上 $x$ 点所属块。

当 $bel_{1, x1} + 1 \geq bel_{1, x2}$ 或 $bel_{1, x1} + 1 \geq bel_{1, x2}$，直接暴力即可。时间复杂度为 $O(q \log nm (n \sqrt{m} + m \sqrt{n}))$。

否则，考虑合并整块信息，并对散块单独处理。

1. 整块合并

直接按前述方式操作即可。

2. 左上、左下、右上、右下四个散块

考虑建 $nm$ 个虚点表示合并过程中临时使用的点，直接合并虚点即可。

3. 上、下、左、右四个散块

对于散块内到散块内的连边，合并虚点即可；对于散块内到整块内的连边，合并散块内的虚点和整块内的实点即可。

综上，该部分的时间复杂度也为 $O(q \log nm (n \sqrt{m} + m \sqrt{n}))$。

由于最开始要预处理整块信息，时间复杂度为 $O(q \log nm (n \sqrt{m} + m \sqrt{n}) + nm \log nm)$。

本题较为卡常，我块长取的是 $0.9 \sqrt{n}$。

代码：
```cpp
#include <stdio.h>
#include <math.h>

#define check(new_x, new_y) if (mp[j][y] == mp[new_x][new_y]) dsu.merge2(id[j][y], id[new_x][new_y])

typedef struct Node_tag {
	int x;
	int y;
	Node_tag(){}
	Node_tag(int x_, int y_){
		x = x_;
		y = y_;
	}
} Node;

typedef struct {
	int top = 0;
	int root[2000007], size[2000007];
	Node s[2000007];
	
	inline void init(int n){
		for (register int i = 1; i <= n; i++){
			root[i] = i;
			size[i] = 1;
		}
	}
	
	int get_root1(int x){
		while (root[x] != x) x = root[x] = root[root[x]];
		return x;
	}
	
	#define swap(x, y) x ^= y ^= x ^= y
	
	inline bool merge1(int x, int y){
		int x_root = get_root1(x), y_root = get_root1(y);
		if (x_root == y_root) return false;
		if (size[x_root] > size[y_root]) swap(x_root, y_root);
		root[x_root] = y_root;
		size[y_root] += size[x_root];
		return true;
	}
	
	int get_root2(int x){
		while (root[x] != x) x = root[x];
		return x;
	}
	
	inline void merge2(int x, int y){
		int x_root = get_root2(x), y_root = get_root2(y);
		if (x_root != y_root){
			if (size[x_root] > size[y_root]) swap(x_root, y_root);
			root[x_root] = y_root;
			size[y_root] += size[x_root];
			s[++top] = Node(x_root, y_root);
		}
	}
	
	inline void undo(){
		while (top > 0){
			Node cur = s[top--];
			root[cur.x] = cur.x;
			size[cur.y] -= size[cur.x];
		}
	}
} DSU;

DSU dsu;
int belong1[1007], lft1[37], rt1[37], belong2[1007], lft2[37], rt2[37], id[1007][1007], pre_ans[37][37];
char mp[1007][1007];

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline int min(int a, int b){
	return a < b ? a : b;
}

inline int f(int x, int y, int n){
	return n * (x - 1) + y;
}

inline int get_sum(int l1, int r1, int l2, int r2){
	return pre_ans[r1][r2] - pre_ans[l1 - 1][r2] - pre_ans[r1][l2 - 1] + pre_ans[l1 - 1][l2 - 1];
}

int main(){
	int n = read(), m = read(), q = read(), size = n * m, block1 = sqrt(n) * 0.9, k = (n - 1) / block1 + 1, block2 = sqrt(m) * 0.9, x = (m - 1) / block2 + 1;
	dsu.init(size * 2);
	for (register int i = 1; i <= n; i++){
		belong1[i] = (i - 1) / block1 + 1;
	}
	for (register int i = 1; i <= k; i++){
		lft1[i] = block1 * (i - 1) + 1;
		rt1[i] = min(i * block1, n);
	}
	for (register int i = 1; i <= m; i++){
		belong2[i] = (i - 1) / block2 + 1;
	}
	for (register int i = 1; i <= x; i++){
		lft2[i] = block2 * (i - 1) + 1;
		rt2[i] = min(i * block2, m);
	}
	for (register int i = 1; i <= n; i++){
		for (register int j = 1; j <= m; j++){
			id[i][j] = f(i, j, m);
		}
	}
	for (register int i = 1; i <= n; i++){
		scanf("%s", &mp[i][1]);
	}
	for (register int i = 1; i <= k; i++){
		for (register int j = 1; j <= x; j++){
			pre_ans[i][j] = (rt1[i] - lft1[i] + 1) * (rt2[j] - lft2[j] + 1);
			for (register int y = lft1[i]; y <= rt1[i]; y++){
				for (register int z = lft2[j]; z <= rt2[j]; z++){
					if (z < rt2[j] && mp[y][z] == mp[y][z + 1] && dsu.merge1(id[y][z] + size, id[y][z + 1] + size)) pre_ans[i][j]--;
					if (y < rt1[i] && mp[y][z] == mp[y + 1][z] && dsu.merge1(id[y][z] + size, id[y + 1][z] + size)) pre_ans[i][j]--;
				}
			}
			pre_ans[i][j] += pre_ans[i][j - 1] + pre_ans[i - 1][j] - pre_ans[i - 1][j - 1];
		}
	}
	for (register int i = 1; i <= q; i++){
		int x1 = read(), y1 = read(), x2 = read(), y2 = read(), a = belong1[x1], b = belong1[x2], c = belong2[y1], d = belong2[y2], ans = (x2 - x1 + 1) * (y2 - y1 + 1);
		if (a + 1 >= b || c + 1 >= d){
			for (register int j = x1; j <= x2; j++){
				for (register int y = y1; y <= y2; y++){
					if (y < y2 && mp[j][y] == mp[j][y + 1]) dsu.merge2(id[j][y], id[j][y + 1]);
					if (j < x2 && mp[j][y] == mp[j + 1][y]) dsu.merge2(id[j][y], id[j + 1][y]);
				}
			}
		} else {
			int ai = a + 1, bd = b - 1, ci = c + 1, dd = d - 1, rt1bd = rt1[bd], lft1ai = lft1[ai], rt2dd = rt2[dd], lft2ci = lft2[ci], rt1a = rt1[a], lft1b = lft1[b], rt2c = rt2[c], lft2d = lft2[d];
			ans += get_sum(ai, bd, ci, dd) - (rt1bd - lft1ai + 1) * (rt2dd - lft2ci + 1);
			for (register int j = lft2ci; j <= rt2dd; j++){
				if (mp[rt1a][j] == mp[lft1ai][j]) dsu.merge2(id[rt1a][j], id[lft1ai][j] + size);
			}
			for (register int j = ai; j < bd; j++){
				int rt1j = rt1[j], lft1ji = rt1j + 1;
				for (register int y = lft2ci; y <= rt2dd; y++){
					if (mp[rt1[j]][y] == mp[lft1[j + 1]][y]) dsu.merge2(id[rt1j][y] + size, id[lft1ji][y] + size);
				}
			}
			for (register int j = lft2ci; j <= rt2dd; j++){
				if (mp[rt1bd][j] == mp[lft1b][j]) dsu.merge2(id[rt1bd][j] + size, id[lft1b][j]);
			}
			for (register int j = lft1ai; j <= rt1bd; j++){
				if (mp[j][rt2c] == mp[j][lft2ci]) dsu.merge2(id[j][rt2c], id[j][lft2ci] + size);
			}
			for (register int j = ci; j < dd; j++){
				int rt2j = rt2[j], lft2ji = rt2j + 1;
				for (register int y = lft1ai; y <= rt1bd; y++){
					if (mp[y][rt2j] == mp[y][lft2ji]) dsu.merge2(id[y][rt2j] + size, id[y][lft2ji] + size);
				}
			}
			for (register int j = lft1ai; j <= rt1bd; j++){
				if (mp[j][rt2dd] == mp[j][lft2d]) dsu.merge2(id[j][rt2dd] + size, id[j][lft2d]);
			}
			for (register int j = x1; j <= rt1a; j++){
				for (register int y = y1; y <= rt2c; y++){
					check(j, y + 1);
					check(j + 1, y);
				}
				for (register int y = lft2d; y <= y2; y++){
					check(j, y - 1);
					check(j + 1, y);
				}
			}
			for (register int j = lft1b; j <= x2; j++){
				for (register int y = y1; y <= rt2c; y++){
					check(j, y + 1);
					check(j - 1, y);
				}
				for (register int y = lft2d; y <= y2; y++){
					check(j, y - 1);
					check(j - 1, y);
				}
			}
			for (register int j = lft1ai; j <= rt1bd; j++){
				for (register int y = y1; y <= rt2c; y++){
					if (mp[j][y] == mp[j][y + 1]) dsu.merge2(id[j][y], y == rt2c ? id[j][y + 1] + size : id[j][y + 1]);
					if (mp[j][y] == mp[j + 1][y]) dsu.merge2(id[j][y], id[j + 1][y]);
				}
				for (register int y = lft2d; y <= y2; y++){
					if (mp[j][y] == mp[j][y - 1]) dsu.merge2(id[j][y], y == lft2d ? id[j][y - 1] + size : id[j][y - 1]);
					if (mp[j][y] == mp[j + 1][y]) dsu.merge2(id[j][y], id[j + 1][y]);
				}
			}
			for (register int j = lft2ci; j <= rt2dd; j++){
				for (register int y = x1; y <= rt1a; y++){
					if (mp[y][j] == mp[y][j + 1]) dsu.merge2(id[y][j], id[y][j + 1]);
					if (mp[y][j] == mp[y + 1][j]) dsu.merge2(id[y][j], y == rt1a ? id[y + 1][j] + size : id[y + 1][j]);
				}
				for (register int y = lft1b; y <= x2; y++){
					if (mp[y][j] == mp[y][j + 1]) dsu.merge2(id[y][j], id[y][j + 1]);
					if (mp[y][j] == mp[y - 1][j]) dsu.merge2(id[y][j], y == lft1b ? id[y - 1][j] + size : id[y - 1][j]);
				}
			}
		}
		ans -= dsu.top;
		dsu.undo();
		printf("%d\n", ans);
	}
	return 0;
}
```

---


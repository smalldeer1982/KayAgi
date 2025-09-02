# Drivers Dissatisfaction

## 题目描述

In one kingdom there are $ n $ cities and $ m $ two-way roads. Each road connects a pair of cities, and for each road we know the level of drivers dissatisfaction — the value $ w_{i} $ .

For each road we know the value $ c_{i} $ — how many lamziks we should spend to reduce the level of dissatisfaction with this road by one. Thus, to reduce the dissatisfaction with the $ i $ -th road by $ k $ , we should spend $ k·c_{i} $ lamziks. And it is allowed for the dissatisfaction to become zero or even negative.

In accordance with the king's order, we need to choose $ n-1 $ roads and make them the main roads. An important condition must hold: it should be possible to travel from any city to any other by the main roads.

The road ministry has a budget of $ S $ lamziks for the reform. The ministry is going to spend this budget for repair of some roads (to reduce the dissatisfaction with them), and then to choose the $ n-1 $ main roads.

Help to spend the budget in such a way and then to choose the main roads so that the total dissatisfaction with the main roads will be as small as possible. The dissatisfaction with some roads can become negative. It is not necessary to spend whole budget $ S $ .

It is guaranteed that it is possible to travel from any city to any other using existing roads. Each road in the kingdom is a two-way road.

## 样例 #1

### 输入

```
6 9
1 3 1 1 3 1 2 2 2
4 1 4 2 2 5 3 1 6
1 2
1 3
2 3
2 4
2 5
3 5
3 6
4 5
5 6
7
```

### 输出

```
0
1 1
3 1
6 1
7 2
8 -5
```

## 样例 #2

### 输入

```
3 3
9 5 1
7 7 2
2 1
3 1
3 2
2
```

### 输出

```
5
3 0
2 5
```

# 题解

## 作者：Suzt_ilymtics (赞：5)

# 0.闲聊几句


[--->卑微的题面](https://www.luogu.com.cn/problem/CF733F)

 [博客食用更佳>-<](https://www.luogu.com.cn/blog/Silymtics/cf733f-drivers-dissatisfaction-ti-xie)


------------

# 1.Solution

主要思路：[最小生成树](https://www.luogu.com.cn/problem/P3366) + [$\text{LCA}$](https://www.luogu.com.cn/problem/P3379) + （感觉和[严格次小生成树](https://www.luogu.com.cn/problem/P4180)有点像）

根据题意我们需要先用 $\text{Kruskal}$ 建出一棵最小生成树

我们考虑枚举每一条边来确定降低那条边的权值更优。

为什么只需要枚举一条边？

假设现在有两条边 $e_1,e_2$，如果 $e_1 > e_2$ 那么不断的减 $e_2$ 一定更优，这样赚便宜。如果 $e_1 = e_2$ 那么减那条边都可以，既然都可以，把所有的操作都放在一个边上岂不是更简单？

现在讨论每一条边，

- 如果是在树上的边：

直接把所有钱都砸在这条边上（~~money 的力量~~），看看得到的最小生成树权值和是否会更小

- 如果是非树边：

同样是把所有钱都砸在这条边上，这条边就会有一个新的权值。

因为连接这条边会使原来的生成树出现一个环，那么需要我们删掉环上的一条边。根据贪心的策略，我们找到最大的边删除。然后判断此时生成树的权值和是否更小。如果更小就更新答案。

直接枚举边做出判断是难以实现的,这就需要我们预处理最大值。

倍增预处理或者直接裸上树链剖分都可以。

再按照上面的思路跑一遍。

最后输出答案（可能有多组解）。


### 提几点注意事项（感谢Aliemo学姐为我debug）：

1、代码中有除法时要保证除数不为零，否则会RE，就像我

![RE一览](https://cdn.luogu.com.cn/upload/image_hosting/45gi1ln0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

2、看好题目中 $ans$ 最大值可能为多少（ $2 \times 10^{14}$ !!!），所以用到 $\text{INF}$ 的时候要开大一点（开 $10^{18}$ 就足够）

3、注意不同图（树）中的边号所存的边号到底是排序前的边号，还是排序后的边号


# 2.放代码

（~~~~我知道你们只喜欢这个~~~~）

## 2.1 关于变量名的解释：
```cpp
/*
edge{
	起点，终点
	权值w，花费c，边号（排序后），下一条边 
}e[]：生成树的边 
,a[]：输入的边 
node{
	边号，边的权值 
} maxm[][]：用来存编号及边的权值（倍增里存的最大值 
n:点数 
m:边数
S:钱数（花费
ans：存答案 
cnt：通过kruskal建出的生成树的权值和
flag：标记减那一条边更优
pre_jia:上一次加的边 
pre_jian: 上一次减的边
c[]：每条边减权值所需的花费
w[]：每条边的权值
fa[]：每个点的父亲（kruskal的并查集）
f[][]：倍增惯用的小抄
depth[]：每个点的深度（LCA惯用数组）
vise[]:标记 用kruskal建完树 后有那几条边被选中 
vis_new[]: 标记 用过减边权的边 后有那几条边被选中
*/
```
## 2.2 真正的AC代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define LL long long
#define INF 1e18
using namespace std;
const int MAXN = 2e5+5;
struct edge{
	int from,to;
	LL w,c,bh,nxt;
	bool operator < (const edge &b) const {return w < b.w ;}
}e[MAXN << 2],a[MAXN << 2];
struct node{
	int bh;LL dis;
}maxm[MAXN][26];//maxm用来存编号及边的权值 
int head[MAXN << 2], num_edge;
LL n, m, S, ans, cnt, flag, pre_jia, pre_jian;
int c[MAXN], w[MAXN]; 
LL fa[MAXN];//并查集 
LL f[MAXN][26];//倍增 
LL depth[MAXN];//存深度 
bool vise[MAXN << 1],vis_new[MAXN << 1];//vise标记在最小生成树中的边，vis_new标记更换过的边 

LL find(LL x) {return fa[x] == x ? x : fa[x] = find(fa[x]); }
void add(int from,int to,LL w,LL c, LL i){
	e[++num_edge].from = from;		e[num_edge].to = to;
	e[num_edge].w = w;				e[num_edge].c = c;
	e[num_edge].bh = i;
	e[num_edge].nxt = head[from];
//	e[num_edge] = (edge){from, to, w, c, i, head[from]};
	head[from] = num_edge;
}

void kruskal(){
	for(int i=1;i<=m;++i){
		LL uf = find(a[i].from), vf = find(a[i].to);
		if(uf != vf){
			add(a[i].from,a[i].to,a[i].w,a[i].c,i);
			add(a[i].to,a[i].from,a[i].w,a[i].c,i);//加边是排序后的编号 
			fa[uf] = vf;
			cnt += a[i].w;
			vise[i] = 1;
			vis_new[i] = 1;
		} 
	}
}

void dfs(LL u,LL fa){//在建出的最小生成树上跑DFS，并对LCA进行初始化 
	f[u][0] = fa;
	//cout<<u<<" "<<fa<<"lzx"<<endl;
	for(int i=head[u]; i; i = e[i].nxt){
		LL v = e[i].to;
		if(v == fa) continue;
		else{
			depth[v] = depth[u] + 1ll;
			maxm[v][0].dis = e[i].w;
			maxm[v][0].bh = e[i].bh;//a中排序后的编号 
			dfs(v,u);
		}
	}
}

void init_lca(){
	for(int i=1;i<=25;++i){
		for(int j = 1; j <= n; ++j){
		//cout<<f[j][0]<<"fjh"<<endl;
			f[j][i] = f[f[j][i-1]][i-1];//LCA初始化 
			if(maxm[j][i-1].dis > maxm[f[j][i-1]][i-1].dis){
				maxm[j][i].dis = maxm[j][i-1].dis;//存向上跳2^i步的最大值 
				maxm[j][i].bh = maxm[j][i-1].bh;//及编号 
			}
			else{
				maxm[j][i].dis = maxm[f[j][i-1]][i-1].dis;
				maxm[j][i].bh = maxm[f[j][i-1]][i-1].bh;
			}
		}
	}
}

LL get_lca(LL u,LL v){
	if(depth[u] > depth[v]) swap(u,v);//保证v的深度大于u的深度 
	for(int i = 25; i >= 0; --i){//把v点调到和u点同样的位置 
		if(depth[f[v][i]] < depth[u]) continue;
		else v = f[v][i];
	}
	if(u == v) return u;//如果此时是同一个点，直接返回即可 
	for(int i = 25; i >= 0; --i){//两个点一起向上跳，跳到最近公共祖先的下面 
		if(f[v][i] != f[u][i]){ 
			v = f[v][i];
			u = f[u][i];
		}
	}
	//cout<<u<<"wzd"<<endl;
	return f[u][0];//再跳一下 
}

node qmax(LL u, LL v){
	node Ans;
	Ans.bh = -1;	Ans.dis = -INF;
	for(int i = 25; i >= 0; --i){
		if(depth[f[u][i]] >= depth[v]){
			if(Ans.dis < maxm[u][i].dis){//如果珂跳到最近公共祖先的下面，尝试更新最大值 
				Ans.dis = maxm[u][i].dis;
				Ans.bh = maxm[u][i].bh;
			}
			u = f[u][i];//向上跳一下 
		}
	}
	return Ans;//返回Ans值 
}

int main()
{
   	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;++i)	scanf("%d",&w[i]);
	for(int i=1;i<=m;++i)	scanf("%d",&c[i]);
	for(int i=1,u,v;i<=m;++i){//存边 
		scanf("%d%d",&u,&v);
		a[i].from = u;	a[i].to = v;
		a[i].w = w[i];	a[i].c = c[i];
		a[i].bh = i;//a[i].bh存的是一开始的边号 
	}
	scanf("%lld",&S);
	
	for(int i=1;i<=n;++i) fa[i] = i;
	sort(a+1,a+m+1);//i与a[i].bh已经不一样了 
	kruskal();
	
	depth[1] = 1;
		maxm[1][0].dis = -INF;
		maxm[1][0].bh = e[1].bh;
	
	dfs(1,1);//深搜初始化LCA 
	init_lca();//初始化LCA
	
	 
	ans = INF;
	for(int i=1;i<=m;++i){
		LL ww = S / a[i].c;
		if(vise[i]){//如果这条边是最小生成树里面的，直接减去即可 
			if(ans > cnt - ww){
				flag = i; //更新要减权值的bian 
			} 
			ans = min(ans, cnt - ww);
		}
		else{
			LL u = a[i].from, v = a[i].to;
			LL lca = get_lca(u,v);//u，v的LCA 
			node maxu = qmax(u, lca);//两边的最大值都要求 
			node maxv = qmax(v, lca);
			if(maxu.dis > maxv.dis){//挑有最大边最大的那一边 
				if(ans > cnt - maxu.dis + a[i].w - ww){
		//删掉最长的那个边，加上新来的那条边，减去可以减得边权值 
					ans = cnt - maxu.dis + a[i].w - ww;
					vis_new[pre_jia] = 0;
					vis_new[pre_jian] = 1;
					vis_new[i] = 1;//把新加的标记一下 
					vis_new[maxu.bh] = 0;//把删掉的标记为0 
					pre_jia = i;
					pre_jian = maxu.bh;//这里都是a中排序后的边号 
					flag = i;//更新一下标记bian
				}	
			}
			else{
				if(ans > cnt - maxv.dis + a[i].w - ww){
					ans = cnt - maxv.dis + a[i].w - ww;
					vis_new[pre_jia] = 0;
					vis_new[pre_jian] = 1;
					vis_new[i] = 1;
					vis_new[maxv.bh] = 0;
					pre_jia = i;
					pre_jian = maxv.bh;//这里也是排序后的边号 
					flag = i;//更新一下标记bian
				}
			}
		}
		//if(pre_jian == 1){
	//		cout<<"lkp"<<endl;
	//	}
	//	if( vis_new[1] == 0){
	//		printf("bj\n");
	//	}
	}
	if(flag)//防止除数为0
	a[flag].w = a[flag].w - (S / a[flag].c);
	printf("%lld\n",ans);
	for(int i = 1; i <= m; ++i){
		if(vis_new[i]){//如果这条边在新树中被标记过，就输出  
			printf("%lld %lld\n", a[i].bh, a[i].w);
		}
	}
	
	return 0;
}
```
## 2.3 附：我遇到的多组解：
样例一题面输出：

```cpp
0
1 1
3 1
6 1
7 2
8 -5
```

我的输出（不同但是过了）：

```cpp
0
1 1
4 1
6 1
7 2
8 -5
```

手膜样例之后发现其实都是一组合法解，需要自己注意一下。

（~~样例不对不要慌，万一交上去AC了呢~~）

------------


# 3.写在最后

第一次写黑题题解（~~现在掉紫了~~），由于细节太多，难免有些遗漏

如果您有什么疑惑，或我犯了什么sb错误，尽管提出

$\text{The\ end.}$

---

## 作者：KEBrantily (赞：4)

## 扯在前面
人生第一道黑（>▽< )。

那天听了老师讲图论讲了这道题，~~发现这道黑题并不是很黑~~于是就做了做，在同机房dalao的帮助下三个小时做完（太菜了），于是来发篇题解。


------------
# 正文
## 题意
给出一张 n 个点 m 条边的无向图，每条边(ai,bi)有一个权值 wi 和费用 ci，表示这条边 每降低 1 的权值需要 ci 的花费。现在一共有 S 费用可以用来降低某些边的权值（可以降到 负数），求图中的一棵权值和最小的生成树并**输出方案**


------------

## 分析
本题就是一个求最小生成树加不定边的题目，而且输出多了个方案

**题目中信息很多，在这里先总结一下：**
1. 最多降低权值为 S / ci;
1. 既然你可以用 S 费用来降低 S / ci 的权值，而且可以降到负数，本题又是求最小生成树，那就一直降一条边就好了（保证降完后本条边是在生成树里的）；
1. 他要求输出方案，就需要开数组或结构体来存储树上的是第几条边以及他的权值

~~好像就这么点信息也不是很多~~

**那么我们想想该怎么做**

- 我们知道，本题肯定是先求最小生成树，然后再枚举边看是否替换并比较最优方案；
- 枚举边有两种情况，第一是已经在生成树上的边，既然已经在树上，那么答案就直接把最小生成树权值和减去降低的权值拿来比较就好了
- 另一方面，最多减低 S / ci 的权值，那 ci 肯定越小越好，所以在树内的边我们就降低 c 最小的那一条
- 枚举数外的边时，我们要看加入当前边后是否为环（肯定是），把这条边与环上最大的树边比较，如果树边更大就减去这条树边（这个思路是不是有些熟悉）
- 当不用换边时，就直接输出原树的信息就好了


------------
## 贴码
做的时候没写注释，但是很好理解，就是lca板子加编号和边权的存储，最后打个标记看是否换边
```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#define maxn 200005
#define INF 1000000000000000000

using namespace std;

int n,m;
long long f[maxn][26],depth[maxn];
long long tot,head[maxn*4],fa[maxn],S,ans,num,cnt,sum,flag,lkp,fjh;
bool vis[maxn*2],v[maxn*2];

struct node{
	long long dis,c,fr,to,bh,nxt;
}a[maxn*4],e[maxn*4];

struct ma{
	long long dis,bh;
}maxi[maxn][26];

inline void add(long long fr,long long to,long long dis,long long c,long long bh){
	e[++tot].to=to;
	e[tot].fr=fr;
	e[tot].dis=dis;
	e[tot].bh=bh;
	e[tot].c=c;
	e[tot].nxt=head[fr];
	head[fr]=tot;
}


inline long long Getf(long long x){
	if(fa[x]==x) return x;
	return fa[x]=Getf(fa[x]);
}

inline void hb(long long x,long long y){
	x=Getf(x);
	y=Getf(y);
	if(x!=y) fa[y]=x;
}

inline bool pd(long long x,long long y){
	x=Getf(x);
	y=Getf(y);
	if(x==y) return true;
	return false; 
}

inline void dfs(long long now,long long p){ 
	f[now][0]=p;
	for(long long i=head[now];i;i=e[i].nxt){
		long long to=e[i].to;
		if(to==f[now][0]) continue;
	    depth[to]=depth[now]+1ll;
		maxi[to][0].dis=e[i].dis;
		maxi[to][0].bh=e[i].bh;
		dfs(to,now);
	}
}

inline void caq(){
	for(int i=1;i<=25;++i)
		for(int j=1;j<=n;++j){
			f[j][i]=f[f[j][i-1]][i-1];//
//			maxi[j][i]=max(maxi[j][i-1],maxi[f[j][i-1]][i-1]);
//			mini[j][i]=max(mini[j][i-1],mini[f[j][i-1]][i-1]);
			if(maxi[j][i-1].dis>maxi[f[j][i-1]][i-1].dis){
			    maxi[j][i].dis=maxi[j][i-1].dis;
				maxi[j][i].bh=maxi[j][i-1].bh;
			}
            else{
			    maxi[j][i].dis=maxi[f[j][i-1]][i-1].dis;
            	maxi[j][i].bh=maxi[f[j][i-1]][i-1].bh;
		    }
		}
}

inline long long lca(long long x,long long y){
    if(depth[x]<depth[y]) swap(x,y);
//    while(depth[x]>depth[y])
//        x=f[x][lg[depth[x]-depth[y]]-1];
    for(int i=25;i>=0;--i)
		if(depth[f[x][i]]>=depth[y])
			x=f[x][i];
    if(x==y) return x;
    for(int i=25;i>=0;--i)
        if(f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    return f[x][0];
}

inline ma get_max(long long u,long long v)
{
    ma Ans;
	Ans.bh=-1;
	Ans.dis=-INF;
	for(int i=25;i>=0;--i){
		if(depth[f[u][i]]>=depth[v]){
		    if(Ans.dis<maxi[u][i].dis){
		    	Ans.dis=maxi[u][i].dis;
		    	Ans.bh=maxi[u][i].bh;
			}
			u=f[u][i];
		}
	}
	return Ans;
}

inline long long cmp(node a,node b){
	return a.dis<b.dis;
}

int main(){
	cin>>n;cin>>m;
	
	for(int i=1;i<=m;i++) cin>>a[i].dis;
	for(int i=1;i<=m;i++) cin>>a[i].c;
	for(int i=1;i<=m;i++){
		cin>>a[i].fr;
		cin>>a[i].to;
		a[i].bh=i;
	}
	cin>>S;
	
	for(int i=1;i<=n;i++) fa[i]=i;
	
	sort(a+1,a+m+1,cmp);
	
	for(int i=1;i<=m;i++){
		if(!pd(a[i].fr,a[i].to)){
			hb(a[i].fr,a[i].to);
			add(a[i].fr,a[i].to,a[i].dis,a[i].c,i);
			add(a[i].to,a[i].fr,a[i].dis,a[i].c,i);
			sum+=a[i].dis;
			vis[i]=1;
			v[i]=1;
		}
	}
	
//	sort(e+1,e+m+1,cnp);
	
	depth[1] = 1;
	maxi[1][0].dis = -INF;
	maxi[1][0].bh = e[1].bh;
	
	dfs(1,1);
	caq();

	
	cnt=INF;
	for(long long i=1;i<=m;i++){
		long long ww=S/a[i].c;
		if(vis[i]){
			if(cnt>sum-ww){
			    flag=i;
			}
			cnt=min(sum-ww,cnt);
		}
		else{
			long long fr=a[i].fr;
			long long to=a[i].to;
			long long lcaa=lca(fr,to);
			ma maxu=get_max(fr,lcaa);
			ma maxv=get_max(to,lcaa);
			if(maxu.dis>maxv.dis){
				if(cnt>sum-maxu.dis+a[i].dis-ww){
					cnt=sum-maxu.dis+a[i].dis-ww;
					v[lkp]=0;
					v[fjh]=1;
					v[i]=1;
					v[maxu.bh]=0;
					lkp=i;
					fjh=maxu.bh;
					flag=i;
				}
			}
			else{
				if(cnt>sum-maxv.dis+a[i].dis-ww){
				    cnt=sum-maxv.dis+a[i].dis-ww;
				    v[lkp]=0;
				    v[fjh]=1;
				    v[i]=1;
				    v[maxv.bh]=0;
				    lkp=i;
				    fjh=maxv.bh;
				    flag=i;
				}
			}
		}
//	cout<<ww<<"  ";
	}
	if(flag)
		a[flag].dis=a[flag].dis-(S/a[flag].c);
	printf("%lld\n",cnt);
//	cout<<flag<<" ";
//	cout<<S/a[flag].c<<endl; 
	for(int i=1;i<=m;i++)
		if(v[i]) printf("%lld %lld\n",a[i].bh,a[i].dis);
	return 0;
}
```

第一次A黑可能比较鸡冻，如果有什么不对的地方请及时告知我

---

## 作者：_ajthreac_ (赞：3)

### 0.一些想说的东西
课上讲了这个题，感觉没什么难度。即使算上一些实现细节我感觉最多紫色了。    
发现仅有的两篇题解代码注释都比较少（至少我这种蒟蒻看了好长时间），所以我参照第一篇题解的代码，又写了一份更可读、注释更全面的。        
### 1.思路
楼下的各位$dalao$的思路比较简短，我还是来带着大家一起看一看。      
首先，我们注意到，$c$是可以无限降低的。这说明我们可以采取贪心的手段，把$S$全用到一条边上，这样一定是最优的。         
现在我们的问题，也是这道题的核心，就是**怎么找这条边**。           
我们又可以很容易地发现，要降的边本来的边权也要尽量小，我们就可以求这个图的**最小**生成树，在这棵树里枚举$c$最小的边。             
还有一些问题：如果树外的边更优怎么办？         
例如：若$a_i,a_o$为两条分别在树内和树外的边，$w_i=1,c_i=100,w_o=19,c_o=5,S=100$，此时，选择$a_o$明显比选择$a_i$更优。
于是基本思路就出来了：先建最小生成树，求出树里$c$最小的边；再枚举树外$c$最小的边$(u,v)$，用它替换原树内$u,v$间最长边。
### 2.实现
最小生成树用Kruskal建立，用LCA求$u,v$间最大边权。         
求出最大边权后这条边就不能输出了，所以在输出时枚举边还需要加一个判断：当前的边满足最大边权且在$u,v$之间。题解中的**在$u,v$之间**那部分代码不是很清楚，我给大家演示一下：
```cpp
inline bool Check(int a,int b,int c){//Check函数的用途参照下图
	int ab=LCA_Node(a,b);
	int ac=LCA_Node(a,c);
	int bc=LCA_Node(b,c);
	if(ab==bc&&ac==c)return 1;
	if(ab==ac&&bc==c)return 1;
	return 0;
}
```
（点到LCA的路径被省略成了一条边）      
![](https://cdn.luogu.com.cn/upload/image_hosting/p8zcz6b3.png)   
我们按照代码里写的把一些点重合看看：        
![](https://cdn.luogu.com.cn/upload/image_hosting/601facto.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/mi3nyyab.png)    
可以看到，这就是用于判断$c$在$a,b$之间的代码。
### 3.代码
缺省源太长被省略了，可以去[我的博客](https://www.cnblogs.com/juruoajh/)里面找。
```cpp
#define N 200010
int n,m,S;//题中定义 
int fa[N];//用于并查集的祖先数组 
int dep[N];//深度 
int f[N][25];//用于倍增的祖先数组 
int mx[N][25];//用于倍增的当前点到祖先的最大边权
struct Edge {
	int fr,to,wei,c;//起点，终点，边权，花费
	int idx,nxt;//编号，下一条
	int st;//当前边的状态
	//st=0不在MST里 
	//st=1在MST里 
	//st=2在MST里且降低了花费 
}e[N<<1],t[N<<1];//e存初始边，t存MST的边 
int head[N],cnt;
inline void ade(int u,int v,int w){
	t[++cnt].fr=u,t[cnt].to=v,t[cnt].wei=w;
	t[cnt].nxt=head[u],head[u]=cnt;
}
inline bool cmp(Edge a,Edge b){
	return a.wei<b.wei;
}
int fd(int x){//并查集查找 
	return fa[x]==x?x:fa[x]=fd(fa[x]);
}
void Union(int u,int v){//并查集合并 
	int fu=fd(u),fv=fd(v);
	fa[fu]=fv;
}
void DFS(int now,int ff,int wei){//预处理 
	dep[now]=dep[ff]+1;
	f[now][0]=ff;
	mx[now][0]=wei;
	for(int i=1;(1<<i)<=n;i++){
		f[now][i]=f[f[now][i-1]][i-1];//普通的倍增预处理 
		mx[now][i]=max(mx[now][i-1],mx[mx[now][i-1]][i-1]);
	}
	for(int i=head[now];i!=-1;i=t[i].nxt){
		int v=t[i].to;
		if(v!=ff)DFS(v,now,t[i].wei);
	}
}
inline int LCA_Node(int u,int v){//正常的倍增求LCA 
	if(dep[u]>dep[v])swap(u,v);
	for(int i=20;i>=0;i--){
		if(dep[u]<=dep[v]-(1<<i))v=f[v][i];
	}
	if(u==v)return u;
	for(int i=20;i>=0;i--){
		if(f[u][i]!=f[v][i]){
			u=f[u][i],v=f[v][i];
		}
	}
	return f[u][0];
}
inline int LCA_Max(int u,int v){//正常的倍增求u,v之间最大边权
	int ans=0; 
	if(dep[u]>dep[v])swap(u,v);
	for(int i=20;i>=0;i--){
		if(dep[u]<=dep[v]-(1<<i)){
			ans=max(ans,mx[v][i]);
			v=f[v][i];
		}
	}
	if(u==v)return ans;
	for(int i=20;i>=0;i--){
		if(f[u][i]!=f[v][i]){
			ans=max(ans,max(mx[u][i],mx[v][i]));
			u=f[u][i],v=f[v][i];
		}
	}
	return max(ans,max(mx[u][0],mx[v][0]));
}
inline bool Check(int a,int b,int c){//Check函数的用途参照下图
	int ab=LCA_Node(a,b);
	int ac=LCA_Node(a,c);
	int bc=LCA_Node(b,c);
	if(ab==bc&&ac==c)return 1;
	if(ab==ac&&bc==c)return 1;
	return 0;
}
signed main(){
	//读入+预处理部分
	memset(head,-1,sizeof(head));
	Read(n),Read(m); 
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)Read(e[i].wei);
	for(int i=1;i<=m;i++)Read(e[i].c);
	for(int i=1;i<=m;i++){
		int u,v;
		Read(u),Read(v);
		e[i].fr=u,e[i].to=v;
		e[i].idx=i,e[i].st=0;
	}
	Read(S);
	//Kruskal求最小生成树(MST)部分 
	sort(e+1,e+m+1,cmp);
	int sum=0,minc=INF,lstminc=0;//MST上边权和，最小c，最小c所在边
	for(int i=1;i<=m;i++){//Kruskal
		int u=e[i].fr,v=e[i].to,w=e[i].wei,c=e[i].c;
		if(fd(u)!=fd(v)){
			if(c<minc)e[i].st=2,e[lstminc].st=1,minc=c,lstminc=i;
			else e[i].st=1;
			minc=min(minc,c);
			sum+=w;
			Union(u,v);
			ade(u,v,w),ade(v,u,w);
		}
	} 
	//枚举树外边部分 
	int tans=sum,add=0;//暂存ans，新加上的非树边 
	sum-=S/minc;//先从MST里面更新
	DFS(1,0,0);
	for(int i=1;i<=m;i++){
		int u=e[i].fr,v=e[i].to,w=e[i].wei,c=e[i].c;
		if(!e[i].st){//选非树边 
			if(c<minc){//肯定要更优的，否则就直接树里选了 
				int tmp=tans-LCA_Max(u,v)+w-S/c;//计算新的答案 
				if(tmp<sum)add=i,sum=tmp;
			}
		}
	} 
	cout<<sum<<endl;
	if(!add){//MST已经最优，没有选树外边 
		for(int i=1;i<=m;i++){
			if(e[i].st==1)cout<<e[i].idx<<" "<<e[i].wei<<endl;
			if(e[i].st==2)cout<<e[i].idx<<" "<<e[i].wei-S/e[i].c<<endl;
		}
	}else {
		int nu=e[add].fr,nv=e[add].to;
		bool frog=1;
		for(int i=1;i<=m;i++){
			if(i==add)cout<<e[i].idx<<" "<<e[i].wei-S/e[i].c<<endl;
			if(e[i].st){
				//判断是否被删除了 
				if(e[i].wei==LCA_Max(nu,nv)&&Check(nu,nv,e[i].fr)&&Check(nu,nv,e[i].to)&&frog){
					frog=0;
					continue;
				}
				cout<<e[i].idx<<" "<<e[i].wei<<endl;
			}
		}
	}
	return 0;//完结撒花 
}
```
### 4.结束了

---

## 作者：风华正茂 (赞：3)

又是一道最小生成树和lca的CF好题，~~真的很凉心~~。

一开始从严格次小生成树点进来的时候，我是没有什么灵感的。但是我从题目里反复思考，读懂了这句话。

>原话：现在一共有S费用可以用来降低某些边的权值（可以降到负数）

既然可以无限降低，那我们为什么不挑出$c$值最小的那条边，然后把$S$全用在它上面呢。显然这样是最优的。

再深入思考一下：既然只能降低一条边的权值。那么我们按权值求出了一棵最小生成树后，可以得到这棵树最小的$c$值，称为$minc$。

如果我们要更换一条边，我们的总权值不会更优，但是最小的$c$会因此更新。换句话说，更换的这条边只能够小于$minc$。

若加入的边为$(u,v)$，为了使答案更优，我们必须删去$u$到$v$的路径上权值最大的边，~~这不就是lca板子了吗~~。

程序流程就出来了：

1、按权值求出最小生成树。

2、在这颗最小生成树上lca预处理，求路径最大值。

2、枚举未选中的边，考虑是否加入。如果答案更优，那么加入$q$数组，$q[0]$表示要换下的边，$q[1]$表示要换上的边。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 400005
#define M 400005
using namespace std;
ll read() {
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)) {
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)) {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}
struct edge {
	int next,to,id;
	ll ds;
} a[N];
struct node {
	int x,y,id;
	ll z,c;
} b[M];
struct nod {
	ll x,d;
} ans1[M];
int head[N],cnt,fa1[N],used[M];
int n,m,fa[N][21],dep[N],A[N][21];
ll ans,dis[N][21],q[2],tot,S;
int find(int x) {
	if(fa1[x]==x)return x;
	return fa1[x]=find(fa1[x]);
}
void add(int x,int y,int z,int xyz) {
	a[++cnt].next=head[x];
	a[cnt].to=y;
	a[cnt].ds=z;
	a[cnt].id=xyz;
	head[x]=cnt;
}
bool cmp(node a,node b) {
	if(a.z!=b.z)return a.z<b.z;
	return a.c<b.c;
}
bool kmp(nod a,nod b) {
	return a.x<b.x;
}
void dfs(int x,int f,int deep) {
	dep[x]=deep;
	fa[x][0]=f;
	for(int i=1; i<=20; ++i) {
		fa[x][i]=fa[fa[x][i-1]][i-1];
		if(dis[x][i-1]>dis[fa[x][i-1]][i-1])dis[x][i]=dis[x][i-1],A[x][i]=A[x][i-1];
		else dis[x][i]=dis[fa[x][i-1]][i-1],A[x][i]=A[fa[x][i-1]][i-1];
	}
	for(int i=head[x]; i; i=a[i].next) {
		int y=a[i].to;
		if(y==f)continue;
		dis[y][0]=a[i].ds;
		A[y][0]=a[i].id;
		dfs(y,x,deep+1);
	}
}
nod ldis(int x,int y) {
	ll res=0,yyb;
	if(dep[x]<dep[y])swap(x,y);
	for(int i=20; i>=0; --i) {
		if(dep[x]-(1<<i)>=dep[y]) {
			if(res<dis[x][i])res=dis[x][i],yyb=A[x][i];
			x=fa[x][i];
		}
	}
	if(x==y)return (nod) {
		yyb,res
	};
	for(int i=20; i>=0; --i) {
		if(fa[x][i]!=fa[y][i]) {
			if(res<dis[x][i])res=dis[x][i],yyb=A[x][i];
			if(res<dis[y][i])res=dis[y][i],yyb=A[y][i];
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	if(res<dis[x][0])res=dis[x][0],yyb=A[x][0];
	if(res<dis[y][0])res=dis[y][0],yyb=A[y][0];
	return (nod) {
		yyb,res
	};
}
int main() {
	n=read();
	m=read();
	for(int i=1; i<=m; ++i)b[i].z=read();
	for(int i=1; i<=m; ++i)b[i].c=read();
	for(int i=1; i<=m; ++i)b[i].x=read(),b[i].y=read(),b[i].id=i;
	S=read();
	sort(b+1,b+m+1,cmp);
	for(int i=1; i<=n; ++i)fa1[i]=i;
	ll minn=1e9+1,sum=0,biao;//minn的初值用1e9会WA96那个点，亲测(比S大即可)
	for(int i=1; i<=m; ++i) {
		int xzz=find(b[i].x),yyb=find(b[i].y);
		if(xzz!=yyb) {
			fa1[xzz]=yyb;
			sum+=b[i].z;
			used[i]=1;
			if(b[i].c<minn)minn=b[i].c,biao=i;
			add(b[i].x,b[i].y,b[i].z,i);
			add(b[i].y,b[i].x,b[i].z,i);
		}
	}
	ans=sum-S/minn;
	dfs(1,0,1);
	for(int i=1; i<=m; ++i) {
		if(used[i]||minn<=b[i].c)continue;
		nod xzz=ldis(b[i].x,b[i].y);
		ll yyb=sum-xzz.d+b[i].z-S/b[i].c;
		if(yyb<ans) {
			q[0]=xzz.x;
			q[1]=i;
			ans=yyb;
		}
	}
	cout<<ans<<endl;
	if(!q[0]) {//一开始求出的最小生成树就是答案
		for(int i=1; i<=m; ++i) {
			if(used[i]) {
				ans1[++tot].x=b[i].id;
				if(biao==i)ans1[tot].d=b[i].z-S/b[i].c;
				else ans1[tot].d=b[i].z;
			}
		}
	} else {//需要换一条边
		for(int i=1; i<=m; ++i) {
			if(used[i]&&q[0]!=i) {
				ans1[++tot].x=b[i].id;
				ans1[tot].d=b[i].z;
			} else if(q[1]==i) {
				ans1[++tot].x=b[i].id;
				ans1[tot].d=b[i].z-S/b[i].c;
			}
		}
	}
	sort(ans1+1,ans1+tot+1,kmp);
	for(int i=1; i<=tot; ++i)printf("%lld %lld\n",ans1[i].x,ans1[i].d);
	return 0;
}
```

---

## 作者：piao_A_piao (赞：3)

## 最小生成树+LCA

由于求sum(w)最小，很明显我们找到选中的边中最小的c进行计算

先构造一棵最小生成树，则sum(w)-k/min(c)为其答案

又因为最小生成树外的边有可能被选中（由于被选中只可能是c小于生成树中的min(c)，所以最多选一条树外边），依次枚举每条c<min(c)的树外边，加入一条边则需删除一条边，应删除该边u、v间的最长边，可用LCA进行求解

最后记录下所选的边就行了

------------

```
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <queue>
#include <algorithm>
#define N 200005
#define ll long long
#define inf 1e15
using namespace std;

ll n,m,k,cnt;
ll head[N],fa[N],p1[N],p2[N];
ll d[N],f[N][25],w[N][25];

struct node
{
	ll u;
    ll v;
    ll w;
    ll c;
    ll num;
    ll sig;
    ll nex;
}e[2*N],t[2*N];

bool cmp(node x,node y)
{
	return x.w<y.w;
}

void adde(ll v,ll u,ll w)
{
    e[++cnt].u=u;
    e[cnt].v=v;
    e[cnt].w=w;
    e[cnt].nex=head[u];
    head[u]=cnt;
}

ll finds(ll x)
{
	return fa[x]==x?x:fa[x]=finds(fa[x]);
}

void joins(ll x,ll y)
{
	ll fax=finds(x);
	ll fay=finds(y);
	fa[fax]=fay;
}

void dfs(ll u,ll fau,ll val)
{
    d[u]=d[fau]+1;
    f[u][0]=fau;
    w[u][0]=val;
    for(ll i=1;(1<<i)<=n;i++)
    {
		f[u][i]=f[f[u][i-1]][i-1];
    	w[u][i]=max(w[u][i-1],w[f[u][i-1]][i-1]);
    }
    for(ll i=head[u];i!=-1;i=e[i].nex)
    {
        ll v=e[i].v;
        ll w=e[i].w;
        if(v!=fau) dfs(v,u,w);
    }
}

ll lca(ll a,ll b)
{
	ll ans=0;
    if(d[a]>d[b]) swap(a,b);
    for(ll i=20;i>=0;i--)
    if(d[a]<=d[b]-(1<<i)) ans=max(ans,w[b][i]),b=f[b][i];
    if(a==b) return ans;
    for(ll i=20;i>=0;i--)
    {
    	if(f[a][i]==f[b][i]) continue;
    	ans=max(ans,max(w[a][i],w[b][i]));
    	a=f[a][i],b=f[b][i];
 	}
    ans=max(ans,max(w[a][0],w[b][0]));
 	return ans;
}

ll lcat(ll a,ll b)
{
    if(d[a]>d[b]) swap(a,b);
    for(ll i=20;i>=0;i--)
    if(d[a]<=d[b]-(1<<i)) b=f[b][i];
    if(a==b) return a;
    for(ll i=20;i>=0;i--)
    {
    	if(f[a][i]==f[b][i]) continue;
    	a=f[a][i],b=f[b][i];
 	}
 	return f[a][0];
}

bool pd(ll a,ll b,ll c)
{
	ll x1=lcat(a,b);
	ll x2=lcat(a,c);
	ll x3=lcat(b,c);
	if(x1==x3&&x2==c) return 1;
	if(x1==x2&&x3==c) return 1;
	return 0;
}

int main()
{
	cnt=0;
    memset(head,-1,sizeof(head));
    memset(w,0,sizeof(w));
    memset(f,0,sizeof(f));
    memset(d,0,sizeof(d));
	scanf("%lld%lld",&n,&m);
    for(ll i=1;i<=n;i++) fa[i]=i;
    ll a,b;
    for(ll i=1;i<=m;i++) scanf("%lld",&p1[i]);
    for(ll i=1;i<=m;i++) scanf("%lld",&p2[i]);
    for(ll i=1;i<=m;i++)
    {
    	scanf("%lld%lld",&a,&b);
		t[i].u=a;
		t[i].v=b;
		t[i].w=p1[i];
		t[i].c=p2[i];
		t[i].num=i;
		t[i].sig=0;
	}
    sort(t+1,t+m+1,cmp);
    ll ans=0;
    ll cmin=inf;
    ll lastcmin=0;
    for(ll i=1;i<=m;i++)
    {
    	ll u=t[i].u;
    	ll v=t[i].v;
    	ll w=t[i].w;
    	ll c=t[i].c;
    	if(finds(u)==finds(v)) continue;
    	if(c<cmin) t[i].sig=2,t[lastcmin].sig=1,cmin=c,lastcmin=i;
    	else t[i].sig=1;
    	cmin=min(cmin,c);
    	ans+=w;
    	joins(u,v);
		adde(u,v,w);
		adde(v,u,w);
	}
    scanf("%lld",&k);
    ll pre=ans,r=0;
    ans-=k/cmin;
    dfs(1,0,0);
    for(ll i=1;i<=m;i++)
    {
    	ll u=t[i].u;
    	ll v=t[i].v;
    	ll w=t[i].w;
    	ll c=t[i].c;
    	if(t[i].sig) continue;
		if(c>=cmin) continue;
		ll tmp=pre+w-lca(u,v);
		tmp-=k/c;
		if(tmp<ans) r=i,ans=tmp;
	}
	printf("%lld\n",ans);
	if(!r)
	{
		for(ll i=1;i<=m;i++)
		{
			if(t[i].sig==1) printf("%lld %lld\n",t[i].num,t[i].w);
			if(t[i].sig==2) printf("%lld %lld\n",t[i].num,t[i].w-k/t[i].c);
		}
	}
	else
	{
		ll u=t[r].u;
		ll v=t[r].v;
		ll xw=lca(u,v);
		bool flag=1;
		for(ll i=1;i<=m;i++)
		{
			if(i==r) printf("%lld %lld\n",t[i].num,t[i].w-k/t[i].c);
			if(t[i].sig)
			{
				if(xw==t[i].w&&pd(u,v,t[i].u)&&pd(u,v,t[i].v)&&flag) {flag=0;continue;}
				printf("%lld %lld\n",t[i].num,t[i].w);
			}
		}
	}
	return 0;
}
```


---

## 作者：CDFLS_mao_zx (赞：2)

## CF733F

### 废话：

很久没写题解了，这道题比较水，来水一波题解。（居然没人写树链剖分？！）

### 题意：

给定一张无向图，边有边权，你可以使用不超过 $s$ 的代价降低一些边的边权，其中第 $i$ 条边降低 $\text{1}$ 边权的代价为 $c_i$ 。（边权可以为负数），你需要使得降低边权后的图的 $\text{MST}$ 边权和最小。

### 思路：

#### MST=最小生成树

结论一：我们必然会选降低了边权的边，这个是显然的，不然还不如不降。

结论二：一定只会降低一条边的边权，这个也是显然的，但以下给出证明：假设降低了多条边的边权，那么这些边都会选（参照第一个结论），那为什么我们不只降低它们中 $c_i$ 最小的那一条边来获得一个更优的 $\text{MST}$ 呢？

接下来怎么搞？枚举降低权值的边求 $\text{MST}$ ？，复杂度不对，但正确性显然。

其实我们发现它就相当于强制要求选定一条边，然后再求 $\text{MST}$ 。

熟悉一点的同学马上就可以知道只需要求出 $\text{MST}$ 再替换边就可以了，但是为什么这样是对的呢，下面将给出证明：

考虑 $\text{Kruscal}$ 的过程，如果一条边 $u,v$ 会使得最终的答案变小，实际上我们的要替换的边 $u,v$ 就是在排序的过程中在 $u,v$ 相连之前被考虑了进去，在选 $u,v$ 之前的所有边和原来的 $\text{MST}$ 是一致的，在选了 $u,v$ 之后，因为 $u,v$ 已经相连了，所以原来的 $\text{Kruscal}$ 过程中把 $u,v$ 连起来的最后一条边就不会被选择，但其他的边依然按顺序排列，所以还是会选择原先选择的边。

所以我们随便求出一颗 $\text{MST}$ ，然后考虑替换边，设替换的边是 $u,v$ 每次只需要求出 $\text{MST}$ 上路径 $u,v$ 上边权最大的边并删掉它替换成 $u,v$ 就可以了，这样的话保证了图还是一颗树。

这里可能还有一个问题，为什么随便一颗 $\text{MST}$ 都可以，因为任意一个 $\text{MST}$ 中，发挥连接最终两个固定的点 $u,v$ 的边的权值一定都是一样的，可以感性理解一下，所以 $u,v$ 路径上最大边的权值一定是一样的。

使用树链剖分维护树上路径边权最大的边。枚举每条边，如果是树边，直接扣掉权值，如果是非树边，扣掉权值后加进去，然后减掉路径 $u,v$ 上边权最大的边即可。

### 关于树链剖分 ：

其实这道题完全可以用树上倍增做，但主要是为了练一下码力，所以蒟蒻毅然选择了 4Kb 的树链剖分，细节将在代码中体现。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long//显然需要开long long 但我很懒
using namespace std;
inline void read(int &x)
{
	x=0;int f=1;
	char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	if(ch=='-'){f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
const int N=2e5+10;
int i,j,k,m,n,s,t,cnt;
struct fu{
	int next,p,val,c,u,v,rk;
    //val,c同题意
    //p记录该边是否在mst中
    //rk记录该边的原先编号
}a[N<<1];//双向边2倍
struct Tree{
	int max,rk;
}T[N<<2],val[N];//线段树4倍
int head[N],fa[N],tdv[N],tdc[N];
int rak[N],dfn[N],top[N],son[N],size[N],dep[N];
void work(int aa,int bb,int cc,int dd)
{
	a[++k].next=head[aa];
	head[aa]=k;
	a[k].v=bb;
	a[k].u=aa;
	a[k].val=cc;
	a[k].c=dd;
	a[k].rk=k;
}
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
bool cmp(fu aa,fu bb)
{
	if(aa.val!=bb.val)
	return aa.val<bb.val;
	return aa.rk<bb.rk;//为了防止一些奇奇怪怪的问题
}
bool cmp2(fu aa,fu bb)
{
	return aa.rk<bb.rk;
}
int kru()
{
	sort(a+1,a+k+1,cmp);
	int ret=0;
	int rt[N<<2];//因为进行了排序，所有head和next被打乱了，需要重新计算
	memset(rt,0,sizeof(rt));
	for(i=1;i<=k;i++)
	rt[a[i].rk]=i;
	for(i=1;i<=n;i++)
	head[i]=rt[head[i]];
	for(i=1;i<=k;i++)
	a[i].next=rt[a[i].next];
	for(i=1;i<=k;i+=2)
	{
		int u=find(a[i].u);int v=find(a[i].v);
		if(u==v)
		continue;
		ret+=a[i].val;
		fa[u]=v;
		a[i].p=a[i+1].p=1;
		cnt++;//Kruscal
	}
	for(i=1;i<=k;i++)
	a[i].rk=(a[i].rk-1)/2+1;//重算编号
	return ret;
}
void dfs1(int u)
{
	size[u]=1;
	for(int i=head[u];i;i=a[i].next)
	{
		int v=a[i].v;
		if(fa[u]==v||a[i].p==0)//非树边要忽略
		continue;
		fa[v]=u;
		val[v].max=a[i].val;//注意需要记录边的编号
		val[v].rk=a[i].rk;//我们用一个点的值代表连向它父亲的边的权值
		dep[v]=dep[u]+1;
		dfs1(v);
		size[u]+=size[v];
		if(size[v]>size[son[u]])
		son[u]=v;
	}
}
void dfs2(int u)
{
	dfn[u]=++t;rak[t]=u;
	if(son[fa[u]]==u)
	top[u]=top[fa[u]];
	else
	top[u]=u;
	if(son[u])
	dfs2(son[u]);
	for(int i=head[u];i;i=a[i].next)
	{
		int v=a[i].v;
		if(son[u]==v||a[i].p==0||fa[u]==v)
		continue;
		dfs2(v);
	}//树剖基础
}
Tree push_up(Tree aa,Tree bb)
{
	Tree ret;
	if(aa.max>bb.max)
	{
		ret.max=aa.max;
		ret.rk=aa.rk;
	}
	else
	{
		ret.max=bb.max;
		ret.rk=bb.rk;
	}
	return ret;//合并答案
}
void build(int l,int r,int rt)
{
	if(l==r)
	{
		T[rt]=val[rak[l]];
		return;
	}
	int mid=(l+r)/2;
	build(l,mid,rt<<1);
	build(mid+1,r,rt<<1|1);
	T[rt]=push_up(T[rt<<1],T[rt<<1|1]);
}
Tree quert(int l,int r,int rt,int x,int y)
{
	if(x<=l&&y>=r)
	return T[rt];
	Tree ret;ret.max=0;
	if(x>y)return ret; //记得退出，不然会死掉
	int mid=(l+r)/2;
	if(x<=mid)
	ret=quert(l,mid,rt<<1,x,y);
	if(y>mid)
	ret=push_up(quert(mid+1,r,rt<<1|1,x,y),ret);
	return ret;
}
Tree query(int u,int v)
{
	if(top[u]==top[v])
	{
		if(dep[u]>dep[v])//记得交换位置
		swap(u,v);
		return quert(1,n,1,dfn[u]+1,dfn[v]);//LCA不要算进去了，它不对答案贡献
	}
	if(dep[top[u]]<dep[top[v]])//树剖最容易出问题的地方之一（一定是top[u]和top[v]比深度）
	swap(u,v);
	Tree ret1,ret2;
	ret1=quert(1,n,1,dfn[top[u]],dfn[u]);//
	ret2=query(fa[top[u]],v);
	return push_up(ret1,ret2);
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//freopen(".ans","w",stdout);
	read(n),read(m);
	for(i=1;i<=m;i++)
	read(tdv[i]);
	for(i=1;i<=m;i++)
	read(tdc[i]);
	for(i=1;i<=m;i++)
	{
		int x,y;
		read(x),read(y);
		work(x,y,tdv[i],tdc[i]);
		work(y,x,tdv[i],tdc[i]);
	}
	read(s);
	for(i=1;i<=n;i++)
	fa[i]=i;
	int all=kru();
	memset(fa,0,sizeof(fa));
	dfs1(1);
	dfs2(1);
	build(1,n,1);
	int ans=all,max1=0,max2=0;
	{
		for(i=1;i<=k;i+=2)
		{
			if(a[i].p)
			{
				int tmp=all-s/a[i].c;
				if(ans>tmp)
				{
					ans=tmp;
					max1=max2=a[i].rk;
				}
				continue;
			}
			int u=a[i].u,v=a[i].v;
			Tree sum=query(u,v);
			int tmp=all+a[i].val-sum.max-s/a[i].c;
			if(tmp<ans)
			{
				max1=a[i].rk;
				max2=sum.rk;
				ans=tmp;
			}
		}
	}
	printf("%lld\n",ans);
	sort(a+1,a+k+1,cmp2);
	for(i=1;i<=k;i+=2)
	{
		if((a[i].p&&max2!=a[i].rk)||max1==a[i].rk)
		{
			printf("%d ",a[i].rk);
			int x=a[i].val;
			if(max1==a[i].rk)
			x-=s/a[i].c;
			printf("%d\n",x);
		}
	}
	return 0;
}
```



 



---

## 作者：xfrvq (赞：1)

[$\tt Link$](/problem/CF733F)。

**我们所有的代价只会用在一条边上**。因为如果代价被用在多个边上，那么找到其中 $c$ 最小的一条，代价全用在上面将会更优。

于是我们枚举每一条边作为这个 *特殊边*，计算出如果选用它将会带来的优惠 $v$。然后计算 **固定此边必选** 时的 **最小生成树总边权**，在结合优惠，看看总和是否更优。

固定一条边必选的 $\tt MST$ 是个经典问题。参照 [严格次小生成树](/problem/P4180)。

做法是考虑加入这一条边，设其 $\{x,y\}$，然后会形成一个环，我们删去环上的非 $\{x,y\}$ 的最大边。

好吧其实就是若干次链最大值询问。

这非常的平凡。树剖套 $\tt ST$ 表即可简单做到 $O(1)$。

但是这题要输出方案，属于是恶心。对应的 $\tt ST$ 表需要支持求最大值的位置。

整体其实并不算难，但我觉得不止 $\tt^\ast2200$ 。

```cpp
#import<stdio.h>
#import<vector>
#import<tuple>
#import<numeric>

using namespace std;

using ll = long long;

const int N = 2e5 + 5;

int n,m,s,tc[N],tw[N],pa[N];
ll res = 0;
vector<pair<int,int>> G[N];
pair<int,int> st[22][N];
int lg2[N];
int dep[N],siz[N],son[N],fa[N],wei[N];
int dfn[N],adfn[N],top[N],tot = 0;
tuple<int,int,int,int,int,bool> E[N];

int fnd(int i){ return i == pa[i] ? i : pa[i] = fnd(pa[i]); }

void dfs1(int u = 1,int ft = 0){
	dep[u] = dep[fa[u] = ft] + 1;
	siz[u] = 1;
	for(auto[v,w] : G[u]) if(v != ft){
		dfs1(v,u); wei[v] = w;
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}

void dfs2(int u = 1,int tp = 1){
	adfn[dfn[u] = ++tot] = u; top[u] = tp;
	if(son[u]) dfs2(son[u],tp);
	for(auto[v,w] : G[u]) if(!top[v]) dfs2(v,v);
}

void build(){
	for(int i = 2;i <= n;++i) lg2[i] = lg2[i >> 1] + 1;
	for(int i = 1;i <= n;++i) st[0][i] = make_pair(wei[adfn[i]],adfn[i]);
	for(int j = 1;(1 << j) <= n;++j)
		for(int i = 1;i + (1 << j) - 1 <= n;++i)
			st[j][i] = max(st[j - 1][i],st[j - 1][i + (1 << j - 1)]);
}

auto query(int l,int r){
	int k = lg2[r - l + 1];
	return max(st[k][l],st[k][r - (1 << k) + 1]);
}

auto qry(int x,int y){
	auto res = make_pair(0,0);
	while(top[x] != top[y]){
		if(dep[top[x]] < dep[top[y]]) swap(x,y);
		res = max(res,query(dfn[top[x]],dfn[x]));
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x,y);
	return max(res,query(dfn[x] + 1,dfn[y]));
}

void MST(){
	iota(pa,pa + n + 1,0);
	sort(E + 1,E + m + 1);
	for(int i = 1;i <= m;++i){
		auto&[w,u,v,c,I,f] = E[i];
		int fu = fnd(u),fv = fnd(v);
		if(fu == fv) continue;
		G[u].emplace_back(v,w);
		G[v].emplace_back(u,w);
		pa[fu] = fv; res += w; f = true;
	}
}

void solve(){
	ll ans = res; int id1,id2;
	for(int i = 1;i <= m;++i){
		auto[w,u,v,c,I,f] = E[i];
		auto[x,y] = qry(u,v);
		ll cur = res - (s / c);
		if(!f) cur += w - x;
		if(cur < ans){
			ans = cur,id1 = i;
			if(!f) id2 = y;
		}
	}
	printf("%lld\n",ans);
	for(int i = 1;i <= m;++i){
		auto[w,u,v,c,I,f] = E[i];
		if(i == id1) printf("%d %d\n",I,w - (s / c));
		else if(f){
			int p = fa[u] == v ? u : v;
			if(id2 != p) printf("%d %d\n",I,w);
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;++i) scanf("%d",tw + i);
	for(int i = 1;i <= m;++i) scanf("%d",tc + i);
	for(int i = 1;i <= m;++i){
		int a,b;
		scanf("%d%d",&a,&b);
		E[i] = make_tuple(tw[i],a,b,tc[i],i,false);
	}
	MST(); dfs1(); dfs2(); build();
	scanf("%d",&s); solve();
	return 0;
}
```

---

## 作者：Dita (赞：0)

## CF733F Drivers Dissatisfaction

> 给出一张 $n$ 个点 $m$ 条边的无向图，每条边 $(a_i,b_i)$ 有一个权值 $w_i$ 和费用 $c_i$表示这条边 每降低 $1$ 的权值需要 $c_i$ 的花费。现在一共有 $S$ 费用可以用来降低某些边的权值（可以降到负数），求图中的一棵权值和最小的生成树并输出方案

**solution**

因为可以减到负数，那么肯定就全部把钱花在一条边上（~~逮一条花费最少的狂减~~）

但这条边分两种情况

- 树边，肯定要找一个花费少的树边
- 非树边，就要从树上合法的边中找一条权值最大的中被它代替

合法的边：从这条边的两个端点向上找 $LCA$ ，两个点到 $LCA$ 路径上的所有边（因为你要保证替换完之后，还能和原来最小生成树上的边构成一棵树）

找 $LCA$ 的时候是在最小生成树上跑

**第一种情况：**

求最小生成树的时候顺便记录一个花费最小的边以及最小生成树的总权值，最后把钱都花在它上面就好了

**第二种情况：**

枚举每一条非树边，找出合法的权值最大的边来代替，看是否更优

**实现：** 用树剖解决第二种情况，维护链上权值最大的边

下面的代码在第75个点的时候wa个，忘dalao相救

（参考[Wans_ovo](https://www.cnblogs.com/wans-caesar-02111007/p/9911336.html)的AC代码：）

**code**

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lson rt << 1
#define rson rt << 1|1
#define int long long 
using namespace std;
const int M = 1e6 + 5;
int n, m, s;
int read(){
   int x = 0,f = 1;char c = getchar();
   while(c < '0'||c > '9'){if(c == '-')f = -1;c = getchar();}
   while(c >= '0'&&c <= '9'){x = x*10 + c - '0';c = getchar();}
   return f*x;
}
int fa[M], dep[M], siz[M], son[M];
int top[M], idw[M], idnum[M], dfn[M], jlw[M], jlnum[M];
//两个图，原图，和最小生成树 
struct edge{
    int u, v, w, num, vis, nxt;
}E[M], e[M]; 
bool cmp(edge a, edge b){return a.w < b.w;}
int head[M], Ecnt;
void add(int u, int v, int w, int num) {
    E[++Ecnt] = (edge) {u, v, w, num, 0, head[u]};
    head[u] = Ecnt;
}
int etot;
void add_inv(int u, int v, int w, int num) {
    e[++etot] = (edge) {u, v, w, num, 0, 0};
}

namespace Seg{
   struct Tree {
       int w, num;
         Tree operator + (const Tree &a) const {
            Tree c;
            if(a.w > w)    c.w = a.w, c.num = a.num;
            else        c.w = w, c.num = num;
            return c;
       }
   }tree[M];
   void update(int rt) {
        tree[rt] = tree[lson] + tree[rson];
   }
   void build(int rt, int l, int r) {
       if(l == r) {
           tree[rt].w = idw[l];
           tree[rt].num = idnum[l];
           return ;
        }
       int mid = (l + r) >> 1;
       build(lson, l, mid);    
	   build(rson, mid + 1, r);
       update(rt);
    }
   Tree query(int rt, int l, int r, int L, int R) {
       if(l >= L && r <= R)    return tree[rt];
       int mid = (l + r) >> 1; Tree ans;    
	     ans.w = -0x3f3f3f3f, ans.num = 0;
       if(L <= mid)ans = ans + query(lson, l, mid, L, R);
       if(R > mid)ans = ans + query(rson, mid + 1, r, L, R);
       return ans;
    }
}
namespace Cut{
	//大法师 1 
    void dfs(int u, int f) {
        fa[u] = f, dep[u] = dep[f] + 1, siz[u] = 1;
        for(int i = head[u]; i; i = E[i].nxt) {
            int v = E[i].v;
            if(v == f) continue;
            dfs(v, u);
            siz[u] += siz[v];
            if(siz[v] > siz[son[u]])    
		    son[u] = v, jlw[u] = E[i].w, jlnum[u] = E[i].num; 
        }
    }
    //大法师 2 (要记录每条边在原图中的信息)
	int cnt = 0;
    void dfs2(int u, int t, int w, int num) {
        top[u] = t, idw[++cnt] = w, idnum[cnt] = num, dfn[u] = cnt;//很容易以写错，要分清原图的标号还是刨完之后的编号 
        if(son[u])    dfs2(son[u], t, jlw[u], jlw[u]);
        for(int i = head[u]; i; i = E[i].nxt) {
            int v = E[i].v;
            if(v == fa[u] || v == son[u]) continue;
            dfs2(v, v, E[i].w, E[i].num);
        }
    }
   Seg::Tree query(int u, int v) {
        Seg::Tree ans; 
		ans.w = -0x3f3f3f3f, ans.num = 0;
        while(top[u] != top[v]) {
             if(dep[top[u]] < dep[top[v]])    swap(u, v);
             ans = ans + Seg::query(1, 1, n, dfn[top[u]], dfn[u]);
             u = fa[top[u]];
        }
        if(dep[u] < dep[v])    swap(u, v);
        ans = ans + Seg::query(1, 1, n, dfn[v] + 1, dfn[u]);
        return ans;
    }
}
//并查集 
int f[M];
int find(int x) {return f[x] == x ? x : f[x] = find(f[x]); }
int w[M], c[M] = {0x3f3f3f3f}, tot, ans1, ans2;
void Kruskal() {
    sort(e + 1, e + 1 + m, cmp);
    for(int i = 1; i <= n; i ++)    f[i] = i;
    for(int i = 1; i <= m; i ++) {
        int u = e[i].u, v = e[i].v, num = e[i].num;
        int x = find(u), y = find(v);
        if(x != y) {
            e[i].vis = 1;//树边 
            f[x] = y;
            add(u, v, w[num], num);    add(v, u, w[num], num);
            tot += w[num];
            if(c[num] < c[ans1])    ans1 = num;//统计树上的最小花费边的编号 
        }
    }
}

signed main() {
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
    n = read(), m = read();
    for(int i = 1; i <= m; i ++) w[i] = read();
    for(int i = 1; i <= m; i ++) c[i] = read();
    for(int i = 1; i <= m; i ++) {
        int u, v;
        u = read(), v = read();
        add_inv(u, v, w[i], i);
    }
    s = read();
    Kruskal();    
	ans2 = tot - s / c[ans1];
    Cut::dfs(1, 0);    
	Cut::dfs2(1, 0, -0x3f3f3f3f, 0);    
	Seg::build(1, 1, n);
    int flag = 0;
    for(int i = 1; i <= m; i ++) {
        if(!e[i].vis) {
            int u = e[i].u, v = e[i].v, num = e[i].num;
            Seg::Tree a = Cut::query(u, v);
            int tmp = tot - a.w + w[num] - s / c[num];
            if(tmp < ans2)    ans1 = num, ans2 = tmp, flag = a.num;
        }
    }
    printf("%lld\n", ans2);
    for(int i = 1; i <= m; i ++) {
        int num = e[i].num;
        if(ans1 == num) {
            printf("%lld %lld\n", num, w[num] - s / c[num]);//减少权值的边     
        } 
		else if(e[i].vis) {
            if(flag != num) {//其他的树边 
                printf("%lld %lld\n", num, w[num]);
            }
        }
    }
    return 0;
}
```

---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF733F)

# 题解

**我们应该明白的第一件事——所有的花费只会全部花在一条边上**，这是这道题的基础 ~~虽然我知道也没第一时间做出来~~

下文称这条边为“$JZM$”.

然后，随便找一个 $MST$，然后我们对于这条 $JZM$ 应该会出现在哪里分类讨论：

1. 出现在树边上，显然 $JZM$ 应该是 $c$ 最小的那条边，只有这样才能最大地减少整棵树的花费；
2. 出现在非树边上，对于一条边 $(u,v)$，如果我们要选择它成为 $JZM$，无疑会破坏树结构，考虑在 $u,v$ 树上路径去掉一条边以维持树结构，显然去掉的边应该是权值最大的，然后，我们再全部把花费砸在我们加进来这条边，和答案进行比较即可；

由于答案要输出具体方案，需要保存哪条边是 $JZM$.

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13553032.html
```



---


# Session in BSU

## 题目描述

Polycarp 就读于 Berland State University。很快他就要参加考试了。他需要通过恰好 $n$ 门考试。

对于每门考试 $i$，有两个已知的日期：$a_i$ —— 第一次可以参加该考试的日期，$b_i$ —— 第二次可以参加该考试的日期（$a_i < b_i$）。Polycarp 每天最多只能参加一门考试。对于每门考试，Polycarp 可以自行选择在哪一天参加。他必须通过所有 $n$ 门考试。

Polycarp 希望尽早通过所有考试。请输出 Polycarp 能够通过所有 $n$ 门考试的最早日期的最小编号。如果他无法通过所有考试，则输出 $-1$。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
1 5
1 7
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3
5 13
1 5
1 7
```

### 输出

```
7
```

## 样例 #3

### 输入

```
3
10 40
40 80
10 80
```

### 输出

```
80
```

## 样例 #4

### 输入

```
3
99 100
99 100
99 100
```

### 输出

```
-1
```

# 题解

## 作者：大菜鸡fks (赞：11)

1、如果边数等于点数 即为一个基环树，那么明显 这个连通块的最后时间为 权值最大的点

2、如果边数小于点数 即为一个树，那么连通块的最后时间为 权值次大的点

3、如果边数大于点数 那么就冲突了， 输出-1就好了

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=2e6+5;
int n,tot,head[N],a[N],b[N],num[N],cnt;
struct edge{
	int link,next;
}e[N];
inline void init(){
	n=read();
	for (int i=1;i<=n;i++){
		a[i]=read(); b[i]=read();
		num[++cnt]=a[i]; num[++cnt]=b[i];
	}
	sort(num+1,num+1+cnt);
	cnt=unique(num+1,num+1+cnt)-num-1;
}
inline void add_edge(int u,int v){
	e[++tot]=(edge){v,head[u]}; head[u]=tot;
}
inline void insert(int u,int v){
	add_edge(u,v); add_edge(v,u);
}
bool vis[N];
int ans,ed,sz,mx1,mx2;
void dfs(int u){
	if (vis[u]) return;
	if (u>mx1) mx2=mx1,mx1=u;
		else if (u>mx2) mx2=u;
	vis[u]=1; sz++;
	for (int i=head[u];i;i=e[i].next){
		ed++; dfs(e[i].link);
	}
}
inline void solve(){
	for (int i=1;i<=n;i++){
		a[i]=lower_bound(num+1,num+1+cnt,a[i])-num;
		b[i]=lower_bound(num+1,num+1+cnt,b[i])-num;
		insert(a[i],b[i]);
	}
	ans=0;
	for (int i=cnt;i;i--){
		if (!vis[i]){
			mx2=mx1=sz=ed=0;
			dfs(i);
			if (ed/2>sz) {
				puts("-1"); return;
			}else{
				if (ed/2==sz) ans=max(ans,mx1);
					else ans=max(ans,mx2);
			}
		}
	}
	writeln(num[ans]);
}
int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：ModestCoder_ (赞：10)

这题我用并查集过了

看到范围1e9，所以先离散。然后每次把点对应的两个时间用并查集连条边

对于每个点的两个时间，分类讨论

 - 两个时间都没选，暂时选小的那个，并用并查集把两个时间连起来
 - 有一个选了，那么这次选剩下的那个，然后把这两个时间删掉（就是在并查集里把他们的祖先设置为0）
 - 都选过了（表现为两个时间的祖先都为0），那么直接输出-1得了

为什么这题用并查集就搞定了呢，并查集的连边操作的意义是什么？

其实感性理解一下就行了

以 $(1,5)(1,7)(5,13)$为例

对于第一个任务，我先选了1，把1与5连起来，并且5是1的祖先；

对于第二个任务，我的待选时间就变为了$(5,7)$，那么我选5的意义是：对于第一个任务选1的操作反悔，改选5，然后我在第二个任务的时候选择了1

这就是并查集在这里的用处

具体实现在代码更好

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 1000010
using namespace std;
struct node{
	int id, x, v;
}a[maxn << 1];
int n, ans, num[maxn << 1], f[maxn << 1], p;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

bool cmp1(node x, node y){ return x.x < y.x; }
bool cmp2(node x, node y){ return x.id == y.id ? x.v < y.v : x.id < y.id; }
int get(int k){ return k == f[k] ? k : f[k] = get(f[k]); }

int main(){
	n = read();
	for (int i = 1; i <= n; ++i) a[(i << 1) - 1].x = read(), a[i << 1].x = read(), a[(i << 1) - 1].id = a[i << 1].id = i;
	sort(a + 1, a + 1 + (n << 1), cmp1);
	a[0].x = a[1].x + 1;
	for (int i = 1; i <= (n << 1); ++i) a[i].v = a[i].x == a[i - 1].x ? p : ++p, num[a[i].v] = a[i].x;
	sort(a + 1, a + 1 + (n << 1), cmp2);
	for (int i = 1; i <= p; ++i) f[i] = i;
	for (int i = 1; i <= n; ++i){
		int s1 = get(a[(i << 1) - 1].v), s2 = get(a[i << 1].v);
		if (!s1 && !s2){ puts("-1"); return 0; }
		if (s1 == s2 || !s1 || !s2){ ans = max(ans, max(num[s1], num[s2])); f[s1] = f[s2] = 0; } else{
			if (s1 > s2) swap(s1, s2);
			ans = max(ans, num[s1]); f[s1] = s2;
		}
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：hsfzLZH1 (赞：6)

## 题目大意

[$KesdiaelKen$](https://www.luogu.org/space/show?uid=32275)大佬要实现他的$AK$计划。有$n$道题等着他做，第$i$题只有两个$AC$时间，$a_i$或$b_i$。错过了这两个$AC$时间，他就不能$AK$虐全场了。但是他在一个时间段里只能做至多一道题。现在请你告诉他，他最早能在哪个时刻$AK$虐全场。如果不能，输出$-1$。（$1\le n\le 10^6,1\le a_i<b_i\le 10^9$）

## 解法

最直接的想法自然是离散化$a,b$，每道题建一个点，每个$AC$时刻建一个点，从题目向$AC$时刻连一条边，然后跑二分图完美匹配/二分最大流。（没学过二分图/网络流的当我没说）

观察此题的数据范围，$10^6$远远超出了二分图/网络流可以承受的范围。需要寻找更优的做法。

假设我们已经建好了图。现在我们发现，这样的图可能是多个联通块组成的。而联通块之间并没有影响关系。于是我们可以用$dfs$计算处每个联通块的状态，分类讨论，最后对每个联通块的答案（计算出的最小时间）取最大值，即为所求。

对于每个联通块的情况，分类讨论如下：

若该联通块的边数大于点数，由于每个边都对应一种决策，此时一定无解，输出$-1$；

若该联通块的**边数**小于**点数**，因为这个块连通，所以这一定是棵树。其中所有的节点都会被选到，取该连通块的**最大值**。

若该联通块的边数等于点数，这就是一个基环树。考虑这样一种分配方案。以连通块中最大值所在的点为根进行$dfs$。每个点和它的父亲所连的边即为所选择的方案。也就是说，此时取该联通块的**次大值**。

所以，我们在找到一个联通块之后，进行一个$dfs$，求出该联通块的点数，边数，最大值和次大值。我们就可以在$O(n)$的时间复杂度内愉快地求出答案啦！

## 代码展示
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
using namespace std;
const int maxn=1000010;
int st[maxn*2],current,id[maxn*2];
int n,a[maxn],b[maxn],cur,cnt,h[maxn*3],nxt[maxn*6],p[maxn*6],ans,idx,cc[maxn*3],nodes,edges,max1,max2;
map<int,int>mp;
inline void add_edge(int x,int y)
{
    cur++;nxt[cur]=h[x];h[x]=cur;p[cur]=y;
}
void dfs(int x)
{
    //printf("%d\n",x);
    nodes++;
    cc[x]=idx;
    for(int j=h[x];j;j=nxt[j])
    {
        edges++;
        if(!cc[p[j]])
        {
            dfs(p[j]);
            if(p[j]>n)
            {
                if(p[j]-n>max1)max2=max1,max1=p[j]-n;
                else if(p[j]-n>max2)max2=p[j]-n;
            }
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d%d",a+i,b+i),st[++current]=a[i],st[++current]=b[i];
    sort(st+1,st+current+1);
    for(int i=1;i<=current;i++)if(st[i]!=st[i-1])id[++cnt]=st[i],mp[st[i]]=cnt;
    for(int i=1;i<=n;i++)a[i]=mp[a[i]]+n,b[i]=mp[b[i]]+n;
    for(int i=1;i<=n;i++)add_edge(i,a[i]),add_edge(i,b[i]),add_edge(a[i],i),add_edge(b[i],i);//printf("%d %d\n%d %d\n",i,a[i],i,b[i]);
    for(int i=1;i<=n+cnt;i++)if(!cc[i])
    {
        nodes=edges=0;
        max1=max2=-1;
        idx++;
        dfs(i);
        //printf("\n");
        edges/=2;
        if(nodes<edges){printf("-1\n");return 0;}
        if(nodes==edges)ans=max(ans,max1);
        if(nodes>edges)ans=max(ans,max2);
    }
    //printf("%d %d\n",cur,ans);
    printf("%d\n",id[ans]);
    return 0;
}
```

---

## 作者：OIerAlbedo (赞：2)

# 前言
看到题解里都是用并查集什么，用DP的我来水一发题解。
# 基本思路
题目中要我们选时间，但是是选时间点，不是时间段，所以我们可以考虑离散化，这样后面比较好处理。然后进行连边，一条边上至少要选一个点，我们可以发现，连好边之后如果环内有环，那么是一定无解的，因为一个环上的点是一定要选的，环内有环就导致一边无法满足要求。判断好有无解之后，就是DP时间了。
# DP思路
我们定义 ：

$ f_{x,1} $ ---- $ x $ 与他的子节点中最大的时间点（不包括环）。

$ g_{x,1} $ ----不选 $ x $ 这个时间点可以达到的最优解。

$ g_{x,0} $ ----以 $ x $ 这个节点为根的子树所能达到的最优解。

不难发现 $ g_{x,1}=\max(f_{son[x],1}) $ ,因为 $ x $ 不选，下面的点就必须全部选才能满足要求。

而对于 $ g_{x,0} $ 则有点复杂。

$$
g_{x,0}=\min(\max(x,g_{son[x],0}),f_{son[x],1}) 
$$

上文的 $ f_{son[x],1} $ 就是 $ x $ 不选的情况， $ \max(x,g_{son[x],0}) $ 则是选了 $ x $ 那下面的点就可以不选。

然后对于环上的点 $ ans =\max(ans,f_{x,1}) $ ,因为环上的点必须都用于环上，对于非环的点 $ ans=\max(ans,g_{x,0}) $ ，具体实现可能有些不同。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int e3[2100000],e2[2100000],e1[2100000],f[2100000][3],a[2100000],b[2100000],d[2100000],de[2100000],f2[4000000],g[2100000][3];
int l,r,mid,w,ww,n,cnt,ans1,ans2,sum,i,t;
bool o[2100000],ll[2100000],u[2100000];
inline int read()			
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
void add(int x,int y)
{
    cnt++;a[cnt]=y;b[cnt]=d[x];d[x]=cnt;
}
void sc(int x,int fa)
{
    if (o[x]) return;o[x]=true;
    f[x][1]=x;
    int ans1=0,ans2=0,anss=0,ans=x;
    for (int i=d[x];i;i=b[i])
       if (a[i]!=fa)
          if (ll[a[i]]==false)
           {
           sc(a[i],x);
           if (f[a[i]][1]>ans1)
                {
                ans2=ans1;
               ans1=f[a[i]][1];anss=a[i];
                }
        else if ((f[a[i]][1]>ans2)) ans2=f[a[i]][1];
        if (f[a[i]][1]>ans) ans=f[a[i]][1];
           }
   f[x][1]=max(f[x][1],ans);f[x][0]=ans1;
   g[x][1]=f[x][1];
   int xx=ans2;
   int yy=min(max(x,g[anss][0]),f[anss][1]);
  xx=max(xx,yy);
  g[x][0]=xx;
}
int main()
{
    n=read();
    for (i=1;i<=n;i++)
         {
             e1[i]=read();e2[i]=read();
             w++;e3[w]=e1[i];w++;e3[w]=e2[i];
         }
    sort(e3+1,e3+1+w);ww=0;
    for (i=1;i<=w;i++)
        if (e3[i]!=e3[i-1])
            {
                ww++;e3[ww]=e3[i];
            }
    w=ww;
    for (i=1;i<=n;i++)
         {
             l=1;r=w;ans1=0;
             while (l<=r)
                  {
                      mid=(l+r)/2;
                      if (e3[mid]==e1[i])
                          {
                              ans1=mid;break;
                          }
                    else if (e3[mid]>e1[i]) r=mid-1;
                    else l=mid+1;
                  }
            l=1;r=w;ans2=0;
             while (l<=r)
                  {
                      mid=(l+r)/2;
                      if (e3[mid]==e2[i])
                          {
                              ans2=mid;break;
                          }
                    else if (e3[mid]>e2[i]) r=mid-1;
                    else l=mid+1;
                  }
        e1[i]=ans1;e2[i]=ans2;
        add(ans1,ans2);add(ans2,ans1);
        de[ans1]++;de[ans2]++;
         }
    n=w;w=0;t=1;
     for (i=1;i<=n;i++)
                 if (de[i]==1)
                     {
                     w++;f2[w]=i;
                     }
            while (t<=w)
                {
                if (u[f2[t]]) continue;u[f2[t]]=true;de[f2[t]]--;
                for (i=d[f2[t]];i;i=b[i])
                         {
                         de[a[i]]--;
                         if (de[a[i]]==1)
                             {
                             w++;f2[w]=a[i];
                             }
                         }
                t++; 
                }
    for (i=1;i<=n;i++)
        if (de[i]==2)
            {
            ll[i]=true;
            }
    else if (de[i]>2)   
           {
               printf("-1");
               return 0;
           }
    sum=0;
    for (i=1;i<=n;i++)
        if (ll[i]==true)
           {
               sc(i,0);sum=max(sum,i);
               sum=max(sum,g[i][1]);
           }
   for (i=1;i<=n;i++)
         if (o[i]==false)
             {
             sc(i,0); sum=max(sum,i);
        sum=max(sum,g[i][0]);
          }
    printf("%d\n",e3[sum]);
    return 0;
}
```
## 题外话
其实聪明人应该看出来了，对于有环的联通块，答案为所有值的最大值，无环的点，答案为次大值，只是我做烦了，这是个"伪DP"。

---

## 作者：chenxia25 (赞：2)

~~额朋友们好 这篇题解是来讲卡常的 因为这是一只线对的菜鸡~~

第一眼看到就知道可以二分答案 + 判二分图完美匹配，但是网络流跑不过去。那就考虑 Hall 定理。

如果有两天都选不了的就滚蛋。如果只能选一天，那就强制选，然后会导致连锁反应——一些其他人也必须强制选，就递归实现即可，如果有无法搞的就滚蛋。剩下来的都是可以选两天的，于是把人放左边，天放右边连二分图。应用 Hall 定理，对于任意左部子集，如果连过去之后不连通，显然可以拆成若干个连通的子条件，不需要考虑。所以只要考虑连通的情况。

选一个人要把连的两天都带上，这个「两」不难想到把人看成边，连两天，那么就是不能存在一个边集使得它的导出子图包含点数要小于边数。于是就建个图再说啦。由于是连通的，有 $|E|\geq|V|-1$（这就是仅考虑连通情况的好处），要满足 $|E|\leq|V|$，只有 $|E|=|V|-1$ 或 $|E|=|V|$，分别等价于树和基环树。然后不难发现，一个连通块的所有边导出子图都是树或基环树，和该连通块是树或基环树是等价的。那就跑出所有连通块然后看是否树或基环树，等价于判断是否有 $|E|\leq|V|$。

这样是线对的。然后考虑到一开始递归处理只能选一天的情况有点难写，可以强行加到最终的结论上，就是选一个点的话就可以选对应的只能选它的所有人，就建若干个自环即可。

看到题解区基本全是线性的，我不禁自惭形秽。~~但是图论题总不可能出到 1e7 吧？那不出到 1e7 的话线性和线对不是一样的吗？~~ 然后真就 T 掉了，懒得改前向星干脆直接上路径压缩 + 启发式双优化并查集，虽说是 $\mathrm O(n\alpha(n)\log n)$，但常数比 `vector` + 递归要小好多了。~~最终以 3900+ms A 掉了，~~**_[code](https://www.luogu.com.cn/paste/cxwaeyh5)_**。

---

## 作者：LXH5514 (赞：1)

## CF1027F Session in BSU

### 题目大意

有n场考试，每场考试你有两个时间点$a_i,b_i$可以考，你可以选择一天去考，然后经过你的合理安排，你需要将这n场考试都考掉，并且求出最少要多少太天才能考完，即考完的最后一天，如果无法做到将所有考试考完，那么就输出-1。over

### 备注

部分参考[**ModestCoder_**](https://www.luogu.com.cn/user/51719)

### 思路

这题一开始做的时候，很容易就想到要将时间用重复的考试一起处理，因为这些考试是会互相关联和牵制影响，而对于独立的考试直接在较早的一天考就行。

我们再来考虑如何一起处理互相牵制的考试，对于这种有同种性质的一个个团体就会想到用并查集。但当你一开始口糊的时候，你可能会觉得有一些东西无法处理，我这只蒟蒻也是。

比如当加进来一个数，我们需要判断这场考试的两个时间是否已经选择，因为在并查集里的数不一定被选择，等一系列问题。

这时候我们就可以来考虑一下我们这个并查集的性质：

1. 加进来的考试中至少有一个时间已经在并查集中出现过了。

2. 由 $1$ 可得每次加进并查集里最多只有一个数。

3. 每场考试加进来，就必定有一个时间点会被选择。

4. 由 $2，3$ 可得并查集里最多只会有一个数没被选择。

5. 并查集只能查询祖先，不能查询这个祖先有哪些儿子。

6. 由 $4，5$ 可得我们需要将这个没选择的当做祖先，而由于我们需要最优，所以肯定是相对来说时间较靠后的那个。

以上就是我认为的一些细节。

我们接下考虑如何处理答案，将考试分个类：

1. 两个时间点都没被选过，就这时两个数都是祖先，那么就选小的那个，将小的并到大的那个，大的当祖先，这是肯定是局部最优，这是有人会说，那他不一定是全局最优啊，没事放心，后面会调整的。

2. 有一个时间点被选过，一个没选过（其实不一定没被选过），即祖先不同，我们只要将选过的那个的祖先（由上述的6性质可知这一定没被选过）和另一个没选过的像1一样合并就行。这里要解释一下为什么祖先，因为我也理解了半天。虽然被选过的这个时间点和祖先不一定有直接关系，但一定可以通过一定的关系联系起来，因为并查集合并的时候就有点像连边操作，如果把这个并查集想象成一个图，那么就是相当于在一张联通图里面加一个点，那么任意两个点肯定还是互通的。举个栗子：

 ```cpp
4
1 2
2 3
3 4
1 5
 ```

​      当我们要连 $1$ 和 $5$ 时，图是这样的：

![img](https://cdn.luogu.com.cn/upload/image_hosting/vej8wg8n.png)

然后连完 $1$ 和 $5$ 后：

![img](https://cdn.luogu.com.cn/upload/image_hosting/kvn2xnnn.png)

而实际上是这样的， $4$ 和 $5$ 比较之后肯定选 $5$，看上去只是将 $4$ 连向 $5$ 。但其实是从原本的第一场考试 $1$ 考，第二场考试 $2$ 考，第三场考试在 $3$ 考，变成了第一场考试在 $2$ 考，第二场考试在 $3$ 考，第三场考试在 $4$ 考，第四场考试在 $1$ 考。因此一定可以通过某种路径将这两个点联系在一起。

3. 如果两个时间点都同一并查集里，那么此时一定选他们的祖先，这时这个并查集就废了，他已经没有一个点没被选了，因此我们将他的祖先连向一个空节点 $0$ 即可，

4. 如果说一场考试它考试的两个时间相同，那也就是说这场考试一定得在这天考，那么合并完后（合不合并无所谓），这个并查集肯定就废了。

5. 如果考试有一个时间在废的并查集里，那么将另一个点加进去的时候，这个并查集的还是废的。

6. 如果两个是时间点都在废的的并查集里，那么肯定就无法满足，输出-1，应该很好理解。

   ```cpp
   #include<iostream>
   #include<stdio.h>
   #include<algorithm>
   using namespace std;
   int read()
   {
   	int x=0,f=1;
   	char c=getchar();
   	while(c<'0'||c>'9'){
   		if(c=='-')f=-1;
   		c=getchar();
   	}
   	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+f*(c-'0'),c=getchar();
   	return x;
   }
   
   const int MAXN=1e6+10;
   int n,m;
   int a[MAXN],b[MAXN];
   int f[MAXN*2];
   int ans;
   int d[MAXN*2];
   int get(int x)
   {
   	if(f[x]==x)return x;
   	return f[x]=get(f[x]);
   }
   int main()
   {
   	n=read();
   	for(int i=1;i<=n;i++)
   	a[i]=read(),b[i]=read();
   	for(int i=1;i<=n;i++)
   	d[i*2-1]=a[i],d[i*2]=b[i];
   	sort(d+1,d+1+2*n);
   	m=unique(d+1,d+1+2*n)-d-1;
   	for(int i=1;i<=n;i++)
   	{
   		a[i]=lower_bound(d+1,d+1+m,a[i])-d;
   		b[i]=lower_bound(d+1,d+1+m,b[i])-d;
   	}//离散化 
   	for(int i=1;i<=n;i++)
   	f[a[i]]=a[i],f[b[i]]=b[i];
   	for(int i=1;i<=n;i++)
   	{
   	int x,y;
   	x=get(a[i]);
   	y=get(b[i]);
   	if(x==0&&y==0)
   	{
   		printf("-1\n");
   		return 0;
   	 }//类型6 
   	if(x==y||x==0||y==0)
   	{
   		ans=max(ans,max(d[x],d[y]));
   		f[x]=f[y]=0;//类型3，4，5 
   	}else{
   		if(x>y)swap(x,y);//选小的，因此将大的当根 
   		f[x]=y;
   		ans=max(ans,d[x]);//类型1，2 
   	}
   	}printf("%d\n",ans);
    	return 0;
   }
   
   ```

   

---


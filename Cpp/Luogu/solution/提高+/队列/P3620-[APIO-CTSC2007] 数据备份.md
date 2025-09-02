# [APIO/CTSC2007] 数据备份

## 题目描述

你在一家 IT 公司为大型写字楼或办公楼的计算机数据做备份。然而数据备份的工作是枯燥乏味的，因此你想设计一个系统让不同的办公楼彼此之间互相备份，而你则坐在家中尽享计算机游戏的乐趣。

已知办公楼都位于同一条街上。你决定给这些办公楼配对（两个一组）。每一对办公楼可以通过在这两个建筑物之间铺设网络电缆使得它们可以互相备份。

然而，网络电缆的费用很高。当地电信公司仅能为你提供 $K$ 条网络电缆，这意味着你仅能为 $K$ 对办公楼（或总计 $2K$ 个办公楼）安排备份。任一个办公楼都属于唯一的配对组（换句话说，这 $2K$ 个办公楼一定是相异的）。

此外，电信公司需按网络电缆的长度（公里数）收费。因而，你需要选择这 $K$ 对办公楼使得电缆的总长度尽可能短。换句话说，你需要选择这 $K$ 对办公楼，使得每一对办公楼之间的距离之和（总距离）尽可能小。

下面给出一个示例，假定你有 $5$ 个客户，其办公楼都在一条街上，如下图所示。这 $5$ 个办公楼分别位于距离大街起点 $1\rm km$, $3\rm km$, $4\rm km$, $6\rm km$ 和 $12\rm km$ 处。电信公司仅为你提供 $K=2$ 条电缆。

  ![](https://cdn.luogu.com.cn/upload/pic/4386.png) 

上例中最好的配对方案是将第 $1$ 个和第 $2$ 个办公楼相连，第 $3$ 个和第 $4$ 个办公楼相连。这样可按要求使用 $K=2$ 条电缆。第 $1$ 条电缆的长度是 $\rm 3km-1km = 2km$，第 2 条电缆的长度是 $\rm 6km―4km = 2 km$。这种配对方案需要总长 $4\rm km$ 的网络电缆，满足距离之和最小的要求。

## 说明/提示

$30\%$ 的输入数据满足 $N\leq 20$。

$60\%$ 的输入数据满足 $N\leq 10^4$。

## 样例 #1

### 输入

```
5 2 
1 
3 
4 
6 
12 ```

### 输出

```
4```

# 题解

## 作者：3493441984zz (赞：169)

# 题外话：

题解好像没有图，发个有图的，希望能帮助你们更好的理解

------------
# 思路：

其实就是一个贪心吧，见的挺多的，一开始做的话很难想到这个反悔机制

### 转化问题

我们把每相邻两个办公楼之间的距离算出来，抽象出来点，也就是有$n-1$个点，第$i$个点的点权表示第$i$栋楼与第$i+1$栋楼的距离

那么，当我们选了第$i$个点时，我们就不能再选$i-1,i+1$这两个点了，为什么呢？因为选了第$i$个点的话，就不能再有电缆连接第$i$和第$i+1$栋楼了，而选$i-1,i+1$这两个点的话，又会连接一下第$i$或第$i+1$栋楼，不符合题意。

那么这样做了之后，题目就变为，给定$n-1$个点，要你选出$k$个点，并且这$k$个点两两不相邻（如果没看懂请重复看上面这段话）

那么问题转化了之后呢？？？
### 我们先来看一个**错误的思路**：

我们弄一个小根堆（本蒟蒻用的优先队列代替）

把每一个点放进去，然后每次贪心取最小值，取了一个点后就把相邻的点标记为不能取

如果你认为这是对的话，就看看下面这个样例（楼层$5$个，要连接电缆数$2$个）：

![](https://i.loli.net/2019/02/15/5c665076ca5c9.png)

长方形是楼层，圆形是抽象出来的点，那么如果按照上面的思路的话，我们会先取$1$，也就是下图：

![](https://i.loli.net/2019/02/15/5c6650ee1e7a5.png)

那么我们就只能取$9$了，答案就是$10$，可是，这是最优的吗？？

我们用肉眼都能看出来选择$2,2$更优,那么我们就要增添一个反悔机制：

当我们取了一个点后，我们要再加入一个点，这个点的权值为左边的点权$+$右边的点权$-$自身的点权,为什么这样就能反悔了呢？？

我们边模拟边解释：

当我们取了$1$点后，把两个$2$标记为访问过,并且更新$1$节点的左右，$1$节点左边已经空了，右边则是$9$节点，然后在$1$节点位置加入一个点权为$2+2-1$的点

如下图：

![](https://i.loli.net/2019/02/15/5c66533adaef9.png)

那么优先队列下一个点为$2$，而$2$被访问过了，直接下一个点，下一个点还是$2$，而$2$也被访问过了，再下一个点，下一个点为$3$，把与它相邻的$9$标记为访问过，而且现在已经取了$2$个点了（本样例题目规定了安装$2$条电缆）所以更新$ans$，并且退出

最后如下图：

![](https://i.loli.net/2019/02/15/5c6653fc4c443.png)

看出来了吗？其实这就相当于我们取了$2,2$两个点，为什么呢？$ans=1+3$,也等于$2+2$呀，还记得$3$怎么来的吗？$3=2+2-1$，那么代回去就是

$4=1+3=1+2+2-1=2+2$

也就是说取了$3$这个点，就相当于没有取$1$这个点，而是取了$2,2$这两个点

你看懂了这个反悔机制吗$qwq$

至于左右节点的更新，我们用双向链表实现：


------------
接下来是美滋滋的代码时间~~~

~~~cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define N 500007
#define inf 0x3f3f3f3f
using namespace std;
struct Place
{
	int val,l,r;
}p[N];
struct Node
{
	int val,id;
	bool operator <(Node it) const
	{
		return val>it.val;
	} 
};
int n,m,ans,last;
bool vis[N];
priority_queue<Node> q;
void Del(int x)
{
	p[x].l=p[p[x].l].l;
	p[x].r=p[p[x].r].r;
	p[p[x].l].r=x;
	p[p[x].r].l=x;
}
int main()
{
	scanf("%d%d%d",&n,&m,&last);
	for(int i=1;i<n;++i)
	{
		int in;
		scanf("%d",&in);
		p[i].val=in-last;
		last=in;
		p[i].l=i-1;
		p[i].r=i+1;
		q.push((Node){p[i].val,i});
	}
	p[0].val=p[n].val=inf;//注意这里 
	for(int i=1;i<=m;++i)
	{
		while(vis[q.top().id])
			q.pop();
		Node now=q.top();
		q.pop();
		ans+=now.val;
		vis[p[now.id].l]=vis[p[now.id].r]=1;
		p[now.id].val=p[p[now.id].l].val+p[p[now.id].r].val-p[now.id].val;
		q.push((Node){p[now.id].val,now.id});
		Del(now.id);
	}
	printf("%d",ans);
	return 0;
}
~~~

---

## 作者：基地A_I (赞：59)

[博客园食用地址](https://www.cnblogs.com/BaseAI/p/12119618.html)

## Problem

[Luogu 题目地址](https://www.luogu.com.cn/problem/P3620)

[ACwing 题目地址](https://www.acwing.com/problem/content/149/)

## Sulotion

代码短，思维强，实现妙（就算猜出性质也不一定会实现），神仙题啊，科科（我太菜了而已）。

----

- 首先有一个显然的性质：选出来的这 $k$ 对点一定相邻。

根据这个性质，我们做第一步问题转换：记两个点 $i$ 和 $i+1$ 之间的距离为 $D_i$，那么我们就得到一个长度为 $n-1$ 的数组 $D$，我们要在 $D$ 中选出 $k$ 个数，并且这 $k$ 个数两两不能相邻。

----

（~~做到这里就不会了是吧？~~）既然没有什么头绪，我们就从 $k=1$ 的情况逐步推起，考虑像 [[算进]序列](https://www.acwing.com/problem/content/148/) （就是上一题，虽然这两题看起来毫无联系的样子）一样用**数学归纳法**解决问题。

- $k=1$

显然我们要选 $\min\{D_i\}$，并且记这个数为 $D_m$。

- $k=2$

显然决策集合只有两个部分：1.选 $D_m + D_{m'}$ （$D_{m'}$ 是不与 $D_m$ 相邻的最小值）；2.选 $D_{m-1} + D_{m+1}$。

如果你不理解的话，这里有解释：如果我们考虑选 $D_{m-1}$ 或者 $D_{m+1}$，这就要使 $D_m$ 换成别的数，假设将 $D_m$ 换成 $D_x$，$D_{m-1}+D_x$ （假设选 $D_{m-1}$，$D_{m+1}$ 同理），那么 $D_m+D_x$ 一定可以比它优。**于是我们可以不用管 $D_{m-1}$ 与其他数组合能否得到最优解，因为它一定是不能的，只要考虑 $D_{m-1}$ 和 $D_{m+1}$ 能否组成最优解，因为这个在 $D_m+D_{m'}$ 里面没有考虑到。**

- $k=3$

（~~k=3，它显得杂乱无章。所以我们不在乎数学的严谨性，直接讨论我们想看到的~~）

现在已经选出 $k=2$ 的情况，假设如下图所示

![](https://cdn.luogu.com.cn/upload/image_hosting/4g806qrb.png)

令 $k=2$ 中选出来的分别是 $D_{m-1},D_{m+1}$ （和上图一样，他们 “间接相邻”）

那么决策集合也只有两个部分：1.选 $D_{m-2}+D_{m}+D_{m+2}$；2.选 $D_{m-1}+D_{m+1}+D_{m'}$（$D_{m'}$ 就是不干扰这两个点的最小的一个点）

**直观地来说，要么选蓝色部分，要么选红色部分 + $D_{m'}$**

如果你~~还是~~不理解的话，继续解释：如果我选了蓝色部分的一个点 $D_b$ (blue)，那么就要干扰一个甚至多个点，被干扰的点记为 $D_r$ (red)，将它更换为其他的点 $D_e$ (else)，因为其他部分没有变化，因为有 $D_e+D_r < D_e+D_b$，那么我们会发现这样选取是不可行的！如果干扰了多个点（最多为两个），记为 $D_{r1},D_{r2}$ ，将它更换为其他的点 $D_{e1},D_{e2}$，假设 $D_{e1}+D_{e2}+D_b<D_{r1}+D_{r2}+D_{m'}$ 因为 $D_{e1}>=D_{m'}$，那么 $D{e_2}+D_b<D_{r1}+D_{r2}$，如此一来，这不是说明 $D_{r1},D_{r2}$ 不是上一轮的最优解！？这与条件相矛盾，故不成立。

----

做出以上分析后，我们摸索出来一个性质：（先上一张图，假设当前选了 $k$ 对点了）

![](https://cdn.luogu.com.cn/upload/image_hosting/qo6fs0h8.png)

**如果有一些点 “间接相邻”，若有一个点被干扰（选了一个蓝色点），所有的点改变位置（红色变蓝色区域）**，形象地解释为：**“同生死，共进退”**。首先这个性质是我们通过刚才这些分析猜出来的，对于任意情况，可以用我给出来的这种方法做类似分析，~~这样证明是不是严谨的就不知道了~~，但是这个结论是可以证明的，具体我也不会、、

----

当然你还会想啊，我们选的点是离散的呀，比如下面这张图

![](https://cdn.luogu.com.cn/upload/image_hosting/ihg960gw.png)

**但是对于间接相邻的这些点 上面这个性质成立呀！qwq**

----

现在也许你对这个算法的思想大概明白了，却不知道怎么实现，这就要引出我们 “妙” 的代码实现了

- 开一个小根堆，结点存放 $val,pos$ ，开一个链表。$pos$ 表示这个结点在链表中相应的位置。

- 然而这个 $val$ 就妙了，，，先讲实现流程：

- 每次从堆中取出一个结点，将 $ans+=val$，将链表中 $pos,L[pos],R[pos]$ 中三个结点删去，加入在这个位置加入一个新的结点，这个新结点的 $val=val(L[pos])+val(R[pos])-val(pos)$，再把这个结点加入堆。**结合“红蓝点的说法”，其实我们是把蓝点区域看成一种状态加入进了堆,val是记录红点区域和蓝点区域的差值**（自己模拟一下会有一点点 容斥般巧妙的感觉qwq）。

- 重复 $k$ 次得到答案。

----

还有 **一点点细节**，如果我们遇到下面这种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/gprseajw.png)

红点在边缘，我把它叫做 “**蓝点会溢出**”，这种情况我们肯定不能再将蓝点区域放入堆里面了。反过来，我们不取出它就可以了。有一个小 $Trick$，将链表的头尾（虚拟）结点的 $val=INF$ 即可。

----

综上所述，这题考察了我们 **优先队列+双向链表** 的灵活运用。

## Code

Talk is cheap.Show me the Code.

```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 1e18
using namespace std;
inline int read() {
	int x=0,f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=(x<<3)+(x<<1)+(ch^48); ch=getchar(); }
	return x * f;
}
const int N = 100007;
int n,K,ans;
int D[N],L[N],R[N],val[N];
bool vis[N];
priority_queue<pair<int,int> > q;
signed main()
{
	n = read(), K = read();
	int last = read();
	for(int i=2,x;i<=n;++i) x = read(), D[i-1] = x-last, last = x;
	for(int i=1;i<n;++i) val[i] = D[i], L[i] = i-1, R[i] = i+1, q.push(make_pair(-val[i],i));
	val[0] = val[n] = INF;
	for(int i=1;i<=K;++i) {
		while(vis[q.top().second]) q.pop();
		int x = -q.top().first, pos = q.top().second; q.pop();
		//printf("x = %d\n",x);
		ans += x; int l = L[pos], r = R[pos];
		L[pos] = L[l], R[pos] = R[r];
		R[L[pos]] = pos, L[R[pos]] = pos;
		vis[l] = vis[r] = 1;
		val[pos] = val[l] + val[r] - x;
		//printf("updata x = %d\n",val[pos]);
		q.push(make_pair(-val[pos],pos));
	}
	printf("%lld\n",ans);
	return 0;
}
```

## Summary

这是一道思维题，我还是要强行在这中间学到套路(逃:

- **善于从简单的情况入手，考虑数学归纳法，从而猜出一些性质**

- **灵活运用双向链表，灵活实现代码（双向链表真是一种神奇的数据结构）**

---

## 作者：zhoutb2333 (赞：33)

我来一份不同方法的题解

考虑朴素dp，设  $f[i][j][0/1]$ 为前 $i$ 个房子，连了 $j$ 条线，并且第 $i$ 个房子是/否和第 $i-1$ 个房子连线。那么答案就是 $\min(f[n][k][0],f[n][k][1])$ 。
转移很简单，什么 $f[i][j][0]=\min(f[i-1][j][0],f[i-1][j][1]), f[i][j][1]=f[i-1][j-1][0]+pos[i]-pos[i-1]$。

然而并开不下。但是发现这个东西很像九省联考D2T2。

设 $h(x)$ 为 $\min(f[n][x][0],f[n][x][1])$ （就是 $k=x$ 时的答案），那么这是肯定是一个增函数。我们继续打表发现，这还是一个下凸函数（可以感性的理解一下，一开始可以选小点的，后来就没办法了）。然而并不会证明~~OI没有证明~~

那么我们考虑用一条斜率为 $slope$ 的直线去切这个函数。切到的第一个点肯定满足 $h(x)-slope *x$ 最小。而我们发现这个式子是有意义的：相当于我们可以连没有限制条边，并且每连一条边都可以额外使答案减少 $slope$ 。这样的话我们就可以dp出满足 $h(x)-slope *x$ 最小的 $x$ ，dp方法跟朴素dp差不多，只不过可以去掉连边数限制的那一维，然后再记一个 $g[i][0/1]$ 表示最优状态下的连边数。

这个 $x$ 不一定等于 $k$ （如果等于 $k$ 那么我们可以直接求出答案了），但是因为 $h(x)$ 是一个凸函数，所以我们可以二分这个斜率，然后每次根据dp出的结果来调整二分的 $slope$ 。最终切到 $k$ 的时候就可以求出答案 $h(k)$ 了。

也有切不到 $k$ 的时候，比如说 $h(k+1)-h(k)=h(k)-h(k-1)$ ，所以我们改在 $x \le k$ 时更新答案。

``` cpp
#include<bits/stdc++.h>
#define maxn 100010
#define ll long long
using namespace std;

int g[maxn][2],pos[maxn],n,k;
ll f[maxn][2];
const ll INF=1LL<<60;
inline void check(ll &x,int &y,ll X,int Y){
	if(x>X||(x==X&&y>Y))
		x=X,y=Y;
}
void solve(ll s){
	f[1][0]=g[1][0]=0,f[1][1]=INF;
	for(int i=2;i<=n;i++){
		f[i][0]=f[i-1][0],g[i][0]=g[i-1][0];
		check(f[i][0],g[i][0],f[i-1][1],g[i-1][1]);
		f[i][1]=f[i-1][0]-s+pos[i]-pos[i-1],g[i][1]=g[i-1][0]+1;
	}
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&pos[i]);
	ll l=0,r=1e9+10,ans;
	while(l<r){
		int ansg;
		ll mid=l+r>>1,ansf=INF;
		solve(mid);
		for(int i=0;i<=1;i++)
			check(ansf,ansg,f[n][i],g[n][i]);
		if(ansg<=k)
			ans=ansf+mid*k,l=mid+1;
		else
			r=mid;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：niiick (赞：32)

不难想到，
为了使布线长度尽量小，每对布线的办公楼一定是相邻的

所以我们可以在读入时计算差分数组保存每相邻两个办公楼的距离

这样问题转化为，
**在差分数组中找k个数，满足k个数之和最小且互不相邻**

设差分数组为b[]，
其中最小的数为b[i]

显然最优解必定是一下其中一种

1.包含b[i]以及除b[i-1]和b[i+1]的数

2.包含b[i-1]和b[i+1]以及除b[i]，b[i-2]，b[i+2]

从这一点扩展，
可以先取b[i]，并以b[i-1]+b[i+1]-b[i]替换，

然后在新数列中继续重复k-1次得到最后结果

这样若b[i]不属于最优解，则b[i-1]+b[i+1]-b[i]必定被选，满足了上述第二种情况

更具体做法是，
将原差分数组每个值插入堆，
并将数组以链表串起来

每次取堆顶最小值更新答案，并删除该值，

设最小值编号为i，
那么再插入b[ pre[i] ]+b[ nxt[i] ]-b[i]，
并更新链表

重复k次即得最优解
*************************

```
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;
typedef long long lt;
 
lt read()
{
    lt f=1,x=0;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return f*x;
}
 
const int maxn=500010;
int n,k,cnt;
lt a[maxn],b[maxn];
struct node{lt val;int num;}mi[maxn];
int pre[maxn],nxt[maxn],judge[maxn];
lt ans;
 
void swapp(int x,int y)
{
    node tt=mi[x];
    mi[x]=mi[y]; mi[y]=tt;
}
 
void ins(lt val,int num)
{
    mi[++cnt].val=val; mi[cnt].num=num;
    int p=cnt;
    while(p>1)
    {
        if(mi[p>>1].val>mi[p].val){ swapp(p,p>>1); p>>=1;}
        else break;
    }
}
 
void pop()
{
    mi[1]=mi[cnt--];
    int p=1,s=p<<1;
    while(s<=cnt)
    {
        if(s<cnt&&mi[s].val>mi[s+1].val) s++;
        if(mi[p].val>mi[s].val){ swapp(p,s); p=s; s=p<<1;}
        else break; 
    }
}
 
int main()
{
    n=read();k=read();
    for(int i=1;i<=n;++i) a[i]=read();
    for(int i=1;i<n;++i)
    {
        b[i]=a[i+1]-a[i];
        ins(b[i],i);
        pre[i]=i-1; nxt[i]=i+1;
    }
    b[0]=b[n]=2e9;//注意0号和n号赋极大值
    nxt[0]=1; pre[n+1]=n;
    while(k--)
    {
        while(judge[mi[1].num]) pop();
        int val=mi[1].val,num=mi[1].num; pop();//取堆顶最小值
         
        ans+=val;
        b[num]=b[pre[num]]+b[nxt[num]]-b[num];//新插入得值
        judge[pre[num]]=judge[nxt[num]]=1;//两旁得值不能再取
         
        pre[num]=pre[pre[num]]; nxt[pre[num]]=num;//更新链表
        nxt[num]=nxt[nxt[num]]; pre[nxt[num]]=num;
         
        ins(b[num],num);//插入新值
    }
    printf("%lld",ans);
    return 0;
}
```



---

## 作者：djh123 (赞：13)

由于自己不想手写堆~~（太懒）~~，就决定用STL水过去，而题解中又没有用优先队列做的，就决定来写篇STL的题解啦

具体证明，做法楼上大佬已经讲的很清楚了，这道题的重点就是处理好合并。
```cpp
#include <cstdio>
#include <queue>
using namespace std;
const int inf = 1e9 + 7;
int f[100005], l[100005], nxt[100005], pre[100005], n, k, ans;
struct node{int id, val;}now;
bool operator < (node a, node b) {return a.val > b.val;}
priority_queue <node> Q;
int main() {
	scanf("%d %d", &n, &k);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &f[i]);
	for(int i = 1 ; i < n ; ++ i) l[i] = f[i + 1] - f[i], nxt[i] = i + 1, pre[i] = i - 1;// 预处理出左右与相邻的长度 
	nxt[n - 1] = 0;//处理边界，防止越界，后面更好处理 
	for(int i = 1 ; i < n ; ++ i) Q.push((node){i, l[i]});
	for(int i = 1 ; i <= k ; ++ i) {
		now = Q.top(), Q.pop();
		if(now.val != l[now.id]) { // 如果两个值不相同，则已经合并 
			++ k;
			continue;
		}
		ans += now.val;
		int lp = pre[now.id], rn = nxt[now.id];//新的左右边界 
		nxt[now.id] = nxt[rn]; pre[nxt[now.id]] = now.id; // 更新边界 
		pre[now.id] = pre[lp]; nxt[pre[now.id]] = now.id; // 更新边界 
		l[now.id] = (lp && rn) ? min(inf, l[lp] + l[rn] - l[now.id]) : inf; //更新合并后的值
		//若lp rn中有一个是0，那么就把长度设为inf 
		l[lp] = l[rn] = inf;Q.push((node){now.id, l[now.id]});//把合并后的扔进堆中 
	}
	printf("%lld", ans);
}
```

---

## 作者：revenger (赞：13)

原题可以转化为在一个数轴上有n个点，从里面选出2k个点组成k组，每组点之间的距离和最小。

首先这道题有一个非常明显的性质，每个点只会和与自己相邻的两个点连线。

证明：假设有a,b,c三个相邻点(a<b<c).假设a和c连边，如果b没有被连边，则a与b连边显然比a与c优。

如果b与另一个点d连边，那么d<a或d>c。当d>c时如果cd和ab相互连边的话会省下bc之间的距离，d<a时同理。

对于60%的数据,n<=10000。

结合以上性质，60分的做法非常好想。

f[i][j]表示考虑前i个点，已经形成j对点的最小距离，num[i]表示第i个点的坐标。

如果这个点不与其他点组成一对，那么f[i][j]=f[i-1][j]。

否则这个点只能和前面的点组成一对，f[i][j]=f[i-2][j-1]+num[i]-num[i-1]。

f[i][j]=min(f[i-1][j],f[i-2][j-1]+num[i]-num[i-1]);

时间复杂度O(nk) 这道题空间限制只有32M，可以滚动数组优化过。

我们可以在60分的基础上进行分析。

100分的数据点是n<=100000。

这个数据范围如果把nk中的一维降为log级别就能过。

我们现在可以对题目进行进一步转化。对原数组求一个差分，然后题目转化为在n-1个值里选择不相邻的k个。

结合复杂度，我们可以考虑贪心，每次找n-1个值里面最小的加入，然后把与它相邻的值删除，使用堆优化可以达到klogn的效率。

然而这种算法很明显就能被证明是错误的……

比如4个值3 2 3 1000000 按照贪心原则会选择2+1000000，然而最优解很明显是3+3 ←\_←

所以我们需要想一个贪心策略。

这里有一个非常精妙的转化。假设在原先的n个点上有abcde5个相邻点(a<b<c<d<e)，我们把它差分以后就是ab,bc,cd,de四个值。

假设bc是最小的那个，我们贪心把bc选出来，然后加入答案以后删除。之后我们同时把与bc相邻的ab,cd取出来。把这三个值全都删除后合成一个新的值，这个值=ab+cd-bc。那么如果我们再次通过贪心原则把这个ab+cd-bc选出来加入答案，那么其中的-bc会和一开始选择的bc抵消，相当于我们这两次选择了ab+cd，也就是与bc相邻的两段。每一次选择会把已选择的段的数量+1，所以选择k次以后的ans就是最优解

那么我们就可以每次从堆里选择一个点，然后同时删除与之相邻的点，然后加入一个新点，操作k次。单次操作为4logn的效率(3次取出和1次加入），所以最后效率为4klogn。

我们可以维护一个链表表示每个值的前驱后继，对于起始位置和结束位置，我们可以人为创造一个0号点和n号点(因为一共n-1个值，注意这里的点是差分以后的，不要和原数组搞混），它们的值为inf。这样我们就可以处理一个单向链表。

现在还有两个问题，如何从堆里快速找到一个点对应的位置，还有如何从堆里删除一个随意点(非根节点)。

对于第一个问题，我们可以开一个数组f，f[i]表示第i号点在堆里的位置是哪里。在维护堆的性质时把f数组一块交换即可。

第二个问题，我们还是从堆的最后找一个节点插入你要删除的位置，然后向下维护。注意如果你无法向下维护，你需要向上维护，因为从堆尾往堆中间的随意节点插入一个值时，这个值不一定比这个节点的父亲节点大，比如一个堆数组里是1 6 2 8 9 3 4 很明显这满足堆的性质(因为不会插图所以就直接写数组了，看不懂的请自行画出这个堆)但是当你想删除8的时候，你把4插入8的位置，但是4比它的父节点6还要小，所以你还要向上维护。

注意到这一坨细节问题后我们就可以开始写代码了，下面附代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int    num[200005],n;
int ans;
int heap[200005],fheap[200005],sz;
int pre[200005],nxt[200005],k;
int x1,x2;
inline void swap(int &x,int &y)
{
    x^=y,y^=x,x^=y;
}
inline void del(int x)
{
    heap[x]=heap[sz--];
    fheap[heap[sz+1]]=x;
    int now=x,nxt;
    if(num[heap[now]]>=num[heap[now>>1]])
    {
        nxt=now<<1;
        while(nxt<=sz)
        {
            if(nxt<sz)
            nxt=num[heap[nxt]]<num[heap[nxt|1]]?nxt:nxt|1;
            if(num[heap[now]]<num[heap[nxt]])
            break;
            swap(fheap[heap[now]],fheap[heap[nxt]]);
            swap(heap[now],heap[nxt]);
            now=nxt;nxt=now<<1;
        }
    }
    else
    {
        nxt=now>>1;
        while(nxt)
        {
            if(num[heap[now]]>=num[heap[nxt]])
            break;
            swap(fheap[heap[now]],fheap[heap[nxt]]);
            swap(heap[now],heap[nxt]);
            now=nxt,nxt=now>>1;
        }
    }
}
inline void push(int x)
{
    heap[++sz]=x;
    fheap[x]=sz;
    int now=sz,nxt=now>>1;
    while(nxt)
    {
        if(num[heap[now]]>=num[heap[nxt]])
        break;
        swap(fheap[heap[now]],fheap[heap[nxt]]);
        swap(heap[now],heap[nxt]);
        now=nxt,nxt=now>>1;
    }
}
void read(int &ans,char ch=getchar())
{
    ans=0;
    for(;ch<'0'||ch>'9';ch=getchar());
    for(;ch>='0'&&ch<='9';ans=ans*10+ch-48,ch=getchar());
}
int main()
{
    read(n),read(k);
    read(x1);
    for(int i=2;i<=n;i++)
    {
        pre[i]=i-1;
        nxt[i]=i+1;
        read(x2);
        num[i]=x2-x1;
        x1=x2;
        push(i);
    }
    num[1]=1e9+7;
    num[n+1]=1e9+7;
    push(1);
    push(++n);
    for(int i=1;i<=k;i++)
    {
        int x=heap[1];
        del(1);del(fheap[pre[x]]);del(fheap[nxt[x]]);
        x1=num[pre[x]],x2=num[nxt[x]];
        num[++n]=x1+x2-num[x];
        ans+=num[x];
        pre[n]=pre[pre[x]];
        nxt[n]=nxt[nxt[x]];
        nxt[pre[pre[x]]]=n;
        pre[nxt[nxt[x]]]=n;
        push(n);
    }
    printf("%d",ans);
}

```

---

## 作者：jyz666 (赞：10)

# 题解 P3620 【[APIO/CTSC 2007]数据备份】

传送门[QwQ](https://www.luogu.com.cn/problem/P3620)

## 题目分析

这道题用到了网络流（貌似）中一个比较重要的思想：**退流思想**（大概就是反悔机制（也就是高级贪心））！

**题意：**从$n$−$1$个点选取$k$的不相邻的点使得所得答案最大。

我到这里是先想到一个$dp$，结果一看数据范围直接懵逼，$O(n2)$用脚趾头想都是过不了的。~~然后想了想似乎网络流也能做，不过复杂度貌似也过不去。。。~~

根据进阶指南，可以得到以下结论：
对于任意一对（相邻两个）办公楼 $i$ , $j$ ，局部最优解只会有两种情况:

1. 连$i$，$j$
1. 连$i$-1,$i$和$j$,$j+1$

显而易见，1情况最优时$ i$−1 ,$ i $和$j,j+1$是不能选的。

对于2情况，由于所有距离都是正数，故选择$i$−1,$i$和$j,j+1$两段一定比只选其中某一段更优。

但是我们发现如果直接贪心，也就是每次选择最小距离累加进答案，是有后效性的，因为这会导致最小距离两侧的距离不可选择，但最优解仍然有可能包含它们两个。

注意到此处直接贪心的后效性产生的原因**仅仅是因为其影响了当前状态下最短距离两侧的距离的选择**，既然如此，那我们不妨考虑一个**可以反悔并消除之前选择的影响**的贪心。

那么我们可以得到一种贪心：建立链表1∼$n$−1，对应所有距离，并映射到一个优先队列中。每次贪心选择最短距离$kd$累加进答案，假设其所在位置为$d$，把$d$−1,$d$+1两段打上标记，表示不能选择，再在链表中删除$d$−1,$d$,$d$+1的节点，在堆中也删除对应的节点，再在链表原来的位置加入新节点，其权值为$kd$−1+$kd$+1−$kd$（$k$为距离大小），同时也在堆中新增一个权值为$kd$−1+$kd$+1−$kd$的节点。这样一来，当我们在之后的状态中再次选择新节点时，就会消除之前选择$d$的影响，相当于选择了$d$−1,$d$+1而不选$d$。

下图中，黑色填充表示选择该段。

第一次选择位置$d$的点时，答案$ans$=⋯+$kd$。

![](https://cdn.luogu.com.cn/upload/image_hosting/78suk9zd.png)

第二次选择该位置的点，答案$ans$=⋯+$kd$+$kd$−1+$kd$+1−$kd$=⋯+$kd$−1+$kd$+1

![](https://cdn.luogu.com.cn/upload/image_hosting/y64zujrc.png)

我们删除原节点并新增节点的操作实际上相当于对一个子问题做出了决策，并逐步解决规模更大的子问题。

下图中如果红框内表示当前状态的最优解，实际上他就是该子问题的最优解，在之后的决策中，我们可以直接使用这个子问题的最优解，而不用考虑其内部是如何构成的。

![](https://cdn.luogu.com.cn/upload/image_hosting/bydzv20p.png)

我们需要证明更一般的情况以解决整个问题，下面我们证明全局最优解也满足这个性质。

首先，显然我们的贪心具有决策包容性，任意的子问题一定包含了比它更小的所有子问题（这是一个区间上的问题）。

我们不妨使用微扰法和范围缩放法进行贪心正确性的证明。

尝试证明标记不可选择区域的操作的正确性，假设当前子问题状态如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/2x4b1ogy.png)

即，前一步时，子问题最优解为黑色区域，当前最短距离为灰色区域。

如果此时我们选择了灰色区域，那么一定有**所有距离**$>$**最右边的那段灰色距离**，且已经选择的**所有黑色区域的任意一个的距离**$<$**灰色区域的距离**，因此在这个子问题中我们一旦选择了灰色区域，一定会减少一个比灰色区域更小的距离，增加一个比灰色区域更大的距离到答案中，这一定**不是**最优解。

显然这个性质可以扩展到任意子问题，即任意时刻做出如上贪心决策不会使得结果变差。



此外，我们还要注意一些**细节**：链表的上下界处理，我们要保证表头和表尾不被选择（它们不包含在任一子问题中），只需把初值赋为无穷大即可。

### AC代码
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define inf 0x3f3f3f3f
#define N 100005
#define rep(i,x,y) for (register int i=x;i<=y;++i) 
using namespace std; 
int n,k,list,ans,pre[N],suf[N],a[N],t,T; 
priority_queue<pair< int ,int >,vector< pair < int ,int > >,greater<pair< int ,int > > > q; 
int main(){ 
	scanf("%d%d",&n,&k); 	
	ans=0; list=0;
	memset(pre,0,sizeof(pre)); 
	memset(suf,0,sizeof(suf));
	while (q.size()) q.pop(); 
	rep(i,1,n) {
		scanf("%d",&t); a[i]=t-list; list=t; 
		pre[i]=i-1,suf[i]=i+1;  
	}
	pre[2]=suf[n]=0; 
	for(register int i=2;i<=n;++i) q.push(make_pair(a[i],i)); 
	for(register int i=1;i<=k;++i) {
		while (q.top().first!=a[q.top().second]) q.pop(); 
		pair< int ,int > e=q.top(); q.pop(); ans+=e.first; 
		int l=pre[e.second],r=suf[e.second]; 
		a[e.second]=(l&&r)?min(a[l]+a[r]-a[e.second],inf):inf; a[l]=a[r]=inf; 
		suf[pre[e.second]=pre[l]]=e.second,pre[suf[e.second]=suf[r]]=e.second;
		q.push(make_pair(a[e.second],e.second)); 
	}
	printf("%d\n",ans); 
	return 0; 
}
```

求点赞QwQ

---

## 作者：llzzxx712 (赞：6)

# P3620题解

[传送门](https://www.luogu.com.cn/problem/P3620)

## 题目分析

容易发现，最优解中相邻两个办公楼一定是相邻的，我们求出每相邻两个办公楼之间的距离$a$，记为 $a_1,a_2,a_3 … a_{N-1}$ ，那么问题可以转化为从数组a中选出不超过K个数，使他们的和最小，并且相邻两个数不能同时被选。

[这样本题就被转化为了P1484](https://www.luogu.com.cn/problem/P1484) （不过P1484是一个环这是一条链，而且本题有多组数据）

比如样例就可以被转化为  $2,1,2,6$ ，那么我们选择第一个和第三个2，就得到了最优解4。

## 解题思路

如果 K = 1，那么结果就是$a$数组中的最小值。

如果 K = 2，那么就有两种情况：

1. 选择最小值 $a_i$ ，不选 $a_{i-1} ,a_{i+1} $ ，再从剩下的数中选择最小值。
1. 不选最小值 $a_i$ ，选 $a_{i-1} ,a_{i+1} $ 。

为什么不选最小值 $a_i$ 就要选 $a_{i-1} ,a_{i+1} $ 呢？

如果只选了 $a_{i-1} ,a_{i+1} $ 中的一个，那么把选了的换成了 $a_i$ 一定更优。

显然$a_i , a_{i-1} ,a_{i+1} $都不选不是最优解。

**所以最小值左右两侧的数要么都选，要么都不选。**

所以我们可以先选上 $a$ 数组中的最小值（第一种情况），然后将然后将 $a_{i-1},a_i,a_{i+1}$ 从数列中删除，并在原位置插入一个新元素$a_{i-1}-a_i+a_{i+1}$ 。这样原问题就变成了一个从 $a$数组中选 $K-1$ 的数的子问题，显然重复这个操作 $k-1$次就可以求出最终结果。

## 代码实现思路

所以我们可以建立一个链表 Q，分别记录$a_1,a_2,a_3 … a_{N-1}$ 。 再建立一个二元组小根堆，每个元素与链表中的每一个元素成一一映射关系，第二元记录对应链表中的指针。

每次取出堆顶，更新答案。再删除节点（链表中打标记、更新左右节点数组，小根堆中删除）、插入新节点。

执行$K$次后输出

## 易错点
- 本题数据是一条链而不是环
- 记得开 long long

## AC代码

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;
void read(int &x){
	int f=1;x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
#define N 100010
priority_queue < pair <ll,int > > q;
int n,k,le[N],r[N];
bool v[N];
long long ans,a[N];
void del(int x){
	le[r[x]]=le[x];
	r[le[x]]=r[x];
	v[x]=1;
}
int main(){
	read(n),read(k);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	n--;
	//le[1]=n,le[n]=n-1,r[1]=2,r[n]=1;
	for(int i=1;i<=n;i++){
		le[i]=i-1,r[i]=i+1;
		a[i]=a[i+1]-a[i];
		q.push(make_pair(-a[i],i));
	}
	a[0]=a[n+1]=1234567890;
	while(k--){
		int x,y;
		while(v[q.top().second]) q.pop();
		x=q.top().second;q.pop();
		ans+=a[x];
		//printf("%lld %d\n",ans,x);
		a[x]=a[le[x]]+a[r[x]]-a[x];
		v[x]=0;
		del(le[x]),del(r[x]);
		q.push(make_pair(-a[x],x));
	}
	cout<<ans;
	return 0;
}

```





---

## 作者：Sundial (赞：4)


相信大家已经看过很多dalao的证明了，而且本蒟蒻也不太会

就不多赘述啦，我提供个数组做双向链表的吧

双向链表的核心就是用两个数组分别储存自己前面和后面数的坐标

分别称为前驱，后驱（反正我是这么叫的qwq）

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll ans;
int n, k;
int qian[500021];//前驱数组
int hou[500021];//后驱数组
int a[500021];//读入数组
set<pair<int, int> > s;//堆
int main () {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		qian[i + 1] = i;//前驱预处理
		hou[i] = i + 1;//后驱预处理
	}
	for (int i = n - 1; i > 0; i--) {
		a[i] -= a[i - 1];//求查分
		s.insert(make_pair(a[i], i));//绑起来塞进去
	}
	a[0] = 1e9, a[n] = 1e9;//防止越界
	while (k--) {
		int x = s.begin() -> second;//取最小的坐标
		s.erase(s.begin());//删掉
		ans += a[x];//因为是最小，直接加入答案
		s.erase(make_pair(a[qian[x]], qian[x]));//将前面的删掉
		s.erase(make_pair(a[hou[x]], hou[x]));//将后面的删掉
		a[x] = a[qian[x]] + a[hou[x]] - a[x];//前后合并
		s.insert(make_pair(a[x], x));//合并后再绑起来塞进去
		qian[x] = qian[qian[x]];//更新前驱坐标
		hou[x] = hou[hou[x]];//更新后驱坐标
		qian[hou[x]] = x;// i 的前驱的后驱还是 i 
		hou[qian[x]] = x;// i 的后驱的前驱还是 i
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：SamariumPhosphide (赞：2)

首先，每条电缆必须是相邻的两幢楼之间连接的。否则，我们用同样的字母表示连在一起的两幢楼，如果有类似 a \* a 的情况，那么分类讨论：

+ a \*  a中当中的那幢楼没有连电缆，那么可以将改为 a  a \*，比原来更优。
+ 如果当中的楼有连电缆，例如 a b a \* \* \* b，那么将当中的 a 和 b 交换位置，改为 a a b \* \* \* b 比原来更优。

所以现在只用考虑相邻的楼之间的差即可。假设 $d[i]=pos[i]-pos[i-1]$，题目即求在 $d$ 中选择 $k$ 个不相邻的数。我们考虑 $d$ 中最小的数 $d_k$，以及其两边的数 $d_{k-1}, d_{k+1}$。

如果 $d_{k-1},d_{k+1}$ 均不选，那么如果没有选择 $d_k$，那么将选择的其中一个数改为 $d_k$ 一定更优。说明一定选择了 $d_k$。

如果 $d_{k-1}, d_{k+1}$  只选择了一个，那么不能选择 $d_k$，此时如果将选择的那个改为 $d_k$ 一定更优。说明不能只选一个。

综上，我们证明了：要么选 $d_k$，要么 $d_{k-1}, d_{k+1}$ 同时选。

此时我们考虑怎么讨论这两种情况，可以这样：先取出 $d_k$，累加在答案上，然后去掉 $d_{k-1}, d_{k+1}$，插入 $d_{k-1} + d_{k+1} - d_k$。如果这个数最后被选了，相当于将 $d_k$ 替换为 $d_{k-1}$ 和 $d_{k+1}$，否则就是选择了 $d_k$。这样便高效地解决了分类地问题。

实现：使用链表和 set 即可。

~~最后请大家自觉日膜UM~~

[Code](https://www.luogu.com.cn/paste/rqffg67l)



---

## 作者：Sakurajima_Mai (赞：2)

首先呢

简要题意：

从$n$个点中选取$k$个点，最小化每对点之间的距离

明确一点：要使得每对点之间的距离最小，那这两个点一定是相邻的

由此，我们可以得到一个简单的想法：将距离两两差分，直接从中选出最小的$k$个

但是，这样的想法存在一种可能，也就是我们所选取的$k$个距离可能重复选取两个相同的办公楼。不满足题中所言"**任一个办公楼都属于唯一的配对组(换句话说，这 2K 个办公楼一定是相异的)**"

所以，我们假设选取了差分后的第$i$段，则第$i-1$段和第$i+1$段均无法被选取，但最终答案也可能是选取第$i$段和$i+1$段

因此可以再选取了第$i$段后，将第$i-1$和第$i+1$段标为不可选，再将$len[i-1]+len[i+1]-len[i]$加入可选段中，代表同时选择第$i-1$和第$i+1$段。
（ps:$len[i]$代表差分数组）
  
那要同时选择第$i-1$和第$i+2$段呢？

如果同时选择第$i-1$和第$i+2$段而不是第$i-1$和第$i+1$段的话则必须要满足$len[i+2] \leq len[i+1]$
先选择第$i$段的条件是$len[i] \leq len[i-1]$
则$len[i+2] \leq len[i+1]+len[i-1]-len[i]$

于是乎呢第$i-2$段和第$i$段同时被选择，答案更优，与假设矛盾

因此得到贪心算法：
- 将输入的序列差分成$n$段，且将$n$段放入堆中
- 选出堆中答案最小的一段，加入答案中
- 将该段的前一段和后一段标为不可用
- 将该段在下一次的选择中的权值改为$len[pre]+len[nxt]-len[now]$
- 最后重复上述步骤$k$次，得到答案


最后看一下代码吧：
$vis$数组用于标记一段是否可用，
$sum$呢是所谓的差分，
$q$呢为优先队列
```cpp
for(int i=1;i<=k;i++){
    while(vis[(q.top()).id])q.pop();
    node x = q.top();q.pop();
    ans+=x.num;
    int a=pre[x.id],b=nxt[x.id];
    int v=sum[a]+sum[b]-sum[x.id];
    sum[x.id]=v;
    q.push((node){v,x.id});
    pre[x.id]=pre[a];nxt[pre[a]]=x.id;vis[a]=1;
    nxt[x.id]=nxt[b];pre[nxt[b]]=x.id;vis[b]=1;
    }
```




---

## 作者：dsjkafdsaf (赞：1)

### 可反悔的贪心！！！
看到题面，很显然可以得到每栋写字楼必定要
和其相邻的写字楼相连接。

很自然的用堆来维护。

可是否是每次将堆顶的未取线段取走，并打标记呢？

由样例就可以看出，这是不行的。。

那么该怎么办呢？

于是我们要给程序一个“后悔“的机会：将弹出的两侧办公楼对合为一对，其距离为两个办公楼对的距离和-弹出的办公楼距离。

这样我们取这个对的时候就相当于减去了中间的对而取了旁边两侧的对，就是一个“后悔”的过程啦！

维护两侧的对可以用链表来实现。

**注意一定要清空有关变量；** 
## 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
#define rep(a,b,c) for(reg int a=(b),a##_end_=(c); a<=a##_end_; ++a)
#define drep(a,b,c) for(reg int a=(b),a##_end_=(c); a>=a##_end_; --a)
#define debug(x) cerr<<#x<<" = "<<x<<endl;
int Read() {
    int res=0,f=1;
    char c;
    while(c=getchar(),c<48)if(c=='-')f=-1;
    do res=(res<<3)+(res<<1)+(c^48);
    while(c=getchar(),c>=48);
    return res*f;
}
void Min(double &A,double B) {
    if(A>B)A=B;
}
const int M=1e5+5;
int n,k,Ans,A[M],S[M],L[M],R[M];
bool vis[M];
void Add(int num) {
    L[num]=num-1,R[num]=num+1;
}
void Del(int num) {
    vis[num]=1;
    L[R[num]]=L[num];
    R[L[num]]=R[num];
}
struct node {
    int id;
    bool operator<(node _)const {
        return S[id]>S[_.id];
    }
};
priority_queue<node>Q;
int main() {
    n=Read(),k=Read();
    rep(i,1,n)A[i]=Read(),L[i]=i-1,R[i]=i+1;
    rep(i,1,n-1) {
        S[i]=A[i+1]-A[i];
        Q.push((node)<%i%>);
    }
    S[0]=S[n]=1e9;
    rep(i,1,k){
        node Now=Q.top();
        Q.pop();
        if(vis[Now.id]) {
            i--;
            continue;
        }
        Ans+=S[Now.id];
        S[Now.id]=S[L[Now.id]]+S[R[Now.id]]-S[Now.id];
        Del(L[Now.id]),Del(R[Now.id]);
        Q.push((node)<%Now.id%>);
    }
    printf("%d",Ans);
}
```

---

## 作者：山水一程_ (赞：1)

直接贪心(每次选最小)的话显然不对...样例都过不了...
选两个办公楼的时候,显然不能跨越另一个楼,这样不优...
于是 先把原数列处理成n-1个的数(每一个办公楼和上一个的距离),存在a[]中
题目就是 要求选出K个不相邻的数,使得选出的数的和最小

依然考虑贪心,每次选最小的 
但是若a[]是2 1 2 6,要选K=2个,先选了1,然后会发现两个2都没法选,只好选6,这样就尴尬了...
1选了就选了吧,我们考虑补救措施...
就是选1的时候,在堆里删掉两个2,然后在堆中插入2+2-1
相当于 我们以后可以取到那两个2,而且2+2-1可以表示选了两个数,因为刚才选了1,所以在这里-1

还有个边界问题...比如取了第一个数或最后一个数,那么把a[0]和a[n]赋成极大值呗...

因为边界的数 的两侧 只有一个有效的数,无法补救了(补救的时候需要俩数...),赋成极大值那么以后都无法取到

那就要存储 一个数的前一个数是多少,后一个数是多少(方便删除)

7 2 1 2 6 8 取1,删掉俩2,然后新开一个链表空间a[++n],存储2+2-1,用这个链表空间取代2 1 2

新的链表空间,前驱是7所在位置,后继是6所在位置...不要忘了修改 7和6 的前驱和后继...

    特别地,0的前驱和n的后继都是本身...方便修改...

时间复杂度 O( K*log(n) )
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm> 
#define N 100009
using namespace std;
int n,dis[N],la,lheap,heap[N<<3],pos[N<<3],K,now,point[N<<3][2],prev,next;
long long a[N<<3],ans;
inline void push(int x)
{
    int i=++lheap;
    heap[i]=x;
    pos[x]=i;//pos用来记录链表a[]第x个位置 在堆中的位置
    while (i>1)
        if (a[ heap[i] ]<a[ heap[i/2] ])
            {
                swap(heap[i],heap[i/2]);
                swap(pos[ heap[i] ],pos[ heap[i/2] ]);
                i>>=1;
            }
        else return;
}
inline int del(int x)//这里删除的时候,仅仅是赋了一个极大值,塞到堆最靠下的位置啦~
{
    int i=pos[x];
    a[x]=1e12;
    while (i*2<=lheap)
        {
            int p=i*2;
            if ( a[ heap[p+1] ]<a[ heap[p] ] ) p++;
            if ( a[ heap[p] ]<a[ heap[i] ] )
                {
                    swap(heap[i],heap[p]);
                    swap(pos[ heap[i] ],pos[ heap[p] ]);
                    i=p;               
                }
            else break;
        }
}
inline int pop()
{
    int i=1,rt=heap[1];
    heap[1]=heap[lheap--];
    pos[ heap[1] ]=1;
    while (i*2<=lheap)
        {
            int p=i*2;
            if ( a[ heap[p+1] ]<a[ heap[p] ] ) p++;
            if ( a[ heap[p] ]<a[ heap[i] ] )
                {
                    swap(heap[i],heap[p]);
                    swap(pos[ heap[i] ],pos[ heap[p] ]);
                    i=p;
                }
            else return rt;
        }
    return rt;
}
int main()
{
    int i,j,k;
    cin>>n>>K>>dis[1];
    a[0]=a[n]=1e12;//边界赋一个极大值...(因为a[]中是n-1个数,后边界显然是n)
    point[0][1]=1,point[0][0]=0,point[n][1]=n,point[n][0]=n-1;//题解中有解释...
    push(0),push(n);
    for (i=1;i<n;i++)
        {
            scanf("%d",&dis[i+1]);
            a[i]=dis[i+1]-dis[i];
            point[i][0]=i-1;
            point[i][1]=i+1;
            push(i);
        }
     
    for (la=n;K;K--)
        {
            ans+=a[now=pop()];//pop完了后,要先push,因为堆是在不断扩展的,pop后那个元素依然在heap
            prev=point[now][0],next=point[now][1]; //数组的最后一个,push后可以把它覆盖
            a[++la]=a[prev]+a[next]-a[now];
 
            point[la][0]=point[prev][0];
            point[ point[prev][0] ][1]=la;
            point[la][1]=point[next][1];
            point[ point[next][1] ][0]=la;

            push(la);//push要在del之前,
            del( prev ),del( next );
        }
    cout<<ans<<endl;
}
```



---

## 作者：cirnovsky (赞：0)

## 题意简述

给定 $n$ 栋建筑，选出 $k$ 对，使其距离之和最小。

## 题解

可以想见，这 $k$ 对建筑每对都是相邻的。我们设 $L_{i}=A_{i}-A_{i-1}$，其中 $A_{i}$ 为题目中输入的序列。即 $L$ 为 $A$ 的差分序列。

由于已经被选过的位置不能再次被选，所以如果我们选了 $L_{i}$ 那么 $L_{i+1}$ 和 $L_{i-1}$ 都不能选了。如果我们选了 $L_{i+1}$ 和 $L_{i-1}$ 那么我们也不能选 $L_{i}$ 了。

我们设 $L$ 中的最小值为 $L_{m}$。考虑当前情况的每一个最优解，则只有以下两种情形：

1. 选 $L_{m}$

2. 选 $L_{m+1}$ 和 $L_{m-1}$

如此我们得到了一个策略：每次选择 $L$ 中的最小值即 $L_{m}$，然后删除 $L_{m},L_{m-1},L_{m+1}$。如果我们选择了 $L_{m+1}+L_{m-1}-L_{m}$ 的话，即删除 $L_{m}$，选择 $L_{m}$。否则即认为选择 $L_{m}$ 是当前的最优策略。

思路来自李煜东的蓝书。

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e5 + 5;
int n, k, tot, rhs, ans, dis[N], lists[N];

struct ListNode {
	struct LinkList {
		int prev, next;
		int val, id;
	} p[N];
	
	void remove(int x) {
		p[p[x].prev].next = p[x].next;
		p[p[x].next].prev = p[x].prev;
	}
} list;

struct HeapNode {
	struct Heap {
		int val, id;
	} h[N];
	
	void upward(int x) {
		while (x > 1) {
			if (h[x].val < h[x >> 1].val) {
				swap(h[x], h[x >> 1]);
				swap(list.p[h[x].id].id, list.p[h[x >> 1].id].id);
				x >>= 1;
			}
			else break;
		}
	}
	
	void downward(int x) {
		int s = x << 1;
		while (s <= tot) {
			if (s < tot && h[s].val > h[s + 1].val) ++s;
			if (h[s].val < h[x].val) {
				swap(h[s], h[x]);
				swap(list.p[h[s].id].id, list.p[h[x].id].id);
				x = s;
				s = x << 1;
			}
			else break;
		}
	}
	
	void remove(int x) {
		if (x == --tot + 1) return ;
		swap(h[x], h[tot + 1]);
		swap(list.p[h[x].id].id, list.p[h[tot + 1].id].id);
		upward(x);
		downward(x);
	}
	
	void extract(int x) {
		h[1] = h[n--];
		downward(1);
	}
	
	int backtop() {
		return h[1].val;
	}
} heap;

signed main() {
	scanf("%d %d %d", &n, &k, &rhs);
	for (int i = 1; i < n; ++i) {
		int x; scanf("%d", &x);
		list.p[i].val = x - rhs;
		list.p[i].prev = i - 1;
		list.p[i].next = i + 1;
		list.p[i].id = ++tot;
		rhs = x;
		heap.h[tot].val = list.p[i].val;
		heap.h[tot].id = i;
		heap.upward(tot);
	}
	for (int i = 1; i <= k; ++i) {
		ans += heap.backtop();
		if (!list.p[heap.h[1].id].prev || list.p[heap.h[1].id].next == n) {
			if (!list.p[heap.h[1].id].prev) {
				heap.remove(list.p[list.p[heap.h[1].id].next].id);
				list.remove(list.p[heap.h[1].id].next);
			}
			else {
				heap.remove(list.p[list.p[heap.h[1].id].prev].id);
				list.remove(list.p[heap.h[1].id].prev);
			}
			list.remove(heap.h[1].id);
			heap.remove(1);
		}
		else {
			int temp = heap.h[1].id;
			heap.h[1].val = list.p[list.p[heap.h[1].id].prev].val + list.p[list.p[heap.h[1].id].next].val - list.p[heap.h[1].id].val;
			list.p[heap.h[1].id].val = heap.h[1].val;
			heap.downward(1);
			heap.remove(list.p[list.p[temp].prev].id);
			heap.remove(list.p[list.p[temp].next].id);
			list.remove(list.p[temp].prev);
			list.remove(list.p[temp].next);
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：RyexAwl (赞：0)

#### [更好的阅读体验](https://www.cnblogs.com/wxy-max/p/12834098.html)
---
# 暴力
## 思路
首先这道题有一个极为明显的性质：要使每段最短，只能使其这一段只经过两个端点，中间不经过任何建筑。

因此我们可以通过这个性质，枚举每组可行方案，最后选出长度前$k$小的方案。

## 复杂度分析
因为一共有$n$个建筑，存在$n-1$个间隔，每个间隔都有选或不选的两种可能，因此暴力枚举的复杂度为$O(2^n)$。

# 正解（贪心）

## 思路
我们从题目给出的样例开始手玩。

如图，定义$F[i]$为第$i$个间隔的距离。
![](https://cdn.luogu.com.cn/upload/image_hosting/7ixdjuk5.png)

那么很显然，如果我们要想让当前方案的距离总和尽可能小，肯定要优先选当前距离最小的。我们定义$F[u]$为集合$F$中最小的元素。

那么我们是不是可以每次选取我们能选的最小的元素呢？根据样例来看很显然是不可能的，因为你能选的最小的元素可能非常大，远大于$F[u-1]$与$F[u+1]$。

而根据给出的样例，我们选中的两个元素全局最小值$F[u]$两边的元素$F[u-1]$与$F[u+1]$。那么很显然我们就有了以下几种选择方法：

1.选择全局最小值$F[u]$，与除了$F[u-1]$和$F[u+1]$的全局最小值。

2.选择全局最小值$F[u]$两边的元素其中一个$F[u-1]$或$F[u+1]$并选取其他元素使其尽量小。

而对于方案二来说，如果我们要让方案而的状态空间进一步缩小，即让其状态空间所包括的元素尽量少并不遗漏所可能是答案的元素，那么选取了$F[u-1]$，那么我们就一定要选取$F[u+1]$，反之亦是如此，而不能在其他元素中“找小三”。

为什么？

因为如果我们选取了$F[u-1]$与一个元素$F[a]$，那么必然有$F[a] + F[u] < F[u-1]+F[u]$，而对于$F[u+1]$也是如此。

#### 即最小值两侧的点要么全选，要么全不选。

所以，如果我们选择了$F[u+1]$与$F[u-1]$中的任意一个，我们必须选择其令一个才能使其状态空间尽量小，复杂度尽量优。

那么对于$k=2$我们就推出了两种基本的选法：

1.选择全局最小值$F[u]$，与除了$F[u-1]$和$F[u+1]$的全局最小值。

2.选择全局最小值$F[u]$两边的元素$F[u+1]$与$F[u-1]$。

那么我们就可以通过比较$F[u]$与合法的全局最小值$F[v]$的和$F[u]+F[v]$与$F[u+1]+F[u-1]$的答案来得到答案。

那么我们这种思路能否推广到$k>2$的情况呢？

我们可以先找到全局最小值$F[u]$，维护一个集合$S$，将$F[u-1]+F[u-1]$与$F$集合中除了$F[u]$ $F[u-1]$及$F[u+1]$以外的元素与$F[u]$相加后加入集合维护，并将问题转化为“求解从$F$集合中选出不超过$K-1$个数，使其和最小”。


而我们如果选择了$F[u+1]+F[u-1]$这个状态说明我们目前选择的最优答案中不包括$F[u]$,将答案更新为$F[u+1]+F[u-1]$如果选择了$F[v]$，则将$F[v]$更新为答案。而如果是前者，我们则需要将$S$集合中的元素全都更新为$F[u+1]+F[u-1]+F[i]$，而对于这个状态而言我们同样有两种选择，我们可以选择合法的最小的$F[v]$或者选择$F[u-2]$,$F[u]$，与$F[u+2]$，因此我们可以将$F[u-2]$,$F[u]$与$F[u+2]$一同加入集合$S$维护。而对于后者，我们的选择方案同样为$F[u]+F[u+2]$与$F[v]$。

而其中$F$集合因为我们要快速地找出并修改某个元素前面的元素的前面的元素与后面的元素，所以我们可以使用链表维护，而$S$集合要快速找出最小的元素，所以可以用小根堆维护。

因此，我们可以初始化$ans=0$，$F$,$S$（全部元素均加入到$F$与$S$集合），每次将堆顶取出加到$ans$，并在链表中移除堆顶所对元素与堆顶所对元素的前驱与后继，在堆中移除堆顶所对应的前驱与后继。将堆顶的前驱与后继的和减去堆顶的值插入堆中维护，并在链表中插入元素，其前驱为堆顶所对元素的前驱的前驱，后继为堆顶所对元素后继的后继。重复$k$次得到的就为答案。

## 复杂度分析

初始化链表的复杂度为$O(n)$，初始化二叉堆的复杂度为$O(n\ log\ n)$。

而链表与堆中的每个元素最多进$n$次删$n$次，因此总的复杂度为$O(n\ log\ n)$

## 代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int f[100010],a[100010],pre[100010],next[100010],v[100010];
int n,m,p,i,x,ans;

void up(int p)
{
	while(p>1)
		if(a[f[p]]<a[f[p>>1]])
		{
			swap(f[p],f[p>>1]);
			swap(v[f[p]],v[f[p>>1]]);
			p>>=1;
		}
		else break;
}

void down(int l,int r)
{
	int t=2*l;
	while(t<=r)
	{
		if(t<r&&a[f[t]]>a[f[t+1]]) t++;
		if(a[f[l]]>a[f[t]])
		{
			swap(f[l],f[t]);
			swap(v[f[l]],v[f[t]]);
			l=t,t=2*l;
		}
		else break;
	}
}

void insert(int x)
{
	f[++p]=x; v[x]=p;
	up(p);
}

void erase(int x)
{
	f[v[x]]=f[p]; v[f[p]]=v[x]; p--;
	up(v[x]),down(v[x],p);
}

int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	for(i=1;i<n;i++)
	{
		a[i]=a[i+1]-a[i];
		next[i]=i+1,pre[i+1]=i;
		insert(i);
	}
	for(i=1;i<=m;i++)
	{
		x=f[1]; ans+=a[x];
		if(pre[x]==0&&next[x]==n) break;
		if(pre[x]==0)
		{
			erase(x),erase(next[x]);
			pre[next[next[x]]]=0;
		}
		else if(next[x]==n)
		{
			erase(x),erase(pre[x]);
			next[pre[pre[x]]]=n;
		}
		else{
			erase(x),erase(pre[x]),erase(next[x]);
			a[x]=a[pre[x]]+a[next[x]]-a[x];
			insert(x);
			pre[x]=pre[pre[x]]; next[pre[x]]=x;
			next[x]=next[next[x]]; pre[next[x]]=x;
		}
	}
	cout<<ans<<endl;
	return 0; 
}
```




---


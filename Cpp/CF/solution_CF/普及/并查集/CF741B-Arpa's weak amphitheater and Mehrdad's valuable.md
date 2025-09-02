# Arpa's weak amphitheater and Mehrdad's valuable

## 题目描述

有 $n$ 个人 $(1\le n\le1000)$。每个人有一个重量 $w_i(1\le w_i\le 1000)$ 和一个魅力值 $b_i(1\le b_i\le 10^6)$。 $n$ 个人之间有 $m(1\le m\le\min(\frac{n\times(n-1)}{2}, 10^5))$ 个关系。第 $i$ 个关系由两个数字 $x_i$ 和 $y_i$ 组成，表示第 $x_i$ 个人和第 $y_i$ 个人是朋友，朋友关系是双向的。

已知若 $a$ 和 $b$ 是朋友，$b$ 和 $c$ 是朋友，则 $a$ 和 $c$ 是朋友。 现在 Mehrdad 要邀请一些人来到派对，使这些人的重量总和不超过 $w\ (1\le w\le1000)$，且魅力值总和尽量大。同一个朋友圈里的人，只能邀请其中的一个人，或者全部人，或者一个人也不邀请。

## 样例 #1

### 输入

```
3 1 5
3 2 5
2 4 2
1 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 2 11
2 4 6 6
6 4 2 1
1 2
2 3
```

### 输出

```
7
```

# 题解

## 作者：星空记逸 (赞：5)

![](https://cdn.luogu.com.cn/upload/image_hosting/ioleite7.png)


一道 $CF$ 好题。

先看**题意**：

1. “朋友关系是双向的，已知若 $a$ 和 $b$ 是朋友，$b$ 和 $c$ 是朋友，则 $a$ 和 $c$ 是朋友。”

 明显可以用**并查集**的数据结构来维护这个朋友关系。

2. 现在 $Mehrdad$ 要邀请一些人来到派对，使这些人的重量总和不超过 $wi(1<=wi<=1000)$，且魅力值总和尽量大。同一个朋友圈里的人，只能邀请其中的一个人，或者全部人，或者一个人也不邀请。

是不是很眼熟？

引用一段分组背包 $DP$ 的题意：

- 有 $N$ 件物品和一个容量为 $V$ 的背包。第i件物品的费用是 $c[i]$，价值是 $w[i]$。这些物品被划分为若干组，每组中的物品互相冲突，最多选一件。求解将哪些物品装入背包可使这些物品的费用总和不超过背包容量，且价值总和最大。

可以看到，分组背包中一组中的情况为选一件或不选，而本题则可以**选一件**，**选全部**或**不选**。

那如何转化呢？

 只要将选**全部**的情况看作是选一件重量和魅力值都是该组人员**总和**的物品，就可以将情况转化为分组背包了。



------------

下面是分组背包板子：

- 设 $f[v]$ 表示花费费用 v 能取得的最大权值，从而得到柿子↓

 $f[j] = \max (f[j],f[j-w[i]]+b[i]);$

伪代码如下：

```cpp
for 所有的组 k
    for v=V..0
        for 所有的 i 属于组 k
            f[v]=max{f[v],f[v-c[i]]+w[i]}
```



结束了？

但本题还有一点。

样例可以发现本题中还可能会存在~~不会社交~~的人（合情合理），即他一个人一组的情况，此时选一件和选全部相同，就不用转换了。



------------


全部代码如下：

```cpp
#include<bits/stdc++.h>
#define N 1005
using namespace std;
int n,m,wi;
int fa[N],f[N],gr[N][N<<1],w[N<<1],b[N<<1];

//fa 记录并查集各点的根节点 
//gr[i][j]记录当前组根节点为 i、第 j 个点的下标 ，
//gr[i][0]记录当前根节点为 i 的组有几个人 

int find(int x){ //并查集路径压缩板子 
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}

int main(){
	scanf("%d%d%d",&n,&m,&wi);
	for(int i=1;i<=n;i++) fa[i]=i; //并查集数组初始化 
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		if(find(x)!=find(y))
			fa[find(x)]=find(y); //维护关系 
	}
	for(int i=1;i<=n;i++){
		gr[find(i)][0]++;
		gr[find(i)][gr[find(i)][0]]=i; //分组 
	}
	int js=n; //记录选择总数 
	for(int i=1;i<=n;i++){
		if(gr[i][0]>1){ //一组中人数大于一 
			gr[i][0]++,js++;
			gr[i][gr[i][0]]=js;
			for(int j=1;j<gr[i][0];j++){
				w[js]+=w[gr[i][j]];
				b[js]+=b[gr[i][j]]; //将该组总和作为一个新选择加入 
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!gr[i][0]) continue;
		for(int j=wi;j>=0;j--)
			for(int k=1;k<=gr[i][0];k++){
				int no=gr[i][k]; //当前点下标 
				if(j-w[no]>=0)
					f[j]=max(f[j],f[j-w[no]]+b[no]); //分组背包板子 
			}			
	}
	printf("%d\n",f[wi]);
	return 0;
}
```
~~完结撒花~~

---

## 作者：Bitter_Tea (赞：2)

本题考察的主要是并查集和分组背包

因为朋友的关系满足传递性，即$A$是$B$的朋友，$B$是$C$的朋友，那么$A$也是$C$的朋友。于是我们便可以用并查集很好地维护出一个朋友圈里的人了。

不懂的同学详见[并查集模板](https://www.luogu.com.cn/problem/P3367)


至于分组背包，则是$01$背包的延伸了，三层$for$循环顺序不要颠倒

不懂的同学详见[分组背包模板](https://www.luogu.com.cn/problem/P1757)

当我们学会上面两个模板题之后，此题就很简单啦。


我们每个朋友圈只能邀请一个人，全邀请或者都不邀请。那么我们直接把一个朋友圈里的人全加起来算作一个人的就好了。

我的做法是用$stl$中的$vector$这个容器，一开始给每个动态数组里面加一个空的结构体，表示该朋友圈的加和。然后我们进行统计的时候顺便加上即可。

下面给出代码。


$Code$
```cpp
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;
const int N=1005;
struct D{int w,v;}e[N],c;
int f[N],dp[N];
int n,m,w;
vector<D> q[N];
int find(int x) {return f[x]==x?x:f[x]=find(f[x]);}
int main()
{
	scanf("%d%d%d",&n,&m,&w);
	for(int i=1;i<=n;i++)
	scanf("%d",&e[i].w),f[i]=i;
	for(int i=1;i<=n;i++)
	scanf("%d",&e[i].v);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		int fx=find(x),fy=find(y);
		f[fx]=fy;
	}
	for(int i=1;i<=n;i++)
	{
		c.v=0;c.w=0;
		q[i].push_back(c);
	}
	for(int i=1;i<=n;i++)
	{
		int fx=find(i);
		c.v=e[i].v;c.w=e[i].w;
		q[fx][0].v+=c.v;q[fx][0].w+=c.w;
		q[fx].push_back(c);
	}
	for(int i=1;i<=n;i++)
	{
		if(f[i]!=i) continue;
		for(int j=w;j>=0;j--)
		for(int k=0;k<q[i].size();k++)
		{
			if(q[i][k].w>j) continue;
			dp[j]=max(dp[j],dp[ j-q[i][k].w ]+q[i][k].v);
		}
	}
	printf("%d\n",dp[w]);
	return 0;
}
```


---

## 作者：zyc____ (赞：2)

### 题意：
你有n个人要邀请,每个人都有2个属性,重量和魅力值，并且这些人会组成一些朋友圈。对于每个朋友圈,你只能选择全部的人,或者只选一个人,问不超过w的重量时,最大的魅力值能是多少?

### 题解： 
这是分组背包,这题的思路就是优先选择全部的朋友圈，即连通块,之后用并查集去判断,是否是一个连通块有多个人?
如果是,那么继续细分dp,这时的dp就代表只选一个的情况。
如果不是,那就和01背包一样了。

这题有两个地方比较坑，一是要用并查集判连通块，二是判完还要分开dp，想两个不同的dp方程，~~像我这种菜鸡就想了很久~~
```cpp
#include <bits/stdc++.h>
using namespace std;

int dp[1010],f[1010],w[1010],b[1010],n,m,x,y,size;
vector<int> v[1010];

int sf(int x){
    return f[x]==x?x:f[x]=sf(f[x]);
}

int main(){  
    ios::sync_with_stdio(false);
    cin>>n>>m>>size;
    for(int i=1;i<=n;i++) f[i]=i,v[i].clear();
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        f[sf(x)]=sf(y);
    } 
    for(int i=1;i<=n;i++) v[sf(i)].push_back(i); 
    memset(dp,0,sizeof(dp));  
    for(int i=1;i<=n;i++) 
        if(sf(i)==i){  
            for(int j=size;j>=0;j--){  
                int W=0,B=0;  
                for(int k=0;k<v[i].size();k++){  
                    W+=w[v[i][k]];
                    B+=b[v[i][k]];  
                    if(j>=w[v[i][k]]) dp[j]=max(dp[j],dp[j-w[v[i][k]]]+b[v[i][k]]);  
                }
                if(j>=W) dp[j]=max(dp[j],dp[j-W]+B);  
            }  
        }
    cout<<dp[size];  
} 
```


---

## 作者：李尧 (赞：2)

思想很简单啊，并查集和背包（就如标签一样）

~~我亲眼见证了这题从蓝题变成紫题（世纪性的一幕）~~

~~别误会，我就写了不到半小时，毕竟我只是个蒟蒻，不会刚省选题的，真的是它突然变了~~

介绍一下思想

首先，我们要把所有的朋友放在一个并查集内，这很简单，只要会打并查集模板就好了

然后，我们想一下，只能找一个朋友或者找全部或者不找，是不是很眼熟啊？没错，就是我们的分组背包！

只要把同一个并查集内的元素放到一个组内，然后载把这个并查集中所有元素的总和作为该组中的一个元素就好了（想一下是不是要么找一个，要么不找，要么找全部）

还有一个注意点（虽然我从一开始就没被坑），但是还是提醒一下，注意如果一个并查集内只有一个元素，那么就不要把该并查集内所有元素总和加入分组背包了（克隆人类是违法的！）

下面放代码
```
#include <bits/stdc++.h>
using namespace std;
int n,m,wt,w[1007],b[1007],a[1007],num[1007],totw[1007],totb[1007],cnt;//解释一下
//n：初始人数 m：关系数 wt:weight tot 最高体重和
//w，b数组：初始体重及魅力 a数组：记录每一个并查集标志数（即该组内所有人的father）所属于的组数，由此来将一个并查集中的元素放入一个组 num数组：记录每一个组内元素个数（不含所有元素和，这个后面加） totw，totb数组：记录每一个组的w及b之和 cnt：记录组数
int fa[1007],d[1007][1007],x,y,f[1007];
//fa数组：并查集 d数组：记录每一个组别内的每一个元素的编号（是编号哦！！） x，y ： 读入工具 f数组：记录最大魅力和，即背包
int find(int x){
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);//并查集+路径压缩
}
int main(){
	scanf("%d%d%d",&n,&m,&wt);
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	for(int i=1;i<=n;i++) fa[i]=i;//读入初始化
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		int p=find(x);
		int q=find(y);
		if(p!=q) fa[p]=q;//构造并查集
	} 
	for(int i=1;i<=n;i++){
		int p=find(i);
		if(a[p]==0) a[p]=++cnt;//新建组别，通过标志数帮每一个元素找到自己的组别
		d[a[p]][++num[a[p]]]=i;//为组别内加元素
		totw[a[p]]+=w[i];totb[a[p]]+=b[i];//更新该组别总重，总魅力
	}
	for(int i=1;i<=cnt;i++){
		if(!(totw[i]==w[d[i][1]]&&totb[i]==b[d[i][1]])){//上面的注意点
			d[i][++num[i]]=n+1;//将组别的总和作为最后一个元素加入组别
			w[n+1]=totw[i];b[n+1]=totb[i];
		}
		for(int v=wt;v>=0;v--)
			for(int j=1;j<=num[i];j++)
				if(v>=w[d[i][j]])
					f[v]=max(f[v],f[v-w[d[i][j]]]+b[d[i][j]]);//熟悉的背包
	}
	printf("%d",f[wt]);
	return 0;
}
```

希望大家都AC，但是代码不要复制哦

---

## 作者：hy233 (赞：0)

## 题目分析
- 对于朋友之间的关系，我们可以使用并查集维护出朋友圈；
- 对于每一个朋友圈，要么只选择其中一个人，要么全选，我们将全选的情况合成一个“新人”来做即可；
- 于是就变成了经典的分组背包（不会的见 [P1757](https://www.luogu.com.cn/problem/P1757) ），大力 dp 即可。

时间复杂度 $O(nw)$，可以通过本题。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1005;
int f[N]; //并查集
int find(int x)
{
	return f[x]==x?x:f[x]=find(f[x]); 
}
int w[N],b[N];
int s[N],cnt; //存储每个朋友圈的代表点
vector<int> p[N]; //存储每个朋友圈的人编号 
int sw[N],sb[N]; //存储每个联通块全选的总和 
int dp[N];
int main()
{
	int n=rd(),m=rd(),W=rd();
	for(int i=1;i<=n;i++)	
		f[i]=i; 
	for(int i=1;i<=n;i++)
		w[i]=rd();
	for(int i=1;i<=n;i++)
		b[i]=rd();
	while(m--) //并查集合并两点 
	{
		int u=rd(),v=rd();
		int fu=find(u);
		int fv=find(v);
		if(fu!=fv)
			f[fu]=fv;
	}
	for(int i=1;i<=n;i++)
	{
		int fi=find(i); //找出所在联通块 
		if(fi==i) //是代表点 
			s[++cnt]=i;
		p[fi].push_back(i);
		sw[fi]+=w[i];
		sb[fi]+=b[i];
	} 
	for(int i=1;i<=cnt;i++)
		for(int j=W;j>=0;j--)
		{
			for(int k=0;k<p[s[i]].size();k++)
			{
				int u=p[s[i]][k];
				if(j>=w[u])
					dp[j]=max(dp[j],dp[j-w[u]]+b[u]);
			}
			if(j>=sw[s[i]])
				dp[j]=max(dp[j],dp[j-sw[s[i]]]+sb[s[i]]);
		}
	
	int ans=0;
	for(int i=0;i<=W;i++)
		ans=max(ans,dp[i]);
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：天亮codekiller (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF741B)
# 并查集+分组背包

知识点传送门：

[并查集模板](https://www.luogu.com.cn/problem/P3367)

[分组背包模板](https://www.luogu.com.cn/problem/P1757)

因为题目中说到朋友关系的解释：

已知若 $a$ 和 $b$ 是朋友，$b$ 和 $c$ 是朋友，则 $a$ 和 $c$ 是朋友

可以得知朋友关系具有传递性，所以适合用并查集来解决。至于整个组的信息的存储，可以使用“边带权”的并查集。

我们将重量看做体积，将 $beauty$ 度看做权值，于是因为“同一个朋友圈里的人，只能邀请其中的一个人，或者全部人，或者一个人也不邀请”这句话，明显是分组背包的特征，所以用分组背包来解决。

具体细节见代码注释：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int SYX=1005;//我的个人码风，可以理解成MAXN 
int n,m,v;//n,m如题意所述，v就是最大重量的限制 
int w[SYX],b[SYX];//含义和题目相同 
int fa[SYX],totw[SYX],totb[SYX],x,y;//并查集的组分，父指针，组内总重，总beauty值 
int f[SYX],cost[SYX][SYX],value[SYX][SYX],cnt[SYX],type,order[SYX];
//f数组是背包，
//cost[i][j]为第i组第j个物品的重量（体积），
//value[i][j]为第i组第j个物品的beauty值（权值），
//cnt[i]为第i组的成员数（第i组的总物品数还要加上整个组这一种方案），
//type为物品的总数，order是每一种物品在cost与value数组的第一维的位置 
int ans;//ans为答案 
bool vis[SYX];//vis数组是每一个元素对应的组有没有被访问过，方便计数 
int find(int x){//并查集基本操作 
	return (fa[x]==x)?x:fa[x]=find(fa[x]);
}
int main(){
	scanf("%d%d%d",&n,&m,&v);
	for(int i=1;i<=n;++i)scanf("%d",&w[i]);
	for(int i=1;i<=n;++i)scanf("%d",&b[i]);//读入环节 
	for(int i=1;i<=n;++i){
		fa[i]=i;//并查集初始化 
		totw[i]=w[i];//附加信息 
		totb[i]=b[i];
	}
	for(int i=1;i<=m;++i){
		scanf("%d%d",&x,&y);
		if(find(x)!=find(y)){//如果朋友不在一个集合中，就合并 
			totw[find(y)]+=totw[find(x)];
			totb[find(y)]+=totb[find(x)];
			fa[find(x)]=find(y);//改变父指针一定要在合并附加消息后！ 
		}
	}
	for(int i=1;i<=n;++i){
		int p=find(i);
		if(!vis[p]){//如果是一个新的组，就重新开辟一维 
			vis[p]=true;//标记这个组访问过了 
			order[p]=++type;//组的总数加1 
			cost[type][0]=totw[p];//利用0这一维度存储总和，避免了在最后加入总和的麻烦 
			value[type][0]=totb[p];
		}
		cost[order[p]][++cnt[p]]=w[i];//记录每一个点的信息 
		value[order[p]][cnt[p]]=b[i];
	}
	memset(f,0xcf,sizeof(f));//将f数组初始化为一个很小的负数 
	f[0]=0;//初始化f[0]=0，都是分组背包的基本步骤 
	for(int i=1;i<=type;++i)//阶段 
		for(int j=v;j>=0;--j)//状态 
			for(int k=0;cost[i][k];++k)//决策，注意k从0开始，当cost[i][k]为0是就退出 
				if(j>=cost[i][k])
					f[j]=max(f[j],f[j-cost[i][k]]+value[i][k]);//状态转移 
	for(int i=1;i<=v;++i)
		ans=max(ans,f[i]);//在所有解中寻找最大值 
	printf("%d",ans);//输出答案 
	return 0;
}
```


---

## 作者：漠寒 (赞：0)

## 分析

分组背包加并查集。

本题的并查集是最基本的满足传递性的朋友关系，所以直接合并即可。

然后用背包分组别进行运算，$f[i]$ 表示计算了前面的组别后 $i$ 的重量最多多少魅力值，$g[i]$ 表示计算当前组后的对应答案，为保证分组正确性，避免在计算一个组时将单个个体计算多次，转移计算 $g$ 时只能用 $f$。在计算完后再将 $g$ 的答案更新给 $f$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void read(int &res){
	int f=1;
	res=0;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
	res*=f;
}
int n,m,w;
int vis[1005];
int fa[1005];
int f[1005],g[1005];
int a[1005],b[1005];
inline int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
signed main()
{
	read(n);read(m);read(w);
	for(int i=1;i<=n;i++)read(a[i]),fa[i]=i;
	for(int i=1;i<=n;i++)read(b[i]);
	//并查集 
	for(int i=1;i<=m;i++){
		int x,y;
		read(x);read(y);
		int kx=find(x),ky=find(y);
		if(kx==ky)continue;
		fa[kx]=ky;
	}
	//分组背包 
	for(int i=1;i<=n;i++){
		int x=find(i);
		if(!vis[x]){
			for(int j=1;j<=w;j++)g[j]=f[j];//0个 
			int sa,sb;
			sa=sb=0;
			for(int j=1;j<=n;j++){
				if(find(j)==x){//选一个
					sa+=a[j];
					sb+=b[j];
					for(int k=w;k>=a[j];k--){
						g[k]=max(g[k],f[k-a[j]]+b[j]);
					}
				}
			}
			for(int k=w;k>=sa;k--){//全选 
				g[k]=max(g[k],f[k-sa]+sb);
			}
			for(int i=1;i<=w;i++)f[i]=g[i];
			vis[x]=1;
		}
	}
	int ans=0;
	for(int i=0;i<=w;i++)ans=max(ans,f[i]);
	cout<<ans;
	return 0;
}



```


---

## 作者：珅肐 (赞：0)

$vector$实现

因为在一群朋友内只有三种情况：只选一个、都选、都不选

我们很自然地想到把都选的打包成一个新人？？

情况就只剩两种：任选一个或者都不选。

**分组背包。**

在此之前我们需要把同是朋友的用并查集并起来，操作比较简单

**！** 还有一个坑点：

分组内只有一个人的不可以添加新人！

分组内只有一个人的不可以添加新人！

分组内只有一个人的不可以添加新人！

重要的事情说三遍。

#### 详见代码：

```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
#include<vector>
using namespace std;
inline int read(){//快读，可快了
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
int w[2007],v[2007],fa[1007],f[1007];
//w是重量，v是魅力值，即题目中的b。注意，这两个数组要开两倍（至少1.5倍），因为加的新人最多有500个。
vector<int> ve[1007];//ve[i]表示第i个分组，里面存的是编号
inline int find(int x){//并查集常规操作
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
	int n=read(),m=read(),W=read(),p=n;
	for(int i=1;i<=n;++i)w[i]=read(),fa[i]=i;//并查集初始化
	for(int i=1;i<=n;++i)v[i]=read();
	for(int i=1;i<=m;++i){
		int a=find(read()),b=find(read());//并查集常规操作
		if(a!=b)fa[b]=a;
	}
	for(int i=1;i<=n;++i)ve[find(i)].push_back(i);//这里用i的祖先来表示他所属的分组
	for(int i=1;i<=n;++i){
		if(ve[i].size()<=1)continue;//如果只有一个人或者没有的话，不可以添加新人。
		ve[i].push_back(++p);//p是人数，初始化为n
		for(int j=0;j<ve[i].size()-1;++j)w[p]+=w[ve[i][j]],v[p]+=v[ve[i][j]];//新人加和
	}
	for(int k=1;k<=n;++k){//普通的分组背包
		if(!ve[k].size())continue;
		for(int j=W;j>=0;--j)
			for(int i=0;i<ve[k].size();++i){
				int o=ve[k][i];//o是编号
				if(j>=w[o])f[j]=max(f[j],f[j-w[o]]+v[o]);
			}
	}
	printf("%d\n",f[W]);//输出
	return 0;//好习惯
}

```


---

## 作者：AC自动机 (赞：0)

### 算法
分组背包   并查集

### 思路
并不是很难的一道题，首先用并查集把所有的朋友处理出来，每一堆朋友都是一个小种类，再处理出来这一堆朋友的重量和和美丽度的和，放入这堆朋友中，这样就把所有人分成了很多个集合，每个集合中都有单独的个人和总和，每个集合中只能选一个元素或不选，因此就是一个分组背包。dp方程不难推出：
```cpp
	for(register int i=1;i<=cnt;i++){  // xuan le ji zu
		for(register int j=1005;j>=0;j--){
			for(register int k=0;k<v[i].size();k++){
				if(j-a[v[i][k]].w<0)continue;
				dp[j]=max(dp[j],dp[j-a[v[i][k]].w]+a[v[i][k]].b);
			}
			if(j-friendw[i]>=0){
				dp[j]=max(dp[j],dp[j-friendw[i]]+friendv[i]);
			}
		}
	}
```

#### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
vector<int>v[1005];
struct nod{
	int w,b,f;
};
nod a[1005]; 
int fa[1005];
int friendw[1005];
int friendv[1005];
int dp[1000005];
int n,m,w;
int getfa(int x){
	if(fa[x]!=x) return fa[x]=getfa(fa[x]);
	else return fa[x];
}
int ini(){
	for(register int i=1;i<=1004;i++){
		fa[i]=i;
	}
}
int unio(int x,int y){
	fa[getfa(x)]=fa[getfa(y)];
}
int main(){
	ini();
	cin>>n>>m>>w;
	for(register int i=1;i<=n;i++){
		cin>>a[i].w;
	}
	for(register int i=1;i<=n;i++){
		cin>>a[i].b;
	}
	int cnt=0;
	for(register int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		if(getfa(x)!=getfa(y))unio(x,y);
	}
	for(register int i=1;i<=n;i++){
		if(a[getfa(i)].f==0){
			a[getfa(i)].f=++cnt;
			v[cnt].push_back(i);
		}
		else {
			v[a[getfa(i)].f].push_back(i);
		}
	}
	//----------------------------------
	for(register int i=1;i<=cnt;i++){
		for(register int j=0;j<v[i].size();j++){
			friendv[i]+=a[v[i][j]].b;
			friendw[i]+=a[v[i][j]].w;
		}
	}
	for(register int i=1;i<=cnt;i++){  // xuan le ji zu
		for(register int j=1005;j>=0;j--){
			for(register int k=0;k<v[i].size();k++){
				if(j-a[v[i][k]].w<0)continue;
				dp[j]=max(dp[j],dp[j-a[v[i][k]].w]+a[v[i][k]].b);
			}
			if(j-friendw[i]>=0){
				dp[j]=max(dp[j],dp[j-friendw[i]]+friendv[i]);
			}
		}
	}
	cout<<dp[w]<<endl;
}
```

---


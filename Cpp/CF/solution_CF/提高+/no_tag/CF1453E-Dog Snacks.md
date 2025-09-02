# Dog Snacks

## 题目描述

Gildong is playing with his dog, Badugi. They're at a park that has $ n $ intersections and $ n-1 $ bidirectional roads, each $ 1 $ meter in length and connecting two intersections with each other. The intersections are numbered from $ 1 $ to $ n $ , and for every $ a $ and $ b $ ( $ 1 \le a, b \le n $ ), it is possible to get to the $ b $ -th intersection from the $ a $ -th intersection using some set of roads.

Gildong has put one snack at every intersection of the park. Now Gildong will give Badugi a mission to eat all of the snacks. Badugi starts at the $ 1 $ -st intersection, and he will move by the following rules:

- Badugi looks for snacks that are as close to him as possible. Here, the distance is the length of the shortest path from Badugi's current location to the intersection with the snack. However, Badugi's sense of smell is limited to $ k $ meters, so he can only find snacks that are less than or equal to $ k $ meters away from himself. If he cannot find any such snack, he fails the mission.
- Among all the snacks that Badugi can smell from his current location, he chooses a snack that minimizes the distance he needs to travel from his current intersection. If there are multiple such snacks, Badugi will choose one arbitrarily.
- He repeats this process until he eats all $ n $ snacks. After that, he has to find the $ 1 $ -st intersection again which also must be less than or equal to $ k $ meters away from the last snack he just ate. If he manages to find it, he completes the mission. Otherwise, he fails the mission.

Unfortunately, Gildong doesn't know the value of $ k $ . So, he wants you to find the minimum value of $ k $ that makes it possible for Badugi to complete his mission, if Badugi moves optimally.

## 说明/提示

In the first case, Badugi can complete his mission with $ k=2 $ by moving as follows:

1. Initially, Badugi is at the $ 1 $ -st intersection. The closest snack is obviously at the $ 1 $ -st intersection, so he just eats it.
2. Next, he looks for the closest snack, which can be either the one at the $ 2 $ -nd or the one at the $ 3 $ -rd intersection. Assume that he chooses the $ 2 $ -nd intersection. He moves to the $ 2 $ -nd intersection, which is $ 1 $ meter away, and eats the snack.
3. Now the only remaining snack is on the $ 3 $ -rd intersection, and he needs to move along $ 2 $ paths to get to it.
4. After eating the snack at the $ 3 $ -rd intersection, he needs to find the $ 1 $ -st intersection again, which is only $ 1 $ meter away. As he gets back to it, he completes the mission.

In the second case, the only possible sequence of moves he can make is $ 1 $ – $ 2 $ – $ 3 $ – $ 4 $ – $ 1 $ . Since the distance between the $ 4 $ -th intersection and the $ 1 $ -st intersection is $ 3 $ , $ k $ needs to be at least $ 3 $ for Badugi to complete his mission.

In the third case, Badugi can make his moves as follows: $ 1 $ – $ 5 $ – $ 6 $ – $ 7 $ – $ 8 $ – $ 2 $ – $ 3 $ – $ 4 $ – $ 1 $ . It can be shown that this is the only possible sequence of moves for Badugi to complete his mission with $ k=3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1453E/41c4ff4d910e8ed4dbc3cb32cd3891fb337b98b3.png)

## 样例 #1

### 输入

```
3
3
1 2
1 3
4
1 2
2 3
3 4
8
1 2
2 3
3 4
1 5
5 6
6 7
5 8```

### 输出

```
2
3
3```

# 题解

## 作者：Reywmp (赞：7)

- ## CF1453E Dog Snacks

简单树形 $dp$ 。

-----------

- ### Prelude

往树形 $dp$ 直接想就可以了，因为我们发现既然要走完所有点，那么很显然是每个节点的子树内部跑完才会去跑别的子树。现在只需要考虑怎么走 $k$ 最小。


------------

- ### Solution

观察这么一种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/vpuc812y.png)

我们发现，无论先从哪个子节点下去，貌似得到的 $k$ 都会是最长链的长度，因为你肯定要从那个最深的叶子节点回到 $R$ 。

但是如果我们把这颗子树接到另一种情况上。

![](https://cdn.luogu.com.cn/upload/image_hosting/c6wbru9e.png)

因为我们一定是从根走到子树上的节点，我们走**”进去“**的时候其实是无所谓的，因为都是没有走过的节点，所以最近的距离为 $1$ 的都可以走。

于是我们只需要考率回来的操作，因为刚才那个情况全是链，所以感觉怎么走好像都无所谓啊，但是如果我们在子树的根上面接的是唯一的一条很长链，显然这上面的点都被走过了，所以每走一步都会危及到 $k$ 的大小。我们发现从一个叶子节点走回去的路径也是一条链，是这颗子树上的一条链接上上面那条长链。对于上面那个情况我们最后直接就可以从 $6$ 走到 $x$ ，如果从 $5$ 走回 $x$ 显然很劣。

那么就很显然了，我们只需要在最后一次回来的时候走最短的链。那么策略就是每次从最长的向下走，保证最后走回来的是那条最短。也就是回去的路程一般考虑 $\min+1$ 。

但是在子树间转移时，我们答案会不可避免地变成 $\max+1$ 。

所以我们其实一直在考虑 $2$ 个问题：回去的路程 $\min+1$ 和 子树转移的路程 $\max+1$

我们记录状态 $f_i$ 为距离子树中最近叶子节点的距离。

所以每次向上跳的时候，我们考虑用不同子树的最小链合并状态。那就是：
$$
f_u=\min\{f_u,f_v+1[(u,v)\in \mathbf E]\}
$$
途中我们还需要记录答案，答案就是所有子树状态最大值 $+1$ ，因为根据第一张图，而且我们要回到上一个节点，所以是最大值 $+1$ 。
$$
ans_u=\max\{ f_v+1\}[(u,v)\in\mathbf E]
$$
**但是我们只有在一个节点有多个子树才会更新这个答案**。

但是这样的话我们会发现一个问题，那就是如果上面那个子树全是链的图这样做答案是不对的。

我们发现，根节点是不需要遵从这个规律的，因为最后一次回到根节点我们就没有再下去的操作了。

什么意思呢，就是说，我们从一个子树回到父亲节点很显然要继续走这个父亲节点的其他子树，或者跳到上面去，但是根节点的最后一次不需要，也就是说我们没有子树转移的路程可以考虑，我们可以记录下次大链 $+1$ ，其等效于子树转移的路程，这样也可以在根节点求最优了。


-------------------------

- ### Code

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>

#define INL inline

using namespace std;

INL int read()
{
	int x=0,w=1;char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	if(ch=='-')w=-1,ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();
	return x*w;
}

const int N=4e5+5;

struct Rey
{
	int nxt,to;
}e[N<<1];

int n,head[N],cnt;
int f[N],ans;

INL void add(int u,int v)
{
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}

void dfs(int x,int fa)
{
	int mxn,sec_mxn,tot;
	mxn=sec_mxn=tot=0;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int go=e[i].to;
		if(go==fa)continue;
		dfs(go,x);
		tot++;//记录子树个数
		f[x]=min(f[x],f[go]+1);
		if(f[go]+1>mxn)sec_mxn=mxn,mxn=f[go]+1;
		else if(f[go]+1>sec_mxn)sec_mxn=f[go]+1;//次大，给根转移用
	}
	if(tot==0){f[x]=0;return ;}//叶子节点直接返回
	if(x==1)//根节点特判
	{
		if(tot==1)ans=max(ans,mxn);
		else ans=max(ans,max(sec_mxn+1,mxn));
	}
	else if(tot>=2)ans=max(ans,mxn+1);//只有多个子树才需要转移记录答案
}

int main()
{
	int t=read();
	while(t--)
	{
		ans=0;
		memset(f,127,sizeof(f));
		memset(head,0,sizeof(head));
		cnt=0;
		n=read();
		for(int i=1;i<n;i++)
		{
			int x=read(),y=read();
			add(x,y);add(y,x);
		}
		dfs(1,0);
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：LinkWish (赞：2)

这题第一眼就想到了二分答案，将最优性问题变成判定性问题。现在问题就变成了：对于给定的 $k$，狗子能不能合法地走完。

因为每次都要去任意一个距离最近的节点，所以容易贪心地想到，对于一个节点 $x$，肯定是一棵一棵子树地走最优。我们设 $f_i$ 表示以 $i$ 为根的子树走完后还剩下多少步，这里的“剩下的步数”指的是走完回到根节点后还能够继续走的距离，如果以 $i $ 为根的子树无法合法地走完，那么令 $f_i=-1$。

显然，对于节点 $x$，只要他的任意儿子 $y$ 满足 $f_y\ge2$，那么以 $x$ 为根的子树就一定可以走完，如果任意一个儿子 $y$ 满足 $f_y\le1$，那就无法走完，但特殊地，如果节点 $1$ 有至多一个儿子 $y$ 满足 $f_y=1$，还是可以走完的，因为刚好回到了节点 $1$ 上。

转移方程也很好想，因为我们要令 $f_i$ 尽量大，所以 $f_i=\max\limits_{v\in son_i} f_v -1$。

最后在判定的时候只要 $f_1\ne -1$ 就可以，否则不行。

程序只给出主体部分，主要是前面一部分的模板有一些影响观感，而且给出主体已经能够辅助理解。


```cpp
//Linkwish's code
const int N=200005;
int n;
vector<int> e[N];
int f[N];
void dp(int x,int fa,const int k){
	if(e[x].size()==1&&x!=1){
		f[x]=k;
		return ;
	}
	int cnt=0,mx=0;
	for(int to:e[x]){
		if(to!=fa){
			dp(to,x,k);
			if(f[to]==-1){
				f[x]=-1;
				return ;
			}
			if(f[to]<=1){
				if(x==1){
					if(cnt){
						f[x]=-1;
						return ;
					}
					else cnt++;
				}
				else{
					f[x]=-1;
					return ;
				}
			}
			mx=max(mx,f[to]);
		}
	}
	f[x]=mx-1;
}
inline bool check(const int val){
	for(int i=1;i<=n;i++)f[i]=-1;
	dp(1,0,val);
	return f[1]!=-1;
}
inline void solve(){
	read(n);
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1,x,y;i<n;i++){
		read(x),read(y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	int l=1,r=n,mid,res=iinf;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))r=mid-1,res=mid;
		else l=mid+1;
	}
	writeln(res);
}
```


---

## 作者：Priestess_SLG (赞：0)

感谢这个题让可爱 @[aimat](/user/746544) 姐姐女装三次！！！/se/se/se

~~真可爱真可爱~~

易得枚举到以 $j$ 为根节点的子树时，设其直接儿子节点的编号分别为 $i_1,i_2,\ldots,i_k$，必然是获得一个 $1\sim k$ 的排列 $p_1,p_2,\ldots,p_k$，然后以 $i_{p_1},i_{p_2},\ldots,i_{p_k}$ 的顺序遍历子树更为优秀。

首先二分答案为 $k$，然后钦定 $1$ 为根，考虑设 $f_i$ 表示以 $i$ 为根节点的子树中遍历完所有的结点，最后一步跳到子树外面，这个点距离 $i$ 最远距离为多少。特殊的若不能满足这样的条件那么令 $f_i=-1$。更特殊的，若 $i=1$ 则不需要跳到子树外面则需要特殊判断，否则，枚举其所有直接儿子节点 $i_1,i_2,\ldots,i_p$：

+ $p=0$，则直接有 $f_i=k$。
+ $p>0$，则计算其 $i_1,i_2,\ldots,i_p$ 的 $f$ 值，若其中存在一个元素的 $f$ 值为 $-1$，或者至少两个元素的 $f$ 值不足 $1$，则容易证明此时显然不存在任何一组合法的策略。否则，直接计算其中 $f$ 值最大的，让其最后一个访问，显然对其父亲链上结点的影响最优秀，即 $f_i=\max\limits_{j=1}^k f_{i_j}$。

总的时间复杂度为 $O(n\log n)$ 可以通过。

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define int long long
#define F(i,x,y) for(int i=x;i<=y;++i)
#define G(i,x,y) for(int i=x;i>=y;--i)
#define FD(i,x,y) for(int i=x;i*i<=y;++i)
#define GD(i,x,y) for(int i=x;i*i>=y;--i)
#define adde(x,y) z[x].eb(y);
#define Adde(x,y) z[x].eb(y),z[y].eb(x);
#define addew(x,y,w) z[x].eb(y,w)
#define Addew(x,y,w) z[x].eb(y,w),z[y].eb(x,w)
#define FIMX(X) memset(X,0x3f,sizeof X)
#define FIMI(X) memset(X,-0x3f,sizeof X)
#define FI0(X) memset(X,0,sizeof X)
#define FIN(X) memset(X,-1,sizeof X)
#define rng(X) X.begin(),X.end()
#define PII pair<int,int>
#define PDD pair<double,double>
#define PIII tuple<int,int,int>
#define VI vector<int>
#define VII vector<PII>
#define VID vector<pair<int,double>>
#define VDD vector<PDD>
using namespace std;
const int N=500100;
const int mod=998244353;
VI z[N];
int f[N],n;
//钦定1为根
//f[i] 表示 i 为根的子树, 最后一步距离 i 点的距离最小，可以跳到 i 点子树外距离 i 点最多多远
void dfs(int u,int fa,int k){
    if(u!=1&&z[u].size()<=1){
        f[u]=k;
        return;
    }
    int cnt=0;
    f[u]=0;
    for(auto &v:z[u])
        if(v!=fa){
            dfs(v,u,k);
            if(f[v]==-1){
                f[u]=-1;
                return;
            }
            if(f[v]<=1){
                if(u==1){
                    ++cnt;
                    if(cnt>1){
                        f[u]=-1;
                        return;
                    }
                }else{
                    f[u]=-1;
                    return;
                }
            }
            f[u]=max(f[u],f[v]);
        }
    --f[u];
}
int chk(int k){
    F(i,1,n)f[i]=0;
    dfs(1,0,k);
    return ~f[1];
}
void solve(unsigned __testid=1) {
    cin>>n;
    F(i,1,n)z[i].clear();
    F(i,1,n-1){
        int u,v;cin>>u>>v;
        Adde(u,v);
    }
    int l=1,r=n,best=-1;
    while(l<=r){
        int mid=l+r>>1;
        if(chk(mid))best=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<best<<'\n';
}
int32_t main(){
    freopen("flag.in","r",stdin);
    freopen("flag.out","w",stdout);
    int T;
    // T=1;
    cin>>T;
    F(_,1,T)
        solve(_);  
    return 0;
}
```

---

## 作者：PineappleSummer (赞：0)

[CF1453E Dog Snacks](https://www.luogu.com.cn/problem/CF1453E)

很明显，答案具有单调性，所以考虑二分答案，将求最小值该为判定是否可行。

由于每次都要走到离自己距离最近的节点，自然想到应该一个子树走完再走另一个。

设 $f_i$ 为走完以 $i$ 为根的子树后剩余的步数，这里的剩余步数是指走完这个子树后还能继续走的距离。特别的，当以 $i$ 为根的子树无法走完的时候，$f_i=-1$。


对于节点 $u$，如果满足任意儿子 $f_v\ge 2$，即 $\min\limits_{v\in son_u}f_v\ge 2$，则以 $x$ 为根的子树一定能够走完。

如果存在一个儿子 $f_v\le1$ 时，以 $u$ 为根的子树便走不完，此时 $f_u=-1$。特别的，如果**节点 $1$ 的子树中只存在 $1$ 个**儿子 $v$ 使得 $f_v=1$，该树是可以走完的。

对于能够走完的以 $u$ 为根的子树，$f_u=\max\limits_{v\in son_u}f_v-1$。对于叶子节点，$f_u=k$，其中 $k$ 为二分的值。

[参考代码](https://codeforces.com/contest/1453/submission/272492831)，单组数据时间复杂度 $\mathcal O(n\log n)$。

---


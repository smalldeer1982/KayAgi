# Forever Winter

## 题目描述

A snowflake graph is generated from two integers $ x $ and $ y $ , both greater than $ 1 $ , as follows:

- Start with one central vertex.
- Connect $ x $ new vertices to this central vertex.
- Connect $ y $ new vertices to each of these $ x $ vertices.

 For example, below is a snowflake graph for $ x=5 $ and $ y=3 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1829F/8093abf53ab9afd4293f2937f4849e3ca604a47a.png)The snowflake graph above has a central vertex $ 15 $ , then $ x=5 $ vertices attached to it ( $ 3 $ , $ 6 $ , $ 7 $ , $ 8 $ , and $ 20 $ ), and then $ y=3 $ vertices attached to each of those.

 Given a snowflake graph, determine the values of $ x $ and $ y $ .

## 说明/提示

The first test case is pictured in the statement. Note that the output 3 5 is incorrect, since $ x $ should be output before $ y $ .

## 样例 #1

### 输入

```
3
21 20
21 20
5 20
13 20
1 3
11 3
10 3
4 8
19 8
14 8
9 7
12 7
17 7
18 6
16 6
2 6
6 15
7 15
8 15
20 15
3 15
7 6
1 2
1 3
2 4
2 5
3 6
3 7
9 8
9 3
3 6
6 2
2 1
5 2
2 7
4 3
3 8```

### 输出

```
5 3
2 2
2 3```

# 题解

## 作者：zhlzt (赞：13)

### 做法
其实就是一道思维题，可以把一片雪花想象成一棵三层的树，那么根节点就有 $x$ 个孩子，第二层的 $x$ 个节点就各有 $y$ 个孩子，题目又保证 $x,y\ge 1$，所以度数为 $1$ 的节点就是第三层的节点个数（设第三层的节点个数为 $ans$），将与其唯一相连的一个节点放入一个不可重集合内（代码中用 STL set 实现），集合的最终元素个数即为所求的 $x$，很明显，$\dfrac{ans}{x}$ (将第三层的节点平均分配给第二层的节点作孩子）即为所求的 $y$。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt[210];vector<int>edge[210];//cnt 存度数，edge 存边
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n,m;scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++) 
			cnt[i]=0,edge[i].clear();//清空
		while(m--){
			int u,v;scanf("%d%d",&u,&v);
			edge[u].push_back(v);cnt[u]++;
			edge[v].push_back(u);cnt[v]++;
		}
		set<int>st;int ans=0;
		for(int i=1;i<=n;i++) if(cnt[i]==1){
			ans++,st.insert(edge[i][0]);
		} 
		printf("%d %d\n",st.size(),ans/st.size());
	}
	return 0;
}

```

---

## 作者：cjh20090318 (赞：4)

大家好，我是 CQ-C2024 蒟蒻 CJH。

## 题意

一个雪花图可以通过两个大于 $1$ 的整数 $x$ 和 $y$ 生成，具体步骤如下：

- 从一个中心点开始。
- 将 $x$ 个新的顶点连接到该中心点。
- 将 $y$ 个新的顶点分别连接到上述 $x$ 个新顶点中的每个顶点。

给你一个雪花图，请找出它的 $x$ 和 $y$。

## 分析

观察题面图片可以发现，一个雪花图一定是一棵无根树。

也就是说，我们求 $x$ 只需要求出树的重心即可，$x$ 的值即为重心的出度。

$y$ 的值也就是树的重心的任意一个子节点的出度减一即可。

## 注意事项

**本题有多组数据。**

所以一定要把存图的 `vector` 清空！

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n,m;
vector<int> G[202];
int rt,s[202],dp[202];。
bool vis[202];
void dfs(int x,int fa,const int sum){//求树的重心。
	s[x]=1,dp[x]=0;
	for(int v:G[x])
		if(v!=fa && !vis[v]){
			dfs(v,x,sum);
			s[x]+=s[v];//统计子树大小。
			dp[x]=max(dp[x],s[v]);
		}
	dp[x]=max(dp[x],sum-s[x]);
	if(dp[x]<dp[rt]) rt=x;
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) G[i].clear();//多测要清空邻接表！
	for(int i=1,u,v;i<=m;i++)scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	rt=0,dp[0]=202;memset(vis,0,sizeof vis);//清空访问数组。
	dfs(1,0,n);
	printf("%d %d\n",(int)G[rt].size(),(int)G[G[rt][0]].size()-1);//重心的出度和重心任意一个子节点出度减去一。
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```


---

## 作者：luqyou (赞：2)

# 题意

定义两个整数 $x,y$ 构造出的“雪花图”为：

- 创建一个根节点。

- 将根节点连上 $x$ 个点。

- 将所有非根节点都连上 $y$ 个点。

给出一张雪花图，求出它的 $x,y$。

# 思路

首先，它是一棵树。所以如果我们能够确定它的根，那么我们可以发现，深度为 $1$ 的节点数量就是 $x$，深度为 $2$ 的节点数量 $\div$ 深度为 $1$ 的节点数量就是 $y$。

考虑如何确定根节点。

容易发现如果我们将不是根节点的点拿来当做根节点，那么至少有一个点的深度 $>2$。所以我们将每个点作为根处理一遍深度，如果没有 $>2$ 深度的那个点就是根。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200+10;
int n,m,depth[maxn];
vector<int> G[maxn];
void dfs(int u,int fa,int nowdep){//处理深度
	depth[u]=nowdep;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v!=fa){
			dfs(v,u,nowdep+1);
		}
	}
}
void solve(){
	int sum1=0,sum2=0;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++){//确定根
		dfs(i,0,0);
		bool f=1;
		sum1=0;
		sum2=0;
		for(int j=1;j<=n;j++){
			if(depth[j]==1) sum1++;
			if(depth[j]==2) sum2++;
			if(depth[j]>2){
				f=0;
				break;
			}
		}
		if(f){
			break;
		}
	}
	cout<<sum1<<" "<<sum2/sum1<<endl;
	for(int i=1;i<=n;i++){
		G[i].clear();
	}
}
int main(){
 	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Elairin176 (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1829F)        
很有意思的一道题。        
我们可以从每个点的度数来考虑，我们易知有 $xy$ 个点的度数为 $1$，有 $x$ 个点的度数为 $y+1$，有 $1$ 个点的度数为 $x$。      
那么，$n=xy+x+1$。       
对于度数为 $1$ 的点，也就是 $xy$ 的值，我们可以很快求出来。      
我们设 $xy$ 为 $k$，那么我们易知 $x=n-1-k,y=\frac{k}{n-1-k}$。          
[CODE](https://www.luogu.com.cn/paste/p33bsqrd)

---

## 作者：rmzls (赞：0)

### 思路
注意到每个点的度数不超过 $1000$ ，我们把每个度数为 $i$ 的点有多少个记录为 $cnt_i$。整个数组最多只会在三个地方有值。整个数组在 $cnt_1$ 会有一个值，便是叶子个数。我们从 $2$ 开始遍历数组，若 $cnt_i=1$ 这个点便是中心点，这个度数 $i$ 便是 $x$，剩下那个有值的节点就是 $y+1$。若没有 $cnt_i=1$ 的情况，那么此时中心节点和第二层节点度数相同，即 $x=y+1$。

------------
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int ru[N],cnt[N],n,m,a,b,t,x,y;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++){
			scanf("%d%d",&a,&b);
			ru[a]++;ru[b]++;
		}
		for(int i=1;i<=n;i++){
			cnt[ru[i]]++;
		}
		for(int i=2;i<=n;i++){
			if(cnt[i]==1){
				x=i;
			}
			else if(cnt[i]>0){
				y=i-1;
			}
		}
		if(!x){
			x=y+1;
		}
		printf("%d %d\n",x,y);
		x=y=0;
		for(int i=1;i<=n;i++){
			ru[i]=0;
		}
		for(int i=1;i<=m;i++){
			cnt[i]=0;
		}
	}
	return 0;
} 
```


---

## 作者：Light_az (赞：0)

~~看了一眼提交记录，好像我的代码时间最长。~~

本题思路是暴力枚举，观察雪花这张图片我们发现中心点到任意一个点的距离一定是小于等于 $2$ 的，因此我们获取每个点到某一个点的距离，如果距离全部小于等于 $2$，那么说明这个点是中心点。

我们记中心点的儿子个数 $num$，$x$ 的值就是 $num$，而 $y$ 的值就是看中心点的儿子分别连了多少条边（除了连接中心点的那一条），即 $\frac{m-num}{num}$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(int i=j;i<=n;i++)
#define Tr(v,e) for(int v:e)
#define D double
#define ps push_back
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10,NN=1e4+10;
ll n,m,k,x,y,u,v,w,cnt=0,ans=0,t=0,l,r,len,T;
ll mn=INT_MAX,mx=0,Mod,id=1;
string s1,s2;
vector<ll> tr[N];
ll get(ll id,ll fa){//获取最大的深度
	ll sum=0;
	F(i,0,tr[id].size()-1){
		ll v=tr[id][i];
		if(v==fa) continue;
		sum=max(sum,get(v,id));
	}
	return sum+1;
}
void f(ll id){
	ll cnt=0;
	F(i,0,tr[id].size()-1){
		ll v=tr[id][i];
		if(get(v,id)!=2) return ;//大于 2 不符合中心点条件
	}
	cout<<tr[id].size()<<" "<<(m-tr[id].size())/tr[id].size()<<"\n";//num 和 (m-num)/num 的值
}
int main(){	
	cin>>T;
	while(T--){
		memset(tr,0,sizeof(tr));//清空
		cin>>n>>m;
		F(i,1,m){
			cin>>u>>v;
			tr[u].ps(v);
			tr[v].ps(u);
		}
		F(i,1,n) f(i);//枚举
	}
	
	return 0;
}

```


---

## 作者：沉石鱼惊旋 (赞：0)

>upd 2023.05.07 16:00 代码放错了，已更正。

[更好的阅读体验](http://blog.cyx2009.top/archives/169/)

# F.[Forever Winter](https://codeforces.com/contest/1829/problem/F)

## 题目翻译

> 我们定义大小 $(x,y)$ 的雪花图表示有一个节点 $u$ 连向 $x$ 个节点，这 $x$ 个节点又分别连向不同于 $u$ 的 $y$ 个节点。给定一张 $n$ 节点 $m$ 条边的雪花图，问这张雪花图的大小是什么。
> 
> 例如 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1829F/8093abf53ab9afd4293f2937f4849e3ca604a47a.png) 就是大小为 $(5,3)$ 的雪花图。
> 
> $1\leq n\leq 200,1\leq m\leq \min(\frac{n\times (n-1)}{2},1000)$。

## 题目思路

因为给出的图一定是雪花图，所以我们只需枚举它的大小。然后我们观察样例可得，我们需要有一个度数为 $x$ 的点以及 $x$ 个度数为 $y+1$ 的点（因为连到了 $x$ 个点，每个点还会往中心连一次）。

但仅仅这些还不够，我们需要判断这个 $(x,y)$ 是否满足有 $n$ 个点，即 $x\times y+1=n$。

## 完整代码



```cpp
#include<bits/stdc++.h>
using namespace std;
int deg[220];
void solve()
{
    memset(deg,0,sizeof(deg));
    int n,m;
    cin>>n>>m;
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        deg[u]++;deg[v]++;
    }
    for(int x=1;x<=200;x++)
    {
        for(int y=1;y<=200;y++)
        {
            if(x*(y+1)+1!=n)continue;
            int sx=0,sy1=0;
            for(int i=1;i<=n;i++)
            {
                if(deg[i]==x&&!sx){sx=1;continue;}
                if(deg[i]==y+1){sy1++;}
            }
            if(sx==1&&sy1==x)
            {
                cout<<x<<" "<<y<<endl;
                return;
            }
        }
    }
}
int main()
{
    int t;cin>>t;while(t--)
    solve();
    return 0;
}
```

---

## 作者：zajasi (赞：0)

## 题意
给定你一些边，需要你求出 $x$ 和 $y$，满足：某一个点延伸出去得到 $x$ 个点，这些点又延伸出去得到 $y$ 个点。
## 解题思路
观察到 $n$ 和 $m$ 特别小，所以可以直接暴力。

首先枚举中心点是谁，这样也就确定了 $x$。再看看延伸出去的点是不是又延伸出去的点数相等，这就是 $y$ 的值。到这里结束，你会发现连样例都会输出奇奇怪怪的东西，为什么呢？

其实，你需要看看那些点是不是包含了题目中所给出的所有点，不然是不符合的。

详见代码。
## AC 代码
```cpp
/*
written by : zjs123
QQ : 755328053
Wechat : zoujinshu18
CZOJ : zjs123
luogu : _JSYX_
atcoder : zajasi10
codeforces : _JSYX_
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long  
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
int t;
int n,m;
int x,y;
int h[220];
int vis[220];
int vis2[220];
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>m;
        memset(h,0,sizeof h);
        vector<int> g[220];
        set<int> s;
        memset(vis,0,sizeof vis);
        for(int i=1;i<=m;i++){
            cin>>x>>y;
            vis[x]=1;//记录某一个点有没有
            vis[y]=1;
            h[x]++;//记录某一个点引出的边数
            h[y]++;
            g[x].push_back(y);//记录某一个点引出的所有边
            g[y].push_back(x);
            s.insert(x);//记录所有节点
            s.insert(y);
        }
        for(auto&i:s){
            memset(vis2,0,sizeof vis2);//清空，这个记录按照你选的节点来说所用到的点
            int z=0;
            int f=0;
            vis2[i]=1;//你选的点被用了
            for(int j=0;j<g[i].size();j++){
                vis2[g[i][j]]=1;
                if(z==0)z=h[g[i][j]];
                else{
                    if(z!=h[g[i][j]]){
                        f=1;
                        break;
                    }
                }//以上是判断每个延伸出去的点的连接边条数相不相同
                for(int k=0;k<g[g[i][j]].size();k++){
                    vis2[g[g[i][j]][k]]=1;//记录所用到的点
                }
            }
            for(int j=1;j<=n;j++){
                if(vis[j]==1&&!vis2[j]){
                    f=1;
                    break;//如果题目中给了一个点但你选的当中没有用到，很明显是不行的
                }
            }
            if(f==0){
                cout<<h[i]<<" "<<z-1<<"\n";//z-1的原因是因为连接的边中有一条边是去中心点的
                break;
            }
        }
    }
    return 0;
}

```

---

## 作者：aeiouaoeiu (赞：0)

发现中心点的度数为 $x$，中心点延伸出的点的度数为 $y+1$，其他点的度数为 $1$，所以我们可以先寻找中心点：与它有边相连的点度数都大于 $1$，然后 $x$ 即为这个点的度数，$y$ 为与这个点有边相连的点的度数减去 $1$。
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=205;
ll n,m,deg[maxn],flag,x,y;
vector<ll> edge[maxn];
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	ll T=1,u,v;
	cin>>T;
	for(;T--;){
		cin>>n>>m;
		for(int i=1;i<=n;i++) edge[i].clear(),deg[i]=0;
		for(int i=1;i<=m;i++){
			cin>>u>>v;
			edge[u].pb(v),edge[v].pb(u);
			deg[u]++,deg[v]++;
		}
		for(int i=1;i<=n;i++){
			if(deg[i]==1) continue;
			flag=1;
			for(auto v:edge[i]){
				if(deg[v]==1){
					flag=0;
					break;
				}
			}
			if(flag){
				x=deg[i],y=deg[edge[i][0]]-1;
				break;
			}
		}
		cout<<x<<" "<<y<<"\n";
	}
	return 0;
}
```

---


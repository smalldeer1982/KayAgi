# Districts Connection

## 题目描述

There are $ n $ districts in the town, the $ i $ -th district belongs to the $ a_i $ -th bandit gang. Initially, no districts are connected to each other.

You are the mayor of the city and want to build $ n-1 $ two-way roads to connect all districts (two districts can be connected directly or through other connected districts).

If two districts belonging to the same gang are connected directly with a road, this gang will revolt.

You don't want this so your task is to build $ n-1 $ two-way roads in such a way that all districts are reachable from each other (possibly, using intermediate districts) and each pair of directly connected districts belong to different gangs, or determine that it is impossible to build $ n-1 $ roads to satisfy all the conditions.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
4
5
1 2 2 1 3
3
1 1 1
4
1 1000 101 1000
4
1 2 3 4```

### 输出

```
YES
1 3
3 5
5 4
1 2
NO
YES
1 2
2 3
3 4
YES
1 2
1 3
1 4```

# 题解

## 作者：KSToki (赞：4)

构造即可，其实是 $O(n)$ 的。

首先输入扫一遍，如果所有数都一样直接输出 NO。然后将所有与 $a[1]$ 不同的数 $a[i]$ 与 $1$ 连边，把 $i$ 记录下来，所有与 $a[1]$ 相同的数与标记连边即可。

代码简单：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	char ch=getchar();
	while(ch<'0'||ch>'9')
	    ch=getchar();
	int res=0;
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res;
}
int T,n,a[5001];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		a[1]=read();
		bool f=1;
		for(register int i=2;i<=n;++i)
		{
			a[i]=read();
			if(a[i]!=a[i-1])
				f=0;
		}
		if(f)
		{
			printf("NO\n");
			continue;
		}
		printf("YES\n");
		int t;
		for(register int i=2;i<=n;++i)
			if(a[i]!=a[1])
			{
				printf("1 %d\n",i);
				t=i;
			}
		for(register int i=2;i<=n;++i)
			if(a[i]==a[1])
				printf("%d %d\n",i,t);
	}
	return 0;
}
```


---

## 作者：sto__Liyhzh__orz (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1433D)

扫一遍数组，若所有 $a_i$ 皆相等，很容易就能想出无解，输出 `NO`。

若有解，则让 $1$ 为根节点，对于节点 $i$（$2 \le i \le n$）：

* 若 $a_i \ne a_1$，则让 $i$ 为第二层节点，父节点为 $1$。

* 若 $a_i = a_1$，则让 $i$ 为第三层节点，父节点是任意一个点 $j$ ，并且 $a_j \ne a_1$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=5000+5;
int T,n,a[MAXN];

int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		bool flag=1;
		for(int i=2;i<=n;i++)
		{
			if(a[i]!=a[1])
			{
			    flag=0;
			    break;
			}
		}
		if(flag)
		{
			cout<<"NO\n";
			continue;
		}
		cout<<"YES\n";
		int id;
		for(int i=2;i<=n;i++)
		{
			if(a[i]!=a[1])
			{
				cout<<"1 "<<i<<endl;
				id=i;
			}
		}
		for(int i=2;i<=n;i++)
		{
		    if(a[i]==a[1]) cout<<i<<" "<<id<<endl;
		}
	}
	return 0;
}
```

---

## 作者：fls233666 (赞：2)

首先可以发现的是，这题的节点数量 $n$ 范围为 $1 \le n \le 5000$，用 $O(n^2)$ 的暴力算法是可以通过的。那么我们可以用 $O(n^2)$ 的时间先把所有能连的边都预处理出来。

全部的边都预处理出来后，考虑选择那些边作为树边。根据树的定义，我们知道，**对于一棵有 $n$ 个节点的树，需要 $n-1$ 条边将这些点连通。** 那么，关键问题在于如何判断点的连通性。我们可以使用并查集，将连边的点放到同一个集合中，以此来判断连通性问题。

最后总结一下解题思路：

1. 预处理得到所有能连接的边；
2. 遍历所有边，判断边连接的两点是否连通，如果不连通，使用这条边；
3. 如果使用了 $n-1$ 条边，则有解，否则无解。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define rgt register int 
using namespace std;

const int mxn = 5e3+5; 
struct edge{
	int u;
	int v;
}tmp,use[mxn];
vector <edge> e;
int n,ai[mxn],lu;
int fa[mxn];

int getfa(int x){
	return x==fa[x]?x:fa[x]=getfa(fa[x]);
}

int main(){
	int test;
	scanf("%d",&test);
	while(test--){
    
		e.clear();
		scanf("%d",&n);
		lu=0;
		for(rgt i=1;i<=n;i++){
			scanf("%d",&ai[i]);
			fa[i]=i;
		}  //初始化及数据读入
        
		for(rgt i=1;i<=n;i++){
			for(rgt j=i+1;j<=n;j++){
				if(ai[i]!=ai[j]){
					tmp.u=i;
					tmp.v=j;
					e.push_back(tmp);
				}
			}
		}  //算出所有能连接的边
        
		for(rgt fu,fv,i=0;i<e.size();i++){
			fu=getfa(e[i].u);
			fv=getfa(e[i].v);
			if(fu!=fv){  //边连接的两点未连通，使用这条边
				fa[fu]=fv;
				lu++;
				use[lu]=e[i];
			}
			if(lu==n-1)
				break;  //使用了 n-1 条边，构成树，结束循环
		}  //使用边构建树
        
		if(lu!=n-1){  //如果没有使用 n-1 条边，不构成树，无解
			printf("NO\n");
			continue;
		}  //判断无解
        
		printf("YES\n");
		for(rgt i=1;i<=lu;i++)
			printf("%d %d\n",use[i].u,use[i].v);
     //输出答案
	}
	return 0;
}
```


---

## 作者：pigstd (赞：2)

题意：有 $n$ 个点，每个点有一个值 $a_i$ ，如果点 $i,j$ 满足 $a_i=a_j$ 就不能相连，问能不能连成一个树。

因为 $n \le 5000$，那么可以用 $n^2$ 算法解决。

我们可以用最小生成树的思想，枚举任何两个可以连接的，然后如果能连就用并查集把他们并起来，然后记录一下答案就可以了。

[code](https://www.luogu.com.cn/paste/6mr35muh)

---

## 作者：Suzt_ilymtics (赞：1)

## Solution

发现有一种很不错的构造方案是构造菊花图，刚好可以满足题目给我们的性质

在菊花图中，只要让中间的点和所有不与它相同的点连边即可，那些和中间的点相同的点，找一个菊花图边上的点，在用这个点构造个菊花图即可

根据这个思路不难发现，只要有两种点就能构造出一种方案，所以不合法的条件为所有点都相同

为了追求切题效率可以，在输入是判断能否构造，在输出时排一下序，此时 $a_i$ 和 $a_n$ 必定不同，用他们两个当做两个菊花图的中心去构造即可，具体实现看代码吧

## Code

```cpp
/*
Work by: Suzt_ilymics
Knowledge: ??
Time: O(??)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 5050;
const int INF = 1;
const int mod = 1;

struct node{
	int val, bh;
	bool operator < (const node &b) const { return val < b.val; }
}a[MAXN];

int T, n;
bool vis[MAXN];

int read(){
	int s = 0, f = 0;
	char ch = getchar();
	while(!isdigit(ch))  f |= (ch == '-'), ch = getchar();
	while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
	return f ? -s : s;
}

int main()
{
	T = read();
	while(T--){
		memset(vis, 0, sizeof(vis));
		n = read();
		bool flag = true;
		a[1].val = read();
		a[1].bh = 1;
		for(int i = 2; i <= n; ++i) {
			a[i].val = read(); 
			a[i].bh = i;
			if(a[i].val != a[i - 1].val && flag){
				printf("YES\n");
				flag = false;
			}
		}
		if(flag) {
			printf("NO\n");	
		}
		else{
			sort(a + 1, a + n + 1);
			vis[1] = 1;
			for(int i = 2; i <= n; ++i){
				if(!vis[i] && a[i].val != a[1].val) {
					cout<<a[1].bh<<" "<<a[i].bh<<endl;
					vis[i] = 1;
				}
			}
			for(int i = 1; i < n; ++i){
				if(!vis[i] && a[i].val != a[n].val)	{
					cout<<a[n].bh<<" "<<a[i].bh<<endl;
					vis[i] = 1;
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：vectorwyx (赞：1)

若所有区域均属于同一帮派，答案显然为 `NO`。

否则，我们柯以随便选择一个帮派，将这个帮派中的任意一个区域与所有其他帮派的区域连一条边，然后再从另一个帮派中的任意一个区域向这个帮派中的其他区域连边。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
#include<map>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int maxn=5005;
struct Node{
	int val,num;
	bool operator<(const Node &x) const{
		return val<x.val;
	}
}a[maxn];
vector<int> g[maxn];
//map<int,int> b;

void work(){
	int n=read(),pos=-1;
	fo(i,1,n) a[i].val=read(),a[i].num=i;
	sort(a+1,a+1+n);
	int x=0,last=0;
	fo(i,1,n){
		if(a[i].val!=last) x++;
		last=a[i].val;
		a[i].val=x;
	}
	//fo(i,1,n) printf("%d %d\n",a[i].val,a[i].num);puts("");
	if(x==1){
		puts("NO");
		return;
	}
	fo(i,1,x) g[i].clear();
	fo(i,1,n) g[a[i].val].push_back(a[i].num);
	puts("YES");
	fo(i,2,x){
		int s=g[i].size()-1;
		fo(j,0,s) printf("%d %d\n",g[i][j],g[1][0]);
	}
	int s=g[1].size()-1;
	fo(i,1,s) printf("%d %d\n",g[1][i],g[2][0]);
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：_QWQ__QWQ_ (赞：0)

一道简单构造题，一次性 AC。

一种想法是将所有值一样的点全部连到同一个不同值的点上，这样就是所有同一种值的点都有同一个父亲，即可避免连在一起的问题，无解的情况就是只有一种值。

时间复杂度 $O(n^2)$

AC code:

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
const int maxn=1e6+5;
int t,n,a[maxn],c[maxn];
void solve(){
	cin>>n;
	int cnt=0;\
	unordered_map<int,unordered_map<int,int>>pm;//去重数组
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	bool flag=0;
	for(int i=1;i<=n;i++){//枚举每个点
		int pos=0;//找到的位置
		for(int j=1;j<=n;j++){
			if(a[j]!=a[i]){//第一个不同的值
				pos=j;
				break;
			}
		}
		if(pos==0){//没找到，即全是一个值
			cout<<"NO"<<endl;//无解
			return;
		}
		for(int j=1;j<=n;j++){
			if(a[j]==a[i]){//找与 i 相同的值
				if(flag==0){//没有输出 YES
					cout<<"YES"<<endl;//输出
					flag=1;//标记
				}
				if(pm[pos][j]==1){//去重
					continue;
				}
				cout<<pos<<' '<<j<<endl;//pos 与 j 是父子关系
				pm[pos][j]=pm[j][pos]=1;//标记去重数组
			}
		}
	}
	
}
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：pyz51 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1433D)

# 题意简述
给定一个长度为 $n$ 的数组 $a$，构造树使得对于任意一条边 $(u,v)$，有 $a_u \ne a_v$。
# 题解
以 $1$ 为根节点暴力搜索即可，将一个没被连过的节点与当前节点连接，再从这个节点搜索，最后判断是不是所有节点都被连过。

过程示例如下（以样例第 $1$ 个数据为例）：
1. 令根节点为 $1$。  
   ![](https://cdn.luogu.com.cn/upload/image_hosting/mgir91k9.png)
2. 将一个特征值与 $1$ 不同的值的节点与节点 $1$ 相连。这里 $a = \{2,2,1,3\}$ 可以选 $2$。  
   ![](https://cdn.luogu.com.cn/upload/image_hosting/yeugprhs.png)  
   下一步：$a = \{2,1,3\} $ 可以选 $1$（带 * 号是为了分辨）。
   ![](https://cdn.luogu.com.cn/upload/image_hosting/gsbopo1w.png)
4. 重复以上操作，直至节点都被连过。  

**成品（带 * 号是为了分辨）**：

![](https://cdn.luogu.com.cn/upload/image_hosting/gmd3liah.png)
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int M=2e5+5;
const int inf=2147483647;
const long long lof=9223372036854775807;
#define ll long long
#define bug cout<<"...here...\n"
#define mem(a,b) memset(a,b,sizeof a)
int n,a[5005],cnt,cot,ans[2][5005],t;
bool vis[5005];
void dfs(int x){
    vis[x]=1;
    cnt++;
    for(int i=1;i<=n;i++){
        if(vis[i]||a[i]==a[x]) continue;//如果被连过或特征值相等，跳过。
        ans[0][++cot]=x;
        ans[1][cot]=i;//存边
        vis[i]=1;
        dfs(i);
    }
}
int main(){
    cin>>t;
    while(t--){
        mem(ans,0);
        mem(vis,0);
        cnt=cot=0;
        //初始化
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        dfs(1);//以1为根节点搜索
        if(cnt<n) cout<<"NO\n";//节点没有都被连过
        else{
            cout<<"YES\n";
            for(int i=1;i<=cot;i++) cout<<ans[0][i]<<' '<<ans[1][i]<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：luosw (赞：0)

首先，若输入的所有 $a_i$ 全部相等，则输出 $\texttt{NO}$。

其次我们可以将这个问题中的连边分为两个子问题：

现在 $a_i$ 和 $a_j$ 连边。

1. 判断 $a_i\neq a_j$；

1. 判断是否会产生环（**仿照 Kruskal 的思想，利用并查集判断**）。

时间复杂度 $\mathcal O(n^2\alpha(n))$。

---


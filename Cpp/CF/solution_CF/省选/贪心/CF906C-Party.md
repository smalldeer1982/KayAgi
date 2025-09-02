# Party

## 题目描述

Arseny 喜欢组织派对并邀请他的朋友们参加。然而，不仅朋友来参加他的聚会，还有他朋友的朋友，他朋友的朋友的朋友等等。所以 Arseny 的有一部分客人可能不了解他，他决定使用以下方法解决此问题。

在每一步，他都选择了一位客人 $A$，将 $A$ 的所有朋友全都两两互相介绍一遍。在完成这一步之后，$A$ 的任意两个朋友也会互相成为朋友。Arseny 一直重复这个步骤直到所有客人都互相成为朋友为止。

Arseny 不想花太多时间去完成这件事，所以他想用最少的步骤完成这个过程。Arseny 需要你来帮帮她做到这一点。

## 样例 #1

### 输入

```
5 6
1 2
1 3
2 3
2 5
3 4
4 5
```

### 输出

```
2
2 3 ```

## 样例 #2

### 输入

```
4 4
1 2
1 3
1 4
3 4
```

### 输出

```
1
1 ```

# 题解

## 作者：FreedomKing (赞：11)

写自梦熊模拟赛赛后补题。梦熊模拟赛出原题，望周知。

一眼状压 dp，但是转移部分友好请教了@[newbie_QwQ](https://www.luogu.com.cn/user/535491)。

### 思路

假设一个集合 $S$，$S$ 内的元素都认为是互相认识的，然后就能用 $dp_i$，$i$ 的二进制位下 $1$ 代表在 $S$ 集合内，表示出 $S$。通过枚举集合和当前操作的 $j$，可以得出转移式 $dp_i=\min\{dp_{i\operatorname{or}a_j},dp_i+1\}$，其中 $a_j$ 表示 $j$ 的朋友集合。

然后考虑在转移时记录下当前状态是由那个状态转移而来以及转移当前状态需要操作的人的编号，dfs 输出一下即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define int long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int N=(1<<22)+5,mN=5e3+5,mod=1e9+7;
namespace FreedomKing_qwq{
#define lowbit(_) (_&-_)
	struct Tree{
		int tree[N];
		inline void add(int x,int k){
			for(int i=1;i<=x;i+=lowbit(i)) tree[i]+=k;
			return;
		}
		inline int query(int x){
			int ans=0;
			for(int i=x;i>1;i-=lowbit(i)) ans+=tree[i];
			return ans;
		}
	};
	struct Dset{
		int fa[N];
		inline void init(int x){
			for(int i=1;i<=x;i++) fa[i]=i;
			return;
		}
		inline int find(int x){
			return (fa[x]==x?x:fa[x]=find(fa[x]));
		}
		inline void update(int x,int y){
			x=find(x);y=find(y);
			fa[y]=x;
			return;
		}
	};
#define lc (p<<1)
#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}	
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		if(p<0) return qpow(qpow(x,-p,mod),mod-2,mod);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
	//	inline int max(int x,int y){return (x>y?x:y);}
	//	inline int min(int x,int y){return (x<y?x:y);}
	//	inline int abss(int x){return (x>=0?x:-x);}
}
int a[N],dp[N],ans[N],fa[N];
inline void dfs(int x){
	if(fa[x]) dfs(fa[x]);
	qws(ans[x]);
}
signed main(){
	int n=qr,m=qr;
	for(int i=1;i<(1<<n);i++) dp[i]=LONG_LONG_MAX;
	if((n*(n-1)/2)==m){puts("0");return 0;}
	for(int i=1;i<=m;i++){
		int u=qr,v=qr;
		a[u]|=(1<<v-1);
		a[v]|=(1<<u-1);
	}
	for(int i=1;i<=n;i++){
		a[i]|=(1<<(i-1));
		dp[a[i]]=1;
		ans[a[i]]=i;
	}
	for(int i=0;i<(1<<n);i++){
		if(dp[i]==LONG_LONG_MAX) continue;
		for(int j=1;j<=n;j++){
			if((i&(1<<(j-1)))!=0&&dp[i]+1<dp[i|a[j]]){
				dp[i|a[j]]=dp[i]+1;
				ans[i|a[j]]=j;
				fa[i|a[j]]=i;
			}
		}
	}
	qwe(dp[(1<<n)-1]);
	dfs((1<<n)-1);
	return 0;
}
```

讲个笑话，梦熊的数据水到 `if((n*(n+1)/2)==m){puts("0");return 0;}` 都能放过去。

---

## 作者：暮光闪闪 (赞：7)

个人认为题目页面的题意解释已经够详细了，这里不再解释。

## 有一个坑人的地方！
**客人们可以不经过介绍就已经互相认识**！所以开头需要特判
## 思路
将客人之间互相认识的情况状态压缩一下，作为下标存$dp$里面。$dp[s]$表示使i状态中所有客人互相认识所需要的最少步骤数。比如把数字s展开成二进制后是1011，数字"1"从左往右数依次排在第1、3、4位，则dp[s]的意思就是让1、3、4号客人从不认识变为互相认识所需的介绍次数。

所以第一小问的答案在$dp[(1<<n)-1]$里面。第一小问属于状压基础。至于第二小问，开个数组存$q$存经哪个客人介绍后达到的$i$状态，再开个数组$fa$查询$i$状态之前的状态。两个数组相结合就完事了。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
int a[25];//a表示i号客人的朋友圈
int dp[(1<<22)+1000];//dp表示使i状态中所有客人互相认识所需要的最少步骤数
int q[(1<<22)+1000];//q表示经哪个客人介绍后达到的i状态
int fa[(1<<22)+1000];//查询i状态之前的状态，和q数组结合可以查询每个步骤中选择的客人编号，解决了第二小问
void fid(int x){
	if(fa[x])fid(fa[x]);
	printf("%d ",q[x]);
}
int main(){
	memset(dp,0x3f,sizeof(dp));
	int n,m;cin>>n>>m;
	for(int i=1;i<=n;i++)a[i]=1<<(i-1);//自己肯定认识自己 
	for(int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);
		a[x]+=1<<(y-1);//也可a[x]|=1<<(y-1); 
		a[y]+=1<<(x-1);//也可a[y]|=1<<(x-1); 
	}
	if(m==n*(n-1)/2){//如果给你的人际关系图中每个人身上都互相之间都认识，那就不用介绍了
		printf("0\n");
		return 0;
	}
	for(int i=1;i<=n;i++){//初始化 
		dp[a[i]]=1;//i号客人朋友圈内互相认识只需经过i一步介绍
		q[a[i]]=i;//达成i号客人朋友圈内互相认识的状态只需经过i介绍 
	}
	for(int s=0;s<(1<<n);s++){
		if(dp[s]==inf)continue;//当前状态无法达到 
		for(int i=1;i<=n;i++)
//选择i客人进行介绍的前提：1.i被人们所认识 2.让i介绍达到s|a[i]状态需要的步骤比之前的方案更优 
			if((s&(1<<(i-1)))&&dp[s|a[i]]>dp[s]+1){
				dp[s|a[i]]=dp[s]+1;//更新最优步骤 
				q[s|a[i]]=i;//达成s|a[i]状态是通过i介绍得出的 
				fa[s|a[i]]=s;//s|a[i]状态之前的状态是s 
			}
	}
	printf("%d\n",dp[(1<<n)-1]);
	fid((1<<n)-1);
	return 0;
}
```


---

## 作者：yingxilin (赞：4)

今天来水一波题解……

[更好的阅读体验点这里](https://www.cnblogs.com/yingxilin/p/18313209)
## 理解题意
由于题目意思讲得很清楚，就因为懒惰直接复制了……

给你一堆一对对的关系，然后每一个关系对代表两个人认识。然后你每次可以选择一个人 $i$ ，让 $i$ 认识的所有人都相互认识，即 $i$ 把介绍自己所有的朋友给其他人。然后现在问你最少需要选择多少个这样的 $i$ ，使得所有的人都相互认识。

注意了，朋友的朋友并不一定互为朋友，否则就用并查集秒了（这看颜色紫紫的就知道不是这样）。

## 思路
用状压 DP 。

定义一个数组 $dp_s$ , $s$ 表示互为朋友的人的状态，例如 $101001$ 表示第 $1$ 个，第 $4$ 个和第 $6$ 个人的互为朋友，而 $dp_s$ 表示实现 $s$ 这个状态所需的介绍次数。

状态转移方程：  

 $dp_{s \cup fr_i} \leftarrow \min(dp_{s \cup fr_i}, dp_s + 1)$

 $dp_{s \cup fr_i}$ 表示在状态 $s$ 中， $i$ 介绍朋友后的状态， $fr_i$ 表示 $i$ 的朋友的集合，记住 $i$ 也认识它自己！！！

那么初始化呢，因为i的朋友只需i来叫一次，so……  $fr_i$ $=$ $1$ 。

注意如果输入的关系即可使所有人互为朋友，则应输出0，要特判。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
const int N=(1<<22)+1000;
int fr[N];//fr[i]-->i的朋友
int s[N];//人的集合
int dp[N];//使集合i的人认识所需介绍次数
int q[N];//q[s]=i表示s的转态这次由i介绍得到
int pre[N];//存s经过这次i介绍之前的状态
const int inf=0x3f3f3f3f;
void dfs(int x)
{
	if(pre[x]) dfs(pre[x]);
	cout<<q[x]<<" ";//在回溯时输出
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	memset(dp,0x3f,sizeof dp);
	cin>>n>>m;
	for(int i=1;i<=n;i++) fr[i]+=1<<(i-1);//自己认识自己
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		fr[u]+=1<<(v-1);
		fr[v]+=1<<(u-1);
        //v,u互为朋友
	}
	if(m==n*(n-1)/2)//原本互为朋友，特判
	{
		cout<<0;
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		 dp[fr[i]]=1;//i介绍fr[i]需要一步
		 q[fr[i]]=i;//fr[i]由i介绍
	}
	for(int s=0;s<=(1<<n)-1;s++)//枚举状态
	{
		if(dp[s]==inf) continue;//当前集合无法达到
		for(int i=1;i<=n;i++) 
		{
			if((s&(1<<i-1)))//满足s包含i
			{
				if(dp[s|fr[i]]>dp[s]+1)
				{
					dp[s|fr[i]]=dp[s]+1;//更新
					q[s|fr[i]]=i;//存当前的介绍人
					pre[s|fr[i]]=s;//存i介绍前的状态
				}
				
			}
		}
	}
	cout<<dp[(1<<n)-1]<<endl;//输出步数
	dfs((1<<n)-1);//输出介绍人
	return 0;
}
``````
本蒟蒻洛谷第一遍题解 && AC 第一道紫题，如有不足请指教。  
完结撒花

---

## 作者：cool_milo (赞：4)

[可能更好的阅读体验](https://www.cnblogs.com/miloHogwarts4ever/p/CF906C.html)

大家好，我和 DP 有仇，所以我用猜结论的方法过了这道题。

可能是这道题的一个全新思路，可能人自闭久了什么都能想出来（（（

upd：好像这也是官方题解思路，看来大家做题不太喜欢看 CF 官方题解（（（

首先考虑一个问题：如果这是一道构造题，怎么构造一组合法的解？  
在草稿纸上画了很久之后，我发现：只需要在原图上找到一棵生成树，依此从叶子到根操作所有的点，就能得到一个 $n$ 个点的团。其中叶子不用操作。那么操作次数是 $n - leaf_T$ 次。  
很难想到更好的策略了。所以我先写了一个枚举哪些点是叶子的 $\Theta(n^2 2^n)$ 的[暴力](https://codeforces.com/contest/906/submission/226228636)，发现没有 WA 的点。复制了后面的测试点发现答案都是对的。  
很懵逼。外层的枚举叶子应该是无法优化了，内层的 check 怎么优化呢？我们发现我们要 check 两件事：

+ 非叶节点连通
+ 所有叶节点都有向非叶节点的边

可以对于每个点处理它向哪些点连边，用一个二进制数 $State_i$ 存下来。
第一个要求可以预处理两个一个数组 $ok_S$，表示 $S$ 这个集合是否连通。枚举 $j \in S$ 看 $j$ 是否向 $S$ 中其他元素连边就能递推了。  
第二个要求可以直接对于每个叶节点的 $State_i$ 查找是否有非叶节点。

那么复杂度就被降为 $\Theta(n 2^n)$，就可以[通过](https://codeforces.com/contest/906/submission/226229633)这道题了。注意特判掉给出的图就是完全图的情况。

怎么证明结论呢？这里用官方题解的话说：

假设被操作的最小点集是 $T$。  
首先，$T$ 必然连通，否则在不同的连通块之间就没法加上边。  
其次，所有不在 $T$ 中的点必然和 $T$ 中的点有连边，否则这些点上无法加上新的边。  
现在，我随便找出 $T$ 的一棵生成树 $T'$，那么，所有不在 $T$ 中的点就可以向 $T'$ 连边，得到一棵以 $T'$ 为非叶节点的原图的生成树。（$T'$ 中如果有叶节点就一定不优，矛盾。）结论得证。

~~当了一把官方题解搬运工~~

---

## 作者：李柯欣 (赞：4)

题目传送门：[CF906C](https://www.luogu.com.cn/problem/CF906C)。

[更好的阅读感受](https://www.luogu.com.cn/blog/likexin/solution-cf906c)？

### 题目大意：

$n$ 个人，$m$ 对关系。

每一对关系对代表两个人认识。你每次可以选择一个人 $i$，让 $i$ 认识的所有人都相互认识。

问最少需要选择多少个这样的 $i$，使得所有的人都相互认识，并输出任意一种介绍方案。

### 思路：

注意到  $1\le n \le 22$，$0\le m\le \dfrac{n·(n-1)}{2}$。

于是想到状压。

令 $dp_x$ 表示 $x$ 的二进制位上为 $1$ 的人互相认识，依次转移。

预处理出 $p_i$ 表示介绍第 $i$ 个人可以让那些人相互认识，转移时根据 $p_i$ 转移即可。

所以转移方程是：

$$dp_{x|p[j]}=\min (dp_{x}+1)\ (j\in x)$$

为方便数组下标从 $0$ 开始。

$dp_{(n<<1)-1}$ 就是第一问答案。

对于第二问，在转移中处理出 $fa_x$ 表示状态 $x$ 可以由那个状态转移出，和 $s_x$ 表示在到达 $x$ 这一状态时所介绍的那一个人，并以此递推输出。

### 代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<vector>
#include<bitset>
#include<string>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<deque>
#include<queue>
#include<stack>
#include<list>
#include<map>
#include<set>
//#define int long long
using namespace std;
int n,m;
int x,y;
int q[4194314];
int dp[4194314];
int s[4194314]; 
int fa[4194314];
void dfs(int x){
	if(fa[x]) dfs(fa[x]);
	cout<<s[x]+1<<' ';
} 
/*
dfs 函数中，由于输出任意一种情况，所以换成：

cout<<s[x]+1<<' ';
if(fa[x]) dfs(fa[x]);

也是对的。
*/
signed main(){
	memset(dp,0x3f,sizeof(dp));
	cin>>n>>m;
	if(m==n*(n-1)/2){// 开始时可能所有人都两两认识，特判。
		cout<<0<<endl;
		return 0;
	}
	for(int i=0;i<n;i++) q[i]|=(1<<i);//每个人都认识自己。
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		q[x-1]|=(1<<(y-1));
		q[y-1]|=(1<<(x-1));//预处理。
	}
	for(int i=0;i<n;i++){
		dp[q[i]]=1;//让 q[i] 中的人两两认识只需要一步。
		s[q[i]]=i;//介绍的人是 i。
	}
	for(int i=0;i<(1<<n);i++){
		if(dp[i]==0x3f3f3f3f) continue; 
		for(int j=0;j<n;j++){
			if((i&(1<<j))&&dp[i|q[j]]>dp[i]+1){
				fa[i|q[j]]=i;//状态 i|q[j] 由 i 转移而来。
				dp[i|q[j]]=dp[i]+1;
				s[i|q[j]]=j;//转移到状态 i|q[j] 所介绍的人是 j。
			}
		}
	}
	cout<<dp[(1<<n)-1]<<endl;
	dfs((1<<n)-1);
	return 0;
}
```


[AC 记录](https://www.luogu.com.cn/record/86038528)。

---

## 作者：Targanzqq (赞：2)

**鉴定为：紫不如蓝。**

这是一道经典的状压 dp，dp 转移的过程非常好想，设 $f_{i}$ 表示一个互相认识的朋友集合，我们接下来有两种思路：

一种是枚举它的补集，然后把贡献加进去，但是这样做时间复杂度会太高，所以不行。

还有一种是经典套路，就是枚举一个已经加入的朋友，通过它来找新加入的朋友。设 $S_j$ 是 $j$ 的朋友集合，当前集合为 $i$ ，那我们用 $f_i+1$ 去更新 $f_{i|s_j}$，让后者去最小值。

还有就是 dfs 的过程，对于可以产生贡献的 $f_i+1$，我们让 $f_{i|s_j}$ 的转移过程定为 $i$，最后从 $f_{2^n-1}$ 往回找即可，每次输出转移过程。

然后你就会发现，**样例过不了**。

但是我们发现，最后的集合都一样，因为这是一个无向图，让谁先认识都一样，中间都是联通的。所以我们正向输出和倒向输出都对。

源代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f
using namespace std;

int n,m,f[1<<22],g[22],fa[(1<<22)],s[(1<<22)],ans[(1<<22)];
int nxt[22];
vector<int> t[22];

void dfs(int now){
	if(fa[now])dfs(fa[now]);
	cout<<ans[now]<<" ";
}

signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=0;i<(1<<n);i++){
		f[i]=INF;
	}
	for(int i=0;i<n;i++)g[i]|=(1<<i);
	for(int i=1;i<=m;i++){
        int a,b;cin>>a>>b;
        t[a-1].push_back(b-1);
        t[b-1].push_back(a-1);
        g[a-1]|=(1<<(b-1));
        g[b-1]|=(1<<(a-1));
    }
    if((n*(n-1)/2)==m){
		cout<<0;return 0;
	}
	for(int i=0;i<n;i++){
		f[g[i]]=1;
		ans[g[i]]=i+1;
	}
	for(int i=0;i<(1<<n);i++){
		if(f[i]==INF)continue;
		for(int j=0;j<n;j++){
			if(!(i&(1<<j)))continue;
			if(f[i]+1<f[i|g[j]]){
				f[i|g[j]]=f[i]+1;
				fa[i|g[j]]=i;
				ans[i|g[j]]=j+1;
			}
		}
	}
	cout<<f[(1<<n)-1]<<endl;
	dfs((1<<n)-1);
}
```

---

## 作者：Purslane (赞：1)

# Solution

先特判掉完全图。

如果我们操作了一个人，实际上相当于给这个人打上标记。两个人认识，当且仅当他们可以通过若干个（可能为 $0$）打了标记的人。

最终的形态必定是：一个所有人都打标记的联通块外面挂了几个没打标记的人。我们需要没打标记的人最多。

那么用状压 DP 求出所有联通块，并且看他能不能成为答案即可。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=25,MAXM=(1<<22)+10;
int n,m,flg[MAXN][MAXN],dp[MAXM],deg[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	if(n<=2||m==n*(n-1)/2) return cout<<0,0;
	ffor(i,1,m) {
		int u,v;
		cin>>u>>v,deg[u]|=(1<<v-1),deg[v]|=(1<<u-1);	
	}
	ffor(i,1,n) dp[(1<<i-1)]=1;
	ffor(i,0,(1<<n)-1) ffor(j,1,n) if((i&(1<<j-1))&&(i&deg[j])&&dp[i-(1<<j-1)]) dp[i]=1;
	int ans=0,al=0;
	ffor(i,1,(1<<n)-1) if(dp[(1<<n)-1-i]) {
		int flg=1;
		ffor(j,1,n) if(i&(1<<j-1)) flg&=!!(((1<<n)-1-i)&deg[j]);
		if(flg) if(ans<__builtin_popcount(i)) ans=__builtin_popcount(i),al=(1<<n)-1-i;
	}
	cout<<n-ans<<'\n';
	ffor(i,1,n) if(al&(1<<i-1)) cout<<i<<' ';
	return 0;
}
```

---

## 作者：SunnyYuan (赞：1)

## 思路

这是一道非常有意思的状压 DP 题目。

首先，我们默认从 $0$ 开始计数，即下标都从 $0$ 开始，所有人的编号从 $0$ 到 $n - 1$。

首先，我们设 $f_{state}$ 表示要达到状态为 $state$ 需要的最小步骤，假设 $state_i$ 表示 $state$ 在二进制表示下的第 $i$ 位，那么 $state_i = 1$ 构成的 $i$ 的集合表示这些人互相认识，比如 $state = 11011$，表示第 $0, 1, 3, 4$ 个人互相认识。

然后假设 $a_i$ 表示第 $i$ 个人直接认识的人，即如果 $a_i$ 的二进制表示下的第 $j$ 位 $a_{i, j}$ 为 $1$，那么表示 $i, j$ 直接认识。

再然后就是枚举所有的状态 $state$，如果 $state_i$ 为 $1$，那么就可以让第 $i$ 个人进行介绍，状态变为 $state$ 或 $a_i$。

下面是重点，就是我们怎么输出状态：

我们可以记录一个 $prestate$ 表示 $state$ 在动态规划上是从哪个状态来的，$prepeo$ 表示从 $prestate$ 经过了 $prepeo$ 的介绍才来到了 $state$ 状态。

所以我们可以直接弄一个递归函数，一直认祖归宗直到某一个起点，再从前往后输出。


注意我们要先递归再输出，因为我们要从里到外介绍才能保证第 $i$ 个人介绍的时候他自己已经被介绍。

## 代码

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: Party
| Contest: Luogu
| URL:     https://www.luogu.com.cn/problem/CF906C
| When:    2023-10-05 17:29:41
| 
| Memory:  250 MB
| Time:    1000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;

const int N = 22;

int n, m, a[N], f[1 << N], pre_state[1 << N], pre_peo[1 << N];

void dfs(int state) {
    if (!state) return;
    if (pre_peo[state] != -1) cout << pre_peo[state] + 1 << ' ';
    dfs(pre_state[state]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    if (m == n * (n - 1) / 2) {
        cout << 0 << '\n';
        return 0;
    }
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        u--, v--;
        a[u] |= 1 << v;
        a[v] |= 1 << u;
    }
    memset(f, 0x3f, sizeof(f));
    for (int i = 0; i < n; i++) f[1 << i] = 0, pre_peo[1 << i] = -1;
    for (int i = 0; i < (1 << n); i++)
        for (int j = 0; j < n; j++)
            if ((i >> j & 1) && f[i | a[j]] > f[i] + 1) {
                f[i | a[j]] = f[i] + 1;
                pre_state[i | a[j]] = i;
                pre_peo[i | a[j]] = j;
            }
    cout << f[(1 << n) - 1] << '\n';
    dfs((1 << n) - 1);
    return 0;
}
```

---

## 作者：断清秋 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF906C)

看数据范围显然是个状压 dp。

设 $dp[i]$ 表示认识人的情况为 $i$ 时最少需要介绍的次数，$a_i$ 表示 $i$ 认识人的情况，每次转移就是 $dp[i|a_j]=\min(dp[i|a_j],dp[i]+1$)。

第一问的答案就是 $dp[2^n-1]$。

对于第二问，记录 $ans_i$ 表示 $i$ 状态是谁介绍的，$fa_i$ 表示 $i$ 状态的上一个状态，每次转移时更新这两个值，最后 dfs 一遍即可。

需要特判一开始就是完全图的情况。

---

## 作者：時空 (赞：0)

### $\texttt{CF906C Party}$

[In Luogu](https://www.luogu.com.cn/problem/CF906C)

题意：有 $n$ 个人和 $m$ 对朋友关系 $u_i,v_i$，表示第 $u$ 个人和第 $v$ 个人之间是朋友。

你想让所有的 $n$ 个人两两之间都成为朋友，为此你可以进行若干次如下操作：

选择一个人 $x$ ，他会把他所有的朋友叫出来互相认识，在这之后，他的所有朋友两两之间都成为了朋友。

你需要最小化操作次数，输入保证有解。同时，你需要求出每次操作的人。

解：状压好题。

首先考虑原题的弱化版，不考虑输出方案。

看到 $m \le 22$，自然想到状压。

记 $dp_i$，$i$ 的二进制下第 $j$ 位为 $1$ 表示 $j$ 在集合 $i$ 内，与 $i$ 中的其他元素均认识。  

考虑再用 $State$ 去记录 $i$ 本来就认识的人。$State_i$ 表示与 $i$ 认识的人的集合。

然后就很简单了，枚举集合，枚举人进行转移即可。

考虑怎么输出方案。在转移时用一个 $nxt$ 记录即可。

注意特判完全图的情况。

Code:

```cpp
cin >> n >> m;
if ((n * (n - 1) >> 1) == m) { cout << "0\n"; return 0; }
while (m -- )
{
	ll u, v; cin >> u >> v;
	-- u, -- v;
	State[u] |= (1 << v);
	State[v] |= (1 << u);
}
mem(dp, 0x3f);
for (ll i = 0; i < n; i ++ ) State[i] |= (1 << i), dp[State[i]] = 1, Pre[State[i]] = i;
for (ll i = 0; i < (1 << n); i ++ )
{
	for (ll j = 0; j < n; j ++ )
	{
		if (i & (1 << j) && dp[i | State[j]] > dp[i] + 1)
		{
			dp[i | State[j]] = dp[i] + 1;
			nxt[i | State[j]] = i; Pre[i | State[j]] = j;
		}
	}
}
cout << dp[(1 << n) - 1] << '\n';
for (ll i = (1 << n) - 1; i; i = nxt[i] ) cout << Pre[i] + 1 << ' '; 
```

---

## 作者：Drest (赞：0)

# [CF906C] Party 题解

[luogu](https://www.luogu.com.cn/problem/CF906C)
|
[codeforces](https://codeforces.com/contest/906/problem/C)

## 解题思路

非常经典的状压 dp。

设计 $f_i$ 表示当前交友状况为 $i$ 时的最少花费。

对于一个状态 $i$，其**二进制**为 $\ldots x_3x_2x_1$，$x_j=1$ 表示目前互相认识的人集合中有 $j$。

对于第 $k$ 个人，我们需要提前处理出 $a_k$，其**二进制**为 $\ldots y_3y_2y_1$，$y_d=1$ 表示 $d$ 是 $k$ 的朋友。

那么对于一个状态 $i$，其可以转移到的所有状态就是 $s\in i,i\cup a_s$。

具体地，用伪代码表示如下：

```cpp
for (int s = 1; s <= n; s++)
   if (i & (1 << (s - 1))) // s 属于 i
	新状态 = i | a[s]; // i 并 a[s]

```

如果用记忆化搜索实现，那么这里还有一个问题，就是可能会**连续让同一个人介绍朋友**，导致死循环。

解决的方法也很简单，只需要在转移前判断**当前状态**中**这个人的所有朋友**是否**都已经互相认识**。具体地，只需在条件中加上
```cpp
if((i^((1<<m)-1)) // 状态对于全集的补集
   & (a[s] | (1 << (s - 1)))) // 与 s 的朋友
// 是否有交集
// 无交集则表示 （a[s] 并 s） 属于 i
```
即可。

最后是如何处理方案，方法也很简单，定义数组 `pre[i]` 表示状态 $i$ 是由哪个状态转移过来的（最优时），`pri[i]` 表示转移过来时对应的朋友编号。跑一边 dfs 即可。

## 代码

```cpp

#include <bits/stdc++.h>
using namespace std;
const int N = (1 << 22) + 100;

int n, m, s, l;
bool vis[N];
int mem[N], pre[N], pri[N];
int a[N];

int mdfs(int f) {
  
    if (vis[f]) return mem[f];
    if (f == s) return 0;

    int res = (1 << 30);
    for (int i = 1; i <= n; i++) {
        if (a[i] == 0) continue;
        if (((f ^ s) & (a[i] | (1 << (i - 1)))) && (f & (1 << (i - 1)))) {
            int dfs = mdfs(f | a[i]);
            if (dfs < res) {
                pre[f] = f | a[i];
                pri[f] = i;
                res = dfs;
            }
        }
    }
    vis[f] = true;
    return mem[f] = res + 1;
}

void dfn(int f) {
    if (f == s) return;
    cout << pri[f] << " ";
    dfn(pre[f]);
}

signed main() {
    cin >> n >> m;
    s = (1 << n) - 1;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        a[u] |= (1 << (v - 1));
        a[v] |= (1 << (u - 1));
    }

    if (n * (n - 1) / 2 == m) {
        cout << 0;
        return 0;
    }

    int ans = (1 << 30), pre0;
    for (int i = 1; i <= n; i++) {
        int dfs = mdfs(1 << (i - 1));
        if (dfs < ans) {
            ans = dfs;
            pre0 = (1 << (i - 1));
        }
    }
  
    cout << ans << endl;
    dfn(pre0);
  
    return 0;
}

``````

---

## 作者：xuantianhao (赞：0)

# [Party](https://www.luogu.com.cn/problem/CF906C)

DP 是门艺术。

$n\leq 22$ 一眼状压。但是怎么状压就比较困难，因为同一个 $f[x]$ 可以代表成千上万种含义。

这里我们采用，设 $f[x]$ 表示当 $x$ 集合中所有的点都处于同一个团内的最小代价。

则我们有 $f[x \operatorname{or}sta_i]=\max\limits_{i\in x}\{f[x]+1\}$。其中 $sta_i$ 表示与 $i$ 有边的集合。

初始为 $f[\{i\}]=0$，其它均为 $+\infty$。

复杂度为 $O(n2^n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f;
const int N=22;
int n,m,maxx,x,y;
int f[1<<N],d[1<<N],b[1<<N],st[N];
stack<int>s;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    cin>>n>>m;
	maxx=(1<<n);
	memset(f,INF,sizeof(f));
    for(int i=1;i<=m;i++){
		cin>>x>>y;
		x--;y--;st[x]|=(1<<y);st[y]|=(1<<x);
	}
    if(m*2==n*(n-1)){cout<<"0";return 0;}
    for(int i=0;i<n;i++) f[1<<i]=0;
    for(int u=1;u<maxx;u++){
		for(int i=0;i<n;i++){
		    if(!(u&(1<<i))) continue;
		    int v=u|st[i];
		    if(v==u) continue;
		    if(f[v]>f[u]+1){
				f[v]=f[u]+1;
				d[v]=u;
				b[v]=i;
			}
		}
	}
    cout<<f[maxx-1]<<'\n';
    int t=maxx-1;
    while(__builtin_popcount(t)!=1){s.push(b[t]);t=d[t];}
    while(!s.empty()){cout<<s.top()+1<<" ";s.pop();}
    return 0;
}

```

---

## 作者：chihik (赞：0)

首先预处理出一个人能介绍的人的集合 $rel$ 。（包括他本身）

令 $dp(S)$ 表示让集合 $S$ 中的人相互认识最少需要几个人。

那么可以刷表转移：

$$dp(S | rel_i )=\min(dp(S)+1)~~~~~~ (i\in S)$$

边界条件 $dp(rel_i)=1$。

可以看出，第一问的答案为全集的 dp 值。

第二问记录前驱状态和转移到当前状态用的人即可。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 22;
int n , m , rel[ MAXN + 5 ];
int dp[ 1 << MAXN ] , pre[ 1 << MAXN ] , prei[ 1 << MAXN ];

int main( ) {
	scanf("%d %d",&n,&m);
	if( m == n * ( n - 1 ) / 2 ) return printf("0") & 0;
	for( int i = 1 , u , v ; i <= m ; i ++ ) {
		scanf("%d %d",&u,&v); u -- , v --;
		rel[ u ] |= 1 << v; rel[ v ] |= 1 << u;
	}
	for( int i = 0 ; i < n ; i ++ ) rel[ i ] |= 1 << i;
	
	memset( dp , 0x3f , sizeof( dp ) );
	for( int i = 0 ; i < n ; i ++ ) dp[ rel[ i ] ] = 1 , prei[ rel[ i ] ] = i;
	for( int S = 0 ; S < 1 << n ; S ++ )
		for( int i = 0 ; i < n ; i ++ )
			if( S & ( 1 << i ) && dp[ S | rel[ i ] ] > dp[ S ] + 1 ) {
				dp[ S | rel[ i ] ] = dp[ S ] + 1;
				pre[ S | rel[ i ] ] = S; prei[ S | rel[ i ] ] = i;
			}
	printf("%d\n", dp[ ( 1 << n ) - 1 ] );
	for( int i = ( 1 << n ) - 1 ; i ; i = pre[ i ] ) printf("%d " , prei[ i ] + 1 );
	return 0;
}
```

---


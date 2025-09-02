# [USACO14FEB] Cow Decathlon G

## 题目描述

题目大意
约翰有N头奶牛，组成了一直队伍参加全能比赛。比赛一共有N项，每头奶牛必须参加一项比赛，每项比赛也必须有一头奶牛参加。任何一头奶牛可以胜任任何一项比赛，但得分不一样。如果第i头奶牛参加第j项比赛，在比赛结束的时候，可以为团体总分增加Si,j。
比赛是按照顺序依次进行的。除了上述获得分数的方法之外，还有B种奖励分。获得奖励的方法是在前几项比赛里获得足够的分数。具体来说，第i项奖励会在第Ki项比赛结束的时候检查，如果 当时的总分大于或等于Pi，奶牛们就可以立即获得额外的Ai 分。如果有多项奖励在同一时刻检查，奶牛可以自由安排检查和加分的顺序。请问约翰应该如何安排奶牛参加比赛，才能让它们获得最高的分数？

## 说明/提示

第一项比赛由第一头奶牛参加，第二项比赛由第三头奶牛参加，第三项比赛由第二头奶牛参加。

translator：2018_RNG丶妖夢

## 样例 #1

### 输入

```
3 1
2 7 6
5 1 7
2 2 4
4 2 1```

### 输出

```
17```

# 题解

## 作者：JK_LOVER (赞：6)

## 题意
给你一个 $n\times n$ 大小的矩阵，每一行和每一列都只能选取 $1$ 个点，每个点都有 $val_{i,j}$ 的收益。当在某行取了之后，如果不小于一些值，还可以多获得 $A_i$ 的收益。[$QWQ$](https://www.luogu.com.cn/blog/xzc/solution-p4877)
## 分析
读完题，可以发现一个很好的性质，$i,j$ 是唯一对应的。那么可以考虑 $dp$ ，定义状态 $dp[s]$ 表示选取了 $s$ 这个集合之后的最大收益。那么就有如下转移
$$
dp[s] = \max(dp[s-j] + val[count(s)][j]) \ j\in s
$$
那么考虑额外贡献，因为可以自己安排顺序，那么一定要让 $P_i$ 最小的靠前。这个很容易想到。那么总复杂度为 $O(n\times 2^n)$ 。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int x = 0,f = 0;char ch = getchar();
	while(!isdigit(ch)) {if(ch=='-')f=1;ch = getchar();}
	while(isdigit(ch)) {x = x * 10 + ch - '0';ch = getchar();}
	return f ? -x : x;
}
const int N = 21;
struct ex{
	int P,A;
};
vector<ex> e[N];
bool cmp(ex a,ex b) {return a.P < b.P;}
int dp[(1<<N)+10],val[N][N],n,m;
int main()
{
	n = read();m = read();
	for(int i = 1;i <= m;i++) {
		int a = read(),b = read(),c = read();
		e[a].push_back((ex){b,c});
	}
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= n;j++) {
			val[j][i] = read();
		}
	}
	for(int i = 1;i <= n;i++) sort(e[i].begin(),e[i].end(),cmp);
	for(int s = 1;s < (1<<n);s++){
		int S = 0;
		for(int j = 1;j <= n;j++) S += ((s>>(j-1))&1);
//		cout << S << " " << s << endl;
		for(int j = 1;j <= n;j++) {
			if((s&(1<<j-1))) {
				dp[s] = max(dp[s],val[S][j]+dp[s^(1<<j-1)]);
			}
		}
		for(int j = 0;j < e[S].size();j++){
			if(dp[s] >= e[S][j].P) dp[s] += e[S][j].A;
		}
	}
	printf("%d\n",dp[(1<<n)-1]);
	return 0;
}
```



---

## 作者：xiaoshumiao (赞：2)

考虑状压 DP。

设 $dp_S$ 表示前 $\operatorname{popcount}(S)$ 头牛参加 $S$ 所表示的集合的比赛所能获得的最大分数，则

$$dp_i=\max_{j \in i}\{dp_{i-j}+s_{j,\operatorname{popcount}(i)}\}$$

最后遍历所有奖励条件，如果 $\operatorname{popcount}(i)=k_j$ 且 $dp_i \ge p_j$ 则 $dp_i \gets dp_i+a_j$。

有一个细节：为了获得尽可能多的奖励分，应该先对奖励分按 $p_i$ 排序。

时间复杂度 $O(2^NN)$。
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=30,_N=1050000; int s[N][N],dp[_N];
struct P { int k,p,a; }c[N];
int main() {
  int n,b; scanf("%d %d",&n,&b);
  for(int i=1;i<=b;i++) scanf("%d %d %d",&c[i].k,&c[i].p,&c[i].a);
  sort(c+1,c+b+1,[](P a,P b) { return a.p<b.p; });
  for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",&s[i][j]);
  for(int i=0;i<(1<<n);i++) {
    //printf("%d %d\n",i,dp[i]);
    int cnt=0;
    for(int j=1;j<=n;j++) cnt+=(i>>(j-1))&1;
    for(int j=1;j<=n;j++) if((i>>(j-1))&1) dp[i]=max(dp[i],dp[i-(1<<(j-1))]+s[j][cnt]);
    for(int j=1;j<=b;j++) if(c[j].k==cnt&&dp[i]>=c[j].p) dp[i]+=c[j].a;
    //printf("%d %d\n",cnt,dp[i]);
  }
  printf("%d",dp[(1<<n)-1]);
  return 0;
}
```

---

## 作者：Yang818 (赞：1)

看了一下三位大佬写的题解，发现没有人用记忆化搜索，本蒟蒻就用记忆化写了一遍代码
### 题目大意
题目大体就是就是几头奶牛，参加任意的比赛，但是每头奶牛参加不同比赛的得分不同，而且有些比赛还有加分项，让你来排列一下怎么参赛

### 分析
先去掉加分项，其实就是一个简单的 $dp$ 吗，然后来个状态压缩就完事了，这道题做完后也可以去尝试一下[P2915](https://www.luogu.com.cn/problem/P2915),跟这一道题蛮像的。加上加分项以后稍微难了那么一点，每次 $dp$到一个比赛的时候判断一下要不要用这个加分项就行了。要注意的是，$dp$ 分过去时和未来时，这道题未来时是行不通的因为它的分数是在看过去的分数之上的，怎么可能从未来推导呢？本蒟蒻最一开始没想通这点，然后发现完全错误，改了个时态和一个初值，就对了！

还有一点，就是记忆化搜索，因为我们不可能开一个 $20$ 维数组，就算开了，判断也要写 $20$ 个 $if$语句，~~要死人的~~，就把它转成二进制，一位表示一头牛。改的时候用掩码，详细见代码中，这样也可以省掉一维数组。~~多香~~
### 代码
话不多说，上代码。

第一段代码是用递归形式写的，第二段用的是递推，个人感觉递推更简单一点。

还有不懂的可以看代码中的注释：
#### 递归：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct tNode{//加分项 
	int k,p,a;
}g_a[21];
int n,b;
int s[21][21],f[1<<20];//21头奶牛足够了 

bool cmp(tNode x,tNode y){//也可以重载小于号 
	return x.k<y.k||x.k==y.k && x.p<y.p;
}

int dfs(int i,int used){//其实也可以用递推做，而且递推比较偏快
	if(i==0)
		return 0;
	if(f[used])
		return f[used];//记忆化，需要注意的是一定是纯函数才可以用记忆化 
	int ans=0; 
	for(int j=0;j<n;j++){
		int mask=1<<j;//先把掩码写好 
		if(!(used&mask)){ 
			ans=max(ans,dfs(i-1,used|mask)+s[j][i]);//这个dp不能写成未来时，所以要用i-1 
		}
	}
	int j=1;
	while(g_a[j].k<i&&j<=b){
		j++;
	}
	while(g_a[j].k==i&&g_a[j].p<=ans)
		ans+=g_a[j++].a;
	f[used]=ans;
	return ans;
		
}

int calc(int x){
	int ans=0;
	while(x!=0){
		ans+=x&1;
		x>>1;//装逼就这么写，当然还有更装逼的方法，用线段树，这里就不写了 
	}
	return ans;
}

int main(){
	cin>>n>>b;
	for(int i=1;i<=b;i++){
		cin>>g_a[i].k>>g_a[i].p>>g_a[i].a;
	}
	for(int i=0;i<n;i++){
		for(int j=1;j<=n;j++){
			cin>>s[i][j];
		}
	}
	sort(g_a+1,g_a+b+1,cmp);//先排序 
	cout<<dfs(n,0);//过去时 
	return 0;
}
```
#### 递推：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct tNode{//加分项 
	int k,p,a;
}g_a[21];
int n,b;
int s[21][21],f[1<<20];//21头奶牛足够了 

bool cmp(tNode x,tNode y){//也可以重载小于号 
	return x.k<y.k||x.k==y.k && x.p<y.p;
}

int main(){
	cin>>n>>b;
	for(int i=1;i<=b;i++){
		cin>>g_a[i].k>>g_a[i].p>>g_a[i].a;
	}
	for(int i=0;i<n;i++){
		for(int j=1;j<=n;j++){
			cin>>s[i][j];
		}
	}
	sort(g_a+1,g_a+b+1,cmp);//先排序 
	for(int used=1;used<(1<<n);used++){
		for(int j=0;j<n;j++){
			int mask=1<<j;
			if(mask&mask)
				f[used]=max(f[used],f[used^mask]+s[j][i]);
		}
		int j=1;
		while(g_a[j].k<i && j<=b)
			j++;
		while(g_a[j].k==i && g_a[j].p<=f[used])
			f[used]+=g_a[j++].a;
	}
	cout<<dfs(n,0);//过去时 
	return 0;
}
```


---

## 作者：DgNeHzL7777 (赞：0)

注意到 $n$ 和 $m$ 都非常小，为了确定出场状态，我们可以来状压 DP。

## 定义状态

假设 $t$ 的二进制中有 $cnt$ 个一，我们用 $dp_t$ 表示**共** $cnt$ 头奶牛比完**第** $cnt$ 场比赛后的最大值。这样的话，我们最后输出 
```cpp
cout<<dp[(1<<n)-1];
```
表示所有奶牛比完了所有比赛。

## 状态转移

转移其实很简单。二进制遍历每一种出场的情况，情况用 $t$ 表示。在 $t$ 的二进制的第 $i$ 位是一，就说明第 $i$ 头牛出场了。很明显，这一头牛出场之后，答案就更新为这头奶牛比赛之前的最大答案加上这头奶牛的贡献。

它其实就是
```cpp
	dp[t]=max(dp[t],dp[t-(1<<(i-1))]+s[i][cnt]);
```
那奖励分怎么办？我们可以暴力地在每种情况中都遍历，反正 $n$ 和 $m$ 都非常小。然而，值得注意的是，我们需要事先把 $p$ 由小到大排序。


代码有注释

```cpp
int mxt=(1<<n)-1;
for(int t=0;t<=mxt;++t){
	int cnt=0;
	for(int i=1;i<=n;++i){
		cnt+=(t>>(i-1)&1);
	}
	//cnt表示t在二进制下1的个数 
	for(int i=1;i<=n;++i){
		if(t>>(i-1)&1)//如果这一个奶牛出场了 
			dp[t]=max(dp[t],dp[t-(1<<(i-1))]/*从这头奶牛比赛之前的最大答案*/+s[i][cnt]/*加上这头奶牛可以得到的分数*/);
	}
//这个c数组存的是奖励信息
	for(int i=1;i<=m;++i){
		if(cnt==c[i].k){/*如果比完cnt场比赛后可以有奖励分*/
			if(dp[t]>=c[i].p){/*就加上。但是一次比赛可能有很多次奖励，所以要对p从小到大进行排序*/ 
				dp[t]+=c[i].a;
			}
		}
	}
}
```

[这里](https://www.luogu.com.cn/paste/khtrjw91)是完整代码。

---


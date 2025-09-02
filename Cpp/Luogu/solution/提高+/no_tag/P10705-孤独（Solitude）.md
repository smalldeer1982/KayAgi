# 孤独（Solitude）

## 题目背景

>$$行走的岁月静好，$$
> 
>$$苍青的天空古老。$$
>
>$$轻轻唱起，$$
>
>$$那只风鸟。$$
>
>$$你却不见了。$$


## 题目描述

给出 $n$ 和 $n$ 个整数 $a_i$（$1\le i\le n$），$n$ 个整数 $b_i$（$1\le i\le n$）。

现在对于一个长为 $n$ 的序列 $S$ 有以下规定：

- $S_i=a_i$ 或 $b_i$。

- 对于所有的 $S_i$（$1\le i\le n$），若 $S_i>S_{i-1}$ 且 $S_i>S_{i+1}$ 那么称 $S_i$ 为**峰**，特别地 $S_0=S_{n+1}=0$。

**现求：最大峰数以及取到最大峰数时的最大极差。**

**极差：一个序列中最大值和最小值的差。**

**updated：$S_0$ 和 $S_{n+1}$ 不参与极差运算。**

## 说明/提示

#### 【样例解释】

样例一中 $S$ 序列的一种合法方案为 $9,1,2,4,1,10$。

其中 $S_1,S_4,S_6$ 为**峰**，最大值为 $10-1=9$。 

#### 【数据范围】

| subtask 编号 | $n$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $0$ | $\le 20$ | $-$ | $10$ |
| $1$ | $\le 2000$ | $-$ | $10$ |
| $2$ | $\le 10^5$ | $A$ | $10$ |
| $3$ | $\le 10^5$ | $B$ | $10$ |
| $4$ | $\le 10^5$ | $C$ | $10$ |
| $5$ | $\le 5\times10^5$ | $-$ | $50$ |

特殊性质 $A$：$\forall 1< i\le n$，$\text{max}(a_{i-1},b_{i-1})\le \text{min}(a_i,b_i)$。

特殊性质 $B$：$\forall 1< i\le n$，$\text{min}(a_i,b_i)\le\text{max}(a_{i-1},b_{i-1})\le\text{max}(a_i,b_i)$。

特殊性质 $C$：$\forall 1\le i\le n$，$a_i=k$，$k$ 是一个正整数。

对于 $100\%$ 的数据，$1\le n\le 5\times10^5$，$1\le a_i,b_i\le 10^9$，保证 $a_i\ne b_i$。

**特别提醒：本题使用 subtask 捆绑测试，只有通过一个子任务的全部测试点才能获得此子任务的分数。**

## 样例 #1

### 输入

```
6
9 1 2 4 7 10 
8 10 5 1 1 7 ```

### 输出

```
3
9```

## 样例 #2

### 输入

```
10
6 13 27 31 34 59 64 66 71 95 
4 4 10 22 26 28 46 55 62 68 ```

### 输出

```
5
91```

# 题解

## 作者：251Sec (赞：9)

官方题解在说啥？？？

只有第一问是简单的，直接 DP 设 $f(i,0/1,0/1)$ 代表前 $i$ 个数，最后一个数是 $a_i$ 还是 $b_i$，最后一个数是否大于倒数第二个数，最大的峰个数。复杂度 $O(n)$。

加上第二问之后，套路地，我们发现最大极差就等价于在序列里任选两个数 $x,y$（可以相同），然后最大化 $x-y$。那么我们在 DP 里再加两维 $0/1$ 代表是否选出了 $x,y$，复杂度 $O(n)$，带巨大常数。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, a[500005][2];
struct Node {
	int a, b;
	bool operator<(const Node &o) const {
		if (a != o.a) return a < o.a;
		return b < o.b;
	}
} f[500005][2][2][2][2];
void chkmax(Node &a, Node b) { a = max(a, b); }
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i][0]);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i][1]);
	for (int i = 0; i <= n + 1; i++) {
		for (int p = 0; p < 2; p++) {
			for (int q = 0; q < 2; q++) {
				for (int r = 0; r < 2; r++) {
					for (int s = 0; s < 2; s++) {
						if (p + q + r + s + i) f[i][p][q][r][s] = { (int)-1e9, (int)-1e9 };
					}
				}
			}
		}
	}
	for (int i = 1; i <= n + 1; i++) {
		for (int p = 0; p < 2; p++) {
			for (int q = 0; q < 2; q++) {
				for (int r = 0; r < 2; r++) {
					for (int s = 0; s < 2; s++) {
						for (int np = 0; np < 2; np++) {
							auto t = f[i - 1][p][q][r][s];
							if (q && a[i][np] < a[i - 1][p]) t.a++;
							chkmax(f[i][np][a[i][np] > a[i - 1][p]][r][s], t);
						}
					}
				}
			}
		}
		for (int p = 0; p < 2; p++) {
			for (int q = 0; q < 2; q++) {
				for (int r = 0; r < 2; r++) {
					for (int s = 0; s < 2; s++) {
						if (i <= n) {
							if (r) {
								auto t = f[i][p][q][0][s];
								t.b += a[i][p];
								chkmax(f[i][p][q][r][s], t);
							}
							if (s) {
								auto t = f[i][p][q][r][0];
								t.b -= a[i][p];
								chkmax(f[i][p][q][r][s], t);
							}
						}
					}
				}
			}
		}
	}
	Node res = f[n + 1][0][0][1][1];
	printf("%d\n%d\n", res.a, res.b);
	return 0;
}
```

---

## 作者：yywlp (赞：5)

## 题解

一句话总结：dp，建图，dp。

先处理**最大峰数**，我们设 $f_{i,j}(j=0,1,2)$ 表示在 $S_i$ 与 $S_{i-1}$ 为某种大小关系时峰的最大个数，会发现只有三种情况：

- $j=0$ 表示 $S_{i-1}>S_i$

- $j=1$ 表示 $S_{i-1}=S_i$

- $j=2$ 表示 $S_{i-1}<S_i$

但是又因为每个 $S_i$ 有两种取值，所以把 $j$ 扩展一下，$0,1,2$ 对应 $S_i=a_i$，$3,4,5$ 对应 $S_i=b_i$。

那么对于每次转移，因为 $a_i,b_i$ 和 $a_{i-1},b_{i-1}$ 各有一种关系，总共**四种关系**，所以只需要判断一下属于哪种情况对应转移就行，这里转移很好推，就不细讲了。

这里有一点要注意，因为 $S_0=S_{n+1}=0$ 所以应该枚举到 $n+1$，否则可能会算少。

该怎么在**最大峰数**的基础上求出**最大极差**呢？

可以这样想，最小值最大值一定在某一种选择序列中，那么我们先把得到最大值的路线标出来，也就是从 $f_{n+1}$ 开始，看看其中的最大值是从 $f_n$ 的哪个 $j$ 转移过来的，连边，再继续处理那个转移过来的位置，将整个**转移图**建出来，不难发现，在**转移图**上直接或间接相连的点一定是某种合法方案的点集中的点。

这里要注意，因为前面 $f_{i,j}$ 的定义相当于把一个点**拆成**了三个点，又因为有 $a,b$ 两种取法，所以会出现六个点，这六个点是**独立的**，在后面处理的时候不能当做同一个点。

那么接下来的做法就不难想了。

我们可以枚举一个**连接点**，答案的方案一定可以在某个**连接点**的左边和右边，那么只要能把**转移图**上每个点前面后面的最小最大值求出来就可以了。

那么可以再 dp 一次，根据**转移图**设 $mxl_{i,j},mnl_{i,j},mxr_{i,j},mnr_{i,j}$。

$i,j$ 的意义不变，四个不同的数组分别表示对于 $(i,j)$ 在**转移图**上**从左到右**的最大最小值和**从右到左**的最大最小值（建出来的图实际上是**一层一层**的，所以当成普通的 dp 来做即可），求出来后只需要 $6n$ 枚举**连接点**然后求最大值即可。时间复杂度 $\Theta(n)$。不过因为拆点等原因，可能常数会比较大。

其实**最大极差**也可以分治来求，不过既难写还慢，就不讲了，实测比 $\Theta(n)$ 的大概慢了 $3$ 倍。

此外，出题人的朋友提出**最大极差**可以用 ddp 做，不过过不了 $100\%$ 的数据，只能过 $10^5$ 左右的范围。但是出题人没有学过 ddp 也就没去写。~~其实最开始的范围就是 $10^5$，不过在朋友说了之后加强到了 $5\times 10^5$。~~

## Code 1
这是验题人的代码，简洁、易懂、迅速且空间小。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e6+100;
int n,dp[N][3][3],s[N][3],ans,sit[N][3][3];
int head[N],to[N],ne[N],tot,in[N];
int fhead[N],fto[N],fne[N],ftot,fin[N];
void fadd(int x,int y){
	fne[++ftot]=fhead[x];
	fto[ftot]=y;
	fhead[x]=ftot;
	fin[y]++;
}
void add(int x,int y){
	ne[++tot]=head[x];
	to[tot]=y;
	head[x]=tot;
	in[y]++;
	fadd(y,x);
} 
void DP(){
	for(int i=2;i<=n+1;i++){
		for(int k=0;k<=1;k++){// i
			for(int j=0;j<=1;j++){// i-1
				for(int g=0;g<=1;g++){ //i-2
					int bb=dp[i-1][j][g];
					if(s[i-1][j]>s[i][k] and s[i-1][j]>s[i-2][g]) bb++;
					dp[i][k][j]=max(dp[i][k][j],bb);
				}
				if(i==n+1) ans=max(ans,dp[i][k][j]);
			}
		}
	}
}
struct node{int i,k,j,id;}a[N]; int cnt,bcnt;
void build(){
	queue<node>q;
	for(int k=0;k<=1;k++) for(int j=0;j<=1;j++) if(dp[n+1][k][j]==ans) ++cnt,a[cnt]=(node){n+1,k,j,cnt},q.push(a[cnt]);
	bcnt=cnt;
	for(int i=1;i<=bcnt;i++){
		node u=q.front(); q.pop();
		int k=u.k,j=u.j;
		for(int g=0;g<=1;g++){
			int bb=dp[u.i-1][j][g];
			if(s[u.i-1][j]>s[u.i][k] and s[u.i-1][j]>s[u.i-2][g]) bb++;
			if(bb==dp[u.i][k][j] and !sit[u.i][j][g]) 
				cnt++,a[cnt]=(node){u.i-1,j,g,cnt},q.push(a[cnt]),sit[u.i-1][j][g]=cnt;
		}
	}
	while(!q.empty()){
		node u=q.front(); q.pop();
		if(u.i==1) continue;
		int k=u.k,j=u.j;
		for(int g=0;g<=1;g++){
			int bb=dp[u.i-1][j][g];
			if(s[u.i-1][j]>s[u.i][k] and s[u.i-1][j]>s[u.i-2][g]) bb++;
			if(bb==dp[u.i][k][j]){
				if(sit[u.i-1][j][g]) add(sit[u.i-1][j][g],u.id);
				else{
					++cnt;
					a[cnt]=(node){u.i-1,j,g,cnt},q.push(a[cnt]);
					sit[u.i-1][j][g]=cnt;
					add(cnt,u.id);
				}
			}
		}
	}
}
int mi[N],mx[N];
void bfs(){
	queue<int>q;
	for(int i=bcnt+1;i<=cnt;i++){
		if(!in[i]) q.push(i);
		mi[i]=mx[i]=s[a[i].i][a[i].k];
	}
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=head[u];i;i=ne[i]){
			int v=to[i];
			mi[v]=min(mi[v],mi[u]),mx[v]=max(mx[v],mx[u]);
			in[v]--;
			if(!in[v]) q.push(v);
		}
	}
	return;
}
int fmi[N],fmx[N];
void fbfs(){
	queue<int>q;
	for(int i=bcnt+1;i<=cnt;i++){
		if(!fin[i]) q.push(i);
		fmi[i]=fmx[i]=s[a[i].i][a[i].k];
	}
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=fhead[u];i;i=fne[i]){
			int v=fto[i];
			fmi[v]=min(fmi[v],fmi[u]),fmx[v]=max(fmx[v],fmx[u]);
			fin[v]--;
			if(!fin[v]) q.push(v);
		}
	}
	return;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&s[i][0]);
	for(int i=1;i<=n;i++) scanf("%d",&s[i][1]);
	if(n==1){puts("0"),puts("0");return 0;}
	DP();
	build(),bfs(),fbfs();
	int res=0;
	for(int i=bcnt+1;i<=cnt;i++){
		res=max(res,mx[i]-fmi[i]);
		res=max(res,fmx[i]-mi[i]);
	}
	cout<<ans<<endl<<res;
	return 0;
}
```


## Code 2

这是出题人的代码，冗长、难懂、缓慢且空间大。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define mk(x,y) make_pair(x,y)
const int M=5e5+10,N=5e6+10;
int n;
int a[M],b[M];
bool pd[N];
vector<pii> nex[M][6],lst[M][6];
int f[M][6];//0 上 1 中 2 下
int get(pii nn){
	if(nn.second<=2)return a[nn.first];
	return b[nn.first];
}
int get(int x,int y){
	return x*10+y;
}
void add(int i,int j);
void add(int x,int a,int y,int b){
	nex[x][a].push_back(mk(y,b));
	lst[y][b].push_back(mk(x,a));
	if(!pd[get(x,a)]){
		pd[get(x,a)]=true;
		add(x,a);
	}
}
void add(int i,int j){
	if(i==1)return;
	if(j==0){
		if(a[i]<a[i-1]){
			if(f[i][0]==f[i-1][0])add(i-1,0,i,0);
			if(f[i][0]==f[i-1][1])add(i-1,1,i,0);
			if(f[i][0]==f[i-1][2]+1)add(i-1,2,i,0);
		}
		if(a[i]<b[i-1]){
			if(f[i][0]==f[i-1][3])add(i-1,3,i,0);
			if(f[i][0]==f[i-1][4])add(i-1,4,i,0);
			if(f[i][0]==f[i-1][5]+1)add(i-1,5,i,0);
		}
	}else if(j==1){
		if(a[i]==a[i-1]){
			if(f[i][1]==f[i-1][0])add(i-1,0,i,1);
			if(f[i][1]==f[i-1][1])add(i-1,1,i,1);
			if(f[i][1]==f[i-1][2])add(i-1,2,i,1);
		}
		if(a[i]==b[i-1]){
			if(f[i][1]==f[i-1][3])add(i-1,3,i,1);
			if(f[i][1]==f[i-1][4])add(i-1,4,i,1);
			if(f[i][1]==f[i-1][5])add(i-1,5,i,1);
		}
	}else if(j==2){
		if(a[i]>a[i-1]){
			if(f[i][2]==f[i-1][0])add(i-1,0,i,2);
			if(f[i][2]==f[i-1][1])add(i-1,1,i,2);
			if(f[i][2]==f[i-1][2])add(i-1,2,i,2);
		}
		if(a[i]>b[i-1]){
			if(f[i][2]==f[i-1][3])add(i-1,3,i,2);
			if(f[i][2]==f[i-1][4])add(i-1,4,i,2);
			if(f[i][2]==f[i-1][5])add(i-1,5,i,2);
		}
	}else if(j==3){
		if(b[i]<a[i-1]){
			if(f[i][3]==f[i-1][0])add(i-1,0,i,3);
			if(f[i][3]==f[i-1][1])add(i-1,1,i,3);
			if(f[i][3]==f[i-1][2]+1)add(i-1,2,i,3);
		}
		if(b[i]<b[i-1]){
			if(f[i][3]==f[i-1][3])add(i-1,3,i,3);
			if(f[i][3]==f[i-1][4])add(i-1,4,i,3);
			if(f[i][3]==f[i-1][5]+1)add(i-1,5,i,3);
		}
	}else if(j==4){
		if(b[i]==a[i-1]){
			if(f[i][4]==f[i-1][0])add(i-1,0,i,4);
			if(f[i][4]==f[i-1][1])add(i-1,1,i,4);
			if(f[i][4]==f[i-1][2])add(i-1,2,i,4);
		}
		if(b[i]==b[i-1]){
			if(f[i][4]==f[i-1][3])add(i-1,3,i,4);
			if(f[i][4]==f[i-1][4])add(i-1,4,i,4);
			if(f[i][4]==f[i-1][5])add(i-1,5,i,4);
		}
	}else{
		if(b[i]>a[i-1]){
			if(f[i][5]==f[i-1][0])add(i-1,0,i,5);
			if(f[i][5]==f[i-1][1])add(i-1,1,i,5);
			if(f[i][5]==f[i-1][2])add(i-1,2,i,5);
		}
		if(b[i]>b[i-1]){
			if(f[i][5]==f[i-1][3])add(i-1,3,i,5);
			if(f[i][5]==f[i-1][4])add(i-1,4,i,5);
			if(f[i][5]==f[i-1][5])add(i-1,5,i,5);
		}
	}
}
void work_dp(){
	for(int i=2;i<=n+1;i++){
		int la=max(max(f[i-1][0],f[i-1][1]),f[i-1][2]);
		int lb=max(max(f[i-1][3],f[i-1][4]),f[i-1][5]);
		if(a[i]>a[i-1])f[i][2]=la;
		if(a[i]==a[i-1])f[i][1]=la;
		if(a[i]<a[i-1])f[i][0]=max(max(f[i-1][0],f[i-1][1]),f[i-1][2]+1);
		if(a[i]>b[i-1])f[i][2]=max(f[i][2],lb);
		if(a[i]==b[i-1])f[i][1]=max(f[i][1],lb);
		if(a[i]<b[i-1])f[i][0]=max(f[i][0],max(max(f[i-1][3],f[i-1][4]),f[i-1][5]+1));
		if(b[i]>a[i-1])f[i][5]=la;
		if(b[i]==a[i-1])f[i][4]=la;
		if(b[i]<a[i-1])f[i][3]=max(max(f[i-1][0],f[i-1][1]),f[i-1][2]+1);
		if(b[i]>b[i-1])f[i][5]=max(f[i][5],lb);
		if(b[i]==b[i-1])f[i][4]=max(f[i][4],lb);
		if(b[i]<b[i-1])f[i][3]=max(f[i][3],max(max(f[i-1][3],f[i-1][4]),f[i-1][5]+1));
	}
	if(f[n][0]==f[n+1][0])add(n,0);
	if(f[n][1]==f[n+1][0])add(n,1);
	if(f[n][2]+1==f[n+1][0])add(n,2);
	if(f[n][3]==f[n+1][0])add(n,3);
	if(f[n][4]==f[n+1][0])add(n,4);
	if(f[n][5]+1==f[n+1][0])add(n,5);
}
int mxl[M][6],mnl[M][6],mxr[M][6],mnr[M][6];
int solve(){
	for(int i=1;i<=n;i++){
		for(int j=0;j<=5;j++){
			mxl[i][j]=mxr[i][j]=0;
			mnl[i][j]=mnr[i][j]=1e9+1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=5;j++){
			pii zc=mk(i,j);
			int val=get(zc);
			mxl[i][j]=max(mxl[i][j],val),mnl[i][j]=min(mnl[i][j],val);
			for(pii nx:nex[i][j]){
				int u=nx.first,v=nx.second;
				mxl[u][v]=max(mxl[u][v],mxl[i][j]);
				mnl[u][v]=min(mnl[u][v],mnl[i][j]);
			}
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=0;j<=5;j++){
			pii zc=mk(i,j);
			int val=get(zc);
			mxr[i][j]=max(mxr[i][j],val),mnr[i][j]=min(mnr[i][j],val);
			for(pii lt:lst[i][j]){
				int u=lt.first,v=lt.second;
				mxr[u][v]=max(mxr[u][v],mxr[i][j]);
				mnr[u][v]=min(mnr[u][v],mnr[i][j]);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=5;j++){
			for(pii nx:nex[i][j]){
				int u=nx.first,v=nx.second;
				ans=max(ans,max(mxl[i][j]-mnr[u][v],mxr[u][v]-mnl[i][j]));
			}
		}
	}
	return ans;
}
signed main(){
	freopen("temp.in","r",stdin);
	freopen("temp.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	work_dp();
	memset(pd,0,sizeof pd);
	cout<<max(max(f[n+1][0],f[n+1][1]),f[n+1][2])<<endl<<solve();
//	cout<<"sum:"<<sum<<endl;
	return 0;
}
```

---

## 作者：small_john (赞：3)

## 前言

赛时切了这道题，写篇题解纪念一下。

## 思路

首先思考如何求出最大峰数。

设 $f_{i,0/1,0/1}$ 表示前 $i$ 位，选 $a_i$（对应第二维的 $0$）还是 $b_i$（对应第二维的 $1$），小于等于前一个数（对应第三维的 $0$）还是大于前一个数（对于第三维的 $1$）的最大峰数。转移很明显：枚举 $i$，枚举当前这一位和上一位选的数（记为 $x,y$）。如果 $x<y$，当前状态从上一位对应第三维为 1 的状态转移过来对峰的贡献为 1，否则为 0。

这样最大峰数就是 $\max(f_{n,0,0},f_{n,0,1}+1,f_{n,1,0},f_{n,1,1}+1)$。加一的原因是需要考虑最后一位对答案的贡献。问题在于如何求最大极差。

考虑建图，如果 $f_{i-1,a,b}$ 转移到 $f_{i,x,y}$ 是最优的，我们就连一条 $(i-1,a,b)\to(i,x,y)$ 的边。不难发现，这张图是一张拓扑图。

定义最优决策点 $(n,x,y)$ 满足在此状态下可以取得答案，则任意一条从 $(1,a,b)$ 到最优决策点的路径都可以得到最大峰数。问题就被转换为了拓扑图上路径最大极差。

设起点（第一维是一的点）为 $s$，终点（一个最优决策点，需要枚举）为 $t$，把路径上的点拆成三部分：$s\to (a,b,c)$（不包括点 $(a,b,c)$），点 $(a,b,c)$，以及 $(a,b,c)\to t$（不包括点 $(a,b,c)$）。钦定点 $(a,b,c)$ 是路径上的最小值或者最大值，最大值或者最小值在这个点到最优决策点的路径上，这样一定可以覆盖所有情况。

那么做法就呼之欲出了，记 $mx_{a,b,c}$ 为这个点到到最优决策点路径的最大值，$mn_{a,b,c}$ 同理，而这两个数组可以轻松在原图的反图上遍历获得。枚举这个点，计算极差，对于所有的答案取最大值即可。

时间复杂度为 $O(n)$，常数比较大。

## 代码

注：代码比较冗长，请适当参考。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n,a[N][2],f[N][2][2];
vector<int> g[N*4];//记得开四倍空间
int id[N][2][2],cnt,mn[N*4],mx[N*4],du[N*4],val[N*4],ans_;
inline void sol(int u)
{
	for(int i = 1;i<=cnt;i++) du[i] = 0,mn[i] = 2e9,mx[i] = -1;
	for(int i = 1;i<=cnt;i++)
		for(auto j:g[i]) du[j]++;
	queue<int> q;
	for(int i = 1;i<=cnt;i++) if(!du[i]) q.push(i);
	mn[u] = mx[u] = val[u];
	while(!q.empty())
	{
		int u = q.front();q.pop();
		for(auto v:g[u])
		{
			du[v]--;
			if(mn[u]<2e9) mn[v] = min(mn[v],mn[u]),mn[v] = min(mn[v],val[u]);
			if(mx[u]>-1) mx[v] = max(mx[v],mx[u]),mx[v] = max(mx[v],val[u]);
			if(!du[v]) q.push(v);
		}
	}
	for(int i = 1;i<=n;i++)
		for(int j = 0;j<2;j++)
			for(int k = 0;k<2;k++)
			{
				if(f[i][j][k]==-1) continue;//不存在从起始点到 (i,j,k) 的路径
				int d = id[i][j][k];
				if(mn[d]==2e9||mx[d]==-1) continue;//不存在从 (i,j,k) 到终点的路径
				ans_ = max(ans_,max(abs(mx[d]-val[d]),abs(mn[d]-val[d])));
			}
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i = 1;i<=n;i++)
		cin>>a[i][0];
	for(int i = 1;i<=n;i++)
		cin>>a[i][1];
	memset(f,-1,sizeof f);
	f[0][0][0] = f[0][1][0] = 0;
	for(int i = 1;i<=n;i++)
	{
		for(int j = 0;j<2;j++)
			for(int k = 0;k<2;k++)
			{
				if(a[i][j]<a[i-1][k]&&f[i-1][k][1]!=-1) f[i][j][0] = max(f[i][j][k],f[i-1][k][1]+1);
				int w = (a[i][j]>a[i-1][k]);
				if(f[i-1][k][0]!=-1) f[i][j][w] = max(f[i][j][w],f[i-1][k][0]);
				if(f[i-1][k][1]!=-1) f[i][j][w] = max(f[i][j][w],f[i-1][k][1]);
			}
	}
	for(int i = 1;i<=n;i++)
		for(int j = 0;j<2;j++)
			for(int k = 0;k<2;k++)
				id[i][j][k] = ++cnt,val[cnt] = a[i][j];
	//这里直接建反图
	for(int i = 1;i<=n;i++)
		for(int j = 0;j<2;j++)
			for(int k = 0;k<2;k++)
			{
				if(a[i][j]<a[i-1][k]&&f[i-1][k][1]!=-1&&f[i][j][0]==f[i-1][k][1]+1)
				    g[id[i][j][0]].push_back(id[i-1][k][1]);
				int w = (a[i][j]>a[i-1][k]);
				if(f[i][j][w]==-1) continue; 
				if(f[i][j][w]==f[i-1][k][0]) g[id[i][j][w]].push_back(id[i-1][k][0]);
				if(f[i][j][w]==f[i-1][k][1]) g[id[i][j][w]].push_back(id[i-1][k][1]);
			}
	int ans = max({f[n][0][0],f[n][0][1]+1,f[n][1][0],f[n][1][1]+1});
	cout<<ans<<'\n';
	//枚举最优决策点
	if(f[n][0][0]==ans) sol(id[n][0][0]);
	if(f[n][0][1]+1==ans) sol(id[n][0][1]);
	if(f[n][1][0]==ans) sol(id[n][1][0]);
	if(f[n][1][1]+1==ans) sol(id[n][1][1]);
	cout<<ans_;
	return 0;
}
```

---

## 作者：operator_ (赞：2)

# P10705 孤独（Solitude）

[题目传送门](https://www.luogu.com.cn/problem/P10705)

## 题解

看官方题解还建了个图？实际纯 dp 即可。

第一问，最大峰数，这个 dp 很好求。具体而言，设 $f_{i,j,k}$ 表示前 $i$ 个数，第 $i-1$ 个选了哪个，第 $i$ 个选了哪个，转移直接枚举选什么。考虑到当前的末尾点并不好考虑是不是峰，所以我们钦定该状态维护的是前 $i-1$ 个数的答案。

第二问，在上一问的条件下的最大极差。极差直接做不好办，因为最大值和最小值不存在单调关系，所以我们考虑枚举一个值。假设我枚举一个数作为最大值，那么我就要考虑当前情况且答案最大的情况下最小值最小是多少。

于是，序列被分成了两段，一个前缀和一个后缀。于是便有一个极其自然的思路：前后各 dp 一遍然后合并。我们维护一个 $Mn_{i,j,k}$ 表示 $f$ 最大的情况下，该前/后缀最小值最小是多少，同样的，我们钦定该状态维护的是前 $i-1$ 个数的最小值。

然后对于我们枚举的最大值，把前后两个数的选择枚举一下就可以合并了。实现起来很简单。

代码：

```cpp
/*
 * @Author: operator_ 
 * @Date: 2024-07-06 13:53:32 
 * @Last Modified by: operator_
 * @Last Modified time: 2024-07-06 22:07:12
 */
#include<bits/stdc++.h>
using namespace std;
inline int rd() {
    int s=0,m=0;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
    while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}
const int inf=1e9;
int n,a[500005][2],b[500005][2],f1[500005][2][2],Mn1[500005][2][2],f2[500005][2][2],Mn2[500005][2][2];
int ans1,ans2;
signed main(){
    cin>>n;
    for(int j=0;j<=1;j++) for(int i=1;i<=n;i++) a[i][j]=rd();
    memset(f1,-0x3f,sizeof(f1));memset(Mn1,0x3f,sizeof(Mn1));
    f1[0][0][0]=0;
    for(int i=1;i<=n+2;i++) for(int j=0;j<=1;j++) for(int k=0;k<=1;k++) for(int l=0;l<=1;l++) {
        int r=(a[i-1][k]>a[i-2][j]&&a[i-1][k]>a[i][l]);
        if(f1[i][k][l]<f1[i-1][j][k]+r) {
            f1[i][k][l]=f1[i-1][j][k]+r;
            Mn1[i][k][l]=min(Mn1[i-1][j][k],(i==1?inf:a[i-1][k]));
        }
        else if(f1[i][k][l]==f1[i-1][j][k]+r)
            Mn1[i][k][l]=min(Mn1[i][k][l],min(Mn1[i-1][j][k],(i==1?inf:a[i-1][k])));
    }
    for(int i=1;i<=n/2;i++) for(int j=0;j<=1;j++) swap(a[i][j],a[n-i+1][j]);
    memset(f2,-0x3f,sizeof(f2));memset(Mn2,0x3f,sizeof(Mn2));
    f2[0][0][0]=0;
    for(int i=1;i<=n;i++) for(int j=0;j<=1;j++) for(int k=0;k<=1;k++) for(int l=0;l<=1;l++) {
        int r=(a[i-1][k]>a[i-2][j]&&a[i-1][k]>a[i][l]);
        if(f2[i][k][l]<f2[i-1][j][k]+r) {
            f2[i][k][l]=f2[i-1][j][k]+r;
            Mn2[i][k][l]=min(Mn2[i-1][j][k],(i==1?inf:a[i-1][k]));
        }
        else if(f2[i][k][l]==f2[i-1][j][k]+r)
            Mn2[i][k][l]=min(Mn2[i][k][l],min(Mn2[i-1][j][k],(i==1?inf:a[i-1][k])));
    }
    for(int i=1;i<=n/2;i++) for(int j=0;j<=1;j++) swap(a[i][j],a[n-i+1][j]);
    int ans1=f1[n+2][0][0];
    for(int i=1;i<=n;i++) for(int j=0;j<=1;j++) for(int k=0;k<=1;k++) for(int l=0;l<=1;l++) {
        int r=(a[i][k]>a[i-1][j]&&a[i][k]>a[i+1][l]);
        if(f1[i][j][k]+f2[n-i+1][l][k]+r==ans1) ans2=max(ans2,a[i][k]-min(Mn1[i][j][k],Mn2[n-i+1][l][k]));
    }
    cout<<ans1<<endl<<ans2<<endl;
    return 0;
}
```

---

## 作者：robinyqc (赞：2)

其实这题可以贪心，而且思路很简单，感觉比 DP 转移具体多了。

首先若 $a_i > b_i$ 则交换，此时就是有若干个区间 $c_i = [a_i, b_i]$。由于要公差最大，所以若 $S_i$ 为峰则 $S_i = b_i$，否则 $S_i = a_i$。

称一个极长的子段 $c_{l..r}$，满足 $\forall i \in [l, r), |c_i \cap c_{i + 1}| > 0$， 为好的。整个序列被分为若干个好的子段。

> 推论：对于每个 $i\in (l, r)$ 必有 $b_i > a_{i - 1}, a_{i + 1}$。根据定义易证。

显然不同的好段是互不干扰的，每个好段是独立的问题。因为相邻段的边界，按定义没有交。那么不管怎么选，$S_i$ 和 $S_{i + 1}$ 的大小关系都是固定的。

而对于一个好的子段，由于峰不可能连续出现，所以最多只能选段长一半的峰出来，而满足这个数量上限的策略 $ababababab\dots$ 或 $bababababa\dots$，**根据推论，一定是合法的选择方案**。所以每段只会用这两种策略之一。求出这样选，子段的最大值和最小值（当两种选法峰数一样时，两个选法的最大值最小值都要算）。

问题转化为有若干个二元组 $((mn_1, mx_1), (mn_2, mx_2))$，你每次可以选择其中之一，将两个数加入集合，使极差最大。

这个也可以贪心做。简单来说，维护前缀 $\min$ 和 前缀 $\max$，答案仅可能是当前段的极差，或者当前段 $\max$ 与前缀 $\min$ 的差，或者前缀 $\max$ 与当前段 $\min$ 的差。总之只要保证极差不是同一段的两种策略各选一个 $\min$ 或 $\max$ 就行了。

可能讲得有点抽象，所以可以参考一下代码：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using i32 = int;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

template<typename T> using vec = vector<T>;

#define int long long

signed main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vec<int> a(n + 2), b(n + 2);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        if (b[i] < a[i]) swap(a[i], b[i]);
    }

	// 判断两个区间是否有交
    auto intersect = [](int l1, int r1, int l2, int r2)
    {
        return min(r1, r2) - max(l1, l2) > 0;
    };

    int mx = -1e18, mn = 1e18, ans = -1e18, ansc = 0;

    for (int i = 1, j; i <= n; i = j + 1) {
        for (j = i; j <= n; j++) {
            if (!intersect(a[j], b[j], a[j + 1], b[j + 1])) {
                break;
            }
        }
        int mn1 = 1e18, mx1 = -1e18, mn2 = 1e18, mx2 = -1e18, cnt1 = 0, cnt2 = 0;
		// 计算好的子段的两种选法的最大值、最小值、峰的数量。
        for (int k = i; k <= j; k++) {
            if (k & 1) {
                mn1 = min(mn1, a[k]);
                mx1 = max(mx1, a[k]);
                mn2 = min(mn2, b[k]);
                mx2 = max(mx2, b[k]);
				// 这个判断是处理边界能不能成峰的。
                if (b[k] > a[k - 1] && b[k] > a[k + 1]) cnt2++;
            }
            else {
                mn1 = min(mn1, b[k]);
                mx1 = max(mx1, b[k]);
                mn2 = min(mn2, a[k]);
                mx2 = max(mx2, a[k]);
                if (b[k] > a[k - 1] && b[k] > a[k + 1]) cnt1++;
            }
        }

        ansc += max(cnt1, cnt2);

        if (cnt1 < cnt2) {
            ans = max(ans, mx2 - mn2);
            ans = max(ans, mx2 - mn);
            ans = max(ans, mx - mn2);
            mx = max(mx, mx2), mn = min(mn, mn2);
        }
        else if (cnt1 > cnt2) {
            ans = max(ans, mx1 - mn1);
            ans = max(ans, mx1 - mn);
            ans = max(ans, mx - mn1);
            mx = max(mx, mx1), mn = min(mn, mn1);
        }
        else {
			// 两个选法峰数相同则都有可能使用。
			// 只要保证极差不由同一段 mx1 - mn2 或 mx2 - mn1 构成就可以了。
            ans = max(ans, mx1 - mn1);
            ans = max(ans, mx2 - mn2);
            ans = max(ans, mx1 - mn);
            ans = max(ans, mx2 - mn);
            ans = max(ans, mx - mn1);
            ans = max(ans, mx - mn2);
            mx = max({mx, mx1, mx2});
            mn = min({mn, mn1, mn2});
        }
    }

    cout << ansc << '\n' << ans << endl;

    return 0;
}
```

另附一个赛后简化后的代码：[simplified_code](https://www.luogu.com.cn/paste/qp6ewoab)。

---

## 作者：Acheron_RBM (赞：1)

先求最大峰数，那如何在最大峰数取到最大极差呢？

在加入一个点时，如果极差会改变，一定是用它和之前满足最大峰数时能取到的的最大值和最小值分别作差，看能否更新极差。

这个时候，我们发现这三个值都可以通过 dp 维护，所以就不需要建图了。

这个时候转移就有四种状态：选 $a$ 或 $b$，比前面选的大还是小。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[600000][2];
struct node
{
    int maxx,minn;
	int sk;
	int cnt;
}dp[600000][2][2];
node maxk(node x,node y)
{
    if(x.maxx==-1)
	{
		return y;
	}
    if(y.maxx==-1)
	{
		return x;
	}
    if(x.cnt!=y.cnt)
	{
        if(x.cnt>y.cnt)
		{
			return x;
		}
        else
		{
			return y;
		}
    }
    x.maxx=max(x.maxx,y.maxx);
    x.minn=min(x.minn,y.minn);
    x.sk=max(x.sk,y.sk);
    return x;
}
signed main()
{
	cin>>n;
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i][0];
	}
    for(int i=1;i<=n;i++)
	{
		cin>>a[i][1];
	}
    for(int i=1;i<=n;i++)
    {
    	for(int j=0;j<2;j++)
    	{
    		for(int k=0;k<2;k++)
    		{
    			dp[i][j][k]={-1,1000000001,0,0};
			}
		}
	}
    for(int i=0;i<2;i++)
    {
    	dp[1][i][0]={a[1][i],a[1][i],0,0};
	}
    for(int i=2;i<=n;i++)
	{
        for(int j=0;j<2;j++)
        {
        	for(int k=0;k<2;k++)
			{
                for(int o=0;o<2;o++)
				{
                    if((bool)(a[i][j]>a[i-1][o])==(bool)k)
					{
						continue;	
					}
                    for(int q1=0;q1<2;q1++)
					{
                        if(dp[i-1][o][q1].maxx==-1)
						{
							continue;
						}
                        node num=dp[i-1][o][q1];
                        if(q1==0&&a[i][j]<a[i-1][o])
						{
							num.cnt++;
						}
                        num.sk=max(max(a[i][j]-num.minn,num.maxx-a[i][j]),num.sk);
                        num.maxx=max(num.maxx,a[i][j]);
                        num.minn=min(num.minn,a[i][j]);
                        dp[i][j][k]=maxk(dp[i][j][k],num);
                    }
                }
            }
		}  
    }
    dp[n][0][0].cnt++;
    dp[n][1][0].cnt++;
    node ret=maxk(maxk(dp[n][0][0],dp[n][0][1]),maxk(dp[n][1][0],dp[n][1][1]));
    cout<<ret.cnt<<"\n"<<ret.sk;
	return 0;
}
```

---

## 作者：聊机 (赞：1)

~~赛时 T3，T4 都没做出来。于是来写个 T2 的题解。~~

感觉出题人做法有点麻烦了，这题不需要建图，可以直接 DP。

最大峰数是好求的，考虑如何在最大峰数取到最大极差。我们发现新加入一个点时，如果我们想要让它对极差产生影响，就是用它和之前满足最大峰数时能取到的的最大值和最小值分别作差，看能否更新极差。

于是我们只需在 DP 的同时维护另外三个值，首先是在**满足最大峰数**的情况下，最大的极差，能够取到的最大值，能够取到的最小值。

然后转移的时候四种状态，选 $a$ 还是选 $b$，比前面一个选的大还是小（或等于），这个状态是用于维护最大峰数的。

而且这种做法实际上可以开成滚动数组，如果读入格式改成读入一个 $a$ 就读入一个 $b$ 的话，一边读入一边 DP，空间只需要 1KB。

下面是赛时代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace init{
    inline ll qr() {
        ll k=0,f=1;char ch=getchar();
        while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
        while(isdigit(ch)){k=(k<<1)+(k<<3)+(ch^48);ch=getchar();}
        return k*f;
    }
    const ll mod=998244353;
}
using namespace init;
const int N=5e5+2;

int n,a[N][2];
//满足最大峰最多时：最大值最大；最小值最小；极差最大
struct node{
    int mx,mn,delt,cnt;
}f[N][2][2];//选a/b,比前面大/小（或等）
node Max(node x,node y) {
    if(x.mx==-1) return y;
    if(y.mx==-1) return x;
    if(x.cnt!=y.cnt) {
        if(x.cnt>y.cnt) return x;
        else return y;
    }
    x.mx=max(x.mx,y.mx);
    x.mn=min(x.mn,y.mn);
    x.delt=max(x.delt,y.delt);
    return x;
}

void solve() {
    n=qr();
    for(int i=1;i<=n;i++) a[i][0]=qr();
    for(int i=1;i<=n;i++) a[i][1]=qr();
    for(int i=1;i<=n;i++)
        for(int p=0;p<2;p++)
            for(int q=0;q<2;q++)
                f[i][p][q]={-1,1000000001,0,0};//预处理
    for(int p=0;p<2;p++)
        f[1][p][0]={a[1][p],a[1][p],0,0};
    for(int i=2;i<=n;i++) {
        for(int p=0;p<2;p++)
            for(int q=0;q<2;q++) {
                for(int p1=0;p1<2;p1++) {
                    if((bool)(a[i][p]>a[i-1][p1])==(bool)q) continue;
                    for(int q1=0;q1<2;q1++) {
                        if(f[i-1][p1][q1].mx==-1) continue;
                        node z=f[i-1][p1][q1];
                        if(q1==0&&a[i][p]<a[i-1][p1]) z.cnt++;
                        z.delt=max(max(a[i][p]-z.mn,z.mx-a[i][p]),z.delt);
                        z.mx=max(z.mx,a[i][p]);
                        z.mn=min(z.mn,a[i][p]);
                        f[i][p][q]=Max(f[i][p][q],z);
                    }
                }
            }
    }
    f[n][0][0].cnt++;
    f[n][1][0].cnt++;
    node ans=Max(Max(f[n][0][0],f[n][0][1]),Max(f[n][1][0],f[n][1][1]));
    printf("%d\n%d\n",ans.cnt,ans.delt);
}

signed main() {
    int TTT=1;
	while(TTT--) solve();
	return 0;
}
```

---


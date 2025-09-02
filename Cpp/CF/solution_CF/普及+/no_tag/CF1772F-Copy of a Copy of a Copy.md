# Copy of a Copy of a Copy

## 题目描述

给定一张 $n$ 行 $m$ 列的黑白图片（下标从 $1$ 开始），每一个单元格都被涂上了黑色或白色（$1$ 或者 $0$）。

我们对这张图片进行了若干次（可能为零次）操作，每一次操作都是下列两种之一：

- 选择一个单元格，这个单元格不能在图片的边缘（即，单元格所在行不能是 $1$ 或 $n$ 行，所在列不能是 $1$ 或 $m$ 列），并且这个单元格被四个不同颜色的单元格包围（中间 $0$ 四周 $1$，反之亦然），将这个单元格涂成相反的颜色；
- 复制一份当前图片。

两种操作不一定会交替进行。

给出你初始图片与 $k$ 份复制图片，一共 $k+1$ 份图片，这 $k+1$ 份图片是被随机打乱的。

你的任务是恢复操作的顺序。若有多种可能答案，只输出其中一个即可。

所有数据保证答案一定存在。


- $1\ x\ y$ 表示在坐标 $(x,y)$ 执行第一种操作；
- $2\ i$ 表示复制一份当前图片，编号是 $i$。

## 样例 #1

### 输入

```
3 3 1

010
111
010

010
101
010```

### 输出

```
2
2
1 2 2
2 1```

## 样例 #2

### 输入

```
4 5 3

00000
01000
11100
01000

00000
01000
10100
01000

00000
01010
10100
01000

00000
01000
10100
01000```

### 输出

```
3
5
1 2 4
2 2
2 4
1 3 2
2 1```

## 样例 #3

### 输入

```
5 3 0

110
010
001
011
001```

### 输出

```
1
0```

# 题解

## 作者：吴思诚 (赞：8)

# CF1772F Copy of a Copy of a Copy 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1772F)
## 思路
考虑每个格子的反转情况，如果一个格子反转了，那么四周的格子必然不会反转。因为本来这个格子和四周的格子颜色不同，反转后就相同了，而这样四周的每个格子就因为至少有这个格子一个格子颜色与它相同而不能够反转了。所以可以考虑按照每张图能够反转的次数进行排序，然后比较相邻两图不同之处即是答案。还有一点需注意，复制操作会进行 $O(k)$ 次，而修改会进行至多 $O(nm)$ 次，所以总操作次数最多是 $O(k+nm)$，如果用数组存储答案，注意数组的大小。时间复杂度 $O(nmk)$。
```cpp
#include<cstdio>
#include<algorithm>
const int N=110,M=40;
int n,m,k,cnt,ans1[N+M*M],ans2[N+M*M];
char s[N][M][M];
struct node{
	int id,cnt;
	bool operator <(const node &a)const{
		return cnt>a.cnt;
	}
}g[N];
void get(char s[][M],int i,int j,int k){
	char now=s[j][k];
	if(now!=s[j-1][k]&&now!=s[j][k-1]&&now!=s[j+1][k]&&now!=s[j][k+1])++g[i].cnt;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k+1;++i){
		g[i].id=i;
		for(int j=1;j<=n;++j)scanf("%s",s[i][j]+1);
		for(int j=2;j<n;++j)
			for(int k=2;k<m;++k)get(s[i],i,j,k);
	}
	std::sort(g+1,g+1+k+1);
	for(int i=2;i<=k+1;++i){
		int lst=g[i-1].id,now=g[i].id;
		for(int j=2;j<n;++j)
			for(int k=2;k<m;++k)
				if(s[lst][j][k]!=s[now][j][k]){
					ans1[++cnt]=j;
					ans2[cnt]=k;
				}
		ans1[++cnt]=g[i].id;
	}
	printf("%d\n%d\n",g[1].id,cnt);
	for(int i=1;i<=cnt;++i){
		if(ans2[i])printf("1 %d %d\n",ans1[i],ans2[i]);
		else printf("2 %d\n",ans1[i]);
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：3)

# CF1772F 题解



## 思路分析

注意到如下的观察：

> 对于每个可修改位置 $(i,j)$，如果 $(i,j)$ 被修改后，与 $(i,j)$ 相邻的四个格子将不能被修改。
>
> 因此每个 $(i,j)$ 最多被修改一次。

所以对于每个图片 $p_i$，维护对应的可修改位置集合 $\mathbf S_i$，按 $|\mathbf S_i|$ 从大到小排序即可得到每个图片生成的顺序。

由于上面的观察我们能够推知每个位置的修改是没有后效性的，也就是修改位置的顺序没有影响，因此每次修改的位置就是相邻两张图片中不同的那些位置，直接枚举即可。

时间复杂度 $\Theta(nmk)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int MAXN=31,MAXS=1001,MAXK=101;
int n,m,k,id[MAXN][MAXN];
struct node {
	int id,cnt;
	bool a[MAXN][MAXN];
	inline bool valid(int i,int j) {
		return a[i][j]!=a[i-1][j]&&a[i][j]!=a[i+1][j]&&a[i][j]!=a[i][j-1]&&a[i][j]!=a[i][j+1];
	}
	inline friend bool operator <(const node &A,const node &B) {
		return A.cnt>B.cnt;
	}
}	pic[MAXK];
signed main() {
	scanf("%d%d%d",&n,&m,&k);
	int cnt=0;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			id[i][j]=++cnt;
		}
	}
	for(int t=0;t<=k;++t) {
		pic[t].id=t+1;
		for(int i=1;i<=n;++i) {
			for(int j=1;j<=m;++j) {
				scanf("%1d",&pic[t].a[i][j]);
			}
		}
		for(int i=2;i<n;++i) {
			for(int j=2;j<m;++j) {
				if(pic[t].valid(i,j)) ++pic[t].cnt;
			}
		}
	}
	sort(pic,pic+k+1);
	vector <pii> ans;
	for(int t=1;t<=k;++t) {
		for(int i=2;i<n;++i) {
			for(int j=2;j<m;++j) {
				if(pic[t].a[i][j]!=pic[t-1].a[i][j]) {
					ans.push_back(make_pair(i,j));
				}
			}
		}
		ans.push_back(make_pair(pic[t].id,0));
	}
	printf("%d\n%d\n",pic[0].id,(int)ans.size());
	for(auto oper:ans) {
		if(oper.second!=0) printf("1 %d %d\n",oper.first,oper.second);
		else printf("2 %d\n",oper.first);
	}
	return 0;
}

```



---

## 作者：yingkeqian9217 (赞：1)

## 前言

简单思维题。。。

## 分析

注意到，一次操作是不可逆的，那么我们不妨找到一种图片的权值，使得这种权值在一次操作之后必然会减少（或增加）。

然后我们针对权值排序就能找到初始照片，以及操作的顺序。对于操作的内容，我们直接枚举相邻两个，看它们有哪些不同，输出即可。

那么这个权值是什么呢？通常的，我们可以尝试计算图片可以操作的次数。也就是有几个地方是可以被操作的。这些地方不一定在过程中都会操作，但是总次数一定是递减的。

这也不难理解，假设一对图片 $x,y$ 有 $k$ 处不同，那么因为有 $k$ 处原本是可操作的，操作后成为了不可操作的，所以总次数会 $-k$。而其他地方不变，所以可操作次数就是会 $-k$ 的。

自认为代码写的还算简练，凑合着看吧。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
const int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};//上下左右
int n,m,k,a[201][101][101];
vector<pair<int,int> >ans;//答案操作
pair<int,int>s[201];//可操作数
int judge(int id,int x,int y){//判断是否可操作
	int fl=1;
	for(int op=0;op<4;op++)
	 fl&=a[id][x+dx[op]][y+dy[op]]!=a[id][x][y];
	return fl;
}
signed main(){
	scanf("%d%d%d",&n,&m,&k),k++;
	for(int i=1;i<=k;i++){
		s[i].second=i;//表示对应的矩阵编号
		for(int j=1;j<=n;j++)
		 for(int l=1;l<=m;l++)
		  scanf("%1d",&a[i][j][l]);
		for(int j=2;j<n;j++)
		 for(int l=2;l<m;l++)
		  if(judge(i,j,l))
		   s[i].first--;//为了排序方便，我们使用减法，相当于从大到小排序
	}
	sort(s+1,s+k+1);
	for(int i=1;i<k;i++){
		for(int j=2;j<n;j++)
		 for(int l=2;l<m;l++)
		  if(a[s[i].second][j][l]!=a[s[i+1].second][j][l]&&judge(s[i].second,j,l)&&s[i].first<s[i+1].first)
		   s[i].first++,ans.push_back({j,l});
		ans.push_back({s[i+1].second,-1});//两种操作
	}
	printf("%d\n%d\n",s[2].second,ans.size());
	for(auto i:ans)
	 if(i.second==-1) printf("2 %d\n",i.first);
	 else printf("1 %d %d\n",i.first,i.second);
	return 0;
}
```

---

## 作者：Fractured_Angel (赞：0)

看一下你每次改变完其实你在干嘛。如果我们称 $f(k)$ 为 $k$ 图中需要消除的贡献的个数。那么 $f(k)$ 应该是单调不增的。因为你改变之后你自己不可能再改变，你的邻居也不可能再改变。所以你的贡献其实是近似独立的。

那么我们由这个性质，可以求出每张图 $k$ 的 $f(k)$，然后按 $f(k)$ 从大到小排序。然后数操作即可，做完了。其实没那么难。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXK = 105;
const int MAXN = 35;
int n, m, K, A[MAXN][MAXN][MAXK];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
bool in(int x, int y) { return x > 0 && x <= n && y > 0 && y <= m; }
struct Node
{
	int cnt, id;
} B[MAXK];
bool Cmp(Node x, Node y) { return x.cnt > y.cnt; }
int cntOpt = 0;
int Opt[100005], XX[100005], YY[100005], ID[100005];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m >> K; K ++;
	for(int k = 1; k <= K; k ++)
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
			{
				char ch; cin >> ch;
				A[i][j][k] = ch - '0';
			}
				
	for(int k = 1; k <= K; k ++)
	{
		for(int i = 1; i <= n; i ++)
		{
			for(int j = 1; j <= m; j ++)
			{
				int num = 0;
				for(int t = 0; t < 4; t ++)
				{
					int ni = i + dx[t], nj = j + dy[t]; if(!in(ni, nj)) continue;
					num += (A[i][j][k] != A[ni][nj][k]);
				}
				if(num == 4) B[k].cnt ++;
			}
		}
		B[k].id = k;
	}
	sort(B + 1, B + K + 1, Cmp);
	cout << B[1].id << '\n';
	for(int k = 2; k <= K; k ++)
	{
		for(int i = 1; i <= n; i ++)
		{
			for(int j = 1; j <= m; j ++)
			{
				if(A[i][j][B[k].id] != A[i][j][B[k - 1].id]) 
				{
					Opt[++ cntOpt] = 1; 
					XX[cntOpt] = i; YY[cntOpt] = j;
				}
			}
		}
		Opt[++ cntOpt] = 2; ID[cntOpt] = B[k].id;
	}
	cout << cntOpt << '\n';
	for(int i = 1; i <= cntOpt; i ++) 
	{
		if(Opt[i] == 1) cout << 1 << " " << XX[i] << " " << YY[i] << '\n';
		else cout << 2 << " " << ID[i] << '\n';
	}
	return 0;
}
```

---

## 作者：_JF_ (赞：0)

[CF1772F Copy of a Copy of a Copy](https://www.luogu.com.cn/problem/CF1772F)

有些人还是可以回炉重造了。~~提供最复杂无脑的做法。~~

重要的观察，发现如果我从 $a$ 图操作变换到 $b$ 图，那么 $b$ 不可能变回 $a$。操作是不可逆的。

原因显然，如果我把当前的 $0$ 变成了 $1$，那么说明原来 $0$ 周围的四个格子都不能改变，还是四个 $1$，那也就变不回去 $0$。

我们先把相同的图进行合并（也就是记录一下，让他只出现一次，具体在输出的时候我们直接采用操作 $2$ 即可），如果两个图 $a$ 可以变成 $b$ ，则连一条 $a$ 到 $b$ 的有向边。

因为操作是不可逆的，其实这个图没有环，那么问题转换成在有向无环图上找一条路径（一定存在）满足遍历到所有的点，那其实做拓扑排序即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =101*2;
#define int long long
struct node{
	int x,y;
};
struct edge{
	int op,x,y;
};
vector<edge> Ans;
vector<node> G[N][N];
bool vis[N],Vis[N],F[N][N];
char S[N][50][50],S1[N][N],S2[N][N];
int in[N],n,m,k,ans,Fir;
vector<int> vec[N],g[N],V;
bool check(int i,int j){
	if(i==1||j==1||i==n||j==m)	return false;
	if((((int)(S1[i-1][j]-'0'))==(!((int)(S1[i][j]-'0'))))||(((int)(S1[i+1][j]-'0'))==(!((int)(S1[i][j]-'0'))))||(((int)(S1[i][j-1]-'0'))==(!((int)(S1[i][j]-'0'))))||(((int)(S1[i][j+1]-'0'))==(!((int)(S1[i][j]-'0')))))	return true;
	return false;
}
bool check1(int x,int y){
	for(int i=1;i<=n;i++)	for(int j=1;j<=m;j++)	if(S[x][i][j]!=S[y][i][j])	return false;
	return true;
}
void init(int x,int y){
	bool f=true;
	if(check1(x,y))	vec[x].push_back(y);
	if(Vis[x]==true||Vis[y]==true)	return ;
	for(int i=1;i<=n;i++)	for(int j=1;j<=m;j++)	S1[i][j]=S[x][i][j],S2[i][j]=S[y][i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(S1[i][j]!=S2[i][j]){
				if(check(i,j)==true)	S1[i][j]=S2[i][j],G[x][y].push_back({i,j});
				else	f=false;
			}
		}
	if(f==false){G[x][y].clear();return ;}
	g[x].push_back(y),in[y]++,F[x][y]=true;
	return ;
}
void Slove(){
	queue<int> q;
	for(int i=1;i<=k+1;i++)	if((in[i]==0)&&(Vis[i]==false))	Fir=i,q.push(Fir);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<vec[u].size();i++)	ans++,Ans.push_back({2,vec[u][i],0});
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i]; in[v]--;
			if(in[v]==0){
				for(int j=0;j<G[u][v].size();j++)	ans++,Ans.push_back({1,G[u][v][j].x,G[u][v][j].y});
				ans++,Ans.push_back({2,v,0}),q.push(v);
			}
		}
	}
	return ;
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=k+1;i++){
		string p; getline(cin,p);
		for(int j=1;j<=n;j++)	for(int K=1;K<=m;K++)	cin>>S[i][j][K];
	} 
	for(int i=1;i<=k+1;i++){
		bool F1=true;
		for(int j=0;j<V.size();j++)	if(check1(V[j],i)==true)	F1=false;
		if(F1==true)	V.push_back(i);
		else	Vis[i]=true;		
	}
	for(int i=1;i<=k+1;i++)	for(int j=1;j<=k+1;j++)	if(i!=j)	init(i,j);
	Slove();
	cout<<Fir<<endl<<ans<<endl;
	for(int i=0;i<Ans.size();i++){
		if(Ans[i].op==1)	cout<<1<<" "<<Ans[i].x<<" "<<Ans[i].y<<endl;
		else	cout<<2<<" "<<Ans[i].x<<endl;
	}
	return 0;
}
/*
3 3 1

010
111
010

010
101
010

*/ 
```

---

## 作者：Larry76 (赞：0)

## 前言

震惊于本题居然能在 CF 上评 $2000$。

## 题目分析

本题的破题点在于你能意识到操作是不可逆的就好，也就是说，当我们执行一次操作 $1$ 后，它必然不会产生新的可操作空间，并且操作 $1$ 的操作不可撤销。证明是容易的，考虑执行操作后不可能产生新的题目中要求的结构即可证明。

当你意识到这一点的时候，不难想到操作顺序会构成一个 DAG，然后操作的影响是增量的。

故不妨我们暴力一点，$O(k^2)$ 遍历所有的图片，然后比较谁在谁的基础上进行了若干次操作 $1$，然后连边。这里的时间复杂度是 $O(nmk^2)$。

然后我们再进行拓扑排序，当某个点的入度为 $0$ 的时候，将差异压入操作序列，如果同一层的完成了压入操作序列的操作，则忽略本次（不是忽略入队哈）。然后出队的时候如果他不是初始图片，则说明他是复制过来，此时压入一个操作 $2$。然后本题就做完了，这里的时间复杂度 $O(nmk)$。

综上，总时间复杂度 $O(nmk^2)$，实际上用位运算可以再快亿点点，但是懒得写了，这个时间复杂度足以通过该题。

## 代码实现

这里只给出了关键部分的代码实现，其余部分还恳请读者自行实现。

```cpp
bool graph[MAX_PIC][MAX_BORDER][MAX_BORDER];
int head[MAX_SIZE];
int Next[MAX_SIZE];
int ver[MAX_SIZE];
int ind[MAX_SIZE];
int tot = 0;
void add_edge(int u, int v){
    ver[++tot] = v;
    ++ind[v];
    Next[tot] = head[u];
    head[u] = tot;
}

int n,m,k;
int check(int p, int q, int i, int j){
    if(i <= 1 || j <= 1 || i >= n || j >= m){
        debugf("WTF????");
        assert(0);
        return -114514;
    }
    if(graph[q][i-1][j] == graph[q][i][j])
        return 1;
    return -1;
}

int cmp(int p, int q){
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++){
            if(graph[p][i][j] != graph[q][i][j]){
                return check(p, q, i, j);
            }
        }
    }
    return 0;
}

struct opt{
    int op;
    int x,y;
};
vector<opt> ops;

void push_diff(int p, int q){
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(graph[p][i][j] != graph[q][i][j]) {
                ops.push_back((opt){1,i,j});
            }
        }
    }
}

void topo(){
    queue<int> q;
    bool flag = 0;
    int root = 0;
    for(int i = 1; i <= k + 1; i++){
        if(!ind[i] && !flag){
            q.push(i);
            root = i;
            flag = true;
        } else if(!ind[i] && flag){
            q.push(i);
        }
    }
    while(q.size()){
        auto u = q.front();
        q.pop();
        if(u != root) {
            ops.push_back((opt){2,u,0});
        }
        bool changed = false;
        for(int i = head[u]; i; i = Next[i]){
            int v = ver[i];
            --ind[v];
            if(!ind[v]){
                if(!changed){
                    push_diff(u, v);
                    changed = true;
                }
                q.push(v);
            }
        }
    }

}

void main(){
    read(n,m,k);
    string s;
    for(int t = 1; t <= k + 1; t++) {
        for(int i = 1; i <= n; i++) {
            cin>>s;
            for(int j = 1; j <= m; j++) {
                graph[t][i][j] = s[j-1] - '0';
            }
        }
    }
    for(int i = 1; i <= k + 1; i++) {
        for(int j = i + 1; j <= k + 1; j++) {
            switch(cmp(i, j)) {
                case 1:
                    add_edge(i, j);
                    break;
                case -1:
                    add_edge(j, i);
                    break;
            }
        }
    }
    for(int i = 1; i <= k + 1; i++){
        if(!ind[i]){
            write(i, '\n');
            break;
        }
    }
    topo();
    write(ops.size(), '\n');
    for(auto op : ops){
        if(op.op == 1){
            printf("%lld %lld %lld\n", op.op, op.x, op.y);
        } else {
            printf("%lld %lld\n", op.op, op.x);
        }
    }
}
```

---

## 作者：Special_Tony (赞：0)

[洛谷传送门](/problem/CF1772F) & [CF 传送门](//codeforces.com/problemset/problem/1772/F)
# 思路
这题有一个很重要的突破口——操作不可逆，所以可操作的次数是不上升的。所以我们可以对每张图片都统计一次可以操作的数量，然后从大到小排序就得到了打乱前的顺序。至于改变的顺序，那就只要看一下相邻两张图片有哪几个格子不一样即可。
# 代码
```cpp
// LUOGU_RID: 119511355
# include <bits/stdc++.h>
using namespace std;
typedef pair <int, int> pii; //简写，注意不能放到 using namespace std; 前面，因为 pair 是要用到 std 的
struct node {
	string a[35];
	int tot, id;
	bool operator < (const node& x) const { //重载运算符
		return tot > x.tot;
	}
} a[105];
int n, m, k;
vector <pii> ans;
bool check (string a[], int i, int j) { //判断是否合法
	return a[i][j] != a[i + 1][j] && a[i][j] != a[i - 1][j] && a[i][j] != a[i][j + 1] && a[i][j] != a[i][j - 1];
}
int main () {
	cin >> n >> m >> k;
	++ k; //k+1 张图片
	for (int i = 1; i <= k; ++ i) {
		a[i].id = i;
		for (reg int j = 1; j <= n; ++ j) {
			cin >> a[i].a[j];
			a[i].a[j] = ' ' + a[i].a[j];
		}
		for (reg int j = 2; j < n; ++ j) //注意这部分不能和输入合并到一起！！！否则 a[j+1] 还没输入，你会 WA on #16
			for (reg int k = 2; k < m; ++ k)
				a[i].tot += check (a[i].a, j, k); //统计有几个可以被修改
	}
	sort (a + 1, a + k + 1); //排序
	for (int i = 1; i < k; ans.push_back ({a[++ i].id, 0}))
		for (int j = 2; j < n; ++ j)
			for (int k = 2; k < m; ++ k)
				if (a[i].a[j][k] != a[i + 1].a[j][k] && check (a[i].a, j, k))
					ans.push_back ({j, k});
	cout << a[1].id << '\n' << ans.size () << '\n';
	for (pii i : ans)
		if (i.second)
			cout << "1 " << i.first << ' ' << i.second << '\n';
		else
			cout << "2 " << i.first << '\n';
	return 0;
}
```

---


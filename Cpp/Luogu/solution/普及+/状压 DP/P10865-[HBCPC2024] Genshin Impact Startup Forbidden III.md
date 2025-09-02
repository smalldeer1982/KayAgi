# [HBCPC2024] Genshin Impact Startup Forbidden III

## 题目描述

“Blue-edged Shot 被 LeavingZ 禁止玩《原神》。然而，今天 LeavingZ 前往了华中科技大学的网络科学与工程学院，参加2024年中国湖北省国际大学生程序设计竞赛，并收获了金牌。

《原神》中的一个活动多多炸弹大冒险已经开始了。这是一个单人游戏，每局游戏都涉及一个池塘。池塘可以被划分为一个 $n×m$ 的网格，其中第 $i$ 行第 $j$ 列的单元格表示为 $(i,j)$。在这些单元格中，有 $k$ 个单元格包含鱼，你将扮演火花骑士克莱，她用炸药来捕鱼。

如果克莱在 $(a,b)$ 位置投放炸弹，那么所有满足$|x-a|+|y-b|\le 1$的单元格 $(x,y)$ 都将被爆炸覆盖。对于每一个被爆炸覆盖的单元格，克莱都会从其中捕到一条鱼。克莱可以在任何位置投放炸弹。问题是，为了捕到所有的鱼，至少需要多少枚“蹦蹦炸弹”？

## 说明/提示

一种可能的方法是在 $(1,2)$ 位置投放两枚炸弹，再在 $(5,5)$ 位置投放另外两枚炸弹。

可以证明没有比这个答案更小的解。

## 样例 #1

### 输入

```
5 5 3
1 1 2
2 2 1
5 5 2```

### 输出

```
4```

# 题解

## 作者：mlvx (赞：9)

### 题意

一个 $n\times m$ 的矩阵里，有 $k$ 个位置有鱼。

可以放置若干个炸弹，每个炸弹可以炸到上下左右和本格五个格子，一个格子被炸后，鱼的数量会减一。

问最小需要多少个炸弹才能把全部鱼都炸掉。

### 分析

$k\le10$，显然只有最多 $5k$ 个位置放炸弹可以炸到鱼。

$a_i\le3$，显然可以对每个有鱼的格子内鱼的数量进行一个状压，一个四进制数 $s$，第 $x$ 位表示第 $x$ 个有鱼的格子的鱼的数量，$dp_s$ 表示从初始状态到状态 $s$ 所需要的炸弹的最少数量。

转移方程为 $dp_t=\min\{dp_s\}+1$，其中 $t$ 表示在 $s$ 状态上放一个炸弹，可以达到的状态。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int dx[5]={0,0,0,1,-1},dy[5]={1,-1,0,0,0};
int n,m,k,s,x[11],y[11],c[11],vis[11],dp[1<<20],fish[1010][1010];
vector<pair<int,int>>v;
int main(){
	memset(dp,0x3f,sizeof dp),cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		cin>>x[i]>>y[i]>>c[i],(s<<=2)|=c[i],fish[x[i]][y[i]]=i;
		for(int t=0;t<5;t++)
			if(x[i]+dx[t]>0&&y[i]+dy[t]>0&&x[i]+dx[t]<=n&&y[i]+dy[t]<=m)
				v.push_back({x[i]+dx[t],y[i]+dy[t]});
	}dp[s]=0,sort(v.begin(),v.end()),unique(v.begin(),v.end());
	for(int i=s;i;i--){
		memset(vis,0,sizeof vis);
		for(int j=k,tmp=i;j;j--){
			if(tmp&3)vis[j]=1;
			if((tmp&3)>c[j])goto A;
			tmp>>=2;
		}for(auto[x,y]:v){
			int ii=i;
			for(int t=0;t<5;t++){
				int tmp=fish[x+dx[t]][y+dy[t]];
				if(vis[tmp])ii-=(1<<(k-tmp<<1));
			}dp[ii]=min(dp[ii],dp[i]+1);
		}A:;
	}return cout<<dp[0],0;
}
```

---

## 作者：Link_Cut_Y (赞：5)

我们充分发扬人类智慧。

其实一点也不智慧。我们发现有用的格子不会很多，他们是和有鱼的格子四联通的。这样最多有 $4k$ 个。

每个格子最多会扔三个雷。我们把有效格子都复制三倍扔到数组里。这个数组长度不会超过 $4 \times 3 \times k = 120$。

$n \le 120$ 的最优化问题天生为退火而生。

```cpp
int p[N], cnt, g[1010][1010], ans = 10101010;
pair<int, int> pos[N]; int n, x[N], y[N], a[N], m, k, o;
int bin[1010][1010];
const int dx[] = {0, 1, 0, -1, 0};
const int dy[] = {0, 0, 1, 0, -1};
int calc() {
	int az = k, res;
	rep(i, 1, o) rep(j, 0, 4) {
		int tx = pos[p[i]].x + dx[j], ty = pos[p[i]].y + dy[j];
		if (tx <= 0 or tx > n or ty <= 0 or ty > m) continue;
		if (g[tx][ty] == 1) az -- ;
		if (g[tx][ty]) g[tx][ty] -- ;
		if (!az) { ans = min(ans, i); res = i; goto EXIT; }
	} EXIT:;
	rep(i, 1, k) g[x[i]][y[i]] = a[i];
	return res;
}
void SA() {
	random_shuffle(p + 1, p + o + 1);
	for (double t = 1e5; t >= 1e-5; t = t * 0.99) {
		int qwq = calc(); int u = rand() % o + 1, v = rand() % o + 1;
		swap(p[u], p[v]); int qaq = calc();
		if (qaq < qwq) continue; if ((double)exp((qwq - qaq) / t) > (double)rand() / RAND_MAX) continue;
		swap(p[u], p[v]);
	}
}
signed main() {
	read(n, m, k);
	rep(i, 1, k) read(x[i], y[i], a[i]), g[x[i]][y[i]] = a[i];
	rep(i, 1, k) rep(j, 0, 4) {
		int tx = x[i] + dx[j], ty = y[i] + dy[j];
		if (tx <= 0 or tx > n or ty <= 0 or ty > m) continue;
		if (bin[tx][ty]) continue;
		bin[tx][ty] = ++ cnt; pos[cnt] = {tx, ty};
	}
	rep(i, 1, cnt) p[ ++ o] = i, p[ ++ o] = i, p[ ++ o] = i;
	rep(i, 1, 100) SA(); printf("%lld\n", ans); return 0;
}
```

---

## 作者：starfi11 (赞：3)

鱼塘大小为 $n、m$，$10^3\times 10^3$ 以内，有 $k$ 个池塘有鱼，$k\le10$，这让问题规模缩小了很多，每个有鱼的池塘内的鱼个数不超过 $3$，蹦蹦炸弹是十字型的，每颗炸弹炸到的每个池塘只能炸出一条鱼，求炸干净鱼用的蹦蹦炸弹的最小个数。

- 最开始做的时候想到贪心，炸弹炸的位置肯定是鱼塘或者鱼塘相邻的位置，然后每次选择能炸最多鱼的位置炸，但这种贪心的思路能构造出数据证明其错误性。如下图所示，按每次选择炸最多鱼的炸需要 $4$ 颗，而存在方法只需要 $3$ 颗炸弹。

![](https://luweiphoto.oss-cn-wuhan-lr.aliyuncs.com/202408151621592.png)



- 问题规模较小，考虑离散化后 dp

​	有鱼的池塘数量为 $k$ ，且 $k\le10$ ；一个池塘的鱼数量最多为 $3$，用两位二进制位可表示。前面的贪心虽然是错的，但如果要找到最小炸数量，每个炸弹位置炸的必定是鱼塘格或与鱼塘格相邻的格（否则炸了一条鱼都没炸到），炸弹可能炸的位置则约有 $5k$ 个（实际小于 $5k$ )所以一个状态到另一个状态的递推就有了，遍历所有炸弹可能炸的位置递推即可。

​	用一个 int 数表示池塘的状态，每两个二进制位表示一个池塘的鱼数量为多少，只压缩有鱼的 $k$ 个池塘，利用离散化后的下标与  $4^i$ 可以快速完成状态压缩。再考虑更细节一点的问题，一个炸弹可能炸到多个有鱼的格子，要从 state1 计算得到 state2 ，需要知道 state1 中哪些格子有鱼且在本次递推中被炸了。预先处理好 $5k$ 个炸弹各自会炸到的有鱼格子的下标，利用位运算检查 state1 对应格子中是否有鱼即可。递推为: $dp[nextstate]=min(dp[i]+1,dp[nextstate])$。

时间复杂度估计：

​	有鱼的池塘数量 $k$，可能的炸弹位置 $5k$，对每个可能的炸鱼位置预处理出可以炸到哪些有鱼的池塘，$O(5k\times k)$ 即 $O(k^2)$。

​	所有状态的数量为 $2^{2k}=4^k$，对每个状态枚举可能的炸鱼位置约 $5k$ 个，对每个炸鱼位置有预先处理好的至多 $5$ 个的初始有鱼位置下标，对每个初始有鱼位置下标 $O(1)$ 判断其当前状态是否有鱼。

​	dp 时间复杂度为 $O(4^k\times5k\times5)$ 即 $O(k\times4^k)$。

​	总复杂度为 $O(k^2+k\times4^k)$，即 $O(k\times4^k)$。

代码如下：

```cpp
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int n,m,k;
struct Pond{
	//有鱼的鱼塘格 
	int x,y;
	int fish;
	Pond(int x,int y,int fish):x(x),y(y),fish(fish){
	}
};
struct Bomb{
	//在x,y丢的炸弹会炸到的有鱼的鱼塘格存在arr中 
	int x,y;
	vector<int>arr;
	Bomb(int x,int y):x(x),y(y){
	}
};

int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0};

vector<Pond>pond;//存所有有鱼的格子，对应下标存入后为定值 
vector<Bomb>bomb;//存所有可能炸的地方 

int dp[1<<21];//1<<20应该是刚好够 
int inf=0x3f3f3f3f;
int pow4[15];//到9就够用了 

void print(int x){
	//调试时用的 
	vector<int>stack;
	for(int i=0;i<k;i++){
		stack.push_back(x%2);
		x/=2;
		stack.push_back(x%2);
		x/=2;
	}
	for(int i=stack.size()-1;i>=0;i--)
		cout<<stack[i];
	cout<<endl;
}
bool canExplode(int a,int b){
	//询问bomb中下标a的炸弹能不能炸到pond中下标为b的格子
	if(bomb[a].x==pond[b].x&&bomb[a].y==pond[b].y)
		return 1;
	for(int i=0;i<4;i++){
		//pond中都是合法范围的鱼塘，即使bomb+dx越界也没有问题 
		if(bomb[a].x+dx[i]==pond[b].x&&bomb[a].y+dy[i]==pond[b].y)
			return 1;
	}
	return 0;
}
int main(){
	
	pow4[0]=1;
	for(int i=1;i<15;i++){
		pow4[i]=pow4[i-1]*4;
	}
	
	cin>>n>>m>>k;
	int x,y,f;
	int originstate=0;
	for(int i=0;i<k;i++){
		scanf("%d%d%d",&x,&y,&f);
		pond.push_back(Pond(x,y,f));
		bomb.push_back(Bomb(x,y));
		for(int j=0;j<4;j++){
			if(x+dx[j]>=1&&x+dx[j]<=n&&y+dy[j]>=1&&y+dy[j]<=m)
				bomb.push_back(Bomb(x+dx[j],y+dy[j]));
		}
		originstate+=f*pow4[i];
	}
	
	//print(originstate);
	
	//处理每个炸鱼的位置能炸到哪些初始有鱼的池塘
	for(int i=0;i<bomb.size();i++){
		for(int j=0;j<pond.size();j++){
			if(canExplode(i,j))
				bomb[i].arr.push_back(j); 
		}
	}
	
	//初始化 
	memset(dp,0x3f,sizeof(dp));
	dp[originstate]=0;
	
	//dp
	int nextstate;
	const int mask=3;//0011
	for(int i=originstate;i>=0;i--){
		if(dp[i]==inf)
			continue;
		for(int j=0;j<bomb.size();j++){
			//枚举炸鱼位置开炸 
			nextstate=i;
			//对被炸到的有鱼位置都减一 
			for(int z=0;z<bomb[j].arr.size();z++){
				if(i&(mask*pow4[bomb[j].arr[z]]))
					nextstate-=1*pow4[bomb[j].arr[z]];
			}
			dp[nextstate]=min(dp[i]+1,dp[nextstate]);
		}
	}
	
//	for(int i=0;i<=originstate;i++)
//		cout<<i<<"="<<dp[i]<<endl;
	cout<<dp[0];
} 
```

---

## 作者：xzy_AK_IOI (赞：2)

### 思路分析

首先可以发现，$k \le 10$，考虑状压 dp，将有鱼的格子压缩进一个 $10$ 位 $4$ 进制数 $s$ 中。

接下来就开始 dp 了。

设 $ dp_s$ 为集合 $s$ 中状态为 $m$ 的鱼已经清除了 $m$ 条所用到的最小炸弹数量。

则可以写出状态转移方程：


$$dp_s = \min(dp_{s-j}+1)\ (j \isin s\ \land\ check(j))$$

方程意为：清除集合 $s$ 中的鱼的炸弹数为清空集合 $s-j$ 中的鱼的炸弹数 + 将集合 $j$ 中的鱼一次性清除所用的炸弹数 $1$。

其中 $\land$ 运算符为逻辑与运算符，$check(j)$ 函数为检查集合 $j$ 中的鱼能否用一个炸弹全部清除，可以一开始初始化好。

注意这里的集合 $s$ 和集合 $j$ 都是二进制压缩而不是四进制压缩，因为一个炸弹最多只能清除一个格子的一条鱼。

在 $check(j)$ 函数中，我们依次枚举每一个格子及其上下左右的 $5$ 个点，判断将炸弹扔在那里是否可以清除集合 $j$ 中所有鱼。


### 完整代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define F(i,k,n) for (int i=k;i<=n;i++)
typedef long long ll;
const int N=24;
int n,m,k;
int x[N],y[N],a[N];
bool pre_check[1<<N];//预处理check数组
int pre[]={1,4,16,64,256,1024,4096,16384,65536
,262144,1048576,4194304,16777216};//预处理4进制的每一位
int dp[1<<N];
int to[N];
int dx[]={0,0,0,1,-1};
int dy[]={0,1,-1,0,0};//偏移数组
bool check(int a){
	int tot=0;
	F(i,0,k-1){
		if ((a>>i)&1){
			tot++;
			to[tot]=i;
		}
	}
	if (tot==1 || !tot) return 1;
	F(i,1,1){
		F(j,0,4){
			int l=x[to[i]]+dx[j],r=y[to[i]]+dy[j];
			bool flag=1;
			F(p,1,tot){
				if (abs(x[to[p]]-l)+abs(y[to[p]]-r)>1) flag=0;
			}
			if (flag) return 1;
		}
	}
	return 0;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m>>k;
	F(i,0,k-1) cin>>x[i]>>y[i]>>a[i];
	int op=0;
	F(i,0,k-1) op+=pre[i]*a[i];
	for (int j=(1<<k)-1;j;j=(j-1)&((1<<k)-1)){
		if (check(j)){
			pre_check[j]=1;//预处理check
		}
	}
	memset(dp,0x3f,sizeof dp);
	dp[0]=0;
	F(s,1,op){
		int change=0,d=s;
		for (int i=k-1;i>=0;i--){
			if (d>=pre[i]) change+=(1<<i);
			d%=pre[i];//4进制转2进制
		}
		for (int j=change;j;j=(j-1)&change){//枚举s的子集j
			if (pre_check[j]){
				int l=0;
				F(i,0,k-1) if ((j>>i)&1) l+=pre[i];//2进制转回4进制
				dp[s]=min(dp[s],dp[s-l]+1);
			}
		}
	}
	cout<<dp[op];
	return 0;
}
```

---

## 作者：Helenty (赞：2)

### 解题思路

时间复杂度其他题解已经分析了，这里给一个非常简单理解的 BFS 代码。

- 其实不状压而是直接开 $k$ 维数组也挺爽的，不容易状态转移出错。

- $k$ 只有 $10$，有关 $k$ 的部分可以枚举暴搜，充分利用这个条件，$a_i\le3$ 正好可以 $k$ 位四进制状压。

- $4^{10}=1048576$，点最多就是所有状态，时空复杂度才 $2^k$，可以过的。

### 解题代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;

int n, m, k, x, y, a, st;
int dx[5] = {0, 0, 0, 1, -1}, dy[5] = {1, -1, 0, 0, 0}, dp[1050000];
pair<int, int> p[10]; // coordinates pair 坐标对
map<pair<int, int>, int> fish; // 每个坐标对应的鱼鱼数量
set<pair<int, int>> c; // candidate 候选投炸弹的坐标，可能有重复的正好set去重
queue<int> q; // bfs 搜最短路（最少炸弹数）

// 更新状态
int update_state(int state, int index, int value)
{
    int mask = 3; // 四进制的两位掩码
    return (state & ~(mask << (index * 2))) | (value << (index * 2));
}

int main()
{
    cin >> n >> m >> k;
    memset(dp, inf, sizeof(dp));
    for (int i = 0; i < k; i++)
	{
        cin >> x >> y >> a;
        p[i] = {x, y};
        fish[p[i]] = a;
        st = update_state(st, i, a); // 初始化状态
        for (int d = 0; d < 5; d++) // fish 坐标相关的位置投炸弹才有意义，存下来
		{ 
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) c.insert({nx, ny});
        }
    }
    dp[st] = 0;
    q.push(st);
    while (!q.empty())
	{
        int cur = q.front();
        q.pop();
        if (!cur) break; // 所有鱼都被捕到
        for (auto it = c.begin(); it != c.end(); it++) // 在 c 坐标投放一颗炸弹
		{ 
            int nx = it->first, ny = it->second, temp = cur;
            for (int i = 0; i < k; i++) // 遍历所有鱼点
			{ 
                for (int d = 0; d < 5; d++) // 检查炸弹覆盖范围
				{ 
                    if (nx == p[i].first + dx[d] && ny == p[i].second + dy[d])
					{
                        int fish_count = (temp >> (i * 2)) & 3; // 获取当前鱼点的鱼数量
                        if (fish_count > 0) temp = update_state(temp, i, fish_count - 1); // 如果还有鱼，就减少一条鱼
                    }
                }
            }
            if (dp[temp] == inf) // 如果新状态未被访问过
			{ 
                dp[temp] = dp[cur] + 1; // 更新状态
                q.push(temp);
            }
        }
    }
    cout << dp[0] << endl; // 输出最少炸弹数量
    return 0;
}
```

---

## 作者：Rindong (赞：1)

提供一篇搜索题解。

# 思路

观察题目发现 $1 \le k \le 10$ 并且 $a_i \le 3$，那么所有的有鱼的格点状态就只有 $4^k$ 种，可以接受，所以我们可以定义一个 10 维数组来做状态减枝（我也是第一次定义那么多维的数组-_-||）。

然后就是怎么搜索了。我们枚举每个未被取完的有鱼的格子，要取到某个格子的鱼，我们可以有五个位置：上下左右中。枚举到一个格点 $p_i$ 后，我们也把 $p_i$ 的上下左右中减去我们要取的数量即可。

# 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define PII pair<int, int>
#define x first
#define y second
#define cur (dp[arr[0]][arr[1]][arr[2]][arr[3]]\
[arr[4]][arr[5]][arr[6]][arr[7]][arr[8]][arr[9]])
int arr[15] = { 0 };
int dp[4][4][4][4][4][4][4][4][4][4] = { 0 };
int n, m, k;
PII pos[15];
int dir[5][2] = {
	{ 0, 0 }, { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }
};
void dfs(int step) {
	if (step >= cur) return;
	cur = step;
	vector<int> brr(k);
	for (int c = 0; c < k; c++)
		if (arr[c]) {
			int cnt = arr[c];
			for (int d = 0; d < 5; d++) {
				int x = pos[c].x + dir[d][0],
					y = pos[c].y + dir[d][1];
				for (int i = 0; i < 5; i++) {
					int dx = x + dir[i][0],
						dy = y + dir[i][1];
					for (int j = 0; j < k; j++)
						if (dx == pos[j].x && dy == pos[j].y) {
							brr[j] = arr[j];
							arr[j] = max(0, arr[j] - cnt);
						}
				}
				dfs(step + cnt);
				for (int i = 0; i < 5; i++) {
					int dx = x + dir[i][0],
						dy = y + dir[i][1];
					for (int j = 0; j < k; j++)
						if (dx == pos[j].x && dy == pos[j].y) arr[j] = brr[j];
				}
			}
		}
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < k; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		pos[i] = { x, y };
		arr[i] = z;
	}
	memset(dp, 0x3f, sizeof dp);
	dfs(0);
	printf("%d", dp[0][0][0][0][0][0][0][0][0][0]);
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：1)

一个位置最多只有 $3$ 条鱼，而所有有鱼的格子不超过 $10$，所以我们可以写一个 $4$ 进制的状态压缩。设 $dp_s$ 表示 $k$ 个有鱼的格子中受到炸弹影响后的状态为 $s$ 时所需要的最小的炸弹的数量。

同时，由于一个炸弹只能影响到五个格子，所以我们可以预处理出不超过 $50$ 个可能会放炸弹的位置。当状态为 $s$ 时，在某处放入一个炸弹，我们可以将 $s$ 每一位分离后，修改炸弹影响到的那些位置，然后再重新获得 $s'$。因此可以列出转移方程 $dp_{s'} = \min (dp_{s'},dp_s + 1)$。

最后的时间复杂度约为 $O(4^k \times k^2)$，可以通过此题。代码如下：

```cpp
#include <bits/stdc++.h>
#define init(x) memset (x,INF,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 2e6 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,m,k,p,tot,v[15],dp[MAX],sx[] = {0,1,-1,0,0},sy[] = {0,0,0,1,-1};
vector <int> tmp;
set <pair <int,int> > loc;
map <pair <int,int>,int> id;
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();m = read ();k = read ();
	for (int i = 0;i < k;++i)
	{
		int x = read (),y = read ();v[i] = read ();
		id[{x,y}] = i;//用 map 记录下对应的位置
		for (int j = 0;j < 5;++j)
		{
			int xx = x + sx[j],yy = y + sy[j];
			if (1 <= xx && xx <= n && 1 <= yy && yy <= m) loc.insert ({xx,yy});//预处理出炸弹可能放置的位置，用 set 去重
		}
		tot = tot * 4 + v[i];//处理出对应的四进制数
	}
	init (dp);dp[0] = 0;
	for (int i = 0;i <= (1 << (2 * k));++i)
	{
		if (dp[i] == INF) continue;
		for (auto nxt : loc)
		{
			int x = nxt.first,y = nxt.second;
			p = i;tmp.clear ();
			for (int j = 1;j <= k;++j) tmp.push_back (p % 4),p /= 4;//逐位分离
			for (int j = 0;j < 5;++j)
			{
				int xx = x + sx[j],yy = y + sy[j];
				if (id.find ({xx,yy}) == id.end ()) continue;//不需要放置炸弹
				int o = id[{xx,yy}];
				tmp[k - o - 1] = min (v[o],tmp[k - o - 1] + 1);//炸弹最多不超过格子中鱼的数量  注意下标
			}
			p = 0;
			for (int i = tmp.size () - 1;~i;--i) p = p * 4 + tmp[i];//重新计算出新的状态
			dp[p] = min (dp[p],dp[i] + 1); 
		}
	}
	printf ("%d\n",dp[tot]);
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：__rnfmabj__ (赞：1)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P10865)

可莉想要去炸鱼，给定一个 $n\times m$ 的矩阵，其中有 $k$ 个地方有鱼，鱼的数量 $x \in {0,1,2,3}$ 。

当可莉在一个位置 $i,j$ 释放蹦蹦炸弹时，会对周围满足 $|x-i|+|y-j|\le 1$ 的 $x,y$ 位置中的鱼的数量减一，求将所有鱼都炸掉的最小蹦蹦炸弹的数量。

## 题目分析

首先很显然的是蹦蹦炸弹其实只会对他自己以及上下左右四个方向的鱼的数量造成影响。

然后~~考虑贪心，然而并不是正解~~，看到鱼的数量只有 $0,1,2,3$ 感觉可以用状态压缩做，只不过原先的二进制要改成四进制。

将每一个鱼的数量转化成四进制并记录，设 $dp_i$ 表示要达到压缩后 $i$ 状态时的最小花费，那么显然有一个状态转移方程 $dp_i=\min(dp_k+1)$ （其中 $k$ 表示压缩之后能转移到 $i$ 的状态，也就是它本身以及上下左右 $4$ 个能干涉它的点）。

## AC code
附注释
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5,MAXN=1049000;//最大是4^10

map <pair<int,int>,vector<int>> mapp;
//用来存图的信息的

int py[5][2]={{0,0},{0,1},{1,0},{-1,0},{0,-1}};
//偏移量
int n,m,k,pows[15],ans,val[N],dp[MAXN];
//n,m,k作用如题面，pows用于存4的幂次（转四进制），ans用来记录答案的状态
//val是每次输入的鱼的数量

bool check(int x){
	for (int i=0;i<k;i++){
		if (x%4>val[i])return 0;
		x/=4;
	}
	return 1;
}
bool check2(int x,int y){
	for (int i=0;i<y;i++)x/=4;
	if (x%4==val[y])return 0;
	return 1;
}
void init(){
	pows[0]=1;
	for (int i=1;i<11;i++)pows[i]=pows[i-1]*4;
	memset(dp,127,sizeof(dp));
	dp[0]=0;
	//预处理
}
signed main(){
	init();
	cin>>n>>m>>k;
	for (int i=0;i<k;i++){
		int x,y,w;
		cin>>x>>y>>w;
		val[i]=w;
		ans+=w*pows[i];
		for (int j=0;j<5;j++){
			int nt_x=x+py[j][0],nt_y=y+py[j][1];
			//更新图的信息，把当前点能干涉到的点全部加上他
			mapp[{nt_x,nt_y}].push_back(i);
		}
	}
	for (int i=0;i<pows[k];i++){
		if (!check(i))continue;
		for (auto j:mapp){
			//寻找对于i而言可以转移到的点
			vector<int> tem=j.second;
			int a=i;
			for (auto o:tem){
				if (!check2(a,o))continue;
				a+=pows[o];
			}
			dp[a]=min(dp[a],dp[i]+1);
		}
	}
	cout<<dp[ans];
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

逻辑推理，我们可以发现对于整个棋盘影响作用有效果的其实就是 10 个点左右，因为轰炸的范围是 5 个格子当两个点交叉的时候会产生两个最优的位置，10 个点的话最多也就是 10 个，如果是只能影响到一个放鱼位置的话直接处理即可，对于其他点可以直接暴力维护时间复杂度就是 $4^{10}$，可以通过！！

code：

```cpp
int ans,add=100000;
int dx[]={0,0,0,1,-1},dy[]={0,1,-1,0,0};
void dfs(int u,int sum){
	if(sum>add) return ;
	if(u==B.size()){
		for(auto&[x,y]:tv){
			if(w[x][y]<s[x][y]) return ;
		}
		add = min(sum,add);
		return ;
	}
	for(int i=0;i<=3;i++){
		auto [x,y]=B[u];
		for(int j=0;j<5;j++){
    		int a=x+dx[j],b=y+dy[j];
    		w[a][b]+=i;
    	}
		dfs(u+1,sum+i);
		for(int j=0;j<5;j++){
    		int a=x+dx[j],b=y+dy[j];
    		w[a][b]-=i;
    	}
	}
}
void solve(){
    
    cin>>n>>m>>k;
    for(int i=1;i<=k;i++){
    	int x,y,c; cin>>x>>y>>c;
    	s[x][y]+=c;
    	v.push_back({x,y});
    }
    
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    
    for(auto&[x,y]:v){ 
    	for(int i=0;i<5;i++){ // 跑周围的五个点算贡献
    		int a=x+dx[i],b=y+dy[i];
    		if(a<1 or a>n or b<1 or b>m) continue;
    		int cnt = 0;
    		for(int j=0;j<5;j++){
    			int na=a+dx[j],nb=b+dy[j];
    			if(na<1 or na>n or nb<1 or nb>m) continue;
    			if(s[na][nb]) cnt++;
    		}
    		A.push_back({cnt,a,b});
    	}
    }
    
    sort(A.begin(),A.end(),greater<TUP>());
    A.erase(unique(A.begin(),A.end()),A.end());
    
    for(auto[c,x,y]:A){
    	if(c>1){
    		B.push_back({x,y});
    		for(int i=0;i<5;i++){
    			int a=x+dx[i],b=y+dy[i];
    			if(a<1 or a>n or b<1 or b>m) continue;
    			if(s[a][b]) st[a][b]=true;
    		}
    	}
    }
    for(auto&[x,y]:v){
    	if(!st[x][y]) ans += s[x][y]; // 孤立的点自我检查
    	else tv.push_back({x,y});// 否则就是暴力检查的点
    }
	dfs(0,0);
	ans += add;
	cout << ans << endl;
}
```

---

## 作者：Fa_Nanf1204 (赞：0)

### 分析：
观察到 $k$ 和 $a_i$ 很小，考虑状压。

$dp_S$ 就表示当前 $k$ 个有鱼的格子里分别投了多少炸弹。

考虑转移方式，发现每个有鱼的格子最多只会被相邻的 $5$ 个格子炸到，所以每次枚举投放的格子，之后再更新新的状态，即可。

具体来说，设现在的状态为 $S$，投放炸弹之后的状态为 $now$，那么有转移方程 $dp_{now}=\min(dp_{now},dp_S+1)$。
### Code:

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std; 
int n,m,k;
int dp[1<<22];//表示当前状态的最小炸弹数 
int a[55],cnt,maxn[15];
int N=0;
int mp[1001005];
int main(){
	memset(dp,0x3f,sizeof dp);
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		int x,y,z;
		cin>>x>>y>>z;
		maxn[i]=z;
		a[++cnt]=x*m+y;//记录有可能投放炸弹的位置 
		if(x>=2) a[++cnt]=(x-1)*m+y;
		if(x<=n-1) a[++cnt]=(x+1)*m+y;
		if(y>=2)a[++cnt]=x*m+y-1;
		if(y<=m-1) a[++cnt]=x*m+y+1;
		N=(N<<2)+z;
		mp[x*m+y]=i;
	} 
	dp[0]=0;
	sort(a+1,a+cnt+1);
	cnt=unique(a+1,a+cnt+1)-a-1;
	for(int i=0;i<N;i++){
		for(int j=1;j<=cnt;j++){
			ll sum=i,x;
			if(mp[a[j]]!=0){//分别考虑五个位置 
				x=2*(k-mp[a[j]]);
				if((sum>>x)%4<=maxn[mp[a[j]]]-1) sum+=1<<x;	//如果这个位置的炸弹数超了，就不加了 
			}
			if(mp[a[j]+m]!=0){
				x=2*(k-mp[a[j]+m]);
				if((sum>>x)%4<=maxn[mp[a[j]+m]]-1) sum+=1<<x;
			}
			if(mp[a[j]-m]!=0){
				x=2*(k-mp[a[j]-m]);
				if((sum>>x)%4<=maxn[mp[a[j]-m]]-1) sum+=1<<x;
			}
			if(mp[a[j]+1]!=0){
				x=2*(k-mp[a[j]+1]);
				if((sum>>x)%4<=maxn[mp[a[j]+1]]-1) sum+=1<<x;
			}
			if(mp[a[j]-1]!=0){
				x=2*(k-mp[a[j]-1]);
				if((sum>>x)%4<=maxn[mp[a[j]-1]]-1) sum+=1<<x;
			}
			dp[sum]=min(dp[sum],dp[i]+1);
		}
	}
	cout<<dp[N];
	return 0;
}
```

---


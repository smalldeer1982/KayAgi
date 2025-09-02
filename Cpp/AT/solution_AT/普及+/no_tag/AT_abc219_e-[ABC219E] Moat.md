# [ABC219E] Moat

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc219/tasks/abc219_e

$ xy $ -平面上のいくつかの点に村があります。  
 高橋君はこれらの村を民兵や魔女などの外敵から守るため、これらのすべての村を囲むようなお堀を建設します。

$ 0 $ と $ 1 $ からなる $ 4\ \times\ 4 $ 行列 $ A\ =\ (A_{i,\ j}) $ が与えられます。  
 $ A_{i,\ j}\ =\ 1 $ を満たす整数の組 $ (i,\ j) $ $ (1\ \leq\ i,\ j\ \leq\ 4) $ ごとに、座標 $ (i-0.5,\ j-0.5) $ に村があります。

お堀は平面上の多角形です。 高橋君は以下の条件をすべて満たすお堀を建設します（入力例１・出力例１の説明も参考にして下さい）。

1. 自己交差がない
2. 内部にすべての村を含む
3. すべての頂点の $ x $ 座標と $ y $ 座標は $ 0 $ 以上 $ 4 $ 以下の整数
4. すべての辺は $ x $ 軸と $ y $ 軸のどちらかに平行
5. それぞれの内角の大きさは $ 90 $ 度または $ 270 $ 度

高橋君が建設するお堀として考えられるものが何通りあるかを出力して下さい。

## 说明/提示

### 制約

- $ A_{i,\ j}\ \in\ \lbrace\ 0,\ 1\rbrace $
- $ A_{i,\ j}\ =\ 1 $ となる $ (i,\ j) $ が少なくとも $ 1 $ つ存在する

### Sample Explanation 1

下記の $ 2 $ つの画像の例は、高橋君が建設する**お堀の条件を満たします**。 

![](https://img.atcoder.jp/ghi/7b3181deb4e1df72e4c0661b1137db4d.png)
![](https://img.atcoder.jp/ghi/a1e46c7db32d63942caa7119a4f3a593.png) 

下記の $ 4 $ つの画像の例は、高橋君が建設する**お堀の条件を満たしません**。 
![](https://img.atcoder.jp/ghi/335053c01a13eb99e55767a3dc02eb38.png)
![](https://img.atcoder.jp/ghi/c4df3d1fa24557b0d4d94ac0eaa8b9ab.png)
![](https://img.atcoder.jp/ghi/be93de595e9222d5e20c90bd28d24563.png)
![](https://img.atcoder.jp/ghi/37dac3af065c013ce0b8c0ee7591b97a.png) 

上記の $ 4 $ つの例が高橋君の建設するお堀の条件を満たさない理由は、以下の通りです。 - $ 1 $ つ目の画像の例は、「自己交差がない」という条件を満たしません。 - $ 2 $ つ目の画像の例は、「内部にすべての村を含む」という条件を満たしません。 - $ 3 $ つ目の画像の例は、「すべての頂点の $ x $ 座標と $ y $ 座標は $ 0 $ 以上 $ 4 $ 以下の整数」という条件を満たしません。（座標が整数でない頂点があります。） - $ 4 $ つ目の画像の例は、「すべての辺は $ x $ 軸と $ y $ 軸のどちらかに平行」という条件を満たしません。

## 样例 #1

### 输入

```
1 0 0 0
0 0 1 0
0 0 0 0
1 0 0 0```

### 输出

```
1272```

## 样例 #2

### 输入

```
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1```

### 输出

```
1```

# 题解

## 作者：2020luke (赞：1)

# [[ABC219E] Moat](https://www.luogu.com.cn/problem/AT_abc219_e) 题解

## 思路解析

一眼看到输入数据只有 $4$ 行 $4$ 列，直接想到状压枚举。可以直接枚举所有护城河所包含起来的格子，判断是否连通以及判断是否包含住了所有村庄。判断连通我选择用洪水填充，随便选一个包含着的格子，若可以通过当前格移动到所有被包含格就说明连通。以及还要判断被包围格子是否形成了一个环，例如：

![](https://cdn.luogu.com.cn/upload/image_hosting/a4a53t2s.png)

其中蓝线表示护城河，绿色阴影表示护城河包围的格子。可见图中有两条护城河，不符合题意。为排除掉这种情况，我们判断每一个没有被选择的格子，判断它是否被护城河完全包围，也就是判断能否走到地图外即可。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define PII pair<int, int>
#define fir first
#define sec second
int v[8][8], flag[8][8], f[8][8], ans = 0;
bool vis[8][8];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
void flood(int x, int y) {
	queue< PII > q;
	q.push({x, y});
	while(!q.empty()) {
		int xx = q.front().fir, yy = q.front().sec;
		q.pop();
		for(int i = 0; i < 4; i++) {
			int nx = xx + dx[i], ny = yy + dy[i];
			if(flag[nx][ny] && !f[nx][ny]) {
				f[nx][ny] = true;
				q.push({nx, ny});
			}
		}
	}
}
bool flood_loop(int x, int y) {
	queue< PII > q;
	q.push({x, y});
	memset(vis, false, sizeof(vis));
	vis[x][y] = true;
	while(!q.empty()) {
		int xx = q.front().fir, yy = q.front().sec;
		q.pop();
		for(int i = 0; i < 4; i++) {
			int nx = xx + dx[i], ny = yy + dy[i];
			if(!flag[nx][ny] && !vis[nx][ny]) {
				if(nx >= 1 && nx <= 4 && ny >= 1 && ny <= 4) {
					vis[nx][ny] = true;
					q.push({nx, ny});
				}
				else return true;
			}
		}
	}
	return false;
}
int check() {
	int x = 0, y = 0, cnt = 0;
	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= 4; j++) {
			if(flag[i][j]) cnt++, x = i, y = j;
		}
	}
	memset(f, 0, sizeof(f));
	f[x][y] = 1;
	flood(x, y);	//洪水填充判断连通
	int sum = 0;
	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= 4; j++) {
			if(f[i][j]) sum++;
		}
	}
	if(sum != cnt) return 0;	//不连通
	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= 4; j++) {
			if(v[i][j] && !f[i][j]) return 0;	//若有村庄没被包含
		}
	}
	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= 4; j++) {
			if(!flag[i][j] && !flood_loop(i, j)) return 0;	//被护城河完全包围
		}
	}
	return 1;
}
void dfs(int x, int y) {	//暴力枚举
	if(y > 4) y = 1, x++;
	if(x > 4) {
		ans += check();
		return;
	}
	flag[x][y] = 1;
	dfs(x, y + 1);
	flag[x][y] = 0;
	dfs(x, y + 1);
}
int main() {
	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= 4; j++) {
			cin >> v[i][j];
		}
	}
	dfs(1, 1);
	cout << ans;
	return 0;
}
```

---

## 作者：ZBH_123 (赞：1)

## 思路分析
本题是一道状态压缩 DP，如果枚举护城河的每一条边或是每一个顶点会非常麻烦。我们可以考虑枚举每个顶点是否被护城河覆盖，这可以用一个 $16$ 位的二进制数来表示。对于每一个二进制数所对应的状态，我们要去验证这种护城河是否满足条件。对于第 $3$、$4$、$5$ 个条件，我们就不用去验证了，因为按照这个思路构造出来的护城河是一定满足条件的。对于第 $2$ 个条件，我们需要将题目给的 $4 \times 4$ 的矩阵给压缩成长为 $16$ 的序列。具体的压缩方法是：第 $i$ 行第 $j$ 列的元素在序列中的位置为 $(i-1) \cdot 4+j$，其中 $1 \le i,j \le 4$。压缩好之后，我们取出二进制的每一位，放入状态矩阵的每一个位置。其中，二进制数从右往左第 $k$ 为对应矩阵中的位置是 $(k \div 4+1,k \bmod 4+1)$。取出状态后，我们判断村庄的位置是否被覆盖就行了。接下来重点讨论第 $1$ 个条件和一个坑点。

第 $1$ 个条件要求护城河没有自交点。没有自交点是一种怎样的情况呢？可以发现，如果将一个由被覆盖的方格组成并且每个方格都可以通过四个方向的移动到达所有方格的区域叫做一个连通块，那么符合第 $1$ 个条件的护城河一定只有一个连通块，所以我们只需要求出连通块的数量就行了。

解决了第 $1$ 个条件，我们还要解决本题的一个坑点。假如有一条护城河的包围区域如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/vaajfkxs.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这条护城河肯定是不合法的，因为要围成这种形状，就必须要两条护城河。那么，这种情况该怎么判断呢？可以发现，这种情况就是一个被包围区域构成的环。判断是否有环，就要从没被包围的区域入手。我们可以从没被包围的区域开始进行 DFS，如果没被包围的点能通过四个方向的移动走出这个矩阵，那就代表没有环，否则有环。

**AC code：**
```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int maxn=1<<16;
int a[5][5],b[5][5],cnt,l[4]={0,1,0,-1},r[4]={1,0,-1,0};
long long ans;
bool vis[5][5];
void dfs(int x,int y){
	vis[x][y]=true;
	for(int i=0;i<4;i++){
		int xx=x+l[i],yy=y+r[i];
		if(xx<1||yy<1||xx>4||yy>4||vis[xx][yy]||b[xx][yy]==0){
			continue;
		}
		dfs(xx,yy);
	}
}
bool dfs_cycle(int x,int y){
	if(x<1||y<1||x>4||y>4){
		return true;
	}
	if(b[x][y]==1){
		return false;
	}
	vis[x][y]=true;
	bool flag=false;
	for(int i=0;i<4;i++){
		int xx=x+l[i],yy=y+r[i];
		if(vis[xx][yy]==true){
			continue;
		}
		flag|=dfs_cycle(xx,yy);
	}
	return flag;
}
int main(){
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			cin>>a[i][j];
		}
	}
	for(int k=1;k<maxn;k++){
		for(int i=0;i<16;i++){
			b[i/4+1][i%4+1]=k>>i&1;
		}
		memset(vis,0,sizeof vis);
		bool ok=true,color=false;
		for(int i=1;i<=4;i++){
			for(int j=1;j<=4;j++){
				if(ok){
					if(b[i][j]==0&&!vis[i][j]){
						ok=dfs_cycle(i,j);
					}
					if(a[i][j]==1&&b[i][j]==0){
						ok=false;
					}
					if(b[i][j]==1){
						if(color==true&&!vis[i][j]){
							ok=false;
						}
						else{
							dfs(i,j);
							color=true;
						}
					}
				}
			}
		}
		if(ok){
			ans++;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：mojoege (赞：1)

## 分析

数据范围很容易想到状压，但又很容易误导成状压 dp。

只需要枚举那个点在护城河内，在去判断不合法的情况。第 4、5 种情况已经被排除了，只需要判断前三种情况。

第一种很好判断，第二种也只需要去判一下连通块是否只有一个，而第三种就有点难度了。我们发现，如果状压出来的护城河由两条的话肯定是围成了一个类似于大圆套小圆的结构，在状态中护城河包裹的是圆环，而中间那部分是没有被包裹的，这就只需要判断是否有一块没有选中的点是走不到边缘的，如果有，那一定是被圆环包裹住了，也就是不合法的情况。

最后统计答案。

第二种：![335053c01a13eb99e55767a3dc02eb38.png (800×711) (atcoder.jp)](https://img.atcoder.jp/ghi/335053c01a13eb99e55767a3dc02eb38.png)

第三种：![](https://img.atcoder.jp/ghi/253448a3d3672afcb8112d63eb91f689.png)

## 代码
```cpp
#include  <bits/stdc++.h>
using namespace std;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
int n = 4, ans;
int a[5][5], b[5][5], vis[5][5];

int dfs1(int x, int y){//找被护城河围起来了但不是城内的区域
    if (x <= 0 || x > n || y <= 0 || y > n) return 1;
    if (b[x][y]) return 0;
    vis[x][y] = 1;
    int flag = 0;
    for (int i = 0; i < 4; i++){
        int nx = x + dx[i], ny = y + dy[i];
        if (vis[nx][ny]) continue;
        flag |= dfs1(nx, ny);//这一个点所连接的点中只要有一个能走出去就行
    }
    return flag;
}

void dfs(int x, int y){//找连通块
    vis[x][y] = 1;
    for (int i = 0; i < 4; i++){
        int nx = x + dx[i], ny = y + dy[i];
        if (nx > 0 && nx <= n && ny > 0 && ny <= n && vis[nx][ny] == 0 && b[nx][ny] == 1) dfs(nx, ny);
    }
}

int main(){
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++) cin >> a[i][j];
    }
    for (int k = 1; k < (1 << (n * n)); k++){
        for (int i = 0; i < n * n; i++) b[i / n + 1][i % n + 1] = 1 & (k >> i);//状态中每一位对应着矩阵中哪一个地方
        memset(vis, 0, sizeof(vis));
        int flag = 1, cnt = 0;
        for (int i = 1; i <= n && flag; i++){
            for (int j = 1; j <= n && flag; j++){
                if (a[i][j] == 1 && b[i][j] == 0) flag = 0;//第一种情况
                else if (b[i][j] == 0 && !vis[i][j]) flag = dfs1(i, j);//第三种情况，有环
                else if (b[i][j] == 1){
                    if (cnt && !vis[i][j]) flag = 0;//第二种情况，有好多个连通块
                    else dfs(i, j), cnt++;
                }
            }
        }
        if (flag) ans++;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：PDAST (赞：0)

## 思路
由于数据非常小，一共只有 $16$ 个格子，所以考虑用二进制枚举即可。
枚举每个格子是否在圈内，接着用题中给到的几个条件 dfs 判断就好了。
## 代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int cnt,v[11][11],a[11][11],vis[11][11],ans;
int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
void dfs(int x,int y){
	cnt++;
	vis[x][y]=1;
	for(int i=0;i<4;i++){
		int xx=x+dx[i],yy=y+dy[i];
		if(xx>0&&yy>0&&xx<=4&&yy<=4&&!vis[xx][yy]&&v[xx][yy])dfs(xx,yy);
	}
}
int main(){
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++)cin>>a[i][j];
	}
	for(int k=1;k<(1<<16);k++){
		memset(v,0,sizeof(v));
		memset(vis,0,sizeof(vis));
		cnt=0;
		int x,y,sum=0;
		bool f=1;
		for(int i=1;i<=4;i++){
			for(int j=1;j<=4;j++){
				v[i][j]=((k>>((i-1)*4+j-1))&1);
				if(!v[i][j]&&a[i][j])f=0;
				if(v[i][j]){
					x=i;
					y=j;
					sum++;
				}
			}
		}
		if(!f)continue;
		dfs(x,y);
		if(cnt!=sum)continue;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=4;i++){
			for(int j=1;j<=4;j++)v[i][j]^=1;
		}
		for(int i=1;i<=4;i++){
			for(int j=1;j<=4;j++){
				if((i==1||j==1||i==4||j==4)&&v[i][j]&&!vis[i][j])dfs(i,j);
			}
		}
		if(cnt==16)ans++;
	}
	cout<<ans;
}
~~~

---

## 作者：apiad (赞：0)

一开始想到的是如何设计状压，是枚举护城河所在的点还是所在的边呢？思考着通过枚举护城河所在位置，推出有多少符合条件，显然，枚举点，很难算出有多少可能，枚举边，也是比较难算。

但是，正难则反，所以，我们直接状压哪些点被护城河包含着，那么，这显然对应着一个护城河的方案，我们只需要在判断一下是不是所有的村庄都在状压的点内，而且，这个方案能够形成唯一一条护城河。

难点就在这个方案能够形成唯一一条护城河，稍微画个图思考，就知道，如下两种不符合方案：

- 如果一个**不是状压枚举的点**被一堆**状压枚举的点**所包围，那么这个方案就不合法。为什么呢，因为这样类似一个环，里面要一圈护城河，外面要一圈护城河，两条，不符合方案。
- 如果状压枚举的点不连通，那么，不符合方案。

这样，我们就可以用洪水填充法。找一个是**状压枚举的点**，对它的连通块染色，注意，此时染色的只能是**状压枚举的点**。然后我们再找一个**非状压枚举的点**，对他的连通块染不同的色，此时也是只能染**非状压枚举的点**。然后我们再遍历所有的点，如果这个点没有被染色，要么就是**非状压枚举的点**被分成了多个连通块（也就是被包含的情况），或者是**状压枚举的点**被分成了多个连通块。

但是，我们发现这样做，有点小问题。

看看这组样例：

```
1 1 1 1
1 1 1 1
1 1 1 1
1 0 1 0
```

显然，这是有 $4$ 种方案，但是，你的代码会算出来 $3$。为啥？因为你的代码把最下面一行的 $0$ 判断成两个不同的连通块，但是，实际上他们可以同时包含的。

如果我们把图扩建：

```
0 0 0 0 0 0
0 1 1 1 1 0
0 1 1 1 1 0
0 1 1 1 1 0
0 1 0 1 0 0
0 0 0 0 0  0
```

外面套一圈 $0$，那么问题就解决了，下面的 $0$ 就可以是一个连通块了。

我们只需要把搜索的范围控制在 $([0,5],[0,5])$ 中即可。

我在深夜的时候寻找 2020luke 同学进行调代码：[link](https://atcoder.jp/contests/abc219/submissions/51102301)。

这一份代码我们两个人都没有发现问题，就睡觉了。实际上，那是个不起眼的错误，第二天早上发现了之后只能说是唐氏。

为什么呢？

我枚举了 $x$ 和 $y$ 轴，两重循环，而在 dfs 搜索之后仅仅是一个 break，他仅仅是推出了一个维度的循环啊。并没有将两个循环同时推出掉。非常堂食。所以在第二天早上，我把循环里面加了个标记的变量，方便直接推出两层循环，这样就直接 AC 了。如果遇到这种错误，确实也比较难看出来。

AC 的代码：[link](https://atcoder.jp/contests/abc219/submissions/51109572)。

---

## 作者：Rain_Brush (赞：0)

从官方题解翻译过来的。

考虑下列 $16$ 个格子 $R_1-R_{16}$：

![](https://img.atcoder.jp/ghi/890e8ef6ce7fd361cd2dde0804ec59e4.png)

一旦高桥决定建造护城河，$16$ 个区域中的每一个都属于护城河的内部或外部。

例如，在下面的图中，$16$ 个区域被分为两组: 护城河内的区域：$R_1,R_5,R_6,R_7,R_8,R_9,R_{13},R_{14},R_{15}$，以及护城河外的区域：$R_2,R_3,R_4,R_{10},R_{11},R_{12},R_{16}$。

![](https://img.atcoder.jp/ghi/895842478f20443f443e2fecfd45f1b3.png)

此外，如果高桥修建的两条护城河不同，那么划分也是不同的。因此，我们可以通过一切可能的方式将 $16$ 个地区分成两组，内部和外部，并检查是否存在相应的护城河，所有的村庄都包括在护城河内。

请注意，像下面两张图表这样的区域划分并不对应于护城河。

![](https://img.atcoder.jp/ghi/082392e296e12b6f5cb2a2e7a41e287b.png)

![](https://img.atcoder.jp/ghi/253448a3d3672afcb8112d63eb91f689.png)

$\texttt{My AC Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

using i64=long long;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int vill=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			int a;
			cin >> a;
			vill|=a << (4*i+j);
		}
	}
	
	int ans=0;
	for(int st=0;st<(1 << 16);st++){
		if((st & vill)!=vill)
			continue;
		
		vector<vector<int>> A(6,vector<int>(6));
		for(int i=1;i<=4;i++){
			for(int j=1;j<=4;j++){
				int x=i-1,y=j-1;
				A[i][j]=st >> (4*x+y) & 1;
			}
		}
		
		vector<int> id(36);
		for (int i=0;i<36;i++)
			id[i]=i;
		
		function<int(int)> find=[&](int x){
			if(id[x]!=x)
				id[x]=find(id[x]);
			return id[x];
		};
		
		int comp=36;
		for(int i=0;i<5;i++){
			for(int j=0;j<6;j++){
				int a=i*6+j,b=(i+1)*6+j;
				int ida=find(a),idb=find(b);
				
				if(A[i][j]==A[i+1][j] && ida!=idb){
					id[ida]=idb;
					comp-=1;	
				}
			}
		}
		
		for(int i=0;i<6;i++){
			for(int j=0;j<5;j++){
				int a=i*6+j,b=i*6+(j+1);
				int ida=find(a),idb=find(b);
				
				if(A[i][j]==A[i][j+1] && ida!=idb){
					id[ida]=idb;
					comp-=1;	
				}
			}
		}
		
		if(comp==2)
			ans++;
	}
	
	cout << ans;
	return 0;
}
```
[AC 记录](/record/116011189)

---

## 作者：_zzzzzzy_ (赞：0)

# 思路
看数据范围可以发现状态的数量最多是 $2^{16}$ 个，那么我们可以来暴力枚举保护的和没有保护的。

对于每一次保护和没保护我们可以求一下最后受保护的连通块是不是一，如果是的话就说明这个状态是合法的。

最后我们求连通块可以用爆搜来求，也可以用并查集来求，这里的代码用并查集来求，我们可以把没有保护的并到一个集合里，然后当成立时，这个状态有 $2$ 个集合。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5;
int a[maxn][maxn],b[maxn][maxn];
int f[maxn*maxn],sz[maxn*maxn];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
void I(int n){for(int i=0;i<=n;i++)f[i]=i,sz[i]=1;}
int F(int x){return x==f[x]?x:f[x]=F(f[x]);}
void U(int x,int y){
	x=F(x),y=F(y);
	if(x!=y){
		f[y]=x;
		sz[x]+=sz[y];
		sz[y]=0;
	}
}
signed main(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			cin>>a[i][j];
		}
	}
	int ans=0;
	for(int st=0;st<(1<<16);st++){
		memset(b,0,sizeof b);
		for(int i=0;i<16;i++){
			if(st&(1<<i)){
				b[i/4][i%4]=1;
			}
		}
		bool flag=0;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				if(a[i][j]==1&&b[i][j]==0){
					flag=1;
				}
			}
		}
		if(flag==0){
			I(17);
			for(int x=0;x<4;x++){
				for(int y=0;y<4;y++){
					for(int i=0;i<4;i++){
						int nx=x+dx[i],ny=y+dy[i];
						if(nx<0||nx>=4||ny<0||ny>=4){
							if(b[x][y]==0){
								U(x*4+y,16);
							}
						}
						else{
							if(b[x][y]==b[nx][ny]){
								U(x*4+y,nx*4+ny);
							}
						}
					}
				}
			}
			int cnt=0;
			for(int i=0;i<=16;i++){
				if(i==F(i))cnt++;
			}
			if(cnt==2)ans++;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

首先题目给定的多边形一定顶点在格点上且边缘为直角，则一定是把 $ 16 $ 个格子分成两个部分，被保护和不被保护。

观察到 $ n $ 很小，枚举子集也完全可以通过，于是可以暴力枚举每个格子属于哪个部分，然后保证所有输入格子都在被保护的部分内即可。

但这样会出现一个问题：可能会出现一个不被保护的格子在被保护的内部，或者被保护的格子被分割成若干块，显然都不满足题意。

对于这个问题，只需要维护一个并查集，在边界加一圈 $ 0 $，然后判断两个部分是不是全部连通即可。因为某些原因这里用了 LCT 实现的并查集，有需要的话改回普通并查集即可。

时间复杂度 $ \mathcal{O}(2^n \times n) $，其中 $ n=16 $ 为输入大小，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+10;
const int mod=1e18;
int q,u,v,c;
char op;
struct Splay
{
    int ch[maxn][2],fa[maxn],siz[maxn],val[maxn],sum[maxn],add[maxn],mul[maxn],rev[maxn];
    void clear(int x)
    {
        ch[x][0]=ch[x][1]=fa[x]=siz[x]=val[x]=sum[x]=add[x]=rev[x]=0;
        mul[x]=1;
    }
    int getch(int x)
    {
        return (ch[fa[x]][1]==x);
    }
    int isroot(int x)
    {
        clear(0);
        return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
    }
    void maintain(int x)
    {
        clear(0);
        siz[x]=(siz[ch[x][0]]+1+siz[ch[x][1]])%mod;
        sum[x]=(sum[ch[x][0]]+val[x]+sum[ch[x][1]])%mod;
    }
    void pushdown(int x)
    {
        clear(0);
        if(mul[x]!=1)
        {
            if(ch[x][0])
            mul[ch[x][0]]=(mul[x]*mul[ch[x][0]])%mod,val[ch[x][0]]=(val[ch[x][0]]*mul[x])%mod,sum[ch[x][0]]=(sum[ch[x][0]]*mul[x])%mod,add[ch[x][0]]=(add[ch[x][0]]*mul[x])%mod;
            if(ch[x][1])
            mul[ch[x][1]]=(mul[x]*mul[ch[x][1]])%mod,val[ch[x][1]]=(val[ch[x][1]]*mul[x])%mod,sum[ch[x][1]]=(sum[ch[x][1]]*mul[x])%mod,add[ch[x][1]]=(add[ch[x][1]]*mul[x])%mod;
            mul[x]=1;
        }
        if(add[x])
        {
            if(ch[x][0])
            add[ch[x][0]]=(add[ch[x][0]]+add[x])%mod,val[ch[x][0]]=(val[ch[x][0]]+add[x])%mod,sum[ch[x][0]]=(sum[ch[x][0]]+add[x]*siz[ch[x][0]])%mod;
            if(ch[x][1])
            add[ch[x][1]]=(add[ch[x][1]]+add[x])%mod,val[ch[x][1]]=(val[ch[x][1]]+add[x])%mod,sum[ch[x][1]]=(sum[ch[x][1]]+add[x]*siz[ch[x][1]])%mod;
            add[x]=0;
        }
        if(rev[x])
        {
            if(ch[x][0])
            rev[ch[x][0]]^=1,swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
            if(ch[x][1])
            rev[ch[x][1]]^=1,swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
            rev[x]=0;
        }
    }
    void update(int x)
    {
        if(!isroot(x))
        update(fa[x]);
        pushdown(x);
    }
    void rotate(int x)
    {
        int y=fa[x],z=fa[y],chx=getch(x),chy=getch(y);
        fa[x]=z;
        if(!isroot(y))
        ch[z][chy]=x;
        ch[y][chx]=ch[x][chx^1];
        fa[ch[x][chx^1]]=y;
        ch[x][chx^1]=y;
        fa[y]=x;
        maintain(y);
        maintain(x);
        maintain(z);
    }
    void splay(int x)
    {
        update(x);
        for(int f=fa[x];f=fa[x],!isroot(x);rotate(x))
        if(!isroot(f))
        rotate(getch(x)==getch(f)?f:x);
    }
    void access(int x)
    {
        for(int f=0;x;f=x,x=fa[x])
        splay(x),ch[x][1]=f,maintain(x);
    }
    void makeroot(int x)
    {
        access(x);
        splay(x);
        swap(ch[x][0],ch[x][1]);
        rev[x]^=1;
    }
    int find(int x)
    {
        access(x);
        splay(x);
        while(ch[x][0])
        x=ch[x][0];
        splay(x);
        return x;
    }
    void final_mul(int u,int v,int c)
    {
    makeroot(u), access(v), splay(v);
      val[v] = val[v] * c % mod;
      sum[v] = sum[v] * c % mod;
      mul[v] = mul[v] * c % mod;
    }
    void final_add(int u,int v,int c)
    {
    makeroot(u), access(v), splay(v);
      val[v] = (val[v] + c) % mod;
      sum[v] = (sum[v] + siz[v] * c % mod) % mod;
      add[v] = (add[v] + c) % mod;
    }
    int query1(int u,int v)
    {
    makeroot(u), access(v), splay(v);
    return sum[v];
    }
    void link(int u,int v)
    {
    if (find(u) != find(v)) 
    makeroot(u), fa[u] = v;
    }
    void cut(int u,int v)
    {
    makeroot(u);
      access(v);
      splay(v);
      if (ch[v][0] == u && !ch[u][1]) 
      ch[v][0] = fa[u] = 0;
    }
    bool query2(int u,int v)
    {
    return find(u) == find(v);
    }
}st;
int find(int x)
{
return st.find(x);
}
void merge(int u,int v)
{
st.link(u,v);
}
void clean(int n)
{
for(int i=1;i<=n;i++)
st.clear(i),st.maintain(i),st.splay(i);
}//main
int a[40],final;
int encode(int i,int j)
{
return i*6+j+1;
}
int chose[40];
int x[6]={0,-1,1,0,0},y[6]={0,0,0,-1,1};
bool inrange(int x,int l,int r)
{
return l<=x&&x<=r;
}
signed main()
{
    int now=0;
	for(int i=1;i<=4;i++)
    for(int j=1;j<=4;j++)
    {
		int x;
        cin>>x;
        now=(now<<1)+x;
	}
for(int sub=0;sub<(1<<16);sub++)
if((sub&now)==now)
{
for(int j=0;j<16;j++)
{
	int x=j/4,y=j%4;
	if((sub>>j)&1)
	chose[encode(x+1,y+1)]=1;
	else 
    chose[encode(x+1,y+1)]=0;
}
int n=6;
clean(50);
for(int i=0;i<6;i++)
	for(int j=0;j<6;j++)
    {
		if(i+1<6&&chose[encode(i,j)]==chose[encode(i+1,j)]) 
        merge(encode(i,j),encode(i+1,j));
		if(j+1<6&&chose[encode(i,j)]==chose[encode(i,j+1)]) 
        merge(encode(i,j),encode(i,j+1));
	}
bool ans=1;
for(int c=0;c<=1;c++)
{
int lst=-1;
bool ok=1;
for(int i=0;i<n;i++)
for(int j=0;j<n;j++)
if(chose[encode(i,j)]==c)
{
if(lst==-1)
lst=st.find(encode(i,j));
else if(lst!=st.find(encode(i,j)))
ok=0;
}
if(ok==0)
ans=0;
}
final+=ans;
}
cout<<final;
}
```


---


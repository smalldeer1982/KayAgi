# [POI 2019/2020 R1] Układ scalony / 集成电路

## 题目背景

Bajtel 公司专门生产集成电路板。

---

因为数据较多，所以 Subtask 1 的另一部分挪到了 [这里](https://www.luogu.com.cn/problem/U122678)。

## 题目描述

Bajtel 公司生产的集合电路板的大小为 $n \times m$，现在通电的格子为 $(1,1)$。

我们可以在两个相邻的格子连上电路让一个格子的电通向另一个格子，若干个电路组成集合电路。

现在我们要连 $n \times m-1$ 条电路，并且要求最长的集合电路 **恰好** 长度为 $k$，并且要求 **让所有格子通电**。

求一种连接电路的方式。

## 说明/提示

#### 样例说明

对于样例 $1$，如下图

![](https://cdn.luogu.com.cn/upload/image_hosting/ly5swltx.png)

另一组附加样例请见附加文件中的 sample.zip。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（20 pts）：$n,m \le 6$。
- Subtask 2（20 pts）：$n \le 3$。
- Subtask 3（30 pts）：$n \times m$ 为奇数。
- Subtask 4（30 pts）：$n \times m$ 为偶数。

对于 $100\%$ 的数据，$1 \le n,m \le 1000$，$0 \le k \le 10^6$。

如果您输出了 `TAK`（并且这个数据点的确有解），但是您在后面电路连接的描述中出错，您可以获得 $20\%$ 的分数。

#### 说明

翻译自 [POI 2019](https://sio2.mimuw.edu.pl/c/oi27-1/dashboard/) E [Układ scalony](https://sio2.mimuw.edu.pl/c/oi27-1/p/ukl/)。

## 样例 #1

### 输入

```
2 3 4```

### 输出

```
TAK
1 1 1 2
1 1 2 1
1 2 2 2
2 3 2 2
1 2 1 3```

## 样例 #2

### 输入

```
2 3 1```

### 输出

```
NIE```

## 样例 #3

### 输入

```
2 3 3 ```

### 输出

```
TAK
1 2 2 2
1 1 1 2
2 2 2 3
1 2 1 3
2 2 2 1```

## 样例 #4

### 输入

```
1 10 10```

### 输出

```
NIE```

# 题解

## 作者：Computer1828 (赞：9)

这翻译什么鬼&一血&严重拉低AC率

### 题目翻译：

有 $n\cdot m$ 个点排成 $n$ 行 $m$ 列，坐标 $(i,j)$ 表示的是第 $i$ 行第 $j$ 列的点。如果两个点 $A(x_1,y_1)$ $B(x_2,y_2)$ 的距离 $\left\vert x_2-x_1 \right\vert + \left\vert y_2-y_1\right\vert = 1$ ，则 $A$ 和 $B$ 之间有边权为 $1$ 的边相连。给定整数 $k$ ，构造一个这个图的生成树，使生成树的直径恰好为 $k$ 。


------------

首先考虑合法的 $k$ 的范围是多少。

不难发现，当 $n$ 为奇数时， $k\in [n+m-2,nm-1]$ ；当 $n$ 为偶数时， $k\in [n+m-1,nm-1]$ 。这里分类讨论特判一下即可。

然后考虑怎么构造一个直径长度为 $k$ 的生成树。可以分类讨论一下。

以下的图中每个格子代表一个点，左上角的格子的坐标是 $(1,1)$ ，右下角的格子的坐标是 $(n,m)$ ，相邻的格子之间有一条边权为 $1$ 的边，红色粗线表示的是生成树的边。

当 $n$ 为奇数时，可以先构造出 $k = n+m-2$ 的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/2ztq8kb3.png)

然后构造出 $k = nm-1$ 的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/0twxtyl8.png)

思考一下是如何从左边构造出右边的（以下是 $n = 5,m = 4,k = 9$ 的情况）：

![](https://cdn.luogu.com.cn/upload/image_hosting/2wkwut6f.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/wqub40yg.png)

也就是说，先构造出一条主干 A ，然后以主干的端点为起点，继续构造（假设后来构造的叫主干 B ），直到主干 A 的长度加上主干 B 的长度 $= k$ 为止。对于其它不在主干 A 或主干 B 上的点，沿竖直方向连接到主干 A 上。

当 $n$ 为偶数时，仿照上面的做法就行了（以下是 $n = 4,m = 4,k = 10$ 的情况）:

![](https://cdn.luogu.com.cn/upload/image_hosting/jbuawcax.png)

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
bool flag;
int f[1005][1005];
inline void add(int x1,int y1,int x2,int y2){
	if(flag) swap(x1,y1),swap(x2,y2);
	printf("%d %d %d %d\n",x1,y1,x2,y2);
}
inline void dosth1(){
	if(k<n+m-2 || k>=n*m){
		printf("NIE\n");
		return ;
	} 
	printf("TAK\n");
	k -= n+m-2;
	for(int i = 1;i<=n/2;++i) add(i,1,i+1,1);
	for(int i = 1;i<m;++i) add(n/2+1,i,n/2+1,i+1);
	for(int i = 1;i<=n/2;++i) add(i+n/2+1,m,i+n/2,m);
	for(int i = 1;i<=n/2;++i) for(int j = 2;j<=m;++j) f[i][j] = 1;
	for(int i = 1;i<=n/2;++i) for(int j = 1;j<m;++j) f[i+n/2+1][j] = -1;
	for(int i = 1;i<=n/2 && k;++i){
		if(i%2 == 1){
			for(int j = 2;j<=m && k;++j){
				if(j == 2){
					if(i == 1) add(i,j,i,j-1);
					else add(i,j,i-1,j);
				}else add(i,j,i,j-1);
				f[i][j] = 0,k--;
			}
		}else{
			for(int j = m;j>=2 && k;--j){
				if(j == m) add(i,j,i-1,j);
				else add(i,j,i,j+1);
				f[i][j] = 0,k--;
			}
		}
	}
	for(int i = n;i>n/2+1 && k;--i){
		if(i%2 == 1){
			for(int j = m-1;j>=1 && k;--j){
				if(j == m-1){
					if(i == n) add(i,j,i,j+1);
					else add(i,j,i+1,j);
				}else add(i,j,i,j+1);
				f[i][j] = 0,k--;
			}
		}else{
			for(int j = 1;j<m && k;++j){
				if(j == 1) add(i,j,i+1,j);
				else add(i,j,i,j-1);
				f[i][j] = 0,k--;
			}
		}
	}
	for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) if(f[i][j]) add(i,j,i+f[i][j],j);
}

inline void dosth2(){
	if(n == 2) swap(n,m),flag = true;
	if(k<n+m-1 || k>=n*m){
		printf("NIE\n");
		return ;
	} 
	printf("TAK\n");
	k -= n+m-2;
	for(int i = 1;i<n/2;++i) add(i,1,i+1,1);
	for(int i = 1;i<m;++i) add(n/2,i,n/2,i+1);
	for(int i = 1;i<=n/2;++i) add(i+n/2-1,m,i+n/2,m);
	for(int i = 1;i<n/2;++i) for(int j = 2;j<=m;++j) f[i][j] = 1;
	for(int i = 1;i<=n/2;++i) for(int j = 1;j<m;++j) f[i+n/2][j] = -1;
	for(int i = 1;i<n/2 && k;++i){
		if(i%2 == 1){
			for(int j = 2;j<=m && k;++j){
				if(j == 2){
					if(i == 1) add(i,j,i,j-1);
					else add(i,j,i-1,j);
				}else add(i,j,i,j-1);
				f[i][j] = 0,k--;
			}
		}else{
			for(int j = m;j>=2 && k;--j){
				if(j == m) add(i,j,i-1,j);
				else add(i,j,i,j+1);
				f[i][j] = 0,k--;
			}
		}
	}
	for(int i = n;i>n/2 && k;--i){
		if(i%2 == 1){
			for(int j = 1;j<m && k;++j){
				if(j == 1) add(i,j,i+1,j);
				else add(i,j,i,j-1);
				f[i][j] = 0,k--;
			} 
		}else{
			for(int j = m-1;j>=1 && k;--j){
				if(j == m-1){
					if(i == n) add(i,j,i,j+1);
					else add(i,j,i+1,j);
				}else add(i,j,i,j+1);
				f[i][j] = 0,k--;
			}
		}
	}
	for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) if(f[i][j]) add(i,j,i+f[i][j],j);
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	if(m%2 == 1) swap(n,m),flag = true;
	if(n%2 == 1) dosth1();
	else dosth2();
	return 0;
}
```
其实代码可以写得更短，并不需要冗杂的分类讨论，但是不分类讨论的写法的细节过于复杂，不便在此赘述。

---

## 作者：Jryno1 (赞：3)

# P6663

某人场上写了：

```cpp
for(int k=j-1;k>=1;k++){
    pd((edge){k,l,k,l+1});
}
```

导致挂 $40$ pts。

## 题意

有 $n\times m$ 的网格图，构造出一棵树，要求每个格子都在树上，且树的直径为 $d$。可能无解。

$n,m\le 1000,k\le 10^6$。

## Sol

先考虑无解的情况，即 $n,m$ 对于 $d$ 的限制。直径最大值是好构造的，即所有点形成一条长度为 $nm-1$ 的链，画出来长成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/a34ks7ko.png) 

再考虑下界，由于最左上角和右下角是联通的，因此至少也应该是 $(n-1)+(m-1)$。先尝试直接构造出来一种最小直径的方案：

![](https://cdn.luogu.com.cn/upload/image_hosting/6zztr62j.png)

但这个结论并不正确，不论是通过手玩还是对拍会发现，这种情况可以存在当且仅当 $m$ 或者 $n$ 是奇数的情况，即我们能够找到从中间劈开来的一列。如果两个都是偶数，找不到，因此应该是如下图的 $(n-1)+(m-1)+1$ 的下界。

![](https://cdn.luogu.com.cn/upload/image_hosting/e01we5a1.png)

判断完界限之后，考虑如何构造的问题。我们可以从直径最小的情况出发，看有没有方法能够每一次给直径 $+1$ 最终达到直径最大的情况。由于奇数的情况简单，先从奇数入手。参照最大直径的情况，尝试每一次改变一条边，让直径增大。

![](https://cdn.luogu.com.cn/upload/image_hosting/ky14ev0o.png)

按照这种翻转操作（当然有非常多的改变方法，这仅仅是本人考场上想到的，不代表最优方法），对于分割线右边从左到右翻转，可以做到每次对于答案增加 $1$，并且不会影响到其他的结构。对于左边同理，这样做完刚好可以回到直径最大的情况。

最后考虑偶数的情况，其实是类似的，只是多了中间的一条边。先考虑移动中间的一条边（即图三的橙色边），每次平移都会让答案增大 $2$。那么只需要开始先移动这条边，之后再做与奇数相同的操作即可。

总结，先判断是否有解，之后看 $n,m$ 是否都是偶数，如果不是就找到奇数的那个数并从中劈开，然后模拟从最小直径每次翻转边 $+1$ 的过程。如果都是偶数，先用中间的边每次 $+2$，最后通过与奇数操作一样的来调整 $+1$。

这道题难点可能就在于代码实现上面了。

[ 考场代码 ](https://www.luogu.com.cn/record/120484540)

---

## 作者：Mirasycle (赞：1)

首先，构造上下界。上界显然是 $nm-1$，下界需要分奇偶讨论。右下左上联通，所以需要至少 $n-1+m-1$ 的长度，我们发现对于 $m,n$ 中有一个奇数的情况是可以满足的。在奇数那里从中间一列劈开，然后分别向两边连。对于偶数，我们无法到最中间的那个，那么只能选择相对更靠中间的那个。然后如果我们链延生选择同侧，就是这样
![图1](https://cdn.luogu.com.cn/upload/image_hosting/x2ep23ce.png)

会造成长度加一，也就是 $n+m-1$。

最后的构造很显然就是调整法了。我们逐步将最小情况往大去调整，直到遇到答案。以 $n$ 为奇数为例，我们先构造出红笔的主链，然后目前潜在的连边方式是黑笔的下界，如果我们要调整就一点一点地调整成蓝笔的上界，按照那个螺旋线一点点走就行。
![图2](https://cdn.luogu.com.cn/upload/image_hosting/ndfs8sh1.png)

我们可以设置一个标号数组，$f_{i,j}$ 表示该点连边的朝向，初始化就初始黑边朝向即可。然后如果要变更，就改成蓝笔朝向。

本题在 $n,m$ 为偶数的时候的构造，初始状态不要设置为图 $1$ 中那种最小值情况，而是同理设置为图 $2$，方便后续调整构造，图 $1$ 形态不方便调整。

代码细节很多，还有些分类讨论，不太好写。从上午调到下午，WA了很多发，中间还换了种实现方式，终于写出了一个较为简洁的正解。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+10;
int n,m,k,f[maxn][maxn]; bool flip=0;
bool vis[maxn][maxn];
void add(int x1,int y1,int x2,int y2){
	if(flip) swap(x1,y1),swap(x2,y2);
	cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
}
void merge1(int l,int r,int row){ for(int i=l;i<r;i++) add(i,row,i+1,row); }
void merge2(int l,int r,int line){ for(int i=l;i<r;i++) add(line,i,line,i+1); }
void merge3(int x,int y){
	if(f[x][y]==1) add(x,y,x-1,y);
	if(f[x][y]==2) add(x,y,x,y+1);
	if(f[x][y]==3) add(x,y,x+1,y);
	if(f[x][y]==4) add(x,y,x,y-1);
}
int dy,nx,ny,ns,p;
bool check1(){
	if(nx+1==p&&((ny==m&&ns==2)||(ny==2&&ns==4))) return 0;
	return 1;
}
bool check2(){
	if(nx-1==p&&((ny==1&&ns==4)||(ny==m-1&&ns==2))) return 0;
	return 1;
}
int main(){
	cin>>n>>m>>k;
	if(m%2==1) swap(n,m),flip^=1;
	if(n%2==1&&(k<n+m-2||k>=n*m)){ cout<<"NIE"<<endl; return 0; }
	if(n%2==0&&(k<n+m-1||k>=n*m)){ cout<<"NIE"<<endl; return 0; }
	if(n==2) swap(n,m),flip^=1;
	cout<<"TAK"<<endl; k-=n+m-2; p=(n+1)/2;
	merge1(1,p,1); merge2(1,m,p); merge1(p,n,m);
	memset(f,0,sizeof(f)); memset(vis,1,sizeof(vis));
	for(int i=1;i<p;i++)
		for(int j=2;j<=m;j++) f[i][j]=3,vis[i][j]=0;
	for(int i=p+1;i<=n;i++)
		for(int j=1;j<m;j++) f[i][j]=1,vis[i][j]=0;
	dy=1,nx=1,ny=1,ns=2;
	while(k&&nx!=p&&check1()){
		if(!vis[nx][ny+dy]){ f[nx][ny]=ns; ny+=dy; k--; }
		else if(ny==m){ f[nx][ny]=3; nx++; ns=4; dy=-1; k--; }
		else if(ny==2){ f[nx][ny]=3; nx++; ns=2; dy=1; k--;  }
		f[nx][ny]=0;
	}
	dy=-1,nx=n,ny=m,ns=4;
	while(k&&check2()){
		if(!vis[nx][ny+dy]){ f[nx][ny]=ns; ny+=dy; k--; }
		else if(ny==1){ f[nx][ny]=1; nx--; ns=2; dy=1; k--; }
		else if(ny==m-1){ f[nx][ny]=1; nx--; ns=4; dy=-1; k--;  }
		f[nx][ny]=0;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) merge3(i,j);
	return 0;
}
```

---

## 作者：drmr (赞：1)

**题意**：给定一个 $N \times M$ 的网格，现在要在该网格图中构造一棵生成树，使其直径为 $K$。

首先答案的上界一定为 $N \times M - 1$，接下来，由于左下角和右下角的最短距离是矩形边长，下界为 $N + M - 2$。

![1.png](https://www.helloimg.com/i/2025/01/10/6780dc819c3b5.png)

尝试构造一个长度接近上界的，需要先将周围的点按照上右下左的方向连接，于是我们希望剩下的节点不会影响答案。我们可以采用如图所示的做法。在该图中，虚线表示不影响直径的点和边。

这样构造有一定问题。当直径过小时，可能存在两条虚线长度相加大于直径的情况。因此，我们对于 $k \le 2N + M$ 时进行新的构造，如图所示。

![2.png](https://www.helloimg.com/i/2025/01/10/6780ddb985d15.png)

当此时直径较小时，可以在左侧加点，使其满足，如图所示。

![3.png](https://www.helloimg.com/i/2025/01/10/6780dc81d15cf.png)

但是，当 $M$ 为偶数时，该方法可能会失效，如图，红色的部分会代替直径，使直径偏大。此时，若 $N$ 是奇数则右转 $90\degree$。若两者均为偶数则无解。

![4.png](https://www.helloimg.com/i/2025/01/10/6780dc819a18b.png)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
int n, m, d, used[N][N];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m >> d;

	if(d >= n * m){
		cout << "NIE\n";
		return 0;
	}
	if(d < n + m - 2){
		cout << "NIE\n";
		return 0;
	}

	if(n == 1){
		cout << "TAK\n";
		for(int i = 2; i <= m; i++)
			cout << "1 " << i - 1 << " 1 " << i - 0 << "\n";
		return 0;
	}
	if(m == 1){
		cout << "TAK\n";
		for(int i = 2; i <= n; i++)
			cout << i - 1 << " 1 " << i << " 1\n";
		return 0;
	}

	if(d == n + m - 2){
		if(n % 2 == 0 && m % 2 == 0){
			cout << "NIE\n";
			return 0;
		}
		if(n % 2 == 1 && m % 2 == 0 && n > 2){
			cout << "TAK\n";
			int mid = max(2, (n + 1) >> 1);
			for(int i = 1; i < m; i++){
				cout << mid << " " << i << " " << mid << " " << i + 1 << "\n";
				used[mid][i] = 1;
				used[mid][i + 1] = 1;
			}
			for(int i = 1; i < mid; i++){
				cout << i << " 1 " << i + 1 << " 1\n";
				used[i][1] = used[i + 1][1] = 1;
			}
			for(int i = mid; i < n; i++){
				cout << i << " " << m << " " << i + 1 << " " << m << "\n";
				used[i][m] = used[i + 1][m] = 1;
			}
			d -= n + m - 2;
			for(int i = 2; i <= d + 1; i++){
				cout << 1 << " " << i - 1 << " " << 1 << " " << i << "\n";
				used[1][i] = used[1][i - 1] = 1;
			}
			for(int i = 1; i < mid; i++)
				for(int j = 1; j <= m; j++)
					if(!used[i][j])
						cout << i << " " << j << " " << i + 1 << " " << j << "\n";
			for(int i = mid + 1; i <= n; i++)
				for(int j = 1; j <= m; j++)
					if(!used[i][j])
						cout << i << " " << j << " " << i - 1 << " " << j << "\n";
			return 0;
		}
	}
	cout << "TAK\n";

	if(d <= n + n + m - 3 && m > 2){
		int mid = max(2, (m + 1) >> 1);
		for(int i = 1; i < n; i++){
			cout << i << " " << mid << " " << i + 1 << " " << mid << "\n";
			used[i][mid] = 1;
			used[i + 1][mid] = 1;
		}
		for(int i = 1; i < mid; i++){
			cout << "1 " << i << " 1 " << i + 1 << "\n";
			used[1][i] = used[1][i + 1] = 1;
		}
		for(int i = mid; i < m; i++){
			cout << n << " " << i << " " << n << " " << i + 1 << "\n";
			used[n][i] = used[n][i + 1] = 1;
		}
		d -= n + m - 2;
		for(int i = 2; i <= d + 1; i++){
			cout << i - 1 << " " << 1 << " " << i << " " << 1 << "\n";
			used[i - 1][1] = used[i][1] = 1;
		}

		for(int i = 1; i <= n; i++){
			for(int j = 1; j < mid; j++)
				if(!used[i][j])
					cout << i << " " << j << " " << i << " " << j + 1 << "\n";
			for(int j = mid + 1; j <= m; j++)
				if(!used[i][j])
					cout << i << " " << j - 1 << " " << i << " " << j << "\n";
		}
		return 0;
	}

	for(int i = 1; i <= n; i++) used[i][0] = used[i][m + 1] = 1;
	for(int i = 1; i <= m; i++) used[0][i] = used[n + 1][i] = 1;
	int dir = 0, x = n, y = 1;
	if(m == 2) y = 2, dir = 3;
	used[x][y] = 1;
	while(d--){
		cout << x << " " << y << " ";
		if(used[x + dx[dir]][y + dy[dir]]) dir = (dir + 1) % 4;
		x += dx[dir], y += dy[dir];
		cout << x << " " << y << "\n";
		used[x][y] = 1;
	}

	dir = (dir + 1) % 4;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(!used[i][j])
				cout << i << " " << j << " " << i + dx[dir] << " " << j + dy[dir] << "\n";
		}
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

恶心人的构造题。

## 思路

首先不难发现 $n+m-2\leq k\leq n\times m-1$。

先考虑抽一条长度为 $n+m-2$ 的从左上到右下的链。先尝试让其他分支出去的部分小于其到两端的距离。

不难发现可以现在中间一列构造从上到下的链，然后第一行构造从第一列到中间列的链，最后一行构造中间列到最后一列的链。

朴素的想法是，将中间一行作为一条链，在这条链两边连从上到下的链。

不难发现此时若 $n,m$ 均为奇数时直径一定是左上到右下的链，其中一个为偶数时直径不超过 $+1$。

当 $k>n+m-2$ 时，可以在两端（左上和右下）添加一些在未填区域“绕”的链。就可以让链等于 $k$ 了。注意因为原来情况直径最多为 $n+m-1$，$k>n+m-2$ 时不需特殊考虑其中一个为偶数的情况。

当 $k=n+m-2$ 且 $n,m$ 其中有且仅有一个偶数时，可以选择奇数长度的一边正中间连出一条链，然后另一个方向每一行/列均填满链即可。

当 $k=n+m-2$ 且 $n,m$ 均为偶数时，不存在符合要求的解。

Proof：记最终构造出的树的直径中点（之一）为 $t$。分该点在不同区域内讨论。记距离 $t$ 最远的三个端点为 $a,b,c$，其中中间一个（记为 $b$）指的是三点所构成三角形的直角所在位置。不难发现 $(a,b),(b,c)$ 之间至少有一组的路径是 $(a,t,b)$ 或 $(b,t,c)$。此时该距离大于 $n+m-2$。

这道题还要稍微特判一下 $n$ 或 $m$ 为 $2$ 的情况。因为此时没有中间链。这部分构造较为容易，具体见代码。

总复杂度 $O(nm)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
int cnt[1005];
signed main(){
	int n,m,k; cin>>n>>m>>k;
	if(k>=n+m-2&&k<=n*m-1){
		if((!((n*m)&1))&&k==n+m-2){
			if((!(n&1))&&(!(m&1))){
				cout<<"NIE";
				return 0;
			}
			cout<<"TAK\n";
			if(n&1){
				for(int i=1;i<=m;i++){
					for(int j=1;j<n;j++){
						cout<<j<<" "<<i<<" "<<j+1<<" "<<i<<"\n";
					}
				}
				for(int i=1;i<m;i++){
					cout<<(n+1)/2<<" "<<i<<" "<<(n+1)/2<<" "<<i+1<<"\n";
				}
			}
			else{
				for(int i=1;i<=n;i++){
					for(int j=1;j<m;j++){
						cout<<i<<" "<<j<<" "<<i<<" "<<j+1<<"\n";
					}
				}
				for(int i=1;i<n;i++){
					cout<<i<<" "<<(m+1)/2<<" "<<i+1<<" "<<(m+1)/2<<"\n";
				}
			}
			return 0;
		}
		if(n==2){
			cout<<"TAK\n";
			for(int i=1;i<m;i++) cout<<1<<" "<<i<<" "<<1<<" "<<i+1<<"\n";
			cout<<1<<" "<<1<<" "<<2<<" "<<1<<"\n";
			for(int i=1;i<k-(n+m-2);i++){
				cout<<2<<" "<<i<<" "<<2<<" "<<i+1<<"\n";
			}
			for(int i=k-(n+m-2)+1;i<=m;i++){
				cout<<1<<" "<<i<<" "<<2<<" "<<i<<"\n";
			}
			return 0;
		}
		else if(m==2){
			cout<<"TAK\n";
			for(int i=1;i<n;i++) cout<<i<<" "<<1<<" "<<i+1<<" "<<1<<"\n";
			cout<<1<<" "<<1<<" "<<1<<" "<<2<<"\n";
			for(int i=1;i<k-(n+m-2);i++){
				cout<<i<<" "<<2<<" "<<i+1<<" "<<2<<"\n";
			}
			for(int i=k-(n+m-2)+1;i<=n;i++){
				cout<<i<<" "<<1<<" "<<i<<" "<<2<<"\n";
			}
			return 0;
		}
		cout<<"TAK\n";
		//middle column
		int md=(m+1)/2;
		for(int i=1;i<n;i++) cout<<i<<" "<<md<<" "<<i+1<<" "<<md<<"\n";
		for(int i=1;i<md;i++) cout<<1<<" "<<i<<" "<<1<<" "<<i+1<<"\n";
		for(int i=md;i<m;i++) cout<<n<<" "<<i<<" "<<n<<" "<<i+1<<"\n";
		k-=(n+m-2);
		//add left len
		for(int i=1;i<md;i++) cnt[i]=2;
		for(int i=md+1;i<=m;i++) cnt[i]=n-1;
		int x,y,dir;
		x=1,y=1,dir=2;
		while(k&&!(x==n&&((dir==2&&y==1)||(dir==1&&y==md-1)))&&md!=1){
			k--;
			if(dir==1){
				if(y==md-1) cout<<x<<" "<<y<<" "<<x+1<<" "<<y<<"\n",x++,cnt[y]=x+1,dir=2;
				else cout<<x<<" "<<y<<" "<<x<<" "<<y+1<<"\n",y++,cnt[y]=x+1;
			}
			else{
				if(y==1) cout<<x<<" "<<y<<" "<<x+1<<" "<<y<<"\n",x++,cnt[y]=x+1,dir=1;
				else cout<<x<<" "<<y<<" "<<x<<" "<<y-1<<"\n",y--,cnt[y]=x+1;
			}
		}
		if(k){
			x=n,y=m,dir=1;
			while(k){
				k--;
				if(dir==1){
					if(y==m) cout<<x<<" "<<y<<" "<<x-1<<" "<<y<<"\n",x--,cnt[y]=x-1,dir=2;
					else cout<<x<<" "<<y<<" "<<x<<" "<<y+1<<"\n",y++,cnt[y]=x-1;
				}
				else{
					if(y==md+1) cout<<x<<" "<<y<<" "<<x-1<<" "<<y<<"\n",x--,cnt[y]=x-1,dir=1;
					else cout<<x<<" "<<y<<" "<<x<<" "<<y-1<<"\n",y--,cnt[y]=x-1;
				}
			}
		}
		//left part
		int maxv=0; for(int i=1;i<md;i++) maxv=max(maxv,cnt[i]);
		int mdl=max(n/2+1,maxv);
		if(mdl<=n){
			for(int i=1;i<md;i++) cout<<mdl<<" "<<i<<" "<<mdl<<" "<<i+1<<"\n";
			for(int i=1;i<md;i++) for(int j=mdl;j>cnt[i];j--) cout<<j<<" "<<i<<" "<<j-1<<" "<<i<<"\n";
			for(int i=1;i<md;i++) for(int j=mdl;j<n;j++) cout<<j<<" "<<i<<" "<<j+1<<" "<<i<<"\n";
		}
		//right part
		int minv=1e9; maxv=0; for(int i=md+1;i<=m;i++) minv=min(minv,cnt[i]),maxv=max(maxv,cnt[i]);
		if(minv==0){
			if(maxv>0){
				if(cnt[md+1]==1){
					for(int i=md+1;cnt[i]==1;i++){
						cout<<1<<" "<<i-1<<" "<<1<<" "<<i<<"\n";
					}
				}
				else{
					cout<<2<<" "<<m<<" "<<1<<" "<<m<<"\n";
					for(int i=m-1;cnt[i]==1;i--){
						cout<<1<<" "<<i+1<<" "<<1<<" "<<i<<"\n";
					}
				}
			}
			return 0;
		}
		mdl=min((n+1)/2,minv/2+1);
		if(mdl>=1){
			for(int i=md;i<m;i++) cout<<mdl<<" "<<i<<" "<<mdl<<" "<<i+1<<"\n";
			for(int i=md+1;i<=m;i++) for(int j=mdl;j>1;j--) cout<<j<<" "<<i<<" "<<j-1<<" "<<i<<"\n";
			for(int i=md+1;i<=m;i++) for(int j=mdl;j<cnt[i];j++) cout<<j<<" "<<i<<" "<<j+1<<" "<<i<<"\n";
		}
	}
	else{
		cout<<"NIE";
	}
	return 0;
}
```

---

## 作者：tzc_wk (赞：0)

> 摘自我的[贪心 & 构造 & DP 选做Ⅱ](https://www.cnblogs.com/ET2006/p/greedy-construction-dp2.html) 中的第 $39$ 题

~~咦？怎么学校模拟赛的题也混到我博客里了（~~

首先不难发现构造出的树的直径有个下界，考虑如何求出这个下界，显然这个下界不低于 $n+m-2$ 对吧，因为 $(1,1)$ 和 $(n,m)$ 的距离就已经达到了 $n+m-2$，因此我们肯定尽量希望直径长度尽可能接近这个值。可以发现，如果 $n$ 为奇数，那么我们可以按照如下的方式使树的直径达到 $n+m-2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/e12t66pk.png)

对于 $m$ 为奇数的情况也是同理，只需在上图中将图关于 $y=x$ 进行一次翻折即可。

而 $n,m$ 均为偶数的情况，通过观察 $n=m=2$ 以及 $n=2,m=4$ 的情况我们大胆猜测，无法构造出直径为 $n+m-2$ 的方案，因此对于 $n,m$ 为偶数的情况，直径的下界就是 $n+m-1$。

接下来考虑如何根据直径下界构造出合法的解，下面不妨假设 $(n-1)m$ 为偶数，也就是说如果 $n,m$ 中至少有一个为奇数，那么 $n$ 为奇数。考虑分情况讨论：

若 $d\le 2(n-1)+(m-1)$，那么我们在只需在上图的基础之上稍微做一些改动，有以下两种可能：

- 如果 $d\le (n-1)+(m-1)+\dfrac{n-1}{2}$，那么我们断开 $(\dfrac{n+1}{2},1)$ 与 $(\dfrac{n+3}{2},1)$ 之间的边，连上 $(\dfrac{n+3}{2},1)$ 与 $(\dfrac{n+1}{2}-(d-(n-1)-(m-1)),1)$ 之间的边。
- 如果 $d>(n-1)+(m-1)+\dfrac{n-1}{2}$，那么我们断开 $(\dfrac{n+1}{2},1)$ 与 $(\dfrac{n+3}{2},1)$ 之间的边，连上 $(\dfrac{n+3}{2},1)$ 与 $(1,1)$ 之间的边。再断开 $(\dfrac{n+1}{2},m)$ 与 $(\dfrac{n+3}{2},m)$ 之间的边，连上 $(\dfrac{n+3}{2},m)$ 与 $(\dfrac{n+1}{2}-(d-((n-1)+(m-1)+\dfrac{n-1}{2})),m)$ 之间的边。

直接用这些公式描述连断边的情况可能不太直观，借助下图 $n=5,m=6,d=12$ 的构造可能可以更好地理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/pxd6dd1g.png)

若 $d>2(n-1)+(m-1)$，那么我们先从 $(n,1)$ 开始，连接 $(n,1),(n-1,1)$ 的边、$(n-1,1),(n-2,1)$ 的边，……，$(2,1),(1,1)$ 的边，$(1,1),(1,2)$ 的边，$(1,2),(1,3)$ 的边，……，$(1,m-1),(1,m)$ 的边，$(1,m),(2,m)$ 的边，$(2,m),(3,m)$ 的边，……，$(n-1,m),(n,m)$ 的边，然后在中间部分反复徘徊直到直径长度达到 $d$，对于剩余的点直接连向它上方的节点即可，例如 $n=5,m=6,d=23$ 的情况可以按照如下方式构造：

![](https://cdn.luogu.com.cn/upload/image_hosting/gca4kjhe.png)

直接模拟即可。时间复杂度 $\Theta(nm)$。

```cpp
const int MAXN=1000;
int n,m,D,vis[MAXN+5][MAXN+5];bool rev;
void prt(int x1,int y1,int x2,int y2){
	if(rev) printf("%d %d %d %d\n",y1,x1,y2,x2);
	else printf("%d %d %d %d\n",x1,y1,x2,y2);
}
int main(){
//	freopen("grid.in","r",stdin);
//	freopen("grid.out","w",stdout);
	scanf("%d%d%d",&n,&m,&D);int mnd=n-1+m-1;
	if(D>=n*m) return puts("NIE"),0;
	if((~n&1)&&(~m&1)) mnd++;
	if(D<mnd) return puts("NIE"),0;
	if(n&1) swap(n,m),rev=1;
//	printf("%d\n",mnd);
	puts("TAK");
	if(D<=(n-1)+2*(m-1)){
//		puts("-1");
		for(int i=2;i<n;i++) for(int j=1;j<m;j++) prt(i,j,i,j+1);
		int mid=m+1>>1,nd=D-mnd;
		for(int i=1;i<n;i++) prt(i,mid,i+1,mid);
		if(!nd){
			for(int j=1;j<m;j++){
				prt(1,j,1,j+1);
				if(n!=1) prt(n,j,n,j+1);
			}
		} else if(nd<mid){
			for(int j=1;j<m;j++) prt(n,j,n,j+1);
			for(int j=1;j<mid;j++) prt(1,j,1,j+1);
			for(int j=mid+1;j<m;j++) prt(1,j,1,j+1);
			prt(1,mid-nd,1,mid+1);
		} else {
			for(int j=1;j<mid;j++) prt(1,j,1,j+1),prt(n,j,n,j+1);
			for(int j=mid+1;j<m;j++) prt(1,j,1,j+1),prt(n,j,n,j+1);
			prt(1,1,1,mid+1);prt(n,mid-(nd-mid+1),n,mid+1);
		}
	} else {
		for(int i=1;i<m;i++) prt(n,i,n,i+1);
		for(int i=n;i>=2;i--) prt(i,1,i-1,1);
		for(int i=1;i<m;i++) prt(1,i,1,i+1);
		for(int i=1;i<=m;i++) vis[1][i]=vis[n][i]=1;
		for(int i=1;i<=n;i++) vis[i][1]=1;
		prt(1,m,2,m);int rst=D-(n-1)-2*(m-1)-1,x=2,y=m,dir=0;
		vis[x][y]=1;
		while(rst--){
			if(dir&1) prt(x,y,x,y-1),y--,dir=(dir+1)&3;
			else if(dir==0){
				prt(x,y,x+1,y);x++;
				if(x==n-1) dir=(dir+1)&3;
			} else {
				prt(x,y,x-1,y);x--;
				if(x==2) dir=(dir+1)&3;
			} vis[x][y]=1;
		}
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(!vis[i][j])
			prt(i,j,i,j-1);
	}
	return 0;
}
/*
5 5 20

5 5 10
*/
```

---


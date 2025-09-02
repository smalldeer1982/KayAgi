# Orac and Game of Life

## 题目描述

Please notice the unusual memory limit of this problem.

Orac likes games. Recently he came up with the new game, "Game of Life".

You should play this game on a black and white grid with $ n $ rows and $ m $ columns. Each cell is either black or white.

For each iteration of the game (the initial iteration is $ 0 $ ), the color of each cell will change under the following rules:

- If there are no adjacent cells with the same color as this cell on the current iteration, the color of it on the next iteration will be the same.
- Otherwise, the color of the cell on the next iteration will be different.

Two cells are adjacent if they have a mutual edge.

Now Orac has set an initial situation, and he wants to know for the cell $ (i,j) $ (in $ i $ -th row and $ j $ -th column), what will be its color at the iteration $ p $ . He may ask you these questions several times.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1349C/4db31c297e8a6314da42c884c8f60724b3ebcd9e.png)For the first example, the picture above shows the initial situation and the color of cells at the iteration $ 1 $ , $ 2 $ , and $ 3 $ . We can see that the color of $ (1,1) $ at the iteration $ 1 $ is black, the color of $ (2,2) $ at the iteration $ 2 $ is black, and the color of $ (3,3) $ at the iteration $ 3 $ is also black.

For the second example, you can prove that the cells will never change their colors.

## 样例 #1

### 输入

```
3 3 3
000
111
000
1 1 1
2 2 2
3 3 3```

### 输出

```
1
1
1```

## 样例 #2

### 输入

```
5 2 2
01
10
01
10
01
1 1 4
5 1 4```

### 输出

```
0
0```

## 样例 #3

### 输入

```
5 5 3
01011
10110
01101
11010
10101
1 1 4
1 2 3
5 5 3```

### 输出

```
1
0
1```

## 样例 #4

### 输入

```
1 1 3
0
1 1 1
1 1 2
1 1 3```

### 输出

```
0
0
0```

# 题解

## 作者：CYJian (赞：9)

考虑到，如果有两个挨在一起的同色格子，则下一时刻它们肯定还是同色。

也就是说，我们可以把同色的格子缩成一个点，它们每个时刻的状态是一样的！

```plain
01010
11101
01010
```

比如上面这个栗子，左边那个呈十字的 $1$ 连通块颜色一定每个时刻都相同。

然后再考虑变化一个时刻之后，每个大连通块颜色都会取反。这时候如果周围有四周颜色都与其不同的格子的话，这种格子就会并入大连通块中。例如上面的图，在下一时刻就会变成：

```plain
00010
00001
00010
```

之前 $1$ 连通块的十字全变成了 $0$，然后就将周围的 $0$ 也并入大连通块里头了。

不难发现，除非整个图都是 $01$ 交错，否则任何一个单独的点都能被大连通块并入。

那么我们考虑一遍 $\rm BFS$ 求出每个点在哪个时刻，被并入一个初始颜色是啥的大连通块中，就能直接计算第 $p$ 时刻其颜色了。

复杂度 $O(nm+q)$。

$\rm Code$：

```cpp
int n, m, q;
char s[1010][1010];
int bel[1010][1010];
int tim[1010][1010];

struct Node {
	int x, y;

	Node() {}
	Node(int x, int y):x(x), y(y) {}
};

queue<Node>Q;

inline int chk(Node x) {
	return 1 <= x.x && x.x <= n && 1 <= x.y && x.y <= m;
}

int main() {
	memset(bel, -1, sizeof(bel));

	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= n; i++)
		scanf("%s", s[i] + 1);

	for(int i = 1; i <= n; i++) 
		for(int j = 1; j <= m; j++) {
			int tmp = 0;
			tmp |= s[i][j] == s[i - 1][j];
			tmp |= s[i][j] == s[i + 1][j];
			tmp |= s[i][j] == s[i][j - 1];
			tmp |= s[i][j] == s[i][j + 1];
			if(tmp) {
				bel[i][j] = s[i][j] - 48;
				Q.push(Node(i, j));
			}
		}

	while(!Q.empty()) {
		Node x = Q.front(); Q.pop();
		Node t;
		t = Node(x.x + 1, x.y);
		if(chk(t) && bel[t.x][t.y] == -1) Q.push(t), bel[t.x][t.y] = bel[x.x][x.y], tim[t.x][t.y] = tim[x.x][x.y] + 1;
		t = Node(x.x - 1, x.y);
		if(chk(t) && bel[t.x][t.y] == -1) Q.push(t), bel[t.x][t.y] = bel[x.x][x.y], tim[t.x][t.y] = tim[x.x][x.y] + 1;
		t = Node(x.x, x.y + 1);
		if(chk(t) && bel[t.x][t.y] == -1) Q.push(t), bel[t.x][t.y] = bel[x.x][x.y], tim[t.x][t.y] = tim[x.x][x.y] + 1;
		t = Node(x.x, x.y - 1);
		if(chk(t) && bel[t.x][t.y] == -1) Q.push(t), bel[t.x][t.y] = bel[x.x][x.y], tim[t.x][t.y] = tim[x.x][x.y] + 1;
	}

	while(q--) {
		int x = ri, y = ri;
		ll k = rl;
		if(bel[x][y] == -1 || k < tim[x][y]) putchar(s[x][y]);
		else putchar(48 | (bel[x][y] ^ (k & 1)));
		puts("");
	}
	return 0;
}
```

---

## 作者：VenusM1nT (赞：4)

$\textbf{Bfs}$.  
令所有非连通块的初值为 $\infty$，令所有连通块的初值为 $0$，则在一次变换后它会与周围所有值为 $\infty$ 的独立方块同色，且在下一次变换中与其一起变换颜色，于是可以自连通块开始 $\textbf{Bfs}$，令 $\textbf{Bfs}$ 到的值为 $\infty$ 的独立方块的值为当前方块的值 $+1$，代表这个方块在第几次被 $\textbf{Bfs}$ 到，并在下一次改变颜色。因此我们只需要在查询时奇偶判断一下就可以了。（当然，若查询时间到的时候当前方块还没被 $\textbf{Bfs}$ 到则不改变颜色。）
```cpp
#include<bits/stdc++.h>
#define MAXN 1005
#define M 10000000
#define reg register
#define inl inline
#define int long long
using namespace std;
struct Node
{
	int x,y;
};
queue <Node> q;
int n,m,Q,a[MAXN][MAXN];
char ch[MAXN][MAXN];
signed main()
{
	memset(a,60,sizeof(a));
	scanf("%lld %lld %lld",&n,&m,&Q);
	for(reg int i=1;i<=n;i++) scanf("%s",ch[i]+1);
	for(reg int i=1;i<=n;i++)
	{
		for(reg int j=1;j<=m;j++)
		{
			if(ch[i][j]==ch[i-1][j] || ch[i][j]==ch[i+1][j] || ch[i][j]==ch[i][j-1] || ch[i][j]==ch[i][j+1])
			{
				a[i][j]=0;
				q.push((Node){i,j});	
			}
		}
	}
	while(!q.empty())
	{
		reg Node now=q.front();
		q.pop();
		reg int i=now.x,j=now.y;
		if(i+1<=n && a[i+1][j]>M)
		{
			a[i+1][j]=a[i][j]+1;
			q.push((Node){i+1,j});
		}
		if(j+1<=m && a[i][j+1]>M)
		{
			a[i][j+1]=a[i][j]+1;
			q.push((Node){i,j+1});
		}
		if(i-1>=1 && a[i-1][j]>M)
		{
			a[i-1][j]=a[i][j]+1;
			q.push((Node){i-1,j});
		}
		if(j-1>=1 && a[i][j-1]>M)
		{
			a[i][j-1]=a[i][j]+1;
			q.push((Node){i,j-1});
		}
	}
	/*for(reg int i=1;i<=n;i++)
	{
		for(reg int j=1;j<=m;j++)
		{
			if(a[i][j]>M) printf("%c ",'A');
			else printf("%d ",a[i][j]);
		}
		puts("");
	}*/
	while(Q--)
	{
		reg int x,y,t;
		scanf("%lld %lld %lld",&x,&y,&t);
		if(a[x][y]>t) printf("%c\n",ch[x][y]);
		else
		{
			reg int p=t-a[x][y];
			if(p&1) printf("%c\n",ch[x][y]=='0'?'1':'0');
			else printf("%c\n",ch[x][y]);
		}
		
	}
	return 0;
}
```

---

## 作者：juicyyou (赞：2)

# CF1349C Orac and Game of Life
## 题目大意：
有翻译，就不放了。
## 解法：
构造一个矩阵 $B$，其中 $B_{i, j}$ 表示在当前时刻 $i, j$ 的格子能否变化。如果可以则为 1， 不可以则为 0。那么我们首先知道，如果一对相邻的格子颜色相同，那他们在以后的任意一个时刻颜色都相同。然后我们考虑 $B$。
以样举例 ：
```cpp
0 1 0 1 1
1 0 1 1 0
0 1 1 0 1
1 1 0 1 0
1 0 1 0 1
```
的 $B$为：
```cpp
0 0 0 1 1
0 0 1 1 0
0 1 1 0 0
1 1 0 0 0
1 0 0 0 0
```
我们进行一次变换后，$B$变为：
```cpp
0 0 1 1 1
0 1 1 1 1
1 1 1 1 0
1 1 1 0 0
1 1 0 0 0
```
我们发现，中间这个 1 的连通块中所有的格子，都向外扩展了一次！

实际上，由于所有 0 的连通块都是 0 1 交错的，所以，所有 1 的连通块每次都会向外扩展一格。那么一个$B$中0格子变为1时的时候就是最开始时所有 1 格子据他的最短路径的长度，那么一遍 BFS 就搞定了。然后查询时，如果查询时刻小于其最短路径，那么它的颜色就不变，否则，在最短路径长度个时刻 + 1时，这个格子开始在0 1间变化，那么答案就为：

$$(a_{i, j} + q - dis_{i,j}) \mod 2$$

下面是我的Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 1e5 + 5;
const ll maxm = 1e3 + 5;
inline void qread(){}
template<class T1, class ...T2>
inline void qread(T1 &IEE, T2&... ls){
	register T1 __ = 0, ___ = 1;
	register char ch;
	while(!isdigit(ch = getchar())) ___ = (ch == '-') ? -___ : ___;
	do{
		__ = (__ << 1) + (__ << 3) + (ch ^ 48);
	}while(isdigit(ch = getchar()));
	__ *= ___;
	IEE = __;
	qread(ls...);
	return ;
}
ll n, m, k, aa, b, c;
const ll dar[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
char ch;
int a[maxm][maxm], d[maxm][maxm];
bool p[maxm][maxm];
queue<pair<ll, ll> > q;
int main(){
	qread(n, m, k);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			cin >> ch;
			a[i][j] = ch - '0';
		}
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			for(int k = 0;k < 4;k++){
				ll tx = i + dar[k][0], ty = j + dar[k][1];
				if(tx > n || tx < 1 || ty > m || ty < 1) continue;
				if(a[tx][ty] == a[i][j]){
					p[i][j] = 1;
				}
			}
		}
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if(p[i][j]){
				q.push(make_pair(i, j));
			} 
		}
	}
	bool flag = 0;
	if(q.empty()) flag = 1;
	while(!q.empty()){
		ll x = q.front().first, y = q.front().second;
		q.pop();
		for(int i = 0;i < 4;i++){
			ll tx = x + dar[i][0], ty = y + dar[i][1];
			if(tx > n || tx < 1 || ty > m || ty < 1) continue;
			if(p[tx][ty]) continue;
			d[tx][ty] = d[x][y] + 1;
			p[tx][ty] = 1;
			q.push(make_pair(tx, ty));
		}
	}
	while(k--){
		qread(aa, b, c);
		if(flag == 1){
			cout << a[aa][b] << endl;
			continue;
		}
		if(c < d[aa][b]){
			cout << a[aa][b] << endl;
			continue;
		}
		c -= d[aa][b];
		cout << (a[aa][b] + c) % 2;
		puts("");
	}
	return 0;
}
```
上述算法的时间复杂度即为 $\mathcal O(n \cdot m)$，可以通过此题。

---

## 作者：TsH_GD (赞：1)

### 分析

发现一个点什么时候开始变化决定于**离他最近的开始变化的点**是哪个，因此只要求出**最短距离**即可

朴素的想法是通过 bfs 从每个点往外遍历，但是复杂度过高。其实可以考虑从步数考虑，从步数为 $1$ 的不断往外扩展。这样不会炸内存，复杂度也满意


## 献上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e5+10;
char g[1010][1010];
int d[1010][1010];
struct node{
    int x,y;
};
vector<node> q[3020];
int in[1010][1010];
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
int main(){
    ios::sync_with_stdio(false);
    int n,m,t;
    cin>>n>>m>>t;
    int i,j;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            cin>>g[i][j];
        }
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            for(int k=0;k<4;k++){
                int a=i+dx[k];
                int b=j+dy[k];
                if(a&&a<=n&&b&&b<=m){
                    if(g[a][b]==g[i][j]){
                        d[i][j]=1;
                        in[i][j]=1;
                        q[1].push_back({i,j});
                        break;
                    }
                }
            }
        }
    }
    for(i=1;i<=n+m;i++){
        int sz=q[i].size();
        if(sz){
            for(auto tmp:q[i]){
                for(int k=0;k<4;k++){
                    int a=tmp.x+dx[k];
                    int b=tmp.y+dy[k];
                    if(a&&a<=n&&b&&b<=m&&(!in[a][b])){
                        in[a][b]=1;
                        d[a][b]=i+1;
                        q[i+1].push_back({a,b});
                    }
                }
            }
        }
    }
    while(t--){
        ll a,b,c;
        cin>>a>>b>>c;
        if(d[a][b]==0){
            cout<<(g[a][b]-'0')<<endl;
            continue;
        }
        if(c<d[a][b]){
            cout<<(g[a][b]-'0')<<endl;
        }
        else{
            c++;
            c-=d[a][b];
            if(c%2==0){
                cout<<(g[a][b]-'0')<<endl;
            }
            else{
                cout<<((g[a][b]-'0')^1)<<endl;
            }
        }
    }
}
```

---

## 作者：UnfortunatelyDead (赞：0)

考虑当一个棋子满足变动颜色的条件的时候，那么和它颜色一样的点一定也会跟着一起变，然后之后的时候一定是 $0/1$ 更替的。

不难发现，如果我们知道一个棋子满足变动颜色的时间的话，我们可以据此推测出第 $p$ 时间是它的颜色，于是考虑预处理这个时间。

对于每个棋子，如果它能扩展到其相邻的棋子的话，那他一定是只要正好 $1$ 时间的，因为如果两个棋子原颜色相同的话会直接变成连通块。

开局预处理出所有的连通块，然后 BFS 即可，复杂度 $O(nm)$。

```cpp
const int N = 1019, dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
char c[N][N]; int a[N][N];
char Getchar() {
	char c = getchar();
	while (c != '0' && c != '1') c = getchar();
	return c;
}
struct node {
	int x, y, step;
};
signed main() {
	int n, m, t;
	read(n, m, t);
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) c[i][j] = 'a', a[i][j] = 1e18;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) c[i][j] = Getchar();
	queue<node> q;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) if (c[i][j] == c[i-1][j] || c[i][j] == c[i+1][j] || c[i][j] == c[i][j-1] || c[i][j] == c[i][j+1]) {
		a[i][j] = 0;
		q.push({i, j, 0});
	}
	while (!q.empty()) {
		auto [x, y, s] = q.front();
		q.pop();
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx && ny && nx <= n && ny <= m)
			if (a[nx][ny] == 1e18) {
				a[nx][ny] = s + 1;
				q.push({nx, ny, s+1});
			}
		}
	}
	while (t--) {
		int x, y, p;
		read(x, y, p);
		if (a[x][y] >= p) write(c[x][y] - '0', '\n');
		else write((c[x][y] - '0' + (p - a[x][y])) % 2, '\n');
	}
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
比较简单的一个有意思的题。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
首先对于一个大小 $s\ge2$ 的全 $0/1$ 连通块，在变换之后他们肯定还是全 $0/1$ 连通块。

接着来考虑孤立点。

孤立点，顾名思义，其周围的格子都与他不同。

那么孤立点是否一直不变呢？

显然不是的，若孤立点周围的任意一个点在连通块里，则经过一次变换后，这个在连通块中的点的值就会变的和孤立点相同。

也就是，如果一个 $0/1$ 连通块旁边有孤立点，那么经过一次变换，这个孤立点就会被并入这个 $0/1$ 连通块。

如果孤立点的旁边还是孤立点，那就能一步步扩展，都并入连通块。

接着考虑如何求出并入的时间。

孤立点 $i,j$ 并入连通块需要的变换次数即为 $d_{i,j}$。

其中 $d_{i,j}$ 表示距离 $i,j$ 最近的连通块距离。

连通块经过 $t$ 次操作变成的权值就非常简单了，在此不多赘述。

对于 $d_{i,j}$ 的求法，则考虑使用 bfs 即可。

注意特判全是孤立点的情况。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1010,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f,lim=20;
const int dxy[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int n,m,Q,tot,mp[N][N],d[N][N];char s[N][N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='0'&&c<='1'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
signed main()
{
    n=read(),m=read(),Q=read();queue<pair<int,int>>q;
    for(int i=1,l;i<=n;i++) l=0,rd(s[i],l);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
        for(int k=0;k<4;k++)
        {
            int dx=i+dxy[k][0],dy=j+dxy[k][1];
            if(s[dx][dy]==s[i][j]) mp[i][j]=1,q.push({i,j});
        }
    int f=q.empty();
    while(!q.empty())
    {
        auto [x,y]=q.front();q.pop();
        for(int i=0;i<4;i++)
        {
            int dx=x+dxy[i][0],dy=y+dxy[i][1];
            if(dx<1||dy<1||dx>n||dy>m||mp[dx][dy]) continue;
            mp[dx][dy]=1;d[dx][dy]=d[x][y]+1;q.push({dx,dy});
        }
    }
    for(int i=1,x,y,t;i<=Q;i++)
    {
        x=read(),y=read(),t=read();
        if(f||t<d[x][y]) put(s[x][y]),put('\n');
        else print((s[x][y]-'0'+t-d[x][y])%2),put('\n');
    }
    genshin:;flush();return 0;
}
```

---

## 作者：ZZZZZZZF (赞：0)

### 思路

先找规律

1. $01$ 交替不会发生变化

2. 如果图上有相邻的 $0$ 或 $1$，每次变化都会把相邻的格子同化

我们只需要计算出每个格子与最近的连通块的曼哈顿距离就能知道此格子什么时候开始变化，然后通过时间奇偶性判断结果即可

从 $0$ 和 $1$ 的连通块开始 bfs，然后注意一下 long long 即可

### Code:
```cpp
#include <bits/stdc++.h>
#define N 1010
#define INF 2147483646
 
using namespace std;
 
int m, n, t;
int a[N][N], dis[N][N];
int tmp[4][2] = { {0,-1},{0,1},{-1,0},{1,0} };
 
struct point {
	int x, y;
};
 
int getDis(int x,int y) {
	int minDis = INF, vx, vy;
	if (x == 0 || y == 0 || x == m + 1 || y == n + 1)
		return INF - 1;
	for (int i = 0; i < 4; i++) {
		vx = x + tmp[i][0];
		vy = y + tmp[i][1];
		if (dis[vx][vy] < minDis)
			minDis = dis[vx][vy];
	}
	return minDis;
}
 
queue<point> q;
 
int main() {
	//freopen("data.in", "r", stdin);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			a[i][j] = -1;
			dis[i][j] = INF;
		}
 
	char c;
	scanf("%d%d%d", &m, &n, &t);
	for (int i = 1; i <= m; i++) {
		c = getchar();
		for (int j = 1; j <= n; j++) {
			c = getchar();
			if (c == '0')a[i][j] = 0;
			if (c == '1')a[i][j] = 1;
		}
	}
 
	//起点为 0 1 块的 bfs
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++) {
			if (a[i][j] == a[i][j - 1] ||
				a[i][j] == a[i][j + 1] ||
				a[i][j] == a[i - 1][j] ||
				a[i][j] == a[i + 1][j]) {
				dis[i][j] = 0;
				q.push(point{ i,j });
			}
		}
 	
	while (!q.empty()) {
		int x = q.front().x, y = q.front().y, vx, vy;
		q.pop();
        	//拙劣的边界判断
		if (x == 0 || y == 0 || x == m + 1 || y == n + 1)continue;
        
        	//判断是否为 0 1 块边缘的点
		if (dis[x + 1][y] == INF ||
			dis[x - 1][y] == INF ||
			dis[x][y + 1] == INF ||
			dis[x][y - 1] == INF) {
 
			for (int i = 0; i < 4; i++) {
				vx = x + tmp[i][0];
				vy = y + tmp[i][1];
				if (dis[vx][vy] == INF) {
					dis[vx][vy] = getDis(vx, vy) + 1;
					q.push(point{ vx,vy });
				}
			}
		}
	}
	int x, y;
	long long p;
	for (int i = 1; i <= t; i++) {
		scanf("%d%d%lld", &x, &y, &p);
		if (dis[x][y] == INF) { 
			printf("%d\n", a[x][y]); 
			continue; 
		}
		if (dis[x][y] >= p)
			printf("%d\n", (a[x][y]));
		else
			printf("%d\n", (a[x][y])^int(abs(p - dis[x][y])%2));
	}
 
    return 0;
}

```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2000}$
---
### 解题思路：

任意一个有相邻的相同颜色的色块一定是不断在 $0$ 和 $1$ 之间振动的，只有出现 $0$ 和 $1$ 相间的情况时在会停滞。

但是只要出现振动最终一定能使得整个矩阵进入振动，只需要求出每一个位置是从什么时候开始振动的就行了，最后的结果可以用一开始的值，开始振动的时间和要求的时间直接计算出来。

每一次振动都会使得一个色块周围的未进入振动的单元格进入振动，那么直接考虑用 $\text{BFS}$，一开始将所有的进入振动的色块加入，再逐渐拓展即可。



---
### 代码：

```cpp
#include<cstdio>
#include<queue>
using namespace std;
#define int long long
const int MAXN=1005;
int m[MAXN][MAXN],f[MAXN][MAXN],n,M,T,x,y,p;
queue <int> qx,qy;
int dx[10]={0,0,1,-1},dy[10]={1,-1,0,0};
char get(){
	char c=getchar();
	while(c=='\n'||c==' '||c=='\r')c=getchar();
	return c;
}
signed main(){
	scanf("%I64d%I64d%I64d",&n,&M,&T);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=M;j++){
		m[i][j]=1;
		if(get()=='0')m[i][j]=0;
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=M;j++){
		for(int l=0;l<=3;l++){
			if(i+dx[l]<=0||i+dx[l]>n||j+dy[l]<=0||j+dy[l]>M)continue;
			if(m[i][j]!=m[i+dx[l]][j+dy[l]])continue;
			f[i][j]=1;
		}
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=M;j++){
		if(f[i][j]){qx.push(i);qy.push(j);}
	}
	while(!qx.empty()){
		int i=qx.front(),j=qy.front();
		for(int l=0;l<=3;l++){
			if(i+dx[l]<=0||i+dx[l]>n||j+dy[l]<=0||j+dy[l]>M)continue;
			if(f[i+dx[l]][j+dy[l]]!=0)continue;
			f[i+dx[l]][j+dy[l]]=f[i][j]+1;
			qx.push(i+dx[l]);
			qy.push(j+dy[l]);
		}
		qx.pop();qy.pop();
	}
	while(T--){
		scanf("%I64d%I64d%I64d",&x,&y,&p);
		if(f[x][y]==0){
			printf("%I64d\n",m[x][y]);
			continue;
		}
		if(f[x][y]-1>=p){
			printf("%I64d\n",m[x][y]);
			continue;
		}
		if((p-f[x][y]+1)%2)printf("%I64d\n",m[x][y]^1);
		else printf("%I64d\n",m[x][y]);
	}
	return 0;
}
```


---


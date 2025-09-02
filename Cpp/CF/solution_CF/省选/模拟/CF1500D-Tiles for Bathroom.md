# Tiles for Bathroom

## 题目描述

Kostya is extremely busy: he is renovating his house! He needs to hand wallpaper, assemble furniture throw away trash.

Kostya is buying tiles for bathroom today. He is standing in front of a large square stand with tiles in a shop. The stand is a square of $ n \times n $ cells, each cell of which contains a small tile with color $ c_{i,\,j} $ . The shop sells tiles in packs: more specifically, you can only buy a subsquare of the initial square.

A subsquare is any square part of the stand, i. e. any set $ S(i_0, j_0, k) = \{c_{i,\,j}\ |\ i_0 \le i < i_0 + k, j_0 \le j < j_0 + k\} $ with $ 1 \le i_0, j_0 \le n - k + 1 $ .

Kostya still does not know how many tiles he needs, so he considers the subsquares of all possible sizes. He doesn't want his bathroom to be too colorful. Help Kostya to count for each $ k \le n $ the number of subsquares of size $ k \times k $ that have at most $ q $ different colors of tiles. Two subsquares are considered different if their location on the stand is different.

## 说明/提示

In the first example all colors are distinct. Kostya doesn't want the subsquare have more than $ 4 $ colors, so he can buy any subsquare of size $ 1 \times 1 $ or $ 2 \times 2 $ , but he can't buy a subsquare of size $ 3 \times 3 $ .

In the second example there are colors that appear multiple times. Because $ q = 8 $ , Kostya can buy any subsquare of size $ 1 \times 1 $ and $ 2 \times 2 $ , and any subsquare $ 3 \times 3 $ , because of such subsquare has $ 7 $ different colors. He can't buy the whole stand $ 4 \times 4 $ , because there are $ 9 $ colors.

## 样例 #1

### 输入

```
3 4
1 2 3
4 5 6
7 8 9```

### 输出

```
9
4
0```

## 样例 #2

### 输入

```
4 8
1 2 3 4
5 6 7 8
9 1 2 3
4 5 6 7```

### 输出

```
16
9
4
0```

# 题解

## 作者：xcyle (赞：11)

感觉比C简单

---
考虑设 $f_{i,j}$ 表示以 $(i,j)$ 为右下角最大的合法正方形

那么显然有： $f_{i,j}\le min(f_{i-1,j},f_{i-1,j-1},f_{i,j-1})+1$

考虑记录每个位置向左，向上以及向左上的前 $10$ 种颜色，第 $k$ 个设为 $left_{i,j,k},up_{i,j,k},color_{i,j,k}$

前两个数组的转移都非常简单，每次最多把一个元素弹出去

第三个数组的转移考虑将 $left_{i,j-1},up_{i-1,j},color_{i-1,j-1}$ 视为三个队列，每次从堆头选出最小的一个放进 $color{i,j}$ 的队尾，模拟即可

时间复杂度 $O(10\times n ^2)$，常数很大但能过

[提交记录](https://codeforces.com/contest/1500/submission/110441790)

---

## 作者：约瑟夫用脑玩 (赞：8)

直接对于每个 $k$ 计数的话肯定 $O(n^3)$ 起步，但我们发现一个事实就是一个大正方形框住的每个小正方形都一定合法。

但这道题是计数，为了不重不漏，我们在每个正方形的右上角的那个点处统计它。

容易发现对于每个右上角我们只用找到它能满足条件的最大的正方形即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/s5q3fjk0.png?x-oss-process=image/resize,m_lfit,h_170,w_125)

如上图，我们相当于向外每一层，也就是图中红色的一层一层的，累加颜色。

直到去重后颜色都达到 $q+1$，说明已经超了，于是我们只用想办法按层为关键字排序后取前 $q+1$ 种颜色。

但是我们要对每一个右上角求，每次重新求的话要 $O(n^2)$ 血亏，于是就可以注意到它和左下一个作为右上角的点有很多重复的地方。

![](https://cdn.luogu.com.cn/upload/image_hosting/tnlfxeo6.png?x-oss-process=image/resize,m_lfit,h_170,w_125)

于是我们在求红色点时利用左下的黑色点求出来的前 $q+1$ 个颜色的位置，把新可能加入的颜色，也就是黄色的线段处扔进来更新。

显然只用保留 $O(q)$ 个，同时每次只用加入 $O(q)$ 个，所有合并去重并排序时可以做到 $O(q)$，故复杂度为 $O(n^2q)$。

细节：

- 如果要做到更严格的 $O(q)$ 合并，应该用类似归并的办法往里丢。

  但你发现是上次的红色和这次的两段黄色，总共三段做归并，比较麻烦。
  
  所有直接用一个堆或者直接 sort 一下，$\log 30$ 也不大（？）。
  
- 注意是不超过 $q$ 种，应该是在 $q+1$ 前的位置停下。

- 注意正方形不能超出边界，因为实际实现的时候可能顶到边界的时候还没超过 $q$ 种，于是把超出的也算进来了。

  记得顺便把左下总共都不满 $q$ 种颜色情况的处理了。

- 不用怎么注意常数，随便过（每个点 4s+ 的人这么说）。

  但是每次做合并的时候一定记得是 $O(q)$ 的复杂度，不能全局清空，复杂度挂了别来找我。

- 后缀和大家都会吧，那就完了。

[代码](https://www.luogu.com.cn/paste/8bu2r1z1)

---

## 作者：Maverik (赞：4)

##### Statement

​	给定一个 $n\times n$ 的正方形和正整数 $q$，求对于所有正整数 $k\le n$，有多少个 $k\times k$ 的子正方形中所含元素种数不超过 $q$。$n\le1500,q\le10$。

##### Solution

​	答案是单调的，因为一个正方形合法，其内部任意正方形也合法，考虑在右下角统计答案，相当于对每个右下角，找最小的左上角，满足两点构成的正方形内颜色数不超过 $k$。注意到 $q$ 很小，容易观察到相邻正方形间是有继承关系的，继承的信息是 $O(q)$ 的，考虑继承答案。由于贡献难以扣掉，考虑 $(i,j)$ 对 $(i-1,j-1)$ 的正方形的继承，合法颜色数是 $O(q)$ 的，对于每种颜色只关心相对于 $(i,j)$ 层数最小的位置，维护这些位置，不合法就弹掉层数最大的一层。另外还需要考虑第 $i$ 行与第 $j$ 列的贡献，这与前文大同小异，复杂度 $O(n^2q\log q)$。

##### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int maxn=1.5e3+10,inf=0x3f3f3f3f;
int n,a[maxn][maxn],q;
vector<pii>f[2][maxn],tmp,lin[maxn],row[maxn];
int buc[maxn*maxn],ans[maxn],res[maxn][maxn];
inline void solve()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>a[i][j];
    memset(buc,0x3f,sizeof(buc));
    for(int i=1;i<=n;i++)
    {
        for(int j=1,flag=0;j<=n;j++,flag=0)
        {
            row[j]=row[j-1];
            for(auto &[dis,c]:row[j]) dis++;
            for(auto &[dis,c]:row[j]) if(c==a[i][j]) dis=0,flag=1;
            if(!flag) row[j].push_back({0,a[i][j]}); 
            sort(row[j].begin(),row[j].end());
            while(row[j].size()>q+1) row[j].pop_back();            
        }
        for(int j=1,flag=0;j<=n;j++,flag=0)
        {
            for(auto &[dis,c]:lin[j]) dis++;
            for(auto &[dis,c]:lin[j]) if(c==a[i][j]) dis=0,flag=true;
            if(!flag) lin[j].push_back({0,a[i][j]}); 
            sort(lin[j].begin(),lin[j].end());
            while(lin[j].size()>q+1) lin[j].pop_back();
        }
        int cur=(i&1),pre=cur^1;
        for(int j=1,mx;j<=n;j++)
        {
            tmp.clear();
            mx=res[i-1][j-1]+1; f[cur][j].clear();
            for(auto [dis,c]:f[pre][j-1]) tmp.push_back({dis+1,c});
            for(auto [dis,c]:row[j]) if(dis<mx) tmp.push_back({dis,c});
            for(auto [dis,c]:lin[j]) if(dis<mx) tmp.push_back({dis,c});
            for(auto [dis,c]:tmp) buc[c]=min(buc[c],dis);
            for(auto [dis,c]:tmp) if(buc[c]!=inf) f[cur][j].push_back({buc[c],c}),buc[c]=inf;
            sort(f[cur][j].begin(),f[cur][j].end());
            if(f[cur][j].size()>q) res[i][j]=f[cur][j][q].first; else res[i][j]=mx;
            ans[res[i][j]]++; pii lst={0,0};
            while(f[cur][j].back().first>res[i][j]-1) lst=f[cur][j].back(),f[cur][j].pop_back(); 
            if(lst.second) f[cur][j].push_back(lst);
        }
    }
    for(int i=n-1;i>=1;i--) ans[i]+=ans[i+1];
    for(int i=1;i<=n;i++) cout<<ans[i]<<'\n';
}
signed main(){ios::sync_with_stdio(false);cin.tie(NULL);solve();}
```

---

## 作者：Genius_Star (赞：3)

### 思路：

考虑将每个权值随机映射到 $[1, w]$ 中，然后令其权值为 $2^{w}$，则一段区间的颜色数量应该 $\ge$ 这个区间权值的或中 $1$ 的个数。

根据这个思想，使用到本题，使用二维 ST 表维护以 $(x, y)$ 为左上角，边长为 $2^k$ 的正方形的所有权值的或。

然后考虑动态规划，设 $dp_{i, j}$ 表示使得以 $(i, j)$ 为左上角，使得满足条件的最大边长，显然 $dp_{i + 1, j + 1}$ 相当于 $dp_{i, j}$ 肯定是不减的，所以跑指针判断即可，由于这样的斜线只有 $n$ 个，所以复杂度是 $O(n^2)$ 的。

故总时间复杂度为 $O(T n^2 \log n)$，其中 $T$ 是我们随机映射的次数。

设 $k(k > q)$ 这个子矩阵的权值个数，映射到 $[1, w]$ 中，则发生错判的概率为：

$$\frac{\sum\limits_{i = 0}^q \binom{w}{i} \sum\limits_{j = 0}^i (-1)^j \binom{i}{j} (i - j)^k}{w^k}$$

这个式子最小是 $k = q + 1$ 时，当 $q = 10, w = 63$ 时约为 $0.6$。

进行 $T$ 次判断，全部错判的概率为：

$$\left( \frac{\sum\limits_{i = 0}^q \binom{w}{i} \sum\limits_{j = 0}^i (-1)^j \binom{i}{j} (i - j)^k}{w^k} \right)^T$$

其最小值是 $(0.6)^T$，令 $T = 35$ 即可（因为大部分数据 $k$ 应该都是大于 $q$ 很多的）。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 1505, M = 13, INF = INT_MAX;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
mt19937 R(time(0));
int T = 35, n, q;
int lg[N], s[N], id[N * N];
int a[N][N], dp[N][N];
ll F[M][N][N];
inline int ask(int x, int y, int len){
	int k = lg[len];
	ll t = F[k][x][y] | F[k][x + len - (1 << k)][y] | F[k][x][y + len - (1 << k)] | F[k][x + len - (1 << k)][y + len - (1 << k)];
	return __builtin_popcount(t >> 31) + __builtin_popcount(t & INF);
}
bool End;
int main(){
	lg[0] = -1;
	n = read(), q = read();
	for(int i = 1; i <= n; ++i){
		lg[i] = lg[i >> 1] + 1;
		for(int j = 1; j <= n; ++j){
			a[i][j] = read();
			dp[i][j] = n - max(i, j) + 1;
		}
	}
	while(T--){
		for(int i = 1; i <= n * n; ++i)
		  id[i] = R() % 63;
		for(int i = 1; i <= n; ++i)
		  for(int j = 1; j <= n; ++j)
		    F[0][i][j] = 1ll << id[a[i][j]];
		for(int k = 1; k < M; ++k)
		  for(int i = 1; i + (1 << k) - 1 <= n; ++i)
		    for(int j = 1; j + (1 << k) - 1 <= n; ++j)
		      F[k][i][j] = F[k - 1][i][j] | F[k - 1][i + (1 << (k - 1))][j] | F[k - 1][i][j + (1 << (k - 1))] | F[k - 1][i + (1 << (k - 1))][j + (1 << (k - 1))];
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= n; ++j){
				int p = max(dp[i - 1][j - 1] - 1, 0);
				while(p + 1 <= dp[i][j] && ask(i, j, p + 1) <= q)
				 ++p;
				dp[i][j] = min(dp[i][j], p);
			}
		}
	}
	for(int i = 1; i <= n; ++i)
	  for(int j = 1; j <= n; ++j)
	    ++s[dp[i][j]];
	for(int i = n; i >= 1; --i)
	  s[i] += s[i + 1];
	for(int i = 1; i <= n; ++i){
		write(s[i]);
		putchar('\n');
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

### 致谢：

感谢 [@Neil_Qian](https://www.luogu.com.cn/user/367359) 想到了此做法并与我分享，让我们膜拜他。

---

## 作者：_maze (赞：3)

前置知识：切比雪夫距离。如果你还不知道这个知识，请[点这里](https://www.cnblogs.com/closureshop/p/17141025.html)

也不是一定要会，毕竟我们在这道题里只要一个定义就行。



------------

考虑从以每个点为右下角进行枚举，算出此时满足条件的最长边长。我们把合法条件转化一下可以得出：

只有在正方形中，除了当前点的颜色，只有 $q - 1$ 种不同的颜色可以存在。那么最短的非法边长就是除当前点颜色外第 $q$ 种颜色被算入的最小边长。其减一就是最长合法边长。

现在的问题变为，如何判断一种颜色在边长增加到什么时候时会被计算。设右下角的点 $a$ 坐标为 $(x1, y1)$，要求的点 $b$ 坐标为 $(x2,y2)$，那么当正方形边长为 $|x1-x2|+|y1-y2|$ 时该点会首次被计算入颜色种类中，因为要把横纵坐标都囊括到其中。我们发现这就是切比雪夫距离。

因此，我们维护出每个点切比雪夫距离前 $k$ 小的颜色，这个可以通过左，上，左上三个方向进行转移。暴力即可。复杂度为 $O(n^2 q \log q)$。实际上并没有这么大。

```cpp
#include<bits/stdc++.h>
#define forp(i, a, b) for(int i = (a);i <= (b);i ++)
#define formar(i, j, n) forp(i, 1, n) forp(j, 1, n)
using namespace std;
const int maxn = 1505;
int n, q;
int col[maxn][maxn];
void read(){
	cin >> n >> q;
	formar(i, j, n) cin >> col[i][j];
}
struct point{ int x, y, d; };
int d(point a, point b){ return max(abs(a.x - b.x), abs(a.y - b.y)) + 1; }
vector<point> qie[maxn][maxn];
int ill[maxn][maxn];
bool ton[maxn * maxn];
point Q[40];
#define pb push_back
int cha[maxn];
void work(){
	formar(i, j, n){
		ill[i][j] = 1919810;
		int cnt = 0;point u = point{i, j, 1};
		Q[++ cnt] = u;
		if(i > 1) for(auto I : qie[i - 1][j]) Q[++ cnt] = point{I.x, I.y, d(I, u)};
		if(j > 1) for(auto I : qie[i][j - 1]) Q[++ cnt] = point{I.x, I.y, d(I, u)};
		if(i > 1 && j > 1) for(auto I : qie[i - 1][j - 1]) Q[++ cnt] = point{I.x, I.y, d(I, u)};
		sort(Q + 1, Q + cnt + 1, [](point a, point b){ return a.d < b.d; });
		int P = 0;
		point *p = &Q[1];
		forp(w, 1, cnt){
			if(ton[col[p->x][p->y]] == 1){ p ++;continue; }
			ton[col[p->x][p->y]] = 1;
			qie[i][j].pb(*p);
			P ++;if(P == q + 1){ ill[i][j] = p->d - 1;break; }
			p ++;
		}
		ill[i][j] = min(ill[i][j], min(i, j));
		p = &Q[1];
		forp(w, 1, cnt) ton[col[p->x][p->y]] = 0, p ++;
	}
	formar(i, j, n){
		cha[0] ++;
		cha[ill[i][j] + 1] --;
	}
	forp(i, 1, n) cha[i] += cha[i - 1];
	forp(i, 1, n) cout << cha[i] << endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	read();
	work();
	return 0;
}
```


---

## 作者：kkxacj (赞：2)

#### 思路

一个很显然的是我们希望对于每个端点求一个最大的长度 $len$ 使得这个正方形合法，这样对于左上端点为此的正方形长度 $i \le len$ 都是可行的。

考虑两个有交矩形的合并，它们最终的结果和两个矩阵并集的所含元素种数是一样的，让人联想到 $\verb!st!$ 表，我们预处理所有边长为 $2^i$ 次方的正方形矩阵，这样**对于任意一个正方形一定可以被另外四个正方形合并得到**，由于 $q$ 的限制，每个正方形最多 $q+1$ 种颜色，$q+1$ 代表不合法。

具体做法就是对于每个端点二分一个长度然后判一下即可，复杂度 $O(n^2q\log_{2}{n})$。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf1) + fread(buf1, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf1[1 << 23], *p1 = buf1, *p2 = buf1, ubuf[1 << 23], *u = ubuf;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 1510;
int n,q,a[N][N],ans[N],o,lg[N],b[N],l[N][N],r[N][N][15],sum,t[N*N*14],cnt,L,R,mid,cnt1;
int v[N*N];
//l_{i,j} 端点为(i,j)时的开头，我给每个端点分配了一段空间
//r_{i,j,z} 端点为(i,j)，正方形为2^z时，会有几种颜色 
//显然r_{i,j,z}会继承r_{i,j,z-1}，所以可以共用空间 
inline void solve(int L,int R,int Z,int x,int y,int z)
{
	for(int i = l[x][y];i <= r[x][y][z];i++)
		if(v[t[i]] != cnt)//这样不用清空 
		{
			v[t[i]] = cnt;
			if(r[L][R][Z]-l[L][R] >= q) return;//本来是...+1>q，转化得到，本来就>了就不需要加了，加不加都一样 
			t[++r[L][R][Z]] = t[i];
		}
}
inline void solve1(int L,int R,int x,int y,int z)
{
	for(int i = l[x][y];i <= r[x][y][z];i++)
		if(v[t[i]] != cnt)
		{
			v[t[i]] = cnt;
			if(cnt1-l[L][R] >= q) return;
			++cnt1;
		}
}
signed main()
{
//	freopen("square3.in","r",stdin);
//	freopen("square.out","w",stdout);
	read(n),read(q); sum = 0; b[0] = 1;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++)
		{
			read(a[i][j]),l[i][j] = sum,r[i][j][0] = sum-1,t[++r[i][j][0]] = a[i][j];
			for(int z = 1;z <= 13;z++) r[i][j][z] = sum-1;
			sum += 13;//分配空间 
		}
	for(int i = 2;i <= n;i++) lg[i] = lg[i/2]+1;
	for(int i = 1;i <= 13;i++) b[i] = b[i-1]*2;
	for(int i = 1;i <= 13;i++)
	{
		o = (n-b[i]+1);
		for(int j = 1;j <= o;j++)
			for(int z = 1;z <= o;z++)//预处理 
			{
				cnt++;
				solve(j,z,i,j,z,i-1);
				solve(j,z,i,j,z+b[i-1],i-1);
				solve(j,z,i,j+b[i-1],z,i-1);
				solve(j,z,i,j+b[i-1],z+b[i-1],i-1);
			}
	}
	for(int j = 1;j <= n;j++)
		for(int z = 1;z <= n;z++)
		{
			L = 1,R = n-max(j,z)+1; sum = 0;
			while(L <= R)
			{
				mid = ((L+R)>>1);
				cnt1 = l[j][z]-1; cnt++;
				solve1(j,z,j,z,lg[mid]);
				if(cnt1-l[j][z] < q) solve1(j,z,j,z+mid-b[lg[mid]],lg[mid]);
				if(cnt1-l[j][z] < q) solve1(j,z,j+mid-b[lg[mid]],z,lg[mid]);
				if(cnt1-l[j][z] < q) solve1(j,z,j+mid-b[lg[mid]],z+mid-b[lg[mid]],lg[mid]);
				if(cnt1-l[j][z] >= q) R = mid-1;//同理转化 
				else sum = mid,L = mid+1;
			}
			ans[1]++,ans[sum+1]--; //差分 
		}
	for(int i = 1;i <= n;i++) ans[i] += ans[i-1],print(ans[i]),pc('\n');
	flush();
	return 0;
}
```

---

## 作者：jxy2011 (赞：2)

*2900放mns t1???，哦我场切了啊，那没事了（）
#
我们考虑对每个点 $(x,y)$，计算以它作为右下角，正方形的边长最大可以是多少。

事实上，只需要维护每种颜色的点（且要在 $(x,y)$ 左上方）离 $(x,y)$ 切比雪夫距离的最小值，那 $(x,y)$ 为右下角时，最大边长也就是这些最小值中第 $q+1$ 小的。（这里不用 $-1$ 的原因是因为切比雪夫定理定义的是差，但是题面中边长定义的是差 $+1$）。

于是我们考虑对每个点维护距离它距离前 $q+1$ 小的位置，更具体地，可以注意到，可以对 $(x,y)$ 这个点造成贡献的，当且仅当它在 $(x-1,y-1)$，$(x-1,y)$，$(x,y-1)$ 的前 $q+1$ 小的位置出现过，这个证明不难。

那这个题就非常简单了，对每个点都维护一个 `vector` 记录前 $q+1$ 小的位置，然后计算一个点的时候将它左，上，左上 $3$ 个点的 `vector` 合并然后再排序（这里其实是不必要的，可以不排序的，但是我懒了qwq）找出前 $q+1$ 小的，当然这里还要求颜色不同，开个数组记录即可。

时间复杂度 $\mathcal O(n^2q\log{q})$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1510
vector <pair<int,int>> g[N][N];
vector <pair<int,pair<int,int>>> s;
bool c[N*N];
int a[N][N],box[N];
inline int d(pair <int,int> p1,pair <int,int> p2)
{
	return max(abs(p1.first-p2.first),abs(p1.second-p2.second));
}
inline int col(pair <int,int> x)
{
	return a[x.first][x.second];
}
int main ()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,t;
	cin>>n>>t;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			s.clear();
			pair <int,int> id=make_pair(i,j);
			s.push_back(make_pair(0,id));
			for(auto x:g[i-1][j-1]) s.push_back(make_pair(d(x,id),x));
			for(auto x:g[i][j-1]) s.push_back(make_pair(d(x,id),x));
			for(auto x:g[i-1][j]) s.push_back(make_pair(d(x,id),x));
			sort(s.begin(),s.end());
			int pos=0;
			for(auto x:s)
			{
				if(pos>t) break;
				auto y=x.second;
				if(c[col(y)]==0)
				{
					g[i][j].push_back(y);
					pos++;
					c[col(y)]=1;
				}
			}
			for(auto x:g[i][j]) c[col(x)]=0;
			int ans=min(i,j);
			if(g[i][j].size()>t) ans=min(ans,d(g[i][j].back(),id));
			box[ans]++;
		}
	}
	for(int i=n;i>=1;i--) box[i]+=box[i+1];
	for(int i=1;i<=n;i++) cout<<box[i]<<'\n';
	return 0;
}
```

---

## 作者：Polarisx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1500D)。

## 思路

首先容易想到对每个点 $(i,j)$ 求出以该点为右下角且颜色数不超过 $q$ 矩阵长度的最大值 $opt_{i,j}$，把这些值存到数组里做一遍后缀和即可得到答案。

第一眼的想法是，一行 $opt_{i,j}$ 的变化量为 $\mathcal O(n)$，每次更新判断是否比当前维护的矩阵多颜色，颜色最多更新 $\mathcal O(q)$ 次，这样应该能做到 $\mathcal O(n^2q\log n)$，但是空间开销太大会喜提 MLE 0 pts。

考虑另一种方式，对每个点 $(i,j)$ 维护出距离 $(i,j)$ 在其左上方且最小的 $q+1$ 种不同颜色点的位置集合（这里的距离是切比雪夫距离），假设为 $p_{i,j}$，然后 $p_{i,j}$ 可以由 $p_{i-1,j-1},p_{i-1,j},p_{i,j-1}$ 这三个集合取前 $q+1$ 小得到，直接做的时间复杂度是 $\mathcal O(n^2q\log q)$，代码很短。

二维 `vector` 很慢，滚动才能过。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=1505;
int n,q;
int a[Maxn][Maxn];

struct node{int x,y;};
vector<node>c[2][Maxn];
int ans[Maxn];
bool cs[Maxn*Maxn];

inline int dis(node x,node y){
	return max(abs(x.x-y.x),abs(y.y-x.y));
}
inline int solve(node t,vector<node>&vec){
	sort(vec.begin(),vec.end(),[t](node u,node v){
		return dis(u,t)<dis(v,t);
	});
	vector<node>nw;
	for(auto i:vec){
		if(!cs[a[i.x][i.y]]){
			nw.emplace_back(i);
			if(nw.size()>q) break;
		}
		cs[a[i.x][i.y]]=1;
	}
	for(auto i:vec) cs[a[i.x][i.y]]=0;
	vec=nw;
	if(nw.size()>q) return min(dis(t,nw.back()),min(t.x,t.y));
	else return min(t.x,t.y);
}

int main(){
//	freopen("square6.in","r",stdin);
//	freopen("square.out","w",stdout);

	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			int o=(i&1);
			c[o][j].resize(0);
			for(auto k:c[o^1][j]) c[o][j].emplace_back(k);
			for(auto k:c[o][j-1]) c[o][j].emplace_back(k);
			for(auto k:c[o^1][j-1]) c[o][j].emplace_back(k);
			c[o][j].emplace_back((node){i,j});
			ans[solve((node){i,j},c[o][j])]++;
			
		}
	for(int i=n;i;i--) ans[i]+=ans[i+1];
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]);

	return 0;
}
```

---

## 作者：Neil_Qian (赞：1)

# CF1500D Tiles for Bathroom 题解

来发不太一样的。

注意到 $q\le 10$ 但值域很大，考虑 color-coding。每次将 $\forall i\in [1,n^2]$ 映射到 $[1,K]$ 中的一个随机值，只要 $K$ 比较小，比如取 $60$，那么求颜色的并就可以简单地写成两个整数的按位或的结果。然后用 ST 表即可求出一个矩形的颜色并。

一次的正确率至少为 $\frac{K\times (K-1)\times \dots \times (K-q)}{K^{q+1}}$。

将上述过程做 $T$ 次，则时间复杂度为 $O(Tn^2\log n)$。参考数据：$T=35,K=60$。或者可以卡时。

可能需要不少卡常。

```cpp
#include<bits/stdc++.h>
#pragma GCC diagnostic error "-std=c++11"
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
using namespace std;using ll=long long;
char buf[5000000],obuf[5000000],*p1,*p2,*p3=obuf;
#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,5000000,stdin),p1==p2)?EOF:*p1++)
#define flush() (fwrite(obuf,1,p3-obuf,stdout),p3=obuf)
#define pc(ch) (p3==obuf+5000000&&flush(),*p3++=(ch))
inline void read(int &x){
	x=0;bool f=0;char ch=nc();
	while(ch<'0'||ch>'9')f|=(ch=='-'),ch=nc();
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=nc();
	x=(f?-x:x);
}
inline void write(int x){
	if(!x){pc('0');return;}
	if(x<0)pc('-'),x=-x;
	char c[22];int sz=0;
	while(x)c[++sz]=x%10,x/=10;
	while(sz)pc(c[sz--]^48);
}
const int N=1502;int n,q,C,a[N][N],mp[N*N],b[N][N],cnt,ans[N][N],res[N];ll f[13][N][N];
mt19937 rnd(time(0)^(*new unsigned long long));const ll R=(1LL<<32)-1;
inline int calc(int i,int j,int k){
	int k1=__lg(k);ll t=f[k1][i][j]|f[k1][i+k-(1<<k1)][j]|f[k1][i][j+k-(1<<k1)]|f[k1][i+k-(1<<k1)][j+k-(1<<k1)];
	return __builtin_popcount(t>>32)+__builtin_popcount(t&R);
}
int main(){
	read(n),read(q),C=__lg(n);double T=clock();
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)read(a[i][j]),ans[i][j]=n-max(i,j)+1;
	while((clock()-T)/CLOCKS_PER_SEC<3.7){
		for(int i=1;i<=n*n;i++)mp[i]=rnd()%62;
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)b[i][j]=mp[a[i][j]],f[0][i][j]=(1LL<<b[i][j]);
		for(int k=1;k<=C;k++)for(int i=1;i+(1<<k)-1<=n;i++)for(int j=1;j+(1<<k)-1<=n;j++)
			f[k][i][j]=f[k-1][i][j]|f[k-1][i][j+(1<<(k-1))]|f[k-1][i+(1<<(k-1))][j]|f[k-1][i+(1<<(k-1))][j+(1<<(k-1))];
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
			int L=max(ans[i-1][j-1]-1,0);
			while(L+1<=ans[i][j]&&calc(i,j,L+1)<=q)L++;
			ans[i][j]=min(ans[i][j],L);
		}
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)res[ans[i][j]]++;
	for(int i=n;i>=1;i--)res[i]+=res[i+1];
	for(int i=1;i<=n;i++)write(res[i]),pc('\n');
	return flush(),0;
}
```

---

## 作者：lsj2009 (赞：1)

### Solution

这个题就感觉很怪……做的时候确实没想到，但是看了题解之后又觉得属实没有 2900，可能是一种 trick 题吧（？

考虑以 $(i,j)$ 为右下角时，$k$ 最大为多少；对于一个点 $(x,y)$，当其在以 $(i,j)$ 为右端点的正方形内部时，当且仅当 $\max\{i-x,j-y\}+1\le k$，其中等式左边被称作切比雪夫距离。

则题目等价于询问距离 $(i,j)$ 前 $q+1$ 个颜色不同且切比雪夫距离最小的点的切比雪夫距离 $-1$。

然后就是经典 trick（？，考虑到距离 $(i,j)$ 前 $q+1$ 小的点，必然由距离 $(i-1,j),(i,j-1),(i-1,j-1)$ 前 $q+1$ 小的几个点组成，我们对于每个节点维护一个长为 $q+1$ 的 ``vector``，然后排个序取前 $q+1$ 小，复杂度 $\Theta(n^2q\log{q})$，当然可以用 P2827 的 trick 把 $\log$ 去掉，但是没有意义。

需要注意的是，``vector`` 的初始空间非常大，开 $n\times n$ 个 ``vector`` 直接喜提 MLE，哪怕实时释放空间也过不去，所以需要滚一手。

### Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=1501;
vector<PII> vec[2][N];
int a[N][N],n,k,x,y;
bool color[N*N];
int dis(int xa,int ya,int xb,int yb) {
    return max(abs(xb-xa),abs(yb-ya))+1;
}
int merge(int _x,int _y,vector<PII>& vec) {
	x=_x; y=_y;
    sort(vec.begin(),vec.end(),[](const PII &a,const PII &b) {
		int xa=a.first,ya=a.second,xb=b.first,yb=b.second;
		return dis(x,y,xa,ya)<dis(x,y,xb,yb);
	});
    vector<PII> res;
	int ans=INF;
    for(auto v:vec) {
		int tx=v.first,ty=v.second;
        int w=a[tx][ty];
        if(!color[w]) {
            color[w]=true;
            res.push_back(v);            
			if((int)res.size()==k+1) {
				ans=dis(x,y,tx,ty)-1;
				break;
			}
        }
    }
    vec=res;
    for(auto x:vec)
        color[a[x.first][x.second]]=false;
	return ans;
}
ll ans[N];
signed main() {
    scanf("%d%d",&n,&k);
    rep(i,1,n) {
        rep(j,1,n)
            scanf("%d",&a[i][j]);
    }
    rep(i,1,n) {
        rep(j,1,n) {
			vec[i&1][j].clear();
            vec[i&1][j].push_back({i,j});
            if(i) {
                for(auto x:vec[(i-1)&1][j])
                    vec[i&1][j].push_back(x);
            }
            if(j) {
                for(auto x:vec[i&1][j-1])
                    vec[i&1][j].push_back(x);
            }
            if(i&&j) {
                for(auto x:vec[(i-1)&1][j-1])
                    vec[i&1][j].push_back(x);
            }
            int val=merge(i,j,vec[i&1][j]);
            ++ans[min({val,i,j})];
        }
    }
    per(i,n-1,1)
        ans[i]+=ans[i+1];
    rep(i,1,n)
        printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：丛雨 (赞：1)


题外话:考场上打的ST表，多个log所以T了==,后来才发现可以不用ST表

---
我们可以求出每个点可以向右下方拓展出的满足条件的最长边长正方形，然后统计答案

关键就是如何得到最长正方形

我们考虑得到点x右下角,离点x按**最短**切比雪夫距离排序的前$q+1$种颜色,则最长正方形就是点x到第$q+1$种颜色的最短切比雪夫距离-1

直接维护前$q+1$切比雪夫距离近的比较难，所以我们考虑转换为曼哈顿距离

这时我们便可以从右下往左上进行求解,但需要注意的是在原图中为右下角，而在转换后的图中则是$225^\circ$到$315^\circ$之间的点

时间复杂度$O(n^2q)$

```cpp
#include<bits/stdc++.h>
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;
	char k;
	bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
# define A pair<int,int>
int n,q,ans[3005];
bool vis[1505*1505];
struct B{
	vector<A>a;
	int s;
	B(int len=0){s=len;if(s)a.resize(s);}
	A& operator[](const unsigned int x){return a[x];}
	void resize(int len){s=len;a.resize(len);}
	void clear(){s=0;a.clear();}
	B& operator +=(B &x){
		B t(min(s+x.s,q+1));t.s=0;
		for(int i=0,j=0;(i<s||j<x.s)&&t.s<=q;){
			if(i<s&&(j>=x.s||a[i].first<=x[j].first))vis[a[i].second]=1,t[t.s++]=a[i];
			else vis[x[j].second]=1,t[t.s++]=x[j];
			while(i<s&&vis[a[i].second])++i;
			while(j<x.s&&vis[x[j].second])++j;
		}for(int i=0;i<t.s;++i)vis[t[i].second]=0;
		a=t.a;s=t.s;
		return *this;
	}
	void Up(){for(int i=0;i<s;++i)++a[i].first;}
	void Down(){for(int i=0;i<s;++i)--a[i].first;}
}a[3005][3005],d[2][3005];
int main(){
	n=read,q=read;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			a[i+j][i-j+n].resize(1);
			a[i+j][i-j+n][0]=make_pair(0,read);
		}
	int s=n*2;
	for(int i=s;i>1;--i){
		for(int j=1;j<s;++j)d[0][j].Up(),d[1][j]=d[0][j],d[1][j].Up();
		for(int j=s-1;j;--j){
			d[0][j]+=d[1][j-1];d[0][j]+=d[1][j+1];
			d[0][j]+=a[i][j];
			if(~(i^j^n)&1){
				int x=i+j-n>>1,y=i-j+n>>1;
				if(x<1||y<1||x>n||y>n)continue;
				if(d[0][j].s<=q)++ans[n-max(x,y)+1];
				else ++ans[min(n-max(x,y)+1,d[0][j][q].first/2)];
			}
		}
	}
	for(int i=n;i;--i)ans[i-1]+=ans[i];
	for(int i=1;i<=n;++i)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：鲤鱼江 (赞：0)

有点毒的题。

考虑求出以每个点为右下角的最大正方形大小，然后求一遍后缀和可以得到答案。

发现 $q\le 10$，肯定有说法，猜测和 $q$ 线性挂钩。

不难发现最大正方形大小是单调的，可以二分，但是好像没有比较平凡的数据结构可以优秀地做到静态查询，当然还有势能均摊之类的奇怪假做法。

那么究竟怎么做呢，我们预处理出三个数组 $up_{i,j}$,$lef_{i,j}$,$col_{i,j}$，注意我的代码中 $col_{i,j}$ 是分开存的，具体见代码。

$up_{i,j,k}$ 表示自己这一列的正上方最近的第 $k$ 个本质不同的数的位置，不难发现 $k$ 开到 $11$ 就够了。$lef_{i,j}$ 表示左边，$col_{i,j}$ 表示左上角离自己最近的，注意这里的距离指的是 $\max(\Delta x,\Delta y)$。

$up$ 和 $lef$ 可以拿一个双端队列扫一遍出来，拿处理 $up$ 举例：

```cpp
deque < int > d;
for(int i=1;i<=n;++i){
	d.clear();
	for(int j=1;j<=n;++j){
		if(d.empty()) d.emplace_back(j);
		else {
			int fg=0,siz=d.size();
			for(int &k:d) if(a[i][k]==a[i][j]){fg=1;k=j;break;}//由于是离自己最近的数，所以要修改
			if(!fg){
				if(d.size()==q+1) d.pop_front();//注意要处理 q+1 个。
				d.emplace_back(j);
			}else {
				for(int i=0;i<siz-1;++i) if(d[i]>d[i+1]) swap(d[i],d[i+1]);//我们时刻保证位置升序。
			}
		}
		int tmp=0;
		for(int k:d) lef[i][j][++tmp]=k;
	}
}
```

那么怎么处理出 $col_{i,j}$ 呢，我们拿出 $col_{i-1,j-1}$,$up_{i-1,j}$,$lef_{i,j-1}$，将它们归并起来即可，直接排序也不是不行，可能会比较卡常。

总时间复杂度 $O(n^2q)$，常数比较大，我的写法细节好像比较多。

```cpp
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define endl '\n'

using namespace std;
using namespace __gnu_pbds;

bool st;
const int N=2e3+10;
int a[N][N],n,q,res[N];
short up[N][N][13],lef[N][N][13],X[N][N][13],Y[N][N][13],vis[N*N];//可以开 short 空间小一点
deque < int > d;
bool ed;

//col 要存点坐标，分成了 X 和 Y 两个数组。

inline int Get(int a,int b,int id){return max(a-X[a-1][b-1][id],b-Y[a-1][b-1][id]);}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>q;for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) cin>>a[i][j];
	for(int i=1;i<=n;++i){
		d.clear();
		for(int j=1;j<=n;++j){
			if(d.empty()) d.emplace_back(j);
			else {
				int fg=0,siz=d.size();
				for(int &k:d) if(a[i][k]==a[i][j]){fg=1;k=j;break;}
				if(!fg){
					if(d.size()==q+1) d.pop_front();
					d.emplace_back(j);
				}else {
					for(int i=0;i<siz-1;++i) if(d[i]>d[i+1]) swap(d[i],d[i+1]);
				}
			}
			int tmp=0;
			for(int k:d) lef[i][j][++tmp]=k;
		}
	}
	for(int j=1;j<=n;++j){
		d.clear();
		for(int i=1;i<=n;++i){
			if(d.empty()) d.emplace_back(i);
			else {
				int fg=0,siz=d.size();
				for(int &k:d) if(a[k][j]==a[i][j]){k=i;fg=1;break;}
				if(!fg){
					if(d.size()==q+1) d.pop_front();
					d.emplace_back(i);
				}else {
					for(int i=0;i<siz-1;++i) if(d[i]>d[i+1]) swap(d[i],d[i+1]);
				}
			}
			int tmp=0;
			for(int k:d) up[i][j][++tmp]=k;
		}
	}//预处理
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			int x=1,y=1,z=1;
			while(up[i-1][j][x]) ++x;
			while(lef[i][j-1][y]) ++y;
			--x;--y;X[i][j][1]=i;Y[i][j][1]=j;
			vis[a[i][j]]=1;
			for(int k=2;k<=q+1;++k){
				int tmp=1e9;
				if(x) tmp=min(tmp,i-up[i-1][j][x]);
				if(y) tmp=min(tmp,j-lef[i][j-1][y]);
				if(X[i-1][j-1][z]) tmp=min(tmp,Get(i,j,z));
				if(x&&tmp==i-up[i-1][j][x]){X[i][j][k]=up[i-1][j][x--];Y[i][j][k]=j;}
				else if(y&&tmp==j-lef[i][j-1][y]){X[i][j][k]=i;Y[i][j][k]=lef[i][j-1][y--];}
				else if(X[i-1][j-1][z]&&tmp==Get(i,j,z)){X[i][j][k]=X[i-1][j-1][z];Y[i][j][k]=Y[i-1][j-1][z++];}
				else break;
				if(vis[a[X[i][j][k]][Y[i][j][k]]]){X[i][j][k]=Y[i][j][k]=0;--k;}
				vis[a[X[i][j][k]][Y[i][j][k]]]=1;
			}
			int qaq=1e9;
			if(X[i][j][q+1]) qaq=max(i-X[i][j][q+1],j-Y[i][j][q+1]);
			qaq=min(i,min(j,qaq));++res[qaq];
			for(int k=1;k<=q+1;++k) vis[a[X[i][j][k]][Y[i][j][k]]]=0;
//			cout<<i<<' '<<j<<endl;
//			for(int k=1;k<=q+1;++k) cout<<"----"<<X[i][j][k]<<' '<<Y[i][j][k]<<' '<<max(i-X[i][j][k],j-Y[i][j][k])<<endl;
		}
	}
	for(int i=n;i;--i) res[i]+=res[i+1];
	for(int i=1;i<=n;++i) cout<<res[i]<<endl;
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：0)

首先，对于一个固定的左上顶点来讲，满足条件的边长 $k$ 是可二分的，对于每一条斜线上的点，可以进行双指针。

双指针是，要加入/删除一行/一列种的某个区间（形象一点就是一“条”）的所有颜色，我们拿行举例：

对于每个点，维护它右边离它最近的 $q+1$ 种颜色即可，这个可以用链表 $O(n^2q)$ 预处理，是很基础的。

这样就可以精准定位到需要修改的颜色，现在要求每种颜色在某一行的区间出现次数。

这个很简单，每一个点记录它做为它的颜色在这一行是第几次出现，相当于把其他颜色扣掉再做一个重标号，这一部分是 $O(n^2)$ 的。

这样我们就可以做到 $O(q)$ 加入/删除一行的某个区间了，列是一样的，复杂度 $O(n^2q)$。

[代码](https://codeforces.com/contest/1500/submission/304511610)

---

## 作者：Komomo (赞：0)

> 本人没有具体实现过，算法正确性未知，如果假了我立即撤下。

提前预处理 $U_{x,y}, L_{x,y}$ 表示 $(x,y)$ 开始向上 / 向左在满足颜色数 $\le q$ 的条件下最长延伸长度。最终我们目的是统计出对于所有 $(x,y)$，以其为右下角的正方形个数。

枚举 $2n-1$ 条主对角线，每次对一条对角线上的格子双指针，支持往一个可重集加入 / 删除一段宽为 $1$ 的矩形内的元素，记其为 $(x,y,l,\texttt L/\texttt R, +/-)$，表示从 $(x,y)$ 开始向上 / 向左 $l$ 个位置加入集合或者删除，直接做时间复杂度为 $\mathcal O(n^3)$。

观察到进行适当的顺序处理，每次集合操作只会改变 $\le q + 1$ 种颜色，且最多只会操作 $\mathcal O(n)$ 次。再根据操作的单调性，如果按顺序处理每一条对角线，那么对于所有 $x$ 相同的操作，发现对于每个 $\texttt L/\texttt R, +/-$ 独立来看，操作内 $y$ 单调不增。

于是动态维护操作区间，对于不同的属性（$\texttt L/\texttt R, +/-$）开四个单调队列维护操作区间内颜色数和个数，时间复杂度 $\mathcal O(qn^2)$。

---

## 作者：Reunite (赞：0)

一个显然的想法是对于所有固定右下角的位置，求出向左上能达到的最大正方形。但是没有啥好用的数据结构快速矩形颜色查询，考虑利用 $q\le 10$ 的性质，这保证了我们如果只维护最近的 $q$ 个颜色，那么复杂度是可以接受的。

具体地，维护 $lf,up,cl$ 为 $(i,j)$ 向左，向上，向左上的最近 $q$ 个颜色的位置，每次根据邻点更新，$lf,up$ 的更新是显然地，对于 $cl$，也只需要把关键的颜色点拎出来 $O(q)$ 个，然后取重，取最近的 $q$ 个即可。

考虑 $cl$ 对 $(i,j)$ 的可达性限制 $lim_{i,j}$，如果把 $dis$ 相等的点缩起来，那显然是恰好超过 $q$ 的第一个点的距离减 $1$，然后这个 $lim_{i,j}$ 还要和邻点取 $\min$，否则会丢失信息。最后根据这个 $lim_{i,j}$ 差分一下即可。

复杂度 $O(n^2q \log q)$，用桶排可以去掉一个 $\log q$。细节有点多。

---

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define pi pair <int,int>
using namespace std;

int n,q;
int ans[1505];
int a[1505][1505];
int lim[1505][1505];
int lf[1505][1505][11];
int up[1505][1505][11];
pi cl[1505][1505][11];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

int main(){
	in(n),in(q);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) in(a[i][j]);
	for(int i=0;i<=n;i++) lim[0][i]=lim[i][0]=1e9;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int b[15],tt=0,kk=0;
			for(int k=1;k<=q&&lf[i][j-1][k];k++)
				if(a[i][j]!=a[i][lf[i][j-1][k]]) b[++tt]=lf[i][j-1][k];
			b[++tt]=j;
			for(int k=tt>q?2:1;k<=tt;k++) lf[i][j][++kk]=b[k];
			tt=kk=0;
			for(int k=1;k<=q&&up[i-1][j][k];k++)
				if(a[i][j]!=a[up[i-1][j][k]][j]) b[++tt]=up[i-1][j][k];
			b[++tt]=i;
			for(int k=tt>q?2:1;k<=tt;k++) up[i][j][++kk]=b[k];
			tt=kk=0;
			pi c[35],d[35];
			for(int k=1;k<=q&&lf[i][j-1][k];k++) c[++tt]={i,lf[i][j-1][k]};
			for(int k=1;k<=q&&up[i-1][j][k];k++) c[++tt]={up[i-1][j][k],j};
			for(int k=1;k<=q&&cl[i-1][j-1][k].first;k++) c[++tt]=cl[i-1][j-1][k];
			c[++tt]={i,j};
			sort(c+1,c+1+tt,[i,j](pi p,pi q){
				if(a[p.first][p.second]==a[q.first][q.second])
					return max(i-p.first,j-p.second)<max(i-q.first,j-q.second);
				return  a[p.first][p.second]<a[q.first][q.second];
			});
			for(int k=1;k<=tt;k++) if(a[c[k].first][c[k].second]!=a[c[k-1].first][c[k-1].second]) d[++kk]=c[k];
			sort(d+1,d+1+kk,[i,j](pi p,pi q){return max(i-p.first,j-p.second)<max(i-q.first,j-q.second);});
			tt=0;
			for(int k=1;k<=kk&&k<=q;k++) cl[i][j][++tt]=d[k];
			if(kk<=q) lim[i][j]=i;
			else{
				for(int k=1;k<=kk;k++){
					int r=k;
					while(max(i-d[k].first,j-d[k].second)==max(i-d[r].first,j-d[r].second)&&r<=kk) r++;
					r--;
					if(r>q){lim[i][j]=max(i-d[k].first,j-d[k].second);break;}
					k=r;
				}
			}
			lim[i][j]=min({lim[i][j],lim[i-1][j-1]+1,lim[i-1][j]+1,lim[i][j-1]+1});
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int d=min({i,j,lim[i][j]});
			ans[1]++;
			ans[d+1]--;
		}
	}
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]+=ans[i-1]);

	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

对于每个左上角求出最长延伸。

考虑倍增，设 $f_{i,j,k}$（一个集合）为以 $(i,j)$ 为左上角，$2^k\times2^k$ 的矩形包含的数的集合。如果 $|f_{i,j,k}|>q$，则只保留 $q+1$ 个数（也就是不合法）。预处理是 $O(n^2q\log n)$。

我们发现我们只需要知道有哪些数，不需要知道有多少数，也就是可重复计算。所以对于每个左上角，我们可以 $O(q\log n)$ 求出最长延伸。

事情看起来很完美，但是空间是 $O(n^2q\log n)$ 的。不过这也没关系，我们动态做倍增（也就是算完 $f_{i,j,k}$ 就不保留 $f_{i,j,k-1}$ 的信息），对于每个左上角位置找到第一个 $|f_{i,j,k}>q|$ 后，我们只需要用 $f_{x,y,k-1}$ 的信息就可以找出最长延伸，这样空间就是 $O(n^2q)$ 了。

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
using namespace std;
struct node{
	int p[11],tot;
};
int tag[3000005];
node merge(node x,node y){
	if(x.tot==11) return x;
	if(y.tot==11) return y;
	for(int i=1;i<=x.tot;i++) tag[x.p[i]]=1;
	for(int i=1;i<=y.tot;i++){
		if(!tag[y.p[i]]){
			x.tot++;
			if(x.tot==11){
				for(int i=1;i<=x.tot;i++) tag[x.p[i]]=0;
				return x;
			}
			x.p[x.tot]=y.p[i];
		}
		tag[y.p[i]]=1;
	}
	for(int i=1;i<=x.tot;i++) tag[x.p[i]]=0;
	return x;
}
node b[1505][1505],c[1505][1505];
int a[1505][1505],svd[1505][1505],pre[1505];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,q; cin>>n>>q;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) cin>>a[i][j];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			b[i][j].tot=1;
			b[i][j].p[1]=a[i][j];
		}
	}
	for(int k=1;k<=11;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				int i2=i+(1<<(k-1)),j2=j+(1<<(k-1));
				c[i][j]=b[i][j];
				if(i2<=n) c[i][j]=merge(c[i][j],b[i2][j]);
				if(j2<=n) c[i][j]=merge(c[i][j],b[i][j2]);
				if(i2<=n&&j2<=n) c[i][j]=merge(c[i][j],b[i2][j2]);
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(svd[i][j]) continue;
				if(c[i][j].tot>q||i+(1<<k)>n+1||j+(1<<k)>n+1){
					svd[i][j]=1;
					int ex=0;
					for(int l=k-2;l>=0;l--){
						int d=ex+(1<<l);
						if(i+(1<<(k-1))+d<=n+1&&j+(1<<(k-1))+d<=n+1){
							node now=merge(b[i][j],merge(merge(b[i+d][j],b[i][j+d]),b[i+d][j+d]));
							if(now.tot<=q){
								ex=d;
							}
						}
					}
					ex+=(1<<(k-1));
					pre[ex]++;
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				b[i][j]=c[i][j];
			}
		}
	}
	for(int i=n;i>=1;i--) pre[i]+=pre[i+1];
	for(int i=1;i<=n;i++) cout<<pre[i]<<"\n";
	return 0;
}
```

---


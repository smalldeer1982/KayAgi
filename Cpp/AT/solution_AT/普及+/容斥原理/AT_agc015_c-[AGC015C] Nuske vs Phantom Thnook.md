# [AGC015C] Nuske vs Phantom Thnook

## 题目描述

Nuske 现在有一个 $N\times M(N,M\le 2000)$ 的矩阵 $S$，若 $S_{i,j}=1$，那么该处为蓝色，否则为白色，保证所有蓝色格子构成的连通块都是树。

给出 $Q(Q\le 200000)$ 次询问, 每次询问一个子矩阵中蓝色连通块的个数。

## 样例 #1

### 输入

```
3 4 4
1101
0110
1101
1 1 3 4
1 1 3 1
2 2 3 4
1 2 2 4```

### 输出

```
3
2
2
2```

## 样例 #2

### 输入

```
5 5 6
11010
01110
10101
11101
01010
1 1 5 5
1 2 4 5
2 3 3 4
3 3 3 3
3 1 3 5
1 1 3 4```

### 输出

```
3
2
1
1
3
2```

# 题解

## 作者：Limit (赞：11)

# 题目大意

给出一个01矩阵,这个矩阵有一个特殊的性质: 对于任意两个 $1$ 之间最多只有 $1$ 条由 $1$ 构成的路径.每次询问给出一个矩形范围,查询在这个范围内的联通快个数.

# 分析

先从给出的性质出发,可以发现如果在所有相邻的 $1$ 之间连上一条边(双向边)以后这个性质就转化成了在这若干个 $1$ 所组成的图中不会出现环,在仔细思考一下,不会出现环,而且是双向边,这意味着什么?没错,这是一片森林(由很多[树](https://baike.baidu.com/item/树/2699484)组成),对于每一颗树就是一个联通快了,可以发现这既然是树,那么如果它被~~残忍地~~切开后它仍然是一颗树,于是对于矩阵查询并不会对于每个联通块都是一棵树这个性质产生影响,于是就很容易想到树有什么性质,其中有一个非常特殊的性质,一棵有 $N$ 个节点的树中有且只有 $N-1$ 条边,那么矩阵中的点的个数 $-$ 矩阵中相邻的 $1$ 所形成的边的个数 $=$ 矩阵中树的个数,至于计算部分,二维前缀和搞一下就好了,可以做到 $O(1)$ 查询.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i<=last;++i)
using namespace std;
const int maxN=2333;
int N,M,T;
int arr[maxN][maxN];
int sum[maxN][maxN];
//对于竖着的边和横着的边需要不同处理
int suml[maxN][maxN];
int sumr[maxN][maxN];
int main()
{
	scanf("%d%d%d",&N,&M,&T);
	char ch;
	REP(i,1,N)
	{
		REP(j,1,M)
		{
			cin>>ch;
			arr[i][j]=ch-'0';
			sum[i][j]=arr[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];//二维前缀,记录1出现的次数
			if(arr[i][j])
			{
				if(arr[i-1][j])//如果有竖着的边
				{
					suml[i][j]++;
				}
				if(arr[i][j-1])//如果有横着的边
				{
					sumr[i][j]++;
				}
			}
			//处理二维前缀
			suml[i][j]+=suml[i-1][j]+suml[i][j-1]-suml[i-1][j-1];
			sumr[i][j]+=sumr[i-1][j]+sumr[i][j-1]-sumr[i-1][j-1];
		}
	}
	int fx,fy,lx,ly,answer;
	REP(i,1,T)
	{
		scanf("%d%d%d%d",&fx,&fy,&lx,&ly);
		//按照公式计算
		answer=sum[lx][ly]-sum[lx][fy-1]-sum[fx-1][ly]+sum[fx-1][fy-1];
		//竖着的的边的数量与横着的边的数量计算方式略有不同,如果不能理解可以画一张图来帮助理解
		answer-=suml[lx][ly]+suml[fx][fy-1]-suml[lx][fy-1]-suml[fx][ly];
		answer-=sumr[lx][ly]+sumr[fx-1][fy]-sumr[lx][fy]-sumr[fx-1][ly];
		printf("%d\n",answer);
	}
	return 0;
}
```

---

## 作者：M_CI (赞：4)

### 题意简述

给定一个由 `0` 和 `1` 组成的矩阵，其中由 `1` 组成的连通块不存在环，即每两个 `1` 之间仅有 $1$ 条由 `1` 组成的路径，每次询问求一个给定的子矩阵中有多少个由 `1` 组成的连通块。

### 思路

因为这个矩阵中的由 `1` 组成的连通块都是树，所以可以将这个矩阵看做一个森林，而我们知道，一棵树的点数与边数之差为 $1$，所以一个森林中的点数与边数之差即为森林中树的数量。

我们再看每次询问，每次询问的子矩阵中，所有由 `1` 组成的连通块一定仍保持着树的形态，所以以上性质不变。

我们可以在输入时用类似前缀和的方法存点和边的数量，每次询问以 $O(1)$ 的复杂度回答。

注意这是有着树形态的连通块而非真正的一棵树，所以行内连边与列内连边需分开存。

### AC CODE

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,q,s[2010][2010][3];
char c[2010][2010];

int work (int x1,int y1,int x2,int y2) {
	return (s[x2][y2][0]-s[x1-1][y2][0]-s[x2][y1-1][0]+s[x1-1][y1-1][0])-
		   (s[x2][y2][1]-s[x1][y2][1]-s[x2][y1-1][1]+s[x1][y1-1][1])-
		   (s[x2][y2][2]-s[x1-1][y2][2]-s[x2][y1][2]+s[x1-1][y1][2]);
}

int main () {
	cin>> n>> m>> q;
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			cin>> c[i][j];
			s[i][j][0]=s[i-1][j][0]+s[i][j-1][0]-s[i-1][j-1][0]+(c[i][j]=='1');
			s[i][j][1]=s[i-1][j][1]+s[i][j-1][1]-s[i-1][j-1][1]+(c[i][j]=='1'&&c[i-1][j]=='1');
			s[i][j][2]=s[i-1][j][2]+s[i][j-1][2]-s[i-1][j-1][2]+(c[i][j]=='1'&&c[i][j-1]=='1');
		}
	}
	while (q--) {
		int x1,y1,x2,y2;
		cin>> x1>> y1>> x2>> y2;
		cout<< work (x1,y1,x2,y2)<< "\n";
	}
	return 0;
}
```

---

## 作者：cyffff (赞：4)

[$\text{Link}$](https://www.luogu.com.cn/problem/AT2381)
## 题意
给一个 $n\times m$ 的矩阵，有 $0$、$1$ 两种颜色，若相邻格子的颜色相同就连边，每个连通块都是树的形式，$Q$ 组询问 $\begin{bmatrix}(x_1,y_1)&\\&(x_2,y_2)\end{bmatrix}$ 这个子矩阵中有多少个连通块。

$1\le n,m\le 2000,1\le Q\le2\times10^5$
## 思路
这算是 $\text{AGC}$ 系列中非常简单的题了，我都能自己做出来（

首先题目问子矩阵构成的森林的树的个数，我们思考如何转化。

众所周知，树的点数 $p$ 等于边数 $e$ 加 $1$，若要将一个 $x$ 个连通块的森林连成一棵树需要 $x-1$ 条边（相当于将每颗数看为一个点，这些点再构成一棵树），所以在一个 $x$ 个连通块的森林中，$p=e+x$。

问题转化为子矩阵内点数减去边数。点数很好搞，可以直接前缀和。对于边，我们记录**每个点向左、向上连的边数的前缀和**，再记录**每列上向左连的边数的前缀和**、**每行上向上连的边数的前缀和**，用一次二维前缀和，$2n$ 次一维前缀和即可预处理，询问时用第一个算出来的结果减去多算的即可，多算的可以简单地使用后两个算出来。

时间复杂度 $O(nm+Q)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=2e3+10;
int n,m,q,edg[N][N];
bool poi[N][N];
int pr1[N][N],pr2[N][N],lin[N][N],row[N][N];
inline int point(int a1,int b1,int a2,int b2){
	return pr1[a2][b2]-pr1[a2][b1-1]-pr1[a1-1][b2]+pr1[a1-1][b1-1];
}
inline int edge(int a1,int b1,int a2,int b2){
	return pr2[a2][b2]-pr2[a2][b1-1]-pr2[a1-1][b2]+pr2[a1-1][b1-1]-lin[a2][b1]+lin[a1-1][b1]-row[a1][b2]+row[a1][b1-1];
}
int main(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			poi[i][j]=getc()=='1';
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(poi[i][j])
				edg[i][j]=poi[i-1][j]+poi[i][j-1];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			lin[i][j]=lin[i-1][j]+(poi[i][j]&&poi[i][j-1]),
			row[i][j]=row[i][j-1]+(poi[i][j]&&poi[i-1][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			pr1[i][j]=poi[i][j]+pr1[i-1][j]+pr1[i][j-1]-pr1[i-1][j-1],
			pr2[i][j]=edg[i][j]+pr2[i-1][j]+pr2[i][j-1]-pr2[i-1][j-1];
	while(q--){
		int a1=read(),b1=read(),a2=read(),b2=read();
		write(point(a1,b1,a2,b2)-edge(a1,b1,a2,b2));
		putc('\n');
	}
	flush();
}
```
再见 qwq~

---

## 作者：20111019Yu (赞：2)

### 题意

有一个 $n\times m$ 的矩阵，每一个点可能涂色或不涂色，涂色的点形成的联通块没有环，俗称树，$q$ 个问题，每次问你在一个矩阵内有多少个连通块。

### 思路

我们注意到如果是一棵树，则边数一定比点数少一，所以我们可以计算矩阵内相邻的涂色格的对数和涂色格的个数。用点数减去对数即可，显而易见，这可以用前缀和维护。

### code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, q, x, y, xx, yy, cnt[2005][2005], sum[2005][2005][2];//点和边计数前缀和
char a[2005][2005];

signed main(){
	cin >> n >> m >> q;
	for( int i = 1; i <= n; i++ ){
		for( int j = 1; j <= m; j++ ){
			cin >> a[i][j];
			sum[i][j][1] = sum[i - 1][j][1] + sum[i][j - 1][1] - sum[i - 1][j - 1][1];//横着的边
			sum[i][j][0] = sum[i - 1][j][0] + sum[i][j - 1][0] - sum[i - 1][j - 1][0];//竖着的边
			cnt[i][j] = cnt[i - 1][j] + cnt[i][j - 1] - cnt[i - 1][j - 1] + (a[i][j] == '1');//点的数量
			if(a[i][j] == '1'){
				if(a[i - 1][j] == '1') sum[i][j][0]++;
				if(a[i][j - 1] == '1') sum[i][j][1]++;
			}
		}
	}
	while(q--){
		cin >> x >> y >> xx >> yy;
		int len = cnt[xx][yy] - cnt[x - 1][yy] - cnt[xx][y - 1] + cnt[x - 1][y - 1];//矩阵内点数
		int must1 = sum[xx][yy][0] - sum[xx][y - 1][0] - sum[x][yy][0] + sum[x][y - 1][0];//矩阵内竖的边
		int must2 = sum[xx][yy][1] - sum[xx][y][1] - sum[x - 1][yy][1] + sum[x - 1][y][1];//矩阵内横的边
		cout << len - must1 - must2 << endl;//计算答案
	}
	return 0;
}
```

---

## 作者：Ebola (赞：2)

首先是一个 ~~小学生都知道的~~ 常识：森林的联通块数量 = 点数 - 边数

于是，二维前缀和维护点数、边数，边分两种维护：横向边和纵向边，随便维护一下就好了

然后询问直接O(1)做就行了。注意不同的前缀和数组下标含义略有区别，写的时候一定要仔细

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2010;
int sump[N][N],sume1[N][N],sume2[N][N];
bool mp[N][N];

int main()
{
    static char s[N];
    int n,m,q;cin>>n>>m>>q;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        for(int j=1;j<=m;j++)
            mp[i][j]=(s[j]=='1');
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            sump[i][j]=sump[i-1][j]+sump[i][j-1]-sump[i-1][j-1]+mp[i][j];
            sume1[i][j]=sume1[i-1][j]+sume1[i][j-1]-sume1[i-1][j-1]+(mp[i][j]&&mp[i][j+1]);
            sume2[i][j]=sume2[i-1][j]+sume2[i][j-1]-sume2[i-1][j-1]+(mp[i][j]&&mp[i+1][j]);
        }
    while(q--)
    {
        int x1,y1,x2,y2;scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        int n=sump[x2][y2]-sump[x1-1][y2]-sump[x2][y1-1]+sump[x1-1][y1-1];
        int m=sume1[x2][y2-1]-sume1[x2][y1-1]-sume1[x1-1][y2-1]+sume1[x1-1][y1-1];
        m+=sume2[x2-1][y2]-sume2[x2-1][y1-1]-sume2[x1-1][y2]+sume2[x1-1][y1-1];
        printf("%d\n",n-m);
    }
    flush();
    return 0;
}
```



---

## 作者：xfrvq (赞：1)

题目条件说蓝色连通块都是树，所以选中的矩形里的蓝色连通块可以视为森林。

然后数森林连通块个数就是点数减去边数（矩形内）。

考虑把点数二维前缀和，然后矩形数点就是差分。

边分为竖直和水平，前者放在上面点，后者放在左边点，同样二维前缀和然后差分。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = (a);i <= (b);++i)

const int N = 2e3 + 5;

int n,m,q,a[N][N],s1[N][N],s2[N][N];

int main(){
	scanf("%d%d%d",&n,&m,&q);
	rep(i,1,n) rep(j,1,m){
		a[i][j] = getchar();
		while(!isdigit(a[i][j])) a[i][j] = getchar();
		a[i][j] -= '0';
	}
	rep(i,1,n) rep(j,1,m){
		s1[i][j] = a[i][j] && a[i + 1][j];
		s2[i][j] = a[i][j] && a[i][j + 1];
		s1[i][j] += s1[i - 1][j] + s1[i][j - 1] - s1[i - 1][j - 1];
		s2[i][j] += s2[i - 1][j] + s2[i][j - 1] - s2[i - 1][j - 1];
	}
	rep(i,1,n) rep(j,1,m)
		a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
	while(q--){
		int x1,y1,x2,y2;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		int p = a[x2][y2] - a[x2][y1 - 1] - a[x1 - 1][y2] + a[x1 - 1][y1 - 1];
		int q1 = s1[x2 - 1][y2] - s1[x2 - 1][y1 - 1] - s1[x1 - 1][y2] + s1[x1 - 1][y1 - 1];
		int q2 = s2[x2][y2 - 1] - s2[x2][y1 - 1] - s2[x1 - 1][y2 - 1] + s2[x1 - 1][y1 - 1];
		printf("%d\n",p - q1 - q2);
	}
	return 0;
}
```

---

## 作者：DerrickLo (赞：0)

很明显的是，森林中树的数量可以通过点数减边数得到。

所以维护几个前缀和，分别表示点数、横的边数、竖的边数，然后每次询问找到这个子矩阵的点数和边数就行了，注意从这个子矩阵外连到子矩阵内的边不能算进去。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q,a,b,c,d,sum1[2005][2005],sum2[2005][2005],sum3[2005][2005];
char aa[2005][2005];
signed main(){
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)cin>>(aa[i]+1);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		sum1[i][j]=sum1[i-1][j]+sum1[i][j-1]-sum1[i-1][j-1]+(aa[i][j]-'0');
		sum2[i][j]=sum2[i-1][j]+sum2[i][j-1]-sum2[i-1][j-1]+(aa[i][j]=='1'&&aa[i][j-1]=='1');
		sum3[i][j]=sum3[i-1][j]+sum3[i][j-1]-sum3[i-1][j-1]+(aa[i][j]=='1'&&aa[i-1][j]=='1');
	}
	while(q--){
		cin>>a>>b>>c>>d;
		cout<<(sum1[c][d]-sum1[c][b-1]-sum1[a-1][d]+sum1[a-1][b-1])-(sum2[c][d]-sum2[c][b]-sum2[a-1][d]+sum2[a-1][b])-(sum3[c][d]-sum3[c][b-1]-sum3[a][d]+sum3[a][b-1])<<"\n";
	}
	return 0;
}
```

---

## 作者：Erotate (赞：0)

首先，对于森林来说，我们知道联通块的个数等于点数减去边数。那么我们不妨考虑二维前缀和，对点和边都维护二维的前缀和。对于每一个查询，我们只需要用区间里蓝点的个数减去连接两个蓝点边的个数即为答案。注意，这里要考虑边缘的情况，对于区间的上下左右四个边缘，是要减掉蓝点连向区间外的点的边的。

```cpp
//r，c 是统计上下和左右边缘的边的数量的
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N=2e3+5;
int n,m,q,f[N][N],g[N][N],r[N][N],c[N][N];
char ch[N][N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m>>q;
	for(int i=1;i<=n;++i) cin>>ch[i]+1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
			g[i][j]=g[i-1][j]+g[i][j-1]-g[i-1][j-1];
			r[i][j]=r[i][j-1],c[i][j]=c[i-1][j];
			if(ch[i][j]=='1'){
				f[i][j]++;
				if(i>1 && ch[i-1][j]=='1') g[i][j]++,r[i][j]++;
				if(j>1 && ch[i][j-1]=='1') g[i][j]++,c[i][j]++;
			}
		}
	for(int i=1,x,x2,y,y2;i<=q;++i){
		cin>>x>>y>>x2>>y2;
		int v=f[x2][y2]-f[x2][y-1]-f[x-1][y2]+f[x-1][y-1],e=g[x2][y2]-g[x2][y-1]-g[x-1][y2]+g[x-1][y-1];
		e-=r[x][y2]-r[x][y-1]+c[x2][y]-c[x-1][y];
		cout<<v-e<<endl;
	}
	return 0;
}
```


---

## 作者：Tachibana27 (赞：0)

题意较好理解：给定仅由 `0` 和 `1` 组成的二维数组，保证是森林，每次给定询问范围，求范围内有多少个树（连通块）。

注意到：树的数量 = 点数 - 边数，所以问题转化成：给定一个二维区间，分别求其中点与边的数量之和。

求和自然就能想到前缀和，这里是二维前缀和。

前缀和需要维护：点的数量，横边的数量，竖边的数量（因为横边与竖边计算方式不同）。

code：
```cpp
int n,m,q;
bool a[2086][2086];
int s[2086][2086][10];//Sij1表示点的数量，Sij2表示横边（向左边）Sij3表示竖边（向上边）
int main(){
	n=read();
	m=read();
	q=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			char x;
			std::cin>>x;
			if(x-'0')
				a[i][j]=true;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			s[i][j][1]=s[i-1][j][1]+s[i][j-1][1]-s[i-1][j-1][1];
			s[i][j][2]=s[i-1][j][2]+s[i][j-1][2]-s[i-1][j-1][2];
			s[i][j][3]=s[i-1][j][3]+s[i][j-1][3]-s[i-1][j-1][3];//前缀和
			if(a[i][j]){
				s[i][j][1]++;//如果当前点是一个1那么++即可
				if(a[i][j-1])//左边也是1，那么有一条向左边
					s[i][j][2]++;
				if(a[i-1][j])
					s[i][j][3]++;//向上边，与上同理
				
			}
		}
	
	while(q--){
		int x1,y1,x2,y2;
		x1=read();
		y1=read();
		x2=read();
		y2=read();
		write(
		(s[x2][y2][1]-s[x2][y1-1][1]-s[x1-1][y2][1]+s[x1-1][y1-1][1])//点的数量，比较常规的二维前缀和计算
		-(s[x2][y2][2]-s[x2][y1][2]-s[x1-1][y2][2]+s[x1-1][y1][2])//横边与点的计算是不一样的，可以画图理解一下
		-(s[x2][y2][3]-s[x2][y1-1][3]-s[x1][y2][3]+s[x1][y1-1][3])//与上同理
		);
      
	}
  	return 0;//撒花
}
```
~~不建议直接加头文件交代码~~

---

## 作者：封禁用户 (赞：0)

首先，这是一个无环图，也就是树，树与一个性质：n个点，n-1条边，因此，我们只需要知道一个区间有几个点几条边即可。

对于一个二维区间查询，我们可以使用二维前缀和，我们对于每个点，记录以他为右下角的个数为多少，然后容斥即可，如果还是不懂，可以看看这篇文章https://blog.csdn.net/XT_NOI/article/details/72715904。

具体细节看代码，注意边界处理。

给2种写法

第一种：230ms
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2005;
int a[N][N],s[N][N],t[N][N],b1[N][N],b2[N][N];
int main()
{
	int n,m,q,x1,y1,x2,y2,sum1,sum2;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)
	{
		getchar();
		for(int j=1;j<=m;j++)
		{
			a[i][j]=getchar()-'0';
			s[i][j]=s[i-1][j]+s[i][j-1]+a[i][j]-s[i-1][j-1];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j])
			{
				if(a[i-1][j])
					t[i][j]++;
				if(a[i][j-1])
					t[i][j]++;
			}
			t[i][j]=t[i-1][j]+t[i][j-1]+t[i][j]-t[i-1][j-1];
		}
	}
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]&&a[i-1][j])
				b1[i][j]=1;
			b1[i][j]+=b1[i][j-1];
		}
	}
	for(int i=2;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(a[j][i]&&a[j][i-1])
				b2[j][i]=1;
			b2[j][i]+=b2[j-1][i];
		}
	}
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		sum1=s[x2][y2]+s[x1-1][y1-1]-s[x1-1][y2]-s[x2][y1-1];
		sum2=t[x2][y2]+t[x1-1][y1-1]-t[x1-1][y2]-t[x2][y1-1];
		sum2-=b1[x1][y2]-b1[x1][y1-1];
		sum2-=b2[x2][y1]-b2[x1-1][y1];
		printf("%d\n",sum1-sum2);
	}
	return 0;
}

```

第二种：140ms
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <assert.h>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <bitset>
 
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
#define Fi first
#define Se second
#define pb(x) push_back(x)
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0;i<n;i++)
#define all(x) (x).begin(), (x).end()
typedef tuple<int, int, int> t3;
typedef pair<ll, ll> pll;
typedef long double ldouble;
typedef unsigned int uint;
 
char S[2020][2020];
int P[2020][2020];
int Q[2020][2020];
int R[2020][2020];
int n, m, q;
 
int get(int T[][2020], int x1, int y1, int x2, int y2){
	return T[x2][y2] - T[x1-1][y2] - T[x2][y1-1] + T[x1-1][y1-1];
}
 
void solve(){
	scanf("%d%d%d", &n, &m, &q);
	for(int i=1;i<=n;i++) scanf("%s", S[i]+1);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) {
		P[i][j] = P[i-1][j] + P[i][j-1] - P[i-1][j-1] + (S[i][j] - '0');
		Q[i][j] = Q[i-1][j] + Q[i][j-1] - Q[i-1][j-1] + (S[i][j] - '0') * (i?(S[i-1][j] - '0'):0);
		R[i][j] = R[i-1][j] + R[i][j-1] - R[i-1][j-1] + (S[i][j] - '0') * (j?(S[i][j-1] - '0'):0);
	}
	rep(u, q){
		int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		int ans = get(P, x1, y1, x2, y2);
		ans -= get(Q, x1+1, y1, x2, y2);
		ans -= get(R, x1, y1+1, x2, y2);
		printf("%d\n", ans);
	}
}
 
int main(){
	int Tc = 1; //scanf("%d\n", &Tc);
	for(int tc=1;tc<=Tc;tc++){
		solve();
	}
	return 0;
}

```

---


# A Trance of Nightfall

## 题目描述

 The cool breeze blows gently, the flowing water ripples steadily."Flowing and passing like this, the water isn't gone ultimately; Waxing and waning like that, the moon doesn't shrink or grow eventually."

"Everything is transient in a way and perennial in another."

Kanno doesn't seem to make much sense out of Mino's isolated words, but maybe it's time that they enjoy the gentle breeze and the night sky — the inexhaustible gifts from nature.

Gazing into the sky of stars, Kanno indulges in a night's tranquil dreams.





There is a set $ S $ of $ n $ points on a coordinate plane.

Kanno starts from a point $ P $ that can be chosen on the plane. $ P $ is not added to $ S $ if it doesn't belong to $ S $ . Then the following sequence of operations (altogether called a move) is repeated several times, in the given order:

1. Choose a line $ l $ such that it passes through at least two elements in $ S $ and passes through Kanno's current position. If there are multiple such lines, one is chosen equiprobably.
2. Move to one of the points that belong to $ S $ and lie on $ l $ . The destination is chosen equiprobably among all possible ones, including Kanno's current position (if it does belong to $ S $ ).

There are $ q $ queries each consisting of two integers $ (t_i, m_i) $ . For each query, you're to help Kanno maximize the probability of the stopping position being the $ t_i $ -th element in $ S $ after $ m_i $ moves with a proper selection of $ P $ , and output this maximum probability. Note that according to rule 1, $ P $ should belong to at least one line that passes through at least two points from $ S $ .

## 说明/提示

The points in $ S $ and possible candidates for line $ l $ are depicted in the following figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF989E/9dc6a2e53d51df32abc295e2febe0114d0e3d73f.png)For the first query, when $ P = (-1, -3) $ , $ l $ is uniquely determined to be $ 3x = y $ , and thus Kanno will move to $ (0, 0) $ with a probability of $ \frac 1 2 $ .

For the third query, when $ P = (2, 2) $ , $ l $ is chosen equiprobably between $ x + y = 4 $ and $ x = y $ . Kanno will then move to the other four points with a probability of $ \frac 1 2 \cdot \frac 1 3 = \frac 1 6 $ each, or stay at $ (2, 2) $ with a probability of $ \frac 1 3 $ .

## 样例 #1

### 输入

```
5
0 0
1 3
2 2
3 1
4 4
10
1 1
2 1
3 1
4 1
5 1
3 2
3 3
3 4
3 5
3 6
```

### 输出

```
0.50000000000000000000
0.50000000000000000000
0.33333333333333331483
0.50000000000000000000
0.50000000000000000000
0.18518518518518517491
0.15226337448559670862
0.14494741655235482414
0.14332164812274550414
0.14296036624949901017
```

# 题解

## 作者：asuldb (赞：1)

[题目](https://www.luogu.com.cn/problem/CF989E)

根据题意，只有刚开始所在的点可能不是给定的$n$个点，之后所有的位置一定都在给定的点集中了；我们大力求一下$P_{i,j}$表示从点$i$移动到点$j$的概率，这个随便暴力一下就好了，由于询问的终点是给定的，于是我们利用求出来的$P_{i,j}$建一张反图

接下来不妨考虑一下起始点的位置，我们大力猜想这个**起始点不可能是两条直线的交点**，感性理解一下发现这个结论非常正确；在交点上相当于对各条直线上的答案取了一个加权平均值，这个平均值一定小于答案最大的那条直线，我们把起始点放在那条直线上一定比在交点上更优。

于是起始点只可能有两种情况，可能是给定点集中的某个点，也可能在**给定点集形成的一条直线上且不是任意两条直线的交点**；不难发现第二种情况包含第一种情况，我们只需要考虑第二种情况即可。

由于直线条数不超过$O(n^2)$条，于是我们可以暴力每一条直线，并处理出每一条直线上点有哪些。一条直线的答案就是**上面每一个点到$t$的概率除以直线上点的个数。**

由于我们建了反图，所以转化成了$t$到上面每一个点的概率，我们现在要求的就是这个东西了；不难发现这是一个简单dp，我们可以通过矩阵来优化这个dp，但是直接上是$O(qn^3\log m)$的，这看起来不是很科学。

这就是一个简单的套路了，两个矩阵相乘是$O(n^3)$的，但是向量乘矩阵却是$O(n^2)$的，我们求出最终的转移矩阵也只是为了和一个向量相乘，所以我们只保留$2$的次幂的矩阵，拿着向量去乘这些矩阵就好了，这样一组询问的复杂度就只有$O(n^2\log m)$了。

复杂度是$O(n^3+qn^2\log m)$，代码

```cpp
#include<bits/stdc++.h>
#define re register
#define max(a,b) ((a)>(b)?(a):(b))
const int maxn=205;
int n,f[maxn],vis[maxn],Q,ma[maxn][maxn],num;
struct pt{int x,y;}p[maxn];
struct Mat{double a[maxn][maxn];}pw[14];
struct Vector{double d[maxn];}ans;
std::vector<int> line[maxn*maxn];
inline int operator*(const pt &A,const pt &B) {return A.x*B.y-A.y*B.x;}
inline pt operator-(const pt &A,const pt &B) {return (pt){A.x-B.x,A.y-B.y};}
inline Mat operator*(const Mat &A,const Mat &B) {
	Mat C;
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=n;j++) C.a[i][j]=0;
	for(re int k=1;k<=n;k++)
		for(re int i=1;i<=n;i++)
			for(re int j=1;j<=n;j++) C.a[i][j]+=A.a[i][k]*B.a[k][j];
	return C;
}
inline Vector operator*(const Vector &A,const Mat &B) {
	Vector C;for(re int i=1;i<=n;i++) C.d[i]=0;
	for(re int i=1;i<=n;i++) 
		for(re int j=1;j<=n;j++) C.d[j]+=A.d[i]*B.a[i][j];
	return C;
}
inline void calc(int t,int m) {
	for(re int i=1;i<=n;i++)ans.d[i]=0;ans.d[t]=1;
	for(re int i=13;i>=0;--i)if(m>>i&1) ans=ans*pw[i];
}
inline void work() {
	for(re int i=0;i<line[num].size();++i)
		for(re int j=0;j<line[num].size();++j)ma[line[num][i]][line[num][j]]=1;
}
int main() {
	scanf("%d",&n);
	for(re int i=1;i<=n;i++)scanf("%d%d",&p[i].x,&p[i].y);
	for(re int i=1;i<=n;i++) {
		int Line_num=0;double nw=0;
		for(re int j=1;j<=n;j++) {
			if(j==i||vis[j]) continue;
			int tot=0;++Line_num;
			for(re int k=1;k<=n;k++)
				if((p[k]-p[i])*(p[j]-p[i])==0) vis[k]=1,++tot;
			for(re int k=1;k<=n;++k)
				if((p[k]-p[i])*(p[j]-p[i])==0) f[k]=tot;
			nw+=1.0/(double)tot;
		}
		double p=1.0/(double)Line_num;
		for(re int j=1;j<=n;j++) {
			if(j==i) {pw[0].a[i][i]=nw*p;continue;}
			pw[0].a[j][i]=1.0/(double)f[j];
			pw[0].a[j][i]*=p;
		}
		for(re int j=1;j<=n;j++)f[j]=vis[j]=0;
	}
	for(re int i=1;i<=n;i++) 
		for(re int j=i+1;j<=n;j++) {
			if(ma[i][j]) continue;++num;
			for(re int k=1;k<=n;k++)
				if((p[i]-p[k])*(p[j]-p[k])==0) line[num].push_back(k);
			work();
		}
	for(re int i=1;i<=13;i++)pw[i]=pw[i-1]*pw[i-1];
	scanf("%d",&Q);int t,m;double nw;
	while(Q--) {
		scanf("%d%d",&t,&m);nw=0;
		calc(t,m-1);
		for(re int i=1;i<=num;++i) {
			double k=0;
			for(re int j=0;j<line[i].size();++j) k+=ans.d[line[i][j]];
			k*=1.0/(double)line[i].size();
			nw=max(k,nw);
		}
		printf("%.12lf\n",nw);
	}return 0;
}
//g++ cf989e.cpp -o cf989e
```

---

## 作者：PhantasmDragon (赞：0)

首先把给的二维坐标系转化为一张有向图，$u$ -> $v$ 的边权 $P$ 就是从 $u$ 号点走到 $v$ 号点的概率。 方法很多，只要在 $\mathcal O(n^3)$之内处理出来即可。

考虑一个dp: $f_{i,x}$ 表示从 $x$ 走 $i$ 步走到终点 $t$ 的概率, 初值 $f_{0,t}=1$.
那么就有:
$$f_{i,x}=\sum_{y,(x,y)\in E} f_{i-1,y}*P_{x,y}$$

可以使用矩阵乘法优化。

假如当前询问终点为 $t$ , 要求步数为 $step$ , 现在要决定第一步从哪里开始，首先矩阵乘法处理出每个点走 $step-1$ 步走到 $t$ 的概率。

起始点按照题意必须是在 $S$ 中任意两点连线之间的。那么暴力处理出 $S$ 中所有可能的两点之间的连线，枚举每条线，再枚举线上的每个点，算出起点在这条线的概率，答案与其取max即可。

但是，为什么起点不能在这些线的交点上？很显然，如果起点在多条线上，答案就是起点单独在每条线上取个平均值，而一堆输的平均值显然小于其最大值，那么直接选概率最大的线显然最优。

还有矩阵乘法时的小 trick(套路). 直接矩阵快速幂时是 $\mathcal O(n^3logm)$的，对于200次询问显然爆炸。我们可以预处理出原矩阵的2的整次幂，对于每次询问，从中选出 $logn$ 个凑出原矩阵的$step-1$次幂。利用向量乘矩阵只需要 $n^2$ 复杂度的性质，用初始向量依次乘以这些矩阵，复杂度就降到了 $\mathcal O(n^2logn)$，可以接受。


---

## 作者：Thosaka_Forest (赞：0)

   首先根据题意，出发点不一定在特殊点上，但第一次操作后，之后所有的操作都是在特殊点上，所以先考虑从线上出发的最大概率，再加一步即可得到从点出发的最大概率，二者取较大值即可。
   
   记数组f[i][j][k]表示从i点走k步到j点的概率，所以转移方程就出来了：
   
   然后发现这个形式其实就是矩阵乘法，所以可以利用矩阵快速幂优化，计算出走2^i步的概率。
   
   但每次都进行一次快速幂的计算复杂度为O(n^3log(q))，所以继续优化。
   
   因为我们只需要考虑最后到达t的最大概率，所以在进行矩阵乘法的时候很多位置都是没用的，所以考虑将初始矩阵简化为一个1*n的矩阵，表示走0步到达t的概率，显然只有base[t]=1，其他位置均为0。
   
   然后将操作数进行二进制拆分进行左乘，因为初始矩阵只有1行，所以不管乘几次都只有一行，这样直接优化了一个n的复杂度。
   
   从直线开始就是比从点开始少了一步（因为要先走到点上），所以就先处理从直线开始走的情况统计答案，最后再计算一次就可以得到从点开始走的概率。
   
   考虑构造f[i][j][0]，显然从i点走一步到达j点的概率为(1/(经过i点直线数)*（直线i,j上的点数）)，根据这个构造即可。
   
   然后就是各种小细节。。。
   
   1.直线去重，这样可以避免进行重复计算。
   
   2.将一个vector的值赋给另一个vector的时候加个传址符会快一点。
   
   3.在计算f数组和base数组的时候如果f[i][j][k]或g[i]已经小于1e-6了，那么其实并没有必要继续计算下去了，因为精度太小反而可能会爆炸，而且题目也说了误差在1e-6以内即可，这样大大减少运行时间。
   
   附上写的很丑的代码：
        
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=201;
const int MAXM=15;

int n,q;
int x[MAXN],y[MAXN];
int vis[MAXN],cnt[MAXN];      //cnt数组记录经过这个点的直线数 
double ans;
double f[MAXN][MAXN][MAXM+1];
double Base[MAXN],zy[MAXN];
vector<int> point[MAXN][MAXN];//所有共线的点 
vector<pair<int,int> > line;  //所有直线 

inline int Read(){
	int i=0,f=1;
	char c;
	for(c=getchar();(c>'9'||c<'0')&&c!='-';c=getchar());
	if(c=='-')
	  f=-1,c=getchar();
	for(;c>='0'&&c<='9';c=getchar())
	  i=(i<<3)+(i<<1)+c-'0';
	return i*f;
}

bool check(int a,int b,int c){
	return (y[b]-y[a])*(x[c]-x[a])==(y[c]-y[a])*(x[b]-x[a]);  //判三点共线，当然可以用向量进行运算 
}

int main(){
	n=Read();
	for(int i=1;i<=n;++i)
	  x[i]=Read(),y[i]=Read();
	for(int i=1;i<=n;++i){
		memset(vis,0,sizeof(vis));
		for(int j=1;j<=n;++j){
			if(i==j)
			  continue;
			if(vis[j])
			  continue;
			cnt[i]++;
			for(int k=1;k<=n;++k){
				if(check(i,j,k)){        //三点共线 
					point[i][j].push_back(k);
					vis[k]=1;
				}
			}
			line.push_back(make_pair(point[i][j][0],point[i][j][1]));//两点确定一条直线，所以取前两个 
		}
	}
	sort(line.begin(),line.end());
	line.erase(unique(line.begin(),line.end()),line.end());//直线去重避免重复运算 
	int siz1=line.size();
	for(int i=0;i<siz1;++i){
		vector<int> &vec=point[line[i].first][line[i].second];//计算在选择这条直线的情况下i一步走到j的概率 
		int siz2=vec.size();
		for(int j=0;j<siz2;++j){
			for(int k=0;k<siz2;++k){
				f[vec[j]][vec[k]][0]+=1.0/siz2*1.0;
			}
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			f[i][j][0]/=cnt[i];    //在除去一个经过i点的直线数 
		}
	}
	for(int i=1;i<=MAXM;++i){
		for(int j=1;j<=n;++j){
			for(int k=1;k<=n;++k){
				if(f[j][k][i-1]>1e-6){
					for(int t=1;t<=n;++t){
						f[j][t][i]+=f[j][k][i-1]*f[k][t][i-1];//预处理走2^i步的概率 
					}
				}
			}
		}
	}
	q=Read();
	while(q--){
		int t=Read(),step=Read()-1;//计算从线开始的概率 
		memset(Base,0,sizeof(Base));
		Base[t]=1;
		for(int i=0;i<=MAXM;++i){
			if((1<<i)>step)
			  break;
			if((1<<i)&step){
				memset(zy,0,sizeof(zy));
				for(int j=1;j<=n;++j){
					if(Base[j]>1e-6){
						for(int k=1;k<=n;++k){
							zy[k]+=f[k][j][i]*Base[j];//左乘 
						}
					}
				}
				memcpy(Base,zy,sizeof(zy));
			}
		}
		ans=0.0;
		int siz=line.size();
		for(int i=0;i<siz;++i){
			vector<int> &vec=point[line[i].first][line[i].second];
			double tot=0.0;
			int siz2=vec.size();
			for(int j=0;j<siz2;++j){
				tot+=Base[vec[j]];
			}
			tot/=1.0*siz2;
			ans=max(ans,tot);
		}
		memset(zy,0,sizeof(zy));  //计算从点开始的概率 
		for(int i=1;i<=n;++i){
			if(Base[i]>1e-6){
				for(int j=1;j<=n;++j){
					zy[j]+=Base[i]*f[j][i][0];
				}
			}
		}
		memcpy(Base,zy,sizeof(zy));
		for(int i=1;i<=n;++i)
		  ans=max(ans,Base[i]);
		printf("%.10lf\n",ans);
	}
	return 0;
}
```

---


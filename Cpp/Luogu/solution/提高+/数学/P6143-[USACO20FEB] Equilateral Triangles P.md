# [USACO20FEB] Equilateral Triangles P

## 题目描述

Farmer John 的农场可以用一个 $N \times N$ 的方阵（$1 \leq N \leq 300$）。对于方阵内的每个格子，如果这个格子有奶牛，就用 `*` 表示，否则用 `.` 表示。

FJ 相信他的牧场的美丽程度正比于两两距离相等的奶牛三元组的数量。也就是说，她们组成一个等边三角形。不幸的是，直到最近 FJ 才发现，由于他的奶牛都处在整数坐标位置，如果使用欧几里得距离进行计算，不可能存在美丽的奶牛三元组！于是，FJ 决定改用“曼哈顿”距离。形式化地说，两点 $(x_0,y_0)$ 和 $(x_1,y_1)$ 的曼哈顿距离等于 $|x_0-x_1|+|y_0-y_1|$。

给定表示奶牛位置的方阵，计算等边三角形的数量。

## 说明/提示

### 样例解释

有三头奶牛，并且她们组成了一个等边三角形，因为每对奶牛之间的曼哈顿距离都等于二。

### 子任务

- 对于测试点 $T$（$T \in [2,11]$），满足 $N=25T$；
- 对于测试点 $T$（$T \in [12,15]$），满足 $N=300$。

## 样例 #1

### 输入

```
3
*..
.*.
*..```

### 输出

```
1```

# 题解

## 作者：hyfhaha (赞：15)

题解 P6143 【[USACO20FEB]Equilateral Triangles P】

本题解所涉及知识点仅有前缀和。

其实也不需要什么曼哈顿距离的转化，有些结论还是显而易见的

![](https://cdn.luogu.com.cn/upload/image_hosting/s1k5guw1.png))

如上图，对于斜向下$45°$的直线上任意两个点（图中$J,K $）两点

向下做等腰直角三角形$\triangle JHK$ 并延长$JH$和$KH$ 做的等腰直角三角形$\triangle OHL$ 

使$\triangle OHL \cong \triangle JHK$ 

那么线段$OL$上任意一个整点(如图$O,N,M,L$)与$J,K$两点一定形成一个曼哈顿等边三角形

证明：首先$\triangle OJK $ 一定是曼哈顿等边三角形（易证）

$O$每次延$OL$向下移动一个点，它与$J,K$的曼哈顿距离不变（横$+1$，纵$-1$）

所以线段$OL$上任意一个整点与$J,K$两点都可形成曼哈顿等边三角形

------

上面的结论非常显然，我们可以根据上面的结论解决此题

我们先对每一条斜向下的直线做一个前缀和，这样我们可以快速计算出一条斜线段上有多少个`*`点

然后我们枚举一个`*`点（图中$J$）和一个距离（如图中线段$JH$的长）

辣么我们就可以知道其他$3$个点的坐标了（如图上：$K,O,L$）

如果判断点（图中的$K$）也是`*`点

就用前缀和算出线段（图中$OL$）上`*`点的数量

累加答案。

但是，明显我们要统计的不止斜向下$45°$这一条直线的一边上的曼哈顿等边三角形。

所以我们把整张图翻转$90°$，再做一遍。同理$180°$和$270°$ 也要再做一遍。

为了避免重复计算，我们前缀和统计答案时要减去左端点（即$f(R)-f(L-1)$变为$f(R)-f(L)$）

其实核心思想很简单，但我好像解释得太复杂了……

看代码吧，核心的前缀和就一条式子

```cpp
#include<bits/stdc++.h>
#define maxn 611
using namespace std;
int a[maxn][maxn],b[maxn][maxn],n,f[maxn][maxn],ans,tot;
struct kkk{
	int x;int y;
}p[maxn*maxn];
void turn(){			//把图翻转90°
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)b[i][j]=a[i][j];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
		a[j][i]=b[n-i+1][j];
	}
}
void solve(){			//统计答案
	tot=0;
	for(int i=1;i<=n*2;i++)for(int j=1;j<=n*2;j++)f[i][j]=0;
	for(int i=1;i<=n*2;i++){	//开两倍是为了防溢出
		for(int j=1;j<=n*2;j++){
			f[i][j]=f[i-1][j+1]+a[i][j];
		}
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(a[i][j]==1)p[++tot].x=i,p[tot].y=j;	//标记*点
	for(int i=1;i<=tot;i++){	//枚举*点
		for(int k=1;k<=n;k++){	//枚举距离
			int xa=p[i].x,ya=p[i].y;
			int xb=p[i].x-k,yb=p[i].y+k;	//判断点坐标
			if(xb<1||yb>n)break;	//超出范围判断
			if(a[xb][yb]==0)continue;	//判断点是否是*点
			ans+=f[xa+k][ya+k]-f[xa][ya+k*2];	//前缀和统计答案
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char ch;
			cin>>ch;
			if(ch=='*')a[i][j]=1;
			else a[i][j]=0;
		}
	}
	for(int i=1;i<=4;i++)turn(),solve();//翻转一次，统计一次
	printf("%d\n",ans);	//输出
	return 0;
}
```

好简洁的呢

时间复杂度$O(4*n^3)$，不过应该比较难跑满，好像还挺快的（雾

---

## 作者：ix35 (赞：11)

赛时先想出来了 T1，但是第一次 T1 写挂，就先来看了 T2，结果秒了，应该是这次最简单的一题。

我们来观察一个曼哈顿等边三角形，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/lkfcwtla.png)

红线是 $BC$ 的曼哈顿距离，蓝线是 $AC$ 的曼哈顿距离，根据要求有红线和蓝线长度相等。

我们将曼哈顿距离稍作变换，得到下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/65q2jct7.png)

$BC$ 的曼哈顿距离此时是 红+绿，$AC$ 此时是 蓝+绿，于是我们可以得到：红+绿=蓝+绿，所以 红=蓝。

这里建立了一个中转结点 $O$，姑且叫做“曼哈顿外心”，因为 $OA=OB=OC$（曼哈顿距离）。

当然这只是曼哈顿等边三角形的一种摆布，转一转翻一翻就可以得到所有可能的情况。

所以我们先枚举这个外心 $O$，然后枚举 $OA$ 的长，这时 $A,B$ 已经确定，我们只需要确定 $C$，发现 $C$ 是满足 $OC=OA$，且在 $A,B$ 的相反“象限”位置，画一下轨迹就会发现，$C$ 的轨迹是一条与矩阵某条对角线平行的斜线段，这个可以用类似 [道路游戏](https://www.luogu.com.cn/problem/P1070) 中的斜向前缀和套路处理，可以 $O(1)$ 求出这样 $C$ 的数量。

时间复杂度为 $O(n^3)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=310;
int n,a[MAXN][MAXN],sum1[MAXN][MAXN],sum2[MAXN][MAXN];
char c[MAXN][MAXN];
long long ans;
void chk1 (int x,int y,int l) {
	int p=x-l,q=y-l;
	if (p<=0||q<=0||!a[p][y]||!a[x][q]) {return;}
	int tmp1=min(n-x,l),tmp2=min(n-y,l);
	if (tmp1+tmp2<l) {return;}
	ans+=(sum2[x+tmp1][y+l-tmp1]-sum2[x+l-tmp2-1][y+tmp2+1]);
	return;
}
void chk2 (int x,int y,int l) {
	int p=x-l,q=y+l;
	if (p<=0||q>n||!a[p][y]||!a[x][q]) {return;}
	int tmp1=min(n-x,l),tmp2=min(y-1,l);
	if (tmp1+tmp2<l) {return;}
	ans+=(sum1[x+tmp1][y-l+tmp1]-sum1[x+l-tmp2-1][y-tmp2-1]);
	return;
}
void chk3 (int x,int y,int l) {
	int p=x+l,q=y+l;
	if (p>n||q>n||!a[p][y]||!a[x][q]) {return;}
	int tmp1=min(x-1,l),tmp2=min(y-1,l);
	if (tmp1+tmp2<l) {return;}
	ans+=(sum2[x-l+tmp2][y-tmp2]-sum2[x-tmp1-1][y-l+tmp1+1]);
	return;
}
void chk4 (int x,int y,int l) {
	int p=x+l,q=y-l;
	if (p>n||q<0||!a[p][y]||!a[x][q]) {return;}
	int tmp1=min(x-1,l),tmp2=min(n-y,l);
	if (tmp1+tmp2<l) {return;}
	ans+=(sum1[x-l+tmp2][y+tmp2]-sum1[x-tmp1-1][y+l-tmp1-1]);
	return;
}
int main () {
	freopen("triangles.in","r",stdin);
	freopen("triangles.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%s",c[i]+1);
		for (int j=1;j<=n;j++) {a[i][j]=(c[i][j]=='*');}
	}
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			sum1[i][j]=sum1[i-1][j-1]+a[i][j];
			sum2[i][j]=sum2[i-1][j+1]+a[i][j];
		}
	}
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			for (int k=1;k<=n;k++) {
				chk1(i,j,k);
				chk2(i,j,k);
				chk3(i,j,k);
				chk4(i,j,k);
				int cntt=0;
				cntt+=(i>k&&a[i-k][j]);
				cntt+=(j+k<=n&&a[i][j+k]);
				cntt+=(i+k<=n&&a[i+k][j]);
				cntt+=(j>k&&a[i][j-k]);
				ans-=(cntt==3?1:(cntt==4?4:0));
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：xht (赞：6)

曼哈顿距离转成切比雪夫距离，可以发现满足要求的三角形在新的坐标下一定是**一个平行与坐标轴的正方形的两个相邻的顶点和对面的边上的任意一点**连接而成。

那么前缀和计数一下即可，显然要横着和竖着各算一次，时间复杂度 $\mathcal O(n^3)$。

如果出现三个点都是正方形的顶点的情况，会被横着竖着各计算一次，需要去掉这样的情况，在后一次计算的时候不算到即可。

```cpp
const int N = 307;
int n, a[N*2][N*2], b[N*2][N*2];
char s[N];
ll ans;

int main() {
	rd(n);
	for (int i = 1; i <= n; i++) {
		rds(s, n);
		for (int j = 1; j <= n; j++)
			if (s[j] == '*') a[i+j-1][i-j+n] = 1;
	}
	n *= 2;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			b[i][j] = a[i][j] + b[i][j-1];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (a[i][j])
				for (int k = j + 1; k <= n; k++)
					if (a[i][k]) {
						if (i - (k - j) >= 1)
							ans += b[i-(k-j)][k] - b[i-(k-j)][j-1];
						if (i + (k - j) <= n)
							ans += b[i+(k-j)][k] - b[i+(k-j)][j-1];
					}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			b[i][j] = a[i][j] + b[i-1][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (a[j][i])
				for (int k = j + 1; k <= n; k++)
					if (a[k][i]) {
						if (i - (k - j) >= 1)
							ans += b[k-1][i-(k-j)] - b[j][i-(k-j)];
						if (i + (k - j) <= n)
							ans += b[k-1][i+(k-j)] - b[j][i+(k-j)];
					}
	print(ans);
	return 0;
}
```

---

## 作者：lzqy_ (赞：5)

优雅的暴力。

设三个点为 $(i,j,k)$，则有 $6$ 个未知数即 $x_i,x_j,x_k,y_i,y_j,y_k$。又因为有 $2$ 条关于这 $6$ 个未知数的方程 $ij=jk,ij=ik$，所以一定能通过枚举其中的 $4$ 个量来求解，时间复杂度 $O(n^4)$。

而这个 $O(n^4)$ 的暴力是肉眼可见的跑不满（

-----

考虑先枚举点 $i$，则有以下四种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/ynniilt3.png)

解得 $x=a,y=a-b$。

其中，$a,x>0,0\le b,y \le a$。

![](https://cdn.luogu.com.cn/upload/image_hosting/1ktxjae4.png)

解得 $x=a,y=a-b$。

其中，其中，$a,x>0,0\le b,y\le a,\color{red}b\not= 0$。


![](https://cdn.luogu.com.cn/upload/image_hosting/h33l7rwp.png)


解得 $x=2b-a,y=b-a$。

其中，$0\le a<b,0\le x,y$。


![](https://cdn.luogu.com.cn/upload/image_hosting/ud3a5dls.png)

解得 $x=2b-a,y=b-a$。

其中，$0\le a<b,0\le x,y,\color{red}a\not=0$。


------

注意，有些同时存在于两种情况的状态， 需要通过标红的判断去除。

然后就能敲出以下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=310;
inline int read(){
	int x=0;
	char c=getchar();
	for(;(c^'.')&&(c^'*');c=getchar());
	return c=='*';
}
bool c[maxn][maxn];
int n,ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			c[i][j]=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(!c[i][j]) continue;
			for(int a=0;a<=n;a++){
				for(int b=0;b<=a;b++){
					if(a&&i+a<=n&&j+a<=n&&i-a+b>0&&j+a+b<=n)
						ans+=(c[i+a][j+a]&c[i-a+b][j+a+b]);
					if(a&&b&&i-a>0&&j+a<=n&&i+a-b<=n&&j+a+b<=n)
						ans+=(c[i-a][j+a]&c[i+a-b][j+a+b]);
				}
				for(int b=a+1;b<=n;b++){
					if(i-b-b+a>0&&j+a<=n&&i-b+a>0&&j+a+b<=n)
						ans+=(c[i-b-b+a][j+a]&c[i-b+a][j+a+b]);
					if(a&&i+b+b-a<=n&&j+a<=n&&i+b-a<=n&&j+a+b<=n)
						ans+=(c[i+b+b-a][j+a]&c[i+b-a][j+a+b]);
				}
			}
		}
	printf("%d\n",ans);
	return 0;
} 
```

然后你会获得 $51pt$ 的高分。

容易发现，代码中搜索到了许多冗余的状态，考虑将判断放到循环之外：

```cpp

#include<bits/stdc++.h>
using namespace std;
const int maxn=310;
inline int read(){
	int x=0;
	char c=getchar();
	for(;(c^'.')&&(c^'*');c=getchar());
	return c=='*';
}
bool c[maxn][maxn];
int n,ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			c[i][j]=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(!c[i][j]) continue;
			for(int a=0;a<=n;a++){
				if(a&&i+a<=n&&j+a<=n)
					for(int b=max(a-i+1,0);b<=a&&j+a+b<=n;b++)
						ans+=(c[i+a][j+a]&c[i-a+b][j+a+b]);
				if(a&&i-a>0&&j+a<=n)
					for(int b=max(i+a-n,1);b<=a&&b<=n-j-a;b++)
						ans+=(c[i-a][j+a]&c[i+a-b][j+a+b]);
				if(j+a<=n)
					for(int b=a+1;j+a+b<=n&&b+b<i+a;b++)
						ans+=(c[i-b-b+a][j+a]&c[i-b+a][j+a+b]);
				if(a&&j+a<=n)
					for(int b=a+1;j+a+b<=n&&b+b<=n-i+a;b++)
						ans+=(c[i+b+b-a][j+a]&c[i+b-a][j+a+b]);
			}
		}
	printf("%d\n",ans);
	return 0;
} 
```

然后就过了。

祝AC。

---

## 作者：cff_0102 (赞：4)

这题被放到学校比赛里了，来讲讲赛时思路。

注意到这么一个三角形一定满足两个点（设为 $A,C$）到第三个点（设为 $B$）的路径上有一段重合。设那个重合的点为 $O$，那么显然 $OA=OC$，则 $O$ 是 $AC$ 路径上的中点，且 $OA$ 和 $OC$ 互相垂直。

注：下图是赛时我在电脑画图上画的草稿。

![](https://cdn.luogu.com.cn/upload/image_hosting/3u8m2my3.png)

那么根据题面，$AC=CB=AB$，因此 $OA=OB=OC$，$O$ 点就变成了这个三角形的“外心”。

考虑枚举 $O$ 点，每次向两个垂直的方向同时枚举 $A,C$，再在另一个方向枚举 $B$，时间复杂度 $O(n^4)$，看起来过不了，但是有很多情况到不了，所以洛谷上能过。学校比赛时把这个做法卡了。

注意到枚举 $B$ 的时候实际上就是求一段斜线上的数的和，想到可以斜着做前缀和，就能优化到 $O(n^3)$。那这题就做完了。

赛时代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=666;
bool a[N][N];
int s1[N][N],s2[N][N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		char c;cin>>c;a[i][j]=(c=='*');
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		s1[i][j]=s1[i-1][j-1]+a[i][j];
		s2[i][j]=s2[i-1][j+1]+a[i][j];
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			//枚举 2/d
			for(int d=1;d<=n;d++){
				if(i-d>=1&&j-d>=1){
					if(a[i-d][j]&&a[i][j-d]){
						/*
						for(int k=0;k<=d;k++){
							if(i+k<=n&&j+d-k<=n){
								if(a[i+k][j+d-k]){
									ans++;
								}
							}
						}
						*///cout<<i<<" "<<j<<" "<<d<<"  "<<min(i+d,n)<<" "<<j+i+d-min(i+d,n)<<" "<<i+j+d-min(j+d,n)-1<<" "<<min(j+d,n)+1<<" "<<s2[min(i+d,n)][j+i+d-min(i+d,n)]-s2[i+j+d-min(j+d,n)-1][min(j+d,n)+1]<<endl;
						if(min(i+d,n)>i+j+d-min(j+d,n)-1)ans+=s2[min(i+d,n)][j+i+d-min(i+d,n)]-s2[i+j+d-min(j+d,n)-1][min(j+d,n)+1];
					}
				}
				if(i+d<=n&&j-d>=1){
					if(a[i+d][j]&&a[i][j-d]){
						/*
						for(int k=1;k<d;k++){
							if(i-k>=0&&j+d-k<=n){
								if(a[i-k][j+d-k]){
									ans++;
								}
							}
						}
						*///cout<<" "<<s1[i-j-d+min(j+d-1,n)][min(j+d-1,n)]-s1[max(i-d+1,1)-1][j-i+d+max(i-d+1,1)-1]<<endl;
						if(i-j-d+min(j+d-1,n)>max(i-d+1,1)-1)ans+=s1[i-j-d+min(j+d-1,n)][min(j+d-1,n)]-s1[max(i-d+1,1)-1][j-i+d+max(i-d+1,1)-1];
					}
				}
				if(i+d<=n&&j+d<=n){
					if(a[i+d][j]&&a[i][j+d]){
						/*
						for(int k=0;k<=d;k++){
							if(i-k>=0&&j-d+k>=0){
								if(a[i-k][j-d+k]){
									ans++;
								}
							}
						}
						*///cout<<i<<" "<<j<<" "<<d<<"  "<<i+j-d-max(j-d,1)<<" "<<max(j-d,1)<<" "<<max(i-d,1)-1<<" "<<j+i-d-max(i-d,1)+1<<endl;
						if(i+j-d-max(j-d,1)>max(i-d,1)-1)ans+=s2[i+j-d-max(j-d,1)][max(j-d,1)]-s2[max(i-d,1)-1][j+i-d-max(i-d,1)+1];
					}
				}
				if(i-d>=1&&j+d<=n){
					if(a[i-d][j]&&a[i][j+d]){
						/*
						for(int k=1;k<d;k++){
							if(i+k<=n&&j-d+k>=0){
								if(a[i+k][j-d+k]){
									ans++;
								}
							}
						}
						*/
						if(min(i+d-1,n)>i-j+d+max(j-d+1,1)-1)ans+=s1[min(i+d-1,n)][j-i-d+min(i+d-1,n)]-s1[i-j+d+max(j-d+1,1)-1][max(j-d+1,1)-1];
					}
				}
			}
			//cout<<ans<<endl;
		}
	}
	cout<<ans;
	return 0;
}
```

$O(n^4)$ 都能过，这题咋还是蓝的，建议降绿或者把 $O(n^4)$ 做法卡掉。

---

## 作者：hoko (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/P6143)

这是一道比较有意思的偏数学题。首先容易想到结论：![](https://cdn.luogu.com.cn/upload/image_hosting/1y8wjmpp.png?x-oss-process=image/resize,m_lfit,h_450,w_450)
对于倾角为 $45°$ 的线段上的点 $J$ 和点 $K$，作等腰三角形 $JKH$ 然后将其翻转 $90°$，得到其全等三角形 $OHL$，先抛出结论：线段 $OL$ 上的每一个奶牛都可以与点 $J$ 和点 $K$ 形成一个曼哈段等边三角形。

接下来证明：因为 $JK$ 的曼哈顿距离等于 $JH+HK$，又因为 $OJ$ 的距离等于 $OH+HJ$，$OK$ 的距离等于 $OH+HK$，又因为 $OH=HK=HJ$，所以三角形 $OJK$ 为曼哈顿等边三角形。因为线段 $OL$ 是一条倾角为 $45°$ 的线段，所以在这条线段上的每一个点的坐标是由 $O$ 的 $X$ 坐标 $+len$，$Y$ 坐标 $-len$ 变换而来的，所以这条线段上的任意点到 $J$ 和 $K$ 的距离不变。证毕。

所以我们可以枚举 $O$ 点和 $OH$ 的长度 $len$，那么假设 $O$ 的坐标为 $(x,y)$，则 $L$ 坐标为 $(x+len,y-len)$，那么 $J$ 和 $K$ 的坐标分别为 $J(x+len,y+len),K(x+2\times len,y)$。所以我们只需要预先处理出每一条斜 $45°$ 的直线的前缀和，即可快速求出贡献。

下面是代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=701;
int n,a[N][N],f[N][N],b[N][N],ans,tot;
struct tt{
	int x,y;
}e[N*N];
void turn(){
	memcpy(b,a,sizeof(b));
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[j][i]=b[n-i+1][j];
}
void solve(){
	tot=0;
	memset(f,0,sizeof(f));
	for(int i=1;i<=2*n;i++)for(int j=1;j<=2*n;j++)f[i][j]=f[i-1][j+1]+a[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(a[i][j]==1)e[++tot].x=i,e[tot].y=j;
	for(int i=1;i<=tot;i++){
		for(int j=1;j<=n;j++){
			int xa=e[i].x,ya=e[i].y;
			int xb=e[i].x+j,yb=e[i].y-j;
			if(xb>n||yb<1)break;
			if(a[xb][yb]==0)continue;
			ans+=f[xa+2*j][ya]-f[xa+j][ya+j];
		}
	}
}
int main(){
	scanf("%d",&n);
	getchar();
	for(int i=1;i<=n;i++){
		string s;
		getline(cin,s);
		for(int j=0;j<s.size();j++)if(s[j]=='*')a[i][j+1]=1;
	}
	for(int i=1;i<=4;i++){
		solve();
		turn();
	}
	printf("%d",ans);
}
```

---

## 作者：feecle6418 (赞：1)

结论：每个（曼哈顿距离意义下）正三角形 $ABC$ 都存在一点外心 $O$，使 $OA,OB$ 分别与 $x,y$ 轴平行，且 $OA=OB=OC$。

因此我们枚举 $O$ 的位置和 $OA$ 的长度，预处理出每一条斜线上可用点个数的前缀和，则 $C$ 一定在线段 $AB$ 关于 $O$ 的对称线段上，用预处理好的前缀和相减就得到 $C$ 的可能位置数。

以上操作需要重复四次以适应各个不同方向。注意，为了避免在端点处算重，需要每次恰好不算一个端点。同时为了避免数组越界，可以先将所有下标向后平移 $300$ 位。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=0,s[905][905];
char str[905][905],s2[905][905];
void Work(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			s2[j+300][n-i+1+300]=str[i+300][j+300];
		}
	}
	memset(s,0,sizeof(s)),memcpy(str,s2,sizeof(s2));
	for(int i=1;i<=900;i++){//(1,i)开始
		for(int j=1;j<=i;j++)s[j][i+1-j]=s[j-1][i+2-j]+(str[j][i+1-j]=='*');
	}
	for(int i=2;i<=900;i++){//(i,n)开始 
		for(int j=i;j<=900;j++)s[j][i+900-j]=s[j-1][i+900-j+1]+(str[j][i+900-j]=='*');
	}
	for(int i=301;i<=300+n;i++){
		for(int j=301;j<=300+n;j++){//枚举中心和左，上角 
			for(int k=j-1;k>=301&&i-j+k>=301;k--){
				if(str[i][k]^'*'||str[i-j+k][j]^'*')continue;
				ans+=s[i+j-k][j]-s[i][2*j-k];
			} 
		}
	}
}
int main(){
	cin>>n;
	for(int i=301;i<=300+n;i++)cin>>str[i]+301;
	for(int i=1;i<=4;i++)Work();
	cout<<ans;
}
```

---

## 作者：ELECTRODE_kaf (赞：0)

本题解中称牛为“点”，$D(A,B)$ 表示点 $A$ 与点 $B$ 的曼哈顿距离。

先讲做法再讲成立的理由。

### 做法

![](https://cdn.luogu.com.cn/upload/image_hosting/owx1w6f0.png)

枚举两个连线平行于 $y=x$ 的点（图中黑点），则图中红线范围内的点都符合要求，用前缀和累加。

每次旋转图形 $90°$，对 $4$ 种方向都计算一遍。

### 正确性说明

首先考虑一对点 $A,B$，对于 $A$ 来说，满足 $D(A,B)=D(A,C)$ 的点一定在两条平行于 $y=x$ 的直线 $l_1,l_2$ 上。对 $B$ 同理，存在 $l_3,l_4$。但是只有在 $AB$ 连线平行于 $y=x$ 时 $l_1$ 与 $l_3$；$l_2$ 与 $l_4$ 才会重合，即存在“等边三角形”。但上述情况在各种角度下均成立，故累加时需要旋转。

细节：红线的两个端点应该只计算一个，因为另一个可以和两个黑点中的一个作为新的黑点，算进去的这个红点仍作为红点，这样会在另一种角度中被认为是一种新的方案。前缀和注意溢出问题。

```cpp
const ll N = 500;
ll n, ps[N][N], ans;
bool a[N][N], _a[N][N];
vector<pll> v;

ll Ps(ll x, ll y) {
	if (x > n) {
		y += x - n;
		x = n;
	}
	elif(x < 1) {
		y -= 1 - x;
		x = 1;
	}

	if (y >= 1 and y <= n)
		return ps[x][y];
	else
		return 0;
}

int main() {
	cin >> n;

	rep(i, 1, n) {
		rep(j, 1, n) {
			char in;
			cin >> in;
			a[i][j] = in == '*';
		}
	}

	rep(c, 1, 4) {
		v.clear();
		memset(ps, 0, sizeof(ps));

		rep(i, 1, n) {
			rep(j, 1, n) {
				if (a[i][j])
					v.pb({i, j});
			}
		}
		rep(i, 1, n) {
			rep(j, 1, n) ps[i][j] = a[i][j] + ps[i - 1][j + 1];//右上角方向的前缀和
		}

		for (pll i : v) {
			rep(j, 1, n) {
				//枚举纵向距离 j
				
				ll ii = i.fi - j, jj = i.se + j;

				if (ii<1 or jj>n or a[ii][jj] == 0)
					ctn;

				ans += Ps(i.fi + j, i.se + j) - Ps(i.fi, i.se + j + j);
			}
		}

		rep(i, 1, n) {
			rep(j, 1, n) _a[i][j] = a[i][j];
		}
		
		//顺时针旋转 90°
		for (ll i1 = 1, j2 = n; i1 <= n; i1++, j2--) {
			for (ll j1 = 1, i2 = 1; j1 <= n; j1++, i2++)
				a[i1][j1] = _a[i2][j2];
		}
	}

	cout << ans;
}
```

代码宏定义在我个人空间自取。

---

## 作者：Nasaepa (赞：0)

~~学校 vp [USACO20FEB] P 组唯一一道切的题~~。

---

看到曼哈顿距离第一反应就是转成切比雪夫距离，在原图上 $(x,y)$ 上有一点则对应新图上 $(x-y+n,x+y)$ 上有一点，第一维加上 $n$ 是为了避免处理负数，此时讨论新图。认为新图上的点第一维越小越靠上，第二维越小越靠左。

通过打表发现一个等边三角形一定有两个点在同一横线上或者同一竖线上。先考虑这两个点在同一横线上且第三个点在这两个点上面的情况。先枚举其中靠右的点并在其左边再枚举一个点，设右边的点位置为 $(i,j)$ 左边的点的位置为 $(i,k)$ 则可知第三个点的第一维坐标为 $i - j + k$ ，设这个值为 $p$ 。此时考虑第三个点第二维的坐标，发现 $(p,k),(p,k+1),\dots,(p,j-1),(p,j)$ 上的点都可以成为等边三角形的第三点。用前缀和维护这些点的数量。

把图翻转一下就可以处理其它情况，再注意一下去重，这题就做完了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define lowbit(x) (x&-x)
#define pii pair<int,int>
#define N 310
struct node{
    int x,y;
    node(const int &x_ = 0,const int &y_ = 0){x = x_,y = y_;}
}a[90010],b[90010];
int n,p,len,dn,ans;
bool qp;
char mp[N][N];
int s[N<<1][N<<1];// 数量前缀和
int f[N<<1][N<<1];

// 答案
inline void work(){
    // printf("working!\n");
    int from = 0;
    for(int i = 1;i < dn;++i){
        for(int j = 1;j < dn;++j)f[i][j] = s[i][j] = 0;
    }
    for(int i = 1;i <= len;++i)f[b[i].x][b[i].y] = 1;// printf("b x=%d y=%d\n",b[i].x,b[i].y);
    int p;
    for(int i = 1;i < dn;++i){
        for(int j = 1;j < dn;++j){
            s[i][j] = s[i][j-1] + f[i][j];
            if(!f[i][j])continue;
            // printf("f[%d][%d]\n",i,j);
            for(int k = 1;k < j;++k){
                p = i - j + k;
                if(p <= 0 || !f[i][k])continue;
                ans += f[i][j] * f[i][k] * (s[p][j-qp] - s[p][k-!qp]);
                // printf("i = %d j = %d k = %d p = %d ans = %d\n",i,j,k,p,ans);
            }
        }
    }
}

// 主函数
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> n;
    dn = 2*n+1;// 值域 + 1
    for(int i = 1;i <= n;++i){
        cin >> mp[i];
        for(int j = 1,p = 0;j <= n;++j,++p){
            if(mp[i][p] == '.')continue;
            a[++len] = node(i-j+n,i+j);
        }
    }
    // 求值
    for(int i = 1;i <= len;++i)b[i] = a[i];
    work();
    for(int i = i;i <= len;++i)b[i].x = dn - a[i].x,b[i].y = a[i].y;
    work();
    qp = 1;
    for(int i = 1;i <= len;++i)b[i].x = a[i].y,b[i].y = a[i].x;
    work();
    for(int i = 1;i <= len;++i)b[i].x = dn - a[i].y,b[i].y = a[i].x;
    work();
    cout << ans;
    return 0;
}
```

---

## 作者：Anonymely (赞：0)

对于一个曼哈顿三角形，一定存在一个点（叫做它的中点）满足：三角形其中有两个点与它 $x$ 坐标或 $y$ 坐标相等，另一个点的范围在一条直线上，且中点到三个点的曼哈顿距离相等。

枚举中点和中点到顶点的距离，预处理一条斜线前缀和即可。

需要注意的是类似于 $(x+d,y),(x,y-d),(x,y+d)$ 这样的三个点会被计算两次，还需要减掉一次。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define QwQ01AwA return 0
#define ll long long
#define look_time cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n'
template <typename T> void ckmax(T &x, const T y) {x = max(x, y);}
template <typename T> void ckmin(T &x, const T y) {x = min(x, y);}

const int N = 305;
int n;
string s[N];
bool chk(int x) {return x >= 1 && x <= 2 * n;}
int up[N * 2][N], down[N * 2][N];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i] = " " + s[i];
    for (int d = -(n - 1); d <= n - 1; d++) {
        int st = max(1, d + 1), ed = min(n, n + d);
        for (int i = st; i <= ed; i++) up[d + n][i] = up[d + n][i - 1] + (s[i][i - d] == '*');
        for (int j = ed + 1; j <= n; j++) up[d + n][j] = up[d + n][j - 1];
    }
    for (int d = 2; d <= 2 * n; d++) {
        int st = max(1, d - n), ed = min(n, d - 1);
        for (int i = st; i <= ed; i++) down[d][i] = down[d][i - 1] + (s[i][d - i] == '*');
        for (int j = ed + 1; j <= n; j++) down[d][j] = down[d][j - 1];
    }
    int ans = 0;
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            for (int d = 1; d <= n; d++) {
                if (x - d < 1) break;
                if (y - d < 1) break;
                if (s[x - d][y] == '.' || s[x][y - d] == '.') continue;
                int l = x, r = min(x + d, n);
                if (chk(x + y + d)) ans += down[x + y + d][r] - down[x + y + d][l - 1];
                if (x + d <= n && s[x + d][y] == '*') ans--;
            }
        }
    }
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            for (int d = 1; d <= n; d++) {
                if (x - d < 1) break;
                if (y + d > n) break;
                if (s[x - d][y] == '.' || s[x][y + d] == '.') continue;
                int l = x, r = min(x + d, n);
                if (chk(x - y + d + n)) ans += up[x - y + d + n][r] - up[x - y + d + n][l - 1];
                if (y - d >= 1 && s[x][y - d] == '*') ans--; 
            }
        }
    }
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            for (int d = 1; d <= n; d++) {
                if (x + d > n) break;
                if (y - d < 1) break;
                if (s[x + d][y] == '.' || s[x][y - d] == '.') continue;
                int l = max(1, x - d), r = x;
                if (chk(x - y - d + n))  ans += up[x - y - d + n][r] - up[x - y - d + n][l - 1];
                if (y + d <= n && s[x][y + d] == '*') ans--; 
            }
        }
    }
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            for (int d = 1; d <= n; d++) {
                if (x + d > n) break;
                if (y + d > n) break;
                if (s[x + d][y] == '.' || s[x][y + d] == '.') continue;
                int l = max(1, x - d), r = x;
                if (chk(x + y - d)) ans += down[x + y - d][r] - down[x + y - d][l - 1];
                if (x - d >= 1 && s[x - d][y] == '*') ans--;  
            }
        }
    }
    cout << ans << '\n';
    QwQ01AwA;
}
```

---

## 作者：ETHANK (赞：0)

**题目大意：**

给一个 $N\times N$ 的方阵，里面有若干个点，问这些点在曼哈顿距离意义下能构成多少个等边三角形？

数据范围：$1\le N\le 300$ .

> 知识储备：前缀和，曼哈顿距离

> 题目难度：提高+/省选-

**解析：**

*（曼哈顿距离与切比雪夫距离的互相转化是关键思想。）*

先构造几个等边三角形，不难发现有一条边一定与坐标轴成 $45^\circ$ 度角。固定这条边找第三点，发现第三点一定在以这条边为边长的正方形上，且在这条边的对边。比如对于 $A(0,2),B(2,0)$ ，若 $C$ 在 $AB$ 上方，能构成等边三角形的 $C$ 只能在 $(4,2),(3,3),(2,4)$ 这些位置。这个结论可以通过曼哈顿距离转切比雪夫距离更加方便的得出。

有了这个结论，我们可以通过前缀和处理每个斜线上的点数，这样对于每个斜边 $AB$ 都可以 $O(1)$ 算出满足条件的 $C$ 。对两种斜线都要算一次，同时也要注意去掉重复情况，剩下的简单枚举即可。

时间复杂度：$O(N^3)$ .

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const int N=605;
int n,a[N][N],b[N][N];
ll ans;
char s[N];
int main(){
    n=read();
    rep(i,1,n){
        scanf("%s",s+1);
        rep(j,1,n){//转切比雪夫距离
            if(s[j]=='*')a[i+j-1][i-j+n]=1;
        }
    }
    n*=2;
    rep(i,1,n)rep(j,1,n){
        b[i][j]=b[i][j-1]+a[i][j];
    }
    rep(i,1,n)rep(j,1,n)if(a[i][j]){
        rep(k,j+1,n)if(a[i][k]){
            int dis=k-j;
            if(i-dis>=1)ans+=b[i-dis][k]-b[i-dis][j-1];
            if(i+dis<=n)ans+=b[i+dis][k]-b[i+dis][j-1];
        }
    }
    rep(i,1,n)rep(j,1,n){
        b[i][j]=b[i-1][j]+a[i][j];
    }
    rep(i,1,n)rep(j,1,n)if(a[j][i]){
        rep(k,j+1,n)if(a[k][i]){
            int dis=k-j;
            //去掉端点情况
            if(i-dis>=1)ans+=b[k-1][i-dis]-b[j][i-dis];
            if(i+dis<=n)ans+=b[k-1][i+dis]-b[j][i+dis];
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

 







---


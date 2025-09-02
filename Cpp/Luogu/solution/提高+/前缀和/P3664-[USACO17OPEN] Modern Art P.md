# [USACO17OPEN] Modern Art P

## 题目描述

世界各地的艺术评论家最近才开始认识到伟大的奶牛画家 Picowso 的创作天才。

Picowso 以一种非常独特的方式作画。她从一个 $N \times N$ 的空白画布开始，画布用一个 $N \times N$ 的零网格表示，其中零表示画布的一个空单元格。然后她在画布上绘制 $N^2$ 个矩形，每个矩形使用 $N^2$ 种颜色中的一种（方便地用编号 $1 \ldots N^2$ 标识）。例如，她可能首先用颜色 2 绘制一个矩形，得到以下中间画布：

```
2 2 2 0

2 2 2 0

2 2 2 0

0 0 0 0
```

然后她可能用颜色 7 绘制一个矩形：

```
2 2 2 0

2 7 7 7

2 7 7 7

0 0 0 0
```

接着她可能用颜色 3 绘制一个小矩形：

```
2 2 3 0

2 7 3 7

2 7 7 7

0 0 0 0
```

每个矩形的边都与画布的边缘平行，矩形可以大到整个画布，也可以小到一个单元格。每种颜色从 $1 \ldots N^2$ 恰好使用一次，尽管后来的颜色可能会完全覆盖一些先前的颜色。

给定画布的最终状态，请计算有多少种颜色可能是第一个被绘制的。

## 说明/提示

在这个例子中，颜色 2 可能是第一个被绘制的。颜色 3 显然必须在颜色 7 之后绘制，而颜色 7 显然必须在颜色 2 之后绘制。由于我们没有看到其他颜色，我们推断它们也可能是第一个被绘制的。

## 样例 #1

### 输入

```
4
2 2 3 0
2 7 3 7
2 7 7 7
0 0 0 0```

### 输出

```
14```

# 题解

## 作者：Nero_Claudius (赞：8)

### 思路

这道题要求求出可能被第一个画的颜色的数量。

正向思维明显不好求，因为可能存在被完全覆盖的颜色（事实上也是这样的）。

因此我们不妨逆向思维：求出所有肯定不是第一个画的颜色数量，然后用总数$n^2$减，剩余的即为答案。

那么，不能成为第一个画的颜色有什么特征呢？

可以想到，如果一种颜色盖住了另一种颜色，那么它肯定不是第一个画的。

那么直观的思路是：我们假定图中给出的颜色即为其真实大小，然后对每一种出现的颜色占据的区域$+1$，最后统计所有的格子，如果一个格子上出现的颜色数量大于$1$中，那么最上层的颜色必然不能成为第一个画的颜色。

暴力维护显然不行，因此我们可以考虑使用二维前缀和。

这里有两个细节需要注意：

1. 为什么不用知道真实颜色面积就可以有正确性：

2. 假如能见得只有一种颜色的特判。

对于第一个，很多人在观察样例的时候可能会产生这样的疑问：按照这个思路，样例中$2$覆盖的是$2*3$，但事实上覆盖的是$3*3$，为什么不会错呢？

产生这种想法是因为题目说明了样例的形成原因，但事实上完全可以采用与题目不同的覆盖，来达到同样的结果。因此，仅根据最后结果假定面积才是正确的。

对于第二个，我第一次提交就$WA$在了$test3$，原因是对于只有一种颜色的情况程序发现没有任何一个格子的颜色数量大于$1$，也就是所有格子都能是第一个放的了。

然而我们知道所有颜色都必定被画了，所以只有一种颜色的情况必定是它覆盖住了其他所有颜色，因此这种颜色不能成为第一个放的。

------------

### 代码

`272ms 32124kb`

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace StandardIO {

	template<typename T>inline void read (T &x) {
		x=0;T f=1;char c=getchar();
		for (; c<'0'||c>'9'; c=getchar()) if (c=='-') f=-1;
		for (; c>='0'&&c<='9'; c=getchar()) x=x*10+c-'0';
		x*=f;
	}

	template<typename T>inline void write (T x) {
		if (x<0) putchar('-'),x*=-1;
		if (x>=10) write(x/10);
		putchar(x%10+'0');
	}

}

using namespace StandardIO;

namespace Fate {
	
	const int N=1010;
	const int INF=0x3f3f3f3f;
	
	int n,cnt,ans;
	int mp[N][N];
	int border[N*N][4],pre[N][N],sum[N][N],flag[N*N];

	inline void Stay_Night () {
		read(n);
		for (register int i=1; i<=n*n; ++i) {
			border[i][0]=border[i][1]=INF;
		}
		for (register int i=1; i<=n; ++i) {
			for (register int j=1; j<=n; ++j) {
				read(mp[i][j]);
				if (!mp[i][j]) continue;
				if (border[mp[i][j]][0]==INF) ++cnt;
				border[mp[i][j]][0]=min(border[mp[i][j]][0],i);
				border[mp[i][j]][1]=min(border[mp[i][j]][1],j);
				border[mp[i][j]][2]=max(border[mp[i][j]][2],i);
				border[mp[i][j]][3]=max(border[mp[i][j]][3],j);
			}
		}
		for (register int i=1; i<=n*n; ++i) {
			if (border[i][0]!=INF) {
				pre[border[i][0]][border[i][1]]++;
				pre[border[i][2]+1][border[i][3]+1]++;
				pre[border[i][0]][border[i][3]+1]--;
				pre[border[i][2]+1][border[i][1]]--;
			}
		}
		for (register int i=1; i<=n; ++i) {
			for (register int j=1; j<=n; ++j) {
				sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+pre[i][j];
			}
		}
		for (register int i=1; i<=n; ++i) {
			for (register int j=1; j<=n; ++j) {
				if (mp[i][j]&&sum[i][j]>1&&flag[mp[i][j]]==0) {
					++ans,flag[mp[i][j]]=1;
				}
			}
		}
		if (n!=1&&cnt==1) ++ans;
		write(n*n-ans);
	}
	
}

int main () {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	Fate::Stay_Night();
}

```

---

## 作者：yxy666 (赞：7)

题意：给我们一个 n*n 的矩阵，每次都取一种不同的颜色并在上面选取一个矩阵覆盖，给我们最终的序列，求第一次覆盖的颜色有几种可能。

分析：以样例为例，看下图

![](https://cdn.luogu.com.cn/upload/image_hosting/7c00ee2z.png)

对于颜色 2（红色），它原本的矩阵被颜色 7（蓝色）给覆盖了，那么 颜色7 就绝对不可能是第一个。因为一种颜色只能画一次且只能是矩阵，如果 颜色7 第一个，那么给出的最终形态就不合法了。同理，对于颜色 7，它被颜色 3（黄色）覆盖，所以颜色 3 就绝对不不可能是第一个。

定义颜色 A  破坏颜色 B 的意思为颜色 A 覆盖了颜色 B，那么我们就可以得到下面一串思路。


枚举颜色

看一下这个矩阵是否损坏，损坏了又是谁损坏的 

若损坏过，将损坏别人的小子给标记起来

最后没被标记过的就是答案。



code :
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1001;
int n,m,ans,a[maxn][maxn],p[maxn*maxn];
bool vis[maxn*maxn],t[maxn*maxn];
struct yxy{
	int lx,rx,ly,ry;
}b[maxn*maxn];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}//快读
int main(){
	n=read();
	for(int i=1;i<=n*n;i++)b[i].lx=b[i].ly=(1<<30);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
		a[i][j]=read();
		b[a[i][j]].lx=min(b[a[i][j]].lx,i);
		b[a[i][j]].ly=min(b[a[i][j]].ly,j);
		b[a[i][j]].rx=max(b[a[i][j]].rx,i);
		b[a[i][j]].ry=max(b[a[i][j]].ry,j);
		if(!t[a[i][j]]&&a[i][j])t[a[i][j]]=1,m++,p[m]=a[i][j];
	}//记录每种颜色的左上角，右下角
	for(int i=1;i<=m;i++){
		for(int ii=b[p[i]].lx;ii<=b[p[i]].rx;ii++)
		for(int jj=b[p[i]].ly;jj<=b[p[i]].ry;jj++)
		if(a[ii][jj]!=p[i])vis[a[ii][jj]]=1;
	}//将破坏别人的小子标为1
	for(int i=1;i<=n*n;i++)if(!vis[i])ans++;//没被标过即为答案
	if(m==1)ans--; //特判，如果只有一种颜色，那么我当前这种颜色是不可以，而其他颜色都可以
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：MSqwq (赞：3)

## 知识点：差分  
这题挺毒瘤的，就单是题意都不是很好理解....  
题意：给你一个$n*n$的矩阵，有$n*n$个颜色来涂色，之中可能有覆盖，问其中有哪些颜色可以作为第一个涂色的  
题解：  
思考一下，如果直接找哪些作为第一个涂色的，是不是有点困难，所以我们容斥一下，把不可以作为第一个的颜色求出来，再用$n*n$的总数来减就可以了  

那么哪些颜色不能作为第一个呢：  
$1.$如果只有一个颜色则一定不为第一个  
$2.$和另一个矩阵有交集，且在上面  

好！特征已经明白了，接下来就是怎么找？怎么用代码实现？  
显而易见的方法是爆搜嘛，单是明显会挂掉，所以不考虑  
然后思考一下，什么东西可以满足求和还适用于矩阵？

## 二维差分！二维差分！二维差分！二维差分！  
好想到了这里就已经成功一半了  
接下来你需要去思考如何维护差分数组  

我们可以找出每个矩阵大概的轮廓（即上下左右四个点）  
参照一维差分的思想，我们可以在一个矩形的左上角$+1$，右下角$+1$，右边$-1$,下边$-1$  
这样处理了之后，一个点前缀和就是这个点被覆盖的次数  
需要注意的是如果只看得见一个颜色，怎么处理  
代码如下：
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a[1010][1010],sum[1010][1010],f[1000010][8],v[1000010]; 
ll cnt,ans;
void insert(ll x,ll y,ll z)
{
	if(f[z][3]==0)cnt++;
	if(x<f[z][1])f[z][1]=x;
	if(y<f[z][2])f[z][2]=y;
	if(x+1>f[z][3])f[z][3]=x+1;
	if(y+1>f[z][4])f[z][4]=y+1;
}
void solve()
{
	for(int i=0;i<=n*n;i++)
	{
		f[i][1]=1e9;
		f[i][2]=1e9;
		f[i][3]=0;
		f[i][4]=0;
	}	
}
void sum_()
{
	for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
    }
}
int main()
{
	scanf("%lld",&n);
	solve();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%lld",&a[i][j]);
			if(a[i][j]!=0)insert(i,j,a[i][j]);
		}
	}
	for(int i=1;i<=n*n;i++)
	{
		if(f[i][1]==1e9||f[i][3]==0)continue;
		sum[f[i][1]][f[i][2]]++;
		sum[f[i][3]][f[i][4]]++;
		sum[f[i][1]][f[i][4]]--;
		sum[f[i][3]][f[i][2]]--;
	}
	sum_();
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=n;j++)
    	{
    		if(a[i][j]!=0&&sum[i][j]>1&&v[a[i][j]]==0)
    		{
    			ans++;
    			v[a[i][j]]=1;
			}
		}
	}
	if(n>1&&cnt==1)printf("%lld",n*n-1);
	else printf("%lld",n*n-ans);
}
```


---

## 作者：肖翔 (赞：2)

# 前置知识

- 二维差分

- 最好能理解矩阵覆盖和求交

# Solution


此处先讨论矩形相交的情况。

涂的颜色为单独的矩形，或没出现过的颜色等下单独考虑。

![](https://cdn.luogu.com.cn/upload/image_hosting/ve0o42cr.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

对于绿色矩形和黄色矩形，考虑它们的相交部分。

若相交部分为黄色，那么黄色一定在绿色的上面。

![](https://cdn.luogu.com.cn/upload/image_hosting/zhu711pz.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

该图同理，由相交部分的颜色情况可推知，黄在红上面，蓝在黄上面，蓝在红上面。

这种情况推广开来，发现对于颜色为 $col_{i}$ 的矩形，在它与其他矩阵相交的部分中，有某些部分颜色为 $col_{i}$，该颜色就一定在其他颜色的上面，即在其他颜色后面涂，不能最早涂。

如上图的黄色矩阵与红色矩阵相交部分为黄色，黄色就一定在红色上面，不可最早涂，

于是有思路，找到矩阵相交部分，相交部分的颜色一定是不合法的，其他的都可以。

问题变为如何找出矩阵相交的部分。

容易想到，维护一个 $s_{i,j}$，对于每个矩阵，把其内部区域位置的 $s_{i,j}$ 加一，最终 $s_{i,j}$ 大于1的位置即为矩阵的交的部分（相当于覆盖问题）。

遍历矩阵，对于每个 ${(i,j)|s_{i,j}>1}$，把其对应的 $col_{i}$ 标记为不合法。

统计一下合法情况即可。

（可以发现，颜色成为单独矩形或没有出现，都不会被记为不合法情况，所以无需对其单独处理，一并统计即可）。

我们输入的同时处理出每种矩形的左上角坐标与右下角坐标再维护 $s_{i,j}$。


发现直接维护 $s_{i,j}$ 是 $O(mn^2)$ 的，但我们只用到了二维的区间加，对所有矩阵操作完后查询一次。容易想到二维差分。使用二维差分复杂度即可降为 $O(m+n^2)$，可以通过本题。
# Tips：

一：

当出现
```cpp
4
0 0 0 0
0 1 1 0
0 1 1 0
0 0 0 0

```
这样的数据时，可以发现合法情况数应为 $15$，但程序统计为了 $16$。

那是因为我们以上讨论没有涉及矩阵被完全覆盖的问题。

记 $m$ 为颜色种数，当 $m=1$   且   $n>1$ 时最上面的颜色其实是非法的。

但因为下面的颜色被其完全覆盖，没有办法求出矩阵交的部分。

所以这种情况需要处理。
 
然而当 $m>1$ 时，则一定存在一种构造方案，使得按上述方法统计出来的结果合法。

比如：

```cpp
4

0 2 2 2
0 2 2 2
0 2 2 2
1 0 0 0
```
可以让 $3$ ~ $16$ 被 $2$ 的矩形完全覆盖，做到先涂 $1$。

也可以让他们被 $1$ 的矩形完全覆盖，做到先涂 $ 2 $。

至于先涂 $3$ ~ $16$，则是十分容易构造的平凡情况。

其他局面同理。

二：

用矩形维护 $s_{i,j}$ 时，先判断这个矩形是否存在。


# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int rd(){
	int x=0;char c=getchar();int f=1;
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*f;
}
const int maxn=1e3+10;
int n;
int s1[maxn][maxn],s2[maxn][maxn],ans[maxn][maxn];
//ans原数组
//s1一次差分
//s2二次差分
//我的差分理解法是两次差分加两次前缀和，可以看囧仙的日报
inline void up2(int x1,int y1,int x2,int y2,int val){
	s2[x1][y1]+=val;
	s2[x2+1][y1]-=val;
	s2[x1][y2+1]-=val;
	s2[x2+1][y2+1]+=val;
}
int p[maxn][maxn];
bool vis[maxn*maxn]; 

int bx[maxn*maxn],by[maxn*maxn],sx[maxn*maxn],sy[maxn*maxn];
//big_x  big_y   small_x  small_y
//维护矩阵位置
inline void goback(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			s1[i][j]=s1[i][j-1]+s2[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ans[i][j]=ans[i-1][j]+s1[i][j];
		}
	}
}
//差分后，前缀和还原出原数组
const int inf=0x7f7f7f7f;
int sum;
int main(){
	int val;
	n=rd();
	for(int i=1;i<=n*n;i++){
		by[i]=bx[i]=-inf;
		sx[i]=sy[i]=inf;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			val=rd();p[i][j]=val;vis[val]=1;
			bx[val]=max(bx[val],i);
			by[val]=max(by[val],j);
			sx[val]=min(sx[val],i);
			sy[val]=min(sy[val],j);
		}
	}
	for(int i=1;i<=n*n;i++){
		if(vis[i]) 
		up2(sx[i],sy[i],bx[i],by[i],1),sum++;
	}
	goback();
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(ans[i][j]>1)vis[p[i][j]]=1;
		}
	}
	int f=0;
	for(int i=1;i<=n*n;i++){
		if(!vis[i])f++;
	}
   //处理m==1的情况
	if(sum==1)f--;
	cout<<f;
	return 0;		
}
```



---

## 作者：liudl (赞：2)

此题，可能有巨佬一眼就看出来了是二阶差分，反正蒟蒻我做不到。
还是老老实实一步步分析吧
### Step 1 有哪些数可能出现在第一个
此题怎么做呢？我最先想到的，就是暴力搜索，一个一个还原填数时选的矩形，进而推出哪些矩形可能是第一个填上去的。

等等，为什么样例输出里有这么多个数？

其实，这些就是我们本题可以第一个出现的数中的一类——没有出现在图上的数。

这类数，有可能是被后来填上来的数完全覆盖了，所以我们压根看不到它们。

那么，出现在图上的数又有哪些可能是第一个出现的数呢？

其实，这就抽象成了一个放矩阵的问题。如果两个矩阵之间有重叠部分，那么后来的数一定会覆盖先填上数，所以，矩阵重叠区域我们现在看到的数就一定不可能是第一个出现的。

### Step 2 暴力搜索
接下来的问题就是如何还原矩阵了。对此，我们可以枚举每个数出现的极端位置，由于不能选已经使用过的数，所以相同的数字一定属于同一个矩形。

求出每个数出现的极右上位置和极左下，我们就可以得知这个矩形的对角线，进而还原矩形了

我们新开一个矩阵B，对于每个矩阵，我们都将其范围内的B位置上的数++

最后，如果原图上有矩阵重叠区域，那么B矩阵对应位置的数就会>=2。

然后我们就可以得出答案了。

### Step 3 特殊数据
来看看下面这组数据

4

0 0 0 0

0 1 1 0

0 1 1 0

0 0 0 0

按照我们上面推的结论，该图答案应该为16

但是，我们肉眼目测答案很明显是15，因为1不可能出现在第一位。

对于这种图上除了0之外只有1个数的情况，我们需要特判，直接输出$N^2-1$即可

好了，到了这里我们已经可以喜提AC了（~~数据有点水~~）但如果你想了解优化，可以继续往下看。

### Step 4 二阶差分优化
对于一个矩阵实现快速区间修改，这让我们很自然地想到了二阶差分。

所以，我们上面在修改B矩阵的时候，可以加上二阶差分优化。

### Step 5 放码
```cpp
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[1008][1008],Max[1000008][2],Min[1000008][2],n,ans,cnt,cnt1,f[1000008];
bool ff[1000008],fff[1000008];
int b[1008][1008];
char buf[1<<20],*p1,*p2;  
#define GC (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)  
inline ll read() { char t=GC; ll x=0; while(!isdigit(t)) t=GC; while(isdigit(t)) x=x*10+t-48,t=GC; return x; }
void init()
{
    for(int i=1;i<=n*n;i++)
    Min[i][0]=Min[i][1]=1e9+7;
}
int main()
{
    n=read();
    init();
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    {
        a[i][j]=read();
        if(a[i][j]!=0)
        {
            Max[a[i][j]][0]=max((int)i,Max[a[i][j]][0]);
            Max[a[i][j]][1]=max((int)j,Max[a[i][j]][1]);
            Min[a[i][j]][0]=min((int)i,Min[a[i][j]][0]);
            Min[a[i][j]][1]=min((int)j,Min[a[i][j]][1]);
            if(!ff[a[i][j]])
            cnt++,f[cnt]=a[i][j];
            ff[a[i][j]]=true;
        }
    }
    if(cnt==1)
    {
        cout<<n*n-1;
        return 0;
    }
    for(int i=1;i<=cnt;i++)
    for(int j=Min[f[i]][0];j<=Max[f[i]][0];j++)
    for(int k=Min[f[i]][1];k<=Max[f[i]][1];k++)
    b[j][k]++;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    {
        if(b[i][j]>=2&&a[i][j]!=0)
        {
            if(!fff[a[i][j]])
            {
                fff[a[i][j]]=true;
                cnt1++;
                //cout<<i<<" "<<j<<" "<<a[i][j]<<endl;
            }
        }
    }   
    ans=n*n-cnt1;
    cout<<ans;
    return 0;
}
```

祝各位巨佬们早日AK

---

## 作者：冒泡ioa (赞：1)

欢迎来[我的博客](http://bubbleioa.top/usaco17openmodern-art/)
# 题解
似乎没人写差分的代码，我这里就稍微介绍一下。  
首先呢，这道题目很毒瘤，我花了好大功夫才读懂题目，无论它给你的矩阵里面有多少种颜色，它一共还是有[latex]N^2[/latex]种颜色，所以显然我们找不合法的颜色就行。  
观察样例我们可以发现，2颜色的矩阵显然被7的覆盖了一部分，7肯定不能第一个涂，3又把7给覆盖掉了，3也不能第一个涂。  
那么我们可以把问题转化成，有x个矩形（有些被覆盖了的矩形左上角右下角还是可以算到的），求重叠部分上面的矩形的颜色总数。  

当然用暴力就可以莽过去，但是遇到类似的问题用二维前缀和+二维差分显然是更优的。  
参照一维差分的思想，我们可以在一个矩形的左上角+1，右下角+1，右边-1,下边-1  
样例的差分数组：
```
 1  0  0 -1
 0  1  0  0
 0  0 -1  1
-1 -1  1  0
```
这样子统计前缀和后，每个点的前缀和的值就是该点被覆盖的次数。  
细节见代码注释。  
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=1005,inf=0x7fffffff;

int pos[MAXN*MAXN][4],ma[MAXN][MAXN],col,ans,sum[MAXN][MAXN],cnt;
bool fla[MAXN*MAXN];

int main(){
    int n;
    cin>>n;
    for(int i=0;i<=n*n;i++){//初始化
        pos[i][0]=pos[i][1]=inf,pos[i][2]=pos[i][3]=0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>col;
            ma[i][j]=col;
            if(col){//非0
                if(pos[col][2]==0)cnt++;
                if(i<pos[col][0])pos[col][0]=i;//矩形上边边界
                if(j<pos[col][1])pos[col][1]=j;//矩形左边边界
                if(i+1>pos[col][2])pos[col][2]=i+1;//矩形下边边界+1
                if(j+1>pos[col][3])pos[col][3]=j+1;//矩形右边边界+1
            }
        }
    }
    for(int i=1;i<=n*n;i++){
        if(pos[i][0]==inf||pos[i][2]==0)continue;//枚举出现过的颜色
        sum[pos[i][0]][pos[i][1]]++;//上面说的
        sum[pos[i][2]][pos[i][3]]++;
        sum[pos[i][0]][pos[i][3]]--;
        sum[pos[i][2]][pos[i][1]]--;
    }
	//前缀和
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            sum[i][j]+=sum[i][j-1];
        }
    }
    for(int j=1;j<=n;j++){
        for(int i=1;i<=n;i++){
            sum[i][j]+=sum[i-1][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(ma[i][j]&&sum[i][j]>1&&fla[ma[i][j]]==0){//每种颜色只能贡献一次答案
                ans++,fla[ma[i][j]]=1;
            }
        }
    }
    if(n!=1&&cnt==1)ans++;
    printf("%d\n",n*n-ans);
    return 0;
} 

```

---

## 作者：曹老师 (赞：1)

~~不用差分 不用矩阵 不用前缀和~~

**知识点：暴力 模拟**

涂颜色的必定是一个矩形

因此我们可以根据最后的状态判断出矩形的边界

再跑一遍每一个颜色的每一个矩形

打上标记 **如果标记>1 表示肯定有两种或以上颜色在这里涂过**

因此这个位置的最后一种颜色就要去掉（放到del数组中

然后答案就出来了~

**注意：特殊情况 最后的状态只有一种颜色 其余全部为0**（90分未AC的原因

输入
4
0 0 0 0
0 1 1 0
0 1 1 0
0 0 0 0
输出
15

你看是不是答案是16？ 这就需要特判一下

我开了vis数组（貌似麻烦了 特判输出 ans-1 就行了

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#define MAXN 100005
#define LL long long
#define INF 2147483647
#define MOD 1000000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
#define debug(x) cout<<x<<endl;
using namespace std;
const int L=1005;
bool vis[L*L];
int n,w[L][L],t[L][L],ans,del[L*L],cnt,s[L*L],x[L*L],z[L*L],y[L*L]; 
int main()
{
	scanf("%d",&n);
	ans=n*n;
	memset(s,0x3f,sizeof(s));
	memset(z,0x3f,sizeof(z));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&w[i][j]);
			if(w[i][j]&&!vis[w[i][j]])
			{
				vis[w[i][j]]=1;
				cnt++;
			}
			s[w[i][j]]=min(s[w[i][j]],i);
			x[w[i][j]]=max(x[w[i][j]],i);
			z[w[i][j]]=min(z[w[i][j]],j);
			y[w[i][j]]=max(y[w[i][j]],j);
		}
	if(cnt==1&&n!=1)
	{
		printf("%d",ans-1);
		return 0;
	}
	for(int i=1;i<=n*n;i++)
		for(int j=s[i];j<=x[i];j++)
			for(int k=z[i];k<=y[i];k++)
					t[j][k]++;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(t[i][j]>1&&w[i][j])
				del[w[i][j]]=1;
	for(int i=1;i<=n*n;i++)
		if(del[i])
			ans--;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：kczno1 (赞：1)

一个颜色不能被第一个画的情况有两种。

1
存在其他颜色，被它截成非矩形。

2
图中只存在一种颜色。

那么这种颜色不能被第一个画。(除非总共就只有一种颜色)


考虑对每个被截成非矩形的颜色，

求出上下左右的边界，

之后标记这里面的所有非同色的点。

用差分来实现矩形加即可。


```cpp
#include<bits/stdc++.h>

void chmin(int &x,int y)
{
    if(x>y)x=y;
}
void chmax(int &x,int y)
{
    if(x<y)x=y;
}

const int N=1e3+5;
int n,i,j;
int ad[N][N];
struct state
{
int up,down,left,right;
void upd(int x,int y)
{
    if(!up) { left=right=y;up=down=x; }
    else
    {
        chmin(up,x);
        chmax(down,x);
        chmin(left,y);
        chmax(right,y);
    }
}
bool add()
{
    if(!up)return 0;
    ++ad[up][left];
    ++ad[down+1][right+1];
    --ad[down+1][left];
    --ad[up][right+1];
    return 1;
}
}s[N*N];
bool mark[N*N];
int col[N][N];

int main()
{
    freopen("1.in","r",stdin);
    scanf("%d",&n);
    for(i=1;i<=n;++i)
    for(j=1;j<=n;++j)
    { scanf("%d",col[i]+j);
      s[col[i][j]].upd(i,j);
    }
    
    int cnt=0;
    for(i=1;i<=n*n;++i) if(s[i].add())++cnt;
    if(cnt==1&&n>1) {printf("%d\n",n*n-1);return 0;}
    
    for(i=1;i<=n;++i)
    for(j=1;j<=n;++j)
     ad[i][j]+=ad[i-1][j];
    for(i=1;i<=n;++i)
    for(j=1;j<=n;++j)
     ad[i][j]+=ad[i][j-1];
    
    for(i=1;i<=n;++i)
    for(j=1;j<=n;++j)
    if(ad[i][j]>1) 
      mark[col[i][j]]=1;
    
    int ans=n*n;
    for(i=1;i<=n*n;++i)
    if(mark[i])
     --ans;
    printf("%d\n",ans);
}
```

---

## 作者：zhzkiller (赞：0)

## 题目描述
这道题要求我们在一个二维矩阵中找出第一次可能使用的颜色个数，即被破坏或完整的不同数字矩形个数，也即 $n^2-ans$，$ans$ 为破坏其他矩形的数字个数。

## 解题思路
考虑第三种解释：用 $n^2-ans$。对于矩形的重复覆盖，我们有两个个较为常用的算法：**二维前缀和** 和 **二维差分**。我们只需要将每一个数字出现过的左上角和右下角记录下来进行差分，再从头扫一遍二维前缀和即可求出每个位置被覆盖的次数，那么如果此时该位置的次数大于 $1$ 且该位置数字是第一次出现，即可使 $ans$ 加上 $1$。最后输出 $n^2-ans$ 即可。记得特判只有一种数字出现的情况，直接输出 $n^2-1$ 即可，不然会 WA 第二个测试点。

完结撒花~

献上蒟蒻的 AC 代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1000010;

int n,k;
int a[N];
bool vis[N],v[N];
int d[N],maxx[N],maxy[N],minx[N],miny[N];
int ans,cnt,st[N];

int main()
{
	scanf("%d",&n);k=n*n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&a[(i-1)*n+j]);
			if(!a[(i-1)*n+j]) continue;
			if(!vis[a[(i-1)*n+j]])
			{
				cnt++;vis[a[(i-1)*n+j]]=true;
				minx[a[(i-1)*n+j]]=n+1,miny[a[(i-1)*n+j]]=n+1;
				st[cnt]=a[(i-1)*n+j];
			}
			maxx[a[(i-1)*n+j]]=max(maxx[a[(i-1)*n+j]],i);
			maxy[a[(i-1)*n+j]]=max(maxy[a[(i-1)*n+j]],j);
			minx[a[(i-1)*n+j]]=min(minx[a[(i-1)*n+j]],i);
			miny[a[(i-1)*n+j]]=min(miny[a[(i-1)*n+j]],j);
		}
	}
	
	if(cnt==1)
	{
		printf("%d",k-1);
		return 0;
	}
	
	for(int i=1;i<=cnt;i++)
	{
		d[(minx[st[i]]-1)*n+miny[st[i]]]++;
		d[maxx[st[i]]*n+miny[st[i]]]--;
		d[(minx[st[i]]-1)*n+maxy[st[i]]+1]--;
		d[maxx[st[i]]*n+maxy[st[i]]+1]++;
	}
	
	for(int i=1;i<=n*n;i++)
	{
		d[i]+=d[i-1]+d[i-n]-d[i-n-1];
		if(d[i]>1&&!v[a[i]])
		{
			v[a[i]]=true;
			ans++;
		}
	}
	printf("%d",k-ans);
	return 0;
}
```

## 细节处理
1.将二维序号降为一维以防止数据过大。不过本题不需要，如果遇到的是 $n \times m$ 范围时则需要该处理防止爆仓。

---

## 作者：cirnovsky (赞：0)

## 题意简述

给定一个 $n\times n$ 的矩阵，有 $n\times n$ 个内容全部为 $1,2,\cdots,n\times n$ 的子矩阵。用子矩阵覆盖大矩阵，求第一个覆盖的子矩阵的所有可能方案数。

## 题解

挺水一道题。

归纳一下，我们可以发现题目就是让我们求 $n\times n$ 减去不可能的子矩阵数。

考虑如何判断一个子矩阵不可能第一个覆盖。

容易发现一个子矩阵一旦出现在了 **本应是其他子矩阵覆盖的范围** 那么我们就可以断言这个子矩阵不可能是第一个覆盖的子矩阵。

那么如何统计呢？很简单，找出每个子矩阵的左上右下两个端点然后二维前缀和即可。

有几点需要注意一下：

- 端点被覆盖了其实是不影响的，我们只需要关注露出来的端点即可。

- 当 $n\neq 1$ 时，只有一种颜色在最上层的情况也是不可能的，需要特判一下。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 1e3 + 5;
int impossible, n, mat[MAXN][MAXN], sum[MAXN][MAXN];
int color[MAXN * MAXN][5], mark[MAXN][MAXN], vis[MAXN * MAXN], tot;

void prepare() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			scanf("%d", &mat[i][j]);
		}
	}
	for (int i = 1; i <= n * n; ++i) color[i][0] = color[i][1] = 10086001;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (mat[i][j]) {
				if (color[mat[i][j]][0] == 10086001) ++tot;
				color[mat[i][j]][0] = min(i, color[mat[i][j]][0]);
				color[mat[i][j]][1] = min(j, color[mat[i][j]][1]);
				color[mat[i][j]][2] = max(i, color[mat[i][j]][2]);
				color[mat[i][j]][3] = max(j, color[mat[i][j]][3]);
			}
		}
	}
}

void work() {
	for (int i = 1; i <= n * n; ++i) {
		if (color[i][0] ^ 10086001) {
			mark[color[i][0]][color[i][1]]++;
			mark[color[i][2] + 1][color[i][3] + 1]++;
			mark[color[i][0]][color[i][3] + 1]--;
			mark[color[i][2] + 1][color[i][1]]--;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			sum[i][j] = mark[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
		}
	}
}

void answer() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (mat[i][j] && sum[i][j] > 1 && vis[mat[i][j]] ^ 1) {
				vis[mat[i][j]] ^= 1;
				impossible++;
			}
		}
	}
	printf("%d\n", n * n - impossible - (tot == 1 && n != 1));
}

signed main() {
	prepare();
	work();
	answer();
}
```

---


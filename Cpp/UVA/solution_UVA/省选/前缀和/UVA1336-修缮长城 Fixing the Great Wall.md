# 修缮长城 Fixing the Great Wall

## 题目描述

为了简化这个问题，我们把长城看成是一条直线，每个需要修补的点都被用它离起点的距离（一个整数）标记了。GWARR被放在长城的一个随机位置上，并且可以以恒定的速度双向移动。每个点距离起点的距离，现在立即修复的花费，以及每过单位时间修复花费的增长量都已知。GWARR的工作效率极高，以至于它可以立即修复好经过的需要修复的地方。

## 说明/提示

对于$100 \%$数据有：
$1 \leq N \leq 1000, 1 \leq V \leq 100,1 \leq X \leq 500,000$；  
$1 \leq x \leq 500,000, 1 \leq c \leq 50,000, 1 \leq \Delta \leq 50,000$。

# 题解

## 作者：Durancer (赞：9)

### 前言

多次询问不清空，OI十年一场空。

### 思路

设 $f_{i,j,0/1}$
  表示处理完第 $i$ 个点到第 $j$ 个点后，停在 $i$ 点（0） ,或者停在 $j$ 点的位置时花费的最小值。

还是按照经典的区间 $dp$ 的套路，我们枚举区间的长度，并且根据递推吧左右端点给点起来，也就是所谓的填表法，转移方程在下面说的很清楚了。

转移方程是：

$$f_{i,j,0}=\operatorname{min}\begin{cases}f_{i+1,j,0}+\frac{(pos_{i+1}-pos_{i})}{v}\times Δ \\ \\f_{i+1,j,1}+\frac{(pos_{j}-pos_{i})}{v}\times Δ \end{cases}$$

$$ f_{i,j,1}=\operatorname{min}\begin{cases}f_{i,j-1,0}+\frac{(pos_{j}-pos_{i})}{v}\times Δ \\ \\f_{i,j-1,1}+\frac{(pos_{j}-pos_{j-1})}{v}\times Δ \end{cases}$$



唯一注意的是，我们需要把一开始的位置也当成一个没有花费的点加进去，并且按照位置来进行升序排列，然后就可以愉快的进行DP了。

### 代码实现

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
const double INF=0x3f3f3f3f;
const int N=1e3+9;
const int M=1e3+9;
struct node{
	double pos;//位置 
	double delt;//增长量 
	double once;//立刻修复的花费 
}wal[N];
double sum[N];
double tol;
double v;
int n,c;
int now=0;
double f[N][N][3];
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9')
	{
		if(s=='-')	
			f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=getchar(); 
	}
	return f*x;
}
bool cmp(node x,node y)
{
	return x.pos<y.pos;
}
void prepare()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			f[i][j][1]=f[i][j][0]=INF;
	
	for(int i=1;i<=n;i++)
		if(wal[i].pos==(double)c&&wal[i].once==0&&wal[i].delt==0)
		{
			now=i;
			break;
		}
	for(int i=1;i<=n;i++)
		tol+=wal[i].once; 
	//cout<<"now= "<<now<<endl;
	f[now][now][1]=0;
	f[now][now][0]=0;
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+wal[i].delt;
}
void DP()
{
	for(int len=2;len<=n;len++)
		for(int i=1;i-1+len<=n;i++)
		{
			int j=i-1+len;
			f[i][j][0]=min(f[i+1][j][0]+(wal[i+1].pos-wal[i].pos)/v*(sum[n]-sum[j]+sum[i]),
						   f[i+1][j][1]+(wal[j].pos-wal[i].pos)/v*(sum[n]-sum[j]+sum[i]));
			f[i][j][1]=min(f[i][j-1][1]+(wal[j].pos-wal[j-1].pos)/v*(sum[n]-sum[j-1]+sum[i-1]),
						   f[i][j-1][0]+(wal[j].pos-wal[i].pos)/v*(sum[n]-sum[j-1]+sum[i-1]));
//			printf("f[%d][%d][0]= %lf\n",i,j,f[i][j][0]);
//			printf("f[%d][%d][1]= %lf\n",i,j,f[i][j][1]);	
		}
	return;
}
int main()
{
	while(cin>>n)
	{
		tol=0;
		scanf("%lf",&v);
		//cout<<"v= "<<v<<endl;
		c=read();
		if(n==0) break;	
		for(int i=1;i<=n;i++)
			scanf("%lf%lf%lf",&wal[i].pos,&wal[i].once,&wal[i].delt);	
		wal[++n].pos=double(c);
		wal[n].once=0.0;
		wal[n].delt=0.0;	
		sort(wal+1,wal+1+n,cmp);
		prepare(); 
		DP();
		printf("%d\n", (int)floor(tol + min(f[1][n][0], f[1][n][1])));
	} 
	return 0;
}
```




---

## 作者：Infiltrator (赞：9)

[$\Large\color{#FFBBFF}\textit{Tian-Xing's blog}$](https://Tian-Xing.github.io)

------------

# Description

[传送门](https://www.luogu.com.cn/problem/UVA1336)

------------

# Solution

因为只要经过就会修所以最优的修缮策略是从起点开始往左或往右修一段区间，所以考虑反向区间$dp$。

设$dp_{i, j}$表示修缮完区间$[i, j]$后的时间内再修其它区间产生的花费。

那么转移时不需要考虑区间$[i, j]$，只需要考虑除了区间$[i, j]$以外的点。

发现修缮区间$[i, j]$时花费的时间会对以后要修复的点产生影响，具体的，还没有修复的那些点对答案的贡献会加上从区间$[i, j]$转移到下个区间的时间乘单位时间的代价。

所以只需计算区间和区间转移时花费的时间。

注意到修缮完一个区间后一定是在区间的左/右端点，所以可以设$dp_{i, j, 0/1}$表示当前修缮到区间$[i, j]$位于左/右端点，以后的时间内修缮完其他的点的代价。

设$s_i$表示区间$[1, i]$内的$\Delta$的和，$len_{i, j}$表示点$i$到点$j$的距离。很容易的列出$dp$式子：

$$cost = s_n - (s_j - s_{i - 1})$$

$$dp_{i, j, 0} \leftarrow dp_{i - 1, j, 0} + \frac{cost \times len_{i - 1, i}}{v}$$

$$dp_{i, j, 0} \leftarrow dp_{i, j + 1, 1} + \frac{cost \times len_{i, j + 1}}{v}$$

$$dp_{i, j, 1} \leftarrow dp_{i - 1, j, 0} + \frac{cost \times len_{i - 1, j}}{v}$$

$$dp_{i, j, 1} \leftarrow dp_{i, j + 1, 1} + \frac{cost \times len_{j, j + 1}}{v}$$

------------

# Code

```cpp
/*
    _______                       ________                        _______
   / _____ \                     / ______ \                      / _____ \
  / /     \_\  _     __     _   / /      \ \   _     __     _   / /     \_\
 | |          | |   |  |   | | | |        | | | |   |  |   | | | |
 | |          | |   |  |   | | | |     __ | | | |   |  |   | | | |
 | |       __ \  \  |  |  /  / | |     \ \| | \  \  |  |  /  / | |       __
  \ \_____/ /  \  \/ /\ \/  /   \ \_____\  /   \  \/ /\ \/  /   \ \_____/ /
   \_______/    \___/  \___/     \______/\__\   \___/  \___/     \_______/
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define db double

const int N = 1000;

int n, x;

db dp[N + 50][N + 50][2], sum[N + 50], ans, v;

struct Point {
	int pos; db zhi, delta;
} point[N + 50];

bool Cmp(Point a, Point b) {
	return a.pos < b.pos;
}

int main() {
	while (scanf("%d%lf%d", &n, &v, &x) == 3) {
		if (!n && !v && !x) return 0;
		for (int i = 1; i <= n; i++) 
			scanf("%d%lf%lf", &point[i].pos, &point[i].zhi, &point[i].delta);
		point[++n].pos = x; point[n].zhi = point[n].delta = 0.0;
		sort(point + 1, point + n + 1, Cmp);
		int pos;
		for (int i = 1; i <= n; i++) 
			if (point[i].pos == x && point[i].delta == 0.0 && point[i].zhi == 0.0) {
				pos = i;
				break;
			}
		ans = 0;
		for (int i = 1; i <= n; i++) 
			sum[i] = sum[i - 1] + point[i].delta,
			ans += point[i].zhi;
		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= n; j++)
				dp[i][j][0] = dp[i][j][1] = 1e9;
		dp[1][n][0] = dp[1][n][1] = 0.0; 
		for (int l = n - 1; l >= 1; l--)	
			for (int i = 1; i + l - 1 <= n; i++) {
				int j = i + l - 1; db cost = sum[n] - sum[j] + sum[i - 1];
				if (i - 1 >= 1) dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j][0] + cost * (db)(point[i].pos - point[i - 1].pos) / v);
				if (j + 1 <= n) dp[i][j][0] = min(dp[i][j][0], dp[i][j + 1][1] + cost * (db)(point[j + 1].pos - point[i].pos) / v);
				if (j + 1 <= n) dp[i][j][1] = min(dp[i][j][1], dp[i][j + 1][1] + cost * (db)(point[j + 1].pos - point[j].pos) / v);
				if (i - 1 >= 1) dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j][0] + cost * (db)(point[j].pos - point[i - 1].pos) / v);
			}
		printf("%d\n", (int)floor(ans + min(dp[pos][pos][0], dp[pos][pos][1])));
	}
	return 0;
}
```

---

## 作者：轻尘 (赞：6)

## 【题解】紫书例题 Fixing the Great Wall

-----------------
不明显的区间DP。

我们先贪心的思考，选取的每些数必定是一段连续的区间，于是问题就转化成了区间DP。

按照坐标排一下序，（有一点离散化的思想吧，毕竟坐标太大）。每一个位置有两种决策方案，向左走or向右走（这里的走是指走到点，不是一个一个坐标的移动）。

我们不妨设$f[i][j][k]$表示在$i$到$j$的区间，位于左（$k=0$）或右（$k=1$）端点时的最小花费。

**考虑转移：**

当向某一点移动时，对于没有走的点，花费 $cost= t\times \sum \Delta \text{未经过的点} $。

显然 $ t = \text{两点的距离} / v $

**于是状态转移方程就推出来了**

向左走：
$$f[l-1][r][0]=min(f[l-1][r][0],f[l][r][k]+cost);$$

向右走：
$$f[l][r+1][1]=min(f[l][r+1][1],f[l][r][k]+cost);$$

-------------------------

但在实际编码过程中，还需要考虑如何处理出 $cost $。

这个可以用一个前缀和预处理出所有区间的$\Delta$来。

-------------------

### code:
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define T_T double
const int maxn=1001;
using namespace std;
struct qaq
{
    T_T x,c,d;
    bool operator < (const qaq qwq)const
    {
        return x<qwq.x;
    }
}a[maxn];
T_T f[maxn][maxn][2],sum[maxn];
T_T min(T_T x,T_T y)
{
    if(x>y) return y;
    else return x;
}
int main()
{
    int n;
    T_T v,x;
    while(~scanf("%d%lf%lf",&n,&v,&x)&&n&&v&&x)
    {
        int start;
        a[0].x=x;
        a[0].d=0;
        for(int i=1;i<=n;i++)
            scanf("%lf%lf%lf",&a[i].x,&a[i].c,&a[i].d);
        sort(a,a+1+n);
        for(int i=0;i<=n;i++)
        {
            if(!i) sum[i]=a[i].d;
            else sum[i]=sum[i-1]+a[i].d;
            if(a[i].x==x) start=i;
        }//前缀和
        for(int i=0;i<=n;i++)
            for(int j=i;j<=n;j++)
                f[i][j][1]=f[i][j][0]=0x3f3f3f3f;
        f[start][start][0]=f[start][start][1]=0;
        //cout<<start<<endl;
        for(int i=0;i<n;i++)//区间长度
            for(int l=0;l+i<=n;l++)//左端点
            {
                int r=l+i;//右端点
                //向左走。
                for(int k=0;k<=1;k++)
                {
                    if(f[l][r][k]==0x3f3f3f3f) continue;
                    int p=k?r:l;
                    if(l-1>=0)
                    {
                        T_T t=(a[p].x-a[l-1].x)/v;//时间
                        T_T ans=a[l-1].c+t*(sum[n]-sum[r]+sum[l-1]);//花费
                        // cout<<ans<<endl;
                        f[l-1][r][0]=min(f[l-1][r][0],f[l][r][k]+ans);
                    }
                //下同，向右走。
                    if(r+1<=n)
                    {
                        // T_T ans=0;
                        T_T t=(a[r+1].x-a[p].x)/v;
                        T_T ans=a[r+1].c+t*(sum[n]-sum[r]+(l-1>=0?sum[l-1]:0));
                        f[l][r+1][1]=min(f[l][r+1][1],f[l][r][k]+ans);
                        // cout<<f[l][r][k]<<endl;
                    }
                }
            }
        printf("%.0lf\n",floor(min(f[0][n][1],f[0][n][0])));
    }
}
```
## 原谅我皮了一波，用颜文字写代码qwq。
------------------
### 安利博客：[传送门](http://tchoi.club)

---

## 作者：niiick (赞：4)

思路和楼上差不多，但这里用**记搜**实现

将这N个点**按位置排序**

显然如果一个点走过他再回头修一定不会最优，
所以任意时刻**已修补的区间一定是连续的**

即若当前以修好第$ll$~$rr$个地点，那么下一个修补的一定是$ll-1$或$rr+1$

定义$dp[ll][rr][0/1]$表示**已经修好了**$[ll,rr]$**区间**的地点，且**当前所在位置为**$ll(0)$**还是**$rr(1)$，
**修补完剩下的地点所需最小化费**

初始化$dp[1][n][0]=dp[1][n][1]=0$，其余为INF


令$W=Sum[n]-(Sum[rr]-Sum[ll-1])$ 即计算**剩余没修补的地点每单位时间增加的成本总和**

$dp[ll][rr][0]=min(dp[ll-1][rr][0]+Len(ll-1,ll)/V*W,dp[ll][rr+1][1]+Len(ll,r+1)/V*W)$
$dp[ll][rr][1]=min(dp[ll-1][rr][0]+Len(ll-1,rr)/V*W,dp[ll][rr+1][1]+Len(rr,r+1)/V*W)$

注意这里我们还要**把机器人的初始位置作为一个点加进去**，所以**总点数应为N+1**

设排序后表示机器人的点为K，从**DP(k,k,0)开始记搜**即可

答案为$dp[k][k][0]+SUM$ (SUM为初始成本总和)
*************

```cpp
//niiick
#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
typedef double dd;

int read()
{
    int f=1,x=0;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return f*x;
}

const int inf=1e9;
const int maxn=1010;
int n,v,x;
struct node{dd pos,c,dt;}rem[maxn];
bool cmp(node a,node b){return a.pos<b.pos;}
dd sum[maxn],dp[maxn][maxn][2];

dd DP(int ll,int rr,int d)
{
    if(ll==1&&rr==n+1) return 0;
    if(dp[ll][rr][d]!=inf) return dp[ll][rr][d];
    dd resl=0,resr=0,ss=sum[n+1]-(sum[rr]-sum[ll-1]);
    if(ll>1){
        if(d==1) resl=(rem[rr].pos-rem[ll-1].pos)/v*ss;
        else resl=(rem[ll].pos-rem[ll-1].pos)/v*ss;
    }
    if(rr<=n){
        if(d==1) resr=(rem[rr+1].pos-rem[rr].pos)/v*ss;
        else resr=(rem[rr+1].pos-rem[ll].pos)/v*ss;
    }
    if(ll>1) dp[ll][rr][d]=min(dp[ll][rr][d],DP(ll-1,rr,0)+resl);
    if(rr<=n) dp[ll][rr][d]=min(dp[ll][rr][d],DP(ll,rr+1,1)+resr);
    return dp[ll][rr][d];
}

int main()
{
    while(scanf("%d%d%d",&n,&v,&x)!=EOF)
    {
    	if(n==0&&v==0&&x==0) break; dd ssum=0;
    	for(int i=1;i<=n;++i)
    	scanf("%lf%lf%lf",&rem[i].pos,&rem[i].c,&rem[i].dt);
    	rem[n+1].pos=x; rem[n+1].c=0; rem[n+1].dt=0;//将机器人也作为一个点加入
    
    	sort(rem+1,rem+2+n,cmp);
    	for(int i=1;i<=n+1;++i)
    	ssum+=rem[i].c,
        sum[i]=sum[i-1]+rem[i].dt;
    	
    	for(int i=1;i<=n+1;++i)
    	for(int j=1;j<=n+1;++j)
    	dp[i][j][0]=dp[i][j][1]=inf;
    	
    	for(int i=1;i<=n+1;++i)
    	if(rem[i].pos==x){ printf("%.0lf\n",floor(DP(i,i,0)+ssum)); break;}
    }
    return 0;
}

```


---

## 作者：StupidSeven (赞：2)

## Subject 
[题目传送门](https://www.luogu.com.cn/problem/UVA1336)

## Analysis
比较典型的区间 dp 可以先做一下[这题](https://www.luogu.com.cn/problem/P1220)，更简单一点。

套路一样，设 $dp[L][R][0/1]$ 表示把区间 $[L,R]$ 修缮完后，站在端点 $L(0)$ ，或者站在端点 $R(1)$  ， $[L,R]$ 以外的位置产生的的最少代价。 

那么有转移方程：

$dp[L][R][0]=\min(dp[L+1][R][0]+(\sum\limits_{i=1}^{L}\Delta_i+\sum\limits_{i=R+1}^n\Delta_i)\times\dfrac{x_{L+1}-x_L}{v},dp[L+1][R][1]+(\sum\limits_{i=1}^{L}\Delta_i+\sum\limits_{i=R+1}^n\Delta_i)\times\dfrac{x_R-x_L}{v})$ 

- 要去修点 $L$ ，如果站在点 $L+1$  ，就要从 $L+1$ 走到 $L$ ；如果在点 $R$ ，就要从 $R$ 走到 $L$ ，这段时间里， $[1,L]$ 和 $[R+1,n]$ 里的点都会产生额外的 $\Delta$ 。时间就是距离差除以速度。

$dp[L][R][1]=\min(dp[L][R-1][0]+(\sum\limits_{i=1}^{L-1}\Delta_i+\sum\limits_{i=R}^{n}\Delta_i)\times\dfrac{x_R-x_L}{v},dp[L][R-1][1]+(\sum\limits_{i=1}^{L-1}\Delta_i+\sum\limits_{i=R}^n\Delta_i)\times\dfrac{x_R-x_{R-1}}{v})$

- 同上，要去修点 $R$ ，如果在点 $L$ ，就要从 $L$ 走到点 $R$ ；如果在点 $R-1$ ，就要从 $R-1$ 走到 $R$ ，在这段时间里， $[1,L-1]$ 和 $[R,n]$ 里的点都会产生额外的 $\Delta$。时间同上。

其中 $x_i$ 表示 $i$ 点的坐标， $\sum\limits\Delta$ 可以用前缀和优化。

最后答案就是 $ans+\min(dp[1][n][0],dp[1][n][1])$ ，其中 $ans$ 表示修缮所有点的时间。

dp 前要先把所有数据按照 $x$ 从小到大排序。

## Code
```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int M=2e3+10;
const int inf=0x3f3f3f3f;
inline int Read(void){
    int s=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){s=s*10+c-48;c=getchar();}
    return s*f;    
}
struct Node{
    int x,t,val;
    bool operator<(const Node &u)const{
        return x<u.x;
    }
}num[M];
int n,ans,idx,x,t,val;
double v,dp[M][M][2],sum[M];
signed main(void){
    while(scanf("%d%lf%d",&n,&v,&idx)==3&&n&&v&&idx){
        ans=0;
        for(int i=1;i<=n;i++){
            x=Read();
            t=Read();
            val=Read();
            num[i]=(Node){x,t,val};
        }
        num[++n]=(Node){idx,0,0};
        sort(num+1,num+1+n);
        for(int i=1;i<=n;i++){
            if(num[i].x==idx&&num[i].t==0&&num[i].val==0){
                idx=i;
                break;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                dp[i][j][0]=dp[i][j][1]=inf;
            sum[i]=sum[i-1]+num[i].val;
            ans+=num[i].t;
        }
        dp[idx][idx][0]=dp[idx][idx][1]=0;
        for(int len=2;len<=n;len++){
            for(int L=1;L+len-1<=n;L++){
                int R=L+len-1;
                dp[L][R][0]=min(dp[L+1][R][0]+(num[L+1].x-num[L].x)/v*(sum[L]+sum[n]-sum[R]),dp[L+1][R][1]+(num[R].x-num[L].x)/v*(sum[L]+sum[n]-sum[R]));
                dp[L][R][1]=min(dp[L][R-1][0]+(num[R].x-num[L].x)/v*(sum[L-1]+sum[n]-sum[R-1]),dp[L][R-1][1]+(num[R].x-num[R-1].x)/v*(sum[L-1]+sum[n]-sum[R-1]));
            }
        }
        printf("%d\n",(int)floor(ans+min(dp[1][n][0],dp[1][n][1])));
    }
    return 0;
}
```

---

## 作者：Link_Space (赞：1)

很容易看出是DP，那么是什么DP呢？考虑如下：

对于每一个点，我们不可能走过了它但是却不去修补它，因为修补它不需要时间的花费，如果路过了之后不修补那么一定不是最优的做法，那么我们就可以知道每一次已经修补了的点都是一段连续的区间，所以说这道题就是一道区间DP。

既然已经知道了是区间DP，那么我们应该如何定义状态呢？假设我们现在修补到了x这个点上，并且 $L — x$ 这一段区间都已经修补了，那么我们此时有两种选择：继续往右边修补点或者立刻掉头修补L左边的点，当我们修补到x这个点并且 $x — R$ 这一段已经修补了的时候同理。

那么经过以上分析，我们就可以得到一个状态的定义： $dp[i][j][left/right]$ 表示  $point_{i}-point_{j}$ 这一段区间的路灯已经修补并且我们目前站在这个区间的最左边或者最右边的时候产生的最小花费,可能你会问:为什么我一定要站到最左边或者最右边？我不能站到这个区间的中间吗？首先，我们如果已经修复了 $point_{i}-point_{j}$ 这个区间，由于我们是一个一个点修复的，那么当我们刚修复完的时候一定是站在最左边或者最右边的，如果此时我们站在这个区间的中间，那么代表我们修复完这个区间之后还继续往这个区间内已经被修复了的点走，产生的花费是完全多余的，也自然不是最优的选择。

知道了状态之后，转移方程也就比较好想了，假设我们当前刚好修完了 $point_{i}-point_{j}$ 的这段区间，并且站在这段区间的最左边，那么我们有这样几种情况:

1. 上一次已经修好了 $point_{i-1}-point_{j}$ 这段区间并且站到了这段区间的最左边，然后往左继续修了一个点修完了 $point_{i}-point_{j}$ 这段区间，此时我们站在 $point_{i}-point_{j}$ 这段区间的最左边。

2. 上一次已经修好了 $point_{i-1}-point_{j}$ 这段区间并且站到了这段区间的最右边，然后往左掉头修到 $point_i$ 修完了 $point_{i}-point_{j}$ 这段区间，此时我们站在 $point_{i}-point_{j}$ 这段区间的最左边。

对于我们当前刚好修完了 $point_{i}-point_{j}$ 的这段区间，并且站在这段区间的最右边的转移也同理。

如果还不清楚的可以看看代码，代码内有关于这道题的一些注意事项

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 2e3 + 5;
typedef long long ll;//需要开long long，否则会WA
ll dp[N][N][2];
ll sum[N][N];//sum[i][j]表示i-j这一段每单位时间增加的修缮费用的总和
struct Node{
    ll pos, spend;
    bool operator < (Node it)const
    {
        return pos < it.pos;
    }
} broke[N];
int main()
{
    ll n, v, sta;
    while(scanf("%lld%lld%lld",&n,&v,&sta)!=EOF)
    {
        ll ans = 0;
        for (ll i = 1; i <= n;i++)
        {
            ll a;
            scanf("%lld%lld%lld", &broke[i].pos, &a, &broke[i].spend);
            ans += a;//最后的答案为一开始就将所有点的修缮的费用加上期间增加的费用
        }
        broke[++n] = {sta, 0};//将起点作为一个花费为0的点加进去
        sort(broke + 1, broke + n + 1);
        for (ll i = 1; i <= n;i++)
        {
            sum[i][i] = broke[i].spend;
            for (ll j = i + 1; j <= n;j++)
                sum[i][j] = sum[i][j - 1] + broke[j].spend;//预处理前缀和数组
        }
        memset(dp, 0x3f, sizeof dp);//记得初始化为最大值
        for (ll i = 1; i <= n;i++)
        {
            if(broke[i].pos==sta&&broke[i].spend==0)
            {
                if(i!=1)
                    dp[i - 1][i][0] = (broke[i].pos - broke[i - 1].pos) * (sum[1][i - 1] + sum[i + 1][n]);
                if(i!=n)
                    dp[i][i + 1][1] = (broke[i + 1].pos - broke[i].pos) * (sum[1][i - 1] + sum[i + 1][n]);//初始状态的定义，一开始只能从起点走向与起点相邻的点
            }
        }
        for (ll i = 3; i <= n;i++)//枚举区间长度
        {
            for (ll l = 1; l <= n - i + 1;l++)//枚举区间左端点
            {
                ll r = l + i - 1;
                dp[l][r][0] = min(dp[l + 1][r][0] + (broke[l + 1].pos - broke[l].pos) * (sum[1][l] + sum[r + 1][n]),dp[l + 1][r][1] + (broke[r].pos - broke[l].pos) * (sum[1][l] + sum[r + 1][n]));
                dp[l][r][1] = min(dp[l][r - 1][1] + (broke[r].pos - broke[r - 1].pos) * (sum[1][l - 1] + sum[r][n]),dp[l][r - 1][0] + (broke[r].pos - broke[l].pos) * (sum[1][l - 1] + sum[r][n]));
            }
        }
        printf("%lld\n", ans + min(dp[1][n][1], dp[1][n][0]) / v);//上面是按照速度为1来算的，实际增长费用需要除以一个实际速度
    }
}
```


---

## 作者：Sata_moto (赞：1)

### 前言：

[$ \large{}\color {#6495ED} \mathcal{MyBlog} $](https://xjx885.coding-pages.com/)


本题是一道很经典的区间DP题了...

双倍经验入口：[洛谷 P1220 关路灯](https://www.luogu.org/problem/P1220)

在此刷一发题解

---

### 题目大意：

在一条线段上有N个节点，经过每个节点需要付出一定代价，每个点的代价会随时间线性增长，给定你起始点的坐标和速度，求最小代价

---

### 题目分析:

本题乍看上去上去不好下手...

本题固然是到DP，但如何表示它的状态？

如果既考虑当前的位置，又考虑经过了哪些点，那状态未免太过复杂...

空间时间也承受不下...

我们注意到：每个点的代价只会上升，不会下降

所以如果采取最优策略，当我们走过一个点时，我们一定会修复那个点

这样，我们对于点修复与否的表示，可以转化为点经过与否的表示...

又因为我们不可以跳着走，所以我们行走的路线必然是一条连续的线段...

所以我们大可以设$f[k][i][j]$表示我们在k位置时，修复了i~j上的所有点...

这是$O(x^3)$的复杂度...

离散可以优化至$O(n^3)$...

显然不行...还需要继续优化...

观察状态，i,j两维都是必要的，k一维似乎去掉..

如何去掉？滚动数组可优化不了时间...

我们又注意到：在i,j之间逗留是不可取的...

什么意思？如果你当前在C点，你已经把i到j的点修复完了...

那么你下一步要修复的点就是i-1 或者 j+1，那么下一步的坐标也只会是这两者之一...

如果说你下一步想修i-2怎么办？可以看做两步操作：先去修i-1，再修i-1 -1...

如果按照这种思想，可以发现，你的“每一步”走完之后，你要么到达了i-1，要么到达了j+1，换句话说，就是到达了走过区间的两端...

而区间i~j又是从i+1,j走一步，或者从i,j-1走一步出来的...

所以f[k][i][j]中的k，无非就是i或者j（区间的两端）...

所以我们将状态改为f[i][j][2]，表示走过i~j的区间，当前位于区间的左/右端

转移就很清晰了，要么转移到到i-1，要么转移到到j+1...

不过如何维护每一步的代价呢？

可以使用前缀和...所有点的每秒增长代价减去已经修的点的增长代价，然后乘上时间就好...

至于基础代价，直接加在一起作为初值...

具体细节见代码....

---

### 代码：

```cpp
#include <bits/stdc++.h>

const int N = 1020;

//记得开double

int n;
double v, X;

struct node
{
	double x, c, delta;

	bool operator < (const node & other) const
	{
		return x < other.x;
	}
} point[N];//每个需要修复的点

double cl[N];//前缀和维护每秒代价增长
double f[N][N][2];//修好了i~j区间，位于区间左/右端

int C;

int main()
{
	while(scanf("%d %lf %lf", &n, &v, &X) != EOF)
	{
		if(!n) break;

		double add = 0;

		for(int k = 1; k <= n; k++)
		{
			scanf("%lf %lf %lf", &point[k].x, &point[k].c, &point[k].delta);

			add += point[k].c;//直接加出基础代价
		}

		//离散
		point[++n].x = X;//把起点加进去一起离散
		std::sort(point + 1, point + 1 + n);
		for(int k = 1; k <= n; k++)
			if(point[k].x == X)
			{
				C = k;
				break;
			}

		//维护前缀和
		for(int k = 1; k <= n; k++)
			cl[k] = cl[k - 1] + point[k].delta;

		//赋初值
		for(int k = 1; k <= 1010; k++)
			for(int i = 1; i <= 1010; i++)
				f[k][i][0] = f[k][i][1] = 99999999999;
		f[C][C][0] = f[C][C][1] = add;

		//转移 ，这里用的是刷表法
		for(int len = 1; len < n; len++)
			for(int l = 1; l + len - 1 <= n; l++)
			{
				int r = l + len - 1;

				if(f[l][r][0] != 99999999999)
				{
					if(l > 1)
						f[l - 1][r][0] = std::min(f[l - 1][r][0], f[l][r][0] + (cl[n] - cl[r] + cl[l - 1]) / v * (point[l].x - point[l - 1].x));
					f[l][r + 1][1] = std::min(f[l][r + 1][1], f[l][r][0] + (cl[n] - cl[r] + cl[l - 1]) / v * (point[r + 1].x  - point[l].x ));
				}
				if(f[l][r][1] != 99999999999)
				{
					if(l > 1)
						f[l - 1][r][0] = std::min(f[l - 1][r][0], f[l][r][1] + (cl[n] - cl[r] + cl[l - 1]) / v * (point[r].x - point[l - 1].x));
					f[l][r + 1][1] = std::min(f[l][r + 1][1], f[l][r][1] + (cl[n] - cl[r] + cl[l - 1]) / v * (point[r + 1].x  - point[r].x));
				}
			}

		//输出整数 
		printf("%.0lf\n", floor(std::min(f[1][n][0], f[1][n][1])));
	}

	return 0;
}
```

---


### 结语：

如果本题解有BUG...

那么...那么...那么...

（随意了）还请私信作者....

---

## END

---


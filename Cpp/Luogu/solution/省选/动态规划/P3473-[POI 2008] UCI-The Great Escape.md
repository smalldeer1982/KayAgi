# [POI 2008] UCI-The Great Escape

## 题目描述

Al Bytone, the infamous thief, plans a bank robbery.

He knows only too well that the moment he robs the bank a pursuit    will be commenced. Unfortunately, Al Bytone is a poor driver and turning    left causes him great trouble. This is why he tries to devise such an    escape route that at each intersection he would either ride straight    ahead or turn right. He is also aware that once he passes through any    intersection, the police will come and remain there, waiting for him.

Therefore he may pass through any intersection at most once.

Furthermore, the police are always present at certain intersections,    so Al Bytone will have to avoid these intersections as well    (there's no police at the intersections near the bank and near Al Bytone's    hideout.)    Al Bytone is planning his escape route. To your great (and rather    unpleasant) surprise, he paid you a visit and told to calculate the    number of different escape routes leading from the bank to his hideout    complying the aforementioned requirements. Needless to say, Al Bytone    does not take 'no' as an answer...

The streets of Byteburg form a rectangular grid. Every street runs either in the North-South or East-West direction,    and every two non-parallel streets intersect. The bank is situated to the south of the south-western-most intersection.

Al Bytone will start his great escape driving north.

<Task> 

Write a programme that:

reads from the standard input the location of hideout,          descriptions of intersections with police and a positive          integer ![](http://main.edu.pl/images/OI15/uci-en-tex.1.png),                      calculates the number of different escape routes leading from the bank to the hideout          complying the aforementioned requirements,                      writes out to the standard output this number's residue modulo $k$.



## 样例 #1

### 输入

```
3 5 10
4 2
+++++
++*++
++++*
```

### 输出

```
2
```

# 题解

## 作者：金珂拉 (赞：8)

## 题意


现在有一张 $ N \times M $ 的网格图，在这张图中有一些障碍物。

现在要求从左下角出发且方向向上，中间只能直行或右转，并且不能重复经过一个点，到达终点路径条数。

答案对k取模。

- ## 分析

- ### 正常dp
首先，我们可以发现，既然只能右转，那么运动的路径就恰好是个螺旋状，而螺旋状的本质就是一个个不断缩小的矩阵

那么我们就可以发现，右转的过程实质上是在切割大矩形。如图，红线为路径，黑线为矩形。

![](https://cdn.luogu.com.cn/upload/image_hosting/uohppzrb.png)


令 $ f_{u,r,d,l,p} $ 表示在上为 $ u $ 下为 $ d $ 左为 $ l $ 右为 $ r $ 的矩阵上方向为 $ p $ (其中 0-3 分别表示上右下左）的边上运动时的方案数，那么小矩形就是大矩形的子问题，且满足加法原理。

那么，现在我们不考虑障碍物，就可以得到这样的方程。只要枚举在哪个点的地方转弯即可

$ f_{u,r,d,l,0}=\Sigma f_{k,r,d,l+1,1} $

$ f_{u,r,d,l,1}=\Sigma f_{u+1,k,d,l,2} $

$ f_{u,r,d,l,2}=\Sigma f_{u,r-1,k,l,3} $

$ f_{u,r,d,l,3}=\Sigma f_{u,r,d-1,k,0} $

若考虑障碍物，就有了这样的伪代码
```cpp
for(int k;;)
f[u][r][d][l][0]+=f[k][r][d][l+1][0]*(路径上无障碍?1:0) 
for(int k;;)
f[u][r][d][l][1]+=f[u+1][k][d][l][1]*(路径上无障碍?1:0)
for(int k;;)
f[u][r][d][l][2]+=f[u][r-1][k][l][2]*(路径上无障碍?1:0)
for(int k;;)
f[u][r][d][l][3]+=f[u][r][d-1][k][3]*(路径上无障碍?1:0)
```
为方便起见，以下将(路径上无障碍?1:0)简记为 $ check(k) $。


- ### 考虑优化

但是我们发现，这样复杂度是 $ O(n^5) $ 的，显然会超时，必须把 $ k $ 的枚举优化掉

我们可以发现一个公式

以向上为例，有如下式子

$ f_{u,r,d,l,0}=(\Sigma f_{k,r,d,l+1,1} \times check(k) )+f_{u,r,d,l+1,1} \times check(u) =f_{u+1,r,d,l,0}+f_{u,r,d,l+1,1} \times check(u)$

没有了 $ k $ 的枚举，瞬间变成了 $ O(n^4) $ !

但是这样的空间依旧会超，所以我们可以使用滚动数组，然后发现每次枚举的两个子状态都满足行数和列数的和刚好比原状态少 1，所以可以考虑按行列数之和从小到大枚举。

- ## 注意事项

输入终点坐标时，先输入列再输入行，读入时应注意

- ## 代码
```cpp
/*
最初的方程: 
f[u][r][d][l][上]=∑f[k][r][d][l+1][右]*(路径上无障碍?1:0) 
f[u][r][d][l][右]=∑f[u+1][k][d][l][下]*(路径上无障碍?1:0)
f[u][r][d][l][下]=∑f[u][r-1][k][l][左]*(路径上无障碍?1:0)
f[u][r][d][l][左]=∑f[u][r][d-1][k][上]*(路径上无障碍?1:0)
这个显然是n^5的，时间会炸
但是我们仔细一看就会发现 
f[u][r][d][l][上]=∑f[k][r][d][l+1][右]*check(k)+f[u][r][d][l+1][右]*check(u)
f[u][r][d][l][右]=∑f[u+1][k][d][l][下]*check(k)+f[u+1][r][d][l][下]*check(u)
f[u][r][d][l][下]=∑f[u][r-1][k][l][左]*check(k)+f[u][r-1][d][l][左]*check(u)
f[u][r][d][l][左]=∑f[u][r][d-1][k][上]*check(k)+f[u][r][d-1][l][上]*check(u)
其中k的范围会缩小一步。
也就是说，转移方程可以写成这样 
f[u][r][d][l][上]=f[u][r][d][l+1][右]*(路径上无障碍?1:0)+f[u+1][r][d][l][上]
f[u][r][d][l][右]=f[u+1][r][d][l][下]*(路径上无障碍?1:0) +f[u][r-1][d][l][右]
f[u][r][d][l][下]=f[u][r-1][d][l][左]*(路径上无障碍?1:0)+f[u][r][d-1][l][下]
f[u][r][d][l][左]=f[u][r][d-1][l][上]*(路径上无障碍?1:0)+f[u][r][d][l+1][左]
但是发现空间不够用 
不过，我们可以发现的是，每次转移，行数+列数恰好减少1,然后刚好转移也是一步步来的，可以滚动数组优化掉
*/              
#include<bits/stdc++.h>
using namespace std;
int n,m,mod,y,x,s1[101][101],s2[101][101],dp[2][101][101][101][4];
int main() {
    cin>>n>>m>>mod>>y>>x;
    for (int i=1;i<=n;++i)
    for (int j=1;j<=m;++j)
	{
        char c='.';
        while (c!='+' && c!='*') c=getchar();
        s1[i][j]=s1[i][j-1]+(c=='*'),
        s2[i][j]=s2[i-1][j]+(c=='*');
    }
    for (int s=2;s<=n+m;s++)
    for (int i=1;i<s;i++)
    for(int l=1;l<=y&&l<=m-s+i+1;l++)
	for(int u=1;u<=x&&u<=n-i+1;u++)
    {
    int d=u+i-1,r=l+s-i-1;
    if (d<x||r<y) continue;
	dp[s&1][u][l][d][0]=(dp[(s-1)&1][u+1][l][d][0]+(s2[d][l]==s2[u-1][l])*(dp[(s&1)^1][u][l+1][d][1]+(u==x&&l==y)))%mod;
	dp[s&1][u][l][d][1]=(dp[(s-1)&1][u][l][d][1]+(s1[u][r]==s1[u][l-1])*(dp[(s&1)^1][u+1][l][d][2]+(u==x&&r==y)))%mod;
    dp[s&1][u][l][d][2]=(dp[(s-1)&1][u][l][d-1][2]+(s2[d][r]==s2[u-1][r])*(dp[(s&1)^1][u][l][d][3]+(d==x&&r==y)))%mod;
    dp[s&1][u][l][d][3]=(dp[(s-1)&1][u][l+1][d][3]+(s1[d][r]==s1[d][l-1])*(dp[(s&1)^1][u][l][d-1][0]+(d==x&&l==y)))%mod;
    }
    cout<<dp[(n+m)&1][1][1][n][0];
}
```



---

## 作者：zifanwang (赞：3)

[传送门](https://www.luogu.com.cn/problem/P3473)

发现正着不好做，考虑倒着做，即从 $(x,y)$ 开始走转弯只能向左转。

考虑怎么处理不重复走的限制。发现路径是螺旋形的，可以用一个矩形将路径框起来，那么每走一步都会使矩形的长或宽往某个方向延长一个单位。转弯可以看成向前走一格，再左转然后走到矩阵的边界。

然后就可以 dp 做了，记录当前矩形的左上角和右下角还有当前方向，每次 $O(1)$ 直接转移，时间复杂度 $O(n^4)$。然后发现空间不够，可以滚动掉一维，空间复杂度 $O(n^3)$。

参考代码：

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
int n,m,md,x,y,ans,f1[103][103],f2[103][103],dp[102][2][102][102][4];
char s[103][103];
bool fl;
inline void add(int &x,int y){
	x+=y;if(x>=md)x-=md;
}
signed main(){
	scanf("%d%d%d%d%d",&n,&m,&md,&y,&x);
	rep(i,1,n)scanf("%s",s[i]+1);
	rep(i,1,n)rep(j,1,m){
		f1[i][j]=f1[i][j-1]+(s[i][j]=='*');
		f2[i][j]=f2[i-1][j]+(s[i][j]=='*');
	}
	rept(i,0,4)dp[x][0][x][y][i]=1;
	drep(y1,y,1){
		drep(x1,x,1)rep(x2,x,n)rep(y2,y,m)rept(i,0,4)dp[x1][fl^1][x2][y2][i]=0;
		drep(x1,x,1){
			rep(x2,x,n){
				rep(y2,y,m){
					if(x2<n&&s[x2+1][y1]=='+'){
						add(dp[x1][fl][x2+1][y2][0],dp[x1][fl][x2][y2][0]);
						if(f1[x2+1][y1-1]==f1[x2+1][y2])add(dp[x1][fl][x2+1][y2][1],dp[x1][fl][x2][y2][0]);
					}
					if(y2<m&&s[x2][y2+1]=='+'){
						add(dp[x1][fl][x2][y2+1][1],dp[x1][fl][x2][y2][1]);
						if(f2[x1-1][y2+1]==f2[x2][y2+1])add(dp[x1][fl][x2][y2+1][2],dp[x1][fl][x2][y2][1]);
					}
					if(x1>1&&s[x1-1][y2]=='+'){
						add(dp[x1-1][fl][x2][y2][2],dp[x1][fl][x2][y2][2]);
						if(f1[x1-1][y1-1]==f1[x1-1][y2])add(dp[x1-1][fl][x2][y2][3],dp[x1][fl][x2][y2][2]); 
					}
					if(y1>1&&s[x1][y1-1]=='+'){
						add(dp[x1][fl^1][x2][y2][3],dp[x1][fl][x2][y2][3]);
						if(f2[x1-1][y1-1]==f2[x2][y1-1])add(dp[x1][fl^1][x2][y2][0],dp[x1][fl][x2][y2][3]);
					}
				}
			}
		}
		fl^=1;
	}
	rep(x1,1,n)rep(y2,1,m)add(ans,dp[x1][fl^1][n][y2][0]);
	cout<<ans;
	return 0;
}
```

---

## 作者：wgyhm (赞：1)

## Description

https://www.luogu.com.cn/problem/P3473

## Solution

还是一些细节没想清楚啊。

观察到每次相当于切割一次矩阵，我们令 $f_{i,j,k,l,0/1/2/3}$ 表示矩阵的左下角的为 $(i,j)$，右上角为 $(k,l)$，接下来要往 上/右/下/左 走。

先不考虑有障碍的情况。

感觉从 $(1,1)$ 开始不好赋初值啊，于是我们考虑从 $(sx,sy)$ 开始倒着走，也就是每次左转。比如我们以往上走为例子：

![image-20231204191533649](https://s2.loli.net/2023/12/04/3fVLPtuDhZ4lkIX.png)

$f_{i,j,k,l,0}\gets f_{r,j+1,k,l,1}$。

考虑用已经递推出来的来化简这个东西：

$f_{i,j,k,l,0}\gets f_{i+1,j,k,l,0}+f_{i,j+1,k,l,1}$。

可以发现新加入的一条是列为 $j$，行 $[i,k]$ 的一列值，只需要判断这一段上没有障碍就可以转移。

同样的可以扩展到剩下 $3$ 种情况。

最初状态 $f_{sx,sy,sx,sy,i}=1$。

然后考虑转移方向，观察到每次让矩形的半周长增加 $1$。所以我们先枚举矩形半周长即可。

这样就可以 $O(n^4)$ 递推了。空间需要滚动数组优化，复杂度为 $O(n^3)$，有 $8$ 倍的常数。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define maxn 105
#define put() putchar('\n')
#define Tp template<typename T>
#define Ts template<typename T,typename... Ar>
using namespace std;
Tp void read(T &x){
    int f=1;x=0;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    x*=f;
}
namespace Debug{
	Tp void _debug(char* f,T t){cerr<<f<<'='<<t<<endl;}
	Ts void _debug(char* f,T x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	#define gdb(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
#define fi first
#define se second
#define mk make_pair
int n,m,mod;
int r[maxn][maxn],c[maxn][maxn],a[maxn][maxn];
int sx,sy,ans;
int f[2][maxn][maxn][maxn][4];
signed main(void){
	int i,j,k,l,o,s,lenx,leny;char ch;
	read(n);read(m);read(mod);
	read(sy);read(sx);sx=n-sx+1;
	for (i=n;i>=1;i--) {
		cin>>ch;
		for (j=1;j<=m;j++,ch=getchar()) a[i][j]=(ch=='*');
	}
	for (i=1;i<=n;i++) for (j=1;j<=m;j++) c[i][j]=c[i][j-1]+a[i][j],r[i][j]=r[i-1][j]+a[i][j];
	for (s=2;s<=n+m;s++) {
		int now=s&1,pre=now^1;
		memset(f[now],0,sizeof(f[now]));
		for (lenx=1;lenx<s;lenx++) {//x的长度
			leny=s-lenx;
			for (i=1,k=lenx;i<=sx&&k<=n;i++,k++) {
				for (j=1,l=leny;j<=sy&&l<=m;j++,l++) {
					if (k<sx||l<sy) continue;
					f[now][j][k][l][0]=(f[pre][j][k][l][0]+f[pre][j+1][k][l][1]+(i==sx&&j==sy&&k==sx&&l==sy))*(r[i-1][j]==r[k][j])%mod;
					f[now][j][k][l][1]=(f[pre][j+1][k][l][1]+f[pre][j][k-1][l][2]+(i==sx&&j==sy&&k==sx&&l==sy))*(c[k][j-1]==c[k][l])%mod;
					f[now][j][k][l][2]=(f[pre][j][k-1][l][2]+f[pre][j][k][l-1][3]+(i==sx&&j==sy&&k==sx&&l==sy))*(r[i-1][l]==r[k][l])%mod;
					f[now][j][k][l][3]=(f[pre][j][k][l-1][3]+f[pre][j][k][l][0]+(i==sx&&j==sy&&k==sx&&l==sy))*(c[i][j-1]==c[i][l])%mod;
					// gdb(i,j,k,l,f[i][j][k][l][0],f[i][j][k][l][1],f[i][j][k][l][2],f[i][j][k][l][3]);
				}
			}
			ans=(ans+f[now][1][lenx][leny][0])%mod;//统计答案
		}
	}
	// for (k=sx;k<=n;k++) for (l=sy;l<=m;l++) ans=(ans+f[(k+l)&1][1][k][l][0])%mod;
	printf("%d\n",ans);
	return 0;
}
//i=begin && g++ $i.cpp -o $i -std=c++14 && ./$i
```



---


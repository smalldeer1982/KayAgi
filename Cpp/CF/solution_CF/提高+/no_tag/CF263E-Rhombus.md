# Rhombus

## 题目描述

You've got a table of size $ n×m $ . On the intersection of the $ i $ -th row ( $ 1<=i<=n $ ) and the $ j $ -th column ( $ 1<=j<=m $ ) there is a non-negative integer $ a_{i,j} $ . Besides, you've got a non-negative integer $ k $ .

Your task is to find such pair of integers $ (a,b) $ that meets these conditions:

- $ k<=a<=n-k+1 $ ;
- $ k<=b<=m-k+1 $ ;
- let's denote the maximum of the function ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF263E/769fc0d46a3a86543938422030ea676ecc6cb2cb.png) among all integers $ x $ and $ y $ , that satisfy the inequalities $ k<=x<=n-k+1 $ and $ k<=y<=m-k+1 $ , as $ mval $ ; for the required pair of numbers the following equation must hold $ f(a,b)=mval $ .

## 样例 #1

### 输入

```
4 4 2
1 2 3 4
1 1 1 1
2 2 2 2
4 3 2 1
```

### 输出

```
3 2
```

## 样例 #2

### 输入

```
5 7 3
8 2 3 4 2 3 3
3 4 6 2 3 4 6
8 7 6 8 4 5 7
1 2 3 2 1 3 2
4 5 3 2 1 2 1
```

### 输出

```
3 3
```

# 题解

## 作者：itisover (赞：4)

idea 是偷网上的，那就算一下复杂度吧。

考虑转成切比雪夫，那么要加的区域就把一个斜 45 正方形转成了一个正方形（$dis(a,b)=\max\{|x_a-x_b|,|y_a-y_b|\}$ 结论显然），那这样就可以二维前缀和直接做了，正方形内的系数还是一层一层递减的，所以我们直接枚举点坐标和当前计算贡献的层数 $i\in [k,n-k+1],j\in[k,m-k+1],z\in[0,k-1]$ 爆算就行了。

算一下复杂度：$O(i\cdot j\cdot z)=O((n-2k)(m-2k)k)$，显然 $n=m=1000$ 时取的最大，这时候就是 $10^6k-4000k^2+4k^3,k\le500$，求导一下可知最大值为 $74074074.41591052711$，综上能过。

能懂这个正方形长什么样吧，能懂吧能懂吧。来张图，这能理解了吧。

![](https://cdn.luogu.com.cn/upload/image_hosting/fzwmr8w9.png)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int _=2005;
int n,m,k;
long long b[_][_],maxn;
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m>>k;
    pair<int,int> ans={k,k};
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            cin>>b[i+j][i-j+m];//+m是因为有负数
    for(int i=1;i<=n+m;++i)
        for(int j=1;j<=n+m;++j)
            b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1];
    for(int i=k;i<=n-k+1;++i){
        for(int j=k;j<=m-k+1;++j){
            int x=i+j,y=i-j+m;
            long long sum=0;
            for(int z=0;z<k;++z) sum+=b[x+z][y+z]-b[x-z-1][y+z]-b[x+z][y-z-1]+b[x-z-1][y-z-1];//理解成一圈一圈加
            if(maxn<sum) ans={i,j},maxn=sum;
        }
    }
    cout<<ans.first<<" "<<ans.second;
    return 0;
}
//O(74074074.41591052711)
```

---

## 作者：chenxia25 (赞：3)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF263E) & [CodeForces题目页面传送门](https://codeforces.com/contest/263/problem/E)

>给定一个$n$行$m$列的矩阵，第$i$行$j$列为$a_{i,j}$，以及一个常数$s\in\left[1,\left\lceil\dfrac{\min(n,m)}2\right\rceil\right]$，求一个正整数对$(a,b)(a\in[s,n-s+1],b\in[s,m-s+1])$使得$f(a,b)=\sum\limits_{i=1}^m\sum\limits_{j=1}^m\max(0,s-(|i-a|+|j-b|))a_{i,j}$最大。

>$n,m\in\left[1,10^3\right]$。

将矩阵上每格对函数$f$值的贡献的系数画出来，会发现它是个斜着的正方形，中心系数等于$s$，往外$1$层系数减$1$，减到$0$为止，如下图。

![](https://s2.ax1x.com/2020/01/17/lzIwef.png)

枚举中心点，可以得到$\mathrm O(nm)$个这样的正方形。现在问题是怎么快速求出所有正方形的系数乘格子内的数之和，即所有中心点的函数值。假设我们已经知道了$f(i,j)$，现在想知道$f(i,j+1)$。不妨把这两个正方形画出来，看它们相差什么。

![](https://s2.ax1x.com/2020/01/17/lzOjFP.png)

如上图，是$2$个相邻的$s=3$的正方形，紫色的数字是此格子内红色系数减蓝色系数。不难发现，左边一半是一个差都是$-1$、高为$s=3$、直角顶点在底边左侧的等腰直角三角形，右边一半是一个差都是$1$……底边右侧……。由此可以归纳出，设$trl_{i,j}$表示底边中点为$(i,j)$、高为$s$、直角顶点在底边左侧的等腰直角三角形内元素之和，$trr_{i,j}$表示……底边右侧……，则$f(i,j)=f(i,j-1)-trl_{i,j-1}+trr_{i,j}$。假设我们已经知道了$trl,trr$数组，那么可以$\forall i\in[s,n-s+1]$，暴力用对角线前缀和$\mathrm O(s)$求出$f(i,s)$，然后$\forall i\in[s,n-s+1],\forall j\in(s,m-s+1]$，用上面那个关系式递推求出$f(i,j)$，总复杂度为$\mathrm O(nm)$。

现在问题转化为怎么快速求出$trl,trr$数组。以$trl$为例，先画出相邻两个三角形。

![](https://s2.ax1x.com/2020/01/19/19DKKg.png)

如上图，是两个相邻的$s=3$的三角形，紫色的数字是此格子内红色系数减蓝色系数。又不难发现，左边的三角形轮廓的差都是$-1$，右边一列的差都是$1$。这个轮廓的和和列的和可以维护列前缀和$Sum1$、副对角线前缀和$Sum2$（在同一条副对角线上当且仅当行列和相等）、主对角线前缀和$Sum3$（在同一条主对角线上当且仅当行列差相等）搞定。于是就有了一个$trl_{i,j},trl_{i,j-1}$的关系式。那么可以$\forall i\in[s,n-s+1]$，暴力用列前缀和$\mathrm O(s)$求出$trl_{i,s}$，然后$\forall i\in[s,n-s+1],\forall j\in(s,m]$，用关系式递推求出$trl_{i,j}$，总复杂度为$\mathrm O(nm)$。$trr$求法类似。

$\mathrm O(nm)$与处理完$3$个前缀和，$trl,trr$就可以$\mathrm O(nm)$求出来了，那么$f$也可以$\mathrm O(nm)$求出来了，最后找最大值即可。总复杂度$\mathrm O(nm)$。

下面贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
#define X first
#define Y second
const int N=1000,M=1000;
int n/*矩阵行数*/,m/*矩阵列数*/,s/*常数*/;
int a[N+1][M+1];//矩阵 
int Sum1[M+1][N+1]/*列前缀和*/,Sum2[N+M+1][M+1]/*副对角线前缀和*/,Sum3[2*N+1][M+1]/*主对角线前缀和，由于行列差可能是负数，所以平移max(n,m)个单位*/;
int sum1(int x,int l,int r){return l>r?0:Sum1[x][r]-Sum1[x][l-1];}//列区间和 
int sum2(int x,int l,int r){return l>r?0:Sum2[x][r]-Sum2[x][l-1];}//副对角线区间和 
int sum3(int x,int l,int r){return l>r?0:Sum3[x+max(n,m)][r]-Sum3[x+max(n,m)][l-1];}//主对角线区间和 
int trl[N+1][M+1],trr[N+1][M+1];//朝左、朝右三角形 
int rhm[N+1][M+1];//正方形，即f函数 
signed main(){
	cin>>n>>m>>s;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%lld",a[i]+j);
	//预处理前缀和开始 
	for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)Sum1[i][j]=Sum1[i][j-1]+a[j][i];
	for(int i=1;i<=n+m;i++)for(int j=1;j<=n;j++)Sum2[i][j]=Sum2[i][j-1]+(1<=i-j&&i-j<=m?a[j][i-j]:0);
	for(int i=-max(n,m);i<=max(n,m);i++)for(int j=1;j<=n;j++)Sum3[i+max(n,m)][j]=Sum3[i+max(n,m)][j-1]+(1<=j+i&&j+i<=m?a[j][j+i]:0);
	//预处理前缀和结束 
	for(int i=s;i<=n-s+1;i++){//算trl 
		for(int j=1;j<=s;j++)trl[i][s]+=sum1(j,i-j+1,i+j-1);//暴力算边上的trl 
		for(int j=s+1;j<=m;j++)trl[i][j]=trl[i][j-1]+sum1(j,i-s+1,i+s-1)-sum2(i+j-s,i-s+1,i)-sum3(j-s-i,i+1,i+s-1);//用关系式递推其他trl 
	}
	for(int i=s;i<=n-s+1;i++){//算trr，与trl类似 
		for(int j=m;j>=m-s+1;j--)trr[i][m-s+1]+=sum1(j,i-(m-j+1)+1,i+(m-j+1)-1); 
		for(int j=m-s;j;j--)trr[i][j]=trr[i][j+1]+sum1(j,i-s+1,i+s-1)-sum3(j+s-i,i-s+1,i)-sum2(i+j+s,i+1,i+s-1);
	}
//	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)printf("tr(%lld,%lld)=(%lld,%lld)\n",i,j,trl[i][j],trr[i][j]);
	for(int i=s;i<=n-s+1;i++){//算rhm 
		for(int j=0;j<s;j++)rhm[i][s]+=(s-j)*(sum2(i-j+s,i-j,i)+sum3(s-(i+j),i+1,i+j)+sum2(i+j+s,i,i+j-1)+sum3(s-(i-j),i-j+1,i-1));//暴力算边上的rhm 
		for(int j=s+1;j<=m-s+1;j++)rhm[i][j]=rhm[i][j-1]+trr[i][j]-trl[i][j-1];//用关系式递推其他rhm 
	}
//	for(int i=s;i<=n-s+1;i++)for(int j=s;j<=m-s+1;j++)printf("rhm[%lld][%lld]=%lld\n",i,j,rhm[i][j]);
	pair<int,pair<int,int> > mx(0,mp(0,0)); 
	for(int i=s;i<=n-s+1;i++)for(int j=s;j<=m-s+1;j++)mx=max(mx,mp(rhm[i][j],mp(i,j)));//找最大值 
	cout<<mx.Y.X<<" "<<mx.Y.Y;
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

小丑，做这种题做半天。

首先发现有贡献的位置是一个斜正方形，从内到外贡献系数依次递减。先拆成四个部分（四个直角三角形），每次将整个矩形旋转来分别做，最后简单容斥一下。

考虑对于一个直角三角形怎么计算贡献。考虑从它左边的一个三角形转移过来。设定点为 $(i,j)$ 的三角形贡献为 $f_{i,j}$，里面数之和为 $g_{i,j}$，则 $f_{i,j}=f_{i,j-1}-g_{i,j-1}$ 再加上三角形最右边一列的贡献。很多都可以预处理出来前缀和解决。

$g_{i,j}$ 也可以转移，方法应该很多，我的方法是从 $g_{i-1,j+1}$ 转来再减去一列加上一行。只用单独处理 $j=m$ 的情况。

细节挺多。因为做法比较烂/kk。

code：

```cpp
int n,m,k,a[N][N],b[N][N];ll c[N][N][2],d[N][N][2],f[N][N],g[N][N],ans[N][N];
il ll getx(int i,int j){return (c[i][j][1]-c[max(i-k,0)][j][1])-(i-k)*(c[i][j][0]-c[max(i-k,0)][j][0]);}
void solve(int op){
	mems(f,0),mems(g,0),mems(c,0),mems(d,0);
	rep(i,1,n){
		rep(j,1,m){
			c[i][j][0]=c[i-1][j][0]+a[i][j];
			c[i][j][1]=c[i-1][j][1]+1ll*a[i][j]*i;
			d[i][j][0]=d[i][j-1][0]+a[i][j];
			d[i][j][1]=d[i][j-1][1]+1ll*a[i][j]*j;
		}
	}
	rep(i,1,n){
		f[i][1]=getx(i,1),g[i][1]=c[i][1][0]-c[max(i-k,0)][1][0];
		rep(j,2,m){
			f[i][j]=f[i][j-1]-g[i][j-1]+getx(i,j);
			g[i][j]=g[i-1][j+1]-(c[i-1][j+1][0]-c[max(i-1-k,0)][j+1][0])+(d[i][j][0]-d[i][max(j-k,0)][0]);
		}
		g[i][m]=g[i][m-1];
		int x=i,y=m-k;
		while(x&&y<m)g[i][m]-=a[x--][y++];
		g[i][m]+=c[i][m][0]-c[max(i-k,0)][m][0];
		rep(j,1,m){
			f[i][j]-=getx(i,j);
			if(op==1)ans[i][j]+=f[i][j];
			if(op==2)ans[j][n-i+1]+=f[i][j];
			if(op==3)ans[n-i+1][m-j+1]+=f[i][j];
			if(op==4)ans[m-j+1][i]+=f[i][j];
		}
	}
}
void turn(){
	rep(i,1,n)rep(j,1,m)b[m-j+1][i]=a[i][j];
	swap(n,m);
	rep(i,1,n)rep(j,1,m)a[i][j]=b[i][j];
}
void Yorushika(){
	scanf("%d%d%d",&n,&m,&k);
	rep(i,1,n)rep(j,1,m)scanf("%d",&a[i][j]);
	rep(i,1,4)solve(i),turn();
	int x=k,y=k;
	rep(i,k,n-k+1)rep(j,k,m-k+1)if((ans[i][j]+=1ll*k*a[i][j])>ans[x][y])x=i,y=j;
	printf("%d %d\n",x,y);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---


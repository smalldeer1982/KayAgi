# Wilbur and Trees

## 题目描述

Wilbur the pig really wants to be a beaver, so he decided today to pretend he is a beaver and bite at trees to cut them down.

There are $ n $ trees located at various positions on a line. Tree $ i $ is located at position $ x_{i} $ . All the given positions of the trees are distinct.

The trees are equal, i.e. each tree has height $ h $ . Due to the wind, when a tree is cut down, it either falls left with probability $ p $ , or falls right with probability $ 1-p $ . If a tree hits another tree while falling, that tree will fall in the same direction as the tree that hit it. A tree can hit another tree only if the distance between them is strictly less than $ h $ .

For example, imagine there are $ 4 $ trees located at positions $ 1 $ , $ 3 $ , $ 5 $ and $ 8 $ , while $ h=3 $ and the tree at position $ 1 $ falls right. It hits the tree at position $ 3 $ and it starts to fall too. In it's turn it hits the tree at position $ 5 $ and it also starts to fall. The distance between $ 8 $ and $ 5 $ is exactly $ 3 $ , so the tree at position $ 8 $ will not fall.

As long as there are still trees standing, Wilbur will select either the leftmost standing tree with probability $ 0.5 $ or the rightmost standing tree with probability $ 0.5 $ . Selected tree is then cut down. If there is only one tree remaining, Wilbur always selects it. As the ground is covered with grass, Wilbur wants to know the expected total length of the ground covered with fallen trees after he cuts them all down because he is concerned about his grass-eating cow friends. Please help Wilbur.

## 说明/提示

Consider the first example, we have 2 trees with height 2.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF596D/7ea79c02ec83af888c806be42da0defa4e428746.png) There are 3 scenarios:  1. Both trees falls left. This can either happen with the right tree falling left first, which has ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF596D/b116fbdd63568e4121015b312e3b382ba11897c2.png) probability (also knocking down the left tree), or the left tree can fall left and then the right tree can fall left, which has ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF596D/949810d863b968a5ba3d8d376258384cb22f342a.png) probability. Total probability is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF596D/99d81ce87528a9d733790866f22c7ea59a9a6aba.png).

 2. Both trees fall right. This is analogous to (1), so the probability of this happening is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF596D/9c584154315cc26f3f6d096139c60a6d963a78db.png).

 3. The left tree fall left and the right tree falls right. This is the only remaining scenario so it must have ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF596D/7600097d7e8dbe4c0d431b4b3222d04bc7df2acc.png) probability.

 Cases 1 and 2 lead to a total of 3 units of ground covered, while case 3 leads to a total of 4 units of ground covered. Thus, the expected value is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF596D/6b415b0ca26814ba41988ac3a2c4b91c5d01c6e4.png).

## 样例 #1

### 输入

```
2 2 0.500000
1 2
```

### 输出

```
3.250000000
```

## 样例 #2

### 输入

```
4 3 0.4
4 3 1 2
```

### 输出

```
6.631200000
```

# 题解

## 作者：奇米 (赞：2)

# 题解 - $\mathrm{CF596D}$

## 题目意思

[题目传送门](https://www.luogu.com.cn/problem/CF596D)

## $\mathrm{Sol}$

* **期望$DP$**

* 我们先定义状态 $f_{l,r,x,y}$ 表示区间 $[l,r]$，$l-1$往 $x$ 倒，$r+1$往 $y$ 倒的期望。（$x=0$向外倒，$x=1$向内倒，$y$ 同理）

* 我们考虑一次倒下，以左边端点为例子。

* 如果对于 $l$ 向右倒，(其中的$cr[]$表示往右最多能倒到那颗树）

  * 倒下后连锁反应倒下直到 $r$，那么$f_{l,r,x,y}=0.5\times (1.0-P)\times(a[r]-a[l]+\min(m,a[r+1]-a[r]-m*y))$

  * 倒下后只能影响到部分的树

    $f_{l,r,x,y}=0.5\times (1.0-P)\times (a[cr[l]]-a[l]+m+dfs(cr[l]+1,r,1,y))$

    
* 如果对于 $l$ 向左倒

	* $f_{l,r,x,y}=0.5\times P\times (\min(m,a[l]-a[l-1]-x*m)+dfs(l+1,r,0,opr))$
    
    
* 对于$ml[],cr[]$我们$O(n)$就能预处理出来，总复杂度$O(n^{2})$

## $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for ( int i=(a);i<=(b);i++ )
#define Dow(i,b,a) for ( int i=(b);i>=(a);i-- )
#define GO(i,x) for ( int i=head[x];i;i=e[i].nex )
#define mem(x,s) memset(x,s,sizeof(x))
#define cpy(x,s) memcpy(x,s,sizeof(x))
#define YES return puts("YES"),0
#define NO return puts("NO"),0
#define GG return puts("-1"),0
#define pb push_back
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int mod=1e9+7;
const int mo=998244353;
const int N=2005;

int n,m,a[N],ml[N],cr[N];
double f[N][N][2][2],P;

inline double dfs(int l,int r,int opl,int opr)
{
	if(l>r) return 0;
	if(f[l][r][opl][opr]) return f[l][r][opl][opr];
	double sum=0;
	sum+=0.5*P*(min(m,a[l]-a[l-1]-opl*m)+dfs(l+1,r,0,opr));
	sum+=0.5*(1.0-P)*(min(m,a[r+1]-a[r]-opr*m)+dfs(l,r-1,opl,0));
	if(cr[l]>=r) sum+=0.5*(1.0-P)*(a[r]-a[l]+min(m,a[r+1]-a[r]-m*opr));
	else sum+=0.5*(1.0-P)*(a[cr[l]]-a[l]+m+dfs(cr[l]+1,r,1,opr));
	if(ml[r]<=l) sum+=0.5*P*(a[r]-a[l]+min(m,a[l]-a[l-1]-m*opl));
	else sum+=0.5*P*(a[r]-a[ml[r]]+m+dfs(l,ml[r]-1,opl,1));
	return f[l][r][opl][opr]=sum;
}

int main()
{
	n=read();
	m=read();
	scanf("%lf",&P);
	For(i,1,n) a[i]=read();
	sort(a+1,a+n+1);
	ml[1]=1;
	For(i,2,n) 
	{
		if(a[i]-a[i-1]<m) ml[i]=ml[i-1];
		else ml[i]=i;
	}
	cr[n]=n;
	Dow(i,n-1,1)
	{
		if(a[i+1]-a[i]<m) cr[i]=cr[i+1];
		else cr[i]=i;
	}
	a[0]=-1e9;a[n+1]=1e9;
	printf("%.7lf\n",dfs(1,n,0,0));
	return 0;
}
		
	
```


---

## 作者：skyskyCCC (赞：0)

## 前言。
这道题很神啊，看似是个概率题，实际上暗藏玄机。

事实上，因为每次砍树只会从左右两个端点砍树，所以就会形成几个区间，那么对于区间内的树，我们才能求期望值，同时需要考虑整个区间，显然我们不难想到区间动态规划。
## 分析。
首先定义状态。考虑概率性时间，如果我们把一个区间 $\left[l,r\right]$ 单独拿出来考虑，看 $l$ 这棵树是向左边倒还是向右边倒，但是这样就会影响到 $\left[l+1,r\right]$ 的期望值，所以我们对于这个状态的设定，不能只考虑区间内的情况，相反，我们应把端点的状态也考虑进去。

所以我们这个状态要考虑上左右端点。设 $dp_{l,r,x,y}$ 为在砍到 $\left[l,r\right]$ 这个区间时，第 $l+1$ 棵树的倾倒情况为 $x$ 同时第 $r+1$ 棵树的倾倒情况为 $y$。这个状态存的是，这个区间内的区域覆盖期望值。我们同时可以将这个 $x$ 和 $y$ 用倾斜方向简化为两个数，即向右，或者向左。 

最终的终止条件为 $l>r$ 的情况出现，所以转移方程就从边界情况考虑。那么这里以左端点为例：

如果左端点向左倾倒，则 $l$ 对应的区域覆盖贡献就是 $a_l-a_{l-1}-x\times h$ 和 $h$ 的较小值。

注意到本题中，树和相邻树的距离小于 $h$ 时，树倒时会把相邻的树撞倒，倒的方向和撞到它的树一致。所以显然我们上面的 $a_l-a_{l-1}$ 一定大于或等于 $h_i$ 所以我们就可以通过上面的左端点去推 $dp_{l+1,r,x,y}$ 即可。其中的 $x$ 为向区间外面倒下的情况所对于的数。

反之左端点向右倾倒，这样就会出发链式反应，前面先用 $O\left(n\right)$ 的时间预处理出所有这次连锁反应能被波及到的最大的点的位置，然后分为一片直接全部倒，和没有全部倒的情况转移即可。

右端点的情况同理。时间复杂度为 $O\left(n^2\right)$。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;
int n,h,a[2005];
double p;
int sum_1[2005],sum_c[2005];
double dp[2005][2005][2][2];
double work(int l,int r,int x,int y){
	double sum=0;
    if(l>r){
	    return 0;
	}
    if(dp[l][r][x][y]){
	    return dp[l][r][x][y];
	}
    //左端点向左边倒。 
    sum+=0.5*p*(min(a[l]-a[l-1]-x*h,h)+work(l+1,r,0,y));
    //右端点向右边倒。 
    sum+=0.5*(1-p)*(min(a[r+1]-a[r]-y*h,h)+work(l,r-1,x,0));
    //右端点向左边倒。 
    if(sum_1[r]<=l){
        sum+=0.5*p*(min(a[l]-a[l-1]-x*h,h)+a[r]-a[l]);
    }
    else{
        sum+=0.5*p*(work(l,sum_1[r]-1,x,1)+a[r]-a[sum_1[r]]+h);
    }
    //左端点向右边倒。 
    if(sum_c[l]>=r){
        sum+=0.5*(1-p)*(min(a[r+1]-a[r]-y*h,h)+a[r]-a[l]);
    }
    else{
        sum+=0.5*(1-p)*(work(sum_c[l]+1,r,1,y)+a[sum_c[l]]-a[l]+h);
    }
    dp[l][r][x][y]=sum;
    return dp[l][r][x][y];
}
int main(){
    cin>>n>>h>>p;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    sum_1[1]=1;
    for(int i=2;i<=n;i++){
        if(a[i]-a[i-1]<h){
        	sum_1[i]=sum_1[i-1];
		}
        else sum_1[i]=i;
    }
    sum_c[n]=n;
    for(int i=n-1;i>=1;i--){
        if(a[i+1]-a[i]<h){
		    sum_c[i]=sum_c[i+1];
		}
        else sum_c[i]=i;
    }//预处理出来被连锁反应波及到的点。
	a[0]=-0x3f3f3f3f;
	a[n+1]=-a[0];
    printf("%.9lf\n",work(1,n,0,0));
    return 0;
}
```
## 后记。
足足 $95$ 个测试点，测了我将近 $1$ 分钟。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Nightingale_OI (赞：0)

## CF596D

### 大意

有 $n$ 棵高度为 $h$ 的树，第 $i$ 棵在位置 $x_i$，每次各有 $0.5$ 的概率砍掉坐标最左或最右的树。

树倒向左边的概率为 $p$，右边为 $1-p$，如果树和倒向的树距离小于 $h$，会把它也撞倒，倒的方向一致。

求砍完所有树，树干覆盖区间的期望值。

### 思路

设计状态 $f_{vl,l,r,vr}$ 表示剩下 $[l,r]$ 的树，左右的树倒的状态是 $vl$ 和 $vr$（$0$ 向外 $1$ 向内）树干覆盖区间的期望值。

状态数是 ${\rm O}(n^2)$ 的，只要快速转移即可。

预处理出每一棵树向左、右倒的时候引发连锁反应到 $tl_i$ 和 $tr_i$。

从第 $l$ 棵树到第 $r$ 棵树向右**连续**倒的时候，必然是 $[x_l,x_r+h]$ 这段区间被覆盖，向左同理。

可以设计一个函数 $cf(vl,i,i+1,vr)$ 表示第 $i$ 棵树和第 $i+1$ 棵树倒的状态分别是 $vl$ 和 $vr$ 时，若两棵树对覆盖区间的贡献都算作 $h$，则向内倒的树多算了多少贡献。

转移时枚举砍的哪边的树、往哪个方向倒即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int n,m,s,l;
const int N=2020,inf=1e9;
double f[2][N][N][2],p,q;
int a[N],v[2][N][N][2],tl[N],tr[N];
inline int cf(int vl,int l,int r,int vr){return min(a[r]-a[l]-m*(vl+vr),0ll);}
double dfs(int vl,int l,int r,int vr){
    if(l>r)return cf(vl,r,l,vr);
    if(!v[vl][l][r][vr]){
        v[vl][l][r][vr]=1; 
        int x;double re=0;
        x=min(tr[l],r);
        re+=p*(dfs(0,l+1,r,vr)+m+cf(vl,l-1,l,1));
        re+=q*(dfs(1,x+1,r,vr)+m+a[x]-a[l]);
        x=max(l,tl[r]);
        re+=q*(dfs(vl,l,r-1,0)+m+cf(1,r,r+1,vr));
        re+=p*(dfs(vl,l,x-1,1)+m+a[r]-a[x]);
        f[vl][l][r][vr]=re/2;
    }
    return f[vl][l][r][vr];
}
signed main(){
    cin>>n>>m>>p;q=1-p;
    f(i,1,n)scanf("%lld",&a[i]);
    sort(a+1,a+n+1);a[0]=-inf;a[n+1]=inf;
    f(i,1,n)tl[i]=(i>1&&a[i]-a[i-1]<m)?tl[i-1]:i;
    g(i,n,1)tr[i]=(i<n&&a[i+1]-a[i]<m)?tr[i+1]:i;
    printf("%.10lf",dfs(0,1,n,0));
	return 0;
}
```

---

## 作者：AC自动机 (赞：0)

### 思路
又是一道非常有思维难度的题，主要是概率和期望学的太差了/(ㄒoㄒ)/~~  ┗|｀O′|┛

首先从头开始分析，砍树总是从两端开始砍的，因此两端会影响中间，而中间则不会影响到两端的树，因为砍到中间的时候，两端的树都已经砍到了，所以在做dp的时候，例如正在处理区间i到j，我们不需要关注区间内的树是向哪边倒的，因为中间的树不会影响两端的，我们需要关注的是i-1和j+1位的地方的树，因为只有这些地方会对中间的树有影响，所以我们用dp[i][j][0/1][0/1]来表式i-1和j+1这两棵树的状态时，i到j之间的答案。若状态若为0，则表示两外侧倒，若为1，则表示向内倒。

在状态转移时，有以下几种情况：

1.第i颗树向左侧倒，不会影响后面的树

2.第j棵树向右侧倒，不会影响前面的树

3.第i棵树向右侧倒，会影响到后面的树
  
  
  (Ⅰ)第i棵树直接把i+1，j之间的所有树都压倒了
  
  (Ⅱ)第i棵树不能把后面的树都压倒
 
4.第j棵树向左侧倒，会影响到前面的树
  
  
  (Ⅰ)第j棵树直接把i，j-1之间的所有树都压倒了
  
  (Ⅱ)第j棵树不能把前面的树都压倒

所以，状态转移时使用dfs，并且要分类讨论，每棵树分别向两侧倒可以压倒的最远的树可以预处理出来并用数组记录。

### 该死的细节  (╯‵□′)╯︵┻━┻

注意，在处理倒的时候一定要注意和之前砍倒的树会不会发生重叠，要取min值！！！！ 不然一个地方会被算两次！！！



#### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
double dp[2005][2005][2][2];
int pos[2005];
int cl[2005],cr[2005];
int n;
double p,h;
void ini(){
	cl[1]=1;
	for(register int i=2;i<=n;i++){
		if(pos[i]-pos[i-1]<h)cl[i]=cl[i-1];
		else cl[i]=i;
	}
	cr[n]=n;
	for(register int i=n-1;i>=1;i--){
		if(pos[i+1]-pos[i]<h)cr[i]=cr[i+1];
		else cr[i]=i;
	}
}
double dfs(int l,int r,int x,int y){
	//di l-1 ke shu dao xia de fang xiang wei x
	//di r+1 ke shu dao xia de fang xiang wei y
	//0 liang bian dao 1 zhong jian dao
	if(l>r)return 0;
	if(dp[l][r][x][y]!=0)return dp[l][r][x][y];
	register double temp=dp[l][r][x][y];
	//最左边向左倒，因此不影响中间
	//min 计算l向做倒和l-1的重合部分
	temp+=p*0.5*(min(pos[l]-pos[l-1]-x*h,h)+dfs(l+1,r,0,y));
	//最右边向右倒，因此不影响中间
	//min 计算r向右倒和r+1的重合部分
	temp+=(1-p)*0.5*(min(pos[r+1]-pos[r]-y*h,h)+dfs(l,r-1,x,0));

	if(cl[r]<=l) temp+=p*0.5*(min(pos[l]-pos[l-1]-h*x,h)+pos[r]-pos[l]);   // 最右边的向左倒，且把整个区间的树全部付覆盖
	else temp+=p*0.5*(dfs(l,cl[r]-1,x,1)+pos[r]-pos[cl[r]]+h);//无法全部覆盖的情况

	if(cr[l]>=r) temp+=(1-p)*0.5*(min(pos[r+1]-pos[r]-h*y,h)+pos[r]-pos[l]);
	else temp+=(1-p)*0.5*(dfs(cr[l]+1,r,1,y)+pos[cr[l]]-pos[l]+h);
	return dp[l][r][x][y]=temp;

}
int main(){
	cin>>n>>h>>p;
	for(register int i=1;i<=n;i++){
		cin>>pos[i];
	}
	sort(pos+1,pos+n+1);
	pos[0]=-99999999999;
	pos[n+1]=99999999999;
	ini();
	// for(register int i=1;i<=n;i++){
	// 	cout<<cl[i]<<' ';
	// }
	// cout<<endl;
	printf("%.20lf\n",dfs(1,n,0,0));
}
```

---


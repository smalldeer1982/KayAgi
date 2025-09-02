# Gerald and Giant Chess

## 题目描述

Giant chess is quite common in Geraldion. We will not delve into the rules of the game, we'll just say that the game takes place on an $ h×w $ field, and it is painted in two colors, but not like in chess. Almost all cells of the field are white and only some of them are black. Currently Gerald is finishing a game of giant chess against his friend Pollard. Gerald has almost won, and the only thing he needs to win is to bring the pawn from the upper left corner of the board, where it is now standing, to the lower right corner. Gerald is so confident of victory that he became interested, in how many ways can he win?

The pawn, which Gerald has got left can go in two ways: one cell down or one cell to the right. In addition, it can not go to the black cells, otherwise the Gerald still loses. There are no other pawns or pieces left on the field, so that, according to the rules of giant chess Gerald moves his pawn until the game is over, and Pollard is just watching this process.

## 样例 #1

### 输入

```
3 4 2
2 2
2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
100 100 3
15 16
16 15
99 88
```

### 输出

```
545732279
```

# 题解

## 作者：smilke (赞：29)

这题观察数据范围，发现与n有关，于是我们就从黑色棋入手。

假设不存在黑色棋，那么很容易得到答案为ans=$C_{x+y-2}^{x-1}$ .

设 $f[i]$ 表示原点到第$i$个黑色点的路径数量。

由减法原理，原点到第$i$个点的路径数量为$:$路径总数量$-$经过黑色棋的数量。

由乘法原理，第$j$个黑色棋阻碍通过第$i$个棋的路径等于$:$ $f[j]$ * $C_{x_i+y_i-x_j-y_j}^{x_i-x_j}$ ，条件为 $x_i>=x_j$并且$y_i>=y_j$.

因此我们可以得出状态转移方程：

$f[i]=C_{x_i+y_i-2}^{x_i-1}-\sum_{j=1}^{i-1}f[j]*C_{x_i+y_i-x_j-y_j}^{x_i-x_j}$

（条件为 $x_i>=x_j$并且$y_i>=y_j$.）

所以代码也很好写：

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=3e5+50,mod=1e9+7;
int h,w,n,p[N],inv[N],f[N];
struct node{ int x,y; }a[N];
bool mycmp(node a,node b){ return a.x<b.x||(a.x==b.x&&a.y<b.y); }
int C(int m,int n){ if(m>n) return 0; return (p[n]*inv[n-m]%mod*inv[m])%mod; }
int pow(int a,int b){
	int res=1;
	while(b){ if(b&1) res=(res*a)%mod; b>>=1; a=(a*a)%mod;}
	return res%mod;
}
main(){
	scanf("%lld%lld%lld",&h,&w,&n);
	rep(i,1,n) scanf("%lld%lld",&a[i].x,&a[i].y);
	a[n+1].x=h,a[n+1].y=w;
	sort(a+1,a+n+2,mycmp);
	rep(i,0,N-10) p[i]=(i==0)?1:((p[i-1]*i)%mod),inv[i]=pow(p[i],mod-2);
	rep(i,1,n+1) f[i]=C(a[i].x-1,a[i].x+a[i].y-2);
	rep(i,1,n+1) rep(j,1,i-1){
		if(a[i].x<a[j].x||a[i].y<a[j].y) continue;
		f[i]-=f[j]*C(a[i].x-a[j].x,a[i].x+a[i].y-a[j].x-a[j].y);
		f[i]=(f[i]+mod)%mod;
	}
	printf("%lld\n",(f[n+1]+mod)%mod);
	return 0;
}
```


---

## 作者：Booksnow (赞：17)

这道题和 **「BZOJ4767」两双手** 其实是一样的。他们的区别在于移动的方式发生了改变。
首先，我们会发现白点的数量是很多的，而黑点的数量却在两千以内，所以我们能够 **从黑点入手** 。

我们设数组f[i]表示从原点出发到达第i个障碍点，**不经过其他障碍点**的路径条数。

再设另外一个数组g[i][j]表示从i到j的所有路径条数

因此，我们不难推得公式

$f[i]=g[0][i]-\sum_{j=1}^ig[j][i]*f[j] $

这个公式的意思其实就是从**原点到达黑点i的总方案数减去遍历时更先到达的黑点的方案数**。其原因在于在**到达这个黑点之前就已经碰到黑点的方案数已经作废**，不能计入总方案数。

这个时候，就会出现一个问题，这个公式和题目求解的到达目标点的方案数并没有关系。如何解决这个问题？我们可以把目标点变成**最后一个黑点**，就可以通过上述公式求解。

接下来，就是先到达哪个黑点我们并不知道，我们可以**按照x和y的增序给黑点排序**，附上此段代码
```cpp
inline bool cmp(node x,node y)   
{
    if(x.x==y.x) return x.y<y.y;
    return x.x<y.x; 
}
```
理清楚了整个思路，我们现在来解决f数组的求解。
其实，我们能够发现，按照如题所述的走法，到达每个点的步数是一定的我们可以设他下移了X格，右移了Y格，而X和Y其实就是**其实就是目标点的坐标减去1**，这样我们就可以求出他下移和右移的步数，那这就其实可以通过**组合数**来求解了，**总的步数为X+Y，使用Y次B向量，其他使用A向量**，那么总方案数就为

$C_{X+Y}^Y$

这样我们就能通过这个公式，逐步求得到达各个黑点的方案数。还可以解决两个黑点之间的方案数，设起点到第一个黑点分别走的步数为$X_{1}$、$Y_{1}$，第二个黑点为$X_{2}$、$Y_{2}$。

那么方案数为

$C_{X_{2}-X_{1}+Y_{2}-Y_{1}}^{X_{2}-X_{1}}$

在之后**结合求解方案数的公式和第一个公式结合**，这道题就能过了。

最后，附上AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 
const int N=2020,M=1000000,MAX=1000010,MOD=1000000007;
struct node{
    int x,y;
}a[N];
int n,h,w;
ll f[N],fac[MAX],inv[MAX];
//为黑点排序 
inline bool cmp(node x,node y)   
{
    if(x.x==y.x) return x.y<y.y;
    return x.x<y.x; 
}
//模板快速幂 
inline ll power(ll x,ll ent)
{
    ll ans=1;
    while(ent){
        if(ent&1) ans=ans*x%MOD;
        ent>>=1;
        x=x*x%MOD;
    }
    return ans%MOD;
}
//组合数较大，用乘法逆元求解 
inline ll C(ll x,ll y)     
{
    if(x<y) return 0;
    return fac[x]*inv[y]%MOD*inv[x-y]%MOD;
}
 
int main()
{
    scanf("%d%d%d",&h,&w,&n);
    //到达目的地的需要下移和右移的步数 
	h=h-1; w=w-1;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i].x,&a[i].y);
        //直接将就用原数组保存步数了
		a[i].x-=1; a[i].y-=1;	 
    }
    a[0].x=a[0].y=0;
    //将目的地加入黑点 
    a[++n].x=h; a[n].y=w;
    //排序优先级 
    sort(a+1,a+n+1,cmp); 
    fac[0]=1;
    //求解乘法逆元 
    for(ll i=1;i<=M;i++) 		 
        fac[i]=1ll*fac[i-1]*i%MOD;
    inv[0]=1;inv[M]=power(fac[M],MOD-2);
    for(ll i=M-1;i>=1;i--) 
        inv[i]=1ll*inv[i+1]*(i+1)%MOD;
    //求解答案 
    for(int i=1;i<=n;i++){
    	//到达每个黑点的方案数 
        f[i]=C(a[i].x+a[i].y,a[i].x);
        if(f[i]==0) continue;
        for(int j=1;j<i;j++){
        	//从前面黑点转移过来的方案数，总方案数等于到达前面黑点的方案数乘转移的方案数 
        	//到达现在黑点的方案数要减去到达前面黑点的总方案数，这里可能有点绕，稍微理解一下 
            f[i]-=(f[j]*C(a[i].x-a[j].x+a[i].y-a[j].y,a[i].x-a[j].x))%MOD;
            f[i]%=MOD;
            f[i]+=MOD; f[i]%=MOD;
        } 
    } 
    //最后答案就是f[n] 
    printf("%lld\n",f[n]);
    return 0;
} 
```





---

## 作者：chihik (赞：8)


如果没有不能走到的点，这道题就非常简单了。我们只需向下走$h-1$步，向右走$w-1$步，就可到达右下角。在这$h+w-2$步中，我们选$h-1$向下走，那么答案为$C_{h+w-2}^{h-1}$。

但是，棋盘中有些点是不能走的，我们考虑用容斥原理去除多余方案，即

$$
Ans=C_{h+w-2}^{h-1}-P_1+P_2+..+(-1)^n * P_n
$$

其中，$P_i$经过$i$个不能走的点的路径，但是，此题$n<=2000$，容斥原理直接炸掉。

但上面的思路给了我们启示，设$f_i$表示从$(1,1)$走到第$i$个不能走的点，且不经过其它不能走的点的方案数。那么有：

![1.PNG](https://i.loli.net/2019/08/23/kyqlICQNmKEbGSs.png)

我们可以看出，转移时与下标先后顺序有关，我们先对下标排序，再进行计算。

我们将终点也看成一个不能走到的点，答案就为$f_{n+1}$


附上代码：

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define Mod 1000000007

const int MAXN = 2000 , MAXDEX = 100000;
int h , w , n , f[ MAXN + 5 ];
int Fac[ 2 * MAXDEX + 5 ] , Inv[ 2 * MAXDEX + 5 ];
struct node{
    int x , y;
    bool operator < ( const node &Other ) {
        if( x < Other.x )
            return 1;
        if( x == Other.x && y < Other.y )
            return 1;
        return 0;
    }
}a[ MAXN + 5 ];

int Quick_pow( int x , int po ) {
    int Ans = 1;
    while( po ) {
        if( po % 2 )
            Ans = 1ll * Ans * x % Mod;
        x = 1ll * x * x % Mod;
        po /= 2;
    }
    return Ans;
}
void Init( ) {
    int M = 2 * max( h , w );
    Fac[ 0 ] = 1;
    for( int i = 1 ; i <= M ; i ++ )
        Fac[ i ] = 1ll * Fac[ i - 1 ] * i % Mod;
    Inv[ M ] = Quick_pow( Fac[ M ] , Mod - 2 );		//费马小定理算出阶乘最后一项逆元
    for( int i = M - 1 ; i >= 0 ; i -- )
        Inv[ i ] = 1ll * Inv[ i + 1 ] * ( i + 1 ) % Mod;
    
    /*for( int i = 1 ; i <= M ; i ++ )
        printf("%d %d\n",Fac[ i ],Inv[ i ]);*/
}

int Combination( int n , int m ) {	//根据组合数定义
    if( n < m ) return 0;
    return 1ll * Fac[ n ] * Inv[ n - m ] % Mod * Inv[ m ] % Mod;
}

int main( ) {
    scanf("%d %d %d",& h , &w , &n );
    for( int i = 1 ; i <= n ; i ++ )
        scanf("%d %d",&a[ i ].x,&a[ i ].y);
    n ++;
    a[ n ].x = h , a[ n ].y = w;
    sort( a + 1 , a + n + 1 );
    Init( );
    
    for( int i = 1 ; i <= n ; i ++ ) {
        f[ i ] = Combination( a[ i ].x + a[ i ].y - 2 , a[ i ].x - 1 );
        for( int j = 1 ; j <= i - 1 ; j ++ )
            f[ i ] = ( ( 1ll * f[ i ] - 1ll * f[ j ] * Combination( a[ i ].x + a[ i ].y - a[ j ].x - a[ j ].y , a[ i ].x - a[ j ].x ) % Mod ) % Mod + Mod ) % Mod;
    }
    printf("%d\n",f[ n ]);
    return 0;
}
```


---

## 作者：Indus (赞：6)

# 一道计数类DP例题~~~


------------

ps：P党似乎不多了……

我这只蒟蒻第一次写题解，而且计数类DP还是早上刚学的，现学现用，或者说是所谓的“浅谈”一番吧！况且这题写题解的人似乎并不多（~~大佬似乎不屑于光临此题~~）
## 进入正题
 - 题目大意：扔给你一个h*w的棋盘，并给定n给不可以经过的格子的坐标，和（sang）蔼（xin）可（bing）亲（kuang）地让你计算从(1,1)开始走到(h,w)的合法路径的条数，答案对$10^9+7$取模。
 
 看完题后，呵，简单，都做过过河卒这种题吧！递推在手，天下我有！！
 大笑着，不经意间瞟了一下数据范围，笑容瞬间凝固……
 
 - $1<=h,w<=10^{5},1<=n<=2000 $
 
 啥玩意？

无奈，出门左转，~~逃~~！

够英明的选择，但还有更英明的选择——学习！没错，学习！

好的，依阁下高见，我来学习了。

## 孺子可教，吭吭，听好了(冒犯)：

-  倘若你成了超人，通过了之前无法逾越的格子，那么你走到终点的路径总数是可以用一个组合数搞出来的。不会？那就对了，接着看。从起点走到终点，你必然走了$h-1$步往下，$w-1$步往右，对吧？总步数就是$h+w-2$ ,然后想想组合数，整条路径我走了$h-1$步往下，剩下$w-1$步就确定了。那么换种说法，我从$h+w-2$步中选$h-1$步往下，就可以确定唯一的一条路径，则总方案数为$C_{h+w-2}^{h-1}$种，同理，走$w-1$步往下，也可以确定唯一的一条路径，有$C_{h+w-2}^{w-1}$种方案数。两者等价。（等价？质疑请了解$C_n^m=C_n^{n-m}$）

- 但是，棋盘中有些点是不能走的，我们考虑用容斥原理去除多余方案。
$$Ans=C_{h+w-2}^{h-1}-P_1+P_2-P_3+...+(-1)^n*P_n$$	
其中$P_i$表示经过i个不能走的点的路径，但是，此题n<=2000，容斥原理直接炸掉。（况且我也不会容斥原理，我太弱了）

- 但我们不急，不慌，不乱。想想DP，乱设一下，设$f_i$表示从(1,1)走到第i个不能走的点，且不经过其它不能走的点的方案数。推一下，设$x_i,y_i$为第i个不能通过的点（以$x_i$为第一关键字，$y_i$为第二关键字排好序后），我们可以用上文推到的东西先算出(1,1)这个点到总方案数，然后依照我们的定义：“不能经过其他无法通过的点”，所以要减去前$i-1$个点到此点的方案数（不合定义），就是$f_i$了,综上：

- $$f_i=C_{x_i+y_i-2}^{x_i-1}-\sum_{j=1}^{i-1}*C_{x_i+y_i-x_j-x_j}^{x_i-x_j}$$

- 我们可以让终点成为不可通过的点，答案就是$f_{n+1}$了。

- 嗯嗯，讲完了。

$O(n^2)$  的时间复杂度，完美AC。$n<=2000$

那么，再综合解题步骤：

- 以$x_i$为第一关键字，$y_i$为第二关键字排好序。

- 提前预处理出组合数所需要的逆元（逆元可以自学，复习时我可能会写来巩固一下）。

- 把终点加入$f$中，计算$f_i$的值，答案就是$f_{n+1}$

附上完整代码，放心食用。(pascal的，重点在思路，语言无太大关系)


------------


```pascal
const p=trunc(1e9)+7;
type
        node=record
                x,y:int64;
        end;
var
        fac,inv:array [0..200005] of int64;
        f:array [0..3005] of int64;
        a,c:array [0..3005] of node;
        n,m,i,j,k,maxn:longint;
procedure msort(l,r:longint);
var
        i,j,k,mid:longint;
begin
        mid:=(l+r)>>1;
        if (l<mid) then msort(l,mid);
        if (mid+1<r) then msort(mid+1,r);
        i:=l;
        j:=mid+1;
        k:=l;
        while (i<=mid)and(j<=r) do
        begin
                if (a[i].x<a[j].x)or(a[i].x=a[j].x)and(a[i].y<a[j].y) then
                begin
                        c[k]:=a[i];
                        inc(i);
                        inc(k);
                end
                else begin
                        c[k]:=a[j];
                        inc(j);
                        inc(k);
                end;
        end;
        while (i<=mid) do
        begin
                c[k]:=a[i];
                inc(i);
                inc(k);
        end;
        while (j<=r) do
        begin
                c[k]:=a[j];
                inc(j);
                inc(k);
        end;
        for i:=l to r do a[i]:=c[i];
end;
function qpow(x,y:int64):int64;
var
        res:int64;
begin
        res:=1;
        while (y>0) do
        begin
                if (y and 1=1) then res:=res*x mod p;
                x:=x*x mod p;
                y:=y>>1;
        end;
        exit(res);
end;
procedure prepare;
var
        i:longint;
begin
        fac[0]:=1;
        for i:=1 to maxn do fac[i]:=fac[i-1]*i mod p;
        inv[maxn]:=qpow(fac[maxn],p-2);
        for i:=maxn-1 downto 0 do inv[i]:=inv[i+1]*(i+1) mod p;
end;
function combination(n,m:int64):int64;
begin
        if (n<m) then exit(0);
        exit(fac[n]*inv[n-m] mod p*inv[m] mod p);
end;
begin
        //assign(input,'path.in');reset(input);
        //assign(output,'path.out');rewrite(output);
        readln(n,m,k);
        if (n<m) then maxn:=m<<1
        else maxn:=n<<1;
        for i:=1 to k do read(a[i].x,a[i].y);
        k:=k+1;
        a[k].x:=n;a[k].y:=m;
        msort(1,k);
        prepare;
        for i:=1 to k do
        begin
                f[i]:=combination(a[i].x+a[i].y-2,a[i].x-1);
                for j:=1 to i-1 do
                        f[i]:=(f[i]-f[j]*combination(a[i].x+a[i].y-a[j].x-a[j].y,a[i].x-a[j].x) mod p+p) mod p;
        end;
        write(f[k]);
        //close(input);close(output);
end.
```


------------
曲终，继续努力，备战CSP2019。

本文同步发表至[题解 CF559C 【Gerald and Giant Chess】](https://www.cnblogs.com/leiyuanze/p/11949227.html)


---

## 作者：leozhang (赞：4)

这题后来被改编成了我们的考题，所以今天来一发题解

本质是对dp思想的一种优化

首先我们来看，对于一个棋盘，如果直接从左下走到右上，方案数应为C(n+m-2,n)

但是中间有不能经过的点，这样做会多统计。

于是我们回归最本质的思想

我们发现，这个组合数来源于将该棋盘视作一个杨辉三角，然后dp方案数，推出的结论满足斜杨辉三角

那么我们恢复这个思想，由于不能用的点比较少，我们按不能用的点走。

先将所有不能用的点按x为第一关键字，y为第二关键字排序

接下来我们设dp[i]表示从原点到i点**不经过其他不能用的点**的方案数

其中枚举的所有i点都是不能用的点（或终点），以下给出原理：

其实我们可以设dp[i]是所有点的方案数，但这样时空都承受不了

但我们会发现，不能用的点是很少的，于是我们仅需讨论不能用的点即可

因为讨论到任何一个点的方案数，都只需要这个点之前不能用的点的方案数

所以这样做是正确的

对所有i，dp[i]的初值应当都是原点到i的方案数（即C(xi+yi,xi)）

而为了不经过其他的“障碍”点，我们需要排除前面一些“障碍”点的方案

对于每个i，我们仅需枚举所有i之前的j，使xi>=xj,yi>=yj

然后dp[i]-=dp[j]·C(xi-xj+yi-yj,xi-xj)

这里算出的就是同时至少经过i，j两点的方案数

至于会不会重叠，由于我们按x，y排过序，再考虑原先的dp[j]都是只经过j这一个障碍物的，所以不会有重叠

最后贴个代码，线性筛阶乘逆元+组合数dp

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#define ll long long
#define mode 1000000007
#define maxn 200000
using namespace std;
ll inv[200005];
ll mul[200005];
void init()
{
  inv[1]=1;
  inv[0]=1;
  mul[0]=1;
  for(int i=2;i<=maxn;i++)
    {
      inv[i]=(mode-mode/i)*inv[mode%i]%mode;
    }
  for(int i=1;i<=maxn;i++)
    {
      inv[i]*=inv[i-1];
      inv[i]%=mode;
      mul[i]=mul[i-1]*i;
      mul[i]%=mode;
    }
}
int n,m,k;
struct Bad
{
  int x,y;
}p[3005];
ll dp[3005];
bool cmp(Bad a,Bad b)
{
  if(a.x==b.x)
    {
      return a.y<b.y;
    }
  return a.x<b.x;
}
ll C(int x,int y)
{
  return mul[x]%mode*inv[y]%mode*inv[x-y]%mode;
}
int main()
{
//   freopen("path.in","r",stdin);
//   freopen("path.out","w",stdout);
  scanf("%d%d%d",&n,&m,&k);
  init();
  for(int i=1;i<=k;i++)
    {
      scanf("%d%d",&p[i].x,&p[i].y);
    }
    k++;
    p[k].x=n;
	p[k].y=m;
  sort(p+1,p+k+1,cmp);
  for(int i=1;i<=k;i++)
    {
      dp[i]=C(p[i].x+p[i].y,p[i].x);
      for(int j=1;j<i;j++)
	{
	  if(p[j].x<=p[i].x&&p[j].y<=p[i].y)
	    {
	      dp[i]-=dp[j]*C(p[i].x-p[j].x+p[i].y-p[j].y,p[i].x-p[j].x)%mode;
	    }
	}
      dp[i]=(dp[i]%mode+mode)%mode;
    }
  printf("%lld\n",dp[k]);
  return 0;
}

```

---

## 作者：Gorenstein (赞：3)

计数类dp问题。

首先考虑没有黑格子的限制的问题。此时就是一个 $H\times W$的棋盘，从左上角走到右下角的方案数，为 $C_{H+W-2}^{H-1}$。

题目中要求对结果模数。设 $p=10^9+7$，因此可以分别将分子 $n!\bmod p$、分母 $m!(n-m)!\bmod p$，然后快速幂计算分母的乘法逆元，即$\left(m!(n-m)!\right)^{p-2}$。求组合数的时候将分子乘以分母的乘法逆元，即可得到组合数。预处理的复杂度为 $O(n)$。

求阶乘以及逆元：

```
jc[0]=1,jcinv[0]=1;
for(int i=1;i<=200000;i++){
	jc[i]=jc[i-1]*i%mod;
	jcinv[i]=power(jc[i],mod-2);
}
```

求组合数：

```
int C(int n,int m){
	return jc[n]*jcinv[m]%mod*jcinv[n-m]%mod;
}
```

现在题目加上了黑格子的限制。因此，我们需要求出**从左上角到右下角经过了至少一个黑色格子的方案数**，二者相减就是答案。

把所有黑色格子按照行、列递增的顺序排序。 **设 $f_i$表示从左上角走到第$i$个黑色格子，并且途中不经过其他黑色格子的路线数。** 假设左上角是第$0$个黑色格子，右下角是第 $N+1$ 个黑色格子。设第$i$个黑色格子在 $\left(x_i,y_i\right)$。此时答案显然为 $f_{N+1}$。

将从左上角到 $(x_i,y_i)$中，至少经过一个黑色格子的路线分为两部分。考虑在第$i$个黑色格子之前的任意一个黑色格子$j$，作为从左上角到 $(x_i,y_i)$ 经过的**第一个**黑色格子。此时$j$将路线分为了两部分，第一部分是不经过任何黑棋的，即$f_j$；第分是从$j$到$i$的所有路线。根据分步乘法原理，两者相乘就得到了**以第$j$个黑格子作为到第$i$个黑格的路线中的第一个黑格子**的所有路线。

根据加法原理，枚举每个$j(j<i)$，按照上述方法累计，即可得到从左上角到右下角经过了至少一个黑色格子的方案数。然后将没有限制的总方案数减去即可。

因此 **$f_i$ 为不考虑黑色格子的情况下的总数，减去从左上角到$j$之前不经过任何一个黑色格子的总数乘以从$j$到$i$的路线总数。** 可得状态转移方程

$$
f_i=\dbinom{x_{i}-1+y_{i}-1}{x_i-1}-\sum\limits_{j=0}^{i-1}f_i\times\dbinom{x_i-x_j+y_i-y_j}{x_i-x_j}\quad(x_j\leq x_i,y_j\leq y_i)
$$

```
sort(a+1,a+n+1);
a[n+1].x=h,a[n+1].y=w;
for(int i=1;i<=n+1;i++){
	f[i]=C(a[i].x+a[i].y-2,a[i].x-1);
	for(int j=1;j<i;j++){
		if(a[j].x>a[i].x||a[j].y>a[i].y)continue;
		f[i]=(f[i]-(long long)f[j]*C(a[i].x+a[i].y-a[j].x-a[j].y,a[i].x-a[j].x))%mod;
	}
}
```

最后结果为 $f_{N+1}$.

放AC代码以供参考。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define x first
#define y second
const int SIZE=2010;
pair<int,int> a[SIZE];
int h,w,n,f[SIZE],mod=1000000007;
long long jc[200010],jcinv[200010];
int C(int n,int m){return jc[n]*jcinv[m]%mod*jcinv[n-m]%mod;}
long long power(long long a,long long b){
	long long c=1;
	for(;b;b>>=1){
		if(b&1)c=c*a%mod;
		a=a*a%mod;
	}
	return c;
}
int main(){
	jc[0]=1,jcinv[0]=1;
	for(int i=1;i<=200000;i++){
		jc[i]=jc[i-1]*i%mod;
		jcinv[i]=power(jc[i],mod-2);
	}
	cin>>h>>w>>n;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+n+1);
	a[n+1].x=h,a[n+1].y=w;
	for(int i=1;i<=n+1;i++){
		f[i]=C(a[i].x+a[i].y-2,a[i].x-1);
		for(int j=1;j<i;j++){
			if(a[j].x>a[i].x||a[j].y>a[i].y)continue;
			f[i]=(f[i]-(long long)f[j]*C(a[i].x+a[i].y-a[j].x-a[j].y,a[i].x-a[j].x))%mod;
		}
	}
	cout<<(f[n+1]+mod)%mod<<endl;
	return 0;
}
```

---

## 作者：RyexAwl (赞：3)

我们可以知道，从点$\left (x_i,y_i \right )$到点$\left (x_j,y_j \right )$的路径数为$\binom{x_j-x_i+y_j-y_i}{x_j-x_i}$

不考虑黑白格子的限制，从点$\left ( 1,1\right )$到$(h,w)$的路径共有$\binom{h+w-2}{h-1}$种。

如果存在一个黑格子，那么所有经过当前黑格子到$(h,w)$的路径都不合法。

考虑两部分，即从$(1,1)→(x_i,y_i)$与$(x_i,y_i)→(h,w)$

根据乘法原理，从经过黑格子$(x_i,y_i)$到$(h,w)$的总路径为

$$
\binom{x_i+y_i-2}{x_i-1}\times \binom{h-x_i+w-y_i}{h-x_i}
$$

其中要满足$x_i≤h,y_i≤w$

考虑两个黑格子的情况，$(x_i,y_i),(x_j,y_j)$其中$(x_i,y_i)$在$(x_j,y_j)$的前面。

如果两个格子都像前面那样计算，则会产生重复计数。

即从$(x_i,y_i)→(x_j,y_j)→(h,w)$的路径会算两次。

如果我们要进行容斥，不同集合的交各不相同，其复杂度是指数级的。

我们考虑$(x_j,y_j)$的计算

如果我们每次计算黑格子的方案时，都把经过他前面的黑格子的路径给减掉，不就不会产生重复计数了吗？

设$f(i)$为在不经过前面黑格子到第$i$个黑格子的方案数。

那么有
$$
ans=\binom{h+w-2}{h-1}-\sum_{i=1}^nf(i)\binom{h-x_i+w-y_i}{h-w_i}
$$
同理对于$f(i)$有
$$
f(i)=\binom{x_i+y_i-2}{x_i-1}-\sum_{j=1}^{i-1}f(j)\binom{x_i-x_j+y_i-y_j}{x_i-x_j}
$$
代码：
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10,M = 2e3 + 10,mod = 1e9 + 7;

typedef pair<int,int> PII;

PII a[M];

int f[M];

int fac[N << 1],invfac[N << 1];

int C(int n,int m){return n<m?0:(long long)fac[n]*invfac[m]%mod*invfac[n-m]%mod;}

void init(){
    fac[0]=invfac[0]=invfac[1]=1;
    for(int i=1;i<=2e5 + 10;i++)fac[i]=(long long)fac[i-1]*i%mod;
    for(int i=2;i<=2e5 + 10;i++)invfac[i]=(long long)(mod-mod/i)*invfac[mod%i]%mod;
    for(int i=2;i<=2e5 + 10;i++)invfac[i]=(long long)invfac[i-1]*invfac[i]%mod;
}

int main(){
    init();
    int h,w,n;
    cin >> h >> w >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i].first >> a[i].second;
    }
    sort(a + 1,a + n + 1);
    a[n + 1].first = h,a[n + 1].second = w;
    for (int i = 1; i <= n + 1; i++){
        f[i] = C(a[i].first+a[i].second - 2,a[i].first - 1);
        for (int j = 1; j < i; j++){
            if (a[j].first > a[i].first || a[j].second > a[i].second) continue;
            f[i] = (f[i] - 1ll * f[j] * C(a[i].first-a[j].first+a[i].second-a[j].second,a[i].first-a[j].first) + mod) % mod;
        }
    }  
    cout << (f[n + 1] + mod) % mod;
    return 0;
}

```


---

## 作者：冒泡ioa (赞：3)

> [博客链接](http://bubbleioa.top/archives/917)

## 题解
先介绍一个东西：多重集(multiset)的全排列（这里是特殊情况，即选的元素个数不超过任意集合中元素个数的情况）  
我们定义集合的集合为多重集，比如我有 $a_1$ 个 $1$ ， $a_2$ 个 $2$ …… $a_n$ 个 $n$ 。  
那么写成多重集就是 [latex]\left\{\left\{a_1·1\right\},\left\{a_2·2\right\},\cdots,\left\{a_n·n\right\}\right\}[/latex]  
如果我们要从中取 $k$ 个数（上面说了，$k$ 不大于 $a_i$），那么有多少种方案呢？

具体证明请移步至[维基百科](https://en.wikipedia.org/wiki/Multiset)，这里直接给出结论：
![multiset](https://wikimedia.org/api/rest_v1/media/math/render/svg/3085c625fdc63db0b0cf48f07516a78a87109a56)  
也就是 $C_{n+k-1}^{n+1}$  

那么这题其实如果我们把每一行看成一个集合，元素个数就是列数-1（因为我们最终目标是走到右下角，而如果走到了右侧，再走到右下角的方案已经确定，随意等价于走到右侧），如果没有黑格子的话，我们要选的元素个数也是列数-1，答案就是 $C_{H+W-2}^{H-1}$

而如果有黑格子，我们可以统计出不合法的方案数减去即可。

所谓不合法，就是在路径上走到过黑格子，为了避免重复，我们设 $f[i]$ 为只经过第 $i$ 个黑格子的方案数，对于它的求法，可以把它当成右下角，求贡献，对于区域内的黑格子，根据乘法原理，它们产生的不合法的方案数为 $f[j]\times C_{x_i-x_j+y_i-y_j}^{x_i-x_j}$ 即原点到他的方案数乘上以第 $j$ 个黑格子为左上角，第 $i$ 个黑格子为右下角的子矩阵的方案数。

具体实现时可以按照坐标排个序，减少枚举量，设右下角为第 $n+1$ 个黑格子，方便计算答案，还有就是不要弄混横纵坐标。

## 代码
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
const int MOD=1e9+7;
int h,w,n,ans; 
pair<int,int>node[2003];
ll fact[200003];
ll inv[200003];
ll f[2003];

ll qpow(ll a,ll b,ll p){
    ll ans=1;
    while(b){
        if(b&1)ans=ans*a%p;
        a=a*a%p;
        b>>=1;
    }
    return ans;
}

void pre(int n){
    fact[0]=1;
    for(int i=1;i<=n;i++){
        fact[i]=fact[i-1]*i%MOD;
    }
    inv[n]=qpow(fact[n],MOD-2,MOD);
    for(int i=n-1;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

int C(int n,int m){
    if(n==m)return 1; 
    return fact[n]*inv[m]%MOD*inv[n-m]%MOD;
}

int main(){
    cin>>h>>w>>n;
    for(int i=1;i<=n;i++){
        cin>>node[i].x>>node[i].y;
    }
    pre(200000);
    node[n+1].x=h,node[n+1].y=w;
    sort(node+1,node+2+n);
    for(int i=1;i<=n+1;i++){
        f[i]=C(node[i].x+node[i].y-2,node[i].x-1);
        for(int j=1;j<i;j++){
            if(node[i].x<node[j].x||node[i].y<node[j].y)continue;
            f[i]=(f[i]-(ll)f[j]*C(node[i].y-node[j].y+node[i].x-node[j].x,node[i].x-node[j].x)%MOD)%MOD;
        }
        while(f[i]<0)f[i]+=MOD;
    }
    cout<<f[n+1]<<endl;
    return 0;
}

```

---

## 作者：Martian148 (赞：2)

# Link
[CF559C Gerald and Giant Chess](https://www.luogu.com.cn/problem/CF559C)

# Solve
有一个结论，对于一个$W$和$H$的白色方格，从$(1,1)$到$(H,W)$的方案数是$C_{H+W-2}^{H-1}$

直接考虑不能走黑色的比较难，于是想到容斥一下，把总的方案数-经过黑点的方案数=不走黑色的方案数

因为黑点的数比较少，于是用黑点来$DP$,先把黑点按照$x$排序

定义$F[i]$表示从左上角走到$i$这个黑色节点的位置，不经过其他黑点的方案数

由于总的方案数-经过至少一个黑点的方案数=不经过其他黑点的方案数

经过至少一个黑点的方案数=不经过白点到一个黑点，后面乱走，枚举每个满足的黑点，把答案累计起来就好了

所以转移方程就退出来了

$$F[i]=C_{x_i-1+y_i-1}^{x_i-1}-\sum_{j=0}^{i-1}F[j]\ast C_{x_i-x_j+y_i-y_j}^{x_i-x_j}$$

其中$x_i≥x_j,y_i≥y_j$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2005,TT=1000000007;
typedef long long LL;
int H,W,N;
pair<int,int> a[maxn];
LL jc[200005],jcinv[200005],F[maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
LL fast_pow(LL a,LL b){
	LL s=1,w=a;
	while(b){
		if(b&1)s=s*w%TT;
		w=w*w%TT;
		b>>=1;
	}
	return s;
}
LL C(LL x,LL y){
	return jc[x]*jcinv[y]%TT*jcinv[x-y]%TT;
}
int main(){
	jc[0]=1;jcinv[0]=1;
	for(int i=1;i<=200000;i++){
		jc[i]=jc[i-1]*i%TT;
		jcinv[i]=fast_pow(jc[i],TT-2);
	}
	H=read();W=read();N=read();
	for(int i=1;i<=N;i++)a[i].first=read(),a[i].second=read();
	sort(a+1,a+1+N);
	a[N+1].first=H,a[N+1].second=W;
	for(int i=1;i<=N+1;i++){
		F[i]=C(a[i].first+a[i].second-2,a[i].first-1);
		for(int j=1;j<i;j++){
			if(a[j].first>a[i].first||a[j].second>a[i].second)continue;
			F[i]=(F[i]-F[j]*C(a[i].first+a[i].second-a[j].first-a[j].second,a[i].first-a[j].first)%TT+TT)%TT;
		}
	}
	printf("%lld\n",(F[N+1]+TT)%TT);
	return 0;
}
```

---

## 作者：crashed (赞：2)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/CF559C)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先以$x$为第一关键字，$y$为第二关键字，给点进行排序。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后......似乎可以用容斥解决......然后时间为$O(2^n)$，爆炸了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不过，这道题其实阔以$DP$的，时间是$O(n^2)$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~好棒棒哟，底数和指数交换了~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;定义状态：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$DP(i)$：走到第$i$个障碍点并且不经过其它障碍点的总方案数。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设第$i$个点位于$(x_i,y_i)$，转移很容易看出来：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle DP(i)=C_{x_i+y_i-2}^{x_i-1}-\sum_{j=1}^{i-1}C_{x_i-x_j+y_i-y_j}^{x_i-x_j}DP(j)$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不需要考虑前面的点中有点在自己下面，因为这样的话组合数就是$0$，这一项自然就被消掉了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;另外，也可以看一下[[BZOJ 4767]两双手](https://www.lydsy.com/JudgeOnline/problem.php?id=4767)跟这道题类似，就是多了一个扩欧解同余方程的步骤。
# 代码
```cpp
#include <cstdio>
#include <algorithm>

const int mod = 1e9 + 7;
const int MAXN = 2005, MAXH = 100005;

template<typename _T>
void read( _T &x )
{
    x = 0;char s = getchar();int f = 1;
    while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
    while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
    x *= f;
}

template<typename _T>
void write( _T x )
{
    if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
    if( 9 < x ){ write( x / 10 ); }
    putchar( x % 10 + '0' );
}

struct obstacle
{
	int x, y;
	obstacle(){}
	obstacle( const int X, const int Y )
	{
		x = X, y = Y;
	}
	bool operator < ( const obstacle & other ) const
	{
		return x < other.x || ( x == other.x && y < other.y );
	}
}a[MAXN];

int DP[MAXN];
int fac[MAXH * 3], inv[MAXH * 3];
int N, H, W;

void init()
{
	fac[0] = fac[1] = 1;
	inv[1] = 1;
	for( int i = 2 ; i <= H + W ; i ++ )
	{
		fac[i] = 1ll * fac[i - 1] * i % mod;
		inv[i] = 1ll * ( mod - mod / i ) * inv[mod % i] % mod;
	}
	inv[0] = 1;
	for( int i = 1 ; i <= H + W ; i ++ )
	{
		inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
	}
}

int C( const int n, const int m )
{
	if( n < m ) return 0;
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int fix( const int a )
{
	return ( a % mod + mod ) % mod;
}

int main()
{
	read( H ), read( W ), read( N );
	init();
	for( int i = 1 ; i <= N ; i ++ )
	{
		read( a[i].x ), read( a[i].y );
	}
	a[++N] = obstacle( H, W );
    //把目标点当做一个障碍点，然后就可以无脑DP了
	std :: sort( a + 1, a + 1 + N );
	for( int i = 1 ; i <= N ; i ++ )
	{
		DP[i] = C( a[i].x + a[i].y - 2, a[i].y - 1 );
		for( int j = 1 ; j < i ; j ++ )
		{
			DP[i] = fix( DP[i] - 1ll * DP[j] * C( a[i].x - a[j].x + a[i].y - a[j].y, a[i].x - a[j].x ) % mod );
		}
	}
	write( DP[N] ), putchar( '\n' );
	return 0;
}
```

---


# [ABC168F] . (Single Dot)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc168/tasks/abc168_f

無限に広がる草原があります。

この草原上に、大きさが無視できるほど小さい $ 1 $ 頭の牛がいます。牛の今いる点から南に $ x\ \mathrm{cm} $、東に $ y\ \mathrm{cm} $ 移動した点を $ (x,\ y) $ と表します。牛自身のいる点は $ (0,\ 0) $ です。

また、草原には $ N $ 本の縦線と $ M $ 本の横線が引かれています。$ i $ 本目の縦線は点 $ (A_i,\ C_i) $ と点 $ (B_i,\ C_i) $ とを結ぶ線分、$ j $ 本目の横線は点 $ (D_j,\ E_j) $ と点 $ (D_j,\ F_j) $ とを結ぶ線分です。

牛が線分を(端点を含め)通らない限り自由に動き回れるとき、牛が動き回れる範囲の面積は何 $ \mathrm{cm^2} $ でしょうか。この範囲の面積が無限大である場合は代わりに `INF` と出力してください。

## 说明/提示

### 制約

- 入力はすべて $ -10^9 $ 以上 $ 10^9 $ 以下の整数
- $ 1\ \leq\ N,\ M\ \leq\ 1000 $
- $ A_i\ <\ B_i\ (1\ \leq\ i\ \leq\ N) $
- $ E_j\ <\ F_j\ (1\ \leq\ j\ \leq\ M) $
- 点 $ (0,\ 0) $ はどの与えられた線分上にも位置しない

### Sample Explanation 1

牛が動き回れる範囲の面積は $ 13\ \mathrm{cm^2} $ です。 !\[Sample 1\](https://img.atcoder.jp/abc168/education.png "Sample 1")

### Sample Explanation 2

牛が動き回れる範囲の面積は無限大です。

## 样例 #1

### 输入

```
5 6
1 2 0
0 1 1
0 2 2
-3 4 -1
-2 6 3
1 0 1
0 1 2
2 0 2
-1 -4 5
3 -2 4
1 2 4```

### 输出

```
13```

## 样例 #2

### 输入

```
6 1
-3 -1 -2
-3 -1 1
-2 -1 2
1 4 -2
1 4 -1
1 4 1
3 1 4```

### 输出

```
INF```

# 题解

## 作者：iiiiiyang (赞：4)

[虚拟的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17489227.html)

[题目链接](https://www.luogu.com.cn/problem/AT_abc168_f)

挺套路的题。如果值域和线段数量同阶，可以预处理不能越过的线段，使用状压四个方向记录每个节点能不能往这个方向走，然后直接爆搜就好了，标记上能走到哪些地方。但这个值域一看就是没有救的，于是就要拿出来离散化了。把线段的横纵坐标都拎出来离散化，依然是同样的预处理，然后从**离散化后的 $(0,0)$** 开始向外爆搜，最后还是扫一遍能够到哪些地方，统计答案只需要变成离散化前的对应位置即可。唯一需要注意的地方是放入边界横纵坐标一定要比数据范围大一点，本人最开始边界放 $10^9$ 疯狂 WA。于是总复杂度为 $\mathcal O(nm + n \log n + m \log m)$，分别为搜索和离散化。直接这样说可能还是有些抽象了，不过代码非常清晰。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
#define gcd(x,y) (__gcd((x),(y)))
#define lcm(x,y) ((x)*(y)/gcd((x),(y)))
#define lg(x,y)  (__lg((x),(y)))
using namespace std;

namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        putchar(ch);
        return;
    }
}
using namespace FastIO;

inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}

bool Mbe;

namespace LgxTpre
{
    static const int MAX=5010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    static const int mod=1e9+7;
    static const int bas=131;
    
    int n,m,ans;
    int a[MAX],b[MAX],c[MAX],d[MAX],e[MAX],f[MAX];
    int X[MAX],Y[MAX],cntx,cnty;
    #define lbx(x) lower_bound(X+1,X+cntx+1,x)-X
    #define lby(y) lower_bound(Y+1,Y+cnty+1,y)-Y
    
    int dx[]={0,0,1,-1};
    int dy[]={1,-1,0,0};
    int sx,sy,obs[MAX][MAX],vis[MAX][MAX];
    void dfs(int x,int y)
    {
    	if(x<1||y<1||x>cntx||y>cnty||vis[x][y]) return;
    	vis[x][y]=1;
    	for(int i=0;i<4;++i) if(!(obs[x][y]>>i&1)) dfs(x+dx[i],y+dy[i]);
	}
	
    inline void lmy_forever()
	{
		X[++cntx]=-1.1e9,X[++cntx]=0,X[++cntx]=1.1e9,
		Y[++cnty]=-1.1e9,Y[++cnty]=0,Y[++cnty]=1.1e9;
		read(n,m);
		for(int i=1;i<=n;++i) read(a[i],b[i],c[i]),X[++cntx]=a[i],X[++cntx]=b[i],Y[++cnty]=c[i];
		for(int i=1;i<=m;++i) read(d[i],e[i],f[i]),X[++cntx]=d[i],Y[++cnty]=e[i],Y[++cnty]=f[i];
		sort(X+1,X+cntx+1),cntx=unique(X+1,X+cntx+1)-X-1;
		sort(Y+1,Y+cnty+1),cnty=unique(Y+1,Y+cnty+1)-Y-1;
		for(int i=1;i<=n;++i) 
		{
			int l=lbx(a[i]),r=lbx(b[i]),y=lby(c[i]);
			for(int j=l;j<r;++j) obs[j][y]|=1<<1,obs[j][y-1]|=1<<0;
		}
		for(int i=1;i<=m;++i)
		{
			int x=lbx(d[i]),l=lby(e[i]),r=lby(f[i]);
			for(int j=l;j<r;++j) obs[x][j]|=1<<3,obs[x-1][j]|=1<<2;
		}
		sx=lbx(0),sy=lby(0),dfs(sx,sy);
		for(int i=1;i<=cntx;++i) if(vis[i][1]||vis[i][cnty]) return puts("INF"),void();
		for(int i=1;i<=cnty;++i) if(vis[1][i]||vis[cntx][i]) return puts("INF"),void();
		for(int i=2;i<cntx;++i) for(int j=2;j<cnty;++j) if(vis[i][j]) ans+=(X[i+1]-X[i])*(Y[j+1]-Y[j]);
		write(ans,'\n');
    }
}

bool Med;

signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

## 作者：_Yonder_ (赞：0)

垃圾样例。

这题奶牛的面积可以视为 $\frac{1}{2}\times\frac{1}{2}$，题面也没说太清楚，害我看错题。

显然的，这题是要我们跑洪水填充，但这个值域令人汗颜！但我们应该能很快的想到离散化。

我们把牛的起点变为 $(\frac{1}{2},\frac{1}{2})$，这样就能更加直白、轻松的处理不穿过线段的条件了。对点打上不可以往哪个方向走的标记即可。

---

## 作者：blln (赞：0)

#### 详细思路

把每一条东西线的 $Y$ 坐标和南北线的 $X$ 坐标记录下来并排序和去重。

把草地压缩成 $N\times M$ 的表格。

在每两个格子之间加一个格子。（如果有两个格子之间边阻挡，就标记，在数组标记。）

在边缘一圈标记掉。

最后在包含 $(0,0)$ 的格子开始跑一遍 floodfill（洪水填充法）。即从该格子向周围的格子扩散，直到无法扩散为止。

#### 具体实现

```cpp
#include<cstdio>
long long n,m,N,M,v,t,L=0,R=0,Z=0,X,Y,a[1005][3],b[1005][3],kx[10005],ky[1005],tx[1005],ty[1005],map[2005][2005],d[4000005][2],f[2005][2005],sum=0;
long long dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
void pxa(long long x,long long y){
    long long l=x,r=y,mid=a[(l+r)/2][0];
    while(l<=r){
        while(a[l][0]<mid)l++;
        while(a[r][0]>mid)r--;
        if(l<=r){
            v=a[l][0];a[l][0]=a[r][0];a[r][0]=v;
            v=a[l][1];a[l][1]=a[r][1];a[r][1]=v;
            v=a[l][2];a[l][2]=a[r][2];a[r][2]=v;
            l++;r--;
        }
    }
    if(x<r)pxa(x,r);
    if(l<y)pxa(l,y);
    return;
}
void pxb(long long x,long long y){
    long long l=x,r=y,mid=b[(l+r)/2][0];
    while(l<=r){
        while(b[l][0]<mid)l++;
        while(b[r][0]>mid)r--;
        if(l<=r){
            v=b[l][0];b[l][0]=b[r][0];b[r][0]=v;
            v=b[l][1];b[l][1]=b[r][1];b[r][1]=v;
            v=b[l][2];b[l][2]=b[r][2];b[r][2]=v;
            l++;r--;
        }
    }
    if(x<r)pxb(x,r);
    if(l<y)pxb(l,y);
    return;
}
int main(){
    scanf("%lld %lld",&n,&m);
    for(int i=1;i<=n;i++)scanf("%lld %lld %lld",&a[i][1],&a[i][2],&a[i][0]);
    for(int i=1;i<=m;i++)scanf("%lld %lld %lld",&b[i][0],&b[i][1],&b[i][2]);
    pxa(1,n);pxb(1,m);N=1;M=1;
    kx[1]=a[1][0];ky[1]=b[1][0];tx[1]=1;ty[1]=1;
    for(int i=2;i<=n;i++){if(a[i][0]!=a[i-1][0])kx[++N]=a[i][0];tx[i]=N;}
    for(int i=2;i<=m;i++){if(b[i][0]!=b[i-1][0])ky[++M]=b[i][0];ty[i]=M;}
    if(kx[1]>0||ky[1]>0||kx[N]<0||ky[M]<0){printf("INF");return 0;}
    for(int i=1;i<=N;i++)map[i*2-1][1]=map[i*2-1][2*M+1]=-2;
    for(int i=1;i<=M;i++)map[1][i*2-1]=map[2*N+1][i*2-1]=-2;
    map[2*N+1][2*M+1]=-2;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            map[i*2][j*2]=-1;
        }
    }
    for(int i=2;i<=N;i++){
        for(int j=2;j<=M;j++){
            map[i*2-1][j*2-1]=(kx[i]-kx[i-1])*(ky[j]-ky[j-1]);
            if((kx[i]>=0&&kx[i-1]<=0)&&(ky[j]>=0&&ky[j-1]<=0)){
                R++;d[R][0]=i*2-1;d[R][1]=j*2-1;f[i*2-1][j*2-1]=1;sum+=map[i*2-1][j*2-1];
            }
        }
    }
    t=1;
    for(int i=2;i<=N;i++){
        for(int j=1;j<=m;j++){
            if(b[j][1]<=kx[i-1]&&kx[i]<=b[j][2]){
                map[i*2-1][ty[j]*2]=-1;
            }
        }
    }
    t=1;
    for(int i=2;i<=M;i++){
        for(int j=1;j<=n;j++){
            if(a[j][1]<=ky[i-1]&&ky[i]<=a[j][2]){
                map[tx[j]*2][i*2-1]=-1;
            }
        }
    }
    while(L<R){
        L++;
        for(int i=0;i<4;i++){
            X=d[L][0]+dx[i];Y=d[L][1]+dy[i];
            if(X>0&&X<=2*N+1&&Y>0&&Y<=2*M+1){
                if(f[X][Y]==0&&map[X][Y]!=-1){
                    if(map[X][Y]==-2){printf("INF");return 0;}
                    else{
                        f[X][Y]=1;sum+=map[X][Y];
                        R++;d[R][0]=X;d[R][1]=Y;
                    }
                }
            }
        }
    }
    printf("%lld",sum);
}
```


---


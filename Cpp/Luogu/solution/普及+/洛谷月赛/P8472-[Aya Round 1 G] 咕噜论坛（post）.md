# [Aya Round 1 G] 咕噜论坛（post）

## 题目描述

「咕噜论坛」的一篇帖子下，有若干个不同的人对其进行了回复，这些评论形成了一个 $n\times m$ 的矩阵。

论坛管理员 prAB 发现这些评论者的名字颜色只有灰名、紫名和棕名三种，他决定「动用神权」来增加这些评论的整齐度。但是论坛站长超氧化铯（CsO2）可能会因为他「滥用神权」导致论坛「臭名昭著」而踢掉他的管理身份。所以 prAB **最多**只能动用 $k$ 次神权。已知他的神权有两种：

- 「暴政警告」：送一个灰名进陶片使他变成棕名。
- 「放人一马」：将一个棕名解封使他变成灰名。

由于「咕噜论坛」的管理员是至高无上的，对于评论中的紫名他无能为力。

prAB 认为在这些评论者的名字颜色中，最大的颜色相同的子矩阵的大小能代表这篇帖子评论的整齐度。所以他想知道，他动用完神权后评论的整齐度的最大值。

## 说明/提示

### 数据范围及约定

对于 $100\%$ 的数据，$1 \le n,m\le 500$，$0 \le k \le nm$。字符矩阵中只会出现大写字母 `B`、`G` 和 `P`。

## 样例 #1

### 输入

```
3 4 2
BBGB
GBBB
PGPP```

### 输出

```
8
BBBB
BBBB
PGPP```

# 题解

## 作者：chen_zhe (赞：14)

预处理出 $\texttt G$ 和 $\texttt P$ 的二维前缀和，以便后续计算。

进行计算的时候，只需枚举子矩阵的第一行和最后一行，判断这其中需要改的名字颜色数量是否小于等于 $k$（即可以用神权将其全部变得相同），这里可以用二维前缀和差分完成。接着，使用双指针（two-pointers）便可计算出子矩阵的最大整齐度。

输出方案也类似，通过记录下最大整齐度的子矩阵选择的四个顶点，通过对其内部的元素判断之后便可构造。

注意有一种 corner cases：最大子矩阵为全紫名矩阵。

时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,ans,ansxl,ansxr,ansyl,ansyr;
int sum[505][505],cnt[505][505];
char s[505][505];
bool check1(int xl,int xr,int yl,int yr)
{
    if(cnt[xr][yr]-cnt[xr][yl-1]-cnt[xl-1][yr]+cnt[xl-1][yl-1]>0)
        return 0;
    if(sum[xr][yr]-sum[xr][yl-1]-sum[xl-1][yr]+sum[xl-1][yl-1]<=k)
        return 1;
    if(sum[xr][yr]-sum[xr][yl-1]-sum[xl-1][yr]+sum[xl-1][yl-1]>=(xr-xl+1)*(yr-yl+1)-k)
        return 1;
    return 0;
}
bool check2(int xl,int xr,int yl,int yr)
{
    if(cnt[xr][yr]-cnt[xr][yl-1]-cnt[xl-1][yr]+cnt[xl-1][yl-1]==(xr-xl+1)*(yr-yl+1))
        return 1;
    else
        return 0;
}
int main()
{
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++)
    {
        cin >> (s[i]+1);
        for(int j=1;j<=m;j++)
        {
            sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+(s[i][j]=='G');
            cnt[i][j]=cnt[i][j-1]+cnt[i-1][j]-cnt[i-1][j-1]+(s[i][j]=='P');
        }
    }
    for(int yl=1;yl<=m;yl++)
    {
        for(int yr=yl;yr<=m;yr++)
        { 
            int l=1,r=0;
            while(r<=n && l<=n)
            {
                while(r<n && check1(l,r+1,yl,yr))
                    r++;
                if((yr-yl+1)*(r-l+1)>ans)
                {
                    ansxl=l;
                    ansxr=r;
                    ansyl=yl;
                    ansyr=yr;
                    ans=(yr-yl+1)*(r-l+1);
                }
                l++;
            }
        }
    }
    for(int yl=1;yl<=m;yl++)
    {
        for(int yr=yl;yr<=m;yr++)
        { 
            int l=1,r=0;
            while(r<=n && l<=n)
            {
                while(r<n && check2(l,r+1,yl,yr))
                    r++;
                if((yr-yl+1)*(r-l+1)>ans)
                {
                    ansxl=l;
                    ansxr=r;
                    ansyl=yl;
                    ansyr=yr;
                    ans=(yr-yl+1)*(r-l+1);
                }
                l++;
            }
        }
    }
    cout << ans << endl;
    if(check2(ansxl,ansxr,ansyl,ansyr))
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
                cout << s[i][j];
            cout << endl;
        }
    }
    else if(sum[ansxr][ansyr]-sum[ansxr][ansyl-1]-sum[ansxl-1][ansyr]+sum[ansxl-1][ansyl-1]<=k)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                if(i>=ansxl && i<=ansxr && j>=ansyl && j<=ansyr)
                    cout << 'B';
                else
                    cout << s[i][j];
            }
            cout << endl;
        }
    }
    else 
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                if(i>=ansxl && i<=ansxr && j>=ansyl && j<=ansyr)
                    cout << 'G';
                else
                    cout << s[i][j]; 
            }
            cout << endl;
        }
    }
    return 0;
}
```

验题人 @离散小波变换° 的代码：

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN=500+3;
int A[MAXN][MAXN],B[MAXN][MAXN],C[MAXN][MAXN];
int qry(int T[][MAXN],int l1,int l2,int r){
    return T[l2][r]-T[l1-1][r];
}
char S[MAXN][MAXN];
int n,m,k;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int ans=-1,a1,a2,a3,a4,a5;
int main(){
    n=qread(),m=qread(),k=qread();
    up(1,n,i) scanf("%s",S[i]+1);
    up(1,n,i) up(1,m,j){
        A[i][j]=(S[i][j]=='P')+A[i-1][j];
        B[i][j]=(S[i][j]=='B')+B[i-1][j];
        C[i][j]=(S[i][j]=='G')+C[i-1][j];
    }
    up(1,n,i) up(i,n,j){
        int sp=0,sb=0,sg=0,lp=1,lb=1,lg=1,x=j-i+1;
        up(1,m,r){
            int wp=qry(A,i,j,r); sp+=wp;
            int wb=qry(B,i,j,r); sb+=wb;
            int wg=qry(C,i,j,r); sg+=wg;
            if(wp    ) lb=r+1,lg=r+1,sb=sg=0;
            if(wb||wg) lp=r+1,sp=0;
            while(lp<=r&&x*(r-lp+1)-sp>k) sp-=qry(A,i,j,lp),++lp;
            while(lb<=r&&x*(r-lb+1)-sb>k) sb-=qry(B,i,j,lb),++lb;
            while(lg<=r&&x*(r-lg+1)-sg>k) sg-=qry(C,i,j,lg),++lg;
            if(x*(r-lp+1)>ans) ans=x*(r-lp+1),a1=i,a2=lp,a3=j,a4=r,a5='P';
            if(x*(r-lb+1)>ans) ans=x*(r-lb+1),a1=i,a2=lb,a3=j,a4=r,a5='B';
            if(x*(r-lg+1)>ans) ans=x*(r-lg+1),a1=i,a2=lg,a3=j,a4=r,a5='G';
        }
    }
    up(a1,a3,i) up(a2,a4,j) S[i][j]=a5;
    printf("%d\n",ans);
    up(1,n,i) printf("%s\n",S[i]+1);
    return 0;
}
```

---

## 作者：KingPowers (赞：8)

首先看到题目很容易联想到二维前缀和，于是我们可以预处理出三种颜色的二维前缀和 $sumB,sumG,sumP$，方便我们后续的计算。

考虑暴力做法：枚举子矩阵的上下左右边界，然后通过我们预处理出来的前缀和来判断该子矩阵是否可以成为答案，这样的时间复杂度为 $O(n^2m^2)$。但是我们观察数据，发现 $n,m\le500$，这样的复杂度显然无法通过。

那么考虑下我们是否可以减少枚举的信息呢？其实，我们只需要枚举子矩阵的上下两行（或者左右两列）即可。为什么呢？不难发现，其实子矩阵的右边界是随着左边界的递增而递增的（这个可以自己思考一下），所以我们可以用双指针来处理子矩阵左右边界，这样时间复杂度就降到了 $O(nm^2)$，可以接受。

小细节：因为我们不能动紫色，所以用前缀和判断是否可以将子矩阵变为灰色或棕色时，该子矩阵内不能有任何紫色。同理，判断一个子矩阵是否可以全为紫色，只有该子矩阵原本就都是紫色时才可行。

最后统计答案输出即可。

code：
```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 0x7fffffff
#define PII pair<int,int>
#define fx first
#define fy second
#define mk_p make_pair
using namespace std;
const int maxn=5e3+5;
int n,m,k,sumb[maxn][maxn],sumg[maxn][maxn],sump[maxn][maxn];
int mx,ans1,ans2,ans3,ans4;
char mp[maxn][maxn],ansc;
inline int read(){
	int ans=0,flag=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flag=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flag;
}
inline bool check_B(int ax,int ay,int bx,int by){  //能否全棕
	int SB=sumb[bx][by]-sumb[bx][ay-1]-sumb[ax-1][by]+sumb[ax-1][ay-1];
	int SP=sump[bx][by]-sump[bx][ay-1]-sump[ax-1][by]+sump[ax-1][ay-1];
	if(SP) return 0;  //如上所述
	if((bx-ax+1)*(by-ay+1)-SB<=k) return 1;
	return 0;
}
inline bool check_G(int ax,int ay,int bx,int by){  //能否全灰
	int SG=sumg[bx][by]-sumg[bx][ay-1]-sumg[ax-1][by]+sumg[ax-1][ay-1];
	int SP=sump[bx][by]-sump[bx][ay-1]-sump[ax-1][by]+sump[ax-1][ay-1];
	if(SP) return 0;  //如上所述
	if((bx-ax+1)*(by-ay+1)-SG<=k) return 1;
	return 0;
}
inline bool check_P(int ax,int ay,int bx,int by){  //能否全紫
	int SP=sump[bx][by]-sump[bx][ay-1]-sump[ax-1][by]+sump[ax-1][ay-1];
	if(SP==(bx-ax+1)*(by-ay+1)) return 1;  //如上所述
	return 0;
}
signed main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++){
		scanf("%s",mp[i]+1);
		for(int j=1;j<=m;j++){  //预处理前缀和
			sumb[i][j]=sumb[i-1][j]+sumb[i][j-1]-sumb[i-1][j-1]+(mp[i][j]=='B');
			sumg[i][j]=sumg[i-1][j]+sumg[i][j-1]-sumg[i-1][j-1]+(mp[i][j]=='G');
			sump[i][j]=sump[i-1][j]+sump[i][j-1]-sump[i-1][j-1]+(mp[i][j]=='P');
		}
	}
	for(int i=1;i<=n;i++)  //全变棕
		for(int j=i;j<=n;j++)
			for(int l=1,r=0;l<=n&&r<=n;l++){
				while(r<m&&check_B(i,l,j,r+1)) r++; 
				if((r-l+1)*(j-i+1)>mx){  //整齐度更高就更新答案
					mx=(r-l+1)*(j-i+1);
					ans1=i,ans2=l,ans3=j,ans4=r,ansc='B';
				}
			}
	for(int i=1;i<=n;i++)  //全变灰
		for(int j=i;j<=n;j++)
			for(int l=1,r=0;l<=n&&r<=n;l++){
				while(r<m&&check_G(i,l,j,r+1)) r++;
				if((r-l+1)*(j-i+1)>mx){  //整齐度更高就更新答案
					mx=(r-l+1)*(j-i+1);
					ans1=i,ans2=l,ans3=j,ans4=r,ansc='G';
				}
			}
	for(int i=1;i<=n;i++)  //全紫
		for(int j=i;j<=n;j++)
			for(int l=1,r=0;l<=n&&r<=n;l++){
				while(r<m&&check_P(i,l,j,r+1)) r++;
				if((r-l+1)*(j-i+1)>mx){  //整齐度更高就更新答案
					mx=(r-l+1)*(j-i+1);
					ans1=i,ans2=l,ans3=j,ans4=r,ansc='P';
				}
			}
	for(int i=ans1;i<=ans3;i++)
		for(int j=ans2;j<=ans4;j++)
			mp[i][j]=ansc;
	printf("%lld\n",mx);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) putchar(mp[i][j]);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Jairon314 (赞：6)

> [题目链接](https://www.luogu.com.cn/problem/P8472)

$ \text{Solution} $

------------

那天做同学给隔壁普转提小朋友出的模拟赛，我验的是一个双指针里面套一个小双指针的题。突然有人发问：刚刚提高组的小朋友都学过双指针吗？

我思考了思考，好像自己从来没有学过这个东西。这个东西难道不是自然而然顺理成章就会的吗？于是隔壁的小朋友们就被迫害了，喜提骂声一片。

回到这道题，这是一个经典的最大子矩形问题。先对每个颜色进行一个 $O(n^2)$ 的二维前缀和然后再考虑。

比较暴力的想法就是 $O(n^4)$ 枚举矩形的一个对角线的两个顶点，然后发现 $O(n^4)$ 过不去，考虑优化。

既然枚举顶点行不通，那就枚举矩形的边。 $O(n^2)$ 枚举这个矩形的上边和下边所在的直线，然后多一个 $O(n)$ 的复杂度从左到右枚举此时矩形的左边。容易发现受这些限制的矩形想要满足要求且最大，右端点肯定是单调不减的。通过双指针即可做到 $O(n^3)$ 的复杂度，可以通过本题。

看下代码吧，感觉实现的比较简单：

注意同时要处理最大子矩形为全紫的情况。

[Jairon.h](https://www.luogu.com.cn/paste/bckqxxoh)

```cpp
#include <bits/stdc++.h>
using namespace std;

#define lint long long

#include <"Jairon.h">

#define maxn 1000010
#define SIZE 510

int ty;
pii ansp1,ansp2;
int n,m,k,ans=0;
int G[SIZE][SIZE];
int B[SIZE][SIZE];
int P[SIZE][SIZE];
char Map[SIZE][SIZE];

int GG(pii p1,pii p2){ return G[p2.fir][p2.sec]-G[p1.fir-1][p2.sec]-G[p2.fir][p1.sec-1]+G[p1.fir-1][p1.sec-1]; }
int BB(pii p1,pii p2){ return B[p2.fir][p2.sec]-B[p1.fir-1][p2.sec]-B[p2.fir][p1.sec-1]+B[p1.fir-1][p1.sec-1]; }
int PP(pii p1,pii p2){ return P[p2.fir][p2.sec]-P[p1.fir-1][p2.sec]-P[p2.fir][p1.sec-1]+P[p1.fir-1][p1.sec-1]; }
int SS(pii p1,pii p2){ return (p2.fir-p1.fir+1)*(p2.sec-p1.sec+1); }

int main(){
	read(n,m,k);
	FOR(i,1,n){ cin>>(Map[i]+1); }
	FOR(i,1,n){
		FOR(j,1,m){
			G[i][j]=G[i-1][j]+G[i][j-1]-G[i-1][j-1]+(Map[i][j]=='G');
			B[i][j]=B[i-1][j]+B[i][j-1]-B[i-1][j-1]+(Map[i][j]=='B');
			P[i][j]=P[i-1][j]+P[i][j-1]-P[i-1][j-1]+(Map[i][j]=='P');
		}
	}
	FOR(upper,1,n){
		FOR(lower,upper,n){
			int l=1,r=0;
			while(true){
				while(l<=m&&PP(mp(upper,l),mp(lower,l))){ ++l; r=l-1; }
				if(l>m){ break; } int R=r+1;
				while(R<=m&&SS(mp(upper,l),mp(lower,R))-GG(mp(upper,l),mp(lower,R))<=k&&PP(mp(upper,l),mp(lower,R))==0){ ++r,++R; }
				if(r<l){ ++l,++r; continue; }
				if(ans<SS(mp(upper,l),mp(lower,r))){
					ans=SS(mp(upper,l),mp(lower,r));
					ansp1=mp(upper,l); ansp2=mp(lower,r);
					ty=1;
				} ++l;
			} l=1,r=0;
			while(true){
				while(l<=m&&PP(mp(upper,l),mp(lower,l))){ ++l; r=l-1; }
				if(l>m){ break; } int R=r+1;
				while(R<=m&&SS(mp(upper,l),mp(lower,R))-BB(mp(upper,l),mp(lower,R))<=k&&PP(mp(upper,l),mp(lower,R))==0){ ++r,++R; }
				if(r<l){ ++l,++r; continue; }
				if(ans<SS(mp(upper,l),mp(lower,r))){
					ans=SS(mp(upper,l),mp(lower,r));
					ansp1=mp(upper,l); ansp2=mp(lower,r);
					ty=2;
				} ++l;
			} l=1,r=0;
			while(true){
				if(l>m){ break; } int R=r+1;
				while(R<=m&&SS(mp(upper,l),mp(lower,R))==PP(mp(upper,l),mp(lower,R))){ ++r,++R; }
				if(r<l){ ++l,++r; continue; }
				if(ans<SS(mp(upper,l),mp(lower,r))){
					ans=SS(mp(upper,l),mp(lower,r));
					ty=0; ansp2.fir=-1,ansp2.sec=-1;
				} ++l;
			}
		}
	} outn(ans);
	FOR(i,1,n){
		FOR(j,1,m){
			if(i>=ansp1.fir&&i<=ansp2.fir&&j>=ansp1.sec&&j<=ansp2.sec){ pc(ty==1?'G':'B'); }
			else{ pc(Map[i][j]); }
		} pc('\n');
	}
	return 0;
}

/**/
```


---

## 作者：封禁用户 (赞：4)

## 题意简述

给你一个 $n$ 行 $m$ 列的矩阵，其中每个元素只能是 B，G，P 三个字母中的一种。

你最多可以执行 $k$ 次操作。在每次操作中，你可以把一个 B 换成 G，或者把一个 G 换成 B。

求在进行操作后，你能得到的最大矩阵，其中在矩阵内的每个元素都相同。

$1 \leq n, m \leq 500$，$0 \leq k \leq nm$。

## 题目分析

我们首先可以枚举矩阵的上下界，接着我们可以用双指针的做法去决定矩阵的左右界。

如果矩阵需要操作的总数 $<k$ 则右指针往右跑。

如果矩阵需要操作的总数 $>k$ 则左指针往右跑。

那么我们怎么维护总数呢？很自然的想法是维护一个变量 $cnt$，存储需要操作的数量。

但是我们直接暴力的话指针跑的过程中 $cnt$ 也要更新一遍，而这个更新的操作是 $O(n)$ 的（从上往下一个个加）。

这里很明显可以用前缀和优化，只不过一般的前缀和都是横向的，我们这里需要一个纵向的前缀和。

即：

$prev[i][j] = \sum\limits_{k = 1}^{j} a[i][k]$。

查询就是：

$prev[down][j] - prev[up - 1][j]$。

每一次更新完两个指针后取最大值，并且把四个边界记录下来，最后特判输出即可。

注意，**一定要考虑矩阵内全部为P（紫名）的情况**。

这道题细节非常多，一定要想清楚了再开始码代码。

以下是我的通过代码。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, k;
char a[1000][1000];
int pre[1000][1000];
int ans, U, D, L, R;
char C;

void update(char c) { // 尝试填充灰色或者棕色 
    // 做一个纵列的前缀和 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == 'B') {
                pre[i][j] = pre[i - 1][j] + (c == 'B' ? 0 : 1);
            } else if (a[i][j] == 'G') {
                pre[i][j] = pre[i - 1][j] + (c == 'G' ? 0 : 1);
            } else {
                pre[i][j] = pre[i - 1][j] + 300000;
                // 写一个永远取不到的数字，这样在左端点更新的时候就能跳过这一行，因为紫名是无敌的，不能改 
            }
        }
    } 
    for (int u = 1; u <= n; u++) {
        for (int d = u; d <= n; d++) {
            // 枚举上下界，总和为0 
            int l = 1, r = 0, cnt = 0;
            while (r < m) {
                do {
                    r++;  // r端点必须要往前，不然就没有继续循环的意义了 
                    cnt += pre[d][r] - pre[u - 1][r];  // 总和加上右边的和 
                } while (r < m && cnt + pre[d][r + 1] - pre[u - 1][r + 1] <= k);  // 如果cnt在加下一列的情况下还是合法的，那么继续走 
                while (cnt > k) {  // 左端点更新到cnt合法 
                    cnt -= pre[d][l] - pre[u - 1][l];
                    l++; 
                }
                if (ans < (d - u + 1) * (r - l + 1)) {  // 更新答案 
                    ans = (d - u + 1) * (r - l + 1);
                    U = u;
                    D = d;
                    L = l;
                    R = r;
                    C = c;
                }
            }
        }
    }
}

void updateP() {  // 尝试填充紫色
	// 前缀和，只有紫色才会+1 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pre[i][j] = pre[i - 1][j];
            if (a[i][j] == 'P') {
                pre[i][j]++;
            }
        }
    }
    for (int u = 1; u <= n; u++) {
        for (int d = u; d <= n; d++) {
            int l, r = 0;
            while (r < m) {
            	// 更新右端点 
            	// 第一步：
				// GGGGGPPPPPPPGGG
				//     ^ 
	            while (r < m && pre[d][r + 1] - pre[u - 1][r + 1] != (d - u + 1)) r++;
	            // 第二步：
				// GGGGGPPPPPPPGGG
				//            ^
	            while (r < m && pre[d][r + 1] - pre[u - 1][r + 1] == (d - u + 1)) r++;
	            // 如果没有找到就break 
	            if (pre[d][r] - pre[u - 1][r] != (d - u + 1)) break;
	            // 左端点以r为起点往左边跑 
	            l = r;
	            while (pre[d][l - 1] - pre[u - 1][l - 1] == (d - u + 1)) l--;
				// 更新左端点
	            // GGGGGPPPPPPPGGG
	            //      ^     ^
	            //      l     r
				// 注意：这里的l最多跑遍整个m，所以双指针的时间复杂度仍然是O(m) 
	            if (ans < (d - u + 1) * (r - l + 1)) {  // 更新答案 
	                ans = (d - u + 1) * (r - l + 1);
	                U = u;
	                D = d;
	                L = l;
	                R = r;
	                C = 'P';
	            }
        	}
		}
    }
}

int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    // 分别尝试三种颜色 
    update('G');
    update('B');
    updateP();
    cout << ans << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (U <= i && i <= D && L <= j && j <= R) {
            	// 如果在选定矩形内则输出对应颜色 
                cout << C;
            } else {
            	// 否则输出自身颜色 
                cout << a[i][j];
            }
        }
        cout << endl;
    }
    return 0;
}
```

## 时间复杂度

枚举上下界为 $O(n^2)$，双指针为 $O(m)$，维护和为 $O(1)$，所以总体时间复杂度为 $O(mn^2)$，可以通过本题。

结尾感谢 Hack3rD，CoCo_Candy，haixiao_as 在 [这个帖子](https://www.luogu.com.cn/discuss/473727) 中为我指出了错误，这篇题解离开他们我可能永远都查不清楚我的 bug，这篇题解也将不复存在。

感谢你看到最后。

Upd 2022.8.10：修正了关于双指针的时间复杂度描述。

---

## 作者：chenzefan (赞：3)

看到题目，先想到用暴力解决，要枚举矩阵四个顶点，时间复杂度是 $O(n^2m^2)$ ，但数据范围是 $1≤n,m≤500$ ，所以会超时。~~（不愧是绿题）~~

考虑优化，容易想到用**二维前缀和**进行统计，然后用**双指针算法**求解。分成三类来判断，分别是棕名、灰名和紫名。每次，先枚举左上角与右下角的纵坐标，然后用双指针算法来确定左上角与右下角的横坐标，通过一个 check 函数来判断这个矩阵能不能满足要求（用预处理的二维前缀和来判断），也就是能用最多k次把矩阵内字符改成相同的一个字符（不能改紫色，也不能改成紫色！），如果能，就更新答案字符以及矩阵范围，方便后续进行输出。这样做的时间复杂度是 $O(n^2m)$ ，可以过！

**注意**：考虑棕名和灰名时，矩阵内不能有紫名，因为修改不了紫名。而且要考虑矩阵内全是紫名。本题要开 long long 哦！

代码亮相（内含注释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long //数据较大，要开 long long 
const int N=505;//数据范围
int n,m,k;
char a[N][N];//输入与输出的数组 
int sum_B[N][N],sum_G[N][N],sum_P[N][N];//二维前缀和数组 
int ans1,ans2,ans3,ans4,maxx;
char ans_char; 
bool check(int i,int l,int j,int r,char c){
	int S,SP;
	if(c=='B') S=sum_B[j][r]-sum_B[j][l-1]-sum_B[i-1][r]+sum_B[i-1][l-1];//考虑棕名
	if(c=='G') S=sum_G[j][r]-sum_G[j][l-1]-sum_G[i-1][r]+sum_G[i-1][l-1];//考虑灰名
	SP=sum_P[j][r]-sum_P[j][l-1]-sum_P[i-1][r]+sum_P[i-1][l-1];//紫名每次都要考虑 
	if(SP!=0&&c!='P') return 0;//矩阵内出现紫名，并且此时不考虑紫名，那么返回0
	if(c=='P'&&(j-i+1)*(r-l+1)==SP) return 1;
	if((j-i+1)*(r-l+1)-S<=k&&c!='P') return 1;//如果最多用k次能做到要求，那么返回1
	return 0;//做不到要求，返回0 
}
signed main(){//因为用 int 代替了 long long ，所以这里改成 signed 
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			sum_B[i][j]=sum_B[i-1][j]+sum_B[i][j-1]-sum_B[i-1][j-1]+(a[i][j]=='B');//计算从(1,1)到(i,j)这个矩阵中有多少个棕名 
			sum_G[i][j]=sum_G[i-1][j]+sum_G[i][j-1]-sum_G[i-1][j-1]+(a[i][j]=='G');//计算从(1,1)到(i,j)这个矩阵中有多少个灰名 
			sum_P[i][j]=sum_P[i-1][j]+sum_P[i][j-1]-sum_P[i-1][j-1]+(a[i][j]=='P');//计算从(1,1)到(i,j)这个矩阵中有多少个紫名 
		}
	//考虑棕色
	for(int i=1;i<=n;i++) 
		for(int j=i;j<=n;j++){
			int l=1,r=0;
			while(l<=m&&r<=m){
				while(r<m&&check(i,l,j,r+1,'B')) r++; 
				if((r-l+1)*(j-i+1)>maxx){
					maxx=(r-l+1)*(j-i+1);//更新矩阵大小 
					ans1=i,ans2=l,ans3=j,ans4=r,ans_char='B';//更新矩阵范围以及颜色，方便输出  
				}
				l++; 
			}
		} 
	//考虑灰色 
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++){
			int l=1,r=0;
			while(l<=m&&r<=m){
				while(r<m&&check(i,l,j,r+1,'G')) r++;
				if((r-l+1)*(j-i+1)>maxx){
					maxx=(r-l+1)*(j-i+1);//更新矩阵大小 
					ans1=i,ans2=l,ans3=j,ans4=r,ans_char='G';//更新矩阵范围以及颜色，方便输出 
				}
				l++;
			}
		}
	//考虑紫色
	for(int i=1;i<=n;i++) 
		for(int j=i;j<=n;j++){
			int l=1,r=0;
			while(l<=m&&r<=m){
				while(r<m&&check(i,l,j,r+1,'P')) r++;
				if((r-l+1)*(j-i+1)>maxx){
					maxx=(r-l+1)*(j-i+1);//更新矩阵大小 
					ans1=i,ans2=l,ans3=j,ans4=r,ans_char='P';//更新矩阵范围以及颜色，方便输出 
				}
				l++;
			}
		}
	for(int i=ans1;i<=ans3;i++)
		for(int j=ans2;j<=ans4;j++)
			a[i][j]=ans_char;//把矩阵内元素进行修改，其余不变，方便输出 
	printf("%lld\n",maxx);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cout<<a[i][j];
		cout<<endl;
	}//输出要求 
	return 0;//完美的结束！！ 
}

```
本蒟蒻第一次写题解，求管理大大给过。

点个小红心再走吧！

---

## 作者：Ybw0731 (赞：2)

# 前言
本人只是在完成 XSZX 的作业时刷到此题（我是 XXS）。
# 思路
## STEP1
看一眼数据，$n,m\le500$，$O(n^2m^2)$ 的暴力做法直接死掉（超时），于是翻了翻题解区，想到了思路，就是先暴力左上角，然后右下角使用双指针（本人双指针贼差），每次去判断一下是否可行，就行了。

## STEP2
那么重点来了，判断怎么判呢？


### STEP 2.1
首先，紫名大佬是至高无上的，不能侵犯，否则这个矩阵~~该罚~~。然后，看会不会滥用权力，否则将会臭名昭著，棕名与灰名判法一样。

```cpp
bool check1(int x,int y,int xx,int yy){
	int B=sumb[xx][yy]-sumb[xx][y-1]-sumb[x-1][yy]+sumb[x-1][y-1];
	int P=sump[xx][yy]-sump[xx][y-1]-sump[x-1][yy]+sump[x-1][y-1];
	if(P)return 0;
	if((xx-x+1)*(yy-y+1)-B<=k)return 1;
	return 0;
}
```


### STEP 2.2
万一这个矩阵全是紫名呢？


判一下不就好了。

```cpp
bool check2(int x,int y,int xx,int yy){
	int G=sumg[xx][yy]-sumg[xx][y-1]-sumg[x-1][yy]+sumg[x-1][y-1];
	int P=sump[xx][yy]-sump[xx][y-1]-sump[x-1][yy]+sump[x-1][y-1];
	if(P)return 0;
	if((xx-x+1)*(yy-y+1)-G<=k)return 1;
	return 0;
}
```

## STEP3
如何用 $O(1)$ 来算数量呢？


用一下二维前缀和就好了。

```cpp
for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];
			sumb[i][j]=sumb[i-1][j]+sumb[i][j-1]-sumb[i-1][j-1]+(mp[i][j]=='B');
			sumg[i][j]=sumg[i-1][j]+sumg[i][j-1]-sumg[i-1][j-1]+(mp[i][j]=='G');
			sump[i][j]=sump[i-1][j]+sump[i][j-1]-sump[i-1][j-1]+(mp[i][j]=='P');
		}
	}
```

## AC代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e2+5;
const int INF=0x3f3f3f3f;
const double EPS=10e-6;
int n,m,ans1,ans2,ans3,ans4,k,mx;
int sumb[N][N],sump[N][N],sumg[N][N];
char mp[N][N],ansc;
bool check1(int x,int y,int xx,int yy){
	int B=sumb[xx][yy]-sumb[xx][y-1]-sumb[x-1][yy]+sumb[x-1][y-1];
	int P=sump[xx][yy]-sump[xx][y-1]-sump[x-1][yy]+sump[x-1][y-1];
	if(P)return 0;
	if((xx-x+1)*(yy-y+1)-B<=k)return 1;
	return 0;
}//判棕名
bool check2(int x,int y,int xx,int yy){
	int G=sumg[xx][yy]-sumg[xx][y-1]-sumg[x-1][yy]+sumg[x-1][y-1];
	int P=sump[xx][yy]-sump[xx][y-1]-sump[x-1][yy]+sump[x-1][y-1];
	if(P)return 0;
	if((xx-x+1)*(yy-y+1)-G<=k)return 1;
	return 0;
}//判灰名
bool check3(int x,int y,int xx,int yy){
	int P=sump[xx][yy]-sump[xx][y-1]-sump[x-1][yy]+sump[x-1][y-1];
	if(P==(xx-x+1)*(yy-y+1))return 1;
	return 0;
}//判紫名
void solve(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];
			sumb[i][j]=sumb[i-1][j]+sumb[i][j-1]-sumb[i-1][j-1]+(mp[i][j]=='B');
			sumg[i][j]=sumg[i-1][j]+sumg[i][j-1]-sumg[i-1][j-1]+(mp[i][j]=='G');
			sump[i][j]=sump[i-1][j]+sump[i][j-1]-sump[i-1][j-1]+(mp[i][j]=='P');
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			int l=1,r=0;
			while(l<=n&&r<=m){//two-pointer
				while(r<m&&check1(i,l,j,r+1))r++;
				if(mx<(r-l+1)*(j-i+1)){
					mx=(r-l+1)*(j-i+1);
					ans1=i,ans2=l,ans3=j,ans4=r,ansc='B';
				}
				l++;
			} 
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			int l=1,r=0;
			while(l<=n&&r<=m){
				while(r<m&&check2(i,l,j,r+1))r++;
				if(mx<(r-l+1)*(j-i+1)){
					mx=(r-l+1)*(j-i+1);
					ans1=i,ans2=l,ans3=j,ans4=r,ansc='G';
				}
				l++;
			} 
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			int l=1,r=0;
			while(l<=n&&r<=m){
				while(r<m&&check3(i,l,j,r+1))r++;
				if(mx<(r-l+1)*(j-i+1)){
					mx=(r-l+1)*(j-i+1);
					ans1=i,ans2=l,ans3=j,ans4=r,ansc='P';
				}
				l++;
			} 
		}
	}
	for(int i=ans1;i<=ans3;i++){
		for(int j=ans2;j<=ans4;j++){
			mp[i][j]=ansc;
		}
	}
	cout<<mx<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cout<<mp[i][j];
		}
		cout<<endl;
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T=1;
//	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：Epoch_L (赞：2)

[题目链接](https://www.luogu.com.cn/problem/P8472)
## Problem
给定一个矩阵，最多进行 $k$ 次操作，每次可以把 `B` 改成 `G`，`G` 改成 `B`，`P` 不能改，问最后能得到的最大的颜色相同的子矩阵。

## Solution
由于 $n,m\le500$，所以应该是一个 $O(n^3)$ 的做法。

我们枚举一个矩阵的最上行 $x$，最下行 $y$，最左列和最右列的指针分别为 $L=1,R=1$，这是就确定了一个矩阵，由于具有单调性，所以我们可以每次判断如果能够在 $k$ 次操作内将其改成相同矩阵（前缀和预处理），就可以考虑将矩阵加大即 $R++$，否则 $L++$。注意如果当前只有一列，且不合法，并不代表后面也不合法，需要 $L,R$ 都向后推一列。

注意对于每一个 $x,y$ 都有最大的 $L,R$，所以开数组存下这个 $L,R$，然后你需要记录最大的矩阵面积。

有个坑点，要注意紫名矩阵也算，方法一样。

## Code
细节较多，码风较丑，仅供参考。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
void read(int &x)
{
	char ch=getchar();
	int r=0,w=1;
	while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch))r=(r<<3)+(r<<1)+(ch^48),ch=getchar();
	x=r*w;
}
const int N=507;
char c[N][N];
int sumb[N][N],sumg[N][N],l[N][N],r[N][N],ans[N][N],anss[N][N],ls[N][N],rs[N][N],ss[N][N];
bool ok=0;
int queryb(int a,int b,int c,int d)
{
	return sumb[c][d]-sumb[c][b-1]-sumb[a-1][d]+sumb[a-1][b-1];
}
int queryg(int a,int b,int c,int d)
{
	return sumg[c][d]-sumg[c][b-1]-sumg[a-1][d]+sumg[a-1][b-1];
}
main()
{
	int n,m,k;
	read(n);read(m);read(k);
	for(int i=1;i<=n;i++)
		scanf("%s",c[i]+1);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		sumb[i][j]=sumb[i-1][j]+sumb[i][j-1]-sumb[i-1][j-1]+(c[i][j]=='B');
		sumg[i][j]=sumg[i-1][j]+sumg[i][j-1]-sumg[i-1][j-1]+(c[i][j]=='G');
	//	cout<<sumb[i][j]<<" "<<sumg[i][j]<<endl;
	}
	for(int i=1;i<=n;i++)
	for(int j=i;j<=n;j++)
	{
		int L=1,R=1;
		while(L<=R&&R<=m)
		{
//			cout<<L<<" "<<R<<endl;
			int s=ans[i][j];
			if((R-L+1)*(j-i+1)-queryb(i,L,j,R)-queryg(i,L,j,R)!=0)
			{
				L++;
				if(L>R&&R<m)R++;
				continue;
			}
			if(min(queryb(i,L,j,R),queryg(i,L,j,R))<=k)
			{
				ans[i][j]=max(ans[i][j],(R-L+1)*(j-i+1));
				if(ans[i][j]>s)l[i][j]=L,r[i][j]=R;R++;
//				printf("ans[%d][%d]=%d,l=%d,r=%d\n",i,j,ans[i][j],l[i][j],r[i][j]);
			}
			else L++;
			if(L>R&&R<m)R++;
		}
	}
	for(int i=1;i<=n;i++)
	for(int j=i;j<=n;j++)
	{
		int L=1,R=1;
		while(L<=R&&R<=m)
		{
			int s=anss[i][j];//cout<<L<<" "<<R<<" "<<(R-L+1)*(j-i+1)-queryb(i,L,j,R)-queryg(i,L,j,R)<<endl;
			if(queryb(i,L,j,R)+queryg(i,L,j,R)==0)
			{
				anss[i][j]=max(anss[i][j],(R-L+1)*(j-i+1));
				if(anss[i][j]>s)ls[i][j]=L,rs[i][j]=R;
				R++;
			}
			else 
			{
				L++;
				if(L>R&&R<m)R++;
				continue;
			}if(L>R&&R<m)R++;
		}
	}
	int sb=0,ansi,ansj;
	for(int i=1;i<=n;i++)
	for(int j=i;j<=n;j++)
	{
		if(sb<ans[i][j])
		{
			ok=0;
			sb=ans[i][j];
			ansi=i,ansj=j;
		}
		
		if(sb<anss[i][j])
		{
			sb=anss[i][j];
			ok=1;
		}
	}
	cout<<sb<<endl;
	//cout<<ansi<<" "<<ansj<<endl;
	if(ok)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(i>=ansi&&i<=ansj&&j>=ls[ansi][ansj]&&j<=rs[ansi][ansj])
					cout<<"P";
				else cout<<c[i][j];
			}
			cout<<endl;
		}
		return 0;
	}
	if(queryb(ansi,l[ansi][ansj],ansj,r[ansi][ansj])<=k)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(i>=ansi&&i<=ansj&&j>=l[ansi][ansj]&&j<=r[ansi][ansj])
					cout<<"G";
				else cout<<c[i][j];
			}
			cout<<endl;
		}
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(i>=ansi&&i<=ansj&&j>=l[ansi][ansj]&&j<=r[ansi][ansj])
					cout<<"B";
				else cout<<c[i][j];
			}
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：yohoofu2011 (赞：2)

## 思路分析

首先，我们需要用一个二位前缀和统计每个颜色名字的人数，然后枚举子矩阵，一共有两种方法：

1. 枚举子矩阵的右下角，再暴力枚举左上角，时间复杂度为 $O(n^4)$，很显然是过不了的；

2. 可以发现，双指针可以快速找到最优情况，所以来优化一下，先枚举一个长条形的矩阵，如果变的次数符合要求，那么拓宽矩阵，否则减小矩阵的长度，找最优解即可，时间复杂度为 $O(n^3)$。

要注意一下，要特判一下，如果全为紫名也是可以的，注意，紫名不可被修改，也不能把其他名字改成紫名。
## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, k, a[507][507], sum[507][507][3], ans, ansx, ansy, ansxx, ansyy, ys;
bool tf;
char c;
void cz(int x, int y) {
	//特判
	if (x * y <= ans) return;
	if (sum[x][y][0] == x * y) {
		if (ans < x * y) ans = x * y, ansx = x, ansy = y, ansxx = 1, ansyy = 1, ys = 0;
		return;
	}
	if (sum[x][y][0] == 0 && min(sum[x][y][1], sum[x][y][2]) <= k) {
		if (ans < x * y) ans = x * y, ansx = x, ansy = y, ansxx = 1, ansyy = 1, ys = (sum[x][y][1] > sum[x][y][2] ? 1 : 2);
		return;
	}
	//找最优的左上角
	for (int i = 1, j = y; i <= x && j >= 1;) {
		if (sum[x][y][0] - sum[i - 1][y][0] - sum[x][j - 1][0] + sum[i - 1][j - 1][0] == (x - i + 1) * (y - j + 1)) {
			//判断是否更优，并记录子矩阵的位置和颜色
			if (ans < (x - i + 1) * (y - j + 1)) ans = (x - i + 1) * (y - j + 1), ansx = x, ansy = y, ansxx = i, ansyy = j, ys = 0;
			//拓宽子矩阵
			j--;
		} else if (sum[x][y][0] - sum[i - 1][y][0] - sum[x][j - 1][0] + sum[i - 1][j - 1][0] == 0 && min(sum[x][y][1] - sum[i - 1][y][1] - sum[x][j - 1][1] + sum[i - 1][j - 1][1], sum[x][y][2] - sum[i - 1][y][2] - sum[x][j - 1][2] + sum[i - 1][j - 1][2]) <= k) {
			if (ans < (x - i + 1) * (y - j + 1)) ans = (x - i + 1) * (y - j + 1), ansx = x, ansy = y, ansxx = i, ansyy = j, ys = (sum[x][y][1] - sum[i - 1][y][1] - sum[x][j - 1][1] + sum[i - 1][j - 1][1] > sum[x][y][2] - sum[i - 1][y][2] - sum[x][j - 1][2] + sum[i - 1][j - 1][2] ? 1 : 2);
			//同上
			j--;
		} else{
			//减小子矩阵的长度
			i++;
		}
	}
	return;
}
int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> c;
			//统计名字
			if (c == 'P') a[i][j] = 0, sum[i][j][0] = sum[i - 1][j][0] + sum[i][j - 1][0] - sum[i - 1][j - 1][0] + 1, sum[i][j][1] = sum[i - 1][j][1] + sum[i][j - 1][1] - sum[i - 1][j - 1][1], sum[i][j][2] = sum[i - 1][j][2] + sum[i][j - 1][2] - sum[i - 1][j - 1][2];
			else if (c == 'B') a[i][j] = 1, sum[i][j][0] = sum[i - 1][j][0] + sum[i][j - 1][0] - sum[i - 1][j - 1][0], sum[i][j][1] = sum[i - 1][j][1] + sum[i][j - 1][1] - sum[i - 1][j - 1][1] + 1, sum[i][j][2] = sum[i - 1][j][2] + sum[i][j - 1][2] - sum[i - 1][j - 1][2];
			else a[i][j] = 2, sum[i][j][0] = sum[i - 1][j][0] + sum[i][j - 1][0] - sum[i - 1][j - 1][0], sum[i][j][1] = sum[i - 1][j][1] + sum[i][j - 1][1] - sum[i - 1][j - 1][1], sum[i][j][2] = sum[i - 1][j][2] + sum[i][j - 1][2] - sum[i - 1][j - 1][2] + 1;
		}
	}
	//枚举子矩阵的右下角
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			//如果以 (1,1) 为左上角都没 ans 大时直接跳过
			if (i * j <= ans) continue;
			cz(i, j);
		}
	}
	//输出
	cout << ans << "\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i >= ansxx && i <= ansx && j >= ansyy && j <= ansy) printf("%c", (ys == 0 ? 'P' : ys == 1 ? 'B' : 'G'));
			else printf("%c", (a[i][j] == 0 ? 'P' : a[i][j] == 1 ? 'B' : 'G'));
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：Kun_is_Me (赞：1)

### 题意分析。

给定一个 $n\times m$ 的、只包含 $B,G,P$ 三种字符的矩阵以及 $k$。你可以操作最多 $k$ 次，每一次可以将 $G$ 变成 $B$，或将 $B$ 变成 $G$，求最大的颜色相同的子矩阵的大小。

### 题目解法。

**主要知识点：二维前缀和。**

我们可以预处理三种颜色的二维前缀和，方便后续计算。

首先考虑暴力：枚举子矩阵的上下左右边界，用预处理的前缀和判断该子矩阵是否可以成为答案。

该方法时间复杂度：$O(n^2 m^2)$，在 $n,m\leq500$ 的情况下绝对过不了。

实际上我们只需要枚举子矩阵的上下两行（或者左右两列）即可。其实子矩阵的右边界是随着左边界的递增而递增的，我们就可以用双指针来处理子矩阵左右边界，这样时间复杂度就降到了 $O(nm^2)$。

需要特别注意，我们不能动紫色。所以：

1. 用前缀和判断是否可以将子矩阵变为灰色或棕色时，该子矩阵内不能有任何紫色。
2. 判断一个子矩阵是否可以全为紫色，只有该子矩阵原本就都是紫色时才可行。

最后，十年 OI 一场空，不开 ____ ____ 见祖宗。

### AC 代码。

不懂的自行看注释。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k;
char a[514][514];
int sb[514][514],sg[514][514],sp[514][514];//三种颜色的前缀和数组 
int ans1,ans2,ans3,ans4,mx;
char a_c; 
bool check(int i,int l,int j,int r,char c){
	int s,ss;
	if(c=='B') s=sb[j][r]-sb[j][l-1]-sb[i-1][r]+sb[i-1][l-1];
	if(c=='G') s=sg[j][r]-sg[j][l-1]-sg[i-1][r]+sg[i-1][l-1];
	ss=sp[j][r]-sp[j][l-1]-sp[i-1][r]+sp[i-1][l-1];
	if(ss!=0&&c!='P') return 0;
	if(c=='P'&&(j-i+1)*(r-l+1)==ss) return 1;
	if((j-i+1)*(r-l+1)-s<=k&&c!='P') return 1;
	return 0;
}
signed main()
{
	ios::sync_with_stdio(false);//以下两行装杯专用，可以加速 cin 和 cout 的时间，不会的就老实用 scanf 和 printf 吧 
	cin.tie(0),cout.tie(0);//(其实这道题的输入量用未优化的 cin 和 cout 足够了) 
	cin>>n>>m>>k;//(cin 和 cout 就是好用，省去了一大堆格式符)
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			sb[i][j]=sb[i-1][j]+sb[i][j-1]-sb[i-1][j-1]+(a[i][j]=='B');
			sg[i][j]=sg[i-1][j]+sg[i][j-1]-sg[i-1][j-1]+(a[i][j]=='G');
			sp[i][j]=sp[i-1][j]+sp[i][j-1]-sp[i-1][j-1]+(a[i][j]=='P');//以上三行为预处理 
		}
	for(int i=1;i<=n;i++) //考虑棕色，以下同理 
		for(int j=i;j<=n;j++)
		{
			int l=1,r=0;
			while(l<=m&&r<=m)
			{
				while(r<m&&check(i,l,j,r+1,'B')) r++; 
				if((r-l+1)*(j-i+1)>mx)
				{
					mx=(r-l+1)*(j-i+1);
					ans1=i,ans2=l,ans3=j,ans4=r,a_c='B';
				}
				l++; 
			}
		} 
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			int l=1,r=0;
			while(l<=m&&r<=m)
			{
				while(r<m&&check(i,l,j,r+1,'G')) r++;
				if((r-l+1)*(j-i+1)>mx)
				{
					mx=(r-l+1)*(j-i+1);
					ans1=i,ans2=l,ans3=j,ans4=r,a_c='G';
				}
				l++;
			}
		}
	for(int i=1;i<=n;i++) 
		for(int j=i;j<=n;j++)
		{
			int l=1,r=0;
			while(l<=m&&r<=m)
			{
				while(r<m&&check(i,l,j,r+1,'P')) r++;
				if((r-l+1)*(j-i+1)>mx)
				{
					mx=(r-l+1)*(j-i+1);
					ans1=i,ans2=l,ans3=j,ans4=r,a_c='P';
				}
				l++;
			}
		}
	for(int i=ans1;i<=ans3;i++)for(int j=ans2;j<=ans4;j++)a[i][j]=a_c;//修改矩阵，方便输出 
	cout<<mx<<endl;//输出最大同色子矩阵的大小 
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++) cout<<a[i][j];
		cout<<endl;
	}//依题目要求，输出符合要求的矩阵 
	return 0;//华丽结束 
}
```


附上 [AC 记录](https://www.luogu.com.cn/record/201188264)。

今天的题解就到这里。

---

## 作者：fengyaun (赞：1)

### [P8472 Aya Round 1 G 咕噜论坛（post）](https://www.luogu.com.cn/problem/P8472)

#### 思路

先考虑暴力，发现复杂度为 $O(n^4)$ 在 $n \leq 500$ 的情况下会超时。

然后考虑优化，不难发现，可以先固定左右两个两个端点再使用双指针扫一个区间出来，再使用前缀和将 $O(n^2)$ 的查找优化为 $O(1)$。

可以通过前缀和维护 B 和 G 和 P 各自的个数，若 P 个数为 $0$ 则取 B 的个数和 G 的个数的最小值，否则若 P 填满区间则为 P，否则无解。

实现上要注意不要写 `for(; l <= r; )` 而是 `r = max(l, r)`。

#### 实现

```C++
#include<bits/stdc++.h>
using namespace std;

const int N = 5e2 + 10;

struct node
{
    int w, i, j, l, r, t;
};

int n, m, k;

node ans;

int pre[5][N][N]; // 1 : B的个数  2 : G的个数  3 : P的个数 

int maps[N][N];

node check(int i, int j, int l, int r)
{
    int res = INT_MAX;
    int t = -1;
    int A = (j - i + 1) * (r - l + 1);
    int B = A - (pre[1][j][r] - pre[1][i - 1][r] - pre[1][j][l - 1] + pre[1][i - 1][l - 1]);
    int G = A - (pre[2][j][r] - pre[2][i - 1][r] - pre[2][j][l - 1] + pre[2][i - 1][l - 1]);
    int P = pre[3][j][r] - pre[3][i - 1][r] - pre[3][j][l - 1] + pre[3][i - 1][l - 1];
    if (P == 0)
    {
        if (res > B)
        {
            res = B;
            t = 1;
        }
        if (res > G)
        {
            res = G;
            t = 2;
        }
    }
    else
    {
        if (P == A)
        {
            res = 0;
            t = 3;
        }
    }
    return {res, i, j, l, r, t};
}

int main()
{
    cin >> n >> m >> k;
    char cur;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> cur;
            maps[i][j] = (cur == 'B' ? 1 : (cur == 'G' ? 2 : 3));
            if (maps[i][j] == 1)
            {
                pre[1][i][j]++;
            }
            else if (maps[i][j] == 2)
            {
                pre[2][i][j]++;
            }
            else
            {
                pre[3][i][j]++;
            }
            pre[1][i][j] += pre[1][i][j - 1] + pre[1][i - 1][j] - pre[1][i - 1][j - 1];
            pre[2][i][j] += pre[2][i][j - 1] + pre[2][i - 1][j] - pre[2][i - 1][j - 1];
            pre[3][i][j] += pre[3][i][j - 1] + pre[3][i - 1][j] - pre[3][i - 1][j - 1];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            for (int l = 1, r = 0; l <= m; l++)
            {
                r = max(l, r);
                while(r + 1 <= m && check(i, j, l, r + 1).w <= k)
                {
                    r++;
                }
                node cur = check(i, j, l, r);
                if (cur.w <= k && ans.w < (j - i + 1) * (r - l + 1))
                {
                    ans = cur;
                    ans.w = (j - i + 1) * (r - l + 1);
                }
            }
        }
    }
    cout << ans.w << "\n";
    for (int i = ans.i; i <= ans.j; i++)
    {
        for (int j = ans.l; j <= ans.r; j++)
        {
            maps[i][j] = ans.t;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cout << (maps[i][j] == 1 ? 'B' : (maps[i][j] == 2 ? 'G' : 'P'));
        }
        cout << "\n";
    }
    return 0;
}
```

---


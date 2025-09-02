# [USACO09NOV] Lights G

## 题目背景

[English Edition](/paste/410oq6t5)

## 题目描述

给出一张 $n$ 个点 $m$ 条边的无向图，每个点的初始状态都为 $0$。  

你可以操作任意一个点，操作结束后该点以及所有与该点相邻的点的状态都会改变，由 $0$ 变成 $1$ 或由 $1$ 变成 $0$。  

你需要求出最少的操作次数，使得在所有操作完成之后所有 $n$ 个点的状态都是 $1$。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le35,1\le m\le595, 1\le a,b\le n$。保证没有重边和自环。

## 样例 #1

### 输入

```
5 6 
1 2 
1 3 
4 2 
3 4 
2 5 
5 3 
```

### 输出

```
3 
```

# 题解

## 作者：YoungLove (赞：51)

先挂个博客[Youngsc](https://youngscc.github.io/)欢迎来踩

高斯消元，对于一个灯我只有按或者不按两种状态，如果按也只会按一次，最终我们希望所有的灯的状态都为$1$，那么对于每一个灯$i$的状态就是与它相连的每一个灯包括它自己按或者不按的状态$d[i]$的异或和$$(a[1][i]*d[1])xor(a[2][i]*d[2])\cdots(a[n][i]*d[n])=1$$待求的元素就是$d[]$，就可以得到一个$n\*(n+1)$方程组，然后用高斯消元之后会得到一个上三角矩阵，但你可能会产生一些自由元，此时我们采用DFS的方法，消完元后的矩阵相当于重新定义了两个灯之间的关系以及每个灯要到达的状态，由于该矩阵是一个上三角矩阵，意味着此时你要做的就是让所有的灯都符合等号右边的状态，由于新的关系可以保证每一个灯都只会被他后边的灯所影响(注意在消元之后两个灯之间的新关系不一定是双向的)，因此我们从后往前搜，如果这个不是自由元那么我们就可以根据后边灯的状态来判断它按或者不按，如是自由元的话，我们就要枚举一下按或者不按，再分别搜索。

```cpp
# include <bits/stdc++.h>
# define R register
# define db double
# define mi 1e-8

using namespace std;

int n,m,x,y,ans=10000,l[110];
int a[110][110];

template <typename T> inline void in(R T& a){
    R char c=getchar(); R T x=0,f=1;
    while(!isdigit(c)) {if(c == '-') f=-1; c=getchar();}
    while(isdigit(c)) x=(x<<1)+(x<<3)+c-'0',c=getchar();
    a=x*f;
}

template <typename T> inline T ab(R T& a){return a<0? -a:a;}

inline bool gauss(){//高斯消元
    R bool flagg=1;
    for(R int i=1; i<=n; ++i)
    {
        R int k=i;
        while(k<=n&&!a[k][i]) k++;
        if(k>n) {flagg=0; continue;}
        swap(a[i],a[k]);
        for(R int j=1; j<=n; ++j)
        {
            if(i==j||!a[j][i]) continue;
            for(R int k=i+1; k<=n+1; ++k) a[j][k]^=a[i][k];
            a[j][i] = 0;
        }
    }
    return flagg;
}

inline void dfs(R int x,R int num){
    // printf("%d ",x);
    if(num>=ans) return;//剪枝
    if(x == 0){ans = num; return;}
    if(a[x][x])//不是自由元
    {
        R bool v=a[x][n+1];
        for(R int i=x+1; i<=n; ++i) if(a[x][i]) v^=l[i];
        dfs(x-1,num+v);
    }
    else{
        dfs(x-1,num);
        l[x]=1;
        dfs(x-1,num+1);
        l[x]=0;
    }
}

int main(){
    // freopen("data.in","r",stdin);
    // freopen("data.out","w",stdout);
    in(n),in(m);
    for(R int i=1; i<=n; ++i) a[i][i] = a[i][n+1] = 1;
    for(R int i=1; i<=m; ++i) in(x),in(y),a[x][y] = a[y][x] = 1;
    if(gauss()){
        R int ans = 0;
        for(R int i=1; i<=n; ++i) ans += a[i][n+1];
        printf("%d",ans);
    }
    else dfs(n,0),printf("%d\n",ans);
    return 0;
}

```

---

## 作者：AuCloud (赞：44)

# 奇奇怪怪的方法
不难理解，最优方案中每个灯最多被按一次

于是根据这个性质，我们不妨暴力枚举35个灯的全排列

每次从左向右扫，模拟按下开关，如果状态全变1则更新答案

显然这种$n^n$的做法不靠谱/kel

于是祭出大杀器——**随机化**

每次`random_shuffle`一下，暴力从左向右模拟，重复1000000次大概就可以稳定淦掉15个点

看脸，如果脸很白的话可能一次直接AC

~~不然可能要试很多次~~

分数取值范围$[82,100]$

![](https://s1.ax1x.com/2020/10/30/BtJXh6.png)

~~（下面省略好几页的提交记录）~~
### 一些小细节

读入完边之后，遍历一次图，将每个点影响到的点以二进制存下来

每次暴力模拟的时候在状态上异或就行，省去了每次枚举边的时间


### 简短的代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[400], con[400], head[400], nxt[8000], to[8000], tot;
int n, m;
bool used[40];
void add(int x, int y)
{
    nxt[++tot] = head[x];
    head[x] = tot;
    to[tot] = y;
}
int luangao()
{
    int now = 0;//状态，第i位即为i的状态（0关1开）
    for(int i = 1; i <= n; i++)
    {
        now ^= con[a[i]];
        if(now == (1ll << n) - 1) return i;
    }
    return 0x7ffffffffff;
}
signed main()
{
    ios::sync_with_stdio(false);
    srand(time(NULL));//你当然可以去试试玄学的种子
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        add(x, y);
        add(y, x);
    }
    for(int i = 1; i <= n; i++)
    {
        a[i] = i;
    }
    for(int x = 1; x <= n; x++)
    {
        con[x] |= (1ll << (x - 1));
        for(int i = head[x]; i; i = nxt[i])
        {
            int y = to[i];
            con[x] |= (1ll << (y - 1));
        }
    }
    int ans = 0x7ffffffffff;
    int qaq;
    if(n == 35) qaq = 1000000;
    else qaq = 1900000;
    for(int i = 1; i <= qaq; i++)//while(clock()<CLOCKS_PER_SEC*0.95)我的AC记录是卡时间这样写的
    {
        random_shuffle(a + 1, a + n + 1);
        int qwq = luangao();
        ans = min(ans, qwq);
    }
    cout << ans;
    return 0;
}

```

### P.S.

- 当然你可以下数据然后面向数据编程（if数据 cout数据）之类的，但是尽量不要

- 貌似可以暴力枚举随机数种子然后判断哪些在1s以内稳定通过#16#17#18，但是太麻烦了~~而且感觉也算面向数据编程了吧~~

- 制作不易~~脸太黑了~~，麻烦留个赞（

---

## 作者：zubizakeli (赞：23)

说实话我第一眼没看出这是个高斯消元题=-=

所以我用搜索写的qwq

首先，这道题有一个很明显的结论就是每个开关最多只会被操作一次。（因为操作2次等于没有操作）。

我们可以把每个灯看做2进制下的一位，把每个灯的值表示为他所连接到的灯的亦或和，那么开关灯操作就可以看做取亦或操作。

总方案数有2^35个，直接搜索显然会炸，所以我们用meet in the middle，复杂度O（sqrt（2^n））。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
#define LL long long
#define RI register int
using namespace std;
const int INF = 0x7ffffff ;
const int N = 40 ;

inline int read() {
	int k = 0 , f = 1 ; char c = getchar() ;
	for( ; !isdigit(c) ; c = getchar())
	  if(c == '-') f = -1 ;
	for( ; isdigit(c) ; c = getchar())
	  k = k*10 + c-'0' ;
	return k*f ;
}
int n, m, lv, ans = INF ; LL hh[N] ; LL tt ; LL p1[N], bin[N] ;
bool flag ;
map<LL,int>p ;  // 开不下2^35的数组，其实最多只有2^18个状态，所以用map是可以的

void dfs(int now,LL res,int used) {
	if(now > lv) {
		if(res == tt) {
			ans = min(ans,used) ;
		}
		else {
			if(!flag) {
				int t = p[res] ;
				if(!t || used < t) p[res] = used ;
			} else {
				if(p[tt^res]) ans = min(ans,p[tt^res]+used) ;
			}
		}
		return ;
	}
	dfs(now+1,res^p1[now],used+1) ; dfs(now+1,res,used) ; // 选与不选 
}

int main() {
	n = read(), m = read() ;
	bin[0] = 1 ;
	for(int i=1;i<=n;i++) bin[i] = bin[i-1]<<1 ;
	tt = bin[n] - 1 ;
	memset(hh,0,sizeof(hh)) ;
	LL x, y ;
	for(int i=1;i<=m;i++) {
		x = read(), y = read() ;
		hh[x] ^= bin[y-1], hh[y] ^= bin[x-1] ;
	}
	for(int i=1;i<=n;i++) hh[i] ^= bin[i-1] ;
	lv = n>>1 ;
	for(int i=1;i<=lv;i++) p1[i] = hh[i] ;
	dfs(1,0,0) ;  // 搜索前一半 
	for(int i=1;i<=n-lv;i++) p1[i] = hh[i+lv] ;
	lv = (n+1)>>1 ; flag = 1 ; // flag标记在搜索前半段还是后半段 
	dfs(1,0,0) ;  // 搜索后一半 
	printf("%d",ans) ;
	return 0 ;
}
```

其实我一开始没有用bin数组，直接用的（1<<x）这种形式，可是（1<<x）好像不能超过int，所以就参考了下黄学长的代码，发现黄学长用bin数组解决了这个问题。

---

## 作者：Demoe (赞：15)

### [题目传送门](https://www.luogu.com.cn/problem/P2962)

## 题意简述

- 对于一个 $n$ 个点 $m$ 条边的图，每次操作能使该点以及与该点直接相连的点状态改变，求问最少多少次操作可以让所有点状态改变。

## 构造

每个点**最多操作一次**，操作两次就没意义了。所以我们可对**高斯消元**进行修改，将其建立方程组，每个消元操作改为**异或**。

## 前置知识

高斯消元。

## 具体实现

对于每个点建立方程，即 $n$ 元 $1$ 次方程组。

若 $i$ 与 $j$ 有连边，我们分别将第 $i$ 个方程的第 $j$ 位系数和第 $j$ 个方程第 $i$ 位系数改为 $1$。

对于第 $i$ 个方程的第 $i$ 为系数一定是 $1$，不要忘了初始化。

然后我们消元时对于所有系数为1的进行**异或**消元。

若解出自由元，我们对它是 $0$ 或 $1$ 的情况都进行回代，取结果最小。

复杂度 $O(nm \times ?)$ 。

其中 $？$ 指自由元的个数。因为对于 $n=35$ 时，$m=595$，我们认为自由元的个数不多（~~数据小了~~），所以能过。

```cpp
/*
***
还要继续努力
成为一名烤咕学家哦
***
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll N=5005;
ll n,m,zy[N],a[N<<2][N],x[N],t,ans=0x3f3f3f3f;   //a记录方程 zy主元 
template <typename T> void rd(T &xx){
	ll fl=1;xx=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) xx=(xx<<3)+(xx<<1)+c-'0';
	xx*=fl;
}
void wr(ll xx){
	if(xx<0) xx=-xx,putchar('-');
	if(xx<10) putchar(xx+'0');
	if(xx>9) wr(xx/10),putchar(xx%10+'0');
}
ll gauss(){
	ll c=1,r=1,i,j,x;
	for(;c<=n;c++){  //遍历列 
		for(i=r;i<=n&&!a[i][c];i++) ;
		if(i>n) continue;   //c自由元 
		zy[r]=c;
		for(j=1;j<=n+1;j++) swap(a[i][j],a[r][j]);   //换到r行 
		for(x=r+1;x<=n;x++)   //消元 
			if(a[x][c])  //剔除不需要消元的 
				for(j=1;j<=n+1;j++) a[x][j]^=a[r][j];
		r++;
	}
	return r-1;
}
void ANS(ll c,ll r,ll tot){
//	cout<<c<<' '<<r<<' '<<tot<<endl;
	if(tot>ans) return ;    //剪枝 
	if(!c){    //边界 
		ans=min(ans,tot);
		return ;
	}
	if(c==zy[r]){  //主元 
		x[c]=a[r][n+1];  //回代 
		for(ll j=n;j>c;j--) x[c]^=x[j]&a[r][j];
//		cout<<c<<' '<<r<<' '<<tot<<' '<<x[c]<<endl;
		ANS(c-1,r-1,tot+x[c]);
	}
	else{x[c]=0;ANS(c-1,r,tot);x[c]=1;ANS(c-1,r,tot+1);}   //自由元 
}
int main(){
//	freopen("trouble12.in","r",stdin);
//	freopen("trouble12.out","w",stdout);
	rd(n);rd(m);
	for(ll i=1;i<=n;i++) a[i][i]=1;
	for(ll i=1,x,y;i<=m;i++){
		rd(x);rd(y);
		a[x][x]=a[x][y]=a[y][x]=a[y][y]=1;   //建方程组 
	}
	for(ll i=1;i<=n;i++) a[i][n+1]=1;
	ll r=gauss();
//	if(r!=n){cout<<-1<<endl;return 0;}
	ANS(n,r,0);
	wr(ans);puts("");
	return 0;
}
```



---

## 作者：litble (赞：15)

高斯消元+dfs

这题可以用高斯消元解异或方程的办法先搞出来，不过有一些情况下该x的系数消元后为0，那么这个x取的值就不固定了，这个时候就可以用dfs来判断最少关多少盏灯。

```cpp
#include<iostream>
#include<cstdio>
#include<climits>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int read(){
    int q=0;char ch=' ';
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')q=q*10+ch-'0',ch=getchar();
    return q;
}
int n,m,ans=INT_MAX;
int a[40][40],x[40];
void gauss(){//高斯消元
    int i,j,bj,k;
    for(k=1;k<=n;k++){
        bj=k;
        for(i=k+1;i<=n;i++)if(a[i][k]){bj=i;break;}
        if(bj!=k)for(j=1;j<=n+1;j++)swap(a[bj][j],a[k][j]);
        for(i=k+1;i<=n;i++)if(a[i][k]){
            for(j=1;j<=n+1;j++)a[i][j]^=a[k][j];
        }
    }
}
void dfs(int xx,int tot){
    if(tot>ans)return;//剪枝
    if(!xx){ans=min(ans,tot);return;}
    if(a[xx][xx]){//如果消元后系数为1，则用高斯消元的判断方法进行判断
        x[xx]=a[xx][n+1];
        for(int j=n;j>xx;j--)x[xx]^=x[j]&a[xx][j];
        if(x[xx])dfs(xx-1,tot+1);
        else dfs(xx-1,tot);
    }
    else {//如果为0就随便定一个
        x[xx]=0;dfs(xx-1,tot);
        x[xx]=1;dfs(xx-1,tot+1);
    }
}
int main()
{
    int i,j,xx,yy;
    n=read();m=read();
    for(i=1;i<=m;i++){xx=read();yy=read();a[xx][yy]=a[yy][xx]=1;}
    for(i=1;i<=n;i++)a[i][n+1]=1,a[i][i]=1;
    gauss();dfs(n,0);printf("%d",ans);
    return 0;
}
```

---

## 作者：闫飞天jyh (赞：10)

看其他的神仙都用的是高斯消元，   
身为蒟蒻的我用了一种~~简单~~~~的~~方法：  
**dfs+meet-in-middle（折半搜索）**  

如果不了解**meet-in-middle** 可移步CSDN      

 1. 如果直接暴力dfs，复杂度就是$O(2^n)$ 会T，所有要用**meet-in-middle**优化一下  
  复杂度就会变成
  $$
  \large O(n*2^{\frac{n}{2}})
 $$  
   
 2.再说一下**meet-in-middle**的思路:

 **meet-in-middle** 就是让我们先找一半的状态，也就是找出只使用编号为1 到   **mid**  的开关能够到达的状态，再找出只使用另一半开关能到达的状态。  
如果前半段和后半段开启的灯互补，将这两段合并起来就得到了一种将所有灯打开的 方案。  
 具体实现时，可以把前半段的状态以及达到每种状态的最少按开关次数存储在 map 里面，搜索后半段时，每搜出一种方案，就把它与互补的第一段方案合并来更新答案。运用折半搜索的时候若空间足够可用哈希储存。

---

## 作者：超级玛丽王子 (赞：8)

“折半”搜索好题。

请注意，这**不是二分！**

~~Stop learning useless algorithms, LEARN BINARY SEARCH~~

Meet in the middle 搜索方法，中文译作“折半搜索”，是一种用来优化暴力搜索的方法。其思想类似归并排序，将搜索空间分成两半，分别搜索后再按一定方式合并。

对于本题，可以发现每个点最多进行一次操作（否则就变回去了没有意义），考虑对每个点的操作状态压到一个 `long long` 里。之后暴力搜索所有状态的复杂度是 $O(2^n)$。使用 Meet int the middle 可以优化到 $O(2^{\frac n 2}n)$。具体方法是先暴搜 $1$ 到 $mid$ 的所有开关，再暴搜后面的两个部分。如果两个部分搜到的结果刚好能点亮所有的灯，就得到一个可行解。最后找到最优解即可。

实际实现比较复杂，需要用到 `map` 和位运算。具体见下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, ans = 0x7fffffff;
map<long long, int> f;
long long a[40];

int main(void) {
  ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
  cin >> n >> m;
  a[0] = 1;
  for (int i = 1; i < n; ++i) a[i] = a[i - 1] << 1; //预处理每个点都能影响到自己

  for (int i = 1; i <= m; ++i) {
    int u, v;
    cin >> u >> v;
    --u,--v; //与二进制位匹配
    a[u] |= (1ll << v),a[v] |= (1ll << u); //压位记录每个点操作影响到的点
  }

  for (int i = 0; i < (1 << (n >> 1)); ++i) {  //前半段
    long long t = 0;  //状态压缩
    int cnt = 0;
    for (int j = 0; j < (n >> 1); ++j) {
      if ((i >> j) & 1) {
        t ^= a[j];
        ++cnt;
      }
    }
    if (!f.count(t))  //前半段记录在 map 里
      f[t] = cnt;
    else
      f[t] = min(f[t], cnt);
  }

  for (int i = 0; i < (1 << (n - (n >> 1))); ++i) {  //后半段
    long long t = 0;
    int cnt = 0;
    for (int j = 0; j < (n - (n >> 1)); ++j) {
      if ((i >> j) & 1) {
        t ^= a[(n >> 1) + j];
        ++cnt;
      }
    }
    if (f.count((((long long)1 << n) - 1) ^ t))  //后半段与前半段匹配
      ans = min(ans, cnt + f[(((long long)1 << n) - 1) ^ t]);
  }
  cout << ans;
  return 0;
}
```

（代码修改自 OI-wiki 提供的参考代码）

---

## 作者：C20203030 (赞：4)

## 一、题目

不想多说，[传送门](https://www.luogu.org/problem/P2962)


## 二、解法
设为第$i$个点按开关$xi$次，我们把它当做未知数带入邻接矩阵的方程去解，显然有：

$(a[1][i]\times x1 \oplus a[2][i]\times x2 ……\oplus a[n][i]\times xn)=1$

由于开关的性质显然方程是$\%2$意义下的。

保证有解，所以只有两种情况。

1、方程只有一组解，这个解是唯一的，也是最小的。

2、方程有自由元，直接$dfs$每个自由元，枚举后取最小值即可。


```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int read()
{
	int x=0,flag=1;char c;
	while((c=getchar())<'0' || c>'9') if(c=='-') flag=-1;
	while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*flag;
}
int n,m,x,y,ans=0x3f3f3f3f,l[105];
int a[105][105];
bool gauss()
{
	bool flag=1;
	for(int i=1;i<=n;i++)
	{
		int r=i;
		while(r<=n && !a[r][i]) r++;
		if(r>n)
		{
			flag=0;
			continue;
		}
		swap(a[i],a[r]);
		for(int j=1;j<=n;j++)
		{
			if(i==j || !a[j][i]) continue;
			for(int k=i+1;k<=n+1;k++)
				a[j][k]^=a[i][k];
			a[j][i]=0;
		}
	}
	return flag;
}
void dfs(int x,int num)
{
	if(num>=ans) return ;
	if(x==0) {ans=num;return ;}
	if(a[x][x])
	{
		bool v=a[x][n+1];
		for(int i=x+1;i<=n;i++) if(a[x][i]) v^=l[i];
		dfs(x-1,num+v);
	}
	else
	{
		dfs(x-1,num);
		l[x]=1;
		dfs(x-1,num+1);
		l[x]=0;
	}
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++) a[i][i]=a[i][n+1]=1;
	for(int i=1;i<=m;i++) x=read(),y=read(),a[x][y]=a[y][x]=1;
	if(gauss())
	{
		ans=0;
		for(int i=1;i<=n;i++) ans+=a[i][n+1];
		printf("%d\n",ans);
	}
	else
	{
		dfs(n,0);
		printf("%d\n",ans);
	}
}
```



---

## 作者：crashed (赞：4)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P2962)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;根据题意，我们可以建立一个异或方程，然后用高斯消元解出这个方程。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于点$u$，设$l_u$为未知元（按的次数），则可列出如下方程：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle\left(\bigoplus_{e(u,v)\in E}l_v\right)\oplus l_u=1$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;显然，$\forall u\in V,l_u\in[0,1]$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;如果方程解出自由元，我们用搜索来确定最优答案。  
# 代码
```cxx
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 40, MAXM = 605;

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

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

int A[MAXN][MAXN], x[MAXN];
int N, M, res = 0x3f3f3f3f;

void Gauss()
{
	int indx;
	for( int i = 1 ; i <= N ; i ++ )
	{
		indx = -1;
		for( int j = i ; j <= N ; j ++ )
			if( A[j][i] )
			{
				indx = j;
				break;
			}
		if( indx == -1 ) continue;
		swap( A[indx], A[i] );
		for( int j = i + 1 ; j <= N ; j ++ )
			if( A[j][i] )
				for( int k = 1 ; k <= N + 1 ; k ++ )
					A[j][k] ^= A[i][k];
	}
}

void DFS( const int indx, const int num )
{
	if( ! indx )
	{
		res = MIN( res, num );
		return;
	}
	if( num >= res ) return;
	if( A[indx][indx] )
	{
		x[indx] = A[indx][N + 1];
		for( int j = N ; j > indx ; j -- ) x[indx] ^= x[j] & A[indx][j];
		DFS( indx - 1, num + x[indx] );
	}
	else
	{
		x[indx] = 0, DFS( indx - 1, num );
		x[indx] = 1, DFS( indx - 1, num + 1 );
	}
}

int main()
{
	int fr, to;
	read( N ), read( M );
	for( int i = 1 ; i <= M ; i ++ )
	{
		read( fr ), read( to );
		A[fr][to] = A[to][fr] = 1;
	}
	for( int i = 1 ; i <= N ; i ++ ) A[i][i] = A[i][N + 1] = 1;
	Gauss();
	DFS( N, 0 );
	write( res ), putchar( '\n' );
	return 0;
}
```

---

## 作者：arfa (赞：4)

> ### $Dfs+Meet\ in\ middle$

这道题一看,嗯,图论题。

然后我们就可以直接$Dfs$找状态(~~神转折~~)。

我们发现$N \leq 35$,也就是说直接$Dfs$是$O(2^{35})$,~~显然可以被卡过去~~。

我们就用**折半搜索**,就是说我们先搜索前面一半,后面一半再搜索。中间的时候用$hash,map$存储一下状态。这样子我们的时间复杂度就变得乐观:$O(2*2^{n/2})$。

搞死校园?其实并没有那么麻烦。如果你不嫌麻烦,可以打字符串来存储状态。$hash$用字符串$hash$。但是我们这里不用字符串,用一种更为玄学的方式,就是:

我们设$log_i$为$2^i$,如果点$u$到$v$有连边,我们就让$xx[x]$加上$log[v-1]$。然后把所有$u$和$v$枚举,就得到了**让一个灯开的所有贡献(包括其他灯的贡献)**。


> ### $Code$

```pascal
Uses math; //pascal树穴库

var
	reach:array[-1..100,-1..600] of longint; //去到哪里,这里不用链式前向星,麻烦
	statu:array[-1..100] of int64; //灯亮不亮的状态
	log,xx:array[-1..70] of int64; //上述
	hash:array[-1..1000008] of longint; //hash表
	l,r,n,m,i,j,mid,ans,right:longint; //某种变量

function arfa(num:int64):longint; //哈希
begin
        exit(((num mod 1000007)*(num mod 1000007)*99971) mod 1000007);
end;

procedure Dfs(mode,choose,x:longint); //mode是模式,因为是折半搜索,所以有两种模式。choose是选了多少(并不是多少亮着),x是到第几个。
var
	k:int64;
	kk,num,i:longint;
begin
	if x>right then //搜完了
	begin
		k:=0; num:=0;
		if mode=1 then
		begin
			for i:=1 to mid do //去到中间
				if statu[i]>0 then
				begin
                    k:=k xor xx[i]; //贡献
					inc(num); //选了
				end;
                inc(num); //细节
                kk:=arfa(k); //哈希存状态
			if hash[kk]=0 then
                hash[kk]:=num
            else
                hash[kk]:=min(hash[kk],num); //取min hash值
		end
		else
		begin
			for i:=mid+1 to n do //后半部分
				if statu[i]>0 then
				begin
                    k:=k xor xx[i];
					inc(num);
				end;
			kk:=arfa(log[n]-k-1); //配套的
            if hash[kk]>0 then //有答案
				ans:=min(ans,hash[kk]-1+num);
		end;
		exit;
	end;
    statu[x]:=0; //选和不选
	Dfs(mode,choose,x+1);
	statu[x]:=1;
	Dfs(mode,choose+1,x+1);
end;

procedure Ready;
begin
        read(n,m);
	for i:=1 to m do
	begin
		read(l,r);
		inc(reach[l,0]);
		reach[l,reach[l,0]]:=r;
		inc(reach[r,0]);
		reach[r,reach[r,0]]:=l;
	end;

	log[0]:=1;
	for i:=1 to n+1 do //预处理
		inc(log[i],log[i-1]*2);
	for i:=1 to n do //需要理解,是把x点亮的贡献
	begin
		xx[i]:=log[i-1];
		for j:=1 to reach[i,0] do
			inc(xx[i],log[reach[i,j]-1]);
	end;
    ans:=maxlongint div 843;
end;

begin
    Ready;
	mid:=n div 2; //中点
    right:=n div 2; //边界
	Dfs(1,0,1);
    right:=n;
	Dfs(2,0,mid+1); //注意
	writeln(ans);
end.







```

---

## 作者：VagrantAC (赞：2)

### $P2962 [USACO09NOV]Lights G$

#### 题解：

双向搜索，已知 $n$ 最大为 $35$ ，可以先通过对前面的 $n/2$ 进行搜索，之后再对后 $n/2$ 进行搜索，在搜索的过程中可对之前的每个状态进行匹配并输出最小值，这就是结果。

在实际编写的过程中

1. 每个开关不能被重复使用。
2. 需要用二进制来进行表示哪个状态使用过，哪个没有使用过。
3. 最后是匹配是使用二进制 ^ 匹配前 $n/2$ 的状态。

#### 代码

```cpp
#include <map>
#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
const int maxn = 600;
map<ll,int>mm[2];
vector<int>v[40];
int n,m;
inline ll exchar(ll ch,int x){
    if((ch>>x)&1)return ch-((ll)1<<x);
    return ch+((ll)1<<x);
}
inline int slove(){
    mm[0].clear();
    mm[1].clear();
    queue<pair<ll,ll> >q;
    ll s=0,e=((ll)1<<n)-1;
    q.push({s,0});mm[0][s]=0;
    while(!q.empty()){
        pair<ll,ll>p=q.front();
        q.pop();
        int k=mm[0][p.first];
        for(int i=0;i<n/2;++i){
            if((p.second>>i)&1)continue;
            pair<ll,ll>pp=p;
            pp.second+=((ll)1<<i);
            pp.first=exchar(pp.first,i);
            for(int j=0;j<v[i].size();++j){
                pp.first=exchar(pp.first,v[i][j]);
            }
            if(mm[0].count(pp.first)==0){
                mm[0][pp.first]=k+1;
                q.push(pp);
            }
        }
    }
    q.push({s,0});mm[1][s]=0;
    while(!q.empty()){
        pair<ll,ll>p=q.front();
        q.pop();
        int k=mm[1][p.first];
        for(int i=n/2;i<n;++i){
            if((p.second>>i)&1)continue;
            pair<ll,ll>pp=p;
            pp.second+=((ll)1<<i);
            pp.first=exchar(pp.first,i);
            for(int j=0;j<v[i].size();++j){
                pp.first=exchar(pp.first,v[i][j]);
            }
            if(mm[0].count(pp.first^e)){
                return mm[0][pp.first^e]+k+1;
            }
            if(mm[1].count(pp.first)==0){
                mm[1][pp.first]=k+1;
                q.push(pp);
            }
        }
    }
    return -1;
}
int main(){
    int x,y;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;++i){
        scanf("%d%d",&x,&y);
        --x;--y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    printf("%d\n",slove());
    return 0;
}
```



---

## 作者：Jμdge (赞：2)

mmp 这破题做我一个小时，还看了题解

明明知道高斯消元然后还一直wa，然后说什么自由元不自由元的...最后还是要深搜...

想吐...


其实这道题最主要的还是高斯消元解异或矩阵，后面那个什么乱来的深搜也就是给题目加点难度了，不然这题难度也就是黄的...

```
//by Judge
#include<cstdio>
#include<iostream>
using namespace std;
const int M=41;
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} int n,m,ans,A[M][M],l[M];
inline int gauss(){ bool flag=1;
	for(int i=1,j;i<=n;++i){
		for(j=i;j<=n&&!A[j][i];++j);
		if(j>n){flag=0;continue;}
		if(j^i) swap(A[i],A[j]);
		for(j=1;j<=n;++j) if(i^j&&A[j][i])
			for(int k=i;k<=n+1;++k) A[j][k]^=A[i][k];
	} return flag;
}
inline void dfs(int x,int num){
	if(num>ans) return ;
	if(!x) return ans=num,void();
	if(A[x][x]){ bool v=A[x][n+1];
		for(int i=x+1;i<=n;++i)
			if(A[x][i]) v^=l[i];
		dfs(x-1,num+v);
	} else{
		dfs(x-1,num),l[x]=1,
		dfs(x-1,num+1),l[x]=0;
	}
}
int main(){
	ans=n=read(),m=read();
	for(int i=1;i<=n;++i)
		A[i][n+1]=A[i][i]=1;
	for(int i=1,x,y;i<=m;++i)
		x=read(),y=read(),
		A[x][y]=A[y][x]=1;
	if(gauss()){ ans=0;
		for(int i=1;i<=n;++i)
			ans+=A[i][n+1];
	} else dfs(n,0);
	return !printf("%d\n",ans);
}
```




---


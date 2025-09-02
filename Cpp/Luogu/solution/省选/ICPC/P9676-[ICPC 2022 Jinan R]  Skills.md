# [ICPC 2022 Jinan R]  Skills

## 题目描述

庞博士有 $3$ 项技能：喝汽水、猎狐和炒股，编号分别为 $1,2,3$。初始时，每项技能的熟练度为 $0$。

接下来有 $n$ 天。在第 $i$ 天，庞博士可以选择一项技能（假设是第 $j$ 项）进行练习，然后在这天结束时让这项技能的熟练度增加 $a_{i,j}(0\leq a_{i,j}\leq 10000)$。同时，如果某一项技能（假设是第 $k$ 项）已经有 $x$ 天没有练习，那么在这天结束时，这项技能的熟练度会减少 $x$。当然，任何一项技能的熟练度都不可能小于 $0$。

现在，庞博士想知道：在第 $n$ 天结束后，这 $3$ 项技能的熟练度之和最大为多少。由于他非常忙，而且他的日程和对习惯的适应程度可能有变，所以庞博士把这 $T$ 个问题交给了你——每个问题的内容都一样，只是给出的数据可能有所不同而已。

## 样例 #1

### 输入

```
2
3
1 1 10
1 10 1
10 1 1
5
1 2 3
6 5 4
7 8 9
12 11 10
13 14 15
```

### 输出

```
26
41```

# 题解

## 作者：fishing_cat (赞：14)

[传送门](https://www.luogu.com.cn/problem/P9676)

### 思路

动态规划，考虑怎么做。

先想一个最普通的转移，然后看是否可以优化。设 $f_{i, j, k, h}$，每一维分别表示**现在是第几天**，**练习的编号下一项有多久没练了**，**编号下下项有多久没练了**，**练的是哪个**。

哎？这不看起来没有哪一维可以缩掉吗？确实，那先把最基础的转移写出来看看。

首先考虑，在一项技能从没有被练习时，是不会有熟练度负增长的，自然也就不存在所谓的**有多久没练了**。所以在转移时，将第二，三维下标为 $0$ 定义为没练习过，方便转移。由此，可以发现对下一次状态的二，三维的计算应该是 $j_{next} = j_{now} + (j_{now} \ne 0)$，$k$ 同理。

对于每一次转移，有三种操作。

* 继续练上一次练的
$$ f_{i, j_{next}, k_{next}, h} = \max(f_{i-1, j_{now}, k_{now}, h} + a_{i,h} - j_{next} -  k_{next})$$

* 换练编号下一项
$$ f_{i, k_{next}, 1, h+1} = \max(f_{i-1, j_{now}, k_{now}, h} + a_{i,h+1} - 1 -  k_{next})$$

* 换练编号下下项
$$ f_{i, 1, j_{next}, h+2} = \max(f_{i-1, j_{now}, k_{now}, h} + a_{i,h+2} - j_{next} -  1)$$

自然，因为只有三项，对 $h$ 做加法，溢出三的要绕回来。

可以想一下，没练的负增长是指数级的，所以第二，三维实际上限不会太大，超出上限后是一定不优的。现在考虑怎样把这个上限求出来。设一次练习加的熟练度是 $x$，假设 $y$ 天不练后将变得不优，可以列出 $x - \frac{y(y-1)}{2} \le 0$，大体估算求出 $y \ge 2\sqrt{x}$ 时是不优的。所以上限就是 $2\cdot \sqrt{\max(a_{i,j})}$。这样就将二，三维优化下来了。

现在的时间复杂度就是 $O(n\cdot \max(a_{i,j}))$。好耶，可以过了！！！等一等，你要不要算一下空间。最后一步，**滚动数组**，把第一维滚掉。

### code

[link](https://www.luogu.com.cn/record/187295043)

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
using namespace std;
/*快读省了*/
ll t, n, a[1100][4], ans = -inf;
ll f[3]/*  */[214]/*        */[214]/*   */[4];
// 第几天 下一项没练天数 下下项没练天数 练了哪个
//         0->未被练习过  0->未被练习过
il ll get(ll x) {
	if (x > 3) { return x - 3;}
    return x;
}

int main() {
	read(t);
	while (t--) { 
		read(n);
		ans = -1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= 3; j++) {
				read(a[i][j]);
				ans = max(ans, a[i][j]);
			}
		}	
		int MAX = 2*sqrt(ans);// 上限
		// init
		for (int now = 0; now <= 1; now++)
			for (int j = 0; j <= MAX; j++) 
				for (int k = 0; k <= MAX; k++) 
					for (int h = 1; h <= 3; h++) 
						f[now][j][k][h] = 0;		
		ll now = 1;
		for (int i = 1; i <= n; i++) {
			ll last = now ^ 1;
			// init
			for (int j = 0; j <= MAX; j++) 
				for (int k = 0; k <= MAX; k++) 
					for (int h = 1; h <= 3; h++) 
						f[now][j][k][h] = 0;			
			for (int j = 0; j <= min(MAX, i); j++) 
				for (int k = 0; k <= min(MAX, i); k++) 
					for (int h = 1; h <= 3; h++) {
						// strat 转移
						ll u = j + (j!=0), v = k + (k!=0), LAST = f[last][j][k][h];
						f[now][u][v][h] = max(f[now][u][v][h], LAST + a[i][h] - u - v);
						/*继续原来的*/
						f[now][v][1][get(h+1)] = max(f[now][v][1][get(h+1)], LAST + a[i][get(h+1)] - 1 - v);
						/*转下一项*/
						f[now][1][u][get(h+2)] = max(f[now][1][u][get(h+2)], LAST + a[i][get(h+2)] - u - 1);
						/*转下下项*/
					}
			now ^= 1;
		}
		ans = -1;
		for (int j = 0; j <= MAX; j++) 
			for (int k = 0; k <= MAX; k++) 
				for (int h = 1; h <= 3; h++) {
					ans = max(ans, f[now ^ 1][j][k][h]);
				}
		printf("%lld\n", ans);
	}
	return 0; // 完结撒花！！！
}
```

---

## 作者：wind_seeker (赞：6)

原本看到绿题进来，结果我的朋友做了一上午，汗流浃背，于是去看了官方题解。

首先考虑最朴素的 dp，设 $f_{i,d1,d2,d3}$ 表示第 $i$ 天的时候，三个技能分别有多久没有学习了，转移方程较为简单。但是显然这个复杂度是过不去的，考虑如何优化。

1. 滚掉第一维是必须的。

2. 考虑每天一定会学习一个技能，所以必然有一个技能在这一天未学天数为 $0$，所以我们压掉一维，记录当天学习了哪个技能。

此时设 $f_{cur,i,d2,d3}$ 表示第 $i$ 天学习了第 $i$ 个技能，按照顺序往后递增的两个技能未学习天数分别为 $d2$ 和 $d3$，记录往后递增的技能主要是为了更好的转移，例如如果学习技能 $1$，后面就是技能 $2,3$，学习的是技能 $2$，后面就是技能 $3,1$。

显然这个时间复杂度仍然是过不去的，考虑一个性质：

- 一旦一个技能开始学习，那么它一定不会在后面变为 $0$。

如果它在后面变为 $0$，那在学习它的那一天显然学习其他技能不管它更优。

而后我们可以继续证明一个未学习天数上限，假设目前所有 $a_{i,j}$ 中最大值为 $maxW$，那么如果有一个技能未学习 $2\sqrt{maxW}$ 天，则消耗值为 为 $2maxW+\sqrt{maxW}$。然而如果在 $\sqrt{maxW}$ 这一天学习一次该技能，则最多会放弃一个 $maxW$ 不学，该技能总消耗值在第 $2\sqrt{maxW}$ 天小于 $maxW+\sqrt{maxW}$，故总减少值严格小于 $2maxW+\sqrt{maxW}$，所以便可以把枚举未学习天数降至根号级别，卡常即可通过此题。

### code
~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10,inf=1e9+7,B=210;

int val[N],T,n;
int a[N][3],f[2][3][B][B];

void chkmax(int &a,int b){a=max(a,b);}

void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) for(int j=0;j<3;j++) cin>>a[i][j];
	memset(f,0,sizeof(f));
	int cur=0,nxt=1;
	for(int i=0;i<n;swap(cur,nxt),i++){
		for(int j=0;j<3;j++)
			for(int x=0;x<B&&x<=i;x++)
				for(int y=0;y<B&&y<=i;y++){
					int nx=x?x+1:0,ny=y?y+1:0;//如果是0则不学习不变
					if(nx<B&&ny<B) chkmax(f[nxt][j][nx][ny],f[cur][j][x][y]-nx-ny+a[i+1][j]);
					if(ny<B) chkmax(f[nxt][(j+1)%3][ny][1],f[cur][j][x][y]-ny-1+a[i+1][(j+1)%3]);
					if(nx<B) chkmax(f[nxt][(j+2)%3][1][nx],f[cur][j][x][y]-1-nx+a[i+1][(j+2)%3]);
				}
	}
	int ans=0;
	for(int j=0;j<3;j++)
		for(int x=0;x<B;x++)
			for(int y=0;y<B;y++)
				chkmax(ans,f[cur][j][x][y]);
	cout<<ans<<'\n';
}

int main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	for(int i=1;i<N;i++) val[i]=val[i-1]+1;
	cin>>T;while(T--) solve();
}
~~~

---

## 作者：是青白呀 (赞：5)

性质题。

首先，需要观察到的性质是：对于一个维度，我们一旦学习之后，就不会让它再次降低到 $0$，原因是降低到 $0$ 不如不学习，一直维持初始状态。

于是可以设出 dp：设 $f_{i,j,k,1/2/3}$ 表示考虑到第 $i$ 天，这一天提升的项目编号是 $1/2/3$，另两个项目中编号较小的一个已经有 $j$ 天没提升了；另一个已经有 $k$ 天没有提升的最大熟练度和。我们枚举下一天选哪个项目，利用 $j=0,k=0$ 的状态记录另外两个项目是否被提升过，并据此求出这一天的熟练度和变化量。注意这里是不需要考虑对 $0$ 取 $\max$ 的操作的，原因是根据上面提到的性质，不合法的操作一定不优。此时复杂度 $O(n^3)$。

考虑优化。对于某个项目，假设其连续 $2x$ 天没有被提升过，则总熟练度会减少 $\frac{2x(2x+1)}{2}=2x^2+x$；若我们选择最中间的一天转为选择这个项目，设这一天原来的熟练度增加量为 $y$，则总熟练度会减少 $y+2\times \frac{x(x+1)}{2}=x^2+x+y$。联立解不等式得 $x>\sqrt y$，也即一个项目被连续 $2\sqrt y$ 天以上不提升一定是不优的。$y$ 的上界显然为 $\max a_{i,j}$，则 $j,k$ 不会超过 $2\sqrt{\max a_{i,j}}$。此时复杂度变为 $O(nV)$，可以通过。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define int long long
#define double long double
#define qingbai 666
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=1005,M=1e6+5,S=(1<<15)+5,inf=(ll)1e18+7,mo=998244353;
const double eps=1e-8;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int T;
int n,a[N][3];
int f[2][205][205][3];
void getmax(int &x,int v){
    x=max(x,v);
}
void solve(){
    read(n);
    int maxn=0;
    rep(i,1,n){
        rep(j,0,2)
            read(a[i][j]),maxn=max(maxn,a[i][j]);
    }
    int upp=2*ceil(sqrt(maxn));
    rep(j,0,upp){
        rep(k,0,upp){
            rep(l,0,2)
                f[0][j][k][l]=-inf;
        }
    }
    f[0][0][0][1]=0;
    rep(i,0,n-1){
        int nwi=i&1;
        rep(j,0,upp){
            rep(k,0,upp){
                rep(l,0,2)
                    f[nwi^1][j][k][l]=-inf;
            }
        }
        rep(j,0,upp){
            rep(k,0,upp){
                rep(l,0,2){
                    if(f[nwi][j][k][l]<0)continue;
                    int trans[3];
                    trans[l]=(!i?0:1),trans[(l+1)%3]=j,trans[(l+2)%3]=k;
                    if(j)trans[(l+1)%3]++;
                    if(k)trans[(l+2)%3]++;//j,k 是 0 说明这个还没被选过
                    rep(x,0,2)
                        getmax(f[nwi^1][trans[(x+1)%3]][trans[(x+2)%3]][x],f[nwi][j][k][l]+a[i+1][x]-trans[(x+1)%3]-trans[(x+2)%3]);
                }
            }
        }
    }
    int ans=0;
    rep(j,0,upp){
        rep(k,0,upp){
            rep(l,0,2)
                ans=max(ans,f[n&1][j][k][l]);
        }
    }
    printf("%lld\n",ans);
}
signed main(){
    read(T);
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：yllcm (赞：2)

有点太难了。

首先，如果一项技能在若干次训练后熟练度减到了 $0$，那么可以看作没有训练。于是只要确定了某个技能第一次训练的时间，就可以忽略熟练度对 $0$ 取 $\max$ 的限制。

据此可以导出一个 $\mathcal{O}(n^3)$ 的做法：设 $f_{i,(x,y,z)}$ 表示考虑了前 $i$ 天，每个技能上次被操作的时间分别为 $x,y,z$。观察到 $x,y,z$ 至少一者为 $i-1$（或者都是 $0$），所以状态数实际上是 $\mathcal{O}(n^3)$，转移数复杂度是 $\mathcal{O}(1)$ 的。

直觉告诉我们：一个技能不会长期不学习。实际上，有结论：

* 结论：一个技能在第一次学习之后，至多 $\mathcal{O}(\sqrt{\max a_i})$ 天不学习。

先证明一个引理：在只学习两种技能的情况下，一定存在常数 $c$，使得在第 $c$ 天不学习任何技能的情况下，熟练度之和的变化量为 $\mathcal{O}(\max a_i+n)$ 级别。

我们把熟练度的贡献分为两类：第一类是练习增加的熟练度，第二类是长期不练习减少的熟练度。那么如果第 $c$ 天不学习任何技能，第一类贡献的减少量一定是 $\mathcal{O}(\max a_i)$ 级别的。对于第二类贡献，我们假设在第 $c$ 天练习的技能，在第 $c+2$ 天之前会再次练习一次（显然这种技能会在常数天后出现），那么第二类贡献只会在第 $c$ 天和第 $c+1$ 天增加，且变化量均为 $\mathcal{O}(n)$。所以我们证明了引理。

接着我们通过调整证明结论。如果一种技能连续 $B$ 天都没有练习，那么如果我们在 $\frac{B}{2}+c$ 天练习这个技能，根据引理，剩下两个技能熟练度的减少量是 $\mathcal{O}(\max a_i+n)$ 级别。而对于这种技能，第二类贡献的减少量为：$f(B)-2f(\frac{B}{2})$，其中 $f(n)$ 为 $1\sim n$ 的和。$f(B)-2f(\frac{B}{2})$ 约为 $\frac{B^2}{4}$，所以当 $\frac{B^2}{4}>\mathcal{O}(\max a_i+n)$ 的时候，调整更优。所以最优方案的 $B$ 不会超过 $\mathcal{O}(\sqrt{\max a_i})$。

所以直接 DP 的复杂度为 $\mathcal{O}(n\max a_i)$，可以通过。[code](https://qoj.ac/submission/245730)

---

## 作者：xmkxk (赞：1)

~~写题写的眼睛要瞎了，来写个题解。~~

---
首先来定义状态 $f_{i,j,x,y}$ 表示第 $i$ 天练习技能  $j$，且另外两个技能分别有 $x$ 天和 $y$ 天没练习（ $x$ 和 $y$ 为 $0$ 代表一直没练）。注意到练习获得的熟练度不大于 $10000$，则当 $\frac{x(x+1)}{2}>10000$ 时，我们不再扩大 $x$ 的范围进行枚举，故每次 $x$ 的上界为 $\sqrt{v}$，$v$ 为单次获得熟练度的最大值。

转移采用刷表法，思路比较简单，细节见代码，时间复杂度为  $O(n \times v)$。

注意:转移方程中 $x$ 与 $y$ 在数组中的位置有意义，不能随意交换。


---

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=1009;
void gmax(int &a,int b){
	if(b>a)a=b;
}

int a[N][5];
int f[2][5][209][209];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d%d%d",&a[i][0],&a[i][1],&a[i][2]);
		}

		memset(f,0,sizeof f);
		for(int i=1;i<=n;i++){
			for(int j=0;j<3;j++){
				for(int d1=0;d1<=min(i,200);d1++){
					for(int d2=0;d2<=min(i,200);d2++){
						int D1=d1?d1+1:0,D2=d2?d2+1:0;
						//D1,D2的位置有意义
						gmax(f[i&1][j][D1][D2],f[(i-1)&1][j][d1][d2]+a[i][j]-D1-D2);
						gmax(f[i&1][(j+1)%3][D2][1],f[(i-1)&1][j][d1][d2]+a[i][(j+1)%3]-D2-1);
						gmax(f[i&1][(j+2)%3][1][D1],f[(i-1)&1][j][d1][d2]+a[i][(j+2)%3]-D1-1);
					}
				}
			}
		}
		int ans=0;
		for(int j=0;j<3;j++)
			for(int x=0;x<=200;x++)
				for(int y=0;y<=200;y++)
					ans=max(ans,f[n&1][j][x][y]);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：ykzzldz (赞：1)

妙妙题。

先考虑一个比较简单的 dp，设 $f_{i,j,k,o}$ 表示到第 $i$ 天，第 $i$ 天练了 $j$，剩下两项分别有 $k,o$ 天没练的答案。我们发现，复杂度是 $O(n^3)$ 的，不能接受。

在思考良久后，我们发现这个状态似乎没办法优化了。考虑直观上的感受，由于熟练度的减少是一个二次函数，是非常快的，所以一个东西隔了太久不练，那么一定是不优的，我们考虑这个不优的上界是多少。

这个不优，也就是说某次的练习是完全没用的。设一次练习的价值为 $w$，接下来 $k$ 天不练，不优的情况为 $w-\frac{k\times(k-1)}{2}\le0$，所需的情况就是 $k\le2\sqrt{w}$。所以，我们将天数的上界定为 $200$ 左右即可。最后，可能需要考虑某个东西一次都不练习的边界情况，这题就做完了。

---

## 作者：MoonCake2011 (赞：0)

看讨论区，这题之前是绿题，还是太超模了。

首先，朴素 $dp$ 是 $dp_{i,u,v,w}$ 为前 $i$ 天有 $u$ 天没练习喝汽水，有 $v$ 天没练习猎狐，有 $w$ 天没练习炒股。

但这样绝对过不了，所以尝试优化。

首先，一个常见的优化就是 $u$，$v$，$w$ 里的一个必须为 $0$，所以我们可以记录 $0$，$1$，$2$ 中哪个是 $0$。

但这样是 $O(n^3)$ 的，于是考虑继续找性质优化。

还有一个点，一个项目的熟练度不会第二次为 $0$，因为只要为 $0$ 了不如去练其他项目。

所以我们又发现怠工一个项目 $n$ 天减的熟练度是 $O(n^2)$ 级别的，大约是 $4n^2$ 的样子。

这里我们间隔 $2\sqrt{a_{i,j}}$ 天以上不练习，其实不如第 $i$ 天去练习其他项目。

所以 $u$ 和 $v$ 最优解的最大值为 $200$。

设 $a_{i,j}$ 的最大值为 $W$。

最后再将 $i$ 滚掉，时间复杂度 $O(nW)$，空间复杂度 $O(W)$。

可以过掉。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int a[10010][3];
int dp[2][210][210][3];
inline void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) for(int j=0;j<3;j++) cin>>a[i][j];
	memset(dp,0,sizeof dp);
	for(int i=1;i<=n;i++){
		memset(dp[i&1],0,sizeof dp[i&1]);
		for(int lu=0;lu<=min(201ll,i);lu++){
			for(int lv=0;lv<=min(201ll,i);lv++){
				for(int w=0;w<3;w++){
					int u=lu+bool(lu),v=lv+bool(lv);
					dp[i&1][u][v][w]=max(dp[i&1][u][v][w],dp[(i&1)^1][lu][lv][w]+a[i][w]-u-v);
					dp[i&1][v][1][(w+1)%3]=max(dp[i&1][v][1][(w+1)%3],dp[(i&1)^1][lu][lv][w]+a[i][(w+1)%3]-1-v);
					dp[i&1][1][u][(w+2)%3]=max(dp[i&1][1][u][(w+2)%3],dp[(i&1)^1][lu][lv][w]+a[i][(w+2)%3]-u-1);
				}
			}
		}
	}
	int ans=0;
	for(int i=0;i<=201;i++) for(int j=0;j<=201;j++) for(int k=0;k<3;k++) ans=max(ans,dp[n&1][i][j][k]);
	cout<<ans<<"\n";
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0); 
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：sunset_breeze (赞：0)

性质题。

性质：如果学了一个技能，那么以后就不会上这样技能低于 $0$，因为如果低于 $0$ 了，不如当初就不学，学其他的技能。

所以我们发现如果学了一个技能以后，最多间隔 $\sqrt{W}+O(1)$ 天就会再学一次。⽐如⼀个技能 200 天没有学习，不如 100 天的时候学⼀下，那么会损失掉当天的收益，但是后⾯ 100 天每天会少损失 100 点，所以不亏。

那么我们就设 $f_{i,j,k,1/2/3}$ 表示当前到了第 $i$ 天，这一天学习的是第 $1/2/3$ 项技能，其余两项技能已经有 $j,k$ 天没有学了。**注意如果 $j,k$ **为 $0$ 的话就表示**根本就没有学过这个技能**。

那么直接转移就行了。注意实现得太差（⽐如多乘了很多个 3，或者额外⼀维状压每个技能有没有开始学习）会有⼀些常数问题。

时间复杂度：$\mathcal O(nV)$。

---

## 作者：WoXitao (赞：0)

题目大意：

有 $n$ 天，每天可以选择三个技能中的一个进行学习，会对这个技能增加 $a_i$的熟练度，当一天过去了，如果技能 $i$ 有 $x$ 天没有学，会对技能 $i$ 扣除 $x$ 熟练度，熟练度最低是 $0$，最大化最后的各技能熟练度之和。

解答：

我们可以设计一个dp方程为 $dp_{i,j,a,b}$ 表示第 $i$ 天学了技能 $j$，$j$ 前一个技能 $a$ 天没有学，$j$ 后面的一个技能 $b$ 天没有学，最终的熟练度之和是多少。

可以发现，这个方程很好转移。

转移如下：

```c++
int j1=a+(a!=0),j2=b+(b!=0);
dp[i][j][j1][j2]=max(dp[i][j][j1][j2],dp[i-1][j][a][b]+a[i][j]-j1-j2);
dp[i][(j+1)%3][j2][1]=max(dp[i][(j+1)%3][j2][1],dp[i-1][j][a][b]+a[i][(j+1)%3]-1-j2);
dp[i][(j+2)%3][1][j1]=max(dp[i][(j+2)%3][1][j1],dp[i-1][j][a][b]+a[i][(j+2)%3]-j1-1);
```

这样时间复杂度太大了，我们可以发现，上面的 $a$ 和 $b$ 如果太大的话可能会抵消前面的熟练度，发现其上限是 $2×\sqrt{\max a}$ 大约是 $200$ 。这样子时间复杂度就降到 $O(nV)$ 了。

记得加上滚动数组优化。

code：

```c++
#include<bits/stdc++.h>
using namespace std;
int a[1003][4],dp[2][4][500][500];

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		for(int i=1;i<=n+2;i++){
			for(int j=0;j<=2;j++) a[i][j]=0;
		}
		for(int i=1;i<=n;i++){
			cin>>a[i][0]>>a[i][1]>>a[i][2];
		}
		int last=0;
		memset(dp,0,sizeof dp);
		for(int i=1;i<=n;i++){
			int p=i&1;
			for(int j=0;j<=2;j++)
				for(int x=0;x<=200;x++)
					for(int y=0;y<=200;y++) dp[p][j][x][y]=0;
			for(int j=0;j<=2;j++){
				for(int x=0;x<=min(i,202);x++){
					for(int y=0;y<=min(i,202);y++){
						int j1=x+(x!=0),j2=y+(y!=0);
						dp[p][j][j1][j2]=max(dp[p][j][j1][j2],dp[last][j][x][y]+a[i][j]-j1-j2);
						dp[p][(j+1)%3][j2][1]=max(dp[p][(j+1)%3][j2][1],dp[last][j][x][y]+a[i][(j+1)%3]-1-j2);
						dp[p][(j+2)%3][1][j1]=max(dp[p][(j+2)%3][1][j1],dp[last][j][x][y]+a[i][(j+2)%3]-j1-1);
					}
				}
			}
			last=p;
		}
		
		int ans=0;
		for(int j=0;j<=2;j++){
			for(int x=0;x<=200;x++){
				for(int y=0;y<=200;y++){
					ans=max(ans,dp[n&1][j][x][y]);
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---


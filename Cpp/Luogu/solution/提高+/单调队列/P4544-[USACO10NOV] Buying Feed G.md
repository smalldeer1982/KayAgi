# [USACO10NOV] Buying Feed G

## 题目描述

约翰开车来到镇上，他要带$K$吨饲料回家。运送饲料是需要花钱的，如果他的车上有$X$吨饲料，每公里就要花费$X^2$元，开车D公里就需要$D\times  X^2$元。约翰可以从$N$家商店购买饲料，所有商店都在一个坐标轴上，第$i$家店的位置是$X_i$，饲料的售价为每吨$C_i$元，库存为$F_i$。

约翰从坐标$X=0$开始沿坐标轴正方向前进，他家在坐标$X=E$上。为了带$K$吨饲料回家，约翰最少的花费是多少呢？假设所有商店的库存之和不会少于$K$。

举个例子，假设有三家商店，情况如下所示：

|坐标|$X=1$|$X=3$|$X=4$|$E=5$|
|:-:|:-:|:-:|:-:|:-:|
|库存|$1$|$1$|$1$|
|售价|$1$|$2$|$2$|

如果$K=2$，约翰的最优选择是在离家较近的两家商店购买饲料，则花在路上的钱是$1+4=5$，花在商店的钱是$2+2=4$，共需要$9$元。

## 说明/提示

$1 \leq K \leq 10000 , 1 \leq E \leq 500 , 1 \leq N \leq 500$

$0 < Xi < E, 1 \leq Fi \leq 10000, 1 \leq C_i \leq 10^7$

## 样例 #1

### 输入

```
2 5 3
3 1 2
4 1 2
1 1 1```

### 输出

```
9```

# 题解

## 作者：Unknown_Error  (赞：60)

首先先考虑朴素dp，设f[i][j]为到了第i家店，1~i-1家店共买了j吨饲料 

那么转移可以写成 ：

f[i][j]=min(f[i][j],f[i-1][k]+j*j*d[i]+(j-k)*a[i-1].w); 
其中a[i-1].w为第i-1家店饲料的价格，d[i]为第i与i-1家店的距离 
复杂度为O(nk^2)，很明显炸了 

## 怎么办？？
先把式子拆了吧 

f[i][j]=min(f[i][j],f[i-1][k]+j*j*d[i]+j*a[i-1].w-k*a[i-1].w) 

提出来f[i-1][k]+j*j*d[i]+j*a[i-1].w-k*a[i-1].w 

把属于k的提出来，变为f[i-1][k]-k*a[i-1].w+j*j*d[i]+j*a[i-1].w 

可以发现，后半部分是定值，我们用单调队列维护前半部分就好了 
但是如果单纯的单调队列会错，为啥？如果我这家店所能提供的饲料不够我需要的呢？ 

所以，还要加上几个特判啦
# 代码
```
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long LL;
const LL inf=1e15;
struct node
{
    LL x,c,w;//距离 数量 价格 
}a[11000];
bool cmp(node n1,node n2){return n1.x<n2.x;}
LL f[510][11100];//第i家店 1~i-1家店装了j吨饲料
int n,m,kk;//n家店 距离m 希望买kk
LL d[11000];
LL list[11000],head,tail;
int main()
{
    //freopen("feed.in","r",stdin);
    //freopen("feed.out","w",stdout);
    scanf("%d%d%d",&kk,&m,&n);
    for(int i=1;i<=n;i++)scanf("%lld%lld%lld",&a[i].x,&a[i].c,&a[i].w);
    n++;a[n].x=m;
    sort(a+1,a+1+n,cmp);
    for(int i=2;i<=n;i++)d[i]=a[i].x-a[i-1].x;
    for(int i=0;i<=n;i++)for(int j=0;j<=kk;j++)f[i][j]=inf;
    f[0][0]=0;
    for(LL i=1;i<=n;i++)
    {
        head=tail=0;
        for(LL j=0;j<=kk;j++)
        {
            while(head<tail && j-list[head]>a[i-1].c)head++;//需要买的 本商店不能满足 
            if(f[i-1][j]!=inf)
            {
                while(head<tail)
                {
                    LL k=list[tail-1];
                    if(f[i-1][k]-k*a[i-1].w<f[i-1][j]-j*a[i-1].w)break;
                    tail--;
                }
                list[tail++]=j;
            }
            if(head<tail)
            {
                LL k=list[head];
                f[i][j]=f[i-1][k]+(j-k)*a[i-1].w+j*j*d[i];
            }
        }
    }
    printf("%lld\n",f[n][kk]);
    return 0;
}
```

---

## 作者：E_huan (赞：40)

**非单调队列写法，直接用一个变量维护决策即可。时间复杂度和单调队列写法相同。**


------------


前言：写本题时用了一个很简洁的做法，但其中利用的函数凸性和单调性我不会证明，后来看题解区都是单调队列写法，比较怀疑自己的做法正确性，就发帖求助，得到了热心神犇 @Alex_Wei 的帮助，基本确定做法的正确性，而且感觉这和题解区已有的单调队列做法本质并不相同（那位神犇也是这么说的嘿嘿），于是写题解提供一个新思路，但题解通道已关闭，不知道能否交上去。


------------
#### 朴素 DP：

首先还是按照坐标给商店排，然后 DP:

$f_{i, j}$ 表示考虑到第 $i$ 家商店 已经有 $j$ 吨饲料的最小花费，每次枚举新的商店买多少。时间复杂度 $O(nk^2)$ 无法通过。

#### 考虑优化，需要两个性质（放在最后证明）：


性质 $1$：任意时刻 $f_{i, j}$ 都关于 $j$ 下凸。


性质 $2$：只考虑从 $1$ 到 $i$，最优决策中“在 $1$ 到 $(i-1)$ 买的量”随着“ $1$ 到 $i$ 买的总量”增加而不减。

我们定义变量 $pos$ 表示“上次（$j$ 还是 $(j-1)$ 的时候）取到最优解的时候在 $1$ 到 $(i-1)$ 买的数量”，即“对于 $(j-1)$ 的最优决策的位置”。


有了性质 $1$，我们就可以通过从头开始扫，判断 $pos$ 与 $pos+1$ 谁更优即可确定 $pos$ 是否是对于当前 $j$ 的最优决策。直接通过`while(pos<j&&get(i,j,pos)>=get(i,j,pos+1)) pos++;` 求出最优解。

但如果每次都从让 $pos$ 从 $1$ 开始扫，那么时间复杂度和朴素 DP 是一样的，还需要性质二来优化：

根据性质 $2$，我们发现随着 $j$ 增大， $pos$ 取到的值是单调不减的，也就是说可以直接继承上次的 $pos$ 往后扫，那么 $pos$ 最多变化 $O(n)$ 次，内层的时间复杂度就降到了 $O(n)$，再算上外层枚举每家商店，总时间复杂度 $O(nk)$，轻松通过。

AC 代码：(还是非常短的，没怎么压行）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10010;
int k,e,n;
long long f[505][N];
struct node
{
    int x,f,c;
    bool operator<(const node &t)const{return x<t.x;}
}p[N];
inline long long get(int t,int i,int j) 
{
    return f[t-1][j]+1ll*p[t].c*(i-j)+1ll*j*j*(p[t].x-p[t-1].x);
}
int main()
{
    scanf("%d%d%d",&k,&e,&n);
    for(int i=1;i<=n;i++) 
        scanf("%d%d%d",&p[i].x,&p[i].f,&p[i].c);
    p[++n]={e,0,0};//直接算到到家
    sort(p+1,p+n+1);
    memset(f,0x3f,sizeof f); f[0][0]=0;
    for(int i=1;i<=n;i++)
        for(int j=0,pos=0;j<=k;j++)
        {
            while(pos<j-p[i].f) pos++;//保证j-pos是可以在这家买到的（即不超过p[i].f)
            while(pos<j&&get(i,j,pos)>=get(i,j,pos+1)) pos++;
            f[i][j]=get(i,j,pos);
        }
    printf("%lld\n",f[n][k]);
    return 0;
}
```
#### 性质的证明：

(用 $D$ 表示两家店之间的距离，即代码中的 `(p[t].x-p[t-1].x)` )


性质 $1$：从 $f_{i - 1}$ 到 $f_i$，首先给 $j$ 位置上加上了 $Dj ^ 2$，又和 $y = c_ix (0\leq x\leq f_i)$ 做了闵可夫斯基和（闵可夫斯基和就是“两个欧几里得空间的点集的和”，详细解释及性质可以查找相关博客吧）， $y = c_ix (0\leq x\leq f_i)$ 是一次函数，$Dj^2$ 是二次函数，所以都是凸的。两个凸包的闵可夫斯基和还是凸包，所以这个函数是凸函数。

性质 $2$:结合凸性和反证法证明，如果  $f_{i, j}$ 的决策点为 $pos$，$f_{i, j'}$ 的决策点为 $pos'$，若 $j < j'$ 且 $pos>pos'$，发现从 $pos'$ 转移到 $f_{i, j}$ 更优，与 $pos$ 是 $f_{i , j}$ 的决策点矛盾，故不成立。


------------


完结撒花！感谢您的阅读，如果蒟蒻有写错的地方，请神犇们不吝赐教！

~~点赞再润！~~


---

## 作者：devout (赞：21)

考虑$dp$

- 状态：设$f_{i,j}$表示在第$i$个商店一共买到了$j$吨饲料

- 转移：

$$f_{i,j}=\min\{f_{i-1,k}+k^2\times (x_i-x_{i-1})+(j-k)\times c_i\}$$

其中$k$需要满足能够在这个地方买到$j-k$个

那么这个复杂度应该是$O(nK^2)$的，显然不是很优，考虑进行单调队列优化

讲那个式子做一个简单的变化，可以得到

$$f_{i,j}=\min\{f_{i-1,k}+k^2\times(x_i-x_{i-1})-k\times c_i\}+j\times c_i$$

那么我们发现转移的部分只有$i$和$k$了，那么这个时候我们就可以利用单调队列优化这个$dp$了,复杂度$O(nK)$

- 初值：$f_{i,j}=inf,f_{0,0}=0$，因为有些部分是不能取到的，所以初值要设inf

- 答案：因为最后答案是要走到$E$的，所以最后的答案应该是$f_{n,K}+K^2\times(E-x_n)$

代码：变量名有点混乱...

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=505;
const int M=10005;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

# define int long long

int s,n,m;
int f[N][M];
int q[M],head,tail;

struct node{
    int x,f,c;
    bool operator < (const node &cmp)const{
        return x<cmp.x;
    }
}a[N];

int calc(int p,int x){
    return f[p-1][x]+x*x*(a[p].x-a[p-1].x)-a[p].c*x;
}

signed main()
{
    memset(f,0x3f,sizeof(f));
    read(s),read(n),read(m);
    Rep(i,1,m)read(a[i].x),read(a[i].f),read(a[i].c);
    sort(a+1,a+m+1);
    f[0][0]=0;
    Rep(i,1,m){
        head=1,tail=0;
        Rep(j,0,s){
            while(head<=tail&&calc(i,q[tail])>calc(i,j))tail--;
            while(head<=tail&&q[head]<j-a[i].f)head++;
            q[++tail]=j;
            f[i][j]=calc(i,q[head])+a[i].c*j;
        }
    }
    printf("%lld\n",f[m][s]+s*s*(n-a[m].x));
    return 0;
}
```


---

## 作者：Sagittarius (赞：10)

时间复杂度：O(EKlogF)

本题一看，大致方向便是DP。

考虑状态定义：f[i][j]表示到了里起点i个单位的地方，带着j的饲料的最小花费。

初始化：f[i][j]=INF，f[0][0]=0

接着考虑转移，对于每一个f[i][j]，它可以选择不买，从f[i-1][j]转移过来；如果第i个点有商店，可以选择买。于是可以先预处理商店的坐标，将其按照离起点的距离排序，这样就能便捷的判断当前的i有没有商店。

如果没有商店，f[i][j]=f[i-1][j]+j×j

如果有商店，可以购买不超过商店总量的任意质量的饲料，于是想到通过多重背包来转移。一种是朴素的，把多重背包当作01背包做，每次放入1个饲料，这样的时间复杂度是500×10000×10000肯定要炸；于是使用二进制优化。

数学原理：一个数可以通过1+2+4+8+16+..+2^k+t组成

于是分别吧1/2/4/8/16...个饲料打成一个物品，便可以log10000转移。总时间复杂度为500×10000×10，是一个50000000的优秀算法。

代码：

```
#include<bits/stdc++.h>
#define fsb(a,b,c) for (ull a=b;a<=c;a++)
#define fbs(a,b,c) for (ull a=b;a>=c;a--)
#define maxm 10100
#define maxl 510
#define maxn 510
#define mem(a,b) memset(a,b,sizeof(a))
#define INF 9999999999999999
#define min(a,b) ((a)<(b)?(a):(b))
#define ull long long
using namespace std;
ull m,l,n,now,last,k=1;
ull f[2][maxm];
struct shop{
	ull d,c,m;
}a[maxn];
ull cmp(shop a,shop b){
	return a.d<b.d;
}
ull check(ull i,ull j){
	return j>=0&&f[i][j]<INF;
}
int main(){
	// freopen("feed.in","r",stdin);freopen("feed.out","w",stdout);
	cin>>m>>l>>n;//scanf("%d%d%d",&m,&l,&n);
	// cout<<f[0][0];
	// fsb(i,1,n) scanf("%d%d%d",&a[i].d,&a[i].m,&a[i].c);
	fsb(i,1,n) cin>>a[i].d>>a[i].m>>a[i].c;
	sort(a+1,a+1+n,cmp);
	// fsb(i,1,n) printf("%10d%10d%10d\n",a[i].d,a[i].m,a[i].c);
	fsb(i,0,m) f[0][i]=INF;
	f[0][0]=0;now=1;last=0;
	fsb(i,1,l){
		// printf("%10d\n",i);
		fsb(j,0,m) f[now][j]=INF;
		fsb(j,0,m) if (check(last,j)) f[now][j]=min(f[now][j],f[last][j]+j*j);//不买，转移
		// printf("%12d",i);fsb(j,0,m) printf("%12d",f[now][j]);printf("\n");
		while (k<=n&&a[k].d==i){
			ull t=1,tot=0;
			while (1){//买，二进制优化，从f[i][ii-t]转移到f[i][ii]
				tot+=t;if (tot>a[k].m){
					tot-=t;break;
				}
				fbs(ii,m,t)
					if (check(now,ii-t))
						f[now][ii]=min(f[now][ii],f[now][ii-t]+t*a[k].c);
				t*=2;
			}
			t=a[k].m-tot;
			fbs(ii,m,t)
					if (check(now,ii-t))
						f[now][ii]=min(f[now][ii],f[now][ii-t]+t*a[k].c);
			// printf("%10d%10d%10d\n",a[k].d,a[k].m,a[k].c);
			k++;
			
		}
		
		// printf("%12d",i);fsb(j,0,m) printf("%12d",f[now][j]);printf("\n");
		swap(now,last);
	}
	// printf("%0.0lf\n",f[last][m]);
	cout<<f[last][m]<<endl;
	fclose(stdin);fclose(stdout);
	return 0;
}
```

注意点：最大可能有500×10000×10000+的花费，要开long long

优化：f[i]仅与f[i-1]有关，果断滚动数组

---

## 作者：rsdbk_husky (赞：9)

放在前面：本方法时间复杂度为 $O(nW)$ ，单调队列优化 DP。本题还有一道[弱化版](https://www.luogu.com.cn/problem/P2616)，欢迎大佬切完这题顺便把那题也切了，并欢迎大家来该题题解看我的[另一篇博客](https://rsdbk-husky.blog.luogu.org/luogo-p2616-usaco10janbuying-feed-ii-s)。 

## 零. 安利：

[安利一下我的博客。](https://rsdbkhusky.github.io/)

### 一. 变量声明：

- $W$：代替题目中的 $K$，到家时应带的饲料吨数，相当于背包中的背包最大承重（weight）。
- $n$：代替题目中的 $N$，商店数量，相当于背包问题中的物品数。
- $x_i$：同题目中的 $x_i$。
- $w_i$：代替题目中的 $f_i$，商店 $i$ 食物数量。
- $v_i$：代替题目中的 $c_i$，商店 $i$ 食物单价。

## 二. 思路

##### 1. 思考解法

- 路线上后面的商店不会影响路线前半部分的最优解，**符合无后效性**。
- 有最大容量 $W$，有可选择的物品，每个物品有重量和价值，明显是背包类问题。

所以考虑背包 DP。

##### 2. 初始状态

$d_{i,j}=\begin{cases} 0~~~~~~~~~(i=0~\land~j=0)\\ \infty~~~~~~~(else) \end{cases}$

##### 3. 结束状态

$d_{\operatorname{home},W}$        （$\operatorname{home}$：见代码和代码中的注释）

##### 4. 确定状态转移方程

$d_{i,j}$：已经经过前 $i$ 个商店（已到 $i$ 号商店买了东西但还没有往 $i+1$ 号走）且恰好一共买了 $j$ 份食物时最少花费的费用。

本题就是一道改装版的[多重背包问题](https://www.luogu.com.cn/problem/P1776)，就加了一个转移花费，转移花费怎么求呢？$i$ 店与上一家店距离差为 $x_i-x_{i-1}$，若在 $i$ 号店之前买的食物份数一共为 $k$ ，在 $i$ 店购物后车上的食物份数为 $j$，则这段路上车辆运送的食物数为 $k$。转移花费就是 $(x_i-x_{i-1})\times k^2$。

综上所述，朴素状转方程：$d_{i,j}=\min_{k=0}^{k\leqslant j}\{{d_{i-1,k}+(x_i-x_{i-1})\times k^2+v_i\times (j-k)}\}$ 

#### 5. 单调队列优化（重点）

枚举 $i$ 复杂度为 $O(n)$，枚举 $j$ 复杂度为 $O(W)$，枚举 $k$ 最坏情况下复杂度也是 $O(W)$。总复杂度 $O(nW^2)$ 显然会超。那么让我们观察一下状转方程：

$$~~~~~~~~d_{i,j}=\min_{k=0}^{k\leqslant j}\{{d_{i-1,k}+(x_i-x_{i-1})\times k^2+v_i\times (j-k)}\}$$ 

$$\Longrightarrow d_{i,j}=\min_{k=0}^{k\leqslant j}\{{d_{i-1,k}+(x_i-x_{i-1})\times k^2-v_i\times k+v_i\times j}\}$$  

**重点一** ：观察上面这个拆了个括号的方程，左边是我们要去求的状态，在该状态下，$i$ 和 $j$ 是已知的，因为该状态就是由 $i$ 和 $j$ 定义的，$i$ 和 $j$ 在一个具体的状态下为常量（或者换一种解释：$i$ 和 $j$ 是用 ```for``` 循环枚举出来的，所以我们当然知道他的值）。所以我们可以将 $v_i\times j$ 提出括号。可得：

$$\Longrightarrow d_{i,j}=\min_{k=0}^{k\leqslant j}\{{d_{i-1,k}+(x_i-x_{i-1})\times k^2-v_i\times k}\}+v_i\times j$$ 

**重点二**：这个方程中的变量只有 $k$，而又有 $k\leqslant j$，因为在 $i$ 店购物后的食物数不可能低于购物前。那么我们就可以使用[单调队列](https://www.luogu.com.cn/problem/P1886)优化。单调队列中存放的就是 $\min$ 内的部分 $d_{i-1,k}+(x_i-x_{i-1})\times k^2-v_i\times k$ （在这里我们把它称作 $calc_{i,k}$），对于每一个 $i$ ，将 $j$ 从 $0$ 到 $W$ 枚举一遍，对于每个 $j$ 先将它作为 $k$ 计算 $calc_{i,k}$ 并放到单调队列中，再先计算状态 $d_{i.j}$。

## 三. 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

#define re register
#define int long long

const int MAXn = 500;
const int MAXW = 10000;

template <class T> 
inline void read(T &a) {
    register char c;while (c = getchar(), c < '0' || c >'9');register T x(c - '0');while (c = getchar(), c >= '0' && c <= '9')x = (x << 1) + (x << 3) + c - '0';a = x;  
}

template <class T>
inline T min(T a, T b) {
	return a < b ? a : b;
}

struct Shop {
	int x;
	int w;
	int v;
	
	Shop(): x(0), w(0), v(0){}
	Shop(int x_, int w_, int v_): x(x_), w(w_), v(v_) {}
	inline bool operator < (Shop &a) {
		return this->x < a.x;
	}
};

Shop shop[MAXn + 10];
int W, n, d[MAXn + 10][MAXW + 10];
int head, tail, que[MAXW + 10];

inline int calc(int i, int k) {
	return d[i - 1][k] + (shop[i].x - shop[i - 1].x) * k * k - shop[i].v * k;
}

signed main() {
	int E;
	read(W), read(E), read(n);
	shop[0] = Shop(0, 0, 0);    //本人将起点和终点（家）时当做食物数为 0 的商店，这样能避免特判，所以“home”就是n+1
	for (re int i = 1, x, w, v; i <= n; ++i) {
		read(x), read(w), read(v);
		shop[i] = Shop(x, w, v);
	}
	shop[n + 1] = Shop(E, 0, 0);    //同上
	sort(shop, shop + n + 2);
	memset(d, 0x3f, sizeof(d));
	d[0][0] = 0;
	for (re int i = 1; i <= n + 1; ++i) {    //i：当前阶段是在哪个店 
		head = 1; tail = 0;
		for (re int j = 0; j <= W; ++j) {    //j：当前状态要求在此处商店购买后车上有多少饲料
            while (calc(i, que[tail]) > calc(i, j) && head <= tail)
				--tail;
            if (j - que[head] > shop[i].w && head <= tail)
				++head;
			que[++tail] = j;
            d[i][j] = calc(i, que[head]) + shop[i].v * j;			
		}
	}
	printf("%lld", d[n + 1][W]);
}
```



---

## 作者：BriMon (赞：7)

我们发现， 最优的情况肯定是从家里往前走，走到要到达想要到的最远的商店， 往回走的时候再买东西；

这就提示我们， 我们要先对坐标排序， 然后设dp[i][j],表示到了第i个商店， 在第i个商店之前买了j个东西的最小花费；

dp[i][j]=min(dp[i-1][p]+dis[i] * j^2+w[i-1] *(j-p));

update:式子炸了不知道为什么打不上，看我[博客](https://www.cnblogs.com/zZh-Brim/p/9129917.html)吧

什么意思呢?

我们枚举一个p， 表示第i-1个商店时有p个货物，那么显然在i-1个商店买了(j-p)个货物，算上在第i-1个商店的花费，加上从i-1到i的路费，就是dp[i][j]；

复杂度nk^2， 妥妥的炸；

考虑优化；

发现转移式子里有min，自觉地想到了单调队列；

我们对式子进行一波变形。

dp[i-1][p] - w[i-1]*p + dis[i]*j*j + w[i-1]*j;

我们发现， 在i和j变化的时候，只有p是在变的，所以我们单调队列里放p；

怎么处理呢？

如果(j-q.front() > F[i-1])就pop掉队首， 因为我们要在i-1商店买的货物大于了第i-1个店的库存；

如果o=q.back(), dp[i-1][o]-w[i-1]*o >= dp[i-1][j]-w[i-1]*j, 就pop掉队尾；显然；

(写反了这个↑还能A， 数据太水了)

要注意的是，要把自己的家也当成一个点，这样dp[n][k]才是最后的答案！

然后注意开long long；

Code:
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define int long long

inline int read()
{
    int res=0;bool fl=0;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')fl=1;ch=getchar();
    }while(isdigit(ch)){res=(res<<3)+(res<<1)+(ch-'0');ch=getchar();
    }return fl?-res:res;
}

int n, k, e;

struct date
{
    int pos;
    int F;
    int w;
    friend bool operator <(date a, date b)
    {
        return a.pos < b.pos;
    }
}fam[1000010];

int dp[510][10010];

signed main()
{
    k = read(), e = read(), n = read();
    
    for (register int i = 1 ; i <= n ; i ++)
    {
        fam[i].pos = read(), fam[i].F = read(), fam[i].w = read();
    }
    
    fam[++n] = (date){e, 0, 0};
    
    sort(fam + 1, fam + 1 + n);
    
    memset(dp, 0x3f, sizeof dp);
    
    dp[0][0] = 0;
    
    for (register int i = 1 ; i <= n ; i ++)
    {
        deque <int> q; 
        for (register int j = 0 ; j <= k ; j ++) 
        {			
            while (!q.empty() and j - q.front() > fam[i-1].F) q.pop_front(); //要买的大于上一个店的存储 
            if (dp[i-1][j] != 0x3f3f3f3f)
            {
                while (!q.empty() and dp[i-1][q.back()] - fam[i-1].w * q.back() >= dp[i-1][j] - fam[i-1].w * j) q.pop_back();
                q.push_back(j);
            }
            int o = q.front();
            if (!q.empty()) dp[i][j] = dp[i-1][o] - fam[i-1].w * o + (fam[i].pos - fam[i-1].pos) * j * j + fam[i-1].w * j;
        }
    }
    
    cout << dp[n][k] << endl;
    return 0;
    
}


```

---

## 作者：Dfkuaid (赞：5)

# #1.0 朴素算法

首先，我们不难发现，如果我们要花费最小，必然是直接从最远处一路直行回到家，中间没有折返。由于输入的数据是乱序，所以我们首先需要 ```sort()``` 对数据进行排序

我们可以这样设计状态：

$f_{i,j}$ 表示**第 $i$ 个商店前购买了 $j$ 件商品所花的最小代价** 

设 $w_i$ 表示第 $i-1$ 个商店到第 $i$ 个商店的距离，$sum_i$ 表示前 $i$ 家店可提供的商品总数，不难写出状态转移方程：
$$
f_{i,j}=\min_{j-l_i\leq p\leq j}\{f_{i-1,p}+w_i\times j^2+c_i\times(j-p)\}
$$
我们先来看 $p$ 范围的约束条件，$l_i$ 表示商店 $i$ 的商品数量上限，显然应有 $j-p<l_i$，且根据状态的假设，应有 $p\leq sum_{i-2}$，所以其实范围限定应该是 $j-li\leq p\leq \min\{j,sum_{i-2}\}.$

而且要注意，因为状态的设计是*第 $i$ 个商店**前***，所以要求到 $f_{n+1,k}$

不难写出代码：

``` cpp
/*80pts*/
const int N = 510;
const int INF = 0x3fffffff;

struct S{
    int x,f,c;
    int w,sum;
};
S s[N];

int k,e,n;
int f[N][10010];

int cmp(const S &a,const S &b){
    return a.x < b.x;
}

int main(){
    scanf("%d%d%d",&k,&e,&n);
    for (int i = 1;i <= n;i ++)
      scanf("%d%d%d",&s[i].x,&s[i].f,&s[i].c);
    sort(s + 1,s + n + 1,cmp);
    for (int i = 1;i <= n;i ++){
        s[i].w = s[i].x - s[i - 1].x;
        s[i].sum = s[i - 1].sum + s[i].f;
    }
    s[n + 1].w = e - s[n].x;
    mset(f,0x3f); //memset
    for (int i = 1;i <= n;i ++)
      f[i][0] = 0;
    for (int i = 2;i <= n + 1;i ++)
      for (int j = 1;j <= s[i - 1].sum && j <= k;j ++)
        for (int p = 0;p <= s[i - 2].sum && p <= j;p ++){
            if (j - p > s[i - 1].f) continue; //这里可以直接写在循环里
            f[i][j] = min(f[i][j],f[i - 1][p] + s[i].w * j * j + s[i - 1].c * (j - p));
        }
    cout << f[n + 1][k];
    return 0;
}
```

该算法的时间复杂度大约为 $O(nk^2)$，不能接受

# #2.0 优化

## #2.1 简单分析

先从状态转移方程下手，当我们研究最内层循环 $p$ 时，$i,j$ 可以看作一个定值，所以有：
$$
\begin{aligned}
f_{i,j}&=\min_{j-l_i\leq p\leq j}\{f_{i-1,p}+w_i\times j^2+c_i\times(j-p)\}\\
&=\min_{j-l_i\leq p\leq j}\{f_{i-1,p}+w_i\times j^2+c_i\times j - c_i\times p\}\\
&=\min_{j-l_i\leq p\leq j}\{f_{i-1,p}-c_i\times p\}+w_i\times j^2+c_i\times j\\
\end{aligned}
$$
显然，我们需要的最优决策必然是当前 $p$ 的取值范围内 $f_{i-1,p}-c_i\times p$ 最小者。

再来看 $p$ 取值范围的变化：当 $j$ 增加一时，$p$ 范围的上下界皆增加一，有大量的重复。

综合以上两点，考虑能否使用**单调队列**优化

- 需要 $f_{i-1,p}-c_i\times p$ 最小者，所以应维护单调队列中 $f_{i-1,p}-c_i\times p$ **单调增加**
- 决策 $p$ 的范围单调上升，所以也应维护单调队列中 $p$ **单调增加**

显然以上两点中变量仅有 $p$，所以队列中仅需存储 $p$ 的信息。

单调队列优化，无非是以下三个步骤：

- 检查队头元素是否还在范围内
- 更新 $f_{i,j}$
- 将新决策加入队列，同时维护队列单调性
  - 因为 $p$ 的取值范围是闭区间 $[j-l_i,j]$ 所以每次加入的新决策应该是 $j+1$，且循环应从 $0$ 开始
  - 还记得我们上面说过应有 $p\leq sum_{i-2}$ 吗？所以如果 $j+1>sum_{i-2}$，该决策必然不能成立，可直接放弃

## #2.2 码代码

``` cpp
const int N = 510;
const int INF = 0x3fffffff;

struct S{
    ll x,f,c;
    ll w,sum;
};
S s[N];

int k,e,n;
ll f[N][10010];
int q[10010],frt,tal= - 1;

int cmp(const S &a,const S &b){
    return a.x < b.x;
}

int main(){
    scanf("%d%d%d",&k,&e,&n);
    for (int i = 1;i <= n;i ++)
      scanf("%lld%lld%lld",&s[i].x,&s[i].f,&s[i].c);
    sort(s + 1,s + n + 1,cmp);
    for (int i = 1;i <= n;i ++){
        s[i].w = s[i].x - s[i - 1].x;
        s[i].sum = s[i - 1].sum + s[i].f;
    }
    s[n + 1].w = e - s[n].x;
    mset(f,0x3f); //memset
    for (int i = 1;i <= n;i ++)
      f[i][0] = 0; //记得初始化
    for (int i = 2;i <= n + 1;i ++){
        frt = 0,tal = -1;
        q[++ tal] = 0; //第一次选择显然有 p=0 的选择
        for (int j = 0;j <= s[i - 1].sum && j <= k;j ++){
            while (frt <= tal && j - q[frt] > s[i - 1].f)
              frt ++; //删队头
            f[i][j] = f[i - 1][q[frt]] - s[i - 1].c * q[frt] + s[i - 1].c * j + s[i].w * j * j;
            if (j + 1 > s[i - 2].sum) continue;
            while (frt <= tal && f[i - 1][j + 1] - s[i - 1].c * (j + 1) <= f[i - 1][q[tal]] - s[i - 1].c * q[tal])
              tal --; //去队尾
            q[++ tal] = j + 1; //新决策
        }
    }
    cout << f[n + 1][k];
    return 0;
}
```

## #2.3 几个注意点

1. ``` f[i][j] = f[i - 1][q[frt]] - s[i - 1].c * q[frt] + s[i - 1].c * j + s[i].w * j * j;```

因为数据范围，上面这句代码中，```c,f,w``` 的类型必须都是 ```long long```，不然运算会炸 [惨痛教训](https://www.luogu.com.cn/record/list?pid=P4544&user=162191)

2. ```cout << f[n + 1][k];```

要输出什么？

3. 记得初始化，一定！！！

# End

希望能给你带来收获.

---

## 作者：ariyy (赞：4)

~~一般的一维背包都是可以用一维数组打的~~

首先将商店按照距离的顺序排序 在每一个商店我们都可以选择买或者不买，让我们很容易想到多重背包问题（

设dp[i]表示现在装了i吨饲料的最小花费，那我们可以由背包问题轻松的得到dp式 $dp[j]=min(dp[j]+j*j*(b[i].x-b[i-1].x),dp[j-b[i].k]+(j-b[i].k)*(j-b[i].k)*(b[i].x-b[i-1].x)+b[i].v);$

其中b[i].x表示商店的位置，v表示饲料价格，考虑到n比较大，用二进制优化就好啦

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
inline int read()
{
	char ch=getchar();int w=1,s=0;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+ch-48;ch=getchar();}
	return s*w;
}
struct node{
	ll v,k,id,x;
}a[1010],b[10010];
ll e,k,n,cnt;
ll dp[100100];
inline bool cmp(node i,node j){
	return i.x<j.x;
}
int main(){
	k=read(),e=read(),n=read();//注意开 long long
	for(ll i=1;i<=n;i++){
		a[i].x=read(),a[i].k=read(),a[i].v=read();
	}
	sort(a+1,a+1+n,cmp);//排序
	for(ll i=1;i<=n;i++) a[i].id=i,x[i]=a[i].x;
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=a[i].k;j<<=1){
			a[i].k-=j;
			b[++cnt].v=j*a[i].v;
			b[cnt].k=j;
			b[cnt].x=a[i].x;
		}
		if(a[i].k){
			b[++cnt].v=a[i].k*a[i].v;
			b[cnt].k=a[i].k;
			b[cnt].x=a[i].x;
		}
	}//通俗易懂的二进制优化
	for(ll i=1;i<=k;i++) dp[i]=1e18;
	dp[0]=0;
	for(ll i=1;i<=cnt;i++){
		for(ll j=k;j>=b[i].k;j--){
			dp[j]=min(dp[j]+j*j*(b[i].x-b[i-1].x),dp[j-b[i].k]+(j-b[i].k)*(j-b[i].k)*(b[i].x-b[i-1].x)+b[i].v);//明了的dp式
		} 
	}
	cout<<dp[k]+k*k*(e-x[n]);//走第n个商店到终点的距离
} 
```


---

## 作者：Llf0703 (赞：2)

[更好的阅读体验](https://llf0703.com/p/luogu-4544.html)

## 题意

有 $N$ 个商店，每个商店在 $X_i$，有 $F_i$ 个物品，价格为 $C_i$ 元。如果车上有 $P$ 个物品，每单位距离的运输费用为 $P^2$ 。从 $1\rightarrow E$，要求买 $M$ 个物品，求最小花费。

$N,E\le 500 \ , \ X_i\le E$ 。

## 题解

先把 $E$ 看成一个商店，各项属性为 $X_i=E \ , \ F_i=C_i=0$ 。然后把所有商店按 $X$ 排序。

用 $f[i][j]$ 表示到了第 $i$ 个商店，之前买了 $j$ 个物品的最小花费；枚举到 $i-1$ 个商店之前的物品个数 $k$ ，方程式为：

$$f[i][j]=\min_{p\le j} f[i-1][k]+(X_i-X_{i-1})\times j^2 + (j-k)\times C_{i-1}$$

把与 $P$ 有关的项放在一起：

$$f[i][j]=\min_{p\le j} (f[i-1][k]-k\times C_{i-1})+(X_i-X_{i-1})\times j^2 + j\times C_{i-1}$$

很显然是一个单调队列优化DP了。但有些细节需要注意：

1. $f[i-1][j]=inf$ 无法转移
2. 队列可能为空所以计算答案时需要判断
3. **$k$ 可以 $=j$，所以要把 $j$ 入队后再计算答案**（~~我纠结了很久~~）

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

inline ll read()
{
    char ch=getchar(); ll f=1,x=0;
    while (ch<'0' || ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    return f*x;
}

struct node {
    ll x,c,f;
} s[505];
const ll inf=0x3f3f3f3f;
ll n,m,e,f[505][10005],q[10005];

signed main()
{
    m=read(); e=read(); n=read();
    for (ll i=1;i<=n;i++) s[i].x=read(),s[i].f=read(),s[i].c=read();
    s[++n]=(node){e,0,0};
    sort(s+1,s+n+1,[](const node &x,const node &y){ return x.x<y.x; });
    memset(f,0x3f,sizeof(f));
    f[0][0]=0;
    for (ll i=1;i<=n;i++)
    {
        ll l=1,r=1; q[1]=0; f[i][0]=0;
        for (ll j=1;j<=m;j++)
        {
            while (l<=r && j-q[l]>s[i-1].f) l++; //库存不足
            if (f[i-1][j]!=inf)
            {
                while (l<=r && f[i-1][q[r]]-s[i-1].c*q[r]>=f[i-1][j]-s[i-1].c*j) r--;
                q[++r]=j;
            }
            ll k=q[l];
            if (l<=r) f[i][j]=f[i-1][k]+(s[i].x-s[i-1].x)*j*j+s[i-1].c*(j-k); //先入队再更新答案
        }
    }
    return !printf("%lld",f[n][m]);
}
```

---

## 作者：BzhH (赞：1)

看完这到题，很容易想到用背包做，即设状态$f_{i,j}$表示前$i$个商店一共带了$j$吨货的最小花费,只需要先把商店的位置排个序,就可以直接枚举了,那么就可以得到状态转移方程

$\begin{cases} f_{i,j}=f_{i-1,j}+j*j*(X_i-X_{i-1}),u=0\\ f_{i,j}= \underset{0\le j\le k,1\le u\le F_i}{min}(f_{i,j-u}+u*C_i) \end{cases}$

第一层循环枚举当前走到第$i$商店，第二层循环枚举当前一共运了$j$吨货物,第三层循环枚举在当前商店购买$u吨货物$,那么我们就可以$O(n^3)$实现这个算法,很明显是会超时的,所以想办法优化,~~(通过查看标签)~~,很明显可以看到,$f_{i,j}$只跟之前的$f_{i,j-u}$有关,同时每个$u$需满足$u+F_i>=j$,所以可以考虑单调队列来优化,那么时间复杂度就会降为$O(n^2)$,具体细节看代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;

ll dp[505][10005], q[10005], temp[10005];//数据范围最大会爆int,所以要开long long
int front, tail;//队头,队尾
struct sta
{
    int x, f, c;
    bool operator < (const sta a) const 
    {
        return x < a.x;
    }
} shop[505];//存的每一个商店

int main()
{
    int k, e, n;
    scanf("%d%d%d", &k, &e, &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &shop[i].x, &shop[i].f, &shop[i].c);
    sort(shop + 1, shop + 1 + n);//按坐标位置排序
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;//初始状态
    for (int i = 1; i <= n; i++)
    {
        front = 0, tail = -1;
        for (int j = 0; j <= k; j++)
            temp[j] = dp[i][j] = dp[i - 1][j] + j * j * (shop[i].x - shop[i - 1].x);//注意到这里为什么需要重新开个数组,因为每次的$dp_{i,j}$是由之前更新来的,所以如果这次更新了就会影响后面的状态,所以就需要重新开个数组存一下,避免重复更新
        for (int j = 0; j <= k; j++)
        {
            if (front <= tail && q[front] + shop[i].f < j)
                front++;
            while(front <= tail && temp[q[tail]] - q[tail] * shop[i].c > temp[j] - j * shop[i].c)
                tail--;
            q[++tail] = j;
            if (front <= tail)
                dp[i][j] = min(dp[i][j], temp[q[front]] + (j - q[front]) * shop[i].c);
        }//单调队列优化
    }
    printf("%lld", dp[n][k] + k * k * (e - shop[n].x));
    return 0;
}
```




---

## 作者：Shikita (赞：1)

# 此题是[该题](https://www.luogu.org/problemnew/show/P2616)的升级版，如果没有做过那题的同学建议先去做一下那题

今天这题也是有点难度，主要是关于时间复杂度的事情，我看题解里面大佬们都是开二维数组做的该题，经[某位大佬](https://www.luogu.org/space/show?uid=54186)的讲解，稍稍有了一点领会

只是这题与原先那题的一点不同就是这里选取的货物重量会影响之后的选择，即DP的后效性发生了改变（干扰？），并且根据大佬的分析开二维数组有TLE的风险，并且其中的DP数组有一维是从之前的转移而来，那么可以压缩一维，来节省时间（顺便节省空间）并且根据贪心的思想，我们可以先对坐标进行排序,然后进行处理，又因为我们省略了一维，可以用单调队列维护一下之前的最值，这样可以压缩时间。


我们的状态转移方程：
dp[j]=min(dp[k]+k^2×a[i].x-k×a[i].c)+  j×a[i].c-j^2×a[i].x  
max(0,j-a[i].f)<=k<=j
就是把原先暴力的方程拆分开来成为两段，第一段是在到j这个店之前的花费，第二段是转移，之前那家店的状态转移到当前商店，并且限制循环上限，第一段可以用单调队列进行维护（即之前走过的最短的路）

## 代码
```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
typedef long long llx;
inline llx read()
{
    llx x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9'){if(c=='-')flag=1;   c=getchar();}
    while(c>='0'&&c<='9'){x=(x+(x<<2)<<1)+c-'0';c=getchar();}
    return flag?-x:x;
}
struct node
{
    llx x,f,c;
    bool operator < (const node&T) const
	{
        return T.x>x;
    }//重定义符号以便排序 
}a[505];
llx K,E,n,head,tail;
llx dp[100050];
pair<llx,llx> q[100050];
int main()
{
	K=read(),E=read(),n=read();
	for(llx i=1;i<=n;++i)   
    a[i].x=read(),a[i].f=read(),a[i].c=read();
	sort(a+1,a+1+n);
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for(llx i=1;i<=n;++i)
	{
		llx tmp;
		llx head=1,tail=0;//据说用数组手动模拟队列可以快一点哦 
		for(llx k=K;k>=max(0ll,K-a[i].f);k--)
		{
			tmp=dp[k]+k*k*a[i].x-k*a[i].c;
			while (head<=tail&&q[tail].first>=tmp) tail--;
            q[++tail]=make_pair(tmp,k);//单调队列维护最值 
		}
	    for(llx j=K;j>=0;--j)
	   {
	      if (j-a[i].f>=0)
	      {
            int k=j-a[i].f;
            tmp=dp[k]+k*k*a[i].x-k*a[i].c;
            while (head<=tail&&q[tail].first>=tmp) tail--;
            q[++tail]=make_pair(tmp,k);
        }
        while(head<=tail&&q[head].second>j) head++; 
        dp[j]=min(dp[j],q[head].first-j*j*a[i].x+j*a[i].c);
	    }
    }
	llx ans=dp[K]+K*K*E;//到家 
	cout<<ans<<endl;
}
```

你们可以简单理解为我每一次都是回到原点再到当前这个点，也许这样可以便于理解（~~我不敢保证这样好理解~~毕竟大佬当场讲解的确是这样比较方便理解）

至于为什么 typedef llx，是为了致敬[这位大佬](https://www.luogu.org/space/show?uid=9290)
以上
欢迎指教

---

## 作者：fanypcd (赞：0)

不错的一道单调队列优化 dp 的练习题。

~~最开始我看错题了，以为他家可以在商店中间，然后自闭了半个小时~~。

易于设置状态 $f_{i,j}$ 表示当前到了第 i 个商店的位置，且现在携带了 j 吨饲料所需要的最小代价（我们将起点和终点也视为商店，库存为 0）。

朴素的转移方程很好想：

$f_{i,j}=\min \limits_{k + F_i \geq j}(f_{i - 1,k}+k^2 \times (X_i - X_{i - 1}) + (j - k) \times C_i)$

即枚举到当前的商店为止的携带数量，和到上个商店位置的携带数量，两者之差即为当前商店的购买数量，注意不能超过库存限制。复杂度 $O(nK^2)$。

发现上式中枚举的 j 递增时，对应的 k 的取值也是一个区间（会比原来增减部分），可以用单调队列来维护所有符合条件的 $f_{i - 1,k}+k^2 \times (X_i - X_{i - 1}) + (j - k) \times C_i$ 的最小值。

这样每次 j 增加的时候，先在队首弹出‘过期’的元素（当前的商店全部买了还是不够，即 $k+F_i < j$）。

然后将到上一个商店为止携带 j 个的状态加入队列中并去除队尾的冗余元素（所有转移代价不低于携带 j 个的状态的元素）。

分析一下，每个元素至多入队出队一次，复杂度 $O(K)$。

所以总复杂度优化到 $O(nK)$。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
#define inf 0x3f3f3f3f3f3f3f3f
#define N 505
#define V 10005
int K, E, n;
struct shop
{
	int pos, res, cost;
};
bool cmp(const shop &aa, const shop &bb)
{
	return aa.pos < bb.pos;
}
shop a[N];
deque<int> q;
int f[N][V];
signed main()
{
	read(K), read(E), read(n);
	for(int i = 1; i <= n; i++)
	{
		read(a[i].pos), read(a[i].res), read(a[i].cost);
	}
	a[++n] = (shop){E, 0, 0};
	sort(a + 1, a + n + 1, cmp);
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for(int i = 1; i <= n; i++)
	{
		q.clear();
		q.push_back(0);
		f[i][0] = 0;
		for(int j = 1; j <= K; j++)
		{
			while(!q.empty() && q.front() + a[i].res < j)
			{
				q.pop_front();
			}
			while(!q.empty() && f[i - 1][q.back()] + (a[i].pos - a[i - 1].pos) * q.back() * q.back() + (j - q.back()) * a[i].cost >= f[i - 1][j] + (a[i].pos - a[i - 1].pos) * j * j)
			{
				q.pop_back();
			}
			q.push_back(j);
			f[i][j] = min(f[i][j], f[i - 1][q.front()] + (a[i].pos - a[i - 1].pos) * q.front() * q.front() + (j - q.front()) * a[i].cost);
		}
	}
	printf("%lld", f[n][K]);
	return 0;
}
```

---

## 作者：wtyqwq (赞：0)

- [P4544 Buying Feed](https://www.luogu.com.cn/problem/P4544) 这一看就知道是 DP 的题目，先考虑暴力 DP 的做法。先把商店按照位置排序，以便按顺序进行线性 DP。令 $f(i,j)$ 表示前 $i$ 家商店共购买 $j$ 吨饲料（不考虑 $i+1$ 之后的费用）的最少花费。状态转移方程为：

  $$f(i,j)=\min_{0\le k\le \min\{j,F_i\}} \{f(i-1,j-k)+C_i\times k+(j-k)^2\times (X_i-X_{i-1})\}$$
  
  其中 $k$ 表示再第 $i$ 家商店购买的吨数。这样做时间复杂度为 $O(K^2\times N)$。

```cpp
memset(f, 0x3F, sizeof(f));
for (int i = 0; i <= n; ++i) f[i][0] = 0;
for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= t; ++j)
		for (int k = 0; k <= min(j, a[i].R); ++k) f[i][j] = min(f[i][j], f[i - 1][j - k] + (LL)a[i].C * k + (LL)(j - k) * (j - k) * (a[i].loc - a[i - 1].loc));
```

- 我们发现 $i$ 这一维可以直接滚掉（没多大用处）：

```cpp
memset(f, 0x3F, sizeof(f)), f[0] = 0;
for (int i = 1; i <= n; ++i) {
	for (int j = t; j >= 1; --j) {
		LL cnt = INF;
		for (int k = 0; k <= min(j, a[i].R); ++k) cnt = min(cnt, f[j - k] + (LL)a[i].C * k + (LL)(j - k) * (j - k) * (a[i].loc - a[i - 1].loc));
		f[j] = cnt;
	}
}
```
- 然后考虑优化。首先把状态转移方程变形：

  $$f(i,j)=\min_{j-\min\{j,F_i\}\le k\le j}\{f(i-1,k)+C_i\times (j-k)+k^2\times (X_i-X_{i-1})\}$$
  
  我们把 $k$ 的含义变为了 $1\sim i-1$ 购买的吨数。这样，含有状态变量 $j$ 的项和含有决策变量 $k$ 的项就分开了。然后把 $C_i\times (j-k)$ 拆开就可以了。然后就可以愉快地写单调队列啦。
  
```cpp
#include <bits/stdc++.h>
#define LL long long
#define N (1 << 9)
#define T 10005
using namespace std;
struct rec {
	int loc, R, C;
	bool operator < (const rec &b) { return loc < b.loc; }
};
rec a[N];
int n, m, t, q[T], Head, Tail;
LL f[N][T];
inline LL min(LL a, LL b) { return a < b ? a : b; }
inline LL calc(int i, int k) { return f[i - 1][k] - (LL)a[i].C * k + (LL)k * k * (a[i].loc - a[i - 1].loc); }
int main() {
	scanf("%d %d %d", &t, &m, &n);
	for (int i = 1; i <= n; ++i) scanf("%d %d %d", &a[i].loc, &a[i].R, &a[i].C);
	sort(a + 1, a + n + 1);
	memset(f, 0x3F, sizeof(f));
	for (int i = 0; i <= n; ++i) f[i][0] = 0;
	for (int i = 1; i <= n; ++i) {
		q[Head = Tail = 1] = 0;
		for (int j = 1; j <= t; ++j) {
			while (Head <= Tail && j - min(j, a[i].R) > q[Head]) ++Head;
			while (Head <= Tail && calc(i, q[Tail]) >= calc(i, j)) --Tail;
			q[++Tail] = j;	
			f[i][j] = calc(i, q[Head]) + (LL)a[i].C * j;
		}
	}
	printf("%lld\n", f[n][t] + (LL)(m - a[n].loc) * t * t);
	return 0;
}
```


---

## 作者：hzoi_zxb (赞：0)

### part 1 暴力
不难发现有一个 $\mathcal O(K^2n)$ 的基础 dp：

$$f_{i,j+l}=\min(f_{i,j+l},f_{i-1,j}+(x_i-x_{i-1})*j*j+c_i*l)$$

这其中 f 代表在第 i 个点已经买了 j+l 个，其中当前第 i 个点买了 l 个，前 i-1 个点买了 j 个的最小价值。

这样的话可以水到 $90pts$，但是如果是联赛的话应该没有这么高的暴力分。

code
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 10005
using namespace std;
int E,K,f[N],n,c[N],x[N],dp[502][N],sum[N];
struct mm
{int c,x,f;}p[N];
namespace AYX
{	inline bool cmp(mm i,mm j){return i.x<j.x;}	
	inline short main()
	{	scanf("%lld%lld%lld",&K,&E,&n);	
		for(int i=1;i<=n;++i)scanf("%lld%lld%lld",&p[i].x,&p[i].f,&p[i].c);
		memset(dp,0x3f3f3f3f,sizeof(dp));
		dp[1][0]=0;
		sort(p+1,p+1+n,cmp);
		p[n+1].x=E;p[n+1].f=K;
		for(int i=1;i<=n+1;++i)sum[i]=sum[i-1]+p[i].f;
		for(int i=2;i<=n+1;++i)
		for(int j=0;j<=min(K,sum[i-1]);++j)
		for(int l=0;l<=p[i-1].f;++l)
		{	if(l+j>K)break;
			dp[i][j+l]=min(dp[i][j+l],dp[i-1][j]+p[i-1].c*l+(j+l)*(j+l)*(p[i].x-p[i-1].x));
		}
		printf("%lld\n",dp[n+1][K]);
		return 0;
	}
}
signed main()
{return AYX::main();
}
```
### part 2 单调队列优化 dp

对式子进行转换，我们能够得到：
	
$$f_{i,k}=\min(f_{i,j},f_{i-1,j}+(x_i-x_{i-1})*j*j-c_i*j)+c_i*k$$

这样 $c_i\times j$ 会变成一个常数，式子只和 i  和  j  有关。

采用单调队列使复杂度降到 $\mathcal O(Kn)$ 稳稳通过。

当然还可以用二进制优化背包来降复杂度，只不过不如单调队列快。

code
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 10005
using namespace std;
int E,K,f[N],n,c[N],x[N],dp[502][N],sum[N],dui[N],head,tail;
struct mm
{int c,x,f;}p[N];
namespace AYX
{	inline bool cmp(mm i,mm j){return i.x<j.x;}	
	inline int calc(int i,int j)
	{return dp[i-1][j]+(p[i].x-p[i-1].x)*j*j-j*p[i].c;}
	inline short main()
	{	scanf("%lld%lld%lld",&K,&E,&n);	
		for(int i=1;i<=n;++i)scanf("%lld%lld%lld",&p[i].x,&p[i].f,&p[i].c);
		memset(dp,0x3f3f3f3f,sizeof(dp));
		dp[0][0]=0;
		sort(p+1,p+1+n,cmp);
		for(int i=1;i<=n;++i)
		{	head=1;tail=0;
			for(int j=0;j<=K;++j)
			{	int val=calc(i,j);
				while(head<=tail and calc(i,dui[tail])>val)tail--;
				while(head<=tail and j-p[i].f>dui[head])++head;
				dui[++tail]=j;
				dp[i][j]=calc(i,dui[head])+p[i].c*j;
			}
		}
		printf("%lld\n",dp[n][K]+(E-p[n].x)*K*K);
		return 0;
	}
}
signed main()
{return AYX::main();
}
```

   
   
   
   
   
   
   
   

---

## 作者：ListenSnow (赞：0)

单调队列优化 $DP$ 的好题。
## 题意

$FJ$ 要从 $N$ 个商店中购买 $K$ 吨饲料。设某时刻已经买了 $X$ 吨饲料，行驶一公里的花费为 $X^2$ 。现在 $FJ$ 从 $0$ 这个位置出发，最终要走到 $E$ 这个位置。给出每一家商店的位置、饲料的库存以及饲料的单价，求最少花费。

## 思路

首先考虑朴素的状态。

设 $f[i][j]$ 表示到达第 $i$ 个商店时（**还没有**在第 $i$ 个商店买饲料），已经买了 $j$ 吨饲料的最小花费。可以得出状态转移方程：

$f[i][j]=min(f[i-1][k]+(j-k)*c[i-1]+(x[i]-x[i-1])*j*j)$。

其中 $c[i]$ 表示第 $i$ 家商店的售价，$x[i]$ 表示第 $i$ 家商店的位置。

时间复杂度为 $O(nk^2)$。于是需要考虑单调队列优化。

将原来的转移方程拆开，注意到 $((x[i]-x[i-1])*j*j+j*c[i-1])$ 为常数，可以不需要考虑。而对于剩余的 $(f[i-1][k]-k*c[i-1])$ 部分，就可以使用单调队列优化。由于本题需要求最小值，故需要维护一个**单调递增**的队列，若对单调队列不清楚可以看一看[模板题](https://www.luogu.com.cn/problem/P1886)。

但是不同于简单的模板题，本题还有一个限制，也就是只有当 $f[i-1][j]$ 这种状态**合法**，也就是值不为无穷大的时候，才可以考虑将它加入队列中。

最后，本题的数据范围比较大，别忘了开 **long long** 。

## code：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<deque>
using namespace std;
#define int long long
const int N=521; 
const int M=10010;
const int INF=1e18;
int m,e,n,f[N][M];
struct nlc{
	int x,res,c;
	bool operator <(const nlc &t)const{
		return x<t.x;
	}
}a[N];
deque<int> q;
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
signed main()
{
	//freopen("233.in","r",stdin);
	scanf("%lld%lld%lld",&m,&e,&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld%lld",&a[i].x,&a[i].res,&a[i].c);
	sort(a+1,a+n+1);
	for(int i=0;i<=n+1;i++)
	    for(int j=1;j<=m;j++)
	        f[i][j]=INF;
	a[n+1].x=e;
	for(int i=1;i<=n+1;i++)
	{
		q.clear();
		for(int j=0;j<=m;j++) 
		{
			while(q.size()&&j-q.front()>a[i-1].res) q.pop_front();
			if(f[i-1][j]!=INF)
			{
				while(q.size()&&f[i-1][q.back()]-q.back()*a[i-1].c>=f[i-1][j]-j*a[i-1].c) q.pop_back();
				q.push_back(j);
			}
			if(q.size()) f[i][j]=f[i-1][q.front()]+(j-q.front())*a[i-1].c+(a[i].x-a[i-1].x)*j*j;
		}  
	}
	printf("%lld\n",f[n+1][m]);
	return 0;
} 
```


---


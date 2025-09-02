# [PA 2014] Pakowanie

## 题目描述

你有 $n$ 个物品和 $m$ 个包。物品有重量，且不可被分割；包也有各自的容量。要把所有物品装入包中，至少需要几个包？

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 24$，$1\le m\le 100$，$1\le a_i\le 10^8$，$1\le c_i\le 10^8$。

## 样例 #1

### 输入

```
4 3
4 2 10 3
11 18 9```

### 输出

```
2```

# 题解

## 作者：Kiloio (赞：5)

# 状压DP
第一眼看上去**像背包**，然而不是的。    

### 首先基础贪心策略：  
为了包数最少，肯定是尽量先用大包的。
  
### 状态：  
$f[i]$表示前$i$个物品用的个数，用的二进制表示（毕竟是状压）  

$g[i]$表示所有已用背包（即为$i$集合中表示已经用了的）中剩下的**最大空间**  
$g$存的是剩下的**最大空间**，这样就能满足**上述贪心策略**。  
  
### 方程：  
直接看代码里的方程（**代码中有解释**）吧($i$是集合，$j$是枚举的子集)：  
```
if(i&(1<<(j-1))){//如果j在子集里，没在就不管他		
	op=i^(1<<(j-1));
	//两种情况，每种情况中还会有两种情况 
	
	if(g[op]>=a[j]){//当前物品，不用再开一个包就能装下 。即剩余最大空间满足j物品的大小。 
	
		//如果下一个背包大于或等于（等于还需一个条件，另一条件解释在下），更新。	
		if(f[i]>f[op] || (f[op]==f[i] && g[op]-a[j]>g[i])){//等于情况还加了比较新包装后剩余空间，为合并后的结果（其实也是两种情况），也可以分开写
			f[i]=f[op];
			g[i]=g[op]-a[j];
		}
		
	}
	
	//剩余空间不够，需要再开一个包（ b记录的是包的空间） 
	else if(b[f[op]+1]>=a[j]){//下一个包也要装得下，如果下一个包还装不下就放弃	
				
		//这里道理跟上面一样 
		if(f[i]>f[op]+1 || (f[op]+1==f[i] && b[f[op]+1]-a[j]>g[i])){		
			f[i]=f[op]+1;
			g[i]=b[f[op]+1]-a[j];
		}
		
	}
}
```

  
### 没了。完整代码：  
```
#include<bits/stdc++.h>
using namespace std;
const int N=(1<<25)+5;
int n,m,a[110],b[110],f[N],g[N],maxn;
bool cmp(long long x,long long y){
	return x>y;
}
int main(){
	cin>>n>>m;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	for(int i=1; i<=m; i++){
		scanf("%d",&b[i]);
	}
	maxn=(1<<n)-1;
	sort(b+1,b+1+m,cmp);	
	for(int i=1; i<=maxn; i++){
		f[i]=m+1;
	}	
	int op;
	for(int i=0; i<=maxn; i++){	
		for(int j=1; j<=n; j++){		
			if(i&(1<<(j-1))){			
				op=i^(1<<(j-1));
				if(g[op]>=a[j]){		
					if(f[i]>f[op] || (f[op]==f[i] && g[op]-a[j]>g[i])){				
						f[i]=f[op];
						g[i]=g[op]-a[j];
					}
				}
				else if(b[f[op]+1]>=a[j]){				
					if(f[i]>f[op]+1 || (f[op]+1==f[i] && b[f[op]+1]-a[j]>g[i])){					
						f[i]=f[op]+1;
						g[i]=b[f[op]+1]-a[j];
					}
				}
			}
		}
	}	
	if(f[maxn]>=m+1){	
		cout<<"NIE";
		return 0;
	}	
	cout<<f[maxn];
}
```


---

## 作者：Pop_Agoni (赞：3)

## 1. 题意：

有 $M$ 个有容量限制的背包和 $N$ 个有重量的物品，求最少用多少个背包才能装下所有物品。

---

## 前言：

在看题目时觉得数据很水，又看见给了 $5$ 秒的时限，便想用暴力水过去。~~改了三天也没对，贡献了 $6$ 页的评测。~~

## 20pts：

上来就想到可以将物品状态压缩。

DFS 每个背包，然后枚举状态，同时将之前状态存下判断物品有没有重复。

同时可以贪心发现，先装容量大的背包肯定没错。（因为如果一个物品小容量的背包能装，那么大容量的背包肯定也能装。）

## 45pts：

加个最优值判断即判断如果当前没装完所有物品的答案已经大于我之前算出来的答案了，那么放弃此方案。

## 85pts:

#### 优化 1

不难发现每个背包所枚举的状态其实是相同的，所以可以实现将枚举的状态的总重量算出。

然后我们又能发现我们所装的重量肯定小于从能装的最大值（~~这是一句废话~~）。

所以我们可以将每个状态所对应的重量算出后进行排序，然后用背包的重量进行二分，这样所枚举的重量都是合法的。

#### 优化 2

我们可以算出选完这个状态中的物品之后剩下的物品重量的最小值，如果当前这个背包剩余的重量大于此最小值即还能装下，那么这个方案肯定不是最优解。

## 95pts:

这应该是极限了，剩一个点卡不过去，不过好像能结合其他思路的暴力或者随机化卡过去。

#### 优化 1

每个背包的重量都是固定的不会变化，所以可以直接预处理出二分值。

#### 优化 2

对于每个选取完的状态之后剩余物品的最小值都是固定的，预处理。

#### 优化 3

这是一个玄学优化，但是这个优化能大幅提高分数，只不过很玄学，有时也不会增长太多分数，甚至会掉分，所以在比赛或平时打题时很少会使用。

是传说中的卡时限（我也不知道叫什么）

具体来说就是在程序开始时记录时间，并在跑暴力时如果发现时限逼近或快超过运行要求时限时，直接输出运行至当时所求出的答案。

~~赌在规定时限跑出来的答案就是要求答案。~~

它不保证正确性，但保证了时限要求。

```
#include<bits/stdc++.h>
#define ll unsigned int
using namespace std;
ll n,m;
ll a[35],c[105],ans=101,t[105],cnt,l,r,mid,sum,minn,pot=1,lwq,x,p,gf,spring[105];
long M;
bool cmp(ll l,ll r){return l>r;}
struct node{ll x,id;}b[20000005];
ll flag[20000005];
bool Cmp(node l,node r){return l.x<r.x;}
inline ll read(){
	ll x=0,f=1;
    // char ch=getchar();
	char ch=getchar_unlocked();
	while(!isdigit(ch)){
		if(ch=='-') f=-1;
        // ch=getchar();
		ch=getchar_unlocked();
	}
	while (isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar_unlocked();
        // ch=getchar();
	}
	return x*f;
}
inline void write(ll x){
	if (x<0) putchar('-'), x = -x;
	if (x>9) write(x / 10);
	putchar(x%10 +'0');
}//快读快写
ll N;
inline void dfs(){
    if(p>=N){
        ans=min(x,ans);
        return;
    }
    if(x>20||x>m) return;
    if(x+M/c[x]>=ans) return;//最优值比较
    if(clock()-lwq>4993235){//超出运行时限直接输出
        if(ans==101) printf("NIE");
        else write(ans-1);
        exit(0);  
    }
    ll df=p,spr;
    for(register ll i=spring[x];i>=1;i--){
        spr=p|b[i].id;
        if((b[i].id&p)) {continue;}//判断物品是否重复选择
        if(a[flag[spr]]+b[i].x<=c[x]&&flag[spr]<=n){break;}//判断还能不能装下其他物品，如果不能，那么更小的方案肯定也不行
        M-=b[i].x,p=spr,x++;
        dfs();
        M+=b[i].x,x--,p=df;
    }
    return;
}
int main(){
    srand(time(0));
    n=read(),m=read();
    N=(1<<n)-1;
    for(register int i=1;i<=n;i++) a[i]=read(),M+=a[i];
    for(register int i=1;i<=m;i++) c[i]=read();
    lwq=clock();
    sort(a+1,a+n+1),reverse(a+1,a+n+1);
    pot=1,a[n+1]=1e7;
    for(register int i=0;i<(1<<n);i++){
        sum=0;
        for(int j=1;j<=n;j++) if((i>>(j-1))&1) sum+=a[j];
        b[++cnt].x=sum,b[cnt].id=i;
    }//状态预处理
    sort(b+1,b+cnt+1,Cmp);
    sort(c+1,c+m+1,cmp);
    x=1,p=0;
    for(register int i=0;i<(1<<n);i++){
        flag[i]=n+1;
        for(int j=n;j>=1;j--){
            if(!((i>>(j-1))&1)){
                flag[i]=j;
                break;
            }
        }
    }//最小值预处理
    for(register int i=1;i<=m;i++){
        l=1,r=cnt,gf=0;
        while(l<=r){
            mid=(l+r)>>1;
            if(b[mid].x<=c[i]) l=mid+1,gf=mid;
            else r=mid-1;
        }
        spring[i]=gf;
    }//二分预处理
    dfs();
    if(ans==101) printf("NIE");
    else write(ans-1);
    system("pause");
    return 0;
}
```

~~马蜂很丑，勿喷~~

## 正解

经过了几天的折磨后，我还是老老实实的打起了正解。
通过暴力我们不难看出这是一个状压的动态规划。

而且我们还是能用暴力所找到的贪心策略：优先装大包，但是我们这里是指已用（已枚举）剩余重量最大的包。

设 $f_{i}$ 表示物品选取状态为 $i$ 所用的背包个数（肯定是最优的）。

$g_{i}$ 表示物品选取状态为 $i$ 中所用背包中剩余重量最大的**剩余重量**

---

那么就有两种转移方程，就是需要新开一个背包和还可以用原有背包继续装。

因为涉及两个数组赋值，~~我不会用 Latex 表示~~，所以直接用代码注释讲。

```
#include<bits/stdc++.h>
#define ll int
using namespace std;
ll n,m;
ll a[105],c[105],t[105],block,f[30000005],g[30000005];
bool cmp(ll l,ll r){
    return l>r;
}
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)){
		if (ch == '-') 
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

inline void write(int x){
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=m;i++) c[i]=read();
    sort(c+1,c+m+1,cmp);//先用大包装
    for(int i=0;i<(1<<n);i++) f[i]=m+1;//初始化
    f[0]=0;
    for(int i=0;i<(1<<n);i++){
        for(int j=1;j<=n;j++){
            if((((i>>(j-1))&1))){
                block=i-(1<<(j-1));
                if(g[block]>=a[j]){//不需要用新的背包。
                    if(f[block]<f[i]||(f[block]==f[i]&&g[i]<g[block]-a[j])) f[i]=f[block],g[i]=g[block]-a[j];//如果用的背包数量小于或者说剩余背包最大重量更大都可以更新。                  
                }
                else{
                    if(c[f[block]+1]>=a[j]){//如果要用新的背包也需要比较，如果说发现下一个背包也装不下，那么没有背包能装下，因为我们对背包的重量进行了排序，后面的背包重量肯定更小。
                        if(f[block]+1<f[i]||(f[block]+1==f[i]&&g[i]<c[f[block]+1]-a[j])) f[i]=f[block]+1,g[i]=c[f[block]+1]-a[j];//与伤者同理，这里的+1正是新用的背包。
                    }
                }
            }
        }
    }
    if(f[(1<<n)-1]>=m+1) printf("NIE");
    else write(f[(1<<n)-1]);
    system("pause");
    return 0;
}
```

完结撒花。

---

## 作者：jockbutt (赞：3)

 ## 前言

背包加强版。

## 思路

一看数据范围 $1\leq n \leq 24 $，就知道这肯定是个状压打牌，但是它时间只给了五秒，那多项式的时间复杂度肯定不能太高。想办法把袋子数量这一维度给优化掉，先贪心一波。

装东西肯定是要挑大袋子先开始装，前面的如果装得下肯定不会用后面的袋子装，在袋子数量相同的时候，应该让剩余空间最大的那个袋子剩余空间更大。

于是我们就可以得出表达式：

设  $  f_i  $  表示装下以二进制表示的物品需要的袋子数量；  
设  $  g_i  $  表示以最少袋子数量装下物品时那些袋子剩下的空间最大的那个。

这样，我们就可以以 $ f $ 为第一关键变量， $ g $ 为第二关键变量，来进行打牌。 


## Code



```cpp
#include <bits/stdc++.h>
using namespace std;
// #define int long long
const int BUFFER_SIZE=1<<21;
char RB[BUFFER_SIZE],*RP=RB,*RT=RB;
#define getchar() RP==RT?(RT=RB+fread(RB,1,BUFFER_SIZE,stdin),RP=RB,*RP++):*RP++;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9')	{if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9')	{x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,m,N;
const int maxn=3e7;
int a[30],c[200],f[maxn],g[maxn];
inline bool cmp(int x,int y)	{return x>y;}
signed main(){
	n=read(),m=read();
	N=(1<<n)-1;
	for(int i=1;i<=n;++i)	a[i]=read();
	for(int i=1;i<=m;++i)	c[i]=read();
	sort(c+1,c+1+m,cmp);
	const int INF=m+1;
	for(int i=1;i<=N;++i)	f[i]=INF;
	for(int i=0;i<=N;++i)
	{
		for(int j=1,k;j<=n;++j)
		{
			if(i&(1<<(j-1)))
			{
				k=i^(1<<(j-1));
				if(g[k]>=a[j])
				{
					if(f[i]>f[k]||(f[i]==f[k]&&g[i]<g[k]-a[j]))	f[i]=f[k],g[i]=g[k]-a[j];
				}
				else	if(c[f[k]+1]>=a[j])
				{
					if(f[i]>f[k]+1||(f[i]==f[k]+1&&c[f[k]+1]-a[j]>g[i]))
						f[i]=f[k]+1,g[i]=c[f[k]+1]-a[j];
				}
			}
		}
	}
	if(f[N]>=INF)	printf("NIE\n");
	else	printf("%d\n",f[N]);
	return 0;
}
```


---

## 作者：Super_Cube (赞：2)

# Solution

注意到 $n\le 24$ 且时限 5s，考虑状压 dp。

先将 $c$ 从大到小排序。设 $dp_{i}$ 表示已选的物品集合为 $i$ 的最小背包数，同时维护 $g_i$ 表示当前状况下剩余背包的容量最大值。每次找一个还未在集合 $i$ 中的物品 $j$ 并入 $i$ 进行转移即可，具体可参考代码。

# Code

```cpp
#include<bits/stdc++.h>
int dp[16777216][2];
int a[24],b[105];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;scanf("%d",&a[i++]));
	for(int i=1;i<=m;scanf("%d",&b[i++]));
	std::stable_sort(b+1,b+m+1,std::greater<int>());
	for(int i=1;i<(1<<n);++i){
		dp[i][0]=101;
		for(int j=0;j<n;++j)
			if(i>>j&1)
				if(dp[i^(1<<j)][1]>=a[j]){
					if((dp[i][0]>dp[i^(1<<j)][0])||(dp[i][0]==dp[i^(1<<j)][0]&&dp[i][1]<dp[i^(1<<j)][1]-a[j]))
						dp[i][0]=dp[i^(1<<j)][0],dp[i][1]=dp[i^(1<<j)][1]-a[j];
				}else if(b[dp[i^(1<<j)][0]+1]>=a[j])
					if((dp[i][0]>dp[i^(1<<j)][0]+1)||(dp[i][0]==dp[i^(1<<j)][0]+1&&dp[i][1]<b[dp[i^(1<<j)][0]+1]-a[j]))
						dp[i][0]=dp[i^(1<<j)][0]+1,dp[i][1]=b[dp[i^(1<<j)][0]+1]-a[j];
	}
	if(dp[(1<<n)-1][0]==101)puts("NIE");
	else printf("%d",dp[(1<<n)-1][0]);
	return 0;
}
```

---

## 作者：MSqwq (赞：2)

很水的一道状压DP  
根据贪心策略可知有限放在空间大的背包里面，所以先对背包进行递减排序  
然后设PD状态  
$f[i]$为前i个物品所用背包个数，这样定状态会发现信息不全，但是不能再加一个维度了，因为$2^{24}$很大，所以考虑再来一个数组记录这个背包所省的空间  
每次转移的时候就看一下是用当前背包还是用新的背包    
### 最后注意一下初始化别太大，不然很容易下标越界  
RE的看一下初始化是不是太大了  
代码如下：
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mm=(1<<25)+10;
const int inf=21474836;
int n,m,a[110],b[110],f[mm],tot,g[mm],qwe;
bool cmp(ll x,ll y)
{
	return x>y;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	
	tot=(1<<n)-1;
	sort(b+1,b+1+m,cmp);
	
	for(int i=1;i<=tot;i++)f[i]=m+1;
	
	for(int i=0;i<=tot;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i&(1<<(j-1)))
			{
				qwe=i^(1<<(j-1));
				if(g[qwe]>=a[j])
				{
					if(f[i]>f[qwe]||(f[i]==f[qwe]&&g[qwe]-a[j]>g[i]))
					{
						f[i]=f[qwe];
						g[i]=g[qwe]-a[j];
					}
				}
				else if(b[f[qwe]+1]>=a[j])
				{
					if(f[i]>f[qwe]+1||(f[i]==f[qwe]+1&&b[f[qwe]+1]-a[j]>g[i]))
					{
						f[i]=f[qwe]+1;
						g[i]=b[f[qwe]+1]-a[j];
					}
				}
			}
		}
	}
	
	if(f[tot]>=m+1)
	{
		cout<<"NIE";
		return 0;
	}
	
	cout<<f[tot];
}
```


---

## 作者：Sparse_Table (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/P5997)

[博客食用更佳？](https://www.cnblogs.com/SparseTable/p/18822864)

这题很多人一眼就以为是背包问题，但发现背包数量太多，容量太大，dp 数组根本开不下 qwq。

于是我们看了一眼数据范围：$n \leq 24$，原来是状压 dp 啊！

1. 贪心：用的包一定是最大的几个，所以 $c_i$ 要从大往小排序。
2. 设计状态：这题状态还是比较好想的，这题显然需要记录最优方法的用了几个包，还剩多少空间，所以 $dp_{i, 0}$ 记录最优状态用了几个包，$dp_{i, 1}$ 记录在最优状态下最后一个包还剩多少空间。
3. 初值：$dp_{0, 0} = 0, dp_{0, 1} = 0, dp_{i, 0} = m + 1(1 \le i < 2 ^ n - 1)$
4. 转移：对于状态 $i$ 和一个值 $0 \le j < n$，判断第 $j$ 个元素是否被选，若未被选，新状态就是 $i \oplus 2 ^ j$。接着看这个包能不能装下，若不能用一个新包，看能不能装下。
5. 答案：$dp_{2 ^ n - 1, 0}$。
6. 注意！dp 初值不要赋无穷大，不然会越界，变成 $95$ 分，详见[这里](https://www.luogu.com.cn/discuss/1045983)。

题解结束了，有疑问或题解有误欢迎私信，感谢大家的观看。

---

## 作者：C_Pos_Princess (赞：1)

# 题解：P5997 [PA2014] Pakowanie

##### 前置：

一开始看这个题的时候想起了[栅栏](https://www.luogu.com.cn/problem/P2329)那个题，但是好像数据范围不太一样？看到24这个范围，直接状压dp啊！

##### 题解：

首先，肯定要枚举每个状态，不多说。
那么如何转移状态呢，这个地方其实我借鉴了一点栅栏那个题的思路，要维护两个数组，一个存储需要的个数，另一个存储当前剩下的。

```cpp
if (g[k] >= a[j]) {
	if (f[i] > f[k] || (f[i] == f[k] && g[i] < g[k] - a[j])) f[i] = f[k], g[i] = g[k] - a[j];
	} 
```


首先，如果说当前状态剩余的位置可以装下这个物品，则如果当前个数更优或者能剩下更多的位置，就直接装下。

```cpp
else if (c[f[k] + 1] >= a[j]) {
	if (f[i] > f[k] + 1 || (f[i] == f[k] + 1 && c[f[k] + 1] - a[j] > g[i]))
		f[i] = f[k] + 1, g[i] = c[f[k] + 1] - a[j];
	}
```


其次，如果当前位置装不下，就开一个新的包，判断即可。


那么问题来了，怎么判断装的顺序是否是最优的？

不需要考虑，因为我们枚举了所有的状态（顺序）。

代码奉上。
```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;

int n, m;
const int N = 30, M = 110;
int a[N], c[M];

bool cmp(int a, int b) {
	return a > b;
}
const int maxx = 3e7 + 10;
int f[maxx];
int g[maxx];
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", &c[i]);
	}
	sort(c + 1, c + 1 + m, cmp);
	int A = (1 << n) - 1;

	for (int i = 1; i <= A; i++) f[i] = m + 1;

	for (int i = 0; i <= A; i++) {
		for (int j = 1, k; j <= n; j++) {
			if (i & (1 << (j - 1))) {
				k = i ^ (1 << (j - 1));
				if (g[k] >= a[j]) {
					if (f[i] > f[k] || (f[i] == f[k] && g[i] < g[k] - a[j])) f[i] = f[k], g[i] = g[k] - a[j];
				} 
				
				
				else if (c[f[k] + 1] >= a[j]) {
					if (f[i] > f[k] + 1 || (f[i] == f[k] + 1 && c[f[k] + 1] - a[j] > g[i]))
						f[i] = f[k] + 1, g[i] = c[f[k] + 1] - a[j];
				}

			}
		}

	}
	if (f[A] >= m + 1) printf("NIE");
	else printf("%d", f[A]);


	return 0;
}
```

---

## 作者：ImNot6Dora (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/P5997)

## 题意
你有 $n$ 个物品和 $m$ 个背包，物品有各自的质量且不可被分割，包也有各自容量。求装完所有物品所需要的最小背包数量。

## 思路
看到背包和物品，我们很容易想到背包问题，但这道题背包容量太大了，根本开不下这么大的数组。于是我们继续观察数据，发现 $n\le24$，而每个物品都只有放了或没放两种情况，意味着总状态数最大为 $2^{24}=16777216$，那么这就是一个**状压 dp** 问题了。

既然确定了总方法，我们就来继续分析题目。首先容易发现一个**贪心**思路：先放满大的背包，再放小的，即需要按照背包容量进行**降序排序**。

然后就要进行状态转移，为了记录答案，我们首先用 $f_k$ 记录放置 $k$ 中的物品需要用到的**背包数量**。依照上面的贪心，我们在大的背包没放满前不能开小的背包，所以还需要用一个$g_k$ 表示在当前状态下，剩余容量**最大**的背包的剩余容量。

接下来思考转移条件。容易发现，对于某个物体，如果当前背包能放下，那么就放进去；如果在目前开的这些背包里剩余容量最大的背包放不下，就必须要新开一个背包，而新开的这个背包如果也放不下，**由于我们是降序排序背包容量**，则这个物品根本放不下，就不需要更新答案。对于能放下的情况，我们依然要进行进一步判断，由于我们希望背包数量尽可能少且背包剩余容量尽可能多，判断条件也呼之欲出：**背包数量变少**或者**剩余背包最大容量变大**的情况可以更新答案。

那么整体思路就有了：先降序排序背包，再依次枚举放哪个物品，依照转移条件更新答案。

这里无解也是很容易判断的。

## 代码
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m;
int a[30],c[110]; 
int f[16777216],g[16777216]; 
bool cmp(int x,int y){
	return x>y;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>c[i];
	for(int i=1;i<(1<<n);i++)f[i]=111;//初始化，我们这里默认了f[0]=0 
	sort(c+1,c+m+1,cmp); //降序排序背包容量 
	for(int i=0;i<(1<<n);i++){ //枚举状态 
		for(int j=1;j<=n;j++){ //枚举放哪个物品 
			if(!((i>>(j-1))&1))continue; //这里是因为我们必须保证在状态i下是放了物品j的 
			int k=i^(1<<(j-1)); //这个式子表示i中去掉j不放的状态 
			if(g[k]>=a[j]){//如果背包容量足够，不用开新的 
				if(f[i]>f[k]||f[i]==f[k]&&g[i]<g[k]-a[j]){//背包数量变少或者剩余背包容量变大 
					f[i]=f[k];//更新答案 
					g[i]=g[k]-a[j];
				}
			}else{//需要开新的背包 
				if(c[f[k]+1]>=a[j]){//这里是判断新的背包能否放下，如同之前分析，如果新的背包也放不下那么这个物体就放不下了 
					if(f[i]>f[k]+1||f[i]==f[k]+1&&g[i]<c[f[k]+1]-a[j]){//这里原理与上面一样，不过由于新开了一个背包，所以要加一 
						f[i]=f[k]+1;//更新答案 
						g[i]=c[f[k]+1]-a[j];
					}
				}
			}
		}
	}
	if(f[(1<<n)-1]==111)cout<<"NIE";
	else cout<<f[(1<<n)-1];
	return 0;
}

```

---

## 作者：GaryH (赞：0)

# $The$ $Solution$ $Of$ $P5997$

我们在读题时，只要看到是求最优解，就应该意识到，可用的算法只有**DP**,**贪心**和**枚举**(从某种程度上来说，搜索也算枚举的一种)。

那么，我们接下来从**数据范围**与**算法正确性**上来确定所采用的算法。

显然，搜索的时间复杂度不低于$2^{100}$，可以直接排除，而贪心不会对整体最优作优先考虑，而仅仅是每次做出当前最优的抉择。此题的要求是最少使用的包数，也就是要求出一个问题的整体最优解，那当前的最优抉择不一定对整体最优解做出了尽可能大的贡献。

那么，我们可以选的算法就只有$DP$了。

然后，再仔细观察题面，我们发现如果仅用单纯的$DP$，状态转移方程可能会过于复杂(比如来一个24维数组什么的），从本质上来说，就是**单纯的DP不方便表示当前的所有状态**。

于是，我们采用的方法就呼之欲出了：~~骗分~~**状压DP**。

我们建立两个数组，$\large lst[S]$和$\large dp[S]$，分别表示当前状态下的背包的最大剩余容量，与当前状态下使用的背包数量的最小值(即最优解)。那么，我们可以得出，状态转移方程是：

### $dp[S]=min(dp[S],min(dp[S$ $eor$ $2^j],dp[S$ $eor$ $2^k]+1)$

其中，$\large eor$ 表示异或符号。

那么代码就显而易见了。

```
#include<bits/stdc++.h>
using namespace std;
const int maxm=24+1;
const int maxn=100000+10;
const int inf=2147483647;
int n,m;
int w[maxn];
int v[maxn];
int dp[1<<maxm];
int lst[1<<maxm];
inline bool cmp(int a,int b){
	return a>b;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%d",&w[i]);
	}
	for(int i=0;i<m;i++){
		scanf("%d",&v[i]);
	}
	sort(v,v+m,cmp);
	int N=(1<<n);
	for(int i=0;i<N;i++){
		dp[i]=inf;
	}
	dp[0]=0;
	for(register int i=0;i<N;i++){
	 for(register int j=0;j<n;j++){
	 if(i&(1<<j))continue;
	 int st=i|(1<<j);
	 if(lst[i]>=w[j]&&(dp[st]>dp[i]||(dp[st]==dp[i]&&(lst[i]-w[j])>lst[st]))){
	 	dp[st]=dp[i];
	 	lst[st]=lst[i]-w[j];
	 }
	 if(dp[i]<m&&v[dp[i]]>=w[j]&&(dp[st]>(dp[i]+1)||(dp[st]==(dp[i]+1)&&(v[dp[i]]-w[j])>lst[st]))){
	 	dp[st]=dp[i]+1;
	 	lst[st]=v[dp[i]]-w[j];
	 }
	}}
	if(dp[N-1]==inf){
		printf("NIE");
		return 0;
	}
	printf("%d",dp[N-1]);
	return 0;
}
```
最后处理一下细节就行。

[AC](https://www.luogu.com.cn/record/43552057)
(目前最优解保持者）



---

## 作者：wsyhb (赞：0)

首先，我们显然会优先选择容量大的包，因此不妨将 $c$ 数组从大到小排序，即令 $c_1 \ge c_2 \ge \cdots \ge c_m$。那么我们可以依次考虑编号为 $1,2,\cdots,m$ 的包。

由于物品重量和背包容量都是 $10^8$ 级别的，无法直接进行背包 DP。但注意到 $n \le 24$，于是考虑状压 DP。

一个直观的想法是设 $f_S$ 表示要装下 $S$ 集合中的物品，所需的最小背包数量（即至少需要编号为 $1,2,\cdots,f_S$ 的包）。每次考虑当前背包要装哪些物品，则 $f_S$ 由 $f_T(T \subset S)$ 转移而来。由于需要枚举子集，时间复杂度 $O(3^n)$。

复杂度过高，考虑优化：注意到我们没有必要把一个包的所有物品一次性加入——我们完全可以一个一个物品的加入。但这样就需要记当前背包的剩余容量，于是再设一个辅助状态 $g_S$，表示要装下 $S$ 集合中的物品，在背包数量最小的前提下，第 $f_S$ 个背包的最大剩余容量。

转移很简单：考虑加入一个物品 $i \notin S$，若 $g_S \ge a_i$，则仍使用第 $f_S$ 个背包；否则若 $c_{f_S+1} \ge a_i$，则使用第 $f_S+1$ 个背包；否则无论如何都装不下物品 $i$（因为 $c$ 单调不增）。转移时，若 $f$ 值相同，需考虑是否更新 $g$ 值。（DP 的初始值：$f_0=g_0=0$）

总时间复杂度 $O(m\log{m}+n \cdot 2^n)$。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=24+5;
const int max_m=100+5;
const int max_S=1<<24|5;
int a[max_n],c[max_m],f[max_S],g[max_S];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
		scanf("%d",a+i);
	for(int i=1;i<=m;++i)
		scanf("%d",c+i);
	sort(c+1,c+m+1,greater<int>());
	int U=(1<<n)-1;
	f[0]=g[0]=0;
	for(int S=1;S<=U;++S)
		f[S]=m+1;
	for(int S=0;S<U;++S)
	{
		if(f[S]>m)
			continue;
		int f_now=f[S],g_now=g[S];
		for(int i=0;i<n;++i)
		{
			if(~S&(1<<i))
			{
				int T=S|(1<<i);
				if(g_now>=a[i])
				{
					if(f_now<f[T]||(f_now==f[T]&&g_now-a[i]>g[T]))
						f[T]=f_now,g[T]=g_now-a[i];
				}
				else if(f_now<m&&c[f_now+1]>=a[i])
				{
					if(f_now+1<f[T]||(f_now+1==f[T]&&c[f_now+1]-a[i]>g[T]))
						f[T]=f_now+1,g[T]=c[f_now+1]-a[i];
				}
			}
		}
	}
	if(f[U]>m)
		puts("NIE");
	else
		printf("%d\n",f[U]); 
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

你有 $n$ 个物品和 $m$ 个包。物品有重量，且不可被分割；包也有各自的容量。要把所有物品装入包中，至少需要几个包？

$1\le n\le 24,1\le m\le 100$。

# 题目分析

首先根据贪心，我们把所有背包按其容量从大到小排列。

令 $dp[i]$ 表示装的物品情况集合为 $i$ 时的最少背包数，$g[i]$ 表示使用最少背包数量时最大的剩余容量。

根据定义，一定有 $dp[0]=0$。

然后我们对于状态 $i$，枚举前一个状态（也就是任意有一位不选择）是否会对 $g$ 和 $dp$ 更优，根据前一个状态向这一个状态更新即可。

最后答案为 $dp[2^n-1]$，亦即 $dp[(11\dots 1111)_2]$。

# 代码

```cpp
//2022/5/19 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : (-x))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if (x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int INF = 0x3f3f3f3f;
const int N = 25,M = 105;
int a[N],b[M],dp[1 << N],g[1 << N];
//dp[i]:装的物品情况集合为 i 时的最少背包数
//g[i]:使用最少背包数量时最大的剩余容量
int n,m;
inline bool cmp(int x,int y) {
	return x > y;
}
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	n = read(),m = read();
	for (register int i = 1;i <= n; ++ i) {
		a[i] = read();
	}
	for (register int i = 1;i <= m; ++ i) {
		b[i] = read();
	}
	std::sort(b + 1,b + m + 1,cmp);
	mst(dp,0x3f);
	dp[0] = 0;
	for (register int i = 1;i < (1 << n); ++ i) {
		for (register int j = 1;j <= n; ++ j) {
			if (i & (1 << (j - 1))) {
				if (g[i ^ (1 << (j - 1))] >= a[j] && (dp[i ^ (1 << (j - 1))] < dp[i] || (dp[i ^ (1 << (j - 1))] == dp[i] && g[i ^ (1 << (j - 1))] - a[j] > g[i]))) {
					dp[i] = dp[i ^ (1 << (j - 1))];
					g[i] = g[i ^ (1 << (j - 1))] - a[j];
				}
				if (dp[i ^ (1 << (j - 1))] <= m - 1 && b[dp[i ^ (1 << (j - 1))] + 1] >= a[j] && (dp[i ^ (1 << (j - 1))] + 1 < dp[i] || (dp[i ^ (1 << (j - 1))] + 1 == dp[i] && b[dp[i ^ (1 << (j - 1))] + 1] - a[j] > g[i]))) {
					dp[i] = dp[i ^ (1 << (j - 1))] + 1;
					g[i] = b[dp[i ^ (1 << (j - 1))] + 1] - a[j];
				}
			}
		}
	}
	if (dp[(1 << n) - 1] == INF) {
		puts("NIE");
	} else {
		printf("%d\n",dp[(1 << n) - 1]);
	}
	
	return 0;
}
```

---

## 作者：随情英 (赞：0)

看到这题题面，很显然会想到背包。
但这题中背包的容量过大，以至于寻常解决方法行不通。
但也给我们一些启发，是否可以使用动规的方法解决。
再看到 $1≤n≤24$ ,状压 $dp$ 无疑了

不难发现，如果有解，答案不会超过 $n$，且一定是优先选择容量最大的背包。

因为每个背包至少装一件物品，且按照一定的顺序装包时，选择数目较少的背包一定更优。
 
对所有背包按照容量从大到小排序。

设已装物品集合为 $s$, $f[i]$ 表示装集合 $i$ 的物品最少背包数， $g[i]$ 表示使用最少背包时最大的剩余容量。转移方程不难得到。

时间复杂度 $O(n^2⋅n)$

## code
```cpp
/*
 * @Author: suiqingying 
 * @Date: 2020-07-19 14:24:30 
 * @Last Modified by:   suiqingying 
 * @Last Modified time: 2020-07-19 14:24:30 
 */
#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <queue>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (isdigit(c))
    {
        x = x * 10 + c - '0', c = getchar();
    }
    return x * f;
}
bool cmp(const int &a, const int &b)
{
    return a > b;
}
int a[25], c[110];
int f[1 << 24], g[1 << 24];
int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= n; ++i)
    {
        a[i] = read();
    }
    for (int i = 1; i <= m; ++i)
    {
        c[i] = read();
    }
    std::sort(c + 1, c + m + 1, cmp);
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int i = 1; i < (1 << n); ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (i & (1 << (j - 1)))
            {
                if (g[i ^ (1 << (j - 1))] >= a[j] && (f[i ^ (1 << (j - 1))] < f[i] || (f[i ^ (1 << (j - 1))] == f[i] && g[i ^ (1 << (j - 1))] - a[j] > g[i])))
                {
                    f[i] = f[i ^ (1 << (j - 1))];
                    g[i] = g[i ^ (1 << (j - 1))] - a[j];
                }
                if (f[i ^ (1 << (j - 1))] < m && c[f[i ^ (1 << (j - 1))] + 1] >= a[j] && (f[i ^ (1 << (j - 1))] + 1 < f[i] || (f[i ^ (1 << (j - 1))] + 1 == f[i] && c[f[i ^ (1 << (j - 1))] + 1] - a[j] > g[i])))
                {
                    f[i] = f[i ^ (1 << (j - 1))] + 1;
                    g[i] = c[f[i ^ (1 << (j - 1))] + 1] - a[j];
                }
            }
        }
    }
    if (f[(1 << n) - 1] == 0x3f3f3f3f)
    {
        puts("NIE");
    }
    else
    {
        printf("%d\n", f[(1 << n) - 1]);
    }
    return 0;
}

```


---


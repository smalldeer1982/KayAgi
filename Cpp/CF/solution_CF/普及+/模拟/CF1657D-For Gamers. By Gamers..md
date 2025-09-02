# For Gamers. By Gamers.

## 题目描述

Monocarp is playing a strategy game. In the game, he recruits a squad to fight monsters. Before each battle, Monocarp has $ C $ coins to spend on his squad.

Before each battle starts, his squad is empty. Monocarp chooses one type of units and recruits no more units of that type than he can recruit with $ C $ coins.

There are $ n $ types of units. Every unit type has three parameters:

- $ c_i $ — the cost of recruiting one unit of the $ i $ -th type;
- $ d_i $ — the damage that one unit of the $ i $ -th type deals in a second;
- $ h_i $ — the amount of health of one unit of the $ i $ -th type.

Monocarp has to face $ m $ monsters. Every monster has two parameters:

- $ D_j $ — the damage that the $ j $ -th monster deals in a second;
- $ H_j $ — the amount of health the $ j $ -th monster has.

Monocarp has to fight only the $ j $ -th monster during the $ j $ -th battle. He wants all his recruited units to stay alive. Both Monocarp's squad and the monster attack continuously (not once per second) and at the same time. Thus, Monocarp wins the battle if and only if his squad kills the monster strictly faster than the monster kills one of his units. The time is compared with no rounding.

For each monster, Monocarp wants to know the minimum amount of coins he has to spend to kill that monster. If this amount is greater than $ C $ , then report that it's impossible to kill that monster.

## 说明/提示

Consider the first monster of the first example.

Monocarp can't recruit one unit of the first type, because it will take both him and the monster $ 0.75 $ seconds to kill each other. He can recruit two units for the cost of $ 6 $ coins and kill the monster in $ 0.375 $ second.

Monocarp can recruit one unit of the second type, because he kills the monster in $ 0.6 $ seconds, and the monster kills him in $ 0.625 $ seconds. The unit is faster. Thus, $ 5 $ coins is enough.

Monocarp will need at least three units of the third type to kill the first monster, that will cost $ 30 $ coins.

Monocarp will spend the least coins if he chooses the second type of units and recruits one unit of that type.

## 样例 #1

### 输入

```
3 10
3 4 6
5 5 5
10 3 4
3
8 3
5 4
10 15```

### 输出

```
5 3 -1```

## 样例 #2

### 输入

```
5 15
14 10 3
9 2 2
10 4 3
7 3 5
4 3 1
6
11 2
1 1
4 7
2 1
1 14
3 3```

### 输出

```
14 4 14 4 7 7```

## 样例 #3

### 输入

```
5 13
13 1 9
6 4 5
12 18 4
9 13 2
5 4 5
2
16 3
6 2```

### 输出

```
12 5```

# 题解

## 作者：pocafup (赞：7)

场上读了二十分钟仍然读不懂 C 的样例，只能写 D 了（

首先观察性质，注意到他有一个常数 $C$ 表示最大能拿到的钱数，这个东西是 $10^6$ 级别的，可以用数组存下，这启发我们可以尝试预处理。

朴素想法应该是对于每个怪兽，暴力枚举每一个兵种尝试需要多少个才能打死。比较直接的方法是直接枚举兵种个数，但这样是 $\mathcal{O}(nmC)$ 的，需要优化。

考虑双方的杀敌所需时间上下手。杀死怪兽需要的时间为 $\dfrac{d}{H}$，士兵被杀死的时间为 $\dfrac{D}{h}$。题目要求在被杀之前杀掉怪兽，因此需要保证不等式：

$
\begin{array}{ll}
\dfrac{D}{h}<\dfrac{d}{H}
\end{array}
$

移项得：

$
\begin{array}{ll}
D\times H< d\times h
\end{array}
$

发现这样就可以只预处理对于每个 cost 能得到的最大 $d\times h$，询问的时候二分求出最小 cost 满足不等式即可。

但是这样做是 $\mathcal{O}({\sum_{i=1}^n} {\dfrac{C}{c_i}} + m\log C)$ 的，最坏能够被卡成 $\mathcal{O}(nC)$仍然可以被卡超时。

考虑单调队列的思想：如果一个士兵的 $d \times h$ 比另一个士兵小，但是他的 cost 比另外的士兵大，那么使用这个士兵必然不优。

因此，我们考虑将士兵按 $d \times h$ 从大到小进行排序，在扫的时候记录一下现在拿到的士兵的最小 cost。易证如果后扫到的士兵 cost 比这个大，那么使用这个士兵必然不是最优解。

由于使用这种方法不会出现重复的 cost，因此复杂度最坏为 $\mathcal{O}{\sum_{i=1}^n} \dfrac{C}{i}$，根据调和级数证明是 $\mathcal{O} (C \log C)$ 级别的。

最后直接二分最小 cost，判断一下是否无解即可。看了前几的代码大多数都用的 set，但个人死都不会用 upper_bound 于是用了 vector。

复杂度 $\mathcal{O}((m+C) \log C)$

```cpp
//namespace

const int MAXN = 1e6+5;
const int MAXM = 5e5+5;
const int mod = 1e9+7;
int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
int n,m,t,l,k,a,b,C,pos[MAXN],ans,dp[MAXN];

struct Node{
  int c,d,h;
  bool operator < (const Node &o) const{
    return d*h>o.d*o.h;
  }//排序: d*h 大在前面
}node[MAXN];
inline int bs(int val){
  int l = 1, r = C;
  while(l!=r){
    int mid = (l+r)>>1;
    if (dp[mid]>val) r = mid;
    else l = mid+1;
  }//直接二分
  return dp[l]>val ? l : -1;
}
signed main(){
  n = read(); C = read();
  For(i,1,n) node[i] = (Node){read(),read(),read()};
  sort(node+1,node+1+n);
  int pre = 1e9;
  For(i,1,n){
    if (node[i].c>=pre) continue;
    pre = node[i].c;
    for (int j=1;j*node[i].c<=C;j++){//这里就是所谓的调和级数了
      dp[j*node[i].c] = chkmax(dp[j*node[i].c],j*node[i].d*node[i].h);
    }
  }
  For(i,1,C) dp[i] = chkmax(dp[i],dp[i-1]);//求个前缀最大
  m = read();
  For(i,1,m){
    a = read(),b = read();
    Write(bs(a*b));
  }
}
```

隐藏了冗长的码头，需要的可以私信。

---

## 作者：Genius_Star (赞：2)

### 题意：

现有 $n$ 种兵种，每种有单位招募代价、攻击力、生命值三个数值。需回答 $m$ 次询问——每次询问给出魔王的攻击、生命，问在以下条件下，击败魔王至少需要花费多少代价？

- 只能选择一种兵种的士兵招募。

- 任意士兵不能在战斗中死亡。

- 魔王与士兵并非回合制战斗，造成伤害是连续的。

### 思路：

任意士兵是不能死亡的，假如你找 $k$ 个士兵前来，魔王只要打败一个你就失败了，所以找 $k$ 个士兵只是单纯的让其攻击力变为原来的 $k$ 倍，生命值是不会有变化的。

我们设攻击力为 $a_i$ 血量为 $b_i$ 的士兵能打过攻击力为 $a_j$ 血量为 $b_j$ 的魔王，并且仅当 $\frac{b_j}{a_i}< \frac{b_i}{a_j}$，我们可以扩展开来，即 $b_j \times a_j < b_i \times a_i$。

所以我们定义一个攻击力为 $a$ 血量为 $b$ 的士兵其能力值为 $a \times b$，只要士兵的能力值大于魔王的能力值，那么就可以战胜魔王。

同时，如果我们要招募 $k$ 个士兵，我们可以将其合并为一个新的士兵，这个士兵的生命值不变，攻击力 $\times k$，相当于它的能力值 $\times k$。

现在我们需要求至少要花多少个金币可以战胜魔王，可以用动态规划求解。

定义 $dp_i$ 为消耗了是花费 $i$ 个金币能达到的最大能力值，状态转移方程为：

$$dp_{i \times j}=\max(dp_{i \times j},dp_i \times j)$$

其中 $i$ 为我们枚举的花费金币数，$j$ 为再次购买 $j$ 组价钱为 $i$ 的在使用 $i$ 金币下能力值最大的士兵（可能是合并处理的），因为 $i \times j \le C$，所以这样计算的时间复杂度为 $O(C \log C)$。

之后，对于每一次询问，在 $dp$ 数组上二分查找第一个大于魔王能力值的点就可以了。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=1000100;
inline ll read(){ 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,k,x,y,z,m,cnt=0;
ll a[N],dp[N];
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		x=read(),y=read(),z=read();
		dp[x]=max(dp[x],y*z);
	}
	for(int i=1;i<=k;i++)
	  for(int j=2;i*j<=k;j++)
	    dp[i*j]=max(dp[i*j],dp[i]*j);
	for(int i=1;i<=k;i++) 
	  dp[i]=max(dp[i],dp[i-1]);
	m=read();
	while(m--){
		x=read(),y=read();
		if(x*y>=dp[k]){
			a[++cnt]=-1;
			continue;
		}
		a[++cnt]=upper_bound(dp+1,dp+k+1,x*y)-(dp);
	}
	for(int i=1;i<=cnt;i++){
		write(a[i]);
		putchar(' ');
	}
	return 0;
}
```


---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 2000}$
---
### 解题思路：

直接考虑题目给出的胜负条件会使得问题不好处理，考虑进行一个简单的转化。题目要求：$\dfrac{H}{d}\le\dfrac{h}{D}$，其中 $H,D$ 表示怪物的相关数据，$h,d$ 表示战士的相关数据。由于 $D,d$ 都不为 $0$，将等式两边乘上 $Dd$，得到 $HD\le hd$，也就是对于一个怪物或者一个战士有一个特定的“属性值”，对战的时候直接比较这个属性值即可。

由于钱数并不是很多，考虑对于每一种钱数预处理出使用这种钱数能达到的最大属性值，然后对于每一个询问直接找出需要的钱数就行了。

然后具体考虑如何处理。由于每一次只能存在一种战士，直接枚举所有的战士，枚举倍数即可。注意直接做的话可能会被钱数全为 $1$ 卡掉，可以考虑在每一种钱数中只考虑属性最高的战士进行枚举。

这样做的复杂度是 $O(n\log C)$ 的，可以接受。

---
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
struct str{
	int c,d,h,v,id,ans;
	bool operator <(str a){
		if(c==a.c)return v>a.v;
		return c<a.c;
	}
}x[300005],M[300005];
bool cmd(str a,str b){
	return a.id<b.id;
}
int n,m,C,f[1000006],p;
signed main(){
	scanf("%lld%lld",&n,&C);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&x[i].c,&x[i].d,&x[i].h);
		x[i].v=x[i].d*x[i].h;
	}
	sort(x+1,x+n+1);
	for(int i=1;i<=n;i++)
	if(x[i].c!=x[i-1].c)
	for(int j=x[i].c,t=x[i].v;j<=C;j+=x[i].c,t+=x[i].v)
	f[j]=max(f[j],t);
	scanf("%lld",&m);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&M[i].d,&M[i].h);
		M[i].ans=-1;
		M[i].v=M[i].d*M[i].h;
		M[i].id=i;
	}
	sort(M+1,M+m+1);
	p=m;
	for(int i=1;i<=C;i++){
		while(M[p].v<f[i]&&p>=1){
			M[p].ans=i;
			p--;
		}
	}
	sort(M+1,M+m+1,cmd);
	for(int i=1;i<=m;i++){
		printf("%lld ",M[i].ans);
	}
	return 0;
}
/*
5 5
1 1 1
1 2 2
1 3 3
1 1100 1100
1 9987 123
3
100 100
98 98
100000 10000
*/
```


---

## 作者：youdu666 (赞：0)

~~好久没发题解辣！~~

简单转化对战的式子，可得对战双方的生命值与攻击力的乘积大者即为该次对战的胜利者。

于是对士兵进行预处理，以价格为第一关键字、战斗力（即攻击力乘以生命值，下同）为第二关键字排序，对于价格相同的士兵显然购买战斗力高者更优，故在当前价格与上次更新价格相同时跳过本次循环（价格相同时已按战斗力排序）来进行剪枝。在第一次遇到一个价格时更新该价格及其倍数（买多个士兵）能买到的最大战斗力。

于是在询问时便可以对战斗力进行二分搜索。

在实现上，为了保证单调性，可以用前面的较大值来更新后面的较小值（具体见代码）。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(void)
{
    int x=0,y=1;
    char c=getchar();
    while(c>'9'||c<'0')
    {
        if(c=='-')
            y=-1;
        c=getchar();
    }
    while(c<='9'&&c>='0')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x*y;
}
const int N=3e5+5,M=1e6+5;
int n,m;
struct army{
    int m,vs;
}a[N];
int ok[M];
bool cmp(army a,army b)
{
    return a.m==b.m?a.vs>b.vs:a.m<b.m;
}
int x,ip;
signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
        a[i]=(army){read(),read()*read()};
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        if(i>1&&a[i].m==a[i-1].m) continue;
        for(int j=a[i].m;j<=m;j+=a[i].m)
            ok[j]=max(ok[j],j/a[i].m*a[i].vs);
    }
    int mx=ok[1];
    for(int i=2;i<=m;i++)
    {
        if(ok[i]>mx) mx=ok[i];
        else ok[i]=mx;
    }
    int q=read();
    while(q--)
    {
        x=read()*read(),ip=upper_bound(ok+1,ok+m+1,x)-ok;
        printf("%lld ",ip>m?-1:ip);
    }
}
```


---

## 作者：GaryH (赞：0)

## CF1657D 题解
~~`whk` 人回来混一个社贡分~~

考虑如何计算答案，记 $f(X,i)=\max\limits_i(\lfloor\frac{X}{c_i}\rfloor V_i)$，则答案形如 $\max(X\space{\large \mid}f(X,i)>Q_j)$ 的形式，

其中 $V_i=d_ih_i,Q_i=H_iD_i$，则我们对所有 $X\in[1,C]$ 求 $R_X=\max\limits_i(R_{X-1},f(X,i))$，

这个是好求的，我们考虑从 $R_X$ 推到 $R_{X+1}$，发现此时只有 $G(X+1)$ 个 $i$ 满足 $f(X,i)\ne F(X+1,i)$，

其中 $G(X)$ 等于 $X$ 的因数个数。而一个结论是 $\sum\limits_{1\le X\le C}G(X)=O(C\log C)$，故我们暴力更新即可。

最后求答案时，我们可以二分答案 $X$，再判断 $R_X$ 是否大于 $Q_j$ 即可。

代码很好写，就不放了。

---


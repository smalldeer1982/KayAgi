# [DMOI-R2] 回到过去

## 题目背景

 > 想回到过去\
试着抱你在怀里\
羞怯的脸带有一点稚气\
想看你看的世界\
想在你梦的画面\
只要靠在一起就能感觉甜蜜\
想回到过去\
试着让故事继续\
至少不再让你离我而去\
分散时间的注意\
这次会抱得更紧\
这样挽留不知还来不来得及\
想回到过去\
沉默支撑跃过陌生\
静静看着凌晨黄昏\
你的身影 失去平衡\
慢慢下沉\
想回到过去\
—— 周杰伦《[回到过去](https://www.bilibili.com/video/BV1fx411N7bU?p=32&vd_source=2f4592e5507d6452d7d44dc098844d6b)》
>

什么阻碍着两颗心的碰面？什么阻碍着两个人的相见？

或许是令人捉摸不透的时间吧。

## 题目描述

给出 $n,m,t$ 以及 $t$ 个障碍物坐标，求在 $n$ 行 $m$ 列的矩阵中的非障碍位置上放置 $k$ 个两两之间没有公共边的方格的方案有多少种，答案对 $10^9+7$ 取模。

## 说明/提示

#### 【样例解释 #4】

对于测试点 1，可以画出如下的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9ld7rcxr.png)

其中用黑色格子表示障碍物，可发现只有 $\{(1,2)(1,4)\}\{(1,2)(2,3)\}\{(2,2)(1,4)\}\{(2,3)(1,4)\}$ 四种方案满足题意。

对于测试点 2，可以画出如下的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/74rbxvs6.png)

可发现只有 $\{(1,1)(1,3)(2,2)\}\{(1,1)(1,3)(2,4)\}\{(1,1)(2,2)(2,4)\}\{(1,3)(2,1)(2,4)\}\{(1,3)(2,2)(2,4)\}$ 五种情况符合题意。

### 数据点约定

|  数据点编号  |    $n$     |    $m$     |       $k$       |         $t$         |
| :----------: | :--------: | :--------: | :-------------: | :-----------------: |
|     $1$      |    $=1$    | $\le 10^9$ |      $=2$       |        $=0$         |
|     $2$      |    $=1$    | $\le 10^9$ |      $=3$       |        $=0$         |
|     $3$      |  $\le 20$  |  $\le 20$  |      $=2$       |        $=0$         |
|     $4$      |  $\le 20$  |  $\le 20$  |      $=3$       |        $=0$         |
|     $5$      |  $\le 20$  |  $\le 20$  |      $=2$       |      $\le 400$      |
|     $6$      |  $\le 20$  |  $\le 20$  |      $=3$       |      $\le 400$      |
|    $7,8$     | $\le 1000$ | $\le 1000$ |      $=2$       |        $=0$         |
|    $9,10$    | $\le 1000$ | $\le 1000$ |      $=3$       |        $=0$         |
|     $11$     | $\le 1000$ | $\le 1000$ |      $=2$       |      $\le 10$       |
|     $12$     | $\le 1000$ | $\le 1000$ |      $=3$       |      $\le 10$       |
|   $13,14$    | $\le 10^9$ |    $=n$    |      $=2$       |        $=0$         |
|   $15,16$    | $\le 10^9$ |    $=n$    |      $=3$       |        $=0$         |
|   $17,18$    | $\le 10^9$ | $\le 10^9$ |      $=2$       |        $=0$         |
|   $19,20$    | $\le 10^9$ | $\le 10^9$ |      $=3$       |        $=0$         |
|   $21,22$    | $\le 10^9$ | $\le 10^9$ |      $=2$       | $\le 2 \times 10^4$ |
|   $23,24$    | $\le 10^9$ | $\le 10^9$ |      $=3$       | $\le 2 \times 10^4$ |
| $25$ | $\le 10^9$ | $\le 10^9$ | $2 \le k \le 3$ | $\le 2 \times 10^4$ |

对于 $100\%$ 的数据，$1 \le n,m \le 10^9$，$2 \le k \le 3$，$0 \le t \le \min(n\cdot m,2 \times 10^4)$，$1 \le x_i \le n$，$1 \le y_i \le m$，$1 \le T \le 10$。每个数据点等分值。

## 样例 #1

### 输入

```
5
4 3 2 0
5 7 3 0
2 2 3 0
1 8 2 0
19 13 3 0```

### 输出

```
49
4773
0
21
2369219```

## 样例 #2

### 输入

```
10
4329 12935 3 0
125891 5949823 2 0
95023489 15327384 3 0
28592394 32891538 2 0
5894392 52374853 2 0
58963495 32591238 3 0
438291538 42819324 3 0
58493683 234728 2 0
284952 823499 3 0
528394298 25892948 3 0```

### 输出

```
468372138
510295355
536959469
56564283
462091483
842203294
778629925
806214146
91259493
793676806```

## 样例 #3

### 输入

```
10
55888076 506356561 3 3
48940088 192152177
33004718 365781091
45088097 31400730
65004621 206038505 2 3
50919157 24882066
50919158 24882064
50919156 24882067
249418509 7616530 2 1
205309921 4639136
164784593 419325145 3 4
105814446 200482317
105814449 200482315
105814443 200482315
79723922 206425705
477366546 180501076 3 4
39819749 14485585
39819746 14485582
39819743 14485588
39819748 14485585
84215455 29656489 3 0
524291275 23244413 3 4
8149961 10903189
8149958 10903192
8149958 10903193
8149961 10903191
584987873 823324694 3 1
540008401 27919189
25681672 419244427 2 4
4753299 108169462
4753301 108169463
4753298 108169462
4753298 108169464
313195991 98402123 3 3
7016773 83186671
7016770 83186674
7016767 83186675```

### 输出

```
580170965
521412840
890711205
353426094
41995284
193113183
352219667
748854206
767819374
351309432```

## 样例 #4

### 输入

```
10
2 4 2 4
1 1
1 3
2 1
2 4
2 4 3 3
1 2
2 3
1 4
1 1 3 0
3 4 2 0
3 2 2 1
1 2
4 2 3 0
2 3 2 0
5 4 3 3
2 4
1 3
1 1
4 5 2 2
1 4
2 1
3 1 2 0```

### 输出

```
4
5
0
49
5
12
8
385
128
1```

# 题解

## 作者：daniEl_lElE (赞：8)

~~是一血的题解捏（~~

# 思路

$k$ 很小，一定是突破口。

## $k=2$

先考虑 $k=2$，也就是问有多少两个的不相邻的。这种不好统计，考虑去统计总数减去相邻的。

### 总数

先考虑总数，共有 $n\times m-t$ 个可占用格子，故答案为 $\dbinom{n\times m-t}{2}$。

### 相邻

没有黑格子情况下，相邻的共有 $n\times (m-1)+m\times (n-1)$ 个，即每个 $1\times 2$ 的小格子。有黑格子呢？对于每个黑格子，添加进来后与周围白格子都构成一组不符合要求的相邻组，故扣减即可。

### 答案

设相邻的有 $cnt$ 个，故答案为 $\dbinom{n\times m-t}{2}-cnt$。

## $k=3$

前面相邻的还有有用的，我们还是考虑容斥计算，总数减去钦定两个相邻，再加上三个都相邻的。

### 总数

容易发现是 $\dbinom{n\times m-t}{3}$。

### 相邻

首先每个 $2\times 2$ 正方形内包含 $4$ 个连通的，每个 $1\times 3$ 中包含 $1$ 个，故总共有 $(n-2)\times(m-2)\times4+(n-3)\times(m-1)+(n-1)\times(m-3)$ 个。

然后对于每个黑格子，他会在 $6$ 种 $3$ 连通块中的每个位置，故 $18$ 种情况依次枚举扣减即可。

### 答案

设 $2$ 相邻有 $cnt_1$ 个，$3$ 相邻有 $cnt_2$ 个，故答案为 $\dbinom{n\times m-t}{3}-cnt_1\times(n\times m-t-2)+cnt_2$。

## 总结

大力分讨+一定思维含量的推式子以及容斥。

### 坑点

首先在计算的时候所有减法一定要和 $0$ 取 $\max$。

然后就是经典问题，一定记得取模！

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r+1)>>1)
using namespace std;
const int mod=1e9+7;
const int mul=1e9+2;
int n,m,k,t;
map<int,int> mp;
bool ok(int x,int y){
	if(x<1||y<1||x>n||y>m) return false;
	if(mp[x*mul+y]) return false;
	return true;
}
signed main(){
    ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--){
		cin>>n>>m>>k>>t;
		mp.clear();
		int nr=n*(m-1)+(n-1)*m,nr2=(n-1)*(m-1)*4+n*max(0ll,m-2)+m*max(0ll,n-2);
		for(int i=1;i<=t;i++){
			int x,y;
			cin>>x>>y;
			if(ok(x-1,y)) nr--;
			if(ok(x+1,y)) nr--;
			if(ok(x,y-1)) nr--;
			if(ok(x,y+1)) nr--;
			if(ok(x+1,y)&&ok(x,y+1)) nr2--;
			if(ok(x+1,y)&&ok(x,y-1)) nr2--;
			if(ok(x-1,y)&&ok(x,y+1)) nr2--;
			if(ok(x-1,y)&&ok(x,y-1)) nr2--;
			if(ok(x+1,y)&&ok(x+1,y+1)) nr2--;
			if(ok(x+1,y)&&ok(x+1,y-1)) nr2--;
			if(ok(x-1,y)&&ok(x-1,y+1)) nr2--;
			if(ok(x-1,y)&&ok(x-1,y-1)) nr2--;
			if(ok(x,y+1)&&ok(x-1,y+1)) nr2--;
			if(ok(x,y+1)&&ok(x+1,y+1)) nr2--;
			if(ok(x,y-1)&&ok(x-1,y-1)) nr2--;
			if(ok(x,y-1)&&ok(x+1,y-1)) nr2--;
			if(ok(x+1,y)&&ok(x-1,y)) nr2--;
			if(ok(x,y+1)&&ok(x,y-1)) nr2--;
			if(ok(x+1,y)&&ok(x+2,y)) nr2--;
			if(ok(x-1,y)&&ok(x-2,y)) nr2--;
			if(ok(x,y+1)&&ok(x,y+2)) nr2--;
			if(ok(x,y-1)&&ok(x,y-2)) nr2--;
			mp[x*mul+y]=1;
		}
		nr%=mod,nr2%=mod;
		int tot=(n*m-t)%mod;
		int num2=(tot*(tot-1)/2)%mod;
		int num3=(tot*(tot-1)%mod*(tot-2)%mod*166666668)%mod;
		if(k==2) cout<<(num2+mod-nr)%mod<<endl;
		else cout<<(num3+mod-nr*max(tot-2,0ll)%mod+nr2)%mod<<endl;
	}
	return 0;
}
```

---

## 作者：__K2FeO4 (赞：6)

这是我的第一篇紫题题解。

在整个过程中，我都没有使用二维数组来存坐标，而是使用了 map。~~我不知道它带不带 log。~~ 因此，我在赛场上的得分与 $n,m$ **几乎无关**。

## Part 1: $k=2,t=0$

我们先考虑最简单的情况，假如只有一个矩形，无障碍，放两个方格。

若忽略不共边这一限制，则总方案为 $C_{nm}^2=\frac{nm(nm-1)}{2}$。

不能共边怎么办？把共边的减去就行了。

共边方案数是多少？我们可以想象成将一个 $1\times 2$ 的矩形在这个大矩形中放置。如果横向放置，可以放在第 $1\sim n$ 行的任意一行，每行有 $m-1$ 个位置供放置。这样，算上竖放的，方案数为 $n(m-1)+m(n-1)=2nm-n-m$。

$ans=\frac{nm(nm-1)}{2}-2nm+n+m$。

这样可以得 32 分。

## Part 2: $k=3,t=0$

忽略相邻，总数为 $C_{nm}^3=\frac{nm(nm-1)(nm-2)}{6}$。

多了一个格子，我们可以在两个的基础上演算。

两个摆好了，剩下的一个，还有 $nm-2$ 个格子可以摆成"至少有一对拼接的方案"，数量为 $(2nm-n-m)(nm-2)$。

然鹅，这里会有重复计算。

![三位一体](https://cdn.luogu.com.cn/upload/image_hosting/oc93lsg5.png)

如图，AB 拼接时，将 C 也与 B 靠近。那么在以 BC 为基础时有重复计算，因此要在算拼接时把"三位一体"的情况减去，表现在答案上就是加上。

三位一体，无非就是长条形与拐形。长条形好办，同 Part 1，也就是 $n(m-2)+m(n-2)=2nm-2n-2m$。

拐形也不难，看作 $2\times 2$ 的正方形，共 $4$ 种方向，摆放数目为 $4(n-1)(m-1)$。

$ans=\frac{nm(nm-1)(nm-2)}{6}-(2nm-n-m)(nm-2)+(2nm-2n-2m)+4(n-1)(m-1)$

结果发现，没有得到 64 分。

那是因为，在 $n=1$ 或 $m=1$ 时，长条形不适用，因式变为负数了。

于是，我们应该特判一的情况，或者在判三位一体时干脆写 $n\times\max{\{m-2,0\}}+m\times\max{\{n-2,0\}}$。

这样就 64 分了。

## Part 3: $k=2,t>0$

接下来，我们讨论有障碍物的情况。

障碍怎么存？别想开二维数组了，十亿绝对存不下。考虑开 map，以 pair 为键名，bool 为键值。

忽略相邻，总数为 $C_{nm-t}^2=\frac{(nm-t)(nm-t-1)}{2}$。

为了方便，我们把相邻的组数记作 $l_2$。

初始化，$l_2=2nm-n-m$

$l_2$ 也随障碍物的出现而减小。每多加一个障碍物，它的上下左右，如果没有其他障碍物或超出边缘，就要将 $l_2$ 减一。

按照 Part 1 的方法计算，减去因障碍物而减少的组。

$ans=\frac{(nm-t)(nm-t-1)}{2}-l_2$

如果没有意外的话，80 分。

## Part 4: $k=3,t>0$

类似地，我们可以推得，忽略相邻，总数为 $C_{nm-t}^3=\frac{(nm-t)(nm-t-1)(nm-t-2)}{6}$。

对于每两个已被障碍物扣减的格子，与它对应的 $nm-2$ 个格子也会被扣减。但这样"三位一体"又会重复计算。

设三位一体的数量为 $l_3$，它被初始化为 $2nm-2n-2m+4(n-1)(m-1)$。

![十八罗汉](https://cdn.luogu.com.cn/upload/image_hosting/8xmtfrw4.png)

这是所有 18 种情况，将扣减的用这些补回来，即每次将 $l_3$ 减一即可。

$ans=\frac{(nm-t)(nm-t-1)(nm-t-2)}{6}-l_2\times(nm-t-2)+l_3$

在处理 18 种情况时，我用了个数组存起来，避免过长的打表。

```cpp
#include <bits/stdc++.h>
#define mpvc(x,y) make_pair(x,y)
#define p1 first
#define p2 second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pvc;//poly vinyl chlorine
map<pvc,bool> mp;
const ll mod=1e9+7;
int c2[4][2]={0,1,1,0,0,-1,-1,0};
int c3[18][4]={{0,1,0,2},{0,1,1,1},{1,0,1,1},{1,0,2,0},{1,0,1,-1},{0,-1,1,-1},
{0,-1,0,-2},{0,-1,-1,-1},{-1,0,-1,-1},{-1,0,-2,0},{-1,0,-1,1},{0,1,-1,1},
{0,1,1,0},{0,1,0,-1},{0,1,-1,0},{1,0,0,-1},{1,0,-1,0},{0,-1,-1,0}};
ll n,m,t,d,k;
bool ok(ll x,ll y){
    if(x<1||x>n||y<1||y>m)return false;
    return mp[mpvc(x,y)]^1;
}
int main(){
    scanf("%lld",&t);
    while(t--) {
        mp.clear();
        scanf("%lld%lld%lld%lld",&n,&m,&k,&d);
        ll ls2=(2*n*m-n-m)%mod,ls3=((n-1)*(m-1)*4%mod+2*n*m-2*n-2*m)%mod;
        if(n==1)ls3+=m;
        if(m==1)ls3+=n;
        ls3%=mod;
        for(int i=0;i<d;i++){
            ll x,y;
            scanf("%lld%lld",&x,&y);
            if(!ok(x,y))continue;
            for(int j=0;j<4;j++)
            if(ok(x+c2[j][0],y+c2[j][1]))ls2--;
            for(int j=0;j<18;j++)
            if(ok(x+c3[j][0],y+c3[j][1])&&ok(x+c3[j][2],y+c3[j][3]))ls3--;
            mp[mpvc(x,y)]=1;
        }
        ll p=(n*m-d)%mod;
        ll ans,inv=166666668;
        if(k==2)ans=((p*(p-1+mod)%mod*(mod+1)/2%mod-ls2)%mod+mod)%mod;
        else ans=((p*(p+mod-1)%mod*(p+mod-2)%mod*inv%mod-ls2*(p-2)%mod+ls3)%mod+mod)%mod;
        printf("%lld\n",ans);
    }
    return 0;
}
```
相对于其他题解，我的代码是不是很短？

---

## 作者：andychen_2012 (赞：4)

# DMOI官方题解

[https://www.luogu.com.cn/problem/U270463](https://www.luogu.com.cn/problem/U270463)

注：由于题解中 $Solution\ 9$ 的某些地方的 $\LaTeX$ 无法显示，若想观看正常版本 $\LaTeX$ 题解，可到上发链接下载 pdf 版本观看。

## 解题思路

## Solution 1

我们发现只有一行的情况下，问题转化为了一维不相邻问题，放置两个格子的方案数是 $(m-2)+(m-3)+\dots+1=\frac{(m-2)(m-1)}{2}$。放置三个格子的方案数是 $(m-4)+(m-5)+\dots+1+(m-5)+(m-6)+\dots+1+\dots+1=C_{m-2}^{3}$。可以通过 $1,2$ 两个数据点。

## Solution 2

可以直接dfs暴力查找有多少种方案数，时间复杂度 $O(C_{nm}^3)$ ，可以通过 $3,4,5,6$ 四个数据点。

## Solution 3

对于 $n,m \le 1000,k=2$ 的情况，可以进行dp来得出答案。

我们设 $dp_{i,j}$ 为第一个格子放在第 $i$ 行第 $j$ 列，第二个格子放置在第 $i$ 行第 $1 \sim j-1$ 列或第 $i-1$ 行到第 $1$ 行上的方案数。

对于 $dp_{n,m}$，我们知道如果将第一个格子放在 $(n,m)$，则第二个格子共有 $nm-3$ 种放法。对于 $dp_{i,m}$，我们的第二个格子则有 $im-2$ 种方法。

而对于 $dp_{i,j}(j<n)$，我们有 $dp_{i,j}=dp_{i,j+1}-1$。但注意到 $dp_{i,1}=dp_{i,2}$，因为当将一个格子放到 $(i,2)$ 上时，$(i,1)$ 是不可以放置的。

因此有如下代码：

```cpp
for(int i=n;i>=1;--i){
	if(i==1) a[i][m]=i*m-2;
	else a[i][m]=i*m-3;
	for(int j=m-1;j>=1;--j)
		a[i][j]=a[i][j+1]-1;
	a[i][1]=a[i][2];
}
for(int i=n;i>=1;--i){
	for(int j=m;j>=1;--j){
		ans=(ans+a[i][j])%mod;
		a[i][j]=0;
	}
}
```

时间复杂度：$O(nm)$，可以通过 $7,8$ 两个数据点。

## Solution 4

根据 *Christian Poisson* 在1990年的研究，我们知道对于 $n \times n$ 的矩形中放置2个互不相邻的格子的方案数为：

$$
\frac{n(n-1)(n^2+n-4)}{2}
$$

（证明我找不到了，我自己要是在这里证的话就涉及到正解了）

可以通过 $13,14$ 两个数据点。

## Solution 5

根据 Václav Kotěšovec 在2010年的研究，我们知道对于 $n \times n$ 的矩形中放置3个互不相邻的格子的方案数为：
$$
\frac{(n-2)(n^5+2n^4-11n^3-10n^2+42n-12)}{6}
$$
不给出证明的原因同上。

可以通过 $15,16$ 两个数据点。

## Solution 6

根据 $Solution 3$ 的dp，我们有如下思考：

我们对第一个格子的放置进行分情况讨论，对于四个边角的格子，第二个格子有 $nm-3$ 种放置方法，即不能够放在它自己的位置，以及它周围两个格子的位置。对于位于 $(1,j),(n,j),(i,1),(i,m)\ (1 \le i \le n,1 \le j \le m)$ 的格子，第二个格子有 $nm-4$ 种放置方法，即不能够放在它自己的位置，以及它周围三个格子的位置。
对于剩余的格子，第二个格子有 $nm-5$ 种放置方法，即不能够放在它自己的位置，以及它周围四个格子的位置。

又因为每个放置方案被计算了两次，所以答案要除以 $2$，最后答案为

$$
\frac{4(nm-3)+2(n-2+m-2)(nm-4)+(n-2)(m-2)(nm-5)}{2}
$$

可以通过 $17,18$ 两个数据点。

```cpp
ans=2*(n*m%mod-3)%mod+(n+m-4)%mod*(n*m%mod-4)%mod+(n-2)*(m-2)%mod*(n*m%mod-5)%mod*(mod/2+1)%mod;
ans=(ans%mod+mod)%mod;
write(ans,'\n');
```

## Solution 7

我们知道，在 $n \times m$ 的矩形中放置 $3$ 个方格一共有 $C_{nm}^3$ 种方案。

然后我们减去存在两个相邻的方格的方案，分为两种情况，一种是两个方格水平相邻，一直是两个方格竖直相邻，对答案的贡献减去 $2nm(n-1)(m-1)+n(m-1)(m-3)+m(n-1)(n-3)$，因为放置两个相邻方格后，还剩下 $nm-2$ 个位置可以放方格，而放置两个水平相邻的方格共有 $n(m-1)$ 种方案，放置两个竖直相邻的方格共有 $m(n-1)$ 种方案。但我们再考虑后发现，假设我们在 $(1,i)(1,i+1)$ 处放置了方格，就不能够在 $(1,i-1)$ 处放置方格，否则会和 $(1,i-1)(1,i)$ 处放置方格的情况重复计算。因此两种方法对答案的贡献分别为 $-nm(n-1)(m-1)-n(m-1)(m-3)$ 和 $-nm(n-1)(m-1)-m(n-1)(n-3)$。

而我们还要加上重复计算的既满足水平相邻又满足竖直相邻的方案的数量，即 $4(n-1)(m-1)$。

因此最终答案为 $C_{nm}^3-2nm(n-1)(m-1)-n(m-1)(m-3)-m(n-1)(n-3)+4(n-1)(m-1)$。

也可表示为
$$
C_{nm}^3-n(m-1)(nm-2)-m(n-1)(nm-2)+[m>2]n(m-2)+[n>2]m(n-2)+4(n-1)(m-1)
$$


其中 $[]$ 表示艾弗森括号，如果括号中的表达式成立则值为 $1$，否则为 $0$。可以通过 $19,20$ 两个数据点。

## Solution 8

对于 $k=2$ 且 $t \neq 0$ 的情况，我们做如下考虑：

我们先算出没有任何障碍物的答案 $ans=\frac{4(nm-3)+2(n-2+m-2)(nm-4)+(n-2)(m-2)(nm-5)}{2}$。我们知道，第 $i$ 个障碍物对答案的贡献为 $a_i-b_i-(nm-g_i-1)$，其中 $a_i$ 为在处理 $i$ 之前处理过多少个障碍物，当作 $i-1$ 处理即可，$b_i$ 表示其相邻的正左方与正上方的格子有 $b_i$ 个障碍物，可知 $b_i$ 的取值仅有 $0,1,2$，$g_i$ 表示 $i$ 四周不为边界的个数，$-1$ 表示自身。这个贡献表示的是在无障碍物情况下有多少种方案中有一个方格放置到了第 $i$ 个障碍物上。因此最终的答案为 $\frac{4(nm-3)+2(n-2+m-2)(nm-4)+(n-2)(m-2)(nm-5)}{2}+\sum\limits_{i=1}^t(i-1-b_i-nm+g_i+1)$。

可以先预处理出 $a_i,b_i,g_i$，设 $s=2(nm-3)+(n-2+m-2)(nm-4)+\frac{(n-2)(m-2)(nm-5)}{2},sum=\sum\limits_{i=0}^{t-1}i=\frac{t(t-1)}{2}$，则最终答案为
$$
s+\sum\limits_{i=1}^t(i-1-b_i-nm+g_i+1)=s+sum-tnm+\sum\limits_{i=1}^t(g_i-b_i)+t
$$


使用 map 存储障碍物坐标，时间复杂度 $O(t\log t)$。可通过 $5,11,21,22$ 四个数据点。

## Solution 9

对于 $k = 3, t \neq 0$ 的情况，我们做如下考虑：

我们先求出没有障碍的情况下的答案，表示为 $ans$，再求出有障碍的情况下 $k=2$ 的答案，设为 $res$。

因此我们要减去答案中计算了障碍的方案总数。

![](https://cdn.luogu.com.cn/upload/image_hosting/q2h502ut.png)

如图所示，我们先考虑 $(3,3)$ 这个格子对答案的贡献（障碍对答案的贡献肯定是负的）。

![](https://cdn.luogu.com.cn/upload/image_hosting/d1vtiywf.png)

涂为蓝色的格子表示的是需要考虑的格子。

我们知道，$(3,4)$ 已经有障碍了，因此不会在 $res$ 中被计算，这里也不需要考虑。

我们先让 $ans$ 减去 $res$ 表示答案减去这个障碍所贡献的非相邻格子方案数，但这样的话就会有一种计算失误的地方，如图中一个圆和一个叉会在这么计算的时候也计算进去了，但是原本 $ans$ 中是不会计算进去的。因此我们要把多出来的这部分也给容斥掉。

我们设 $g$ 表示这个格子旁边有几个格子（包括障碍物和非障碍物），设 $b$ 表示这个格子旁边有几个障碍物，因此贡献为 $(nm-g-1-t+b)$，当然，因为这个格子不为障碍物，因此就不需要再多考虑了。

但要注意到这样计算会导致有些地方计算重复，如两个叉又会重复计算，这时候又要记一个 $l$ 表示在算这个格子之前算过多少个格子（仅限当前障碍物）。这时，上面的贡献就变为 $(nm-g-1-t+b-l)$。

所以答案变为 $ans+=\sum\limits_{i=1}^{t}(\sum (nm-g-1-t+b-l) -res)$。

注意一开始的答案还有可能选择了两个障碍物，但是我们刚才没有判断这种情况，现在补判：

选择一个障碍物，排除掉它四周的所有障碍物，再判断左上角，右上角，左下角，右下角（与这两个障碍物相邻的格子最多有 $6$ 个），正上方两格，正左方两格，正右方两格，正下方两格（与这两个障碍物相邻的格子最多有 $7$），再判断其他格子，有多少个在边角上，多少个在中心。进行一次容斥后便可以求解，这一步的时间复杂度为 $O(t\log t)$。

设与第 $i$ 个障碍物相邻的方格中有 $a_i$ 个方格可以放置方格（不包括障碍物），$sum=\sum\limits_{i=1}^t a_i$。设 $i$ 和 $j$ 之间重叠的方格有 $p_{i,j}$ 个（不包括障碍物）。又设与 $i$ 相邻的障碍物有 $q_i$ 个，总和为 $q=\frac{1}{2}\sum\limits_{i=1}^tq_i$，因此对答案的贡献为 

$$
-(\sum_{i=1}^{t}\sum_{j=i+1}^{t}[\text{i is not adjacent to j}](nm-a_i-a_j-t+p_{i,j}))
$$

但注意到这样的时间复杂度是 $O(t^2)$ 的，不符合题目要求，但我们注意到可以用 $q,q_i$ 来化简。

$$
sum_{i=1}^{t}\sum_{j=i+1}^{t}[\text{i is not adjacent to j}](nm-a_i-a_j-t+p_{i,j})\\=(\frac{t(t-1)}{2}-q)nm-\sum_{i=1}^t(t-1-q_i)a_i-(\frac{t(t-1)}{2}-q)t+\sum_{i=1}^{t}\sum_{j=i+1}^{t}[\text{i is not adjacent to j}]p_{i,j}
$$

（$\LaTeX$ 炸了）

但是现在后面那部分仍旧是 $O(t^2)$ 的，不过我们可以注意到 $p_{i,j}$ 的取值只有 $0,1,2$ 三种取值，其中 $1,2$ 都可以由一个障碍物在另一个障碍物的左上角，右上角，左下角，右下角取得，$1$ 还可以由一个障碍物在另一个障碍物的正上方两格，正左方两格，正右方两格，正下方两格取得，$0$ 则为其他取值，画图表示如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/ac8qkf2w.png)

其中蓝色格子表示为 $0$。

我们可以对于每个 $i$ 预处理出来 $p_{i,j}$ 有值的 $8$ 个位置，其余全赋值为 $0$，设最终 $p_{i,j}$ 总和为 $cnt$，则 $\sum_{i=1}^{t}\sum_{j=i+1}^{t}[\text{i is not adjacent to j}]p_{i,j}$ 等于 $\frac{cnt}{2}$。

这样时间复杂度就变为 $O(t)$ 了。

注意到一开始的答案还有可能选择了三个障碍物，但是我们刚才没有判断这种情况，现在答案变为

$ans=ans-C_{t}^3+q(t-2)-\text{the number of three black squares are adjacent}$。

其中最右的数字可以 $O(t)$ 预处理。

三个障碍物相邻的图案有以下 $6$ 种：

![](https://cdn.luogu.com.cn/upload/image_hosting/yfvyad7q.png)

一开始计算时可以枚举中心节点来判断符合的障碍物图案个数。

最后答案以此计算。

因此我们有
$$
ans=C_{nm}^3-2nm(n-1)(m-1)-n(m-1)(m-3)-m(n-1)(n-3)+4(n-1)(m-1)
$$

$$
res=\frac{nm(nm-1)}{2}-n(m-1)-m(n-1)+\frac{t(t-1)}{2}-tnm+\sum\limits_{i=1}^t(g_i-b_i)+t
$$

$$
sum=\sum_{i=1}^ta_i
$$

$$
ans+=\sum\limits_{i=1}^{t}(\sum (nm-g-1-t+b-l) -res)
$$

$$
ans-=(\frac{t(t-1)}{2}-q)nm-\sum_{i=1}^t(t-1-q_i)a_i-(\frac{t(t-1)}{2}-q)t+\frac{cnt}{2}
$$

$$
ans=ans-C_{t}^3+q(t-2)-\text{the number of three black squares are adjacent}
$$

然后 $g,t,b$ 可以 $O(1)$ 计算，但是由于用到了 map，因此时间复杂度为 $O(\log t)$，要计算 $t$ 次，所以最后的时间复杂度为 $O(t\log t)$，可以通过所有数据点。

举例而言吧。

![](https://cdn.luogu.com.cn/upload/image_hosting/t39cl02u.png)

对于上图，黑色格子表示障碍物，白色格子表示空地。我们要分别求 $k=2,3$ 的情况。我们可以先计算出没有障碍物下的答案。

$k=2$ 时，假设没有障碍物，则

$ans=18$

（$\LaTeX$ 炸了）

由图可知，障碍物分别为 $(1,3)(2,2)$，$g_1=3,g_2=3,b_1=b_2=0$

$ans=ans-7=11$

（$\LaTeX$ 炸了）

对于 $k=3$ 的情况，假设没有障碍物，则

$ans=12$

（$\LaTeX$ 炸了）

由 $k=2$ 的情况可得 $res=11,a_1=3,a_2=3,sum=6$，又有 $g_{1,2}=3,g_{1,4}=2,g_{2,1}=2,g_{2,3}=3,b_{1,2}=2,b_{1,4}=1,b_{2,1}=1,b_{2,3}=2$

$$
\therefore ans+=\sum\limits_{i=1}^{t}(\sum(b+5-g-l)-11)
$$

（$\LaTeX$ 炸了）

我们发现，在计算第一种情况，即只算一个障碍物的时候，$(1,2)(2,3)$ 会重复计算，这是没有问题的，我们将所有的 $(b-g-l+5)$ 列出来可得：

对于障碍物 $(1,3)$：

$(1,2):b=2,g=3,l=0,b-g-l+5=2-3-0+5=4$

$(1,4):b=1,g=2,l=1,b-g-l+5=1-2-1+5=3$

$(2,3):b=1,g=2,l=2,b-g-l+5=1-2-2+5=2$

对于障碍物 $(2,2)$：

$(2,1):b=1,g=2,l=0,b-g-l+5=1-2-0+5=4$

$(1,2):b=2,g=3,l=1,b-g-l+5=2-3-1+5=3$

$(2,3):b=1,g=2,l=2,b-g-l+5=1-2-2+5=2$

$$
\therefore ans+=(4+3+2-11)+(4+3+2-11)=-4\\
\therefore ans=12-4=8
$$

对于第二种情况，即选择两个障碍物和一个空格子，有 $q_1=q_2=q=0,cnt=4,a_1=a_2=3$：

$$
ans=ans-2=6
$$

（$\LaTeX$ 炸了）

对于第三种情况，由于仅有两个障碍物，无需讨论。因此最后 $ans=6$。

再举一个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/ronh8719.png)

对于 $k=2$ 的情况，假设没有障碍物，则

$ans=24$

（$\LaTeX$ 炸了）

考虑障碍物，则五个障碍物分别为 $(1,2)(2,1)(2,3)(3,1)(3,2)$，$g_1=g_2=g_3=g_5=3,g_4=2,b_1=b_2=b_3=0,b_4=b_5=1$

$ans=6$

（$\LaTeX$ 炸了）

对于 $k=3$，假设没有障碍物，则

$ans=22$

（$\LaTeX$ 炸了）

考虑障碍物，先考虑第一种情况，由 $k=2$ 的情况可得 $res=6$，又有 $g_{1,1}=2,b_{1,1}=2,g_{1,3}=2,b_{1,3}=2,g_{2,2}=4,b_{2,2}=4,g_{3,3}=2,b_{3,3}=2$，

$$
\therefore ans+=\sum\limits_{i=1}^{t}(\sum(b-g-l+3)-6)
$$

（$\LaTeX$ 炸了）

因此我们将所有的 $b-g-l+3$ 列出来可得：

对于障碍物 $(1,2)$：

$(1,1):b=2,g=2,l=0,b-g-l+3=2-2-0+3=3$

$(1,3):b=2,g=2,l=1,b-g-l+3=2-2-1+3=2$

$(2,2):b=4,g=4,l=2,b-g-l+3=4-4-2+3=1$

对于障碍物 $(2,1)$：

$(1,1):b=2,g=2,l=0,b-g-l+3=2-2-0+3=3$

$(2,2):b=4,g=4,l=1,b-g-l+3=4-4-1+3=2$

对于障碍物 $(2,3)$：

$(1,3):b=2,g=2,l=0,b-g-l+3=2-2-0+3=3$

$(2,2):b=4,g=4,l=1,b-g-l+3=4-4-1+3=2$

$(3,3):b=2,g=2,l=2,b-g-l+3=2-2-2+3=1$

对于障碍物 $(3,1)$，周围全为障碍物。

对于障碍物 $(3,2)$：

$(2,2):b=4,g=4,l=0,b-g-l+3=4-4-0+3=3$

$(3,3):b=2,g=2,l=1,b-g-l+3=2-2-1+3=2$

$$
\therefore ans+=(3+2+1-6)+(3+2-6)+(3+2+1-6)+(0-6)+(3+2-6)\\
ans=22-1-6-1=14
$$

对于第二种情况，即选择两个障碍物和一个空格子，$q_1=0,q_2=1,q_3=0,q_4=2,q_5=1,q=\frac{0+1+0+2+1}{2}=2$，$a_1=3,a_2=2,a_3=3,a_4=0,a_5=2,sum=3+2+3+0+2=10$。

又有

$p_{1,2}=p_{2,1}=p_{1,3}=p_{3,1}=p_{3,5}=p_{5,3}=2$

$p_{1,4}=p_{4,1}=p_{2,4}=p_{4,2}=p_{3,4}=p_{4,3}=p_{4,5}=p_{5,4}=0$

$p_{1,5}=p_{5,1}=p_{2,3}=p_{3,2}=p_{2,5}=p_{5,2}=1$

$cnt=18$。

$ans=ans-5=14-5=9$。

对于第三种情况，我们有

$$
C_t^3=10\\
q(t-2)=2 \times 3 =6\\
\text{the number of three black squares are adjacent}=1
$$

因此，$ans=ans-10+6-1=9-10+6-1=4$。

通过手动模拟可知，仅有 $\{(1,1)(1,3)(2,2)\}\{(1,1)(1,3)(3,3)\}\{(1,1)(2,2)(3,3)\}\{(1,3)(2,2)(3,3)\}$ 四种铺放方法符合题意，因此可以验证我们的计算方案是正确的。

## 解题代码

```cpp
#include<cstdio>
#include<map>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
inline int read(){
	int x=0;
	int ch=getchar(),f=0;
	while(ch<48||ch>57) f=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return f?-x:x;
}
inline void write(ll x,char end='\n'){
	if(x==0){
		putchar('0');
		putchar(end);
		return;
	}
	if(x<0) putchar('-'),x=-x;
	int st[70],sr=0;
	while(x){
		st[sr++]=x%10;
		x/=10;
	}
	while(sr--) putchar(st[sr]+48);
	putchar(end);
	return;
}
inline ll fp(ll x,ll y){
	ll s=1;
	while(y){
		if(y&1) s=s*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return s;
}
inline ll dv(ll x,ll y){
	return x*fp(y,mod-2)%mod;
}
inline void swap(ll &x,ll &y){ll t=x;x=y;y=t;}
ll f2,f6;
const int N=2e4+5;
ll ans,n,m,k,t;
int x[N],y[N];
int a[N],q[N];
map<ll,bool> mp;
int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
inline ll id(ll x,ll y){return x*(m+1)+y;}
int main(){
	int T=read();
	f2=dv(1,2);
	f6=dv(1,6);
	while(T--){
		n=read(),m=read(),k=read(),t=read();
		for(int i=1;i<=t;++i){
			x[i]=read(),y[i]=read();
			mp[id(x[i],y[i])]=1;
			a[i]=q[i]=0;
		}
		if(n==1&&m==1){
			puts("0");
			mp[id(1,1)]=0;
			continue;
		}
		if(k==2){
			ans=n*m%mod*(n*m%mod-1)%mod*f2%mod;
			ans=(ans-n*(m-1)%mod-m*(n-1))%mod;
			ans=(ans%mod+mod)%mod;
			for(int i=1;i<=t;++i){
				int g=0,b=0;
				if(x[i]>1) g++,b+=mp[id(x[i]-1,y[i])];
				if(x[i]<n) g++;
				if(y[i]>1) g++,b+=mp[id(x[i],y[i]-1)];
				if(y[i]<m) g++;
				ans=(ans+i-1-b-n*m%mod+g+1)%mod;
			}
			ans=(ans%mod+mod)%mod;
		}
		else{
			//no any obtacles
			ans=n*m%mod*((n*m%mod-1)%mod)%mod*((n*m%mod-2)%mod)%mod*f6%mod;
			ans=(ans-n*(m-1)%mod*(n*m%mod-2)%mod-m*(n-1)%mod*((n*m%mod-2)%mod)%mod)%mod;
			if(m>2) ans=(ans+n*(m-2)%mod)%mod;
			if(n>2) ans=(ans+m*(n-2)%mod)%mod;
			ans=(ans+4*(n-1)%mod*(m-1)%mod)%mod;
			ans=(ans%mod+mod)%mod;
			//calculate k=2 when there are obtacles
			ll res=0;
			res=n*m%mod*(n*m%mod-1)%mod*f2%mod;
			res=(res-n*(m-1)%mod-m*(n-1))%mod;
			res=(res%mod+mod)%mod;
			for(int i=1;i<=t;++i){
				int g=0,b=0;
				if(x[i]>1) g++,b+=mp[id(x[i]-1,y[i])];
				if(x[i]<n) g++;
				if(y[i]>1) g++,b+=mp[id(x[i],y[i]-1)];
				if(y[i]<m) g++;
				res=(res+i-1-b-n*m%mod+g+1)%mod;
			}
			res=(res%mod+mod)%mod;
			//ans-=(a black square and two white squares)
			for(int i=1;i<=t;++i){
				ll sum=-res;
				int g=0,b=0,l=0;
				for(int j=0;j<4;++j){
					int tx=x[i]+dx[j],ty=y[i]+dy[j];
					if(tx<1||ty<1||tx>n||ty>m) continue;
					if(mp[id(tx,ty)]) continue;
					//the white square next to the black square
					g=b=0;
					for(int j2=0;j2<4;++j2){
						int tx2=tx+dx[j2],ty2=ty+dy[j2];
						if(tx2<1||ty2<1||tx2>n||ty2>m) continue;
						g++;b+=mp[id(tx2,ty2)];
					}
					sum=(sum+n*m%mod-g-1-t+b-l)%mod;
					++l;
				}
				ans=((ans+sum%mod)%mod+mod)%mod;
			}
			//ans-=(two black squares and one white square)
			//find two squares with no adjacent white squares between
			//the final answer should delete two nonadjacent black squares and a white square which is not adjacent to the two black squares
			ll qsum=0,sum=0;
			for(int i=1;i<=t;++i){
				for(int j=0;j<4;++j){
					int tx=x[i]+dx[j],ty=y[i]+dy[j];
					if(mp[id(tx,ty)]) q[i]++;
					if(tx>0&&ty>0&&tx<=n&&ty<=m){
						if(!mp[id(tx,ty)]) a[i]++;
					}
				}
				qsum+=q[i];
			}
			qsum/=2;
			sum=(t*(t-1)%mod*f2%mod-qsum+mod)%mod*n%mod*m%mod;
			for(int i=1;i<=t;++i)
				sum=(sum-(t-1-q[i])%mod*a[i]%mod+mod)%mod;
			sum=(sum%mod+mod)%mod;
			sum=(sum-(t*(t-1)%mod*f2%mod-qsum)%mod*t%mod)%mod;
			sum=(sum%mod+mod)%mod;
			ll cnt=0;
			for(int i=1;i<=t;++i){
				if(x[i]-1>0&&(!mp[id(x[i]-1,y[i])])){
					if(mp[id(x[i]-1,y[i]-1)]) ++cnt;
					if(mp[id(x[i]-1,y[i]+1)]) ++cnt;
					if(mp[id(x[i]-2,y[i])]) ++cnt;
				}
				if(x[i]+1<=n&&(!mp[id(x[i]+1,y[i])])){
					if(mp[id(x[i]+1,y[i]-1)]) ++cnt;
					if(mp[id(x[i]+1,y[i]+1)]) ++cnt;
					if(mp[id(x[i]+2,y[i])]) ++cnt;
				}
				if(y[i]-1>0&&(!mp[id(x[i],y[i]-1)])){
					if(mp[id(x[i]-1,y[i]-1)]) ++cnt;
					if(mp[id(x[i]+1,y[i]-1)]) ++cnt;
					if(mp[id(x[i],y[i]-2)]) ++cnt;
				}
				if(y[i]+1<=m&&(!mp[id(x[i],y[i]+1)])){
					if(mp[id(x[i]-1,y[i]+1)]) ++cnt;
					if(mp[id(x[i]+1,y[i]+1)]) ++cnt;
					if(mp[id(x[i],y[i]+2)]) ++cnt;
				}
			}
			cnt/=2;
			sum=(sum+cnt)%mod;
			ans=(ans-sum+mod)%mod;
			//ans-=(three black squares)
			ans=(ans-t*(t-1)%mod*(t-2)%mod*f6%mod+mod)%mod;
			ans=(ans+qsum*(t-2)%mod)%mod;
			sum=0;
			for(int i=1;i<=t;++i){
				if(mp[id(x[i]-1,y[i])]&&mp[id(x[i]+1,y[i])]) ++sum;
				// type 1,three black squares in a column
				if(mp[id(x[i]-1,y[i])]&&mp[id(x[i],y[i]-1)]) ++sum;
				// type 2,a 0111 type
				if(mp[id(x[i]-1,y[i])]&&mp[id(x[i],y[i]+1)]) ++sum;
				// type 3,a 1011 type
				if(mp[id(x[i],y[i]-1)]&&mp[id(x[i],y[i]+1)]) ++sum;
				// type 4,three black squares in a line
				if(mp[id(x[i],y[i]-1)]&&mp[id(x[i]+1,y[i])]) ++sum;
				// type 5,a 1101 type
				if(mp[id(x[i],y[i]+1)]&&mp[id(x[i]+1,y[i])]) ++sum;
				// type 6,a 1110 type
			}
			ans=(ans-sum+mod)%mod;
			ans=(ans%mod+mod)%mod;
		}
		write(ans);
		for(int i=1;i<=t;++i)
			mp[id(x[i],y[i])]=0;
	}
	return 0;
}
```

---

## 作者：2018ljw (赞：3)

一种更加简洁明了的入手角度（？

$k=2$ 和 $k=3$ 两种情况分别求解。

## k=2
考虑基本容斥形式：总方案减去两个方块相邻的方案。

总方案很好求，$C_{nm-t}^2$。然后从公共边的角度计数两个方块相邻。

原本可以成为公共边的边数为 $n(m-1)+m(n-1)=2nm-n-m$，但因为我们放了一些障碍，所以有些边不能成为公共边了，尝试计数有多少边不能成为公共边。

将障碍按 $x$ 坐标为第一关键字，$y$ 为第二关键字排序进行扫描线。对于 $x$ 坐标相同的方块：

1. 若 $x\neq n$，那么每个方块下边界都会占据一条边。
2. 每个方块左右边界都会占据一条边，但可能会出现 $y_i=y_{i-1}+1$ 或者 $y=1/m$ 的情况，这时候需要减掉重叠或边界部分。
3. 若 $x\neq 1$，每个方块上边界也会占据边，但可能上一行这条边已经被统计了。我们开一个 map 维护上一行所有方块的 y 坐标判断一下即可。

如此，我们便得到了可以成为两个方块公共边的数量 $cnt$。这个 $cnt$ 在后面处理 $k=3$ 的问题时还要用到。

每条公共边唯一对应一种不合法情况，答案即为 $C_{nm-t}^2-cnt$。

## k=3
继续容斥：总方案减去至少两个方块相邻加上三个方块相邻

总方案是 $C_{nm-t}^3$。

至少两个方块相邻，第三个方块可以随便放，方案为 $cnt\times (nm-t-2)$。

三个方块均相邻，要么是一个长条要么是 L 型，我们枚举中间那个方块。

关注到这个方块有用的信息是它有几条能作为公共边的出边，如果有 $d$ 条，那么贡献就是 $C_{d}^2$。

所以分别对有 $2\sim4$ 条出边的方块计数，分别记为 $c_2,c_3,c_4$。

首先考虑没有障碍的情况，分类讨论如下：

1. $n=m=1$：$c_2=c_3=c_4=0$
2. $n=1,m\neq 1$：$c_2=m-2$，$c_3=c_4=0$
3. $m=1,n\neq 1$：$c_2=n-2$，$c_3=c_4=0$
4. $m,n\ge 2$：$c_2=4$，$c_3=2m+2n-8$，$c_4=(n-2)(m-2)$

然后考虑障碍的影响：

1. 对于障碍本身，它原本格子对应的计数直接 $-1$。
2. 对于与其相邻的格子，它的计数会掉到下一级。

由于受影响的非障碍格最多只有 $4t$ 个，我们开一个 map 去记录这些格子的出边数，然后枚举每个障碍，修改与其相邻格子的出边数并更新计数即可。

最终答案为 $C_{nm-t}^3-cnt\times(nm-t-2)+c_2+3c_3+6c_4$。

复杂度 $O(t\log t)$，多测记得清 map。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<assert.h>
#define mp make_pair
const int mod=1e9+7,inv2=(mod+1)/2,inv3=(mod+1)/3;
using namespace std;
long long c2(long long x){
	return (x-1)%mod*(x%mod)%mod*inv2%mod;
}
long long c3(long long x){
	return (x-2)%mod*((x-1)%mod)%mod*(x%mod)%mod*inv2%mod*inv3%mod;
}
struct pts{
	int x,y;
}a[20001];
bool operator<(pts x,pts y){
	return x.x==y.x?x.y<y.y:x.x<y.x;
}
long long n,m,t,k;
map<int,bool>sr;
map<pair<int,int>,int>st;
void crt(int x,int y){
	int ot=4;
	if(x==1)ot--;if(x==n)ot--;
	if(y==1)ot--;if(y==m)ot--;
	st[mp(x,y)]=ot;
}
int main(){
	int i,j,q;
	scanf("%d",&q);
	while(q--){
		scanf("%lld%lld%lld%lld",&n,&m,&k,&t);
		for(i=1;i<=t;i++)scanf("%d%d",&a[i].x,&a[i].y);
		sort(a+1,a+t+1);
		int lst=0;
		long long res;
		if(k==2)res=c2(n*m-t);
		else res=c3(n*m-t);
		long long edg=(n*m%mod*2%mod-n-m+2ll*mod)%mod;
		for(i=1;i<=t;i++){
			if(i!=t&&a[i].x==a[i+1].x)continue;
			if(a[i].x!=a[lst].x+1)sr.clear();
			if(a[i].x!=1)for(j=lst+1;j<=i;j++)if(!sr[a[j].y])edg--;
			if(a[i].x!=n)edg-=i-lst;
			for(j=lst+1;j<=i;j++){
				if(a[j].y!=m)edg--;
				if(a[j].y!=1&&(j==lst+1||a[j].y!=a[j-1].y+1))edg--;
			}
			sr.clear();
			for(j=lst+1;j<=i;j++)sr[a[j].y]=1;
			lst=i;
		}
		edg=(edg+mod)%mod;
		if(k==2){
			printf("%lld\n",(res-edg+mod)%mod);
			continue;
		}
		res-=(n*m-t-2+mod)%mod*edg%mod;
		res=(res%mod+mod)%mod;
		long long l2=4,l3=n*2+m*2-8,l4=1ll*n*m-l2-l3;
		if(n==1&&m==1)l2=l3=l4=0;
		else if(n==1||m==1)l2=n+m-3,l3=l4=0;
		for(i=1;i<=t;i++){
			st[mp(a[i].x,a[i].y)]=-1;
			int ot=4;
			if(a[i].x==1)ot--;if(a[i].x==n)ot--;
			if(a[i].y==1)ot--;if(a[i].y==m)ot--;
			if(ot==4)l4--;
			if(ot==3)l3--;
			if(ot==2)l2--;
		}
		for(i=1;i<=t;i++){
			int x=a[i].x,y=a[i].y;
			if(x!=1){
				if(!st[mp(x-1,y)])crt(x-1,y);
				int w=st[mp(x-1,y)];
				if(w==4)l4--,l3++;
				if(w==3)l3--,l2++;
				if(w==2)l2--;
				w--;if(!w)w--;
				st[mp(x-1,y)]=w;
			}
			if(x!=n){
				if(!st[mp(x+1,y)])crt(x+1,y);
				int w=st[mp(x+1,y)];
				if(w==4)l4--,l3++;
				if(w==3)l3--,l2++;
				if(w==2)l2--;
				w--;if(!w)w--;
				st[mp(x+1,y)]=w;
			}
			if(y!=1){
				if(!st[mp(x,y-1)])crt(x,y-1);
				int w=st[mp(x,y-1)];
				if(w==4)l4--,l3++;
				if(w==3)l3--,l2++;
				if(w==2)l2--;
				w--;if(!w)w--;
				st[mp(x,y-1)]=w;
			}
			if(y!=m){
				if(!st[mp(x,y+1)])crt(x,y+1);
				int w=st[mp(x,y+1)];
				if(w==4)l4--,l3++;
				if(w==3)l3--,l2++;
				if(w==2)l2--;
				w--;if(!w)w--;
				st[mp(x,y+1)]=w;
			}
		}
		res=(res+l2+l3*3+l4%mod*6)%mod;
		printf("%lld\n",res);
		st.clear();
	}
}
```

---

## 作者：arrow_king (赞：0)

大力分讨题解捏~

题意很清楚了。

# 分讨

基础思路是容斥，即用全部方案减去有选中的格子相邻的方案。

首先考虑 $k=2$。总方案是 $\dbinom{nm-t}2$，不合法的方案就是两个格子相邻的方案数。考虑没有障碍的方案数，就是 $(n-1)m+(m-1)n$。接下来计算障碍导致的错误计算。对于竖着的情况，发现一个障碍会导致多算两次，但是如果两个障碍竖着连在一起就会多减一次。

```cpp
il ll domino() {
	ll ans2=(n-1)*m%mod-2*t,ans3=n*(m-1)%mod-2*t;
	for(int i=1;i<=t;i++) {
		if(x[i]==1||x[i]==n) ans2++;
		if(y[i]==1||y[i]==m) ans3++;
		if(mp.count({x[i]-1,y[i]})) ans2++;
		if(mp.count({x[i],y[i]-1})) ans3++;
	}
	ans2=(ans2+mod)%mod,ans3=(ans3+mod)%mod;
	if(n==1) ans2=0;
	if(m==1) ans3=0;
	return (ans2+ans3)%mod;
}
```

接下来是 $k=3$ 的情况，此时要复杂一些。

总方案自然是 $\dbinom{nm-t}3$ 没的说，考虑不合法的情况。发现是【钦定两个格子相邻、第三个随意的方案数】减去【三个全部相邻的方案数】。而【钦定两个格子相邻】就是上面的 `domino()`，只需要再乘上一个 $(nm-t-2)$ 即可。

同机房奆佬给了一个很优美的统计三联通的方法：

考虑记一个格子的出度为四周四个格子中没出边界且不是障碍的位置数量。记 $s_i$ 表示出度为 $i$ 的格子数量，那么当枚举三联通的中间点（对于长条是中间的点，对于 "L" 形的图形就是拐点）时相当于在出度格子中选了两个，也就是说一个中心点的贡献是 $\dbinom d2$。那么最后三联通的答案就是
$$
\sum_{i=0}^4\dbinom i2s_i
$$
只需要统计即可。方法是先统计障碍四周的点，再统计边上与角上的点，最后统计内部的点。

时间复杂度 $O(t\log t)$，log 来源于 map。

---

## 作者：lalaji2010 (赞：0)

# [P8915 [DMOI-R2] 回到过去](https://www.luogu.com.cn/problem/P8915)

## 分析

容易发现 $k$ 和 $t$ 都很小，尝试从这里入手。

正难则反，考虑对于 $k$ 的两种取值都求出不放置在障碍上的放置方案数，再减去不放在障碍上的有至少两个方格挨在一起的放置方案数就是答案。

推导到这一步其实不难，接下来就是暴力推式子了。

---

### ①不放置在障碍上的所有放置方案数

当 $k=2$ 时。

根据定义，显然有：

$$tot_2={n \times m - t \choose 2}$$

表示从 $n \times m$ 位置里选出 $2$ 个的方案数。

当 $k=3$ 时。

同理：

$$tot_3={n \times m - t \choose 3}$$

---

### ②不放置在障碍上的不合法放置方案数

当 $k=2$ 时。

如果没有障碍，该方案数相当于 $1 \times 2$ 的骨牌放置在 $n \times m$ 的棋盘上的方案数，易得为 $cnt_2=n(m-1)+m(n-1)$。

对于每一个障碍，其都会影响减少四联通的骨牌放置方案，但是有一些障碍在棋盘边缘，也有一些障碍挨在一起，暴力将 $cnt_2$ 减去 $4$ 会导致冗余的减法运算。

所以我们枚举每个障碍的四联通位置，对于棋盘边缘我们作特判，而对于障碍开一个 map 记录位置，如果当前障碍枚举到的含有该障碍的骨牌放置方案中某位置是之前输入的障碍，则该不合法放置方案已经被统计过。

如果都不是，方案数 $cnt_2$ 自减，因为此方案最先受当前障碍影响而失效。

当 $k=3$ 时。

可以是两个挨在一起再随便选一个，$cnt_2 \times (n \times m - t - 2)$。但是三个都挨在一起的时候这样计算会被算 $2$ 遍，所以还要做一个小容斥，减去多算的。

记三个都挨在一起的放置方案数为 $cnt_3$。

如果没有障碍，该方案数相当于 $L$ 形的放置方案数加上 $I$ 形的放置方案数，即 $cnt_3=n(m-2)+m(n-2)+4(n-1)(m-1)$，相当好理解。

对于每一个障碍，都有可能出现在 $6$ 种 $3$ 连通里的任意一个位置，即会有 $3 \times 6=18$ 种可能会影响的方案，一一枚举并且判断是否为逾越地图边缘或者之前被统计过的方案。如果不是，那么 $3$ 连通的方案数减少 $1$。

---

### ③求解答案

当 $k=2$ 时：

$$Ans_2=tot_2-cnt_2$$

当 $k=3$ 时：

$$Ans_3=tot_3-(cnt_2 \times (n \times m - t - 2)-cnt_3)$$


map 单次操作是 $O(\log n)$ 的，而 unordered_map 单次操作是 $O(1)$ 的，于是本题中我使用 unordered_map 来实现。

一定要**记得取模！**

## AC code

```cpp
#include<bits/stdc++.h>
#include<unordered_map>
#define ll long long
using namespace std;
const ll M=1e9+7;
unordered_map<ll,ll> mp;
int T;
ll n,m,k,t;
inline ll read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline ll ksm(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1){
			ans=ans*a%M;
		}
		b>>=1;
		a=a*a%M;
	}
	return ans;
}
inline bool check(ll x,ll y){
	if(x<1||y<1||x>n||y>m||mp[x*M+y]) return 0;
	return 1;
}
int main(){
	ll inv2=ksm(2,M-2)%M;
	ll inv6=ksm(6,M-2)%M;
	T=read();
	while(T--){
		n=read(),m=read(),k=read(),t=read();
		mp.clear();
		ll tot=(n*m%M-t)%M;
		ll tot2=tot*(tot-1)%M*inv2;
		ll tot3=tot*(tot-1)%M*(tot-2)%M*inv6%M;
		ll cnt2=(n*(m-1)%M+m*(n-1)%M)%M;
		ll cnt3=(max(0ll,n-2)*m%M+max(0ll,m-2)*n%M+4*(n-1)*(m-1)%M)%M;
		for(register int i=1;i<=t;i++){
			int x,y;
			x=read(),y=read();
			//2连通 
			if(check(x-1,y)) cnt2--;
			if(check(x,y-1)) cnt2--;
			if(check(x,y+1)) cnt2--;
			if(check(x+1,y)) cnt2--;
			//3连通
			//障碍为 I 形边缘点 
			if(check(x+1,y)&&check(x+2,y)) cnt3--;
			if(check(x-1,y)&&check(x-2,y)) cnt3--;
			if(check(x,y+1)&&check(x,y+2)) cnt3--;
			if(check(x,y-1)&&check(x,y-2)) cnt3--;
			//障碍为 I 形关键点（中间点） 
			if(check(x,y+1)&&check(x-1,y+1)) cnt3--;
			if(check(x,y+1)&&check(x+1,y+1)) cnt3--;
			//障碍为 L 形边缘点 
			if(check(x+1,y)&&check(x+1,y+1)) cnt3--;
			if(check(x+1,y)&&check(x+1,y-1)) cnt3--;
			if(check(x-1,y)&&check(x-1,y+1)) cnt3--;
			if(check(x-1,y)&&check(x-1,y-1)) cnt3--;
			if(check(x,y-1)&&check(x-1,y-1)) cnt3--;
			if(check(x,y-1)&&check(x+1,y-1)) cnt3--;
			if(check(x+1,y)&&check(x-1,y)) cnt3--;
			if(check(x,y+1)&&check(x,y-1)) cnt3--;
			//障碍为 L 形关键点 
			if(check(x+1,y)&&check(x,y+1)) cnt3--;
			if(check(x+1,y)&&check(x,y-1)) cnt3--;
			if(check(x-1,y)&&check(x,y+1)) cnt3--;
			if(check(x-1,y)&&check(x,y-1)) cnt3--;
			mp[x*M+y]=1;
		}
		cnt2=(cnt2%M+M)%M;
		cnt3=(cnt3%M+M)%M;
		if(k==2) cout<<(tot2-cnt2+M)%M<<"\n";
		else cout<<(tot3-cnt2*max(0ll,tot-2)%M+cnt3+M)%M<<"\n"; 
	}
	return 0;
}
```

---


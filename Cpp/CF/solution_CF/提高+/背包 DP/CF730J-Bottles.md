# Bottles

## 题目描述

有 $n$ 瓶水，第 $i$ 瓶水的水量为 $a_i$，容量为 $b_i$。将 $1$ 单位水从一个瓶子转移到另一个瓶子所消耗时间为 $1$ 秒，且可以进行无限次转移。求储存所有水所需最小瓶子数 $k$ 以及该情况下所用最小时间 $t$。

## 样例 #1

### 输入

```
4
3 3 4 3
4 7 6 5
```

### 输出

```
2 6
```

## 样例 #2

### 输入

```
2
1 1
100 100
```

### 输出

```
1 1
```

## 样例 #3

### 输入

```
5
10 30 5 6 24
10 41 7 8 24
```

### 输出

```
3 11
```

# 题解

## 作者：Asdonel (赞：34)

# 简要思路

对于这一道题，很显然是一个动态规划 ~~（废话）~~ 。

那么我们考虑转移方程。

显然，在这一道题中，关键变量只有两个 $a$ , $b$ 。

第一问很好求，**很显然，根据贪心，先对瓶子的容量进行降序排序，求前若干个瓶子使他们的容量大于等于所有水的体积时的个数即可**。

### 代码如下

```cpp
	sort(c+1,c+n+1,cmp);
	ll temp=0;
	for(ll i=1;i<=n;i+=1){
		temp+=c[i].b;
		if(temp>=m){
			printf("%d ",i);
			break;
		}
	}
```


但是题目在选择瓶子最少的情况下，方案是不一定的。

这就导致在第二问，可能答案会不同。

通过观察得知， **第二问就是要在第一问的个数确定时，求出选择瓶子的水最多的方案** 。

为什么？ **因为选择了若干个瓶子，就意味着其他的瓶子的水要倒入其中，花费就为他们水的体积之和** 。

然后，我们开始考虑转移方程。

设 $f_i$ 表示当水的体积是 $i$ 时所需要的最少的瓶子数。

显然，根据一般的背包问题，有 $f_i = \max{f_{i-b_j} + 1}$ 。

同时，根据上面的分析，我们要求的是此时水体积最大的，所以附加上一个 $ans$ 数组， $ans_i$ **表示 $ans_i$ 表示当容积为 $i$ 时水体积的最大值** 。

由以上思路，就有了如下代码。

CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 20;
int n, m, f[10020], sum, ans[10020]; 
struct Node {
    int a, b;
} c[N];
inline int read() {//快读的板子，请自动忽略 
    char ch = getchar();
    int ans = 0, cf = 1;

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            cf = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        ans = (ans << 1) + (ans << 3) + (ch ^ 48);
        ch = getchar();
    }

    return ans * cf;
}
bool cmp1(Node a, Node b) {//对水的容积进行排序 
    if (a.a != b.a)
        return a.a > b.a;
    else
        return a.b > b.b;
}
int main() {
    n = read();

    for (int i = 1; i <= n; i += 1)
        c[i].a = read(), m += c[i].a;

    for (int i = 1; i <= n; i += 1)
        c[i].b = read(), sum += c[i].b;

    sort(c + 1, c + n + 1, cmp1);
    //初始化边界，当重量为 0  的时候选择 0 个瓶子 
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;

    for (int i = 1; i <= n; i += 1) {//枚举每个瓶子 
        for (int j = sum; j >= c[i].b; j -= 1) {
            if (f[j - c[i].b] + 1 < f[j] || (f[j - c[i].b] + 1 == f[j] && (ans[j - c[i].b] + c[i].a) > ans[j])) {
               //经典的 01 背包模型，同时将 ans （水的体积） 作为第二关键字进行比较 
			   f[j] = f[j - c[i].b] + 1;
                ans[j] = ans[j - c[i].b] + c[i].a;
            }
            if (j > m) {
                if (f[m] > f[j] || (f[m] == f[j] && ans[j] > ans[m])) {
                    f[m] = f[j];
                    ans[m] = ans[j];
                }
            }//如果水的体积超出上界，同样更新答案。 
        }
    }

    printf("%d %d\n", f[m], m - ans[m]);
    return 0;
}
```

真的不点一个赞再走吗 QAQ 。

---

## 作者：demon_yao (赞：17)

### 思路

- 对于第一问，应该可以很容易得出答案：应为可以无限次倒水，所以只要先排序，再取容积最大的$k$的个瓶子，使$\sum b[i]>=V_{tot}$即可。

- 对于第二问，~~显然~~是一个DP；仔细想一想就会知道，要使时间$T$最小化，我们只要使$V_{tot}-V_{nomove}$最大化就可以了。我们设$f[i][j][kk]$为前$i$个瓶子，取$kk$个瓶子，且总容积为$j$的最大$V_{nomove}$。这样就容易得出状态转移方程 $f[i][j][kk]=max(f[i-1][j][kk],f[i-1][j-b_i][kk]+a_i)$

- 最后用$V_{tot}-max(f[i][k])$就可以得到最终的$ans$。

这样就好了qwq。最后贴上code


```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=1e2+5;
struct node{int a,b;}c[N];
int n,ans,suma,sumb,k=0,f[N*N][N];
bool cmp(node x,node y){return x.b>y.b;}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){c[i].a=read();suma+=c[i].a;}
	for(int i=1;i<=n;i++) c[i].b=read();
	sort(c+1,c+n+1,cmp);
	while(sumb<suma) sumb+=c[++k].b;
	cout<<k<<" ";
	memset(f,128,sizeof(f)); f[0][0]=0;
	cout<<f[1][1]<<endl;
	for(int i=1;i<=n;i++)
		for(int j=sumb;j>=c[i].b;j--)
			for(int kk=1;kk<=k;kk++){
				f[j][kk]=max(f[j][kk],f[j-c[i].b][kk-1]+c[i].a);
			}
	for(int i=suma;i<=sumb;i++) ans=max(ans,f[i][k]);
	cout<<suma-ans;
	return 0;
}

```


---

## 作者：Skyjoy (赞：9)

这题其实就是一个简单的**01背包**问题

# 思路

- 首先我们看一看第一个问题。我们只需要把瓶子按容积排序，然后从大到小选择瓶子，直到容积大于等于水的体积就可以了。

- 重点在第二问。既然我们想要时间最少，那么我们就应该使移动的液体体积最小。但是这并不好处理，所以我们选择让不移动的液体的体积最大。

- 解决这样一个问题，我们可以使用**01背包**。用 $f_{i,j,k}$ 表示在前 $i$ 个瓶子中选择了 $j$ 个瓶子，总容积为 $k$ 的最大不移动的液体体积和。我们可以得到：

$$f_{i,j,k}=max(f_{i-1,j,k},f_{i-1,j-1,k-b_i}+a_i)$$

- 此时 $i$ 这一维是可以省掉的。最后我们枚举体积，找出最大的 $f_{j,k}$ ，再用体积和减去它，这就是答案了！

# 代码讲解

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int n,f[N][N*N],sum,tot,ans1,ans2;
struct bottle{
	int a,b;
}b[N];
bool cmp(bottle a,bottle b){
	return a.b>b.b;
}
int main(){
	n=read();
	memset(f,-0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++)b[i].a=read(),sum+=b[i].a;//计算体积和
	for(int i=1;i<=n;i++)b[i].b=read();
	sort(b+1,b+n+1,cmp);
	while(sum>tot)tot+=b[++ans1].b;
	printf("%d ",ans1);
	for(int i=1;i<=n;i++)for(int j=ans1;j;j--)for(int k=tot;k>=b[i].b;k--)f[j][k]=max(f[j][k],f[j-1][k-b[i].b]+b[i].a);//这一段是 dp ，注意 j 和 k 是要倒序枚举的
	for(int i=sum;i<=tot;i++)ans2=max(ans2,f[ans1][i]);//体积为 sum 到 tot 的答案都是可以的
	printf("%d",sum-ans2);//最终答案
	return 0;
}
```

---

## 作者：SSHhh (赞：6)

这道题的思路其实就是转化题意+01背包。

首先 k 应该是最好想的，随便乱搞都能求出来(自己想一想，肯定能想出来)。这里就提醒一句：按照容积从大到小排个序，之后暴力往前倒水就行了。

其次，倒来倒去，t 实际上就是移动了的部分的总体积和，t 最小就意味着没有移动的部分体积最大。那么 t 就完全可以用01背包求出来了。dp[i][j] 表示当前选了 i 个瓶子，总容积为 j 时的最小总体积和。那么用01背包的思路去想，把每一个 b[i] 当做价值，把每一个 a[i] 当做花费，直接做一遍01背包，就可以算出合法状态下没有移动的部分的最大体积和了。

那么还有一个细节问题：dp[i][j] 中的 j 应该枚举到几呢？实际上就是求 k 时枚举到的前若干位的容积之和 lim。因为取 k 个瓶子，总容积一定不会超过 lim，所以枚举答案时也是从水量总和(因为装下这么多水的总容积至少是这个水量总和)到 lim 就可以了。

最后说一句，不要以为 dp 是两维的，计算 dp 时就只枚举 i 和 j——因为 i 只有 1~k，所以必须枚举第三个变量表示当前是第几瓶才行(我当时就这样悲剧了)。还有，j一定要记得倒序枚举。

下面就直接上代码吧：

```cpp
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
int n,K,tot=0,ans,lim,a[105],b[105],dp[105][10005];
struct nod
{
    int a,b,c;
}t[105];
void update(int now)   //update 跟线段树毛线关系都没有，只是求第 now 位上的空余量而已
{
    t[now].c=t[now].b-t[now].a;
}
void pour(int i,int j)  //把第 i 瓶水倒进第 j 瓶水
{
    if(t[j].c>=t[i].a)  t[j].a+=t[i].a,t[i].a=0,update(j),update(i);
    else    t[i].a-=t[j].c,t[j].a=t[j].b,update(j),update(i);
}
bool cmp(nod i,nod j)   //按照容积从大到小排序
{
    return i.b==j.b?i.a>j.a:i.b>j.b;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)   cin>>a[i],t[i].a=a[i],tot+=a[i];
    for(int i=1;i<=n;i++)   cin>>b[i],t[i].b=b[i],update(i);
    sort(t+1,t+n+1,cmp);
    int head=1,tail=n;
    while(head<tail)
    {
        if(t[head].c>=t[tail].a)    pour(tail,head),tail--;
        else    pour(tail,head),head++;
    }   //暴力往前倒水
    K=tail; //简单粗暴的求出 K
    cout<<K<<" ";
    for(int i=1;i<=K;i++)   lim+=t[i].b;
    memset(dp,-12,sizeof(dp));dp[0][0]=0;
    for(int i=1;i<=n;i++)
        for(int j=K;j>=1;j--)
            for(int k=lim;k>=b[i];k--)
                dp[j][k]=max(dp[j][k],dp[j-1][k-b[i]]+a[i]);    //转移
    for(int i=lim;i>=tot;i--)   //tot~lim 这一段都有可能是答案
        ans=max(ans,dp[K][i]);
    cout<<tot-ans;  //别忘了 ans 只是合法状态下没有移动的部分的最大体积和，t=tot-ans
}
```

---

## 作者：lgswdn_SA (赞：5)

不看第二问，只看第一问，很显然为了取最少的瓶子我们应该把水全部倒到容量最大的几个瓶子中，所以我们贪心按容量排个序即可。

现在来看第二问，总的倒入时间=水的总体积-选定最后要倒入的瓶子的剩余的水的总体积。水的总体积是一个定值，所以我们要最小化最后要倒入的瓶子的剩余时间的水的总体积，也就是选定的瓶子的 $\sum a_i$。

设水的总体积为 $V$。现在题目转化为从 $n$ 个瓶子中选定 $t$ 个瓶子使得 $\sum b_i\ge V$，最小化 $\sum a_i$。这就是一个背包问题。$f(i,j,k)$ 表前 $i$ 个瓶子选了 $k$ 个瓶子且 $\sum b_i=j$ 的最大 $\sum a_i$。

转移方程：

$$
f(i,j,k)=\max \big(f(i-1,j,k),f(i-1,j-b_i,k-1)+a_i\big)
$$

空间优化用一下滚动数组或者背包的一个特别空间优化（省掉 $i$ 这维）

最后再用总体积减一下即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=a;i<=b;i++)
#define per(i,a,b) for(register int i=a;i>=b;i--)
using namespace std;
const int N=109;

int n,suma,K,sumb,f[10086][N],ans=0;
struct node {int a,b;}c[N];
bool cmp(const node&a,const node&b) {
	return a.b>b.b;
} 

int main() {
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",&c[i].a), suma+=c[i].a;
	rep(i,1,n) scanf("%d",&c[i].b);
	sort(c+1,c+n+1,cmp);
	while(sumb<suma) sumb+=c[++K].b;
	printf("%d ",K);
	memset(f,128,sizeof(f)); f[0][0]=0;
	rep(i,1,n) per(j,sumb,c[i].b) rep(k,1,K)
		f[j][k]=max(f[j][k],f[j-c[i].b][k-1]+c[i].a);
	rep(j,suma,sumb) ans=max(ans,f[j][K]);
	printf("%d",suma-ans);
	return 0;
}
```

---

## 作者：云岁月书 (赞：4)

Update By 2020/8/10 之前发现有一份代码贴错了，并润色了一下语句。

看到目前的题解使用了空间消耗 $O(n^3)$ 的方法，本人可以提供一个空间消耗为 $O(n^2)$ 的方法。

[题目链接](https://www.luogu.com.cn/problem/CF730J)

## 题目大意

给定 $n$ 个瓶子，其水量为 $a_i$,容积 $b_i$,每次转移 $1$ 单位的水消耗 $1$ 单位的代价。

求出一个最小的 $k$ 使得可以用 $k$ 个瓶子装下所有水，并求出此时最小代价 $t$ 。

## 题意分析：

首先最为一个有一定能力的 Oier,我觉得看出这道题是一个 DP 还是没问题的吧。

然后，仔细思考并不难发现，它长得很像一个背包问题。

如果它只要求 k 的话，它也确实是一个背包问题。

~~当然，贪心也可以求出 $k$。~~

贪心是一个显然的结论，这里就并不详细讨论了（~~毕竟又过不了这个题~~）。

但是要求 $k$ 和 $t$ ,我们就只能上动态规划。

## 思考过程：

先只考虑 $k$ ：

具体分析，对于最优的方案它一定**可以**满足一个性质（也是贪心正确的基础）：

**前 $k-1$ 个瓶子的水一定是装满的，最后一个瓶子可以装满也可以不装满，不存在被选中的空的瓶子。**

介于此，我们可以使用 $01$ 背包来解答这个问题。

回到原题，如果只求 $k$ 的话，本题可以直接套背包模板，但是多求一个最小的 $t$。

这似乎与上述的背包不能一起转移，但深入理解一下题意，不难发现一件事：

**$k$ 的转移实际上是与 $t$ 无关的！**

**$t$ 转移的第一要素实际上是 $k$ 。**

也就是说我们实际上是可以再求 $k$ 的时候顺便求出 $t$ 的(因为当 $k$ 变化时 $t$ 一定变化)。

于是经过上述一番~~周密~~的思考后我们可以得出一个状态转移方程：

记 $f[i],g[i]$ 数组分别为在总装水量为 $i$ 时的最小瓶子数与最小时间。

只有当 $f[j-b[i]]+1\geq f[j]$ 时我们才会有转移，转移分为两种情况：

- $f[j-b[i]]+1 = f[j]$ 时

  $$\large g[j] = Min(g[j],g[j-b[i]]+b[i]-a[i])$$

- $f[j-b[i]]+1 > f[j]$ 时

  $$\large f[j] = f[j-b[i]]+1,g[j]=f[j-b[i]]+b[i]-a[i]$$

记得将 $f$ 初始化为 $n$。

注意到水瓶装水不一定恰好装满，所以我们对初始总装水量的设定应该是 $(\sum\limits_{i=1}^{n}a_i)+Max(a_i)$ 。

我们记 $\sum\limits_{i=1}^{n}a_i = m$

答案在 $[m,m+100)$ 间。 

分析可知时间复杂度 $\Omicron(nm)$,空间复杂度 $\Omicron(n^2)$，可以过。

于是我们有了初版代码（错误代码）：

~~~c++
# include <cstdio>
# include <algorithm>
# define reg register
# define N 100
# define NN 10000
# define Gc getchar()//*/(SS == TT && (TT = (SS = BB) + fread(BB,1,1 << 15,stdin),TT == SS) ? EOF : *SS++)
char BB[1<<15],*SS=BB,*TT=BB;

inline int Read()
{
	register int x = 0;register char ch = Gc;
	
	while(ch < '0' || ch > '9') ch = Gc;
	
	while(ch <= '9' && ch >= '0'){x = x*10 + (ch^48);ch = Gc;}
	
	return x;
}

inline int Min(const int x,const int y){return x < y ? x : y;} 

int a[N + 5],b[N + 5],n,m,f[NN + 42],g[NN + 42],ans;

int main()
{
	n = Read();
	
	for(reg int i = 1; i <= n; ++i) m += (a[i] = Read());
	
	for(reg int i = 1; i <= n; ++i) b[i] = Min(Read(),m);
	
	m += 100; 
	
	for(reg int i = 1; i <= m; ++i) f[i] = n;
	
	for(reg int i = 1; i <= n; ++i)
		for(reg int j = m; j >= b[i] ; --j)
			if(f[j - b[i]]+1 < f[j])
			{
				f[j] = f[j-b[i]]+1;
				g[j] = g[j-b[i]]+b[i]-a[i];
			}
			else if(f[j-b[i]]+1 == f[j]) g[j] = Min(g[j],g[j-b[i]]+b[i]-a[i]);
			
	f[0] = n;//这里是为了方便，将ans指向的位置设为极大值。
			
	for(reg int i = m-100; i <= m; ++i)
		if(f[ans] > f[i]) ans = i;
		else if(f[ans] == f[i] && g[ans] > g[i]) ans = i;
	
	printf("%d %d",f[ans],g[ans]);
	
	return 0; 
}
~~~



当然你以为这样就过了吗，实际上如果你按照上述方程写了交上去的话只有 $30$ 分，因为 DP 中最难确定的一个东西搞错了——**边界条件**。

在 $j > m$ 的转移中，实际上我们多装了并不存在的水，所以步数没有问题，但是 $t$ 却有问题了。

~~我至今不知道这个边界条件有问题的程序是怎么算出的比标准答案还优的分配过程，讲道理它给出的应该更大的。~~

解决的方式很简单，讲所有 $j > m$ 得转移单独讨论，于是得到了真正完整的转移方程：

当 $j \leq m$ 时：

- $f[j-b[i]]+1 = f[j]$ 时

$$\large g[j] = Min(g[j],g[j-b[i]]+b[i]-a[i])$$

- $f[j-b[i]]+1 > f[j]$ 时

$$\large f[j] = f[j-b[i]]+1,g[j]=f[j-b[i]]+b[i]-a[i]$$

当 $j > m$ 时：

- $f[j-b[i]]+1 = f[j]$ 时

$$\large g[j] = Min(g[j],g[j-b[i]]+b[i]-a[i] + m - j)$$

- $f[j-b[i]]+1 > f[j]$ 时

$$\large f[j] = f[j-b[i]]+1,g[j]=f[j-b[i]]+b[i]-a[i] + m - j$$

综上，本题就没有大问题了。

AC 代码 $1$：

~~~c++
# include <cmath>
# include <cstdio>
# include <algorithm>
# define reg register
# define N 100
# define NN 10000
# define mod 998244353 
# define INF 0x7f7f7f7f7f7f7f7f
# define Gc getchar()//*/(SS == TT && (TT = (SS = BB) + fread(BB,1,1 << 15,stdin),TT == SS) ? EOF : *SS++)
char BB[1<<15],*SS=BB,*TT=BB;

inline int Read()
{
	register int x = 0;register char ch = Gc;
	
	while(ch < '0' || ch > '9') ch = Gc;
	
	while(ch <= '9' && ch >= '0'){x = x*10 + (ch^48);ch = Gc;}
	
	return x;
}

inline int Min(const int x,const int y){return x < y ? x : y;} 
inline int ABS(const int x){return x < 0 ? ~x+1 : 0x3f3f3f3f3f;}

int a[N + 5],b[N + 5],n,m,f[NN + 42],g[NN + 42],ans;

int main()
{
	n = Read();
	
	for(reg int i = 1; i <= n; ++i) m += (a[i] = Read());
	
	for(reg int i = 1; i <= n; ++i) b[i] = Min(Read(),m);
	
	for(reg int i = m+100; i >= 1; --i) f[i] = n;
	
	for(reg int i = 1; i <= n; ++i)
		for(reg int j = m+100; j >= b[i] ; --j)
			if(f[j - b[i]]+1 < f[j])
			{
				if(j <= m)
				{
					f[j] = f[j-b[i]]+1;
					g[j] = g[j-b[i]]+b[i]-a[i];
				}
				else
				{
					f[j] = f[j-b[i]]+1;
					g[j] = g[j-b[i]]+b[i] - a[i] + m-j;
				}
			}
			else if(f[j-b[i]]+1 == f[j])
			{
				if(j <= m) g[j] = Min(g[j],g[j-b[i]]+b[i]-a[i]);
				else g[j] = Min(g[j],g[j-b[i]]+b[i] - a[i] + m-j);
			}
			
	f[0] = n;
			
	for(reg int i = m+100; i >= m; --i)
		if(f[ans] > f[i]) ans = i;
		else if(f[ans] == f[i] && g[ans] > g[i]) ans = i;
	
	printf("%d %d",f[ans],g[ans]);
	
	return 0; 
}
~~~

对于 $j > m$ 的边界问题，我们可以从另一个角度优化它。

之前我们对 $g$ 数组的定义是最小时间，所以我们转移有边界问题，但是如果我们将 $g$ 数组定义改为可以装下 $j$ 单位的水时无需转移便已被装入容器中的水。

在这个定义下我们有状态转移方程如下：

-  $f[j-b[i]]+1 = f[j]$ 时

  $$\large g[j] = Min(g[j],g[j-b[i]]+a[i])$$

- $f[j-b[i]]+1 > f[j]$ 时

  $$\large f[j] = f[j-b[i]]+1,g[j]=f[j-b[i]]+a[i]$$

因为 $g$ 数组变了，所以答案统计中 $t$ 应该是 $m-g[ans]$。

AC 代码 $2$：

~~~c++
# include <cmath>
# include <cstdio>
# include <algorithm>
# define reg register
# define N 100
# define NN 10000

inline int Max(const int x,const int y){return x > y ? x : y;} 

int a[N + 5],b[N + 5],n,m,f[NN + 42],g[NN + 42],ans;

int main()
{
	scanf("%d",&n);
	
	for(reg int i = 1; i <= n; ++i) scanf("%d",&a[i]);
	
	for(reg int i = 1; i <= n; ++i) scanf("%d",&b[i]);
	
	for(reg int i = 1; i <= n; ++i) m += a[i];
	
	for(reg int i = m+100; i >= 1; --i) f[i] = n;
	
	for(reg int i = 1; i <= n; ++i)
		for(reg int j = m+100; j >= b[i] ; --j)
			if(f[j - b[i]]+1 < f[j])
				{
					f[j] = f[j-b[i]]+1;
					g[j] = g[j-b[i]]+a[i];
				}
			else if(f[j-b[i]]+1 == f[j]) g[j] = Max(g[j],g[j-b[i]]+a[i]);
			
	f[0] = n;
			
	for(reg int i = m+100; i >= m; --i)
		if(f[ans] > f[i]) ans = i;
		else if(f[ans] == f[i] && g[ans] < g[i]) ans = i;
	
	printf("%d %d",f[ans],m - g[ans]);
	
	return 0; 
}
~~~

谈一下时空复杂度，这种方法空间上是绝对比 $O(n^3)$ 的二维 DP 要更优的，时间复杂度虽然都是 $O(nm)$ ，但落在实际上却大不相同。

我同学的代码用的代码二的方程，没开氧气时间跑到了 $810ms$ ，我本人常数巨大的代码一和代码二没开氧气分别用了 $1.10s$ 和 $1.23s$ 。

而二维 DP 截止 $2020/8/10$ 最快的是一个 $1.25s$ ,普遍的是 $2s-5s$ 左右。

~~为什么最后还有几个明显不是本题的AC记录和没测试点的 AC 记录~~。

下面是 AC 记录。

[同学小常数代码](https://www.luogu.com.cn/record/36664762)

[我本人常数巨大的代码 $1$](https://www.luogu.com.cn/record/36734448)

[我本人常数巨大的代码 $2$](https://www.luogu.com.cn/record/36740898)

---

## 作者：Yeji_ (赞：1)

## 前言
其实这题并没有紫题这么难 ~~（普遍提高）~~

## 做法
第一问可以直接通过贪心求

只需要将数据从小到大排一遍，证明，我也不会 ~~（尴尬）~~

然后第2问直接在里面跑多重背包。

其实模板大家都会打，但是很多人不会做，是因为不能将题目中给出的量，准确的转换为模板

所以这种能力大家需要根据做题来领会

直接给代码：
```cpp
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<iostream>
#define inf 2147483647
using namespace std;
int ff[101][10011],n,s1,s2,ans,num;   
struct node
{
    int soda,val;
}f[10005];
bool cmp(node a,node b)
{
    if (a.val!=b.val)
        return a.val>b.val;
    else
        return a.soda>b.soda;
}
int main()
{
	cin>>n;
    for (int i=1;i<=n;i++)
    {
        cin>>f[i].soda;
        s1+=f[i].soda;
    }
    for (int i=1;i<=n;i++)
    {
        cin>>f[i].val;
        s2+=f[i].val;
    }
    int x=s1;
    sort(f+1,f+1+n,cmp);
    while (1)
    {
        x-=f[++num].val;
        if (x<=0)
            break;
    }
    memset(ff,-0x7f,sizeof ff);
    ff[0][0]=0;
    for (int i=1;i<=n;i++)
        for (int j=s2;j>=f[i].val;j--)
            for (int k=1;k<=num;k++)
                ff[k][j]=max(ff[k][j],ff[k-1][j-f[i].val]+f[i].soda);
    for (int i=s1;i<=s2;i++)
        ans=max(ans,ff[num][i]);
    printf("%d %d",num,s1-ans);
}
```


---

## 作者：Gorenstein (赞：0)

**题意概述**

- $n$ 个瓶子，第 $i$ 个瓶子原有水 $a_i$，容量为 $b_i$；
- 倒 $1$ 单位水需要花 $1$ 单位时间，求用最少的瓶子装下所有水的瓶子个数 $x$，以及将所有水倒入 $x$ 个瓶中所花的最小时间；
- $1\leq n\leq 100$

**问题转化与解决**

第一问很简单罢，给所有的瓶子排序，然后从大到小选就行了。

考虑第二问。比较显然的是求倒水时间就是求倒水的量。而总的水量是不变的，所以最小化倒的水量就是最大化不倒的水量。

略加思考可以想到，不倒的水量就是最重要倒入的那 $x$ 个瓶子原本就有的水量。因此问题就转化为了 _选取 $x$ 个瓶子，需要使瓶子原有的水最多，同时满足这些瓶子容量总和大于总水量_ 。

这就是一个裸的 $01$ 背包了。因为我们关心选取的瓶子个数，一次你增加一维 $k$ 来表示。定义 $f[i][j][k]$ 表示前 $i$ 个瓶子中，总容量为 $j$，选取 $k$ 个瓶子的最大原有水量。转移方程

$$
f[i][j][k]=\max(f[i-1][j][k],f[i-1][j-b_i][k-1]+a_i)
$$

然后按照 $01$ 背包的惯常方法倒序循环，去掉 $i$ 这维。边界条件 $f[0][0]=0$。

```cpp
f[0][0]=0;
for(int i=1;i<=n;i++)
	for(int j=s2;j>=c[i].b;j--)
		for(int k=tot;k>0;k--)
			f[j][k]=max(f[j][k],f[j-c[i].b][k-1]+c[i].a);
```

最终我们的目标状态是能够装下所有水并且瓶子数为 $x$ 的方案中最大的不移动水量。设总水量为 $V_w$，容量前 $x$ 大的瓶子容量和 $V_b$，则目标状态即 $\min\limits_{V_w\leq k\leq V_b}\big\{f[k][x]\big\}$。

记 $ans$ 为上面得出的最打原有水量，则最终答案为 $V_w-ans$。

这样我们这题就做完了。

---

## 作者：AC自动机 (赞：0)

首先发现最开始的一步肯定是贪心，按容量sort一遍可以得到第一个答案，然后稍微转化一下题意，就可以发现，转化后的提议是这个样子：从n个瓶子里面选出num个，使得这num个瓶子的容积之和要大于水的体积，并且当时间最短时，一定有这num个瓶子里的水体积和最大，就可以发现是一个01背包问题。

dp[i][j]表示选了i个瓶子，一共的容积为j的时候，这i个瓶子里水的最大值。由此可得dp方程

dp[j][k]=max(dp[j][k],dp[j-1][k-b[i].v]+b[i].r);

小细节
差点被坑死在这里，按照容量枚举k的时候一定要倒着枚举，不然就成完全背包了2333333。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct nod{
    int r;
    int v;
};
nod b[105];
inline int cmp(nod x,nod y){
    return x.v>y.v;
}
int dp[105][20000];
int main(){
    int n;
    cin>>n;
    int rest=0;
    for(register int i=1;i<=n;i++){
        cin>>b[i].r;
        rest+=b[i].r;
    }
    for(register int i=1;i<=n;i++){
        cin>>b[i].v;
    }
    sort(b+1,b+n+1,cmp);  
    memset(dp,-1,sizeof(dp)); dp[0][0]=0;
    int num=-1,tot=0;
    for(register int i=1;i<=n;i++){
        tot+=b[i].v;
        if(tot>=rest&&num==-1)num=i;
    }
    cout<<num<<endl;
    for(register int i=1;i<=n;i++){ //xuan di ji ge
        for(register int k=tot;k>=b[i].v;k--){
            for(register int j=1;j<=num;j++){  //xuan le ji ge
                if(dp[j-1][k-b[i].v]!=-1){
                    dp[j][k]=max(dp[j][k],dp[j-1][k-b[i].v]+b[i].r);
                    //cout<<dp[j-1][k-b[i].v]<<' '<<b[i].r<<endl;
                    //cout<<i<<' '<<j<<' '<<k<<endl<<endl;
                }
            }
        }   
    }
    // while(1){
    //  int x,y;
    //  cin>>x>>y;
    //  cout<<dp[x][y]<<endl;
    // }
    int ans=-1;
    for(register int i=rest;i<=tot;i++){
        ans=max(ans,dp[num][i]);
    }
    //cout<<tot<<endl;
    cout<<rest-ans<<endl;
}
```

---

## 作者：Trimsteanima (赞：0)

## $\mathcal{Solution}$

 [$\mathtt{blogs}$](https://www.cnblogs.com/wjnclln/p/11650476.html)

第一问要求出最少需要的瓶子很简单，用贪心做，把 $n$ 瓶水的最大容量排序，要使用的瓶子越大越好，第二问可以用 $dp$ 做，$dp[i][j]$ 可以表示选了 $i$ 个瓶子，容量为 $j$ 时，水的最大值。
$$
dp[i][j] = max(dp[i][j], dp[i - 1][j - b[k]] + a[k])
$$

## $\mathcal{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 110;

int n, sum, sum1, sum2, num, f[N][N * N];

struct Node {
    int a, b;
} a[N];

inline int read() {
	int x = 0, k = 1; char c = getchar();
	for (; c < 48 || c > 57; c = getchar()) k ^= (c == '-');
	for (; c >= 48 && c <= 57; c = getchar()) x = x * 10 + (c ^ 48);
	return k ? x : -x;
}

inline bool cmp (Node a, Node b) {
    return a.b > b.b || (a.b == b.b && a.a > b.b);
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++)
        a[i].a = read(), sum += a[i].a;
    for (int i = 1; i <= n; i++)
        a[i].b = read(), sum1 += a[i].b;
    std::sort(a + 1, a + 1 + n, cmp);
    for (sum2 = sum; sum > 0; sum -= a[++num].b) ;
    printf("%d ", num);
    memset(f, -0x3f, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = sum1; j >= a[i].b; j--)
            for (int k = 1; k <= num; k++)
                f[k][j] = std::max(f[k][j], f[k - 1][j - a[i].b] + a[i].a);
    int ans = -1;
    for (int i = sum2; i <= sum1; i++)
        ans = std::max(ans, f[num][i]);
    printf("%d\n", sum2 - ans);
    return 0;
}
```

---


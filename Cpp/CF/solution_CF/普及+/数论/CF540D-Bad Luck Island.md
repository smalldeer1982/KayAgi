# Bad Luck Island

## 题目描述

The Bad Luck Island is inhabited by three kinds of species: $ r $ rocks, $ s $ scissors and $ p $ papers. At some moments of time two random individuals meet (all pairs of individuals can meet equiprobably), and if they belong to different species, then one individual kills the other one: a rock kills scissors, scissors kill paper, and paper kills a rock. Your task is to determine for each species what is the probability that this species will be the only one to inhabit this island after a long enough period of time.

## 样例 #1

### 输入

```
2 2 2
```

### 输出

```
0.333333333333 0.333333333333 0.333333333333
```

## 样例 #2

### 输入

```
2 1 2
```

### 输出

```
0.150000000000 0.300000000000 0.550000000000
```

## 样例 #3

### 输入

```
1 1 3
```

### 输出

```
0.057142857143 0.657142857143 0.285714285714
```

# 题解

## 作者：Strelitzia (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF540D)

---

水紫，考场上二十分钟构思加写完 ~~又调了十分钟，还是花太长时间了~~。

考虑如何定义 $\text{dp}$，我们可以看到这个 $\text{r,s,p}$ 非常小，$\Theta$($n^3$) 完全没问题。

根据数据我们可以得到一个三维的 $dp_{i,j,k}$，表示剩下 $\text{i}$ 个 $\text{r}$，$\text{j}$ 个 $\text{s}$，$\text{k}$ 个 $\text{p}$ 的概率。

那么，对于单独一种，例如 $r$ 种，它这个种族的存活的概率 $\sum_{1}^{r} dp_{i,0,0}$。

考虑递推式：

设 $tot = i * j + j * k + k * i$，也就是所有相遇的事件。

$\operatorname{r}$ 对 $\operatorname{s}$，$\operatorname{s}$ 人数减少一人，相遇概率为 $i * j / tot$，

$\operatorname{s}$ 对 $\operatorname{p}$，
$\operatorname{p}$ 人数减少一人，相遇概率为 $j * k / tot$，

$\operatorname{p}$ 对 $\operatorname{r}$，$\operatorname{r}$ 人数减少一人，相遇概率为 $k * i / tot$。

根据上述条件，可堆出转移式，注意边界条件。

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
    T f = 1;x = 0;char s = getchar();
    while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
    while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
    x *= f;
}
template<typename T>void print(T x) {
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 105;

int r,s,p;
double dp[maxn][maxn][maxn],rwin,swin,pwin;

int main () {
	scanf ("%d %d %d",&r,&s,&p);
	dp[r][s][p] = 1.0;
	for (int i = r ; i >= 0 ; -- i) {
		for (int j = s ; j >= 0 ; -- j) {
			for (int k = p ; k >= 0 ; -- k) {
				double tot = i * j + j * k + i * k;
				if (i && j) dp[i][j - 1][k] += dp[i][j][k] * i * j / tot;
				if (j && k) dp[i][j][k - 1] += dp[i][j][k] * j * k / tot;
				if (k && i) dp[i - 1][j][k] += dp[i][j][k] * i * k / tot;
				if (i && !j && !k) rwin += dp[i][j][k];
				if (!i && j && !k) swin += dp[i][j][k];
				if (!i && !j && k) pwin += dp[i][j][k]; 
			}
		}
	}
	printf("%.12f %.12f %.12f",rwin,swin,pwin);
	return 0;
}
```

---

## 作者：寒冰大大 (赞：4)

[CF540D](https://www.luogu.com.cn/problem/CF540D)

显而易见地联想到石头剪刀布。

$f[i][j][k]$表示当前有i个剪刀，j个布，k个石头的概率

题目要求留下单一种族，用剪刀举例，那么就是$f[i][0][0],i \in [1,r]$的和。

同时考虑状态转移，显然没有平局情况，因此每次i,j,k中必然有一个要-1

同时出现i,j,k中有一个-1的总概率应该是$i*j+j*k+k*i$（这个应该不用解释）

同时剪刀赢布应该是i*j的（不需要解释）

考虑边界，显然赢家和输家都必须有一个才能玩这一局，比如剪刀(i)要赢的话，必须保证有一个以上的布($j\ge1$)才能赢。

另外肯定有学校的ppt中转移写的是=而不是加等于，但是举一个i,j,k（这里暂时不考虑边界），那么就有$[i+1,j,k],[i,j+1,k],[i,j,k+1]$可以转移，所以要写成+=。

这个时候代码就很好写出来了：

```cpp
#include<towenjian.h>

using namespace std;

double f[110][110][110],rwin=0.0,swin=0.0,pwin=0.0;
int r,s,p,tot;

int main()
{
    scanf("%d %d %d",&r,&s,&p);
    int tot;
    f[r][s][p]=1.0;
    int i,j,k;
    for(i=r;i>=0;i--)
    for(j=s;j>=0;j--)
    for(k=p;k>=0;k--)
    {
        tot=i*j+j*k+k*i;
        if(i&&k) f[i-1][j][k]+=1.0*f[i][j][k]*k*i/tot;
        if(j&&i) f[i][j-1][k]+=1.0*f[i][j][k]*i*j/tot;
        if(k&&j) f[i][j][k-1]+=1.0*f[i][j][k]*j*k/tot;
        if(!j&&!k&&i) rwin+=f[i][j][k];
        if(!i&&!k&&j) swin+=f[i][j][k];
        if(!i&&!j&&k) pwin+=f[i][j][k]; //如果看不懂上面的讲解可以看代码来理解
    }
    printf("%.9lf %.9lf %.9lf",rwin,swin,pwin);
}
```



---

## 作者：Trimsteanima (赞：4)

一看就是DP题~~（很水的一道紫题）~~

设$dp[i][j][k]$为留下$i$个$r$族的人，死去$j$个$s$族的人，死去$k$个$p$族的人的概率（跟其他的题解有点差别，但本质相同）。

```cpp
#include <bits/stdc++.h>
using namespace std;
double dp[101][101][101];
int a, b, c;
int main() {
    scanf("%d%d%d", &a, &b, &c);
    for (int i = 1; i <= 100; i++)
        for (int j = 1; j <= 100; j++) {
            dp[i][j][0] = 1;
            for (int k = 1; k <= 100; k++)
                dp[i][j][k] += (i * j * dp[i][j - 1][k] + j * k * dp[i][j][k - 1] + k * i * dp[i - 1][j][k]) / (i * j + j * k + k * i);
        }
    printf("%.12lf %.12lf %.12lf\n", dp[a][b][c], dp[b][c][a], dp[c][a][b]);
    return 0;
}
```

---

## 作者：wsy_jim (赞：4)

# CF540D Bad Luck Island 题解

## 0x01 题意

在孤岛上有三种人，分别有 $r,s,p$ 个， 每两个人相遇的概率相等，相遇时 $r$ 吃 $s$，$s$ 吃 $p$，$p$ 吃 $r$，分别求最后剩下一种种族的概率。

## 0x02 解

概率 $DP$。

因为 $r,s,p$ 都很小，所以我们可以开一个三维数组记录现在的状态，设 $f[i][j][k]$ 表示发生有 $i$ 个 $r$ 种族的人被吃，$j$ 个 $s$ 种族的人被吃，$k$ 个 $p$ 种族的人被吃这个事件的概率。

考虑由一个状态能够转移到哪些状态，于是我们可以得出以下结论：

对于一个已经求出的 $f[i][j][k]$：

- 当下一次是 $r$ 和 $s$ 相遇，可以转移到 $f[i][j+1][k]$；

- 当下一次是 $s$ 和 $p$ 相遇，可以转移到 $f[i][j][k+1] $；

- 当下一次是 $r$ 和 $p$ 相遇，可以转移到 $f[i+1][j][k]$；

只要求出相遇的概率累加就行了。

当转移到只剩一个种族时，要统计答案。

## 0x03 码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=110;
template<typename T>
inline void read(T &x){
    x=0;bool flag=0;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') flag=1;
    for(;isdigit(c);c=getchar()) x=x*10+(c^48);
    if(flag) x=-x;
}

int r,s,p;
double f[N][N][N],ansr=0,anss=0,ansp=0;

signed main(){

	read(r),read(s),read(p);
	f[0][0][0]=1.0;
	for(int i=0;i<=r;i++){
		for(int j=0;j<=s;j++){
			for(int k=0;k<=p;k++){
				double a=r-i,b=s-j,c=p-k,tot=a*b+b*c+c*a;
				if(a&&b) f[i][j+1][k]+=f[i][j][k]*a*b/tot;
				if(b&&c) f[i][j][k+1]+=f[i][j][k]*b*c/tot;
				if(c&&a) f[i+1][j][k]+=f[i][j][k]*a*c/tot;
				if(a&&!b&&!c) ansr+=f[i][j][k];
				if(!a&&b&&!c) anss+=f[i][j][k];
				if(!a&&!b&&c) ansp+=f[i][j][k];
			}
		}
	}
	
	printf("%.9lf %.9lf %.9lf\n",ansr,anss,ansp);
	
    return 0;
}
```



---

## 作者：q1436177712 (赞：2)

既然没有大佬写题解那本蒟蒻就厚颜无耻地写(~~水~~)一(~~经~~)下(~~验~~)吧

题目要求算出个种人单独留下的存活率

因为n,m,p的范围极小，

那么就可以方便地设3位dp状态dp[i][j][k]表示剩余i个石头，j个剪刀，k个布的概率

当前的相遇的总情况数为i*j+i*k+j*k


如果遇到的两个相同的人不发生变化转移可可以忽略


如果遇到不同的人 各自的情况分别为i*j,i*k,j*k

转移方以石头剪刀相遇为例转移方程就为i*jdp[i][j-1][k] += (i*j)/(i*j+i*k+j*k)*dp[i][j][k]

最后算出各自在其他人为0时自己从1到最大的概率累加起来

输出即可

# 代码
```c
#include<bits/stdc++.h> 
using namespace std;
#define ll long long
#define C getchar()-48
inline ll read()
{
    ll s=0,r=1;
    char c=C;
    for(;c<0||c>9;c=C) if(c==-3) r=-1;
    for(;c>=0&&c<=9;c=C) s=(s<<3)+(s<<1)+c;
    return s*r;
} 
const int N=1e2+10;
int n,m,p;
double dp[N][N][N];
int main()
{
	n=read(),m=read(),p=read();
	dp[n][m][p]=1.0;
	for(int i=n;i>=0;i--)
	for(int j=m;j>=0;j--)
	for(int o=p;o>=0;o--)
	{
		if(i&&j) dp[i][j-1][o]+=(1.0*i*j/(i*j+j*o+i*o))*dp[i][j][o];
		if(j&&o) dp[i][j][o-1]+=(1.0*j*o/(i*j+j*o+i*o))*dp[i][j][o];
		if(i&&o) dp[i-1][j][o]+=(1.0*i*o/(i*j+j*o+i*o))*dp[i][j][o];
	}	
	double ed1=0,ed2=0,ed3=0;
	for(int i=1;i<=n;i++) ed1+=dp[i][0][0];
	for(int j=1;j<=m;j++) ed2+=dp[0][j][0];
	for(int o=1;o<=p;o++) ed3+=dp[0][0][o];
	printf("%.10f %.10f %.10f\n",ed1,ed2,ed3);
    return 0;
}
```

---

## 作者：pipi (赞：2)

 **首先**，这是一道比较**的紫题的  ~~(丰富想象空间)~~
   
我们先设 f（a,b,c）为剩下a个r族的概率，b个s族的概率，c个p族的概率  
  
  ![](https://cdn.luogu.com.cn/upload/pic/51504.png)
  
  上面就是递推的式子，从而推出↓
  ![](https://cdn.luogu.com.cn/upload/pic/51508.png )
  而这个简单的等式就可以用来递归的，但是最重要的递归边界呢？
  ![](https://cdn.luogu.com.cn/upload/pic/51509.png)显而易见吧  
  最后在把各个种族的概率累加一下  
  **下面是一些细节**：  
  1、当a>r||b>s||c>p时要return 0；~~（因为是达不到的）~~  
  2、需要判断一下，要是除以零就尴尬了~~  
  3、乘除的时候要注意下形式，免得C++给自动下取整了  
  4、因为是递归，避免重复计算，要记搜一下  
  5、直接用%lf输出只会有6位，加一个 .12 才行  
   ~~** 我才不会说这些都是我犯过的错误**~~  
   下面就是代码（里面有一些小注释）↓
   ```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
double r,s,p,qq,aa,bb,cc,ff[110][110][110];
int a,b,c;
double f(int a,int b,int c){
	if(ff[a][b][c]) return ff[a][b][c];//记搜 
	if(a > r || b > s || c > p) return 0;//防RE 
	if(a == r && b == s && c == p) return 1;//递归边界 
	double v=0,ll,kk;
	if(b!=0||c!=0){
		ll =(a + 1) * c;
		kk =(((a+1) * b) + ((a + 1) * c) + (b * c));
		v += f(a+1,b,c) * (ll / kk);
	}
	if(a!=0||c!=0){
		ll =(b + 1) * a;
		kk =(((b+1) * a) + ((b + 1) * c) + (a * c));
		v += f(a,b+1,c) * (ll / kk);
	}
	if(b!=0||a!=0){
		ll = (c + 1) * b;
		kk = (((c+1) * b) + ((c + 1) * a) + (b * a));
		v += f(a,b,c+1) * (ll / kk);
	}
	ff[a][b][c] = v;
	return v;
}
int main(){
	scanf("%lf%lf%lf",&r,&s,&p);
	for(int i=r;i>0;i--) aa+=f(i,0,0);//上下累加都可以的 
	for(int i=s;i>0;i--) bb+=f(0,i,0);
	for(int i=p;i>0;i--) cc+=f(0,0,i);
	printf("%.12lf %.12lf %.12lf",aa,bb,cc);
}
```

---

## 作者：Fading (赞：1)

一个船新思路

设$f[i][j][k][id]$为$RSP$分别有$i,j,k$个，最后只剩下$id$这个种族的概率。$(id=0(R),1(S),2(P))$

有转移

```
if (i!=0&&j!=0) f[i][j][k][id]+=(((double)(i*j)/(double)(i*j+j*k+k*i)))*f[i][j-1][k][id];
if (j!=0&&k!=0) f[i][j][k][id]+=(((double)(j*k)/(double)(i*j+j*k+k*i)))*f[i][j][k-1][id];
if (k!=0&&i!=0) f[i][j][k][id]+=(((double)(k*i)/(double)(i*j+j*k+k*i)))*f[i-1][j][k][id];
```

左边是枚举出现两种不同种族的概率。

有一个坑点，就是如果有两个相同的种族他们是不会互相伤害的，所以不可以算到概率里！我被坑了很久。。。

所以我写了记忆化搜索。。。

```cpp
#include<bits/stdc++.h>
using namespace std;
double f[102][102][102][3];
int R,S,P,id;
inline double dfs(int R,int S,int P,int id){
    if (R>0&&S==0&&P==0&&id==0) return 1.0;
    if (R==0&&S>0&&P==0&&id==1) return 1.0;
    if (R==0&&S==0&&P>0&&id==2) return 1.0;
    if (f[R][S][P][id]>0) return f[R][S][P][id];
    f[R][S][P][id]=0;
    if (R!=0&&S!=0) f[R][S][P][id]+=(((double)(R*S)/(double)(R*S+S*P+P*R)))*dfs(R,S-1,P,id);
    if (S!=0&&P!=0) f[R][S][P][id]+=(((double)(S*P)/(double)(R*S+S*P+P*R)))*dfs(R,S,P-1,id);
    if (P!=0&&R!=0) f[R][S][P][id]+=(((double)(P*R)/(double)(R*S+S*P+P*R)))*dfs(R-1,S,P,id);
    return f[R][S][P][id];
}
int main(){
    cin>>R>>S>>P;
    for (int i=0;i<=R;i++){
        for (int j=0;j<=S;j++){
            for (int k=0;k<=P;k++){
                for (int ii=0;ii<=2;ii++){
                    f[i][j][k][ii]=-1.0;
                }
            }
        }
    }
    printf("%.12lf %.12lf %.12lf",dfs(R,S,P,0),dfs(R,S,P,1),dfs(R,S,P,2));
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

~~其实我一开始看到是 ```*1900``` 的期望 dp，吓得够呛。~~

## 思路

### 1. dp 定义：

首先发现这道题没法贪心，那就 dp。参考数据范围，大概是 $O(n^3)$ 做法。那么就按照我们要求的设 dp。令 $dp_{(i,j,k)}$ 表示还剩 $i$ 个 $r$ 族人，$j$ 个 $s$ 族人，$k$ 个 $p$ 族人的时候的概率。那么输出要求是剩下单种族人，那么显而易见另外两个族人得是 0。

于是我们分别输出 $\sum\limits_{i=1}^r dp_{(i,0,0)}$，$\sum\limits_{j=1}^s dp_{(0,j,0)}$ 和 $\sum\limits_{k=1}^p dp_{(0,0,k)}$ 就可以了。这个可以在 dp 的时候一块求出来。

### 2. 状态转移方程

转移方程还是比较好想的。每次肯定死考虑死哪一个族的人。限制是，如果你要这个族里一个人死，那么**这个族必须有人，而且吃他的那个族也必须有人**。

于是得到了这样的代码（假设满足上述限制）

$dp_{(i-1,j,k)} = dp_{(i-1,j,k)} + dp_{(i,j,k)} \times p1$

$dp_{(i,j-1,k)} = dp_{(i,j-1,k)} + dp_{(i,j,k)} \times p2$

$dp_{(i,j,k-1)} = dp_{(i,j,k-1)} + dp_{(i,j,k)} \times p3$

其中，$p1$，$p2$，$p3$ 表示两个族碰面的几率：假设三个族分别剩下 $i,j,k$ 人，那么 $r,s$ 两族碰面概率就是 $\dfrac{i \times j}{i\times j + i \times k + j \times k}$，也就是上面转移方程里的 $p1$。$p2,p3$ 以此类推。

最后按题目要求求和输出即可。注意保留至少 7 位小数，我被坑了一次。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
double dp[105][105][105],sum1,sum2,sum3;
int main()
{
	int r,s,p; scanf("%d%d%d",&r,&s,&p);
	dp[r][s][p]=1.0;
	for(int i=r;i>=0;i--)
		for(int j=s;j>=0;j--)
			for(int k=p;k>=0;k--)
			{
				double tot=i*j+j*k+i*k;
				if(i && j) dp[i][j-1][k]+=dp[i][j][k]*i*j/tot;
				if(j && k) dp[i][j][k-1]+=dp[i][j][k]*j*k/tot;
				if(i && k) dp[i-1][j][k]+=dp[i][j][k]*i*k/tot;
				if(i && !j && !k) sum1+=dp[i][j][k];
				if(!i && j && !k) sum2+=dp[i][j][k];
				if(!i && !j && k) sum3+=dp[i][j][k]; 
			}
				
	printf("%.10lf %.10lf %.10lf",sum1,sum2,sum3);
	return 0;
}

```

$$\large{\text{THE END}}$$

$$\text{Thanks for reading.}$$

---

## 作者：pomelo_nene (赞：0)

还是不是很懂。。。$1900$ 是怎么评成紫的啊。

显然定义 $dp_{i,j,k}$ 为剩下 $i$ 个 $\operatorname{R}$，$j$ 个 $\operatorname{S}$，$k$ 个 $\operatorname{P}$。刷表看起来有点麻烦，我们直接把当前状态转移到可能的状态。

分类讨论：

- $\operatorname{R}$ 与 $\operatorname{S}$ 相遇，$\operatorname{S}$ 减少一个。条件为 $i,j > 1$；   
- $\operatorname{R}$ 与 $\operatorname{P}$ 相遇，$\operatorname{R}$ 减少一个。条件为 $i,k > 1$；   
- $\operatorname{S}$ 与 $\operatorname{P}$ 相遇，$\operatorname{P}$ 减少一个。条件为 $j,k > 1$。

考虑计算有多少种可能。我们一共有 $i$ 个 $\operatorname{R}$，$j$ 个 $\operatorname{S}$，$k$ 个 $\operatorname{P}$，$\operatorname{R}$ 和 $\operatorname{S}$ 相遇的状态共有 $i \times j$ 种，其它相遇方案显然，于是这道题就做出来了。

```cpp
#include<bits/stdc++.h>
using namespace std;
double dp[105][105][105];
int r,s,p;
int main(){
	scanf("%d %d %d",&r,&s,&p);
	dp[r][s][p]=1;
	for(int i=r;~i;--i)
	{
		for(int j=s;~j;--j)
		{
			for(int k=p;~k;--k)
			{
				double pro=i*j+j*k+i*k;
				if(i && k)	dp[i-1][j][k]+=dp[i][j][k]*(double)i*(double)k/pro;
				if(i && j)	dp[i][j-1][k]+=dp[i][j][k]*(double)i*(double)j/pro;
				if(j && k)	dp[i][j][k-1]+=dp[i][j][k]*(double)j*(double)k/pro;
			}
		}
	}
	double rr=0,ss=0,pp=0;
	for(int i=1;i<=r;++i)	rr+=dp[i][0][0];
	for(int i=1;i<=s;++i)	ss+=dp[0][i][0];
	for(int i=1;i<=p;++i)	pp+=dp[0][0][i];
	printf("%.10f %.10f %.10f",rr,ss,pp);
	return 0;
}
```

---


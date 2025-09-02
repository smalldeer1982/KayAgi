# [NOISG 2022 Qualification] L-Board

## 题目背景

Lord Pooty 有一个 $n \times m$ 的整数棋盘 $A$。他希望在棋盘上画一个 L 型区域，并且希望覆盖的数字总和最大。L 型区域可以旋转 $4$ 种方向，且每一边不一定完整（可以是一条直线）。

## 题目描述

给定一个 $n \times m$ 的棋盘 $A$，你需要选择棋盘上的三个点 $(x_1, y_1)$, $(x_2, y_1)$, $(x_1, y_2)$，使得以下公式的值 $V$ 最大化：

$$
V = \sum_{i=\min(x_1,x_2)}^{\max(x_1,x_2)} A_{i,y_1} + \sum_{j=\min(y_1,y_2)}^{\max(y_1,y_2)} A_{x_1,j} - A_{x_1,y_1}
$$

## 说明/提示

【样例解释】

对于样例 $1$，选择点 $(1,1)$, $(2,1)$, $(1,2)$，覆盖的数字为 $8, 3, 4$，总和为 $15$。  

对于样例 $2$，选择点 $(1,3)$, $(1,5)$, $(1,3)$，形成一条直线，覆盖的数字为 $8, -2, 9$，总和为 $15$。

【数据范围】

- $1 \leq n, m \leq 1000$
- $-10^9 \leq A_{i,j} \leq 10^9$

| 子任务编号 | 分值 | 额外限制条件             |
| :--------: | :--: | :----------------------: |
| $1$        | $5$  | $1 \leq n, m \leq 2$    |
| $2$        | $10$ | $n = 1$                 |
| $3$        | $15$ | $1 \leq n, m \leq 100$  |
| $4$        | $15$ | $1 \leq n, m \leq 300$  |
| $5$        | $25$ | $0 \leq A_{i,j} \leq 10^9$ |
| $6$        | $30$ | 无额外限制               |

## 样例 #1

### 输入

```
2 2
8 1
3 4```

### 输出

```
15```

## 样例 #2

### 输入

```
1 8
-2 -1 8 -2 9 0 -2 1```

### 输出

```
15```

# 题解

## 作者：zhhgdm (赞：3)

## 题目大意

从一个棋盘选取一个 L 形、Γ 形、Ⴈ 形或 ⅃ 形的区域，使得区域的中数字的和最大。

**注意，这个区域的不能是下图这样的：**

![Invalid L-shape example](https://cdn.luogu.com.cn/upload/image_hosting/xpaos1p8.png)

**因为他的“粗”是 2。**


## 题目分析

既然“粗”只能是 1，那就相当于找到一个交点，从它的上或下选择一条直线（可以不选），再从左或右也选一条直线，使得拼接后数字值和最大，那肯定是选最长的两条直线喽。那么，我们就可以用[最大子段和](https://www.luogu.com.cn/problem/P1115)的方式向四个方向求以其为开头（结尾）的直线的最大和。

例（向上）：

``` cpp
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        pre[i][j]=max(0,pre[i][j-1])+a[i][j];
        // 如果发现前面 <0 了，就丢弃（这条直线只要我一个），否则求让我和前面连上
    }
}
```
# 完整代码

``` cpp
#include<bits/stdc++.h>
#define int long long // 十年 OI 一场空，不开 long long 见祖宗。
using namespace std;
int a[1005][1005];
int pre[1005][1005][4];
signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }

    // 向上

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            pre[i][j][0]=max(0ll,pre[i][j-1][0])+a[i][j]; // max 不支持两个参数类型不同，写成 0 喜提 CE。
        }
    }

    // 向下

    for(int i=1;i<=n;i++){
        for(int j=m;j>=1;j--){
            pre[i][j][1]=max(0ll,pre[i][j+1][1])+a[i][j];
        }
    }

    // 向左

    for(int j=1;j<=m;j++){
        for(int i=1;i<=n;i++){
            pre[i][j][2]=max(0ll,pre[i-1][j][2])+a[i][j];
        }
    }

    // 向右

    for(int j=m;j>=1;j--){
        for(int i=n;i>=1;i--){
            pre[i][j][3]=max(0ll,pre[i+1][j][3])+a[i][j];
        }
    }

    int maxn=LLONG_MIN; // 别忘了刚才 #define int long long 了
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            maxn=max({
                maxn,
                pre[i][j][0]+pre[i][j][2]-a[i][j], // ⅃ 形
                pre[i][j][1]+pre[i][j][2]-a[i][j], // Γ 形
                pre[i][j][0]+pre[i][j][3]-a[i][j], // ⅃ 形
                pre[i][j][1]+pre[i][j][3]-a[i][j] // Ⴈ 形
            });
        }
    }
    cout<<maxn;
}
```

---

## 作者：qhr2023 (赞：3)

## 思路

容易发现是线性动态规划，答案可以拆解成最大子段和问题，我们考虑分类讨论。

我们先分别预处理出 $(i,j)$ 向左、向右、向上、向下且以 $(i,j)$ 结尾的最大连续子段和，分别记作 $l[i][j]$、$r[i][j]$、$up[i][j]$、$dn[i][j]$，记初始数组为 $a[i][j]$，再分类讨论求解即可。

## 预处理

这是板子，[最大子段和问题](https://www.luogu.com.cn/problem/P1115)。

* 向左最大连续子段和。

当前状态都是有左边转移过来的，所以按 $j$ 正序枚举枚举，转移就是常规的最大子段和，下面的三种情况就类似这种。

```cpp
l[i][j]=max(a[i][j], l[i][j-1]+a[i][j]);
```

* 向右最大连续子段和。

按 $j$ 倒序枚举枚举。

```cpp
r[i][j]=max(a[i][j], r[i][j+1]+a[i][j]);
```

* 向上最大连续子段和。

按 $i$ 正序枚举枚举。

```cpp
up[i][j]=max(a[i][j], up[i-1][j]+a[i][j]);
```

* 向下最大连续子段和。

按 $i$ 到序枚举枚举。

```cpp
dn[i][j]=max(a[i][j], up[i+1][j]+a[i][j]);
```

## sol

* $x_1 < x_2$，$y_1 < y_2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/heviedhp.png)

此时，答案就是向下和向右的最大子段和之和，因为 $(x_1,y_1)$ 这点算了两次，所以再减掉1次。我们枚举 $x_1$ 和 $y_1$，答案即 $r[x_1][y_1]+dn[x_1][y_1]-a[i][j]$ 的最大值，下面类似。

* $x_1 < x_2$，$y_1 > y_2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/kr7wpm13.png)

此时答案即 $l[x_1][y_1]+dn[x_1][y_1]-a[i][j]$ 的最大值。

* $x_1 > x_2$，$y_1 < y_2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/4s4yj55k.png)

此时答案即 $r[x_1][y_1]+up[x_1][y_1]-a[i][j]$ 的最大值。

* $x_1 > x_2$，$y_1 > y_2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/5tke7b5d.png)

此时答案即 $l[x_1][y_1]+up[x_1][y_1]-a[i][j]$ 的最大值。

* 特殊情况，答案是一条直线，此时答案即 $l[x_1][y_1]+r[x_1][y_1]-a[i][j]$ 的最大值。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1005;
long long n, m, a[N][N], ans=-1e9, l[N][N], r[N][N], up[N][N], dn[N][N];
int main () {
	cin >> n >> m;
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=m; ++j)
			cin >> a[i][j];
	for (int i=1; i<=n; ++i) {
		for (int j=1; j<=m; ++j) 
			l[i][j]=max(a[i][j], l[i][j-1]+a[i][j]);
		for (int j=m; j>=1; --j)
			r[i][j]=max(a[i][j], r[i][j+1]+a[i][j]),
			up[i][j]=max(a[i][j], up[i-1][j]+a[i][j]);
	}
	for (int i=n; i>=1; --i)
		for (int j=1; j<=m; ++j)
			dn[i][j]=max(a[i][j], dn[i+1][j]+a[i][j]);
	for (int i=1; i<=n; ++i) 
		for (int j=1; j<=m; ++j)
			ans=max(ans, max({r[i][j]+dn[i][j],
							l[i][j]+dn[i][j],
							r[i][j]+up[i][j], 
							l[i][j]+up[i][j], 
							l[i][j]+r[i][j]})-a[i][j]);
	cout << ans;
	return 0;
}
```

---

## 作者：summ1t (赞：1)

省流：前缀和，前缀和，还是前缀和。

考虑枚举 $(i,j)$，发现会将整个棋盘划分成四个部分。

行列是互不影响的，考虑怎么找到行的最大值。发现就是 $i$ 左边的一个后缀和的最大值减去以 $i+1$ 结尾的后缀和，以及 $i$ 右边的一个前缀和的最大值减去以 $i-1$ 结尾的前缀和，两个值取 $\max$ 即可。对于列的计算同理。

所以先对行列分别做一遍前缀和，后缀和，接下来只需要找到前缀和的后缀最大值，后缀和的前缀最大值就好了。

代码细节不是很多，分清变量和 $n,m$ 就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rd read()
#define gc getchar()
#define dg(ch) isdigit(ch)
#define _mul(x) ((x<<3)+(x<<1))
#define ll long long
#define pb push_back
#define FOR(i,j,k) for(int i=j;i<=k;i++)
#define ROF(i,j,k) for(int i=j;i>=k;i--)
int read(){int x=0,f=1;char ch=gc;while(!dg(ch)){if(ch=='-')f=-1;ch=gc;}while(dg(ch))x=_mul(x)+(ch^48),ch=gc;return x*f;}
const int N=1010;
const ll INF=1e18;
int n,m,a[N][N];ll ans=-INF,sp1[N][N],sp2[N][N],sf1[N][N],sf2[N][N],sp1mx[N][N],sp2mx[N][N],sf1mx[N][N],sf2mx[N][N];
int main(){
	n=rd,m=rd;FOR(i,1,n) FOR(j,1,m) a[i][j]=rd;
	memset(sp1mx,-0x3f,sizeof(sp1mx)),memset(sp2mx,-0x3f,sizeof(sp2mx));
	memset(sf1mx,-0x3f,sizeof(sf1mx)),memset(sf2mx,-0x3f,sizeof(sf2mx));
	FOR(i,1,n) FOR(j,1,m) sp1[i][j]=sp1[i][j-1]+a[i][j];//行前缀
	FOR(i,1,n) ROF(j,m,1) sf1[i][j]=sf1[i][j+1]+a[i][j];//行后缀
	FOR(j,1,m) FOR(i,1,n) sp2[i][j]=sp2[i-1][j]+a[i][j];//列前缀
	FOR(j,1,m) ROF(i,n,1) sf2[i][j]=sf2[i+1][j]+a[i][j];//列后缀
	FOR(i,1,m) FOR(j,1,m) sf1mx[i][j]=max(sf1mx[i][j-1],sf1[i][j]);//行后缀的前缀最大值
	FOR(i,1,m) ROF(j,m,1) sp1mx[i][j]=max(sp1mx[i][j+1],sp1[i][j]);//行前缀的后缀最大值
	FOR(j,1,m) FOR(i,1,n) sf2mx[i][j]=max(sf2mx[i-1][j],sf2[i][j]);//列后缀的前缀最大值
	FOR(j,1,m) ROF(i,n,1) sp2mx[i][j]=max(sp2mx[i+1][j],sp2[i][j]);//列前缀的后缀最大值
	FOR(i,1,n) FOR(j,1,m){
		ll res1=sf1mx[i][j],res2=sp1mx[i][j],res3=sf2mx[i][j],res4=sp2mx[i][j];
		ll tmp1=max(res1-sf1[i][j+1],res2-sp1[i][j-1]),tmp2=max(res3-sf2[i+1][j],res4-sp2[i-1][j]);
		ans=max(ans,tmp1+tmp2-a[i][j]);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：ben090302 (赞：1)

每个点的答案其实是显然的，必然是往左的最大子段和和往右的取较大值、上下取较大值，于是考虑预处理出一个点往左边扩展的最大子段和和往右的，以及往上往下的，都是非常显然的动态规划可以解决的。

此处以“以 $(i,j)$ 为右端点的最大子段和”为例，记为 $L_{i,j}$，我们按列从小往大循环，每个点都有两种选择，继承左边那个点的子段和加上自己的权值或者不继承，就只要自己的权值，代码实现如下：

```
for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
		L[i][j]=max(a[i][j],a[i][j]+L[i][j-1]); 
	}
}
```

类似的定义我们可以写出另外三个，预处理总代码如下：

```
for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
		L[i][j]=max(a[i][j],a[i][j]+L[i][j-1]); 
	}
}
for(int i=1;i<=n;i++){
	for(int j=m;j>=1;j--){
		R[i][j]=max(a[i][j],a[i][j]+R[i][j+1]); 
	}
}
for(int j=1;j<=m;j++){
	for(int i=1;i<=n;i++){	
		U[i][j]=max(a[i][j],a[i][j]+U[i-1][j]); 
	}
}
for(int j=1;j<=m;j++){
	for(int i=n;i>=1;i--){	
		D[i][j]=max(a[i][j],a[i][j]+D[i+1][j]); 
	}
}
```

答案统计上文提到了，枚举 `L` 的拐点，向左右扩展的较大值加上上下的减去 $a_{i,j}$ 即可，复杂度 $O(nm)$。

全代码实现如下：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+5;
int L[N][N];
int R[N][N];
int U[N][N];
int D[N][N];
int n,m;
int a[N][N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			L[i][j]=max(a[i][j],a[i][j]+L[i][j-1]); 
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=m;j>=1;j--){
			R[i][j]=max(a[i][j],a[i][j]+R[i][j+1]); 
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){	
			U[i][j]=max(a[i][j],a[i][j]+U[i-1][j]); 
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=n;i>=1;i--){	
			D[i][j]=max(a[i][j],a[i][j]+D[i+1][j]); 
		}
	}
	int ans=-1e18;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int sum=-a[i][j];
			sum+=max(L[i][j],R[i][j]);
			sum+=max(U[i][j],D[i][j]);
			ans=max(ans,sum);
		}
	}
	cout<<ans;
}
```

---

## 作者：末然Ender (赞：1)

# 题解：P11293 [NOISG2022 Qualification] L-Board

建议降黄，橙都能接受。

## 思路

我们记一个点 $a_{i,j}$ 往上面延伸能到达的数最大和为 $shang_{i,j}$，往下面能到达的最大和为 $xia_{i,j}$，往左 $zuo_{i,j}$，往右 $you_{i,j}$，题目其实是在求下面这个式子的最大值

$$a_{i,j}+\max \begin{cases}shang_{i-1,j}+zuo_{i,j-1} \\ shang_{i-1,j}+you_{i,j+1}\\xia_{i+1,j}+zuo_{i,j-1} \\ xia_{i+1,j}+you_{i,j+1}\\\end{cases}$$

然后我们就将问题转化为如何求这四个上下左右的数组了。

私以为有一些 OI 基础敢来做绿题的人应该都能想到（如果没有是我冒犯了），对每一行、每一列跑dp，以 $zuo_{i,j}$ 举例，其转移为 $zuo_{i,j}=\max\{0,a_{i,j}+zuo_{i,j-1}\}$，时间复杂度是 $O(n\cdot m)$ 的完全能过。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar getchar_unlocked
template<typename T>
void read(T& x){x=0;char ch=getchar();long long f=1;while(!isdigit(ch)){if(ch=='-')f*=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}x*=f;}
template<typename T,typename... Args>
void read(T& first,Args&... args){read(first);read(args...);}
template<typename T>
void write(T arg){T x=arg;if (x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
template<typename T,typename... Args>
void write(T arg,Args... args){write(arg);if(sizeof...(args) !=0){putchar(' ');write(args...);}}
const int N=1200;
ll n,m;
ll a[N][N];
ll shang[N][N],xia[N][N],zuo[N][N],you[N][N];
int main(){
	read(n,m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			read(a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			zuo[i][j]=max(0ll,zuo[i][j-1]+a[i][j]);
		}
		for(int j=m;j>=1;j--){
			you[i][j]=max(0ll,you[i][j+1]+a[i][j]);
		}
	}
	
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			shang[j][i]=max(0ll,shang[j-1][i]+a[j][i]);
		}
		for(int j=n;j>=1;j--){
			xia[j][i]=max(0ll,xia[j+1][i]+a[j][i]);
		}
	}
	ll ans=-100000000000ll;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			ans=max(ans,zuo[i][j-1]+shang[i-1][j]+a[i][j]);
			ans=max(ans,zuo[i][j-1]+xia[i+1][j]+a[i][j]);
			ans=max(ans,you[i][j+1]+shang[i-1][j]+a[i][j]);
			ans=max(ans,you[i][j+1]+xia[i+1][j]+a[i][j]);
			
		}
	}
	write(ans);
	return 0;
}
```

---

## 作者：sintle (赞：1)

## 题目链接

- [洛谷 P11293 [NOISG2022 Qualification] L-Board](https://www.luogu.com.cn/problem/P11293)

## 解题思路

考虑维护四个数组 $u_{i,j},d_{i,j},l_{i,j},r_{i,j}$ 分别表示以位置 $(i,j)$ 为起点，在其上、下、左、右四个方向上，一定选择该点的最大区间和，显然可以 DP 维护。

时间复杂度为 $O(nm)$

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
int n , m;
long long a[N][N] , u[N][N] , d[N][N] , l[N][N] , r[N][N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= m ; j++)
        {
            cin >> a[i][j];
            u[i][j] = max(u[i - 1][j] , 0ll) + a[i][j];
            l[i][j] = max(l[i][j - 1] , 0ll) + a[i][j];
        }
    for(int i = n ; i >= 1 ; i--)
        for(int j = m ; j >= 1 ; j--)
        {
            d[i][j] = max(d[i + 1][j] , 0ll) + a[i][j];
            r[i][j] = max(r[i][j + 1] , 0ll) + a[i][j];
        }
    long long ans = -0x3f3f3f3f;
    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= m ; j++)
        {
            ans = max(ans , max(l[i][j] , r[i][j]) + max(u[i][j] , d[i][j]) - a[i][j]);
        }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：Lian_zy (赞：0)

题目已经说的很清楚了，在矩阵中选出一个 L 形状的矩形，使得覆盖的和最大。

不妨枚举这个 L 型的拐点，然后计算从这个拐点出发随便向两个方向拓展，得到的最大值。

如果两个方向恰好构成一条直线也没关系（比如一个向左一个向右），是符合题目要求的。

但是直接这样暴力是 $O(n^3)$ 的，只能获得 $45$ 分的好成绩。

我们可以用 dp 优化这个代码。$u_{i,j},d_{i,j},l_{i,j},r_{i,j}$ 分别表示 $(i,j)$ 向四个方向拓展得到的最大价值，然后枚举 L 型拐点更新答案就好了。

然后转移的话就是个最大子段和板子，具体请看代码： 

code:

``` cpp
#include<bits/stdc++.h>
#define N 1005
#define ll long long
#define mod 1000000007
using namespace std;

ll n,m,ans,a[N][N],u[N][N],d[N][N],l[N][N],r[N][N]; 
int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%lld",a[i]+j);
			l[i][j]=max(l[i][j-1],0ll)+a[i][j];
			u[i][j]=max(u[i-1][j],0ll)+a[i][j];
		}
	}
	for(int i=n;i;i--){
		for(int j=m;j;j--){
			r[i][j]=max(r[i][j+1],0ll)+a[i][j];
			d[i][j]=max(d[i+1][j],0ll)+a[i][j];
		}
	}
	ans=-1e18;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			ans=max(ans,l[i][j]+u[i][j]-a[i][j]);
			ans=max(ans,u[i][j]+d[i][j]-a[i][j]);
			ans=max(ans,r[i][j]+d[i][j]-a[i][j]);
			ans=max(ans,u[i][j]+r[i][j]-a[i][j]);
			ans=max(ans,l[i][j]+d[i][j]-a[i][j]);
			ans=max(ans,l[i][j]+r[i][j]-a[i][j]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：HPXXZYY (赞：0)

$\texttt{\color{blue}{[Analysis]}}$

很显然，对于单个点来说，它的第一项对答案的贡献就是往左最大连续子段和和往右最大连续子段和的较大值，第二项对答案的贡献就是往上的最大连续子段和和往下的最大连续子段和的较大值，第三项是本身。

于是把问题转化为求最大连续子段和。

当然这个问题可以用一个经典的 dp 解决。但是对于一个退役的大学生来说，问题应该怎么复杂化怎么来。

连续和的问题一般都可以转化为前缀和。以往左的最大连续子段和为例，设 $l_{i,j}$ 表示 $(i,j)$ 往左的前缀和，即：

$$l_{i,j} = \sum\limits_{k=1}^{j} a_{i,j}$$

那么从 $(i,j)$ 往左的最大连续子段和就是 $l_{i,j}$ 减去最小的 $l_{i,k}(0 \leq k <j)$，其中 $l_{i,0}$ 定义为 $0$。

注意代码实现的细节，挺多细节需要考虑的。

$\color{blue}{\text{[Code]}}$

```cpp
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=read();
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			Left[i][j]=Left[i][j-1]+a[i][j];
		for(int j=m;j>=1;j--)
			Right[i][j]=Right[i][j+1]+a[i][j];
		
		minn[0]=0;
		for(int j=1;j<=m;j++)
			minn[j]=min(minn[j-1],Left[i][j-1]);
		for(int j=1;j<=m;j++)
			Left[i][j]-=minn[j];
		
		minn[m+1]=0;
		for(int j=m;j>=1;j--)
			minn[j]=min(minn[j+1],Right[i][j+1]);
		for(int j=m;j>=1;j--)
			Right[i][j]-=minn[j];
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++)
			Up[i][j]=Up[i-1][j]+a[i][j];
		for(int i=n;i>=1;i--)
			Down[i][j]=Down[i+1][j]+a[i][j];
		
		minn[0]=0;
		for(int i=1;i<=n;i++)
			minn[i]=min(minn[i-1],Up[i-1][j]);
		for(int i=1;i<=n;i++)
			Up[i][j]-=minn[i];
		
		minn[n+1]=0;
		for(int i=n;i>=1;i--)
			minn[i]=min(minn[i+1],Down[i+1][j]);
		for(int i=n;i>=1;i--)
			Down[i][j]-=minn[i];
	}
	
	ans=-1e18;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			ckmax(ans,max(Up[i][j],Down[i][j])+max(Left[i][j],Right[i][j])-a[i][j]);
	
	printf("%lld",ans);
	
	return 0;
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

考虑枚举 L 的角，然后四个方向扩展。

扩展需要求和，所以每行每列前后缀和一下。

然后这样是 $O(n^4)$ 的好像，需要把扩展变成 $O(1)$ 的。

显然前缀和求 $[l,r]$ 是 $s_r-s_{l-1}$ 现在让我们找 $l$。

那就找 $s_{l-1}$ 最小的就能保证 $[l,r]$ 最大。

然后维护一下前后缀最小值即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
constexpr int N=1001;
int n,m,a[N][N],presc[N][N],presl[N][N],sufsc[N][N],sufsl[N][N],
prenc[N][N],prenl[N][N],sufnc[N][N],sufnl[N][N],ans=-0x3f3f3f3f3f3f3f3fll;
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>a[i][j];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            presc[i][j]=presc[i][j-1]+a[i][j];
        for(int j=m;j>=1;j--)
            sufsc[i][j]=sufsc[i][j+1]+a[i][j];
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++)
            presl[i][j]=presl[i][j-1]+a[j][i];
        for(int j=n;j>=1;j--)
            sufsl[i][j]=sufsl[i][j+1]+a[j][i];
    }
    memset(prenc,0,sizeof(prenc)),
    memset(prenl,0,sizeof(prenl)),
    memset(sufnc,0,sizeof(sufnc)),
    memset(sufnl,0,sizeof(sufnl));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            prenc[i][j]=min(prenc[i][j-1],presc[i][j]);
        for(int j=m;j>=1;j--)
            sufnc[i][j]=min(sufnc[i][j+1],sufsc[i][j]);
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++)
            prenl[i][j]=min(prenl[i][j-1],presl[i][j]);
        for(int j=n;j>=1;j--)
            sufnl[i][j]=min(sufnl[i][j+1],sufsl[i][j]);
    }/*
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    		cerr<<prenc[i][j]<<" \n"[j==m];
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    		cerr<<sufnc[i][j]<<" \n"[j==m];
    for(int i=1;i<=m;i++)
    	for(int j=1;j<=n;j++)
    		cerr<<prenl[i][j]<<" \n"[j==m];
    for(int i=1;i<=m;i++)
    	for(int j=1;j<=n;j++)
    		cerr<<sufnl[i][j]<<" \n"[j==m];
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    		cerr<<presc[i][j]<<" \n"[j==m];
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    		cerr<<sufsc[i][j]<<" \n"[j==m];
    for(int i=1;i<=m;i++)
    	for(int j=1;j<=n;j++)
    		cerr<<presl[i][j]<<" \n"[j==m];
    for(int i=1;i<=m;i++)
    	for(int j=1;j<=n;j++)
    		cerr<<sufsl[i][j]<<" \n"[j==m];*/
    for(int i=1,tmp;i<=n;i++)
        for(int j=1;j<=m;j++){
        	int w=presc[i][j-1]-prenc[i][j-1],
                x=sufsc[i][j+1]-sufnc[i][j+1],
                y=presl[j][i-1]-prenl[j][i-1],
                z=sufsl[j][i+1]-sufnl[j][i+1];
            tmp=a[i][j]+max({w+y,w+z,x+y,x+z});
            ans=max(ans,tmp);
        }
    cout<<ans;
    return 0;
}
```

---

## 作者：Infinite_Loop (赞：0)

# P11293
## 前言
刷 dp 时遇到的第一题，还是挺水的。建议降~~黄~~。
## 题意
给定一个 $n \times m$ 的数组 $A$，要你求出 L 型区域总和的最大值。
## 思路
考虑求出每个点向上、向下、向左、向右的直线区域的最大值，可以用数组模拟。然后对于每个点，求出该点的 L 型区域中的最大值，并求出答案。

需要注意的：

- 要开 long long。

然后我们就可以通过这道题了！
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e3+10;
int n,m,a[N][N],b[2][N][N],c[2][N][N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
		cin>>a[i][j];
	for(int i=1;i<=n;i++)b[1][i][0]=b[0][i][m+1]=-1e18;
	for(int i=1;i<=m;i++)c[1][0][i]=c[0][n+1][i]=-1e18;
	for(int i=1;i<=n;i++){
		for(int j=m;j>=1;j--)b[0][i][j]=max(a[i][j],b[0][i][j+1]+a[i][j]);
		for(int j=1;j<=m;j++)b[1][i][j]=max(a[i][j],b[1][i][j-1]+a[i][j]);
	}
	for(int i=1;i<=m;i++){
		for(int j=n;j>=1;j--)c[0][j][i]=max(a[j][i],c[0][j+1][i]+a[j][i]);
		for(int j=1;j<=n;j++)c[1][j][i]=max(a[j][i],c[1][j-1][i]+a[j][i]);
	}
	int ans=-1e18;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		ans=max(ans,max(b[0][i][j],b[1][i][j])+max(c[0][i][j],c[1][i][j])-a[i][j]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Qerucy (赞：0)

简要题意：在图中找一个 L 型区域，使得区域覆盖的元素和最大。

$O(n^2m^2)$ 的暴力很好想，对于图中的任意两个点对，都会产生至多两个 L 型区域的贡献，于是我们枚举 $(x_2,y_1)$ 和 $(x_1,y_2)$，找到这 $(nm)^2$ 个可能的 L 型区域的和，取它们的最大值便是答案，前缀和优化即可。

然后我们考虑优化，我们发现，枚举每个 L 型区域的 $(x_1,y_1)$，它的和的最大值是以 $(x_1,y_1)$ 为端点的竖直方向的最大子串和加上水平方向的最大子串和。

因为 $a_{{x_1},{y_1}}$ 会被算重复，所以我们要再减去 $a_{{x_1},{y_1}}$。即我们设 $fx_{i,j}$ 为以 $(i,j)$ 为端点的水平方向的最大子串，设 $fy_{i,j}$ 为以 $(i,j)$ 为端点的竖直方向的最大子串，则：

$$ans=\max(fx_{i,j}+fy_{i,j}-a_{i,j})$$

由于方向不限，所以我们要上下左右分别做 $4$ 次，最后还要考虑区域为一条线段的情况，此时不用减去 $a_{i,j}$。

时间复杂度 $O(nm)$。

---

## 作者：Genius_Star (赞：0)

动态规划基础题，建议黄。

### 思路：

容易发现是动态规划题，考虑维护 $s_{0/1/2/3, i, j}$ 分别表示：

- $0$：必选 $(i, j)$，从左边选过来的最大和。

- $1$：必选 $(i, j)$，从右边选过来的最大和。

- $2$：必选 $(i, j)$，从上边选过来的最大和。

- $3$：必选 $(i, j)$，从下边选过来的最大和。

则状态转移方程有：

$$s_{0, i, j} = \max(s_{0, i, j - 1},0) + a_{i,j} \\ s_{1, i, j} = \max(s_{1, i, j + 1}, 0) + a_{i, j} \\ s_{2, i, j} = \max(s_{2, i - 1, j}, 0) + a_{i, j} \\
s_{3, i, j} = \max(s_{3, i + 1, j}, 0) + a_{i, j}$$

然后考虑枚举这个 L 型的转折点 $(x, y)$，以此点为 L 型转折点的最大和是：

$$\max(s_{0, x, y}, s_{1, x, y}) + \max\{s_{2, i - 1, j}, s_{3, i + 1, j}, 0\}$$

时间复杂度为 $O(N^2)$。

### 思路：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it = l; it != r; ++it) (*it)=x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1,s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i,l,r) for(register int i = l; i <= r; ++i)
#define _For(i,l,r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 1010;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
ll ans = -1e18;
int n, m;
ll a[N][N], s[4][N][N];
bool End;
int main(){
	n = read(), m = read();
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= m; ++j){
			a[i][j] = read();
			s[0][i][j] = max(s[0][i][j - 1], 0ll) + a[i][j];
			s[2][i][j] = max(s[2][i - 1][j], 0ll) + a[i][j]; 
		}
	}
	for(int i = n; i >= 1; --i){
		for(int j = m; j >= 1; --j){
			s[1][i][j] = max(s[1][i][j + 1], 0ll) + a[i][j];
			s[3][i][j] = max(s[3][i + 1][j], 0ll) + a[i][j];
		}
	}
	for(int i = 1; i <= n; ++i)
	  for(int j = 1; j <= m; ++j)
		ans = max(ans, max(s[0][i][j], s[1][i][j]) + max({s[2][i - 1][j], 0ll, s[3][i + 1][j]}));
	write(ans);
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---


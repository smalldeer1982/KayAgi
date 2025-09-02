# IOI 饅頭 (IOI Manju)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2014ho/tasks/joi2014ho2

Incredible Okashi Inc. は「途方もなくおいしいお菓子 (incredible okashi)」を製作している会社である．ここでは略して IOI 社と呼ぶ．IOI 社は特製の IOI 饅頭を作ったので，それを販売することになった．IOI 社は $ M $ 種類の饅頭を $ 1 $ 個ずつ作った．作られた $ M $ 個の饅頭はすべて同じ大きさであるが，ひとつひとつ異なる味なので価格は様々であり，$ i $ 番目 ($ 1\ \leqq\ i\ \leqq\ M $) の饅頭の価格は $ P_i $ 円である．

ところで，あなたは Just Odd Inventions 社を知っているだろうか？ この会社の業務は「ただ奇妙な発明 (just odd inventions)」をすることである．ここでは略して JOI 社と呼ぶ．IOI 社は，饅頭を詰めるための高級な箱を JOI 社に発注することになった．JOI 社の製作する饅頭用の箱は $ N $ 種類あり，$ j $ 番目 ($ 1\ \leqq\ j\ \leqq\ N $) の箱は最大で $ C_j $ 個の饅頭を詰められる大きさであり，販売価格は $ E_j $ 円である．これらの $ N $ 種類の箱のうちの何種類か ($ 0 $ 種類以上 $ N $ 種類以下) を $ 1 $ 個ずつ発注し，饅頭をそれらの箱に詰め分けてセットで販売することになった．各饅頭セットの価格は，それに含まれる饅頭の価格の合計である．

すべての饅頭セットが売れるとした場合，IOI 社が得ることができる利益の最大値はいくらだろうか．ここで利益とは，販売した饅頭セットの価格の合計から，発注した箱の価格の合計を引いた値である．なお，箱に詰めなかった饅頭については，IOI 社のスタッフがおいしくいただくため，利益には影響しないものとする．

## 说明/提示

### 課題

各饅頭の価格と，各箱の大きさと価格が与えられたとき，IOI 社が得ることができる利益の最大値を求めるプログラムを作成せよ．

- - - - - -

### 制限

すべての入力データは以下の条件を満たす．

- $ 1\ \leqq\ M\ \leqq\ 10\,000 $．
- $ 1\ \leqq\ N\ \leqq\ 500 $．
- $ 1\ \leqq\ P_i\ \leqq\ 10\,000 $ ($ 1\ \leqq\ i\ \leqq\ M $)．
- $ 1\ \leqq\ C_j\ \leqq\ 10\,000 $ ($ 1\ \leqq\ j\ \leqq\ N $)．
- $ 1\ \leqq\ E_j\ \leqq\ 10\,000 $ ($ 1\ \leqq\ j\ \leqq\ N $)．

### 小課題

#### 小課題 1 \[25 点\]

$ N\ \leqq\ 10 $ を満たす．

#### 小課題 2 \[35 点\]

$ C_j\ \leqq\ 10 $ ($ 1\ \leqq\ j\ \leqq\ N $) を満たす．

#### 小課題 3 \[40 点\]

追加の制限はない．

- - - - - -

### Sample Explanation 1

この例では，$ 1 $ 番目の箱 ($ 100 $ 円) と $ 2 $ 番目の箱 ($ 120 $ 円) を発注し，たとえば $ 1 $ 番目の箱に $ 1 $ 番目の饅頭と $ 2 $ 番目の饅頭を詰めて $ 180\ +\ 160\ =\ 340 $ 円のセットとして販売，$ 2 $ 番目の箱に $ 3 $ 番目の饅頭と $ 4 $ 番目の饅頭を詰めて $ 170\ +\ 190\ =\ 360 $ 円のセットとして販売すると，IOI 社の利益は $ 700\ -\ 220\ =\ 480 $ 円となる． - - - - - -

### Sample Explanation 2

\- - - - - -

## 样例 #1

### 输入

```
4 3
180
160
170
190
2 100
3 120
4 250```

### 输出

```
480```

## 样例 #2

### 输入

```
2 2
1000
2000
1 6666
1 7777```

### 输出

```
0```

## 样例 #3

### 输入

```
10 4
200
250
300
300
350
400
500
300
250
200
3 1400
2 500
2 600
1 900```

### 输出

```
450```

# 题解

## 作者：Marsrayd (赞：7)

## [题目传送门](https://www.luogu.com.cn/problem/AT923)
## 前置芝士
- 基础 dp 模型：背包问题。
- ```sort``` 的使用方法（应该没人手写排序吧qwq）。
- 前缀和的使用。

~~看，前置芝士谁都会，这题一定一道大水题吧。~~

## $\texttt{Solution}$
### 题意简述：
给定 $m$ 个卖价为 $P_i$ 的馒头，$n$ 个容量为 $C_i$ 价格为 $E_i$ 的箱子（不能重复购买）用来装馒头卖，求最大收益。
### 思路：
看到题面“你可以购买一些箱子，并往里面装入馒头，但装入数量不能超过箱子的容量之和。这些馒头将被出售并获得相应的钱数。”这句话有没有很眼熟？我们将箱子的容量 $C_i$ 看作背包问题中物品的重量，将箱子的价格 $E_i$ 看作背包问题中物品的价值，这不就是背包问题吗？又因为本题一个箱子不能重复购买，所以我们很容易可以使用 0/1 背包的 方法求出已购买的箱子总容量为 $j$ 时，最少花费为 $dp_j$ 个馒头。

但是这题不同的是，购买的箱子的总容量为 $j$ 时，能装下 $j-x$ 个馒头（其中$x\le j$），也就是说 $dp_j=\min dp_{j+x}$ 其中 $x\ge 0$ 所以我们在 $dp$ 时要这么写：

```cpp
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=c[i];j--)
		{
			dp[j]=min(dp[j],dp[j-c[i]]+e[i]);
		}
		for(int j=m-1;j>=1;j--)
		{
			dp[j]=min(dp[j],dp[j+1]);
		}
	}
```
还有一个细节就是 $C_i$ 可能会大于 $m$ 。也就是说背包的第 $2$ 维可能会大于 $m$ ，会很大很大。甚至会 $\texttt{TLE}$，$\texttt{MLE}$ ，但是我们顶多只需要容量为 $m$ 的箱子。所以我们可以将箱子的容量 $C_i$ 与 $m$ 取 $\min$ 就可以避免这种情况了。

我们求出了箱子总容量为 $x$ 时的最小花费时，再用取 $x$ 个馒头时最大的总卖价减去它，就是卖出了 $m$ 个馒头时的最大获利，最后我们再枚举 $x,x\in[1,m]$ 即可求出题目要求的答案。

时间复杂度：$\mathcal{O}(nm)$

这题就这么简单愉快的结束了，大家是不是觉得很水啊。连我这个大蒟蒻都能不看题解 $\texttt{AC}$ 本题。

完结撒花。

等等……

$\texttt{AC CODE}$

```cpp
#include<bits/stdc++.h>
#define LL long long
#define inf 1000000000
using namespace std;
const int MAX=100010;
int n,m,p[MAX],c[MAX],e[MAX];
LL dp[MAX],sum[MAX],ans;
bool cmp(int a,int b)
{
	return a>b;
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++) scanf("%d",&p[i]),dp[i]=inf;
	for(int i=1;i<=n;i++) scanf("%d%d",&c[i],&e[i]),c[i]=min(c[i],m);
	sort(p+1,p+m+1,cmp);
	for(int i=1;i<=m;i++) sum[i]=sum[i-1]+p[i];
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=c[i];j--)
		{
			dp[j]=min(dp[j],dp[j-c[i]]+e[i]);
		}
		for(int j=m-1;j>=1;j--)
		{
			dp[j]=min(dp[j],dp[j+1]);
		}
	}
	for(int i=1;i<=m;i++)
	{
		ans=max(ans,sum[i]-dp[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```

~~最后：不要脸的求一波赞~~。

---

## 作者：CYZZ (赞：3)

# [IOI 饅頭](https://www.luogu.com.cn/problem/AT_joi2014ho2)
~~模拟赛的时候没看到这题所以写个题解纪念一下。~~
# 题意简明
你有 $m$ 个大小相等且有价格的馒头和 $n$ 个有容积与价格的盒子，每种馒头和盒子只有一个，可以把馒头装进盒子里。

一个盒子带来的利润 $=$ 盒内馒头的总价值 $-$ 盒子的价格。求最大可能的利润。
# 思路分析
## 设状态
看完题面，刻在 DNA 里的经验告诉我们这题应该是个 [0/1 背包](https://www.luogu.com.cn/paste/1qtp07x1)。于是，我们往背包的方向去想。我们把每个盒子看成一个物品，把盒子的**价格**看成物品的**价值**，把盒子的**容积**看成物品的**重量**，把**馒头**看成要获得的**总价值**。那么 $dp_i$ 就表示装 $i$ 个馒头所需要的最小代价。状态就搞定了。
## 推方程
这时候可能有人会问：我们希望盒子的价格尽量小，但希望物品的价值尽量大。怎么能把这两个看起来相反的状态联系在一起呢？

没错，这就是本题和 0/1 背包的区别。本题中，我们希望 $dp_i$ 的值尽量小，也就是使成本更小。然后我们就得出了方程。
$$dp_i=\min(dp_i,dp_{i-c_j}+e_i)$$
其中，$j$ 为当前枚举到的盒子。大家应该也发现了，本题方程中取 $\min$，0/1 背包中取 $\max$。
## 看细节
在高兴的打完代码后，发现 WA 了。仔细检查后发现，本题中的 $c_i$ 并不一定小于 $m$。也就是说，**有些盒子不能百分之百利用**。当 $c_i>m$ 时，取 $c_i=m$ 即可。同样的，要取 $dp_i=\max(dp_i,dp_j)$，$1\le i<j\le n$。

馒头的大小是一样的，但价值不一样，那肯定选价值大的呀，可以先 $sort$ 一遍。计算答案时，我们已经求出了装 $i$ 个馒头的最小花费。那么答案为 $ans=\max(sum_i-dp_i)$。其中 $sum_i$ 是用前缀和处理出来的前 $i$ 大的馒头价值之和。

总复杂度 $O(nm)$，输出记得换行哟。
# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[10005],c[505],v[505],dp[10005],sum,ans;
bool cmp(int x,int y)
{
	return x>y;
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&a[i]);
		dp[i]=1e9;
	}
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&c[i],&v[i]);
		c[i]=min(c[i],m);//细节
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=c[i];j--)
		{
			dp[j]=min(dp[j],dp[j-c[i]]+v[i]);
		}
		for(int j=m;j>1;j--)
		{
			dp[j-1]=min(dp[j-1],dp[j]);
		}
	}
	for(int i=1;i<=m;i++)
	{
		sum+=a[i];//前缀和
		ans=max(ans,sum-dp[i]);
	}
	printf("%d\n",ans);//记得换行
	return 0;
}
```
希望本篇题解可以帮到大家！！！

---

## 作者：君のNOIP。 (赞：2)

~~很显然の背包。~~

------------
#### 数据范围：

- $ 1≤M≤10000 $

- $ 1 \le N \le 500 $

- $ 1 \le P_i,C_i,E_i \le 10000$


------------

#### ~~错误思路：~~

~~第一眼：什么鬼，不会做。~~

片刻：哦，就是一个简单の**背包**。

$ dp_i $ 表示花 $ i $ 买箱子能装の馒头数。

代码打一半：等等，时间复杂度好像不太对， 500 $\times$ 10000 $\times$ 10000 = ???


------------

#### 正片开始：

- 首先将馒头价格从大到小**排序**，然后随便搞个**前缀和**表示取前 $i$ 个馒头の最大价值。

- 于是我们发现最多就10000个馒头，可以使 $ dp_i $ 表示装 $i$ 个馒头の最小花费。

**时间复杂度：** $O(NM) $


------------
**细节(~~修bug~~)：**

- 初始化： $dp_i = +oo $ , $dp_0 = 0$

- $ans = max( sum_i - dp_i )$

- 此时我们发现样例1过不了。

- 以及：
```cpp
1 1
100 
3 1
```


------------

- 后者很简单，将箱子容量与 $m$ 取最小值。

- 关于前者，我们可以发现如当 $dp_3 = 100$ , $dp_1,dp_2$ 很显然也应更新至100。

------------


#### 给出两种写法：

#### 写法一： $dp$ 开两倍数组，最后只更新一次 $dp$ ，空间换时间 :


------------
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
#define G() Cr=getchar()
#define LL long long
int Xr;char Cr;
inline int  rd(){
	Xr=0;G();
	while(Cr<'0'||Cr>'9')G();
	while(Cr>='0'&&Cr<='9')Xr=(Xr<<1)+(Xr<<3)+Cr-'0',G();
	return Xr;
}
#define MAX_N 505
#define MAX_M 20005
int n,m;
int a[MAX_M];
int c[MAX_N],va[MAX_N];
int sum[MAX_M];
int dp[MAX_M];
int ans;

bool comp(int x,int y){
	return x>y;
}
int main(){
	m=rd(),n=rd();
	for(int i=1;i<=m;i++)a[i]=rd();
	sort(a+1,a+1+m,comp);
	for(int i=1;i<=m;i++)sum[i]=sum[i-1]+a[i]; 
	
	for(int i=1;i<=n;i++)c[i]=rd(),c[i]=min(m,c[i]),va[i]=rd();
	for(int i=1;i<=m<<1;i++)dp[i]=99999999;
	for(int i=1;i<=n;i++)
		for(int j=m<<1;j>=c[i];j--)
			dp[j]=min(dp[j],dp[j-c[i]]+va[i]);
		
	for(int j=(m<<1)-1;j>=1;j--)dp[j]=min(dp[j],dp[j+1]);
	
	for(int i=1;i<=m;i++)ans=max(sum[i]-dp[i],ans);
	cout<<ans<<endl;
}
```


------------

#### 写法二： 每个箱子取完都更新 $dp$ ，时间换空间：

------------
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
#define G() Cr=getchar()
#define LL long long
int Xr;char Cr;
inline int  rd(){
	Xr=0;G();
	while(Cr<'0'||Cr>'9')G();
	while(Cr>='0'&&Cr<='9')Xr=(Xr<<1)+(Xr<<3)+Cr-'0',G();
	return Xr;
}
#define MAX_N 505
#define MAX_M 20005
int n,m;
int a[MAX_M];
int c[MAX_N],va[MAX_N];
int sum[MAX_M];
int dp[MAX_M];
int ans;

bool comp(int x,int y){
	return x>y;
}
int main(){
	m=rd(),n=rd();
	for(int i=1;i<=m;i++)a[i]=rd();
	sort(a+1,a+1+m,comp);
	for(int i=1;i<=m;i++)sum[i]=sum[i-1]+a[i]; 
	
	for(int i=1;i<=n;i++)c[i]=rd(),c[i]=min(m,c[i]),va[i]=rd();
	for(int i=1;i<=m;i++)dp[i]=99999999;
	for(int i=1;i<=n;i++){
		for(int j=m;j>=c[i];j--)
			dp[j]=min(dp[j],dp[j-c[i]]+va[i]);
		for(int j=m-1;j>=1;j--)dp[j]=min(dp[j],dp[j+1]);
	}
	for(int i=1;i<=m;i++)ans=max(sum[i]-dp[i],ans);
	cout<<ans<<endl;
}
```


------------

### 完结撒花~~~

这大概是我写过最艰难の题解了（~~因为种种原因交了11次，WA了8次~~）。

~~第二次抢占题解1楼。~~


---

## 作者：shinzanmono (赞：1)

考虑贪心思想，我们只需要把总价最大的馒头装上就行，关键的问题是装几个。

设 $f_i$ 表示可以正好装 $i$ 个馒头的盒子的最小价值。可以通过一遍 01 背包解决。

然后使用贪心，选择最大的 $i$ 个馒头装进盒子里即可。

有一个坑点在于可以使用大小 $>M$ 的盒子，所以我们让背包的大小为 $M+\max C_i$，然后统计答案即可。

```cpp
#include<iostream>
#include<algorithm>
const int sz=1e4+10;
const int inf=0x3fffffff;
int a[sz],f[sz<<1];
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,m;
    std::cin>>m>>n;
    for(int i=1;i<=m;i++)std::cin>>a[i];
    std::sort(a+1,a+m+1,std::greater<>());
    for(int i=1;i<=m;i++)a[i]+=a[i-1];
    for(int i=1;i<=m+10000;i++)f[i]=inf;
    for(int i=1,c,e;i<=n;i++){
        std::cin>>c>>e;
        for(int j=m+10000;j>=c;j--)
            f[j]=std::min(f[j],f[j-c]+e);
    }
    int ans=0;
    for(int i=1;i<=m+10000;i++){
        if(i<=m)ans=std::max(ans,a[i]-f[i]);
        else ans=std::max(ans,a[m]-f[i]);
    }
    std::cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：AbsMatt (赞：1)

## [题目传送器](https://www.luogu.com.cn/problem/AT_joi2014ho2)
# 前言
由于个人习惯，后面的讲解和代码都会将输入的 $n$ 和 $m$ 调换。

# 题意

给定 $n$ 个馒头和 $m$ 个容器，第 $i$ 个容器可以装 $C_{i}$ 个馒头，价格为 $E_{i}$，第 $i$ 个馒头售价 $P_{i}$。每个馒头和容器只能使用一次，也可以不用。求总利润的最大值。

# 分析

本题很明显是使用 0/1 背包来做，但直接用 0/1 背包时间复杂度就是 $O(n^2m)$，肯定会超时。所以要用前缀和优化。

我们可以用倒叙来进行 0/1 背包，这样就就可以少一个维度。$dp_{i}$ 指前 $i$ 个包装需要的最少的价值，则 $dp_{i} = \min_{j=c_{i}}^{n} dp_{j-c[i]}+e_{i}$。

在进行 0/1 背包后先将 $P$ 数组从大到小排序， $ans=\max_{i=1}^{n}\sum_{j=1}^{i}-dp_{i}$，我们可以用前缀和将 $\sum_{j=1}^{i}$ 的 $O(n)$ 优化掉，最后的时间复杂度就是 $O(nm)$。

### 警醒后人：最后输出答案后一定要换行，否则过不了！

## AC Code
```cpp
#include<bits/stdc++.h>  // 开始了
using namespace std;
const int maxn=1e4+10;
int n,m,ans=0;
int p[maxn],c[maxn],e[maxn],dp[maxn];
bool cmp(int x,int y){return x>y;}
int main(){
	memset(dp,0x3f,sizeof(dp));  // 初始化
	dp[0]=0; // 一个都不取的花费最小值为0
	scanf("%d%d",&n,&m);// 输入
	for(int i=1;i<=n;i++)	scanf("%d",&p[i]);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&c[i],&e[i]);
		c[i]=min(c[i],n);  // 最多装n个馒头
	}
	for(int i=1;i<=m;i++){  // 0/1 背包
		for(int j=n;j>=c[i];j--)	dp[j]=min(dp[j],dp[j-c[i]]+e[i]); 
		for(int j=n-1;j>0;j--)	dp[j]=min(dp[j],dp[j+1]);
	}
	sort(p+1,p+n+1,cmp);  // 从大到小排序
	int now=0;  // 前缀和
	for(int i=1;i<=n;i++){
		now+=p[i];
		ans=max(ans,now-dp[i]);
	}
	printf("%d\n",ans);  // 警醒后人：一定要打换行要不然过不了
  	return 0;  // 再见
}
```

---

## 作者：djh0314 (赞：0)

[**传送门**](https://www.luogu.com.cn/problem/AT_joi2014ho2)。

## 题意

有 $n$ 个物品，$m$ 个背包。第 $i$ 个物品的价值是 $P_i$，第 $j$ 个背包可以装 $C_i$ 个物品，但会消耗 $E_i$ 的价值。

背包不能重复买，问最多可以获得多少价值。

## 分析

首先一个简单的贪心，我们在购买背包后塞入物品，一定时从大往小塞，也就是说，我们可以先对物品从大到小排序并求前缀和。

其次，我们对购买背包进行求最小，显然，使用 01 背包即可，为了防止我们的可以塞的容量大于我们选取的物品，将数组后缀取最小即可。

~~~cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
const int N = 2e4+5;
inline int read() {
	int x;
	scanf("%d",&x);
	return x;
}
int n, m,a[N],qzh[N],f[N];
signed main() {
//	freopen("bread.in","r",stdin);
//	freopen("bread.out","w",stdout);
	n=read(),m=read();
	for(int i=1; i<=n; ++i) a[i]=read();
	sort(a+1,a+n+1,greater<int >());
	for(int i=1; i<=n; ++i) qzh[i]=qzh[i-1]+a[i];
	memset(f,0x3f,sizeof f);
	f[0]=0;
	for(int i=1; i<=m; ++i) {
		int cnt=read(),val=read();
		for(int j=N-1; j>=cnt; --j) f[j]=min(f[j],f[j-cnt]+val);
	}
	for(int i=N-2; i; --i) f[i]=min(f[i],f[i+1]);
	int ans=0;
	for(int i=1; i<=n; ++i) ans=max(ans,qzh[i]-f[i]);
	cout<<ans<<endl;
	return 0;
}
~~~

---

## 作者：GFyyx (赞：0)

## 解题思路
看题目，怎么看怎么都能想到背包。

但是暴力 01 背包时间复杂度为 $\Theta(n^2m)$，会超时。

## 优化
用贪心与前缀和优化掉一重循环。

直接设置状态 $dp_{i,j}$ 表示用前 $i$ 个包装盒装前 $j$ 个馒头的最大收益。

$A_i$ 表示前 $i$ 个馒头的卖价，易得状转：
```cpp
if(j<=bg[i].c) dp[i][j]=max(dp[i-1][j],a[j]-bg[i].e)
else dp[i][j]=max(dp[i-1][j],dp[i-1][j-bg[i].c]+a[j]-a[j-bg[i].c]-bg[i].e)
```

## 完整代码
码量不大，不建议直接文本比对。
```cpp
#include <iostream>
#include <bits/stl_algo.h>
using namespace std;
int n,m,ans;
int a[10005],dp[5002][10005];
struct jjfq{int c,e;}bg[5002];
int main(){
	cin >> m >> n;
	for (int i=1; i<=m; i++)
		cin >> a[i];
	sort(a+1,a+m+1,greater<int>());//贪心地从大到小排序 
	for (register int i=1; i<=m; i++) 
		a[i]+=a[i-1];//滚动前缀和 
	for (register int i=1; i<=n; i++)
		cin >> bg[i].c >> bg[i].e;
	for (register int i=1; i<=n; i++){
		for (register int j=1; j<=m; j++){
			if(j<=bg[i].c) dp[i][j]=max(dp[i-1][j],a[j]-bg[i].e);
			else dp[i][j]=max(dp[i-1][j],
				 dp[i-1][j-bg[i].c]+a[j]-a[j-bg[i].c]-bg[i].e);//状转 
			ans=max(ans,dp[i][j]);
		}
	}
	cout << ans << endl;//输出答案 
	return 0;
}
```


---


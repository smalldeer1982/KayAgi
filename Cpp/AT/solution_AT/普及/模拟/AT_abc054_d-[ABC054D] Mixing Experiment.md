# [ABC054D] Mixing Experiment

## 题目描述

------------

有 $N$ 个物体，第 $i$ 个物体含有 $a_i$ 质量的 A 元素 和 $b_i$ 质量的 B 元素，代价为 $c_i$ 。

问能否取若干个物体，使 A 元素与 B 元素质量之比为 $M_a : M_b$ ，并使代价最小。

------------

## 说明/提示

- $1\le N\le 40$

- $1\le a_i,b_i\le 10$

- $1\le c_i\le 100$

- $1\le M_a,M_b\le 10$

-  $gcd(M_a,M_b)=1$

- 输入都为整数。

------------

translated by @君のNOIP。

## 样例 #1

### 输入

```
3 1 1
1 2 1
2 1 2
3 3 10```

### 输出

```
3```

## 样例 #2

### 输入

```
1 1 10
10 10 10```

### 输出

```
-1```

# 题解

## 作者：龙潜月十五 (赞：5)

## 一、题意

有 $n$ 个物品，每个物品有三个值：$a_i,b_i,c_i$，选若干个物品，使其 $a_i$ 的和与 $b_i$ 的比值为 $ma:mb$，且 $c_i$ 的和最小。

## 二、思路

一看之下最先思考的肯定是如何处理 $a$ 的和和 $b$ 的和比值的问题，但思考下我们会发现其实不用刻意去处理。因为本题的数据范围很小，因此可以直接暴力 $0/1$ 背包。设 $f_{i,j}$ 表示 $a$ 的和为 $i$， $b$ 的和为 $j$ 时的最小 $c$ 值，就可以跑普通的 $0/1$ 背包了。

最后统计答案就枚举每一个 $a$ 的和可能的值，再根据比值求出 $b$ 的和的值，即 $ans = \min(ans,f_{i,i \times mb / ma})$，前提是 $i \times mb$ 能被 $ma$ 整除。

一些注意点在代码注释里。

## 三、代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll read() {
    ll sum = 0, ff = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') {
            ff = -1;
        }
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
    	sum = sum * 10 + ch - 48;
        ch = getchar();
    }
    return sum * ff;
}

void write(ll x) {
	 if(x < 0) {
		putchar('-');
		x = -x;
	 }
	 if(x > 9)
		write(x / 10);
	 putchar(x % 10 | 48);
}

inline int min(int a, int b) {
	return a < b ? a : b;
}

const int INF = 1e9;
const int N = 407;
int n, ma, mb, suma, sumb, f[N][N], ans = INF;
struct node {
	int a, b, c;
}s[N];

int main() {
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	n = read(), ma = read(), mb = read();
	for(register int i = 1; i <= n; ++i)
		s[i].a = read(), s[i].b = read(), s[i].c = read(), suma += s[i].a, sumb += s[i].b;//先求出所有a的和与所有b的和 
	
	for(register int i = 0; i <= suma; ++i)
		for(register int j = 0; j <= sumb; ++j)
			f[i][j] = INF;//初始化 
	f[0][0] = 0;
	
	for(register int i = 1; i <= n; ++i)
		for(register int j = suma; j >= s[i].a; --j)//0/1背包滚动数组要倒叙枚举 
			for(register int k = sumb; k >= s[i].b; --k)
				f[j][k] = min(f[j][k], f[j - s[i].a][k - s[i].b] + s[i].c);

	for(register int i = 1; i <= suma; ++i)
		if(i * mb % ma == 0 && i * mb / ma <= sumb)//要能被整除同时b和的值不能超过sumb 
			ans = min(ans, f[i][i * mb / ma]);
	
	ans = ans == INF ? -1 : ans;//无解的情况 
	write(ans);
	puts("");
    return 0;
}


```


---

## 作者：方123456 (赞：3)

个人认为这题目还是一道简单的 DP 题。

难度大概就 pj T2~T3 的样子吧。

首先可以明白一点，我们需要考虑两种决策，一种是取这个物品，另一种是不取。

然后我们维护整一个状态的时候可用 $f_{i,j,k}$ 表示选到第 $i$ 个物品，有 $j$ 个 $a$ 元素，$k$ 个 $b$ 元素的最小代价。

转移也很容易得出 $f_{i,j,k}=\min(f_{i,j,k},f_{i-1,j-a,k-b}+c)$ 参考 01 背包把第一维压掉，然后倒序枚举。

最后处理答案的时候稍微用点小学的数学即可。

于是这题目就 A 了。

三维的好像也能过？

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int INF=405;
int n,ma,mb,f[INF][INF];
signed main()
{
        scanf("%d",&n);
        scanf("%d %d",&ma,&mb);
        memset(f,63,sizeof f);
        f[0][0]=0;
        for (int i=1; i<=n; i++) {
                int a=0,b=0,c=0; scanf("%d %d %d",&a,&b,&c);
                for (int j=400; j>=a; j--) {
                        for (int k=400; k>=b; k--) {
                                f[j][k]=min(f[j][k],f[j-a][k-b]+c);
                        }
                }
        }
        int ans=1e9;
        for (int i=1; i<=400; i++) {
                int kk=i*mb;
                if (kk%ma) continue;
                kk/=ma; if (kk>400) continue; ans=min(ans,f[i][kk]);
        }
        if (ans<1e9) cout<<ans<<"\n";
        else cout<<"-1\n";
        return 0;
}

```


---

## 作者：君のNOIP。 (赞：2)

#### ~~很明显の背包。~~

------------
### 数据范围：

- $1\le N\le 40$

- $1\le a_i,b_i\le 10$

- $1\le c_i\le 100$

- $1\le M_a,M_b\le 10$

-  $gcd(M_a,M_b)=1$

- 输入都为整数。

------------

### 主要思路：

- 通过观察，我们发现即使所有物体都取， A と B の 质量都不会超过400。

- 那么我们很明显只需设 $dp_{i,j}$ 为取了 $i$ 质量 A 和 $j$ 质量 B 所花费の最小价值。

- 初始化： $dp_{i,j}=+oo $ , $i,j \in [ 0 , 400 ]$ ， $dp_{0,0}=0$

- 答案为 $min $ $ dp_{i,j} $  $ ( i:j=M_a:M_b $且 $ i , j $为整数。)

- 最大计算次数： $40\times400\times400 = 6.4\times10^6$

- 因此可以直接 3 重循环暴力枚举。

------------
### 完整代码：

**ps：** 我一开始每次从400开始算一交发现是luogu Rank2，就加了优化减少不必要运算，一跃Rank1，~~时间比Rank2一半还短~~。

------------
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define G() Cr=getchar()
int Xr;char Cr;
inline int  rd(){
	Xr=0;G();
	while(Cr<'0'||Cr>'9')G();
	while(Cr>='0'&&Cr<='9')Xr=(Xr<<1)+(Xr<<3)+Cr-'0',G();
	return Xr;
}
int n,Ma,Mb,ans=99999999;
int dp[405][405];
int a[100],b[100],c[100];
int suma[100],sumb[100];
int main(){
	n=rd(),Ma=rd(),Mb=rd();
	for(int i=1;i<=n;i++)
		a[i]=rd(),b[i]=rd(),c[i]=rd(),suma[i]=suma[i-1]+a[i],sumb[i]=sumb[i-1]+b[i];
	
	for(int i=0;i<=suma[n];i++)
		for(int j=0;j<=sumb[n];j++)
			dp[i][j]=99999999;
	dp[0][0]=0;	
	
	for(int k=1;k<=n;k++)
		for(int i=suma[k];i>=a[k];i--)
			for(int j=sumb[k];j>=b[k];j--)
				dp[i][j]=min(dp[i][j],dp[i-a[k]][j-b[k]]+c[k]);		
	
	for(int i=1;i<=suma[n];i++)
		for(int j=1;j<=sumb[n];j++)
			if(i*Mb==j*Ma)
				ans=min(ans,dp[i][j]);
	
	printf("%d\n", (ans==99999999)?-1:ans );		
}


```


------------

### 完结撒花~~~

~~（达成成就：首次 翻译 + 第一篇题解 + Rank1 ）~~


---

## 作者：迟暮天复明 (赞：1)

[题面](https://atcoder.jp/contests/abc054/tasks/abc054_d)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/16210222.html)

题意：
在 $n(1\leq n\leq40)$ 个物品中选择若干个，使得 $\dfrac{\sum A_i}{\sum B_i}=\dfrac{ma}{mb}$ 且物品总价格最小。

-----
可能是做题做魔怔了，见到 $n\leq 40$ 就条件反射的想到了双端 DFS。

左右两边 DFS 就是套路，没有任何问题。现在我们的问题就是左边和右边做完以后如何将答案进行合并。

因为题目给了 $a_i\leq10,b_i\leq10$ 的条件，我们可以发现满足 $\dfrac{\sum A_i}{\sum B_i}=\dfrac{ma}{mb}$ 的 $\sum A_i$ 与 $\sum B_i$ 的种类数是很少的。最多的情况下，当 $ma=mb=1$ 时，总计有 $400$ 种情况。所以我们完全可以打一个表，记录那些成立的 $(\sum A_i,\sum B_i)$ 的数对。

右边每做出来一个 $(\sum A_r,\sum B_r)$ 时，对于每一组预处理出的合法 $(\sum A,\sum B)$，可以对应的去寻找左半部分做到的答案。这时更新答案即可。

时间复杂度 $O(nm\times2^{n/2})$，$m$ 指 $A,B$ 数组中最大值，可以通过本题。

[代码](https://paste.ubuntu.com/p/jqtR9ChQvX/)

---

## 作者：Z1qqurat (赞：1)

### 思路

Part 1：如何想到这是一道背包问题的？

看看题目里面的这句话：有 $N$ 个物体，第 $i$ 个物体含有 $a_i$ 质量的 A 元素 和 $b_i$ 质量的 B 元素，代价为 $c_i$ 。

而这不就是一个背包的基本吗？

（可以看看[这个模板](https://www.luogu.com.cn/problem/P1048)。）

Part 2：下一步的深入。

但是题目中多了一句话：使 A 元素与 B 元素质量之比为 $M_a : M_b$ 。

而这个比值就不好处理了是不是，然后我们看看数据范围：

![数据范围](https://cdn.luogu.com.cn/upload/image_hosting/4dbh0s80.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

发现这个范围超级小！三次的算法都跑得过，~~九十分钟的Floyd都能过~~。

于是我们可以考虑先处理出来所有选择，再看看是否满足比值的条件。

Part 3：珂爱的正解！！！

总结一下思路：我们找出所有可以的选择，并记录其中A元素和B元素的分别的个数，最后再看有没有比值为 $Ma$ 比 $Mb$ 的。

（其实思路有点像那[精卫填海](https://www.luogu.com.cn/problem/P1510)了是不是。）

### 小小的经验总结

总结一下这道题告诉我们了什么道理：

1.做限制条件多的题目可以考虑循序渐进。（如P1510.精卫填海。）

2.当思路不明确可以看看**时间复杂度**，帮你确定大致的算法。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,ma,mb,a[50],b[50],c[50],A,B,amin=1e9,bmin=1e9;
ll dp[410][410],minn=1e9;

int main() {
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;	//dp数组中求最小值的时候必须初始化！！！
	cin>>n>>ma>>mb;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i]>>c[i];
		A+=a[i],B+=b[i];
		amin=min(amin,a[i]);//取和，与下面用处一样
		bmin=min(bmin,b[i]);//取两种元素中的最小值，便于后期的dp循环使用
	}
	
	for(int i=1;i<=n;i++){
		for(int j=A;j>=a[i];j--){
			for(int k=B;k>=b[i];k--){
				dp[j][k]=min(dp[j][k],dp[j-a[i]][k-b[i]]+c[i]);//状态转移方程
			}
		}
	}
	
	for(int i=amin;i<=A;i++){
		for(int j=bmin;j<=B;j++){
			if(j!=0&&i*mb==j*ma){//能用乘法绝对不用除法，避免精度误差
				minn=min(minn,dp[i][j]);
			}
		}
	}
	if(minn==1000000000)minn=-1;//如果不行的话要输出-1哦！
	cout<<minn;
	return 0;     
}
```

$End.$

---

## 作者：Night_sea_64 (赞：0)

大家好，本蒟蒻又来写题解了~

~~感觉楼上 dalao 们写的码量有点大。。。~~

[这里是题目](https://www.luogu.com.cn/problem/AT2330)

这道题主要考察的知识点是背包。

就是个背包的裸题。一看，自然而然的就能想到把物体看作物品，把两种元素的质量 $a_i$ 和 $b_i$ 看作体积，把代价 $c_i$ 看作价值。这样问题就迎刃而解了。

**状态**：$f_{j,k}$ 表示有 $j$ 质量的 A 元素和 $k$ 质量的 B 元素，需要的最小代价。

**转移**：$f_{j,k}=\min(f_{j,k},f_{j-a_i,k-b_i}+c_i)$。

记得初值要设成无限大。AC 代码如下，特别短：

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int a[50],b[50],c[50],f[410][410];
int gcd(int x,int y)//最大公因数
{
    if(!y)return x;
    return gcd(y,x%y);
}
int main()
{
    int n,ma,mb,minn=1e9;
    cin>>n>>ma>>mb;
    for(int i=1;i<=n;i++)cin>>a[i]>>b[i]>>c[i];
    memset(f,999999,sizeof(f));
    f[0][0]=0;//初值
    for(int i=1;i<=n;i++)
        for(int j=n*10;j>=a[i];j--)
            for(int k=n*10;k>=b[i];k--)
            {
                f[j][k]=min(f[j][k],f[j-a[i]][k-b[i]]+c[i]);//转移
                if(j/gcd(j,k)==ma&&k/gcd(j,k)==mb)minn=min(minn,f[j][k]);//如果质量比为 Ma:Mb 就更新答案。
            }
    if(minn<1e9)cout<<minn<<endl;
    else cout<<-1<<endl;
    return 0;
}
```

求各位 julao 点个赞吧！！！

---

## 作者：cjZYZtcl (赞：0)

## 01背包
这是一道二维的01背包，$dp_{i,j}$ 表示A元素取i质量，B元素取j质量的最小代价。相当于一维的容量变成了二维的容量。

状态转移：$dp_{i,j} = min(dp_{i,j},dp_{i-a[k],j-b[k]}+c[k])$

注意：由于是最小值，所以初值要赋最大。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[45], b[45], c[45];
int f[405][405];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
} 
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = read(), ma = read(), mb = read(), suma = 0, sumb = 0;
	for(int i = 1; i <= n; i++){
		a[i] = read(), b[i] = read(), c[i] = read();
		suma += a[i];
		sumb += b[i];
	}
	for(int i = 1; i <= suma; i++){
		f[i][0] = 0x3f3f3f3f;
	}
	for(int j = 1; j <= sumb; j++){
		f[0][j] = 0x3f3f3f3f;
	}
	for(int i = 1; i <= suma; i++){
		for(int j = 1; j <= sumb; j++) f[i][j] = 0x3f3f3f3f;
	}
	for(int k = 1; k <= n; k++){
		for(int i = suma; i >= a[k]; i--){
			for(int j = sumb; j >= b[k]; j--){
				f[i][j] = min(f[i][j], f[i - a[k]][j - b[k]] + c[k]);
			}
		}
	}
	int ans = 0x3f3f3f3f;
	for(int i = 1; i <= min(suma / ma, sumb / mb); i++){
		ans = min(ans, f[i * ma][i * mb]);
	}
	if(ans != 0x3f3f3f3f) write(ans);
	else write(-1);
}
```


---


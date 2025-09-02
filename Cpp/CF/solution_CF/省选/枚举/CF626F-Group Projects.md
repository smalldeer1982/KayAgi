# Group Projects

## 题目描述

There are $ n $ students in a class working on group projects. The students will divide into groups (some students may be in groups alone), work on their independent pieces, and then discuss the results together. It takes the $ i $ -th student $ a_{i} $ minutes to finish his/her independent piece.

If students work at different paces, it can be frustrating for the faster students and stressful for the slower ones. In particular, the imbalance of a group is defined as the maximum $ a_{i} $ in the group minus the minimum $ a_{i} $ in the group. Note that a group containing a single student has an imbalance of $ 0 $ . How many ways are there for the students to divide into groups so that the total imbalance of all groups is at most $ k $ ?

Two divisions are considered distinct if there exists a pair of students who work in the same group in one division but different groups in the other.

## 说明/提示

In the first sample, we have three options:

- The first and second students form a group, and the third student forms a group. Total imbalance is $ 2+0=2 $ .
- The first student forms a group, and the second and third students form a group. Total imbalance is $ 0+1=1 $ .
- All three students form their own groups. Total imbalance is $ 0 $ .

In the third sample, the total imbalance must be $ 0 $ , so each student must work individually.

## 样例 #1

### 输入

```
3 2
2 4 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 3
7 8 9 10
```

### 输出

```
13
```

## 样例 #3

### 输入

```
4 0
5 10 20 21
```

### 输出

```
1
```

# 题解

## 作者：皎月半洒花 (赞：27)

大概是稍微详细讲了讲优化部分。


考虑暴力计数，大概就是 $f_{i,j,k}$ 表示考虑了前 $i$ 个学生，分了 $j$ 组，当前不和谐度总和为 $k$ 的方案数。发现这样没法转移，因为并不知道该怎么考虑插入一个元素时的贡献。考虑对于一种状态，如果钦定了其中某些集合的最大值或者最小值已经固定，如果当前元素超过了这个 bond，就不能再用当前元素更新。于是考虑另一种状态，$f_{i,j,k}$ 表示考虑了前 $i$ 个学生，分了不知道组，但是有 $j$ 组的最大值还没确定，当前不和谐度总和为 $k$ 的方案数 。这样显然是需要将所有权值排序之后再 $dp$ 的。

考虑转移。每次遇到一个新的元素，可以将其和之前的某一组合并，或者单独新开一组。记没确定最大值的集合为「未闭合集合」，那么就有四种情况：

1、合并，但是那个集合仍未闭合。

2、合并，那个集合闭合了。

3、不合并，新开的集合未闭合。

4、不合并，新开的集合闭合了。

于是转移就是

![](https://cdn.luogu.com.cn/upload/image_hosting/r8bw0zsg.png)

分别对应四种情况。

考虑这么做的复杂度，似乎是 $O(n^2k)$ ，但是由于中间转移过程的第三维可能会到 $\pm 10^4$ ，大小无法准确预估，所以时空复杂度都是 $O(n^2\sum a_i)$ 的。于是就 gg 。

考虑稍微抽象一下，每个集合的 $min/max$ 可以看做在一条值域轴上线段的左、右端点，对于每个时刻 $i$ ，未闭合的集合就是某些会被 $i$ 横切掉的线段。那么对于某条直线 $(l,r)$ ，满足 $l<i<r$ ，在第 $i$ 个时刻，记录的是代价是 $-a_l$，但这种方法并不聪明，因为只有当取到 $r$ 时，$-a_l$ 才会被用上，所以对于任意一个 $i,l<i<r$ 而言，$-a_l$ 都是没必要承载的空间。于是考虑怎么将一条线段的贡献平摊到每个点上，这样每一维转移就不再是 $O(\max\{\sum a_i,k\})$ 而是 $O(\max\{a_i,k\})$ 。

考虑平摊的话，即如何将 $a_r-a_l$ 展开成每一项都 $<\max\{a_i,k\}$ 的这么一个数列。一个比较简单的方法就是：
$$
a_r-a_l=\sum_{i=l+1}^r(a_i-a_{i-1})
$$
~~一看就是老分式裂项了~~

于是本质上只是优化了转移。令 $d=a_i-a_{i-1}$ 可以得到：

![](https://cdn.luogu.com.cn/upload/image_hosting/xwfr7u4q.png)

然后就没有然后了，复杂度 $O(n^2\max\{k,\max\{a_i\}\})$ 。

```cpp
#define MAXN 510
#define MAXK 1010
#define Mod 1000000007

using namespace std ; 
LL dp[2][MAXN][MAXK], ans ;
int N, K, M, base[MAXN], dif[MAXN] ;

il void del(int &x, const int &y){ x -= y ; if (x < 0) x += Mod ; }
il void add(LL &x, const LL &y){ x += y ; if (x > Mod) x %= Mod ; }
int main(){
	cin >> N >> K ; int i, j, k, d ;
	for (i = 1 ; i <= N ; ++ i) scanf("%d", &base[i]) ; 
 	sort(base + 1, base + N + 1), dp[0][1][0] = dp[0][0][0] = 1 ;
	for (i = 1 ; i < N ; ++ i) dif[i] = base[i + 1] - base[i] ;
	for (d = i = 1 ; i < N ; ++ i, d ^= 1){
		int o = d ^ 1 ; 
		for (j = 0 ; j <= N ; ++ j){
			int op = dif[i] * j ;
			for (k = 0 ; k <= K ; ++ k){
				int val = k + op ;
				LL res = dp[o][j][k], v = res * j % Mod ;
				dp[o][j][k] = 0 ; if (val > K) continue ;
				if (j) add(dp[d][j - 1][val], v) ; 
				add(dp[d][j][val], v + res), add(dp[d][j + 1][val], res) ;
			}
		}
	}
	for (i = 0 ; i <= K ; ++ i) 
		add(ans, dp[(N - 1) & 1][0][i]) ; 
  	cout << ans << endl ; return 0 ; 
}
```



---

## 作者：skylee (赞：23)

# [CF626F]Group Projects
## 题目大意：
有一个长度为$n(n\le200)$的数列$\{A_i\}$，将其划分成若干个子集，每个子集贡献为子集$\max-\min$。求子集贡献和$\le m(m\le1000)$的划分方案数。

## 思路：
将每个数看成数轴上的点,原题中的子集贡献和就是在这些点中，每个点作为至多一个线段的端点，所有线段长度之和（同一线段的两个端点可以相同）。

考虑动态规划，将$\{A_i\}$排序，用$f[i][j][k]$表示用了前$i$个点，$j$条线段只确定了一个端点，总贡献为$k$的方案树。

用$t=(A_{i+1}-A_i)\times j$，转移方程为：

- $f[i+1][j][k+t]+=f[i][j][k]$（该点自己作为线段的两个端点）
- $f[i+1][j][k+t]+=f[i][j][k]\times j$（该点作为其它线段的一部分，但不作为端点）
- $f[i+1][j=1][k+t]+=f[i][j][k]$（该点作为一条线段的起点）
- $f[i+1][j-1][k+t]+=f[i][j][k]\times$（该点作为某条线段的终点）

时间复杂度$\mathcal O(n^2m)$。

## 源代码：
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<functional>
inline int getint() {
	register char ch;
	while(!isdigit(ch=getchar()));
	register int x=ch^'0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x;
}
typedef long long int64;
const int N=201,M=1001,mod=1e9+7;
int a[N],f[N][N][M];
int main() {
	const int n=getint(),m=getint();
	for(register int i=1;i<=n;i++) a[i]=getint();
	std::sort(&a[1],&a[n]+1);
	f[0][0][0]=1;
	for(register int i=0;i<n;i++) {
		for(register int j=0;j<=n;j++) {
			const int t=(a[i+1]-a[i])*j;
			for(register int k=0;k<=m-t;k++) {
				(f[i+1][j][k+t]+=(int64)f[i][j][k]*(j+1)%mod)%=mod;
				if(j!=n) (f[i+1][j+1][k+t]+=f[i][j][k])%=mod;
				if(j!=0) (f[i+1][j-1][k+t]+=(int64)f[i][j][k]*j%mod)%=mod;
			}
		}
	}
	int ans=0;
	for(register int i=0;i<=m;i++) (ans+=f[n][0][i])%=mod;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Liu_zj (赞：12)

## 思路：

~~简单~~区间DP题。

### 最大值减最小值
分析题目，发现每一组中除了最大值、最小值，其他值没有作用。中间的值可以在某一组中，也可以单独分离出来成为一组。

分析数据范围：$n<=200$ 

emmm  O($n^3$)

对于每一个数据，都有以下几种情况：

1.作为一组值的最小值

2.作为一组值的最大值

3.作为一组值的中间值

4.单独成为一组

而所有数据的最小值不可能作为一组值的最大值，所有数据的最大值反之。

考虑将数据升序排序，方便处理每一组值的最大/最小值。

设 $f[i][j][k]$ 表示前 $i$ 个值（排序后），有 $j$ 个组 **可以** 再选人（还没最大值），不和谐度为 $k$ 的方案数。

根据上述四种情况，转移式为：

$f[i][j][k]+=f[i-1][j-1][k+a[i]]$

（$k+a[i]$表示这一组减去最小值）

$f[i][j][k]+=f[i-1][j+1][k-a[i]]*(j+1)$

（ $k+a[i]$ 表示这一组加上最大值，最大值可以是前面j组任意一组的最大值，所以结果乘 $j+1$ ）

$f[i][j][k]+=f[i-1][j][k]*j$

（中间值可以在前面j组任意一组中，所以结果乘 $j$ ）

$f[i][j][k]+=f[i-1][j][k]$

（自开自闭~~简称自闭~~区间）

然而这样打完后你会发现： $k$ 值如何枚举？？

$k$ 的范围极其不定，可以在最小值时变成-100000，也可以在n处回到k。

所以这是这道题第二个难点：

### 动态算贡献

由于k的不确定性，我们继续分析题目

当数据为:

$2,3,5,7,8$

时，如果某组以2为最小值，7为最大值，它的k值变化应该是

$-2 ..... +8  =6$

由于数据是排序的，所以也可以写成

$+(3-2) .. +(5-3) .. +(7-5)..  +(8-7)  =1+2+2+1=6$

它们是相同的。

~~自己推推就好了~~

所以k值在每次转移时，不必在最小值和最大值处变化，而是在每次转移时变化，变化值为 $a[i]-a[i-1]$

状态转移式变为：

$f[i][j][k]+=f[i-1][j-1][k-(j-1)*(a[i]-a[i-1])]$


$f[i][j][k]+=f[i-1][j+1][k-(j+1)*(a[i]-a[i-1])]*(j+1)$


$f[i][j][k]+=f[i-1][j][k-j*(a[i]-a[i-1])]*j$


$f[i][j][k]+=f[i-1][j][k-j*(a[i]-a[i-1])]$

需要注意的是：由于转移时最小值与最小值-1的差值并不需要加上，所以1、2转移要稍加变换。

最后只需要累加 $f[n][0][i]$ ( $i$ from $0$ to $k$ )即可。

而 $f[0][0][0]=1$

然后就愉快的AC了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[201][201][1001];
int a[100001];
#define mod %1000000007
int main()
{
	int n,m,ans(0);
	cin>>n>>m;
	for(register int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	f[0][0][0]=1;
	for(register int i=1;i<=n;i++)
	for(register int j=0;j<=i;j++)
	{
		int cha=(a[i]-a[i-1]);
		for(register int k=0;k<=m;k++)
		{//f[i][j][k]:前i点，开区间j个，到现在的值 k
			//kai
			if(j!=0&&k-(j-1)*cha>=0)
			f[i][j][k]=(f[i][j][k]+f[i-1][j-1][k-(j-1)*cha])mod;
			//bi
			if(j!=n&&k-(j+1)*cha>=0)
			f[i][j][k]=(f[i][j][k]+(long long)f[i-1][j+1][k-(j+1)*cha]*(j+1))mod;
			//mid
			if(k-j*cha>=0)
			f[i][j][k]=(f[i][j][k]+(long long)f[i-1][j][k-j*cha]*j)mod;
			//one
			if(k-j*cha>=0)
			f[i][j][k]=(f[i][j][k]+f[i-1][j][k-j*cha])mod;
		}
	}
	for(register int i=0;i<=m;i++)
	ans=(ans+f[n][0][i])mod;
	cout<<ans;
}
```

### 注意事项

1.DP时 $j$ 可能是负值或超过 $n$ ，需要特判。

2.DP转移相乘时要开longlong！

3.别忘了mod

祝大家AC愉快。

---

## 作者：bzzltl (赞：11)

### 思路
首先，我们看到这道题，每个同学的能力值是输入的，并不是按顺序的。
但是这道题仅仅是求不和谐之和不超过 $k$ (本题解中写作 $op$ ) 的分组数量，而且，由题意可得，每个同学的能力值 $a_i$（本题解中写作 $t_i$ ）的顺序并不重要，重要的是他的能力值。而且，当按顺序排完序之后，我们就可以很方便的就可以找到不和谐度的最小值，方便我们从小到大遍历找不和谐度小于 $k$ 的方案数。所以我们在开始的时候可以用 sort 排序，来方便我们接下来的计算。

如何设计 DP 方程？

因为共有 $n$ 人，我们肯定是需要用一维来记录此时的人数。

每组的不和谐度取决于 $\max - \min$ 的值，因为我们排过序，所以每组的不和谐度就是我们所选的每组最右边的值-最左边的值，最大值-最小值用 $t_i$ 数组即可实现，所以我们可以用第二维来记录当前有多少个扫过去的，只有最左边的值和中间的值，但是最右边没有确定的分组个数。

最后，考虑到我们数组肯定存的是方案数，而和谐度不超过 $k$ 的值我们还没有存，因此我们要再开一维，来记录一下此时的不和谐度之和。


#### 转移方程

考虑一下每当遇到一个点时，这个点所有的情况，设 $ p=(t[i]-t[i-1])\times j$：


当这个点自成一组时：

$$f[i][j][k+p]+=f[i-1][j][k]$$

当此点位于中间，没有其他贡献时: 

$$f[i][j][k+p]+=f[i-1][j][k] \times j$$

当此点位于左端时：

$$f[i][j][k+p]+=f[i-1][j-1][k]$$

当此点位于右端时：

$$f[i][j-1][k+p]+=f[i-1][j][k] \times j$$

坑：注意开 long long。

### 代码：

```
#include<bits/stdc++.h>
#define N 201
//#define int long long 
using namespace std;

inline int read(){int x=0,y=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') y=-y;c=getchar();}while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}return x*y;}
const int mod=1e9+7;

int n,op,t[N];
int f[N][N][1002];

inline int MAX(int x,int y){return x>y?x:y;}//手写MAX函数 

signed main()
{
	n=read();
	op=read();//读入 
	for(int i=1;i<=n;i++) t[i]=read();
	sort(t+1,t+n+1);
	f[0][0][0]=1;//初始化 
	for(int i=1;i<=n;i++) {
		for(int j=0;j<=n;j++) {
			int p=(t[i]-t[i-1])*j;
			for(int k=0;k<=op-p;k++) {
				f[i][j][k+p]=(f[i][j][k+p]+((long long)f[i-1][j][k]*(j+1))%mod)%mod;
				if(j!=n) f[i][j+1][k+p]=(f[i][j+1][k+p]+f[i-1][j][k])%mod;
				if(j!=0) f[i][j-1][k+p]=(f[i][j-1][k+p]+((long long)f[i-1][j][k]*j)%mod)%mod;
			}
		}
	}
	int ans=0;
	for(int i=0;i<=op;i++)
	{
		ans+=f[n][0][i];//将第n个点，有0个未开合的序列，总的不和谐度为k的方案数都加起来 
		ans%=mod;
	}
	printf("%d\n",ans);
	return 0;
}
  
```


---

## 作者：lahlah (赞：6)

[CF626F Group Projects](https://www.luogu.org/problem/CF626F)

题意

题目大意已经说得很清楚了
题解

神仙~~套路~~ DP？？？？？

首先不考虑顺序的话就是直接把**原数组从小到大排个序**

然后考虑DP就相当于是括号匹配

 好像有点抽![在这里插入图片描述](https://img-blog.csdnimg.cn/20191108155312728.png)

左括号的代价就是负的，然后右括号的代价就是正的

设$f[i][j][k]$表示前$i$个数，还有$j$个没有被匹配,代价为$k$的方案数


转移十分简单

- $f[i+1][j+1][k -a[i]] +=f[i][j][k]$   作为左括号（集合中最小的那个数）

- $f[i+1][j-1][k+a[i]]+=f[i][j][k]*j$ 匹配掉一个左括号(作为集合中最大的那个数)

- $f[i+1][j][k] += f[i][j][k]*(j+1)$ 作为前面的一个未被匹配的集合的中间值或者自己成为一组




答案就是$\sum f[n][0][0...k]$


然后可以发现这个转移是$O(1)$的，但是状态数是$O(n^2 \sum a[i])$


发现直接GG了


通过题目可以发现$k<=1000$也就是说最后状态代价最多只有$0\sim1000$是有用的，但是上面转移$k$的范围是$-\sum a[i]  \sim \sum a[i]$会逝世

___
正解


考虑差分，那原来最大值减最小值就可以转换为差分数组的一段的和

那样就只有加没有减了

转移最后一维大于$k$的就可以丢掉了
考虑转移

和上面的差不多，比较麻烦的就是代价的计算

就是当前差分乘上还没有被匹配的集合的个数

即$nxt = k +(a[i+1] - a[i]) *j$

然后转移就和前面一毛一个样了

code:
```cpp

#include<bits/stdc++.h>
#define ll long long
#define N 505
#define mod 1000000007
using namespace std;
void Add(int &x, int y) {
	x += y;
	if(x >= mod) x-= mod;
}
int n, m, dp[2][N][N << 1], a[N];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	dp[0][0][0] = 1;
	for(int i = 0; i < n; i ++) {
		int fr = i & 1, to = fr ^ 1;
		memset(dp[to], 0, sizeof dp[to]);
		for(int j = 0; j <= n; j ++) {
			for(int k = 0; k <= m; k ++) {
				
				int nxt = k; Add(nxt, (ll)(a[i + 1] - a[i]) * j);
				if(nxt > m || !dp[fr][j][k]) continue;//printf("%d %d %d %d  %d %d\n", fr, to, j, k, nxt, i);
				Add(dp[to][j + 1][nxt], dp[fr][j][k]); // zi li yi zu
				if(j) Add(dp[to][j - 1][nxt], (ll)dp[fr][j][k] * j % mod);// xiao yi zu
				Add(dp[to][j][nxt], (ll)dp[fr][j][k] * (j + 1) % mod); // bu xuan huo zuo wei zhong jian zhi
			}
		}
	}
	int ans = 0;
	for(int i = 0; i <= m; i ++) Add(ans, dp[n & 1][0][i]);
	printf("%d", ans);
	return 0; 
}
```


总结


 ~~我写DP像***~~

对于这种DP要把状态巧妙转化一下
转化的方法一般有

- 把贡献拆开
- 差分
-  看题解（划掉

---

## 作者：一架飞机 (赞：5)

这道题虽然是个纯 dp，但是非常还是高级。

# 暴力
把所有数按大小放在数轴上，每一组的所有数字一定在以最小值为左端点，最大值为右端点的线段上（线段内的数不一定在这个组里）。把 $a_i$ 排序，每次考虑放第 i 大的数，它可以：成为一个线段的右端点（结束这个线段，贡献加 $a_i$）；成为左端点（开始一个线段，贡献减 $a_i$）；在一个还没结束的线段中间（不做贡献）；自己独自做一个线段（其实和上一个转移是一样的）。

设 $dp_{i,j,k}$ 表示放了前 i 个点，还有 j 条线段没有结束，当前贡献为 k 的方案数。转移方程：
$$ dp[i][j][k]+=
\left\{
\begin{aligned}
&dp[i-1][j+1][k-a[i]]*(j+1) \\
&dp[i-1][j-1][k+a[i]]\\
&dp[i-1][j][k]*(j+1)
\end{aligned}
\right.
$$


虽然 k 最后只会用到 $0 \sim K$，但是中间的贡献可以是 $-\sum a_i \sim \sum a_i$，太大了。

# 正解
所以我们转换计算贡献的方式，让贡献保持递增。可以发现：最大值减最小值等于这条线段的长度。考虑差分。每次放一个数时，就把所有还没有结束的线段的贡献加 $a_i-a_{i-1}$。

设 $x=a_i-a_{i-1}$。

转移方程：
$$ dp[i][j][k]+=
\left\{
\begin{aligned}
&dp[i-1][j-1][k-x*(j-1)]\\
&dp[i-1][j+1][j+1][k-x*(j+1)]*(j+1)\\
&dp[i-1][j][k-x*j]*(j+1)
\end{aligned}
\right.
$$


---

## 作者：pigstd (赞：3)

首先先把 $a$ 排序。看到这个题目可能会想到 dp，但是如果直接 dp 的话比较难转移。设每组第一个数是 $l$，最后一个数是 $r$，那么这段区间的贡献就是 $a_r-a_l$，这提示我们可以把贡献拆开来。一个一个加数的时候，对于每一组，如果这一组里的数已经全部加完了那么就称这一组是闭合的。那么对于新加的一个数 $a_i$，有以下 $4$ 种可能：

- 加到了前面任何一个没有闭合的组里，这一组还是没有闭合，对总数的贡献是 $0$。
- 加到了前面任何一个没有闭合的组里，让这一组闭合了，对总数的贡献是 $a_i$。
- 新成立了一个没有闭合的组，这一组没有闭合，对总数的贡献是 $-a_i$。
- 新成立了一个没有闭合的组，这一组闭合了（即这一组只有它一个数），对总数的贡献是 $0$。

那么可以设 $dp_{i,j,k}$ 表示前 $i$ 个数，有 $j$ 个未闭合区间，此时的总数为 $k$ 的情况，转移就分成上面四类转移：

$dp_{i,j,k}=dp_{i-1,j,k}\times j + dp_{i-1,j+1,k-a_i} \times (j+1)+dp_{i-1,j-1,k+a_i}+dp_{i-1,j,k}=(j+1)\times (dp_{i-1,j,k}+dp_{i-1,j+1,k-a_i})+dp_{i-1,j-1,k+a_i}$。

然而……这样子会出现负下标的情况，状态数是 $n^2 \sum a_i$ 级别的，过不去。

思考一下原因：计算贡献的时候有减有加，这样的话会让第三维的下标变的很小。如果把这个过程变成单调不减的过程，那么就没有那么多事情了。

那么，怎么变呢？差分！对于 $a_r-a_l$ 这个东西，把他转化成 $\displaystyle \sum_{i=l+1}^r {a_i-a_{i-1}}$。那么算加入第 $i$ 个数之和的贡献的时候，不就相当于是 $j \times (a_{i}-a{i-1})$ 了吗（$j$ 是之前没有闭合的组，显然每个没有闭合的组都会产生 $a_{i}-a_{i-1}$ 的贡献）。

那么可以轻松得到 dp 方程（$d=a_i-a_{i-1}$）：$dp_{i,j,k}=dp_{i-1,j,k-d\times j}\times j+dp_{i-1,j+1,k-d\times(j+1)}\times (j+1)+dp_{i-1,j-1,k-d\times (j-1)}+dp_{i-1,j,k-d\times j}=dp_{i-1,j,k-d\times j}\times (j+1)+dp_{i-1,j+1,k-d\times (j+1)}\times (j+1)+dp_{i-1,j-1,k-d\times (j-1)}$。时间复杂度 $O(n^2 k)$。

[code](https://www.luogu.com.cn/paste/x8yoc3oq)。

---

## 作者：vegetable_king (赞：1)

完全不需要提前计算贡献啊，为什么题解都是。

原题面中的 $k$ 在这里用 $m$ 表示。

将 $a$ 排序后，显然有 DP 设 $f_{i, j, k}$ 为考虑前 $i$ 个，有 $j$ 组还没有放 $\max$，当前不和谐度之和为 $k$ 的方案数。转移是显然的，每次加入一个数考虑它是新一组的唯一元素 / 新一组的 $\min$ / 之前一组的中间值 / 之前一组的 $\max$ 四种情况：

$$f_{i, j, k} = (j + 1)(f_{i - 1, j, k} + f_{i - 1, j + 1, k - a_i}) + f_{i - 1, j - 1, k + a_i}$$

直接这样转移，第三维中途可能会很小 / 很大，所以时间复杂度为 $O(n^2\sum a_i)$。

但我们可以剪枝啊！有很多状态最终是无法转移到最终合法状态的。

考虑一个状态 $f_{i, j, k}$ 能转移到的最小不和谐度。显然，将 $a_i$ 后面的 $j$ 个作前面 $j$ 组的 $\max$，剩下的单独成组即可。令 $sm = \sum_{p = i + 1}^{i + j} a_p$，即最终不和谐度为 $k + sm$。则 $k + sm \le m$ 时，$f_{i, j, k}$ 才是有用的。

将不等式变形，得到 $k \le m - sm$，这是 $k$ 的一个上界。而 $k$ 的下界 $lk$ 显然是 $-\sum_{p = i - j + 1}^i a_p$（在前 $i$ 个中选最后 $j$ 个作为 $\min$，剩下的单独成组），又因为 $a$ 的单调性，所以 $-sm \le lk \le k \le m - sm$（前面 $j$ 个加起来肯定小于等于后面 $j$ 个），则 $m - sm - lk \le m - sm + sm = m$，对于一对 $i, j$，有用的 $k$ 只有 $O(m)$ 个。

每次只转移有用的 $k$，时间复杂度即可减为 $O(n^2m)$。main code：

```cpp
for (int i = 1;i <= n;i ++){swap(f0, f1);
	for (int j = 0;j <= i && j <= n - i;j ++){
		int le = sm[i - j] - sm[i], ri = m - sm[i + j] + sm[i];
		for (int k = le;k <= ri;k ++){f1[j][k] = 0;
			add(f1[j][k], (j + 1ll) * f0[j][k] % mod);
			if (j && k + a[i] <= m) add(f1[j][k], f0[j - 1][k + a[i]]);
			if (j < n) add(f1[j][k], (j + 1ll) * f0[j + 1][k - a[i]] % mod);
			if (i == n && !j) add(ans, f1[j][k]);
		}
	}
}
```

---

## 作者：piggy123 (赞：1)

怀疑出题人的脑部构造，这是人类能想到的优化？？？？？？？？~~赛时好像F过得比E多。怎么这么多神仙，这已经成套路了吗……~~


首先，花几分钟口胡出来一个经典 DP，考虑 $dp_{i,j,k}$ 表示排序后数组前 $i$ 个位置，还剩下 $j$ 组没有匹配，当前和为 $k$ 的方案。转移容易。但是当你写出来你就会发现 $k$ 在转移过程中可以达到 $[-\sum a_i,\sum a_i]$，于是复杂度退化为 $O(n^2\sum a_i)$ ，过不去。

考虑一些常见优化：
1. 猜测合法的 $k$ 很少，写一发 TLE 与 MLE on 11
2. 猜测过小的 $k$ 可以忽略，写一发 WA on 11

然后不会了，看题解。

一个**套路**：$a_r-a_l=\sum_{i=l}^{r-1} a_{i+1}-a_i$。也就是**差分数组一段的和**，运用这个式子可以在 DP 中分拆贡献。

这个性质有什么用呢？我们注意到在有序数组上，**差分数组非负**。这样子，我们将每一组的贡献分拆，这样 $k$ 也是不降的，因为刚开始的 $k=0$，所以第三位就压到了 $O(k)$，总体就是时空 $O(n^2k)$。在实现中使用了滚动数组。

AC Code：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;

ll a[205];
const ll mod=1000000007;
ll dp[2][205][2005];

int main(){
	ll n,k;
	cin >> n >> k;
	for (ll i=1;i<=n;i++){
		cin>> a[i];
	}
	sort(a+1,a+1+n);
	dp[0][0][0]=1;
	for (ll i=0;i<n;i++){
	    for (ll j=0;j<=i;j++){
	        for (ll z=0;z<=1000;z++){
	            dp[i&1^1][j][z]=0;
	        }
		}
		for (ll j=0;j<=i;j++){
			for (ll z=0;z<=1000;z++){
				dp[i&1][j][z]%=mod;
				// 不和前面的合并 
				if (z+j*(a[i+1]-a[i])<=1000)
				dp[i&1^1][j][z+j*(a[i+1]-a[i])]+=dp[i&1][j][z]*(j+1)%mod;
				// 和前面的合并
				if (j>=1&&z+j*(a[i+1]-a[i])<=1000)
				dp[i&1^1][j-1][z+j*(a[i+1]-a[i])]+=dp[i&1][j][z]*j%mod;
				// 新建
				if (z+j*(a[i+1]-a[i])<=1000)
				dp[i&1^1][j+1][z+j*(a[i+1]-a[i])]+=dp[i&1][j][z]%mod;
			}
		}
	}
	ll ans=0;
	for (ll i=0;i<=k;i++)ans+=dp[n&1][0][i],ans%=mod;
	cout<< ans;
	return 0;
}

```


---

## 作者：FutaRimeWoawaSete (赞：1)

完全没想到要费用提前计算啊？                    

考虑分组这个东西，只能通过一些奇技淫巧变成一个在序列上正推的过程 DP，不妨考虑怎么转化题意。                 

由于一组的答案只和组的最小值以及最大值有关，又由于“分组”本身是无序的，不难想到先排个序，这样正着扫过去，每一组的最小值一定出现在最大值前面。           

然后这时候如果有人告诉你要费用提前计算那么你是不是就会了？       

由于我们发现，dp 的转移肯定得具有无后效性，现在的重难点在于转化成一个无后效性的题意。        

假设一组选择的最小值在 $a_l$，最大值在 $a_r$，那么一组的答案可以表示成 $\sum_{i = l} ^ {r - 1} a_{i + 1} - a_i$，这样就有费用提前计算的样子了，并且可以分摊贡献。

考虑维护 $dp_{i,j,p}$ 表示此时对于前 $i$ 个数还有 $j$ 个组没有确定最大值且此时的不和谐度之和已经为 $p$。             

那么将新的点 $a_{i + 1}$ 加入 dp 中，我们考虑这个点是作为一个组的起点，终点，单独成一组，或是直接被归入一个组中但不作为起/终点。       

不难发现这四种情况下，对于不和谐度的新增贡献都是 $(a_{i + 1} - a_i) \times j$，记 $dt = (a_{i + 1} - a_i) \times j$。


1. 对于单独成段，就直接转移：

$dp_{i + 1,j,p + dt} \leftarrow dp_{i,j,p}$

2. 对于被归入一个组中，我们不在意它被归入了哪个组，只知道它此时可以被归入 $j$ 个组，所以应该由 $dp_{i,j,p} \times j$ 转移：

$dp_{i + 1,j,p + dt} \leftarrow j \times dp_{i,j,p}$

3. 对于作为一个组的起点，那么不确定的组数量加 $1$，转移：

$dp_{i + 1,j + 1,p + dt} \leftarrow dp_{i,j,p}$

4. 对于作为一个组的终点，我们也不关心它被归入了哪个组，只知道它此时可以被归入 $j$ 个组，并且此时不确定的组数量减 $1$，转移：

$dp_{i + 1,j - 1,p + dt} \leftarrow dp_{i,j,p} \times j$

时空复杂度 $O(n^2k)$。



---

## 作者：hgzxwzf (赞：0)

## [CF626F](https://www.luogu.com.cn/problem/CF626F)

首先对答案有影响的一定是每组里的最大值和最小值，所以我们先将 $a$ 从大到小排序。

设 $dp_{i,j,k}$ 表示考虑了前 $i$ 个人，有 $j$ 个组还允许加人，$k$ 为每个组的最大值之和减去已经不允许加人的组的最小值之和。

如果为 $i$ 新开一个组，那么 $a_i$ 就是这个新组里最大的数，还允许加人的组多了一个，$dp_{i,j,k}=dp_{i-1,j-1,k-a_i}$；

如果让 $i$ 成为某一个组的最后一个人，那么 $a_i$ 就是这个组里最小的数，还允许加人的组少了一个，$dp_{i,j,k}=dp_{i-1,j+1,k+a_i}\times (j+1)$；

将 $i$ 孤立或者加入一个还允许加人的组，$a_i$ 不是最大也不是最小，或者 $a_i$ 即使最大也是最小，贡献都是 $0$，$dp_{i,j,k}=dp_{i-1,j,k}\times(j+1)$。

因为 $a$ 的和很大，最大达到 $10^5$ 所以我们 $\verb!dp!$ 数组的第三维也要开这么大，空间上显然无法接受，可以滚动数组优化。

时间上呢？我们可以忽略很多不合法的方案。

假设前 $sum=\sum_{j=1}^ia_j,res=\sum_{j=1}^na_j$。

$dp_{i,j,k}$ 的 $k$ 一定不会超过 $sum$，因为 $a_i$ 以及 $a_i$ 之前的数加起来才等于 $sum$。

其次，$k$ 超过了 $res-sum+v$（$v$ 题目中的限制）一定不合法，因为就算 $k$ 从 $i+1$ 开始一直减，最后也会大于 $v$。

最慢 $764ms$。

### Code：
```cpp
#include<cstdio>
#include<set>
#include<algorithm>
#include<vector>
#include<stack>
#include<cmath>
#include<vector>
#include<cstring>
#include<queue>
#include<string>
#include<iostream>
#include<map>
#include<bitset>

#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)
#define LL long long
#define pi pair<int,int>
#define mk make_pair
#define fi first
#define se second

using namespace std;
const int N=200+10,Max=1e5+10,mod=1e9+7;

int a[N],dp[2][N][Max];

inline int add(int x,int y)
{
	x+=y;
	if(x>=mod) x-=mod;
	return x;
}

int main()
{
	int n,v,sum=0,res=0,cur=0;
	scanf("%d%d",&n,&v);
	rep(i,1,n) scanf("%d",&a[i]),res+=a[i];
	sort(a+1,a+1+n,greater<int>());
	dp[0][0][0]=1;
	rep(i,1,n)
	{
		cur^=1;
		sum+=a[i];
		rep(j,0,i)
			rep(k,0,min(sum,res-sum+v))
			{
				dp[cur][j][k]=0;
				if(j&&k>=a[i]) dp[cur][j][k]=dp[cur^1][j-1][k-a[i]];
				if(k+a[i]<=min(sum,res+k)) dp[cur][j][k]=add(dp[cur][j][k],1ll*dp[cur^1][j+1][k+a[i]]*(j+1)%mod);
				dp[cur][j][k]=add(dp[cur][j][k],1ll*dp[cur^1][j][k]*(j+1)%mod);
			}
	}
	int ans=0;
	rep(k,0,v)
		ans=add(ans,dp[cur][0][k]);
	printf("%d",ans);
	return 0;
}
```


---


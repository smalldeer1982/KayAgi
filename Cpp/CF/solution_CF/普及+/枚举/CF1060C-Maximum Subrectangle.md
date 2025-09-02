# Maximum Subrectangle

## 题目描述

You are given two arrays $ a $ and $ b $ of positive integers, with length $ n $ and $ m $ respectively.

Let $ c $ be an $ n \times m $ matrix, where $ c_{i,j} = a_i \cdot b_j $ .

You need to find a subrectangle of the matrix $ c $ such that the sum of its elements is at most $ x $ , and its area (the total number of elements) is the largest possible.

Formally, you need to find the largest number $ s $ such that it is possible to choose integers $ x_1, x_2, y_1, y_2 $ subject to $ 1 \leq x_1 \leq x_2 \leq n $ , $ 1 \leq y_1 \leq y_2 \leq m $ , $ (x_2 - x_1 + 1) \times (y_2 - y_1 + 1) = s $ , and $ $$ \sum_{i=x_1}^{x_2}{\sum_{j=y_1}^{y_2}{c_{i,j}}} \leq x. $ $$

## 说明/提示

Matrix from the first sample and the chosen subrectangle (of blue color):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1060C/ea340f2e4123e359048067db39cb97e3a56962fb.png)Matrix from the second sample and the chosen subrectangle (of blue color):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1060C/29ed72ba75c43c8c56e95a795caca1696bad260c.png)

## 样例 #1

### 输入

```
3 3
1 2 3
1 2 3
9
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 1
5 4 2 4 5
2
5
```

### 输出

```
1
```

# 题解

## 作者：Bitter_Tea (赞：5)

## **这是一道数学题**

~~我似乎把小学的知识都还给老师了~~，qwq

本题是对小学的**乘法分配律**的考察

$$
\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}a_i\times b_i=\sum\limits_{i=1}^{n}a_i\times \sum\limits_{j=1}^{m}b_j
$$

看似没有什么变化，但是我们会发现现在一个子矩阵的和便可以看做一段$a$数列之和与一段$b$数列之和乘积的形式。

为了使子矩阵的面积尽量大，我们显然应该维护出一定长度的$a$数列和一定长度的$b$数列的区间和的最小值，直接$O(n^2)$暴力即可。
如果$fa_i \times fb_j\le x$，我们便可以用$i \times j$尝试更新最大面积。$fa_i$表示区间长度为$i$的$a$数列和的最小值。

注：要注意开$long long$，否则会炸掉。

$Code$
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define ll long long
using namespace std;
const int N=2005;
int sa[N],sb[N],fa[N],fb[N];
int x,n,m,a,ans;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		sa[i]=sa[i-1]+a;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&a);
		sb[i]=sb[i-1]+a;
	}
	memset(fa,0x3f,sizeof(fa));
	memset(fb,0x3f,sizeof(fb));
	for(int i=1;i<=n;i++)
	for(int j=1;j<=i;j++)
	fa[i-j+1]=min(fa[i-j+1],sa[i]-sa[j-1]);
	for(int i=1;i<=m;i++)
	for(int j=1;j<=i;j++)
	fb[i-j+1]=min(fb[i-j+1],sb[i]-sb[j-1]);
	scanf("%d",&x);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	if((ll)fa[i]*fb[j]<=x) ans=max(ans,i*j);
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：PR_CYJ (赞：4)

# [题目传送门](https://www.luogu.com.cn/problem/CF1060C)
# 思路
对于每个正方形，其权值
$$\begin{aligned} \sum_{i=c}^x \sum_{j=d}^y a_i \times b_j (1\le c < x\le n,1\le d < y \le m) \end{aligned}$$
可以通过乘法分配律化简为
$$\begin{aligned} \sum_{i=c}^x a_i \times \sum_{j=d}^y b_j (1\le c < x\le n,1\le d < y \le m) \end{aligned}$$
即一段 $a$ 数组的和以及一段 $b$ 数组的和。我们只需预处理出前缀和，再暴力枚举每一个正方形即可。

但是对于这道题 $1\le n,m \le 2000$ 的数据，$O(n^4)$ 的算法显然无法通过。所以考虑优化。可以注意到，对于每个正方形长度 $i$，我们可以预处理出 $a$ 数组长度为 $i$ 的子段的区间和的最小值，这其实是一种贪心的策略。对于宽度也是如此。这样就可以保证每次遍历到的正方形都是在该大小下最优的，从而避免了很多不必要的枚举，使算法时间复杂度下降到 $O(n^2)$，轻松通过。
# 代码
- 切勿抄袭！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3000;
int a[N],b[N],mina[N],minb[N];
int main()
{
	int n,m,t,k,ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>t;
		a[i]=a[i-1]+t;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>t;
		b[i]=b[i-1]+t;
	}
	cin>>k;
	memset(mina,127,sizeof(mina));
	memset(minb,127,sizeof(minb));//因为是求最小值，所以一定要赋一个较大的初值 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			mina[i-j+1]=min(mina[i-j+1],a[i]-a[j-1]);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=i;j++)
			minb[i-j+1]=min(minb[i-j+1],b[i]-b[j-1]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if ((long long)(mina[i])*minb[j]<=k)//一定要开 long long ！！！ 
				ans=max(ans,i*j);
	cout<<ans<<endl;
}
```

---

## 作者：ztz11 (赞：2)

## 一场惨淡的cf

本来认为要掉分，~~然后rating涨了18？~~

这道题是个~~傻逼~~题，然后被卡了20min

由题可知，对于矩阵中每个位置的值是可以用乘法算出来的

那么一个子矩阵的值是可以O(1)算出来的

**计算方法如下：**

因为$a_{i,j}$=$x_i*y_j$

所以对于子矩阵每一列的的和，我们可以用前缀和算出大小

$$\sum_{i=x_1}^{x_2} a_{i,j}=(qzhy[x_2]-qzhy[x_1-1])\times y[j]$$

然后，在这个式子基础上可以再按前缀和跑一遍，就是答案

原始式子可以化为：

$$\sum_{i=x_1}^{x_2} \sum_{j=y_1}^{y2}a_{i,j}=(qzhy[y_2]-qzhy[y_1-1])\times (qzhx[x_2]-qzhy[x_1-1])$$

也就是说，当子矩阵长宽唯一时，矩阵最小值具有唯一性，且十分好算

然后怎么做呢？

我们可以$n^2$和$m^2$分别求出$x$和$y$在长度分别为$i$和$j$时的最小区间值

然后$n\times m$枚举矩阵长和宽

每次O(1)判断合法性即可
```cpp
#include<iostream>
#include<cstdio>
#define rii register int i
#define rij register int j
#define int long long
using namespace std;
int qzhx[2005],qzhy[2005],minx[2005],miny[2005],lim;
int n,m,ans;
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(rii=1;i<=n;i++)
	{
		scanf("%lld",&qzhx[i]);
		qzhx[i]+=qzhx[i-1];
	}
	for(rii=1;i<=m;i++)
	{
		scanf("%lld",&qzhy[i]);
		qzhy[i]+=qzhy[i-1];
	}
	for(rii=1;i<=n;i++)
	{
		minx[i]=2147483647;
	}
	for(rij=1;j<=m;j++)
	{
		miny[j]=2147483647;
	}
	for(rii=1;i<=n;i++)
	{
		for(rij=1;j+i-1<=n;j++)
		{
			minx[i]=min(minx[i],qzhx[j+i-1]-qzhx[j-1]);
		}
	}
	for(rii=1;i<=m;i++)
	{
		for(rij=1;j+i-1<=m;j++)
		{
			miny[i]=min(miny[i],qzhy[j+i-1]-qzhy[j-1]);
		}
	}
	cin>>lim;
	for(rii=1;i<=n;i++)
	{
		for(rij=1;j<=m;j++)
		{
			if(minx[i]*miny[j]<=lim)
			{
				ans=max(ans,i*j);
			}
		}
	}
	cout<<ans;
}
```

---

## 作者：Erica_N_Contina (赞：1)

## 思路

我们考虑子矩阵的实质是什么。

假设子矩阵 $[(a,b)(x,y)]$，则这个子矩阵中的每一个项目为 $a_i\times b_j, i\in [a,x],j\in [b,y]$。

那么这个矩形中的所有值的和就可以表示为 $s=\sum\limits_{i=a}^x\sum\limits_{j=b}^y a_i\times b_y$。

我们考虑对这个式子进行变形，$s=\sum\limits_{i=a}^x a_i\times \sum\limits_{j=b}^y b_j$，这时我们可以考虑枚举 $a,b,x,y$，但很明显过不去的。

我们可以考虑 $O(n^2)$ 预处理。

我们处理出 $b$ 中区间和 $≤i(i\in [1,m])$ 的最长区间长度。然后我们枚举 $x,a$，$\log m$ 求解。

预处理时，我们定义结构体 `{len,sum}`，然后以 $sum$ 从小到大为第一关键字，$len$ 从大到小为第二关键字排序，然后从前往后扫描一遍，求出前缀最大值数组。然后在枚举 $a,x$ 时，二分查找前缀最大值中 $sum≤n\div(\sum\limits_{i=a}^x a_i)$ 的 $len$。

复杂度为 $O(n^2\log n)$。

带个 $\log $ 多不好呀，或者我们可以换一种思路——我们还是 $O(n^2)+O(m^2)$ 预处理，分别对数组 $a,b$ 预处理出对于每一个长度 $i\in [1,n],j\in [1,m]$ 的区间的区间和最小值。

然后我们 $O(nm)$ 枚举数组 $a,b$ 中的分别的长度 $i,j$，$O(1)$ 判定即可。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . FancyKnowledge .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//
#include<bits/stdc++.h>

//
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
#define err(fmt, ...) fprintf(stderr, "[%d] : " fmt "\n", __LINE__, ##__VA_ARGS__)
///*
#define pr pair<double,int>
#define pf first
#define ps second
#define pb push_back
//*/

//
using namespace std;
//
const int N=2e3+5;
const int M=1e3;
const int MOD=1e9+7;
const int MMOD=903250223;
const int INF=1e9;
const int IINF=1e18;
const db eps=1e-9;
//
int n,m,qa[N],qb[N],la[N],lb[N],a,b,x,ans;

void solve(){
	//nothing in your main function??!
	scanf("%lld%lld",&n,&m);
	
	memset(la,0x3f3f,sizeof la);
	memset(lb,0x3f3f,sizeof lb);
	
	for(int i=1;i<=n;i++){
		cin>>a;qa[i]=qa[i-1]+a;
	}
	for(int j=1;j<=m;j++){
		cin>>b;qb[j]=qb[j-1]+b;
	}
	cin>>x;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			la[j-i+1]=min(la[j-i+1],qa[j]-qa[i-1]);
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=i;j<=m;j++){
			lb[j-i+1]=min(lb[j-i+1],qb[j]-qb[i-1]);
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(lb[j]*la[i]<=x)ans=max(ans,i*j);
		}
	}
	
	
	printf("%lld\n",ans);
	return ;
}

signed main(){

//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	freopen(".txt","w",stderr);

		
	solve();
	
	return 0;
}

//check your long long and the size of memery!!!

```




---

## 作者：hswfwkj_ (赞：0)

根据这个矩阵的性质，很容易发现如果你选择了左上角坐标为 $(x1, y1)$，右下角坐标为 $(x2, y2)$ 的矩阵，总和就是 $\sum_{i = x1}^{x2}a_i \times \sum_{i = y1}^{y2} b_i$。

那么考虑枚举 $x1$ 和 $x2$，通过维护前缀和快速确定区间和，然后便可以得出 $b$ 数组中选取的区间和最大为 $x$ 除以 $a$ 数组的区间和。先对 $b$ 数组进行预处理，得出对于确定最大区间和的情况下，最大区间长度是多少即可。

时间复杂度 $O(n^2)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, x;
int a[2005], b[2005];
int d[4000005];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> a[i], a[i] += a[i - 1];
	for(int i = 1; i <= m; i++)
		cin >> b[i], b[i] += b[i - 1];
	cin >> x;
	for(int len = m; len; len--)
	{
		int k = INT_MAX;
		for(int i = 1; i + len - 1 <= m; i++)
			k = min(k, b[i + len - 1] - b[i - 1]);
		d[k] = len;
	}
	for(int i = 1; i <= 4000000; i++)
	{
		if(d[i]) continue;
		d[i] = d[i - 1];
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j++)
			ans = max(ans, (j - i + 1) * d[min(x / (a[j] - a[i - 1]), 4000000)]); 
	cout << ans;
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

多少是有点诈骗，一开始想到二分答案什么混乱邪恶的东西上去了

$\sum \sum a_{i}\times b_j=(\sum a_i)\times (\sum b_j)$

即原题转化为：求 $a,b$ 的各一个子串，两个子串的和乘积小于 $x$ 且长度乘积最大。

对于某个长度 $L$，我们可以 $O(n)$ 的求出 $a,b$ 中长度为 $L$ 的最小的子串和。设为 $A_{L},B_{L}$。

原题再度转化为求一个满足 $A_{L_0}\times B_{L_1}\le x$ 的 $L_0\times L_1$ 最大值。

这个 $O(n^2)$ 暴力下就好了。

代码咕着。

---


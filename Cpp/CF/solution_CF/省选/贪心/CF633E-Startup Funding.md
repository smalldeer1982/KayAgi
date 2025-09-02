# Startup Funding

## 题目描述

An e-commerce startup pitches to the investors to get funding. They have been functional for $ n $ weeks now and also have a website!

For each week they know the number of unique visitors during this week $ v_{i} $ and the revenue $ c_{i} $ . To evaluate the potential of the startup at some range of weeks from $ l $ to $ r $ inclusive investors use the minimum among the maximum number of visitors multiplied by $ 100 $ and the minimum revenue during this period, that is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633E/d4c95097082aa3764e2e11310a38092f1681fe02.png)The truth is that investors have no idea how to efficiently evaluate the startup, so they are going to pick some $ k $ random distinct weeks $ l_{i} $ and give them to managers of the startup. For each $ l_{i} $ they should pick some $ r_{i}>=l_{i} $ and report maximum number of visitors and minimum revenue during this period.

Then, investors will calculate the potential of the startup for each of these ranges and take minimum value of $ p(l_{i},r_{i}) $ as the total evaluation grade of the startup. Assuming that managers of the startup always report the optimal values of $ r_{i} $ for some particular $ l_{i} $ , i.e., the value such that the resulting grade of the startup is maximized, what is the expected resulting grade of the startup?

## 说明/提示

Consider the first sample.

If the investors ask for $ l_{i}=1 $ onwards, startup will choose $ r_{i}=1 $ , such that max number of visitors is $ 3 $ and minimum revenue is $ 300 $ . Thus, potential in this case is $ min(3·100,300)=300 $ .

If the investors ask for $ l_{i}=2 $ onwards, startup will choose $ r_{i}=3 $ , such that max number of visitors is $ 2 $ and minimum revenue is $ 200 $ . Thus, potential in this case is $ min(2·100,200)=200 $ .

If the investors ask for $ l_{i}=3 $ onwards, startup will choose $ r_{i}=3 $ , such that max number of visitors is $ 1 $ and minimum revenue is $ 300 $ . Thus, potential in this case is $ min(1·100,300)=100 $ .

We have to choose a set of size $ 2 $ equi-probably and take minimum of each. The possible sets here are : $ {200,300} $ , $ {100,300} $ , $ {100,200} $ , effectively the set of possible values as perceived by investors equi-probably: $ {200,100,100} $ . Thus, the expected value is $ (100+200+100)/3=133.(3) $ .

## 样例 #1

### 输入

```
3 2
3 2 1
300 200 300
```

### 输出

```
133.3333333
```

# 题解

## 作者：subcrip (赞：1)

其实思路和其他题解是一样的，但是想补充一个结论：

> 当 $l$ 向左移动时，最优的 $r$ 也一定（非严格）向左移动。

因为 $\min$ 里面的两个函数一个是单调递增的，另一个是单调递减的，比较直观，所以可以通过画图来验证这个结论。因此，**可以直接使用双指针维护 $r$ 的位置，而不需要二分查找。**

以及，取对数算组合数好妙啊，我是通过当答案比较大的时候再除阶乘来同时避免 $nan$ 和 $0.0$ 的。

```cpp
void solve() {
	read(int, n, k);
	readvec(int, a, n);
	readvec(int, b, n);
	sparse_table<int> range_max(a.rbegin(), a.rend(), functor(max));
	sparse_table<int> range_min(b.rbegin(), b.rend(), functor(min));

	vector<int> c(n);
	int j = n - 1;
	for (int i = n - 1; ~i; --i) {
		auto calc = [&] (int j) { return min(100 * range_max.query(i, j), range_min.query(i, j)); };
		while (j > i and calc(j - 1) >= calc(j)) {
			j -= 1;
		}
		c[i] = calc(j);
	}

	sort(c.begin(), c.end(), greater());

	ld p = 1;  // long double
	int ptr = 0;

	if (k - 1 != 0) p /= k - 1;

	ld q = p;
	ld res = 0;
	for (int i = k - 1; i < n; ++i) {
		if (i != 0) q *= i;
		if (i != k - 1) q /= i - k + 1;
		while (q > 1e9 and ptr < k) {
			q /= n - ptr;
			res /= n - ptr;
			ptr += 1;
		}
		res += q * c[i];
	}
	for (int i = 0; i < k; ++i) {
		res *= i + 1;
		while (res > 1e9 and ptr < k) {
			res /= n - ptr;
			ptr += 1;
		}
	}

	while (ptr < k) {
		res /= n - ptr;
		ptr += 1;
	}


	cout << fixed << setprecision(50);
	cout << (long double)res << '\n';
	
}
```

---

## 作者：Autumn_Rain (赞：1)

首先观察题目中这个式子。

$p(l,r)=\min\{100\times\max\limits_{l\leq i\leq r} v_i,\ \min\limits_{l\leq i\leq r} c_i\}$，$a_l=\max\limits_{l\leq r\leq n} p(l,r)$。(我把 $q$ 数组改成 $a$ 了)

区间最大最小值首先想到线段树和 ST 表，这里选用较为好写的后者。[ST 表](https://www.luogu.com.cn/problem/P3865) 主要运用类 dp 的方法实现 $O(n \log_{}{n} )$ 预处理，$O(1)$ 查询，足以通过本题。为了方便，先统一把 $v_{i}$ 乘上 $100$，不影响查询结果。

再用自然语言转换一下上式变成：找到一段以 $l$ 为左端点的区间使得这段区间内 $\min(\max v_{i},\min c_{i})$ 最大，记这个值为 $a_{l}$，用 ST 表易求。现在问题简化为从数组 $a$ 中随机选择 $k$ 个数，设我们选择这些数中的最小值为 $x$，如果我们按非递减顺序对 $a$ 进行排序，那么答案即为：

$$ E(x)=\frac{\sum_{i=1}^{n-k+1} a_{i} \times C_{n-i}^{k-1}}{C_{n}^{k}}$$

期望其实类似加权平均数，总情况有 $C_{n}^{k}$ 种故要除掉。$C_{n-i}^{k-1}$ 则是因为我们的 $a$ 已经排序，想要当前的 $a_{i}$ 是选中 $k$ 个中最小的，则需要在比她大的剩下 $n-i$ 个里面选剩下 $k-1$ 个数字。为什么只加到 $n-k+1$？因为再往后选，比当前 $a$ 大的数字不足 $k$ 个，贡献都是 $0$。

当然 $C_{n}^{k}$ 会很大，不直接计算而是算它和分子的比率。

时间复杂度：$O(n\log n)$。

这题时限不知为何卡的很严格。所以你的 ST 表很可能会寄。以下提供我的 TLE 解决方案。

1. 用 ```__lg``` 函数而不是 ```log2```，而且必须要事先预处理。
2. 快读什么的全加上，能不开长整型就不要开。

可以参考一下我的提交记录。

[Time limit exceeded on test 6](https://codeforces.com/problemset/submission/633/295884976)

[Time limit exceeded on test 11](https://codeforces.com/problemset/submission/633/296009241)

AC code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define db double
const int N=1e6+10;
int n,k;
int v[N],c[N];
int mx[N][20];
int mn[N][20];
int a[N];
int lg2[N];
db s[N];
db ans;
int qrymx(int l,int r){
	int k=lg2[r-l+1];
	return max(mx[l][k],mx[r-(1<<k)+1][k]);
}
int qrymn(int l,int r){
	int k=lg2[r-l+1];
	return min(mn[l][k],mn[r-(1<<k)+1][k]);
}
int qry(int l,int r){
	return min(qrymx(l,r),qrymn(l,r));
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0); 
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>v[i];
		mx[i][0]=v[i]*100;
	}
	for(int i=1;i<=n;i++){
		cin>>c[i];
		mn[i][0]=c[i];
	}
	s[0]=0;
	for(int i=1;i<=1e6;i++){
		s[i]=s[i-1]+log(i);
		lg2[i]=__lg(i);
	}
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			mx[i][j]=max(mx[i][j-1],mx[i+(1<<(j-1))][j-1]);
			mn[i][j]=min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
		}
	}
	//a[l]先增后减 
	for(int i=1;i<=n;i++){
		int l=i,r=n;
		int res=i;
		while(l<=r){
			int mid=(l+r)>>1;
			//注意到 maxv<minc 时答案呈上升趋势 
			if(qrymx(i,mid)<qrymn(i,mid)){
				res=mid;
				l=mid+1;
			}
			else{
				r=mid-1;
			}
		}
		a[i]=max(qry(i,res),qry(i,res+1));
		//二分出使之最大的r值 
	}
	sort(a+1,a+1+n);
	for(int i=1;i<=n-k+1;i++){
		db t=log(k)+(s[n-i]+s[n-k])-(s[n-i-k+1]+s[n]);
		ans+=a[i]*exp(t);//拆项计算 
		//exp(t)是以e为底的对数 
	}
	cout<<fixed<<setprecision(7)<<ans;
	return 0;
}
```

为什么 $a$ 数组会是先增后减？为什么 $maxv < minc$ 时答案呈上升趋势？[证明在此处](https://www.luogu.com.cn/paste/ufkzi7n4)。

---

## 作者：海之眷恋8 (赞：1)

# 超级~~水~~(nan)题

## 简略思路：

>**第一步：求出上面定义的Q[L]数组**

>**第二步：将Q数组进行排序，从小到大排序。**

>**第三步：计算概率，利用下面的公式：**

公式的解释，对于Q[t]，在Q[t]右边的数有n-t个，假设Q[t]要作为k个数中的最小值，那么其余的k-1个数都必须在它右边，

所以在n-t个数中取k-1个数的每种方案中，都要计算一次Q[t],最后再除以总的方案数n中选k。



## 第一步：求Q数组

为了省事，直接让所有的V都乘上了100，所以公式变为：p(L,R)=min(max(区间内的V),min(区间内的C))。

容易看到，对于每个L，在R慢慢增加的情况下，p(L,R)先增后减（也有可能只增或只减），所以二分法可以求出最大p值。

但要注意，不能用p值的大小作为二分法的判断量，因为对于很多个R，p(L,R)的值是一样的，而当一样时，没法判断是在上升阶段还是在下降阶段。

所以二分法其实是在判断max(区间内V)和min(区间内C)这两个值哪个小，如果max(区间内V)小，那么处于上升趋势，如果min(区间内C）小，那么处于下降趋势。

用二分法可以找到上升趋势到下降趋势的分界线，我的代码中，用二分法找到上升部分的最后一个值，但是此时下降部分的第一个值仍然可能大于上升部分的最后一个值，

所以二分法求出上升部分的最后一个值之后，还需要再往前看一个数，看一下值是否更大。



二分法的判断中，需要求出max(区间内V)和min(区间内C)这两个值，于是需要一个数据结构来维护这个值。

方法有二： 

> 1.非递归线段树  （  43100KB  ，2.9秒）  

> 2.Sparse Table （176100KB ，2.4秒）

补充：Sparse Table的查询中会用到log2这个函数，将log2进行预处理之后，查询就是真正的O(1)了，这种做法是：(180000KB , 1.5秒)。

**题目时限是3秒。**

非递归线段树O(n)建树，O(logn)查询，加上二分法的O(logn)，所以计算Q值的复杂度是O(n(logn)^2) ，用时2.9秒。

Sparse Table O(nlogn)建表，用时2.4秒，预处理log2函数之后查询复杂度O(1)，用时1.5秒。

Sparse Table花的空间是非递归线段树的5倍，不过快了很多。

Sparse Table是刚刚发现的很神奇的算法，空间复杂度O(nlogn),查询复杂度O(1)，缺点就是不支持对数组的快速修改。

所以不需要修改的区间最值问题，就可以考虑使用Sparse Table来解决。



Sparse Table的思路（动态规划）以最大值为例：

建表：Max[ i ] [ j ] 表示区间 [ i , i + 2^j )的最值。

递推式：Max[ i ][ j ] = max(Max[ i ][ j - 1 ] , Max [i + (1<<(j-1)][ j ] )。

所以按照递推式，把所有可能用到的区间的Max表都建好。

这里说的是所有可能用到的区间，Max[ i ][ j ] 对应的区间是[ i , i + 2^j )，所以所有[ i , i + 2^j )在[1,n]以内的 i 和 j 的Max值都需要计算，而其余的都不需要计算。

代码中只计算了需要的部分，各种条件就是在保证对应的区间不出界（出界的后面一定不会用到，所以值不需要管）。

## 查询：

查询时，假设查询区间[s,t],那么先求k使得 (t-s+1)/2 < 2^k <= t-s+1   这时 t = floor(log2(t-s+1))，正的double转成int时自动取floor所以直接强制转换成int就可以了。

有了k之后，已经知道了从s开始2^k个数的最大值（即Max[s][k]），也知道了从t往前2^k个数的值（即Max[t - (1<<k)+1][k]）。

取这两个值的最大值就是区间s到t的最大值，所以差不多可以算是O(1)查询。



代码如下：
```cpp
//Sparse Table 
int Max[maxn][21];
int Min[maxn][21];
void BuildSparseTable(){
	//填好j=0的值 
	for(int i=1;i<=n;++i) Max[i][0]=V[i],Min[i][0]=C[i];
	//计算Sparse Table 
	for(int j=1;(1<<j) <= n;++j){
		for(int i=1;i+(1<<j)-1<=n;++i){
			Max[i][j]=max(Max[i][j-1],Max[i+(1<<(j-1))][j-1]);
			Min[i][j]=min(Min[i][j-1],Min[i+(1<<(j-1))][j-1]);
		}
	}
}
void Query(int L,int R,int &MaxV,int &MinC){
	int k = int(log2(R-L+1.0));
	MaxV=max(Max[L][k],Max[R-(1<<k)+1][k]);
	MinC=min(Min[L][k],Min[R-(1<<k)+1][k]);
}
```
# 第二步：对Q排序
不用多说，直接sort函数
# 第三步：计算答案
在计算中要注意不能每次都重新求C，那样会超时，注意到C每次只变了下标，所以可以利用组合数的递推关系，来递推每一个C，减少了很多计算量。

然后附上3份代码：

## 非递归线段树（43100KB，2.9秒）：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include<iomanip>
#include <cstring>
#include <algorithm>
#define out(i) <<#i<<"="<<(i)<<"  "
#define OUT1(a1) cout out(a1) <<endl
#define OUT2(a1,a2) cout out(a1) out(a2) <<endl
#define OUT3(a1,a2,a3) cout out(a1) out(a2) out(a3)<<endl
#define LD long double
#define maxn 1000007
using namespace std;
//非递归线段树 
int Max[maxn<<2],Min[maxn<<2],N;
void Init(int n){//初始化 
	N = 1; while(N < n + 2) N <<= 1;
	for(int i = 2*N;--i;) Max[i]=0,Min[i]=10000000;
}
void UpdateMax(int X,int V){//点更新
	for(int s = N + X;s;s >>= 1) 
		if(V > Max[s]) Max[s] = V;
		else break;
}
void UpdateMin(int X,int V){//点更新
	for(int s = N + X;s;s >>= 1) 
		if(V < Min[s]) Min[s] = V;
		else break;
}
void Query(int L,int R,int &MaxV,int &MinC){//获取区间最大值最小值 
	MaxV=0;MinC=10000000;
	for(int s=N+L-1,t=N+R+1;s^t^1;s>>=1,t>>=1){
		if(~s&1) MaxV=max(MaxV,Max[s^1]),MinC=min(MinC,Min[s^1]);
		if( t&1) MaxV=max(MaxV,Max[t^1]),MinC=min(MinC,Min[t^1]);
	}
}
int n,k,x;
int V[maxn];//题目数据V 
int C[maxn];//题目数据C 
int Q[maxn];//排序前：每个L对应的最优R值对应的答案
//二分查找 
void BinarySearch(int X){
	int L=X,R=n+1,M,MaxV,MinC;//[L,R) last Max <= Min
	while((L+1)^R){
		M = (L+R)>>1;
		Query(X,M,MaxV,MinC);
		if(MaxV <= MinC) L = M;
		else R = M;
	}
	Query(X,L,MaxV,MinC);
	Q[X]=min(MaxV,MinC);
	if(L < n) Q[X]=max(Q[X],min(max(MaxV,V[L+1]),min(MinC,C[L+1])));
}
int main(void)
{
	while(~scanf("%d%d",&n,&k)){
		Init(n);
		for(int i=1;i<=n;++i)	scanf("%d",&V[i]),UpdateMax(i,V[i]*=100);
		for(int i=1;i<=n;++i)   scanf("%d",&C[i]),UpdateMin(i,C[i]);
		//二分法计算从每个L开始的最优值
		for(int i=1;i<=n;++i) BinarySearch(i);
		//从小到大排序 
		sort(Q+1,Q+n+1);
		//计算结果 
		LD ANS=(LD)(0);
		LD CF=(LD)k/n;
		for(int t=1;t <= n-k+1;++t){
			ANS+=CF*Q[t];
			CF*=(LD)(n-k-t+1)/(n-t);
		}
		cout<<fixed<<setprecision(7)<<ANS<<endl;
	}
return 0;
}
```
## Sparse Table代码（176100KB,2.4秒）：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include<iomanip>
#include <cstring>
#include <algorithm>
#define out(i) <<#i<<"="<<(i)<<"  "
#define OUT1(a1) cout out(a1) <<endl
#define OUT2(a1,a2) cout out(a1) out(a2) <<endl
#define OUT3(a1,a2,a3) cout out(a1) out(a2) out(a3)<<endl
#define LD long double
#define maxn 1000007
using namespace std;
int n,k,x;
int V[maxn];//题目数据V 
int C[maxn];//题目数据C 
int Q[maxn];//排序前：每个L对应的最优R值对应的答案
 
//Sparse Table 
int Max[maxn][21];
int Min[maxn][21];
void BuildSparseTable(){
	//填好j=0的值 
	for(int i=1;i<=n;++i) Max[i][0]=V[i],Min[i][0]=C[i];
	//计算Sparse Table 
	for(int j=1;(1<<j) <= n;++j){
		for(int i=1;i+(1<<j)-1<=n;++i){
			Max[i][j]=max(Max[i][j-1],Max[i+(1<<(j-1))][j-1]);
			Min[i][j]=min(Min[i][j-1],Min[i+(1<<(j-1))][j-1]);
		}
	}
}
void Query(int L,int R,int &MaxV,int &MinC){
	int k = int(log2(R-L+1.0));
	MaxV=max(Max[L][k],Max[R-(1<<k)+1][k]);
	MinC=min(Min[L][k],Min[R-(1<<k)+1][k]);
}
//二分查找 
void BinarySearch(int X){
	int L=X,R=n+1,M,MaxV,MinC;//[L,R) last Max <= Min
	while((L+1)^R){
		M = (L+R)>>1;
		Query(X,M,MaxV,MinC);
		if(MaxV <= MinC) L = M;
		else R = M;
	}
	Query(X,L,MaxV,MinC);
	Q[X]=min(MaxV,MinC);
	if(L < n) Q[X]=max(Q[X],min(max(MaxV,V[L+1]),min(MinC,C[L+1])));
}
int main(void)
{
	while(~scanf("%d%d",&n,&k)){
		for(int i=1;i<=n;++i)	scanf("%d",&V[i]),V[i]*=100;
		for(int i=1;i<=n;++i)   scanf("%d",&C[i]);
		BuildSparseTable();
		//二分法计算从每个L开始的最优值
		for(int i=1;i<=n;++i) BinarySearch(i);
		//从小到大排序 
		sort(Q+1,Q+n+1);
		//计算结果 
		LD ANS=(LD)(0);
		LD CF=(LD)k/n;
		for(int t=1;t <= n-k+1;++t){
			ANS+=CF*Q[t];
			CF*=(LD)(n-k-t+1)/(n-t);
		}
		cout<<fixed<<setprecision(7)<<ANS<<endl;
	}
return 0;
}
```
# Sparse Table + 预处理log2函数  (180000KB , 1.5秒)：
```
#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include<iomanip>
#include <cstring>
#include <algorithm>
#define out(i) <<#i<<"="<<(i)<<"  "
#define OUT1(a1) cout out(a1) <<endl
#define OUT2(a1,a2) cout out(a1) out(a2) <<endl
#define OUT3(a1,a2,a3) cout out(a1) out(a2) out(a3)<<endl
#define LD long double
#define maxn 1000007
using namespace std;
int n,k,x;
int V[maxn];//题目数据V 
int C[maxn];//题目数据C 
int Q[maxn];//排序前：每个L对应的最优R值对应的答案
 
//Sparse Table 
int Max[maxn][21];
int Min[maxn][21];
int Log2[maxn];//Log2[x] = floor(log2(x))  预处理，为了加速 
void BuildSparseTable(){
	//填好j=0的值 
	for(int i=1;i<=n;++i) Max[i][0]=V[i],Min[i][0]=C[i];
	//计算Sparse Table 和Log2[] 
	int j,D,H;
	for(j=1,D=2,H=1;D <= n;++j,D <<= 1,H <<= 1){
		for(int i=1;i+ D - 1<=n;++i){
			Max[i][j]=max(Max[i][j-1],Max[i+H][j-1]);
			Min[i][j]=min(Min[i][j-1],Min[i+H][j-1]);
		}
		for(int i=H;i<D;++i) Log2[i]=j-1;
	}
	for(int i=H;i<=n;++i) Log2[i]=j-1;
}
void Query(int L,int R,int &MaxV,int &MinC){
	int k = Log2[R-L+1];
	MaxV=max(Max[L][k],Max[R-(1<<k)+1][k]);
	MinC=min(Min[L][k],Min[R-(1<<k)+1][k]);
}
//二分查找 
void BinarySearch(int X){
	int L=X,R=n+1,M,MaxV,MinC;//[L,R) last Max <= Min
	while((L+1)^R){
		M = (L+R)>>1;
		Query(X,M,MaxV,MinC);
		if(MaxV <= MinC) L = M;
		else R = M;
	}
	Query(X,L,MaxV,MinC);
	Q[X]=min(MaxV,MinC);
	if(L < n) Q[X]=max(Q[X],min(max(MaxV,V[L+1]),min(MinC,C[L+1])));
}
int main(void)
{
	while(~scanf("%d%d",&n,&k)){
		for(int i=1;i<=n;++i)	scanf("%d",&V[i]),V[i]*=100;
		for(int i=1;i<=n;++i)   scanf("%d",&C[i]);
		BuildSparseTable();
		//二分法计算从每个L开始的最优值
		for(int i=1;i<=n;++i) BinarySearch(i);
		//从小到大排序 
		sort(Q+1,Q+n+1);
		//计算结果 
		LD ANS=(LD)(0);
		LD CF=(LD)k/n;
		for(int t=1;t <= n-k+1;++t){
			ANS+=CF*Q[t];
			CF*=(LD)(n-k-t+1)/(n-t);
		}
		cout<<fixed<<setprecision(7)<<ANS<<endl;
	}
return 0;
}
```
# 勿抄袭！！！！！！！！
>[原文](https://blog.csdn.net/zearot/article/details/50825559)


---


# Pair of Numbers

## 题目描述

Simon 有一个长度为 $ N $ 的正整数数列 $ a_1 , a_2 , \cdots , a_n $ ，现在他想找到这个数列中最长的一个区间，满足区间中有一个数可以整除区间中任意数。

## 样例 #1

### 输入

```
5
4 6 9 3 6
```

### 输出

```
1 3
2 
```

## 样例 #2

### 输入

```
5
1 3 5 7 9
```

### 输出

```
1 4
1 
```

## 样例 #3

### 输入

```
5
2 3 5 7 11
```

### 输出

```
5 0
1 2 3 4 5 
```

# 题解

## 作者：klii (赞：17)

# [题目传送门](https://www.luogu.com.cn/problem/CF359D)

### 题目大意：

给定一个长度为 $n(n <= 3e5)$ 的数列， 求出该数列中**最长的**满足条件的区间并输出该区间的左端点（所有）。

条件如下：
	
    该区间中存在一个数x使得x可以整除该区间内的所有数。
    


------------
# Solution
提供一种 $O(n)$ 的解法(貌似是目前最优解？)。

记 $l[i]$ 表示以 $a[i]$ 为 $x$， 能**连续**整除到的**最左端**的位置， $r[i]$ 同理。

则区间 $[l[i], r[i]]$为一个满足条件的区间， 求答案时扫一遍即可。

如何求 $l[i], r[i]$ ？



------------
## 引理：
若 $x$ 能整除的数集为 $S$, 则 $x$ 的 **因数** **也能整除** $S$ 中的**所有数**。

此结论显然成立，证明略去。


受此启发， 我们可以考虑用这个性质去求 $l[i]$。

大致代码如下:
```cpp
for (int i = 1; i <= n; i++) {
	l[i] = i; // 初始为自身 
	while (a[l[i] - 1] % a[i] == 0 && l[i] > 1) l[i] = l[l[i] - 1];
	//若左端点前面的数能被a[i]整除， 则l[i]可以扩展到左端点前一位的l 
}
```

这一过程（求出**所有**$l[i]$）的时间复杂度？ 可以证明是$O(n)$的。

------------
# 简略证明：

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/vj3ujonn.png)

红色部分所示的情况是不存在的。

原因是如果能跳到红色部分，$a[j]$必然能整除$a[i]$, 能整除$a[i]$意味着$a[j]$能整除$[l[i], i]$的所有数，显然会跳到$l[i]$。

**跳了一次后**，每跳多一次，就少了一个跳跃点，由于最多有n个跳跃点，最多跳$2n$次，复杂度即为$O(n)$。

------------
### 代码如下: ~~（短的离谱~~
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 3e5 + 12;
int n, a[N], l[N], r[N], maxl, cnt, p[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		l[i] = i; // 初始为自身 
		while (a[l[i] - 1] % a[i] == 0 && l[i] > 1) l[i] = l[l[i] - 1];
		//若左端点前面的数能被a[i]整除， 则l[i]可以扩展到左端点前一位的l 
	}
	for (int i = n; i >= 1; i--) {
		r[i] = i;
		while (a[r[i] + 1] % a[i] == 0 && r[i] < n) r[i] = r[r[i] + 1];
	} //同理 
	for (int i = 1; i <= n; i++) //找答案 
	if (r[i] - l[i] > maxl) {
		maxl = r[i] - l[i];
		p[cnt = 1] = l[i];
	} else if (r[i] - l[i] == maxl && p[cnt] != l[i]) p[++cnt] = l[i];
	//注意特判一段相同的数的情况 (p[cnt] != l[i]) 
	printf("%d %d\n", cnt, maxl);
	for (int i = 1; i <= cnt; i++) printf("%d ", p[i]);
	return 0;
}
```

如有疑问可在评论区提出，感谢阅读！

---

## 作者：Wings_of_liberty (赞：4)

# 分析
这道题最主要的问题就是如何判断一个区间是否满足条件（其中有一个数可以被所有数整除），很明显，一个区间内能被所有数整除的数一定是他们的最大公约数，并且，这个数一定是最小的数。所以说，不可以总司令。

所以说，这道题的关键就是维护每一个区间的最小值和 $\gcd$。对于 $\gcd$ 和 $\min$ 这种具有结合律的运算 $\gcd(a,b,c) = \gcd(a,\gcd(b,c))$，$\min(a,b,c) = \min(a,\min(b,c))$，我们很容易想到运用线段树维护，但是复杂度不够，这时感谢我的同学 [glorious_dream](https://blog.csdn.net/glorious_dream) 的提醒，选择了 ST 表，这样可以把线段树的 $O(\log n)$ 查询变成 $O(1)$。

# 注意
希望大家不要像我一样写类似代码时复制而忘记修改（我在写查询 $\gcd$ 时是用查询最小值的代码复制的，结果忘记修改数组名了）。

# 代码
```
#include <bits/stdc++.h>
using namespace std;
#define op(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
#define cl() fclose(stdin),fclose(stdout)
#define F(i,x,y) for(int i=(x);i<=(y);i++)
#define rF(i,x,y) for(int i=(x);i>=(y);i--)
typedef long long ll;
inline int read(){
	int ret=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(isdigit(ch)){
		ret=(ret<<3)+(ret<<1)+ch-'0';
		ch=getchar();
	}
	return ret*f;
}
const int MAX=3e5+10;
int n;
int ans;
int f[MAX][21],g[MAX][21];
int lg[MAX];
int ans2[MAX],cnt=0;
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int check_min(int l,int r){
    int k=lg[r-l+1]; 
    return min(f[l][k],f[r-(1<<k)+1][k]);
}
inline int check_gcd(int l,int r){
    int k=lg[r-l+1]; 
    return gcd(g[l][k],g[r-(1<<k)+1][k]);
}
inline bool check(int mid){
	int j,x,y;
	F(i,1,n-mid+1){
		j=i+mid-1;
		x=check_min(i,j);
		y=check_gcd(i,j);
		if(x==y){
			return true;
		}
	}
	return false;
}
inline void init(){
	n=read();
	F(i,2,n){
		lg[i]=lg[i>>1]+1;
	}
	F(i,1,n){
		f[i][0]=read();
		g[i][0]=f[i][0];
	}
	for(int j=1;(1<<j)<=n;j++){
    	for(int i=1;i+(1<<j)-1<=n;i++){
    		f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
    		g[i][j]=gcd(g[i][j-1],g[i+(1<<(j-1))][j-1]);
		}
	}
}
inline void work(){
	int l=1,r=n,mid;
	while(l<r){
		mid=((l+r)>>1)+1;
		if(check(mid)){
			l=mid;
		}else{
			r=mid-1;
		}
	}
	ans=l-1;
	int j,x,y;
	F(i,1,n-ans){
		j=i+ans;
		x=check_min(i,j);
		y=check_gcd(i,j);
		if(x==y){
			ans2[++cnt]=i;
		}
	}
	printf("%d %d\n",cnt,ans);
	F(i,1,cnt){
		printf("%d ",ans2[i]);
	}
}
int main(){
    init();
    work();
    return 0;
}
```


---

## 作者：xiangshengtao (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF359D)
## 题目大意
有一个长度为 $N$ 的正整数数列，找到这个数列中最长的一个区间，满足区间中有一个数 $x$ 可以整除区间中任意数。
## 思路
### 分析
“满足区间中有一个数 $x$ 可以整除区间中任意数。”“整除”我们或许会想到用 $\gcd$，然后仔细品味这一句话，首先我们可以得出，这一段区间的 $\gcd$ 一定小于等于这一段区间的 $\min$，然后带着这个思路继续往下走，若要满足区间中有一个数 $x$ 可以整除区间中任意数，那么就得满足这个区间的 $\min$ 等于这个区间的 $\gcd$。
### 方法
有思路了，方法自然也不难想，一段区间的 $\min$ 和这段区间的 $\gcd$ 怎么求。枚举是一种方法，但时间复杂度太高，于是我们就可以想到用倍增，倍增怎么做我在这里就不多说了，主要就是一段区间的前一半与后一半进行组合求 $RMQ$ 的方法。
## 总结
思路理顺了，接下来就是代码，最长区间长度怎么求，没错，就是二分答案，里面套个循环枚举当长度为 $len$ 时所有的情况，最后就是利用 $RMQ$ 判断。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,T,i,x,y,a[300010],f[300010][30],e[300010][30],sum,t,w,mid,bao,ans[300010];
int gcd(int x,int y){//简单的gcd
	int z=x%y;
	while (z>0) x=y,y=z,z=x%y;
	return y;
}
void rmq(){//利用倍增思想求RMQ，不仅仅是min可以用倍增，gcd也可以
	int i,j;
	for (i=1;i<=n;i++) f[i][0]=a[i];
	for (j=1;(1<<j)<=n;j++)
		for (i=1;i+(1<<j)-1<=n;i++)
			f[i][j]=gcd(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	for (i=1;i<=n;i++) e[i][0]=a[i];
	for (j=1;(1<<j)<=n;j++)
		for (i=1;i+(1<<j)-1<=n;i++)
			e[i][j]=min(e[i][j-1],e[i+(1<<(j-1))][j-1]);
}
bool pd(int len){//二分的判断
	int i,x,y,k,g=0;
	for (i=1;i<=n-len;i++){//枚举每一个区间左端点
		x=i;y=i+len;
		k=log2(y-x+1);
		if (gcd(f[x][k],f[y-(1<<k)+1][k])==min(e[x][k],e[y-(1<<k)+1][k])){//判断gcd是否等于min
			g++;
			if (g==1) sum=0;
			ans[++sum]=i;//保存左端点
		}
	}
	if (g>0) return true;
	else return false;//如果长度为len的区间找不到，返回false
}
int main(){
	scanf("%d",&n);
	for (i=1;i<=n;i++) scanf("%d",&a[i]);
	rmq();
	t=0;w=n-1;
	while (t<=w){//二分答案
		mid=(t+w)>>1;
		if (pd(mid)) bao=mid,t=mid+1;
		else w=mid-1;
	}
	printf("%d %d\n",sum,bao);
	for (i=1;i<=sum;i++) printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：happybob (赞：1)

## 题意

题目描述非常清晰。

## 思路

先考虑一个 $O(n^2)$ 级别的算法，就是暴力枚举每个 $a_i$，并对其向两边扩展，最坏情况 $O(n^2)$，但是在随机数据下跑得非常快。

想办法优化。

显然，我们发现枚举次数过多，所以考虑尽量少枚举一些。

对于每个 $a_i$，假设我们枚举到的区间是 $[l,r]$，显然对于每个 $j(l \leq j \leq r)$，都有 $a_i \mid  a_j$。显然地，我们可以发现对于每个 $a_j$ 重新枚举是没有必要的。

如何证明？首先，若 $a \mid b$，则 $a$ 的所有因数 $p_i \mid b$，那么，对于 $a_j$ 进行枚举时，假设枚举到的每一个数是 $a_k$，若 $a_j \mid a_k$，则一定有 $a_i \mid a_k$，也就是说，$a_j$ 可以拓展的每个数，$a_i$ 一定可以拓展。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 3e5 + 5;

int a[N], n, maxn = 0, cnt = 0;
bool b[N];
int ans[N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
	{
		if (b[i]) continue;
		register int l = i - 1, r = i + 1;
		while (l >= 1 && a[l] % a[i] == 0) l--;
		while (r <= n && a[r] % a[i] == 0) r++;
		l++;
		r--;
		if (r - l > maxn)
		{
			maxn = r - l;
			cnt = 1;
			ans[cnt] = l;
		}
		else if (r - l == maxn)
		{
			ans[++cnt] = l;
		}
		for (l; l <= r; ++l)
		{
			if (a[l] >= a[i]) b[l] = true;
		}
	}
	sort(ans + 1, ans + cnt + 1);
	printf("%d %d\n", cnt, maxn);
	for (int i(1); i <= cnt; i++) printf("%d\n", ans[i]);
	return 0;
}
```


---

## 作者：RedreamMer (赞：1)

# CF359D题解

算法：ST表+二分答案

[（请自学ST表）](https://zhouziheng666.blog.luogu.org/qian-tan-st-biao)

[(ST表练手题)](https://www.luogu.org/problem/P3865)

这道题如果用朴素暴力来做时间复杂度为 $O(n^2)$ 显然过不去，能不能更快呢？

首先我们可以用ST表来维护区间最小值和最大公约数（时间复杂度 $O(n$ $log_2$ $n)$ ），因为如果一个区间的最小值和最大公约数相等，那这个区间就是题目所要求的，其次用二分来枚举区间长度，否则以 $O(n^2)$ 的时间查询还是会超时，综上所述，就可以轻松搞定此题，时间复杂度 $O(n$ $log_2$ $n)$ ，但写的时候要注意细节不能出错

ST表是一种空间小，容量大，存储快，查询快的数据结构

------------


### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,som;
int g[300001][21],m[300001][21];//数组不能开太小，第二维要开log2(n)以上 
int p[300001],pp[300001];
inline int r() {//快读 
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*y;
}
inline int f(int n,int t,int o) {//ST表O(1)查询 
	int q=log2(t-n+1);
	if(o)
		return min(m[n][q],m[t-(1<<q)+1][q]);//细节 
	else
		return __gcd(g[n][q],g[t-(1<<q)+1][q]);//细节 
}
inline bool check(int n) {
	memset(p,0,sizeof(p));
	for(register int i=1; i+n<=a; i++) {
		if(f(i,i+n,0)==f(i,i+n,1))
			p[++p[0]]=i;
	}
	if(p[0])
		return true;
	else
		return false;
}
int main() {
	memset(m,0x7f,sizeof(m));
	a=r();
	for(register int i=1; i<=a; i++)
		g[i][0]=m[i][0]=r();
	for(register int i=1; (1<<i)<=a; i++)
		for(register int j=1; j+(1<<i)-1<=a; j++) {//细节 
			g[j][i]=__gcd(g[j][i-1],g[j+(1<<(i-1))][i-1]);
			m[j][i]=min(m[j][i-1],m[j+(1<<(i-1))][i-1]);
		}
	int l=0,r=a-1;
	while(l<=r) {//二分枚举区间答案 
		int mid=(l+r)/2;
		if(check(mid)) {//判断答案是否合法 
			l=mid+1;
			memcpy(pp,p,sizeof(p));//保存答案 
			som=mid;
		} else
			r=mid-1;
	}
	printf("%d %d\n",pp[0],som);
	for(int i=1;i<=pp[0];i++)
	printf("%d ",pp[i]);
	return 0;
}
```

### [$\color{blue}\text{My Blog}$](https://www.luogu.org/blog/184549/)

---

## 作者：CreeperLordVader (赞：1)

### 没有用ST表的？我来一个

~~我强大的原力告诉我~~思考可得，区间是满足单调性的，因此可以二分答案

而很显然，一个区间内所有数的约数一定是最小的那个，只要判区间$gcd$是否等于区间最小值就好了

众所周知，ST表不能用于查询区间和等信息，在这个题之前我也只知道它能写RMQ(实际上除了模板我在其它的地方就没写过ST表)

想维护区间最小值和区间$ gcd $很自然地想到线段树，但是线段树的时间复杂度难以保证

### 假如用线段树,我们又要二分答案，又还要$gcd$,复杂度为

$ O(logN)*O(N)*O(logN)*O(logN)=O(Nlog^{3}N)$

显然不行

因此用ST表可把询问时间减少一个$ log $

### ST表能维护$gcd$吗？

ST表不能维护区间和是因为ST表的两段查询有重复，导致答案错误，但重复的这一段对$gcd$而言没有影响

最后,注意区间长度

```cpp
#include<bits/stdc++.h>
using namespace std;
const int LOGN=20;
int n,ans;
int b[300050],cnt;
int a[300050];
int f[300050][LOGN],g[300050][LOGN];
int lg[300050];
void read(int& x)
{
	char c=getchar();
	x=0;
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
}
int gcd(int x,int y)
{
	return y?gcd(y,x%y):x;
}
int MIN(int l,int r)
{
	return min(f[l][lg[r-l+1]],f[r-(1<<lg[r-l+1])+1][lg[r-l+1]]);
}
int GCD(int l,int r)
{
	return gcd(g[l][lg[r-l+1]],g[r-(1<<lg[r-l+1])+1][lg[r-l+1]]);
}
bool check(int mid)
{
	for(int i=1;i+mid-1<=n;i++)
	{
		int j=i+mid-1;
		int x=MIN(i,j),y=GCD(i,j);
		if(x==y)return 1;
	}
	return 0;
}
int main()
{
	srand(time(0));
	read(n);
	lg[1]=0;
	for(int i=2;i<=n;i++)
	{
		lg[i]=lg[i>>1]+1;
	}
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		f[i][0]=g[i][0]=a[i];
	}
	for(int j=1;(1<<j)<=n;j++)
	{
		for(int i=1;i+(1<<j)-1<=n;i++)
		{
			f[i][j]=min(f[i][j-1],f[i+(1<<j-1)][j-1]);
			g[i][j]=gcd(g[i][j-1],g[i+(1<<j-1)][j-1]);
		}
	}
	int l=1,r=n;
	while(l<r)
	{
		int mid=((l+r)>>1)+(rand()&1);
		if(check(mid))l=mid;
		else r=mid-1;
	}
	ans=l-1;
	for(int i=1;i+ans<=n;i++)
	{
		int j=i+ans;
		int x=MIN(i,j),y=GCD(i,j);
		if(x==y)b[++cnt]=i;
	}
	printf("%d %d\n",cnt,ans);
	for(int i=1;i<=cnt;i++)printf("%d ",b[i]);
}
```


---

## 作者：yeshubo_qwq (赞：0)

## 前置芝士

在阅读此题解前请确保您已经熟练掌握了 [ST 表](https://www.luogu.com.cn/problem/P3865)。

## Description

给定一个长度为 $n$ 的序列 $a_1,a_2 \dots a_n$，求符合**区间中有一个数 $x$ 可以整除区间中任意数**的区间最长的长度和数量，并求出符合要求的最长区间的左端点。

## Solution

区间中有一个数 $x$ 可以整除区间中任意数等价于区间中有一个数 $x$ 为区间中任意数的约数，也就是说，区间中有一个数 $x$ 为区间中所有数的公约数。

区间中所有数的公约数一定不大于区间最小值，所以这个数 $x$ 一定是区间最小值，然后维护区间 $\gcd$，判断是否与区间最小值相等就可以了。

此题中维护区间最小值，区间 $\gcd$ 是不带修的，使用 ST 表可以做到 $O(n \log n)$ 预处理，$O(1)$ 单次查询。

如果存在长度为 $mid$ 的符合条件的区间，则一定存在长度 $<mid$ 的符合条件的区间，由此可见，此题具有单调性，二分答案即可。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[300005],st[300005][24],st1[300005][24];
namespace _ST{//ST 表模板 
	void init(int *a){
		for (int i=1;i<=n;i++)
			st[i][0]=a[i],st1[i][0]=a[i];
		for (int j=1;(1<<j)<=n;j++)
			for (int i=1;i+(1<<j)-1<=n;i++)
				st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]),//st 是区间 min 
				st1[i][j]=__gcd(st1[i][j-1],st1[i+(1<<(j-1))][j-1]);//st1 是区间 gcd 
	}
	int query_min(int l,int r){//查询区间 min
		int k=log2(r-l+1);
		return min(st[l][k],st[r-(1<<k)+1][k]);
	}
	int query_gcd(int l,int r){//查询区间 gcd 
		int k=log2(r-l+1);
		return __gcd(st1[l][k],st1[r-(1<<k)+1][k]);
	}
}
using namespace _ST;
int check(int x){
	int ans=0;
	for (int i=1,j=i+x;j<=n;i++,j++)
		if (query_min(i,j)==query_gcd(i,j))
			ans++;//统计符合要求的区间数 
	return ans;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	init(a);
	int l=0,r=n-1,ans=0,cnt=0;
	while (l<=r){
		int mid=(l+r)>>1,x=check(mid);
		if (x>0) l=(ans=mid)+1,cnt=x; //如果区间数不为 0 说明有符合要求的区间
			else r=mid-1;
	}
	cout<<cnt<<' '<<ans<<'\n';
	for (int i=1,j=i+ans;j<=n;i++,j++)//再做一遍，求出每个区间的左端点 
		if (query_min(i,j)==query_gcd(i,j))
			cout<<i<<' ';
	return 0;//完结撒花 OvO~ 
}
```


---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF359D)
## 思路
简单 $\verb!DS!$ 题，给出一种不需要动脑，跑的很慢的双 $\log$ 做法。

先枚举一个 $x$，考虑往左右扩展，暴力扩展当然会超时，所以考虑倍增优化。设 $f_{i,j}$ 表示从点 $i$ 开始向右扩展 $2^j$ 长度时的 $\gcd$，$g_{i,j}$ 表示从点 $i$ 开始向左扩展 $2^j$ 长度时的 $\gcd$，那么我们就直接倍增扩展，若 $a_i|f_{i,j}/g_{i,j}$ 就直接跳。

时间复杂度 $O(n \log^2 n)$，主要瓶颈在于预处理时的 $\gcd$ 操作。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=3e5+10;
int a[N],f[N][20],g[N][20],ans;
vector<int>ansq;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for (int i=1;i<=n;++i) cin>>a[i],f[i][0]=a[i];
    for (int j=1;j<=19;++j)
        for (int i=1;i+(1<<(j-1))<=n;++i)
            f[i][j]=__gcd(f[i][j-1],f[i+(1<<(j-1))][j-1]);
    for (int i=1;i<=n;++i) g[i][0]=a[i];
    for (int j=1;j<=19;++j)
        for (int i=n;(i-(1<<(j-1)))>=1;--i)
            g[i][j]=__gcd(g[i][j-1],g[i-(1<<(j-1))][j-1]);
    for (int i=1;i<=n;++i){
        int l=i;
        for (int j=19;j>=0;--j){
            if (l-(1<<j)<0) continue;
            if (g[l][j]%a[i]==0) l-=(1<<j);
        }
        ++l;
        int r=i;
        for (int j=19;j>=0;--j){
            if (r+(1<<j)>n+1) continue;
            if (f[r][j]%a[i]==0) r+=(1<<j);
        }
        --r;
        if (r-l>ans) ans=r-l,ansq.clear();
        if (r-l==ans) ansq.push_back(l);
    }
    sort(ansq.begin(),ansq.end());
    ansq.erase(unique(ansq.begin(),ansq.end()),ansq.end());
    cout<<ansq.size()<<' '<<ans<<'\n';
    for (auto i:ansq) cout<<i<<' ';cout<<'\n';
    return 0;
}
```


---

## 作者：Arghariza (赞：0)

最劣解，介绍一种 $2$ 个 $\log$ 的做法。

不难想到对于每一个 $i\in [1,n]\cap \mathbb Z$ 计算出以其为公因数的最大区间的长度，这个区间记为 $[l,r]$，考虑分别求 $l$ 和求 $r$。

左右端点都具有单调性，所以我们可以分别二分 $l$ 和 $r$，然后 `check` 函数的话我们转化为**查询一个区间的 $\gcd$ 是否为 $a_i$**，可以用 `st` 表在 $O(\log n)$ 询问的复杂度解决。

复杂度 $O(n\log n\log w)$，顺便一提，`st` 表预处理 $\gcd$ 复杂度是 $O(n(\log n+\log w))$ 的，详见 [`oi wiki`](https://oi-wiki.org/ds/sparse-table/)。

```cpp
#include <bits/stdc++.h>
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(int x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 3e5 + 300;
int n, tot, a[maxn], g[maxn][25];
vector<pair<int, int> > vec[maxn];

void init() {
	for (int i = 1; i <= n; i++) g[i][0] = a[i];
	for (int j = 1; (1 << j) <= n; j++) {
		for (int i = 1; i + (1 << j) - 1 <= n; i++) {
			g[i][j] = __gcd(g[i][j - 1], g[i + (1 << (j - 1))][j - 1]);
		}
	}
}

int query(int l, int r) {
	int len = log2(r - l + 1);
	return __gcd(g[l][len], g[r - (1 << len) + 1][len]);
}

int main() {
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	init();
	for (int i = 1; i <= n; i++) {
		int l, r, L, R;
		l = 1, r = L = R = i;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (query(mid, i) % a[i] != 0) l = mid + 1;
			else r = mid - 1, L = mid;
		}
		l = i, r = n;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (query(i, mid) % a[i] != 0) r = mid - 1;
			else l = mid + 1, R = mid;
		}
		if (!vec[R - L].size()) {
			vec[R - L].push_back(make_pair(0, 0));
		}
		vec[R - L].push_back(make_pair(L, R));
	}
	for (int i = n - 1, fl = 0; ~i; i--) {
		if (vec[i].size() && !fl) {
			int cnt = 0;
			sort(vec[i].begin(), vec[i].end());
			for (int k = 1; k <= vec[i].size() - 1; k++) {
				if (vec[i][k].first == vec[i][k - 1].first) continue;
				cnt++;
			}
			write(cnt), putchar(' '), write(i), puts("");
			for (int k = 1; k <= vec[i].size() - 1; k++) {
				if (vec[i][k].first == vec[i][k - 1].first) continue;
				write(vec[i][k].first);
				putchar(' ');
			}
			fl = 1;
		}
	}
//	while (clock() / CLOCKS_PER_SEC < 1) ;
	return 0;
}
```

---

## 作者：WRuperD (赞：0)

较为简单的一道数据结构题。

### 思路
首先考虑暴力。对于每一个序列中的数 $a_i$  暴力向后和向前拓展，虽然在随机数据跑得飞快，但是最坏可以被卡到 $O(n^2)$。

稍微观察一下题面，发现是求区间 $\operatorname{gcd}$ 。回想一下 $\operatorname{gcd}$ 的性质，我们发现 $\operatorname{gcd}$ 满足**结合律**。满足结合律就可以考虑使用一些数据结构进行优化。这里我们可以使用线段树之类的数据结构。考虑对于每个可能长度都进行一次枚举，再 $\log(n)$ 求出区间 $\operatorname{gcd}$ ，区间最小值，如果**区间 $\operatorname{gcd}$ 等于区间最小值**，那这个区间就是可行的。复杂度 $O(n \log n)$。

可惜以上复杂度并不能够顺利通过此题，但是我们稍加思考，即可发现可行的区间长度满足**单调性**，考虑使用二分答案进行优化，即可将复杂度降至   $O(n \log^2 n)$。


### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long 
const int maxn = 500000+5;
int gcd(int a, int b){
	if(b == 0){
		return a;
	}
	return gcd(b,a%b);
}

int n;
int a[maxn], f[maxn][25], f2[maxn][25];

void init(){
	for(int i = 1; i <= n; i++)	f[i][0] = a[i];
	for(int j = 1; j <= 25; j++)
	for(int i = 1; i +(1 <<j) -1 <= n; ++i){
		f[i][j] = min(f[i][j-1], f[i+(1<<(j-1))][j-1]);
	} 
}

void init2(){
	for(int i = 1; i <= n; i++)	f2[i][0] = a[i];
	for(int j = 1; j <= 25; j++)
	for(int i = 1; i +(1 <<j) -1 <= n; ++i){
		f2[i][j] = gcd(f2[i][j-1], f2[i+(1<<(j-1))][j-1]);
	} 
}
int cnt;
int ans[500005];

int q(int l, int r){
	int k = log2(r-l+1);
	return min(f[l][k], f[r-(1<<k)+1][k]);
}

int q2(int l, int r){
	int k = log2(r-l+1);
	return gcd(f2[l][k], f2[r-(1<<k)+1][k]);
}

bool check(int x){
	for(int i = 1; i <= n-x+1; i++){
		if(q2(i, i+x-1) ==  q(i, i+x-1)){
			ans[++cnt] = i;
		}
	}
	if(cnt)	return 1;
	return 0;
}

signed main()
{	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i = 1; i <= n; i++)	cin>>a[i];
	memset(f, 0x3f, sizeof(f));
	init();
	init2();
	int L = 1, R = n;
	while(L <= R){
		int mid = (L+R)/2;
		if(check(mid)){
			L = mid + 1;
			cnt  = 0;
		}else{
			R = mid-1;
			cnt = 0;
		}
	} 
	check(R);
	cout<<cnt<<' '<<R-1<<endl;
	for(int i = 1; i <= cnt; i++){
		cout<<ans[i]<<' ';
	}
	return 0;
}
```

### 相关练习
CF475D

---

## 作者：zhengrunzhe (赞：0)

二分区间长度

check函数里面直接对$O(n)$个这样长度区间一个个查

查区间gcd是不是存在于区间中 准确来说这个gcd是区间最小值 但其实我们并不需要多求一个区间最小值

类似莫队的思想 直接开个$cnt[]$数组表示每个数值的出现次数 看区间gcd有没有出现即可 右端插入$cnt[a[r]]++$ 左端弹出$cnt[a[l]]--$

区间gcd用st表就好了 别想不开写线段树 由于求gcd单次要$\log a$  所以总复杂度是$O(n\log n \log a)$

是目前的最优解
```cpp
#include<cstdio>
#include<vector>
using std::vector;
template<class type>inline const void read(type &in)
{
	in=0;char ch(getchar());
	while (ch<48||ch>57)ch=getchar();
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
}
inline const int gcd(const int &a,const int &b){return !b?a:gcd(b,a%b);}
typedef vector<int>Vector;
const int N(3e5+5),M(1e6+5);
Vector ans;
int n,a[N],st[N][19],pow2[19],log2[N],cnt[M];
inline const void build()
{
	for (int i(pow2[0]=1);i<19;i++)pow2[i]=pow2[i-1]<<1;
	for (int i(2);i<=n;i++)log2[i]=log2[i>>1]+1;
	for (int i(1);i<=n;i++)st[i][0]=a[i];
	for (int j(1);j<=log2[n];j++)
		for (int i(1);i+pow2[j]-1<=n;i++)
			st[i][j]=gcd(st[i][j-1],st[i+pow2[j-1]][j-1]);
}
inline const int query(const int &l,const int &r)
{
	const int k(log2[r-l+1]);
	return gcd(st[l][k],st[r-pow2[k]+1][k]);
}
inline const Vector check(const int &len)
{
	static Vector v;v.clear();
	for (int i(1);i<=len;i++)cnt[a[i]]++;
	if (cnt[query(1,len)])v.push_back(1);
	for (int i(len+1);i<=n;i++)
	{
		cnt[a[i-len]]--;cnt[a[i]]++;
		//printf("%d [%d,%d] %d\n",len,i-len+1,i,query(i-len+1,i));
		if (cnt[query(i-len+1,i)])v.push_back(i-len+1);
	}
	for (int i(1);i<=n;i++)cnt[a[i]]=0;
	return v;
}
int main()
{
	read(n);
	for (int i(1);i<=n;i++)read(a[i]);
	build();
	int l(1),r(n);
	while (l<=r)
	{
		const int mid(l+r>>1);
		Vector v=check(mid);
		if (v.empty())r=mid-1;
		else l=mid+1,ans=v;
	}
	printf("%d %d\n",ans.size(),l-2);
	for (Vector::iterator i(ans.begin());i!=ans.end();i++)printf("%d ",*i);
	putchar('\n');
	return 0;
}
```

---

## 作者：ChthollyTree (赞：0)


因为一个区间满足条件

设为[l,r] 

“满足区间中有一个数 x  可以整除区间中任意数”

则[l,r] 的所有包含 x 的子区间 [l',r']

必然也满足条件

所以区间长度就具有单调性，就可以二分

至于判定一个区间是否符合条件，可以用线段树

每个节点维护区间gcd

同时这个区间的x一定是区间的最小值

可以rmq求

最后判定区间gcd是不是x的倍数就可以了

（当然直接判定线段树上每个节点的区间gcd是不是x的倍数就行）

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 300005
#define INF 0x3f3f3f3f
#define lc(i) (i<<1)
#define rc(i) ((i<<1)|1)

int n,m;
int a[MAXN];
int f[MAXN][22];

struct aa
{
	int l,r,s,a;
}c[MAXN<<2];


int gcd(int x,int y) {
	if(x%y == 0) return y;
	return gcd(y,x%y);	
}

void jianshu(int i,int l,int r) {
	int mid = (l+r)>>1;
	c[i].l = l;
	c[i].r = r;
	if(l == r) {
		c[i].s = a[l];
		c[i].a = a[l];
		return;
	}
	jianshu(lc(i),l,mid);
	jianshu(rc(i),mid+1,r);
	c[i].a = gcd(c[lc(i)].a,c[rc(i)].a);
}

void rd()
{
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++)
		scanf("%d",&a[i]);
	jianshu(1,1,n);
	for(int i = 1; i <= n; i ++)
		f[i][0] = a[i];
	for(int j = 1; j <= 20; j ++)
		for(int i = 1; i <= n; i ++)
		if(i + (1<<j) - 1 <= n) {
			f[i][j] = min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
}

int qiu(int i,int l,int r,int x)//求区间gcd
{
	if(l <= c[i].l && c[i].r <= r) {
		if(c[i].a % x == 0) return 1;
		else return 0;
	}
	if(l > c[i].r || r < c[i].l) return 1;
	if(!qiu(lc(i),l,r,x)) return 0;
	return qiu(rc(i),l,r,x);
}

int rmq(int l,int r)
{
	int o = log2(r-l+1);
	return min(f[l][o],f[r-(1<<o)+1][o]);
}

bool pd(int l,int r)
{
	int u = rmq(l,r);
	return qiu(1,l,r,u);
}

bool judge(int len)
{
	for(int i = 1; i+len-1 <= n; i ++) {
		if(pd(i,i+len-1)) return 1;
	}
	return 0;
}

int ans[MAXN];
void wt(int len)
{
	int cnt = 0;
	for(int i = 1; i+len-1 <= n; i ++) {
		if(pd(i,i+len-1))
		{
			cnt ++;
			ans[cnt] = i;
		}
	}
	cout<<cnt<<" "<<len-1<<"\n";
	for(int i = 1; i <= cnt; i ++)
		cout<<ans[i]<<" ";
}

int main()
{
	rd();
	int l = 1,r = n;
	//cout<<judge(5)<<"\n";
	//return 0;
	while(l + 3 < r)
	{
	//	cout<<"Orz\n";
		int mid = (l+r)>>1;
		if(judge(mid)) l = mid;
		else  r = mid;
	}
	//cout<<"Sooke tql";
	for(int i = r; i >= l; i --)
	{
		if(judge(i))
		{
			wt(i);
			return 0;
		}
	}
	return 0;
}
```

---


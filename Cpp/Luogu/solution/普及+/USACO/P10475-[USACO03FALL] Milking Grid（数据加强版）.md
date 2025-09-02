# [USACO03FALL] Milking Grid（数据加强版）

## 题目描述

每天早上挤奶时，农夫约翰的奶牛们排成一个 $R (1 \leq R \leq 10,000)$ 行乘 $C (1 \leq C \leq 75)$ 列的矩形网格。众所周知，农夫约翰是一个相当擅长牛行为的专家，目前正在撰写一本关于奶牛饲养行为的书。他注意到，如果每头奶牛都标有一个表示其品种的大写字母，那么奶牛在挤奶时形成的二维图案有时似乎是由更小的重复矩形图案组成的。

帮助农夫约翰找到可以重复铺设以组成整个挤奶网格的最小面积的矩形单元。请注意，小矩形单元的尺寸不一定需要完全整除整个挤奶网格的尺寸，如下面的示例输入所示。

## 说明/提示

整个挤奶网格可以由图案 AB 的重复构建。

翻译来自于：ChatGPT。

## 样例 #1

### 输入

```
2 5 
ABABA 
ABABA
```

### 输出

```
2```

# 题解

## 作者：SkyLines (赞：10)

## Solution

因为这个矩形要重复，所以可以求出行最小和列最小的值，相乘即为答案。

求每行和每列的 Hash 值，求行和列的最小循环节长度即为最小值，求法见 [Link.](https://www.luogu.com.cn/problem/P4391)，可用 Hash 或 KMP 做。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
const int N = 10005, p = 131, M = 75;
int r, c, a[N], b[M], nxt[N], ans, ans2, j;
string s[N];
signed main(){
	cin >> r >> c;
	for(int i = 1; i <= r; i++){
		cin >> s[i];
		s[i] = " " + s[i];
		for(int j = 1; j <= c; j++){
			a[i] = a[i] * p + s[i][j];
		}
	}
	for(int i = 1; i <= c; i++){
		for(int j = 1; j <= r; j++){
			b[i] = b[i] * p + s[j][i];
		}
	}
	nxt[1] = 0;
	j = 0;
	for(int i = 2; i <= r; i++){
		while(j && a[i] != a[j + 1]) j = nxt[j];
		if(a[i] == a[j + 1]) j++;
		nxt[i] = j;
	}
	ans = r - nxt[r];
	nxt[1] = 0;
	j = 0;
	for(int i = 2; i <= c; i++){
		while(j && b[i] != b[j + 1]) j = nxt[j];
		if(b[i] == b[j + 1]) j++;
		nxt[i] = j;
	}
	ans2 = c - nxt[c];
	cout << ans * ans2;
	return 0;
}
```

---

## 作者：ask_silently (赞：7)

## [题目传送门](https://www.luogu.com.cn/problem/P10475)

## 思路分析

这道题的一维弱化版是 [P4391](https://www.luogu.com.cn/problem/P4391)，没有做过的可以先做弱化版。我们发现这道题只是弱化版的二维模式，所以我们可以先将每一行作为主体，对列做一个 KMP 或者 Hash，求出最短循环节；然后将每一列作为主体，对行做一个 KMP 或者 Hash，最后将两个值相乘就可以得到答案。

## AcCode

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long

const int N=1e4+10,M=100;
const int P=131;

int n,m;
int a[N],b[M];
int nxt1[N],nxt2[M];

char c[N][M];

inline int read(){
	int t=0,f=1;
	register char c=getchar();
	while(c<'0'||c>'9') f=(c=='-')?(-1):(f),c=getchar();
	while(c>='0'&&c<='9') t=(t<<3)+(t<<1)+(c^48),c=getchar();
	return t*f;
}

signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) cin>>c[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) a[i]=a[i]*P+(int)(c[i][j]-'a'+1);
	for(int j=1;j<=m;j++)
		for(int i=1;i<=n;i++) b[j]=b[j]*P+(int)(c[i][j]-'a'+1);
	for(int i=2,j=0;i<=n;i++){
		while(j&&a[j+1]!=a[i]) j=nxt1[j];
		if(a[j+1]==a[i]) j++;
		nxt1[i]=j;
	}
	for(int i=2,j=0;i<=m;i++){
		while(j&&b[j+1]!=b[i]) j=nxt2[j];
		if(b[j+1]==b[i]) j++;
		nxt2[i]=j;
	}
	cout<<(n-nxt1[n])*(m-nxt2[m]);
	return 0;
}

```

---

## 作者：Drifty (赞：4)

### Solution

KMP 经典题目。

题意即为求最小重复子矩阵。

在处理这个问题之前，可以先看看最小重复子串的例题：[P4391 [BOI2009] Radio Transmission 无线传输 ](/problem/P4391)。这有助于您理解如何用 KMP 去求最小重复子串。

- 考虑分别找出最小重复子矩阵的宽和高。
- 先找出每行的重复子串的并集的长度作为最小重复子矩阵的宽。
- 再找出每列的重复子串的并集的长度作为最小重复子矩阵的高。
- 相乘即为答案。

### AC-Code

```cpp
#include <iostream>
using namespace std;
constexpr int N = 10007, C = 77;
string s[N], a;
int p[N], i, j, x, y, r, c, f[C] = {0};
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	cin >> r >> c;
	for (i = 0; i < r; i ++) {
		cin >> s[i], a = s[i];
		for (j = c - 1; j > 0; j --) {
			a[j] = 0;
			for (x = 0, y = 0; s[i][y]; x++, y++) {
				if (!a[x]) x = 0;
				if (a[x] != s[i][y]) break;
			}
			if (!s[i][y]) f[j] ++;
		}
	}
	for (i = 0; i < c; i ++) if (f[i] == r) break; x = i;
	for (i = 0; i < r; i ++) s[i][x] = 0;
	p[0] = -1, j = -1;
	for (i = 1; i < r; i++) {
		while (j >= 0 && s[i] != s[j + 1]) j = p[j];
		if (s[i] == s[j + 1]) j ++; p[i] = j;
	}
	cout << (r - 1 - p[r - 1]) * x;
	return 0;
}
```

---

## 作者：Montpelier (赞：2)

### 前置内容：一维 kmp

**KMP 算法**，是**一种字符串模式匹配算法**，用大白话来说就是在某个已知字符串中寻找某个询问子串是否存在、存在位置如何的高效算法。  
通过记录已经确定匹配的部分，可以把时间复杂度从暴力算法的 $O(NM)$ 降低至 $O(N+M)$。

其重要组成部分：`next[]` 数组，即用来记录**最大公共前后缀**的数组，它可以拓展用来求**最短重复子串**，详见：[P4391](https://www.luogu.com.cn/problem/P4391)，此处不再赘述。

---

### 本题：二维 kmp
从[题目描述](https://www.luogu.com.cn/problem/P10475)我们可以得知，题目要我们求最小重复矩形。显然，既然**存在**这个矩形满足“重复”，那么水平和竖直两个方向上，也一定存在**最小构成单位**，也就是我们前面讲的**最短重复子串**。

那么思路就清晰了，我们分别从水平和竖直方向上求出其**最小构成单位的长度**，也就是分别两个一维 kmp，轻轻松松。

所以，最后的答案是什么呢？

举个例子。如果水平方向上，最小构成单位的长度是 $5$，而竖直方向上，最小构成单位的高度是 $3$，那么我们要求的这个矩形的**面积**就是 $3\times5=15$。
为什么呢？看表。~~（懒得弄图了）~~



|...|...|...|...|...|...|...|...|...|...|...|...|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|...|...|1|1|1|1|1|3|3|3|3|3|
|...|...|1|1|1|1|1|3|3|3|3|3|
|...|...|1|1|1|1|1|3|3|3|3|3|
|...|...|2|2|2|2|2|4|4|4|4|4|
|...|...|2|2|2|2|2|4|4|4|4|4|
|...|...|2|2|2|2|2|4|4|4|4|4|
|...|...|...|...|...|...|...|...|...|...|...|...|

表中 “1” “2” “3” “4”分别代表四个重复的矩形，编号仅用于区分。

省略号代表其余部分。可以很直观的看到，假设水平方向上的循环节是 $x$，竖直方向上的循环节是 $y$，那么我们要求的矩形面积就是 $S=xy$。


那这样本题就结束了。还有一些注意点，比如如何处理水平和竖直方向上的最小重复单元。我们注意到，如果**所有**单个行上都满足元素有规律，那么**放眼全表**，列也一定是整列整列地有规律的出现。所以我们可以把每一列哈希，然后这样就变成了一条一维数组，其元素个数等于列数，就可以用 kmp 了。行也是如此。

其余细节就见代码吧 : )



```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10009;
const int base=1145141919; //810
int n,m,mp[N][N];
int nh,hx[N]; //哈希数组&哈希数组元素个数
int nxt[N];
int kmp() { //针对hx[]数组求其最小循环周期数，见P4391
	memset(nxt,0,sizeof nxt);
	int j=0;
	for (int i=1;i<nh;++i) { //注意循环要从1开始，因为"a"是没有前缀or后缀的，自然也没有公共前缀后缀
		while (j>0&&hx[j]!=hx[i]) j=nxt[j-1];
		if (hx[i]==hx[j]) j++;
		nxt[i]=j;
	}
	return nh-nxt[nh-1];
}
int main() {
	cin>>n>>m;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j) {
			char c;
			cin>>c;
			mp[i][j]=c-'A'+1; //把char转换成int，常见操作
		}
	
	//第一遍哈希，把每一行压缩成一个数
	nh=n; //哈希数组一个数代表每一行的情况，那么一共就有n个元素了(n是行数)
	for (int i=1;i<=nh;++i) {
		int hxi=0; //就算溢出变负也无所谓，所以不用取模
		for (int j=1;j<=m;++j)
			hxi=hxi*base+mp[i][j];
		hx[i-1]=hxi; //我想让hx的x范围是[0,nh)，但是不这样也是可以的
	}
	//第一次kmp
	int rep1=kmp();
	
	//第二遍哈希，把每一列压缩成一个数
	nh=m; //哈希数组一个数代表每一列的情况，那么一共就有m个元素了(m是列数)
	for (int j=1;j<=nh;++j) {
		int hxj=0; //就算溢出变负也无所谓，所以不用取模
		for (int i=1;i<=n;++i)
			hxj=hxj*base+mp[i][j];
		hx[j-1]=hxj;
	}
	//第二次kmp
	int rep2=kmp();
	
	//因为求的是面积，所以两个答案要乘起来
	cout<<rep1*rep2<<endl;
	return 0;
}

//第一篇题解呢
```
[评测记录](https://www.luogu.com.cn/record/168970879)

---

## 作者：Superiority (赞：2)

# 思路

如果直接做这题的话，难度可能还是有点高，不过可以先看一下一维版的这题 [P4391](https://www.luogu.com.cn/problem/P4391)。

我们考虑如何把它变成一维的 P4391，很容易就想到了 Hash 来把此题转化为一维版。

我们先用 Hash 将每行每列的 Hash 值预处理出来。这时会发现跟 P4391 没啥区别了。不过题目是求最小的面积，转换一下其实就是所有行和列 Hash 值的**最小循环节**相乘起来，而求最小循环节我就可以用 KMP 来进行求解最小的循环节。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;//by cqbzbbd
#define zjj long long
const int MAXN=1e7+5;
const int N=131;
const int mod=1e9+7;
int n,m;
int idx;
zjj sa,sb;
zjj a[MAXN],b[MAXN];
string s[MAXN];
zjj nxt[MAXN];
void KMP(zjj x[]){
	nxt[1]=0;
	idx=0;
	for(int i=2;i<=n;i++){
		while(idx&&x[i]!=x[idx+1]) idx=nxt[idx];
		if(x[idx+1]==x[i]) idx++;
		nxt[i]=idx;
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		s[i]=" "+s[i];
		for(int j=1;j<=m;j++){
			a[i]=(a[i]*N+s[i][j])%mod;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			b[j]=(b[j]*N+s[i][j])%mod;
		}
	}
	KMP(a);
	sa=n-nxt[n];
	memset(nxt,0,sizeof(nxt));
	n=m;
	KMP(b);
	sb=m-nxt[m];
	cout<<sa*sb<<endl;
	return 0;
}
//CTJ可耻
```

---

## 作者：Chenyichen0420 (赞：1)

## 思路分析

很显然，行和列是完全独立的两个问题。因为 $R$ 远大于 $C$，故我们直接讲解 $R$ 的做法。

考虑我们能不能快速的比较两个矩阵是否相等。显然哈希是一个不错的选择。

但是我们似乎并没有一个名叫二维哈希的神奇东西。但是，我问你：矩阵是什么？不就是一行一行叠放在一起吗？

那我们可不可以选择对每一行算出一个哈希值，然后将矩阵看作是行的哈希值构成的序列，对他再做一遍类似于字符串哈希的哈希呢？

包的，实践出真知。代码如下：（对 $C$ 使用 $O(n^2)$ 的暴力，对 $R$ 使用 $O(n\ln n)$ 调和级数的正解，可以对照着看二者的异同。）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m, mix, miy; char c[100005][80];
int vx[85], vy[100005], cp[100005], ap[100005];
constexpr int p = 37, p2 = 131, md = 1e9 + 7;
mt19937 mt(time(0));
inline int random(int l, int r) {
	int tmp;
	do tmp = mt() % (r - l + 1) + l;
	while (tmp<l || tmp>r);
	return tmp;
}
inline int qpow(int a, int b = md - 2, int p = md) {
	int ret = 1;
	for (; b; b >>= 1, a = a * a % p)
		(b & 1) && (ret = ret * a % p);
	return ret;
}
inline bool cmpx(int ll, int lr, int rl, int rr) {
	for (int i = ll, j = rl; i <= lr && j <= rr; ++i, ++j)
		if (vx[i] != vx[j]) return 0;
	return 1;
}
inline bool cmpy(int ll, int lr, int rl, int rr) {
	if (rl > rr) return 1;
	if (lr - ll == rr - rl) {
		int vll = (vy[lr] - vy[ll - 1] * cp[lr - ll + 1] % md + md) % md;
		int vlr = (vy[rr] - vy[rl - 1] * cp[rr - rl + 1] % md + md) % md;
		return vll == vlr;
	}
	lr = ll + rr - rl;
	int vll = (vy[lr] - vy[ll - 1] * cp[lr - ll + 1] % md + md) % md;
	int vlr = (vy[rr] - vy[rl - 1] * cp[rr - rl + 1] % md + md) % md;
	return vll == vlr;
}
signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> m; cp[0] = 1;
	for (int i = 1; i <= 1e5; ++i) cp[i] = cp[i - 1] * p % md;
	for (int i = 1; i <= 1e5; ++i) ap[i] = random(3, p - 1);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> c[i][j], c[i][j] -= 'A';
	for (int i = 0; i <= n; ++i) vy[i] = 1;
	for (int j = 0; j <= m; ++j) vx[j] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			vx[j] = (vx[j] + ((c[i][j] + ap[i]) * cp[i])) % md,
			vy[i] = (vy[i] + ((c[i][j] + ap[j]) * cp[j])) % md;
	for (int i = 1; i <= n; ++i) vy[i] = (vy[i - 1] * p + vy[i]) % md;
	for (int i = 1; i <= m; ++i) {
		int ll = 1, lr = i, rl = i + 1, rr = 2 * i;
		bool cn = 1;
		while (cn) {
			rr = min(rr, m);
			cn &= cmpx(ll, lr, rl, rr);
			if (rr == m) break;
			rl += i, rr += i;
		}
		if (cn) { mix = i; break; }
	}
	cerr << mix << endl;
	for (int i = 1; i <= n; ++i) {
		int ll = 1, lr = i, rl = i + 1, rr = 2 * i;
		bool cn = 1;
		while (cn) {
			rr = min(rr, n);
			cn &= cmpy(ll, lr, rl, rr);
			if (rr == n) break;
			rl += i, rr += i;
		}
		if (cn) { miy = i; break; }
	}
	cerr << miy << endl;
	cout << mix * miy << endl;
}
```

---

## 作者：dengjunhaodejia09 (赞：1)

首先看到这道题，我们发现，若是有一个重复列数使得每一行都成立，那么每一列的循环节在开头肯定都是可以的，此时我们发现列数很小，即可以暴力枚举列数看最小的每一行都满足的列数，看行与行之间的重复，求出行与行的最小循环节即是最后的矩阵。


```cpp
#include <bits/stdc++.h>
using namespace std;
string s[10005];
unsigned long long Hash[10005][105],sum[10005],base=1299709;
unsigned long long get_hash(int id,int l,int r){
	return Hash[id][r]-Hash[id][l-1]*sum[r-l+1];
}
int n,m;
bool check(int id,int len){
	if(len==m){
		return 1;
	}
	int Len=m-m%len;
	if(Len/len==1){
		if(m%len==0){
			return 1;
		}
		if(get_hash(id,Len+1,m)==get_hash(id,1,m-Len)){
			return 1;
		}
		return 0;
	}else if(get_hash(id,1,Len-len)==get_hash(id,len+1,Len)){
		if(m%len==0){
			return 1;
		}
		if(get_hash(id,Len+1,m)==get_hash(id,1,m-Len)){
			return 1;
		}
		return 0;
	}
	return 0;
}
unsigned long long ans[1919810];
int nxt[1919810];
int main(){
	cin>>n>>m;
	sum[0]=1;
	for(int i=1;i<=m*2;i++){
		sum[i]=sum[i-1]*base;
	}
	for(int i=1;i<=n;i++){
		cin>>s[i];
		s[i]=" "+s[i];
		for(int j=1;j<=m;j++){
			Hash[i][j]=Hash[i][j-1]*base+s[i][j];
		}
	}
	int Min=0;
	for(int i=1;i<=m;i++){
		bool vis=1;
		for(int j=1;j<=n;j++){
			vis&=check(j,i);
		}
		if(vis==1){
			Min=i;
			break;
		}
	}
	for(int i=1;i<=n;i++){
		ans[i]=get_hash(i,1,Min);
	}
	int j=0;
	for(int i=2;i<=n;i++){
		while(j!=0 && ans[j+1]!=ans[i]){
			j=nxt[j];
		}
		if(ans[j+1]==ans[i]){
			j++;
		}
		nxt[i]=j;
	}
	cout<<(n-nxt[n])*Min;
	return 0;
}
```

---

## 作者：zhangxiaohan007 (赞：1)

## 思路
大眼一看，一道二维 ```KMP```。

这道题其实不难，~~其实就是一个升级成二维的[P4391](https://www.luogu.com.cn/problem/P4391)~~。

我们可以将 ```KMP``` 和哈希一起用，把每行的哈希求出，求一下哈希值的循环节，然后求一下每列的哈希，再将哈希值求循环节，再将行和列的循环节乘起来即可。

建议可以先看看[P4391](https://www.luogu.com.cn/problem/P4391)，先练习求一维循环节。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define inf 2e9
using namespace std;
int net[10005],n,n2,ans1,ans2;
string s[10005];
int ss[10005];
ull h[10005],h2[10005];
ull p[10005];
void get_next(int xx)
{
	net[1]=0;
	int j=0;
	for(int i=2;i<=xx;i++)
	{
		while(j&&h2[i]!=h2[j+1])
		{
			j=net[j];
		}	
		if(h2[i]==h2[j+1])j++;
		net[i]=j;
	}
}
int main()
{
	cin>>n>>n2;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		s[i]=' '+s[i];
	}
	p[1]=131;
	for(int i=2;i<=n;i++)
	{
		p[i]=p[i-1]*131;
	}
	for(int j=1;j<=n;j++)
	{
		h[0]=0;
		for(int i=1;i<=n2;i++)
		{
			h[i]=h[i-1]*p[1]+s[j][i];
		}
		h2[j]=h[n2];
	}
	get_next(n);
	ans1=n-net[n];
	for(int j=1;j<=n2;j++)
	{
		h[0]=0;
		for(int i=1;i<=n;i++)
		{
			h[i]=h[i-1]*p[1]+s[i][j];
			net[i]=0;
		}
		h2[j]=h[n];
	}
	get_next(n2);
	ans2=n2-net[n2];
	cout<<ans1*ans2;
	return 0;
}
```

---

## 作者：Infinite_Loop (赞：0)

# P10475
## 题意
给定一个 $R$ 行 $C$ 列的矩阵，求最小的矩阵使得这个矩阵重复多次后可以得到原矩阵。
## 思路
本题是一道二维的 KMP，[P4391](https://www.luogu.com.cn/problem/P4391) 的加强版。

很容易想到 KMP 与哈希一起做。先把每一行、每一列字符串的哈希值求出来，然后就可以用 P4391 的方法。

我们可以用 KMP 把行和列字符串的哈希值的循环节求出来，最后的答案就是行的循环节乘以列的循环节。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int R=1e4+10;
const int N=233,mod=1e9+7;
int r,c,ha[R],hb[R],f[R];
string s[R];
void kmp(int x[],int y){
	f[1]=0;
	for(int i=2,j=0;i<=y;i++){
		while(j>0&&x[j+1]!=x[i])j=f[j];
    	if(x[j+1]==x[i])j++;
    	f[i]=j;
	}
}
signed main(){
	cin>>r>>c;
	for(int i=1;i<=r;i++){
		cin>>s[i];
		s[i]=" "+s[i];
		for(int j=1;j<=c;j++){
			ha[i]=(ha[i]*N+s[i][j])%mod;
		}
	}
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			hb[j]=(hb[j]*N+s[i][j])%mod;
		}
	}
	kmp(ha,r);
	int s1=r-f[r];
	memset(f,0,sizeof(f));
	kmp(hb,c);
	int s2=c-f[c];
	cout<<s1*s2;
	return 0;
}
```

---

## 作者：L_zaa_L (赞：0)

首先题意是让我们求最小的矩阵使得这个矩阵重复多次后某一个地方是原矩阵。

首先行和列是不会相互影响的，所以我们要求最小的行和最小的列。我们将每一行用 hash 表示为一个数字，那么数字相同的就是一样的一行，我们要想使一个选的矩阵重复多次拼成原矩阵，那么我们的选的矩阵一定是原矩阵的列的最小循环节。

然后我们发现 KMP 可以求最小循环节，就是一个字符串的 $border$（最大的后缀是原串前缀相同的）。那么 $n-border$ 就是最小循环节了。

然后将行的最小循环节乘上列的最小循环节就可以得到最小的矩阵了。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=5e5+5,base=999983,Mod=998244353;
//char buf[(1<<21)+5],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
void chmx(int &x,int y){(x<y)&&(x=y);}
void chmn(int &x,int y){(x>y)&&(x=y);}
typedef __int128_t i128;
i128 _base=1;
inline int mol(int x){return x-Mod*(_base*x>>64);}
inline void Add(int &x,int y){x=mol(x+y+Mod);}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
int r,c;
char s[10005][85];
int h=0,w=0;
int hsh1[N],hsh2[N];
int b1[N],b2[N];//border
signed main(){
	_base=(_base<<64)/Mod;
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	r=read(),c=read();
	For(i,1,r){
		scanf("%s",s[i]+1);
		For(j,1,c){
			hsh1[i]=hsh1[i]*base+s[i][j]-'A'+1;
			hsh1[i]%=Mod;
			hsh2[j]=hsh2[j]*base+s[i][j]-'A'+1;
			hsh2[j]%=Mod;
		}
	}
	int j=0;
	For(i,2,r){
		while(j&&hsh1[j+1]!=hsh1[i]) j=b1[j];
		if(hsh1[j+1]==hsh1[i]) ++j;
		b1[i]=j;
		
	}j=0;
	For(i,2,c){
		while(j&&hsh2[j+1]!=hsh2[i]) j=b2[j];
		if(hsh2[j+1]==hsh2[i]) ++j;
		b2[i]=j;
	}
	printf("%lld\n",(r-b1[r])*(c-b2[c]));
#ifdef LOCAL
    Debug("\nMy Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}

```

---

## 作者：ZBH_123 (赞：0)

## 题目分析

在做本题之前，请先尝试下面的题目，以便更好的理解本题：

[P4391](/problem/P4391)

可以发现，本题其实就是 [P4391](/problem/P4391) 的二维化版本。对于这道题，我们可以先利用 Hash 将每一行以及每一列转换为一个整数，这样我们就将本题转换为了 [P4391](/problem/P4391)，即一维化了。当我们用 [P4391](/problem/P4391) 的方法求出所有行和所有列的最短循环节的长度后，只需要将两个答案相乘，就得到本题的答案了。

## 示例代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const int mod=1e9+7,p=131;
int n,m,nxt[10005];
char s[10005][105];
ll a[10005][105],b[105][10005];

void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>s[i][j];
			a[i][j]=(a[i][j-1]*p%mod+s[i][j])%mod;
		}
	}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			b[i][j]=(b[i][j-1]*p%mod+s[j][i])%mod;
	
	nxt[1]=0;
	int j=0;
	for(int i=2;i<=n;i++){
		while(j&&a[i][m]!=a[j+1][m]) j=nxt[j];
		if(a[i][m]==a[j+1][m]) j++;
		nxt[i]=j;
	}
	int ans1=n-nxt[n];
	nxt[1]=0;
	j=0;
	for(int i=2;i<=m;i++){
		while(j&&b[i][n]!=b[j+1][n]) j=nxt[j];
		if(b[i][n]==b[j+1][n]) j++;
		nxt[i]=j;
	}
	int ans2=m-nxt[m];
	
	cout<<1ll*ans1*ans2<<'\n';
}

int main(){
	int T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

---


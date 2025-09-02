# [AGC005C] Tree Restoring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc005/tasks/agc005_c

青木君は数列と木が大好きです。

青木君はある日高橋くんから長さ $ N $ の数列 $ a_1,\ a_2,\ ...,\ a_N $ を貰いました。そしてこの数列を見て、木を作りたくなりました。

青木君が作りたいのは、頂点数が $ N $ で、全ての $ i\ =\ 1,2,...,N $ について頂点 $ i $ と最も遠い頂点の距離が $ a_i $ となる木です。なお、辺の長さは全て $ 1 $ とします。

これを満たす木が存在するか判定してください。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 100 $
- $ 1\ ≦\ a_i\ ≦\ N-1 $

### Sample Explanation 1

!\[\](https://atcoder.jp/img/agc005/cda0380bb5cd1b9502cfceaf2526d91e.png) 上図は条件を見たす木の一例です。赤い矢印は最も遠い頂点への経路を表します。

## 样例 #1

### 输入

```
5
3 2 2 3 3```

### 输出

```
Possible```

## 样例 #2

### 输入

```
3
1 1 2```

### 输出

```
Impossible```

## 样例 #3

### 输入

```
10
1 2 2 2 2 2 2 2 2 2```

### 输出

```
Possible```

## 样例 #4

### 输入

```
10
1 1 2 2 2 2 2 2 2 2```

### 输出

```
Impossible```

## 样例 #5

### 输入

```
6
1 1 1 1 1 5```

### 输出

```
Impossible```

## 样例 #6

### 输入

```
5
4 3 2 3 4```

### 输出

```
Possible```

# 题解

## 作者：MiRaciss (赞：5)


很容易发现，可以把图拆成一条条链。那么所给的$a_i$中最大的即为图中最长的链的长度。


首先需要判断它能否构成一条链。如果一条链都不满足，那么肯定不成。

而一条链怎么判呢？

引入一个叫中间点的东西，即为$a_i$最小的点，可以发现它在链的中间，于是形象的称其为中间点，

如果$a_i$中的最小值无法达到$\lfloor \frac{x+1}{2} \rfloor$，那么就说明无法完成构图，因为一条链中的最小长度的点即为中间点，中间点到两端的长度就为$\lfloor \frac{x+1}{2} \rfloor$:

```cpp
if(Min<(Max+1)/2){
	printf("Impossible\n");		
	return 0;
}
```

接下来，我们对最长链的长度进行分类讨论。


如果长度是奇数，那么中间点就应该合成一个；如果长度为偶数，那么中间点就应该有两个。如果不满足，则直接结束

```cpp
if(Max&1){						//有奇数个点 
	if(f[Min]!=2){	
		printf("Impossible\n");	
		return 0;
	}
}
else {							//有偶数个点 
	if(f[Min]!=1){		
		printf("Impossible\n");
		return 0;
	}
}

```

我们可以发现，~~链是轴对称图形~~，链从中间点向左右两边，长度应该是对称的，所以从中间点的旁边的点开始算起,一定有另一个点的$a_i$值和其相等，所以除中间点外每个点都至少有两个，小于两个，就不成立。

```cpp
void Cheak(int Max){
	for(int i=(Max+1)/2+1;i<=Max;i++){	//从中间点的旁边的两个点开始算起 
		if(f[i]<2){		//对称，答案应该超过两个 
			printf("Impossible\n");
			return ;
		}
	}
	printf("Possible\n");
}

```

然后就完了qwq


```cpp
#include<bits/stdc++.h>
using namespace std;

int f[105];
int a[105];
int Max=0,Min=105;
int n;

void Cheak(int Max){
	for(int i=(Max+1)/2+1;i<=Max;i++){	//从中间点的旁边的两个点开始算起 
		if(f[i]<2){		//对称，答案应该超过两个 
			printf("Impossible\n");
			return ;
		}
	}
	printf("Possible\n");
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		f[a[i]]++;
		Max=max(Max,a[i]);
		Min=min(Min,a[i]);
	}
	if(Min<(Max+1)/2){
		printf("Impossible\n");		//如果连一条链都不可以达到 
		return 0;
	}
	if(Max&1){						//有奇数个点 
		if(f[(Max+1)/2]!=2){		//两个中间点合成一个，那么Max应该为偶数 
			printf("Impossible\n");	
			return 0;
		}
		Cheak(Max);
	}
	else {							//有偶数个点 
		if(f[Max/2]!=1){			// 中间点没有合为一个，Max为奇数 
			printf("Impossible\n");
			return 0;
		}
		Cheak(Max);
	}
	return 0;
}
```

---

## 作者：Hasinon (赞：3)

有一个结论，对于任意一个点，离他最远的点一定是它直径两端点中的一个。  

虽然与此题没有啥关系，但是我们容易因此想到找直径。  

直径的两端点一定是 $a$ 值最大的。
- 当他们的 $a$ 值为偶数的时候，如 $a=2$。
![](https://cdn.luogu.com.cn/upload/image_hosting/hduzaxf0.png)

从两端到中间到两端的 $a$ 值从 $a$ 下降到 $a/2+1$ 再上升到 $a$。

- 当他们的 $a$ 值为奇数的时候，如 $a=3$。
![](https://cdn.luogu.com.cn/upload/image_hosting/q1nqvimb.png)

从两端到中间到两端的 $a$ 值从 $a$ 下降到 $a/2$ 再上升到 $a$。

所以我们开个桶，第 $i$ 位记录 $a$ 值为 $i$ 的有几个，然后减去构造直径所需的点。 

- 如果发现构造不出来直径。（减去之后为剩余点数为负）  

- 如果发现有比直径上最小值更小的点。（由最前面的结论知，其他点的 $a$ 值不可能小于直径上的最小值）

就无法构造出这棵树。

code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define FOR(i,a,b) for(int i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(int i=(a); i>=(b); --i)
using namespace std;
const ll N=100;
ll a[N+10],vis[N+10];
ll mmax=0,n;
//
bool sol(){
	ll mid=mmax/2+1;
	FOR(i,mid,mmax){
		vis[i]-=2;
		if(vis[i]<0) return 0;
	}
	if(!(mmax&1)){
		--vis[mid-1];
		if(vis[mid-1]<0) return 0;
		--mid;
	}
	FOR(i,1,mid){
		if(vis[i]) return 0;
	}
	return 1;
}
int main() {
	n=gt(),mmax=0;
	FOR(i,1,n){
		a[i]=gt();
		++vis[a[i]];
		mmax=max(mmax,a[i]);
	} 
	sol()?printf("Possible\n"):printf("Impossible\n");
}


```

---

## 作者：Naro_Ahgnay (赞：2)

## 题目大意
给定一个长度为 $n$ 的序列，问是否存在一棵树，对于每一个点 $i(1≤i≤N)$，在树中离它距离最远的点与它的距离恰好等于 $a_i$。

## 思路
关于树的问题，应该要想到树的直径。

我们一步一步考虑不合法的情况。

+ 对于 $i$，当 $a_i$ 最大时 $i$ 肯定是直径的一个端点，所以当这样的 $i$ 只有一个时肯定不合法。

+ 从直径的两端向内考虑，最里面点的 $a_i$ 肯定需要满足 $a_i≥\lfloor \frac{\max a+1}{2}\rfloor$，所以 $\min a≥\lfloor \frac{\max a+1}{2}\rfloor$。

+ 发现当 $\max a$ 为奇数时，直径最里面的点只有一个； $\max a$ 为偶数时，直径最里面的点只有两个。除了最里面的点其他长度的 $a_i$ 需要满足至少有两个。

+ 用桶记录每个长度的点的数量，检验上一点的条件是否满足即可。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ma,d;
int a[101],b[101];
bool bo;
int main()
{
	scanf("%d",&n);
	memset(b,0,sizeof(b));
	ma=-1,bo=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[a[i]]++;
		if(a[i]>ma) ma=a[i];
	}
	d=ma+1>>1;
	for(int i=1;i<d;i++) 
		if(b[i]) {bo=0;break;}
	if(!bo) {puts("NO");continue;}
	if((ma&1)&&b[d]!=2) {puts("NO");continue;}
	if(!(ma&1)&&b[d]!=1) {puts("NO");continue;}
	for(int i=d+1;i<=ma;i++) 
		if(b[i]<2) {bo=0;break;}
	if(!bo) {puts("NO");continue;}
	puts("Yes");
	return 0;
}

```


---

## 作者：installb (赞：2)

先分析条件，本题给出了对每一个点，在树中离它距离最远的点与它的距离 $a_i$。  

可以想到树的直径的性质：  
- 距离任意点最远的点一定是直径的一个端点。  

通过题目条件得知了直径的长度（$len=\max{a_i}+1$）考虑先将一条直径构造出来，树至少存在一条直径。如果不能够选出点构造出直径，则为 `Impossible`。  

删去构造直径用到的点后，剩下的点的必有 $a_i\leq len-1$，我们观察能否使这些点的要求满足，这里根据树直径的上述的性质，把该点与直径上某一点相连，达到的最大距离为 $len-1$，最小距离为与直径中点相连的 $\lfloor\frac{len}{2}\rfloor+1$。  

显然直接把点与直径上的点直接相连可以取到最大值与最小值之间的任何一个值，所以没必要把点挂在别的点上，把所有点都挂在直径上就可以了。  

如果有 $a_i$ 比最小值小的点就不合法。

给张图，结合理解，黑链是直径，数字代表距离，~~画的有点丑吧~~。  
![](https://cdn.luogu.com.cn/upload/image_hosting/7azt7pps.png)  

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;

LL n,a;
LL mx = 0,cnt[100005];

int main(){
	ios::sync_with_stdio(false);
	cin >> n;
	for(LL i = 1;i <= n;i ++){
		cin >> a; mx = max(mx,a);
		cnt[a] ++;
	}
	for(LL i = 0;i <= mx;i ++) cnt[max(i,mx - i)] --;
	for(LL i = 1;i <= n;i ++) if(cnt[i] < 0){ cout << "Impossible" << endl; return 0; }
    // 组不成这条直径，这里直接减，减成负数代表不够用了
	
	for(LL i = 0;i <= ((mx + 1) >> 1);i ++) if(cnt[i] > 0){ cout << "Impossible" << endl; return 0; }
    // 距离太小无法满足

	cout << "Possible" << endl;
	return 0;
}
```

原评分 $\sf{\color{blue}1954}$  
还是感觉没那么难  
考察知识：树的直径及其性质  
实现难度/代码难度：几乎没有  
思维难度：还行吧，主要是树的直径的相关技巧

---

## 作者：CYJian (赞：2)

## AGC005C

首先我们发现，最远的一对点的链拉出来一定是一条直径。

然后在一条点数为 $L$ 的直径上，能通过挂在直径上的某个点上得到的距离一定是在 $[\left \lfloor \frac{L}{2} \right \rfloor +1,L-1]$ 这个区间内。而且有且仅有 $L \bmod 2 +1$ 个点的最远距离是 $\left \lfloor \frac{L}{2}\right \rfloor$，最远距离在 $[\left \lfloor \frac{L}{2} \right \rfloor +1,L-1]$ 内的点数至少为 $2$。

上面这些条件都不难得到。在纸上画一条链，发现每一条链一定都需要满足后两个性质；然后在每个点上（除了链的端点）挂上一个点，就能发现这些挂上去的点的最远距离一定都满足第一个条件。然后用这些条件随便判断一下就行了。

${\rm Code}$：

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int __SIZE = 1 << 18;
char ibuf[__SIZE], *iS, *iT;

#define ge (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
#define ri read_int()
#define rl read_ll()
#define FILE(s) freopen(s"in", "r", stdin), freopen(s"out", "w", stdout)
#define ERROR return puts("Impossible"), 0

template<typename T>
inline void read(T &x) {
	char ch, t = 0; x = 0;
	while(!isdigit(ch = ge)) t |= ch == '-';
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = ge;
	x = t ? -x : x;
}
inline int read_int() { int x; return read(x), x; }
inline ll read_ll() { ll x; return read(x), x; }

template<typename T>
inline void chkmax(T&a, T b) { a = a > b ? a : b; }

int c[110];
int mx;

int main() {
#ifdef LOCAL
	FILE("");
#endif

	int n = ri;
	for(int i = 1; i <= n; i++) {
		int x = ri;
		++c[x];
		chkmax(mx, x);
	}

	int mi = (mx + 1) >> 1;
	for(int i = mx; i > mi; --i) {
		if(c[i] < 2) ERROR;
		n -= c[i];
	}
	if(c[mi] != 1 + (mx & 1) || n != c[mi]) ERROR;
	puts("Possible");
	return 0;
}
```

---

## 作者：lizexuanaibiancheng (赞：1)

首先，我们可以很明显的知道，$\max_{i=1}^{n}a_i$ 就为树的直径的长度（后面记为 $len$），所以我们画图可以知道，直径上的点的 $a_i$ 一定在 $[\lceil \frac{len}{2} \rceil \dots len]$。

我们可以分情况讨论：

+ $len$ 为偶数，那么则有 $2$ 个 $a_i$ 为 $len$，$2$ 个 $a_i$ 为 $(len-1) \dots 1$ 个 $a_i$ 为 $\frac{len}{2}$

+ $len$ 为奇数，那么则有 $2$ 个 $a_i$ 为 $len$，$2$ 个 $a_i$ 为 $(len-1) \dots 2$ 个 $a_i$ 为 $\lceil \frac{len}{2} \rceil$

我们发现，除了 $len$ 为偶数多了一个 $\frac{len}{2}$ 以外都一样，都从 $\lfloor \frac{len}{2} \rfloor +1$ 开始到 $len$，所以代码也很好写：
```cpp
for(int i = (len >> 1)+1;i <= len;++i){ // 从 len/2+1 开始循环到 len
	cut[i] -= 2; // cut 为桶数组
	if(cut[i] < 0) return puts("Impossible"),0; // 不满足
}
if(!(len&1)){ // 特判偶数的情况
	cut[len/2]--;
	if(cut[len/2] < 0) return puts("Impossible"),0;	
}
```

接下来，我们从画的图可以知道，直径上挂的点的 $a_i$ 一定比直径上 $a_i$ 的大，如果有小于等于的它，那一定不会成一棵树。

通过前面的代码，我们知道，直径上的点最小的 $a_i$  为$\lceil \frac{len}{2} \rceil$，所以只需要判断是否小于这个值即可。

代码也非常简单：
```cpp
for(int i = 0;i <= (len+1) >> 1;++i){
	if(cut[i]) return puts("Impossible"),0;
}
```

总代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 110;
int cut[N],n,len;
inline int read(){ // 快速读入
	int res = 0;bool f = 1;char c = getchar();
	while(c < '0' || c > '9'){
		if(c == '-') f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		res = (res << 3) + (res << 1) - '0' + c;
		c = getchar();
	}
	return (f ? res : -res);
}
int main(){
	n = read();
	for(int i = 1,a;i <= n;++i){
		a = read();
		cut[a]++;
		len = max(len,a);
	} // 用桶存储所有的值，并求出直径
	for(int i = len/2+1;i <= len;++i){
		cut[i] -= 2;
		if(cut[i] < 0) return puts("Impossible"),0;
	} // 判断直径
	if(!(len&1)){
		cut[len/2]--;
		if(cut[len/2] < 0) return puts("Impossible"),0;	
	} // 特判 len 为偶数
	for(int i = 0;i <= (len+1) >> 1;++i){
		if(cut[i]) return puts("Impossible"),0;
	} // 判断其他点
	puts("Possible"); // 满足条件
	return 0;
}
```

---

## 作者：Leap_Frog (赞：1)

### P.S.
阳间题，可惜我是大傻逼。    

### Solution.
首先，树有一条直径，直径上的端点权值必定最大，所以我们找出最大值，然后就可以找到树的直径了。  
然后，它必定有一些节点，它的权值分别是 $\{k,k-1,...k-1,k\}$。  
我们把这些点去掉，剩下的点就相当于在这条链上挂节点。  
然后必定满足剩下的任意一个节点的权值都大于等于中间节点的权值。  
而且如果大于等于中间节点权值，且因为找到最大值了，所以它必定小于等于最大值。  
所以必然存在一个节点，它的权值是所需要权值减一，新加入节点挂它下面即可。  
然后就做完了，什么中点的啦权值的啦手摸手摸就好了啦。  

### Coding.
```cpp
//是啊，你就是那只鬼了，所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}/*}}}*/
int n,a[1005],tn[1005];
signed main()
{
	read(n);for(int i=1;i<=n;i++) read(a[i]),tn[a[i]]++;
	int mx=0;for(int i=1;i<=n;i++) mx=max(mx,a[i]);
	if(!(mx&1)) tn[mx>>1]--;
	for(int i=(mx>>1)+1;i<=mx;i++) tn[i]--,tn[i]--;
	for(int i=1;i<=mx;i++) if(tn[i]<0) return puts("Impossible"),0;
	int mn=1e9;for(int i=1;i<=n;i++) if(tn[i]) {mn=i;break;}
	if(mn<=((mx+1)>>1)) return puts("Impossible"),0;else return puts("Possible"),0;
}
```

---

## 作者：sky_of_war (赞：1)

没什么人来写题解吗。。
树上一个点的最远点，一定是直径的两个端点之一。所以首先我们找出直径的长度$L$。
然后分为两类：
 - $L$是偶数，那么$a_i=\frac{L}{2}$的点只能有一个，$\frac{L}{2} <  a_i \leq L$的点至少要有两个，如果有更多，则可以通过连接直径上$a_j=a_i-1$的点$j$来达成目标。而$a_i< \frac{L}{2}$的点不能存在。
 - $L$是奇数，那么$a_i=\lceil \frac{L}{2} \rceil$的点只能有两个，$\lceil \frac{L}{2} \rceil <a_i \leq L$至少有两个，$a_i < \lceil \frac{L}{2} \rceil$不能存在。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e2 + 10;
int a[MAXN], b[MAXN];
int n, mx = 0;
template <class T>
inline void _read(T &x)
{
	x = 0;
	char t = getchar();
	while (!isdigit(t) && t != '-') t = getchar(); 
	if (t == '-')
	{
		_read(x);
		x *= -1;
		return ;
	}
	while (isdigit(t))
	{
		x = x * 10 + t - '0';
		t = getchar();
	}
}
int main()
{
	_read(n);
	for (int i = 1; i <= n; ++i) _read(a[i]), mx = max(mx, a[i]), ++b[a[i]];
	if(mx & 1)
	{
		for(int i = mx; i >= (mx + 1) / 2; --i)
			if(b[i] < 2)
			{
				puts("Impossible");
				return 0;
			}
		for(int i = 1; i < (mx + 1) / 2; ++i)
			if(b[i])
			{
				puts("Impossible");
				return 0;
			}
		if(b[(mx + 1) / 2] > 2)
		{
			puts("Impossible");
			return 0;
		}
	}
	else
	{
		for(int i = mx; i > mx / 2; --i)
			if(b[i] < 2)
			{
				puts("Impossible");
				return 0;
			}
		for(int i = 1; i < mx / 2; ++i)
			if(b[i])
			{
				puts("Impossible");
				return 0;
			}
		if(b[mx / 2] != 1)
		{
			puts("Impossible");
			return 0;
		}
	}
	puts("Possible");
	return 0;
}

```

---

## 作者：Conan15 (赞：0)

既然是树，容易想到先构造一条链作为直径。\
如何找直径？显然对于一个直径端点，距离它最远的点是另一个直径端点。所以找出 $i,j$ 使得 $a_i = a_j = \max\limits_{k=1}^{n} a_k$ 即可。\
后面就简单了，考虑对直径长度 $t$ 进行奇偶讨论：

- 若 $t$ 是奇数:
    - 则中间那个点显然只能容纳一个数。因为无论你在哪里加边，都不可能让 $a$ 值与中间那个点相等。
    - 其它点必须有 $\geq 2$ 个点可以填，因为直径关于中心点对称。
- 若 $t$ 是偶数：
    - 中间两个点显然只能各容纳一个数，其它点必须 $\geq 2$。
    - 与上面同理。

为什么这样是对的？\
显然如果其它点容纳数量 $=2$，那么就成功构造出一条链。\
那么多余的点不是向这条链对应的位置连边就好了吗？

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 115;
int n, a[N];
int Max, c, cnt[N];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (Max < a[i]) Max = a[i], c = 1;
        else if (Max == a[i]) c++;
    }
    for (int i = 1; i <= n; i++) cnt[a[i]]++;
    if (cnt[1] > 1 && n > 2) return puts("Impossible"), 0;
    if (Max & 1) {
        int mn = (Max + 1) >> 1;
        bool flag = (cnt[mn] == 2);
        for (int i = mn + 1; i <= Max; i++) flag &= (cnt[i] >= 2);
        puts(flag ? "Possible" : "Impossible");
    } else {    //中间的只能出现一次
        int mn = Max >> 1;
        bool flag = (cnt[mn] == 1);
        for (int i = mn + 1; i <= Max; i++) flag &= (cnt[i] >= 2);
        puts(flag ? "Possible" : "Impossible");
    }
    return 0;
}
```

---

## 作者：SunburstFan (赞：0)

### C - Tree Restoring

#### 题目大意

有一个长度为 $N$，$a_1, a_2, ..., a_N$ 的整数序列，判断是否存在这样一棵树：

树上有 $N$ 个顶点，编号为 $1$ 到 $N$，假设每条边的长度为 $1$，对于每个 $i = 1,2,...,N$，顶点 $i$ 与离它最远的顶点之间的距离为 $a_i$。

#### 解题思路

考虑将最长距离直接拆成一条链，然后讨论其中点的位置与个数，记录下 $a_i$ 中的最小和最大值，进行极值判断。

还要对中点的个数进行判断，偶数长度的链，有两个中点，奇数长度的链，有一个中点，如果不对，说明不可行。

其次，我们注意到中点两边的点的中点个数应该大于 $2$。

`check` 函数：

```cpp
void check(vector<int> &f,int Max){
	for(int i=(Max+1)/2+1;i<=Max;i++){	
		if(f[i]<2){	
			cout<<"Impossible\n";
			return ;
		}
	}
	cout<<"Possible\n";
}
```

```cpp
int maxn=0,minn=1<<30;

vector<int> a(n+5),f(n+5,0);
for(int i=1;i<=n;i++){
    cin>>a[i];
    f[a[i]]++;
    maxn=max(maxn,a[i]);
    minn=min(minn,a[i]);
}

if(minn<(maxn+1)/2){
    cout<<"Impossible\n";
    return 0;
}

if(maxn&1){						
    if(f[(maxn+1)/2]!=2){		
        cout<<"Impossible\n";	
        return 0;
    }
    check(f,maxn);
}
else {				
    if(f[maxn/2]!=1){			
        cout<<"Impossible\n";
        return 0;
    }
    check(f,maxn);
}
```

---

## 作者：win114514 (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Al-lA/p/17646370.html)。

比较简单的题。

### 思路

我们可以把一棵树抽象成一条极长的链上挂了很多的点。

观察这样的树的性质。

除去中间的每一个 $dis$ 至少有两个点的 $a_i=dis$。

考虑这条链的长度为 $s$。

那么对于中间的点，我们可以分两种情况讨论。

1. $s$ 为偶数

    那么我们必然要求在中间的权值只有一个。

    否则无法构成一棵树。

2. $s$ 为奇数

    与偶数类似。

    那么我们必然要求在中间的权值有且仅有两个。

那么我们只需要把这几种情况判断一下即可。

### Code

[AC记录](https://atcoder.jp/contests/agc005/submissions/44694350)。

---

## 作者：xiaoyang111 (赞：0)

### 前言

[题目传送门。](https://www.luogu.com.cn/problem/AT_agc005_c)

构造题。

### 题解

#### 思路

距离序列中每个数是离这个点最远点的距离，通过最远，不难想到直径。

那么我们朝着直径这个方向思考。

通过手玩样例，可以先构造出一条直径，直径两个端点是距离序列最远的两个点。

那么直径中间的点呢？就直接拿距离序列上距离对应的点放在直径的中间，且除了中间的那个点的距离只有一个其他的距离都必须是成对出现的。

这样解释有点抽象，拿一个具体的例子解释。就像距离序列是 `5 4 3 3 4 5`，画成图就是这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/zeyoniuq.png)

如果直径都构造不出来，那么直接无解。

直径的部分解决了，接下来解决多的点。

我们可以把点直接挂在这条链上的一个点上面，像距离序列 `5 4 3 3 4 5 4 5 4 4` 的话图可以搞成下面这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/awk70vhq.png)

如果一个点过于小的话实在没地方放就无解。

那么我们直接开个桶用来构造直径和是否有过于小的点，如果不能构造直径或者有过于小的点就说明无解，否则有解。

#### 代码

下面是代码。

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;
int main(){
	int n;
	cin >> n;
	unordered_map<int,int> m;//桶
	int a;
	int mx=-1;
	for (int i=0;i<n;++i){
		scanf("%d",&a);
		mx=max(mx,a);
		m[a]++;
	} 
	for (int i=0;i<=mx;++i){//构造直径
		--m[max(mx-i,i)];
	}
	for (int i=0;i<=n;++i){//如果构造不了直径
		if (m[i]<0){
			cout<<"Impossible"<<endl;
			return 0;
		}
	}
	for (int i=0;i<=ceil(1.0*mx/2.0);++i){//找距离小的点
		if (m[i]){
			cout<<"Impossible"<<endl;
			return 0;
		}
	}
	cout<<"Possible"<<endl;
	return 0;
} 
```

---


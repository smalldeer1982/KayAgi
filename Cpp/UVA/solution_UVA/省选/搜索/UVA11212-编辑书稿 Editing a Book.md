# 编辑书稿 Editing a Book

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2153

[PDF](https://uva.onlinejudge.org/external/112/p11212.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11212/cb36674ea3b096f313832bf9d1662a62d42ac8f2.png)

## 样例 #1

### 输入

```
6
2 4 1 5 3 6
5
3 4 5 1 2
0```

### 输出

```
Case 1: 2
Case 2: 1```

# 题解

## 作者：mol_low (赞：18)

数据范围极小$2<=n<=9$，所以直接IDA* 就可以通过。

对于楼下提到的暴力，在此不加赘述，讲讲更快的方法(0ms)
# 言归正传
假设每次移动一个数$u$，如果我们不考虑其他因素，只单把$u$放到第$u$位，则$u$到达了正确的位置。所以我们最多移动$n$步就一定可以使所有数到达应到的位置，而$n\le9$。基于这个前提，我们便可以采用IDA* 算法求出答案。

设$f(n)=g(n)+h(n)$，我们接下来设计$h(n)$：因为每次移动$a[i]$至$a[j-1]$，
则在最好的情况，$a[i]$的后继会正确，原来的$a[j-1]$(如今的$a[j-2]$)的后继会正确，原来的$a[i-1]$(如今的$a[i-2]$)的后继也会正确。所以，每次移动最多使3个数的后继正确。所以我们设计出如下式子：$f(n)=g(n)+different(n)/3$。由于$different(n)$可能不会被3整除，所以我们进行等价变形:$3*f(n)=3*g(n)+h(n)$

先贴出朴素代码：
```
#include <cstdio>
#include <cstring>
#define N 12

int a[N + 2] , n , num;
int deepth;
bool solve;

int check() {
	int different = 0;
	for(int i = 1; i <= n; i++) if(a[i] != a[i - 1] + 1) different++;
	return different;
}

void IDDFS(int cur) {
	int ret = check();
	if(cur * 3 + ret > deepth * 3) return;
	if(!ret) {
		solve = 1;
		return;
	}
	int copy_first[N + 2] , copy_second[N + 2];
	memcpy(copy_first , a , sizeof(a));
	for(int i = 1; i <= n; i++) 
		if(a[i] != a[i - 1] + 1) {
			for(int j = i; j <= n; j++) {
				if(j < n and a[j + 1] == a[j] + 1) continue;
				for(int k = i; k <= j; k++) copy_second[k] = a[k];
				for(int k = j + 1; k <= n; k++) {
					if(k < n and a[k + 1] == a[k] + 1) continue;
					for(int left = i , right = j + 1; right <= k; left++ , right++) a[left] = a[right];
					for(int right = i + k - j , left = i; left <= j; left++ , right++) a[right] = copy_second[left];
					IDDFS(cur + 1);
					if(solve) return;
					memcpy(a , copy_first , sizeof(a));
				} 
			}
		}
}

int main() {
	while(scanf("%d", &n) and n) {
		memset(a , 0 , sizeof(a));
		solve = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(deepth = 0; deepth <= n; deepth++) {
			IDDFS(0);
			if(solve) break;
 		}
		printf("Case %d: %d\n", ++ num , deepth);
	}
	return 0;
}
```
到此，我们已经设计出可以通过本题的代码(10ms左右)，但还可以进一步优化。
## 优化
在剪切时，我们可以设想出如下情形：

设现有$A,B,C$三段待剪切。我们可以发现$A$与$B$的分界便是当$A$的最后一个元素$a[i]!=a[i+1]+1$时，即非连续的一段。而$B$与$C$的分界也是如此。

在我们朴素的交换中，直接将$A,B,C$交换变成$C,B,A$。但是，如果$C$整体比$A$大，$C$还需要排在$A$后面怎么办呢。我们之前的朴素代码会无脑暴力搜下去，而浪费许多时间！

在~~苦思冥想~~后~~小蒟蒻~~想出来一种解决办法：生活常识

我们继续考虑$A,B,C$，如果出现上文提到的情况，我们根本不需要交换$A$和$C$，因为如果交换了，以后还要交换回来，反而得不偿失。

在这个~~小优化~~的加持下，时间复杂度便会骤降。在极限数据下，每个$cur$(当前搜索深度，$IDDFS$特定名词)会减少100000+次搜索！

下贴代码(~~博主良心~~)(0ms)：
```
#include <cstdio>
#include <cstring>
#define N 12

int a[N + 2] , n , num;
int deepth;
bool solve;

int check() {
	int different = 0;
	for(int i = 1; i <= n; i++) if(a[i] != a[i - 1] + 1) different++;
	return different;
}

void IDDFS(int cur) {
	int ret = check();
	if(cur * 3 + ret > deepth * 3) return;
	if(!ret) {
		solve = 1;
		return;
	}
	int copy_first[N + 2] , copy_second[N + 2];
	memcpy(copy_first , a , sizeof(a));
	for(int i = 1; i <= n; i++) 
		if(a[i] != a[i - 1] + 1) {
			for(int j = i; j <= n; j++) {
				if(j < n and a[j + 1] == a[j] + 1) continue;
				if(a[j + 1] > a[j]) continue;
				for(int k = i; k <= j; k++) copy_second[k] = a[k];
				for(int k = j + 1; k <= n; k++) {
					if(k < n and a[k + 1] == a[k] + 1) continue;
					for(int left = i , right = j + 1; right <= k; left++ , right++) a[left] = a[right];
					for(int right = i + k - j , left = i; left <= j; left++ , right++) a[right] = copy_second[left];
					IDDFS(cur + 1);
					if(solve) return;
					memcpy(a , copy_first , sizeof(a));
				} 
			}
		}
}

int main() {
	while(scanf("%d", &n) and n) {
		memset(a , 0 , sizeof(a));
		solve = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(deepth = 0; deepth <= n; deepth++) {
			IDDFS(0);
			if(solve) break;
 		}
		printf("Case %d: %d\n", ++ num , deepth);
	}
	return 0;
}
```

---

## 作者：NXYorz (赞：7)


[题目](https://www.luogu.com.cn/problem/UVA11212)

首先我们来看数据范围很小，就考虑~~状压~~或者搜索，在仔细一想，这个过程好像不太容易模拟？所以我们就用搜索来降低模拟这个过程的难度。

我们可以用迭代加深来做，从 $0$ 开始枚举答案 $d$ ，然后判断是否这个答案可行，第一次找到的一定是最小的。

再者我们考虑怎么搜，我们可以把剪切粘贴的过程抽象为将此序列的某两个 **相邻** 的子串调换一下位置。于是乎我们就首先枚举 **被剪切** 的序列的首段，然后枚举 **被剪切** 序列长度，然后枚举 **被粘贴** 的位置。

也许我的表述不是那么准确，就举一个例子来说明一下这个过程：

首先我们有一个序列 $a,b,c,d,e,f,g$ ，然后我们选择 $b$ 作为作为 **被剪切** 序列的首段，然后我们假设当前枚举到的 **被剪切** 序列的长度为 $2$ ，那么就是说我们被剪切的序列为 $b,c$ ，然后假设我们枚举的 **被粘贴** 的序列位置为 $f$。

因此我们要做的就是讲序列 $b,c$ ,与序列 $d,e,f$ 调换一下位置。

明白了这一点，我们会发现这样做并不是很容易实现，而且回溯的时候也会很麻烦，可以考虑单独写两个函数来实现，这样会使思路清晰很多。

操作代码如下：
```cpp
inline void swap(int x,int y,int k,int z)
{
	int sum=0,b[9],c[9];
	for(register int i=k;i<=z;i++) b[i]=a[i];
	for(register int i=x;i<=x+y-1;i++) c[i]=a[i];
	for(register int i=z-y+1;i<=z;i++) {a[i]=c[x+sum];sum++;}
	sum=0;
	for(register int i=x;i<=x+z-k;i++) {a[i]=b[k+sum];sum++;}
}
```

回溯代码如下：
```cpp
inline void reswap(int x,int y,int k,int z)
{
	int sum=0,b[9],c[9];
	for(register int i=z-y+1;i<=z;i++) b[i]=a[i];
	for(register int i=x;i<=x+z-k;i++) c[i]=a[i];
	for(register int i=k;i<=z;i++) {a[i]=c[x+sum];sum++;}
	sum=0;
	for(register int i=x;i<=x+y-1;i++) {a[i]=b[z-y+1+sum];sum++;}
}
```

这里解释一下变量，$x$指的是 **被剪切** 序列的首段，$y$ 指的是 **被剪切** 序列的长度，$z$ 是 **被粘贴** 的序列位置,那么 $k$ 自然就是中间形成的序列的起始位置了。

为了保险起见我们可以加一个估价函数，估价函数写的质量直接影响你的程序的效率，自然地，我们首先要保证这个估价函数是正确的。

我们可以写一个求还有多少元素没有就位的函数，美曰其名为 $step$ ，然后我们考虑，每操作一次，最多可以使多少元素就位，仔细想想应该是 $3$ 个，然后我们就可以有一个可行性剪枝了：当前步数加上至少需要的步数是否大于上限了。

#### $Code$
```cpp
#include<iostream>
#include<cstdio>
#define N 10
using namespace std;
int n,d,ans;
int a[N];
inline void print(int x) 
{printf("Case %d: %d\n",x,d);}
inline void in(int &x)
{
	x=0;char ee=getchar();
	while(ee<'0'||ee>'9') ee=getchar();
	while(ee>='0'&&ee<='9') {x=(x<<1)+(x<<3)+ee-'0';ee=getchar();}
}
inline int g()
{
	int cnt=0;
	for(register int i=2;i<=n;i++)
		if(a[i]!=a[i-1]+1) cnt++;
	return cnt;
}
inline void swap(int x,int y,int k,int z)
{
	int sum=0,b[9],c[9];
	for(register int i=k;i<=z;i++) b[i]=a[i];
	for(register int i=x;i<=x+y-1;i++) c[i]=a[i];
	for(register int i=z-y+1;i<=z;i++) {a[i]=c[x+sum];sum++;}
	sum=0;
	for(register int i=x;i<=x+z-k;i++) {a[i]=b[k+sum];sum++;}
}
inline void reswap(int x,int y,int k,int z)
{
	int sum=0,b[9],c[9];
	for(register int i=z-y+1;i<=z;i++) b[i]=a[i];
	for(register int i=x;i<=x+z-k;i++) c[i]=a[i];
	for(register int i=k;i<=z;i++) {a[i]=c[x+sum];sum++;}
	sum=0;
	for(register int i=x;i<=x+y-1;i++) {a[i]=b[z-y+1+sum];sum++;}
}
inline bool dfs(int x)
{
	int step=g();
	if(x>d)
	{
		if(step==0) return true;
		return false;
	}
	if((x-1)*3+step>d*3) return false;
	for(register int i=1;i<=n;i++) 
		for(register int j=1;j+i<=n;j++) 
			for(register int k=j+i;k<=n;k++) 
			{
				swap(i,j,j+i,k);
				if(dfs(x+1)) return true;
				reswap(i,j,j+i,k);
			}
	return false;
}	
int main()
{
	int sum=0;
	while(1)
	{
		in(n);if(n==0) break;
		sum++;
		for(register int i=1;i<=n;i++) scanf("%d",a+i);
		d=0;if(g()==0) {print(sum);continue;}
		for(d=1;;d++)
		 if(dfs(1)) 
		{print(sum);break;}
	}return 0;
}
//7 6 5 2 4 3 1
```

--------

写在后面

调了好久，主要是思想简单但是实现比较困难，比较有代码难度。

[强行推荐博客](https://www.luogu.com.cn/blog/niexiaoyang12138/)

$End$














---

## 作者：PPPPz (赞：4)


那么可以用IDA*来做。设 $f(x)=g(x)+d(x)$

其中 $f(x)$ 为总次数, $g(x)$ 为当前次数, $d(x)$ 为剩下次数。

设 $h(x)$ 为后继不正确的数的数

因为每一次移动最多可以将三个不正确的数改为正确的

则 $d(x)\ge h(x)/3$

则 $f(x)\ge g(x)+h(x)/3$

所以 $3 * f(x)\ge 3*g(x)+h(x)$

IDA* 代码如下

代码如下,耗时0ms
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=11;
int n,lefts[maxn],rights[maxn];
int readint()
{
	//快读
	char c=getchar();
	int a=1,x=0;
	while(!isdigit(c))
	{
		if(c=='-')
			a=-1;
		c=getchar();
	}
	while(isdigit(c))
	{
		x*=10;
		x+=c-'0';
		c=getchar();
	}
	return a*x;
}
void link(int l,int r)
{
	rights[l]=r;
	lefts[r]=l;
}
bool read()
{
	n=readint();
	if(n==0)
		return 0;
	int l,r=0;
	for(int i=0;i<n;i++)
	{
		l=r;
		r=readint();
		link(l,r);
	}
	l=r;
	r=n+1;
	link(l,r);
	return 1;
}
int h()
{
	//估价函数，统计有几个顺序不正确的
	int cnt=0;
	for(int i=1;i<=n+1;i++)
	{
		if(i-1!=lefts[i])
			cnt++;
	}
	return cnt;
}
bool iddfs(int f,int g)
{
	//迭代加深搜索
	if(h()+g*3>f*3)
		return 0;
   //剪枝
	if(h()==0)
		return 1;
   //正确顺序则返回
	for(int i=rights[0];i<=n;i=rights[i])
	{
		for(int j=i;j<=n;j=rights[j])
		{
			for(int k=rights[j];k<=n;k=rights[k])
			{
				int ll=lefts[i],rr=rights[j];
				link(lefts[i],rights[j]);
				link(j,rights[k]);
				link(k,i);
				if(iddfs(f,g+1))
					return 1;
           	//回溯
				link(lefts[i],rights[j]);
				link(ll,i);
				link(j,rr);
			}
		}
	}
	return 0;
}
int solve()
{
	int ans=0;
	while(!iddfs(ans,0))
	{
		ans++;
	}
	return ans;
}
int main()
{
   int kase=1;
	while(read())
	{
		printf("Case %d: %d\n",kase++,solve());
	}
	return 0;
}
```


---

## 作者：Zenurik (赞：3)

**只有一篇题解，而且还是IDA***……

但是以这题的数据范围其实没有必要用IDA*。(~~我才不会告诉你其实我不会呢QAQ~~)

通过手推最坏情况(987654321)可以发现答案最多不超过5步。

双向bfs，先从初始状态搜索3步，再从终态搜索2步。

然后你就会发现这样做需要20多s。

emm……于是尝试用map把状态哈希，愉快地压到了3s。为了卡常又换了unordered_map，但似乎差别不大。

后来发现从初态和终态各搜2步，如果没有答案那么答案自然是5.

最终还是比IDA*慢一点~~但是好想啊qwq~~

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
#include <tr1/unordered_map>
#include <vector>
#include <cstdlib>
#ifdef WIN32
#include <windows.h>
#endif
std::tr1::unordered_map<int, int> fir, sec;
std::map<int, int> calc;
std::queue<std::pair<int, int> > q;
int n, order[10], a[10], ans, temp[10];

inline int merge(int* tmp) {
    int res = 0;
    for(register int i = n; i >= 1; i--) res = (res<<3) + (res<<1) + tmp[i];
    return res;
}

inline void decompose(int x, int* tmp) {
    for(register int i = 1; i <= n; i++, x /= 10) tmp[i] = x%10;
}

void bfs1() {
    int x = merge(a);
    q.push(std::make_pair(x, 0));
    while(!q.empty()) {
        int sta = q.front().first, stp = q.front().second;
        q.pop();
        if(++stp >= 3) break;
        decompose(sta, a);
        for(int l = 1; l <= n; l++)
            for(int r = l; r <= n; r++)
                for(int k = 1; k+r-l <= n; k++) {
                	int pos1 = k, pos2 = l;
                	while(pos2 <= r) temp[pos1++] = a[pos2++];
                	pos1 = 1, pos2 = 1;
                	while(pos1 <= n) {
                		if(pos1 == k) pos1 = k+r-l+1;
                		if(pos2 == l) pos2 = r+1;
                		temp[pos1++] = a[pos2++];
					}
					int now = merge(temp);
					if(!fir[now]) {
						fir[now] = stp;
						q.push(std::make_pair(now, stp));
					}
				}
    }
}

void bfs2() {
	int x = merge(a);
	if(fir[x]) ans = std::min(ans, fir[x]);
	q.push(std::make_pair(x, 0));
	while(!q.empty()) {
		int sta = q.front().first, stp = q.front().second;
		q.pop();
		if(++stp >= 3) break;
		decompose(sta, a);
		for(int l = 1; l <= n; l++)
            for(int r = l; r <= n; r++)
                for(int k = 1; k+r-l <= n; k++) {
                	int pos1 = k, pos2 = l;
                	while(pos2 <= r) temp[pos1++] = a[pos2++];
                	pos1 = 1, pos2 = 1;
                	while(pos1 <= n) {
                		if(pos1 == k) pos1 = k+r-l+1;
                		if(pos2 == l) pos2 = r+1;
                		temp[pos1++] = a[pos2++];
					}
					int now = merge(temp);
					if(fir[now]) ans = std::min(ans, fir[now]+stp);
					if(!sec[now]) {
						sec[now] = 1;
						q.push(std::make_pair(now, stp));
					}
				}
	}
}

int main() {
	int T = 0;
    while(scanf("%d", &n) != EOF && n) {
    	T++;
    	fir.clear();
    	sec.clear();
    	while(!q.empty()) q.pop();
        ans = 5;
        for(int i = 1; i <= n; i++) order[i] = i;
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        int x = merge(a);
        if(x == merge(order)) {
            printf("Case %d: 0\n", T);
            continue;
        }
        if(calc[x]) {
            printf("Case %d: %d\n", T, calc[x]);
            continue;
        }
        bfs1();
        for(int i = 1; i <= n; i++) a[i] = i;
        bfs2();
        printf("Case %d: %d\n", T, calc[x] = ans);
    }
    return 0;
}
```

---

## 作者：Mortidesperatslav (赞：2)

IDA*。

本题的难点在于如何构造估价函数使得估价合理且乐观。

我们来分析一次交换产生的最大贡献（因为要乐观）。

其余题解对估价函数的设计的讲解大致如下：

注意到假设我们把 $[i,j]$ 这段区间移动到第 $k$ 个元素后面，那么最优情况下：

+ $a_{i-1}+1=a_{k}$。

+ $a_j+1=a_{k+1}$。

+ $a_k+1=a_i$。

这样就产生了 $3$ 的贡献。所以设有 $x$ 个 $a_i\neq a_{i-1}+1$（为了方便，不妨设 $a_0=0$），估价函数可以定义为 $h(x)=\dfrac{x}{3}$。

这个时候你可能会问一个问题：为什么当 $a_i=a_{i-1}+1$ 时，我们不进行交换？

证明：若 $a_i=a_{i-1}+1$，则交换之后最大的贡献：

$a_j+1=a_{k+1}$，贡献为 $1$。

$a_k+1 \neq a_i$。无贡献。

$a_{i-1}+1 \neq a_{k}$。无贡献。

然后注意到本来 $a_i=a_{i-1}+1$ 贡献没掉了，也就是说，这次操作没有贡献。

而如果把 $[i+1,j]$ 放到第 $k$ 个元素后面：

$a_j+1=a_{k+1}$。贡献为 $1$。如果把 $[i,j]$ 放到第 $k$ 个元素后面，这个贡献依然存在。

$a_{k+1}$ 可能等于 $a_{i+1}$。

$a_{i+1}$ 可能等于 $a_k$。

这样一定更优。

同理我们可以证明 $a_j+1=a_{j+1}$ 和 $a_k+1=a_{k+1}$ 时不会把 $[i,j]$ 放到第 $k$ 个元素之后。

这就证明了我们估价函数的正确性。剩下的就是 IDA*+剪枝了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[105], id, ans = -1, lim;
double h(const int p[20]){
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		if (p[i] != p[i - 1] + 1)
			cnt++;
	return cnt / 3.0;
}
struct node{
	int p[20], dep;
	bool operator < (node b)const{
		return h(this->p) + this->dep > h(b.p) + b.dep;
	}
};
void dfs(node u){//IDA*
	u.p[0] = 0;
//	cout << u.dep << "\n";
//	for (int i = 1; i <= n; i++)
//		cout << u.p[i] << " ";
//	cout << "\n";
//	system("pause");
//	cout << h(u.p) << "\n";
	if (u.dep > lim)
		return;
	if (h(u.p) < 1e-7){
//		cout << h(u.p) << "\n";
		ans = u.dep;
		return;
	}
	if (ans != -1)
		return;
	priority_queue<node> q;//我喜欢用堆优先搜估计的最优解
	for (int i = 1; i <= n; i++){
		if (a[i] == a[i - 1] + 1)//剪枝
			continue;
		for (int j = i; j <= n; j++){
			if (j < n && a[j + 1] == a[j] + 1)//剪枝
				continue;
			int tmp[20];
			for (int l = i; l <= j; l++)
				tmp[l] = u.p[l];
			for (int k = j + 1; k <= n; k++){
				if (k < n && a[k + 1] == a[k] + 1)//剪枝
					continue;
				node v = u;
				v.dep++;
				int pl = i, pr = j + 1;
				while (pr <= k)
					v.p[pl++] = v.p[pr++];
				pl = i, pr = i + (k - j);
				while (pl <= j)
					v.p[pr++] = tmp[pl++];
				if (h(v.p) + v.dep > lim)
					continue;
			//	dfs(v);
				q.push(v);
			}
		}
	}
	while (!q.empty()){
		node v = q.top();
		q.pop();
		dfs(v);
	}
}
int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);cout.tie(0);
	while (cin >> n){
		if (!n)
			break;
		++id;
		ans = -1;
		node tmp;
		for (int i = 1; i <= n; i++){
			cin >> a[i];
			tmp.p[i] = a[i];
		}
		tmp.dep = 0;
		for (lim = 0; lim <= n; lim++){//迭代加深枚举深度
			dfs(tmp);
			if (ans != -1){
				cout << "Case " << id << ": " << lim << "\n";
				break;
			}
		}
	}
	return 0;
}

---

## 作者：Xu_brezza (赞：2)

# IDA*
博大精深的算法，也就是所谓的迭代加深搜索，适用在dfs里，是一种通过深度上限和估价函数来限制搜索树从而剪枝的方法。

$ maxd $ $g(n)$ $h(n)$ 分别为我们指定的最大搜索深度，当前搜索深度，乐观估价函数。其中 $maxd$ 通过枚举得到，接下来通过本题讲讲乐观估价函数。

顾名思义，他是在最乐观的情况下进行的，他代表的是当前深度最乐观情况下还需要将搜索树加深几层，换句话说，就是至少再进行几次操作。对于本题我们可以这么来设计：

考虑 $a$ $b$ $c$ $d$ 四个相邻序列，假设我们剪切 $b$ 变为 $a$ $c$ $b$ $d$  那么最好情况是什么？就是 $ac$ $cb$ $bd$ 之间相邻的数都合法了，那么最多一次我们可以使 $3$ 组合法，进而我们可以得出，对于数列中所有不合法的 $h$ 组数对，最理想情况下我们只需要 $h/3$   次操作使他变成目标序列。那么不合法的就变成了 $h(n)/3 + g(n) > maxd$ 再变一下就是 $h(n) + g(n) \times 3 > maxd$ 。这就是所谓的估价函数。

剩下的只需要按照他说的剪切就行了。

```cpp
#include<cstdio>
#include<queue>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cctype>
#include<vector>
#include<string>
using namespace std;
const int N = 15;
int n,depth,flag;
int a[N];
inline int evaluate(){
	int res = 0;
	for(int i=1;i<=n;++i)if(a[i] != a[i-1] + 1)res++;
	return res;
}
inline void f(int to_start,int from_start,int end,int *p,int *q){
	for(int i=to_start,j=from_start;j<=end;++j,++i)p[i] = q[j];
} 
inline void IDA_star(int now_depth){
	int res = evaluate();
	if(now_depth * 3 + res > depth * 3)return;
	if(res == 0)return flag = 1,void();
	int b[N],c[N];
	memcpy(b,a,sizeof(b));
	for(int i=1;i<=n;++i){
		if(a[i] != a[i-1] + 1){//不合法 
			for(int j=i;j<=n;++j){//子段枚举 
				if(j < n && a[j+1] == a[j] + 1)continue;//合法 
				if(a[j+1] > a[j])continue;//合法 
				for(int k=i;k<=j;++k)c[k] = a[k];//存当前子序列 
				for(int k=j+1;k<=n;++k){//枚举粘贴的右节点 
					if(k < n && a[k+1] == a[k] + 1)continue;//当前点与他后面的合法，不动 
					f(i,j+1,k,a,a);//就是把当前j+1 ~ k这一段给我们的上面的子序列i~i+k-j，粘贴过来 
					f(i+k-j,i,j,a,c);//子序列里的粘贴过去 
					IDA_star(now_depth+1);
					memcpy(a,b,sizeof(a));//回溯 
					if(flag)return;
				}
			}
		}
	}
}
int main(){
	int cnt = 0;
	while(scanf("%d",&n) == 1 && n){
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		flag = 0;
		for(depth = 0;depth <= n;++depth){
			IDA_star(0);
			if(flag)break;
		}
		printf("Case %d: %d\n",++cnt,depth);
	}
}

```


---

## 作者：peterwuyihong (赞：2)

题意：给你一个排列，每次你可以把一个子段捞出来塞在别的位置，称为 $1$ 次操作，问你几次操作能让这个排列复原。

看没有双向 BFS 的，这里写一发

你正着搜，同时倒着搜，这样搜索树会少一半指数。

```cpp
State target;
int d[2][maxs];
State q[2][maxs];
int front[2], rear[2];
int bfs() {
	int cur = 0;
	for (int i = 0; i < 2; ++i) front[i] = rear[i] = 0;
	memset(d, -1, sizeof(d));
	State start;
	for (int i = 0; i < n; ++i) start.v[i] = i + 1;
	int x = start.hash();
	d[cur][x] = 0, d[cur ^ 1][t] = 0;
	q[cur][rear[cur]++] = start;
	q[cur ^ 1][rear[cur ^ 1]++] = target;
	State tmp, now;
	int dep[2] = { 0, 0 };
	while (true) {
		if (front[cur] >= rear[cur]) cur ^= 1;
		if (front[cur] >= rear[cur]) break;
		tmp = q[cur][front[cur]++];
		x = tmp.hash();
		if (d[cur][x] > dep[cur]) {
			dep[cur] = d[cur][x];
			cur ^= 1;
			continue;
		}
		if (d[cur ^ 1][x] != -1) {
			return d[cur][x] + d[cur ^ 1][x];
		}
		for (int l = 0; l < n; ++l)
			for (int r = l; r < n; ++r) {
				for (int k = -1; k < n; ++k) {
					if (l <= k&&k <= r) continue;
					now = tmp;
					now.insert(l, r, k);
					int y = now.hash();
					if (d[cur][y] != -1) continue;
					d[cur][y] = d[cur][x] + 1;
					q[cur][rear[cur]++] = now;
				}
			}
	}
}
```

---

## 作者：ygsldr (赞：2)

可以证明，最大步数肯定小于9次，即每次将一个移到他的位置

当然从排序的想法理应必这个小，我对9个数进行了全排列，发现答案最大也为5（但是太弱证不来）。

回归正题，答案肯定<=5,所以我们可以用迭代加深搜索

于是很愉快地打了个IDDFS啊，然后很开心的TLE了emmmm...

```cpp
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int n,Dep;
int p[15][15];
inline bool notok(int dep)
{
    for(int i(0);i < n;++i)
        if(p[dep][i] != i)return false;
    return true;
}
bool dfs(int dep)
{
    if(dep == Dep)
        return notok(dep);
    int nextdep = dep + 1;
    for(int len(1);len < n;++len)//切割长度
    {
        for(int start(0);start <= n - len;++start)
        {//从哪开始切
            if(start && p[dep][start] - 1 == p[dep][start - 1])
                continue;
            if(start + len < n && p[dep][start + len] - 1 == p[dep][start + len - 1])
                continue;
            //如果试图切割完整串，就不剪，相比A*的剪枝弱多了
            //我的剪切粘贴还是比较复杂的，最好自己实现一个，这也是一个比较细节的地方
            for(int pos(0);pos <= n - len;++pos)
            {//贴到哪个位置前面
                if(pos >= start && pos < start + len)
                    continue;
                //不要贴到自己里面
                for(int i(0);i < n;++i)
                    p[nextdep][i] = p[dep][i];
                if(pos < start)
                {
                    for(int i(0);i < len;++i)
                        p[nextdep][pos + i] = p[dep][start+i];
                    for(int i(pos);i < start;++i)
                        p[nextdep][i + len] = p[dep][i];
                }
                else
                {
                    for(int i(0);i < len;++i)
                        p[nextdep][pos + i] = p[dep][start+i];
                    for(int i(pos);i > start;--i)
                        p[nextdep][i - len] = p[dep][i];
                }
                
                if(dfs(nextdep))
                    return true;	
            }
        }
    }	
    return false;
}
int main()
{
    int T(0);
    while(scanf("%d",&n) != EOF && n != 0)
    {
        ++T;
        for(int i(0);i < n;++i)
        {
            scanf("%d",&p[0][i]);
            --p[0][i];
        }
        for(int i(0);i <= n;++i)
        {
            Dep = i;
            if(dfs(0))
            {
                printf("Case %d: %d\n",T,i);
                break;
            }
        }
    }
    return 0;
}

```

所以说，要优化，我们可以用IDA*,那么就是乐观估价函数的问题了

定义h()表示有多少个数后继不正确

我们每次操作，最多改变3个数的后继如：

EABCD -> EACBD

可见，ABC的后继改变了,而DE没有变

那么可以写出剪枝条件：(h()+2)/3+dep > maxdep,maxdep为深度限制，就可以愉快的AC了

放出示例代码
```cpp
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int n,Dep;
int p[15][15];
inline int discorrect(int dep)
{
    int ret(0);
    for(int i(0);i < n - 1;++i)
        ret += p[dep][i + 1] != p[dep][i] + 1;
    return ret + (p[dep][n - 1] != (n - 1));	
}
inline bool notok(int dep)
{
    for(int i(0);i < n;++i)
        if(p[dep][i] != i)return false;
    return true;
}
bool dfs(int dep)
{
    if(dep == Dep)
        return notok(dep);
    int nums = discorrect(dep);
    if(dep*3 + nums > Dep*3)
        return false;
    int nextdep = dep + 1;
    for(int len(1);len < n;++len)
    {
        for(int start(0);start <= n - len;++start)
        {
            if(start && p[dep][start] - 1 == p[dep][start - 1])
                continue;
            if(start + len < n && p[dep][start + len] - 1 == p[dep][start + len - 1])
                continue;
            for(int pos(0);pos <= n - len;++pos)
            {
                if(pos >= start && pos < start + len)
                    continue;
                for(int i(0);i < n;++i)
                    p[nextdep][i] = p[dep][i];
                if(pos < start)
                {
                    for(int i(0);i < len;++i)
                        p[nextdep][pos + i] = p[dep][start+i];
                    for(int i(pos);i < start;++i)
                        p[nextdep][i + len] = p[dep][i];
                }
                else
                {
                    for(int i(0);i < len;++i)
                        p[nextdep][pos + i] = p[dep][start+i];
                    for(int i(pos);i > start;--i)
                        p[nextdep][i - len] = p[dep][i];
                }
                
                if(dfs(nextdep))
                    return true;	
            }
        }
    }	
    return false;
}
int main()
{
    int T(0);
    while(scanf("%d",&n) != EOF && n != 0)
    {
        ++T;
        for(int i(0);i < n;++i)
        {
            scanf("%d",&p[0][i]);
            --p[0][i];
        }
        for(int i(0);i <= n;++i)
        {
            Dep = i;
            if(dfs(0))
            {
                printf("Case %d: %d\n",T,i);
                break;
            }
        }
    }
    return 0;
}

```


---

## 作者：Engulf (赞：1)

因为 $n \le 9$，所以我们可以肯定答案不会很大，但是操作的方案特别多，搜索树会特别庞大。因此，我们需要使用 IDA* 来解决。

IDA* 最重要的是估价函数的设计。

**重要：估价函数不能大于实际步数。**

对于本题来说，可以发现，每次移动一段书，会影响最多三本书的后继，而我们又可以发现最终的状态的每本书的后继都是固定的，所以我们可以统计后继不同的书的本数 $\mathrm{cnt}$，可以认为至少要 $\left\lceil \dfrac{\mathrm{cnt}}{3}\right\rceil$ 次完成。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int inf = 0x3f3f3f3f;
const LL infLL = 0x3f3f3f3f3f3f3f3fLL;

const int N = 15;

int n;
int q[N];
int w[5][N];

int f()
{
	int cnt = 0;
	for (int i = 0; i + 1 < n; i ++ )
		if (q[i + 1] != q[i] + 1)
			cnt ++ ;
	return (cnt + 2) / 3;
}

bool check()
{
	for (int i = 0; i + 1 < n; i ++ )
		if (q[i + 1] != q[i] + 1)
			return false;
	return true;
}

bool dfs(int u, int dep)
{
	if (u + f() > dep) return false;
	if (check()) return true;
	for (int len = 1; len <= n; len ++ )
		for (int i = 0; i + len - 1 < n; i ++ )
		{
			int j = i + len - 1;
			for (int k = j + 1; k < n; k ++ )
			{
				memcpy(w[u], q, sizeof q);
				int x, y;
				for (x = j + 1, y = i; x <= k; x ++ , y ++ ) q[y] = w[u][x];
				for (x = i; x <= j; x ++ , y ++ ) q[y] = w[u][x];
				if (dfs(u + 1, dep)) return true;
				memcpy(q, w[u], sizeof q);
			}
		}
	return false;
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr);
	int tt = 1;
	while (cin >> n, n)
	{
		for (int i = 0; i < n; i ++ ) cin >> q[i];
		int depth = 0;
		while (!dfs(0, depth)) depth ++ ;
		cout << "Case " << tt ++ << ": " << depth << "\n";
	}
	return 0;
}
```

---

## 作者：mcDinic (赞：1)

巨佬们用的各种神仙方法，如 IDA*，双向 bfs 等。

蒟蒻表示不会，写了个朴素的 bfs 过了，时间也还好啦。

在每次 bfs 时，枚举剪切段落的首和尾，以及要粘贴入的位置。但防止粘贴到原来位置，白搞，就特判一下。为了防止与之前状态重复，也给它记录好。这样就不会 TLE 啦。

虽然我的程序跑得不快，但容易实现，降低出错概率，可以让搜索初学者更好地食用。

## Code：

```cpp
#include<bits/stdc++.h>
const int mod=1e6+7;
int n,a[15],h,t,mubiao,T,hd[mod],nxt[mod];
struct node{
	int num,sum;
	int st[10];
}q[1000005];
bool ha(int x){
	int sk=(x+mod)%mod;
	for(int i=hd[sk];i!=-1;i=nxt[i])if(q[i].num==x)return 0;
	nxt[t+1]=hd[sk];
	hd[sk]=t+1;
	return 1;
}
int main(){
	while(~scanf("%d",&n)&&n){
		memset(hd,-1,sizeof(hd));
		memset(nxt,-1,sizeof(nxt));
		h=0;t=1;mubiao=0;T++;
		q[1].num=q[1].sum=0;
		for(int i=1;i<=n;i++)scanf("%d",&q[1].st[i]),q[1].num=q[1].num*10+q[1].st[i],mubiao=mubiao*10+i;
		if(q[1].num==mubiao){
			printf("Case %d: %d\n",T,0);
			continue;
		}
		hd[(q[1].num+mod)%mod]=1;
		int w=0;
		while(h<t){
			h++;
			//printf("%d %d %d\n",q[h].num,q[h].sum,mubiao);
			for(int i=1;i<=n;i++){
				for(int j=i;j<=n;j++){
					for(int k=0;k<=n;k++){
						if(k>=i-1&&k<=j)continue;
						int sqr=0;
						for(int l=1;l<=k;l++)if(l<i||l>j)sqr=sqr*10+q[h].st[l];
						for(int l=i;l<=j;l++)sqr=sqr*10+q[h].st[l];
						for(int l=k+1;l<=n;l++)if(l<i||l>j)sqr=sqr*10+q[h].st[l];
						if(ha(sqr)){
							if(sqr==mubiao){
								printf("Case %d: %d\n",T,q[h].sum+1);
								w=1;
								break;
							}							
							q[++t].num=sqr;							
							int op=n+1;
							while(sqr){
								q[t].st[--op]=sqr%10;
								sqr/=10;
							}
							q[t].sum=q[h].sum+1;
						}
					}
					if(w==1)break;
				}
				if(w==1)break; 
			}
			if(w==1)break;
		}
	}
	return 0;
}
```


---

## 作者：chenxinyang2006 (赞：1)

这题时限开了10s，暴力迭代加深明显可以过。既然题解中没有不带优化的，那我就来讲一下。

* 什么是迭代加深

迭代加深其实就是bfs和dfs的结合体，具有dfs的状态易储存，和bfs的“先搜到的一定是最优解”的优点。~~当然，速度没bfs快，也比dfs难写~~

* 怎么写迭代加深

最大深度从0开始每次递增1，对于每一个最大深度跑一遍dfs，如果搜索深度已经大于最大深度就返回，这样肯定可以确保“先搜到的肯定是最优解”，空间开销也小。

* 关于本题的hash

hash数组肯定是越小越好（每次都要重置），很容易发现，本题的所有状态其实都是1~n的一个排列，所以可以直接用康托展开求出是第几个排列。如果不会康托展开，请去做P5367 【模板】康托展开

code：
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
int ans,n,flag;
int now[15],arr[15],fact[15],has[370000];

int count(){//n^2的康托展开，有nlog（n），但是这里没必要
    int total = 1;
    for(int i = 1;i <= n;i++){
    	int cnt = 0;
    	for(int j = i - 1;j >= 1;j--){
    		if(now[j] < now[i]){
    			cnt++;
    		}
    	}
    	total += (now[i] - 1 - cnt) * fact[n - i];
    }
    return total;
}

void move(int i,int j,int k){//这部分请自己画图理解，move（i，j，k）表示将j~j+i-1移到k~k+i-1的位置（当然，原来在那里的需要移动）
    int tmp[15];
    for(int q = 1;q <= n;q++){
        tmp[q] = now[q];
    }
    if(j > k){
        for(int q = 0;q < i;q++){
            now[q + k] = now[q + j];
        }
        for(int q = 0;q < j - k;q++){
            now[q + k + i] = tmp[q + k];
        }
    }else{
        for(int q = i - 1;q >= 0;q--){
            now[q + k] = now[q + j];
        }
        for(int q = 0;q < k - j;q++){
            now[q + j] = tmp[q + i + j];
        }
    }  
}

void dfs(int x){
    if(flag){
        return;
    }
    if(x == ans + 1){
        return;
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n - i + 1;j++){
            for(int k = 1;k <= j - 1;k++){
                move(i,j,k);
                int tmp = count();
                if(has[tmp] > x){
                    if(tmp == 1){//递增是第一个排列
                        flag = 1;
                        return;
                    }
                    has[tmp] = x;
                    dfs(x + 1);
                }
                if(flag){
                    return;
                }
                move(i,k,j);                        
            }
        }
    }
}

int main(){
    fact[0] = 1;
    for(int i = 1;i <= 10;i++){
        fact[i] = fact[i - 1] * i;
    }
    for(int len = 1;len <= 20;len++){
        flag = 0;
        scanf("%d",&n);
        if(n == 0){
            break;
        }
        for(int i = 1;i <= n;i++){
            scanf("%d",&arr[i]);
        }
        ans = 0;
        for(int i = 1;i <= n;i++){
            now[i] = arr[i];
        }
        if(count() == 1){//有可能一开始就符合条件
            flag = 1;
        }
        while(!flag){
            memset(has,0x3f,sizeof(has));
            ans++;
            dfs(1);
            for(int i = 1;i <= n;i++){
                now[i] = arr[i];
            }
        }
        printf("Case %d: %d\n",len,ans);
    }
    
    return 0;
}
```


---

## 作者：charlieqi (赞：0)

由于数据范围只有 $2\le n \le 9$，所以考虑使用**迭代加深搜索**。
# Solution
迭代加深搜索的核心就是暴力枚举答案，深搜检查。

设 $f(n)=g(n)+h(n)$，考虑 $h(n)$ 如此设计：

每次移动 $a_i$ 最多会有 $3$ 个数是正确的，所以有等式：$f(n)=g(n)+d(n)\div 3$，由于 $d(n)$ 可能不是 $3$ 的倍数，所以我们将等式变形得：$3\times f(n)=3\times g(n)+h(n)$。
# $\text{Code}$
```cpp
#include<bits/stdc++.h>
const int N=12;
using namespace std;
int n,a[N],maxdep;
bool flag;
int check(){//有几个位置不同
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(a[i]!=a[i-1]+1){
			cnt++;
		}
	}
	return cnt;
}
void dfs(int x){
	int res=check();
	if(x*3+res>maxdep*3){//最多次数
		return;
	}
	if(!res){
		flag=true;
		return;
	}
	int b[N],c[N];
	memcpy(b,a,sizeof(a));
	for(int i=1;i<=n;i++){//变换
		if(a[i]!=a[i-1]+1){
			for(int j=i;j<=n;j++){
				if(j<n&&a[j+1]==a[j]+1){
					continue;
				}
				for(int k=i;k<=j;k++){
					c[k]=a[k];
				}
				for(int k=j+1;k<=n;k++){
					if(k<n&&a[k+1]==a[k]+1){
						continue;
					}
					for(int l=i,r=j+1;r<=n;r++,l++){
						a[l]=a[r];
					}
					for(int r=i+k-j,l=i;l<=j;l++,r++){
						a[r]=c[l];
					}
					dfs(x+1);
					if(flag){
						return;
					}
					memcpy(a,b,sizeof(a));
				}
			}
		}
	}
}
int main(){
	int test=0;
	while(cin>>n&&n){
		flag=false;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(maxdep=0;maxdep<=n;maxdep++){
			dfs(0);
			if(flag){//有答案了
				break;
			}
		}
		printf("Case %d: %d\n",++test,maxdep);
	}
	return 0;
}
```

---

## 作者：Hisy (赞：0)

## 分析
本题可以使用 IDA-star 来做。

首先考虑暴力 dfs，枚举起始点 $l$、中转点 $mid$ 和结束点 $r$，为交换 $[l,mid]$ 和 $[mid+1,r]$ 这两个区间。

可以用迭代加深来限制步数。

之后，考虑估价函数怎么定。设一个序列可以由四个序列拼接而成，即 $a=s_1+s_2+s_3+s_4$，那么交换 $s_1$ 和 $s_2$，最好的情况即本来都不正确，而交换后的 $s_1+s_3+s_2+s_4$ 是正确的。所以，一次最多让三个变成正确的。即 $s_1$ 的结尾和 $s_2$ 的开头冲突，与 $s_3$ 的开头不冲突、$s_3$ 的结尾与 $s_4$ 的开头冲突，与 $s_2$ 的开头不冲突以及 $s_2$ 的结尾与 $s_3$ 的开头冲突，与 $s_4$ 的开头不冲突。

所以，估价函数最多把三个转成正确的。设错误的有 $res$ 个，那么一共要转 $\lceil\frac{res}{3}\rceil$ 次。

在 dfs 的中的改变状态比较复杂，估价函数的推导较为棘手，其余的基本都能够轻松解决。是一道很好的搜索练习题。
## 代码
```cpp
#include<bits/stdc++.h>
#define MAXN 11
using namespace std;
int n,maxdep,a[MAXN];
bool f;
inline int goal(){
	int res=0;
	for(int i=2;i<=n;++i){
		if(a[i]!=a[i-1]+1){
			++res;
		}
	}
//	cout<<res<<endl;
	return res;
}
void iddfs(int dep){
	const int g=goal();
	if(g+3*dep>3*maxdep){
		return;
	}
	if(!g){
		f=true;
		return;
	}
	for(int l=1;l<n;++l){
		for(int mid=l;mid<n;++mid){
			for(int r=mid+1;r<=n;++r){
				int cpy[MAXN]={0};
				memcpy(cpy,a,sizeof(a));
//				for(int i=1;i<=n;++i){
//					cout<<cpy[i]<<" ";
//				}
//				cout<<endl;
				for(int i=l,j=mid+1;j<=r;++i,++j){
					a[i]=cpy[j]; 
				}
				for(int i=l,j=l+r-mid;i<=mid;++i,++j){
					a[j]=cpy[i];
				}
				iddfs(dep+1);
				if(f){
					return;
				}
				memcpy(a,cpy,sizeof(a));
			}
		}
	} 
}
int main(){
	for(int test=1;~scanf("%d",&n)&&n;++test){
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);
		}
		printf("Case %d: ",test);
		f=false;
		for(maxdep=0;;++maxdep){
			iddfs(0);
			if(f){
				printf("%d\n",maxdep);
				break;
			}
		}
	}
}
```

---

## 作者：dingshengyang (赞：0)

IDA* 大法吼啊！

~~如果还有问题，麻烦管理员大大详细说明一下~~

前置知识：

+ 迭代加深搜索 

+ 深搜

我主要讲讲 IDA* 。

所谓 IDA* ，无非是迭代加深搜索加上“科学”的剪枝——
一个玄学的东西：估价函数。

估价函数可以等于 0 ，但它一定要比实际情况 
**乐观**！！！

为什么呢……

比如，实际上，目标要 5 步。
估价函数：它要 7 步。

那么，我们在已经可以搜的时候，认为不能搜，那么迭代的步数就会白白增加 2 ！

回到本题。定义名词“断点”，也就是不符合连续递增的点。

```cpp
12|4|3|56
（“|”是“断点”）
```

一次操作，最多可以消除 3 次断点（把 3 移到 2 后面）！
现在：
```cpp
12||3||4||56
（“||”是被消除的“断点”）
```


估价函数：
```cpp
int f(){
	int cnt = 0;
	for(int i = 2;i <= n;i++)
		if(w[i] != w[i-1] + 1)
			cnt++;
	return (cnt + 2) / 3;
}
```

深搜:
```cpp
int dfs(int step){
	if(step + f() > depth)
		return 0;
	if(!f())
		return 1;
	for(int len = 1;len <= n;len++){
		for(int i = 1;i + len - 1 <= n;i++){
			int l = i,r = i + len - 1;
			for(int k = r + 1;k <= n;k++){
				int x,y;
				memcpy(cpy[step],w,sizeof(w));
				for(y = r + 1,x = i;y <= k;y++,x++)
					w[x] = cpy[step][y];
				for(y = i;y <= i + len - 1;y++,x++)
					w[x] = cpy[step][y];
				if(dfs(step + 1))
					return 1;
				memcpy(w,cpy[step],sizeof(w));
			}
		}
	}
	return 0;
}
```

满分代码（我知道你们只看这个）:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,depth,ti = 0;
int cpy[20][1000];
int w[100];
int f(){
	int cnt = 0;
	for(int i = 2;i <= n;i++)
		if(w[i] != w[i-1] + 1)
			cnt++;
	return (cnt + 2) / 3;
}
int dfs(int step){
	if(step + f() > depth)
		return 0;
	if(!f())
		return 1;
	for(int len = 1;len <= n;len++){
		for(int i = 1;i + len - 1 <= n;i++){
			int l = i,r = i + len - 1;
			for(int k = r + 1;k <= n;k++){
				int x,y;
				memcpy(cpy[step],w,sizeof(w));
				for(y = r + 1,x = i;y <= k;y++,x++)
					w[x] = cpy[step][y];
				for(y = i;y <= i + len - 1;y++,x++)
					w[x] = cpy[step][y];
				if(dfs(step + 1))
					return 1;
				memcpy(w,cpy[step],sizeof(w));
			}
		}
	}
	return 0;
}
main(){
	while(cin >> n,n){
		for(int i = 1;i <= n;i++)
			cin >> w[i];
		depth = 0;
		while(!dfs(0))
			depth++;
		printf("Case %d: %d\n",++ti,depth);
	}
	return 0;
}
```

---

## 作者：Sktic (赞：0)

本题利用迭代加深搜索，也是一道典型的状态空间搜索问题，状态就是 $1$~$n$ 的排列，初始状态是输入，终止状态是 $1,2,……n$ 。由于 $n≤9$  ,排列最多有 $9！=362880$ 个，但由于每个状态的后继状态比较多，因此仍有TLE的危险。

很显然，最坏的情况是需要 $n-1$ 次剪切，搜索层数不多，但每一层的状态数目又非常庞大，适宜使用 $IDA$。本题如果利用迭代加深搜索，可以发现做多只需要 8 步，关键在于如何有效地剪枝。考虑后继不正确的数字的个数 $h$，可以证明每次剪切时 $h$ 最多减少 3（因为一次剪切最多只会改变 $3$ 个数字的后继，若剪切后这 3 个数字的后继都正确，则h最多减少了 3），因此当$h>3$ 时剪枝即可

减枝分析：

当改变一个区间的位置，最多会改变 3 个数的位置的正确性。
比如 $1,2,3,4,5,6$ 序列，把 $2,3$ 移动到 $6$ 后面，那么 $1$ 的后面变成了 $5$, 而 $6$ 的后面变成了 $2$,而 $3$ 的后面变成 无，同样，设当前有四个数字 $a b c d$ ，如果把 $b$ 移到 $c$ 后面，则改变了 $a、b、c$ 三个数的后继，所以最多会改变3个数的位置的正确性。

也就是说，对于这道题，如果遍历到了一个深度，``(还能遍历的深度-当前深度)×3<不正确数字的个数``，那么就没有必要继续遍历了，因为往后就是全把这些数字改对了也无法达到理想状态。

知道这个之后时间复杂度的问题就得到解决了，只需要每次枚举该步的所有移动就可以了。

搜索：截取 $[i, j]$ 插入剩余序列的第 $k$ 个数字前

献上AC代码
```
#include <bits/stdc++.h>

using namespace std;
const int maxn = 10;

int n, Case=0;
int a[maxn];

int is_sort()
{
  int res = 0;
  for(int i = 0; i < n-1; i++) if(a[i]+1 != a[i+1]) res++;
  if(a[n-1] != n) res++;
  return res;
}

bool dfs(int maxd,int d)
{
  int h = is_sort();
  if(h == 0) return true;
  if(h > (maxd-d)*3) return false;

  int b[maxn],old[maxn];
  memcpy(old,a,sizeof(old));
  for(int i = 0; i < n; i++)
   for(int j = i; j < n; j++)
    {
      int tot = 0;
      for(int k = 0; k < i; k++) b[tot++] = old[k];
      for(int k = j+1; k < n; k++) b[tot++] = old[k];
      for(int k = 0; k <= tot; k++)
      {
        int tot1 = 0;
        for(int v = 0; v < k; v++) a[tot1++] = b[v];
        for(int v = i; v <= j; v++) a[tot1++] = old[v];
        for(int v = k; v < tot; v++) a[tot1++] = b[v];
        if(dfs(maxd,d+1)) return true;
      }
    }
    return false;
}

int solve()
{
  for(int i = 1; i < n-1; i++)
    if(dfs(i,0)) return i;
  return n-1;
}

int main()
{
  while(scanf("%d",&n) && n)
  {
    for(int i = 0; i < n; i++) scanf("%d",&a[i]);
    if(is_sort() == 0) {printf("Case %d: %d\n",++Case,0);continue;}
    printf("Case %d: %d\n",++Case,solve());
  }
  return 0;
}
```

---


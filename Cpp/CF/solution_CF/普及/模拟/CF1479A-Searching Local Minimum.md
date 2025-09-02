# Searching Local Minimum

## 题目描述

This is an interactive problem.

Homer likes arrays a lot and he wants to play a game with you.

Homer has hidden from you a permutation $ a_1, a_2, \dots, a_n $ of integers $ 1 $ to $ n $ . You are asked to find any index $ k $ ( $ 1 \leq k \leq n $ ) which is a local minimum.

For an array $ a_1, a_2, \dots, a_n $ , an index $ i $ ( $ 1 \leq i \leq n $ ) is said to be a local minimum if $ a_i < \min\{a_{i-1},a_{i+1}\} $ , where $ a_0 = a_{n+1} = +\infty $ . An array is said to be a permutation of integers $ 1 $ to $ n $ , if it contains all integers from $ 1 $ to $ n $ exactly once.

Initially, you are only given the value of $ n $ without any other information about this permutation.

At each interactive step, you are allowed to choose any $ i $ ( $ 1 \leq i \leq n $ ) and make a query with it. As a response, you will be given the value of $ a_i $ .

You are asked to find any index $ k $ which is a local minimum after at most $ 100 $ queries.

## 说明/提示

In the example, the first line contains an integer $ 5 $ indicating that the length of the array is $ n = 5 $ .

The example makes five "?" queries, after which we conclude that the array is $ a = [3,2,1,4,5] $ and $ k = 3 $ is local minimum.

## 样例 #1

### 输入

```
5
3
2
1
4
5```

### 输出

```
? 1
? 2
? 3
? 4
? 5
! 3```

# 题解

## 作者：Cutest_Junior (赞：10)

## 题解 CF1479A 【Searching Local Minimum】

### 题意

+ $a_1,a_2,\dots,a_n$ 是长度为 $n$ 的排列，$a_0=a_{n+1}=\inf$。
+ 每次可以询问一个位置 $i$，将得到 $a_i$ 的值，最多能询问 $100$ 次。
+ 求一个整数 $k$，使 $a_{k-1}>a_k,a_{k+1}>a_k$，以下简称“条件”。
+ $n\le10^5$。

### 做法

首先证明一个结论。

若 $l,r$ 满足：
1. $a_{l-1}>a_l$，$a_{r+1}>a_r$；
2. $a_l,a_{l+1},\dots,a_r$ 互不相同。

则一定有一个满足题目条件的 $k$ 会出现在区间 $[l,r]$ 中，以下把这种区间称为“正确区间”。

反证法，假设任意 $l\le k\le r$ 都不满足条件。

因为 $a_{l-1}>a_l$，且 $l$ 不满足条件，且 $a_l\neq a_{l+1}$，则一定有 $a_l>a{l+1}$。

同理可得，$a_{l+1}>a_{l+2},a_{l+2}>a_{l+3},\dots,a_{r-1}>a_{r}$。

又因为 $a_{r+1}>a_r$，则 $r$ 满足条件，与假设不符。

---

知道这个结论能这么样呢？

我们发现 $[l=1,r=n]$ 就是一个正确区间。

我们可以每次二分出一个 $mid$，询问 $a_{mid},a_{mid+1}$ 的值。

若 $a_{mid}<a_{mid+1}$，我们发现 $[l,mid]$ 也是一个正确区间。

若 $a_{mid}=a_{mid+1}$，我们发现并不满足题目中的“排列”这个条件，可以去举报这个题。

若 $a_{mid}>a_{mid+1}$，我们发现 $[mid+1,r]$ 也是一个正确区间。

然后就可以快乐地二分啦。

$2\times log_2 10^5$ 连 $40$ 都不到，而题目中给了我们 $100$ 次机会，随便玩。

### 代码

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

const int N = 1e5 + 5;

int arr[N];

int main() {
	int n;
	scanf("%d", &n);
	int l = 1, r = n;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (arr[mid] == 0) {
			printf("? %d\n", mid);
			fflush(stdout);
			scanf("%d", &arr[mid]);
		}
		if (arr[mid + 1] == 0) {
			printf("? %d\n", mid + 1);
			fflush(stdout);
			scanf("%d", &arr[mid + 1]);
		}
		if (arr[mid] < arr[mid + 1]) {
			r = mid;
		}
		else {
			l = mid + 1;
		}
	}
	printf("! %d\n", l);
	cout << endl;
}
```

---

## 作者：CSP_Sept (赞：1)

**CF1480** Codeforces Round #700 Sol [A](/blog/supervise/solution-cf1480a) / [B](/blog/supervise/solution-cf1480b) / C

### 背景

C fst 选手前来玩耍（

### 分析

考虑二分。

每次询问到 $m=\dfrac{l+r}2$ 时，询问 $m-1,m,m+1$（注意判断边界），获得三个值 $a,b,c$。

- 若 $b<\min(a,c)$，则输出 $m$。
- 若 $a>b,b>c$，则 $[r+1,n]$ 中必然有答案。
- 否则 $[1,l-1]$ 中必然有答案。

**注意判断边界。** ~~我就是因为这个 fst 的~~

### 代码

[$\text{Link}$](https://codeforces.com/contest/1480/submission/107283614)

---

## 作者：Diaоsi (赞：1)

**二分**

首先考虑一种特殊情况：

![1](https://cdn.luogu.com.cn/upload/image_hosting/h4u7u4ji.png)

显然这种情况是可以二分的，设中点为 $\text{mid}$ ，每次询问 $\text{mid}-1,\text{mid},\text{mid+1}$ 并判断是否满足 $\text{mid}-1 < \text{mid}<\text{mid}+1$ ，满足的话收敛右边界，否则收敛左边界，就能正确查找到答案。

对于任意一个排列，都可以看成若干个上面那种排列拼在一起，根据直觉，最后二分区间一定回收敛到一个形如上面排列的区间，所以直接二分就行。

同时对于每次二分的 $\text{mid}$ ，特判一下该点是否满足要求，若满足直接输出答案。

有一个小小的常数优化：记录下每次提问的结果，当出现重复提问时直接调用就行。

注意不要询问 $0$ 和 $n+1$ ，考场上我就因为这个 fst 了。

既然你能找到这题，我相信你能瞬间做出来的。

$Code:$

```cpp
#include<bits/stdc++.h>
typedef long long LL;
typedef long double LD;
using namespace std;
const LL N=100010,M=1000010,INF=0x3f3f3f3f3f3f3f3f;
inline LL Max(LL x,LL y){return x>y?x:y;}
inline LL Min(LL x,LL y){return x<y?x:y;}
inline void Swap(LL &x,LL &y){x^=y^=x^=y;}
LL n,ans,a[N];
inline LL read(){
	char c=getchar();LL x=0,f=1;
	while(c<'0'||'9'<c){if(x=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
LL check1(LL i){
	LL a1,a2,a3;
	if(a[i])a1=a[i];
	else{
		std::cout<<"? "<<i<<std::endl;
		std::cin>>a1;a[i]=a1;
	}
	if(a[i-1])a2=a[i-1];
	else{
		std::cout<<"? "<<i-1<<std::endl;
		std::cin>>a2;a[i-1]=a2;
	}
	if(a[i+1])a3=a[i+1];
	else{
		std::cout<<"? "<<i+1<<std::endl;
		std::cin>>a3;a[i+1]=a3;
	}
	return a2<a1&&a1<a3;
}
LL check2(LL i){
	LL a1,a2,a3;
	if(a[i])a1=a[i];
	else{
		std::cout<<"? "<<i<<std::endl;
		std::cin>>a1;a[i]=a1;
	}
	if(a[i-1])a2=a[i-1];
	else{
		std::cout<<"? "<<i-1<<std::endl;
		std::cin>>a2;a[i-1]=a2;
	}
	if(a[i+1])a3=a[i+1];
	else{
		std::cout<<"? "<<i+1<<std::endl;
		std::cin>>a3;a[i+1]=a3;
	}
	return a1<Min(a2,a3);
}
int main(){
	n=read();
	a[0]=a[n+1]=INF;
	LL l=1,r=n;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check2(mid)){ans=mid;break;}
		if(check1(mid))r=(ans=mid)-1;
		else l=mid+1;
	}
	std::cout<<"! "<<ans<<endl;
	return 0;
}
```


---

## 作者：Werner_Yin (赞：1)

## Problem

[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/CF1480-solution.html)

[传送门CF1480C CF1479A](http://codeforces.com/problemset/problem/1479/A)

交互题，给你一个长度为 $n$ （$\leq 10^5$）的序列 $A$，你每次可以问一个位置的值，找出一个位置 $i$ , 使得 $A[i]$ < $\min{A[i-1],A[i+1]}$ ,($A[0],A[n+1] = \inf$) , 你最多可以问 $100$ 次。

## Sol

先特判两端，然后考虑二分。

如果一个 $mid$ 不行，一定是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/wtpd20va.png)

或者：

![](https://cdn.luogu.com.cn/upload/image_hosting/m1ou3k3f.png)

情况一，$[l,mid-1]$ 一定有答案，情况二，$[mid+1,r]$ 一定有答案。

二分就完了：

```cpp
#define in read()

const int N = 1e5+10;

int a[N],n;

void Find(int x){printf("! %d\n",x);fflush(stdout);exit(0);}

void query(int x){//记忆化
	if(a[x]) return;
	printf("? %d\n",x);fflush(stdout);
	a[x] = in;
}

bool able(int x){//check
	query(x); query(x-1); query(x+1);
	if(a[x] < min(a[x-1],a[x+1])) return 1;
	return 0;
}

int main(){
	n = in; a[0] = N+1,a[n+1] = N+1;
	int l = 1,r = n;
	if(able(l)) Find(l);
	if(able(r)) Find(r);
	while(l <= r){
		int mid = l+r>>1;
		if(able(mid)) Find(mid);
		int lm = a[mid-1],rm = a[mid+1];
		if(lm < rm) r = mid-1;
		else l = mid+1;
	}
	Find(l);
	return 0;
}
```

---

## 作者：Meickol (赞：0)

一道不错的二分贪心交互题。

### 思路

我们要找到一个下标 $i\ (1\leq i \leq n)$ 满足 $a_i < \min\{a_{i-1},a_{i+1}\}$，不难发现这个局部图像呈现 `∨` 形。

直接给出做法：二分时结合贪心，在每轮中将 $mid$ 与 $mid+1$ 进行比较，然后将二分边界更新为较小的那个位置。这样最终找到的一定是局部内符合条件的谷底点，可以作为答案。



### 正确性分析


因为这题给定的数组为 $1 \sim n$ 的排列，保证不会出现两个相同的数字。

那么对于此序列任意情况下作出折线图都能保证整个曲线的图像不可能出现水平和竖直的情况。

我们考虑下标 $[1,n]$ 内的折线图像，会发现无非就是 `\`、`/`、`∨`、`∧` 这四种中的某一种或是拼接情况。

若将下标 $[1,n]$ 绘制出折线图后，图中存在 `∨` 或`∧` 的折线图像（单一也好叠加也罢），我们必然可以在 $(1,n)$ 内找到一个点 $x$ 使得 $a_{x-1} \gt a_x$ 且 $a_x \lt a_{x+1}$。

若将下标 $[1,n]$ 绘制出的折线图为  `\` 或`/` 的单一折线图像，也是符合的，且在该情况下最终选取到的局部最低点恰好是全局最低点，而这两种图像的全局最低点一定是区间左端点或区间右端点。即我们一定会在下标 $1$ 或下标 $n$ 这两个点中选择到一个点 $x$ 使得 $a_{x-1} \gt a_x$ 且 $a_x \lt a_{x+1}$。又因为题目保证了 $a_0=a_{n+1}=+\infin$，最终选取的那个区间端点也一定是符合条件（若该点为 $x$，即该点的左右相邻点的值都比该点）。

换句话说，对于 $[0,n+1]$ 这段区间的折线图像，一定会存在先下降后上升的情况，我们只需要找到那个谷底点即可。

### 注意事项及代码

因为最初序列中的值都是未知的，为了避免重复询问，查询时可以加个记忆化，若该位置曾经询问过则不再询问。

```cpp
const int N=1e5+5;
int n;
int a[N];
int query(int x){
	if(a[x]) return a[x];
	cout<<"? "<<x<<endl;
	int y;
	cin>>y;
	return a[x]=y;
}
void solve(){
	cin>>n;
	int l=1,r=n;
	a[0]=a[n+1]=0x3f3f3f3f;
	while(l<r){
		int mid=(l+r)>>1;
		if(query(mid)<query(mid+1)) r=mid;
		else l=mid+1;
	}
	cout<<"! "<<l<<endl;
}
```

---

## 作者：ZLCT (赞：0)

# CF1479A Searching Local Minimum
一道有助于学习交互题写法的好题。
## 题意
给定一个长度为 $n$ 的排列 $a$，每次可以提问任意一个 $a_i$ 的值，需要求出一个 $i$ 满足 $a_i<\min(a_{i-1},a_{i+1})$。询问次数不超过 $100$。并且规定 $a_0=a_{n+1}=+\infty$。\
$n\le 10^5$。
### 无从下手？条件别漏
这个题非常关键的一点就在它给出的是一个排列，这有什么用呢？\
我们考虑任意 $i<j<k$，如果 $a_i>a_j<a_k$，那么 $[i,k]$ 至少会构成一个“山谷”，而一个山谷就是满足条件的一个答案。\
于是我们每次二分中间位置 $mid$，查询 $a_{mid-1},a_{mid}$，并且判断两个数的大小，哪个大就把它作为下一轮的边界（只要满足新的区间依然是山谷即可）。因为是个排列，所以不可能相等。\
因为每次都至少删去一半的区间，于是复杂度 $O(\log n)$。
### code
由于本题是交互题，所以写法以及解法细节自由度极高，具体实现尽情探索吧。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[112345];
bool flag;
signed main(){
    cin>>n;
    int l=0,r=n+1;
    a[0]=a[n+1]=0x3f3f3f3f;
    while(!flag){
        int mid=(l+r+1)>>1;
        if(!a[mid]){
            cout<<'?'<<' '<<mid<<'\n';
            cin>>a[mid];
        }
        if(!a[mid-1]){
            cout<<'?'<<' '<<mid-1<<'\n';
            cin>>a[mid-1];
        }
        if(a[mid-1]<a[mid])r=mid;
        else l=mid-1;
        if(l==r){
            cout<<'!'<<' '<<l<<'\n';
            flag=1;
        }
        if(r-l==2){
            cout<<"! "<<r-1<<'\n';
            flag=1;
        }
    }
}
```

---

## 作者：TPJX (赞：0)

### 题目分析
在解决这个问题时，我们采用的主要策略是二分搜索，这是一种在有序数据结构中查找特定元素的有效方法。本题虽然数组本身未知，但我们可以通过逐步缩小可能的搜索范围来寻找局部最小值。

我们从整个数组的范围开始，逐步缩小考虑的区间。每次通过询问中间位置的元素值，并与其相邻的元素进行比较，根据比较结果来判断局部最小值可能位于哪一侧。

- 如果中间元素是局部最小，直接返回结果。
  
- 如果中间元素比左边的元素大，则左侧可能包含局部最小，因此调整搜索区间为左半部分。
  
- 反之，如果中间元素比右边的元素大，则右侧可能包含局部最小，因此搜索区间调整为右半部分。
  
考虑到数组两端的特殊性，如果搜索区间缩小到数组的起始或结束位置，还需要额外判断这些位置是否为局部最小。

```cpp
#include <iostream>
using namespace std;

int q(int i) {
    cout << "? " << i << endl;
    int v;
    cin >> v;
    return v;
}

int main() {
    int n;
    cin >> n;
    int l = 1, r = n;
    if (n == 1) {
        cout << "! 1" << endl;
        return 0;
    }
    while (l < r) {
        int m = (l + r) / 2;
        int vm = q(m);
        if (m == 1) {
            int vm1 = q(m + 1);
            if (vm < vm1) {
                cout << "! 1" << endl;
                return 0;
            } else {
                l = m + 1;
                continue;
            }
        }
        if (m == n) {
            int vm1 = q(m - 1);
            if (vm < vm1) {
                cout << "! " << n << endl;
                return 0;
            } else {
                r = m - 1;
                continue;
            }
        }
        int vl = q(m - 1), vr = q(m + 1);
        if (vm < vl && vm < vr) {
            cout << "! " << m << endl;
            return 0;
        } 
        else if (vm > vl) r = m - 1;
        else l = m + 1;
    }
    cout << "! " << l << endl;
    return 0;
}
```

- 时间复杂度：$O(\log n)$，$n$ 为题面中的 $n$。
- 空间复杂度：$O(1)$，代码中，我们只使用了几个变量来存储索引和查询结果，与 $n$ 的规模无关。

---

## 作者：loser_seele (赞：0)

因为题目给的操作次数太多了，我得到了一个乱搞的解法。

首先判断两端是极值的情况以及 $ n \leq 100 $，这个可以直接暴力。

不难发现如果两端不是答案，而数组是排列，则中间一定存在一个 $ 1 $，因为两端是 $ 1 $ 则答案一定在两端，前面判断过了。

因为 $ 1 $ 是极小值，于是问题转化为在单谷函数里找最小值，这个可以直接三分解决，询问次数最大情况下大约 $ 30 $ 次不到，优于二分解法。可以通过。

[提交记录](https://codeforces.cc/contest/1479/submission/193124579)

---

## 作者：lightup37 (赞：0)

### CF1480C

### 题意

  **这是一道交互题.**

  有一个排列 $a_i$, 已知其长度 $n$. 你可以向交互库执行两种操作 ``query`` 和 ``submit``.

- 直接输出 ``? i`` 你将会得到正整数 $a_i (1\leq a_i\leq n)$. 你最多可以使用 100 次此操作.

- 直接输出 ``! i`` 你会将 $i$ 作为答案提交. 如果 $a_t \leq \min(a_{i-1}, a_{i+1})$, 则你会获得本测试点的所有分数. 特别的, 我们认为 $a_0 = a_{n+1} = +\infty$.

### 输入格式

  仅一行一个正整数 $n(1\leq n\leq 10^5)$, 表示排列的长度.

### 输出格式

  参见前文.

### 解法

  二分. 假设目前的区间是 $[l, r]$ 且有解且 $a_{l-1} > a_l$, $a_{r+1} > a_r$. 考虑 $a_{mid}$ 和 $a_{mid+1}$, 如果 $a_{mid} < a_{mid+1}$, 则我们断言 $[l, mid]$  区间内有解, 因为如果这个区间里没有解, 则 $a_{mid-1} < a_{mid}$, 依次类推... 所以 $a_l < a_{l+1}$, 而这样, $[l, mid]$ 区间内有解 $l$ 且合法($a_{l-1}>a_l, a_{mid+1}>a_{mid}$). 同理, 如果 $a_{mid} > a_{mid+1}$, 则 $[mid+1, r]$ 区间必定合法.

### 代码

```cpp
#include<bits/stdc++.h>
#define f(i,x,y) for(int i=x, i##end=y; i<=i##end; ++i)
#define d(i,x,y) for(int i=y, i##end=x; i>=i##end; --i)
#define ll long long
char ch;
int rd() {
  int f=1, x=0; ch=getchar();
  while(!isdigit(ch)) { f=((ch=='-')?-1:f); ch=getchar(); }
  while(isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
  return x*f;
}
void rd(int& x) { x=rd(); }
using namespace std;
#define _ 1000005
int a[_], n;
int min(int x, int y) {
	return x>y ? y : x;
}
int query(int T) {
	if(a[T]) return a[T];
	printf("? %d\n", T); fflush(stdout);
	a[T] = rd(); return a[T];
}
int main() {
  srand(time(0)); rd(n); int l, r;
	a[0]=a[n+1]=n+1; l=1; r=n;
	while(l<r) {
		int m = (l+r) >> 1;
		query(m); query(m + 1);
		if(query(m) < query(m+1)) r=m;
		else l = m+1;
	}
	printf("! %d\n", l);
  return 0;
}
```

---


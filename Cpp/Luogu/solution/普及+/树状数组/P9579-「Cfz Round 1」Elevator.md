# 「Cfz Round 1」Elevator

## 题目背景

电梯是一个可以让人充分思考的空间。

## 题目描述

给定两个长度为 $n$ 的数组 $a,b$。我们称序列 $p$ 是满足条件的，设 $p$ 的长度为 $m$，当且仅当：

- $p_1=1$；  
- 对于所有的 $1\le i<m$，都有 $|p_i-p_{i+1}|=1$；  
- 对于所有的 $1\le k\le n$，都存在一个有序数对 $(i,j)$，满足 $1 \le i < j \le m$ 且 $p_i=a_k$，$p_j=b_k$。

你需要输出所有满足条件的序列 $p$ 中，$p$ 的长度的最小值。

## 说明/提示

#### 【样例解释 #1】

序列 $p$ 的长度的最小值为 $7$，此时的序列 $p$ 为 $\{1,2,3,2,3,4,5\}$。

#### 【数据范围】

对于所有数据，$1 \le n \le 5\times10^5$，$1 \le a_i,b_i \le 10^9$，保证 $a_i \neq b_i$。

**本题采用捆绑测试。**

|子任务编号|分值|$n \le$|特殊性质|
|:---:|:---:|:---:|:---:|
|$1$|$9$|$1$|无|
|$2$|$9$|$5\times10^5$|保证 $a_i < b_i$|
|$3$|$21$|$5\times10^5$|数据随机生成|
|$4$|$27$|$2000$|无|
|$5$|$34$|$5\times10^5$|无|

## 样例 #1

### 输入

```
2
3 2
2 5```

### 输出

```
7```

## 样例 #2

### 输入

```
4
4 7
10 8
9 11
4 2```

### 输出

```
18```

# 题解

## 作者：Coffee_zzz (赞：31)

另一种不是 dp 的做法。

以下把 $a_i,b_i$ 看成一个区间。

首先记录数组 $a$ 和数组 $b$ 中的最大值 $m$，发现 $a\lt b$ 的区间没有用，因为移动到 $m$ 的过程中一定会满足这些要求，那我们就不管 $a \lt b$ 的区间，把所有满足 $a \gt b$ 的区间以 $a_i$ 为第一关键字从大到小排序。

我们首先把相交的区间都合并，然后枚举每个区间 $i$，下标大于 $i$ 的区间都用先走到 $a_i$ 再走回 $b_i$ 最后再走到 $a_i$ 的方法满足，下标小于等于 $i$ 的区间都从 $m$ 走回来，最后给所有可能的答案取 $\min$ 即可。

---

## 作者：Komomo (赞：22)

## 题目描述

给定两个长度为 $n$ 的数组 $a,b$。我们称序列 $\{p\}$ 是满足条件的，设 $\{p\}$ 的长度为 $m$，当且仅当：

- $p_1=1$；  
- 对于所有的 $1\le i<m$，都有 $|p_i-p_{i+1}|=1$；  
- 对于所有的 $1\le k\le n$，都存在一个有序数对 $(i,j)$，满足 $1 \le i < j \le m$ 且 $p_i=a_k$，$p_j=b_k$。

你需要输出所有满足条件的序列 $\{p\}$ 中，$\{p\}$ 的长度的最小值。

## 数据范围

对于所有数据，$1 \le n \le 5\times10^5$，$1 \le a_i,b_i \le 10^9$，保证 $a_i \neq b_i$。


## 题解

我们把每个 $a_i,b_i$ 看做一个“区间”：$[a_i,b_i]$，并令 $a_i<b_i$ 为「上升区间」，$a_i>b_i$ 为「下降区间」。

我们发现对于上升的部分是必要的，而下降区间可以插在上升序列中间，也可以直接跟在上升序列后，于是我们考虑如何插入下降区间。

拿样例 2 来讲，首先我们构造一个最简单的方案：

![pPNcddf.png](https://cdn.luogu.com.cn/upload/image_hosting/p11nej8c.png)

此时序列长度为 $20$，显然不是最优，手模一下发现，样例方案是这样的：

![pPNcwo8.png](https://cdn.luogu.com.cn/upload/image_hosting/f13xvhqp.png)

我们先考虑将一个下降区间 $[a_i,b_i]$ 插入前面的代价。令下降区间集合为 $S$，去除 $[a_i,b_i]$ 的区间集合为 $S'$。对于前面需要新增 $2(a_i-b_i)$ 个元素，后面减少的元素为 $\min\limits_{[l,r]\in S'} r-\min\limits_{[l,r]\in S} r$，由此我们可以看出，单独去掉一个区间，若要对原答案**可能**有负影响，向前插入的 $[a_i,b_i]$ 必然是 $b_i$ 最大的下降区间，由此我们可以得出，向前插入的区间一定是将下降区间按 $r$ **从小到大排序**的一个**前缀**。

---

已经知道了插入的区间形式，并已经求出了单个区间向前插入的代价，考虑多个区间。

先去掉下降区间中互相包含者，因为如果 $[a_i,b_i]$ 包含了 $[a_j,b_j]$，如果我把 $[a_i,b_i]$ 插入了上升序列中，显然一定会包含如 $[a_i,a_i-1,\dots,b_i]$ 的子段，此时 $[a_j,b_j]$ 也满足，所以我们只要考虑 $[a_i,b_i]$ 即可。

再考虑相交的区间 $[a_i,b_i]$ 和 $[a_j,b_j]$，满足 $a_i>b_i\ge a_j>b_j$。我们考虑按照前面插入方法的代价：

![pPN2mE6.png](https://cdn.luogu.com.cn/upload/image_hosting/e4m0k9co.png)

此时插入两个下降区间的代价为 $12$，但我们发现黄色点其实是浪费的，可以合并：

![pPN2ZHx.png](https://cdn.luogu.com.cn/upload/image_hosting/kh4twrtn.png)

此时代价只有 $10$ 了，所以合并相交区间是显然更优的。

最后下降区间都是两两无交的。于是我们只要按照 $b_i$ 自小到大排序，取每个前缀的最小值即可，排序之后，$\min\limits_{[l,r]\in S'} r$ 的值即为该前缀后面一个区间的 $b_i$，而 $\min\limits_{[l,r]\in S} r$ 我们可以直接预处理，时间复杂度 $\mathcal O(n\log n)$。

```cpp
int n, L, ans, up, lo = 2e9;
struct Node { int l, r; } p[maxn], r[maxn];
//p 为下降区间，r 为去除包含区间和有交区间

bool cmp(Node a, Node b) { return a.r < b.r || a.r == b.r && a.l > b.l; } // 按照右端点排序，为了判断包含方便，左端点也要排序 

signed main() {
	
	n = read(); 
	for (int i = 1; i <= n; i ++) {
	    int l = read(), r = read(); up = max({up, l, r});
		if (l > r) lo = min(lo, r), p[++ L] = Node {l, r};
        // lo 为原集合的最小 r
	}
	
	if (lo == 2e9) return cout << up, 0; // 没有下降区间 
	ans = up + (up - lo), sort(p + 1, p + L + 1, cmp);
	
	int tmp = L; r[L = 1] = p[1]; 
	for (int i = 2; i <= tmp; i ++)
		if (!(r[L].r <= p[i].r && p[i].l <= r[L].l)) { // 是否已被前面区间包含 
			if (r[L].l >= p[i].r && p[i].r >= r[L].r) r[L].l = p[i].l; // 是否相交，若相交则合并 
			else r[++ L] = p[i]; // 否则直接加入区间 
		}
	
	int del = 0, sum = 0; // sum 表示代价前缀和，del 表示新答案和原答案的差 
	r[L + 1].r = up; // 为了方便处理这里设 r[L + 1].r 为上升区间的最大 r 
	for (int i = 1; i <= L; i ++) { 
		sum += 2 * (r[i].l - r[i].r);
		del = min((lo - r[i + 1].r) + sum, del);
	}
	
	cout << ans + del << endl;
	return 0;
}
```

---

## 作者：佬头 (赞：11)

## Description

给定两个长度为 $n$ 的数组 $a,b$。我们称序列 $\{p\}$ 是满足条件的，设 $\{p\}$ 的长度为 $m$，当且仅当：

- $p_1=1$；  
- 对于所有的 $1\le i\le m$，都有 $|p_i-p_{i+1}|=1$；  
- 对于所有的 $1\le k\le n$，都存在一个有序数对 $(i,j)$，满足 $1\le i\lt j\le m$ 且 $p_i=a_k$，$p_j=b_k$。

你需要输出所有满足条件的序列 $\{p\}$ 中，$\{p\}$ 的长度的[**最小值**](https://www.luogu.com.cn/problem/P9579)。

## Solution
由前两个条件可知 $\{p\}$ 的第一个元素是 $1$ 且之后每个元素与前一个元素的差的绝对值为 $1$。为了使构造的序列一定满足条件且长度最小，则序列中的最大值就是数组 $a$ 与数组 $b$ 的最大值中的较大值，这里计为 $x$。可以先构造一个这样的上升序列，那么对于所有 $a_k\lt b_k$ 的情况就被解决了。

对于第二个样例，则可以先构造一个这样的序列。

![](https://cdn.luogu.com.cn/upload/image_hosting/1jtxf37t.png)

接下来的步骤就是将 $a_k\gt b_k$ 的情况放入这个序列，我们可以先对所有这种情况按照 $a$ 降序排列，对于同一个 $a$，我们直接选取 $b$ 最小的情况放，因为 $b$ 若不是最小则一定被最小的情况包含。然后开始放入，接下来以将 `5 3`（红色）和 `4 2`（蓝紫色）先后放入最大值为 $7$ 的序列为例，显然有三种情况：
- **接**在整个序列的尾部，设尾部降序列的最小值为 $y$，则总代价为 $x-y$。

![](https://cdn.luogu.com.cn/upload/image_hosting/t8x8i0tx.png)
- 直接**插**在 $a_k$ 的后面，代价为 $(a_k-b_k)\times2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/vr9th24o.png)
- 找出前几次**插入**形成的降序列的最小值 $y$（若存在），**插**在 $y$ 的后面，代价为 $(y-b_k)\times2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/xpgh5bzr.png)

显然第一种情况和后两种情况是独立的，我们对第一种情况和后两种情况同时计算代价。对于后两种情况，插入代价可以简化为 $(\min(a_k,y)-b_k)\times2$，总代价为 $ans+(\min(a_k,y)-b_k)\times2$。每放入一对 $a,b$ 我们便将当前总代价 $ans$ 取为第一种情况的总代价和后两种情况的总代价的最小值。

则最终答案为 $ans+x$。时间复杂度 $\mathcal{O}(n\log n)$。

## Code
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 500005;
int n, cnt, maxx, minn, ans;
pair <int, int> s[N];
int read(){
	int x = 0;
	char a = getchar();
	while(a < '0' || '9' < a) a = getchar();
	while('0' <= a && a <= '9') x = (x << 1) + (x << 3) + (a ^ 48), a = getchar();
	return x;
}
void write(int x){
	if(x > 9) write(x / 10);
	putchar(x % 10 | 48);
}
int main(){
	n = read();
	for(int i = 1; i <= n; ++ i){
		s[++ cnt].first = read(), s[cnt].second = read();
		if(s[cnt].first > maxx) maxx = s[cnt].first;
		if(s[cnt].second > maxx) maxx = s[cnt].second;
		if(s[cnt].first < s[cnt].second) cnt --;
	}
	minn = maxx;
	sort(s + 1, s + 1 + cnt);
	for(int i = cnt; i >= 1; -- i)
		if(s[i].first != s[i - 1].first && minn > s[i].second){
			ans += (min(minn, s[i].first) - s[i].second) << 1;
			minn = s[i].second;
			if(ans > maxx - minn) ans = maxx - minn;
		}
	write(maxx + ans);
	return 0;
}
```


---

## 作者：Xy_top (赞：4)

一种全程只需要排序，不需要动态规划的解法。

（由于我没买讲评，不知道是不是官方解法）

简化题意，$n$ 个限制条件给你 $x$ $y$ 就是让你保证至少一个 $x$ 的出现位置在 $y$ 的出现位置前面。

记 $maxr$ 为所有限制中 $x$ $y$ 的最大值，答案至少有 $maxr$，不然无法从 $1$ 增加到 $maxr$。

如果 $x<y$，增加的过程中，就能找到 $x$ 的位置在 $y$ 的位置前面了，要解决的是 $x>y$ 的情况。

先来看一种简单的，$1$ $5$，$2$ $1$。

最短的序列为 $1$ $2$ $1$ $2$ $3$ $4$ $5$ ，由此得出 $x>y$ 的解决方案。在 $1$ 自增到 $x$ 时，回退到 $y$，然后再回来。

然而真的是这样的吗，再来看一组，$7$ $3$。

最短序列为 $1$ $2$ $3$ $4$ $5$ $6$ $7$ $6$ $5$ $4$ $3$，所以，如果 $x=maxr$，回退后就不用回来了。

但事实仍然不是这样，比如 $7$ $3$，$5$ $1$。

此时最短的为 $1$ $2$ $3$ $4$ $5$ $6$ $7$ $6$ $5$ $4$ $3$ $2$ $1$，为什么呢？因为单独把它们两个回退不如一起回退，这两个是有交的，一起回退会更优。

还是错的，还有最后一步，样例 $2$，如果 $x<maxr$，也可以加到 $maxr$ 后再回退，这样就不用再自增回来可能会短些。

口胡一分钟，代码十小时，这里我用堆写的，先把有交集的合并完再按照 $y$ 排序，然后交给 $maxr$ 处理的（就是回退完不回来的）一定是一段后缀，再跑一遍，同时维护不给 $maxr$ 的答案即可。

```cpp
#include<queue>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n,k,maxr,minl=1000000001;
int pre1[500005],pre2[500005];
priority_queue<int>q;
struct Node{int x,y;}a[500005],c[500005];
bool cmp(Node n1,Node n2){return n1.x<n2.x||n1.x==n2.x&&n1.y>n2.y;}
bool cmp_(Node n1,Node n2){return n1.y<n2.y;}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i].x,&a[i].y);
		maxr=max(maxr,max(a[i].x,a[i].y));
		if(a[i].x>a[i].y)minl=min(minl,a[i].x);
	}
	if(minl==1000000001){
		cout<<maxr;
		return 0;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(a[i].x<a[i].y)continue;
		if(q.empty())q.push(i);
		else{
			while(!q.empty()&&a[q.top()].x>=a[i].y){
				a[i].y=min(a[i].y,a[q.top()].y);
				q.pop();
			}
			q.push(i);
		}
	}
	while(!q.empty()){
		c[++k]=a[q.top()];
		q.pop();
	}
	sort(c+1,c+k+1,cmp_);
	int ans=20000000000,sum=0;
	for(int i=1;i<=k;i++){
		ans=min(ans,maxr+sum+(maxr-c[i].y));
		sum+=2*(c[i].x-c[i].y);
	}
	cout<<min(ans,maxr+sum);
	return 0;
}
```


---

## 作者：qzhwlzy (赞：2)

### 题目大意

[原题面](https://www.luogu.com.cn/problem/P9579)写得挺清楚了。

给定两个长度为 $n$ 的数组 $a$ 和 $b$。求序列 $p$ 的最小长度 $m$，满足：

- $p_1 = 1$；
- $\forall i\in[1,m),|p_i - p_{i-1}| = 1$；
- $\forall i\in[1,n],\exists j,k$ 使得 $a_i = p_j,b_i = p_k$。

### 思路

首先，我们发现，$p$ 中元素的最大值 $mx$ 一定是 $a,b$ 中的最大值，所以我们至少需要 $mx$ 的长度来走到 $p_{mx}=mx$。此时，所有 $a_i\le b_i$ 的区间已经被满足了。

接下来我们考虑 $a_i > b_i$ 的区间。发现满足这些区间有两种可能：一种是在到 $mx$ 以后再走下来到 $b_i$，或者是在向上走到 $a_i$ 的途中向下到 $b_i$ 再折回到 $a_i$。我们发现了以下两个性质：

1. 若两个区间有交，那么合并它们不会使答案更劣。  
假设两个区间 $[x_1,y_1],[x_2,y_2]$（$x_1\ge x_2\ge y_1\ge y_2$）有交，则 $x_1\rightarrow y_1\rightarrow x_2\rightarrow y_2$ 的步数肯定大于 $x_1\rightarrow y_2$。  
于是我们可以把能合并的合并。

2. 从 $mx$ 走下来的一定是按照区间右端点从小到大的一段后缀。  
不难证明，否则前面肯定浪费了若干步。

所以，我们枚举哪一段后缀是从 $mx$ 走下来的即可。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 500005
#define int long long
using namespace std;
int n,mmax,l,r,cnt=0,ccnt=0,ans=0,res; struct node{int l,r;}a[maxn],b[maxn];
bool cmpl(node aa,node bb){return aa.l<bb.l;} bool cmpr(node aa,node bb){return aa.r<bb.r;}
signed main(){
	scanf("%lld",&n); for(int i=1;i<=n;i++){
		scanf("%lld%lld",&l,&r); mmax=max(mmax,max(l,r));
		if(l>r) b[++ccnt]=(node){r,l};
	} if(ccnt==0){printf("%lld",mmax); return 0;}
	sort(b+1,b+1+ccnt,cmpl); int pos;
	for(int i=1;i<=ccnt;i=pos+1){
		pos=i; while(pos<ccnt&&b[pos+1].l<=b[i].r) pos++,b[i].r=max(b[i].r,b[pos].r);
		a[++cnt]=(node){b[i].r,b[i].l};
	} sort(a+1,a+1+cnt,cmpr);
	// for(int i=1;i<=cnt;i++) printf("[%d,%d]\n",a[i].l,a[i].r);
	ans=res=2*mmax-a[1].r; a[cnt+1].r=mmax; for(int i=1;i<=cnt;i++){
		res=res-(a[i+1].r-a[i].r)+(a[i].l-a[i].r)*2;
		ans=min(ans,res);
	} printf("%lld",ans);
	return 0;
}
```

---

## 作者：zymooll (赞：1)

### 题目大意

给定两个长度为 $n$ 的数组 $a,b$。我们称序列 $\{p\}$ 是满足条件的，设 $\{p\}$ 的长度为 $m$，当且仅当： 

- $p_1=1$； 
- 对于所有的 $1\le i<m$，都有 $|p_i-p_{i+1}|=1$； 
- 对于所有的 $1\le k\le n$，都存在一个有序数对 $(i,j)$，满足 $1 \le i < j \le m$ 且 $p_i=a_k$，$p_j=b_k$。 

你需要输出所有满足条件的序列 $\{p\}$ 中，$\{p\}$ 的长度的最小值。

### 主要思路

直接考虑将下降线段按 $b$ 从小往大排序后枚举，初始所有下降线段都在最高点右侧，对于每次操作，我们尝试把选定下降线段放在最高点左侧，令 $maxn$ 是所有线段 $a$,$b$ 的最大值，$p$ 为当前的上升线段代价加上将已放在最高点左侧的下降线段代价之和，初始为 $maxn$（即从 $1$ 到上升到最高点），转移有：

$$\left\{\begin{matrix} b_i > a_{prev} \ \ \ \ p \to p + 2 \times (a_i - b_i) \\ a_i > a_{prev} \wedge b_i \le a_{prev} \ \ \ \ p \to p + 2 \times (a_i - a_{prev}) \\ a_i \le a_{prev} \wedge b_i \le a_{prev} \ \ \ \ a_i \gets a_{prev} \end{matrix}\right.$$

其中 $a_{prev}$ 指上一个线段的 $a$，特别的，当选定的下降线段为第一个时，只考虑 $p \to p + 2 \times (a_i - b_i)$。

然后更新答案 $ans \gets \min(ans,p + (maxn - b_{next}))$，其中 $b_{next}$ 是下一个线段的 $b$，特别的，当选定的下降线段为最后一个时，$b_{next}$ 取 $maxn$。最后输出 $ans$ 即可。

### 思路解释

感觉思路有点跳，解释解释。

首先我们考虑什么时候可能是一个可能解，首先 $1$ 到 $maxn$ 这一段是省不了的，所以上升线段可以直接插入，所以我们只需要考虑下降线段，首先我们要将所有下降线段按 $b$ 从小往大排序，初始假定都在最高点右侧，所以有：

![](https://cdn.luogu.com.cn/upload/image_hosting/slbxzf0q.png?x-oss-process=image/resize,m_lfit,h_300)

可以发现目前的代价为 $maxn + (maxn - minn)$，直接输出这个可以拿到 39pts，考虑优化这个代价，可以发现，我们的优化只能对 $minn$ 下手，考虑把当前构成 $minn$ 的下降线段（也就是 $b_i$ 最小的，这也是为什么要排序），如何优化呢，我们发现，将线段插入到最高点左侧是一个办法，因为左侧天然满足 $minn$ 存在的条件，插入后如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/0kr6fh8i.png?x-oss-process=image/resize,m_lfit,h_300)

可以发现，这样就可以把原先的 $minn$ 变大，你可能已经想到转移了 $ans \to ans - (b_{next} - b_{i}) + 2 \times (a_i - b_i)$，对吗？如对！

为什么呢？因为可能下降线段中有重叠线段，而重叠部分是可以被重复利用的，所以我们可以考虑下面三种情况（附图）：

![](https://cdn.luogu.com.cn/upload/image_hosting/3ywn1gmb.png?x-oss-process=image/resize,m_lfit,h_300)

- 情况一，当前区间同之前处理过的区间交集为空集（$b_i > a_{prev}$），直接处理 $p \to p + 2 \times (a_i - b_i)$
- 情况二，当前区间同之前处理过的区间交集不为空，但交集也不等于当前区间（$a_i > a_{prev} \wedge b_i \le a_{prev}$），处理没处理过的区间，$p \to p + 2 \times (a_i - a_{prev})$
- 情况三，当前区间同之前处理过的区间交集不为空，且交集等于当前区间（$a_i \le a_{prev} \wedge b_i \le a_{prev}$），继承之前处理过的区间大小（其实是偷懒），$a_i \gets a_{prev}$

注：$a_{prev}$ 是排序后下降线段组的上一个线段的 $a$；排序保证 $b_i \ge b_{prev}$，$p$ 为当前的上升线段代价加上将已放在最高点左侧的下降线段代价之和。

特别的，当我们枚举第一个下降线段的时候，我们只能考虑第一种情况（因为空集交任何集合都为空集）。

然后考虑如何更新答案，初始 $ans \gets maxn + (maxn - minn)$，即第一张图片的所示图片。

更新时，我们只需要考虑 $maxn$ 和目前的 $minn$ 的差值即可，而目前的 $minn$ 就是 $b_{next}$（排序后下降线段组的下一个线段的 $b$），所以有 $ans \gets \min(ans, p + (maxn - b_{next}))$，特别的，当我们枚举第一个下降线段的时候，我们取 $maxn - minn$ 为 0（因为右边已经没有线段了）。

### 参考代码

```cpp
// Author:zymooll
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, maxn, minn = INT_MAX;
struct ggb{
  int a, b;
  friend bool operator < (ggb aa, ggb bb){
    return aa.b < bb.b;
  }
};
vector<ggb>q;
int ans, pans;
signed main(){
  n = read();
  if(n == 1){
    int a = read(), b = read();
    if(a < b)print(b);
    else print(a + (a - b));
    return 0;
  }
  for(int i = 1; i <= n; i++){
    int a = read(), b = read();
    if(a < b)maxn = max(maxn, b);
    else{
      maxn = max(maxn, a), minn = min(minn, b);
      q.push_back({a,b});
    }
  }
  if(minn == INT_MAX){ print(maxn); return 0; }
  q.push_back({114514,maxn});
  sort(q.begin(), q.end());
  ans = maxn, pans = maxn + (maxn - minn);
  for(int i = 0; i < q.size() - 1; i++){
    int& a = q[i].a, & b = q[i].b, & rb = q[i + 1].b;
    if(i == 0){
      ans += 2 * (a - b);
    }
    else{
      int& fa = q[i - 1].a;
      if(b > fa)ans += 2 * (a - b);
      else if(a > fa)ans += 2 * (a - fa);
      else a = fa;
    }
    pans = min(ans + (maxn - rb), pans);
  }
  print(min(pans, ans));
  return 0;
}
```

注：去掉了快读快写。

### 后记

参考时间复杂度 $O(n \log n)$.

---

## 作者：sail_with_pleasure (赞：1)

我们把这道题放到一个平面直角坐标系上，其中横轴代表 $p$ 的下标，纵轴代表 $p_i$ 的值。由于 $|p_i-p_{i+1}|=1$，所以我们可以把序列 $p$ 看成一条折线。

我们首先想到的是画一道先上升后下降的折线，求出最高点和最低点就一定满足条件。

![](https://cdn.luogu.com.cn/upload/image_hosting/w5ycs96m.png)

那么为什么这样做不是最优的呢？

考虑如下的输入:

```
2
1 100
6 2
```

按照上述方法：

![](https://cdn.luogu.com.cn/upload/image_hosting/qhaxpx0k.png)

显然不如下图更优：

![](https://cdn.luogu.com.cn/upload/image_hosting/94so3hfa.png)

这是因为直线下降的过程中经过了太多的无意义点，所以我们不如直接走一个折线从 $6$ 折回到 $2$ 再折回到 $6$ 继续上升。

综上，对于某一个满足 $a_k>b_k$ 的点对，我们要么从最高点直接向下折，要么从某个需要折回的点（不一定是 $a_k$，可能是一个更往上的点）折到 $b_k$ 再向上升，最优解一定是这两种之一。而对于 $a_k<b_k$ 的点对,只要正常向上升就可以由 $a_k$ 直接到 $b_k$，只需要知道上升的最高点即可。

即最优解一定类似于下图的形状，且满足 $G_y>B_y,E_y>D_y$，否则从 $B$ 和 $D$ 向下折就显得很蠢：

![](https://cdn.luogu.com.cn/upload/image_hosting/xkrsewtv.png)

大概知道策略了之后我们考虑 dp，令 $f_{i,0}$ 和 $f_{i,1}$ 分别表示从某个较高的点下降再返回，和从最高点直接落到当前点两种方案。发现我们需要按照某种顺序 dp 才可以，所以我把所有点对按照 $\max(a_k,b_k)$ 从小到大排序然后从 $n$ 循环到 $1$（真的很蠢），从高处向低处转移，且在碰到 $a_k<b_k$ 的点对时可以直接跳过。

令 $la$ 表示上一个被转移的位置（因为会有被跳过的点对）则显然 $f_{i,1}=f_{la,1}+b_{la}-b_i$。

$f_{i,0}$ 的转移略难一些，分两种情况讨论，取一下最小值就能得到答案了：$f_{i,0}=\min(f_{la,1},f_{la,0})+(\min(b_{la},a_i)-b_i) \times 2$。

至于初始化的话预处理一下 $la$ 为最高点，$f_{la,0},f_{la,1}$ 都为输入点对中的最大值就好啦！


---

## 作者：喵仔牛奶 (赞：1)

一个赛时想到的另类 DP 做法。

# Solution

容易将原题转化为一个人乘电梯每次上下一层。

对于 $a_i<b_i$ 是好处理的，记 $\displaystyle m=\max_{1\leq i\leq n}\{a_i,b_i\}$，只需要跑到 $m$ 即可解决所有这种条件。

对于 $a_i>b_i$ 的条件，我们除了到 $m$ 外，还需要额外地从上往下跑。显然我们跑一轮可以解决掉多个询问，设解决的询问集合是 $S$，则分两类：
1. 先下后上，代价为 $\displaystyle(\max_{i\in S}\{a_i\}-\min_{i\in S}\{b_i\})\times 2$，可以跑若干轮。
2. 到 $m$ 再下去，代价为 $m-\min_{i\in S}\{b_i\}$，只能跑一轮。

第二种跑法只能最后跑，故在计算答案时考虑，下文考虑第一种跑法。

将 $a_i>b_i$ 的询问按 $a_i$ 排序，设 $f_{i}$ 是用第一种跑法满足前 $i$ 个条件的最小额外次数。观察发现，每次处理的条件是一个区间。

证明（可以跳过不看）：假设原来两个区间里元素组成的集合分别是是 $P,Q$，$\forall i\in P,j\in Q$，$a_i\leq a_j$。则考虑将 $Q$ 中的一个元素放入 $P$ 中使答案变优。由于放入后，$P$ 的代价会变大，要是答案变优，需要 $Q$ 代价变小。若取 $Q$ 中 $b_i$ 最小的元素 $k$ 加入 $p$，则 $Q$ 中 $a_i$ 小于 $a_k$ 的元素加入 $P$ 代价不变；若取 $Q$ 中 $a_i$ 最大的元素加入 $P$ 中，由于 $\forall i\in P,j\in Q$，$a_i\leq a_j$，代价和变大。证明 $P$ 中元素加入 $Q$ 中不优同理。

易得转移方程：
$$f_{i}=\min_{0\leq j<i}\{f_{j}+(a_i-\min_{j<k\leq i}\{b_k\})\times 2\}=\min_{0\leq j<i}\{f_{j}-2\times\min_{j<k\leq i}\{b_k\}\}+2\times a_i$$

考虑优化这个 DP。

令 $\displaystyle d_x=\min_{x<j\leq i}\{b_j\}$，则转移方程为 $\displaystyle f_i=\min_{1< j\leq i}\{f_{j-1}-2\times d_j\}+2\times a_i$。每次更新 $d_x\gets\min\{d_x,b_i\}$。
容易发现 $d$ 是不降序列。用珂朵莉树维护段连续相同的 $d$。加入 $a_i$ 只需要二分出第一个 $a_i\leq d_j$ 的位置 $j$，然后将 $j\sim i$ 合并为新段即可。

为了求出 $f_i$，还需要维护每块里面的 $\displaystyle\min_{j-1\leq k\leq i-1}\{f_{k}\}+2\times d$ 和它的前缀 $\min$。为了维护它们，合并时还需要用一颗线段树来求出 $\displaystyle\min_{j-1\leq k\leq i-1}\{f_{k}\}$。

最后，只需要枚举第二种跑法从哪里开始就行啦，答案为 $\displaystyle\min_{0\leq i\leq n}\{f_{i}+2m-\min_{i<j\leq n}\{b_i\}\}$。

时间复杂度 $\mathcal{O}(n\log n)$。

# Code
```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
    typedef vector<LL> poly;
	const int N = 1e6 + 5;
	namespace SGT {
	    LL sum[N << 2];
	    inline void push_up(int p) { sum[p] = min(sum[p << 1], sum[p << 1 | 1]); }
	    void modify(int p, int l, int r, int t, LL k) {
	        if (l == r) { sum[p] = k; return; }
	        int mid = (l + r) >> 1;
	        if (t <= mid) modify(p << 1, l, mid, t, k);
	        if (t > mid) modify(p << 1 | 1, mid + 1, r, t, k);
	        push_up(p);
	    }
	    LL query(int p, int l, int r, int nl, int nr) {
	        if (nl <= l && r <= nr) return sum[p];
	        LL mid = (l + r) >> 1;
	        if (nl <= mid && nr > mid)
	            return min(query(p << 1, l, mid, nl, nr), query(p << 1 | 1, mid + 1, r, nl, nr));
	        if (nl <= mid) return query(p << 1, l, mid, nl, nr);
	        if (nr > mid) return query(p << 1 | 1, mid + 1, r, nl, nr);
	    }
	};
	using namespace SGT;
	struct node {
		mutable LL v, l, r, pre;
		node(LL HCY, LL AK, LL IOI, LL Orz) : v(HCY), l(AK), r(IOI), pre(Orz) {}
		bool operator < (const node& x) const { return v < x.v; }
	};
	LL n, m, cnt, x, y, mn, ans, f[N]; pii a[N]; 
	set<node> s;
	int main() {
		memset(sum, 0x3f, sizeof sum);
		memset(f, 0x3f, sizeof f);
		cin >> n;
		for (int i = 1; i <= n; i ++) {
			cin >> x >> y, m = max({m, x, y});
			if (x > y) a[++ cnt] = pii(x, y);
		}
		n = cnt, sort(a + 1, a + 1 + n);
		f[0] = 0, modify(1, 0, n, 0, 0);
		for (int i = 1; i <= n; i ++) {
			auto it = s.lower_bound(node(a[i].se, 0, 0, 0));
			LL t = (it == s.end() ? i : it->l), last = (it == s.begin() ? m + 1 : prev(it)->pre);
			s.erase(it, s.end());
            s.insert(node(a[i].se, t, i, min(last, query(1, 0, n, t - 1, i - 1) - a[i].se * 2)));
			f[i] = prev(s.end())->pre + a[i].fi * 2, modify(1, 0, n, i, f[i]);
		}
		mn = m, ans = INT_MAX;
		for (int i = n; i >= 0; i --)
			ans = min(ans, f[i] + m * 2 - mn), mn = min(mn, a[i].se);
		cout << ans << '\n';
		return 0;
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
    int T = 1;
    while (T --) Milkcat::main();
    return 0;
}
```

---

## 作者：XSean (赞：0)

[P9579 「Cfz Round 1」Elevator](https://www.luogu.com.cn/problem/P9579)

## 基本思路：

思路：

主要思路为贪心。其他解法可观看其他题解。

- 首先找到所有 $a_i,b_i$ 中的最大值 $Mx$，$\{p\}$ 至少是 $\{1,2,3\dots Mx\}$，对于 $a_i < b_i$ 的状态必然包含于其中。

- 然后考虑插入 $a_i > b_i$ 的状态，模拟样例 $2$，发现有两种插入方法。

  样例 $2$ 的 $\{p\}$ 的最终状态之一为 $\{1,2,3,4,3,2,3,4,5,6,7,8,9,10,11,10,9,8\}$。

  - 中间插入。如：中间数字 $4$ 后面的 $\{3,2,3,4\}$。
  - 最末插入。如：末尾的 $\{10,9,8\}$。

  这两个插入方法的区别在于一个降了要升回来，一个只要降但要先降到 $\max(a_i,b_i)$。

- 可以省插入的数字的情况：比如前面有一段为 $\{10, 9, 8\}$，那么 $a_i=9,b_i=8$ 的情况可以省去。

- 保证复杂度的操作：将 $a_i > b_i$ 的状态挑出来，以 $a_i$ 为第一关键字，以 $b_i$ 为第二关键字排序，第一关键字降序，第二关键字升序。因为从最大的开始降降到对应的最低可以省去相同的第一关键字，并且第一关键字的下一个比上一个小就可以直接降不用管前面的状态。

  如假如样例 $2$ 还有一状态 $a_i = 3, b_i = 1$，就可以直接插在 $\{4,3,2\}$ 的后面， 那么 $\{p\}$ 的最终状态之一为 $\{1,2,3,4,3,2,1,2,3,4,5,6,7,8,9,10,11,10,9,8\}$。

- 考虑反悔操作：假如当排完序后某一状态需要使用最末插入时，可以去除前面的所有插入。

- 使用哪种插入方法：记录两个方法的最低处 $midl,endl$，对比哪种更优即可，具体看代码。 

## 代码实现：

核心代码：

```cpp
//bool stt;
const int N = 5e5 + 10;
int n;
int a[N], b[N];
int Mx;
PII pos[N];
int tot;
bool cmp(PII a, PII b){
	if(a.fi != b.fi) return a.fi > b.fi;
	else return a.se < b.se;
} //排序
//bool edd;
int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
//	cerr << (&edd - &stt) / 1024.0 / 1024.0 << endl;
	rd(n);
	rep(i, 1, n){
		rd(a[i], b[i]); Mx = max(Mx, max(a[i], b[i])); //找最大值Mx
		if(a[i] > b[i]) pos[++tot] = {a[i], b[i]}; //挑出ai > bi的情况
	} 
	LL s = Mx * 2, sum = Mx, sum1 = 0, sum2 = 0;
    //s为最多需要多少，sum为至少多少，sum1为最末插入的数字个数，sum2为中间插入的数字个数
	sort(pos + 1, pos + tot + 1, cmp); //排序
	LL endl = Mx, midl = 0;
	rep(i, 1, tot){
		auto t = pos[i];
		if(!midl) midl = t.fi; //最初的midl初始化
		if(t.fi == pos[i - 1].fi) continue; //跳过相同第一关键字
		if(t.se >= endl || t.se >= midl) continue; //省插入的数字的情况
		int tmp1 = endl - t.se, tmp2; //开始对比 tmp1为最末插入的情况
		tmp2 = 2 * (min((LL)t.fi, midl) - t.se); //tmp2为中间插入的情况
		if(tmp2 >= tmp1) sum1 += tmp1, endl = t.se, sum2 = 0; //对比，反悔
		else sum2 += tmp2, midl = t.se;	
	}
	prf("%lld\n", min(s, sum + sum1 + sum2));
	return 0;
}
```

**[完整代码](https://www.luogu.com.cn/paste/kx4t62tw)**



---

## 作者：One_JuRuo (赞：0)

## 思路

假设 $a_i$ 和 $b_i$ 的最大值是 $maxn$。

可以发现序列 $1,2,3 \cdots maxn$ 一定是要构造的序列的子序列。

那么，这种情况下，一定满足了所有的 $a_i<b_i$，因为 $a_i\neq b_i$，所以我们只需要单独满足所有的 $a_i>b_i$ 就可以了。

对于所有的 $a_i>b_i$，我们有两种选择，到了 $a_i$ 后，序列往回减倒 $b_i$ 再加回来，或者序列最后达到 $maxn$ 再往回减倒 $b_i$。

第一种情况会使答案增加 $2\times (a_i-b_i)$，第二种情况会使答案增加 $maxn-b_i$。

那么，我们可以先对 $b_i$ 排序，然后枚举 $i$，$i$ 以前的用前一种，$i$ 以后的用后一种。

## 39pts WA code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{long long a,b;}spe[500005];
inline bool cmp(node a,node b){return a.b<b.b;}
long long n,a1,b1,cnt,maxn,ans,sum;
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;++i)
	{
		scanf("%lld%lld",&a1,&b1);
		if(a1>b1) spe[++cnt].a=a1,spe[cnt].b=b1;//记录ai>bi的情况
		maxn=max(maxn,max(a1,b1));
	}
	ans=0x3f3f3f3f3f3f3f3f;
	sort(spe+1,spe+cnt+1,cmp);//排序
	for(long long i=1;i<=cnt;++i)
	{
		ans=min(ans,sum+maxn-spe[i].b);//取最小
		sum+=2*(spe[i].a-spe[i].b);//记录前i所增加的答案
	}
	printf("%lld",min(sum,ans)+maxn);//最后的sum是全部都选择第一种的答案
	return 0;
}
```

WA 了，这是为什么呢？仔细想了一下，如果有两组 $a_i$ 和 $b_i$ 有重叠部分，如 $1,5$ 和 $3,7$ 那么如果这两组都选择第一种方式，那么增加的答案应该是 $2\times(7-1)$ 而非 $2\times(5-1)+2\times(7-3)$。

所以我们再记录前面所有的 $a_i$ 的最大值为 $lasa$，那么在处理第 $i+1$ 组时，如果 $b_i<lasa$ 的话，增加的答案就是 $2\times(a_i-lasa)$，否则的话就还是原来的答案贡献，合在一起就是 $2\times(a_i-\max(lasa,b_i))$。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{long long a,b;}spe[500005];
inline bool cmp(node a,node b){return (a.b!=b.b)?a.b<b.b:a.a<b.a;}
long long n,a1,b1,cnt,maxn,ans,sum,lasa;
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;++i)
	{
		scanf("%lld%lld",&a1,&b1);
		if(a1>b1) spe[++cnt].a=a1,spe[cnt].b=b1;
		maxn=max(maxn,max(a1,b1));
	}
	ans=0x3f3f3f3f3f3f3f3f;
	sort(spe+1,spe+cnt+1,cmp);
	for(long long i=1;i<=cnt;++i)
	{
		ans=min(ans,sum+maxn-spe[i].b);
		sum+=2*(max(0ll,spe[i].a-max(lasa,spe[i].b))),lasa=max(lasa,spe[i].a);
	}
	printf("%lld",min(sum,ans)+maxn);
	return 0;
}
```

---


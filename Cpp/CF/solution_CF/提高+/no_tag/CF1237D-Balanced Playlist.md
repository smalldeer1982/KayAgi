# Balanced Playlist

## 题目描述

您最爱的音乐平台 Imakf 为您专门推出了一份完美平衡的歌单，共 $n$ 首曲子，编号从 $1$ 到 $n$。您听歌是列表循环的，所以说您听完第 $i$ 首歌后，下一首会播放第 $i + 1$ 首歌，听完最后一首歌后将会从头播放。

您根据自己的感觉，为每首歌估计了一个**KUN值**，第 $i$ 首歌的KUN值是 $a_i$.

每天早上您都会从一首歌开始听，听的过程中，您就会记住您已经听的歌中最大的KUN值是多少，记为 $x$。当您听到一首KUN值严格小于 $\dfrac{x}{2}$ 的歌曲时，您会立刻砸掉播放器，以保持每天的好心情。

久而久之，您就想知道对于每一首歌 $i$ ，如果从它开始听，到停止播放之前一共可以听多少首歌？一首歌如果被重复播放，那每一次都要统计。

## 样例 #1

### 输入

```
4
11 5 2 7
```

### 输出

```
1 1 3 2
```

## 样例 #2

### 输入

```
4
3 2 5 3
```

### 输出

```
5 4 3 6
```

## 样例 #3

### 输入

```
3
4 3 6
```

### 输出

```
-1 -1 -1
```

# 题解

## 作者：qian_shang (赞：12)

 写一个单调队列的做法

 **处理数据**：

> 首先，因为是循环播放，所以要破环为链

> 通常的手段是开两倍，这道题有点特殊

> 试想这样一个情景，就是开头是一个小值，后面有一个大值，循环到第二次的时候把小值给中断了，这样很显然两倍是不够的，于是我们要开三倍

 **维护单调队列**：

> 我们可以线性查找每一个KUN值，与队列首作比较。如果KUN值过小就弹出队首，最后将这个数压入队列，并更新答案。

 **细节**：

> 1. 有些答案会在弹出队首的时候被忽略，所以最后要处理一遍

> 如果没有答案，就是上一个答案+1

> 2. 如果所有KUN值中的$min*2>=max$,就全部输出$-1$

> 可以证明，如果有一个是无限循环，则所有都是

 **详见代码注释**：(~~窝码风太丑了~~）

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 300005//注意三倍
#define M 30
#define inf 0x7f7f7f
using namespace std;
int maxx(int A,int B){return A>B?A:B;}
int minn(int A,int B){return A<B?A:B;}
int abss(int A){return A<0?-A:A;}
int n,m,cnt,l,r,x,y,ma,mi;
int a[N],s[N],b[N],ans[N];
int main()
{
	scanf("%d%d",&n,&a[1]);
	ma=mi=a[1]; a[(n<<1)+1]=a[n+1]=a[1];
	for (int i=2;i<=n;i++){
		scanf("%d",&a[i]);
		a[(n<<1)+i]=a[i+n]=a[i];
		ma=maxx(ma,a[i]);
		mi=minn(mi,a[i]);
	}//破环为链，开三倍，并记录最大最小值
	if ((mi<<1)>=ma) {
		for (int i=1;i<=n;i++)
			printf("-1 ");
		putchar('\n');return 0;
	}//特判无限循环
	l=0; r=0;//我太弱了，只能打手工滴
	for (int i=1;i<=n*3;i++){
		while (r>=l&&s[r]<a[i]) r--;//单调队列维护
		s[++r]=a[i]; b[r]=i;
		while (s[l]>(a[i]<<1)) {
			ans[b[l]]=i-b[l]; l++;//更新答案
		}
	}
	for (int i=n*3;i;i--){
		if (!ans[i]) ans[i]=ans[i+1]+1;
	}//特判，如果没有答案，就等于上一个加一
	for (int i=1;i<=n;i++)
		printf("%d ",ans[i]);//输出
	return 0;
}
```

---

## 作者：FallenGemini (赞：10)

## 题意

>  因为笔者太蒻了所以题意显得比较冗杂...

给定一个长度为 $n$ 的数列 $a_1,a_2,\cdots,a_n$。

对于第 $i$ 个数，我们按照 $i,i+1,\cdots,n-1,n,1,\cdots,i-2,i-1,i,i+1,\cdots$ 这样进行循环遍历，停止遍历当且仅当**前面的数均能被遍历**且**当前数严格小于已遍历数中的最大值的 $\frac{1}{2}$ **。

换句话说，对于以第 $i$ 个数开始的遍历，记在第 $j$ 个数停止，则需满足条件：

+  $\forall~k\in\{i,i+1,i+2,\cdots,j-1\}$ 满足 $a_k\ge \dfrac{max\{a_i,a_{i+1},\cdots,a_{k-1}\}}{2}$
+  $a_j< \dfrac{max\{a_i,a_{i+1},\cdots,a_{j-1}\}}{2}$

我们需要求出从第 $i$ 个整数，最长能遍历的长度为多少，若可以无限长，则输出 $-1$。

## Solution

首先考虑遍历长度无限长的情况：既然是无限长，那么整个数列就会全部被遍历，也就是说数列中的最小值 $a_{min}$ 满足 $a_{min}\ge \dfrac{a_{max}}{2}$ ，而既然整个数列的最大值和最小值的都不会使其停止，那么从任意位置开始，其遍历长度均为无限长。

考虑更一般的情况：对于任意一个数，我们从这个数开始向右遍历，在遍历的过程中我们会维护一个 $Max$ ，记录当前已被遍历的数中的最大值，在遍历过程中其状态的改变只有两种情况：

+ 情况一：当前节点的值比 $Max$ 大，我们需要更新 $Max$。
+ 情况二：当前节点的值严格小于 $\frac{Max}{2}$ ，遍历停止。

除了以上两种情况，其他节点对这个位置均无影响，那么我们应该怎么快速求出这两种情况的最靠前的位置呢？~~（肯定不会写O(n)暴力吧，如果暴力还优化什么。。。~~

显然这是一类 $\text{RMQ}$ 问题，但又不同于正常的 $\text{RMQ}$ 问题，我们求的是第一个满足某个条件的数，但又因为这个条件满足区间最大（最小）性质，所以我们可以考虑二分位置：

例如：当前我们需要在数列 $11,5,3,7,2,13,1,9,6$ 中找到第一个大于 $11$ 的位置，记二分左端点 $l=1$，右端点 $r=9$。

第一次二分：$mid=(1+9)>>1=5$ ，查询区间 $[1,5]$ 中的最大值下标为 $1$，因为 $a_1<=11$ 所以在区间 $[1,5]$ 不存在大于 $11$ 的数，$l=mid+1=6$

第二次二分： $mid=(6+9)>>1=7$ ，查询区间 $[1,7]$ 中的最大值下标为 $6$，因为 $a_6>11$ ，所以在区间 $[1,7]$ 中存在大于11的数，$r=mid=7$

第三次二分：$mid=(6+7)>>1=6$，查询区间 $[1,6]$ 中的最大值下标为 $6$ ，因为 $a_6>11$ ，所以在区间 $[1,6]$ 中存在大于11的数，$r=mid=6$

此时 $l=r=6$ ，找到第一个大于 $11$ 的位置，单次期望复杂度$O(logn)$。

已经解决了怎么找到最近的满足条件的数，下面来考虑怎么转移：

若情况二靠前，则从该节点开始的答案显然为 $ans_i=j-i$ 。

若情况一靠前，则从该节点开始的答案显然 $ans_i=ans_j+j-i$。

显然情况一的依赖关系不存在环，那记忆化搜索一遍就搞定了。

**注意这道题是环，所以要破环为链。**

## Code

~~代码不压行，可读性较高~~

```c++
//压行课次
#include<bits/stdc++.h>
#define LL long long
#define LD long double
using namespace std;
const int MAXN=1e5+10;
int n,a[MAXN<<1],MX[MAXN<<1][19],MN[MAXN<<1][19],ans[MAXN],MXX,MNN=1e9;
int read(){int sss=0,fff=1;char ccc;ccc=getchar();while(ccc<'0'||ccc>'9'){if(ccc=='-')fff=-1;ccc=getchar();}while(ccc>='0'&&ccc<='9')sss=(sss<<1)+(sss<<3)+(ccc^'0'),ccc=getchar();return sss*fff;}
int MinST(int l,int r)
{
	int len=r-l+1;
	int k=log2(len);
	if(a[MN[l][k]]<a[MN[r-(1<<k)+1][k]]) return MN[l][k];
	return MN[r-(1<<k)+1][k];
}
int MaxST(int l,int r)
{
	int len=r-l+1;
	int k=log2(len);
	if(a[MX[l][k]]>a[MX[r-(1<<k)+1][k]]) return MX[l][k];
	return MX[r-(1<<k)+1][k];
}
int Min(int l,int r)
{
	int x=a[l-1];
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(a[MinST(l,mid)]*2>=x) l=mid+1;
		else r=mid;
	}
	return l;
}
int Max(int l,int r)
{
	int x=a[l-1];
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(a[MaxST(l,mid)]<x) l=mid+1;
		else r=mid;
	}
	return l;
}
int solve(int x)
{
	if(ans[x]) return ans[x];
	int A=Min(x+1,x+n),B=Max(x+1,x+n);
	if(A<B) return ans[x]=A-x;
	else return ans[x]=B-x+solve((B-1)%n+1);
}
int main()
{
//	freopen("123.in","r",stdin);
//	freopen("123.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++) a[i]=a[i+n]=read(),MX[i][0]=MN[i][0]=i,MX[i+n][0]=MN[i+n][0]=i+n,MXX=max(MXX,a[i]),MNN=min(MNN,a[i]);
	if(MNN*2>=MXX)
	{
		for(int j=1;j<=n;j++)
			printf("-1 ");
		return 0;
	}
	for(int k=1;k<=18;k++)
	{
		int len=1<<k;
		for(int i=1;i+len-1<=n*2;i++)
		{
			int j=i+len-1,mid=i+(len/2);
 
			if(a[MX[i][k-1]]<a[MX[mid][k-1]]) MX[i][k]=MX[mid][k-1];
			else MX[i][k]=MX[i][k-1];
			
			if(a[MN[i][k-1]]>a[MN[mid][k-1]]) MN[i][k]=MN[mid][k-1];
			else MN[i][k]=MN[i][k-1];
		}
	}
	for(int i=1;i<=n;i++)
		ans[i]=solve(i);
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：Grisses (赞：5)

[题面](https://www.luogu.com.cn/problem/CF1237D)

先来分析一下样例。

- 样例1

```
4
11 5 2 7
```
第 1 首歌，听到第 2 首时 $5<\frac{11}{2}$ 只有 1 首。

第 2 首歌，听到第 3 首时 $2<\frac{5}{2}$ 只有 1 首。

第 3 首歌，听到第 2 首时 $5<\frac{11}{2}$ 只有 3 首。

第 4 首歌，听到第 2 首时 $5<\frac{11}{2}$ 只有 2 首。

所以输出是 `1 1 3 2`。

- 样例2

```
4
3 2 5 3
```
第 1 首歌，听完一圈再到第 2 首时 $2<\frac{5}{2}$ 只有 5 首。

第 2 首歌，听完一圈再到第 2 首时 $2<\frac{5}{2}$ 只有 4 首。

第 3 首歌，听到第 2 首时 $2<\frac{5}{2}$ 只有 3 首。

第 4 首歌，听完两圈再到第 2 首时 $2<\frac{5}{2}$ 只有 6 首。

所以输出是 `5 4 3 6`。

- 样例3

```
3
4 3 6
```
每一首歌都会无限播放下去，所以输出是`-1 -1 -1`。

然后，我们发现，本题其实只需要一个[单调队列](https://oi-wiki.org/ds/monotonous-queue/)。我们维护一个单调递减队列，如果队首大于了现在要插入元素的二倍，就弹出它，并更新他的答案。最后，因为有可能有的答案不会被更新，所以我们还要加一个处理，具体细节在代码中讲述。

代码
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,a[300005],ans[300005];//a存储元素的值，因为可能会超过2倍的范围，所以开3倍（具体参考样例2），ans存储答案
  deque<int>q;//单调队列用双端队列实现
  int main()
  {
      scanf("%d",&n);
      for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i+n]=a[i+2*n]=a[i];//复制2次
      for(int i=1;i<=3*n;i++){
          while(!q.empty()&&a[q.front()]>a[i]*2){//考虑队列前端是否大于了二倍a[i]
              ans[q.front()]=i-q.front();
              q.pop_front();
          }
          while(!q.empty()&&a[q.back()]<a[i])q.pop_back();//维护单调
          q.push_back(i);
      }
      for(int i=n*3;i>=1;i--){
          if(ans[i]==0&&ans[i+1]!=0)ans[i]=ans[i+1]+1;//如果它没被更新过，那它一定是被维护单调时弹出了，找到它后面第1个有值的元素，再加上距离即可（证明在后），这里用从后往前遍历来累加，也可以达到同样的效果
      }
      for(int i=1;i<=n;i++)printf("%d ",(ans[i]==0?-1:ans[i]));//如果还是0，那就是因为可以无限播放，输出-1
      return 0;
  }
```

## 证明

在**不存在**无限播放的情况下，对于一个因为维护单调被弹出的元素，将它弹出的那个元素也可能也会被其他元素因为维护单调而弹出。但一定会有一个元素 $i$ 是因为作为队首而大于队尾的二倍而被弹出（否则就会存在无限播放）。那么，在 $i$ 之前的那一段连续的没有答案更新的元素一定是也是在从 $i$ 开始播放停止的地方停止（因为 $i$ 是这一段中最大的）。那对于每一个在这一段中的元素，它的答案就是它到 $i$ 的距离加上 $i$ 的答案。

---

## 作者：DarkMoon_Dragon (赞：3)

# 题意：

+ 对于一个数组的每一位，输出当前位置的最远循环合法访问位置离当前位置多远。
+ 一个合法访问当且仅当已访问的最大数小于等于已访问的最小数的两倍。

# $Solution$
+ 读题首先肯定都想得到**二分+RMQ**查询的$\Theta(n\log^2 n)$做法，先不考虑这种做法，又难写复杂度又高。
+ 无限循环的充要条件是数组最小值的两倍大于等于最大值。这个比较显然。
+ 考虑找到前面比当前数小的最大值，维护**单调栈**，二分查找更新，复杂度$\Theta(n\log n)$。
+ 下面是`tourist`的单调栈做法`std`。

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(3 * n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i + n] = a[i + 2 * n] = a[i];
  }
  vector<int> ans(3 * n);
  vector<int> st_max;
  vector<int> st_min;
  for (int i = 3 * n - 1; i >= 0; i--) {
    while (!st_max.empty() && a[st_max.back()] < a[i]) {
      st_max.pop_back();
    }
    while (!st_min.empty() && a[st_min.back()] > a[i]) {
      st_min.pop_back();
    }
    int low = 0, high = (int) st_min.size();
    while (low < high) {
      int mid = (low + high) >> 1;
      if (a[st_min[mid]] * 2 < a[i]) {
        low = mid + 1;
      } else {
        high = mid;
      }
    }
    int nxt = 3 * n;
    if (low > 0) {
      nxt = min(nxt, st_min[low - 1]);
    }
    if (!st_max.empty()) {
      nxt = min(nxt, st_max.back());
    }
    if (nxt < 3 * n && a[nxt] >= a[i]) {
      ans[i] = ans[nxt];
    } else {
      ans[i] = nxt;
    }
    st_min.push_back(i);
    st_max.push_back(i);
  }
  for (int i = 0; i < n; i++) {
    if (i > 0) {
      cout << " ";
    }
    cout << (ans[i] == 3 * n ? -1 : ans[i] - i);
  }
  cout << '\n';
  return 0;
}
```

+ 这两种方法都得把数组复制三遍，虽然直觉可能是只复制两遍，但是有一种情况最大值出现在最后一位，但是并不能循环完成，还得再走一遍找到最小值。所以是复制三遍。
+ 当然这种`Global Round`~~代码量应该不大~~
+ 原来对于每个数的查找比较是$\Theta(n)$的，重复比较了很多次。考虑`two pointers`（即尺取法）减少比较次数。
+ 可以维护一个`multiset`，加上`two pointers`即可做到$\Theta(\log n)$查找最右合法位置，并且不会重复比较，具体可以看下面代码。
+ 注意将遍历过的冗余状态删除。
+ 这种写法就特别简洁了。

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#define rr int
using namespace std;
typedef long long ll;
inline ll read() {
    char i = getchar();
    ll f = 1, res = 0;
    while (i < '0' || i > '9') {
        if (i == '-') f = -1;
        i = getchar();
    }
    while (i >= '0' && i <= '9') {
        res = res * 10 + i - '0';
        i = getchar();
    }
    return f * res;
}
const int N = 3e5 + 50;
int n;
multiset<int> st;
int a[N], maxn = -1e9, minn = 1e9;
int main() {
    n = read();
    for (rr i = 1; i <= n; ++i) {
        a[i] = read();
        a[i + 2 * n] = a[i + n] = a[i];
        minn = min(minn, a[i]);
        maxn = max(maxn, a[i]);
    }
    if (maxn <= 2 * minn) {
        for (rr i = 1; i <= n; ++i) printf("-1 ");
        return 0;
    }
    for (rr i = 1, j = 0; i <= n; ++i) {
        while (1) {
            if ((!st.empty() && (*(--st.end())) > a[j + 1] * 2) || (j >= 3 * n))
                break;
            st.insert(a[++j]);
        }
        printf("%d ", j - i + 1);
        st.erase(st.lower_bound(a[i]));
    }
    return 0;
}
```

---

## 作者：Light_in_Dark (赞：2)

## CF1237D Balanced Playlist 题解

$\texttt{As we know}$， `CF` 的题大多是水题。

先看一眼题目，可以很容易地写出暴力代码，然后就光荣地 $\texttt{T}$ 掉了。仔细想一想，发现假设上一次最多可以从 $i$ 看到 $j$，那么就一定可以从 $i+1$ 看到 $j$，为什么呢？有如下证明：

> 首先假设从 $i$ 看到 $k$（$i < k \leq j$），那么 $\max^{k}_{l=i}a_l$ 一定是大于 $\max^{k}_{l=i+1}a_l$，所以只要 $i$ 可以看到 $j$，$i+1$ 就一定可以看到 $j$。

于是我们就可以发现，这不就是单调队列裸题吗！！！只要发现一个不能看的歌，就直接输出答案，枚举下一个时就从这首歌开始。由于它可以循环播放，于是我们复制两遍到后面，就能让~~他~~它循环播放了。于是就有如下代码：



**code:**

```cpp
//懒得打注释，反正上面都写了。。。
#include <bits/stdc++.h>
using namespace std;
const int inf = 1e5 + 5;
int n, a[inf], top = 1;
int q[inf], l = 1, r;
int main() {
	cin >> n;
	q[++r] = 0;
	for (int i = 1; i <= n; ++i) cin >> a[i], a[i + n] = a[i + (n << 1)] = a[i];
	for (int i = 1; i <= n; ++i) {
		for ( ; l <= r && q[l] < i; ++l) ;
		for ( ; top <= 3 * n; ++top) {
			if (l <= r && (a[top] << 1) < a[q[l]]) {
				cout << top - i << " ";
				break ;
			}
			for ( ; l <= r && a[q[r]] < a[top]; --r) ;
			q[++r] = top;
		} if (top > 3 * n) cout << -1 << " ";
	}
	return 0;
}
```

~~被卡半天，才发现要开三倍空间~~

---

## 作者：401rk8 (赞：2)

上午 vp了这场比赛，发现自己这道题用了十分 ~~暴力~~ 不一样的做法：线段树。

$-1$ 显然好判断。  
有解的情况一定不超过 $2n$（第一次枚举会得到最大值，第二次结束）。

那么可以将 $a$ 复制 $3$ 倍（为了让 $a_n$ 后也有 $2n$ 个数），考虑每个 $i$ 在何处停止。  
如果 $a_i$ 是较大值，那么停止的位置 $ans_i$ 满足 $j>i,a_j<\frac{a_i}2$ 的最小的 $j$。如果 $a_i$ 不是，那么 $ans_i=ans_{i+1}$。

发现两种情况都需要用到 $i$ 之后的数据，倒着做即可。对于第一种情况则用权值线段树转移。时间复杂度 $O(n\log a_i)$。

由于 $a_i$ 很大且无法离散化，需要动态开点，注意数组一定要开够（赛时因此 RE 了一次）

```cpp
const int N = 3e5+5;
int n,a[N];
 
int ind,rt,ls[N*10],rs[N*10],mn[N*10];
int ans[N];
 
void up(int u) { mn[u] = min(mn[ls[u]],mn[rs[u]]); }
void add(int &u,int l,int r,int p,int x) {
	if( !u ) mn[u = ++ind] = n+1;
	if( l == r ) { mn[u] = min(mn[u],x); return; }
	int mid = l+r>>1;
	if( p <= mid ) add(ls[u],l,mid,p,x);
	else add(rs[u],mid+1,r,p,x);
	up(u);
}
int query(int u,int l,int r,int ql,int qr) {
	if( ql <= l && r <= qr ) return mn[u];
	int mid = l+r>>1, res = n+1;
	if( ql <= mid && ls[u] ) res = min(res,query(ls[u],l,mid,ql,qr));
	if( mid < qr && rs[u] ) res = min(res,query(rs[u],mid+1,r,ql,qr));
	return res;
}
 
int main() {
	read(n);
	For(i,1,n) read(a[i]), a[i+n] = a[i+n+n] = a[i];
	n *= 3;
	mn[0] = ans[n] = n+1, add(rt,1,1e9,a[n],n);
	for(int i = n-1; i; --i) {
		ans[i] = min(ans[i+1],query(rt,1,1e9,1,(a[i]-1)/2));
		add(rt,1,1e9,a[i],i);
	}
	For(i,1,n/3) printf("%d ",ans[i]<=n ? ans[i]-i : -1);
	return 0;
}
```

最后，~~求赞~~ 祝大家 THUSC RP++

---

## 作者：Liynw (赞：1)

这是我们考试题，考试打了个不知道是什么玩意儿的线段树然后爆零了……

正解是单调队列，时间复杂度 $\Theta(n)$。

我们先把数组复制 $3$ 遍。等等，为什么不是两遍呢？

因为最大值有变化，某首歌是否满足条件的数据在变化，所以可能出现第一次可以播放，但第二次不行的情况。平时我们是复制两遍，所以这里要多复制一遍。

然后从第一首歌开始，一次遍历被复制了三遍的数组，维护一个单调递减的队列。当然，里面存的是数组下标，下标当然不是单调递减的，但是代表的喜爱值是递减的。

我们以样例举例：

`3 2 5 3`

```
i =   1  2  3  4  5  6  7  8  9  10 11 12
a =   3  2  5  3  3  2  5  3  3  2  5  3
ans = 0  0  0  0  0  0  0  0  0  0  0  0
```

每次遍历到一个数，依次进行如下操作：

1. 判断队首元素是否符合标准，当前遍历到的元素 $i$ 是否满足要求，即是否有 $a_i<\dfrac{a_{q.\text{front()}}}{2}$。如果是，那么计算队首元素的答案（从它开始最多可以放多少首歌，**即为当前遍历到的歌曲编号减去队首元素的编号**）并把队首元素弹出。

	**注意队首可能不止一个元素不满足要求，需要连续弹出。**

   比如我们遍历到了 $6$ 号，然后单调队列现在长这样：
   
   `front {3, 4, 5} back` 也就是 `front {5, 3, 3} back`
   
  	本来没什么问题，但是注意到 $2<\frac{5}{2}$，所以如果播放了 $3$ 号歌曲，就不能播放 $6$ 号歌曲了。那么，从 $3$ 号歌曲开始播放最多能播放 $6-3=3$ 首歌，也就是 $3,4,5$ 这三首。
   ```
                         v i遍历到这儿了
	i =   1  2  3  4  5  6  7  8  9  10 11 12
	a =   3  2  5  3  3  2  5  3  3  2  5  3
	ans = 0  0  3  0  0  0  0  0  0  0  0  0
		        ^答案被更新
	```

2. 把遍历到的元素放进单调队列。当然，为了保持单调，也许需要弹出队尾的一些元素。

	**其实这也是为什么不能用队列长度来更新答案的原因。有些数可能会被弹掉，此时直接用队列长度判断答案可能会遗漏。**
    
遍历完数组之后就可以输出答案了，但是有个问题：

比如样例遍历完之后 `ans` 数组长这样：

`0 0 3 0 0 0 3 0 0 0 3 0`

那 $1,2,4$ 号怎么办呢？

其实这个很简单，你想一下，就以 $2$ 号歌曲举例，你先听一首到 $3$ 号歌曲，然后再按照 $3$ 号的答案计算不就行了吗？所以这里我们再倒序遍历一遍数组，如果某个下标的答案没被更新，就把答案更新为 `在它后面的最近的一个本来就有答案的值 + 当前遍历到的下标和那个数的下标之差`。

给出代码：

```cpp
#include <cstdio>
#include <deque>
#define rep(i, j, k) for(int i = j; i <= k; ++i)
#define dep(i, j, k) for(int i = j; i >= k; --i)

const int maxn = (int)3e5 + 5;

int n, N, a[maxn], ans[maxn];
std::deque<int> q;

inline void file() {
	freopen("playlist.in", "r", stdin);
	freopen("playlist.out", "w", stdout);
	return;
}

int main() {
	file();
	scanf("%d", &n);
	rep(i, 1, n) {
		scanf("%d", &a[i]);
		a[i + n] = a[i + (n << 1)] = a[i];
	}
	N = 3 * n;
	rep(i, 1, N) {
		while(!q.empty()/*防止 RE*/ && (a[i] << 1) < a[q.front()]) {
			ans[q.front()] = i - q.front();
			q.pop_front();
		}
		while(!q.empty() && a[q.back()] < a[i])
			q.pop_back();
		q.push_back(i);
	}
	int tot = 0, lst = N + 1;
	dep(i, N, 1) {
		if(ans[i]) {
			tot = 0;
			lst = i;
		} else
			ans[i] = ans[lst] + tot;
		++tot;
	}
	rep(i, 1, n)
		printf("%d ", (ans[i] < n << 1) ? ans[i] : -1);
	return 0;
}
```

---

## 作者：xkcdjerry (赞：0)

发现对于任意一个放歌放到一半的状态，还有多长时间结束只取决于现在的位置和已经播放的最大值。  
那么若强行把现在的位置回滚到已经播放的最大值，那么还有多长时间结束只取决于现在的位置，*与前面放了什么无关*。

注意到：  
* 答案只取决于现在的位置，状态数较少  
* 答案不受前面放了什么影响，无后效性

所以可以猜出是 dp。

由于状态和数组内容显然（状态就是最大值所在的位置，内容就是从这个位置往后放还能放多久），这里考虑转移方程。

假如最大值一直不改变，那么显然会一直往后放直到撞到第一个 $<\frac{a_i}2$ 的数，记这种情况下还会放多少个为 $f_i$。  

再记下一个 $>a_i$ 的数还要放几首为 $g_i$。

显然有如下结论（下面关于位置的计算均隐式模 $n$）：  
* 若 $g_i>f_i$，那么因为会在走到更大值前结束，所以结果与最大值不改变相同，即 $c_i=f_i$。
* 若 $g_i<f_i$，那么走到 $i+g_i$ 处时接下来就与 $i$ 无关，变为了从 $i+g_i$ 处出发能走几步，即 $c_i=g_i+c_{i+g_i}$。
* 由 $f_i$ 与 $g_i$ 的定义显然可知 $f_i \neq g_i$。

由于每次求 $c_x$ 时若需要 $c_y$，则一定存在 $a_x<a_y$，所以上述转移式一定不存在循环求值情况。

由此可知，已知 $f$ 和 $g$ 的情况下可使用 dfs 在 $O(n)$ 的时间内求出 $c$。

考虑 $f$ 和 $g$ 求值的本质均在于找到左端点固定且最小小于某值/最大大于某值的最小区间，而由于若区间 $[l,r]$ 存在该最小/最大值，那么 $[l,r+1]$ 一定也存在该最小/最大值，即该问题可二分。

得到最小/最大值可选用 $O(n \log n)$ 预处理，$O(1)$ 查询的 st 表，那么二分 $2n$ 次复杂度为 $O(n \log n)$，即含预处理求 $f,g$ 的时间复杂度为 $O(n \log n)$。

综上，程序的总复杂度为 $O(n+n \log n)=O(n \log n)$。

代码如下（二分和 dfs 部分为了避免冗长略有压行）：  
```c++
#include <cstdio>
#include <cmath>
#define inf 0x3f3f3f3f
#define N 100010
#define LG 20
#define mid (l+r)/2
int n,a[N];
int mn[LG][N],mx[LG][N];
int f[N],g[N],c[N];
int l,r;
int min(int x,int y){return x<y?x:y;}
int max(int x,int y){return x>y?x:y;}
int fmin(int l,int x) {int t=log2(x); return min(mn[t][l],mn[t][(l+x-(1<<t)+1)%n]);}
int fmax(int l,int x) {int t=log2(x); return max(mx[t][l],mx[t][(l+x-(1<<t)+1)%n]);}
int dfs(int x) {return c[x]?c[x]:c[x]=(f[x]<g[x]?f[x]:g[x]+dfs((x+g[x])%n));}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",a+i);
    for(int i=0;i<n;i++) mn[0][i]=mx[0][i]=a[i];
    for(int i=1;(1<<i)<=n;i++) for(int j=0;j<n;j++)
    {
        mn[i][j]=min(mn[i-1][j],mn[i-1][(j+(1<<(i-1)))%n]);
        mx[i][j]=max(mx[i-1][j],mx[i-1][(j+(1<<(i-1)))%n]);
    }
    int t1=fmin(0,n),t2=fmax(0,n);
    if(t1*2>=t2) {for(int i=0;i<n;i++) printf("-1 "); return 0;}
    for(int i=0;i<n;i++)
    {
        if(2*t1>a[i]) f[i]=inf;
        else
        {
            for(l=1,r=n-1;l!=r;) 2*fmin(i,mid)<a[i]?r=mid:l=mid+1;
            f[i]=l;
        }
        if(a[i]==t2) g[i]=inf; 
        else
        {
            for(l=1,r=n-1;l!=r;) fmax(i,mid)>a[i]?r=mid:l=mid+1;
            g[i]=l;
        }
    }
    for(int i=0;i<n;i++) printf("%d ",dfs(i));
}
```

[AC 记录](https://www.luogu.com.cn/record/87584071)

---

## 作者：Unnamed114514 (赞：0)

对于本题，我们可以先考虑无解的情况：在多次遍历后，最大值和最小值都已遍历，此时若最小值和最大值都不满足题目中的条件的话，我们就发现它会一直循环下去。

在判断了无解之后，我们可以构建一个单调递减队列，此时队首存储的是当前遍历到的最大值，队尾为当前遍历到的最小值，此时我们已经保证有解了。如果我们的队首和队尾已经满足有解，记录答案为 $k$。

此时，我们可以发现：有些答案有解，有些答案还是空着的。此时我们需要填充它。设 $i$ 表示当前需要填充的答案，则对于后面的第一个有答案的位置 $j$，我们只需要先从 $i\to j$，再得到 $j$ 的答案 $ans_j$，答案就是 $j-i+ans_j$。此时我们可以用递推优化：假设 $k$ 还暂时没有解，$k+1$ 此时已经有解，从刚刚推出的公式可以发现：$ans_k\gets ans_k+(k+1)-k=ans_k+1$。

对于数组大小，我们可以开到三倍：因为我们至少要在遍历最大值之后再遍历一次最小值，于是我们就只能先遍历一层循环，此时若最小值比最大值先遍历到，我们还需要再遍历一次，才能满足在最大值之后遍历最小值。

时空复杂度均为 $O(3n)$。
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
inline int read(){
    int res=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')
        ch=getchar();
    while(ch>='0'&&ch<='9'){
        res=(res<<1)+(res<<3)+(ch^'0');
        ch=getchar();
    }
    return res;
}
int n,a[maxn],mx,ix=1e9+1,q[maxn],l,r,ans[maxn];
int main(){
    int n=read();
    for(int i=1;i<=n;++i)
        a[i+n*2]=a[i+n]=a[i]=read(),mx=max(mx,a[i]),ix=min(ix,a[i]);
    if(mx<=(ix<<1)){
        for(int i=1;i<=n;++i)
            printf("-1 ");
        return 0;
    }//剪枝：唯一的无解情况——最大值小于等于最小值的两倍
    for(int i=1;i<=3*n;++i){
        while(l<=r&&a[q[l]]>(a[i]<<1))
            ans[q[l]]=i-q[l],++l;
        while(l<=r&&a[q[r]]<a[i])
            --r;
        q[++r]=i;
    }
    for(int i=n*3;i;--i)
        if(!ans[i])
            ans[i]=ans[i+1]+1;
    for(int i=1;i<=n;++i)
        printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：cqbzjyh (赞：0)

### Soulution.

先将原数组复制三份。

然后，我们可以用一个单调递减队列来维护 KUN 值。当某个时刻发现队首元素 $a_i$ 除以 $2$ 比队尾元素 $j$ 大，这就表明了 $i$ 元素以前已经被弹出的元素都将会在 $j$ 处暂停播放音乐。于是我们就用数组记录答案，然后 $i$ 以前的元素都可以通过 $i$ 推出来。（弹出队首时我们要用 `while` ，因为可能有多个队首都不满足条件）。

### Code.

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T>
void read (T &x) {
    x = 0; T f = 1;
    char ch = getchar ();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar ();
    }
    x *= f;
}
char For_Print[25];
template <typename T>
void write (T x) {
    if (x == 0) { putchar ('0'); return; }
    if (x < 0) { putchar ('-'); x = -x; }
    int poi = 0;
    while (x) {
        For_Print[++poi] = x % 10 + '0';
        x /= 10;
    }
    while (poi) putchar (For_Print[poi--]);
}
template <typename T>
void print (T x, char ch) {
    write (x); putchar (ch);
}
int n;
int a[300005];
int q[300005], tail = 0, head = 0;//单调队列
int ans[300005];
signed main() {
	freopen("playlist.in", "r", stdin);
	freopen("playlist.out", "w", stdout);
	read(n);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
	}
	for (int i = 1; i <= n; i++) {
		a[i + n] = a[i];
	}
	for (int i = 1; i <= n; i++) {//复制三份
		a[i + 2 * n] = a[i];
	}
	for (int i = 1; i <= 3 * n; i++) {
		while (head <= tail && a[q[tail]] < a[i]) tail--;//维护单调递减
		q[++tail] = i;
		while (a[q[head]] * 1.0 / 2 > a[q[tail]]) {//弹出队首
			ans[q[head]] = i - q[head];
			head++;
		}
	}
	for (int i = 3 * n; i >= 1; i--) {
		if (ans[i] == 0 && ans[i + 1] != 0) ans[i] = ans[i + 1] + 1;
	}
	for (int i = 1; i <= n; i++) {
		if (ans[i] == 0) print(-1, ' ');
		else print(ans[i], ' ');
	}
	return 0;
}
```

---


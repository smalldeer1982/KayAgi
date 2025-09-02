# 【MX-J3-T2】 Substring

## 题目背景

原题链接：<https://oier.team/problems/J3C>。

## 题目描述

你有一个数列 $a$，**其中 $1\sim n$ 各出现了一次**。

当你任意选一对 $1\le l\le r\le n$，并将 $a_l,a_{l+1},\ldots,a_r$ 排成一行，你就得到了 $a$ 的一个子串，记为 $a_{l\sim r}$，称 $l$ 为左端点，$r$ 为右端点。

你需要把 $a$ 所有子串按字典序从小到大排序。但是为了避免输出量过大，我会给出 $q$ 个问题，每次给出一个 $k$，求字典序第 $k$ 小的子串左右端点。

---

如果你不知道什么是字典序，看这里：

对于两个数列 $p,q$，称 $p$ 的字典序小于 $q$（记为 $p<q$），当且仅当存在**自然数** $k$ 使 $p,q$ 的前 $k$ 个数相同且 $p_{k+1}<q_{k+1}$。

特别地，若 $p$ 是 $q$ 的前缀且 $p\ne q$，也认为 $p$ 的字典序小于 $q$。

例如：
- $[1,2]<[3,2]$（当 $k=0$）
- $[3,1,100]<[3,2,1]$（当 $k=1$）
- $[3,4]<[3,4,6]$（$p$ 是 $q$ 前缀）

## 说明/提示

**【样例解释 #1】**

数列 $3,1,2$ 共有 $6$ 个子串，从小到大排序的结果为：$[1],[1,2],[2],[3],[3,1],[3,1,2]$。

**【数据范围】**

|测试点编号|$n\le$|$q\le$|特殊性质|
|:-:|:-:|:-:|:-:|
|$1\sim 3$|$200$|$200$||
|$4\sim 7$|$1000$|$3\times 10^5$||
|$8\sim 9$|$3000$|$3\times 10^5$||
|$10\sim 13$|$3\times 10^5$|$10$||
|$14\sim 15$|$3\times 10^5$|$3\times 10^5$|$a_i=i$|
|$16\sim 20$|$3\times 10^5$|$3\times 10^5$||

对于全体数据，保证 $1\le n,q\le 3\times 10^5$，$1\le k\le \dfrac{n(n+1)}{2}$，$a_i$ 中 $1\sim n$ 各有一个，输入皆为整数。

## 样例 #1

### 输入

```
3 6
3 1 2
1
2
3
4
5
6
```

### 输出

```
2 2
2 3
3 3
1 1
1 2
1 3
```

## 样例 #2

### 输入

```
50 25
42 22 27 8 44 11 14 31 37 10 48 15 12 40 13 4 25 9 19 5 2 18 6 1 32 3 38 33 43 34 46 47 23 35 21 20 45 39 50 7 36 17 24 29 16 30 49 26 28 41
1178
991
755
1094
689
132
671
635
421
659
448
334
327
213
1206
453
1160
583
388
781
150
692
23
1162
62
```

### 输出

```
37 48
27 44
3 28
1 46
43 47
20 34
33 37
2 19
15 44
2 43
7 27
6 31
6 24
4 29
32 37
7 32
5 44
19 47
13 47
44 45
23 24
43 50
24 46
5 46
26 30
```

# 题解

## 作者：yummy (赞：15)

# B. Substring 官方题解

本题考察的主要知识点：

- 【3】递推法（前缀和）
- 【4】lower\_bound 函数

### 思路分析

（为了防止双重下标，可能会用 $a[x]$ 表示 $a_x$。）

考虑如何比较 $a[l_1\sim r_1]$ 和 $a[l_2\sim r_2]$ 的字典序。

因为数列 $a$ 中 $1\sim n$ 各出现了一次，如果 $l_1\ne l_2$，那么 $a[l_1],a[r_2] $ 必然不同，比较它们即可。

否则一个字符串必然是另一个的前缀。如果 $r_1<r_2$ 则前者字典序小于后者，反之亦然。

使用这个方法可以把所有子串进行排序，根据选用排序方法的不同可得 $35\sim 45$ 分。

---

进一步思考，我们不求出所有子串，照样可以回答“第 $k$ 个子串是谁“的问题吗？

假设 $a_l=x$，记 $ p_x=l$，即“$x$ 的位置是 $l$”，那么 $x$ 开头的子串就有 $n+1-p_x$ 个。

在读入整个 $a$ 后，我们对于所有 $i=1,2,\ldots,n$，知道了以 $i$ 开头的子串个数。进而作前缀和，对于所有 $i=1,2,\ldots,n$，可知开头 $\le i$ 的子串个数，记为 $c_i$。

对于一个问题，我们查找最小的 $l$ 使得 $ c_l\ge k$，这样 $c_{l-1}+1\le k\le c_l$，左端点的**数值**就是 $l$ 了，左端点下标是 $ p_l$。然后计算 $k-c_{l-1} $ 知区间长度，计算 $p_l+k-c_{l-1}-1$ 就可以求出右端点。

总时间复杂度 $O(n+q\log n)$。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,x,p[300005];
long long k,c[300005];
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		p[x]=i;
	}
	for(int i=1;i<=n;i++)
		c[i]=c[i-1]+n-p[i]+1;
	for(;q;q--){
		scanf("%lld",&k);
		int l=lower_bound(c,c+n+1,k)-c;
		printf("%d %lld\n",p[l],k-c[l-1]+p[l]-1);
	}
	return 0;
}
```

---

## 作者：netlify (赞：8)

## [【MX-J3-T2】Substring](https://www.luogu.com.cn/problem/P10995)

### 题意简述

给你 $1$ 到 $n$ 的**排列**，求字典序第 $k$ 小的连续子串。

### 思路分析

以下“**区间**”，“**子串**”均指**连续子串**。

求第 $k$ 小，一个朴素的想法就是排序所有区间，然后输出第 $k$ 呗。

这样的时间复杂度是 $\Theta(n^2+q)$ 的，代码繁杂，此处不赘述。

但是我们这样考虑: 钦定一个区间，比如 $[i,n]$ ，由字典序的定义，他的所有前缀 $\forall i<j<n$ , $[i,j]$ 的字典序都小于他。也就是说，把所有区间排序输出， $[i,n]$ 一定在他的所有前缀后面。

而 $[i,n]$ 的所有前缀有 $n-i$ 个，也就是说以 $i$ 开头的所有子串的字典序排名是连续的，有 $n-i+1$ 个。  

然后考虑区间左端点不同的情况，由于是**排列**，左端点不同就是最左的数字不同。所以我们可以先排个序，然后维护一个类似前缀和的数组 $\text{sum}[i]$ 表示区间 $[i,n]$ 的字典序排名。询问时在 $\text{sum}[i]$ 数组中二分左端点，快速计算右端点(即在左端点加上偏移量 $k-\text{sum}[pos-1]-1$ )即可。

排序之前要把原下标记录一下。

时间复杂度 $\Theta(n\log n+q\log n)$ 。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,sum[300005];
pair<int,int>a[300005];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i].first,a[i].second=i;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
        sum[i]=sum[i-1]+n-a[i].second+1;
    for(int x;q--;){
        cin>>x;
        int pos=lower_bound(sum+1,sum+n+1,x)-sum;
        x-=sum[pos-1];
        cout<<a[pos].second<<" "<<a[pos].second+x-1<<"\n";
    }
    return 0;
}
```

---

## 作者：2c_s (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P10995)

## 思路

贪心、前缀和、二分。

由于查询的是子串，那么串一定连续。这时候子串排序的结果一定是按照 **$1$ 开头，$2$ 开头，...，$n$ 开头**这样的顺序排的。设这个数字为 $a_i$，则 $a_i$ 开头的子串数量就是 $n-i+1$。

知道了这一点后，我们就可以先记录每个数字的位置 $id_{a_i}$，再把数字排序，计算出每个数开头的子串数量，最后计算前缀和。

每次查询的时候找第一个前缀和 $\ge k$ 的位置 $p$，说明第 $k$ 个子串肯定在 $a_p$ 开头的范围内。现在我们知道左端点为 $id_p$，接着计算右端点。

此时 $sum_p$ 为**加上 $a_p$ 开头的所有数之后**的前缀和，所以 $k-sum_{p-1}$ 即为要往后**延长**的数量。但是注意这样查的范围是右界 $+1$，所以最后还要 $-1$，即右端点为 $id_p+k-sum_{p-1}-1$。

- 子串数最大为 $\Large\frac{n(n+1)}{2}$，$1\le n\le 3\times 10^5$，记得开 long long。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){
	ll k=0;bool flag=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')flag=0;c=getchar();}
	while(isdigit(c)){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	if(flag)return k;return -k;
}
const int N=3e5+10;
ll n,q,sum[N],id[N];
struct node{
	ll x,num;//x 当前数，num 子串数量。
}a[N];
signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;++i){
		a[i]={read(),n-i+1};
		id[a[i].x]=i;//记录这个数的位置。
	}
	sort(a+1,a+1+n,[](node a,node b){return a.x<b.x;});
	for(int i=1;i<=n;++i)sum[i]=sum[i-1]+a[i].num;
	while(q--){
		ll k=read();
		int p=lower_bound(sum+1,sum+1+n,k)-sum;
		cout<<id[p]<<" "<<id[p]+k-sum[p-1]-1<<"\n";
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/174725815)

---

## 作者：shuqiang (赞：4)

考虑如何比较 $a_{b \sim c},a_{d \sim e}$。

题目中，字典序的定义如下：

对于两个数列 $p,q$，称 $p$ 的字典序小于 $q$（记为 $p<q$），当且仅当存在**自然数** $k$ 使 $p,q$ 的前 $k$ 个数相同且 $p_{k+1}<q_{k+1}$。

特别地，若 $p$ 是 $q$ 的前缀且 $p \ne q$，也认为 $p$ 的字典序小于 $q$。

我们可以根据字典序的定义得出两个结论：
1. 当 $b \ne d$ 时，因为 $1 \sim n$ 在数列 $a$ 中各出现了一次，所以 $a_b \ne a_d$，$k$ 只能等于 $0$，得出当 $a_b<a_d$ 时，$a_{b \sim c}$ 的字典序小于 $a_{d \sim e}$。

2. 当 $b = d$ 时，我们不妨假设 $c<e$，此时 $a_{b \sim c}$ 是 $a_{d \sim e}$ 的前缀，按照题目对字典序的定义得出 $a_{b \sim c}$ 的字典序小于 $a_{d \sim e}$。

设 $f_i$ 为数字 $i$ 在 $a$ 中子串的字典序排名，根据结论 $1$ 易得 $f_i<f_{i+1}$，又因为以 $l$ 开头的子串有 $n-l+1$ 个，所以可以先令 $f_{i+1}$ 等于以数字 $i$ 开头的子串的个数，$f_1=1$，再对 $f$ 求前缀和，就可以求出数字 $i$ 在 $a$ 中子串的字典序排名。

设要查询第 $x$ 个，我们可以求出 $f_l \le x < f_{l+1}$，因为 $f$ 满足 $f_i<f_{i+1}$ 的单调性，所以可以用二分求出 $l$，最后根据结论 $2$ 求出 $r=l+(x-f_l)$，时间复杂度 $\mathcal{O}(n + q \log n)$。

AC 代码：
```cpp
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 3 * 1e5 + 10;
int n, q, a[N];
long long x, c[N];

struct pii{
	int x, y;
	
	bool operator < (const pii & o) const{
		return x < o.x;
	} 
} b[N];

int main(){
	cin >> n >> q;
	for(int i = 1; i <= n; i++) {cin >> a[i]; b[i].x = a[i], b[i].y = i;}
	sort(b + 1, b + 1 + n);
	c[1] = 1;
	for(int i = 1; i <= n; i++) {c[i+1] = n - b[i].y + 1; c[i+1] += c[i];}
	while(q--){
		cin >> x;
		int fd = upper_bound(c + 1, c + 2 + n, x) - c - 1;
		cout << b[fd].y << ' ' << b[fd].y + (x - c[fd]) << '\n';
	}
    return 0;
}

```

---

## 作者：canwen (赞：3)

彩蛋：被入门组吊打了，才 $356$ pts，特写题解反省。

## 题意
有长度为 $n$ 的数列 $s$，将其所有子串按字典序排序。

有 $q$ 次询问，记第 $x$ 小的子串左右端点下标分别为 $l,r$，求出 $l,r$。

关于数列的子串以及字典序比较，题目描述已经讲得很清楚了，不再赘述。
## 分析
首先知道，如果两个字符串的长度不等，那么长度较长的串字典序大。

题目考虑的是**子串**，不是序列，结合样例，就能看出其实只需对序列 $s$ 的数字进行升序排序，记好原来的下标，就能表示出第 $x$ 小的子串的 $l,r$。

以样例一为例子，排序后的第一个数字 $1$ 原来的下标（下面默认下标从 $1$ 开始）是 $2$，说明 $l=2$ 的子串能够解决第 $1$ 小到第 $n-2+1=2$ 小子串的询问。排序后的第二个数字 $2$ 原来的下标是 $3$，说明 $l=3$ 的子串能够解决第 $2+(n-3+1)=3$ 小子串的询问。排序后的第三个数字同上。记录以 $s$ 中的每个数字的下标为 $l$ 的所能表示到第几小存到数组中。

上面的做法模拟一下就行了。

接着可以用二分的方式查找第 $x$ 小的子串的 $l$，接着 $r$ 就好求了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5+5;
int n,q;
long long ans[N],cnt,x;//注意N*(N+1)/2 会爆int 
struct node{
	int id,num;
}a[N];
bool cmp(node a,node b){
	return a.num<b.num;
}
int main(){
	scanf("%d%d",&n,&q); 
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i].num);
		a[i].id=i;//记录原来的下标 
	}
	sort(a+1,a+1+n,cmp); 
	for(int i=1;i<=n;++i){
		//记录l=i时能表示到第几小 
		ans[i]=cnt+n-a[i].id+1;
		cnt=ans[i];
	}
	for(int i=1;i<=q;i++){
		scanf("%lld",&x); 
		int k=lower_bound(ans,ans+1+n,x)-ans;//二分查找 
		printf("%d %d\n",a[k].id,x-ans[k-1]+a[k].id-1); //求出l和r 
	}
	return 0;
}
```

---

## 作者：fede (赞：2)

# 正文

## 分析

题目中让我们把子串按字典序从小到大排序，因为是字典序，我们可以很好推断出子串的性质。

首先，要让字典序小，则第一位一定要小，所以我们不妨把第一位先确定下来。

既然第一位确定了，根据“特别地，若 $p$ 是 $q$ 的前缀且 $p\ne q$，也认为 $p$ 的字典序小于 $q$”，我们可以知道：   
如果第一位已经确定了，因为子串只能向后再取，前面的部分保持相同，所以第一位相同的情况时子串越长字典序越大。

第一位相同的子串，它们的排名一定是连续的。

## 思路

题目要我们求字典序第 $k$ 小的子串。

### 45分

根据上面的推断，我们就可以用 $n^2$ 的时间处理出所有子串的排名，具体思路是这样的

设 $cnt$ 表示当前排名。   
因为输入的序列 $1\sim n$ 各出现了一次，所以从小到大遍历每一个数，找到这个数出现的位置，这个数作为单独子串，它的排名就为 $cnt+1$。之后在从当前位置遍历每一个数，把数加入到子串中，再计算这个新子串的排名。

查询时间复杂度为 $O(1)$，所以整体时间复杂度为 $O(n^2)$，空间复杂度也会爆掉。

### 正解

因为我们把所有情况都处理出来了，而我们只需要求出每一次询问的答案，会有大量的冗余操作。我们考虑在询问时再进行专门处理。

首先，我们需要找出第一个数字是多少，但是直接查找效率太慢。

这么思考，对于每个数作为子串开头，子串的右端点可以从它的位置一直到 $n$，所以能组成的方案数就为包括它自己后面还有多少个数。这样我们就可以知道每个数产生了多少排名。

既然知道了每个数产生的排名，我们就可以按照第一个数从小到大的顺序将能产生的排名数量累加起来，达到我们需要的排名区间。

我们可以借助**前缀和**来帮助我们处理，但是一个一个判断区间仍然太慢。

我们再想想看，前缀和是有序地，而且我们是要查找找到排名所在的区间——这不就是二分查找吗？

在前缀和序列中，我们可以找到从左到右第一个大于查询排名的位置或最后一个小于查询排名的位置，我们也就能够知道了第一个数字是多少。

第一个数字在哪里子串的左端点就在哪里，这是毫无疑问的。   
但是因为前缀和序列储存的等同于是这个位置上的数作为第一个数字的最后一个排名，所以我们要按前一个数作为第一个数字的最后一个排名加上区间的长度就能知道子串的右端点了。

可以用 $\operatorname{lower\underbar{ }bound}$，也可以自己手写二分。

## 代码

### 45分

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=5e6+10;
struct node{
	int l,r; 
};
node ans[N];
int a[N];
int vi[N];
int n,Q;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>Q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		vi[a[i]]=i;
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		for(int j=vi[i];j<=n;j++){
			cnt++;
			ans[cnt].l=vi[i];
			ans[cnt].r=j;
		}
	}
	while(Q--){
		int x;
		cin>>x;
		cout<<ans[x].l<<' '<<ans[x].r<<endl;
	}
	return 0;
}
```

### 正解

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define No "No"
#define Yes "Yes"
using namespace std;
const int N=1e6+10;
int vi[N];
int sum[N];
int a[N];
int n,Q;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>Q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		vi[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1];
		sum[i]+=n-vi[i]+1;
	}
	while(Q--){
		int x;
		cin>>x;
		int l=1,r=n;
		while(l+1<r){
			int mid=(l+r)>>1;
			if(sum[mid]>x){
				r=mid;
			}else{
				l=mid;
			}
		}
		int ansl=0,ansr=0;
		if(sum[l]>=x){
			ansl=vi[l];
			ansr=ansl+x-sum[l-1]-1;
		}else{
			ansl=vi[r];
			ansr=ansl+x-sum[r-1]-1;
		}
		cout<<ansl<<' '<<ansr<<endl; 
	}
	return 0;
}
```

时间复杂度 $O(q\log{n})$，空间复杂度 $O(n)$，完美通过此题。

---

## 作者：linch (赞：2)

## 题意
给定一个长度为 $n$ 数列，其中数字 $1$ 到 $n$ 各出现一次。求出这个数列中字典序第 $k$ 小的子串。

## 思路
**首先考虑暴力求解。**

暴力枚举出每一个子串，通过排序获得字典序子串即可，时间复杂度过高，哪怕使用快排也明显不能通过此题。

**进一步地，我们根据字典序的定义进行优化求解。**

可以发现，对于一子串 $a$ 的第一个数字 $x$ 和另一个子串 $b$ 的第一个数字 $y$，当 $x < y$ 时，$a$ 的字典序一定小于 $b$ 的字典序。

根据上面的规律，容易得出，对于一个开头为 $x$ 的子串，其在所有子串中的字典序一定是从 $1$ 至 $x-1$ 的所有子串数量之和加上这个子串在**以 $x$ 开头的所有子串**中的位次。

## 解法
可以通过计算或者观察样例解释发现，数列中第 $i$ 个数字数字开头的子串个数为 $n - i + 1$。

我们可以使用前缀和预处理出 $pre_i$ 为分别从 $1 \sim i$ 开头的子串数量之和。

接着，我们每次询问时查找最小的 $i$，使得 $pre_i \geq k$ 即可。由于每次从 $1$ 开始枚举复杂度过劣，为 $O(nq)$，需要使用二分查找，找到满足条件的 $i$ 后计算答案即可。总时间复杂度 $O(n + q \log n)$，可以通过此题。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
long long n,q,a[maxn],cnt[maxn],pre[maxn];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		a[x]=i;
	}//记录位置
	for(int i=1;i<=n;i++){
		cnt[i]=n-a[i]+1;//cnt 数组表示以 $i$ 开头的子串个数。
		pre[i]=pre[i-1]+cnt[i];
	}//前缀和。
	for(int i=1;i<=q;i++){
		long long x;
		cin>>x;
		long long l=1,r=n,mid;
		long long ans=r+1;
		while(l<=r){
			mid=l+r>>1;
			if(pre[mid]<x){
				l=mid+1;
			}
			else{
				r=mid-1;
				ans=min(mid,ans);
			}//二分查找。
		}
		cout<<a[ans]<<" "<<a[ans]+x-pre[ans-1]-1<<"\n";//计算答案，注意计算右边界时要加一。
	}
	return 0;
}
```
[赛时 AC 记录](https://www.luogu.com.cn/record/174651857)

---

## 作者：savvsavsaasvav (赞：2)

题目意思非常简洁明了，在 $a$ 的所有子串中，找出字典序第 $k$ 大的子串。

朴素做法，按照题意模拟一遍，再进行快速排序。

这题是一道二分加前缀和的一道简单应用。~~连我在赛中都能做的出来就是简单的。~~

二分思路显而易见，二分的是左指针所指的数，因为所指的数越小，排序时的字典序越小，这就是本题的单调性，这样我们就可以~~轻松~~求出左指针所指的数。怎么求呢，我先卖个关子，后面我再讲。

当然，到这里还没有结束，因为右指针我们还未确定。

这个时候，前面的问题就来了，怎么求做指针所指的数，可以看到，字典序一定比它小的字串个数可以确定。具体就是，将所有数的位置标记，即设 $p_a=i$，以 $i$ 为左指针所指的数的子串个数就有 $n-p_i+1$（加的一就是只有自己的子串）。

这样我们使用前缀和 $sum_i$ 表示以 $i$ 及 $i$ 之前为左指针的所有字串个数。如果 $sum_{mid-1}<k$，说明 $mid$ 取小了，因为字典序比它小的子串个数不足 $k$，加上它本身也不足 $k$。否则就是取大了。

好，这下左指针的问题解决了，右指针也就好办了。

题目中对字典序的描述非常清晰，如果 $p$ 是 $q$ 的前缀，那么 $p$ 的字典序比 $q$ 小。所以在以 $i$ 为左指针的所有子串中，$l=r=p_i$ 是字典序最小的，接下来是 $l=p_i,r=p_i+1$，最大的是 $l=p_i,r=n$。右指针就是 $p_i+k-sum_{pos-1}-1$，就是将左指针向右移动 $k$ 个子串中除去一定比以 $p_i$ 为左指针字典序小的子串。

说了这么多，相信大家都会自己写了吧。跟着本蒟蒻的代码和注释一起来一遍吧。

提示：$sum,k$ 都需要开 long long，不然会喜提 WA。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e5+10;
int n,q,a,p[N];
ll sum[N],k;//记得开 long long。
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i){
		scanf("%d",&a);
		p[a]=i;//统计 a 的位置。
	}
	for(int i=1;i<=n;++i){
		sum[i]=sum[i-1]+(ll)(n-p[i]+1);//前缀和，前面有提到过。
	}
	while(q--){
		scanf("%lld",&k);
		int l=1,r=n,pos=1;
		while(l<=r){
			int mid=(l+r)/2;
			if(sum[mid-1]<k){//取小了。
				l=mid+1,pos=mid;
			}
			else{
				r=mid-1;
			}
		}
		printf("%d %d\n",p[pos],p[pos]+k-sum[pos-1]-1);//我的大家的二分习惯可能不同，我的答案就是 pos。p[pos] 就是左指针所在位置。
	}
}
```

---

## 作者：Scean_Tong (赞：2)

## P10995 【MX-J3-T2】Substring
### 题意
给你一个排列，将该排列的每个子串按字典序排序，每次询问查询字典序第 $k$ 小的子串的左右端点。

### 思路
给出一个赛时做法，可能会很麻烦。

首先，以 $a_i$ 为左端点的子串共有 $n-i+1$ 个。

考虑如何求出按顺序以每个值为左端点的子串的个数，可以先用结构体存下每个值、下标和以这个值为左端点的子串的个数，然后按值排序。

然后对每个值的子串数量求一下前缀和，设前缀和为 $sum_i$，那么每次询问就转化为了找出第一个 $sum_{cnt}$ 大于等于 $k$ 的 $cnt$，这个显然可以用二分求。

最后答案显然。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T=1;
const int maxn=3e5+7;
struct node{
	int val,id,num;
}a[maxn];
int n,q;
bool cmp(node a,node b){
	return a.val<b.val;
}
int sum[maxn];
int check(int k){
	int l=0,r=n;
	int ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(sum[mid]>=k){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	return ans;
}
void solve(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i].val;
		a[i].id=i;
		a[i].num=n-i+1;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[i].num;
	}
	while(q--){
		int k;
		cin>>k;
		int cnt=check(k);
		cout<<a[cnt].id<<' '<<a[cnt].id+(k-sum[cnt-1])-1;
		cout<<'\n';
	}
}
int32_t main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	while(T--){
		solve();
	}
	return 0;
}




```

---

## 作者：_Deer_Peach_ (赞：2)

题意：

有一个长度为 $n$ 的数组 $a$，其中 $1$ 到 $n$ 各出现一次，有 $q$ 次询问，每次询问字典序第 $k$ 小的子串是哪一段。

思路：

先从样例开始解释：
```
3 6
3 1 2
```
先把所有的子串按字典序大小从小到大全列出来为 $[1],[1,2],[2],[3],[3,1],[3,1,2]$。以 $1$ 开头的子串数量有 $2$ 个，以 $2$ 开头的子串数量有 $1$ 个，以 $3$ 开头的子串数量有 $3$ 个。子串都是连续的，以第 $i$ 个数字开头，那么它的子串的数量就是在它后面的数字数量加上自己，也就是 $n-i+1$ 个。那么我们可以在输入时统计出每个数字的下标和以这个数字开头的子串数量。
```
for(int i=1;i<=n;i++){
  cin>>a[i];
  ns[a[i]].id=i;//下标
  ns[a[i]].num=n-i+1;//以a[i]开头的子串数量
}
```
然后 $q$ 次询问。每次询问都是给出一个数字 $k$，求字典序第 $k$ 小的子串的区间。\
字典序越小，那么开头的数字就越小，所以求第 $k$ 小的子串可以从以 $1$ 开头的子串开始找，直到找到目标子串。找到目标子串后，因为是以数字 $i$ 为子串的开头，所以 $l$ 就是数字 $i$ 的下标，再算出以数字 $i$ 开头的子串中第几个是第 $k$ 小的，加上 $l$ 再减 $1$ 就是 $r$ 了。
```
int cnt=0,l,r;//cnt是找到的子串数量,l和r表示区间
for(int i=1;i<=n;i++){
	if(cnt+ns[i].num>=x){//找到了
    	l=ns[i].id;//以i开头的子串所以l是数字i的下标
    	r=l+(x-cnt)-1;//算出是以数字i开头的子串中第几个是第k小的
    	break;//找到之后就可以直接结束了
  	}
  	cnt+=ns[i].num;//还没找到
}
cout<<l<<" "<<r<<endl;
```
完整代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,a[300001];struct node{
	int id,num;
}ns[300001];signed main(){
	cin>>n>>q;for(int i=1;i<=n;i++){cin>>a[i];ns[a[i]].id=i;ns[a[i]].num=n-i+1;}
	while(q--){
		int x;cin>>x;int cnt=0,l,r;for(int i=1;i<=n;i++){
			if(cnt+ns[i].num>=x){l=ns[i].id;r=l-cnt+x-1;break;}
			cnt+=ns[i].num;
		}cout<<l<<" "<<r<<endl;
	}
	return 0;
}
```
但是这样查找的复杂度太高了，所以可以先通过前缀和求出以前 $i$ 个数字为开头的子串的数量，再用二分找出目标子串是以哪个数字为开头的。
```
for(int i=1;i<=n;i++)b[i]=b[i-1]+ns[i].num;//前缀和
while(q--){
	int x;
	cin>>x;
	int l=1,r=n+1,mid;
	while(l<r){//二分找出目标子串是以哪个数字为开头的
		mid=(l+r)/2;
		(b[mid]>=x?r=mid:l=mid+1);
	}
	cout<<ns[r].id<<" "<<ns[r].id-b[r-1]+x-1<<endl;//输出
}
```
完整代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,a[300001],b[300001];struct node{
	int id,num;
}ns[300001];signed main(){
	cin>>n>>q;for(int i=1;i<=n;i++){cin>>a[i];ns[a[i]].id=i;ns[a[i]].num=n-i+1;}
	for(int i=1;i<=n;i++)b[i]=b[i-1]+ns[i].num;while(q--){
		int x;cin>>x;int l=1,r=n+1,mid;while(l<r){
			mid=(l+r)/2;(b[mid]>=x?r=mid:l=mid+1);
		}cout<<ns[r].id<<" "<<ns[r].id-b[r-1]+x-1<<endl;
	}
	return 0;
}
```

---

## 作者：MoonCake2011 (赞：1)

哇，原来是排列。

那不错。

对于不同 $l$ 的子串就可以方便的排序了。

那我们直接对每个位置排序。

可以 $O(1)$ 计算每个位置为 $l$ 的子串数量。

然后我不想二分了。

于是我直接离线询问。

排序。

这样就只用移动指针了。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[300010];
int pos[300010],s[300010];
bool cmp(int x,int y){
	return a[x]<a[y];
}
struct node{
	long long ak;
	int id;
}q[300010];
bool operator < (node x,node y){
	return x.ak<y.ak;
}
int ansl[300010],ansr[300010];
int main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],pos[a[i]]=i;
	sort(pos+1,pos+n+1,cmp);//排序 
	long long sum=0,P=0; 
	for(int i=1;i<=m;i++) cin>>q[i].ak,q[i].id=i;
	sort(q+1,q+m+1);//离线排序
	for(int i=1;i<=m;i++){//枚举询问
		while(P<n && sum+n-pos[P+1]+1<q[i].ak) sum+=n-pos[P+1]+1,P++;//如果可行，移动指针 
		long long t=q[i].ak-sum;//计算区间长度 
		ansl[q[i].id]=pos[P+1],ansr[q[i].id]=pos[P+1]+t-1;//提出左端点右端点
	}
	for(int i=1;i<=m;i++) cout<<ansl[i]<<" "<<ansr[i]<<"\n";
	return 0;
}
```

---

## 作者：_Weslie_ (赞：1)

感觉有点板？

## Solution of P10995

考虑一个序列：$a=\{4,1,5,6,2,3\}$。

先考虑字典序最小的子串，按照题目要求是 $\{1\}$。

然后排开是 $\{1,5\},\{1,5,6\},\{1,5,6,2\},\{1,5,6,2,3\}$。

然后是以 $2$ 开头的子串，以 $3$ 开头的子串，最后到 $\{6,2,3\}$。

按照题目规则，不难发现按照字典序排序的子串一定是以 $1$ 开头的，等以 $1$ 开头的结束了才轮到以 $2$ 开头的，然后依次排开。

然后记录一下以 $i$ 开头的分别有几个，设有 $p_i$ 个，则 $p_i=n-pos_i+1$，其中 $pos_i$ 表示 $i$ 在排列中的位置。

然后对 $p$ 前缀和得数组 $sum$，不难看出 $sum_i$ 表示到从以 $1$ 到以 $i$ 开头的所有子串数量。

然后我们在 $sum$ 数组中二分找出第一个大于等于 $k$ 的 $sum_i$。然后左端点就是 $pos_i$。手搓一下也不难看出右端点是 $pos_i+k-sum_{i-1}-1$。输出这个即可。

## Code

```
#include<bits/stdc++.h>
using namespace std;
struct node{
	int val,id;
}a[300005];
int n; 
bool cmp(node _,node __){
	return _.val<__.val; 
}
long long sum[300005],k;
int q;
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i].val);
		a[i].id=i; 
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+(n-a[i].id+1);
	}
	while(q--){
		scanf("%lld",&k);
		int t=lower_bound(sum+1,sum+n+1,k)-sum;
		printf("%d %lld\n",a[t].id,a[t].id+k-sum[t-1]-1);
	}
	return 0;
}
```

---

## 作者：皓月星辉 (赞：1)

## 题意
给定一个长度为 $n$ 的**排列** $a$，以及 $q$ 次询问，对于每次询问，给定一个 $k$，要求排列 $a$ 的所有子串中按字典序排名的第 $k$ 个子串的左右节点的下标。
## 分析
由于 $1 \sim n$ 各出现了一次，而字典序的第一关键字是首字母，所以我们只要记录以每个数字开头的子串有多少个即可。

对于每个 $a_i$，以其为开头的子串数目为 $n - i + 1$ 个，然后去计算第 $k$ 个子串的开头数字和长度就可以计算出其结尾下标。

计算开头数字需要预处理，否则在询问时计算会超时。
## 代码（含注释，请勿抄袭）

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,q,a[300005],b[300005];
long long t1,s1,s[300005],t[300005],x=1;
//结构体存储，方便排序。
struct node{
	long long v,id,t,s;
}k[300005];
bool cmp(node a,node b){return a.v<b.v;}//按数值大小排序。
bool cmp1(node a,node b){return a.id<b.id;}//按序号大小排序。
int main()
{
	cin>>n>>q;
	for(long long i=0;i<n;i++)
	{
		cin>>a[i];
		b[a[i]]=n-i;//记录子串数量。
	}
	for(long long i=1;i<=q;i++)
	{
		cin>>k[i].v;
		k[i].id=i;
	}
    sort(k+1,k+q+1,cmp);//按数值大小从小到大排序，方便计算开头数字。
    //预处理计算开头数字
	for(long long i=1;i<=n&&x<=q;i++)
	{
		s1+=b[i];
		while(s1>=k[x].v&&x<=q)
		{
			s1-=b[i];
			k[x].s=s1;
			k[x].t=i;
			s1+=b[i];
			x++;
		}
	}
	sort(k+1,k+q+1,cmp1);//按输入的顺序排回去，这一步很重要！
	for(int i=1;i<=q;i++)cout<<n-b[k[i].t]+1<<" "<<n-b[k[i].t]+k[i].v-k[i].s<<endl;//计算出下标并输出答案。
	return 0;
}
```
## END

---

## 作者：FurippuWRY (赞：1)

注意到要把子串按字典序排序，观察样例，可以得出一个结论：$\forall i \in [1, n]$，设子串 $[a_i]$ 的排名是 $t$，那么子串 $[a_i, a_{i + 1}],[a_i,a_{i + 1},a_{i+2}],...,[a_i,...,a_n]$ 的排名分别为 $t+1,t+2,...,t+n-i$。

那我们就可以计算每一个字符及其后面所有字符可以组成的子串数量，对于字符 $a_i$，这个数就是 $n - i + 1$，存入一个 `map` （我定义为 `p`）中，然后计算前缀和（存入 `map`，我定义为 `s`），便于判断查询时子串的两个端点。

举个例子，如样例一，其前缀和如下：

|$s_1$|$s_2$|$s_3$|
|:-:|:-:|:-:|
|$2$|$3$|$6$|

可以发现，$s_i$ 就是以 $i$ 开头的子串的最大右端点，那么输入 $k$ 后，判断它在 $s$ 中的哪两个数之间，然后反推子串的第一个和最后一个字符，再反推左右端点即可。

同样还是用样例一举例，输入 $k = 5$，查找到在 $s_2$ 与 $s_3$ 之间（查到的数是 $s_3$），那么可以推出这个子串是以 $3$ 开头的，然后反推出 $3$ 在 $a$ 中的序号，即为左端点；对于右端点，计算出 $k$ 与 $s_2$ 的差，加上左端点即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 9;

#define int long long

int n, q, a[N], k;
map<int, int> p, r;
int s[N];

signed main() {
	
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		p[a[i]] = n - i + 1;
        // 计算 a[i] 后可以组成的子串数量，同时也可以用来反推序号
	}
	s[0] = 0;
	for (int i = 1; i <= n; ++i) {
		s[i] += p[i] + s[i - 1];
	}
	while (q--) {
		cin >> k;
		int t = lower_bound(s + 1, s + n + 1, k) - s;
        // 查找 k 在 s 中的右边的数的序号
		cout << -(p[t] - n - 1) << ' ' << -(p[t] - n - 1) + k - s[t - 1] - 1 << '\n';
	}
	
	return 0;
}
```

闲话：多开一个 `map` 卡常才能过，开两个直接 T 飞了。赛时多开一个，洛谷卡卡常过了，在梦熊死活过不去，打了更多卡常还是过不去，梦熊神机。

---

## 作者：xxxalq (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P10995)

# 思路

此题中的字典序是第一个数大就大，且由于 $a$ 是一个排列，所以由每一个 $a_i$ 开头的子串在所有子串的排序中一定是连续的。那么我们就可以通过前缀和优化加二分查找在 $O(\log n)$ 的时间复杂度内找到排名第 $k$ 名的子串的左端点位置所对应的的数，通过存储每个数的位置，就可以 $O(1)$ 的计算出右端点了。

总时间复杂度 $O(q \log n)$。

# 代码


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=300005;

ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch>57||ch<48){
        if(ch==45){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>=48&&ch<=57){
        x=(x<<3)+(x<<1)+(ch-48);
        ch=getchar();
    }
    return x*f;
}

int n,q,mk[maxn];

ll a[maxn];

int main(){
    n=read(),q=read();
    int x;
    for(int i=1;i<=n;i++){
        x=read();
        a[x]=n-i+1;
        mk[x]=i;
    }
    for(int i=1;i<=n;i++){
        a[i]+=a[i-1];
    }
    ll k;
    while(q--){
        k=read();
        int l=1,r=n,mid;
        while(l<r){
            mid=(l+r)>>1;
            if(a[mid]<k){
                l=mid+1;
            }else{
                r=mid;
            }
        }
        cout<<mk[l]<<" "<<mk[l]+k-a[l-1]-1<<"\n";
    }
    return 0;
}
```

---

## 作者：sbno333 (赞：0)

我们考虑**如果**把所有区间按照字典序排序后是怎样的顺序。

我们发现对于 $1$ 开始的是最小的，假设 $1$ 的位置是 $x$，由于对于 $x\le i< j\le n$，有 $zdx(a_{l\sim i})<zdx(a_{1\sim j})$，其中 $zdx(s)<zdx(t)$ 在这里为 $s$ 比 $t$ 字典序小。

于是我们记 $b_i$ 表示 $i$ 的下标，按顺序应当为 $a_{b_1\sim b_1},a_{b_1\sim b_1+1},a_{b_1\sim b_1+2}\dots a_{b_1\sim n},a_{b_2\sim b_2},a_{b_2\sim b_2+1},a_{b_2\sim b_2+2}\dots a_{b_2\sim n}\dots a_{b_n\sim b_n},a_{b_n\sim n}$。

然后我们简单分成 $n$ 段，第 $i$ 段表示以 $b_i$ 为开始的字符串组成的。

我们如果找到了是哪一段，然后知道在这一段第几大，我们可以轻松推出来右端点。

我们可以做一个前缀和，然后二分在哪一段，使得减去前头的和是否还有选择的余地 $k>0$，且段的编号最大。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
int a[1000009];
signed main(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		a[x]=n-i+1;
	}
	for(int i=2;i<=n;i++){
		a[i]+=a[i-1];
	}
	while(q--){
		int k;
		cin>>k;
		int l,r;
		l=1,r=n;
		while(l<r){
			int mid;
			mid=l+r;
			mid>>=1;
			if(k<=a[mid]){
				r=mid;
			}else{
				l=mid+1;
			}
		}
		int x,y;
		x=a[l]-a[l-1];
		x=n-x+1;
		k-=a[l-1];
		y=x+k-1;
		cout<<x<<" "<<y<<endl;
	}
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# P10995 题解

## 思路

假设左端点相同，则长度越大的，字典序靠后。

左端点不相同，左端点对应的数字更小的，字典序靠前。

对于每一个 $a_i$，统计以 $a_i$ 为左端点的子串个数，记作 $b_{a_i}$，记 $pos_i$ 为数字 $i$ 出现的位置，则 $pos_{a_i}=i$。

对 $b$ 求前缀和 $pre$，$pre_i$ 表示左端点选 $\le i$ 的子串数量之和。

对于每一个 $k$，求 $pre$ 中第一个 $\geq k$ 的数字，设为 $t$，则左端点为 $pos_t$，右端点为 $p+k-pre_{t-1}-1$。

举个例子。样例 $1$ 序列为 $[3,1,2]$，数字 $3$ 作为左端点，则子串数量为 $3$，那么 $b_3=3$，同理，$b_1=2$，$b_2=1$，所以 $b$ 数组即为 $[2,1,3]$，构建前缀和数组 $pre$ 为 $[2,3,6]$。拿第 $5$ 个询问来说吧，要求排名第 $5$ 的子串左右端点，二分求得 $pre$ 里面第一个 $\geq 5$ 的数，显然是索引为 $3$ 的 $6$，那么记 $t=3$，则这个子串的左端点对应的数字就是 $3$，根据 $pos$，得到原数组中的下标为 $1$，则左端点为 $1$。先求得左端点对应的数字 $\le 3$ 的子串数量为 $pre[t-1]$ 即 $pre[2]=3$，那么 $k-3=2$，意思就是求的这个子串是以数字 $3$ 的位置为左端点的第 $2$ 个子串，那么右端点自然就可以得出是 $1+2-1=2$，答案就是 `1,2`。

二分求第一个大于等于 $k$ 的数，可以用 `lower_bound` 来求。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define _rep(i,a,b) for (int i=(a);i<=(b);++i)

const int N=300005;

int n,q;
int arr[N];
int b[N],pre[N];
int pos[N];

signed main() {
    scanf("%lld %lld",&n,&q);
    _rep(i,1,n) scanf("%lld",&arr[i]);
    _rep(i,1,n) pos[arr[i]]=i;
    _rep(i,1,n) b[arr[i]]=n-i+1;
    _rep(i,1,n) pre[i]=pre[i-1]+b[i];
    while (q--) {
        int k;
        scanf("%lld",&k);
        int t=lower_bound(pre+1,pre+1+n,k)-(pre+1)+1;
        int p=pos[t],bias=k-pre[t-1];
        printf("%lld %lld\n",p,p+bias-1);
    }
    return 0;
}

---

## 作者：linjinkun (赞：0)

做法显然，用一个数组 $f$ 记录下来以每一个数开头的子串数量，然后排个序（以当前的 $a_i$ 排序），对于每一个询问，二分属于哪个 $l$ 开头，然后再算出 $r$ 就行了。

### 分几部分给出代码：

求出 $t$：
```cpp
for(int i = 1;i<=n;i++)
{
	t[i].x = n-i+1;//t是一个结构体数组，t[i].x表示的是以i开头的
	t[i].id = i;//t[i].id表示的是这个子串的开头（因为后面要排序）
}
```
排序函数：
```cpp
int cmp(node x,node y)
{
	return a[x.id]<a[y.id];
}
```
求前缀和（为之后的二分埋下伏笔）：
```cpp
for(int i = 1;i<=n;i++)
{
	sum[i] = sum[i-1]+t[i].x;
}
```
二分（重点！！）：
```cpp
while(q--)
{
	long long x;//必须开long long 
	scanf("%lld",&x);
	int l = 1,r = n,ans = 0;
	while(l<=r)
	{
		int mid = l+r>>1;
		if(sum[mid]>=x)//看x属于哪个块
		{
			ans = mid;
			r = mid-1;
		}
		else
		{
			l = mid+1;
		}
	}
	int l1 = t[ans].id;
	int r1 = l1+x-sum[ans-1]-1;
	printf("%d %d\n",l1,r1);
}
```
全部代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5+5;
struct node
{
	int x;
	int id;
}t[N];
int a[N];
long long sum[N];
int cmp(node x,node y)
{
	return a[x.id]<a[y.id];
}
signed main()
{
	int n,q;
	scanf("%d %d",&n,&q);
	for(int i = 1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i = 1;i<=n;i++)
	{
		t[i].x = n-i+1;
		t[i].id = i;
	}
	sort(t+1,t+n+1,cmp);
	for(int i = 1;i<=n;i++)
	{
		sum[i] = sum[i-1]+t[i].x;
	}
	while(q--)
	{
		long long x;
		scanf("%lld",&x);
		int l = 1,r = n,ans = 0;
		while(l<=r)
		{
			int mid = l+r>>1;
			if(sum[mid]>=x)
			{
				ans = mid;
				r = mid-1;
			}
			else
			{
				l = mid+1;
			}
		}
		int l1 = t[ans].id;
		int r1 = l1+x-sum[ans-1]-1;
		printf("%d %d\n",l1,r1);
	}
	return 0;
}
```

---

## 作者：Double_Light (赞：0)

假设把 $\dfrac{n(n+1)}{2}$ 个子串按字典序从小到大排序，那么由于定义，对于任意 $i<j$，$i$ 开头子串的肯定排在 $j$ 开头的前面。同时假设 $a_i=j$，则 $j$ 开头的所有子串一定是 $a_{i\sim i},a_{i\sim i+1},a_{i\sim i+2},\dots,a_{i\sim n}$。同样由于定义，对于任意 $k\leq i<j$，$a_{k\sim i}$ 一定排在 $a_{k\sim j}$ 前面。

所以考虑记录 $i$ 开头的子串的个数 $b_i$，然后对 $b_i$ 做前缀和，记作 $s_i$。显然 $s$ 数组是单调递增的，所以可以二分子串开头的字符，然后就可以用 $k$ 减去 $s_\text{mid}$ 来计算出结尾的字符位置。


```cpp
#include<iostream>
#define int long long
using namespace std;
int n,q,a[300005],b[300005],sum[300005],k,c[300005];
signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[a[i]]=n-i+1;
		c[a[i]]=i;
	}
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+b[i];
	for(int i=1;i<=q;i++){
		cin>>k;
		int l=0,r=n,mid,ans,man;
		while(l<=r){
			mid=(l+r)/2;
			if(k<=sum[mid]){
				r=mid-1;
				ans=sum[mid-1];
				man=mid;
			}
			else l=mid+1;
		}
		k-=ans;
		cout<<c[man]<<' '<<c[man]+k-1<<endl;
	}
	return 0;
}
```

---

## 作者：Tiger_Rory (赞：0)

给大家提供一个相对简单的做法，希望能帮助到大家。

第一次写黄题题解，如有不足还请指出。

由于我们要排序的是子串，所以子串首位越小，排名越靠前，所以我们可以先对序列进行一次排序，在此之前记下序列各元素原来的下标。

接着，因为从子串首位的下标 $i$ 开始可以形成 $n-i+1$ 个子串，并且长度越长，排名越靠后，所以我们可以认为序列中以这一位为首位形成的子串占据了 $n-i+1$ 个排名。这样，我们将排名累加，然后就可以将所有子串按照子串首位划分成 $n$ 个排名区间。

回答询问时，如果询问在某一区间内，就从这个区间对应的子串首位原下标开始一位一位往后找末尾下标就好了。

当然，这个做法要求询问的排名单调递增，所以这是个离线做法，需要将每个询问进行排序，然后逐一求解。

如果还有疑问，可以看看代码。


```cpp
#include<bits/stdc++.h>
#define MAXN 300005
#define int long long
//不开long long只有45pts
using namespace std;

int n, q; 
int tot;

struct number {
	int id, num, st, nd; 
}dp[MAXN], ques[MAXN], ans[MAXN];  
//id:下标 num:值
//st&nd:ans数组的前后两项，即输出的l和r
//声明:本程序和dp无关
bool cmp(number a, number b) {
	if(a.num != b.num) return a.num < b.num; 
	return a.id < b.id; 
}
//排序
signed main() {
	ios::sync_with_stdio(false); 
	cin.tie(0), cout.tie(0); 
	cin >> n >> q; 
	for(int i = 1; i <= n; i++) {
		cin >> dp[i].num; 
		dp[i].id = i; 
	}
	for(int i = 1; i <= q; i++) {
		cin >> ques[i].num; 
		ques[i].id = i; 
	} 
	sort(dp + 1, dp + n + 1, cmp);
	sort(ques + 1, ques + q + 1, cmp); 
	for(int i = 1, j = 1; i <= n, j <= q; i++) {
		int k = n - dp[i].id + 1; //从i开始可以产生k个子串，占据k个排名
		tot += k; //累加排名
		int kkk = tot - k + 1; //本区间开始的位置
		while(ques[j].num <= tot) { //如果询问在区间范围内
			ans[ques[j].id].st = dp[i].id; //记录l
			ans[ques[j].id].nd = dp[i].id + ques[j].num - kkk; //记录r，就是一位一位往后找末尾下标
			j++; //询问的下标往后加
			if(j>q) break; 
		}
	}
	for(int i = 1; i <= q; i++) cout << ans[i].st << ' ' << ans[i].nd << '\n';
    //输出
	return 0; 
}
```

---

## 作者：lcfollower (赞：0)

蒟蒻赛时没打，赛后补题用了二分，但是**听说**可以不用二分？

令 $a_i$ 表示 $i$ 出现的位置，那么对于第 $i$ 个数而言，可以产生 $n - a_i + 1$ 个子串，令其为 $b_i$。

然后我们需要查找到合适的 $k$，但是暴力会超时，于是考虑前缀和 $pre_i = \sum_{j = 1}^i b_j$。

显然 $pre_i$ 单调不降，于是二分出合适的 $pos$，那么第 $k$ 小的子串左端点为 $a_{pos}$。

明显从 $a_{pos}$ 后面提取越多的字符，字符串的字典序也就越大，所以第 $k$ 小的子串右端点为 $a_{pos} + (k - pre_{pos - 1}) - 1$。

时间复杂度为 $\mathcal O(Q\log N)$。

```cpp
#include <bits/stdc++.h>

# define int long long
# define rint register int

using namespace std;

const int N = 3e5 + 10;
int n ,Q ,x ,pre[N] ,a[N] ,b[N];

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL);
  cin >> n >> Q;
  for(rint i = 1 ;i <= n;i ++)
    cin >> x ,a[x] = i;
  for(rint i = 1 ;i <= n;i ++)
    b[i] = n - a[i] + 1;
  for(rint i = 1;i <= n; i ++) pre[i] = pre[i - 1] + b[i];//预处理 pre。
  while(Q --){
    int k;
    cin >> k;
    int l = 1 ,r = n ,pos = 0;
    while(l <= r){//二分。
      int mid = ((l + r) >> 1ll);
      if(pre[mid] < k) l = mid + 1;
      else r = mid - 1, pos = mid;
    }
    cout << a[pos] << ' ' << a[pos] + (k - pre[pos - 1]) - 1 << '\n';//计算左端点以及右端点。
  }
  return 0;
}
```

---

## 作者：guer_loser_lcz (赞：0)

# 题解
## 思路
显然，子串字典序开头是从 $1$ 到 $n$ 。

对于一个以第 $i$ 个数开头的子串能贡献 $n - i + 1$ 个子串。

按 $1$ 到 $n$ 的顺序统计以 $i$ 开头的字串是的几个到第几个，建议配合代码理解。

然后二分找。
## 代码
输入：
```cpp
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i].val;//数值
		a[i].id=i;//第i个
		a[i].lon=n-i+1;//贡献子串个数
	}
```
处理：

```cpp
	sort(a+1,a+n+1,cmp);//按大小排序
	for(int i=1;i<=n;i++){
		a[i].fir=ans+1;//单个i是第几个
		ans+=a[i].lon;//加上贡献个数
	}
```
二分求答案：

```cpp
	for(int i=1;i<=q;i++){
		long long x;
		cin>>x;
		int l=1,r=n;
		bool f=0;
		while(l<=r){
			int mid=(l+r)/2;//二分
			if(x>=a[mid].fir&&(x<a[mid+1].fir||mid==n)){如果第x个比以mid开头的大且比mid+1小，那么x在mid贡献的子串中
				cout<<a[mid].id<<" "<<a[mid].id+x-a[mid].fir<<endl;
				break;//跳出
			}
			if(x>a[mid].fir)l=mid+1;
			else r=mid-1;
		}
	}
```

---

## 作者：lzbzl (赞：0)

# P10995 Substring 题解

非常好的二分题，使我的大脑旋转。

### 分析

题目要求输出字典序第 $k$ 小的序列的 $l$ 和 $r$。不难发现只需要将数组中数的下标记录下来记为 $l$，按数的大小排序后通过计算就能得出 $r$。

但题目的数据范围十分的大，直接查找第 $k$ 小必定会超时，由于字典序具有单调上升性，我们便可以用二分解决。我们引入前缀和记录到 $a_i$ 时共有多少个序列，然后进行二分。时间复杂度为 $O(q\log n)$。
贴上代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m;

struct yee
{
    int a,b,c;
}a[300005];

bool cmp(yee x,yee y){return x.a<y.a;}

signed main()
{
    a[0].a=a[0].b=a[0].c=0;
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i].a),a[i].b=i,a[i].c=n-i+1;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
        a[i].c=a[i-1].c+a[i].c;
    while(m--)
    {
        long long x;
        scanf("%lld",&x);
        int l=0,r=n;
        while(l+1<r)
        {
            int mid=(l+r)>>1;
            if(a[mid].c<x)l=mid;
            else r=mid;
        }
        cout<<a[l+1].b<<" "<<a[l+1].b+x-a[l].c-1<<"\n";
    }
    return 0;
}

```
感谢管理员审核。

---

## 作者：WhiteNight__ (赞：0)

## [P10995 【MX-J3-T2】Substring](https://www.luogu.com.cn/problem/P10995) 题解

### 思路
容易想到，因为求的字典序是一段连续的区间，且没有重复的数字，所以可以推导出**以较小的数字开头的区间字典序小于以较大数字开头的区间**。并且通过发现，**以相同数字开头的区间长度较短的区间字典序较小**。

举例：
- $[1,4,6,7,9] < [4,6,7,9,5]$
- $[1,4] < [1,4,6] < [1,4,6,7] < [1,4,6,7,9]$

那么我们便可以想到这个解法：用一个数组 $r$ 来记录每一个数字出现的位置，从 $1$ 开始枚举，统计每次枚举的最大字典序排名，若某次枚举中最大字典序排名不低于 $k$，则以该数为开头的区间内一定包含答案区间，只需计算右区间即可。

### Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define ll long long
int n , q , k , g , a[300050] , r[300050];
int main()
{
	cin >> n >> q;
	for(int i = 1 ; i <= n ; i ++)
	{
		cin >> a[i];
		r[a[i]] = i;
	}
	while (q --)
	{
		cin >> k; g = 0; // 用g来记录枚举时的最大字典序排名
		for(int i = 1 ; i <= n ; i ++)
		{
			if(g+n-r[i]+1>=k)
			{
				printf("%d %d\n",r[i],r[i]+k-g-1);
				break;
			}
			g+=n-r[i]+1;
		}
	}
}
```
当然这么大的数据是过不了的，考虑优化。可以先预处理出 $g$ 数组，询问时再用二分查找即可。

### Code

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define ll long long
ll N , Q , k , x , a[300050] , r[300050] , g[300050];
// 三个数组
// a[]数组表示题目输入
// r[]数组表示数字i在a数组中的位置r[i]
// g[]数组表示比以数字i开头的区间字典序小的数有g[i]个

ll search (ll l , ll r) // 二分查找
{
	ll mid;
	while (l<r)
	{
		mid = l+(r-l+1)/2;
		if(g[mid]>=k) // 答案过大，缩小范围
			r = mid-1;
		else l = mid;
	}
	return r;
}

int main()
{
	cin >> N >> Q;
	for(int i = 1 ; i <= N ; i ++)
	{
		cin >> a[i];
		r[a[i]] = i;
	}
	for(int i = 2 ; i <= N ; i ++)
		g[i] = g[i-1]+N-r[i-1]+1; // 递推求g[]数组
	while (Q --)
	{
		cin >> k;
		x = search(1,N); // 查找以数字x开头的区间
		printf("%lld %lld\n",r[x],r[x]+k-g[x]-1);
	}
}
```

---

## 作者：jjy2023 (赞：0)

# P10995 【MX-J3-T2】Substring
## Description：
给你一个数列 $a$，求字典序第 $k$ 小的子串的左右端点。
## Solution：
可以使用前缀和来解决。记录每一个数的位置，将原数组进行排序，再将所有情况进行前缀和。在枚举时，注意到 $O(mn)$ 的算法会超时，所以可以进行二分；枚举当左端点为 $l$，右端点为 $r$ 时的情况总数为多少，最后再输出 $l$ 以及下一项的前缀和 $-$ 该项的前缀和再 $-1$ 即可。最终时间复杂度为 $O(m\log n)$。
## Code：

```cpp
#include<bits/stdc++.h>
#define int long long//注意要开longlong
using namespace std;
int n,m,a[300005],aa[300005],b[300005],c[300005],d[300005];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],aa[i]=a[i],b[a[i]]=i;
	sort(aa+1,aa+n+1);
	for(int i=1;i<=n;i++) c[i]=n-b[aa[i]]+1,d[i]=d[i-1]+c[i];
	for(int i=1;i<=m;i++)
	{
		int x,sum=0,flag=0;
		cin>>x;
		int l=1,r=n;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(d[mid]==x) {cout<<b[mid]<<' '<<n<<endl;flag=1;break;}
			else if(d[mid]>x) r=mid-1;
			else l=mid+1;
		}
		if(flag==0)
		{
			sum=d[r];
			cout<<b[l]<<' '<<b[l]+(x-sum-1)<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

这题有一个障眼法。其实我们注意到，每一个数都是不一样的。这也就意味着，$a_l$ 更小者一定排在更前面。而 $a_l$ 相等的情况下，$r$ 更小者靠前。

至此，思路已经十分明显了：计算出以 $a_l$ 开始的子序列在排序后的开始与结束位置，然后进行二分即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[300005],p[300005],t,cnr[300005],cnl[300005];
signed main(){
	ios::sync_with_stdio(0); cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i],p[a[i]]=i;
	for(int i=1;i<=n;++i) 
		cnr[i]=cnr[i-1]+(n-p[i]+1),
		cnl[i]=cnr[i-1]+1;
	while(m--){
		cin>>t;
		int pt=upper_bound(cnl+1,cnl+n+1,t)-cnl-1;
		int mr=t-cnl[pt];
		cout<<p[pt]<<" "<<p[pt]+mr<<endl;
	}
} 
```

---

## 作者：lostxxx (赞：0)

# 题目分析

首先我们了解到题目让我们求的是由字典序从小到大排序的第 $k$ 个子串，由于是按照字典序排序的，所以以 $1$ 开头的子串排在最前面，以 $2$ 开头的子串肯定排在以 $1$ 开头的子串的后面，所以我们从这个点入手。

我们注意到，题目给出的是一个排列，所以数字 $1$ 至 $n$ 都只会出现一次。

首先我们利用 $pos_i$ 表示数字 $i$ 在原数组 $a$ 中出现的位置，那么以数字 $i$ 开头的子串只有 $n-pos_i+1$ 个，用数组 $siz$ 存下来。在利用一个前缀数组 $s_i$ 表示以 $1$ 至 $i$ 开头的所有子串的数量。然后我们在数组 $s$ 上进行二分，找第一个大于等于 $k$ 的元素的下标 $x$，然后输出 $pos_x$ 和 $pos_x+k-s_{x-1}$。

代码如下。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[300100];
ll pos[300100];
ll siz[300100];
ll s[300100];
ll n,q;
ll x;
int main(){
    cin>>n>>q;
    for (int i=1;i<=n;i++){
        cin>>a[i];
        pos[a[i]]=i;
        siz[a[i]]=n-i+1;
    }
    for (int i=1;i<=n;i++){
        s[i]=s[i-1]+siz[i];
        //cout<<siz[i]<<endl;
    }
    while(q--){
        cin>>x;
        ll po=lower_bound(s+1,s+n+1,x)-s;
        //cout<<po<<endl;
        ll tmp=x-s[po-1];
        cout<<pos[po]<<" "<<tmp+pos[po]-1<<endl;
    }
}
```

---

## 作者：tanghg (赞：0)

发现对于排列，只有子串的第一个元素的大小对字典序有影响。所以排序后的子串将变成从 $1$ 的位置一直到 $n$ 的所有子串，之后从 $2$ 的位置开始，最后到 $n$ 的位置。所以记录从 $i$ 的位置开始的子串数量，然后记录前缀和，之后找到一个前缀和最接近且不超过 $k$ 的（不妨设为 $f_i$， $i$ 的位置为 $p_i$），则显然子串为 $[p_i,p_i+k-f_{p-1}-1]$。时间复杂度为 $O(q\log n)$。
```cpp
#include <bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
const ll MAXN=3e5+5;
ll a[MAXN],v[MAXN],f[MAXN],id[MAXN];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll n,q;
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        v[a[i]]=n-i+1;
        id[a[i]]=i;
    }
    for(int i=1;i<=n;++i){
        f[i]=f[i-1]+v[i];
    }
    while(q--){
        ll k;
        cin>>k;
        ll q=lower_bound(f+1,f+n+1,k)-f;
        cout<<id[q]<<" "<<id[q]+k-f[q-1]-1<<endl;
    }
    return 0;
}
```

---

## 作者：_Jocularly_ (赞：0)

### 字典序
因为是从 $1$ 到 $n$ 的排列，观察按照字典序排序之后的特点，发现字典序可按照以下方式构造出有序子串。首先找到当前数组最大的数，然后从这个位置往后依次连接后面的元素，例如 $\text{3 1 2}$，最大的数字是 $\text{1}$，第一个为 $\text{1}$，第二个为它和后面连接而成，即为 $\text{1 2}$，直到没有数了为止，删掉这个数，重复上文过程即可。得到的结果即为按照字典序升序排列的子串数组。

### 算法一
我会模拟！根据以上思路，我们可以采用暴力算法，将每个数和位置存下来，排序后枚举，依次存到 $ans$ 数组里，答案即为 $k$ 位置上的子串。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int cnt;
struct P{
    int id;
    int val;
}a[4500005];
int l[4500005],r[4500005];
int cmp(P a,P b){
    return a.val < b.val;
}
int main(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i].val;
        a[i].id = i;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        int pos = a[i].id;
        for(int j=pos;j<=n;j++){
            l[++cnt] = pos;
            r[cnt] = j;
        }
    }
    while(m--){
        int k;
        cin >> k;
        cout << l[k] << " " << r[k] << endl;
    }
    return 0;
}
```

排序时间复杂度 $O(n \log n)$，每次枚举子串 $O(n^2)$，总计为 $O(n(\log n + n))$，预计得分 $45$ 分。

### 算法二
我会数学！针对算法一进行优化，我们将每次子串的第一个值作为分隔，抽象成一个四元组 $(l,r,h,t)$，其中 $l$ 和 $r$ 表示的是此区间的起止位置，$h$ 和 $t$ 表示的是此区间中最小和最大的等级值。

此时，假设查找的等级为 $k$，我们求得答案的方法即为，寻找一个区间 $i$，满足 $l_{i} \le k \le r_{i}$，此时能够保证答案一定在这个区间中。观察发现，这个区间中按照等级排序的区间为 $[l_{i},l_{i}] ,[l_{i},l_{i}+1],...,[l_{i},l_{i}+x],...,[l_{i},r_{i}]$，对应的等级为 $h,h+1,...,h+x,...,t$，那么我们发现此时如果我们要寻找等级为 $k$ 的，只要求得 $x$ 即可，我们令 $h + x = k$，那么 $x = k - h$，那么区间位置即为 $[l_{i},l_{i}+x]=[l_{i},l_{i}+(k-h)]$。

观察发现，四元组的数量取决于起始元素值的数量，因为是排列，数量即为 $n$，那么排序复杂度不变，为 $O(n \log n)$，每次查询最劣为 $O(n)$，总计为 $O(n( \log n + m))$，预计得分 $60$ 分，能通过 $m$ 较小的部分。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int cnt,tot;
int flag = 1;
int now;
struct P{
    int id;
    int val;
}a[300005];
struct node{
    int l,r;//位置
    int h,d;//级别
}b[300005];
int cmp(P a,P b){
    return a.val < b.val;
}
int find(int k){
    for(int i=1;i<=tot;i++){
        if(b[i].h <= k && k <= b[i].d) return i;
    }
    return -1;
}
signed main(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i].val;
        a[i].id = i;
        if(a[i].val != i) flag = 0;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        int pos = a[i].id;
        b[++tot].l = pos;
        b[tot].r = n;
        b[tot].h = now + 1;
        now += n - pos + 1;
        b[tot].d = now;
    }
    while(m--){
        int k;
        cin >> k;
        int pos = find(k);
        int l = b[pos].l;
        int r = l + k - b[pos].h;
        cout << l << " " << r << endl;
    }
    return 0;
}
```

### 算法三
我会二分！观察代码发现，能够优化的似乎只有 $O(n)$ 的查找了，猜想它具有单调性。证明：设元素下标为 $i$，因为字典序排序后等级递增，所以 $i$ 越大等级区间所包含的范围在数轴上越靠右，单调性成立。那么我们只需要用二分找到满足 $h \le k$ 的第一个位置即可，计算方法不变。

单词查询为 $O(\log n)$，回答总共 $O(m \log n)$，总计为 $O((n + m)\log n)$，预计得分 $100$ 分。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int tot;
int flag = 1;
int now;
struct node{
    int id;
    int val;
}a[300005];
int l[300005],r[300005];
int h[300005],t[300005];
int cmp(node a,node b){
    return a.val < b.val;
}
int find(int k){
    for(int i=1;i<=tot;i++){
        if(h[i] <= k && k <= t[i]) return i;
    }
    return -1;
}
int binary_find(int k){
    int l = 1,r = tot;
    while(l < r){
        int mid = (l + r + 1) / 2;
        if(h[mid] <= k) l = mid;
        else r = mid - 1; 
    }
    return l;
}
signed main(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i].val;
        a[i].id = i;
        if(a[i].val != i) flag = 0;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        int pos = a[i].id;
        l[++tot] = pos;
        r[tot] = n;
        h[tot] = now + 1;
        now += n - pos + 1;
        t[tot] = now;
    }
    while(m--){
        int k;
        cin >> k;
        int pos = binary_find(k);
        //int pos = lower_bound(h+1,h+1+tot,k) - h;
        //int pos = upper_bound(t+1,t+1+tot,k) - t;
        //int pos = find(k);
        int be = l[pos];
        int ed = be + k - h[pos];
        cout << be << " " << ed << endl;
    }
    return 0;
}
```

---

## 作者：TemplateClass (赞：0)

文中记 $\max(i)$ 为序列 $a$ 中第 $i$ 大的元素的位置。

---

注意到字典序的比较的关键是从第 $1$ 个元素开始比较，所以 $a$ 中的某个元素越小，以它作为首项的子串在字典序中就越靠前。

然后考虑相同的首项。显然对于任意两个拥有相同首项的子串，其中的某一个一定是另一个的前缀。所以我们得到，相同首项的子串，长度越长，在字典序中就越靠后。

由此，我们得到字典序：

- $\left(a _ {\max(1)}\right)$，$\left(a _ {\max(1)}, a _ {\max(1) + 1}\right)$，$\cdots$，$\left(a _ {\max(1)}, a _ {\max(1) + 1}, \cdots, a _ n\right)$。

- $\left(a _ {\max(2)}\right)$，$\left(a _ {\max(2)}, a _ {\max(2) + 1}\right)$，$\cdots$，$\left(a _ {\max(2)}, a _ {\max(2) + 1}, \cdots, a _ n\right)$。

- $\left(a _ {\max(3)}\right)$，$\left(a _ {\max(3)}, a _ {\max(3) + 1}\right)$，$\cdots$，$\left(a _ {\max(3)}, a _ {\max(3) + 1}, \cdots, a _ n\right)$。

- $\cdots$

- $\left(a _ {\max(n)}\right)$，$\left(a _ {\max(n)}, a _ {\max(n) + 1}\right)$，$\cdots$，$\left(a _ {\max(n)}, a _ {\max(n) + 1}, \cdots, a _ n\right)$。

现在我们已经完全知道了字典序，接下来思考如何快速地查询这些区间。

我们可以采用类似于前缀和的方式，记录下 $a _ 1 \sim a _ i$ 所产生的总序列长度。这样给出 $k$ 后二分查找即可。其中，$\max(i)$ 对应的子串长度是 $n - \max(i) + 1$。（$+ 1$ 是因为要算上只有 $\max(i)$ 单独一个元素的子串）（代码中的 `startpos` 就是这个作用，但是名字似乎取得不好……）

通过计算 $k$ 和查询到的长度差异，我们就能知道这个子串的长度了。注意子串数量可能很多，`int` 开不下。

代码中 `index[i]` 即代表 $\max(i)$。

```cpp
int n, q, a[N], index[N];
unsigned long long startpos[N];

void solve(){
	std::cin >> n >> q;
	for(int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		index[a[i]] = i;
	}
	
	for(int i = 1; i <= n; ++i) {
		startpos[i] = startpos[i - 1] + (n - index[i] + 1);
	}
	
	while(q--) {
		unsigned long long k; std::cin >> k;
		int pos = std::lower_bound(startpos + 1, startpos + n + 1, k) - startpos;
		unsigned long long delta = k - startpos[pos - 1] - 1;
		std::cout << index[pos] << " " << index[pos] + delta << "\n";
	}
}
```

---

## 作者：xuan_gong_dong (赞：0)

## 题面

[P10995 【MX-J3-T2】Substring](https://www.luogu.com.cn/problem/P10995)

## 分析

对于每一个数字，记录以它为前缀开始位置的子串个数有 $n-i+1$。以权值排序，并求得子串个数的前缀和。
在求得的前缀和中进行二分，即可求得答案。

时间复杂度为 $O(n \log n)$。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int pre[300010];
int a[300010];
int n,q;
int xgd[300010];
map<int,int> hys;
signed main()
{
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		pre[a[i]]=n-i+1;
		xgd[a[i]]=i;
	}
	for(int i=1;i<=n;i++)
	{
		int tmp=xgd[i];
		pre[i]+=pre[i-1];
		hys[pre[i]]=tmp;
//		cout<<pre[i]<<' '<<tmp<<endl;
	}
	while(q--)
	{
		int id;
		scanf("%lld",&id);
		int num=lower_bound(pre+1,pre+n+1,id)-pre;
		int tmp=pre[num-1];
		num=hys[pre[num]];
		
//		cout<<"num="<<num<<' '<<tmp<<' '<<id<<endl;
//		num--;
		printf("%lld %lld\n",num,num+id-tmp-1);
	}
	return 0;
}
```

---


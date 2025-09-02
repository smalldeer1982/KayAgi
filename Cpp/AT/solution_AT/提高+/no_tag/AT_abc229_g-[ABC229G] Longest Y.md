# [ABC229G] Longest Y

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc229/tasks/abc229_g

`Y` と `.` からなる文字列 $ S $ が与えられます。

次の操作を $ 0 $ 回以上 $ K $ 回以下行うことができます。

- $ S $ の隣り合う $ 2 $ 文字を入れ替える

操作後に、`Y` を最大で何個連続させることができますか？

## 说明/提示

### 制約

- $ 2\ \leq\ |S|\ \leq\ 2\ \times\ 10^5 $
- $ S $ の各文字は `Y` または `.` である
- $ 0\ \leq\ K\ \leq\ 10^{12} $
- $ K $ は整数である

### Sample Explanation 1

$ S $ の $ 6,7 $ 文字目および $ 9,10 $ 文字目を入れ替えて `YY....YYY..` とすると、$ 7 $ 文字目から $ 9 $ 文字目で `Y` が $ 3 $ 個連続しています。 `Y` を $ 4 $ 個以上連続させることはできないので、答えは $ 3 $ です。

## 样例 #1

### 输入

```
YY...Y.Y.Y.
2```

### 输出

```
3```

## 样例 #2

### 输入

```
YYYY....YYY
3```

### 输出

```
4```

# 题解

## 作者：_Tooler_Fu_ (赞：5)

题解没有 $O(n)$ 解法，我来一发 $O(n)$ 的。

很显然的，答案区间一定是**一段开头结尾**都为 $Y$ 的。

关键就在于如何找这**一整段**。

由于这一整段是连续的，且答案满足单调性，那我们就可以利用**双指针**，枚举答案区间把 $Y$ 聚在一起的最小代价，再与 $k$ 相匹配，即能判断可行性与求出答案。

假定现在的区间为 $[l,r]$，那么如果最小的代价小于 $k$，就将 $r$ 向右扩展同时记录答案，否则将 $l$ 向右扩展。

但如何计算代价呢？~~很简单。~~

初中数学告诉我们：
1. 数轴上有奇数个点，所有点都要聚到其中一个点上，要使所有点移动距离和最小，则应当选中间那个点。
1. 数轴上有偶数个点，所有点都要聚到其中一个点上，要使所有点移动距离和最小，则应当选中间那两个点。

所以我们应该在移动指针时顺便记录在枚举的区间内 $Y$ 所在的位置，求出中间点的位置，令该位置为 $g$，让坐标小于 $g$ 的点依次排在 $g$ 之前，大于 $g$ 的点依次排在 $g$ 之后，求出该过程代价即可。（因为我太蒻了，只会用前缀和和 deque 完成）

这样就是 $O(n)$ 的啦！

代码如下：

```cpp
// Problem: 
//     [ABC229G] Longest Y
//   
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc229_g
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//我是废物，我爱贺题！！！
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,x,y,z) for(long long i=x;i<=y;i+=z)
#define fd(i,x,y,z) for(long long i=x;i>=y;i-=z) 
ll n,k;
bool vis[200005];
ll sm[200005];
char s[200005];
ll l,r;
ll ans=0;
deque<ll> q;
bool check(ll a,ll b){
	ll tt=(1LL<<50);
	ll hh=q.size();
	ll ff=hh/2+(hh%2);
	ll gg=q[ff-1];
	tt=min(tt,(gg+(gg-ff+1))*ff/2-sm[gg]+sm[a-1]+sm[b]-sm[gg]-(gg+1+(gg+(hh-ff)))*(hh-ff)/2);
	if(hh%2==0){
		gg=q[ff];
		tt=min(tt,(gg+(gg-ff))*(ff+1)/2-sm[gg]+sm[a-1]+sm[b]-sm[gg]-(gg+1+(gg+ff-2))*(ff-2)/2);
	}
	if(tt<=k){
		return true;
	}
	else{
		return false;
	}
}
int main() {
	scanf("%s",s+1);
	scanf("%lld",&k);
	n=strlen(s+1);
	f(i,1,n,1){
		sm[i]=sm[i-1]+(s[i]=='Y'?i:0);
	}
	l=r=1;
	while(r<=n){
		while(!q.empty()&&q.front()<l){
			q.pop_front();
		}
		if(s[l]=='.'){
			if(l==r){
				r++;
			}
			l++;
		}
		else{
			if(s[r]=='Y'&&!vis[r]){
				q.push_back(r);
				vis[r]=1;
			}
			if(check(l,r)){
				ll ttt=q.size();
				ans=max(ans,ttt);
				r++;
			}
			else{
				l++;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

~~但是常数很大喜提最劣解。~~

---

## 作者：loser_seele (赞：5)

很强的思维题。

首先将 $ Y $ 的下标塞进一个数组里，然后减去其在新数组里的下标，于是显然可以将问题转化为：让一个数组 $ +1 $ 或 $ -1 $ （对应移动操作）若干次，问最多有多少个数能变得相同（对应最长连续长度）。

显然答案有单调性，于是二分答案。

问题转化为让一个数组 $ +1 $ 或 $ -1 $ 若干次是否能让恰好 $ k $ 个数字相同。

显然选取一个连续子序列总是最优，于是考虑一个子问题：将一个有序数组变为相同元素的代价。

这就是一个经典套路了，选择中位数总是最优，否则可以通过挪动到中位数获得更有答案。通过预处理前缀和可以 $ \mathcal{O}(1) $ 解决。

而对于上一个问题，暴力枚举区间起点，显然是 $ \mathcal{O}(n) $ 的。总时间复杂度 $ \mathcal{O}(n\log{n}) $，因为需要二分答案，可以通过。

代码：

```cpp
#import<bits/stdc++.h>
using namespace std;
long long k,a[200010],n,cnt,s[200010],l,r,mid,sum;
string ch;
bool check(int x)
{
    for(int i=1;i<=n-x+1;i++)
    {
    	sum=a[i+x/2]*(x/2)-(s[i+x/2-1]-s[i-1])+(s[i+x-1]-s[i+x/2])-a[i+x/2]*((x-1)/2);
    	if(sum<=k) 
    	return 1;
    }
    return 0;
}
int main()
{
    cin>>ch;
    scanf("%lld",&k);
    for(int i=0;i<ch.length();i++)
    {
    	if(ch[i]=='Y')
    	{
    		a[++n]=cnt;
    		cnt=0;
    	}
    	else 
    	cnt++;
    }
    for(int i=1;i<=n;i++)
    	a[i]+=a[i-1];
    for(int i=1;i<=n;i++)
    	s[i]=s[i-1]+a[i];
    l=0;
    r=n;
    while(l<r)
    {
    	mid=(l+r+1)>>1;
    	if(check(mid)) 
    	l=mid;
    	else 
    	r=mid-1;
    }
    printf("%lld",l);
}
```


---

## 作者：_Hugoi_ (赞：2)

## 题意
给定一个字符串 $S$，由 `Y` 和 `.` 构成。

现在最多进行 $k$ 次操作，每次可以交换两个相邻的字符。

求操作后，最长连续字符 `Y` 的长度。

## 思路

不难发现答案具有一种单调性，即比答案更短的所有区间一定满足要求，且比答案更长的所有区间一定不满足要求。

于是可以二分……

但是发现，对于一个固定的左端点，答案同样具有单调性。

于是可以双指针，比二分少个 $\log$。

现在的问题就是对于一个给定的区间，如何 $O(n)$ 求出最优答案。

结论：将区间所有 `Y` 移动至所有 `Y` 的中位数处最优。

首先最优方案中一个 `Y` 一定不能跨越另一个 `Y`。

所以确定了要把所有 `Y` 移动至的位置后答案就确定了。

称这个位置为决策点。

若结论错误，不妨假设决策点在中位数的右侧。

若决策点在中位数和下一个 `Y` 之间，那么决策点每右移 1，中位数左侧点都多右移 1，中位数右侧点都少左移 1，中位数右移 1。

显然不优。

若区间内 `Y` 的个数为偶数，则任取一个中位数即可，因为决策点为两中位数及中间位置时答案相同。

所以现在知道了决策点位置，考虑 $O(1)$ 计算答案。

类似前缀和，可以预处理出 **之前所有 `Y` 到当前位置的距离和** 以及 **当前点及之前的所有 `Y` 的个数**；

类似地，可以搞出后缀的这个东西。

然后推亿推式子即可。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,k,pos[N],tot,ans,sop[N];
struct node{	
	int dis,cnt;
}pre[N],suf[N];
string s;
int calc(int l,int r){
	int mid=sop[(pos[l]+pos[r])/2];
	return pre[mid].dis-pre[l].dis-(pre[l].cnt-1)*(mid-l)-(pre[mid].cnt-pre[l].cnt)*(pre[mid].cnt-pre[l].cnt+1)/2+suf[mid].dis-suf[r].dis-(suf[r].cnt-1)*(r-mid)-(suf[mid].cnt-suf[r].cnt)*(suf[mid].cnt-suf[r].cnt+1)/2;
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	ios::sync_with_stdio(0);
	cin>>s>>k;
	n=s.size();
	s=" "+s;
	for(int i=1;i<=n;i++){
		pre[i].dis=pre[i-1].dis+pre[i-1].cnt;
		pre[i].cnt=pre[i-1].cnt;
		if(s[i]=='Y') pre[i].cnt++,pos[i]=++tot,sop[tot]=i;
		else pos[i]=tot;
	}
	pos[n+1]=pos[n]+1;
	for(int i=n;i>=1;i--){
		suf[i].dis=suf[i+1].dis+suf[i+1].cnt;
		suf[i].cnt=suf[i+1].cnt;
		if(s[i]=='Y') suf[i].cnt++;
	}
	for(int l=1,r=1;r<=n;l++){
		while(s[l]=='.') l++;
		if(r<l) r=l;
		while(r<=n&&calc(l,r)<=k){
			r++;
			while(s[r]=='.') r++;
		}
		ans=max(ans,pos[r]-pos[l]);
	}
	cout<<ans<<'\n';
}
```

---

## 作者：LEWISAK (赞：1)

考虑将 `Y` 单独拎出来，用数组存储他的下标，那么将第 $x$ 个 `Y` 转移至第 $y$ 个 `Y` 就需要 $a_x-b_y-1$ 次操作。

发现一个问题：

第一次从左移动至 $y$ 需要减 $1$，第二次从左移动需要减 $2$，以此类推。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/tln2gxbw.png)

这似乎是一个很麻烦的问题，我们的某知名 lyh 教授是通过指针（应该是吧）解决的。

但我有一个想法：

假若被转移点和参照点的路径中有别的 `Y` ,那么因为为了保证最优性，在被转移点左边的点必须先被转移！

听起来有点绕，上图！

![](https://cdn.luogu.com.cn/upload/image_hosting/xv28h1f0.png)

那么就可以直接用被转移点前面的 `Y` 的个数减参照点前面 `Y` 的个数即可算出应该减多少了：

此部分代码处理：

```cpp
for(int i=0;i<t.size();i++){
	if(t[i]=='Y'){
		a[++n]=i-n;
		sum[n]=sum[n-1]+a[n];
	}
}
```

接下来不难发现，经过我们巧妙的处理之后，我们将问题转换成了：

给定一个单调不降的序列，可以对其中的数 $+1$ 或 $-1$ （对应着向左或向右交换）求 $k$ 次操作后最多有几个数一样。

接下来又很容易想到：为了保证最优，一样的数一定是连续的，又很容易想到，让连续的一段数一样的最优参照点一定是中位数。

令 $i$ 为区间起点，$x$ 为长度，$sum$ 为前缀和，则转移需要的步数=

$$
a_{i+\frac{x}{2}}\times (\frac{x}{2})-(s_{i+\frac{x}{2}}-s_{i-1})+(s_{i+x-1}-s_{i+\frac{x}{2}-1})-a_{i+\frac{x}{2}}(\frac{x-1}{2}))

$$
解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/6abt2t2p.png)

这部分的代码处理：

```cpp
for(int i=1;i<=n-x+1;i++){
	if((a[i+x/2]*(x/2)-(sum[i+x/2]-sum[i-1])+(sum[i+x-1]-sum[i+x/2-1])-a[i+x/2]*((x-1)/2))<=k){
		return 1;
	}
}
```

然后又很容易想到，二分长度，枚举起点即可。时间复杂度 $O(n\log n)$。

# ACcode

```cpp
#include<bits/stdc++.h>
using namespace std;
string t;
int k,a[200100],n,sum[200100];
bool check(int x){
	for(int i=1;i<=n-x+1;i++){
		if((a[i+x/2]*(x/2)-(sum[i+x/2]-sum[i-1])+(sum[i+x-1]-sum[i+x/2-1])-a[i+x/2]*((x-1)/2))<=k){
			return 1;
		}
	}
	return 0;
}
signed main(){
	cin>>t>>k;
	for(int i=0;i<t.size();i++){
		if(t[i]=='Y'){
			a[++n]=i-n;
			sum[n]=sum[n-1]+a[n];
		}
	}
	int l=0,r=n;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)){
			l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
	cout<<r<<endl;
}
```

---

## 作者：Claire0918 (赞：0)

注意到答案具有单调性，即如果 $i$ 个连续的 $\texttt{Y}$ 可以在 $k$ 次操作内得到，那么任何 $i' < i$ 个连续的 $\texttt{Y}$ 都可以在 $k$ 次操作内得到。于是考虑二分。

我们有一种计算方式：将 $l$ 处的 $\texttt{Y}$ 移动，使得它与位于 $r$ 处的 $\texttt{Y}$ 连通的最少操作次数是 $\sum_{i = l}^{r} [s_i = \texttt{.}]$。考虑每一次操作的意义即可证明。

我们还有一个性质：将 $[l, r]$ 中所有的 $\texttt{Y}$ 移动，使得它们互相连通的最优方案是不移动位于中间位置的 $\texttt{Y}$，将两边的分别向中间移动。形式化地，我们记 $c = \sum_{i = l}^{r} [s_i = \texttt{Y}]$，那么我们不移动第 $\lfloor \frac{c}{2} \rfloor$ 个 $\texttt{Y}$，将其两侧的 $\texttt{Y}$ 向其移动。

证明考虑反证法。如果我们选定第 $i < \lfloor \frac{c}{2} \rfloor$ 个不移动，对比选取第 $j \in (i, \lfloor \frac{c}{2} \rfloor]$ 个不移动，显然后者更优，因为 $i$ 左侧的点比右侧少，而每次使 $i$ 增大每个左侧的点操作次数增加，每个右侧的点减少相同的操作次数，从而将 $i$ 增加时减少的操作次数比增加的更多，即 $i$ 增加更优。对于 $i$ 在中心右侧的情况可以类似证明。

综上，如果我们要判断 $x$ 是否可以成为答案，只需枚举 $l$，将 $[l, l + x - 1]$ 中的 $\texttt{Y}$ 向第 $\lfloor \frac{l + (l + x - 1)}{2} \rfloor$ 个 $\texttt{Y}$ 移动即可。

记 $a_i$ 表示 $s$ 中第 $i$ 个 $\texttt{Y}$ 前有几个 $\texttt{.}$，那么将第 $l$ 个 $\texttt{Y}$ 移动到第 $r$ 个的最少次数即为 $a_r - a_l$。记 $r = l + x - 1, mid = \lfloor \frac{l + r}{2} \rfloor$，那么 $[l, r]$ 的操作次数即为
$$
\begin{aligned}
& \sum_{i = l}^{mid} (a_{mid} - a_i) + \sum_{i = mid + 1}^{r} (a_i - a_{mid})\\
&= ((mid - l + 1) \times a_{mid} - \sum_{i = l}^{mid} a_i) + (\sum_{i = mid + 1}^{r} a_i - (r - mid) \times a_{mid})
\end{aligned}
$$

维护 $\{a_i\}$ 的前缀和即可 $\mathcal{O}(1)$ 计算上式。

如果存在一个 $l$ 使得上式小于等于 $k$，那么 $x$ 就是合法的答案，否则 $x$ 不合法。

二分 $x$ 即可，时间复杂度 $\mathcal{O}(n \log n)$。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxlen = 2e5 + 10;

char s[maxlen];
int n = 0;
long long k;
int a[maxlen];
long long pre[maxlen];

inline bool check(int x){
    for (int l = 1; l + x - 1 <= n; l++){
        const int r = l + x - 1, mid = l + r >> 1;
        const long long vall = (long long)(mid - l + 1) * a[mid] - (pre[mid] - pre[l - 1]), valr = (pre[r] - pre[mid]) - (long long)(r - mid) * a[mid];
        if (vall + valr <= k){
            return true;
        }
    }
    return false;
}

int main(){
    scanf("%s %lld", s, &k);
    for (int i = 0, cnt = 0; s[i]; i++){
        s[i] == 'Y' ? a[++n] = cnt : cnt++;
    }
    for (int i = 1; i <= n; i++){
        pre[i] = pre[i - 1] + a[i];
    }
    int l = 0, r = n;
    while (l < r){
        const int mid = l + r + 1 >> 1;
        if (check(mid)){
            l = mid;
        }else{
            r = mid - 1;
        }
    }
    printf("%d", l);
}
```

---

## 作者：Expert_Dream (赞：0)

非常好的一道题。

思维要求蛮高的。

我们可以将题面转换一下，例如一个 ```Y```  他要从 $x$ 走到 $y$，那么他所需要的步数就是 $x$ 到 $y$ 之间 ```.```  的个数。

那么我们对于一个区间 $[l,r]$，就变成了，这上面每一个点有一个数，找一个点然后是的所有的点到他的距离最小，这是一个很经典的问题，这个时候的策略就是选中间点。

我们可以直接二分长度，然后枚举每一个区间，然后计算一下是否符合条件。

我们可以通过一个前缀和和一个二次前缀和搭配使用来算出他所需要的次数。

在 check 函数里即可达到线性的时间复杂度。

[link](https://atcoder.jp/contests/abc229/submissions/52412424)。

---

## 作者：Minuswy (赞：0)

分享一个 $O(n \log^2 n)$ 的 ~~麻烦的~~ 另一个角度的二分做法。

~~在某个地方看到这题有数据结构的标签，昨晚发现并不用数据结构，前缀和就可以。所以为什么有数据结构标签呢？~~

---

首先还是转换这个问题。将 $Y$ 下标塞进一个数组里，然后减去其在新数组里的下标，得到数组 $a$，于是问题可以转化为：让 $a$ 里的一些数 $+1/-1$ 若干次，问最多有多少个数能变得相同。

样例1 里的 $a$ 数组就是 $0,0,3,4,5$。可以发现，$a$ 一定是单调不降的。

可以枚举最终变得相同的数 $x$。显然最终答案对应的 $x$ 一定是原先有 $Y$ 的位置。

然后二分出能够在 $k$ 次操作下都变成 $x$ 的最远区间 $[L,R]$。这个怎么二分呢，可以对区间到 $x$ 的最大操作次数 $p$ 进行二分，因为我们发现这个 $p$ 一定在 $L$ 或者 $R$ 的位置取到，方便确定整个区间。

对于一个 $p$ 和最终都变成的数 $x$，先 `lower_bound` 出 $L,R$ 的位置，然后用前缀和处理这个区间都变成 $x$ 需要操作的次数。具体来说，就是把 $[L,R]$ 拆成 $[L,x],[x,R]$ 分别计算。

如果需要操作的次数 $>k$ 那么 $p$ 就是不合法的，反之就是合法的。

**但是！！** 还有可能碰到这样的情况：$a=\{1,2,2,2,2,2,2,2\},k=3$。此时你的 $[L,R]$ 是 $[1,1]$，但显然可以是 $[1,4]$。这时就要把 $L,R$ 往两边再扩展。因为你不知道 $[L,R]$ 哪一头能再往外扩，所以两边都试一下，设这个能被外扩的数为 $w$。

具体地说，如果通过二分得到的 $[L,R]$ 已经花费了 $d$ 次操作，那么还剩下 $k-d$ 次外扩的操作。因为外扩的每个数所需操作都是 $|a_x-w|$，直接用 $k-d$ 去除一下就可以了。

---

```cpp
#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define endl "\n"
#define int long long
#define pii pair<int,int>
#define mem(a,b) memset(a,(b),sizeof(a))
using namespace std;
const int N=2e5+5;
int n,k,ans,mx;
char s[N];
int a[N],t[N];
int dis(int l,int r,int op){
	if(op==1) return t[r]-t[l-1]-(r-l+1)*a[l];
	return (r-l+1)*a[r]-(t[r]-t[l-1]);
}
bool check(int x,int p){
	int L=lower_bound(a+1,a+n+1,max(0ll,a[x]-p))-a,R=upper_bound(a+1,a+n+1,a[x]+p)-a-1;
	if(dis(L,x,-1)+dis(x,R,1)>k) return 0;
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>s+1;
	cin>>k;
	int len=strlen(s+1); 
	FOR(i,1,len){
		if(s[i]=='Y') a[++n]=i-n,mx=max(mx,a[n]);
	}
	FOR(i,1,n) t[i]=t[i-1]+a[i];
	FOR(i,1,n){
		int l=0,r=max(a[i],mx-a[i]);
		while(l<r){
			int mid=(l+r+1)>>1;
			if(check(i,mid)) l=mid;
			else r=mid-1;
		}
		int L=lower_bound(a+1,a+n+1,max(0ll,a[i]-r))-a,R=upper_bound(a+1,a+n+1,a[i]+r)-a-1;
		ans=max(ans,R-L+1);
		int qwq=dis(L,i,-1)+dis(i,R,1);
		if(k==qwq) continue;
		int res=0;
		if(L!=1&&L!=0) ans=max(ans,res=max(res,R-L+1+(k-qwq)/abs(a[i]-a[L-1])));
		if(R!=n-1&&R!=n) ans=max(ans,res=max(res,R-L+1+(k-qwq)/abs(a[i]-a[R+1])));
	}
	cout<<ans<<endl;
	return (0-0);
}
```

---


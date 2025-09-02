# Round Marriage

## 题目描述

It's marriage season in Ringland!

Ringland has a form of a circle's boundary of length $ L $ . There are $ n $ bridegrooms and $ n $ brides, and bridegrooms decided to marry brides.

Of course, each bridegroom should choose exactly one bride, and each bride should be chosen by exactly one bridegroom.

All objects in Ringland are located on the boundary of the circle, including the capital, bridegrooms' castles and brides' palaces. The castle of the $ i $ -th bridegroom is located at the distance $ a_i $ from the capital in clockwise direction, and the palace of the $ i $ -th bride is located at the distance $ b_i $ from the capital in clockwise direction.

Let's define the inconvenience of a marriage the maximum distance that some bride should walk along the circle from her palace to her bridegroom's castle in the shortest direction (in clockwise or counter-clockwise direction).

Help the bridegrooms of Ringland to choose brides in such a way that the inconvenience of the marriage is the smallest possible.

## 说明/提示

In the first example the first bridegroom should marry the second bride, the second bridegroom should marry the first bride. This way, the second bride should walk the distance of $ 1 $ , and the first bride should also walk the same distance. Thus, the inconvenience is equal to $ 1 $ .

In the second example let $ p_i $ be the bride the $ i $ -th bridegroom will marry. One of optimal $ p $ is the following: $ (6,8,1,4,5,10,3,2,7,9) $ .

## 样例 #1

### 输入

```
2 4
0 1
2 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10 100
3 14 15 92 65 35 89 79 32 38
2 71 82 81 82 84 5 90 45 23
```

### 输出

```
27
```

# 题解

## 作者：封禁用户 (赞：7)

~~在某个比赛看到了这一题迫不及待的使用了毕生所学的卡暴力做法~~

## 题意

$n$ 个新郎和 $n$ 个新娘围成一个环，长度为 $L$，第 $i$ 个新郎位置为 $a_i$，第 $i$ 个新娘位置为 $b_i$，需要将他们两两配对，最小化新郎和新娘距离的最大值。

## 解法

明显看到这一题，我们这一直接暴力先爆他：

```cpp
/*****************************************
备注：
******************************************/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <climits>
using namespace std;
typedef long long ll;
#define int ll
const int MAXN = 2e6 + 10;
const int MR = 10 + 5;
const int INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const bool debug = false;
int n, l;
int a[MAXN], b[MAXN];
int dis(int a, int b)
{
	//计算a, b两个人的距离
	return min(abs(a - b), l - abs(a - b));
}
signed main()
{
	// int start = clock();
	cin >> n >> l;
	for(int i = 1;i <= n; i++)cin >> a[i];
	for(int i = 1;i <= n; i++)cin >> b[i];
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + n);
	int ans = INF;
	for(int i = 1; i <= n; i++)
	{
		int distance = -INF;
		for(int j = 1; j <= n; j++)
		{
			int left = a[j];
			int right = b[(i + j) % n];
			distance = max(distance, dis(left, right));
		}
		ans = min(ans, distance);
	}
	cout << ans << endl;
	// printf("%.3lf", clock() - start);
    return 0;
}


```

直接交上去发现 `TLE on test 8`，因为超时肯定是在二次循环的地方造成的。

我们发现如果当前的距离大于答案，那么我们就可以直接 break 掉：

```cpp
/*****************************************
备注：
******************************************/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <climits>
using namespace std;
typedef long long ll;
#define int ll
const int MAXN = 2e6 + 10;
const int MR = 10 + 5;
const int INF = INT_MAX;
const int MOD = 1e9 + 7;
const bool debug = false;
int n, l;
int a[MAXN], b[MAXN];
int dis(int a, int b)
{
	//计算a, b两个人的距离
	return min(abs(a - b), l - abs(a - b));
}
signed main()
{
	// int start = clock();
	cin >> n >> l;
	for(int i = 1;i <= n; i++)cin >> a[i];
	for(int i = 1;i <= n; i++)cin >> b[i];
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + n);
	int ans = INF;
	for(int i = 1; i <= n; i++)
	{
		int distance = -INF;
		for(int j = 1; j <= n; j++)
		{
			int left = a[j];
			int right = b[(i + j) % n + 1];
			distance = max(distance, dis(left, right));
			if(distance > ans)break;
		}
		ans = min(ans, distance);
	}
	cout << ans << endl;
	// printf("%.3lf", clock() - start);
    return 0;
}
```

再交一发，发现 `TLE on test24`，原因肯定是在什么小的地方上。

考虑优化细节，比如将 `min` 换成三目运算符，加上 `register` 跑循环等等。

但是有一个细节，就是 `if(distance > ans)break;` 这一行，如果我们将上面的细节全部优化，我们会发现会 `TLE on test27`，原因是因为如果当前距离等于答案了，那么可以不用再更新一次，可以直接 break 掉。

## AC 代码

```cpp
/*****************************************
备注：
******************************************/
#pragma GCC optimize("-Ofast,fast-math")
#pragma GCC target("avx,sse,sse2,sse3,sse4,popcnt")
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cctype>
#include <cmath>
#include <cassert>
#include <climits>
using namespace std;
typedef long long ll;
#define int ll
const int MAXN = 2e5 + 10;
const int MR = 10 + 5;
const int INF = INT_MAX;
const int MOD = 1e9 + 7;
const bool debug = false;
struct ios {
    inline char read() {
        static const int inlen = 1 << 18 | 1;
        static char buf[inlen], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, inlen, stdin)), s == t ? -1 : *s++;
    }
    template<typename T> inline ios& operator>> (T &x) {
        static char c11, boo;
        for (c11 = read(), boo = 0; !isdigit(c11); c11 = read()) {
            if (c11 == -1) return *this;
            boo |= c11 == '-';
        }
        for (x = 0; isdigit(c11); c11 = read()) x = x * 10 + (c11 ^ '0');
        boo && (x = -x);
        return *this;
    }
} fin;
int n, l;
int a[MAXN], b[MAXN];
#define getmin(a, b) (a < b ? a : b);
#define getmax(a, b) (a > b ? a : b);
int dis(int a, int b)
{
	//计算a, b两个人的距离
	return getmin(abs(a - b), l - abs(a - b));
}
int iid[MAXN];//随机化枚举顺序
int jid[MAXN];
signed main()
{
	// int start = clock();
	srand((unsigned)time(NULL));
	fin >> n >> l;
	for(register int i = 1;i <= n; i++)fin >> a[i];
	for(register int i = 1;i <= n; i++)fin >> b[i];
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + n);
	for(int i = 1;i <= n; i++)
	{
		iid[i] = jid[i] = i;
	}
	random_shuffle(iid + 1, iid + 1 + n);
	random_shuffle(jid + 1, jid + 1 + n);
	int ans = INF;
	for(register int i = 1; i <= n; i++)
	{
		int distance = -INF;
		for(register int j = 1; j <= n; j++)
		{
			int ii = iid[i];
			int jj = jid[j];
			int left = a[jj];
			int right = b[(ii + jj) % n + 1];
			distance = getmax(distance, dis(left, right));
			if(distance >= ans)break;
		}
		ans = getmin(ans, distance);
	}
	cout << ans << endl;
	// printf("%.3lf", clock() - start);
    return 0;
}
```

---

## 作者：翼德天尊 (赞：6)

> $n$ 个新郎和 $n$ 个新娘围成一个环，长度为 $L$，第 $i$ 个新郎位置为 $a_i$，第 $i$ 个新娘位置为 $b_i$，需要将他们两两配对，最小化新郎和新娘距离的最大值。
>
> $1\le n\le 2\times 10^5$，$1\le L\le 10^9$.

首先根据 "最小值最大"，先二分答案，考虑如何判定「当新郎可以和距离其 $x$ 以内的新娘配对时，是否存在完美匹配」。

又观察到了「完美匹配」，考虑使用 Hall 定理。

首先断环成链，设第 $i$ 个新郎向左可以匹配到第 $nl_i$ 个新娘，向右可以匹配到第 $nr_i$ 个新娘。由于单次判定对于每个新郎的 $x$ 值相同，故可以利用单调性 $O(n)$ 求出每个新郎的 $nl,nr$ 值。

那么根据 Hall 定理，有：
$$
r-l+1\le nr_r-nl_l+1
$$
观察到该式子只和 $l,r$ 有关，考虑将 $l,r$ 拆开：
$$
nr_r-r\ge nl_l-l
$$
于是从左向右扫时，动态更新之前所有 $nl_l-l$ 的最大值，判断是否不大于当前 $nr_r-r$ 即可。

注意断环时将 $a$ 拆成两份，将 $b$ 拆成四份，才能便捷地在处理中表示所有情况。

时间复杂度 $O(n\log n)$.


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
const int N=8e5+5;
int n,L,a[N],b[N],al[N],ar[N];
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
bool check(int x){
    for (int l=1,r=0,i=n+1;i<=n*3;i++){
        while (r<n*4&&b[r+1]-a[i]<=x) ++r;
        while (l<=r&&a[i]-b[l]>x) ++l;
        al[i]=l,ar[i]=r;
    }
    //cout<<x<<"\n";
    //for (int i=n+1;i<=n+n;i++) cout<<al[i]<<" "<<ar[i]<<"\n";
    int maxn=-3e9;
    for (int i=n+1;i<=n*3;i++){
        maxn=max(maxn,al[i]-i);
        //cout<<"===="<<i<<" "<<maxn<<" "<<al[i]<<'\n';
        if (ar[i]-i<maxn) return 0;
    }
    return 1;
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif  
    n=read(),L=read();
    for (int i=1;i<=n;i++) a[i]=read();
    for (int i=1;i<=n;i++) b[i]=read();
    sort(a+1,a+1+n);
    sort(b+1,b+1+n);
    for (int i=1;i<=n+n;i++) a[i+n]=a[i]+L;
    for (int i=1;i<=n*3;i++) b[i+n]=b[i]+L;
    int l=0,r=L/2,ans=0;
    while (l<=r){
        int mid=l+r>>1;
        if (check(mid)) r=mid-1,ans=mid;
        else l=mid+1;
    }
    cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：大菜鸡fks (赞：6)

考虑二分答案。如何验证？

这是二分图，考虑hall定理。 那么对于一个新郎，可以找到的新娘为l[i]-r[i]这个区间。

那么对于任意的i，j 必须满足r[j]-l[i]>=j-i

移项得r[j]-j>=l[i]-i

还不会判断吗？？

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=2e5+5,INF=1e9;
int n,L;
ll a[N<<1],b[N<<2];
inline bool judge(int len){
	int mx=-INF,j1=1,j2=1;
	for (int i=1;i<=n*2;i++){
		while (j1<=4*n&&b[j1]<a[i]-len) j1++;
		while (j2<=4*n&&b[j2]<=a[i]+len) j2++;
		mx=max(mx,j1-i);
		if (j2-i-1<mx) return 0;
	}
	return 1;
} 
inline void init(){
	n=read(); L=read();
	for (int i=1;i<=n;i++) a[i]=read(); sort(a+1,a+1+n);
	for (int i=1;i<=n;i++) b[i]=read(); sort(b+1,b+1+n);	
	for (int i=1;i<=n;i++) a[i]+=L,a[n+i]=a[i]+L;
	for (int i=1;i<=3*n;i++) b[i+n]=b[i]+L;

}
inline void solve(){
	int l=0,r=L/2;
	while (l<r){
		int mid=(l+r)>>1;
		if (judge(mid)) r=mid;
			else l=mid+1;
	}
	writeln(l);
}
int main(){
	init();
	solve();
	return 0;
} 
```

---

## 作者：sry_ (赞：5)

二分答案 $k$ 后求二分图是否存在完美匹配，显然 $Hall$ 定理。

但是问题在于一个点连的不为连续区间，会存在连一段前缀与一段后缀的情况（即为环的贡献）

一个很简单的想法是断环为链，由于我们仅需要考虑连续段的影响，那么我们考虑将 $a$ 复制一份进行考虑，跑序列上的做法。

正确性我们可以考虑如果在当前 $[l,r]$ 中对应的 $Y$ 有两个相同的（但位置不同），那么 $X$ 已经可以把所有的 $Y$ 均取到了，所以我们不需要考虑这种情况，那么我们仅需要求出在 $l$ 有限制的情况下的答案，这需要个单调队列维护，去保证 $Y$ 不交。

事实上在代码实现中我们不需要求一段区间的最小值，因为上述情况必然 $|X|\leq |Y|$ ，因为当前 $k\leq \frac{L}{2}$ ，那么对于两个相同的 $x$ 所覆盖的区间是无交的，那么我们就直接对应即可，显然此时 $|X|\leq |Y|$ 。

时间复杂度 $\mathcal O(n\log n)$ 。

---

## 作者：Steven_Meng (赞：4)

这道题其实可以用暴力水过qwq

首先可以知道一个暴力做法如下，具体地来说可以用调整法证明其正确性，但是过不了所有的点。

```
#pragma GCC optimize (2)
#pragma G++ optimize (2)
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#define MAXN 200005
using namespace std;
int A[MAXN], B[MAXN];
int l;;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9'){
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline int max(int a, int b)
{
    return a > b ? a : b;
}
inline int min(int a, int b)
{
    return a < b ? a : b;
}
inline int calc(int a, int b)
{
    int dis = a > b ? a - b : b - a;
    return min(dis, l - dis);
}
int num1[MAXN],num2[MAXN];
int main()
{
    int n;
    n=read(),l=read();
    for (register int i = 0; i < n; ++i)
    {
        A[i]=read();
    }
    for (register int i = 0; i < n; ++i)
    {
        B[i]=read();
    }
    sort(A, A + n);
    sort(B, B + n);
    int minmax = 0x7fffffff;
    for (register int i = 0; i <n; ++i)
    {
        int maxn = -0x7fffffff;
        for (register int j = 0; j <n; ++j)
        {
            maxn = max(maxn, calc(A[j], B[(i + j >= n) ? (i + j - n) : (i + j)]));
        }
        minmax = min(minmax, maxn);
    }
    printf("%d\n", minmax);
    return 0;
}
```

然后，我们有一个比较显然的优化：如果当前最大值已经比最小的最大值要大的话，就break掉。

```cpp
#pragma GCC optimize (2)
#pragma G++ optimize (2)
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#define MAXN 200005
using namespace std;
int A[MAXN], B[MAXN];
int l;;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9'){
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline int max(int a, int b)
{
    return a > b ? a : b;
}
inline int min(int a, int b)
{
    return a < b ? a : b;
}
inline int calc(int a, int b)
{
    int dis = a > b ? a - b : b - a;
    return min(dis, l - dis);
}
int num1[MAXN],num2[MAXN];
int main()
{
    int n;
    n=read(),l=read();
    for (register int i = 0; i < n; ++i)
    {
        A[i]=read();
    }
    for (register int i = 0; i < n; ++i)
    {
        B[i]=read();
    }
    sort(A, A + n);
    sort(B, B + n);
    int minmax = 0x7fffffff;
    for (register int i = 0; i <n; ++i)
    {
        int maxn = -0x7fffffff;
        for (register int j = 0; j <n; ++j)
        {
            maxn = max(maxn, calc(A[j], B[(i + j >= n) ? (i + j - n) : (i + j)]));
            if (maxn >= minmax)
            {
                break;
            }
        }
        minmax = min(minmax, maxn);
    }
    printf("%d\n", minmax);
    return 0;
}
```
但是，显然这个程序在随机数据下表现良好，但是会被一些别有用心的数据构造者卡掉。。。比如说这个程序就T在了第24个点

什么？你要写二分？too young too naive！如果数据不是随机的，我们就“构造”出随机的数据，比如说，用random_shuffle优化枚举顺序

```cpp
#pragma GCC optimize (2)
#pragma G++ optimize (2)
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#define MAXN 200005
using namespace std;
int A[MAXN], B[MAXN];
int l;;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9'){
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline int max(int a, int b)
{
    return a > b ? a : b;
}
inline int min(int a, int b)
{
    return a < b ? a : b;
}
inline int calc(int a, int b)
{
    int dis = a > b ? a - b : b - a;
    return min(dis, l - dis);
}
int num1[MAXN],num2[MAXN];
int main()
{
    int n;
    n=read(),l=read();
    for (register int i = 0; i < n; ++i)
    {
        //scanf("%d", &A[i]);
        A[i]=read(),num1[i]=i;
    }
    for (register int i = 0; i < n; ++i)
    {
        //scanf("%d", &B[i]);
        B[i]=read(),num2[i]=i;
    }
    random_shuffle(num1,num1+n);
    random_shuffle(num2,num2+n);
    sort(A, A + n);
    sort(B, B + n);
    int minmax = 0x7fffffff;
    for (register int ii = 0; ii <n; ++ii)
    {
        int maxn = -0x7fffffff;
        for (register int jj = 0; jj <n; ++jj)
        {
            int i=num1[ii],j=num2[jj];
            maxn = max(maxn, calc(A[j], B[(i + j >= n) ? (i + j - n) : (i + j)]));
            if (maxn >= minmax)
            {
                break;
            }
        }
        minmax = min(minmax, maxn);
    }
    printf("%d\n", minmax);
    return 0;
}
```

然后就成功地刷到了cf排行榜第一

有图为证:

![屏幕快照 2018-10-20 下午11.11.23.png](https://i.loli.net/2018/10/20/5bcb45ba78522.png)


---

## 作者：xxxxxzy (赞：3)

[CF981F Round Marriage](https://www.luogu.com.cn/problem/CF981F)

题意： $n$ 个新郎和 $n$ 个新娘围成一个环，长度为 $L$，第 $i$ 个新郎位置为 $a_{i}$，第 $i$ 个新娘位置为 $b_{i}$，需要将他们两两配对，最小化新郎和新娘距离的最大值。

直接二分答案，发现问题变成了如何检验是否能在距离 $mid$ 之间匹配完，即最大匹配数为 $n$。

考虑 **Hall** 定理来判定，首先断环为链，设第 $i$ 个新郎可以匹配的区间是 $[lx_{i},rx_{i}]$，那么由 Hall 定理知，对于任意一个新郎的区间 $[l,r]$，一定有 $r-l+1 \le rx_{r}-lx_{l}+1$。

移项，得到 $rx_{r}-r \ge lx_{l}-l$。

那么就可以维护每个地方 $lx_{l}-l$ 的最大值，再判断是不是 $\le$ 当前的 $rx_{r}-r$ 即可。

$lx_{i},rx_{i}$ 可以直接双指针或者二分求出来，时间复杂度 $O(n \log L)$。

细节：注意为了保证后面的 $lx_{l}-l$ 可以被前面的 $rx_{x}-r$ 判断到，$a$ 数组要复制 $2$ 次，$b$ 数组要复制 $4$ 次。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define drep(i,a,b) for(int i=a;i>=b;i--)
#define pb push_back
#define pii pair<int,int>
const int inf=1e9+5;
using namespace std;
int n,L,a[800005],b[800005],lx[800005],rx[800005];
bool check(int mid){
	int l=1,r=0,maxn=-inf;
	rep(i,n+1,n*3){
		while(r<n*4&&b[r+1]-a[i]<=mid) r++;
		while(l<=r&&a[i]-b[l]>mid) l++;
		lx[i]=l,rx[i]=r;
	}
	rep(i,n+1,n*3){
		maxn=max(maxn,lx[i]-i);
		if(rx[i]-i<maxn) return 0;
	}
	return 1;
}
int ask(int l,int r){
	int ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>L;
	rep(i,1,n) cin>>a[i];
	rep(i,1,n) cin>>b[i];
	sort(a+1,a+1+n);sort(b+1,b+1+n);
	rep(i,1,n<<1) a[i+n]=a[i]+L;
	rep(i,1,n*3) b[i+n]=b[i]+L;
	cout<<ask(0,L/2);
}
```

---

## 作者：waauto (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF981F)

决斗的时候决斗到了这题，感觉题解做法不太一样？写一下题解。

首先一个很暴力的想法是先排个序然后移动一个环去匹配，时间复杂度 $O(n^2)$。

但是我们注意到这题问的是一个经典二分答案问题，同时答案确实显然有单调性，我们考虑二分。

思考一下如何 check。

对于每一个点 $b_i$，我们求出它所能对应的在 $a$ 上距离 $i$ 的一个范围 $l,r$。

贪心的思考一下，其实我们只需要判断是否有交就可以了，断环成链，每次 lowerbound 或者 upperbound 找端点。

*2500 AC 最快的一集。

代码挺短的，贴一下吧。

```cpp

int n,L;
const int N=4e5+5;
int a[N],b[N];

int l,r;
inline int findL(int x,int pos){
	pos+=n;
	int to=lower_bound(a+1,a+1+2*n,b[pos]-x)-a;
	ret to-pos;
}
inline int findR(int x,int pos){
	int to=upper_bound(a+1,a+1+2*n,b[pos]+x)-a-1;
	ret to-pos;
}
inline bool ck(int x){
	l=-1e9,r=1e9;
	F(i,1,n){l=max(l,findL(x,i));r=min(r,findR(x,i));}
	ret r>=l;
}
inline void mian(){
	cin>>n>>L;
	F(i,1,n)cin>>a[i],a[i+n]=a[i]+L;
	F(i,1,n)cin>>b[i],b[i+n]=b[i]+L;
	sort(a+1,a+1+2*n);
	sort(b+1,b+1+2*n);
	int l=0,r=L+1;
	while(r>l){
		int mid=(l+r)>>1;
		if(ck(mid))r=mid;
		else l=mid+1;
	}
	cout<<l<<'\n';
}
```

---

## 作者：Danslapiscine (赞：0)

什么是 Hall 定理，蒟蒻不知道。

考虑二分答案，问题转化为是否能在 $mid$ 距离内为每个少男找到匹配的少女。

首先证明对于一个两个**位置序列**，最优匹配方案一定是分别从小到大排序后依次匹配。分类讨论即可。

然后证明对于**环上**问题，最优匹配方案一定不同时存在有少男从左端到右端和从右端到左端的情况。并且一定是一段前缀或后缀的少男匹配到环的另一端。

这样我们就有了断环为链的前提，并且知道了匹配方式。把少女的位置序列 $b$ 复制三份，分别存 $L-b_i$、$b_i$ 和 $L+b_i$，首尾相接设为 $B$。最优方案就是其中连续长度为 $n$ 的某一段和 $a_i$ 进行的如上所述的匹配。

这样写还是会TLE，考虑优化。发现可与 $a_i$ 匹配的位置在 $B$ 上是一段区间，并且左右端点随i增大单调递增，可 $O(n)$ 求出。并且发现若 $1 \sim i-1$ 的 $a$ 符合匹配条件的 $B$ 的右端点的取值为 $[L,R]$ ，那么相当于 $a_i$ 可以“接上”的范围为 $[L+1,R+1]$，又要符合自己的匹配条件，取交集即可。

时间复杂度 $O(n \log V)$。


```cpp
#include <bits/stdc++.h>
using namespace std;

int n, LL, a[200002], b[600002];
int have[200002];
bool check(int s){
	int l = 1, r = 1, nowl = 1, nowr = 3 * n;
	for(int i=1;i<=n;i++){
		while(l <= 3 * n && b[l] < a[i] - s) l++;
		while(r <= 3 * n && b[r] <= a[i] + s) r++;
		r--;
		nowl = max(nowl, l), nowr = min(nowr, r);
		nowl++, nowr++;
	}
	return nowl <= nowr;
}

int main(){
	//freopen("marriage1.in","r",stdin);
	
	scanf("%d%d",&n,&LL);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=n+1;i<=2*n;i++) scanf("%d",&b[i]);
	sort(a+1,a+n+1), sort(b+n+1,b+2*n+1);
	for(int i=1;i<=n;i++) b[i] = b[n+i] - LL;
	for(int i=n*2+1;i<=n*3;i++) b[i] = b[i-n] + LL;
	
	int l = 0, r = 2e9;
	while(l < r){
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	
	printf("%d",l);
	
	return 0;
}
```

---

## 作者：_Cheems (赞：0)

显然二分答案，转化为判定性问题。

那么对于验证 $k$，考虑让新郎 $a_i$ 向所有可以匹配的新娘连边，那么 $k$ 合法，当且仅当建出的二分图有完美匹配。

考虑 $\rm Hall$ 定理，首先将 $a,b$ 排序，尽量让 $a_i$ 管辖的 $b$ 构成一段连续区间。

不过这是环，所以我们需要破环成链。注意一下，假设第 $p$ 份表示将原数组复制然后每一项加 $p\times L$，那么应该选择第 $2,3$ 份 $a$ 和 $1,2,3,4$ 份 $b$，才能表示出所有情况。这很重要。

于是现在 $a_i$ 管辖 $[L_i,R_i]$，贪心地，必然是选择一段连续的 $a_i$ 才能更劣，判定 $[i,j]$ 即为：$j-i+1\le R_j-L_i+1$，移项得 $L_i-i\le R_j-j$，扫描一遍即可。

然后有两个细节：

1. 假如 $[L,R]$ 覆盖的 $b$ 出现重复元素（对应原序列而言）：此时必然已经覆盖了原 $b$ 序列一遍，肯定多于 $a$ 的数量，所以不用考虑。

2. 假如 $a$ 中 $[i,j]$ 实际覆盖的 $b$ 并不连续，即存在某个 $b$ 不被任何 $a$ 覆盖：那么设其为 $b_{pos}$，那么必然有一个 $a$ 多出来；反向思考，对于 $b_1\dots b_{pos-1}$ 和 $b_{pos+1}\dots b_n$，必然存在一者使得对应的 $a$ 数量小于 $b$ 数量，就不满足 $\rm Hall$ 定理了。所以一定非法，无需特判。

~~有些抽象。~~

二分查找 $L_i,R_i$，复杂度 $O(n\log n\log V)$。双指针代替可做到 $O(n\log V)$。

#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e6 + 5, inf = 1e10;
int n, len, a[N], b[N];

inline bool check(int p){
	int mx = -inf;
	for(int i = n + 1; i <= 3 * n; ++i){
		int l = lower_bound(b + 1, b + 1 + 4 * n, a[i] - p) - b, r = upper_bound(b + 1, b + 1 + 4 * n, a[i] + p) - b - 1;
		if(l > r) return false;
		if(mx > r - i) return false;
		mx = max(mx, l - i);
	}
	return true; 
}
signed main(){
	cin >> n >> len;
	for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; ++i) scanf("%lld", &b[i]);
	sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + n);
	for(int i = n + 1; i <= 4 * n; ++i) a[i] = a[i - n] + len, b[i] = b[i - n] + len;
	int L = -1, R = 1e9 + 5;
	while(L + 1 < R){
		int mid = L + R >> 1;
		if(check(mid)) R = mid;
		else L = mid; 
	}
	cout << R;
	return 0;
}
```

---


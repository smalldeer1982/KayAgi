# Tape

## 题目描述

You have a long stick, consisting of $ m $ segments enumerated from $ 1 $ to $ m $ . Each segment is $ 1 $ centimeter long. Sadly, some segments are broken and need to be repaired.

You have an infinitely long repair tape. You want to cut some pieces from the tape and use them to cover all of the broken segments. To be precise, a piece of tape of integer length $ t $ placed at some position $ s $ will cover segments $ s, s+1, \ldots, s+t-1 $ .

You are allowed to cover non-broken segments; it is also possible that some pieces of tape will overlap.

Time is money, so you want to cut at most $ k $ continuous pieces of tape to cover all the broken segments. What is the minimum total length of these pieces?

## 说明/提示

In the first example, you can use a piece of length $ 11 $ to cover the broken segments $ 20 $ and $ 30 $ , and another piece of length $ 6 $ to cover $ 75 $ and $ 80 $ , for a total length of $ 17 $ .

In the second example, you can use a piece of length $ 4 $ to cover broken segments $ 1 $ , $ 2 $ and $ 4 $ , and two pieces of length $ 1 $ to cover broken segments $ 60 $ and $ 87 $ .

## 样例 #1

### 输入

```
4 100 2
20 30 75 80
```

### 输出

```
17
```

## 样例 #2

### 输入

```
5 100 3
1 2 4 60 87
```

### 输出

```
6
```

# 题解

## 作者：chenlingxi (赞：3)

## 题面

先给你n,m,k,分别表示点数，总长度，胶带的数量

再给你n个点，保证递增。

求覆盖所有的点所需的最小胶带长度（胶带数量<=k）

~~表示语文差到极点~~

---

### 题解

数据范围100000，很显然是nlogn的复杂度

~~nlogn^2也有可能~~

先考虑k=1的情况

很显然就是从第1个点覆盖到第n个点

如果k更大呢

---

考虑贪心

因为每个点都要覆盖，所以减少的最多只能是相邻两点间的一段

再根据贪心，我们要求出能减少中的前k-1大的

那么输入时处理出相邻两点间间距，然后sort排一发就好了

复杂度O(nlogn)~~主要是sort的时间~~

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],sum[100005];
bool cmp(int i,int j)
{
	return i>j;
}
int main()
{
	int n,k,s;
	cin>>n>>k>>s;
	for(int i=1;i<=n;++i)cin>>a[i];
	int num=a[n]-a[1]+1;
	for(int i=2;i<=n;++i)
	sum[i]=a[i]-1-a[i-1];
	sort(sum+2,sum+n+1,cmp);
	for(int i=2;i<=s;++i)
	num-=sum[i];
	cout<<num;
}
```

---

## 作者：installb (赞：2)

首先，这题中每一个点都是需要被覆盖的  
在胶带数量$k=n$的情况下，只需要覆盖每个点即可  
否则的话，每少用一个胶带代表会有两个**相邻的**点要使用同一个胶带覆盖即需要覆盖这两个点之前的区间(**不包括端点，即开区间**)的长度$b[i]-b[i-1]-1$

到了这里我们就可以**贪心**了  
不难发现，只要每次取最小的区间知道胶带数满足要求即可  
而需要取的区间数即为$n-k$  

最后加上点数n即可  

## code:

```cpp
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LL long long
using namespace std;
const LL INF = 0x3f3f3f3f3f3f3f3f;

LL n,m,k;
LL l[100005] = {0};
LL dl[100005] = {0}; // 保存区间长度
LL sum = 0;

int main(){
	ios::sync_with_stdio(false);
	cin >> n >> m >> k;
	k = n - k; // 先把k改为需要取得区间数量
	for(register int i = 1;i <= n;i ++){
		cin >> l[i];
		dl[i - 1] = l[i] - l[i - 1] - 1; // 计算区间长度
	}
	sort(dl + 1,dl + n); // 从小到大排序(注意只有n-1个区间)
	for(register int i = 1;i <= k;i ++) sum += dl[i]; // 覆盖区间
	cout << sum + n << endl; // 加上所有端点，输出答案
	return 0;
}
```

---

## 作者：Spir1t (赞：1)

### ~~水~~题
这道题还是很好想的

我们可以先对裂口进行排序，然后对于相邻的两个裂口之间的距离，选择使用胶带对其进行粘合，使得这段距离被覆盖。在排序后的裂口位置之间距离，将其存放在一个数组中，因为我们需要对每一段存储的距离值进行操作。具体来说，我们需要将所有距离值从小到大排序，然后选择前  $k$  小的距离值，使用长度为该距离的胶带进行修复。

### 代码
```
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100010;
int n, m, k;
int a[N], d[N];
int main() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	sort(a, a + n);
	int cnt = 0;
	for (int i = 1; i < n; ++i) {
		d[cnt++] = a[i] - a[i - 1];
	}
	sort(d, d + cnt);
	int res = n;
	for (int i = 0; i < cnt - k + 1; ++i) {
		res += d[i] - 1;
	}
	cout << res << '\n';
	return 0;
}
```


---

## 作者：StayAlone (赞：1)

### 题意  

给定 $n,m,k$，分别表示布上破裂的点的数量，布的总长度，只能使用的胶带的数量。接下来 $n$ 个正整数 $b_i$，保证 $b_i$ 严格递增且 $b_n \leqslant m$。  

胶带可以通过粘合修复布。求修复布所需的最小的胶带总长度。注意每一个胶带的长度都只能是整数。  


### 思路  

这个题虽然是 CF，但实际上思维强度不大。我们把操作过程想成分割 $k - 1$ 次，令 $d_i = b_i - b_{i - 1}(i\in[2, n])$，然后从大到小排序 $d$ 数组。显然割掉的那些胶带的长度均大于等于 $d_{k - 1}$。

但是细节问题可能比较不好处理：当第 $k - 1$ 大的长度有很多个时，应该怎么分割？仔细想想也能想到，这种情况下，允许胶带越过差等于 $d_{k - 1}$ 的次数等于 $i \in [k,n]$ 中 $a_i = d_{k - 1}$ 的数量。  

[AC code 记录](https://www.luogu.com.cn/record/63564146)  

```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (int i = j; i <= int(n); ++i)
#define rep2(i, j, n) for (int i = j; i >= int(n); --i)
#define ......
using namespace std;
typedef long long ll;
typedef ......
const int MAXN = 1e5 + 10, inf = ~0U >> 2, INF = ~0U >> 1;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
namespace stupid_lrc
{
	template <typename T>
	il void read(T &x)
    
    il int read()
	
	template <typename T>
	il void write(T x)
	
	template <typename T>
	il T my_max(const T &x, const T &y)
	
	template <typename T>
	il T my_min(const T &x, const T &y)
	
	template <typename T>
	il T lowbit(const T &x)
	
	il string ItS(int k)
	
	il int StI(const string &s)
}
using namespace stupid_lrc;
// 奇妙缺省源
int n, m, k, a[MAXN], d[MAXN]; ll ans;

int main()
{
	read(n); read(m); read(k);
	rep1(i, 1, n) read(a[i]), d[i] = a[i] - a[i - 1];
	d[1] = -inf;
	sort(d + 1, d + 1 + n, greater <int>());
	int l = 1, r = 1; d[0] = INF;
	int q = 0;
	rep1(i, k, n) q += d[i] == d[k - 1];
	while (l <= r && r <= n)
	{
		bool p = true;
		if (r < n)
		{
			int t = a[r + 1] - a[r];
			if (q > 0 && t <= d[k - 1]) q -= t == d[k - 1], ++r, p = false;
			else if (q <= 0 && t < d[k - 1]) ++r, p = false;
		}
		if (p) ans += a[r] - a[l] + 1, l = ++r;
	}
	write(ans);
	rout;
}
```

---

## 作者：ModestCoder_ (赞：1)

[原题传送门](http://codeforces.com/problemset/problem/1110/B?csrf_token=5c7c36a779badf846118e6a7915707ec)

You have a long stick, consisting of mm segments enumerated from 11 to mm. Each segment is 11 centimeter long. Sadly, some segments are broken and need to be repaired.

You have an infinitely long repair tape. You want to cut some pieces from the tape and use them to cover all of the broken segments. To be precise, a piece of tape of integer length tt placed at some position ss will cover segments s,s+1,…,s+t−1s,s+1,…,s+t−1.

You are allowed to cover non-broken segments; it is also possible that some pieces of tape will overlap.

Time is money, so you want to cut at most kk continuous pieces of tape to cover all the broken segments. What is the minimum total length of these pieces?

Input
The first line contains three integers nn, mm and kk (1≤n≤1051≤n≤105, n≤m≤109n≤m≤109, 1≤k≤n1≤k≤n) — the number of broken segments, the length of the stick and the maximum number of pieces you can use.

The second line contains nn integers b1,b2,…,bnb1,b2,…,bn (1≤bi≤m1≤bi≤m) — the positions of the broken segments. These integers are given in increasing order, that is, b1<b2<…<bnb1<b2<…<bn.
Output
Print the minimum total length of the pieces.
input
4 100 2
20 30 75 80
output
17
input
5 100 3
1 2 4 60 87
output
6
Note
In the first example, you can use a piece of length 1111 to cover the broken segments 2020 and 3030, and another piece of length 66 to cover 7575 and 8080, for a total length of 1717.

In the second example, you can use a piece of length 44 to cover broken segments 11, 22 and 44, and two pieces of length 11 to cover broken segments 6060 and 8787.

**题目大意：**

总长度为m的纸上，有n个点，点的位置为b数组，现用k条线段覆盖所有的点，求线段总长度最小值

开始想到的是O(n^2)的DP，然后发现n<=100000，果断淘汰

仔细一想，有玄机！

若有一条线段覆盖了两个必须要覆盖的点，那么这两点中间的普通点也被覆盖，线段总长度就是被覆盖的普通点+所有必须覆盖的点
所以我们令被覆盖的普通点最少

然后普通点是一段一段来的，就是两个必须覆盖的点的间隔，所以只要算出间隔，排个序就行了


Code：

```cpp
/*
4 100 2
20 30 75 80
*/
#include <bits/stdc++.h>
#define res register int
#define ll long long
#define maxn 100010
using namespace std;
int n, m, k, c[maxn];

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1; c = getchar();
	}
	while (c >= '0' && c <= '9') s = (s << 1) + (s << 3) + (c ^ 48), c = getchar();
	return s * w;
}

int main(){
	n = read(), m = read(), k = read();
	int a = read(), b = 0;
	for (res i = 2; i <= n; ++ i){
		b = read(); c[i - 1] = b - a - 1; a = b;
	}
	sort(c + 1, c + n);
	int ans = 0;
	for (res i = 1; i <= n - k; ++ i) ans += c[i];
	printf("%d\n", ans + n);
	return 0;
}
```


---

## 作者：Zechariah (赞：1)

这个题其实并不难。  
不难发现，不管我们怎样去覆盖，按照题目要求，有$n$个点是必须覆盖的，因此我们考虑先单独覆盖每个点，这样的话需要$n$段来覆盖，考虑到题目给我们加了一个最多$k$段的限制，观察一下怎么样会减少段数。  
很容易推出：如果你把相邻两个点连起来（中间全部覆盖），会使得段数-1，也就是这两个点分别所在的段合并成一个段。  
所以做法就很明显了，把每一个中间段（不包含两个端点）拿出来排序，去掉最大的$k-1$个（保留较小的$n-k$个，因为目前总段数是$n$，按照上述结论这样操作后剩余段数是$n-(n-k)=k$个），剩余的中间段求和，再加上$n$，这样就可以保证总花费最少了  
复杂度$O(nlogn)$
```cpp
#include <bits/stdc++.h>
#define jh(x,y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 1e5 + 5, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
    inl ll read()
    {
        rg ll num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    inl int chread(rg char s[])
    {
        rg int len = 0;
        rg char ch;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        s[len++] = ch;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            s[len++] = ch;
        s[len] = 0;
        return len;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg long long x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
int b[N], n, m, k, ans, t[N];

int main(void)
{
    n = fast_IO::read(), m = fast_IO::read(), k = fast_IO::read(), ans = 0;
    for (rg int i = 1; i <= n; ++i)b[i] = fast_IO::read();
    for (rg int i = 1; i != n; ++i)t[i] = b[i + 1] - b[i] - 1;
    sort(t + 1, t + n);
    for (rg int i = 1; i <= n - k; ++i)ans += t[i];
    fast_IO::write(ans + n);
    return 0;
}

```

---

## 作者：Bulyly (赞：0)

### 前言
在 nowcoder 上做到了这道题，于是准备在洛谷水一下社区贡献。

### 解析
- 可以发现破裂的点只有和前后两点连与不连两种状态，可以贪心的考虑如果它和相邻点接近的话就连，反之不连。

- 怎么实现？可以用差分来维护相邻点之间的距离，很显然 $k$ 个胶带将点分为了 $k$ 个连续部分，这等价于我们需要寻找 $k-1$ 个断点。

- 显然的，断点前后距离之差越大，它对减少胶带长度的贡献就最大，所以我们取前后距离前 $k-1$ 大的地方为断点。

下附代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N=100010;
int n,m,k;
int a[N],p[N];
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)  scanf("%d",&a[i]);
    for(int i=2;i<=n;i++)   p[i]=a[i]-a[i-1];
    sort(p+2,p+n+1);
    int ans=0;
    for(int i=2;i<=n-k+1;i++)  ans+=p[i];
    
    printf("%d\n",ans+k);
    return 0;
}
```
完结撒花~


---

## 作者：Hooch (赞：0)

### 题目大意

一共有 $n$​ 个点分布在 $1,2,3\cdots m$​ 中，你有 $k$​ 条胶布。

每条胶布可以有无限长。

现在让你用胶布覆盖 $n$​ 个点，最终每条胶布长度和最小，输出这个长度和。

### 思路

最开始被这个屑翻译坑了，以为是每条胶布长度相等，求最小的胶布长。

样例都没看，就搞了个二分，果然样例不过。翻译了英文题面终于看懂了。

于是我们就能想到一个贪心：

两个相邻的点的距离可以看做**覆盖那个点的胶布的一部分**。

于是我们取最小的距离，这样既可以保证能覆盖 $n$ 个点，还能使答案最小。

整个差分数组，`sort` 一遍，取 $n-k$​ 个距离（因为一条胶布**至少能覆盖一个点**，于是 $k$ 个点就不用算了）。

我们在添加的过程中还要处理一个 $cnt$，表示处理中已经覆盖了多少个点。

最后要用总长度加上 $n-cnt$​​​​​​​，因为 $cnt<n$​​​​​​​ 时，一定要用其他剩余的胶布**单独覆盖没有覆盖到的点**。（为什么一定剩下多余的胶布，之前已经解释过了）

代码：

```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (int i(j); i <= n; ++i)
#define rep2(i, j, n) for (int i(j); i >= n; --i)
#define il inline
using namespace std;
template <typename T>
il void read(T &x) {
   x = 0; T f = 1; char ch = getchar();
   while (!isdigit(ch)) x = (ch == '-') << 1, ch = getchar();
   while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = getchar();
   x *= f;
}
const int N = 1e5 + 5, inf = 0x3f3f3f3f;
int n, m, k, a[N]; bool vis[N];//vis[i]存i有没有被胶布覆盖
struct node {int i, j, dis; il bool operator < (const node &x) const {return dis < x.dis;}} d[N];
main() {
	read(n); read(m); read(k);
	rep1(i, 1, n) {
		read(a[i]); if (i != 1) d[i - 1] = (node) {i, i - 1, a[i] - a[i - 1]};//处理距离
	}
	sort(d + 1, d + n);/*从小到大排序*/ int cnt = 0, sum = 0;
	rep1(i, 1, n - k/*n-k个距离*/) {
		if (!vis[d[i].i] && !vis[d[i].j]) cnt += 2, ++sum;
		else ++cnt; //分类对cnt处理
		sum += d[i].dis;
		vis[d[i].i] = vis[d[i].j] = 1;
	}
	printf("%d", sum + (n - cnt)/*剩余n-cnt个点是单独覆盖的，所以要加n-cnt*/);
}
```



---

## 作者：_easy_ (赞：0)

# 思路
通过读题，可以发现我们必须使用 $k$ 长度的胶带，剩下没有覆盖的就需要通过覆盖两个点的区间来覆盖。换句话说，就是要覆盖 $k$ 个点和 $n-k$ 个区间。

拿样例来说，首先花费 $2$ 长度的胶带覆盖两个点（注意，不是前两个），再将两点之间的区间长度排序，覆盖前 $2$ 个，也就是 $20$ 到 $30$ 和 $75$ 到 $80$。最后将总和加起来就行了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k,a[100005],s[100005],ans;
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		s[i]=a[i]-a[i-1];
	}
	s[1]=INT_MAX;//排除第一个
	if(n==k){
		cout<<n;
		return 0;
	}//注意，如果胶带和点一样多，就直接每个点覆盖一个长度为1的就行了。
	ans=k;//先覆盖k个点。
	sort(s+1,s+n+1);
	n-=k;
	for(int i=1;i<=n;i++){
		ans+=s[i];//加上区间长，注意因为我们已经覆盖了一个点了，所以加长度的时候不用加1。
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xukuan (赞：0)

区间贪心

正难则反，我们把它当成一个区间拆解问题

我们把它拆成k个区间，意味者要拆k-1次

每一次显然拆区间长度最长的。

代码（codeforces评测id：49573821），我的比赛代码
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll n,m,k,a[100010],b[100010],ans;

inline bool cmp(ll x,ll y){
	return x>y;
}

int main(){
	cin>>n>>m>>k;
	for(ll i=1; i<=n; i++) scanf("%I64d",&a[i]);
	for(ll i=1; i<n; i++) b[i]=a[i+1]-a[i]-1;//算出每一个区间的长度，这里要注意，区间两端一定要被覆盖，相当于一个两端都不种的植树问题
	ans=a[n]-a[1]+1;//答案初值就是区间总长
	sort(b+1,b+1+n,cmp);//按区间长度从长到短排序
	for(ll i=1; i<k; i++) ans-=b[i];//减去前k-1长的区间
	cout<<ans;//输出
	return 0;
}
```

---

## 作者：hpbl (赞：0)

贪心+维护可重复前k小值

首先可以想到把每个坏的地方单独修理，共用磁带$n$

然后再把$n-k$个相邻的放在一起修，这样就可以保证最多用$k$段磁带

我们会发现你选哪$n-k$段是无所谓的，所以只要维护前$n-k$小的相邻两点距离即可

这里就有点毒瘤了

我先前并不知道```multiset```删除末尾元素时，会把```multiset```中的每个和这个元素相等的都删掉

然后```Wrong Answer On Test 10```$\times 2$

最后发现这点后加了个```map```判断末尾元素是否需要全部删除后才过了

附上代码

抄题解勿扰
```cpp
include<cstdio>
include<set>
include<map>
using namespace std
int n,m,k,lst,nw,tp,t;
multiset<int> s;
map<int,int> mp;
int main()
{
    scanf("%d %d %d",&n,&m,&k);
    tp=n-k;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nw);
        if(lst) s.insert(nw-lst),mp[nw-lst]++;
        if(s.size()>n-k)
        {
            mp[*(--s.end())]--;
            if(!mp[*(--s.end())]) s.erase(*(--s.end()));
        }
        lst=nw;
    }
    for(set<int>::iterator it=s.begin();it!=s.end(),t<tp;it++,t++)
        k+=*it;
    printf("%d",k);
}
```

---


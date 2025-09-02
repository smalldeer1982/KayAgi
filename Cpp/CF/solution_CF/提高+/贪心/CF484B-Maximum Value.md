# Maximum Value

## 题目描述

You are given a sequence $ a $ consisting of $ n $ integers. Find the maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484B/f78b808248b814b54b378a7e1094ac9b8497b197.png) (integer remainder of $ a_{i} $ divided by $ a_{j} $ ), where $ 1<=i,j<=n $ and $ a_{i}>=a_{j} $ .

## 样例 #1

### 输入

```
3
3 4 5
```

### 输出

```
2
```

# 题解

## 作者：fuqingchen (赞：21)

# 题解

首先有一个广为人知的公式：$a \bmod b = a - k \times b$ 设 $k = \lfloor\frac{a}{b}\rfloor$。

接着将序列去重并排序。接着就可以枚举 $b$ 和 $k$，在排序后的序列中二分 $a$，取最大值作为答案。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
namespace get {
	inline char nc() {
		static char buf[1000010], *p1 = buf, *p2 = buf;
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000010, stdin), p1 == p2) ? EOF : *p1++;
	}
}
using namespace std;
//#define getchar get::nc
namespace read {
	inline void rd(char *s) {
		char c = getchar();
		while (c != ' ' && c != '\n' && c != '\r') *(++s) = c, c = getchar();
		*(s + 1) = 0;
	}
	inline void rd(char &c) {
		do c = getchar();
		while (c == ' ' || c == '\n' || c == '\r');
	}
	template<typename T> inline void rd(T &x, int f = 1, char c = getchar()) {
		x = 0;
		while (c > '9' || c < '0') f = (c == '-') ? -1 : 1, c = getchar();
		while (c <= '9' && c >= '0') x = x * 10 + (c ^ 48), c = getchar();
		x *= f;
	}
}
using namespace read;
namespace write {
	#define ps puts("")
	#define pc putchar(' ')
	template<typename T> inline void wr(T x) {
		short _wr[40];
		if (x < 0) putchar('-'), x = -x;
		int _top = 0;
		do _wr[++_top] = x % 10, x /= 10;
		while (x);
		while (_top) putchar(48 | _wr[_top--]);
	}
	inline void wr(char c) {putchar(c);}
	inline void wr(char *s) {
		int pl = 1;
		while (s[pl]) putchar(s[pl++]);
	}
	inline void wr(const char *s) {
		int pl = 0;
		while (s[pl]) putchar(s[pl++]);
	}
	template<typename T, typename ...Args> inline void wr(T x, Args... Rest) {wr(x), wr(Rest...);}
}
using namespace write;
int n, a[200010], res;
signed main() {
	rd(n);
	for (int i = 1; i <= n; ++i) rd(a[i]);
	sort(a + 1, a + 1 + n);
	n = unique(a + 1, a + 1 + n) - a - 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= a[n] / a[i]; ++j)
			res = max(res, a[lower_bound(a + 1, a + 1 + n, a[i] * (j + 1)) - a - 1] % a[i]);
	wr(res);
	return 0;
}
```

## 时间复杂度证明

可以发现时间复杂度最多为 $\sum_{i = 1}^{2 \times 10^5} 10 ^ 6 / i$。

显然该式小于 $\sum_{i = 1}^{10^6} 10 ^ 6 / i$，而根据调和级数，该式约为 $n \log n$ 级别，证毕。

---

## 作者：QwQcOrZ (赞：14)

我们知道 $a\ mod\ b$ 可以化成 $a-kb$（$a,b,k$ 都是整数，$k=\left\lfloor\dfrac{a}{b}\right\rfloor$）的形式

于是可以发现 $kb\le a<(k+1)b$

那么就先枚举 $k$ 和 $b$，因为$a<(k+1)b$，所以可以二分最大的符合条件的 $a$，取最大的 $a\ mod\ b$ 的值即可

于是可以轻松过掉此题

$Code\ Below$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
const int inf=INT_MAX;

inline int read()
{
	register int s=0;
	register char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(register int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
inline void print(const register int x,const register char c='\n')
{
	write(x);
	putchar(c);
}
int a[N];

int main()
{
	int n=read(),ans=0;
	for (int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+1+n);
	n=unique(a+1,a+1+n)-a-1;//排序去重，方便二分
	a[n+1]=inf;//二分时防止此时的(k+1)b>a[n]而导致错误
	for (int i=1;i<=n;i++)//枚举b
	for (int j=2*a[i];j-a[i]<=a[n];j+=a[i])//枚举(k+1)b
	{
		int k=lower_bound(a+1,a+n+2,j)-a-1;//显然大于等于(k+1)b的第一个数的前一个就是小于(k+1)b的最大值
		ans=max(ans,a[k]%a[i]);
	}
	print(ans);

	return 0;
}
```

---

## 作者：Warriors_Cat (赞：6)

主要思路是按照数值分块暴力。

### $Solution:$

很显然我们可以取两个相同的数，所以 $ans \ge 0$，然后对原序列排列去重。

由于 $a_i \le 10^6$，所以我们可以按照 $a_i \le 10^3$ 和 $a_i > 10^3$ 来分来处理。

因为已经去重，所以 $a_i \le 10^3$ 的个数最多只有 $1000$ 个，直接每次 $O(n)$ 暴力也不会 TLE。

对于 $a_i \ge 10^3$，发现它的倍数不超过 $10^3$，所以直接枚举 $a_i$ 的倍数，然后用 `lower_bound` 找前驱就行。

总时间复杂度为 $O(n\sqrt V \log n)$，而且跑不满。

亲测过全部按照 $a_i \ge 10^3$ 的情况会快很多，似乎也是跑不满的缘故（

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read(){
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
    return x * f;
}
int n, a[200010], k, ans;
inline int getid(int x){
	return lower_bound(a + 1, a + k + 2, x) - a - 1;
}
int main(){
	n = read(); for(register int i = 1; i <= n; ++i) a[i] = read();
	sort(a + 1, a + n + 1); k = unique(a + 1, a + n + 1) - a - 1;
	a[k + 1] = 0x7f7f7f7f;//注意边界问题
	for(register int i = 1; i <= k; ++i){
		if(a[i] <= 1000){
			for(register int j = i + 1; j <= k; ++j) ans = max(ans, a[j] % a[i]);
		} //块内暴力
		for(register int j = 2; a[i] * (j - 1) <= a[k]; ++j){
			ans = max(ans, a[getid(a[i] * j)] % a[i]);
		} //块外暴力
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：Hovery (赞：4)

## Problem

[Maximum Value](https://www.luogu.com.cn/problem/CF484B)

## Sol

这题我一开始想的是一个暴力，枚举 $a_i$ 的倍数 $x$ ，在 $a$ 中找与 $x$ 接近的数，并统计答案。（注：上文及下文的 $a$ 是去重后的数组）。

有了这个暴力后，发现对于答案是在值域上操作的，考虑根号分治。

定一个值域 $B$。

$1.\ a_i \le B$ 时直接暴力枚举比 $a_i$ 大的所有数统计答案，时间复杂度为 $\mathcal O(n \times B)$。

$2.\ a_i > B$ 时枚举倍数，然后枚举出的倍数放到 $a$ 中去二分，取附近两个就行，时间复杂度为 $\mathcal O(\frac{n\log n \times \max_{i = 1}^{n}{a_i}}{B})$。

总的时间复杂度为 $\mathcal O(n\log n\times \sqrt{\max_{i = 1}^{n}{a_i}})$ 。由于这是一个很松的上界，可以轻松过掉这道题。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int n, a[200010], ans = 0;

signed main()
{
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i];
	}
	sort(a + 1, a + n + 1);
	n = unique(a + 1, a + n + 1) - a - 1;
	for (int i = 1;i <= n;i++)
	{
		if (a[i] <= 900)
		{
			for (int j = i + 1;j <= n;j++)
			{
				ans = max(ans, a[j] % a[i]);
			}
		}
		else {
			for (int j = a[i];j <= a[n];j += a[i])
			{
				int _ = lower_bound(a + 1, a + n + 1, j) - a;
				ans = max(ans, a[_] % a[i]);
				_--;
				if (a[_] > a[i])
				ans = max(ans, a[_] % a[i]);
			}
			ans = max(ans, a[n] % a[i]);
		}
	}
	cout << ans;
}
```

---

## 作者：创世游戏科技 (赞：3)

# Maximum Value

## 题目大意

给定一个序列 $a_i$，请找出两个数 $i,j$，使得 $a_i \ge a_j$，并且使得 $a_i \bmod a_j$ 的值最大，求这个 $a_i\bmod a_j$ 的最大值。

## 思路解析

考虑 $a_i \bmod a_j$ 在模数为 $a_j$ 下的值具有循环意义。

那么 $p \bmod a_j$ 的值在 $p\in\left[0,a_j\right),\left[a_j,2a_j\right)...\left[ka_j,(k+1)a_j\right)$ 等区间构成的值组成的集合是相等的。

这启发我们查询 $a_i \bmod a_j$ 的最大值，在 $a_j$ 确定的情况下，我们只需要分别查询 $a_i\in\left[0,a_j\right),\left[a_j,2a_j\right)...\left[ka_j,(k+1)a_j\right)$ 的最大值 $m \bmod a_j$ 的最大值即可。

考虑为什么这样做是对的呢，因为每个区间都包含了取模结果的值域，在区间内部答案是单调递增的，包含了答案**所有的极值点**，他们的最大值就是答案的最值。

![](https://cdn.luogu.com.cn/upload/image_hosting/e3pu4nqh.png)

类似上图。

我们可以用 st 表维护值域区间最大值，具体而言，我们令一个数组 $a_i$ 的位置的值为 $a_i$，这时 st 表维护的区间就是值域区间最大值。

注意题目要求 $a_i \ge a_j$，所以需要舍去第一个区间，注意边界值处理即可。

## 参考实现


```
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;
const int MAXK=1e6+10;
int n,m,a[MAXN],st[MAXK+20][31],mx,lg[MAXN];
int solve(int l,int r){
	int log2r=lg[r-l+1];
	return max(st[l][log2r],st[r-(1<<log2r)+1][log2r]);
}
int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    for(int i=2;i<MAXK;i++)lg[i]=lg[i/2]+1;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],st[a[i]][0]=a[i],mx=max(mx,a[i]);
	int log2n=lg[mx];
	for(int j=1;j<=log2n;j++){
		for(int i=0;i<=mx-(1<<j)+1;i++){
            st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
    int ans=0;
    for(int i=1;i<=mx;i++){
        if(!st[i][0])continue;
        for(int j=i;j<=mx;j+=i){
            int r=solve(j,min(mx,j+i-1));
            ans=max(ans,r%i);
        }
    }
    cout<<ans;
	return 0;
}
```

---

## 作者：N_Position (赞：3)

# CF484B
## 题目大意
给定长度为 $n$ 的数列 $a_i$，求 $a_i \bmod a_j$ 的最大值，其中 $a_i > a_j$。

## 题目分析
显然的几个性质：
- 重复的 $a_i$ 对答案没有新的贡献，即相同的数只计算一次即可。
- 设 $\lfloor\frac{a_i}{a_j}\rfloor=k$，则对于同一个 $a_i$ 和 $k$，$a_j$ 越大时，$a_i \bmod a_j$ 越大。

所以我们考虑先排序，再枚举 $k$ 的值即可。

时间复杂度为：$O(\sum_{i=1}^{1\times10^6}\frac{n}{i})$。

化简后即：$O(n\log n)$。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
const int MAX = 2e6+5;
int f[MAX];
int a[N],ans = -1;
bool cmp(int X,int Y){
	return X < Y;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	sort(a+1,a+1+n,cmp);
	int t = unique(a+1,a+1+n) - a-1;
	int maxn = a[t];
	for(int i=1;i<=t;i++){
		f[a[i]] = a[i]; 
	}
	for(int i=1;i<MAX;i++){
		if(f[i] == 0){
			f[i] = f[i-1];
		}
	}
	int ans = 0;
	for(int i=1;i<=t;i++){
		for(int j=1;(j-1)*a[i] <= maxn;j++){
			int now = j*a[i]-1;
			if(f[now] > a[i]){
//				cout<<f[now]<<' '<<a[i]<<' '<<ans<<'\n';
				ans = max(ans,f[now] % a[i]);
			}
		}
	}
	printf("%d",ans);
}
```

---

## 作者：Mine_King (赞：2)

众所周知，$a \bmod b$可以转化成$a - kb,k=\lfloor \frac{a}{b} \rfloor$（也就是带余数的除法中的商）。并且可以发现$kb \le a < (k+1)b$（如果$(k+1)b \le a$，那么$k$就应该等于$k+1$而不是$k$，显然就不成立了）。 

于是对于这题，我们可以先枚举$b$（即题目中的$a_j$），然后枚举$(k+1)b$（当然枚举$k$也行），然后对于找到的$k$和$b$，可以二分找到一个$a_x$，使得$a_x \ge (k+1)b > a_{x-1}$（但是输入的序列并不是有序的，所以需要先排序）。  

但是我们考虑极限数据：$a=1,1,1,\cdots,10^6$，发现这好像卡不过去？于是我们就想到了去重。那么如果去重则极限数据就是$a=1,2,3,\cdots,n-1,10^6$，这样应该就可以卡过去了（还跑得飞快QAQ）。

**code：**
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,ans,a[200005];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	n=unique(a+1,a+n+1)-a-1;
	a[n+1]=1e9;
	for(int i=1;i<=n;i++)
		for(int j=a[i]*2;j-a[i]<=a[n];j+=a[i])
		{
			int k=lower_bound(a+1,a+n+2,j)-a-1;
			if(a[k]%a[i]>ans) ans=a[k]%a[i];
		}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：UperFicial (赞：1)

貌似没人写严格 $O(n\sqrt{V})$ 的做法。

根号分治，记 $V=\max a_i$，阈值为 $B$。

对于 $a_i>B$，形如 $[Ka_i,(K+1)a_i)$ 的段不超过 $\frac{V}{B}$ 个，每个段取最大的数最优，考虑预处理 $pre_i$ 表示 $\le i$ 的数的最大值，那么这一部分可以做到 $O(\frac{m}{B})$。

对于 $a_i\le B$，$[a_i,2a_i)$ 段长不超过 $B$，可以枚举枚举其中每一个数 $j$，若存在 $a_k=x\ge a_i$ 满足 $x\bmod a_i=j-a_i$，那么 $j$ 合法。考虑预处理 $d_{i,j}$ 表示是否存在一个 $a_k=x$ 满足 $x\bmod i=j$ 即可做到 $O(B)$ 处理。

当 $B=\sqrt{V}$ 时取到最优复杂度 $O(n\sqrt{V})$。

```cpp
int main()
{
	n=read();
	rep(i,1,n) a[i]=read(),vis[a[i]]=true;
	rep(i,1,N) if(vis[i]) pre[i]=i;else pre[i]=pre[i-1];
	int B=1000;
	rep(i,1,n)
		rep(j,1,Min(a[i],B)) d[j][a[i]%j]=true;
	rep(i,1,n)
	{
		if(a[i]<=B)
		{
 
			rep(j,a[i]+1,Min(a[i]+a[i]-1,N)) if(d[a[i]][j-a[i]]) ans=Max(ans,j-a[i]);
		} 
		else
		{
			rep(j,2,B)
			{
				int r=Min(N,a[i]*j-1);
				if(pre[r]>a[i]) ans=Max(ans,pre[r]%a[i]);
				if(r==N) break;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：LiJoQiao (赞：1)

[更好的阅读体验](https://www.cnblogs.com/LiJoQiao/p/18017825)  

------------------------
朴素的办法是枚举每两个数然后更新取模的结果。时间复杂度为 $O(n^2)$ 不能通过。

这个朴素的过程可以看作枚举一个数然后找对其取模最大值的过程。

我们可以枚举一个数，然后再枚举以它的倍数为两端的区间，找其中取模的最大值。  
找最大值的过程可以二分或双指针。  
值域很小，也可以用预处理小于某个值的最大值的方法来 $O(1)$ 查找。

代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int MAXN=2e5+10;
int n,a[MAXN],le[2000010],ans;
namespace sol{
    void solve(){
        scanf("%d",&n);
        for(int i=1;i<=n;++i)scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        n=unique(a+1,a+n+1)-(a+1);
        int p=1;
        for(int i=a[1]+1;i<=2000000;++i){
            while(p<n&&a[p+1]<i)++p;
            le[i]=a[p];
        }
        for(int i=1;i<=n;++i){
            for(int j=2;(j-1)*a[i]<=a[n];++j){
                ans=max(ans,le[j*a[i]]-(j-1)*a[i]);
            }
        }
        printf("%d\n",ans);
    }
}
int main(){
    sol::solve();
    return 0;
}
```



---

## 作者：QianianXY (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF484B)

## 题目分析

模运算具有周期性，因此一个比较显然的做法就是根号分治了。

也许是脚造数据的问题，这题有的纯暴力会跑得更快。

有两种算法：

1、$O(n^2)$ 暴力枚举最大值。

2、枚举 $a_i$ 的倍数 $a_i\times k$（$k$ 为整数），二分查找 $a$ 中第一个小于等于 $a_i\times k$ 的数，与答案比较并更新。

当 $a_i$ 较大时，$a_i\times k$ 的数量会较少，使用算法二。

当 $a_i$ 较小时，周期较短，采用算法一较优。

阈值大约取到 $\sqrt{n}$ 就可以了。

排序去重可以优化用时。

## code

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 1000010
using namespace std;

template <typename T> inline void read(T &x)
{
	x = 0; int f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int n, a[N], T, maxn, ans; bool b[N];

int main()
{
	read(n); T = 1000;
	for (rei i = 1; i <= n; i++) read(a[i]);
	sort(a + 1, a + 1 + n); n = unique(a + 1, a + 1 + n) - a - 1; a[n + 1] = 1e9;
	for (rei i = 1; i <= n; i++)
	{
		if (a[i] < T) {for (rei j = i + 1; j <= n; j++) ans = max(ans, a[j] % a[i]); continue;}
		for (rei j = a[i] << 1; j <= a[n]; j += a[i]) ans = max(ans, a[lower_bound(a + 1, a + 1 + n, j) - a - 1] % a[i]);
		ans = max(ans, a[n] % a[i]);
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：fanfansann (赞：1)

## CF484B Maximum Value（2100，模运算，优化剪枝枚举）

**Problem**

给定一个序列 $a_i$ ，请找出两个数 $i,j$，使得 $a_i \ge a_j$ ，并且使得 $a_i \bmod a_j$  的值最大，求这个 $a_i\bmod a_j$  的最大值。

 $1 \le n \le 2\times 10^5,1 \le a_i \le 10^6$
 
**Solution**

我们要找的是最大的 $a_i\bmod a_j$。

那么显然有：

 $$a\mod b=a-\lfloor\frac{a}{b}\rfloor\times b=a-k\times b\ (\text{设}\ k=\lfloor\dfrac{a}{b}\rfloor)$$ 

显然 $a\mod b$ 得到的是余数，值一定$b$ 的简化剩余系内，即 $0\le a\mod b=a-k\times b<b$，所以一定有

$$\begin{aligned}&a>kb&\\ &a<(k+1)b\end{aligned}$$

我们可以枚举 $a[i]=b$，然后枚举倍数 $k$，使得 $kb<a,a=\max\{a[i]\}$，对于枚举到的 $b$ 和 $k$ ，我们可以直接二分找到最大的小于 $(k+1)b$  的数作为 $a$。

复杂度有点问题，考虑优化。首先这里两个相同权值的点的作用显然是完全一样的，所以我们可以先排序去重，这样我们会遇到的最坏的情况的数据就是 $1,2,\cdots n-1$，这样枚举 $k$ 的均摊复杂度为 $\dfrac{n(n+1)}{2}=1e6,n=\sqrt {\dfrac{1e6}{2}}=707$。

总复杂度为 $O(nlogn\sqrt m)≈2e9$ hhh

考虑继续优化：我们可以加上最优化剪枝，当枚举到的 $b<ans$ 的时候，显然求出来的 $a\mod b<b$ ，所以直接跳过就行了，这样的话我们就可以倒序枚举 $b$，这样我们在遇到的极端数据 $1,2,\cdots n-1$ 的时候，从大到小枚举，前面被更新了之后，基本上后半段遇到的所有的数都可以直接跳过，亲测效率极高。

优化之后跑的贼快，没有一个点超过150ms，在洛谷的提交记录里能排第二 hhh。

**Time**

$O(nlogn\sqrt m),m=\max\{a[i]\}$

**Code**

```cpp
// Problem: CF484B Maximum Value
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF484B
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Author: 繁凡さん https://fanfansann.blog.csdn.net/
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 7, M = 2e6 + 7, INF = 1e7;

int n, m;
int ans;
int a[N];
int maxx;

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++ i) {
		scanf("%d", &a[i]);
		maxx = max(maxx, a[i]);
	}
	sort(a + 1, a + n + 1);
	int num = unique(a + 1, a + n + 1) - a - 1;
	a[num + 1] = maxx;
	
	for(int i = num; i >= 1; -- i) {
		if(a[i] <= ans) continue;

		for(int k = 2; (k - 1) * a[i] <= a[num + 1]; ++ k) {//a > kb
			int val = k * a[i];//k -> k + 1 
			int aa = lower_bound(a + 1, a + num + 2, val) - a - 1;//a < (k + 1)b
			ans = max(ans, a[aa] % a[i]);
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：RainFestival (赞：1)

题意：给一个 $n$ 个数的数列 $a$ , 要求 $\max(a_i\bmod a_j)$ , 其中 $a_i>a_j$。

$n\le 200000,a_i\le 1000000$

定义 $k=\max\limits_{i=1}^{n} a_i$。

可以转化求 $\max(a_i-\lfloor \frac{a_i}{a_j}\rfloor\times a_j)$ , 其中 $a_i>a_j$。

我们对于每一个不同的数字作为 $a_i$。

枚举 $\frac{a_i}{a_j}$。

代码：

```cpp
#include<cstdio>
#include<algorithm>
struct bit
{
	int s[2000005],n;
	void setup(int sz)
	{
		for (int i=1;i<=n;i++) s[i]=0;
		n=sz;
	}
	int lowbit(int x)
	{
		return x&(-x);
	}
	void add(int x,int v)
	{
		for (;x<=n;x=x+lowbit(x)) s[x]=s[x]+v;
	}
	int query(int x)
	{
		int ans=0;
		for (;x>=1;x=x-lowbit(x)) ans=ans+s[x];
		return ans;
	}
	int find(int rk)
	{
		if (query(n)<rk) return -1;
		int x=0;
		for (int i=21;i>=0;i--)
		{
			x=x+(1<<i);
			if (x>n||s[x]>=rk) x=x-(1<<i);
			else rk=rk-s[x];
		}
		return x+1;
	}
};
int n,f[1000005],ans=0;
bit t;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		f[x]=1;
	}
	t.setup(2000000);
	for (int i=1;i<=1000000;i++) if (f[i]) t.add(i,1);
	for (int i=1000000;i>=1;i--)
	    if (f[i]&&i>ans)
		{
			for (int j=1;i*j<=1000000;)
		    {
				int k=t.find(t.query((j+1)*i-1));
		    	if (k/i==j) ans=std::max(ans,k%i);
		    	int x=t.find(t.query((j+1)*i-1)+1);
		    	if (x!=-1) j=x/i;
		    	else break;
			}
		}
	printf("%d\n",ans);
	return 0; 
}
//RP++
//QWQ
```

---

## 作者：Priestess_SLG (赞：0)

比较简单的，枚举 $a_i$ 和 $\lfloor\frac{a_i}{a_j}\rfloor$ 的值，显然这是调和级数级别的，然后因为这个东西有单调性，所以对于上面的信息直接二分出最大的 $a_j$ 的值就做完了。时间复杂度 $O(n\log n\log V)$，需要卡常。

upd：对上述显然结论的证明：对于每一个 $a_j$，设 $a_i$ 的上限是 $V$，则 $\lfloor\frac{a_i}{a_j}\rfloor$ 能取到的最大的值是 $\lfloor\frac{V}{a_j}\rfloor$，总量级不超过 $\sum\limits_{i=1}^V\lfloor\frac{V}{i}\rfloor$。又有经典结论 $\sum\limits_{i=1}^V \frac{V}{i}\approx V\log V$，且 $\sum\limits_{i=1}^V\lfloor\frac{V}{i}\rfloor\le \sum\limits_{i=1}^V\frac{V}{i}$，因此 $\sum\limits_{i=1}^V\lfloor\frac{V}{i}\rfloor\approx V\log V$（甚至还要小一点）。因此证毕。

[AC Code](https://codeforces.com/contest/484/submission/299258426)

---

## 作者：_Kenma_ (赞：0)

# CF484B 解题报告

## 前言

模拟赛 T2。

感觉很有意思，题意也很简洁。

CCF 能不能学一学这种命题风格。

## 思路分析

首先肯定不能暴力。

考虑发掘关于 $a_i \bmod a_j$ 的性质。

发现可以把 $a_i \bmod a_j$ 转化为 $a_i- \lfloor \frac{a_i}{a_j} \rfloor \cdot a_j$。

应该算是经典变形了。

然后因为枚举 $a_i$ 不可做，所以考虑枚举 $\lfloor \frac{a_i}{a_j} \rfloor$。

好像就做完了。

具体地，我们枚举 $a_j$，对于每一个 $a_j$ 枚举 $\lfloor \frac{a_i}{a_j} \rfloor$ 的值，用 set 维护当前剩余的 $a_i$ 的值，直接在 set 上查找合法的 $a_i$，并且在当前合法的 $a_i$ 中选择最优的一个，用 $a_i \bmod a_j$ 更新答案即可。

时间复杂度 $O(n\log^2 n)$。没有区分 $n$ 和 $v$。

好像 set 需要卡卡常。

## 代码实现

具体实现看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,maxn,a[200005];
bool cmp(int x,int y){
	return x<y;
}
set<int> s; 
int main(){
	//freopen("data.in","r",stdin);
	//freopen("WA.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]; 
		maxn=max(maxn,a[i]);
	}
	sort(a+1,a+1+n,cmp);
	n=unique(a+1,a+1+n)-a-1;
	for(int i=1;i<=n;i++){
		s.insert(a[i]);
	}
	for(int i=1;i<=n;i++){
		s.erase(a[i]);
		if(ans>=a[i]) continue;
		for(int j=a[i];;j+=a[i]){
			set<int>::iterator it=s.lower_bound(j);
			if(it==s.begin()){
				if(j>=maxn) break;
				else continue;
			}
			it=prev(it);
			ans=max(ans,(*it)%a[i]);
			if(j>=maxn) break;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：WorldMachine (赞：0)

有 $\mathcal O(N\log N)$ 的做法，但是老师让用根号分治做(￣▽￣)"

设定阈值 $B$。枚举 $a_i$，如果 $a_i\leq B$，那么我们直接枚举余数 $r$，判断是否存在一个元素 $t$ 使得 $t\bmod a_i=r$ 即可。所以我们需要预处理出 $v_{i,j}$，表示是否存在一个元素 $t$，使得 $t\bmod i=j$。这一部分的预处理复杂度为 $\mathcal O(NB)$，单次获取答案的复杂度为 $\mathcal O(B)$。

如果 $a_i>B$，枚举每一个长度为 $a_i$ 的值域段，获取段内最大的数即可。所以我们需要预处理出 $\text{maxx}_i$，表示不大于 $i$ 的最大数。这一部分的预处理复杂度为 $\mathcal O(V)$，单次获取答案的复杂度为 $\mathcal O\left(\dfrac VB\right)$。

$N,V$ 同级，取 $B=\sqrt V$，有最优复杂度 $\mathcal O(N\sqrt N)$。

---

## 作者：Richard_Whr (赞：0)

# Maximum Value

##### 模拟赛T2，赛时打了暴力竟然过了。。。

### 优化思路：模数转减法。

 $A \bmod B = A - k \times B$ 其中 $k =  \lfloor \frac{A}{B} \rfloor$。
 
 其中若 $B$，$k$ 确定，$A$ 要符合条件：
 
 $A \ge k \times B$ 且 $A<(k+1)\times B$

我们在这个范围中最大化 $A$ 的数值，就等价于最大化 $ans$ 的数值。

因此可以考虑**排序+去重+二分**，因为顺序不影响答案，以此来找到最大的符合条件的 $A$。

枚举 $k$ ( 其实是 $(k+1) \times  B)$ 和 $B$。

寻找第一个 $ \ge (k+1) \times B$ 的，他的左边一个就是最大化的 $A$，同时更新答案。

同时不要忘记，若 $k \times B > $ 最大数了，那么就没有必要再算了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
int n;

int main()
{
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	
	sort(a+1,a+1+n);
	n=unique(a+1,a+1+n)-a-1;
	
	int res=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=a[i]*2;j-a[i]<=a[n];j+=a[i])
		{
			int k=lower_bound(a+1,a+1+n,j)-a-1;
			res=max(res,a[k]%a[i]);	
		}
	}	
	
	printf("%d",res);
	
	return 0;
}
```


---


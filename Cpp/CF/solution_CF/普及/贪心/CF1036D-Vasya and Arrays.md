# Vasya and Arrays

## 题目描述

Vasya has two arrays $ A $ and $ B $ of lengths $ n $ and $ m $ , respectively.

He can perform the following operation arbitrary number of times (possibly zero): he takes some consecutive subsegment of the array and replaces it with a single element, equal to the sum of all elements on this subsegment. For example, from the array $ [1, 10, 100, 1000, 10000] $ Vasya can obtain array $ [1, 1110, 10000] $ , and from array $ [1, 2, 3] $ Vasya can obtain array $ [6] $ .

Two arrays $ A $ and $ B $ are considered equal if and only if they have the same length and for each valid $ i $ $ A_i = B_i $ .

Vasya wants to perform some of these operations on array $ A $ , some on array $ B $ , in such a way that arrays $ A $ and $ B $ become equal. Moreover, the lengths of the resulting arrays should be maximal possible.

Help Vasya to determine the maximum length of the arrays that he can achieve or output that it is impossible to make arrays $ A $ and $ B $ equal.

## 样例 #1

### 输入

```
5
11 2 3 5 7
4
11 7 3 7
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
1 2
1
100
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3
1 2 3
3
1 2 3
```

### 输出

```
3
```

# 题解

## 作者：SCAR_L (赞：4)

## 尺取法题解    

------------

经过本蒟蒻的观察，题解区大部分大佬用的是二分或贪心，所以本蒟蒻来写一篇尺取法的题解。

### 尺取法：
尺取法是什么呢？~~很简单~~我们先来看一道题：

提供一个数组 $a$，选出一个子序列，且子序列之和 $\ge k$。问子序列有几种选法？
($1 \leq a(i) \leq 10^5$, $1 \leq n \leq 10^5$, $1 \leq k \leq 10^{10}$)

首先，这题肯定不能写暴力，普通前缀和也不行，因为 $O(n^2)$ 也会TLE。
```cpp
for(int l = 1; l <= n; l++) //普通前缀和
  for(int r = l; r <= n; r++)
    if(s[r] - s[l-1] >= k)
      ans++;
```
但我们可以优化（因为 $a(i)$ 不为负数，所以若 $[l, r]$ 合法则 $[l, r+1]$ 也合法）: 
```cpp
for(int l = 1; l <= n; l++)
  for(int r = l; r <= n; r++)
    if(s[r] - s[l - 1] >= k)
    {
        ans += n - r + 1;    //优化
        break;
    }
```
还是会超时。  

------------

我们再来观察一下：      
设 **k=10, a = 5 1 3 4 2**，如图（合法用粗体表示）：

| |l=1|l=2|l=3|l=4|l=5|
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
|r=1|   5  |  X   | X | X | X |
|r=2|   6  |  1   | X | X | X |
|r=3|   9  |  4   | 3 | X | X |
|r=4|**13**|  8   | 7 | 4 | X |
|r=5|**15**|**10**| 9 | 6 | 2 |
我们发现 **若区间 $[l, r]$ 合法，则 $[l+1, r-1]$ 一定不合法**。 

则我们继续可优化代码
```cpp
int r = 0;
for(int l = 1; l <= n; l++)
    while(r <= n)
    {
        if(s[r] - s[l - 1] >= k)	
        {
            ans += n - r + 1;
            break;
        }
        r++;
    }
```
## 这就是尺取法(又名双指针)
 注：尺取法的时候也要做前缀和

那尺取法和这道题有什么关系呢？~~没有关系你讲啥呀~~
#### 很显然，$i$ 和 $j$ 都不可减少，所以时间复杂度就从 $O(n^2)$ 变成了 $O(n)$。
------------
# 代码与实现：
首先，输入时写个前缀和：
```cpp
cin >> n;
for(int i = 1; i <= n; i++) 
{
    scanf("%d", &a[i]);	//用scanf更快
    a[i] += a[i - 1];	//我把前缀和写在原数组里了
}
cin >> m;
for(int j = 1; j <= m; j++) 
{
    scanf("%d", b[i]);
    b[j] += b[j - 1];
}
```
------------
再加个简简单单的判断：
```cpp
if(a[n] != b[m]) return printf("-1"), 0;	//码风丑请忽视
```
------------
### 接下来就是本题精髓（尺取法）：
```cpp
long long ans = 0, i = 1, j = 1;//其实用int也行，只不过long long更保险
while(i <= n && j <= m)
{
    if(a[i] == b[j])	//如果当前两段相等
        ans++, i++, j++;
    else if(a[i] > b[j]) j++;
    else if(a[i] < b[j]) i++;
}
```
------------
快乐的输出：
```cpp
return printf("%d", ans), 0;	//码风丑请忽视
```
------------
这时有人就会问了：你每截一段为什么不清零呢？   
因为（~~没法清零~~）两个数加上一样的差不变（同增同减差不变）

------------
### 结语：
好了，这就是[Vasya ans Arrays](https://www.luogu.com.cn/problem/CF1036D)这道题了，至于[完整代码](https://www.luogu.com.cn/paste/9g16g0h4)嘛，我是不会放的。[doge]  

感谢管理员大大指出问题。
###### ps：这是蒟蒻的第1篇题解

---

## 作者：DPair (赞：2)

其实这道题没必要用双指针，$3\times10^5$ 的数据范围让我们可以 $O(nlogn)$ 地yong $map$ 水过本题。

首先不难发现，无解当且仅当 $a$，$b$ 总和不同（不然完全可以考虑分成一段，总和相同）。

然后我们贪心的去想，发现当两个数列的某一位上的前缀和相同时，由于前缀和单调递增，把他们减掉对后面是没有影响的。

所以我们就尽可能的删去相同的前缀和即可，每遇到一段相同的前缀和就把答案加一。那么后面所有数的前缀和都要减去当前这个前缀和。

发现我们减去的两个前缀和大小相同，因此后面的所有前缀和的**大小关系**是不变的，因此可以不减（我们只考虑大小关系）。

那么问题就变成了：

给你两个序列，问这两个序列中有多少个数相同。

这个用 $map$ 维护一下就过去了。

核心代码如下：

```cpp
int n, m, ans;
LL a[300010], b[300010];
LL sa[300010], sb[300010];
map <LL, bool> h;
int main(){
    read(n);
    for (register int i = 1;i <= n;i ++) read(a[i]), sa[i] = sa[i - 1] + a[i];
    read(m);
    for (register int i = 1;i <= m;i ++) read(b[i]), sb[i] = sb[i - 1] + b[i];
    if(sa[n] ^ sb[m]) return printf("-1\n"), 0;//判无解
    for (register int i = 1;i <= n;i ++) h[sa[i]] = 1;
    for (register int i = 1;i <= m;i ++) ans += h[sb[i]];//判相同的数个数
    fprint(ans, 10);
}
```

---

## 作者：奇米 (赞：1)

## 题解- CF1036D

* **题目意思**

	就是给你两个数组$A,B$，你要把他们分成$k$段使得对应的段和相同，问最大分段数。
    
* $Sol$
	
    这道题目对于判断无解很容易，若$\sum A ≠\sum B$ 输出$-1$即可
    
    对于有解的情况怎么判断呢？我们$O(n)$遍历$B$中每一个点，再在$A$的$(p,n]$（$p$后面会提到）中二分早到第一个与$B_i$相同的位置$p$，如果不存在这个$p$我们继续累加$B_i$直至找到可以与其匹配的$p$，不停地更新$p$即可。
    
    这样总复杂度大约为$O(n\log n)$，可以过这道题。。
    
* $Code$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=3e5+5;

int n,m,a[N],b[N],SA[N],SB[N],ans;

signed main()
{
	scanf("%lld",&n);
	int tot=0;
	for ( int i=1;i<=n;i++ ) 
	{	
		scanf("%lld",&a[i]);
		SA[i]=SA[i-1]+a[i];
	}
	scanf("%lld",&m);
	for ( int i=1;i<=m;i++ ) 
	{
		scanf("%d",&b[i]);
		SB[i]=SB[i-1]+b[i];
	}
	if(SA[n]!=SB[m]) 
		return printf("-1\n"),0;
	int las=0,lp=0;
	for ( int i=1;i<=m;i++ )
	{
		las+=b[i];
		int pos=-1;
		int ll=lp,rr=n;
		while(ll<=rr)
		{
			int mid=(ll+rr)/2;
			if(SA[mid]-SA[lp]==las) 
			{
				pos=mid;
				break;
			}
			if(SA[mid]-SA[lp]<las) ll=mid+1;
			else rr=mid-1;
		}
		if(pos==-1) continue;
		las=0;
		lp=pos;
		ans++;
	}
	printf("%lld\n",ans);
	return 0;
}
	
		
```


---

## 作者：lightningZ (赞：1)

## 思路
由于把两个数列要分成多个和相同的小数列，那么很容易就可以推导出来一个结论“**只要两个数列的和相同，就一定有解，不然就一定无解。**”

所以我们只需要在判断是否有解后，用 $x$ 和 $y$ 这两个变量来记录 $a$ 数组和 $b$ 数组分别取到了什么位置，用 $sum1$ 和 $sum2$ 来记录两个小段的和，然后分三种情况讨论:

1. 如果 $sum1>sum2$ 那么就代表第二个小段需要增加数，所以 $y+1$。

2. 如果 $sum1<sum2$ 同理，代表第一个小段需要增加数，所以 $x+1$。

3. 如果 $sum1=sum2$ 那么就代表可以分成小段，就清空， $ans+1$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[300005],b[300005],ans;
long long q;
signed main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		q+=a[i];//记录第一个数组的总和。
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&b[i]);
		q-=b[i];//记录第二个数组的总和。
	}
	if(q!=0)//特判无解。
	{
		printf("-1");
		return 0;
	}
	int x=1,y=1,sum1=a[1],sum2=b[1];
	while(x<=n||y<=m)//因为不可能出现无解的情况，所以不用判断越界的情况，找到最后结束就可以。
	{
		if(sum1>sum2)//第一种情况
		{
			y++;
			sum2+=b[y];
		}
		else if(sum1<sum2)//第二种情况
		{
			x++;
			sum1+=a[x];
		}
		else//第三种情况
		{
			ans++;
			x++;
			y++;
			sum1=a[x];
			sum2=b[y];
		}
	}
	printf("%d",min(ans,min(n,m)));//因为份数不可能比某个数列的长度还长，所以要特判（好像可有可无）。
	return 0;
}
```

### 感谢观看

---

## 作者：Tenshi (赞：1)

## 分析
贪心地考虑这个问题，可以发现如果将所有数合并为一个时两个数列仍然不相等，那么一定无解，否则一定无解。

下面考虑最优方案：

我们记 `pta` 为指向 `a` 数列的指针，`ptb` 为指向 `b` 数列的指针， `sa[]` 为数列 `a[]` 的前缀和，`sb[]` 为数列 `b[]` 的前缀和

注意到如果两个数列 `a,b` 的前缀和 `sa[pta], sb[ptb]`相等，那么我们肯定能够将相应的部分合并，并且贡献 `res++` ，而且这样做是最优的。

很短的代码：
```cpp
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define pb(a) push_back(a)
#define set0(a) memset(a,0,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
#define INF 0x3f3f3f3f
typedef long long ll;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

const int N=3e5+5;
int n,m;
ll a[N],sa[N],b[N],sb[N];

int main(){
	cin>>n;
	rep(i,1,n) a[i]=read() ,sa[i]=sa[i-1]+a[i];
	cin>>m;
	rep(i,1,m) b[i]=read() ,sb[i]=sb[i-1]+b[i];
	
	if(sa[n]!=sb[m]){
		puts("-1");
		return 0;
	}
	
	int res=0;
	for(int pta=1,ptb=1;pta<=n,ptb<=m;){
		if(sa[pta]==sb[ptb]) res++,pta++,ptb++;
		else if(sa[pta]<sb[ptb]) pta++;
		else ptb++;
	}
	cout<<res<<endl;
	
    return 0;
}

```



---

## 作者：localhost (赞：1)

若$A,B$总和不相同，显然是-1

由于元素都大于0，可以使用类似双指针的方法

两个指针在$A,B$数组中移动，若找到$A,B$中和相同的两端，答案就+1

简短的代码：

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define ll long long
#define Fur(i,x,y) for(int i(x);i<=y;++i)
const int N=300011;
inline void in(int &x){x=0;char c;bool f=0;while((c=getchar_unlocked())<'0'||'9'<c)f^=(c=='-');while('0'<=c&&c<='9')x=x*10+c-48,c=getchar_unlocked();if(f)x=-x;}
int n,m,a[N],b[N];
int main(){
    in(n);
    Fur(i,1,n)in(a[i]);
    in(m);
    Fur(i,1,m)in(b[i]);
    int ans=0,j=1;
    ll s=0;
    Fur(i,1,n){
        s+=a[i];
        while(s>=b[j]&&j<=m)s-=b[j++];
        if(!s)++ans;
    }
    if(s!=0||j!=m+1)printf("-1\n");
    else printf("%d\n",ans);
}
```

---

## 作者：nekko (赞：1)

由于元素的值都是大于$0$的，因此维护双指针扫一遍，如果$s_p == s_q$那么就新分出一段

~~或者用$set$直接存一下所有的前缀和也行~~

``` cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct FastIO {
    static const int S = 1e7;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) exit(0);
        return buf[pos++];
    }
    inline int operator () () {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline ll operator ! () {
        int c = xchar(); ll x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline void wchar(int x) {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void operator () (ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar('\n');
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

const int N = 3e5 + 10; 
int n, m;
struct T { ll x[N], s[N]; } a, b;

void wa() { puts("-1"), exit(0); }

int main() {
	n = io();
	for(int i = 1 ; i <= n ; ++ i) a.x[i] = io(), a.s[i] = a.s[i - 1] + a.x[i];
	m = io();
	for(int i = 1 ; i <= m ; ++ i) b.x[i] = io(), b.s[i] = b.s[i - 1] + b.x[i];
	int p = 0, q = 0; ll sp = 0, sq = 0;
	if(a.s[n] != b.s[m]) {
		wa();
	} else {
		p = 1, q = 1, sp = a.x[1], sq = b.x[1];
		int ans = 0;
		while(1) {
			if(p > n || q > m) wa();
			while(sp < sq) {
				if(p + 1 > n) wa();
				sp += a.x[++ p];
			}
			while(sp > sq) {
				if(q + 1 > m) wa();
				sq += b.x[++ q];
			}
			if(sp == sq) {
				sp = a.x[++ p], sq = b.x[++ q];
				++ ans;
				if(p == n + 1 && q == m + 1) io(ans), exit(0);
			}
		}
	}
}
```

---

## 作者：fedoralxy (赞：0)

今天本人就换一种方式来写这篇题解。

其实这道题只需要搞清楚以下几个问题就可以了：

第一，什么情况下他有可行解，什么情况下没有？

第二，如何 $O(1)$ 求出任何区间的区间和？

第三，我们如何得到这个区间的左端点和右端点？

第四，根据第三题，暴力解法肯定会超时，怎么利用性质优化？

答案：

第一，在两个数组的和不同的时候没有可行解，反之，有可行解。

第二，前缀和。

第三，有尺取法枚举即可。

第四，要分三种情况：左端点有右端点的值相同，左端点大，右端点大。分别进行以下操作：计数器增加，左端点右移，右端点右移；右端点右移；左端点右移。

最后讲句废话，顺便立个旗：

再用尺取法的时候判断边界，左端点不超过第一个数组的长度且右端点不超过第二个数组的长度。

到这里大家如果理解以上内容就可以写代码了，还不理解的，可以下滑。

这里放一个伪代码。

```
头文件。
定义数组、变量。
主函数：
{
	输入第一个数组并求前缀和。
	输入第二个数组并求前缀和。
	判断两个原数组的和是否相等，不等输出 -1。
	定义计数器，左端点、右端点为 1。
	while 循环，边界：左端点不超过第一个数组的长度且右端点不超过第二个数组的长度。
   	{
		如果左端点的值等于右端点的值：
			计数器增加，左端点右移，右端点右移。
		左端点大：
			右端点右移。
		右端点大：
			左端点右移。
   	}
	输出计数器。
	( return 0 结束主函数)
}
```

结语，代码还是要自己写的。

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

给定 $A,B$ 两个数列，长度分别为 $n,m$，数列长度不超过 $3 \times 10^5$。数列中每个元素的值为 $[1,10^9]$ 的整数。

你需要将两个数列都分割成 $k$ 份，使得每一份的元素和对应相等

如果可行，输出最多将序列分割成多少份，如果不可行，输出 $-1$。

## 解法

首先判断输出 $-1$ 的情况：如果 $A,B$ 两个数列之和不相等，即当 $ \sum_{i=1}^n a_i\neq\sum_{i=1}^m b_i$ 时，直接输出 $-1$。

否则，一定可以得到答案，哪怕只能全部合并起来。

我们会很自然地想到贪心算法：用一个变量 $ans$ 记录答案，每次找到最小的 $i,j$ 使得 $\sum_{x=1}^i a_x =\sum_{x=1}^j b_x$,此时 $ans$ 加一，然后删掉 $[a_1,a_i]$ 以及 $[b_1,b_j]$,并对剩下的 $A,B$ 数组再次进行同样的操作。最后答案就是 $ans$.

我们可以很容易用反证法证明算法的正确性：假设我们可以把数列分割成 $res$ 份，且 $res>ans$，那么我们肯定是有 $p$ 次分割错了，这一段可以分割成 $p+res-ans$ 段，然而我们每次找的 $i,j$ 是最小的，当我们修改的时候只能找更大的 $i,j$ ，就只能分成更少的段，因此原分割方法正确。

## 代码

下面放无注释代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
long long a[300005],b[300005],suma,sumb;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],suma+=a[i];
    cin>>m;
    for(int i=1;i<=m;i++)cin>>b[i],sumb+=b[i];
    if(suma!=sumb){
	cout<<"-1"<<endl;
	return 0;
    }
    for(int i=1,j=1;i<=n&&j<=m;){
	if(a[i]==b[j])ans++,i++,j++;
	else if(a[i]>b[j])b[j+1]+=b[j],j++;
	else a[i+1]+=a[i],i++;
    }
    cout<<ans<<endl;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
给定两个长度分别为 $n$ 和 $m$ 的数列 $A,B$。你需要将两个数列都恰好分成 $k$ 份，使得两个数列中第 $i(i\in[1,k])$ 份的元素和对应相等。问是否可行，并在可行的情况下求出最大的 $k$。

**数据范围：$1\leqslant n,m\leqslant 3\times 10^5$，$1\leqslant A_i,B_i\leqslant 10^9$。**
## Solution
我们先将两个数列中的所有数的和加起来，记为 $S_A,S_B$。显然，如果 $S_A\neq S_B$，那么显然我们无法满足题目中的要求。

否则，我们采用双指针的方式，每次移动就记录下当前两个序列的前缀和，记为 $s_A,s_B$。

- 如果 $s_A<s_B$，那么我们将数列 $A$ 在当前位置下往前移一位。
- 如果 $s_A>s_B$，那么我们将数列 $B$ 在当前位置下往前移一位。
- 否则，我们将答案加 $1$（就相当于在这里把还未分进去的元素分成一份了），然后选择任意一个数列在当前位置下往前移一位。

输出答案即可。复杂度为 $\mathcal{O}(n)$，足以通过本题。 
## Code
```cpp
int a[300007], b[300007], visa[300007], visb[300007], ans;
ll sa, sb, suma, sumb;

int main() {
	int n = Rint; F(int, i, 1, n) suma += (a[i] = Rint);
	int m = Rint; F(int, i, 1, m) sumb += (b[i] = Rint);
	if(suma != sumb) return printf("-1"), 0;
	for(int i = 1, j = 1; i <= n && j <= m;) {
		sa += 1ll * a[i] * (1 - visa[i]), sb += 1ll * b[j] * (1 - visb[j]), visa[i] = visb[j] = 1; //为了避免重复加入前缀和，开 vis 数组记录当前元素是否已经加入前缀和。 
		if(sa == sb) ans++, sa = sb = 0, i++;
		else if(sa > sb) j++;
		else i++;
	}
    return write(ans), 0;
}

---

## 作者：wz20201136 (赞：0)

# 思路
看到数据范围，$O(n^{2})$ 的暴力显然不行。观察题目，数据范围满足 $a_i$ **大于等于一**，就可以用**双指针**，因为只要其中一个序列的当前这一段的和小于另一个序列，只能让当前序列加入一个元素。

而不符合条件的就很好判断了，只要两个序列总和不同，就不成立，反之一定成立。
# 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[300005],b[300005],n,m;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	cin>>m;
	for(int i=1;i<=m;i++) scanf("%lld",&b[i]);
	int ans=0,i=1,j=1,s1=a[1],s2=b[1];//两个指针，与当前一份的和
	while(i<=n&&j<=m)
	{
		if(s1==s2)
		{
			ans++;
			s1=a[++i],s2=b[++j];
			continue;
		}
		if(s1<s2) s1+=a[++i];
		else s2+=b[++j];
	}
	if(i!=n+1||j!=m+1) puts("-1");//只有当i=n且j=m且当时两份的和相等时i++,j++才成立
	else cout<<ans;
	return 0;
}
```

---


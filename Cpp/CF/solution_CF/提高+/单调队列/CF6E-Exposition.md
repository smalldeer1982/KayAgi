# Exposition

## 题目描述

There are several days left before the fiftieth birthday of a famous Berland's writer Berlbury. In this connection the local library decided to make an exposition of the works of this famous science-fiction writer. It was decided as well that it is necessary to include into the exposition only those books that were published during a particular time period. It is obvious that if the books differ much in size, the visitors will not like it. That was why the organizers came to the opinion, that the difference between the highest and the lowest books in the exposition should be not more than $ k $ millimeters.

The library has $ n $ volumes of books by Berlbury, arranged in chronological order of their appearance. The height of each book in millimeters is know, it is $ h_{i} $ . As Berlbury is highly respected in the city, the organizers want to include into the exposition as many books as possible, and to find out what periods of his creative work they will manage to cover. You are asked to help the organizers cope with this hard task.

## 样例 #1

### 输入

```
3 3
14 12 10
```

### 输出

```
2 2
1 2
2 3
```

## 样例 #2

### 输入

```
2 0
10 10
```

### 输出

```
2 1
1 2
```

## 样例 #3

### 输入

```
4 5
8 19 10 13
```

### 输出

```
2 1
3 4
```

# 题解

## 作者：Nepenthe (赞：6)

首先区分子串与子序列的定义:

- 某个数列的子序列是从最初序列通过去除某些元素但不破坏余下元素的相对位置（在前或在后）而形成的新数列
- 如果子序列在原序列中是连续的,就称之为子串

即子串是连续的子序列不要求连续

本题思路:
既然要求子串中的最大值和最小值,我们可以想到用RMQ.

我们枚举子串的左端点l,然后二分右端点r,如果[l,r]中极差不大于k就继续向右二分.

**单调性证明** 右端点越向右,加入子串的元素越多,期望的极差也就越大

**Code**
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define siz 100010
#define maxn(a,b) (a>b?a:b)
#define minn(a,b) (a<b?a:b)
using namespace std;
int n,k,l,r,mid,nans,cnt;
int a[siz],maxT[siz][20],minT[siz][20],ansl[siz][2];
inline int gmax(int l,int r) {
    int j=log2(r-l+1);
    return maxn(maxT[l][j],maxT[r-(1<<j)+1][j]);
}
inline int gmin(int l,int r) {
    int j=log2(r-l+1);
    return minn(minT[l][j],minT[r-(1<<j)+1][j]);
}
int binary_(int i) {
    l=i,r=n;
    int ans=i;
    while(l<=r) {
        mid=(l+r)>>1;
        if(gmax(i,mid)-gmin(i,mid)<=k) ans=mid,l=mid+1;
        else r=mid-1;
    }
    return ans;
}
int main ( ) {
    
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]),maxT[i][0]=minT[i][0]=a[i];
    for(int j=1;(1<<j)<=n;++j)
     for(int i=1;(i+(1<<j)-1)<=n;++i) {
          maxT[i][j]=maxn(maxT[i][j-1],maxT[i+(1<<(j-1))][j-1]);
          minT[i][j]=minn(minT[i][j-1],minT[i+(1<<(j-1))][j-1]);
     }
    for(int i=1;i<=n;++i) {
        int pos=binary_(i); //printf("now nans=%d cnt=%d i=%d pos=%d\n",nans,cnt,i,pos);
        if(pos-i+1>nans) nans=pos-i+1,ansl[cnt=1][0]=i,ansl[cnt][1]=pos;
        else if(pos-i+1==nans) ansl[++cnt][0]=i,ansl[cnt][1]=pos;
    }    
    printf("%d %d\n",nans,cnt);
    for(int i=1;i<=cnt;++i) printf("%d %d\n",ansl[i][0],ansl[i][1]); 
    return 0;
}
```


---

## 作者：小闸蟹 (赞：6)

```cpp
// 楼上大佬的题解我有点不太理解
// 我发一个跟我一样弱的都能看懂的做法
// 希望能对大家有帮助
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <array>

// 这题数据量还是比较大的，上快读加速明显
int Read()
{
    int n = 0, k = 1;
    char ch = getchar();
    while ((ch > '9' || ch < '0') && ch != '-')
        ch = getchar();

    if (ch == '-')
    {
        k = -1;
        ch = getchar();
    }

    while (ch <= '9' && ch >= '0')
    {
        n = n * 10 + ch - '0';
        ch = getchar();
    }

    return n * k;
}

int main()
{
    static std::array<int, 100000> Book{ 0 };
    int n, k;
    n = Read();
    k = Read();

    // v：存放答案的左端点和右端点
    // s：可行序列
    // l：左端点
    // r：右端点
    // Ans：最长的序列长度
    std::vector<std::pair<int, int>> v;
    std::multiset<int> s;
    int l = 0, Ans = 0;
    for (int r = 0; r < n; ++r)
    {
        Book[r] = Read();
        s.insert(Book[r]);  // 利用std::multiset有序且可重复的特性
        while (*s.crbegin() - *s.cbegin() > k)
        {
            // 如果最大的减去最小的超范围了，那就不停地删掉左端点
            // 直到满足 <= k 为止
            // 这样做稍微有一点点尺取法的味道
            s.erase(s.find(Book[l]));
            ++l;
        }

        if (r - l + 1 > Ans)    // 如果得到了一个更长的序列，那就更新答案
        {
            v.clear();
            Ans = r - l + 1;
            v.push_back({ l + 1, r + 1 });  // 我从0开始算的，所以要加一
        }
        else if (r - l + 1 == Ans)  // 同样长的也要
        {
            v.push_back({ l + 1, r + 1 });
        }
    }

    std::cout << Ans << ' ' << v.size() << std::endl;
    for (const auto &r : v)
    {
        std::cout << r.first << ' ' << r.second << std::endl;
    }

    return 0;
}
```

---

## 作者：kczno1 (赞：5)

翻译说是子序列,于是我就当子序列打了..  
完了之后过不了样例3..  
又看了遍英文题面,才知道是子串..  
这件事告诉我们读完题要先看看样例,确保没理解错.

如果是子序列的话,就是枚举值域区间然后$rmq$求出最左最右.   
具体的话就是把元素按值排序,  然后枚举左端点$l$,  
维护$r=max(i),v[i]<=v[l]+k$  
($v[i]$表示排完序第$i$个元素的值)  
则$r-l+1$就是子序列长度,对$[l,r]rmq$一下就得到了子序列左端点右端点.  
$rmq$可以用单调队列,时间除排序外$O(n)$

如果是子串的话,就是枚举左端点$l$,  
维护$r=max(i),max(a[l..i])-min(a[l..i])>k$  
单调队列即可,时间$O(n)$

```cpp
//by kcz 1552920354@qq.com
//if you find any bug in my code
//please tell me
#include<bits/stdc++.h>
using namespace std;

template <typename T> void chmin(T&x,const T &y)
{
	if(x>y)x=y;
}
template <typename T> void chmax(T &x,const T &y)
{
	if(x<y)x=y;
}
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned short us;
typedef unsigned int ui;
typedef pair<int,int> pii;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
#define pb push_back
#define mp make_pair
#define gc (c=getchar())
int read()
{
	char c;
	while(gc<'-');
	if(c=='-')
	{
		int x=gc-'0';
		while(gc>='0')x=x*10+c-'0';
		return -x;
	}
	int x=c-'0';
	while(gc>='0')x=x*10+c-'0';
	return x;
}
#undef gc
const int N=1e5+5;
struct que
{
pii q[N];int h,t;
void push(const pii &x)
{
	while(h<=t&&x.second>q[t].second)--t;
	q[++t]=x;
}
int get(int l)
{
	while(q[h].first<l)++h;
	return q[h].second;
}
};
que zheng,fu;
int a[N];

int main()
{
	freopen("1.in","r",stdin);//freopen("1.out","w",stdout);
	int n=read(),k=read();
	rep(i,1,n)a[i]=read();
	a[n+1]=1e9;

	static int q[N];
	int ans=-1,top=0;
	int j=0;
	rep(i,1,n)
	{
		while(j<i||zheng.get(i)+fu.get(i)<=k)
		{
			++j;
			zheng.push(mp(j,a[j]));
			fu.push(mp(j,-a[j]));
		}
		if(j-i>ans){ans=j-i;q[top=1]=i;}
		else 
		if(j-i==ans)q[++top]=i;
	}
	printf("%d %d\n",ans,top);
	rep(i,1,top)printf("%d %d\n",q[i],q[i]+ans-1);
}


```

---

## 作者：caidzh (赞：3)

其实我是在做数学期望的时候搜到这个题的

然后我看完题面后发现这不是一道数学期望，仔细想了$10s$后意识到这是一道$STL$练习题，于是就用$multiset$和$queue$水过了这题

首先我们说明一个引理：如果区间$[l,r]$满足条件，那么若区间$[l_1,r_1]\in[l,r]$，那么$[l_1,r_1]$也满足条件

这是显而易见的，这里不再证明

所以这就启示我们可以使用双指针从头到尾扫一遍得到结果

怎么去维护当前这个区间是否合法？这可以通过维护区间最大和区间最小来实现

怎么维护动态插入删除的区间最大和区间最小？考虑使用平衡树来维护，实际上写一个$multiset$即可，那么接下来就是双指针的板子题，注意一些边界细节就可以了

最后答案的输出可以使用一个队列来保存答案，如果当前区间长度$=ans$则插入队列，如果$>ans$则清空队列再插入队列，由于每个节点最多入队一次，出队一次，所以并不会影响到整体复杂度

最终复杂度$O(nlogn)$
```
#include<bits/stdc++.h>
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
const int maxn=100010;
int n,k,a[maxn],Max,ans;
multiset<int>s;queue<int>que;
int main()
{
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();if(n==1){printf("%d %d\n%d %d\n",1,1,1,1);return 0;}
	int l=1;s.insert(a[1]);
	for(int i=2;i<=n;i++){
		s.insert(a[i]);while(i-l+1>=2&&*s.rbegin()-*s.begin()>k&&l<i)s.erase(s.find(a[l])),l++;
		if(i-l+1==ans){que.push(i);}
		if(i-l+1>ans){ans=i-l+1;while(!que.empty())que.pop();que.push(i);}
	}if(ans!=1)printf("%d %d\n",ans,que.size());else printf("%d %d\n%d %d\n",ans,n,1,1);
	while(!que.empty())printf("%d %d\n",que.front()-ans+1,que.front()),que.pop();
	return 0;
}
```


---

## 作者：zrzring (赞：3)

[更好的阅读体验](http://zrzring.cn/index.php/archives/262)

> 求最大的极差不超过k的子串

当时最初想到的是枚举右端点，用单调队列存一个单增和一个单减，每次取队头做差，不行就弹队头

实际上这个做法会被这个数据hack

```txt
4
1 6 4 7
```

最后一个位置时，单增队列为`4 7`，单减队列只有一个`7`，就找不到`6 4 7`这一个子串

上述方法从性质上就是错误的，不能继续修改

一种正确的做法，枚举左端点，更新右端点，因为其满足单调性，随着左端点的推进右端点肯定是只会往右移的，于是我们可以做到线性复杂度

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

void file() {
    freopen("std.in", "r", stdin);
    freopen("wa.out", "w", stdout);
}

const int N = 1e6 + 10, M = 2e6 + 10, inf = 1e9;

inline int read() {
    bool sym = 0; int res = 0; char ch = getchar();
    while (!isdigit(ch)) sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}

int n, m, ans, res[N], a[N], h1, t1, h2, t2, q1[N], q2[N];

void ins(int x) {
    while (h1 <= t1 && a[x] >= a[q1[t1]]) t1--;
    q1[++t1] = x;
    while (h2 <= t2 && a[x] <= a[q2[t2]]) t2--;
    q2[++t2] = x;
}

int main() {
    n = read(); m = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    int l = 1, r = 0;
    for (l = 1; l <= n; l++) {
        if (r < l) ins(++r);
        if (h1 <= t1 && q1[h1] < l) h1++;
        if (h2 <= t2 && q2[h2] < l) h2++;
        while (r < n && max(a[r + 1], a[q1[h1]]) - min(a[r + 1], a[q2[h2]]) <= m) ins(++r);
        res[l] = r - l + 1; ans = max(ans, res[l]);
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) if (res[i] == ans) cnt++;
    printf("%d %d\n", ans, cnt);
    for (int i = 1; i <= n; i++) if (res[i] == ans) printf("%d %d\n", i, i + res[i] - 1);
    return 0;
}
```

---

## 作者：Elegy_of_Green_Kite (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/CF6E)

题意有点误导人，应该是子串而不是子序列，但研究一下样例应该能明白。

在做这道题目前建议先去试着做做[这道模板题](https://www.luogu.com.cn/problem/P3865)，我们就会发现这道题其实是 ST 表模板的升级版。

ST 表的作用是可以在 $O(n log n)$ 的预处理下 $O(1)$ 查询出一段区间内的最大值或最小值，使用的是倍增的思想。

主要代码就像这样（$f_{i,j}$ 表示序列 $A$ 中下标在子区间 $i,i+2^{j}-1$ 里的数的最大值）：
```cpp
void ST_prework() 
{
	for(int i=1;i<=n;i++)  f[i][0]=a[i];
	int t=(int)(log(n)/log(2)+1);
	for(int j=1;j<t;j++)
		for(int i=1;i<=n-(1<<j)+1;i++)
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}
int ST_query(int l,int r)
{
	int k=(int)(log(r-l+1)/log(2));
	return max(f[l][k],f[r-(1<<k)+1][k]);
}
```
所以，最大值减最小值的问题就解决了，现在只需要找出 $l$,$r$就可以 $O(1)$ 判断是否合法了。

考虑到数据范围是 $n \le 10^{5}$，$n^{2}$ 枚举左右端点肯定不行。于是我们就可以想到 $O(n)$ 寻找区间的**单调队列**。

单调性体现在存在一个合法区间 $[ l,r ]$，那么对于所有 $l \le x \le r$，区间 $[x,r]$ 必然是合法的。

代码如下：
```cpp
#include<iostream>
#include<stdio.h>
#include<math.h>
using namespace std;
const int N=1e5+5;
int n,k,le=1,ri,ans,cnt,a[N],s[N];
int f1[N][25],f2[N][25];
void ST_prework() 
{
	for(int i=1;i<=n;i++)  f1[i][0]=f2[i][0]=a[i];
	int t=(int)(log(n)/log(2)+1);
	for(int j=1;j<t;j++)
		for(int i=1;i<=n-(1<<j)+1;i++)
		{
			f1[i][j]=max(f1[i][j-1],f1[i+(1<<(j-1))][j-1]);
			f2[i][j]=min(f2[i][j-1],f2[i+(1<<(j-1))][j-1]);
		}
return;
}
int query(int l,int r)
{
	int k=(int)(log(r-l+1)/log(2));
	int rec=max(f1[l][k],f1[r-(1<<k)+1][k])-min(f2[l][k],f2[r-(1<<k)+1][k]);
return rec;//返回的值极为区间l,r之间的最大最小值之差
}
int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)  scanf("%d",&a[i]);
	ST_prework();
	for(int i=1;i<=n;i++)
	{
		//确定右端点是 i
		while(le<=ri && query(s[le],i)>k)  le++;
		//删除不合题意的左端点
		s[++ri]=i;
		if(ans==i-s[le]+1)  cnt++;
		else if(ans<i-s[le]+1)  ans=i-s[le]+1,cnt=1;
		//如果当前区间长度已经是能找到的最大值了，那么方案数加一
		//如果当前区间长度比已知的最大值还要大，那么计数器重新计数
	}
	le=1,ri=0;
	printf("%d %d\n",ans,cnt);
	//现在已经确定了最大长度，相当于直接再搜索一遍
	for(int i=1;i<=n;i++)
	{
		while(le<=ri && query(s[le],i)>k)  le++;
		s[++ri]=i;
		if(ans==i-s[le]+1)  printf("%d %d\n",s[le],i);
	}
return 0;
}
```


---

## 作者：伊凡 (赞：1)

这道题第一眼看上去很容易想到一种暴力的思路，就是从大到小枚举子串的长度l，一旦找到合法（满足条件）的子串就搜一遍所有长度为l的子串然后输出所有合法子串的位置（起始结束下标）。

但是这样显然太暴力了，肯定会超时，~~暴力是解决不了问题的，但是好像可以解决我~~于是我们想到可以用ST表预处理所有区间的最大、最小值，这样判断合法就可以做到O（1），然后用二分答案去找最大的合法子串长度。

TIPS：好像很多题解都提了一下翻译有问题，题目要求的应该是子串而不是子序列

下面附上代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int n,k,stmax[100005][18],stmin[100005][18],ans[100005][2],maxx,m=0;//stmax处理最大值，stmin处理最小值，ans保留答案，maxx存最大长度，m统计答案数
bool check(int l,int r)
{
	int i=log(double(r-l+1))/log(double(2));//寻找一个特殊的值i，这个值可以将区间分为长度相等且长度为2^n的两部分（两部分可能重合）
	if(max(stmax[l][i],stmax[r-(1<<i)+1][i])-min(stmin[l][i],stmin[r-(1<<i)+1][i])<=k)return true;
	else return false;
}
bool check1(int t)
{
	int i;//这里是枚举所有长度为t的子串，只要有一个合法就行
	for(i=1;i+t-1<=n;i++)
	if(check(i,i+t-1))return true;
	return false;
}
int main()
{
	scanf("%d%d",&n,&k);
	int i,j,mid;
   //初始化st表
	for(i=1;i<=n;i++)
	{
		scanf("%d",&stmin[i][0]);
		stmax[i][0]=stmin[i][0];
	}
   //预处理ST表
	for(j=1;j<=n;j++)
	if(1<<j>n)break;
	else
	for(i=1;i+(1<<(j-1))<=n;i++)
	stmin[i][j]=min(stmin[i][j-1],stmin[i+(1<<(j-1))][j-1]);
	for(j=1;j<=n;j++)
	if(1<<j>n)break;
	else
	for(i=1;i+(1<<(j-1))<=n;i++)
	stmax[i][j]=max(stmax[i][j-1],stmax[i+(1<<(j-1))][j-1]);
   //二分答案
	i=1;j=n;
	while(i<j)
	{
		mid=(i+j)/2+1;
		if(check1(mid))i=mid;
		else j=mid-1;
	}
	maxx=i;//找到最大长度
	for(i=1;i+maxx-1<=n;i++)//找所有合法子串
	if(check(i,i+maxx-1))
	{
		m++;ans[m][0]=i;ans[m][1]=i+maxx-1;
	}
	printf("%d %d\n",maxx,m);
	for(i=1;i<=m;i++)
	printf("%d %d\n",ans[i][0],ans[i][1]);
	return 0;
} 
```
~~那啥，是C++的代码啊！我防止大家看不出来所以加上了~~


---

## 作者：oimaster (赞：1)

在我的[博客](https://oi-master.github.io/post/atcoder-abc-160-e-ti-jie/)阅读体验更好哦！

## 题面
由于这道题翻译得很好，所以我就先不翻译了。翻译请点击 <https://www.luogu.com.cn/problem/CF6E>。
## 思路
这一道题， $N\leq 10^5$ ，我们知道，这种数据一定是 $O(Nlog_2^N)$ 的时间复杂度。但是，我们用什么方法呢？排序？二分答案？二叉堆？这样空想是一定不行的，我们要有针对性的想。
我们觉得 $log$ 不太好想，也许只是一个小算法的时间复杂度。我们可以像是“往宏观”走，去想想这道题有没有 $O(N)$ 的算法。
我们发现，想要是 $O(N)$ 的话，暂时就是“双指针”算法。这个算法是可以的，我来讲一下什么情况下要干嘛。
+ 当 $A_L, A_L+1, ... , A_R-1, A_R$ 不满足条件的时候，我们可以把 $L+1$ ，这样子，就有可能合法。至于到底合不合法，可以稍后判断。
+ 当 $A_L, A_L+1, ... , A_R-1, A_R$ 合法的时候，也就是满足这个条件后，我们可以先比较一下长度。如果长度比原来存的序列长度长，那么就更新一下长度，把答案数量再改成 $1$ ，接下来，我们再把 $R+1$ 。如果还是不了解我的意思，可以在评论区留言。
不过，我们如何找到“最大值”与“最小值”呢？大家可以搞个单调队列，不过我在这里推荐 multiset 。不懂的自己查 [百度](http://baidu.physton.com/?q=C%2B%2B%20%E4%B8%AD%E7%9A%84%20multiset) 。
## 代码
然后，就是可爱的代码啦！
```cpp
/*
 * Author: OI_Master
 * Time: 2020-03-24 10:01:05
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,k;
	cin>>n>>k;
	multiset<int>m;
	int j=1;
	int a[n+1];
	int maxs=0;
	vector<pair<int,int> >ans;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		m.insert(a[i]);
		while(*(m.rbegin())-*(m.begin())>k){
			m.erase(m.find(a[j]));
			++j;
		}
		if(i-j+1>maxs){
			ans.clear();
			maxs=i-j+1;
			ans.push_back(make_pair(j,i));
		}
		else if(i-j+1==maxs)
			ans.push_back(make_pair(j,i));
	}
	cout<<maxs<<' '<<ans.size()<<endl;
	for(int i=0;i<ans.size();++i)
		cout<<ans[i].first<<' '<<ans[i].second<<endl;
	return 0;
}
```

---

## 作者：bzdht (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF6E)

这道题第一眼看上去很容易想到一种暴力的思路，就是从大到小枚举子串的长度**l**，一旦找到合法（满足条件）的子串就搜一遍所有长度为**l**的子串然后输出所有合法子串的位置（起始结束下标）。

但是这样显然太暴力了，肯定会超时，于是我们想到可以用ST表预处理所有区间的最大、最小值，这样判断合法就可以做到O（1），然后用二分答案去找最大的合法子串长度。~~然后就过了？~~

TIPS：好像很多题解都提了一下翻译有问题，题目要求的应该是子串而不是子序列

下面附上代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int n,k,stmax[100005][18],stmin[100005][18],ans[100005][2],maxx,m=0;//stmax处理最大值，stmin处理最小值，ans保留答案，maxx存最大长度，m统计答案数
bool check(int l,int r)
{
	int i=log(double(r-l+1))/log(double(2));//寻找一个特殊的值i，这个值可以将区间分为长度相等且长度为2^n的两部分（两部分可能重合）
	if(max(stmax[l][i],stmax[r-(1<<i)+1][i])-min(stmin[l][i],stmin[r-(1<<i)+1][i])<=k)return true;
	else return false;
}
bool check1(int t)
{
	int i;//这里是枚举所有长度为t的子串，只要有一个合法就行
	for(i=1;i+t-1<=n;i++)
	if(check(i,i+t-1))return true;
	return false;
}
int main()
{
	scanf("%d%d",&n,&k);
	int i,j,mid;
   //初始化st表
	for(i=1;i<=n;i++)
	{
		scanf("%d",&stmin[i][0]);
		stmax[i][0]=stmin[i][0];
	}
   //预处理ST表
	for(j=1;j<=n;j++)
	if(1<<j>n)break;
	else
	for(i=1;i+(1<<(j-1))<=n;i++)
	stmin[i][j]=min(stmin[i][j-1],stmin[i+(1<<(j-1))][j-1]);
	for(j=1;j<=n;j++)
	if(1<<j>n)break;
	else
	for(i=1;i+(1<<(j-1))<=n;i++)
	stmax[i][j]=max(stmax[i][j-1],stmax[i+(1<<(j-1))][j-1]);
   //二分答案
	i=1;j=n;
	while(i<j)
	{
		mid=(i+j)/2+1;
		if(check1(mid))i=mid;
		else j=mid-1;
	}
	maxx=i;//找到最大长度
	for(i=1;i+maxx-1<=n;i++)//找所有合法子串
	if(check(i,i+maxx-1))
	{
		m++;ans[m][0]=i;ans[m][1]=i+maxx-1;
	}
	printf("%d %d\n",maxx,m);
	for(i=1;i<=m;i++)
	printf("%d %d\n",ans[i][0],ans[i][1]);
	return 0;
} 
```


---


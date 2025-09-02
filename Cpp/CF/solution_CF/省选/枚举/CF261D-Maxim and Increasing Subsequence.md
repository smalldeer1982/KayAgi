# Maxim and Increasing Subsequence

## 题目描述

Maxim loves sequences, especially those that strictly increase. He is wondering, what is the length of the longest increasing subsequence of the given sequence $ a $ ?

Sequence $ a $ is given as follows:

- the length of the sequence equals $ n×t $ ;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF261D/62550b81a494c59fe3493af08329ebf8f9d7bb9b.png) $ (1<=i<=n×t) $ , where operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF261D/946bcc44e053027f1f6b5dfc3143583e661988f5.png) means taking the remainder after dividing number $ x $ by number $ y $ .

Sequence $ s_{1},s_{2},...,s_{r} $ of length $ r $ is a subsequence of sequence $ a_{1},a_{2},...,a_{n} $ , if there is such increasing sequence of indexes $ i_{1},i_{2},...,i_{r} $ $ (1<=i_{1}&lt;i_{2}&lt;...\ &lt;i_{r}<=n) $ , that $ a_{ij}=s_{j} $ . In other words, the subsequence can be obtained from the sequence by crossing out some elements.

Sequence $ s_{1},s_{2},...,s_{r} $ is increasing, if the following inequality holds: $ s_{1}&lt;s_{2}&lt;...&lt;s_{r} $ .

Maxim have $ k $ variants of the sequence $ a $ . Help Maxim to determine for each sequence the length of the longest increasing subsequence.

## 样例 #1

### 输入

```
3 3 5 2
3 2 1
1 2 3
2 3 1
```

### 输出

```
2
3
3
```

# 题解

## 作者：liangzihao (赞：13)

大意： 
给你一个数列b，和一个数t，构造出一个数列a为t个数列b组成的数列。 
**比如：b={3,2,1},t=2;a={3,2,1,3,2,1}。** 

有k组数据，数列中元素大小为**[0,maxb] **
求数列a的最长上升子序列(**严格单调**)。

分析： 
观察样例与数据可以知道，**当t>=sum时，答案就是sum，其中sum为序列中不同数字的个数**，因为是严格单调的。

那么，我们只考虑t＜sum的情况。我们发现n$*$maxb≤2$*$10^7的，我们可以发现，这种情况下序列长度就是≤2*10^7，因为sum一定小于maxb。

然后dp，找最大值用树状数组，反正我用线段树TLE了。复杂度还是很恐怖的。在代码里面玄学优化就差不多了。反正能过就是了。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>

const int maxn=1e5+7;

using namespace std;

int k,n,maxb,t,sum,ans,i,j,c;
int a[maxn],b[maxn],tree[maxn],f[maxn];

int lowbit(int x)
{
    return x&(-x);
}

void updata(int x,int c)
{
    while (x<=maxb)
    {
        tree[x]=max(tree[x],c);
        x+=lowbit(x);
    }
}

int get(int x)
{
    int c=0;
    while (x>0)
    {
    	c=max(c,tree[x]);
    	x-=lowbit(x);
    }
    return c;
}

int main()
{
    scanf("%d%d%d%d",&k,&n,&maxb,&t);
    while (k--)
    {
        sum=0;
        for (i=1;i<=n;i++) 
        {
            scanf("%d",&a[i]);
            if (b[a[i]]!=k+1) sum++;
            b[a[i]]=k+1;
        }
        if (t>=sum)
        {
            printf("%d\n",sum);
            continue;
        }
        ans=0;
        for (i=1;i<=maxn;i++)//清空数组 
        {
            tree[i]=0;	
            f[i]=0;
        }	    
        for (i=1;i<=t;i++)枚举周期
           for (j=1;j<=n;j++)//枚举位置
           {
                c=get(a[j]-1)+1;
                if (c>f[j])//判断能不能修改树状数组，其中f[j]记录上一周期的答案
                {
                	f[j]=c;
                	ans=max(ans,c);
                	updata(a[j],c);
                }
                if (ans>=sum) break;//答案不可能超过sum，可以直接退掉
           }
        printf("%d\n",ans);
    }
}
```

---

## 作者：yyandy (赞：7)

题解里目前的解法似乎都是树状数组，   
时间复杂度是 $O(k\times n\times maxb \times \log_2 maxb)$。   
然而这样在时间上非常的紧，而且这是 CF 的远古场，在当时的机子上应该是跑不过去的，需要更优秀的解法。       
树状数组的解法本质还是将循环拆开再做最长上升子序列，这就没有很好地利用循环的一些性质。   
首先我们考虑最暴力的解法，对每一段进行暴力求最长上升子序列再进行转移。      
这应该非常基础好写，核心代码如下：     
```cpp
for(int i=1;i<=t;++i){
	for(int j=1;j<=n;++j)
		for(int k=1;k<=n;++k)
			if(a[j]>a[k])
				f[j]=max(f[j],F[k]+1);
	for(int j=1;j<=n;++j)
		F[j]=f[j],f[j]=1;
	for(int j=1;j<=n;++j)
		for(int k=1;k<j;++k)
			if(a[j]>a[k])
				F[j]=max(F[j],F[k]+1);
}
```
其中上面一个是处理从前一个循环到后一个循环之间的转移，而下面一个是处理同一个循环内的最长上升子序列。       
时间复杂度为 $O(k\times t\times n^2)$，非常地不优。      
观察性质，如果能从位置 $x$ 转移到位置 $y$，那么一定满足 $a_x<a_y$。        
由此可知，最长上升子序列的长度上限就是原数组 $a$ 中不同的 $a_i$ 的数量。        
于是就可以优化至 $O(k\times t\times n\times maxb)$。    
进一步优化过程中，发现原数组不太好处理。    
而前面那个性质就启示我们将 $a$ 排序，并记录每个位置的数下在原数组中的位置 $id$。     
这样就只能从前向后转移了。     
当然，要注意如果有相同的 $a_i$，它们之间是不能进行转移的。    
我们的转移可以进行相应更改，      
设 $f_{i,j}$ 表示当长度为 $j$ 的上升子序列的结尾在位置 $i$ 时，所需跨越的最少循环数（此处的位置 $i$ 指的是排好序后的位置）。   
跨越的循环数量可能有些难理解，我们举个栗子：         
[![](https://cdn.luogu.com.cn/upload/image_hosting/3qzczq7p.png)](咕咕咕)    
那什么时候需要跨越循环呢？      
如果从 $y$ 转移到 $x$，那么显然是 $id_x>id_y$ 的时候啦。      
如果跨越循环数小于 $t$，那么就是可行的方案。      
如果我们对于每一个位置暴力从前面转移的话，仍然是  $O(k\times t\times n\times maxb)$ 的。     
然而我们可以用两个数组记录一下来降低复杂度，    
$g_j$ 表示目前长度为 $j$ 的上升子序列所需要跨越的最少循环数量。      
$p_j$ 表示在满足跨越的循环数量最少的前提下，最小的 $id$ 值。        
这样就可以直接求出 $f_{i,j}$ 了，具体地：     

$$
\begin{array}{lll}
f_{i,j}=
\begin{cases}
g_j & id_i > p_j\\
g_j+1 & id_i \le p_j\\
\end{cases}
\end{array}
$$    
而每次我们求出 $f_{i,j}$ 后，都要对 $g$ 数组进行更改。      
为什么这样转移是对的呢？     
这就与[这题](https://www.luogu.com.cn/problem/P3572)做单调队列的思想有些相似了。      
$p_j$ 的大小最多只对 $f_{i,j}$ 的大小产生 $1$ 的影响，所以我们先保证跨越区间数量最小是对的，时间复杂度也降至 $O(k\times n\times maxb)$。       
最终答案即为满足 $g_j<k$ 的最大 $j$。       
**注意处理数值相同而不能转移的情况！**     
## CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int Mx,M,n,g[120000],f[120000],T,k,p[120000],z[120000];
struct D{
	int s,id;
}a[120000];
bool cmp(D x,D y){
	if(x.s!=y.s)
		return x.s<y.s;
	else 
		return x.id<y.id;
}
int E;
int main(){
	cin>>T>>n>>E>>k;
	while(T--){
		Mx=M=0;
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i].s),a[i].id=i,Mx=max(Mx,a[i].s);
		sort(a+1,a+n+1,cmp);// 从小到大排序方便后续 DP
		memset(g,63,sizeof(g));
		memset(p,0,sizeof(p));
		g[0]=0;a[0].s=-1;a[n+1].s=-1;
		for(int i=1;i<=n;++i){
			if(a[i].s!=a[i-1].s){
				for(int j=1;j<=Mx;++j){
					if(a[i].id>p[j-1])
						f[j]=g[j-1],z[j]=a[i].id;
					else 
						f[j]=g[j-1]+1,z[j]=a[i].id;
				}	
			}
			else{ // 特判数值相同不能转移相同情况
				for(int j=1;j<=Mx;++j){
					if(a[i].id>p[j-1]){
						if(f[j]>g[j-1]||(f[j]==g[j-1]&&a[i].id<z[j]))
							z[j]=a[i].id,f[j]=g[j-1];
					}else{
						if(f[j]>g[j-1]+1||(f[j]==g[j-1]&&a[i].id<z[j]))
							z[j]=a[i].id,f[j]=g[j-1]+1;
					}
				}
			}
			if(a[i].s!=a[i+1].s){// 更改 g 数组
				for(int j=1;j<=Mx;++j){
					if(f[j]<g[j]||(g[j]==f[j]&&z[j]<p[j]))
						g[j]=f[j],p[j]=z[j];
				}
			}
		}
		for(int i=1;i<=Mx;++i)if(g[i]<k)M=i;
		printf("%d\n",M);
	}
}
```  
跑得很快，随便进行一些优化就可轻松跑进 1s。     
代码对 $f$ 数组进行了滚动，由于是在模拟赛中打的，变量含义可能与题目讲解不同，仅供参考。       

---

## 作者：fuqingchen (赞：4)

# 原题链接

[CF261D Maxim and Increasing Subsequence](https://www.luogu.com.cn/problem/CF261D)

# 解题思路

首先一个显然的结论：若 $m \le t$（$m$ 是离散化后的长度）则输出 $m$。可以在第 $i$ 个序列中选序列中第 $i$ 大的数做到。

若 $m < t$，根据最长上升子序列的 DP 转移方程，我们可以用树状数组维护前缀最大值，由于空间限制，建议滚动一下防止空间溢出。

# 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace get {
	inline char nc() {
		static char buf[1000010], *p1 = buf, *p2 = buf;
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000010, stdin), p1 == p2) ? EOF : *p1++;
	}
}
using namespace std;
//#define getchar get::nc
namespace read {
	inline void rd(char *s){
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
int n, tr[100010], k, ma, t, b[100010], cnt;
bool a[100010];
int f[20000010], res;
inline int lowbit(int x) {
	return x & -x;
}
inline void add(int x, int k) {
	while (x <= ma) {
		tr[x] = max(tr[x], k);
		x += lowbit(x);
	}
}
inline int query(int x) {
	int res = 0;
	while (x > 0) {
		res = max(tr[x], res);
		x -= lowbit(x);
	}
	return res;
}
signed main() {
	rd(k), rd(n), rd(ma), rd(t);
	while (k--) {
		memset(b, 0, sizeof(b));
		memset(a, 0, sizeof(a));
		memset(tr, 0, sizeof(tr));
		memset(f, 0, sizeof(f));
		cnt = res = 0;
		for (int i = 1; i <= n; ++i) {
			rd(b[i]);
			if (!a[b[i]]) cnt += (a[b[i]] = 1);
		}
		if (cnt <= t) {
			cout << cnt << '\n';
			continue;
		}
		for (int i = 1; i <= t; ++i)
			for (int j = 1; j <= n; ++j) {
				int now = query(b[j] - 1) + 1;
				if (now > f[j]) {
					f[j] = now;
					add(b[j], now);
					res = max(res, now);
				}
			}
		cout << res << '\n';
	}
	return 0;
}
```

---

## 作者：Jayun (赞：4)

# 链接：

[洛谷](https://www.luogu.com.cn/problem/CF261D)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/14316871.html)

# 题目大意：

将长度为 $n$ 的 $b$ 数组复制 $t$，首尾相连后得到 $a$ 数组，求 $a$ 的最长上升序列长度。

# 正文：

如果 $t$ 足够大，答案是固定的。设 $cnt$ 表示 $b$ 数组不同数字个数，则显然有当 $cnt\leq t$ 时答案是 $cnt$。

再考虑 $cnt>t$ 的情况。跑一趟 $O(n^2t^2)$ 的最长上升子序列显然不可能，考虑优化它。设 $f_i$ 表示 $a$ 数组中第 $i$ 个数在最长上升序列的最长长度。则有：

$$f_i=\max_{j<i,a_j<a_i}\{f_i+1\}$$

其中 $\max$ 可以用树状数组维护。

还有一点，空间 $O(nt)$ 是接受不了的，考虑滚动数组，滚到 $O(n)$ 就行了。

# 代码：

```cpp
int k, t, n, maxb, cnt;
bool a[N];

int tr[N], f[N], b[N];

void update(int x, int val)
{
	for (; x <= maxb; x += x & -x) tr[x] = max(tr[x], val);
	return;
}

int query(int x)
{
	int ans = 0;
	for (; x; x -= x & -x) ans = max(ans, tr[x]);
	return ans;
}

int ans;

int main() 
{
    for (scanf("%d%d%d%d", &k, &n, &maxb, &t); k--; )
    {
    	ans = 0;
    	memset (a, 0, sizeof a);
    	memset (b, 0, sizeof b);
    	memset (tr, 0, sizeof tr);
    	memset (f, 0, sizeof f);
    	cnt = 0;
    	for (int i = 1; i <= n; i++)
    	{
    		scanf ("%d", &b[i]);
    		if (!a[b[i]]) cnt++, a[b[i]] = 1;
		}
		if (cnt <= t) {printf ("%d\n", cnt); continue;} 
		for (int j = 1; j <= t; j++)
			for (int i = 1; i <= n; i++)
			{
				int tmp = query(b[i] - 1) + 1;
				if (tmp > f[i])
				{
					f[i] = tmp;
					update(b[i], tmp);
					ans = max (ans, tmp);
				}
			}
		printf ("%d\n", ans);
	}
    return 0;
}
```

---

## 作者：JA_yichao (赞：3)

## 思路
首先我们可以得到：**当t大于等于当前数列不同数字的个数时，
答案就是不同数字的个数。**

### 证明
假设当前不同数字的个数 $sum$ 为 $3,t=3;$

此时共有 $sum$ 个相同的序列，

那么我们在**第 $x$ 个序列选择第 $x$ 小的数** $(1<=x<=t)$，

此时一定能保证生成含有 **$sum$ 个元素**的最长上升子序列。
图例：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020081819105110.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0phY2ttYV9tYXlpY2hhbw==,size_16,color_FFFFFF,t_70#pic_center)

----
接下来处理 $k<sum$ 的情况

我们可以设一个 $f[j]$ 表示当前周期的最长序列长度，

由于数据太大，所以要开**滚动数组**。

当枚举到当前周期时，考虑怎样转移。

最长上升子序列的动态转移方程为

$f[i]=max(f[j])+1(j<i,a[j]<a[i])$

其实这道题也是一样的，我们找到比 $a[j]$ 小的数，也就是 $a[j]-1$，

我们就可以想到用树状数组维护。

显然，我们用树状数组维护的是最大值。

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;

int a[100010],b[100010],f[100010],tree[100010];
int k,n,maxb,t,ans;

int lowbit(int x)
{
	return x&(-x); 
}
int find(int x)
{
	int ans=0;
	for(; x; x-=lowbit(x))
	   ans=max(tree[x],ans);   //求区间最大值
	return ans;
}
void query(int x,int c)
{
	for(; x<=maxb; x+=lowbit(x))
	   tree[x]=max(tree[x],c);   //修改区间最大值
}
int main()
{
    cin>>k>>n>>maxb>>t;
    while(k--)
     {
     	int sum=0;
     	ans=0;
     	for(int i=1; i<=n; i++)
     	 {
     	 	scanf("%d",&a[i]);
     	 	if(b[a[i]]!=k+1)   //标记求sum，不用赋初值，因为每次k+1都不一样
     	 	  sum++;
     	 	b[a[i]]=k+1;
     	 }
     	if(t>=sum)  //特判
     	 {
     	 	cout<<sum<<endl;
     	 	continue;
     	 }
     	for(int i=1; i<=100007; i++)
     	   tree[i]=f[i]=0;
     	for(int i=1; i<=t; i++)
     	 for(int j=1; j<=n; j++)
     	  {
     	  	 int c=find(a[j]-1)+1;
     	  	 if(c>f[j])
			  {
			  	f[j]=c;
			  	ans=max(ans,c);
			  	query(a[j],c);
			  }
             if(ans>sum)  //不存在ans>sum的情况
               break;
     	  }
        printf("%d\n",ans);
     }
    return 0;
}
```

---

## 作者：VLMOESR (赞：2)


# 思路：

首先我们可以得到：当 $t$ 大于当前数列不同数字的个数时，答案就是不同数字的个数。

因为它是严格单调递增，所以在每个周期里选一个数就可以组成一个上升序列。

接下来处理上述不成立的情况

我们可以设一个 $f[i][j]$ 表示当前周期的最长序列长度，由于数据太大，所以要开滚动数组。当枚举到当前周期时，我们考虑怎样转移。
我们想想最长上升子序列的动态转移方程：

$$f[i]=max(f[j])+1 (j<i,a[j]<a[i])$$

其实这道题也是一样的，我们要找到比 $a[j]$ 小的数，也就是 $a[j]-1$，我们就可以想到可以用树状数组维护。
# 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<map>
#include<cstring>
using namespace std;

int k, n, maxb, t, sum;
int a[100100], b[20000100];
int f[100100], tree[100100];

int VL_lowbit(int x){return x & -x;}
void VL_change(int x, int y)
{
	for(; x<=maxb; x+=VL_lowbit(x))
	    tree[x]=max(tree[x], y);
} 
int VL_find(int x)
{
	int ans=0;
	for(; x; x-=VL_lowbit(x))
		ans=max(ans, tree[x]);
	return ans;
}
int main(){
	scanf("%d%d%d%d", &k, &n, &maxb, &t);
	while(k--)
	{ 
		sum=0;
		for(int i=1; i<=n; i++)
		{
			scanf("%d", &a[i]);
			if(b[a[i]]!=k+1)
				sum++;
			b[a[i]]=k+1;
		}
		if(t>=sum)
		{
			printf("%d\n", sum);
			continue;
		}
		int ans=0;
		for(int i=1; i<=100007; i++)
			f[i]=tree[i]=0;
		for(int i=1; i<=t; i++)
			for(int j=1; j<=n; j++)
			{
				int x=VL_find(a[j]-1)+1;
				if(x>f[j])
				{
					f[j]=x;
					ans=max(ans, x);
					VL_change(a[j], x);
				}
				if(ans>=sum)break;
			}
		printf("%d\n", ans);
	}
	return 0;
}

```

---

## 作者：Purslane (赞：0)

# Solution

题解的做法大多都是 $O(knb \log n)$，但是显然题目想要你写 $O(knb)$ 的复杂度的。给一种题目中没有的做法。

~~刚开始把题目看错了，以为 $nt \le 2 \times 10^7$ 给我想玉玉了~~

考虑按照数的大小加点，$dp_{i,j}$ 表示考虑了所有 $\le i$ 的数，长度为 $j$ 的上升子序列结束端点最近是何处。

考虑把所有 $i+1$ 加进去。如果 $dp_{i,j-1} < pos < dp_{i,j}$，其中 $a_{pos}=i+1$，那么 $dp_{i+1,j} \leftarrow \min pos$，否则 $dp_{i+1,j} \leftarrow dp_{i,j}$。

注意到可能的 $pos$ 只有 $O(nb)$ 个，因为 $t \ge b$ 的时候一定存在 $b$ 的上界。

所以我们直接对两个序列进行简单归并即可，复杂度为 $O(knb)$。但是它跑了 $2 \rm s$ 是怎么回事 /yun

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int k,n,m,t,tot,dp[MAXN],a[MAXN],nxt[MAXN],occ[MAXN];
int solve(void) {
	ffor(i,1,n) cin>>a[i];
	memset(occ,0,sizeof(occ));
	roff(i,n,1) nxt[i]=occ[a[i]],occ[a[i]]=i;
	roff(i,n,1) if(!nxt[i]) nxt[i]=occ[a[i]];
	tot=0,memset(dp,0x3f,sizeof(dp));
	ffor(i,1,m) if(occ[i]) {
		int pos=occ[i],lst=0;
		ffor(j,1,tot+1) {
			while(pos<lst) {
				int ori=pos-(pos-1)/n*n;
				int psl=nxt[ori],npos=0;
				if(psl>ori) npos=pos+psl-ori;
				else npos=pos+n+psl-ori;
				pos=npos;
			}
			int ori=dp[j];
			if(pos<dp[j]) dp[j]=pos;
			lst=ori;
			if(j==tot+1&&dp[j]==pos) {
				tot++;
				break ;	
			}
		}
	}
	roff(i,tot,1) if((dp[i]-1)/n<t) return i;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>k>>n>>m>>t;
	while(k--) cout<<solve()<<'\n';
	return 0;
}
```

---

## 作者：Sad_Rex (赞：0)

> 相关题目 [最长上升子序列](https://www.luogu.com.cn/problem/B3637)

### 最长上升子序列优化

本题中 $N \leq 10^5$, 明显我们不能用 $O(N^2)$ 求最长上升子序列，考虑优化。

我们发现每次转移时，操作为 $1 \to a_i - 1$ 中寻找最大值，考虑树状数组前缀最大值。

以下为前缀最大值的修改和查询函数

```cpp

void modify(int x,int v){
    for(int i=x;i<=mx;i+=low(i))
        tree[i]=max(tree[i],v);
}
int ask(int x){
    int c=0;
    for(int i=x;i;i-=low(i))//前缀
        c=max(c,tree[i]);
    return c;
}
```

在转移时我们仅需

```cpp
int c=ask(x[j]-1)+1;//1 - x[j]-1 的 max
if(c>f[j]){
	f[j]=c;
	ans=max(ans,c);
	modify(x[j],c);//向后修改
}
```

以上是求最长上升子序列的优化。

### 分讨

不妨设 $tot$ 为序列 $a$ 的不重复元素个数。

若 $tot \leq t$，则明显有答案为 $tot$。

反之我们跑优化过的最长上生子序列即可。

因为 $n \times maxnb \leq 10^7$ 且 情况2的 $k < tot$ 且 $tot \leq manb$，所以 $O(Nt)$ 的时间复杂度正确。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mk make_pair
const int N=1e6+90;
int T,n,mx,k;
int f[N];
int tree[N];
int x[N];
int d[N];
int ans,tot;
void init(){
    ans=tot=0;
    memset(f,0,sizeof f);
    memset(x,0,sizeof x);
    memset(d,0,sizeof d);
    memset(tree,0,sizeof tree);
}
int low(int x){return x&-x;}
void modify(int x,int v){
    for(int i=x;i<=mx;i+=low(i))
        tree[i]=max(tree[i],v);
}
int ask(int x){
    int c=0;
    for(int i=x;i;i-=low(i))
        c=max(c,tree[i]);
    return c;
}
signed main(){
    cin>>T>>n>>mx>>k;
    while(T--){
        init();
        for(int i=1;i<=n;i++)
            cin>>x[i],tot+=(d[x[i]]==0?d[x[i]]=1:0);
        if(tot<=k){
            cout<<tot<<'\n';
            continue;
        }
        for(int i=1;i<=k;i++)
            for(int j=1;j<=n;j++){
                int c=ask(x[j]-1)+1;
                if(c>f[j]){
                    f[j]=c;
                    ans=max(ans,c);
                    modify(x[j],c);
                }
            }
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：moonbowqwq (赞：0)

[题目链接](https://codeforces.com/problemset/problem/261/D)

此做法学习自 CF 上的这份 AC 代码：[link](https://codeforces.com/contest/261/submission/25566348)。

## 题意简述

有一个长度为 $n$ 的正整数数列 $b$，满足其最大的元素 $b_{max}$ 和 $n$ 的乘积不大于 $2 \times 10^7$，现将该数列重复 $t$ 次，求形成的新数列 $a$ 的最长上升子序列长度。

多次询问，每个测试点询问次数不超过 $10$ 次，测试数据满足：$ 1 \leq n, b \leq 10^5, n \times b_{max} \leq 2 \times 10^7, t \leq 10^9$。

## 解题思路

设数列 $b$ 中的元素种数为 $d$，可以发现，当 $t \geq d$ 时，答案为 $d$，所以我们只需要考虑 $t < d$ 的情况即可。

考虑动态规划，我们设 $f_{i, j}$ 表示当前枚举到数列 $a$ 的第 $i$ 位，以不超过 $j$ 的数字结尾最长上升子序列长度。那么转移方程就为：

$$f_{i, j} = \begin{cases}
				f_{i - 1, j} &\text{ if } j < a_i \\
                f_{i - 1, j - 1} + 1 &\text{ if } j = a_i \\
                \max(f_{i - 1, j}, f_{i, a_i}) &\text{ if } j > a_i
			 \end{cases}$$

但是直接这样做是 $O(ntb_{max})$ 的，尝试优化，首先我们可以把第一维滚掉，然后对于取 $\max$ 的更新操作，由于 $f$ 值是单调的，当我们从 $f_{a_i}$ 开始从小到大更新 $f$ 的值时发现某一个 $f_j \geq f_{a_i}$ 后，直接跳出当前更新，继续考虑下一位 $a_i$ 即可。加上离散化后，这样做的复杂度就降为 $O(nt + d^2)$ 了。

## 代码实现

马蜂逐渐离谱……

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace my_code{
  #define ll long long
  const int N = 1e5;

  int k, n, maxb, t;

  int b[N + 5], num_diff, uni[N + 5], f[N + 5];

  void solve(){
    num_diff = 0;

    for(int i = 1; i <= n; ++i){
      scanf("%d", &b[i]);
      uni[++num_diff] = b[i];
    }
    
    sort(uni + 1, uni + 1 + num_diff);
    num_diff = unique(uni + 1, uni + 1 + num_diff) - uni - 1;
    for(int i = 1; i <= n; ++i)
      b[i] = lower_bound(uni + 1, uni + 1 + num_diff, b[i]) - uni;

    if(t >= num_diff){
      printf("%d\n", num_diff);
      return;
    }

    for(int i = 1; i <= num_diff; ++i)
      f[i] = 0;
    f[num_diff + 1] = N;

    for(int i = 1; i <= t; ++i)
      for(int i = 1; i <= n; ++i){
        f[b[i]] = f[b[i] - 1] + 1;
        for(int j = b[i]; f[j + 1] < f[j]; f[j + 1] = f[j], ++j);
      }

    printf("%d\n", f[num_diff]);
    return;
  }

  void my_main(){
    scanf("%d%d%d%d", &k, &n, &maxb, &t);
    while(k--)
      solve();
    return;
  }
}

int main(){
  my_code::my_main();
  fflush(stdout);
  return 0;
}
```

---

## 作者：xuantianhao (赞：0)

# [Maxim and Increasing Subsequence](https://www.luogu.com.cn/problem/CF261D)

首先，我们可以发现，当这个重复次数很大的时候，答案就等于序列中出现的不同权值个数。实际上，这个“很大”就可以被当作“大于等于不同权值个数”。

不同权值个数实际上是 $\min(n,m)$ 级别的，其中 $n$ 是序列长度，$m$ 是序列最大值。因此直接特判掉即可。

我们考虑暴力 DP，设 $f_{i,j}$ 表明现在跑到序列中的第 $i$ 个位置，且所有最后一个数小于等于 $j$ 的 LIS 的长度的最大值。假如我们直接暴力扫过 DP 数组更新的话，最多最多更新 $\min(n,m)^2$ 次，即最终把 DP 数组中所有数全都更新到最大值。而又有 $n\times m\leq2\times10^7$，所以我们最终会发现复杂度最大只有 $2\times10^7$。时限 6 秒，轻松跑过。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+100;
int T,n,lim,m;
int a[N],f[N];
vector<int>v;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    cin>>T>>n>>lim>>m;
    while(T--){
        v.clear();
        for(int i=0;i<n;i++){
			cin>>a[i];
			v.push_back(a[i]);
		}
        sort(v.begin(),v.end());
		v.resize(unique(v.begin(),v.end())-v.begin());
        if(v.size()<=m){printf("%d\n",v.size());continue;}
        for(int i=0;i<n;i++) a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;
        for(int i=1;i<=v.size();i++) f[i]=0;
        for(int i=0;i<n*m;i++){
            int now=f[a[i%n]-1]+1;
            for(int j=a[i%n];j<=v.size();j++){
				if(f[j]<now) f[j]=now;
				else break;
			}
            if(f[v.size()]==v.size()) break;
        }
        cout<<f[v.size()]<<'\n';
    }
    return 0;
}
```


---

## 作者：qfpjm (赞：0)

# 题解

- 设 $b$ 数组中不同数的个数为 $cnt$.

- 显然，当 $t$ 足够大时（$cnt\leq t$），答案是固定的，即为 $cnt$，证明比较简单。

- 如果 $t$ 不是很大A（$cnt>t$），我们就要考虑如何维护答案了。

- 首先存储的问题，我们需要用滚动数组存储。

- 求最长上升子序列，我们用动态规划处理。设 $f_i$ 为复制后的数组中（即 $a$ 数组）中第 $i$ 个数在最长上升序列的最长长度。状态转移方程为：

$$f_i=\max_{j<i,a_j<a_i}\{f_i+1\}$$

- 上述的 $\max$ 可以用树状数组维护。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int k, t, n, maxb, cnt, tr[100005], f[100005], b[100005];
bool vis[100005];

int lowbit(int x)
{
	return x & -x;
}

void update(int x, int val)
{
	for ( ; x <= maxb ; x += lowbit(x))
	{
		tr[x] = max(tr[x], val);
	}
	return;
}

int query(int x)
{
	int ans = 0;
	for (; x; x -= lowbit(x))
	{
		ans = max(ans, tr[x]);
	}
	return ans;
}

int ans;

int main() 
{
	cin >> k >> n >> maxb >> t;
    while (k--)
    {
    	ans = cnt = 0;
    	memset(vis, 0, sizeof vis);
    	memset(b, 0, sizeof b);
    	memset(tr, 0, sizeof tr);
    	memset(f, 0, sizeof f);
    	for (int i = 1 ; i <= n ; i ++)
    	{
    		cin >> b[i];
    		if (!vis[b[i]])
			{
				cnt ++;
				vis[b[i]] = 1;
			}
		}
		if (cnt <= t)
		{
			cout << cnt << endl;
			continue;
		} 
		for (int j = 1 ; j <= t ; j ++)
		{
			for (int i = 1 ; i <= n ; i ++)
			{
				int tmp = query(b[i] - 1) + 1;
				if (tmp > f[i])
				{
					f[i] = tmp;
					update(b[i], tmp);
					ans = max (ans, tmp);
				}
			}
		}
		cout << ans << endl;
	}
    return 0;
}
```


---

## 作者：CHHC (赞：0)

## 题意
（多测。）给定一个长为$n$的序列，满足对于序列中任意元素$i$有$i∈[1,maxb]∩Z$。将此序列复制t次得到新序列，求新序列的最长严格上升子序列长度。$n,maxb≤105$，$t≤10^9$，$n×maxb≤2×107$。
## 思路
首先，由于要求的是最长“严格上升”子序列长度，所以若$t$比序列中不同元素的个数还要多，那么答案只能是“序列中不同元素的个数“。这样有$t≤min(n,maxb)$。

考虑dp。$dp(i,j)$表示考虑到第i段复制序列，最大元素为$j$的最长严格上升子序列长度。但这样需要记录并查找每个值的出现位置。为了方便转移，我们可以考虑修改dp状态：$dp'(i,j)$表示考虑到第$i$段复制序列，最大元素不超过$j$的最长严格上升子序列长度。这样每次更新都是一个连续区间。（如果数据范围大一些可以考虑线段树维护，但是此题可以暴力跑过去）。dp状态总数为$t×maxb≤n×maxb≤2×10^7$。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int N, maxb, t;
int a[100010];
int dp[100010];

void solve()
{
    for (int i = 1; i <= N; i++)
    {
        cin >> a[i];
    }
    if (t >= N || t >= maxb) // 处理t较大的情况
    {
        map<int, int> mp;
        for (int i = 1; i <= N; i++)
        {
            mp[a[i]]++;
        }
        cout << (int)mp.size() << endl; // 直接输出不同元素个数
        return;
    }
    for (int i = 1; i <= t; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            for (int k = a[j]; k <= maxb; k++) // 考虑从当前点转移
            {
                if (dp[k] >= dp[a[j] - 1] + 1)
                    break;
                dp[k] = dp[a[j] - 1] + 1;
            }
        }
    }
    cout << dp[maxb] << endl;

    memset(dp, 0, sizeof(dp));
}

signed main()
{
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    cin >> N >> maxb >> t;
    while (T--)
        solve();

    return 0;
}
```
（翻到两篇写在本地的题解…姑且发一下好了）

---


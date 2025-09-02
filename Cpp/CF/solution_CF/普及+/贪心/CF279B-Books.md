# Books

## 题目描述

你有 $n$ 本书，读第 $i$ 本书需要 $a_i$ 分钟，你现在有 $m$ 分钟

你读书的方式是这样的：找出任意一个数 $x$，并按编号从小到大的顺序读第 $x \sim n$ 本   
如果你读完了第 $n$ 本，那么读书结束  
如果你准备要读第 $i$ 本书，但是剩下的时间小于 $a_i$（也就是读不完这本书）：那么你就**不可以开始读**这本书了，并且读书结束  
换句话说，如果你读一本书，就必须要读完，否则就不能读

求最多能读多少本书

## 说明/提示

$1 \le n \le 10^5$  
$1 \le m \le 10^9$  
$1 \le a_i \le 10^4$

感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
4 5
3 1 2 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 3
2 2 3
```

### 输出

```
1
```

# 题解

## 作者：FanYongchen (赞：5)

这道题就是找一个区间，这个区间的每个数字的和小于等于$m$且长度最长。

看到别的大佬都用了二分，这里就用一下尺取法。

当然，尺取法的效率别二分是要低很多的，但它容易呀。

有关尺取法，可以看一下这二篇文章：[传送门1](https://blog.csdn.net/lxt_Lucia/article/details/81091597)，[传送门2](https://www.luogu.com.cn/blog/Nero-Yuzurizaki/chi-qu-fa-xiao-jie)。

这里思路大致如下：

有一个左端点$l$，表示从第$l$本开始读，然后一直往后找，直到时间读完，读到了第$r$本，然后将$l$左端点右移一位，顺便统计最长长度。

右移后，因为我们已经统计出$l$到$r$所花的时间，所以下一次只要把$a[l]$减去，然后继续往后找就行了。

```cpp
#include <iostream>
using namespace std;
int n,m;
int a[100005];
int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++) cin>>a[i];
    int l=0,r=0;//左端点与可读到的最后一本书
    int ans=0,sum=0;//ans表示最多可读的书，sum表示花的时间
    while(l<n)
    {
        while(r<n&&sum+a[r]<=m) sum+=a[r++];//一直往下读，直到没时间
        if(r==n) {ans=max(ans,r-l);break;}
        //如果读到了最后一本，直接可以结束。
        //因为之后你不管怎么读，都不可能再有比这个多的数
        if(r==l) {l++,r++,sum=0;continue;}//如果现在一本书也读不了
        ans=max(ans,r-l);//统计出最长长度
        sum-=a[l],l++;//减去a[l]，为下一次统计做准备
    }
    cout<<ans;//输出
    return 0;
} 
```

---

## 作者：fjy666 (赞：4)

### 0x01 思路
看到 $n \le 10^5$ ，我们不难发现：$\Theta(n^2)$ 的暴力肯定 TLE ，想也不用想。  
于是，我们就想到了 **二分查找**，用 $\Theta(n\times\log n)$的复杂度来解决。  
怎么实现呢？  
对于每一个点 $p$ ，二分最大的点 $q$，使
$$\sum^q_{i=p}a_i \le t$$
但是，求 $\sum^q_{i=p}$ 不是 $\Theta(n)$ 吗？  
没关系，使用 **前缀和** 即可！

$q$ 的范围：$i \le q \le n$。
- 若 $a_p > t$ 会不会越界？  
不会，因为二分后 $r = p - 1$ ，$r-p+1$ 的值为 $0$。
- 若 $\sum^n_{i=p} \le t$ 会不会越界？  
不会，别忘了，二分完 $p \le n$！

这样，我们就用 $\Theta(n\times\log n)$ 的优秀复杂度解决了这个问题。

------------
### 0x02 代码
```cpp
#include <cstdio>
#include <algorithm>
#define fo(i_,j_,k_) for(int i_=j_;i_<=k_;++i_)
#define fr(i_,j_,k_) for(int i_=j_;i_>=k_;--i_)
#define It(type_) type_::iterator
#define rg register
#define rtn return
#define il inline

typedef long long ll;
using namespace std;
const int kMaxn = 100005;
int books[kMaxn],sum[kMaxn];

int main()
{
	int n,t,ans = 0;
	scanf("%d%d",&n,&t);
	fo(i,1,n) 
	{
		scanf("%d",books+i);
		sum[i] = sum[i-1] + books[i];
	}
	fo(i,1,n)
	{
		int l = i,r = n;
		while(l <= r)
		{
			int mid = l + r >> 1; 
			if(sum[mid] - sum[i-1] <= t) l = mid + 1;
			else r = mid - 1; 
		}
		ans = max(ans,r - i + 1);
	}
	printf("%d",ans);
	rtn 0;
}
```

---

## 作者：是个汉子 (赞：4)

### Solution

这个题可以看成找一段区间书的数量最多，那么我们不难想到**尺取法**。

### 代码

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int N=1e5+10;
int a[N],n,t;

int main(){
    scanf("%d%d",&n,&t);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    int l=1,r=1,s=0,ans=0;
    while(233){
        while(r<=n&&s<=t) s+=a[r++];
        if(s<=t){
            ans=max(ans,r-l);
            break;
        }
        else ans=max(ans,r-l-1);
        s-=a[l++];
    }
    printf("%d\n",ans);
    return 0;
}
```



---

## 作者：mszyyds (赞：2)

## 思路：尺取法
本题要找以每一位开始最多能看的数的本数，设以 $i$ 开头最多能连续看到第 $j_{i}$ 。显然 $j_{i} >j_{i-1}$，所以可以用尺取做。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[100005],num,ans;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,j=0;i<=n;i++)
	{
		num-=a[i-1];
		while(num<=m&&j<=n) num+=a[++j];
		num-=a[j--];
		ans=max(ans,j-i+1);
	} 
	cout<<ans;
	return 0;
}
```


---

## 作者：Z_M__ (赞：1)

**题意：**

题目意思可以理解为：有n本书，m分钟，任意选一本书从这本书开始往后读，直到时间不够用时停止，问最多读几本书？

**分析：**

- 首先想到暴力做法：枚举每本书$i$再往后枚举直到大于$m$时停止，更新答案。$n\le 1e5$,时间复杂度为$O(n^2)$,所以这样做显然会TLE，考虑优化。

- 假设当前选了第$i$本书，最多能读到第$j$本书。由于选完一本书后，就不能读该书前面的书了，所以$j>=i$ , 那么选择第$i+1$本书时，最多能读到$k (k>=j)$,也就是在选择第$i+1$时与$i$已经没有关系了。

- 所以可以先处理出读书时间的前缀和，再用两个指针$l$，$r$，表示当时选第$l$本书,$r$是向后延展的位置，当$sum[r]-sum[l - 1]<m$时，说明还可以向后延展，此时$r++$）。而当$sum[r]-sum[l - 1]>m$时，说明$r-1$是$l$向后最长的延展距离，这时更新一下答案，并且$i$就没用了，所以$i++$,也就是换到第$i+1$本书了，继续上述操作。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
int n, m, l, r, ans;
int sum[MAXN];
int main ()
{
	ios :: sync_with_stdio (0), cin.tie (0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> sum[i], sum[i] += sum[i - 1];
	l = 1, r = 1;
	while (r <= n)
	{
	    if (sum[r] - sum[l - 1] <= m) // 还不够，继续读 
		{
	    	r++;
		}
	    else
		{
			ans = max (ans, r - l), l++; // 超过了，更新答案（注意是r-l）	
		}
	}
	cout << max (r - l, ans) << endl; //注意最后还要和r-l比一下
	return 0;
}

```

---

## 作者：XL4453 (赞：0)

### 解题思路：

题目中所说的从 $x$ 开始一直读到 $n$ 结束，由于并不一定要读到 $n$ 结束，而是有可能在中间停止，所以这个问题其实就相当于要找一个连续的区间使得这一段区间满足：$\sum a_i\le m$ 且这一段区间尽可能大。

那么考虑尺取法，用两个指针维护左右边界，每一次左指针向右移动一格，右指针向右移动直到无法再向右扩展，可能是边界限制也可能是时间限制，然后更新答案。

这样由于两个指针都是只向右移动，每一个的移动距离都是 $n$ 故复杂度是 $O(n)$ 的，可以通过这道题。


---------
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,a[100005],l,r,ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]),a[i]+=a[i-1];
	l=1;
	while(l<=n){
		while(r<n&&a[r+1]-a[l-1]<=m)r++;
		ans=max(ans,r-l+1);
		l++;	
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Otomachi_Una_ (赞：0)

考虑函数 $f(x)$ 为选择数 $x$ ，最多能读到第几本书，显然 $f(x)$ 是单调递增的。

也就是在枚举的时候，不用从 $1$ 开始，只需要从上一轮结束的地方开始即可，这种方法我们称之为 **尺取法** 。

# Code

```cpp
#include<iostream>
using namespace std;
const int MAXN=1e5+5;
int n,m,ans,l=1;
int a[MAXN];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]+=a[i-1];
	}
	for(int r=1;r<=n;r++){
		while(a[r]-a[l-1]>m)
			l++;
		ans=max(ans,r-l+1);
	}
	cout<<ans;
}
```


---

## 作者：Priori_Incantatem (赞：0)

一道很简单的二分题

我们先枚举 $i$，表示从第 $i$ 本书开始往后读  
那么，肯定存在一个下标 $j$，满足从第 $i$ 本书开始往后读，只能读完第 $j$ 本（读不了后面的），除非第 $i$ 本都读不了（$a_i>m$）

那么，我们就二分查找这个端点 $j$

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int Maxn=100000+10,inf=0x3f3f3f3f;
int a[Maxn],s[Maxn];
int n,m,ans;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read(),m=read();
	
	for(int i=1;i<=n;++i)
	a[i]=read(),s[i]=s[i-1]+a[i];
	
	for(int i=1;i<=n;++i)
	{
		if(a[i]>m)continue; //如果第i本书都读不了，要你有何用
		int l=i,r=n; // 二分查找右端点j
		while(l<r)
		{
			int mid=(l+r)>>1;
			mid++;
			if(s[mid]-s[i-1]<=m)l=mid;
			else r=mid-1;
		}
		ans=max(ans,l-i+1); // 更新答案
	}
	printf("%d\n",ans);
	return 0;
}
```

---


# Queries about less or equal elements

## 题目描述

You are given two arrays of integers $ a $ and $ b $ . For each element of the second array $ b_{j} $ you should find the number of elements in array $ a $ that are less than or equal to the value $ b_{j} $ .

## 样例 #1

### 输入

```
5 4
1 3 5 7 9
6 4 2 8
```

### 输出

```
3 2 1 4
```

## 样例 #2

### 输入

```
5 5
1 2 1 2 5
3 1 4 1 5
```

### 输出

```
4 2 4 2 5
```

# 题解

## 作者：百里迎荷 (赞：5)

# 题目：对于任何一个bi，输出在a数组中小于等于bi的数的个数。



首先想到暴力：这道题暴力肯定是过不了的，**复杂度O(nm)**（1≤n,m≤2·10^5)

优化：将a数组排序，然后在a数组中**二分**找出第一个大于bi的数，**复杂度O(lognm)**


------------


二分代码
```cpp
int ans(int x)
{
	int l=0,r=n-1,mid;
	while(l<=r)
	{
		mid=(l+r)/2;
		if(x<a[mid]) r=mid-1;
		else l=mid+1;
	}
	return l;
}
```



------------


手敲二分麻烦，~~还容易死循环qwq~~

所以，接下来该 c++ 万能，神奇，快速，便捷，~~哲学~~ 的**stl**出场了

今天介绍的两个函数是：

**lower_bound()** and **upper_bound()**

百度中的解释：lower_bound()返回一个 iterator (迭代器)， 它指向在 [first,last] 标记的**有序**序列中可以插入value，而不会破坏容器顺序的第一个位置，而这个位置标记了一个不小于value 的值。该函数为C++ STL内的函数。

这个解释较难理解 ~~巨佬请无视~~

简单来说，
lower_bound返回大于等于某个元素值的迭代器
lower_bound返回大于某个元素值的迭代器
(是用二分的)**注意：返回的是迭代器**


使用方法:

lower_bound(起始地址，结束地址，要查找的数值) 

upper_bound(起始地址，结束地址，要查找的数值)


------------

献上丑陋的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector <int> a;
int ans(int x)
{
	return upper_bound(a.begin(),a.end(),x)-a.begin();
    //算法核心，用了upper_bound函数；
    //本来应该减一，但因为下标从0开始，加一减一抵消
}
int main(){
  
	int n,m,tmp,x;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&tmp),a.push_back(tmp);//读入
    
	sort(a.begin(),a.end());//容器必须有序，所以要排序
    
	for(int i=1;i<=m;i++)
		scanf("%d",&x),printf("%d ",ans(x));//输出
	return 0;
  
}
```


------------

管理大大求过qwq







---

## 作者：Alex_Wei (赞：3)

仔细看题目，发现这不就是个二分裸题嘛

先把 $a$ 数组排个序，然后依次读入 $b_i$ ，对于每个 $b_i$ ，二分查找在 $a$ 数组里 **第一个比它大的数的下标**，别忘了最后要 $-1$ （因为这个数不算），而且二分边界要设置为 $(1,n+1)$ ，防止 $a$ 数组里没有比 $b_i$ 大的数

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[200002],b;
int ef(int l,int r)//二分板子
{
	if(l==r)return l;
	int m=(l+r)>>1;
	if(a[m]>b)return ef(l,m);
	else return ef(m+1,r);
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];//读入
	sort(a+1,a+n+1);//排序
	for(int i=0;i<m;i++)
		cin>>b,cout<<ef(1,n+1)-1<<" ";//查找，注意边界
	return 0;
}
```


---

## 作者：hxhhxh (赞：2)

## 大意

给一个有 $ n $ 个元素的数组 $ a $ 和 $ m $ 个整数 $ b_i $ ，求对于每一个 $ b_i $ ，求 $ a $ 数组中有多少个不大于 $ b_i $ 数。

## 思路

#### 善用`STL`!

`upper_bound`的功能是在一个**有序**数组里找到第一个比它大的元素的位置，不存在则返回最后一个的下一个，具体用法可以看代码。

在第一个比它大的数的左边就是不大于它的数，所以答案就是`upper_bound(a+1,a+n+1,b)-a-1`

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[200005],b;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=m;i++){
		scanf("%lld",&b);
		printf("%lld ",upper_bound(a+1,a+n+1,b)-a-1);
	}
	return 0;
}
```

---

## 作者：Dantal10n (赞：2)

### 题目大意
已知 $n$ 个数，$q$ 次问询，每次问询这 $n$ 个数中小于等于某数的有多少个。  
数据范围：$n \le 2\times10^5, q \le 2\times10^5, |$所有数$|\le 10^9$
### 解题思路1
| 关键词 | 对应思路 |
| :----------: | :----------: |
| 小于等于 | 前缀和 |
| 所有数的绝对值$\le 10^9$ | 离散化 |

于是这题可以使用一道前缀和+离散化的方式解决。

离散化有两种方式：  
第一种：下标排序 $\rightarrow$ 逐个计算。  
时间复杂度 $\Theta(n\log_2n)$。  
代码：  
```cpp
//将a离散化
bool cmp1(const int &p,const int &q){return a[p]<a[q];}
......
for(int i=1;i<=n;i++)id[i]=i;
stable_sort(id+1,id+1+n,cmp1);
for(int i=1;i<=n;i++)
	t[id[i]]=(tot+=(i==1||a[id[i]]!=a[id[i-1]]));
for(int i=1;i<=n;i++)a[i]=t[i];
```

第二种：排序 $\rightarrow$ 去重 $\rightarrow$ 二分。  
这个遍地都是，可以参考蓝书实现或者[这个](https://blog.csdn.net/Cirspring/article/details/51836776)。

将 $a,b$ 数组合并成一个，然后离散化。  
思考：为什么不能分别离散化？

离散化结束后，创建值域数组，第 $i$ 项含义为数组 $a$ 中等于 $i$ 的数的数量，将其前缀和来计算数组 $a$ 中小于等于 $i$ 的数的数量。

之后遍历 $b$ 数组，对于每一项求出小于等于它的答案。

$AC\,code:$
```cpp
#include<bits/stdc++.h>
#define N 400005
using namespace std;
int n,m,a[N],b[N],t[N],s[N],id[N],tot;
bool cmp1(const int &p,const int &q){return a[p]<a[q];}
int read(){
	int x=0,t=1;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')t=-1;ch=getchar();}
	while('0'<=ch&&ch<='9')x=x*10+(ch-'0'),ch=getchar();
	return x*t;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n+m;i++)a[i]=read(),id[i]=i;
	stable_sort(id+1,id+1+n+m,cmp1);
	for(int i=1;i<=n+m;i++)
		t[id[i]]=(tot+=(i==1||a[id[i]]!=a[id[i-1]]));
	for(int i=1;i<=n;i++)a[i]=t[i];
	for(int i=1;i<=m;i++)b[i]=t[i+n];
	for(int i=1;i<=n;i++)s[a[i]]++;
	for(int i=1;i<N;i++)s[i]+=s[i-1];
	for(int i=1;i<=m;i++)printf("%d ",s[b[i]]);
	return 0;
}
```

### 解题思路2
如其余大多数题解所说，使用排序 $+$ 二分的方式求解。

------------
#### _Extra-Experience_
 1. 在`与真实值无关，只与大小关系有关时`，可使用离散化。
 2. 值域上的前缀和可求出小于等于某数的数的个数。

[云剪贴板版本](https://www.luogu.com.cn/paste/e2sqnok9)

---

## 作者：wanggk (赞：1)

### 一个不同于二分的做法
依题：
**“对于任何一个 $b[i]$ ，输出在 $a$ 数组中小于等于 $b[i]$ 的数的个数。”**

可知，答案与顺序无关。又看数据 $n,m ≤ 200000$ ，感觉可以排序。

于是，我们就先将两个数组排序，接着设立两个指针 $i$ 和 $j$ ， 分别指向两个数组。

随着每次 $j$ 增加 $1$ ， $i$ 不断向后更新至小于等于 $b[j]$ 的最后一位（因为排序后两个数组都是单调递增的，所以两个指针都是只加不减）。

代码感觉比二分好写，其实核心语句就四五行。
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n;
int ans[200005];
struct node{
	int idx;
	int val;
}a[200005],b[200005];
bool cmp(node x,node y){ return x.val<y.val; }
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&a[i].val);
		a[i].idx=i;
	}
	for(int i=1;i<=n;i++)
	{
		 scanf("%d",&b[i].val);
		 b[i].idx=i;
	}
	sort(a+1,a+1+m,cmp);
	sort(b+1,b+1+n,cmp);
	int i=0;
	for(int j=1;j<=n;j++)
	{
		while(a[i+1].val<=b[j].val&&i+1<=m) i++;
		ans[b[j].idx]=i;
	}
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：TRZ_2007 (赞：1)

**[题解 CF600B 【Queries about less or equal elements】](https://www.luogu.com.cn/problem/CF600B)**  
# Solution  

观察一下数据，发现 $1\le n,m\le 2\times 10 ^ 5$，因此 $\mathcal{O(n\times m)}$，的暴力做法明显不会过。因此我们考虑**二分**。  

~~如果有同学不会二分呢？~~  
那么……就讲一下吧……  

看这个图：  
当然，数据要有序。  
![](https://cdn.luogu.com.cn/upload/image_hosting/7epd1216.png)  

我们现在取一下这组数据的中点，发现这个数字大于我们的 mid ，那么在 mid 左边的数字都不可能会是解，因为它们都比 mid 小。继续，  
![](https://cdn.luogu.com.cn/upload/image_hosting/5pmueyrj.png)  

发现比 mid 大，那么答案在左边，但是区间长度为0了，输出答案就是数字 7 的位置。  
但是，我们要的答案不是 7 的位置，而是 5 的位置，怎么办？ 减一就好了。  

其实用函数也可以，就是比较慢，要吸氧。  
听说平衡树或者树状数组也可以过，这里就不讲了。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;

struct node {
	int val,size;
	int lson,rson;
}tree[N * 4];

int n,m,l,r;
int a[N],key,ans;

inline int find(int key) {
	l = 1;r = n + 1;
	int cnt = 0;
	while(l <= r) {
	//	cout << l << " " << r << "\n";
		int mid = (l + r) >> 1;
		if(a[mid] > key) {
			cnt = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	return cnt;
}

int main() {
	scanf("%d %d",&n,&m);
	for(int i = 1;i <= n;i++) {
		scanf("%d",&a[i]);
	}
	sort(a + 1,a + n + 1);
	a[n + 1] = INT_MAX;	//定义一个哨兵为 inf 以防关键字太大了。
	for(int i = 1;i <= m;i++) {
		scanf("%d",&key);
		ans = find(key);
		printf("%d ",ans - 1);
	}
	return 0;
}
```

---

## 作者：Lyz09 (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF600B)

在博客食用更佳。

------------

暴力解法

这题就是求对于每个 $b_i$，在 $a$ 数组中小于等于它的数字的个数。

这题如果使用暴力枚举每一个 $a_i$ 是否小于等于 $b_i$，时间复杂度为 $O(nm)$，肯定会 TLE 。

顺便附上暴力代码。

~~~cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,a[200001],b[200001];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	 scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	 scanf("%d",&b[i]);
	for(int i=1;i<=m;i++)
	{
		long long ans=0;
		for(int j=1;j<=n;j++)//暴力判断
		if(a[j]<=b[i])
		 ans++;
		printf("%lld ",ans);
	}
}
~~~

------------

正确做法

对于这种查找的题型，使用二分当然是一种很好的选择，但是手打二分对于我这种很懒的人来说，自然不想打，那应该怎么办呢？

这时候就应该使用 STL 中的法宝： **upper_bound** 和 **lower_bound** 。

用法：

lower_bound(数组起始地址，数组结束地址，查找数值)

upper_bound(数组起始地址，数组结束地址，查找数值)

lower_bound 是用来查找数组中第一个大于等于要查找的数值的元素， upper_bound 则是用来查找数组中第一个大于要查找的数值的元素。两者非常接近，区别在于一个是查找大于等于的元素，另一个是查找大于的元素。

**需要注意的是，两者返回的不是下标，而是迭代器！因此如果想求下标，应该减去数组起始地址（迭代器）。**

既然这两者这么接近，那么这题应该用哪一个呢？

因为题目求的是在 $a$ 数组中小于等于 $b_i$ 的数，因此应该求第一个大于 $b_i$ 的数的位置，在这个数之前的数即为符合题意的数。

又因为upper_bound 是求第一个大于要查找的数值，所以应用 upper_bound。

代码

~~~cpp
#include<iostream>
#include<cstdio>
#include<algorithm>//upper_bound 和 sort 都需要用到此库。
using namespace std;
int n,m,a[200001],b[200001];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	 scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	 scanf("%d",&b[i]);
	sort(a+1,a+n+1);//排序，因为 upper_bound 和 lower_bound 只能用在升序数组。
	for(int i=1;i<=m;i++)
	{
		int x=upper_bound(a+1,a+n+1,b[i])-a-1;//求符合题意的数字的个数
		if(x<0)
		 printf("%d ",x+1);//特殊情况
		else
		 printf("%d ",x);
	}
}
~~~

---

## 作者：跳跳谷hj (赞：0)

好吧，这题其实有点~~淼~~难度

[题目链接](https://www.luogu.com.cn/problem/CF600B)
## 暴力
首先，刚拿到题目还没有什么思路的时候就先打了个暴力

暴力其实很简单，当 $b$ 数组输入了一个数以后，扫描一遍 $a$ 数组以统计比此数要小的数据，最后再输出，就像这样
``` c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[200010],b[200010],ans[200010],n,m;
map<int,int>mp;
int main(){
//    freopen("elements.in","r",stdin);
//    freopen("elements2.out","w",stdout);
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        mp[a[i]]++;
    }for(int i=1;i<=m;i++){
        scanf("%lld",&b[i]);
        for(int j=1;j<=b[i];j++)ans[i]+=mp[j];
    }for(int i=1;i<=m;i++)printf("%lld ",ans[i]);
}
```
但暴力的时间复杂度用脚都可以估计出来，在极限数据的情况下，时间复杂度会来到 O($n^2$)，如果$n$，$m$都以最大值，即 $2*10^5$ 的情况下，会进行 $4*10^{10}$ 次运算，时间复杂度直接爆炸。

那此时，我们就要想办法降低时间复杂度。

## 二分
因为我们只用输出 $b$ 数组中每一个元素比a数组中有多少个元素比这个元素小的元素的个数，因此，我们可以对 $a$ 数组进行排序，之后再用二分与 $b$ 数组中的元素比对，这样就能大大地减少时间复杂度。

附上代码

``` c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[200010],ans[200010],n,m;
struct p{
	int num,id;
}b[200010];
bool cmp(p a,p b){
	return a.num<b.num;
}
int main(){
//    freopen("elements.in","r",stdin);
//    freopen("elements.out","w",stdout);
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    sort(a+1,a+1+n);
    for(int i=1;i<=m;i++){
    	scanf("%lld",&b[i].num);
    	b[i].id=i;
	}
    sort(b+1,b+1+m,cmp);
    for(int i=1;i<=m;i++){
    	int k=upper_bound(a+1,a+n+1,b[i].num)-a;//偷懒用了upper_bound
    	ans[b[i].id]=k-1;//因为upper_bound找出的是第一个比这个值大的元素的位置，因此减一
	}for(int i=1;i<=m;i++)printf("%lld ",ans[i]);
}
```
其实此题可以在输入了 $b$ 数组以后排序并在遇到了相同的值以后进行剪枝。

另：代码写出后记得造几组极限数据来测时间复杂度

---

## 作者：封禁用户 (赞：0)

## CF600B Queries about less or equal elements
[原题链接](https://www.luogu.com.cn/problem/CF600B)

## 分析
最简单的思路当然是将 $b$ 数组中的每个元素与 $a$ 数组进行逐个比较。但看到数据范围，这是行不通的。可以尝试用二分解出这道题。

## 思路
提到二分查找，自然想到 STL 中的函数：

``upper_bound(begin , end , num)``

即从数组的 $begin$ 位置到 $end-1$ 位置二分查找第一个大于 $num$ 的数字，返回它的位置。

推导过程：通过返回的地址减去起始地址，就能得到首个大于 $num$ 的数据在数组中的下标。由于数组已经通过 ``sort()`` 从小到大排列，则得到的下标等于小于等于 $b[i]$ 的数的个数。

于是我们用主函数中五行代码，愉快地通过了这道绿题。

## Code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[200010],b[200010];
int main(){
	int n,m;cin>>n>>m;
	for(int i=0;i<n;i++) cin>>a[i];
	for(int i=0;i<m;i++) cin>>b[i];
	sort(a,a+n); //数组需要有序
	for(int i=0;i<m;i++) cout<<upper_bound(a,a+n,b[i])-a<<" "; //上文推导得直接输出函数值即为答案
	return 0; //end
}
```


---

## 作者：WanderingTrader (赞：0)

看到题解区里基本都是二分做法，那我来个尺取吧。
### 题目分析
题目可以拆成 $m$ 个问询。对于 $1$ 到 $m$分别问询 $a$ 中小于等于 $b_i$ 的数的个数。

注意到问询的范围都一致，是整个 $a$ 数组。

因此第一想法是把 $a,b$ 的数放在一起离散化后把整个 $a$ 数组插入一个树状数组，然后进行前缀和查询。大约是 $O(n\log n)$ 级别的时间复杂度。

不过很快又想到一个更简单的方法。注意到都是离线问询，所以可以按照 $b$ 从小到大的顺序回答 $m$ 个问题。那么再将 $a$ 排序，于是一个 $O(n+m)$ 尺取的做法就出来了。

假设数组 $a,b$ 已排序。维护两个指针 $i,j$，分别对应数组  $a,b$。开始时 $i=1,j=1$，从 $1$ 到 $m$ 枚举 $j$。对于每个 $j$，只要 $a_i\le b_j$ 且 $i\le n$ 就让 $i$ 自增 $1$。最后答案就是 $i-1$。相当于用均摊 $O(1)$ 的尺取代替了 $O(\log n)$ 的 `upper_bound` 函数的功能。

### 代码
注意排序时不可直接在原数组上排序。常用的方法是结构体，但这里我用了排名数组代替了结构体（为了省码量）。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=2e5+5;
LL a[maxn],b[maxn],idA[maxn],idB[maxn],ans[maxn],n,m;
bool cmpIDA(int u,int v){return a[u]<a[v];}
bool cmpIDB(int u,int v){return b[u]<b[v];}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(LL i=1;i<=n;++i) scanf("%lld",a+i);
	for(LL i=1;i<=m;++i) scanf("%lld",b+i);
	for(LL i=1;i<=n;++i) idA[i]=i;
	for(LL i=1;i<=m;++i) idB[i]=i;
	sort(idA+1,idA+1+n,cmpIDA);
	sort(idB+1,idB+1+m,cmpIDB);
	LL i=1,j=1;
	for(j=1;j<=m;++j)
	{
		while(a[idA[i]]<=b[idB[j]]&&i<=n) ++i;
		ans[idB[j]]=i-1;
	}
	for(int i=1;i<=m;++i) printf("%lld ",ans[i]); puts("");
	return 0;
}
```
循环部分一定要小心，什么时候用 `i,j`，什么时候用`idA[i],idB[j]`。千万不可混淆。

$$\texttt{The End.}$$

---

## 作者：Juvenile (赞：0)

#### 题意：找出a数组中比b数组中每个数小或者相等的数的个数
------------
### 0.~~暴力~~
你觉得能拿多少分??? (灵魂的拷问)

注：$\color{red}(1≤n,m≤2·10^5) $ 

复杂度 $\color{red}O(nm)$   ~~除非玄学~~

------------
### 1.~~二分(手敲版)~~


代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200009
int n,m,a[N],b[N];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
		scanf("%d",&b[i]);	
	sort(a+1,a+n+1);//sort大法好
	for(int i=1;i<=m;i++)
	{
		int l=1,r=n;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(a[mid]>b[i]) r=mid-1;
			else l=mid+1;
		}
		printf("%d ",r);
	}
	return 0;
}
```

------------
### 2.~~二分(STL)~~

作为一名 _c++_ 选手，其实有更简单的做法

>upper_bound(a,a+n,k)

返回的就是第一个大于k的位置指针（a按照升序排列）如果a按照降序排列则是第一个小于k的位置指针
>lower_bound(a,a+n,k)

返回的就是第一个大于等于k的位置指针（a按照升序排列）如果a按照降序排列则是第一个小于等于k的位置指针

~~代码短就自己写去吧~~

---


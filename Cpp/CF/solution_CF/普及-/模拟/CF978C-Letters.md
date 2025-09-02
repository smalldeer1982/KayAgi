# Letters

## 题目描述

There are $ n $ dormitories in Berland State University, they are numbered with integers from $ 1 $ to $ n $ . Each dormitory consists of rooms, there are $ a_i $ rooms in $ i $ -th dormitory. The rooms in $ i $ -th dormitory are numbered from $ 1 $ to $ a_i $ .

A postman delivers letters. Sometimes there is no specific dormitory and room number in it on an envelope. Instead of it only a room number among all rooms of all $ n $ dormitories is written on an envelope. In this case, assume that all the rooms are numbered from $ 1 $ to $ a_1 + a_2 + \dots + a_n $ and the rooms of the first dormitory go first, the rooms of the second dormitory go after them and so on.

For example, in case $ n=2 $ , $ a_1=3 $ and $ a_2=5 $ an envelope can have any integer from $ 1 $ to $ 8 $ written on it. If the number $ 7 $ is written on an envelope, it means that the letter should be delivered to the room number $ 4 $ of the second dormitory.

For each of $ m $ letters by the room number among all $ n $ dormitories, determine the particular dormitory and the room number in a dormitory where this letter should be delivered.

## 说明/提示

In the first example letters should be delivered in the following order:

- the first letter in room $ 1 $ of the first dormitory
- the second letter in room $ 9 $ of the first dormitory
- the third letter in room $ 2 $ of the second dormitory
- the fourth letter in room $ 13 $ of the second dormitory
- the fifth letter in room $ 1 $ of the third dormitory
- the sixth letter in room $ 12 $ of the third dormitory

## 样例 #1

### 输入

```
3 6
10 15 12
1 9 12 23 26 37
```

### 输出

```
1 1
1 9
2 2
2 13
3 1
3 12
```

## 样例 #2

### 输入

```
2 3
5 10000000000
5 6 9999999999
```

### 输出

```
1 5
2 1
2 9999999994
```

# 题解

## 作者：Silence_water (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/CF978C)

---

$Analyse$

这是一道思路直接的题目。

翻译中丢掉了一个关键的信息：
> All $b_j$ are given in increasing order.

意思就是说询问序列的房间编号递增。

那么答案的楼层数必然不递减。所以先让初始楼层为 $1$，然后直接模拟，一层一层往上走，直到走到对应楼层为止。

---

$Solution$

第 $j$ 层的第 $k$ 个房间就是 $\sum\limits_{i=1}^{j-1}{a_i}+k$。

故可以先预处理出每个楼层的最后一个房间的编号。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=2e5+5;
int n,m,fl=1;
ll a[M],b[M],p[M];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		p[i]=p[i-1]+a[i];// 前缀和。p[i]即第i层的最后一个房间的编号
	}
	for(int i=1;i<=m;i++)
	{
		ll x;scanf("%lld",&x);
		ll ch=x-p[fl-1];// 还差这么多编号
		while(ch>a[fl])ch-=a[fl],fl++;// 模拟
		printf("%d %lld\n",fl,ch);
	}
	return 0;
}
```

---

$The$ $end$

客官看完别忘了点个赞哦~

---

## 作者：StudyingFather (赞：7)

这道题其实非常简单，按照题意计算即可。
```cpp
#include <iostream>
using namespace std;
long long n,m,a[200005],b[200005],c[200005];
int main()
{
 ios::sync_with_stdio(false);
 cin>>n>>m;
 for(int i=1;i<=n;i++)
 {
  cin>>a[i];
  c[i]=c[i-1]+a[i];
 }
 int f=1;
 for(int i=1;i<=m;i++)
 {
  cin>>b[i];
  long long k=b[i]-c[f-1];
  while(k>a[f])//这里计算宿舍号和房间号
   k-=a[f++];
  cout<<f<<' '<<k<<endl;
 }
 return 0;
}
```

---

## 作者：封禁用户 (赞：6)

题意就不说了，自行解决。

这道题目涉及的算法很容易想到：二分和前缀和。\
首先要二分的话，我们要实现一个单调性的数组 $sum$ ， $sum_i$ 用于表示   $a_1$ 到 $a_i$ 的和。 
求解 $sum_i $ 也很简单，开个循环， $sum_i $ = $sum_{i-1} $ + $a_i$ 。
然后对于每一个 $b_j$ 我们就可以通过二分 $sum$ 求得 $b_j$ 在哪一号寝室楼。
然后对于 $b_j$ 来说，我们找到了它的寝室号 $f$ ，那么他的房间号就是     $b_j$ − $a_{f-1}$ 。

实现代码如下：

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
long long a[200020],b,sum[200020];//long long预警
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i ++)
    {
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];//之前的人数
    }
    while(m--)
    {
        cin>>b;
        int f=lower_bound(sum+1,sum+1+n, b)-sum;//宿舍号
        long long k=b-sum[f-1];//房间号
        cout<<f<<" "<<k<<endl;
    }
    return 0;
}

```
# 完结撒花^_^

---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF978C) & [CF链接](http://codeforces.com/problemset/problem/978/C)

## 思路分析：

题目叙述清晰明了，在这里不过多赘述，不懂的看样例。

这道题可以用前缀和优化二分查找。

首先在输入时预处理前缀和，然后用二分查找前缀和数组中大于询问房间的最小前缀和位置，就是他的宿舍编号，然后用询问房间减去上一个前缀和求出第几个房间。

## 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long//不开long long见祖宗
using namespace std;
ll n,a[200010],m;
int main(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		a[i]+=a[i-1];//预处理前缀和，高效写法，只开一个数组
	}
	ll t;
	while(m--){
		scanf("%lld",&t);
		ll l=1,r=n,mid;
		//二分查找模板
		while(l<r){
			mid=(l+r)/2;
			if(a[mid]<t){
				l=mid+1;
			}else{
				r=mid;
			}
		}
		printf("%lld %lld\n",l,t-a[l-1]);//计算宿舍编号和房间编号并输出
	}
	return 0;
}
```

---

## 作者：EmptyAlien (赞：0)

# 思想

这道题让我们求某一个房间在哪个宿舍。

我们把它抽象成一个数学问题：

给定 $a$，要求对于每一个 $b_i$，满足以下式子的 $j$：

$$
\sum^{j - 1}_{k = 1} a_k < b_i - 1 \le \sum^j_{k=1}a_k
$$

这个时候我们发现，其中的 $\sum^{j - 1}_{k = 1} a_k$ 与 $\sum^j_{k = 1} a_k$ 可以利用前缀和进行优化。

于是，我们使用 $pre_i$ 来表示 $\sum^i_{j=1} a_j$。

所以我们原来的式子就变成了：

$$
pre_{j-1} < b_i - 1 \le pre_j
$$

但是我们如果暴力枚举 $j$ 的话，时间复杂度还是会爆掉。

注意到 $pre$ 是单调递增的，所以我们就可以使用二分。

即我们对于每一个 $b_i$，在 $pre$ 里面 `lower_bound` 一下，把得到的结果加一就是第一问的答案。

至于第二问，可以直接用第一问的答案算出来，肥肠简单。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
int n, m;
long long a, b, ans, pre[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        pre[i] = pre[i - 1] + a;
    }
    for (int i = 1; i <= m; i++) {
        cin >> b;
        ans = lower_bound(pre + 1, pre + n + 1, b) - pre - 1;
        cout << ans + 1 << " " << b - pre[ans] << endl;
    }
    return 0;
}
```

---

## 作者：Shadow_T (赞：0)

### 分析

此题若暴力肯定超时，那么就要用到其他算法了：二分和前缀和。

先在输入时求出前缀和，因为房间是有序的，所以用二分找到房间号，输出就可以了。

还有：不开 long long 见祖宗！

[血的教训](https://www.luogu.com.cn/record/111531918)
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+25;
int n,m,a,q[N];
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		q[i]=q[i-1]+a;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>a;//回收再利用 
		int p=lower_bound(q+1,q+n+1,a)-q;//STL万岁！！！ 
		cout<<p<<" "<<a-q[p-1]<<"\n";
	}
	return 0;
}

```

---

## 作者：As_Snow (赞：0)

#### 前置芝士：[二分](https://oi-wiki.org/basic/binary/),[前缀和](https://oi-wiki.org/basic/prefix-sum/)

#### [题目链接](https://www.luogu.com.cn/problem/CF978C)

### 思路
 $n$ 的范围是 $1\le n\le 2 \times 10^5$，因此直接暴力求解肯定会```TLE```。

因为每层楼的房间编号是连续的，我们就可以维护每一个楼层的房间编号的区间。
 $sum_i$ 表示 $a_1$ 到 $a_i$ 的和，那么第 $i$ 层楼的房间编号区间就是 $sum_{i-1}\!+\!1 \sim sum_i$。我们只用二分查找出询问的房间在哪一层楼，然后算出是第几个房间就可以了。

## Code:
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+25;
int n,m,a[N];
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",a+i),a[i]+=a[i-1];
	while(m--){
		int b;
		scanf("%lld",&b);
		int p=lower_bound(a+1,a+n+1,b)-a;
		printf("%lld %lld\n",p,b-a[p-1]);
	}
	return 0;
}
```

---

## 作者：gshgsh (赞：0)

## 题意大意
有 $n$ 个宿舍，第 $i$ 个宿舍有 $a[i]$ 个房间房间编号从第一个宿舍第一个房间开始，一个宿舍中的房间有一段连续房间编号对于每个房间编号 $b[i]$，求出它是第几个宿舍的第几个房间。

提示：不开 long long 见祖宗。
## 输入

1. 一行 $n$ , $m$ , $m$ 表示访问序列的长度。
2. 一行 每各宿舍包含的房间数 $a[i]$。
3. 一行 访问序列 $b[i]$。


## 思路

用前缀和求房间编号，然后就模拟就行了，注意超时。

## 上代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const long long M = 2e5 + 5;
long long n, m, a[M], b[M], s[M];

int main()
{
    cin >> n >> m;
    for(long long i = 1; i <= n; i++)
    {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    s[n + 1] = 1e11 + 10; //可以不加
    for(long long i = 1; i <= m; i++)
        cin >> b[i];
    long long l = 1;
    for(long long i = 1; i <= m; i++)
    {
        while(b[i] - s[l] > 0)
            l++;
        if(b[i] - s[l] == 0)
            cout << l << " " << a[l] << endl;
        else
            cout << l << " " << b[i] - s[l - 1] << endl;
    }
    return 0;
}
```


## 完美结束

**希望能过啊！**

---

## 作者：Rainbow_Sky (赞：0)

## 思路
我们首先可以了解一个 c++ 的内部函数 `lower_bound`：在一个有序序列中进行二分查找，返回指向第一个**大于等于** $x$ 的元素的位置的迭代器。如果不存在这样的元素，则返回尾迭代器。写作：
`lower_bound(v.begin(),v.end(),x)`。

就这样，本题最为麻烦查找部分就解决了，至于房间号，用当前查找的那个数减去前面房间总数即可房间。

注：前面需要与处理前缀和。

## AC code

```cpp
#include<bits/stdc++.h>
#define int long long//打代码竟如此丝滑
using namespace std;
const int MAXN=1000+10;
const int MAXM=100000+10;
const int INF=100000;
int a[MAXM],s[MAXM];
signed main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		s[i]=s[i-1]+a[i];
	}
	for(int i=1;i<=m;i++)
	{
		int x;
		cin>>x;
		int k=lower_bound(s+1,s+1+n,x)-s;
		cout<<k<<" "<<x-s[k-1]<<"\n";
	}
	return 0;
}
```

---

## 作者：Colead (赞：0)

正如其他两篇题解所言，这一题其实非常简单。

题目翻译中漏掉了十分重要的一句话：

仔细去看英文的最后一句，会发现问询以升序给出。

这样子就很简单，一路向上模拟，模拟到最后一个问询为止。

这里提供一个小小的技巧：前缀和，，这样不用再开变量记录。

具体表现为：

```
long long s[200005]={};//psq
long long a[200005]={};
……
for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		s[i]=s[i-1]+a[i];
	}
```
这样就很好操作啦！

code：

```
#include<bits/stdc++.h>
using namespace std;
long long n,m;
long long s[200005]={};//psq
long long a[200005]={};
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		s[i]=s[i-1]+a[i];
	}
	long long building=1;
	long long ask=0;
	for(int i=1;i<=m;i++)
	{
		cin>>ask;
		while(ask>s[building])
		{
			building++;
		}
		cout<<building<<" "<<ask-s[building-1]<<endl;
	}
	return 0;
}
```

祝大家AC快乐~

---

## 作者：Noby_Glds (赞：0)

话说这题怎么一会 TLE 一会 AC 呢？
### 思路：
我看到样例，我就猜想，询问的房间号是递增的吗？

结果，还真是。

那就好办了，我们用循环把 $n$ 个楼层扫一遍，$pp$ 记录当前是第几个询问，$sum$ 记录当前扫过的楼层的总房间数。

如果当前询问的房间号小于等于 $sum$，就输出此时的楼层和 
```b[pp]-sum+a[i]```
，后者为该房间在当前楼层的第几个房间。

反之，楼层加一，$sum$ 加上目前楼层的房间数。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[200010],b[200010],pp=1,sum;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	for(int i=1;i<=n;i++){
		sum+=a[i];
		while(b[pp]<=sum&&pp<=m){
			cout<<i<<" "<<b[pp]-sum+a[i]<<endl;
			pp++;
		}
	}
	return 0;
}
```
最优解的 76ms 是怎么做到的？

---


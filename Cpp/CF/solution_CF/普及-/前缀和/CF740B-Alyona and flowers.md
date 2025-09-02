# Alyona and flowers

## 题目描述

Little Alyona is celebrating Happy Birthday! Her mother has an array of $ n $ flowers. Each flower has some mood, the mood of $ i $ -th flower is $ a_{i} $ . The mood can be positive, zero or negative.

Let's define a subarray as a segment of consecutive flowers. The mother suggested some set of subarrays. Alyona wants to choose several of the subarrays suggested by her mother. After that, each of the flowers will add to the girl's happiness its mood multiplied by the number of chosen subarrays the flower is in.

For example, consider the case when the mother has $ 5 $ flowers, and their moods are equal to $ 1,-2,1,3,-4 $ . Suppose the mother suggested subarrays $ (1,-2) $ , $ (3,-4) $ , $ (1,3) $ , $ (1,-2,1,3) $ . Then if the girl chooses the third and the fourth subarrays then:

- the first flower adds $ 1·1=1 $ to the girl's happiness, because he is in one of chosen subarrays,
- the second flower adds $ (-2)·1=-2 $ , because he is in one of chosen subarrays,
- the third flower adds $ 1·2=2 $ , because he is in two of chosen subarrays,
- the fourth flower adds $ 3·2=6 $ , because he is in two of chosen subarrays,
- the fifth flower adds $ (-4)·0=0 $ , because he is in no chosen subarrays.

Thus, in total $ 1+(-2)+2+6+0=7 $ is added to the girl's happiness. Alyona wants to choose such subarrays from those suggested by the mother that the value added to her happiness would be as large as possible. Help her do this!

Alyona can choose any number of the subarrays, even $ 0 $ or all suggested by her mother.

## 说明/提示

The first example is the situation described in the statements.

In the second example Alyona should choose all subarrays.

The third example has answer $ 0 $ because Alyona can choose none of the subarrays.

## 样例 #1

### 输入

```
5 4
1 -2 1 3 -4
1 2
4 5
3 4
1 4
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4 3
1 2 3 4
1 3
2 4
1 1
```

### 输出

```
16
```

## 样例 #3

### 输入

```
2 2
-1 -2
1 1
1 2
```

### 输出

```
0
```

# 题解

## 作者：Keep_RAD (赞：3)

这一题很多人一开始都想到了暴力（因为数据范围很小，在`100`之内），虽然暴力是能过的，但是因为暴力好写，思路简单，在此不做赘述。

下面我要介绍一种更加好写，代码更少的算法------前缀和。


------------
前缀和，顾名思义，是一个数组的某项下标之前(包括此项元素)的所有数组元素的和，这种算法在求区间的题目中十分好用。比如说求$l$到$r$中所有元素的和，只需用前缀和数组中的下标为$r$减去$l-1$（之所以是$l-1$是因为$l$本身不能被减去）。

有了这种算法，代码就十分好写了。

思路：

先读入数组，边读边算前缀和，再读入`l`与`r`，计算出`l`与`r`的之间的和（用前缀和），如果大于0就加到`sum`和变量中，最后输出。（更详细解释再代码中）

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[102],he[102],sum;//用he数组表示记录前缀和,sum记录答案
int main()
{
    int n,m;
    cin>>n>>m;
    int l,r;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        he[i]=he[i-1]+a[i];//计算前缀和，he数组种第i个数表示a数组中前i个数的和，用he数组下标为i-1的和加上a[i]，算出he数组中下标为i的值
    }
    for(int i=1;i<=m;i++)
    {
        cin>>l>>r;
        if(he[r]-he[l-1]>0/*如果l到r中和大于0,注意l-1，he[l]本身不能被减去*/) sum+=he[r]-he[l-1];
    }
    cout<<sum;
    return 0;
}
```
再见！看(dian)懂(ge)即(zan)可(zan)。

求过！

---

## 作者：xgwpp6710 (赞：0)

思路很简单，就是贪心，区间之和是正的就取，否则不取。

区间之和当然可以暴力（因为数据小），但连续和会更好。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[109],s,qzh[109],n,m,r,l;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		qzh[i]=qzh[i-1]+a[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>l>>r;
		if(qzh[r]>qzh[l-1]) s+=qzh[r]-qzh[l-1];//注意是l-1！
	}
	cout<<s;
	return 0;
}
```

---

## 作者：phil071128 (赞：0)

#  CF740B 【Alyona and flowers】 题解
[题目传送门](https://www.luogu.com.cn/problem/CF740B)

给一个长度为 n 的序列，然后给 m 个区间，你可以任意选择几个区间，求所有选择中区间的和最大是多少？

你可能问：把这些区间内的数都加上这个不就是最大的吗？

怎么还要选最大的呢？慢着，有没有发现数列里有可能出现负数，如果你选择加上这个负数的话，那么是不是就会比不加要小了呢？

所以，我们需要统计出这个区间内的和，如果这个和>0就说明可以加上，如果<=0就说明不加比加上更优(或相等)

这题的正解是用前缀和来做的，但是由于数据过水的原因不用前缀和也可以AC。

非前缀和优化代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	int a[10000];
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int maxx=0;
	for(int i=1;i<=m;i++){
		int left,right;
		cin>>left>>right;
		int sum=0;
		for(int i=left;i<=right;i++){
			sum+=a[i];
		}
		if(sum>0){
			maxx+=sum;
		}
	}
	cout<<maxx; 
	return 0;
}	
```
[提交记录](https://www.luogu.com.cn/record/38764924)
用时：784ms

前缀和优化：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	int a[10000];
	a[0]=0;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		a[i]=a[i-1]+x;//前缀和，a[i]表示前i项的和 
	}
	int maxx=0;
	for(int i=1;i<=m;i++){
		int left,right;
		cin>>left>>right;
		int sum=0;
		sum+=(a[right]-a[left-1]);  //表示这个区间内的和
		if(sum>0){
			maxx+=sum;
		}
	}
	cout<<maxx; 
	return 0;
}	
```
用时：648ms

---

## 作者：dzy2008 (赞：0)

这道题目就是一个前缀和 $+$ 贪心

我们 $m$ 次询问每次询问的 $l$ 到 $r$ 区间的和只要大于 $0$，我们就去，因为不取就亏了啊

我们用一个前缀来维护序列

$a_i$ 表示 $\sum\limits_{j=1}^ia_j$ 

$l$ 到 $r$ 的和就是 $a[r] - a[l - 1]$ 啦

$AC$ 代码：

```
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
int a[10010]; 
int main()
{
	int n, m, ans = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		a[i] = a[i - 1] + x;
	}
	
	for (int i = 1; i <= m; i++) {
		int l, r;
		cin >> l >> r;
		int sum = a[r] - a[l - 1];
		if (sum > 0) { //等于0和没加一样 
			ans += sum;
		}
	}
	cout << ans;
	return 0;
}

```

---

## 作者：yxy666 (赞：0)

这道题的意思：题目给我们一个n个数的序列，然后给出m个区间（就是从L到R所有数的和），然后让我们选择任意区间，让答案最大。

思路：先构造一趟前缀和，然后判断这段前缀和是否大于0，大于0我们就取，小于0绝对不取。因为题目要求答案最大吗。也就是贪心的想法啦。

$code$ ：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,s[105]; 
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}//快读 
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)s[i]=s[i-1]+read();//构造前缀和 
	for(int i=1;i<=m;i++){
		int L=read(),R=read();
		if(s[R]-s[L-1]>0)ans+=s[R]-s[L-1];//判断这个区间的和大于0，我就取 
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 个数 $a_1,a_2,a_3,...,a_n$，给定 $m$ 个区间，你可以选择一些区间使得它们的总和最大（也可以不选），求这个最大的总和。

**数据范围：$1\leqslant n,m\leqslant 100,-100\leqslant a_i\leqslant 100$。**
## Solution
我们利用前缀和来求出每个区间的元素的和：设 $s_i$ 表示前 $i$ 个数的和，$[l,r]$ 为要表示的区间，那么这个区间的和就是 $s_r-s_{l-1}$。

然后我们将每个区间里的所有元素的和排序，然后按从大到小取，一旦取到了负数或者取完了，那我们就不取了，直接输出选的这些区间的总和。
## Code
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m, a[107], s[107], ss[107], ans;

bool cmp(int a, int b) {
	return a > b;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		s[i] = s[i - 1] + a[i];
	}
	for(int i = 1; i <= m; ++i) {
		int l, r;
		scanf("%d%d", &l, &r);
		ss[i] = s[r] - s[l - 1];
	}
	sort(ss + 1, ss + m + 1, cmp);
	for(int i = 1; i <= m; ++i) {
		if(ss[i] <= 0)	break;
		ans += ss[i];
	}
	printf("%d", ans);
}
```

---

## 作者：小恐 (赞：0)

~~这竟然是一道无人问津的题（没人写题解？）~~

~~那本蒟蒻就来写一篇题解吧（有人问津的题都轮不到我）~~

说正事：

思路灰常简单，就是对于每一段妈妈选的，和如果是正数就选，否则不选，就是这么简单。如果是每输入一个区间都一个个加的话，复杂度为$O(n+n\times m)$,稍微高了点（不过貌似能过的样子），求一个前缀和可能复杂度低一些（就是把前1个、前2个……前n个都求和），复杂度$O(n+m)$。

上代码：
```cpp
#include<stdio.h>
using namespace std;
int sum[105];//存前缀和 
int ans;//答案 
int main()
{
	int n,m;;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		int a;
		scanf("%d",&a);
		sum[i]=sum[i-1]+a;//算出前i个的前缀和 
	}
	for(int i=1;i<=m;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(sum[y]-sum[x-1]>0)//如果这个区间大于0 
			ans+=sum[y]-sum[x-1];//选它！ 
	}
	printf("%d",ans);//输出 
	return 0;
}
```
珍爱生命，远离抄袭！

---

## 作者：流绪 (赞：0)

贪心！

因为要让和最大，那么我们贪心地只选区间和大于 0 的区间就好了！

我们读入每一个区间并算他的和，如果它大于 0，就把这个和加到答案里，小于等于 0 的就舍弃掉，然后就好啦！

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
#include<cstring>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
using namespace std;
int a[maxn];
int main()
{
	ios::sync_with_stdio(false);
	int n,m;
	cin >> n >> m;
	for(int i=1;i<=n;i++)
		cin >> a[i];
	int ans = 0;
	for(int i=1;i<=m;i++)
	{
		int l,r,sum=0;
		cin >> l >> r;
		for(int j=l;j<=r;j++)
			sum +=a[j];
		if(sum > 0)
			ans += sum;
	}
	cout << ans ;
	return 0; 
}  
```


---


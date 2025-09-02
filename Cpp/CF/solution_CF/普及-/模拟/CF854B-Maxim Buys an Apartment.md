# Maxim Buys an Apartment

## 题目描述

Maxim想在大都会的莱恩大道上买一座新的公寓。这幢楼房共有 n 座公寓，从 1 到 n 编号排列在一个数列中。两座相邻公寓的编号相差为 1。有一些公寓已经被售出了，另外的一些是待售的。

Maxim时常拜访他的邻居，因此如果有一座待售公寓，其相邻公寓中至少有一座是已售出的，那么这座公寓很适合Maxim。Maxim已经知道了有 k 座公寓已被售出，但是他还不知道这些已售出公寓的编号是多少。

计算出适合Maxim的公寓数可能的最小值及最大值。

## 说明/提示

在样例中，如果编号为 1，2，3 的公寓被售出了，那么只有编号为 4 的公寓适合Maxim。如果编号为 1，3，5 的公寓被售出了，那么编号为 2，4，6 的公寓都是适合Maxim的。

Translated by @radish布団

## 样例 #1

### 输入

```
6 3
```

### 输出

```
1 3
```

# 题解

## 作者：MiRaciss (赞：3)

最小值很简单，我们只需要把所有的公寓全部挤在一起，那么供他选择的就只有一个。

如果公寓数量等于N或根本没有公寓，那么就没有他的安身之所。

对于最大值，因为一个公寓的左右两边都可以让Maxim住，所以每三个一组，每组放一个公寓，最多分成$ \frac{n}{3}$个组。

如果公寓数量大于了$ \frac{n}{3}$，则不可能分更多的组，所以满足题意的就是剩下所有的公寓。
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	long long  n,k;
	cin>>n>>k;
	if(n==k||k==0){
		printf("0 0");
		return 0;
	}
	else{
		printf("1 ");
		if(k*3<n){	
			printf("%d",2*k);
		}
		else{
			printf("%d",n-k);
		}
	}
}
```

---

## 作者：az__eg (赞：2)

div2B 是蓝题，纪念一下恶意评分，写一篇题解。

首先考虑最小能有几间宜居，我们发现从左往右连起来放过去，这样最多能影响一个房子是否宜居，显然没有更优的了。

再考虑最大能有几间宜居，我们发现可以从第二间房子被卖出开始，每隔两间房子放一间被买的，这样每个房间左右两边都被最大化利用了。

代码：

```cpp
#include<cstdio>
#define int long long
int n,k;
signed main()
{
	int i,j;
	scanf("%lld%lld",&n,&k);
	if(k==n||k==0)
	{
		printf("0 ");
	}
	else
	{
		printf("1 ");
	}
	if(k*3>=n)
	{
		printf("%lld",n-k);
	}
	else
	{
		printf("%lld",2*k);
	}
}
```


---

## 作者：Zq_water (赞：0)

**一道结论题**

先看最小值，我们可以把所有公寓放在一起，那么就有一种情况，若公寓数等于 $n$ 或者没有公寓，那么就没有情况。

再看最大值，对于每一个公寓，它的左右两边都可以住，那么我们可以把它看成三个一组，一共有 $\frac{n}{3}$ 组。若 $k<\frac{n}{3}$，那么他两边的位置就可以住，即 $2\times k$ 个，若 $k>\frac{n}{3}$，那么就有 $n-k$ 个。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k;
int main(){
	scanf("%lld %lld",&n,&k);
	if(k==0||n==k) printf("0 ");
	else printf("1 ");
	
	if(k>n/3) printf("%lld",n-k);
	else printf("%lld",2*k);	
	return 0;
}
```

---

## 作者：Butterfly___qwq (赞：0)

## 题意
给定 $n$ 和 $k$，表示 $n$ 个连续位置中已经放了 $k$ 个点。现在继续在剩余位置放点，必须与 $k$ 个点中至少一个相邻。求能放的点的数量最小值和最大值。

## 题解
最小值，除非 $k=0$ 或 $k=n$ 时为 $0$，其他情况都为 $1$。
最大值，考虑将 $k$ 个点相隔两个放置一定最优，也就是一个点能管包括本身在内的三个点，画个图就明白了。

代码:
```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int main() {
    ll n, k; scanf("%lld%lld", &n, &k);
    if (k == n || k == 0) return 0 * puts("0 0");
    return 0 * printf("1 %lld\n", k * 3 >= n ? n - k : k * 2);
}
```cpp

---

## 作者：Tomato_Ya (赞：0)

## 题意
有 $n$ 座公寓，有 $k$ 座公寓已经被售出让你求相邻公寓中有已售出公寓的待售公寓的最大值和最小值。
## 思路
#### 最小值
由于求的是相邻公寓中有已售出公寓的待售公寓的最小值，所以我们就得让待售公寓相邻的公寓中尽量没有已售出公寓，换句话说，也就是让已售出公寓尽量与待售公寓不相邻。

那我们的策略就是让每一座已售出公寓相邻，把待售公寓的位置占掉，然后让第一个或最后一个在一端。

这样最小值永远为 $1$，只有挨着最后面或最前面的那一栋待售公寓适合居住。

举个栗子，当输入为：
```cpp
8 3
```
这时公寓的排列为
![](https://cdn.luogu.com.cn/upload/image_hosting/sv1kwdie.png)
我们只能选第四座公寓，所以答案为 $1$。
#### 最大值
我们要让可以选择的公寓最多，就得让已售公寓分开，这样每座已售公寓都能让它的价值最大，让每座已售公寓的两边都适合居住。

我们一共有 $k$ 座已售公寓，我们就有 $2\times k$ 座合适的待售公寓。
![](https://cdn.luogu.com.cn/upload/image_hosting/a07rnubt.png)

但是我们可以发现一座已售公寓加上两座待售公寓组成了一组，里面包含三座公寓。所以一共有 $3\times k$ 座公寓。

这时要注意 $3\times k<n$ 的情况，如果小于的话，说明除了已售公寓外其他的待售公寓都是适合的，答案就是剩下的代售公寓的数量，也就是 $n-k$。
### 注意
$n$ 和 $k$ 是有可能相等的，如果相等，就说明公寓都卖完了，最大值和最小值都是 $0$。

$k$ 可能等于 $0$，说明公寓一座也没有卖出去， 也就没有已售公寓，所以也没有合适的公寓。
## 代码
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n, k;
int main() {
	scanf("%d%d", &n, &k);
	n == k || k == 0 ? printf("0 0") : printf("1 %d", min(2 * k, n - k));
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

感觉还是比较简单的。

首先要保证有房可买，还需要有人住在这里。

对于最小值，显然是 1，直接将所有的已售出的公寓堆到一边，然后就只有一个能买了。

然后就是最大值，考虑两个限制条件，没有足够的已售出的公寓可以提供相邻的住处位置，一种是售出的公寓太多了，没有足够的空余位置可以选择。

第一种限制条件满足 $k<\dfrac{n}{3}$，此时最大的可选择位置是 $2\times k$ 也就是每一个已售出的公寓都提供了两个，也就是最多的可选择位置。

第二个限制条件满足 $k>\dfrac{n}{3}$，此时一定存在一种方法使得每一个空闲位置都是可选的，最大可选位置数为：$n-k$。

而若 $k=\dfrac{n}{3}$，随便放到哪一种都是可以的。

------------
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,k;
int main(){
	scanf("%d%d",&n,&k);
	if(n<=k||k==0){
		printf("0 0\n");
		return 0;
	}
	printf("1 ");
	printf("%d",min(2*k,n-k));
	return 0;
}
```


---

## 作者：AC_Automation (赞：0)

### 简单的结论题（没有蓝题难度吧）
先说结论：
1. 最小值当$k=0$或$k=n$时为$0$，否则为$1$
2. 最大值在$3k>n$时为$n-k$，否则为$2k$

为什么？

1. 求最小值时让前$k$栋房屋住人，这样仅有第$k+1$栋符合条件。当$k=0$或$k=n$时，明显没有符合条件的房屋。
2. 求最大值时，让第$2,5,8\dots$栋房屋住人，这样当$3k>n$时没住人的房屋都可以被选择，答案为$n-k$，否则所有住人的房屋旁边的两栋都可以选择，答案为$2k$。

然后就是代码了（其实代码没有什么难度）
```cpp
#include<iostream>
using namespace std;
int main(){
	long long n,k;//3*k是有可能爆int的！楼上不需要是因为用的是n/3
	cin>>n>>k;
	if(n==k||k==0)cout<<0<<' ';
	else cout<<1<<' ';//最小值
	if(n<3*k)cout<<n-k<<endl;
	else cout<<2*k<<endl;//最大值
	return 0;
}

```

---

## 作者：泠小毒 (赞：0)

# Maxim Buys an Apartment
Maxim想在大都会的莱恩大道上买一座新的公寓。这幢楼房共有 n 座公寓，从 1 到 n 编号排列在一个数列中。两座相邻公寓的编号相差为 1。有一些公寓已经被售出了，另外的一些是待售的。

Maxim时常拜访他的邻居，因此如果有一座待售公寓，其相邻公寓中至少有一座是已售出的，那么这座公寓很适合Maxim。Maxim已经知道了有 k 座公寓已被售出，但是他还不知道这些已售出公寓的编号是多少。

计算出适合Maxim的公寓数可能的最小值及最大值。
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190506/)
## 解法
第一小问，不是0就是1，判断一下就可以了

第二小问，如果3k>n，那就是n-k，不然就是2k
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,ans1,ans2;
int main()
{
	scanf("%d%d",&n,&k);
	if(k&&k!=n)ans1=1;
	else ans1=0;
	m=n/3;
	if(m>=k)ans2=k*2;
	else ans2=n-k;
	printf("%d %d\n",ans1,ans2);
	return 0;
}
```

---

## 作者：hanyaxin (赞：0)

~~这题只有入门吧~~

先看最小值,如果 $n$ $=$ $k$，就是全部售出了，还有 $k$ $=$ $0$ 也就是说他无论住哪都没有邻居，那么这两种情况下最小值和最大值都是 $0$。如果两者都不满足，最小值就是 $1$，因为把所有已售出的从最左边开始排，这样就只有 $1$ 间未售出的屋子有邻居了。

再考虑最大值，我们模拟一下就可以发现从第二个屋子开始排，然后隔两个空位放一个屋子，这时候能住的屋子最多。

废话不多说看代码

```
#include <bits/stdc++.h>
using namespace std;
int n,k;
int main() 
{
	cin>>n>>k;
	if(k==0||n==k) 
	{
		cout<<"0 0"<<endl;
		return 0;
	}
	cout<<"1 ";
	if(k>n/3)
	cout<<n-k;
	else 
	cout<<2*k;
	return 0;
}
```

---


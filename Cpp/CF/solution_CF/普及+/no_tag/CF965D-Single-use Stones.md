# Single-use Stones

## 题目描述

A lot of frogs want to cross a river. A river is $ w $ units width, but frogs can only jump $ l $ units long, where $ l < w $ . Frogs can also jump on lengths shorter than $ l $ . but can't jump longer. Hopefully, there are some stones in the river to help them.

The stones are located at integer distances from the banks. There are $ a_i $ stones at the distance of $ i $ units from the bank the frogs are currently at. Each stone can only be used once by one frog, after that it drowns in the water.

What is the maximum number of frogs that can cross the river, given that then can only jump on the stones?

## 说明/提示

In the first sample two frogs can use the different stones at the distance $ 5 $ , and one frog can use the stones at the distances $ 3 $ and then $ 8 $ .

In the second sample although there are two stones at the distance $ 5 $ , that does not help. The three paths are: $ 0 \to 3 \to 6 \to 9 \to 10 $ , $ 0 \to 2 \to 5 \to 8 \to 10 $ , $ 0 \to 1 \to 4 \to 7 \to 10 $ .

## 样例 #1

### 输入

```
10 5
0 0 1 0 2 0 0 1 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10 3
1 1 1 1 2 1 1 1 1
```

### 输出

```
3
```

# 题解

## 作者：lichenfan (赞：6)

### 按每一个区间计算
如果设每一段青蛙最多跳的距离 $l$ 为一个区间，计算每个区间青蛙最多能调过的只数，就是这一段石头的个数，只要有一个区间青蛙跳不过去，那么整段就过不去了。  
也就是说，可以得知，青蛙最多跳过去的只数为其中一段区间青蛙能跳过的最少只数。   
我们用一个 $sum$ 来计算前缀和，那么这一段总共的石头就为 $sum[i+l]-sum[i]$，也就是青蛙最多可以跳过的个数。  
到这里，代码就很容易实现了。  
## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long                 
int w,l,a[100010],sum[100010],ans=999999999;                 //sum数组代表前缀和 
signed main()
{
	cin>>w>>l;
	for(int i=1;i<w;i++) cin>>a[i],sum[i]=sum[i-1]+a[i]; //计算前缀和 
	for(int i=0;i<w-l;i++) ans=min(sum[i+l]-sum[i],ans); //计算这一段青蛙能跳的距离，有几个石头够它调到下一组 
	cout<<ans;                                           //ans取最小值，因为只要有一段跳不过去，青蛙就过不去 
 } 
```

  

---

## 作者：XL4453 (赞：2)

### 解题思路：

直接取所有区间长度为 $l$ 的区间中的石头总和最小的一个就行了。

想要证明这个结论，要从两个方面来证。如果设上述的石头总和最小的区间的石头数为 $n$，那么需要分别证明没有比 $n$ 大的方案，以及 $n$ 的方案一定可行。

---
不存在更大的方案很好证明，因为每一只青蛙都不可能跳过超过 $l$，那么如果存在一个石头数为 $n$ 的区间，一定不可能有超过 $n$ 只青蛙跳过去。

---
另一方面也很简单，由于每一个其他区间的石子数都比 $n$ 要大，那么一定可以从另一个石子数不小于 $n$ 的区间跳过来。所以一定有解。

---
### 代码：
```
#include<cstdio>
#include<algorithm>
using namespace std;
int w,l,a[100005],ans;
int main(){
	scanf("%d%d",&w,&l);
	for(int i=1;i<w;i++)
	scanf("%d",&a[i]),a[i]+=a[i-1];
	ans=2147483647;
	for(int i=l;i<w;i++)
	ans=min(ans,a[i]-a[i-l]);
	printf("%d",ans);
	return 0;
}
```		

---

## 作者：Stars_visitor_tyw (赞：1)

## CF965D Single-use Stones 题解
### 思路：
我们将 $i$ 到 $i+l$ 之间有多少个石头统计并取最小值 $mini$ 即可。因为这样可以保证这 $mini$ 只青蛙不管在哪个区间都一定有石头铺路，如果不是取最小值你就不能保证是否有青蛙没有地方落脚。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int w, l, mini=1e9, sum, a[100005];
signed main()
{
    cin>>w>>l;
    for(int i=1;i<=w-1;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<l;i++)
    {
        sum+=a[i];//先统计第一个区间除了最后一项以外所有的和，方便求出区间和，不用每次都循环
    }
    for(int i=l;i<=w-1;i++)
    {
        sum+=a[i];
        mini=min(mini,sum);
        sum-=a[i-l+1];//把原区间第一项减掉
    }
    cout<<mini;
    return 0;
}

---

## 作者：xiangshengtao (赞：1)

## 题意
青蛙每次可以跳 $1\sim l$ 的距离，可以踩在非 $0$ 的地方，请问再多可以让几只青蛙过河？

## 思路
这题其实并不难，有一点思维的含量，因为它只能跳 $l$ 的距离，所以如果现在到第 $i$ 个位置，从 $i-1+l$ 到 $i$ 的石头数即为这段区间青蛙可以到的次数（即青蛙的只数），因此可以把每个长为 $l$ 的区间有多少个石头求出来，取个最小值（因为这样可以保证无论踩在哪儿都能到达终点）。

## 程序
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,i,s,mi,a[100010];
int main(){
	scanf("%d%d",&n,&l);mi=2e9;
	for (i=1;i<n;i++) scanf("%d",&a[i]);
	for (i=1;i<l;i++) s=s+a[i];
	for (i=l;i<n;i++) s=s-a[i-l]+a[i],mi=min(mi,s);//s为每个区间的和，减去第i-l个，加上第i个
	printf("%d\n",mi);
	return 0;
}
```


---

## 作者：_szs9601 (赞：1)

### 思路
因为青蛙最多只能跳 $L$ 的距离，所以假设青蛙从 $i$ 跳到 $i+L+1$ 的位置，能跳过去的青蛙数等于这个区间内的石子数之和。所以我们只需要求长度为 $L$ 的区间内的石子数之和的最小值就行了。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,ans,s,a[100100];
int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<m;i++) scanf("%d",&a[i]),s+=a[i];
	ans=2e9;
	for(i=m;i<n;i++){
		scanf("%d",&a[i]);
		s+=a[i];
		ans=min(ans,s);//求长度为m的区间最小值
		s-=a[i-m+1]; 
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

### 一、题意

给出两个正整数 $w,l$,表示河的宽度和青蛙最远跳的距离。


再给出长度为 $w-1$ 的数组 $a_i$，表示第 $i$ 点可以过多少只青蛙。

最后问总共能过多少只青蛙。

### 二、思路

我们发现，想要结果越大，一只青蛙在任意区间 $[i,i+l)$ 中，不能逗留多次，尽量只走一次。

又因为第 $i$ 块石头最多过 $a_i$ 只青蛙，那么**在这个区间里，最多只能过这个区间的 $\sum a_i$ 只青蛙**。

再由此得出，最后的结果就是所有区间最小的可过青蛙数。

至此，代码呼之欲出。

### 三、代码

还算挺清爽的。

```cpp
#include <stdio.h>
const int maxn=100005;
int w,l,len,i,ans=1<<30;
//w,l同题面。
//len即区间个数
//i为循环变量
//ans为结果，要求min
int a[maxn],s[maxn];
//a[]同题面
//s[]是前缀和数组
int main(){
	scanf("%d %d",&w,&l);
	for(i=1;i<w;++i){
		scanf("%d",&a[i]);//读入a[i]
		s[i]=s[i-1]+a[i]; //求前缀和数组
	}
	len=w-l;//求区间个数
	for(i=0;i<len;++i)
		if(s[i+l]-s[i]<ans)
			ans=s[i+l]-s[i];//求结果，s[i+l]-s[i]就是该区间a[i]之和
	printf("%d",ans);//输出
	return 0;
}
```

---

## 作者：_Clown_ (赞：0)

# D.Single-use Stones
$\mathtt{Difficulty}$=$\mathtt{1900}$

先说结论：
> 最多通过的青蛙的数量就是每个长度为 $l$ 的区间中石头数量的最小值。

我们考虑一段长度为 $l$ 的区间，

因为青蛙最多跳 $l$ 的距离，

不难想到，每只青蛙都一定会在这个区间落下至少一次。

因为一定可以从另一个石子数大于等于 $n$ 的区间跳过来，

所以这样取出的答案是可行的。

那么我们就得到了结论：
> 最多通过的青蛙的数量就是每个长度为 $l$ 的区间中石头数量的最小值。

代码就不难写出了。
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int W,L,A[100001],Prefix[100001];
int main(void)
{
	BetterIO;
	register int i;cin>>W>>L;
	for(i=1;i<W;i++)cin>>A[i];
	for(i=1;i<W;i++)Prefix[i]=Prefix[i-1]+A[i];
	register int Ret(INT_MAX);
	for(i=0;i+L<W;i++)Ret=min(Ret,Prefix[i+L]-Prefix[i]);
	cout<<Ret<<endl;
	return 0;
}
```

---


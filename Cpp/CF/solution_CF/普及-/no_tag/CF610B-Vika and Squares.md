# Vika and Squares

## 题目描述

Vika 有 $n$ 桶油漆，第 $i$ 桶有 $a_i$ 升油漆。

Vika 有一张无限长的长方形纸条，她将长方形纸条分成了无限个正方形，她将按照以下规则对正方形涂色。

- 涂一个正方形需要 $1$ 升油漆。
- 第一个正方形可以用第任意第 $i$ 桶油漆。
- 若第 $k$ 个正方形用了第 $x$ 桶油漆，则第 $k+1$ 个正方形将用第 $x+1$ 桶油漆，若 $x=n$，则第 $k+1$ 个正方形将用第 $1$ 桶油漆。若 $a_x = 0$ 则停止涂色。

求 Vika 最多可以涂多少个正方形。

## 样例 #1

### 输入

```
5
2 4 2 3 3
```

### 输出

```
12
```

## 样例 #2

### 输入

```
3
5 5 5
```

### 输出

```
15
```

## 样例 #3

### 输入

```
6
10 10 10 1 10 10
```

### 输出

```
11
```

# 题解

## 作者：流绪 (赞：2)

贪心！

我们算出每种颜色的最少数量 minn，所以我们就可以涂 minn 遍颜色，然后我们可以选择起始颜色，让我们涂的长度尽量长。

首先我们一定可以涂 minn*n 格,因为颜色最少的都够用 minn 次，接下来我们可以选择起点，然后让答案再加上几格。我们可以发现总格数等于起点到从起点开始的第一个最小数量颜色的距离，加上循环的格数。所以我们贪心地让起点到从起点开始的第一个最小数量颜色的距离最大。换一种说法就是找到两个最小数量颜色之间距离最大的地方，然后让起点位于这段的第一格，然后就大功告成啦！

注意样例三,因为是循环着涂的,把样例三展开：

10 10 10 1 10 10,10 10 10 1 10 10

此时最大间隔应该是 5，要注意这种情况！

下面是 AC 代码，细节注释在代码里了。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
using namespace std;
ll a[maxn];
int main()
{
	ios::sync_with_stdio(false);
	ll n;
	cin >> n;
	ll minn = inf,p=0;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i];
		minn = min(minn,a[i]);//找到最小数量的颜色
	}
	int p1=0,p2=0;//记录第一个和最后一个最小数量的颜色
	for(int i=1;i<=n;i++)
	{
		if(a[i] == minn)
		{
			if(!p1)
				p1=i;
			p2=i;
			ll j=i+1;
			while(a[j]!=minn&&j<n)
				j++; //记录间隔
			p = max(p,j-i-1);更新最大间隔
			i=j-1;
		}
	}
	p=max(n-p2+p1-1,p);更新特殊情况的间隔
	cout << minn*n+p;
	return 0; 
}  
```


---

## 作者：sqh_let_it_be (赞：1)

# 思路：

一句话总结：让两桶最少的油漆距离尽可能的远。

我们将原来 $a$ 的序列在后面复制一份，这样所有的情况就会在一个数组里呈现出来，例如样例 1：
```
5
2 4 2 3 3
```
将 $a$ 数组复制一份得：
```
2 4 2 3 3 2 4 2 3 3
```
这样最优解就会是：
```
2 4 2 | 3 3 2 4 2 | 3 3
```

我们把 $a$ 数组中最小的数，记作 $minn$。然后遍历一遍复制后的 $a$ 数组中两个最小值之间的间隔最大值，记作 $maxn$。

那我们就可以找到规律：
1. Vika 最少可以涂 $n \times minn$ 个正方形；
2. 最优解一定是 $n \times minn+maxn$。

那么就得出，最后答案是 $n \times minn+maxn$。

当然，如果 $a$ 数组中数据相同时，答案为 $n \times minn$。

### AC 代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
long long int n,a[400005],minn=1e9+9,sum;
bool xt=true;
inline long long int read()
{
	long long int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-48;ch=getchar();}
	return s*w;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		if(i!=1)
		{
			if(a[i]!=a[i-1])
			  xt=false;
		}
		minn=min(a[i],minn);
	}
	if(xt==true)
	{
		cout<<n*minn;
		return 0;
	}
	sum+=n*minn;
	for(int i=n+1;i<=2*n;i++)
	  	a[i]=a[i-n];
	int l=-1,maxn=-1;
	for(int i=1;i<=2*n;i++)
	{
		if(a[i]==minn)
		{
			if(l==-1)
				l=i;
			else
			{
				maxn=max(i-l-1,maxn);
				l=i;
			}
		}
	}
	cout<<sum+maxn;
}
```

---

## 作者：一只大龙猫 (赞：1)

题目翻译：

你有 $n$ 桶油漆，每一桶可以画 $a_i$ 个正方形。在你用了第 $i$ 桶油漆画了一个正方形之后，你必须接着使用第 $i+1$ 桶油漆去画正方形（如果 $i=n$，则下一次使用第 $1$ 桶油漆。）你可以任意选择一桶油漆开始画正方形，求你最多可以画多少个正方形。


首先，我们设 $minn$ 为 $\min \limits_{1 \le i \le n}a_i $ 。

因为所以的油漆都能画 $minn$ 个正方形，所以我们最少也总共可以画 $minn \times n$ 个正方形。但是如果我们选择合适的起点的话，那么可以画出更多正方形，不妨设最多可以再多画 $sum$ 个。

我们可以想象一下，当我们画完 $minn \times n$ 个正方形之后，所有的只能画 $minn$ 个正方形的油漆都已经用完了，我们如果想要画出更多正方形，就只能看那些能画多于 $minn$ 个正方形的油漆，$sum$ 自然就是其中的最长的连续区间的长度。

也就是说，我们要找的就是**最长的连续区间，使得其中的每一个 $a_i$ 都大于 $minn$**。$sum$ 就是这段区间的长度。

注意：在这里，$a_n$ 和 $a_1$ 也是相连的。

怎么求出这段区间的长度（就是 $sum$）的值呢？

我们可以换个角度思考：既然这段区间中的每一个 $a_i$ 都大于 $minn$，那么，这段区间的两头肯定就是 $minn$。那么，只要我们枚举每一个 $a_i$，如果它等于 $minn$，就计算它与上一个 $minn$ 之间的距离，如果比当前的 $sum$ 大，就更新 $sum$，这样就能求出 $sum$ 的值了。

代码如下。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long sum=-18e16,n,a[200001],minn=18e16,last;
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(a[i]<=minn){
			minn=a[i];
			last=i;
		}
	}                          
	for(int i=1;i<=n;i++){
		if(a[i]==minn){
			if(last>=i){
				sum=max(sum,(n-last)+(i-1));
			}else{
				sum=max(sum,i-last-1);
			}
			last=i;
		}
	}
	printf("%lld",sum+minn*n);
	return 0;
}
```

代码中，变量 $last$ 指的是目前遍历到的最后一个 $minn$ 的位置。每次遍历到一个新的 $minn$，都要更新一下 $last$ 的值。

```cpp
if(last>=i){
	sum=max(sum,(n-last)+(i-1));
}else{
	sum=max(sum,i-last-1);
}
```

所求的就是以 $a_{i-1}$ 为结尾的区间的长度。

如果 $last \geq i$，意味着这一段区间为 
$$a_{last+1},a_{last+2},...,a_n,a_1,a_2,...,a_{
i-2},a_{i-1}$$

长度为 $[last+1,n]$ 的长度与 $[1,i-1]$ 的长度之和，即 $(n-last)+(i-1)$。

如果 $last < i$，意味着这一段区间为

$$a_{last+1},a_{last+2},...a_{i-2},a_{i-1}$$

长度为 $[last+1,i-1]$ 的长度，即 $i-last-1$。

---

## 作者：zgy_123 (赞：0)

算上这题，就是我的第 $20$ 道 CF 的 AC了，于是就写一篇题解。

题面十分好理解，所以直接开始讲解。

首先不难发现，对于 $1\le i\le n,a_i\ge1$ 每涂 $n$ 个正方形，所有 $a_i$ 均会减 $1$。

所以可推断出，答案为 $n\times \min\{a_i\}+x$。

那么，$x$ 是多少？

要解决这个问题，必须知道 $x$ 是由什么决定的。

我们以样例 $1$ 举例，将每个数都减少 $2$ 后变为：
```
0 2 0 1 1
```
对于这个样例，应该从第 $4$ 位开始，直到遇到 $0$，$x=2$。

那么，该怎么判断从哪开始呢？

```
0 1 1 1 0 -> 2~4 -> x=3
```
```
0 0 1 1 1 -> 3~5 -> x=3
```
```
1 0 0 1 1 -> 3~1 -> x=3
```
举过这几个例子后，我们可以发现，$x$ 就是非 0 子串的最大长度！

于是可以想到如下方法：

先读入 $n$ 和 $a$，找最小值 `minn`，并在后面复制一次：
```cpp
cin>>n;
for(int i=1;i<=n;i++){
	cin>>a[i];
	a[n+i]=a[i];
	minn=min(minn,a[i]);
}
```
然后求出 $x$：
```cpp
for(int i=1;i<=2*n;i++)
	if(a[i]==minn){
		x=max(x,cnt);
		cnt=0;
	}
	else cnt++;
x=max(x,cnt);
```
最后输出：
```cpp
cout<<minn*n+x;
```
附上我的 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a[400005];
int main(){
	ll n,minn=2e9,x=-1,cnt=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[n+i]=a[i];
		minn=min(minn,a[i]);
	}
	for(int i=1;i<=2*n;i++)
		if(a[i]==minn){
			x=max(x,cnt);
			cnt=0;
		}
		else cnt++;
	x=max(x,cnt);
	cout<<minn*n+x;
	return 0;
}
```
提示 & 提醒：
- 变量要初始化！
- $a$ 数组要开两倍！
- 不开 `long long` 一场空！
- 不要抄袭！

---

## 作者：Keroshi (赞：0)

# 题目分析
先看题目第三组样例。
![](https://cdn.luogu.com.cn/upload/image_hosting/xv1zbj13.png)  
其中，停止涂色是当正方形为 $0$，那么涂色的周期就是数组的最小值。   
题目需要涂到更多的油漆。由于停止涂色后的正方体将不再涂色，那么就从最小值后面一项开始涂色，这样就能涂到尽可能多的正方形。   
如果给出的数组中有多个相同的最小值，选择哪一个最小值后面开始涂色很关键。不难想到只要选择的两个最小值的间隔越大，涂色次数也就更多，于是找间隔最大的两个最小值中的前一个开始图色。
# 注意事项 
1. 由于题目是一个环，需要延长两倍数组。   
2. $a_i \cdot n$ 超过了 int 范围，要开 long long。
# 参考代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=4e5+5;
const ll INF=2e9;
ll n,a[N],minn=INF,res,l,r,cnt,f;
int main(){
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++) {
        scanf("%lld",&a[i]);
        minn=min(minn,a[i]);
        a[n+i]=a[i];
    }
    for(ll i=1;i<=n;i++) res+=(a[i]==minn);
    if(res==1) {
        printf("%lld",n*(minn+1)-1);
        return 0;
    }
    for(ll i=1;i<=2*n;i++){
        if(a[i]==minn) {
            if(f==0) f=1;
                else cnt=max(cnt,i-l+1);
                l=i;
            }
        }
    }
    printf("%lld",(minn+1)*(cnt-2)+minn*(n-cnt+2));
    return 0;
}
```

---

## 作者：s_c_lmlm_L (赞：0)

 贪心思想，解题三部曲


## $Step$ $1$ 《取最小值》
 取 $n$ 桶油漆中的最小值 $a_i=x$ 

由于最小值存在多个，可以有任意最小值 $a_j$ 且 $a_j=a_i$ ,即
$$a_i=a_j$$  
$$x=a_i$$ 

## $Step$ $2$ 《取离 $x$ 最远的桶 $y$ 》
 找到离最小值 $x$ 最近的桶 $y$ 作为我们涂色的起点。

“若第 $k$ 个正方形用了第 $x$ 桶油漆，则第 $k+1$ 个正方形将用第 $x+1$ 桶油漆，若 $x=n$ ，则第 $k+1$ 个正方形将用第  $1$ 桶油漆”

如上我们可以得出一个狠重要的信息！——我们是从左往右使用油桶。

由此我们贪心思想初步形成！——我们的起点 $y$ 要尽可能地离 $x$ 远，且是从左往右尽可能的远

然而…我们该怎么找离 $x$ 最远的点呢？
其实很简单，只要找到 $a_{i+1}$ ，什么意思呢，假设 $x$ 下标为 $1$ 。即：
$$x=a_1$$
$$y=a_2$$
$OK$，现在我们已经知道了涂色的起点 $y$ 了，可以开始列公式了！

## $Step$ $3$ 《列公式》
其实 ~~高级的~~ 公式往往只需要观察就可以得出，通过样例就可以得出

接下来直接为大家列出公式。设最多涂色数量为 $m$，$x$ 下标为 $i$ ，$y$ 下标为 $j$

$$m=x\cdot n+n+i-j$$

可以简化为
$$m=(x+1)\cdot n-1$$
 我们就以样例 3 为例吧。

 输入：
```
6
10 10 10 1 10 10
```
通过上述 $Step1$ 我们得出 $x=1$ 即 $a_4$，$i=4$

再通过 $Step2$ 我们得出 $y=a_5$，$j=5$

$$m=(1+1)\cdot6-1=11$$

 咻~终于写完啦


---


# Sereja and Coat Rack

## 题目描述

Sereja owns a restaurant for $ n $ people. The restaurant hall has a coat rack with $ n $ hooks. Each restaurant visitor can use a hook to hang his clothes on it. Using the $ i $ -th hook costs $ a_{i} $ rubles. Only one person can hang clothes on one hook.

Tonight Sereja expects $ m $ guests in the restaurant. Naturally, each guest wants to hang his clothes on an available hook with minimum price (if there are multiple such hooks, he chooses any of them). However if the moment a guest arrives the rack has no available hooks, Sereja must pay a $ d $ ruble fine to the guest.

Help Sereja find out the profit in rubles (possibly negative) that he will get tonight. You can assume that before the guests arrive, all hooks on the rack are available, all guests come at different time, nobody besides the $ m $ guests is visiting Sereja's restaurant tonight.

## 说明/提示

In the first test both hooks will be used, so Sereja gets $ 1+2=3 $ rubles.

In the second test both hooks will be used but Sereja pays a fine $ 8 $ times, so the answer is $ 3-8=-5 $ .

## 样例 #1

### 输入

```
2 1
2 1
2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 1
2 1
10
```

### 输出

```
-5
```

# 题解

## 作者：Halberd_Cease (赞：1)

我们考虑 $2$ 种情况：

1. $n\le m$ 这时衣架肯定用完，所有收益可以加满，赔的钱就是 $(m-n)\times d$；
2. $n>m$ 顾客从便宜到贵拿，排序后从 $1$ 开始加即刻。

Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[110];
int n,d,m;
int total;
main()
{
    cin>>n>>d;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        total+=a[i];
    }
    cin>>m; 
    if(m>=n)
    {
        cout<<total-(m-n)*d;
        return 0;
    }
    total=0;
    sort(a+1,a+n+1);
    for(int i=1;i<=m;i++)
    {
        total+=a[i];
    }
    cout<<total;
}
```

---

## 作者：WilliamFranklin (赞：1)

~~又找到了一个可以写题解的。~~
## 主要思路
首先，将数列排序。

再判断一下 $m$ 和 $n$ 的关系：

- 如果 $m$ 等于 $n$，那么直接输出整个数列之和即可。
- 如果 $m$ 小于 $n$，那么就输出这个数列前 $m$ 项之和即可。
- 如果 $m$ 大于 $n$，那么就输出整个数列之和加上 $d$ 乘 $(m-n)$ 即可。

为了方便，我们其实可以先将整个数列之和求出，这样第一种情况直接输出即可，第二种情况直接输出整个数列之和减去第 $m + 1$ 项到第 $n$ 项的和即可，第三种情况就像如上所说一样即可。

好啦，废话不多说，上代码。
### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105];
int main() {
	int n, d, m, ans = 0;
	cin >> n >> d;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		ans += a[i];
	}
	cin >> m;
	sort(a + 1, a + n + 1);
	if (m == n) {
		cout << ans;
	} else if (m < n) {
		int sum = 0;
		for (int j = n; j > m; j--) {
			sum += a[j];
		}
		cout << ans - sum;
	} else {
		cout << ans - (m - n) * d;
	}
	return 0;
} 
```


---

## 作者：chenjingfei (赞：1)

[CF368A传送门](https://www.luogu.com.cn/problem/CF215A)



看了看其他大佬都是用贪心，让我这个蒟蒻来用个分类讨论吧。

## 大致题意

旅店一共有 $n$ 个衣架，有 $m$ 个客人，每个客人来会选最便宜的衣架挂衣，旅店获得相应的钱，但是衣架不够的情况下要给每个客人赔款 $p$ 元。

## 大体思路

先排序，然后再分类讨论。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,m,sum,s;
int a[10000];
int main()
{    
    while(~scanf("%d%d",&n,&d))
    {
        memset(a,0,sizeof(a));
        for(int i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            s+=a[i];
        }
        sort(a,a+n);//来个排序
        scanf("%d",&m);
        if(m==n)printf("%d\n",s);
        else if(m>n)
        {
            s-=(m-n)*d;
            printf("%d\n",s);
        }
        else if(m<n)
        {
            sum=0;
            for(int i=0;i<m;i++)sum+=a[i];
            printf("%d\n",sum);
        }
    }
    return 0;
}
```

---

## 作者：NATO (赞：0)

### 题目分析：

先将挂钩价格排序，再按照题意从小到大统计答案和，分两种情况。

1.若 $m≤n$ 将排序后的 $a_1,a_2,a_3,...,a_m$ 累加即可。
2.若 $m>n$ 将排序后的 $a_1,a_2,a_3,...,a_n$ 累加后减去 $(m-n)\times d$（翻译似乎翻译错了，英文题面中是 $d$ 而不是 $p$）即可。

#### 参考代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m;
ll p,a[105],ans,jl;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>p;
	
	for(ll i=1;i<=n;++i)
		cin>>a[i];cin>>m;
	sort(a+1,a+1+n);
	for(ll i=1;i<=n&&i<=m;++i)
	{
		ans+=a[i];jl=i;
	}
	if(jl==m)
		cout<<ans;
	else
		cout<<ans-(m-n)*p;
}
```


---

## 作者：Firstly (赞：0)

## **题目思路：**
------------
因为客人们想要优先挑便宜的钩子挂衣服以达到省钱的目的，所以我们先要把钩子的价格从小到大排好序。

然后我们可以用一个数组，记录当已经挂到一个钩子时，此时老板一共能收的钱。（类似于前缀和）

当客人数量不超过钩子数量的时候，老板不需要赔钱。此时老板赚的钱是相当于客人数量的钩子所需要的钱的总和；当客人数量超过钩子数量的时候，老板赚的钱是所有钩子需要钱的总和减去没挂到衣服的客人们的数量与需要赔给每个人的钱的积。

分析完毕。本题代码如下：

## **Code：**
------------
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,d,m,a[105],f[105];
int main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++)cin>>a[i];
	cin>>m;
	sort(a+1,a+n+1);//将数组排好序
	for(int i=1;i<=n;i++)f[i]=f[i-1]+a[i];//这步类似于前缀和
	if(m>n)cout<<f[n]-(m-n)*d;
	else cout<<f[m];
	return 0;
}
```


---

## 作者：fox_nice (赞：0)

~~不知道水多少篇题解了~~

**大致题意：**

$m$ 个客人来一家饭店吃饭，一共有 $n$ 个钩子给客人挂衣服，第 $i$ 个钩子要 $a_i$ 元钱，客人们会选择最便宜的钩子挂衣服，如果客人来了没有钩子，老板就要给客人 $d$ 元钱，问老板能赚多少。

**分析：**

大致看一看题意和数据范围。

第一个想到的就是贪心。因为客人会先选择便宜的钩子挂，首先要排序。

其次是处理赔给客人钱的事。

进行讨论：

如果钩子够，那就不用赔钱了；

但如果钩子不够，就要交 $d$ 元，很明显总共要赔 $(m-n) \times d$ 元钱。

然后赚的钱减去赔的钱就是最终答案。

分析完毕，上代码。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[105];
int main(){
    int n,d;
    cin >>n>>d;
    for(int i=0;i<n;i++){
        cin >>a[i];
    }
    sort(a,a+n);
    int ans=0;
    int m;
    cin >>m;
    for(int i=0;i<m;i++){
        if(i>=n){
            ans-=d;
        }else{
            ans+=a[i];
        }\\判断是赔钱还是赚钱
    }
    cout<<ans<<endl;
}
```


---

## 作者：小杨小小杨 (赞：0)

## 题意
给你许多钩子，每一个钩子都有价钱，有 $h$ 个顾客，每一个顾客都会把自己的衣服挂在最便宜的钩子上，若没有了钩子，就要亏损 $m$ 元，不然就会得到当前最便宜的空钩子的价值元。
## 思路
排序，贪心。应为顾客每一次都会取最便宜的钩子，那么就会一个个由小到大地取最便宜的、第二便宜的、第三便宜的……直到第 $min(n,h)$ 的钩子,如果还有剩下的人，那么剩下的人就只能每一个人都赔 $m$ 元了，不然就是这样，直接输出即可。故，对钩子排序后进行如上的模拟即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,i,a[100001],h,k;
int main(){
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);//排序，从小到大
	scanf("%d",&h);
	k=min(n,h);//取最小，看看取完了还是没取完
	for (i=1;i<=k;i++) ans+=a[i];//累加能赚的钱
	for (i=k+1;i<=h;i++) ans-=m;//剩下的只能赔钱
	printf("%d\n",ans);//输出
	return 0;
}
```


---

## 作者：RainFestival (赞：0)

$\texttt{codeforces}$ 难度评定 $1000$。


先对每一个 $a_i$ 进行排序。

然后取前 $\min(n,m)$ 个。

剩下的只能赔偿，所以赔偿 $d\times max(m-n,0)$。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
int n,d,m,s,a[105];
int main()
{
	scanf("%d%d",&n,&d);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	std::sort(a+1,a+n+1);
	scanf("%d",&m);
	for (int i=1;i<=std::min(n,m);i++) s=s+a[i];
	s=s-d*std::max(m-n,0);
	printf("%d\n",s);
	return 0; 
}
```

---


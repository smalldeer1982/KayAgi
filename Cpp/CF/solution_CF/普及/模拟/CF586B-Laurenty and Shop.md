# Laurenty and Shop

## 题目描述

A little boy Laurenty has been playing his favourite game Nota for quite a while and is now very hungry. The boy wants to make sausage and cheese sandwiches, but first, he needs to buy a sausage and some cheese.

The town where Laurenty lives in is not large. The houses in it are located in two rows, $ n $ houses in each row. Laurenty lives in the very last house of the second row. The only shop in town is placed in the first house of the first row.

The first and second rows are separated with the main avenue of the city. The adjacent houses of one row are separated by streets.

Each crosswalk of a street or an avenue has some traffic lights. In order to cross the street, you need to press a button on the traffic light, wait for a while for the green light and cross the street. Different traffic lights can have different waiting time.

The traffic light on the crosswalk from the $ j $ -th house of the $ i $ -th row to the $ (j+1) $ -th house of the same row has waiting time equal to $ a_{ij} $ ( $ 1<=i<=2,1<=j<=n-1 $ ). For the traffic light on the crossing from the $ j $ -th house of one row to the $ j $ -th house of another row the waiting time equals $ b_{j} $ ( $ 1<=j<=n $ ). The city doesn't have any other crossings.

The boy wants to get to the store, buy the products and go back. The main avenue of the city is wide enough, so the boy wants to cross it exactly once on the way to the store and exactly once on the way back home. The boy would get bored if he had to walk the same way again, so he wants the way home to be different from the way to the store in at least one crossing.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF586B/04e19dedf810ee5c633b66631501e6fe5923174b.png)Figure to the first sample.Help Laurenty determine the minimum total time he needs to wait at the crossroads.

## 说明/提示

The first sample is shown on the figure above.

In the second sample, Laurenty's path can look as follows:

- Laurenty crosses the avenue, the waiting time is $ 3 $ ;
- Laurenty uses the second crossing in the first row, the waiting time is $ 2 $ ;
- Laurenty uses the first crossing in the first row, the waiting time is $ 1 $ ;
- Laurenty uses the first crossing in the first row, the waiting time is $ 1 $ ;
- Laurenty crosses the avenue, the waiting time is $ 1 $ ;
- Laurenty uses the second crossing in the second row, the waiting time is $ 3 $ .

 In total we get that the answer equals $ 11 $ .In the last sample Laurenty visits all the crossings, so the answer is $ 4 $ .

## 样例 #1

### 输入

```
4
1 2 3
3 2 1
3 2 2 3
```

### 输出

```
12
```

## 样例 #2

### 输入

```
3
1 2
3 3
2 1 3
```

### 输出

```
11
```

## 样例 #3

### 输入

```
2
1
1
1 1
```

### 输出

```
4
```

# 题解

## 作者：Starmoon_dhw (赞：1)

# Solution1
本题数据范围较小，$n$ 最多只有 $50$，所以可以直接暴力枚举，简单省事。

可以使用同一个数组，因为红绿灯是双向的，所以无需考虑过去和回来直接枚举,然后把最快的两条路径求和即可。

可以建立一个数组 $a$ 用来保存各个路径所耗费的时间，数组中应有 $n$ 个元素。

首先，给每条路径都加上中间路耗费的时间。

然后枚举路径，因为不能往回走，所以，如果你上面走到了 $i$ 那么你下面就需要从 $i$ 开始枚举。

枚举好之后，只需要找到耗费时间最少的两条路径，然后把他们的耗费时间加起来即可。

核心代码:
```cpp
for(int i=1;i<=n;i++)
	{
        k[i]=b[i];//b是中间的路
		for(int j=1;j<=i-1;j++)
			 k[i]+=a[1][j];//上面的路 
        for(int j=i;j<=n-1;j++)//别从1开始啦！
			 k[i]+=a[2][j];//下面的路
        
    }
```
# Solution2

第二种思路是最短路！

我这边给大家提供一种存路线的方案。
```cpp

	for(int i=0;i<=1;i++)
		for(int j=2;j<=n;j++)
			cin>>a[i*n+j-1][i*n+j];
	for(int i=1;i<=n;i++)
		cin>>a[i][i+n]
```
存好图后，其实就是普通的最短路，但是这道题目因为有的地方走过后就不能再走了，所以需要记录最短路线，并删去，十分麻烦，所以还是推荐上述方法。

---

## 作者：Eason_cyx (赞：0)

简单题。

容易发现，这个红绿灯是双向的，所以求出一条家到超市的路，等价于从超市到家的路。

由于只能经过一次主街道，我们枚举过主街道的位置，记为 $i$；那么等待时间就分成：从第 $2$ 排第 $n$ 列（家）到第 $2$ 排第 $n$ 列，过主街道，从第 $1$ 排第 $i$ 列到第 $2$ 排第 $n$ 列（超市）这三部分。分开枚举计算就可以了。

最后，将所有这些时间记录在一个数组中，因为往返不能走同一条路，所以输出最小值与次小值的和即可。

时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[5][55],b[55],dis[55];
int main() {
    int n; cin >> n;
    for(int i = 1;i <= 2;i++) {
        for(int j = 1;j < n;j++) {
            cin >> a[i][j];
        }
    }
    for(int i = 1;i <= n;i++) cin >> b[i];
    for(int i = n;i >= 1;i--) {
        dis[i] = b[i];
        for(int j = n-1;j >= i;j--) dis[i] += a[2][j];
        for(int j = i-1;j >= 1;j--) dis[i] += a[1][j];
    }
    sort(dis+1,dis+n+1);
    cout << dis[1] + dis[2] << endl;
    return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
前缀和和后缀和的简单应用。
## 分析。
首先本题要求找到两条路径，这两条路径除了起点和终点外不能重合，那么我们不妨给它们两拆开然后单独去算。一个显然的思路就是对整个网格进行搜索，然后标记每一个走过的地方，去找最短路。但是我们注意到 $n$ 的数据范围极小，我们可以直接进行暴力枚举。注意到穿过中间的大道只有一次，所以一共只有大道次的方案数，直接在它们中间枚举，用前缀和和后缀和分别进行统计，然后加上通过大道的时间，取两个较小的值即可，复杂度完全过得去。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,a[55],b[55],main_r[55];
int sum,ans=0x3f3f3f3f;
int main(){
	cin>>n;
	for (int i=2;i<=n;i++){
		cin>>a[i];
		a[i]=a[i]+a[i-1];
	}
	for (int i=1;i<=n-1;i++){
		cin>>b[i];
	}
	for (int i=n-1;i>=1;i--){
		b[i]=b[i+1]+b[i];
	}
	//我们可以直接用题目中的输入来做前后缀合。 
	for (int i=1;i<=n;i++){
		cin>>main_r[i];
	}
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			if(i==j){
			    continue;
			}
			sum=a[i]+main_r[i]+b[i];
			sum+=a[j]+main_r[j]+b[j];
			ans=min(sum,ans);
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```
## 后记。
这道题本来想找最短路和次小路的，但是开数组时才发现不需要，要加训了。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：_Rainlzy (赞：0)

大致题意就是 Laurenty 想要从右下角的地方走到左上角，再走回来，每条路都需要等待一段时间，每次走只能走中间的马路，而且不能重复走一条路。

这道题数据范围才 $2 \leq n \leq 50$，数据这么小，直接暴力枚举。

用前缀和和后缀和，再加上等待的时间，比较一下哪个更小，就是正解。

```c++
#include<bits/stdc++.h>
using namespace std;
int n,a[55],b[55],f[55],ans=INT_MAX,minn=0;
int main(){
	a[1]=0,b[1]=0;
    cin>>n;
    for(int i=2;i<=n;i++){
    	cin>>a[i];
    	a[i]=a[i]+a[i-1];
    }
    for(int i=1;i<=n-1;i++)
    	cin>>b[i];
    for(int i=n-1;i>=1;i--)
    	b[i]=b[i+1]+b[i];
    for(int i=1;i<=n;i++)
    	cin>>f[i];
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=n;j++){
    		if(i==j)
				continue;
    		minn=a[i]+f[i]+b[i];
    		minn+=a[j]+f[j]+b[j];
    		ans=min(minn,ans);
    	}
    cout<<ans<<endl;
    return 0;
}
```



---


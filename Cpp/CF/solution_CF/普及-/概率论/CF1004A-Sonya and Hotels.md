# Sonya and Hotels

## 题目描述

Sonya decided that having her own hotel business is the best way of earning money because she can profit and rest wherever she wants.

The country where Sonya lives is an endless line. There is a city in each integer coordinate on this line. She has $ n $ hotels, where the $ i $ -th hotel is located in the city with coordinate $ x_i $ . Sonya is a smart girl, so she does not open two or more hotels in the same city.

Sonya understands that her business needs to be expanded by opening new hotels, so she decides to build one more. She wants to make the minimum distance from this hotel to all others to be equal to $ d $ . The girl understands that there are many possible locations to construct such a hotel. Thus she wants to know the number of possible coordinates of the cities where she can build a new hotel.

Because Sonya is lounging in a jacuzzi in one of her hotels, she is asking you to find the number of cities where she can build a new hotel so that the minimum distance from the original $ n $ hotels to the new one is equal to $ d $ .

## 说明/提示

In the first example, there are $ 6 $ possible cities where Sonya can build a hotel. These cities have coordinates $ -6 $ , $ 5 $ , $ 6 $ , $ 12 $ , $ 13 $ , and $ 19 $ .

In the second example, there are $ 5 $ possible cities where Sonya can build a hotel. These cities have coordinates $ 2 $ , $ 6 $ , $ 13 $ , $ 16 $ , and $ 21 $ .

## 样例 #1

### 输入

```
4 3
-3 2 9 16
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5 2
4 8 11 18 19
```

### 输出

```
5
```

# 题解

## 作者：Node_Edge (赞：3)

这题考察模拟和枚举，我们可以遍历每个旅馆的距离，分三种情况：

---

第一种：$2 \times d<x_{i+1}-x_i$

即 
![](https://cdn.luogu.com.cn/upload/image_hosting/1t94vwl4.png)

从图得知，点 A 和点 B 之间可以有两个旅馆。

----

第二种：$2 \times d=x_{i+1}-x_i$

即
![](https://cdn.luogu.com.cn/upload/image_hosting/fzsz2pif.png)

从图得知，点 A 和点 B 之间可以有两个旅馆重合，所以只有一个旅馆。

---

第三种：$2 \times d>x_{i+1}-x_i$

即
![](https://cdn.luogu.com.cn/upload/image_hosting/xtlj9tg0.png)

从图得知，相比之下 a 旅馆 离点 B 更近，b 旅馆 离点 A 更近，所以都不成立，中间不可放置旅馆。

---

**注意：**

由于在 $x_1$ 的左边和 $x_n$ 的右边都可放置旅馆，所以初始值应该是 $2$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,cnt=2;
int a[105];
int main(){
    cin>>n>>d;
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n-1;i++){
        int x=a[i+1]-a[i];
        if(x>2*d) cnt+=2;//第一种情况
        else if(x==2*d) cnt++;//第二种情况
    }
    cout<<cnt;
    return 0;
}
```


---

## 作者：Obviathy (赞：1)

## 解题思路：
计算相邻酒店的距离，如果距离大于 $2d$，在这两个酒店之间就有距离第 $i$ 家酒店 $d$ 米和距离第 $i-1$ 家酒店 $d$ 米两种情况；如果距离等于 $2d$，在这啷个酒店之间就只有正中间这一种情况；如果距离小于 $2d$，那么无论距离这两家酒店中哪一家距离是 $d$，都要距离另一家小于 $d$ 米，$d$ 就不是最小值，所以没有情况。因为两头都可以放，所以最后的结果还要加二。
## AC Code:
```cpp
#include<bits/stdc++.h>\\if判断版
using namespace std;
int n,k,ans;
int a[200];
int main(){
	cin >> n >> k;
	for(int i = 1;i <= n;i ++)cin >> a[i];
	sort(a+1,a+n+1);
	for(int i = 2;i <= n;i ++)
	 if((a[i]-a[i-1])*1.0/k==2)ans++;
	 else if((a[i]-a[i-1])*1.0/k>2)ans+=2;
	cout<<ans+2;
	return 0;
}
```

```cpp
#include<bits/stdc++.h>\\公式压行版
using namespace std;
int n,k,ans=2;
int a[200];
int main(){
	cin >> n >> k >> a[1];
	for(int i = 2;i <= n;i ++){cin >> a[i];ans=ans+((a[i]-a[i-1])==2*k)+2*(a[i]-a[i-1]>2*k);}
	cout<<ans+2<<endl;
	return 0;
}

```

---

## 作者：猜一猜我是谁 (赞：1)

# 思路
既然说了新酒店和其他酒店最小距离是 $d$，那我们可以先在两边建，即最初 $ans=2$。然后再一个个枚举两个相邻的酒店，尝试在相邻两个酒店之间建造酒店，如果重合了就只可建造一个酒店，否则如果距离大于 $2\times d$ 就可建造两个酒店。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[105];
int main(){
    long long n,d,ans=2;
    cin>>n>>d;
    for(long long i=1;i<=n;i++) cin>>a[i];
    for(long long i=1;i<n;i++){
        int b=a[i+1]-a[i];
        if(b==2*d) ans++;
        else if(b>2*d) ans+=2;
    }
    cout<<ans;
}
```

---

## 作者：maple_love (赞：1)

  一道大水题，在CF上看到的时候满脸~~mmp~~高兴，开始看到的时候以为很难~~（实际上更难）~~，开始的时候以为是在二维矩阵里求出让Sonya盈利最多的方法，后来才发现想多了。
奉上题解：
```
#include<bits/stdc++.h>
using namespace std;
int n;
int dis,hotel[110];
int ans=2;//定义初始酒店数量 ，这个是个坑
void judge(int x)//判定函数 
{
	if (hotel[x]-hotel[x-1]>=2*dis+1)
    {
        ans+=2;
	}
    if (hotel[x]-hotel[x-1]==2*dis)
    {
        ans++;
	}	
} 
int main()
{
	int i;
    cin>>n>>dis;
    for(i=1;i<=n;i++)
    {
    	cin>>hotel[i];
	} 
    for (i=2;i<=n;i++)
	{
    	judge(i);
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：Luo_gu_ykc (赞：0)

## 题目大意

有一个数轴，数轴上有 $n$ 家酒店，给出 $n$ 家酒店的坐标（递增），现在要新开一家酒店，这家酒店与别的酒店的间隔不能小于 $d$, 问这家酒店可以开在哪。

## 思路

由于坐标是递增的，所以可以在左右两家酒店之间建造，如果这两家酒店的坐标差为 $2 \times d$，只能建造一家酒店，但如果差大于 $2 \times d$，那么就能建造两家酒店，最后统计即可（记得可以在第一家酒店之前和最后一家酒店之后建造）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 105;
int n, k, a[N], sum;
int main(){
	cin >> n >> k;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		if(i >= 2){
			int cha = a[i] - a[i - 1];
			if(cha == 2 * k){ // 为 2 * k
				sum++;
			}
			if(cha > 2 * k){ // 大于 2 * k
				sum += 2;
			}
		}
	}
	cout << sum + 2; // 还有在最左和最右建造的两种方案
	return 0;
}


---

## 作者：_HiKou_ (赞：0)

UPD：把数学公式加上了 $\LaTeX$。

[题目传送门](https://www.luogu.com.cn/problem/CF1004A)

本题的大致意思是，在数轴上找一个点，使其到其他已知点的最小距离等于 d。

很显然第一步可以先想到，既然要距离最小，那直接在每个点两侧 d 个单位处做点，答案肯定是 $2n$。

但是，这里又有两个问题。

1. 如当 $d=3$ 时且两个酒店位置为 0 和 4 时，按照刚刚的逻辑，找到的点的位置为 3 。可是最近距离应该为 $4-3=1$ ，不等于 3 。

2. 如当 $d=3$ 时且两个酒店位置为 0 和 6 时，在 0 的右侧找到的点为 3，在 6 的左侧找到的点也为 3，两个点重合了。

针对以上两个问题，我们可以有如下操作方案：

1. 首先，第一个酒店的左侧和第 n 个酒店的右侧一定可以找到一个点，因为在这里选址没有更近的点，所以答案可以先初始化为 2。

2. 对于中间的点，我们可以枚举每一个酒店的间隔，如果 $a[i]+d<a[i+1]-d$，说明了两个点是不重复的，且不会影响到对方。（既然 $a[i]+d<a[i+1]-d$，说明 $a[i+1]-(a[i]+d)>d$，即两者距离大于 d，不会影响到彼此，$a[i+1]$ 左侧同理）

3. 如果 $a[i]+d=a[i+1]-d$，说明两个点重合，只取一个。

CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1010],ans=2;//答案先初始化为2
int main(){
	long long n,d,i;
	cin>>n>>d;
	for(i=1;i<=n;i++)cin>>a[i];
	for(i=1;i<=n-1;i++)//间隔数为n-1个
	{
		if(a[i]+d==a[i+1]-d)ans++;//如果重合就只取一个
		else if(a[i]+d<a[i+1]-d)ans+=2;//否则就把两个点都加上
      		//如果不满足则什么都不做，即这个间隔不取点
	}
	cout<<ans;
	
	
	return 0;
}
```

---

## 作者：__Hacheylight__ (赞：0)

水题一道

注意处理细节

先是肯定a[1]向左建d的和a[n]向右建d的都是可以的

之后，从2枚举到n

若a[i]到a[i-1]的空隙>2*d 说明 a[n-1]向右 和 a[n]向左都可以 ans+2

若=2*d 则两种方法的地方相同 ans+1

首先对于每个位置的数字都可以往左或者往右添加一个距离为d的点，

往左边添加的话那么它距离当前点左边那个点的距离一定要大于等于d，

往右同理。

这种时候有可能会把某个点算重复，

比如d=2时，4 8。

6会在4的右边被统计一次，

还会在8的左边被统计一次，

所以我们要把这种情况归到某一边

（即左边为>=右边为>或左边为>右边为>=）。

```cpp
#include <bits/stdc++.h>
using namespace std ;
int n ;
int d,a[110] ;
int main(){
	scanf("%d%d",&n,&d) ;
	for (int i=1;i<=n;i++) scanf("%d",&a[i]) ;
	int ans=2;
	for (int i=2;i<=n;i++){
		if (a[i]-a[i-1]>=2*d+1) ans+=2 ;
		if (a[i]-a[i-1]==2*d) ans++ ;
	}
	printf("%d\n",ans) ;
} 
```

---

## 作者：Hanghang (赞：0)

# 注意细节，细节

## [题目传送门](https://www.luogu.com.cn/problem/CF1004A)

## [AC记录](https://www.luogu.com.cn/record/44868899)

仔细读题，发现并不难首先可以判断答案大于等于2

就看中间能放几个，进行判断即可

话不过说，直接看代码（没有注释貌似是最短的）

```cpp

#include<bits/stdc++.h>
using namespace std;
//万能头大法好

int n,k,s=2,x,y;
//n表示酒店数量，s表示方案数量
//k表示新酒店到其他所有酒店的距离的最小值
//x表示当前酒店坐标，y表示上一个酒店坐标
int main()
{
   cin>>n>>k>>x;y=x;
        //读入，初始化
	for(int i=1;i<n;i++)
        //注意，已经输入了一个，要少循环一次
	{
		y=x;cin>>x;
                //初始化，读入
		if(x-y>k*2)s+=2;
                //判断是否可以有两个可能
		if(x-y==k*2)s++;
                //判断是否可以有一个可能
	}
	cout<<s<<endl;
        //直接输出走人
	return 0;
    //别忘了return 0
}

```

---


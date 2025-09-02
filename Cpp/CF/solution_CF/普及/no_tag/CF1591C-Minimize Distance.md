# Minimize Distance

## 题目描述

A total of $ n $ depots are located on a number line. Depot $ i $ lies at the point $ x_i $ for $ 1 \le i \le n $ .

You are a salesman with $ n $ bags of goods, attempting to deliver one bag to each of the $ n $ depots. You and the $ n $ bags are initially at the origin $ 0 $ . You can carry up to $ k $ bags at a time. You must collect the required number of goods from the origin, deliver them to the respective depots, and then return to the origin to collect your next batch of goods.

Calculate the minimum distance you need to cover to deliver all the bags of goods to the depots. You do not have to return to the origin after you have delivered all the bags.

## 说明/提示

In the first test case, you can carry only one bag at a time. Thus, the following is a solution sequence that gives a minimum travel distance: $ 0 \to 2 \to 0 \to 4 \to 0 \to 3 \to 0 \to 1 \to 0 \to 5 $ , where each $ 0 $ means you go the origin and grab one bag, and each positive integer means you deliver the bag to a depot at this coordinate, giving a total distance of $ 25 $ units. It must be noted that there are other sequences that give the same distance.

In the second test case, you can follow the following sequence, among multiple such sequences, to travel minimum distance: $ 0 \to 6 \to 8 \to 7 \to 0 \to 5 \to 4 \to 3 \to 0 \to (-5) \to (-10) \to (-15) $ , with distance $ 41 $ . It can be shown that $ 41 $ is the optimal distance for this test case.

## 样例 #1

### 输入

```
4
5 1
1 2 3 4 5
9 3
-5 -10 -15 6 5 8 3 7 4
5 3
2 2 3 3 3
4 2
1000000000 1000000000 1000000000 1000000000```

### 输出

```
25
41
7
3000000000```

# 题解

## 作者：xiaozeyu (赞：3)

[CF1591C Minimize Distance](https://www.luogu.com.cn/problem/CF1591C)

一道贪心题目。

在数轴上有很多的货物，每个货物有自己的坐标。

开始时自己在坐标轴原点。

每次最多能去拿起 $k$ 个货物，然后要把货物再拿回原点处。

所需的代价就是做过的路程长度。

在最后拿完了之后，不需要回到原点，也就是最终停留在最后拿起东西的地方。

这显然是一个贪心。

每次都可以拿上好几个货物，尽量每次都拿满。

每次拿连续的一段，这时最远的一个的距离就对应这单程的代价。

不该回头，回头再折返会浪费这重复的距离，要拿就顺路捎上。

从两端开始分别取正坐标物品与负坐标物品。保证拿上高代价的同时拿上其他高代价的物品，接下来的代价就会降低。

这时有了一个问题，靠近原点的两边的不满 $k$ 个的物品该怎么处理？

我们已经发现了单侧折返会亏。

在双侧情况下，越过零点折返去拿另一头的物品是不赚的，因为你本可以在经过原点时就把拿着的放下，再去另一端，这样你可以拿上另一头更多的物品，你的总代价是大于等于折返时的，也就是不劣。

最后是不用在取光之后返回的事情。

在正端与负端出现的最大值一定是在顶头的，我们只需要在最后去掉一个最大的单程即可。

在代码的实现上，我们只需要分别取完左右两边的物品，记录单程的代价，在最后翻倍，并且去除两头中最大的一次单程代价。

代码如下。



------------

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
int read()
{
	char c=getchar();int x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
const int maxn=200010;
int T,n,k,a[maxn];
int ans;
signed main()
{
	T=read();
	while(T--)
	{
		ans=0;
		n=read();k=read();
		For(i,1,n) a[i]=read();
		sort(a+1,a+n+1);
		for(int i=n;i>=1&&a[i]>0;i-=k) ans+=a[i];
		for(int i=1;i<=n&&a[i]<0;i+=k) ans-=a[i];
		printf("%lld\n",ans*2-max(abs(a[1]),a[n]));
	}	
}
```

感谢管理的审核。

---

## 作者：Hutao__ (赞：0)

## 思路
由于求最短路程，所以我们考虑贪心。

可以把坐标分成正数和负数两个部分，分别求最短路程。

而且每次我们要尽量拿满 $k$ 个，然后还要回去，所以答案要乘 $2$。

直接遍历坐标即可。

## 代码


```cpp
//lgRMJ坏了，不保证此代码能通过本题
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,a[200005];
signed main(){
	cin>>t;
	while(t--){
		int n,k,sum=0;
		cin>>n>>k;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1);//
		for(int i=1;i<=n;i+=k){//遍历负坐标
			if(a[i]>0)break;
			sum+=2*abs(a[i]);//要回去，答案乘2
		}
		for(int i=n;i>=1;i-=k){//遍历正坐标
			if(a[i]<0)break;
			sum+=2*abs(a[i]);//同上
		}
		cout<<sum-max(abs(a[1]),abs(a[n]))<<'\n';//由于到最后可以不用回去，所以减去两端的绝对值最大值
	}
      return 0;  
}
```

---

## 作者：ghx0052 (赞：0)

## 思路
考虑贪心，贪心方法如下：

先从小到大排序，先送距离远的，再向距离近的送，每次带满 $k$ 个；

即原点左的答案如下（设 $n_1$ 为原点左侧的最大值的下标）:

$$
(|a_1|+|a_{1+k}|+|a_{1+2\times k}|+\cdots+|a_{1+\lfloor n_1\div k\rfloor \times k}|)\times 2
$$

原点右同理，答案如下（设 $n_2$ 为原点右侧的最小值的下标）：

$$
(|a_n|+|a_{n-k}|+|a_{n-2\times k}|+\cdots+|a_{n-\lfloor (n-n_2)\div k\rfloor \times k}|)\times 2
$$

因为最终可以不回原点，所以总答案减去一个 $\max(|a_1|,|a_n|)$；

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[100010];
signed main() {
    int t;
    cin >> t;
    while (t --) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; i ++) cin >> a[i];
        sort(a + 1, a + n + 1);
        int ans = 0;
        for (int i = 1; i <= n && a[i] < 0; i += k) ans += abs(2 * a[i]);
        for (int i = n; i >= 1 && a[i] >= 0; i -= k) ans += abs(2 * a[i]);
        cout << ans - max(abs(a[1]), abs(a[n])) << endl;
    }
}
```

---


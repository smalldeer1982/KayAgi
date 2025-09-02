# Maxim and Discounts

## 题目描述

Maxim always goes to the supermarket on Sundays. Today the supermarket has a special offer of discount systems.

There are $ m $ types of discounts. We assume that the discounts are indexed from 1 to $ m $ . To use the discount number $ i $ , the customer takes a special basket, where he puts exactly $ q_{i} $ items he buys. Under the terms of the discount system, in addition to the items in the cart the customer can receive at most two items from the supermarket for free. The number of the "free items" (0, 1 or 2) to give is selected by the customer. The only condition imposed on the selected "free items" is as follows: each of them mustn't be more expensive than the cheapest item out of the $ q_{i} $ items in the cart.

Maxim now needs to buy $ n $ items in the shop. Count the minimum sum of money that Maxim needs to buy them, if he use the discount system optimally well.

Please assume that the supermarket has enough carts for any actions. Maxim can use the same discount multiple times. Of course, Maxim can buy items without any discounts.

## 说明/提示

In the first sample Maxim needs to buy two items that cost $ 100 $ and get a discount for two free items that cost $ 50 $ . In that case, Maxim is going to pay $ 200 $ .

In the second sample the best strategy for Maxim is to buy $ 3 $ items and get $ 2 $ items for free using the discount. In that case, Maxim is going to pay $ 150 $ .

## 样例 #1

### 输入

```
1
2
4
50 50 100 100
```

### 输出

```
200
```

## 样例 #2

### 输入

```
2
2 3
5
50 50 50 50 50
```

### 输出

```
150
```

## 样例 #3

### 输入

```
1
1
7
1 1 1 1 1 1 1
```

### 输出

```
3
```

# 题解

## 作者：happy_zero (赞：1)

### 这题是一个贪心。
首先是对于打折方案的选择。显然的，我们应该选择 $q_i$ 最小的那一种，因为每一种方案送的商品个数都是一样的，而 $q_i$ 小的可以使打折的次数多一些。我们令 $k$ 为最小的 $q_i$。

接下来是选择哪些付钱，哪些赠送。对于每每买了 $k$ 个物品时，我们选价格大的赠送肯定更划算。但注意，赠送的商品价格不能超过购买的商品价格，所以前 $k$ 大的商品一定不能被当作赠品，只能购买，所以我们按商品价格从大到小的顺序选择，每当买满 $k$ 件后就选剩下中价格最大的两件，接着把这两件跳过。

注：这里我们最好从大到小排序后正序枚举，若从小到大排序后倒叙枚举，则在跳过时可能会有数组越界的情况。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int N = 100005;
int a[N];
bool cmp(int x, int y)
{
    return x > y;
}
int mian()
{
    int n, m, k = INF;
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        int x;
        cin >> x;//由于只需要最小的所以不用存起来
        k = min(k, x);
    }
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort (a + 1, a + 1 + n, cmp);//从大到小排序
    int ans = 0, cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += a[i];//当前商品需要购买
        cnt++;
        if (cnt % k == 0) i += 2;//若cnt%k=0则说明已经买满k件
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：Transparent (赞：1)

### 题目大意：
商店进行促销活动，
有 $m$ 种促销方式，
其中第 $i$ 种方式是
买满 $q_i$ 种商品后可以任意选择 $0$~$2$ 种商品作为赠品
~~（话说除非超市被抢空了，谁会傻到选1种或不选）~~ ，
但是要求选择的所有物品种价格最大的商品的价格
都不能大于购买的这 $q_i$ 种商品中价格最小的商品的价格。
每种促销可以无限次数地参加，
给你 $n$ 个商品的价格，
问买这 $n$ 个商品最少需要花多少钱。

花絮：做题时直接从CF复制题目到Google Translate翻译，
结果翻译出来 $1 \leq n \leq 105$ ，
窝就觉得不对劲，
结果 RE 之后发现（别找提交记录了，在CF上交的）， 
正确的范围是 $1 \leq n \leq 10^5$ ……

友情提示：别太相信翻译，能看懂的尽量自己看吧……

### 方法：贪心
既然每种优惠可以无数次参与，
并且奖励方式相同
那当然选要求最低的参加啦！
这样赠品的数量就可以得到最大值了。
于是可以发现，这道题得数据中有许多的
~~坑~~ 无用条件。

既然赠品有价格的要求，
而要使节约的钱最多，
赠品的价格当然越大越好。

既然所有东西都得买，
那从最贵得开始卖就会更划算，
因为买的贵，送的东西也贵啊！
都得买，肯定得让赠品得价值最大化。

按照以上买法，
一定可以用最少的前，
买到最大价值的东西。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define min(a,b) (((a)<(b))?(a):(b))//手写min函数提速（好像并没啥用） 
int m,n,minq=0x7fffffff,tmp,a[100001];
int main()
{
	scanf("%d",&m);
	for(register int i=1;i<=m;++i)
	{
		scanf("%d",&tmp);//无用条件就不用存储了 
		minq=min(minq,tmp); //留下最小值作为有用条件 
	}
	scanf("%d",&n);
	for(register int i=1;i<=n;++i)
	{
		scanf("%d",a+i);
	}
	sort(a+1,a+n+1);//把商品价格从小到大排序 
	int nowa=n,nownum=0,ans=0;//从尾到头遍历，就是从大到小遍历 
	while(nowa>0)
	{
		ans+=a[nowa];//统计答案 
		++nownum;//统计当前未参与促销的商品数量 
		--nowa; 
		if(nownum==minq)//满足条件，立即享受优惠 
		{
			nownum=0;//清空数量 
			nowa-=2;//将这两个商品视为赠品 
		}
	}//特别注意，if不能放在while前面，因为在去除赠品后，nowa有可能为负数。 
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：XL4453 (赞：0)

### 解题思路：

考虑贪心。

首先发现，由于每一个打折方式可以使用多次，所以其实真正用到的打折方式只有一种，也就是最少的那一种。否则，将选出的一个 $q_i$ 更大的换成更小的一定不劣于当前答案。

然后决策如何选择物品，发现如相当于每一次选择 $q_i+2$ 个物品然后只支付最贵的 $q_i$ 个物品的钱。显然，每一次选择最贵的 $q_i+2$ 个物品一定是最优的。否则在进行交换后优惠掉的价格一定不高于前者。

---
### 代码:

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[100005],minx=2147483647,m,x,ans;
int main(){
	scanf("%d",&m);
	for(int i=1;i<=m;i++)scanf("%d",&x),minx=min(minx,x);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	sort(a+1,a+n+1);
	int cnt=0;
	for(int i=n;i>=1;i--){
		cnt++;
		ans+=a[i];
		if(cnt==minx)i-=2,cnt=0;;
	}
	printf("%d",ans);
	return 0;
}
```

---
### 闲话:

其实这样打折也挺好的，尤其是存在价格高昂的物品时，假设洛谷采用这种优惠方案，当有一个 $q_i$ 为 $1$ 时，在洛谷报名 NOIP 计划就可以白嫖省选计划了。（逃

---


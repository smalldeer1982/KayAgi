# [ABC121C] Energy Drink Collector

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc121/tasks/abc121_c

栄養ドリンクにレーティング上昇効果があると聞いた高橋くんは、$ M $ 本の栄養ドリンクを買い集めることにしました。

栄養ドリンクが売られている店は $ N $ 軒あり、$ i $ 軒目の店では $ 1 $ 本 $ A_i $ 円の栄養ドリンクを $ B_i $ 本まで買うことができます。

最小で何円あれば $ M $ 本の栄養ドリンクを買い集めることができるでしょうか。

なお、与えられる入力では、十分なお金があれば $ M $ 本の栄養ドリンクを買い集められることが保証されます。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N,\ M\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ B_i\ \leq\ 10^5 $
- $ B_1\ +\ ...\ +\ B_N\ \geq\ M $

### Sample Explanation 1

$ 12 $ 円あれば $ 1 $ 軒目の店で $ 1 $ 本、$ 2 $ 軒目の店で $ 4 $ 本の栄養ドリンクを購入し、合計 $ 5 $ 本の栄養ドリンクを買い集めることができます。一方、$ 11 $ 円以下では $ 5 $ 本の栄養ドリンクを買い集めることができません。

### Sample Explanation 3

出力が $ 32 $ ビット整数型におさまらないことがあります。

## 样例 #1

### 输入

```
2 5
4 9
2 4```

### 输出

```
12```

## 样例 #2

### 输入

```
4 30
6 18
2 5
3 10
7 9```

### 输出

```
130```

## 样例 #3

### 输入

```
1 100000
1000000000 100000```

### 输出

```
100000000000000```

# 题解

## 作者：Otomachi_Una_ (赞：0)

很基本的贪心，买饮料时，应先买便宜的，这样才能出最优解，逻辑与[P1208 混合牛奶](https://www.luogu.com.cn/problem/P1208)类似，这里不多阐述。

特别要注意的是，因为数据范围，这里记录答案的变量要开 long long 。

## _Code_

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long
const int MAXN=1e5+5;
int n,m;
ll ans=0;
struct shop{
	int num;
	ll val;
}a[MAXN];
bool cmp(shop x,shop y){
	return x.val<y.val;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i].val>>a[i].num;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(a[i].num>=m){
			ans+=m*a[i].val;
			break;
		}
		ans+=a[i].num*a[i].val;
		m-=a[i].num;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Kevin_Zhen (赞：0)

题目链接 [$\mathfrak{AT4326}$](https://www.luogu.com.cn/problem/AT4326)，原题面详见[官网](https://atcoder.jp/contests/abc121/tasks/abc121_c)。  
本题翻译在表述上稍有不妥，此篇题解会给出清晰的翻译，读者亦可以直接参考官网英文原版题面。

### 题目大意
高桥君决定去买 $M$ 瓶饮料。  
有 $N$ 家超市，对于第 $i$ 家超市，高桥君可以以 $A_i$ 的单价购买一瓶饮料。但是超市供货有限，高桥君在第 $i$ 家超市最多只能买 $B_i$ 瓶饮料。  
高桥君想知道他最少需要花多少钱，买到 $M$ 瓶饮料。

### 输入格式
$N\ \ \ M$  
$A_1\ \ \ B_1$  
$A_2\ \ \ B_2$  
$\vdots$  
$A_N\ \ \ B_N$

### 变量介绍
结构体 $\operatorname{Shop}$：$\operatorname{price}$ 记录单价，$\operatorname{num}$ 记录物品数量。  
$\operatorname{cnt}$：记录已经购买的物品数量。  
$\operatorname{ans}$：记录购买所花的金额（所求答案），注意要开 $\operatorname{long\ long}$。

### 思路
本题可以运用贪心的思想，将所有超市按照单价升序排序。

对于每一个超市，如果 当前已经购买的物品数量 加上 这个超市的供货量 小于等于 $M$，我们就可以把这个超市所有的饮料买下，并累加上购买金额。  
如果加上这个超市的供货量后超过了 $M$ 瓶，只需购买剩下所需的瓶数，然后跳出循环。

具体实现详见代码。

### AC CODE
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

struct Shop {
	int price, num;
} shop[100010];

int n, m, cnt; ll ans;

bool cmp(Shop a, Shop b) { return a.price < b.price; }

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &shop[i].price, &shop[i].num);
	}
	sort(shop + 1, shop + 1 + n, cmp);
	for (int i = 1; i <= n; ++i) {
		if (cnt + shop[i].num <= m) {
			cnt += shop[i].num;
			ans += (ll)shop[i].num * shop[i].price;
		}
		else {
			ans += ((ll)m - cnt) * shop[i].price;
			break;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

### 感谢观赏！

---


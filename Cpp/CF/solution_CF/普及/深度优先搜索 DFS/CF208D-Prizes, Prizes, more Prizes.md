# Prizes, Prizes, more Prizes

## 题目描述

## 题意
你有 n 块巧克力可以吃，每块巧克力包装背后有一个积分，要用这些积分去换 5 种不同价格的礼物。你每次只能吃一块，吃完后去换礼物，要求先换价格尽量高的礼物，然后要把积分尽量用完，用不完的积分可以留在下一次和下一个积分合并再用。请输出能换到每种礼物的数量和剩余的积分。

## 样例 #1

### 输入

```
3
3 10 4
2 4 10 15 20
```

### 输出

```
1 1 1 0 0 
1
```

## 样例 #2

### 输入

```
4
10 4 39 2
3 5 10 11 12
```

### 输出

```
3 0 1 0 3 
0
```

# 题解

## 作者：liukangyi (赞：0)

# 题目大意
给你数字 $n$ 和 $n$ 块巧克力的积分以及 $5$ 样礼品所需的积分数，而且每吃完一块巧克力后可以用当前的积分**尽量先买最高价的礼品**，最后问你能换到每种礼物的数量与剩余的积分数。


------------
# 分析
这道题已经给了我们买礼品时的要求，即要按价格**从大到小**来进行购买，所以我们从**第一块巧克力一直到最后一块巧克力**，每次对积分进行累加，并按倒序遍历礼品，同时统计每种礼物的个数，最后输出即可。

------------
**注意：保险起见，开 long long**。


------------
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cursum,p[60],a[10],res[10]; //定义变量 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i]);
	for(int i=1;i<=5;i++)
		scanf("%d",&a[i]);
	//输入数据
	 
	for(int i=1;i<=n;i++){
		cursum+=p[i]; //累加积分 
		for(int j=5;j>=1;j--){ //倒序 
			res[j]+=cursum/a[j]; //统计当前礼品购买数 
			cursum%=a[j]; //买完后剩下的钱 
		}
	}
	
	for(int i=1;i<=5;i++)
		printf("%d ",res[i]);
	cout<<'\n'<<cursum;
	//输出答案 
	return 0;
}
```



---

## 作者：_Evergarden_ (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/CF208D)

## 题意

给定一些积分，在使用一次积分之后买礼物，尽量买价格最高的且尽量把积分花完，剩余积分可以留下再次使用，最后输出每一种礼物买的次数和剩余钱数。

## 思路

一个简单的贪心。

用一个变量存储当前积分数，循环枚举，在枚举每种礼物价格时**倒序**枚举，能减就减，最后输出就可以了。

#### 注意：需要开 long long。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5 + 10;

int p[N], a[6] , ans[6], now;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int n;
	cin >> n;
	for(int i = 1; i <= n; ++ i) cin >> p[i];
	for(int i = 1; i <= 5; ++ i) cin >> a[i];
	for(int i = 1; i <= n; ++ i) {
		now += p[i];
		for(int j = 5; j >= 1; -- j) {
			if(now >= a[j]) {
				ans[j] += now / a[j];
				now -= (now / a[j]) * a[j];
			}
		}
	}
	for(int i = 1; i <= 5; ++ i) cout << ans[i] << (i != 5 ? " " : "\n");
	cout << now;
	return 0;
}
```


---

## 作者：zwy__ (赞：0)

### 题意
你有 $n$ 块巧克力可以吃，每块巧克力包装背后有一个积分，要用这些积分去换 $5$ 种不同价格的礼物。你每次只能吃一块，吃完后去换礼物，要求先换价格尽量高的礼物，然后要把积分尽量用完，用不完的积分可以留在下一次和下一个积分合并再用。请输出能换到每种礼物的数量和剩余的积分。
### 思路
这题我们按题意模拟。先用一个变量存储积分，然后从尾到头扫一遍，如果其中一个礼物可以换的话，我们就用一个数组存储这个礼物可兑换的次数，最后输出就可以了。
### 细节
这题不管是数组还是变量都要开 $long\,\,long$ ，不然就会错！！！
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,sum;
long long a[550],b[100],c[100];
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++)cin>>a[i];
	for(int i=1; i<=5; i++)cin>>b[i];
	for(int i=1; i<=n; i++)
	{
		sum+=a[i];
		for(int j=5; j>=1; j--)
		{
			if(sum>=b[j])
			{
			    c[j]+=sum/b[j];
				sum-=(sum/b[j])*b[j];
			}
		}
	}
	for(int i=1; i<=5; i++)cout<<c[i]<<" ";
	cout<<endl<<sum;
	return 0;
}
```


---

## 作者：fuzhelin1984 (赞：0)

## 思路

  题意讲的很清楚了，只要每次吃完就去尽量换礼物，然后没用完的就留到下次，为了让效率高一点，我们可以用除法快速求出每次最多能换多少，直接模拟就好。
  
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100],b[100],c[10000],sum;
int main()
{
	long long n;
	cin >> n;
	for(int i = 1;i <= n;++i) cin >> c[i];
	cin >> a[1] >> a[2] >> a[3] >> a[4] >> a[5];
	for(int i = 1;i <= n;++i)
	{
		sum += c[i];
		for(int j = 5;j >= 1;--j)
		{
			if(sum >= a[j])
			{
				int syy = sum / a[j];
				b[j] += syy;
				sum -= syy * a[j];
			}
		}
	}
	cout<<b[1]<<" "<<b[2]<<" "<<b[3]<<" "<<b[4]<<" "<<b[5]<<"\n"<<sum;
	return 0;
}
```


---

## 作者：Raoxiaomi (赞：0)

这题没什么想法就是暴力贪心就行。

不用考虑可以买更多东西。
每次拿到积分就查一次就行。

~~知道你们想看代码了（不是）~~。
```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
#define ll long long int
#define MAXN 105
/////////////////////////////////
ll ans[MAXN], re[MAXN], p[MAXN], noko = 0;
int main(int argc, char** argv){
	ios::sync_with_stdio(false);
	//freopen("1.txt", "r", stdin);
	int n; cin >> n;
	for(int i = 0; i < n; i++){
		cin >> re[i];
	}
	for(int i = 0; i < 5; i++){
		cin >> p[i];
	}
   //noko是剩下的点数   每一次积攒下来的点数有得用就会被用掉。
	for(int i = 0; i < n; i++){
		noko += re[i];
		for(int j = 4; j >= 0; j--){
			if(noko >= p[j]){
				ans[j] += noko / p[j];
				noko -= (noko/p[j]) * p[j];
			}
		}
	}
	for(int i = 0; i < 5; i++){
		cout << ans[i] << " ";
	}
	cout << endl << noko << endl;
	return 0;
}
```


---


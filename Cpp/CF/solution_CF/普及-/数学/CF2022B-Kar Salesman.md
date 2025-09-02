# Kar Salesman

## 题目描述

Karel is a salesman in a car dealership. The dealership has $ n $ different models of cars. There are $ a_i $ cars of the $ i $ -th model. Karel is an excellent salesperson and can convince customers to buy up to $ x $ cars (of Karel's choice), as long as the cars are from different models.

Determine the minimum number of customers Karel has to bring in to sell all the cars.

## 说明/提示

For the first case, Karel only needs to lure in $ 3 $ customers. He will convince the customers to buy the following models of cars:

- Customer $ 1 $ buys $ 2 $ cars with model $ 1 $ and $ 3 $ .
- Customer $ 2 $ buys $ 2 $ cars with model $ 1 $ and $ 2 $ .
- Customer $ 3 $ buys $ 2 $ cars with model $ 1 $ and $ 3 $ .

For the second case, Karel only needs to lure in $ 3 $ customers. He will convince the customers to buy the following models of cars:

- Customer $ 1 $ buys $ 2 $ cars with model $ 1 $ and $ 3 $ .
- Customer $ 2 $ buys $ 3 $ cars with model $ 1 $ , $ 2 $ and $ 3 $ .
- Customer $ 3 $ buys $ 1 $ car with model $ 3 $ .

## 样例 #1

### 输入

```
4
3 2
3 1 2
3 3
2 1 3
5 3
2 2 1 9 2
7 4
2 5 3 3 5 2 5```

### 输出

```
3
3
9
7```

# 题解

## 作者：jubaoyi2011 (赞：2)

## 题意
卡雷尔是一家汽车经销店的推销员。这家经销商有 $n$ 种不同型号的汽车。第 $i$ 种型号的汽车有 $a_i$ 辆。卡雷尔是一名优秀的销售人员，他可以说服顾客购买多达 $x$ 辆来自不同的型号的车。

请确定卡雷尔销售所有汽车所需要引入的最小客户数量。

## 思路

我们设至少有 $ans$ 个顾客，应为他们买的车型不同，且每人只买一辆车，所以可以得出结论：

$ans = \max \left \{  a_1 , a_2 , a_3 , \dots a_{n-1} , a_n \right \}$。

然后再考虑每名顾客只能买 $x$ 辆车，所以又可以得出结论：

$ans = \left \lceil \frac{ a_1 + a_2 + a_3 + \dots + a_{n-1} + a_n}{x} \right \rceil$。

综上所述， $ans = \max \left \{ \max \left \{  a_1 , a_2 , a_3 , \dots a_{n-1} , a_n \right \} , \left \lceil \frac{ a_1 + a_2 + a_3 + \dots + a_{n-1} + a_n}{x} \right \rceil \right \}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int T,n,x,ans,mmax,a;

main(){
	cin>>T;
	while(T--){
		cin>>n>>x;
		ans=0;
		mmax=0;
		while(n--){
			cin>>a;
			mmax=max(mmax,a);//if(max<a)swap(mmax,a);
			ans+=a;
		}
		cout<<max(mmax,(ans+x-1)/x)<<endl;
		/*
		ans=max(mmax,(ans+x-1)/x);
		cout<<ans<<endl;
		*/
	}
}
```

---

## 作者：Zhl2010 (赞：1)

# 题目概括
给~~像我一样~~看不懂题目翻译的人。

有 $T$ 个测试数据，每个数据有 $n$ 辆车，卖车要遵循以下两点：

 - 每个顾客可以买 $x$ 辆车。

 - 且这些车是不同型号的。

## 思路
分析题目中的两个条件。

首先每个顾客只能买 $x$ 辆车，所以假如只有这个条件，答案为 $\lceil \frac{\sum^{n}_{i-1} a_{i}}{x} \rceil$。

其次每个顾客买的车只能是不同型号的，所以假如只有这个条件，答案为 $\max\{ a_{1},a_{2},...,a_{n} \}$。

所以最后的答案为 $\max\{\lceil \frac{\sum^{n}_{i-1} a_{i}}{x} \rceil,\max\{ a_{1},a_{2},...,a_{n} \}\}$。

最后不要忘记开 `long long`。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,x;
		cin>>n>>x;
		int sum=0,a;
		int ma=0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&a);
			sum+=a;
			ma=max(ma,a);
		}
		cout<<max(ma,(sum+x-1)/x)<<endl;
	}
	return 0;
}
//AC 记录：https://codeforces.com/problemset/submission/2022/289090899 
```

---

## 作者：a18981826590 (赞：0)

# [Kar Salesman](https://www.luogu.com.cn/problem/CF2022B)
## 解题思路
分两种情况讨论：

1. $n \le x$：在这种情况下，所有顾客都可以把余下的车都买一辆，即每个顾客可以使剩余数量 $> 0$ 的车的数量减少 $1$，答案即为 $\max\{ a_{1},a_{2},...,a_{n} \}$。

2. $n > x$：除了刚才的答案，因为每个顾客最多买 $x$ 辆车，答案即为 $\lceil \frac{\sum^{n}_{i-1} a_{i}}{x} \rceil$。

综上所述，最终答案即为以上两个答案的最大值。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int a,m,n,s,t,x;
int main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n>>x;
		m=s=0;
		while(n--){
			cin>>a;
			m=max(a,m);
			s+=a;
		}
		cout<<max(m,(long long int)ceil(1.0*s/x))<<'\n';
	}
	return 0;
}
```

---

## 作者：chengjindong (赞：0)

[题目](https://www.luogu.com.cn/problem/CF2022B)

首先由于每个顾客每一种车只能买一辆，所以至少需要：$\max(a_1,a_2,...a_n)$ 名顾客来卖车，但每个顾客只能买 $x$ 个，所以要 $\frac{\sum_{i=1}^{n}a_i}{x}$ 名顾客来卖车。所以最终答案就是它们的最大值。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int t;
	cin >>t;
	while(t--){
        int n,x;
		cin >>n>>x;
		int s=0;//总和
		int ma=0;//最大值
		while(n--){
            int a;
			cin >>a;
			ma=max(ma,a);//取最大值
			s+=a;//累加
		}
		cout<<max(ma,(s+x-1)/x)<<endl;//套公式
	}
    return 0;
}
```

---

## 作者：qiuqiu1231 (赞：0)

### 思路
看到题目，就知道是贪心。我们可以先看拥有最多汽车的型号，这样能尽可能多的减少剩余的汽车数量。
### 实现
1. 将所有车型降序排序，找到最多客户需要的车型。
2. 遍历每个汽车型号，看看要多少客户才能售完这种汽车。
3. 将所有每种汽车所需的客户数加起来，就可以得到最小的客户数量。
### 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int t;  
    cin >> t;
    while (t--) {
        int n, x;  
        cin >> n >> x;
        vector<long long> a(n);  // 存储每种型号的汽车数量
        for (int i = 0; i < n; ++i) {
            cin >> a[i];  // 读取每种型号的汽车数量
        }
        // 将汽车数量降序排序
        sort(a.rbegin(), a.rend());
        long long customers = 0;  // 需要的最小客户数量
        // 计算所需的客户数量
        for (int i = 0; i < n; ++i) {
            // 每种型号需要多少客户
            customers += (a[i] + x - 1) / x;
        }
        cout << customers << endl;
    }
    
    return 0;
}
```

### 时间复杂度
- sort 的时间复杂度是 $ O(nlogn) $。
- 遍历的时间复杂度是 $ O(n)$。
- 整体复杂度为 $ O(nlogn)$，可以通过本题。

---

## 作者：linjinkun (赞：0)

简单题。

首先由于每个顾客每一种车只能买一辆，所以至少需要 $\max(a_1,a_2,a_3,\dots,a_n)$ 名顾客才能卖完所有的车，而且由于每位顾客最多买 $x$ 辆车，所以至少需要 $\lceil \frac{\sum_{i = 1}^n a_i}{x} \rceil$ 名顾客才能卖完所有的车，所以整合起来，最终答案就是 $\max(\max(a_1,a_2,a_3,\dots,a_n),\lceil \frac{\sum_{i = 1}^n a_i}{x} \rceil)$。

**注意：十年 OI 一场空，不开 long long 见祖宗。**

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
signed main()
{
	int _;
	scanf("%lld",&_);
	while(_--)
	{
		int n,x;
		scanf("%lld %lld",&n,&x);
		int ans = 0;
		int maxx = 0;
		for(int i = 1;i<=n;i++)
		{
			int x;
			scanf("%lld",&x);
			ans+=x;
			maxx = max(maxx,x);
		}
		printf("%lld\n",max(maxx,(ans+x-1)/x));
	}
	return 0;
}
```

---

## 作者：wuyouawa (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2022B)

### 思路

这道题是一道思维题。

首先，要卖完所有的车，就需要把车辆数最多的型号的车辆数个客户，因为这么多客户的话，才能把最多的全卖掉，少的可以肯定可以用这些顾客买完。那么，也就是 $\max\{a_1,a_2,\ldots,a_n\}$。接下来，由于每个顾客最多只能买 $x$ 辆车，所以顾客数就是汽车数总和 $\div$ $x$，也就是$\lceil{\sum_{i = 1}^{n} a_i \div x}\rceil$。由于我们两个条件都要满足，所以取最大值。

### CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a[200005], s, ma, x, f;
int main() {
	cin >> t;
	while (t--) {
		scanf("%d%d", &n, &x);
		ma = 0, s = 0; //多测不清零，爆零两行泪
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			s += a[i];
			ma = max(ma, a[i]); //求第一个答案
		}
		f = ceil(double(s) / double(x)); //ceil需要强转为double
		ma = max(ma, f); //取最大值
		printf("%d\n", ma);
	}
	return 0;
}
```

---

## 作者：FXLIR (赞：0)

### 题意
有 $n$ 种不同型号的汽车，第 $i$ 种车型有 $a_i$ 辆，每位顾客最多购买 $x$ 辆型号互不相同的汽车。求卖出所有汽车所需的最少顾客数。
### 做法
首先，因为对于同一种车，每位顾客只会买一辆，因此如果想要卖出所有的车，至少需要 $\max \{a_1,a_2,...a_n\}$ 名顾客，设这个人数为 $i$。

同时，因为每位顾客最多只会买 $x$ 辆车，所以如果想要卖出所有的车，至少需要 $\lceil  \frac{\sum_{k=1}^{n}a_i}{x} \rceil$ 名顾客，设这个人数为 $j$。

由于上述两个条件都需要满足，且若满足了所需人数较多的条件，所需人数较少的条件也会被满足，所以答案为 $i$ 和 $j$ 中较大的值。
### AC code
[AC 记录](https://codeforces.com/problemset/submission/2022/286697451)

```cpp
#include<cstdio>
#include<iostream>
#define int long long
using namespace std;
const int N=1e5+5,INF=1e9;
int t,n,x,a,maxa,sum;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		maxa=-1e9,sum=0;
		cin>>n>>x;
		for(int i=1;i<=n;i++){
			cin>>a;
			sum+=a,maxa=max(maxa,a);
		}
		int t=sum/x+(sum%x!=0);
		cout<<max(maxa,t)<<"\n";
	}
	return 0;
}
```

---

## 作者：cly312 (赞：0)

因为每个顾客来买的都不是同一类型的车，所以我们至少需要 $\max\{a_1, a_2, \cdots a_n\}$ 个顾客。

因为每个顾客只能买 $x$ 台车，所以我们至少需要 $\left\lceil \frac{a_1 + a_2 + \cdots + a_n}{x}\right\rceil$ 位顾客。

答案为：$\max\left\{\left\lceil \frac{a_1 + a_2 + \cdots + a_n}{x}\right\rceil, \max\{a_1, a_2, \cdots a_n\}\right\}$。


```cpp
#include <iostream>
using namespace std;
 
int main(){
	int t;
	cin>>t;
	while(t--){
		long long n,x,sum=0,mx=0,in;
		cin>>n>>x;
		while(n--){
			cin>>in;
			mx=max(mx,in);
			sum+=in;
		}
		cout<<max(mx,sum/x+(sum%x!=0))<<"\n";
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2022B)

### 题目大意
卡雷尔是一家汽车经销店的推销员。这家经销商有 $n$ 种不同型号的汽车。第 $i$ 种型号的汽车有 $a_i$ 辆。卡雷尔是一名优秀的销售人员，他可以说服顾客购买多达 $x$ 辆车（卡雷尔的选择），只要这些车来自不同的型号。

确定卡雷尔必须引入的最小客户数量才能销售所有汽车。

### 解题思路
我们需要从两个角度来考虑问题。
1. 由于每个顾客买的车类型都不同，所以我们至少需要 $\max\{a_1,a_2,\cdots,a_n\}$ 位顾客。
2. 由于每个顾客只能买 $x$ 辆车，所以我们至少需要 $a_1,a_2,\cdots,a_n$ 的平均值位顾客，即 $\lceil\frac{a_1+a_2+\cdots+a_n}{n}\rceil$ 位顾客。

故答案为 $\max\{\max\{a_1,a_2,\cdots,a_n\},\lceil\frac{a_1+a_2+\cdots+a_n}{n}\rceil\}$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,x,ans,maxn,a;
int main(){
	cin>>T;
	while(T--){
		ans=maxn=0;
		cin>>n>>x;
		while(n--){
			cin>>a;
			maxn=max(maxn,a);
			ans+=a;
		}
		cout<<max(maxn,(ans+x-1)/x)<<endl;
	}
}
```

---


# FASHION - Fashion Shows

## 题目描述

A fashion show rates participants according to their level of hotness. Two different fashion shows were organized, one for men and the other for women. A date for the third is yet to be decided ;) .

Now the results of both fashion shows are out. The participants of both the fashion shows have decided to date each other, but as usual they have difficuly in choosing their partners. The Maximum Match dating serive (MMDS) comes to their rescue and matches them in such a way that that maximizes the hotness bonds for all couples.

If a man has been rated at hotness level x and a women at hotness level y, the value of their hotness bond is x\*y.

Both fashion shows contain **N** participants each. MMDS has done its job and your job is to find the sum of hotness bonds for all the couples that MMDS has proposed.

## 样例 #1

### 输入

```
2
2
1 1
3 2
3
2 3 2
1 3 2```

### 输出

```
5
15```

# 题解

## 作者：Withers (赞：2)

~~又是一道水题~~

铺垫：
需要用到一个不等式，叫做[排序不等式](https://baike.baidu.com/item/%E6%8E%92%E5%BA%8F%E4%B8%8D%E7%AD%89%E5%BC%8F/7775728?fr=aladdin)：

设有两数列 $a_1,a_2,\dots,a_n$ 和 $b_1,b_2,\dots,b_n$， 
满足 $a_1\le a_2\le\dots\le a_n$，$b_1\le b_2\le\dots\le b_n$，
$c_1,c_2,\dots,c_n$ 是 $b_1,b_2,\dots,b_n$ 的乱序排列，

则有

$\sum_{i=1}^na_ib_{n+1-i}\le \sum_{i=1}^na_ic_i\le \sum_{i=1}^na_ib_i$

基本的证明就是差小积大，用调整法就显然可以得证

------------
题意：

给 $a$ 和 $b$ 数组排个序，使得他们按顺序乘最大

------------
解法：

显然由题意要取到最大值，举一反三，用排序不等式的结论得到就从小到大排个序按顺序乘即可，需要注意记录和的变量要开个 long long


------------

CODE：


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010],b[100010];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long sum=0;//记录答案
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>b[i];//输入 
		sort(a+1,a+n+1);
		sort(b+1,b+n+1);//排序，注意stl中的排序结尾的地址要是实际最后一个+1
		for(int i=1;i<=n;i++) sum+=a[i]*b[i];//计算
		cout<<sum<<endl; 
	}
 } 
```




---

## 作者：YJY0807qwq (赞：1)

# 一道大水题！
## 题意描述
* 给你两个数组 $a$ 和 $b$ ；
* 你需要重新分别排列这两个数组中的元素；
* 排列后要使 $\sum^n_{i = 1} a_i\times b_i$最大
## 思路分析
对于任意非负实数，给定一个固定的非负实数 $k$ ，若两个非负实数的和为 $k$ ，则它们的差越小，积越大（和一定差小积大原则）

因此将较大的数放一起，将较小的数放一起即可实现差较小。

**证明：**

设和为 $k$ ，有一数为 $n$ ，则另一数为 $k - n$ ，另有一数 $c$。（$0 \le n \le k, c\to 0^+$）

$\therefore n\ \cdot\ (k - n) = nk - n^2$

$(n + c)\ \cdot\ (k - n - c) = (nk - n^2) - (2nc + c^2 - ck)$

$\because n \ge 0,\ k - n \ge 0$

$\therefore nk - n^2 \ge 0$

$\therefore$ 当 $2nc + c^2 - ck \le 0$ 时，有 $(nk - n^2) - (2nc + c^2 - ck) - (nk - n^2) = -(2nc + c^2 - ck) \ge 0 \qquad (\mathrm{I})$ 

即 $(n + c)(k - n - c) \ge n(k - n) \qquad (\mathrm{II})$

$\because c \to 0^+$ ，即 $c > 0$

$\therefore$ 将不等式 $(\text{I})$ 两端同时除以 $c$ 得 $2n + c - k \le 0$ 时，不等式 $(\text{II})$ 成立

即 $2n + c \le k$ 时，不等式 $(\mathrm{II})$ 成立

$\because c\to 0$

$\therefore 2n \le k$ 时，不等式 $(\mathrm{II})$ 成立

故 $n \to \dfrac{k}{2}$ 时，即 $n - (k - n) \to 0$ 时，$n(k - n)$ 最大

## 算法实现
**STL大法好！**

对 $a$ 和 $b$ 分别进行从小到大排序即可( `sort(a + 1, a + n + 1)` 和 `sort(b + 1, b + n + 1)` )
## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int T, n, a[1001], b[1001], total; //T: 数据组数, total: 总和 
    cin>>T;
    for (int i = 1; i <= T; i++)
    {
        cin>>n;
        for (int j = 1; j <= n; j++)
        {
            cin>>a[j];
        }
        for (int j = 1; j <= n; j++)
        {
        	cin>>b[j]; 
        }
        sort(a + 1, a + n + 1);
        sort(b + 1, b + n + 1); //快排 
        for (int j = 1; j <= n; j++)
        {
            total += a[j] * b[j]; //求和 
        }
        cout<<total<<endl;
    }
    return 0; //完美结束 
}
```

---

## 作者：Fleeing_loser (赞：0)

题目给了一定个数的 $a_i$ 和 $b_i$，要求将 $a_i$ 和$b_i$ 重新排列后求一

个 $ans=\sum\limits_{i=1}^{n}a_i \times b_i$ 的值最大。仔细一想，若 

$a_i$ 与 $b_i$ 已经按升序排好序了，那么它们再乘起来的时候答案是最大的。



代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100010],b[100010],ans;
int main()
{
    scanf("%d",&t);
    for(int i=1;i<=t;++i)
    {
    	ans=0;//注意细节，ans每次循环要清零
    	scanf("%d",&n);
    	for(int i=1;i<=n;++i)
    	{
    		scanf("%d",&a[i]);
    	}
    	for(int i=1;i<=n;++i)
    	{
    		scanf("%d",&b[i]);
    	}
    	sort(a+1,a+1+n);
    	sort(b+1,b+1+n);
    	for(int i=1;i<=n;++i)
    	{
    		ans+=a[i]*b[i];//排序后直接加上a,b的乘积就是最大值
    	}
    	printf("%d\n",ans);
    }
    return 0;
}

```


---

## 作者：PeterBei (赞：0)

**和同近积大**原理。

在和相同的情况下，两个因数之间的差越小，它们的积越大。

类似于正方形与长方形之间的关系（周长一定的情况下，图形越接近正方形，该图形的面积越大），具体请自行百度。

顺便介绍几个好习惯：

1.这题要对积求和，虽然按照数据范围，每次的和最大也就是 $1000\times10^2$ 大小，根本超不出 ```int``` 范围，但还是最好把求和的 ```sum``` 设置成 ```long long```。

2.在多组数据测试题中，变量和数组要在使用完一次后进行初始化赋值。

代码：

```
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;

int read()
{
	char c = getchar();
	int f = 1;
	int a = 0;
	while(c != '-' && (c > '9' || c < '0'))
	{
		c = getchar();
	}
	if(c == '-')
	{
		f = -1;
		c = getchar();
	}

	while(c >= '0' && c <= '9')
	{
		a = a * 10 + (c - '0');
		c = getchar();
	}

	return f * a;
}

int a[1010], b[1010];
long long sum = 0;

int main()
{
	int t = read();
	
	while(t--)
	{
		int n = read();
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		sum = 0;
		for(int i = 1; i <= n; i++)
		{
			a[i] = read();
		}
		for(int i = 1; i <= n; i++)
		{
			b[i] = read();
		}
		
		sort(a + 1, a + n + 1);
		sort(b + 1, b + n + 1);
		
		for(int i = 1; i <= n; i++)
		{
			sum = sum + a[i] * b[i];
		}
		
		printf("%d\n", sum);
	}

	return 0;
}
```

---

## 作者：Fengxiang008 (赞：0)

### 算法分析：

贪心。

### 题意理解

给定两个长度为 $n$ 的数组 $a,b$，从 $a,b$ 中取出一组取出一个相乘并累加，使得最后结果的值最大。

### 具体操作：

相信大家小学时都学过 “和一定差小积大”这一原则。

每次从数组 $a,b$ 各取出一个最小数相乘，即是答案。

那如何做到排序呢？

代码实现

```cpp
sort(a+1,a+n+1)//将 a 数组内部排序
```

再看数据范围：

$1 \le N  \le 1000$

$0 \le a_i,b_i \le 10$

那么:

$ans \le 10 \times 10 \times 1000 = 10^5$

远远没超过 int 范围，所以用 int 肯定能过。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005],b[1005],ans;
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
			scanf("%d",&b[i]);
		sort(a+1,a+n+1);//排序 
		sort(b+1,b+n+1);
		ans=0;
		for(int i=1;i<=n;i++)
			ans+=a[i]*b[i];//算乘积 
		printf("%d\n",ans);//输出结果，注意换行 
   }
   return 0;
}
```


---

## 作者：dapingguo8 (赞：0)

### 题意

给定两个长度为 $n$ 的数组 $a,b$，将 $a,b$ 中的元素分别重新排列使得 $ans=\sum\limits_{i=1}^n a_i\times b_i$ 的值最大，求 $ans$ 最大值。

### Solution

- 尽可能将 $a$ 中较大的值与 $b$ 中较大的值匹配，这样可以使得答案最大。

**证明**：假设存在 $a_i<a_j$ 且 $b_i>b_j$，则不放设 $a_j=a_i+d_0$，$b_j=b_i+d_1$。将 $a_i,a_j$ 的值交换，交换前结果为: 

$$a_i b_i+a_jb_j=a_ib_i+(a_i+d_0)(b_i+d_1)=2a_ib_i+a_id_1+b_id_0+d_0d_1$$ 

交换后结果为:

 $$a_ib_j+a_jb_i=a_i(b_i+d_1)+(a_i+d_0)b_i=2a_ib_i+a_id_1+b_id_0$$
 
 两者作差得
 
 $$2a_ib_i+a_id_1+b_id_0+d_0d_1-(2a_ib_i+a_id_1+b_id_0)=d_0d_1$$
 
 因为 $d_0>0$ 且 $d_1<0$，可得 $d_0d_1<0$。因此交换后答案更大。
 
 这样，只需要将 $a,b$ 进行排序，然后逐个计算答案即可。
 
 ### Code
 
 ```cpp
 #include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int a[n+5],b[n+5];
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
		}
		sort(a+1,a+n+1);
		sort(b+1,b+n+1);
		int ans=0;
		for(int i=1;i<=n;i++){
			ans+=a[i]*b[i];
		}
		cout<<ans<<endl;
	}
}
 ```

---


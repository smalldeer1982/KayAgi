# [ABC133B] Good Distance

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc133/tasks/abc133_b

$ D $ 次元空間上に $ N $ 個の点があります。

$ i $ 番目の点の座標は $ (X_{i1},\ X_{i2},\ ...,\ X_{iD}) $ です。

座標 $ (y_1,\ y_2,\ ...,\ y_D) $ の点と座標 $ (z_1,\ z_2,\ ...,\ z_D) $ の点の距離は $ \sqrt{(y_1\ -\ z_1)^2\ +\ (y_2\ -\ z_2)^2\ +\ ...\ +\ (y_D\ -\ z_D)^2} $ です。

$ i $ 番目の点と $ j $ 番目の点の距離が整数となるような組 $ (i,\ j) $ $ (i\ <\ j) $ はいくつあるでしょうか。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 2\ \leq\ N\ \leq\ 10 $
- $ 1\ \leq\ D\ \leq\ 10 $
- $ -20\ \leq\ X_{ij}\ \leq\ 20 $
- 同じ座標の点は与えられない。すなわち、$ i\ \neq\ j $ ならば $ X_{ik}\ \neq\ X_{jk} $ なる $ k $ が存在する。

### Sample Explanation 1

以下のように距離が整数となる点の組は $ 1 $ 組です。 - $ 1 $ 番目の点と $ 2 $ 番目の点の距離は $ \sqrt{|1-5|^2\ +\ |2-5|^2}\ =\ 5 $ で、これは整数です。 - $ 2 $ 番目の点と $ 3 $ 番目の点の距離は $ \sqrt{|5-(-2)|^2\ +\ |5-8|^2}\ =\ \sqrt{58} $ で、これは整数ではありません。 - $ 3 $ 番目の点と $ 1 $ 番目の点の距離は $ \sqrt{|-2-1|^2+|8-2|^2}\ =\ 3\sqrt{5} $ で、これは整数ではありません。

## 样例 #1

### 输入

```
3 2
1 2
5 5
-2 8```

### 输出

```
1```

## 样例 #2

### 输入

```
3 4
-3 7 8 2
-12 1 10 2
-2 8 9 3```

### 输出

```
2```

## 样例 #3

### 输入

```
5 1
1
2
3
4
5```

### 输出

```
10```

# 题解

## 作者：lgvc (赞：6)

## 解法：

观察到本题中 $N$,$D$ 都不超过 $10$，故考虑暴力。

枚举 $i,j$，计算： $(X_{i,1}-X_{j,1})^2+(X_{i,2}-X_{j,2})^2+…+(X_{i,D}-X_{j,D})^2$。

再判断该数是否为平方数即可。

code:

```cpp
#include <bits/stdc++.h>

signed main(void) {
	int N,D,ans=0,x[12][12];
	scanf("%d %d",&N,&D);
	for(int i=1;i<=N;i++) {
		for(int j=1;j<=D;j++) {
			scanf("%d",&x[i][j]); 
		}
	}
	for(int i=1;i<=N;i++) {
		for(int j=i+1;j<=N;j++) {
			int sum=0;
			bool flag=0;
			for(int k=1;k<=D;k++) {
				sum+=(x[i][k]-x[j][k])*(x[i][k]-x[j][k]);
			}
			for(int i=1;i*i<=sum;i++) {
				if(i*i==sum) {
					flag=1;
				}
			}
			if(flag) {
				ans++;
			}
		}
	}
	printf("%d",ans);
    return 0;
}
```


---

## 作者：AgrumeStly (赞：1)

### solution

看到数据后暴力即可，暴力模拟，算出每个点的距离，然后判断若为整数就记录即可。



### code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#define int long long
using namespace std;
const int NR = 15;
int n, d, ans;
int x[NR][NR];
int sqr(int a) {
	return a * a;
}
signed main() {
	cin >> n >> d;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= d; j++)
			cin >> x[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++) {
			double dd = 0;
			for (int k = 1; k <= d; k++)
				dd += sqr(x[i][k] - x[j][k]);
			dd = sqrt(dd);
			if (dd == (int)dd) ans++;
		}
	cout << ans << endl;
	return 0;
}
```



---

## 作者：3a51_ (赞：0)

### 题目大意

$D$ 维中有 $n$ 个点，求两点之间距离为整数的对数。

### 思路分析

数据不大，考虑枚举。

枚举两个点，计算距离时只需判断是否为整数即可。

怎么判断呢？

观察式子，发现只有根号才会产生小数，所以我们可以先计算 $(y_1-z_1)^2+(y_2-z_2)^2+...+(y_D-z_D)^2$ ，然后判断是否为平方数即可。

### 坑点

第二层循环的 $j$ 一定要在 $i+1$ 开始，不然 $i,j$ 算一遍， $j,i$ 又算了一遍，会产生重复。

平方数判断时记得加上```int(sqrt(ans))*int(sqrt(ans))==ans```，如果只是```sqrt(ans)*sqrt(ans)==ans```就会产生错误。

### code

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int a[15][15],cnt;
int main()
{
	int n,d;
	cin>>n>>d;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=d;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			int ans=0;
			for(int k=1;k<=d;k++)
				ans+=(a[i][k]-a[j][k])*(a[i][k]-a[j][k]);
			//cout<<i<<" "<<j<<" "<<ans<<endl;
			if(int(sqrt(ans))*int(sqrt(ans))==ans)
				cnt++;	
		}
	cout<<cnt;
	return 0;
}
```

---

## 作者：Wuyanru (赞：0)

一道非常适合用来放松心情的题。

首先我们来看数据范围,$ n\le 10 $,$ d\le10 $,然后我们就可以暴力枚举了。

过程：我们可以设 $ dis_{i,j} $ 表示点 $ i $ 与点 $ j $ 之间的距离，那么 $ dis_{i,j}=\sqrt{\left(y_1-z_1\right)+\left(y_2-z_2\right)+\cdots+\left(y_D-z_D\right)} $,所以说 $ dis_{i,j}^2=\left(y_1-z_1\right)+\left(y_2-z_2\right)+\cdots+\left(y_D-z_D\right) $。

所以，如果两个数之间的距离是整数，那么就必然有 $ \left\lfloor\sqrt{dis_{i,j}}\right\rfloor^2=dis_{i,j} $。

所以我们暴力枚举一下就可以结束本题。

AC代码：
```
#include<cstdio>
#include<cmath>
using namespace std;
int a[11][11];
int n,d;
int ans;
int main() {
	scanf("%d%d",&n,&d);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=d; j++)
			scanf("%d",a[i]+j);
	for(int i=1; i<=n; i++)
		for(int j=i+1; j<=n; j++) {
			int num=0;
			for(int k=1; k<=d; k++)
				num+=((a[i][k]-a[j][k])*(a[i][k]-a[j][k]));
			if((int)sqrt(num)*(int)sqrt(num)==num)
				ans++;
		}
	printf("%d",ans);
	return 0;
}
```
感谢观看！

---

## 作者：Loxilante (赞：0)

不愧是ABC的B题，只用根据题意模拟枚举即可啦

另外补充一下数据范围:
- $2 \leq N \leq 10$
- $2 \leq D \leq 10$
- $-20 \leq X_{ij} \leq 20$

```cpp
#include<bits/stdc++.h>
#define int ll
using namespace std;
typedef long long ll;
int w[20][20];
signed main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, d, cnt = 0;              // 计数器记得清0~ 
	cin>>n>>d;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < d; j++)
			cin>>w[i][j];
	for(int i = 0; i < n; i++)
		for(int j = i+1; j < n; j++)  // 双重循环枚举对数 注意 i < j 
		{
			int dist = 0;             // 距离也要清0~ 
			for(int k = 0; k < d; k++) dist += (w[i][k]-w[j][k])*(w[i][k]-w[j][k]);
			if (sqrt(dist) == (int)sqrt(dist)) cnt++;  // 判断距离是否为整数~
		}
	cout<<cnt<<endl;
	return ~~(0-0); // 完结撒花~
}
```


---


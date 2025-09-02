# [ABC057D] Maximum Average Sets

## 题目描述

你有 $n$ 个物品，第 $i$ 个物品的价值为 $v_i$。
你需要从这些物品中选择 $A$ 个以上，$B$ 个以下的物品，计算出所选物品平均值的最大值，并求出能使选择物品的平均值最大的选择方法有几种。

## 说明/提示

#### 数据规模与约定
对于 $100\%$ 的测试点数据，保证：
- $1\le a\le b\le n\le50$
- $1\le v_i\le10^{15}$
- $v_i$ 全部为整数。

#### 样例 $1$ 解释
选择第 $4$ 个物品和第 $5$ 个物品，价值的平均值是最大的，所以第一行输出 $4.5$。另外，由于除此之外的物品的选择方法中没有价值平均值为 $4.5$ 的东西，所以第二行输出 $1$。

#### 样例 $2$ 解释
物品价值平均值最大的物品的选择方法可能有多个。

---
翻译：@[Wuzetong](https://www.luogu.com.cn/user/1219873)

## 样例 #1

### 输入

```
5 2 2
1 2 3 4 5```

### 输出

```
4.500000
1```

## 样例 #2

### 输入

```
4 2 3
10 20 10 10```

### 输出

```
15.000000
3```

## 样例 #3

### 输入

```
5 1 5
1000000000000000 999999999999999 999999999999998 999999999999997 999999999999996```

### 输出

```
1000000000000000.000000
1```

## 样例 #4

### 输入

```
50 1 50
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1```

### 输出

```
1.000000
1125899906842623```

# 题解

## 作者：jzzcjb (赞：9)

### Description：

从n个数中选A~B个数，求所选数平均数的最大值，和在平均值最大的情况下方案数。（值相同的数认为不同）

### solution：
贪心：
要使平均数最大，选的数一定越大越好。**所以先把n个数从小到大排序，贪心的选取前A个数，此时平均数一定是最大的**。因为剩下的数都小于等于选出的数，答案只能越来越劣，不会更优。

然后考虑方案数，

假如说你拥有的序列为（排序后）：
```
7 6 6 5 4 4 4 4 3 2 2 2 1 A=6 B=8 那么你选出的A个数是
7 6 6 5 4 4 
```
发现：哇，有好多个6，不过都要选啊

发现：哇，有好多个2，不过都不选啊

发现：哇，有好多个4，选哪两个都一样啊

发现：哇，好像只能选2个4啊，因为选多了就拉低平均分，选少了不达标。

所以，**方案数只与“临界值”的那堆数有关**，方案数为
**$\Large {C}_{\tiny{\text{临界值数的个数}}}^{\tiny{\text{临界值数在前A个数中的个数}}}$ **


不过有一种特殊情况，

```
2 2 2 2 1 1 A=2,R=5
```

因为临界值和最大值相等，所以没必要一定选A个，还可以选A+1,A+2…… 只要不选到其他数，反正不影响平均值。
所以要特判这种情况，方案数为$\Large\sum\limits_{i=A}^{B}C_{\tiny{\text{临界值数的个数}}}^{i}$。

### code：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
int n,L,R,a[55],ans1,ans2,cnt1,cnt2;
bool cmp(int a,int b){return a>b;}
int C[55][55];
void init(){
	C[0][0]=1;
	for(int i=1;i<=50;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
		C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
}
signed main(){
	init();
	cin>>n>>L>>R;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+1+n,cmp);//从大到小排序
	for(int i=1;i<=L;i++) ans1+=a[i];//求和，求平均值
	for(int i=1;i<=n;i++) if(a[i]==a[L]) cnt1++;//临界值数个数
	for(int i=1;i<=L;i++) if(a[i]==a[L]) cnt2++;//1~L中临界值数个数
	if(a[1]==a[L])//特判
		for(int i=L;i<=R;i++) ans2+=C[cnt1][i];
	else ans2=C[cnt1][cnt2];
	printf("%lf\n%lld",(double)ans1/L,ans2);
}
```

---

## 作者：ycy1124 (赞：4)

### 题意

在 $n$ 个物品里面选择 $a \sim b$ 个，求最大的平均值与在平均值最大的情况下有多少个方案数。

### 想法

首先想贪心，贪心的思路非常简单，当然是选取当前最大的 $a$ 个数的平均值为答案。

贪心证明：假如不是选取当前最大的 $a$ 个，当然不可能把这 $a$ 个数换成比它小的数。假如我们多取一个，那么多取的一定是**不大于平均值**的，所以多取的答案**一定**是小于等于取 $a$ 个最大的数的答案。

接下来看如何求方案数。

因为取得最大的 $a$ 个数当中，最小的那个数可能有很多**重复的**，但是不会取完所有的，所以如何取最小数的方案数就是最终的方案数。

一般情况下，方案数等于

$$
\Large{C}_{\small{最小数个数}}^{\small{最小数在这 a 个数当中占的个数}}
$$

在所有数相等的情况下，方案数等于

$$
\Large\sum_{i=a}^{i\le b} C_{\small{最小数的个数}}^{i}
$$

但是直接计算排列组合可能会爆 `long long` 所以需要提前预处理出来。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long w[51],work[51][51];//输入的数与预处理的排列组合。
bool cmp(long long x1,long long x2){//自定义从大到小排序。
	return x1>x2;
}
int main(){
	long long n,a,b;
	for(int i=1;i<=50;i++){
		work[i][0]=1;//从 i 个数里选取 0 个的方案数为 1。
		for(int j=1;j<=i;j++){
			work[i][j]=work[i-1][j-1]+work[i-1][j];
            //从 i 个里面选 j 个的方案数等于
            //从 i-1 个数里面选 j-1 个数的方案数加上
            //从 i-1 个数里面选 j 个数的方案数。
			if(i==j){//从 i 个数里面选 i 个数的方案数为 1。
				work[i][j]=1;
			}
		}
	}
	scanf("%lld%lld%lld",&n,&a,&b);
	for(int i=1;i<=n;i++){
		scanf("%lld",&w[i]);
	}
	long long js=0;
	double ans;
	sort(w+1,w+n+1,cmp);//排序
	int bj=51;
	for(int i=1;i<=a;i++){
		js+=w[i];
		if(w[i]==w[a]){
			bj=min(i,bj);//记录最早出现的最小数来计算需要多少最小数。
		}
	}
	ans=1.000000*js/a;
	printf("%.6lf\n",ans);//输出最大平均值。
	long long ans2=0;
	if(w[a]==ans){//特判。
		int ww=0;
		for(int i=1;i<=n;i++){
			if(w[i]==w[a]){//计算最小数个数。
				ww++;
			}
		}
		for(int i=a;i<=b;i++){
			ans2+=work[ww][i];//计算方案数。
		}
		cout<<ans2;//输出答案。
		return 0;
	}
	for(int i=1;i<=n;i++){
		if(w[i]==w[a]){
			ans2++;
		}
	}
	cout<<work[ans2][a-bj+1];//输出答案。
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/173613685)。

---

## 作者：qi__ (赞：2)

## 题解
[**题目**](https://www.luogu.com.cn/problem/AT_abc057_d)

这道题的数据真的很奇葩啊，明明有很好的解法但还是 $n \leq 50$。

本篇题解主要讲一讲大佬们不讲的东西。

1. 组合数计算。

我们都知道，$C^m_n$ 代表：

>从 $n$ 个不同元素中，任取 $m$（$m \leq n$）个元素并成一组，叫做从 $n$ 个不同元素中取出 $m$ 个元素的一个组合；从 $n$ 个不同元素中取出 $m$（$m \leq n$）个元素的所有组合的个数，叫做从 $n$ 个不同元素中取出 $m$ 个元素的组合数。

它的计算方法：
$$
C^m_n=\frac{P^m_n}{P^m_m}=\frac{n!}{m!(n-m)!},C^0_n=1;
$$

还有递推式：
$$
C^m_n=C^{m-1}_{n-1}+C^m_{n-1}
$$

有了递推式，就不用再一遍又一遍地算阶乘了。

---

2. 懒人方法：sort（P 党请划走）

sort 函数是 STL 中自带的。需要 algorithm 库（当然万能头文件里也有）。

用法：
```cpp
bool cmp(int a,int b){//比较函数
	return a>b;//当然可以是别的
}
int a[1001];//要排序的数组
int n;//数组长度
sort(a+1,a+n+1,cmp);//这就好了
```
---
说回本题，第一问很简单，排序后取前 $a$ 个就行。

第二问，本题的重点。

有一个东西叫“临界值”，是前 $a$ 大的数中最小的。也就是 $arr_a$。设前 $a$ 个 元素里有 $x$ 个和“临界值”相等，再整个数组里有 $y$ 个元素和“临界值”相等。仔细一想，你就会发现：
>这些和“临界值”相等的元素似乎是可以互相替换的呀！

那答案就是 $C^x_y$ 吗？

你说的对，但是你还是不能全对。

有一种特殊情况，那就是“临界值”和 $arr_1$ 相等，也就是 $arr_1=arr_a$。这时我们只要不影响平均值，而且个数不超过 $b$ 就行。那公式就变成了 $\sum\limits_{i=a}^{b}C^i_x$。

好了，就是这么简单。

---
最后是 ~~你们最喜欢的~~ 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int c[51][51],n,a,b;
long long arr[51],avg=0.00,ans=0.00,cnt=0;
bool cmp(long long a,long long b){
	return a>b;
}
int main(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)cin>>arr[i];
	sort(arr+1,arr+n+1,cmp);
	for(int i=1;i<=a;i++)ans+=arr[i];
	ans/=(double)(a);
	printf("%lf\n",ans);
	/*---------------*/
	c[0][0]=1;
	for(int i=1;i<=50;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++)
			c[i][j]=c[i-1][j]+c[i-1][j-1];
	}
	int c1=0,c2=0;
	for(int i=1;i<=n;i++)if(arr[i]==arr[a])c1++;
	for(int i=1;i<=a;i++)if(arr[i]==arr[a])c2++;
	if(arr[1]==arr[a])
	for(int i=a;i<=b;i++)cnt+=c[c1][i];
	else
	cnt=c[c1][c2];
	cout<<cnt<<endl;
	return 0;
}
```

---

## 作者：George222 (赞：1)

[或许更好的阅读体验](https://george110915.github.io/%5BABC057-D%5D%20sol/)

## 思路

考虑贪心算法。

---

对于一个平均数，要想使平均数大就要**取尽可能大的数**，否则一定会拉低平均值。

而且取任何比 $v_A$ 小的数一定会拉低平均值，所以我们选择只取前 $A$ 大的值。

$$avg = (\sum_{i = 1}^{A} \max(v_{i})) \div A$$

---

继续解决方案数部分。

对于方案数的增加，只有多个与 $v_A$ 相同的值才能起效果。

为什么呢？因为你肯定要选所有比 $v_A$ 大的值，而 $v_A$ 就很尴尬，因为可能 $v_{A - 1}, v_{A + 1}, v_{B} \dots$ 都等于 $v_A$，而方案数，就是将 $1 \sim A$ 中的 $v_A$ 替换为其他就是方案数。

$$cnt = \operatorname*{C}_{1 \sim n 中 v_A 的个数}^{1 \sim A 中 v_A的个数}$$

但是你发现，为什么 AC 不了？因为有一种特殊情况。

如果 $v_A$ 与 $\max(v_i)$ 相等，那么我们可以选 $A \sim B$ 中任意多个 $v_A$，不影响平均值。

$$cnt = \sum_{i = A}^{B} \operatorname*{C}_{1 \sim n 中 v_A 的个数}^{i}$$

## [AC code](https://www.luogu.com.cn/record/177997533)


```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
int n, a, b;
int v[55];
bool cmp(int x, int y) {
	return x > y;
}

int C[55][55];
void preC() // 预处理出 C(x, x) 的数量。 
{
	C[0][0] = 1;
	for (int i = 1; i <= 50; i++)
	{
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1]; // 组合数基本性质。 
	}
	return ; 
}

signed main()
{
	scanf("%lld %lld %lld", &n, &a, &b);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &v[i]);
	sort(v + 1, v + n + 1, cmp);
	preC();
	
	int ave = 0;
	for (int i = 1; i <= a; i++)
		ave += v[i]; // 求初始 1 ~ A 的平均数。 
	
	int cnt = 0;
	int cntn = 0, cnta = 0; // 求 1 ~ n / 1 ~ A 中等于 v[A] 值的个数。
	for (int i = 1; i <= n; i++)
	{
		if (v[i] == v[a])
			cntn++;
	}
	for (int i = 1; i <= a; i++)
	{
		if (v[i] == v[a])
			cnta++;
	}
	
	// 开始计算方案数。
	if (v[1] == v[a])
	{
		// 如果 v[A] 与最大值相等，则将 A ~ B 个数区间所有的最大值方案取出（贪心）。 
		for (int i = a; i <= b; i++)
			cnt += C[cntn][i];
	}
	else
		cnt = C[cntn][cnta]; // 如果不，则将 1 ~ A 中所有的 v[A] 替换的方案数。
	
	printf("%lf\n%lld", (double)ave / a, cnt);
	return 0; 
}
```

---

## 作者：jhdrgfj (赞：1)

2023.4.25 修改几处 latex。

# 解题思路

对于第一问，求平均值最大，不难想到可以使用贪心算法，将原数列从小到大排序，后 $A$ 个元素的平均值即为答案。

难点主要在第二问，我们先设原数列中第 $A$ 大的数为 $x$，$x$ 的个数为 $d$，比 $x$ 大的数个数为 $c$。则我们需要在 $d$ 个数中选择 $A - c$ 个数，因为所有数相等，所以我们使用组合数而不是排列数，即答案为 $C_{d}^{A-c}$。

特别的，如果使用上述的思路，那么样例 #4 会输出 $50$。这是因为我们只选了 $A$ 个 $x$，而选择 $A$ 至 $B$ 个 $x$ 都是没问题的。所以对于所有被选中的数都相等的情况下，答案应为 $\displaystyle\sum_{i=A}^B C_{d}^{i}$。 

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[55],ans2,n,k,b,c,d;
long long ca[55][55]; //ca 数组用于存放组合数值
double ans1;
int main()
{
	ca[0][0]=1;
	for(int i=1;i<=52;i++){
		ca[i][0]=1;
		for(int j=1;j<=i;j++){
			ca[i][j]=ca[i-1][j]+ca[i-1][j-1];
		}
	}      //初始化组合数的值
	cin>>n>>k>>b;
	for (int i=0;i<n;i++) cin>>a[i];
	sort(a,a+n);
	for (int i=n-1;i>=n-k;i--){
		ans1+=a[i];
	}      //计算第一问
	for (int i=0;i<n;i++){
		if (a[i]>a[n-k]) c++;
		if (a[i]==a[n-k])d++;
	}           //统计 c 和 d 的值
	ans1/=(double)k;
	if (c){    //选中的数有不一样的情况
		ans2=ca[d][k-c];
	}else{
		for (int i=k;i<=b;i++){
			ans2+=ca[d][i];
		}   //选中的数都一样的情况
	}
	printf("%lf\n%lld\n",ans1,ans2);
} 
```

---

## 作者：abensyl (赞：1)

原题：[ABC057D Maximum Average Sets ](https://www.luogu.com.cn/problem/AT_abc057_d)。

本人有与其他题解不一样的做法。

## 思路

读入时，用 map 存储每个数字的出现次数。

从大到小遍历每个数字，假设遍历到的数字是 $c$，目前的数字 $c$ 共有 $x$ 个，目前数字的数量是 $tot$。

如果加上所有数字 $c$ 之后 $tot$ 就大于等于 $a$ 了，就加上这个数字，平均值非常容易求出，但是方案书如何求呢：

- 如果这个数字是第一个，那么无论你选多少都不会拉低平均值，但是注意，最多选择 $b$ 个，那么我们可以选择任意多个，通过组合数进行计算，方案数为 $\sum^{a-tot}_{\min(b,x)}C^i_x$ 种；  
- 否则只能选择还差的个数，选择的方式可以通过组合数进行计算，方案数为 $C^{a-tot}_x$ 种。

**注意：不开 long long 的话 AT 评测机有可能想见你的祖宗！**

## 代码：
```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 2e5 + 2;

int cnm(int a, int b) {
  int res = 1;
  for (int i = 1, j = b; i <= a; ++i, --j) res = res * j / i;
  return res;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  map<int, int> mp;
  int n, a, b;
  cin >> n >> a >> b;
  for (int i = 1, tt; i <= n; ++i) cin >> tt, mp[tt]++;
  int tot = 0, sum = 0;
  map<int, int>::reverse_iterator i;
  for (i = mp.rbegin(); i != mp.rend(); ++i) {
    auto c = *i;
    cerr << c.first << ' ' << c.second << '\n';
    if (tot + c.second >= a) {
      sum += (a - tot) * c.first;
      long double ta = sum * 1. / a;
      int tb = 0;
      if (tot)
        tb = cnm(a - tot, c.second);
      else
        for (int i = a - tot; i <= min(c.second, b); ++i)
          tb += cnm(i, c.second);
      cout << fixed << setprecision(10) << ta << '\n' << tb << '\n';
      return 0;
    }
    tot += c.second;
    sum += c.first * c.second;
  }
  return 0;
}
```

---

## 作者：cheatme (赞：0)

## 题目描述
有 $n$ 个物品，选择 $A$ 个以上 $B$ 个以下的物品，使得平均数最大，先求最大平均数，再求最大平均数的最大方案数。
## 题目分析
分析题目，本题的标签为贪心和排序，所以可以先把 $n$ 个数从大到小排序，在考虑贪心策略，可知当你选 $A$ 个物品时，平均数最大，因为选择的物品体积最大，个数最少，然后记录临界值的个数为 $X$，临界值在 $A$ 个物品内的个数 $Y$，方案数即为 $C_Y^X$ 种。

不过还要考虑一种特殊情况，就是当选的物品体积都相同时，即最大的物品体积等于第 $A$ 个物品的体积，这时不一定只选 $A$ 个物品，每次还可以选 $A$ 和 $B$ 之间的随意个数，所以需要特判一下。
## [Code](https://www.luogu.com.cn/record/178421706)
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=100;
int n,a,b,v[N],c[N][N];
bool cmp(int a,int b)
{
	return a>b;
}
void init()
{
	c[0][0]=1;
	for(int i=1;i<=50;++i)
	{
		c[i][0]=1;
		for(int j=1;j<=i;++j)
			c[i][j]=c[i-1][j]+c[i-1][j-1];
	}
}
void solve()
{
	cin>>n>>a>>b;
	for(int i=1;i<=n;++i) cin>>v[i];
	sort(v+1,v+1+n,cmp);//大小排序
	int sum=0,res=0;
	for(int i=1;i<=a;++i) 
	{
		sum+=v[i];//求最大平均数
		if(v[i]==v[a]) ++res;//需要的v[a]的个数
	}
	printf("%.6lf\n",sum*1.000000/a);
	int cnt=0;//记录和v[a]相等的数的个数(总个数)
	for(int i=1;i<=n;++i) if(v[i]==v[a]) ++cnt;
	int ans=0;//记录方案数
	if(v[1]==v[a])//特判
	{
		for(int i=a;i<=b;++i) ans+=c[cnt][i];
	}
	else ans=c[cnt][res];
	cout<<ans<<'\n';
}
signed main()
{
	init();//预处理
	solve();
	return 0;
}

```

---

## 作者：_WF_ (赞：0)

## 题意分析
  在 $n$ 个数中选 $a$ ~ $b$ 个数，使 **平均值最大** ，并输出 **平均值最大** 的 **个数** 。
## 题意理解
选择使用 **贪心** 算法，可以想到，将 $n$ 个数排序后 **从大往小** 取 $k$ 个数（ $a \le k\le b$ ），即为最大平均值，再计算 **组合数** 便可解决。

-----
关于 **组合数** 采用 **杨辉三角** 预处理的方式。

## 代码展示

```
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
int n, a, b;
long long s[60];
long long c[60][60];
map<long long, int> id;

void solve(int n){  //求组合数
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= i; j++){
            if (!j) c[i][j] = 1;
            else c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++){
        cin >> s[i];
        id[s[i]]++;  //记录出现次数
    }
    solve(n);
    sort(s + 1, s + n + 1, greater<long long>());//从大到小 
    long long cnt = 0;
    long long ans = 0;
    for (int i = 1; i <= a; i++){
        ans += s[i];
        if (s[i] == s[a]) cnt++;
    }
    long long res = 0;
    long long x = s[a];
    if (cnt < a) res = c[id[x]][cnt];
    else {
        for (int i = a; i <= b && i <= id[x]; i++){
            res += c[id[x]][i];
        }
    }

    printf("%.6f\n", (double)ans / a);
    printf("%lld\n", res);

    return 0;
}

//		_/				  _/            _/              _/_/_/_/
//		_/				  _/    _/_/    _/              _/
//		_/_/_/   _/  _/    _/  _/  _/  _/               _/_/_/
//		_/  _/   _/  _/    _/  _/  _/  _/               _/
//		_/_/_/   _/_/_/     _/_/    _/_/    _/_/_/_/    _/
//					 _/
//				 _/_/_/          qwq
```

---

## 作者：ZYH_XB (赞：0)

---
## 题意

[在查看题解之前先读题](https://www.luogu.com.cn/problem/AT_abc057_d)

本题难度：普及+/提高（绿题）~~很简单~~

**我们转入正题**：在 $n$ 个物品里面选择 $a∼b$ 个，求最大的平均值与在平均值最大的情况下有多少个方案数。


---


## 说明：
使用贪心： 要使平均数最大，选的数一定越大越好。所以先把 $n$ 个数从小到大排序，贪心的选取前 $A$ 个数，此时平均数一定是最大的。因为剩下的数都小于等于选出的数，答案只能越来越劣，不会更优。

注意有一种特殊情况：

```cpp
2 2 2 2 1 1 A=2,R=5
```

因为临界值和最大值相等，所以没必要一定选 $A$ 个，还可以选 $A+1,A+2⋯$ 只要不选到其他数，反正不影响平均值。 所以要特判这种情况。

#### 注意要开 long long ! ! !

---


## 代码：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
long long n,u,v,a[505],ans1,ans2,cnt1,cnt2;//新建变量
//再次强调注意开long long！！！
bool cmp(long long a,long long b){
    return a>b;//sort排序
}
long long c[505][505];
int main(){
    c[0][0]=1;
	for(int i=1;i<=50;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
		    c[i][j]=c[i-1][j]+c[i-1][j-1];
		}
	}
	cin>>n>>u>>v;
	for(int i=1;i<=n;i++) cin>>a[i];//输入
	sort(a+1,a+1+n,cmp);//从大到小排序
	for(int i=1;i<=u;i++) ans1+=a[i];//求和，求平均值
	for(int i=1;i<=n;i++){
	    if(a[i]==a[u]) cnt1++;
    }
	for(int i=1;i<=u;i++){
	    if(a[i]==a[u]) cnt2++;
    }
	if(a[1]==a[u]){//特判
		for(int i=u;i<=v;i++){
		    ans2+=c[cnt1][i];
        }
	}else{
	    ans2=c[cnt1][cnt2];
    }
	printf("%lf\n%lld",(double)ans1/u,ans2);
	return 0;//程序完美~~~~~~~~~~~~结束
}
```

---
本人写题解不易，花了很多时间，烦请管理员批准。

完结撒花！！！（如有漏洞，请私信我）

我的[AC代码](https://www.luogu.com.cn/record/172622712)

---

## 作者：Hacker_Cracker (赞：0)

## AT_abc057_d Maximum Average Sets 题解
**前置知识：卡特兰数**
### Solution
#### 题目概述
有一个 $n$ 个数的数组，让你最少选 $a$ 个数，最多选 $b$ 个数，最大化你所选的这些数的最大值，而且让你求出能选出该最大值的方案数。

#### 思路
本题采取贪心策略。

+ 第一问：我们先将数组从大到小排序。此时数组里的元素**单调不降**，所以选前 $k$ 个数的平均值肯定比选前 $k+1$ 个数的平均值大。那么我们就把前 $a$ 大的数组元素加起来求平均值，肯定是最优解。
+ 第二问：

以一组数据为例：

```
9 8 8 8 7 6 6 6 6 4 3 n=11 a=6 b=9
```

其中，我们不难发现，选取前 $6$ 个数必然是最优解，也就是说，选取 $1$ 个 $9$ , $3$ 个 $8$ ，$1$ 个 $7$ ， $1$ 个 $6$ 。显然， $9$ 、 $8$ 、 $7$ 的选取个数无法再改变，否则将不能满足最优解的要求。也就是说，临界值 $6$ 决定了最终方案数。我们需要求出：**在所有临界值中选取 $k$ 个临界值的方案数，其中 $k$ 是 $1$ 到 $a$ 中临界值的个数**。

即：枚举 $1$ 到 $a$ 统计最优解内需要有几个临界值,记作 $cnt1$ ，然后遍历整个数组，寻找临界值的个数 $cnt2$ ，最后求 $C^{cnt1}_{cnt2}$ ，即~~大名鼎鼎的~~卡特兰数。

需要注意的是，有一种特殊情况不符合我们刚才推导的公式，如本组数据：

```
7 7 7 7 7 7 3 2 1 n=9 a=3 b=5
```

此时， $1$ 到 $b$ 中全部是临界值，也就是说，临界值等于最大值。在这种情况下，选 $a$ 个，选 $a+1$ 个……选 $b$ 个都是等价的。所以此时的公式为：
$$\displaystyle{\sum^{b}_{a}C^{i}_{cnt2}}$$

### [AC](https://atcoder.jp/contests/abc057/submissions/56161160) Code
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1<<6;
long long a[N],dp[N][N],res1,res2,tot_all,tot_in_range;//卡特兰数极大，不开 long long 见祖宗
void calc_Catalan(void){//求数据范围内全部的卡塔兰数。
	for(int i=0;i<=50;i++) dp[i][0]=1;
	for(int i=1;i<=50;i++){
		for(int j=1;j<=i;j++){
			dp[i][j]=dp[i-1][j]+dp[i-1][j-1];
		}
	}
	return;
}
int main(){
	int n,l,r;
	cin>>n>>l>>r;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1,greater<>());//自大到小排序
	for(int i=1;i<=l;i++) res1+=a[i];
	printf("%.6lf\n",1.0*res1/l);
	calc_Catalan();
	for(int i=1;i<=n;i++){
		if(a[i]==a[l]) tot_all++;//寻找 1~a 里的临界值个数
		if(a[i]==a[l]&&i<=l) tot_in_range++; //寻找全部的临界值个数
	}
	if(a[1]==a[l]){//特判：临界值=最大值
		for(int i=l;i<=r;i++){
			res2+=dp[tot_all][i];
		}
	}else{
		res2=dp[tot_all][tot_in_range];
	}
	cout<<res2<<endl;
	return 0;
}
```

---

## 作者：Breath_of_the_Wild (赞：0)

题意：有 $n$ 个整数，你需要从中选出 $x$ 个，满足 $x\in [L,R]$ 且这 $x$ 个数的平均数最大，并求出这个平均数，以及能够使 $x$ 个数的平均值为最大平均值所选的方案个数。

考虑贪心。显然，我们可以先将数组从大到小排序，从中选择前 $L$ 个，即最大的 $L$ 个数。因此平均值就求出来了。

记位于 $L$ 位置的数为 $l$，$l$ 的个数为 $k_1$ 个，比 $l$ 大的数有 $k_2$ 个。

然后思考如何求方案数。注意到方案个数只跟第 $l$ 有关。则总共有 $\dbinom{L-k_2}{k_1}$ 种选法。$L-k_2$ 就是第 $l$ 能填的位置个数。

特殊地，如果第 $l$ 与第 $1$ 大的数相等，那么我们可以随便取，共 $\sum\limits_{i=L}^{R}\dbinom{i}{k_1}$ 种。

然后就没有然后了。

---

## 作者：cloudann (赞：0)

## 题意描述

有 $n$ 个数，可以选取最少 $A$ 个最多 $B$ 个，使得所选的数的平均值最大，求可能的最大平均值和在平均值最大的情况下的方案数。
## 思路简析
定义 $buck_x$ 为 $x$ 元素出现次数。

定义 $pre_x$ 为前 $x$ 大的元素中第 $x$ 个元素 $num_x$ 出现次数。

想要选择 $k$ 个数的平均值最大，显然这里需要排序选择最大的 $k$ 个数，对应的方案数即为  ${buck_{num_x} \choose pre_x}$，可以从所有的 $num_x$ 中选出当前 $num_x$ 出现的次数。

例如，$\left[2,2,2,2\right]$ 选择 $2$ 个元素，则需要从 $4$ 个 $2$ 中选择出两个 $2$ 组成最大的 $\left[2,2\right]$。

## 数据范围分析

本题，$A,B$ 数据在 $50$ 以内，但每个元素大小为 $10^{15}$。 

最坏情况下，总和最大为 $5\times 10^{16}$，因此超过了 `double` 的存储范围。

但对于最小值的情况， $1\div 50=0.02$， 因此可以粗略估算对于小数位我们可以保留 $2$ 位小数即可保留精度。

1. 根据上述思路，我们可以对结果左移两位使用 `long long` 来存储平均值（完全可以 $a,b$ 取 $5000$，左移三位卡掉 `long long`）。 
2. 小数除法运算的原理。
3. 这里组合数求解可以利用杨辉三角等于对应的组合数。
4. 注意本题数据范围，元素最大 $10^{15}$，所以记录元素时使用 `unordered_map<long long,int>` 比较好
## 思路1 
1. 计算求和左移两位的结果。
2. 整除当前选定的数字个数。
3. 右移两位输出个数，并输出低两位。

### __int128 
一开始没算的那么细，而且当时担心组合数会不会爆，后面想了一下，组合数大小应该是 $2^k$ 所以 $50$ 行爆不了 `long long`。

`__int128` 是一种特殊的数据类型，专门用于存储128位二进制位的整数类型，长度约为十进制的 $40$ 位。

缺点是不是基础数据类型所以需要专门写对应的输入输出函数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll num[200]; 
unordered_map<ll,int> buck;
ll pre[200];
__int128 dp[100][100];
string fput(__int128);
int main()
{
	dp[0][0] = 1;
	for(int i = 1;i<=50;i++)
	{
		dp[i][0] = dp[i][i] = 1;
		for(int j = 1;j<i;j++)
		{
			dp[i][j] = dp[i-1][j-1]+dp[i-1][j];
		}
	}
	int n,a,b;
	cin>>n>>a>>b;
	for(int i = 1;i<=n;i++)
	{
		cin>>num[i];
		buck[num[i]]++;	
	} 
	sort(num+1,num+1+n);
	reverse(num+1,num+1+n); 
	__int128 sum = 0,m = 0,cnt = 0;
	num[0] = -num[1];
	for(int i = 1;i<=b;i++)
	{
		if(num[i]==num[i-1]) pre[i] = pre[i-1]+1;//记录 0~i内有多少个相同数字
		else pre[i] = 1;
		sum+=num[i];
		if(i<a) continue;
		if(sum*100/i>m)//不是最大平均值则更新 方案数清零
		{
			m = sum*100/i;
			cnt = 0;
		}
		if(m==sum*100/i)//如果大小一致则累加最大值
		{
			cnt+=dp[buck[num[i]]][pre[i]];
			//选择 pre[i]个数 一共有 buck[num[i]]个 
		}
	}
	cout<<fput(m/100)<<"."<<fput(m%100)<<endl;
	cout<<fput(cnt)<<endl; 
	return 0;
}
string fput(__int128 x)//将int128转字符串
{
	string s;
	if(x==0) s = "0"; 
	while(x)
	{
		s.push_back(x%10^48);
		x/=10;
	}
	reverse(s.begin(),s.end());
	return s;
}
```
### long long Ac 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll num[200]; 
unordered_map<ll,int> buck;
ll pre[200];
ll dp[100][100];
int main()
{
  	......
	ll sum,m,cnt;
	sum = m = cnt = 0;
	......
	cout<<m/100<<"."<<m%100<<endl;
	cout<<cnt<<endl; 
	return 0;
}
```
### 思路2
~~对题目列一下公式会发现很神奇的事情，从这个思路看其实这道题也就还是个普及组的求组合数以及一点小思维。~~

对于选定的 $k$ 个数字，根据思路 $1$ 有公式：
$(\sum_{i=1}^{k}num_i)\times 100\div i\div 100$。

联想到求模方法，多个数余数再整除产生容斥太多，实际对于任意一个数字 $x$，存在一个 $b < y$，使得 $x = a\times y + b$，因此其实 $x\div y$ 的整数位即位 $a$ 就是整除运算的商。而小数的结果，因为 $b<y$ 即为 $b\div y$ 的小数位 （整数位为 $0$），因此结果为 $
(\lfloor \frac{sum}{i}\rfloor)\times(\frac{sum\bmod i}{i})$ 即可。
```cpp

#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll num[200]; 
unordered_map<ll,int> buck;
ll pre[200];
ll dp[100][100];

int main()
{
  	.......
	ll sum = 0,cnt;
	double m = 0;
	cnt = 0;
	num[0] = -num[1];
	for(int i = 1;i<=b;i++)
	{
    	......
		double x = sum/i+(sum%i)*1.0/i;
  		......
	}
	printf("%.2lf\n",m);
	cout<<cnt<<endl; 
	return 0;
}
```

---

## 作者：HNOIRPplusplus (赞：0)

题目中要求选出的数的平均值最大。所以，很自然我们应该选尽可能大的数。由于最大的数是越取越小的，所以取得更多并不会让平均数更大，反而可能会越来越小。所以我们只需要取最大的 $A$ 个即可。

假设说某序列为 $\{1,1,4,5,1,4,5\}$，要从中取 $3$ 个数，那么我们根据取最大值原则会取出两个 $5$ 和一个 $4$。现在，$4$ 是没有取完的，而比 $4$ 大的所有数（本例为 $5$）已经全部取完了。

因此，我们可以找到这个还没有被取完的数，将比它大的数全部取完，所以现在问题变成从两个 $4$ 中取一个出来，答案显然是 $C_2^1$。

---
你仔细地审视了一下样例 $4$，发现你的做法好像不对了。你会发现，如果最大的 $A$ 个数是相同的，$A+1$ 个数也是相同的，那么它们的平均值还是一样的。

所以，我们更正上面的取法：在最大的 $A$ 个值已经不一样的时候，只取 $A$ 个值。因为再取平均值就变小了。此时的答案即在取到的最小值中间挑选的方案。否则，就可以取 $\max\{\text{最大值的个数},B\}$ 个最大值，把这些部分全部都要加起来。

组合数部分随便怎么算都不会超时~~吧~~。

---

``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 55;

int v[N];
int c[N][N];

signed main() {
  int n, a, b;
  cin >> n >> a >> b;
  for(int i = 1; i <= n; i++) {
    cin >> v[i];
  }
  c[0][0] = c[1][0] = 1;
  for(int i = 1; i <= n; i++) {
    c[i][0] = 1;
    for(int j = 1; j <= i; j++) {
      c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    }
  }
  sort(v + 1, v + n + 1);
  int sum = 0;
  for(int i = n; i > n - a; i--) {
    sum += v[i];
  }
  cout << fixed << setprecision(6) << sum * 1.0 / a << '\n';
  if(v[n - a + 1] == v[n]) {
    int ans = 0, cnt = 0;
    for(int i = n; v[i] == v[n]; i--, cnt++);
    for(int i = a; i <= b && i <= cnt; i++) {
      ans += c[cnt][i];
    }
    cout << ans;
  } else {
    int ans = 0, cnt = 0, x = 0;
    for(int i = n - a; v[i] == v[n - a + 1]; i--, cnt++);
    for(int i = n - a + 1; v[i] == v[n - a + 1]; i++, cnt++, x = i);
    cout << c[cnt][a - (n - x + 1)];
  }
}
```

---

## 作者：zcr0202 (赞：0)

## 题目大意

给你一个数 $n$，代表数组的长度；两个数 $A$ 和 $B$，分别代表你最少可以取出的数和你最多可以取的数。让你求出取出的这些数的平均数最大有多少种方案。

## 解题思路

首先将数组排个序，用贪心求出最大的平均数。接着我们发现我们取出的最后一个数有不止一个数的时候，我们就会有 $\Large {C}_{\tiny{\text{总共的个数}}}^{\tiny{\text{取出这个数的个数}}}$。答案就这样出来了。不过还有一种情况，就是我们取出的数全是同一个数的时候，我们要特判一下。由于我们可以取从 $A$ 到 $B$ 个数，每种情况就是 $\Large {C}_{\tiny{\text{总共的个数}}}^{\tiny{\text{可以取出多少个数}}}$，累加起来就可以了。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100;
const int mod = 1e18 + 7;
int n, A, B;
int a[N], c[N][N];
double ans1;
int ans2;
int s1, s2;
signed main() {
	for(int i = 1; i <= N; i++) {
		c[i][i] = 1;
		c[i][0] = 1;
	}
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j < i; j++) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}	//求组合数
	cin >> n >> A >> B;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a + 1, a + 1 + n);		//排序
	for(int i = n; i >= n - A + 1; i--) {
		ans1 += a[i];
	}
	ans1 = ans1 * 1.0 / A;	//求出最大平均值
	cout << fixed << setprecision(6) << ans1 << '\n';
	s1 = s2 = 0;
	for(int i = 1; i <= n; i++) {
		if(a[i] == a[n - A + 1]) {
			s1++;
		}
	}	//求出总共的个数
	for(int i = n - A + 1; i <= n; i++) {
		if(a[i] == a[n - A + 1]) {
			s2++;
		}
	}	//求出选出的数中有多少个数
	if(a[n - A + 1] == a[n]) {	//特判
		ans2 = 0;
		for(int i = A; i <= B; i++) {
			ans2 += c[s1][i];
		}
	}
	else {
		ans2 = c[s1][s2];
	}
	cout << ans2;
	return 0;
}
```

---

## 作者：abensyl (赞：0)

原题：[[ABC057D] Maximum Average Sets](https://www.luogu.com.cn/problem/AT_abc057_d)。

一道好题。

## 思路

很显然的，选择的数字越少，其平均值就越大。

考虑在数组 $v$ 中，选取平均值最大的 $a$ 个数，很容易想到，选择最大的 $a$ 个即可。

- 那么，什么情况下选择 $a+1$ 个数之后平均值仍然不变呢？

> 显然地，选择的第 $a+1$ 个数字一定是第 $a+1$ 大的，那么如果前 $a$ 个数都跟他一样大，他的加入并不会影响平均值，否则，就不能加入第 $a+1$ 个数字。

然后，可以用排列组合算出答案，对于临界的数字，也就是说和 $v_a$ 一样大的数字中，可以选任意的一个或几个以凑出数量，可以用排列组合算出。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+2;
vector<int> v;
int cnm(int a,int b) {
	int res=1;
	for(int i=1,j=b;i<=a;++i,--j) res=res*j/i;
	return res;
} //组合数
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,a,b;
	cin>>n>>a>>b;
	for(int i=1,tt;i<=n;++i)
		cin>>tt,v.push_back(tt);
	sort(v.rbegin(),v.rend()); // 排序
	int sum=0,ans=0;
	for(int i=0;i<a;++i)
		sum+=v[i]; 
	long double res=sum;
	res/=a; //计算平均值
	cout<<fixed<<setprecision(6)<<res<<'\n';
	int fir=a-1,lst=a-1,aim=v[a-1];
	for(int i=0;i<v.size();++i)
		if(v[i]==aim)
			fir=min(fir,i),
			lst=max(lst,i);
	if(fir==0) { //前 a 个数字都一样大
		for(int i=a-1;i<=min(lst,b-1);++i) {
			int need=i-fir+1;
			ans+=cnm(need,lst-fir+1);
		}
	} else { //前 a 个数字不都一样大
		int need=a-1-fir+1;
		ans+=cnm(need,lst-fir+1);
	} cout<<ans<<'\n';
	return 0;
}
```

我的 [AC 记录](https://www.luogu.com.cn/record/133584702)。

---

## 作者：细数繁星 (赞：0)

[题目传送门。](https://www.luogu.com.cn/problem/AT_abc057_d)

于 `2023/08/01 13:18` 写。

## 前言

这题目坑还是有点多的，我就是因为变量类型问题 WA 了 7 次，我把坑整理一下：

- 不要开 `double`，`double` 是存不下除样例以外的数据的，也不要开 `long double`，因为一些玄学原因，开了 `long double` 会爆零，想办法把所有的 `long double` 都换成 `long long`。平均值处理这块可以先把平均值用 `long long` 累加，再强转 `double` 然后做除法。
- 尽量不要开 `int`，把所有的 `int` 都换成 `long long`。
- 很多代码角落的地方是你注意不到的，所以为了避免多次爆零，可以用宏定义把所有 `int` 提前都转成 `long long`。

## 贪心策略

看到算法标签，大家应该都能猜到现需要把数组给排序，为什么要排序呢？

排序后前 $A$ 个元素是必定要选的。为什么？因为前 $A$ 个元素肯定是最大的那 $A$ 个元素，而我们希望尽量在保证平均值单调递增的情况下，选择的元素最少，那么肯定要先选前 $A$ 个元素。

那对于第二小问呢？

有一个临界值，前文提到，选择前 $A$ 个元素是最优选择，那么临界值就是 $v_A$。 设在区间 $[1,A]$ 内有 $k_1$ 个元素使得 $v_i=v_A$，在整个数组中，有 $k_2$ 个元素使得 $v_i=v_A$ 在这种情况下，第二小问的答案是：
$$
C^{k_1}_{k_2}
$$

这个式子的含义是什么？是表示从那 $k_2$ 个数选择 $k_1$ 个数有多少种方案。这应该很好理解，我也不过多赘述了。

如果你现在就急着去写，恭喜你，喜提部分分。

为什么？因为我们还没有考虑到一种特殊情况，那就是 $v_1=v_A$，这种情况我们只需要选不影响平均值即可，只要选的数的个数不超过 $B$，那么，这一部分的公式如下：
$$
\sum_{i=A}^BC^i_{k_1}
$$
所以最终代码如下：

```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
long long YangHuiTraingle[55][55]; // 杨辉三角，排列组合用
void init()
{
    YangHuiTraingle[0][0] = 1;
    for (int i = 1; i <= 50; i++)
    {
        YangHuiTraingle[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            YangHuiTraingle[i][j] = YangHuiTraingle[i - 1][j] + YangHuiTraingle[i - 1][j - 1];
        }
    }
}
long long arr[114514];
int n, A, B;
long long average = 0.0; // 平均值
int main()
{
    init();
    cin >> n >> A >> B;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }  
    // 排序，注意 greater要用 long long
    sort(arr + 1, arr + n + 1, greater<long long>());
    long long choose = 0; // 选择了多少元素？
    long long choosebefore = 0; // 表示 k_1
    long long chooseafter = 0; // 表示 k_2
    for (int i = 1; i <= n; i++)
    {
    // 这是刚开始写错的，不用过多理会
        if (choose < A)
        {
            average += arr[i];
            choose++;
        }
        else if (choose > B)
        {
            break;
        }
        else if (choose >= A && arr[i] > average)
        {
            average += arr[i];
            choose++;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (arr[i] == arr[A])
        {
            choosebefore++;
            if (i <= A)
            {
                chooseafter++;
            }
        }
    }
    long long ans2 = 0;
    if (arr[1] == arr[A])
    
    {
        for (int i = A; i <= B; i++)
        {
            ans2 += YangHuiTraingle[choosebefore][i];
        }
    }
    else
    {
        ans2 += YangHuiTraingle[choosebefore][chooseafter];
    }
    printf("%.6lf\n%lld", (average / (double)(choose)), ans2);
}
```
[AC记录证明。](https://atcoder.jp/contests/abc057/submissions/44153230)
希望大家愉快的 AC 此题。

---

## 作者：0xyz (赞：0)

给出一种不同的做法。

首先吐槽一下这题出题人，正解 $O(n\log n)$ 出到 $n\le 50$，真不知道怎么想的。

我呢，一看到这个 $n\le 50$，就想到了**折半搜索**这样的指数级别算法。

关于第一问的求法，我也是很快想到了先将所有数从大到小排序，然后取前 $A$ 个。这样是因为后面的所有数小于等于这 $A$ 个中的任意一个，也就是小于等于前 $A$ 个数的平均值，所以加上之后一定不会更优。

然后是第二问，要求选择方法数有几个。于是考虑折半搜索，先预处理出后 $k$ 个数，每个选或不选，组成的和。由于要求平均数，所以还要考虑个数，所以我们要对这些和针对选取的数的个数分一下类。容易知道，由于要最大的平均数，在选择的数相同的情况下，一定要保证和尽量大。所以我们每一类只要选和最大的组合就可以了。使用 $b_i$ 表示后 $k$ 个数中选 $i$ 个数最大的和是多少；使用 $c_i$ 表示后 $k$ 个数中选 $i$ 个数和为 $b_i$ 的选法有所少组。

统计的时候针对前 $m$ 个数，枚举选择方案。但是选择方案要满足三条限制：

1. 平均数是第一问答案。
2. 选择的数不少于 $A$ 个。
3. 选择的数不多于 $B$ 个。

所以我们可以在外层枚举前 $m$ 个数选的情况 $i$，内层统计这个选的情况对应的和 $s$ 以及选择的个数 $t$，然后再枚举在后 $k$ 个数里选几个数 $j$，然后再判断当前平均数 $\frac{s+b_j}{t+j}$ 是否等于最大平均数 $\frac{sum}{A}$，然后再统计贡献。

取 $m=\lfloor\frac{n}{2}\rfloor,k=n-m$，时间复杂度 $O(2^{\frac{n}{2}}n)$，又卡时间，又卡空间。~~但是我卡过了。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,k,A,B,a[60],b[60],c[60],sum=0,ans=0;
char z[(1<<25)+1];
int main(){
	cin>>n>>A>>B;
	for(ll i=0;i<n;i++)cin>>a[i];
	sort(a,a+n,greater<ll>());
	for(ll i=0;i<A;i++)sum+=a[i];
	cout<<fixed<<setprecision(6)<<double(sum)/double(A)<<'\n';
	m=n/2;k=n-m;
	for(ll i=0;i<26;i++)z[1<<i]=i;
	for(register ll i=0,j,s,t;i<(1<<k);i++){
		s=0;t=__builtin_popcount(i);j=i;
		while(j)s+=a[m+z[j&-j]],j-=j&-j;
		if(s>b[t])b[t]=s,c[t]=1;
		else if(s==b[t])c[t]++;
	}
	for(register ll i=0,j,s,t,l,r;i<(1<<m);i++){
		s=0;t=__builtin_popcount(i);
		l=max(0ll,A-t);r=min(k,B-t);j=i;
		while(j)s+=a[z[j&-j]],j-=j&-j;
		for(j=l;j<=r;j++)
			if(sum*(t+j)==A*(s+b[j]))ans+=c[j];
	}
	cout<<ans<<'\n';
	return 0;
}
```

现在想来，正解十分显然，但是我却深陷指数级算法无法自拔。警示后人。

---


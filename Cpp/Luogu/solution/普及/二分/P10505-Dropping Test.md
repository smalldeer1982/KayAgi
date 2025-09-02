# Dropping Test

## 题目描述

在某个课程中，你需要进行 $n$ 次测试。 

如果你在共计 $b_i$ 道题的测试 $i$ 上的答对题目数量为 $a_i$，你的累积平均成绩就被定义为

$$100\times \dfrac{\displaystyle \sum_{i=1}^n a_i}{\displaystyle \sum_{i=1}^n b_i}$$

给定您的考试成绩和一个正整数 $k$，如果您被允许放弃任何 $k$ 门考试成绩，您的累积平均成绩的可能最大值是多少。

假设您进行了 $3$ 次测试，成绩分别为 $5/5,0/1$ 和 $2/6$。

在不放弃任何测试成绩的情况下，您的累积平均成绩是

$$100\times \frac{5+0+2}{5+1+6} \approx 58.33 \approx 58$$

然而，如果你放弃第三门成绩，则您的累积平均成绩就变成了

$$100\times \frac{5+0}{5+1}\approx 83.33\approx 83$$

## 说明/提示

数据范围 $1 \le n \le 1000$, $0 \le k < n$, $0 \le a_i \le b_i \le 10^9$。

## 样例 #1

### 输入

```
3 1
5 0 2
5 1 6
4 2
1 2 7 9
5 6 7 9
0 0```

### 输出

```
83
100```

# 题解

## 作者：__Cyn__ (赞：19)

[题目传送门](https://www.luogu.com.cn/problem/P10505)

刷题好习惯先看标签，算法是二分和分数规划。看题意可知：
$$\frac{\sum a_i}{\sum b_i} \ge mid$$

思路：先简化，移项和两边同时 $\times \sum b_i$ 后可得：

$$\sum a_i-mid\times b_i\ge0$$

再贪心一波，不留 $a_i-b_i\times mid$ 最小的 $k$ 门，留 $a_i-b_i\times mid$ 最大的 $n-k$ 门。还有，记得开 `double`。

然后套二分模版即可。

---

## 作者：Z_AuTwT (赞：6)

## 思路：

相当于对于两个序列，选出 `n-k` 个下标，对于每个序列，将被选中的下标对应的数字进行求和使得比值最大。

鉴定成分为“分数规划”，使用实数二分求解。

直接根据“分数规划”的式子来二分就行了。注意这题与其他不同的是需要用排序来取得前 `n-k` 个数。

不会“分数规划”的戳[这里](https://www.cnblogs.com/Dawn-Star/p/9610410.html)。

## CODE：

```c++
#include<bits/stdc++.h>
using namespace std;
int n,k;
struct node{
    int Yes,Sum;
}arr[1010];
struct node1{
	double a;
	int id;
}b[1010];
bool cmp(node1 A,node1 b){
    return A.a>b.a;
}
bool check(double ans){//判断是否合法
    double sum=0;
    for(int i=1;i<=n;i++) b[i].a=arr[i].Yes-ans*arr[i].Sum,b[i].id=i;
    sort(b+1,b+n+1,cmp);
    for(int i=1;i<=n-k;i++) sum+=b[i].a;//取前n-k个
    return sum>=0;
}
double work(double ans){//求最后的答案
    double sum=0,sum1=0;
    for(int i=1;i<=n;i++) b[i].a=arr[i].Yes-ans*arr[i].Sum,b[i].id=i;
    sort(b+1,b+n+1,cmp);
    for(int i=1;i<=n-k;i++) sum+=arr[b[i].id].Yes,sum1+=arr[b[i].id].Sum;
    return 100.00*sum/sum1;
}
main(){
    while(cin>>n>>k&&(n||k)){
        for(int i=1;i<=n;i++) cin>>arr[i].Yes;
        for(int i=1;i<=n;i++) cin>>arr[i].Sum;
        double l=0,r=1;
        while(r-l>=1e-6){//实数二分模板
            double mid=(l+r)/2.00;
            if(check(mid)) l=mid;
            else r=mid;
        }
        printf("%.0lf\n",round(work(l)));
    }
}
```

望管理通过。???

---

## 作者：xuchuhan (赞：4)

分数规划模板题。

## 题意

给你 $n$ 个数 $a_1,a_2,\dots,a_n$，以及 $n$ 个数 $b_1,b_2,\dots,b_n$。请在 $1$ 至 $n$ 中选出 $n-k$ 个数 $d_1,d_2,\dots,d_{n-k}$ 使得 $S=100\times\dfrac{\sum_{i=1}^{n-k}a_{d_i}}{\sum_{i=1}^{n-k}b_{d_i}}$ 最大，输出 $S$。

有多组数据。

## 解法

可以将本题换种方式思考。

求最大的 $S$ 可以看作求最大的 $p$ 使 $\dfrac{\sum_{i=1}^{n-k}a_{d_i}}{\sum_{i=1}^{n-k}b_{d_i}}>p$，最后的答案即为 $100\times p$。将式子简单转化一下即可得到 $\sum_{i=1}^{n-k} a_{d_i}-p\times b_{d_i}>0$。显然 $\sum_{i=1}^{n-k} a_{d_i}-p\times b_{d_i}$ 具有单调性，所以可以二分处理。二分 $p$ 的最大值。

那么 `check` 函数怎么写呢？

设 $c_i=a_i-p\times b_i$，那么选取时肯定选取最大的 $n-k$ 个 $c_i$ 作为答案，使得 $c_i$ 之和，即总答案更大。若总答案大于 $0$ 则代表这个 $p$ 可行，否则不可行。

## 细节

本题需要实数二分。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const double eps=1e-9;//我在这一行中翻过2个错,以此警示后人:1.eps的类型是const double.2.eps的精度要尽量开高一点,不要像我一样只开1e-3 
int n,k;
double a[N],b[N],c[N];
bool cmp(double x,double y){
	return x>y;
}
bool check(double mid){
	for(int i=1;i<=n;i++)
		c[i]=a[i]-b[i]*mid;//求c[i] 
	sort(c+1,c+n+1,cmp);//找答案 
	double s=0;
	for(int i=1;i<=n-k;i++)
		s+=c[i]; 
	return s>=0;
}
int main(){
	while(cin>>n>>k&&n){
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			cin>>b[i];
		double l=0,r=1e9;//实数域二分 
		while(r-l>eps){
			double mid=(l+r)/2.0;
			if(check(mid))//此mid可行 
				l=mid;//更新l 
			else//否则 
				r=mid;//更新r 
		}
		printf("%d\n",int(l*100+0.5));//*100是因为答案要乘100,+0.5是处理四舍五入 
	}
	return 0;
}
```

---

## 作者：PengDave (赞：2)

# solution
考虑二分答案。可得（下面式子中的 $a$ 和 $b$ 均表示去掉 $k$ 门考试成绩的 $a$ 和 $b$）：
$$\frac{\sum a_i}{\sum b_i}\ge mid$$
去分母、移项得：
$$\sum a_i - mid \times \sum b_i \ge 0$$
很显然，只要贪心地保留 $a_i-b_i\times mid$ 最大的 $n-k$ 门考试成绩即可。
# code
```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int n,k;
double a[1010],b[1010],tmp[1010];
bool check(double m){
	double cnt=0;
	for(int i=1;i<=n;i++){
		tmp[i]=a[i]-b[i]*m;
	}
	sort(tmp+1,tmp+1+n);
	for(int i=n;i>k;i--){
		cnt+=tmp[i];
	}
	return cnt>=0.0;
}
const double eps=1e-8;
int main(){
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	while(cin>>n>>k){
		if(n==0&&k==0){
			break;
		}
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
		}
		double st=0,ed=100;
		while(fabs(ed-st)>=eps){
			double mid=st+(ed-st)/2.0;
			if(check(mid)){
				st=mid;
			}else{
				ed=mid;
			}
		}
		cout<<round(st*100.0)<<"\n";
	}
	cout<<flush;
	return 0;
}
```

---

## 作者：bcbgszyzh (赞：1)

二分

根据题意得

$$\dfrac{∑a_i}{∑b_i}≥mid$$

简化后得

$$∑a_i-mid\times ∑b_i≥0$$

显然，只用保留 $a_i-b_i\times mid$ 最大的 $n-k$ 门即可。

---

## 作者：__Creeper__ (赞：0)

## 思路
### 1.纯贪心
定义 $c$ 数组，$c_{i} = a_{i} \div b_{i}$（特判 $b_{i} = 0$ 的情况），用 sort 排序（从大到小排序），取前 $n - k$ 个数，答案表示为 $\frac{\sum _ {i = 1} ^ k a_{i}}{\sum _ {i = 1} ^ k b_{i}}$，但贪心有局限性，所以就被 hack 了。
### 2.01分数规划（正解）
- 01 分数规划多用于求解类似于给出 $a$，$b$ 数组，求选择 $k$ 个数 $p$，使 $\frac{\sum _ {i = 1} ^ k a_{p_{i}}}{\sum _ {i = 1} ^ k b_{p_{i}}}$ 最大。
#### 01 分数规划怎么求？
求解分数规划最常用的方式是二分，我们**二分**答案，假设实际值是大于 mid 的，则有：

- $\frac{\sum _ {i = 1} ^ k a_{p_{i}}}{\sum _ {i = 1} ^ k b_{p_{i}}} > mid$ 

化简：

- $\frac{\sum _ {i = 1} ^ k a_{p_{i}}}{\sum _ {i = 1} ^ k b_{p_{i}}} - mid > 0$ 
- $\sum _ {i = 1} ^ k a_{p_{i}} - mid \cdot {\sum _ {i = 1} ^ k b_{p_{i}}} > 0$
- $\sum _ {i = 1} ^ k a_{p_{i}} - mid \cdot b_{p_{i}} > 0$

直接套用公式，就是一个二分板子题了。
## Code 
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1005;
const double eps = 1e-6;

int n, k, a[N], b[N];
double c[N];

bool cmp ( double x, double y )
{
    return x > y;
}

bool check ( double mid ) 
{
	for ( int i = 1; i <= n; i++ ) 
	{
	    c[i] = 1.0 * a[i] - 1.0 * b[i] * mid; //公式
	}
	sort ( c + 1, c + n + 1, cmp );
	double sum = 0;
	for ( int i = 1; i <= n - k; i++ ) //贪心取最大的
	{
      	    sum += c[i];
	}
	return sum >= 0;
}

signed main()
{
	while ( cin >> n >> k && n ) 
	{
		for ( int i = 1; i <= n; i++ ) 
		{
		    cin >> a[i]; 
		}
		for ( int i = 1; i <= n; i++ ) 
		{
         	    cin >> b[i];
		}
		double l = 0, r = 1;
		while ( r - l > eps ) //浮点数二分
		{
			double mid = ( l + r ) / 2.0;
			if ( check ( mid ) ) 
			{
           		    l = mid;
			} 
			else 
			{
              		    r = mid;
			}
		}
		cout << (int)( l * 100 + 0.5 ) << endl; // 四舍五入
	}
	return 0;
}
```
四舍五入 printf 输出也可，~~作者懒得写，用 cout 也是可以的~~

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10505)
## 解题思路
二分。

把题目里的式子加上二分模版：
$$
\dfrac{\sum\limits_{i=1}^na_i}{\sum\limits_{i=1}^nb_i}\ge mid
$$
移项，得：
$$
\dfrac{\sum\limits_{i=1}^na_i}{\sum\limits_{i=1}^nb_i}-mid\ge 0
$$
两边同乘 $\sum\limits_{i=1}^nb_i$ 得：
$$
\sum\limits_{i=1}^na_i-mid\times \sum\limits_{i=1}^nb_i\ge 0
$$
把式子里的 $\sum\limits_{i=1}^na_i-mid\times \sum\limits_{i=1}^nb_i$ 排序，求最大 $m$ 个的和，判断 $\ge0$ 即可。

然后直接套二分模版。

**记得开 `double`**！
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
double a[1010],b[1010],c[1010];
bool ck(double mid)
{
	for(int i=1;i<=n;i++)
		c[i]=a[i]-b[i]*mid;
	sort(c+1,c+n+1);
	double s=0;
    for(int i=n;i>=m+1;i--)
		s+=c[i];
    return s>=0;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while(cin>>n>>m)
	{
		if(!n&&!m)return 0;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			cin>>b[i];
		double l=0,r=100;
		while(r-l>=1e-8)
		{
			double mid=(l+r)/2;
			if(ck(mid))l=mid;
			else r=mid;
		}
		cout<<round(l*100)<<'\n';
	}
	return 0;
}

```

---

## 作者：be_RISK (赞：0)

## [$luogu$](https://www.luogu.com.cn/problem/P10505)
## 思路
### 纯贪心（其实不用看的）
这是在机房，我左右两边两个巨佬提出的，水过了第 15 行后就被老师 hack 了，俩人讨论后发现贪心有局限性
### 01 分数规划（正解）
#### 01 分数规划是什么？
01 分数规划多用于求解类似于给出 $a,b$ 数组，求选择 $k$ 个数 $p$，使得 $\frac{\sum_{i = 1}^{k} a_{p_i}}{\sum_{i = 1}^{n} b_{p_i}}$ 最大化。
#### 01 分数规划怎么求？
01 分数规划多使用二分求解，下面推一下 check：

首先有
$$\frac{\sum_{i = 1}^{k} a_{p_i}}{\sum_{i = 1}^{k} b_{p_i}}> mid$$
移项得
$$\frac{\sum_{i = 1}^{k} a_{p_i}}{\sum_{i = 1}^{k} b_{p_i}}-mid>0$$
再次移项得
$${\sum_{i = 1}^{k} a_{p_i}}-mid\times{\sum_{i = 1}^{k} b_{p_i}}>0$$
化简得
$${\sum_{i = 1}^{k} a_{p_i}-mid\times b_{p_i}}>0$$
#### 引入本题
这就是一个 01 分数规划板子，直接分数二分套板子就好了
## code
```
#include<bits/stdc++.h>
//#define int long long
#define esp 1e-6//精度差
using namespace std;
inline int read(){
	char c=getchar();
	int ret=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		ret=(ret<<3)+(ret<<1)+c-'0';
		c=getchar();
	}return ret*f;
}
inline void write(int x,int op){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10,0);
	putchar((char)(x%10+'0'));
	if(op){
		if(op>0)puts("");
		if(op<0)putchar(' ');
		if(op==0)puts("114514");
	}
}
const int N=1e3+10;
int n,k;
double a[N],b[N];
bool cmp(double x,double y){return x>y;}
bool check(double x){
	double ret=0,c[N];
	for(int i=1;i<=n;i++)c[i]=a[i]-x*b[i];
	sort(c+1,c+1+n,cmp);//排序，为贪心做准备
	for(int i=1;i<=n-k;i++)ret+=c[i];//贪心的选取最大
	return ret>0;
}
int main(){
	n=read(),k=read();
	while(n||k){
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=n;i++)b[i]=read(); 
		double l=0.0,r=114.0;//二分上下界
		while(r-l>=esp){
			double mid=(l+r)/2.0;
			if(check(mid))l=mid;
			else r=mid;
		}printf("%.0lf\n",100*l);//按题目要求输出l*100
		n=read(),k=read();
	}
	return 0;
}//*~完结撒花~*
```

---

## 作者：QinghongLi (赞：0)

# 分数规划问题
求 $\max\frac{\sum_{i=1}^{n}a_i s_i}{\sum_{i=1}^{n}b_i s_i}$，其中 $s_i=1$ 或 $s_i=0$，表示是否选择这一项，且 $\sum_{i=1}^{n}s_i=k$。

猜测一个可能的答案值 $x$ 即：
$$
\frac{\sum_{i=1}^{n}a_i s_i}{\sum_{i=1}^{n}b_i s_i}\ge x
$$
移项得 $f=\sum_{i=1}^{n}(a_i-x b_i)s_i\ge 0$。显然我们可以二分枚举 $x$ 的值，将 $a_i-x b_i$ 的值从大到小取前 $k$ 项。判断其值是否大于 $0$，如果大于显然可以枚举更大的 $x$ 的值。
# 代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n,k;
double a[1001],b[1001],y[1001];
bool judge(double x){
    for(int i=1;i<=n;i++)y[i]=a[i]-b[i]*x;
    sort(y+1,y+1+n);
    double sum=0;
    for(int i=0;i<k;i++)
        sum+=y[n-i];
    return sum<0;
}
int main()
{
    while(scanf("%d%d",&n,&k)==2&&n+k){
        k=n-k;
        double l=0,r;
        for(int i=1;i<=n;i++){
            scanf("%lf",&a[i]);
            r+=a[i];
        }
        for(int i=1;i<=n;i++)cin>>b[i];
        for(int i=1;i<=80;i++){
            double mid=(l+r)/2;
            if(judge(mid))
                r=mid;
            else
                l=mid;
        }//80次大概够用了
        printf("%d\n",(int)(100*(l+0.005)));//四舍五入
    }
    return 0;
}


```

---

## 作者：InversionShadow (赞：0)

注意一下，样例有误，见[此帖](https://www.luogu.com.cn/discuss/822265)。

---

0-1 分数规划板子。

题意就是构造一组 $w$，满足 $\sum\limits_{i=1}^n[w_i=0]=k$，其他的 $n-k$ 个 $w_i=1$，使得：
$$100\times\dfrac{\sum\limits_{i=1}^n(a_i\times w_i)}{\sum\limits_{i=1}^n(b_i\times w_i)}$$ 
最大化。

先把 $100$ 去掉，二分答案一个 $mid$。$mid$ 满足：

$$\dfrac{\sum\limits_{i=1}^n(a_i\times w_i)}{\sum\limits_{i=1}^n(b_i\times w_i)}\ge mid$$

那么变成：

$$\sum\limits_{i=1}^n(w_i\times(a_i-mid\times b_i))\ge 0$$

贪心地思考，肯定要把 $a_i-mid\times b_i$ 最小的 $k$ 个赋 $0$，最大的 $n-k$ 个赋 $1$，判断其与 $0$ 的大小即可。

最后输出答案是 $l\times 100$ 四舍五入。

还有就是，输入的 $k$ 有可能等于 $0$，注意一下终止条件。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e3 + 100;
const double eps = 1e-6;

int n, k, a[N], b[N];
double c[N];

bool check(double mid) {
	for (int i = 1; i <= n; i++) {
		c[i] = 1.0 * a[i] - 1.0 * b[i] * mid;
	}
	sort(c + 1, c + n + 1, greater<double>());
	double sum = 0;
	for (int i = 1; i <= n - k; i++) {
		sum += c[i];
	}
	return sum >= 0;
}

signed main() {
	while (cin >> n >> k && n) {
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		for (int i = 1; i <= n; i++) {
			cin >> b[i];
		}
		double l = 0, r = 1;
		while (r - l > eps) {
			double mid = (l + r) / 2.0;
			if (check(mid)) {
				l = mid;
			} else {
				r = mid;
			}
		}
		cout << (int)(l * 100 + 0.5) << '\n';
	}
	return 0;
}

/*
3 1
5 0 2
5 1 6
4 2
1 2 7 9
5 6 7 9
0 0
*/
```

---

## 作者：Tachibana27 (赞：0)

### 题意

给定 $2$ 个长度为 $n$ 的数列 $a$ 和 $b$，希望你选出 $n-k$ 个数 $p_i$，使得 $\frac{\sum \limits _{i=1} ^{n-k} a_{p_i}}{\sum \limits _{i=1} ^{n-k} b_{p_i}}$ 尽可能的大。

### 思路

#### 贪心

看似可以解决此问题，但认真思考后会发现没有正确性，~~虽然本蒟蒻第一个就想到了贪心~~，无论是根据得分与总分的比值还是差都很容易举出反例。

~~听说有多次贪心求最大值的做法？~~

#### 分数规划

求解分数规划最常用的方式是**二分**，我们二分答案，假设实际值是大于 mid 的，则有：

$$\frac{\sum \limits _{i=1} ^{n-k} a_{p_i}}{\sum \limits _{i=1} ^{n-k} b_{p_i}}>mid$$

移项得：

$$\frac{\sum \limits _{i=1} ^{n-k} a_{p_i}}{\sum \limits _{i=1} ^{n-k} b_{p_i}}-mid>0$$

再移项得：

$$\sum \limits _{i=1} ^{n-k} a_{p_i} -mid \times \sum \limits _{i=1} ^{n-k} b_{p_i}>0$$

最后简化成：

$$\sum \limits _{i=1} ^{n-k} (a_{p_i} -mid \times b_{p_i})>0$$

考虑计算所有的 $a_{i} -mid \times b_{i}$，随后贪心的选择最大的 $n-k$ 个即可。

### code：

四舍五入的话其实可以用 printf。

```cpp

#define eps 1e-5
int n,k;
class node{
    public:
        double a;
        double b;
}qwq[1086];
double c[1086];
bool check(double x){
    double sum=0;
    for(int i=1;i<=n;i++)
        c[i]=qwq[i].a-x*qwq[i].b;//上式
    std::sort(c+1,c+1+n);
    for(int i=1+k;i<=n;i++)//贪心的选择大的
        sum+=c[i];
    return sum>0;
}
int main(){
    while(std::cin>>n>>k and (n or k)){
        for(int i=1;i<=n;i++)
            std::cin>>qwq[i].a;
        for(int i=1;i<=n;i++)
            std::cin>>qwq[i].b;
        double l=0;
        double r=100.001;
        while(r-l>eps){//实数二分
            double mid=(l+r)/2.00;
            if(check(mid))
                l=mid;
            else
                r=mid;
        }
        printf("%.0lf\n",l*100.00);//利用printf进行四舍五入
    }
    return 0;//撒花~
}
```

---


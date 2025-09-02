# [CCC 2020] Surmising a Sprinter's Speed

## 题目背景

本题译自 [Canadian Computing Competition](https://cemc.uwaterloo.ca/sites/default/files/documents/2020/2020CCCSrProblemSet.html) [2020 Senior](https://cemc.uwaterloo.ca/sites/default/files/documents/2020/seniorEF.pdf) T1 Surmising a Sprinter's Speed。

## 题目描述

Trick E. Dingo 正在捕捉 Street Sprinter，他正在收集数据，进一步了解 Street Sprinter 的速度。

Trick E. Dingo 正在一条笔直的东西向的道路上抓捕 Street Sprinter，这条路上有一块特别著名的石头，亲切地被称为“原点”。这条路上的位置是根据与原点的距离用数字来测量的：原点以西的位置使用负数表示，以东的位置使用正数表示。

Trick E. Dingo 的观察记录每次包含两个数字：一个时间和在该时间 Street Sprinter 在路上的位置值。根据这些信息，Street Sprinter 至少能达到了什么速度呢？

## 说明/提示

#### 【样例解释】
对于第一组样例，为了在 $10$ 秒内从位置 $120$ 移动到位置 $50$，速度必须至少为 $7$。
#### 【数据范围】
**本题采用捆绑测试**。

对于 $50\%$ 的数据，$0 \le n \le 1000$。

## 样例 #1

### 输入

```
3
0 100
20 50
10 120```

### 输出

```
7.0```

## 样例 #2

### 输入

```
5
20 -5
0 -17
10 31
5 -3
30 11```

### 输出

```
6.8```

# 题解

## 作者：jojo222 (赞：2)

首先，将记录按时间排序；接着，选 $i$ 和 $i+1$（$1\le i<n$）的记录做差取最大值；最后，输出答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
double ans;
pair<int, int> a[100001];
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].first, &a[i].second);
	sort(a + 1, a + 1 + n);
	for(int i = 1; i < n; i++)
		ans = max(ans, 1.0 * abs(a[i + 1].second - a[i].second) / (a[i + 1].first - a[i].first));
	cout << ans;
	return 0;
}
```

知识：`pair` 也能排序，先看 `first`，如果相同，看 `second`。  
警示后人：$n$ 的范围在题干中，不要看下面 $50\%$ 的数据；位置做差要取绝对值，可能~~傻~~往回跑。

---

## 作者：2023z (赞：2)

### 前置芝士

小学数学：

 $ 速度 = 路程 \div 时间 $

### 思路

我们开一个结构体，分别表示每次记录的时间和路程。首先对时间排序，然后依次算出每次记录的速度，取最大值。**注意坑点**，结构体要开 $ 10^5 $，因为只告诉了我们 $ 50\% $ 数据。

#### code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct s{
	int t,m;
}a[101000]; //t 时间，m 路程
int n;
double ans;
bool cmp(s a,s b){
	return a.t<b.t; //排序函数
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].t>>a[i].m; //输入
	sort(a+1,a+n+1,cmp); //排序
	for(int i=2;i<=n;i++){
		double x=abs(a[i].m-a[i-1].m)*1.0/(a[i].t-a[i-1].t); //算出速度
		ans=max(ans,x); //更新最大值
	}
	printf("%.5lf",ans); //注意精度
	return 0;
}
```
[AC](https://www.luogu.com.cn/record/198939073)

完结撒花！

---

## 作者：Doraeman (赞：2)

## 题意
题目给出了 $n$ 个时间 $t$，每个时间都有一个 Street Sprinter 所在的位置 $x$，题目询问从每个时间到其下一个时间的平均速度的最大值。
## 思路
1. 对时间进行排序。
2. 计算从第 $i$ 时间到第 $i+1$ 时间的平均速度。
3. 循环取最大值。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100005;

// 创建数据结构，保存每个时间和对应的位置 
struct Street{
	int t, p; // time, position 
}a[N]; 

// 时间小排在前面 
bool cmp(Street x, Street y){
	return x.t < y.t;
}

double ans;

int main(){
	int n; cin >> n;
	for(int i=1; i<=n; i++)
		cin >> a[i].t >> a[i].p;
	
	// 根据时间排序 
	sort(a + 1, a + n + 1, cmp);
	
	// 循环计算速度，取最大值 
	for(int i=1; i<n; i++){
	    // 计算从i时间到i+1时间的路程和时间，求出速度
		// 在数轴上，x到y的距离=|x-y| 
		// 速度=路程/时间，v=s/t 
		double v = abs(a[i].p - a[i+1].p)/1.0/(a[i+1].t - a[i].t);
		
		// 更新答案，得到最大值 
		ans = max(ans, v);
	}
	
	// 输出答案，注意输出答案的限制，应当提高精确度 
	printf("%.6lf",ans);
}
```

---

## 作者：Eric1030 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P11581)

此题主要考察小学学的行程问题的公式：$v=\frac{s}{t}$。

有了这个公式，这道题就可以做了。

但要注意 $50\%$ 的数据是 $1000$，所以我们要把数组开大点，避免 RE。我们也要把输入进来的数据按时间从小到大排序。然后求速度的最大值。

下面就是代码了。


```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
double ans;//保留一位小数，用double（用float也可以）
struct node {//因为时间和位置是一组一组输入进来的，用struct存
	int t, x;
}a[10000005];//数组开大点
bool cmp(node t1, node t2)
{
	return t1.t < t2.t;//比较函数，从小到大排
}
int main()
{
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i].t >> a[i].x;
	}
	sort(a + 1, a + 1 + n, cmp);//排序
	for (int i = 1;i <= n - 1;i++)
	{
		ans = max(ans, abs(a[i].x - a[i + 1].x) * 1.0 / (a[i + 1].t - a[i].t));//求最大值，用两个时间内走的路程除以两个时间内用的时间，因为时间是按从小到大排序的，就不用abs了。
	}
	cout << ans << setprecision(1);//保留一位小数输出
	return 0;
}
```

无注释代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
double ans;
struct node {
	int t, x;
}a[10000005];
bool cmp(node t1, node t2)
{
	return t1.t < t2.t;
}
int main()
{
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i].t >> a[i].x;
	}
	sort(a + 1, a + 1 + n, cmp);
	for (int i = 1;i <= n - 1;i++)
	{
		ans = max(ans, abs(a[i].x - a[i + 1].x) * 1.0 / (a[i + 1].t - a[i].t));
	}
	cout << ans << setprecision(1);
	return 0;
}
```

[AC](https://www.luogu.com.cn/record/199044027) 记录

---

## 作者：Loyal_Soldier (赞：1)

### 思路

这一题我们要先把时间从小到大排序，再遍历一遍 $2\sim n$，计算从上一次测量时到本次测量时的秒速，然后在这些秒速中取最大值。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct stu{
    int t,x;
}a[114514];//定义每次测量时的时间和位置的结构体
bool cmp(stu a,stu b){
    return a.t<b.t;
}
double ans;//ans表示最终答案
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i].t>>a[i].x;
    sort(a+1,a+n+1,cmp);//按时间从小到大排序
    for(int i=2;i<=n;i++)
        ans=max(ans,abs(a[i].x-a[i-1].x)/1.0/(a[i].t-a[i-1].t));//计算上一次测量时到本次测量时的秒速，ans在ans和本次算出的秒速中取最大值
    printf("%.5lf",ans);//注意题目中的限制，记得提高输出的精度
    return 0;
}
```

---

## 作者：jiqihang (赞：1)

### 题目链接
[P11581 [CCC2020] Surmising a Sprinter's Speed](https://www.luogu.com.cn/problem/P11581)
### 题意
给出 $n$ 个时间 $t$，每个时间都有对应的 $x$，表示 Street Sprinter 的位置。求出两个时间之间的平均速度的最大值。
### 分析
用结构体做。

1. 对时间排序（从小到大，即从最开始的时到最后的时间）。
2. 计算两个时间之间的平均速度。
3. 打擂台求最大值。找到后输出。

本题要用到结构体排序，实现方法不赘述，具体可自行查找。

本题易错点是求速度中距离要取绝对值。

还有就是把精度处理好就行了。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node{
	int t,x;
}a[100000]; //结构体
bool cmp(Node a,Node b)
{
	return a.t<b.t;
}//排序规则
int main()
{
	int n;
	double maxn=0;//最大值，要用 double
	cin>>n;//输入n
	for(int i=0;i<n;i++) cin>>a[i].t>>a[i].x;//输入结构体数据
	sort(a,a+n,cmp);//排序
	for(int i=0;i<n;i++)
	{
		double v=abs(a[i+1].x-a[i].x)/1.0/(a[i+1].t-a[i].t);//易错点
		maxn=max(maxn,v);//打擂台
	}
	cout<<maxn;//输出
	return 0;
}
```
这题我们就可以 AC 了。

---

## 作者：langni (赞：1)

题目给出了 $n$ 个测量结果，每个测量结果都包含时间 $t$ 和 Street Sprinter 的位置 $x$，求 Street Sprinter 的最大速度。由于题目没有保证 $t$ 按从小到大给出，所以我们需要按照 $t$ 从小到大排序。排好序后，我们就可以用位置差除以时间差来计算速度，再取最大值即可。\
代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct celiang
{
    int t, x; //定义一个结构体，结构体里包含 t 和 x
}a[101000];
bool cmp(celiang A, celiang B)
{
    return A.t < B.t; //排序函数
}
signed main()
{
    cin >> n;
    double v_max = 0, v_now; //v_max记录答案，v_now记录当前 Street Sprinter 的速度
    for (int i = 1; i <= n; ++ i)
    {
        cin >> a[i].t >> a[i].x;
    }
    sort(a + 1, a + 1 + n, cmp); //按 a 排序
    for (int i = 1; i < n; ++ i)
    {
        v_now = abs(a[i].x - a[i + 1].x) * 1.0 / abs(a[i + 1].t - a[i].t); //计算速度(计算时，一定要取绝对值，不然可能算出负数)
        v_max = max(v_max, v_now); //取最大值
    }
    cout << v_max; //输出
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 具体思路
先对数据排序，按测量时间升序排序。则从一个位置到下一时刻所到达的位置的距离为两者测量距离之差，时间为两者测量时间之差，然后由速度公式 $v=\frac{s}{t}$ 得出速度，答案为所有得出的速度的最大值。  
### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define deap(i,a,b) for(int i=a;i>=b;i--)
#define in(a) a=read()
const int N = 1e5+5;
const int inf = INT_MAX;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
void fast() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
pair<int,int> a[N];
signed main() {
	//fast();
	int n;
	in(n);
	rep(i,1,n)in(a[i].first),in(a[i].second);
	sort(a+1,a+n+1);
	double ans=0;
	rep(i,1,n-1){
		double s=abs(a[i].second-a[i+1].second),t=abs(a[i].first-a[i+1].first);
		ans=max(ans,s/t); 
	}
	cout<<ans;
	return 0;
}



```

---

## 作者：All_Wrong_Answer (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11581)

## 思路：

**结构体排序**

定义如下结构体：

```cpp
struct node{
	double tim;//时间
	int wz;//位置
}m[114514];
```
然后按时间排序，由于重载运算符比较复杂，所以我们采用 ```cmp``` 与 ```sort``` 相结合的方式来排序。


```cpp
bool cmp(node q,node p){
	return q.tim<p.tim;
}
```

快速排序：
```cpp
sort(m+1,m+1+n,cmp);
```

接下来就是计算速度，小学就学过了，这里不过多赘述，比较大小记录最大值即可。

##完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	double tim;
	int wz;
}m[114514];//结构体 
int n;
double da;
bool cmp(node q,node p){
	return q.tim<p.tim;
}//排序用的cmp 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>m[i].tim>>m[i].wz;
	}
	sort(m+1,m+1+n,cmp);//快排 
	int shtim=m[1].tim;
	int shwz=m[1].wz;
	for(int i=2;i<=n;i++){
		da=max(da,(abs(m[i].wz-shwz))/(m[i].tim-shtim));
		//速度=路程/时间 
		shwz=m[i].wz;
		shtim=m[i].tim;
	}
	printf("%.9lf",da);//保证精度 
	return 0;
}
```

---


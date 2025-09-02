# 自習 (Self Study)

## 题目描述

在 JOI 高中高一的第三个学期的 $M$ 个星期的时间内，有 $N$ 门课，编号为 $1 \sim N$。每个星期有 $N$ 个课时，第 $i$ 个课时上课程 $i$ 的一节课。

比太郎是一位高一学生。对于 $N \times M$ 个课时中的每一个，他会选择如下行动中的一个：

- 行动 1：比太郎去上课。如果他去上了课程 $i$ 的一节课，那么他对课程 $i$ 的理解程度会增加 $A_i$。
- 行动 2：比太郎不去上课。他转而选择任意一门课，并且自学选中的那门课。如果他选中了课程 $i$ 进行了时长为一课时的自学，那么他对课程 $i$ 的理解程度会增加 $B_i$。

一开始，对每门课的理解程度都为 $0$。由于比太郎想要在课后练习算法竞赛，他在非上课时间内不会学习。当第三个学期的所有课时结束后，期末考就会举行。

比太郎不想挂科。所以他想要最大化在期末考时对每门课的理解程度的最小值。

给定学期的长度，课程的数量，以及对理解程度的提升数值，请写一个程序计算在期末考时对每门课的理解程度的最小值的最大可能值。

## 说明/提示

**【样例解释 \#1】**

举个例子，如果比太郎按如下方式学习，则他对课程 $1, 2, 3$ 的理解程度将分别为 $19, 18, 19$。

- 第一周课程 $1$ 的课：自学课程 $2$；
- 第一周课程 $2$ 的课：自学课程 $2$；
- 第一周课程 $3$ 的课：去上课程 $3$ 的课；
- 第二周课程 $1$ 的课：去上课程 $1$ 的课；
- 第二周课程 $2$ 的课：自学课程 $3$；
- 第二周课程 $3$ 的课：去上课程 $3$ 的课；
- 第三周课程 $1$ 的课：自学课程 $3$；
- 第三周课程 $2$ 的课：自学课程 $2$；
- 第三周课程 $3$ 的课：去上课程 $3$ 的课。

由于对每门课的最小的理解程度不能大于等于 $19$，输出 $18$。

这个样例满足子任务 $3, 5$ 的限制。

**【样例解释 \#2】**

这个样例满足子任务 $1, 3, 5$ 的限制。

**【样例解释 \#3】**

这个样例满足子任务 $3, 5$ 的限制。

**【样例解释 \#4】**

这个样例满足子任务 $2, 3, 4, 5$ 的限制。

----


**本题采用捆绑测试。**

对于 $100 \%$ 的数据，$1 \le N \le 3 \times {10}^5$，$1 \le M \le {10}^9$，$1 \le A_i, B_i \le {10}^9$。

- 子任务 $1$（$10$ 分）：$M = 1$。
- 子任务 $2$（$25$ 分）：$N \cdot M \le 3 \times {10}^5$，$A_i = B_i$。
- 子任务 $3$（$27$ 分）：$N \cdot M \le 3 \times {10}^5$。
- 子任务 $4$（$29$ 分）：$A_i = B_i$。
- 子任务 $5$（$9$ 分）：无特殊限制。

----

**译自 [JOI 2022 Final](https://www.ioi-jp.org/joi/2021/2022-ho/index.html) T2「[自習](https://www.ioi-jp.org/joi/2021/2022-ho/2022-ho-t2.pdf) / [Self Study](https://www.ioi-jp.org/joi/2021/2022-ho/2022-ho-t2-en.pdf)」**

## 样例 #1

### 输入

```
3 3
19 4 5
2 6 2```

### 输出

```
18```

## 样例 #2

### 输入

```
2 1
9 7
2 6```

### 输出

```
7```

## 样例 #3

### 输入

```
5 60000
630510219 369411957 874325200 990002527 567203997
438920902 634940661 593780254 315929832 420627496```

### 输出

```
41397427274960```

## 样例 #4

### 输入

```
4 25
1 2 3 4
1 2 3 4```

### 输出

```
48```

# 题解

## 作者：ny_jerry2 (赞：4)

**最小值最大**，光凭这个就可以确定要用二分了。

那么，二分答案的函数具体怎么实现呢？  
首先有一个地方，如果当前课程自学比老师教要好，那肯定选择自学，因为这样收益大一点。

然后是主体部分。先求出每一个课程如果全让老师教的话（当然要特殊处理一下上述特殊情况，直接让自学等同于老师教即可），看可以节省出多少天去自学其他的科目（如果本来就不够用除外）。

然后就去用节省出来的天去补那些效果达不到的科目。如果能够补完，说明当前二分的值，可以继续放大；否则就要缩小。

## 代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
long long n,m;
const int N=3e5+10;
long long a[N],b[N],c[N];
bool check(long long mid){
	long long res=0;
	for(int i=1;i<=n;i++){
		res+=max(0ll,m-(mid+c[i]-1)/c[i]);
	}
	for(int i=1;i<=n;i++){
		long long cha=mid-m*c[i];
		cha<=0?:res-=(cha+b[i]-1)/b[i];
		if(res<0){
			return 0;
		}
	}
	return 1;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&b[i]);
		c[i]=max(a[i],b[i]);
	}
	long long l=0,r=1e18;
	while(l<r){
		long long mid=(l+r+1)>>1;
		if(check(mid)){
			l=mid;
		}else{
			r=mid-1;
		}
	}
	cout<<l;
}
```

---

## 作者：leixinranYY (赞：1)

### 思路
一看这题中最小的最大，一眼就是二分答案，读完题发现后面还有一点点贪心。

看题面，描述了两种学的方法，一个是老师教，一个是自学。输入时判断哪种学法的效果更好。

接着在
 `check` 函数里，把节省下来的时间拿去补效果没多少的学科，看看能不能补完，能补完二分的左端就可以变大，如果不能补完右端就要缩小。

**注意**，本题数据过大，long long [过不了](https://www.luogu.com.cn/record/199670836)，要开 unsigned long long。

### AC 代码
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int n,m,a[300005],b[300005],ans,ma,sum;
bool check(int mid)
{
	sum=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]*m>=mid)sum+=(mid+a[i]-1)/a[i];
		else sum+=(mid-a[i]*m+b[i]-1)/b[i]+m;
	}
	if(sum<=n*m)return 1;
	return 0;
}
signed main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)
	{
		scanf("%lld",&b[i]);
		a[i]=max(a[i],b[i]);
		ma=max(ma,a[i]);
	}
    int l=0,r=ma*m+1;
    while(l<=r)
	{
    	int mid=(l+r)/2;
    	if(check(mid))l=mid+1;
    	else r=mid-1;
	}
	printf("%lld",r);
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/199671397)

---

## 作者：nytyq (赞：1)

## 分析

注意到这句话：

> 所以他想要最大化在期末考时对每门课的理解程度的最小值。

这道题很明显就是二分答案。

下文简述，我们令上课理解度为 $x$，自学理解度为 $x_1$。

对于 ```check``` 函数，我们考虑用贪心法判断：

+ $x>x_1$，我们就一直上课。
+ $x_1>x$，我们就一直自学。
+ 节省下来的时间去补那些达不到效果的科目。

对于上述讨论完成之后，考虑到两种情况：

+ 能，二分值放大。

+ 不能，二分值缩小。

## ACcode

```
#include<bits/stdc++.h>

using namespace std;

const int N=3e5+10;

typedef unsigned long long int ll;

ll n,m; 

ll A[N],B[N];

ll mat(ll x,ll y){return x>y?x:y;}

bool check(ll x){
	ll cnt=0;
	for(int i=1;i<=n;i++){
		if(A[i]*m>=x) cnt+=(x+A[i]-1)/A[i];//注意上取整细节 
		else cnt+=(x-A[i]*m+B[i]-1)/B[i]+m;
	}
	if(cnt<=n*m) return 1;
	else return 0;
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(ll i=1;i<=n;i++){
		cin>>A[i];
	} 
	for(ll i=1;i<=n;i++){
		cin>>B[i];
	}
	
	ll r=1;
	
	for(ll i=1;i<=n;i++){
		A[i]=mat(A[i],B[i]);
		r=mat(r,A[i]);
	}
	
	ll l=0;r*=m;
	
	while(l<=r){
		ll mid=l+r>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	
	cout<<r;

	return 0;
}
```

---

## 作者：ny_Dacong (赞：1)

# 翻译

>先贴一发翻译。为了方便，标题从第三级开始。

### 题目描述

JOI 高中一年级的第 $ 3 $ 学期在第 $ 1 $ 周到第 $ M $ 周之间进行，共有 $ N $ 门课程。每门课程都有一个从 $ 1 $ 到 $ N $ 的编号。同时，每一周，课程 $ i $ ($ 1\ \leq\ i\ \leq\ N $) 都会有一课时。

高中一年级的比太郎可以在 $ N\ \times\ M $ 节课中采取以下任意一种行动：

- 行动 $ 1 $：出席该节课。如果出席的这节课是课程 $ i $ ($ 1\ \leq\ i\ \leq\ N $)，则该课程的理解度将增加 $ A_i $。
- 行动 $ 2 $：不出席该节课，自由选择一门课程进行自习。如果自习的这节课是课程 $ i $ ($ 1\ \leq\ i\ \leq\ N $)，则该课程的理解度将增加 $ B_i $。

初始时，所有课程的理解度均为 $ 0 $。此外，比太郎希望在放学后花时间练习 OI ，因此他不在上课时间以外进行学习。

在第 $ 3 $ 学期的所有课程结束后，将进行期末考试。比太郎希望在考试时尽量提高理解度最低的课程，因此他希望在考试时，理解度最低的课程的理解度尽可能大。

给定学期的长度、课程数量和理解度的增量，请编写程序计算考试时理解度的最小值的最大可能值。

# 思路

考虑“最小值的最大可能值”，很明显是双最值问题。那么可以考虑二分这个值。

接下来详细说说 `check()` 函数。这里提供一种比较好写的方法。（但貌似用时是所有提交记录里最慢的？不过也就慢几十毫秒。）

首先考虑单个课程：对于这 $M$ 个课时，如果 $A_i > B_i$，那么肯定是上课更划算。否则就自习。注意，这里只讨论单个课程，不讨论在这课时自习其他课程的情况。

这是一种贪心思想，其正确性显然。

现在扩展到 $N$ 个课程。我们设当前二分的理解度为 $x$。每个课程在经过上述讨论后有两种情况：

1. 理解度至少为 $x$。
2. 理解度小于 $x$。

对于情况一，我们可以计算出多上了几课时。这些课时可以留给其他课程自习使用。

对于情况二，我们一样可以计算缺少的课时。可以从其他课程里“借”。

那么维护一个变量 $r$，计算当前剩下的多余的课时数量。对于情况一，统计多出来的课时备用。对于情况二，从 $r$ 里扣除缺少的课时。

注意：运行时 $r$ 是可以为负数的。这表示“欠”了几课时。最后只用判断 $r$ 是否大于等于 $0$ 即可。

**本题数据较大，这种写法至少需要使用 `unsigned long long` 类型。但是由于 $r$ 可以为负数，所以只好用 `__int128`**。

# 可迁移技巧

## 向上取整

对于整型之间的除法向上取整，不建议使用 `ceil()` 函数。因为这个函数必须传入浮点数，而浮点数表示的范围较小，还有精度问题。对于整型 $a$、$b$，$\lceil \frac{a}{b} \rceil$ 可以在代码中用 `(a+b-1)/b` 代替。

## `__int128` 的读入

C++ 没有提供直接读入 `__int128` 的方法。但是可以先定义一个类型为 `long long` 的临时变量，读入之后赋值给目标。同理，如果输出的结果不超范围，也可以把 `__int128` 强转成 `long long` 输出。但是一定要注意是否溢出。

## 二分求中点

数据较大时建议使用 `l+((r-l)>>1)` 来求中点。因为 `(l+r)/2` 可能溢出，这样更保险，更快。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long Read;//读入的临时变量
__int128 n,m;
__int128 a[300005],b[300005];
bool check(__int128 x){
	__int128 rest = 0,tp;//rest：多余的课时
	for(__int128 i = 1; i <= n; i++){
		if(a[i] >= b[i]){//上课比自习更优
			if(m*a[i] >= x){//有多余的课时
				tp = m*a[i]-x;//多余的理解度
				tp /= a[i];//多余的课时
				rest += tp;//备用
			}else{//缺少课时
				tp = x-m*a[i];//缺少的理解度
				tp = (tp+b[i]-1)/b[i];//向上取整
				rest -= tp;//从别的课程借课时
			}
		}else{
			if(m*b[i] >= x){//自习比上课更优
				tp = m*b[i]-x;
				tp /= b[i];
				rest += tp;
			}else{
				tp = x-m*b[i];
				tp = (tp+b[i]-1)/b[i];//向上取整
				rest -= tp;
			}
		}
	}
	return rest >= 0;//是否有剩余的课时
}
int main(){
	scanf("%lld",&Read);
	n = Read;
	scanf("%lld",&Read);
	m = Read;
	for(__int128 i = 1; i <= n; i++){
		scanf("%lld",&Read);
		a[i] = Read;
	}
	for(__int128 i = 1; i <= n; i++){
		scanf("%lld",&Read);
		b[i] = Read;
	}
	__int128 l = 0,r = 1e19+20,mid,ans = 0;//二分答案
	while(l <= r){
		mid = l+((r-l)>>1);
		if(check(mid)){
			l = mid+1;
			ans = mid;
		}else{
			r = mid-1;
		}
	}
	Read = ans;
	printf("%lld",Read);
	return 0;
}
```

---

## 作者：DHT666 (赞：1)

## 题意
一学期 $M$ 周，有 $N$ 种课，每周有 $N$ 天，第 $i$ 天可以增加使 $i$ 课程增加 $A_i$ 的权值，或者另选课程 $j$ 使其增加 $B_j$ 的权值，求 $M$ 周后每种课的权值中最小值最大可以是多少。

## 思路
最小值最大，这类问题用二分答案，然后判断函数贪心，是典型套路。

具体怎么贪心？

如果自学比上课更好，那么就去自学，直到达到目标值为止。

如果上课比自学更好，那么看一看只上课能否达到目标值。如果可以，那就尽可能少地去上课。如果达不到目标，那就先上完课，然后再尽可能少地自学。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 10, inf = 1e18; // 上限是 1e18

int n, m;
int a[N], b[N];

int read() {
    int k = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9') {
        if(c == '-') f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9') {
    	k = k * 10 + c - '0';
		c = getchar();
	}
    return k * f;
}

void write(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + '0');
    else {
		write(x / 10);
		putchar(x % 10 + '0');	
	}
}

bool check(int x) {
	int tot = 0;
	for(int i = 1;i <= n;i++) {
        // 这里三目运算符是做向上取整操作
		if(a[i] < b[i]) {
			tot += x % b[i] ? x / b[i] + 1 : x / b[i];
		} else {
			if(m * a[i] >= x) tot += x % a[i] ? x / a[i] + 1 : x / a[i];
			else tot += m + ((x - m * a[i]) % b[i] ? (x - m * a[i]) / b[i] + 1 : (x - m * a[i]) / b[i]);
		}
		if(tot > n * m) return 0;
	}
	return 1;
}

signed main() {
	n = read(), m = read();
	for(int i = 1;i <= n;i++) {
		a[i] = read();
	}
	for(int i = 1;i <= n;i++) {
		b[i] = read();
	}
	
	int l = 0, r = inf, res = 0;
	while(l <= r) {
		int mid = l + r >> 1;
		if(check(mid)) {
			l = mid + 1;
			res = mid;
		} else {
			r = mid - 1;
		}
	}
	
	write(res);
	
	return 0;
}
```

---

## 作者：ny_123457 (赞：0)

## Part 1.文字解析
题目描述中“最小值的最大可能值”这一句几乎可以说是直接告诉你本题是二分，简单分析一下题面后有感觉有点贪心的意思。那么，二分答案，启动！

本题所描述的就只有两个东西，老师教和自学。这样就可以分两种情况，如果这一门学科自学的效果比老师教的好，那么这一门学科直接自学，否则这一门学科就可以全让老师教，节省下来的时间去补那些达不到效果的学科，看看能不能补完，如果能，那么当前二分的值能继续放大，如果不能，当前二分的值就要缩小。

注意本题数据范围较大，所以要用 unsigned long long。
## Part 2.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long n,m,a[300005],b[300005],ans,maxx;
bool check(unsigned long long mid){
	unsigned long long cnt=0;
	for(unsigned long long i=1;i<=n;i++){
		if(a[i]*m>=mid)cnt+=(mid+a[i]-1)/a[i];
		else cnt+=(mid-a[i]*m+b[i]-1)/b[i]+m;
	}
	if(cnt<=n*m)return true;
	return false;
}
int main(){
    scanf("%lld%lld",&n,&m);
    for(unsigned long long i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(unsigned long long i=1;i<=n;i++)scanf("%lld",&b[i]);
    for(unsigned long long i=1;i<=n;i++){
		a[i]=max(a[i],b[i]);
		maxx=max(maxx,a[i]);
	}
    unsigned long long l=0,r=maxx*m,mid;
    while(l<=r){
    	mid=(l+r)/2;
    	if(check(mid))l=mid+1;
    	else r=mid-1;
	}
	printf("%lld",r);
	return 0;
}
```

---

## 作者：LJ26yanxingyu (赞：0)

[更好地阅读体验？](https://www.luogu.com.cn/article/ob21p7sx)  
[双倍经验](https://www.luogu.com.cn/problem/P8161)
### 思路
由于是求理解程度的**最小值的最大**可能值，所以肯定用二分，可以二分理解程度的值，然后 `check` 一下能不能达到这个值。
### check 函数
首先，如果他自学效益比上课大，那肯定自学，所以如果自学效益大于上课，直接在输入时让 `a[i]=b[i]`，到了那节课就去自学。

设 $k$ 是他学到二分出的值 $x$ 所需的课时，那么如果 $M$ 节课他能学到 $x$，就让 $k$ 加上去上课所需的课时，不然再加上还要去自学的课时。
#### 提示  
`m*a[i]` 会爆 long long，所以用人类智慧将不等式移项一下就好了。
### 代码
```cpp
#include<bits/stdc++.h>
#define Maxn 1000000000000000010

using namespace std;

long long n,m;
long long a[300005];
long long b[300005];

bool chek(long long x){
	long long k=0;
	for(int i=1;i<=n;i++){
		if(m>=(x+a[i]-1LL)/a[i]){
			k+=(x+a[i]-1LL)/a[i];//M节课他能学到,加上去上课所需的课时
		}
		else{
			k+=m+((x-a[i]*m)+b[i]-1LL)/b[i];//不然再加上去自学的课时
		}
		if(k>m*n)return false;
	}
	return k<=m*n;
}
long long erfen(long long L,long long R){
	long long mid=(L+R)/2;
	while(L<=R){
		if(chek(mid))L=mid+1;
		else R=mid-1;
		mid=(L+R)/2;
	}
	return R;
}

int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&b[i]);
		if(a[i]<b[i])a[i]=b[i];//他自学效益比上课大,自学
	}
	printf("%lld",erfen(1,Maxn));
	return 0;
}
``````

---

## 作者：ruik (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_joi2022ho_b)

[双倍经验](https://www.luogu.com.cn/problem/P8161)
### 题意
比太郎在上学期间共有 $ N \times M $ 节课的时间学习，他需要同时学习多门课。他对每一节课都有一个理解度，他希望能合理运用这 $ N \times M $ 节课的时间，使他对每一节课理解程度的最小值最大。

他可以通过自学和听课增加理解度。两者不同在于他最多只能花 M 节课听讲，但他可以用这  $ N \times M $  节课的任意时间自学。
### 思路
主体思路是二分答案，寻找出可行的最大理解度。
### 难点
比太郎可以选择自学，也可以选择听课。那他到底该如何抉择呢？

1、对于每一个理解度，如果自学的收益大于听讲的收益，比太郎肯定会只用自学。

2、而如果听讲的收益大于自学，那他便会先听讲，若将 M 节课听完了此科的理解度还是没到二分值再想办法自学。

因此我们可以直接将听讲的收益改为听讲与自学收益的最大值，这样在 check 时直接用第二种方案。
### code：

```cpp
#include <bits/stdc++.h>
#define ll unsigned long long
using namespace std;
ll n,m,a[300500],b[300500],mx;
bool _check(ll mid){
	ll cnt=0;
	for(int i=1;i<=n;i++){
		if(a[i]*m>=mid)cnt+=(mid+a[i]-1)/a[i];
		else cnt+=(mid-a[i]*m+b[i]-1)/b[i]+m;
	}
	if(cnt<=n*m)return true;
	else return false;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)scanf("%d",&b[i]);
    for(int i=1;i<=n;i++)a[i]=max(a[i],b[i]),mx=max(mx,a[i]);
    ll l=0,r=mx*m,mid;
    while(l<=r){
    	mid=(l+r)/2;
    	if(_check(mid))l=mid+1;
    	else r=mid-1;
	}
	printf("%lld",r);
    return 0;
}
```
~~其实看题解也算一种自習。~~

---


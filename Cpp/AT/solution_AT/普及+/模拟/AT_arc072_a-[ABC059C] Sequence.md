# [ABC059C] Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc059/tasks/arc072_a

長さ $ N $ の数列があり、$ i $ 番目の数は $ a_i $ です。 あなたは $ 1 $ 回の操作でどれか $ 1 $ つの項の値を $ 1 $ だけ増やすか減らすことができます。

以下の条件を満たすために必要な操作回数の最小値を求めてください。

- すべての$ i\ (1≦i≦n) $ に対し、第 $ 1 $ 項から第 $ i $ 項までの和は $ 0 $ でない
- すべての$ i\ (1≦i≦n-1) $ に対し、$ i $ 項までの和と $ i+1 $ 項までの和の符号が異なる

## 说明/提示

### 制約

- $ 2≦\ n\ ≦\ 10^5 $
- $ |a_i|\ ≦\ 10^9 $
- $ a_i $ は整数

### Sample Explanation 1

例えば、数列を $ 1,\ -2,\ 2,\ -2 $ に $ 4 $ 回の操作で変更することができます。この数列は $ 1,\ 2,\ 3,\ 4 $ 項までの和がそれぞれ $ 1,\ -1,\ 1,\ -1 $ であるため、条件を満たしています。

### Sample Explanation 2

はじめから条件を満たしています。

## 样例 #1

### 输入

```
4
1 -3 1 0```

### 输出

```
4```

## 样例 #2

### 输入

```
5
3 -6 4 -5 7```

### 输出

```
0```

## 样例 #3

### 输入

```
6
-1 4 3 2 -5 4```

### 输出

```
8```

# 题解

## 作者：tyr_04 (赞：3)

[传送门](https://www.luogu.com.cn/problem/AT_arc072_a)

~~这是一道水题，但却被评为了绿题。~~

所有数字排列一共有两种情况：

$1$.正负正负正负......

$2$.负正负正负正......

意思就是说，确定了第一个数为正或负，后面的数的正负也可以确定了。并且，为了得到最优解，每一次变号只能变为 $1$ 或 $-1$ 。明白了这个条件，打代码的就很容易了。

注意和为 $0$ 的特殊情况，如果遇到和为 $0$，要根据上一次的和来改成正或负。

# 代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100005],ans1=0,ans2=0,l=0;
bool z;
int main()
{
	long long n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	z=0;
	for(int i=1;i<=n;i++)
	{
		l+=a[i];
		if(l>=0&&z==1)
		{
			ans1+=l+1;
			l=-1;
		}
		else if(l<=0&&z==0)
		{
			ans1+=1-l;
			l=1;
		}
		if(z==1)
		{
			z=0;
		}
		else if(z==0)
		{
			z=1;
		}
	}
	z=1;
	l=0;
	for(int i=1;i<=n;i++)
	{
		l+=a[i];
		if(l>=0&&z==1)
		{
			ans2+=l+1;
			l=-1;
		}
		else if(l<=0&&z==0)
		{
			ans2+=1-l;
			l=1;
		}
		if(z==1)
		{
			z=0;
		}
		else if(z==0)
		{
			z=1;
		}
	}
	cout<<min(ans1,ans2);
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

# AT_arc072_a [ABC059C] Sequence 题解

[题面](https://www.luogu.com.cn/problem/AT_arc072_a)

## 思路

1. 题面说的有一点专业，意思就是

记 $S_i = \sum ^i_{j=1} A_j$，求最少的操作次数使得 $S_i \neq 0$ 且 $S_i$ 与 $S_{i+1}$ 异号。

2. 这道题看到后首先想到的是 $S_i$ 的符号是
- $+\ -\ +\ -\ +\ -\ +\ -\ \ldots \ldots$
- $-\ +\ -\ +\ -\ +\ -\ +\ \ldots \ldots$
3. 那么我们可以反别考虑以上两种情况，并使用贪心求解分别的答案，再去最小值。

- 当符号是 $+\ -\ +\ -\ +\ -\ +\ -\ \ldots \ldots$ 时

$
\left\{
	\begin{aligned}
    ans-sum+1 && i\bmod 2=1 \  \& \  sum \le 0\\
    ans+sum+1 && i\bmod 2=0 \  \& \  sum \ge 0\\
	\end{aligned}
\right.
$

- 当符号是 $-\ +\ -\ +\ -\ +\ -\ +\ \ldots \ldots$ 时

$
\left\{
	\begin{aligned}
    ans-sum+1 && i\bmod 2=0 \  \& \  sum \le 0\\
    ans+sum+1 && i\bmod 2=1 \  \& \  sum \ge 0\\
	\end{aligned}
\right.
$

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define re register
#define endl '\n'

const int maxn=1e5+1;
int n,a[maxn],sum,ans1,ans2;

signed main()
{
//	freopen("B.in","r",stdin);
//	freopen("B.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
		if(i%2==1&&sum<=0)
		{
			ans1-=sum-1;
			sum=1;
		}
		else if(i%2==0&&sum>=0)
		{
			ans1+=sum+1;
			sum=-1;
		}
	}
	sum=0;
	for(int i=1;i<=n;i++)
	{
		sum+=a[i];
		if(i%2==1&&sum>=0)
		{
			ans2=ans2+1+sum;
			sum=-1;
		}
		else if(i%2==0&&sum<=0)
		{
			ans2=ans2-sum+1;
			sum=1;
		}
	}
	cout<<min(ans1,ans2)<<endl;
	return 0;
}
```

---

## 作者：banned_xiejiayun (赞：1)

~~呃……你确定这是绿题？~~


### 建议降黄！


[题目传送门](https://www.luogu.com.cn/problem/AT_arc072_a)

题目说的有点专业，简单说来就是：

给定一个长度为 $N$ 的序列 $A$，每次操作可以选择一个 $i$ 使得 $A_i$ 大小减 $1$ 或加 $1$。

记 $S_i = \sum\limits_{j = 1} ^ i A_j$，求最少的操作次数使得：$ S_i \ne 0$ 且 $S_i$ 与 $S_{i + 1}$ 异号。

所以可以推断出，$S$ 序列应该是：

```
+ - + - + - + - + - + - ……
```
或者是：


```
- + - + - + - + - + - + ……
```
由此，我们可以定义两个变量，表示两种情况下的前缀和。

若本应为正却为负，就强行变为 $1$。

若本应为负却为正，就强行变为 $-1$。

需要注意的是 $0$ 的情况，当此时前缀和为 $0$ 时，无论是该正还是负，都得改变。

具体见代码：

## AC code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a;
int s1;//+ - + - + - 的情况。
int s2;//- + - + - + 的情况。
int ans1;//+ - + - + - 的情况所需改变的次数。
int ans2;//- + - + - + 的情况所需改变的次数。
signed main() {
//	freopen("B.in","r",stdin);
//	freopen("B.out","w",stdout);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a;
		s1 += a;
		s2 += a;
		if (i % 2 == 1) {//通过循环变量 i 来判断此时 s1、s2 的理想状态。
			if (s1 <= 0) {
				ans1 += (1 - s1);
				s1 = 1;
			}
			if (s2 >= 0) {
				ans2 += (s2 + 1);
				s2 = -1;
			}
		} else {
			if (s1 >= 0) {
				ans1 += (s1 + 1);
				s1 = -1;
			}
			if (s2 <= 0) {
				ans2 += (1 - s2);
				s2 = 1;
			}
		}
	}
	cout << min(ans1, ans2);//最后取两种情况的最小。
	return 0;
}
```
是不是感觉很简单？

---

## 作者：QZJ666 (赞：1)

# 1.题意
让数组的前缀和每一项不为$1$，并且让数组前缀和连续两项正负性不同。

每次可让数组中的每一项$±1$

# 2.思路
对于每一个前缀和数组有$2$种情况:

$1$:负正负正...

$2$:正负正负... 

所以我们可以写一个函数,用$-1$代表负数的情况，$1$表示正数的情况，于是每当前缀和正负性不同时，如果是要变为正数，为了使结果最小，就让它变为$1$,所以，相反就变为$-1$。

# 3.代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100005],b[100005];
long long x;
long long f(long long n) {//n是-1代表负数的情况，1表示正数的情况
	long long ans=0;
	b[0]=n;
	for(long long i=1; i<=x; i++) {
		b[0]=0;
		b[i]=a[i]+b[i-1];
		b[0]=n;
		bool flag=0;
		if(b[i-1]>0) {
			flag=1;
		}
		if(b[i]==0) {
			if(flag==1) {
				b[i]--;
				ans++;
			} else {
				b[i]++;
				ans++;
			}
		}
		if(b[i-1]>0&&b[i]>0) {
			ans+=b[i]+1;
			b[i]=-1;
		}
		if(b[i-1]<0&&b[i]<0) {
			ans+=abs(b[i])+1;
			b[i]=1;
		}
	}
	return ans;
}
int main() {
	cin>>x;
	for(long long i=1; i<=x; i++) {
		cin>>a[i];
	}
	long long xx=f(-1),xxx=f(1);
	cout<<min(xx,xxx)<<endl;
	return 0;
}
```


---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

明显的，要满足对于每个小于等于 $n-1$ 的 $i$ 使得 $\sum\limits_{j=1}^{i} A_j \times \sum\limits_{j=1}^{i+1} A_j$ 小于 $0$，需要使 $\sum\limits_{j=1}^{i} A_j$ 和 $\sum\limits_{j=1}^{i+1} A_j$ 正负号不同。

但是是先正再负还是先负再正我们并不知道，所以我们把两种都尝试一遍，输出其中较小代价者即可。

具体实现上，我们记录一个 $sum_i$ 表示 $\sum\limits_{j=1}^{i} A_j$ 的值，根据先正再负或者先负再正的顺序将 $sum_i$ 不符合顺序的项改为 $1$ 或 $-1$ 并统计差值的和即可。

### $\text{code}$


```cpp
int n;

int a[maxn];

int sum1,sum2;

void solve(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	int cnt1=0;
	for(int i=1;i<=n;i++){
		sum1+=a[i];
		if(i%2==1&&sum1>=0){
			cnt1=cnt1+sum1+1;
			sum1=-1;
		}
		if(i%2==0&&sum1<=0){
			cnt1=cnt1-sum1+1;
			sum1=1;
		}
	}
	int cnt2=0;
	for(int i=1;i<=n;i++){
		sum2+=a[i];
		if(i%2==0&&sum2>=0){
			cnt2=cnt2+sum2+1;
			sum2=-1;
		}
		if(i%2==1&&sum2<=0){
			cnt2=cnt2-sum2+1;
			sum2=1;
		}
	}
	int ans=min(cnt1,cnt2);
	write(ans);
	puts("");
	return ;
}

```

---

## 作者：mayike (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_arc072_a)
~~话说这题有点水了~~

## 思路

对于 $S_i\times S_{i+1}<0$，且 $S_i\ne 0$，则 $S_i$ 和 $S_{i+1}$ 定为一正一负，这里 $1 \le i<n$。所以 $S_1$ 只有两种可能，正或负，间接导致后面数正负一定。

那么就很好办了，分别统计当 $S_1$ 为正和负的最小操作次数，比较输出即可。

若某 $S_i$ 不符合设定的正负性，那若是正就操作成 1，若是负则操作成 -1，统计操作次数。这里变换的是 $A_i$，因为变换前面没有任何意义，反而**可能**会影响操作次数。

为何变 1 或 -1 呢？因为 1 是正整数里最小的，-1 同理。

那就可以愉快的上代码啦：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;long sum1,sum2,ans1,ans2; //记得开 long long
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;sum1+=x;sum2+=x;//前缀和更新
		if(i%2){
			if(sum1<=0)ans1+=1-sum1,sum1=1;
			if(sum2>=0)ans2+=sum2+1,sum2=-1;
		}
		else{
			if(sum1>=0)ans1+=sum1+1,sum1=-1;
			if(sum2<=0)ans2+=1-sum2,sum2=1;
		}//枯燥地更新操作次数
	}cout<<min(ans1,ans2)<<'\n';//比较两种排列的最小操作次数
	return 0;
}
```
~~还抢了个最优解，这是我万万没想到的~~

---

## 作者：qiuzijin2026 (赞：0)

# [ABC059C] Sequence

## [题面](https://www.luogu.com.cn/problem/AT_arc072_a)

## 思路

题目说得通俗一点就是：

记 $S_{i} = \sum ^{i} _ {j=1} A_{j}$，求最少的操作次数使得：

- $S_{i} \ne 0$

- $S_{i}$ 与 $S_{i+1}$ 异号

我们可以发现 $S$ 数组的符号只有以下两种情况：

- $+-+-+-+-\dots\dots$

- $-+-+-+-+\dots\dots$

于是我们就可以暴力了。

对于每一个 $S_{i}$ 如果它与它应该的符号不同，就把他改成 $1$ 或 $-1$ 统计修改了几次即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long a[100005]; 
long long ans;
long long tmp;
long long cnt;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++) scanf("%lld",&a[i]);
	ans=INT_MAX;
	tmp=0;
	cnt=0;
	for(long long i=1;i<=n;i++)
		if(i%2==1){
			cnt+=a[i];
			if(cnt<=0){
				tmp+=1-cnt;
				cnt=1;
			} 
		}
		else{
			cnt+=a[i];
			if(cnt>=0){
				tmp+=cnt+1;
				cnt=-1;
			} 
		}
	ans=tmp;
	tmp=0;
	cnt=0;
	for(long long i=1;i<=n;i++)
		if(i%2==0){
			cnt+=a[i];
			if(cnt<=0){
				tmp+=1-cnt;
				cnt=1;
			} 
		}
		else{
			cnt+=a[i];
			if(cnt>=0){
				tmp+=cnt+1;
				cnt=-1;
			} 
		}
	ans=min(ans,tmp);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Rain_Brush (赞：0)

如果要使得 $S_i \times S_{i+1}<0$，说明这两位异号。

我们并不需要考虑改了哪一位，只要保证 $S_i$ 符合就行，不难想到，将 $S_i$ 改为 $1$ 或 $-1$ 最优。

**不开 $\text{long long}$ 见祖宗。**

$\text{Code}$：
```cpp
#include <bits/stdc++.h>
using namespace std;

long long n,a[100010],sum,t1,t2; 
int main(){
	cin >> n;
	for(int i=1;i<=n;i++) cin >> a[i];
	
	for(int i=1;i<=n;i++){
		sum+=a[i];
		if(i%2==1 && sum<=0){
			t1=t1+1-sum;
			sum=1;
		}
		
		if(i%2==0 && sum>=0){
			t1=t1+sum+1;
			sum=-1;
		}
	}
	
	sum=0;
	for(int i=1;i<=n;i++){
		sum+=a[i];
		if(i%2==1 && sum>=0){
			t2=t2+sum+1;
			sum=-1;
		}
		
		if(i%2==0 && sum<=0){
			t2=t2+1-sum;
			sum=1;
		}
	}
	
	cout << min(t1,t2); //找最优解
	return 0;
}
```

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc072_a)

#### 题意

给定一个长度为 $N$ 的序列 $A$，每次操作可以选择一个 $i$ 使得 $A_i$ 大小减 $1$ 或加 $1$。

记 $S_i = \sum\limits_{j = 1} ^ i A_j$，求最少的操作次数使得：

* $\forall i \in [1, n], S_i \ne 0$

* $\forall i \in [1, n - 1], S_i \times S_{i + 1} < 0$

#### 思路

很明显这是一道贪心题，由于条件 $\forall i \in [1, n - 1], S_i \times S_{i + 1} < 0$，所以 $S_i$ 和 $S_{i + 1}$ 必须异号，那么只会有两种情况：

1. 奇数位为负，偶数位为正。
1. 奇数位为正，偶数位为负。

我们并不需要考虑改了哪一位，只要保证 $S_i$ 符合就行，不难想到，将 $S_i$ 改为 $1$ 或 $-1$ 最优。

#### 注意：要开 long long

code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100010],sum,ans,ans1; 
int main()
{
	scanf("%lld",&n);
	for(int i = 1;i <= n;i++) scanf("%lld",&a[i]);
	for(int i = 1;i <= n;i++)//求奇数位为正的，偶数位为负的 
	{
		sum += a[i];
		if(i % 2 == 1 && sum <= 0)
		{
			ans = ans + 1 - sum;
			sum = 1;
		}
		if(i % 2 == 0 && sum >= 0)
		{
			ans = ans + sum - 0 + 1;
			sum = -1;
		}
	}
	sum = 0;
	for(int i = 1;i <= n;i++)//求奇数位为负的，偶数位为正的 
	{
		sum += a[i];
		if(i % 2 == 1 && sum >= 0)
		{
			ans1 = ans1 + sum - 0 + 1;
			sum = -1;
		}
		if(i % 2 == 0 && sum <= 0)
		{
			ans1 = ans1 + 1 - sum;
			sum = 1;
		}
	}
	printf("%lld",min(ans,ans1));//求最优的 
	return 0;
}

```


---

## 作者：WaterSun (赞：0)

# 思路

我们发现要使任意的 $S_i \times S_{i + 1} < 0$，其正负性必定为：**正负正负**或者是**负正负正**。

那么，我们可以用一个函数 $\operatorname{f}(w)(w = 0,1)$ 表示以负正负正的方式/正负正负的方式所带来的代价。

在这个函数中，我们用两个变量 $sum,ans$ 分别记录前缀和和代价。

对于每一种操作，有两种情况：

1. $w = 0,sum \geq 0$，因为要使 $sum$ 为负数，那么所带来的最小代价是 $sum + 1$。

2. $w = 1,sum \leq 0$，因为要使 $sum$ 为正数，那么所带来的最小代价是 $|sum| + 1$。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 2e5 + 10;
int n;
int arr[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int f(bool w){// w = false：负  w = true：正 
	int sum = 0,ans = 0;
	for (re int i = 1;i <= n;i++){
		sum += arr[i];
		if (!w && sum >= 0){
			ans += sum + 1;//更新 
			sum = -1;
		}
		else if (w && sum <= 0){
			ans += abs(sum) + 1;//更新 
			sum = 1;
		}
		w = !w;
	}
	return ans;
}

signed main(){
	n = read();
	for (re int i = 1;i <= n;i++) arr[i] = read();
	printf("%lld",min(f(false),f(true)));//取最小代价 
	return 0;
}
```

---

## 作者：Withers (赞：0)

[题目传送门](https://atcoder.jp/contests/arc072/tasks/arc072_a)
# 题目大意
就是一个数组 $a[]$，要使它的前缀和 $pre[]$ 任意相邻两个乘积为负数，一次把其中一个数 +1 或 -1，求最少多少次

# 思路
我们可以把操作等价于修改原数组的代价是原始的数和要改的数差的绝对值

分类讨论 $pre[1]$ 的正负性然后如果要使 $pre[i-1] \times pre[i]$ 为负数，我们可以考虑贪心，如果已经是负数，就不用变了，如果是正的，就要改变 $pre[i]$ 的正负性 因为是贪心，要每一步最优那么就只需到 -1/1 就行了,记得开 long long
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100010];
bool k=0;//存正负性，0为负，1为正 
long long run(bool k)
{
	long long pre=0,ans=0;
	for(int i=1;i<=n;i++)
	{
		pre+=a[i];//前缀和，下面是分类处理 
		if(pre>=0&&k==0) 
		{
			ans+=(pre+1);
			pre=-1;
		}
		else if(pre<=0&&k==1)
		{
			ans+=(-pre+1);
			pre=1;
		}
		k=!k;
	}
	return ans;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	cout<<min(run(0),run(1));//分类取最小值 
}
```


---


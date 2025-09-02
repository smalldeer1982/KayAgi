# Successive Subtraction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/diverta2019-2/tasks/diverta2019_2_c

黒板に $ A_1,\ A_2,\ ...,\ A_N $ の $ N $ 個の整数が書かれています。

以下の操作を $ N-1 $ 回繰り返して黒板にただ $ 1 $ つの整数が書かれているようにします。

- $ 2 $ 個の整数 $ x,\ y $ を選んで消し、新たに $ 1 $ 個の整数 $ x-y $ を書く。

ただ $ 1 $ つ残る整数としてありうる値の最大値と、その最大値を達成する操作列を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ -10^4\ \leq\ A_i\ \leq\ 10^4 $
- 入力は全て整数である

### Sample Explanation 1

$ 1 $ 回目の操作で $ x $ として $ -1 $、$ y $ として$ 1 $ を選ぶと、黒板に書かれている整数は $ (-2,\ 2) $ になります。 $ 2 $ 回目の操作で $ x $ として $ 2 $、$ y $ として$ -2 $ を選ぶと、黒板に書かれている整数は $ (4) $ になります。 よって $ 4 $ がただ $ 1 $ つ残り、$ 5 $ 以上の整数がただ $ 1 $ つ残ることはないので、これが最大です。

## 样例 #1

### 输入

```
3
1 -1 2```

### 输出

```
4
-1 1
2 -2```

## 样例 #2

### 输入

```
3
1 1 1```

### 输出

```
1
1 1
1 0```

# 题解

## 作者：Gaoyx (赞：3)

一道贪心题。
## 思路
分类讨论：

- 如果这个数等于零，那么没有作用。

- 如果这个数小于零，那么最优则是有最大的数减去这个数。

- 如果这个数大于零，则最优是用最小的数减去这个数。

最后答案则是最大值减最小值。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
long long n, tot, a[110000], aa[110000], aaa[110000], ans, ma, mi;
int main() {
	cin >> n;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i];
	}
	sort(a+1,a+n+1);
	for(int i=2;i<n;i++)
	{
		if(a[i] > 0)
		{
			tot++;
			aa[tot] = a[1], aaa[tot] = a[i];
			a[1] = a[1] - a[i];
		}
		else
		{
			tot++;
			aa[tot] = a[n],aaa[tot] = a[i];
			a[n] = a[n] - a[i];
		}
	}
	cout << a[n] - a[1] << "\n";
	for(int i=1;i<=tot;i++) cout << aa[i] << " " << aaa[i] << "\n";
	cout << a[n] << " " << a[1];
	return 0;
}
```
感谢 zimujum 的宝贵思路。


---

## 作者：zimujum (赞：3)

## 思路
按照题意，我们可以知道我们需要在相减的情况下，找到我们能得的最大值，而数据给的 $-10^4\ \leq\ A_i\ \leq\ 10^4$，也就给了一个思路：将所有的正数都让最小的数减掉，让最大的数将除去最小数的负数都减掉，这样得到的数就是最大的。

## 代码
按照思路写即可。
```
#include <bits/stdc++.h>
#define itn int
#define ll long long
#define ull unsigned long long
#define AC return 0
using namespace std;
const ll M=114514;
int n;
int a[M];
int b[M],c[M];//b和c进行储存被减数。
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin >> n;
	for(int i=1;i<=n;i++) cin >> a[i];
	sort(a+1,a+n+1);//排序为了便于计算。
	for(int i=2;i<n;i++){//从第二小开始，大于零被最小的减，小于零被最大数减。
		if(a[i]>0){
			b[i]=a[1];c[i]=a[i];
//			cout << a[1] << " " << a[i] << endl;
			a[1]=a[1]-a[i];
		}else{
			b[i]=a[n];c[i]=a[i];
//			cout << a[n] << " " << a[i] << endl;
			a[n]-=a[i];
		}
	}
	
	cout << a[n]-a[1] << endl;//按要求输出最大数。
	
	for(int i=2;i<n;i++){
		cout << b[i] << " " << c[i] << endl;
	}
	cout << a[n] << " " << a[1] << endl;//最后输出最大减最小。
	
	
//	fclose(stdin);
//	fclose(stdout);
	AC;
}
//请放心食用，是安全无风险的美味代码欧。

```

还是 very easy 啊。

---

## 作者：pm_fp (赞：2)

### 思路

一眼数据范围，数不是很大，考虑正，负，零三种情况，然后暴力即可

由于只能做减法，先查找出来初始黑板上的最大值和最小值，接下来的操作，使初始最大值越来越大，初始最小值越来越小，那么最终的答案就是最大的

接下来考虑三种情况：

1. 这个数是正数，则用最小值减整个数，使最小数越来越小

1. 这个数是负数，则用最大值减整个数，使最大数越来越大

1. 这个数是零，对最大值最小值均无贡献，但不要忘记，最后输出被减数和减数时要用上

最后当然就是用最终最大值减最终最小值啦

### 码
```
#include<bits/stdc++.h>
using namespace std;
int n;
int a[1919810];
int maxn=-100000,minn=100000;
int ma,mi;
int b[1919810],c[1919810];
int t;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]>maxn) maxn=a[i],ma=i;
	}//找最大值 
	for(int i=1;i<=n;i++){
		if(i!=ma){
			if(a[i]<minn) minn=a[i],mi=i;
		}
	}//找最小值 
	for(int i=1;i<=n;i++){
		if(i!=ma&&i!=mi){
			if(a[i]>0){//判断正数情况 
				t++;
				b[t]=minn;
				c[t]=a[i];
				minn-=a[i];
			}
			if(a[i]<=0){//判断其他情况 
				t++;
				b[t]=maxn;
				c[t]=a[i];
				maxn-=a[i];
			}
		}
	}
	cout<<maxn-minn<<endl;//输出最终答案 
	for(int i=1;i<=t;i++){
		cout<<b[i]<<" "<<c[i]<<endl;//输出被减数和减数 
	}
	cout<<maxn<<" "<<minn;//输出最大值和最小值 
	return 0;//功德圆满 
}
```


---

## 作者：topcsa (赞：0)

## 算法

这是一道基础的贪心题，想不到竟然会有这么简单的黄题。

## 思路

首先，因为这是跟大小写密切相关的题目，所以要先排序。要使最后的差尽量大，可以把负数（包括 $0$）和正数分开讨论：

+ 如果是正数，则用最小数减当前数。
+ 否则则是负数，用最大数减这个数。

为什么这样做是正确的？

因为把正数做减数，会让数越来越小，把负数做减数，会使数越来越大，我们让最小数越来越小，让最大数越来越大，这样最大数 $x$ 减去最小数 $y$ 的值才会最大。

## Code

下面是带有注释的 AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N];
struct node {
	int x, y; // x 表示被减数，y 表示减数
};
node pos[N];
int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a + 1, a + n + 1); // 排序
	int cs = 0; // 操作次数
	for (int i = 2; i < n; i++) { // 保留 a[1] 和 a[n] 两个极端值
		if (a[i] > 0) { // 如果是正数，按上面思路的操作
			cs++;
			pos[cs].x = a[1]; // 记录
			pos[cs].y = a[i];
			a[1] -= a[i];
		}
		else { // 如果是负数，按上面思路的操作
			cs++;
			pos[cs].x = a[n]; // 记录
			pos[cs].y = a[i];
			a[n] -= a[i];
		}
	}
	cout << a[n] - a[1] << '\n'; // 求出最终值
	for (int i = 1; i <= cs; i++) { // 输出每次的操作
		cout << pos[i].x << ' ' << pos[i].y << '\n';
	}
	cout << a[n] << ' ' << a[1] << '\n'; // 最后一次的减法不能漏
	return 0;
}

```
## 注意
一定要输出最后一步操作，因为最后一步是不会加入到 pos 数组里的。

---

## 作者：joker_opof_qaq (赞：0)

贪心就可以了。

## 题意简述

给定 $n$ 个正整数 $A_1, A_2, A_3, \cdots, A_N$。

通过进行 $n-1$ 次将 $x$ 和 $y$ 变成 $x-y$ 的方式求出最后一个数字的最大值。

## 思路 && 解法

每次进来一个数 $x$，我们都判断：

- 如果 $x < 0$，那么就用最大值减掉它，让最大值更大。

- 如果 $x > 0$，那么就用最小值减掉它，让最小值更小。

- 如果 $x = 0$，那么它什么用都没有，我们直接把他减给最大值，或者减给最小值都可以。

---

## 作者：smartdevil (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_diverta2019_2_c)

## 思路：

一道贪心题，直接暴力正，负，零三种情况，让最大值越来越大，最小值越来越小。

讨论三种情况：

如果是正数，则用最小值减这个数，使最小数越来越小。

如果是负数，则用最大值减这个数，使最大数越来越大。

如果是零，对最大值最小值都没变化，但是最后输出被减数和减数时要用上。

最后用最大值减最小值就好了。

## 代码：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>
#include<map>
#include<list>
#include<stack>
#define int long long
using namespace std;
int n,a[2000001],maxx=-114514,minn=114514,n,m;
int x[2000001],y[2000001],cnt;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]>maxx){
		    maxx=a[i];
		    n=i;
		}
	} 
	for(int i=1;i<=n;i++){
		if(i!=n){
			if(a[i]<minn){
			    minn=a[i];
			    m=i;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(i!=n&&i!=m){
		    if(a[i]<=0){
				cnt++;
				x[cnt]=maxx;
				y[cnt]=a[i];
				maxx-=a[i];
			}
			else{
				cnt++;
				x[cnt]=minn;
				y[cnt]=a[i];
				minn-=a[i];
			}
		}
	}
	cout<<maxx-minn<<endl; 
	for(int i=1;i<=cnt;i++)cout<<x[i]<<" "<<y[i]<<endl;
	cout<<maxx<<" "<<minn;
	return 0;
}
```

## code:[AC code](https://www.luogu.com.cn/record/177702653)

---

## 作者：封禁用户 (赞：0)

## 前言：
竟然有如此水的黄题。

## 思路：

这是一道非常经典的贪心问题。

我们要考虑三种情况：

如果当这个数是正数，则用最小值减整个数，使最小数越来越小。

如果当这个数是负数，则用最大值减整个数，使最大数越来越大。

如果当这个数是零，对最大值最小值均无贡献，但不要忘记，最后输出被减数和减数时要用上。

最后输出最大值减最小值即可。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N=110000;
long long n,a[N],b[N],c[N],sum=0;

int main()
{
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for(long long i=1;i<=n;i++)
	{
		cin >> a[i];
	}
	sort(a+1,a+n+1);
	for(long long i=2;i<n;i++)
	{
		if(a[i] > 0)
		{
			sum++;
			b[sum]=a[1];
			c[sum]=a[i];
			a[1]=a[1]-a[i];
		}
		else
		{
			sum++;
			b[sum]=a[n];
			c[sum]=a[i];
			a[n]=a[n]-a[i];
		}
	}
	cout << a[n]-a[1] << endl;
	for(long long i=1;i<=sum;i++)
	{
		cout << b[i] << " " << c[i] << endl;
	}
	cout << a[n] << " " << a[1] << endl;
	return 0;
}
``````

---

## 作者：chl090410 (赞：0)

## The Solution to AT_diverta2019_2_c Successive Subtraction

### Description

黑板上有 $N$ 个数，每次可以选择两个数 $x,y$ 擦掉并写上 $x-y$，直到只剩一个数，问最终剩下的那个数的最大值及得到这个数的操作方法。

### Solution

因为总有一个数要成为被减数，总有一个数要成为减数，而要求最大数，所以我们让最大数成为这个不变的被减数，最小数作为不变的减数。

而对于其他的数，因为 $a-(b-c)=a-b+c$，所以若其为正数，我们就用最小值减去这个数，最后用最大值减掉最小值就能把这些正数全部加进答案。

而若一个数为负数，直接用最大值减去这个数即可，这样最终答案也会增大。

对于 $0$，无论加或减对最终结果都没有影响，此时不用处理，但是不要忘记输出操作方法时也要输出它即可。

而操作方法则直接输出每一步的被减数、减数即可。

### AC code 如下：

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100005],k,c,m,l,p,o,u;
queue<int> q1,q2;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		o-=a[i];
	}
	sort(a+1,a+n+1);
	q2.push(a[1]);
	for(int i=2;i<=n-1;i++){
		if(a[i]>=0){
			q1.push(a[i]);
			u+=a[i];
		}else{
			q2.push(a[i]);
			u-=a[i];
		} 
	}
	if(a[n]>0)	u+=a[n];
	else u-=a[n];
	if(a[n]<0){
		cout<<o+2*a[n]<<endl;
	}else{
		cout<<u-a[1]<<endl;
	}
	while(!q1.empty()){
		int u=q1.front(),v=q2.front();
		q1.pop();q2.pop();
		cout<<v<<" "<<u<<endl;
		q2.push(v-u);
	}
	while(!q2.empty()){
		cout<<a[n]<<" "<<q2.front()<<endl;
		a[n]-=q2.front();
		q2.pop();
	}
	return 0;
}

---

## 作者：GI录像机 (赞：0)

## 思路：

考虑让最大的数作为最后一个被减数。对于每个负数，可以直接让最大的数减去它，显然更优。对于每个正数，可以让最小的数减去它，最后再让最大的数减去最小的数，就可以把减号消掉，让最大的数加上正数。$0$ 显不会对答案产生贡献。

当最小的数最初不为正数时，该解法能得到所有数的绝对值之和，显然为最优解。

当最小的数最初为正数时，该解法能得到除最小的数外所有数的绝对值之和减去最小的数。由于去掉最后一次操作后只有 $n-2$ 次操作，所以总有一个数的符号无法变更。该解法仍为最优解。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 1e5 + 10, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int n = read(), a[N], sum;
queue<int>q;
signed main() {
	for (int i = 1; i <= n; i++) {
		a[i] = read();
		sum += abs(a[i]);
	}
	sort(a + 1, a + n + 1);
	int now = a[1];
	for (int i = 2; i < n; i++) {
		if (a[i] >= 0) {
			q.push(now);
			q.push(a[i]);
			now -= a[i];
		} else {
			q.push(a[n]);
			q.push(a[i]);
			a[n] -= a[i];
		}
	}
	q.push(a[n]);
	q.push(now);
	a[n] -= now;
	write(a[n]);
	putchar('\n');
	while (!q.empty()) {
		write(q.front());
		q.pop();
		putchar(' ');
		write(q.front());
		q.pop();
		putchar('\n');
	}
	return 0;
}
```


---


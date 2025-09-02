# Little Pony and Sort by Shift

## 题目描述

一天，暮光闪闪对如何给一个整数数组按照不递减顺序排序产生了兴趣。作为一只年轻的独角兽，她能做的只有一个操作：单位移动。她可以把最后一个元素移动到第一个去：$a_1,a_2,\cdots ,a_n\to a_n,a_1,a_2,\cdots ,a_{n-1}$
帮助暮光闪闪确定：最少需要花多少次操作才能把数组排好序？

## 样例 #1

### 输入

```
2
2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 3 2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
2
1 2
```

### 输出

```
0
```

# 题解

## 作者：Dancing_Wave (赞：5)

对于这道题的操作，我们可以换一个角度理解。

把数列头尾连起来，每次操作=把这个环顺时针旋转一格。

那么我们可以很容易地得出结论：一个可以达到题目条件的“环”最多只有一组相邻的数（包括 $a_{n}$ 和 $a_{1}$ )满足左边的数大于右边的数。我们称这组数叫做“逆序对”（跟定义的不太一样）。

而且这时我们就要把右边的数“旋转”到 $a_{1}$ 的位置。

我们定义两个变量 $x$ 和 $y$ , $x$ 表示“逆序对”的数量， $y$ 表示第一组“逆序对”右边的数。

我们记录x的时候，只要当 $x\ge 2$ 是，立刻输出-1并结束程序就可以了。

然后如果 $x=0$ 或 $y=1$ 就输出0。

否则输出 $n-y+1$ 。

[运气很好，一遍AC了。](https://www.luogu.com.cn/record/31802455)

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[100010];//存数列
int main(){
	cin>>n;
	int cnt=0;//前面讲的x
	for(int i=1;i<=n;i++){
		cin>>a[i];
	} 
	int fir;//前面讲的y
	for(int i=2;i<=n;i++){
		if(a[i]<a[i-1]){
			if(cnt==0){
				cnt++;
				fir=i;
			}else{//如果cnt>=2，输出-1，并结束程序
				cout<<-1<<endl;
				return 0;
			}
		}
	}
	if(a[1]<a[n]){
		if(cnt==0){
			cnt++;
			fir=1;
		}else{//如果cnt>=2，输出-1，并结束程序
			cout<<-1<<endl;
			return 0;
		}
	}
	if(cnt==0||fir==1){//序列已经满足题目条件不需要操作
		cout<<0<<endl;
	}else{
		cout<<n-fir+1<<endl;//输出操作数
	}
	return 0;
}

```

看在我每句话都打了空格的份上，给个赞再走呗。

---

## 作者：_Lightning_ (赞：2)

## Little Pony and Sort by Shift

### 思路：

题目问最少需要花多少次操作才能把数组排成单调递增数列，并且只能移动最后一位。所以，我们只需要查询一下单调递增数列的个数，如果有两个就输出后一个单调递增数列的长度，大于两个就输出 $-1$。

注意本身有序的情况，在末尾输出 0。

### AC Code:


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n,a[N];
int main() {
	cin>>n;
	for (int i = 1; i <= n; i++)
		cin>>a[i];
	for (int i = 2; i <= n; i++) {
		if (a[i-1]>a[i]) {
			for (int j = i + 1; j <= n; j++) {
				if (a[j-1]>a[j]) {
					cout<<"-1\n";
					return 0;
				}
			}
			if (a[n]>a[1]) {
				cout<<"-1\n";
				return 0;
			}
			cout<<n-i+1<<'\n';
			return 0;
		}
	}
	cout<<"0\n";
	return 0;
}
```

@written by _lightning_

---

## 作者：IkeveLand (赞：1)

本蒟蒻已经在 vjudge 上测过，可以放心食用。
### 题目大意：
给你一个序列，不停的将最后一个元素移动到最前边，询问你最少经过多少次可以变成一个单调递增的序列，否则输出 $-1$。 
### 思路：
1. 假设该序列按照不断从后向前移动即可，那么该序列要么只有一段单调递增的序列。
2. 要么有两段单调递增的序列，分别为 $1$ 到 $k$ 和 $k+1$ 到 $n$，并且其最大值 $sum[n]\le $ 第一段的最小值 $sum[1]$。

### Code： 

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+100;

int n;
int a[N];
signed main ()
{
	scanf("%d",&n);
	int res=0;
	int cur=0,pp=0;
	for (int i=1;i<=n;i++){
		int aa;
		scanf("%d",&aa);
		a[i]=aa;
		if (aa<cur) res++,pp=i;
		cur=aa;
	}
	if (res==0) puts("0");
	else if (res>1) puts("-1");
	else {
		if (a[n]>a[1]) puts("-1");
		else printf("%d\n",n-pp+1);
	}
	return 0;
}
```

---

## 作者：wuzihe (赞：0)

### 题目描述

[题目传送门](https://www.luogu.com.cn/problem/CF454B)。

给定一个长度为 $n$ 的数组 $a$，每次可以将最后一个元素移动到第一个，问：至少需要几次操作，让序列从小到大排好序，若无解输出 $-1$。

------------

### 算法1
##### (暴力枚举)

不难想到，将最后一个元素拼接在第一个元素之前，再把最后一个元素删去，判断一下是否有序即可。

时间复杂度 $O(n^2)$。

#### C++ 代码
请读者自行实现。

----------

### 算法2

在算法一中，主要是枚举字串并判断的时间太长了，于是我们考虑优化一下。

假设当前枚举到了 $i$ 这个点，其前面的数组都是从小到大排好序的，所以前面的元素一定不会被拆分。于是考虑第 $i + 1$ 个元素。

* 若 $a_i < a_{i + 1}$：只要把 $i$ 指针往后移即可。
* 若 $a_i > a_{i + 1}$：这种情况如果直接将其跳过肯定是不行的，所以一定得挪动 $i$ 后面的元素依次放到前面，而且后面的元素一定有序且最后一个元素不能大于第一个元素。

按照上面的分析，可以发现将最后一个元素移到最前边，实际上就是为了将满足 $a_{i-1} > a_i$ 的两个元素分离，成为合法的序列。但是如果有两组以上这样的元素，就无法满足题目要求了。

时间复杂度 $O(n)$。

----------
#### C++ 代码
```
#include <iostream>
using namespace std;

const int N = 100010;
int n;
int a[N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	
	a[0] = a[n];
	
	int cnt = 0, ans = -1;
	for (int i = 0; i <= n; i++)
		if (a[i-1] > a[i]) { // 统计逆序对
			cnt++;
			ans = n - i + 1;
		}
	ans %= n; // 如果ans > n，肯定也可以用ans % n来满足题目要求。
	cout << (cnt > 1 ? -1 : ans) << endl;
	
	return 0;
}
```

---

## 作者：louliu (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF454B)

## 分析

首先是关于元素移动：

### 情况一

$1\ 2\ 3\ 4\ 5\ 6$

这是一组排序好的数据。

我们能在其中发现一个规律，$a_i$ 必定是大于 $a_{i-1}$ 的（即必须为单调队列）！

### 我们设 $b_i$ 等于 $a_i$，且 $ans$ 为记录个数的单位。

```cpp
if(b[i]<b[i-1]){
	ans++;//记录数组，不符合该规律的加一 
}
```


### 情况二

$3\ 4\ 5\ 6\ 1\ 2$

这又是一串乱序数字。

其中 $a_i$ 大于 $a_{i-1}$ 的次数只有一次（首尾交界处，极有可能相差极大）！

所以超过一次直接退出（单调队列已经被破坏掉了，这个数组不可能有序，因为首尾情况最多出现一次）。

```cpp
if(ans==2){
	cout<<-1;//不要犹豫，直接退出 
	return 0;
}
```


### 情况三

$1\ 3\ 2\ 4\ 5\ 6$

一串不能成立的数字。

但在刚刚的条件下，却可以成立。

所以我们加入最后一个条件：$a_n$ 不能大于 $a_1$（首尾交界处的特殊情况，循环是无法审查到的）！

其他的时候就直接记录 $a_i$ 大于 $a_{i-1}$ 的那唯一一个值，那就是两数交替处（这样也不会影响队列单调性，类似于特判）！

```cpp
if(b[a]>b[1]){//情况三
	if(ans==1){//ans也等于一（单调破坏了）
		cout<<-1;
		return 0;
	}
  	else if(ans==0){//可能位置就不用改变，还要给当前交界处赋值
		ans++;
      		k=1;
	}
}
```


### 特殊情况

$1\ 1\ 1\ 1\ 1\ 1$

该样例没有任何一个交替处（这也不会影响队列单调性），所以要进行特判，如果交替处为零，直接输出 $0$。

```cpp
if(ans==0||k==1) cout<<0;//特殊情况
```

如果不输出 $-1$，那么就将总数减交替处再加一即可。

代码就这么分析出来了！

#### 注意边界问题

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b[100005],ans;
int k;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>a;
	for(int i=1;i<=a;i++){
		cin>>b[i];
	}
	for(int i=2;i<=a;i++){//边界问题
		if(b[i-1]>b[i]){//情况一
			if(ans==0){
				k=i;
			}
			ans++;
			if(ans==2){//情况二
				cout<<-1;
				return 0;
			}
		}
	}
	if(b[a]>b[1]){//情况三
		if(ans==1){
			cout<<-1;
			return 0;
		}
  		else if(ans==0){
			ans++;
        k=1;
		}
	}
  	if(ans==0||k==1) cout<<0;//特殊情况，本就在原来位置上
	else if(k==0){
		cout<<a;
	}
	else{
		cout<<a-k+1;
	}
	return 0;
} 
```

如果大家还有疑问，可以在评论区留言，作者会及时解答并更新题解！

---

## 作者：liuzhongrui (赞：0)

## 思路
题目中说可以把最后一个元素移动到第一个去，我们可以将它理解为 $a_0 = a_n$，那么这个序列就变成了 $a_n , a_1 , a_2 , a_3 ⋯ a_{n-1} , a_n$。

如果该序列中仅存在一对递减的数，其实是合法的，但当出现了多对这样的数，那就是不合法的，应输出 ```-1```。

从 $1$ 到 $n-1$ 遍历，如果一对数递增，即左边的数大于右边的数，我们记录一下左边的数（记录为 $last$），特别的如果这对数正好是 $a_1$ 和 $a_n$，我们还要看看它满不满足 $a_1 < a_n$，如果满足，也要参与统计。

最后，如果满足 $last = n$ 或 $n - last = n$，这些情况都是输出 ```0```；如果不满足这些情况，输出 $n - last$ 即可。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int n, a[N], cnt, last;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	if (a[1] < a[n]) {
		last = n;
		cnt++;
	}
	for (int i = 1; i < n; i++) {
		if (a[i] > a[i + 1]) {
			last = i;
			cnt++;
		}
	}
	if (cnt > 1) {
		cout << -1; 
		return 0;
	}
	if (last == n) { 
		cout << 0; 
		return 0;
	}
	if (n - last == n) { 
		cout << 0; 
		return 0;
	}
	cout << n - last; 
	return 0;
}
```



---

## 作者：L_shadow (赞：0)

## 思路：
先让 $a_0=a_n$，形成了一个环，再遍历一遍，统计 $a_{i-1}<a_i$ 的 $i$ 个数。

很容易想，如果这个序列，有多（$\ge 2$）个下降的点，我们只能把其中一个放在序列的头，另一个将会在后面的序列中，不能形成单调递增。

如果只有一个，把它放在序列的头，剩下的一定是单调递增的序列，此时的花费是 $n-i-1$。

## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],n,cnt,p;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	a[0]=a[n];
	for(int i=1;i<=n;i++){
		if(a[i]<a[i-1]){
			cnt++;
			p=n-i+1;
		}
		if(cnt>1){
			cout<<-1;
			return 0;
		}
	}
	if(p==n) cout<<0;
	else cout<<p;
	return 0;
}

```


---

## 作者：fz20181223 (赞：0)

将原数组复制一份到最后，那么我们只需在新的数组中找出一个长度大于等于 $n$ 的非严格递增序列即可。

故有了以下的代码。

关于答案统计（ans 变量）：根据方案，可得知最后答案即为 $2n$ 减去非严格递增序列的末尾位置。但是我们貌似统计出的是比较次数，所以真正的操作次数为从 $i$ 变为 $n$ 以下后的次数（初值 $2n-1$）。

若扫描完了数组未果，则说明不存在实现方案。整个算法复杂度 $O(n)$ 级别。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9;
int a[N<<1],n,cnt=0;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",a+i);
		a[n+i]=a[i];
	}
	for(int i=(n<<1)-1,ans=0;i>=1;--i){
		if(cnt==n-1){
			printf("%d",ans);
			return 0;
		}
		if(a[i]<=a[i+1]) cnt++;
		else cnt=0;
		ans+=(i<=n);
	}
	printf("-1");
	return 0;}
```

---

## 作者：Tune_ (赞：0)

这题呢，只要找对思路，打代码就不是问题！

最后要求是让数组按照不递减顺序排序，那么，如果这个数组可以通过“把最后一个元素移动到第一个去”这样的操作进行排序，就只存在一个数a[i]，符合a[i-1]>a[i]的条件。只要找到这个数，n-i+1就是答案。

当然，存在移动0次的数据（数组本身已经有序），所以要记得特判哦~

下面附上~~简洁的~~代码：

```
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=2;i<=n;i++)//开始判断
	{
		if(a[i-1]>a[i])//找到符合条件的数
		{
			for(int j=i+1;j<=n;j++)
			{
				if(a[j-1]>a[j])//如果后面还有，就输出-1
				{
					cout<<-1;
					return 0;
				}
			}
			if(a[n]>a[1])//注意是前后连接的，a[n]和a[1]也要判断
			{
					cout<<-1;
					return 0;
			}
			cout<<n-i+1;
			return 0;
		}
	}
	cout<<0;//特殊情况
	return 0;//拜了个拜
}

```

走过路过，给本蒟蒻点个赞吧~(〃'▽'〃)~

---

## 作者：chenkaiwen (赞：0)

这一题是对点调递增增数列的操作，这一题中，我们对于一个数列，有以下三种可能：

1. 只有一个单调递增数列，也就是整个数列都是递增排序的，所以直接输出0就可以了
2. 有两个单调递增数列，我们要做的就是把第二个数列的数都转移到前面去，所以输出第二个数列的长度
3. 有三个或三个以上，则不可能排序成功，那么输出-1

我们需要做的就是模拟上述三种情况，首先，我们用 $O(n)$ 的算法获得有多少个单调递增数列和第二个数列的长度（如果有的话），如果是第一种情况，直接输出0，如果是第二种输出我们已经获得的第二个数列的长度，如果是第三种情况，则输出-1，其他细节我会在代码的注释中详细写出，这里就不多讲了。

代码如下：

```cpp
#include<bits/stdc++.h>
#include <iostream>
using namespace std;
int a[10001];//储存输入 
int s=1,ans=0,n;
int main() {
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=0; i<n; i++) {
		cin>>a[i];
	}//输入 
	bool q=0;
	int l=0;
	for(int i=0; i<n-1; i++) {
		if(a[i]<=a[i+1]) {//查找单调递增数列 
			q=1;
			l++;
			ans=l;//储存长度 
		} else if(q==1) {
			q=0;//
			s++;
		}
	}
	if(s==1) {//三种情况 
		cout<<0<<endl;
	} else if(s==2) {
		cout<<ans<<endl;
	} else {
		cout<<"-1"<<endl;
	}
	return 0;
}




```


---

## 作者：Jason_Lee (赞：0)

一道大水题，来水一些贡献：

首先，题目要求最少需要花多少次操作才能把数组排成单调递增数列，并且只能移动最后一位。

所以，我们只需要判断一下单调递增数列的个数，如果只有一个就输出0，两个就输出后一个的长度，大于两个输出-1.

代码：

```
#include <bits/stdc++.h>

const int N = 100005;
using namespace std;

int n;
int a[N];

int main()
{
//	freopen("std.in","r",stdin);
//	freopen("bf.out","w",stdout);
    scanf("%d",&n);
    for (int i = 1; i <= n; i++) scanf("%d",&a[i]);
    for (int i = 2; i <= n; i++) {
        if (a[i-1]>a[i])
        {
            for (int j = i + 1;j <= n; j++) {
                if (a[j-1]>a[j]) {printf("-1\n");return 0;}
            } 
            if (a[n]>a[1]) {printf("-1\n");return 0;}
            printf("%d\n",n-i+1);return 0;
        }
    }
    printf("0\n");
    return 0;
}
```


---


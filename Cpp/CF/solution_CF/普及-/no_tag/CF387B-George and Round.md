# George and Round

## 题目描述

George decided to prepare a Codesecrof round, so he has prepared $ m $ problems for the round. Let's number the problems with integers $ 1 $ through $ m $ . George estimates the $ i $ -th problem's complexity by integer $ b_{i} $ .

To make the round good, he needs to put at least $ n $ problems there. Besides, he needs to have at least one problem with complexity exactly $ a_{1} $ , at least one with complexity exactly $ a_{2} $ , ..., and at least one with complexity exactly $ a_{n} $ . Of course, the round can also have problems with other complexities.

George has a poor imagination. It's easier for him to make some already prepared problem simpler than to come up with a new one and prepare it. George is magnificent at simplifying problems. He can simplify any already prepared problem with complexity $ c $ to any positive integer complexity $ d $ ( $ c>=d $ ), by changing limits on the input data.

However, nothing is so simple. George understood that even if he simplifies some problems, he can run out of problems for a good round. That's why he decided to find out the minimum number of problems he needs to come up with in addition to the $ m $ he's prepared in order to make a good round. Note that George can come up with a new problem of any complexity.

## 说明/提示

In the first sample the set of the prepared problems meets the requirements for a good round.

In the second sample, it is enough to come up with and prepare two problems with complexities $ 2 $ and $ 3 $ to get a good round.

In the third sample it is very easy to get a good round if come up with and prepare extra problems with complexities: $ 2,3,4 $ .

## 样例 #1

### 输入

```
3 5
1 2 3
1 2 2 3 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3 5
1 2 3
1 1 1 1 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 1
2 3 4
1
```

### 输出

```
3
```

# 题解

## 作者：残阳如血 (赞：4)

# 思路分析
因为最终要使得 $a,b$ 相同，所以我们应该希望让相同的数字尽量相同。所以，我们需要先对 $a$ 和 $b$ 进行排序，这样子就可以使用**双指针**的方法来维护最终值了。

我们定义 $l$ 指针指向 $a_l$，$r$ 指针指向 $b_r$。因为题目要求**添加数字的次数最少**，所以我们希望尽可能地来缩小数字以减少添加数字的次数。所以如果 $a_l<b_r$，那么我们可以将 $l$ 增加$1$，代表我们对于这个数可以采用减少的方法。对于每次操作，我们都需要将 $r$ 增加 $1$，是因为我们不能重复地操作 $b_r$。

# 复杂度分析
## 时间复杂度
整个程序的**性能瓶颈在于对所有点进行排序**，时间复杂度是 $\mathcal O(n\log n)$ 的，对于 $1\le n,m\le3000$ 的范围是丝毫没有问题的。
## 空间复杂度
我们需要两个数组 $a$ 和 $b$ 来存储值，$a$ 的大小为 $n$，$b$ 的大小为 $m$，所以最终的空间复杂度是 $\mathcal O(n+m)$，也是没有问题的。
# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, l, r;
int main() {
	cin >> n >> m;
	vector<int> a(n), b(m);
	for (auto &x : a) cin >> x;
	for (auto &x : b) cin >> x;
	sort(a.begin(), a.end()); // 对a数组排序
	sort(b.begin(), b.end()); // 对b数组排序
	while (l < n && r < m) {
		if (a[l] <= b[r]) l++; // 如果a[l]<=b[r]，那么我们只需将b[r]减少，不用添加数字
		r++; // 继续比较下一位
	}
	cout << n - l; // 共有n个数字，去掉减小数字的次数，就是添加数字的次数了
	return 0;
}
```

---

## 作者：k_17 (赞：2)

[CF387B George and Round](https://www.luogu.com.cn/problem/CF387B)
### 题意
给出 $a$、$b$ 两个数组（已从下到大排序）以及它们的长度 $n$、$m$。你可以在 $b$ 数组中添加一个数（大小不限）或减小 $b$ 数组中的数（注意，是减小，不是减少）来使得 $a$ 数组中的任意一个元素都有一个 $b$ 中的对应元素（不与其他元素共享。如 $a$ 中有两个 $1$ 则 $b$ 中至少要有两个 $1$ 或比 $1$ 大的数。），现求最小添加次数。

------------
### 思路
由于添加的数大小不限而且可下调 $b$ 中元素大小。于是我们只需要统计 $a$ 数组中可以被匹配的（即在 $b$ 中存在一个未访问元素大于等于该元素）元素数 $l$，然后再用 $n-l+1$ 计算答案。

------------
### 参考代码
就知道大家喜欢看这个。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,b[3010],a[3010],l=0,r=0;//其实有0<=n,m<=3000，数据好水捏。
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]);
	while(l<=n&&r<=m) {
		if(a[l]<=b[r]) l++;
		r++;
	}
	printf("%d",n-l+1); //加1是因为上面多加了,实际上是n-(l-1)捏 。
}
```


---

## 作者：借我昔日热忱 (赞：2)

# 这个题目的翻译错了！！！

~~因为翻译错误所以我被卡了十几遍的提交，为了不再让人们因为翻译被卡，我这里给出了正确的翻译和便于理解的样例~~

**正确翻译：输入n和m(1<=n,m<=3000)，a数组和b数组（a数组长度为n，b数组长度为m，每个数最大为10^6）,目标是让b数组中数与a数组中的数一一对应（相等），为了达到这一目标，你可以让b数组中的数减小，或者增添新的数（大小随意）,求问最少需要增添多少个数。**

------------


如果还不能理解，那就看看这组样例（题目给的样例也够坑的）：

样例1：

输入：

5 5

3 3 3 3 3

1 1 1 1 1

输出：

5

样例解释：a数组中有5个3，b数组中有5个1，无法通过减小b中的某一个数让他等于3，所以要增添5个>=3的数到b中。

------------


样例2：

输入：

5 5

1 1 1 1 1

3 3 3 3 3



输出：

0

样例解释：a数组中有5个1，b数组中有5个3，减小b中的每一个3让他等于1，所以要增添0个数到b中。


------------

题目大意了解清楚之后我们再来做题：这道题目我是先读入了a数组，再读入了b数组，然后将两个数组从小到大比对。

如果a数组的当前数字的数量比b数组当前数字的数量多，就让结果加上这个差。

```cpp
if(w[1][i]-w[2][i]>0) 
	ans+=w[1][i]-w[2][i];
```


如果当前数字b的数量比a多，而且前面有某一个数字，b的数量比a少，那么就让结果减去b对a的差（特别的，如果当前b比a多的数量多于之前a比b多的数量，直接让结果归0）
```cpp
else if(ans>0) {
			if(ans+w[1][i]-w[2][i]<0) ans=0; 
			else ans+=w[1][i]-w[2][i];
		}
```
最后直接输出结果即可

完整代码

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
long long w[3][10004000];
int main(){
	int n,m;
	long long maxn=-1,t,ans=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&t);
		w[1][t]++;
		maxn=max(maxn,t);
	}
	for(int i=1;i<=m;i++){
		scanf("%lld",&t);
		w[2][t]++;
		maxn=max(maxn,t);
	}
	for(int i=0;i<=maxn;i++){
		if(w[1][i]-w[2][i]>0) ans+=w[1][i]-w[2][i];
		else if(ans>0) {
			if(ans+w[1][i]-w[2][i]<0) ans=0; 
			else ans+=w[1][i]-w[2][i];
		}
	}
	
 	printf("%lld",ans);
	return 0;
} 
```




---

## 作者：溪水瑶 (赞：2)

## 暴力还真的出奇迹了
这题窝将读入的两个数组都先排个序，然后再枚举一遍就过了；

目前题解最短的代码QwQ。
## 这里是代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000004
int n,m,a[N],b[N],l,r;
int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<m;i++)
		cin>>b[i];
	sort(a,a+n),sort(b,b+m);
	while(l<n&&r<m){
		if(a[l]<=b[r])l++;
		r++;
	}
	cout<<n-l<<endl;
	return 0;
}
```

---

## 作者：luguangxing (赞：0)

这一题看时间复杂度，暴力是可以过的，思路是这样的：

我们有两个数组 $a$ $b$ 题目有两种改变的方法，一种就类似于删除元素，把后面的数往前移这个方法是不加次数的，第2种是增加数字是要加次数的，根据题目要求最少次数，那我们应该能用第一种就用第一种，于是我们先要看 $a$ 和 $b$ 有几个元素相同，（不过 $b$ 元素因在 $a$ 后面）。

## 好来直接开始暴力出奇迹。

代码展示：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[3005],b[3005],ans,sum;//ans是用来做数组位置的代数，sum相同
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<m;i++)
		cin>>b[i];
	while(ans<n&&sum<m)
	{
		if(a[ans]<=b[sum])//在他的后边或者刚好等于他
		ans++;//计算方法一可以用的次数
		sum++;//把他往后遍历
	}
	cout<<n-ans<<endl;//用总共用方法二更改的次数去减用方法一的次数
	return 0;
} 
```

---

## 作者：foryou_ (赞：0)

考虑采用双指针法解决此题。

首先需要对 $a,b$ 数组**排序**，并且维护两个指针 $l,r$，分别指向 $a,b$ 两个数组中的元素。

接着循环移动 $r$ 指针，每次都尝试匹配 $a_l$ 和 $b_r$：

- 若 $a_l \le b_r$，则说明 $a_l = b_r$ 或可以采用减少 $b_r$ 的方式使 $a_l = b_r$，这时我们就称 $a_l$ 和 $b_r$ 匹配成功。接着令**不需要**添加的元素个数 $ans \gets ans+1$，同时也令 $l \gets l+1$（右移一位）。

- 否则，则说明需要添加一个元素，不进行任何操作。

当 $l,r$ 指针移动到末尾时循环结束，此时的答案即为 $n-ans$。

代码非常好写，因此不贴了。

---

## 作者：zsh_haha (赞：0)

这道题看起来很烦，但是细看还是很好懂的。

### 题目简化

给定一个长度为 $n$ 数组 $a$，和一个长度为 $m$ 的数组 $b$。

将数组 $b$ 整的任意一个数减小或在数组 $b$ 中添加一个任意的数，使得数组 $a$ 中的所有数，在数组 $b$ 中对应。

### 解题思路

首先，把数组 $a$ 和数组 $b$ 中共有的数抵消掉。

然后，找到比数组 $a$ 中**剩下**的数更大的数组 $b$ 中的数，抵消掉（即为把数组 $b$ 的这个数变小到数组 $a$ 中剩下的这个数）。

最后寻找数组 $a$ 中还**未被抵消**的数的总和，输出（数组 $a$ 还未被抵消的数即为既不和 $b$ 数组中的数相等，又不能通过 $b$ 数组中的数缩小然后抵消的数）。

### AC代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000006],b[1000006];
int aa[3001],bb[3001];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		aa[i]=x;
		a[x]++;
	}
	for(int i=1;i<=m;i++){
		int x;
		cin>>x;
		bb[i]=x;
		b[x]++;
	}
	for(int i=1;i<=n;i++){
		int num=aa[i];
		if(b[num]>a[num]){
			b[num]-=a[num];
			a[num]=0;
		}else{
			a[num]-=b[num];
			b[num]=0;
		}
	}
	for(int i=1;i<=n;i++){
		int num=aa[i];
		for(int j=1;j<=m&&a[num]>0;j++){
			if(bb[j]>num){
				int numb=bb[j];
				if(b[numb]>=a[num]){
					b[numb]-=a[num];
					a[num]=0;
				}else{
					a[num]-=b[numb];
					b[numb]=0;
				}
			}
		}
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		sum+=a[aa[i]];
		a[aa[i]]=0;
	}
	cout<<sum;
	return 0;
}
```

### Accepted
![](https://cdn.luogu.com.cn/upload/image_hosting/m085annd.png)

---

## 作者：Ruan_ji (赞：0)

看见这题，我们先强调一下题目的意思，很多人都是栽在下面这个坑里。

“现在你可以通过**减小** $b$ 数组中的数字或向 $b$ 数组中增加一个新的数字” 注意到里面标黑的词：“减小”。**是减小不是减少啊**，大家一定要注意！

然后，用暴力枚举其实就可以解这道题，并不是很难，但是重点是要注意怎么遍历。具体流程见下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/qtu0o4h5.png)
我们维护两个值 $va$ 和 $vb$ ，分别表示 $a$ 数组和 $b$ 数组目前遍历到哪里了。那么注意，最终输出的答案就是 $n$ 减去 $va$ 。

那么，开始模拟吧，加油~

## AC code
```cpp
#include <iostream>
#include <cstdio>
#define MAXN 1000005
using namespace std;
int n, m, answer;
int a[MAXN], b[MAXN];

int main () {
    cin >> n >> m;
    for (int i = 0;i < n; ++i) cin >> a[i];
    for (int i = 0;i < m; ++i) cin >> b[i];

    int value_a = 0, value_b = 0;
    while (value_a < n && value_b < m) {
        if (a[value_a] <= b[value_b]) value_a ++;
        value_b ++;
    }
    
    answer = n - value_a;
    cout << answer << endl;
    return 0;
}
```


---

## 作者：xsI666 (赞：0)

以下选自官方题解：

	考虑困难的需求数量，我们将覆盖这些困难，
    然后我们将提出新的问题，并准备新的问题来覆盖其他需求。
    很明显，如果我们决定满足从n中抽取i的要求，那么最好采用那些复杂性最小的要求。
    让我们把最难的问题简化成最简单的要求。
    如果一切顺利，我们用n-i更新答案。
	时间复杂度为O(n^2)，空间复杂度为O(n)。
    有一个复杂度为O(n+m)的解，希望读者认真探究。
    
代码：
```cpp
#include <bits/stdc++.h>//万能头文件

using namespace std;//使用标准名字空间

inline int read()//快速读入
{
	int f=1,x=0;
	char c=getchar();

	while(c<'0' || c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}

	while(c>='0' && c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}

	return f*x;
}

int a[3005],b[3005],n,m,ans;//定义变量

int main()
{
	n=read(),m=read();

	for(register int i=0; i<n; i++)a[i]=read();

	for(register int i=0; i<m; i++)b[i]=read();

	ans=n;//初始化答案

	if(ans>m)//如果答案比已有复杂度的个数还多
	{
		ans=m;//就把答案设为已有复杂度个数
	}
	
	for(int i=ans; i>=0; i--)//开始枚举
	{
		int flag=1;//设置标记
		
		for(int j=0; j<i; j++)//枚举位置在i前面的复杂度
		{
			if(a[j]>b[m-i+j])//如果不满足条件
			{
				flag=0;//就标记为不行
			}
		}

		if(flag)//如果当前是一个可行方案
		{
			printf("%d\n",n-i);//那么直接输出

			return 0;//结束
		}
	}
}
```


---

## 作者：_Gabriel_ (赞：0)

### 思路

双指针模拟题。

定义了两个指针 $l$ 和 $r$，分别表示数组的左右边界。

在输入的 $m$ 个数中，从左到右依次与数组 $a$ 中的元素进行比较，如果 $m$ 中的数大于等于数组 $a$ 中的数，则计数器 $ans$ 加一，且 $l$ 向右移动一位。$r$ 每次循环都向右移动一位。最后输出 $n$ 减去 $ans$ 的值，即为最少要添加的数字次数。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3e3 + 10;
int a[N];
int n, m, t, ans = 0;

int main() {
	cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
	}
	int l = 1, r = 1;
    while (r <= m) {
        cin >> t;
        if (l <= n && t >= a[l]) {
            ans++;
            l++;
        }
        r++;
    }
    cout << n - ans;
    return 0;
}
```


---


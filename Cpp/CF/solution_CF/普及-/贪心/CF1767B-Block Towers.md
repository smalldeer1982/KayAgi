# Block Towers

## 题目描述

There are $ n $ block towers, numbered from $ 1 $ to $ n $ . The $ i $ -th tower consists of $ a_i $ blocks.

In one move, you can move one block from tower $ i $ to tower $ j $ , but only if $ a_i > a_j $ . That move increases $ a_j $ by $ 1 $ and decreases $ a_i $ by $ 1 $ . You can perform as many moves as you would like (possibly, zero).

What's the largest amount of blocks you can have on the tower $ 1 $ after the moves?

## 说明/提示

In the first testcase, you can move a block from tower $ 2 $ to tower $ 1 $ , making the block counts $ [2, 1, 3] $ . Then move a block from tower $ 3 $ to tower $ 1 $ , making the block counts $ [3, 1, 2] $ . Tower $ 1 $ has $ 3 $ blocks in it, and you can't obtain a larger amount.

In the second testcase, you can move a block from any of towers $ 2 $ or $ 3 $ to tower $ 1 $ , so that it has $ 2 $ blocks in it.

In the third testcase, you can $ 500000000 $ times move a block from tower $ 2 $ to tower $ 1 $ . After that the block countes will be $ [500000001, 500000000] $ .

## 样例 #1

### 输入

```
4
3
1 2 3
3
1 2 2
2
1 1000000000
10
3 8 6 7 4 1 2 4 10 1```

### 输出

```
3
2
500000001
9```

# 题解

## 作者：hyfzelda (赞：3)


## 思路
1.依题，我们发现，使得 $a_1$ 最大，仅需使 $a_1$ 与更大的数进行操作，因为不管如何操作，数列总和不变，故不需要非 $a_1$ 的二数进行操作。
 
 2.经过操作，使 $a_1 =  (a_1+a_j+1)\div2$ 时，二数最平均，故此时最大，同时，为了使 $a_1$ 与尽可能多的数操作，应从小到大进行操作，故需先排序
 
##  代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000005],n,t,x;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&x);
		for(int i=1;i<n;i++)
		{
			scanf("%d",&a[i]);
		}
		sort(a+1,a+n);
		for(int i=1;i<n;i++)
		{
			if(x<a[i]) x=(x+a[i]+1)/2;//与更大数进行操作
		}
		printf("%d\n",x);
	}
	
}
```


---

## 作者：ImNot6Dora (赞：2)

由于集合的总和不变，其实就是将 $a_{1}$ 与其他元素操作，而由于只能操作比 $a_{1}$ 大的元素，所以必须将其他元素进行排序，这样可以获得更大的结果。

每次操作会让两个数互相靠近，所以操作结束后 $a_{1}$ 的值应变成了 $\operatorname{ceil}(\frac{a_{1}+a_{i}}{2.0})$。

注意由于输入样例有多组，所以每次需要将 $a$ 数组初始化。

# C++ CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001];
int main(){
	int t;
	cin>>t;
	while(t--){
		memset(a,0,sizeof(a));
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1+1,a+n+1);
		for(int i=2;i<=n;i++){
			if(a[1]<a[i])a[1]=ceil((a[1]+a[i])/2.0);
		}
		cout<<a[1]<<endl;
	}
	return 0;
}
```

完结撒花！

By ImNot6Dora

---

## 作者：happy_zero (赞：2)

我们先不考虑所有的数，我们先单独考虑对两个数进行操作：设两个数 $A$，$B$（$A < B$），对它们不停进行操作后我们可以发现 $A$ 会变成 $\left\lceil\dfrac{A+B}{2}\right\rceil$。而题目中要求我们要使 $a_1$ 变得最大，那我们就可以把 $a_1$ 和 $a$ 数组中所有大于 $a_1$ 的数字进行一遍操作。

#### 这里有一个问题。
$a_1$ 在操作过程中是会不断变大的，这时候有些原本大于它的数就会小于 $a_1$，所以我们就要考虑枚举的顺序是怎样才能使 $a_1$ 最后的值最大。

#### 思考一番后发现就是贪心。
我们对 $a$ 数组除 $a_1$ 外的元素进行从小到大排序，使得每次在可以操作的数字中取最小的那个，这样就可以保证最后得到的值最大。

最后放上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int a[200005];
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        sort(a+2,a+1+n);
        for(int i=2;i<=n;i++){
            if(a[i]>a[1])
            	a[1]=ceil((a[1]+a[i])/2.0);
        }	
        cout<<a[1]<<endl;
    }
    
    return 0;
}
```



---

## 作者：InversionShadow (赞：1)

### 题意：

$T$ 组操作，每组有一个序列 $\{a_n\}$，你可以在每次操作中，你可以选定两个位置 $i,j$，且必须满足 $a_i>a_j$，我们就将 $a_i$ 减一，$a_j$ 加一，问在任意多次操作后，$a_1$ 的最大值为多少？

### 思路：

易知不管多少操作，$a_i+a_j$ 的和不变，即他们的平均数为 $\left\lceil\dfrac{a_i+a_j}{2}\right\rceil$
。

依题意知 $a_1$ 的位置不变，$a_2$ 到 $a_n$ 从小到大排序，如果 $a_j>a_1$，则 $a_1=\left\lceil\dfrac{a_i+a_j}{2}\right\rceil$，输出 $a_1$ 即可。

### Code:

```cpp
#include <bits/stdc++.h>

using namespace std;

int t, n, a[1200001];

int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    sort(a + 2, a + n + 1);
    for (int i = 2; i <= n; i++) {
      if (a[i] > a[1]) {
        if ((a[i] + a[1]) % 2 == 0) {
          a[1] = (a[i] + a[1]) / 2;
        } else {
          a[1] = (a[i] + a[1]) / 2 + 1;
        }  // 上面这个 if 语句等价为 ceil(1.0 * (a[i] + a[1]) / 2.0)
      }
    }
    cout << a[1] << endl;
  }
  return 0;
}

```


---

## 作者：0zhouyq (赞：1)

### CF1767B 题解

[传送门](https://www.luogu.com.cn/problem/CF1767B)

### 思路：

我们要让 $a_1$ 变大，就要让他和更大的数操作。假设我们不断让 $a_1$ 和 $a_i$ 操作（$a_1<a_i$），$a_1$ 就会不断接近 $a_i$，显然 $a_1$ 和 $a_i$ 操作后最大变成 $\lfloor \dfrac{a_1+a_i+1}{2} \rfloor$。

考虑操作顺序。因为每一次操作前 $a_1$ 原来的值都为操作后的值贡献 $\lfloor \dfrac{a_1}{2} \rfloor$，所以每一次操作的对象对最终答案的影响都是下一次的一般。因此越大的数一定要越晚和 $a_1$ 操作。

模拟一下就可以了。

### AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
priority_queue<ll,vector<ll>,greater<ll> > q;
int main(){
	ll t;
	scanf("%lld",&t);
	while(t--){
		ll n;
		scanf("%lld",&n);
		ll a;
		scanf("%lld",&a);
		for(ll i=1;i<n;i++){
			ll x;
			scanf("%lld",&x);
			q.push(x);
		}
		while(!q.empty()){
			if(a<q.top()){
				a=(a+q.top()+1)/2;
			}
			q.pop();
		}
		printf("%lld\n",a);
	}
	return 0; 
}
```

---

## 作者：joyslog (赞：1)

## Block Towers

[CF1767B](https://codeforces.com/problemset/problem/1767/B)

给定一个 $n$ 个数的数列 $a_1,a_2,\dots ,a_n$。

在每次操作中，你可以选定两个位置 $i,j$ 且满足 $a_i>a_j$，把 $a_i$ 减去 $1$，同时把 $a_j$ 加上 $1$。

询问在任意多次操作后，$a_1$ 的最大值是多少？

### 题解

显然对某两个数进行足够多次操作后，它们会变为它们的平均数。

那么如果要对 $a_1$ 有增加的贡献，其实就是选定一个 $a_i>a_1$，然后 $a_1\gets \lfloor \frac{a_1+a_i+1}{2}\rfloor$。

那么我们把大于 $a_1$ 的所有数从小到大排序，贪心地进行操作。因为每次操作后 $a_1$ 仍然小于后面的所有数，所以每次操作都会使 $a_1$ 增加。
 
代码实现可以排序也可以优先队列。时间复杂度 $O(T n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
priority_queue<int, vector<int>, greater<int>> pq;
 
inline ll read() {...}
inline void write(ll x) {...}
 
int main() {
    int t = read();
    while(t--) {
        int n = read(), ans = read();      
        for(int i = 2; i <= n; i++) {
            int x = read();
            if(x > ans) pq.push(x);
        }
        while(!pq.empty()) {
            int x = pq.top(); pq.pop();
            ans = (ans + x + 1) >> 1;
        }
        write(ans), putchar('\n');
    }
    return 0;
}
```

---

## 作者：liangbob (赞：0)

### CF1767B 题解

#### 思路分析

一道数学思维题。

首先我们发现，两个数，一个加一，一个减一。那么显然和不变。

现在我们要求 $a_1$ 的最大值。显然，它的最大值是由操作得来的，求最大值要尽量的往上加，也就是要求每次操作 $a_1$ 都是较小的那个，这样子它才能加。而且注意要从小到大，保证单调性，不然取不到最大。这个很容易实现，把除 $a_1$ 的数排序后遍历比 $a_1$ 大的数就可以了。

然后我们就要思考：$a_1$ 每次到底最多能变为什么呢？注意：每次操作都要满足 $a_1$ 是较小的那个，而且和不变。设当前要与 $a_1$ 操作的数为 $a_x$ 那么 $a_1$ 就最多变为 $\dfrac{a_1+a_x}{2}$，注意向上取整（不用担心较小条件的问题，因为操作本来就是要变为较大的）。

按照那个公式排序并计算即可。注意：多测不清空，爆零两行泪。

#### 关键代码

```cpp
void solve(int x) // x 为 a1
{
	// 备注：a 已经按从小到大把 a2 到 an 排序
	int t = x;
	for(int i = 2;i <= n;i++)
	{
		if(a[i] > x)
		{
			t = ceil((a[i] + t) / 2.0); // 按照公式计算
		}
	}
	cout << t << endl;
	
} 
```





---

## 作者：Crazyouth (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1767B)

**分析**

由于要让 $a[1]$ 尽可能大，所以在挑选 $a[i]$ 与 $a[j]$ 时，将 $a[1]$ 作为 $a[j]$ 使其增加。因为不管如何操作，整个数组的和是不会变化的，所以我们并不需要对 $a[1]$ 以外的数进行任何操作。

接下来，为保证 $a[1]$ 在进行操作时不会操作到过大使得一些比上一个与其操作的数更小的数不能有效利用，我们需要将除了 $a[1]$ 以外的数从小到大排序。这里可以直接用 sort 函数进行排序。

排序后就可以开始开始进行操作了。在操作时为了使 $a[1]$ 尽可能大，要让被操作数与 $a[1]$ 尽量平均，可总结出 $a[1]=(a[j]+a[1]+1)/2$ 时，$a[1]$ 最大。

最后输出 $a[1]$ 既可。

**AC代码**

```
#include <iostream>
#include <algorithm>
using namespace std;
int a[int(2e5+10)];
int main()
{
	int t,n;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>n;
		for(int j=1;j<=n;j++) cin>>a[j];
		sort(a+2,a+n+1); //对a[2]到a[n]从小到大进行排序。 
		for(int j=2;j<=n;j++)
		{
			if(a[j]>a[1]) a[1]=(a[j]+a[1]+1)/2; //使a[1]最大的贪心策略 
		}
		cout<<a[1]<<endl; //输出答案 
	}
	return 0;
}
```


---

## 作者：liuzr156 (赞：0)


你可能刚看到题目会觉得怪怪的，~~我也是~~，那么我们采用一个~~很笨的~~办法：举例探究。顺着题目意思我们可以发现：对于 $a_i$ $(i\ne1)$ 且 $(a_i>a_1)$ ，$a_i$ 给 $a_1$ 的数和 $a_i-a_1$ 有很大关系 ， 所以我们分两种情况：$(a_i-a_1)$ 是奇数和 $(a_i-a_1)$ 是偶数。

当$(a_i-a_1)$ 是奇数时，可以举出这个简单的例子：$n=2$ , $a_1 = 1$ , $a_2 = 4$ 。

第一次给：$a_1 = 2$ , $a_2 = 3$ ;第二次给： $a_1=3$ , $a_2=2$。此时$a_1>a_2$ ，不能再给了。所以很容易发现，当差为奇数时，给的数量就是$\dfrac{a_i-a_1}{2}+1$。

如果$(a_i-a_1)$ 是个偶数，可以举出这个简单的例子
：$n=2$ , $a_1 = 1$ , $a_2 = 5$

第一次给：$a_1 = 2$ , $a_2 = 4$ ;第二次给： $a_1=3$ , $a_2=3$。此时$a_1=a_2$，也不能再给了。所以当差为偶数时，给的数量就是$\dfrac{a_i-a_1}{2}$。

那么直接按照输入顺序进行给数可以吗？很明显不行。就比如

```
3
1 3 2
```
这个例子，如果直接按照输入顺序结果就是 $2$ , 但是正确答案是 $3$ ，那应该怎么做？其实很明显，就是要从小到大进行排序，因为只有从小到大进行排序后才能保证 $a_1$ 能尽量多次地从 $a_i$ 上获取数字。


结合上面的结论可以总结出思路：首先取出 $a_1$ ,然后将 $a_2$ ~ $a_n$ 的部分由小到大进行排序，接下来遍历 $a_2$~$a_n$ 的部分，对于每个大于 $a_1$ 的数，直接将
$a_1$ $\gets$ $a_1+\left\lceil\dfrac{a_i-a_1}{2}\right\rceil$ ，时间复杂度 $O(Tn \log n)$ 。
 
code:
 
 ```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[N],n,T;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline int kun(int x){//如果不会向上取整的函数可以直接分类讨论
	if(x%2!=0) return x/2+1;
	return x/2;
}
int main(){
	T=read();
	while(T--){
		n=read();
		long long k=read();
		for(int i=1;i<n;i++) a[i]=read();//快读
		sort(a+1,a+n);
		for(int i=1;i<n;i++){
			if(a[i]>k){
				k+=ceil((a[i]-k)/2.0);//向上取整函数，注意要除以2.0
			}
		}
		cout << k << endl;
	}
	return 0;
}
```


---

## 作者：Colorful_Unicorn (赞：0)

# 思路
通过这题我们可以知道，最后 $a_1$ 不能变时，它与另外一个数的差一定小于等于一。我们设 $a_1$ 与 $a_j$ 的差为 $cha$，那么 $a_1$ 每次就应该加上 $\frac{(cha+1)}{2}$，$a_j$ 就应减去 $\frac{(cha+1)}{2}$。因为要让 $a_1$ 最大，故让它先与小的数做操作，注意排序时不要包括 $a_1$。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005];
int main()
{
	cin >> t;
	for (int i=1;i<=t;i++)
	{
		cin >> n;
		for (int j=1;j<=n;j++)
			cin >> a[j];
		sort(a+2,a+n+1);
		for (int j=2;j<=n;j++)
		{
			int cha=(a[j]-a[1]);
			if (cha<0)  //a[1]<a[j],不符合条件直接跳过
				continue;
			a[1]+=(cha+1)/2;
			a[i]-=(cha+1)/2;
		}
		cout << a[1] << "\n";
	}
	return 0;
}
```

---

## 作者：_FJX_ (赞：0)

分析:

对于任意一组 $a_i$ 和 $a_j$ ，进行足够多次操作后他们就会变为它们的平均数。

那么要求 $a_1$ 的最大值，其实就是选定一个大于 $a_1$ 的 $a_i$ , 将 $a_1$ 变成 $\left\lfloor\dfrac{a_1 + a_i + 1}{2}\right\rfloor$ 。

实现过程:

运用贪心算法，将所有大于 $a_1$ 的 $a_i$ 从小到大排序，依次进行操作，这样可以确保每次操作后都能使 $a_1$ 变大。

实现：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[1000005];
void work()
{
	int n, a1, t = 0;
	scanf("%d%d", &n, &a1);
	for (int i = 2; i <= n; i ++)
	{
		int x;
		scanf("%d", &x);
		if (x > a1)
		{
			a[++ t] = x;
		}
	}
	sort(a + 1, a + t + 1);
	for (int i = 1; i <= t; i ++)
	{
		a1 = (a1 + a[i] + 1) / 2;
	}
	printf("%d\n", a1);
}
int main(){
	int T;
	scanf("%d", &T);
	while (T --)
	{
		work();
	} 
	return 0;
}

```


---

## 作者：LiaoYF (赞：0)

## 分析
显然，每一个大于 $a_1$ 的数进行任意多次操作后，都可以将 $a_1$ 增加它与 $a_1$ 的差的一半（向上取整）。所以先将数组排序，然后二分查找第一个可以操作的 $a_i$，因为数组从小到大排好了序，所以在第一个数后面的所有数都可以操作。
## code
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,a[200005];
int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        sort(a+2,a+n+1);
        int x=upper_bound(a+2,a+n+1,a[1])-a;//二分查找第一个大于a[1]的数
        for(int i=x;i<=n;i++){
            a[1]+=ceil((a[i]-a[1])/2.0);
        }
        cout<<a[1]<<"\n";
    }
    return 0;
}
```


---

## 作者：zfx_VeXl6 (赞：0)

如果 $a_1$ 是最大的，就没必要进行操作了。

如果 $a_1$ 不是最大的，就让 $a_1$ 与某个比 $a_1$ 大的元素进行操作，直到 $a_1$ 比这个元素大。假设这个元素是 $a_i$，那么进行若干次操作后 $a_1$ 将会变为 $\lceil\frac{a_1+a_i}{2}\rceil$。

但是比 $a_1$ 大的元素可能有多个，所以用贪心的思路来选择先后顺序。

看样例 $1$：$a_1=1,a_2=2,a_3=3$，如果先把 $a_1$ 和 $a_3$ 进行操作再把 $a_1$ 和 $a_2$ 进行操作，得到最终的 $a_1$ 是 $2$。但如果先把 $a_1$ 和 $a_2$ 进行操作再把 $a_1$ 和 $a_3$ 进行操作，得到最终的 $a_1$ 是 $3$。这说明每次操作都应选择比 $a_1$ 大的元素中最小的那个。

于是考虑将 $a_2$ 到 $a_n$ 从小到大排序，依次遍历每个 $2$ 到 $n$ 中的 $i$，如果 $a_i>a_1$，那么将 $a_1$ 修改为 $\lceil\frac{a_1+a_i}{2}\rceil$。

代码如下：

```cpp
cin >> t;
while (t--)
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 2, a + n + 1);
    for (int i = 2; i <= n; i++)
        if (a[i] > a[1])
            a[1] = int(ceil((a[1] + a[i]) / 2.0));
    cout << a[1] << '\n';
}
```

---

## 作者：lwx20211103 (赞：0)

## 思路

这是一道比较简单的贪心题。

由题意可知，每次让我们选两个数，第一个比第二个大，第一个减一，第二个加一。通过这个操作，让数列的第一个数最大。

为了让他最大，我们可以得出就是选数列第一个数和后面比他大的数，观察得到：经过选数之后，**被加一的数字会变成两个数的平均数（向上取整）**。

于是贪法就有了：先把数组从第二个数开始排序，在**第一个数字小于后面数字的情况下**，把第一个数和后面的每个数字比较，找到后面数字比第一个数字更大的数，然后再和后面的数字取平均数，变成新的第一个数，就可以了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int nums[n + 1];
        int a1;
        cin >> a1;
        for (int i = 1; i < n; i++)
        {
            cin >> nums[i];
        }
        sort(nums + 1, nums + n);
        for (int i = 1; i < n; i++)
        {
            if (a1 < nums[i])
            {
                if ((nums[i] + a1) & 1) //如果两个加起来是奇数
                {
                    a1 = ((a1 + nums[i]) >> 1) + 1;
                }
                else a1 = (a1 + nums[i]) >> 1;
            }
            
        }
        cout << a1 << "\n";
    }
    
    return 0;
}

```
## 写在最后

感谢各位的观看，如有改进意见或 hack 数据，可以提出来。

---

## 作者：lfxxx (赞：0)

考虑贪心。

首先可以先排一遍序。

但是因为要求 $a_1$ 最大化，所以我们只对 $a_2 - a_n$ 排序。

然后呢？

扫一遍，对于每个元素考虑一遍操作（操作的本质是取上取整平均数）。

那为什么是对的呢？

假设对于数 $A,B$ 有 $A \leq B$ 。

那么数 $C$ 对他们进行一遍正倒序操作贡献分别为

$ \frac{\frac{C + B}{2} + A}{2} = \frac{C + B}{4} + \frac{A}{2}$

由于 $A \leq B$ ，所以以上式子肯定比 $\frac{C + A}{4} + \frac{B}{2}$ 小。

更何况先对大数操作可能会出现负操作的情况。

所以就证明了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000001]; 
void work(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+2,a+n+1);
	for(int i=2;i<=n;i++){
		if(a[1]<a[i]){
			a[1]=ceil((a[1]+a[i])*1.0/2.0); 
		}
	}
	cout<<a[1]<<'\n';
} 
int t;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--) work();
}
```


---

## 作者：zhang_kevin (赞：0)

# Solution

观察题目，可以发现两个数进行足够次数的操作后，会变成两数的平均数。

如果想要 $a_1$ 变多，可以选择一个**比它大的数** $a_i$，将 $a_1$ 赋值为 $\left\lfloor\dfrac{a_1+a_i+1}{2}\right\rfloor$。

我们可以开一个 `priority_queue`，把大于 $a_1$ 的数存进去，然后计算即可。

单次询问时间复杂度 $\mathcal{O}(n \log n)$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin >> T;
	while(T--){
		priority_queue<int, vector<int>, greater<int>> q;
		int n, a1;
		cin >> n >> a1;
		for(int i = 2; i <= n; i++){
			int val;
			cin >> val;
			if(val > a1) q.push(val);
		}
		while(!q.empty()){
			a1 = (a1+q.top()+1) >> 1;//a >> 1 = a / 2
			q.pop();
		}
		cout << a1 << endl;
	}
	return 0;
}
```

---


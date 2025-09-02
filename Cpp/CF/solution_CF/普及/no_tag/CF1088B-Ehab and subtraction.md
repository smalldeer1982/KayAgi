# Ehab and subtraction

## 题目描述

You're given an array $ a $ . You should repeat the following operation $ k $ times: find the minimum non-zero element in the array, print it, and then subtract it from all the non-zero elements of the array. If all the elements are 0s, just print 0.

## 说明/提示

In the first sample:

In the first step: the array is $ [1,2,3] $ , so the minimum non-zero element is 1.

In the second step: the array is $ [0,1,2] $ , so the minimum non-zero element is 1.

In the third step: the array is $ [0,0,1] $ , so the minimum non-zero element is 1.

In the fourth and fifth step: the array is $ [0,0,0] $ , so we printed 0.

In the second sample:

In the first step: the array is $ [10,3,5,3] $ , so the minimum non-zero element is 3.

In the second step: the array is $ [7,0,2,0] $ , so the minimum non-zero element is 2.

## 样例 #1

### 输入

```
3 5
1 2 3
```

### 输出

```
1
1
1
0
0
```

## 样例 #2

### 输入

```
4 2
10 3 5 3
```

### 输出

```
3
2
```

# 题解

## 作者：little_sun (赞：4)

## 题解 CF1088B 【Ehab and subtraction】

这种题一上来先排序啊

然后就开始操作了

对于每一次操作，找到第一个$\geq$当前已经减去的数的数$a_i$，把它减去当前已经减去数的值$now$,然后把now更新为$a[i]$,最后再二分（所以知道为什么要排序了吧）找下一个大于$now$的数，如果这个位置越界了之后就都输出$0$

如果还不理解就看代码

```cpp
# include <bits/stdc++.h>

# define ll long long

ll a[100010];

int main()
{
    ll n, k;
    ll now = 0, pos = 1;
    scanf("%I64d%I64d", &n, &k);
    for(int i = 1; i <= n; i++)
        scanf("%I64d", &a[i]);
    std::sort(a + 1, a + n + 1);
    a[n + 1] = 0x7f7f7f7f7f7f7f;
    for(int i = 1; i <= k; i++)
    {
        if(pos == n + 1)
        {
            printf("0\n");
            continue;
        }
        printf("%I64d\n", a[pos] - now);
        now += a[pos] - now;
        ll l = pos + 1, r = n + 1;
        while(l < r)
        {
            ll mid = (l + r) >> 1;
            if(a[mid] > now)
                r = mid;
            else l = mid + 1;
        }
        pos = l;
    }
    return 0;
}
```

---

## 作者：floatery (赞：3)

竟然没有用unique的？

unique就是去重函数，当然必须是排好序的数组才能用这个，把重复的元素踢到最后面。

本题需要标出踢到最后面的第一个元素的下标。

本题思路前面的题解已经够详细了，在此不再多说。也就是排好序之后输出相邻的两个元素之差而已。

[这里是我从网上找到的unique函数使用教程](https://www.cnblogs.com/wangkundentisy/p/9033782.html)


```cpp
#include <stdio.h>
#include <algorithm>
using namespace std;
int a[100001];
int main()
{
	int n,k,mark;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	sort(a+1,a+n+1);
	unique(a+1,a+n+1);
	mark=n+1;
	for(int i=1;i<=n;i++)
	{
		if(a[i]<=a[i-1])
		{
			mark=i;
			break;
		}
	}
	for(int i=1;i<=k;i++)
	{
		if(i>=mark)
		{
			printf("0\n");
		}
		else
		{
			printf("%d\n",a[i]-a[i-1]);
		}
	}
	return 0;
}
```

---

## 作者：初雪_matt (赞：2)

update: 2021.7.17 修改了一处错别字。

这道题其实用 python 很容易,接下来我来给大家分析一下。

题目是说让你在给定的序列中不停找最小值 $x$ ,让所有不为零的数（包括本身）都减去一个 $x$ ，直到 $m$ 此操作过后为止。

首先，如果你直接枚举，就会是双重循环， $n$ 、$m$ 是 $10^5$ 以内，也就是说，直接枚举肯定会爆（~~特别是python~~）,那么肯定就要把它降成一重循环，
首先想到的是**差分数组**，但每次求完差分还要求一次前缀和，还要一个循环， $m$ 次操作也要一次循环，还是双重循环，那该怎么办呢？我们可以先把这个序列排序，排序默认升序，那第一个数就是 $x$ ,再把他丢进 python 的迭代器中，循环 $m$ 次后用迭代器自带后退函数进行后移，然后就可以输出原来减去   $x$  的差了。详细代码请看下面：


```python
n,k=map(int,input().split(" "))#输入不用说
a=iter(sorted(set(map(int,input().split(" ")))))
'''
上面这里是关键，先把数据排序,再使用迭代器 iter ,这是为了后面的方便。
'''
r=0#注意初始值
while k > 0:#循环 k 次
    x=next(a,r)#迭代器 next ,可取出迭代器中的下一个函数
    print(x-r)#输出减去后的 x
    r=x
    k-=1#注意要减一
```


题解结束，撒花~

---

## 作者：zzhbpyy (赞：1)

### [Problem - 1088B - Codeforces](https://codeforces.com/problemset/problem/1088/B)

其实根本不需要用优先队列。容易发现，一次操作等价于将序列中非零数中所有最小的数变成 $0$。我们也可以理解为每次去掉数列中所有的最小数，所以数列中重复的数是对答案没有影响的。可以直接用 `sort` 和 `unique` 函数，答案显然就是处理后的序列每两个数之差。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005];
signed main(){
	ios::sync_with_stdio(0);cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	int tot=unique(a+1,a+n+1)-a-1;
	for(int i=1;i<=min(tot,m);i++){
		cout<<a[i]-a[i-1]<<'\n';
	}
	for(int i=min(tot,m)+1;i<=m;i++)cout<<0<<'\n';
}
```

---

## 作者：filletoto (赞：1)

## 思路
题目要让我们在给定的序列中找最小值 $x$，我们可以用优先队列来维护。

每次在序列不空的情况下找最小值并且进行去重，用变量 $last$ 记录上一个循环中最小的值，初始 $last$ 赋值为 $0$，如果序列空了，剩下的用 $0$ 补全。

## 代码
```cpp
#include <iostream>
#include <queue>
using namespace std;
int n,m;
priority_queue<int,vector<int>,greater<int>> q;//优先队列
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		q.push(x);
	}
	int i,last=0;
	for(i=1;i<=m&&!q.empty();i++)
	{
		int minn=q.top();
		q.pop();
		while(!q.empty()&&q.top()==minn)
			q.pop();//去重
		cout << minn-last << endl;
		last=minn;	//存储循环的最小值
	}
	for(;i<=m;i++)
	{
		puts("0");//将0补全
	}


	return 0;
}
```

---

## 作者：meimu75 (赞：0)

题目传送门：[Ehab and subtraction](https://www.luogu.com.cn/problem/CF1088B)

1. 暴力

   很容易想到暴力思路，不停地找最小的正数，输出，然后所有的数字都减去这个最小正数，直到没有正数，就可以输出 0 了。

2. `sort`

   我们把一直以来一共累计减掉的数称为 $sub$。

   从小到大排个序，然后找到第一个减完之后还是正数的数（大于 $sub$，二分），更新 $sub$，然后循环，直到二分发现没有大于 $sub$ 的数，剩下的就剩输出 0 了。

4. 优先队列（小根堆）

   这里同样把一直以来一共累计减掉的数称为 $sub$，另外本文中所有入队，出队等都指优先队列。

   首先把所有的元素都入队。然后记录当前说所有元素都一起减了 0 ，对吧。我们如何得到在减了一些数之后最小的非 0 数呢，很显然，把堆顶那些小于等于一共减了的数的都出队，只留下减了之后不是 0 的。但是，如果中途就队列空了或者出队完之后队列空了，要输出 0 。

   接下来我们更新 $sub$，首先堆顶我们直接出队，记为 $cur$。再由于堆顶原来是被减了 $sub$ 的，所以 `cur -= sub;`，然后 `sub += cur;` 把新的堆顶（也就是当前最小的数）给累加到 $sub$ 里面。

   # Code:
   ```cpp
   #include <bits/stdc++.h>
   using namespace std;
   int a[100005];
   priority_queue<int,vector<int>,greater<int> > pq;
   int main()
   {
       int n,m;
       cin >> n >> m;
       for(int i = 1;i <= n;i++)
       {
           cin >> a[i];
           pq.push(a[i]);
       }
       int sub = 0,cur;
       for(int i = 1;i <= m;i++)
       {
           while(!pq.empty() && pq.top() <= sub)
           {
               pq.pop();
           }
           if(pq.empty())
           {
               cout << "0\n";
               continue;
           }
           cur = pq.top();
           pq.pop();
           cur -= sub;//可能看起
           sub += cur;//来有点抽象
           cout << cur << "\n";
       }
       return 0;
   }
   ``````

---

## 作者：2b2b2bbb (赞：0)

# 思路
这道题每次都要我们求一次序列中的最小值，但是如果我们直接循环找或者排序时间上都来不及。     


我们可以用优先队列来维护小根堆。  


对于每一次的输出我们要有几个判断条件。首先如果这个序列中没有数那么我们就要输出 $0$。     


同时我们要一个 $sum$ 判断之前总共要减少多少。然后只要当前的数减去 $sum$ 刚好为 $0$ 那么就不能输出。       
如果都不满足那么我们就可以直接输出当前的 $x$ 减去 $sum$ 的值了。      

注意: $sum$ 加的是当前的 $x$ 减去 $sum$ 的值并不是加上 $x$。                    
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,sum,cnt;
priority_queue<long long, vector<long long>, greater<long long> > q;
int main(){
	cin >> n >> m;
	for(int i = 1 ; i <= n ; i ++){
		int x;
		cin >> x;
		q.push(x);
	}
	while(m --){
		int ans;
		while(!q.empty () && q.top () - sum == 0){
			q.pop();
		}
		if(q.empty()){
			cout << 0 << endl;
			continue;
		}
		ans = q.top() - sum;
		sum += ans;
		cout << ans << endl;
		q.pop();
	}
	return 0;
} 
```

---

## 作者：_yang_yi_bo_ (赞：0)

我们可以维护一个小根堆，存储当前所有数中不为 $0$ 的数。

由于数组中减的数永远是一样的，我们可以维护当前减了多少数，每次输出当前 $>0$ 的最小数时，只需输出当前小根堆的最小数 $-$ 减的数的数量。

注意：每次要将优先队列中小于 $0$ 的数弹出。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ccf,kkk;
priority_queue<int,vector<int>,greater<int> > x;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		x.push(a);
	}for(int i=1;i<=m;i++){
		while(!x.empty()&&x.top()==kkk){
			x.pop();
		}if(x.empty()){
			cout<<0<<"\n";
			continue;
		}
		ccf=x.top();
		x.pop();
		ccf-=kkk;
		kkk+=ccf;
		cout<<ccf<<"\n";
	}
    return 0;
}
```

---

## 作者：Tachibana27 (赞：0)

题意非常清晰，不妨尝试按题意[模拟](https://www.luogu.com.cn/record/156136130)。

很明显，全部删除的话时间复杂度来到 $O(n^{2})$ 甚至更高，很明显是无法通过的。

将数列中的数全部减去 $x$ 的复杂度是非常高的，可以使用类似**懒标记**的思想。将所需要删的数统计到 lazy 标记里，删除操作不一定要全部拉出来删一遍，取到它时再删也没有问题。

------------


那么每一次的最值都是改动的，是否就需要用**优先队列**维护最值呢？

**优先队列**很明显可以解决这种问题，插入 $n$ 次，弹出 $k$ 此，复杂度为 $O((n+k)\log n)$。

排序数组同样可以解决。排序一遍后用一个指针维护当前可用最小值，询问复杂度为 $O(1)$，总复杂度 $O(n\log n+m)$。

------------

tips：去重后就不用考虑当前值是否为 $0$ 的情况了。

code：

```cpp
//数组
intt n,m;
intt sum;
intt a[100086];
intt point;
intt main(){
    std::cin>>n>>m;
    for(intt i=1;i<=n;i++)
    	std::cin>>a[i];
    std::sort(a+1,a+1+n);//排序
    while(m--){
        if(point==n)//取到头了，全是0
            puts("0");
        else{
        	while(a[++point]==a[point+1]);//去重，如果当前和下一个一样就不考虑当前
            std::cout<<a[point]-sum<<"\n";//减去懒标记
            sum+=a[point]-sum;//更新懒标记
        }
    }
    return 0;//撒花
}
```

```cpp

//优先队列
#include<bits/stdc++.h>
#define int long long
intt n,m;
std::priority_queue<intt>q;
std::map<intt,booll>mp;
intt sum;
intt main(){
    std::cin>>n>>m;
    for(intt i=1;i<=n;i++){
        intt x;
        std::cin>>x;
        if(not mp[x])//这里用map来去重
            q.push(-x);
        mp[x]=true;
    }
    while(m--){
        if(q.empty())
            puts("0");//队列为空，取到头了
        else{
            intt x=-q.top();//取一个最小值
            q.pop();
            std::cout<<x-sum<<"\n";
            x-=sum;
            sum+=x;//同上份代码
        }
    }
    return 0;//撒花
}
```

---

## 作者：Weekoder (赞：0)

### 思路

一开始想的是优先队列维护最小值再暴力修改，结果 $\text{T}$ 了。

怎么优化？其实上面做法的缺点是每次都 $\mathcal{O(n)}$ 地进行修改，速度太慢。由于整个区间都需要统一减去某个数，所以元素的相对大小是不会变的，也就是原来是最小值的那个数还是他。不如直接累加每次需要修改的值 $sum$，再取出某个值 $x$ 的时候，实际上的值就是 $x-sum$。再把等于 $0$ 的值先弹出，输出队头 `pq.top() - sum` 即可。

关于 $sum$ 的累加，我写的是 `sum = pq.top()`。本来应该是 `sum += pq.top() - sum`，展开得 `sum = sum + pq.top() - sum`，消掉 $sum$ 就变成了 `sum = pq.top()`。

# $\text{Code:}$

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, sum;

priority_queue<int, vector<int>, greater<int> > pq;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1, a; i <= n; i++) {
		cin >> a;		
		pq.push(a);
	}
	for (int i = 1; i <= m; i++) {
		while (!pq.empty() && pq.top() - sum == 0) pq.pop();
		if (pq.empty()) cout << "0\n";
		else {
			cout << pq.top() - sum << "\n";
			sum = pq.top();
		}
	}
	return 0;
}

```

---

## 作者：Lyw_and_Segment_Tree (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF1088B)
## 题意简述
> 给定一个长度为 $n$ 的序列 $a$，现在要对 $a$ 序列进行 $m$ 次操作，每次操作将序列中最小的数记为 $x$，并将整个序列中所有数减去 $x$，当这个数列全为 0 时，输出 0。否则输出 $x$。

## 开始解题！
首先，我们很快便可以想到时间复杂度为 $O(nm)$ 的暴力：暴力找最小值，然后一个个减。然而这样的速度太慢了，会超时。  
然后我们分析一下，发现这个算法慢的原因在于要不停地找最小值，那么此时，我们就可以使用优先队列来优化这一过程：对于每个数，放入优先队列，那么此时队首最小值，这样使找最小值的时间复杂度降为了 $O(1)$，然后再来考虑修改操作，我们可以定义一个变量 $sum$ 来记录需要减的值。并对其进行求和。那么一开始，$sum$ 的值就是 0。此后的每一次操作中，其实这个 $x$ 就是队首减去 $sum$ 的值。因为队首自然是这个数列中最小的数，然后将其一次性地减去所需的值，其差必然是 $x$。然后让 $sum$ 加上队首减去 $sum$ 的值后，对队首进行 `pop` 操作，因为如果不进行 `pop` 操作，那么在下一次操作时，$sum$ 的值变为了队首，所以不如先 `pop` 了。那么当序列为空时，直接输出 0 即可。时间复杂度 $O(m \log n)$，可以通过。代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    priority_queue<int,vector<int>,greater<int> > q;
    int n,m,sum=0;
    cin>>n>>m;
    for(int i=1,x;i<=n;i++) cin>>x,q.push(x);
    while(m--){
        while(!q.empty()&&q.top()-sum==0) q.pop();
        if(q.empty()) puts("0");
        else{
            cout<<q.top()-sum<<endl;
            sum+=(q.top()-sum);
            q.pop();
        }
    }
}
```
[AC 记录](https://www.luogu.com.cn/record/144529364)

---

## 作者：YangXiaopei (赞：0)

## Solution

首先有个最暴力的方法：每次找最小大于 $0$ 的数，并把所有数全部减去此数，时间复杂度 $\mathcal{O}(n ^ 2)$。

我们首先要知道：时间复杂度多在了哪？

两个地方：

* 找最小。

* 遍历减去最小的数。

先解决第一个问题：

想要在更小的时间复杂度以内维护最小值，有两个好用的方法：优先队列或单调队列。

虽然单调队列时间复杂度 $\mathcal{O}(n)$，优于优先队列的 $\mathcal{O}(n \log n)$，但很明显，优先队列的时间复杂度足够了，且更方便。

再解决第二个问题：

我们需要思考：想要得到每个数，一定要在每次找到最小时去减吗？

一个数，他在任何时候减，答案都不会有变化，那我们为什么不拿一个 $sum$ 存下每次减的和，等要输出时，把它减去这个和并将 $sum$ 加上它与 $sum$ 的差以及将这个数 `pop` 掉呢？

最后，在所有算之前将所有与 $sum$ 差为 $0$ 的数 `pop` 掉就可以完美切掉这题了。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k, sum, a[100005];
priority_queue<int, vector<int>, greater<int> > q;
int main(){
	cin >> n >> k;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		q.push(a[i]);
	}
	while(k--){
		while(!q.empty() && q.top() - sum == 0){
			q.pop();
		}
		if(q.empty()){
			cout << 0 << "\n";
		}
		else{
			cout << q.top() - sum << "\n";
			sum += (q.top() - sum);
			q.pop();
		}
	}
	return 0;
}
```

---

## 作者：sccc_ (赞：0)

## 思路  
对于每一个最小值，我们无需一遍一遍的找，只需存进优先队列里，并维护小根堆。  

对于每一个都需要减去 $x$，其实我们减来减去最小值都是一个，我们可以定义一个 $sum$ 累加每次最小值减掉 $sum$ 的值，每次输出当前最小值减掉 $sum$，并且 $sum$ 加上当前最小值减去 $sum$ 的值即可。 

另外，每次输出前我们需要把与 $sum$ 差为 $0$ 的值弹出队列。  

## 代码
```c++
#include <bits/stdc++.h>

using namespace std;

int n, m, x, sum;
priority_queue<int, vector<int>, greater<int> > q;

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i ++)
	{
		cin >> x;
		q.push(x);
	}
	for (int i = 1; i <= m; i ++)
	{
		int cur;
		while (!q.empty () and q.top () - sum == 0)
		{
			cur = q.top();
			q.pop();
		}
		if (q.empty()) cout << 0 << '\n';
		else
		{
			cur = q.top();
			q.pop();
			cur -= sum;
			sum += cur;
			cout << cur << '\n';
		}
	}
	return 0;
}
```

---


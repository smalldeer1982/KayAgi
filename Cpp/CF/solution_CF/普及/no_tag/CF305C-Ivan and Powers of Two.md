# Ivan and Powers of Two

## 题目描述

Ivan has got an array of $ n $ non-negative integers $ a_{1},a_{2},...,a_{n} $ . Ivan knows that the array is sorted in the non-decreasing order.

Ivan wrote out integers $ 2^{a_{1}},2^{a_{2}},...,2^{a_{n}} $ on a piece of paper. Now he wonders, what minimum number of integers of form $ 2^{b} $ $ (b>=0) $ need to be added to the piece of paper so that the sum of all integers written on the paper equalled $ 2^{v}-1 $ for some integer $ v $ $ (v>=0) $ .

Help Ivan, find the required quantity of numbers.

## 说明/提示

In the first sample you do not need to add anything, the sum of numbers already equals $ 2^{3}-1=7 $ .

In the second sample you need to add numbers $ 2^{0},2^{1},2^{2} $ .

## 样例 #1

### 输入

```
4
0 1 1 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
1
3
```

### 输出

```
3
```

# 题解

## 作者：luojien (赞：4)

## 前置知识

- $2$ 的前 $n$ 个整数次幂之和：$\sum\limits_{i=0}^{n}2^n = 2^{n + 1} - 1$。
- $2$ 的整数次幂的合并：$2^xn=2^{x + n - 1}$。

## 思路分析
每次输入，查找是否可以合并，如果可以，那么合并。

合并后取最大的 $a_i$ 将其加一，作为目前的 $v$。

最后结果为 $v - |a| + 1$。其中，$|a|$ 表示集合 $a$ 的长度。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
set<int> s;
void uniquee(int& x)
{
	while (s.count(x))
	{
		s.erase(x);
		x++;
	} 
	s.insert(x);
}
int main()
{
	int n;
	cin >> n;
	int mx = -1e9;
	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		uniquee(x);
		mx = max(mx, x);
	}
	int v = mx + 1;
	cout << v - s.size() << endl;
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：3)

模拟赛。。

------------

考虑看作一个二进制数，最终只需要将最高位后的 $0$ 全部填成 $1$。

所以需要统计 $0$ 的个数即为答案。

用优先队列维护每个位置，若同一位有两个，则合并成高一位的 $1$。

若没有相同的则记录 $1$ 的个数，并更新最高位。

最后相减即为答案。

最多合并 $n-1$ 次一定可以变成一个二进制数。

------------

不清楚可以看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,a,now,cnt,maxx;
priority_queue<ll,vector<ll>,greater<ll> > pq;
int main(){
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++){
        scanf("%lld",&a);
        pq.push(a);
    }
    while(!pq.empty()){
        now=pq.top();
        pq.pop();
        if(!pq.empty()&&now==pq.top()){
            pq.pop();
            pq.push(now+1);
        }
        else{
            cnt++;
            maxx=max(maxx,now);
        }
    }
    printf("%lld Sherry",maxx-cnt+1);
    return 0;
}
```


---

## 作者：111101q (赞：2)

###   首先我们给出一个数学定理（~~贼简单~~）

#### $2^n +2^n =2^{n+1}$

所以我们初步的思路就是从 $0$ 遍历到 $n-1$，然后如果有一样的数字就进位。

并且题目条件已经帮我们排序好了，所以就不用手动排序了。

那如何对其进行进位操作呢？这里初步想到的思路就是用 ```set``` 进行维护。

(因为 ```set``` 类型可以进行去重）

下面附上代码（看不懂的看注释）：
```cpp
#include<iostream>
#include<set>
using namespace std;
int n,x,maxn;
set<int>s;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;//读入数字 
		while(s.count(x)){
			s.erase(x);
			x++;//去重进位 
		}
		s.insert(x);//插入数字 
		if(maxn<x)maxn=x;//找到最大的x 
	}
	cout<<maxn+1-s.size();
	//maxn+1表示的是最大的长度 ，s.size()表示的是当前的标记数 
	return 0;//完结撒花 
}
```

---

## 作者：lanretE (赞：1)

感觉前面两篇题解写的不是很清楚，所以写了一篇给萌新看的，神犇请绕道。

~~顺便说一句本题的翻译是我提供的。~~


首先看思路，我们知道题目中 $2^v-1$ 可以表示为$\sum_{i=0}^{v-1}2^{i}$，故要记录每个次幂的出现情况，然而本题中 $a_i<2\times10^9$，所以不能开数组，要使用 STL 中的 map。

因为 $2^n+2^n=2^{n+1}$，所以当我们每次输入一个次幂 $x$ 时，如果这个 $x$ 已经出现过，我们就应该将 $x+1$ 次幂出现的数量加一。同理，如果 $x+1$ 次幂也已经出现过，那么就要将 $x+2$ 次幂加一……直到发现 $x+i$ 次幂尚未出现过为止。如此一来可以保证最后所有次幂的个数都不大于 $1$。

上述过程可以用以下代码实现：

```
while(sum.count(x))//x次幂已有 
sum.erase(x++);//清除并更新x 
++sum[x];//此时x未出现过，所以加一
```
由于最后题目求的是要补上多少个次幂，所以我们应统计出已有的最高次幂，并以其作为题目里的 $v$，也就是说从 $0$ 到这个最大值中所有次幂我们都需要，即我们需要 $v+1$ 个次幂，那么答案就是 $v+1$ 减去 map 的 size。

代码如下

```cpp
#include<iostream>
#include<map>
using namespace std;
int n,v,ans;
map<int,int>sum;
int main(){
	cin>>n; 
	for(int i=1;i<=n;++i){
		int x; cin>>x;
		while(sum.count(x))//x次幂已有 
			sum.erase(x++);//清除并更新x 
		++sum[x];//此时x未出现过，所以加一
		v=max(v,x);//同时更新2次幂的最大值 
	}
	cout<<v+1-sum.size()<<endl;//由于还要考虑是否需要0次幂，所以加1 
	return 0;
}
```



---

## 作者：ztxtjz (赞：1)

## 【题意】
给你一个$n$，输入$n$个$ai$，$ai$表示$2^{ai}$。问你需要再加几个形如$2^b$的数，让他们的总和为$2^v-1$。
## 【思路】
用我们已有的数学知识可知，$2^n+2^n=2^{n+1}$。所以若当前数已输入过一次，则不断判断下一个数是否也出现过，直到一个没有输入过的数为止，并标记这个数已出现过。

最终出现过的数的个数为$a.size()$。因为$2^0+2^1+……+2^{n-1}=2^n-1$，所以还需要的个数为$n-a.size()+1$。
## 【代码】
```cpp
#include <cstdio>
#include <map>
#define ll long long
ll n;
std::map<ll,ll> a;
int main()
{
	scanf("%lld",&n);
	for(ll i=1,x;i<=n;i++)
	{
		scanf("%lld",&x);
		while(a[x]) a.erase(x++);
		a[x]++;
	}
	std::map<ll,ll>::iterator ite=a.end();  //迭代器
	ite--;  //找到最大值
	printf("%d",ite->first-a.size()+1);
	return 0;
}
```

---

## 作者：Guoliyuan2023 (赞：0)

本蒟蒻的第六篇题解。

# 题目：CF305C Ivan and Powers of Two

## 题目

[CF305C 原题传送门](https://www.luogu.com.cn/problem/CF305C)

让我们加上最少个数的 $2^x$，来满足给定序列 $+2^{x1}+2^{x2}+\dots+2^{xn}=2^v$。

## 思路

所以我们初步的思路就是从 $0$ 遍历到 $n-1$，如果有一样的数字，进位。

而且题目已经帮我们排序好了，所以就不用再排序了。（哎嘿，真省事哎）

那么就可以用 `set` 来维护。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
set <int> s;//要维护的set
int main()
{
    int n , a , maxn = -2e9;
    cin >> n;
    for(int i = 1; i <= n; i++)//真正意义上做到了《边读边处理》
    {
        cin >> a;
	    while(s.count(a) != 0)
	    {
	        s.erase(a);
	        a ++;
	    }
	    s.insert(a);
	    maxn = max(maxn , a);
    }
    cout << maxn - s.size() + 1 << endl;//输出
    return 0;//完美结束
}

```

## 温馨提示：

题目千万条，诚信第一条，代码不规范，棕名两行泪。别抄我的，也别抄别人的昂。

## The end

---

## 作者：qwq___qaq (赞：0)

注意到 $2^v-1=\sum\limits_{i=0}^{v-1}2^i$，也就是说我们要将 $2^{a_i}$ 每次插入到里面去，如果 $2^{a_i}$ 出现了两次，就合并为 $2^{a_i+1}$。

所以在合并之后，贪心地，我们应该选取的是合并后的 $a_i$ 的最大值，然后再减去元素的数量 $cnt$。

值域比较大，需要使用 `map`。

这些操作中，最耗时间的就是合并，我们来想一想。

因为 $a$ 单调不降，那么如果想要合并 $a_i$，那么就要另一个 $a_i$，这样的话，为了保证浪费的 $a$ 最少，我们需要让所有的 $n$ 相等。

那么我们就可以得到，对于 $i\mod2^x=0$，$i$ 会产生 $x$ 的贡献，那么所有的合并次数加起来就是 $\dfrac{n}{2}+\dfrac{n}{4}+\cdots$，这个式子上界是 $n$，算上 `map` 就是 $O(n\log n)$。

---

## 作者：kkkk0369 (赞：0)

水题

由于n比较大且需要去重，用STL库中的set即可。

以下代码：

```cpp
#include<cstdio>
#include<set>
using namespace std;
int n,x,maxx;
set<int> a;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&x);
		while(a.count(x)) a.erase(x),x++;
		a.insert(x);
		if (maxx<x) maxx=x;
	}
	printf("%d",maxx+1-a.size());
	return 0;
}
```

---


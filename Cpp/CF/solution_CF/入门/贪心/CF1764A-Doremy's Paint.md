# Doremy's Paint

## 题目描述

Doremy 有 $n$ 个油漆桶，用一个长度为 $n$ 的数组 $a$ 表示。第 $i$ 个油漆桶中装有颜色为 $a_i$ 的油漆。

定义 $c(l,r)$ 表示子数组 $[a_l,a_{l+1},\ldots,a_r]$ 中不同元素的个数。请选择两个整数 $l$ 和 $r$，满足 $l \leq r$，使得 $r-l-c(l,r)$ 的值最大。

## 说明/提示

在第一个测试用例中，$a=[1,3,2,2,4]$。

- 当 $l=1$ 且 $r=3$ 时，$c(l,r)=3$（$[1,3,2]$ 中有 $3$ 个不同的元素）。
- 当 $l=2$ 且 $r=4$ 时，$c(l,r)=2$（$[3,2,2]$ 中有 $2$ 个不同的元素）。

可以证明，选择 $l=2$ 且 $r=4$ 能使 $r-l-c(l,r)$ 的值最大，为 $0$。

在第二个测试用例中，$a=[1,2,3,4,5]$。

- 当 $l=1$ 且 $r=5$ 时，$c(l,r)=5$（$[1,2,3,4,5]$ 中有 $5$ 个不同的元素）。
- 当 $l=3$ 且 $r=3$ 时，$c(l,r)=1$（$[3]$ 中有 $1$ 个不同的元素）。

可以证明，选择 $l=1$ 且 $r=5$ 能使 $r-l-c(l,r)$ 的值最大，为 $-1$。选择 $l=3$ 且 $r=3$ 也是可行的。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
5
1 3 2 2 4
5
1 2 3 4 5
4
2 1 2 1
3
2 3 3
2
2 2
1
1
9
9 8 5 2 1 1 2 3 3```

### 输出

```
2 4
1 5
1 4
2 3
1 2
1 1
3 9```

# 题解

## 作者：aCssen (赞：3)

### Solution
设当前已经选出了一个区间 $[l,r]$，考虑将其扩展（这里举向右的例子，即变为 $[l,r+1]$），此时 $r-l$ 增大 $1$，而 $c(l,r)$ 只有如下两种情况：
+ $a_{r+1}$ 在 $[l,r]$ 中没有出现，则 $c(l,r)$ 增加 $1$，此时 $r-l-c(l,r)$ 的值不变。
+ $a_{r+1}$ 在 $[l,r]$ 中出现过，则 $c(l,r) $ 的值不变，此时 $r-l-c(l,r)$ 的值增加 $1$。

综上，将一个区间扩展成更大的区间时，$r-l-c(l,r)$ 的值一定不会比原来的值小，归纳一下可得，$[1,n]$ 就是答案。
### 代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=~f+1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x*f;
}
int n,x,t;
int main(){
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;i++)
			x=read();
		printf("1 %d\n",n);
	}
	return 0;
}
```

---

## 作者：zhujiangyuan (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1764A)

## 题意简述
给定一个长度为 $n$ 的序列，定义一段序列的价值为序列长度减去序列内出现的数的种类。求一个序列内价值最大的一个子序列。

## 分析
我们发现将一个区间扩展成更大的区间时，$r-l-c(l,r)$ 的值一定不会比原来的值小，因此直接输出 $[1,n]$。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,n,a;
	cin>>t;
	while(t--)
	{
		cin>>n;
	    for(int i=1;i<=n;i++) cin>>a;
	    cout<<1<<" "<<n<<endl;
	}
	return 0;
}
```

---

## 作者：lol_qwq (赞：2)

# CF1764A 题解

**思路**

假设有 $n$ 个数，我们随便取 $l$ 和 $r$，假设 $[a_l,a_r]$ 中有 $x$ 种，那么结果肯定是 $r - l - x$。如果序列是 $[a_l,a_r + 1]$ 有 $x + 1$ 种，那么肯定结果也是 $r - l - x$，但是如果只有 $x$ 种，那么结果是 $r - l -(x - 1)$。因此，要使结果更多，那么 $[a_l,a_r]$ 必定取到最多值，因此 $(a_l)_{min} = 1$，$(a_r)_{max} = n$。

**代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int a;
    cin >> a;
    while(a--){
        int b;
        cin >> b;
        for(int i = 1;i <= b;i++){
            int c;
            cin >> c;
        }
        cout << 1 << " " << b << endl;
    }
    return 0;
}
```

---

## 作者：zfx_VeXl6 (赞：0)

设区间 $[l,r]$ 中 $w(l,r)=r-l-c(l,r)$。

考虑已经找到了一对 $l$ 和 $r$，那么考虑两个区间 $[l-1,r]$ 和 $[l,r+1]$，这里只说明区间 $[l-1,r]$，分以下 $2$ 种情况讨论：

- 如果 $a_{l-1}$ 与 $a_l$ 到 $a_r$ 中的某个数相同，那么 $c(l-1,r)=c(l,r)$，$w(l-1,r)=r-(l-1)-c(l-1,r)=r-l+1-c(l,r)=w(l,r)+1$，说明区间 $[l-1,r]$ 比 $[l,r]$ 更优。

- 如果 $a_{l-1}$ 与 $a_l$ 到 $a_r$ 中的每个数都不同，那么 $c(l-1,r)=c(l,r)+1$，$w(l-1,r)=r-(l-1)-c(l-1,r)=r-l+1-(c(l,r)+1)=w(l,r)$，说明区间 $[l-1,r]$ 与 $[l,r]$ 等价。

以此类推，区间 $[1,r]$ 一定比区间 $[l,r]$ 优或与之等价。

区间 $[l,r+1]$ 也是同理，区间 $[l,n]$ 一定比区间 $[l,r]$ 优或与之等价。

因此最终的答案就是 $[1,n]$。

代码非常简单。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a;
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a;              //注意要把a[i]读进来
        cout<<1<<' '<<n<<'\n';
    }
    return 0;
}
```

---

## 作者：xyta (赞：0)

非常奇怪的一道题！你说他难吧，他的代码和思路比谁都简单。但你说他简单吧，对于萌新来说想一天都不一定明白。
## 题目概括
Doremy 有 $n$ 桶油漆，用一个长度为 $n$ 的序列 $a$ 表示。第 $i$ 个桶中的颜料编号为 $a_i$。定义 $c(l,r)$ 为从 $a_l$ 到 $a_r$ 的子串中颜料种类的数量（及相同的颜料只算一次）。请找出一对 $l$ 和 $r$ 使得 $l \leq r$ 并且 $r-l-c(l,r)$ 的值最大。

输入 $t$ 组数据。
## 题目思路
要是我和你说不管输入数据是什么只需要输出 1 和 $n$ 你信不信?其实就是这样，我们来证明一下！

为了让结果过更大，我们想要 $r$ 更大，$l$ 和 $c(l,r)$ 更小，先不考虑 $c(l,r)$ 的话，$r$ 选 $n$，$l$ 选 1 是最优情况。那 $c(l,r)$ 呢？他指的是这个子串中不同元素的个数，想要他越小，那么相同元素的个数应该越多。而 $c(1,n)$ 就包含了所有的相同元素，做到最优，但每增加一个不必要的元素，总元素个数会增加 1 ，而 $c(l,r)$ 也会增加 1 ，一抵消，也就相当于没有增加不必要的元素，所以永远会保持最优。

注：根据这个思路写完代码会发现样例不对，但是照样能通过。这是因为这道题对于每个输入数据其实有多种满足要求的输出，而样例只是给出其中的一种，题目在判断时，你的输出只要是其中一种，就都能通过！
## 通过代码
```cpp
#include<iostream>
using namespace std;
int a[100005];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		cout<<1<<" "<<n<<endl;
	}
	return 0;
}
```
这个代码没什么好说的，就不加注释了。

---

## 作者：honglan0301 (赞：0)

## 题目分析
容易发现每多加一个数, $r-l$ 增加 $1$, 而 $c(l,r)$ 最多增加 $1$, 即选取更多的数总是更优的。所以对于每组数据输出 $1$ 和 $n$ 就行。

## 代码
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n,t,a[100005];
inline int read()
{
	int now=0,nev=1; char c=getchar();
	while(c<'0' || c>'9') { if(c=='-') nev=-1; c=getchar();}
	while(c>='0' && c<='9') { now=(now<<1)+(now<<3)+(c&15); c=getchar(); }
	return now*nev;
}
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
		}
		printf("1 %d\n",n);
	}
}
```


---


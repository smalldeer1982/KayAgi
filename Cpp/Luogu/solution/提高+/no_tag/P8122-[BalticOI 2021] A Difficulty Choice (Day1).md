# [BalticOI 2021] A Difficulty Choice (Day1)

## 题目背景

**本题为交互题。**

感谢交互库与 checker 的提供者 [Hi_chocolate](https://www.luogu.com.cn/user/193198) 为本题做出的巨大贡献。

### 特别提示

**在洛谷提交本题时的一些注意事项（与原题面不同之处请以此处为准）：**

1. 提交时请在程序里加入以下函数声明语句：

```cpp
extern "C" long long skim (int i);
extern "C" void answer (std::vector<int> v);
extern "C" void impossible ();
```

你实现的 `solve` 函数应为：

```cpp
extern "C" void solve (int N, int K, long long A, int S);
```

2. 程序开头不用，也不应该包含 `books.h` 头文件。
3. 仅支持 `C++`（含 `C++`，`C++11`，`C++14`，`C++17`）提交。

## 题目描述

您致力于 AK BalticOI，而 AK BalticOI 的方式就是学习。您走进了一家书店，架子上有 $N$ 本书，编号为 $1$ 到 $N$，第 $i$ 本的难度为 $x_i$。您要从这 $N$ 本书中挑选出 $K$ 本书用来学习，您不希望学到太简单或太难的东西，所以您想要保证这 $K$ 本书的难度之和位于 $[A,2A]$ 的区间内。

可惜的是，您并不知道 $x_i$ 的具体数值，所以您要浏览这些书籍以得知他们的难度。书店老板有洁癖，他不希望您浏览太多的书籍，所以他规定您最多只能浏览 $S$ 本书，然后确定这些书的难度。幸运的是，您被告知这 $N$ 本书按照编号的增加，难度呈单调递增。

请编写一个程序，通过浏览书籍，购买您需要的书籍，或者指出无解。

### 交互格式

本题为交互题，您需要编写 `void solve (int N, int K, long long A, int S)` 函数，$N,K,A,S$ 在上面已经定义，并且保证 $x_1<x_2<\cdots<x_n$，该函数只被调用一次。

您还可以调用如下的函数：

- `long long skim (int i)` 浏览第 $i$ 本书以获取他的难度 $x_i$。
- `void answer (vector<int> v)` 买您所需要的书。其中 $v=\{i_1,i_2,\cdots,i_K\}$，并且需要满足：
$$A \le \sum\limits_{j=1}^K i_j \le 2A$$
- `void impossible ()` 指出不可能按照要求买下 $K$ 本书。

如果存在满足要求的 $K$ 本书，您必须准确地调用 `answer` 函数一次；否则您需要准确地调用 `impossible` 函数一次。调用过后，程序会自动停止。

如果您的函数调用不符合上面的格式，或者调用了超过 $S$ 次 `skim` 函数，程序会自动停止，这个测试点会判为 **Not correct**；你不能在标准输出中输出任何东西，否则会被判为 **Security violation**。

如果您使用 C++ 编码，请调用 `books.h` 头文件，如果您想检验您的程序的正确性，可以在下方附件中下载 `sample_grader.cpp` 与 `books_sample.cpp`，分别为您提供检验正确性和示例说明的作用。

如果您使用 Python 编码，可以在下方附件中下载 `books_sample.py` 检验。

交互库希望标准输入里有两行：

- 第一行四个整数，$N,K,A,S$。
- 第二行 $N$ 个整数，$x_1,x_2,\cdots,x_N$。

随后，交互库会调用您的程序，最后，交互库会在标准输出中返回信息：

|信息|意义|
|:-:|:-:|
|**Invalid input.**|标准输入的格式错误|
|**Invalid skim.**|`skim` 函数调用无效|
|**Out of books to skim.**|`skim` 函数调用超过 $S$ 次|
|**Invalid answer.**|`answer` 函数调用无效|
|**Wrong answer.**|`answer` 函数调用的 $v$ 不满足要求|
|**No answer.**|`solve` 函数没有调用 `answer` 函数和 `impossible` 函数中的任意一个|
|**Impossible (not checked): s book(s) skimmed.**|上述事件都没有发生，调用了 $S$ 次 `skim` 函数，并在有答案的时候调用了 `impossible` 函数|
|**Correct: s book(s) skimmed.**|上述事件都没有发生，调用了 $S$ 次 `skim` 函数|

针对上面若干个错误的情况，交互库仅会返回 **Not correct**，或者正确的时候返回 **Correct**。每当出现上面的若干个错误，或者您的程序调用了 `answer` 或 `impossible` 函数时，程序会被自动停止。

## 说明/提示

#### 样例 1 解释

$N=15$，$K=3$，$A=42$，$S=8$，下面是可能的两种会被判为通过的调用结果：

示例 1：

|你的程序|返回值|
|:-:|:-:|
|`skim(1)`|$1337$|
|`impossible`|-|

示例 2：

|你的程序|返回值|
|:-:|:-:|
|`skim(1)`|$7$|
|`skim(15)`|$21$|
|`answer({11,15,7})`|-|

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$S=N$，$170 \le N \le 1000$，$K=3$。
- Subtask 2（15 pts）：$S=N$，$N \ge 170$。
- Subtask 3（10 pts）：$S \ge 170$，$x_{i+1}-x_i \le \frac A K$。
- Subtask 4（15 pts）：$S \ge 170$，$x_{i+1}-x_i \le A$。
- Subtask 5（15 pts）：$S \ge 170$。
- Subtask 6（20 pts）：$S \ge 40$，$x_{i+1}-x_i \le A$。
- Subtask 7（20 pts）：$S \ge 40$。

对于 $100\%$ 的数据，$K \le N$，$3 \le N,S \le 10^5$，$1 \le A,x_i \le 10^{17}$，$3 \le K \le 10$。

#### 说明

翻译自 [BalticOI 2021 Day1 A A Difficulty Choice](https://boi.cses.fi/files/boi2021_day1.pdf)。

## 样例 #1

### 输入

```
15 3 42 8```

### 输出

```
```

# 题解

## 作者：天野星河 (赞：2)

### 理解题意

这是一个交互题，给定一个长度为 $N$ 的未知的数列 $x_i$，并且保证其单调递增，你可以用任意顺序询问其中至多 $S$ 个数，并且对于给定的值 $A$ 和 $K$，要求从 $N$ 个数中选出 $K$ 个数（不能重复），使得它们的和 $\in[A,2A]$。

### 分析

1. 先取前 $K-1$ 个，然后二分找到序列中最后一个 $i$，使得 $(\sum_{j=1}^{K-1}x_j)+x_i\le 2A$。
2. 如果不存在这样的 $i$ 则无解。
3. 如果找到的这样的和恰好 $\ge A$，则找到一组解。
4. 否则，如果存在解则一定可以用 $[1,K-1]$ 和 $[i-K+1,i]$ 中的数得到一组解。

次数为
$$\log n+2K-2$$
。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
#define rep(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
extern "C" {
	long long skim(int i);
	void answer(vector<int> v);
	void impossible();
	void solve(int n, int k, ll L, int m) {
		static const int N = 1e6 + 10;
		assert(m >= 40);
		if (k > n) return impossible();
		static ll a[N];
		rep(i, 1, n) a[i] = -1;
		ll s = 0;
		rep(i, 1, k - 1) s += a[i] = skim(i);
		if (s > 2 * L) return impossible();
		int l = k, r = n, res = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			a[mid] = skim(mid);
			if (s + a[mid] >= L && s + a[mid] <= 2 * L) {
				vector <int> t;
				rep(i, 1, k - 1) t.pb(i);
				t.pb(mid);
				return answer(t);
			}
			if (s + a[mid] > 2 * L) r = mid - 1;
			else l = mid + 1, res = mid;
		}
		if (res == -1) return impossible();
		if (a[k] == -1) a[k] = skim(k);
		rep(i, max(k + 1, res - k + 1), res) if (a[i] == -1) a[i] = skim(i);
		static int pos[N], c = 0;
		rep(i, 1, res) if (~a[i] && (i <= k || i > res - k)) pos[c++] = i;
		rep(S, 0, (1 << c) - 1) if (__builtin_popcount(S) == k) {
			ll v = 0;
			rep(i, 0, c - 1) if (S & (1 << i)) v += a[pos[i]];
			if (v >= L && v <= 2 * L) {
				vector <int> t;
				rep(i, 0, c - 1) if (S & (1 << i)) t.pb(pos[i]);
				return answer(t);
			}
		}
		return impossible();
	}
}
```
审核大大求过…

---

## 作者：_H17_ (赞：1)

## 题目分析

首先考虑判掉一些简单的情况：最前面 $K$ 个还比 $2\times A$ 大肯定不行。

其他情况我们可以直接得到解或者换成更大的数来得到解。

注意到需要换数的情况下，前面 $K$ 个的和肯定是比 $A$ 小的。

我们考虑换一个数 $i$，把他换成 $j$，使得 $d_i<d_j$，而且 $d_j-d_i\le A$。

那我们就把最小的换成一个最大的能换的。

但是这样会出现一个问题，增加值比 $A$ 还大。

增加比 $A$ 大，很可能就到 $2\times A$，我们不妨找一个上界，就是 $2\times A$ 减去前 $K-1$ 个数的和（二分，假设这个结果是 $n$，显然 $n\sim N$ 中数都没用，加上最小的还超过上界了）。

这样要不然 $\sum\limits_{j=1}^{k-1}d_j+d_n$ 在 $A\sim 2\times A$ 之间，要不然比 $A$ 小。

比 $A$ 小的话很显然每次加的都比 $A$ 小，就可以了。

至于怎么选 $i,j$ 来换，那显然 $d_i$ 最小的 $i$ 和 $d_j$ 最大的 $j$ 就行，两边用大小根堆维护即可。

总次数大约 $2\times K+\log N\le Q$。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
extern"C" long long skim(int i);
extern"C" void answer(std::vector<int> v);
extern"C" void impossible();
extern"C" void solve(int givenN, int givenK, long long givenA, int givenS){
	#define int long long 
    #define ALL(x) x.begin(),x.end()
	int n=givenN,k=givenK,a=givenA,qq=givenS,sum=0;
	vector<int>d(n+1,-1);
    vector<signed>ans(k),vis(n+1,0);
    priority_queue<pair<int,signed>,vector<pair<int,signed> >,greater<pair<int,signed> > >q;
    priority_queue<pair<int,signed> >oq;
    if(n<k)
        return impossible();//判
	for(int i=1;i<=k;i++)
		sum+=(d[i]=skim(i));
    if(sum>(a<<1))
        return impossible();//判
    if(a<=sum){
        for(int i=0;i<k;i++)
            ans[i]=i+1;
        return answer(ans);
    }//判
    sum-=d[k];
    int l=k,r=n;//二分换数
    while(l<r){
        int mid=(l+r+1)>>1;
        if(sum+(d[mid]=skim(mid))<=(a<<1))
            l=mid;
        else
            r=mid-1;
    }
    n=l;//1~n 可能被选
    if(a<=sum+d[n]&&sum+d[n]<=(a<<1)){
        for(int i=0;i<k-1;i++)
            ans[i]=i+1;
        ans[k-1]=n;
        return answer(ans);
    }//判
    for(int i=n-k+1;i<=n;i++)
        if(d[i]==-1)
            d[i]=skim(i);
    for(int i=1;i<=k;i++){
        q.push({d[i],i});
        vis[i]=1;
    }
    sum+=d[k];
    for(int i=n-k+1;i<=n;i++)
        if(!vis[i])
            oq.push({d[i],i});//两个堆
    while(sum<a){
        int id=q.top().second,val=q.top().first,
            nid=oq.top().second,nval=oq.top().first;
        if(d[nid]<=d[id])
            return impossible();//没法换了
        sum+=d[nid]-d[id];
        vis[id]=0,vis[nid]=1;
        q.pop(),q.push({nval,nid});
        oq.pop(),oq.push({val,id});//换
    }
    for(int i=0;i<k;i++)
        ans[i]=q.top().second,q.pop();
    sort(ALL(ans));
    return answer(ans);//回答
	#undef int
}
```

---

## 作者：int_R (赞：1)

发现要求是这 $k$ 个数和在 $[A,2A]$ 之间，这个 $2A$ 肯定有说法。

分类讨论有没有选择 $\geq A$ 的数。如果选择了，一定是仅选择一个 $\geq A$ 中最小的数，这时已经满足 $\geq A$ 了，剩下的肯定是要取前 $k-1$ 小。

如果没有选择，那么先默认选择最小的 $k$ 个数，如果和 $<A$，就不断把最小的数换成 $<A$ 的数中最大的数，这样每次的变化量都小于 $A$，不会突然超过 $2A$ 的上界限制。

要先找到第一个 $\geq A$ 的数的下标 $i$，还要知道下标在 $[1,k]$ 和 $[i-k,i-1]$ 中的数的值，总询问次数 $\log n+2k$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#define ll long long
using namespace std;
const int MAXN=1e5+10;ll a[MAXN],s;
extern "C" long long skim (int i);
extern "C" void answer (std::vector<int> v);
extern "C" void impossible ();
extern "C" void solve(int n,int k,ll A,int S)
{
    vector <int> ans;
    for(int i=1;i<=k;++i)
        s+=(a[i]=skim(i)),ans.push_back(i);
    if(s>=A&&s<=2*A) answer(ans);
    if(a[k]>=A) impossible();
    int l=k+1,r=n+1;while(l<r)
    {
        int mid=(l+r)>>1;
        skim(mid)>A?r=mid:l=mid+1;
    }
    if(l<=n&&s-a[k]+skim(l)<=2*A)
        ans.pop_back(),ans.push_back(l),answer(ans);
    for(int i=l-1;i>=max(l-k,k+1);--i)
    {
        s=s-a[l-i]+skim(i);
        ans.erase(ans.begin()),ans.push_back(i);
        if(s>=A) answer(ans);
    }
    impossible();
}
```

---


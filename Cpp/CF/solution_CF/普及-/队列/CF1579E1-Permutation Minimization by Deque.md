# Permutation Minimization by Deque

## 题目描述

In fact, the problems E1 and E2 do not have much in common. You should probably think of them as two separate problems.

A permutation $ p $ of size $ n $ is given. A permutation of size $ n $ is an array of size $ n $ in which each integer from $ 1 $ to $ n $ occurs exactly once. For example, $ [1, 4, 3, 2] $ and $ [4, 2, 1, 3] $ are correct permutations while $ [1, 2, 4] $ and $ [1, 2, 2] $ are not.

Let us consider an empty [deque](https://tinyurl.com/pfeucbux) (double-ended queue). A deque is a data structure that supports adding elements to both the beginning and the end. So, if there are elements $ [1, 5, 2] $ currently in the deque, adding an element $ 4 $ to the beginning will produce the sequence $ [\color{red}{4}, 1, 5, 2] $ , and adding same element to the end will produce $ [1, 5, 2, \color{red}{4}] $ .

The elements of the permutation are sequentially added to the initially empty deque, starting with $ p_1 $ and finishing with $ p_n $ . Before adding each element to the deque, you may choose whether to add it to the beginning or the end.

For example, if we consider a permutation $ p = [3, 1, 2, 4] $ , one of the possible sequences of actions looks like this:

 $ \quad $ 1.add $ 3 $ to the end of the deque:deque has a sequence $ [\color{red}{3}] $ in it; $ \quad $ 2.add $ 1 $ to the beginning of the deque:deque has a sequence $ [\color{red}{1}, 3] $ in it; $ \quad $ 3.add $ 2 $ to the end of the deque:deque has a sequence $ [1, 3, \color{red}{2}] $ in it; $ \quad $ 4.add $ 4 $ to the end of the deque:deque has a sequence $ [1, 3, 2, \color{red}{4}] $ in it;Find the lexicographically smallest possible sequence of elements in the deque after the entire permutation has been processed.

A sequence $ [x_1, x_2, \ldots, x_n] $ is lexicographically smaller than the sequence $ [y_1, y_2, \ldots, y_n] $ if there exists such $ i \leq n $ that $ x_1 = y_1 $ , $ x_2 = y_2 $ , $ \ldots $ , $ x_{i - 1} = y_{i - 1} $ and $ x_i < y_i $ . In other words, if the sequences $ x $ and $ y $ have some (possibly empty) matching prefix, and the next element of the sequence $ x $ is strictly smaller than the corresponding element of the sequence $ y $ . For example, the sequence $ [1, 3, 2, 4] $ is smaller than the sequence $ [1, 3, 4, 2] $ because after the two matching elements $ [1, 3] $ in the start the first sequence has an element $ 2 $ which is smaller than the corresponding element $ 4 $ in the second sequence.

## 说明/提示

One of the ways to get a lexicographically smallest permutation $ [1, 3, 2, 4] $ from the permutation $ [3, 1, 2, 4] $ (the first sample test case) is described in the problem statement.

## 样例 #1

### 输入

```
5
4
3 1 2 4
3
3 2 1
3
3 1 2
2
1 2
2
2 1```

### 输出

```
1 3 2 4 
1 2 3 
1 3 2 
1 2 
1 2```

# 题解

## 作者：初雪_matt (赞：2)

考虑如何保证字典序最佳。

一个元素进入双端队列，仅有进入左队头或右队头两种操作。

- 若此元素加入左队头使字典序更佳，即此元素比还未插入时的左队头小。

- 若此元素加入右队头使字典序更佳，即此元素比还未插入时的左队头大，仅有加入右队头一种选择。

核心代码：

```python
a=deque([l[0]])
for i in l[1:]:
    if i<a[0]:
        a.appendleft(i)
    else:
        a.append(i)
```

---

## 作者：kimidonatsu (赞：1)

#  CF1579E1 题解

## 题意简述

虽然题目很长很唬人，但是实际上就是使用双端队列进行一个模拟，但是要求需要按 **字典序** 来维护队列。

## 题目分析

所谓双端队列，其实完全可以用 STL 中的 `std::deque` 来实现，但是这题的考点在于 **字典序**，其实想通了也非常简单，无非就是在推进队列之前判断一下当前数据的大小，小就推到前面，大就推到后面去，输出就是从头遍历，输一个弹一个，到最后队列为空。在这里我们会使用到 `std::deque` 的以下用法：

* `front()` 返回队列首元素的引用。
* `empty()` 判断当前队列是否为空。
* `push_front()` 在头部插入一个元素，**常数复杂度**。
* `pop_front()` 删除头部元素，**常数复杂度**。
* `push_back()` 在末尾插入一个元素，**常数复杂度**。

---

接着我们可以自己用样例模拟一遍这个过程：给定数据量为 `4`，
1. 输入 `3`：当前队列为空，直接入队
2. 输入 `1`：比当前队列 `front()` 的 `3` 小，所以 `push_front()`
3. 输入 `2`：比当前队列 `front()`的 `1` 大，所以 `push_back()`
4. 输入 `4`：比当前队列 `front()` 的 `1` 大，所以 `push_back()`

那么根据这个流程，我们就可以快乐地写出代码啦~

## 代码

### `std::deque` version

```cpp
#include <bits/stdc++.h>

using namespace std;

int t, n, x;
deque< int > q;

int main() {
	ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> x;
			if (i == 1) q.push_front(x);
			else if (x > q.front()) q.push_back(x);
			else q.push_front(x);
		}
		while (!q.empty()) {
			cout << q.front() << " ";
			q.pop_front();
		}
		cout << endl;
	}
	return 0;
}

```

代码小注：

此处在第一次推送时加了一遍特判（即当 `i == 1` 时），如果在队列为空时调用 `front()` 的话是会报错的，所以只需要推进队列。

### `std::list` version

```cpp
#include <bits/stdc++.h>

using namespace std;

int t, n, x;
list< int > q;

int main() {
	ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> x;
			if (i == 1) q.push_front(x);
			else if (x > q.front()) q.push_back(x);
			else q.push_front(x);
		}
		while (!q.empty()) {
			cout << q.front() << " ";
			q.pop_front();
		}
		cout << endl;
	}
	return 0;
}

```

代码小注：

由于题目不要求支持随机访问队列下标，那么 `std::deque` 也可以用 `std::list` 快捷地代替，你会发现这份代码仅仅只是改了一下初始化容器的代码。

## 结语

> Aya 衷心祝愿大家不再因为 `std::deque()` 重蹈覆辙。		——chen_zhe


---

## 作者：Leonid (赞：1)

[原题](https://www.luogu.com.cn/problem/CF1579E1)

观察样例不难发现，当插入的数字 x 小于队头时入队头，反之入队尾即为最小字典序排列。

用 stl ```deque``` 模拟即可。

比如样例 1：

一开始队列为空，插入 3 后队头为 3，第二个数 1 比队头小，于是插入队头。2 和 4 同理。

```cpp
#include <cstdio>
#include <deque>

using namespace std;

int T, n, x;
deque <int> q;

int main(){
	scanf ("%d", &T);
	while (T--) {
		scanf ("%d", &n);
		for (int i=1;i<=n;++i){
			scanf ("%d", &x);
			if (i==1) q.push_front(x);
			else if (x>q.front()) q.push_back(x);
			else q.push_front(x);
		}
		while (!q.empty()) {
			printf ("%d ", q.front());
			q.pop_front();
		}
		printf ("\n");
	}
	return 0;
}
```


---

## 作者：ttq012 (赞：1)

由于这个题的数据范围很小，并且保证了所有的数字都不相同，所以我们可以暴力地枚举每一个序列的第一个元素：如果第一个元素比队首元素大，那么就插到队尾，否则就查到队首。


---

## 作者：MYFJWHR (赞：0)

### CF1579E1题解

首先，我们通过读题，可以发现：题目中提到了 `deque`，即双端队列，再仔细读一遍题，我们可以发现，题目中需要从队首或队尾插入数字，而我们比较熟知的，的确是上文提到的 `deque`，所以这个题考虑用双端队列做。

然后，我们再来思考做法。文中要求字典序最小，所以采用贪心策略。而第 $i$ 个数字只有两种插入情况：被插入到前面或者被插入到后面。所以我们可以得出：当第 $i$ 个数字大于当前队列中的第一个数字，就把 $i$ 扔到最后面去，否则，就把 $i$ 扔前面去。

#### AC Code

```c++
#include<bits/stdc++.h>
using namespace std;
int t;
long long n,a[200005];
deque<long long>q;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		q.push_front(a[1]);//插进去先垫个底
		for(int i=2;i<=n;i++){
			if(a[i]<q.front()) q.push_front(a[i]);//扔进对首
			else q.push_back(a[i]);//扔进队尾
		}
		for(int i=1;i<=n;i++){
			printf("%lld ",q.front());
			q.pop_front();//输出了就弹出
		}
		cout<<endl;
		q.clear();//清空队列
	}	
	return 0;
}
```



---

## 作者：__LiChangChao__ (赞：0)

## 思路

为了使得字典序最小，考虑**贪心**。

使用一个双端队列，如果要进队列的元素比队头小，就把它放到队首，否则直接扔到队尾就好了，这样就可以使得整个队列字典序最小。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
deque<int>q;//双端队列
long long n,t,x;
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&x);
			if(x<q.front())q.push_front(x);//加入队头
			else q.push_back(x);//扔到队尾
		}
		for(int i=1;i<=n;i++){
			printf("%d ",q.front());//输出
			q.pop_front();
		}
		printf("\n");
	}
}

```

---

## 作者：zwy__ (赞：0)

### 题目大意
给定一个 $1 \sim n$ 的排列，以及一个双端队列。按先后顺序将排列的第 $i$ 个数字取出并插入到双端队列的队头或队尾。求插完所有数字后双端队列中字典序最小的排列。
### 题目思路
如果我们不考虑使用 STL 的话，我们可以使用数组进行模拟。那么肯定会超时。所以，我们可以考虑使用双端队列，因为双端队列时间复杂度比较小，所以不会超时。根据题意进行模拟即可。
### 前置知识
```
deque<int>deq：定义类型为 int 的双端队列 deq。
```
```
deq.front()：访问 deq 的第一个元素。
```
```
deq.back()：访问 deq 的最后一个元素。
```
```
deq.push_front(a)：在 deq 最前面插入元素 a。
```
```
deq.push_back(a)：在 deq 最后面插入元素 a。
```
```
deq.pop_front()：删除 deq 最前面的元素。 
```
```
deq.pop_back()：删除 deq 最后面的元素。
```
```
deq.size()：获取 deq 的长度。
```
### 题目思路
有了前置知识，我们根据题意进行模拟即可。如果是第一个元素，直接插入即可。如果遇到一个元素，看一下是否比第一个元素大，就插入第一个，否则就插入最后一个。
### 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a;
deque<int>duq;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1; i<=n; i++)
		{
			cin>>a;
			if(duq.size()==0)duq.push_front(a);
			else if(a>duq.front())duq.push_back(a);
			else duq.push_front(a);
		}
		while(duq.size()>0)
		{
			cout<<duq.front()<<" ";
			duq.pop_front();
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：信息学carryHarry (赞：0)



### 题意：
给定一个 $1\sim n$ 的排列 $p$ 和一个双端队列，按先后顺序将排列的第一个数字取出并插入到双端队列的队头或队尾。求插完所有数字后双端队列中字典序最小的排列。

- 此题可以用双端队列（题目说了）模拟，然后题目就迎刃而解了。

### code:
```cpp
#include<bits/stdc++.h>

using namespace std;
const int N=2e5+5;
int t,n,a[N];
int main()
{
	cin>>t;
	while(t--){
		deque<int>dq;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			if(a[i]<=dq.front()){
				dq.push_front(a[i]);
			}
			else{
				dq.push_back(a[i]);
			}
		}
		while(!dq.empty()){
			cout<<dq.front()<<" ";
			dq.pop_front();
		}
		cout<<endl;
	}
	return 0;
}

```




---

## 作者：Jairon314 (赞：0)

$ Solution $

----------

容易发现，因为每次往 ``deque`` 中塞数字只能从左边或者右边进入，而且每次的状态互不影响。所以可以贪心，记录 ``deque`` 的 ``front`` 和 ``back`` ，设当前的数字为 ``cur`` ，则如果 $ cur < front $ ，将 ``cur`` 从前面放进去最优；如果 $ cur > back $ ，将 ``cur`` 从后面放进去最优。然后按照这种方式用 ``deque`` 模拟即可

如样例 $ 1 $：

```

4
3 1 2 4

```

模拟过程为：

一开始 ``deque`` 为空，直接加入 $ 3 $；第二次加入 $ 1 $ 的时候，从尾部插入的字典序大于从头部插入的字典序，所以应从尾部插入，此时 ``deque`` 中的数字为 $ 1 \, 3 $ ；第三次同理，$ 1 \, 3 \, 2 $ ；第四次数列变成 $ 1 \, 3 \, 2 \, 4 $


```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
using namespace std;
 
#define $int long long
 
/***** Fast_IO *****/
 
using std::cin;
using std::cout;
using vii = std::vector<int> ;
using pii = std::pair<int,int> ;
 
namespace IO{
	char buf[(1<<21)],*p1=buf,*p2=buf,buf1[(1<<21)]; int _=0;
 
	inline char gc (){
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,(1<<21),stdin),p1==p2)?EOF:*p1++;
	}
 
	#define gc getchar
	#define pc putchar
	#define ONLINE_JUDGE OJ
 
	template<class I>
	inline I read(I &x){
		x=0; I f=1; char c=gc(); if(c==EOF){ return -1; }
		while(c<'0'||c>'9'){ if(c=='-'){ f=f*(-1); } c=gc(); }
		while(c>='0'&&c<='9'){ x=(x<<1)+(x<<3)+(c^48); c=gc(); }
		return x=x*f;
	}
 
	template<class I>
	inline void write(I x){
		if(x==0){ pc('0'); return; }
		int tmp=x>0?x:(-x),cnt=0;
		if(x<0){ pc('-'); }
		while(tmp){ buf[cnt++]=(tmp%10)+'0'; tmp/=10; }
		while(cnt){ pc(buf[--cnt]); }
		return;
	}
 
	void _FILE(){
		#ifndef ONLINE_JUDGE
			freopen("text.in","r",stdin);
			freopen("text.out","w",stdout);
		#endif
	}
 
	#define out(x) write(x),pc(' ')
	#define outn(x) write(x),pc('\n')
	#define assi() pc('\t')
	#define FOR(i,a,b) for(int i(a);i<=(b);++i)
	#define ROF(i,a,b) for(int i(a);i>=(b);--i)
	#define FORs(i,a,b,s) for(int i(a);i<=(b);i+=(s))
	#define ROFs(i,a,b,s) for(int i(a);i>=(b);i-=(s))
	#define next(i,now) for(int i(link[now]);i;i=edge[i].nexty)
	#define each(i,v) for(auto &i:v)
	#define all(v) v.begin(),v.end()
	#define pb push_back
	#define mp make_pair
	#define fir first
	#define sec second
}using namespace IO;
 
/***** Fast_IO *****/
 
#define maxn 1000010
#define SIZE 5010
 
int T,n;
int a[maxn];
 
::deque<int> de;
 
int main(){
	_FILE();
	read(T);
	while(T--){
		// de.clear();
		read(n);
		FOR(i,1,n){
			int val=read(_);
			if(val<de.front()){
				de.push_front(val);
			} else{
				de.push_back(val);
			}
		}
		while(!de.empty()){
			out(de.front());
			de.pop_front();
		}
		puts("");
	}
	return 0;
}
```


---

## 作者：SSL_wj (赞：0)

# CF1579E1
## 思路
题意是显然的，就是个双端队列给**排列**排序。

考虑如何使字典序最小，那么最小的一定会在轮到它时塞到队头，剩下的塞到队尾，前面的一部分就是一个子问题，直接递归即可做到 $O(n^2)$。

考虑优化，那么有三种做法：

- 直接建结构体扔进小根堆里，选的时候看看左边选没选过即可，选上直接输出，最后从前往后输出全部没选上的，$O(n\log n)$。

- 直接结构体排序，同理，但可以使用基数排序做到 $O(n)$。

- 倒序扫一遍，拿一个单调栈记录即可，先自底向上输出栈中的，再从前往后输出不在栈中的，$O(n)$。

这里提供[第一种方法的代码](https://codeforces.com/contest/1579/submission/130245415)。

---

## 作者：Jerrlee✅ (赞：0)

## 题意
给定一个双端队列，从 $1$ 开始，往后读数，可以放在队首或队尾，拼成一种队列（它会给你拼出的队列，让你打印拼成的步骤）。
## 思路
用一个双端队列，每读入一个数就直接跟队首比较，如果比他小，扔前面就行了。

让我们证明一下：如果插入的那个数小于队首，把他仍在队首会比扔在队尾的情况字典序小，反之亦然。

总而言之，如果读入的数小于队首，那扔的数在队首的情况一定会比在队尾的情况小，反之一定会大于它。
## 注意
这又是一个多解的题目，样例对的，但不代表只能是样例！
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,a;
        cin>>n;
        deque<int>d;
        for(int i=0;i<n;i++){
            cin>>a;
            if(i==0||a<d[0]) d.push_front(a); //队首要读，否则没数来比较
            else d.push_back(a);
        }
        for(int x:d) cout<<x<<" ";
        cout<<endl;
    }
}
```
[AC记录（洛谷）](https://www.luogu.com.cn/record/58819797)

[AC记录（CF）](https://codeforces.com/contest/1579/submission/130422184)

---

## 作者：yimuhua (赞：0)

## 题意：


略

## 解题思路：

贪心。

若当前数字比队首小，则放在队首，否则放在队尾。

我使用的是 STL。

## AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, x;
deque<int> dq;
int main() {
    cin >> t;//数据组数
    while(t--) {
        cin >> n >> x;//输入排列长度和第一个数
        dq.push_back(x);//第一个先放入队列，防止RE
        for(int i = 1; i < n; i++) {
            cin >> x;
            if(x > dq.front())//比队首大
                dq.push_back(x);//放入队尾
            else//比队头小
                dq.push_front(x);//放入队首
        }
        while(!dq.empty())//while循环输出
            cout << dq.front() << ' ', dq.pop_front();
        cout << endl;//多组数据换行
    }
    return 0;
}
```


---


# Polycarp Recovers the Permutation

## 题目描述

Polycarp wrote on a whiteboard an array $ p $ of length $ n $ , which is a permutation of numbers from $ 1 $ to $ n $ . In other words, in $ p $ each number from $ 1 $ to $ n $ occurs exactly once.

He also prepared a resulting array $ a $ , which is initially empty (that is, it has a length of $ 0 $ ).

After that, he did exactly $ n $ steps. Each step looked like this:

- Look at the leftmost and rightmost elements of $ p $ , and pick the smaller of the two.
- If you picked the leftmost element of $ p $ , append it to the left of $ a $ ; otherwise, if you picked the rightmost element of $ p $ , append it to the right of $ a $ .
- The picked element is erased from $ p $ .

Note that on the last step, $ p $ has a length of $ 1 $ and its minimum element is both leftmost and rightmost. In this case, Polycarp can choose what role the minimum element plays. In other words, this element can be added to $ a $ both on the left and on the right (at the discretion of Polycarp).

Let's look at an example. Let $ n=4 $ , $ p=[3, 1, 4, 2] $ . Initially $ a=[] $ . Then:

- During the first step, the minimum is on the right (with a value of $ 2 $ ), so after this step, $ p=[3,1,4] $ and $ a=[2] $ (he added the value $ 2 $ to the right).
- During the second step, the minimum is on the left (with a value of $ 3 $ ), so after this step, $ p=[1,4] $ and $ a=[3,2] $ (he added the value $ 3 $ to the left).
- During the third step, the minimum is on the left (with a value of $ 1 $ ), so after this step, $ p=[4] $ and $ a=[1,3,2] $ (he added the value $ 1 $ to the left).
- During the fourth step, the minimum is both left and right (this value is $ 4 $ ). Let's say Polycarp chose the right option. After this step, $ p=[] $ and $ a=[1,3,2,4] $ (he added the value $ 4 $ to the right).

Thus, a possible value of $ a $ after $ n $ steps could be $ a=[1,3,2,4] $ .

You are given the final value of the resulting array $ a $ . Find any possible initial value for $ p $ that can result the given $ a $ , or determine that there is no solution.

## 说明/提示

The first test case in the example is clarified in the main section of the problem statement. There may be other correct answers for this test set.

In the second test case, $ n=1 $ . Thus, there is only one permutation that can be the answer: $ p=[1] $ . Indeed, this is the answer to this test case.

In the third test case of the example, no matter what permutation you take as $ p $ , after applying the $ n $ steps, the result will differ from $ a=[1, 3, 5, 4, 2] $ .

## 样例 #1

### 输入

```
4
4
1 3 2 4
1
1
5
1 3 5 4 2
3
3 2 1```

### 输出

```
3 1 4 2
1
-1
2 3 1```

# 题解

## 作者：szkzyc (赞：5)

首先是判无解。可以知道，不管怎样，这个数组最后生成的新数组最大值不是在最左端就是在最右端，因为在取最小值的时候最大值一直比另一个数小，直到只剩下最后一个数。所以当且仅当一个长度为 $n$ 的数组最大值（即 $n$）在首位或末位时才有解，其余情况都是无解。

对于有解的情况，当这个数组倒过来后，因为最大的数在最左边或是最右边，所以其他的数都是一个个的倒回去，也就是原来的数组。于是我们发现只要将这个数组倒序便肯定是可以的。

思维题，代码量极低。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF INT_MAX
#define debug puts("qwq")
using namespace std;
int a[200005];
int main(){
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++) cin >> a[i];
		if(a[1] != n && a[n] != n) puts("-1");//当最大值不在首位或末位就是无解 
		else{
			for(int i = n; i >= 1; i--) cout << a[i] << ' ';//倒序输出 
		}
		cout << '\n';
	}
	return 0;
}

```


---

## 作者：Texas_the_Omertosa (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1611C)

### 0x01 思路

首先我们可以想一想判断无解的方法。既然每一次都是选取两端最小的数，那么最大的一定要么在最左端，要么在最右端。由于序列元素一定是 $1\sim n$（~~翻译好像没说~~），所以我们就得出了判断无解的方法：

```cpp
	if(a[n]!=n&&a[1]!=n)
	{
		cout<<"-1\n";
		continue;
	}
```

接下来我们就要想如何输出可能解了。审题可得：最左端最小新序列就放在最右边，最右端最小就放在新序列的最左边，那么倒序输出不就是一种 可能解吗？所以我们得出了打印可能的序列的方法：

```cpp
	for(int i=n;i>=1;i--)
	{
		cout<<a[i]<<' ';
	}
	cout<<'\n';
```

剩下的都是常规操作了，相信来观摩本蒟蒻题解的大佬们都会啦~

### 0x02 AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int a[N];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int asdf=1;asdf<=t;asdf++)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		if(a[n]!=n&&a[1]!=n)
		{
			cout<<"-1\n";
			continue;
		}
		for(int i=n;i>=1;i--)
		{
			cout<<a[i]<<' ';
		}
		cout<<'\n';
	}
	return 0;
} 
```

---

## 作者：HPXXZYY (赞：1)

$\color{blue}{\texttt{[Solution]}}$

显然地，最大的数（即 $n$）一定在 $a$ 的两侧，如果不符合这个条件，那么答案一定是 $-1$。

考虑与最大数相邻的那个数，它一定比最大数小，按照题意，如果在 $a$ 中它在最大数的左（右）边，那么在 $p$ 中它就在最大数的右（左）边。

以此类推，我们可以找到一个非常妙的方法：即把 $a$ 数组逆序输出，就是可能的 $p$ 数组。


$\color{blue}{\texttt{[code]}}$


```cpp
int main(){
	for(int T=1,Q=read();T<=Q;T++){
		n=read();
		for(int i=1;i<=n;i++)
			a[i]=read();
		
		if (a[1]!=n&&a[n]!=n)
			printf("-1\n");
		else{
			for(int i=n;i>=1;i--)
				printf("%d ",a[i]);
			printf("\n");
		}
	}
	
	return 0;
}
```

---

## 作者：togeth1 (赞：0)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF1611C)

### [题意解析]
有 $n$ 组数组 $p$，我们可以对 $p$ 这个数组做一次操作：

+ 取最左边和最右边的数中较小的一个，如果选的是最左边，就加入新数组 $a$ 的左边，否则加入 $a$ 的右边。

注：$p$ 数组中的元素只包含 $1∼ n$。

### [思路分析]
首先我们考虑特判情况，什么情况下无解。因为我们只能取最左侧或最右侧，所以只要最右侧或者最左侧的其中一个不带**最大值**那这组数据无解。然后我们考虑有解的情况，既然 $1\leq n\leq200000$，~~所以我们总不可能一种一种的枚举~~。我们想如果在这组数据有解的情况下，**倒序是否是一个合法的解呢**？例如：

+ 样例 $1$ $3$ $2$ $4$，它有解，那它的倒序就是 $4$ $2$ $3$ $1$，显然它的倒序就是一组合法的解。

综上所述我们需要做的就是：

1. 特判无解情况。
2. 如果数据有解，输出数组的倒序。

### [贴上代码]
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn = 200010;
/*注意范围*/
int T,n,a[Maxn];
int main(){
	cin>>T;
	while(T--){
		cin >> n;
		for(int i=1; i<=n; i++)
			cin >> a[i];
		if(a[1] != n&&a[n] != n){
			cout << "-1\n";
			continue;
		}
		/*特判最左侧与最右侧*/
		for(int i=n; i>=1; i--)
			cout << a[i] <<" ";
		/*有解输出倒序*/
		cout << "\n";
	}
	return 0;
}
```


---

## 作者：kaceqwq (赞：0)

# 题目大意:
有一个长度为 $n$ 的数组 $p$，我们每次执行以下操作：
取 $p$ 最左边和最右边的数中较小的一个，如果选的是最左边，就加入新数组 $a$ 的左边，否则加入 $a$ 的右边。
现在给出 $a$，求 $p$ 。如果无解，输出 $-1$ ；如果多组解，输出任意一组即可。

# 分析:
首先，我们根据题意分析，这显然是一道模拟题，接着我们可以先考虑无解的情况：因为最大的数 $n$ 明显一定是在数组 $a$ 的最左边或最右边，可是如果都不在，即是无解的请况，输出 $-1$ ，无解的请况判断完了，然后根据题意模拟有解的请况即可。不过要注意的是:本题有多组数据，不要被坑了。

# Code:
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int a[200005];
signed main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
	    int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		cin>>a[i];
		if(a[1]!=n&&a[n]!=n)
		cout<<-1;
		else
		{
		for(int i=n;i>=1;i--)
		cout<<a[i]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}

```


---

## 作者：XL4453 (赞：0)

### 解题思路：

首先判断无解，队后一个放置的一定是最大的那一个，所以最大的那一个数 $n$ 一定是在最左边或者最右边，如果不在，则一定无解。

反之则一定有构造使之有解。直接将这个过程反过来，每一次找出左右两边最大的一个加入相应的左右端就行了。

---

代码实现上可以使用链表，也可以开两倍数组直接前后加。

我的代码采用了后一种实现方式。

----
### 代码：

```cpp
#include<cstdio>
using namespace std;
int n,a[200005],T,b[400005],l,r,l1,r1;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		if(a[1]!=n&&a[n]!=n){printf("-1\n");continue;}
		l=200000;r=199999;l1=1;r1=n;
		for(int i=1;i<=n;i++){
			if(a[l1]>a[r1]){
				l--;b[l]=a[l1];
				l1++;
			}
			else{
				r++;b[r]=a[r1];
				r1--;
			}
		}
		for(int i=l;i<=r;i++)printf("%d ",b[i]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：智子 (赞：0)

## 题意

有一个元素个数为 $n$ 的数组 $p$，我们每次执行以下操作：

取 $p$ 最左边和最右边的数**中较小的一个**，如果选的是最左边，就加入新数组 $a$ 的左边，否则加入 $a$ 的右边。

现在给出 $a$，求 $p$。如果无解，输出 `-1`；如果多组解，输出任意一组即可。

（[关于原翻译的错误。](https://www.luogu.com.cn/discuss/385807)）

## 思路

~~说实话第一眼看到这道题时首先想到了今年 CSP-S T3。~~

这道题其实是一个模拟，我们只需要按照题意从最终结果反推初始状态就行。

题目中每次取左右较小值，我们反过来，取 $a$ 最左边和最右边的数中较**大**的一个，如果选的是最左边，就加入原数组 $p$ 的左边，否则加入 $p$ 的右边。

判断无解也比较简单：如果有解，$n$ 要么在 $a$ 的最左边，要么在最右边。

## 代码

```cpp
#include<cstdio>
#include<deque>
using namespace std;

const int MAXN = 200000 + 5;

int a[MAXN], ans[MAXN];
int n;

int main() {
    int T;

    scanf("%d", &T);
    while(T--) {
        deque<int> q;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        if(a[1] != n && a[n] != n) {
            printf("%d\n", -1);
            continue;
        }
        int s = 1, t = n;
        while(s <= t) {
            if(a[s] > a[t]) {
                q.push_front(a[s++]);
            } else {
                q.push_back(a[t--]);
            }
        }
        for(int i = 0; i < n; i++) {
            printf("%d ", q[i]);
        }
        printf("\n");
    }

    return 0;
}

```

---


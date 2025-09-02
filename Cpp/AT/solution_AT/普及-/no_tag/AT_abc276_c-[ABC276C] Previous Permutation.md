# [ABC276C] Previous Permutation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc276/tasks/abc276_c

$ (1,\ \dots,\ N) $ の順列 $ P\ =\ (P_1,\ \dots,\ P_N) $ が与えられます。ただし、$ (P_1,\ \dots,\ P_N)\ \neq\ (1,\ \dots,\ N) $ です。

$ (1\ \dots,\ N) $ の順列を全て辞書順で小さい順に並べたとき、$ P $ が $ K $ 番目であるとします。辞書順で小さい方から $ K-1 $ 番目の順列を求めてください。

 順列とは？ $ (1,\ \dots,\ N) $ の**順列**とは、$ (1,\ \dots,\ N) $ を並べ替えて得られる数列のことをいいます。

 辞書順とは？ 長さ $ N $ の数列 $ A\ =\ (A_1,\ \dots,\ A_N),\ B\ =\ (B_1,\ \dots,\ B_N) $ に対し、$ A $ が $ B $ より**辞書順で真に小さい**とは、ある整数 $ 1\ \leq\ i\ \leq\ N $ が存在して、下記の $ 2 $ つがともに成り立つことをいいます。

- $ (A_{1},\ldots,A_{i-1})\ =\ (B_1,\ldots,B_{i-1}) $
- $ A_i $

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ P_i\ \leq\ N\ \,\ (1\ \leq\ i\ \leq\ N) $
- $ P_i\ \neq\ P_j\ \,\ (i\ \neq\ j) $
- $ (P_1,\ \dots,\ P_N)\ \neq\ (1,\ \dots,\ N) $
- 入力される値は全て整数

### Sample Explanation 1

$ (1,\ 2,\ 3) $ の順列を辞書順で小さい順に並べると次のようになります。 - $ (1,\ 2,\ 3) $ - $ (1,\ 3,\ 2) $ - $ (2,\ 1,\ 3) $ - $ (2,\ 3,\ 1) $ - $ (3,\ 1,\ 2) $ - $ (3,\ 2,\ 1) $ よって $ P\ =\ (3,\ 1,\ 2) $ は小さい方から $ 5 $ 番目であり、求める順列、すなわち小さい方から $ 5\ -\ 1\ =\ 4 $ 番目の順列は $ (2,\ 3,\ 1) $ です。

## 样例 #1

### 输入

```
3
3 1 2```

### 输出

```
2 3 1```

## 样例 #2

### 输入

```
10
9 8 6 5 10 3 1 2 4 7```

### 输出

```
9 8 6 5 10 2 7 4 3 1```

# 题解

## 作者：_H17_ (赞：7)

## 思路分析

首先，这道题就是求一个全排列的下一个值。

如果你没听说过 `prev_permutation` 函数，那这道题还是挺难得，我先来讲讲 `prev_permutation` 函数吧。

首先，我们要了解它是用来干什么的，它是用来求数组中上一个全排列并存回数组，例如：数组 $a = \{ 5 , 4 , 3 , 2 , 1 \}$，它的上一个全排列是 $a = \{ 5 , 4 , 3 , 1 , 2 \}$。

再讲一讲它是怎么用的吧。

头文件：`<algorithm>`，也可以使用万能头 `<bits/stdc++.h>`。

调用方法：`prev_permutation(首地址,末地址);`

我们可不能忘了学返回值，它的返回值是 `bool`，如果有上一个全排列返回 `true`，否则返回 `false` 和 `cin` 差不多。（本题目没有用到返回值）

于是，这道题就可以轻松解决了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[101];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",p+i);
    //输入
    prev_permutation(p+1,p+n+1);
    //核心部分，调用
    for(int i=1;i<=n;i++)
        printf("%d ",p[i]);
    //输出
    putchar('\n');
    //AT后一定要加换行！！
    return 0;
}
```

## 拓展部分

大家学了 `prev_permutation` 是不是觉得应该还有个 `next_permutation`？没错，你猜对了，调用方法差不多，用途是求下一个全排列，放两道练习题帮助大家巩固：[A](/problem/SP12150)、[B](/problem/P1088)。

---

## 作者：Y2y7m (赞：3)

第一道有点难度的题目。

模仿一下找下一个全排列的方法。

发现这个全排列前面的一部分是不需要改变的。从后往前扫，若 $a_i>a_{i+1}$ 则把 $a_{i+1}$ 放到第 $i$ 位上，把 $a_i$ 和 $a_{i+2},...,a_{n}$ 从大到小排序并输出即可。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
int a[110];
int n;
vector<int> vec;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=n-1;i>=1;i--)
	{
		if(a[i]>a[i+1])
		{
			for(int j=1;j<i;j++)
				cout<<a[j]<<" ";
			for(int j=i+1;j<=n;j++)
				vec.push_back(a[j]);
			sort(vec.begin(),vec.end());
			vector<int> ::iterator t=lower_bound(vec.begin(),vec.end(),a[i])-1;
			cout<<*t<<" ";
			vec.erase(t);
			vec.push_back(a[i]);
			sort(vec.begin(),vec.end(),greater<int>());
			for(int j=0;j<vec.size();j++)
			{
				cout<<vec[j]<<" ";
			}
			cout<<endl;
			break;
		}
	}
	return 0;
}

```


---

## 作者：cjh20090318 (赞：3)

大家好，我是 CQ-C2024 蒟蒻 CJH。

## 题意

给出 $1$ 到 $N$ 的一个排列（保证不是字典序最小的排列），求它按照字典序的上一个排列。

## 分析思路

这一道题很明显就是使用全排列 STL `prev_permutation` 函数，此函数在 `algorithm` 库中，就可以求得上一个全排列。

拓展一下：`next_permutation` 函数可以求得下一个全排列。

函数原型：`bool prev_permutation(_BidIt _First, _BidIt _Last)`

以上两个函数当没有上一个/下一个时会返回 `false`。

用法其实和 `sort` 函数是一样的，给定一个左闭右开的区间，找出这一段的全排列。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>//函数在此库中
using namespace std;
int n,a[101];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	prev_permutation(a+1,a+n+1);//求得上一个全排列。
	for(int i=1;i<=n;i++) printf("%d ",a[i]);
	return 0;
}
```

*谢谢大家！*

---

## 作者：liangbob (赞：1)

### AT_abc276_c 题解

#### 思路分析

这道题可以用 STL，有大佬已经讲过了，我就来讲一个不用 STL 的做法。这个做法其实也是 STL 内部的实际做法。

这个做法分三步：

1. 从右往左找到第一个不满足递减的数（即比它后面的数大）。因为如果是字典序最小的排列，从左往右一定递减。而题目保证不会输入字典序最小的排列，所以一定会有这个数。我们令这个数为 $q$ 。

2. 从右往左找到第一个在 $q$ 后面且小于 $q$ 的数 $p$，并将 $p$ 和 $q$ 交换。由于这个数是第一个，所以可以保证所有在 $q$ 后面的数从小到大排列。
3. 将所有在 $q$ 原来位置（即现在的 $p$ 所在的位置）的后面的数反转，这样可以保证所有在 $q$ 后面的数从大到小排列。这样就可以保证这就是按照字典序的上一个排列。

#### 关键代码

```cpp
void change()
{
	int cur = n;
	int pre = n - 1;//初始化下标
	while(cur > 1 && a[pre] <= a[cur]) //从右往左找到第一个不满足递减的数 q（即比它后面的数大）
	{
		cur--;
		pre--;//往前找
	}
	cur = n;//重置下标
	while(a[cur] >= a[pre])//从右往左找到第一个在 q 后面且小于 q 的数
	{
		cur--;
	}
	swap(a[pre], a[cur]);//交换 p 和 q
	reverse(a + pre + 1, a + n + 1);//反转 p 后面的数
}
```



---

## 作者：xiaohaoaibiancheng66 (赞：1)

# 思路
回想一下我们用 dfs 枚举全排列的过程：选定下一个**没被占用**的数字作为下一个全排列这个位置上的数字。

这里让我们求上一个全排列，所以只要一直往前追溯，追溯到一个**可以选比它小的数字**的位置，则即可把这个位置上的数字换掉。

随后在向后安排。在向后安排时要注意：有多个选择时要选最大的一个，这样才会让新排列与原排列差距最小。
# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
 
int a[300];
bool book[300];
 
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		book[a[i]]=1;
	}
	int j=n;
	for(int i=n-1;i>=0;i--)//向前回溯
	{
		j=i;
		book[a[i]]=0;
		bool b=0;
		for(int j=a[i]-1;j>0;j--)
			if(book[j]==0)
			{
				b=1;
				a[i]=j;
				book[j]=1;
				break;
			}
		if(b)break;
	}
	for(int i=j+1;i<n;i++)//向后安排
	{
		for(int j=n;j>0;j--)
		{
			if(book[j]==0)
			{
				a[i]=j;
				book[j]=1;
				break;
			}
		}
	}
	for(int i=0;i<n;i++)cout<<a[i]<<' ';
	return 0;
 } 
 ```

---

## 作者：sunzz3183 (赞：1)

# [ABC276C] Previous Permutation 题解

## 题意

给出 $1$ 到 $N$ 的一个排列，求它按照字典序的上一个排列。

## 分析

### 方法一：

我们发现有一部分前缀（可以为空）是不需要变化的，而这一前缀就是 $a_{1\sim x}$，其中 $x$ 为**从后向前第一个上升的数字的位置**，为什么呢？

全排列的实现过程其实就是在第 $i$ 的位置选择一个数字，然后把前面没有出现过的数字依次从小到大输出。

并且我们有两种情况：

1. 排列中 $a_i=i$，此时 $x=0$，因为从后向前的数字全是下降的，那么此时，就输出 $n\sim 1$。

2. 我们找到了从后向前第一个上升的数字的位置，那么上一个数字就是 $a_{x+1\sim n}$ 中第一个比 $a_x$ 小的数（$a$ 不可能为1，因为是上升，就一定要比前一个数大）记为 $a_y$，让 $a_x$ 与 $a_y$ 交换，然后顺序输出 $a_{1\sim x}$ ，倒叙输出 $a_{x+1\sim n}$。找 $a_y$ 的话就二分找，因为后面的数是递增的。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int N=1e5+5;
int n,a[N],x=0;
int er(int l,int r,int x){
	int ans;
	while(l<=r){
		int mid=(l+r)>>1;
		if(a[mid]<x)l=mid+1,ans=mid;
		else r=mid-1,ans=mid-1;
	}
	return ans;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=n;i>=1;i--)if(a[i-1]>a[i]){x=i-1;break;}
	if(!x){for(int i=n;i>=1;i--)printf("%lld ",i);return 0;}
	for(int i=1;i<x;i++)printf("%lld ",a[i]);
	int y=er(x+1,n,a[x]);
	swap(a[x],a[y]);
	printf("%lld ",a[x]);
	for(int i=n;i>x;i--)printf("%lld ",a[i]);
	return 0;
}		
```

### 方法二：

使用STL中的全排列 `prev_permutation` 函数，可以求上一个全排列，在 `algorithm` 库中。

`next_permutation` 函数可以求得下一个全排列。
 
###  代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int N=1e5+5;
int n,a[N];
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	prev_permutation(a+1,a+n+1);//求得上一个全排列。
	for(int i=1;i<=n;i++)printf("%lld ",a[i]);
	return 0;
}
```


---

## 作者：JiaY19 (赞：0)

### 思路

我们可以使用 $\text{STL}$ 内内置的函数来实现。

`prev_permutation` 用于求出某一个排列的上一个排列。

使用方法与 `next_permutation` 类似。

括号内填头指针与尾指针即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
 
const int N = 1000010;
 
int n , a[N];
 
inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
    return asd * qwe;
}
 
int main()
{
    n = read();
    for(int i = 1;i <= n;i++)
        a[i] = read();
    prev_permutation(a + 1 , a + n + 1);
    for (int i = 1; i <= n;i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
```

---


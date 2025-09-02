# Main Sequence

## 题目描述

As you know, Vova has recently become a new shaman in the city of Ultima Thule. So, he has received the shaman knowledge about the correct bracket sequences. The shamans of Ultima Thule have been using lots of different types of brackets since prehistoric times. A bracket type is a positive integer. The shamans define a correct bracket sequence as follows:

- An empty sequence is a correct bracket sequence.
- If $ {a_{1},a_{2},...,a_{l}} $ and $ {b_{1},b_{2},...,b_{k}} $ are correct bracket sequences, then sequence $ {a_{1},a_{2},...,a_{l},b_{1},b_{2},...,b_{k}} $ (their concatenation) also is a correct bracket sequence.
- If $ {a_{1},a_{2},...,a_{l}} $ — is a correct bracket sequence, then sequence ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF286C/b33e2eedc865caf6f8fa1a0ee5d1acc87a898f62.png) also is a correct bracket sequence, where $ v $ $ (v&gt;0) $ is an integer.

For example, sequences $ {1,1,-1,2,-2,-1} $ and $ {3,-3} $ are correct bracket sequences, and $ {2,-3} $ is not.

Moreover, after Vova became a shaman, he learned the most important correct bracket sequence $ {x_{1},x_{2},...,x_{n}} $ , consisting of $ n $ integers. As sequence $ x $ is the most important, Vova decided to encrypt it just in case.

Encrypting consists of two sequences. The first sequence $ {p_{1},p_{2},...,p_{n}} $ contains types of brackets, that is, $ p_{i}=|x_{i}| $ ( $ 1<=i<=n $ ). The second sequence $ {q_{1},q_{2},...,q_{t}} $ contains $ t $ integers — some positions (possibly, not all of them), which had negative numbers in sequence $ {x_{1},x_{2},...,x_{n}} $ .

Unfortunately, Vova forgot the main sequence. But he was lucky enough to keep the encryption: sequences $ {p_{1},p_{2},...,p_{n}} $ and $ {q_{1},q_{2},...,q_{t}} $ . Help Vova restore sequence $ x $ by the encryption. If there are multiple sequences that correspond to the encryption, restore any of them. If there are no such sequences, you should tell so.

## 样例 #1

### 输入

```
2
1 1
0
```

### 输出

```
YES
1 -1
```

## 样例 #2

### 输入

```
4
1 1 1 1
1 3
```

### 输出

```
YES
1 1 -1 -1
```

## 样例 #3

### 输入

```
3
1 1 1
0
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
4
1 2 2 1
2 3 4
```

### 输出

```
YES
1 2 -2 -1
```

# 题解

## 作者：Cutest_Junior (赞：4)

## 题解 CF286C 【Main Sequence】

### 题目大意

+ 与[P1739](https://www.luogu.com.cn/problem/P1739)类似；
+ 给出一个数列，其中一些数是负数，其他可正可负；
+ 把正数看成左括号，负数看成右括号；
+ 左右括号要相对应。
+ $n\le10^6$

### 思路

维护一个栈，从左到右依次加入栈。

如果加入的数是负数，则直接加入；

否则：

>若与栈顶匹配，则一起弹出。

>若不匹配，则把这个数改为负数，入栈。

如果最后栈空，则可以匹配，否则不行。

### 代码

```cpp
# include <iostream>
# include <stack>

using namespace std ;

# define return r // 防抄袭

const int N = 1000005 ;

int arr [ N ] ;

stack < int > sta ;

int read ( ) // 这题似乎有点卡常，也有可能是我个人常数太大
{
    int a = 0 ;
    char c = getchar ( ) ;
    
    while ( c < '0' || c > '9' )
    {
        c = getchar ( ) ;
    }
    
    while ( c >= '0' && c <= '9' )
    {
        a = a * 10 + c - '0' ;
        c = getchar ( ) ;
    }
    
    return a ;
}

int main ( )
{
    int n = read ( ) ;
    
    for ( int i = 1 ; i <= n ; ++ i )
    {
        arr [ i ] = read ( ) ;
    }
    
    int k = read ( ) ;
    
    for ( int i = 1 ; i <= k ; ++ i ) // 标注为负数
    {
        int x = read ( ) ;
        
        arr [ x ] = - arr [ x ] ;
    }
    
    for ( int i = n ; i ; -- i )
    {
        if ( arr [ i ] < 0 ) // 如果加入的数是负数，则直接加入
        {
            sta . push ( arr [ i ] ) ;
        }
        else
        {
            if ( ! sta . empty ( ) && arr [ i ] == - sta . top ( ) ) // 若与栈顶匹配，则一起弹出
            {
                sta . pop ( ) ;
            }
            else // 若不匹配，则把这个数改为负数，入栈
            {
                sta . push ( - arr [ i ] ) ;
                arr [ i ] = - arr [ i ] ;
            }
        }
    }
    
    if ( sta . empty ( ) )
    {
        cout << "YES\n" ;
        
        for ( int i = 1 ; i <= n ; ++ i )
        {
            cout << arr [ i ] << " " ;
        }
    }
    else
    {
        cout << "NO\n" ;
    }
    
    return 0 ;
}
```

---

## 作者：_jhq (赞：2)

### 解题思路

首先看题目关于幸运数列的定义，如果你**把正数看成左括号**，**把负数看成右括号**，你会发现这就是合法括号序列的定义。

所以题意就可以转化为：

给你一个括号序列，有一些括号一定是右括号，其他的括号你可以认为是左括号，也可以认为是右括号，问是否能构造出一个合法括号序列。

由于题目规定了一些括号是右括号，那么我们应该去找右括号，在它前面设法用左括号与之配对，所以要**倒序遍历序列**来得知当前还有多少个右括号没有配对，这显然可以用栈来维护。

因此我们得到了一个贪心做法：

从右往左倒序遍历序列，对于每个括号：

1. 如果是右括号，则直接加入栈中。

2. 否则如果栈非空，且当前括号若为左括号，能与栈顶的右括号配对的话，那么就把当前括号认为是左括号，并把它们都弹出栈。

3. 否则就只能把当前括号认为是右括号加入栈中（因为该做法是倒序遍历，如果把当前括号认为是左括号的话，那就没有与之配对的了）。

最后如果栈空了，就说明所有的右括号都与其左括号配对了，也就是说可以构造出一个合法括号序列；反之则不能。

### 正确性证明

这个贪心做法一定是正确的吗？

目前的其他三篇题解里面都没有关于贪心做法的正确性证明，所以我来补充一下。

假设贪心做法是错误的，从右往左看第一个出错的地方是位置 $i$，贪心做法的输出为 $print_i$，而正确的输出应为 $ans_i$。

因为输出的数要么是正数要么是负数，所以出错则 $ans_i$ 与 $print_i$ 互为相反数，即 $ans_i = -print_i$。

因此我们可以分为以下两种情况来讨论：

1. $ans_i>0$，$print_i<0$

如果 $ans_i>0$，则位置 $i$ 为左括号，且位置 $i$ 后面一定有能与之配对的右括号。

根据贪心做法的第 2 条和第 3 条可以发现，贪心做法是先考虑当前括号是否能为左括号，所以 $print_i>0$。

因此这种情况不存在。

2. $ans_i<0$，$print_i>0$

如果 $ans_i<0$，则正确的输出中位置 $i$ 前面必定有一个位置 $j$ 满足 $j<i$ 且 $ans_j>0$，即位置 $i$ 的右括号与位置 $j$ 的左括号配对了。

那么我们可以把 $ans_i$ 和 $ans_j$ 都变号，即在正确的输出中让位置 $j$ 的左括号变为右括号，并与它前面的左括号配对；让位置 $i$ 的右括号变为左括号，并与它后面的右括号配对。

可以发现，这样仍然能构造出一个合法的括号序列，且与贪心做法的输出相同。这也就说明了当 $ans_i<0$，$print_i>0$ 时，贪心做法是正确的。

可能有点难懂，这里举个例子，若输入为：

```
6
1 1 1 1 2 2
2 4 6
```

正确做法的输出为：

```
YES
1 1 -1 -1 2 -2
```

贪心做法的输出为：

```
YES
1 -1 1 -1 2 -2
```

在这个例子中，从右往左数第一个出错的地方是位置 3，正确做法是将位置 3 的右括号与位置 2 的左括号搭配。

我们可以将位置 2 的左括号变为右括号并与位置 1 的左括号搭配，将位置 3 的右括号变为左括号并与位置 4 的右括号搭配。

可以发现，这样输出仍然是合法的，并且与贪心做法的输出相同。

综上所述，这个贪心做法是正确的。

### 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

void read(int &s)
{
	s = 0; bool pd = false; char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-') pd = true;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		s = (s << 3) + (s << 1) + (c ^ 48);
		c = getchar();
	}
	if (pd) s = -s;
	return;
}

const int N = 1e6 + 10;
int n, t, top, a[N], sta[N], ans[N];

int main()
{
	read(n);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	read(t);
	for (int x, i = 1; i <= t; i++)
		read(x), a[x] = -a[x];
	for (int i = n; i; i--)
	{
		if (a[i] < 0) ans[i] = sta[++top] = a[i];
		else if (a[i] == -sta[top]) ans[i] = a[i], top--;
		else ans[i] = sta[++top] = -a[i];
	}
	if (top) puts("NO");
	else
	{
		puts("YES");
		for (int i = 1; i <= n; i++)
			printf("%d ", ans[i]);	
	}
	return 0;
}
```

---

## 作者：tuzhewen (赞：0)

### 题目大意

定义一个“整数括号序列”：每个正整数都要有一个与之匹配的相反数，把正整数视为左括号，负整数视为右括号。

设$lsum_i$,$rsum_i$为位置$1$~$i$的左、右括号数量，则这个序列要满足：

即每个左（右）括号都有对应的右（左）括号。

现在给你$N$个**正**整数，给定其中$M$个位置，对其取负，问能否将另一些位置的正整数也取负，使得这个“整数括号序列”合法。如果可以，输出这个修改后的序列。

$N\le 10^6,M\le N$

#### 输入格式

第一行一个$N$，接下来一行$N$个**正整数**，下面一行一个$M$，然后$M$个数$q_i$紧接其后，表示将$a_{q_i}$变成原来的数的相反数。

#### 输出格式

如果不能把更改后的数组变得合法，就输出`NO`，否则输出`YES`，并且输出更改后的合法序列。

### 思路

我们从右往左贪心（因为我们要根据右括号去匹配左括号），然后如果当现在的$a_i< 0$我们就把它推到当前的栈里，如果遇到了一个正整数，那就看看这个数跟栈顶匹不匹配，匹配就pop掉栈顶，否则我们就把当前这个**正整数**变为它的相反数，然后也推进栈里面，试着跟后面的正整数匹配。

如果栈不空，那么就匹配不了，就输出`NO`,否则输出`YES`，然后再把我们刚刚的$a$数组输出即珂。

### $ACcode$



```c++
#include<bits/stdc++.h>
#define F(i,l,r) for(register int i=l;i<=r;i++)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define p_b push_back
#define m_p make_pair
#define il inline
using namespace std;
int n,m;
int a[1000005],q;
stack<int> S;
int main() {
	scanf("%d",&n);
	F(i,1,n) scanf("%d",&a[i]);
	scanf("%d",&m);
	F(i,1,m) scanf("%d",&q),a[q]=-a[q];//以上均为如题所述
	for(int i=n;i>0;i--) {
		if(a[i]>=0&&!S.empty()&&S.top()==-a[i]) S.pop();//如果栈顶可以与当前a[i]匹配（一定要记住保证栈不空！）
		else S.push(a[i]*=a[i]>0?-1:1);//否则把当前的也变为负数推进去
	}
	if(!S.empty()) return puts("NO"),0;
	puts("YES");
	F(i,1,n) printf("%d ",a[i]);
	return 0;
}
```



---

## 作者：Infiltrator (赞：0)

~~好久没写题解，社区贡献掉了……~~  
赶紧来一发  

# 解题思路
看到此题中的括号一词，我们不难想到栈这个东西  

因为有左括号，则必有右括号  

因为后扫到的左括号先和右括号匹配，所以可以用栈维护  

那么我们就从右边开始向左边扫，扫到一个位置不能和栈顶元素匹配或者已经被钦定为右括号，就把他丢进右括号的栈里  

为什么从右边开始扫呢？  

因为题目给出的是钦定的右括号，也就是说这些位置一定是右括号  

如果从左边开始则不能很好的满足这些数是右括号的条件  

所以从右边开始贪心即可  

若扫到的元素不能和栈顶元素匹配，如果把它和别的元素匹配，就会导致一个括号被忽略的情况，所以不能和栈顶匀速匹配就进栈    

方案的话如果是右括号就是-，左括号就是+

# CODE
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define int long long
int n,m,top=0;
int a[2000050],stack[2000050],b[2000050],answer[2000050];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	scanf("%lld",&m);
	int x;
	for(int i=1;i<=m;i++)scanf("%lld",&x),b[x]=1;
	for(int i=n;i>=1;i--)
	{
		if(a[i]!=stack[top] || b[i]==1)stack[++top]=a[i],answer[i]=-1;
		else top--,answer[i]=1;
	}
	if(top)printf("NO");
	if(!top)printf("YES\n");
	if(!top)for(int i=1;i<=n;i++)printf("%lld ",answer[i]*a[i]);
	return 0;
}
```

---


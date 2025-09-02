# Spoilt Permutation

## 题目描述

给出一个长度为 $ n $ 的序列（保证序列中 $ 1-n $ 每个数有且仅出现1次），问能否恰好反转序列中的一段，使得序列变成 $ 1,2...n $ 的顺序。

## 样例 #1

### 输入

```
8
1 6 5 4 3 2 7 8
```

### 输出

```
2 6
```

## 样例 #2

### 输入

```
4
2 3 4 1
```

### 输出

```
0 0
```

## 样例 #3

### 输入

```
4
1 2 3 4
```

### 输出

```
0 0
```

# 题解

## 作者：MurataHimeko (赞：5)

## CF56B


------------

### 思路

按照题意，我们通过一遍循环来找出**位置编号和该位置上的值不同（停顿）的最小编号和最大编号**。


代码实现：


------------

```cpp
    for(register int i(1); i <= n; ++i) {
        if(val[i] ^ i) {
            sum++;
            if(i < l) l = i;
            if(i > r) r = i;
        }
    }
```



------------

我们最终的答案就是由 $l$ 和 $r$ 围成的区间。因为：
1. 区间外的数字是一定合法的，否则会在上面的代码更新边界，所以没有必要再向外拓展边界。
2. 而如果边界取不到 $l$ 或 $r$， 则会导致边界上的数仍然不合法。

我们直接判断翻转后的序列是否合法即可。


------------

### 代码


------------
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define max_(a, b) a > b ? a : b
#define min_(a, b) a < b ? a : b
#define INF 0x3f3f3f3f

namespace IO {
char buf[1<<21], *p1 = buf, *p2 = buf, buf1[1<<21];
inline char gc () {return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}

#ifndef ONLINE_JUDGE
#endif

template<class I>
inline void read(I &x) {
    x = 0; I f = 1; char c = gc();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = gc(); }
    while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = gc(); }
    x *= f;
}

template<class I>
inline void write(I x) {
    if(x == 0) {putchar('0'); return;}
    I tmp = x > 0 ? x : -x;
    if(x < 0) putchar('-');
    int cnt = 0;
    while(tmp > 0) {
        buf1[cnt++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while(cnt > 0) putchar(buf1[--cnt]);
}

#define in(x) read(x)
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')

} using namespace IO;

int n;
int val[1003], pos[1003];
int l = 1002, r, sum;

int main() {
    read(n);
    for(register int i(1); i <= n; ++i) read(val[i]), pos[val[i]] = i;
    for(register int i(1); i <= n; ++i) {
        if(val[i] ^ i) {
            sum++;
            if(i < l) l = i;
            if(i > r) r = i;
        }
    }
    if(!sum) {
        puts("0 0");
        return 0;
    }
    for(register int i(l); i <= r; ++i) {
        if(val[r+l-i] ^ i) {
            puts("0 0");
            return 0;
        }
    }
    out(l), out(r);
}
```


------------

感谢您能阅读本蒟蒻这篇题解！

---

## 作者：Lucifer_Bartholomew (赞：2)

# 排序模拟
将序列排序，即换成1~n的序列，与原序列比较，若不一样的一段是互相的倒序，即可通过一次翻转得到，即为合法，输出该段序列的头尾序号；否则输出0 0。
```cpp
#include <cstdio>
#include <algorithm>
#define rr register int
using namespace std;
inline int read()
{
    char ch=getchar();
    if(!(~ch))return 0;
    int f=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    int x=0;
    while(ch>='0'&&ch<='9')
    {
        x=(x<<3)+(x<<1)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int a[1001],b[1001];
int main()
{
	int n=read();
	for(rr i=1;i<=n;++i)
		a[i]=b[i]=read();//读入序列并复制
	sort(b+1,b+n+1);//将一个序列排序到有序
	int x=0;
	for(rr i=1;i<=n;++i)//找不同段的开头
	{
		if(a[i]!=b[i])
		{
			x=i;
			break;
		}
	}
	int y=0;
	for(rr i=n;i;--i)//找不同段的结尾
	{
		if(a[i]!=b[i])
		{
			y=i;
			break;
		}
	}
	for(rr i=y;i>x;--i)//比较该不同段
		if(a[i]+1!=a[i-1])
		{
			puts("0 0");
			return 0;
		}
	printf("%d %d\n",x,y);
	return 0;
}
```
~~我是蒟蒻~~

---

## 作者：人间凡人 (赞：1)

### 这题n只有1000啊！直接暴力模拟不就好了吗？

题意：输入 $n$ 个数，问是否只翻转一段的数，使得这 $n$ 个数递增排列$(1 , 2 ... n)$

思路：纯暴力模拟，现将这 $n$ 个数排序，然后一个个比较，如果发现第i位不相同，那么求出正确的数在输入的数中的位置 $m$ ，则说明应该翻转 $i$ 到 $m$ 这一段的数，那么就去判断，如果发现翻转后仍然不匹配，则输出$0$ $0$ 否则输出 $i$ $m$ 即可。

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,a[1005],b[1005],Id[1005];
int ans,ans1,ans2;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=a[i],Id[b[i]]=i;
	sort(a+1,a+n+1);
	i=1;
	while(i<=n){
		if(a[i]!=b[i]){
			m=Id[a[i]];
			for(int j=i+1;j<=m;j++)
				if(b[j]!=b[j-1]-1){
					printf("0 0\n");
					return 0;
				}
			ans++;
			ans1=i;ans2=m;
			i=m;
		}
		i++;
	}
	if(ans!=1)printf("0 0\n");
	else printf("%d %d\n",ans1,ans2);
	return 0;
}
```


---

## 作者：Kissland (赞：1)

题目可以理解为:

是否可以通过翻转 1-n 的某个区间,得到给定的序列。

**当且仅当翻转区间左端元素的值与右端下标以及右端元素的值等于左端下标时成立**
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a[1011];
	int n;
	while(~scanf("%d",&n))
	{
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i]);
			
		int i=1,j=n;
		while(a[i]==i) ++i;
		while(a[j]==j) --j;
		if(i<j && a[i]==j &&a[j]==i) 
			printf("%d %d\n",i,j);
		else printf("0 0\n");
		
	}

	return 0;
}
```


---

## 作者：Fan_Tuan (赞：0)

## 题意：
给定一个长度为 $n$ 的序列，问能否反转其中的一段使得这个序列的顺序变为 $1,2,...,n$。

## 思路：
~~这题建议评橙~~。

枚举，因为只能翻一次，所以首先枚举一遍序列中最长一段不能符合 $a_i = i$ 的一段子序列，把所有不符合条件的序列元素都包含起来，然后我们发现如果我们反转一段 $l$ 到 $r$ 的区间，使得他变为 $l,l+1,...,r$ 的顺序，那么这段区间里的元素必须是 $r,r-1,...,l$ 的顺序，所以我们只需要判断一下我们找出的不符合要求的子序列是否满足这个条件就行了。

## 代码：
```cpp
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>
// #define int long long
using namespace std;

inline int read() {
    int f = 0, s = 0;
    char ch = getchar();
    while (!isdigit(ch)) f |= ch == '-', ch = getchar();
    while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
    return f ? -s : s;
}

void print (int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) print (x / 10);
    putchar(x % 10 + '0');
} 

const int maxn = 1e3 + 10;
int n, a[maxn], l, r, flag;

signed main() {
    n = read();
    l = n, r = 1;
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++) 
        if (a[i] != i) 
            l = min(l, i), r = max(r, i), flag = 1;
    for (int i = l + 1; i <= r; i++) 
        if (a[i] + 1 != a[i - 1]) {
            puts("0 0");
            return 0;
        }
    if (flag) cout << l << " " << r;
    else puts("0 0");
    return 0;
}
```

---

## 作者：Mint_Flipped (赞：0)

这道题是一个简单的模拟题。

思路大概就是这样：

1：找到一个与该位置不匹配的数，做一个翻转判断。

YES：

（1）继续走，如果再找到一个不匹配的数，不用判断，输出 0 0。

（2）没有就是可以输出翻转的两个位置。

NO：0 0。

2：都匹配，输出0 0 即可。

解释下翻转判断：就是用不匹配数的下标i，到p[ i ]，作为新的一段j，再用p [ i ] ，到i，作为新的一段k，判断p [ j ]！=k即可。

~~PS：我还是觉得这应该是一道普及题 QAQ。~~

代码如下：
```c
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define lowbit(a) (a&(-a))
#define fir(a) a->first 
#define sec(a) a->second 
const int inf=0x3f3f3f3f;
const int maxn=1e3+5;
const int mod=1e9+7;
const double eps=1e-6;
int n,p[maxn];
int main()
{
    scanf("%d",&n);
    fo2(i,n)
    scanf("%d",&p[i]);
    int l,r;
    bool flag=0;
    fo2(i,n){
        if(i!=p[i]){
            if(flag){
                printf("0 0\n");
                return 0;
            }
            int j=p[i];
            int k=i;
            bool fg=0;
            for(;j>=i;--j){
                if(p[j]!=k++){
                fg=1;
                break;
                }
            }
            if(!fg)
            flag=1,l=i,r=p[i],i=p[i];
        }
    }
    if(flag){
    printf("%d %d\n",l,r);
    return 0;
    }
    printf("0 0\n");
    return 0;
}
```




---

## 作者：谦谦君子 (赞：0)

**这题不是很难，模拟就行了，然后一次次check，代码如下**
```cpp
#include<iostream>
using namespace std;
int n,num[1010];
int check1(int t)
{
    for (int i=t;i<n-1;i++)
	{
        if (num[i]!=num[i+1]-1)
		{
            return i+2;
        }
    }
    return 0;
}
int check2(int t)
{
    for(int i=t;i<n-1;i++)
	{
        if(num[i]!=num[i+1]+1)
		{
            return i+1;
        }
    }
    return 0;
}
int main()
{
    int a,b,c,flag,flag2,t,k;
    while (cin>>n)
	{
        a=b=flag=flag2=0;
        for (int i=0;i<n;i++)
		{
            cin>>num[i];
        }
        a=check1(0);
        if (a)
		{
            b=check2(a-1);
            if (b)
			{
                c=check1(b);
                if (c)
				{
                    flag=1;
                    a=b=0;
                }
            }
            else
			{
                b=n;
            }
        }
        if (a==n)
		{
            b=check2(0);
            if (b)
			{
                a=0;
            }
            else
			{
                a=1;
                b=n;
            }
        }
        if (a==0||b==0)
		{
            a=b=0;
        }
        cout<<a<<" "<<b<<endl;
    }
    return 0;
}
```

---


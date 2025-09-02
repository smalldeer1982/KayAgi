# Ohana Cleans Up

## 题目描述

Ohana Matsumae is trying to clean a room, which is divided up into an $ n $ by $ n $ grid of squares. Each square is initially either clean or dirty. Ohana can sweep her broom over columns of the grid. Her broom is very strange: if she sweeps over a clean square, it will become dirty, and if she sweeps over a dirty square, it will become clean. She wants to sweep some columns of the room to maximize the number of rows that are completely clean. It is not allowed to sweep over the part of the column, Ohana can only sweep the whole column.

Return the maximum number of rows that she can make completely clean.

## 说明/提示

In the first sample, Ohana can sweep the 1st and 3rd columns. This will make the 1st and 4th row be completely clean.

In the second sample, everything is already clean, so Ohana doesn't need to do anything.

## 样例 #1

### 输入

```
4
0101
1000
1111
0101
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
111
111
111
```

### 输出

```
3
```

# 题解

## 作者：きりと (赞：2)

**[题目传送门](https://www.luogu.com.cn/problem/CF554B)**

### 题目大意

见中文翻译

### 解题思路

因为我们每对一列格子进行操作，就相当于将这一列的数字取反，如果我们在进行过若干次操作以后，有两行的数字一样，则这两行数字原来也肯定一样。

现在我们要让某几行数字都变成$0$，也就是说这几行数字原来必须相同，不同的两行数字无论如何操作都不能变成相同的两行，更不能全变成$0$。

那么，我们只需要去计算有多少行的数字相同，取其中最大值即可。

### 代码实现

开$map$存一下每行的数字串出现次数，取$max$

```cpp
#include<bits/stdc++.h>
using namespace std;
map<string,int> mp;
string s;
signed main()
{
	int n,maxn=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		mp[s]++;
		maxn=max(maxn,mp[s]);
	}
	cout<<maxn<<endl;
	return 0;
}
```

完结撒花~~

---

## 作者：Franka (赞：1)

~~看到楼下建了个图，小蒟蒻瑟瑟发抖。~~
### **题目**
给定一个$n*n$的方阵（**只有**$0$和$1$），求**反转**过后，最多能有几行**全是0**。

所谓的反转，指的是将$0$变成$1$，$1$变成$0$。
### **思路**
首先分析下样例：

$0101$

$1000$

$1111$

$0101$

样例解释：翻转$1,3$两行，使得$1,4$两列变成全白，最多$2$行全白。

反转$1$和$3$？

可以发现，第一行和第三行是一样的。

化简题目：求n行中，有多少行是一样的，输出最大值。
### **代码**
```pascal
var max,s,n,i,j:longint;a:array[0..101] of string;//定义
begin
 readln(n);//读入n
 for i:=1 to n do readln(a[i]);//读入a数组
 for i:=1 to n do//每行都要找
  begin
   s:=0;//s清零
   for j:=1 to n do if a[i]=a[j] then inc(s);//如果有相等，s累加
   //注：自己的这一行也要算进去
   if s>max then max:=s;//找最大值
  end;
 writeln(max);//输出最大值
end.
```


---

## 作者：Rainbow_qwq (赞：1)

[CF554B Ohana Cleans Up](https://www.luogu.com.cn/problem/CF554B)

---

作为一道 Div.2 的 B 题，而且 $n\le 100$ ，~~应该是道简单题~~

来观察一下样例。
```cpp
4
0101
1000
1111
0101
```
翻转第 $1$ 列与第 $3$ 列，能使第 $1$ 行与第 $3$ 行全变成 $1$ 。

而第 $1$ 行与第 $3$ 行是完全一样的！

也就是说，只有若干行完全一样，它们才可以一起变成全 $1$ 。

那么只要把输入当字符串 `string` ，再开一个 `map<string,int>a` 统计每个串出现次数，最后输出出现次数最大的那个。

时间复杂度 $O(n\log n)$ 。

代码：
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
string s;
map<string,int>a;
int n,res;
int main()
{
	n=read();
	For(i,1,n){
		cin>>s;
		a[s]++;
        res=max(res,a[s]);
	}
	cout<<res;
    return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF554B)

建议评橙。

### 思路

如果我们翻转一列，则这一列上的 $1$ 都会变为 $0$。

如果有两行相同，则它们一定可以通过翻转相同列而变为全 $0$ 行。

而如果两行不同，则它们之间一定相互影响。

所以本题的答案就是最大的重复行的个数。

记录方法是 $\operatorname{map}$。

```
#include<iostream>
#include<map>
#include<cstring>
using namespace std;
map<string,int>mp;
string s;
int n;
int ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		mp[s]++;
		ans=max(ans,mp[s]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：wbs200 (赞：0)

这个题的意思是：给定一个 $n \times n$ 的 $01$ 矩阵，可以修改若干列，求修改后最多有多少行的元素都为 $1$，并输出这个数。

很明显这又是一道思维题，我们可以从中发现一些性质：设这个矩阵有 $2$ 行：

1. 当这 $2$ 行完全相同时，则改变一列后，这一列的两个数仍相同。
2. 当这 $2$ 行不相同时，则改变一列后，这一列的两个数不同。

然后我们就可以发现：

1. 行与行之间的相等不变。
2. 任意行均可变成全 $1$。

于是我们可以将问题转化成：统计每一行的次数，求出次数最大值就可以了。这样统计的话我们把每一行看作一个字符串，用一个哈希表就行了。

```
#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    int n;
    cin >> n;
    unordered_map<string, int> cnt;
    while (n--)
    {
        string s;
        cin >> s;
        cnt[s]++;
    }
    int ans = 0;
    for (auto [k, v] : cnt) ans = max(ans, v);
    cout << ans << endl;
    return 0;
}
```

---


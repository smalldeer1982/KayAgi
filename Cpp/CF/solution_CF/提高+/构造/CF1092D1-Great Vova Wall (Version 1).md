# Great Vova Wall (Version 1)

## 题目描述

### 题意简述
给定一个序列 $a=\{a_1,a_2,\dots,a_n\}$，有以下两种操作：

- 若 $a_i=a_{i\ +\ 1}$，则可将 $a_i$ 与 $a_{i\ +\ 1}$（$1\le i < n$）同时加 $1$；
- 将 $a_i$（$1\le i\le n$）加 $2$。

求问是否可经过多此操作后使得所有 $a_i$ 相等。

------------


Vova 在建一堵墙（Vova 美名其曰“The Great Vova Wall”）。此时有序列 $a=\{a_1,a_2,\dots,a_n\}$，其中 $a_i$ 表示墙体第 $i$ 部分的高度。

 _（注：此问题中假设 Vova 的砖头无限且只能用 $2\times 1$ 的砌墙）_ 
 
Vova 可以将砖头水平放置或垂直放置。当然水平放置时不可让砖头“越界”，即砖头不可有部分位于第 $1$ 部分的左边或位于第 $n$ 部分的右边。水平放置时砖头将会使第  $i$ 和 $i+1$ 部分高度 $+\ 1$，垂直放置时则将其所在的位置高度 $+\ 2$。

重度强迫症患者兼完美主义者 Vova 认为所有部分高度相等以及墙内没有空隙时这堵墙才算完工。
****

## 说明/提示

【样例 $1$】

初始：$[2,1,1,2,5]$；  
第一次操作：$[2,1+1,1+1,2,5]$；  
第二次操作：$[2+1\times 3,2+1\times 3,2,2,5]$；  
第三次操作：$[5,5,2+1\times 3,2+1\times 3,5]$； 
最终序列：$[5,5,5,5,5]$。

【样例 $2$】

初始：$[4,5,3]$；  
第一次操作：$[4,5,3+2]$；  
第二次操作：$[4,5+1,5+1]$；  
第三次操作：$[4+2,6,6]$；  
最终序列：$[6,6,6]$。

【样例 $3$】

初始：$[10,10]$；  
最终序列：$[10,10]$。

【样例 $4$】

初始序列：$[1,2,3]$；  
此序列无法通过题目给定操作完工。

## 样例 #1

### 输入

```
5
2 1 1 2 5
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
4 5 3
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
2
10 10
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
3
1 2 3
```

### 输出

```
NO
```

# 题解

## 作者：BqtMtsZDnlpsT (赞：10)

传送门[CF1092D1 Great Vova Wall (Version 1)](https://www.luogu.com.cn/problem/CF1092D1)

- 首先可以发现，将 $a_i+2$ 的这个条件只是用来增加高度的

	1.  因此可以想到，先把所有 $a_i$ 都 $+2$ 使序列只判断 $+1$ 的情况。如
        
		$$\texttt{2,1,1,2,5}$$
		$$\Downarrow$$
		$$\texttt{4,5,5,4,5}$$
        
    1. 其次可以发现，处理后，相邻的两个 $a_i$ 若相同，相当于没有用（可以把他们同时 $+1$ ，再做对其他的做第一步，成与其他相同的）
        
		$$\texttt{4,5,5,4,5}$$
		$$\Downarrow$$
		$$\texttt{4,6,6,4,5}$$
    再进行第一步：
	$$\Downarrow$$
	$$\texttt{6,6,6,6,5}$$
    再进行第二步：
	$$\Downarrow$$
	$$\texttt{7,7,7,7,5}$$
    再进行第一步：
	$$\Downarrow$$
	$$\texttt{7,7,7,7,7}$$
- 由此想到奇偶性（二进制）
	$$\texttt{2,1,1,2,5}$$
	$$\Downarrow$$
	$$\texttt{0,1,1,0,1}$$
	$$\Downarrow$$
	$$\texttt{0,1+1,1+1,0,0,1}$$
	$$\Downarrow$$
	$$\texttt{0,0,0,0,1}$$
	$$\Downarrow$$
	$$\texttt{1,1,1,1,1}$$
- 可以用栈判断连续两个数奇偶性相同情况，并删除

上代码：
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
int a[2000005],q[2000005],n,t;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i]=a[i]%2;
	for(int i=1;i<=n;i++)
	{
		q[++t]=a[i];//入栈
		if(t>1&&q[t]==q[t-1])t-=2；//若相同，删除
	}
	puts(t<2?"YES":"NO");//注意正好一个数也算是
	return 0;
}
```


---

## 作者：Erica_N_Contina (赞：1)

## V1

给定一个序列 $a=\{a_1,a_2,\dots,a_n\}$，有以下两种操作：

- 若 $a_i=a_{i\ +\ 1}$，则可将 $a_i$ 与 $a_{i\ +\ 1}$（$1\le i < n$）同时加 $1$；

- 将 $a_i$（$1\le i\le n$）加 $2$。

求问是否可经过多此操作后使得所有 $a_i$ 相等。

---

首先我们考虑第 $2$ 种操作——我们只使用这一种操作很显然并不能达到目的，但是我们可以使用操作 $2$ 来让每个 $\max(a_i)-\min(a_i)≤1$，这样我们用操作 $1$ 会更容易讨论一些。

下面我们来讨论一些情况。

- $a,a+1,a+1,a$ 型

这种情况我们先把中间两个 $+1$，变成 $a,a+2,a+2,a$。然后对两边执行操作 $2$，即可变成 $a+2,a+2,a+2,a+2$。

- $a+1,a,a,a+1$ 型

一目了然了。

上面是一些具体的例子，下面我们来考虑比较普遍的情况。我们考虑把所有 $a_i$ 看成是在对 $2$ 取模的意义下，那么操作 $1$ 就是对相邻的两个数字同时取反，操作 $2$ 就相当于没有影响。

现在问题看上去貌似简单了一些：给定 $01$ 串，每次你可以选择相邻两个数字把他们取反。求最后是否可以让所有数字相等。由上面第一个距离可以发现，如果两个奇偶性相同的数字中间有若干**对奇偶性相同**的数字，那么这两个数字也是可以最终变成和其他数字奇偶性相同。

于是我们可以想到括号匹配，用**栈**来维护。我们定义一种括号匹配为 `(` 与 `(` 匹配，`)` 与 `)` 匹配，那么本题就是询问能否在这种匹配规则下完成匹配，或者只有一个字符无法匹配（思考为什么这种情况也合法）。详情看代码。

---

```C++
/*
CB Ntsc
*/

#include<bits/stdc++.h>
using namespace std;
// #define long long long long
#define mp make_pair

#define rd read()
inline long long read()
{
	long long xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(long long out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}


// void solve(){

//     cerr<<"\nlong longrr[][]=";
//     for(long long i=1;i<=n;i++)cerr<<t[i].l<<' '<<t[i].r<<endl;
// }



const long long N=5e5+5;
 const long long M=5e5+5;
const long long INF=2e9+5;
const long long MOD=2e9+7;
bool f1;
long long n,t,k;
long long stk[N],top;
long long ans;
long long a[N];
bool f2;


signed main(){

    // freopen("woof.in","r",stdin);
    // freopen("woof.out","w",stdout);

	n=rd;
	while(n--){
		int a=rd;
		if(a%2==stk[top]%2&&top)top--;
		else stk[++top]=a;
	}
	if(top>1)cout<<"NO";
	else cout<<"YES";
    
}

/*
2 5
0 1 1 1 1
0 1 1 2 4
0 2 1 2 1
0 2 1 1 4
*/
```




---

## 作者：Leaper_lyc (赞：0)

先观察两个操作，发现：
- 对于 $+1$ 的操作，我们可以改变两个相邻且相同的数的奇偶性。
- 对于 $+2$ 的操作，只能改变数的大小，不能改变数的奇偶性。
- 两个结合可以发现，若相邻两数奇偶性相同，则可以变为同一大小。

也就是说**两个相邻的数可以相消**。

举个栗子：

$[2,2,1,3,5,9]$，等同于 $[0,0,1,1,1,1]$。

$[3,3,1,3,5,9]$，$[4,4,1,3,5,9]$，
$[5,5,1,3,5,9]$，
$[6,6,1,3,5,9]$，
$[7,7,1,3,5,9]$，
$[8,8,1,3,5,9]$，
$[9,9,1,3,5,9]$，这些等同于消去两个 $0$，此时相当于 $[1,1,1,1,1,1]$。

$[9,9,3,3,5,9]$，
$[9,9,5,3,5,9]$，
$[9,9,7,3,5,9]$，
$[9,9,9,3,5,9]$，
$[9,9,9,5,5,9]$，
$[9,9,9,6,6,9]$，
$[9,9,9,7,7,9]$，
$[9,9,9,8,8,9]$，
$[9,9,9,9,9,9]$，这些就是最后的“抬高”过程。

可以用单调栈来实现。

注意特判一个的情况，这种也是可以的。

简短的代码：
```cpp
#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;
stack <int> s;
signed main() {
	int n; scanf("%d", &n);
	for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x), x %= 2;
		if (!s.empty() && s.top() == x) s.pop();
		else s.push(x);
    }
	puts(s.size() < 2 ? "YES" : "NO");
}
```

---

## 作者：Elaina_ (赞：0)

这一题我们只要知道一件事情：他能否满足要求之和每个位置上的奇偶性有关，因为我们有长度为 $2$ 的砖块去补齐。

不难得到做法：

在输入的时候就判断奇偶性，相同就合并在一起，如果当前那个数是已经合并过的，就再和上一个数合并，最后判断一下长度是否为 $2$ 并分类一下两个位置上的数就能得到答案：

左右奇偶性不同并且存在至少一个合并过的数或者合并完了的串长度只有 $1$ 就输出 YES，否则是 NO。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int F=1100000;

int read(){
    char ch=getchar();int x=0,f=1;
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}

int t,n,op,top;
int a[F],ml[F];

signed main(){
    n=read();
    a[0]=-1,top=0;
    for(int i=1;i<=n;i++){
        a[++top]=read(),a[top]&=1;
        while(a[top]==a[top-1] && top>1) top--,a[top]=3;
        if(a[top]==3 && top>1) top--;
    }
    int ff=0;
    if((top<=2 && (a[1]==3 || a[2]==3)) || top==1) cout<<"YES"<<'\n';
    else cout<<"NO"<<'\n';
    return 0;
}
### ```

---

## 作者：WaterSun (赞：0)

# 思路

发现，如果相邻元素的奇偶性相同，那么一定能通过在较低的位置竖着放若干个如果在 $i$ 的位置竖着放一块砖头，使得这两列的高度相同。

那么，我们想到直接考虑 $h_i$ 的奇偶性，即将 $h_i \leftarrow h_i \bmod 2$。

如果 $h_i = h_{i + 1}$，我们显然可以同时使 $h_i$ 和 $h_{i + 1}$ 同时变成 $(h_i + 1) \bmod 2$。

那么我们可以将所有的长度为偶数的连续相同的子串全部删除，如果最后剩下的元素小于等于 $1$，说明有解。因为当剩下 $1$ 个时，其它的元素可以通过若干次变换变成剩下的元素。

所以我们可以用一个栈来维护此过程，当当前栈顶元素与当前元素相同，那么就可以凑出一个长度为 $2$ 的可删除的子串，直接弹出栈顶元素即可。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2e5 + 10;
int n;
stack<bool> st;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	n = read();
	for (re int i = 1;i <= n;i++){
		int x;
		x = read() & 1;
		if (!st.empty() && st.top() == x) st.pop();
		else st.push(x);
	}
	if (st.size() <= 1) puts("YES");
	else puts("NO");
	return 0;
}
```

---

## 作者：Gold14526 (赞：0)

[Great Vova Wall (Version 1) ](https://www.luogu.com.cn/problem/CF1092D1)

### 题意简述

给出一个长度为 $n$ 的序列，每次将相邻两个相同的数同时加 $1$，或者将任意一个数加 $2$，问经过若干次操作后，序列是否能满足任意两个数都相同。

### 结论

- 两个数是否能只通过加 $2$ 操作相同，只与奇偶性相关

如果两个数奇偶性相同，显然较小数加若干次 $2$ 总能与较大数相同。

如果不同，由于加 $2$ 并不会影响数字的奇偶性，奇偶性不同的数字一定不同。

### 做法

考虑把奇数项的奇偶性全部反转，原操作就变成了交换相邻两个数的奇偶性，这样的好处是你可以保证在不反转的情况下，它们的奇偶性一定是相同的。

这样你最后需要把序列变成以下两种情况中的一种就可以了（$0$ 代表偶数，$1$ 代表奇数）：

```
0 1 0 1 0 1 ...
1 0 1 0 1 0 ...
```

显然只要奇数和偶数的数量之差不超过一就有解。

### Code

十分简短，只有 $16$ 行。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,s[2];
int main()
{
    cin>>n;
    while(n--)
    {
        cin>>x;
        x+=n;
        ++s[x%2];
    }
    if(abs(s[0]-s[1])<=1) printf("YES");
    else printf("NO");
    return 0;
}
```

---


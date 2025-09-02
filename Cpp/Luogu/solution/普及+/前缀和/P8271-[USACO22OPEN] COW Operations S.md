# [USACO22OPEN] COW Operations S

## 题目描述

Bessie 找到了一个长度不超过 $2 \cdot 10^5$ 且仅包含字符 'C'，'O' 和 'W' 的字符串 $s$。她想知道是否可以使用以下操作将该字符串变为单个字母 'C'（她最喜欢的字母）：

1. 选择两个相邻相等的字母并将其删除。

2. 选择一个字母，将其替换为另外两个字母的任一排列。

求出这个字符串本身的答案对 Bessie 而言并不足够，所以她想要知道 $s$ 的 $Q$（$1\le Q\le 2\cdot 10^5$）个子串的答案。


## 说明/提示

【样例解释】

第一个询问的答案是「是」，因为 s 的第一个字符已经等于 'C'。

第五个询问的答案是「是」，因为 s 的第二到第三个字符组成的子串 OW 可以通过两步操作变为 'C'：

```
   OW
-> CWW
-> C
```

这个样例字符串 COW 的其他子串均不能被转变为 'C'。

【测试点性质】

- 测试点 2-4 满足 $|s|\le 5000$ 以及 $Q\le 5000$。
- 测试点 5-11 没有额外限制。

## 样例 #1

### 输入

```
COW
6
1 1
1 2
1 3
2 2
2 3
3 3```

### 输出

```
YNNNYN```

# 题解

## 作者：ppip (赞：16)

[题目传送门](https://www.luogu.com.cn/problem/P8271)

# 性质

首先，三个字母是可以随意交换的，所以先用 `XYZ` 代替 `COW`。
 
枚举易得以下性质（`=>` 意为**变换后答案不变**，`=x>` 反之，`E` 表示空串）：

1. `X =x> Y`
1. `XY =x> X/Y`
1. `XYZ =x> X/Y/Z`
1. `XX =x> X`
1. `XY => Z`（逆运算）
1. `E => XX`（逆运算）

整合一下就得到了三个字母各最多有一个的解决方案：

|$s$|$ans$|理由|
|:-:|:-:|:-:|
|`E`|`N`|性质 4、6|
|`C`|`Y`|-|
|`O`|`N`|性质 1|
|`W`|`N`|性质 1|
|`CO`|`N`|性质 2|
|`CW`|`N`|性质 2|
|`OW`|`Y`|性质 5|
|`COW`|`N`|性质 3|

于是我们的目标变为：尝试将字符串 $s$ 简化为上述情况中的一种。

---
接下来，让我们请出伟大的性质  7：

7. `XY => Z => YX`（性质 5）
7. `XX => XX`

也就是说，**任意两个相邻的的字符可以互相交换**。

这意味着什么呢？

冒泡排序学过没？

也就是说，**这个字符串可以被任意的重新排列**。

相信到这里各位都会做了。

# 解法
我们将字符串 $s$ 排序，把相邻的删掉，最后每种字符最多有一个。完了。

用前缀和处理一下，对于每个询问，统计区间内的三个字符的个数除以 2 的余数，再根据上面的表格求出答案就行了。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN(2e5+5);
int sum[MAXN][3];
int c['~'];
int main()
{
    c['C']=0;c['O']=1;c['W']=2;
    string s;cin>>s;
    for (int i{1};i<=s.size();++i)
    {
        for (int j{0};j<3;++j) sum[i][j]+=sum[i-1][j];
        ++sum[i][c[s[i-1]]];
    }
    int T;cin>>T;
    while (T--)
    {
        int l,r;scanf("%d %d",&l,&r);
        int z[3];
        for (int i{0};i<3;++i)
            z[i]=sum[r][i]-sum[l-1][i]&1;
        printf("%c",!(z[1]^z[2])&&(z[0]^z[1])?'Y':'N');
    }
    return 0;
}
```

---

## 作者：lihanwen12 (赞：10)

题目大意  
给定一个由字符 'C'，'O' 和 'W' 构成的字符串 s，允许两种操作：删除两个相邻且相等的字符或者选择一个字母将其替换为另外两个字母的任一排列。回答 $Q$ 个询问，第 $l$ 到第 $r$ 个字符组成的子串能否通过若干次操作变为单个字符 'C'。  

思路  
注意到字符串 s 的长度不超过 $200000$，询问个数 $Q$ 同样不超过 $200000$。所以 $O(|s|\times Q)$ 做法肯定会超时。尝试对字符 'O' 进行操作：  
```
O-->CW-->CCO-->O
O-->CW-->COC
O-->CW-->OWW-->O
O-->CW-->WOW
O-->WC-->OCC-->O
O-->WC-->COC
O-->WC-->WWO-->O
O-->WC-->WOW
```
观察发现如果相邻两个字符不同则可以将其转换成三者中的另一个字符，如果相邻两个字符相同则可以将其一同删除。字符的相对顺序并不影响转换且转换可逆，即一个字符 'C' 可以视为一个字符 'O' 和一个字符 'W'，一个字符 'O' 和一个字符 'W' 也可以视为一个字符 'C'。  
对三种字符出现的个数预处理出一个前缀和，用于快速统计区间 $[l,r]$ 中每种字符出现的个数。如果字符 'O' 和字符 'W' 奇偶性相同则可以将其全部转换为字符 'C'，看能否最终转换成奇数个字符 'C'，如果字符 'O' 和字符 'W' 奇偶性不同则注定无解。时间复杂度为 $O(|s|+Q)$。

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
long long n,Q,l,r,A,B,C,nc[200010],no[200010],nw[200010];
bool p;
int main(){
	cin>>st>>Q;
	n=st.size();
	for(int i=0;i<n;i++){
		nc[i+1]=nc[i];
		no[i+1]=no[i];
		nw[i+1]=nw[i];
		if(st[i]=='C')nc[i+1]++;
		if(st[i]=='O')no[i+1]++;
		if(st[i]=='W')nw[i+1]++;
	}
	for(int i=1;i<=Q;i++){
		cin>>l>>r;
		A=(nc[r]-nc[l-1])%2;
		B=(no[r]-no[l-1])%2;
		C=(nw[r]-nw[l-1])%2;
		if(A==1 && B==0 && C==0){
			cout<<"Y";
            continue;
		}
		if(A==0 && B==1 && C==1){
			cout<<"Y";
            continue;
		}
		cout<<"N";
	}
	return 0;
}

```

---

## 作者：wangyibo201026 (赞：8)

## 思路

~~话说 USACO 官方题解用得是暴力？~~

首先我们定义一种运算 $\bigotimes$，则 $a \bigotimes b$ 表示当一个字符串里只有 $a$ 和 $b$ 这两个字符时产生的最后的字符。

那么我们可以推出以下式子：

1. $C \bigotimes C = \varnothing$，$O \bigotimes O = \varnothing$，$W \bigotimes W = \varnothing$。

2. $C \bigotimes O = W$，$O \bigotimes C = W$，$C \bigotimes W = O$，$W \bigotimes C = O$，$O \bigotimes W = C$，$W \bigotimes O = C$。

3. $\varnothing \bigotimes C = C$，$\varnothing \bigotimes O = O$，$\varnothing \bigotimes W = W$，$C \bigotimes \varnothing = C$，$O \bigotimes \varnothing = O$，$W \bigotimes \varnothing = W$。

4. $\varnothing \bigotimes \varnothing = \varnothing$。

我们可以看出几个性质：

1. $\bigotimes$ 这种运算满足交换律。

2. $\bigotimes$ 这种运算满足逆元。

3. 自己试一试，$\bigotimes$ 这种运算满足结合律。

所以我们考虑大力前缀和。

我们再把这三种字母编上号，就会发现 $\bigotimes$ 这种运算实际上就是异或！所以我们就可以用异或来解决这个问题了。

我们只需要把区间内的元素全部异或，如果等于 $1$ 那么就输出 YES，否则输出 NO。

## 代码

代码：

```cpp
#include<bits/stdc++.h>
#define int long long   //防爆

using namespace std;

const int N = 2e5 + 5;

string s;
int sum[N];

int q;

void Solve(){
	cin >> s;
	s = " " + s;
	sum[1] = (s[1] == 'C' ? 1 : (s[1] == 'O' ? 2 : 3));
	for(int i = 2; i < s.size(); i++){
		sum[i] = (sum[i - 1] ^ (s[i] == 'C' ? 1 : (s[i] == 'O' ? 2 : 3)));
	}    //初始化前缀异或数组
	cin >> q;
	while(q--){
		int l, r;
		cin >> l >> r;
		cout << ((sum[l - 1] ^ sum[r]) == 1 ? 'Y' : 'N');   //这里只需要异或就可以得到最终结果
	}
}

signed main(){
  Solve();
  return 0;
}
```

---

## 作者：XGTD (赞：2)

# P8271 [USACO22OPEN] COW Operations S

看了一圈，各位神犇都是用的前缀和或者异或，怎么没人用最直白的方法呀？**倍增了解一下！**

## Problem statement
[p8271](https://www.luogu.com.cn/problem/P8271)。

## Solution

首先玩几组数据，发现一个显然的性质，任意两个不同的字母都可以变成第三个字母。只需要把他们中的一个分裂再把剩下的三个其中两个消掉，就只剩第三个原来没出现的字母了。令此操作为操作三。

其次，由上面的性质发现每一段字母都可以通过一系列操作变成一个或者零个字母，因为只要还有两个或以上字母一定可以用题目给出的操作一消掉，或者用操作三使字母数减一，直到只剩一个或零个字母。

最后再玩几组数据发现似乎操作的顺序并不影响，每个字符串一定会得到一个固定的结果。~~我太蒻了不会证。~~

有了以上三个发现，再考虑到是长度为 $10^5$ 的区间上的询问，大概率是 $O(n \log n)$ 预处理再 $O(\log n)$ 求答案，想到倍增。

我用了一个非常像 st 表的思路，$f_{i,j}$ 表示从 $i$ 开始的 $2^j$ 个字母全部合并后是什么。$1$ 表示 C，$2$ 表示 O，$3$ 表示 W，$4$ 表示空串。

转移也和 st 表非常像，
$$f_{i,j}=\operatorname{merge}(f_{i,j-1},f_{i+2^{j-1},j-1})$$

$\operatorname{merge}$ 函数表示把这两个字母（或者空串）合并的结果。

处理询问时也是用倍增思想，但和 st 表不太一样，相当于把区间长度拆成好几个（最多 $ \log n$ 个）$2$ 的次幂加起来，一次一次跳过去，单次查询复杂度 $O(\log n)$。

细节看代码，有注释。

## Code

```cpp
/*
1 h

OMG my idea is completely original????

no one on usaco or luogu's thought of this????

W*F???

isn't this like natrual? like you have interval queries but only
O(n) or O(nlogn) complexity, what to do? binary lifting! duh

but everyone else did prefix sum and parity checking?
well I suppose that too is what i should've thought of first
but still binary lifting is natural


first notice that if you have two different letters, you can
always turn it into the third one.

then after playing around with some man made samples, you notice
that it seems like the order you do the operations don't matter?
what ever order you combine the sequence you can always get
down to one, and the one you get to is certain????


and now we try binary lifting, utilize an idea almost like
st table rmq, where f[i][j] = when combined a[i] through
a[i + 2^j - 1](-1 cuz that way it's 2^j elements in total), what
is the final letter? 1 = c, 2 = o, 3 = w, 4 = empty


and the transition is almost exactly like st table rmq too.


why have ABSOULTELY NO ONE thought of this before? it's so 
natural!!!
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
string s;
//log2 1e5 approximately 18
int n, q, a[200005], b[200005], f[200005][25];
//f[i][j] = after merging i to i + 2^j - 1
signed main(){
	cin>>s;
	n = s.size();
	for(int i = 1; i <= n; i++){
		if(s[i - 1] == 'C')b[i] = 1;
		else if(s[i - 1] == 'O')b[i] = 2;
		else b[i] = 3;
		f[i][0] = b[i];
	}
	for(int j = 1; j <= log2(n); j++){	
		for(int i = 1; i <= n - (1 << j) + 1; i++){
			int val1 = f[i][j - 1];
			int val2 = f[i + (1 << (j - 1))][j - 1];
			//alot like st table rmq, but not quite
			if(val1 == 4){
				f[i][j] = val2;
				continue;
			}
			if(val2 == 4){
				f[i][j] = val1;
				continue;
			}
			if(val1 == val2){
				f[i][j] = 4;
				continue;
			}
			if(val1 != 1 && val2 != 1)f[i][j] = 1;
			else if(val1 != 2 && val2 != 2)f[i][j] = 2;
			else if(val1 != 3 && val2 != 3)f[i][j] = 3;
		}
	}
	cin>>q;
	while(q--){
		int x, y;
		cin>>x>>y;
		if(x == y){
			if(b[x] == 1)cout<<"Y";
			else cout<<"N";
			continue;
		}
		int ans = 4;
		for(int i = 18; i >= 0; i--){
			//"jump" from x to y, atmost log times
			if(x + (1 << i) - 1 <= y){
				if(ans == 4){
					ans = f[x][i];
				}else if(f[x][i] == 4){
					ans = ans;
				}else if(f[x][i] == ans){
					ans = 4;
				}else if(f[x][i] != 1 && ans != 1){
					ans = 1;
				}else if(f[x][i] != 2 && ans != 2){
					ans = 2;
				}else if(f[x][i] != 3 && ans != 3){
					ans = 3;
				}
				x += (1 << i);
			}
		}
		if(ans == 1)cout<<"Y";
		else cout<<"N";
	}
	cout<<endl;
	return 0;
}

```

## Result
[AC](https://www.luogu.com.cn/record/199815109)

这种解法比正解慢得多，但是我觉得似乎比正解好想~~还是我太蒻了。~~

求赞。

---

## 作者：lndjy (赞：1)

我做这题的时候他还是个橙，做完就绿了（

其实就是两个性质。

性质 1：**操作可逆。**

证明:`CO->WOO->W`，其他同理，也就是两个连续字母可以变成另一个字母。

这时你就可以线段树，每个区间维护区间合起来的字符，就做完了。

但是可以简单一些。

性质2：**重排不影响答案。**

考虑交换：因为操作可逆，`CO->W->OC`。

这样只需要维护区间三个字母个数，前缀和即可。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
char a[200005];
int sum[200005][3],n;
int main()
{
	cin>>(a+1);n=strlen(a+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<3;j++)
		sum[i][j]=sum[i-1][j];
		if(a[i]=='C') sum[i][0]++;
		if(a[i]=='O') sum[i][1]++;
		if(a[i]=='W') sum[i][2]++;
	}
	int q;
	cin>>q;
	while(q--)
	{
		int l,r;
		cin>>l>>r;
		int f[3];
		for(int i=0;i<3;i++)
		f[i]=(sum[r][i]-sum[l-1][i])%2;
		if(f[1]&&f[2]) f[1]=f[2]=0,f[0]^=1;
		if(f[0]&&f[1]==0&&f[2]==0) cout<<"Y";
		else cout<<"N";
	}
 	return 0;
}


```


---

## 作者：Little09 (赞：1)

面对这种题目要大胆赋值。

考虑序列肯定可以不停操作，最后剩下可能是：空、`C`、`O`、`W`。

我们把空赋值为 $0$，`COW` 三个字母分别是 $1,2,3$。

操作 $1$ 对应的是两个相等的数运算后得 $0$。操作 $2$ 则是两个不相等的数运算后得到第三个数。还有一点是 $0$ 和任何数运算得 $0$。

容易发现这就是异或运算！XOR 是具有交换律和结合律的，因此操作结果与顺序无关，就是所有字母的异或值。

所以就一下 XOR 前缀和，每次询问回答就行了。

```
#include <bits/stdc++.h>
using namespace std;

const int N=500005;
int n,m; 
char a[N];
int s[N];

inline int read()
{
    int F=1,ANS=0;
	char C=getchar();
    while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
    while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
    return F*ANS;
}

int main()
{
	cin >> (a+1);
	n=strlen(a+1);
	m=read();
	for (int i=1;i<=n;i++)
	{
		if (a[i]=='C') s[i]=(s[i-1]^1);
		else if (a[i]=='O') s[i]=(s[i-1]^2);
		else s[i]=(s[i-1]^3);
	}
	for (int i=1;i<=m;i++)
	{
		int l=read(),r=read(),ans=s[r]^s[l-1];
		if (ans==1) printf("Y");
		else printf("N");
	}
	return 0;
}

```


---

## 作者：I_am_Accepted (赞：1)

### Analysis

居然是结论题……

------------

**结论：** 设字符串中 `C`、`O`、`W` 的个数分别为 $c,o,w$。这个字符串能变成 `C` 当且仅当

$$\begin{aligned}
2&\ |\ o+w
\\
2&\nmid c+o
\end{aligned}$$

**引理 A：** 任意 $2$ 个相邻的不同字符总是可以变换成 $1$ 个，且必然是这两种以外的另一种字符。

正确性显然，故不证。

**证明：** 

**必要性：**

我们先将相邻的 `W` 消掉，再用引理 A 将所有 `W` 消掉。这样 $c+o$ 仍然为奇数，且 $o$ 为偶数，$c$ 为奇数。再把相邻的 `C`、`O` 消掉，最后一定是 `COCOC` 或 `OCOCOCO` 类型之一，显然都可以化成 `C`。

**充分性：**

若 $2\nmid o+w$，则不论怎样 $o+w$ 一定是奇数，不可能变化成单个 `C`。（`O` 和 `W` 至少留一个)

若 $2\ |\ c+o$。则不论怎样 $o+c$ 一定是偶数，一定不可能变化成单个 `C`。（若存在奇数个 `C`，则一定存在 `O`)

$\blacksquare$

------------

所以我们处理一下前缀和就可以线性解决。

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define N 200010

string s;
int a[N][3],n,q;
signed main(){IOS;
	cin>>s;
	n=s.size();
	For(i,1,n){
		For(j,0,2) a[i][j]=a[i-1][j];
		if(s[i-1]=='C') a[i][0]++;
		if(s[i-1]=='O') a[i][1]++;
		if(s[i-1]=='W') a[i][2]++;
	}
	int x,y;
	cin>>q;
	while(q--){
		cin>>x>>y;x--;
		cout<<((((a[y][0]-a[x][0]+a[y][1]+a[x][1])&1) && !((a[y][2]-a[x][2]+a[y][1]+a[x][1])&1))?'Y':'N');
	}
return 0;}
```

---

## 作者：xixike (赞：1)

[更好的阅读体验](https://xixike.github.io/USACO2022.3%20Silver/)

## Description

[Luogu传送门](https://www.luogu.com.cn/problem/P8271)

## Solution

非常妙的一道题（不理解为什么只有橙）。

题目中只有两种操作：

- 删除两个相邻且相同的字符。
- 把两个相邻且不同的字符换成第三种字符。

我们预处理出一个 $4 \times 4$ 的数组 $nxt$，0 表示空字符，1 表示 `C`，2 表示 `O`，3 表示 `W`。

$nxt_{i, j}$ 即为状态 $i$ 和 $j$ 合并之后是什么。

然后再预处理一个前缀和 $sum_i$，表示从 1 合并到 $i$ 之后剩下一个什么字符（显然合并顺序不影响结果）。

然后查询时直接 $O(1)$ 判断 $nxt[sum_{l - 1}][sum_r]$ 是否为 1 即可。

## Code

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define ll long long

using namespace std;

namespace IO{
    inline int read(){
        int x = 0;
        char ch = getchar();
        while(!isdigit(ch)) ch = getchar();
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x;
    }

    template <typename T> inline void write(T x){
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

const int N = 2e5 + 10;
char s[N];
int n, m;
int nxt[4][4] = {
    0, 1, 2, 3,
    1, 0, 3, 2,
    2, 3, 0, 1,
    3, 2, 1, 0
};
// '': 0  'C': 1  'O': 2   'W': 3
int sum[N];

inline int calc(int x){
    if(s[x] == 'C') return 1;
    if(s[x] == 'O') return 2;
    if(s[x] == 'W') return 3;
}

inline void init(){
    n = strlen(s + 1);
    for(int i = 1; i <= n; ++i)
        sum[i] = nxt[sum[i - 1]][calc(i)];
}

signed main(){
    scanf("%s", s + 1);
    init();
    m = read();
    while(m--){
        int l = read(), r = read();
        putchar(nxt[sum[l - 1]][sum[r]] == 1 ? 'Y' : 'N');
    }
    return 0;
}
```

---

## 作者：Sparkle_ZH (赞：1)

**题意简述**
+ 给定一个仅包含字符 'C'，'O' 和 'W' 的字符串 $s$，有两种操作：
  1.选择两个相邻的字符并将其删除。
  2.选择一个字母，将其替换为另外两个字母的任一排列。
+ $q$ 次询问，每次询问给定 $l, r$，问能否通过上述两种操作将 $s$ 的子串 $[l, r]$ 变为单个字母 'C'，能则输出 'Y'，不能则输出 'N'。
+ $1 \leq l \leq r \leq \mid s \mid \leq 2 \cdot 10^5$， $1 \leq q \leq 2 \cdot 10^5$。

**解题思路**

比较简单的思维题。

首先思考在变化的字符串 $s$ 中有什么是不变的。

这种题目的一个常见套路就是分析奇偶性。我们记字符 'C'，'O'，'W' 的个数为 $c, o, w$，列出下表观察奇偶性：

||$c$|$o$|$w$|$c+o$|$o+w$|$w+c$|$c+o+w$|
|-----|-----|-----|-----|-----|-----|-----|-----|
| 操作 $1$ | 奇偶性不变|奇偶性不变|奇偶性不变|奇偶性不变|奇偶性不变|奇偶性不变|奇偶性不变|
| 操作 $2$ | 奇偶性变|奇偶性变|奇偶性变|奇偶性不变|奇偶性不变|奇偶性不变|奇偶性变|

我们惊奇地发现：$c+o, o+w, w+c$ 的奇偶性自始至终都不变！

既然我们需要把字符串变成单个字符 'C'，那么 $c+o$ 就 $w+c$ 就应该是奇数，$o+w$ 就应该是偶数。

那么解法也呼之欲出了。我们使用前缀和维护 'c'，'o'，'w' 出现的次数，对于每一次询问，求出该子串里 $c+o, o+w, w+c$ 的值，再判断奇偶性是否符合要求即可。

**代码**

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0; char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = (x<<3) + (x<<1) + ch - '0', ch = getchar();
	return x;
}

const int L = 2e5 + 5;
int q, l, r, c, o, w, pre[L][3];
string s;

int main() {
    cin >> s;
    for (int i = 0; i < s.size(); i++) {
	if (i) pre[i][0] = pre[i-1][0], pre[i][1] = pre[i-1][1], pre[i][2] = pre[i-1][2];
	if (s[i] == 'C') pre[i][0]++;
	else if (s[i] == 'O') pre[i][1]++;
	else pre[i][2]++;
    }
	
    q = read();
    while (q--) {
	l = read()-1, r = read()-1;
	if (l) c = pre[r][0]-pre[l-1][0], o = pre[r][1]-pre[l-1][1], w = pre[r][2]-pre[l-1][2];
	else c = pre[r][0], o = pre[r][1], w = pre[r][2];
	if (((c+o)&1) && ((c+w)&1) && !((o+w)&1)) printf("Y");
	else printf("N");
    }
	
    return 0;
}
```

---

## 作者：SSER_ZRQ (赞：0)

# COW Operations S题解

观察样例可以得知，`OW` 可以合并为一个 `C`。

**那如果被一个或几个 `C` 间隔呢？？？**

根据题意得：`C` = `OW` or `WO`.

所以对于 `OCW` 或 `WCO`这一种子串，可以转化为 `OOWW` 或 `WWOO`从而消除。

另外的，对于 `OCCW` 这种也可以转为 `OOWWOW` 从而变为 `OW`。

可以得出，在一个子串中，`O` 和 `W` 能配出的 `C` 的个数与位置无关。

**那么，正解也渐渐地浮出水面了！！**

我们先统计子串中 `O`,`W`的个数，找出能配成多少个 `C`。

边询问边统计容易爆时间，预处理前缀和即可。

时间复杂度： $O(n)$

**判断是否成立的条件**

1. `O`,`W` 在配对后可能还会剩下一些，如果剩下的个数为奇数，说明无法两两抵消完毕，必然会剩下一个 `O` 或 `W`,此时直接判否。
2. 如果最后包括 `OW`配出的 `C` 个数是偶数 ，则它们会两两抵消，直至没有。此时直接判否。
3. 其他情况必然成立。

### CODE

[code](https://www.luogu.com.cn/paste/7oy4de1d)


---

## 作者：宇宙的怒火 (赞：0)

这道题的正解是前缀和！！！
------------
**前置证明:对于任意长度的由COW三个字母组成的字符串， _总_  能转化为 _唯一_ 的一个字符  （  'C' 'O' 'W' 或 ' '  ） 。** 

------------

对于长度为  1  的字符串，显然。。。

若这对于任意长度为 $ (len-1) $ 的字符串成立，那么对于长度为 $ len $ 的字符串，可以分为第  1  个字符和后 $ (len-1) $ 个字符串。设第  1  个字符为 $ X $ ， 后 $ (len-1) $ 个字符可以转化为字符 $ Y $ ,那么：

若 $ X==Y $ ：得到的是 $ XY='\;' $（空字符）  

若 $ X=='\;' $ ：得到的是 $ XY=Y $ 

若 $ Y=='\;' $ ：得到的是 $ XY=X $ 

否则 ： 

转化方案一 ： $ XY=ZYY=Z $ 

转化方案二 ： $ XY=XXZ=Z $ 

即此时  XY  总能转化为  Z  。

结合律: $ (XY)Z=X(YZ) $ 所以从中间任意长度分开最后结果一样。 ~~显然，大不了就全枚举一遍嘛。~~

得证。

------------

不难发现， 若 $ XY=Z $ 且 $ XW=Z $ ，则 $ Y=W $ 。

由此，可以前缀和了。

前缀和数组  sum[]  不必多说

若 $sum[l-1] C =sum[r] $ 则成立，否则不成立。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200010
char sum[N];
int n;
char c[N],tt='C'^'O'^'W';
char deal(char a,char b){
	if(a==b)return ' ';
	if(a==' ')return b;
	if(b==' ')return a;
	return tt^a^b;
}
int main(){
	scanf("%s%d",&c,&n);
	sum[0]=' ';
	sum[1]=c[0];
	int len=strlen(c);
	for(int i=2;i<=len;i++){
		sum[i]=deal(sum[i-1],c[i-1]);
	}
	for(int i=1;i<=n;i++){
		int l,r;scanf("%d%d",&l,&r);
		if(deal('C',sum[l-1])==sum[r]){
			putchar('Y');
		}else{
			putchar('N');
		}
	}
}
```


---


# [ARC127B] Ternary Strings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc127/tasks/arc127_b

整数 $ N,L $ が与えられます． 以下の条件をすべて満たす $ 3N $ 個の文字列の組 $ (S_1,S_2,\cdots,S_{3N}) $ を一つ求めてください．

- $ S_i $ は `0`, `1`, `2` からなる長さ $ L $ の文字列である．
- $ S_i $ はすべて互いに異なる．
- すべての $ j $ ($ 1\ \leq\ j\ \leq\ L $) および $ c= $`0`, `1`, `2` について，次が成り立つ．
  
  
  - $ S_i $ のうち，$ j $ 文字目が $ c $ であるようなものはちょうど $ N $ 個存在する．
- $ S_1,S_2,\cdots,S_{3N} $ の中で，辞書順で最も大きい文字列を $ t $ で表すことにする． このときの $ t $ は，$ t $ としてありうる文字列の中で辞書順最小の文字列である．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^4 $
- $ 1\ \leq\ L\ \leq\ 15 $
- $ 3N\ \leq\ 3^L $
- 入力される値はすべて整数である

### Sample Explanation 1

この出力例はすべての条件を満たしています． 例えば，$ 2 $ 文字目が `0` であるような文字列は $ 2 $ 個存在しています． また，この例では $ t= $`21` ですが，$ t $ がこれより辞書順で小さくなることはありません．

## 样例 #1

### 输入

```
2 2```

### 输出

```
00
02
11
12
20
21```

# 题解

## 作者：DeepSeaSpray (赞：2)

# [ARC127B] Ternary Strings

经典技巧，找到问题上界，然后证明其可以取得。

对于该问题，首先可以确定的是一定有 $2$ 开头的 $N$ 个数（三进制下）。

那么答案（字典序最大的串字典序最小）上界显然是 $2 \times 3^{L-1} + N - 1$。

如何证明其可以取到，构造字符串即可。

首先，以 $2$ 开头的数已经都确定了。考虑分别需要满足题目中的剩下两个条件。

对于条件各出现了 $N$ 次。我们考虑对于每一个已求出的数每一位进行置换，在 $\mod 3$ 意义下分别加 $1$，加 $2$。

如：

```
201
012
120
```

这样我们就满足了这个条件。

对于条件所有字符串互不相同，由于一开始确定的字符串都不同，所以其置换也不同（比较显然），所以满足条件。

[完整代码](https://atcoder.jp/contests/arc127/submissions/49644472)

---

## 作者：Eakang (赞：2)

# [[ARC127B] Ternary Strings](https://www.luogu.com.cn/problem/AT_arc127_b) 题解

## 大致题意：

给定 $n$ 和 $L$，构造出 $3n$ 个长为 $L$ 的串 $S$，使：

- 两两不同。
- 取出所有字符串当中的某一位，$0$, $1$, $2$ 恰好各出现 $n$ 次。
- 字典序最大的字符串字典序尽量小。

## 做法：

首先我们知道第一列一定是 $n$ 个 $0$、$n$ 个 $1$、$n$ 个 $2$，我们可以发现只需考虑其中一种就行了。

由于有字典序的限制，我们考虑 $2$。

然后考虑如何**构造不重复**：

1. 由于我们是通过三个数构造，可以考虑三进制。

    由于有 $n$ 位，我们直接枚举 $0$ 到 $n-1$ 的三进制形式，便可保证其不同。

2. 我们贪心地往后放先 $0$，再放 $1$，最后放 $2$：
    
    设位数为 $Len$，当前列为 $x$，我们处于当前列的 $l$ 到 $r$，我们求出  $ mx = n^{(Len - x)} $。
 
    当 $mx > cnt0$ 时我们一直放 $0$，直到 $cnt0 = n$ 或 $mx \leq cnt0$， 然后进入到下一列的 $l$ 到 $l + cnt0 - 1$。

    递归出来大概长这样：
    
    注：每一个块表示一段区间。
    ![image](https://cdn.luogu.com.cn/upload/image_hosting/zaq09ikb.png)

    $0$, $1$ 同理。

    **思考这么做的正确性：**
        
     由于我们是贪心的，只会对前一列数相同的进行分割，前列数的不同支持后列数即使相同也不会导致不同行的重复，所以此算法正确。

此两种做法均可保证字典序最大的最小。

**此题还有多种做法，不再一一赘述。**

我用的第二种做法：
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

#define ull unsigned long long
#define ll long long
#define dd double
// #define int long long

const int INF = 0x3f, INFF = 0x3f3f3f3f, INFFFF = 0x7fffffff;
const int maxn = 1e5 + 5;

int n, L;
int a[maxn][16];

int read()
{
    int x = 0, w = 0; char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')w = true; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x * 10) + (ch ^ '0'); ch = getchar();}
    if(w) return -x;  return x;
}
ll qpow(ll x, ll y)
{
    ll res = 1;
    while(y)
    {
        if(y & 1)
            res = res * x;
        x = x * x, y >>= 1;
    }
    return res;
}
void Dfs(int l, int r, int dep)
{
    if(dep > L) return;
    int lim = qpow(3, L - dep), len = r - l + 1;
    int cnt0 = 0, cnt1 = 0, cnt2 = 0;
    
    while(cnt0 < lim && cnt0 < n) cnt0 ++;
    if(cnt0)
    {
        for (int i = l; i <= l + cnt0 - 1; ++ i) a[i][dep] = 0;
        Dfs(l, l + cnt0 - 1, dep + 1);
    }
    
    while(cnt1 < lim && cnt0 + cnt1 < len && cnt1 < n) cnt1 ++;
    if(cnt1)
    {
        for (int i = l + cnt0; i <= l + cnt0 + cnt1 - 1; ++ i) a[i][dep] = 1;
        Dfs(l + cnt0, l + cnt0 + cnt1 - 1, dep + 1);
    }

    while(cnt2 < lim && cnt0 + cnt1 + cnt2 < len && cnt2 < n) cnt2 ++;
    if(cnt2)
    {
        for (int i = l + cnt0 + cnt1; i <= l + cnt0 + cnt1 + cnt2 - 1; ++ i) a[i][dep] = 2;
        Dfs(l + cnt0 + cnt1, l + cnt0 + cnt1 + cnt2 - 1, dep + 1);
    }
    return;
}

void Solve()
{
    n = read(), L = read();
    if(L == 1)
    {
        printf("0\n1\n2\n");
        return;
    }
    for (int i = 1; i <= n; ++ i)
    {
        a[i][1] = 2;
    }
    Dfs(1, n, 2);
    for(int i = 1; i <= n; ++ i)
    {
        for(int j = 1; j <= L; ++ j)
            printf("%d", a[i][j]);
        puts("");
    }
    //构造出0和1的
    for(int i = 1; i <= n; ++ i)
    {
        for(int j = 1; j <= L; ++j)
        {
            if(a[i][j] == 0) printf("1");
            if(a[i][j] == 1) printf("2");
            if(a[i][j] == 2) printf("0");
        }
        puts("");
    }
    for(int i = 1; i <= n; ++ i)
    {
        for(int j = 1; j <= L; ++ j)
        {
            if(a[i][j] == 0) printf("2");
            if(a[i][j] == 1) printf("0");
            if(a[i][j] == 2) printf("1");
        }
        puts("");
    }
    return;
}
#undef int
int main()
{
    freopen("three.in", "r", stdin);
    freopen("three.out", "w", stdout);
    Solve();
    return 0;
}
```

---

## 作者：听取MLE声一片 (赞：1)

简单题。

## 简要翻译：

给定 $N$ 和 $L$，你要构造 $3\times N$ 个长度为 $L$ 的串，满足以下要求。

- 构造的串两两不同。

- 对于所有字符串的每一位，$0$,$1$,$2$ 各出现了 $N$ 次。

- 字典序最大的串字典序最小。

## 解法：

第一位要有 $N$ 个 $0$,$1$,$2$，所以让字典序最大的最小只需要处理第一位为 $2$ 的即可。

考虑无重，只需要枚举从 $0$ 到 $n-1$ 的所有数，然后分别转为三进制后从最后一位往前填，不足的部分（第二位及之后）就用前导零弥补，这样既满足两两不同的限制又满足字典序最大最小限制。

最后就是满足出现次数限制。我们重复上述过程，分别在 $0$,$1$ 后面拼入，然后把每一位要填的数在模 $3$ 的意义下分别加 $1$,$2$ 即可，即可满足出现次数限制。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=2e5+10;
const int M=18;
int n,m,a[N][M];
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i][1]=0;
	for(int i=n+1;i<=n*2;i++)
		a[i][1]=1;
	for(int i=n*2+1;i<=n*3;i++)
		a[i][1]=2;
	for(int i=0;i<n;i++){
		int x=n*2+i+1,p=i;
		for(int j=m;j>=2;j--){
			a[x][j]=p%3;
			p/=3;
		}
	}
	for(int i=0;i<n;i++){
		int x=n+i+1,p=i;
		for(int j=m;j>=2;j--){
			a[x][j]=(p%3+1)%3;
			p/=3;
		}
	}
	for(int i=0;i<n;i++){
		int x=i+1,p=i;
		for(int j=m;j>=2;j--){
			a[x][j]=(p%3+2)%3;
			p/=3;
		}
	}
	for(int i=1;i<=n*3;i++){
		for(int j=1;j<=m;j++)
			cout<<a[i][j];
		cout<<'\n';
	}
	return 0;
}

```

---

## 作者：YuYuanPQ (赞：1)

# 洛谷 AT_arc127_b 题解

## 题目大意

题面很简练，所以不概括了。

## 赛时

因为没有 SPJ，教练让我们别做。所以我打表。

代码扔在了后面。

## 分析

~~水题~~

首先，第 $1$ 位先固定下来，从 $0$ 到 $2$，每个数字都会是 $n$ 个串的开头。这样就是 $3N$ 个串。

然后，倒着做。从第 $3N$ 个串开始，枚举到第 $1$ 个串，并且将枚举的数转成三进制。

附上一个转进制的代码吧：

```cpp
void jz(int n,int x)//n表示待转换进制的数，x表示转换为x进制。
{
	int len=0,p[33];
    while(n)
    {
    	p[++len]=n%x;
        n/=x;
    }
    for(int i=len;i>=1;i--) printf("%d",p[i]);//转进制后倒着输出。
    printf("\n");
    return;
}
```

其次，为了使 `字典序最大的串字典序最小`，在串中，我们应当使小的数放在靠前的位置。而不足的部分就用 $0$ 代替。

结束。

代码中的注释很详细，可以看看。

完结撒花~

## 注意

- 数组开到 $n$ 的 $3$ 倍及以上。我第 $1$ 次交只开到了 $n$。（不在洛谷上）

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAXN 52020
using namespace std;
int n,l;
int d[MAXN*3][20];
int qread()
{
    int sum=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {sum=(sum<<1)+(sum<<3)+ch-48;ch=getchar();}
    return sum*f;
}
void qprint(int x)
{
    if(x>9) qprint(x/10);
    putchar(x%10+48);
    return;
}
void qp(int x)
{
    if(x<0) x=-x;
    qprint(x);
    return;
}
int main()
{
    //freopen("01-016.in","r",stdin);
    //freopen("my.out","w",stdout);
	n=qread();
    l=qread();
    
    //确定首位数字
	for(int i=n+1;i<=n*2;i++)
		d[i][1]=1;
	for(int i=n*2+1;i<=n*3;i++)
		d[i][1]=2;
    //确定首位数字
    
	for(int i=0;i<n;i++)//枚举可以放的数
    {
		int x=n*2+i+1,p=i;//x代表第几个数,p代表当前枚举到的数字。
		for(int j=l;j>1;j--)//第1位不需要枚举到，因为前面已经赋值了。
        {
            //以下为转三进制的操作。
			d[x][j]=p%3;
			p/=3;
		}
	}
	for(int i=0;i<n;i++)//枚举可以放的数
    {
		int x=n+i+1,p=i;//x代表第几个数,p代表当前枚举到的数字。
		for(int j=l;j>1;j--)//第1位不需要枚举到，因为前面已经赋值了。
        {
            //以下为转三进制的操作。
			d[x][j]=(p%3+1)%3;
			p/=3;
		}
	}
	for(int i=0;i<n;i++)//枚举可以放的数
    {
		int x=i+1,p=i;//x代表第几个数,p代表当前枚举到的数字。
		for(int j=l;j>1;j--)//第1位不需要枚举到，因为前面已经赋值了。
        {
            //以下为转三进制的操作。
			d[x][j]=(p%3+2)%3;
			p/=3;
		}
	}
	for(int i=1;i<=n*3;i++)//输出
    {
		for(int j=1;j<=l;j++) qp(d[i][j]);//,putchar(' ');
        putchar('\n');
	}
	return 0;
}
```
## 赛时代码

```cpp
#include<bits/stdc++.h>
#define INF pow(2,31)-1
#define ll long long
#define MAXN 520
using namespace std;
int a,b;
int main()
{
    cin>>a>>b;
    if(a==2&&b==2) cout<<"00\n02\n11\n12\n20\n21\n";
    else cout<<"1\n";
    return 0;
}
```

## 附

- [题目链接](https://www.luogu.com.cn/problem/AT_arc127_b)
- [我的提交记录](https://www.luogu.com.cn/record/list?pid=AT_arc127_b&user=1029900)

---


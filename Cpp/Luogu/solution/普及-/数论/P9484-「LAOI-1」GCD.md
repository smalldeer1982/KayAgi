# 「LAOI-1」GCD

## 题目描述

一张图有 $n$ 个节点，编号为 $1,2,3,\dots,n$。其中 $i$ 号节点会向 $j$ 号节点连一条边权为 $|i-j|$ 的无向边，当且仅当 $\gcd(i,j)=i,\operatorname{lcm}(i,j)=j$ 时连边。现询问 $q$ 次，每次询问求 $x$ 到 $y$ 的最短路径。

## 说明/提示

注意时空限制，本题不捆绑。

对于 $40\%$ 的数据，$T,n,q\le100$;

对于 $100\%$ 的数据，$1\le T\le10^6$，$1\le n,q\le10^6$，$1\le x,y\le n$，$1\le \sum n,\sum q\le10^6$。

**请使用更快的 IO 方式**。

updata on 2024/8/8：

时限上调到 1000ms。/yun

## 样例 #1

### 输入

```
1
6 4
1 4
3 5
2 5
2 4```

### 输出

```
3
6
5
2```

# 题解

## 作者：Coffins (赞：19)

## 前言

赛时 5min 切了，然后就没继续比赛了。

这题目其实就是纯白给签到题~~然而我第一次提交被卡了输入~~

## 解法

考虑条件 $\gcd(i,j)=i,\operatorname{lcm} (i,j)=j$ ，显然等价于 $i|j$，也就是说当一个数为一个数的倍数时，两个数之间有边。

然后考虑如何最小化路径。

感性上理解是把 $x$，$y$ 都跳到 $\gcd(x,y)$ 处，那么如何证明？

（不妨设 $y\le x$）

考虑把 $x$ 往 $y$ 走，那么 $x$ 一定要先到达一个  $y$ 的因数/倍数 $z$。

### 情况一：倍数

把 $x$ 加倍后至少走了 $x\ge \gcd(x,y)$ 步，所以一定不比往 $\gcd(x,y)$ 走优。

### 情况二：因数

$z$ 比 $\gcd(x,y)$ 小的话显然不比向 $\gcd(x,y)$ 走优；
$z$ 比 $\gcd(x,y)$ 大的话 $z$ 中一定有 $y$ 不需要的因子，最终还要除去，而 $x$ 已经加倍过，出去后走的就要比原来远，故也不如直接走到 $\gcd(x,y)$ 优。

综上，答案为 $x+y-2\gcd(x,y)$。

## Code

```cpp
#include<bits/stdc++.h>
int t,n,q;
int x,y;
int gcd(int a,int b)
{
	while(b^=a^=b^=a%=b);
	return a;
}
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>q;
		for(int i=1;i<=q;i++)
		{
			cin>>x>>y;
			cout<<x+y-2*gcd(x,y)<<'\n';
		}
	 } 
	return 0;
}

```

---

## 作者：zzx0102 (赞：10)

# 官方题解

首先，令 $g=\gcd(i,j)$。

那么 $i$ 到 $g$ 有 $i-g$ 的边，$j$ 到 $g$ 也有一条 $j-g$ 的边。

那么 $i+j-2g$ 是其中一种方案。

此外，按照 $\gcd$ 的定义，如果 $i$ 到更小的公约数 $g',g'<g$，那么 $i+j-2g'>i+j-2g$，更加不优。

所以答案是 $i+j-2g$。

当然也可能是 $2\operatorname{lcm}(i,j)-i-j$，但是这样一定不优。

证明：

不妨设 $i\le j$。

令 $g=\gcd(i,j),l=\operatorname{lcm}(i,j)$。

$$i+j-2g\le 2l-i-j$$

$$2i+2j\le 2g+2l$$

$$i+j\le l+g$$

又因为 $ij=gl$，并且 $l\ge j,g\le i$。

又因为两个数积相等，差越大和越大，所以上式成立。

考虑 $\forall i,j\ge 0,j\ge i, i+j\ge 2\sqrt {ij}$，所以两个数积相等，$j-i$ 越小，$i+j$ 越大。

所以 $i+j\le l+g$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define gc getchar
#define pc putchar
#define W while
#define I inline
namespace SlowIO{
    I int read() {
        int x = 0, f = 1; char ch = gc();
        W(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
        W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
        return x * f;
    }
    I void Read(int &x) {x = read();}
    I void Read(int &x, int &y) {Read(x), Read(y);}
    I void write(int x) {
        if(x < 0) pc('-'), x = -x;
        if(x > 9) write(x / 10);
        pc(x % 10 + '0');
    }
    I void writeln(int x) {write(x); pc('\n');}
} using namespace SlowIO;
signed main() {
    int t; Read(t);
    while(t--) {
        int n, q; Read(n, q); 
        while(q--) {
            int a, b; Read(a, b); int g = __gcd(a, b);
            writeln(a + b - 2 * g);
        }
    }
    return 0;
}
```

---


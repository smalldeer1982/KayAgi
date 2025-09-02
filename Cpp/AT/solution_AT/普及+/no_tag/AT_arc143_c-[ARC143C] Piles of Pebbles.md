# [ARC143C] Piles of Pebbles

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc143/tasks/arc143_c

小石の山が $ N $ 個あります．最初，$ i $ 番目の山には $ A_i $ 個の小石があります．

これらを用いて，高橋君と青木君がゲームをします． 高橋君から始めて，交互に次の操作を行い，操作を行えなくなった方が負けとなります．

- 山を $ 1 $ つ以上選び，選んだそれぞれの山から，高橋君の操作の場合は $ X $ 個ずつ，青木君の操作の場合は $ Y $ 個ずつ小石を取り除く． ただし，小石の個数が足りない山を選ぶことはできない．

二人が最適に行動したとき，どちらがゲームに勝つかを求めてください.

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ X,\ Y\ \leq\ 10^9 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $

### Sample Explanation 1

例えば，以下のようなゲームの進行が考えられます． - 高橋君が両方の山から石を $ 1 $ つ取り除く． - 青木君が $ 1 $ 番目の山から石を $ 1 $ つ取り除く． - 高橋君が $ 1 $ 番目の山から石を $ 1 $ つ取り除く． - 青木君が $ 2 $ 番目の山から石を $ 1 $ つ取り除く． - 高橋君が $ 2 $ 番目の山から石を $ 1 $ つ取り除く． 青木君がどのように操作を行っても高橋君が勝つことができるので，答えは `First` です．

## 样例 #1

### 输入

```
2 1 1
3 3```

### 输出

```
First```

## 样例 #2

### 输入

```
2 1 2
3 3```

### 输出

```
Second```

# 题解

## 作者：AIskeleton (赞：7)

[博客园查看](https://www.cnblogs.com/AIskeleton/p/17008461.html)

$\text{Difficulty:} \color{Blue}{1697}$

### description

给定 $n$ 堆石子，两个人轮流取，不能操作者败。

每次取选择若干堆石子，先手取走 $x$ 个，后手取走 $y$ 个。

判断胜负。

### solution

首先考虑一堆石子 $a$ 的情况。

显然先将 $a$ 对 $x+y$ 取模，设 $b=a\bmod (x+y)$。

不难发现，如果 $b\ge x$，先手必赢，否则必输。

考虑 $n$ 堆石子的情况。

首先可以想到，如果每一堆石子数对 $x+y$ 取模得到的数都 $< x$，那么先手必败，此时后手只要重复先手的操作即可。

然后考虑分讨 $x,y$ 的大小关系。

- $x \le y$

  此时先手必胜。

  因为存在至少一堆石子，其数量 $a$ 满足 $a \bmod(x+y) \le x \le y$，先手可以在第一步取满足条件的堆，之后模仿后手的操作，就能让后手最后无法操作。

- $x>y$

  此时需要分讨(AT 数据水，这里直接输出后手必胜都能过)。

  考虑特殊情况。

  - 如果存在至少一堆石子，其数量 $a$ 满足 $y\le a \bmod (x+y)<x$，则后手必胜。

    此时后手可以选择模仿先手的操作，所有堆满足数量 $<(x+y)$ 之后，因为 $y<x$，所有先手可以操作的堆，后手都可以操作，所以后手必胜。

  - 反之，先手必胜。

  

### code

```c++
#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n,x,y;
  cin>>n>>x>>y;

  vector<int>a(n);
  bool f=0;
  for(int &i:a){
    cin>>i;
    i%=(x+y);
    f|=(i>=x);
  }

  if(!f){
    cout<<"Second\n";
  }
  else if(x<=y){
    cout<<"First\n";
  }
  else{
    f=0;
    for(int i:a){
      f|=(i>=y&&i<x);
    }
    if(!f){
      cout<<"First\n";
    }
    else{
      cout<<"Second\n";
    }
  }
  return 0;
}
```



---

## 作者：TempestMiku (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/AT_arc143_c)

## 一、题目大意

$n$ 堆石头，两个人轮流取，先手**只**能取 $x$ 个，后手**只**能取 $y$ 个。
最后谁不能操作谁就输。在最优策略下问先手赢还是后手赢。

## 二、思路

我们可以发现在每堆石头 $a_i$ 和在模 $x+y$ 意义下是相同的，因为假设原来取的顺序是 $x,y,x$ ，模完之后变成 $x$ ，本来的游戏一定会转化成这种局面。

假设 $op_i$ 为 $a_i$ 模 $x+y$。

- 当所有 $op_i$ 都小于 $x$ 的时候：

这时候因为先手必须取 $x$ 个，所以这时候先手取不了，后手就必赢。

- 当不是所有 $op_i$ 都小于 $x$ 的时候：


	如果存在 $x\le y$ 的时候，那么先手必赢，因为这时候先手可以取一次 $x$ ，后手就不能再取了。
    
    
   如果存在 $x>y$ 的时候，如果存在 $y\le op_i<x$ ，那么后手必赢，这时候因为先手必须取 $x$ 个，所以这时候先手取不了，后手就必赢。
   
   如果没有上面情况就是先手必赢。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Testify{
    inline int read(){
        int f(1),x(0);
        char ch=getchar();
        for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
        for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
        return f*x;
    }
    inline void Write(int x){
        if(x>9) Write(x/10);
        putchar(x%10+48);
    }
    inline void write(int x){
        if(x<0) putchar('-'),x=-x;
        Write(x);
        putchar('\n');
    }
}
using namespace Testify;
int n,m,Tempestissimo(0);
int x,y;
const int N=2e5+5;
bool flag=false;
int a[N];
signed main(void){
    n=read(),x=read(),y=read();
    for(register int i=1;i<=n;i++){
        a[i]=read();
        a[i]%=(x+y);
        if(a[i]>=x){
            flag=true;
        }
    }
    if(!flag){
        puts("Second");
        return 0;
    }
    if(x<=y){
        puts("First");
        return 0;
    }
    flag=false;
    for(register int i=1;i<=n;i++){
        if(a[i]<x&&a[i]>=y){
            // flag=true;
            puts("Second");
            return 0;
        }
    }
        puts("First");
    return 0;
}
```


---

## 作者：DengDuck (赞：2)

我没场切纯属唐氏。

我们设 $b_i=a_i\bmod (x+y)$。

情况一：如果 ${b_i}<x(1\leq i\leq n)$。

先手必败。

那么先手怎么操作，后手都可以操作相同的石子，这相当于不断地选择一些棋子减去 $x+y$，最后显然所有的棋子都会变成 $b_i$，然后先手无法操作。

情况二：如果存在 ${b_i}\geq x(1\leq i\leq n)$，$x\leq y$。

先手必胜。

先手可以选择所有的 $i(b_i\geq x)$ 操作，之后转换为情况一，相当于扔给了对面一个先手必败的局面。

情况三：如果存在 ${b_i}\geq x(1\leq i\leq n)$，$x>y$。

想办法转换成上面的情况。

怎么转换成全部 $b_i<y$ 情况呢？

对于所有 $b_i\geq y$，如果 $b_i\in[y,x]$，减了 $x$ 之后会变成 $b_i\in[2y,y+x]$，这时依旧有 $b_i\leq y$，对于后手相当于情况二，那么先手就输了。

如果不存在的话，就是所有的 $b_i\geq y$ 都满足 $b_i\geq x$，这时选中它们减去 $x$ 即可，先手必胜。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=3e5+5;
LL n,x,y,a[N];
int main()
{
	cin>>n>>x>>y;
	LL mx=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		a[i]%=x+y;
		mx=max(a[i],mx);
	}
	if(mx<x)
	{
		puts("Second");
		return 0;
	}
	if(x<=y)
	{
		puts("First");
		return 0;
	}
	LL flg=0;
	for(int i=1;i<=n;i++)
	{
		flg|=(a[i]<x&&a[i]>=y);
	}
	if(!flg)puts("First");
	else puts("Second");
}
```

---

## 作者：LiveZoom (赞：2)

## Description

[link](https://www.luogu.com.cn/problem/AT_arc143_c)

## Solution

首先设 $r_i=a_i\bmod (x+y)$。

如果所有的 $r_i$ 都小于 $x$，那么后手只要选先手选的堆即可。

否则，如果 $x\leq y$，则必定会有至少一个 $r_i$，使得 $x\leq r_i<x+y$。那么先手只要第一次选这些 $r_i$ 操作，然后每次重复后手操作即可。

如果 $x>y$ 且存在一个 $r_i$ 满足 $y\leq r_i<x$，那么后手只要每次重复先手操作即可。

如果 $x>y$ 且不存在 $r_i$ 满足 $y\leq r_i<x$，那么先手先把所有 $r_i\geq x$ 的选了，然后每次重复后手操作即可。

时间复杂度：$O(n)$。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2e5 + 5;

int n, x, y;
int a[kMaxN], r[kMaxN];

bool check1() {
  for (int i = 1; i <= n; ++i) {
    if (r[i] >= x)
      return 0;
  }
  return 1;
}

bool check2() {
  for (int i = 1; i <= n; ++i) {
    if (r[i] >= y && r[i] < x)
      return 1;
  }
  return 0;
}

int main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> x >> y;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    r[i] = a[i] % (x + y);
  }
  if (check1()) {
    cout << "Second\n";
    return 0;
  }
  if (x <= y) {
    cout << "First\n";
  } else {
    if (check2()) {
      cout << "Second\n";
    } else {
      cout << "First\n";
    }
  }
  return 0;
}
```

---

## 作者：Hanzelic (赞：2)

# [原题链接](https://www.luogu.com.cn/problem/AT_arc143_c)    
假设一堆石子有 $a_i$ 个石子，那么对 $a_i$ 个石子适用的策略对 $a_i\bmod x+y$ 是同样适用的，因为如果 $a_i\ge x+y$，当第一个人取走 $x$ 个石子后，第二个人可以跟随第一个人取走这一堆石子的 $y$ 个，此时又轮到第一个人来取走石子，所以我们可以把每一个给出的 $a_i$ 对 $x+y$ 取模再进行计算。  
#### 接下来考虑如何判断胜负  
首先考虑一堆石子的情况，显然可以得知，当 $a_i\ge x$ 的时候，先手必赢，反之后手必赢。   
然后开始考虑 $n$ 堆石子的情况，有一个显然成立的猜测：当所有石子的个数都小于 $x$ 的时候先手必输。  
之后就开始判断 $x$ 和 $y$ 的大小，  
**如果 $x\le y$ 的时候先手必赢**，这里当时我纠结了好久，最后发现是我读错题了，这两个人是可以一次取很多堆石子的，并且此时肯定有至少一堆石子个数会大于 $x$ ，不成立的情况上面的特判可以排除，这是第一个人可以把所有大于 $x$ 的石子堆全都取走 $x$ ，剩下的石子个数全都是小于 $y$ 的。  
**如果 $x> y$ 的时候就需要进行判断了**，当存在石子个数大于等于 $y$ 且小于 $x$ 的时候先手必输，反之先手必赢。因为这种情况下，第二个人可以先把符合情况的石子置之不理，第一个人能采的石子堆第二个人都可以采，这样等到最后必是先手输。  
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y;
int a[200005];
bool p1;
int main(){
	scanf("%d%d%d",&n,&x,&y);
	for(int q=1;q<=n;q++){
		scanf("%d",&a[q]);
		a[q]%=(x+y);
		if(a[q]>=x)p1=1;
	}
	if(!p1){
		printf("Second\n");
		return 0;
	}
	else if(x<=y){
		printf("First\n");
		return 0;
	}
	else{
		for(int q=1;q<=n;q++){
			if(a[q]>=y&&a[q]<x){
				printf("Second\n");
				return 0;
			}
		}
		printf("First\n");
		return 0;
	}
}
```


---


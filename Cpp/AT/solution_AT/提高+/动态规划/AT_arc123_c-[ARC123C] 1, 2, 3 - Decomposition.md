# [ARC123C] 1, 2, 3 - Decomposition

## 题目描述

给出一个正整数 $n$ ，求 $n$ 至少可以表示为多少个 「十进制下仅含有 $1,2,3$ 的正整数」 的和？

翻译 by [_FJqwq](https://www.luogu.com.cn/user/755947)

## 样例 #1

### 输入

```
5
456
10000
123
314
91```

### 输出

```
2
4
1
2
4```

# 题解

## 作者：Shapy_UI_Tools (赞：5)

## 题意
给你一个数 $n$，你要用 $ans$ 个十进制表示中只包含 `1` `2` `3` 的数加起来得到 $n$，求最小的 $ans$。

## 解法
### 思路
我们考虑一位一位地凑，设 $x$ 为 $n$ 的十进制表示下的某一位。对于每个 $ans$，分别考虑用 $ans$ 个数能凑出来什么样的数。

以下"第 $x$ 位"表示一个数十进制表示中从左往右数的第 $x$ 位。
1. $ans=1$。显然必须 $\forall x \in [1,3]$。
2. $ans=2$。如果依照惯性思维，应当是 $\forall x \in [2,6]$，但是我们注意到，虽然题目要求所有数的每一位都只能是 `1` `2` `3`，但是实际上一个数的位数不一定与 $n$ 相同，**前导 $0$ 可以使某一位的值不受最小值的限制**。举个例子，$n=16$，显然 $n=13+3$。其中 $13$ 是两位数，但是 $3$ 是一位数，这就是为什么 $n$ 的第一位为 $1$ 但仍然可以凑出来。但是这种情况直接判断比较不方便，所以我们换个角度来看，把 $16=13+3$ 等价看作 $6=3+3$ 且 $1=1$，也就是用两个数凑出了 $n$ 的第二位，同时用一个数凑出了 $n$ 的第一位。因此，我们在判断 $n$ 是否能用 $ans$ 个数凑出来时，如果从右往左已经扫完了第 $i$ 位，此时从第一位到第 $i-1$ 位只需用更少的数就能凑出来了，那么同样可以判断 $n$ 可以用 $ans$ 个数凑出来。
3. $ans=3$。与 $ans=2$ 同理，只不过 $x$ 的范围变成了 $[3,9]$。
4. $ans=4$。此时就有可能出现进位的情况了。如果不考虑第 $i$ 位受到第 $i+1$ 位进位的影响，那么 $n$ 需要满足 $\forall x \in [4,9] \cup [0,2]$。我们发现**如果一个数能被表示，其会不会对下一位进行进位是确定的**，换句话说就是不存在一个数既可以由四个小的数加起来直接凑出又可以由四个大的数加起来对 $10$ 取模后凑出。然后，我们发现 $3$ 是不能被表示的，因为 $1*4 \bmod 10=4$，$3*4 \bmod 10=2$。但是如果第 $i+1$ 位向第 $x$ 位进位了，则可以用四个 $3$ 加上一个进位的 $1$ 表示出来 $3$。与此同时，我们还要考虑进位带来的副作用，也就是如果存在进位，我们是**不能表示出无进位的最小值** $4$ 的，因为就算四个数全取最小的 $1$，它们再加上进位的 $1$ 后就也到 $5$ 了。
5. $ans=5$。此时我们不考虑进位时能表示的数就已经是所有数了。而且进位不会产生副作用，也就是我们**不会**因为进位而无法表示无进位的最小值 $5$，因为就算进位了我们也可以先凑出 $4$ 然后再加上进位的 $1$ 变成 $5$。因此，任何 $n$ 都可以由不超过五个数凑出来。

### 实现
这个时候我们就可以写出很优美的代码了。用五个函数分别判断五种情况，判断 $ans=x$ 时，按照 2 中的说法，去调用 $ans=x-1$ 的函数来判断。因为判断每个 $ans$ 都要循环 $\log n$ 次，而每次循环还会调用之前的函数，所以极限时间复杂度是 $O(T\log^5n)$，但是常数过小，而且就算刻意构造数据，跑起来也完全不可能摸到这个复杂度的尾巴，1ms 就能跑完。

## 代码
[提交记录](https://atcoder.jp/contests/arc123/submissions/46420299)
```cpp
#include <iostream>
using namespace std;

int T;

long long a;

bool one(long long x) {
	while (x != 0) {
		if (x % 10 < 1 || x % 10 > 3) return false;
		x /= 10;
	}
	return true;
}

bool two(long long x) {
	while (x != 0) {
		if (one(x)) return true;
		if (x % 10 < 2 || x % 10 > 6) return false;
		x /= 10;
	}
	return true;
}

bool three(long long x) {
	while (x != 0) {
		if (two(x)) return true;
		if (x % 10 < 3) return false;
		x /= 10;
	}
	return true;
}

bool four(long long x) {
	bool f = false;//是否从上一位进位过来
	while (x != 0) {
		if (three(x - f)) return true;
		if (x % 10 <= 2) f = true;
		else if (x % 10 == 3) {
			if (f == 0) return false;
		}
		else if (x % 10 == 4 && f) return false;
		else f = false;
		x /= 10;
	}
	return true;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%lld", &a);
		if (one(a)) printf("1\n");
		else if (two(a)) printf("2\n");
		else if (three(a)) printf("3\n");
		else if (four(a)) printf("4\n");
		else printf("5\n");
	}
}
```

---

## 作者：Erica_N_Contina (赞：4)

# [ARC123C] 1, 2, 3 - Decomposition



## 思路

本题要求我们求出**至少**可以表示为多少个「十进制下仅含有 $1,2,3$ 的正整数」的和，我们首先要推出一个结论。

以下我们称「十进制下仅含有 $1,2,3$ 的正整数」为「$123$ 数」

我们观察到对于任意的正整数 $n$，它每一位可能由 $0\sim9 $ 组成。如果我们只有一个 $123$ 数，那么每一位只能是 $[1,3]$，如果有 $2$ 个，则每一位可以是 $[2,6]$（我们要注意这里不是 $[1,6]$ 因为 $123$ 数每一位至少是 $1$，这也解释了为什么 $4$ 个 $123$ 数不能构成所有正整数）……如果有 $4$ 个，那么每一位可以是 $[4,12]$，考虑进位，则是 $[0,2][4,9]$，当我们一旦有 $5$ 个 $123$ 数时，我们就很显然可以构成任意正整数了。

所以本题的答案最大值即是 $5$。



接下来我们考虑本题的解法。给定一个正整数 $n$，我们从最高位开始逐位考虑，贪心地记录到第 $i$ 位最少需要几个 $123$	 数，并且记忆化存储在 map 中。

我们采用 dfs 递归，从最低位进入，先 dfs 到最高位，然后从最高位返回，考虑当前第 $i$ 位的数字 $n_i$，根据上文我们推出的每一位的范围与 $123$ 数的个数的关系计算出当前需要的 $123$ 数的最小值，直到考虑完整个数。

```C++
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
const int N=1e5+5;
using namespace std;

int T,n,a,b,c,qzh[N];

map <int,int> mp;

int dfs(int n){
	if(!n)return 0;
	if(mp[n])return mp[n];//记忆化
	
	int a=n/10,b=n%10;
	//从最高位开始逐位考虑(从代码看上去是从个位开始的,但实际上因为是dfs递归所以实际上是从最高位开始的)
	
	if(1<=b&&b<=3&&dfs(a)<=1)return mp[n]=1;
	if(2<=b&&b<=6&&dfs(a)<=2)return mp[n]=2;
	if(3<=b&&b<=9&&dfs(a)<=3)return mp[n]=3;
	if(4<=b&&b<=9&&dfs(a)<=4)return mp[n]=4;
	if(0<=b&&b<=2&&dfs(a-1)<=4)return mp[n]=4;//考虑进位
	return mp[n]=5;
}

signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		int ans=dfs(n);
		cout<<ans<<endl;	
	}
}

```




---

## 作者：EuphoricStar (赞：3)

从低位往高位考虑。设当前个位为 $k$，暴力搜索这一位向上进 $i$ 位，设 $\left\lfloor\frac{n}{10}\right\rfloor - i$ 的答案为 $t$。

- 若 $t > 10i + k$ 显然就不可行，因为就算个位全部填 $1$ 也不能补齐；
- 否则 $n$ 的答案就是 $\max(t, \left\lceil\frac{10i+k}{3}\right\rceil)$，取 $\max$ 是因为有可能之前不够个位至少需要数的个数，要补。

直观感觉是 $i$ 不会很大（事实上 $i \le 1$），所以这个做法跑得很快。

[code](https://atcoder.jp/contests/arc123/submissions/40964270)

---

## 作者：elbissoPtImaerD (赞：2)

考虑**枚举**答案，不妨现在要 chk $m$ 个数是否能拼成 $n$。

由于 $[1,3]$，所以在某一位其能匹配的就是 $[m+s,3m+s]$，其中 $s$ 是前一位的进位。

对于 $n$ 每一位来说，其若不能被直接匹配或者进位后匹配，则需要让 $m \gets m-1$。

这个策略容易用贪心说明最优性。

直接贪心即可，复杂度 $O(T\log_{10}n)$。

而且我们注意到 $[5+s,15+s]$ 可以覆盖全部，所以答案应 $\le 5$。

```cpp
ve<int>a;
il bool chk(int n)
{
  int s[2]{};
  for(int x:a)
  {
    for(;n;--n)
    {
      int L=n+s[0],R=3*n+s[0],l=L%10,r=R%10;
      if(x>R) return false;
      if(l>r)
      {
        if(l<=x) break;
        if(x<=r)
        {
          s[1]=1;
          break;
        }
      }
      else if(l<=x&&x<=r) break;
    }
    if(!n) return false;
    s[0]=s[1],s[1]=0;
  }
  return true;
}
il int Solve()
{
  sd string s;
  rd(s),a.resize(s.size());
  for(int i=0;i<s.size();++i) a[i]=s[i]-48;
  sd reverse(all(a));
  for(int i=1;i<=4;++i) if(chk(i)) return i;
  return 5;
}
```

[$\color{green}\checkmark$](https://atcoder.jp/contests/arc123/submissions/49334772)

---

## 作者：littlebug (赞：1)

……

## Solution

注意到可以对于每个数位分开算，比如说 $10000$ 就可以拆成 $3$ 个 $9$ 和 $1$ 个 $10$。

又注意到每个数位对应的组合具体是什么无关紧要，我们只关心它由几个 $1,2,3$ 中的数构成，于是就可以确定每个数位对应的可能个数区间（也就是由几个数加起来可以得到）。

但是，有时候是不行的，因为还要考虑进位。

不过注意到答案显然不会太大，打了个表可以发现 $[5,15]$ 的个数区间内都出现了 $5$，于是显然答案最大为 $5$。

所以直接暴力枚举答案为 $1 \sim 4$ 就行了（设为 $x$）。但是发现样例不过，为什么呢？注意到不一定每一位都要完全取到 $x$ 个，可以少取，所以考虑取 $1 \sim x$ 个，枚举即可。注意更高位就不能再多取了。

比如说 `314 = 312 + 2`，就是这样的，个位取了 $2$ 个，但十位和百位都只取了 $1$ 个。

时间复杂度看起来很小的样子，总之能过……

## Code

```cpp
int n,a[30],l[30],r[30],len;

il int ql(int x) {return x%3?x/3+1:x/3;}
il int qr(int x) {return x;}

il bool dp(int i,int x,bool op)
{
    int now=a[i]-op;
    if(i==len) return now>=0 && l[now]<=x;

    rpe(y,x,1)
    {
        if(now>0 && l[now]<=y && y<=r[now] && dp(i+1,y,0)) return 1;
        if(l[now+10]<=y && y<=r[now+10] && dp(i+1,y,1)) return 1;
    }
    
    return 0;
}

il void solve()
{
    read(n);

    len=0;
    int _n=n;
    while(_n) a[++len]=_n%10,_n/=10;

    int ans=5;
    rep(x,1,4) if(dp(1,x,0)) {ans=x; break;}
    write(ans,'\n');
}

il void init()
{
    rep(i,0,29) l[i]=ql(i),r[i]=qr(i);
}
```

---

华风夏韵，洛水天依！

---

## 作者：forever_nope (赞：1)

虽然题解也不少了，但是我打算具体说一下原因（感性证明。

## 思路

我们将题目中「十进制下仅含有 $1,2,3$ 的正整数」称为「好的数字」。

先考虑，一个数 $N$ 如果可以由若干个好的数字组成，那么它的形式是什么样子的。

1. 一个：每一位都只能是 $[1,3]$；
2. 两个：每一位都只能是 $[2,6]$；
3. 三个：每一位都只能是 $[3,9]$。

接下来，注意到就可能会出现进位了！我们依旧分类讨论，从高位开始：

先讨论四个的情况：

4. 当前位是 $[4,9]$，那么**有可能**这一位没有产生进位；
5. 当前位是 $[0,2]$，那么**有可能**产生了进位，即 $\{^{2+2+3+3=10}_{3+3+3+3=12}$。

然后讨论五个的情况：

6. 当前位是 $[5,9]$，那么**有可能**没有产生进位；
7. 当前位是 $[0,5]$，那么**有可能**产生了进位，即 $\{^{2+2+2+2+2=10}_{3+3+3+3+3=15}$。

然后我们注意到，任意整数都可以表示为五个好的数字相加！

所以 $\forall\mathit{ans}\le5$，我们只需要每一位都讨论这五种情况即可。

所以说就是一个记忆化搜索，比较好写。

注意到 $N\le10^{18}$，要开 long long，同时也需要用 map 存记忆的结果。

## 代码

见：<https://atcoder.jp/contests/arc123/submissions/46982307>

谢谢观看！


---

## 作者：happy_zero (赞：1)

[题目传送门。](https://www.luogu.com.cn/problem/AT_arc123_c)

注：以下记「十进制下仅含有 $1,2,3$ 的正整数」为“好的”数。

首先需要发现一个规律：任何数都可以被不超过 $5$ 个“好的”数组成。证明：$5$ 个“好的”数每一位可以组成的范围为 $[5,15]$，正好包括了 $[0,9]$（个位），而如果是 $4$ 的话则无法全部表示。

那么原问题就变成了一个判定问题：问一个数能否被 $i$ 个“好的”数相加而成？从低到高一位一位来考虑（默认加上进位）：若当前第 $j$ 位 $k$ 高于可以被表示的最高数（$3x$，$x$ 为现在仍有的数），那 $k$ 肯定不能被表示，就返回 `false`。

接下来考虑 $k$ 可以被表示的情况（也就是在 $3x$ 以内）。如果 $k$ 可以在 $x$ 以上，那么就完事大吉了，直接看下一位，否则易证进一位（如果可以的话）比舍去几个数来得更优，就像前进 $1$，这也是为什么会存在进位的原因。

一次判断的时间复杂度是 $\lg n$，所以总时间复杂度为 $O(T\lg n)$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
char s[N];
int n, a[N];
bool chk(int x) {
	int sum = x, lst = 0;
	for (int i = n; i >= 1; i--) {
		if (sum == 0 || a[i] + lst > sum * 3) return 0;
		//如果还没被表示完数但剩下的数已经为 0 了，也返回 false 
		if (a[i] - lst < sum) {
		    //能进位尽量进位 
			if (a[i] - lst + 10 <= sum * 3) lst = (a[i] + 10) / 10;
			else sum = a[i] - lst, lst = 0;
		}
		else lst = 0;//记得把进位设为 0 
	}
	return 1;
}
int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> s;//由于数很大所以用 char 输入后转 int 
		n = strlen(s);
		for (int i = 1; i <= n; i++)
			a[i] = s[i - 1] - '0';
		for (int i = 1; i <= 5; i++)
			if (chk(i)) {
				cout << i << "\n";
				break;
			}
	}
	return 0;
}
```

---

## 作者：SlyCharlotte (赞：0)

# 分析
结论：任何一个数最多不会由超过五个的 $123$ 类数组成。

暴力算每各位 check，$1/2/3/4/5$ 依次是否可以。

# 代码
```cpp
#include <map>
#include <cstdio>
using namespace std;
#define int long long
map < int, int > mp;
int T, n;

int solve( int n ) {
	if( ! n ) return 0;
	if( mp[n] ) return mp[n];
	int s = n / 10, r = n % 10;
	if( 1 <= r && r <= 3 && solve( s ) <= 1 ) return mp[n] = 1;
	if( 2 <= r && r <= 6 && solve( s ) <= 2 ) return mp[n] = 2;
	if( 3 <= r && r <= 9 && solve( s ) <= 3 ) return mp[n] = 3;
	if( 4 <= r && r <= 9 && solve( s ) <= 4 ) return mp[n] = 4;
	if( 0 <= r && r <= 2 && solve( s - 1 ) <= 4 ) return mp[n] = 4;
	return mp[n] = 5;
}

signed main() {
	scanf( "%lld", &T );
	while( T -- ) {
		scanf( "%lld", &n );
		printf( "%lld\n", solve( n ) );	
	}
	return 0;
}

```

---


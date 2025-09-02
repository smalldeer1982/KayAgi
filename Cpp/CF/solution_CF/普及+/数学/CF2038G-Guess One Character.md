# Guess One Character

## 题目描述

This is an interactive problem. You have to use flush operation right after printing each line. For example, in C++ you should use the function fflush(stdout) or cout.flush(), in Java or Kotlin — System.out.flush(), and in Python — sys.stdout.flush().

The jury has a string $ s $ consisting of characters 0 and/or 1. The length of this string is $ n $ .

You can ask the following queries:

- $ 1 $ $ t $ — "how many times does $ t $ appear in $ s $ as a contiguous substring?" Here, $ t $ should be a string consisting of characters 0 and/or 1; its length should be at least $ 1 $ and at most $ n $ . For example, if the string $ s $ is 111011 and the string $ t $ is 11, the response to the query is $ 3 $ .

You have to guess at least one character in the string $ s $ by asking no more than $ 3 $ queries. Note that giving the answer does not count as a query.

In every test and in every test case, the string $ s $ is fixed beforehand.

## 说明/提示

In the example, there are $ 3 $ test cases: 101, 11 and 10. Note that everything after the // sign is a comment that explains which line means what in the interaction. The jury program won't print these comments in the actual problem, and you shouldn't print them. The empty lines are also added for your convenience, the jury program won't print them, and your solution should not print any empty lines.

## 样例 #1

### 输入

```
3     // 3 test cases
3     // the length of the string is 3

1     // 101 occurs once

1     // guessed correctly
2     // the length of the string is 2

0     // 00 occurs zero times

0     // 0 occurs zero times

1     // guessed correctly
2     // the length of the string is 2

1     // 1 occurs once

0     // 01 occurs zero times

1     // guessed correctly```

### 输出

```
1 101 // how many times 101 occurs

0 2 0 // guess: s[2] is 0


1 00  // how many times 00 occurs

1 0   // how many times 0 occurs

0 1 1 // guess: s[1] is 1


1 1   // how many times 1 occurs

1 01  // how many times 01 occurs

0 2 0 // guess: s[2] is 0```

# 题解

## 作者：Reunite (赞：3)

考虑 $01$ 连续段，先询问 $11$ 的个数为 $a$，$1$ 的个数为 $b$，则显然，$1$ 构成了 $a-b$ 个极长连续段。如果 $b=0/n$ 则可以直接判定。否则考虑询问 $10$ 的个数为 $x$，如果 $x=a-b$，那说明每个 $1$ 连续段后面都有一段 $0$，显然 $s_n=0$，否则一定有 $x=a-b-1$，说明最后一个 $1$ 连续段之后没有 $0$ 了，显然 $s_n=1$。直接交互即可。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

int T,n;

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		int X,a,b;
		puts("1 10");
		fflush(stdout);
		scanf("%d",&X);
		puts("1 11");
		fflush(stdout);
		scanf("%d",&a);
		puts("1 1");
		fflush(stdout);
		scanf("%d",&b);
		int x1=b-a;
		if(b==0){puts("0 1 0");fflush(stdout);scanf("%d",&X);continue;}
		if(b==n){puts("0 1 1");fflush(stdout);scanf("%d",&X);continue;}
		if(x1==X){printf("0 %d 0\n",n);fflush(stdout);scanf("%d",&X);continue;}
		else printf("0 %d 1\n",n),fflush(stdout),scanf("%d",&X);;
	}

	return 0;
}
```

---

## 作者：hgcnxn (赞：2)

## CF2038G Guess One Character题解

### 题目大意

有一个被隐藏的长度为 $n$ 的 $01$ 串 $s$，每一次你可以询问一个 $01$ 串，交互库会告诉你 $s$ 中有多少连续子串为你所询问的 $01$ 串。在询问至多 $3$ 次后，你需要准确说出 $s$ 的任意一个位置上的数。

### 思路

考虑第一次询问 $1$ 并获取 $s$ 中 $1$ 的个数 $x$。  
注意到在你询问的 $01$ 串长度 $ \ge 2$ 时，$s$ 的最后一位不可能作为它的第一位出现。所以，我们可以继续询问 $11$ 与 $10$ 的个数 $y$ 与 $z$。如果 $x = y + z$，就说明 $s$ 中所有的 $1$ 均作为长度为 $2$ 的连续子串的第一位出现过，那么 $s$ 的最后一位一定为 $0$，否则 $s$ 的最后一位为 $1$。

### 代码

注意交互题的输入格式。

```
#include<bits/stdc++.h>
using namespace std;
int t,n,x,y,z,k;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		cout<<"1 1"<<endl;
		cin>>x;
		cout<<"1 11"<<endl;
		cin>>y;
		cout<<"1 10"<<endl;
		cin>>z;
		if(x==y+z)cout<<"0 "<<n<<" 0"<<endl;
		else cout<<"0 "<<n<<" 1"<<endl;
		cin>>k;
		if(k!=1)break;
	}
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：1)

太抽象了。

我们先询问 $s$ 中 $\texttt{0}$ 的数量，设输入了 $k_1$。

我们再询问 $s$ 中 $\texttt{10}$ 的数量，设输入了 $k_2$。

我们再询问 $s$ 中 $\texttt{00}$ 的数量，设输入了 $k_3$。

我们可以将询问 $\texttt{10}$ 视为有多少个 $\texttt{0}$ 前面是 $\texttt{1}$，而询问 $\texttt{00}$ 则视为有多少个 $\texttt{0}$ 前面是 $\texttt{0}$。

由于 $s_1$ 前面没有任何东西，若 $s_1=\texttt{0}$，$k_2,k_3$ 绝对不会计入 $s_1$，但此时 $k_1$ 却计入了 $s_1$，也就是说，当 $s_1=\texttt{0}$ 时，$k_2+k_3-1=k_1$。反之，当 $s_1=\texttt{1}$ 时，$k_1,k_2,k_3$ 都不会计入 $s_1$，所以 $k_2+k_3=k_1$。

---

## 作者：MournInk (赞：1)

一到很有意思的思维题。

给定一个长度为 $n$ 的 `0/1` 串，要求进行三次以内子串出现次数询问后确定串的任意一位是 `0` 还是 `1`。

不难想到，我们一定会去确定 $s_1$ 或 $s_n$ 而不是 $s_{2 \sim n - 1}$ 中的任意一位。

不难发现性质：

如果有 $a$ 个 `0`，且有 $b$ 个 `00`，那么此时共有 $a - b$ 个 `0` 的块（此处的块指由若干个连续的 `0` 组成的子串）。

> 一个简易的证明为：
>
> - 选择形成新的块：去掉两个 `0`，形成一个 `00`
> - 选择合并到前面的块：去掉一个 `0`，前面的块变长
>
> 不难发现以上两种操作的单次代价均为使块数 $-1$。

观察到，如果两个块之间没有 `1` 来间隔，那么这两个块应当合并为一个块。

进而发现：对于每一个 `0` 的块，前面都会有 `1` 来隔开。而第一个块的前面不一定会有 `1`。

此时就可以通过 `10` 的个数 $q$ 与 `0` 的块的数量 $a - b$ 来确定答案 $s_1$，如果 $q < a - b$，那么 $s_1$ 为 `0`，否则 $s_1$ 为 `1`。

注意此题为交互题，所以在输出后不要忘记 `flush`。

附代码：
~~~cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    for(cin >> t; t --; )
    {
        int n, a, b, q, d;
        cin >> n;
        cout << "1 0\n";
        cout.flush();
        cin >> a;
        cout << "1 00\n";
        cout.flush();
        cin >> b;
        cout << "1 10\n";
        cout.flush();
        cin >> q;
        if(a - b - q) cout << "0 1 0\n";
        else cout << "0 1 1\n";
        cout.flush();
        cin >> d;
    }
    return 0;
}
~~~

> 本文来自：
> ![做干净的奥赛](https://img.picgo.net/2024/11/19/950f46f6adff54912eadac7f86ab204670735f7200db90bb.png)
>
> 另附[官方题解](https://codeforces.com/contest/2038/attachments/download/28397/presentation_eng.pdf)。

---

## 作者：Engulf (赞：0)

除非 $s$ 的最后一个字符是 $1$，否则 $s$ 中的每个 $1$ 的右边一定会有一个 $0$ 或 $1$。记 $c_{t}$ 表示询问字符串 $t$ 得到的答案。如果 $c_1 = c_{10} + c_{11}$，说明最后一个字符不是 $1$，反之亦然。

```
int n;
cin >> n;

auto query = [](string s) {cout << "1 " << s << endl; int x; cin >> x; return x;};

int c1 = query("1"), c10 = query("10"), c11 = query("11");

cout << "0 " << n << " " << (c10 + c11 != c1) << endl;
int x; cin >> x;
```

---

## 作者：1234567890sjx (赞：0)

唐诗题，但是怎么把我控了接近半小时啊？？？

考虑分别询问 $1,11,10$ 的出现次数。设她们的值分别为 $a,b,c$。则显然有 $a=b+c$ 或 $a=b+c+1$。

其中若 $a=b+c+1$ 则说明存在一个 $1$ 她后面的位置既不是 $0$ 也不是 $1$，则这个 $1$ 显然在最后，可以输出 `0 n 1`，否则显然没有一个 $1$ 在最后，最后一个位置一定是 $0$，输出 `0 n 0`。询问次数为 $3$，时间复杂度为 $O(1)$，可以通过。

```cpp
void run() {
    int T = read();
    while (T--) {
        int n = read();
        cout << "1 1" << endl;
        int a = read();
        cout << "1 11" << endl;
        int b = read();
        cout << "1 10" << endl;
        int c = read();
        cout << "0 " << n << ' ' << (a != b + c) << endl;
        int o = read();
    }
}
```

---

## 作者：TTpandaS (赞：0)

对于前 $i-1$ 位，每一位的下一位都会有 $0/1$，所以询问 $0,00,01$，判断 $0$ 的数量与 $00,01$ 数量之和是否相等，是则说明最后一位不是 $0$，那么 $s_n=1$，否则 $s_n=0$。

---

## 作者：ivyjiao (赞：0)

1. 第一次询问 $1$ 的数量，数量为 $a$。
2. 第二次询问 $01$ 的数量，即有多少 $1$ 前面是 $0$，数量为 $b$。
3. 第三次询问 $11$ 的数量，即有多少 $1$ 前面是 $1$，数量为 $c$。

由于 $s_1$ 前面没有数字，所以若 $a+b=c$，那么 $s_1=0$，否则 $s_1=1$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,s,p,q,ans;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        cout<<1<<" "<<"1"<<endl;
        cin>>s;
        cout<<1<<" "<<"01"<<endl;
        cin>>p;
        cout<<1<<" "<<"11"<<endl;
        cin>>q;
        if(p+q!=s) cout<<0<<" "<<1<<" "<<1<<endl;
        else cout<<0<<" "<<1<<" "<<0<<endl;
        cin>>ans;
    }
}
```

---

## 作者：WRuperD (赞：0)

聪明题。

首先问一次 1，如果 1 的个数是 0 或者 $n$ 那么我们可以直接断定这个字符串是全 0/1 的。

否则再问一次 11 的个数。用 1 的个数减去 11 的个数即可得到 1 连续段的个数。这很有用。我们再问 01 出现的次数。不难发现，一个以 0 开头的字符串 01 和 1 的连续段个数相等。以 1 开头的字符串 01 比 1 的连续段个数少一。至此我们可以猜出字符串开头的那个是什么。

---

## 作者：RayAstRa_ (赞：0)

脑筋急转弯题。

## Description

交互库有一个长为 $n(2\leq n\leq 50)$ 的 01 串 $s$，你每次可以询问交互库一个串 $t$，交互库会返回 $s$ 所有子串中 $t$ 的数量。你需要通过不超过 $3$ 次询问猜出 $s$ 串中某一个你自己选择的下标的值。

## Solution

观察到询问串 `01` 和 `11` 能得出所有值为 $1$ 且下标不是 $1$ 的字符的数量 $x$，再询问 `1` 得到整个串中 $1$ 的数量 $y$，$x=y$ 则 $s_1=0$，$x+1=y$ 则 $s_1=1$。

---

## 作者：lgx57 (赞：0)

一道很有意思的题目。

结论：问 $1$，$11$，$10$ 的个数。

我们可以把连续的 $0$ 和 $1$ 都缩成 $1$ 个 $0$ 或 $1$。经过这样的操作后，整个字符串变成了 $0$ 和 $1$ 交替的样子。

于是可以想到计算出 $1$ 的段数。设 $x$ 为 $1$ 的个数，$xx$ 为 $11$ 的个数，容易得到 $1$ 的段数为 $len=x-xx$。

再设 $10$ 的个数为 $yy$，然后分成 $2$ 种情况讨论：
 1. 若 $len>yy$ 那么这个字符串一定是 $0101 \cdots 01$ 或 $10101 \cdots 01$，无论怎么样都是 $1$ 结尾。（不然这个 $1$ 一定会对 $10$ 的数量产生贡献）
2. 否则，这个字符串一定以 $0$ 结尾。

然后就做完了。

---

## 作者：Ad_lqz_ht (赞：0)

## 前言
诈骗交互题。
## 做法
询问 $1$ 的出现次数，记为 $cnt1$。  
询问 $10$ 的出现次数，记为 $cnt10$。  
询问 $11$ 的出现次数，记为 $cnt11$。  
如果 $cnt10+cnt11=cnt1$ 则末位为 $0$ 否则末尾为 $1$。

## 证明
不考虑最后一位的情况下，每个 $1$ 的下一位都是 $0$ 或者 $1$，这两位连起来的结果必然只有 $11$ 和 $10$ 两种，每个 $1$ 都会作为 $10$ 或 $11$ 被统计，所以不考虑最后一位， $1$ 的数量等于 $10$ 的数量和 $11$ 的数量之和。

这时考虑最后一位如果为 $0$ 则 $1$ 的数量不变，否则 $1$ 的数量会比 $10$ 的数量与 $11$ 的数量之和多 $1$，符合上面的结论。

## 代码
注意是交互题，因此在每次输出过后都要清空缓冲区。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t, n;
    int cnt1, cnt10, cnt11;
    cin >> t;
    while (t--)
    {
        cin >> n;
        cout << "1 1" << endl; //询问1
        cin >> cnt1;
        cout << "1 10" << endl;//询问10
        cin >> cnt10;
        cout << "1 11" << endl;//询问11
        cin >> cnt11;
        cout << "0 " << n << ' ' << (cnt1 != cnt10 + cnt11) << endl;
        cin >> n;//别忘了输入结果！
        if (n == -1) return 0;
    }
    return 0;
}
```

---


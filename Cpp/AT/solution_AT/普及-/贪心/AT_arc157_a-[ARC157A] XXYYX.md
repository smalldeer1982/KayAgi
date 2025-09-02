# [ARC157A] XXYYX

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc157/tasks/arc157_a

`X`, `Y` からなる長さ $ N $ の文字列 $ S $ であって，以下の条件を満たすものが存在するかどうかを判定してください．

**条件:** $ S $ 中で $ 2 $ つの文字が隣り合う $ (N\ -\ 1) $ 箇所のうち

- ちょうど $ A $ 個が `XX`，
- ちょうど $ B $ 個が `XY`，
- ちょうど $ C $ 個が `YX`，
- ちょうど $ D $ 個が `YY` である．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ A\ \geq\ 0 $
- $ B\ \geq\ 0 $
- $ C\ \geq\ 0 $
- $ D\ \geq\ 0 $
- $ A\ +\ B\ +\ C\ +\ D\ =\ N\ -\ 1 $
 
### Sample Explanation 1

たとえば $ S\ =\ {} $`XXYYX` とすると，$ 2 $ つの文字が隣り合う箇所は左から順に `XX`, `XY`, `YY`, `YX` であり，各 $ 1 $ 個ずつとなって条件を満たします．

### Sample Explanation 2

たとえば $ S\ =\ {} $`XXYXY` が条件を満たします．

### Sample Explanation 3

条件を満たす文字列は存在しません．

## 样例 #1

### 输入

```
5 1 1 1 1```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5 1 2 1 0```

### 输出

```
Yes```

## 样例 #3

### 输入

```
5 0 4 0 0```

### 输出

```
No```

# 题解

## 作者：SlyCharlotte (赞：3)

#### 题目大意

确定是否存在一个由 X 和 Y 组成的长度为 Y 的字符串 $S$，它满足以下条件。

在 $S$ 中的 $N-1$ 对相邻字符中，正好有 $A$ 个 XX，$B$ 个 XY，$C$ 个 YX，$D$ 个 YY。

#### 简要分析

如果我们固定 $S$ 的第一个和最后一个字符，XY 和 YX 的数字之差将是唯一确定的，与中间的字符无关。例如，如果 $S$ 以 X 开始，以 Y 结束，那么 XY 一定比 YX 多出现一次，我们有 B-C=1。通过类似地考虑其他情况，我们可以看到，$∣B-C∣\leq1$ 必须成立，答案才是肯定的。

当 $∣B-C∣=1$ 时，一个期望的字符串 $S$ 总是存在的。现在，让我们忽略 $A$ 和 $D$ 的条件。

如果 $B-C=1$，$S′=XYXY...XY$，如果 $B-C=-1$，$S′=YXYX...YX$。

然后，在 $S′$ 的开头和结尾处相应地加上 $(A-1)$Xs 和 $(D-1)$Ys，得到一个想要的字符串 $S$。

例如，你可以让 $S′=XYXY...XYX$（$B$ 个 XYs 后跟一个 X），然后在 $S′$ 中相应地添加 $(A-1)$ 个 Xs 和 $(D-1)$ 个 Ys，得到一个所需的字符串 $S$。

最后，当 $B=C=0$ 时，字符串的唯一可能形式是 XXX...X 或 YYY...Y。

若答案是 Yes，当且仅当 $A$ 和 $D$ 中至少有一个是 $0$。

#### 代码实现

```C++
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
signed main()
{
	int n, a, b, c, d;
	scanf("%d%d%d%d%d", &n, &a, &b, &c, &d);
	if (abs(b - c) >= 2)
		cout << "No";
	else if (b == 0 && c == 0 && a > 0 && d > 0)
		cout << "No";
	else
		cout << "Yes";
}
```



---

## 作者：__LiChangChao__ (赞：2)

# 题意

问有没有一个长度为 $N$ 的由字符 `X` 和字母 `Y` 组成的字符串 $s$ 的 $(N-1)$ 对连续字符中有 $a$ 个`XX`，$b$ 个`XY`，$c$ 个`YX`，$d$ 个`YY`。

# 思路

首先，如果在 $a\not = 0,d\not = 0,b=0,c=0$ 的情况下，那绝对不成立，因为没法把 $(a+1)$ 个`X`和 $(b+1)$ 个`Y`连接起来。

然后，如果 $2 \le |b-c|$，那么也无法连接出一个字符串，因为光靠`XX`或`YY`无法连接一个以上的`XY`或`YX`。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,a,b,c,d;
int main() {
	cin>>n>>a>>b>>c>>d;
	if((abs(b-c)>=2)||(b==0&&c==0&&a>0&&d>0))cout<<"No";
	else cout<<"Yes";
}
```

---

## 作者：_Chesed_ (赞：1)

## 题意
给出 5 个数 $N$，$a$，$b$，$c$，$d$，确定是否存在一个由 X 和 Y 组成的长度为 Y 的字符串 S，满足在 S 中有相邻的 $a$ 个 XX，$b$ 个 XY，$c$ 个 YX，$d$ 个 YY。
## 分析
首先我们不难发现 $N$ 对于结果并没有影响，因为 $a+b+c+d=N-1$。

其次来分析相邻字符串，可以发现 XY 和 YX 就是由 XX 和 YY 拼成的，因此当 $b=c=0$ 而 $a > 0 \& d > 0$ 时一定不存在。有以下代码：
```cpp
	if(b==0&&c==0&&a>0&&d>0){
		printf("No");
	}
```
还有一点，当 $\left |b-c  \right | \ge 2$ 时也不成立。因为当 $\left |b-c  \right | \le 1$ 时，可以构造出 XY 与 YX 交替出现的字符串。而 $\left |b-c  \right | \ge 2$ 时必然会多出一个 XY 或 YX，因此无解。代码如下：
```cpp
	if(abs(b-c)>=2){
		printf("No");
	}
```
而其他情况就可以开心地输出 `Yes` 了。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a,b,c,d;
	cin>>n>>a>>b>>c>>d;
	if(abs(b-c)>=2){
		printf("No");
	}
	else if(b==0&&c==0&&a>0&&d>0){
		printf("No");
	}
	else{
		printf("Yes");
	}
} 
```



---

## 作者：ruanshaochuan______ (赞：0)

这道题中我们只需要考虑不可能的情况，把他们判断出来就可以了。                   
首先，如果 $a>0$，$d>0$，$c=0$，$b=0$ 是绝对不可能的，因为 `XX` 和 `YY` 之间必须要有连接。   
$|b-c|\ge2$ 也是不行的，因为仅靠 `XX` 和 `YY` 无法连接 `XY` 或 `YX`。   
code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,a,b,c,d;
    cin>>n>>a>>b>>c>>d;
    if((a&&d&&!c&&!b)||abs(b-c)>=2)
        cout<<"No";
    else
        cout<<"Yes";
}
```


---

## 作者：_Gabriel_ (赞：0)

### 思路

可以发现每一个 `XY` 必然伴随着出现一次 `YX`，当然可能会有一个 `XY` 没有伴随的 `YX` 的。
而且若必须存在 `XX` 和 `YY` 而不存在 `XY` 或 `YX` 的则无解。
就根据上述的两个条件判一下就好了。

所以有两种情况：

- $B,C$ 为 $0$，$A,C$ 大于 $0$ 或 $\lvert B - C \rvert \ge 2$ 的情况是不行的，因为存在 `XX` 和 `YY` 而不存在 `XY` 或 `YX`，所以输出 `No`；

- 其余输出 `Yes` 即可；

### 代码

```cpp
#include <bits/stdc++.h> 
using namespace std;
int main() {
	int n, a, b, c, d;
	cin >> n >> a >> b >> c >> d;
	if (abs(b - c) >= 2) {
		cout <<"No\n";
	} else if (a > 0 && b == 0 && c == 0 && d > 0) {
		cout << "No\n";
	} else {
		cout << "Yes\n";
	} 
	return 0;
}
```


---

## 作者：volatile (赞：0)

## 思路

看数据范围时能发现，这 $N$ 啥用也没有，因为 $A+B+C+D=N-1$。

首先，$B$，$D$ 为 $0$ 且 $A$，$C$ 为 $0$ 的情况是不可能有的，因为既然有 `XX` 和 `YY` 字符串，那么一定会至少组成一个 `XY` 或 `YX`，输出 `No`；

然后，$\left|B-D\right|\le1$ 才可以，因为构造两个 `XY`一定会出现一个 `YX`，`YX` 同理，当两个 $\left|B-D\right|>1$ 时，`XY` 或 `YX` 一定会超过所需的值,输出 `No`；

其余情况输出 `Yes` 就可以了。

## 代码

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int n,a,b,c,d;
	cin>>n>>a>>b>>c>>d;
	if(abs(b-c)>=2||(b==0&&c==0&&a>0&&d>0)) cout<<"No";
	else cout<<"Yes";
	return 0;
}
```

---

## 作者：code_hyx (赞：0)

显然，$N$ 没有用，因为 $A+B+C+D=N-1$，所以长度一定满足条件，不用考虑 $N$。  
然后，对于一个 $XY$，若不是最后一个，那么后面一定还会有一个 $X$，不然哪儿来的下一个 $XY$ 呢？既然这样，除最后一个 $XY$ 外，后面一定对应了一个 $YX$。  
同理，除最后一个 $YX$ 外，后面一定对应了一个 $XY$。  
所以，$B$ 和 $C$ 的差的绝对值超过 $1$，一定无解。  
特别地，当 $B=0$ 且 $C=0$ 时，只能全 $X$ 或全 $Y$，因此如果 $A>0,B=0,C=0,D>0$ 也是无解的。  
其它情况下，在 $X$ 和 $Y$ 之间任意插入 $X$ 或 $Y$，都不会影响 $XY$ 和 $YX$ 的数量，因此 $XX$ 和 $YY$ 的数量一定可以满足条件。  
代码：
```
#include<bits/stdc++.h> 
using namespace std;
int a,b,c,d,len;
string s;
int main()
{
	cin>>len>>a>>b>>c>>d;
	if(abs(b-c)>1)
	{
		cout<<"No\n";
		return 0;
	}
	else if(b==0&&c==0)
	{
		if(!(a>0&&d>0))cout<<"Yes\n";
		else cout<<"No\n";
	}
	else
	{
		cout<<"Yes\n";
	}
	return 0;
}
```


---

## 作者：___cjy__ (赞：0)

# [ARC157A] XXYYX 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_arc157_a)

[更好的阅读体验](https://www.luogu.com.cn/blog/509668/solution-at-arc157-a)

### 题目大意：

求一个长度为 $n-1$ 的字符串，其中含有 $A$ 个 $XX$，$B$ 个 $XY$，$C$ 个 $YX$ 和 $D$ 个 $YY$。判断此串是否有解。

### 正文：

显然，只要有至少一个 $XY$ 或 $YX$，当 $A$ 和 $D$ 为任何值时此串皆有解。所以当 $B$ 和 $C$ 都为 $0$ 时，此串无解。

同时，当 $|b-c|\le1$ 时，构造一个 $XY$ 与 $YX$ 交替出现的序列，可以轻松得到此串的解。在另外的情况下即当 $|b-c|>1$ 时，必会存在剩余的 $XY$ 或 $YX$。因此此串无解。

### AC Code：

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

int n, a, b, c, d;

signed main(){
	cin >> n >> a >> b >> c >> d;
	
	if(a && !b && !c && d) cout << "No\n";
	else if(abs(b - c) <= 1) cout << "Yes\n";
	else cout << "No\n";
	
	return 0;
}
```

---

## 作者：aeiouaoeiu (赞：0)

考虑先满足 $A$ 和 $D$。

不难发现当 $A,D\neq0$ 时，满足 $A,D$ 所产生的 $B,C$ 之差不超过 $1$，即所产生的 $|B-C|\le1$。

而且，在这个条件下，加上向外可延展的 $B,C$ 仍满足这个条件。

证明：当满足 $A,D$ 所产生的 $B,C$ 满足 $B-C=1$ 时，字符串形如 $\texttt{X}\ldots\texttt{XXY}\ldots\texttt{YYX}\ldots\texttt{XX}~\cdots~\texttt{Y}\ldots\texttt{YY}$，此时两边延展均只能增加 $C$，两边延展后也只能增加 $B$，一直满足 $|B-C|\le1$，其他情况同理。

但是有一个特殊条件：当 $B=C=0$ 时无解，因为满足 $A,D$ 中间必须有一个 $B$ 或 $C$，即变成形如 $\texttt{X}\ldots\texttt{XXY}\ldots\texttt{YY}$（反过来类似）。

我们还有一种情况：$A,D$ 中至少有一个为 $0$，此时满足 $A,D$ 所产生的 $B,C$ 之差显然不超过 $1$，所以只需判断 $|B-C|\le1$ 是否成立即可。

综上，我们有了以下结果：

- 当 $A,D\neq0$ 时，如果 $B=C=0$，那么无解，输出 ``No``。

- 当 $A,D\neq0$ 且 $B,C$ 中至少有一个不为 $0$，判断 $|B-C|\le1$ 是否成立，成立输出 ``Yes``，否则输出 ``No``。

- 当 $A,D$ 中至少有一个为 $0$ 时，判断 $|B-C|\le1$ 是否成立，成立输出 ``Yes``，否则输出 ``No``。

简短的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=200005;
ll n,a,b,c,d;
int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n>>a>>b>>c>>d;
    if(a&&d&&!b&&!c) cout<<"No";
    else if(abs(b-c)<=1) cout<<"Yes";
    else cout<<"No";
    return 0;
}
```


---

## 作者：快乐的大童 (赞：0)

UPD：先前排版有一点小问题，现在已修改。
### 题意简述
求是否存在一个长度为 $n$ 的仅由 `X` 和 `Y` 的字符串，满足有 $a$ 个连续的 `XX`，$b$ 个连续的 `XY`，$c$ 个连续的 `YX`，$d$ 个连续的 `YY`。保证 $a+b+c+d=n-1$。
### 思路
分类讨论：
#### 0. $b,c=0,a,d\not=0$
这是一个小特判，要在所有判断条件之前（因为这种情况下 `XX` 和 `YY` 拼接必然会产生一个 `XY` 或者 `YX`）。
#### 1. $|b-c|\ge 2$
由于构造两个 `XY` 必定会产生一个 `YX`，所以这种情况下无解。 

两个 `YX` 的情况同理。
#### 2. $|b-c|\le 1$
这种情况下必定有解（除了上述特判），构造方法：

- $b=c$，则可以构造 `XYXYX...`（`X` 比 `Y` 多 $1$ 个或者 `Y` 比 `X` 多 $1$ 个）。
- $b-c=1$，则可以构造 `XYXYXY...`（`X` 开头，`Y` 结尾，两者数量相等）。
- $c-b=1$，则可以构造 `YXYXYX...`（`Y` 开头，`X` 结尾，两者数量相等）。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,d;
int main(){
	cin>>n>>a>>b>>c>>d;
	if(!b&&!c&&a&&d) puts("No");
	else if(abs(b-c)<=1) puts("Yes");
	else puts("No");
}
```


---

## 作者：qifan_maker (赞：0)

### 题目链接

[洛谷](https://www.luogu.com.cn/problem/AT_arc157_a)

[AtCoder](https://atcoder.jp/contests/arc157/tasks/arc157_a)

### 题意分析

给定一个由 $X$ 和 $Y$ 组成的长度为 $N$ 的字符串 $S$，确定是否存在一个字符串满足以下条件： 其中 $N-1$ 个连续的字符对，有 $A$ 对 ``XX``，$B$ 对 ``XY`` ，$C$ 对 ``YX``，$D$ 对 ``YY``。

### 题目解法

**结论题**。

* * *

如果 $∣B-C∣=0$，

我们可以举个例子：`5 0 2 2 0`，

这时正确的字符串 $S$ 为 `XYXYX` 或 `YXYXY`，

`XY` 有 $2$ 个，是 $\rm\fbox{XY}\fbox{XY}X$ 或 $\rm Y\fbox{XY}\fbox{XY}$，

`YX` 有 $2$ 个，是 $\rm X\fbox{YX}\fbox{YX}$ 或 $\rm\fbox{YX}\fbox{YX}Y$，

所以我们可以推导出：

当 $∣B-C∣=0$ 并且 $A$ 和 $D$ 为 $0$ 时，可能的字符串形式是 `XYXY...XYX` 或 `YXYX...YXY`，答案是 ``Yes``。

* * *

如果 $∣B-C∣=1$，

说明 `X` 比 `Y` 或 `Y` 比 `X` 少 $1$，只需要在 $∣B-C∣=0$ 的前提下加一个 `X` 或 `Y` 即可，

如 `6 0 2 3 0`，

这时正确的字符串 $S$ 为 `YXYXYX`，

`XY` 有 $2$ 个，是 $\rm Y\fbox{XY}\fbox{XY}X$，

`YX` 有 $3$ 个，是 $\rm\fbox{YX}\fbox{YX}\fbox{YX}$，

所以我们可以推导出：

当 $∣B-C∣=1$ 并且 $A$ 和 $D$ 为 $0$ 时，可能的字符串形式是 `YXYX...YX`，答案是 `Yes`。

* * *

如果 $∣B-C∣> 1$，

如 `7 0 2 4 0`，

这时我们如果尝试使用以上 `X` 和 `Y` 交替输出的方法列出字符串时，

会发现 `XY` 的个数已经达到了要求，而 `YX` 的个数却不够，

如果继续增加，直到 `YX` 的个数达到要求，就会发现 `XY` 的个数却超过了要求，

如 `YXYXYXYX`,

`XY` 有 $3$ 个，是 $\rm Y\fbox{XY}\fbox{XY}\fbox{XY}X$，

`YX` 有 $4$ 个，是 $\rm \fbox{YX}\fbox{YX}\fbox{YX}\fbox{YX}$，

所以我们可以推导出：

当 $∣B-C∣> 1$ 时，无法满足题意，答案是 `No`。

* * *

现在，我们将以上结论整理一下，得出：

如果 $∣B-C∣ > 1$，那么答案为 `No`，

否则答案为 `Yes`。

但是提交后发现 [WA了3个测试点](https://atcoder.jp/contests/arc157/submissions/39219086)，

我们考虑到一种情况，

如果 $B = C = 0$，$A>0$，$D>0$，

如 `5 2 0 0 2`，

这时我们尝试列出答案 `XXXYYY`，

会发现超出了字符串长度的限制 $N$，

我们可以推导出：

当 $B = C = 0$，$A>0$，$D>0$ 时，答案的长度会超出字符串长度限制，答案是 `No`。

所以我们需要特判，如果 `b==0 and c==0 and a>0 and d>0`，就输出 `No`。

### [AC](https://www.luogu.com.cn/record/103167317) Code
```cpp
/*
题目编号：
A - XXYYX
思路：
无
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,a,b,c,d;
	cin >> n >> a >> b >> c >> d;
    if (b==0 and c==0 and a>0 and d>0){
    	cout << "No";
	}
	else if (abs(b-c) > 1){
		cout << "No";
	}
	else {
		cout << "Yes";
	}
	return 0;
}
```

---


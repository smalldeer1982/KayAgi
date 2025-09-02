# 「DAOI R1」Concert

## 题目背景

> $ \texttt{I want to be an artist.} $

## 题目描述

$ \texttt{Erinyes} $ 的学校将举办一场音乐会，但是他若想加入其中就必须经过一场考核，试题如下：

给定两个整数 $ n,k $，表示有 $ n $ 个同学，你需要给每位同学分发一个数字，即对于整数 $ n $ 构造一个序列 $ a $。

同学得到的数字必须满足如下性质：

- 对于每个 $ i\;(1 \leq i \leq n-1) $，满足 $ a_i=\gcd(a_{i+1},a_{i+2},\dots,a_{n-1},a_n) $。
- 对于每个 $ i\;(1 \leq i \leq n) $，满足 $ 1 \leq a_i \leq 10^5 $。
- 对于每个 $ i\;(1 \leq i \leq 10^5) $，$ a_i $ 至多在序列中出现 $ k $ 次。

但这对 $ \texttt{Erinyes} $ 来说太简单了，所以他决定专心准备节目，而这个问题则将交给你。

你的任务是输出这样的序列的个数 $ l $ 以及所有这样的序列。但是由于答案可能会很大，所以我们对输出做了如下规定：

- 对于 $ l=0 $，输出 ```Impossible```。
- 对于 $ 1 \leq l \leq 4 $，输出序列实际个数，接下来 $ l $ 行，每行一个序列，表示你所构造的序列。
- 对于 $ l \geq 5 $，输出 ```5 or more```，接下来五行，每行一个序列，表示你所构造的序列中字典序最小的五个。
- 你必须按照字典序输出。

## 说明/提示

### 样例解释
对于第一组数据，可以发现此方案是最优解。

对于第二组数据，无论如何也无法构造出正确的序列。

对于第三组数据，无论如何也无法构造出正确的序列。

对于第四组数据，无论如何也无法构造出正确的序列。

### 数据规模
对于 $ 100\% $ 的数据，$ 1 \leq t \leq 100,1 \leq n \leq 10^5,0 \leq k \leq 10^5 $

## 样例 #1

### 输入

```
4
1 1
97 0
17 1
5 2```

### 输出

```
5 or more
1
2
3
4
5
Impossible
Impossible
Impossible```

# 题解

## 作者：Iratis (赞：14)

这道题目作为本次比赛的 T1，难度还是较低的。

我们考虑一个长度为 $ n $ 的序列 $ a $，当 $ i=n-1 $ 时，$ a_{n-1}=\gcd(a_n)=a_n $，当 $ i=n-2 $，$ a_{n-2}=\gcd(a_{n-1},a_n)=a_n $。像这样枚举下去，必然可以得到一个性质，序列中的所有数相同。

所以当 $ n \leq k $ 时，可以构造出一个所有数字相同的序列。

否则，无法构造。

代码如下：
```cpp
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int T;
int n,k; 
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&k);
		if(n>k)puts("Impossible");
		else
		{
			puts("5 or more");
			for(int i=1;i<=5;i++)
			{
				for(int j=1;j<=n;j++)printf("%d ",i);
				puts(""); 
			}
		}
	}
	return 0;
}
```


---

## 作者：Buried_Dream (赞：4)

## 题意：

构造一个长度为 $n$ 序列，满足 
$a_i=\gcd(a_{i+1},a_{i+2},a_{i+3},...,a_{n})$，$1 \le a_i \le 10^5$，对于每一个 $a_i$，最多在这个序列中出现 $k$ 次。

## 思路：

老诈骗题了，对于 $a_{n-1}$， $a_{n-1} = \gcd(a_n)$，所以 $a_{n-1} = a_n$，那 $a_{n-2}= \gcd(a_{n-1},a_n)$，又因为 $a_{n-1}=a_n$，所以 $a_{n-2} = a_{n-1} = a_n$，于是我们能得出这个序列中的所有数字都是相等的，只需要满足 $a_i$ 出现的次数为 $n \le k$ 即可。

## AC code:

```cpp
/*
	Work by: TLE_Automation
*/
#include<cmath>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL long long
//#define int long long
using namespace std;

const int N = 1e6 + 10;
const int MAXN = 2e5 + 10;

inline char readchar() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline int read() {
	#define readchar getchar
	int res = 0, f = 0;
	char ch = readchar();
	for(; !isdigit(ch); ch = readchar()) if(ch == '-') f = 1;
	for(; isdigit(ch); ch = readchar()) res = (res << 1) + (res << 3) + (ch ^ '0');
	return f ? -res : res;
}

inline void print(int x) {
	if (x < 0 ) putchar('-'), x = -x;
	if (x > 9 ) print(x / 10);
	putchar(x % 10 + '0');
}

int a[MAXN];

inline void Main() {
	int n = read(), k = read();
	if(!k || (k < n)) return printf("Impossible\n"), void();
	printf("5 or more\n");
	for(register int j = 1; j <= 5; j++)  {
		for(register int i = 1; i <= n; i++) printf("%lld ", j);
		printf("\n");
	} 
}

signed main() {
	int T = read();
	while(T--) Main();
}

---

## 作者：Galex (赞：3)

既然正着不好搞，那就反着考虑。

假设我们已经知道 $a_n$，那么 $a_{n-1}=a_n$，$a_{n-2} = \gcd(a_{n-1},a_n)=a_n$，依此类推。

那么就很明显了：$a_1=a_2=a_3=a_4= \dots =a_n$。

如果 $k \ge n$，则 $l=10^5$，输出 $n$ 个 $1$、$n$ 个 $2$、$n$ 个 $3$、$n$ 个 $4$、$n$ 个 $5$。

否则，输出 `Impossible`。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

string ans[5];
int n, k, cnt = 0;
int c[100005]; 

signed main() {
	int t = read();
	while (t--) {
		n = read(), k = read();
		if (k >= n) {
			printf("5 or more\n");
			for (int i = 1; i <= 5; i++) {
				for (int j = 1; j <= n; j++)
					printf("%d ", i);
				putchar('\n');
			}
		}
		else
			printf("Impossible\n");
	}
	return 0;
}
```


---

## 作者：skyskyCCC (赞：2)

**前言。**

构造题。

**分析。**

题意：[P8284传送门](https://www.luogu.com.cn/problem/P8284)。

小注：下面的 $gcd(x)$ 表示 $x$ 的最大公约数，若括号里有多个数，则是这多个数的最大公约数。

不知道最大公约数的点[这里](https://baike.so.com/doc/5399827-5637381.html)。

考虑逆推：

当 $i=n-1$ 时：

因为 $a_i=gcd(a_{i+1},a_{i+2},...,a_{n-1},a_n)$，

又因所构造的序列中字典序需要最小，

所以 $a_{n-1}=gcd(a_n)=a_n$。

同理，

当 $i=n-2$ 时，得 $a_{n-2}=gcd(a_{n-1},a_n)=gcd(a_n,a_n)=a_n$。

再往下推，我们发现 $a_i=a_n$ 这个规律。

换言之，就是 $a_1=a_2=a_3=a_4=...=a_{n-1}=a_n$ 的结论，就是说，序列 $a$ 中的数都相同。

因为 $a_i$ 至多在序列中出现 $k$ 次，又因为任何一个序列 $a$ 里的数都相同，那么，$k$ 决定的就是 $a$ 数组的长度。因为 $a$ 数组的长度为 $n$ ，故而当 $k<n$ 时，构造不出符合条件的 $a$ 数组；当 $k \geq n$ 时，可以构造出无数个符合条件的 $a$ 数组。

那么，分两个情况讨论即可。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int t,n,k;
int main(){
    ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);//加速，可省略。
    cin>>t;
    for (int i=1;i<=t;i++){
        cin>>n>>k;
        if(k<n)cout<<"Impossible"<<endl;
        //第一种情况，需要的数小于数组，无解。
        if(k>=n){//第二种情况。
            cout<<"5 or more"<<endl;
            for(int j=1;j<=5;j++){
                for(int k=1;k<=n;k++){
                    cout<<j<<" ";
                }//使字典序最小。
                cout<<endl;//注意换行。
            }
        }
    }
    return 0;
}//by zzy
```
**后记。**

速度非常慢，大约 $2$ 秒多。

大家如有疑问，请在评论区提出，我会尽力解答的。


---

## 作者：雨伞CKY (赞：2)

# 题意简述
- 每组数据给定两个整数 $n,k$。
- 构造整数数列 $a$，使得：
    - 对于每个整数 $i\in [1,n)$，$a_{i}=\gcd (a_{i+1},a_{i+2},\dotsc ,a_{n})$。
    - 对于每个整数 $i\in [1,n]$，$a_{i}\in [1,10^{5}]$。 
    - 数列内的某一整数至多重复 $k$ 次。
- 满足题意的数列不存在时，输出 `Impossible`；满足题意的数列的个数在四个以内时，输出数列实际个数和构造的数列；满足题意的数列的个数不小于五个时，输出 `5 or more` 和按字典序排序最小的五个符合题意的数列。
  
# 题目分析
注意到“对于每个整数 $i\in [1,n)$，$a_{i}=\gcd (a_{i+1},a_{i+2},\dotsc ,a_{n})$”，则有 $a_{n-1}=\gcd (a_{n})=\gcd (a_{n})=a_{n}$，$a_{n-2}=\gcd (a_{n-1},a_{n})=\gcd (a_{n},a_{n})=a_{n}$。

继续计算不难发现，数列 $a$ 的每个整数都等于 $a_{n}$，即它们都相等。又因为“数列内的某一整数至多重复 k 次”，可以得到以下结论。
- 当且仅当 $n\gt k$ 时，没有符合题意的数列；
- 否则，一定有 $10^{5}$ 个符合题意的数列 $i,i,\dotsc ,i(i\in [1,10^{5}])$。
  
# 代码
```cpp
#include <cctype>
#include <cstdio>
using namespace std;

int read(){
    int tmp = 0;
    char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)){
        tmp = (tmp << 3) + (tmp << 1) + (ch ^ '0');
        ch = getchar();
    }
    return tmp;
}

int t,n,k;

int main(){
    t = read();
    for (int i = 1;i <= t;i++){
        n = read();
        k = read();
        if (k < n){
            printf("Impossible\n");
        }
        else{
            printf("5 or more\n");
            for (int i = 1;i <= 5;i++){
                for (int j = 1;j <= n;j++){
                    printf("%d ",i);
                }
                putchar('\n');
            }
        }
    }
    return 0;
}
```

---

## 作者：Patients (赞：1)

[P8284 「DAOI R1」Concert](https://www.luogu.com.cn/problem/P8284)

------------

当我们看到 $ \gcd(a[i],a[i+1],…,a[n]) $ 时，不妨设想一下我们用检查时，时间复杂度为 $ O(T \times n \times \log _2^n) $ ，就会有 $ 2.5 \times 10^8 $ 的时间复杂度，再输出一下不就超了吗？


让我们来推一下：

$ a[n-1] = \gcd(a[n]) = a[n] $

$ a[n-2] = \gcd(a[n],a[n-1]) = a[n] $

………

$ a[1] = \gcd(a[n],a[n-1],…,a[2]) = a[n] $

所以说这一个序列 $ a $ 所满足的条件是所有值相等。

对于 $ n < k $ 时输出 ``` Impossible ``` 。
否则输出 ``` 5 or more ``` 。

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,k,T;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		if(n>k) cout<<"Impossible"<<'\n';
		else
		{
			cout<<"5 or more"<<'\n';
			for(int i=1;i<=5;i++)
			{
				for(int j=1;j<=n;j++) cout<<i<<' ';
				cout<<'\n';
			}
		}
	}
	return 0;
}


```


---

## 作者：lsj2009 (赞：1)

## 题目大意
<https://www.luogu.com.cn/problem/P8284>。

## 思路

在此之前，先让我们看一个显然成立的柿子：

$$\gcd(\underbrace{a,a,\cdot\cdot\cdot,a,a}_{\texttt{若干个相同的正整数} a})=a$$


------------
容易发现，由于每个 $\forall a_i(1\le i<n)$ 都是由 $a_{i+1}\sim a_n$ 推出的，则如果我们固定了 $a_n$，可以推出 $a_{n-1}$，再推出 $a_{n-2}$……一直到推出整个序列 $\{a_n\}$。

****引理：$\forall a_i$ 满足 $a_i=n$****。

****证明：数学归纳法。****

- $i=n$ 时明显满足条件。

- 当 $i+1\sim n$ 均满足条件时，$a_i=\gcd(a_{i+1},a_{i+2},\cdot\cdot\cdot,a_n)$ 而对于任意 $k>i$ 的 $a_k$ 均满足条件，则上式变为 $\gcd(a_n,a_n,\cdot\cdot\cdot,a_n,a_n)=a_n$。

- 证毕。

则该序列的所有元素的值都是 $a_n$，一个元素出现了 $n$ 次，如果 $k<n$ 则本题无解。

反之由于 $a_n$ 有 $10^5$ 种取法，一定超出 $5$ 种，则我们只需要依次输出 $a_n=1,2,3,4,5$ 的情况即可。

---

## 作者：Nygglatho (赞：0)

首先，我们会发现，若 $n \le k$，则有解，否则无解。

因为，若 $n > k$，则 $a$ 中 **必定会** 有多于 $1$ 个的不同数字。

那么这样的话，考虑把 $a$ 根据数字是否相同，来分成好几段，如 $1, 1, 1, 5, 5, 5$ 分成两段。那么最后一段的最大公约数必然不等于前面一段的最后一个数字，因为最后一段的最大公约数仍然是最后一段本身，而最后一段本身必然不等于前面一段的数字。

举个例子：$a$ 为 $4, 8, 12, 12$ 时，虽然 $\gcd(8, 12, 12) = 4$，然而 $\gcd(12, 12) \ne 8$。

由于 $n > k$ 时，至少分成两段，所以必定无解。

而 $n \le k$ 时，只有一段，那么本身的最大公约数仍然是本身， 如 $\gcd(5, 5, 5) = 5$，所以有解，这里只需要输出 $n$ 个 $1$ 一直到 $n$ 个 $5$ 即可。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;

void Solve() {
	int n, k;
	scanf ("%d%d", &n, &k);
	if (n > k) {puts("Impossible"); return;}
	else puts("5 or more");
	for (int i = 1; i <= 5; ++i) {
		for (int j = 1; j <= n; ++j) cout << i << ' ';
		cout << endl;
	}
}

int main() {
	int T;
	scanf ("%d", &T);
	while(T--) Solve();
}
```

---


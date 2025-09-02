# [ARC153A] AABCDDEFE

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc153/tasks/arc153_a

正整数 $ x $ が**美しい整数**であるとは，$ x $ が $ 9 $ 桁の整数であり，その $ 10 $ 進法表記 $ S_1\ldots\ S_9 $ （$ S_i $ は $ x $ の $ 10 $ 進法表記の $ i $ 文字目）が以下の条件をすべて満たすことをいいます：

- $ S_1 $ は `0` ではない
- $ S_1\ =\ S_2 $
- $ S_5\ =\ S_6 $
- $ S_7\ =\ S_9 $
 
例えば $ 998244353 $ や $ 333333333 $ は美しい整数です．$ 111112222 $ は $ S_5\ \neq\ S_6 $ であるため美しい整数ではありません．

正の整数 $ N $ が与えられます．小さい方から数えて $ N $ 番目の美しい整数を答えてください．

## 说明/提示

### 制約

- $ N $ は正の整数
- 美しい整数が $ N $ 個以上存在する
 
### Sample Explanation 1

美しい整数を小さい順に並べると，$ 110000000,\ 110000010,\ 110000020,\ \ldots $ となります．

## 样例 #1

### 输入

```
3```

### 输出

```
110000020```

## 样例 #2

### 输入

```
882436```

### 输出

```
998244353```

## 样例 #3

### 输入

```
2023```

### 输出

```
110200222```

# 题解

## 作者：U_star (赞：3)

题目大意：一个九位数，如果它满足以下条件，则称它为一个美丽的数：

- 最高位不为 $0$；
- 亿位上的数字等于千万位上的数字；
- 万位上的数字等于千位上的数字；
- 百位上的数字等于各位上的数字。

现在给定了 $N$，求第 $N$ 个美丽数。

一种可行的方法，是对这个数的亿位、百万位、十万位、万位、百位、十位进行枚举，虽然是六次方级的暴力，但是由于常数较小，时间复杂度可以通过。
```cpp
#include<bits/stdc++.h>
using namespace std;
int sum=0;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=9;i++)
		for(int j=0;j<=9;j++)
			for(int k=0;k<=9;k++)
				for(int l=0;l<=9;l++)
					for(int m=0;m<=9;m++)
						for(int o=0;o<=9;o++)
							if(++sum==n)
							cout<<i<<i<<j<<k<<l<<l<<m<<o<<m;
	return 0;
}
```
~~暴力 yyds！~~

其实此题还有更快的做法。

我们观察上一份代码，发现它一共循环了 $9\times 10^5$ 次，每次都必然产生一个美丽数，也就是说美丽数恰好共有 $9\times 10^5$ 个。

这是一种巧合吗？并不是。我们冷静下来一思考，发现由于亿位上的数字等于千万位上的数字，所以在亿位上的数字固定的情况下，千万位的数字必然不会变化，因此我们可以抛开千万位上的数字，千位、个位数字也是同理，抛开这三个数字后，它就变成了一个六位数。

因此问题转化成了：给定了一个正整数 $N$，求第 $N$ 个六位数，将其十万位、千位、百位重复输出一次。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	string s=to_string(n+99999);
	cout<<s[0]<<s[0]<<s[1]<<s[2]<<s[3]<<s[3]<<s[4]<<s[5]<<s[4];
   	return 0; 
}
```
所以这题是专为 $998244353$ 准备的吗？

---

## 作者：chlchl (赞：3)

**做法与所有题解不一致，望通过。**

作为签到题，肯定没什么思维难度。

## Solution
如果枚举所有九位数，时间复杂度会非常紧（虽然有卡常过的）。

但换个角度想，第 $n$ 小的数，其实可以转化为统计数量的问题。

由此，赛时想到二分，然后对 $mid$ 跑数位 DP，看看 $[10^8,mid]$ 中有没有这么多美丽的正整数。

至于数位 DP 怎么写，看看题目限制：
- $S_1\neq 0$：判断前导 $0$ 是数位 DP 的常见操作。
- $S_1=S_2,S_5=S_6$：记录上一位数字即可。
- $S_7=S_9$：记录上两位数字。

综上，记录前导 $0$、前两位数字是多少、万年不变的当前位数和是否达到最高位 $op$ 即可完成本题。

```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int N = 10 + 5;
int n, dgt[N], f[N][2][N][N];
 
int dp(int len, int op, int lst1, int lst2){//一个比较简单的数位 DP
	if(!len)
		return 1;
	if(~f[len][op][lst1][lst2])
		return f[len][op][lst1][lst2];
	int k = (op ? dgt[len] : 9);
	int cnt = 0;
	for(int d=0;d<=k;d++){
		if(len == 9 && d == 0)
			continue;
		if(len == 8 && d != lst1)
			continue;
		if(len == 4 && d != lst1)
			continue;
		if(len == 1 && d != lst2)
			continue;
		cnt += dp(len - 1, op & (d == k), d, lst1);
	}
	return f[len][op][lst1][lst2] = cnt;
}
 
int solve(int x){
	memset(f, -1, sizeof(f));
	int len = 0;
	do
		dgt[++len] = x % 10;//第 9 位开始枚举（最高位） 
	while(x /= 10);
	return dp(len, 1, 10, 10);
}
 
bool check(int x){
	return solve(x) >= n;
}
 
int main(){
	scanf("%d", &n);
	int l = 100000000, r = 999999999;//二分边界记得设
	while(l <= r){
		int mid = (l + r) >> 1;
		if(check(mid))
			r = mid - 1;
		else
			l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}
```

这个做法的优越性在于：
- 思维难度低，不需要观察任何性质。
- 工程量小，比打表省事多了。
- 效率高，不开 O2 跑进最优解第一页。

So，[数位 DP](https://www.luogu.com.cn/blog/hugocaicai/shuo-wei-dp-xue-xi-bi-ji) 香不香 qwq？

---

## 作者：rui_er (赞：1)

本题解并非正经解法（正经解法是简单数学），但在遇到更复杂的类似题目时可能会用到，放在这里供参考。

九位数共 $9\times 10^8$ 个，可以在较短时间内枚举一遍，因此考虑分段打表。按题意容易写出暴力打表程序（核心代码）：

```cpp
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
bool check(int x) {
	int a = x / 100000000;
	int b = x / 10000000 % 10;
	int c = x / 1000000 % 10;
	int d = x / 100000 % 10;
	int e = x / 10000 % 10;
	int f = x / 1000 % 10;
	int g = x / 100 % 10;
	int h = x / 10 % 10;
	int i = x % 10;
	return a == b && e == f && g == i;
}
int main() {
	int n; vector<int> p;
	rep(i, 100000000, 999999999) if(check(i)) p.push_back(i);
	printf("const int a[]={0");
	rep(i, 0, (int)p.size()-1) /* if(i % 1000 == 999) */ printf(",%d", p[i]);
	printf("};");
	return 0;
}
```

上面这份代码会生成所有符合要求的九位数，并生成相关的 C++ 代码。但是数太多了代码太长，怎么办呢？我们每 $1000$ 个数打印一个（即注释部分），然后代码就能放下了。

容易根据 $n$ 算出所求在哪两个数中间，把这两个数中间的所有数暴力一遍即可。

可以得到最终代码：

```cpp
// Problem: A - AABCDDEFE
// Contest: AtCoder - AtCoder Regular Contest 153
// URL: https://atcoder.jp/contests/arc153/tasks/arc153_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int a[]={100000000,110099999,110199999,...,999999999};

int n;
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
bool check(int); // 同打表程序

int main() {
	scanf("%d", &n);
	int i, j;
	for(i = a[n/1000] + 1, j = n / 1000 * 1000; j < n; i++) if(check(i)) ++j;
	printf("%d\n", i-1);
	return 0;
}
```

---

## 作者：FyFive (赞：0)

>简要题意：
>找到字典序第 $n$ 个不含前导 0 的九位正整数，满足以下条件：
>
>- 第一位和第二位相同
>- 第五位和第六位相同
>- 第七位和第九位相同
>
>例如：$998244353$、$333333333$
>保证 所给的 $n \leq $ 满足条件的正整数数量。

很显然，其实有三位都是和其他位绑定的，那么排除掉就好了。

排除之后，显然只剩下第 $1, 3, 4, 5, 7, 8$ 位了，很显然，这几位也是决定顺序的位。

到这里就容易知道了，只有 $900000$ 个满足要求的九位正整数，从 $110000000$ 到 $999999999$。

那么，输入的 $n$ 就必然是六位的，和上述位置一一对应，如果不足六位应当以前导 0 补齐。

剩下三位直接对应就好。

时间复杂度为 $O(1)$。

Code：
```cpp
int main()
{
    cin>>n;
    --n;
    n+=100000;
    ans=101*(n%100/10);
    ans+=10*(n%10);
    ans+=11000*(n%1000/100);
    ans+=100000*(n%10000/1000);
    ans+=1000000*(n%100000/10000);
    ans+=110000000*(n/100000);
    cout<<ans;
    return 0;
}
```

---

## 作者：Paracelestia (赞：0)

## 题目大意

给定正整数 $N$ ，求出第 $N$ 个形如 ```AABCDDEFE``` 的数。

## 题目解法

赛时看没有给出数据范围一度很慌，但这题其实就是暴力枚举。

多重循环分别枚举 ```A``` ， ```B``` ，```C``` ， ```D``` ， ```E``` ， ```F``` 位上的数，同时统计个数，第 $N$ 个即为答案。时间复杂度 $\mathcal{O}(n)$ 。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 114514
#define M 1919810
#define inf 0x3f3f3f3f
template<typename T> inline void read(T &x) {
    x = 0; int f = 1; char ch;
    for(; !isdigit(ch); ch = getchar())
        if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar())
        x = (x << 3) + (x << 1) + (ch - '0');
    x *= f;
}
int n;
int main() {
    read(n);
    for(int a = 1; a <= 9; a ++)
        for(int b = 0; b <= 9; b ++)
            for(int c = 0; c <= 9; c ++)
                for(int d = 0; d <= 9; d ++)
                    for(int e = 0; e <= 9; e ++)
                        for(int f = 0; f <= 9; f ++) 
                            if(-- n == 0) printf("%d%d%d%d%d%d%d%d%d", a, a, b, c, d, d, e, f, e);
    return 0;
}
```


---

## 作者：lzyqwq (赞：0)

赛时打表没打下，没想到枚举数位，写了个暴力 $\mathcal{O}(9\times 10^8)$ 卡过了（话说 $9\times 10^8$ 本来就是可以卡过的级别吧）。

思路很简单，就枚举 $[10^8,10^9)$ 中的每个数，如果满足题目所给的格式 `AABCDDEFE`，计数器加 $1$，如果计数器为 $n$ 输出即可。

代码：

```cpp
#pragma GCC optimize("Ofast")//外站可以指令集
#include<bits/stdc++.h>
using namespace std;
int n;
bool check(int x){
	return x/100000000==x/10000000%10&&x/10000%10==x/1000%10&&x/100%10==x%10;
}
int main(){
    cin>>n;
    for(register int i=1e8;i<1e9;++i){
        if(check(i)){
            --n;
            if(!n){
                return cout<<i,0;
            }
        }
    }
}
```


---

## 作者：Butterfly___qwq (赞：0)

# ARC153A 题解：
## 题意：
我们定义一种数，这个数是一个九位数，各位数字分别是  $s1,s2,s3,s4,s5,s6,s7,s8,s9$。这个数还满足以下条件：
- $s1 \neq 0$
- $s1=s2$
- $s5=s6$
- $s7=s9$    

求出第 $N$ 小的这种数。
## 思路：
这道题实际上数据范围很小，根据样例，可以发现最大的 $N$ 在 $10^7$ 左右，所以此题我们可以用 $O(n)$ 的算法通过。我们可以这样：
- 先把 $s8$ 每次加一，加到十再清零，$s7,s9$ 各加一。
- $s7,s9$ 大于十，把 $s7,s9$ 清零，$s5,s6$ 加一。
- $s5,s6$ 大于十，把 $s5,s6$ 清零，$s4$ 加一。
- $s4$ 大于十，把 $s4$ 清零，$s3$ 加一。
- $s3$ 大于十，把 $s3$ 清零，$s1,s2$ 加一。
- $s8$ 清零后，还要继续进行 $s8$ 的操作。
这些操作就可以得到这种数。这样一来，代码就很好写了。
## 代码：
```cpp
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main(){
	int s1=1,s2=1,s3=0,s4=0,s5=0,s6=0,s7=0,s8=0,s9=0;
	long long n;cin>>n;
	n--;
	while(n--){
		s8++;
		if(s8>=10){
			s8=0;
			s7++;
			s9++;
		}
		if(s7>=10){
			s7=s9=0;
			s6++;
			s5++;
		}
		if(s6>=10){
			s6=s5=0;
			s4++;
		}
		if(s4>=10){
			s4=0;
			s3++;
		}
		if(s3>=10){
			s3=0;
			s2++;
			s1++;
		}
	}
	cout<<s1<<s2<<s3<<s4<<s5<<s6<<s7<<s8<<s9;
	return 0;
}
```

---

## 作者：Lyu_echo (赞：0)

## 题意

定义一个 9 位整数 $S$ 为 `beautiful integer` 当且仅当满足以下要求：

- $S_1 \ne 0$
-  $S_1 = S_2$
- $S_5 = S_6$
- $S_7 = S_9$

其中：$S_i$ 表示整数 $S$ 从左往右的第 $i$ 位数，$1 \le i \le 9$。

给定整数 $N$，问：第 $N$ 个 `beautiful integer` 是多少？

## 解题思路

明显地，9 位整数 $S$ 由 6 个不同个位数组成。

枚举这 6 个数，再组成 9 位整数 $S$。对所有的整数 $S$ 求 $N$ 小值。

求 $N$ 小值可以使用 `std :: sort` 或 `std :: nth_element`。前者时间复杂度 $\mathcal{O}(N\operatorname{log} N)$，后者 $\mathcal{O}(N)$。

## 代码实现

给出代码主要部分。

```cpp
void solve() {
    vector<int> ans;
    int n;
    cin >> n;
    for (int a = 1; a <= 9; a++) {
        for (int b = 0; b <= 9; b++) {
            for (int c = 0; c <= 9; c++) {
                for (int d = 0; d <= 9; d++) {
                    for (int f = 0; f <= 9; f++) {
                        for (int e = 0; e <= 9; e++) {
                            int tmp = a * 110000000 + b * 1000000 + c * 100000 + d * 11000 + e * 101 + f * 10;
                            vec.push_back(tmp);
                        }
                    }
                }
            }
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans[n-1] << endl;
    return ;
}
```



---


# [ABC161D] Lunlun Number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc161/tasks/abc161_d

正の整数 $ X $ が以下の条件を満たすとき、 $ X $ はルンルン数であると言います。

- $ X $ を(leading zeroなしで)十進数表記した際に、隣り合うどの $ 2 $ つの桁の値についても、差の絶対値が $ 1 $ 以下

例えば、 $ 1234 $ , $ 1 $ , $ 334 $ などはルンルン数ですが、 $ 31415 $ , $ 119 $ , $ 13579 $ などはルンルン数ではありません。

正の整数 $ K $ が与えられます。小さい方から $ K $ 番目のルンルン数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ 10^5 $
- 入力はすべて整数である。

### Sample Explanation 1

小さい方から $ 15 $ 番目までのルンルン数を順に並べると、 $ 1 $, $ 2 $, $ 3 $, $ 4 $, $ 5 $, $ 6 $, $ 7 $, $ 8 $, $ 9 $, $ 10 $, $ 11 $, $ 12 $, $ 21 $, $ 22 $, $ 23 $ ですので、答えは $ 23 $ です。

### Sample Explanation 4

答えが $ 32 $ ビット符号付き整数の範囲に収まらない可能性があるので注意してください。

## 样例 #1

### 输入

```
15```

### 输出

```
23```

## 样例 #2

### 输入

```
1```

### 输出

```
1```

## 样例 #3

### 输入

```
13```

### 输出

```
21```

## 样例 #4

### 输入

```
100000```

### 输出

```
3234566667```

# 题解

## 作者：SpeedStar (赞：9)

## 算法分析
这个问题可以用队列来解决。首先，开一个空队列，并将1~9这9个数依次压入队列。然后执行以下操作$k$次：
1. 弹出队首元素，并将它赋给$x$；
2. 如果$x\ mod\ 10 \ne 0$，则将$10x+(x\ mod\ 10)-1$压入队列；
3. 将$10x+(x\ mod\ 10)$压入队列；
4. 如果$x\ mod\ 10 \ne 9$，则将$10x+(x\ mod\ 10)+1$压入队列。

在第$k$次出队列的数将会是第$k$个$Lunlun$数。


## C++代码
```cpp
#include <iostream>
#include <queue>
#define int long long

using namespace std;

signed main() {
	int k;
	cin >> k;
	
	queue<int> q;
	for (int i = 1; i <= 9; i++) q.push(i);
	while (!q.empty()) {
		int x = q.front(); q.pop(); k--;
		if (k == 0) {
			cout << x << '\n';
			break;
		}
		
		for (int y = (x % 10) - 1; y <= (x % 10) + 1; y++) {
			if (y < 0 || y > 9) continue;
			q.push(x * 10 + y);
		}
	}
	
	return 0;
}
```


---

## 作者：AmamiyaYuuko (赞：5)

题目大意：给出 $k$，求第 $k$ 小的数 $a$ 且满足 $a$ 中相邻两位的差不超过 $1$。

考虑用队列存下所有的 $a$，最开始时将 $1 \sim 9$ 存入队列，然后每次处理队首。

容易发现，我们只需要末尾的数的大小就可以从当前数求出下一个数可能的结果。

设当前数为 $x$，$x \bmod 10 = k$

分别将 $10x + k - 1, 10x + k, 10x + k + 1$ 存入队列即可。

注意舍去 $k - 1 < 0$ 和 $k + 1 > 9$ 的情况。

别忘了开 LL。

代码：

```cpp
std::queue<LL> q;
int k;

int main() {
    for (int i = 1; i <= 9; ++i)    q.push(i);
    read(k);
    for (int i = 1; i < k; ++i) {
        LL a = q.front();
        int dig = a % 10;
        q.pop();
        if (dig != 0)   q.push(a * 10 + dig - 1);
        q.push(a * 10 + dig);
        if (dig != 9)   q.push(a * 10 + dig + 1);
    }
    printf("%lld\n", q.front());
    return 0;
}
```

其实这题暴力 dfs 可过。。

---

## 作者：ix35 (赞：3)

不会所有题解里 $O(K)$ 那种做法，写一个数位 DP 题解，是 $O(\log^2 N)$ 的（$N$ 是最大位数，大概是 $10$）。

考虑二分答案，转化成计算 $N$ 以内有多少个 Lunlun Number。

这个基本学过数位 DP 的都会做，设 $dp(i,j)$ 表示最高位为 $j$ 的 $i$ 位数中有几个 Lunlun Number，转移大概就是从 $dp(i-1,j+k)$ 到 $dp(i,j)$，其中 $k\in\{-1,0,1\}$。

然后计算的过程中就按照数位 DP 的套路从高位到低位卡，卡到某个前缀已经不是 Lunlun Number 了就直接 return。

注意一下前导 $0$，dp 过程中 $0$ 也要用于判定 Lunlun Number，但在计算答案时，前导 $0$ 不影响 Lunlun Number 判定。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=20;
ll k,l,r,len,dig[MAXN],dp[MAXN][MAXN],g[MAXN];
ll chk (ll x) {
	len=0;
	while (x) {
		dig[++len]=x%10;
		x/=10;
	}
	ll ans=g[len];
	for (int j=1;j<dig[len];j++) {ans+=dp[len][j];}
	for (int i=len-1;i>=1;i--) {
		for (int j=dig[i+1]-1;j<=min(dig[i]-1,dig[i+1]+1);j++) {if (0<=j&&j<=9) ans+=dp[i][j];}
		if (abs(dig[i]-dig[i+1])>1) {break;}
	}
	return ans;
}
int main () {
	scanf("%lld",&k);
	for (int i=0;i<=9;i++) {dp[1][i]=1;}
	g[1]=1;
	for (int i=2;i<=11;i++) {
		g[i]=g[i-1];
		for (int j=1;j<=9;j++) {g[i]+=dp[i-1][j];}
		dp[i][0]=dp[i-1][1]+dp[i-1][0];
		for (int j=1;j<=8;j++) {dp[i][j]=dp[i-1][j-1]+dp[i-1][j]+dp[i-1][j+1];}
		dp[i][9]=dp[i-1][8]+dp[i-1][9];
	}
	l=1,r=1e11;
	while (l<r) {
		ll mid=(l+r)>>1;
		if (chk(mid)-1>=k) {r=mid;}
		else {l=mid+1;}
	}
	printf("%lld\n",l-1);
	return 0;
}
```



---

## 作者：Meatherm (赞：2)

观察到 $K\leq 10^5$，并且第 $10^5$ 个符合要求的数也仅 $10^9$ 级别，于是考虑模拟。

设我们已经求出第 $x$ 个符合要求的数，现在要求第 $x+1$ 个，第 $x$ 个符合要求的数是 $\overline{a_1a_2a_3...a_n}$。

如果存在 $1<i\leq n$ 满足 $|a_{i-1}-(a_i+1)|\leq 1$ 且 $a_i<9$，则将 $a_i$ 增加 $1$，并重置所有 $i<j\leq n$ 的 $a_j$ 为 $\max\{a_{i}-(j-i),0\}$，即可得到第 $x+1$ 个符合要求的数。

如果满足 $a_1<9$，则将 $a_1$ 增加 $1$，并按照上面的方法重置其余位，即可得到第 $x+1$ 个符合要求的数。

如果上述两个条件均不满足，则第 $x+1$ 个数为 $\overline{100...0}$（$n$ 个 $0$）。

每次模拟的复杂度可以近似看作常数，总复杂度为 $O(K)$。

```cpp
# include <bits/stdc++.h>
# define rr register
const int N=100010;
int size;
int a[N];
int k;
int main(void){
	scanf("%d",&k);
	size=1,a[1]=1;
	for(rr int i=2;i<=k;++i){
		for(rr int j=size;j>=1;--j){
			if((j>1&&a[j]<a[j-1]+1&&a[j]<9)||(j==1&&a[j]<9)){
				++a[j];
				for(rr int k=j+1;k<=size;++k){
					a[k]=std::max(0,a[k-1]-1);
				}
				goto ENd;
			}
		}
		++size;
		a[1]=1;
		for(rr int j=2;j<=size;++j){
			a[j]=0;
		}
		ENd:;
	}
	for(rr int i=1;i<=size;++i){
		printf("%d",a[i]);
	}
	return 0;
}
```

---

## 作者：iiawaKL (赞：1)

这题不说了，一题简单的dfs。

我们只要dfs出所有数，然后排序，最后输出，就很简单了。

So easy.

但这题就是要考验细心。如果你打错了一个字母就会报零。

 _Code->_ 
 
```
#include<bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
#define forn(i,a,b) for(int i=a;i<=b;i++)
#define INF 2147483647
#define LLINF 9223372036854775807
using namespace std;
int k;
int sum=0;
set<string> t1;
vector<string> v;
void dfs(string s){
	if(t1.find(s)==t1.end());
	else return ;
	t1.insert(s);
	v.push_back(s);
	if(s.size()==10)return ;
	if(s[s.size()-1]!='0')dfs(s+(char)(s[s.size()-1]-1));
	dfs(s+s[s.size()-1]);
	if(s[s.size()-1]!='9')dfs(s+(char)(s[s.size()-1]+1));
}
inline bool cmp(string x,string y){
	if(x.size()<y.size())return 1;
	if(x.size()==y.size()&&x<y)return 1;
	return 0;
}
int main(){
	cin>>k;
	for(char c='1';c<='9';c++){
		string t="";
		t+=c;
		dfs(t);
	}
	int sum=0;
	sort(v.begin(),v.end(),cmp);
	cout<<v[k-1]<<endl;
	return 0;
}

```


---

## 作者：fighter (赞：0)

比赛的时候被降智了……

其实这就是个模拟题。不过我写的方法好像挺麻烦的。

这题只要求$10^5$个数，所以我们可以一个一个枚举。具体的方法就是从个位开始，从低到高逐位确定。

我们维护一个指针，同时记录目前的最高位。每次操作，把指针指向的位置+1，然后判断一下是否满足条件。

如果不满足，由于我们是从低到高确定，所以就尝试调整下一位，然后把之前的所有位置变成符合要求的最小值（也就是一个从高到低递减的序列），然后把指针指向1重新构造。

有一些小细节需要注意，可以参考代码。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define MAX 500005
using namespace std;

int n;
int a[15];

int main(){
    cin>>n;
    int i = 1, now = 1;
    while(n){
        a[i]++;
        if(a[i] > 9 || (a[i] > a[i+1]+1 && i+1 <= now) || (i > 1 && a[i] > a[i-1])){
            while(a[i] > 9 || (a[i] > a[i+1]+1 && i+1 <= now) || (i > 1 && a[i] > a[i-1])) a[i+1]++, i++;
            now = max(now, i);
            for(int j = i-1; j >= 1; j--){
                a[j] = max(a[j+1]-1, 0);
            }
            i = 1;
        }
        n--;
    }
    int j = 10;
    while(!a[j]) j--;
    for(int i = j; i >= 1; i--){
        cout<<a[i];
    }
    puts("");

    return 0;
}

```

---


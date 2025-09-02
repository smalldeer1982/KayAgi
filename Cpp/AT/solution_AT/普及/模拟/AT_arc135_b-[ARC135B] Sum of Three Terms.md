# [ARC135B] Sum of Three Terms

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc135/tasks/arc135_b

項数 $ N $ の整数列 $ S\ =\ (S_1,\ \ldots,\ S_N) $ が与えられます。 項数 $ N+2 $ の整数列 $ A\ =\ (A_1,\ \ldots,\ A_{N+2}) $ であって、次の条件を満たすものが存在するか否かを判定してください。

- 任意の $ i $ ($ 1\leq\ i\leq\ N+2 $) に対して $ 0\leq\ A_i $ が成り立つ。
- 任意の $ i $ ($ 1\leq\ i\leq\ N $) に対して、$ S_i\ =\ A_{i}\ +\ A_{i+1}\ +\ A_{i+2} $ が成り立つ。

存在する場合には、そのようなものをひとつ出力してください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 3\times\ 10^5 $
- $ 0\leq\ S_i\leq\ 10^9 $

### Sample Explanation 1

以下のように、任意の $ i $ ($ 1\leq\ i\leq\ N $) に対して $ S_i\ =\ A_i\ +\ A_{i+1}\ +\ A_{i+2} $ が成り立つことが確認できます。 - $ 6\ =\ 0\ +\ 4\ +\ 2 $。 - $ 9\ =\ 4\ +\ 2\ +\ 3 $。 - $ 6\ =\ 2\ +\ 3\ +\ 1 $。 - $ 6\ =\ 3\ +\ 1\ +\ 2 $。 - $ 5\ =\ 1\ +\ 2\ +\ 2 $。

## 样例 #1

### 输入

```
5
6 9 6 6 5```

### 输出

```
Yes
0 4 2 3 1 2 2```

## 样例 #2

### 输入

```
5
0 1 2 1 0```

### 输出

```
No```

## 样例 #3

### 输入

```
1
10```

### 输出

```
Yes
0 0 10```

# 题解

## 作者：Union_Find (赞：1)

~~这题我们充分发扬人类智慧。~~

首先，我们发现了一个好玩的，设 $a_i$ 表示答案序列，那么 $S_{i+1}-S_i=a_{i+3}-a_i$。如果这样的话，相当于我们将 $a_i$ 分成了三种，就是 $i \bmod 3 = 1$，$i \bmod 3 = 2$ 和 $i \bmod 3 = 0$。这三部分基本上是互不影响的，并且每个部分的差是不会变的。

所以我们可以先令 $a_1=a_2=a_3=0$，先求出其它 $a_i$。但是题目要求 $a_i \ge 0$，所以我们要让每个部分加上这个部分的最小值的相反数，就可以保证所有数都是正数且最小。注意要特判如果这个部分所有数都大于 $0$ 就不用改。

为什们要 $a_i$ 最小呢？因为三个部分有一个要求，就是要 $a_1+a_2+a_3=S_1$。当 $a_i$ 最小时，如果 $a_1+a_2+a_3 > S_1$，就说明无解，输出 `No`。如果 $a_1+a_2+a_3$ 在最小的时候小于 $S_1$，就可以让 $a_3$ 加上这个差值（其实$a_1$ 和 $a_2$ 也可以）。然后按照正确的 $a$ 数组的前三项求出其他项输出即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 300005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n = rd(), s[N], a[N], ma, mb, mc;
int main(){
	for (int i = 1; i <= n; i++) s[i] = rd();
	for (int i = 1; i < n; i++){
		a[i + 3] = a[i] + s[i + 1] - s[i];
		if (i % 3 == 1) ma = min(ma, a[i + 3]);
		if (i % 3 == 2) mb = min(mb, a[i + 3]);
		if (i % 3 == 0) mc = min(mc, a[i + 3]);
	}
	a[1] = -ma, a[2] = -mb, a[3] = -mc;
	if (a[1] + a[2] + a[3] > s[1]) return puts("No"), 0;
	a[3] = s[1] - a[1] - a[2];
	puts("Yes");
	for (int i = 1; i < n; i++) a[i + 3] = a[i] + s[i + 1] - s[i], cout << a[i] << " ";
	cout << a[n] << " " << a[n + 1] << " " << a[n + 2] << "\n";
	return 0;
}

```

---

## 作者：loser_seele (赞：1)

设答案的前两项为 $ a,b $，不难发现答案有周期性：$ x_i+a,x_i+b,x_i-a-b $，这个是显然的。而 $ x_i $ 可以直接通过差分计算。

于是问题转化为了：给定 $ c_1,c_2,c_3 $，求一组合法解 $ a,b $，满足 $ c_1 \leq a,c_2 \leq b,a+b \leq c_3 $，显然为了满足条件 $ 3 $ 应该贪心使得 $ a=c_1,b=c_2 $，如果不满足条件则显然无解，否则这就是一组合法解。

对于所有的位置暴力计算，时间复杂度 $ \mathcal{O}(n) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,a[N];
long long s[3],mn[3],b[N];
signed main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
    	scanf("%d",&a[i]);
    if(n==1)
    	puts("Yes"),printf("0 0 %d\n",a[1]),exit(0);
    for(int i=1;i<n;i++)
    	s[i%3]+=a[i+1]-a[i],mn[i%3]=min(mn[i%3],s[i%3]);
    b[1]=-mn[1],b[2]=-mn[2],b[3]=-mn[0];
    if(b[1]+b[2]+b[3]>a[1]) 
    puts("No"),exit(0);
    puts("Yes");
    b[1]+=a[1]-b[1]-b[2]-b[3];
    for(int i=1;i<n;i++)
    	b[i+3]=b[i]+a[i+1]-a[i];
    for(int i=1;i<=n+2;i++) 
    printf("%lld ",b[i]);
}
```


---

## 作者：Lele_Programmer (赞：0)

# AT_arc135_b 题解

## 思路

$$
\because S_i = a_i + a_{i+
1} + a_{i+2}, S_{i+1} = a_{i+
1} + a_{i+2} + a_{i+3}
$$

$$
\therefore S_{i+1}-S_i = a_{i+3}-a_i
$$

因此只需要确定 $a_1,a_2,a_3$ 的值，后面的所有值就都可以确定了。

分别以下标 $1,2,3$ 为起点，可以发现每次往后 $3$ 个位置的增量成链式分布，且互不影响。对于每一条链，找出起点所能够填的最小的自然数，使得链中每一个数都为大于 $0$。对 $3$ 条链都这样做一遍，如果初始 $a_1+a_2+a_3>S_1$，则无解，因为这三个起点的值都不能减少。将其中任意一者不断自增，直到 $a_1+a_2+a_3=S_1$，输出 $a$ 序列即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
};

using namespace IO;

const int N=300005;
const int inf=2.1e9;

int n;
int s[N],c[N];
i64 a[N];

int main() {
    read(n);
    _rep(i,1,n) read(s[i]);
    _rep(i,1,n-1) c[i]=s[i+1]-s[i];
    _rep(i,1,3) {
        int cur=c[i];
        int mn=c[i];
        int j=i;
        while (j<=n) {
            j+=3;
            cur+=c[j];
            mn=min(mn,cur);
        }
        a[i]=max(-mn,0);
    }
    if (a[1]+a[2]+a[3]>s[1]) {
        puts("No");
        return 0;
    }
    puts("Yes");
    a[1]+=s[1]-(a[1]+a[2]+a[3]);
    _rep(i,1,n) {
        a[i+3]=a[i]+c[i];
        writesp(a[i]);
    }
    writesp(a[n+1]);
    writesp(a[n+2]);
    return 0;
}
```

---


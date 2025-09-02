# Blue-Red Permutation

## 题目描述

有 $n$ 个数，每个数是红色或蓝色。你可以进行无限次操作（也可以 $0$ 次），每次操作你可以：

1. 把一个蓝色的数 $-1$ 。
2. 把一个红色的数 $+1$ 。

问是否能将这 $n$ 个数变成 $1$ 到 $n$ 的排列，是就输出 `YES` ，否则 `NO` 。

## 说明/提示

$1 \le T \le 10^4$ ，$1 \le n \le 2 \times 10^5$ ， $-10^9 \le a_i \le 10^9$ ，$\sum n \le 2 \times 10^5$ 。

## 样例 #1

### 输入

```
8
4
1 2 5 2
BRBR
2
1 1
BB
5
3 1 4 2 5
RBRRB
5
3 1 3 1 3
RBRRB
5
5 1 5 1 5
RBRRB
4
2 2 2 2
BRBR
2
1 -2
BR
4
-2 -1 4 0
RRRR```

### 输出

```
YES
NO
YES
YES
NO
YES
YES
YES```

# 题解

## 作者：SxEe (赞：7)

### 这道题比较简单，贪心就可以解决
# 题目翻译：
给一个长度为 $n$ 的整数 $a$ 数组。数组的元素可以不同，也可以相同。

数组的每个元素都是蓝色或红色的。共有两种操作：

- 选择一个蓝色元素并将其值减少 $1$。

- 选择一个红色元素并将其值增加 $1$。

问是否存在一种步骤，使最后的数组有且仅有 $1$ 到 $n$ 的数字？

### 输入格式：

有多组测试数据。

第一行输入一个 $t(1\le t \le 10^4)$ 表示共有 $t$ 组数据

对于每一组数据，共有 $3$ 行。

第一行一个整数 $n$ 表示数组的长度。

第二行共有 $a$ 个数，表示数组的每一个数。

第三行一个字符串，表示 $a$ 数组中每一个数的颜色（ $R$ 表示红色， $B$ 表示蓝色）。

### 输出格式：

共 $t$ 行，每行输出一个字符串 “YES” 或 “NO”，表示是否能组成满足题意的数组。

# 简单易懂的思路：
维护两个数组 $red$ 和 $blue$ 分别表示红色和蓝色的元素。

因为我需要求得一个只有 $1$ 到 $n$ 数字的数组，所以显然可以想到：

把 $red$ 从大到小排列、$blue$ 从小到大排列；如果满足题意，必定存在：

- $red$ 的第 $i$ 项满足 $\le n-i+1$。
- $blue$ 的第 $i$ 项满足 $\ge i$。

这里简单说明一下原因：

举个例子：假如数组 $blue$ 排序后是 $2,3,3,3$。

我们可以把第一项 $2$ 减到 $1$ ，第二项 $3$ 减到 $2$，第三项不变。

此时第四项 $3\gt 4$ 不满足上面的结论，因为 $3$ 无法减到 $4$ ，所以这个序列无法达到要求。红色同理。

# Code：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int q,n,a[200005],red[200005],blue[200005];
char b[200005];
int main(){
	cin>>q;
	while(q--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		cin>>b+1;
		int rl=0,bl=0;
		for(int i=1;i<=n;i++){//将每一个元素按颜色分开 
			if(b[i]=='R'){
				rl++;
				red[rl]=a[i];
			}else{
				bl++;
				blue[bl]=a[i];
			}
		}
		sort(red+1,red+rl+1); 
		sort(blue+1,blue+bl+1);
		bool o=true;
		for(int i=1;i<=bl;i++){
			if(blue[i]<i)o=false;
		}
		for(int i=rl;i>=1;i--){
			if(red[i]>n-(rl-i))o=false;//n-(rl-i)相当于降序排列 
		}
		if(o)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
}
```


---

## 作者：Ninelife_Cat (赞：4)

### 题目大意

给出一个长度为 $n$ 的整数数组 $a$，数组中每个元素都只可能是红蓝两种颜色之一，每一次操作：

- 可以选择数组中一个颜色为蓝色的元素并让它的值 $-1$。
- 可以选择数组中一个颜色为红色的元素并让它的值 $+1$。

问能否在若干次操作之后使整个数组成为一个长度为 $n$ 的排列。

### 思路

既然红色元素只能增加它的值，蓝色元素只能减少它的值，那么可以考虑对于蓝色元素，从小到大填满排列的前半段，而对于红色元素则从大到小填满排列的后半段。

如果出现一个蓝色元素比它应该填的位置上的数还要小，或是一个红色元素比它应该填的位置上的数还要大的不合法情况，那就直接判无解。

感觉上面那些话比较绕的话，那就看看代码帮助理解吧。

### 核心代码

```cpp
#define ri register
#define pb push_back
#define int long long
const int N=2e5+10;
int t,n,a[N];
char s[N];
inline bool Cmp(int x,int y) {return x>y;}
signed main()
{
	cin>>t;while(t--)
	{
		cin>>n;
		for(ri int i=1;i<=n;++i)
			cin>>a[i];
		cin>>s+1;
		vector<int> R,B;//存两种颜色元素的值
		for(ri int i=1;i<=n;++i)
			if(s[i]=='R') R.pb(a[i]);
				else B.pb(a[i]);
		sort(R.begin(),R.end(),Cmp);//红色元素从大到小排序
		sort(B.begin(),B.end());//蓝色元素从小到大排序
		for(ri int i=0;i<R.size();++i)
			if(R[i]>n-i) {cout<<"NO\n";goto end;}
		for(ri int i=0;i<B.size();++i)
			if(B[i]<i+1) {cout<<"NO\n";goto end;}
		cout<<"YES\n";end:;
	}
	return 0;
}
```

---

## 作者：引领天下 (赞：2)

非常简单的贪心。考虑从 $1\sim n$ 枚举。

将蓝色的数字和红色的数字分别维护，每次找对应组中最小的数字尝试用掉（最优性显然）。

这里提一个容易犯的错误（会导致`WA on #2`，事实上我就是这个傻逼问题调一晚上没调出来）：

**如果两组中都有可用数字，一定要优先使用蓝色组的（因为 $i$ 较大时较小的蓝色组中数字可能就没法用了），千万不要想什么类似于用最接近 $i$ 的数字去凑 $i$ 之类的迷惑策略。**

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005];
string s;
multiset<int>dc,ic;//dc中存的是蓝色组中的数字，ic中存的是红色组中的数字
//tips:显然是要开可重集的（不过没注意到这个点的怕是样例都过不了吧？）
int main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        cin>>s;
        ic.clear(),dc.clear();
        for(int i=0;i<n;i++)if(s[i]=='B')dc.insert(a[i+1]);else ic.insert(a[i+1]);
        bool flag=1;
        for(int i=1;i<=n&&flag;i++){
            auto x=(dc.size()?*dc.begin():0),y=(ic.size()?*ic.begin():n+1);
            if(x<i&&y>i){cout<<"NO\n";flag=0;continue;}//蓝色组中最小的数字都<i，那么这个蓝色组中的最小数字必然不会被用上（因为1~i-1都处理过了），红色组中最小数字又同时>i意味着i是无法凑成的。
            if(x>=i)dc.erase(dc.begin());//优先使用蓝色组中数字
            else ic.erase(ic.begin());
        }
        if(flag)cout<<"YES\n";
    }
    return 0;
}
```

---

## 作者：老官童鞋gogo (赞：1)

[博客体验更佳](http://laoguantx.nov.vin/cf1607d-blue-red-permutation-%e9%a2%98%e8%a7%a3/.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1607D)

---

## 题解

### 题目强调与分析

翻译本题：给出一串长度为 $n$ 的字符串，其中只包含 "$B$" ， "$R$" 两种字符，分别表示蓝色和红色，每一个字符还附有一个值，对于每次操作，你可以选择其中一个字符，对它的值进行以下两种修改：

1. 如果颜色是红色，可以通过一次操作将它的值 $+1$ ；
2. 如果颜色是蓝色，可以通过一次操作将它的值 $-1$ ；

求：是否存在一种方案，将整个序列的值修改为 $1$~$n$ 的排列（不考虑顺序）。共 $T$ 组数据（对于部分多组数据题目，要记得初始化变量、数组）。

### 思路分析

这道题目我第一眼看成是用线段树做法（个人理解，未使用代码验证正确性），将一对字符和值看作是一个不等式，例如 "$R$-$5$" ，会被记作 $x \ge 5$ ， "$B$-$3$" ，会被记作 $x \le 3$ ，然后分别在区间 $[5,n]$ 和区间 $[1,3]$ 范围 $+1$ ，最后将线段树上所有的叶子节点拿出来排序，如果排序的结果为单调递增，则输出`YES`，否则输出`NO`。这种方法时间复杂度为 $O(n \log n)$ ，常数很大，代码写起来很麻烦。

另外一种更优的做法，先将输入的字符与值根据颜色不同分类，对蓝色与红色的数组分别维护，对分类后的数组从小到大排序，从第小数开始枚举，如果当前的蓝色数组能够取到符合要求的数，就优先取蓝色的，为什么？根据贪心，红色的值只会变大不会变小，蓝色的值只会变小不会变大，所以蓝色的值越小，红色的值越大，它们所能修改到的数越少。因此对于一些小数，我们尽量用蓝色数组中的更小的值转化而来，这样会使这些数字发挥更大的作用，因为那些较大的数不能用蓝色数组中较小的值取到，反观红色，亦是如此。所以若是数字从小到大枚举，需要优先选取蓝色数组中的值。这钟方法，时间复杂度为 $O(n \log n)$ ，复杂度主要来自于排序。

既然主要复杂度来自于排序，那么我们可以继续在排序上优化。本题 $1\le n \le 2 \times 10^5$ ，数据不大，所以可以使用桶排序，但是 $−10^9 \le a_i \le 10^9$ ，没有关系，因为我们要求的是 $1$~$n$ 的排列，对于超过这个范围的数据可以提前处理掉，例如：

- 蓝色数组中值小于 $1$ 的与红色数组中值大于 $n$ 的，只要存在，就可以直接输出`NO`。
- 蓝色数组中大于 $n$ 的值能够变换到 $1 \sim n$ 中的任意值，它与蓝色数组中为 $n$ 的值是等价的。红色数组中小于 $1$ 的值能够变换到 $1 \sim n$ 中的任意值，它与红色数组中为 $n$ 的值是等价的。可以将它们分别处理为与其等价的结果。

如此，时间复杂度降为 $O(n)$ 。

---

## 代码

本题只使用了时间复杂度为 $O(n \log n)$ 的做法。

```c++
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>
using namespace std;
#define LL long long
#define uLL unsigned long long
#define reg register
#define PI acos(-1.0)
#define pb(x) push_back(x)
#define mp(a,b) make_pair(a,b)
#define fi first
#define se second
#define pr(x) cerr<<#x<<"="<<(x)<<endl
#define pri(x,lo) {cerr<<#x<<"={";for (int ol=0;ol<=lo;ol++)cerr<<x[ol]<<",";cerr<<"}"<<endl;}
#define inf 100000000
#define N 1000
#define M 1000001
template<class T>inline void read(T &x)
{
    x=0;register char c=getchar();register bool f=0;
    while(!isdigit(c))f^=c=='-',c=getchar();
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
    if(f)x=-x;
}
template<class T>inline void print(T x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar('0'+x%10);
}
int t,a[M],b[M],r[M];
int main()
{
	read(t);
	while(t--)
	{
		int n,lenr=0,lenb=0;
		char c;
		read(n);
		for(int i=1;i<=n;i++)
		{
			read(a[i]);
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%c",&c);
			if(c=='R')
				r[++lenr]=a[i];
			else
				b[++lenb]=a[i];
		}
		sort(b+1,b+1+lenb);
		sort(r+1,r+1+lenr);
		int i=0,j=0;
		while(1)
		{
			if(i==lenb&&j==lenr)
			{
				break;
			}
			if(i<lenb&&j<lenr)
			{
				if(b[i+1]>=i+j+1)
					i++;
				else if(r[j+1]<=i+j+1)
					j++;
				else
					break;
			}
			else if(j==lenr)
			{
				if(b[i+1]>=i+j+1)
					i++;
				else
					break;
			}
			else if(i==lenb)
			{
				if(r[j+1]<=i+j+1)
					j++;
				else
					break;
			}
		}
		if(i==lenb&&j==lenr)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}

```

---

若其他方法有误，请指出。

---

## 作者：BootsH (赞：1)

贪心题。

## 分析

1. 蓝色的数只能减，红色的数只能加。

2. 没有规定操作次数的多少。

## 思路

根据以上两点，我们可以得出贪心策略：若能够排成一个 $1$ 至 $n$ 的排列，则有一种方法，使得任意蓝色的数比任意红色的数小。

简单证明：

设一个红色的数为 $r$，蓝色的数为 $b$，且 $r < b$，那么我们可以增加 $r$ 的值，变成原来 $b$ 的值；且减少 $b$ 的值，变成原来 $r$ 的值。所以这样下来，（如果可以排出 $1$ 至 $n$ 的排列）我们可以得出一种方案，使得所有蓝色的数都比任意红色的数小。

所以，我们把蓝色和红色的数从小到大排序。

对于每一个蓝色的数（设为 $b_{i}$），如果 $b_{i} < i$，那么一定不能排成（$bi < i$，无论怎么减也减不成功的），直接输出 `NO` 即可。

对于每一个红色的数（设为 $r_{i}$），如果 $r_{i} > i+lenb$（因为这里，$ri$ 在排列中真正的位置是 $i$ 加上蓝色数的个数），那么也一定不能排成。理由大致同上。直接输出 NO 即可。

如果对于所有的 $b_{i}$ 都有 $b_{i} \geq i$，对于所有的 $r_{i}$ 都有 $r_{i} \leq i+lenb$，那么可以排成，输出 YES。

## 代码

快读快写操作等略，看 [这里](https://www.luogu.com.cn/paste/2i2fp17n)

`iget` 为输入 `int` 类型数。

`swln` 为输出 字符串字面量 且换行。

```cpp

#include <algorithm>

namespace Solution
{
    using namespace AKA;
    using IO::gc; using IO::pc; 
    using IO::iget; using IO::ipr; using IO::iwsp; using IO::iwln;
    using IO::llget; using IO::llpr; using IO::llwsp; using IO::llwln;
    using IO::ullget; using IO::ullwsp; using IO::ullwln;
    using IO::spr; using IO::swsp; using IO::swln;


    constexpr int maxn = 2e5 + 5;

    int b[maxn], r[maxn], a[maxn];

    void real_main()
    {
        using IO::iaget;
        int n = iget();
        for (int i = 1; i <= n; ++i)
        {
            a[i] = iget();
        }
        char c;
        while ((c = gc()) < 'A' || c > 'Z') {}
        int i = 0, j = 0, k = 0;
        while (c >= 'A' && c <= 'Z') 
        {
            if (c == 'B')
            {
                b[++j] = a[++i];
            }
            else  
            {
                r[++k] = a[++i];
            }
            c = gc();
        }
        std::sort(b + 1, b + j + 1);
        std::sort(r + 1, r + k + 1);
        for (i = 1; i <= j; ++i)
        {
            if (b[i] < i) 
            {
                return swln("NO");
            }
        }
        for (i = 1; i <= k; ++i)
        {
            if (r[i] > i + j)
            {
                return swln("NO");
            }
        }
        return swln("YES");
    }


    void main(void)
    {
        #ifndef ONLINE_JUDGE
            std::ifstream cin("main.in");
            std::ofstream cout("main.out");
            IO::inbuf = cin.rdbuf(); IO::outbuf = cout.rdbuf();
        #else
            std::ios::sync_with_stdio(false);
            using std::cin; using std::cout;
            #if __cplusplus >= 201103L
                cin.tie(nullptr); cout.tie(nullptr);
            #else
                cin.tie(NULL); cout.tie(NULL);
            #endif
            IO::inbuf = cin.rdbuf(); IO::outbuf = cout.rdbuf();
        #endif


        int general_q = iget();
        while (general_q--)
        {
            real_main();
        }


        #ifndef ONLINE_JUDGE
            cin.close(); cout.close();
        #endif
    }
} // namespace Solution

```

---

## 作者：Madefaker (赞：1)

##### D. Blue-Red Permutation

题目大意：

对于多组数据 $(1 \leq t \leq 10^4)$ 给定一个长度为 $n(1 \le n \le 2 \times 10^5)$ 的数组 $a(-10^9 \le a_i \le 10^9)$，并给 $\forall a[i]$ 指定了红蓝色，接下来可以做无限次操作：如果涂了红色每次可以 $+1$，如果涂了蓝色每次可以 $-1$。问是否有办法将 $a$ 变成一个 $1 \sim n$ 的排列。

------

思路：

由于可以做无限次操作，我们可以直接认为涂了红色的数字 $i$ 可以变成 $[i,+∞)$（下文我们称作用域为它），否则可以变成 $(-∞,i]$。进一步地，由于我们只需要考虑变成 $1 \sim n$ 的情况，那么红色 $i$ 的作用域为 $[i,n]$，蓝色 $i$ 的作用域为 $[1,i]$。（如果不存在这个区间自然是 `NO` 了）

于是，题目就转化成了每一个数字在自己的作用域下选择一个位置，最终要求选中的是 $1 \sim n$ 中的每一个数字。接下来发现一个重要的结论：**如果有 $j$ 个数字的作用域中只包含 $j-1$ 及以下个数字，那么无法实现题意。**为什么呢？因为如果按照题目要求，这 $j$ 个数字需要各自找一个位置，并且两两不同。而这 $j$ 个数字的作用域总共都没有 $j$ 个数，如何做到这一点？所以不能。另外，如果对于任意 $j$ 个数字都有其作用域包含的数字不少于 $j$ 个，并且不存在没有作用域的数字，那么可以实现题意。

------

实现：

那么我们按照这个结论往下想（这提供了一个思路，但并没有充足的时间来实现枚举）。由于我们的数组有红有蓝，作用域有的靠左有的靠右没有那么容易考虑，所以分开来考虑。把红色的数字递增排列，蓝色的数字**递减**排列。这把所有的作用域分为靠左和靠右两部分，为接下来的操作提供极大便利。

遍历红色的数字，如果第 $j(0-indexed)$ 个数字小于等于 $j$，那么证明这 $j$ 个数字的作用域中只包含**前** $j-1$ 及以下个数字。遍历蓝色的数字（是倒着排的），如果第 $j$ 个数字大于 $n-j$，那么证明这 $j$ 个数字的作用域中只包含**后** $j-1$ 及以下个数字，举个例子：

如果红色的数字前几个分别为 $[1,2,2]$，那么由于第三个 $2$ 小于等于其 $index=2$，这三个数的作用域只包含前 $2$ 个数字。$[1,3,3]$ 则可以。

如果蓝色的数字前几个分别为 $[5,4,4]$，$n=5$，那么由于第三个 $4$ 大于 $n - index=3$，这三个数的作用域只包含后 $2$ 个数字。$[5,4,2]$ 则可以。

走一遍之后还是可以的话，那么就成立了（因为在这个过程中如果有的数字没有作用域，那么已经被排除了）这样我们得到了一个时间复杂度 $O(n \log n)$ 的算法。

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int n;
		cin >> n;
		vector<int> a(n);
		for (int j = 0; j < n; j++) {
			cin >> a[j];
		}
		string s;
		cin >> s;
		vector<int> b, r;
		for (int j = 0; j < n; j++) {
			if (s[j] == 'B') {
				b.push_back(a[j]);
			}
			if (s[j] == 'R') {
				r.push_back(a[j]);
			}
		}
		int B = b.size();
		int R = r.size();
		bool ok = true;
		sort(b.begin(), b.end());
		for (int j = 0; j < B; j++) {
			if (b[j] <= j) {
				ok = false;
			}
		}
		sort(r.begin(), r.end(), greater<int>());
		for (int j = 0; j < R; j++) {
			if (r[j] > n - j) {
				ok = false;
			}
		}
		if (ok) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
}
```



---

## 作者：gheescoo (赞：1)

### **原版题面**
[Codeforces Round #753 (Div. 3) D.Blue-Red Permutaion](https://codeforces.com/contest/1607/problem/D)

------------


### **题目大意**

有两个数列 B 和 R。B 中元素只能减，R 中元素只能增，这样的增增减减，然后组成一个全排列（就是从 $1$ 到 $n$ 都有）。如果能，输出 yes；如果不能，输出 no。


------------
### **解决方案**

很显然如果有一个元素 $0$，他的颜色为 Blue，那么很显然不能组成全排列。因为无论 $-1$ 减去多少都不会落在 $[1, n]$ 上（减去负数的靠边站）。同理一个元素 $n + 1$ ，颜色为 Red，这也是不可以的。

分析其中的一个样例：（样例的第4组数据）

R: $1, 3, 3$ &emsp; B: $1, 3$

目标 permutaion （原谅我不知道这个的汉语是什么）的 $1$ 应该在 B 中取，取出来 $1$，然后减去 $0$，得到 $1 - 0 = 1$。那么 permutation 的 $2$ 呢？

也应该优先从 B 中取。

#### 理由如下：
 
 >假如我们的 permutation 是这样得来的（以角标标注其原数字的颜色）：
 
 >$1_{B}, 2_{B}, 3_{R}, 4_{B}, 5_{R}$。
 
 >看到 $3_{R}$ 和 $4_{B}$，设 $4_{B}$ 的原数字为 $x$，则 $x \ge 4$。
 
 >$\therefore x > 3$，即 $3$ 可以由原本得到 $4$ 的元素得来。
 
 >同理 $4$ 可以由原本得到 $3$ 的元素得来。
 
 >则 permutation 可以为 $1_{B}, 2_{B}, 3_{B}, 4_{R}, 5_{R}$。
 
 >因而根据冒泡排序的原理，对于任意一个可行的数组，可行的方案都可以化成“前面是 B，后面是 R”的形式。
 
 >如果连这种形式都不满足，那么他肯定就不可以通过加加减减成为一个可行的 permutation。
 
 >##### 证毕


------------

于是思路很明了了，先排序，再检查。

------------
### **~~拿来主义~~**


```cpp
#include <cstdio>
#include <algorithm>

//快读
#include <cctype>
auto read_d = [](void) -> int
{
    int x = 0; int f = +1;
    char ch = getchar();
    while(!isdigit(ch) && ch != '-' && ch != '+') ch = getchar();
    if(ch == '-')
    {
        f = -1;
        ch = getchar();
    }else
    if(ch == '+') ch = getchar();
    while(isdigit(ch))
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
};
auto read_c = [](void) -> char
{
    char ch = getchar();
    const char l = 0x21, r = 0x7f;
    while(ch < l || ch >= r) ch = getchar();
    return ch;
};
//快读

std::pair<bool, int> brp[200005]; //pair 的排列先以第一个元素为基准，再排列第二个元素。
void Blue_Red_Permutation()
{
    register int i;
    const int n = read_d();
    for(i = 1; i <= n; ++i) {
        brp[i].second = read_d();
    }
    for(i = 1; i <= n; ++i) {
        brp[i].first = (read_c() == 'R'); //Red 应该靠后走。
    }
    auto legal = [&i] { //真·合法
        return brp[i].first? (brp[i].second <= i) : (brp[i].second >= i);
    };
    std::sort(brp + 1, brp + n + 1);
    for(i = 1; i <= n; ++i) {
        if(!legal()) return (void)(printf("NO\n"));
    }
    return (void)(printf("YES\n"));
}

int main()
{
    int t = read_d();
    while(t--)
    {
        Blue_Red_Permutation();
    }
    return 0;
}
```

---

## 作者：ZZQF5677 (赞：0)

### 解题思路
首先将红数与蓝数分批成两个数组 $r$ 与 $b$，且别忘了排序，然后记住一点，蓝数只能 $-1$，所以 $b_i$ 如果小于需要变成的数，无论如何都达不到的；红数只能 $+1$，所以如果 $r_i$ 大于需要变成的数，无论如何都达不到的。因为蓝数能够变小，所以小一点的数 $1$ 到 $|b|$ 就让蓝数来组成，大一点的数 $n - |r|$ 到 $n$ 就让红数来组成。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[200005], r[200005], rlen, b[200005], blen;
char s[200005];
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    bool f = 0;
    rlen = 0;
    blen = 0;
    for (int i = 1; i <= n; i++) {
      cin >> s[i];
      if (s[i] == 'R') {
        r[++rlen] = a[i];
      } else {
        b[++blen] = a[i];
      }
    }
    stable_sort(r + 1, r + 1 + rlen);
    stable_sort(b + 1, b + 1 + blen);
    for (int i = 1; i <= blen; i++) {
      if (b[i] < i) {  // 因为蓝数只能 -1，而如果 b_i 小于需要变成的数，无论如何都达不到的。
        f = 1;
      }
    }
    for (int i = 1, j = n - rlen + 1; i <= rlen; i++, j++) {
      if (r[i] > j) {  // 因为红数只能 +1，而如果 r_i 大于需要变成的数，无论如何都达不到的。
        f = 1;
      }
    }
    if (f) {
      cout << "NO\n";
    } else {
      cout << "YES\n";
    }
  }
  return 0;
}
```

---

## 作者：Xhesika_Frost (赞：0)

有的会上升有的也会下降，似乎是很麻烦。但是我们可以换一种考虑的角度。

对于每一个 B 的砖，我们只需要把它们先拼命地加，加到 INF ，对于 R 的砖拼命地减，减到 -INF ，然后开始进行下降和上升。

把相同类型的砖放到一起，然后贪心的进行上升和下降操作。假如 B 的砖一共有
 $x$ 个，我们就试图把 $1-x$ 的数字都用蓝色的砖表示出来, R 的砖同理。
 
如果遇到了不能下降和不能上升的情况，就证明了无解。

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cmath>
#include<stack>
#include<algorithm>
using namespace std;
template<class T>inline void read(T &x)
{
    x=0;register char c=getchar();register bool f=0;
    while(!isdigit(c))f^=c=='-',c=getchar();
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
    if(f)x=-x;
}
template<class T>inline void print(T x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar('0'+x%10);
}
int n;
int t;
int a[200005];int b[200005];
int d[200005];
string s;
int c1,c2;
int main(){
	read(t);
	while(t--){
		read(n);
		c1=0;c2=0;
		for(int i=1;i<=n;++i){
			read(d[i]);
		}
		cin>>s;
		s=' '+s;
		for(int i=1;i<=n;++i){
			if(s[i]=='B') a[++c1]=d[i];
			else b[++c2]=d[i]; 
		}
		sort(a+1,a+c1+1);
		sort(b+1,b+c2+1);
		int f=0;
		for(int i=1;i<=c1;++i){
			if(a[i]>=i){
				continue;
			}else{
				f=1;
				break;
			}
		}
		int l=1;
		for(int i=n-c2+1;i<=n;++i){
			if(i>=b[l]){
				l++;
				continue;
			}else{
				f=1;
			}
		}
		if(f){
			cout<<"No\n";
		}else{
		cout<<"YEs\n";
		}
	}
	return 0;
}
```

---


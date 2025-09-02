# Orac and Medians

## 题目描述

Slime has a sequence of positive integers $ a_1, a_2, \ldots, a_n $ .

In one operation Orac can choose an arbitrary subsegment $ [l       \ldots r] $ of this sequence and replace all values $ a_l, a_{l       + 1}, \ldots, a_r $ to the value of median of $ \{a_l, a_{l +       1}, \ldots, a_r\} $ .

In this problem, for the integer multiset $ s $ , the median of $ s $ is equal to the $ \lfloor \frac{|s|+1}{2}\rfloor $ -th smallest number in it. For example, the median of $ \{1,4,4,6,5\} $ is $ 4 $ , and the median of $ \{1,7,5,8\} $ is $ 5 $ .

Slime wants Orac to make $ a_1 = a_2 = \ldots = a_n = k $ using these operations.

Orac thinks that it is impossible, and he does not want to waste his time, so he decided to ask you if it is possible to satisfy the Slime's requirement, he may ask you these questions several times.

## 说明/提示

In the first query, Orac can't turn all elements into $ 3 $ .

In the second query, $ a_1=6 $ is already satisfied.

In the third query, Orac can select the complete array and turn all elements into $ 2 $ .

In the fourth query, Orac can't turn all elements into $ 3 $ .

In the fifth query, Orac can select $ [1,6] $ at first and then select $ [2,10] $ .

## 样例 #1

### 输入

```
5
5 3
1 5 2 6 1
1 6
6
3 2
1 2 3
4 3
3 1 2 3
10 3
1 2 3 4 5 6 7 8 9 10```

### 输出

```
no
yes
yes
no
yes```

# 题解

## 作者：Meatherm (赞：21)

提供一个赛时想的奇怪做法...

首先要特判一下（样例很良心，全都给出来了）$n=1$ 或没有 $a_i=k$ 的情况。

接下来有三个结论：

1. 相邻的三个数中只要存在任意两个相等，则将它们进行操作后，均会变为那个相等的数。

2. 相邻的两个数进行操作后会变为较小的那个数。

3. 根据结论 1，只要数列中存在两个相邻的 $k$，那么必定是 `Yes`。

我们可以找到两个相邻的且 $\ge k$ 的数，操作它们。容易发现，操作之后，它们仍然 $\ge k$，但变得相等。

然后使用结论 1，不断地进行操作，将某一个 $k$ 的左侧或者右侧修改为 $\ge k$ 的数。

例如 $n=7,k=3$，$a=[3~2~2~2~2~5~4]$：

- 用结论 2 对 $[6,7] $ 进行操作，变成 $[3~2~2~2~2~4~4]$
- 用结论 1 不断地进行操作：
  - 操作 $[5,7]$ 后：$[3~2~2~2~4~4~4]$
  - 操作 $[4,6]$ 后：$[3~2~2~4~4~4~4]$  
  ......

最后，变成 $[3~4~4~4~4~4~4]$，$a_1$ 的右侧有了 $\geq k$ 的数。
  
这个时候就可以用结论 2 制造出两个相邻的 $k$ 了！上面提到过，有了两个相邻的 $k$，必定是 `Yes`。
  
综上，如果存在 $1<i \leq n$ 使得 $a_{i-1} ,a_i\geq k$，则答案是 `Yes`。

但考虑下面这种情况：

$n=7,k=3$，$a=[2,3,2,2,4,2,5]$。按照上面的做法，是 `No`，但应该是 `Yes`，因为可以操作 $[5,7]$ 得到相邻的 $\geq k$ 的数。

于是还有一种情况：存在 $1<i<n$ 使得 $a_{i-1},a_{i+1} \geq k$，则答案是 `Yes`。

```cpp
# include <bits/stdc++.h>
# define rr
const int N=100010,INF=0x3f3f3f3f;
int a[N];
int n,k;
int T;
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}

int main(void){
	T=read();
	while(T--){
		n=read(),k=read();
		bool flag=false;		
		for(rr int i=1;i<=n;++i){
			a[i]=read();
			if(a[i]==k){
				flag=true;
			}			
		}
		if(!flag){ // 数列中没有 k
			puts("No");
			goto End;
		}		
		if(n==1&&a[1]==k){ // n = 1
			puts("Yes");
			goto End;
		}

		for(rr int i=2;i<n;++i){
			if(a[i-1]>=k&&a[i+1]>=k){ // 情况 2
				puts("Yes");
				goto End;
			}
		}

		for(rr int i=2;i<=n;++i){
			if(a[i]>=k&&a[i-1]>=k){// 情况 1
				puts("Yes");
				goto End;
			}
		}
		puts("No");
		End:;
	}
	return 0;
}

```

---

## 作者：KellyFrog (赞：13)

显然一个数比$k$大多少和一个数比$k$小多少没有关系。

如果能够找到一个位置$i$，满足$a_i=k$，$a_{i+1}\ge k$或$a_{i-1}\ge k$，那么显然应该输出`yes`，因为可以把上面两个改成$k$，之后一直改就行了。

如果存在$i$，$a_i,a_{i+1}\ge k$或$a_i,a_{i+2}\ge k$，那么我们可以将包括$i$的区间推平成$\ge k$的一个数。我们只要不断平推，一直推平到一个$a_{i-1}=k$或$a_{i+1}=k$的位置，之后就取$i=i-1$或$i=i+1$，就满足了上面一条，就能够输出`yes`了。

记得特判$n=1$和$a$中没有$k$的情况（这个样例真的良心）

$\text{code}:$

```cpp
#include <iostream>

using namespace std;

const int MAXN = 1e5 + 5;

int n, k, t;

int a[MAXN];

void Solve() {
	cin >> n >> k;
	bool hasK = false;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		if(a[i] == k) {
			hasK = true;
		}
	}
	if(!hasK) {
		cout << "no" << endl;
		return;
	}
	if(n == 1) {
		cout << "yes" << endl;
		return;
	}
	for(int i = 1; i < n; i++) {
		if(a[i] >= k && a[i + 1] >= k) {
			cout << "yes" << endl;
			return;
		}
	}
	for(int i = 1; i < n - 1; i++) {
		if(a[i] >= k && a[i + 2] >= k) {
			cout << "yes" << endl;
			return;
		}
	}
	cout << "no" << endl;
}

int main() {
	cin >> t;
	while(t--) {
		Solve();
	}
	return 0;
}
```

---

## 作者：Daidly (赞：4)

考虑将 $a_i<k$ 赋值为 $-1$，$a_i\ge k$ 赋值为 $1$。问题转化成了求最大子段和是否大于 $0$。

因为保证了选取的子段内 $>k$ 的元素个数大于等于 $<k$ 的元素个数，使得对选取子段进行操作结果必然是全部大于等于 $k$。

而若仅有的 $k$ 也在子段中，并不用担心会被消除。因为子段中必定有子区间满足其区间和等于 $0$ 且包含 $k$，使 $k$ 成为中位数。

- 以上方法已经可以解决本题。

但是若采用：将 $a_i<k$ 赋值为 $-1$，$a_i=k$ 赋值为 $0$，$a_i>k$ 赋值为 $1$ 的方法，不好判定问题。

首先若子段中无 $k$，上述规定满足题意的条件是子段和大于 $0$；而有 $k$ 的情况下又需要满足子段和大于等于 $0$ 的条件；并且若 $k$ 仅有一个且在子段中，而子段和大于等于 $0$，并不能保证 $>k$ 的数的个数大于等于 $<k$ 的数的个数，需要特判，还有最大子段和相同的情况，极为麻烦。

第一种方法代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

const int MAXN=1e5+5;
int t,n,k,a[MAXN],b[MAXN];

int main(){
	t=read();
	while(t--){
		n=read(),k=read();
		bool f=0;
		for(int i=1;i<=n;++i){
			a[i]=read();
			if(a[i]>=k)b[i]=1,f=1;
			else b[i]=-1;
			b[i]+=b[i-1];
		}
		if(!f){puts("no");continue;}
		if(n==1){puts("yes");continue;}
		f=0;
		int minn=0;
		for(int i=2;i<=n;++i){
			minn=min(minn,b[i-2]);
			if(b[i]>minn){
				f=1;break;
			}
		}
		if(f)puts("yes");
		else puts("no");
	}
	return 0;
}
```



---

## 作者：e4fsrc2e4fsrc2 (赞：3)

## [Orac and Medians](https://www.luogu.com.cn/problem/CF1349B)
## 思路分析
很明显有一个性质：
1. 如果数列里面有两个 $k$ 是相邻的，那么一定可以构造出来（取与这连续两个  $k$ 相邻的第三个数，这三个数的中位数必定为 $k$，循环以往，可以构造出来）。

2. 如果没有 $k$，那么一定构造不出来。

上面两种情况都不满足，说明有 $k$，但是 $k$ 不相邻。

假设数列为 $a$，对于一个 $k$，我们发现，如果 $\exists i$ 满足 $a_i\ge k,a_{i-1}\ge k$。

那么就可以把 $k$ 旁边的数构造成 $k$，如：
```
k=3
 3 2 2 2 4 5
->3 4 4 4 4 4
->3 3 4 4 4 4
```
还有一种情况，就是 $\exists i$，满足 $a_{i-1}\ge k,a_{i+1}\ge k$ 
也是可以的，如:
```
k=3
 3 2 2 4 2 5
->3 4 4 4 4 4
->3 3 4 4 4 4
```
所以我们就得到了最后的判断规则：

当有 $k$ 但是不连续的时候，判断这个位置有没有 $i$ 满足上面的条件，就可以构造出相邻的 $k$。

PS：需特判 $n=1$ 时，$a_1$ 是否等于 $k$。
## AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
const int N=3e5+1;
string s;int n,cnt;ll a[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>s;
	for(R i=0; i<n; i++){
		a[cnt]++;
		while(i<n&&s[i]==s[i+1])a[cnt]++,i++;
		cnt++;
	}
	cout<<(ll)n*(n-1)/2-2*n+a[0]+a[cnt-1]+cnt-1;
	return 0;
}

```

---

## 作者：Link_Space (赞：3)

题目的意思很简洁：给你一个序列，你每次可以选择一个区间，让这个区间内的所有数全部变成这个区间的中位数，你需要回答最后是否能够将整个序列全部变为 k 。

一开始的时候我有些懵，往数据结构方面想发现并没有什么数据结构能够解决这道题。后来换了种思考，才发现这道题其实很简单。

首先你需要判断的是这个序列中本来存不存在 k 这个数，如果不存在的话那么这个序列无论如何也不能全部变为 k ，因为你不能将序列的数改变成一个序列里并没有的数，所以如果没有 k 的话直接输出 no 即可。

接下来就思考如何应对有k的情况，首先如果序列长度为 1 的话这个数就是 k ，直接输出 yes 即可。

否则遍历整个序列，假设这个序列为 s ，如果存在一个 i 满足 $i\leqslant n $ && $s[i] \leqslant k ,s[i+1] \leqslant k$ ，那么这个序列就可以整个变为 k ，或许有的同学会不理解，这是为什么呢？

我们假设这个序列中为 k 的数在 $s[i+1]$ 的后面，那么我们可以直接将 $s[i] , s[i+1] ,s[i+2]$ 全部变为一个大于等于 k 的数,然后又将 $s[i+1],s[i+2].s[i+3]$ 全部变为一个大于等于 k 的数，这样一格一格地向后推，直到碰到 k ,假设 k 这个数在序列的位置为 x 那么我们就可以将 $s[x],s[x-1]$ 变成k，然后将 $s[x-1],s[x-2]$ 全部变为 k ，以此类推。

对于 k 这个数在 $s[i]$ 的前面的情况也同理。

同时如果 如果存在一个 i 满足 $i\leqslant n $ && $s[i] \leqslant k ,s[i+2] \leqslant k$ 那么我们也可以将这个序列全部变为 k ，因为我们可以将 $s[i],s[i+1],s[i+2]$ 全部变为一个大于 k 的数，然后同上。

这样我们就可以直接秒掉这道题拉！

以下是代码：

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
const int N = 1e5 + 5;
int a[N];
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        bool flag = false;
        bool already = false;
        for (int i = 1; i <= n;i++)
        {
            scanf("%d",&a[i]);
            if(a[i]==k)
                flag = true;
        }
        if(!flag)
        {
            puts("no");
            continue;
        }
        if(n==1)
        {
            puts("yes");
            continue;
        }
        for (int i = 1; i < n;i++)
        {
            if(a[i]>=k&&a[i+1]>=k)
            {
                puts("yes");
                already = true;
                break;
            }
        }
        if(already)
            continue;
        for (int i = 1; i < n - 1;i++)
        {
            if(a[i]>=k&&a[i+2]>=k)
            {
                puts("yes");
                already = true;
                break;
            }
        }
        if(already)
            continue;
        puts("no");
    }
    return 0;
}
```


---

## 作者：InfSauf (赞：2)

拿到题目首先找一下规律，发现并不是很好找规律，于是我们采用数学归纳法。

1. 当 $n=1$ 时，若 $a_i=k$ 则输出 yes 这就不用证明了罢。

2. 当 $n=2$ 时，若 $min\{a_{i},a_{i+1}\}=k$ 输出 yes。
	
    根据题目，中位数是排序后第 $\left \lfloor \frac{1+|l|}{2} \right \rfloor $ 个数，所以当数列只有两个元素，且 $k$ 是最小的那个数，则第 $\left \lfloor \frac{1+2}{2} \right \rfloor =1$ 个数就是 $k$，输出 yes。
    
    这里解释一下，如果中位数是题目中的第 $\left \lfloor \frac{1+|l|}{2} \right \rfloor $ 小数，那么在某些情况下不能正确输出答案，例如输入的数列为 $2,2,3$，且 $k=3$ 的情况下，正确输出应该是 no，而如果是第 $\left \lfloor \frac{1+|l|}{2} \right \rfloor $ 小数，则应该输出 yes，因为在该数列中第 $\left \lfloor \frac{1+|3|}{2} \right \rfloor =2$ 小的数是 $3$ 则一定能变为 $\{3,3,3\}$。

3. 当 $n=3$ 时,设数列 $\{a_1,a_{2},a_{3}\}$，此时我们令 $a_i \ge k$ 的
数为 $+$，$a_i <k$ 的数为 $-$。

	- 令 $a_1 < k,a_{2} \ge k,a_{3} \ge k$，则原数列可以表示为 $\{-,+,+\}$ 若 ${a_2,a_3=k}$ 则 ${a_2,a_3}$ 都是该数列的中位数，故可以将数列变为 $\{k,k,k\}$ （目标数列）的形式。
   - 若 $a_2,a_3 < k,a_1 =k$，则原数列可以表示为$\{+,-,-\}$，不难发现，该数列中的中位数显然小于 $k$，所以不能将原数列变为目标数列。
   - 若数列中所有元素都大于等于 $k$，保证存在至少 $1$ 个 $k$ 则一定可以变为目标数列。
    
我们根据上文得出推论：若原数列中，存在至少一个长度为3的子段中含有至少两个数是大于等于 $k$ 的则说明可以变为目标数列。

推广至 $n$ 个数，设数列为 $\{a_1,a_2,\cdots,a_n\}$ 且该数列中存在至少一个 $k$ 则同样令 $a_i \ge k$ 的数为 $+$，$a_i <k$ 的数为 $-$，假设该数列有 $6$ 个数，$n=4$，数列为 $\{1,1,4,5,1,4\}$ 从左往右检查长度为 $3$ 的子段，依次是 $\{1,1,4\},\{1,4,5\},\{4,5,1\},\{5,1,4\}$，不难发现，有三个子段中的元素存在至少两个数是大于等于 $4$ 的故可以变为目标数列。
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int t;
bool can = 0;
int a[N], b[N];
void sol(int n){
	int num = 0;
	for(int j = 1; j <= n - 2; j++){
		num = b[j] + b[j + 1] + b[j + 2];
		if(num >= 2){
			cout << "yes\n";
			return;
		}
	}
	cout << "no\n";
}
int main(){
	cin >> t;
	for(int i = t; i --> 0;){
		int n, k;
		cin >> n >> k;
        can = 0;
		for(int j = 1; j <= n; j++){
			cin >> a[j];
			b[j] = (a[j] >= k) ? 1 : 0;
			if(a[j] == k){
				can = 1;
			}
		}
		if(!can){
			cout << "no\n";
			continue;
		}
		if(n == 1 && a[1] == k){
			cout << "yes\n";
			continue;
		}
		if(n == 2 && min(a[1], a[2]) == k){
			cout << "yes\n";
			continue;
		}
		sol(n);
		//cout << "no\n";
	}
}
```


---

## 作者：bsdsdb (赞：1)

题意：给定 $\{a_n\}$ 和 $k$，一次操作 $(l,r)$ 定义为 $a_{[l,r]}\gets\operatorname{median}(a_{[l,r]})$，问能不能若干次操作后将 $a$ 中全部数变成 $k$。

提示：

1. 如果没有 $k$，或者 $n=1$，答案会是什么？
2. 如果有连续的两个 $k$，答案是什么？
3. 怎么用两个连续的 $\ge k$ 造出情况 2？
4. 什么情况可以造出情况 3？

（提示 1 解答）没有 $k$ 肯定不行，因为根据中位数定义有 $\operatorname{mid}(b)\in b$，不能无中生有。如果 $n=1$，那么答案显然就是 $[a_1=k]$。（提示 2 解答）如果有 $a_i=a_{i+1}=k$ 那么操作 $(i,i+2),(i,i+3),\cdots,(i,n),(i-1,n),(i-2,n),\cdots,(1,n)$ 即可。（提示 3 解答）如果有 $a_i=k,a_j,a_{j+1}\le k$，那么不妨设 $i\le j$，先操作 $(j-1,j+1),(j-2,j+1),\cdots,(i+1,j+1)$ 使得 $a_{i+1}\ge k$，再操作 $(i,i+1)$ 造出情况 2。否则，考虑最近的两个 $\ge k$，如果他们的距离为 2，即有子串形如 $[\ge k,<k,\ge k]$，可以对这个子串操作造出情况 3；否则，所有 $\ge k$ 的距离都大于 2，那么无论怎么取子串他们的中位数都小于 $k$，不可能操作出所需情况。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
random_device rndv;
mt19937 rd(rndv());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
const double eps = 1e-8;
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const ll MAXN = 1e5 + 5;

ll n, k, a[MAXN];

void init() {
    fill_n(a + 1, n, 0);
}
int mian() {
    read(n), read(k);
    for (ll i = 1; i <= n; ++i) {
        read(a[i]);
    }
    if (n == 1 && a[1] == k) {
        puts("yes");
        return 0;
    }
    bool hk = 0;
    for (ll i = 1; i <= n; ++i) {
        if (a[i] == k) {
            hk = 1;
        }
    }
    if (!hk) {
        puts("no");
        return 0;
    }
    for (ll i = 1; i <= n; ++i) {
        if ((a[i] >= k && a[i + 1] >= k) || (a[i - 1] >= k && a[i + 1] >= k)) {
            puts("yes");
            return 0;
        }
    }
    puts("no");
	return 0;
}

int main() {
	ll T;
	read(T);
	while (T--) {
		init();
		mian();
	}
	return 0;
}

;             ;;;;;;;;;;;         ;
;                      ;         ; ;
;                    ;          ;   ;
;                   ;          ;     ;
;                 ;           ;;;;;;;;;
;               ;            ;         ;
;              ;            ;           ;
;;;;;;;;;;;   ;;;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2000}$
---
### 解题思路：

首先可以知道的是，当整个数组连 $k$ 都不存在的时候，一定无解。那么接下来的所有文字都是建立在 $k$ 在序列中存在的前提下的。

考虑一些特殊的情况：如果这其中出现了两个连续的 $k$，那么直接由这两个往外拓展，每一次在这两个数的外围选择一个，就一定将中位数设置为 $k$，这样就能将所有的数都变成 $k$。

否则考虑转化为这种情况。将整个数组分成三种数大于 $k$ 的数，小于 $k$ 的数和 $k$。如果一个比 $k$ 大的数出现在了 $k$ 的旁边，那么选择这两个数就能将问题转化为之前的情况。而如果 $k$ 旁边有一个比 $k$ 小的数，再旁边又是比 $k$ 大的数，那么同样能转化为之前的情况。间隔更长就不行了。

从上面这些特殊情况可以发现，真正妨碍最后结果其实那些没有 $k$ 大的数，因为选择的时候中位数会向小的一侧偏移。那么，更一般地，考虑不比 $k$ 小的数的拓展。从上面的特殊情况可以发现当两个不比 $k$ 小的数的距离不超过 $2$ 的时候，就能够向外拓展到整个序列，那么也就一定能拓展到某一个 $k$ 的旁边。

综上所述，只要序列中有 $k$，而且存在两个不比 $k$ 小的数的距离不超过 $2$，就一定有解，否则一定无解。

---
如果对这个结论还不放心，可以将不满足上述的序列抽象为任意一个不比 $k$ 小旁边有两个连续的比 $k$ 小的数，那么无论怎么取区间都是不能使得中位数不比 $k$ 小的，也就是无解。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int n,T,a[100005],k,last,flag;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		flag=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i]==k)flag=1;
		}
		if(flag==0){
			printf("no\n");
			continue;
		}
		if(n==1){
			if(flag)printf("yes\n");
			else printf("no\n");
			continue;
		}
		last=0;flag=0;
		for(int i=1;i<=n;i++){
			if(a[i]>=k){
				if(last!=0&&i-last<=2)flag=1;
				last=i;
			}
		}
		if(flag)printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
```


---

## 作者：ctq1999 (赞：1)

## 题意简述

$T$ 组询问。

对于每一组询问：

有 $n$ ，$k$ 和 $n$ 个正整数 $a_1,a_2,\dots,a_n$ 。

你可以进行无限次操作：

* 把区间 $[l, r]$ 的数变为这个区间的中位数。

* 中位数指这个区间第 $\lfloor\frac{r-l+2}{2}\rfloor$ 个数，即 $a_{l+\lfloor\frac{r-l+2}{2}\rfloor-1}$。

如果能使 $[1,n]$ 内的所有数变为 $k$ ，输出 `Yes` ，否则输出 `No` 。

## 题解

一道很有意思的题。

首先明确各种维护中位数什么的操作不可取，至少本题目的不是。

好好观察，手玩一下样例。

发现一个结论：

* 如果两个相等的数 $x$ 下标绝对值差在 $[1, 2]$ ，那么所有数可以变为 $x$ 。

这个结论当时我和其他神仙都想出来了，但是不知道这结论如何应用。

当时我的思考过程：

* 既然有这个结论，那么说明一段区间进行标号，大于 $k$ 的标 $1$，等于标 $0$ ，下于标 $-1$ ，如果一段区间和为 $0$ 或 $1$，那么就说明中位数是 $k$ ，那么全部都可以变为 $k$ 。

* 考虑前缀和，但是这个区间的左右端点枚举是 $O(n^2)$ 的啊

* 想不出来……

~~然鹅我当时没打，只是看了一下 1B~~

最后还是 **@Froggy** 神仙给出了标算。

其实不一定要以 $k$ 拓展。

约定 $x$ 为正整数。

观察一个区间：

$$[k-x,k-x,k-x,k,k-x,k-x,k-x]$$

$$(e.g:[3,3,3,5,3,3,3])$$

可以发现，不管怎么样，都不能 `Yes` 。

若是：

$$[k+x,k+x,k,k+x,k+x,k+x] $$

$$(e.g:[7,7,4,7,7,7])$$

那么任意取 $k$ 周围一个数，排序后一定为 $[k,k+x]$ ，中位数为 $k$，即 `Yes` 。

推论：

* 若可以使k相邻的数变成 $k+x$ ，那么一定为 `Yes` 。

* 否则一定为 `No`。

判断k相邻的数能否变成 $k+x$，只需要判断k的一侧能否全部变成 $k+x$ 。

判断k的一侧能否全部变成 $k+x$ ，只需要判断有无两个大于等于 $k$ 的数下标绝对值差在 $[1, 2]$。（能组成一个符合区间 $[l, r]$，即区间中大于等于 $k$ 的个数大于等于 $\lfloor\frac{r-l+2}{2}\rfloor$ 的话，那么相邻的或间隔一个的一定有，抽屉原理）

**完**

## 代码

直接上 **@Froggy** 的代码了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define N 100010
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
int n,k,T,a[N];
int main(){
	T=read();
	while(T--){
		n=read(),k=read();
		bool ok=true;
		int gg=0;
		for(int i=1;i<=n;++i){
			a[i]=read();
			if(a[i]^k)ok=false;
			else ++gg;
		}
		if(!gg){
			printf("no\n");
			continue;
		}
		for(int i=1;i<n;++i){
			if(a[i]>=k){
				if(a[i+1]>=k||(i<n-1&&a[i+2]>=k)){
					ok=true;
					break;
				}
			}
		}
		printf(ok?"yes\n":"no\n");
	}
	return 0;
}
```


---

## 作者：RockyYue (赞：0)

### 1349B

给定 $k,a_{1\dots n}$，问是否可以通过若干次操作，将 $a_{1\dots n}$ 全部变为 $k$，一次操作定义为选取 $(l,r)$，将 $a_{l\dots r}$ 全部变为其中位数（长度偶数则取较小一个），要求 $O(n)$。

### Sol

- 原序列中不存在 $a_i=k$，则无解；否则，从扩散的角度想。

- 若一个长度 $\ge 2$ 的连续段全为 $k$，则每次向一侧扩散一位，可以扩散到整个序列，需要看能否得到这样的连续段。

- 其充要条件：一段长度 $\ge 2$ 的区间 $[l,r]$，满足其中至少 $\lfloor\frac{r-l+1}{2} \rfloor$ 个数 $\le k$，下面分析 `NO` 条件。
  - 知道：原序列具体数值对操作并无影响，只需知道其与 $k$ 的大小关系（下记 $a_i=0,1,2$ 分别表示 $<,=,>k$）。
  - 分析特殊情况：$a_i=1$，若其相邻为非 $0$，这两位操作可得。进一步地，与其距离 $\le 2$ 的位（$a_{i-2,i-1,i+1,i+2}$）必须均为 $0$。
- 操作中，不一定自始至终围绕 $a_i=1$，也可以得到 $2$ 连续段，再扩散到 $1$ 相邻位，故与每个 $2$ 距离 $\le 2$ 的位同样需要为 $0$。
- 到这里得到 `NO` 必要条件，由于这样的构造下任一个区间中 $0$ 数量 $\ge$ $1$ 和 $2$ 总和，充分性亦满足。

---

## 作者：一只小咕咕 (赞：0)

刷一些 CF2000，进行一个录的记。

### 思路记录
1. 首先观察到数列里的数不能凭空产生，所以初始序列必须含 $k$。
2. 由于两个数的中位数是较小的那个，所以只要有一个与数列里的 $k$ 相邻且比 $k$ 大的数，就可以扩展到整个序列。
3. 发现可以把第二条推广一下，不必要和 $k$ 相邻，因为只要有两个相邻的比 $k$ 大的数，就可以进行扩展到与 $k$ 相邻。
4. 问题就来到了如何产生一段长度大于 $1$ 的比 $k$ 大的数列。第三条是一种方法，还有一种就是两个大于 $k$ 的数之间间隔一个任意数。（可以自己造几组样例手玩一下）

至此问题就得到了解决，一组数据时间复杂度 $\mathcal{O(n)}$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
inline int read();
int T;
int n,k,a[N];
int main()
{
	T=read();
	while(T--)
	{
		bool flag=0;
		n=read();k=read();
		for(int i=1;i<=n;i++) a[i]=read();
		if(n==1&&a[1]==k) {puts("yes");continue;}
		for(int i=1;i<=n;i++) if(a[i]==k) flag=1;
		if(!flag) {puts("no");continue;}
		else flag=0;
		for(int i=2;i<=n;i++)
		{
			if(a[i-1]>=k&&a[i]>=k) {puts("yes"),flag=1;break;}
		} 
		if(!flag)
		for(int i=2;i<n;i++)
		{
			if(a[i-1]>=k&&a[i+1]>=k) {puts("yes"),flag=1;break;}
		}
		if(!flag) puts("no");
	}
	return 0;
}

inline int read()
{
	int x=0,f=1;
	char ch;
	ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')
	{
		x=(x<<1)+(x<<3)+(ch&15);
		ch=getchar();
	}
    return x*f;
}


```

---

## 作者：UncleSam_Died (赞：0)

### 解题思路
一个比较显然的结论：
- 若序列中存在一段连续的长度大于 $1$ 的区间，且区间中的数均为 $k$，那么一定可以将整个序列转化为 $k$。

进一步的，我们可以推出，若序列中有一段区间的中位数为 $k$，那么这个序列一定可以全部转化为 $k$。

最后特判 $n=1$ 和序列中没有 $k$ 的情况即可。
### AC 代码
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#define N 100005
#define inf 2e9+7
int n,k,a[N],p[N],ce;
int l[N],r[N],cl,cr;
inline void work(){
    scanf("%d%d",&n,&k);ce=0;
    for(register int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    for(register int i=1;i<=n;++i)
        if(k==a[i]) p[++ce]=i;
    if(!ce){puts("No");return;}
    if(n==1){puts("Yes");return;}
    for(register int i=1;i<=ce;++i){
        int now=p[i];
        if(now>1&&a[now-1]>=k){
            puts("Yes");return;
        }
        else if(now<n&&a[now+1]>=k){
            puts("Yes");return;
        }
    }
    for(register int i=1;i<n;++i)
        if(a[i]>=k&&a[i+1]>=k){
            puts("Yes");return;
        }
    for(register int i=2;i<n;++i)
        if(a[i-1]>=k&&a[i+1]>=k){
            puts("Yes");return;
        }
    puts("No");
}
signed main(){
    int T;scanf("%d",&T);
    while(T--) work();
}
```

---

## 作者：RockyYue (赞：0)

既然中位数的取值与区间长度有关，考虑对于特殊长度的区间是否有特殊性质，有：

- 对连续两个数进行操作，可以将这两个数中较小者变为较小者。
- 连续三个数中若有两个相同，可以将另一个不同的变为这个相同值。
  - 进一步地，若有两个相邻的数相同，可以任意长度地向两边拓展使得这些数与其相同，即若 $a_i=a_{i+1}=x$，则对于任意 $l\le i\le i+1\le r$ 均可以经过若干次操作使得 $a_l=a_{l+1}=\dots =a_r=x$。

同时，我们只需要关心 $k$ 在每段中的排名，于是将所有数分成三类：$>k,=k$ 和 $<k$。

结合以上性质，发现若有 $k$ 和 $>k$ 的数相邻，就可以先对这两个数进行操作得到相邻两个 $k$，再拓展到整个序列即可，考虑在初始 $k$ 两侧的数均 $<k$ 时如何操作使得相邻的数 $>k$，想到从同侧的两个相邻的 $>k$ 的数拓展而来（或者这就是这两个数之一），也只能这样。即只要可以得到两个相邻的 $>k$ 的数，也可以通过若干次操作将整个序列变成 $k$。

总结一下，输出 ```yes``` 有以下两种情况：

1. 初始序列中就有至少 $\lceil \frac{n+1}{2}\rceil$ 个 $k$，只需要一次操作；
2. 否则需要从一个 $k$ 拓展，即序列中存在至少一个 $k$ 且可以得到相邻 $\ge k$（相邻两个 $k$ 直接拓展）。

接下来看什么样的情况可以得到相邻 $>k$，在初始没有的情况下只能操作一个区间 $[l,r]$。因为我们只需要相邻两个，考虑操作长度较小的区间。这里我们只考虑是否存在长度为 $3$ 的区间经过一次操作可以全部 $>k$，这也是 $[l,r]$ 存在的充要条件，整个区间中至少一半 $>k$，则必然有相邻的三位中至少有两个 $>k$。

至此，完成了对输出 ```yes``` 所有情况的判断，复杂度 $O(n)$。

---

## 作者：Pwtking (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1349B)

观察与思考后可得以下结论：

设序列中的一个子区间中**大于等于** $k$ 的个数有 $a$ 个，**小于** $k$ 的个数有 $b$ 个。

- 若 $a>b$，则这个区间可以全部变成大于等于 $k$ 的数

- 若 $b=0$，则一定可以在保证这段区间含 $k$ 的情况下把这段区间全部变成 $k$。

结论 $2$ 证明：考虑一个仅有两个数的序列 $k,k+x$，$x \in[0,inf]$。则其中位数一定为 $k$。所以对于一个除了 $k$ 以外全都大于 $k$ 的序列一定可以反复用这样的方式将其全部变成 $k$。

所以如果这个序列有 $k$ 的情况下，能找到一个子区间使得 $a>b$ 的话，则一定合法。

发现这种子区间只会由形如 $k+x,k-x,k+x$ 或 $k+x,k+x$，$x \in[0,inf]$ 的形式叠加构成。把序列扫一遍即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x7fffffff
const ll maxn=1e5+10;
ll a[maxn];
ll T,n,k;
inline ll in() {
	char a=getchar();
	ll v=0,f=1;
	while (a>'9'||a<'0') {if (a=='-') f=-1;a=getchar();}
	while (a>='0'&&a<='9') {v=(v<<3)+(v<<1)+a-'0';a=getchar();}
	return v*f;
}
inline void write(ll x) {
	if (x>9) write(x/10);
	putchar('0'+(x%10));
} 
signed main(){
	T=in();
	while (T--) {
		n=in(),k=in();a[n+1]=a[n+2]=0;
		ll flag=0,tot=0;
		for (ll i=1;i<=n;++i) a[i]=in();
		for (ll i=1;i<=n;++i) {
			if ((a[i]>=k&&a[i+1]>=k)||(a[i]>=k&&a[i+2]>=k)) tot++;
			if (a[i]==k) flag=1;
		}
		if (!flag||(tot==0&&n>=2)) {puts("no");}
		else puts("yes");
	} 
	return 0;
}
```


---

## 作者：double_wings (赞：0)

# [CF1349B Orac anOrac and Medians](https://www.luogu.com.cn/problem/CF1349B)
## 题意
给定一串序列，每次可以选任意区间使这个区间的值全部变为这个区间的中位数，问可不可以不断通过这种操作使得整个序列变为 k。
## 思路
想象一下，两个数，一个为 k，另一个大于等于 k，那么这两个数都可以变为 k，那我们的目标就是使得区间所有的数都大于等于 k，如果任意连续的三个数中有两个大于等于 k，那么我们就可以通过不断传递的操作使得所有的数大于等于 k。

再特判一下特殊情况，这道题就结束了。

## 代码
```cpp

#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("-funroll-loops")
using namespace std;
using ll=long long;
using ull=unsigned long long;
//#define mid ((l+r)>>1)
//#define len (r-l+1)
//#define ls p<<1
//#define rs p<<1|1
//#define int long long
constexpr int inf=1e9+7;
constexpr int mod=998244353;
//constexpr ll inf=1e18+7;
constexpr int N=100005;
int t;
int n,k;
int a[N];
// char buf[1<<21],*p1,*p2;
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();return x*f;}
void wt(long long x,char ch=0){if(x<0) putchar('-'),wt(-x);else{if(x>=10) wt(x/10);putchar(x%10+'0');}if(ch) putchar(ch);return;}
signed main(){
    //freopen("in.in","r",stdin);
    //freopen("ot.out","w",stdout);
    cin.tie(0);
    cout.tie(0);
    t=read();
    while(t--)
    {
        n=read(),k=read();
        for(int i=1;i<=n;++i)a[i]=read();
        int biao=0;
        for(int i=1;i<=n;++i)
        {
            if(a[i]==k)break;
            if(i==n)
            {
                biao=1;
                break;
            }
        }
        if(n==1&&a[1]==k)
        {
            cout<<"YES"<<'\n';
            continue;
        }
        if(n==1||biao)
        {
            cout<<"NO"<<'\n';
            continue;
        }
        int tot=0;
        for(int i=1;i<n;++i)
        {
            tot=0;
            if(a[i-1]>=k)tot++;
            if(a[i]>=k)tot++;
            if(a[i+1]>=k)tot++;
            if(tot>=2)
            {
                cout<<"YES"<<'\n';
                break;
            }
        }
        if(tot<=1) cout<<"NO"<<'\n';
    }
    // cout<<clock()/(double)CLOCKS_PER_SEC;
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```

---

## 作者：GFyyx (赞：0)

## 题目分析
题目保证所有询问中 $n$ 的和不超过 $10^5$。

如果 $t=1,n=10^5$ 还是能把暴力 $\Theta(n^2)$ 算法卡掉的。

## 解题思路
不难发现，序列 $a$ 中如果不含有元素 $k$，肯定不满足条件。

设 $w,x,y,z \in N$，依据题意，对于 $a$ 中连续两个元素 $k,(k+w)$ 可以都赋值为 $k$。

仔细观察，对于 $a$ 中连续三个元素 $(k+x),(k-y),(k+z)$ 可以都赋值为大于 $k$ 的三个元素。

延伸一下，序列 $a$ 对于任意连续的三个元素，如果其中有两个大于 $k$，那么该序列 $a$ 满足题设。

## AC 代码（附有注释）
$\Theta(n)$ 的时间复杂度，代码不长，先自己写一下。
```cpp
#include <iostream>
#include <string.h>
using namespace std;
int n,k,a[114514];
short isb[114514];
inline bool solve(){
	memset(isb,0,sizeof isb);
	cin >> n >> k;
	int pos=0;
	for(register int i=1; i<=n; i++){
		cin >> a[i];
		if(a[i]>k) isb[i]=1;
		if(a[i]==k) pos=i,isb[i]=1;
	}
	if(!pos) return 0;//不存在k
	if(n==1) return 1;//特判n为1或2的情况
	if(n==2) return min(a[1],a[2])==k;
	for(register int i=3; i<=n; i++)
		if(isb[i]+isb[i-1]+isb[i-2]>=2) return 1;//滑动查找满足题意的区间
	return 0;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;cin >> t;
	while(t--){
		if(solve()) cout << "YES\n";
		else cout << "NO\n";//别抄
	}
	return 0;
}
```


---

## 作者：52luogu (赞：0)

# [传送门](https://www.luogu.com.cn/problem/CF1349B)
## 题目理解
一道思维题，看看样例思考需要找到怎样的数才能使所有数转换为 $k$。（建议思考 $10$ 分钟以上）
## 思维及结论
首先要满足有 $k$，其次我们~~不难~~发现任意三个连续的数中只要有两个不小于 $k$ 便能推到全 $k$， 即 $ a_i $ 和 $ a_{i-1}$ 均不小于 $k$ 或 $a_{i-1}$ 和 $a_{i+1}$ 不小于 $k$。
不妨设 $a_i$ 和 $a_{i-1}$ 不小于 $k$ 经过操作即可将 $a_i$ 和 $a_{i-1}$ 都可赋值为 $k$。若有连续的 $k$ 也必定可以将所有数变为 $k$。

### 举个栗子
$n = 7$，$k = 2$

一串数 $1,2,2,3,4,5,6$ 可以变成 $2,2,2,3,4,5,6$ 可以继续利用连续的 $2$ 将数串的中位数转化为我们需要的 $2$ 最后使全数列变为 $2$。

$n = 7$，$k = 2$

一串数 $5,2,0,1,3,1,4$ 可以变成 $5,2,3,3,3,3,3$ 最后通过以 $2$ 为中位数变换区间即可使数列全变为 $2$。

## 易错
判断 $a_i$，$a_{i-1}$ 不小于 $k$ 和 $a_{i-1}$，$ a_{i+1}$ 不小于 $k$ 需分两次否则会出问题，需要特判只有一个或两个数的情况。
### 错误示范
```cpp
for(int i=2;i<=n;i++)
	if((a[i-1]>=k&&a[i]>=k)||(a[i-1]>=k&&a[i+1]>=k))//这里 a[i+1] 会出现问题
  	fl2=true;
```

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mn=1e6+5;
int n,a[mn],w,k; 
int main(){
	ios::sync_with_stdio(0);//运行更快
	cin.tie(0);
	cin>>w;
	while(w--){
		int n;
		bool fl1=false,fl2=false;//fl1 判断是否满足有 k，fl2 判断是否满足任意三个相邻数中有两者不小于 k
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]==k) fl1=true;
		} 
		if(n==1&&a[1]==k){//特殊情况
			cout<<"yes\n";
			continue;
		}
		for(int i=2;i<n;i++){
			if((a[i-1]>=k&&a[i]>=k)||(a[i-1]>=k&&a[i+1]>=k))
			{
				fl2=true;
				break;
			}
		}
		if(fl1==true&&fl2==true)//必须同时满足两者才行
		{
			cout<<"yes\n";
		}
		else
			cout<<"no\n";
	}
	return 0;
}

```



---

## 作者：Shirο (赞：0)

### 题意
给定一个序列$A_i$，可以将 $[L,R]$ 变为其 $A [L,R]$ 的中位数，问能否全部变成$k$
### 做法
可以进行一个简单的转换，我们不需要考虑数字的具体大小，只需知道其相对 $k$ 的大小即可。固我们进行如下变换：
$$B_i=\left\{
\begin{aligned}
0\ (A_i<k)\\
1\ (A_i=k)\\
2\ (A_i>k)\\
\end{aligned}
\right.$$
同时我们可以观察到，如果我们的 $1$ 旁边有 $2$ 的话，马上可以拓展到整个数列去，所以本质上来说我们应该要找到在 $B_i=1$ 的两边的 $B_j=2$

所以问题转变为我们找一个长度为 $3$ 的序列，使得其端点的 $B_i$ 大于 $0$

考虑以下情况：

$\{ 1, 0 , 1 \} ,\{1,0,2\},\{2,0,1\}$ 直接采用中位数操作

对于 $\{2,0,2\}$ 我们直接把全部变为 $2$ 然后在和一个相邻的$1$操作一下就能保证有解

故只需保证存在 $B_i=1$ 且 $B_j \times B_i>0 (j-i+1\leq 2)$ 就能有解

特判一下没有 $k$ 和 $n=1$ 的情况

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int maxn=1e5+5;
int a[maxn],n,k,T,b[maxn];
int main()
{
	T=read();
	while(T--)
	{
		n=read(),k=read();
		bool exist=0;
		for(int i=1;i<=n;++i)
		{
			a[i]=read();
			if(a[i]<k)b[i]=0;
			else if(a[i]==k)b[i]=1,exist=1;
			else b[i]=2;
		}
		if(!exist){puts("No");continue;}
		if(n==1){puts("Yes");continue;}
		bool ans=0;
		for(int i=1;i<=n;++i)
		{
			for(int j=i+1;j<=n and j-i<=2;++j)
				if(b[i] and b[j])
					ans=1;
		}
		puts(ans?"Yes":"No");
	}
}
```


---

## 作者：juicyyou (赞：0)

# CF1349B Orac and Factors
## 题目大意：
给定义一个数列 $a$，你每次可以选择一个区间将其中的所有数都变为这段区间的中位数，问能不能使得整个数列都变成一个数 $k$。
## 解法：
本文采取了官方题解的思路。

我们构造一个数列 $b$ 使得：
$$\large{b_i = \left\{\begin{aligned}0\quad a_i < k\\1 \quad a_i = k\\2 \quad a_i > k\end{aligned}\right.}$$
那么问题变为使得整个 $b$ 都变为 $1$。

首先，如果 $b$ 里没有 $1$，那肯定不行，直接输出 NO 。

其次，如果任意一个 $i, j$ 使得 $b_i > 0 , b_j > 0, i < j$ 都有 $j - i > 2$ ，那么显然任意一端区间里 $0$ 都要比 $1$ 多，那所有区间的中位数都是 $0$，肯定不行。

接下来，开始神仙构造。

1. 如果有两个 $1$ 相邻，那么每次选择旁边的一个数组成一个长度为 $3$ 的区间，进行操作，显然可以使得每个数最后都为 $1$ ，所以这样的情况恒成立。
2. 如果有三个相邻的数**排序**后是：$\{0, 1, 2\}$ 或者 $\{0, 1, 1\}$ 或者 $\{1, 1, 2\}$ 或者 $\{1, 2, 2\}$ 一类的，显然可以转换为 1 那么肯定可以。
3. 如果有三个相邻的数**排序**不是 2 ，那么由于不可能性质 2 ，一定存在一个区间是 $\{0, 2, 2\}$ 或 $\{2, 2, 2\}$ 那么只需一次操作将其全部变为 $2$ 然后进行 1操作，最后当有一个 2 与 一个 1 相邻时，再用 2 策略，那么这个问题就解决了。

于是，我们只需要判断两种不可能情况即可。

下面是我的Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 2e5 + 5;
const ll maxm = 1e3 + 5;
inline void qread(){}
template<class T1, class ...T2>
inline void qread(T1 &IEE, T2&... ls){
	register T1 __ = 0, ___ = 1;
	register char ch;
	while(!isdigit(ch = getchar())) ___ = (ch == '-') ? -___ : ___;
	do{
		__ = (__ << 1) + (__ << 3) + (ch ^ 48);
	}while(isdigit(ch = getchar()));
	__ *= ___;
	IEE = __;
	qread(ls...);
	return ;
}
ll n, m;
ll a[maxn];
int main(){
	ll t;
	qread(t);
	while(t--){
		qread(n, m);
		bool p = 0;
		for(int i = 1;i <= n;i++){
			qread(a[i]);
			if(a[i] == m) p = 1;
		}
		if(!p){
			puts("no");
			continue;
		}
		if(n == 1){
			puts("yes");
			continue;
		}
		bool flag = 0;
		for(int i = 1;i <= n;i++){
			if(a[i] < m) continue;
			for(int j = i + 1;j <= min(n, (ll)i + 2);j++){
				if(a[j] >= m) flag = 1;
			}
		}
		if(flag == 1){
			puts("yes");
			continue;
		} else {
			puts("no");
			continue;
		}
		
	}
	return 0;
}
```

上述算法时间复杂度即为 $\mathcal O(n)$， 算上多组数据之后，复杂度即为 $\mathcal O(\sum n)$，可以通过此题。

---

## 作者：VenusM1nT (赞：0)

结论题。  
结论 1：对于 $n>1$，令第 $i$ 个 $a_j\ge k$ 的位置为 $\text{pos}_ i$，若 $\exists \ i$，使得 $\text{pos}_ {i+1}-\text{pos}_ i\le2$，且 $\exists\ i$，使得 $a_i=k$，则有解，反之无解。  
证明：有显然结论 2，若有两个 $k$ 相邻则有解，因为这两个 $k$ 可以通过对旁边的数字取中位数而不断扩张，最后覆盖整个数列。因此解决该问题的关键为能否获得两个相邻的 $k$。  
$\quad\quad\ \  $接下来证明上述结论 1。利用反证法，若两个最近的 $a_i\ge k$ 的数中间有 $\ge2$ 个数（与证题相反），则可以发现，若对这两个最近的 $a_i\ge k$ 取中位数，令区间内 $a_i\ge k$ 的数量为 $x$，$a_i\le k$ 的数量为 $y$，则有 $y\ge x$，则 $k$ 不可能作为中位数出现。同理，扩展至 $3,4,...,n$ 亦成立，则不可能使 $k$ 更多地出现，原题无解。 
虽然题目不要求，但如果满足结论 1 的要求，要如何操作呢？显然，我们直接对满足条件的两个 $a_i\ge k$ 取中位数，若这两个数相邻，则取中位数，得到两个 $k$；若中间隔了一个 $\leq k$ 的数，取中位数，得到三个 $k$，均为结论 2 中的有解。  
此时有一种特殊情况为一些 $\ge k$ 的值在一起，而一个 $k$ 孤立，此时可以让这些 $\ge k$ 的值扩展到 $k$ 的旁边再进行取中位数的操作就可以了。
```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define reg register
#define inl inline
#define int long long
using namespace std;
int n,a[MAXN],k,pos[MAXN],tot;
signed main()
{
	ios::sync_with_stdio(0);
	reg int Time;
	cin>>Time;
	while(Time--)
	{
		tot=0;
		cin>>n>>k;
		reg int cnt=0;
		for(reg int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i]==k) cnt++;
			if(a[i]>=k) pos[++tot]=i;
		}
		if(n==1 && a[1]==k)
		{
			cout<<"yes"<<endl;
			continue;
		}
		if(!cnt || tot==1)
		{
			cout<<"no"<<endl;
			continue;
		}
		reg bool fg=0;
		for(reg int i=1;i<=tot-1;i++)
		{
			if(pos[i+1]-pos[i]<=2)
			{
				fg=1;
				break;
			}
		}
		if(fg) cout<<"yes"<<endl;
		else cout<<"no"<<endl;
	}
	return 0;
}
```

---

## 作者：几何之舞丶 (赞：0)

首先是要特判一下长度为1的区间.


考虑每一个长度为2的区间,可以发现,若这个区间可以变成全是k的数,那么必然其中一个数等于k,另一个数大于k.

考虑每一个长度为3的区间,可以发现,若这个区间可以变成全是k的数,那么必然其中一个数等于k,剩下的两个数中有一个大于k即可.

枚举一下,然后就可以O(TN)搞定了.

代码:
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<algorithm>
#define N 100005
#define INF 0x7fffffff
#define inf 0x3f
#define int long long
#define ll long long
#define lson (now<<1)
#define rson (now<<1|1)
#define pii pair<int ,int >
#define pushup1(now)  tr[now].sum=(tr[lson].sum+tr[rson].sum);
#define pushup2(now)  tr[now].sq=(tr[lson].sq+tr[rson].sq);
using namespace std;
const int mod=100000000;
inline ll read() {
	ll now=0;
	char c=getchar();
	ll f=1;
	while(c<'0'||c>'9') {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		now=(now<<1)+(now<<3)+(c^48);
		c=getchar();
	}
	return f*now;
}
int n,t,m,a[N];
signed main(){
	t=read();
	while(t--){
		n=read();m=read();int len=0;
		memset(a,0,sizeof(a));
		//memset(pos,0,sizeof(pos));
		for(int i=1;i<=n;i++)
		a[i]=read();
		for(int i=1;i<=n;i++){
			if(a[i]==m){
				len++;
			}
		}
		if(len==0){
			puts("no");
			continue;
		}
		if(n==1&&a[1]==m){
			puts("yes");
			continue;
		}
		bool flag=0;
		for(int i=1;i<n;i++){
			if(a[i]>=m && a[i+1]>=m){
				flag=1;break;
			}
			if(a[i-1]>=m && a[i]>=m){
				flag=1;break;
			}
			if(n>2&& a[i]>=m &&a[i-2]>=m){
				flag=1;break;
			}
			if(n>2&& a[i]>=m&&a[i+2]>=m){
				flag=1;break;
			}
		}
		if(flag)
		puts("yes");
		else
		{
			puts("no");
		}
		
	}
//	system("pause");
	return 0;
}
```


---


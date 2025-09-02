# Arithmetic Progression

## 题目描述

Everybody knows what an arithmetic progression is. Let us remind you just in case that an arithmetic progression is such sequence of numbers $ a_{1},a_{2},...,a_{n} $ of length $ n $ , that the following condition fulfills:

 $ a_{2}-a_{1}=a_{3}-a_{2}=a_{4}-a_{3}=...=a_{i+1}-a_{i}=...=a_{n}-a_{n-1}. $ For example, sequences \[1, 5\], \[10\], \[5, 4, 3\] are arithmetic progressions and sequences \[1, 3, 2\], \[1, 2, 4\] are not.

Alexander has $ n $ cards containing integers. Arthur wants to give Alexander exactly one more card with a number so that he could use the resulting $ n+1 $ cards to make an arithmetic progression (Alexander has to use all of his cards).

Arthur has already bought a card but he hasn't written a number on it. Help him, print all integers that you can write on a card so that the described condition fulfilled.

## 样例 #1

### 输入

```
3
4 1 7
```

### 输出

```
2
-2 10
```

## 样例 #2

### 输入

```
1
10
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4
1 3 5 9
```

### 输出

```
1
7
```

## 样例 #4

### 输入

```
4
4 3 4 5
```

### 输出

```
0
```

## 样例 #5

### 输入

```
2
2 4
```

### 输出

```
3
0 3 6
```

# 题解

## 作者：丧黑福造 (赞：3)

## 思维题
------------
本题主要是分类讨论的思想

当$n=1$时，此时一定无解，输出$-1;$

当$n=2$时，最左端和最右端必然有解，此时还需要判断两数之间是否可以插入一个数构成等差数列

当$n\ge3$时，首先从小到大排序，如果可以从中插入一个数（这时一定不是两端），那么两个相邻的数之差$ = $公差的次数会是最多的。只要这个差出现不少于$2$次，这个差就是公差。

 确定公差之后，后面就比较容易了。插入该数的两个相邻数之间的差不可能等于公差，而该数是否合法，可以通过这两个相邻数中较小的一个$+2$倍公差，能否得到较大的数来判断。

 如果插入的数不在中间，那么有可能是无解（输出$0$）或者是从两端插入（输入的序列已经是等差数列）。

  还有一种情况要特别注意，当序列只有$3$个数的时候，并且可以从中插入一个数成为等差数列的情况。此时公差取较小的那个差。例如：$1,2,4$，我们会取$1$作为公差,因为此时可在$2$和$4$之间插入$3$来构成等差数列。
  
 

------------
代码：
```cpp

#include <stdio.h>
#include <algorithm>
using namespace std;
int a[100005];
main(){
    int cnt, n, d, ans, td, td1, c1, c2;
    scanf("%d", &n);
		for (register int i = 1; i <= n; i++) scanf("%d", &a[i]);
        sort (a + 1, a + n + 1);
        d = a[2] - a[1];
        if (n == 1)	puts ("-1");
        else if (a[1] == a[n] && n >= 2)/*常数列*/ printf("1\n%d\n", a[1]);
        else if (n == 2) {
			if ((a[1] + a[2]) % 2)/*判断两数之间是否也可以插入*/  printf("2\n%d %d\n", a[1] - d, a[2] + d);
			else printf("3\n%d %d %d\n", a[1] - d, (a[1] + a[2]) / 2,  a[2] + d);
        }
        else {
			c2 = c1 = 1;
			td1 = a[3]-a[2];
			if (td1 != d) {
				for (register int i = 4; i <= n; i ++){
					int td = a[i] - a[i-1];
					if (td == td1) c2++;
					else c1++;
					if (c1 >= 2 || c2 >= 2) break;//出现次数>=2的差即为整个序列的公差
				}
			}
            if (c2 >= c1 && n >= 3 && d > td1)/*最终确定公差*/ d = td1;
            cnt = 0;
            for (register int i = 2; i <= n; i++) {
			td = a[i] - a[i-1];
			if (d != td) {
				cnt++;
				if ((a[i-1]+a[i]) % 2 || a[i-1]+2*d != a[i]) {
					cnt++;
					break;
                }
            	else ans = a[i-1] + d;
			}
		}
		if (!cnt) printf("2\n%d %d\n", a[1]-d, a[n]+d);//本身已经是等差数列了 
		else if (cnt == 1) printf("1\n%d\n", ans); 
		else puts ("0");//无解 
	}
    return 0;
}

```




---

## 作者：AKPC (赞：1)

### 思路
还是模拟。先排序，然后分类讨论。

$n=1$，则有无限个答案，因为任意两个数字都可以是等差数列。

$n=2$，那么在数列两端放数字是肯定可以的，如果 $2\mid(a_2-a_1)$，那么 $a_1$ 与 $a_2$ 的平均数就是整数，也计入答案。

$n\geq3$，那么处理相邻两个数的差，然后 `map` 存起来，判断这些差的众数，然后看众数在数列出现次数，如果所有数都是众数，那么只能放在两端，如果有一个差不是个，那么只能放差对应的两个数字之间，且需要满足这个不同的差和众数存在两倍关系才能放。

注意如果 $n=3$，而且两个差不一样，需要直接判断两倍关系或者差相等，否则容易出问题。

另外注意，如果答案里出现重复，需要去重之后再输出。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,a[100001],f[100001],t[5],maxn,id=-1,sum,idx=-1,tip;
unordered_map<int,int>mp;
signed main(){
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	if (n==1) {cout<<-1;return 0;}
	sort(a+1,a+n+1);
	if (n==2){
		if (a[2]-a[1]==0) cout<<1<<'\n'<<a[1];
		else if ((a[2]-a[1])%2==0) cout<<3<<'\n'<<a[1]*2-a[2]<<' '<<(a[2]+a[1])/2<<' '<<a[2]*2-a[1];
		else cout<<2<<'\n'<<a[1]*2-a[2]<<' '<<a[2]*2-a[1];
		return 0;
	}
	for (int i=1;i<n;i++){
		f[i]=a[i+1]-a[i];
		if (!mp[f[i]]++) t[++tip]=f[i];
		if (maxn<mp[f[i]]&&mp[f[i]]>=2) maxn=mp[f[i]],id=f[i];
		if (tip>=3) {cout<<0;return 0;}
	}
	if (id==-1){
		if (f[1]==2*f[2]) cout<<1<<'\n'<<f[2]+a[1];
		else if (f[2]==2*f[1]) cout<<1<<'\n'<<f[1]+a[2];
		else cout<<0;
		return 0;
	}
	for (int i=1;i<n;i++){
		if (f[i]==id) continue;
		if (f[i]!=id*2) {cout<<0;return 0;}
		sum++,idx=i;
	}
	if (tip==1){
		if (id==0) cout<<1<<'\n'<<a[1];
		else cout<<2<<'\n'<<a[1]-f[1]<<' '<<a[n]+f[1];
	}
	else if (sum<=1) cout<<1<<'\n'<<a[idx]+id;
	else cout<<0;
	return 0;
}
```


---

## 作者：kimi0705 (赞：1)

# CF382C Arithmetic Progression 题解

## 分类讨论
$$\left\{
\begin{aligned}
n=1\\
a_1=a_2=\dots=a_n\\
n=2\\
n\geq 3\\
\end{aligned}
\right.
$$
### $n = 1$
在 $n=1$ 的情况下，新的一个数取什么的都可以，因为任意两个数都可以是等差数列。
### $a_1=a_2=\dots=a_n$
显然是只有 $1$ 种， 且必须是 $a_i$。
### $n = 2$
$|a_1-a_2|+\max(a_1,a_2)$、$\min(a_1,a_2)-|a_1-a_2|$ 肯定可以，即在数列的两端填数。

$\frac{|a_1-a_2|}{2}+\min(a_1,a_2)$ 有可能可以，在两数奇偶性相同的情况下，即在两数中间加数。
### $n\geq3$
- 先排序，`sort(a+1,a+n+1);`
- 有以下两种情况
  - 一，原本就是等差数列：可以在 $a_1$ 的左边或 $a_n$ 的右边。
  - 二，原本不是等差数列：可以在 $a_i$ 和 $a_{i+1}$ 之间插一个。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool check ( vector <int> a ) {
	int c  = a[1] - a[0];
	for ( int i = 2; i < a.size(); i++ ) if ( a[i] - a[i - 1] != c ) return 0;
	return 1;
}
int main() {
	int n;
	cin >> n;
	vector <int> Arr ( n );
	for ( int &i : Arr ) cin >> i;
	sort ( Arr.begin(), Arr.end() );
	if ( n == 1 ) cout << -1;
	else if ( Arr[0] == Arr[n - 1] ) cout << 1 << ' ' << Arr[0];
	else if ( n == 2 ) {
		if ( ( Arr[1] - Arr[0] ) & 1 ) { // 差是奇数，不能在中间插入
			cout << 2 << '\n';
			cout << Arr[0] - ( Arr[1] - Arr[0] ) << ' ' << Arr[1] + ( Arr[1] - Arr[0] ) << '\n';
		} else {
			cout << 3 << '\n';
			cout << Arr[0] - ( Arr[1] - Arr[0] ) << ' ' << ( Arr[1] - Arr[0] ) / 2 + Arr[0] << ' ' << Arr[1] + ( Arr[1] - Arr[0] ) << '\n';
		}
	} else {
		if ( check ( Arr ) ) {
			int c = Arr[1] - Arr[0];
			cout << 2 << '\n';
			cout << Arr[0] - c << ' ' << Arr[n - 1] + c;
		} else {
			// 假设 0-1 是公差
			int c = Arr[1] - Arr[0];
			int cnt = 0, id;
			for ( int i = 1; i < Arr.size(); i++ ) if ( Arr[i] - Arr[i - 1] != c ) cnt++, id = i - 1;
			if ( cnt == 1 ) {
				if ( Arr[id + 1] - Arr[id] == 2 * c ) {
					cout << 1 << '\n';
					cout << ( Arr[id + 1] - Arr[id] ) / 2 + Arr[id];
					return 0;
				}
			}
			// 假设 1-2 是公差
			c = Arr[2] - Arr[1];
			cnt = 0;
			for ( int i = 1; i < Arr.size(); i++ ) if ( Arr[i] - Arr[i - 1] != c ) cnt++, id = i - 1;
			if ( cnt == 1 ) {
				if ( Arr[id + 1] - Arr[id] == 2 * c ) {
					cout << 1 << '\n';
					cout << ( Arr[id + 1] - Arr[id] ) / 2 + Arr[id];
					return 0;
				} else {
					cout << 0;
					return 0;
				}
			}
			cout << 0;
			return 0;
		}
	}
}
```
~~题解是我家，AC 靠大家!。~~

---


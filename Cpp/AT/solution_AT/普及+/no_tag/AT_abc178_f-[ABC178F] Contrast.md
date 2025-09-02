# [ABC178F] Contrast

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc178/tasks/abc178_f

長さ $ N $ の数列 $ A $ と $ B $ が与えられます。 $ A,B $ はそれぞれ昇順にソートされています。 $ B $ を好きに並べ替えてすべての $ i(1\ \leq\ i\ \leq\ N) $ について $ A_i\ \neq\ B_i $ を満たすようにできるか判定し、できるならそのような $ B $ の並べ替え方を一つ示してください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\leq\ A_i,B_i\ \leq\ N $
- $ A,B $ はそれぞれ昇順にソートされている。
- 入力はすべて整数

## 样例 #1

### 输入

```
6
1 1 1 2 2 3
1 1 1 2 2 3```

### 输出

```
Yes
2 2 3 1 1 1```

## 样例 #2

### 输入

```
3
1 1 2
1 1 3```

### 输出

```
No```

## 样例 #3

### 输入

```
4
1 1 2 3
1 2 3 3```

### 输出

```
Yes
3 3 1 2```

# 题解

## 作者：CarroT1212 (赞：9)

### 题目大意

给定长度为 $N$ 的两个升序排列的序列 $A,B$，试重新排列 $B$，使得 $A_i\neq B_i\,(1 \le i \le N)$。输出任意一个满足条件的排列后的 $B$。

数据范围：$1 \le N \le 2\times10^5$，$1 \le A_i,B_i \le N$。

------------

### 解法分析

这个升序排列好像在暗示着什么呢。

这里用“相交”表示 $A_i=B_i$。尝试把 $B$ 倒过来，这样 $A,B$ 就是一个升序一个降序了，感觉也比较容易出现更多不同的 $A_i,B_i$。

然后我们会发现一个性质：此时相交的位置要么不存在，要么会组成一段连续的区间，并且区间内的 $A_i,B_i$ 全部相等。手造几个样例就可以理解了。这么好的性质，直接用它开大即可。

如果没有相交位置的话我们就可以直接输出。否则，设这个相同的数为 $k$，接下来考虑如何消除这段相交部分，很简单，就是把相交部分的 $B_i$ 与其它的位置交换。

不过交换的位置也有讲究，设处于相交部分的 $B_i$ 要与 $B_j$ 交换，则 $j$ 需要满足 $A_j,B_j$ 都不等于 $k$。如果 $A_j=k$，那 $B_i$ 换过去还是和 $A_j$ 相等，没用；如果 $B_j=k$，$B_j$ 换过来又和 $A_i$ 相等，也没用。如果满足这两个条件的位置不少于相交位置，我们模拟一遍就可以直接把 $B$ 输出了。否则，就没法把相交区间内的 $B_i$ 全部换出去了。

那没法全部交换出去，就无解了吗？还真是，简单证明一下。设等于 $k$ 的 $A_i$ 个数为 $a$，等于 $k$ 的 $B_i$ 个数为 $b$。显然如果要满足所有 $A_i$ 都不等于 $B_i$ 的话，必须有 $a+b\le N$。但是如果相交部分内的 $B_i$ 没法全部交换出去，设相交部分长为 $c$，我们就可以得到 $c>N-(a+b-c)$，即 $a+b>N$，与前面矛盾，所以这种时候一定无解。

------------

### 代码

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pll pair<ll,ll>
using namespace std;
const int N=2e5+7;
int n,a[N],b[N],k,l,r=-1,cnt=1;
int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++) scanf("%d",&b[i]);
	reverse(b+1,b+n+1);
	for (int i=1;i<=n;i++) if (a[i]==b[i]) {
		k=a[i],l=r=i;
		while (b[r+1]==a[r+1]) r++;
		break;
	}
	while (l<=r) {
		while (a[cnt]==k||b[cnt]==k) cnt++; // 从前往后扫所有可以把 B_i 换出去的位置一一交换
		if (cnt>n) return printf("No"),0;
		swap(b[l++],b[cnt++]);
	}
	printf("Yes\n");
	for (int i=1;i<=n;i++) printf("%d ",b[i]);
	return 0;
}
```

---

## 作者：OyamaMahiro_qwq (赞：3)

统计每个数 $i$ 在 $a$ 和 $b$ 中的出现次数 $c_i$。

若存在 $i$ 使得 $c_i > n$ 则无解。

这是因为每个 $i$ 需要占用一个位置，而总共只有 $n$ 个位置。

然后考虑翻转序列 $b$。

题目保证现在 $a$ 升序，$b$ 降序。

所以 $a_i=b_i$ 的下标组成一个区间，且区间内的所有数相同。

特判不存在的情况，直接输出此时的 $b$ 数组。

我们扫一遍找到这个区间，设区间内的数为 $val$。

设在 $a$ 中 $val$ 的区间是 $[l_a, r_a]$；在 $b$ 中是 $[l_b, r_b]$。

则 $l_a \le l_b \le r_b \le r_a$。

考虑让不在 $[l_a, r_a]$ 中的 $b_i$ 和在 $[l_b, r_b]$ 的数交换。

因为 $c_{val} \le n$，所以 $(r_a - l_a + 1) + (r_b - l_b + 1) \le n$。

可以交换的数量 $num = n - (r_a - l_a + 1) \ge r_b - l_b + 1$。

故一定可行。

```cpp
#include <algorithm>
#include <iostream>
#include <climits> 
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> a(n + 1), b(n + 1), cnt(n + 1);
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		cnt[a[i]]++;
	}
	for(int i = 1; i <= n; i++) {
		cin >> b[i];
		cnt[b[i]]++;
	}
	for(int i = 1; i <= n; i++) {
		if(cnt[i] > n) {
			cout << "No\n";
			return 0;
		}
	}
	reverse(next(b.begin()), b.end());
	int L = -1, R = -1, val = -1;
	for(int i = 1; i <= n; i++) {
		if(a[i] == b[i]) {
			L = i;
			val = a[i];
			break;
		}
	}
	for(int i = n; i >= 1; i--) {
		if(a[i] == b[i]) {
			R = i;
			break;
		}
	}
	if(L == -1) {
		cout << "Yes\n";
		for(int i = 1; i <= n; i++) {
			cout << b[i] << " ";
		}
		cout << "\n";
		return 0;
	}
	for(int i = 1, j = L; i <= n; i++) {
		if(L <= i && i <= R) {
			continue;
		}
		if(a[i] == val || b[i] == val) {
			continue;
		}
		swap(b[i], b[j]);
		j++;
		if(j > R) {
			cout << "Yes\n";
			for(int k = 1; k <= n; k++) {
				cout << b[k] << " ";
			}
			cout << "\n";
			return 0;
		}
	}
	cout << "No\n";
	return 0;
}
```

---

## 作者：Wzmois (赞：1)

$$
\colorbox{#52c41a}{\textcolor{white}{Contrast-Solution}}
$$
## 分析题目
1. $A,B$ 以**升序**排列。
2. $B$ 中元素顺序**重新排列**。
3. $A_i\not=B_i$。
## 实现思路
由第一点可知，一般情况下，倒序的 $B$ 与正序的 $A$，会有最多的数满足第三点。由第二点，于是我们可以对 $B$ 进行数组反转操作。

反转过后，可能还会有不符合第三点的数字，于是我们找出最左边不符合位置的下标和最右边不符合位置的下标。

此时处理 $[l,r]$ 即可。

### 特殊情况 1
某个数在 $A$ 和 $B$ 中出现次数 $>n$，由于数列长度为 $n$。根据容斥原理可知，至少会有一个 $i$ 满足 $A_i=B_i$。此时之间输出 `No` 即可。
### 特殊情况 2
如果反转过后的数组已经符合条件，那么棒棒的，可以输出数组 $B$ 了！
## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){int i=0;char n=0,ch='\0';while((ch=getchar())<48||ch>57) if(ch=='-') n=1 ;while(ch>47&&ch<58) i=(i<<1)+(i<<3)+(ch&0xCF),ch=getchar();if(n) i=-i;return i;}
#define s(mois) mois=read()
const int N=200002;
int n,cnt[N],t;
int a[N],b[N],l=-1,r=-1,val=-1;
void p(){
	puts("Yes");
	for(int i=1;i<=n;i++) printf("%d ",b[i]);
	exit(0);
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t;
		a[i]=t;
		cnt[t]++;
	}
	for(int i=1;i<=n;i++){
		cin>>t;
		b[i]=t;
		cnt[t]++;
	}
//特殊情况 1
	for(int i=1;i<=n;i++){ 
		if(cnt[i]>n){puts("No");return 0;}
	}
//找到 l & r
	reverse(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		if(a[i]==b[i]){
			l=i,val=a[i];break;
		}
	}
	for(int i=n;i>=1;i--){
		if(a[i]==b[i]){
			r=i;break;
		}
	}
//特殊情况 2
	if(l==-1) p();
//处理 [l,r]
	int tmp=l;
	for(int i=1;i<=n;i++){
		if((l<=i&&r>=i)||a[i]==val||b[i]==val) continue;
		swap(b[i],b[tmp]);
		tmp++;
		if(tmp>r) p();
	}
	puts("No");
	return 0;
}

``````
完结撒花！

---

## 作者：_Sheepsheep (赞：1)

## 题意简述：
给出 $A$ ，$B$ 两个有序数组，长度为 $n$，任意排列 $B$，问是否有一种方案使得对于所有的  $i(1\le i\le n)$ 都有 $A_i≠B_i$。

## 题目分析:
如果存在某一个数出现的次数大于等于 $n+1$，根据鸽巢原理一定无解。

设 $C_i$ 表示 $A$ 数组中值小于或等于 $i$ 的数的出现次数，$D_i$ 表示 $B$   数组中值小于或等于 $i$ 的数的出现次数。

将 $C_i$ 和 $D_i$ 看作是 $x$ 轴上的点，对于所有的 $i(1\le i\le n)$，$(C_{i-1},C_i)$、$(D_{i-1},D_i)$ 形成若干条线段。考虑构造一个 $x$，使得对于任意的 $i(1\le i\le n)$，都有 $(D_{i-1}+x,D_i+1)$ 与 $(C_{i-1},C_i)$ 与 $(C_{i-1}+n,C_i+n)$ 不相交。

![](https://cdn.luogu.com.cn/upload/image_hosting/q7qwmlgh.png?x-oss-process=image)

由三条线段关系得到不等式：  
$$\begin{cases}D_{i-1}+x\ge C_i\\D_i+x\le C_{i-1}+n \end{cases}$$  
 即： 
$$C_i-D_{i-1}\le x\le C_{i-1}+n-D_i$$ 
 可以证明每一个数在 $A$，$B$ 中一共出现的次数小于等于 $n$ 时，合法的 $x$ 一定存在。

## 证明：

假设 $x$ 不存在，即存在一对 $(i,j)$ 使得  $C_i-D_{i-1}>C_{j-1}+n-D_j$   成立。

- 若 $i==j$，有 $(C_i-C_{i-1})+(D_i-D_{i-1})>n$，即表示某一个数字在 $A$ 和 $B$ 中一共的出现次数大于 $n$，这与我们的前提条件不符，所以当 $i==j$ 时假设不成立。
- 若 $i<j$，有 $(C_i-C_{j-1})+(D_j-D_{i-1})>n$，此时 $(C_i-C_{j-1})\le0$，所以 $(D_{j}-D_{i-1})>n$。但根据定义，$D$ 数组的值域为 $[0,n]$，所以在 $i<j$ 时假设不成立。

- 若 $i>j$，$(C_{i}-C_{j-1})+(D_{j}-D_{i-1})>n$，此时 $(D_{j}-D_{i-1})\le0$，所以 $(C_{i}-C_{j-1})>n$。但根据定义，$C$ 数组的值域为 $[0,n]$，所以在 $i>j$ 时假设不成立。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std ;
#define ll long long
#define double long double
const ll N = 1e6+9 ;
const ll INF = 1e17 ;
const ll mod = 998244353 ;
//const double pi = acos(-1) ;
const double eps = 1e-7 ;
ll gcd( ll a , ll b ){ return a == 0 ? b : gcd( b%a , a ) ; }
ll lcm( ll a , ll b ){ return (a/gcd(a,b))*b ; }
ll Abs( ll x ){ return x < 0 ? -x : x ; }
ll n , a[ N ] , b[ N ] , c[ N ] , d[ N ] ;
void solve(){
    cin >> n ;
    for( int i = 1 ; i <= n ; i ++ ){
        cin >> a[ i ] ; c[ a[i] ] ++ ;
    }
    for( int i = 1 ; i <= n ; i ++ ){
        cin >> b[ i ] ; d[ b[i] ] ++ ;
    }

    for( int i = 1 ; i <= n ; i ++ ) if( c[i]+d[i] > n ){
        cout << "No\n" ; return ;
    }

    for( int i = 1 ; i <= n ; i ++ ){
        c[ i ] += c[ i-1 ] ; d[ i ] += d[ i-1 ] ;
    }

    ll l = 0 , r = INF ;
    for( int i = 1 ; i <= n ; i ++ ){
        l = max( l , c[i]-d[i-1] ) ; r = min( r , c[i-1]+n-d[i] ) ;
    }
    if( l > r ){
         cout << "No\n" ; return ;
    }

    cout << "Yes\n" ;
    for( int i = 1 ; i <= n ; i ++ ){
        cout << b[ (((i-l+n)%n==0)?n:((i-l+n)%n))  ] << " " ;
    }
    cout << "\n" ;
}
int main(){
    ios::sync_with_stdio(false) ; cin.tie(0) ; cout.tie(0) ;
    ll tt = 1 ; //cin >> tt ;
    while( tt-- ) solve() ;
    return 0 ;
}


```




---

## 作者：Empty_Dream (赞：0)

## ABC178F 解题报告

### 分析

比较简单的一题。

考虑什么时候我们能简单地构造出较多的不一样之处，我们发现一个序列升序，另一个降序能构造出一对比较不一样的数列。

我们发现一个性质：对于排完序的两个数列，要么全都不一样，要么有一段相同的数一样。

有了这点后，就剩下如何操作使得数列不一样了。我们发现其实可以把相同的每一个数换到相同的区间外面，直到相同区间为空。

如何记录相同区间呢？只需要先记录 $A$ 和 $B$ 中 某个数出现的最左边和最右边 $L_i$ 和 $R_i$，如果要替换 $X$，只需要找到 $L_X-1$ 或 $R_x+1$ 的地方替换就好，最后后更新 $L_X$ 或 $R_X$。

对于不可能的情况，就是有一个相同的数找不到一个合法的数替换了，也就是 $L_X$ 和 $R_X$ 都到边界了，就直接输出 $-1$。 

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int a[200005], b[200005], l[200005], r[200005];
vector<int> v;

int main(){
	cin >> n;
	memset(l, 0x3f, sizeof(l));
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		l[a[i]] = min(l[a[i]], i), r[a[i]] = max(r[a[i]], i);//记录每一个数的左右端点
	}
	for (int i = 1; i <= n; i++) cin >> b[i];
	sort(b + 1, b + n + 1, greater<int>());
	for (int i = 1; i <= n; i++) l[b[i]] = min(l[b[i]], i), r[b[i]] = max(r[b[i]], i);
	for (int i = 1; i <= n; i++){
		if (a[i] == b[i]) v.push_back(i);//判断相同的数
	}
	for (int i = 0; i < v.size(); i++){
		if (l[a[v[i]]] == 1 && r[a[v[i]]] == n) return cout << "No", 0;//到边界了
		if (l[a[v[i]]] != 1){//交换这两个数
			swap(b[l[a[v[i]]] - 1], b[v[i]]);
			l[a[v[i]]]--;
		}
		else{
			swap(b[r[a[v[i]]] + 1], b[v[i]]);
			r[a[v[i]]]++;
		}
	}
	cout << "Yes\n";
	for (int i = 1; i <= n; i++) cout << b[i] << " ";
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

# [ABC178F] Contrast


## 思路

首先考虑最简单的情况：如果 $A,B$ 中出现最多的元素相同，那么我们考虑出现最多的那个相同元素的个数。假设 $A$ 中有 $i$ 个数字 $k$，$B$ 中有 $j$ 个数字 $k$，若 $i+j>N$ 则无解。否则一定有解。

推广到所有情况，我们发现对于每一个数字 $i$，我们统计其出现的次数 $t_i$，如果存在 $t_i>N$ 则无解，否则有解。

我们考虑一下这种情况，这已经是极限情况了。但很显然，我们依旧可以找到合法的方案。

```Plain Text
6 
1 1 1 1 3 3
3 3 3 3 1 1
```


这时我把 $A$ 中或者 $B$ 中某些数字更改一下，那很显然就更可以找到合法的方案了。



至于输出方案，我们将 $B$ 排序从大到小输出，当遇到 $A_i=B_i=j$ 的情况我们就把 $B_i$ 赋值为下一个数，等 $A_i≠j$ 时我们再考虑安排 $j$。

## 代码

```C++
/*////////ACACACACACACAC///////////
	   . Coding by Ntsc .
	   . ToFind Chargcy .
	   . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>

//数据类型
#define ll long long
#define ull unsigned long long
#define db double
#define endl '\n'
//命名空间
using namespace std;
//常量
const int N=2e5+5;
const int M=1e3;
const int MOD=903250223;
const int INF=1e9;
//变量
int n,m,a[N],b[N],c,ton[N],y[N],ans,t,mx,res,tmp,cnt,web[M][M];
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>a[i];ton[a[i]]++;
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];ton[b[i]]++;
		mx=max(mx,ton[b[i]]);
	}

	if(mx>n){printf("No\n");return 0;}
	cout<<"Yes\n";
	for(int i=1,j=n;i<=n;i++,j--){
		if(j<1){
			cout<<t<<' ';continue;
		}
		if(a[i]==b[j]){t=b[j];while(a[i]==b[j])j--;}
		cout<<b[j]<<' ';
	}
#ifdef PAUSE_ON_EXIT
	system("pause");
#endif
	return 0;
}
```




---


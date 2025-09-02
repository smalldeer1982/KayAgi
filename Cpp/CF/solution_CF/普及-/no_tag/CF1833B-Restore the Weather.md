# Restore the Weather

## 题目描述

You are given an array $ a $ containing the weather forecast for Berlandia for the last $ n $ days. That is, $ a_i $ — is the estimated air temperature on day $ i $ ( $ 1 \le i \le n $ ).

You are also given an array $ b $ — the air temperature that was actually present on each of the days. However, all the values in array $ b $ are mixed up.

Determine which day was which temperature, if you know that the weather never differs from the forecast by more than $ k $ degrees. In other words, if on day $ i $ the real air temperature was $ c $ , then the equality $ |a_i - c| \le k $ is always true.

For example, let an array $ a $ = \[ $ 1, 3, 5, 3, 9 $ \] of length $ n = 5 $ and $ k = 2 $ be given and an array $ b $ = \[ $ 2, 5, 11, 2, 4 $ \]. Then, so that the value of $ b_i $ corresponds to the air temperature on day $ i $ , we can rearrange the elements of the array $ b $ so: \[ $ 2, 2, 5, 4, 11 $ \]. Indeed:

- On the $ 1 $ st day, $ |a_1 - b_1| = |1 - 2| = 1 $ , $ 1 \le 2 = k $ is satisfied;
- On the $ 2 $ nd day $ |a_2 - b_2| = |3 - 2| = 1 $ , $ 1 \le 2 = k $ is satisfied;
- On the $ 3 $ rd day, $ |a_3 - b_3| = |5 - 5| = 0 $ , $ 0 \le 2 = k $ is satisfied;
- On the $ 4 $ th day, $ |a_4 - b_4| = |3 - 4| = 1 $ , $ 1 \le 2 = k $ is satisfied;
- On the $ 5 $ th day, $ |a_5 - b_5| = |9 - 11| = 2 $ , $ 2 \le 2 = k $ is satisfied.

## 样例 #1

### 输入

```
3
5 2
1 3 5 3 9
2 5 11 2 4
6 1
-1 3 -2 0 -5 -1
-4 0 -1 4 0 0
3 3
7 7 7
9 4 8```

### 输出

```
2 2 5 4 11
0 4 -1 0 -4 0
8 4 9```

# 题解

## 作者：Coffee_zzz (赞：6)

### 分析

难点在于理解题意。

给定两个长度为 $n$ 的数组 $a,b$，你需要重排 $b$ 数组，让 $|a_i-b_i|$ 尽可能小且小于等于 $k$，保证有解。

容易发现 $|a_i-b_i|\le k$ 这个条件是没有用的，只需要让 $|a_i-b_i|$ 尽可能小。因为在 $|a_i-b_i|$ 最小且保证有解的情况下，一定有 $|a_i-b_i|\le k$。

那现在的问题就转化为了，如何重排 $b$ 数组，让 $|a_i-b_i|$ 尽可能小。显然当 $a$ 和 $b$ 都是从小到大或从大到小排好序的时候，$|a_i-b_i|$ 是尽可能小的。

题目还要求按照 $a$ 的原顺序对应输出 $b_i$ 的值，那么我们只需要把 $a$ 存到一个结构体里，记录他原来的编号，然后结构体排序即可。

### 代码

```c++
#include <bits/stdc++.h>

using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read(){
		reg char ch=gh();
		reg long long x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using IO::read;
const int N=1e5+5;
int b[N],tmp[N];
struct Nod{
	int id,val;
}a[N];
bool cmp(Nod a,Nod b){
	return a.val<b.val;
}
void solve(){
	int n=read(),k=read();
	for(int i=1;i<=n;i++) a[i].val=read(),a[i].id=i;
	for(int i=1;i<=n;i++) b[i]=read();
	sort(b+1,b+1+n);
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		tmp[a[i].id]=b[i];
	}
	for(int i=1;i<=n;i++) cout<<tmp[i]<<' ';
	cout<<'\n';
}
signed main(){
	int T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：Furina_Hate_Comma (赞：2)

~~吐槽一波这个 $\sout k$。~~

将 $a$ 序列与 $b$ 序列排序，然后一一对应。

必然存在这样一组解。

因为我们希望差最小，所以明显排序后对应的值差最小。

这是一个典型的贪心思路。

由于不可能出现无解的情况，所以匹配后再按照日期排序输出即可。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct tem{
	int d,t;
}a[114514];
int b[114514];
bool cmp1(tem a,tem b){return a.t<b.t;}
bool cmp2(tem a,tem b){return a.d<b.d;}
signed main()
{
	int t;
	cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i].t;
			a[i].d=i;
		}for(int i=1;i<=n;i++)
			cin>>b[i];
		sort(a+1,a+1+n,cmp1);
		sort(b+1,b+1+n);
		for(int i=1;i<=n;i++)a[i].t=b[i];
		sort(a+1,a+1+n,cmp2);
		for(int i=1;i<=n;i++)
			cout<<(a[i].t)<<" ";
		cout<<"\n";
	}
    return 0;
}
```

---

## 作者：Lovely_Chtholly (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1833B)

### 【题意】

给你长度为 $n$ 的 $2$ 个数组 $a$ 和 $b$，将 $b$ 数组重排，使 $|a_i-b_i|\le k$。

### 【分析】

要保证 $|a_i-b_i|\le k$ 就要先将 $a$ 和 $b$ 排序，然后将 $b$ 数组与 $a$ 数组一一匹配输出即可。因为有多种情况时输出任意一种情况即可，所以输出和样例不一样并不一定就是错的。

### 【AC 代码】

```cpp
#include<stdio.h>
#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;
const int N=1e5+10;
inline int read(char ch=getchar(),int n=0,int m=1)
{
	while(ch<'0' or ch>'9')
	{
		if(ch=='-')m=-1;
		ch=getchar();
	}
	while(ch>='0' and ch<='9')n=(n<<3)+(n<<1)+ch-'0',ch=getchar();
	return n*m;
}
ostream& operator <<(ostream& o,__uint128_t &a)
{
	__uint128_t x=a;
	stack<int>s;
	while(x)s.push(x%10),x/=10;
	while(!s.empty())o<<s.top(),s.pop();
	return o;
}
int t=read();
struct node
{
	int a,n;
}c[N];
bool cmp(node n,node m)
{
	return n.a<m.a;
}
bool cmp1(node n,node m)
{
	return n.n<m.n;
}
signed main()
{
	while(t--)
	{
		int n=read(),k=read(),b[N];
		for(int i=1;i<=n;i++)c[i].a=read(),c[i].n=i;
		for(int i=1;i<=n;i++)b[i]=read();
		sort(c+1,c+1+n,cmp),sort(b+1,b+1+n);
		for(int i=1;i<=n;i++)c[i].a=b[i];
		sort(c+1,c+1+n,cmp1);
		for(int i=1;i<=n;i++)cout<<c[i].a<<" ";
		puts("");
	}
	return 0;
}
```

---

## 作者：CheZiHe929 (赞：2)

# CF1833B 题解
## 原题链接
[**洛谷**](https://www.luogu.com.cn/problem/CF1833B)

## 题目大意
有 $T$ 组测试样例，每组样例给你长度为 $n$ 的数组 $a$ 和数组 $b$。将 $b$ 数组进行重新排列，使得 $ |a_i - b_i| \le k $，题目保证有解。最后输出 $b$ 数组时按照 $a$ 数组的原顺序进行输出。

## 思路分析
其实我们经过观察可以发现，$ |a_i - b_i| \le k $ 这个条件是没有用的，只要保证 $ |a_i - b_i| $ 足够小即可。既然相差需要最小，那么我们就要事先排序 $a$ 数组和 $b$ 数组。但由于最后要按照 $a$ 数组的原顺序进行输出，那么我们就需要一个结构体，所以排序前要手写一个比较器。

## 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
struct node{
	int num;//储存下来编号，输出时需要 
	int temp;//temp记录a数组中的温度 
}a[100005];

int b[100005];//用来排序的b数组 
int ba[100005];//按照a的顺序来排列的b数组 
bool cmp(node a,node b){//sort无法直接对结构体进行排序，所以我们需要手写比较器cmp 

	return a.temp < b.temp; 
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(ba,0,sizeof(ba));//多测不清空，爆零两行泪 
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			a[i].num=i;//记录a数组的原顺序，也就是储存下来编号 
			cin>>a[i].temp;
		}
		for(int i = 1 ; i <= n ; i++) 
			cin >> b[i];
		sort(a+1,a+n+1,cmp);//结构体的用手写cmp排序 
		sort(b+1,b+n+1);//普通数组直接sort排序 
		for(int i=1;i<=n;i++)
			ba[a[i].num] = i; //根据a数组的顺序更改b数组 
		for(int i=1;i<=n;i++)
			cout<<b[ba[i]]<<' '; //输出在a数组中对应位置上的数 
		cout<<endl;
	}
    return 0;
}
```


这个题大家不要过度纠结于样例，因为本题有多个解，输出其一即可。

## [AC 记录](https://www.luogu.com.cn/record/111030543)

**THE END.**

**THANK YOU.**

---

## 作者：封禁用户 (赞：1)

## 题意：

有数字 $n$ 和 $k$，给你数列 $A$ 和 $B$,让你给 $A$ 与 $B$ 匹配，直到任意一个 $i$ 满足 $A_i - b_i \le k$。

## 解法：

把数列 $A$ 的下标映射到数组 $id$,再将 $id$ 按 $A$ 的值的大小排序，再将 $A_i$ 与 $B_i$ 对应即可。

## code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int q;
int n,k;
const int maxn = 1e5+ 5;
int a[maxn],b[maxn];
int id[maxn];

bool cmp(int x,int y) {
	return a[x] < a[y];
}
int ans[maxn];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>q;
	while(q--){
		cin>>n>>k;
		for(int i = 1;i<=n;i++) {
			cin>>a[i];
			id[i] = i;
		}
		for(int i = 1;i<=n;i++) {
			cin>>b[i];
		}
		sort(b+1,b+1+n);
		sort(id+1,id+1+n,cmp);
		for(int i = 1;i<=n;i++) {
			ans[id[i]] = b[i];
		}
		for(int i = 1;i<=n;i++) {
			cout<<ans[i]<<" ";
		}
		cout<<endl;
	}
}
```

---

## 作者：minVan (赞：0)

**题目大意**

对于 $n$ 天的天气，用两个数组 $a$ 和 $b$ 来存储，$a$ 为预估的天气，$b$ 为实际天气，但 $b$ 是一个集合，可以任意排序。

问 $b$ 该如何排列才能使每一天预估天气和实际天气的差的绝对值小于 $k$。

**解题思路**

先把 $b$ 镜像到 $b'$ 里，接着将 $a$、$b$ 进行排序，然后用一个数组 $t$ 来记录 $b$ 的最终位置，即 `t[a[i].id] = b[i].id`，最终输出 $b'_{t_i}$ 即可。

**AC 代码，请勿抄袭**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
struct node {
    int num, id;
} a[N], b[N];
int tt[N], bb[N];
inline bool cmp(node x, node y) {
    return x.num < y.num;
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        int n, k;
        cin >> n >> k;
        for(int i = 1; i <= n; i++) {
            cin >> a[i].num;
            a[i].id = i;
        }
        for(int i = 1; i <= n; i++) {
            cin >> b[i].num;
            bb[i] = b[i].num;
            b[i].id = i;
        }
        sort(a + 1, a + n + 1, cmp);
        sort(b + 1, b + n + 1, cmp);
        for(int i = 1; i <= n; i++) {
            tt[a[i].id] = b[i].id;
        }
        for(int i = 1; i <= n; i++) {
            cout << bb[tt[i]] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
```

---

## 作者：I_am_kunzi (赞：0)

# CF1833B 题解

### 题目大意

有 $ t $ 组测试数据，其中每组有以下的输入输出。

> 给你 $ n $ 天的预测天气，还有 $ n $ 天的实际天气，但是不小心把实际天气的顺序整乱了，但是可以保证同一天的实际天气 $ i $ 和预测天气 $ j $ 满足 $ \left \vert i - j \right \vert \le k$，需要你帮忙恢复这些实际天气的顺序并输出，对于多种答案的，输出其一。

其中，有 $ 1 \le t \le 10 ^ 4 , 1 \le n \le 10 ^ 5 , 0 \le k \le 10 ^ 9 , \sum n \le 10 ^ 5$。

### 题目分析

我们让预测天气数组和实际天气数组强行产生关系来进行后续操作，可以用 ``` sort ``` 排序。因为题目保证同一天的实际天气 $ i $ 和预测天气 $ j $ 满足 $ \left \vert i - j \right \vert \le k$，排序后预测天气数组和实际天气数组已经保证有序，那么可以认为此时满足了 $ \left \vert i - j \right \vert \le k$，也就是找到了排序后对应的结果。

但是如何恢复回原来的样子呢？我们不妨用结构体存下预测天气数组，再用一个变量存下天数，从前往后扫一遍，用一个数组记下天数 $ i $ 对应的位置，最后每次输出实际数组中天数 $ i $ 对应位置处的数字即可完成本题。

### 代码时间

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
struct ttt //结构体 
{
	int bh , temp; //bh 存储天数，temp 存储温度 
};
ttt a[100005];
int b[100005];
int wz[100005];
bool cmp(ttt a , ttt b) //sort 函数中没有 ttt 类型的比较器，所以需要手写 
{
	return a.temp < b.temp; 
}
signed main()
{
	int t;
	cin >> t;
	while(t--)
	{
		memset(a , 0 , sizeof(a));
		memset(b , 0 , sizeof(b));
		memset(wz , 0 , sizeof(wz));
		int n , k;
		cin >> n >> k;
		for(int i = 1 ; i <= n ; i++)
		{
			a[i].bh = i; //记录天数 
			cin >> a[i].temp;
		}
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> b[i];
		}
		sort(a + 1 , a + n + 1 , cmp);
		sort(b + 1 , b + n + 1);
		for(int i = 1 ; i <= n ; i++)
		{
			wz[a[i].bh] = i; //记录对应天数的位置 
		}
		for(int i = 1 ; i <= n ; i++)
		{
			cout << b[wz[i]] << ' '; //输出对应天数的位置上的数 
		}
		cout << endl;
	}
    return 0;
}
```

---

## 作者：ScapegoatTree (赞：0)

### 题目简述
本题有多组测试数据。

对于每组数据，给定两个整数 $n$,$k$ 和两个长度为 $n$ 的两个序列 $a$ 和 $b$，现在可以重排 $b$，使得对于每一个 $\leq n$ 的正整数 $i$，使 $|a_i - b_i| \leq k$。数据保证有解。

### 思路

我们可以考虑这样的一种贪心思想：把 $a$ 和 $b$ 中的元素按照升序排列后两两配对，再按照编号排回原来的顺序。

代码大致可以这么实现：对于 $a$ 数组，我们可以把它定义成一个结构体，里面包含编号 $num$， $a$ 数列中的原数 $k$，与之配对的 $b$ 数列的数 $c$，先把这个结构体按照 $k$ 升序排序，再把 $b$ 数列升序排序，两两配对求出 $c$ 之后再按照 $num$ 升序排序，回到原序，输出时输出 $c$ 即可。

正确性很好证，就不证了。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int n,k;
struct w{
	int num;
	int k,c;
}a[MAXN];
int b[MAXN];
bool cmp1(w a,w b){
	return a.k<b.k;
}
bool cmp2(w a,w b){
	return a.num<b.num;
}
void solve(){
	cin>>n>>k;
	for(int i=0;i<n;i++){
		cin>>a[i].k;
		a[i].num=i;
	}
	for(int i=0;i<n;i++){
		cin>>b[i];
	}
	sort(a,a+n,cmp1);
	sort(b,b+n);
	for(int i=0;i<n;i++){
		a[i].c=b[i];
	}
	sort(a,a+n,cmp2);
	for(int i=0;i<n;i++)cout<<a[i].c<<' ';
	cout<<'\n';
}
int T;
int main(){
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：Introl (赞：0)

### 题意简述

- 给定两个长度为 $n$ 的数组 $a,b$。
- 重排数组 $b$，使得 $|a_i-b_i|$ 的值尽可能小且 $|a_i - b_i|\le k$。
- 保证有解。

### 分析
因为这道题是保证有解的，所以在 $|a_i - b_i|$ 的值最小的情况下，$|a_i - b_i|\le k$ 这个条件是不必要的。可得本题做法为怎样重排 $b$ 数组，保证 $|a_i - b_i|$ 的值尽可能小。显然，通过简要的转化可得，当 $a,b$ 按照升序或降序排列的时候，$|a_i-b_i|$ 的值尽可能小。注意一点，在题目中，要求以 $a$ 数组的原顺序来输出重排后的 $b$ 数组。我们可以使用结构体存储 $a_i$ 的原编号，对结构体排序之后按照这个顺序进行输出即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
const int MaxN = 1e5 + 100;
const int INF = 1e9;
int T=1, N, M;
template<class T>
inline void qread(T &sum)
{
    sum=0;int boo=1;
    char x=getchar();
    while(x<'0'||x>'9'){if(x=='-')boo=-1;x=getchar();}
    while(x>='0'&&x<='9'){sum=(sum<<1)+(sum<<3)+x-'0';x=getchar();}
    sum*=boo;
}
template<class T>
void qput(T x)
{
    if(x<0){
        x=-x;
        putchar('-');}
    if(x>9)
        qput(x/10);
   putchar(x%10+48);
}
struct f{
    int id ,a;
}a[MaxN];//结构体，id为原编号，a为值。

bool cmp(f a,f b){
    return a.a<b.a;//对结构体按照a的大小进行排序。
}
inline void Solve()
{
    int n,k;//其实与k的值是无关的。
    int b[MaxN],ans[MaxN];
    qread(n),qread(k);
    for(int i=0;i<n;i++){
        qread(a[i].a);
        a[i].id=i;//在输入a数组时记录a_i的编号。
    }
    for(int i=0;i<n;i++){
        qread(b[i]);
    }
    sort(b,b+n);
    sort(a,a+n,cmp);
    for(int i=0;i<n;i++){
        ans[a[i].id]=b[i];//存储重排之后的b数组
    }
    for(int i=0;i<n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
}
signed main()
{
    cin >> T;
    while (T--)
       Solve();
    return 0;
}
```


---

## 作者：EmptyAlien (赞：0)

# 题意简述

本题有 $t$ 组测试数据。

对于每组测试数据，给定整数 $n,k$ 与两个长度为 $n$ 的数组 $a$ 与 $b$。

要求重新排列 $b$ 使得对于每一个 $1\le i \le n$，满足 $|a_i - b_i| \le k$。

保证一定有解。

对于 $100\%$ 的数据满足：
* $1 \le t \le 10^4$
* $\sum_{i=1}^t n \le 10^5$
* $-10^9 \le a_i, b_i \le 10^9$
* $0 \le k \le 10^9$
# 思路
这道题本质上其实就是一个贪心思想。

为什么这么说呢？

题目要求对于每一个 $1\le i \le n$，满足 $|a_i - b_i| \le k$。

它又说保证一定有解。

所以实际上**这道题就与 $k$ 没有任何关系了**。

这个问题也就转化成了让 $|a_i - b_i|$ 的最大值最小的 $b$。

这里我们感性理解一下。

**两个长度相等且排好序的数组是不是按顺序对应起来的差的绝对值最小**？

很明显吧。

所以思路就出来了。

将两个数组都排序，同时记录下 $a_i$ 原始的位置。

再把 $b_i$ 对应上 $a_i$ 的原始位置。

# 代码
```cpp
/*
 * @Author: Lightning Creeper
 * @Date: 2023-05-21 10:15:57
 * @LastEditTime: 2023-05-21 10:41:33
 * @FilePath: \CreeperCpp\Contest\Codeforces\CF1833\B\B.cpp
 */
#include <bits/stdc++.h>
using namespace std;
struct Node {
    int x;
    int id;
};
bool cmp(Node x, Node y)
{
    return x.x < y.x; // 按照值排序
}
void Solve()
{
    int n, k;
    cin >> n >> k;
    vector<Node> a(n); // 开一个长度为 n，类型为 Node 的数组
    vector<int> b(n), ans(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x;
        a[i].id = i; // 记录原始位置
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    sort(a.begin(), a.end(), cmp); // 排序
    sort(b.begin(), b.end());
    for (int i = 0; i < n; i++) {
        ans[a[i].id] = b[i]; // 把b[i]对应到a[i]的原始位置上
    }
    for (int i : ans) {
        cout << i << " ";
    }
    cout << endl;
}
int main()
{
    ios::sync_with_stdio(false); // 关闭流同步，去掉也行
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) { // 多组数据
        Solve();
    }
    return 0;
}
```

---


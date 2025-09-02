# Masha and geometric depression

## 题目描述

Masha really loves algebra. On the last lesson, her strict teacher Dvastan gave she new exercise.

You are given geometric progression $ b $ defined by two integers $ b_{1} $ and $ q $ . Remind that a geometric progression is a sequence of integers $ b_{1},b_{2},b_{3},... $ , where for each $ i&gt;1 $ the respective term satisfies the condition $ b_{i}=b_{i-1}·q $ , where $ q $ is called the common ratio of the progression. Progressions in Uzhlyandia are unusual: both $ b_{1} $ and $ q $ can equal $ 0 $ . Also, Dvastan gave Masha $ m $ "bad" integers $ a_{1},a_{2},...,a_{m} $ , and an integer $ l $ .

Masha writes all progression terms one by one onto the board (including repetitive) while condition $ |b_{i}|<=l $ is satisfied ( $ |x| $ means absolute value of $ x $ ). There is an exception: if a term equals one of the "bad" integers, Masha skips it (doesn't write onto the board) and moves forward to the next term.

But the lesson is going to end soon, so Masha has to calculate how many integers will be written on the board. In order not to get into depression, Masha asked you for help: help her calculate how many numbers she will write, or print "inf" in case she needs to write infinitely many integers.

## 说明/提示

In the first sample case, Masha will write integers $ 3,12,24 $ . Progression term $ 6 $ will be skipped because it is a "bad" integer. Terms bigger than $ 24 $ won't be written because they exceed $ l $ by absolute value.

In the second case, Masha won't write any number because all terms are equal $ 123 $ and this is a "bad" integer.

In the third case, Masha will write infinitely integers $ 123 $ .

## 样例 #1

### 输入

```
3 2 30 4
6 14 25 48
```

### 输出

```
3```

## 样例 #2

### 输入

```
123 1 2143435 4
123 11 -5453 141245
```

### 输出

```
0```

## 样例 #3

### 输入

```
123 1 2143435 4
54343 -13 6 124
```

### 输出

```
inf```

# 题解

## 作者：_6_awa (赞：6)

分析：大意为有个 $b_i$ 和 $q$，$b_i = b_{i - 1} \times q$， 当 $|b_i| > l$ 时停止，不计 $b_i$ 等于 $m$ 个整数中的一个的数。正常情况下，不超过 $100$ 次是一定会退出来的，但是当 $q$ 为特殊值或者 $b_1$ 为 $0$ 时，情况就不一样了。

当 $q$ 为 $1$ 时，第 $i$ 次都得原数。这是只要判断 $b_1$ 是否在 $m$ 个整数中的一个即可。

当 $q$ 为 $-1$ 时，当 $i$ 为奇数时为 $b_1$，否则为 $-b_1$。但是我们不用管，因为只要有一个不在 $m$ 个整数中都是 `inf`，否则就是 $0$。

当 $q$ 为 $0$ 时，后面的数都是 $0$，当 $0$ 为 $m$ 个整数中的一个时，在判断 $b_1$ 也是不是，为 $1$ 或 $0$；否则为 `inf`。

另外，当 $b_1$ 为 $0$ 时，不管 $q$ 为多少都为 $0$，还需要进行特判。

接下来就是正常操作了。这里如果 $b_1$ 的绝对值都 $> l$ 了，那么就不用枚举了。记得开 `long long`。

```cpp
#include <iostream>
#include <cmath>
#include <map>
#define int long long
using namespace std; 
map<int,int>mp;
int b1,q,l,m,x,cnt;
signed main()
{
    cin >> b1 >> q >> l >> m;
    for(int i = 1;i <= m;i ++)cin >> x,mp[x] = 1;
    if(l < abs(b1))//直接特判
    {
        cout << 0;
        return 0;
    }
    if(q == 1)
    {
        if(mp[b1])cout << 0;
        else cout << "inf";
        return 0;
    }
    if(q == -1)
    {
        if(mp[b1] && mp[-b1])cout << 0;
        else cout << "inf";
        return 0;
    }
    if(q == 0)
    {
        if(mp[0] && !mp[b1])cout << 1;
        else if(mp[0] && mp[b1])cout << 0;
        else cout << "inf";
        return 0;
    }
    if(b1 == 0)
    {
        if(mp[b1])cout << 0;
        else cout << "inf";
        return 0;
    }
    while(abs(b1) <= l)//正常操作
    {
        if(!mp[b1])cnt ++;
        b1 *= q;
    }
    cout << cnt;
}
```

---

## 作者：_Life_ (赞：5)

是否厌倦了其它题解冗长到离谱的特判？那么来看看这篇只要一次特判的题解吧！

以下为本蒟蒻的奇思妙想：

我们把 $A$ 中的元素全部丢进set里 之后每次判重的时候时间复杂度可以达到 $\log m$ 

然后循环枚举 $B_{i}$ 1000000次！当然，由于题目中 $|B_{i}|<=l$ 的限制，**绝大部分情况**下是没法循环这么多次的 我们每次判断 $B_{i}$ 是否在 $A$ 中，如果不在 $A$ 中就 `ans++` 即可

那么一些聪明的同学可能会问了：那**循环1000000次的极少数情况**呢？

循环1000000次的情况有如下几种：

1. $B_{1}=0$
2. $P=0$
3. $P=1$
4. $P=-1$

数列的情况如下：

1. $0 \ 0 \ 0 \ 0 \ 0 \dots $
2. $B_{1} \ 0 \ 0 \ 0 \ 0 \dots$
3. $B_{1} \ B_{1} \ B_{1}\ B_{1} \dots$
4. $B_{1} \ \textnormal{-}B_{1} \ B_{1}\ \textnormal{-}B_{1} \dots$

易得在以上几种情况中，$B$中最多有$2$种**不同**的元素（注意此处**同样的元素也是计入元素个数的**）

但 $B_{i}$ 中的元素可能在 $A$ 中而导致不被计入元素个数，因此在以上四种情况中，答案**只有**0、1、inf三种（自己想一想为什么）

~~对了，还有一件事~~ **十年OI一场空，不开long long见祖宗**

附上AC代码一份：[AC记录](https://www.luogu.com.cn/record/44972128)
```cpp
#include<set>
#include<cmath>
#include<cstdio>
using namespace std;
#define int long long
int b1,q,l,m;
int ans,cnt;
set <int> a;
signed main()
{
	//freopen("array.in","r",stdin);
	//freopen("array.out","w",stdout);
	scanf("%lld %lld %lld %lld",&b1,&q,&l,&m);
	for(int i=0;i<m;i++)
	{
		int x;
		scanf("%lld",&x);
		a.insert(x);//把A中元素扔进set
	}
	int b2=b1;
	while(abs(b2)<=l)
	{
		cnt++;//统计当前循环枚举的次数
		if(a.find(b2)==a.end())//A中没有找到B[i]
			ans++;
		b2*=q;//枚举数列的下一项
		if(cnt==1000000)//如果循环枚举了1000000次
		{
			if(ans!=0&&ans!=1)//特判
				ans=-1;//如果写下的元素个数有无限多个 则标为-1
			break;
		}
	}
	if(ans==-1)
		printf("inf");
	else
		printf("%lld",ans);
}
```

---

## 作者：lukelin (赞：4)

特判q为0,1，-1；b1为0的情况  
然后其他情况直接用set暴力模拟即可  
有一个坑点：  
----如果abs(b) > l即使q=0，0没有限制也要输出0，~~蒟蒻不知道为什么~~  
放个代码
```cpp
#include <cstdio>
#include <cmath>
#include <set>
#define ll long long

using namespace std;

inline ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

set<ll> st;

int main(){
    ll b = read(), q = read(), l = read(), m = read();
    for (int i = 1; i <= m; ++i)
        st.insert(read());
    if (q == 0){
        if (st.find(0) != st.end() || (l < 0)){
            if (st.find(b) != st.end() || (abs(b) > l))
                printf("0");
            else
                printf("1");
        }
        else if (abs(b) > l)
            printf("0");
        else
            printf("inf");
        return 0;
    }
    else if (q == 1){
        if ((abs(b) > l) || st.find(b) != st.end())
            printf("0");
        else
            printf("inf");
        return 0;
    }
    else if (q == -1){
        if (abs(b) > l){
            printf("0");
            return 0;
        }
        if (st.find(b) == st.end()){
            printf("inf");
            return 0;
        }
        if (st.find(-b) == st.end()){
            printf("inf");
            return 0;
        }
        printf("0");
        return 0;
    }
    else if (b == 0){
        if (st.find(0) != st.end() || (l < 0))
            printf("0");
        else
            printf("inf");
        return 0;
    }
    else{
        int cnt = 0;
        for (ll i = b; abs(i) <= l; i *= q){
            if (st.find(i) == st.end())
                ++cnt;
        }
        printf("%d", cnt);
    }
    return 0;
}
```

---

## 作者：洛璟 (赞：2)

## Solution：

这道题……值一道绿题。

好吧其实这道题目，根据我的duliu马蜂，特判是主程序的12倍长。

因此这道题本身难度可能不是很大，只不过考验你细心，只要你足够细（？），AC不成问题。

我们需要特判的东西有以下几点：$b1$ < $l$、$b1=0$、$l<0$、$q=1$、$q=1$、$q=-1$。因此你需要6个奇怪的if，其中还要嵌套不少if。

去掉特判之后，我们直接上暴力，把整个等比数列列出来，再去判断，由于我们看到数据范围略微有些大，因此我们使用map来存储数组中出现的数字，由于其 $10^5$的数据范围，map是不会爆炸的。

因此只要你足够细，这就是一道红题。（迫真

那么其他的直接看代码罢

```cpp
#include<bits/stdc++.h>
#define int long long
#define MAX 1000000000
using namespace std;
int n, l, s, q, ans;
map<int, bool> fg;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
signed main()
{
    s = read();
    q = read();
    l = read();
    n = read();
    int k = s;
    for (int i = 1;i <= n;i++)
    {
        int a;
        a = read();
        fg[a] = 1;
    }
    if (abs(s) > l)//接下来是冗长的特判，fg就是用于记录数组出现的数字
    {
        printf("0\n");
        return 0;
    }
    if (s == 0)
    {
        if (fg[0] == 1)
        {
            printf("0\n");
            return 0;
        }
        if (fg[0] == 0)
        {
            printf("inf\n");
            return 0;
        }
    }
    if (l < 0)
    {
        printf("0\n");
        return 0;
    }
    if (q == 1 && fg[s] == 1)
    {
        printf("0\n");
        return 0;
    }
    if (q == 1 && fg[s] == 0)
    {
        printf("inf\n");
        return 0;
    }
    if (q == 0)
    {
        if (fg[0] == 1 && fg[s] == 1)
        {
            printf("0\n");
            return 0;
        }
        if (fg[0] == 0)
        {
            printf("inf\n");
            return 0;
        }
        if (fg[0] == 1 && fg[s] == 0)
        {
            printf("1\n");
            return 0;
        }
    }
    if (q == -1)
    {
        if (fg[s] == 1 && fg[-s] == 1) printf("0\n");
        else printf("inf\n");
        return 0;
    }
    while (abs(k) <= l)//三行核心代码（确信
    {
        if (fg[k] == 0) ans++;//枚举
        k *= q;
    }
    printf("%lld", ans);
    return 0;
}
```


---

## 作者：Cure_Wing (赞：0)

[CF789B Masha and geometric depression](https://www.luogu.com.cn/problem/CF789B)

考虑全面，才不会错失良机。

### 思路

一般情况下，等比数列的数是不会相同的。但是有三个特例 $-1,0,1$。

当 $q=0$ 时，显然除了第一个数是 $b_1$，其它**全是** $0$。

当 $q=1$ 时，显然**全是** $b_1$。

当 $q=-1$ 时，显然**全是** $b_1,-b_1$ 轮换。

当 $b=0$ 时，显然**全是** $0$。

特殊情况就这么四种，唯一的难点也许就在于如何考虑全面。

其余的情况，由于 $q$ 的绝对值最小是 $2$，所以直接暴力乘加判断就好了，这样时间复杂度为 $O(\log_ql)$。当心乘法结果爆 `int` 的情况。

最后我们判断一下这些数能不能出现，统计个数。特别的，如果有**全是**的数出现的话，答案显然是 `inf`。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<map>
using std::cin;using std::cout;
constexpr int N=100005;
int b1,q,l,m,a,ans;
std::map<int,bool>p,t;
signed main(){
	freopen("array.in","r",stdin);
	freopen("array.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>b1>>q>>l>>m;
    for(int i=1;i<=m;++i){cin>>a;p[a]=1;}
    if(q==0){
        if(std::abs(b1)>l) cout<<0;
        else if(p[0]) cout<<!p[b1];
        else cout<<"inf";
        return 0;
    }
    if(q==1){
        if(std::abs(b1)>l||p[b1]) cout<<0;
        else cout<<"inf";
        return 0;
    }
    if(q==-1){
        if(std::abs(b1)>l) cout<<0;
        else{
            if(!p[b1]||!p[-b1]) cout<<"inf";
            else cout<<0;
        }
        return 0;
    }
    if(b1==0){
        if(p[0]) cout<<0;
        else cout<<"inf";
        return 0;
    }
    for(long long k=b1;std::abs(k)<=l;k*=q) ans+=!p[k];
    cout<<ans;
    return 0;
}
```

---

## 作者：huanglihuan (赞：0)

[刚好的阅读体验？](https://www.luogu.com.cn/problem/CF789B)

思路：

其实本题非常简单，只要你够仔细，肯定能够过。

其实核心代码：

```cpp
while (abs (b) <= l)
	{
		if (!a.count (b)) ans ++;
		b *= q;
	}
```

这些就足够了。

但我们要判断

$$ [b=0]\operatorname{or}[q=0]\operatorname{or}[q=1]\operatorname{or}[q=-1] $$

的特殊情况。

[先给大家展示一下AC 记录](https://www.luogu.com.cn/record/138752657)

然后是 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main ()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int b,q,l,m;
	cin >> b >> q >> l >> m;
	set <int> a; // 用set储存去重
	// 将当前禁止的数储存 
	for (int i = 0;i < m;i ++)
	{
		int tmp;
		cin >> tmp;
		a.insert (tmp);
	}
	if (b == 0) // 0的任意倍数都是0 
	{
		// 如果当前0在set中，那么构不成无穷的条件
		if (!a.count(0)) cout << "inf";
		else cout << 0;
		return 0; 
	}
	if (q == 0) // 倍数为0，那么会一直变成0 
	{
		// 首项为被禁止&&循环项也被禁止 超出可写的范围
		if (a.count (b) && a.count (0) || abs (b) > l) cout << 0;
		else
		{
			// 当前如果公比为0的话那么会输出很多个 
			if (a.count (0)) cout << 1; // 循环项被禁止 
			else cout << "inf";
		 } 
		 return 0;
	}
	if (q == 1) // 当前倍数为1 
	{
		// 任何数的倍数1都为自己本身，自己本身没有超出范围的话，那么就会一直循环
		if (!a.count (b) && abs (b) <= l) cout << "inf";
		else cout << 0;
		return 0; 
	}
	if (q == -1) // 当前倍数为-1，会在整数和负数直接来回切换 
	{
		// 如果正数不能被写出的同时负数也不能被写出 或者本身超出范围
		if (a.count (b) && a.count (-b) || abs (b) > l) cout << 0;
		else cout << "inf";
		return 0; 
	}
	// 当前特殊情况已经判断完毕，while循环暴力查找答案 
	int ans = 0;
	while (abs (b) <= l)
	{
		// 当前的数可以被写出 
		if (!a.count (b)) ans ++;
		b *= q;
	}
	cout << ans;
	return 0;
}
```

最后说句实话，我觉得本题评绿真的有点过分了（但是我们不得不尊重我们的管理员大佬啊！）  

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
给你一个等比数列，首项为 $b_1$，公比为 $q$.  
现在Masha在黑板上从首项开始书写这个等比数列，直到数列某项的绝对值大于 $l$，给定 $m$ 个整数，若该等比数列中的某项等同于这 $m$ 个整数，则不会被写出.  
问Masha会写出多少个数字？如果她会写出无穷多个数字，输出`inf`.  
注意： $b1,q$ 可能为$0$.
## $\text{Solution}$
大特判题.  
特判一下公差等于 $0/1/-1$，首项等于 $0$ 的情况，其他的暴力算即可.  
需要开 longlong.

## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define double long double 
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
const double eps=1e-12;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,mx;
ll d,x;
map<ll,bool>mp;
int ans;
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  x=read();d=read();mx=read();n=read();
  for(int i=1;i<=n;i++) mp[read()]=1;
  if(abs(x)>mx){
    printf("0");return 0;
  }
  if(d==0){
    if(mp[0]) printf("%d",!mp[x]);
    else printf("inf");
  }
  else if(d==1){
    if(mp[x]) printf("0");
    else printf("inf");
  }
  else if(d==-1){
    if(mp[x]&&mp[-x]) printf("0");
    else printf("inf");
  }
  else if(x==0){
    if(mp[0]) printf("0");
    else printf("inf");
  }
  else{
    while(abs(x)<=mx){
      if(!mp[x]) ++ans;
      x*=d;
    }
    printf("%d\n",ans);
  }
  return 0;
}
/*

*/

```


---

## 作者：泠小毒 (赞：0)

# Masha and geometric depression
给你一个等比数列，首项为b1，公比为q，现在Masha在黑板上从首项开始书写这个等比数列，直到数列某项的绝对值大于l，给定m个整数，若该等比数列中的某项等同于这m个整数，则不会被写出。

问Masha会写出多少个数字？如果她会写出无穷多个数字，输出inf
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190507/)
## 解法
这道题太毒瘤了，有一种做法是纯模拟，当答案大于40时一定是inf，因为超出了上界

考试的时候没想到，就特判吧。。。
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int b1,q,l,m,x,ans;
long long b;
map<int,bool>mp;
int main()
{
	scanf("%d%d%d%d",&b1,&q,&l,&m);
	for(int i=1;i<=m;i++)scanf("%d",&x),mp[x]=1;
	if(q==1){if(mp[b1]||abs(b1)>l)puts("0");else puts("inf");}
	else if(q==0)
	{
		if(abs(b1)<=l)
		{
			if(mp[0])
			{
				if(mp[b1])puts("0");
				else puts("1");
			}
			else puts("inf");
		}
		else puts("0");
	}
	else if(q==-1){if((mp[b1]&&mp[-b1])||abs(b1)>l)puts("0");else puts("inf");}
	else if(b1==0){if(mp[b1])puts("0");else puts("inf");}
	else
	{
		b=b1;
		while(abs(b)<=l){if(!mp[b])ans++;b=b*q;}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：mulberror (赞：0)

$$\href{https://www.chhokmah.top/}{\Large\texttt{My blog}}$$

---
# Masha and geometric depression
## Description
> Link：[CF](http://codeforces.com/problemset/problem/789/B)

给你一个等比数列的首项和公比， 和$m$个数记为$a_i$，和$l$，如果数列超过了$l$就停止，如果遇到了$a_k$，那么就跳过，问能写多少个数，如果有无数个，输出$inf$。  
## Solution 
比较SB的一道题目，以下的骗到了满分的做法。    
懒得暴力讨论。    
map记录$a_i$，然后直接按照题目要求模拟，记录有多少个数。  
我们就判断一下这个数有多少个就可以了。  
我们枚举$100$项，很明显如果不是$1$或者是$-1$之类的公比，那么一定会超过$l$，不管$l$是多大。  
那么如果当前记录的数的个数超过了某一个常数，那么就是$inf$。  
考试的时候保险起见：开了$50$，赛后实测$40$可过，$30$就WA掉了。  
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void read(T &x) {
    x = 0; T fl = 1; char ch = 0;
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') fl = -1; 
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48); 
    x *= fl; 
}
typedef long long ll;
unordered_map<ll, int> vis;
ll b1, q, l;
int m, ans = 0; 
int main() {
    read(b1); read(q); read(l); read(m); 
    for (int i = 1; i <= m; i ++) {
        ll x; read(x);
        vis[x] = 1;  
    }
    for (int i = 1; i <= 100; i ++) {
        if (abs(b1) > l) break; 
        if (!vis[b1]) ans ++; 
        b1 *= q;  
    }
    if (ans < 40) printf("%d\n", ans);
    else puts("inf");
    return 0; 
}
```

---


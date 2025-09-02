# [ARC155B] Abs Abs Function

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc155/tasks/arc155_b

$ 2 $ つの非負整数からなる組の集合 $ S $ 、および非負整数 $ x $ に対し $ f_S(x) $ を $ \displaystyle\ f_S(x)=\min_{(a,\ b)\ \in\ S}\ \left|\ \left|\ x-a\ \right|\ -\ b\ \right| $ と定義します。

$ 2 $ つの非負整数からなる組の集合 $ T $ があります。はじめ $ T=\lbrace\ (A,\ B)\rbrace $ です。

$ Q $ 個のクエリを処理してください。$ i $ 番目のクエリでは $ 3 $ つの非負整数 $ t_i,\ a_i,\ b_i $ が与えられるので、以下のように処理してください。

- $ t_i=1 $ のとき 、 $ T $ に $ 2 $ つの非負整数からなる組 $ (a_i,\ b_i) $ を追加する。
- $ t_i=2 $ のとき 、 $ a_i\ \leq\ x\ \leq\ b_i $ を満たす非負整数 $ x $ に対する $ f_{T}(x) $ の最小値を出力する。

## 说明/提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ A,B\ \leq\ 10^{9} $
- $ t_i $ は $ 1 $ または $ 2 $
- $ 0\ \leq\ a_i,b_i\ \leq\ 10^{9} $
- $ t_i=2 $ のとき、$ a_i\ \leq\ b_i $
- $ t_i=2 $ を満たすクエリは $ 1 $ つ以上存在する
- 入力される値はすべて整数
 
### Sample Explanation 1

$ 2 $ 番目のクエリを実行するとき、$ T=\lbrace(0,\ 5),\ (3,\ 11)\ \rbrace $ であり、たとえば $ x=7 $ とすると $ f_T(7)=\min\ \lbrace\ \left|\ \left|7-0\right|-5\right|,\ \left|\ \left|7-3\right|-11\right|\ \rbrace=\min\ \lbrace\ 2,\ 7\ \rbrace=2 $ となります。 同様に、$ f_T(8)=3 $ となります。よって $ 2 $ 番目のクエリの答えは $ \min\ \lbrace\ 2,\ 3\ \rbrace\ =2 $ です。 $ 4 $ 番目のクエリを実行するとき、 $ T=\lbrace(0,\ 5),\ (3,\ 11),\ (8,\ 2)\ \rbrace $ です。$ 8\ \leq\ x\ \leq\ 9 $ において $ f_T(x) $ は $ x=9 $ で最小値 $ f_T(9)=1 $ をとります。

## 样例 #1

### 输入

```
4 0 5
1 3 11
2 7 8
1 8 2
2 8 9```

### 输出

```
2
1```

## 样例 #2

### 输入

```
2 1 2
1 2 3
2 2 6```

### 输出

```
0```

## 样例 #3

### 输入

```
20 795629912 123625148
2 860243184 892786970
2 645778367 668513124
1 531411849 174630323
1 635062977 195695960
2 382061637 411843651
1 585964296 589553566
1 310118888 68936560
1 525351160 858166280
2 395304415 429823333
2 583145399 703645715
2 97768492 218377432
1 707220749 459967102
1 210842017 363390878
2 489541834 553583525
2 731279777 811513313
1 549864943 493384741
1 815378318 826084592
2 369622093 374205455
1 78240781 821999998
2 241667193 243982581```

### 输出

```
26468090
3491640
25280111
9543684
0
22804896
20649370
19245624
4849993
484865```

# 题解

## 作者：Scrolling_Ball (赞：2)

很显然，这道题比 a 和 c 都简单得多。

拿到这道题，因为查询很奇怪，我们就先看查询。（为了简洁一点就用 $x$ 和 $y$ 代替 $j_{first}$ 和 $j_{second}$ 了）

$$\min_{a\le i\le b}^{j\in S}||i-x|-y|$$

因为有个绝对值，咱们就把它分讨一下：

$$
||i-x|-y|=
\begin{cases}
|i-(x+y)|&i\ge x\\
|i-(x-y)|&\text{others}
\end{cases}
$$

所以对于 add 操作，我们就可以把存 $(a,b)$ 这个二元组改成存 $a+b$ 和 $a-b$ 啦。

再看回我们推的那个式子，对于查询 $a\sim b$ 这个区间，$i$ 的取值显然只有两种情况：

1.如果集合内有数在 $a\sim b$ 这个区间里面，答案就为 $0$。

2.如果没有，那么选区间里面的数是肯定没有选 $a$ 和 $b$ 优的。

于是呢，我们就需要一个能够自动排序的数据结构。

显然，set 是一个最好的选择。（vector 也可以，就是会 [TLE](https://atcoder.jp/contests/arc155/submissions/42075510) 而已）

然后就做完啦，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int q, n = 0;
set<int> s;
int main()
{
	cin >> q;
	int x, y;
	cin >> x >> y;
	s.insert(x + y);
	s.insert(x - y);
	while(q -- )
	{
		int op, a, b;
		cin >> op >> a >> b;
		if(op == 1)
		{
			s.insert(a + b);
			s.insert(a - b);
		}
		else
		{
			if(*s.rbegin() <= a)//rbegin是最大值。如果最大值都比a小，lower_bound是搜不出来值的，所以就要特判。
			{
				printf("%d\n", a - *s.rbegin());
				continue;
			}
			auto it = s.lower_bound(a);
			int k = *it;
			if(it != s.begin())it -- ;//如果搜出来是第一个，那是没有比a小的值的。
			if(k <= b)puts("0");//在区间内输出0。
			else printf("%d\n", min(k - b, abs(a - *it)));//a与最大的比a小的值的差跟b与最小的比b大的值取最小。
		}
	}
	return 0;
}
```

---

## 作者：ljlawa (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/AT_arc155_b)

题面还是比较清晰的，给你 $q$ 个操作，加入二元组 $(a,b)$ 或者查询 $\min_{a\le i\le b}^{j\in S}||i-j_{first}|-j_{second}|$，以及初始有二元组 $(a,b)$。

~~看到这种题就会想到数据结构。~~

我们先将 $||i-j_{first}|-j_{second}|$ 拆开。

若 $i \ge j_{first}$，原式 $= |i-(j_{.first}+j_{.second})|$。

若 $i \le j_{first}$，原式 $= |(j_{first} - j_{second})-i|$。

然后发现我们只需要用到 $j_{first} - j_{second}$ 和 $j_{first} + j_{second}$。所以在添加操作里面我们只需要将这两个数添加进去，考虑用 $set$ 维护，问题就迎刃而解了。

查询：使用查询 $set$ 中第一个 $\ge a$ 的数 $res$，如果它 $\le b$，那么答案显然可以达到最小的 $0$。否则答案在 $res - b$ 和 $a-s[res.id-1]$ 中取最小。注意边界问题。

```cpp
#include <bits/stdc++.h>

using namespace std;

int q, a, b, t;
set <int> s;

void add (int a, int b)
{
	s.insert (a - b);
	s.insert (a + b);
}

void query (int a, int b)
{
	int res = *s.lower_bound(a);
	if (res <= b && res != *s.end()) { cout << 0 << endl; return ; }
	int ans = INT_MAX;
	if (res != *s.begin()) ans = min (ans, a - *(-- s.lower_bound(a)));
	if (res != *s.end()) ans = min (ans, res - b);
	cout << ans << endl;
}

signed main()
{
	cin >> q >> a >> b;
	add (a, b);
	while (q --)
	{
		cin >> t >> a >> b;
		if (t == 1) add (a, b);
		else query (a, b);
	}
	return 0;
}

```

---

## 作者：Augury (赞：1)

# 题解——[[ARC155B] Abs Abs Function](https://www.luogu.com.cn/problem/AT_arc155_b)

## 题意

你有一个集合 $S$，要求支持两种操作

1. 插入一个二元组 $(a,b)$
2. 给定一个 $c$ 一个 $d$，查询

$$
\min_{c\le x\le d}^{(a,b)\in S}||x-a|-b|
$$

## 做法

考虑这个式子变形

显然，这是个带有绝对值的式子，考虑把它拆开

当 $x\ge a$ 时：
$$
\begin{array}{c}
||x-a|-b|\\ = |x-a-b|\\ = |x-(a+b)|\\ = |a+b-x|
\end{array}
$$

当 $x<a$ 时：
$$
\begin{array}{c}
||x-a|-b|\\ = |a-x-b|\\ = |a-b-x|
\end{array}
$$

所以我们把问题转换成了求
$$
\min_{c\le x\le d}^{(a,b)\in S}\min\{|a-b-x|,|a+b-x|\}
$$

的值。

当然，这个式子看起来很丑。我们考虑一个新的集合 $T$：
$$
T=\{a-b|(a,b)\in S\}\cup\{a+b|(a,b)\in S\}
$$

问题就转化成了求
$$
\min_{c\le x\le d}^{y\in T}|x-y|
$$

的值。

然后大力分讨。

如果 $\exists x,c\le x\le d且 x\in T$，显然答案为 $0$。

否则，考虑找到
$$
\max_{y<c}^{y\in T}y
$$
和
$$
\min_{z>d}^{z\in T}z
$$
然后求出
$$
\min\{c-y,z-d\}
$$
即可，显然 $\min\{c-y,z-d\}$ 就是我们要求的答案。

这个式子的值可以方便地用 $\text{set}$ 维护。

具体细节见代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=0x3f3f3f3f3f3f3f3f;
int n,t,a,b;
set<int>st;
signed main(){
	scanf("%lld",&n);
	st.insert(inf);
	st.insert(-inf);
	scanf("%lld%lld",&a,&b);
	st.insert(a-b);//插入值
	st.insert(a+b);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&t,&a,&b);
		if(t==1){
			st.insert(a-b);
			st.insert(a+b);
		}
		else{
			if((*st.lower_bound(a))<=b)puts("0");
			else{
				auto it1=st.upper_bound(a);//求出T中小于a的最大的值
				it1--;
				auto it2=st.upper_bound(b);//求出T中大于b的最小的值
				int ans=min(a-*it1,*it2-b);
				cout<<ans<<'\n';
			}
		}
	}
	return 0;
}
```



---

## 作者：CrTsIr400 (赞：0)

ARC 的这类题目都比较小清新，有一点思维含金量，只要突破了这层障碍就可以很轻松 AC 掉。

考虑化简 $||i-a_j|-b_j|$ 这个绝对值式子。

首先，讨论 $i>a_j$ 时候的情况：则式子为 $|i-a_j-b_j|$。显然记 $c_j=a_j+b_j$ 然后查询区间 $[l,r]$ 中有没有这样的 $c$，如果没有的话就看看离左右端点有多长。

讨论 $i\le a_j$，那么原式= $|a_j-i-b_j|$。其实也是 $|i-a_j+b_j|$，也是和上面的流程类似。

感觉不够简洁，毕竟这个东西真的维护很麻烦，考虑再次简化式子。

观察到 $b_j$ 是一个非负整数，所以发现，其实 $a_j-i<0$ 也没有什么关系，绝对值肯定会很大。如果 $i>a_j$ 的式子就算代入一个 $i<a_j$ 也没关系，顶多搞出一个负数让你的绝对值不优。显然这样算答案是不漏不错的。

于是把所有 $c,d$ 丢进 `set` 里面然后直接查询即可。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
I q,a,b,t;
set<I>s;
I fmin(){
//	for(auto&i:s)printf("%d ",i);
//	puts("");
	auto p=s.lower_bound(a);
	if(p!=s.end()&&*p<=b)return 0;
	I ans=(p==s.begin()?1<<30:a-*prev(p));
	p=s.lower_bound(b);
	ans=min(ans,(p==s.end())?1<<30:(*p-b));
	return ans;
}
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>q>>a>>b;s.insert(a+b);s.insert(a-b);
	fo(i,1,q){
		cin>>t>>a>>b;
		if(t==1)s.insert(a+b),s.insert(a-b);
		else printf("%d\n",fmin());}
	return 0;}
```





---

## 作者：Rushroom (赞：0)

# 题意

有一个非负整数对的集合 $T$，初始时 $T={A,B}$。每次操作，要么向 $T$ 中加入一个元素，要么给定区间 $[l,r]$，查询 $\min\limits_{x\in [l,r],(a,b)\in T} \lvert\lvert x-a \rvert -b \rvert$。
$q \le 2\cdot 10^5,A,B,l,r \le 10^9$

# 题解

查询的东西函数图像画出来是一个 W。其实可以转化成 $\min\{\lvert a+b-x\rvert,\lvert a-b-x\rvert\}$。刚好它要求的也是 min，所以就拆成两个数 $a+b$ 和  $a-b$，查询改为 $\min\limits_{x\in [l,r],y\in T} \lvert x-y\rvert$。
这个东西用 set 维护一下就行了。

# Code

```cpp
ll q, t, a, b;
set<ll>s;
void solve() {
    cin >> q >> a >> b;
    s.insert(a + b), s.insert(a - b);
    while (q--) {
        cin >> t >> a >> b;
        if (t == 1)s.insert(a + b), s.insert(a - b);
        else {
            auto p = s.lower_bound(a);
            ll ans = MAXN;
            if (p != s.end()) {
                int x = *p;
                if (x <= b)ans = 0;
                else ans = x - b;
            }
            if (p != s.begin()) {
                p--;
                int x = *p;
                ans = min(ans, a - x);
            }
            cout << ans << endl;
        }
    }
}
```

---


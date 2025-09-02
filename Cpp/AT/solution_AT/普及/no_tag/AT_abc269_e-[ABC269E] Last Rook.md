# [ABC269E] Last Rook

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc269/tasks/abc269_e

**この問題はインタラクティブな問題**（あなたの作成したプログラムとジャッジプログラムが入出力を介して対話を行う形式の問題）です。

縦横 $ N $ マスのチェス盤と $ N $ 個のルークの駒があります。以下では上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,\ j) $ と表します。  
 チェス盤のマスにルークを置くことを考えます。ただし、あなたは次の条件をすべて満たすようにルークをチェス盤に置く必要があります。

- 1 つの行に $ 2 $ 個以上のルークが存在しない。
- 1 つの列に $ 2 $ 個以上のルークが存在しない。

今、チェス盤に $ N-1 $ 個のルークが上の条件をすべて満たした状態で置かれています。あなたはルークが置かれていないマスを 1 つ選び、そのマスにルークを置くことにしました。(上の条件をすべて満たすようにルークを置くことができるマスは少なくとも 1 つ以上存在することが証明できます。)

ただし、あなたはチェス盤のどのマスにルークが置かれているかを直接知ることはできません。  
 そのかわりに、ジャッジシステムに対して以下の質問を $ 20 $ 回まで行うことができます。

- 整数 $ A,\ B,\ C,\ D $ を $ 1\ \leq\ A\ \leq\ B\ \leq\ N,\ 1\ \leq\ C\ \leq\ D\ \leq\ N $ を満たすように選ぶ。そして、$ A\ \leq\ i\ \leq\ B,\ C\ \leq\ j\ \leq\ D $ を満たすマス $ (i,\ j) $ からなる長方形領域に置かれているルークの個数を聞く。

ルークを置くことができるマスを見つけてください。

### Input &amp; Output Format

この問題はインタラクティブな問題（あなたの作成したプログラムとジャッジプログラムが入出力を介して対話を行う形式の問題）です。

最初に、チェス盤のサイズ $ N $ を標準入力から受け取ってください。

> $ N $

次に、ルークを置くことができるマスが見つかるまで質問を繰り返してください。  
 質問は、以下の形式で標準出力に出力してください。

> $ ? $ $ A $ $ B $ $ C $ $ D $

これに対する応答は、次の形式で標準入力から与えられます。

> $ T $

ここで、$ T $ は質問に対する答えです。ただし、不正な質問を行った、あるいは質問の回数が $ 20 $ 回を超えた場合は $ T $ は `-1` となります。

ジャッジが `-1` を返した場合、提出はすでに不正解とみなされています。この場合、ただちにプログラムを終了してください。

ルークを置くことができるマスを見つけたら、そのマスを $ (X,\ Y) $ として、解答を以下の形式で出力してください。その後、ただちにプログラムを終了してください。

> $ ! $ $ X $ $ Y $

答えが複数ある場合、どれを出力しても正解とみなされます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^3 $
- $ N $ は整数

### 注意点

- **出力を行うたびに、末尾に改行を入れて標準出力を flush してください。そうしなかった場合、ジャッジ結果が TLE となる可能性があります。**
- **対話の途中で不正な出力を行った場合のジャッジ結果は不定です。**
- 解答を出力したらただちにプログラムを終了してください。そうしない場合、ジャッジ結果は不定です。

### 入出力例

以下は、$ N=3 $ で $ (1,\ 2),\ (2,\ 1) $ にルークが置かれている場合の入出力例です。

 入力 出力 説明 `3`  まず整数 $ N $ が与えられます。  `? 1 2 1 3`  $ (A,B,C,D)=(1,2,1,3) $ として質問を行います。 `2`  質問の答えは $ 2 $ なので、ジャッジはその値を返します。  `? 2 3 1 1` $ (A,B,C,D)=(2,3,1,1) $ として質問を行います。 `1`  質問の答えは $ 1 $ なので、ジャッジはその値を返します。  `? 1 3 3 3` $ (A,B,C,D)=(1,3,3,3) $ として質問を行います。 `0`  質問の答えは $ 0 $ なので、ジャッジはその値を返します。  `! 3 3` 答えは $ (3,\ 3) $ だとわかったので、それを出力します。

# 题解

## 作者：_hxh (赞：1)

## 题意

有一个 $n \times n$ 的棋盘，上面已经有了 $n - 1$ 个互相不攻击的车，此时该棋盘有且仅有一个位置 $(x,y)$ 还可以放一辆车（与其他车互相不能攻击）。你可以进行不超过 $20$ 次的形如 `? a b c d` 的询问，得到左上角为 $(a,c)$，右下角为 $(b,d)$ 的子矩阵中的车的数量，最后求出该棋盘还可以放一辆车的位置 $(x,y)$。$1 \le n \le 1000$。

## 分析

这是一道交互题。因为车只影响本行与本列，所以一行和一列没有车的格子的交点处即为答案。由于 $n \le 1000$，且只有 $20$ 次询问，所以我们可以二分求得答案。分两种情况：

1. 前面所有车加起来的数量和本格子编号相同，说明前面没有少车，答案在后面；
2. 前面所有车加起来的数量比本格子编号小，说明前面少车了，即有一列空出来了，答案在前面；

## Code


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ask,l,r;//ask为每次询问交互机返回的结果 
int find_x()//找到没有车的那一行 
{
	l = 1,r = n;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		cout << "? " << l << " " << mid << " " << 1 << " " << n << endl;
		cin >> ask;
		if (ask == mid - l + 1)//结果和长度相等 
			l = mid + 1;//前面没有少车，说明在右边 
		else
			r = mid;//否则前面少车了，在左边 
	}
	return l;//l为最终答案 
}
int find_y()//找到没有车的那一列 
{
	l = 1,r = n;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		cout << "? " << 1 << " " << n << " " << l << " " << mid << endl;//注意这里询问的格式不同！ 
		cin >> ask;
		if (ask == mid - l + 1)
			l = mid + 1;
		else
			r = mid;
	}
	return l;
}//同上 
int main()
{
	cin >> n;
	int x = find_x(); 
	int y = find_y();
	cout << "! " << x << " " << y << endl;//注意输出和输入的格式，不要少空格！ 
	return 0;
}
```

---

## 作者：__HHX__ (赞：1)

# 大意
给定 $n \times  n$ 的棋盘，里面有 $n - 1$ 个**互相不能攻击**的车。

现在让你放一个车在棋盘里并且保证里面的车还是**互相不能攻击**。
# 思路
因为车的攻击**只限于本行与本列**，所以**每一行每一列只有一辆车**。

当一个格子的**行和列都没有棋子**，这个格子就是答案。

因为每一行每一列只有一辆车，所以我们可以压成**只有一列和只有一行**的序列。

然后把这两个序列做一遍前缀和，就会发现前面是**前缀和与序列号相等**的数，后面是**前缀和与序列号不相等相等**的数。

**第一个不相等**的数就是答案

这个题就变成二分答案的题目了。
# 代码
```cpp
#include<iostream>
using namespace std;

int main() {
	int n, z;
	cin >> n;
	int x, y, l = 1, r = n;
	while(l < r) {
		int mid = (l + r) >> 1;
		cout << '?' << ' ' << l << ' ' << mid << ' ' << 1 << ' ' << n << '\n';
		cin >> z;
		if(z == mid - l + 1) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}
	x = l;
	l = 1, r = n;
	while(l < r) {
		int mid = (l + r) >> 1;
		cout << '?' << ' ' << 1 << ' ' << n << ' ' << l << ' ' << mid << '\n';
		cin >> z;
		if(z == mid - l + 1) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}
	y = l;
	cout << '!' << ' ' << x << ' ' << y << '\n';
	return 0;
}
```

---

## 作者：_GW_ (赞：1)

## 思路
交互题。

看到 $n$ 的范围和二十次的询问次数，！二分！

事实上也确实可以。

我们先二分答案的横坐标，如果 $a=1,b=mid,c=1,d=n$ 正好有 $mid$ 辆车，则已经放满了，再放就一定会能和 $mid$ 辆车的其中一辆互相攻击了，横坐标一定在 $mid$ 之后，否则就在 $mid$ 之前。

同理，纵坐标也可以这样做：如果 $a=1,b=n,c=1,d=mid$ 时正好有 $mid$ 辆车，则已经放满了，答案一定在后面，反之亦然。

最后输出即可，AC！

## code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a,b,l,r,n,m,num,val,aa;
int get(int a,int b,int c,int d){cout<<"? "<<a<<" "<<b<<" "<<c<<" "<<d<<endl;cin>>aa;return aa;}
signed main()
{
    cin>>n;
	l=1,r=n;
    while(l<r)
    {
        int mid=l+r>>1;
        if(get(1,mid,1,n)==mid) l=mid+1;
        else r=mid;//二分横坐标
    }a=l;l=1,r=n;
    while(l<r)
    {
        int mid=(l+r)/2;
        if(get(1,n,1,mid)==mid) l=mid+1;
        else r=mid;//二分纵坐标
    }
    cout<<"! "<<a<<" "<<r<<endl;
    return 0;
}
```
## 本题一维版

[P1733](https://www.luogu.com.cn/problem/P1733)

---

## 作者：封禁用户 (赞：0)

水题。

因为车每行每列均只能有一个，所以考虑分别确定哪一行以及哪一列没有车。

由于最多询问 $20$ 次，所以考虑二分：

* 对于车的行：

令 $cnt_{(x,y),(c,d)}$ 为左上角 $(x,y)$，右下角 $(c,d)$ 的子矩阵的车的数量。

* $cnt_{(l,1),(mid,n)}= mid-l+1$，那么对于 $l\sim mid$ 这些行来说都有车，答案必定在 $mid+1\sim r$ 这些行中。

* $cnt_{(1,l),(n,mid)}= mid-l$，那么对于 $l\sim mid$ 这些行来说必定有一行没有车，答案必定在 $l\sim mid$ 这些行中。

因为棋盘上已经有 $n-1$ 个车，所以不会有其他情况。

对于列同理。

这样行的询问次数和列的询问次数都是 $O(\log n)$，在 $n=10^3$ 时这个数小于 $10$，总共次数小于 $20$，足以通过本题。

```cpp
#include<bits/stdc++.h>
#define sd std::
//#define int long long
#define inf 0x3f3f3f3f
#define linf 1e18
#define il inline
#define db double
#define ldb long double
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define umap(x,y) sd unordered_map<x,y>
#define pque(x) sd priority_queue<x>
#define X first
#define Y second
#define kg putchar(' ')
#define Fr(a) for(auto it:a)
#define dbg(x) sd cout<<#x<<": "<<x<<sd endl
#define clear fflush(stdout)
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);sd cout<<sd endl;}
il void printk(int x){print(x);kg;}
const int N=1e5+10;
int n,x,y;
il void solve()
{
	n=read();
	int l=1,r=n;
	while(l<r)//确定行 
	{
		int mid=l+r>>1,len=mid-l+1;//len为长度 
		printf("? %d %d %d %d\n",l,mid,1,n);
		clear;
		int ans=read();
		if(ans==len) l=mid+1;
		else r=mid;
	}
	x=l;
	l=1,r=n;
	while(l<r)//确定列 
	{
		int mid=l+r>>1,len=mid-l+1;
		printf("? %d %d %d %d\n",1,n,l,mid);
		clear;
		int ans=read();
		if(ans==len) l=mid+1;
		else r=mid;
	}
	y=l;
	printf("! %d %d",x,y);
	clear;
}
int main()
{
	int T=1;
//	T=read();
	while(T--) solve();
    return 0;
}
```

---

## 作者：zhu_wen (赞：0)

# Last Rook
## [原题传送门](https://atcoder.jp/contests/abc269/tasks/abc269_E)
## 思路
~~本题就是个大水题~~，找到一个位置，使得所有的 $n$ 辆车互相不能攻击。
- 二分枚举其中的行和列 $x=l$ 和 $y=r$。

这就是本题的答案，**但注意本题的输出格式**。

别忘了在二分之间，左右指针要进行初始化。
## 代码
```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fi first
#define se second
#define re register
#define swap(a, b) a ^= b, b ^= a, a ^= b
#define pb push_back
#define all(x) x.begin(), x.end()
#define fst                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int Max = 1e3 + 5;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

inline int read()
{
    int x = 0;
    bool f = true;
    char c = getchar();
    while (c < 48 || c > 57)
    {
        if (c == '-')
            f = false;
        c = getchar();
    }
    while (c >= 48 && c <= 57)
        x = (x << 3) + (x << 1) + c - 48, c = getchar();
    return f ? x : -x;
}
inline void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}
inline void wsp(int x) { write(x), putchar(' '); }
inline void wel(int x) { write(x), putchar('\n'); }

int n, l, r;
int x, y;

signed main()
{
    fst;
    n = read();
    l = 1, r = n;
    while (l < r) // 二分行
    {
        int mid = l + r >> 1;
        cout << "?"
             << " " << l << " " << mid << " " << 1 << " " << n << endl;
        int res;
        res = read();
        if (res == mid - l + 1)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    int x = l;
    l = 1, r = n; //别忘了初始化二分
    while (l < r) // 二分列
    {
        int mid = l + r >> 1;
        cout << "?"
             << " " << 1 << " " << n << " " << l << " " << mid << endl;
        int res;
        res = read();
        if (res == mid - l + 1)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    int y = r;
    cout << "!"
         << " " << x << " " << y << endl;
    return 0;
}
```


---

## 作者：Windy_Hill (赞：0)

## 题意
有一个 $n \times n$ 的棋盘，每行每列只能放一个棋子，其中还可以再放下一个棋子，你每次可以询问一个矩阵 $ (a,c) $ 到 $(b,d)$ 内有几颗棋子，最多询问 $20$ 次，问哪里还可以再放一颗棋子。

## 思路
既然每行每列只能放一颗棋子，那么我们可以询问行与列，每行每列是否可以放，由于 $1 \le n \le 1000$，我们可以想到二分枚举枚举行和列，每行每列最多给 $10$ 次，$1000 < 2^{10}$，所以方案可行。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int n;

bool check_row(int l, int r)//检查行行不行
{
    printf("? %d %d %d %d\n", l, r, 1, n);
    int x;
    cin >> x;
    return (x == r - l + 1 ? false : true);//是否满足矩阵内的车放满
}

bool check_col(int l, int r)//检查列行不行
{
    printf("? %d %d %d %d\n", 1, n, l, r);
    int x;
    cin >> x;
    return (x == r - l + 1 ? false : true);//是否满足矩阵内的车放满
}

int main()
{
    cin >> n;

    int x, y;
    int l = 1, r = n;

    while (l < r)//二分
    {
        int mid = (l + r) / 2;
        if (check_row(l, mid) == true) r = mid;//可行
        else l = mid + 1;//不可行
    }
    x = l;

    l = 1, r = n;
    while (l < r)//二分
    {
        int mid = (l + r) / 2;
        if (check_col(l, mid) == true) r = mid;//可行
        else l = mid + 1;//不可行
    }
    y = l;

    printf("! %d %d", x, y);

    return 0;
}

```


---

## 作者：Crazyouth (赞：0)

**分析**

看到交互题，先看交互次数。发现交互次数接近 $2\log_2n$，想到二分。题目要求唯一没有车的行与列，那就二分这两个东西就行了，每次询问从左端点到 $mid$ 的行或列的子矩阵，如果答案是 $mid-l+1$（$l$ 为左端点），就搜索 $mid$ 到右端点的区间，否则搜左端点到 $mid$ 的区间。

P.S. 赛后 vp 时写的先二分列后二分行，所以代码是先定 $y$ 再定 $x$ 的（$(x,y)$ 为要求的坐标）。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int x,y;
	int l,r,mid;
	int n;
	cin>>n;
	l=1;r=n;mid=(l+r)>>1;
	while(r-l>=1)//二分列
	{
		mid=(l+r)>>1;
		cout<<"? 1 "<<n<<' '<<l<<' '<<mid<<endl;
		cout.flush();
		int ans;
		cin>>ans;
		if(ans!=(mid-l+1))//左区间少车
		r=mid;//查询左区间
		else l=mid+1;//查询右区间
	}
	y=l;
	l=1;r=n;mid=(l+r)>>1;
	while(r-l>=1)//二分行，同上
	{
		mid=(l+r)>>1;
		cout<<"? "<<l<<' '<<mid<<" 1 "<<n<<endl;
		cout.flush();
		int ans;
		cin>>ans;
		if(ans!=(mid-l+1))
		r=mid;
		else l=mid+1;
	}
	x=l;
	cout<<"! "<<x<<' '<<y;
	return 0; 
}

---

## 作者：__Dist__ (赞：0)

~~没见过这么水的E题~~

## 题目描述

棋盘上要放 $n$ 个车，已经放好的 $n-1$ 个，你要跟机器询问先前 $n-1$ 个放在哪里，并指出第 $n$ 个车要放在哪里。

## 思路讲解

一道简单的交互题。很多交互题都会用到二分，所以这道题自然会想到二分啦。

我们可以二分分别枚举 $a$ 和 $b$、$c$ 和 $d$，记录两次最终左端点的值，即是答案。

## 代码环节

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int l,r;
int x,y;//第n个车的位置 
int main()
{
	cin>>n;
	l=1,r=n;
	while(l<r)
	//二分枚举a、b 
	{
		int mid=(l+r)>>1;
		printf("?%d %d %d %d\n",l,mid,1,n);
		int p;
		cin>>p;
		if(p==mid-l+1)
		{
			l=mid+1;
		}
		else
		{
			r=mid;
		}
	}
	x=l;
	l=1,r=n;
	while(l+1<=r)
	//二分枚举c、d 
	{
		int mid=(l+r)>>1;
		printf("?%d %d %d %d\n",1,n,l,mid);
		int p;
		cin>>p;
		if(p==mid-l+1)
		{
			l=mid+1;
		}
		else
		{
			r=mid;
		}
	}
	y=l;
	printf("!%d %d\n",x,y);
	return 0;
}
```

---

## 作者：Neilchenyinuo (赞：0)

- 本题可以使用二分做。

## Solution

1. 先二分横坐标，如果 $a=1,b=mid,c=1,d=n$ 时，说明已放满，再放就会相互攻击，所以答案在后，否则答案在前。

2. 二分纵坐标也是一样，如果 $a=1,b=n,c=1,d=mid$ 时，说明已放满，答案在后，反之，答案在前。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int ans,n,m,s;
int get_ans(int a,int b,int c,int d)
{
	cout<<"? "<<a<<" "<<b<<" "<<c<<" "<<d<<"\n";
	cin>>s;
	return s;
}
signed main()
{
    cin>>n;
    int lt=1,rt=n;
    while(lt<rt)
    {
        int mid=(lt+rt)>>1;
        if(get_ans(1,mid,1,n)==mid)
	    lt=mid+1;
        else
	    rt=mid;
    }
    ans=lt,lt=1,rt=n;
    while(lt<rt)
    {
        int mid=(lt+rt)>>1;
        if(get_ans(1,n,1,mid)==mid)
	    lt=mid+1;
        else
	    rt=mid;
    }
    cout<<"! "<<ans<<" "<<rt<<"\n";
    return 0;
}
```


---

## 作者：guanyf (赞：0)

### 题意
- 有一个 $N \times N$ 的棋盘，棋盘上有 $N-1$ 个互相不冲突的车，很容易想到，在位置 $(x,y)$ 还可以放一个车。现在你可以询问至多 $20$ 次，内容为：左上角为 $(a,c)$ 右下角为 $(b,d)$ 的矩阵中车的数量。求 $x,y$。

- $2 \le N \le 10 ^ 3$

### 分析、思路
可以发现：由于每行每列最多就只有 $1$ 个车，因此递增的行或列中车的数量具有单调性，所以可以二分。

先找到车所在的行。设 $l$ 初始时为 $1$，$r$ 初始时为 $N$，$mid = \lfloor \frac{l+r}{2} \rfloor$。当 $(l,1),(mid,N)$ 中车的数量等于 $mid-l+1$ 时，则查找右半边，$(l=mid+1)$；否则查找左半边，$r=mid$。

列也跟行差不多。当找到行和列的时候，直接输出。

由于对于行或列来说，最多询问 $10$ 次，而 $2 ^ {10} = 1024$，大于 $\max(N)$，因此是正确的。

时间复杂度：$\operatorname{O}(\log(N))$。

#### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, lx, ly, rx, ry, x, y;
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  lx = ly = 1, rx = ry = n;
  for (int mid, t; lx < rx;) {
    mid = (lx + rx) >> 1;
    cout << "? " << lx << ' ' << mid << ' ' << ly << ' ' << ry << endl;
    cin >> t;
    if (t == mid - lx + 1) {
      lx = mid + 1;
    } else {
      rx = mid;
    }
  }
  x = lx, lx = ly = 1, rx = ry = n;
  for (int mid, t; ly < ry;) {
    mid = (ly + ry) >> 1;
    cout << "? " << lx << ' ' << rx << ' ' << ly << ' ' << mid << endl;
    cin >> t;
    if (t == mid - ly + 1) {
      ly = mid + 1;
    } else {
      ry = mid;
    }
  }
  y = ly;
  cout << "! " << x << ' ' << y <<endl;
  return 0;
}
```


---

## 作者：charleshe (赞：0)

注意互相不能攻击的定义：

> 在任何一行中最多只有一辆车，在任何一列中最多只有一辆车。

再根据棋盘上已有 $n - 1$ 辆车，容易发现该棋盘的 $n$ 行中有 $n - 1$ 行有一辆车，$1$ 行没有车；$n$ 列中有 $n - 1$ 列有一辆车，$1$ 列没有车。显然这没有车的一行和一列的交汇点就是我们要寻找的第 $n$ 个放置车的点。

于是问题被转化成了：

- 在 $n$ 行中找到 $1$ 个没有放置车的行；

- 在 $n$ 列中找到 $1$ 个没有放置车的列。

由于可以将棋盘转置把第二问转化为第一问，所以此处仅讨论第一问的求解过程。

考虑二分。二分该棋盘的行，设 $l$ 为二分左端点，$r$ 为二分右端点，$mid = \dfrac{1}{2} \times (l + r)$，则对于 $l$ 至 $mid$ 这个区间内做一次 `? l mid 1 n` 的询问（求列时询问 `? 1 n l mid`）。

Q：为什么要有一个 $1$ 和一个 $n$ 混入询问操作？

A：显然我们此时只关心哪一行（或列）没有放车，则对于列（或行）只需要询问一组 `1 n`，询问全部区间，相当于没有询问（并不会影响行（或列）的返回结果）。

显然，只有两种可能的返回结果：

1. $mid - l + 1$：说明 $l$ 行至 $mid$ 行全部放了车，那么没放车的那行只会在 $mid + 1$ 行至 $r$ 行中，将 $l$ 设定为 $mid + 1$。

2. $mid - l$：说明 $l$ 行至 $mid$ 行中有一行没放置车，将 $r$ 设定为 $mid$。

接下来证明只有这两种可能的返回结果：

对于一个非上述两种情况的返回结果，有两种可能：

1. 小于 $mid - l$：说明有不止一个行没放置车，与题意不符，舍去。

2. 大于 $mid - l + 1$：说明有少于 $0$ 个点没放置车，显然不可能。

根据上述条件去不断二分，最终当 $l = r$ 时，就得到了唯一没放置车的一行。列同理。

因此，该算法询问次数为 $2 \times \left\lfloor\log_2n\right\rfloor$。在 $n = 1000$ 的最大限度时该算法需要询问正好 $20$ 次，可以通过。

```cpp
#include <iostream>
using namespace std;
int n,x,y,l,r,ans;
int main(){
	cin>>n;
	l=1,r=n;
	while(l<r){
		int mid=l+r>>1;
		cout<<"? "<<l<<" "<<mid<<" 1 "<<n<<endl;
		cin>>ans;
		if(ans==mid-l+1) l=mid+1;
		else r=mid;
	}
	x=l;
	l=1,r=n;
	while(l<r){
		int mid=l+r>>1;
		cout<<"? 1 "<<n<<" "<<l<<" "<<mid<<endl;
		cin>>ans;
		if(ans==mid-l+1) l=mid+1;
		else r=mid;
	}
	y=l;
	cout<<"! "<<x<<" "<<y<<endl;
	return 0;
} 
```


---

## 作者：heaksicn (赞：0)

## 1 题意

交互。

在一个 $n$ 行 $n$ 列的网格中，除了某一个点，其他点都有一个棋子。

每次可以询问一个方阵，问这个方阵中有多少个棋子。

最多进行 $20$ 次询问，求出没有棋子的点的位置。

## 2 思路

首先观察到 $n\leq 10^3$，有因为 $q\leq 20$，所以大多数和二分有点联系。

那如果直接二分方阵，肯定是不好做的，所以我们考虑将行和列分开询问。

假设当前区间为 $[l,r]$，每次我们询问 $[l,mid]$ 行中的棋子数量，如果棋子数量不为 $(mid-l+1)\times n$，说明没有棋子的点在左边，否则在右边。

列的操作类似。

由于 $n\leq 10^3$，行和列分别最多做 $\log n$ 次询问，可以通过此题。

## 3 code

```cpp
#include<bits/stdc++.h>
using namespace std; 
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n;
signed main(){
	int n=read();
	int l=1,r=n;
	int now=n-1;
	while(l<r){
		int mid=(l+r)/2;
		cout<<"? "<<l<<" "<<mid<<" "<<1<<" "<<n<<endl;
		fflush(stdout);
		int tp=read();
		if(tp>now-tp) l=mid+1,now=now-tp;
		else r=mid,now=tp;
	}
	int x=l;
	now=n-1,l=1,r=n;
	while(l<r){
		int mid=(l+r)/2;
		cout<<"? "<<1<<" "<<n<<" "<<l<<" "<<mid<<endl;
		fflush(stdout);
		int tp=read();
		if(tp>now-tp) l=mid+1,now=now-tp;
		else r=mid,now=tp;
	}
	cout<<"! "<<x<<" "<<l;
	fflush(stdout);
	return 0;
}
```


---


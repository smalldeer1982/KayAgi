# Tolik and His Uncle

## 题目描述

今天早上，Tolik 意识到，在他睡觉的时候，他发明了一个非常棒的问题，非常适合放在 Codeforces 上！但是，由于“讨论题目”项目（英文版）还没有诞生，他决定先测试一下这个题目，并请教了他的叔叔。

Tolik 的叔叔思考了很久，还是没有想出解决方法。但他又不想让 Tolik 知道自己不会做，于是他决定向你请教如何解决这个问题。

在本题中，给定一个 $n \times m$ 的网格，由 $n$ 行 $m$ 列组成，其中点的坐标 $(x, y)$ 表示它位于第 $x$ 行第 $y$ 列（行列编号均从 $1$ 开始，$1 \leq x \leq n, 1 \leq y \leq m$）。你最初站在单元格 $(1, 1)$。每一步，你可以从当前所在的单元格 $(x, y)$ 跳到 $(x+dx, y+dy)$，其中 $(dx, dy)$ 是任意非零向量。显然，你不能跳出网格，并且还有一个重要条件——每个向量只能使用一次，不能重复。你的任务是恰好访问网格中的每一个单元格一次（初始单元格视为已访问）。

Tolik 的叔叔是一位非常受人尊敬的人。请你帮助他解决这个问题！

## 说明/提示

第一个样例中的跳跃向量依次为 $(0, 2), (0, -1), (1, 0), (0, 1), (0, -2)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 3
```

### 输出

```
1 1
1 3
1 2
2 2
2 3
2 1```

## 样例 #2

### 输入

```
1 1
```

### 输出

```
1 1
```

# 题解

## 作者：wucstdio (赞：7)

### 题意

你需要从$(1,1)$开始遍历一个$n\times m$的网格，满足任意两步之间你行走的向量都不相同。

### 题解

首先我们考虑$1\times m$的怎么做。

这时候所有的向量第一维都是$0$，所以我们只需要让第二维互不相同即可。

构造方法就是$1,m,2,m-1,3,m-2,4,m-3\cdots$，也就是每次把左右端点拿出来分成一组，然后依次遍历。

如果$n>1$，我们考虑刚刚那个解法如何进行拓展。既然一维可以把左右端点拿出来配对，那么二维也就可以把上下两行拿来配对。

考虑到这里，构造方法就出来了，不太好说直接上代码吧：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n/2;i++)
	{
		for(int j=1;j<=m;j++)
		{
			printf("%d %d\n",i,j);
			printf("%d %d\n",n-i+1,m-j+1);
		}
	}
	if(n&1)
	{
		for(int i=1;i<=m/2;i++)
		{
			printf("%d %d\n",n/2+1,i);
			printf("%d %d\n",n/2+1,m-i+1);
		}
		if(m&1)printf("%d %d\n",n/2+1,m/2+1);
	}
	return 0;
}
```

---

## 作者：_always_ (赞：6)

# 题意
给定一个矩阵的边长 $n$ 和 $m$，要求以不同的向量到达矩阵中的每一个格子，并输出到达各自的顺序。   
以不同的向量，简单理解就是将当前格子和要去往的格子连线，使得整个过程中所有直线两两斜率不相同。   
# 思路
不太好直接构造，也不可能用类似搜索的做法（$1\leq n \times m \leq 10^6$）。    
本题最大的障碍是，如果按心情随便走，很有可能在走到某一个点时发现剩下的点都必须用到相同的向量才可到达，那我们不妨考虑一种有规律的方法。   
首先，考虑如果 $n=1$：   
显然，横坐标都是 $0$，纵坐标：$1,m,2,m-1,3,m-2,\ldots$。   
这里可以给我们一些启发：在这个过程中，向量时绝对不会重复的。    
![](https://cdn.luogu.com.cn/upload/image_hosting/pk90nqs5.png)   
（图丑见谅）    
图中蓝色向右走，红色向左走。可以发现，每一条水平的蓝红色线段两两不相等。    
那我们把这种方法扩展，对于 $n$ 行的矩阵，第一次在第 $1$ 行和第 $n$ 行之间跳，第二次在第 $2$ 行和第 $n-1$ 行之间跳，相当于横坐标是水平对称的。     
而纵坐标则竖直对称。以下图帮助理解（图中数字代表到达顺序）：    
![](https://cdn.luogu.com.cn/upload/image_hosting/9598y572.png)   
其实可以发现，每两行之间的跳跃不会出现向量相同的情况，当移动距离相同时，一定会有上下或左右方向相反。    
而扩展到另两行时，上下移动的距离又不相同，所以一定不会出现向量相同的情况。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m;

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n/2;i++)
		for(int j=1;j<=m;j++)
			printf("%d %d\n%d %d\n",i,j,n-i+1,m-j+1);
	if(n%2==1){
		int x=(n/2)+1;
		for(int i=1;i<=m/2;i++) printf("%d %d\n%d %d\n",x,i,x,m-i+1);
		if(m%2==1) printf("%d %d\n",x,(m/2)+1);
	}
	return 0;
}
```
完结撒花！

---

## 作者：bsdsdb (赞：1)

题意：给定 $n,m$，构造一个二维向量序列 $\{\boldsymbol x_{n,m}\}$，满足 $(1,1)$ 到 $(n,m)$ 各出现一次，且 $\boldsymbol {x_{i+1}}-\boldsymbol {x_i}$ 两两不同。

提示：考虑 $n=1$。

在 $n=1$ 时，有构造 $(1,1),(1,m),(1,2),(1,m-1),\cdots$。由于每次向右时距离会减少 $2$，向左同理，所以满足条件。对于二维，可以让 $(x,y)$（不是向量）遍历 $(1,n),(2,n-1),\cdots$，然后对于固定的 $x,y$，构造 $(x,1),(y,m),(x,2),(y,m-1),\cdots$ 即可。由于每次向下时向右的距离都会减少 $2$，向上同理，所以满足条件。当 $(x,y)$ 变为 $(x+1,y-1)$ 时，有相邻向量的差为 $(y-(x+1),1-1)=(y-x-1,0)$。由于 $(x,y)$ 固定时，$y-x\equiv n-1\pmod 2$，而 $y-x-1\not\equiv n-1\pmod 2$，又每次 $y-x-1$ 会减少 $2$，所以这不会带来和其他向量差的重复。

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

ll n, m;

int main() {
	read(n), read(m);
	for (ll i = 1; i <= n + 1 - i; ++i) {
		ll j = n + 1 - i;
		for (ll l = 1; l <= m; ++l) {
			ll r = m + 1 - l;
			if (i == j && r < l) {
				break;
			}
			write(i), space(), write(l), enter();
			if (i == j && r <= l) {
				break;
			}
			write(j), space(), write(r), enter();
		}
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

## 作者：FiraCode (赞：1)

## 思路:
先考虑 $n=2$ 怎么做，以 $n=2,m=3$ 为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/g2lwgsvf.png)

那么显然可以这么走：

![](https://cdn.luogu.com.cn/upload/image_hosting/tc68sg9c.png)

也就是是两边是对称的，所以这些增量都是形如 $(x,y_1),(-x,y_1),\dots$，而每个 $x,-x$ 循环中 $y$ 都不同那么是合法的。

进一步总结得出：

设当前坐标为 $(x, y)$。

*	若当前在上方，那么下一次坐标就是 $(x+1,m-y+1)$
*	若当前在下方，那么下一次坐标就是 $(x+1,m-y)$


而当 $n > 2$ 时，依以 $m=3$ 为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/aj4rurw9.png)

有一种走法时这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/vrsrkblo.png)

有没有发现什么规律？

首先对于 $(1,n),(2,n-1),\dots$ 这些行对之间仅有一条连边。

如图上 $(1,4)$ 与 $(2,3)$ 这两个行对之间仅有 $(4,1) \to (2,1)$ 这一条边。

然后在每个行对中按照上面总结的做即可。

若最后还剩一行的话，那么可以考虑 $x$ 不变 $y$ 是 $1 \to m \to 2 \to (m  -2)\dots$。

然后就做完啦。

## Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m;
bool st[1000010];

void dfs(int i, int j) {
	if (i > j) return;
	if (i == j) {
		for (int t1 = m, t2 = 1; t1 >= t2; --t1, ++t2) {
			if (t1 == t2) {
				printf("%d %d\n", i, t1);
			} else {
				printf("%d %d\n", i, t2);
				printf("%d %d\n", i, t1);
			}
		}
	} else {
		for (int dx = 1; dx <= m; ++dx) {
			if (dx == m) {
				printf("%d %d\n", j, m - dx + 1);
				if (i + 1 != j) {
					if (i + 1 != j - 1)
						printf("%d %d\n", i + 1, 1);
					dfs(i + 1, j - 1);
				}
				continue;
			}
			printf("%d %d\n", j, m - dx + 1);
			printf("%d %d\n", i, dx + 1);
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	if (n != 1)
		printf("%d %d\n", 1, 1);
	dfs(1, n);
	return 0;
}
```

---

## 作者：FallingFYC_ (赞：1)

[原题](https://www.luogu.com.cn/problem/CF1179B)

---
### 思路

先把问题简化，变成遍历一个 $1 \times m$ 的棋盘，很明显，遍历的方式即为 $1 , m , 2 , m - 1 \dots$。

可以把这种遍历方法应用到二维，具体来说，每次选取第 $i$ 行和第 $n - i + 1$ 行，遍历 $(i , 1) , (n - i + 1 , m) ,(i , 2) , (n - i + 1 , m - 1) \dots$，如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/0cbx8iaz.png)

---
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n , m;
int main()
{
    cin >> n >> m;
    for (int i = 1 , j = n ; i <= j ; i++ , j--)
        for (int k = 1 , l = m ; (i == j ? k <= l : k <= m && l >= 1)/*防止重复输出*/ ; k++ , l--) 
        {
            cout << i << ' ' << k << '\n';
            if (i != j || k != l) cout << j << ' ' << l << '\n';//防止重复输出
        }
    return 0;
}
```

---

## 作者：Wf_yjqd (赞：1)

很有意思的构造题。

------------

通过模拟样例 $1$ 的前三个操作，我们很容易想到只有 $1$ 行时的做法，即从 $1$ 到 $m$ 到 $2$ 到 $m-1$ 到 $3$ 到……

然后考虑沿用这个做法的思想，拓展到 $n$ 行。

每次用第一行剩余的第一个和第 $n$ 行剩余的最后一个更新位置。

显然对于这两行不会产生冲突。

而对于其他行，$dx$ 一定不同。

故为正确的构造方案。

模拟即可，复杂度 $\operatorname{O}(n\times m)$。

------------

没啥好说的结论题。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n/2;i++)
        for(int j=1;j<=m;j++)
            printf("%d %d\n%d %d\n",i,j,n-i+1,m-j+1);
    if(n&1){
        for(int i=1;i<=m/2;i++)
            printf("%d %d\n%d %d\n",n/2+1,i,n/2+1,m-i+1);
        if(m&1)
            printf("%d %d\n",n/2+1,m/2+1);
    }
    return 0;
}
```


---

## 作者：npqenqpve (赞：1)

### 题意：

你站在一个 $n\times m$ 的网格的 $(1,1)$ ，每次可以选择一个数对 $(dx,dy)$ ，把你的位置 $(x,y)$ 变为 $(x+dx,y+dy)$ ，使得你经过了每一个格点，并且没有重复使用同一个数对，请构造出路径。

### 思路：

神仙构造题，观察第一个样例，发现可以对于每一行都形如 $(1,y)-(n,y)-(2,y)-(n-1,y)$  这么走下来，考虑纵向怎么走。默认你在 $(a,b)$ 这个位置 ，大力构造，每次把未被处理的最下面一行和未被处理的最上面一行进行操作，即前两次的处理是 $(1,1)-(n,m)-(2,1)-(n-1,m)-...-(1,n)-(n,1)$ ，然后每次找该处理那两行即可。

注意分讨奇偶

### 代码（方法1）：

```cp
#include <bits/stdc++.h>
#define int unsigned long long
#define ull unsigned long long
#define ld long double
using namespace std;
int n,m;
signed main() 
{
    cin>>n>>m;
    int tx1,ty1,tx2,ty2;
    tx1=ty1=1,tx2=n,ty2=m;
    if(n%2&&m%2)
    {
        while(ty1!=ty2)
        {
            cout<<tx1<<" "<<ty1<<"\n"<<tx2<<" "<<ty2<<"\n";
            if(tx1==n)
            {
                tx1=1,tx2=n;
                ty1++,ty2--;
            }
            else tx1++,tx2--;
        }
        tx1=1,tx2=n,ty1=ty2=(m/2+1);
        while(tx1!=tx2)
        {
            cout<<tx1<<" "<<ty1<<"\n"<<tx2<<" "<<ty2<<"\n";
            tx1++,tx2--;
        }
        cout<<tx1<<" "<<ty1<<"\n";
    }
    if(n%2==0&&m%2)
    {
        while(ty1!=ty2)
        {
            cout<<tx1<<" "<<ty1<<"\n"<<tx2<<" "<<ty2<<"\n";
            if(tx1==n)
            {
                tx1=1,tx2=n;
                ty1++,ty2--;
            }
            else tx1++,tx2--;
        }
        tx1=1,tx2=n,ty1=ty2=(m/2+1);
        while(tx1<tx2)
        {
            cout<<tx1<<" "<<ty1<<"\n"<<tx2<<" "<<ty2<<"\n";
            tx1++,tx2--;
        }
    }
    if(n%2&&m%2==0)
    {
        while(ty1<ty2)
        {
            cout<<tx1<<" "<<ty1<<"\n"<<tx2<<" "<<ty2<<"\n";
            if(tx1==n)
            {
                tx1=1,tx2=n;
                ty1++,ty2--;
            }
            else tx1++,tx2--;
        }
    }
    if(n%2==0&&m%2==0)
    {
        while(ty1<ty2)
        {
            cout<<tx1<<" "<<ty1<<"\n"<<tx2<<" "<<ty2<<"\n";
            if(tx1==n)
            {
                tx1=1,tx2=n;
                ty1++,ty2--;
            }
            else tx1++,tx2--;
        }
    }
    // system("pause");
}
```



---

## 作者：XiaoQuQu (赞：0)

一道萌萌构造题。

考虑一些特殊情况，当 $n=1$ 时，我们可以这么构造：$1\to m\to 2\to \cdots $，由于每次我们横向移动的距离（即 $dx$）都不同，所以这是一个合法的答案，当 $n=2$ 的时候情况也差不多，我们可以 $(1,1)\to (2,m)\to (1,2)\to (2,m-1)\to\cdots\to (1,m-1)\to (2,2)\to (1,m)\to (2,1)$ 这么构造，保证了横向相同的纵向一定不同。

对于 $n>2$ 的情况，我们对于最上方、最下方的一行按照 $n=2$ 的方法构造，将中间的转化为一个 $n'=n-2$ 的子问题，递归地构造下去即可。

```cpp
int N, M;

void solve(int n, int m, int dx) {
	if (n == 1) {
		int l = 1, r = m;
		while (l < r) {
			cout << dx + 1 << ' ' << (l++) << endl;
			cout << dx + 1 << ' ' << (r--) << endl;
		}
		if (l == r) cout << dx + 1 << ' ' << r << endl;
		return;
	}
	int l = 1, r = m;
	while (l <= m) {
		cout << dx + 1 << ' ' << (l++) << endl;
		cout << N - dx << ' ' << (r--) << endl;
	}
	if (n > 2) solve(n - 2, m, dx + 1);
}

void work() {
	cin >> N >> M;
	solve(N, M, 0);
}
```


---

## 作者：Luo_gu_ykc (赞：0)

# CF1179B

## 题目大意

给顶一个 $n \times m$ 的矩阵，你要从 $(1, 1)$ 的位置出发，在向量不重复的情况下走遍所有矩阵所有的位置。

输出从 $(1, 1)$ 开始当前所在的位置。

- 向量：从 $(x_1, y_1)$ 走到 $(x_2, y_2)$ 的 $x$ 轴变化与 $y$ 轴变化的值。

## 思考过程

可能我们最暴力的方式就是全排列 $x$ 轴的变化，$y$ 轴的变化，当然超时是必然的。

这时，我们看看 $n \times m$ 的范围有 $10 ^ 6$，并没有给出 $n$ 和 $m$ 的范围，而只给出了 $n \times m$ 的范围，所以很明显时间复杂度是与 $n \times m$ 有很大关系的，大概率是 $O(n \times m)$ 的时间复杂度，~~这时候有个人点开了某蓝色的东西~~。

思考到这里，可以发现其实输出就是 $n \times m$ 的时间，为了在 $1s$ 通过，所以一定要在 $O(10 ^ 2)$ 做出，但我们发现，这个时间复杂度与题面给出的所有数基本没有关系，所以考虑 $O(1)$ 构造，我们首先先将这个问题简化一点，甚至说是简单地可以自己想到的答案，比如只构造一个序列，也就是 $n$ 为 $1$，那么其实很好想，我们可以先从 $1$ 走到 $m$ 再走到 $2$ 再走到 $m - 1$ 再 $\dots$ 一直走到中间的位置，可以发现，一次走的步数是越来越小的，因此构造规律也就出来了，先从最小的走到最大的，再走到次小和次大的，这样完全可以避免重复。

又因为题目说只是 $x$ 与 $y$ 的轴变化都不重复，所以明显，不仅 $x$ 轴可以满足这个规律，$y$ 轴也可以满足，所以答案就已经被构造了出来，总结一下：

1. 从变化 $x$ 轴可以发现，从小到大到次小再到次大一次走的路是越来越小的，所以不会有重复。

2. 因为要求的是两个轴变化时所组成的二元组不重复，也就是说 $y$ 轴也可以满足这个规律。

在 $x$ 轴按构造的变化规律变化下，我们只考虑 $y$ 轴，明显就是从 $1$ 到 $m$ 到 $2$ 在到 $m - 1 \dots$ 这就是 $y$ 轴的构造变化规律。

那问题又来了，是每次都变化 $x$ 和 $y$ 轴吗？

明显可以分析出来不能这样，只能优先变化 $y$ 轴一次，再在这两行中变化 $x$ 轴。

举个栗子，假设 $n$ 和 $m$ 都为 $3$。

那么我们的行走过程就会为 

$(1, 1) \to (3, 3) \to (1, 2) \to (3, 2) \to (1, 3) \to (3, 1) \to (2, 1) \to (2, 3) \to (2, 2)$

所以分析完毕，上代码：

## Code

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

int n, m;

signed main(){
	cin >> n >> m;
	for(int i = 1; i <= n / 2; i++){ // 变化 y 轴
		for(int j = 1; j <= m; j++){ // 变化 x 轴
			cout << i << ' ' << j << "\n"; 
			cout << n - i + 1 << ' ' << m - j + 1 << "\n";
		}
	}
	if(n % 2 == 1){ // 当 y 轴不能完全对应
		for(int j = 1; j <= m / 2; j++){ // 按序列处理
			cout << n / 2 + 1 << ' ' << j << "\n";
			cout << n / 2 + 1 << ' ' << m - j + 1 << "\n";
		}
		if(m % 2 == 1){ // x 轴也不能完全对应
			cout << n / 2 + 1 << ' ' << m / 2 + 1 << "\n";
		}
	}
	return 0;
}
```

---

## 作者：do_while_true (赞：0)

考虑每一步怎样走，所用的向量一定不能被后面用。

$(1,1)$ 自然是顶到头，尽可能往远走，也就是走到 $(n,m)$，$(+n-1,+m-1)$ 的向量被用过。这个时候可以发现除了 $(1,1)$，没有任何一个格子会用到这个向量。依次类推，$(n,m)$ 可以走到 $(1,2)$，使用 $(-(n-1),-(m-2))$ 这个向量，这个向量只有 $(n,m)$ 和 $(n,m-1)$ 能用，而 $(n,m-1)$ 用了会走到之前已经走过的 $(1,1)$，所以这一步用到的向量也一定不会被后面走到。

依次类推地走，会发现最终走到了 $(n,1)$，且每一步用的向量都不会被后面的用到。

然后再跳到 $(2,1)$，$(-(n-2),+0)$ 也不会被后面的用到，这样就剩下了一个子问题。

最终中间可能会剩一行，也是类似的走法，每次走到最边上的格子，保证每一步用的向量一定不会被后面用即可。

```cpp
//Code by do_while_true
#include<iostream>
#include<cstdio>
#include<algorithm>
typedef long long ll;
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T> T Abs(T x) { return x < 0 ? -x : x; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 1000010;
int n, m;
signed main() {
	read(n); read(m);
	for(int i = 1; i <= n / 2; ++i)
		for(int j = 1; j <= m; ++j)
			printf("%d %d\n%d %d\n", i, j, n-i+1, m-j+1);
	if(n & 1) {
		for(int i = 1; i <= m / 2; ++i)
			printf("%d %d\n%d %d\n", n/2+1, i, n/2+1, m-i+1);
		if(m & 1) printf("%d %d\n", n/2+1, m/2+1);
	}
	return 0;
}
```

---

## 作者：PI_AC (赞：0)

# 题目

[Tolik and His Uncle](https://www.luogu.org/problem/CF1179B)

# 题解

首先考虑只有一行的情况：

很明显就是从$(1, 1)$走到$(1, n)$，然后到$(1, 2)(1, n - 1)$……

其次就是多行的情况：

我们类比一行的情况。只有一行时我们只对列进行更改，多行时我们就直接把行的更改加入就行了

顺序如下：

$(1,1)(n,n)(1,2)(n,n-1)$……

$(2,1)(n-1,n)(2,2)(n-1,n-1)$……

……

# 代码

```cpp
#include <map>
#include <set>
#include <cmath>
#include <deque>
#include <queue>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
T Max(T x, T y) {return x > y ? x : y;}

template <typename T>
T Min(T x, T y) {return x < y ? x : y;}

template <typename T>
T Fabs(T x) {return x < 0 ? -x : x;}

#define LL long long

int n, m, px, py;

int main() {
    scanf("%d %d", &n, &m);
    px = py = 1;
    for(int i = 1; i <= n / 2; i ++) {
        for(int j = 1; j <= m; j ++) {
            printf("%d %d\n", i, j);
            printf("%d %d\n", n - i + 1, m - j + 1);
        }
    }
    if(n & 1) {
        for(int i = 1; i <= m / 2; i ++) {
            printf("%d %d\n", n - n / 2, i);
            printf("%d %d\n", n - n / 2, m - i + 1);
        }
        if(m & 1)
            printf("%d %d\n", n - n / 2, m - m / 2);
    }
    return 0;
}
```

---

## 作者：qcwlmqy (赞：0)

# 分析
明显是一道构造题
构造题，可以从小的例子开始构造，寻找规律
## 首先，我们看一维的例子：

1，2：
（1，1）->（1，2）

1，3：
（1，1）->（1，3）->（1，2）

1，4：
（1，1）->（1，4）->（1，2）->（1，3）

1，5：
（1，1）->（1，5）->（1，2）->（1，4）->（1，3）

容易发现对于一维的构造我们可以通过关于中心对称的方法构造，因为左右指针向中间靠，则每次的移动距离为n-i（i为移动步数）

## 那这个方法能不能扩展到二维呢？

即关于中心对称

对于两行的情况 2，3：

（1，1）->（2，3）->（1，2）->（2，2）->（1，3）->（2，1）

每两次移动为（1，n  - i）和（-1，n - 1 - i）

关于每两行都如是操作

对于正中的行如一维操作即可
## 代码
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#pragma warning (disable:4996)
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n / 2; i++) {	//对于每两行关于中心对称
		for (int j = 1; j <= m; j++) {
			printf("%d %d\n", i, j);
			printf("%d %d\n", n + 1 - i, m + 1 - j);
		}
	}
	if (n & 1) {	//中间行如一维操作
		n = (n + 1) / 2;
		for (int i = 1; i <= m / 2; i++) {
			printf("%d %d\n", n, i);
			printf("%d %d\n", n, m + 1 - i);
		}
		if (m & 1) printf("%d %d\n", n, (m + 1) / 2);
	}
}
```


---


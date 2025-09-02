# Tenzing and Books

## 题目描述

Tenzing received $ 3n $ books from his fans. The books are arranged in $ 3 $ stacks with $ n $ books in each stack. Each book has a non-negative integer difficulty rating.

Tenzing wants to read some (possibly zero) books. At first, his knowledge is $ 0 $ .

To read the books, Tenzing will choose a non-empty stack, read the book on the top of the stack, and then discard the book. If Tenzing's knowledge is currently $ u $ , then his knowledge will become $ u|v $ after reading a book with difficulty rating $ v $ . Here $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR). Note that Tenzing can stop reading books whenever he wants.

Tenzing's favourite number is $ x $ . Can you help Tenzing check if it is possible for his knowledge to become $ x $ ?

## 说明/提示

For the first test case, Tenzing can read the following $ 4 $ books:

- read the book with difficulty rating $ 1 $ on the top of the first stack. Tenzing's knowledge changes to $ 0|1=1 $ .
- read the book with difficulty rating $ 1 $ on the top of the third stack. Tenzing's knowledge changes to $ 1|1=1 $ .
- read the book with difficulty rating $ 2 $ on the top of the first stack. Tenzing's knowledge changes to $ 1|2=3 $ .
- read the book with difficulty rating $ 5 $ on the top of the second stack. Tenzing's knowledge changes to $ 3|5=7 $ .

After reading all books, Tenzing's knowledge is $ 7 $ .

For the third test case, Tenzing can read $ 0 $ books to make his final knowledge equals to $ 0 $ .

## 样例 #1

### 输入

```
3
5 7
1 2 3 4 5
5 4 3 2 1
1 3 5 7 9
5 2
3 2 3 4 5
5 4 3 2 1
3 3 5 7 9
3 0
1 2 3
3 2 1
2 2 2```

### 输出

```
Yes
No
Yes```

# 题解

## 作者：paramecium_ (赞：4)

## 题目大意

给定 $a$，$b$，$c$ 三个大小为 $n$ 栈，把 $u$ 初始化为 $0$，接下来可以挑选三个栈顶的的一个数 $v$，每次进行一次操作，使得 $u=u \operatorname{or} v$，最终问你 $u$ 能不能变为 $x$（不懂位运算的[戳这里](https://oi-wiki.org/math/bit/#%E4%B8%8E%E6%88%96%E5%BC%82%E6%88%96)）。

## 题目思路

比较暴力的贪心，尽量的多看一些书，到最后如果和 $x$ 相同就出 `yes`，这里提一嘴 `yEs`、`yes`、`Yes`、`YES` 都是可以的否则栈空的话的话就 `no`。

## 代码

本人不打空格还压行，码风太丑请见谅。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define P
#define R read()
#define int long long
const int N=1e5+5;
int a[N],b[N],c[N],t,n,x;
inline int read(){//快读
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();} 
	return x*f;
}
signed main(){
	t=R;
	while(t--){
		n=R;x=R;
		int xa=1,xb=1,xc=1,now=0;//多组数据初始化，直接开在循环里
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>b[i];
		for(int i=1;i<=n;i++) cin>>c[i];
		while(xa<=n&&(a[xa]|x)==x) now|=a[xa++];//判断是否栈顶是否合法，不合法退出
		while(xb<=n&&(b[xb]|x)==x) now|=b[xb++];//同理
		while(xc<=n&&(c[xc]|x)==x) now|=c[xc++];
		if(now==x) P("Yes\n");
		else P("No\n");
	}
	return 0;//结束
}
```

---

## 作者：sz_jinzikai (赞：2)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1842B)&[CF 传送门](https://codeforces.com/problemset/problem/1842/B)
# 题目大意
给定 $3$ 个大小为 $n$ 的栈，初始时整数 $u$ 的值为 $0$，可以取任意个元素，但是每次只可以取走三个栈顶元素中的一个数 $v$，$u=u\mid v$，问最终 $u$ 是否可能到达 $x$。（注：前面说的 $\mid$ 指的是按位或运算，下同。）
# 思路
本题需要用到按位或运算，而按位或有一个特点，就是转换成二进制后，某一位上一旦变成了 $1$，就再也不可能变回 $0$，但是如果某一位上是 $0$，它随时都可以变成 $1$，所以我们可以考虑用贪心。

贪心，就是把能选上的数全部选上，最后判断这些数按位或起来是不是 $x$ 即可。哪些数是能选的呢？那就是这个数转换成二进制后，它的所有为 $1$ 的位置上，$x$ 的这个位置也是 $1$，转换一下，就是 $x\mid v=x$。
# 代码
```cpp
# include <bits/stdc++.h> //万能头
using namespace std;
int t, n, x, now, ha, hb, hc, a[100005], b[100005], c[100005]; //定义变量
int main () { //定义主函数
	cin >> t; //输入数据组数
	while (t --) { //多组数据的经典写法
		cin >> n >> x; //输入元素个数和 x
		ha = hb = hc = now = 0; //多组数据要初始化
		for (reg int i = 0; i < n; ++ i)
			cin >> a[i]; //读入 a 数组
		for (reg int i = 0; i < n; ++ i)
			cin >> b[i]; //读入 b 数组
		for (reg int i = 0; i < n; ++ i)
			cin >> c[i]; //读入 c 数组
		while (ha < n && (a[ha] | x) == x) //判断是否栈顶是否合法，不合法退出，因为这是栈
			now |= a[ha ++]; //合法了，那就或上
		while (hb < n && (b[hb] | x) == x) //判断是否栈顶是否合法，不合法退出，因为这是栈
			now |= b[hb ++]; //合法了，那就或上
		while (hc < n && (c[hc] | x) == x) //判断是否栈顶是否合法，不合法退出，因为这是栈
			now |= c[hc ++]; //合法了，那就或上
		cout << (now == x ? "Yes\n" : "No\n"); //这是三目表达式，不懂也可以写成这样：
/*
		if (now == x)
        cout << "Yes\n";
		else
        cout << "No\n";
*/
	}
	return 0;
}
```

---

## 作者：D0000 (赞：2)

# CF1842B Tenzing and Books 题解
## 解法说明（贪心、位运算）
### 初步分析
由于是或运算，所以按照贪心策略，知识的二进制中 $0$ 的部分是不会的结果造成影响的，即只要满足某本书的二进制不存在不同于 $x$ 的 $1$，就拿走。如果有一本不能拿，则它底下的所有书全部不读。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
	int n, x, ans = 0;
	cin >> n >> x;
	vector<int> a(n + 1), b(n + 1), c(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	for (int i = 1; i <= n; i++) {
		if ((x | a[i]) == x) ans |= a[i];
		else break;
	}
	for (int i = 1; i <= n; i++) {
		if ((x | b[i]) == x) ans |= b[i];
		else break;
	}
	for (int i = 1; i <= n; i++) {
		if ((x | c[i]) == x) ans |= c[i];
		else break;
	}
	std::cout << (ans == x ? "Yes\n" : "No\n");
} 

int main() {
	sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}

```
## 易错点
1、这里有 $3$ 堆书

2、输入是**从上往下**

3、是**达到** $x$，不是超过
## 其它解法
我同学都使用递归做的

结果：**10分**（老师做的测试点）

建议大家不要使用


另外，建议难度设为 普及/提高-



**~~第一次提交题解，希望审核通过！~~**

---

## 作者：lzj666_luogu (赞：1)

## 题目大意

给定三个栈，每个栈有 $n$ 个非负数，初始值为 $u=0$，每取一个数 $v$，$u \leftarrow u|v$，问最终结果是否能达到 $x$。

## 分析

由于是按位或运算，二进制中 0 的部分在或了以后是会根据对方的值来影响结果的。

所以就有贪心策略：只要栈顶的元素在或上 $x$ 以后还等于 $x$，即 $x$ 二进制位上为 0 的部分其二进制位上也为 0 都选。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int stk[3][100000+10],top[3];
//三个栈，以及它们分别的顶 
int main(){
	ios_base::sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--){
		int n,x,u=0;
		cin>>n>>x;
		for(int j=0;j<3;++j)
			for(int i=1;i<=n;++i)
				cin>>stk[j][i];
		top[0]=top[1]=top[2]=1;
		//输入以及初始化三个栈
		for(int i=0;i<3;++i)
			while(top[i]<=n&&(stk[i][top[i]]|x)==x)
				u|=stk[i][top[i]++];
		//枚举三个栈分别操作 
		cout<<(u==x?"YES":"NO")<<endl;
	}
} 
```

---

## 作者：kczw (赞：0)

# 题意
共 $t$ 组数据。

每组数据给定三个大小为 $n$ 的栈和一数 $k$。现有 $u=0$，可让 $u$ 按位或上某一栈顶数字，并弹出此栈栈顶数。问最后能否使 $u=k$。
# 思路
做这道题首先要知道什么是按位或，这里浅讲一下。

按位或也就是指将两个数在二进制最低位对齐后每一位进行取或运算。举个例子，$5_{10}=101_2$ 和 $3_{10}=11_2$ 按位取或：
```
0101
0011
----
0111
```
得到 $111_2=7_{10}$。取或意味只要有一位为 $1$，结果取 $1$，否则取 $0$。知道了按位或，接下来可以分析题了。

首先，假设 $u$ 按位或了一些数。若最终 $u$ 二进制的某位上为 $0$，根据或操作的过程，我们可以知道，这意味 $u$ 按位或过的所有数二进制的相应的位子上为 $0$。相反的，若 $x$ 二进制的某一位上为 $1$，则说明按位或过的数中至少有一个数二进制的相应位子上为 $1$。

易得，$u$ 按位或的所有数二进制上为 $1$ 的部分对应到 $k$ 皆应有 $1$，否则最后不可得 $u=k$。所以按位或的每个数都应保证只在 $k$ 二进制上有 $1$ 的位置有 $1$，这也就说明 $u$ 按位或了 $x$ 还能得到 $u=k$ 可以推导出 $k|x=k$。

所以对于每个栈，若栈顶的数 $x$ 满足 $k|x=k$，便持续按位或直到不能满足，然后换下一个栈。若最后 $u\ne k$，则输出 `NO`，否则输出 `YES`。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int t,n,k,ans;
int a[3][N];
main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&k);
		ans=0;
		for(int l=0;l<=2;l++)
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[l][i]);
		for(int l=0;l<=2;l++)
		for(int i=1;i<=n&&(a[l][i]|k)==k;i++)
			ans|=a[l][i];
		if(ans==k)puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：rainygame (赞：0)

赛时因为样例太水导致错了 $4$ 次……两个晚上白熬了。

其实这是一道很水的题目，首先考虑按位或的性质：单调不降（也就是 $x$ 对另一个数按位或之后不会小于 $x$），那么我们就有一个想法：既然它是单调不降的，那我们可以尽量的多看一些书，到最后如果和 $x$ 相同，就 `YES`，否则就 `NO`。

不过注意看的书的值和 $x$ 按位或之后还是 $x$ 才可以看，这样才表示书的值比 $x$ 没有多余的 $1$。

考场代码优化版：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define for1(i, s, t) for (int i(s); i<=t; ++i)
#define for2(i, t, s) for (int i(t); i>=s; --i)
#define for3(i, vec) for (auto i: vec)
#define INF 0x3f3f3f3f
#define opb pop_back
#define pb push_back
#define pf push_front
#define opf pop_front
#define fi first
#define se second
#define gc() getchar()
#define pc(x) putchar(x);
#define sp pc(' ');
#define el pc('\n');
#define pr(x) printf(x);
#define Yes pr("YES");
#define No pr("NO");
#define err assert(0);
const int MAXN(1e5+2);
//const ll MOD(1e9+7);

ll re(){
    ll x(0), f(1);
    char ch;
    while ((ch = gc()) < 48) f = ch == '-' ? -1 : 1;
    do{
        x = (x << 1) + (x << 3) + (ch ^ 48);
    }while ((ch = gc()) > 47);
    return x * f;
}

void uwr(ll x){
    ll tmp(x/10);
    if (tmp) uwr(tmp);
    pc(x-(tmp<<1)-(tmp<<3)^48);
}

void wr(ll x){
    if (x < 0){
        pc('-');
        x = -x;
    }
    uwr(x);
}

int n, x, ind, now;
int a[MAXN], b[MAXN], c[MAXN];

void solve(){
	n = re();
	x = re();
	for1(i, 1, n) a[i] = re();
	for1(i, 1, n) b[i] = re();
	for1(i, 1, n) c[i] = re();
	
	now = ind = 0;
	while ((a[++ind] | x) == x && ind <= n) now = now | a[ind];
	ind = 0;
	while ((b[++ind] | x) == x && ind <= n) now = now | b[ind];
	ind = 0;
	while ((c[++ind] | x) == x && ind <= n) now = now | c[ind];
	pr(now == x ? "YES" : "NO");
}

int main(){
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);

    int t(1);
  t = re();
    while (t--){
        solve();
        el
    }

    return 0;
}


```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

题目中不限制阅读的书的数量。能读多少就读多少。

再考虑到按位或运算的特点，我们可以发现，如果一本书的“难度指数”（原文 difficulty rating）中二进制某一位为 $1$，那么阅读这本书后，主人公的知识指数（原文 knowledge）中二进制某一位也会变为 $1$，并且不可以变回 $0$。如果此时 $x$ 的这一位为 $0$，那么就证明这本书就不可以被阅读，这本书以后的书也不可以被阅读（同一堆书中，前面的书被阅读了，后面的才能被阅读）。

理解了上面这段话，题目就很好做了。更多思路请参见代码注释。

### 二、代码

```cpp
// Author: cyrxdzj
// Problem: B. Tenzing and Books
// Contest: CodeTON Round 5 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/1842/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<cstdio>
using namespace std;
int t;
int n;
int x;
bool bit_x[35];//x的二进制形式。
int a[4][100005];//a、b、c三个数组的内容。
bool bit_a[4][100005][35];//a、b、c三个数组的内容的二进制形式。
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&x);
        for(int i=1;i<=3;i++)
        {
            for(int j=1;j<=n;j++)
            {
                a[i][j]=0;
                for(int k=1;k<=34;k++)
                {
                    bit_a[i][j][k]=0;
                }
            }
        }
        for(int i=1;i<=34;i++)
        {
            bit_x[i]=0;
        }
        int tempx=x;
        for(int i=1;i<=34&&tempx;i++)//获取x的二进制形式
        {
            bit_x[i]=tempx&1;
            tempx>>=1;
        }
        for(int i=1;i<=3;i++)//获取a、b、c的二进制形式
        {
            for(int j=1;j<=n;j++)
            {
                scanf("%d",&a[i][j]);
                int tempa=a[i][j];
                for(int k=1;k<=34&&tempa;k++)
                {
                    bit_a[i][j][k]=tempa&1;
                    tempa>>=1;
                }
            }
        }
        int res=0;
        for(int i=1;i<=3;i++)
        {
            for(int j=1;j<=n;j++)
            {
                bool flag=true;//可否阅读？
                for(int k=1;k<=34;k++)
                {
                    if(bit_a[i][j][k]==1&&bit_x[k]==0)
                    {
                        flag=false;
                        break;
                    }
                }
                if(flag)
                {
                    res|=a[i][j];//阅读这本书。
                }
                else
                {
                    break;
                }
            }
        }
        printf((res==x)?"Yes\n":"No\n");
    }
    return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：0)

**【题目分析】**

分析或运算的性质，显然当一位上的数字变成 $1$ 的时候就不可能再成为 $0$。因此，我们能选的数字有且只有 $x$ 每个为 $0$ 的数位都是 $0$ 的数，也即 $a_i | x = x$。因此直接模拟，把所有能选的数字都选上，最后看得到的数字是否等于 $x$。

**【完整代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,n,m,x;
signed main(){
    cin >> t;
    while(t --){
    	int k = 0,f = 0;
    	cin >> n >> m;
    	for(int i = 1;i <= n;i ++){
    		cin >> x;
			if((x | m) == m && f == 0) k |= x;
			else f = 1;
		}
		f = 0;
		for(int i = 1;i <= n;i ++){
    		cin >> x;
			if((x | m) == m && f == 0) k |= x;
			else f = 1;
		}
		f = 0;
		for(int i = 1;i <= n;i ++){
    		cin >> x;
			if((x | m) == m && f == 0) k |= x;
			else f = 1;
		}
		if(k == m) cout << "Yes\n";
		else cout << "No\n";
	}
	return 0;
}
```

---

## 作者：Zhddd_ (赞：0)

题意简述：给定三个栈，每个栈有 $n$ 个非负数，初始值为 $u = 0$，每取一个数 $v$，$u\leftarrow u|v$，问最终结果是否能达到 $x$。

考虑贪心：

- 如果 $v$ 的二进制表示中，$1$ 的位置的集合为 $A$，$x$ 的二进制表示中，$1$ 的位置的集合为 $B$，如果 $A\in B$，那么选上 $v$，结果一定不会更差。（即对于任意一位，不存在 $v$ 的那一位是 $1$，$x$ 的那一位是 $0$ 的情况，那么一定要选 $v$）。

- 如果发现 $v$ 不能选，因为那是个栈，所以后面的数都不用考虑了。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int T;
int main() {
	scanf("%d", &T);
	while (T--) {
		int n, x, t = 0;
		scanf("%d%d", &n, &x);
		for (int i = 0; i < 3; i++) {
			int flag = 1;
			for (int j = 1; j <= n; j++) {
				int a;
				scanf("%d", &a);
				if (flag) {
					if ((~x) & (a)) flag = false;
					else {
						t |= a;
					}
				}
			}
		}
		if (t == x) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

---


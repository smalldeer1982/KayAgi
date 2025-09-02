# Trouble Sort

## 题目描述

Ashish has $ n $ elements arranged in a line.

These elements are represented by two integers $ a_i $ — the value of the element and $ b_i $ — the type of the element (there are only two possible types: $ 0 $ and $ 1 $ ). He wants to sort the elements in non-decreasing values of $ a_i $ .

He can perform the following operation any number of times:

- Select any two elements $ i $ and $ j $ such that $ b_i \ne b_j $ and swap them. That is, he can only swap two elements of different types in one move.

Tell him if he can sort the elements in non-decreasing values of $ a_i $ after performing any number of operations.

## 说明/提示

For the first case: The elements are already in sorted order.

For the second case: Ashish may first swap elements at positions $ 1 $ and $ 2 $ , then swap elements at positions $ 2 $ and $ 3 $ .

For the third case: The elements are already in sorted order.

For the fourth case: No swap operations may be performed as there is no pair of elements $ i $ and $ j $ such that $ b_i \ne b_j $ . The elements cannot be sorted.

For the fifth case: Ashish may swap elements at positions $ 3 $ and $ 4 $ , then elements at positions $ 1 $ and $ 2 $ .

## 样例 #1

### 输入

```
5
4
10 20 20 30
0 1 0 1
3
3 1 2
0 1 1
4
2 2 4 8
1 1 1 1
3
5 15 4
0 0 0
4
20 10 100 50
1 0 0 1```

### 输出

```
Yes
Yes
Yes
No
Yes```

# 题解

## 作者：封禁用户 (赞：7)

### 题意

对于一个数组 $a$ 以及每个数的属性 $b$，可以交换两个属性不同的数字，问最后能否使原数组成为一个不降序列。

### 分析

可以发现，如果存在属性不同的数字，那么原数组就可以交换两个数字。

证明如下：

假设存在属性不同的数字，我们要交换 $x$ 和 $y$。

+ 若 $x$ 和 $y$ 的属性不同，直接交换。

+ 若 $x$ 和 $y$ 的属性相同，则找出属性与 $x$，$y$ 均不同的 $z$，先交换 $x$ 和 $z$，再交换 $y$ 与 $z$，最后交换 $x$ 与 $z$ 也能达到目的。

所以只有同时满足以下两个条件，输出 No。

1. 所有数字的属性均相同。

1. 原数组不是一个不降序列。

其它情况均输出 Yes。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define N 510
int a[N],b[N],t,n;
int main()
{
    read(t);
    F(cas,1,t)
	{
        read(n);
 		F(i,1,n) read(a[i]);
 		F(i,1,n) read(b[i]);
 		bool f1 = 0,f0 = 0;
 		F(i,1,n) f1 |= (b[i]),f0 |= (!b[i]);
        if(f1&&f0) 
        {
        	puts("Yes");
        	goto END;
		}
       	F(i,1,n-1)
       		if(a[i] > a[i+1])
       		{
       			puts("No");
				goto END;	
			}
        puts("Yes");
        END:;
    }
    return 0;
}
```




---

## 作者：do_while_true (赞：2)

手推一下发现 $b$ 中只要 $0$ 和 $1$ 都出现了就可以实现全部位置随便打乱，比如有 $i$ 和 $j$ 想要互换位置，但是他们都是相同种类的数，则我们找另一个不同种类的数 $k$，先让 $i$ 和 $k$ 换，再让 $k$ 和 $j$ 换，再让 $i$ 和 $k$ 换即可达到 $i,j$ 交换位置的效果。

所以如果全部都是 $0$ 或 $1$ 并且序列不是不下降的，则为 `No`，否则为 `Yes`。

[$\mathcal{Code}$](https://codeforces.ml/contest/1365/submission/82813642)

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int T,n,m,s[1010];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		int f=0,l=0,y=0;
		for(int i=1;i<=n;i++) {
			scanf("%d",&s[i]);
			if(s[i]<s[i-1]) f=1;
		}
		for(int i=1;i<=n;i++) {
			scanf("%d",&s[i]);
			if(s[i]==0) l=1;
			else y=1;
		}
		if(l+y==1&&f==1) puts("No");
		else puts("Yes");
	}
	return 0;
}
```

---

## 作者：Blunt_Feeling (赞：2)

## CF1365B Trouble Sort 题解
这是一道有意思的题目。

题目中说，当两个元素的属性不同时，可以交换这两个数。这意味着，只要数列中存在不同属性的数，数列就可以被排成一个不降数列。

可以给出一种交换的方法。这种交换方法类似于冒泡排序，我们平常写的冒泡排序时这样的：
```cpp
for(int i=1;i<n;i++)
	for(int j=i+1;j<=n;j++)
		if(a[i]>a[j])
		{
			int tmp=a[i];
			a[i]=a[j];
			a[j]=tmp;
		}
```
其中，我们可以把属性为 0 的数列看成 a 数组，而想要把属性为 0 的数列按升序排好，就可以随意选择一个属性为 1 的数，把它当作`tmp`来作为中间替换的元素。

比方说有这样一组样例：
```cpp
3
2 1 3
0 0 1
```
先交换 1 和 3，
```cpp
2 3 1
0 1 0
```
再交换 2 和 3，
```cpp
3 2 1
1 0 0
```
最后交换 3 和 1，
```cpp
1 2 3
0 0 1
```
就完成了一组交换，且属性为 1 的 3 又恢复原位，皆大欢喜。按照同样的方法，就能换完所有的数。

那么当数列里只有一种元素时，就只要判断数列本身是不是一个不降序列；若是，输出`Yes`，否则输出`No`。

### Code
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
const int maxn=520;
int T,n,a[maxn],b[maxn];
bool check() //用来判断数列本身是不是一个不降序列
{
	For(i,2,n)
		if(a[i-1]>a[i])
			return false;
	return true;
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		For(i,1,n) cin>>a[i];
		bool f0=false,f1=false;
		For(i,1,n)
			cin>>b[i],b[i]?f1=true:f0=true; //三目运算符，用来记录属性
		if(f0&&f1) puts("Yes");
		else puts(check()?"Yes":"No");
	}
	return 0;
}
```

---

## 作者：Refined_heart (赞：1)

题目大意：将所有数分成两类，只有不同种类的数字可以互换位置，问能不能排成一个不降序列。

观察一下，发现如果种类数有不同的，那么这个序列就可以任意排序。因为每个数都可以和不同的那个数换，通过交换可以达到任意交换两个数字的目的。

那么，如果只有一种，显然不能换，判断一下是不是不降就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,a[1000],b[1000],n;

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);int s=0;int vv[2];vv[0]=vv[1]=0;
		for(int i=1;i<=n;++i)scanf("%d",&a[i]);
		for(int i=1;i<=n;++i)scanf("%d",&b[i]),s+=(!vv[b[i]]),vv[b[i]]=1;
		if(s>1){
			puts("Yes");
			fill(a+1,a+n+1,0);
			fill(b+1,b+n+1,0);
			continue;
		}
		else{
			int fg=0;
			for(int i=2;i<=n;++i){
				if(a[i]<a[i-1]){
					puts("No");
					fg=1;break;
				}
			}
			fill(a+1,a+n+1,0);
			fill(b+1,b+n+1,0);
			if(!fg)puts("Yes");
			continue;
		}
	}
	return 0;
}
```


---

## 作者：精神小伙！ (赞：1)

## 思路

可以发现一个有趣的性质。

只要序列里有任何两个数的属性不同，就一定能得到得到一个不降序列。

否则判断这个序列本身是不是不降序列即可。

## 代码

```cpp
#include<iostream>
using namespace std;
int a[10010],b[10010];
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		bool f1=0,f2=0;
		cin>>n;
		for(int i=1;i<=n;++i)
		    cin>>a[i];
		for(int i=1;i<=n;++i)
		{
			cin>>b[i];
			if(b[i]) f1++;
			else     f2++;
		}
		if(f1&&f2) cout<<"Yes"<<endl;//判断有没有两个数的属性不同
		else 
		{
			bool f=0;
			for(int i=2;i<=n;++i)
			    if(a[i]<a[i-1]) {f=1;break;}
		    if(f) cout<<"No"<<endl;
		    else  cout<<"Yes"<<endl;
		}//判断是否为不降序列
	}
	return 0;
}


```

---

## 作者：czh___ (赞：0)

### 思路
如果原本就是升序，或即存在 $0$ 类型又存在 $1$ 类型的数就一定能过通过一定的转换顺序将其变成非降序的序列。

反之就无法实现。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int  N=2e5+1;
int t,n;
int a[N],b[N];
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        int abc=0,abcd=0,flag=1;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            if(i>1&&a[i]<a[i-1]) 
				flag=0;
        }
        for(int i=1;i<=n;i++){
            cin>>b[i];
            if(b[i]) 
				abcd=1;
            else 
				abc=1;
        }
        if(flag||abc&&abcd) 
			cout<<"Yes\n";
        else 
			cout<<"No\n";
    }
    return 0;
}
```
拜拜！

---

## 作者：Lan_yan (赞：0)

一道考验思维~~但还是很水~~的题。

## 思考

“不降序列”指的是 $a_i$ 永远 $ \ge a_{i-1}$，与 $b$ 数组没有任何关系。

样例直白地告诉了我们规律。

样例有 $5$ 个数据。可以明显看出：

- 数据 $1$ 和数据 $3$ 已经是“不降序列”，而其他不是。

- 数据 $3$ 和数据 $4$ 只有 $1$ 种属性，即 $b_i$ 只全部为 $0$ 或全部为 $1$，而其他不是。

观察发现只有数据 $4$ 是不能通过若干次操作得到“不降序列”的。

#### 大胆猜测：只有当所有数只有同一种属性且不为“不降序列”时才不能通过若干次操作得到“不降序列”。

有没有漏网之鱼（有不是上面类型的数据但却不能得到“不降序列”）？

答案很明显。

当两个数 $a_x,a_y$ 必须交换时，会有两种情形：

情形一：$b_x \ne b_y$。

根据题目所述，$a_x,a_y$ 可直接交换。

情形二：$b_x = b_y$。

假定 $b_z \ne b_x$ 且 $b_z \ne b_y$，则可以通过如下操作交换 $a_x,a_y$：

$a_z,a_x$ 互相交换。

$a_x,a_y$ 互相交换。（这里 $a_x$ 已经是 $a_z$ 了）

$a_y,a_z$ 互相交换。

也能达成目的。所以，没有漏网之鱼。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[505],b[505];
int main()
{
	int i;
	scanf("%d",&t);
	while(t--)
	{
		int x0=1,x1=1,y=1;
		//x0考验有没有b[i]为0,x1考验有没有b[i]为1,y考验a数组是否为“不降序列”
		scanf("%d",&n);
		for(i=0;i<n;i++)scanf("%d",&a[i]);
		for(i=0;i<n;i++)
		{
			scanf("%d",&b[i]);
			if(b[i]==0)x0=0;
			if(b[i]==1)x1=0;
		}
		for(i=1;i<n;i++)if(a[i]<a[i-1])y=0;
		if((x0==1||x1==1)&&y==0)printf("No\n");//套用结论
		else printf("Yes\n");
	}
    return 0;
}
```

完结撒花！

---

## 作者：Xdl_rp (赞：0)

solution：
------------

首先是输入（没什么好说的），因为不论如何，只要 $b$ 数列中有不同的数字或者 $a$ 数组本身就是一个不降序列，就可以直接输出 `YES`，否则输出 `NO`。当 $a_i$ 可以与 $a_j$ 交换，则 $a_i$ 可以去到 $a_j$ 那里，也就是任何一位所在的位置都可以到它排序后的地方（跋山涉水，也就是经过很多地方的转折）。

例如：

```cpp
20 10 100 50
0 0 0 1
```

将 $100$ 和 $50$ 交换，接下来将 $20$ 与 $50$ 交换，$50$ 再依次和 $10$ 和 $20$ 交换，这样就完成了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 5;
int a[N], b[N], n;
bool check() {
	for (int i = 1; i <= n; i++) if (a[i - 1] > a[i]) return false;
	return true;
}
void init() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];	
}
void ans(bool x, bool y) {
	puts((x && y) || check() ? "YES" : "NO");
}
void solve() {
	bool f1 = false, f2 = false;
	for (int i = 1; i <= n; i++) b[i] ? f1 = true : f2 = true;
	ans(f1, f2);
}
signed main() {
	int T;
	cin >> T;
	while (T--) {
		init();
		solve();
	}
	return 0;
}
```


---

## 作者：猜一猜我是谁 (赞：0)

# 思路
可以发现，如果存在两个数的属性不相同，那么最终一定能构成一个不降序列。

所以先判断是否存在两个数的属性不相同，如果是，直接输出 Yes。否则再判断序列本身是不是不降序列，是就输出 Yes，否则输出 No。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[505],b[505];
int main(){
    int t,n,f1,f2;
    cin>>t;
    while(t--){
        f1=0,f2=0;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++){
            cin>>b[i];
            if(b[i]==1) f1=1;
            else f2=1;
        }
        if(f1==1&&f2==1) cout<<"Yes\n";//判断是否存在两个数的属性不相同
        else
        {
            bool f=0;
            for(int i=1;i<n;i++)
                if(a[i]>a[i+1]){
                    f=1;
                    break;
                }
            if(!f) cout<<"Yes\n";//判断序列本身是不是不降序列
            else  cout<<"No\n";
        }
    }
}
```

---

## 作者：Ba_creeper (赞：0)

#### 题意分析

通过模拟样例，发现只要 $b$ 中同时出现 $0$ 和 $1$，就可以实现在 $n$ 次成功交换到位。

所以，我们只对 $b$ 只为 $0$ 或只为 $1$ 时的情况考虑。

很容易发现，此时是不能交换的。那么当且仅当此时的 $a_i$ 满足不下降才符合题目要求。

所以，根据以上性质进行特判，即可通过此题。

#### 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;

ll n, T, m;
ll a[10000], b[10000];
bool ok1, ok0;

void Clear() //初始化，清空
{
    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
    ok1 = 0;
    ok0 = 0;
}

bool check() //判断 b[i] 全是1 或 全是0
{
    if (ok1 == 0 && ok0 == 1)
        return 1;
    if (ok1 == 1 && ok0 == 0)
        return 1;
    return 0;
}

int main()
{
    T = read();
    while (T--)
    {
        Clear();
        n = read();
        for (int i = 1; i <= n; ++i)
            a[i] = read();

        for (int i = 1; i <= n; ++i)
        {
            ll x = read();
            b[i] = x;
            if (x == 0) ok0 = 1; 
            if (x == 1) ok1 = 1;
        }
        
        if (check()) //判断b 全是0 或 全是1 
        {
            bool ook = 0;
            for (int i = 1; i < n; ++i)
            {
                if (a[i] > a[i + 1]) //判断 a序列 是否不下降
                {
                    ook = 1;
                    break;
                }
            }
            if (ook == 1)
                puts("No");
            else
                puts("Yes");
        }
        else
            puts("Yes");
    }
}
```

---

## 作者：PragmaGCC (赞：0)

**当两个元素的属性不同时可以交换**

实际上，只要可以交换，那么就可以变换为一个不下降序列，只需要将这个数到处换就可以了，具体可以参考样例

那么，如果不能交换，也就是所有属性都相同呢？

只需要判断序列本身是不是不下降序列就好了

```
#include <bits/stdc++.h>
using namespace std;
int T, a[510], b[510], n, flagb, flaga;
//flagb表示是否能交换，flaga表示是不是不下降序列
int main()
{
    scanf("%d", &T);
    for (int j = 1; j <= T; j++)
    {
        flagb = 0, flaga = 1; //一定要初始化！
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++)
            scanf("%d", &b[i]);
        for (int i = 2; i <= n; i++) //判断是否可以交换
        {
            if (b[i] != b[i - 1])
            {
                flagb = 1; //属性有不同的，可以交换
                break;
            }
        }
        if (flagb == 1) //属性不同，输出Yes
        {
            printf("Yes\n");
            continue;
        }
        //既然属性都相同，那就判断是否为不下降序列
        for (int i = 2; i <= n; i++)
        {
            if (a[i] < a[i - 1]) //下降了
            {
                flaga = 0;
                break;
            }
        }
        if (flaga) //如果本身是不下降序列，就输出Yes，否则输出No
            printf("Yes\n");
        else
            printf("NO\n");
    }
}
```

---

## 作者：ShineEternal (赞：0)

[更佳的阅读效果。](https://vipblog.github.io/sal5L5T03/)

## description：

- 给定一个长度为 $n$ 的序列 $a_i$ 和每个元素的属性 $b_i$。

- 一次操作定义为一对 $(i,j)$ 满足 $b_i\neq b_j$ 时，交换 $a_i,a_j$。（属性也随之交换）

- 你需要求出这个序列能否由若干次（可以为 $0$）操作后得到一个不降序列。

- **输入有多组数据**。数据组数不超过 $100$。 $1\le n\le 500$，$1\le a_i\le 10^5$，$b_i\in \{0,1\}$。

- translate by @[ShineEternal](https://www.luogu.com.cn/user/45475)。

## solution：

这道题可以观察到一个十分有趣的属性：只要 $0$ 和 $1$ 都存在，那么这个序列一定能由一些操作后得到不降序列。

否则如果序列最开始已经是不降序列了，也是 `Yes`。

其余情况就是 `No` 了。

## code：
```cpp
#include<cstdio>
using namespace std;
int a[505],b[505];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		int flag0=0,flag1=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&b[i]);
			if(b[i]==0)
			{
				flag0=1;
			}
			if(b[i]==1)
			{
				flag1=1;
			}
		}
		if(flag0==1&&flag1==1)
		{
			printf("Yes\n");
			continue;
		}
		flag1=0;
		for(int i=2;i<=n;i++)
		{
			if(a[i-1]>a[i])
			{
				printf("No\n");
				flag1=1;
				break;
			}
		}
		if(flag1==0)
		printf("Yes\n");
	}
}
```

---

## 作者：Fairicle (赞：0)

[更好的阅读体验](https://www.luogu.com.cn/blog/Fairicle/solution-cf1365b)

我们可以发现，只要一个序列既有 1 也有 0，那么必定可以排出单调不递减序列。

简短证明：

假设 $a_1$ 是 0，$a_2$ 是 1，$a_3$ 是 1，那么就可以先交换 $a_1$ 和 $a_2$ 的位置，再交换 $a_1$ 和 $a_3$ 的位置，最后再交换 $a_1$ 和 $a_2$ 的位置，就达到了交换  $a_2$ 和 $a_3$ 的目的。

简而言之，就是，如果一个序列有 1 也有 0，那么任意两个不同的位置的数都能进行交换。

那么对于有 1 和 0 的序列输出 Yes 即可，否则就判断给定的是否是个单调不递减序列。

code：
```cpp
#define ll long long
#define ri register int
int t,n;
#define N 100010
int a[N],b[N];
int main()
{
	t=rd();
	while(t--){
		n=rd();int num=0;
		for(ri i=1;i<=n;++i) a[i]=rd();
		for(ri j=1;j<=n;++j) b[j]=rd(),num+=b[j];int ok=1;
		for(ri i=1;i<=n-1;++i) if(a[i]>a[i+1]){
			ok=0;break;
		}
		if(num==0||num==n){
			if(ok==0)
			puts("NO");
			else puts("YES");
		}
		else puts("YES");
	}
    return 0;
}
```


---


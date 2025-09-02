# Yet Another Tetris Problem

## 题目描述

你有一个数列 $\{a_n\}$，现在有两种操作：

1. 当数列 $\{a_n\}$ 的任意一项大于 $0$ 时，你可以选择**一些** $i(1\le i\le n)$，把每个 $a_i$ 加上 $2$。
2. 当数列 $\{a_n\}$ 的每一项都大于 $0$ 时，把这个数列的每一项都减去 $1$。

问你最后能不能把 $\{a\}$ 数组的元素全部变成 $0$。如果能，输出 `YES`，不然输出 `NO`。

## 说明/提示

$1\le t\le 100$，$1\le n\le 100$，$1\le a_i\le 100$。

## 样例 #1

### 输入

```
4
3
1 1 3
4
1 1 2 1
2
11 11
1
100```

### 输出

```
YES
NO
YES
YES```

# 题解

## 作者：Limit (赞：5)

~~闲得无聊,发个位运算版题解,谔谔~~

# 题目大意

给出一个序列 $a$,每次操作可以在任何一个元素加上 $2$,问最后是否可以使得所有元素相等.

# 分析

可以发现最大值 $-$ 当前位置要是一个偶数,那么再理解一下就是所有元素的奇偶性相同,那么可以维护一个 $and$ 和,以及一个 $or$ 和,最后看二进制最后一位就好了.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
int T,N;
void YES()
{
	printf("YES\n");
}
void NO()
{
	printf("NO\n");
}
void work()
{
	scanf("%d",&N);
	int and_=1,or_=0;//记录and和以及or和,初值为1和0
	int a;
	REP(i,1,N)
	{
		scanf("%d",&a);
		and_&=a&1;//因为用到的知识奇偶性所以可以直接在a上and1
		or_|=a&1;
	}
	if(and_||or_^1)//如果and最后为1(全是奇数),或者or最后为0(全是偶数),则输出YES
	{
		YES();
		return;
	}
	NO();//否则不成立
}
int main()
{
	scanf("%d",&T);
	REP(i,1,T)
	{
		work();
	}
	return 0;
}
```

---

## 作者：幻之陨梦 (赞：4)

$Solution:$

首先我们知道每一个数，在变化的时候都是只能+2，而2是个偶数，所以不会改变原数的奇偶性，所以我们只需要判断是否都是奇偶性相同的数，如果是就输出YES，不是就输出NO

$\textbf{位运算：}$

因为此体会涉及到位运算的知识，所以给大家普及一下。

1. $\&$符号，$x\&y$，会将两个十进制数在二进制下进行与运算，然后返回其十进制下的值。例如$3(11)\&2(10)=2(10)$
2. $|$符号，$x|y$，会将两个十进制数在二进制下进行或运算，然后返回其十进制下的值。例如$3(11)|2(10)=3(11)$
3. ^符号，x^y，会将两个十进制数在二进制下进行异或运算，然后返回其十进制下的值。例如3(11)^2(10)=1(01)
4. $<<$符号，左移操作，$x<<2$，将$x$在二进制下的每一位向左移动两位，最右边用0填充，$x<<2$相当于让$x$乘以4。相应的，$>>$是右移操作，$x>>1$相当于给x/2，去掉$x$二进制下的最有一位。
5. ~取反符号，可以将一个数的每一位都取反。

我们这里把位运算讲了一遍，但是真正用到的其实只有第一个 $\&$ 符号

$code:$
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//标准数据库
inline int read()//快速读入
{
    int x=0;bool f=true;char c=getchar();
    if(c==EOF) return 0;
    while(c<'0' || c>'9'){if(c=='-') f=false;c=getchar();}
    while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return f?x:-x;
}
int T,n,x,a;
bool f;
int main()
{
    T=read();//输入数据组数
    while(T--)
    {
        f=1;//初始化
        n=read();//输入一共有多少数
        x=read();//将第一个数输入进来当做基准数
        for(int i=1;i<n;i++)
        {
            a=read();//输入以后的每个数
            if((a&1)!=(x&1)) f=0;//如果奇偶性不同，就将 f 置0
        }
        puts(f?"YES":"NO");//如果 f 为真就输出 YES 要不然就输出 NO
    }
    return 0;
}
```

---

## 作者：C　C　A (赞：4)

# $CF1324A\ Yet\ Another\ Tetris\ Problem's\ Solution$
						
$\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad By$ [$CCA$](https://www.luogu.com.cn/user/78645)

## $Problem$

$\qquad$给定一些数，问能不能给其中一个加$2$，重复任意次后使得所有数相等。

## $Solution$

$\qquad$我们知道，这些数的大小是无所谓的，因为无论其中一个多大或者多小，都能通过加$2$变得相近。

$\qquad$但是什么时候会无法相等呢？当然是奇偶性不同的时候。

$\qquad$所以我们把所有数跟第一个数比较奇偶性，只要有一个不同，就输出$"NO"$，反之输出$"YES"$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int T , n , a[200];

int main(){
	scanf("%d" , &T); while(T--){
		scanf("%d" , &n);
		for(int i = 1; i <= n; i++) scanf("%d" , &a[i]);
		bool flag = true;
		for(int i = 2; i <= n; i++)
			if((a[i] & 1) != (a[1] & 1)) flag = false;
		flag ? puts("YES") : puts("NO");
	}
	return 0;
}
```

自认为码风还是比较清奇可看的，大家可以对着$Solution$仔细看一下。

最后，[$This\ is\ my\ blog$](https://www.luogu.com.cn/blog/A66-888/) , 有兴趣的可以逛一下，应该能有所收获。

---

## 作者：tuzhewen (赞：2)

说实话，稍加思考题目就简单多了。

我们的目的是把整个数组变成$0$，并不需要求出最少的步数。那么我们只需要看一看所有$a_i$之间的差是不是$2$的倍数就好了。如果是，那么一定可以把所有数变成同一个数字，不然就无解。

$ACcode:$
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[1005];
bool flag;
int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		flag=true;
		for(int i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			if(i>1) {
                if(abs(a[i]-a[i-1])%2!=0) {
                    flag=false;//因为是在输入的时候进行判断的，所以不能break。其实也可以在输入结束后来判断。
                }
			}
		}
        flag==true ? puts("YES") : puts("NO");
    }
	return 0;
}
```

我有一个想法 ~~（但是懒得写）~~，判断所有数字的奇偶性，如果有不同的，那么就不行。

---

## 作者：艹poy (赞：1)

判断每组数据的奇偶性是否相同即可

统计数据中奇数个数和偶数个数

如果奇数个数和偶数个数中有一个为0

说明都是偶数或都是奇数，就输出“YES”

如果两个都不是0，就输出“NO”

代码：

```cpp
#include <iostream>
using namespace std;
int n,x,a,os,js;
int main(){
	cin >> n;//输入数据个数
	for (int i = 1;i <= n; ++i){
		cin >> x;//输入数据
		os = 0;
		js = 0;//初始化
		for (int i = 1;i <= x; ++i){
			cin >> a;
			if (a % 2 == 0) os ++;
			else js ++;//统计奇数个数和偶数个数
		}
		if (!os || !js) cout << "YES" << endl;//如果其中有一个为0
		else cout << "NO" << endl;//如果两个都不是0
	}
	return 0;
}
```

---

## 作者：do_while_true (赞：1)

题目传送门: [CF](http://codeforces.com/problemset/problem/1324/A) [洛谷](https://www.luogu.com.cn/problem/CF1324A)

## 题目翻译

俄罗斯方块游戏，共有$n$列，给出每一列目前的方块个数，可以放置任意个高为2宽为1的方块(不可旋转)，问能不能把所有方块消掉

#### 输入数据

第一行一个整数T，代表有T组数据

对于每一组数据

第一行一个整数$n$ 代表共有$n$列

第二行一个整数序列$a$，$a_i$表示第$i$列共有多少方块

#### 输出数据

T行，对应每组数据的答案

对于每组数据的答案: 如果能把所有方块消掉，则输出"YES",否则输出"NO"

## 题目分析

我们可以把问题转化成这样的形式:

给定一个序列 $a$，每次可以选择一个$a_i$，将$a_i$加上个2，求能不能把这个序列a变成所有元素相等。

因为每次只能加上一个2，所以我们只需要考虑每个序列模2是否相等，如果相等就是 能变成所有元素相等。也就是判断序列中奇偶性是否都相等。

因为模2相等的话，你可以加上任意个2，他们一定能变成相等的(都可以写成$k*2+a_i\%2$)。

## Code:

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,T,x,ji,ou;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		ji=ou=0;
		//ji代表奇数的个数，ou代表偶数的个数 
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			if(x%2==0) ou++;
			if(x%2==1) ji++;
		}
		if(ji&&ou) puts("NO");//如果既有奇数也有偶数，说明奇偶性不同 
		else puts("YES");
	}
	return 0;
}
```


---

## 作者：do_while_false (赞：1)

【题目大意】

对于每个 $a_i$ ，不断地加 $2$，看最终所有的 $a_i$ ，是否能等于 $\max(a_i)$ (即序列 $a$ 中的最大数)。

【大概思路】

找出序列 $a$ 中的最大数，然后暴力枚举其它的数，设序列 $a$ 中的最大数为 $k$ ，只要有一个 $(k-a_i)\mod2=1$ ，答案就为"NO"。

【具体做法】

我们可以直接排序，在把数组翻转一下，此时 $a_1$ 即为最大数，然后暴力判断即可。

【代码】

```cpp
#include<bits/stdc++.h>
#define MAXN 100 + 10
using namespace std;
int t,n,a[MAXN];
bool flag=true;
inline int read() {//快读 
	int r=0;bool flag=true;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=false;ch=getchar();}
	while(ch>='0'&&ch<='9'){r=(r<<3)+(r<<1)+(ch^48);ch=getchar();}
	return flag==true?r:~r+1;
}
int main(void) {
	t=read();
	while(t--) {
		memset(a,0,sizeof(a));
		flag=true;//初始化 
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();//输入 
		stable_sort(a+1,a+n+1);//排序 
		reverse(a+1,a+n+1);//翻转 
		for(int i=2;i<=n;i++)
			if((a[1]-a[i])%2!=0) //判断 
				flag=false;
		if(flag==false) printf("NO\n");//输出 
		else printf("YES\n");
	}
	return 0;
}

```

---

## 作者：寒鸽儿 (赞：0)

目标是达到相同高度, 而增量只能是2, 也就是奇偶性不会改变, 所以必须要相同奇偶性才可达。如果奇偶性相同, 那么2可以视为单位大小, 能拼凑出一切值, 故一定可行。  
```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define rep(i,a,b) for(int i=a;i<=(b);++i)
#define per(i,a,b) for(int i=a;i>=(b);--i)
#define repp(i,a,b) for(int i=a;i<(b);++i)
#define perr(i,a,b) for(int i=a;i>(b);--i)
#define pb push_back
#define itra(T) vector<T>::iterator
#define VI vector<int>
#define VL vector<long long>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3f;

inline ll qp(ll a, ll b, ll p) { ll res = 1%p; for(;b;b>>=1) { if(b&1)res=res*a%p; a=a*a%p; } return res; }
inline ll gcd(ll a, ll b) { while(b) { int t = b; b = a%b; a=t; } return a; }
mt19937 mrand(random_device{}()); int rnd(int x) { return mrand() % x;}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tests;
	cin>>tests;
while(tests--) {
	int n;
	cin >> n;
	bool flg=true;
	int tmp,qaq;
	cin>>tmp;
	while(--n) {
		cin>>qaq;
		if((tmp&1)^(qaq&1)) flg=false;
		tmp=qaq;
	}
	if(flg) cout<<"YES\n";
	else cout<<"NO\n";
}
	return 0;
}
```

---

## 作者：chenxia25 (赞：0)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/CF1324A) & [CodeForces题目页面传送门](https://codeforces.com/contest/1324/problem/A)

>给出$n$个数，第$i$个数为$a_i$。每次操作可以选择一个$i\in[1,n]$并令$a_i=a_i+2$，或令$\forall i\in[1,n],a_i=a_i-1$。问能否经过若干次操作，将$a$数组清零。本题多测。

结论显然，能将$a$数组清零当且仅当所有数奇偶性相同。

证明：若所有数奇偶性相同，显然可以通过若干次第$1$种操作把它们变成两两相等，再通过若干次第$2$种操作把它们都变成$0$；若存在$2$个数$a_i,a_j$奇偶性不相同，则若对$a_i,a_j$做第$1$种操作，那么它们奇偶性不变，若做第$2$种操作，它们奇偶性互换，所以它们奇偶性永远不可能相同，自然也无法都变成$0$。得证。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
void mian(){
	int n;
	cin>>n;
	int x;
	cin>>x;
	x&=1;//a[1]的奇偶性
	n--;
	bool ok=true;
	while(n--){
		int y;
		cin>>y;
		ok&=x==(y&1);//奇偶性要全部相同
	}
	puts(ok?"YES":"NO");
}
int main(){
	int testnum;
	cin>>testnum;
	while(testnum--)mian();
	return 0;
}
```

---

## 作者：LB_tq (赞：0)

# Solution
题意转化为：给定一个序列 $a$ ，可以进行无限次的两种操作：
- 选择任意一个 $i$ ,使 $a_i+2$。
- 若所有 $a_i>0$ ,则将所有 $a_i$ 替换为 $a_i-1$ 。

设 $d=a_i-a_j$ ，可以发现两种操作只会改变 $d$ 的大小，而 $d$ 的奇偶性无法改变。所以如果存在 $d\bmod2=1$ ，则不可能将序列都变成 $0$ 。

所以检查所有的 $d$ 是否都是 $2$ 的倍数即可。

时间复杂度 $O(n^2)$ 。
# Code
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const int maxn=110;
int t,n,a[maxn];
bool f;
int main(){
	cin>>t;
	while(t--){
		f=true;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				if(abs(a[i]-a[j])%2==1){
					f=false;
					break;
				}
		if(f)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
	return 0;
}
```


---

## 作者：Lylighte (赞：0)

要使得所有方块都被消除，这些方块必须能堆叠成同一高度（不多不少），因此它们的奇偶性相同。

因为每次只能向上叠加 $2$ 个方块，所以不改变原来的奇偶性。

求出原来每个高度的奇偶性是否相同即可。

```cpp
#include <iostream>
using namespace std;

int a[110];
int t;

int main(){
	cin >> t;
	for(int T=1;T<=t; T++){
		int width, ftr;
		bool cansolve = true;
		cin >> width;
		for(int i=1; i<=width; i++){
			cin >> a[i];
			a[i] %= 2;				//直接记录它的奇偶性
		}
		ftr = a[1];
		for(int i=2; i<=width; i++){
			if(a[i]!=ftr){
				cansolve = false;
				break;				//判断奇偶性是否相同
			}
		}
		if(cansolve)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;	//输出
	}
	return 0;
}
```

~~朴素的写法。~~

---

## 作者：registerGen (赞：0)

很容易想到，我们只需先方块弄齐，再一举消灭即可。

每次 $a_i$ 只能加 $2$。

所以，只需判断 $a_i$ 的奇偶性是否相等即可。

---

下面放出代码，时间复杂度 $O(n)$。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>

const int N=100;

int a[N+10];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		bool ok=true;
		bool jiou;
		for(int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			if(i==1)jiou=x%2;
			else if(x%2!=jiou)ok=false;
		}
		if(ok)puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---


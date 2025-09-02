# [ABC351C] Merge the balls

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc351/tasks/abc351_c

空の列と、$ N $ 個のボールがあります。$ i $ 個目 $ (1\leq\ i\leq\ N) $ のボールの大きさは $ 2^{A_i} $ です。

これから $ N $ 回の操作を行います。  
 $ i $ 回目の操作では、$ i $ 個目のボールを列の一番右に付け加えた後、次の手順を繰り返します。

1. 列にあるボールが $ 1 $ つ以下ならば操作を終了する。
2. 列にあるボールのうち右から $ 1 $ 番目のものと $ 2 $ 番目のものの大きさが **異なる** ならば操作を終了する。
3. 列にあるボールのうち右から $ 1 $ 番目のものと $ 2 $ 番目のものの大きさが **等しい** ならば、$ 2 $ つのボールを取り除き、「取り除かれた $ 2 $ つのボールの大きさの和」の大きさのボール $ 1 $ つを列の一番右に付け加える。その後、1. に戻り、手順を繰り返す。
 
$ N $ 回の操作の後で、列にあるボールの数を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 0\leq\ A_i\leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

操作は次のように行われます。 - $ 1 $ 回目の操作の後、列にあるボールは $ 1 $ つで、大きさは $ 2^2 $ です。 - $ 2 $ 回目の操作の後、列にあるボールは $ 2 $ つで、大きさは順に $ 2^2 $, $ 2^1 $ です。 - $ 3 $ 回目の操作の後、列にあるボールは $ 1 $ つで、大きさは $ 2^3 $ です。これは次のようにして得ることができます。 - $ 3 $ 回目の操作において $ 3 $ 個目のボールを付け加えたとき、列にあるボールの大きさは順に $ 2^2,2^1,2^1 $ となります。 - 右から $ 1 $ 番目のボールと $ 2 $ 番目のボールの大きさが等しいため、これらのボールが取り除かれ、大きさが $ 2^1+2^1=2^2 $ のボールが追加されます。このとき、列にあるボールの大きさは $ 2^2 $, $ 2^2 $ となります。 - さらに、再び右から $ 1 $ 番目のボールと $ 2 $ 番目のボールの大きさが等しいため、これらのボールが取り除かれ、大きさが $ 2^2+2^2=2^3 $ のボールが追加され、列にあるボールの大きさは $ 2^3 $ となります。 - $ 4 $ 回目の操作の後、列にあるボールは $ 1 $ つで、大きさは $ 2^4 $ です。 - $ 5 $ 回目の操作の後、列にあるボールは $ 2 $ つで、大きさは順に $ 2^4 $, $ 2^5 $ です。 - $ 6 $ 回目の操作の後、列にあるボールは $ 3 $ つで、大きさは順に $ 2^4 $, $ 2^5 $, $ 2^3 $ です。 - $ 7 $ 回目の操作の後、列にあるボールは $ 3 $ つで、大きさは順に $ 2^4 $, $ 2^5 $, $ 2^4 $ です。 よって、最後に列にあるボールの数である $ 3 $ を出力します。

### Sample Explanation 2

操作は次のように行われます。 - $ 1 $ 回目の操作の後、列にあるボールは $ 1 $ つで、大きさは $ 2^0 $ です。 - $ 2 $ 回目の操作の後、列にあるボールは $ 1 $ つで、大きさは $ 2^1 $ です。 - $ 3 $ 回目の操作の後、列にあるボールは $ 2 $ つで、大きさは順に $ 2^1 $, $ 2^0 $ です。 - $ 4 $ 回目の操作の後、列にあるボールは $ 3 $ つで、大きさは順に $ 2^1 $, $ 2^0 $, $ 2^1 $ です。 - $ 5 $ 回目の操作の後、列にあるボールは $ 4 $ つで、大きさは順に $ 2^1 $, $ 2^0 $, $ 2^1 $, $ 2^2 $ です。 よって、最後に列にあるボールの数である $ 4 $ を出力します。

## 样例 #1

### 输入

```
7
2 1 1 3 5 3 3```

### 输出

```
3```

## 样例 #2

### 输入

```
5
0 0 0 1 2```

### 输出

```
4```

# 题解

## 作者：__xsy2013__ (赞：3)

这题建议评红。直接模拟即可。需要开 `long long`，然后我用了 `vector` 容器进行模拟，进入是 `push_back()`，出就是 `pop_back()`，还可以判断队头以来模拟，话不多说，上代码！

```cpp
# include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 2e5 + 5;
int n; ll a[MAXN];
vector <ll> b;
int main() {
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	for(int i = 1; i <= n; ++i) {
		b.push_back(a[i]);
		while(b.size() > 1 && b[b.size() - 1] == b[b.size() - 2]) {
			b.pop_back();
			++b[b.size() - 1];
		}
	} cout << b.size();
	return 0;
}
```

完结撒花！

---

## 作者：liaoxingrui (赞：3)

## Content

给你一个正整数 $N$ 和一个长度为 $N$ 的数组，你将进行 $N$ 次运算。  

在第 $i$ 操作中，你要把第 $i$ 个值（$2^{a_i}$）添加到序列的右端，然后重复下面的步骤：

1. 如果序列中只有一个或更少的球，则结束操作。

1. 如果序列中最右边的球和第二个最右边的球大小不同，则结束操作。

1. 如果序列中最右边的球和最右边的第二个球的大小相同，则移除这两个球，并在序列的右端添加一个新球，其大小等于移除的两个球的大小之和（$2^{a_i} + 2^{a_{i - 1}}$）。然后回到步骤 $1$，重复上述过程。

计算 $N$ 操作后序列中剩余的值的个数。

## Solution

因为 $a_i = a_{i - 1}$，所以 $2^{a_i} + 2^{a_{i - 1}}$ 可以转化为 $2^{a_i} + 2^{a_i}$，可直接化简为 $2^{a_i + 1}$。

题目就相当于判断相邻的数是否相同，如果是，则将它们合并为其中的一个数加上 $1$，同时减去 $i$ 和 $n$ 的值，最后输出 $n$ 的值即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[200001];
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
	return x;
}
int main(){
	n=read();
	a[1]=read(); 
	for(int i=2;i<=n;i++){
		a[i]=read();
		while(a[i-1]==a[i]){
			a[i-1]++;
			n--;
			i--;
		}
	}
	cout<<n;
	return 0;
}
```

---

## 作者：HasNoName (赞：2)

### 思路

应为 $2^{A_i}$ 非长大，而两个相同 $2$ 的整数次方向加起来也是 $2$ 的整数次方。所以，可以将 $2^{A_i}$ 变为 $A_i$。因为题目只求个数，所以这样是对的。

只需要用一个栈模拟就行了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int c[N],top;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,x;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        while(c[top]==x&&top)//入栈
        {
            top--;
            x++;
        }
        c[++top]=x;
    }
    cout<<top<<'\n';//栈的长度即为个数
    return 0;
}

```

---

## 作者：lucasincyber (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc351_c)
## 思路
应该不难想到，用一个栈维护这个序列。因为 $a_i ≤ 10^9$，所以栈里只能维护 $a_i$（也就是 $2$ 的指数），而不能维护 $2^{a_i}$。按照题意模拟即可。

时间复杂度 $O(n)$，可以通过本题。

注意：$2\times2^x = 2^{x+1}$，而维护的是 $2$ 的指数，所以合并两个相同的数后维护的就是 $x+1$。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

int n;
int a[N];
stack<int> stk; // 用栈维护

int main()
{
 	scanf("%d", &n);
 	for (int i = 1; i <= n; i++)
 		scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
    {
    	stk.push(a[i]);
    	while (stk.size() > 1)
    	{
    		int a1 = stk.top();
    		stk.pop();
    		int a2 = stk.top();
    		stk.pop();
    		if (a1 == a2) stk.push(a1 + 1); // 如果满足 a1 == a2，就将 a1 + 1 推入栈顶
    		else // 否则将 a1，a2 按原本顺序推回栈顶
    		{
    			stk.push(a2);
    			stk.push(a1);
    			break;
			}
    	}
	}
	printf("%d\n", stk.size()); // 最后栈的元素个数为答案
	return 0;
}
```

---

## 作者：qhr2023 (赞：1)

## 题意

给定 $N$ 个数和一个初始为空的序列，执行 $N$ 次操作，在第 $i$ 次操作中第 $i$ 个数被添加到该列的最右边，如果序列最右边的两个数相等，则删除他们，然后在最右边加上一个大小为两数之和的数，直到最右边两数不等或序列长度小于 $1$，操作结束。

求 $N$ 次操作后序列长度。

## 思路

直接模拟。用 $a$ 存储这 $N$ 个数的指数，用 $q$ 表示序列，用 $q_0$ 表示序列长度，按上述题意模拟即可。

**注意**：这里序列中的数非常大，我们可以存储他的指数。 

事实上，只有两数相等才进行加法操作，比如用 $2^x$ 表示序列最右端的两个数，那么再删除两数后，加入的元素为 $2^x+2^x$，即 $2^{x+1}$。  

这样，我们就用自增替换了加法。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, q[200005], a[200005];
int main(){
	cin >> n;
	for(int i=1; i<=n; i++)
		cin >> a[i];
	for(int i=1; i<=n; i++){
		q[++q[0]]=a[i];
		while(q[q[0]]==q[q[0]-1]&&q[0]>1)
			q[--q[0]]++; // 相当于先删除两数，再加入两数之和
	}
	cout << q[0];
	return 0;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：1)

很显然，直接用栈解决。

每次首先把当前的数入对，然后重复把栈的最上面的两个取出，如果一样，设当前两个数的值为 $x$ 则放入 $x + 1$ 这个数并继续判断，如果不一样直接退出。

语法题。

代码如下。

```cpp
#include <iostream>
#include <stack>
using namespace std;

int n, a[200005];

stack <int> st;

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		st.push(a[i]);
		while(st.size() > 1) {
			int x = st.top();
			st.pop();
			if(st.top() == x) {
				st.pop();
				st.push(x + 1);
			} else {
				st.push(x);
				break;
			}
		}
	}
	cout << st.size();
}
```

---

## 作者：Elysian_Realme (赞：0)

# AT_abc351_c

## 解题思路

思路很显然，暴力即可，用栈模拟即可。

我们可以考虑从 $1$ 到 $N$ 挨着放进去，只要当前栈顶和将要放进去的一样就弹出来并让将要插入的加一。

代码很短，主函数不到 $10$ 行。

code：

```cpp
// Problem: C - Merge the balls
// Contest: AtCoder - AtCoder Beginner Contest 351
// URL: https://atcoder.jp/contests/abc351/tasks/abc351_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// By：lmq
// AC Time：2024-04-27 20:07:46

#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n;
stack<int> stk;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int t;cin>>t;
		while(!stk.empty()&&stk.top()==t)
			stk.pop(),t++;
		stk.push(t);
	}
	cout<<stk.size();
	return 0;
}

```

---

## 作者：xd244 (赞：0)

小小用栈实现的模拟题目。

直接按照题目模拟：每次判断最右边的两个数 $a$ 和 $b$ 是否相等，相等就变成 $a+1$，最后输出个数。

代码：
```cpp
#include<iostream>
using namespace std;
#define int long long
signed main(){
    int n;cin>>n;
    int a[200010]={},top=0;
    for(int c=1;c<=n;c++){
        int x;cin>>x;
        a[++top]=x;
        if(top<=1)continue;
        while(1){
            if(a[top-1]==a[top])a[top]=0,top--,a[top]++;
            else break;
        }
    }cout<<top;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
注意到每个球的大小是 $2^{A_i}$，$0 \leq A_i \leq 10^9$，那么肯定不能直接计算了，所以我们放进序列的只是指数。$2^0+2^0=2^1$，$2^1+2^1=2^2$，$2^n+2^n=2^{n+1}$。如果两个球的大小相等，我们放进序列是其中一个球的大小 $+1$。

接下来是按照题目意思进行模拟，这里就不再赘述了。
### 代码
```cpp
#include<iostream>
#include<vector>
#define N 200005
int a[N];
signed main(){
	std::vector<int>seq;
	std::ios::sync_with_stdio(0);
	int n;std::cin>>n;
	for(int i=1;i<=n;i++)std::cin>>a[i];
	for(int i=1;i<=n;i++){
		seq.push_back(a[i]);
		while(seq.size()>=2&&seq[seq.size()-1]==seq[seq.size()-2]){
			int v=seq[seq.size()-1];
			seq.pop_back(),seq.pop_back();
			seq.push_back(v+1);
		}
	}
	std::cout<<seq.size();
}
```

---

## 作者：unordered_yao (赞：0)

## 思路

1. 第 $i$ 个球的大小是 $2^{A_i}$，而且 $A_i$ 非常大，如果直接算的话，肯定是不可取的。我们可以从中得到一个性质，当 $p$ 为整数时，有 $2^p+2^p=2^{p+1}$，通过这个式子，我们只需要计算指数就可以了。

2. 还有一点，该题只是看序列的后两项。所以，我们可以用栈来储存这个序列。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+10;
template <typename T>
inline void read(T &x){
    x = 0;char ch = getchar();bool f = 0;
    while(ch < '0' || ch > '9'){if(ch == '-')f = 1;ch = getchar();}
    while(ch >= '0' && ch <= '9')x = (x<<1) + (x<<3) + (ch^48),ch=getchar();
    if(f)x = -x;                                       
}
template <typename T,typename ...Args>
inline void read(T &tmp,Args &...tmps){read(tmp);read(tmps...);}
template<typename type>
inline void write(type x,short mode=0){
    x<0?x=-x,putchar('-'):0;static short Stack[50],top(0);
    do Stack[++top]=x%10,x/=10; while(x);
    while(top) putchar(Stack[top--]|48);
    if(mode == 2) return;
    mode?putchar('\n'):putchar(' ');
}
ll a[N];
stack<ll> ans;
int main(){
    int n;
    read(n);
    int s = 0;
    for(int i=0;i<n;i++)read(a[i]);
    for(int i=0;i<n;i++){
        ans.push(a[i]);
        while(ans.size()>=2){
            ll x = ans.top();ans.pop();
            ll y = ans.top();ans.pop();
            //cout << i << ' ' << x << ' ' << y << '\n';
            if(x == y) ans.push(x+1);
            else {
                ans.push(y),ans.push(x) ;
                break;
            }
        }
    }
    cout << ans.size();
    return 0;
}
```

---

## 作者：Tulip_ (赞：0)

### 题意

你有一个空序列和 $N$ 个球。球 $i$ 的大小是 $2^{A_i}$。

你将进行 $N$ 次运算。
在 $i$ 操作中，你将 $i$ 球添加到序列的右端，然后重复下面的步骤：

1. 如果序列中只有一个或更少的球，则结束操作。
2. 如果序列中最右边的球和第二个最右边的球大小**不同**，结束操作。
3. 如果序列中最右边的球和最右边的第二个球的大小**相同**，则移除这两个球，并在序列的右端添加一个新球，其大小等于移除的两个球的大小之和。然后回到步骤 $1$，重复上述过程。

计算 $N$ 操作后序列中剩余的球数。

### 思路

用一个数组 `q[Max]` 模拟运行步骤，在边模拟时，边计算剩余的球数。

纯模拟，不会超时。

### 注意

模拟时，一定不能漏判剩余的球数是否大于等于 $2$，如果满足就模拟步骤 $2$，否则结束操作。

- $1 \leq N \leq 2 \times 10^5$
- $0 \leq A_i \leq 10^9$
- 所有输入值均为整数。

每一个步骤都不能漏。

### 代码

模拟运行，如下。

```cpp
for(int i=1;i<=n;i++){
		q[++t]=a[i];
		while(t>=2/*判断剩余的球数*/&&q[t]==q[t-1]) q[t-1]=q[t]+1,t--;//步骤3
	}
```

完整代码，如下。

```cpp
#include <bits/stdc++.h>//万能头
#define int long long
using namespace std;
const int Max = 2e5 + 5;
int n,t;
int a[Max],q[Max];
signed main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];//输入
	for(int i=1;i<=n;i++){//模拟
		q[++t]=a[i];
		while(t>=2&&q[t]==q[t-1]) q[t-1]=q[t]+1,t--;
	}
	cout<<t;//输出答案，剩余的球数
	return 0;//好习惯
}

```

---

## 作者：Spark_King (赞：0)

# ABC_351_C 题解
## 题意分析
题目给我们一个长度为 $N$ 的数组，让我们进行 $N$ 次操作。对于第 $i$ 次操作，我们向**预先设置的栈**中放入数列的第 $i$ 个数，然后**反复**执行下列操作：

1. 如果栈内**只有一个数**，则结束操作。
2. 如果栈顶两个数**不相等**，则结束操作。
3. 如果栈顶两个数**相等**，则弹出这两个数，并将这两个数的和放入栈中。

在 $N$ 次操作后，题目要求输出栈内**还剩多少个数**（即栈的大小）。

注意，这里我们数列中的数代表的是**指数**，即对于数列中的一个数 $A_i$，该数所代表的数字**大小为 $2^{A_i}$**，因此在进行求和操作时，应该是在栈中放入 $A_i+1$。

这里由于要同时**访问栈顶两个数**，所以利用**数组模拟栈**会更方便一些。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n;
ll num[200010];
ll stk[200010],top;//用数组模拟栈
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(ll i=1;i<=n;i++)
	{
		cin>>num[i];
	}
	for(ll i=1;i<=n;i++)
	{
		top++;
		stk[top]=num[i];
		while(top>1)//按照题目要求进行操作
		{
			if(stk[top]!=stk[top-1]) break;
			stk[top-1]++;//注意求和操作
			top--;
		}
	}
	cout<<top;//输出栈顶指针，即栈的大小
	return 0;
}
```

---

## 作者：ganyu1 (赞：0)

# ABC_351_C 题解
## 题目翻译
有一组长度为 $n$ 的数据与一个空栈，对于第 $i$ 次操作：
1. 将 $A_i$ 推入栈中，注意推入的数据为 $2^{A_i}$。
2. 若栈中数据数量小于等于 $1$ 个，则结束本次操作。
3. 若栈中的最后一个数与倒数第二个数相等，则推出这两个数，并推入一个大小为这两个数的和的数，可以理解为合并这两个数。
4. 若栈中的最后一个数与倒数第二个数不等，则结束本次操作。
5. 重复进行第 $2$ 至第 $4$ 步，直至操作结束。
## 分析
一道简单的纯模拟题，为了方便对栈的最后一个数与倒数第二个数的比较与修改操作，选择用数组模拟栈，其他按照题意打即可。
## AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n; 
int a[200001];
int s[200001],o;//模拟栈，o为栈顶
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		s[++o]=a[i];
		if(o<=1) continue;//若数量小于等于1则结束操作
		while(s[o]==s[o-1]){
			if(o<=1) break;
			s[o-1]++;
        		//由于存储元素为2多少次方，则两相等数据相加结果为2的x+1次方
			o--;
		}
	}
	cout<<o;//输出最后数量
	return 0;
}
```

---

## 作者：seika27 (赞：0)

### 题意
给定一个长度为 $n$ 的序列 $a_i$，以及一个空序列 $b$。

其中第 $i$ 个数的大小为 $2^{a_i}$。

要求把 $a$ 中的数，依次从左往右加入到空序列。

我们在加入时要遵守下面的规则。

如果 $b$ 最后两个数字的大小相同，就会把这两个数字踢出，并在后面加入这两个数字的和，一直重复这个过程，直到 $b$ 中只有一个数或最后两个数字不同。

最后输出 $b$ 的长度。

### 思路

我们知道 $2^x + 2^x=2^1\times2^x=2^{x+1}$。

所以我们可以不用算出第 $i$ 个数的准确值。

面对依次需要的合并操作，我们只需要记录一下最后一个数的值为 $k$，然后把最后两个数删除，再加入 $k+1$ 即可。

那么对于这里的序列 $b$，我们可以使用很多种数据结构。

这里我就是用了双端队列来进行尾部的删减。

### code
```cpp
#include <bits/stdc++.h>
#define int long long 
#define cin std::cin
#define cout std::cout 
std::deque<int>q;
int n;
const int N=2e5+5;
int a[N];
signed main()
{
	std::ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	cin>>a[1];
	q.push_back(a[1]);
	for(int i=2;i<=n;++i)cin>>a[i];
	for(register int i=2;i<=n;++i)
	{
		q.push_back(a[i]);
		while(1)
		{
			int l=q.size();
			if(l<=1)break;
			if(q[l-2]!=q[l-1])break;
			int x=q[l-2];
			q.pop_back();		//删除后两数
			q.pop_back();
			q.push_back(x+1);	//增添合并数
		}
	}
	cout<<q.size();
	return 0;
}
```

---

## 作者：Houkiseino_Kokoro (赞：0)

### $\texttt{C. Merge the balls}$
#### [原题链接](https://atcoder.jp/contests/abc351/tasks/abc351_c)
#### 题意简述
给定一个初始为空的序列与一个 $N$ 项数列 $a$。数列的第 $i$ 项为 $2^{a_i}$。

依次对数列的每一项执行下列操作：

1. 将该数添至序列末尾。
2. 若序列末尾的两个数相等，将这两个数合并为一个数，其值等于这两个数的和。
3. 重复第2步操作，直至序列末尾的两个数不等或序列中的数不足两个。

求序列里最终有几个数。
#### 解法
很基础的栈。

序列的更新只在末尾进行，很容易想到这是一个栈。依次遍历数列中的每个数进行入栈操作，对第 $i$ 个数的入栈操作，判断该数是否与栈顶相等，若相等，弹出栈顶，并将其加到待入栈的数上。由于 $2^{a_i} + 2^{a_i} = 2^{a_i+1}$，我们只需要维护 $a_i$，合并操作即为 $a_i \gets a_i + 1$。重复上述操作直至待入栈的数与栈顶不相等或栈已空时，将该数入栈。
#### 代码
```cpp
int main()
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n + 1);
    for (size_t i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
    }
    std::stack<int> s;
    for (size_t i = 1; i <= n; i++)
    {
        int tmp = arr[i];
        while (!s.empty() && tmp == s.top())
        {
            s.pop();
            tmp++;
        }
        s.push(tmp);
    }
    std::cout << s.size();
    return 0;
}

```

---

## 作者：_ayaka_ (赞：0)

## 题意
给出一个数 $n$ 以及 $n$ 个数 $a_i$，每个数的值为 $2^{a_i}$。将每个数放入序列的末尾，并进行以下操作：
- 若序列中的数小于 $2$ 个，则不进行任何操作。
- 若放入的数与它前一个数的值不同，则不进行任何操作。
- 若放入的数与它前一个数的值相同，则将这个数与前一个数合并，合并出的数为两个数之和，并再次重复此操作。

最后输出序列中所剩的数的数量。
### 题意转换

两个相同的数合并会变为两数之和，那么也就是说会变为其中一数的两倍。而我们数的值也是以 $2$ 的幂次进行存储的，并且答案跟数的值没有任何关系，所以我们可以将题意转换为：

给出一个数 $n$ 以及 $n$ 个数的值 $a_i$。将每个数放入序列的末尾，并进行以下操作：
- 若序列中的数小于 $2$ 个，则不进行任何操作。
- 若放入的数与它前一个数的值不同，则不进行任何操作。
- 若放入的数与它前一个数的值相同，则将这个数与前一个数合并，合并出的数为原数的值 $+1$，并再次重复此操作。

最后输出序列中所剩的数的数量。

## 思路

每次读取一个数，并模拟放入的过程，然后最后输出即可。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[2000005],cnt;
signed main() {
	ios::sync_with_stdio(0);
	cout.tie(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
      cnt++;
		cin>>a[cnt];
		while(cnt>1&&a[cnt]==a[cnt-1]) {
			cnt--;
			a[cnt]++;
		}
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：zzhbpyy (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/AT_abc351_c)

看似 $2^{A_i}$ 大的惊人，实则就是一个幌子，由于只须判断球的大小是否相等，可以直接把球的大小视作 $A_i$。最后根据题意模拟即可。

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005],tot,q[2000005];//tot是序列中的元素个数，q中记录所有球的大小是2的几次方
signed main(){
	ios::sync_with_stdio(0);cin.tie(nullptr);cout.tie(nullptr);
	int n,cnt=1;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int cnt=1;cnt<=n;cnt++){
		q[++tot]=a[cnt];
		while(tot>=2)//如果序列中有超过2个元素判断是否可以合并
            if(q[tot]==q[tot-1])
                q[--tot]++;
			else break;
	}
	cout<<tot;
	return 0;
}
```

---

## 作者：xixisuper (赞：0)

# AT_abc351_c [ABC351C] Merge the balls 题解

建议添加标签：栈，模拟。

建议难度：入门 or 普及-。

## 思路

题目描述的已经十分清楚了，直接对其进行模拟即可。

详细地，开一个栈存放指数，当栈中元素大于两个时，比较栈顶与次顶的两个数。如果相等，则把这两个数弹栈，把**该数 $+1$ 压入栈**中，然后重复上述操作直至**栈顶两元素不相等**或**栈中元素少于两个**。

至于为什么要把原数加一压进去？我们需要一点初中知识。

$$2^a+2^a=2 \times 2^a=2^{a+1}$$

由于栈中存的是指数，所以把原数加一压入栈中。

## 代码

蒟蒻代码，不喜勿喷。

```cpp
#include <iostream>
#define ll long long
using namespace std;
const int N = 1e6+10;
ll n;
ll stk[N],nums[N],top;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
	cin>>n;
	for(ll i=1;i<=n;i++) cin>>nums[i];
	for(ll i=1;i<=n;i++){
		if(!top) stk[++top]=nums[i];
		else{
			stk[++top]=nums[i];
			while(top>1){
				if(stk[top]!=stk[top-1]) break;
				stk[top-1]++;
				top--;
			}
		}
	}
	cout<<top;
	return 0;
}
```

---

## 作者：Igallta (赞：0)

这道题我们发现 $a_i \leqslant 10^9$，如果直接记录 $2^{10^9}$ 明显非常荒谬，把最后两位加起来其实就是次幂加一。

举个例子：

$2^1$，$ 2^2$，$2^2 $ 合并后变成 $2^1$，$(2^2\times2)$、$2^1$ 也就是 $2^{(2+1)}$。

所以合并操作其实就是把最后两位去掉之后补一个多一次方的数进去。

由此，我们就想到只需要记录几次幂就行了。

这里因为是在尾部添加，所以我选用了 `vector`。

- 下文把该数列称作 $a$，把尾部称作 $a_n$。

大体思路是这样的：

1. 循环 $1$ 到 $n$，输入球的数。
2. 把这个球添加到 $a$。
3. **重复执行**，如果 $a$ 大小大于等于 $2$，当前 $a_n = a_{n-1}$，那么就删掉这两个，添加一个 $a_n+1$ 的数到尾部。
4. 循环结束后输出当前数组大小即可。

千万要注意第三个操作是 `while`，而不是 `if`，要一直判断大小是否大于等于 $2$，以及 $a_n = a_{n-1}$，否则你会喜提 $0$ 分。

思路讲完了，代码：

```cpp
/****************************************
作者:Iam_God
版权:luogu@813622
日期:4/28
*****************************************/
#include<bits/stdc++.h>
#define LL k<<1
#define RR k<<1|1
#define int long long

using namespace std;
vector<int>a;
int n;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		int t;
		cin>>t;
		a.push_back(t);//把新元素添加到尾部
//		cout<<a[i-1]<<' '<<a[i-2]<<'\n';
		while(a.size() >= 2 && a[a.size()-1] == a[a.size()-2]){//一直判断
			int k=a[a.size()-1]+1;//等会要 push 的值
			a.pop_back();//把末尾两个弹出
			a.pop_back();
			a.push_back(k);
		}
	}
	cout<<a.size();//输出大小即可
	return 0;
}
```

---

## 作者：codingwen (赞：0)

考虑无脑模拟，使用栈存储球。   
当新进的球与栈顶相同时（此时的栈大小应大于 $2$），将栈顶弹出，将合并后的球入栈。否则直接将球推入栈中。   
最后输出栈的大小即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
stack<int> stk;
int a[200010];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		stk.push(a[i]);
		while(true){
			if(stk.size()<2)break;
			stk.pop();
			int t=stk.top();
			if(t==a[i]){
				stk.pop();
				stk.push(t+1);
				a[i]++;
			}else{
				stk.push(a[i]);
				break;
			}
		}
	}
	cout<<stk.size()<<endl;
}
```

---

## 作者：39xiemy (赞：0)

## 题目大意

给出一串数 $A$ 和一个空序列，但这串数的实际上的值为 $2^{A_i}$。将这些数按照从左到右的顺序依次添加到序列的最右端，当序列里的数多于 $1$ 个时，如果最右边的数 $c$ 和次右边的数 $d$ 相等，就进行一次合并操作，内容如下：移除 $c$ 和 $d$，并在序列的最右端添加一个新数，这个数的值为 $c + d$。

求最终序列里剩余的数的个数。

## 分析

由于是从左到右依次添加数，并且可能的修改都只在最右边和次右边的两个数中发生，所以可以联系到用栈来维护。虽然题目中不是直接将 $A_i$ 添加进序列，但题目不要求输出数列中的数，所以可以直接用栈来维护 $A_i$，但合并操作就需要改变。

而对于合并操作，我们~~都~~知道 $2^n + 2^n = 2^{n+1}$，所以如果要直接合并 $A_i$ 和 $A_j$，那么合并操作就等价于：移除 $A_i$ 和 $A_j$，并在序列的最右端添加一个新数，这个数的值为 $A_i + 1$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b[200002],tail=1,c[200001];
int main()
{
	scanf("%d%d",&a,&b[1]);
	c[tail]=b[1];             //提前先往栈里存一个元素 
	for(int i=2;i<=a;i++)
	{
		scanf("%d",&b[i]);
		c[++tail]=b[i];
		while(c[tail]==c[tail-1])  //不断循环检查是否要合并 
		{
			c[--tail]++;//弹出一个栈顶元素，并将当前的栈顶元素加1，就能完成合并 
		}
	}
	printf("%d",tail);    //tail就是这个栈中的元素个数，即答案 
	return 0;
}
```

---


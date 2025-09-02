# 「FAOI-R5」becoder

## 题目背景

**警告：请不要试图使用 AI，使用者按作弊处理。**

## 题目描述

$\text {becoder}$ 拥有所有中文 OJ 中最快的评测机，现在评测机需要处理 $n$ 次题目的评测。已知第 $i$ 次题目的评测在某中文 OJ 上跑了 $T_i$ 秒，空间耗费 $M_i$。

$\text {becoder}$ 的评测机实在是太快了，你可以把 $\text {becoder}$ 跑第 $i$ 个评测的时间视为 $\left \lfloor \frac{T_i}{2} \right \rfloor $。

告诉你 $\text {becoder}$ 上 $n$ 次题目评测的时间限制 $t_i$ 和空间限制 $m_i$。以及，在测评 $[L,R]$ 内的题目时，$\text {becoder}$ 的评测机会打瞌睡。

$\text {becoder}$ 的评测机按如下规则评判提交：
- 如果 $\text {becoder}$ 的评测机在打瞌睡，评测结果会返回 ```System Error```；
- 如果 $\text {becoder}$ 的评测机没有打瞌睡，且你的代码空间超限，即 $M_i > m_i$，评测结果会返回 ```Memory Limit Exceeded```；
- 如果 $\text {becoder}$ 的评测机没有打瞌睡，且你的代码空间不超限，时间超限，即 $M_i \le m_i,\left \lfloor \frac{T_i}{2} \right \rfloor > t_i$，评测结果会返回 ```Time Limit Exceeded```。
- 否则，$\text {becoder}$ 评测机会返回 ```Accepted```。

请你输出所有 $\text {becoder}$ 对于每个测评会返回的结果。你不考虑除上述四种返回结果以外的情况。

## 说明/提示

**本题开启捆绑测试**。

+ Subtask 1（30 pts）：$1 \le n,m \le 10^3$。
+ Subtask 2（30 pts）：$1 \le T_i,M_i,t_i,m_i \le 10^3$。
+ Subtask 3（40 pts）：无附加限制。

对于 $\text{100}\%$ 的数据，$1 \le L \le R \le n \le 10^5,1\le T_i,M_i,t_i,m_i \le 10^9$。

## 样例 #1

### 输入

```
5 3 3
10 2
12 4
3 6
8 7
9 3
5 2
5 7
1 7
4 6
10 5```

### 输出

```
Accepted
Time Limit Exceeded
System Error
Memory Limit Exceeded
Accepted```

# 题解

## 作者：2011hym (赞：6)

~~一道十足的大水题~~

个人认为算法是**循环**和**分支**

根据题意进行模拟，循环每次询问进行判断

就完事儿了

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int T[100010],M[100010],t[100010],m[100010];
int main(){
    int n,L,R;
    cin>>n>>L>>R;
    for(int i=1;i<=n;i++){
        cin>>T[i]>>M[i];
    }
    for(int i=1;i<=n;i++){
        cin>>t[i]>>m[i];
    }
    for(int i=1;i<=n;i++){
        if(i>=L&&i<=R){
            cout<<"System Error\n";
            continue;
        }
        if(M[i]>m[i]){
            cout<<"Memory Limit Exceeded\n";
            continue;
        }
        int tim=T[i]/2;
        if(tim>t[i]){
            cout<<"Time Limit Exceeded\n";
            continue;
        }
        cout<<"Accepted\n";
    }
    return 0;
}
```

（对了，记得根据顺序去判断）

---

## 作者：__CJY__ (赞：5)

红题，太水了。
## 思路
用两个数组 $T,M$ 存读入的限制，再按照题意模拟即可。

题目已经把步骤讲得很清晰了，没什么好讲的。

>* 如果 $\text{becoder}$ 的评测机在打瞌睡，评测结果会返回 `System Error`；
>* 如果 $\text{becoder}$ 的评测机没有打瞌睡，且你的代码空间超限，即 $M_i>m_i$，评测结果会返回 `Memory Limit Exceeded`；
>* 如果 $\text{becoder}$ 的评测机没有打瞌睡，且你的代码空间不超限，时间超限，即 $M_i \le m_i,\lfloor \frac{T_i}{2} \rfloor>t_i$，评测结果会返回 `Time Limit Exceeded`。
>* 否则，$\text{becoder}$ 评测机会返回 `Accepted`。

只需要用 `if`、`else if`、`else` 模拟即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,l,r,T[maxn],M[maxn];
int main(){
	cin>>n>>l>>r;
	for(int i=1;i<=n;i++) cin>>T[i]>>M[i],T[i]/=2;
	for(int i=1;i<=n;i++){
		int t,m;cin>>t>>m;
		if(i>=l&&i<=r) cout<<"System Error\n";
		else if(M[i]>m) cout<<"Memory Limit Exceeded\n";
		else if(T[i]>t) cout<<"Time Limit Exceeded\n";
		else cout<<"Accepted\n";
	}
}
```

---

## 作者：Pyrf_uqcat (赞：4)

题目都告诉你了，分支结构一个个遍历下去不就行了，水红。

只需把评测规则都过一遍即可。


```cpp
#include <bits/stdc++.h>
#define int long long

#define N 100005

using namespace std;

int n,l,r,T[N],M[N],t[N],m[N];

signed main()
{
    cin>>n>>l>>r;
    for(int i=1;i<=n;i++)
    {
		cin>>T[i]>>M[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>t[i]>>m[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(l<=i&&i<=r)
		{
			cout<<"System Error"<<endl;
			continue;
		}
		if(M[i]>m[i])
		{
			cout<<"Memory Limit Exceeded "<<endl;
		}
		else if((T[i]/2)>t[i])
		{
			cout<<"Time Limit Exceeded"<<endl;
		}
		else
		{
			cout<<"Accepted"<<endl;
		}
	}
    return 0;
}

```

---

## 作者：_Deer_Peach_ (赞：4)

~题意：你重生了，成为了一个评测机，来评测一些代码。~

思路：

按照题目模拟，先判断 $i$ 是否在~你~评测机睡觉的时候，接着再判断空间是否在空间限制范围内，最后注意把 $t_i$ 除以 $2$ 再判断是否在时间限制范围内，如果都满足就通过了这道题。

代码：

几个分支语句：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int N=1e5+5;
int n,L,R;
struct node{
	int t,m;
}a[N],b[N];
signed main(){
	IOS;cin>>n>>L>>R;
	for(int i=1;i<=n;i++)cin>>a[i].t>>a[i].m;
	for(int i=1;i<=n;i++){
		cin>>b[i].t>>b[i].m;
		if(i>=L&&i<=R){cout<<"System Error"<<endl;continue;}//睡着了
		if(b[i].m<a[i].m)cout<<"Memory Limit Exceeded"<<endl;//超空间了
		else if(b[i].t<a[i].t/2)cout<<"Time Limit Exceeded"<<endl;//超时了
		else cout<<"Accepted"<<endl;//通过了
	}return 0;
}
```

---

## 作者：nightwatch.ryan (赞：3)

### Analysis
按照题目意思模拟即可。

对于第 $i$ 条提交记录：
- 先判断 $i$ 是否满足 $L \leq i \leq R$，如果满足，说明评测机在打瞌睡，输出 `System Error`。
- 接下来，判断 $M_i$ 是否大于 $m_i$，如果大于，说明空间超限，输出 `Memory Limit Exceeded`。
- 然后，判断 $\lfloor \frac{T_i}{2} \rfloor$ 是否大于 $t_i$，如果大于，说明时间超限，输出 `Time Limit Exceeded`。
- 否则，说明你的程序没有问题！输出 `Accepted`。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int T[N], M[N];
int main(){
    int n, l, r;
    cin >> n >> l >> r;
    for(int i = 1; i <= n; i ++)
     cin >> T[i] >> M[i];
    for(int i = 1; i <= n; i ++){
        int t, m; cin >> t >> m;
        if(i >= l && i <= r) cout << "System Error\n";
        else if(M[i] > m) cout << "Memory Limit Exceeded\n";
        else if(T[i] / 2 > t) cout << "Time Limit Exceeded\n";
        else cout << "Accepted\n";
    }
}
```

---

## 作者：XsIeEiKcEk (赞：3)

### 题意

有 $n$ 道题，第 $i$ 道题耗费了 $T_i$ 秒，空间耗费 $M_i$ 。而第 $i$ 道题的题的时间限制为 $t_i$ 秒，空间限制为 $m_i$ 。

在第 $L$ 到第 $R$ 道题时，评测~~姬~~机会打瞌睡。

如果处理这一题时评测机在打瞌睡，也就是如果 $L\le i\le R$，输出```System Error```。

否则，如果 $M_i>m_i$ ，输出```Memory Limit Exceeded```。

否则，如果 $\lfloor\frac{T_i}{2}\rfloor>t_i$ ,输出```Time Limit Exceeded```。 $\lfloor x\rfloor$ 表示最大的比 $x$ 小的整数。

否则，输出```Accepted```。

### 解法

按照题意去判断。

但是，关于 $\lfloor\frac{T_i}{2}\rfloor$ 不一定要用
```cpp
floor(double(T[i])/2.0)
```
来表示，因为```int```类型相除的商会自动向下取整，所以只需要用
```cpp
T[i]/2
```
表示就好了。

### [AC](https://www.luogu.com.cn/record/201061059) CODE
```cpp
#include <iostream>
using namespace std;

int main() {
	int n, l, r, t[100000], m[100000], T[100000], M[100000];
	cin >> n >> l >> r;
	for (int i = 0; i < n; i++)
		cin >> T[i] >> M[i];
	for (int i = 0; i < n; i++)
		cin >> t[i] >> m[i];
	for (int i = 0; i < n; i++) {
		if (i + 1 >= l && i + 1 <= r)
			cout << "System Error\n";//\n同endl
		else if (M[i] > m[i])
			cout << "Memory Limit Exceeded\n";
		else if (T[i] / 2 > t[i])
			cout << "Time Limit Exceeded\n";
		else
			cout << "Accepted\n";
	}
	return 0;
}
```

---

## 作者：yedalong (赞：3)

## 思路

很简单的题目，直接根据题意判断即可。\
需要注意的是，优先判断 `SE`，接着判断 `MLE`，然后才判断 `TLE`。

## AC code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,l,r,t[100005],m[100005],a,b;
int main(){
    cin>>n>>l>>r;
    for(int i = 1;i<=n;i++) cin>>t[i]>>m[i];
    for(int i = 1;i<=n;i++){
        cin>>a>>b;
        if(l<=i&&i<=r) cout<<"System Error\n";
        else if(b<m[i]) cout<<"Memory Limit Exceeded\n";
        else if(a<t[i]/2) cout<<"Time Limit Exceeded\n";
        else cout<<"Accepted\n";
    }
    return 0;
}

```

---

## 作者：M1__ (赞：3)

# 题解：P11654 「FAOI-R5」becoder
[题目传送门](https://www.luogu.com.cn/problem/P11654)
## 题目思路
按题意模拟即可。       
- 用 $temp$ 记录一组数据的编号，当 $L \le temp \le R$ 时，输出 ```System Error``` 即可；
- 当 $M_i > m_i$ 时，输出 ```Memory Limit Exceeded``` 即可；
- 当 $M_i \le m_i,\left \lfloor \frac{T_i}{2} \right \rfloor > t_i$ 时，输出 ```Time Limit Exceeded``` 即可；
- 如果上述条件都不满足，输出 ```Accepted``` 即可。
- 注意数据范围、输出格式和换行符。
## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1e5+10;
ll n,L,R;
ll T[MAXN],t[MAXN],M[MAXN],m[MAXN];
ll temp;
int main(){
	cin>>n>>L>>R;
	for(int i=1;i<=n;i++){
		cin>>T[i]>>M[i];
	}
	for(int i=1;i<=n;i++){
		cin>>t[i]>>m[i];
		temp=i;
		if(temp>=L&&temp<=R) cout<<"System Error"<<"\n";
		else if(M[i]>m[i]) cout<<"Memory Limit Exceeded"<<"\n";
		else if(M[i]<=m[i]&&floor(T[i]/2)>t[i]) cout<<"Time Limit Exceeded"<<"\n";
		else cout<<"Accepted"<<"\n";
	}
	return 0;
}
```

---

## 作者：ny_123457 (赞：2)

## Part 1.思路
先预处理一下所有的 $T_i$，剩下的其实就是 `if`，`else if` 和 `else` 的小应用。  
循环从头到尾遍历一遍，如果此时测评机在睡觉即 $l \le i \le r$ 时输出 `System Error`。  
不在睡觉时就要注意，空间超限时无论时间是否超限都是输出 `Memory Limit Exceeded`，空间没有超限但时间超限是才是输出 `Time Limit Exceeded`。  
**注意：超限是小于等于。**  
## Part 2.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,r,a,b,c,t[100005],m[100005],T[100005],M[100005];
int main(){
	cin>>n>>l>>r;
	for(int i=1;i<=n;i++)cin>>T[i]>>M[i];
	for(int i=1;i<=n;i++)cin>>t[i]>>m[i];
	for(int i=1;i<=n;i++){
		T[i]/=2;
		if(l<=i&&r>=i)cout<<"System Error"<<endl;
		else{
			if(M[i]>m[i])cout<<"Memory Limit Exceeded"<<endl;
			else if(T[i]>t[i])cout<<"Time Limit Exceeded"<<endl;
			else cout<<"Accepted"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：monkeyking_QAQ (赞：2)

[题目传送门。](https://www.luogu.com.cn/problem/P11654)

### 题意：

输入评测题目的次数 $n$ 和评测机休息区间的两个端点 $L,R$，然后输入每次评测耗费的时间 $T_i$ 和耗费的空间 $M_i$，再输入道题的时间限制 $t_i$ 和空间限制 $m_i$。每输入一次题目的时间与空间限制，就输出此题的评测结果。

### 思路：

简单的一道分支语句题。

我们来简化一下评测规则：

+ 如果当前判断的题目 $i$，不在 $[L,R]$ 这个区间内，则输出 `System Error`；

+ 如果当前判断的题目 $i$，在 $[L,R]$ 这个区间内，并且 $M_i > m_i$，则输出 `Memory Limit Exceeded`；

+ 如果当前判断的题目 $i$，在 $[L,R]$ 这个区间内，并且 $M_i \le m_i, ⌊\frac{T_i}{2}⌋ > t_i$，则输出 `Time Limit Exceeded`；

+ 否则，输出 `Accepted`。
### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,r;
int T[100005],M[100005],t[100005],m[100005];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    cin>>n>>l>>r;
    for(int i=1;i<=n;i++)
    	cin>>T[i]>>M[i];
    for(int i=1;i<=n;i++){
    	cin>>t[i]>>m[i];
    	if(i>=l && i<=r)               //第一种情况
    		cout<<"System Error"<<endl;
    	else if(M[i]>m[i])    //第二种情况
    		cout<<"Memory Limit Exceeded"<<endl;
    	else if(M[i]<=m[i] && (T[i]/2)>t[i])    //第三种情况
    		cout<<"Time Limit Exceeded"<<endl;
    	else                      //第四种情况
    		cout<<"Accepted"<<endl;
	}
    return 0;
}
```

---

## 作者：shy_lihui (赞：2)

闲话：第一眼以为有多个 $[L,R]$ 就想了个树状数组的解法然后发现只有一组。

小磨你。

先把所有的 $T_i,M_i$ 存起来，之后输入一组 $t_i,m_i$ 检验测评状态即可。

判断测评状态函数如下：
$$
\operatorname{output}(i) = \begin{cases}
  \texttt{System Error} &L \le i \le R\\
   \texttt{Memory Limit Exceeded} & M_i > m_i \\
  \texttt{Time Limit Exceeded}& M_i \le m_i \operatorname{and} \lfloor \frac{T_i}{2} \rfloor > t_i \\
  \texttt{Accepted} & \text{other}
\end{cases}

$$

具体细节请看代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,l,r;
int T[100005],M[100005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>l>>r;
	for(int i=1;i<=n;i++)
	{
		cin>>T[i]>>M[i];
	}
	for(int i=1;i<=n;i++)
	{
		int m,t;
		cin>>t>>m;
		if(l<=i&&i<=r)//如果测评姬在摸鱼 
		{
			cout<<"System Error\n";//则是SE 
		}
		else if(M[i]>m)//超出内存限制 
		{
			cout<<"Memory Limit Exceeded\n";//MLE
		}
		else if(M[i]<=m && signed(T[i]/2)>t)
		{//没有 MLE 但是 TLE了 
			cout<<"Time Limit Exceeded\n";
		}
		else
		{
			cout<<"Accepted\n";//other 
		}
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

# 题解：P11654 「FAOI-R5」becoder

## 思路

直接根据题意模拟即可。

其中分数的计算方法为分子除以分母。

由于 C++ 会自动向下取整，因此无需在 $\left \lfloor \frac{T_i}{2} \right \rfloor$ 这个运算中进行 `floor()` 操作。

## 代码

```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int n, l, r, T[100005], M[100005], t, m;

int main()
{
    cin >> n >> l >> r;
    for (int i = 1; i <= n; i++)
        cin >> T[i] >> M[i];
    for (int i = 1; i <= n; i++)
    {
        cin >> t >> m;
        if (l <= i && i <= r)
            cout << "System Error" << endl;
        else if (M[i] > m)
            cout << "Memory Limit Exceeded" << endl;
        else if (M[i] <= m && T[i] / 2 > t)
            cout << "Time Limit Exceeded" << endl;
        else
            cout << "Accepted" << endl;
    }
    return 0;
}
```

---

## 作者：Curry_mvp (赞：2)

挺好的一道模拟题

~~也是本场比赛我唯一AC的一道题~~

开一个结构体，分别记录时间限制和空间限制，开两个数组，一个记录标准的时间和空间，另一个记录评测机限制的时间和空间，然后做毕竟就行，至于休眠期特判一下就行了

注意判断的顺序，先判断空间，然后在满足空间要求的前提下，再判断时间

注意一下输入顺序，别搞反了

代码贴在下面：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,l,r;
struct node
{
	int t;
	int m;
};
const int maxn=1e5+5;
node a[maxn];
node b[maxn];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
signed main ()
{
	n=read();
	l=read();
	r=read();
	for(int i=1;i<=n;i++)
	{
		a[i].t=read();
		a[i].m=read();
	}
	for(int i=1;i<=n;i++)
	{
		b[i].t=read();
		b[i].m=read();
	}
	for(int i=1;i<=n;i++)
	{
		if(i>=l&&i<=r)
		{
			cout<<"System Error"<<"\n";
			continue;
		}
		else
		{
			if(a[i].m>b[i].m)
			{
				cout<<"Memory Limit Exceeded"<<"\n";
			}
			else if(a[i].m<=b[i].m&&a[i].t/2>b[i].t)
			{
				cout<<"Time Limit Exceeded"<<"\n";
			}
			else
			{
				cout<<"Accepted"<<"\n";
			}
		}
	}
	return 0;
}

```
注释就不加了，水

管理大大求过！！！

---

## 作者：xf20280111 (赞：2)

考查了分支结构，字符串的入门知识点。

### 思路
可以用数组存储数据。

用 if 语句进行判断每种情况的条件，一定要清楚题目中的条件。

### AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100000 + 10;
int T[N],M[N],t[N],m[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,l,r;cin >> n >> l >> r;
	for (int i = 1;i <= n;i++){
		cin >> T[i] >> M[i];
	}
	for (int i = 1;i <= n;i++){
		cin >> t[i] >> m[i];
	}
	for (int i = 1;i <= n;i++){
		if (i >= l and i <= r) cout << "System Error" << "\n";
		else if (M[i] > m[i]) cout << "Memory Limit Exceeded" << "\n";//注意，每个输出完后都要换行
		else if (T[i] / 2 > t[i]) cout << "Time Limit Exceeded" << "\n";
		else cout << "Accepted" << "\n";
	}
	return 0;
}
```
建议评红

---

## 作者：Eric1030 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P11654)

这道题是一道简单的运用到了判断和循环的题目。

我们只需要把数据输入进来，然后判断四个条件即可。需要注意的是，输出完每一组数据对应的结果后要换行。下面是条件判断的框架。
```cpp
if(i在L和R之间)
{
    //输出所对应字符串，下面的同理
}
if(代码空间超限)
{
    
}
if(时间超限)
{
    
}
else//来到了这个判断就说明通过了
{
    
}
```


思路讲完了，下面就是 [AC](https://www.luogu.com.cn/record/201087547) 代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
int n, l, r, t[100005], m[100005], a[100005], b[100005];
int main()
{
	cin >> n >> l >> r;
	for (int i = 1;i <= n;i++)
	{
		cin >> t[i] >> m[i];//t[i]也就是是T[i]，m[i]也就是题目中的M[i]
	}
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i] >> b[i];//a[i]也就是t[i]，b[i]是题目中的m[i]
		if (i >= l && i <= r)//判断评测机是否在打瞌睡
		{
			cout << "System Error" << endl;//记得换行
		}
		else if (m[i] > b[i])//看你的代码空间是否超限，如果能执行到这一条就说明评测机没有打瞌睡，就不用判断是否打瞌睡了，下面的同理
		{
			cout << "Memory Limit Exceeded" << endl;
		}
		else if ((t[i] / 2) > a[i])//看时间是否超限
		{
			cout << "Time Limit Exceeded" << endl;
		}
		else//上面的都不成立就直接输出"Accepted"
		{
			cout << "Accepted" << endl;
		}
	}
	return 0;//结束！
}
```

---

## 作者：zouchenjun (赞：1)

### 思路
先读入每组的的时间及空间，分别判断不同状态即可。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T[100005],M[100005];
int main(){
	int n,L,R;
	cin>>n>>L>>R;
	for(int i=1;i<=n;i++)cin>>T[i]>>M[i];
	for(int i=1;i<=n;i++){
		int t,m;cin>>t>>m;
		//分别判断每种状态
		if(i>=L&&i<=R)cout<<"System Error\n";
		else if(M[i]>m)cout<<"Memory Limit Exceeded\n";
		else if(T[i]/2>t)cout<<"Time Limit Exceeded\n";
		else cout<<"Accepted\n";
	}
}
```

---

## 作者：getchar_unlocked (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P11654)

### 思路

**模拟**题。

首先判断打瞌睡的情况，即 $i\ge L$ 且 $i\le R$ 时，输出 `System Error`。

其次判断代码空间超限，即 $M_i>m_i$ 时，输出 `Memory Limit Exceeded`。

然后判断时间超限，即 $\lfloor\frac{T_i}{2}\rfloor>t_i$ 时，输出 `Time Limit Exceeded`。

最后只剩下 `Accepted` 的结果。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e5+10;
int T[N],M[N];
signed main(){
	int n=read(),l=read(),r=read();
	for(int i=1;i<=n;++i)
		T[i]=read(),M[i]=read();
	for(int i=1;i<=n;++i){
		int t=read(),m=read();
		if(i>=l&&i<=r)
			printf("System Error\n");
		else{
			int temp=T[i]/2;
			if(M[i]>m)
				printf("Memory Limit Exceeded\n");
			else if(temp>t)
				printf("Time Limit Exceeded\n");
			else printf("Accepted\n");
		}
	}
	return 0;
}
```

---

## 作者：guoxinda (赞：1)

## 题目概述
$\text {becoder}$ 的评测机按如下规则评判提交：
- 如果 $\text {becoder}$ 的评测机在打瞌睡，评测结果会返回 ```System Error```；
- 如果 $\text {becoder}$ 的评测机没有打瞌睡，且 $M_i > m_i$，评测结果会返回 ```Memory Limit Exceeded```；
- 如果 $\text {becoder}$ 的评测机没有打瞌睡，且 $M_i \le m_i,\left \lfloor \frac{T_i}{2} \right \rfloor > t_i$，评测结果会返回 ```Time Limit Exceeded```。
- 否则，$\text {becoder}$ 评测机会返回 ```Accepted```。\
请你输出所有 $\text {becoder}$ 对于每个测评会返回的结果。你不考虑除上述四种返回结果以外的情况。\
第一行三个正整数，$n,L,R$，代表询问的次数，和评测机睡觉的区间。\
接下来 $n$ 行，每行两个正整数代表 $T_i,M_i$。\
接下来 $n$ 行，每行两个正整数代表 $t_i,m_i$。\
输出 $n$ 行，第 $i$ 行一个字符串代表第 $i$ 次评测的结果。
## 思路
很明显，这题考多分支语句的运用。
- 首先，判断 $i$ 在不在区间内，在则输出 ```System Error```；
- 然后，判断是否 $M_i > m_i$，如果是则输出 ```Memory Limit Exceeded```；
- 其次，判断是否  $M_i \le m_i,\left \lfloor \frac{T_i}{2} \right \rfloor > t_i$，如果是则输出 ```Time Limit Exceeded```；
- 如果都不是，输出  ```Accepted```。\
直接模拟即可。
## code
```cpp 
#include<bits/stdc++.h> 
using namespace std;
#define int long long
int n,L,R,T[100010],M[100010],t[100010],m[100010];
signed main(){
    ios::sync_with_stdio(0);
    cin>>n>>L>>R;
    for(int i=1;i<=n;i++)cin>>T[i]>>M[i];
	for(int i=1;i<=n;i++){
		cin>>t[i]>>m[i];
		if(i>=L&&i<=R){//评测机在打瞌睡
			cout<<"System Error";
		}else if(M[i]>m[i]){//becoder 的评测机没有打瞌睡，且你的代码空间超限
			cout<<"Memory Limit Exceeded";
		}else if(T[i]/2>t[i]){//整数除自动向下取整 
			cout<<"Time Limit Exceeded";
		}else{//输出Accepted
			cout<<"Accepted";
		}
		cout<<endl;
	}
    return 0;
}
```

---

## 作者：yu1128_AKIOI (赞：0)

## 思路

按题意模拟即可。注意 $[L,R]$ 为闭区间，应写成 `L<=i&&i<=R`。还有注意区分变量名的大小写。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,L,R,T[100010],M[100010],t[100010],m[100010];
int main(){
	cin>>n>>L>>R;
	for(int i=1;i<=n;i++) cin>>T[i]>>M[i];
	for(int i=1;i<=n;i++){
		cin>>t[i]>>m[i];
		if(L<=i&&i<=R) cout<<"System Error\n";
		else{
			if(M[i]>m[i]) cout<<"Memory Limit Exceeded\n";
			else if(T[i]/2>t[i]) cout<<"Time Limit Exceeded\n";
			else cout<<"Accepted\n";
		}
	} 
} 
```

---

## 作者：zhoumurui (赞：0)

### 题面展示

# 「FAOI-R5」becoder

## 题目背景

**警告：请不要试图使用 AI，使用者按作弊处理。[](U2FsdGVkX1+8wT+JZ1ip+v0oY6hhnMxzAjstIUBCUdCVwJ2Z0rlSh6uXq4IA+5ZrYH1RdrAQA+OJv3OGw4QGK0iXAIoA4YnMa7Kw/ekc7pwrCPvNf3IhE6viz6n/tN1N2c1Rt4hkYR9cwV5eDe0EK8wAzJTkvViv6QdJCaOl5MjmmB8nT2WYOFQnv7w6SF1YxfHxnufxKWTFdB0UYHW6+VMJdiBUCGRu/1sRklBNIS5UOiGnlQuCuaKO3sCUsiAKALbwovP6dJSSZ3iE/Z3R7DTIjrV3j0vGwG2phyR64wvO3d9dsc2djlGauYnyy3sMfQswoW6b41z3hDfeZw/DnXKjhuaGbHs+7Ajqm4TBA+fYvl6cJ91kP9J379ApOCYPrPY1h19IWA9e38qwSVBOKWHHo7H3EmKfkwQOUvLtbc8iBEtXBvFDkY1eVE8n9OKVWpVM4drlBxksDUjAdvgjQrHcjH+hR38X4SwnYkw74UAfVDmPMfj7eRx9RH99Qnz86UfSMf7IwSdRg4apkYQfgd2remtAjn01tRt+44K468y9VLSVX/RfRCbZ9Yyf1IUyAbZMUyBXZ0wqA+J7m841WDvkfbUxUyrmXxx6OMKG8r5tueIc+lS5Ex0rDYYBMybbo4RXvhw0fSPCIDJlXBZkkxV7FGIEJyFRJ+26Z5W+rXmx1blPe2UeTo5SV1ggNMEsRdbKkzwQVr+E2fi8bwknTba5+P0fkoiepvvgszZh+ujJ7cskkprvRrZDwhCZ9I06uBU26O1teI4Bydqfm8zrGdNlMDRX5wT2GnAL/NV80p3w22UHWG4Mv1Vx2E8V/Dd81I8ePKkKhQEbvSmxIujtROCSLQhl8TxBZcUKxPdfseP4uEKdTNGl5y2kQ7o1JpCnP7wpBe3SF6Iab9XvCn3yQxk6PRSMsXUO2rkzZe/KK9Fs9XnULoMHvqehKE4Aksw8NQcmFiQsdLVu0YnN+jjCP5eEVUiSE+6FveWVyD2mIjnkJaTEcoj9jpqcpBTb5DLuAy9GS83aKInoPxZsxe1QF1ug7/K4DglFF0gK9PEHdWbiC/iIImZsWVV8/JfhQaLd+nwePbt1rVaC2X1D9gsY2D6CKGlxDGNfkbvquU/wLzKVG5cEBJcMNANz/y9msVKaWM1kv2uAcM2LW8x4RoSGiaePD/WTCjTgRaccK2op1a2Z46cp2M5iDZ0lgT73CCl9YdPHIn5EOZXN9i42bHMdt7vkA8f+8BiFjs/iYGgHRfMd3b0mmX4PVy3NpcuWSe6TTg1RvG8cBkoI7dFZ3kICQ0N66U9yIzVVDjk28Mu/cuUaBKLWfeS2pTqGpDYMT2p7QPptI/LiKG6ZE5JguXZYTUhqkwp7D5hV48R6Ep+Wr9Joeo3U3tKT6DpQ+CVwOmPt5UZjMLiFBgqWamjnWmgT4i6+xVMkRBM69OpUz9tE9Fw=)**

[$\text {becoder}$ - 最快的中文 OJ](https://www.becoder.com.cn/)。

## 题目描述

评测机需要处理 $n$ 次题目的评测。已知第 $i$ 次提交在评测机上跑了  $\left \lfloor \frac{T_i}{2} \right \rfloor $ 秒，空间耗费 $M_i$。

已知第 $i$ 次提交的题目的时间限制 $t_i$ 和空间限制 $m_i$。

$\text {becoder}$ 的评测机按如下规则评判提交：
- 如果题号在 $[L,R]$ 范围内，评测机会无法运行，评测结果会返回 ```System Error```；
- 如果评测机正常运行，且你的代码空间超限，即 $M_i > m_i$，评测结果会返回 ```Memory Limit Exceeded```；
- 如果评测机正常运行，且你的代码空间不超限，时间超限，即 $M_i \le m_i,\left \lfloor \frac{T_i}{2} \right \rfloor > t_i$，评测结果会返回 ```Time Limit Exceeded```。
- 否则，评测结果会返回 ```Accepted```。

请你输出评测机对于者 $n$ 个测评分别返回的结果。

### 解题思路

使用分支结构 if-else 来判断每个条件并分别输出。

### 核心代码展示
```cpp
int n,l,r,t[1000005],m[1000005],T[1000005],M[1000005];
signed main(){
    cin>>n>>l>>r;
    for (int i=1;i<=n;i++)cin>>T[i]>>M[i];
    for (int i=1;i<=n;i++)cin>>t[i]>>m[i];
    for (int i=1;i<=n;i++){
        if (i>=l&&i<=r){
            cout<<"System Error\n";
        }
        else if (M[i]>m[i]){
            cout<<"Memory Limit Exceeded\n";
        }
        else if (T[i]/2>t[i]){
            cout<<"Time Limit Exceeded\n";
        }
        else cout<<"Accepted\n";
    }
    return 0;
}
```

---

## 作者：mishitaotuoyyds (赞：0)

## 思路：
这道题没什么太大的难度，只需要按照题目模拟即可，但是有很多细节，如下。
1. 在在测评 $[L,R]$ 内的题目时不是 $i\le L$ 并且 $i\ge R$ 而是 $i\ge L$ 并且 $i\le R$。
2. 这个 $\left \lfloor \frac{T_i}{2} \right \rfloor $ 不需要向上取整。
3. 四种情况需要一个个判断，不能修改顺序。
4. 注意格式和换行。
## 参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,l,r;
long long a[100100][2],b[100100][2];
int main(){
	cin>>n>>l>>r;
	for(int i=1;i<=n;i++)cin>>a[i][0]>>a[i][1];
	for(int i=1;i<=n;i++)cin>>b[i][0]>>b[i][1];
	for(int i=1;i<=n;i++){
		if(i>=l&&i<=r)cout<<"System Error\n";
		else{
			if(a[i][1]>b[i][1])cout<<"Memory Limit Exceeded\n";
			else if(a[i][1]<=b[i][1]&&a[i][0]/2>b[i][0])cout<<"Time Limit Exceeded\n";
			else cout<<"Accepted\n";
		}
	}
	return 0;
}
```
完结撒花。

---


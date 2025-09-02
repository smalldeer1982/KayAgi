# [ABC157C] Guess The Number

## 题目描述

如果存在满足以下条件的非负整数，请输出其中最小的一个。如果不存在这样的整数，请输出 $-1$。

- 该整数的十进制表示恰好为 $N$ 位数。（$0$ 被视为 $1$ 位数。对于其他整数，不允许在首位添加 $0$。）
- 从左起第 $s_i$ 位上的数字为 $c_i$，其中 $i = 1, 2, \cdots, M$。

## 说明/提示

### 限制条件

- 所有输入均为整数。
- $1 \leq N \leq 3$
- $0 \leq M \leq 5$
- $1 \leq s_i \leq N$
- $0 \leq c_i \leq 9$

### 样例解释 1

$702$ 的从左起第 $1$ 位是 $7$，第 $3$ 位是 $2$，因此 $702$ 满足题目条件。此外，$701$ 及以下的非负整数都不满足题目条件。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
1 7
3 2
1 7```

### 输出

```
702```

## 样例 #2

### 输入

```
3 2
2 1
2 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
3 1
1 0```

### 输出

```
-1```

# 题解

## 作者：zhou_ziyi (赞：3)

### 思路
这只是一道普通的模拟题……  
这道题中无解的情况有两种：
+ 不是一位数并且首位为 `0`。
+ 每一位上为两个不同的值。

除此之外，我们要找到最小的 `好数`， 就应该把首位赋值为 `1`, 其余赋值为 `0`。
### Code
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 15;
int n, m, s, c;
int ans[MAXN];
int main() {
	scanf("%d %d", &n, &m);
	if (n == 1 && !m) { //特判
		printf("%d", 0);
		return 0;
	}
	for (int i = 1; i <= n; i++)
		ans[i] = -1;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &s, &c);
		if (s == 1 && c == 0) {
			if (n == 1) {
				ans[s] = c;
				continue;
			}
			printf("%d", -1);
			return 0;
		}
		if (ans[s] == -1 || ans[s] == c) {
			ans[s] = c;
			continue;
		}
		printf("%d", -1);
		return 0;
	}
	if (ans[1] == -1)
		ans[1] = 1;
	for (int i = 1; i <= n; i++)
		printf("%d", ans[i] != -1 ? ans[i] : 0);
	return 0;
}
```

---

## 作者：Pencil_22 (赞：2)

链接：[link](https://www.luogu.com.cn/problem/AT5335)。
***
1. 题意：

按题目要求输入，并将每一个数位赋值，最后将整个数字输出。

要求：
- 输出的数是所有满足条件的 $n$ 位数中最小的。
- 不合法就输出 `-1`。

2. 思路：

本题是一道[细节调整](https://www.luogu.com.cn/record/list?pid=AT5335&user=542442)题，换句话说，很多细节，但并不难。

做题前，先要知道以下几点细节：
- 形如 $0$ 后面跟 $n - 1$ 位数的数不是 $n$ 位数，特别的 $0$ 是一位数。因此如若说 $n \ge 2$ 且第一位要求赋值为 $0$，则它不合法；又有 $n \ge 2$ 且第一位没有赋值，则改它为 $1$。
- 如若一个数位必须同时满足多个不同的数值，则该数不合法。

看完了以后，动手打一打吧。

3. 代码（核心）
```cpp
int n, m, a[8], s, c;
bool f, vis[8];
scanf("%d %d", &n, &m);
for (int i = 1; i <= m && !f; i++) {
	scanf("%d %d", &s, &c);
	if ((s == 1 && c == 0 && n != 1)/*第一点细节*/ || (vis[s] && a[s] != c)/*第二点细节*/)
		f = true;
	else
		a[s] = c, vis[s] = true;
}
if (f) {
	printf("-1");
	return 0;
}
a[1] == 0 && n > 1 ? a[1] = 1 : 1;//第一点细节
for (int i = 1; i <= n; i++)
	printf("%d", a[i]);
```

---

## 作者：SpeedStar (赞：2)

## 题目
见[C - Guess The Number](https://atcoder.jp/contests/abc157/tasks/abc157_c)

### 算法
关于这题只需注意几点：

1. 这个十进制整数不能有前导零
2. 同一位数可以赋相同的值，如果赋不同的值则输出$-1$
3. 至于其他方面只需要处理好细节就行了

#### C++ 代码
```
#include <iostream>
#include <vector>

using namespace std;

int n, m;
int s[10], c[10];

bool check(int x) {
	vector<int> xs;
	
	if (x == 0) xs.push_back(0);
	else {
		while (x) {
			xs.push_back(x % 10);
			x /= 10;
		}
	}
	
	if (xs.size() != n) return false;
	
	for (int i = 0; i < m; i++) {
		if (xs[n - s[i]] != c[i]) return false;
	}
	
	return true;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) cin >> s[i] >> c[i];
	
	for (int i = 0; i < 1000; i++) {
		if (check(i)) {
			cout << i << endl;
			return 0;
		}
	}
	
	cout << -1 << endl;
	
	return 0;
}
```

---

## 作者：wangyi_c (赞：1)

[你谷题目传送门](https://www.luogu.com.cn/problem/AT5335)

[AT题目传送门](https://atcoder.jp/contests/abc157/tasks/abc157_c)

## 1.题目大意

题目定义了一个“好数”：

- 有 $n$ 位。

- 且从左往右第 $s_i$ 位的值为 $c_i$。

- 这个数还**没有前导零**。

给我们所有的 $s_i$ 和 $c_i$，求满足条件的最小的“好数”，如果没有输出 $-1$。

## 2.思路讲解

我们可以定义一个数组，存每一位上的数字，然后我们再在循环中一边读入，一边判断，一边存储。没有的位子上都存零，保证最小。

- 应对第一个问题：太简单，不用应对。

- 应对第二个问题：在每次存之前先看一下当前这个位子是否被存过，如果有，就输出 $-1$，否则就可以存。

- 应对第三个问题：存入时判断一下，如果存第一位为零并且 $n$ 不等于 $1$，那么就会产生前导零，输出 $-1$；并且在输出时还要判断第一位为零并且 $n$ 不等于 $1$，那么第一位就变成 $1$。(~~我绝对不会告诉你我在这WA了10次。~~)

## 3.AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[20];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int s,c;
		cin>>s>>c;
		if(a[s]!=c && a[s]!=0){//判断是否重复存一个位子
			cout<<-1;
			return 0;
		}
		if(s==1 && c==0 && n>1){//判断是否会出现前导零
			cout<<-1;
			return 0;
		}
		a[s]=c;//存入当前位置
	}
	if(a[1]==0 && n>1) a[1]=1;//第一位为0，那么第一位就变成1
	for(int i=1;i<=n;i++) cout<<a[i];
	return 0;
}
```
_THE END_

谢谢观看

By Wangyi

---

## 作者：LucasXu80 (赞：1)

这题细节十分的多。我来给大家总结一下这题的细节与做题时的心得。

读题很重要，我们一行行来读。

这里我建议大家有能力的话阅读英语题面，因为中文题面可能存在翻译有遗漏或不准确的情况。

> We assume $0$ to be a $1$ -digit integer. For other integers, leading zeros are not allowed.

$0$ 是一位数。

这个条件十分重要，说明 $0$ 是一个符合要求的数。但是在其他位数的数中，首位不能为 $0$，即最少是 $1$。

接下来我们来理思路。

1. 如何记录所有限制？

由于 $n \leq 3$，直接开一个 `a[4]` 的数组记录即可。对于每一组输入的 $s,c$，进行操作 `a[s]=c`。

2. 如何判断不存在这样的数（即输出 `-1`）？

- 很容易想到，如果出现对于一组 $i,j \leq m$ 且 $i \not =j$，$s_i=s_j$ 且 $c_i \not =c_j$，就不成立；
- 如果对于 $n \geq 2$，有 $s=1,c=0$，由高位不能为 $0$ 的限制可得不存在。

3. 如何使输出的数最小？

容易想到：

- 对于所有 $i \geq 2$，如果 `a[i]` 还没有被赋值，那么将其赋值为 $0$；
- 对于 $i=1$，如果 `a[i]` 还没有被赋值，那么将其赋值为 $1$。

这样就结束了吗？

我们提到过，$0$ 是一个符合要求的一位数。所以，当 $n=1$ 时，如果第 $1$ 位没有被赋值，那么我们应该直接输出 $0$，而非赋值为 $1$。

最后一位一位输出即可。

我们来看代码的实现。

```cpp
#include <iostream>
using namespace std;
int n,m,s,c,a[4]={0,-1,-1,-1}; // 开数组记录每一位，先赋值为 -1 表示没有被赋值过
int main()
{
    cin>>n>>m;
    if (n==1 && m==0) // 特判
    {
        cout<<0;
        return 0;
    }
    while (m--) // m 组限制
    {
        cin>>s>>c;
        if (s==1 && c==0) // 第一位为 0
        {
            if (n==1)
            {
                a[1]=0; // 是一位数，没问题
                continue;
            }
            cout<<-1; // 不是一位数，不成立
            return 0;
        }
        if (a[s]==-1 || a[s]==c) a[s]=c; // 未被复值过或是原来就是这个值，那么赋值
        else // 被赋值过且原来不是这个值，矛盾
        {
            cout<<-1;
            return 0;
        }
    }
    if (a[1]==-1) a[1]=1; // 未被赋值，设为 1
    for (int i=2; i<=n; i++)
    {
        if (a[i]==-1) a[i]=0; // 未被赋值，设为 0
    }
    for (int i=1; i<=n; i++) cout<<a[i]; // 一位一位输出
    return 0;
}
```

这篇题解就到这里啦，感谢大家的阅读！

---

## 作者：_wjr_ (赞：0)

首先，还是那句话：如果一道红题，有一个人反反复复，耗时8小时，交了15遍才过，请不要怀疑这道题的难度。因为那个蒟蒻 $\cdots$

是我。

不谈这些事情了，我们先看一眼题目。

## 题目大意

我们要找出最小的 $n$ 位数，使得对于第 $s_i$ 位上的数字是 $c_i$。如果不满足以上条件，则输出 $-1$。

## 解题思路

首先，要保证第 $s_i$ 位上的数是 $c_i$，用整型变量很明显不太合适。我们维持一个数组 $a$，$a_i$ 表示这个数的第 $i$ 位，这样就方便修改一个单独的位了。

而如果，第 $x$ 位上既是 $y$，也是 $z$，当 $y$ 与 $z$ 不等时，整个数也就不可能满足要求，这时候直接输出 $-1$ 即可。

到这里，似乎整道题还很简单嘛！那有什么值得某人连错 14 遍呢？

## 坑

不难注意到，当 $n$ 是 $1$，且不进行任何操作的时候，明显应该输出 $0$，而不像其他多位数一样，首位没有值的时候强行把它赋值为$1$。那么，整道题就做完啦。

献上AC代码！

## AC code

```cpp
#include<bits/stdc++.h>

using namespace std;

int a[100010];

bool flag[100010];//判断每一位是否被改动过

int main()
{
    int n, m;
    cin >> n >> m;
    if (n == 1 && !m) //特判，当n是1且m是0的时候，输出0而不是1
    {
        cout << 0 << endl;
        return 0;
    }
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        if (!x || x > n || (flag[x] && a[x] != y) || (x == 1 && y == 0 && n >= 2) || y < 0 || y > 9)
        {
            cout << -1 << endl;
            return 0;
        }//判断是否可行
        else 
        {
            a[x] = y;
            flag[x] = true;
        }
    }
    
    if (a[1] || n == 1) cout << a[1];//特判，当首位有值或者n是1的时候直接输出首位，其余的要输出1
    else cout << 1;

    for (int i = 2; i <= n; i++)
        cout << a[i];
    return 0;
}
```

完结撒花！望管理员审过！

---

## 作者：Supor__Shoep (赞：0)

既然是一道红题，那么也多半是一个~~很水的~~模拟题。

本题确实不难，就是有些情况有些难发现。下面我列举出所有的坑点以及条件。

- 如果 $m=0$，根据 $n$ 的大小分别输出 $0,10,100$。

- 如果输入过程中，$s_i=1$ 并且 $c_i=0$，那么就说明最高位是 $0$，肯定是不行的。但是同时 $n=1$ 的情况除外，这种情况直接输出 $0$。

- 如果有 $s_i=s_j$ 并且 $c_i≠c_j$，就说明一个位上同时出现了两个值，肯定是不行的。

- 如果最高位并没有植入任何一个值，就补上 $1$。

- 如果非最高位没有植入值，就补上 $0$。

我们用 set 类型数组储存，最后直接输出就行了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
set<int> st[15];
void END(){puts("-1");exit(0);}
int main()
{
	cin>>n>>m;
	if(!m)
	{
		if(n==1)	puts("0");
		if(n==2)	puts("10");
		if(n==3)	puts("100");
		return 0;
	}
	while(m--)
	{
		int x,y;
		cin>>x>>y;
		st[x].insert(y);
		if(st[x].size()>1||(n!=1&&x==1&&y==0))	END();
	}
	for(int i=1;i<=n;i++)
	{
		if(i==1&&!st[i].size())	cout<<"1";
		else if(!st[i].size())	cout<<"0";
		for(set<int>::iterator it=st[i].begin();it!=st[i].end();it++)	cout<<*it;
	}
	puts("");
	return 0;
}
```

---

## 作者：ztntonny (赞：0)

## 题意
定义“好数”是恰好有 $n$ 位，并且从左往右数第 $s_i$ 位是 $c_i$ 的数。输出最小的“好数”，若没有则输出 $-1$。
## 思路
首先，列举一下无解情况：
1. 同一位上两个不同数字；
2. 前导零并且不是一位数；
- 那么思路很清晰，所有初始值设为零，根据给出的数据将数组对应的数值从初始值更改，形成一个新数。如果最后第一位没有被赋值，因为数第一位不为零，所以改成最小的一，在输出时所有没有被赋值过的都是零。
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int a , b , c , d , ans[100] , s[100];//初始值都为零
int main()
{
    cin >> a >> b;
	for ( ll i = 0; i < b; i++ )
	{
		cin >> c >> d;
		if ( s[c - 1] == 0 )//正规赋值
		{
			ans[c - 1] = d;
			s[c - 1]++;
		}
		if ( s[c - 1] != 0 && d != ans[c - 1] || c == 1 && d == 0 && a > 1)//如果没有
		{
			cout << -1 << endl;
			return 0;//直接结束
		}
	}
	if ( ans[0] == 0 && a != 1 )//去前导零
	ans[0] = 1;
	for ( ll i = 0; i < a; i++ )
	cout << ans[i];
    return 0;
}
```


---

## 作者：COsm0s (赞：0)


## 整体思路：

按照题意模拟，并按顺序一位一位给各个数位赋值，最后将用于模拟的
整个数组进行输出操作。

细节方面：本题要求输出最小的数，那么当什么时候这个数**最小**呢？

当变量 $i=1$ 且 $a_i$ 并没有被赋值时，将 $a_i$ 赋值为 $1$（因为首位不能为零）；

当 $i>1$ 且 $a_i$ 并没有被赋值时，将 $a_i$ 赋值为 $0$。

这样，就可以保证当前数为最小。

## 坑点（也是无解处）

1、首先，这个数必须没有前导零（除非是一位数）。

2、一个数位一定要满足多个数，则直接判定无解。

3、一定要特判，即 $n=1$ 并且 $m=0$ 时，判定无解。

# Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[10]= {0,-1,-1,-1,-1,-1,-1,-1,-1}; //手动赋值
int n,m;
inline int read() {//快读
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)) {
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)) {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
signed main() {

	n=read(),m=read();
	if(n==1&&m==0) {//本题坑点 ：特判 
		cout<<0;
		return 0;
	}
	for(int i=1; i<=m; i++) {//开始模拟 
		int s=read(),t=read();
		if(a[s]!=-1&&a[s]!=t)//如果存在前导零，无解 
			return cout<<-1,0;
         if(s==1&&t==0&&n!=1)//如果已被赋值，无解 
         	return cout<<-1,0;
		a[s]=t;//赋值
	}
	if(a[1]==-1) a[1]=1;//特判a[1] 
	for(int i=1; i<=n; i++) {//将整个数字输出 
		if(a[i]==-1) cout<<0;
		else cout<<a[i];
	}
	return 0;
}
```


------------





---

## 作者：lovely_hyzhuo (赞：0)

本题是一个坑题。

有这么几个坑点：

$1.$ 在 $n=1$，$m=0$ 时，输出应为 $0$

$2.$ 首位不能为 $0$ (除非就 $1$ 位）

$3.$ 普通的不满足条件为在同一位上有多次不一样的数

接下来就简单多了，开开心心写代码就完了。

参考代码

```cpp
#include<iostream>
using namespace std;
struct b
{
	int s;
	int ch=0;
}a[400];
int main()
{
	int len=0;
	int n,m;
	cin>>n>>m;
	if(n==1&&m==0)
	{
		cout<<0;
		return 0;
	}
	a[1].s=1;
	for(int i=1;i<=m;i++)
	{
		int x,v;
		cin>>x>>v;
		if(n==1&&x==1&&v==0)
		{
			cout<<0;
			return 0;
		}
		if(x==1&&v==0)
		{
			cout<<-1;
			return 0;
		}
		if(a[x].ch==1&&v!=a[x].s)
		{
			cout<<-1;
			return 0;
		}
		if(x>n)
		{
			cout<<-1;
			return 0;
		}
		if(a[x].ch==0)
		{
			a[x].ch=1;
			a[x].s=v;
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<a[i].s;
	}
	return 0;
}
```


---

## 作者：迟暮天复明 (赞：0)

题意说明：


------------


定义“好数”是恰好有 $n$ 位，并且从左往右数第 $s_i$ 位是 $c_i$ 的数。

你需要输出最小的“好数”，若没有则输出 ``` -1 ``` 。



------------
楼上的方法是枚举“好数”，但是这个方法效率极低。

我的方法是记录下每一位的数字，最后输出这些个数字。如果有一位有两个不同的数，则是无解。

对于没有规定的，能填 $0$ 就填 $0$ ，如果不能填 $0$ （比如 $?01$ 中的 $?$）则填 $1$ 。



------------
下面是代码。 $s$ 数组记录这一位是否填过数， $c$ 数组记录每一位填的数。

```cpp
#include<stdio.h>
int s[10], c[10], n, m;
int main() {
    int i, ss, cc;
    scanf("%d%d", &n, &m);
    for(i = 1; i <= m; ++i) { //输入每一个要求。一边输入就一边处理。
        scanf("%d%d", &ss, &cc);
        if(s[ss]) { //这一位已经填过
            if(c[ss] != cc) { //而且填过的数和现在读入的不同，
                printf("-1\n"); //这样一个位置要填两个数，出现错误。
                return 0; //直接报错。记得换行！
            }
        }
        if(ss == 1 && cc == 0 && n != 1) { //第一位填0，不符合要求。
            printf("-1\n"); //n的特判是防止只有一位0的被判错[1]。
            return 0; 
        }
        s[ss] = 1; //将这一位记为已经出现过
        c[ss] = cc; //记录填的数
    }
    for(i = 1; i <= n; ++i) {
        if(s[i]) printf("%d", c[i]); //这一位填过
        else if(i != 1 || n == 1) printf("0"); //这一位没填过，且不是第一位[2]。
        else printf("1"); //第一位只能填1
    }
    puts(""); //别忘了！
    return 0;
}
```

注释：

【1】这里若写 
```cpp
if(ss == 1 && cc == 0) {
            printf("-1\n"); 
            return 0; 
}
```
对于```1 1  1 0```的输出是 ```-1``` ，但是此数据答案是 ```0``` 。


------------
【2】这里若写
```cpp
 else if(i != 1) printf("0")
```
对于 ```1 0``` 的输出是 ```1``` ，但答案是 ```0``` 。



------------
### 完结

---


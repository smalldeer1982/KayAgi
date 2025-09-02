# Lock

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2014-china-open/tasks/code_festival_china_a



## 说明/提示

### Problem

Alice has a box locked with $ n $ digits dial lock. Each dial of the lock can be set to a digit from $ 0 $ to $ 9 $. Unfortunately, she forgot the passcode (of $ n $ digits). Now she will try all possible combinations of digits to unlock the key.

She can do one of the following procedure each time.

- Choose $ 1 $ dial and add $ 1 $ to that digit. (If the digit chosen was $ 9 $, it will be $ 0 $).
- Choose $ 1 $ dial and subtract $ 1 $ from that digit. (If the digit chosen was $ 0 $, it will be $ 9 $).

Curiously, she wants to try all combinations even if she found the correct passcode during the trials. But it is a hard work to try all the $ 10^n $ combinations. Help her by showing the way how to make the procedure less as possible.

Initially, the combination of digits of the lock is set to $ 00..0 $.

Calculate $ m $, the minimum number of procedures to try all combinations of digits, and show the $ m+1 $ combinations of digits after each procedures, including the initial combination $ 00..0 $. If there are more than one possible answer, you may choose any one of them.

Checking if the current combination of digits matches the passcode doesn't count as a procedure.

### Sample Explanation 1

Don't forget to output the minimum number of procedures $ 9 $ on the first line. On the following lines, note that you have to output $ m+1 $ lines including the initial combination $ 0 $.

## 样例 #1

### 输入

```
1```

### 输出

```
9
0
1
2
3
4
5
6
7
8
9```

## 样例 #2

### 输入

```
2```

### 输出

```
99
00
01
02
03
04
05
06
07
08
09
19
18
17
16
15
14
13
12
11
10
20
21
22
23
24
25
26
27
28
29
39
38
37
36
35
34
33
32
31
30
40
41
42
43
44
45
46
47
48
49
59
58
57
56
55
54
53
52
51
50
60
61
62
63
64
65
66
67
68
69
79
78
77
76
75
74
73
72
71
70
80
81
82
83
84
85
86
87
88
89
99
98
97
96
95
94
93
92
91
90```

# 题解

## 作者：Dream__Sky (赞：4)

此题数据最大 $n=5$，用搜索可做。

分析数据可得：

当某一位是 $0$ 时，那么就从 $0$ 到 $9$ 枚举，即题目中的加 $1$ 操作。

当这一位从 $0$ 到 $9$ 的操作结束后，这一位下一次就进行题目中的减 $1$ 操作。

每次从低位往高位枚举，当低位一轮从 $0$ 到 $9$（从 $9$ 到 $1$）的操作结束后，就往更高一位操作。

本题还有一个问题，比较简单，问共有几个数。

找规律可得，答案为 $10^n-1$。

附代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s;
void dfs(int dep)//这里的搜索其实是从高位往下，但是道理是和我解释中一样的，读者可以自己理解一下
{
	if(dep==n)//边界条件，当n个数位都放好了，那么就输出
	{
		cout<<s<<endl;
		return;
	}
	
	if(s[dep]=='0')//当这一位是0，从0到9枚举
	{
		while(s[dep]<'9') 
			{dfs(dep+1);s[dep]++;}//枚举，并向下一位搜索
		dfs(dep+1);//由于最后s[dep]已经为9，只需要搜索，不必要再加了
	}
	else 
	{
		while(s[dep]>'0')
			{dfs(dep+1);s[dep]--;}//同理
		dfs(dep+1);
	}
}
int main()
{
	ios::sync_with_stdio(0);//IO优化
	cin>>n;
	for(int i=0;i<n;i++) s=s+'0';//初始化，第一个数为0
	cout<<pow(10,n)-1<<endl;//第一问答案
	dfs(0);//搜索
	return 0;
}

```




---

## 作者：A_grasser (赞：1)

## 题意简化

给出 $n$ 位数的排列，并使排列中相邻两个数只改变一位。

## 需要注意的地方

1. $n$ 很小，可以用较普通解法。

## 解法分析

$1 \le n \le 5$，意味着，深搜复活了。

首先求总总数很容易，规律一推就知道是 $10^n-1$ 个。

重点放在输出排列上，这里我们可以先搞一个字符串 $s$，并赋值上 $n$ 个零，以作为处理对象。

定义深搜框架，设 $x$ 为处理到第几位（从前往后），那么处理到第 $n$ 位时就结束（因为是字符串，所以不是第 $n+1$ 位）。之后是里面内容，也十分好想，分两种情况：

- 当 $s_x$ 为 $0$ 时，代表枚举这一位要从小到大枚举，那么就从 $0$ 到 $9$ 枚举，每设置一位就向下一层继续搜；

- 当 $s_x$ 为 $9$ 时，代表枚举这一位要从大到小枚举，那么就从 $9$ 到 $0$ 枚举，每设置一位也向下一层继续搜；

整体就是这个样子：

```cpp
void dfs(int x){
	if(x==n){//处理完成 
		cout<<s<<endl;
		return;
	}
	if(s[x]=='0'){//要从小到大处理 
		for(int i=0;i<=9;i++){
			s[x]='0'+i;
			dfs(x+1);
		}
	}
	else{//要从大到小处理 
		for(int i=9;i>=0;i--){
			s[x]='0'+i;
			dfs(x+1);
		}
	}
}
```

开始条件就是 `dfs(0);`。之后的内容也是特别好做，输入输出即可。

最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

```cpp
//已通过
#include<bits/stdc++.h>
//万能头文件
using namespace std;
string s;
int n;
void dfs(int x){
	if(x==n){//处理完成 
		cout<<s<<endl;
		return;
	}
	if(s[x]=='0'){//要从小到大处理 
		for(int i=0;i<=9;i++){
			s[x]='0'+i;
			dfs(x+1);
		}
	}
	else{//要从大到小处理 
		for(int i=9;i>=0;i--){
			s[x]='0'+i;
			dfs(x+1);
		}
	}
}
int main(){
	cin>>n;
	cout<<pow(10,n)-1<<endl;//总方案数 
	for(int i=1;i<=n;i++) s+='0';//初始化 
	dfs(0);
	return 0;
}
```

---

## 作者：wangqinyan (赞：1)

这题思路与代码实现其实都很简单。

# **题目思路**

这道题的数据范围很小，可以用简单的深搜来做。题目中的第一个问题很简单，因为有 $n$ 位，每个位置上都可能是 $0$ 到 $9$ 中的任意一个数。所以尝试的次数为 $10$ 的 $n$ 次方。还有个十分重要的点，见注意点。接下来，再来解决题目中第二个问题。因为由题意可知只能用加 $1$ 或减 $1$ 来改变尝试中的组合，所以不能每次末位加一，再往前进位。观察样例可知，改变尝试中的组合的方法是当要改变的位为 $0$ 时，一直执行题目中的加一操作，一直到 $9$ 为止。而当要改变的位为 $9$ 时，一直执行题目中的减一操作，一直到 $0$ 为止。当这个位置按以上方式执行完后，就在按同样的方式执行它的高位，也就是从低到高进行以上操作。这样，我们就完成了这道题。具体可见代码。

# **注意点**

尝试次数不包括全是 $0$ 的情况。

# **代码**
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,b=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')b=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*b;
}
inline void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10^48);
	return;
}
long long a[10],s,n;
void dfs(long long x)
{
	if(x>n)
	{
		for(int i=1;i<=n;i++)cout<<a[i];
		cout<<endl;
		return ;
	}
	if(a[x]!=0)
	{
		for(int i=9;i>=0;i--)
		{
			a[x]=i;
			dfs(x+1);
		}
	}
	else
	{
		for(int i=0;i<=9;i++)
		{
			a[x]=i;
			dfs(x+1);
		}
	}
}
int main()
{
//    freopen(".in","r",stdin);
//    freopen(".out","w",stdout);
	cin>>n;
	s=1;
	for(int i=1;i<=n;i++)s*=10;
	cout<<s-1<<endl;
	dfs(1);
//    fclose(stdin);
//    fclose(stdout);
	return 0;
}


 
```
感谢观看！

---

## 作者：Vegetableless (赞：1)

~~感觉像橙题？~~

我们考虑模拟调密码锁，可以发现，每当后一位没法继续往后（或往前）调时，也就是后一位为 $9$ 或 $0$ 时，这一次就调当前一位（即当前数字加减一）。那么思路就明了了，我们调密码锁的时候可以从低位往高位一个一个调，然后用一个布尔数组表示这一位是加一还是减一：

```cpp
bool vis[6];//记录每一位是要加一还是减一（从后往前，顺序颠倒）

inline void trying(int depth){//从低位向高位递归
	if(depth > n) return;//超过密码位数的，不用考虑
	if(!vis[depth]){//要加
		if(num[depth] == 9) vis[depth] = 1 , trying(depth + 1);//为 9 时，调高位
		else num[depth]++;
	}
	else {//要减
		if(num[depth] == 0) vis[depth] = 0 , trying(depth + 1);//为 0 时，调高位
		else num[depth]--;
	}
}
/*
说明一下，这里的顺序是颠倒的：
1 对应第 n 位
2 对应第 n-1 位
······
以此类推。
*/
```

这道题 $1 \le n \le 5$，有 $10^{n}$ 种不同的排列，时间复杂度就是 $O(10^{n})$ 的，完全可过。

接下来是完整代码：

```cpp
/*
By Vegetableless
*/
#include<bits/stdc++.h>
using namespace std;

int n , num[6] , m;

bool vis[6];

inline void trying(int depth){
	if(depth > n) return;
	if(!vis[depth]){
		if(num[depth] == 9) vis[depth] = 1 , trying(depth + 1);
		else num[depth]++;
	}
	else {
		if(num[depth] == 0) vis[depth] = 0 , trying(depth + 1);
		else num[depth]--;
	}
}

int main(){	
	cin >> n;
	
	m = 1;
	for(register int i = 1;i <= n;++i) m *= 10;
	m--;//因为不算全零的情况，所以实际一开始输出的是 10^n - 1
	
	for(register int i = 1;i <= n;++i) putchar('9');
	putchar(10);//注意换行
	
	for(register int i = 0;i <= m;++i){//一开始要输出全0的情况
		for(register int j = n;j;--j) putchar(num[j] + 48);
		putchar(10);
		trying(1);//从第 n 位开始调
	}
	return 0;
}//本题输出量略大，你可以关闭同步流，用 printf，或者像我一样用 putchar 等。
```


---

## 作者：Big_Dinosaur (赞：0)

#### 1.尝试次数
$n$ 位，每位可以是 $0\sim 9$，那么有 $10^n$ 种可能，全是零的要去除，所以答案为 $10^n-1$。
#### 2.如何尝试
考虑依次对每一位尝试。尝试时，若开始为 $9$，则从大到小枚举到 $0$，否则从小到大枚举到 $9$。每枚举一个，要在下一位枚举，下一位枚举完，再回到这一位。

用 DFS 即可。
```
#include<bits/stdc++.h>
using namespace std;
int n;
char c[8];
void dfs(int x) {
	if(x==n) {
		puts(c);
		return;
	}
	if(c[x]=='0') {
		while(c[x]<='9') {
			dfs(x+1);
			c[x]++;
		}
		c[x]--;
	} else {
		while(c[x]>='0') {
			dfs(x+1);
			c[x]--;
		}
		c[x]++;
	}
}
main() {
	cin>>n;
	memset(c,'0',sizeof(c));
	c[n]='\0';
	cout<<pow(10,n)-1<<endl;
	dfs(0);
}
```

---

## 作者：封禁用户 (赞：0)

读完题，不难发现，这与普通的全排列不同，他输出的顺序是不同的。于是，我就想到了第一种思路。我们先设一个哨兵，$sum$，再用一个 $b$ 数组，把数记录下来。刚开始 $sum$ 的值为 $0$，然后如果是双数，我们就正序存，反之倒序存。如果最后一个数为 $0$，$sum$ 就存为 $0$，反之就存为 $1$。

Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, n, b[1001], sum = 1;
bool p = 1;
void dfs(int k)
{
	if(k > n)
	{
		for(int i = 1; i <= n; i ++) cout << b[i];
		cout << endl;
		if(b[n] % 10 == 0) sum = 1;
		else sum = 0;
		return;
	}
	if(sum % 2) {
		for(int i = 0; i <= 9; i ++) 
		{
			b[k] = a[i];
			dfs(k + 1);
		}
	}
	else
	{
		for(int i = 9; i >= 0; i --) 
		{
			b[k] = a[i];
			dfs(k + 1);
		}
	}
//	cout << sum <<endl;
}
int main()
{
	cin >> n;
	cout << pow(10, n) - 1 <<endl; 
	dfs(1);
    return 0;
}
```

于是……

一片红色。

回头看题，我才发现每一位都得用这种规律。好，我就整整想了半个小时，还没想到方法，我就想到了一个暴力程序。及先特判，把 $n$ 大于三的情况每个都打一个暴力程序。

代码有点长，放这。

[Code](https://www.luogu.com.cn/paste/hgk2beac)

但不知为何还是全错。

~~但我就是气啊，这就是道黄题！~~

我就询问了机房巨佬，即第一篇题解的发布者。

重点来了！这题的思路其实很简单。我们用深搜来枚举每一位上的数。而且每一位只有搜过和没搜过两种状态。所以当前这位只有 $0$ 和 $9$ 两种情况。所以我们可以分两种情况讨论：如果是 $0$，那么我们就一直将他加到九，并且每次都深搜一次，因为他要输出所有情况。如果是 $1$，那么同理，我们就一直减到 $0$。每个位数都搜过了我们就输出。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100100];

void print() {for(int i = 1; i <= n ; i ++) cout << a[i];}
void Vegetabscdmg(int k)
{
	if(k>n) { print(); cout << endl; return;}
	if(! a[k])
	{
		while(a[k] < 9)  { Vegetabscdmg(k + 1); a[k] ++; }
		Vegetabscdmg(k + 1);
	}
	else 
	{
		while(a[k] > 0) { Vegetabscdmg(k + 1); a[k] --;}
		Vegetabscdmg(k + 1);
	}
}
int main()
{
	cin>>n;
	cout << pow(10, n) - 1 << "\n";
	Vegetabscdmg(1);
	return 0;
}
```

---

## 作者：The_jester_from_Lst (赞：0)

简易深搜题。

一眼像个全排列，可惜题面对输出顺序做出了要按尝试顺序的要求。那么我们看看尝试顺序：每次只能加一或减一。从这句话我们可以知道，每次枚举的顺序不是单纯的 $1$ 至 $9$，而是：

当当前的位上初值为 $1$，则枚举顺序为 $1$ 至 $9$。否则枚举顺序为 $9$ 至 $1$，这样我们的顺序就一定满足要求了，唯一的难点也解决了。


附上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int rd(){
	int jya=0,tl=1;char jyt=getchar();
	while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
	while(isdigit(jyt)){jya=jya*10+(jyt-'0');jyt=getchar();}
	return jya*tl;
}
inline void wr(int jjy){
	if(jjy<0)putchar('-'),jjy=-jjy;
	if(jjy>9)wr(jjy/10);
	putchar(jjy%10+48);
}
int n,m,a[6];
inline void dfs(int x){
	if(x>n){
		for(int i=1;i<=n;++i)putchar(a[i]+48);
		putchar('\n');
		return;
	}
	if(a[x]==0){
		for(int i=0;i<=9;++i){
			a[x]=i;
			dfs(x+1);
		}
	}
	else{
		for(int i=9;i>=0;--i){
			a[x]=i;
			dfs(x+1);
		}
	}
}
signed main(){
	n=rd();
	wr(pow(10,n)-1);
	putchar('\n');
	dfs(1);
	return 0;
}
```

---

## 作者：_Sky_Dream_ (赞：0)

# [传送门](https://www.luogu.com.cn/problem/AT_code_festival_china_a)

一题很有意思的深搜。不同于全排列，他要求按升降序来输出。

### Question1:要试多少次：

首先，有 $n$ 个空，每个空有 $0,1,2,3,4,5,6,7,8,9$ 这些数可以填上去。一共是 $10$ 个。这样的话，一共有 $10^n$ 种可能。但题目说了，全是零不算。所以我们要输出 $10^n-1$。

### Question2:怎么组合：

时间复杂度估一下 $O(10^n)$，而 $n \le 5$，不会超时，采用深搜。

1. 边界条件：填了 $n$ 个数；
2. 填数：如果是 $0$，向上填；如果是 $9$，向下填。

### 代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,s[6];
void dfs(int sum){
	if(sum>n){for(int i=1;i<=n;++i)cout<<s[i];cout<<endl;return;}//边界判断，由于sum从1开始算，所以sum>n才填完了
	else if(s[sum]==0)//向上填
		for(int i=0;i<=9;++i){//枚举所有可能
			s[sum]=i;
			dfs(sum+1);//填下一位
            //注意：这里不能回溯，这是下一位要向下填的标志
		}
	else//同理
		for(int i=9;i>=0;--i){
			s[sum]=i;
			dfs(sum+1);
            //注意：这里不能回溯，这是下一位要向上填的标志
		}
}
void Enchanted(){
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	memset(s,0,sizeof(s));
	cin>>n;
	int q=1;
	for(int i=1;i<=n;++i)q=q*10;//问题一
	cout<<q-1<<endl;//当然，采用pow（10，n）-1也一样
	dfs(1);//开始深搜
}
signed main(){Enchanted();}

```


附上我~~简短的~~超长的[打表代码](https://note.ms/iloveluogu)。


---


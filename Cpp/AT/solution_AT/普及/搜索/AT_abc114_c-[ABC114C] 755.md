# [ABC114C] 755

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc114/tasks/abc114_c

整数 $ N $ が与えられます。$ 1 $ 以上 $ N $ 以下の整数のうち、*七五三数* は何個あるでしょうか？

ここで、七五三数とは以下の条件を満たす正の整数です。

- 十進法で表記したとき、数字 `7`, `5`, `3` がそれぞれ $ 1 $ 回以上現れ、これら以外の数字は現れない。

## 说明/提示

### 制約

- $ 1\ \leq\ N $
- $ N $ は整数である。

### Sample Explanation 1

$ 575 $ 以下の七五三数は、$ 357,\ 375,\ 537,\ 573 $ の $ 4 $ 個です。

### Sample Explanation 2

$ 3600 $ 以下の七五三数は、上記の $ 4 $ 個と $ 735,\ 753,\ 3357,\ 3375,\ 3537,\ 3557,\ 3573,\ 3575,\ 3577 $ の計 $ 13 $ 個です。

## 样例 #1

### 输入

```
575```

### 输出

```
4```

## 样例 #2

### 输入

```
3600```

### 输出

```
13```

## 样例 #3

### 输入

```
999999999```

### 输出

```
26484```

# 题解

## 作者：phigy (赞：7)

### 法一

直接枚举 。

超时 。

### 法二

只能出现 $3,5,7$ 。

使用 BFS 。

BFS 即广度优先搜索 。

不同于 DFS 每次直接到搜索树的叶子 。

BFS 是一层一层的搜索。

例如

![](https://cdn.luogu.com.cn/upload/image_hosting/c7ztgrjm.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

BFS 就会按 $1,2,3,4,5,6,7$ 遍历 。

而 DFS 则会按 $1,2,4,5,3,6,7$ 的顺序遍历 。

实现的方法是用一个队列保存接下来要遍历的点 。

上图 BFS 方式：

将 $1$ 入队，当前队列 $1$ 。

队列中第一个是 $1$ 将 $1$ 弹出 $2,3$ 入队，当前队列 $2,3$ 。

队列中第一个是 $2$ 将 $2$ 弹出 $4,5$ 入队，当前队列 $3,4,5$ 。

队列中第一个是 $3$ 将 $3$ 弹出 $6,7$ 入队，当前队列 $4,5,6,7$ 。

队列中第一个是 $4$ 将 $4$ 弹出，当前队列 $5,6,7$ 。

队列中第一个是 $5$ 将 $5$ 弹出，当前队列 $6,7$ 。

队列中第一个是 $6$ 将 $6$ 弹出，当前队列 $7$ 。

队列中第一个是 $7$ 将 $7$ 弹出，当前队列为空 。

对列为空结束遍历 。

本题先将 $0$ 入队 。

每次检查是否 $3,5,7$ 各有一个且小于等于 $n$ 。

再将其 $\times10+3$ 和 $\times10+5$ 和 $\times10+7$ 入队。

可是依然超时 。

```cpp
#include <iostream>
#include <queue>

using namespace std;

queue<long long> q;

int n,ans;
int main()
{
    int i,j,k;
    cin>>n;
    q.push(0);
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        if(x>n)continue;
        int a[4]={0,0,0,0},y=x;
        while(y)
        {
            a[y%10/2]++;
            y/=10;
        }
        if(a[1]&&a[2]&&a[3])
        {
            ans++;
        }
        q.push(x*10+3);
        q.push(x*10+5);
        q.push(x*10+7);
    }
    cout<<ans;
    return 0;
}  
```
### 法三

多加入一个 $f[3]$ 来表示每个数 $3,5,7$ 个数 。

使用结构体将数值和 $f[3]$ 在队列中捆绑起来 。

省去检查时间 。

就可以过了 。

```cpp
#include <iostream>
#include <queue>

using namespace std;


struct number
{
    long long a;
    int f[4];
};
queue <number> q;

int n,ans;
int main()
{
    int i,j,k;
    cin>>n;
    number s;
    s.a=0;
    s.f[1]=0;
    s.f[2]=0;
    s.f[3]=0;
    q.push(s);
    while(!q.empty())
    {
        number x=q.front();
        q.pop();
        if(x.a>n)continue;
        
        if(x.f[1]&&x.f[2]&&x.f[3])
        {
            ans++;
        }
        number pig;
        pig.f[1]=x.f[1];
        pig.f[2]=x.f[2];
        pig.f[3]=x.f[3];

        pig.a=x.a*10+3;
        pig.f[1]++;
        q.push(pig);
        pig.f[1]--;
        pig.a+=2;
        pig.f[2]++;
        q.push(pig);
        pig.f[2]--;
        pig.a+=2;
        pig.f[3]++;
        q.push(pig);
    }
    cout<<ans;
    return 0;
}  
```

### 法四

数位DP 。

$dp[i][1]$ 表示只有且至少有一个 $3$ 的 $i$ 位数个数 。

$dp[i][2]$ 表示只有且至少有一个 $5$ 的 $i$ 位数个数 。

$dp[i][3]$ 表示只有且至少有一个 $3,5$ 的 $i$ 位数个数 。

$dp[i][4]$ 表示只有且至少有一个 $7$ 的 $i$ 位数个数 。

$dp[i][5]$ 表示只有且至少有一个 $3,7$ 的 $i$ 位数个数 。

$dp[i][6]$ 表示只有且至少有一个 $5,7$ 的 $i$ 位数个数 。

$dp[i][7]$ 表示只有且至少有一个 $3,5,7$ 的 $i$ 位数个数 。

不考虑边界转移如下：

$dp[i][1]=dp[i-1][1] ,$ 

$dp[i][2]=dp[i-1][2],$

$dp[i][3]=dp[i-1][1]+dp[i-1][2]+2\times dp[i-1][3],$

$dp[i][4]=dp[i-1][4],$

$dp[i][5]=dp[i-1][1]+dp[i-1][4]+2\times dp[i-1][5],$

$dp[i][6]=dp[i-1][2]+dp[i-1][4]+2\times dp[i-1][6],$

$dp[i][7]=dp[i-1][3]+dp[i-1][5]+dp[i-1][6]+3\times dp[i-1][7].$

可以使用记忆化搜索来处理边界 。

时间复杂度 $O(logn)$ 。

### 法五

如果说题目变成求 $10^n$以内的  _Shichi-Go-San_ 数个数 。

并且 $n<=10^9$ 。

朴素数位的 DP 也过不了 。

使用矩阵快速幂来加速 。

构造出来的转移矩阵长这样：

$
\begin{vmatrix}
1 & 0 & 0 & 0 & 0 & 0 & 0\\ 
0 & 1 & 0 & 0 & 0 & 0 & 0\\ 
1 & 1 & 2 & 0 & 0 & 0 & 0\\ 
0 & 0 & 0 & 1 & 0 & 0 & 0\\ 
1 & 0 & 0 & 1 & 2 & 0 & 0\\ 
0 & 1 & 0 & 1 & 0 & 2 & 0\\ 
0 & 0 & 1 & 0 & 1 & 1 & 3
\end{vmatrix}
$

复杂度 $O(logn)$ 。

对于原题是 $O(loglogn)$ 。

只是无法处理边界 。

---

## 作者：XWCL_OI (赞：2)

思路：

使用 `BFS` 函数，并定义三个变量，分别代表 $7$、$5$、$3$ 的个数，并使用 `ans` 来设定为总个数的计数器，随后定义一个变量 $x$ 表示为当前的数即可。

**注意：$x$ 要开 `long long`！**

code：

```
#include<bits/stdc++.h>
using namespace std;
long long n,cnt=0,ans;
void dfs(long long x,int a,int b,int c)
{
	if(x>n)
	{
		return;
	}
	ans+=a&&b&&c;
	dfs(x*10+3,a+1,b,c);
	dfs(x*10+5,a,b+1,c);
	dfs(x*10+7,a,b,c+1);
	
}
int main()
{
	cin>>n;
	dfs(0,0,0,0);
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：_shine_ (赞：1)

## 题目大意
有一个整数 $n$，现在请问你，在小于整数 $n$ 中，有多少个数满足不含 $7$ 和 $5$ 或 $3$ 外的数字，并且，整几个数字至少出现一次。
## 思路
我们可以发现，这道题只需要从零开始进行爆搜，使得每一次都只包含 $7,5,3$ 这几个数，因为题目要求，并且数位一定 $\le 20$（因为数位也就只有这么多），之后就是对于每一次爆搜，都判断里面是否存在这几个数，如果有，说明找到了，答案加上就可以了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
    while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;ch=getchar();
	}
    while(ch>='0'&&ch<='9'){
    	s=s*10+ch-'0';
		ch=getchar();
	} 
    return s*w;
}
inline void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)write(x/10);
    putchar(x % 10 + '0');
}// 快读，可以忽略。
int n,ans;
void dfs(int f,int a,int b,int c){
	if(f>n){
		return ;
	}else{
		if(a==b && b==c && c==1)ans++;
		dfs(f*10+3,1,b,c);
		dfs(f*10+5,a,1,c);
		dfs(f*10+7,a,b,1);
	}
}// a代表是否出现3，b代表是否出现5，c代表是否出现7
signed main(){
	n=read();
	dfs(0,0,0,0);
	write(ans);
	return 0;
} 
```
### [AC记录](https://www.luogu.com.cn/record/list?pid=AT_abc114_c&user=525141)

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc114_c)      
简单 dfs。           
考虑到最多只有 $9$ 位，所以我们直接 dfs 搜即可。             
首先，我们需要写一个 check 函数，用于判断数字是否合法：     
```cpp
int b[10]={0,0,0,0,0,1,0,2};
inline bool check(int x){
	bool flag=(x<=n)&&(x>=1);
	int cnt=0;
	while(x){
		cnt|=(1<<b[x%10]);
		x/=10;
	}
	return cnt==7&&flag;
}
```
其中 $b$ 是给状压用的，$b_3$、$b_5$ 和 $b_7$ 是状压时移动的位数。         
之后，dfs 我们用长度和数字两个值就可以得到答案了。      
[CODE](https://www.luogu.com.cn/paste/2cxg7mo6)

---

## 作者：Leaves_xw (赞：0)

一道递归题。

**大意：**

你有一个整数 $N$。在 $1$ 到 $N$（含）之间的整数中，有多少个七五三数？

七五三数是满足以下条件的正整数：

* 用十进制数写数字时，数字`7`、`5`和`3`至少出现一次，而其他数字从不出现。


**思路：**

定义一个`void`函数，使用递归参数对`3`、`5`、`7`分别进行递归，所代表的计数器累加，当所判断的数大于 $N$ 的时候返回即可。


**代码：**
```
#include<bits/stdc++.h>
using namespace std;
int n,ans,plan[32];//定义变量
void dfs(int step,int cnt3,int cnt5,int cnt7,long long num)//递归函数
{//num乘10+7后可能会超int,所以使用long long
    if(num>n)return;//如果所判断的数大于n了，则返回
    if(cnt3>0&&cnt5>0&&cnt7>0)ans++;//总计数器累加
    plan[step]=3;
    dfs(step+1,cnt3+1,cnt5,cnt7,num*10+3);//递归有关3的数
    plan[step]=5;
    dfs(step+1,cnt3,cnt5+1,cnt7,num*10+5);//递归有关5的数
    plan[step]=7;
    dfs(step+1,cnt3,cnt5,cnt7+1,num*10+7);//递归有关7的数
}
int main()
{
    scanf("%d",&n);
    dfs(1,0,0,0,0);//除了步数从1开始，其他的都为0
    cout<<ans<<endl;//输计数术器
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/97155534)


---

## 作者：JustinXiaoJunyang (赞：0)

思路分析：

本文就管这些数叫七五三数。

这道题的数据范围不大，可以直接深搜。参数除还要判断三个数字是否出现过。每次都判断是否为七五三数，超出范围就结束。如果都满足条件了就可以让计数器自增。

这里直接对数进行拼接就可以了。

但要注意拼接时要开 `long long`。

参考代码：

```cpp
#include <iostream>
using namespace std;

int n, cnt = 0;
void dfs(long long x, bool f1, bool f2, bool f3)
{
    if (x > n) return; 
    if (x <= n && f1 && f2 && f3) cnt++;
    dfs(x * 10 + 3, true, f2, f3);
    dfs(x * 10 + 5, f1, true, f3);
    dfs(x * 10 + 7, f1, f2, true);
}

int main()
{
    cin >> n;
    dfs(0, false, false, false);
    cout << cnt << endl;
    return 0;
}
```

---

## 作者：liangbowen (赞：0)


小学生又来写题解啦！

容易想到，范围内**七五三数不会很多**，因此尝试**暴力搜索**，即**深搜**。

参数除了当前的数外，还有三个布尔类型的变量分别表示三、五、七有无出现。

每次都判断是否为七五三数即可，超出范围才跳出。

对了，还有一个**魔鬼细节**，在代码中会提到。

## 满分代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int cnt, n;
void dfs(long long x, bool use3, bool use5, bool use7)
//魔鬼细节来啦！
//看到上面的 long long 没有？
{
	if (x > n) return; 
	if (x <= n && use3 && use5 && use7) cnt++;  //判断一下，注意此时不用跳出。 
	dfs(x * 10 + 3, true, use5, use7); //补个 3。 
	dfs(x * 10 + 5, use3, true, use7); //补个 5。 
	dfs(x * 10 + 7, use3, use5, true); //补个 7。 
}
int main()
{
	scanf("%d", &n);
	dfs(0, false, false, false);
	printf("%d", cnt);
	return 0;
}
```

---

## 作者：BotDand (赞：0)

# $\text{Problems}$

求 $1$ 到 $n$ 中有多少数满足：由数字 `3,5,7` 组成，且 `3,5,7` 都至少出现 $1$ 次。

# $\text{Answer}$

建立一个搜索树，只包含 `3,5,7`，定义其根节点为 $0$，即从 $0$ 开始搜索，如下图。

![](https://z3.ax1x.com/2021/08/17/f5xK8H.png)

然后遍历这棵树即可。

判断是否符合要求可以用另一个变量 $\text{num}$ 储存，用二进制 $\text{000}$ 表示 `3,5,7` 都没有，$\text{001}$ 表示有 `3`，$\text{010}$ 表示有 `5`，$\text{100}$ 表示有 `7`，以此类推。

# $\text{Code}$

BFS

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct arr
{
    int n,num;
};
int n;
queue<arr> q;
arr x,y;
int ans;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline void print(int x)
{
    write(x);
    putchar('\n');
}
signed main()
{
    n=read();
    y.n=0;y.num=0;
    q.push(y);
    while(!q.empty())
    {
        x=q.front();
        q.pop();
        if(x.n>n) continue;
        if(x.num==7) ans++;
        y.n=x.n*10+3;y.num=x.num|1;
        q.push(y);
        y.n=x.n*10+5;y.num=x.num|2;
        q.push(y);
        y.n=x.n*10+7;y.num=x.num|4;
        q.push(y);
    }
    print(ans);
    return 0;
}
```

DFS

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int ans;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline void print(int x)
{
    write(x);
    putchar('\n');
}
void dfs(int x,int num)
{
    if(x>n) return;
    if(num==7) ans++;
    dfs(x*10+3,num|1);
    dfs(x*10+5,num|2);
    dfs(x*10+7,num|4);
}
signed main()
{
    n=read();
    dfs(0,0);
    print(ans);
    return 0;
}
```


---

## 作者：high_sky (赞：0)

既然只有 $3,5,7$ 组成，那么只需要枚举每个位为 $3,5,7$ 就行了，设 $x$ 为 $n$ 的位数最多枚举 $3^x$ 次，用一个 `dfs` 搜索就行了

```cpp
#include<iostream>
#define int long long
using namespace std;
int n, ans;
void dfs(int x, int f) { 
	if (x > n) return;
	if (f == 7) ans++; 
	dfs(x * 10 + 3,f | 4); 
	dfs(x * 10 + 5,f | 2); 
	dfs(x * 10 + 7,f | 1); 
}
signed main() {
   cin>>n;
   dfs(0,0);
	cout << ans;
	return 0;
}
```
有人可能要问 `f` 是干嘛的？其实他是用来判断是否 $3,5,7$ 全在里面

---

## 作者：yaolibo (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT4276)  
## 题意解释：
问在不超过 $n$ 的正整数中，只由若干个 $3,5,7$ 组成的数的个数。  
例如：$35753$ 是符合要求的数，$35743$ 就不是符合要求的数。
## 思路 & 方法：
本题 $n$ 的范围较大，使用 $\Theta(n)$ 算法将每个数都遍历一遍显然不行，故我们换个思路，不妨通过一些方式去构造所有符合要求的数。  
有一个显然的事实：**在一个符合要求的数的任意一位插入 $3,5,7$ 当中的一个数字，这个数字也是符合要求的。**  
因此，我们可以利用这个事实，不停的在数后面加上 $3,5,7$，最后判断一下此数是否集齐了 $3,5,7$ 三个数字就可以累加答案了。此过程可以用递归实现，其中在判断累加的时候使用到了位运算的知识。  
具体操作见代码注释。

------------
`Solve` 函数中的 $x$ 代表当前构造的这个数字，$cnt$ 可看为一个三位的二进制数，各位分别表示 $3,5,7$ 是否在 $x$ 中出现，$1$ 表示出现过，$0$ 表示没出现过。  
主函数中调用 `Solve` 时 $x$ 在一开始用 $0$ 表示。不难看出，$x$ 的各位中永远不会存在除 $3,5,7$ 外其他的数，故只需判断 $3,5,7$ 是否全部存在即可。
### 核心代码
```cpp
#define LL long long
int n, ans;
inline void Solve(LL x, int cnt) { 
	if (x > n) return;
	if (cnt == 7) ans++; // 即cnt在二进制下为111，说明3,5,7均在x中出现过
	Solve(x * 10 + 3, cnt | 4); // 4在二进制下为100，cnt|4意为将cnt的左数第1位变成1， 以下类似
	Solve(x * 10 + 5, cnt | 2); // 2在二进制下为010
	Solve(x * 10 + 7, cnt | 1); // 1在二进制下为001
	// 递归，每次在x的末尾加上3,5,7
	return;
}
int main() {
	n = Read();
	Solve(0, 0);
	cout << ans;
	return 0;
}
```
### 结束~Over~


---


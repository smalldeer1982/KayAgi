# Multiply by 2, divide by 6

## 题目描述

You are given an integer $ n $ . In one move, you can either multiply $ n $ by two or divide $ n $ by $ 6 $ (if it is divisible by $ 6 $ without the remainder).

Your task is to find the minimum number of moves needed to obtain $ 1 $ from $ n $ or determine if it's impossible to do that.

You have to answer $ t $ independent test cases.

## 说明/提示

Consider the sixth test case of the example. The answer can be obtained by the following sequence of moves from the given integer $ 15116544 $ :

1. Divide by $ 6 $ and get $ 2519424 $ ;
2. divide by $ 6 $ and get $ 419904 $ ;
3. divide by $ 6 $ and get $ 69984 $ ;
4. divide by $ 6 $ and get $ 11664 $ ;
5. multiply by $ 2 $ and get $ 23328 $ ;
6. divide by $ 6 $ and get $ 3888 $ ;
7. divide by $ 6 $ and get $ 648 $ ;
8. divide by $ 6 $ and get $ 108 $ ;
9. multiply by $ 2 $ and get $ 216 $ ;
10. divide by $ 6 $ and get $ 36 $ ;
11. divide by $ 6 $ and get $ 6 $ ;
12. divide by $ 6 $ and get $ 1 $ .

## 样例 #1

### 输入

```
7
1
2
3
12
12345
15116544
387420489```

### 输出

```
0
-1
2
-1
-1
12
36```

# 题解

## 作者：江户川·萝卜 (赞：6)

## [CF1374B Multiply by 2, divide by 6](https://www.luogu.com.cn/problem/CF1374B) 题解
此题我的思路感觉跟题解区中不同。

我的思路就是：

因为只有 $/6$ 才是能得到 $1$ 的关键，没有 $/6$ 整个数字就不会下降到 $1$ 。

我们考虑怎样才能使数字被 $6$ 整除。而 $6=2*3$

$2$ 可以通过 $*2$ 来得到（或者数字本身给出），但是 $3$ 必须由数字本身给出。

可以得到以下步骤：

1. 判断该数是否被 $3$ 整除，不能整除则跳出循环输出 $-1$ ，否则进行下一步。
2. 判断该数是否被 $2$ 整除：
	- 是： $\text{step}+1$ ，$n$ 变成 $n/6$。（$\text{step}$ 即操作次数）
    - 否： $\text{step}+2$ ，$n$ 变成 $n/3$。（$\text{step}+2$ 是因为需要 $*2 /6$ 两个步骤）
3. 判断该数是否为 $1$ ，是 $1$ 则跳出循环输出 $\text{step}$，否则执行第一步。

这样就能写出代码啦~

### Code:
```cpp
#include<cstdio>
int t,n,step;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        step=0;
        while(n%3==0){
            if(n%2==0) step++,n/=6;
            else step+=2,n/=3;
        }
        if(n>1) printf("-1\n");
        else printf("%d\n",step);
    }
    return 0;
}
```


---

## 作者：_cmh (赞：5)

~~再不写题解咕值就没了~~

众所周知，$6=2\times3$，所以呢 ~~（所以啥呢，你倒是说啊）~~ ……

题目让我们每次可以将 $n\div2$ 或 $n\times6$，又因 $6=2\times3$，得出： $n$ 每次 $\div\ 6$ 只需一步，而若不满足，则可以尝试每次 $\times2\div6$，即 $\div\ 3$，共 $2$ 步。最后判断 $n$ 是否等于 $1$ ，输出答案即可。

上代码！（多组数据）


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
int T,n; 
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		int ans=0;
		while(n%6==0) ans++,n/=6;
		while(n%3==0) ans+=2,n/=3;
		if(n==1) cout<<ans<<endl;
		else cout<<"-1\n";
	}
    return 0;
}
```

~~无耻求赞~~

---

## 作者：xixike (赞：2)

upd：修改了**乘**和**除以**，感谢the_tool_er大佬的提醒

**题目大意**：

给你一个 $n$，你只能对 $n$ 进行两种操作：
1. **乘2**
2. **除以6**（能除尽的情况下）

要求你计算出最少需要进行多少次操作，使得 $n=1$，如果可以，则输出最少需要多少次；如果无法使 $n=1$，则输出 $-1$。

**题解**：

~~也是很水的一道题~~

我们只需求出 $n$ 中有多少个 $2$，以及有多少个因子 $3$。

1. 如果 $n$ 除了质因子 $2$ 和 $3$ 以外还有别的质因子，直接输出 $-1$。
2. 如果 $2$ 的个数多于 $3$ 的个数，直接输出 $-1$。因为如果 $2$ 的个数大于 $3$ 的个数，则无论如何也凑不出一个数，使得这个数能被 $6$ 整除。
3. 如果 $2$ 的个数少于 $3$ 的个数，则输出 $sum_2+2×(sum_3-sum_2)$。
	
    证明③：我们要把 $n$ 变成 $1$，就一定要用除以 $6$，我们先尽可能的把 $6$ 除掉，也就是 $sum_2$ 个，对于余下的 $3$ 的个数我们要先补上 $sum_3-sum_2$ 个 $2$，然后再除以 $sum_3-sum_2$ 个 $6$，因此操作次数为 $sum_2+2×(sum_3-sum_2)$。

**附代码**：
```
#include<iostream>
#include<cstdio>

using namespace std;

int tmp;

int get_yinzi(int p){
	int res=0;
	while(tmp%p==0){
		res++;
		tmp/=p;
	}
	return res;
}

int main(){
	int t,n;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		tmp=n;
		int x2=get_yinzi(2);
		int x3=get_yinzi(3);
		if(x2>x3||tmp!=1){
			printf("-1\n");
			continue;
		}
		printf("%d\n",x2+2*(x3-x2));
	}
	return 0;
}
```


---

## 作者：B_lhx (赞：2)

[CF1374B Multiply by 2, divide by 6](https://www.luogu.com.cn/problem/CF1374B)
==

**前置芝士：小学数学**


**思路：**2只有一个质因子2，6有两个质因子3和2，如果给定数字2的质因子和3的一样多，那就输出拥有2的质因子个数，否则要补2,乘2除3是两步，所以要补2乘(包含3的质因子个数-包含2的质因子个数），所以列出了如下式子

```
two+2*(three-two)
```
**然后就可以做了，代码如下：**


```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;//变量t
	cin>>t;//t组数据
	while(t--){//t次循环
		int n,two=0,three=0,nc;//分别为输入数字，2的个数，3的个数和n的备份
		cin>>n;//输入n
		nc=n;//备份
		while(nc%2==0){//如果数字中2的因子没有取光
			nc/=2;//除以2
			two++;//2的计数器++
		}
		while(nc%3==0){//3和2一样操作，如果数字中3的因子没有取光
			nc/=3;//除以3
			three++;//3的计数器++
		}
		if(nc>1||two>three){//如果还有别的因子或者3数量太少（只能*2）
			cout<<-1<<endl;//输出-1
		}else{//如果可以计算
			cout<<two+2*(three-two)<<endl;//3的个数多，每个2都得除以6消掉，然后3先和2抵消一部分再用*2/6抵消剩下的
		}
	}
    return 0;
}
```


---

## 作者：Tarsal (赞：1)

~~维持咕值，被迫营业。~~

### 题意

给你一个整数 $n$。

每次操作可以把 $n \to n * 2$ 或者 $n \to n / 6$

第二种必须满足 $n$ 是 $6$ 的倍数。

### 题解

考虑 $n$ 的因子。

因为操作二只可以抵消因子 $2$ 或 $3$。

如果有除了 $2$ 或 $3$ 的其他因子，那么直接 $puts("-1");$

然后如果 $2$ 的因子个数大于 $3$ 也直接 $puts("-1");$

最后就是合法的了，因为 $2$ 需要去补 $3$ 多出来的，所有两者的差值需要乘二。

假设 $num$ 是 $2$ 的因子个数，$sum$ 是 $3$ 的因子个数，那么就只要 $printf("%d\n", num + (sum - num) * 2);$

### 代码

```
// #include <iostream>
// #include <cstdio>
// #include <algorithm>
// #include <cstring>
// #include <vector>
#include <bits/stdc++.h>
#define maxn 100001
#define ls x << 1
#define rs x << 1 | 1
#define inf 0x3f3f3f3f
#define inc(i) (++ (i))
#define dec(i) (-- (i))
#define mid ((l + r) >> 1)
// #define int long long
#define XRZ 1000000003
#define debug() puts("XRZ TXDY");
#define mem(i, x) memset(i, x, sizeof(i));
#define Next(i, u) for(register int i = head[u]; i ; i = e[i].nxt)
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout);
#define Rep(i, a, b) for(register int i = (a) , i##Limit = (b) ; i <= i##Limit ; inc(i))
#define Dep(i, a, b) for(register int i = (a) , i##Limit = (b) ; i >= i##Limit ; dec(i))
int dx[10] = {1, -1, 0, 0};
int dy[10] = {0, 0, 1, -1};
using namespace std;
inline int read() {
    register int x = 0, f = 1; register char c = getchar();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
} long long Ans; int a[maxn];//, head[maxn];
priority_queue<int> Q[maxn]; vector<int> s, qwq[maxn];
// struct node { int nxt, to;} e[maxn << 1];
// void add(int x, int y) { e[inc(cnt)] = (node) {head[x], y}; head[x] = cnt;}
void merge(int x, int y) {
	if(Q[x].size() < Q[y].size()) swap(Q[x], Q[y]);
	while(Q[y].size()) {
		s.push_back(max(Q[x].top(), Q[y].top()));
		Q[x].pop(), Q[y].pop();
	} while(s.size()) Q[x].push(s.back()), s.pop_back();
}
void Dfs(int x) {
	// Next(i, x) { int v = e[i].to; Dfs(v); merge(x, v);}
	Rep(i, 0, qwq[x].size() - 1) Dfs(qwq[x][i]), merge(x, qwq[x][i]);
	Q[x].push(a[x]);
}
signed main() { int t = read();
	while(t --) { int n = read(), num = 0, sum = 0;
		while(n % 2 == 0) n /= 2, num ++;
		while(n % 3 == 0) n /= 3, sum ++;
		if(n != 1) puts("-1");
		else if(num > sum) puts("-1");
		else printf("%d\n", num + (sum - num) * 2);
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

# 题面描述

给你$n$，请你将$n$乘$2$或除$6$，请问你至少要多少次才可以将$n$变成$1$。若可以，输出至少多少次，若不行，输出$-1$。你要完成$t$组数据。

# 分析
首先，假设我们乘$a$个$2$，除$b$个$6$，那么$n=b*6/max(a*2,1)$。

所以，我们可以分析出若不满足以下两个条件，输出$-1$：

1）$n$必须只有$3$或$2$两个因子。

2）因为哪怕$a=0$，$n$的$2$因子数也不会大于$3$的因子数。

满足两个条件的情况下，输出$3$因子数（$b$次操作）+$3$的因子数-$2$的因子数（$a$次操作）。

# 代码

```

#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int t;//多测
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int iner3=0,iner2=0;//因子3的数量，因子2的数量
		while(n%3==0){//计算3因子
			iner3++;
			n/=3;
		}
		while(n%2==0){//计算2因子
			iner2++;
			n/=2;
		}
		if(n!=1){//有其他因子
			cout<<-1;
		}
		else if(iner2>iner3){//2因子比3因子多
			cout<<-1;
		}
		else{//正常情况
			cout<<iner3*2-iner2;
		}
		cout<<endl;
	}
	return 0;
}


```

---

## 作者：hensier (赞：0)

看到题解区里大多数方法类似，代码效率极高。~~而本蒟蒻的代码却稳稳地垫底【最优解】。~~

既然是要求最小步数，不妨进行$\text{BFS}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int f(int x)
{
    int q[100001][2]={},front=1,rear=1;
    //队列元素开10万个，头尾指针都为1（当然0也可以）
    map<int,bool>vis;//如果用bool数组要开1e9个下标，会有很多空间浪费，肯定会MLE（在CF中是RE）
    q[1][0]=x;//首先对队列第一个元素进行赋值，表示BFS的初始数字
    while(front<=rear)
    {
        int a=q[front][0],s=q[front][1];//a表示当前的数，s为上一次的步数
        if(a==1)return s;//BFS=最优解——一旦a等于1就返回步数
        if(a%6==0&&!vis[a/6])//如果a能够被6整除并且a/6未被访问过就继续拓展
        {
            vis[a/6]=true;
            q[++rear][0]=a/6;
            q[rear][1]=s+1;
            /*
            入队操作：
            1、标记访问
            2、尾指针+1
            3、在尾指针处进行赋值
            */
        }
        if(!vis[a<<1]&&a<=5e8)
        {
            /*
            注意a<=5e8的用途！
            如果一个数为5e8，那么乘2后变为1e9，继续乘下去的话很快就会溢出然后死循环，所以只有a在可控范围之内才能继续拓展。
            */
            vis[a<<1]=true;
            q[++rear][0]=a<<1;
            q[rear][1]=s+1;
        }
        front++;//头元素拓展完毕后出队
    }
    return -1;//没有达到1就返回-1
}
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int main()
{
    t=read();
    while(t--)printf("%d\n",f(read()));
    return 0;
}
```

---

## 作者：45dino (赞：0)

这是签到题的第二题。

因为要把一个正整数变成 $1$ ，所以只考虑除法

容易看出，$\times 2/6$ 相当于 $/3$ 。

所以可以构造出除以 $3$ （两步）和除以 $6$（一步）。

然后就出来了。

显而易见，符合如下任意一种情况会输出 $-1$ ：
- n有除 $2$ 和 $3$ 的质因子。
- n的 $2$ 因子的个数大于 $3$ 因子的个数。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		int a=0,b=0;
		while(n%2==0)
		{
			a++;
			n/=2;
		}
		while(n%3==0)
		{
			b++;
			n/=3;
		}
		if(n!=1||a>b)
			puts("-1");
		else
			cout<<b*2-a<<endl; 
	}
	return 0;
}
```


---

## 作者：Clouder (赞：0)

给定 $n$，可以 $\div 6$ 或 $\times 2$，问几步后可得到 $1$。  

顺序不会影响答案，若答案存在，则 $n \div 6^a \times 2^b = 1$，求 $a + b$。  

化简为 $n \div 6^{a-b} \div 3^b = 1$，$\times 2 \div 6 = \div 3$ 计算两步贡献，直接统计。    

```cpp
#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int T;
long long x;
int main()
{
    read(T);
    while(T--)
    {
        read(x);
        long long ans = 0;
        while(x % 6 == 0) ++ans, x /= 6;
        while(x % 3 == 0) ans += 2,x /= 3;
        if(x == 1) printf("%lld\n",ans);
        else puts("-1");
    }
    return 0;
}
```

---

## 作者：PanH (赞：0)

## 题意
给你一个数 $n$ ，每一步你可以对它除 $6$（要整除） 或者乘 $2$ ，问你可不可以把它变成 $1$ 。可以则输出最小步数，不可以就输出 $-1$ 。

## 做法

显然要让这个数变小，那么只有多除一点 $6$ 。先除完能除的 $6$ ，再除能除的 $3$ ，因为它乘 $2$ 就是 $6$ 了，但要花费两步。

若剩下还大于 $1$ ，那我们就无能为力了。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int x,tot3=0,ans=0;
		cin>>x;
		while(x%6==0)	x/=6,ans++;
		while(x%3==0)	x/=3,tot3++;
		if(x>1)	puts("-1");
		else	cout<<ans+tot3*2<<endl;
	}
}
```


---


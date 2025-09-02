# Game 23

## 题目描述

Polycarp plays "Game 23". Initially he has a number $ n $ and his goal is to transform it to $ m $ . In one move, he can multiply $ n $ by $ 2 $ or multiply $ n $ by $ 3 $ . He can perform any number of moves.

Print the number of moves needed to transform $ n $ to $ m $ . Print -1 if it is impossible to do so.

It is easy to prove that any way to transform $ n $ to $ m $ contains the same number of moves (i.e. number of moves doesn't depend on the way of transformation).

## 说明/提示

In the first example, the possible sequence of moves is: $ 120 \rightarrow 240 \rightarrow 720 \rightarrow 1440 \rightarrow 4320 \rightarrow 12960 \rightarrow 25920 \rightarrow 51840. $ The are $ 7 $ steps in total.

In the second example, no moves are needed. Thus, the answer is $ 0 $ .

In the third example, it is impossible to transform $ 48 $ to $ 72 $ .

## 样例 #1

### 输入

```
120 51840
```

### 输出

```
7
```

## 样例 #2

### 输入

```
42 42
```

### 输出

```
0
```

## 样例 #3

### 输入

```
48 72
```

### 输出

```
-1
```

# 题解

## 作者：yuzhechuan (赞：4)

入门难度的一道题，题意也很直白，毕竟是div3的A啊。。。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b;
int main(){
	scanf("%d%d",&a,&b);
	if(b%a!=0){
		printf("-1"); //假如后者无法除尽前者，那么怎样乘都不可能实现，直接输-1
		return 0;
	}
	b/=a; //（省点内存）除得两者相差的倍数
	a=0;
    /*下面类似分解质因数*/
	while(b%2==0) b/=2,a++; //除去b因数中所有的2
	while(b%3==0) b/=3,a++; //除去b因数中所有的3
	if(b!=1) a=-1; //如果b不为1那么说明b一开始就含有不为2或3的因数，达不到，直接输-1
	printf("%d",a);
}
```


---

## 作者：1saunoya (赞：2)

>[更好的阅读体验](https://www.cnblogs.com/qf-breeze/p/10564133.html)
~~~
	这个是div3的第一题 也是最简单的一道题目。。。全场切的题。
~~~
>这题很简单啊 可以用$DFS$来打
>毕竟是 $2^x*3^y=m 输出x+y啊$
>这是最简单的做法
~~~
#include <bits/stdc++.h>
using namespace std;
typedef long long LL ;
inline LL In() { LL res(0),f(1); register char c ;
    while(isspace(c=getchar())) ; c == '-'? f = -1 , c = getchar() : f = 1 ;
    while(res = (res << 1) + (res << 3) + (c & 15) , isdigit(c=getchar())) ; return res * f ;
}
int n , m ;
int ans = 0x7f7f7f7f;
inline void dfs(int x,int step) {//x是当前数值  step是步数
    if(x > m) return ;
    if(x == m) {//符合条件
        cout << step << endl ;//输出
        exit(0);//这个同return 0; 不过适用于函数中
    }
    dfs(x<<1,step+1) , dfs(x*3,step+1) ;
}
signed main () {
    n = In() , m = In() ;
    dfs(n,0) ;
    if(ans == 0x7f7f7f7f) cout << -1 << endl ;
    return 0 ;
}
~~~

---

## 作者：hensier (赞：1)

这道题可以用$dfs$过。每一次进行函数操作，就把参数$k$乘$2$、乘$3$进行递归。再设置一个$step$参数，每次加$1$。只要$k>m$就退出，如果$k=m$直接输出$step$，并退出$\red{\text{整个程序}}$，注意不是函数。

我们为了在函数中便于退出整个函数，可以使用$exit(0)$，这个函数在$cstdlib$库中。

$AC$代码：

```cpp
#include<cstdio>
#include<cstdlib>
int n,m;
void dfs(int k,int step)
{
    if(k>m)return;//k>m就跳出函数
    if(k==m)
    {
        printf("%d",step);
        exit(0);//k=m就结束程序
    }
    dfs(k*2,step+1);
    dfs(k*3,step+1);//衍生
}
int main()
{
    scanf("%d%d",&n,&m);//输入
    dfs(n,0);//初始的step=0，一开始k=n
    printf("-1");//dfs完了以后输出-1
}
```

---

## 作者：KazamiHina (赞：0)

~~这个应该是你咕最水的黄题吧qaq~~

直接搜就好了

如果搜到了就与现在的答案比较大小

如果已经 大于m了 或者 比现在用的步数多了 就退出

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int a,b,ans=0x7fffffff;//ans要初始化的很大

inline void dfs(int x,int step)
{
	if(x>b||step>ans)return;//如果现在的x已经比m大了 或者 现在用的步数已经比ans大了 就直接退出不用搜了
	if(x==b)ans=min(ans,step);//打擂台比大小
	dfs(x*2,step+1);//递归乘2的情况
	dfs(x*3,step+1);//递归乘3的情况
}

int main()
{
	cin>>a>>b;//输入不多说
	dfs(a,0);//递归
	if(ans==0x7fffffff)cout<<-1;//如果ans没有改变过则无解输出-1
	else cout<<ans;
	return 0;
}
```


---

## 作者：zhy12138 (赞：0)

本文同步发表于[我的博客](https://zhy12138.github.io/2019/03/24/CF-1141-div3/)

作为一道A题，它的难度不大，也没什么要注意的细节

无解的两种情况：

- m不为n的倍数

- $\frac{m}{n}$除2和3以外有别的因子

具体做法就把$\frac{m}{n}$中的2和3剥离，然后看是否为1就行了

次数可以在剥离2和3的同时进行计算

代码如下
```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<ctime>
#define ll long long
using namespace std;
inline int read()
{
    int kkk=0,x=1;
    char c=getchar();
    while((c<'0' || c>'9') && c!='-')
        c=getchar();
    if(c=='-')
        c=getchar(),x=-1;
    while(c>='0' && c<='9')
        kkk=(kkk<<3)+(kkk<<1)+(c-'0'),c=getchar();
    return kkk*x;
}
int n,m;
int main()
{
    n=read(),m=read();
    if(m%n!=0)
    {
        puts("-1");
        return 0;
    }
    int t=m/n,ans=0;
    while(t%2==0)
        t/=2,++ans;
    while(t%3==0)
        t/=3,++ans;
    if(t==1)
        printf("%d\n",ans);
    else
        puts("-1");
    return 0;
}
```

---

## 作者：FP·荷兰猪 (赞：0)

> 题意：给定两个整数n，m，现在你要进行若干次操作，每次操作珂以把n乘上2或3，求能否通过一定数量次的操作，把n变成m，若能则输出操作次数，若不能则输出-1。

解法：纯模拟。

先判断m是否能整除n，不能的话直接输出-1，否则把商不断得除以2和3，直到都除不尽为止。此时若商是1则输出操作次数，否则输出-1。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for (i=x;i<=y;i++)
typedef long long ll;
const long long INF=214748347;

int main()
{
	ll n,m;
	cin>>n>>m;
	double shang;
	shang=m*1.0/n;
	if (shang!=int(shang))//判断m是否为n的整数倍
	{
		cout<<"-1"<<endl;
		return 0;
	}
	else
	{
		ll t;
		t=m/n;
		ll ans;
		ans=0;
		while (t%3==0)
		{
			t/=3;
			ans++; 
		}
		while (t%2==0)
		{
			t/=2;
			ans++;
		}
		if (t!=1)
		{
			cout<<"-1"<<endl;
			return 0;
		}
		else
		{
			cout<<ans<<endl;
			return 0;
		}
	}
	return 0;
}
```

---


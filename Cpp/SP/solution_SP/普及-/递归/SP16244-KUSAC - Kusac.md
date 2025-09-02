# KUSAC - Kusac

## 题目描述

Mirko has given up on the difficult coach job and switched to food tasting instead. Having skipped 

breakfast like a professional connoisseur, he is visiting a Croatian cured meat festival. The most 

renowned cook at the festival, Marijan Bajs, has prepared N equal sausages which need to be 

distributed to M tasters such that each taster gets a precisely equal amount. He will use his trusted knife 

to cut them into pieces. 

In order to elegantly divide the sausages, the number of cuts splitting individual sausages must be as 

small as possible. For instance, if there are two sausages and six tasters (the first test case below), it is 

sufficient to split each sausage into three equal parts, making a total of four cuts. On the other hand, if 

there are three sausages and four tasters (the second test case below), one possibility is cutting off three 

quarters of each sausage. Those larger parts will each go to one of the tasrers, while the fourth taster 

will get the three smaller pieces (quarters) left over. 

Mirko wants to try the famous sausages, so he volunteered to help Bajs. Help them calculate the 

minimum total number of cuts needed to carry out the desired division. 

## 样例 #1

### 输入

```
2 6```

### 输出

```
4```

## 样例 #2

### 输入

```
3 4
```

### 输出

```
3
```

# 题解

## 作者：Miller2019 (赞：11)

题意：求把 $\ n$ 根香肠切成 $\ m$ 分所需的刀数。

思路：如果切的地方刚好在连接的地方，就可以减去一刀。先假设需要切 $\ m-1$ (本来的次数) 刀，然后再减去 $\ n$ 和 $\ m$ 的最大公约数(重叠的部分)，再加上末尾的一刀。所以说答案就是 $\ m$ 减去 $\ m , n $  的最大公因数。

```cpp
#include<stdio.h>
int gcd(int a,int b) //log(min(a,b))
{
	return b?gcd(b,a%b):a;
}
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	printf("%d",m-gcd(n,m));
	return 0;
}
```

蒟蒻橙后第 11 篇题解。

---

## 作者：_Camille_ (赞：9)

### 前言

一眼看到这题感觉没爬完，然后编者就去 SPOJ 看了一眼，发现确实没爬完 ...

### 题意简述

给你 $n$ 个香肠，有 $m$ 位品尝者，你要切多少刀才能让每位品尝者都吃到同样分量的香肠。输出切多少刀。

附上英文完整题面，由于编者被禁言了，希望管理员在审核的时候加上。

```
Mirko has given up on the difficult coach job and switched to food tasting instead. Having skipped 

breakfast like a professional connoisseur, he is visiting a Croatian cured meat festival. The most 

renowned cook at the festival, Marijan Bajs, has prepared N equal sausages which need to be 

distributed to M tasters such that each taster gets a precisely equal amount. He will use his trusted knife 

to cut them into pieces. 

In order to elegantly divide the sausages, the number of cuts splitting individual sausages must be as 

small as possible. For instance, if there are two sausages and six tasters (the first test case below), it is 

sufficient to split each sausage into three equal parts, making a total of four cuts. On the other hand, if 

there are three sausages and four tasters (the second test case below), one possibility is cutting off three 

quarters of each sausage. Those larger parts will each go to one of the tasrers, while the fourth taster 

will get the three smaller pieces (quarters) left over. 

Mirko wants to try the famous sausages, so he volunteered to help Bajs. Help them calculate the 

minimum total number of cuts needed to carry out the desired division. 



```

以及补上一组 SPOJ 上有的样例：

```
Input:
3 4 

Output:
3
```

### 解题思路

编者想到的是递归，分两种不同的情况。我命名递归函数为 $rec$

1. 当 $n>=m$ 时，递归 $rec(n$ $mod$ $m)$

1. 当 $n<m$ 时，递归 $x+rec(n,m-n)$

特别的，当 $n$ 和 $m$ 不互质时，我们取其最大公约数，设为 $t$ ，递归 $t*rec(n/t,m/t)$

小提醒：当 $x=0$ 与 $x=1$ 时注意特判一下。

具体这样，可能有一点难度，想通了就好了，可手动模拟帮助理解。

实现看代码。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int rec(int x,int y){
    int t;
    if(x==0) return 0; 
    if(x==1) return y-1; //注意一下这两种情况的特判

    t=__gcd(x,y); //直接使用 __gcd 函数，因为我用了万能头，要单独使用需加上头文件 algorithm 。如果想要速度更快可以手打。
    
    if(t>1)  return t*rec(x/t,y/t);
    if(x>=y) return rec(x%y,y);
    if(x<y)  return x+rec(x,y-x); //三种情况递归
}
int main(){
    int n,m;
    cin>>n>>m;
    int ans=rec(n,m);
    cout<<ans;
    return 0; //主函数按题意输入输出
}
```
### 结尾

具体就是这样，还有不懂可以私信我。

管理员审核辛苦了。

---

## 作者：做对算我输 (赞：5)

由题可知，有m位品尝者，则每人可以吃到总香肠的1/m。


我们可以把所有香肠的总和理解为一根长长的香肠，每一根香肠的间隙则为这根长长的香肠的断口，当断口与我们要切的一刀重合时，我们就可以少切一刀。

则我们总共可以少切n与m的最大公因数刀。

图中橙色方框为香肠的断口，黑色直线为我们切的刀，虚线为我们不用切的刀。

![](https://cdn.luogu.com.cn/upload/image_hosting/mmyznkwg.png)



![](https://cdn.luogu.com.cn/upload/image_hosting/dph9qu17.png)

下面来看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
	cin>>n>>m;
	int a=__gcd(n,m);//记录n与m的最大公因数
	cout<<m-a<<endl;
	return 0;
}
```


---

## 作者：过往梦魇之殇 (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/SP16244)

**思路简述：**

将$n$根香肠连在一起，正常来讲要切$m-1$刀

切在接口处就不用切了，减一刀，总共应该是$gcd(n,m)-1$刀要减去

然后：总共要切的就是$(m-1)-(gcd(n,m)-1)=m-gcd(n,m)$

所以直接输出答案即可！

**代码展示：**

```cpp
#include<bits/stdc++.h>
#define re register
#define in inline
#define ll long long
#define pi acos(-1.0)
#define inf 2147483640
using namespace std;
in int read()
{
    int sum=0,negative=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')negative=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        sum=sum*10+ch-'0';
        ch=getchar();
    }
    return sum*negative;
}
in void write(int X)
{
    if(X<0)putchar('-'),X=-X;
    if(X>=10)write(X/10);
    putchar(X%10+'0');
}
int main()
{
	int n=read();
	int m=read();
	write(m-__gcd(n,m));
    return 0;
}
```

管理员审核辛苦了~

>$Thanks$ $For$ $Watching!$

---

## 作者：Into_qwq (赞：2)

### 题目大意 : 有$n$根香肠,分给$m$个人,最少问要切几次

~~我是不是可以提交翻译了~~

然后,我们可以想到 : 最多需要切$m-1$次

因为一刀两段 , 两刀三段... $m$刀$m-1$段

然而 , 有些例外 :

$n$=$2$ , $m$=$6$时 , 只用切了四刀

想想为啥 ?

因为香肠本身是断开的 , 所以省了一刀

具有这种特点的香肠的最大公约数($gcd$)大于$1$

总结一下，就是先假设要切$m$-$1$刀，然后再减去$n$和$m$的最大公约数，也就是断开的地方

但这样不能$AC$ , 因为最后的地方不用切，所以还要加上一 , 就和前面$m$-$1$那个$1$抵消了

**代码如下**

```c++
#include<bits/stdc++.h>
using namespace std;
int gcd(int n,int m)//求最大公约数
{
    int r=m%n;
    while(r)
    {
        m=n;
        n=r;
        r=m%n;
    }
    return n;
}
int main()
{
    int n,m;
    cin>>n>>m;
    if(n==1)
    {
        cout<<m-1;
        return 0;
    }
    cout<<m-gcd(n,m);
}
```

---

## 作者：hicc0305 (赞：2)

一共有两种算法：

### 一
按照情况递归(x为木棒数，y为人数)：1.当前x,y的gcd大于1，那么就递归gcd*get(x/gcd,y/gcd) 2.当前x>=y,递归get(x%y,y) 3.x<y,递归x+get(x,y-x)

代码如下
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m;
int gcd(int x,int y)
{
	if(x==0) return y;
	return gcd(y%x,x);
}
int get(int x,int y)
{
	if(x==0) return 0;
	if(x==1) return y-1;
	int g=gcd(x,y);
	if(g>1) return g*get(x/g,y/g);
	else if(x>=y) return get(x%y,y);
	else return x+get(x,y-x);
}
int main()
{
	scanf("%d%d",&n,&m);
	printf("%d",get(n,m));
	return 0;
}
```

### 二
可以知道，最后每个人拿到的长度一定是总长度除以人数，可以想象成原来你就有一根长度为总长的木棍，你本来分给n个人需要切n-1刀，已经有别人帮你切了几刀，那么那重复的几刀你就不用切了

代码:
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll a,ll b){return (b?gcd(b,a%b):a);}
ll lcm(ll a,ll b){return a*b/gcd(a,b);}
ll a,b;
int main()
{
	scanf("%lld%lld",&a,&b);
	printf("%lld",b-a*b/lcm(a,b));//b减去重复的导数
	return 0;
} 
```

---

## 作者：Kevin_Zhen (赞：1)

题目链接 [$\mathfrak{SP16244}$](https://www.luogu.com.cn/problem/SP16244)。

### 题意
求把 $n$ 根香肠平均切成 $m$ 份所需的刀数。

### 思路
首先考虑，如果只有一根香肠，平均切成 $m$ 份，需要切 $m$ 刀。  
题目有 $n$ 根香肠。每两根香肠的连接处不需要切，等同于帮我们切了一刀，一共帮我们切了 $\gcd(n,m)$ 刀。所以我们需要再切 $m-\gcd(n,m)$ 刀。

### AC CODE
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int n, m;

int main() {
	scanf("%d%d", &n, &m);
	printf("%d", m - __gcd(n, m));
	return 0;
}
```

### 感谢观赏！

---

## 作者：Rn_Lamsuly (赞：1)

在看到这题时，我先看了看样例，发现两个样例输出都是 $(m-gcd(n,m))$ ,
然后就交了这么一份代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int g=__gcd(n,m);
	printf("%d",m-g);
	return 0;
}
```
然后就过了？？？
我们来分析一波：
我们可以先把所有香肠连在一起，然后平均剪开，本来就没有相连的部分就不算。

其中平均剪开要 $(m-1)刀$ ，要剪地方和未连接地方重合个数是 $(gcd(n,m)-1)$ （小学奥数最大公因数回看不谢）。两数相减，得到 $(m-gcd(n,m))$ ，然后就可以开心的code了。

备注：gcd这个东西其实不用手写，C++自带函数:
```cpp
__gcd(n,m)
```
可以求出 $n,m$ 的**最大公因数**。

什么？你问**最小公倍数**？
```cpp
n*m/__gcd(n,m)
```
不用谢

---

## 作者：WsW_ (赞：0)

### 更新
这是一篇**已通过**的题解。
- $2024.12.12$ 更新老题解。

---
### 思路
容易想到想到，切的刀数等于块数减一。  
![](https://cdn.luogu.com.cn/upload/image_hosting/dxqj9n91.png)  
要切成 $m$ 块，所以要切 $m-1$刀。   

令每根香肠的长度为 $m$，那么 $n$ 根香肠看作一根长度为 $n\times m$ 的大香肠。本来隔 $n$ 的长度就切一刀，要切 $m-1$ 刀。但实际上每隔 $m$ 的长度就本身是断的，减去这些重复了的地方。  
容易发现，每隔 $n$ 切一刀和每隔 $m$ 断开，实际上就是每隔 $\operatorname{lcm}(n,m)$ 会重复一次。大香肠的长度为 $n\times m$，所以一共有 $\dfrac{n\times m}{\operatorname{lcm}(n,m)}-1=\gcd(n,m)-1$ 个地方重复了。其中减一是因为末尾不用切，所以要剔除。  

综上，一共要切 $m-1-\left(\gcd(n,m\right)-1)=m-\gcd(n,m)$ 刀。  
$\gcd(n,m)$ 可以用辗转相除法求，也可以使用函数 `__gcd(n,m)`。  

---
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int gcd(int i,int j){
	if(j==0)return i;
	return gcd(j,i%j);
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	printf("%d",m-gcd(n,m));
	return 0;
}
```

---


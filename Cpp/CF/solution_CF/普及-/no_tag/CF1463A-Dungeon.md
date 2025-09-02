# Dungeon

## 题目描述

You are playing a new computer game in which you have to fight monsters. In a dungeon you are trying to clear, you met three monsters; the first of them has $ a $ health points, the second has $ b $ health points, and the third has $ c $ .

To kill the monsters, you can use a cannon that, when fired, deals $ 1 $ damage to the selected monster. Every $ 7 $ -th (i. e. shots with numbers $ 7 $ , $ 14 $ , $ 21 $ etc.) cannon shot is enhanced and deals $ 1 $ damage to all monsters, not just one of them. If some monster's current amount of health points is $ 0 $ , it can't be targeted by a regular shot and does not receive damage from an enhanced shot.

You want to pass the dungeon beautifully, i. e., kill all the monsters with the same enhanced shot (i. e. after some enhanced shot, the health points of each of the monsters should become equal to $ 0 $ for the first time). Each shot must hit a monster, i. e. each shot deals damage to at least one monster.

## 说明/提示

In the first test case, you can do as follows: $ 1 $ -th shot to the first monster, $ 2 $ -th shot to the second monster, $ 3 $ -th shot to the third monster, $ 4 $ -th shot to the first monster, $ 5 $ -th shot to the third monster, $ 6 $ -th shot to the third monster, and $ 7 $ -th enhanced shot will kill all the monsters.

In the second test case, you can't kill monsters with the same enhanced shot, because the total number of health points of monsters is $ 3 $ , and you will kill them in the first 3 shots.

## 样例 #1

### 输入

```
3
3 2 4
1 1 1
10 1 7```

### 输出

```
YES
NO
NO```

# 题解

## 作者：Locklink (赞：8)

“`每 7 次开炮为增强版` ”，说明六次开炮是普通开炮，造成 $1$ 点伤害，一次开炮是增强版，给每个怪物造成 $1$ 点伤害，三个怪物就是 $3$ 点。

所以每 $7$ 次开炮共计能造成 $1*6+3=9$ 点伤害。

要想在某次增强版开炮后所有的怪物都挂掉，$a+b+c$就必须是 $9$ 的倍数。

此外，还需保证，这三个怪物中较弱的必须能挺到最后，不会中间就挂掉了。

最终每个怪物会承受 $(a+b+c)/9$ 点伤害，因此必须满足 $(a+b+c)/9 \le \text{min}(a,b,c)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
		int a,b,c;
		cin>>a>>b>>c;
		int sum=a+b+c;
		if(sum%9==0&&sum/9<=min(a,min(b,c))){
			cout<<"YES"<<endl;
		}
		else{
			cout<<"NO"<<endl;
		}
	}
}
```


---

## 作者：gyh20 (赞：2)

模拟。

首先，我们把 $7$ 次操作看成一轮，所以说每一轮会造成 $9$ 的伤害，所以如果总血量不是 $9$ 的倍数，则输出 NO。

否则，判断三个数的最小值，我们一定会保到最后，也就是说，如果总轮数大于最小的一个，则输出 NO。

否则输出 YES。

```cpp
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<cstdio>
#include<algorithm>
#define re register
using namespace std;
const int Mxdt=500000;	//单次大小 
inline char gc(){
	static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline int read(){
	re int t=0;re char v=gc();
	while(v<='0')v=gc();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=gc();
	return t;
}
int n,a,b,c,t;
int main(){
	t=read();
	while(t--){
		a=read(),b=read(),c=read();
		if((a+b+c)%9)puts("NO");
		else{
			int d=min(min(a,b),c);
			if(d<(a+b+c)/9)puts("NO");
			else puts("YES");
		}
	}
}
```


---

## 作者：juun07 (赞：0)

## 直奔主题

>  每第七次开炮为增强版

说人话即叠加六次平A激活大招

前六次开炮伤害为1

第七次开大的伤害和则为3

$1*6+3=9$

所以要想用一个大招消灭掉所有怪物

必须要保证的前提是

- 怪物的血量为9 or 9的倍数

但因为大招是针对所有怪物的

比如一个血量为3的怪物

就算平A不在他身上

大招也得打掉一滴血

所以还要保证开大次数不能小于他们血量的最小值

这么一想代码很容易就能写出来了

## Code(代码略长，但十分易读)

```cpp
#include <iostream>
#include <cstdio>

using namespace std; 

int a[10001],b[10001],c[10001],sum;

int M(int a,int b,int c)//找最小值 
{
	if(a<=b&&a<=c)
		return a;
	if(b<=a&&b<=c)
		return b;
	if(c<=b&&c<=a)
		return c;
}

int main () 
{
	int t;
	cin>>t;
	
	for (int i=0;i<t;i++) 
	{
		cin>>a[i]>>b[i]>>c[i]; 
	}
	
	for (int i=0;i<t;i++)
	{
		sum=a[i]+b[i]+c[i]; //求和 
		if (sum%9==0&&M(a[i],b[i],c[i])>=sum/9)//核心部分，判定 
		{
			cout<<"YES"<<endl; 
		}
		else
		{
			cout<<"NO"<<endl; 
		}
	}
	
	return 0; 
}
```

### 感谢阅读，希望我的题解能帮你理清思路

---

## 作者：oimaster (赞：0)

[可能不会有更好效果的博客](https://oi-master.gitee.io/2020/12/22/Codeforces-1463A-%E9%A2%98%E8%A7%A3/)

题目链接戳：<http://codeforces.com/problemset/problem/1463/A>

首先，很清楚每 $7$ 炮会打出 $1+1+1+1+1+1+3$ 点伤害，因为第 $7$ 炮会被加强到所有的怪兽。也就是说，每 $7$ 炮会打出 $9$ 点伤害。

那么我们可以当 $a+b+c$ 是九的倍数时，输出 `Yes`，否则输出 `No`。

然而事情并不简单。若是这样：

```
1 1 16
```

我们发现，第 $1$ 和第 $2$ 个怪兽后面就直接死了，没有挺到最后。那么最坏他们要被打 $\left(a+b+c\right)\div9$ 下。

所以增加判断 $a+b+c\ge\left(a+b+c\right)\div9$。

```c++
#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int a,b,c;
        cin>>a>>b>>c;
        int sum=a+b+c;
        if(sum%9!=0)
            cout<<"No";
        else{
            sum/=9;
            if(a<sum||b<sum||c<sum)
                cout<<"No";
            else
                cout<<"Yes";
        }
        cout<<endl;
    }
}
```

---

## 作者：Time_tears (赞：0)

可以很容易注意到答案要为YES，那么 $a+b+c$ 必定是 $9$ 的倍数(因为每一轮删 $7$ 次会删掉 $9$ )。

还有什么情况是不合法的呢，可以发现当 $(a+b+c) \div 9$ 大于 $\min (a,b,c)$ 时，最小的会被减到零，所以此时也不合法。

判掉这两种情况后就一定合法了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,a,b,c;
inline int read() {
	int s=0,f=0;
	char ch=getchar();
	while(ch<48||ch>57)f=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58)s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
int main() {
	T=read();
	while(T--) {
		a=read(),b=read(),c=read();
		int sum=a+b+c,tmp=min(min(a,b),c);
		if(sum%9!=0)puts("NO");
		else if(sum/9>tmp)puts("NO");
		else puts("YES");
	}
	return 0;
}
```


---

## 作者：luosw (赞：0)

由于执行的操作有周期性，考虑每一个长度为 $7$ 的周期。我们考虑 $s=a+b+c$，在执行 $7$ 次操作后，前六次 $s-6$，第七次当 $a,b,c$ 都不为零时 $s-3$，因此每个周期的操作，$s$ 的值会减去 $9$。

因而我们得到：**引理 1** 满足题意的三元组 $(a,b,c)$ 一定满足 $9\mid a+b+c$。

下面我们考虑在执行周期内的第 $7$ 次操作时，$a,b,c$ 存在 $0$ 的情况，显然有

$$
\textbf{引理 2}\qquad\dfrac{s}{9}>\min(a,b,c)\iff \text{Output}\texttt{ NO}.
$$

排除引理 $1,2$ 的情况后输出 $\texttt{YES}$ 即可。

---


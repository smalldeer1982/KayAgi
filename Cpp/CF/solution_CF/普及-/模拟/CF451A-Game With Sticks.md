# Game With Sticks

## 题目描述

After winning gold and silver in IOI 2014, Akshat and Malvika want to have some fun. Now they are playing a game on a grid made of $ n $ horizontal and $ m $ vertical sticks.

An intersection point is any point on the grid which is formed by the intersection of one horizontal stick and one vertical stick.

In the grid shown below, $ n=3 $ and $ m=3 $ . There are $ n+m=6 $ sticks in total (horizontal sticks are shown in red and vertical sticks are shown in green). There are $ n·m=9 $ intersection points, numbered from $ 1 $ to $ 9 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF451A/18b27511f71a42f9e0fd0b22af6d5248021325d7.png)The rules of the game are very simple. The players move in turns. Akshat won gold, so he makes the first move. During his/her move, a player must choose any remaining intersection point and remove from the grid all sticks which pass through this point. A player will lose the game if he/she cannot make a move (i.e. there are no intersection points remaining on the grid at his/her move).

Assume that both players play optimally. Who will win the game?

## 说明/提示

Explanation of the first sample:

The grid has four intersection points, numbered from $ 1 $ to $ 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF451A/e0d83475f64b355b0a9b5538e74aa373b38a9909.png)If Akshat chooses intersection point $ 1 $ , then he will remove two sticks ( $ 1-2 $ and $ 1-3 $ ). The resulting grid will look like this.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF451A/c9bd491d9b8dd9c48045e00c65ed3725174a35a0.png)Now there is only one remaining intersection point (i.e. $ 4 $ ). Malvika must choose it and remove both remaining sticks. After her move the grid will be empty.

In the empty grid, Akshat cannot make any move, hence he will lose.

Since all $ 4 $ intersection points of the grid are equivalent, Akshat will lose no matter which one he picks.

## 样例 #1

### 输入

```
2 2
```

### 输出

```
Malvika
```

## 样例 #2

### 输入

```
2 3
```

### 输出

```
Malvika
```

## 样例 #3

### 输入

```
3 3
```

### 输出

```
Akshat
```

# 题解

## 作者：封禁用户 (赞：3)

这是一道博弈论的题，找出规律即可~~秒~~。  
题目传送>>[CF451A](https://www.luogu.com.cn/problem/CF451A)  
### 题意简述：  
$n$ 根竖棒和 $m$ 根横棒交叉摆出 $n* m$ 个交点，Malvika 和 Akshat 轮流取一交点对应两棒，最终不能选者败，求胜者。  
### 题目分析:  
两人轮流此游戏，我们可计算出游戏可进行的总次数，然后对总次数判奇偶，奇则先手胜，偶则次手胜。  
$n$ 根竖棒和 $m$ 根横棒交叉摆出 $n* m$ 个交点，每次取交点对应的两根棒，即一根竖棒一根横棒，如剩余横、竖棒均有，则还可进行。所以可以发现游戏可进行的总次数是由竖棒数和横棒数的最小值决定的，因为每一个交点都由一根竖棒和横棒才可构成。  
也就是说，此博弈论题我们只需对竖棒数和横棒数的最小值进行判奇偶，奇则先手 Akshat 胜，偶则次手 Malvika 胜。  
### 问题解决：  
#### 判断：  
我们可以直接使用 if...else... 进行判断。  
即:  
```cpp
if(min(n,m)%2!=0)
{
	cout<<"Akshat";
}
else
{
	cout<<"Malvika";
}
```
当然，我们也可以使用一个小东西 —— 三目运算符 “?:”。  
例 ：a?b:c 的含义是：如果 a 为真，则表达式的值是 b，否则是 c。  
即:  
```cpp
cout<<(min(n,m)%2!=0? "Akshat":"Malvika");
```
### Code:  
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("input.in","r",stdin);
	//freopen("print.out","w",stdout);
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	int n,m;   //定义竖棒数和横棒数
	cin>>n>>m;
	cout<<(min(n,m)%2!=0? "Akshat":"Malvika");   //利用三目运算符判断输出
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）：  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/ewuc86eq.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：3a51_ (赞：1)

### 思路分析

每次取走一个交点，就会拿走一根横棒一根竖棒，最后肯定是小的先被取完，所以只要取 $\min(a,b)$ 次就没有交点了。也就是说，取完 $\min(a,b)$ 次后轮到谁，谁就输了。

可以从样例中看出，```Malvika```先手。

### 代码

```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	if(min(n,m)%2)//该Akshat了
		cout<<"Akshat";
	else
		cout<<"Malvika";
	return 0;
}
```

---

## 作者：Ybocean_s (赞：1)

题意：$ n $ 根竖棒和 $ m $ 根横棒交叉摆出交点，$ Malvika $ 和 $ Akshat $ 轮流取一交点对应两棒，最终不能选者败，求胜者。


------------


思路：计算出游戏可进行的总次数，然后对总次数判断，奇则先手胜，偶则次手胜。可以发现游戏可进行的总次数是由竖棒数和横棒数的最小值决定的，因为每一个交点都由一根竖棒和横棒才可构成，当较小的被拿完，游戏结束。


------------

代码为：

```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	if(min(n,m)%2!=0){//判断奇数偶数。
	cout<<"Akshat";
	}else{
	cout<<"Malvika";
	}
	return 0;
}
```


---

## 作者：LordLaffey (赞：1)

## 分析
这道题其实就是看有无交点，而无交点的情况则是只有相同方向的木棍。

而每次选取一个交点则必然会使横向纵向的木棍各减少一根，那么交点的存在就只与数量最少的那个方向的木棍有关。问题就转化成了
>有$min(m,n)$根木棍，每次两人轮流抽一根，谁抽到最后一个则胜

那么就只需要判断此方向上木棍奇偶即可，若为奇数则输出$Akshat$,否则输出$Malvika$

## 代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
string s[2]={"Malvika","Akshat"}; 

int main(){
	
	int n,m;
	scanf("%d%d",&n,&m);
	
	cout<<s[min(n,m)%2];
	
	return 0;
	
}
```
完结撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：BlackPanda (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF451A)

------------
### 题意：
用 $m$ 根横棒，$n$ 根竖棒，交叉摆出 $n×m$ 个交点，两人轮流摆，每次选一个交点，拿走过这个交点的两个棒。最后没得选的人输。输出胜者。

------------
### 思路：
每次拿走一根横棒和一根竖棒，数量少的先被取完，所以可以假设横棒数量为 $x$，竖棒数量为 $y$。则取 $min(x,y)$ 次后，小棒就被取完了，最后只要判断最后一个是谁取的，谁就是胜者。（注：可以用较少小棒数量的奇偶性来判断胜者。）（先手是```Akshat```）

------------
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long x,y; 
int main(){
	cin>>x>>y;
	long long t=min(x,y);
	if(t%2!=0){
		cout<<"Akshat"<<endl;
	}
	else{
		cout<<"Malvika"<<endl;
	}
	return 0;
}

```


---

## 作者：封禁用户 (赞：0)

## 题目详解

这道题我们有两个数据，$n$ 和 $m$ ，怎们做呢？我们要求胜的人

我们可以看到，每个人拿走一个交叉点，我们就需要拿走一个横的一个竖的，那最后结束条件是啥？横的先拿完或竖的先拿完或横的和竖的同时拿完。那我们就要一个 $k$ 来存 $\min(n,m)$ 

1. $k\equiv1\pmod{2}$ 那么就是 $Malvika$ 刚刚拿完，就 $Akshat$ 就没办法取了，于是我们就输出 $Akshat$

1. $k\equiv0\pmod{2}$ 那么就是 $Akshat$ 刚刚拿完，就 $Malvika$ 就没办法取了，于是我们就输出 $Malvika$


于是代码如下：

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long l;//忘了int吧，我被int坑过10000000回！！！

int main() {
	l a,b;
	cin>>a>>b;
	l k=min(a,b);
	if(k%2==1){
		cout<<"Akshat"<<endl;
	}else{
		cout<<"Malvika"<<endl;
	}
	return 0;
}
```
勿抄袭，勿抄袭，勿抄袭！！！
# 谢谢观赏

---

## 作者：违规用户名gAGt8$%z (赞：0)

## 思路
每次操作只会减少一行一列，行和列的奇偶性和原来奇偶性相同，行和列中有一个为零就结束了，因此答案只和行和列中较小的那一个有关。

所以只要判断行和列较小的那个的奇偶性。

若为奇，输出 $Malvika$ ; 

反之输出 $Akshat$ 。

------------

**那么，上代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m; cin>>n>>m;
	if(min(n,m) % 2)cout<<"Akshat";
	else cout<<"Malvika";
	return 0;
}

```


---

## 作者：Creator_157 (赞：0)

### 大体思路：
这题可以看作是道博弈论，因为每拿走一个点，就减少一个横棒和一个竖棒，最后没得选的人输（就是 横棒 或 竖棒 中有一者取为 $0$）。

所以就判断 横棒、竖棒 的**最小值**的**奇偶** :

若为奇，输出 $Malvika$ ; 反之输出 $Akshat$ 。

------------
### code：

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
int m,n;
int main()
{
    cin>>m>>n;
    m=min(m,n);
    if(m%2==0)cout<<"Malvika";
    else cout<<"Akshat";
    return 0;
}
```
亦可简化为 三目做法

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
int m,n;
int main()
{
    cin>>m>>n;
    cout<<(min(m,n)%2==0?"Malvika":"Akshat");
    return 0;
}
```

---

## 作者：shiroi (赞：0)

一道勉强算是博弈论的题。

由于每次操作只会减少一行一列，行和列有一个为零就结束了，因此答案只和较小的那一个有关。

代码实现很简短，仅需要判断一下结果的奇偶性即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0; int f=1; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1; ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-'0'; ch=getchar();}
	return x*f;
}

int main(int argc, char const *argv[])
{
	puts(min(read(),read())&1 ? "Akshat" : "Malvika");
	return 0;
}
```

---


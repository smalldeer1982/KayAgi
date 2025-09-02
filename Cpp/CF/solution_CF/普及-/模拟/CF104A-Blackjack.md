# Blackjack

## 题目描述

Blackjack是一个扑克牌游戏。

Blackjack使用除了两张王以外的全部52张卡牌，也就是$2,3,4,5,6,7,8,9,10,J,Q,K,A$。其中规定$2,3,4,5,6,7,8,9,10$的点数为$2,3,4,5,6,7,8,9,10$，$J,Q,K$的点数均为$10$，$A$的点数同时为$1$或$11$，这取决于玩家的意愿。虽然扑克牌有花色，但是一张卡牌的点数与其花色无关。这个游戏的规则很简单：拿两张牌，如果这两张牌的点数之和等于$n$，玩家就赢了，否则玩家就输了。

现在玩家已经拿了一张黑桃$Q$，求在其他牌中再抽一张，能使玩家赢得游戏的方案数。

## 样例 #1

### 输入

```
12
```

### 输出

```
4```

## 样例 #2

### 输入

```
20
```

### 输出

```
15```

## 样例 #3

### 输入

```
10
```

### 输出

```
0```

# 题解

## 作者：封禁用户 (赞：3)

此题仅需几个 if 判断即可 AC。  
题目传送>>[CF104A](https://www.luogu.com.cn/problem/CF104A)
### 题意简述：  
两张王以外的全部 $52$ 张卡牌，规定数字卡牌 $2,3,4,5,6,7,8,9,10$ 的点数为其对应的数字，$J,Q,K$ 的点数为 $10$, $A$ 的点数同时为 $1$ 或 $11$，这取决于玩家的意愿，并且点数与其花色无关。现玩家已经拿了一张黑桃 $Q$，求在其他牌中再抽一张，这两张牌的点数之和等于 $n$,求方案数。  
### 题目分析：  
1. $n\leqslant10:$ 因为玩家手中已拿一张点数为 $10$ 的卡牌黑桃 $Q$，所以无法再拿一张卡牌而满足 $n$，即方案数为 $0$。  
1. $10\lt n\lt 20:$ 减去已有的 $10$，此时需凑的点数 $\in[1,9]$，取卡牌 $A$ 的 $1$ 值和各数字卡牌可满足，此时各满足的卡牌有四种花色，即方案数为 $4$。  
1. $n=20:$ 减去已有的 $10$，仅需点数为 $10$ 的卡牌一张即可，而点数为 $10$ 的卡牌有 $10,J,Q,K$,共 $4$ 种，且各种卡牌有 $4$ 种花色，方案数为 $4×4=16$ ？坑点注意！！！因为玩家手中已拿的卡牌为黑桃 $Q$，所以此时供再拿的 $Q$ 只有 $3$ 种花色，所以最终方案数为 $4×3+3=15$。  
1. $n=21:$ 减去已有的 $10$，此时需凑的点数为 $11$，取卡牌 $A$ 的 $11$ 值即可，且卡牌 $A$ 有四种花色，即方案数为 $4$。  
1. $22\leqslant n:$ 减去已有的 $10$，此时需凑的点数 $\in[12,+∞)$，所以无法再拿一张卡牌而满足，即方案数为 $0$。  
#### 综上所述，特判 $n<=10$ 或 $n>=22$ 输出 $0$,否则再特判 $n=20$ 输出 $15$ ，否则输出 $4$即可。  
### Code：  
```cpp
#include<iostream>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);   //关同步流，加速cin输入和cout输出 
	int n;   //定义要求的点数 
	cin>>n;
	if(n<=10||n>=22)
	{
		cout<<"0";
	}
	else
	{
		if(n==20)
		{
			cout<<"15";
		}	
		else
		{
			cout<<"4";
		}	
	}
	return 0;    //结束整个程序 
}
```
### 评测结果（未吸氧）：  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/wmq1k8oa.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：to_be_continued (赞：3)

此题为恶评题，首先我们可以发现，每一个数的答案是一定的。而只有10要输出15，其他的要么是4，要么就是超出范围0。

那么一共就三种情况，直接特判就好了。

~~没有难点~~

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

int main(){
	int n;
	scanf("%d",&n);
	n-=10;
	if (n<=0||n>11) {//0的情况
		printf("0");
		return 0;
	}  
	if (n==10){//15的情况
		printf("15");
		return 0;
	}
	printf("4");//其他情况的话，答案是唯一的，只要输出4就好了，毕竟有4个花色。
}
```
~~然后这题就奇奇妙妙的A了~~

本人为C++蒟蒻，在此膜拜各位C++巨爷。



---

## 作者：GaryH (赞：2)

# 蒟蒻又来发题解啦！

其实此题...正解不好说，反正我用的类似一遍遍遍历的方法

我用一个数组存每个点数是否用过

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt,vis[12],ll;
int main(){
	cin>>n;
	for(int i=1;i<=11;i++){
		if(i!=10){
			vis[i]=4;
			continue;
		}
		vis[i]=15;
		//把每张牌的用的次数存好 
	}
	int xp=n-10;
	while(1){//一遍遍枚举遍历 
		ll=cnt;
		//ll存上次的cnt 
		for(int i=1;i<=11;i++){//枚举 
			if(i==xp&&vis[i]>0){
				if(i==1||i==11){
					vis[1]--;
					vis[11]--;
					cnt++;
					continue;
					//如果i为1或11就一起减 
				}
				vis[i]--;
				cnt++;
				//统计 
			}
		}
		if(ll==cnt){
			cout<<cnt;
			break;
			//如果已经放不了就退循环 
		}
	}
	return 0;
}
```

# 拜拜！

---

## 作者：帝千秋丶梦尘 (赞：1)

## [题目链接](https://www.luogu.com.cn/problem/CF104A)

开头还以为是一道dfs（没好好看题）

看完后才知道只能选一张的，

所以就简单多了

先可以把n减去$10$（比较清晰

然后就可以分为三种情况：

当$n=0$或$n＞10$时：

没有点数为$0$和大于$10$的牌，所以一种选法都没有，输出$0$

当$1≤n＜10$时：

n就为$4$种，因为扑克牌每种牌是有$4$张的，即输出$10$

当$n=10$时：

可以选$10,J,Q,K$，但是$Q$题目中说到你现在已经有了张$Q$了，所以15种

（其实样例里就有）

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(void)
{
	std::ios::sync_with_stdio(false);
	cin>>n;
	n-=10;
	if((n>=1&&n<10)||(n==11)) cout<<"4";
	else if(n==10) cout<<"15";
	else cout<<"0";
	return 0;
}
```


---

## 作者：林家三少 (赞：1)

这一题可以非常$\color{black}\text{~~睿智~~}$的特判

我们可以发现输出只有三种情况：

- 输出$0$的情况，有两种，一种是$n≤10$，因为$Q$就是$10$，$10-10=0$，要一张$≤0$的牌，但并没有这样的牌，所以这种情况是输出$0$的；第二种是$n≥22$的情况，因为当前所有牌中最大的是等于$11$的$A$，$10(Q)+11(A)=21<22$,所以当$n≥22$时是无解的

- 输出$15$的情况，当$n=20$时，需要一张$10$，代表$10$的有$10,J,Q,K$这四张牌，一副牌里有四种花色，所以这时方案数$=4×4($四张牌四种花色$)-1($黑桃$Q)$

- 最后是输出$4$的情况，都是$1$张牌$×4$种花色的了

所以有了这个程序：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
int main(){
	cin>>n;
	if(n<=10||n>21)
		cout<<0;
	if(n==20)
		cout<<15;
	else
		cout<<4;
	return 0; 
} 
```
然后完美$WA$，第三个点错了，看了一下发现输出了$04$

恍然大悟，原来是$n≤10$的情况都会这样，为什么呢，因为他先输出了$0$，后面又输出了$4$，所以这是我们需要一个$else$

改成这样就$AC$了：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
int main(){
	cin>>n;
	if(n<=10||n>21)
		cout<<0;
	else
		if(n==20)
			cout<<15;
		else
			cout<<4;
	return 0; 
} 
```


---

## 作者：fzj2007 (赞：1)

### PS:

严重吐槽 这道题应该改为红题。为什么呢？因为几个`if`就可以秒掉这道题。

## 第一步 题目解读

1、读完这道题，我们发现已经给定了一个Q，所以已经确定了一个10。如果 $n \le 10$，那就无法再选一个张牌。如果 $22 \le n$，那么也无法选任何一张牌。为什么呢？因为最大的一张牌是A(11)，但是（10+11=21），21也没有22大，所以无解。这两种答案都要输出0。

2、那么如果n为20，剩下的一张牌要凑出10。因为`10`、`J`、`Q`、`K`都代表，10，所以再凑出10有 4种牌 $\times$ 4种花色 - 一个Q = 15种。

3、其他的都是 1张牌 $\times$ 4种花色 = 4种了。

下面看的更清楚：

| $n$ | `ans` |
| :----------: | :----------: |
| $0-10$ 或 $22-25$ | 0 |
| 20 | 15 |
| 其他 | 4 |

## 第二步 函数解读

下面介绍一个快速读入：

对比模式：

1、普通读入：

```
int a;
cin>>a;
```
这样的读入理解简单，适合初学者，但是非常慢。

2、scanf

```
int a;
scanf("%d",&a);
```
这样的读入就比较快了，也较好理解，在题目不卡时间的情况下可以通过大部分题。

3、初级快读
```
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
```

这个已经很快了，但是还可以更快：

4、快速读入：
```
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);//这里是重点
        ch=getchar();
    }
    return x*f;
}
```

好了最后放代码（这题就别抄了太简单）
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int ans=0,flag=1;
	char ch=getchar();
	while((ch>'9'||ch<'0')&&ch!='-') ch=getchar();
	if(ch=='-') flag=-1,ch=getchar();
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+(ch^'0');
		ch=getchar();
	}
	return ans*flag;
}
int n; 
int main(){
	n=read();
	if(n<=10||n>21) printf("0\n");
	else if(n==20) printf("15\n");
	else printf("4");
	return 0;
}
```
别忘了点赞啊！

[我的主页](https://www.luogu.com.cn/user/172370)和[博客](https://www.luogu.com.cn/blog/fzj2007/)

---

## 作者：Anleax_ (赞：1)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int ds[15] = {15,4,4,4,4,4,4,4,4,4};

int main()
{
	cin>> n;
	int cz = n - 10;
	if( cz > 11 || cz < 1 )
	{
		cout<<'0';
		return 0;
	}
	else
	{
		cout<< ds[cz%10]<< endl;
		return 0;
	}
}
```


---

## 作者：wenge (赞：1)

典型的一道手算题。不必模拟，只需要手玩打表。

在$n<=10$时，没有解。

在$10<n<=19$时，解为$4$，这$4$张牌是所有的$4$张$n-10$。

在$n=20$时，解为$15$，其他所有的$10,J,Q,K$。

在$n=21$时，解为$4$，所有的$A$。

在$n>21$时，没有解。

AC代码：
```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <stack>
using namespace std;
int f[30]={0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,15,4,0,0,0,0};
int n;
int main(){
	cin>>n;
	cout<<f[n];
    return 0;
}
```

---

## 作者：听取MLE声一片 (赞：0)

~~不得不说，这是一道裸的分类讨论题目。~~

首先是考虑无解的情况，`n` 比 `10` 小或比 `21` 大显然无解，因为最大只能凑出 `21` （$10+11=21$）。

一定注意 `A` 可以表示 `1` 和 `11`。

依照这个写出：

```
	if(n<=10||n>21){
		cout<<0;
		return 0;
	}
```

然后是 $n=20$ 的情况，一共有 `10,J,Q,K` 一共 `16` 种情况，又因为提前抽了一张 `Q` ，所以答案为 `15`。

由此得出：

```
	if(n==20){
		cout<<15;
		return 0;
	}
```

剩下的就是一一配对的情况，没有什么特殊的，直接输出 `4`  就可以了:

```
cout<<4;
```

下面是全代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n;
int main()
{
	n=read();
	if(n<=10||n>21){
		cout<<0;
		return 0;
	}  
	if(n==20){
		cout<<15;
		return 0;
	}
	cout<<4;
	return 0;
}

```

谢谢大家！

---

## 作者：末置lzy (赞：0)

# CF104A 【Blackjack】题解
题目传送器：[Blackjack](https://www.luogu.com.cn/problem/CF104A)

**题目分析**

~~本来以为要暴力模拟，在演草纸上列着样例，结果发现特判一下就完了qwq~~

首先因为有4个花色,所以大部分情况只要输出4就完了qwq

```cpp
cout<<"4";
```
不过还有两种情况要特判

1.看样例，20，黑桃Q配一起，所以只需要一张值能是10的就行了，按这题里的规则就是十，十一，十二，十三，这三张牌可以用，所以就有4*4=16种情况，但是又因为黑桃十二用过了，所以减一就有16-1=15种了，这个情况就是对10的特判。

2.当输入的数比题中十二还小或者输入的比最大还多，也就是十一，所以这个时候就只用输出0，因为它无解。

so

# AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    if(n<=10||n>21)
    {
        cout<<"0";
        return 0;
    }
    if(n==20)
    {
        cout<<"15";
        return 0;
    }
    cout<<"4";
    return 0;
}
```
结束，拜拜qwq

---

## 作者：weak_ddb (赞：0)

### [题目链接](https://www.luogu.org/problem/CF104A)

首先我们来分析一下题目：

1.黑桃$Q$点数为$10$，所以点数$\leq$10的全部无解，输出$0$。

2.牌中最大点数为$10$，所以两张牌点数最大为$20$，$n>20$全部无解，输出$0$。

3.因为$n-10$只有唯一值，但是点数$10$有$10,J,Q,K$四种卡牌，其余只有$1$种。所以分类讨论。

当$n-10\neq10$时，只有$4$种取法（有四种花色），输出$4$

当$n-10=10$时，有$15$种取法（$4\times4-1=15$，黑桃$Q$不能重复取），输出$15$。

程序如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
    cin>>n;
    if(n<=10||n>20)
        printf("0");
    else if(n==20)
        printf("15");
    else printf("4");
    return 0;
}
```


---


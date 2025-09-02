# Ternary Sequence

## 题目描述

You are given two sequences $ a_1, a_2, \dots, a_n $ and $ b_1, b_2, \dots, b_n $ . Each element of both sequences is either $ 0 $ , $ 1 $ or $ 2 $ . The number of elements $ 0 $ , $ 1 $ , $ 2 $ in the sequence $ a $ is $ x_1 $ , $ y_1 $ , $ z_1 $ respectively, and the number of elements $ 0 $ , $ 1 $ , $ 2 $ in the sequence $ b $ is $ x_2 $ , $ y_2 $ , $ z_2 $ respectively.

You can rearrange the elements in both sequences $ a $ and $ b $ however you like. After that, let's define a sequence $ c $ as follows:

 $ c_i = \begin{cases} a_i b_i & \mbox{if }a_i > b_i \\ 0       & \mbox{if }a_i = b_i \\ -a_i b_i & \mbox{if }a_i < b_i \end{cases} $

You'd like to make $ \sum_{i=1}^n c_i $ (the sum of all elements of the sequence $ c $ ) as large as possible. What is the maximum possible sum?

## 说明/提示

In the first sample, one of the optimal solutions is:

 $ a = \{2, 0, 1, 1, 0, 2, 1\} $

 $ b = \{1, 0, 1, 0, 2, 1, 0\} $

 $ c = \{2, 0, 0, 0, 0, 2, 0\} $

In the second sample, one of the optimal solutions is:

 $ a = \{0, 2, 0, 0, 0\} $

 $ b = \{1, 1, 0, 1, 0\} $

 $ c = \{0, 2, 0, 0, 0\} $

In the third sample, the only possible solution is:

 $ a = \{2\} $

 $ b = \{2\} $

 $ c = \{0\} $

## 样例 #1

### 输入

```
3
2 3 2
3 3 1
4 0 1
2 3 0
0 0 1
0 0 1```

### 输出

```
4
2
0```

# 题解

## 作者：Convergent_Series (赞：1)

题目分析：
---

考虑使用**贪心**思想。

对于 $C_i$ 的三种组成方式，最大值分别为：

$C_i = \begin{cases}A_iB_i &A_i>B_i\ \  \to2(A_i=2,B_i=1)\\
0&A_i = B_i\  \to0\\
-A_iB_i &A_i<B_i\  \to-2(A_i=1,B_i=2)\end{cases}$

所以，最优构造方式为：

+ 搭配尽可能多的 $(2,1)$
+ 将 $B$ 中的 $2$ 与 $A$ 中的 $0$ 匹配
+ 把剩下的相同数据放在一起

根据上述规则即可写出代码。

参考代码：
---
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,x_1,y_1,z_1,x_2,y_2,z_2;
int m1,m2,ans;
int main(){
    cin>>t;
    while(t--){
        cin>>x_1>>y_1>>z_1>>x_2>>y_2>>z_2;
        m1=min(x_1,z_2);x_1-=m1;z_2-=m1;
        m2=min(z_1,z_2);z_1-=m2;z_2-=m2;
        ans=(min(y_2,z_1)-min(y_1,z_2))*2;
        cout<<ans<<"\n";
    }
    return 0;
}
```



---

## 作者：Yizhixiaoyun (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1401B)

## 题目分析

本题思路考虑**贪心**。

我们不难发现，这题获得最大收益时就是 $(2,1)$ 的时候。所以我们将 $a$ 中的 0 去抵消掉 $b$ 中的 1 ，然后将$a$ 中的 2 去抵消掉 $b$ 中的 2 ，最后求 $\min(y2,z1) - \min(y1,z2)$ 就可以了。

## 贴上代码

```cpp
#include<iostream>
using namespace std;
int T;
int min(int a,int b){
	if(a<b) return a;
	else return b;
}
int main(){
    cin>>T;
    while(T--){
    	int x1,y1,z1,x2,y2,z2;
        cin>>x1>>y1>>z1>>x2>>y2>>z2;
        int min1=min(x1,z2);
        x1-=min1;z2-=min1;
        int min2=min(z1,z2);
        z1-=min2;z2-=min2;
        int ans=(min(y2,z1)-min(y1,z2))*2;
        cout<<ans<<endl;
    }
}
```

---

## 作者：huayucaiji (赞：1)

这个题就是直接贪心讨论即可。

我们来分析一下，其实这个题目 $c_i$ 的计算根本没那么麻烦.我们只需贪心计算。我们先尽可能让 $b$ 中的 $2$ 产生最小负面影响。我们第一选择是拿 $a$ 中的 $0$ 一个一个~~去送死~~抵消。再拿 $2$ 去抵消。最后才是 $1$ 因为只有此时每一对都会产生 $-2$ 的负面 BUFF。然后我们尽可能多的让 $a$ 中的 $2$ 产生正面 BUFF，和 $b$ 中的 $1$ 一个一个配对，剩下的随意排布都不会产生贡献或负贡献，算法就结束了。

```cpp
//Don't act like a loser.
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

int x[2],y[2],z[2];

signed main() {
	int T=read();
	while(T--) {
		for(int i=0;i<=1;i++) {
			x[i]=read();y[i]=read();z[i]=read();
		}
		
		int ans=0;
		
		int tmp=min(z[1],x[0]);
		z[1]-=tmp;
		x[0]-=tmp;
		if(z[1]) {
			int t1=min(z[1],z[0]);
			z[1]-=t1;
			z[0]-=t1;
			if(z[1]) {
				ans-=z[1]*2;
				y[0]-=z[1];
			}
		}
		
		ans+=min(z[0],y[1])*2;
		
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：xuezhe (赞：1)

容易发现真正能对结果造成贡献的只有 $2 \times 1$ 这一种可能。

所以直接考虑贪心。

首先尽可能用 $a$ 中的 $0$ 抵掉 $b$ 中的 $1$，再用 $a$ 中的 $2$ 抵 $b$ 中的 $2$，然后直接计算 $\min \lbrace z_1,y_2 \rbrace - \min \lbrace y_1,z_2 \rbrace$ 即可。

Code:
```cpp
int main(){
    int T,x1,y1,z1,x2,y2,z2;
    cin>>T;
    while(T--){
        cin>>x1>>y1>>z1>>x2>>y2>>z2;
        int t=min(x1,z2);
        x1-=t,z2-=t;
        t=min(z1,z2);
        z1-=t,z2-=t;
        cout<<(min(z1,y2)-min(y1,z2))*2<<'\n';
    }
    return 0;
}
```

---

## 作者：Azazеl (赞：1)

### CF1401B Ternary Sequence 题解  

#### 题意 

> $~~~~$ $A,B$ 序列为仅由 $0,1,2$ 组成的序列，$A$ 序列有 $x_1$ 个 $0$ ，$y_1$ 个 $1$，$z_1$ 个 $2$，$B$ 序列则分别为 $x_2,y_2,z_2$ 个。$C$ 序列是根据 $A,B$ 序列的排布组成的序列。求如何排布 $A,B$ 序列使得 $C$ 序列元素和最大。 



---

#### 题解

$~~~~$ 观察式子，不难发现正贡献仅可能来自 $A$ 序列的 $2$ 与 $B$ 序列的 $1$ ，因此考虑优先最大化正贡献。  

$~~~~$ 再来观察负贡献，同理仅可能来自 $B$ 序列的 $2$ 与 $A$ 序列的 $1$ ，因此考虑用 $A$ 序列剩下的 $0,2$ 去抵消 $B$ 序列的 $2$ ， $B$ 序列剩下的 $0,1$ 去抵消 $A$ 序列的 $1$ 即可，最后无法抵消的部分就是负贡献。  



---

#### 代码

（就这么个简单东西我考场上写挂了两次）

```cpp
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
int a0,a1,a2,b0,b1,b2;
int main() {
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d %d %d %d %d",&a0,&a1,&a2,&b0,&b1,&b2);
		int ans=0;
		if(a2>=b1)
		{
			ans+=b1*2;
			if(a0+a2-b1-b2<0) ans+=(a0+a2-b1-b2)*2;
		}
		else
		{
			ans+=a2*2;
			if(a0<=b2) ans+=(a0-b2)*2;	
		}
		printf("%d\n",ans);
	}
	return 0;
} 
```



---

## 作者：HYLD_WYB (赞：0)

## 老规矩，题目大意：
给出两个序列 $A,B$，对其进行排列构造一个新序列 $C$，使得 $C_{i}$ 最大，考虑到贪心的做法。
## 具体做法：
根据从 $C_{i}$ 最大值的定义：

1.当 $A_{i}>B_{i}$ 时，$C_{i}\gets A_{i} \times B_{i}$

2.当 $A_{i}=B_{i}$ 时，$C_{i}\gets0$

3.当 $A_{i}<B_{i}$ 时，$C_{i}\gets-(A_{i} \times B_{i})$

根据~~观察~~贪心可得出：
要尽量将 $(2,1)$ 搭配，其次将 $(2,0)$ 匹配，最后剩余的数据放在一起即可。

## 代码部分：
```
#include<bits/stdc++.h>
using namespace std;
int t,x1,yl,z1,x2,y2,z2;
int m1,m2,ans;
int main(){
    cin>>t;
    while(t--){
        cin>>x1>>yl>>z1>>x2>>y2>>z2;//输入
        m1=min(x1,z2);//将最小值减去
        x1-=m1;
        z2-=m1;
        m2=min(z1,z2);
        z1-=m2;
        z2-=m2;
        ans=(min(y2,z1)-min(yl,z2))*2;
        cout<<ans<<endl;
    }
    return 0;
}
```


---

## 作者：yhx0322 (赞：0)

## 题目简述
- 两个序列 $A, B$。这两个序列都是由 $0,1,2$ 这三个数构成。
- $x_1,y_1,z_1$ 和 $x_2,y_2,z_2$ 分别代表 $A$ 序列和 $B$ 序列中 $0,1,2$ 出现的次数。

- 你可以重新排列两个序列中的元素，然后生成一个新序列 $C$，$C$ 的生成规则如下：

$$C_i = \begin{cases}A_iB_i &A_i>B_i \\
0&A_i = B_i\\ -A_iB_i &A_i<B_i\end{cases}$$

求：所有排列的方案中，$C$ 序列所有元素之和的最大值。

## 思路
本题采用的算法：贪心、构造。

- 尽量地凑出 $(A_i,B_i)$ 为 $(2,1)$。
- $B_i=2$，则和 $A_i=0$ 的情况配对。
- 对于剩下的元素，把相同的元素配对。

## 代码
```c++
#include <bits/stdc++.h>

using namespace std;

int t;
int main() {
    scanf("%d", &t);
    int x1, y1, z1, x2, y2, z2;
    while (t--) {
        scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
        x1 -= min(x1, z2), z2 -= min(x1, z2);
        z1 -= min(z1, z2), z2 -= min(z1, z2);
        int ans = (min(y2, z1) - min(y1, z2)) << 1;
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：Miyamizu_Mitsuha (赞：0)

非常之水，贪心+模拟就好了。

只有 $(2,1)$ 会产生正贡献，所以贪心，最大化正贡献。

因为 $(1,2)$ 会产生负贡献，所以就用 $A$ 的 $0$ 抵掉 $B$ 的 $1$，$A$ 的 $2$ 抵掉 $B$ 的 $2$。



```
#include <iostream>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
    	int x1,y1,z1,x2,y2,z2;
        cin>>x1>>y1>>z1>>x2>>y2>>z2;
        int t1=min(x1,z2);
        x1-=t1,z2-=t1;
        int t2=min(z1,z2);
        z1-=t2,z2-=t2;
        cout<<2*(min(y2,z1)-min(y1,z2))<<endl;
    }
    return 0;
}
```


---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1401B)

主要思路：贪心与模拟。

通过 $C_i$ 的规定我们知道了三个重要的信息：

当 $2$ 和 $1$ 匹配时，贡献增加 $2$。

当 $1$ 和 $2$ 匹配时，贡献减少 $2$。

其余情况，贡献增加 $0$。


为了让结果最大，我们要多造成第一种情况，利用第三种情况不让第二种情况发生；保留序列 $A$ 的 $2$ 和序列 $B$ 的 $1$；消灭序列 $B$ 的 $2$ 和 $0$。

最首先想到的肯定是用 $A$ 序列的 $0$ 消灭掉 $B$ 序列的 $2$ 啦，如果 $0$ 不够就再用一些 $A$ 序列 $2$ 灭掉 $B$ 序列的残余的 $2$；否则用剩余的 $0$ 消灭 $B$ 序列的 $0$。

$B$ 序列中的 $0$ 也是个危险分子，有了它 $A$ 序列的 $2$ 就会消失，所以当 $0$ 用完时，$A$ 序列的 $1$ 便前赴后继，与 $0$ 同归于尽。不过不幸的是，无论最后哪一方多出，都要从贡献中扣掉一些。

总之，这是一道很好的贪心和模拟。

上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,x1,x2,x3;
int xy1,xy2,xy3;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>x1>>x2>>x3>>xy1>>xy2>>xy3;
		int tmp;
		tmp=x1;
		x1-=xy3;
		if(x1<=0)
		{
			x3-=(xy3-tmp);
		}
		else
			xy1-=x1;
		tmp=x2;
		x2-=xy1;
		if(x2<=0)
		{
			x3-=(xy1-tmp);
			xy1-=tmp;
		}
		else
			xy2-=x2;
		cout<<x3*2<<endl;
	}
	return 0;
}
```




---

## 作者：Limury (赞：0)

### 思路

将 $0,1,2$ 三个数字进行全排列后，不难发现只有当 $ai=2,bi=1$ 时， $ci$ 的值为 $2$ ，对答案有正贡献。而当 $ai=1,bi=2$ 时， $ci$ 的值为 $-2$ ，对答案有负贡献。我们需要找到答案的最大值，所以我们最大化 $ci=2$ 的情况，最小化 $ci=-2$ 的情况。不难发现为贪心思想。

具体一点，即是先用 $a2$ 去匹配 $b1$ 的情况，再求出去掉 $a2$ 情况后 $a1$ 和 $b2$ 的最小重合次数，即为最少的 $-2$ 次数。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=100005;
#define ll long long
ll a[maxn],T,t;

int main(){
	cin>>T;
	while(T--){
		ll a0,a1,a2,b0,b1,b2,sum=0;
		scanf("%lld%lld%lld%lld%lld%lld",&a0,&a1,&a2,&b0,&b1,&b2);
	 	t=min(a2,b1);
	 	a2-=t;
		b1-=t;
		ll x=a0+a1+a2-a1-b2;
		if(x>0){
			x=0;
		}
		sum+=2*t;
		sum+=2*x;
		printf("%lld\n",sum);
	} 
	return 0;
}
```


---

## 作者：KSToki (赞：0)

手模一下可以知道当 $a_i=2$ 且 $b_i=1$ 时 $c_i=2$，当 $a_i=1$ 且 $b_i=2$ 时 $c_i=-2$，其它情况 $c_i$ 都为 $0$。

所以先将 $a$ 所有的 $2$ 和 $b$ 中所有的 $1$ 配对，再将 $a$ 所有的 $1$ 与 $b$ 中不是 $2$ 的配对。如果此时 $a$ 中还有 $1$ 剩余就只能与 $b$ 中的 $2$ 配对了。易知此时如果将与 $a$ 中的 $2$ 配对的 $b$ 中的 $1$ 拿过来与剩余的 $1$ 配对的话结果是一样的，所以直接模拟即可。

代码~~忽略那个大写的 Y~~：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,x1,x2,Y1,y2,z1,z2,ans;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>x1>>Y1>>z1>>x2>>y2>>z2;
		ans=min(z1,y2)*2;
		y2-=min(z1,y2);
		Y1-=x2+y2;
		if(Y1>0)
			ans-=2*Y1;
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：fls233666 (赞：0)

先单独考虑序列的 $c$ 的第 $i$ 个位置。我们根据 $c_i$ 的产生方法，可以推断出以下三点：

- $c_i$ 能增加最终答案，**当且仅当 $a_i=2,b_i=1$ 时**。此时 $c_i$ 值为 $2$，会使最终答案增加 $2$。
- $c_i$ 会减少最终答案，**当且仅当 $a_i=1,b_i=2$ 时**。此时 $c_i$ 值为 $-2$，会使最终答案减少 $2$。
- 对于其它情况，$c_i$ **最终的值都是 $0$**。

题目要求 $\sum_{i=1}^{n}c_i$ 的**最大值**，我们就要使序列 $c$ 上能增加最终答案的位置尽可能多，能减少最终答案的位置尽可能少。于是我们又得出三条处理答案的规则：

- 考虑序列 $a$ 中 $2$ 数量和序列 $b$ 中 $1$ 的数量，尽可能地增加答案。
- 考虑序列 $a$ 中剩下的 $2$ 和 $0$ 的数量，以及序列 $b$ 中 $2$ 的数量，尽可能消掉序列 $b$ 中的 $2$。
- 考虑完上述两点后，由于序列 $c$ 的其它位置都会变成 $0$ ，因此不考虑剩下的其它数字。

由以上两条规则，我们得到了最终的代码：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;
int main(){
	ll test,a[3],b[3],ans;
	scanf("%lld",&test);
	while(test--){
    
		for(rgt i=0;i<3;i++) //读入数据
			scanf("%lld",&a[i]);
		for(rgt i=0;i<3;i++)
			scanf("%lld",&b[i]);
            
		ans=0;
     //计算序列 c 中增加答案的增加量
		if(a[2]>b[1]){
			ans+=b[1]*2;
			a[2]-=b[1];
			b[1]=0;
		}else{
			ans+=a[2]*2;
			b[1]-=a[2];
			a[2]=0;
		}
        
     //用序列 a 中的 0 和 2 把序列 b 中的 2 消掉
		if(b[2]>a[0]){
			b[2]-=a[0];
			a[0]=0;
		}else{
			a[0]-=b[2];
			b[2]=0;
		}
		if(b[2]>a[2]){
			b[2]-=a[2];
			a[2]=0;
		}else{
			a[2]-=b[2];
			b[2]=0;
		}
        
		ans-=b[2]*2;  //消不掉的要从最终答案中扣掉这部分
        
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：Ryo_Yamada (赞：0)

这题我们要明确，只有 $a_i = 2, b_i = 1$ 时才有 $c_i > 0$，$a_i = 1, b_i = 2$ 时才有 $c_i < 0$。

所以只需要把利益最大化，同时尽可能多地“消耗”$b_i=2$ 的数量。其他的不需要考虑，因为其他情况必定 $c_i = 0$。

$\text{Code}$：

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--) {
		int a, b, c, x, y, z, sum = 0;
		scanf("%d%d%d%d%d%d", &a, &b, &c, &x, &y, &z);
		int k = min(c, y);
		c -= k, y -= k;
		sum += k + k;//求出(2, 1)带来的最大收益
		k = b - x - y;//使用a[i]=2 和 a[i]=0 消耗 b[i]=2 的情况
		if(k > 0) {
			sum -= min(k, z) * 2;//如果还有，只能负增长
		}		
		printf("%d\n", sum);
	}
	return 0;
}


```


---

## 作者：EDqwq (赞：0)

### 这是一个结论+模拟题

***

简单尝试可知以下情况：    
1. 2与1配对可以加2分

1. 1与2配对可以扣2分
1. 其他情况加0分

**所以我们优先配对2,1，如果没有，就配对0的情况，在迫不得已的情况下才会让1和2配对。**
***
于是我用优先级写了一个$while$的代码，直接暴力模拟，发现$TLE$了...

转念一想，发现每一轮模拟可以直接选择两个数的最小值，将所有转换。

这时，好奇的小朋友就会问了：**这样不会WA吗，一次全部算完?**

其实不会，**由于我们已经优先级排序，所以无影响**，这也是用最小值和优先级的巧妙之处。
***
上代码，可以和注释配套食用:

```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
int t;
 
int main(){
	cin>>t;
	for(int i = 1;i <= t;i ++){
		int a0,a1,a2,b0,b1,b2;
		int ans = 0;
		cin>>a0>>a1>>a2;
		cin>>b0>>b1>>b2;
		int minn = min(a2,b1);//直接求min，然后两个数个数减去，min，全部算完之后肯定都用完了
		ans += minn * 2;
		a2 -= minn;
		b1 -= minn;
		minn = min(a1,b1);
		a1 -= minn;
		b1 -= minn;
		minn = min(a1,b0);
		a1 -= minn;
		b0 -= minn;
		minn = min(a0,b2);
		a0 -= minn;
		b2 -= minn;
		minn = min(a0,b1);
		a0 -= minn;
		b1 -= minn;
		minn = min(a2,b0);
		a2 -= minn;
		b0 -= minn;
		minn = min(a2,b2);
		a2 -= minn;
		b2 -= minn;
		minn = min(a0,b0);
		a0 -= minn;
		b0 -= minn;
		minn = min(a1,b2);
		a1 -= minn;
		b2 -= minn;
		ans -= minn * 2;
		cout<<ans<<endl;//输出答案
	}
	return 0;
}
```

---


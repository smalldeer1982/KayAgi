# Chunga-Changa

## 题目描述

Soon after the Chunga-Changa island was discovered, it started to acquire some forms of civilization and even market economy. A new currency arose, colloquially called "chizhik". One has to pay in chizhiks to buy a coconut now.

Sasha and Masha are about to buy some coconuts which are sold at price $ z $ chizhiks per coconut. Sasha has $ x $ chizhiks, Masha has $ y $ chizhiks. Each girl will buy as many coconuts as she can using only her money. This way each girl will buy an integer non-negative number of coconuts.

The girls discussed their plans and found that the total number of coconuts they buy can increase (or decrease) if one of them gives several chizhiks to the other girl. The chizhiks can't be split in parts, so the girls can only exchange with integer number of chizhiks.

Consider the following example. Suppose Sasha has $ 5 $ chizhiks, Masha has $ 4 $ chizhiks, and the price for one coconut be $ 3 $ chizhiks. If the girls don't exchange with chizhiks, they will buy $ 1 + 1 = 2 $ coconuts. However, if, for example, Masha gives Sasha one chizhik, then Sasha will have $ 6 $ chizhiks, Masha will have $ 3 $ chizhiks, and the girls will buy $ 2 + 1 = 3 $ coconuts.

It is not that easy to live on the island now, so Sasha and Mash want to exchange with chizhiks in such a way that they will buy the maximum possible number of coconuts. Nobody wants to have a debt, so among all possible ways to buy the maximum possible number of coconuts find such a way that minimizes the number of chizhiks one girl gives to the other (it is not important who will be the person giving the chizhiks).

## 说明/提示

The first example is described in the statement. In the second example the optimal solution is to dot exchange any chizhiks. The girls will buy $ 3 + 4 = 7 $ coconuts.

## 样例 #1

### 输入

```
5 4 3
```

### 输出

```
3 1
```

## 样例 #2

### 输入

```
6 8 2
```

### 输出

```
7 0
```

# 题解

## 作者：αnonymous (赞：2)

这道题其实很简单,用一点贪心就能AC了

### 重点：

最大值必为（x+y）/z，而最少移动个数则可以看两方的余数,再用余数小的一方往余数大的一方补足(使移动个数最小)
```cpp
#include <iostream>
using namespace std;
long long x,y,z,mini;
int main(){
	long long a,b,c;
	cin>>x>>y>>z;
	a=x%z;//余数计算
	b=y%z;
	if(a+b>=z)//和必须要能再买一个,否则在做无用功
		if(a>b)//使移动个数最少
			mini=z-a;
		else
			mini=z-b;
	cout<<(x+y)/z<<" "<<mini;
	return 0;
}
```


---

## 作者：_cmh (赞：1)

[原题传送门~](https://www.luogu.com.cn/problem/CF1181A)

## $\texttt{Description}$

给定两人钱数 $x,y$，糖果 $z$ 元，解决问题。共 $2$ 问。

- 第 $1$ 问，求最多购买的糖果数量。

- 第 $2$ 问，求一个人最少要给另一个人多少钱才能买到最多的糖果。

## $\texttt{Solution}$

看到题目范围是 $10^{18}$，明显，时间复杂度为 $\mathcal{O}(1)$。

对于第 $1$ 问，显然输出 $\large\frac{x+y}{z}$ 即可。

对于第 $2$ 问，显然两人剩余的钱能再买一个糖才可以继续进行。为了实现移动钱数最少的目的，输出时需判断剩余钱数后再输出。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
int main(){
	ll x,y,z;
	scanf("%lld%lld%lld",&x,&y,&z);
	printf("%lld ",(x+y)/z);
	x%=z;y%=z;
	printf("%lld",x+y>=z?((x>y)?z-x:z-y):0);
    return 0;
}
```


---

## 作者：Meatherm (赞：1)

这是我$Codeforces \#567(div.2)$唯一AC的题目，记忆犹新啊。

很明显，对于第一问，输出$(x+y)/z$（下取整）即可。因为想要买到尽可能多的东西，必须要尽可能地合理利用，使得剩下地钱数不超过$z$。

重点讨论第二问。

1.如果$z|x$并且$y|x$，那么根本不需要移多补少，因为都可以恰好用完。这种情况下第二问答案为$0$。

2.$x/z+y/z=(x+y)/z$。这种情况下移多补少之后的结果和不补是一样的，也就是说补没有意义（反而浪费操作次数），还不如不补，这种情况下第二问答案也为$0$。

3.如果上述两种情况都没有出现，则答案为$\min\{(x/z+1)*z-x,(y/z+1)*z-y\}|(x/z+1)*z-x≤y,(y/z+1)*z-y≤x$。

来解释一下第三个。首先，移多补少时最多补$z-1$个。如果超过了$z-1$，那么还不如把钱留在这里，让自己买一个。于是我们只需要分别算出两个人还要补多少钱才能再买一个，并取最小值。注意要补的钱必须小于另一个人所持有的钱数，因为“没有人愿意欠债”。

另外，为了保证程序的鲁棒性，可以加一些特判。


```
# include <bits/stdc++.h>
# define rr register
unsigned long long x,y,z;
int main(void){
    scanf("%I64d%I64d%I64d",&x,&y,&z);//Codeforces不支持%lld的格式，scanf输入long long型变量请使用%I64d形式
    printf("%I64d ",(x+y)/z);//第一问
    if((x+y)/z==0){
        printf("0");
        return 0;
    }
    if(x%z==0&&y%z==0||x/z+y/z==(x+y)/z){
        printf("0");
        return 0;
    }
    unsigned long long ans=1e18+10;
    if((x/z+1)*z-x<=y)
        ans=std::min(ans,(x/z+1)*z-x);
    if((y/z+1)*z-y<=x)
        ans=std::min(ans,(y/z+1)*z-y);
    if(ans==1e18+10)
        printf("0");
    else printf("%I64d",ans);
    return 0;
}
```

---

## 作者：灵光一闪 (赞：1)

~~抢前排！！~~

这题我重构了4次 ~~（我太弱了~~

然后……第5次……

# 这不就是个分类讨论吗？？？

首先，它们买了各自的。

1. 如果有一个余数为0就直接把各自的相加，给0元

1. 如果余数之和不够买一个的，参见第一条

1. 如果够购买一个的话就看下面：

伪代码：
``min(min(第一个人剩下的钱,第二个人剩下的钱),min(第一个人差多少钱,第二个人差多少钱))``

这就是要给多少钱



---------我是分割线--------

code:
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

using namespace std;
long long int n,m,k;
long long int num;
long long int n1,m1,n2,m2;
int main(){
    cin>>n>>m>>k;
    n1=n/k;
    m1=m/k;
    if(n1*k==n||m1*k==m){//有一个余数为0
        cout<<n1+m1<<" "<<0<<endl;
        return 0;
    }
    n2=n%k;
    m2=m%k;
    if(n2+m2>=k){//够买一个
        cout<<n1+m1+1<<" "<<min(min(n2,m2),min(k-n2,k-m2))<<endl;
        return 0;
    }
    else{//不够
        cout<<n1+m1<<" "<<0<<endl;
        return 0;
    }
    Please do not try to copy it.
    Although this code can pass.
}
```

---

## 作者：hxb13396344589 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1181A)
## Part 1 分析题目

题目大意

已知两人手中钱的数量，分别求两人能买的最多的糖果数量和~~要买到最多糖果数量~~其中一个人要给另一个人的钱数。

假设第一个人手中有 a 元，另一个人有 b 元，糖果的单价为 c 元。

第一个答案好判断，为
$\frac{a+b}{c}$。

但是第二个答案就不好做了，因为需要分类讨论。

1. 如果有人带的钱刚好可以买整数个糖，那么直接输出 0。
2. 如果两个人剩余的钱加起来不够买一个，那么同样输出 0。
3. 如果两个人剩余的钱加起来够买一个，见代码注释。

解释：

1. 如果一个人剩下的钱为 0，另一个人剩下的钱比 c 小，所以无法再买糖了，输出 0。
2. 两人所剩的钱无法再买了，输出 0。
3. 见代码注释。

## Part 2 代码
```c++
#include <iostream>
using namespace std;
#define int long long
main()
{
    ios::sync_with_stdio(false); ///输入输出加速
    int a,b,c;cin>>a>>b>>c;
    cout<<(a+b)/c<<" "; ///输出第一个答案，注意后面不能打 endl
    if ((a/c)*c==a || (b/c)*c==b){ ///判断 1，是否一人所剩钱为 0
        cout<<"0"<<endl;return 0;}
    if (a%c+b%c>=c){ ///判断 3，是否两人所剩的钱还能再买
        cout<<min(min(a%c,b%c),min(c-a%c,c-b%c))<<endl;
        /**
        这里用的公式是：min(min(a%c,b%c),min(c-a%c,c-b%c)),在两人剩余钱数较小的与两人买糖需要钱数较小的里面取最小值
        **/
        return 0;
    }
    else ///判断 2，是否两人所剩的钱不能再买
        cout<<"0"<<endl;
    return 0;
}

```

### [AC 记录](https://www.luogu.com.cn/record/77200265)

---

## 作者：Firstly (赞：0)

## **题目思路：**

容易发现，两人买的糖果的总数最多是 $\frac{x+y}{z}$ 个，因为两人一共就只有 $x+y$ 元，如果全部汇集到一起还不够买一些糖果，那么不可能有更优方案能够达到这个数字。

两人是分开买糖果的。如果两人买糖果剩下的钱没有达到 $z$ 元，那么再怎么给都会是徒劳的，也就是说不用给就能达到最优值。但是如果两人买糖果剩下的钱已经达到了 $z$ 元，那么经过一定的给钱，是可以再买一个的。

我们要最小化给的钱，那么就比较两人谁剩下的钱更接近 $z$ 元，帮这个人将钱补够即可。

## **Code：**

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long x,y,z;
int main(){
    cin>>x>>y>>z;
    cout<<(x+y)/z<<' ';
    long long xx=x%z,yy=y%z;
    if(xx+yy>=z)cout<<min(z-xx,z-yy);
    else cout<<0;
    return 0;
}
```


---

## 作者：XMK_萌新 (赞：0)

和别的题解同样是分类讨论但思路稍微有些不同              


$Case$ $1.$ 如果 $z$ $|$ $x$ 或者 $z$ $|$ $y$ 就说明至少有一个人刚好买够，那么另外一个人也不用借钱了，否则要么扯平要么少一个。所以输出 $x$ $/$ $z$ $+$ $y$ $/$ $z$ 和 $0$            

------------

$Case$ $2.$ 如果两个都不能整除（这里假设$x$ $mod$ $z$ $≤$ $y$ $mod$ $z$）。               
那么肯定要从$x$那里往$y$那补钱，理由很简单这样借的钱少嘛       
于是又分成两种情况：

------------

$Case$ $2.1.$ 如果$y$要补上$k$块才能刚好再买一块（易得：$k$ = $z$ $-$ $y$ $mod$ $z$）      
那么必须满足$x$ $mod$ $z$ $≥$ $k$。           
为什么？因为如果你给$y$补贴好了然后$x$买的时候少了一个没有意义，还是不变，并且还借钱了。       
所以在 $x$ $mod$ $z$ $<$ $k$ 的情况下你就不用借任何钱了，和 $Case$ $1$的输出一样    

------------

$Case$ $2.2.$ 如果$x$ $mod$ $z$ $≥$ $k$ 那么就让$x$减去$k$，$y$加上$k$                
所以借的钱就是$k$               



$CODE:$
```cpp
#include <iostream>
using namespace std;
long long x,y,z;
int main()
{
	cin>>x>>y>>z;
	if(x%z>y%z) swap(x,y);
	if(x%z==0LL||y%z==0LL) cout<<x/z+y/z<<" "<<0;
	else
	{
		long long k=z-y%z;	//the value to plus (or minus)
		if(x%z<k) cout<<x/z+y/z<<" "<<0;
		else
		{
			x-=k; y+=k;
			cout<<x/z+y/z<<" "<<k;
		}
	}
	return 0;
} 

```

---


# Cola

## 题目描述

To celebrate the opening of the Winter Computer School the organizers decided to buy in $ n $ liters of cola. However, an unexpected difficulty occurred in the shop: it turned out that cola is sold in bottles $ 0.5 $ , $ 1 $ and $ 2 $ liters in volume. At that, there are exactly $ a $ bottles $ 0.5 $ in volume, $ b $ one-liter bottles and $ c $ of two-liter ones. The organizers have enough money to buy any amount of cola. What did cause the heated arguments was how many bottles of every kind to buy, as this question is pivotal for the distribution of cola among the participants (and organizers as well).

Thus, while the organizers are having the argument, discussing different variants of buying cola, the Winter School can't start. Your task is to count the number of all the possible ways to buy exactly $ n $ liters of cola and persuade the organizers that this number is too large, and if they keep on arguing, then the Winter Computer School will have to be organized in summer.

All the bottles of cola are considered indistinguishable, i.e. two variants of buying are different from each other only if they differ in the number of bottles of at least one kind.

## 样例 #1

### 输入

```
10 5 5 5
```

### 输出

```
9
```

## 样例 #2

### 输入

```
3 0 0 2
```

### 输出

```
0
```

# 题解

## 作者：SUNCHAOYI (赞：5)

我们从容积较大的$2L$开始循环速度更快，那么循环次数应该为多少次呢？    
如果每种都有无限瓶，那么最多只要买$\frac{n} {2}$瓶就够了；但是如果这种的数量$c$小于$\frac{n} {2}$瓶，那么我们最多只能买$c$瓶了。因此，$c$种可乐我们最多只能买$min(\frac{n} {2},c)$瓶。这样我们就得到了第一层循环。
```
for(int i = 0;i <= min(n / 2,c);i++)
//注意，每种饮料都可以不买，所以应该从0开始循环
```

同理，我们可以得到$1L$的第二层循环：
```
for(int j = 0;j <= min(n,b);j++)
//n / 1 = n
```
那么我们还要第三层循环吗？答案是不需要。我们根据前两层循环，便能推算出$a$种可乐的数量。   
因为$b,c$两种的可乐的容积都是整数，所以$n - 2 * b - c$为剩下的，一定是整数，即一定能被$a = 0.5L$除尽，因此只要确保数量不小于$0$且数量不超过$a$即可。判断不超过$a$很简单，只要把$0.5$变为$*10 / 5 = *2$判断就行。

------------

**最终代码：**
```
#include <iostream>
using namespace std;
int main()
{
	int n,a,b,c,ans = 0;
	cin>>n>>a>>b>>c;
	for(int i = 0;i <= min(n / 2,c);i++)//最大的数量 
		for(int j = 0;j <= min(n,b);j++)
			if((n - i * 2 - j)  * 2 <= a && n - i * 2 - j >= 0) ans++;//符合条件 
	cout<<ans<<endl; 
	return 0;
}

```



---

## 作者：灵光一闪 (赞：3)

本解或成题解区最短解？
很简单，就是枚举，具体注释在代码里：
```
//#include<bits/stdc++.h>

#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<vector>
#include<string>
#include<cmath>
#include<map>
#include<string.h>

using namespace std;

int main()
{
    int n,a,b,c;//明明int就够了，为啥某位dalao要开long long？
    cin>>n>>a>>b>>c;
    int ans=0;
    for(int i=0;i<=a;i+=2)//这里a要2个2个加，因为n一定是个整数
        for(int j=0;j<=c;j++)//我枚举的是a和c，因为b是正好1
            if(n-(i/2+j*2)<=b&&n-(i/2+j*2)>=0)//既不能超过b又不能超过总数量（可以等于
                ans++;
    cout<<ans;//完美OK
    return 0;//不要吐糟我的头文件，我们教练最近在讲DFS和字符串，懒人必备的缺省源
}
```

---

## 作者：CrTsIr400 (赞：2)

### ~~恶评~~
### 模拟题一道，一个个枚举，连搜索都不用
### 核心代码 ~~（似乎大家都写的差不多）~~
```cpp
for(int i=0;i<=a;i+=2)//2个2个加（别问为什么）
for(int j=0;j<=c;j++)//因为b=1
if((n-(i/2+j*2)<=b)&&(n-(i/2+j*2)>-1))sum++;//判断
```
### 简单明了，用不着多说
### ~~完整代码不给了~~

---

## 作者：_C_H_M_ (赞：2)

由于买的可乐数n为整数，就可以把2个0.5L的看作1个1L的，(若a为奇数，必有1个0.5L的没用）然后n^2~~暴力~~枚举买1L、2L的数量，再加上1L用2*0.5L代替的方案数即可~

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
long long ans=0,n,b,c,i,j,x,y;
int main(){
    scanf("%lld%lld%lld%lld",&n,&x,&y,&c);
    b=x/2+y;
    for(i=0;i<=b;i++)
        for(j=0;j<=c;j++)
            if(i+j*2==n){
                if(j*2==n){
                    ans++;
                    continue;
                }
                if(max(x/2,y)>=i) ans+=min(i+1,min(x/2,y)+1);   
                else ans+=min(x/2,y)-(i-max(x/2,y))+1;  
            }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：BADFIVE (赞：1)

**题意：** 有 $a$ 瓶 $0.5$ $L$ 的可乐，$b$ 瓶 $1$ $L$ 的可乐，$c$ 瓶 $2$ $L$ 的可乐，求购买 $n$ $L$ 可乐的方案数   
**思路：** 我们可以暴力枚举所以的情况，然后再加起来，显然这个会超时。   
那我们可以先枚举后面两种情况的可乐，也就是 $1L$ 和 $2L$ 的，因为 $0.5$ 既是 $1$ 的因数也是 $2$ 的因数，所以这里可以不用枚举。我们可以根据两个 $for$ 推举出 $a$ 种可乐的个数，也就是 $n-i \ast 2-j$ ，我们只需要判断 $a$ 是否能被 $0.5$ 整除就可以了，当然 $a$ 的数量必须是 $\ge 0$

$codes:$
```
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,a,b,c,ans=0,sum;
    cin>>n>>a>>b>>c;
    for(int i=0;i<=c;i++){
        for(int j=0;j<=b;j++){
            sum=n-i*2-j;
            if(sum>=0&&a*0.5>=sum)ans++;
        }
    }
    cout<<ans;
}
```

---

## 作者：sinsop90 (赞：1)

这道题的核心思想主要还是暴力,可以稍微分析一下时间复杂度

我们会发现如果我们使用双层 $for$ 循环枚举,是不会超时的

因此我们有了这样的思路:

1.第一种$0.5$升不好枚举,我们枚举第二种和第三种

2.如果 $n$ 减去第二种的数量加上第三种的数量$*2$ 之后剩下的能被第一种凑够,$ans ++ $

我们考虑如何判断剩下的能不能被第一种凑够:

一个数除以 $0.5$ 等于这个数乘 $2$ 因此没必要定义$double$

如果剩下的是负数$($也就是第二种第三种加起来超过了$n$$)$ , 显然是不行的

于是有了下述代码:

```
#include<bits/stdc++.h>
using namespace std;
int n, a, b, c;
int ans;
int main() {
	scanf("%d%d%d%d", &n, &a, &b, &c);
	for(int i = 0;i <= b;i++) {//第二种
		for(int j = 0;j <= c;j++) {//第三种
			int count = i + j * 2;//第二种和第三种加起来
			if((n - count) * 2 <= a && (n-count) * 2 >= 0) {//除以0.5等于乘2
				ans++;
			}
		}
	}
	cout << ans << endl;
}
```


---

## 作者：chl123123 (赞：0)

此题为一道暴力的题目，我们首先会想到三层循环：
```cpp
for(int i=0;i<=a;i++)
	for(int j=0;j<=b;j++)
		for(int k=0;k<=c;k++)//时间复杂度为O(a*b*c) 
```
但一看数据范围便可知肯定超时

其次，我们想到优化“能算就算”，便只有两层循环
```cpp
for(int i=1;i<=a;i++)
	for(int j=1;j<=b;j++)
		c=n-a*0.5-b;//时间复杂度为O(a*b)
```
可还是可以优化，不然还是有超时的可能

我们想到如果总容量超过目标容量，则后面的循环都不用进行了
```cpp
for(int i=0;i<=min(n/2,c);i++) //如果0.5*a超过n就不用进行了
	for(int j=0;j<=min(n,b);j++)//同理
		if(n-(i*2)-j>=0&&2*n-i*4-j*2<=a) ++ans;//最后特判一下了
```
最后 [AC](https://www.luogu.com.cn/record/54518009)

---

## 作者：午尘 (赞：0)

觉得这题是道挺有趣的暴力呢……


------------


先放代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,i,j,k,a,b,c,ans;
int main(){
	scanf("%d%d%d%d",&n,&a,&b,&c);
	a=a/2;ans=0;
	for (i=0;i<=a;i++)
	  for (j=0;j<=b;j++)
	    if (i+j<=n && i+j+2*c>=n && (n-i-j)%2==0) ans++;
	printf("%d\n",ans);
  return 0;
}
```


------------
然后是一些解释啦……

```cpp
  a=a/2;    
 //因为n为整数，所以不可能用奇数个0.5升的，所以就可以看为a/2个1升的喽……
```

```cpp
//接下来是一些if判断条件的
i+j<=n   //为了保证不超过
i+j+2*c>=n  //2升的极限是2c升，为了保证能到n升
(n-i-j)%2==0  //一开始没考虑到，就是需要加的升数得能被2整除w

```




---

## 作者：happybob (赞：0)

这题是个暴力题目，挺水

代码来了，2重循环，1.06s

```cpp
#include <cstdio>

inline int read()//快读
{
    int x = 0;
    char ch = getchar();
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}

#define min(x, y) (x < y ? x : y)//宏定义

int main()
{
    int n, a, b, c, ans = 0;
    n = read();
    a = read();
    b = read();
    c = read();
    for(register int i = 0; i <= min(n / 2, c); i++)
    {
        for(register int j = 0; j <= min(n, b); j++)
        {
            if((n - i * 2 - j) * 2 <= a && n - i * 2 - j >= 0)
            {
                ans++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
```


---


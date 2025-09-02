# The Monster

## 题目描述

A monster is chasing after Rick and Morty on another planet. They're so frightened that sometimes they scream. More accurately, Rick screams at times $ b,b+a,b+2a,b+3a,... $ and Morty screams at times $ d,d+c,d+2c,d+3c,... $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF787A/23c11249630f1c4252ef0b9cda8ec1bf9b317b5a.png)The Monster will catch them if at any point they scream at the same time, so it wants to know when it will catch them (the first time they scream at the same time) or that they will never scream at the same time.

## 说明/提示

In the first sample testcase, Rick's $ 5 $ th scream and Morty's $ 8 $ th time are at time $ 82 $ .

In the second sample testcase, all Rick's screams will be at odd times and Morty's will be at even times, so they will never scream at the same time.

## 样例 #1

### 输入

```
20 2
9 19
```

### 输出

```
82
```

## 样例 #2

### 输入

```
2 1
16 12
```

### 输出

```
-1
```

# 题解

## 作者：Alex_Wei (赞：14)

模拟+初级数论

设 $k=gcd(a,c)$

$b+ax=d+cy$ 有解，当且仅当 $k|d-b$

简要证明

整理，得 $ax-cy=d-b$

$∵a,b,c,d$ 为常数

$∴$ 根据贝祖定理，该方程有解当且仅当 $k|d-b$

得证

在判断有没有解之后，就可以放心模拟了

当 $b\ !=d$ 时，如果 $b<d$，则 $b+=a$，否则 $d+=c$，直到 $b=d$

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d;
int gcd(int i,int j){return !j?i:gcd(j,i%j);}//求gcd
int main()
{
	cin>>a>>b>>c>>d;
	if((d-b)%gcd(a,c))cout<<-1,exit(0);//判断是否有解
	while(b!=d)b<d?b+=a:d+=c;//模拟
	cout<<b;
	return 0;
}
```

当然，用扩欧也是可以滴，不过稍微有些麻烦

求赞QWQ

---

## 作者：xujian (赞：3)

楼下的几位大佬们的代码都好复杂啊，蒟蒻来奉上自己的简洁代码。

这题考察双重循环的模拟，比较适合循环的初学者练题。题目的意思就是求什么时候b+i*a=d+j*c，满足此条件就直接输出然后return 0，因为这肯定是最小的答案，不用向楼下那位大佬再给答案全部排一遍序了。

### 另外，就是要注意边界值问题，i和j如果太大，双重循环会超时。而太小则会精度不够，全部WA掉，所以精度的控制十分的关键。个人建议i和j到100就足够了。

代码如下↓：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,c,d;
    const int bj=100;
    cin>>a>>b>>c>>d;
    for(int i=0;i<=bj;i++)
        for(int j=0;j<=bj;j++)
            if((b+a*i)==(d+c*j)){
                cout<<b+a*i;return 0;
            }
    puts("-1");
    return 0;
}
```

附：[AC记录：888ms，12kb](https://www.luogu.org/recordnew/show/14946685)

~~求管理大大给过。~~

---

## 作者：_Empty (赞：2)

这道题的数据含水量极高

只要用两个for循环嵌套就可以了

```c
#include <bits/stdc++.h>  	//万能头文件
#include <assert.h>　　　　	//设定插入点
#include <ctype.h>　　　	 //字符处理
#include <errno.h>   　　　//定义错误码
#include <float.h>　　　   //浮点数处理
using namespace std;
int a1=0,a2=0,a3=0,a4=0;//“=0”加不加都一样
int main(){
	cin>>a1>>a2>>a3>>a4;//输入
	for (int x=0;x<=99999;x++)//循环*1（看别的大佬的题解似乎100就够了
		for (int y=0;y<=99999;y++)//循环嵌套（我就开个99999吧
			if (a2+x*a1==a4+y*a3){//判断
				cout<<a2+x*a1;//输出
          	return 0;
			}	
	cout<<-1;//如果判断不成功输出-1
	return 0;//华丽收尾
}
```

# 每一个代码字母都是自己手打出来的
# 莫抄题解
# 除非宁想宗明

###### 希望管理大大通过

---

## 作者：Cutest_Junior (赞：1)

## 题解 CF787A 【The Monster】

### 题意

+ 求一个最小的 $x$，使 $x>b$ 且 $x>d$ 且 $a|(x-b)$ 且 $c|(x-d)$，
+ $1\le a,b,c,d\le100$。

### 做法

可以想到 $x$ 不会大于 $a\times c+\max(b,d)$，否则，就一定存在一个更小的数 $x-a\times c$，满足题目中的条件。

因为 $1\le a,b,c,d\le100$，所以 $a\times c+\max(b,d)\le10100$。

因为很小，直接枚举即可。

### 代码

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
	int a, b, c, d;
	scanf("%d%d%d%d", &a, &b, &c, &d);

	for (int i = max(b, d); i <= 10000; ++i) {
		if (i % a == b % a && i % c == d % c) {
			printf("%d", i);
			return 0;
		}
	}

	printf("-1");
}
```

---

## 作者：耶耶小朋友 (赞：1)

### 思路:
先看数据范围 $(1≤n,m≤100)$，那就不是暴力吗？

那就模拟呗。

### 提示：
- $mx$ 为模拟次数最大值（当然可以更大）。
- $x,y$ 为当前两人尖叫的时刻。

### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mx = 100;
int main () {
	std::ios::sync_with_stdio(false);
	int a,b,c,d;
	cin >> a >> b >> c >> d; 
   	//模拟
	int x,y; 
	for (int i = 0;i <= mx;i++) {
		x = b + a * i;
		for (int j = 0;j <= mx;j++) {
			y = d + c * j;
			if (x == y) {
				cout << x << endl;
				return 0; 
			}
		}
	}
	cout << "-1";
	return 0;
}

```


---

## 作者：肖恩Sean (赞：1)

#### 套用扩展欧几里得求一元线性同余方程
将原式视为

x≡b(mod a)

x≡d(mod c)

然后用扩展欧几里得合并为

x≡f(mod e)

大于max(a,c)的最小解即可

```cpp
#include<bits/stdc++.h>
#define LL long long
#define For(i,l,r) for(int i=(l);i<=(r);++i)
#define ReFor(i,l,r) for(int i=(l);i>=(r);--i)
using namespace std;
int a1,a2,r1,r2,tmp;
int read(){
	int x=0,f=1;char c;
	while(c<'0'||c>'9'){if(c=='-') f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int exgcd(int a,int b,int &x,int &y){
	if(!b){x=1;y=0;return a;}
	int tmp=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return tmp;
}
int main(){
	a1=read();r1=read();a2=read();r2=read();tmp=max(r1,r2);
	int c=r2-r1,x0,y0,d=exgcd(a1,a2,x0,y0);
	if(c%d){printf("-1\n");return 0;}
	int t=a2/d;
    x0=(x0*(c/d)%t+t)%t;
    r1=a1*x0+r1;
    a1=a1*(a2/d);
    while(r1<tmp) r1+=a1;
	printf("%d\n",r1);
	return 0;
}

```

---

## 作者：OdtreePrince (赞：1)

# -模拟-

纯粹的模拟，找到了，排序输出，找不到，输出-1

前面对奇偶的判断完全可以省略，主要是受样例影响

神犇不要介意！^-^

管理员给通过哦！

~~~
#include<bits/stdc++.h>
using namespace std;
int aa[20000000],k,i=0,a,b,c,d;
int main(){
    scanf("%d%d%d%d",&a,&b,&c,&d);
    if((b%2==1&&a%2==0&&d%2==0&&c%2==0)||(b%2==0&&a%2==0&&d%2==1&&c%2==0)){
    	cout<<"-1";
    	return 0;
    }//不加这一判断也罢
    for(int i=0;i<=5000;i++){
    	for(int j=0;j<=5000;j++){
    		if(b+i*a==d+j*c){
    			aa[++k]=b+i*a;
            }
        }
    }
    if(k==0){
        cout<<-1;
        return 0;
    }
    sort(aa+1,aa+k+1);
    cout<<aa[1];
    return 0;
}
~~~

---

## 作者：李至擎 (赞：0)

[点我看题](https://www.luogu.com.cn/problem/CF787A)

看到各位dalao都用了很高大上的方法，那我就来丢人现眼了。

思路：暴力枚举 $a$ 和 $c$ 的乘数，计算答案。

方法（以一次枚举为例）：

- $1.$ 枚举 $a$ 和 $c$ 的乘数；

- $2.$ 判断是否相等；

- $3.$ 如果相等，就输出答案。

细节：

- 因为第一个式子分别是 $b$ 和 $d$ ，所以枚举的起点是 $0$ 而不是 $1$ 。

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
int a,b,c,d;//a、b、c、d如题意 
int main()
{
	cin>>a>>b>>c>>d;//输入
	for(int i=0;i<=100;i++)//循环*1 
	{
		for(int j=0;j<=100;j++)//循环*2 
		{
			if(b+a*i==d+c*j)//判断
			{
				cout<<b+a*i;//输出
				return 0;//结束程序 
			}
		}
	}
	cout<<-1;//如果找不到输出-1
    return 0;//结束程序 
}
```

---

## 作者：sodak (赞：0)

## 思路
柿子其实就是$k1*a-k2*c=d-b$，可以用$exgcd$求一组最小非负解，然鹅我太懒了，写了个暴力，一个一个加，模拟就可以了

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define re register 
#define gc getchar()
#define getch while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=gc;}
#define getnu while(ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+ch-'0';ch=gc;}
using namespace std;
inline int read(){int s=0,f=1;char ch=gc;getch;getnu;return s*f;}
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int main(){
	int a=read(),b=read(),c=read(),d=read();
	int ans=d-b;int g=gcd(a,c);
	if(ans%g)return puts("-1"),0;
	while(b!=d)b<d?b+=a:d+=c;
	printf("%d\n",b);
}
```

---

## 作者：happybob (赞：0)

这道题和数论似乎有些关系，但我怎么想也想不出公式（我才小学5年级），于是只好循环了。

先说说为啥两层循环：

首先在同时尖叫时候，第一个人尖叫的可能第a次，第二个人可能是跟a差很多的，所以需要两层循环。本题限时1.00s，电脑一秒算一亿次，所以两次循环均要小于sqrt(100000000)，循环次数是i * j， a，b，c，d都小于100，不用算很多次的。

两层循环，代码如下，O(105 * 105)，707ms：

```
#include <iostream>
using namespace std;

int main()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int x1 = b, x2 = d;
    for(int i = 0; i <= 105; i++)
    {
        x1 = b + a * i;
        for(int j = 0; j <= 105; j++)//注意循环从0开始，因为可能b和d相等，从1开始的话第一人第一次的b和第二人第一次的d就没了……
        {
            x2 = d + c * j;
            if(x1 == x2)
            {
                cout << x1 << endl;
                return 0;
            }
        }
    }
    cout << "-1\n";
    return 0;
}
```

---

## 作者：Contemptuous (赞：0)

由于此题数据范围较小，因此暴力也能过。

我们可以用两个$for$循环，然后判断$b+i*a$是否等于$d+j*c$，如果等于就输出$b+i*a$，结束程序。

如果在$10000$次循环后还没有成立，就输出$-1$。

上代码。
```cpp
#include <iostream>

using namespace std;

int main()
{
	
	int a, b, c, d;
	
	cin >> a >> b >> c >> d;
	
	for (int i = 0; i <= 100; ++i)
	{
		for (int j = 0; j <= 100; ++j)
		{
			if ((b+i*a) == (d+j*c))
			{
				cout << b+i*a << endl;
				return 0;
			}
		}
	} 
	
	cout << "-1";
	
	return 0;
}
```

---

## 作者：Thomas_Cat (赞：0)

这题一个词：暴力

暴力循环，建议到200就好 ~~数据太水~~

直接上代码

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main()
{
    int a,b,c,d;//定义输入
    cin>>a>>b>>c>>d;//输入
    int ascream=b,bscream=d;//这里比较形象（划掉）a尖叫的时候和b尖叫的时候一开始就定义成b和d，就不用后边在for循环里面麻烦的加上
    for(int i=1;i<=200;i++)//暴力循环，建议到200就好 数据太水（划掉）
    {
        for(int j=1;j<=200;j++)//同上
            if((ascream+a*i)==(bscream+c*j)) {//如果两个尖叫时间相同
                cout<<ascream+a*i;     //输出任意一个
                return 0;//直接退出
            }
    }
    cout<<"-1";//否则输出-1
    return 0;//华丽结束
}
```

---


# Grandfather Dovlet’s calculator

## 题目描述

Once Max found an electronic calculator from his grandfather Dovlet's chest. He noticed that the numbers were written with seven-segment indicators ([https://en.wikipedia.org/wiki/Seven-segment\_display](https://en.wikipedia.org/wiki/Seven-segment_display)).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF620B/67b24c9a2393a33eff16b95f90d96d29b0d56e85.png)Max starts to type all the values from $ a $ to $ b $ . After typing each number Max resets the calculator. Find the total number of segments printed on the calculator.

For example if $ a=1 $ and $ b=3 $ then at first the calculator will print $ 2 $ segments, then — $ 5 $ segments and at last it will print $ 5 $ segments. So the total number of printed segments is $ 12 $ .

## 样例 #1

### 输入

```
1 3
```

### 输出

```
12
```

## 样例 #2

### 输入

```
10 15
```

### 输出

```
39
```

# 题解

## 作者：Anomie (赞：3)

**[题目传送门](https://www.luogu.com.cn/problem/CF620B)**

## 大意

用火柴棒摆数字，求摆 $ a $ 到 $ b $ 间的数字共用多少根火柴棒。

## 思路

数据较小，可以直接模拟。先把 $ 0 \sim 9 $ 各自用的火柴棒数量存到一个数组里，然后逐位计算，把每位的火柴数都累加到答案里就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
int a,b,s,number[10]={6,2,5,5,4,5,6,3,7,6};//存各个数字用的火柴棒数量的数组
int main(){
    scanf("%d%d",&a,&b);
    for(int i=a;i<=b;i++){
    	int j=i;//不能直接用i，会改变i在循环中的值
    	while(j) s+=number[j%10],j/=10;//s是统计答案的变量
    }
    printf("%d",s);
    return 0;//完结撒花~
}
```


---

## 作者：Juruoviet (赞：2)

### 题目大意：

用火柴棒摆数字，求要用多少个火柴棒

### 思路：

这题主要就是枚举，先把每个数字需要的火柴根数在数组里面标好，然后再进行取数位，把每个位对应的根数累加到变量里，最后输出就行了。

### CODE：
```cpp
#include <iostream>
using namespace std;
int a[10]={6,2,5,5,4,5,6,3,7,6};//先把每个数字需要的火柴数量开个数组
int len(int n){//取长度的函数
	if(n<10){
		return 1;
	}
	return len(n/10)+1;
	
}
int f(int a,int b){//取数位的函数
	if(len(a)-b==0){
		return(a%10);
	}
    return f(a/10,b);
}
int main(){
	int l,r,ans=0;
	cin>>l>>r;
	for(int i = l; i <= r; i++){
		int k=len(i);//取长度
		for(int j = 1; j <= k; j++){//取数位
			int b=f(i,j);
			ans+=a[b];//累加根数
		}
	}
	cout << ans <<endl;
	return 0;//完美AC
}
```


---

## 作者：zhenjianuo2025 (赞：1)

### Solve
注意到数据范围较小外加数据很水，我们只需要枚举 $[l,r]$ 区间内的所有数字，计算其各个数位上数字的贡献之和就行啦。

可以把 $0\sim 9$ 这 $10$ 个数字的贡献储存在数组中，到时候直接以下标进行访问即可。

### Code
```cpp
#include <iostream>
using namespace std;
const int w[15] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};   // 0~9 每个数字的贡献
int l, r;
int main() {
	cin >> l >> r;
	int ans = 0;
	for (int i = l; i <= r; i++) {
		int t = i;
		while (t) {
			ans += w[t % 10];   // 计算各个数位上数字的贡献
			t /= 10;
		}
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：lovely_hyzhuo (赞：1)

本题题意：用火柴棒摆出从 $l$ 到 $r$ 的所有数，问要多少根火柴。

上面给出了从 $0$ 到 $9$ 的十个数字所需的火柴棒根数，就将 $l$ 到 $r$ 的所有数拆分成 $x$ 位，然后根据是第几个数，按题意枚举即可。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10]={6,2,5,5,4,5,6,3,7,6};
int sum=0;
void chaifen(int n)
{
	while(n!=0)
	{
		int t=n%10;
		n/=10;
		sum+=a[t];
	}
}
int main()
{
	int l,r;
	cin>>l>>r;
	for(int i=l;i<=r;i++)
	{
		chaifen(i);
	}
	cout<<sum;
	return 0;
}
```


---

## 作者：arrow_king (赞：1)

观察数据范围，$1\leq l\leq r\leq10^6$，所以毫不犹豫开始**模拟**。

## 思路

显然，一个数一个数来求“贡献”是不现实的，所以我们可以进行递推。

如何递推呢？

我们可以发现，一个数字的贡献可以表示为每个数位的贡献之和。设 $f(x)$ 表示 $x$ 的贡献，则有：

$$f(x)=f\left(\left\lfloor\dfrac{x}{10}\right\rfloor\right)+f\left(x\bmod10\right)$$

也就是 $x$ 的贡献就是 $x$ 的最后一位的贡献加前面的贡献，而 $x$ 前面的贡献有相当于 $x$ 的前面的最后一位的贡献加 $x$ 的前面的前面的贡献……

所以这时候就可以递推了，初始条件为 $f_0,f_1,\dots f_9$ 的贡献，一直递推到 $f_{100000}$。

**初始条件：**

|$f_0$|$f_1$|$f_2$|$f_3$|$f_4$|$f_5$|$f_6$|$f_7$|$f_8$|$f_9$|
|-|-|-|-|-|-|-|-|-|-|
|$6$|$2$|$5$|$5$|$4$|$5$|$6$|$3$|$7$|$6$|

## 完整代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long f[2000005],ans;
int l,r;
int main() {
	f[0]=6;
	f[1]=2;
	f[2]=5;
	f[3]=5;
	f[4]=4;
	f[5]=5;
	f[6]=6;
	f[7]=3;
	f[8]=7;
	f[9]=6;    //初始条件
	for(int i=10;i<=1000000;i++) f[i]=f[i/10]+f[i%10];    //递推式
	scanf("%d%d",&l,&r);
	for(int i=l;i<=r;i++) ans+=f[i];    //直接累加就可以
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：AKPC (赞：0)

### 题目描述
给定 $n,m$ 作为区间的左端和右端，用火柴棒依次拼出区间内所有数字，求出需要多少火柴棒。
### 注意
- 记得判断位数（$n,m$ 可以是多位数）！
- 这里的数可以区间跨位（$n$ 和 $m$ 位数不同）。
### 题目正解
首先先写两个函数方便写```main()```：一个判断数字的位数，一个判断数的第 $w$ 位数字。
```cpp
int wei(int x){   //这个函数用来判断数字的位数
	return log10(x)+1;
}
int fwei(int x,int w){   //判断x的第w位数字
	return x%(int)pow(10,w)/(int)pow(10,w-1);
}
```

接着可以写主函数了。既然这里的数可以是多位数，甚至区间跨位，那么我们设定两层循环，第一层枚举每个数字，第二层枚举数字的位数即可。
```cpp
for (int i=n;i<=m;i++)   //枚举每个数字
		for (int j=1;j<=wei(i);j++)   //枚举数字的位数
			ans+=f[fwei(i,j)];
```
### 贴代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long   //不开long long见祖宗
const int f[10]={6,2,5,5,4,5,6,3,7,6};   //单个数数位火柴个数打表
int n,m,ans=0;   //n,m分别是数字区间的左端和右端，ans统计结果
int wei(int x){   //这个函数用来判断数字的位数
	return log10(x)+1;
}
int fwei(int x,int w){   //判断x的第w位数字
	return x%(int)pow(10,w)/(int)pow(10,w-1);
}
signed main(){
	cin>>n>>m;
	for (int i=n;i<=m;i++)   //枚举每个数字
		for (int j=1;j<=wei(i);j++)   //枚举数字的位数
			ans+=f[fwei(i,j)];   
	cout<<ans;
	return 0;
}
```
为了您和他人的健康，请不要在洛谷抄我的代码，谢谢。

---

## 作者：EthanC_ (赞：0)

### 题意
用若干根火柴棒摆数字，求 $ l \sim  r $ 之间共用多少根火柴棒。
### 思路
因为本题数据较小，我们可以直接模拟。我们先把 $ 0 \sim  9 $ 各自需要的火柴棒数存入一个数组，然后把 $ l \sim  r $ 区间中的各个数逐位计算所需的火柴棒数量并存入一个变量中。下面给出 $ 0 \sim  9 $ 火柴棒所需个数。

| 数字 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 火柴个数 | 6 | 2 | 5 | 5 | 4 | 5 | 6 | 3 | 7 | 6 |

讲的很详细了，简单的代码就不给了。


---

## 作者：jimmyfj (赞：0)

思路：由图知，$0 \sim 9$ 的贡献值分别为 $6$，$2$，$5$，$5$，$4$，$5$，$6$，$3$，$7$，$6$。

再仔细观察，我们发现 $0$，$6$，$9$ 的贡献值相同，都是 $9$。同样的，$2$，$3$，$5$ 的贡献值也相同。剩下的就是不相同的贡献值。

我们将其分为 $6$ 类：

1. $0$，$6$，$9$ 为一类，贡献值为 $9$。

2. $2$，$3$，$5$ 为一类，贡献值为 $5$。

3. $1$ 单独为一类，贡献值为 $2$。

4. $4$ 单独为一类，贡献值为 $4$。

5. $7$ 单独为一类，贡献值为 $3$。

6. $8$ 单独为一类，贡献值为 $7$。


参考代码：
```
#include <iostream>
#include <cstdio>

using namespace std;

int l, r;
int s = 0;

int main()
{
    scanf("%d %d", &l, &r);
    
    for(int i = l; i <= r; i ++)
    {
        int d = i;
        while(d != 0)
        {
            if(d % 10 == 0 || d % 10 == 6 || d % 10 == 9) s += 6;//第1类
            else if(d % 10 == 2 || d % 10 == 3 || d % 10 == 5) s += 5;//第2类
            else if(d % 10 == 1) s += 2;//第3类
            else if(d % 10 == 4) s += 4;//第4类
            else if(d % 10 == 7) s += 3;//第5类
            else s += 7;//第6类
            d /= 10;//每一循环除以10,每次删除这个数的最后一位
        }
    }
    printf("%d\n", s);
    return 0;
}

```

---

## 作者：Sniper_jyb (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF620B)

### 思路
首先，我们可以发现：所有数的火柴棒根数都是由 $0-9$ 这十个数组成。因此，我们就可以先确定 $0-9$ 的火柴棒根数，然后推出所有数字的火柴棒根数，最后将 $[l,r]$ 内所有数字的火柴棒根数加起来就可以了。

那么如何递推呢？

显然的，每个数的火柴棒根数相当于最低火柴棒根数加上其余数位的火柴棒根数。因此我们就有了递推式：

$f(x)=f(
\dfrac{x}{10})+f(x\bmod 10)$

初始条件：

```
f[0]=6;   f[1]=2;
f[2]=5;   f[3]=5;
f[4]=4;   f[5]=5;
f[6]=6;   f[7]=3;
f[8]=7;   f[9]=6;
```

然后，从 $f_{10}$，一直递推到 $f_r$ 就可以了。

------------

上代码——

```
#include<iostream>
using namespace std;
int f[1000010]={6,2,5,5,4,5,6,3,7,6},l,r,ans;
int main(){
    cin>>l>>r;
    for(int i=10;i<=r;i++) 
        f[i]=f[i/10]+f[i%10];
    for(int i=l;i<=r;i++)
        ans+=f[i];
    cout<<ans;
    return 0;
}
```


---

## 作者：_acat_ (赞：0)

本题建议评红。

## 题目大意

用火柴棒摆数字，给定 $l,r$ 两个数字，求 $1$ 到 $r$ 之间共用多少根火柴棒。

## Sol

因为本题数据比较小，所以我们可以把 $1 - 9$ 的每个数所用的火柴棒的数量存在一个数组里，然后逐位计算，最后将火柴棒的数量累加起来就行了。

$0-9$ 所用的火柴棒个数：

| 数字 | $0$ | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8$ | $9$ |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 所用个数 | $6$ | $2$ | $5$ | $5$ | $4$ | $5$ | $6$ | $3$ | $7$ | $6$ |


代码就不给了把。。。

---

## 作者：cfkk (赞：0)

这是一道模拟题。

首先，想要知道 $(l,r)$ 中的每个数的每一位都用了多少个火柴棍，我们需要一个数组 $v$ 来记录 ${0,1,2,……,9}$ 中每一个数用了多少个火柴棍。

有了数组 $v$ ，我们再枚举 $(l,r)$ 中的每一项，再用一个循环求出每一项中的每一个数位进行累加求和，就可以知道答案了。

代码来喽：
```cpp
/*#define fastcall __attribute__((optimize("-O3")))
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")*/
#include<bits/stdc++.h>
#include<string.h>
#define min(a,b)(a<b?a:b)
#define max(a,b)(a>b?a:b)
#define int long long
#define mod 998244353
#define maxn 1000010
#define inf 1<<30
using namespace std;
inline int read()
{
    char ch=getchar();
    int s=0,w=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-'){w=-1;}
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        s=(s<<1)+(s<<3)+ch-48;
        ch=getchar();
    }
    return w*s;
}
inline void out(int x)
{
    if(x<0){putchar('-'),x=-x;}
    if(x>9){out(x/10);}
    putchar(x%10+'0');
}
inline void print(int x,char ch)
{
    out(x);
    printf("%c",ch);
}
inline string read_char()
{
    string str="";
    while(1)
    {
        char ch=getchar();
        if(ch=='\n'){break;}
        str+=ch;
    }
    return str;
}
int v[10]={6,2,5,5,4,5,6,3,7,6};
int f(int n)
{
    int sum=0;
    while(n)//找每一位
    {
        sum+=v[n%10];
        n/=10;
    }
    return sum;
}
signed main()
{
    int l=read(),r=read(),cnt=0;
    for(int i=l;i<=r;i++){cnt+=f(i);}//累加求和
    print(cnt,'\n');
    return 0;
}

```


---

## 作者：Deamer (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF620B)

# 思路：

我们把每个数字所需的线段数都提前存下来，然后枚举 $l$ 到 $r$ 之间的每一个数累加答案，对于任意一个数，它的线段总数为它每一位数字所需的线段数之和。

#  _Code_ 

```cpp
#include<bits/stdc++.h>
using namespace std;
int l,r;
int a[10]={6,2,5,5,4,5,6,3,7,6};		//每个数所需的线段数
int ans;
int main(){
	scanf("%d%d",&l,&r);
	for(int i=l;i<=r;i++){
		int x=i;
		while(x){
			ans+=a[x%10];				//累加每一数位所需线段数
			x/=10;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```
[完结撒花！！！](https://www.luogu.com.cn/record/76999785)

---

## 作者：Hisaishi_Kanade (赞：0)

### 一、题意

用火柴棒摆区间 $\left[l,r\right]$ 中的数字需要多少根。

### 二、思路

设 $g\left(n\right)$ 表示数码 $n$ 的火柴棒；$f\left(m\right)$ 表示一个个位数 $m$ 的火柴棒。

易得公式：

$$
g\left(n\right)=g\left(\frac n {10}\right)+f\left(n\mod10\right)
$$

和 $f\left(m\right)$ 的表格：

|$m$|$0$|$1$|$2$|$3$|$4$|$5$|$6$|$7$|$8$|$9$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$f\left(m\right)$|$6$|$2$|$5$|$5$|$4$|$5$|$6$|$3$|$7$|$6$|

由此，结果为 $\sum_{i=l}^{r} g\left(i\right)$。

讲的很清楚了，不给完整代码。

```cpp
int f[]={6,2,5,5,4,5,6,3,7,6};
int g(int n){
	if(n<10)
		return f[n];
	else
		return g(n/10)+f(n%10);
}
```

---

## 作者：hxhhxh (赞：0)

## 大意

求用火柴规范地摆出从 $ a $ 到 $ b $ 的数字需要的火柴棍数。

## 思路

注意到 $ 1 \leq a \leq b \leq 10^6 $ ，可以直接从 $ a $ 枚举到 $ b $ 。

在这道题里，即是对于每一个数枚举它的数位都可以过。

但是，拓展一下，如果 $ 1 \leq a \leq b \leq 10^8 $ 呢？

我们可以开一个大小为 $ b $ 的数组 $ v $ ， $ v_i $ 表示摆 $ i $ 的消耗。

有如下递推式： $ v_i = v_{\lfloor \frac{i}{10} \rfloor } + num_{i \bmod 10} $ ，其中 $ num $ 为数组 $ \{6,2,5,5,4,5,6,3,7,6\} $ 。每一次访问 $ v $ 数组时，如果 $ v_i $ 没有值，访问 $ v_{ \lfloor \frac{i}{10} \rfloor } $ 

这样可以把时间复杂度从 $ O((b-a)\log_{10}b) $ 将到 $ O(b) $ 。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,num[10]={6,2,5,5,4,5,6,3,7,6},v[1000006],ans;
int f(int x){
	if(v[x]) return v[x];
	if(x==0) return 0;
	return v[x]=f(x/10)+num[x%10];
}
int main(){
	cin>>a>>b;
	for(int i=a;i<=b;i++) ans+=f(i);
	cout<<ans;
	return 0;
}
```

---

## 作者：_easy_ (赞：0)

# 题目大意
给你两个数 $a,b$，求出 $a$ 到 $b$ 之间的所有数字（包括 $a$ 和 $b$）需要的火柴棒个数。
# 思路
暴力求解，但是会有多位数，我们参考高精度的处理方法，使用逐位计算，最后将综合累加起来就行了。注意每次需要将数字更新，即除以十。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b,ans,c[10]={6,2,5,5,4,5,6,3,7,6};//使用数组来存储每个数字需要多少根火柴棒 
int main(){
	cin>>a>>b;
	for(int i=a;i<=b;i++){
		int k=i;//千万不能用i，因为如果用i的话会使得每次的i都会变成0 
		while(k){
			ans+=c[k%10];//逐位求解
			k/=10;//每次除以十
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：世末OIer (赞：0)

能不能将翻译加进题目？题目还没有翻译

题目大意：

![](https://codeforces.com/predownloaded/8c/3c/8c3cf4e0d09f92371a130402aa5467fd763c8d4c.png)

在l至r这些数中，问你所有线条被点亮的总的次数。

如:数字1被点亮了2个线条，3被点亮了5个线条。

$1 \le l \le r\le 10^6$


题解：

暴力。

```cpp
int col[]={6,2,5,5,4,5,6,3,7,6},l,r;
int main(){
	rdi(l),rdi(r);  //快读
	int i,j;
	ll ans=0;
	for(i=l;i<=r;++i){//枚举
		j=i;
		while(j) ans+=col[j%10],j/=10;//按位累加
	}
	print(ans);
}
```

---


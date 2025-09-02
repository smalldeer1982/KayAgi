# [USACO19DEC] MooBuzz S

## 题目描述

Farmer John 的奶牛们最近成为了一个简单的数字游戏“FizzBuzz”的狂热玩家。这个游戏的规则很简单：奶牛们站成一圈，依次从一开始报数，每头奶牛在轮到她的时候报一个数。如果一头奶牛将要报的数字是 $3$ 的倍数，她应当报 `Fizz` 来代替这个数。如果一头奶牛将要报的数字是 $5$ 的倍数，她应当报 `Buzz` 来代替这个数。如果一头奶牛将要报的数字是 $15$ 的倍数，她应当报 `FizzBuzz` 来代替这个数。于是这个游戏的开始部分的记录为：

`1, 2, Fizz, 4, Buzz, Fizz, 7, 8, Fizz, Buzz, 11, Fizz, 13, 14, FizzBuzz, 16`

由于词汇的匮乏，奶牛们玩的 FizzBuzz 中用`Moo` 代替了 `Fizz`、`Buzz`、`FizzBuzz`。于是奶牛版的游戏的开始部分的记录为：

`1, 2, Moo, 4, Moo, Moo, 7, 8, Moo, Moo, 11, Moo, 13, 14, Moo, 16`

给定 $N$，请求出这个游戏中第 $N$ 个被报的数。

## 说明/提示

关于部分分：

测试点 $1$ 为样例。

测试点 $2\sim 5$ 满足 $N\le 10^6$。

对于 $100\%$ 的数据，$1 \leq N \leq 10^9$

供题：Brian Dean

## 样例 #1

### 输入

```
4```

### 输出

```
7```

# 题解

## 作者：2017gdgzoi999 (赞：26)

### 简要解法：

我们将所有 $3$ 的倍数和 $5$ 的倍数去除，剩余的列表（报出的数）前段如下：

`1 2 4 7 8 11 13 14/`

`16 17 19 22 23 26 28 29/`

`31 32 34 37 38 41 43 44...`

设第 $i$ 个列表中的数为 $f_i$。

上面，`/`符号将列表分成了若干部分，其中每一个部分有 $8$ 个数。

对于每部分的最后一个数找规律，易得如下公式（$k$ 为正整数）：

$$f_{8k} = 15k-1$$

得到这个公式后，对于 $N$ 为 $8$ 的倍数的情况，可以直接套用公式求解。

如果不是呢？不妨设 $N=8k+a$（$1 \leq a \leq 7$），问题就转化为从 $15k$ 开始的被报出的第 $a$ 个数。由于 $a$ 很小，这一部分只要暴力即可。

代码（文言）：

注释中也有一些对于文言语句的说明。

```cpp
注曰。「「注曰语句是程序中的注释。」」。
注曰。「「注释中说明的语句是简体字。实际编程中需要使用繁体。」」。

吾嘗觀「「算經」」之書。方悟「取底」之義。
注曰。「「吾尝观...之义语句导入库中函数。」」。

吾有一術。名之曰「判断合法」。欲行是術。必先得一數。曰「甲」。是術曰。
注曰。「「判断是否会被报出。吾有一术名之曰语句声明函数」」。
注曰。「「欲行其术必先得...曰语句声明参数。无参时可省略。曰可以有多个。」」。
注曰。「「是术曰语句声明函数开始」」。
    除「甲」以三。所餘幾何。名之曰「除三之余」。
    若「除三之余」等於零者。乃得陰也。
    注曰。「「若...乃语句表示满足某个条件时的返回值。」」。
    注曰。「「三的倍数不会被报出」」。
    除「甲」以五。所餘幾何。名之曰「除五之余」。
    若「除五之余」等於零者。乃得陰也。
    注曰。「「五的倍数不会被报出」」。
    乃得陽也。
    注曰。「「如果不是三的倍数也不是五的倍数，它就会被报出」」。
    注曰。「「返回布尔值。阳表示真，阴表示假。」」。
是謂「判断合法」之術也。
注曰。「「是谓...之术也语句声明函数结束。」」。

施「require('fs').readFileSync」於「「/dev/stdin」」。名之曰「初始输入」。
施「(buf => buf.toString().trim())」於「初始输入」。昔之「初始输入」者。今其是矣。
施「parseInt」於「初始输入」。名之曰「甲」。
注曰。「「输入部分。使用Javascript的语法。」」。
注曰。「「parseInt函数将字符串转换为数字」」。
除「甲」以八。名之曰「周期数」。
注曰。「「计算此数之前的完整周期次数。」」。
注曰。「「加/乘/除...以语句进行运算。」」。
注曰。「「名之曰语句声明变量。其值在前面语句提到。」」。
施「取底」於「周期数」。昔之「周期数」者。今其是矣。
注曰。「「此语言除法不会向下取整，需要使用函数。」」。
注曰。「「施...于语句执行函数。于传入参数，可以有多个。」」。
注曰。「「昔之..者斤其是矣语句将变量重新复值。其值在前面语句提到。」」。
乘「周期数」以十五。名之曰「结果」。
加「结果」以负一。昔之「结果」者。今其是矣。
注曰。「「现在的结果是上文中15k-1的值。」」。
除「甲」以八。所餘幾何。名之曰「剩余」。
注曰。「「往后剩余要找的数字数量即为N除8的余数。」」。
注曰。「「除...以...所余几何语句计算余数。」」。
恆為是。
注曰。「「恒为是语句表明一个死循环。」」。
    若「剩余」小於一者。乃止。云云。
    注曰。「「现在已经是目标，退出循环并输出它」」。
    注曰。「「乃止语句表明退出循环，相当于break。」」。
    注曰。「「若...云云语句表明若满足条件会执行的语句。相当于if。」」。
    加「结果」以一。昔之「结果」者。今其是矣。
    施「判断合法」於「结果」。名之曰「是否合法」。
    注曰。「「将当前数增加一，然后检查是否会被报出」」。
    若「是否合法」等於陽者。
        加「剩余」以负一。昔之「剩余」者。今其是矣。
        注曰。「「次数会被报出。找的数的剩余数量减一。」」。
    云云。
云云。
注曰。「「此处的云云语句说明循环结束。」」。
加「结果」以零。書之。
注曰。「「将最终的结果输出。」」。
注曰。「「书之语句进行输出。调用此语句将在最后额外输出一个换行符。」」。
```

附：同义C++代码。

```cpp
#include <iostream>
#include <cstdio>

using namespace std;
typedef long long ll;

bool check(ll x) {
	if (x%3==0) return false;
	if (x%5==0) return false;
	return true;
}
int main() {
	ll k; scanf("%lld",&k);
	ll res=15LL*(k/8)-1; k&=7;
	while (k) {
		if (check(++res)) --k;
	}
	printf("%d", res);
	return 0;
}
```

---

## 作者：Yellow_Lemon_Tree (赞：12)

可能我的最短了

方法：找规律！

我发现他、它的数是以15一个循环，分别是：-1 1 2 4 7 8 11 13 16，（前要-1）于是打个表加一加就行了。

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int sum[10]={-1,1,2,4,7,8,11,13,16};
int main()
{
    int n;
    scanf("%d",&n);
    long long ans=0;
    ans=(n/8)*15+sum[n%8];
    printf("%d\n",ans);
return 0;
}
```
希望能过。

记得点赞！

---

## 作者：风人 (赞：7)

## 以下是python AC代码，超简洁，3行搞定：
```python
a=int(input())
b=(1,2,4,7,8,11,13,14)#由于py中下标[-1]代表从后往前第一个数故可以这样写，c++不行	
print(((a-1)//8)*15+b[a%8-1])
```
## C++AC代码：
```c
#include <iostream> 
using namespace std;
int a,b[9]={14,1,2,4,7,8,11,13,14},c;
int main()
{
    cin>>a;
    c=((a-1)/8)*15+b[a%8];
    cout<<c<<endl;
    return 0;
}
```

   
  
总的来说，比较简单，数是每8个为一循环，即可写出代码

# 具体思路如下

列出序号与报的数之间的关系（第一行序号，第二行报的数）

    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
    1 2 * 3 * * 4 5 * *  6  *  7  8  *
    
    16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
    9  10 *  11 *  *  12 13 *  *  14 *  15 16 *

由以上两组实验可以看出，每15个报的数为一循环，这也很好理解，3*/5=15，即15为其最小公倍数。每15个数中报8个数，报的数的对应关系也可容易得，1>>1，2>>2，3>>4，4>>7等等，因此可首先判断周期，再取模判断序号，相加即可。

**需要注意！**当a%8=0时的情况（需要在次中减一）这也是最后一个测试点的坑，84分的大概都死在这……（我+1）

因此题输入少，变量少，提供一种思路——**打表**

但因对本题无时间和空间优化，可留给大家自行探索。
思路：循环判断是否取模3，5=0，如是跳过，不是则输出序号即可。

1. 2019月12月27日完成初稿。
1. 2020月1月2日第一次修改，修改内容：修改代码格式，添加部分注释，增加C++部分。

---

## 作者：gtl_caiji (赞：7)

### 题意理解
题目比较长，~~USACO好像就爱用很长的题目~~，大体意思就是要求你求出第n个既不是3的倍数也不是5的倍数的数。
### 思路
我们可以先看一下题目描述中给的样例
```
1, 2, Moo, 4, Moo, Moo, 7, 8, Moo, Moo, 11, Moo, 13, 14, Moo, 16
```
我们可以继续续写下去：
```
1, 2, Moo, 4, Moo, Moo, 7, 8, Moo, Moo, 11, Moo, 13, 14, Moo, 16，17，Moo,19,Moo,Moo,22,23,Moo,Moo,26,Moo,28,29,Moo,31……
```

经过枚举，我们发现，1-15与16-30 Moo 的位置一样！

然后我们就可以~~愉快地~~做这道题了

### 代码

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<cstdlib>
#include<stack>
#include<ctime>
#include<map>
#include<list>//常用头文件合集，大佬若不嫌弃可以拿去用用
using namespace std;

int main()
{
	int n;
	scanf("%d",&n);
	int tmp1=n%8;//这个代表n是我们发现的规律中的第几个
	int ans=n/8*15;//这个代表n在第几个循环
	int cnt=0;//这个代表第cnt个数（注意，是数，不是Moo）
	for(int i=1; i<=16; i++)
	{
		if(i%3!=0 && i%5!=0) cnt++;
		if(cnt==tmp1)
		{
			printf("%d\n",ans+i);
			return 0;
		}
	}
 	return 0;
}

```
嘿嘿，我想你们的小手已经不自觉的按下了ctrl c，可是这个代码是不对滴，[详情](https://www.luogu.com.cn/record/32394848)

主要原因是我们没有考虑当n为15倍数时的情况，这种情况下，循环不会执行，所以才不会输出。我们可以把循环改一改，我比较懒，直接加了一个特判。
### 真正的AC代码
[详情](https://www.luogu.com.cn/record/32394990)

拒绝抄袭

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<cstdlib>
#include<stack>
#include<ctime>
#include<map>
#include<list>
using namespace std;

int main()
{
	int n;
	scanf("%d",&n);
	int tmp1=n%8;
	int ans=n/8*15;
	int cnt=0;
	if(tmp1==0)
	{
		printf("%d\n",ans-1);//注意，一定要-1
		return 0;
	}
    //下面不需要注释，注释在上面有
	for(int i=1; i<=16; i++)
	{
		if(i%3!=0 && i%5!=0) cnt++;
		if(cnt==tmp1)
		{
			printf("%d\n",ans+i);
			return 0;
		}
	}
 	return 0;
}
```
虽然已经有了同样思路，但我觉得我的更详细，而且适合中小学生OIer，求过

---

## 作者：rui_er (赞：5)

**题目大意：求从一开始第$n$个既不是三的倍数又不是五的倍数的数**

没有思路。列几个数看看：

1, 2, 4, 7, 8, 11, 13, 14, 16, 17, 19, 22, 23, 26, 28, 29, ……

因为三乘五等于十五，所以猜测模15的余数可能有规律。列一下：

1, 2, 4, 7, 8, 11, 13, 14, 1, 2, 4, 7, 8, 11, 13, 14, ……

于是很明显地发现存在8位的循环节。根据数学推导可得（以下所有公式中的除号“/”均表示整除，即向下取整）：

$ans=(n/8)*15+a[n\mod8]$，其中$a[1...n]=\{14, 1, 2, 4, 7, 8, 11, 13\}$，就是上面推导的余数。

但是当$n\mod8=0$时发现有问题，此时$ans=(n/8)*15-1$，特判一下就好。

AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[8] = {14, 1, 2, 4, 7, 8, 11, 13};

int main()
{
	int n;
    cin>>n;
    int d = n / 8;
    int ans = d * 15;
    if(n % 8 != 0) ans += a[n%8];
    else --ans;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：gznpp (赞：4)

第一篇题解（按时间排序）是个 $O(1)$ 的算法，我表示比不过。

这题一看很像另外一道题：$1\dots N$ 中有多少个数既不能被 $3$ 整除也不能被 $5$ 整除。

上面提到的这题是入门容斥：  
能被 $3$ 整除的有 $N \div 3$ 个，能被 $5$ 整除的有 $N \div 5$ 个，但是能被 $15$ 整除的数被算了两次，要减掉 $N \div 15$。这就是 $1\dots N$ 中能被 $3$ **或** $5$ 整除的数的个数。  
最后答案就是 $N$ 减掉上面计算的值。

一句话：$ans = n - \dfrac{n}{3} - \dfrac{n}{5} + \dfrac{n}{15}$。时间复杂度 $O(1)$。

这题其实是原题的判定形式。

根据复杂度理论，判定复杂度不劣于求解。

所以——二分答案！

判定的时候算 $ans$，如果比 $N$ 大就`r = mid - 1`，否则`l = mid`。

二分左右边界可以估算一下，我直接设的是 $[0,\text{INT\_MAX}]$。

时间复杂度 $O(\log W)$，其中 $W$ 是值域。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
inline bool pd(int x)
{
	int k=x-x/3-x/5+x/15;
	if(k<=n)
		return 1;
	else
		return 0;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
 	freopen("moobuzz.in","r",stdin);
 	freopen("moobuzz.out","w",stdout);
	cin>>n;
	int l=0,r=INT_MAX;
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(pd(mid))
			l=mid;
		else
			r=mid-1;
	}
	while(l%3==0||l%5==0)
		--l;
	cout<<l<<endl;
	return 0;
}
```

---

## 作者：7KByte (赞：3)

发现自己的方法比较独特于是发篇题解


显然求前$N$个数中有多少个$Moo$比求除去$Moo$的第$N$个数好求


显然$=N-N/3-N/5+N/15$


所以我们可以二分答案，将求解转化为判定


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
int main(){
	//freopen("moobuzz.in","r",stdin);
	//freopen("moobuzz.out","w",stdout);
    scanf("%lld",&n);
	ll l=1,r=999999999999ll,ans;
	while(l<=r){
		ll mid=(l+r)>>1;
		ll val=mid-(mid/3)-(mid/5)+(mid/15);
		if(val>=n)r=mid-1,ans=mid;
		else if(val<n)l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：Snow_Dreams (赞：2)

这道题很多题解都用了一个数学方法：余数循环

但是我还是想说一下里面的数学原理

为什么余数具有循环性（不用找规律）？

首先，不难发现，[3,5] = 15

在前15个数中（1~15），一共有8个数不被3和5整除，分别是1,2,4,7,8,11,13,14

然后又因15≡0（mod 3）,15≡0(mod 5)

所以1+15n≡1(mod 3),   1+15n≡1(mod 5)

所以1+15n不与3或5同余

同理可证剩下的

然后代码就是去开一个数组，1,2,4,7,8,11,13,14

然后数学法求就可以了

最后还是附上代码：

```cpp
#include<cstdio>
int n, yu, ans;
int a[8] = {14, 1, 2, 4, 7, 8, 11, 13};
int main()
{
    scanf("%d",&n);
	yu = n/8;
    ans = yu*15;
    if(n%8 != 0) ans += a[n%8];
    else --ans;
    printf("%d",ans);
    return 0;
}
```


---

## 作者：GIFBMP (赞：1)

这题实际上是求第$n$个不是$3$或$5$的倍数的正整数。

一开始我们会觉得无从下手，但我们发现，这些数每$15$个构成一个循环，其中$15$以内有$8$个符合要求的数。

于是我们可以用$f_x$表示第$x$个符合要求的数，可以推出式子:

$$f_x=f_{x-8}+15$$

然而这样仍然会TLE.

然后我们再简化一下式子，推出前面有多少个循环节$k$，即$k=\frac{n-1}{8}$，然后就可以愉快地得出：

$$f_x=f_{x-k*8}+k*15$$

时间复杂度$\Theta(1)$。

CODE:

```cpp
#include<cstdio>
using namespace std;
int n,k,ans[1010],cnt;
bool ok(int x){
	return x%3 && x%5;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=15;i++)
		if(ok(i))k++,ans[++cnt]=i;
	int x=(n-1)/k;
	printf("%d",ans[n-k*x]+x*15); 
	return 0;
}
```

---

## 作者：tiger2005 (赞：1)

### 做题全过程

10:30来到机房，直接开始打USACO。

不知道为什么，我不用打铜组(可能是我之前达到银组了)，之后直接看了Silver T1。

(1分钟的脑子翻译之后)

WTF?为什么这道题这么简单？不是二分裸题吗……

用10分钟敲了二分，之后发现自己边界什么的直接爆炸……

开完动员会之后才调出了这道题。

---

### 题意简述

找到从1开始第N个不是3或者5的倍数的数。

---

### 做法

我们可以通过容斥原理发现1到N之间会被说出来的数字。
```
首先，所有数           ->N

之后，排掉3的倍数       ->-N/3

还有5的倍数            ->-N/5

15的倍数重复减了，加上  ->N/15
```

之后，我们就可以列出代码：

```cpp
long long num(long long m){return m - (m / 3) - (m / 5) + (m / 15);}
```

再然后就是二分了，直接找到符合`num(M)>=N`的最小M即可。

复杂度：$O(logN)$(常数取决于区间大小)。

Code:

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
long long N,L,R,M;
long long num(long long m){return m - (m / 3) - (m / 5) + (m / 15);}
int main(){
	freopen("moobuzz.in","r",stdin);
	freopen("moobuzz.out","w",stdout);
	scanf("%lld",&N);
	R=15*N;
	while(L<R-1){
		M = (L+R)>>1;
		if(num(M)>=N)	R=M;
		else	L=M;
	}
	printf("%lld",R);
	fclose(stdin);
	fclose(stdout); 
	return 0;
}
```

---

### P.S. : 考后YY的$O(1)$做法

我们可以知道，连续15个数之中，只有8个数会被说出来(使用欧拉函数和剩余系说明即可，细节留给读者思考)。

那么我们可以将N分为两段：$N=8p+q\ (0\leq q\leq8)$。

那么答案就是$15p+sz[q]$(sz[]数组储存1~15之内被叫到的数字)。

细节见代码。

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int sz[10]={1,2,4,7,8,11,13,14};
long long N;
int main(){
    scanf("%lld",&N);
    printf("%lld",15*((N-1)/8)+sz[(N-1)%8]);
}
```

---

## 作者：chenningxuan (赞：0)

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> a;//用了vector，可以用普通数组代替，但要注意下标的使用
bool ok(int x) {//判断是否是3和5的倍数
	return x%3&&x%5;
}
int work(int n) {找规律，余数8个数为一个周期：1,2,4,7，8,11,13,14
	int num=(n-1)/8;
	return a[n-8*num-1]+15*num;//数学公式，-1是因为vector下标从0开始
}
int main()
{
	for(int i=1;i<=15;i++) {
		if(ok(i)) a.push_back(i);
	}//可以打表哦
	int n;
	cin>>n;//输入n
	cout<<work(n)<<endl;输出
	return 0;
}
```


---

## 作者：guoxinyugz (赞：0)

### 就是求第n个不是3的倍数也不是5的倍数的数。

显然，3和5的最小公倍数是15，

这意味着每15个数里出现的不是3的倍数也不是5的倍数的数是一样的，8个。

这就是**周期**啊。我们除以八，算出答案在第几“组”里，乘以15，再加剩下的余数所对应的数就可以了。

下面是我的代码。比较容易犯的错误是代码13行应为a-1而不是a。

```
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
long long n,a;
int main()
{
// 	freopen("moobuzz.in","r",stdin);
// 	freopen("moobuzz.out","w",stdout);
	scanf("%lld",&n);
	a=n/8*15;
	n=n%8;
	if(n==0) printf("%lld",a-1);
	else if(n==1) printf("%lld",a+1);
	else if(n==2) printf("%lld",a+2);
	else if(n==3) printf("%lld",a+4);
	else if(n==4) printf("%lld",a+7);
	else if(n==5) printf("%lld",a+8);
	else if(n==6) printf("%lld",a+11);
	else if(n==7) printf("%lld",a+13);
	return 0;
}
```

这应该算银组最简单的题了吧？


---

## 作者：2020ywj (赞：0)

这是本蒟蒻第七个题解，不喜勿喷。

* 思路：

利用容斥原理+二分判断。我们假设n个数里共有cnt个被跳过的数，那么报的第n个数就是n+cnt，由于n和cnt都具有单调性，所以我们可以利用二分判定来解决。

其中容斥原理很容易想到，cnt显然等于n内3的倍数+5的倍数+15的倍数，但是15=3 * 5，所以15不需要重复统计（已经在3的倍数中统计过了）。但是我们重复统计3和5的公倍数（统计了2次），于是我们就要减去同时是3的倍数和5的倍数的个数即可得到cnt。

在O(1)时间内求出cnt后，我们就可以在O(logN)时间内用二分搜索解决此题。

* 代码：
```cpp
#include<iostream>
using namespace std;
int n;
int check(long long s)
{
	long long a=s/3,b=s/5;
	long long c=s/15;
	long long t=a+b-c;
	return s-t>=n;
}
int main()
{
	cin>>n;
	long long l=1,r=1001;
	while(l<=r)
	{
		long long mid=l+r>>1;
		if(check(mid)) r=mid-1;
		else l=mid+1;
	}
	cout<<l<<endl;
	return 0;
}
```
记得关注我哟！

[P5834 [USACO19DEC]MooBuzz S题目传送门](https://www.luogu.com.cn/problem/P5834)

---


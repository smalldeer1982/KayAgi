# [AGC003B] Simplified mahjong

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc003/tasks/agc003_b

高橋君は $ 1 $ から $ N $ までの整数のうちのどれかが書かれたカードをたくさん持っています。 高橋君は整数 $ i $ が書かれたカードを $ A_i $ 枚持っています。

$ 2 $ 枚のカードについて、それらに書かれた整数の差の絶対値が $ 1 $ 以下のとき、これらをペアにすることができます。

高橋君は、同じカードが複数のペアに使われないように、できるだけ多くのペアを作りたいです。高橋君が作れるペアの個数の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 10^5 $
- $ 0\ ≦\ A_i\ ≦\ 10^9\ (1\ ≦\ i\ ≦\ N) $
- 入力はすべて整数である。

### Sample Explanation 1

一例として、$ (1,1),(1,1),(3,4),(3,4) $ の $ 4 $ つのペアをつくることができます。

## 样例 #1

### 输入

```
4
4
0
3
2```

### 输出

```
4```

## 样例 #2

### 输入

```
8
2
0
1
6
0
8
2
1```

### 输出

```
9```

# 题解

## 作者：zhang_kevin (赞：12)

# Part 1：题目分析

观察体面，不难看出这道题的本质就是一张牌**与自己匹配**或者**与相邻的牌匹配**。所以，这道题的解法就是**贪心**。

# Part 2：解题思路

题目分析里已经说过了，一张牌只能**与自己匹配**或**与相邻的牌匹配**。所以我们直接循环输入 $A_i$ ，每次都先与自己匹配，然后在**自己和下一个都不为 $0$ 的情况下**与下一个匹配即可。

最后，注意要开 `long long`。

# Part 3：AC代码

```cpp
#include<bits/stdc++.h>
#define int long long //十年 OI 一场空，不开 long long 见宗祖！
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(ch<'0'||ch>'9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9'){
        x = (x<<1) + (x<<3) + (ch^48);
        ch = getchar();
    }
    return x*f;
}
int n, m, i, j, k;
int a[100010];
int ans = 0;
signed main(){
    n = read();
    for(i=1; i<=n; ++i)
        a[i] = read();
    for(i=1; i<=n; ++i){
        ans+=a[i]/2;
        a[i]%=2;
        if(a[i]&&a[i+1]){
            --a[i];
            --a[i+1];
            ++ans;
        }
    }
    printf("%lld\n", ans);
    return 0;
}//人生自古谁无死，留篇题解帮萌新。
```


---

## 作者：zjyqwq (赞：7)

### AT2002题解
我又来发题解了！！！


------------
#### 本题思路
题意很清晰。

可以用贪心的方法做。

首先，我们先将每个都与自己配对。然后再看看能不能与后面的配对，然后就输出。

就行了！！！


------------
#### 代码
```c++
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a[100010],n,i;
long long s;//定义
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	cin>>a[i];//输入
	for(i=1;i<=n;i++)
	{
		s=s+a[i]/2;//先于自己配对
		a[i]=a[i]%2;
		if(a[i])if(a[i+1]){a[i]--;a[i+1]--;s++;}//再与后面的配对
	}
	cout<<s;//输出
	return 0;
}
```
结束了！！！

---

## 作者：京润 (赞：3)

### 题意解释：

已知1—N所有面值的牌的个数，同面值或相邻面值的牌可以配对，求最多可以配对的个数。

### 做法：

题意很明确，不妨定义一个数组$ a[i]$储存各面值的牌的个数，然后按面值从小到大枚举，符合条件合并即可。

### 重点：

#### 1.同面值或相邻面值合并的优先性问题：
因为是从小到大枚举，所以要尽可能让所枚举的较小面值进行配对，所以先对此面值进行同面值配对，若剩余（一定剩一张），则将其与下一面值配对，从而保证了枚举过程的正确性，然后进行下一面值的处理，以此类推。


#### 2.一定要开 long long！！！

下面上代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[100010];
long long ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		ans+=a[i]/2;
		a[i]%=2;
		if(i<n&&a[i]&&a[i+1])
		{
			ans++;
			a[i]--;
			a[i+1]--;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Protons (赞：3)

这个题的大意就是：一张面值为a的卡牌，只能和面值为a-1、a、a+1的卡牌配对；给你一堆卡牌，求最大配对数。

刚拿到这个题，我的第一想法就是：先推推样例看一看。我的初始思路是：读入后，先把每种面值的卡牌与它后面的卡牌尽量配对以后，在将剩下的该面值卡牌模2，统计总数，但是，我造了一组数据，卡掉了这个想法：
```cpp
4
2 5 2 1
```
如果按我们原先的思路来，最终结果是4，但是我们尝试一下能发现，最大结果其实是5

#### 咋回事呢？

我们发现，按原先的想法处理完数据之后会剩下两个不相邻的1（0 1 0 1），我们要想办法把这两个1再配对。于是我们就想，应该可以通过调换一下处理顺序，先模2，再配对，这样就能使落单卡牌的面值尽量大（可能描述的有点不清楚，大家自己推一推便明白了，~~毕竟我是个语文渣~~）

然后我就惊讶地发现，我居然AC了……

以下是我的代码：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int a[100010],n;
long long ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		if(!a[i])continue;
		ans+=a[i]/2;
		a[i]%=2;
		if(a[i])if(a[i+1])a[i]-=1,a[i+1]-=1,ans++;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Night_sea_64 (赞：1)

这道题思路太好想了。

显然是贪心。尽可能的都凑完，如果自己不能跟自己凑，就跟下一个再凑。如果下一个没有的话就只能放弃。

注意开 long long 就行了。AC 代码如下：

```cpp
#include<iostream>
using namespace std;
int a[100010];
int main()
{
    int n;
    long long sum=0;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)
    {
        sum+=a[i]/2;
        if(i<n&&a[i]%2&&a[i+1])
            sum++,a[i+1]--;
    }
    cout<<sum<<endl;
    return 0;
}
```

这题真的太水了，改橙吧。。。

---

## 作者：TRZ_2007 (赞：1)

# Description  
有一个长度为$n$的数列，其中第$i$个表示面值为$i$的卡牌数目。你可以挑选相同的或相邻的把它们合并在一起，求合并的最小次数。  
# Solution  
这个我也说不明白，大概是**贪心**，先考虑相同的卡牌，把它们合并在一起。然后没有匹配的和上面的匹配。大概是这样。  
**注意要开long long，要换行！！**  
# Code  
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int book[N];
int n;
long long cnt;

int main() {
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) {
		scanf("%d",&book[i]);
	}
	for(int i = 1;i <= n;i++) {
		cnt += (book[i] / 2);  //相同的匹配
		book[i] %= 2;  //如果有没匹配上的
		if(book[i] && book[i + 1] && i < n) {  //就和后面的匹配
			cnt++;
			book[i]--;
			book[i + 1]--;
		}
	}
	printf("%lld\n",cnt);  //输出，没了
	return 0;
}
```

---

## 作者：yinpeichu2021 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_agc003_b)

## 思路：

可以 $O(n)$ 地从左扫到右。由 $|a-b|\leq1$ 可以知道，每一个数可以与左右两边的数组合，也可以与自身组合。此时可以**尽可能地与自身组合**，若有剩余再**与其后面的数组合**，若其后面的数为 $0$，就放弃。

## code:

```cpp
#include<bits/stdc++.h>
#define int long long //不开long long见祖宗！
using namespace std;
int n,a[100005],ans;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        ans+=a[i]/2,a[i]&=1;
        if(a[i]&&a[i+1])ans++,a[i]--,a[i+1]--;
    }
    cout<<ans;
    
    return 0;
}
```

[AC记录](https://atcoder.jp/contests/agc003/submissions/35787396)

---

## 作者：SSSdyzs (赞：0)

### 题目分析：

------------

不难看出此题用的是**贪心**。

由题目得，组合只有两种方式：
- 自己和自己一组。
- 自己和下一个一组。

可能有人会反驳：还可以是自己和上一个啊！  但是如果按三种情况算的话，自己和下一个、下一个和他的上一个（即自己）会重复算，从而使自己无从下手，不方便写代码。~~至少我是这样。~~

所以按两种方式算能不重不漏的覆盖所有情况。

先自己和自己凑一组，把每种能消耗的消耗完；再用剩下的和下一种匹配。这样能使消耗得牌数尽量多，即使能租的组数尽量多。



### AC 代码：
------------
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100010],ans;
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++){
		ans+=a[i]/2;//先自己和自己组
		a[i]=a[i]%2;//计算和自己组完后能和下一种组合的牌数
		if(a[i]!=0&&a[i+1]!=0){//若有一方为0，则不能和下一种组，直接跳过
			ans+=1;
			a[i]-=1;
			a[i+1]-=1;
		}//因为a[i]%2所以a[i]只能为1或0，但a[i]和a[i+1]都不为0（见判断条件），所以能组的最大数为1
	}
	printf("%lld\n",ans);
	return 0;
}
```


------------
#### 完

---

## 作者：Henry_ji (赞：0)

来写题解咯~

P.S. 完全没有看出这道题和麻将有任何关系啊喂

## Part 1 题目分析
首先，让我们来通读一遍题目。~~点开算法标签，好吧，没有算法标签。~~

显然，这道题的本质就是**和自身匹配**&**和相邻匹配**。所以，这道题的最好方法就是**贪心算法**。

## Part 2 程序思路
1. 和自身匹配：
```cpp
cnt += nL[i] / 2;
nL[i] %= 2;
```
2. 如果和自己匹配不完就且后一个不是0的话和后面一个匹配：
```cpp
if (nL[i] == 1 and nL[i + 1] != 0 and i != n - 1){
	cnt += 1;
	nL[i] --;
	nL[i + 1]--;
}
```

## Part 3 完整程序
上 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

long long n, tn, cnt, nL[100010];

int main() {
	cin >> n;
	for (int i = 0; i < n; i ++) cin >> nL[i];
	for (int i = 0; i < n; i ++) {
		cnt += nL[i] / 2;
		nL[i] %= 2;
		if (nL[i] == 1 and nL[i + 1] != 0 and i != n - 1){
			cnt += 1;
			nL[i] --;
			nL[i + 1]--;
		}
	}
	cout << cnt;
	return 0;
}
```

## Part 4 回顾反思
写几个做题时碰到的坑

1. 边输入边和自身匹配

这是个大坑，遇到如下方的情况就会出问题

```
3
1
2
1
```
2. 不加 long long

没什么好说的

好啦，这篇题解就写到这啦，求管理通过~

---

## 作者：零殇 (赞：0)

#### 题意

有若干张点数分别为$1$到$n$的卡片，告诉你每种的数量，若两张卡片点数之差不大于$1$，就是合法的。求最多可以凑出多少种组合。

#### 思路

对于某种点数为$x$的卡片，只有点数为$x-1$，$x$，$x+1$三种卡片可以配对。

我们从前往后计算，所以不考虑与$x-1$配对（因为我们在$x-1$是就考虑过这种情况了）。

显然，为了最大避免浪费，最优的办法是自己和自己配对，这样就算有浪费，也只可能浪费一张。

如果点数$x+1$的牌的张数大于$0$，就配对。

可能你的想法是：直接和后面配对至一种消失，如果本种有剩，就自己配对，否则考虑下一个。

现在我们看看这个数据：`10 1 1`

按这种想法来看，我们就只能配对出$5$种组合，但事实上有$6$种。

为什么会这样呢？

现在我们考虑这种办法对后面两位的影响。

我们不妨把它们的点数设为$x$，$x+1$，$x+2$。

若$x$与$x+1$配对后，并剩下了$x$，且配对后还剩$1$张，那么就无法与$x+2$配对，这张就白白浪费了。

但如果自己先配对的话，那么最多剩下$1$个，如果与$x+1$可以配对，那么剩下的就只会是$x+1$，也就可以和$x+2$配对。

也就是说，我们的$x$与$x+1$的配对数其实是不能改变的，只不过我们强迫最后剩下的那张（最多只可能剩$1$张）是$x+1$，因为这样我们就可以和$x+2$配对。

最后记得开`long long`。

上代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,a[100001];
long long sum;
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) {
		sum+=(long long)(a[i]>>1);
		a[i]=(a[i]&1);
		if(a[i]==1&&a[i+1]>0) {
			a[i]--;
			a[i+1]--;
			sum++;
		}
	}
	printf("%lld\n",sum);
	return 0;
}
```

完结撒花~


---

## 作者：cjZYZtcl (赞：0)

## AT2002 [AGC003B] Simplified mahjong 题解
这题的主要思路就是把能配对的尽可能配对。

但要注意配对顺序。

虽然题目说，面值为 $x$ 的可以和面值为 $x-1$、$x$、$x+1$ 的配对，但是，上一个面值已经和当前面值配对过了，所以当前面值配对的就只有 $x$ 和 $x+1$ 。

可以证明，先和同面值的配对最优。

如果先和同面值的配对，那么剩余的就和下一面值配对，可以使当前面值最多剩余一个，且下一面值也剩余最多。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[100005];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = read(), sum = 0;
	for(int i = 1; i <= n; i++){
		a[i] = read();
	}
	for(int i = 1; i <= n; i++){
		sum += a[i] / 2;
		a[i] %= 2;
		if(a[i] && a[i + 1]){
			sum++;
			a[i]--;
			a[i + 1]--;
		}
	}
	write(sum);
}
```


---


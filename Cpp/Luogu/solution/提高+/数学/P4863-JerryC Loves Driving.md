# JerryC Loves Driving

## 题目背景

JerryC最近迷上了狂野飙车！！！

## 题目描述

众所周知，JerryC是一位疯狂的Female。他最近买了一台跑车~~(但是却没有驾驶证)~~，所以他就只能到一个偏僻的地方练习开车。

当然，JerryC是不可能正常开车的。她首先决定要开$(B-A+1)$段路程的车，第$i$段路程的速度都是从$1$开始加速的。每一秒会加上$1$的单位速度。当速度加到$(i+A-1)$的时候，JerryC就会把速度降为$1$，然后开始下一段路程。

对于第$i$段路程的第$j$秒，JerryC获得的愉悦值为$\lfloor \frac{i+A-1}{j} \rfloor * (-1)^j$。(反正JerryC就是不喜欢奇数。)

现在请你求出JerryC最后的总愉悦值。

P.s. ：

如果上面的东西没有看懂，那么简单版就是这个意思：

给出A，B，求出下面式子的值。

$$\sum_{i=A}^B \sum_{j=1}^{i}\lfloor \frac{i}{j} \rfloor * (-1)^j$$

## 说明/提示

对于50%的数据：$1 \leqslant A \leqslant B \leqslant 5*10^3$

对于70%的数据：$1 \leqslant A \leqslant B \leqslant 5*10^4$

对于100%的数据：$1 \leqslant A \leqslant B \leqslant 2*10^7$

## 样例 #1

### 输入

```
1 1```

### 输出

```
-1```

## 样例 #2

### 输入

```
2 2```

### 输出

```
-1```

## 样例 #3

### 输入

```
3 3```

### 输出

```
-3```

# 题解

## 作者：zhoutb2333 (赞：19)

一个大概 $\large O(\sqrt{N})$ 的算法

原式相当于 $\large \sum \limits _{i=1}^{B} \sum \limits _{j=1}^{i} (-1)^j \lfloor \frac{i}{j} \rfloor - \large \sum \limits _{i=1}^{A-1} \sum \limits _{j=1}^{i} (-1)^j \lfloor \frac{i}{j} \rfloor$

现在考虑计算 $\large \sum \limits _{i=1}^{N} \sum \limits _{j=1}^{i} (-1)^j \lfloor \frac{i}{j} \rfloor$

令 $\large k=\lfloor \frac{i}{j} \rfloor$ ，那么 $\large ans = \sum \limits _{k=1}^{N} k \left( \sum \limits _{j=1}^{\lfloor \frac{N}{k} \rfloor} (-1)^j \times (\text{存在多少个 } 1\le i \le N \text{ 满足 }   \lfloor \frac{i}{j} \rfloor  =k )\right) $

然后我们拆那个括号里的条件：

$\large  \lfloor \frac{i}{j} \rfloor = k  \Leftrightarrow  j \times k \le i < j \times (k+1)  $

所以当 $\large j \times (k+1) \le N $ 时，$\large i$ 的个数为 $\large j \times (k+1) - j \times k = j$ 

当 $\large j \times (k+1) > N $ 时，$\large i$ 的个数为 $\large N-j \times k +1$ 

故 $\large ans = \sum \limits _{k=1}^{N} k \left( \sum \limits _{j=1}^{\lfloor \frac{N}{k+1} \rfloor} (-1)^j \times j \ \  + \ \ \sum \limits _{j=\lfloor \frac{N}{k+1} \rfloor +1}^{\lfloor \frac{N}{k} \rfloor} (-1)^j \times (N-j \times k +1) \right)$

然后这两个 $\large sum$ 当固定上下界时都可以 $\large O(1)$ 计算，所以我们按照 $\large \lfloor \frac{N}{k} \rfloor$ 和 $\large \lfloor \frac{N}{k+1} \rfloor$ 对 $k$ 进行数论分块即可（$\large N $ 大了跑得很慢，可能我人傻常数大。。）

超丑代码：

``` cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int calc(int x){//计算最终式子前面的sum
    if(~x&1)
        return x>>1;
    return (x-1>>1)-x;
}
ll s1(int l,int r){//求自然数l~r的和
    return 1LL*(r+l)*(r-l+1)/2;
}
ll calc3(int r,int x,int k){
    ll ret=0;
    if(r&1)
        ret-=x+1;
    ret-=1LL*k*calc(r);
    return ret;
}
ll calc2(int l,int r,int x,int k){//计算后面的sum，用两个前缀减
    if(l>r)
        return 0;
    return calc3(r,x,k)-calc3(l-1,x,k);
}
ll solve(int x){
    ll ret=0;
    for(int k=1,pos;k+1<=x;k=pos+1){
        pos=x/(x/(k+1))-1;
        ret+=1LL*s1(k,pos)*calc(x/(k+1));
    }
    for(int k=1,pos;k+1<=x;k=pos+1){
        pos=min(x/(x/k),x/(x/(k+1))-1);
        ret+=1LL*s1(k,pos)*calc2(x/(k+1)+1,x/k,x,k);
    }
    ret+=1LL*x*calc2(1,1,x,x);//这是上一个循环k=x的情况，我的写法不特判会死循环
    return ret;
}
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    printf("%lld\n",solve(b)-solve(a-1));
    return 0;
}
```

---

## 作者：Insouciant21 (赞：8)

首先一想直接暴力 $A$ 到 $B$ 然后内部分块，然后写出来本地一跑 `A=1 B=2000000` 就T了

于是列表找规律

![第一个表](https://s1.ax1x.com/2020/10/10/06Jxoj.png)

发现在 $j$ 相同的情况下，$\left\lfloor\dfrac{i}{j}\right\rfloor \times (-1)^j$ 的值仍有规律。

可以发现，对于 $j$ 相同时的 $\left\lfloor\dfrac{i}{j}\right\rfloor \times (-1)^j$ 的每一个值，都连续出现了 $j$ 次

于是将外部循环 $i$ 改为循环 $j$。

求式子 
$$
\sum_{i=A}^B\sum_{j=1}^i\left\lfloor\dfrac{i}{j}\right\rfloor\times(-1)^j
$$
即为求表中 $i$ 列由 $A$ 到 $B$ ，$j$ 列由 $1$ 到 $B$ 的矩形数值的和

对于每一列的值，可以使用等差数列求和公式计算

设 $l=\left\lfloor\dfrac{A}{j}\right\rfloor$ 且 $r=\left\lfloor\dfrac{B}{j}\right\rfloor$ 

计算 $A$ 至 $B$ 之间的和，可以变为计算 $j$ 个首项为 $0$，末项为 $r$，公差为 $1$ 的等差数列之和减去不属于 $A$ 与 $B$ 之间的部分

等差数列之和为 $\dfrac{r\times(r+1)}{2}\times j$

先计算 $A$ 之前的和，可发现它由 $j$ 个首项为 $0$，末项为 $l$，公差为 $1$ 的等差数列去掉在 $A$ 里面的 $l$ 组成

在 $A$ 里面的 $l$ 有 $l\times j+j-A$ 个，就是 $l$ 的最大值减去 $A$ 为在内部的 $l$ 的个数

式子为 $\dfrac{l\times(l + 1)}{2}\times j-l \times(l\times j+j-A)$

对于超出 $B$ 的部分，与 $A$ 相同处理

得到式子 $(r\times j+j - B - 1) \times r$ （ 减去 $1$ 是因为得到 $r$ 的最大值为 $r\times j + j-1$ ）

AC代码如下

``` cpp
#include <bits/stdc++.h>

using namespace std;

int A, B;

long long ans;

int main() {
    cin >> A >> B;
    for (int j = 1; j <= B; j++) {
        long long sum = 0;
        long long l = A / j;
        long long r = B / j;
        sum = r * (r + 1) * j / 2;
        long long front = l * (l + 1) / 2 * j - l * ((l + 1) * j - A);
        long long back = ((r + 1) * j - B - 1) * r;
        sum = sum - front - back;
        if (j % 2 == 0)
            ans += sum;
        else
            ans -= sum;
    }
    cout << ans << endl;
    return 0;
}
```



---

## 作者：Euler_Pursuer (赞：6)

# 题目解答

## 比赛解答

[比赛解答链接](https://www.luogu.org/blog/20782/solution2)

$O(\sqrt{B})$的原创解答在本博客最下面。

各位也可以参考一下另一位大佬写的$O(\sqrt{B})$的做法：应该就在这里，不过思路和我不一样。

鉴于各位懒得打开比赛解答，现在贴出$O(B)$的解法，**解答来自出题人**。

### 冷静分析

第一时间想到的是内部分块做法，外部线性暴力，不过细细一看，这绝对会超时的啊（你自己都说暴力了）！因此我们需要一个线性做法。

那么我们就需要将式子变形了。

$$\sum^{B}_{i=A}\sum^{i}_{j=1}\left \lfloor \frac{i}{j} \right \rfloor \times \left ( -1 \right )^j =\sum^{B}_{i=1}\left ( \left ( -1 \right )^i \sum^{B}_{j=A} \left \lfloor \frac{j}{i} \right \rfloor \right )$$

注意到式子中，我们把$-1$提出来了，为了使式子等价于原来的式子，我们不得不给式子做一个大手术。因为$-1$提前了，那么它的幂次只能是$i$，于是我们将$i$和$j$的意义替换，变换式子使得其等价于原来的式子。其中注意$i>j$时，分式向下取整得$0$，对答案无影响，所以这两个式子是等价的。

看到这里，你可能还是不知道怎么得到线性做法，我们就这样看：

$$\sum^{B}_{i=1}\left ( \left ( -1 \right )^i \sum^{B}_{j=A} \left \lfloor \frac{j}{i} \right \rfloor \right )=\sum^{B}_{i=1}\left ( \left ( -1 \right )^i \left ( \sum^{B}_{j=1} \left \lfloor \frac{j}{i} \right \rfloor - \sum^{A-1}_{j=1} \left \lfloor \frac{j}{i} \right \rfloor \right ) \right )$$

现在$i$是比较稳定的了，因为当$i$取一个值时，而$j$是连续递增的，那么向下取整可以得到连续$i$个的向下取整的相同的值。

举个例子吧，当$i=3$时，假设$j$从$1$逐一递增到无穷，我们会得到：

$$0,0,1,1,1,2,2,2,3,3,3,\cdots $$

那么我们就可以在$O(1)$的常数时间内算出里面的和式差，最终我们就得到了时间复杂度为$O(B)$的算法。

当然，由于$B$有点大，因此我们需要稍微注意一下常数问题。

不过，在写程序的时候，要注意考虑前面的$0$的个数是$i-1$个的。但是总体还是有规律可循，具体看我的程序。

### 程序实现

```cpp
#include <cstdio>
int main()
{
    int a, b;
    long long ans = 0, r, s, t;
    scanf("%d%d", &a, &b);
    for(register int i = 1; i <= b; i += 1)
    {
        r = a / i - 1;//因为最后一项长度不定，所以我们确定倒数第二项
        s = (a - r * i - i) * (r + 1);//计算最后一项的长度并求和
        r = (r + 1) * r / 2 * i;//前面项的和
        t = s + r;
        //同理可得
        r = (b + 1) / i - 1;
        s = (b + 1 - r * i - i) * (r + 1);
        r = (r + 1) * r / 2 * i;
        if(i & 1)
            ans -=  s + r - t;
        else
            ans += s + r - t;
    }
    printf("%lld", ans);
    return 0;
}
```
最大耗时点耗时：237ms。

本人经过摸索，终于写出了根号级的做法。

## 极速解法（原创）

当然，和式还是原出题人给的。

### 冷静分析

现在将那个和式进行变换：

$$\sum^{B}_{i=1}\left ( \left ( -1 \right )^i \left ( \sum^{B}_{j=1} \left \lfloor \frac{j}{i} \right \rfloor - \sum^{A-1}_{j=1} \left \lfloor \frac{j}{i} \right \rfloor \right ) \right )=\sum^{B}_{i=1}\left ( \left ( -1 \right )^i \sum^{B}_{j=1} \left \lfloor \frac{j}{i} \right \rfloor \right ) - \sum^{A-1}_{i=1}\left ( \left ( -1 \right )^i \sum^{A-1}_{j=1} \left \lfloor \frac{j}{i} \right \rfloor \right )$$

我们可以对最外层的和式进行分块运算。

我们只需分成$4$组进行求和即可，也就是将其分为奇偶和左右部分即可（方便快速高斯求和）。

那么分块具体如何实现呢？

我们发现内部都是有秩序的，虽然将外层的$i$以不同的值写出，同类合并之后我们会发现有点混乱，但是并非无迹可寻！

因为注意到$\left \lfloor \frac{j}{i} \right \rfloor$在某几种$i$的值中（连续的、差为$2$的$i$值），如果组成的数的个数不变（比如都有$1$到$9$），那么除最后一个数（前面的例子的$9$），其他数的变化都是**同规律线性的**（根据比赛题解中提到的结论可得），可以用高斯求和公式算出来。

而组成的数个数不变，当且仅当$\left \lfloor \frac{j}{i} \right \rfloor$中$j$取最大值时该式得到的值不变。

就比如上面提到的那个$9$，因为随着$i$的变化，比$9$小的值都会越来越多，而$9$就会被压出去（可以说是溢出吧2333），毕竟序列长度只有这么长。

而这个值（例如那个$9$）的变化也是线性的！因为前面是线性递增，那么上述的$9$的个数就会线性递减。

那么线性的都可以算出来，仅对最大值的变化讨论即可。而最大值的变化恰恰是有分块的属性（这个不难证明，大家思考一下），于是我们通过内部常数时间，外部分块时间即可算出答案。

严格来说，根号外面至少还有$4$的常数，但是还有可以优化的地步——常数优化（~~蒟蒻我太懒了~~）。而时间复杂度还是$O(\sqrt{B})$的，所以很快就能通过。

### 程序实现

```cpp
#include <cstdio>

int a, b;

//对比O(B)的代码，其实只是加了一些高斯求和罢了
inline long long getans(int f)
{
    int rr, q, delta;
    long long ans = 0, r, r_, s, t, l;
    for(register int i = (f ? 1 : 2); i <= a; i = q + 2)
    {
    	rr = a / i;
    	q = a / rr;
    	if((q & 1) && !f)//要偶数却是奇数
            q ^= 1;
        else if(!(q & 1) && f)//要奇数却是偶数
            q -= 1;
        delta = (q - i >> 1) + 1;//中间长度
        r = a / i - 1;//因为最后一项长度不定，所以我们确定倒数第二项
        l = a + 1 - r * i - i;
        s = (r + 1) * (l - (delta - 1) * (r + 1)) * delta;
        //分块的最后一项求和
        r_ = r;//记录
        r = (r + 1) * r * i >> 1;//前面项的和
        r = r * delta + ((1 + r_) * r_ >> 1) * ((delta - 1) * delta);
        //增加的值
        t = s + r;
        if(f & 1)
            ans += t;
        else
            ans -= t;
    }
    for(register int i = (f ? 1 : 2); i <= b; i = q + 2)
    {
    	rr = b / i;
    	q = b / rr;
    	if((q & 1) && !f)//要偶数却是奇数
            q ^= 1;
        else if(!(q & 1) && f)//要奇数却是偶数
            q -= 1; 
        delta = (q - i >> 1) + 1;//中间长度
        r = b / i - 1;//因为最后一项长度不定，所以我们确定倒数第二项
        l = b + 1 - r * i - i;
        s = (r + 1) * (l - (delta - 1) * (r + 1)) * delta;
        //分块的最后一项求和
        r_ = r;//记录
        r = (r + 1) * r * i >> 1;//前面项的和
        r = r * delta + ((1 + r_) * r_ >> 1) * ((delta - 1) * delta);
        //增加的值
        t = s + r;
        if(f & 1)
            ans -= t;
        else
            ans += t;
    }
    return ans;
}

int main()
{
    scanf("%d%d", &a, &b);
    a -= 1;
    printf("%lld", getans(1) + getans(0));
    return 0;
}
```
单点最大耗时：3ms（由于新测评机的缘故，至少都是2ms的点，应该可以0ms的，没赶上时机哎）。

# 个人感慨

其实上午根据原题解的式子就想到了这个方法（不过也要感谢另一位也是根号解法的大佬提了一下有根号的做法），很感谢原题解作者的化简式，不然我也不会想到。不过我在写程序的过程中也出现了很多小插曲，比如刚写完函数老师就点了集体关机，然后还原GG。不过还好我记得这个方法，然后又写了一下午，调试了大概一个小时还不对，当时是绝望的。然后我发现我智障的把$p$写成了$i$导致奇偶错乱，改了之后大部分数据都过了。进一步我将$a$的那部分有一些与$b$扯上关系的东西改成了$a$（目前还未证明为什么不对）。

总之我想说的是：**成功贵在坚持不懈**！

# 写在最后

感谢比赛举办者提供的题目和题解，感谢各位阅读本文章。
原比赛题解仅作为个人收藏，不做任何商业用途，禁止任何人做商业用途传播。
另外，如果作者认为不妥，可以告诉我，我会马上删掉。
所有程序为个人智力成果，仅根据公式写出，未查看标准程序；此分块做法亦为个人智力成果，如需转载，请注明出处。

---

## 作者：Flokirie (赞：4)

# 来自一位$NOIP2017$选手的忠告：数论题用$Excel/Dev-cpp$打打表，难道$2017\ Day1\ T1$的错还想再犯吗    
（貌似好多同学就是因为卡在了规律上痛失1=）  

那么这道题又有什么规律？

----
先看一下我用$Excel$打的表：（不要在意那一列"#DIV/0!"）
![](https://cdn.luogu.com.cn/upload/pic/31300.png )   
我们容易得到以下规律：   
1. 每一列的数字，绝对值依次是$0,0,0,...,0,1,1,1,...,1,2,2,2,...,2$（重复$j$次）
2. 这个表的“右上角”全部为$0$   

然后，我们就可以做这道题了？

----

我们先看看$A$和$B$是干啥用的。   
假设$(A,B)=(5,11)$，表现在表格中，就是让我们求蓝色部分的和：
![](https://cdn.luogu.com.cn/upload/pic/31304.png )
原本是让我们求每一**行**的和，现在我们既然找到了每一列的规律，何不转换为按**列**求和？   
让我们在代码里解释每一列上、下界的判定。

----

```cpp
#include <bits/stdc++.h>

using namespace std;

inline long long odd (long long x){
	return x&1;
}

inline long long sum(long long n){
	return ((n+1ll)*n)/2ll;
}//计算1+2+...+n

int main(){
	long long a,b;
	cin>>a>>b;
	long long s=0;
	if (b-a<5 && a<10){//为防止较小的数据爆炸特地加入的暴力（我才不会告诉你下面的代码连样例都过不去）
		for (long long i=a;i<=b;i++){
			for (long long j=1;j<=i;j++){
				s+=(i/j)*((odd(j)?(-1):(1)));
			}
		}
		cout<<s;
		return 0;
	}
	for (long long i=1;i<=b/2;i++){//在图中可以看到，蓝色框的后半部分绝对值都为0/1，因此考虑后半程加快运算
		long long f=1ll,temp=0ll;
		if (odd(i)){
			f=-1ll;
		}//判断该列正负号
        /*NOIP2018RP++*/
		long long ns=((a)/i+1ll)*i,ne=((b)/i)*i-1ll;
		temp+=((ns-a)*(a/i)+(b-ne)*(b/i));
		long long us=ns/i,ue=ne/i;
		long long res=(us<=ue)?(sum(ue)-sum(us-1)):0;
        /*NOIP2018RP++*/
		s+=(temp+res*i)*f;
	}
	for (long long i=b/2+1;i<=b;i++){
		long long f=1ll;
		if (odd(i)){
			f=-1ll;
		}
		long long ns=max(i,a),ne=b;//有多少个±1
		s+=(ne-ns+1)*f;
	}
	cout<<s;
	return 0;
}
```
代码中两行$NOIP2018RP++$注释中间的思路是这样的：   
考虑和式$a+a+...+a+(a+1)+(a+1)+...+(a+1)+...+b+b+...+b$（其中除首尾的$a$,$b$之外，项数均相同），我们先用$O(1)$时间把$a$、$b$的部分和算出来，再用等比数列求和公式，$O(1)$时间内把剩余的和算出。   
至于上下界那里令人恶心的上取整、下取整，本人表示不想再提。多注意边界情况。

----

emmm时间复杂度大概$O(B)$，然后就过了？（吸入氧气单点最大341ms，不吸貌似700ms？）

---

## 作者：暴力出奇迹 (赞：3)

首先很容易发现，可以对 $[1,B]$ 和 $[1,A-1]$ 求解，然后两者相减即可。

写一个 $solve$ 函数对 $[1,x]$ 求解：
```cpp
inline LL solve(LL x) {
	LL ret = 0;
	for(LL i = 1; i <= x; i++)
		for(LL j = 1; j <= i; j++)
			if(j & 1) ret -= i / j;
			else ret += i / j;
	return ret;
}
```
时间复杂度 $O(n^2)$，可以得 $55$ 分。

这时候我们很容易想到分块打表，但是你可以算一下打表到 $2 \times 10^7$ 需要多长时间 QAQ。

然后我们可能会想到对于每一个 $i$，用 $O(1)$ 的时间复杂度求出当前一轮对答案的贡献。然而我们很难做到，因为这个 $(-1)^j$ 很难处理，而且只给定被除数，想求解也很麻烦。

所以我们就想出来了一个神奇的思路：

**先枚举 $j$！**

这样，以上的两个问题都解决了：
1. $(-1)^j$ 显然不成问题了。
1. 给定除数比给定被除数简单多了。

先写出暴力代码：
```cpp
inline LL solve(LL x) {
	LL ret = 0;
	for(LL j = 1; j <= x; j++) {
		LL now = 0;
		for(LL i = j; i <= x; i++)
			now += i / j;
		if(j & 1) now = -now;
		ret += now;
	}
	return ret;
}
```
接下来很容易优化了：直接枚举 $\lfloor\dfrac{i}{j}\rfloor$ 即可。

显然，对于 $\lfloor\dfrac{x}{j}\rfloor-1$ ，这一部分是完整的；对于 $\lfloor\dfrac{x}{j}\rfloor$，则需要特殊处理。

接下来的这一段比较抽象，建议反复阅读：

1. 对于第一部分，每一个整除后的结果都恰好出现了 $j$ 次，所以我们可以算出 $\sum\limits_{i=1}^{\lfloor\frac{x}{j}\rfloor-1}i$，然后 $\times j$即可，可以用小学学过的等差数列求和化简一下。

1. 对于第二部分，$\lfloor\dfrac{x}{j}\rfloor$ 出现的次数是 $x \bmod j + 1$ 次，所以两者相乘即可啦。

具体看代码吧：
```cpp
#define LL long long
inline LL solve(LL x) {
	LL ret = 0;
	for(LL j = 1; j <= x; j++) {
		LL now = (x / j) * (x / j - 1) / 2 * j;
		now += (x % j + 1) * (x / j);
		if(j & 1) now = -now;
		ret += now;
	}
	return ret;
}
```
主函数很简单，不给出了。

---

## 作者：tyccyt (赞：2)

这里是分段打表题解。

# 简化题意

求 
$$
\sum_{i=A}^B \sum_{j=1}^{i}\lfloor \frac{i}{j} \rfloor \times (-1)^j
$$

# $70$ 分

考虑整除分块（不会的来看看[这个题](https://www.luogu.com.cn/problem/P2261)和[资料](https://oi-wiki.org/math/number-theory/sqrt-decomposition/)）。

相信你看完了，但这里求的东西不是很模版，举个例子（$i=10$）：

|                    j                    |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  10  |
| :-------------------------------: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| $\lfloor \frac{10}{j} \rfloor \times (-1)^j$ | -10  |  5   |  -3  |  2   |  -2  |  1   |  -1  |  1   |  -1  |  1   |

主要观察 $6 \le j\le10$，你会发现每隔两个数就会抵消！！！

那么，就在整除分块时判断这个块长是不是奇数，如果是答案加上块末一点，否则不变。

时间复杂度：$O(B\sqrt B)$.

```cpp
#include <bits/stdc++.h>
using namespace std;
int A,B; 
int main()
{
	cin>>A>>B;
	long long ans=0;
	for(int i=A;i<=B;i++)
	{
		int l=1,r=1;
		while(l<=i)
		{
			r=i/(i/l);
			int t=r-l+1;
			//if(t&1)ans+=(i/r)*(r&1?-1:1);
        if(t%2==1)
    	   {
       	     if(r%2==0)ans+=(i/r);
            else ans+=-(i/r);
         }
			l=r+1;
		}
	}
	cout<<ans;
	return 0;
}
```

# $100$ 分

考虑分段打表。

直接把上面代码拿来分段打表！！！

然后就是漫长的等待（理论上应需一两个小时）~~

只出示打表代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int n=20000000,b=50000;//这个随你调，只要不MLE就行
int main()
{
	freopen("1.txt","w",stdout);
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		int l=1,r=1;
		while(l<=i)
		{
			r=i/(i/l);
			int t=r-l+1;
			if(t&1)ans+=(i/r)*(r&1?-1:1);
			l=r+1;
		}
		if(i%b==0)cout<<ans<<',';
	}
	return 0;
}
```

望通过~~~

---

## 作者：AlicX (赞：2)

## Solution 

为了方便，我们定义 $f_n=\sum_{i=1}^{n}\sum_{j=i}^{n} \lfloor\frac{i}{j} \rfloor \times (-1)^j$。于是答案即为 $f_b-f_{a-1}$。

观察到如果我们直接计算这个式子而不做丝毫变形的话时间复杂度是 $O(n^2)$ 的。  

考虑把先枚举 $j$，计算 $j$ 的贡献。此时就有了 $O(n \sqrt n)$ 的做法。

然后继续手模一些小数据就可以发现，$j$ 对答案的贡献应该是 $j$ 个 $1,2,3\dots (n-j)/j$。于是计算出 $n$ 在哪一块，计算出整块与单块的贡献即可。

```cpp
ll calc(int l,int r){ return 1ll*(l+r)*(r-l+1)/2; }  
ll get(int n){ 
	ll ans=0; 
	for(int j=1;j<=n;j++){ 
		ll w=(j&1)?-1:1,id=(n-j)/j+1,r=id*j-1; //id 表示 n 所在的块，r 表示上一块的最后的位置
		ans+=1ll*w*j*calc(1,id-1); //整块的贡献
        ans+=1ll*w*(n-r)*id; // 单块的贡献
	} return ans; 
} 
```


---

## 作者：CJ_Alexander (赞：2)

题目告诉我们：给出A，B，求出下面式子的值

![公式一](https://cdn.luogu.com.cn/upload/image_hosting/vxwzjzaf.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

题目描述就这么简单。

然后我们来推式子：

先把要求的变一下：

![gs2](https://cdn.luogu.com.cn/upload/image_hosting/c1yxiy84.png)

考虑到-1的j次方不好处理，我们把枚举顺序换一下。

![gs3](https://cdn.luogu.com.cn/upload/image_hosting/htpuo3ow.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

后面那项同理。

然后，我们运用等差出列求和的公式，就可以很轻松地把这个式子在O(n)的时间内求出来了。

核心代码：
```cpp
int calc(int x)
{
	int res = 0;
	for(int j = 1;j <= x;j++)
	{
		int tmp = (x-j+1)/j,oth = x-j+1-tmp*j;
		if(j&1)
			res -= (1+tmp)*tmp/2*j+oth*(tmp+1);
		else
			res += (1+tmp)*tmp/2*j+oth*(tmp+1);
	}
	return res;
}
```

---

## 作者：CrTsIr400 (赞：1)

我不想推式子，于是考虑分段打表。

首先我们需要学会整除分块计算单个 $n$ 的答案。

它的优势在于值域比较小的时候操作次数是 $O(\sqrt n)$ 级别的。由此我们可以用它作为内层暴力算法。

它的操作不难，如果我有最长 $[l,r]$ 数值区间满足 $\lfloor\dfrac{n}{l}\rfloor=\lfloor\dfrac{n}{r}\rfloor$ 那么就可以对于区间统计答案。按照 $[l,r]$ 区间长的奇偶性判断即可。

于是暴力算法就这样写出来了：（这个是打表程序，实际上可以取得 $70$ 分）

```cpp
LL calc(I n){
	LL ans(0);
	for(I l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		ans+=((r-l+1)&1?(r&1?-1:1):0)*(n/l);}
	return ans;}
I main(){I A,B;LL ans(0);
	in(A,B);
	fo(i,A,B){
		ans+=calc(i);}
	return printf("%lld\n",ans),0;}

```

然后本地跑暴力。多线程暴力跑一跑大概就可以半个小时内出解。

每 $len$ 个数分一个块算答案，整块直接暴力求和，散块直接暴力计算。

时间复杂度是 $O(len\times \sqrt{B})$ 的，$B$ 的最大值为 $2\times 10^7$，取 $len=10^4$。因为整除分块两倍常数的原因，运算总数不超过 $9\times 10^7$ 次，可以通过。

于是这道题就结束了。[代码比较长，放到了剪贴板里面。](https://www.luogu.com.cn/paste/2eifd5yx)

---

## 作者：huangkx (赞：1)

## 思路

要求的是：

$$
\sum _ { i = A } ^ B \sum _ { j = 1 } ^ i \lfloor \frac { i } { j } \rfloor \times ( - 1 ) ^ j
$$

用前缀和的形式表示。得到：

$$
( \sum _ { i = 1 } ^ B \sum _ { j = 1 } ^ i \lfloor \frac { i } { j } \rfloor \times ( - 1 ) ^ j ) - ( \sum _ { i = 1 } ^ { A - 1 } \sum _ { j = 1 } ^ i \lfloor \frac { i } { j } \rfloor \times ( - 1 ) ^ j )
$$

现在要求的是：

$$
\sum _ { i = 1 } ^ n \sum _ { j = 1 } ^ i \lfloor \frac { i } { j } \rfloor \times ( - 1 ) ^ j
$$

先枚举 $j$。得到：

$$
\sum _ { j = 1 } ^ n ( - 1 ) ^ j \times \sum _ { i = j } ^ n \lfloor \frac { i } { j } \rfloor
$$

化简后半部分。得到：

$$
\sum _ { j = 1 } ^ n ( - 1 ) ^ j \times ( \frac { 1 } { 2 } \times \lfloor \frac { n } { j } \rfloor \times ( \lfloor \frac { n } { j } \rfloor + 1 ) \times j - \lfloor \frac { n } { j } \rfloor \times ( ( \lfloor \frac { n } { j } \rfloor + 1 ) \times j - 1 - n ) )
$$

整理。得到：

$$
\sum _ { j = 1 } ^ n \lfloor \frac { n } { j } \rfloor \times ( n + 1 ) \times ( - 1 ) ^ j - \frac { 1 } { 2 } \times \lfloor \frac { n } { j } \rfloor \times ( \lfloor \frac { n } { j } \rfloor + 1 ) \times j \times ( - 1 ) ^ j
$$

用数论分块计算即可。

时间复杂度为 $\mathcal { O } ( \sqrt B )$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int A, B;
int Solve(int n)
{
	if(n == 0) return 0;
	int res = 0;
	for(int l = 1, r; l <= n; l = r + 1){
		r = n / (n / l);
		res += (n / l) * (n + 1) * ((r - l + 1) % 2 ? (l % 2 ? - 1 : 1) : 0)
			- (n / l) * (n / l + 1) / 2 * ((r - l + 1) / 2 - ((r - l + 1) % 2 ? r : 0)) * (l % 2 ? 1 : - 1);
	}
	return res;
}
signed main()
{
	scanf("%lld%lld", & A, & B);
	printf("%lld\n", Solve(B) - Solve(A - 1));
	return 0;
}
```

## 闲话

我翻了下题解区，发现没有一样的做法，于是写了这篇题解。

我本以为这个做法常数很小，就尝试卡到最优解。但是就是差几毫秒，怎么卡常也没用。也许是评测机的原因吧。

2022.12.16

---

## 作者：zhiyangfan (赞：1)

### 题意
给出 $A,B$，求下面的式子：
$$\sum_{i=A}^B\sum_{j=1}^i(-1)^j\left\lfloor\dfrac{i}{j}\right\rfloor$$
($1\le A\le B\le 2\times10^7$)
### 题解
小清新式子题。首先用差分转成前缀的形式，然后看见这个下取整可以联想到整除分块，但现在的样子直接整除分块是 $\mathcal{O}(B\sqrt{B})$ 的，显然无法通过，所以要推一推式子。设当前想求的式子是 $\sum_{i=1}^n\sum_{j=1}^i(-1)^j\left\lfloor\frac{i}{j}\right\rfloor$。

考虑枚举这个分式的值：
$$\sum_{k=1}^n\sum_{i=1}^n\sum_{j=1}^i(-1)^jk\left[\left\lfloor\dfrac{i}{j}\right\rfloor=k\right]$$
交换一下求和顺序：
$$\sum_{k=1}^nk\sum_{j=1}^n(-1)^j\sum_{i=j}^n\left[\left\lfloor\dfrac{i}{j}\right\rfloor=k\right]$$
现在我们的重点聚焦到了关于 $i$ 个那个求和，即 $\lfloor\frac{i}{j}\rfloor=k$ 的 $i$ 有多少。考虑这个条件相当于：
$$jk\le i<j(k+1)$$
所以 $i$ 要满足的条件为 $i\in[jk,\min(j(k+1),n+1))\cap\mathbb{Z}$，所以对于给定的 $j$，上面那个关于 $i$ 的求和的值为：
$$\begin{cases}j(k+1)-jk=j&j(k+1)\le n\\n-jk+1&j(k+1)>n\end{cases}$$
所以把 $j$ 的和式拆开，原式子又可以化为：
$$\sum_{k=1}^nk\left(\sum_{j=1}^{\lfloor\frac{n}{k+1}\rfloor}(-1)^jj+\sum_{j=\lfloor\frac{n}{k+1}\rfloor+1}^{\lfloor\frac{n}{k}\rfloor}(-1)^j(n-jk+1)\right)$$
我们发现现在就能做了，只需要对 $\left\lfloor\frac{n}{k}\right\rfloor,\left\lfloor\frac{n}{k+1}\right\rfloor$ 做整除分块就行了。时间复杂度为 $\mathcal{O}(\sqrt{n})$。

我推到这儿的时候，跑去实现花了点功夫，这里顺便再讲一些实现的具体细节吧。

首先要把 $\sum_{k=1}^nk$ 这个和式乘进去把待求的玩意分成两部分，然后我们发现要求三种前缀和：
$$\sum_{k=1}^nk\qquad\sum_{j=1}^n(-1)^jj\qquad\sum_{j=1}^{n}(-1)^j(n-jk+1)$$
第一个简单，第二个需要简单打个表看一下：
$$\begin{array}{c|c}\mathbf{n}&\mathbf{\sum}\\1&-1\\2&1\\3&-2\\4&2\\5&-3\\6&3\\\vdots&\vdots\end{array}$$
容易发现答案就是 $(-1)^n\lceil\frac{n}{2}\rceil$。第三个稍显复杂，不过分析一下可以发现，对于 $n,1$ 的求和，如果 $n$ 为偶数会全部抵消，否则会变为 $-n-1$。而对于 $-jk$ 的求和只需要套第二个前缀和然后乘上 $k$ 即可。具体实现见代码，注意一些边界情况。
```cpp
#include <cstdio>
#include <algorithm>
typedef long long ll;
inline int getNegSum(int x) { return ((x + 1) >> 1) * (x & 1 ? -1 : 1); }
inline ll getSum(ll l, ll r) { return (r - l + 1) * (r + l) / 2; }
inline ll getCmpSum(int r, int n, int k)
{
	ll ret = 0;
	if (r & 1) ret -= n + 1;
	ret -= (ll)getNegSum(r) * k; return ret;
}
inline ll getCompSum(int l, int r, int n, int k)
{
	if (l > r) return 0;
	return getCmpSum(r, n, k) - getCmpSum(l - 1, n, k);
}
inline ll solve(int n)
{
	ll ans = 0;
	for (int l = 1, r; l + 1 <= n; l = r + 1)
	{
		r = (n / (n / (l + 1))) - 1;
		ans += (ll)getSum(l, r) * getNegSum(n / (l + 1));
	}
	for (int l = 1, r; l + 1 <= n; l = r + 1)		
	{
		r = std::min((n / (n / (l + 1))) - 1, (n / (n / l)));
		ans += (ll)getSum(l, r) * getCompSum(n / (l + 1) + 1, n / l, n, l);
	}
	ans += (ll)n * getCompSum(1, 1, n, n);
	return ans;
}
int main()
{
	int a, b; scanf("%d%d", &a, &b);
	printf("%lld\n", solve(b) - solve(a - 1)); return 0;
}
```
ps. 写完发现题解区有思路差不多的，那就当做是对实现细节的补充吧 qwq

---

## 作者：WhxStar2024 (赞：0)

## 本题思路：
这道题在考场时被诈骗了，以为只能打一个整除分块，结果只有暴力的 $70$ 分……

经过老师的提点，我知道了如果我们交换枚举顺序，我们就可以发现这些数字被除时是有规律，我们发现除数会从一开始单调递增，并且每一种数都会有当前除数个。

那么我们就可以直接枚举除数，用等差数列求和公式算出从 $1$ 到 $A-1$ 与 $B$ 的结果，两个相减即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,ans1,ans2;
signed main(){
	cin>>a>>b;
	for(int i=1;i<=b;i++){
		int p=1;
		if(i%2) p=-1;
		int sum=(1+(b/i-1))*(b/i-1)/2*i+(b/i)*(b%i+1);
		ans1+=sum*p;
	}
	a--;
	for(int i=1;i<=a;i++){
		int p=1;
		if(i%2) p=-1;
		int sum=(1+(a/i-1))*(a/i-1)/2*i+(a/i)*(a%i+1);
		ans2+=sum*p;	
	}
	cout<<ans1-ans2;
	return 0;
}
```

---

## 作者：呆瓜yy (赞：0)

我一开始看这道题时很崩溃，但其实这道题并不难(也许吧).下面是一篇比较容易理解的题解~~（看不懂就算了^_^）~~

首先为像我一样的初中生解释一下集合：简单地来说，这道题就是要求嵌套for循环

```cpp
for(int i=a;i<=b;i++)
      for(int j=1;j<=i;j++)
        if（j&1）
          s+=-i/j;
        else
          s+=i/j;
```
    
   中s的结果。~~（求和符号的本质就是循环）（至少我是这么认为的）~~    
   
   但是，这样硬做会超时（我就是这样水了55分）。其实，只要换一种方式做就可以了：
   
   当a=1,b=8时，要求的就是以下这些数的和：
   
|1
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
|1  |2  
|1  |2  |3  
|1  |2  |3  |4  
|1  |2  |3  |4  |5  
|1  |2  |3  |4  |5  |6  
|1  |2  |3  |4  |5  |6  |7  
|1  |2  |3  |4  |5  |6  |7  |8

   
仔细观察就会发现，**一般情况下**（a=1），1会重复加b次，2会重复加（b-1）次，3会重复加（b-2）次……
那么，我们只要用for循环枚举就行了（当让是与上面不同方法）


```cpp
	#include<cstdio> 
  
	#include<iostream>
  
	using namespace std;

	int a,b,k,i,l;
	
	unsigned long long s;

	int main(     )

	{

    scanf("%d%d",&a,&b);
    
    for(int j=1;j<=b;j++)
    
    {
    	if(j%2==1)
    	  l=-1;
    	else
    	  l=1;//判断奇偶
    	if(j<a)//特殊情况1：当j<a时，j重复加的次数就不是（b-j+1）次了。
	  {
	  	  if(a%j==0)//特殊情况2：（我也忘了是什么）
		  {
	  	  	 k=a/j;
             for(i=a;i<=b;i+=j)
             {
        	    s+=k*l*j;
        	    k++;
		     }
		     if((b+1)%j!=0)//特殊情况3：多加了，要减去重复的。
		       s=s-(i-b-1)*(k-1)*l;
		  }
		  else
		  {
		  	 k=a/j+1;
		  	 s+=(a/j)*(k*j-a)*l;
		  	 for(i=k*j;i<=b;i+=j)
		  	 {
        	    s+=k*l*j;
        	    k++;
		     }
		     if((b+1)%j!=0)
		       s=s-(i-b-1)*(k-1)*l;
		  }
	  }
	  else
	  {
	   	  k=1;
	   	  for(i=j;i<=b;i+=j)
	   	  {
	   	  	   s+=k*l*j;
	   	  	   k++;
		  }
		  if((b+1)%j!=0)
		  	s=s-(i-b-1)*(k-1)*l;
	  }
	} 
    printf("%lld",s);
    return 0;
}
```


假如这个方法有问题，那就是数据太水了~~（管它呢，我就这么过了 ）~~

**~~若题解的某些部分与程序不符，请见谅，因为我是做出来很久之后才写题解的。~~**

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P4863)

#### 思路

稍微推一下式子，能够发现对于一个数 $j$ 满足 $a \le j \le b$，那么对答案就为 $\sum_{i=j}^{b}\lfloor \frac{i}{j} \rfloor$，然后发现这是一个等差数列，每  $j$ 个值加一，可以用公式快速求出这一段的值在减去左边一段多算的和右边一段多算的就行了。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,ans,n,l;
int main()
{
	scanf("%lld%lld",&a,&b);
	for(long long i = 1;i <= b;i++)
	{
		a = max(a,i);
		l = ((b / i) * i - (a / i) * i - 1) / i + 2;
		if((b / i) * i == (a / i) * i) l--;
		if(i % 2 == 1) ans -= (i * (a / i + b / i) * l / 2 - (b / i) * (((b / i + 1) * i - 1) - b) - (a / i) * (a - (a / i) * i));
		else ans += (i * (a / i + b / i) * l / 2 - (b / i) * (((b / i + 1) * i - 1) - b) - (a / i) * (a - (a / i) * i));
	}
	printf("%lld",ans);
	return 0;
}
```


---


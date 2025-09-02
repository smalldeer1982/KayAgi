# [ABC014C] AtColor

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc014/tasks/abc014_3

 AtColor社は，$ 0 $ から $ 1,000,000 $ まで $ 1,000,001 $ 通りの濃さがある灰色の絵の具を販売することにしました．$ 0 $ が最も黒く，$ 1,000,000 $ が最も白い絵の具です．

 しかし，途方も無い数の濃さのバリエーションがある一方，消費者には細かい違いが分からないということが判明しました．これを知ったAtColor社は，売れない濃さの絵の具を生産するのはやめて，最も人気のある濃さの色の絵の具1つだけを販売することにしました．

 AtColor社は上記を達成するために，最も人気な絵の具がどのくらい売れるかをアンケート調査で調べることにしました． AtColor社がどの範囲の濃さの絵の具なら購入したいかというアンケートを消費者に対して行ったところ， 「$ a\ ≦\ x\ ≦\ b $ を満たす濃さ $ x $ の絵の具ならば購入する」という形式の情報が $ n $ 件得られました．

 あなたの仕事は，これらの情報から，最も多くの消費者に購入される濃さの絵の具について，その絵の具を購入する消費者の数を出力するプログラムを作ることです．

## 说明/提示

### 部分点

この問題には2つのデータセットがあり，データセット毎に部分点が設定されている．

- $ 1≦n≦2,000 $ を満たすデータセット 1 に正解した場合は $ 30 $ 点が与えられる．
- 追加制約のないデータセット 2 に正解した場合は，上記のデータセットとは別に $ 70 $ 点が与えられる．

### Sample Explanation 1

\- 濃さ $ 0,1,4,5,6 $ の絵の具は，1人の消費者によって購入してもらえます． - 濃さ $ 2 $ の絵の具は，3人の消費者によって購入してもらえます． - 濃さ $ 3 $ の絵の具は，2人の消費者によって購入してもらえます． - 他の濃さの絵の具は誰にも購入してもらえません． よって，$ 3 $ を出力します．

## 样例 #1

### 输入

```
4
0 2
2 3
2 4
5 6```

### 输出

```
3```

## 样例 #2

### 输入

```
4
1000000 1000000
1000000 1000000
0 1000000
1 1000000```

### 输出

```
4```

# 题解

## 作者：Grisses (赞：7)

[题面](https://www.luogu.com.cn/problem/AT1011)

这题是一道 **差分** 的模板题。

## 差分

差分是一种可以在 $O(1)$ 的时间复杂度内完成区间修改的东西。

对于一个数组 $a_1,a_2 \cdots a_n$，它的差分数组是 $a_1-0,a_2-a_1\cdots a_n-a_{n-1}$。

如果我们需要将 $[l,r)$ 区间全部加上 $x$，那么我们只需要将差分数组 $b$ 的 $b_l$ 加上 $x$，将 $b_r$ 减去 $k$ 即可。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,a,b,ans,x[1000005];//x是差分数组
  signed main()
  {
      scanf("%d",&n);
      while(n--){
          scanf("%d%d",&a,&b);
          x[a]++;
          x[b+1]--;//修改
      }
      ans=x[0];
      for(int i=1;i<=1000000;i++)x[i]+=x[i-1],ans=max(ans,x[i]);//求值，去max
      printf("%d\n",ans);
      return 0;
  }
```

---

## 作者：zjyqwq (赞：7)

### AT1011 AtColor题解
我又来发题解了！！！Pascal题解来一发！！！


------------
#### 解题思路
一眼看上去，这不是很简单吗！直接打一暴力。
```Pascal
var
n,i,x,y,j,max:longint;
a:Array[0..1000000]of longint;//定义
 begin
  readln(n);
  for i:=1 to n do //边输入边处理
   begin
    readln(x,y);
    for j:=x to y do //枚举范围
     begin
      a[j]:=a[j]+1;//+1+1……
      if a[j]>max then max:=a[j];//比较大小
     end;
   end;
  write(max);//输出
 end.

```
然后，就错了。

很明显，十万的双重枚举肯定炸呀。

我去问 [ZYZ](https://www.luogu.com.cn/user/188286)巨佬，他教我了一种新的方法——[差分](https://blog.csdn.net/qq_44879626/article/details/107734704)。


那如何将差分运用在这题上面呢？

我们用数组 $a[]$ ，令 $a[x]$ 为 $x$ 号区间减去 $x-1$ 号区间的值，这样就可以使时间复杂度为 $o(n)$ 了。



------------
#### 代码
```Pascal
var
n,i,x,y,j,ans,m:longint;
a,s:Array[-10..10000000]of longint;//定义部分，不多讲
 begin
  readln(n);m:=0;
  for i:=1 to n do 
   begin
    readln(x,y);//输入
    a[x]:=a[x]+1;a[y+1]:=a[y+1]-1;//进行差分，要注意这里是y+1。
    if y+1>m then m:=y+1;//一个小优化，记录最大的区间编号。
   end;
  for i:=0 to m do
  begin
   a[i]:=a[i-1]+a[i];//还原数组
   if a[i]>ans then ans:=a[i];//比较大小
  end;
  writeln(ans);//输出
 end.
```
结束了！！！


---

## 作者：tZEROちゃん (赞：4)

### Other Ver.

**中文**・[日本語](https://www.luogu.com.cn/paste/joa0on9y)・[English](https://www.luogu.com.cn/paste/kduh3ow4)

### Solution

差分。

那么，差分是什么？

首先你有一个可爱的 $a$ 数组，你还有一个可爱的 $b$ 数组。

那么如果说 $a_i = b_1 + b_2 + \cdots + b_i$，那么这个 $a$ 数组就是 $b$ 数组的 **前缀和数组**，反过来，我们称 $b$ 数组是 $a$ 的 **差分数组**。

那么 $b$ 数组大概是这个样子（$a_0 = 0$）：

- $b_1 = a_1 - a_0$；
- $b_2 = a_2 - a_1$；
- $b_3 = a_3 - a_2$；
- $b_4 = a_4 - a_3$；
- $\cdots$
- $b_n = a_n - a_{n - 1}$。

那么当我们有 $b$ 数组的时候，我们就可以用很快的时间（$O(n)$）得到 $a$ 数组。

那么显然，这题我们可以用差分解决。

因为 $a$ 是 $b$ 的前缀和数组，而如果我们改变 $b_i$ 的话，那么 $a_i$，$a_{i + 1}$，$\cdots$，$a_n$ 都会被改变。

假如我们要给 $[l, r]$ 这个区间加上 $k$，那么就可以用这些可爱的步骤来：

1. 让 $b$ 数组 $b_l$ 加上 $k$；
2. 让 $b$ 数组 $b_{r + 1}$ 减去 $k$；

通过第一次操作，$b$ 数组中第 $l$ 个元素之后都加上了 $k$；通过第二次操作，$b$ 数组中第 $r + 1$ 个元素之后都减去了 $k$，然后你就发现 $[l, r]$ 这个区间的数都加了 $k$，而对于第 $k$ 个元素之后的数都没有改变。

于是单次修改的时间复杂度是 $O(1)$。

这是一个差分的模板：

```cpp
for(int i = 1; i <= n; i++) {
  scanf("%d", &d[i]); // 原数组
}

for(int i = 1; i <= m; i++) {
  int l, r, k; // 将 d[l] ~ d[r] 元素值加上 k
  cin >> l >> r >> k; 
// 差分数组 b
  b[l] += k;
  b[r + 1] -= k;
}

// 前缀和数组 a
for (int i = 1; i <= n; i++) {
  a[i] = a[i - 1] + b[i];
}
// 累加结果
for (int i = 1; i <= n; i++) {
  s[i] = d[i] + a[i];
}
```

然后这个可可爱爱的 $s$ 数组就是答案。

好耶！你发现这题就是模板嘛，而且比模板还简单，$k = 1$，原数组的所有元素都是 $0$，然后就做完了 qwq。

---

## 作者：Swire (赞：3)

这道题好像就是一个裸的区间覆盖

为什么可以评到紫题（应该是个橙题吧）

望管理员有空修改一下难度评级


```cpp
#define R register//当时没看清数据范围加了一些常数优化，可以忽略
#include<cstdio>
const int MAXN=1e6+7;
int n,times,mx,ma;
int cover[MAXN];
int MAX(int a,int b){
	return a>b?a:b;
	//听说手写max会变快？？？
}
int main(void){
	scanf("%d",&n);
	for(R int i=1;i<=n;i++){
		int l,r;
		scanf("%d%d",&l,&r);
		mx=MAX(mx,r);//只记录有被覆盖到的区间
		cover[l]++;//起点覆盖次数+1
		cover[r+1]--;//终点（记得要+1）覆盖次数-1
	}
	for(R int i=0;i<=mx;i++){
		times+=cover[i];
		ma=MAX(ma,times);
	}
	printf("%d\n",ma);
	return 0;
}
```


---

## 作者：zct_sky (赞：3)

### Description:
-----
给你 $n$ 个区间，每次将区间中的数增加 $1$，最后求出区间内的最大值。
### Solution:
-----
这题很明显是一道裸的差分数组。

那么，什么是差分呢？

设有一个数列为 $a_1,a_2,a_3,\dots,a_n$，

又有一数组 $b$，且 $b_i=a_i-a_{i-1}$。

则此时除了能知道 $b_i=a_i-a_{i-1}$，还能发现 $a_i=b_1+b_2+b_3+\dots+b_i$，
也就是 $a_i=\sum\limits_{j=1}^i b_i$。

这时我们就把 $a$ 数组称为 $b$ 数组的前缀和数组，把 $b$ 数组称为 $a$ 数组的差分数组。

然后我们再来看这题：

输入一个 $l$ 和 $r$，如果将 $l$ 到 $r$ 全部加 $1$，再将数组求一次差分数组，就能发现，只有 $a_l$ 为 $1$，$a_{r+1}$ 为 $-1$。

那么，每次输入一个 $l$ 和 $r$，只需将 $a_l$ 加 $1$，将 $a_{r+1}$ 减 $1$，最后求出它的前缀和数组，再找出前缀和数组里的最大值并输出即可。 
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){//快读，可快啦 
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
inline void write(int x){//快输 
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+48);
	return;
}
const int N=1e6+10;
int a[N],n,ans; 
int main(){
	n=read();
	for(int i=0;i<n;i++)
		a[read()+1]++,a[read()+2]--;//防止下面l=0时出错，所以将l和r都+1 
	for(int i=1;i<1e6;i++)
		a[i]+=a[i-1],ans=max(ans,a[i]);//求出前缀和数组，并找出最大值 
	write(ans);
	puts("");//坑点：如果不换行就会WA 
	return 0;
}
```

---

## 作者：零殇 (赞：1)

#### 题意

给定$n$个区间，每一次把每个区间加$1$，求最后所有区间中最大的数。

#### 思路

在这里，我们要引入一个概念——$\color{black}差分$

那么，什么是差分？

我们先假设一个原序列，名为$A$。

若对于每一个$i$，都有$B[i]=A[i]-A[i-1](B[0]=A[0])$，我们就说序列$B$是序列$A$的差分序列。

我们可以发现什么？

$B[i]=A[i]-A[i]$

可以转化为

$A[i]=A[i-1]+B[i]$

也就是说，原序列$A$其实就是差分序列$B$的前缀和！

现在我们回到这题。

首先，我们设定一个差分序列$a$。

当我们输入左边界$x$以及右边界$y$时，就将$a[x]+1$,这样后面计算原序列时，前缀和会把这个$1$一直带入后面。

但达到$y+1$时，我们就不能再加了，为了和前面的抵消，我们就要将$a[y+1]-1$。

最后我们再跑一边循环，用前缀和计算出原序列就可以得到答案了。

上代码：


```
#include<bits/stdc++.h>
using namespace std;
int a[1000001],b[1000001],n,x,y,maxn=-1,flag;
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d%d",&x,&y);
		a[x]++;
		a[y+1]--;
		maxn=max(y,maxn);
	}
	b[0]=a[0];
	flag=b[0];
	for(int i=1;i<=maxn;i++) {
		b[i]=b[i-1]+a[i];
		flag=max(flag,b[i]);
	}
	printf("%d\n",flag);
	return 0;
}
```

完结撒花~

---

## 作者：jxbe6666 (赞：0)

## 前置芝士：前缀和与差分
**前缀和：** 前缀和是一个数组的某项下标之前(包括此项元素)的所有数组元素的和。  
定义式：$b_i=\sum\limits^i_{j=0}a_i$。

递推式：$b_i=b_{i-1}+a_i$。

在信奥中前缀和通常作为优化算法来优化时间复杂度，在区间求和时暴力算法需要 $O(n^2)$，而前缀和只需 $O(n)$。~~真是一大卡常神器~~   

**差分：** 差分是一种和前缀和相对的策略，就是用一个 b 的数组用来记录数组 a 的变化情况。如果要把 l 到 r 的区间加 n。就只要：
```cpp
for(int i=1;i<=a_length;i++){
	b[i]=a[i];
}
b[l]+=n; b[r]-=n;
```
再给 b 数组求一次前缀和就好了。

也能像前缀和一样把区间修改的时间复杂度从 $O(n^2)$ 优化到 $O(n)$。~~也是一大卡常神器~~  

------------

**题目分析：** 对于这道差分模板题，简单自然是挺简单的，就是要注意几个小坑点。  
坑点 1：差分的范围要注意，是 $l-r+1$。
坑点 2：最后在输出答案后，需要再输出一个换行符。  
解决了这些坑点后，AC 就不再是问题了。


------------
AC Code:
```cpp
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
#define ll long long
using namespace std;
const int N = 1e6 + 5;
int l, r, n, m;
int a[N];
inline int read()
{
    int number = 0, check = 1;
    char ch = getchar();
    while (ch < 48 || ch > 57)
    {
        check = ch == 45 ? -1 : 1;
        ch = getchar();
    }
    while (ch >= 48 && ch <= 57)
    {
        number = (number << 1) + (number << 3) + (ch ^ 48);
        ch = getchar();
    }
    return number * check;
}
inline void write(int X)
{
    if (X < 0)
    {
        X = ~(X - 1);
        putchar('-');
    }
    if (X > 9)
        write(X / 10);
    putchar(X % 10 + '0');
}
int main()
{
    int maxn = INT_MIN, maxsum = INT_MIN;
    n = read();
    for (int i = 1; i <= n; i++)
    {
        l = read();
        r = read();
        l++, r++;
        maxn = max(maxn, r);
        a[l]++;
        a[r+1]--;
    }
    for (int i = 1; i <= maxn; i++)
    {
        a[i] += a[i - 1];
        maxsum = max(maxsum, a[i]);
    }
    write(maxsum);
    putchar('\n');
    I AK IOI
}

```
[祝你们成功](https://www.luogu.com.cn/record/64630600) 


---

## 作者：szkzyc (赞：0)

这道题乍一看上去没什么思路，可能第一眼想到的就是暴力枚举，每次输入区间左端点和右端点后就再嵌套for循环加一

### 暴力代码：
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define reg register
using namespace std;
const int N = 100005;
int a[N], maxn = -1;
int maxx(int x, int y){//手写max函数， 算是优化吧 
	return x >= y ? x : y;//同等与if(x>=y)return x; else return y; 
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);//一些输入输出优化 
    int n;
    cin >> n;
    while(n--){ 
    	int x, y;
    	cin >> x >> y;//输入左端点和右端点 
    	for(int i = x; i <= y; i++){
    		a[i]++, maxn = maxx(maxn, a[i]);//区间每个数都加一，再判断最大值 
		}
	}
	cout << maxn << endl; //最后一定要输出换行！！我因为这个错误WA了两次 
	return 0;
}

```
但这样的话时间复杂度可就变成了$O(N^2)$,对于此题的数$n<=100000$是肯定会超时的，所以我们就要想办法找到$O(N)$的解法

### 前置芝士：前缀和与差分

PS:此处介绍部分参考[点我](https://www.pianshen.com/article/2386279923/)

如果有一数列 $a[1],a[2],.…a[n]$


且令 $b[i]=a[i]-a[i-1],b[1]=a[1]$

那么就有
$a[i]=b[1]+b[2]+.…+b[i]$

$=a[1]+a[2]-a[1]+a[3]-a[2]+.…+a[i]-a[i-1]$

此时b数组称作a数组的差分数组

换句话来说a数组就是b数组的前缀和数组

前缀和的优点是在于快速求出区间和

而差分呢？就是能快速进行区间修改

根据上面的内容可以推出在$[x,y]$区间每个数加z只要$a[x]+=z,a[y]-=z$即可

那在修改完以后，该怎么找出最大值呢?

这个时候，我们可以再引入一个数组：$sum$数组

这个数组的作用就是前几项的和，也就是用来找出最大值辣！

如果你还有点不明白，那就让我再放个图（图片转载自[这里](https://blog.csdn.net/zsyz_ZZY/article/details/79918809))

![](https://img-blog.csdn.net/20180412202629489?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3pzeXpfWlpZ/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

里面的d数组就相当于b数组哦

这样下来是不是就很容易了!

### 来，上代码！
```cpp
#includ <bit/stdc++.h>
#define ull unsigned long long
#define ll long long
#define reg register
using namespace std;
const int N = 100005;
int a[N], maxn = -1, h;
int maxx(int x, int y){//手写max函数，算是优化吧 
	return x >= y ? x : y;//同等与if(x>=y)return x; else return y; 
}
int mian(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);//一些输入输出优化 
    int n;
    cin >> n;
    while(n--){
    	int x, y;
    	cin >> x >> y;
    	a[x]++, a[y + 1]--;//利用差分即可O(1)的复杂度实现区间修改 
	}
	for(int i = 0; i <= N; i++) h += a[i], maxn = max(h, maxn); //寻找最大值 
	cout << maxn << endl;//最后一定要输出换行！！我因为这个错误WA了两次 
	return 0;
}
//请勿抄袭，营造美好的洛谷氛围哦 （抄袭后果自负） 
```

这个题解蒟蒻写了好久，求通过qaq

---

## 作者：Cambridge (赞：0)


蒟蒻又来发题解了！

我们先来讲一讲超了0.31s的算法，其实也就是纯暴力，将区间内的所有数的个数都加一，同时求最大值，代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
long long n,x,y;
int a[1000010],da;
int main()
{
cin>>n;
for(int i=1; i<=n; i++)
{
	cin>>x>>y;
	for(int j=x; j<=y; j++)
		a[j]++,da=max(da,a[j]);//将区间内的所有数的个数都加一，同时求最大值
}
cout<<da<<endl;//输出
    return 0;
}

```

这时候我们发现，超了0.31s，接下来我开始讲正解：前缀和。其实也就是我们设一个前缀和S数组，区间第一位为l，区间最后一位为r，然后Sl加一，Sr+1减一，然后就相当于区间中所有数加一。代码如下：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
long long n,x,y,maxs;
int a[1000010],da,djy,s[1000010];
int main()
{
cin>>n;
for(int i=1; i<=n; i++)
{
	cin>>x>>y;
	maxs=max(maxs,y+1);//求所有区间中最右边的位置
	s[x]++,s[y+1]--;//上头已解释
}
for(int i=0; i<=maxs; i++)
{
	djy+=s[i],da=max(djy,da);//求最大值
}
cout<<da<<endl;
    return 0;
}

```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：jijidawang (赞：0)

$n^2$ 肯定过不了百万所以差分裸题啊

差分的思路就是维护一个差分数组 $s$，每次 $[l,r]$ 区间覆盖就用 $s_l=s_l+1$，$s_{r+1}=s_{r+1}-1$。

对于 $s$ 做前缀和即可精准定位一个点的区间个数。

原理大概是前缀和中 $s_l$ 加了一后面全都加一了，$s_{r+1}$ 减一了就把后面全减一了导致 $[l,r]$ 全体加一的效果。

变成线性复杂度就肯定能过了。

Code:
```cpp
#include<iostream>
using namespace std;
const int N=1000005;
int s[N],l,r,n,sum,ans,maxnum;
int main()
{
	cin>>n;
	for (int i=0;i<n;i++)
	{
		cin>>l>>r;
		++s[l]; --s[r+1]; // 差分操作
		maxnum=max(maxnum,r+1); // 提前求出最大值使得不用求太多 max，这步优化可以不加，看数据范围能过
	}
	for (int i=0;i<=maxnum;i++){sum+=s[i]; ans=max(ans,sum);} // 对每个点的区间个数求 max
	cout<<ans;
	return 0;
}
```

---


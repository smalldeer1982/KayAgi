# Blink

## 题目描述

Farmer John 对于农场里昏暗的灯光很不满，于是他刚刚装上一个装饰精美的新吊灯。

这个吊灯由 $N(3 \le N \le 16)$ 个灯组成，并排成一个**圆圈**。

奶牛们对于这个新的发光装置很有兴趣。他们喜欢玩这样的一个游戏：

在在时刻 $T$ 时，对于每一盏灯 $i$，如果在时刻 $T-1$ 时，$i$ 左边的灯 $(1<i\le n$ 时为 $i-1$，$i=1$ 时，为 $n)$ 是开的，那么**改变第 $i$ 盏灯的状态**，否则不做操作。

他们会在 $B(1 \le B \le 10^{15})$ 个单位的时间里一直进行这样的操作。

**请注意，$B$ 可能会超过一般的 $32$ 位整数的范围。**

现在已知每一个灯的初始状态，请计算出在经过 $B$ 个单位的时间后，每一个灯的状态。

## 说明/提示

样例输出解释：

下面是样例输出的模拟

```cpp
Time T=0: 1 0 0 0 0
Time T=1: 1 1 0 0 0
Time T=2: 1 0 1 0 0
Time T=3: 1 1 1 1 0
Time T=4: 1 0 0 0 1
Time T=5: 0 1 0 0 1
Time T=6: 1 1 1 0 1

## 样例 #1

### 输入

```
5 6
1
0
0
0
0```

### 输出

```
1
1
1
0
1```

# 题解

## 作者：Mr_Li (赞：14)

由于N<=16，所以我们可以把灯的状态压成一个数。

由于B会超过32位数的范围，所以我们可以用倍增的方法解此题。

设用2^i的时间，会把可以压成j的灯的状态变成可以压成f[i][j]的灯的状态。

例如我们可以把“1 0 0 0 0”压成“16”，“1 0 1 0 0”压成“20”，“1 1 1 0 1”压成“29”，（这里利用了二进制的思想）于是f[1][16]=20，f[2][20]=29。

对于边界条件f[0][i]可以模拟。

倍增算法通用的状态转移方程是f[i][j]=f[i-1][f[i-1][j]]。

时间复杂度是O(2^Nlog B)。

附代码：

···cpp

```cpp
#include<iostream>
using namespace std;
long long n,b,i,j,f[51][65536]={},light,compress=0;
int main ()
{
    cin>>n>>b;
    for (i=0;i<1<<n;i++)
    for (j=0;j<n;j++)
    f[0][i]+=((i&1<<(j+1)%n)>0^(i&1<<j)>0)*(1<<j);
    for (i=1;i<=50;i++)
    for (j=0;j<1<<n;j++)
    f[i][j]=f[i-1][f[i-1][j]];
    for (i=1;i<=n;i++)
    {
        cin>>light;
        compress=compress<<1|light;
    }
    for (i=50;i>=0;i--)
    if (1LL<<i<=b)
    {
        b-=1LL<<i;
        compress=f[i][compress];
    }
    for (i=n-1;i>=0;i--)
    cout<<((compress&1<<i)>0)<<endl;
    return 0;
}
···
```

---

## 作者：Mo默Sh笙 (赞：4)

### [传送门](https://www.luogu.com.cn/problem/P2203)

~~好像并没有**矩阵快速幂**的题解，那我来写一篇~~

------------

## 题目分析
### 对于每两盏灯，只考虑右灯变化，分为四种情况：
左灯为 $1$，右灯为 $1$，右灯变为 $0$；

左灯为 $0$，右灯为 $0$，右灯不变，为 $0$；

左灯为 $1$，右灯为 $0$，右灯变为 $1$；

左灯为 $0$，右灯为 $1$，右灯不变，为 $1$；

设第 $i$ 盏灯状态为 $s[i]$。

#### 不难发现：
$$s[i] = s[i-1] \oplus s[i]$$

------------

### 可以构造如下 $N\times N$ 递推矩阵，用于进行递推：

$\begin{bmatrix}
1 & 1 & 0 & \cdots & 0 & 0 & 0\\
0 & 1 & 1 & \cdots & 0 & 0 & 0\\
0 & 0 & 1 & \cdots & 0 & 0 & 0\\
\vdots & \vdots & \vdots & \ddots & \vdots & \vdots & \vdots &\\
0 & 0 & 0 & \cdots & 1 & 1 & 0\\
0 & 0 & 0 & \cdots & 0 & 1 & 1\\
1 & 0 & 0 & \cdots & 0 & 0 & 1\\
\end{bmatrix}$

**（灯环形排列，需要头尾相接）**

------------

举个例子，当 $N=5$ 时，矩阵即为：

$\begin{bmatrix}
1 & 1 & 0 & 0 & 0\\
0 & 1 & 1 & 0 & 0\\
0 & 0 & 1 & 1 & 0\\
0 & 0 & 0 & 1 & 1\\
1 & 0 & 0 & 0 & 1\\
\end{bmatrix}$

递推矩阵推出来后，直接矩阵快速幂即可。


------------

## 朴实无华的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//十年OI一场空，不开long long见祖宗
inline int read(){int x=0;char ch=getchar();while(ch<'0'||ch>'9')ch=getchar();while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}return x;}
const int N=20;
const int p=2;
int n,m;
int s[N];
struct MS
{
	int c[N][N];
	int n,m;
};
MS operator *(const MS &a,const MS &b)//矩阵乘法
{
	MS c;
	c.n=a.n;
	c.m=b.m;
	for(int i=1;i<=a.n;i++)
		for(int j=1;j<=b.m;j++)
			c.c[i][j]=0;
	for(int i=1;i<=a.n;i++)
		for(int j=1;j<=b.m;j++)
			for(int k=1;k<=a.m;k++)
				c.c[i][j]=(c.c[i][j]+a.c[i][k]*b.c[k][j]%p)%p;
	return c;
}
MS fpow(MS a,int k)//矩阵快速幂
{
	MS e;
	e.n=n;
	e.m=m;
	for(int i=1;i<=n;i++) e.c[i][1]=s[n-i+1];
	while(k>0)
	{
		if(k&1) e=a*e;
		a=a*a;
		k>>=1;
	}
	return e;
}
MS init()//递推矩阵构造
{
	MS a;
	a.n=n;
	a.m=n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			a.c[i][j]=0;
	for(int i=1;i<=n;i++)
	{
		a.c[i][i]=1;
		a.c[i][i+1]=1;
	}
	a.c[n][1]=1;//头尾相接
	return a;
}
MS a;
signed main()
{
	int k;
	m=1;
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++) s[i]=read();
	a=init();
	MS ans=fpow(a,k);
	for(int i=n;i>=1;i--)
	printf("%lld\n",ans.c[i][1]);
	return 0;
}
```


---

## 作者：jiang_cheng (赞：2)

## 解题思路：
打模拟赛的一道题~~可我考试时没写出来~~，这道题b的数据很大，肯定是有循环节的，于是就压缩表示，并找循环节就出来了。（管理员大大最帅了，让我过吧！！！）
## 附上代码：
```cpp
#include <cstdio>
#include <iostream>

using namespace std;

const int kMaxN = 16;
const int kMaxL = 1 << 16;

int l[kMaxL], p[kMaxL];
int n, m, x;
long long b;

int main() {
  cin >> n >> b;
  for (int i = 0; i < n; i++) {  // 压缩表示
    cin >> x;
    l[1] |= x << i;
  }
  for (m = 1; !p[l[m]]; m++) {                                           // 寻找循环节
    p[l[m]] = m;                                                         // 记录位置
    l[m + 1] = l[m] ^ (l[m] << 1 & ((1 << n) - 1)) ^ (l[m] >> (n - 1));  // n位循环左移取与
  }

  if (++b >= m) {  // 超出循环节的部分取余
    b = (b - p[l[m]]) % (m - p[l[m]]) + p[l[m]];
  }
  for (int i = 0; i < n; i++) {  // 拆分输出
    cout << (l[b] >> i & 1) << endl;
  }
  return 0;
}
```


---

## 作者：Shadow_F (赞：1)

没有java的题解那我就提交一哈试试咯.

总体思路是寻找循环节,毕竟B的范围委实是太大了.

个人采用Arraylist来保存每次的结果,采用字符串拼接将每次录入或变换结束的结果拼接保存成为String存入.用自带方法判断是否存在.然后再逐一删除不是循环节内的.

具体看代码以及代码注释吧,单纯头脑逻辑边想边敲wa甚至re了=-=整体也可能有些乱,主要是看注释吧.





```java

import java.util.*;
public class Main{
    public static void main(String[] args)  {
        Scanner sc = new Scanner(System.in);
        //灯泡数以及时间
        int number=0;long time =0;
        //循环节长度(其实可以不放这里)
        int step = 0;
        number = sc.nextInt();
        //录入的时候这里第一次第二次是int所以re了,也要改long
        time = sc.nextLong();
        //是否存在循环节
        boolean breakTag = false;
        //当前的灯泡状态
        int[] tag = new int[number];
        //下一轮的灯泡状态
        int[] antherTag = new int[number];
        //准备拼接的Str
        String test1 ="";
        for(int i = 0;i<number;i++){
            antherTag[i] = tag[i]= sc.nextInt();
            String six = String.valueOf(tag[i]);
        }
        //保存Str
        ArrayList<String> test = new ArrayList<String>();
        //循环灯泡状态
        for(int i = 0;i<time;i++){
            for(int j = 0;j<number;j++){
                if(tag[j] == 1 && j != number-1){
                    antherTag[j+1] = Math.abs(antherTag[j+1]-1);
                }else if(tag[j] == 1){
                    antherTag[0] =  Math.abs(antherTag[0]-1);
                }
                if(j!=number-1){
                    test1= test1.concat(String.valueOf(antherTag[j+1]));
                }else  {
                    test1= String.valueOf(antherTag[0]).concat(test1);
                }

            }
            //java的坑--不能直接使用等于号,会改变引用
            tag = antherTag.clone();
            //是否存在,不存在则add
            if(!test.contains(test1)){
               
                test.add(test1);
                test1 = "";
            }else {
            //存在则开始判断循环节,剔除不在循环节内的并time--
               while (!test.get(0).equals(test1)){
                   test.remove(0);
                   time--;
               }
               //剩下的list长度就是循环节长度(所以上面定义其实没必要
               step = test.size();
               //取余
                int x = (int) ((time)%step);
                //由于index的特殊情况,以及list可能会存在长度为1全0的情况(全0下灯光不再变化)
                if(x-1 <0){
                    x =1;
                }
                //拆分String,逐一输出
                char[] strChar = test.get(x-1).toCharArray();
                for(int m = 0;m<strChar.length;m++){
                    System.out.println(strChar[m]);
                }
                breakTag = true;
               break;
            }
        }
        if (breakTag == false){
            char[] strChar = test.get(test.size()-1).toCharArray();
            for(int m = 0;m<strChar.length;m++){
                System.out.println(strChar[m]);
            }                                           
        }
    }
}
```

---

## 作者：十三陵 (赞：1)

没有C++题解?
那就发一个c++题解吧.

发现其实灯的状态是有规律的出现的.

因为,当n最大为16,那么灯的状态最多为2^16=65536种,那么其实我们边打表,边找循环节就行了.**注意**灯的状态经过一次操作得到结果,这过程不可逆,
**意味着可能很多情况经过操作可以得到相同结果!**,也等价于循环节不是从头开始的,可能从中间蹦出来

看代码吧

```c
#include<iostream>
#include<cstring>
using namespace std;
int l[505][20];  //储存灯的每次状态 
bool bo[20];	//判断灯上次的亮灭 
int n;
int f=0;	//循环头 
int t=1;	//周期 
long long b;
void print()
{
	for(int j=0;j<n;j++)
	{
		cout<<l[(b-f)%t+f][j]<<"\n";  //知道了循环节从f开始,以t为周期 
	} 
}
void judge(int a,int b)
{
	bool p=true;
	for(int j=0;j<n;j++)
	{
		if(l[a][j]!=l[b][j]) p=false;
	}
	if(p)
	{
		f=a;
		t=b-a;
	}
}
void init()
{
	for(int i=0;i<n;i++)
		cin>>l[0][i];
}
int main()
{
	cin>>n>>b;
	init();
	for(int i=1;i<=500;i++)
	{
		memset(bo,0,sizeof(bo));
		for(int j=0;j<n;j++)
		{
			if(l[i-1][j]==1) bo[j]=true; 	//强行读入上次的状态 
			l[i][j]=l[i-1][j];				//继承上次状态,然后下面进行操作 
		}
		for(int j=0;j<n;j++)
		{
			if(bo[j]) l[i][(j+1)%n]=1-l[i][(j+1)%n];  //翻转 
		}
		for(int j=1;j<i;j++)
		{
			judge(j,i);		//判断第j次是否在前j次出现过,出现了就找到了循环节了 
			if(t>1) break; 
		}
		if(i==b)  //如果没找到周期就碰到b了,直接输出吧 
		{
			for(int j=0;j<n;j++)
			{
				cout<<l[b][j]<<"\n";
			} 
			return 0;
		}
	}
	print();
	return 0;
} 
```

---

## 作者：66666a (赞：1)

这题b有10^15，模拟肯定不行

我们会发现，其实，灯的亮灭形态是循环出现的，因此，就变成找循环节的问题

同时，循环节并不是从初始状态开始的。我被这坑了好久

```cpp
label aaa;
var
j,n,i,x:longint;
b:qword;
a:array[-10..20,0..100000] of longint;
t:array[-10..20] of longint;
f:boolean;
function hh(i:longint):boolean;
var j,k:longint;
begin
for k:=0 to i-1 do
begin
for j:=1 to n do if a[j,i]<>a[j,k] then break;
if not(a[j,i]<>a[j,k]) then
begin
x:=k;
exit(true);
end;
end;
exit(false);
end;
begin
assign(input,'blink.in');
reset(input);
assign(output,'blink.out');
rewrite(output);
readln(n,b);
for i:=1 to n do
begin
readln(a[i,0]);
t[i]:=i-1;
end;
t[1]:=n;
f:=true;
i:=0;
while f do
begin
inc(i);
for j:=1 to n do
if a[t[j],i-1]=1 then
begin
if a[j,i-1]=0 then a[j,i]:=1 else a[j,i]:=0;
end else a[j,i]:=a[j,i-1];
if hh(i) then f:=false;
if i=b then goto aaa;
end;
i:=i-x;
b:=(b-x) mod i+x;
```
aaa:
for j:=1 to n do writeln(a[j,b]);

close(input);

close(output);

end.

---

## 作者：信守天下 (赞：1)

## 思路：寻找循环节
因为有$16$盏灯，数据范围为$10^{15}$

很明显，这道题一次一次模拟会超时

数据上限是$16$盏灯，就只有$16!$种可能

因为$10^{15}$ $>$ $16!$,所以这道题一定有循环节

所以思路就是记录状态，然后找循环节

所有的状态都可以压缩表示成一位进行优化

## $code$
~~~cpp
#include <iostream>
using namespace std;
const int kMaxN = 16;
const int kMaxL = 1 << 16;
int l[kMaxL], p[kMaxL];
int n, m, x;
long long b;
int main() {
  cin >> n >> b;
  for (int i = 0; i < n; i++) {  // 压缩表示
    cin >> x;
    l[1] |= x << i;
  }
  for (m = 1; !p[l[m]]; m++) {                                           // 寻找循环节
    p[l[m]] = m;                                                         // 记录位置
    l[m + 1] = l[m] ^ (l[m] << 1 & ((1 << n) - 1)) ^ (l[m] >> (n - 1));  // n位循环左移取与
  }
  if (++b >= m) {  // 超出循环节的部分取余
    b = (b - p[l[m]]) % (m - p[l[m]]) + p[l[m]];
  }
  for (int i = 0; i < n; i++) {  // 拆分输出
    cout << (l[b] >> i & 1) << endl;
  }
  return 0;
}
~~~

---

## 作者：COsm0s (赞：0)

本题数据范围：$n \leq 16$，$B \leq 10^{15}$。

如果打暴力，复杂度就为 $O(B)$，爆了。

再看一眼，发现：

**灯的状态是有规律的出现的。**

因为，当 $n$ 最大为 $16$，那么灯的状态最多为 $2^{16}$ 种，其实我们边打表，边找循环节就行了。（并不用二进制压缩）

**注意：循环节并不是从初始状态开始的。**

代码复杂度：$O(2^n \times n^2)$

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,cnt,x,y;
bool dp[70005][20];
inline ll read() {
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)) {
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)) {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x) {
	if(x < 0) {
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
//快读快输 
inline bool check(int x,int y) {
	for(int i = 1; i <= n; ++ i)
		if(dp[x][i] != dp[y][i]) return 0;
	return 1;
}
//判断是否循环 
signed main() {
	n = read(), cnt = read();
	for(int i = 1; i <= n; ++ i)
		dp[0][i] = read();
	//输入，默认为dp[0][i] 
	for(int i = 1; i <= pow(2, 16) + 1; ++ i) {//状态最多有2^16种 
		for(int j = 1; j <= n; ++ j) {
			dp[i][j] = dp[i - 1][j];
			if(dp[i - 1][(j - 1 == 0 ? n : j - 1)] == 1)
				dp[i][j] = !dp[i][j];
		}//将状态改变 
		for(int j = 1; j < i; ++ j) {
			if(check(j,i)) {
				x = j, y = i;
				break;
			}
		}//搜索循环节 
		if(cnt == i) {
			for(int j = 1; j <= n; ++ j)
				write(dp[i][j]),puts("");
			return 0;
		}//如果cnt<2^16，则直接输出 
	}
	for(int i = 1; i <= n; ++ i)
		write(dp[(cnt - 1) % (y - x) + 1][i]),puts("");
		//输出循环节，注意取模的时候会有0，所以要-1模后再+1 
	return 0;
}
```


---

## 作者：Lokawa (赞：0)

第一眼看见这个肯定想到强模拟

然而1 <= B <= 10^15 纯模拟不炸是不可能的

那么就成了一个找循环节的问题咯


喜闻乐见的代码君来咯

···var i,j,n,k:longint;

```cpp
m:qword;
a:array[0..1000000,1..16] of longint;
f:boolean;
function pd(x:longint):longint;
begin
  if x=1 then exit(n) else exit(x-1);
end;//环处理
begin
readln(n,m);
for i:=1 to n do readln(a[0,i]);//a[0,i]存初始状态
for j:=1 to m do
begin
  for i:=1 to n do
  begin
    if a[j-1,pd(i)]=1 then
    case a[j-1,i] of
    1:a[j,i]:=0;
    0:a[j,i]:=1;
    end;
    if a[j-1,pd(i)]=0 then a[j,i]:=a[j-1,i];
  end;//模拟得出新状态
  for i:=1 to j-1 do
  begin
    f:=true;
    for k:=1 to n do if a[i,k]<>a[j,k] then
    begin
      f:=false;
      break;
    end;
    if f then break;
  end;//判断是否循环
  if f then break;
end;
if j<m then
begin
   if (m-i+1) mod (j-i)=0 then
    for k:=1 to n do writeln(a[j-1,k])
   else for k:=1 to n do writeln(a[(m-i+1) mod(j-i)+i-1,k]);//输出循环节
end else for i:=1 to n do writeln(a[m,i]);//没有循环节就直接输出时间为m时的情况
end.
```
···
AC！

---

## 作者：时光 (赞：0)

来发pascal

其实不用想楼下那么麻烦，（至少我没看懂），讲个易懂的——————循环节。

eg：5 6

1
        0
        0
0 这个数据，把每一次都模拟出来，结果是

11000
10100
11110
10001
01001
11101
00011
10010
11011
00110
00101
10111
01100
01010
01111
11000
10100
11110
10001
01001
11101
00011
10010
11011
00110
00101
10111
01100
01010
01111
11000
10100
11110
10001
01001
11101
00011
10010
11011
00110
明显发现，15位一个循环，但不同的数据循环节不同，还要找

但是请注意，循环节并不是一定从第一位开始的

下一个要处理的问题是

怎么判断出现了循环节——用二进制储存，并储存他是在何时出现的

下面的实现看代码




```cpp
var ii,j,n,jinz,kk,hk:longint;
    g:boolean;
    m,i:qword;
    a:array[0..100000,0..20] of longint;//第i分钟的状态
    can:array[0..70000]of boolean;
    lj:array[0..70000]of longint;
function er(h:longint):longint;
var i,hh,k:longint;
begin
k:=1;
hh:=0;
for i:=n downto 1 do
begin
hh:=hh+a[h,i]*k;
k:=k*2;
end;
exit(hh);
end;
begin
readln(n,m);
g:=false;
fillchar(can,sizeof(can),false);
for ii:=1 to n do readln(a[0,ii]);
i:=0;
while i<m do
begin
inc(i);
a[i-1,0]:=a[i-1,n];
for j:=n downto 1 do
begin
if a[i-1,j-1]=1 then
if a[i-1,j]=1 then a[i,j]:=0 else a[i,j]:=1;
if a[i-1,j-1]=0 then a[i,j]:=a[i-1,j];
end;
jinz:=er(i);//求二进制
if can[jinz] then
begin
kk:=i-lj[jinz];
hk:=(m-i) mod kk;//不一定是第一位开始，减去开头
g:=true;
for ii:=1 to n do writeln(a[lj[jinz]+hk,ii]);
halt;
end
else
begin
can[jinz]:=true;
lj[jinz]:=i;
end;
end;
if not g then
for ii:=1 to n do writeln(a[m,ii]);//可能还没出现循环节，如样例
end.
end.

```

---


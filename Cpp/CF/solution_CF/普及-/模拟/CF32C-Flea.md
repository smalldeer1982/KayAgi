# Flea

## 题目描述

It is known that fleas in Berland can jump only vertically and horizontally, and the length of the jump is always equal to $ s $ centimeters. A flea has found herself at the center of some cell of the checked board of the size $ n×m $ centimeters (each cell is $ 1×1 $ centimeters). She can jump as she wishes for an arbitrary number of times, she can even visit a cell more than once. The only restriction is that she cannot jump out of the board.

The flea can count the amount of cells that she can reach from the starting position $ (x,y) $ . Let's denote this amount by $ d_{x,y} $ . Your task is to find the number of such starting positions $ (x,y) $ , which have the maximum possible value of $ d_{x,y} $ .

## 样例 #1

### 输入

```
2 3 1000000
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3 3 2
```

### 输出

```
4
```

# 题解

## 作者：Accepted_Z (赞：10)

打个小广告：[点我](https://www.luogu.org/blog/hhhh123/)

以下正文：

------------
### 思路
我们用a和b来记录行和列用步数整除后分别还剩下几格,也就是a=n%s,b=m%s

然后再用c和d来记录用步数可以把行列分别分成几段,也就是c=n/s,d=m/s 

其中：a加c乘s等于n,b加d乘s等于m

于是我们便可以很容易地发现：a和b是c和d除以s以后的余数。

所以a和b就被活生生的浪费掉了。但是为了得到最大值，我们就必须要把a和b利用起来。我们浪费a和b的根本原因是只把一个点作为了起点。如果我们能够把好几个点都作为起点，就能让行和列分成的段数(c和d)的值加一，只不过每次取的格子是余数，而不是每段格子数。

最后在输出a乘b乘c乘d的值，就233啦。
### 注意
(1)如果a或b的值是0,那行或列中的每段我们都可以挑,这时a=s或b=s

(2)本题测试数据较大，需要开long long
### 代码
以下是我的超短萌新代码
```cpp
#include <bits/stdc++.h>//万能头文件
using namespace std;
long long n,m,s,a,b,c,d;
int main()
{
	cin>>n>>m>>s;//输入
    a=n%s;b=m%s;//初始化a和b的值
    c=n/s;d=m/s;//初始化c和d的值
    if(a==0) a=s;//特判a等于0的情况
    else c++;//否则就把c的段数加一
    if(b==0) b=s;//特判b等于0的情况
    else d++;//否则就把d的段数加一
    cout<<a*b*c*d;//输出
    return 0;//233啦
}

```

---

## 作者：haozinojc (赞：2)

此题是一道非常简单的思维题。
### 思路：

用 $n_1$ 存行中剩下的格子数，也就是 $n\bmod s$。

用 $m_1$ 存列中剩下的格子数，也就是 $m\bmod s$。

用 $n_2$ 存行被分了几段，也就是 $n\div s$。

用 $m_2$ 存列被分了几段，也就是 $n\div s$。

通过 $n_1$ 和 $n_2$，我们很轻易地知道了初始位置的格子数，
再根据 $n_2$ 和 $m_2$，就把答案算出来了。

**什么？听不懂？**

见下图（保证小学生都能看得懂）：

![1](https://cdn.luogu.com.cn/upload/image_hosting/1j7yke8g.png)

#### 解释：$n=2,m=2,s=3$

对于红色的圈，他最多能到九个位置。

- 那么看看横着的：最右边（那个橙色的旁边）有两个空位，那么这时我们就可以在红圈右边的右边放一个蓝圈，这样它往右边也能延伸两个浅蓝圈。接下来在往蓝色右边放就延伸不了两个了，所以对于横着的，蓝色格子就是极限。

- 再看看竖着的：跟横着的一个道理，最下边（那个橙色的下边）有两个空位，那么这时我们就可以在红圈下边的下边放一个绿圈，这样它往右边也能延伸两个浅绿圈。接下来在往绿色下边放就延伸不了两个了，所以对于竖着的，绿色格子就是极限。

综上所述，棕色框里的所有格子就是能到达九个格子的。

那么剩下的就很简单了，算出棕色方框里有几个格子，再算出每个格子能到达的格子个数，最后相乘就好了。

现在知道上面的 $n_1$、$n_2$、$m_1$、$m_2$ 有什么用了吧。

**注：$n\bmod s$ 或 $m\bmod s$ 可能等于零哦，要记得处理一下。**

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,n1,n2,m1,m2,s;
signed main(){
	cin>>n>>m>>s;
	n1=(n-1)%s+1;m1=(m-1)%s+1;
	n2=n/s;m2=m/s;
	if(n1!=s)n2++;
	if(m1!=s)m2++;
	cout<<(n1*n2*m1*m2);
	return 0;
}
```


---

## 作者：刘嘉琦 (赞：2)

## 题意翻译

（我觉得题目中的翻译有点不对）

一只跳蚤在 $n \times m$ 的棋盘上跳跃，每次只能横着或纵着跳，而且跳的格数为定值 $s$。不能跳出棋盘外。

记 $d_{x, y}$ 为从格子 $(x, y)$ 开始跳，能跳到的格子个数。求有多少个格子 $(x,y)$，使得 $d_{x, y}$ 达到给定棋盘上的最大值。

## 思路

首先，我们要知道，如果从格子 $(x_1, y_1)$ 能跳到 $(x_2, y_2)$，那么 $d_{x_1, y_1} = d_{x_2, y_2}$，因为从 $(x_2, y_2)$ 能且仅能跳到从 $(x_1, y_1)$ 能跳到的格子。

那么，哪些格子满足要求呢？

放上我的手绘丑图：

![示意图](https://cdn.luogu.com.cn/upload/image_hosting/2gdar3pb.png)

图中 $n = 9$，$m = 8$，$s = 3$。

感性理解一下，我们可以发现，只有从左上角的绿色矩形中的格子出发（只能向右、向下跳），才能“延展”出最多的格子。

**看图，看图，看图！**

再仔细观察，可以发现 $d_{x, y}$ 的最大值为 $\lceil \frac{n}{s} \rceil \times \lceil \frac{m}{s} \rceil$，绿色矩形中的格子数为 $(n \% s) \times (m \% s)$。

需要注意的是，当 $n \% s = 0$ 或 $m \% s = 0$ 时，须将其换成 $s$。

**不懂的，看图！**

将 $d_{x, y}$ 的最大值与绿色矩形中的格子数相乘，就是答案。

如图中例子，答案便是 $\lceil \frac{9}{3} \rceil \times \lceil \frac{8}{3} \rceil \times 3 \times (8 \% 3) = 54$。

## 代码

代码还是挺短的，理解了就很容易打出来。

```cpp
#include <iostream>
#include <cstdio>

int main()
{
	long long n, m, s;
	scanf("%lld %lld %lld", &n, &m, &s);
	printf("%lld\n", ((n + s - 1) / s) * ((m + s - 1) / s) * ((n + s - 1) % s + 1) * ((m + s - 1) % s + 1));
	// 此处操作可能较骚
	// 对于整数a、b(a >= 0，b > 0)
	// a除以b的商向上取整是：(a + b - 1) / b
	// 取a除以b的余数，且要在a整除b时取到b，可以这样取：(a + b - 1) % b + 1
	// 具体原因不解释，都是利用整除的特性
	return 0;
}
```

---

## 作者：cz666 (赞：2)

## 吐槽

这只是一道简单的思维题但是~~它怎么会黑的呢？~~

思维难度也不高，适合**入门级选手**例如我来做。

## 思路

**（备注：下面的 $k$ 是题面里的 $s$ ，即跳跃距离）**

画几幅图来随意 $yy$ 几下就会发现下面的三个规律：

1. 最显而易见的如果 $k$ 大于 $n$ **和** $m$ （注意条件关系是**和**而不是或！此时无论哪里开始 $d(x,y)$ 的值都是 $1$ ）或者 $k$ 等于 $1$ （都能跳到），那么可以直接输出答案 $n*m$ 。

2. 点 $(x,y)$ 能跳到的点的 $d$ 值一定与 $d(x,y)$ 相等（跳跃互逆性）。

	所以如果点 $(x,y)$ 的 $d(x,y)$ 最大，那么就代表它所有能走到的点都能对答案有 $1$ 的贡献。

3. 点 $(1,1)$ 一定拥有最大的 $d(1,1)=((n-1)/k+1)*((m-1)/k+1)$ ，所以这题就转化成 $n*m$ 的区域里有多少个点的 $d(x,y)$ 等于 $d(1,1)$ 。

之后我们考虑求出以 $(x,y)$ 为跳跃开始的左上角，这样有多少个 $d(x,y)==d(1,1)$ 。

上面求出的 $(x,y)$ 的个数再去乘上 $d(1,1)$ 不就是题目所要求的起始位置个数了吗？

显然对于每一行可以有 $m\%k$ 个符合条件的点。

同理对于每一列，也可以有 $n\%k$ 个符合条件的点。

所以答案就是 $d(1,1)*(n\%k)*(m\%k)$ 。

即 $((n-1)/k+1)*((m-1)/k+1)*(n\%k)*(m\%k)$ 。

然后交上去发现顺利得到 $WA$ 的好成绩。

检查发现如果 $n\%k==0$ 或者 $m\%k==0$ 我们会清空答案，然而正确情况下应该是乘上一个 $k$ ！，那就再判一下 $!(n\%k)$ 和 $!(m\%k)$ 的情况即可，成功 $AC$ ！

~~无法相信水题的思路我能写这么长，果然我是菜鸡。~~

## 无注释AC代码

```cpp
/*
...(省略一张字符画)
这个***（人名和谐掉（隐私权））可以让你AK CSP-S 2019.
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define dd c=getchar()
inline int read(){int s=0,w=1;char c;while (dd,c>'9' || c<'0') if (c=='-') w=-1;while (c>='0' && c<='9') s=s*10+c-'0',dd;return s*w;}
inline void write(int x){if (x<0) putchar('-'),x=-x;if (x>=10) write(x/10);putchar(x%10|'0');}
inline void wln(int x){write(x);putchar(10);}
inline void wlk(int x){write(x);putchar(32);}
#undef dd
signed main(){
	int n=read(),m=read();
	int k=read(),ans=0;
	if (k>n&&k>m||k==1) return wln(n*m),0;
	ans=((n-1)/k+1)*((m-1)/k+1);
	if (n%k) ans*=(n%k);
	if (m%k) ans*=(m%k);
	if (!(n%k)) ans*=k;
	if (!(m%k)) ans*=k;
	return wln(ans),0;
}
```

最后祝大家 $CSP-S$ $2019$ $RP+=INF$ 。

---

## 作者：w33z8kqrqk8zzzx33 (赞：1)

蒟蒻只会$O(n+m)$解法

可以枚举对于所有初始行可以到达有多少个行，包含自己，然后统计有多少行可以到达一样多的行; 对于一个行$a$，它可以到达的行数为
$$f(a)=\lfloor\frac{n-a}{s}\rfloor-\lceil\frac{1-a}{s}\rceil+1$$

相似判断列；$n$改成$m$

只需要注意应为$\frac{1-a}{s}$是负数或者$0$，求`ceil`值是`(1-a)/s`，不是`(1-a+(s-1))/s`。

```c++
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair

using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m, s; cin >> n >> m >> s;
    int mxf = 0, mxfcnt = 0, mxg = 0, mxgcnt = 0;
    rep1(a, n) {
        int tr = (n-a)/s-(1-a)/s+1;
        if(mxf < tr) {
            mxfcnt = 1;
            mxf = tr;
        } else if(mxf == tr) mxfcnt++;
    }
    rep1(b, m) {
        int tr = (m-b)/s-(1-b)/s+1;
        if(mxg < tr) {
            mxgcnt = 1;
            mxg = tr;
        } else if(mxg == tr) mxgcnt++;
    }
    ll v = mxfcnt; v *= mxgcnt;
    cout << v << endl;
}
```

---


# The Clock

## 题目描述

Victor has a [24-hour clock](https://en.wikipedia.org/wiki/24-hour_clock) that shows the time in the format "HH:MM" (00 $ \le $ HH $ \le $ 23, 00 $ \le $ MM $ \le $ 59). He looks at the clock every $ x $ minutes, and the clock is currently showing time $ s $ .

How many different palindromes will Victor see in total after looking at the clock every $ x $ minutes, the first time being at time $ s $ ?

For example, if the clock starts out as 03:12 and Victor looks at the clock every $ 360 $ minutes (i.e. every $ 6 $ hours), then he will see the times 03:12, 09:12, 15:12, 21:12, 03:12, and the times will continue to repeat. Here the time 21:12 is the only palindrome he will ever see, so the answer is $ 1 $ .

A palindrome is a string that reads the same backward as forward. For example, the times 12:21, 05:50, 11:11 are palindromes but 13:13, 22:10, 02:22 are not.

## 说明/提示

The first test case is explained in the statement.

## 样例 #1

### 输入

```
6
03:12 360
00:00 1
13:22 2
15:15 10
11:11 1440
22:30 27```

### 输出

```
1
16
10
0
1
1```

# 题解

## 作者：Otue (赞：3)

## 思路
直接模拟。

疯狂对当前时间加上  $x$ ，如果说时间出现了循环（之间出现过这个时间，现在又来一次），那么整个时间轴就开始循环了，没必要继续算下去，直接停止，输出之前有多少个回文数即可。

## 代码
考试代码，由于赶时间，所以代码变量名不太可观。
```c++
#include <bits/stdc++.h>
using namespace std;

int t;
bool vis[10000];

bool check(char a, char b, char c, char d) {   //判断回文
	if (a == d && b == c) return 1;
	return 0;
}


int main() {
	cin >> t;
	while (t--) {
		int res = 0;
		memset(vis, 0, sizeof vis);
		char a, b, c, d, xx;
		int x;
		cin >> a >> b >> xx >> c >> d;  //特殊的读入方式
		cin >> x;
		int aa = a- '0', bb = b - '0', cc = c - '0', dd = d - '0';   //char转化为数字
		int tmp = (aa * 10 + bb) * 60 + cc * 10 + dd;   //把时间转化为分钟
        // tmp是指转化为分钟之后的时间
        //比如01:40(一个小时40分钟)转化为分钟就是100
		while (1) {
			tmp = (tmp + x) % 1440;  //疯狂加x
           
            // %1440是因为一天1440分钟，一个循环
			if (vis[tmp] == 1) break;  //如果说之前出现过该时间，退出
			else vis[tmp] = 1;
			int t1 = tmp / 60, t2 = tmp % 60;  //t1表示当前时间的“时”，t2表示“分”
			int aaa, bbb, ccc, ddd;
            //转化为aaa bbb : ccc ddd 的时间
			if (t1 < 10) aaa = 0, bbb = t1;    //有前导0情况 
			else aaa = t1 / 10, bbb = t1 % 10;
			if (t2 < 10) ccc = 0, ddd = t2;
			else ccc = t2 / 10, ddd = t2 % 10;
			if (check(aaa, bbb, ccc, ddd)) {   //如果是回文，统计
				res++;
			} 
		}
		cout << res << endl;
	}
	
}
```

---

## 作者：Digital_Sunrise (赞：2)

## 前言
[link](https://www.luogu.com.cn/problem/CF1692D)

不知为何，我觉得题解区里的代码都好奇怪。。。

## 题目内容

### 题目描述
从一个`24`小时制的时间点开始，每隔 $x$ 秒看一次手表，求到重新看到此时间点为止一共看到了多少个回文时间点。

回文时间点：诸如`13:31`,`25:52`等时间点。

### 输入
第一行一个数 $T$ 表示数据组数，

接下来 $T$ 行每行一个时间点 `xx:xx` 和时间间隔 $x$ ，使用空格分隔。

### 输出
对于每一组数据，输出一个 $ans$ 表示看到的回文时间点的数量。

## 题解

从输入的时间点开始枚举直到这个时间点再次出现。

将所有时间以秒的单位储存（比如`24:00`->`1440s`），然后只在比较回文的时候提取一下，这样写出来的代码非常简洁。

## 代码

```cpp

#include <bits/stdc++.h>
using namespace std;

int T;

int main()
{
	cin >> T;
	while(T--)
	{
		int tim1,tim2;
		char ch;
		cin >> tim1 >> ch >> tim2;
		int x,ans = 0;
		cin >> x;
		int i = tim1 * 60 + tim2;
		do
		{
			if(i / 60 % 10 == i % 60 / 10 and i / 60 / 10 == i % 60 % 10)
				++ans;
			i = i + x;
			i %= 1440;
		}while(i != tim1 * 60 + tim2);
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Yefori (赞：2)

相信前面几位大佬已经将题意和暴力枚举的方法解释的很清楚了。

本蒟蒻便来贡献一个更短的解法。

------------

首先，一天内的“回文时间”是有限的，只有16个。所以我们可以将这十六个时间转成分钟后保存起来，方便判断。

根据输入的 $h,m,x$ 来判断某个“回文时间” $p_i$ 是否满足条件，满足则答案$s$自增。

那么如何判断 $p_i$ 是否满足条件呢？明显，若 $p_i$ 满足条件：

$$
{\text{令} \hspace{1em} t = h*60+m}\\
{\text{则有} \hspace{1em} (nx+t) \bmod 1440 = p_i \hspace{1em} (n \in N^*)}\\
{\text{即} \hspace{1em}nx+t= p_i + m*1440 \hspace{1em} (n,m \in N^*)}\\
$$

若取 $x$,$y$ 为自变量，则

$$
{ax+t=1440y+p_i}\\
{1440y-ax=t-p_i}\\
$$

而一元二次方程 $ax+by=c$ 有解的条件是: $c \bmod gcd(a,b) = 0$ 。

所以若 $p_i$ 为条件 $h,m,x$ 下的“回文时间”，则
$$
{(h*60+m-p_i) \bmod gcd(1440,x) = 0}\\
$$

------------

AC代码如下：

```cpp
# include <bits/stdc++.h>

const int p[16] = {0, 70, 140, 210, 280, 350, 601, 671, 741, 811, 881, 951, 1202, 1272, 1342, 1412};

int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        int h, m, x, s = 0;
        scanf("%d:%d %d", &h, &m, &x);
        for (auto i: p) if (!((h * 60 + m - i) % (std::__gcd(1440, x)))) s++;
        printf("%d\n", s);
    }
    return 0;
}

```


---

## 作者：cyrxdzj (赞：2)

### 一、思路

显然，过了 $3600$ 次 $x$ 秒后，当前的时间就一定与原来输入的时间一致，形成循环。

因此，我们可以枚举每一个可能的时间，判断即可。

### 二、代码

```cpp
#include<cstdio>
using namespace std;
int t;
int sh,sm,x;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%2d:%2d\n",&sh,&sm);
		scanf("%d",&x);
		int nh=sh,nm=sm;
		int ans=0;
		for(int i=1;i<=3600;i++)//循环3600次
		{
			nm+=x;
			if(nm>=60)//分达到60，向时进位
			{
				nh+=nm/60;
				nm%=60;
			}
			if(nh>=24)//时达到24，取余
			{
				nh%=24;
			}
			//printf("%d %d\n",nh,nm);
			if(nh/10==nm%10&&nh%10==nm/10)//判断回文
			{
				ans++;
			}
			if(nh==sh&&nm==sm)//出现循环
			{
				break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：user470883 (赞：1)

## 题意：
给您一个格式为 `HH:MM` 的时间，每次增加 $x$ 分钟，在给出的时间点再次出现之前，一共出现了几次回文时间（可以理解为去掉 `:` 后是否是回文数）。

## 思路：
我们通过举例几次发现：

> 每经过 $1440$ 次所给的 $x$ 秒，就必定形成了循环（即再次出现题目所给您的时间）

那么一切都解决了。

我们直接模拟题意，每次分钟加上所给的 $x$ 然后除以 $60$ 的往前进，膜 $60$ 的自己留下。

时钟由于没有天数，直接膜 $24$ 然后剩下的留下。

然后判断回文，看算出的小时翻转后是否等于分钟即可。

最后不要忘记判断循环，这就要我们在开始的时候将输入进来的备份最后比较，相同之时，就循环一遍下来了，我们可以安心跳出然后输出答案。

---

## 作者：sgl654321 (赞：0)

### 题目大意
- 定义一种时刻为回文时刻，当且仅当这种时刻正着读和反着读一样，例如 ```12:21```。

- 给定一个时刻 ```HH:MM``` 和一个常数 $x$，每隔 $x$ 分钟看一下时刻，注：该钟表为二十四小时计时法。

- 问回到 ```HH:MM``` 之前，总共可以看到几个回文时刻？

### 解题思路
直接模拟即可。

- 操作 $1$：判断该时刻是否回文。

设该时刻为 $h$ 时 $m$ 分，直接对该时刻的 $h$ 进行一次倒转，将它的个位和十位进行交换，变为 $h'$。判断 $h'$ 与 $m$ 是否相等即可。若相等，则 $ans$ 自增 $1$。

- 操作 $2$：将该时刻加上 $x$ 分钟。

若开始的时间为 $h$ 时 $m$ 分，经过 $x$ 分钟后，结束时时间为 $H$ 时 $M$ 分，其中 $M=(m+x)\bmod60$，$H=(h+\lfloor\dfrac{m+x}{60}\rfloor)\bmod24$。

有这两个操作就可以轻松做出这一道题啦！

### 参考代码
注意本题时刻的输入方式，以及本题有多组数据。
```cpp
#include<bits/stdc++.h>
using namespace std;
bool p;
long long t,h,m,x,nowh,nowm,niubi,ans;
char ch;
int main(){
	cin>>t;
	while(t--){
		cin>>h>>ch>>m>>x;
		ans=0;
		p=0;
		nowh=h;nowm=m;
		while(1){
			if(nowh==h&&nowm==m&&p==1)break;
			if(nowh==h&&nowm==m&&p==0)p=1;
			niubi=nowh/10+nowh%10*10;
			if(niubi==nowm)ans++;
			nowm+=x;
			nowh+=nowm/60;
			nowm%=60;
			nowh%=24;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：OLE_OIer (赞：0)

## CF1692D The Clock

这道题是一道不错的模拟题。

题意：给你一个时间点，它每次增加一段时间，问你在这个时间点下一次出现时有多少个回文时间点。

我们可发现，无论怎样，时间点变了 $1440$ 次后一定会回到原样，所以直接暴力枚举即可。注意时间加法的正确性。

代码附上：
```cpp
//CF1692D The Clock
#include<bits/stdc++.h>
#include<windows.h>
#define int long long
#define elif else if
using namespace std;
struct tme{
	int a,b;
	tme operator+(const tme &x){//将时间往后推移一段。
		tme ans;ans.a=a+x.a,ans.b=b+x.b;
		if(ans.b>=60) ans.a+=ans.b/60,ans.b%=60;
		if(ans.a>=24) ans.a%=24;
		return ans;
	}
	bool pdm(){//判断是否是回文时间
		return a%10==b/10&&a/10==b%10;
	}
};
void func(){
	tme p,k,tmp;int ans=0;char c;k.a=0;
	cin>>p.a>>c>>p.b>>k.b;//这样的输入可以直接把中间的冒号给“吃”掉
	tmp=p;
	if(tmp.pdm()) ++ans;//判断第一个时间点是否为回文。
	while(true){
		tmp=tmp+k;//时间推移
		if(tmp.a==p.a&&tmp.b==p.b) break;//如果和原时间相同则跳出循环
		if(tmp.pdm()) ++ans;//判断回文
	}
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	int n;cin>>n;
	for(int i=1;i<=n;++i) func();
	return 0;
}
```
有问题可以在评论区问笔者，笔者会尽快回答的。

---

## 作者：Hooch (赞：0)

### 题目大意

现在有一个 $24$ 小时制的时钟，这个时钟每次会过去 $x$ 分钟。并且会告诉你开时钟的开始时间。

请求出这个时钟一共会出现的所有情况中，时钟时间是回文串的总数。

### 基本思路

我们可以直接写暴力，每次跳到时钟的下一次，直到重新跳到起点为止。然后可以证明暴力时间复杂度是 $O(1440)$ 的。

#### 证明

$O(1440)$ 复杂度就是一共会出现的 $O(60\times24)$ 种情况。

我们可以把每个情况的时钟和它的下一分钟的时钟连一条边，这样会成为一个环，然后每一次跳都是跳到下 $x$ 个了。

我们计算得出这时会跳 $\operatorname{lcm}(x, \text{环长})$ 遍。令 $y=$ 环长，那么会跳 $x\times y÷\gcd(x,y)$，因为每次跳 $x$ 个，所以会跳 $y\div \gcd(x,y)$ 次。又因为 $\gcd(x,y)\ge1$，所以复杂度是 $O(y)$，也就是 $O(1440)$。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define Next_Char getchar
template <typename T>
inline void read(T &x) {
	x = 0; char ch = Next_Char(); T f = 1;
	while (!isdigit(ch)) f -= (ch == '-') << 1, ch = Next_Char();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = Next_Char();
	x *= f;
}
template <typename T, typename ...L> inline void read(T &x, L &...y) {read(x), read(y...);}
int x, t, sx, sy;
inline bool check(int x, int y) {
    int a = x / 10, b = x % 10, c = y / 10, d = y % 10;
    return (a == d &&  c == b);
} //是否回到起点
inline void nxt(int &x, int &y, int ax, int ay) {
    x += ax, y += ay;
    if (y >= 60) y -= 60, ++x;
    if (x > 23) x -= 24;
} //时钟是 x:y 的下一个
main() {
    read(t); while (t--) {
        read(sx, sy, x);
        int ax = x / 60, ay = x % 60, ans = 0;
        int tx = sx, ty = sy; nxt(tx, ty, ax, ay);
        while (tx != sx || ty != sy) {
            ans += check(tx, ty);
            nxt(tx, ty, ax, ay);
        } ans += check(sx, sy);
        cout << ans << endl;
    }
}
```

---


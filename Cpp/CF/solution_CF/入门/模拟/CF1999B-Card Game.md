# Card Game

## 题目描述

Suneet 和 Slavic 正在玩一款纸牌游戏。游戏规则如下：

- 每张牌的整数点数在 $1$ 到 $10$ 之间。
- 每位玩家各自获得 $2$ 张面朝下的牌（玩家不知道自己拿到的牌）。
- 游戏为回合制，总共进行两回合。在每一回合中，两位玩家各自从自己未翻开的牌中随机选择一张并翻开。翻开的牌点数严格更大的玩家赢得该回合。如果点数相等，则本回合无人获胜。
- 如果某位玩家赢得的回合数严格多于对方，则该玩家赢得整局游戏。如果回合数相等，则无人获胜。

由于 Suneet 和 Slavic 并不是最好的朋友，你需要计算所有可能的游戏过程中，Suneet 获胜的方案数。

如需更好地理解题意，请参考提示部分。

## 说明/提示

以第一个测试用例为例，Slavic 拥有点数为 $2$ 和 $6$ 的牌，Suneet 拥有点数为 $3$ 和 $8$ 的牌。该局游戏共有 $4$ 种不同的进行方式：

- Suneet 翻开 $3$，Slavic 翻开 $2$。Suneet 赢得第一回合。然后 Suneet 翻开 $8$，Slavic 翻开 $6$。Suneet 也赢得第二回合。由于 Suneet 赢得了 $2$ 个回合，他赢得了整局游戏。
- Suneet 翻开 $3$，Slavic 翻开 $6$。Slavic 赢得第一回合。然后 Suneet 翻开 $8$，Slavic 翻开 $2$。Suneet 赢得第二回合。由于双方各赢一回合，无人获胜。
- Suneet 翻开 $8$，Slavic 翻开 $6$。Suneet 赢得第一回合。然后 Suneet 翻开 $3$，Slavic 翻开 $2$。Suneet 也赢得第二回合。由于 Suneet 赢得了 $2$ 个回合，他赢得了整局游戏。
- Suneet 翻开 $8$，Slavic 翻开 $2$。Suneet 赢得第一回合。然后 Suneet 翻开 $3$，Slavic 翻开 $6$。Slavic 赢得该回合。由于双方各赢一回合，无人获胜。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
3 8 2 6
1 1 1 1
10 10 2 2
1 1 10 10
3 8 7 2```

### 输出

```
2
0
4
0
2```

# 题解

## 作者：Program_A2 (赞：4)

## 思路

~~本蒟蒻太菜了555，只想到了暴力求解，dalao勿喷~~

挺简单的，只需列出所有能让 Sunnet 赢的可能结果，并输出 Sunnet 数量

## 代码


```
#include <bits/stdc++.h>
using namespace std;
int b[10001][5];
int x(int q,int w,int e,int r){
	int sum=0,c[5]={0,q,w,e,r},n=0,m=0; //数组方便记忆
	if(c[1]>c[3])n++;
	if(c[1]<c[3])m++;
	if(c[2]>c[4])n++;
	if(c[2]<c[4])m++;
	if(n>m)sum++;
	n=0,m=0;
    if(c[2]>c[3])n++;
	if(c[2]<c[3])m++;
	if(c[1]>c[4])n++;
	if(c[1]<c[4])m++;
	if(n>m)sum++;
	n=0,m=0;
    if(c[1]>c[4])n++;
	if(c[1]<c[4])m++;
	if(c[2]>c[3])n++;
	if(c[2]<c[3])m++;
	if(n>m)sum++;
	n=0,m=0;
    if(c[2]>c[4])n++;
	if(c[2]<c[4])m++;
	if(c[1]>c[3])n++;
	if(c[1]<c[3])m++;
	if(n>m)sum++;           //这里列出所有可能性，如果Sunnet的次数多，赢的次数+1
	n=0,m=0;
	return sum;         //返回赢的次数
}
int main(){
	int a;
	cin>>a;
	for(int i=1;i<=a;i++)for(int l=1;l<=4;l++)cin>>b[i][l];          //输入数据
	for(int i=1;i<=a;i++){
		cout<<x(b[i][1],b[i][2],b[i][3],b[i][4])<<endl;      //输出数据
	}
	return 0;
}
```

$$\huge{END}$$

---

## 作者：PineappleSummer (赞：4)

[CF1999B Card Game](https://www.luogu.com.cn/problem/CF1999B)

发现不考虑先后顺序，只有两种出牌情况。

第一种：$a_1$ 对 $b_1$，$a_2$ 对 $b_2$。

第二种：$a_1$ 对 $b_2$，$a_2$ 对 $b_1$。

分情况讨论即可。题目要考虑先后顺序，所以答案要乘二。

单组数据时间复杂度 $\mathcal O(1)$。

```cpp
void solve () {
	cin >> a1 >> a2 >> b1 >> b2;
	int cnt = 0;
	if ((a1 > b1 && a2 >= b2) || (a1 >= b1 && a2 > b2)) cnt ++;
	if ((a1 > b2 && a2 >= b1) || (a1 >= b2 && a2 > b1)) cnt ++;
	cout << cnt * 2 << '\n';
}
```

---

## 作者：qifan_maker (赞：3)

两层循环枚举所有翻牌情况，计算 Suneet 和 Slavic 赢得的回合数，若 Suneet 赢得的回合数比 Slavic 多，则答案加一。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 998244353;
const int MAXN = 200100,hsb=1045141919;
const ll Inf = 1000000000000000000ll;
#define PI pair<ll,ll>
#define PII pair<ll,pair<ll,ll>>
int a[5];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int Tcs=1;
    cin >> Tcs;
    while (Tcs--){
        cin >> a[0] >> a[1] >> a[2] >> a[3];
        int ans=0;
        for (int i=0;i<=1;i++){
            for (int j=0;j<=1;j++){
                int x=0,y=0;
                if (a[i]>a[j+2]) x++;
                if (a[i^1]>a[j^1+2]) x++;
                if (a[i]<a[j+2]) y++;
                if (a[i^1]<a[j^1+2]) y++;
                if (x>y) ans++;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：WsW_ (赞：3)

很坑很坑。

---
## 思路
枚举并判断各种对局双方赢的回合。  


如果 Suneet 赢的回合数**大于** Slavic 赢的回合数，就说明这种对局 Suneet 能赢得游戏。  

那么有两种情况：
- $a_1$ 对 $b_1$；$a_2$ 对 $b_2$。
- $a_2$ 对 $b_1$；$a_1$ 对 $b_2$。

但是将第一回合和第二回合的对局交换一下，又是一种**新对局**。显然以上两种对局都有一种和自身**输赢情况相同**的**新对局**，所以最终答案要 $\times 2$。  

**注意：** 当对战的两张牌数字相等时，没有人赢得这个回合。但是，如果 Suneet 一赢一平，最后还是他赢得游戏。  

---
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;

void work(){
	int a[2],b[2];
	cin>>a[0]>>a[1]>>b[0]>>b[1];
	int cnt[2]={0,0},ans=0;
	for(int i=0;i<2;i++){
		cnt[0]=cnt[1]=0;
		for(int j=0;j<2;j++){
			cnt[0]+=(a[j^i]>b[j]);
			cnt[1]+=(b[j]>a[j^i]);
		}
		ans+=(cnt[0]>cnt[1]);
	}
	cout<<ans*2<<'\n';
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		work();
	}
	return 0;
}
```

---

## 作者：xxxalq (赞：2)

[洛谷链接](https://www.luogu.com.cn/problem/CF1999B) & [CF链接](http://codeforces.com/problemset/problem/1999/B)

# 思路

考虑到第一局只会有 $4$ 种情况，$a1,b1$，$a1,b2$，$a2,b1$，$a2,b2$，所以可以判断这 $4$ 种情况，因为第一局确定了，第二局也就确定了。

注意到是严格大于才算胜利，所以必须要赢一局且另一局不能输，也就是一局大于，另一局大于等于，注意可能第一局赢，也可能第二局赢。

# 代码


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int read(){
	int x=0;
	bool flag=false;
	char ch=getchar();
	while(ch<48||ch>57){
		if(ch==45){
			flag=true;
		}
		ch=getchar();
	}
	while(ch>=48&&ch<=57){
		x=(x<<3)+(x<<1)+(ch-48);
		ch=getchar();
	}
	return flag?-x:x;
}
int T,a1,a2,b1,b2;
void solve(){
	int ans=0;
	if((a1>b1&&a2>=b2)||(a1>=b1&&a2>b2)){
		ans+=1;
	}
	if((a1>b2&&a2>=b1)||(a1>=b2&&a2>b1)){
		ans+=1.0;
	}
	if((a2>b1&&a1>=b2)||(a2>=b1&&a1>b2)){
		ans+=1;
	}
	if((a2>b2&&a1>=b1)||(a2>=b2&&a1>b1)){
		ans+=1;
	}
	cout<<ans<<"\n";
	return;
}
int main(){
	T=read();
	while(T--){
		a1=read(),a2=read(),b1=read(),b2=read();
		solve();
	}
	return 0;
}

```

---

## 作者：block_in_mc (赞：1)

## 题目大意

Suneet 和 Slavic 在玩一个游戏，每人有两张牌，上面写着 $1$ 至 $10$ 的数字。对于每一回合，两个人各出一张牌，点数较大的获胜，若点数相等，则无人获胜。两个回合中，获胜数更多的人赢得游戏的胜利。

给定 Suneet 和 Slavic 的手牌，求有几种出牌方案使得 Suneet 获胜。

## 解题思路

直接枚举 Suneet 和 Slavic 两回合各自出的牌 $a,b$ 和 $a',b'$，若满足以下两种情况的一种，则 Suneet 获胜：

* $a\ge a'$ 且 $b>b'$；
* $a>a'$ 且 $b\ge b'$。

需要注意的是，第一回合两人出 $a,a'$，第二回合两人出 $b,b'$ 与第一回合两人出 $b,b'$，第二回合两人出 $a,a'$ 是两种不同的方案，但两者的判断条件相同，只需判断一次，将答案增加 $2$。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, a, b, c, d;
int main() {
    cin >> t;
    while(t--) {
        cin >> a >> b >> c >> d;
        int ans = 0;
        if((a > c && b >= d) || (a >= c && b > d)) ans+=2;
        if((a > d && b >= c) || (a >= d && b > c)) ans+=2;
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：Archy_ (赞：1)

## 题目翻译
[传送门](https://www.luogu.com.cn/problem/CF1999B)

给出 $4$ 个数字，每回合 A 从前两个数字选一个，B 从后两个数字选一个，不能重复选，进行比较，大于则胜利，相等则平局。二回合后若 A 的胜利回合数大于 B，称作 A 赢得比赛。求 A 赢得比赛有几种可能。
## 题目思路
分类讨论，A 赢得比赛有三种情况。
1. 回合一 A 胜利，回合二 A 胜利。
2. 回合一平局，回合二 A 胜利。
3. 回合一 A 胜利，回合二平局。

其次，若 A 通过一种方式赢得了比赛，那么一定存在相反的操作使得 A 赢得比赛。
## CODE
```cpp
#include <iostream>
using namespace std;
int main() {
	cin.tie(0) -> ios :: sync_with_stdio(0);
	int q; cin >> q;
	while(q--) {
		int a1, a2, b1, b2, ans = 0; 
		cin >> a1 >> a2 >> b1 >> b2;
		if(a1 >= b1 && a2 > b2 || a1 > b1 && a2 >= b2) ans+=2;	
		if(a1 >= b2 && a2 > b1 || a1 > b2 && a2 >= b1) ans+=2;
		cout << ans << "\n";
	}
	return 0;
} 
```
这似乎是最短的码量了。

---

## 作者：So_noSlack (赞：1)

## 题目简述

有 $T$ 组数据，每组数据分别给出两个人的两张牌的点数。

求在所有可能的出牌方式中（一张牌只能出一次），$\text{Suneet}$ 获胜的方式数。

注意：对于每次出牌，当且仅当点数大于对方时获胜，若相同则平局，两人均不得分。在两轮出牌中，得分大于对方的人获胜，若相同则无人获胜。

## 思路

那么思路就很明确了，我们可以直接枚举所有情况。

这里我们可以用 $a_0, a_1, b_0, b_1$ 存下两个人的两张牌，接着枚举两个人第一次出的牌，若第一次两个人出 $a_i, b_j$，那么第二次只能出 $a_{!i}, b_{!j}$，这里的 $!$ 为非运算符。

那么 $\text{Suneet}$ 获胜的条件就是，第一局平局或获胜且第二局平局或获胜，需要注意的是，不能两局都平局。

代码如下：


```cpp
#include<iostream>
using namespace std;

long long read() {
	long long x = 0, f = 1; char ch = getchar();
	while(ch < 48 || ch > 57) { if(ch == 45) f = -1; ch = getchar(); }
	while(ch >= 48 && ch <= 57) { x = (x << 3) + (x << 1) + (ch - 48); ch = getchar(); }
	return x * f;
}

long long T, a[2], b[2];

int main() {
	T = read();
	while(T --) {
		long long ans = 0;
		a[0] = read(); a[1] = read(); 
		b[0] = read(); b[1] = read();
		for(int i = 0; i <= 1; i ++) for(int j = 0; j <= 1; j ++) 
			if((a[i] > b[j] && a[!i] >= b[!j]) || (a[i] >= b[j] && a[!i] > b[!j])) ans ++;
		cout << ans << "\n";
	}
	return 0;
}
```

[$\text{Submission}$](https://codeforces.com/contest/1999/submission/274802094)

---

## 作者：GreenMelon (赞：1)

## 翻译

Suneet 有两个卡片 $a_1$，$a_2$，Slavic 有两个卡片 $b_1$，$b_2$，游戏会进行两个回合，每个回合每个人拿出一张卡片，谁的卡片上的数大谁将会赢这一轮比赛。

请输出 Suneet 能获胜的方案总数。

## 分析

四张卡片会有相同的情况，所以不能单单比较大小，需在比较的同时再判断两个数字是否相等。而且因为交换顺序后也是一种方案，所以只需判断两种方案，最后再乘上 $2$ 即可。时间复杂度为 $O(1)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int a1, a2, b1, b2;
		cin>>a1>>a2>>b1>>b2;
		int k=0;
		if(a1==a2 && a2==b1 && b1==b2){
			cout<<0<<endl;
			continue;
		}
		if(a1>=b1 && a2>=b2 && (a1!=b1 || a2!=b2)) k++;
		if(a1>=b2 && a2>=b1 && (a1!=b2 || a2!=b1)) k++;
		cout<<k*2<<endl;
	}
} 
```

---

## 作者：__O__o__ (赞：1)

## 前言
世纪笑话：B 的通过率比 D 还低。
## 思路简述
枚举第一、二局可能抓到的牌和 Suneet 可能赢的情况。又因为这种胜利情况倒转过来也能胜利，所以每种情况要 $+2$。
## Code
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int a1,a2,b1,b2,ans=0;
        cin>>a1>>a2>>b1>>b2;
        if (a1>b1)
        {
            if(a2>=b2)
                ans+=2;
        }
        if(a1==b1)
        {
            if(a2>b2)
            {
                ans+=2;
            }
        }
        if(a1>b2)
        {
            if(a2>=b1)
                ans+=2;
        }
        if(a1==b2)
        {
            if (a2>b1)
            {
                ans+=2;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：InfiniteRobin (赞：1)

### 简要题意 

---
每人有 $2$ 张牌，每个回合两人随机出一张自己的牌，点数大的人积一分，平局则不计分，两回合结束后积分多的人获胜。

在所有可能的出牌情况中，求第一个人获胜的局数。

---
### 分析
---
这里要注意的是，获胜的情况有两种：分别是 $1:0$ 和 $2:0$，需要分类讨论。此外，将第一局和第二局调转顺序也算作两种不同的局面。 

设第一个人的牌是 $a$ 和 $b$，第二个人的牌是 $c$ 和 $d$。若：

- $a>c$ 且 $b>d$，答案数量加 $2$。
- $a=c$ 且 $b>d$ 或 $a>c$ 且 $b=d$，答案数量加 $2$。
- $a>d$ 且 $b>c$，答案数量加 $2$。
- $a=d$ 且 $b>c$ 或 $a=d$ 且 $b>c$，答案数量加 $2$。

---
### Code

---
代码很好写。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        int cnt=0;
        if(a>d&&b>c){ //2：0的一种情况
            cnt+=2; //+2 是因为调转第一局和第二局的顺序被认为是两种答案
       }
        else if((a==d&&b>c) || (a>d&&b==c)){ //1：0的一种情况
            cnt+=2;
        }
        if(a>c&&b>d){//2：0的另一种情况
            cnt+=2;
        }
        else if((a==c&&b>d) || (a>c&&b==d)){//1：0的另一种情况
            cnt+=2;
        }
        
        cout<<cnt<<endl;
    }
    
    
}
```

---

## 作者：Pink_Cut_Tree (赞：1)

# CF1999B Card Game 

[Luogu Link](https://www.luogu.com.cn/problem/CF1999B)|[CF Link](https://codeforces.com/contest/1999/problem/B)|[My AC submission](https://codeforces.com/contest/1999/submission/274867795)。

好坑的题，WA 了三发。

### 解析

其实只有两种情况，即 $a_1$ PK $b_1$，$a_2$ PK $b_2$。或是 $a_1$ PK $b_2$，$a_2$ PK $b_1$。显然的，对于每一局 PK，数字大的得 $1$ 分，一样的得 $0$ 分，比对方小的得 $-1$ 分，最后判断分数是否大于 $0$ 即可，若大于 $0$，答案 $n$ 自增 $2$。为什么是 $2$ 而不是 $1$ 呢？因为两组卡谁先抽出是不确定的，所以要乘以局数 $2$。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int a1,a2,b1,b2,ans;
int my;
int point(int a,int b){
	if(a>b){
		return 1;
	}
	if(a==b){
		return 0;
	}
return -1;
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>T;
	while(T--){
		ans=0;
		cin>>a1>>a2>>b1>>b2;
		my=point(a1,b1)+point(a2,b2);
		if(my>0){
			ans+=2;
		}
		my=point(a1,b2)+point(a2,b1);
		if(my>0){
			ans+=2;
		}
		cout<<ans<<"\n";
	}
return 0;
}
```

---

## 作者：ka_da_Duck (赞：0)

[Card Game](https://www.luogu.com.cn/problem/CF1999B)
-

交了很多发，最后才发现正解。两局中我方获得两胜或者一胜一平都是可以赢的。最后答案乘 $2$ 即可，因为我方先翻 $a$ 或 $b$ 都是一样的结果。

```cpp
#include <bits/stdc++.h>
#define int long long
 
using namespace std;
const int maxn = 2e5 + 10;
 
void solve() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	int ans = 0;
	if (a > c && b >= d) ans++;
	if (a == c && b > d) ans++;
	if (a > d && b >= c) ans++;
	if (a == d && b > c) ans++;
	cout << ans * 2 << '\n';
}
 
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	//t = 1;
	while (t--) solve();
}
```

---

## 作者：wangzc2012 (赞：0)

# F1999B Card Game
## 题意概括
甲和乙玩纸牌游戏。游戏规则如下：每位玩家有两张牌，在每个回合中，双方抽取一张未翻开的牌，翻开的牌中数字更大的一方胜出本轮，如果数字相等，则无人获胜。现给出甲和乙的牌，求甲在多少种情况下胜出的轮数比乙多。
## 思路分析
本题可以直接使用暴力枚举通过，即直接将所有情况都判断一遍，最后记录答案。  
但是这样写出来的代码一点也不简洁，所以我们先分析甲的获胜条件，然后对每一个条件进行分级，最后判断即可。（没听懂也没事，看看代码就会啦）
## AC Code
两种方法的代码都在这里了。

首先是最简单粗暴的枚举代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a1,a2,b1,b2;
int main(){
	cin>>t;
	while (t--){
		cin>>a1>>a2>>b1>>b2;
		int ans=0;
		if (a1>b1 and a2>b2) ans+=2;
		if (a1>b2 and a2>b1) ans+=2;
		if (a1==b1 and a2>b2) ans+=2;
		if (a1==b2 and a2>b1) ans+=2;
		if (a2==b1 and a1>b2) ans+=2;
		if (a2==b2 and a1>b1) ans+=2; 
		cout<<ans<<'\n';
	}
	return 0;
}
```

然后是简洁一点的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a1,a2,b1,b2;
int check(int x,int y){
    if (x>y) return 1;
    if (x==y) return 0;
    if (x<y) return -1;
}
int main(){
	cin>>t;
	while (t--){
		cin>>a1>>a2>>b1>>b2;
		int ans=0;
		if (check(a1,b1)+check(a2,b2)>0) ans+=2;
		if (check(a1,b2)+check(a2,b1)>0) ans+=2;
		cout<<ans<<'\n';
	}
	return 0;
}

```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
枚举四种可能的情况，分别统计 Suneet 和 Slavic 的获胜次数，如果 Suneet 的获胜次数严格大于 Slavic 的获胜次数，那么答案 $+1$，最后输出答案。

本题多测。
### 代码
```cpp
#include<iostream>
void solve(int T){
	if(T==0)return;
	int a,b,c,d;
	std::cin>>a>>b>>c>>d;
	int cnt=0,ans=0,cnt1=0;

	if(a>c||b>d)cnt++;
	if(a<c||b<d)cnt1++;
	if(cnt>cnt1)ans++;
	cnt=0,cnt1=0;

	if(a>d||b>c)cnt++;
	if(a<d||b<c)cnt1++;
	if(cnt>cnt1)ans++;
	cnt=0,cnt1=0;

	if(b>c||a>d)cnt++;
	if(b<c||a<d)cnt1++;
	if(cnt>cnt1)ans++;
	cnt=0,cnt1=0;

	if(b>d||a>c)cnt++;
	if(a<c||b<d)cnt1++;
	if(cnt>cnt1)ans++;

	std::cout<<ans<<"\n";
	solve(T-1);
}
signed main(){
	int T;
	std::cin>>T;
	solve(T);
}
```

---

## 作者：liuli688 (赞：0)

### 题意
A 和 B 在玩纸牌。规则如下：
- 纸牌上的点数在 $1 \sim 10$ 之间。
- 每人获得 $2$ 张背面朝上的纸牌。
- 游戏进行 $2$ 回合，每回合两人分别翻开自己的任意一张纸牌，点数较大者积 $1$ 分，另一人不积分。若点数相同，双方均不积分。
- 两回合结束，积分较大者胜。

A 想让你帮他算一算，给定他的 $2$ 张纸牌的点数和 B 的 $2$ 张纸牌的点数，在所有可能的游戏中，他获胜的游戏有多少局？
### 思路
由于可能的游戏只有 $4$ 种，考虑枚举每个人翻开的牌是哪一张。

之后，比较两次翻开两张牌的大小并积分，即可算出一局游戏的输赢。

将四种游戏全部计算一遍即可。
### 代码

```cpp
#include <bits/stdc++.h>

int T, a1, a2, b1, b2;

//计算 A 第一张牌为 p1, 第二张牌为 p2, B 第一张牌为 q1, 第一张牌为 q2 的积分
short calc(int p1, int p2, int q1, int q2)
{
    short res = 0;
    if (p1 > q1)
        ++res;
    if (p1 < q1)
        --res;
    if (p2 > q2)
        ++res;
    if (p2 < q2)
        --res;
    return std::max(res, short(0));
}

signed main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d", &a1, &a2, &b1, &b2);
        //枚举四种游戏情况
        //因为 calc 函数计算的是积分不是输赢，所以需要转化为 bool
        printf("%d\n", bool(calc(a1, a2, b1, b2)) + bool(calc(a1, a2, b2, b1)) + bool(calc(a2, a1, b1, b2)) + bool(calc(a2, a1, b2, b1)));
    }
    return 0;
}
```

---

## 作者：tzzl3035 (赞：0)

# CF1999B 题解
### 题目大意
有 $t$ 组数据，每组给出四个正整数 $a_1$，$a_2$，$b_1$，$b_2$。前两张是甲的牌，后两张是乙的牌。游戏共两轮，每轮双方各翻起一张还未翻起的牌，若谁的牌更大，则谁胜出此轮，若相等，则无人胜出。问甲在几种情况下胜出的轮数比乙多。
### 大致思路
赛时有许多人错在第二个数据点（包括我），原因是只判断了甲两张牌都更大的情况，没有判断其中一张相等的情况。所以，我们要考虑两张牌都更大的情况，还要考虑其中一张相等另一张更大的情况。
### 核心代码
```cpp
void solve() {
  // 输入
  int a1, a2, b1, b2;
  std::cin >> a1 >> a2 >> b1 >> b2;
  int ans = 0;
  // 统计胜利局数用的辅助函数
  auto comp = [&](int x, int y) -> int {
    if(x > y) return 1;
    if(x == y) return 0;
    if(x < y) return -1;
  };
  // 统计胜利局数
  if(comp(a1, b1) + comp(a2, b2) > 0) ans += 2;
  if(comp(a1, b2) + comp(a2, b1) > 0) ans += 2;
  // 输出
  std::cout << ans << '\n';
}

```
### [RESULT](https://codeforces.com/contest/1999/submission/274908926)

---

## 作者：Heldivis (赞：0)

## CF1999B Card Game

题目认为，只要第一次两人出牌的牌（而非牌面大小）不同，那么就认为是两种方案。

考虑枚举两人第一次出牌的情况，可以知道第二次的情况。牌面数字严格大于对手才能得分，得分严格大于对手才能获胜。那么获胜情况必须是**一次大于，一次大于或等于**。

代码：

```cpp
void Main() {
  cnt = 0;
  a[0] = read(), a[1] = read(), b[0] = read(), b[1] = read();
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j)
      if ((a[i] > b[j] && a[1 - i] >= b[1 - j]) ||
          (a[i] >= b[j] && a[1 - i] > b[1 - j]))
        ++cnt;
  printf("%d\n", cnt);
}
```

---

## 作者：ToastBread (赞：0)

## 题目翻译
现在有两个人玩游戏。玩家 1 的手牌为 $a_1,a_2$，玩家 2 的手牌为 $b_1,b_2$。**保证手牌的数字 $\leq 10$**。

游戏的玩法是这样的：
- 两人先翻开一张自己的牌，比较大小，较大者积一分，平局不计分。
- 再翻开另外一张牌，比较大小，较大者积一分，平局不计分。
- 最后，谁的分多谁就赢，**平局不算任何人赢**。

请你求出，**在所有可能的方式中，玩家 1 有几种方式会赢**？

## 题目思路
显然是一道**模拟**题。

先枚举出玩家 1 第一轮出的牌，然后枚举玩家 2 第一轮出的牌，就可以确定一种情况。

对于每种情况，模拟求出玩家 1 是否获胜即可。

具体的实现可以参考我的代码。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[3],b[3],ans;
int main()
{
	cin>>t;
	while(t--)//多组数据 
	{
		cin>>a[1]>>a[2]>>b[1]>>b[2];
		//使用了数组的方式，方便枚举 
		ans=0;//重置答案 
		for(int i1 = 1; i1 <= 2; i1++)//玩家 1 第一轮出的牌的编号
		{
			int i2=3-i1;//玩家 1 第二轮出的牌的编号 
			for(int j1 = 1; j1 <= 2; j1++)//同理 
			{
				int j2=3-j1,now=0;//now 玩家 1 目前领先的积分 
				if(a[i1]>b[j1]) now++;//玩家 1 第一轮赢了 
				if(a[i2]>b[j2]) now++;//玩家 1 第二轮赢了
				if(a[i1]<b[j1]) now--;//玩家 1 第一轮输了
				if(a[i2]<b[j2]) now--;//玩家 1 第二轮输了
				if(now>0) ans++;//玩家 1 在这种情况下赢了 
			}
		}
		cout<<ans<<endl;//输出答案总数 
	}
	return 0; 
 } 
```

---

## 作者：ICU152_lowa_IS8 (赞：0)

这题只要给题目看清了会发现就是诈骗。

实际上只有两种可能：

- $a_1$ 对 $b_1$。

- $a_1$ 对 $b_2$。

值得注意的是，根据样例解释，$a_1$ 对 $b_1$ 放在第一次和第二次是两种情况，这两种情况的胜负结果一定是一样的。

故上述两种情况判断，一次将答案加 $2$ 即可。

代码：


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int t;
	cin>>t;
	while(t--){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		int ans=0,ccnt=0,cccnt=0;
		if(a>c)ccnt++;
		if(b>d)ccnt++;
		if(c>a)cccnt++;
		if(d>b)cccnt++;
		if(ccnt>cccnt)ans+=2;
		ccnt=0;
		cccnt=0;
		if(a>d)ccnt++;
		if(b>c)ccnt++;
		if(d>a)cccnt++;
		if(c>b)cccnt++;
		if(ccnt>cccnt)ans+=2;
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：GeXiaoWei (赞：0)

# CF1999B Card Game
## 解析

通过题目可知，想要胜利，只能赢一局、平一局或连赢两局，所以只需要考虑以上情况即可。

注意：每种胜利方案要按两倍计算，因为可以改变出牌顺序。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b,c,d,w;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d",&a,&b,&c,&d);w=0;
		if(a>c&&b>d) w+=2;//连赢两局
		if(a>d&&b>c) w+=2;//连赢两局
		if(b==d&&a>c) w+=2;//一赢一平
		if(a==c&&b>d) w+=2;//一赢一平
		if(b==c&&a>d) w+=2;//一赢一平
		if(a==d&&b>c) w+=2;//一赢一平
		printf("%d\n",w);
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

很简单，直接枚举四种情况，看 Suneet 赢不赢就行了。单词查询复杂度 $O(1)$，常数 $4$。

代码如下：

```cpp
#include<iostream>
using namespace std;
short t,a[2],b[2],ans,tmp;
inline bool judge(){
	return ((a[0]>b[0])+(a[1]>b[1]))>((a[0]<b[0])+(a[1]<b[1]));
}
int main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>a[0]>>a[1]>>b[0]>>b[1];
		ans=judge();
		swap(a[0],a[1]); ans+=judge();
		swap(b[0],b[1]); ans+=judge();
		swap(a[0],a[1]); ans+=judge();
		putchar(ans^48); putchar('\n');
	}
	return 0;
} 
```

---

## 作者：wmrqwq (赞：0)

需要我教你怎么 AK div.4 吗？

# 题目链接

[CF1999B](https://www.luogu.com.cn/problem/CF1999B)

# 解题思路

发现每个人都有两张牌。

因此我们发现，我们匹配完了一对牌，那么我们也就可以确定另一对需要匹配的牌。

直接暴力枚举第一对需要匹配的牌然后根据题意统计答案即可。

# 参考代码

```cpp
/*
Tips:

你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
打 cf 不要用 umap！！！

记住，rating 是身外之物。

该冲正解时冲正解！

Problem:

算法：

思路：

*/
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
ll pw(ll x,ll y,ll mod){if(x==0)return 0;ll an=1,tmp=x;while(y){if(y&1)an=(an*tmp)%mod;tmp=(tmp*tmp)%mod;y>>=1;}return an;}
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
ll _t_;
void _clear(){}
ll a[5],b[5];
void solve()
{
	_clear();
	forl(i,1,2)
		cin>>a[i];
	forl(i,1,2)
		cin>>b[i];
	ll ans=0;
	forl(i,1,2)
		forl(j,1,2)
		{
			ll sum=0,sum2=0;
			sum+=a[i]>b[j];
			sum+=a[3^i]>b[3^j];
			sum2+=a[i]<b[j];
			sum2+=a[3^i]<b[3^j];
			if(sum>sum2)
				ans++;
		}
	cout<<ans<<endl;
}
int main()
{
	IOS;
	_t_=1;
 	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---


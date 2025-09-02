# The Meaningless Game

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF833A/28a3b44282ccdbacfa3b5998d49bb6aaf4e51076.png)Slastyona and her loyal dog Pushok are playing a meaningless game that is indeed very interesting.

The game consists of multiple rounds. Its rules are very simple: in each round, a natural number $ k $ is chosen. Then, the one who says (or barks) it faster than the other wins the round. After that, the winner's score is multiplied by $ k^{2} $ , and the loser's score is multiplied by $ k $ . In the beginning of the game, both Slastyona and Pushok have scores equal to one.

Unfortunately, Slastyona had lost her notepad where the history of all $ n $ games was recorded. She managed to recall the final results for each games, though, but all of her memories of them are vague. Help Slastyona verify their correctness, or, to put it another way, for each given pair of scores determine whether it was possible for a game to finish with such result or not.

## 说明/提示

First game might have been consisted of one round, in which the number $ 2 $ would have been chosen and Pushok would have won.

The second game needs exactly two rounds to finish with such result: in the first one, Slastyona would have said the number $ 5 $ , and in the second one, Pushok would have barked the number $ 3 $ .

## 样例 #1

### 输入

```
6
2 4
75 45
8 8
16 16
247 994
1000000000 1000000
```

### 输出

```
Yes
Yes
Yes
No
No
Yes
```

# 题解

## 作者：Cutler (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF833A)

简化题意：

两个数初始为一，每次其中一个乘 $k^2$，一个乘 $k$，给出最后的结果，判断是否有可能出现这种情况。

看这个题目有点数论的味道，显然最后的结果一定是 $k$ 的倍数，并且

$$
a\times b=k^3
$$

但枚举 $k$ 肯定会超时的，所以我们把 $a \times b$ 开三次方，判断是否为整数，且同时被 $a,b$ 整除。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

int Q, a, b;

signed main(){
	scanf("%lld", & Q);
	
	while(Q --){
		scanf("%lld%lld", & a,& b);
		int t = round(pow(a * b,1.0 / 3));
		if(t * t * t == a * b && a % t == 0 && b % t == 0) puts("Yes");
		else puts("No");
	}
	
	return 0;
}
```

优雅结束。

---

## 作者：hzoi_liuchang (赞：2)

## 分析
**一句话题意：现在两个人做游戏，每个人刚开始都是数字1，谁赢了就能乘以k^2，输的乘以k，现在给你最终这两个人的得分，让你判断是否有这个可能，有可能的话Yes，否则No。**

我们假设游戏进行了 i 轮，每次选择的数分别是n$_1$、n$_2$、n$_3$……n$_i$

那么第一次，必定有一个人乘n12,另一个人乘n1，同样地，第二次，必定有一个人$\times$n$_2$$^2$，另一个人$\times$n$_2$

我们设A为第一个人最终的得分，B为第二个人最终的得分，那么很显然,如果结果正确的话，必定有A$\times$B=n$_1$$^3$$\times$n$_2$$^3$$\times$n$_3$$^3$$\times$……$\times$n$_i$$^3$

所以我们要判断对A$\times$B开三次根号后的数是不是整数

同时，一个人的最小得分必定为n1$\times$n2$\times$n3$\times$……$\times$ni，最大得分必定为n1$^2$$\times$n2$^2$$\times$n3$^2$$\times$……$\times$ni$^2$

所以我们还要判断A和B能否被它们的乘积开三次根号的结果整除

如果上述条件都满足，就输出Yes，否则输出No

## 代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<queue>
#include<cmath>
using namespace std;
typedef long long ll;
int main(){
    ll t;
    scanf("%lld",&t);
    while(t--){
        ll a,b;
        scanf("%lld%lld",&a,&b);
        ll tot=a*b;
        ll js=round(pow(1.0*tot,1.0/3));
        //对A*B开三次根号取整  
        if(js*js*js==tot && a%js==0 && b%js==0) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
```


---

## 作者：PigJokerYellow (赞：1)

## 前言

- `cbrt`：求立方根。

## 题意

- 选择一个数 $ k $，俩人玩游戏，赢的人的分 $ \times k^2 $，输的人 $ \times k $，给出最后的结果，判断是否合法。

## 分析

- 我们会发现在两个人中，他们一个分 $ \times k^2 $，另一个的 $ \times k $，则每次两个人总共乘了 $ k^3 $ 分，则最后他们的总分数的成绩绝对开得尽三次方，对吧？

- 所以说我们只需要把他们的最后总分乘起来，则这个数始终是一个数的三次方，把他开三次方，判断是否为整数，即可判断是否合法。

## Tips
- 本题 `cin` 可能会 T 掉，所以我们就用 `cin` 吧。


## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,a,b,c;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//关闭同步流，加速 
	cin>>n;
	while(n--){
		cin>>a>>b;
		c=round(cbrt(a*b));
		//求a与b的立方根 
		if(c*c*c==a*b&&a%c==0&&b%c==0) cout<<"Yes\n";
		//判断整数c是否为ab的立方根，得出是否合法 
		else cout<<"No\n";
	}
    return 0;
}

```


---

## 作者：Su_Zipei (赞：1)

## 分析
这道题有一点点数学的感觉（其实我只是看到了平方），来分析一下，两个人的初始值都一样，只知道最后的结果，中间的过程我们是不知道的，但可以很明显的看出，只要我的操作合法，两个数的乘积就一共扩大了$k^3$倍，所以关键的就是确定这个$k$是啥。
直接枚举是显然不可以的，需要找一些共性的东西，于是就想到了分解质因数。只要我分解出来的每个质因数，第一个数的个数和第二个数的个数加起来一定是3的倍数。因为$k$可以分解为$p_1,p_2……p_n$，$k^2$就是把每个质因数都平方，所以一次操作就相当于多了3，说的可能绕了一些，反正就是这样。
这么写的正确性肯定是毋庸置疑的，但时间消耗会很大，尤其是涉及到取%的操作很多，于是就TLE了。
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e6+10;
int prime[N];
bool isp[N];
void init(){
    memset(isp,1,sizeof(isp));
    for(int i=2;i<=N-5;i++){
        if(isp[i])
            prime[++prime[0]]=i;
        for(int j=1;j<=prime[0]&&i*prime[j]<=N-5;j++){
            isp[i*prime[j]]=0;
            if(i%isp[j]==0)break;
        }
    }
}
int num[N],cnt[N];
int prim(int n){
    int mx=0;
    memset(num,0,sizeof(num));
    for(int i=1;prime[i]<=n&&i<=prime[0];i++){
        while(n%prime[i]==0){
            n/=prime[i];
            num[prime[i]]++;
            mx=i;
        }
    }
    return mx;
}
int prim_(int n){
    int mx=0;
    memset(cnt,0,sizeof(cnt));
    for(int i=1;prime[i]<=n&&i<=prime[0];i++){
        while(n%prime[i]==0){
            n/=prime[i];
            cnt[prime[i]]++;
            //printf("%d\n",prime[i]);
            mx=i;
        }
    }
    return mx;
}
int main(){
    int T;
    scanf("%d",&T);
    init();
    while(T--){
        int a,b;
        scanf("%d%d",&a,&b);
        if(a==1||b==1){
            printf("Yes\n");
            continue;
        }
        int pa=prim(a),pb=prim_(b);
        if(pa==0||pb==0||pa!=pb){
            printf("No\n");
        }
        else {
            bool ok=1;
            for(int i=1;i<=pb;i++){
                if((num[prime[i]]+cnt[prime[i]])%3!=0){
                    ok=0;break;
                }
            }
            if(ok)printf("Yes\n");
            else printf("No\n");
        }
    }
}
```
再想一下优化，其实没必要把每个质因数都枚举一遍，因为它又没让求是怎么分解的，所以直接对所有的整体的开三次方就好，然后这样就相当于开出了所有的质因数，先判断能不能开尽，再判断质因数就好。
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;
const int N=1e6+10;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int a,b;
        scanf("%d%d",&a,&b);
        ll s=(long long)a*b;
        ll x=pow(s,1.0/3)+0.5;
        if(x*x*x!=s||a%x||b%x)
            printf("No\n");
        else printf("Yes\n");
    }
}
```

---

## 作者：Rookie_t (赞：0)

不妨设两个人的分数为 $a$ 和 $b$。

根据题意，必须要满足 $a \times b = n^3$ 且 $a$ 和 $b$ 都能整除 $k$。
 
我们就可以用这个判断条件来写代码了： 
```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a,b;
signed main(){
	ios::sync_with_stdio(false);
	cin >> n;
	while(n--){
		cin>>a>>b;
		int k = round(pow(a * b,1.0 / 3));
		if((pow(k,3) == a * b) && a % k == 0 && b % k == 0){
			puts("Yes");
		}
		else{
			puts("No");
		}
	}
	return 0;
}
```

---

## 作者：asas111 (赞：0)

## 思路
不论是哪一方赢，双方得分的乘积是不变的，都为 $k^3$，即 $x\times y=k^3$。并且双方得分一定整除 $k$。

所以对于每一个询问，只需要判断 $\sqrt[3]{x\times y}$，即 $k$ 是否为整数，和 $k\mid x$，$k\mid y$ 就可以了。

STL 中有一个函数叫 cbrt，可以求出一个数的立方根。本题的数据范围比较大，需要用 long long。输入输出需要用 scanf 和 printf，否则会超时。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int a;
	cin>>a;
	while(a--){
		int x,y;
		scanf("%lld%lld",&x,&y);
		int z=round(cbrt(x*y));
		if(z*z*z==x*y&&x%z==0&&y%z==0)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```


---

## 作者：GFyyx (赞：0)

## 解题思路
题目中 $1 \leq a,b \leq 10^9$ 且有多组数据，显然是一道思维题。

## 推理结论
因为胜利者的得分在那之后会乘以 $k^2$，而输了的人的得分就只能乘以 $k$。假设进行了 $x$ 场比赛，$a$ 或 $b$ 均可表示为 $\prod\limits_{i=1}^xk^p_i,p \in [1,2]$。

因此对于合法的 $a,b$ 都有以下两个性质：
1. $a \times b = k^3_1 \times k^3_2  \times \dots \times k^3_x$。
2. $a \mid \sqrt[3]{a \times b}$ 且 $b \mid \sqrt[3]{a \times b}$。

判断 $a,b$ 是否满足这两个结论即可。

## AC 代码
```c
#include <stdio.h>
#include <math.h>
long long a,b,c,n;
int main(){
	scanf("%lld",&n);
	while(n--){
		scanf("%lld%lld",&a,&b);
		c=round(pow(a*b,1.0/3));
		if(c*c*c==a*b&&(a+b)%c==0)puts("Yes");
		else puts("No");
	}
	return 0;
}
```

### 温馨提示
该代码为本蒟蒻远古 C 码风，记得开 ```long long``` 勿抄。

---

## 作者：WOL_GO (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF833A)

一道数学题。首先，因为赢的人分数能 $\times k^2$，而输的人分数能 $\times k$，所以两人的分数一共 $\times k^3$，所以两人分数最终的乘积一定是一个数的三次方，并且两个人的分数也一定能整除那个数。所以判断一下这三个条件就好了

**代码**
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
#define ll long long
void read(ll &xx){
    register char ch=getchar();
    register ll ans=0;
    char t=0;
    while(!isdigit(ch))t|=ch=='-',ch=getchar/*_unlocked*/();
    while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar/*_unlocked*/();
    xx=t?-ans:ans;
    return ;
}
void write(ll x){
    if(x<0){
        putchar('-');
        x*=-1;
    }
    char wr[18];
    ll cnt=1;
    if(x==0){
        putchar('0');
        putchar('\n');
        return ;
    }
    while(x){
        wr[cnt++]=x%10+'0';
        x/=10;
    }
    for(cnt--;cnt;cnt--){
        putchar(wr[cnt]);
    }
    putchar('\n');
    return;
}
ll t;
int main(){
    read(t);
    while(t--){
        ll x,y,k;
        read(x);
        read(y);
        k=round(pow(x*y,1.0/3));
        if(k*k*k==x*y&&x%k==0&&y%k==0)puts("Yes");
        else puts("No");
    }
    return 0;
}
```

---

## 作者：YouXam (赞：0)


设$a$和$b$是两个人比赛的得分，对于$a$和$b$来说，每轮游戏不是$a=a \cdot k,b=b \cdot k^2$，就是$a=a \cdot k^2,b=b \cdot k$,显然每轮游戏，$a \cdot b$的总和都会被乘$k^3$，那么对 最后得分 开三次方后是整数，说明可能存在这种情况。

但是注意，这个条件并不充足。

还有一个条件，就是开立方的结果是$a$和$b$的因数

$\because ab=k^{3n}$

$\therefore \sqrt[3]{ab} = \sqrt[3]{k^{3n}} = k^n $

设进行了$p$次游戏，$a$或$b$最少乘了$p$次$k$，则$k^n$(开立方结果)一定是$a$和$b$的因数

反过来也成立，当$\sqrt[3]{ab}=k^n$是整数 且 $k^n$是$a$和$b$的因数 时，得分是合法的

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        long long a, b;
        scanf("%lld%lld", &a, &b);
        long long m = pow(a * b, (1.0 / 3)) + 0.5;
        puts((m * m * m != a * b || a % m || b % m) ? "No" : "Yes");
    }
    return 0;
}

```

---

## 作者：DarthVictor (赞：0)

## 题目
[原题链接](https://www.luogu.com.cn/problem/CF833A)
## 解说
~~题目名称起的太好了！~~

这道题属于思维/数学题，想明白了真的很简单。

一个数可以由许多数相乘得到，每个组成它的数就像它的成分一样。给一个数乘$k$就相当于在其组成中增加了$k$。那么我们看看这道题。

假设两个人分别为$A B$，初始均为$1$,那么一轮游戏中给$A$乘k就是在其组成中加入$k$，同时在$B$的组成中加入两个$k$，$AB$合计加入了三个$k$。显然$A×B$就相当于把$AB$混合在了一起，其所有成分都混合在了一起，所以$A×B$中一定含有三个$k$。那么我们只要判断$A×B$是否为完全立方数即可。

于是我写出了第一代代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
    char ch=getchar();
    ll s=0,f=1;
    while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9') {s=(s<<3)+(s<<1)+ch-'0';ch=getchar();}
    return s*f;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		ll a,b;
		a=read();b=read();
		ll u=a*b;
		ll m=pow(u,(1.0/3))+0.5;//计算立方根
  		//注意变为整数时+0.5四舍五入
		if(m*m*m!=u) cout<<"No"<<endl;
		else cout<<"Yes"<<endl;
	}
	return 0;
}
```
然后就WA了……

哪里有问题？哦，我们忽略了一种情况，假如把三个$k$都放到一个数里，那么我的程序会输出$Yes$，但事实上这是不符合条件的。我们还需要加一层条件，就是得到的立方根是$AB$两个数的因数。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
    char ch=getchar();
    ll s=0,f=1;
    while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9') {s=(s<<3)+(s<<1)+ch-'0';ch=getchar();}
    return s*f;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		ll a,b;
		a=read();b=read();
		ll u=a*b;
		ll m=pow(u,(1.0/3))+0.5;
		if(m*m*m!=u||a%m||b%m) cout<<"No"<<endl;
		else cout<<"Yes"<<endl;
	}
	return 0;
}
```


---

## 作者：灵茶山艾府 (赞：0)

把一个人赢的局的数字 $k$ 之积计作 $A$，另一个人的计作 $B$.

则有 $A^2B=a,\ AB^2=b$，两式相乘得 $(AB)^3=ab$，即 $AB=\sqrt[3]{ab}$.

所以 $A=\dfrac{a}{\sqrt[3]{ab}},\ B=\dfrac{b}{\sqrt[3]{ab}}$

注意到 $A$，$B$ 均为整数，这要求 $\sqrt[3]{ab}$ 为整数且 $\sqrt[3]{ab}\mid a,\ \sqrt[3]{ab}\mid b$，满足该条件时游戏结果正确。

AC 代码：(Golang)

```go
package main

import (
	"bufio"
	. "fmt"
	"math"
	"os"
)

func cbrt(a int64) int64 {
	r := int64(math.Round(math.Cbrt(float64(a))))
	if r*r*r == a {
		return r
	}
	return -1
}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var t, a, b int64
	for Fscan(in, &t); t > 0; t-- {
		Fscan(in, &a, &b)
		r := cbrt(a * b)
		if r == -1 || a%r != 0 || b%r != 0 {
			Fprintln(out, "No")
		} else {
			Fprintln(out, "Yes")
		}
	}
}
```


---


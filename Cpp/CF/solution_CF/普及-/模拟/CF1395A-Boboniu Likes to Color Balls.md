# Boboniu Likes to Color Balls

## 题目描述

Boboniu gives you

- $ r $ red balls,
- $ g $ green balls,
- $ b $ blue balls,
- $ w $ white balls.

He allows you to do the following operation as many times as you want:

- Pick a red ball, a green ball, and a blue ball and then change their color to white.

You should answer if it's possible to arrange all the balls into a palindrome after several (possibly zero) number of described operations.

## 说明/提示

In the first test case, you're not able to do any operation and you can never arrange three balls of distinct colors into a palindrome.

In the second test case, after doing one operation, changing $ (8,1,9,3) $ to $ (7,0,8,6) $ , one of those possible palindromes may be "rrrwwwbbbbrbbbbwwwrrr".

A palindrome is a word, phrase, or sequence that reads the same backwards as forwards. For example, "rggbwbggr", "b", "gg" are palindromes while "rgbb", "gbbgr" are not. Notice that an empty word, phrase, or sequence is palindrome.

## 样例 #1

### 输入

```
4
0 1 1 1
8 1 9 3
0 0 0 0
1000000000 1000000000 1000000000 1000000000```

### 输出

```
No
Yes
Yes
Yes```

# 题解

## 作者：Ryo_Yamada (赞：4)

一道细节题。主要考察可能性是否找全了，我 WA2 了一次/kk

易知，当四种球的个数有三种都是偶数时，定能摆成回文状。

而这个换球的本质其实就是把现有的偶数变成奇数，奇数变成偶数。

所以剩余的情况，若红绿蓝有一种球为 $0$ 或有两个偶数时，永远不能摆成回文状。

$\text{Code}$：

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

int r, g, b, w, cnt;

int main() {
	int t;
	cin >> t;
	while(t--) {
		cnt = 0;//多组数据记得归零
		scanf("%d%d%d%d", &r, &g, &b, &w);
		if(r % 2 == 0) cnt++;
		if(g % 2 == 0) cnt++;
		if(b % 2 == 0) cnt++;
		if(w % 2 == 0) cnt++;
		if(cnt >= 3) puts("Yes");
		else if(!r || !g || !b) puts("No");
		else {
			if(cnt == 2) puts("No");
			else puts("Yes");
		}//分情况讨论
	}
	return 0;
}
```


---

## 作者：_tommysun_ (赞：3)

**题目大意**：  
现有一些蓝色，绿色，红色与白色的球，每次可以挑一个蓝球，一个绿球与一个红球将其全部染成白色 （注意，单独的挑一个或两个颜色染色是不行的） ，问是否能通过操作将其排列成回文。

**思路**：

球的总数可以是偶数，也可以是奇数。我们分开讨论。

如果球的总数是偶数，每种球的数量就只能全是偶数，如果有一种球是奇数则无法构成回文。

如果球的总数是奇数，每种球的数量就必须有且仅有一个是奇数，其他都是偶数，奇数的那种球在中间（如下图，白球是奇数个球）

![](https://cdn.luogu.com.cn/upload/image_hosting/elua6ymf.png)

给出的球如果不能回文就继续染，直到达到上面的条件或无法继续染了为止。

注意一下，要用 long long ,否则会爆。

**代码**:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,b,c,d;
int main(){
    ios_base::sync_with_stdio(0); //卡常，不加会TLE。
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a>>b>>c>>d;
        while(a>0&&b>0&&c>0&&(a%2+b%2+c%2>1)){  //如果可以继续染且不能构成回文
            a--; b--; c--; d+=3; //染色
        }
        if(a%2+b%2+c%2+d%2<=1) cout<<"Yes"<<endl; //如果构成回文就输出Yes,否则输出No
        else cout<<"No"<<endl;
    }
    return 0;
}
```


---

## 作者：Demoe (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/CF1395A)

## 题意

- 给定四个数 $a$ $b$ $c$ $d$。

- 每次操作可以让 $a$ $b$ $c$ 减 $1$，$d$ 加 $3$，必须保证 $a,b,c,d \in N$。

- 问最后能否让四个数中**奇数**个数不超过 $1$。

## Sol

简单奇偶分析。

因为 加的 $1$ 减的 $3$ 都是奇数，那么每次操作即让 **四个数奇偶性全部改变**。

我们发现如果操作两次，奇偶性即与原来一样。

那么显然最多操作一次。

因为要保证操作后 $a,b,c,d \in N$，若 $abc=0$ 我们需特判掉，因为这种情况**无法进行操作**。

我们发现，若能操作，仅有原始奇数个数为 $2$ 的情况下不能满足题意。（$3 \to 1$，$4 \to 0$）

综合以上即可。

```cpp
/*
***
还要继续努力
成为一名烤咕学家哦
***
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a,b,c,d,x,cnt,T;
template <typename T> void rd(T &x){
	ll fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(ll x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(T);
	while(T--){
		rd(a);rd(b);rd(c);rd(d);
		cnt=(a&1)+(b&1)+(c&1)+(d&1);
		x=min(a,min(b,c));
		if(x==0){
			if(cnt>1) cout<<"No"<<endl;
			else cout<<"Yes"<<endl;
		}
		else{
			if(cnt==2) cout<<"No"<<endl;
			else cout<<"Yes"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：—维尼— (赞：0)

div2的第一题
## 题目描述

给定红绿蓝白四种球以及它们的数量，每次你可以把一个红球，一个绿球，一个蓝球共三个球变成一个白球，问你是否可以通过这种操作（不限次数）
让所有球能排成一个回文序列

ps:类似这样：“rrrwwwbbbbrbbbbwwwrrr”

 - ~~由于之前学长的毒瘤模拟赛，我看到这题居然想直接打暴力骗分走人~~ 
	

其实我刚开始就发现了很多规律，比如说**如果有大于两个以上奇数的球，那么就不行**
 - 可是为什么呢？
 - 翻译告诉我们，每次将三个（红绿蓝各一）涂成白色
 - 可以直接认为是将三个其他颜色的球改为一个白色球
 
 为什么是一个？
 
 因为都是奇数的情况下是一样的，（后面会证明）

## ok现在题目看完了

 - 继续说规律
 - 首先，证明有两个以上的奇数数量的球不行
 - 因为是回文串，只能有一个奇数子串（并放到中间）或者全是偶串

所以我们得出了只要有两个以上的奇数数量的球就不行（>=）

**那有人会问了：我可以变啊**

对，我们还要考虑变化一次之后的情况，当然在此之前要判断是否有足够的球
变化一次之后，再套用原来的公式，两次都不行的直接~~扼杀掉~~

**那有人又会问了：那我再变不行吗？**

可是你想想，就算你球够，你变两次之后奇偶不变啊

所以不需要循环

~~（我不会说我第一次还加了个while还t飞了）~~

## **整理思路**：

用奇数少于2的规律判断一次

先判断球够不够

变一次之后再判断一次

~~否就没救了~~ 

## 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,r,g,b,w;
bool xxx(int a,int b,int c,int d){
	if((a%2+b%2+c%2+d%2)>=2)
	return false;
	else return true; 
}

int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>r>>g>>b>>w;
		if(xxx(r,g,b,w)){
			cout<<"Yes"<<endl;
			continue;
		}
		else if(r>0&&g>0&&b>0&&xxx(r-1,g-1,b-1,w-1)){
			cout<<"Yes"<<endl;
		}
		else
		cout<<"No"<<endl;
		
	}
	return 0;
}
```



---

## 作者：白鲟 (赞：0)

## 前言
发现各位的代码都写得比较长，因此来发一篇题解。

## 题目分析
这四种球能够组成回文串，当且仅当个数为奇数的球不超过 $1$ 种。容易发现，“改变”操作会使得四种球的个数的奇偶性全部改变，因此仅有第一次使用该操作有意义。  

那么判断如下——若原四种球中仅有不超过 $1$ 种球个数为奇数，则可行；若能改变且改变后仅有不超过 $1$ 种球个数为奇数，亦可行；否则不可行。

## 代码
```cpp
#include<cstdio>
using namespace std;
int T,r,g,b,w;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&r,&g,&b,&w);
		if((r&1)+(g&1)+(b&1)+(w&1)<=1)
			puts("Yes");
		else if(r&&g&&b&&((r-1)&1)+((g-1)&1)+((b-1)&1)+((w+1)&1)<=1)
			puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：jeff_isapig (赞：0)

首先，这个题我们要分奇偶性来考虑

因为经过一次操作之后4个球的奇偶性会发生颠倒（也就是说3奇1偶和1奇3偶是一个东西）

所以我们用x记录在这四个球中有多少个偶数（**不能出现超过1个奇数！！！**）

------------


分情况考虑（一下情况不含0）：

1. **4奇/4偶**：因为四个偶数是可以的，所以4奇也可以

2. **3奇1偶/1奇3偶**：奇数取一个到中间，故可行

3. **2奇2偶**：不管如何变化都是2奇2偶，2奇无法构成回文，故不可行

------------

但是以上操作我们都忽略了一个东西：0

只要前三个球中有一个0代表什么呢，没错，就是无法变化

所以我们只需要考虑0的个数这个题就可以轻松A掉了

------------
又是分类讨论：

- **一个0**：只要剩下的有2个或3个偶数就可行
- **两个0**：只要剩下的2个不全是奇数即可
- **三个0**：不管怎样都可以

不需要考虑白球为0，因为白球只会加3

------------
又是~~喜闻乐见~~的放代码时间了
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int a,b,c,d;
		int x=0; 
		cin>>a>>b>>c>>d;
		if(a%2==0) x++;
		if(b%2==0) x++;
		if(c%2==0) x++;
		if(d%2==0) x++;
		if(a*b*c==0)
		{
			int num=0;
			if(!a) num++;
			if(!b) num++;
			if(!c) num++;
			x-=num;
			if(num==1)
			{
				if(x==2||x==3) cout<<"Yes"<<endl;
				else cout<<"No"<<endl;
				continue;
			}
			else if(num==2)
			{
				if(x!=0) cout<<"Yes"<<endl;
				else cout<<"No"<<endl;
				continue;
			}
			else if(num==3)
			{
				cout<<"Yes"<<endl;
				continue;
			}
		}
		if(x!=2) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
}
```


---

## 作者：infinities (赞：0)

是一道简单的小学数学题。

要求把所有四种颜色的球摆成回文串，而且可以进行操作把一绿一蓝一红三球改成白色。

回文串的条件非常显然，就是四种颜色球中单数的个数最多有一个，只看奇偶性，所以我们发现改两次和不改其实是一样的。

所以只有两种可能，改一次和不改，看这两种情况能否有一种达到要求即可。

注意特判三种球有一种球个数为 0 的情况，此时不能操作。

code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define rint regester int
const int maxn = 1e6 + 10;
const int INF = 1e9;
using std::ios;
using std::cin;
using std::cout;
using std::max;
using std::min;
using std::sort;
using std::unique;
using std::lower_bound;
using std::swap;
using std::abs;
using std::acos;
using std::queue;
using std::map;
using std::string;
int read(){
    int x = 0,f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
int t;
int r, g, b, w;
signed main(){
	t = read();
	for(int i = 1; i <= t; i++){
		int ans = 0;
		r = read(), g = read(), b = read(), w = read();
		if(r & 1)ans++;
		if(g & 1)ans++;
		if(b & 1)ans++;
		int qwq = min(r, min(g, b));
		if(qwq == 0 && ans + (w & 1) >= 2){
			cout << "NO\n";
			continue; 
		}
		if(qwq >= 1){
			if(ans + (w & 1) <= 1){
				cout << "YES\n";
				continue;
			}
			if(ans == 3){
				cout << "YES\n";
				continue;
			}
			if(ans == 1 && (w & 1)){
				cout << "NO\n";
				continue;
			}
			if(ans == 2 && (w & 1)){
				cout << "YES\n";
				continue;
			}
			if(ans == 2 && !(w & 1)){
				cout << "NO\n";
				continue;
			}
		}cout << "YES\n";
	}
}

```

---

## 作者：KSToki (赞：0)

要使得可以形成回文串，$r$，$g$，$b$，$w$ 中最多有一个奇数。若 $r$，$g$，$b$ 均不为 $0$，就有一次改变四个数的奇偶性的机会，判断即可。

代码中用的 $a$，$b$，$c$，$d$：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,a,b,c,d;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>a>>b>>c>>d;
		int cnt=0;
		if(a==0||b==0||c==0)
		{
			if(a&1)
			    ++cnt;
			if(b&1)
			    ++cnt;
			if(c&1)
			    ++cnt;
			if(d&1)
			    ++cnt;
			if(cnt<2)
			    cout<<"Yes"<<endl;
			else
			    cout<<"No"<<endl;
			continue;
		}
		if(a&1)
		    ++cnt;
		if(b&1)
		    ++cnt;
		if(c&1)
		    ++cnt;
		if(d&1)
		    ++cnt;
		if(cnt<2||cnt>2)
		    cout<<"Yes"<<endl;
		else
		    cout<<"No"<<endl;
	}
	return 0;
}
```


---

## 作者：luosw (赞：0)

### 题意简述

- 有四种颜色的球：$r,g,b,w$。

- 可以执行操作：将 $r,g,b$ 全部 $-1$，$w+3$。

- 问能不能通过这些操作，让 $r,g,b,w$ 这些小球摆成回文的队列。

- 回文的队列例如：$\texttt{rr}$，$\texttt{rgr}$，$\texttt{rgbgr}$，$\texttt{rgbbbbbwwwwbbbbbgr}$；但 $\texttt{rg}$ 不是回文。

### 题目分析

观察每一个回文的字符串，统计其中 $r,b,g,w$ 出现的个数：

|字符串|$r$|$g$|$b$|$w$|
|:-----:|:-----:|:-----:|:-----:|:-----|
|$\texttt{rgbbbbbwwwwbbbbbgr}$|$2$|$2$|$10$|$4$|
|$\texttt{rggbbbbbwwwwwbbbbbggr}$|$2$|$4$|$10$|$5$|

我们可以发现，要使 $r,g,b,w$ 组成回文，那么其中必定只有 $1$ 个以下的奇数，这个奇数多出来的一个应该放在回文字符串的**最中间**。

也就是说，得先判断 $r\bmod{2}+g\bmod{2}+b\bmod{2}+w\bmod{2}$ 与 $1$ 的大小关系。如果本身其结果小于 $1$ 不需要进行任何操作，那么直接输出 $\texttt{YES}$，反之，执行操作：

> 将 $r,g,b$ 全部 $-1$，$w+3$。

由于我们要探究的是奇偶性的关系，这里可以采用以 $2$ 为模的算术，$w+3$ 和 $w+1$ 本质上毫无区别，也就是说，**仅需判断执行一次操作后数的奇偶性，多次执行操作毫无意义**。只需要将 $r,g,b$ 全部 $-1$，$w+1$ 即可判断，但是这里要注意，因为**在现实生活中球的个数应该为非负整数，所以不可能减去后变成负数**，故在这里还需要加上条件 $r,g,b>0$ 才可以。

然后如果两次判断都不符合，直接输出 $\texttt{NO}$。

### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int  r, g, b, w, t;
bool a(int r, int g, int b, int w) {
    if (r % 2 + g % 2 + b % 2 + w % 2 > 1)
        return false;
    return true;
}
bool check() {
    if (a(r, g, b, w)) {
        return true;
    }
    else if (r > 0 and g > 0 and b > 0 and a(r - 1, g - 1, b - 1, w + 1))
        return true;
    return false;
}

int main() {
    cin >> t;
    while (t--) {
        cin >> r >> g >> b >> w;
        if (check())
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
    
}
```

---

## 作者：grass8cow (赞：0)

题意简述：你有红，绿，蓝，白四种颜色的球，每次操作可以使红绿蓝减一个，白加三个，要使它们能排成回文串。

能排成回文串，说明四种球的个数至多有一种是奇数。由于两次操作后奇偶性不变，可以考虑统计当前奇数个数，设其为  $ans1$ 。如果红，绿，蓝皆不为 $0$ ，则可以进行一次操作，有 $ans=\min(ans1,4-ans1)$ 。否则，$ans=ans1$ 。最后判断 $ans$ 是否小于等于 $1$ 即可。

code
```cpp
#include<bits/stdc++.h> 
using namespace std;
int T,r,g,b,w,a;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&r,&g,&b,&w);
		a=(r&1)+(g&1)+(b&1)+(w&1);
		if(r&&g&&b)a=min(a,4-a);
		if(a<=1)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```
： 

---

## 作者：引领天下 (赞：0)

显然只有 $4$ 种球中，个数为奇数个的要 $\le1$ 种，这样才可以形成回文串。（如果有 $2$ 种，则必然放不下去。）

那么我们先判断一下原始数据是否可行，不可行就看一下执行一次操作后是否可行就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    register int t,a,b,c,w;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d%d",&a,&b,&c,&w);
        if((a&1)+(b&1)+(c&1)+(w&1)<2)puts("Yes");
        else{
            if(a&&b&&c)a--,b--,c--,w+=3;
            if((a&1)+(b&1)+(c&1)+(w&1)<2)puts("Yes");
            else puts("No");
        }
    }
    return 0;
}
```

---


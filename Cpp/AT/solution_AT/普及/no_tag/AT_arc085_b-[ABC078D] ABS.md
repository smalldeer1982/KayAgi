# [ABC078D] ABS

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc078/tasks/arc085_b

$ N $ 枚のカードからなる山札があります。カードにはそれぞれ数が書かれており， 上から $ i $ 枚目には $ a_i $ が書かれています。

この山札を使い，X さんと Y さんが $ 2 $ 人でゲームをします。 X, Y さんは最初，$ Z,\ W $ が書かれたカードを持っています。 そして X さんから交互に以下を行います。

- 山札から何枚かカードを引く。そして今持っているカードを捨て，最後に引いたカードを代わりに持つ。ただし，必ず $ 1 $ 枚は引かなくてはならない。

山札がなくなるとゲームは終了で，$ 2 $ 人の持っているカードに書かれた数の差の絶対値がこのゲームのスコアになります。

X さんはスコアを最大化するように，Y さんはスコアを最小化するようにゲームをプレイした時， スコアはいくつになるでしょうか？

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 2000 $
- $ 1\ \leq\ Z,\ W,\ a_i\ \leq\ 10^9 $

### Sample Explanation 1

X さんが最初に $ 2 $ 枚カードを引くと，次に Y さんが最後のカードを引き，スコアは $ |1000\ -\ 100|\ =\ 900 $ になります。

### Sample Explanation 2

X さんが最初に全てのカードを引くと，スコアは $ |100\ -\ 1000|\ =\ 900 $ になります。

## 样例 #1

### 输入

```
3 100 100
10 1000 100```

### 输出

```
900```

## 样例 #2

### 输入

```
3 100 1000
10 100 100```

### 输出

```
900```

## 样例 #3

### 输入

```
5 1 1
1 1 1 1 1```

### 输出

```
0```

## 样例 #4

### 输入

```
1 1 1
1000000000```

### 输出

```
999999999```

# 题解

## 作者：UnyieldingTrilobite (赞：4)

[lnk](https://www.luogu.com.cn/problem/AT3671)。

首先我们试图证明一个结论：先手第一次取牌不会剩下超过一张。

我们注意到，如果先手至少留下了两张牌，那后手可以直接取到只剩一张牌，然后先手就只能取最后一张，后手可以做到 $|a_{n-1}-a_{n}|$ 的差值——由于后手要得分尽量小，所以最后得分不会比这个大了。而我们注意到，先手第一次取牌直接取到只剩一张也可以做到 $|a_{n-1}-a_{n}|$，不劣——那为什么要留给后手进一步优化的空间？

那我们就只要讨论先手第一次取 $n-1$ 张还是 $n$ 张就可以了。容易发现这两种情况下后手的操作都是唯一的，所以可以直接得出答案。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2009;
int n, z, w, a[N];
int main() {
  cin >> n >> z >> w;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  int ans = abs(a[n] - w);
  if (n > 1) ans = max(ans, abs(a[n] - a[n - 1]));
  return cout << ans << endl, 0;
}
```

---

## 作者：yyz_100110 (赞：3)

[ABC078D] ABS

这一题，我们先看题面，从样例入手： 

```
3 100 100       
10 1000 100 
```

假如我们的 X 拿了牌面最好的那张——1000，那么 Y 只能拿 100，那么绝对值就是 900 了。这样我们先理解一下样例，就可以有思路了呀！

我们不能单方面思考，只想 X 不想 Y，Y 他是有脑子的,他不可能放弃自己的牌，直接让 X 赢，如果你明白了这个题目，就可以开始制造你的代码了！还是以样例作为方法入手：

```cpp
#include <bits/stdc++.h>//万能头
using namespace std;
constexpr int j=2009;
int n,m,s;//全局变量
int a[j];
int main(){
    cin>>n>>m>>s;
    for (int i=1;i<=n;++i) {
            cin>>a[i];
    }
    int ans;
    ans=abs(a[n]-s);
    if(n>1){
        ans=max(ans,abs(a[n]-a[n-1]));
    }
    cout<<ans;
    cout<<endl;//日本题换行要记得
	return 0;//比赛时不能忘
}
```

---

## 作者：fish_love_cat (赞：3)

观察题面，我们发现，由于至少需要拿一张，位于前面的牌必然是没用的。因为小 Y 也不是傻子，不会看小 X 拿了一个极其有利的牌，然后把剩下的牌扔掉结束游戏使小 X 直接获胜。他会留下一些牌，强制小 X 扔掉你手中的好牌去抓烂牌。所以如果小 X 摸了这张牌，小 Y 还能给你留牌的话，这张牌就没有必要且不能摸，因为不摸一定比摸不劣。为了不让小 Y 钻了空子，所以小 X 只能给小 Y 留下 1 张牌或者不留。那么，这个问题就已经非常简单了。求出留或不留两种选择中，对小 X 来说结果最优的选择的分数，输出即可。

经典博弈论，思路绿，代码红……

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,z,w;
    cin>>n>>z>>w;
    for(int i=0;i<n-2;i++){
        int x;
        cin>>x;//过滤掉前面
    }
    int x,y;
    cin>>x;
    if(n==1) y=x;
    else cin>>y;
    cout<<max(abs(y-x),abs(w-y));//输出较大值
    return 0;
}
```

---

## 作者：QLUjyroooy (赞：2)

博弈问题。

　　大概题意：

　　X,Y两个人，手中各有一张牌，牌上的数字大小分别是Z，W。此时桌子上有N张牌，X、Y两个人一前一后从桌子上拿任意多的牌。

　　每次拿到几张牌后，把手头原有的牌扔掉，只保留刚刚拿起的这些牌里最后的一张。

　　一直到拿到桌子上没有牌之后，比较X、Y两个人手中牌的差。

　　X的目的是让结果最大化，Y的目的是让结果最小化 。

　　

　　这个题做的时候没有想到什么办法，因为桌子上的牌的数值是不确定的，没有办法根据这个直接判断，所以当时干脆让X先拿的时候拿到第 n-1 个或者第 n 个，然后进行对比，基本就是模拟了一下样例的过程。

　　然后该坐等WA了（稳如老狗）

　　哈？竟然过了emmmmm。。。好吧。。。。
  ```cpp
#include<iostream>
#include<cstdlib>
#include<math.h>
using namespace std;

int main(){
    int n, z, w, a[2010];
    cin >> n >> z >> w;
    for(int i=1;i<=n;i++) cin >> a[i];
    if(n==1) {
        cout << llabs(a[n]-w);
    }
    else{
        cout << max(llabs(a[n]- a[n-1]), llabs(a[n] - w));
    }
    return 0; 
}
```

---

## 作者：_AyachiNene (赞：1)

# 思路：
很容易看出，这道题就是到博弈论。我们可以分情况讨论：当 $n=1$ 时，先手至少拿一个，那么答案就是 $a_1-w$。否则，我们可以直接拿最后一张或倒数第二张，答案就是差值小的一个，因为就算先手前面拿的有多好，后面都还会拿，所以就等价于直接拿后两张中的一张。那么代码就很好实现。
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,z,w,a[114514];
int main()
{
	cin>>n>>z>>w;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	if(n==1)
		cout<<abs(a[1]-w);
	else
		cout<<max(abs(a[n]-a[n-1]),abs(a[n]-w));
}
```


---

## 作者：watcher_YBH (赞：1)

# 思路：
根据题目意思，每次取完后都要清空手中的牌。所以，每次取牌后只会保留最后一张。并且，小 $y$ 会让小 $x$ 拿到渣牌，所以，小 $x$ 要么只留一张牌，要么不留。
# 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)
using namespace std;
const int MAX = 1e5+5;
int n,z,w;
int a,b;
int main(){
	cin>>n>>z>>w;
	int ___;
	for(int i = 1; i<=n-2; i++) cin>>___;
	if(n == 1)cin>>b,cout<<abs(b-w);
	//当只有一张牌时，x只能拿第一张 
	else cin>>a>>b,cout<<max(abs(b-w),abs(a-b));
	//当多于一张牌时，比较只留一张牌，与不留的情况 
	return 0;
}
```



---

## 作者：STARSczy (赞：1)

# 思路：
由于无论如何拿牌，最优情况下只会剩最后两张。因此我们只需要判断最后两张的情况即可。特殊情况，当 $n$ 值为 $0$ 时，直接输出即可。

# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,z,w,a[1000000];

signed main(){
	cin>>n>>z>>w;
	for(int i=1;i<=n;i++) cin>>a[i];
	n==1?cout<<abs(a[1]-w)/*特殊情况*/:cout<<max(abs(a[n]-a[n-1]),abs(a[n]-w))/*最后两张*/;
	return 0;
}
```

---

## 作者：small_john (赞：1)

## 思路

简单的博弈论。

由于至少取 $1$ 个数，所以小 X 在最后只能取倒数 $2$ 个数，否则小 Y 则有可能让答案更小。

综上，答案最终有两种情况：

$$\begin{cases}|a_n-a_{n-1}|\\|a_n-w|\end{cases}$$

两种取最大值输出即可。**注意**：当 $n=1$ 时，不存在第一种情况，输出 $|a_n-w|$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e3+5;
int n,x,y,a[N]; 
signed main()
{
	cin>>n>>x>>y;
	for(int i = 1;i<=n;i++)
		cin>>a[i];
	if(n==1) cout<<abs(a[1]-y);//特判n=1
	else cout<<max(abs(a[n]-a[n-1]),abs(a[n]-y));
	return 0;
}
```

---

## 作者：Sirkey (赞：1)

非常简单的一个贪心。

在 $n$ 个数里面选两个数。令绝对值为最大的最小值。

这里有一点隐藏条件。如果你选了一个数，这个数不在末尾。另一个人再选一个你都是白搭。

那你就肯定选的是倒数第一个或者第二个啊。现在确定一个最大的。因为是 $x$ 先手。所以用的是最大值。

如果只有一个的情况下特判一下，毕竟倒数第二个此时为 $0$。

code：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define tell(ans) out(ans),printf("\n");
#define say(ans) out(ans),printf(" ");
#define pb push_back
//
//
//
using namespace std;
inline ll read() {
    ll f=0,t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}
inline void out(ll x) {
    if(x<0) putchar('-');
    if(x>9) out(x/10);
    putchar('0'+x%10);
}
ll a[100005],t;
int main() {
	ll n=read(),x=read(),y=read();
	FOR(i,1,n) a[i]=read();
	if(n==1) cout<<abs(a[1]-y);
	else cout<<max(abs(a[n-1]-a[n]),abs(a[n]-y));
    return 0;
}

```
——end——


---

## 作者：Yashajin_Ai (赞：1)

### 思路
与其他题解代码好像不是很一样，此题考虑的点其实在模拟两个人去那这个牌的过程，他没有说拿完马上轮换，所以思路一就出来了。

思路一：第一个人拿牌的时候可以拿到自己满意的牌再换，另一个人也是同理，那第一个人拿到满意的人拿到满意的了，第二个人满意的不是下一张呢？那只能让第一个人割舍自己心仪的牌，那当前这张牌。

那如果两个人轮流拿呢？

思路二：两人轮流拿牌，不管是否心仪，都拿。

那感觉思路二两个人很笨啊，但确实是一种拿法，那么，让先拿的人拥有思考，出现了思路三。

思路三：先拿的只要留了牌给后拿的，那么自己心仪的肯定会被换掉，那先拿的不如不给第二个人留牌。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,k,a[2001],f,kk,mm;
	cin>>n>>m>>k;
	a[n-1]=k;
	kk=k,mm=m;
	f=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(mm<=a[i]&&f==0){
			f=1;
			mm=a[i];
			kk=a[i-1];
		}
		else{
			mm=a[i];
		}
		if(kk>=a[i]&&f==1){
			f=0;
			kk=a[i];
			mm=a[i-1];
		}
		else{
			kk=a[i];
		}
	}
	cout<<max(abs(mm-kk),max(abs(a[n]-k),abs(a[n-1]-a[n])));
}
```

---

## 作者：whx2009 (赞：1)

## 本题思路：
这道题其实是一道结论题，因为每个人手上最多只能留拿的最后一张卡牌，并且每次最少必须拿一张，最多可以拿无数张，所以每次只需要判定最后两张就可以了（注意，当只有 $1$ 张牌时需要特殊判定）。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	int n,z,w,a,b;
	cin>>n>>z>>w;
	for(int i=0;i<n-2;i++)//其他牌不需要，就过掉了 
	{
	  cin>>s;
	}
	cin>>a;
	if(n==1) b=a;//判定特殊情况 
	else cin>>b;
	cout<<max(abs(b-a),abs(w-b));
	return 0;
}
```

---

## 作者：Kobe_BeanBryant (赞：0)

### 题目大意：
结论题，每个人手上最多只能拿最后 $ 1 $ 张卡牌，且每次最少必须拿 $ 1 $ 张，最多可以拿无数张，每次只要判定最后两张就可以了。

注意:当只有 $ 1 $ 张时要进行特判。

### 样例解释：
- 样例一：如果 $ x $ 先抽两张牌，$ y $ 抽最后一张牌，比分为 $ 1000 $ 与 $ 100 $ 之间的绝对值，及 $ 900 $。

### 公式：
$ a_n $ 与 $ a_{n-1} $ 之间的绝对值和 $ a_n $ 与 $ w $ 之间的绝对值中最大值。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,z,w;
long long a[2005];
int main(){
	scanf("%lld%lld%lld",&n,&z,&w);//输入
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	if(n==1)//当n等于1时进行特判
		printf("%lld",abs(a[1]-w));
	else//套用我们推出来的公式
		printf("%lld",max(abs(a[n]-a[n-1]),abs(a[n]-w)));
	return 0;
}
```

---


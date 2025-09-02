# Rule of League

## 题目描述

There is a badminton championship in which $ n $ players take part. The players are numbered from $ 1 $ to $ n $ .

The championship proceeds as follows: player $ 1 $ and player $ 2 $ play a game, then the winner and player $ 3 $ play a game, and then the winner and player $ 4 $ play a game, and so on. So, $ n-1 $ games are played, and the winner of the last game becomes the champion. There are no draws in the games.

You want to find out the result of championship. Currently, you only know the following information:

- Each player has either won $ x $ games or $ y $ games in the championship.

Given $ n $ , $ x $ , and $ y $ , find out if there is a result that matches this information.

## 说明/提示

In the first test case, player $ 1 $ and player $ 4 $ won $ x $ times, player $ 2 $ and player $ 3 $ won $ y $ times.

In the second, third, and fifth test cases, no valid result exists.

## 样例 #1

### 输入

```
5
5 2 0
8 1 2
3 0 0
2 0 1
6 3 0```

### 输出

```
1 1 4 4
-1
-1
2 
-1```

# 题解

## 作者：ImNot6Dora (赞：4)

由于每场比赛都分胜负，所以前两个人中一定有一个人直接输掉，他赢了零场，也就是说**如果 $\min(x,y)\neq 0$，这题无解。**

而由于第一轮比赛还有一个胜者，所以**如果 $\max(x,y)=0$，还是无解。**

根据前两条，我们可以发现，胜者**必须连续赢完 $\max(x,y)$ 场比赛**，之后的一轮比赛**必须输**，这也是后面输出的时候一个关键点。

我们设前两条成立，假设一共有 $a$ 个人胜利，根据刚刚我们的总结，$a\times \max(x,y)$ 一定等于 $n-1$，所以说，**如果 $a\times \max(x,y)\neq n-1$，那么还是无解。**

既然我们找到了所有的无解方案，我们就可以构造出如下代码：
```cpp
if(maxx>0&&0==(n-1)%maxx&&minn==0){
	//...
}else cout<<-1<<endl;
```
那么究竟我们要如何输出结果呢？

根据我们前面的总结：“胜者**必须连续赢完 $\max(x,y)$ 场比赛**，之后的一轮比赛**必须输**。”而前两名球员有一个胜者一个败者，我们可以假设其中一个人是胜者，当然如果我们选择第一个人的话就会……

![](https://cdn.luogu.com.cn/upload/image_hosting/46m3ubji.png?x-oss-process=image/resize,m_lfit,h_6500,w_6500)

所以我们要选择第二个人，也就是说，他连续获得了 $\max(x,y)$ 场比赛胜利后，下一个胜利的人是第 $\max(x,y)+2$ 个人。

我们可以用双重循环解决这个问题，内层主要是因为胜利者会连续胜利 $\max(x,y)$ 次。

于是，把所有的注意事项合并到一起，我们写出了如下代码：

### AC C++ CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,x,y,minn,maxx;
		cin>>n>>x>>y;
		maxx=max(x,y),minn=min(x,y);
		if(maxx>0&&0==(n-1)%maxx&&minn==0){
			for(int i=2;i<=n;i+=maxx){
				for(int j=1;j<=maxx;j++)cout<<i<<' ';
			}
			cout<<endl;
		}else cout<<-1<<endl;
	}
	return 0;
}
```
By ImNot6Dora

---

## 作者：yanhao40340 (赞：3)

[更 ~~好~~ 的阅读体验](https://www.luogu.com.cn/blog/yanhao40340/solution-cf1733b)

## 题意

~~毕竟翻译是我写的，就复制过来了。~~

有一场有 $n$ 个球员参加的羽毛球锦标赛，他们从 $1$ 到 $n$ 编号。

每一次比赛都由前一场的胜者与下一个没有比过赛的球员比赛。特别地，第 $1$ 场是 $1$ 号球员和 $2$ 号球员比赛。假设比赛没有平局。

例如第 $1$ 场是 $1$ 号球员和 $2$ 号球员比赛，第 $2$ 场是第 $1$ 场的胜者与 $3$ 号球员比赛，第 $3$ 场是第 $2$ 场的胜者与 $4$ 号球员比赛……以此规则进行了 $n-1$ 场比赛。

已知每一位球员要么赢了 $x$ 场球，要么赢了 $y$ 场球，请确定每一场比赛获胜的球员编号。

## 无解

显然，每一场比赛都有一个胜者和一个负者。

所以 $1$ 号选手和 $2$ 号选手中一定会有一个负者，也就是赢 $0$ 场的人。**即若 $\min\{x,y\} \ne 0$ 时，无解。**

再者，**如果 $x=0 \land y=0$ 时，显然无解。** 因为 $n-1$ 场比赛中必有胜者。

假设以上两条条件都满足，那么不妨设 $y=0$。由第二条可知 $x \ne 0$。

设一共有 $k$ 个获胜过的球员，那么可知 $kx=n-1$。即 $x \mid (n-1)$。于是我们又得到了一个条件：**如果 $x \nmid (n-1)$，那么无解。**

综上，我们可以写出以下的代码用来判无解：

```cpp
if (min(x,y)!=0||max(x,y)==0){puts("-1");return;}//条件1和条件2
if ((n-1)%max(x,y)){puts("-1");return;}//条件3
```

## 构造

不妨设 $y=0$，共有 $k$ 个获胜者，则 $x \ne 0$。

因为 $1$ 号球员和 $2$ 号球员中必有一个胜者，不失一般性，我们设 $2$ 号球员为胜者，则他一定获胜了 $x$ 局比赛。

显然获胜的比赛场次一定是连续的，所以下一个胜者即为 $x+2$ 号球员。

以此类推，因为 $kx=n-1$，所以最后一个获胜者编号为

$$(k-1)x+2=n+1-x \le n$$

而再往后一个循环到的获胜者编号为

$$kx+2=n-1+2=n+1 > n$$

**所以获胜球员编号循环到 $n$ 即可。**

构造部分代码：

```cpp
for (int i=2;i<=n;i+=max(x,y))
	for (int j=1;j<=max(x,y);++j) printf("%d ",i);
putchar('\n');
```

## 代码

由于核心代码已经给出，此处不在给出完整代码。完整代码详见 [link](https://codeforces.com/problemset/submission/1733/176630636)。

---

## 作者：SL_skb (赞：1)

# 题目大意
意思是有 $T$ 组数据。

每组数据由 $n$（人数），$x$，$y$。

而 $x$ , $y$ 则是进球的个数，也就是要么进 $x$ 球，要么进 $y$ 球。
# 解法
### 1
当然，我们知道，一场比赛只会有一个赢家，所以，想要 $x$ 和 $y$ 都大于 $0$。似乎是不可能的。

就拿第一场举例，如果第一个人赢，则第二个人就是赢 $0$ 场。反之亦然。
### 2
那么， $x$ 和 $y$ 都等于 $0$ 可以吗？

显然不可以。
### 3
最后因为场数是 $(n-1)$ 赢得人要赢 $\max(x,y)$, 所以，我们就可以设赢得人数为 $w$ ( $w$ 为正整数)，并可得到一个方程 $w\times\max(x,y)=(n-1)$。

知道这些，我们就可以敲代码了。

```cpp
if (y>0||x==0||(n-1)%max(x,y)!=0) cout<<-1;
```

# 输出
输出可是把我这个小蒟蒻搞死了。

~~于是乎我也看了眼 tj，终于理解了。~~

我们首先知道 $\min(x,y)=0$，$\max(x,y)>0$，$(n-1)\bmod\max(x,y)=0$。

我们不妨让 $2$ 号赢 $1$ 号，之后 $2$ 号一共赢 $x$ 场，再让第 $x+2$ 号赢 $x$ 场，在让……（就这样一直下去）

好了，上代码:

```cpp
for (int i=2;i<=n;i+=max(x,y))

for (int j=1;j<=max(x,y);j++) cout<<i<<" ";
```

那么最后 $AC$ 代码：
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL t,x,y,n;
int main(){
	cin>>t;            //输入数据的组数
	for (int sw=1;sw<=t;sw++){
		cin>>n>>x>>y;
		if (x<y) swap(x,y);   //这里偷点懒（swap为交换两数） 这样 x 就一定是大的，y 就是小的了
		if (y>0||x==0||(n-1)%x!=0) cout<<-1;
		else{
			for (int i=2;i<=n;i+=x)
			  for (int j=1;j<=x;j++) cout<<i<<" ";
		}
		cout<<"\n";
	}
}
```

---

## 作者：__Segment__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1733B)

### 无解条件：

由于题目保证一场比赛肯定有人赢，那么 $x$ 和 $m$ 不可能
都是 $0$，所以如果 $\max(x, y) \le 0$ 就一定无解。

如果 $x$，$y$ 中没有 $0$，那么也无解，也就是 $\min(x, y) > 0$。

比赛场数一定有 $n - 1$ 场，如果有解，那么：

设有 $k$ 个人赢了 $\max(x, y)$ 场，

那么：

$k \times \max(x, y) = n - 1$。

如果 $n - 1 \bmod \max(x, y) \not = 0$，那么无解。



### 如果有解：
式子应该满足 $ \max(x,y) >0$ 并且 $\min(x,y)\le 0 $。

最后只需要套公式就可以了。

### Code（C++ 版本）
```
#include <bits/stdc++.h>
using namespace std;
int _max(int a, int b) {return a > b ? a : b;}
int _min(int a, int b) {return a < b ? a : b;}
int main() {
	int n, x, y, T;
	cin >> T;
	while (T--) {
		cin >> n >> x >> y;
		if (x < y) swap(x, y);
		// 如果 x < y 那么交换 x 和 y。
		if (_max(x, y) <= 0 || min(x, y) > 0 || (n - 1) % x != 0) cout << "-1\n";
		else {
			for (int i = 1; i <= n; i += x) {
				int d = x;
				while (d--) cout << i << " ";
			}
			cout << endl;
		}
	}
}
```
### Code（C 版本）
```
#include <stdio.h> 
int n, x, y, T;
int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &x, &y);
		if (x < y) swap(x, y);
		if (y > 0 || x == 0 || (n - 1) % x != 0) {
			printf("-1\n");
		} else {
			for (int i = 2; i <= n; i += x){
				int d = x;
				while(d--) {
					printf("%d ", i);
				}
			}
			printf("\n");
		}
	}
	return 0;
}
```

代码如有不足请指出，谢谢。

---

## 作者：zhouweixi0 (赞：0)

# CF1733B
## 题意
[传送门](https://www.luogu.com.cn/problem/CF1733B)

有 $T$ 组数据，每组数据给出 $n$，$x$，$y$。

其中，$n$ 代表有多少个选手，$x$ 和 $y$ 代表一个人可以赢的场数。

输出获胜的选手编号。

## 如何实现
我们选择先判断无解情况，之后进行输出。

无解情况：

- 第一种情况：由于每场比赛都有败者，所以必然会出现胜 $0$ 场的情况，若没有，则直接判为无解。

- 第二种情况：由于每场比赛都有胜者，必然不可能出现只能胜 $0$ 场，若出现，直接判为无解。

- 第三种情况：由于会发生 $n-1$ 场比赛，而且根据我们之前的推测，$x$ 与 $y$ 中必会有一个为 $0$，则剩下的必为 $n-1$ 的因数，若不是，则判为无解。

如何输出：

我们让 $2$ 号选手一直胜利至不可再胜利，让下一个选手重复此过程即可。

## 代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,T;
int main(){
    cin>>T;
    while(T--){
        cin>>n>>x>>y;
        //判断无解
        if(min(x,y)!=0||max(x,y)==0||(n-1)%max(x,y)!=0){
            cout<<-1<<"\n";
            continue;
        }
        //输出
        for(int i=2;i<=n;i+=max(x,y)){
            for(int j=1;j<=max(x,y);j++){
                cout<<i<<" ";//输出是第几号选手
            }
        }
        cout<<"\n";
    }
    return 0;
}
~~~

---

## 作者：yigexiaobai (赞：0)

# CF1733B Rule of League
[题目传送门](www.luogu.com.cn/problem/CF1733B)
## 题意
每场比赛有 $n$ 人参加。同时，给定一组数据 $(x,y)$，代表每个人要么赢 $x$ 场，要么赢 $y$ 场，求每场比赛的获胜者是谁。
## 思路
无解情况：
- 1.因为每场比赛都有一个胜者和败者，所以就必有一个人直接输掉，一场也没赢，因此 $\min(x,y) \ne 0$ 时，无解。

- 2.同理，这场比赛中必有一人胜出，因此 $\max(x,y)=0$ 时，无解。

- 3.总结完前两条，我们发现最后场数是 $(n-1)$ 场获胜的人要赢 $\max(x,y)$。于是我们设赢得人数为 $a$，便可得方程 $a \times \max(x,y)=(n-1)$。因此，如果 $a \times \max(x,y) \ne (n-1)$ 时，无解。

判断代码如下：

```
if(min(x,y)>0||max(x,y)==0||(n-1)%max(x,y)!=0) printf("-1\n");
```

输出：

输出卡了我老长时间，~~感谢题解。~~

回到正题，输出时，我们不妨让二号赢一号，然后让二号一直赢 $x$ 场，再让 $x+2$ 号赢 $x$ 场，以此类推。
输出代码如下：

```cpp
for(int i=2;i<=n;i+=max(x,y){
	for(int j=1;j<=max(x,y);j++) printf("%d ",i);
}
```
## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){//多组样例输出
		scanf("%d%d%d",&n,&x,&y);
		int a=min(x,y),b=max(x,y);
		if(a>0||b==0||(n-1)%b!=0) printf("-1\n");
		else{
			for(int i=2;i<=n;i+=b){
				for(int j=1;j<=b;j++) printf("%d ",i);
			}
		}
		printf("\n");//换行
	}
	return 0;//完结撒花
}
~~~

---

## 作者：nono126 (赞：0)

# 题意
给出 $n$ 个数，每次操作可以使一个数加 $1$ 或者减 $1$。问经操作后至多有几个是相等的。
# 思路

我们可以很快发现，一个数加 $1$ 或者减 $1$，$n$ 个数的和是不会变的。总和不变，如果 $n$ 个数的总和是 $n$ 的倍数，那么就可以说明通过操作能使得所有数都相等。否则我们舍弃一个数，让其他数相等，其他数都和他一起进行操作，就能有 $n-1$ 个数相等。

# 代码展示
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,sum,x;
int main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&x);
        sum+=x;
    }
    if(sum%n==0) printf("%lld",n);
    else printf("%lld",n-1);
    return 0;
}
```


---

## 作者：Walrus (赞：0)

## 题意
一共有 $n$ 个人参加比赛，给定一组 $(x,y)$，每个人要么赢 $x$ 场，要么赢 $y$ 场，求每场比赛的胜者是谁。

## 分析数据范围
显然，题目给到 $0 \le x,y < n$，但并没有说明**有且仅有一个为 0**。于是便需要分类讨论 $(x,y)$ 的情况。

## 讨论数据范围
#### Top1.$\,x = 0,y = 0$
显然，每场比赛都有胜者，这种情况显然不可能，无解。

---
#### Top2.$\,x \neq 0,y \neq 0$
显然，每场比赛都有败者，这种情况同样不可能出现，无解。

先将上述两种情况综合，得出结论：

**$(x,y)$ 中有且仅有 1 个为 0**。

---
#### Top3.其他情况
上述两种比较容易发现的无解已经讨论完了，那我们就要思考如何解决问题。容易发现，**要么赢 $x$ 场球，相当于将 $1 \sim n$ 分成了若干条长度为 $x\,$ 的段**(我们假定 $x$ 为**非零数**)。

---
#### Top4.由情况3引出的无解
刚刚说到，把 $1\sim n$ 分成若干条长度为 $x$ 的段，那么我们可以发现，如果一个人想要赢得冠军，那么就要进行 **$n - 1$** 场比赛，因为一场比赛淘汰一人。

所以我们可以发现，当 **$n - 1$** 不是 $x$ 的倍数时，也是无解的。

上述 $x$ 均为非零数 $($较大值$)$。

---
问题已经分析到这，那么便可以写出代码。

## 实现程序
### 无解：
```cpp
if(!x && !y || x && y) {
	cout << -1 << '\n';
	continue;
}
x = max(x, y);
if((n - 1) % x) {
	cout << -1 << '\n';
	continue;
}
```
---
### 输出：
```cpp
for(int i = 1; i <= x; i++) {
	cout << 2 << ' ';
}
for(int i = x + 2; i <= n; i += x) {
	for(int j = 1; j <= x; j++)
		cout << i << ' ';
}
cout << '\n';
```
感谢观看。


---

## 作者：FSHYLHX (赞：0)

# 题目大意
每组比赛有 $n$ 个人，每个人要么赢 $x$ 场，要么赢 $y$ 场，问具体每场比赛的胜者是谁。
# 思路分析
首先来判断无解的情况，一共有三种。为了方便，我把 $x$ 和 $y$ 的最大值赋给 $x$。
#### 1
由于是淘汰赛，所以说第一场比赛一定有一个输的人被淘汰，所以说  $y$ 必须是 $0$，如果不是 $0$ 则无解。
#### 2
至少有一场比赛，所以不可能 $x$ 和 $y$ 都是 $0$，否则无解。
#### 3
因为场数有 $n - 1$ 场，所以场数是 $n - 1$ 的赢家要赢 $x$ 场。又因为人数一定是整数，所以说 $x$ 必须要被 $n - 1$ 整除，否则无解。

然后我们来思考如何输出有解的情况。

我们可以用贪心的策略，让 $2$ 号一直赢下去，赢 $x$ 场，然后再让 $x + 2$ 号一直赢下去，不断循环。
# 代码实现
```c
#include<bits/stdc++.h>
using namespace std;
int i,j,k,m,n,ans,sum,t,x,y;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&x,&y);
		if(x < y) swap(x, y);
		if(y != 0)printf("-1");
		else if(x == 0) printf("-1");
		else if((n-1)%x!=0) printf("-1");
		else{
			for(int i=2; i<=n; i+=x){
				int ans = x;
				while(ans--) printf("%d ", i);
			}
		}
		printf("\n");
	}
	return 0;
}

```


---

## 作者：lrmlrm_ (赞：0)

## 题意

有 $n$ 个球员参加比赛，编号为 $1\sim n$。第一场比赛 $1$ 号选手与 $2$ 号选手比赛。第二场比赛是第一场比赛的胜者与 $3$ 号选手比赛。假设比赛没有平局。第三场比赛是第二场比赛的胜者与 $4$ 号选手比赛。以此类推，对于第 $n$ 场比赛是第 $n-1$ 场比赛的胜者与 $n+1$ 号选手比赛（$n>1$）。已知每位选手要么赢了 $x$ 场球，要么赢了 $y$ 场球，问每场比赛胜利选手的编号。

## 思路

先考虑无解的情况：

1.一场比赛肯定会有人赢（题目保证没有平局），所以 $x$ 和 $y$ 不可能都是 $0$，如果都是 $0$ ，也就是 $\max(x,y)\leq 0$，就显然无解。

2.考虑第一场比赛输者接下来将不会再有比赛，也就是 $x,y$ 中肯定有一个 $0$ ，如果 $x,y$ 中没有 $0$，也就是 $\min(x,y)> 0$，也无解。

3.显然，场数有 $n-1$ 场，如果有解赢的人应该要赢 $\max(x,y)$ 场，已知如果有解应该满足 $\min(x,y)=0 $，$\max(x,y)>0$，设有 $k$ 个人赢了 $\max(x,y)$ 场，显然 $w\times\max(x,y)=(n-1)$（$w$ 为正数）。根据这一条式子，易得如果 $(n-1)\bmod\max(x,y)\neq 0$，$w$ 就不是整数，与式子不符，无解。

无解的情况考虑完了，接下来考虑有解时应当如何输出。

一个赢者肯定要连续赢 $\max(x,y)$ 场，连续赢完后肯定会输，从第 $1$ 场比赛开始连赢的可能是 $1$ 号选手或 $2$ 号选手，显然这两种情况都满足题目要求，为了~~不 `WA`~~ 方便，我们假设是 $2$ 号选手胜利，接下来在第 $1+\max(x,y)$ 场 $2$ 号选手肯定会输，第 $2+\max(x,y)$ 号选手取得胜利，开始连赢。容易想到，可以用双层循环来解决。外层循环枚举当前是几号选手正在连胜，内层循环满足胜利者要连胜 $\max(x,y)$ 场。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,t;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&x,&y);
		if(x<y)swap(x,y);
//此时x一定是两数中的最大值，y一定是两数中的最小值
		if(y>0||x==0||(n-1)%x!=0)printf("-1\n");
		else{
			for(int i=2;i<=n;i+=x){
				int xx=x;
				while(xx--)printf("%d ",i);
			}
			printf("\n");
		}
	}
	return 0;
}
```

---


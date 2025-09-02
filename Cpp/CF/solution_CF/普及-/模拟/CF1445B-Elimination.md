# Elimination

## 题目描述

There is a famous olympiad, which has more than a hundred participants. The Olympiad consists of two stages: the elimination stage, and the final stage. At least a hundred participants will advance to the final stage. The elimination stage in turn consists of two contests.

A result of the elimination stage is the total score in two contests, but, unfortunately, the jury lost the final standings and has only standings for the first and for the second contest separately.

In each contest, the participants are ranked by their point score in non-increasing order. When two participants have a tie (earned the same score), they are ranked by their passport number (in accordance with local regulations, all passport numbers are distinct).

In the first contest, the participant on the 100-th place scored $ a $ points. Also, the jury checked all participants from the 1-st to the 100-th place (inclusive) in the first contest and found out that all of them have at least $ b $ points in the second contest.

Similarly, for the second contest, the participant on the 100-th place has $ c $ points. And the jury checked that all the participants from the 1-st to the 100-th place (inclusive) have at least $ d $ points in the first contest.

After two contests, all participants are ranked by their total score in two contests in non-increasing order. When participants have the same total score, tie-breaking with passport numbers is used. The cutoff score to qualify to the final stage is the total score of the participant on the 100-th place.

Given integers $ a $ , $ b $ , $ c $ , $ d $ , please help the jury determine the smallest possible value of the cutoff score.

## 说明/提示

For the first test case, consider the following olympiad scenario: there are $ 101 $ participants in the elimination stage, each having $ 1 $ point for the first contest and $ 2 $ points for the second contest. Hence the total score of the participant on the 100-th place is $ 3 $ .

For the second test case, consider the following olympiad scenario:

- there are $ 50 $ participants with points $ 5 $ and $ 9 $ for the first and second contest respectively;
- $ 50 $ participants with points $ 4 $ and $ 8 $ for the first and second contest respectively;
- and $ 50 $ participants with points $ 2 $ and $ 9 $ for the first and second contest respectively.

 Hence the total point score of the participant on the 100-th place is $ 12 $ .

## 样例 #1

### 输入

```
2
1 2 2 1
4 8 9 2```

### 输出

```
3
12```

# 题解

## 作者：洛璟 (赞：4)

又是一道数学题 。~~（比赛的时候还因为正解的正确性和同学讨论（吵架）了半个小时。~~

先注意一个小小的坑，b是属于第二场比赛的最少分，d是第一场比赛的最少分。

同时注意以上给出的分数均为单场排名，非总分（

由于题目已经告诉我们分数按非降序排列，那么第100名的分数绝对比以前的99人都低 。~~（傻子都知道~~

那么这里我们可以得出，想要保证刚刚好卡到100人能进
~~（为什么不和ccf一样让尽可能多的选手参赛呢？~~，而a+b或c+d，~~易证~~他们就是总分中前101名总分最低的两人

证明： ~~（就是为了这个证明我讨（吵）论（架）了半小时）~~

第一场中第100名为a分，因此按第一场来算第100名总分最低分就是a+b，不会更低。

同理得按第二场来算第100名总分最低分为c+d。又因为分数按不降序排列，后面的人会比这两个更低，可以不用管。 ~~（蒟蒻无人权~~

~~这时，有人看到题目求最小值，笑容满面打了min（a+b，c+d）~~，这里我感谢这位同志为比赛多贡献了一个~~蒟蒻~~选手，这里我们手造几个数据，就会发现如果取min就会多选人，那么我们就取max罢。

好了，这就是正解。

~~码风清奇的代码：~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b,c,d;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')
	{
		x=(x<<1)+(x<<3)+(c^'0');
		c=getchar();
	}
	return x*f;
}
int main()
{
 
	t=read();
	while(t--)
	{
		a=read();
		b=read();
		c=read();
		d=read();
		printf("%d\n",max(a+b,d+c));
	}
	return 0;
}
```


---

## 作者：_121017_ (赞：2)

其实这道题很水，我们只要输出 $max ( a + b , c+d )$ 即可。

不过还是讲一下原因：因为第一场比赛前 $100$ 最差的是 $a$ 分，而第二场最差的分数为 $b$，第二场比赛前 $100$ 最差为 $c$，第一场为 $d$，所以两场比赛总分进了前 $100$ 中最差的两位诞生了，$ta$ 们的分数是 $a+b$ 和 $c+d$。

不过因为这题只能前 $100$ 的，所以要取 $max$。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		cout<<max(a+b,c+d)<<endl;
	}
	return 0;
}

```


---

## 作者：vеctorwyx (赞：2)

### 题目大意

~~原题面很啰嗦这里简述~~

有两场比赛，给出

第一场第一百名的分数（记作$a$），第一场前一百名所有人在第二场中的最小得分（记作$b$）；

第二场第一百名的分数（记作$c$），第二场前一百名所有人在第一场中的最小得分（记作$d$）。

**注意以上排名均为单场排名**，求总排名第一百名可能的分数的最小值。

### sol

设第一场第一百名的总分恰好为$a+b$，当然也可以证明第一场中不会有比他还小的最小得分；

设第二场第一百名的总分恰好为$c+d$，同理，也可以证明他在第二场中最小。

~~既然他没给其他东西直接取max就好了~~。接下来，要求第一百名分数的最小值，又可以证明两个单场内的排名一定是第一百名，则让其中一个为总排名的第一百名就好了，当然要取max。

所以用程序表达就是~~直接输出~~$\max(a+b,c+d)$。

code：

```
#include<bits/stdc++.h>
using namespace std;
int read()
{
    int x=0,y=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')y=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    return x*y;
}
int t,a,b,c,d;
signed main()
{
	t=read();
	while(t--)
	{
		a=read(),b=read(),c=read(),d=read();
		cout<<max(a+b,c+d)<<"\n";
	}
}
```

---

## 作者：Eason_AC (赞：1)

## Content
一个比赛分两场进行，其中：
- 第一场的第一百名成绩为 $a$，且第一场的前一百名在第二场中都至少得到了 $b$ 分。
- 第二场的第一百名成绩为 $c$，且第二场的前一百名在第一场中都至少得到了 $d$ 分。

求总分第一百名的成绩的最小值。

**数据范围：$0\leqslant a,b,c,d\leqslant 9,d\leqslant a,b\leqslant c$。**
## Solution
我们可以发现，第一场的前一百名的总分的最小值是 $a+b$，第二场的前一百名的总分的最小值是 $c+d$。故输出 $\max(a+b,c+d)$ 即可。

为什么？很显然，如果取较小值作为第 $100$ 名，那么较大值还排在了后面，那就显然不合理了。
## Code
```cpp 
int main() {
	int t = Rint;
	while(t--) {
		int a = Rint, b = Rint, c = Rint, d = Rint;
		printf("%d\n", max(a + b, c + d));
	}
	return 0;
}
```

---

## 作者：Su_Zipei (赞：1)

这题题意说实话有点难懂，翻译半天发现什么都看不出来。。。

~~于是比赛的时候我选择观察样例然后输出最大值~~

其实仔细想一下应该也不是很难，因为$a,b$是关于第一场里边前一百名的信息，$c,d$是关于第二场里边前一百名的信息，那么第一场里边在最后排名在前一百的人分数最低为$a+b$，同理第二场为$c+d$，因为最后只有一百人所以二者取最大值。

```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		printf("%d\n",max(a+b,c+d));
	}
	return 0;
}
```

---

## 作者：ql12345 (赞：1)

## 证明思路很好

#### 证明：

- 答案不小于这个数：

	这个数已经有至少100人了，所以第100名不可能小于这个分数
    
- 答案不大于这个数：

	大于这个数**没意义**，考虑在所有这条分数线上的人（包括这个分数）都是这个分，仍有至少100个人可选

#### 总结：

- 猜完结论之后，从正反两方面将结论证明，如果成功，不要犹豫，写上去就对了

- “没意义”是OI证明或构造时常用的套路，尤其是CF的题，只需考虑答案的正确性即可

#### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
	int t;
	cin >>t;
	while(t --)
	{
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		cout<<max(a+b,c+d)<<endl;
	}
	
	return 0;
}
```

---

## 作者：phil071128 (赞：0)

~~其实这是一道数学题~~

### 题意：

有一场比赛分为两场，以单调不增排名。现在已知：

- 第一场的第一百名成绩为 $ a $，且第一场的前一百名（包含）在第二场中都至少得到了 $b$ 分。

- 第二场的第一百名成绩为 $c$ ，且第二场的前一百名（包含）在第一场中都至少得到了 $d$ 分。

求两场的成绩加起来后，总分第一百名的成绩最小可能是多少。

我们知道：


- 第一场的前100名最少成绩为$a+b$

- 第二场的前100名最少成绩为$c+d$

- 总分的最小成绩为$ max(a+b,c+d)$

输出即为$max(a+b,c+d)$

### 代码：
```cpp
#include <iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int a,b,c,d;
    cin>>a>>b>>c>>d;
    cout<<max(a+b,c+d)<<endl;
    }
    
    return 0;
}
```
真是一道大好题

---

## 作者：greenheadstrange (赞：0)

**简述题面**：

第一场考试中的第100名的成绩为a，第一场考试中的前100在第二场考试中得的分均>=b

第二场考试中的第100名的成绩为c，第二场考试中的前100在第一场考试中得的分均>=d

**思路**:
由第一个条件可以得到总分前100名至少为a+b，同理第二个

故输出**max(a+b,c+d)** 即可
```cpp
#include<bits/stdc++.h>
#define _I inline
#define _R register
#define ll long long
#define ull unsigned long long
#define mod 998244353
#define eps 1e-4
#define INF 0x3f3f3f3f
#define lowbit(i) i&(-i)
#define memset(x,y) memset(x,y,sizeof(x))
#define memcpy(x,y) memcpy(x,y,sizeof(x))
using namespace std;
char buf[1<<18],*p1=buf,*p2=buf;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<18,stdin),p1==p2)?EOF:*p1++)
_I int read(){
	_R int x=0;_R char ch=getchar();_R bool f=0;
	while(ch<'0'||ch>'9')f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	f&&(x=-x);
	return x;
}
const int N=1;
int t,a,b,c,d;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	system("fc .out .ans");
	t=read();
	while(t--){
		a=read();b=read();c=read();d=read();
		printf("%d\n",max(a+b,c+d));
	}
	return 0;
}
```


---

## 作者：Midoria7 (赞：0)

## 题目大意

对于两场比赛，有

第一场的第 100 名成绩为 $a$，且第一场的人在第二场得分至少为 $b$。

第二场的第 100 名成绩为 $c$，且第二场的人在第一场的得分至少为 $d$。

求两场比赛成绩加和后第 100 名的成绩最少可能是多少。

## 思路

要求最少，那么最后的第 100 名一定是第一场的第 100 名或者第二场的第 100 名。可以知道第一场的第 100 名得分最少为 $a+b$，第二场的第 100 名得分最少为 $c+d$。假设 $a+b>c+d$，我们还取了 $c+d$ 作为最后的第 100 名，那么第一场的第 100 名的最后得分都会比最后的”第 100 名“大，这显然矛盾了。所以我们要取的就是 $a+b$ 和 $c+d$中的较大值。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read(){
	int x=0;bool fopt=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar())if(ch=='-')fopt=0;
	for(;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+ch-48;
	return fopt?x:-x;
}

int main(){
	int T=read();
	while(T--){
		int a=read(),b=read(),c=read(),d=read();
		printf("%d\n",max(a+b,c+d));
	}
	return 0;
}
```

---

## 作者：K2sen (赞：0)

### 简化题面
一共有两场考试。

现在给你第一场考试的第一百名的成绩 a，和第一场考试中的前 100 在第二场考试中获得的最小成绩 b。

第二场考试的第一百名的成绩为 c，和第二场考试中的前 100 名在第一场考试中获得的最小分数 d。

然后通过这两场考试的成绩的加和，会有一个排名，这个排名的前 100 名会进入终极考试，现在想问你最小的分数线是多少。

### 思路
~~直接输出 a+b,c+d中的最大值~~

可以发现从第一次给出的信息中可以得出最少成绩是 $a+b$，第二次给出的信息中可以得出最少的成绩为 $c + d$，所以如果想让其中的一个成为总排名的第 100 名，那就是要取一个最大值就好了。


### code
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
#define N 100010
#define M 1010

using namespace std;
const int mod = 1e9+7;
const int inf = 0x3f3f3f3f;
int T, a, b, c, d;

int read() {
  int s = 0, f = 0; char ch = getchar();
  while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
  while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
  return f ? -s : s;
}

int main() {
  T = read();
  while (T--) {
    a = read(), b = read(), c = read(), d = read();
    cout << max(a + b, c + d) << "\n";
  }
}
```

---

## 作者：幻影星坚强 (赞：0)

假设第一场前一百名的分数一样，一百名之后的分数一样，同时第二场前一百名分数一样，一百名之后的分数一样。那么想让答案最小肯定是让第一场前一百名都掉到第二场之外，第二场一百名都掉到第一场之外，这样既能保证答案的合法性也能保证答案最小（由于要让答案最小假设其他人都得了0分）。故只要判断$a+b$与$c+d$即可。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int t;
int main()
{
	scanf("%d", &t);
	while(t --)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		printf("%d\n", max(a + b, c + d));
	}
}
```


---

## 作者：enucai (赞：0)

### 题意

有两场比赛：

第一场的第 $100$ 名成绩为$a$，且第一场的人在第二场得分至少为$b$。

第二场的第 $100$ 名成绩为$c$，且第二场的人在第一场的得分至少$d$。

求两场比赛成绩加和后第$100$名的最少成绩是多少

### 题解

这道题是一道很明显的数学题。我们来观察一下样例：

` 1 2 2 1 `

答案是 ` 3 `

` 4 8 9 2 `

答案是 ` 12 `

不难发现，答案就是$a+b$与$c+d$的较小值。也就是说，是第一场前$100$名的总分与第二场$100$名的总分。

所以，答案直接输出$max(a+b,c+d)$就可以了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	int a,b,c,d;
	while(t--){
		scanf("%d%d%d%d",&a,&b,&c,&d);
		printf("%d\n",max(a+b,c+d));
	}
	return 0;
}
```

---


# Creating a Character

## 题目描述

You play your favourite game yet another time. You chose the character you didn't play before. It has $ str $ points of strength and $ int $ points of intelligence. Also, at start, the character has $ exp $ free experience points you can invest either in strength or in intelligence (by investing one point you can either raise strength by $ 1 $ or raise intelligence by $ 1 $ ).

Since you'd like to make some fun you want to create a jock character, so it has more strength than intelligence points (resulting strength is strictly greater than the resulting intelligence).

Calculate the number of different character builds you can create (for the purpose of replayability) if you must invest all free points. Two character builds are different if their strength and/or intellect are different.

## 说明/提示

In the first query there are only three appropriate character builds: $ (str = 7, int = 5) $ , $ (8, 4) $ and $ (9, 3) $ . All other builds are either too smart or don't use all free points.

In the second query there is only one possible build: $ (2, 1) $ .

In the third query there are two appropriate builds: $ (7, 6) $ , $ (8, 5) $ .

In the fourth query all builds have too much brains.

## 样例 #1

### 输入

```
4
5 3 4
2 1 0
3 5 5
4 10 6
```

### 输出

```
3
1
2
0
```

# 题解

## 作者：弦巻こころ (赞：2)

大意就是给你一个一些经验值,你可以加在智力或者力量上,但要求力量必须大于智力 ~~(莽夫预定)~~.问你有多少种方案.

这题还是很简单的,我们搞出要力量最小值和力量最大值.再相减,但须注意的是.这个值最多只有c+1 种,所以还要取个min.

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,b,c,minn,maxx;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>a>>b>>c;
		if((a+b+c)%2==0)//处理力量最小值
		{
			minn=(a+b+c)/2+1;
		}
		else
		{
			minn=(a+b+c+1)/2;
		}
		maxx=a+c;//力量最大值
		printf("%I64d\n",min(c+1,max(0ll,maxx-minn+1ll)));
     		//记得取min   
	}
}
```


---

## 作者：big_news (赞：2)

## 中文题面（google translate）

你又玩了自己喜欢的游戏。 你选择了之前没玩过的角色。 它具有体力点和智力点。 此外，在开始时，角色拥有免费的经验值，你可以在力量或智力方面进行投资（通过投资一点，你可以将力量提高1或者将智力提高1）。

既然你想要创造一个jock角色，那么它就有更多的力量，因此它的体力点比智力点更高（人物的体力一定大于其智力）。

如果必须投入所有免费积分，请计算您可以创建的不同角色构建的数量（为了可重复性）。 如果他们的力量和/或智力不同，则两个角色的构建是不同的。

## 题解

大水题一道。。。

设初始体力值是$a$，智力值是$b$，经验值是$c$。设$x,y$分别是给$a,b$分配的经验值，那么其实就是解方程$\begin{cases} x+y=c \\ a+x>b+y \\ x\geqslant 0\\ y\geqslant 0\\ \end{cases}$。

解出来之后$x$的范围是$[0,c] \cap (\dfrac{-a+b+c}{2},+\infty)$。这个东西取值并不是一定的，实际上有四种情况：$\dfrac{-a+b+c}{2}<0,\dfrac{-a+b+c}{2}=0,0<\dfrac{-a+b+c}{2}<c,\dfrac{-a+b+c}{2}\geqslant c$，分类讨论就好了，最后还得特判一下$c=0$，因为此时有两种情况重复。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

#define DB double
int a,b,c,t;

int main()
{
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		scanf("%d%d%d",&a,&b,&c);
		
		DB r = (b-a+c) / 2.0;
		
		if(r < 0) //[0,c]
		    printf("%d\n",c+1);
		
		if(r == 0) //(0,c]
		    printf("%d\n",c);
		    
		if(0<r && r<(DB)c){ //(r,c]
		    int int_r = r*10;
		    int_r /= 10;
		    printf("%d\n",c-int_r);
	    }
	    
	    if(r!=0 && r>=(DB)c) //empty
		    printf("%d\n",0);
	}
	
	return 0;
}
```

---

## 作者：幽界の冥神 (赞：1)

本题我交了两遍才过，挂在了一些细节上。

我的做法比较丑，手玩了几个样例，发现一些规律，
首先经过一些处理，使得$str = int + 1$， 保证了严格大于，当然如果此时$exp < 0$ 输出$0$否则此时为$str$最小值

接下来可以每次将$int - 1$，$str + 1$可以保证是合法方案，当然一个个减肯定超时，可以直接在$str = int + 1$的基础之上把剩下的$exp$全加到$str$上，即为$str$最大值

用最大值减去最小值加一即是答案

std :
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
 
using namespace std;
 
int t, a, b, c;
//a -> str
//b -> int
//c -> exp
int mxa, mna, lb;
//mxa -> Max_str
//mna -> Min_str

int main () {
	scanf ("%d", &t);
	while (t --) {
		scanf ("%d%d%d", &a, &b, &c);
		if (a <= b) {//防止a <= b
			c -= (b - a + 1);
			a = b + 1;
		}
		if (c < 0) {//特判
			puts ("0");
			continue;
		}
		if (c == 0) {//特判
			puts ("1");
			continue;
		}
		mxa = a + c;
		if (a - b > 1) {//使str == int + 1
			lb = b;
			b = min (b + c, a - 1);
			c -= (b - lb);
		}
		c = (c + 1) / 2;
		mna = a + c;
		printf ("%d\n", mxa - mna + 1);
	}
	return 0;
}
```

祝你幸福~~

---

## 作者：YGB_XU (赞：0)

VP 时做的题，~~怒交 n 发未过~~。

把题目信息转化为 $str$ 和 $int$ 的差，则满足大小关系时这个差值大于 $0$。那么如果不考虑大小关系，这个差值将最小为 $str-int-exp$，最大为 $str-int+exp$ 且每次变化 $2$ 。那么当差值无论如何都大于 $0$ 时，答案即 $exp+1$，而当差值无论如何都小于 $0$ 时，答案即 $0$。

此外的情况中，我们要计算差值大于 $0$ 的次数，就可以用

$$\left\lceil\dfrac{str-int+exp}{2}\right\rceil$$

得到答案（已经考虑过下界大于 $0$ 的情况，故不会出错）。

详见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t,a,b,c;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&a,&b,&c);
		int tmp1=a-b+c;
		int tmp2=a-b-c;
		if(tmp2>0){
			printf("%d\n",c+1);
			continue;
		}
		if(tmp1<=0){
			printf("0\n");
			continue;
		}
		printf("%d\n",(tmp1+1)/2);//这里是关键，加一后除二就可以应对两种奇偶性
	}
	return 0;
}
```

---

## 作者：晴耕雨读罢了 (赞：0)

这道题就是求exp分给str int 后使str>int的所有翻案数,求一个str加后最大值和最小值一减即可。

附上ac代码

代码中有详细注释可供理解


------------
```
#include<bits/stdc++.h>
using namespace std;
int n,mmin,mmax;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		/*找出最小值和最大值*/
		//最小值需要特判判断和为奇偶分别能取到的最小值
		//最小值为str刚好比int大一（和为奇） 或刚好大二（和为偶） 
		if((a+b+c)%2==0){
		//三个值相加为偶数的情况
		mmin=(a+b+c)/2+1;
		} 
		if((a+b+c)&1){
		//三个值相加为奇数的情况
		mmin=(a+b+c+1)/2;
		}
		//最大值为把exp全部加给str 
		mmax=a+c;
	    //记得判断exp为零情况 
		if(c==0&&a<=b)cout<<0<<endl;
		if(c==0&&a>b)cout<<1<<endl;
		if(c!=0&&a+c<=b)cout<<0<<endl;//小心exp+str没大于int 
		if(c!=0&&a+c>b)cout<<min(c+1,max(0,(mmax-mmin)+1))<<endl;//有一个会被减掉记得加一 
	}
	return 0;
}
```


---

## 作者：开始新的记忆 (赞：0)

题目大意：现在有n点，两种属性（力量和智力），现在告诉你了力量和智力的初始点数，要你把n点分配到这两种属性上使得力量的点数大于智力，求有多少中方案满足题意。

大致思路：先把n点都分配到力量上，然后先判断现在的力量和智力的点数大小关系，如果小于等于智力，则输出0，反之则减少一个就相当于两个之差减少了2

```
#include<bits/stdc++.h>
using namespace std;
 
int main()
{	int t;
	cin>>t;
	while(t--)
	{
		int n,a,b;
		cin>>a>>b>>n;
		int s=n+1;
        b+=n;
		int nn=b-a;
        if(nn==0)
			s=n;
        if(nn>0)
			s-=(nn/2+1);
        cout<<max(s,0)<<endl;
	} 
	return 0;
}
```


---

## 作者：Buried_Dream (赞：0)

## 题意：

通俗一点，你玩的一个角色是一个四肢发达的人，

力量需要大于智力，

给你一些经验加成，可以自由选择加在力量还是智力上，

求有多少种方案可以满足其四肢发达的人设。

## 思路：

找出能够满足条件的最小的力量值，再找出最大的力量值，

最大值：也就是将所有加成点加到力量上。

最小值：求出力量和智力相等的时候，因为必须是大于，所以再加上个一，注意分是奇数和是偶数两种情况。

## AC code:
```cpp
//内有防抄袭 
#include<bits/stdc++.h>
#define int long long
#define orz cout << "szt lps fjh AK IOI";
using namespace std;
const int maxn = 3e6;
const int MAXN = 3e3;

inline int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while (!isdigit(ch)) {if(ch == '-') {w = -1;}ch = getchar();}
	while (isdigit(ch)) {s = (s << 1) + (s << 3) + (ch ^ 48);ch = getchar();}
	return s * w;
}

inline void print(int x) {
	if (x < 0 ) putchar('-'), x = -x;
	if (x > 9 ) print(x / 10);
	putchar(x % 10 + '0');
}

//---------------------------------------------------------------------
int Abs(int a) { return (a ^ (a >> 31) - (a >> 31)); }
int Max(int a, int b) {	return a > b ? a : b; }
int Min(int a, int b) {	return a < b ? a : b; }
//---------------------------------------------------------------------
int szt[maxn], lps = 0, fjh = 0, wxf = 0; 
//---------------------------------------------------------------------
signed main() {
	int T = read();
	while(T--) {
		int a = read(), b = read(), c = read(); 
		int maxx = a + c; //力量最大的情况是将加成全给力量。
		int minn;
		if(!((a + b + c) & 1)) {
			minn = (a + b + c) / 2 + 1;
		}
		else {
			minn = (a + b + c) / 2;
		} 
		cout << Min(c + 1, Max(maxx - minn + 1, 0)) << endl;
	}
	return 0;
}

```


---


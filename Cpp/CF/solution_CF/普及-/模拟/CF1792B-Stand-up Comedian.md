# Stand-up Comedian

## 题目描述

Eve is a beginner stand-up comedian. Her first show gathered a grand total of two spectators: Alice and Bob.

Eve prepared $ a_1 + a_2 + a_3 + a_4 $ jokes to tell, grouped by their type:

- type 1: both Alice and Bob like them;
- type 2: Alice likes them, but Bob doesn't;
- type 3: Bob likes them, but Alice doesn't;
- type 4: neither Alice nor Bob likes them.

Initially, both spectators have their mood equal to $ 0 $ . When a spectator hears a joke he/she likes, his/her mood increases by $ 1 $ . When a spectator hears a joke he/she doesn't like, his/her mood decreases by $ 1 $ . If the mood of a spectator becomes negative (strictly below zero), he/she leaves.

When someone leaves, Eve gets sad and ends the show. If no one leaves, and Eve is out of jokes, she also ends the show.

Thus, Eve wants to arrange her jokes in such a way that the show lasts as long as possible. Help her to calculate the maximum number of jokes she can tell before the show ends.

## 说明/提示

In the first testcase, Eve only has jokes of the first type. Thus, there's no order to choose. She tells all her jokes, both Alice and Bob like them. Their mood becomes $ 5 $ . The show ends after Eve runs out of jokes.

In the second testcase, Eve only has jokes of the fourth type. Thus, once again no order to choose. She tells a joke, and neither Alice, nor Bob likes it. Their mood decrease by one, becoming $ -1 $ . They both have negative mood, thus, both leave, and the show ends.

In the third testcase, first, Eve tells both jokes of the first type. Both Alice and Bob has mood $ 2 $ . Then she can tell $ 2 $ jokes of the third type. Alice's mood becomes $ 0 $ . Bob's mood becomes $ 4 $ . Then $ 4 $ jokes of the second type. Alice's mood becomes $ 4 $ . Bob's mood becomes $ 0 $ . Then another $ 4 $ jokes of the third type. Alice's mood becomes $ 0 $ . Bob's mood becomes $ 4 $ . Then the remaining joke of the second type. Alice's mood becomes $ 1 $ . Bob's mood becomes $ 3 $ . Then one more joke of the third type, and a joke of the fourth type, for example. Alice's mood becomes $ -1 $ , she leaves, and the show ends.

In the fourth testcase, Eve should first tell the jokes both spectators like, then the jokes they don't. She can tell $ 4 $ jokes of the fourth type until the spectators leave.

## 样例 #1

### 输入

```
4
5 0 0 0
0 0 0 5
2 5 10 6
3 0 0 7```

### 输出

```
5
1
15
7```

# 题解

## 作者：Wind_Smiled (赞：5)

## 题意

有四种操作：

1.	令 A 和 B 均增加 $1$
2.	令 A 增加 $1$，B 减少 $1$
3.	令 A 减少 $1$，B 增加 $1$
4.	令 A 和 B 均减少 $1$

若 A 或 B 的值严格小于 $0$，则结束以后的操作，当前操作保留。

有 $T$ 组数据，对于每一组数据，分别给定四种操作的个数 $a1,a2,a3,a4$，输出最大的操作次数。

### 分析

显然的，使操作次数最多，要求尽可能先进行操作一，尽可能晚进行操作四。可以发现，若第一种操作可操作的次数为零，则无论如何再进行下一次操作时必将结束后续的操作。所以可以将判断放置最前，若满足 $a1$ 值为 $0$，则输出 $1$，进行下一组数据处理。

还可以发现，操作二和操作三是完全相反的，所以可以将两个相反的操作合并为一组，但是开始操作时有一个必要条件，即进行一组操作时，A 和 B 的初始值不能为 $0$。由于有了前面的判断，所以必定可以进行 $\min(a2,a3) \times 2$ 次操作。

剩余的操作次数会将 A 和 B 的值减小，且操作完成之后两个值相等，所以可操作次数显然是 这个值 和 剩余操作次数 的最小值。但是不要忘记操作结束是 A 或 B 的值 **小于** $0$ 或者不可操作。故要将 A 或 B 的值 加上一，再进行计算输出。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int a1,a2,a3,a4,ans;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d",&a1,&a2,&a3,&a4);
		if(a1==0){//不可操作 
			printf("1\n");
			continue;
		}
		ans=a1;
		ans+=min(a2,a3)*2;//2,3的相反操作 
		ans+=min(a1+1,abs(a2-a3)+a4);//在相反操作中已经进行了 min(a2,a3) 次操作，故要取大减小的差值再与 a4 的可操作数相加。 
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Convergent_Series (赞：4)

首先，如果 $a_1=0$ ，则说任何相声都会使其中一人离场，直接输出 $1$ ，结束。

$a_1$ 类型的相声不可能使人离场，一定要说。

容易发现，表演一个 $a_2$ 相声后再表演一个 $a_3$ 相声后，作用抵消，所以还可以说 $2\times\min(a_2,a_3)$ 个相声。

接下来有两种可能，一种是全部说完后没人离场，也就是又说了 $a_4+a_3+a_2-2\times\min(a_2,a_3)$ 个，另一种是说到有人离场，即有人的满意度为 $-1$ ，一共说了 $a_1-(-1)=a_1+1$ 个。在这两种情况中取最小值，加上之前说的即为答案。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5],sum,t;
int main(){
	cin>>t;
	while(t--){
		cin>>a[1]>>a[2]>>a[3]>>a[4];	
		if(a[1]==0){
			cout<<1<<"\n";
			continue;
		}
       		sum=a[1];
		int x=min(a[2],a[3]);
		sum+=2*x;
		sum+=min(a[1]+1,a[4]+a[2]+a[3]-2*x);
		cout<<sum<<"\n";
	}
	return 0;
}
```

---

## 作者：Syamoe (赞：2)

[原题 Link](https://www.luogu.com.cn/problem/CF1792B)

### 简明题意

（下文中讲 Alice 称为 A，Bob 称为 B）

有以下 4 种操作，使得：

1. A 和 B 均增加 $1$；

2. A 加 $1$，B 减 $1$；

3. A 减 $1$，B 加 $1$；

4. A 和 B 均减少 $1$；

若 A 和 B 中一个数 **严格小于 $1$**，结束以后操作（记录此操作）。

求出操作次数最大值。

### 题目分析

- 首先特判，如果 $a_1=0$ 时，无法进行任何操作，因此直接输出 $1$，结束；

考虑操作过程：

- 不难看出操作 1 是最优操作，无法操作 1 时尽量选择 2 和 3，尽量不要选择操作 4；

- 考虑简化操作 2 和操作 3，由于在进行操作过程中，2 和 3 可以看做同一类操作（即“一方加一，一方减一”类型操作） 因此考虑**合并操作**；

考虑结束条件：

- 中途有人离开，也就是 A 或者是 B 达到 $-1$，那么表演结束。计算总时间；

- 所有表演已经结束，自然结束，计算总时间；

### 代码

```cpp
#include <iostream>
#include <cmath>
using namespace std;
int main() {
	int T;
	cin >> T;
	while (T--) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		if (a == 0) {
			cout << "1" << endl;
			continue;//多组数据无法直接 break
		}
		int cnt = 0;
		if (b > c) {
			swap(b, c);//此处比较 b 和 c 谁小，以便后续的代码中不用取绝对值
		}
		cnt += a + 2 * b + min(a + 1, c - b + d);
		//这里要注意，题目里面说了最后一个节目也记总数 因此是 a+1
		cout << cnt << endl;
	}
	return 0;
}
```
----

### 后续

感谢您的观看

如果您发现这篇题解有不妥之处欢迎[私信 zsd](https://www.luogu.com.cn/chat?uid=358902) 奥！

完结——撒花！

---

## 作者：幻想繁星 (赞：2)

# 题意
给定 $a_1$，$a_2$，$a_3$，$a_4$ 且 $x=y=0$，你每次操作可以使：
1. $a_1-1\to a_1$，$x+1\to x$，$y+1\to y$；
1. $a_1-2\to a_2$，$x+1\to x$，$y-1\to y$；
1. $a_1-3\to a_3$，$x-1\to x$，$y+1\to y$；
1. $a_1-4\to a_4$，$x-1\to x$，$y-1\to y$；

在保证任何时候 $x$，$y$，$a_1$，$a_2$，$a_3$，$a_4$ 都不小于 $0$ 的情况下，最多可以进行多少次操作。
# 思路
首先执行操作一没有任何负收益，所以要尽可能多执行，也就是先执行 $a_1$ 次操作一。

其次操作二和操作三可以相互抵消，所以可以在 $x$，$y$ 结果没有任何变化的情况下，执行 $\min(a_2,a_3)$ 次操作二和 $\min(a_2,a_3)$ 次操作三。

然后我们可以在保证 $x$，$y$，$a_4$ 都不小于 $0$ 的情况下尽可能多地执行操作四，即执行 $\min(\min(x,y)+1,a_4)$ 次操作四。

最后分情况讨论：

- 如果 $x \ge y$，则可以执行 $\min(a_2,y+1)$ 次操作二；
- 如果 $y \ge x$，则可以执行 $\min(a_3,x+1)$ 次操作三；

## 特殊情况
如果 $a_1=0$ 那么执行任意一个操作就会使 $x$ 或 $y$ 小于 $0$，所以直接输出 $1$ 即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read();
int main()
{
	int t=read();
	while(t--)
	{
		int a[5],sum=0,x=0,y=0;
		for(int i=1;i<=4;i++)
			a[i]=read();
		if(a[1]==0)
		{
			cout<<"1\n";
			continue;
		}
		sum+=a[1];
		x+=a[1];
		y+=a[1];
		
		int mina=min(a[2],a[3]);
		sum+=2*mina;
		a[2]-=mina;
		a[3]-=mina;
		
		int minb=min(min(x,y)+1,a[4]);
		sum+=minb;
		x-=minb;
		y-=minb;
		
		if(x>=y&&x>=0&&y>=0)
			sum+=min(a[2],y+1);
		if(y>=x&&x>=0&&y>=0)
			sum+=min(a[3],x+1);
		
		cout<<sum<<"\n";
	}
	return 0;
}
```

如发现错误，请私信作者——[_1412_kid](https://www.luogu.com.cn/user/649095)。

---

## 作者：happy_zero (赞：1)

首先显然我们肯定是要优先考虑表演第 1 类相声，最后表演第 4 类相声（前提是可以表演），接下来我们主要考虑第 2 类和第 3 类相声。

在这里不妨设 $a_2\le a_3$，否则交换他们俩情况就一样了。

我们发现，当 `Alice` 和 `Bob` 心情都不为 0 时，表演一个第 2 类相声后再表演一个第 3 类相声后，他们的心情和表演前相同，所以**当两人心情都不为零时**可以把第 2 类和第 3 类打包在一起，共有 $a_2$ 组 $2\times a_2$ 个相声。

而其余的相声会使至少一个人的心情不断减少，因为只要有一个观众离开表演就结束，所以这时剩下的第 2、3 类相声其实和第 4 类相声一样了，只需考虑他们的总数即可：剩下的第 2、3 类相声有 $a_3-a_2$ 个，第 4 类相声有 $a_4$ 个，则共有 $a_3-a_2+a_4$ 个。

这里考虑前面表演了第 1 类相声和打包的 2、3 类相声可以将两人的心情增加 $a_1$，还能表演的相声节目就是 $min(a_1,a_3-a_2+a_4)$ 个？其实这个是错的。注意题目说的：

>若演完某个节目有观众退场，这个节目也算在总数之中。

所以当有人的心情减少到 0 时，若还有节目，则还可以继续表演，所以还能表演的相声数应该是 $min(a_1+1,a_3-a_2+a_4)$ 个。

把上述合并起来，就能得到最终的结果（答案用 $ans$ 表示）：

$ans=a_1+2\times a_2+min(a_1+1,a_3-a_2+a_4)$

最后看一下这道题要注意的地方（别被坑了！）：

1.把第 2、3 类打包起来后应该是组数的 2 倍。

2.若演完某个节目有观众退场，这个节目也算在总数之中。

**3.若 $a_1=0$，则只能表演一个节目（需要特判！！）。**

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    cin>>T;
    while(T--){
        int ans;
        int a,b,c,d;//这里用a,b,c,d代替a[1],a[2],a[3],a[4]
        cin>>a>>b>>c>>d;
        if(a==0){cout<<1<<endl;continue;}
        if(b>c)swap(b,c);
        ans=a+2*b+min(a+1,c-b+d); 
        cout<<ans<<endl;
    }
    return 0;
}
```


---

## 作者：fengxiaoyi (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/CF1792B)**

### 思路

显然，当 $a_1=0$ 时，输出 $1$（因为 $a_2,a_3,a_4$ 连续的无论怎么取都只能取 $1$ 个）。

如果 $a_1\not=0$，因为题目说：

> type 1: both Alice and Bob like them;

翻译过来就是第 $1$ 种笑话，两个人都喜欢，所以讲第 $1$ 种笑话是有益的。

所以，$ans$ 加上 $a_1$。

接着我们发现题目又说：

> type 2: Alice likes them, but Bob doesn't;  
> type 3: Bob likes them, but Alice doesn't;

所以，讲一个第二种再讲一个第三种不会改编两人的辛勤。

这样，就把 $ans$ 加上第二种和第三种的最小值再乘 $2$，既 $2\times\min(a_2,a_3)$。

现在，后三种的笑话还剩 $a_2+a_3+a_4-2\times\min(a_2,a_3)$ 个，而两人的心情值为 $a_1$。

所以，最后结束是要么讲了 $a_1+1$ 个后三种的笑话，两个人的心情值至少有一个人小于 $0$；要么是讲完了后三种笑话，结束表演。

则，$ans$ 加上 $\min(a_1+1,a_2+a_3+a_4-2\times\min(a_2,a_3))$。最后，输出 $ans$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a1,a2,a3,a4;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d",&a1,&a2,&a3,&a4);
		if(a1==0){
			printf("1\n");
			continue;
		}
		int ans=a1;
		ans+=2*min(a2,a3);
		ans+=min(a1+1,a2+a3+a4-2*min(a2,a3));
		printf("%d\n",ans);
	} 
	return 0;
}
```


---

## 作者：Cure_Wing (赞：0)

### 题目
[CF](https://www.luogu.com.cn/problem/CF1792B)[1792B](https://codeforces.com/problemset/problem/1792/B)

### 解析
首先考虑 $a_1=0$ 的情况。  
这时候显然 Eve 不管讲 $2,3,4$ 都会导致某人的心情小于 $0$，所以如果有相声答案为 $1$，没有为 $0$。

接下来考虑 $a_1>0$ 的情况。  
因为 $1$ 会使两人的心情增加，所以使用 $1$ 是不用担心变负的，所以可以直接讲掉。  
这个时候我们发现先讲 $2$ 再讲 $3$ 不会使两个人心情发生变化，所以我们可以将一个 $2$ 和一个 $3$ 打包，讲掉 $2\times\min(a_2,a_3)$ 个相声。  
接下来你就会发现无论怎么讲都会有一个人的心情持续下降，所以如果剩下的相声全部讲完后两个人的心情均为非负数，那么全部讲完。否则我们只能讲 $(a_1+1)$ 个相声，因为在讲完剩余第 $(a_1+1)$ 个相声后，至少有一个人的心情变负了。

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
int t,a,b,c,d;
signed main(){
// 	freopen(".in","r",stdin);
// 	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	for(cin>>t;t--;){
		cin>>a>>b>>c>>d;
		if(a==0) cout<<(b||c||d)<<'\n';
		else cout<<a+std::min(b,c)*2+std::min(a+1,b+c+d-std::min(b,c)*2)<<'\n'; 
	}
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

这题还没有人发题解，就发第一篇吧~

这是一道简单的贪心题。

容易发现肯定要先表演第一类相声，此时两人的快乐值都是 $a$，然后再交替地表演第二类、第三类相声，保持两人的快乐值为 $a$，此时，尽可能地表演剩下的第二类或第三类相声，直到一人的快乐值为 $0$，**然后如果还有剩余的相声，再表演一个。**

应当注意，当第一类相声为 $0$ 时，无法交替表演第二类、第三类相声，因为题目给了 $1 \le a1+a2+a3+a4$ 的条件，也就是保证了一定有相声，答案为 $1$。

具体细节略多，直接看代码吧：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a,b,c,d;
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		int ans;
		if(a)
		{
			int t = min(b,c);
			ans = a + 2*t;
			b -= t,c -= t;
			if(c) swap(b,c);
			if(a >= b) ans += b + min(a-b,d) + (d > (a-b));
			else ans += a + ((b > a)||d);
		}
		else ans = 1;
		printf("%d\n",ans);
	}
    return 0;
} 

```


---

## 作者：loser_seele (赞：0)

很简单但是讨论略麻烦的题目。

在以下的过程中，如果心情在全部笑话讲完前消耗完则答案要 $ +1 $，因为显然可以再讲一个跑路，否则不需要增加答案。

首先不难发现优先讲第一种笑话总是最优，因为不会使得任何一个人的心情变坏。如果根本没有第一种笑话答案显然是 $ 1 $，因为至少有一个笑话，然后接下来随便讲一个笑话都有人离场。

第四类笑话和二三两种比显然不优，所以二三种应该放在中间。

讲了 $ a $ 个第一类笑话后两人的心情都为 $ a $。因为 $ a=0 $ 已经在上面的讨论中被排除了，所以以下默认 $ a \geq 1 $。

考虑答案的一种构造：轮流讲两种笑话直到一种消耗完，然后讲剩下的。

这么做的正确性也不难证明，首先如果方案正确的话由于两种笑话效果互补所以在任意时刻只有两种情况：两个人心情不变，或者一个 $ +1 $ 一个 $ -1 $，因为 $ a \geq 1 $ 所以显然合法。

然后证明最优性：当某个时刻出现一个人心情较小，一个人心情较大的时候，显然使得两个人的心情尽量接近总是更优，否则会出现一个已经用完的情况。上面的构造方案恰好符合。

于是设 $ c,d $ 为二三种笑话的较小值和较大值，则应该先讲 $ \min(a,c) $ 个两种笑话，然后如果心情值足够再讲 $ \min(a,d-c) $ 个笑话（注意 $ a $ 表示当前心情，在上个过程中需要更新）。

最后剩下使得所有人心情值都降低的笑话，不难发现能讲的个数只取决于当前心情较小的一方（根据上面的构造，答案为 $ a-d $），然后判一下是心情先归 $ 0 $ 还是笑话先讲完即可。

时间复杂度 $ \mathcal{O}(T) $，可以通过。对于上面的分类讨论不懂的可以看代码实现。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int a[2000020],ans=0;
void gen(int n)
{
int f[2000020];
for(int i=1;i<=n;i++)
f[i]=i;
do
{
if(0)//add something here.
ans++;
}while(next_permutation(f+1,f+n+1));
}
#define Y cout<<"Yes"<<'\n'
#define N cout<<"No"<<'\n'
signed main()
{
int T;
cin>>T;
while(T--)
{
	int a,b,c,d,now=0;
	cin>>a>>b>>c>>d;
	now=a;
	if(now==0)
		cout<<1<<'\n';
	else
	{
		int tmp=max(b,c)-min(b,c);
		if(now<tmp)
			cout<<2*min(b,c)+now+a+1<<'\n';
		else
		{
			int ans=2*min(b,c)+a+tmp;
			now-=tmp;
			if(now>=d)
			cout<<ans+min(now,d)<<'\n';
			else
			cout<<ans+min(now,d)+1<<'\n';
		}
	}
}
}
```


---

## 作者：0zhouyq (赞：0)

### CF1792B 题解

[传送门](https://www.luogu.com.cn/problem/CF1792B)

### 思路：

分类讨论即可。

如果 $a_1=0$，因为 $a_1+a_2+a_3+a_4\ge1$，所以 $a_2+a_3+a_4\ge1$。但是无论从 $a_2$、$a_3$ 还是 $a_4$ 中选任意一个节目来表演，都会导致两人中的一个心情小于零，所以最多只能表演一个节目，直接输出。

如果 $a_1>0$，那么肯定首先把 $a_1$ 中的所有节目表演完。因为交换 $a_2$ 和 $a_3$ 并不会改变答案，我们就可以调整 $a_2$ 和 $a_3$ 使得 $a_2\le a_3$。此时两人的心情都至少为 $1$，我们可以交替表演 $a_2$ 和 $a_3$ 中的节目，两人的心情都不会变。到这里就已经表演了 $a_1+2\times a_2$ 个节目了。此时 $a_3$ 中只剩下 $a_3-a_2$ 个节目了。表演剩下的节目并不会使 Bob 的心情小于 Alice 的心情。所以我们只需要考虑 Alice 的心情。设她的心情为 $x$。此时再表演 $x+1$ 个节目她的心情就会小于零，表演就结束。或者再表演 $a_3-a_2+a_4$ 个节目表演也会结束。设 $x+1$ 和 $a_3-a_2+a_4$ 的较小的那个的值为 $q$，最终的答案就是 $a_1+2\times a_2+q$。

### AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ll t;
	scanf("%lld",&t);
	while(t--){
		ll a1,a2,a3,a4,ans=0,x=0;
		scanf("%lld %lld %lld %lld",&a1,&a2,&a3,&a4);
		if(a1==0){//特判
			printf("1\n");
		}
		else{
			ans=a1;
			x=a1;
			if(a2>a3) swap(a2,a3);
			ans+=2*a2;
			a3-=a2;
			ans+=min(x+1,a4+a3);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```

---


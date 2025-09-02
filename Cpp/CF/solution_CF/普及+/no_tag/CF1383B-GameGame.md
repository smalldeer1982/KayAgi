# GameGame

## 题目描述

Koa the Koala and her best friend want to play a game.

The game starts with an array $ a $ of length $ n $ consisting of non-negative integers. Koa and her best friend move in turns and each have initially a score equal to $ 0 $ . Koa starts.

Let's describe a move in the game:

- During his move, a player chooses any element of the array and removes it from this array, xor-ing it with the current score of the player.  More formally: if the current score of the player is $ x $ and the chosen element is $ y $ , his new score will be $ x           \oplus y $ . Here $ \oplus $ denotes [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).
  
   Note that after a move element $ y $ is removed from $ a $ .
- The game ends when the array is empty.

At the end of the game the winner is the player with the maximum score. If both players have the same score then it's a draw.

If both players play optimally find out whether Koa will win, lose or draw the game.

## 说明/提示

In testcase $ 1 $ of the first sample we have:

 $ a = [1, 2, 2] $ . Here Koa chooses $ 1 $ , other player has to choose $ 2 $ , Koa chooses another $ 2 $ . Score for Koa is $ 1 \oplus 2 = 3 $ and score for other player is $ 2 $ so Koa wins.

## 样例 #1

### 输入

```
3
3
1 2 2
3
2 2 3
5
0 0 0 2 2```

### 输出

```
WIN
LOSE
DRAW```

## 样例 #2

### 输入

```
4
5
4 1 5 1 3
4
1 0 1 6
1
0
2
5 4```

### 输出

```
WIN
WIN
DRAW
WIN```

# 题解

## 作者：灵茶山艾府 (赞：11)

从高位往低位判断：

1. 若该位 $1$ 的个数是偶数，要么两人各选奇数个 $1$，要么各选偶数个 $1$。无论怎么选，两人在该位的异或值相同，对输赢无影响。
2. 若该位 $1$ 的个数是奇数，则必有一人选到奇数个 $1$，从而获胜。
3. 接上，对于奇数，有 $4k+3$ 和 $4k+1$ 两种情况。若该位有 $4k+3$ 个 $1$，且该位有偶数个 $0$，则后手可以完全模仿先手的选择，先手必定会选到 $2k+2$ 个 $1$，而后手选到 $2k+1$ 个 $1$，先手必败；若有奇数个 $0$，则先手可以选一个 $0$ 从而让后手变成前述的情况，此时先手必胜。
4. 接上，若该位有 $4k+1$ 个 $1$，先手可以选一个 $1$，然后模仿后手的选择。对于有奇数个 $0$ 的情况，要么最后一个 $0$ 被后手选走然后剩下的 $1$ 两人平分，要么 $1$ 被选完先手选走最后的 $0$。无论情况如何，先手总是可以选到 $2k+1$ 个 $1$ 从而获胜。

最后，若所有位上的 $1$ 的个数均为偶数则平局。

AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

void run() {
    int n;
    cin >> n;
    vector<int> a(n);
    int s = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s ^= a[i];
    }
    if (s == 0) { // 所有位上的 1 的个数均为偶数则平局
        cout << "DRAW" << '\n';
        return;
    }
    for (int b = 30;; b--) {
        if (s >> b & 1) { // 该位 1 的个数是奇数
            int ones = 0;
            for (int v: a) if (v >> b & 1) ones++;
            int zeros = n - ones;
            cout << (ones % 4 == 3 && zeros % 2 == 0 ? "LOSE" : "WIN") << '\n';
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int t;
    for (cin >> t; t--; run());
}
```



---

## 作者：Bronya18C (赞：7)

我们先不考虑博弈论经典的Sg函数~~（毒瘤）~~

我们观察，我们要让最终的异或和最大，

设A为先手最终取完的值，B为后手最终取完的值

比如分别是24和23，拆分成二进制来看看

11000（8）

10111（7）

显然前面会有一段A，B相同（可能没有），前面都一样

然后突然B没有了，A仍然有，因为无论后面如何，这一位已经决定了A比B大了

### 所以问题就是抢最高位！！

好了，我们开始分析了

### Case.1假如最高位为偶数
此时，显然不影响最后结果

因为我们可以把偶数分解成奇数+奇数或偶数+偶数

如果是奇数+奇数，两个都有，不影响

如果是偶数+偶数，两个没有，不影响

所以我们再考虑次高位。

### Case.2当前的最高位为奇数
此时，又有两种情况，

 Case.2.1如果为4n+1个的话，那么肯定是分解成奇数+偶数，然后第一个人要抢奇数个，然后你们只能轮流抢，然后先手显然会比后手抢的多，所以先手会为奇数（好好想一下）

 Case.2.2如果为4n+3个的话，那么要分成两堆，含最高位的和不含最高位的，我们要保证自己不抢到偶数个，那么我们会变成有奇数+奇数+1个，然后我们要不抢到最后一个，那么我们会从没有最高位的垃圾堆里选，然后谁没得从垃圾堆里选，谁就输了，所以垃圾堆有奇数个，先手赢，有偶数个，后手赢。

### Case.3全是偶数，没有最高位为奇数

显然平局

代码实现：
这里选择先异或好，然后如果异或完为0就是Draw，不然分别考虑，先只保留最高位的1，然后判断有哪些有这个最高位的1，然后如果是4n+1,先手必胜，否则判断剩下的是奇数或偶数
```
#include<bits/stdc++.h>

using namespace std;
int t;
int n;
long long a[100005];
long long sum,g;
int lowbit(int u){
	return u&(-u);
}
int main(){ 
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		sum=0;g=0;
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]),sum=sum xor a[i];
		if(sum==0){
			puts("DRAW");
			continue;
		}
		while(sum-lowbit(sum)!=0)sum-=lowbit(sum);
		for(int i=1;i<=n;i++)
			if(a[i]&sum)g++;
		if(g%4==1){
			puts("WIN");
		}
		else{
			if(n%2==1)puts("LOSE");
			else puts("WIN");
		}
	}
	return 0;
}
```


---

## 作者：一架飞机 (赞：0)

这是一道博弈论的题。解题方法一般为：帮助先手找到一种策略，使后手怎么样都干都一定先手胜，这样就是先手必胜；或者帮助后手找到一种策略，使先手怎么样都干都一定后手胜，这样就是先手必输。常用的策略是：让先/后手跟着它前面的操作做对应的操作。

因为是异或，我们就贪心地从最高位开始一位一位地算，如果某一位先手必胜或者必输，就直接结束程序；如果这一位怎么样都不能决出胜负，就可以随便拿，所以看下一位。

设 $cnt$ 为 这一位 $1$ 的个数。

- 易得，$cnt$ 为偶数的时候，如果先手有偶数个，后手一定也有偶数个，奇数同理。所以不会决出胜负。

- 讨论 $cnt$ 为奇数时候，分四种状态。

	- $cnt=4k+1$，$n$ 为奇数。先手先拿一个 $1$，然后后手拿什么先手就拿什么。每次先手拿完以后，先手一定比后手多一个 $1$。因为 $cnt=4k+1$，所以~~用小学二年级学过的方程~~可以知道最后先手有 $2k+1$ 个，后手有 $2k$ 个。先手必胜。
	- $cnt=4k+1$，$n$ 为偶数。同上。然后因为每次先手拿完以后都一共拿了奇数个 $1$，所以最后后手拿到一定是 $0$。先手必胜。
	- $cnt=4k+3$，$n$ 为奇数。如果后手一直和先手拿一样的，最后一定剩一个 $1$ 给先手拿，后手 $4n+1$ 个，先手 $4n+2$ 个。先手必败。
	- $cnt=4k+3$，$n$ 为偶数。先手先拿一个 $0$，然后后手拿什么先手就拿什么。同理可得，先手必胜。

---

## 作者：FxorG (赞：0)

## $\text{Solution}$
这种异或贪心基本都是按位分析。

考虑从高位到低位，假如这一位有 $tot$ 个1，考虑按 $tot$ 奇偶来分。

偶： 考虑异或能有贡献的仅有 1，所以我们只分析 1 。假如 2 个人可以都选奇数个，即对 2 个人的答案都有贡献。假如都选偶数个，那么对于 2 个人来说都抵消了。所以偶数个 1 不会影响答案。

奇： 对于奇数，假如第二个人选 $x$ 个数，那么第一个人选 $x+1$ 个。考虑第一个人选的是奇数（才能对答案有贡献），即 $2k+1$ ,那么第二个人选 $2k$ 个，由于这样子可能胜利，所以我们保留这种情况，即 1 的数量 $tot \% 4==1$。为什么说可能胜利呢，因为假如有奇数个 $0$ ，那么完全可以让第一个人选到偶数个 $1$ 以及奇数个 $0$ ，让第二个人选到奇数个 $1$ 和偶数个 $0$。那么假如第一个人选 $2k+2$ 个 $1$,则第二个人选 $2k+1$ 个 $1$，判定方式类似于上面。但也不一定会输，因为只要有奇数个 0 ，那么就可以把奇数个 $0$ 留给自己，使得最后有奇数个 $1$。（实际上就是第一个必然选偶数个数，我们要保证有奇数个 1）

假如到了最低位都没法，显然平局。

## $\text{Solution}$

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>

#define N (int)(1e5+5)

using namespace std; 
int rd() {
	int f=1,sum=0; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*f;
}

int t,n,a[N];

int main() {
	t=rd();
	while(t--) {
		n=rd(); int S=0;
		for(int i=1;i<=n;i++) a[i]=rd(),S^=a[i];
		bool fl=0;
		for(int i=30;i>=0;i--) {
			if((S>>i)&1) {
				int tot=0;
				for(int j=1;j<=n;j++) tot+=(a[j]>>i)&1;
				//cout<<i<<" "<<tot<<endl;
				if((n-tot)%2==0&&tot%4==3) fl=1,puts("LOSE");
				else fl=1,puts("WIN");
			}
			if(fl) break;
		}
		if(!fl) puts("DRAW");
	}	
	return 0;
}
```

---


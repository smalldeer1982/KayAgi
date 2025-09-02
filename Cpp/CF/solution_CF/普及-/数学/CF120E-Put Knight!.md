# Put Knight!

## 题目描述

Petya and Gena play a very interesting game "Put a Knight!" on a chessboard $ n×n $ in size. In this game they take turns to put chess pieces called "knights" on the board so that no two knights could threat each other. A knight located in square $ (r,c) $ can threat squares $ (r-1,c+2) $ , $ (r-1,c-2) $ , $ (r+1,c+2) $ , $ (r+1,c-2) $ , $ (r-2,c+1) $ , $ (r-2,c-1) $ , $ (r+2,c+1) $ and $ (r+2,c-1) $ (some of the squares may be located outside the chessboard). The player who can't put a new knight during his move loses. Determine which player wins considering that both players play optimally well and Petya starts.

## 样例 #1

### 输入

```
2
2
1
```

### 输出

```
1
0
```

# 题解

## 作者：RainFestival (赞：3)

看到题目猜结论：

$n$ 为奇数先手赢，$n$ 为偶数后手赢。

然后就通过了。

其实这确实是对的。

只要下中心对称棋子就可以了。

只是争夺最中心一个点。

代码：

```cpp
#include<cstdio>
int t,n;
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        printf("%d\n",!(n%2));
    }
}
```

---

## 作者：Marshall001 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF120E)

## 题目大意

佩蒂娅和吉娜玩了一个叫“放一个骑士”的有趣游戏。有一个 $n \times n$ 的棋盘。在这个游戏中，他们轮流把“骑士”棋子放在棋盘上，以便没有两个骑士可以互相威胁。一个骑士可以威胁的范围和象棋中的马是一样的。不能在期盼放置新骑士的玩家将失败。注意，佩蒂娅和吉娜都很聪明。

佩蒂亚先下，请确定哪个人获胜。

## 思路

其实就是对称下法，佩蒂娅下（$1,1$），吉娜就会下（$n,n$）。这样子，就成了强中心点的游戏。$n$ 为奇数时先手赢，输出 $0$，否则后手赢，输出 $1$。

## 注意

这道题如果你得了 $0$ 分，或许不是你代码出了问题，而是你没有加：

```cpp
freopen
```

注意！这题一定要加这个，否则就会 $0$ 分！

## 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int main(){
	freopen("input.txt","r",stdin);//一定要加！
	freopen("output.txt","w",stdout);//一定要加！
	long long t;
	cin>>t;
	while(t--){
		long long n;
		cin>>n;
		if(n%2==0){
			cout<<"1";
		}
		else{
			cout<<"0";
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：云岁月书 (赞：2)

题目并不难。

首推打表大法，分分钟秒了这道题。

严谨点的话，这道题是个显然的博弈题。

但是我不会博弈论，所以下面的讨论可能并不博弈论。

首先有一个并不那么显然的结论：

在棋盘上放第一个骑士，那么若存在与之中心对称的位置，则那个位置必然可放下一个骑士且不会被第一个骑士攻击到。

扩展一下也不难得到本题思路:

若此前双方共放了 $2x$ 个骑士，且每一对敌对骑士都是中心对称的。

接下来若第一个人放了一个可以放位置，则与这个位置中心对称的位置也一定是可放的的(这个应该不难理解)！

综上在这种情况下，不难发现第二个人只需每一次下与第一个人上一次下的位置中心对称的位置就可以一直放下去。

也即此时先手必败。

对于 $n = 2k+1,k \in N$，也即不存在一个位置与自己中心对称的情况下，可以第一步下载那个中心的位置，此时相当于第二人变成了先手。

此时先手必胜。

唯一的坑点或许是要加 `freopen`。

代码就非常简单了：

~~~
# include <ctime>
# include <cmath>
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <algorithm>
# include <queue>
# include <iostream>
# define N 2000
# define LL long long

int T,n;

int main()
{
    //freopen("ysqm.in","r",stdin);
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    for(scanf("%d",&T); T ; T--)
    {
        scanf("%d",&n);
        if(n&1) puts("0");
        else puts("1");
    }
    return 0;
}

~~~

---

## 作者：Back_Stuff (赞：1)

一道很好的博弈论。

## 思路

首先我给出两张图，本人画的不喜勿喷。

![](https://cdn.luogu.com.cn/upload/image_hosting/845i1zss.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/kxbcwkzn.png)

一张是边长为 $7$，可放的骑士数量是 $17$ 个。

一张是边长为 $6$，可放的骑士数量是 $12$ 个。

骑士放的位置都是类似对角线的地方，所以我们可以将可放的骑士数量算出再判断。

```cpp
cin>>n;
ll k=0;
for(int j=n;j>=1;j-=3) k+=j;
k=k*2-n;
if(n%2==1) cout<<"0\n";
else cout<<"1\n";
```

我们还可以发现，可放的骑士数量与当前棋盘边长的奇偶性是相同的，所以可直接按照棋盘边长来判断。

```cpp
cin>>n;
if(n%2==1) cout<<"0\n";
else cout<<"1\n";
```

## 注意

如果你是 $0$ 分，那么一定是少了这个。

```cpp
freopen("input.txt","r",stdin);//一定要加！！！
freopen("output.txt","w",stdout);//一定要加！！！
```

---

## 作者：_segmenttree (赞：1)

### 思路

我们可以将棋盘对角线当作对称轴，模仿对手在棋盘对称处下。

由于两人的模仿，前面棋盘格子数除二轮都不会分出胜负，真正决定胜负的是两人走完这些轮后还剩的格子数。

如果棋盘有偶数个格子，那么剩零个格子，先手失败。不然剩一个格子，后手失败。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		if(n%2!=0) cout<<0<<"\n";
		else cout<<1<<"\n";
	}
	return 0;
}

```

---

## 作者：abensyl (赞：0)

原题：[CF120E Put Knight!](https://www.luogu.com.cn/problem/CF120E)

## 思路

本题是一个博弈论（~~我感觉我小学四年级的时候奥数就见过这道题~~）。

- 核心：在棋盘上放第一个骑士，那么若存在与之中心对称的位置，则那个位置必然可放下一个骑士且不会被第一个骑士攻击到。

当 $n$ 为偶数时，先手每下一步，后手对称着也下一步（在于先手下的点的中心对称的点下），最后先手一定会输。

当 $n$ 为奇数时，如果先手每下一步，后手对称着也下一步，那么，最后先手下在中心，后手没有地方下了，于是就输了。

- 注意：一定要用 **文件读写**！（我就因为没用 WA 了一次）

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int t;
  cin>>t;
  while(t--) {
    int n;
    cin>>n;
    cout<<((n%2)?0:1)<<'\n'; //判断奇偶数输出结果
  }
	return 0; //华丽结束
}
```

我的 [AC 记录](https://www.luogu.com.cn/record/85064218)

各位看官大佬，点个赞呗！

---

## 作者：DioxygenDifluoride (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF120E)

看完样例，我们可以猜测奇数先手胜，偶数后手胜。

提交代码后还真对了。

为什么这是对的？

$n$ 为奇数时，如果第一个骑士下在了一个位置，那么与其中心对称的位置就不会被第一个骑士击败； $n$ 为偶数时先手每下一步，后手也下一步，最后先手一定会输。最后说一句，这题有文件读写！
### 代码实现

```cpp
#include<stdio.h>
int T,x;
main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d",&T);
    while(T--)
        scanf("%d",&x),
        printf("%d\n",!(x&1));
}
```

---

## 作者：wangyi_c (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF120E)

## 1.题意讲解

两个小孩在玩放骑士游戏，骑士可以威胁到一些格子（即那几个格子里不能由对方放骑士），问有无必胜策略。

## 2.思路讲解

这是一道博弈论的题目，~~当然用打表找规律过也不是不行~~。

首先，我们可以发现，当放置一个骑士的时候，只要对方放置与其中心对称的位置，就肯定威胁不到对方。也就是说，后手只要一直下与先手中心对称的位置，后手必胜。
而先手只要下在一个没有中心对称点的位置，就可以变成后手，那么此时先手就必胜。而什么点没有中心对称点呢？对，就是**中心点**。而中心点只有在棋盘边长为**奇数**时才会出现，所以就不难推出：当 $n$ 为偶数时，后手会赢，输出 $1$；当 $n$ 为奇数时，先手会赢，输出 $0$。

忘记说了，这道题有点坑，要使用文件读写：

```cpp
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```

## 3.AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
signed main(){
	freopen("input.txt","r",stdin);//文件读写
	freopen("output.txt","w",stdout);
	cin>>t;
	while(t--){
		cin>>n;
		cout<<((n&1)^1)<<endl;//使用位运算，更快
	}
	return 0;
}
```
谢谢观看

 _THE END_
 
 By wangyi

---

## 作者：Tobiichi_Origami (赞：0)

**题目大意**

佩蒂亚赢了，或者是打平了，则输出 和吉娜在玩一个游戏，就是在一个 $n$ 乘 $n$ 的棋盘上放骑士，和象棋中的马一样。佩蒂亚先下，如果佩蒂亚赢了，则输出 $0$，否则输出 $1$。

**思路**

因打平或佩蒂亚赢输出 $0$，所以我们就尽可能的控制住其他的点。那到底怎么才能控制住呢，我们知道她们都是要放骑士，所以我们就先放到中心，把其他的点全部控制住，使后手到最后没有可放的点。那如果是偶数矩阵怎么办呢，就输出 $1$。最后，**记得用文件！**

**贴代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int T,n;
    cin>>T;
    while(T--)
    {
        cin>>n;
        if(n%2==0) cout<<"1"<<endl;
        else cout<<"0"<<endl;
    }
    return 0;
}


```


---

## 作者：cxy000 (赞：0)

首先让我们看看样例：

我们大概可以猜到什么呢？围着中心点下，奇数先手胜，偶数后手胜。

证明：

若 $n$ 为奇数则必有中点，而每次后手沿着对称点下，在最后先手下中点，则先手赢。

而当 $n$ 为偶数时没有中点，沿着对角线下，则后手必然取胜。

所以可以得出结论，上面猜想可以证明。

大概就这样：
```cpp
if(x%2==1) cout<<"0"<<endl;
else cout<<"1"<<endl;
```

不要想太复杂。

上全代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		if(x%2==1) cout<<"0"<<endl;
		else cout<<"1"<<endl;
	}
	return 0;
}
```

---

## 作者：Siteyava_145 (赞：0)

不放传送门了（逃

一道普普通通的博弈论的题。

骑士每行进一次，它的所在格子颜色就会变换，所以只要放在同色格上，就可以避免被攻击。

而最佳方案就为对称中心点的格子。那样可以保证这个格子没有被控制住，因为假设第一个人的棋子关于中心点对称的格子不可放置，那么反过来，第一个人的那颗棋子也是被控制住的（中心点对称），所以这就是最佳方案。

最终中心点周围的点全部被占满时，这时第一个人先走，如果棋盘有中心点（$n$ 为奇数），那么他将占领，则第二个人输掉，第一个人胜，输出 $0$。如果棋盘没有中心点（$n$ 为偶数），那么第一个人没得走了，则第二个人胜，输出 $1$。

注意加 ```freopen``` 文件操作！！！！！

AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    //xiexie讨论区的大佬
    int t;
    cin>>t;
    while(t--){
        int a;
        cin>>a;
        if(a%2==0){
            cout<<1<<endl;
        }else cout<<0<<endl;
    }
}
```


---

## 作者：ztntonny (赞：0)

## **思路**
贪心，$n$ 为奇数则输出 1，否则输出 0；其实可以证明，因为如果第一个骑士下在了一个位置，那么与其中心对称的位置就不会被第一个骑士击败，则在 $n$ 为偶时，先手每下一步，后手就对应着也下一步，最后先手一定输；若 $n$ 为奇数，那么先手必然选中间那个，而此时后手就等于先手了，后手必输。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    std::ios::sync_with_stdio(false);
    long long a , b;
    cin >> b;
    while ( b > 0 )
    {
        b--;
        cin >> a;
        printf ( "%d\n" , ! ( a % 2 ) );
    }
    return 0;
}
```


---


# Coin Games

## 题目描述

There are $ n $ coins on the table forming a circle, and each coin is either facing up or facing down. Alice and Bob take turns to play the following game, and Alice goes first.

In each operation, the player chooses a facing-up coin, removes the coin, and flips the two coins that are adjacent to it. If (before the operation) there are only two coins left, then one will be removed and the other won't be flipped (as it would be flipped twice). If (before the operation) there is only one coin left, no coins will be flipped. If (before the operation) there are no facing-up coins, the player loses.

Decide who will win the game if they both play optimally. It can be proved that the game will end in a finite number of operations, and one of them will win.

## 说明/提示

In the first test case, the game may go as follows.

- Alice chooses the first coin and $ s $ becomes "DDUU".
- Bob chooses the last coin and $ s $ becomes "UDD".
- Alice chooses the first coin and $ s $ becomes "UU".
- Bob chooses the first coin and $ s $ becomes "U".
- Alice chooses the only coin and $ s $ becomes empty.
- Bob can't choose any coin now, and he loses the game.

It can be proved that Bob will always lose if they both play optimally.

## 样例 #1

### 输入

```
3
5
UUDUD
5
UDDUD
2
UU```

### 输出

```
YES
NO
NO```

# 题解

## 作者：yitian_ (赞：8)

## 题目分析

题目描述了一个硬币游戏，游戏规则如下：

1. 有一排硬币，初始状态是一些硬币正面朝上，一些硬币背面朝上。
2. 两名玩家轮流操作，每次操作可以选择并取出一枚正面朝上的硬币，并将其相邻的两枚硬币翻转。
3. 如果玩家操作前没有正面朝上的硬币可供选择，则该玩家输掉游戏。也可以理解为玩家操作后没有正面朝上的硬币就胜利。

我们的目标是分析这个游戏的胜负情况，即在给定的初始硬币状态下，先手是否必胜。

## 思路

如题所述，操作分为两步：

1. 取出一枚硬币。
2. 翻转相邻的硬币。

如果在 $n$ 枚硬币中，有 $num$ 个硬币是正面朝上。

操作中取出硬币会改变 $num$ 的奇偶性；而翻转相邻的硬币，无论这两枚硬币状态是相同还是不同，都不会改变 $num$ 的奇偶性。

所以玩家的操作实际上就是改变 $num$ 的奇偶性。

由于两名玩家轮流操作，因此每位玩家的操作始终是将 $num$ 从奇数变为偶数，或者从偶数变为奇数。

玩家操作后如果没有正面朝上的硬币获胜。换句话说，获胜的玩家是将 $num$ 的奇偶性从奇数变为偶数的玩家。此题要求我们判断先手玩家是否必胜，也就是判断初始时 $num$ 是否为奇数。

## C++ 代码实现

```c
#include<bits/stdc++.h> // 包含标准库头文件
using namespace std; // 使用标准命名空间

int main() // 主函数入口
{
    int t; // 声明变量 t，用于存储测试用例数量
    scanf("%d",&t); // 从标准输入读取测试用例数量
    while(t--) // 循环执行测试用例
    {
        int n,num=0; // 声明变量 num 用于记录字符 'U' 出现的次数
        scanf("%d",&n); // 从标准输入读取字符串长度
        while(n--) // 循环读取每个字符
        {
            char c; // 声明字符变量 c，用于存储当前字符
            cin >> c; // 从标准输入读取一个字符
            if(c=='U') num++; // 如果当前字符是 'U'，num 加一
        }
        if(num%2==1) cout << "YES\n"; // 如果字符 'U' 出现的次数为偶数
        else cout << "NO\n";
    }
    return 0; // 返回程序执行成功
}
```

---

## 作者：cjh20090318 (赞：3)

赛时降智写了个链表暴力模拟，在小数据范围下还能过。

显然这种解法不够优美，所以还是讲正解。

## 题意

桌子上有 $n$ 枚硬币围成一个圆圈，每枚硬币要么朝上，要么朝下。两名玩家轮流操作。

在每次操作中，玩家选择一枚正面朝上的硬币，取出硬币并翻转与其相邻的两枚硬币。如果（操作前）只剩下两枚硬币，则取出一枚，另一枚不翻转（因为会翻转两次）。如果（操作前）只剩下一枚硬币，则不会翻转任何硬币。如果（操作前）没有正面朝上的硬币，玩家就输了。

两人做的都是最优决策，请问先手是否会获胜。

## 分析

分情况讨论。

1. 硬币周围有两个 `U` 时，此次操作会减少 $3$ 个 `U`。
2. 硬币周围有一个 `U` 和一个 `D` 时，此次操作会减少 $1$ 个 `U`。
3. 硬币周围有两个 `D` 时，此次操作会增加 $1$ 个 `U`。

观察到 `U` 个数的奇偶性是持续变化的，因为 `U` 的个数为 $0$ 时将无法操作，所以先手获胜的条件是 `U` 的个数为奇数。

## 代码

```python
T = int(input())
for _ in range(T):
    int(input())
    print('YES' if input().count('U')%2 else 'NO') # U 的个数是否为奇数。
```

---

## 作者：Hacker_Cracker (赞：1)

## CF1972B 题解
##### 第一篇题解求过。
[站内链接](https://www.luogu.com.cn/problem/CF1972B)
 [原地址](http://codeforces.com/problemset/problem/1972/B)
 
先看下 [AC](https://www.luogu.com.cn/record/157996804) 代码：
```cpp
#include <iostream>
#include <cstring>
using namespace std ;
int main() {
	int __T ;
	cin >> __T ;
    for (int i = 1 ; i <= __T ; i++) {
        int n ;
        string s ;
		cin >> n >> s ;
        int cnt = 0;
        for (int j = 0 ; j < s.length() ; j ++) {
			if (s[j] == 'U') cnt++ ;
		}
        if (cnt % 2 != 0) puts ("YES") ;//这里也可以写成 if (cnt & 1) ... ,效果相同
        else puts ("NO") ;
    }
    return 0;
}
```
从中不难看出，当且仅当 $\operatorname{U}$ 的数量是奇数时，Alice 才能取胜。下面进行证明：

+ $\textup{U\red{U}U -> DD}$ 
+ $\textup{U\red{D}D -> UD}$
+ $\textup{D\red{U}D -> DD}$

由此可见，当 $\operatorname{U}$ 的个数为奇数时，进行下一次操作的人必败。由此得出上文结论。

#### 撒花！

---

## 作者：Nake_fu (赞：0)

一道关于 **string**，而又关于 **博弈**  的水题。

# 我们来找一下规律：

当 $coin$ 为 $DUD$ 时会变成 $UU$ 这时正面次数 $+1$。

当 $coin$ 为 $UUD$ 时会变成 $UD$ 这时正面次数 $-1$。

当 $coin$ 为 $UUU$ 时会变成 $DD$ 这时正面次数 $-3$。

也就是说，当 $coin$ 数 $\le3$ 时，无论怎样硬币的正面次数都会发生**奇偶性的变化**。

而当 $coin$ 数 $\le2$ 时，就更不用说。

当为 $UD$ 时，则正面次数 $-1$。

当为 $UU$ 时，则正面次数 $-1$。

当 $coin$ 即使 $\le2$ **奇偶性仍旧变化**。

而上过学的人都知道**负负得正**，变化两次等于啥也没变化。

所以只要一开始 $coin$ 的**正面次数为奇数**，就直接输出 **YES**，否则就输出**NO**。

# [AC](https://www.luogu.com.cn/record/158451178) code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n,cnt;
signed main() //signed 是有符号的意思，可以代替 int。 
{
	int t;
	cin>>t;
	while(t--)
	{
		cnt=0;
		cin>>n;
		cin>>s;
		for(int i=0;i<n;i++)
		{
			if(s[i]=='U') cnt++; //统计正面次数 
		}
		if(cnt%2==1) cout<<"YES"<<endl; 
		else cout<<"NO"<<endl;
	}
	return 0; //完结撒花！！！ 
}
```

---

## 作者：hema5177 (赞：0)

### 思路（不正经）

ac 这道题有点阴差阳错，因为我只是在找样例规律。
```
3
5
UUDUD
5
UDDUD
2
UU
```

发现第二组数据和第一组数据只有一个 `U` 的差别，所以猜测是关于 `U` 的奇偶性，而第三组数据正好验证了这一点。

所以猜测当 `U` 的个数是奇数时输出 `YES`，否则输出 `NO`。

一种骗分方法，正解在下面。

### 思路（正经）

尝试分析关于题目中说的关于翻不同位置的硬币对于结果的影响，得出以下结论：

1. 翻左右各有一个 `U` 的硬币时，`U` 会减少 $3$ 个；

`UUU` -> `DD`

2. 翻左右各有一个 `D` 的硬币时，`U` 会增加 $1$ 个；

`DUD` -> `UU`

3. 翻只有左或右有一个 `D` 或者只剩 $2$ 个硬币时，`U` 会减少 $1$ 个；

`DUU` -> `UD`

`UU` -> `U`

那么 Alice 赢的条件是 Alice 拿走最后一个 `U`，而经过两个人的一轮操作后 `U` 奇偶性持续不变（一直增加或者减去一个偶数），所以要使最后剩下的 `U` 被  Alice 拿走，`U` 在最开始就必须是奇数。

代码如下。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,sum=0;
        string s;
        cin>>n>>s;
        for(int i=0;i<s.size();i++)
        {
            if(s[i]=='U') sum++;
        }
        if(sum%2==1) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}
```

---

## 作者：ggylz49 (赞：0)

## 思路
博弈论。我们用 `U` 表示正面，`D` 表示反面。

首先我们看一下在最后一轮（剩下 $2$ 枚硬币时）有什么情况：

1. `UU`：取走正面，对方取走正面，输。
2. `DU`：取走正面，胜利。
3. `DD`：不用说，输。

所以我们能确定，最后一轮时正面硬币一定要剩下奇数个。

再看一下普通的操作（不导致游戏结束）：

1. `UUU`：取走正面，翻转两个正面，正面数量减少三个。
2. `DUD`：增加一个正面，`DUD->UU`。
3. `DUU,UUD`：`UUD->DU`，`DUU->UD`，正面数量减少一个。

所以，每一次操作正面硬币都增加或减少奇数个，奇偶性会发生变化，而操作两次相当于奇偶性没有变化。

这导致了游戏结果：若正面硬币有奇数个，两人互相翻转，决胜局轮到先手时剩下的是奇数个硬币，先手胜；若正面硬币有偶数个，两人互相翻转，决胜局轮到先手时剩下的是偶数个硬币，先手负。

最后的结果是：游戏开始前硬币的个数只要是奇数个，先手就会胜利。
## Code
```cpp
#include <iostream>
#include <string>//使用string字符串调用<string>库
using namespace std;
int main()
{
    int t;
    cin>>t;
    while (t--)
    {
        int n,ans=0;//计量正面数量
        string s;
        cin>>n>>s;
        for (int i=0;i<n;i++)
        {
            if (s[i]=='U')ans++;
        }
        if (ans%2==1)cout<<"YES\n";//正面奇数个，胜
        else cout<<"NO\n";//否则负
    }
    return 0;
}
```

---

## 作者：Dream_Mr_li (赞：0)

## Solution

题目中说，没有正面朝上的硬币，玩家就输了。
也就是说，如果在对手回合之前，都是反面朝上的硬币，玩家就赢了。

我们先判断一下每种情况：

- `UUU` 去掉中间的 `U` 两边的 `U` 变成 `DD`，减少了三个 `U`。

- `DUD` 去掉中间的 `U` 两边的 `D` 变成 `UU`，增加了一个 `U`。

- `UUD` 去掉中间的 `U` 两边的 `U` 和 `D` 变成 `D` 和 `U`，减少了一个 `U`。

- `DUU` 去掉中间的 `U` 两边的 `D` 和 `U` 变成 `U` 和 `D`，减少了一个 `U`。

我们发现，无论怎么操作，正面朝上的硬币数量都会增加或减少一个奇数。

可以推出，胜负决定于**朝上硬币的个数**的奇偶性，而先手为了赢，初始正面朝上的的数量就得是奇数。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
signed main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		string s;
		int ans=0;
		cin>>n>>s;
		for(int i=0;i<n;i++){
			if(s[i]=='U'){//统计朝上硬币的个数
				ans++;
			}
		}
		if(ans%2==1){//判断
			cout<<"YES\n";
		}else{
			cout<<"NO\n";
		}
	}
	return 0;
} 
```

---

## 作者：keep_shining (赞：0)

个人建议评橙。

## 思路：

我们用 $U$ 表示正面朝上，用 $D$ 表示正面朝下。

我们观察发现，选择时会出现以下几种情况：

- 全是 U，正面数量减少了三个 `UUU -> DD`。

- 两边是 D，正面数量加了一个 `DUD -> UU`。

- 两边有一个 D，正面数量减少一 `DUU -> UD` 或 `UUD -> DU`。

- 两枚硬币，正面数量减少一（很显然，取走了一个正的）。

于是我们发现，无论怎么操作，正面朝上的硬币数量都会增加或减少一个奇数，也就是说每次正面朝上硬币的数量的奇偶性都会发生变化，而变化两次就相当于没变化，于是我们得出结论：只有初始时**正面朝上的的数量**是**奇数**时，先手才能获胜。



## AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s; 
int main()
{
	cin>>t;
	while(t--)
	{
		int cnt=0;
		cin>>n>>s;
		for(auto i:s)if(i=='U')cnt++;//cnt统计正面朝上的硬币的数量
		cout<<((cnt&1)?"YES\n":"No\n");//如果正面朝上的数量是奇数则先手赢，否则后手赢
	}
	return 0;
}
```

---

## 作者：__galaxy_1202__ (赞：0)

### 很裸的一道博弈论题~~  
先放结论：**只有当 $U$ 的数量是奇数时，输出 $YES$，否则输出 $NO$。**  
## 思路：
首先胜利目标很显然，就是要想方设法让方向为 $U$ 的硬币数归 $0$。当硬币数 $\ge 3$ 时，设想下面几种情况：  
1. 俩 $D$ 夹着一 $U$，很明显可以发现，一顿操作后会增加一个 $U$，**奇偶变化**。
1. 俩 $U$ 夹着一 $U$，可以发现，一顿操作后会减少三个 $U$，**奇偶依然变化**。
1. 一 $U$ 一 $D$ 夹着一 $U$，可以发现，一顿操作后会减少一个 $U$，**奇偶又双叒叕发生变化**。  

总结：硬币数 $\ge 3$ 时，奇偶一定发生变化。   

其他情况则更好想，当硬币数 $\ge 2$ 时，设想下面几种情况：  
1. 一 $D$ 一 $U$，很明显可以发现，一顿操作后会减少一个 $U$，**奇偶变化**。
1. 俩 $U$，可以发现，一顿操作后会减少一个 $U$，**奇偶依然变化**。  

一个就不用说了，直接胜利，所以得出结论：**每次操作都是**会让 $U$ 的个数的奇偶发生变化。  
学过小学的人都知道，**变化两次等于没变**，所以显然的，这样就可以得到开头的结论了。  

### **下面给出代码：**
```cpp
#include <iostream>
using namespace std;
int t, n, cnt;
char c;
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        cnt = 0;
        while (n--) 
        {
            cin >> c;
            if (c == 'U') cnt++;
        }
        if (cnt & 1) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
```

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1972B)

观察可发现，对于一枚正面朝上的硬币，如果左右两边都是正面朝上或正面朝下的硬币，那么把这枚硬币翻面之后左右两边的硬币翻面，正面朝上的硬币数减 $3$ 或 加 $1$；如果左右两边一个是正面朝上一个是正面朝下的硬币，那么这枚硬币翻面之后正面朝上的硬币数就减 $1$。

现在叫先手为 A，后手为 B，A 与 B 都执行完之后为一回合。

根据上文，可以发现每一回合结束后正面朝上的硬币的数量奇偶性不变，因为每一回合减去的数量都是偶数。又发现，如果到最后有 $3$ 个连在一起的正面朝上的硬币时，操作的人就赢了。由于奇偶性每回合结束后不变，所以如果 A 要赢，那么最后在操作前的数量一定为 $3$，$3$ 是奇数，所以初始时正面朝上的硬币的数量也得为奇数 A 才赢，否则 B 赢。

# CODE:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
int n;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int sum=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			char ch;
			cin>>ch;
			if(ch=='U') sum++;
		}
		if(sum&1) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：ThySecret (赞：0)

## Solution

一道博弈题，从操作的性质方面入手。

对于依次操作的位置，受到影响的就是其两边的硬币，无非分为以下几种情况：

- 两边都是 U，删去元素后两边都变成 D，U 的个数少了三个（包括操作的那一个）。
- 一边是 U，一边是 D，操作后 U 的个数少了一个。
- 两边都是 D，操作后 U 的个数增加了一个。

不难发现无论怎么操作，U 的个数的奇偶性始终不会改变。对于最后一种操作，如果 U 的个数便为 $0$，那么游戏结束。

我们可以统计出初始状态 U 的个数，如果 U 为奇数，则 Alice 获胜，否则 Bob 获胜。

## AC Code

```c++
void solve()
{
      int res = 0;
      cin >> n >> s + 1;
      for (int i = 1; i <= n; i ++)
            res += s[i] == 'U';
      cout <<( (res & 1) ? "YES\n" : "NO\n");
}
```

---

## 作者：Infinite_Loop (赞：0)

# CF1972B
## 题意
有 $n$ 枚硬币围成的圆圈，有的朝上，有的朝下。Alice 和 Bob 在玩一个博弈游戏，Alice 是先手。

轮到某个人时，玩家需要选出一枚正面朝上的硬币，取出这枚硬币并反转相邻的两枚硬币。当剩余硬币的数量小于等于 $2$，则不再反转。当轮到某个人时，已经没有正面朝上的硬币，那么这位玩家就输了。

问双方都以最优方式下棋，谁会赢呢？如果是 Alice 赢，输出 ```YES```，否则输出 ```NO```。
## 思路
本题很明显是找规律题。

我们可以考虑所有的情况：

- ```UUU -> DD```，正面朝上的硬币数量减少 $3$。
- ```UUD -> DU```，正面朝上的硬币数量减少 $1$。
- ```DUU -> UD```，正面朝上的硬币数量减少 $1$。
- ```DUD -> UU```，正面朝上的硬币数量增加 $1$。
- 两枚硬币时，显然正面朝上的硬币减少 $1$。

我们发现，不管每次怎么操作，正面朝上的硬币数量总是减少奇数个。

因为 Alice 是先手，所以只有当一开始正面朝上的硬币数量为奇数，她才能赢。

综上，我们只要一开始统计字符串中 ```U``` 的数量，判断是否为奇数，是输出 ```YES```，否则输出 ```NO```。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s; 
int main(){
	cin>>t;
	while(t--){
		int cnt=0;
		cin>>n>>s;
		for(int i=0;i<s.size();i++)
			if(s[i]=='U')cnt++;
		if(cnt%2==1)cout<<"YES"<<'\n';
		else cout<<"NO"<<'\n';
	}
	return 0;
}
```

---

## 作者：yyz1005 (赞：0)

赛时猜歌结论直接创过去了，难蚌。

注意到对于相邻的三项进行一次操作，三个位置的是否为 $1$ 的变化之和为 $3$ 个 $-1$ 或 $1$，由此，答案是与初始状态装 `u` 的数量有关的。

容易发现，奇数为 `YES`，偶数为 `NO`。

[Code](https://codeforces.com/contest/1972/submission/258870382)

---

## 作者：wly09 (赞：0)

# 题意简述

桌子上有 $n$ 枚硬币围成的圆圈，每枚硬币要么朝上，要么朝下。

在每次操作中，玩家选择一枚正面朝上的硬币，取出硬币并翻转与其相邻的两枚硬币。如果（操作前）只剩下两枚硬币，则取出一枚，另一枚不翻转（因为会翻转两次）。如果（操作前）只剩下一枚硬币，则不会翻转任何硬币。如果（操作前）没有正面朝上的硬币，玩家就输了。

如果两人都以最佳方式下棋，判定先手是否必胜。

# 做题历程

乍一看可能没有思路，不妨先打个暴力：
+ 若桌上没有正面朝上的硬币，先手必输；
+ 若操作后的所有状态都是“先手必胜”，这个状态是“先手必输”；
+ 若操作后的所有状态有“先手必输”，这个状态是“先手必胜”。

实际上这可能也是博弈论的常见暴力思路。

暴力打表后，容易发现，“先手必输”当且仅当当前状态下偶数个硬币正面朝上。

考虑证明（实际上赛时不用想这么多，这里只是思路）：

若桌上没有正面朝上的硬币（规定的失败状态），显然正面朝上硬币的个数为偶数（$0$）。

我们注意到每次的操作一定会改变正面朝上硬币个数的奇偶性，那么，以上结论容易被证明了。

# AC Code

```cpp
#include <iostream>
using namespace std;

int n;
char coins[120];

void solve() {
	cin >> n >> coins;
	int cnt = 0;
	for (int i = 0; i < n; ++i)
		if (coins[i] == 'U') ++cnt;
	cout << (cnt & 1? "Yes\n": "No\n");
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：Resstifnurv (赞：0)

### CF1972B 题解
[题目传送门（谷）](https://www.luogu.com.cn/problem/CF1972B)

---

当我们每次操作的时候，有以下三种情况：

- `U` 的两侧都是 `D`，此时有 `DUD` → `UU`，`U` 的数量 $+1$；
- `U` 的两侧 `D` 与 `U` 各有一个，此时有 `DUU` → `UD`，`U` 的数量 $-1$；
- `U` 的两侧都是 `U`，此时有 `UUU` → `DD`，`U` 的数量 $-3$；

可以发现每次操作 `U` 的个数必然变化奇数个，也就是每次操作 `U` 的数量必然奇数变偶数，偶数变奇数。而最后失败的局面下 `U` 个数为 $0$ 个，是个偶数，所以我们发现谁先手操作时 `U` 的数量为奇数个，他必不可能输，即必胜，反之亦然。

代码：
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int T,n;
char s[110];
int cnt=0;

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%s",&n,s+1);
		cnt=0;
		for(int i=1;i<=n;i++) cnt+=(s[i]=='U');
		if(cnt&1) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：破壁人罗辑 (赞：0)

## 题目大意

$n$ 枚硬币排成环，其中有 $m$ 枚是朝上的，Alice 和 Bob 轮流选取一枚朝上的硬币取走并将它两边的硬币翻转，无法操作时输掉游戏。问谁能赢。

## 解题思路

每次翻转操作都会进行两次，不影响 $m$ 的奇偶性。而每次取走硬币都会让 $m$ 奇偶性改变。所有只要 $m$ 为奇数则先手必胜，否则后手必胜。

## AC 代码
### C++
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;scanf("%d",&T);
    while(T--){
		int n;scanf("%d",&n);
        bool t=1;
		while(n--){
			char c=getchar();
            while(c!='U'&&c!='D')c=getchar();
			t=c=='U'?!t:t;
		}
		puts(t?"NO":"YES");
	}
	return 0;
}
```
### Python
```python
t=int(input())
for T in range(t):
    n=int(input())
    s=input()
    m=False
    for i in range(n):
        if s[i]=='U':
            m=not m
    if m:
        print('YES')
    else:
        print('NO')
```

---


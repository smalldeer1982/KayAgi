# 「MXOI Round 2」游戏

## 题目描述

小 C 和小 D 正在玩一款蒸蒸日上的游戏。

这款游戏共有 $3$ 种手牌：杀、闪、斩。他们的用途分别如下：

- 杀：对对方使用，对方需要使用一张**闪**，否则对方输掉游戏；**或**回应对方的**斩**；

- 闪：回应对方的**杀**；

- 斩：对对方使用，对方需要使用一张**杀**，否则对方输掉游戏。

玩家在每使用一张牌后，都需要弃掉该使用的牌。

从小 C 开始，每个回合依次属于小 C 和小 D。在玩家的回合内，该玩家可以出**任意**张**杀**和**斩**，对方需要做出对应的回应。当然，玩家也可以不出牌，直接进入对方的回合。

现在，小 C 共有 $c_1$ 张杀、$c_2$ 张闪、$c_3$ 张斩，小 D 共有 $d_1$ 张杀、$d_2$ 张闪、$d_3$ 张斩，**双方都知道对方的手牌**。你需要求出，双方在都进行最优策略的情况下，游戏的结果会如何。

## 说明/提示

#### 【样例解释 #1】

对于第一组数据，小 C 可以先出一张斩，并在小 D 回应一张杀后再出一张斩。此时小 D 的杀用完了，无法做出回应，输掉了游戏。

#### 【样例 #2】

见附加文件中的 `game/game2.in` 与 `game/game2.ans`。

#### 【数据范围】

对于 $100\%$ 的数据，$1 \le T \le 10^5$，$0 \le c_1,c_2,c_3,d_1,d_2,d_3 \le 10^9$。

|测试点编号|特殊性质|
|:---:|:---:|
|$1\sim3$|保证 $c_3=d_3=0$|
|$4\sim6$|保证 $c_1=d_2$ 且 $c_2=d_1$|
|$7\sim10$|无|

## 样例 #1

### 输入

```
3
3 1 4 1 5 9
1 1 4 5 1 4
5 2 1 2 6 3```

### 输出

```
C
D
E```

# 题解

## 作者：Coffee_zzz (赞：22)

### 分析

简单模拟。

由于小 C 先手，我们首先分析小 C。

如果小 C 可以用杀或斩秒掉小 D，那么直接秒就行。

若 $c_1 \gt d_2$ 或 $c_3 \gt d_1$，则直接输出 `C`。

如果不满足 $c_1 \gt d_2$ 或 $c_3 \gt d_1$，由于双方都是以最优策略进行游戏的，所以小 D 一定不会再给小 C 机会了，所以小 C 没有胜利的可能了，他能做的只有把所有的斩都出掉，让小 D 的杀少一些，而小 C 的杀需要留着，应对小 D 的斩。此时小 D 的杀的数量为 $d_1-c_3$。

我们再来分析小 D。

如果小 D 可以用杀或斩秒掉小 C，那么也直接秒就行。

若 $d_1-c_3 \gt c_2$ 或 $d_3 \gt c_1$，则直接输出 `D`。

如果不满足 $d_1-c_3 \gt c_2$ 或 $d_3 \gt c_1$，由于双方都是以最优策略进行游戏的，所以小 D 也没有机会胜利了。此时双方平局，输出 `E`。

### Code

```c++
#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	int T,c1,c2,c3,d1,d2,d3;
	cin>>T;
	while(T--){
		cin>>c1>>c2>>c3>>d1>>d2>>d3;
		if(c1>d2) puts("C");
		else if(c3>d1) puts("C");
		else if(d3>c1) puts("D");
		else if(d1-c3>c2) puts("D");
		else puts("E");
	}
	return 0;
}
```

---

## 作者：andyli (赞：8)

小 C 先手，则先判断小 C 能否通过杀或斩赢。如果小 C 无法赢，则要出斩消耗对方的杀，没有必要出杀。然后判断小 D 能否通过杀或斩赢，如果小 C、小 D 均无法赢则为平局。  

```cpp
int main() {
    multipleTests([&] {
        dR(u32, c1, c2, c3, d1, d2, d3);
        if (c1 <= d2 && c3 <= d1) { // 小 C 无法赢
            d1 -= c3; // 小 C 用斩消耗对方的杀
            if (d1 <= c2 && d3 <= c1) // 小 D 无法赢
                writeln('E');
            else
                writeln('D');
        }
        else
            writeln('C');
    });
    return 0;
}
```

---

## 作者：Dream__maker (赞：7)

## 题意
-  “杀” 回应 “斩” 。
-  “闪” 回应 “杀” 。
## 分析
由于小 C 先出牌，所以做出如下分析：

1. 小 C 赢的条件

   - 他的 “斩” 多于对方的 “杀”。
   - 他的 “杀” 多于对方的 “闪”。
2. 小 D 赢的条件 （在小 C 没赢的情况下）

   - 他的 “斩” 多于对方的 “杀”。
   - 他的 “杀” 多于对方的 “闪” 和 “斩” 的总和，因为他不仅要 “杀” 光对方的 “闪” ，还要回应对方的 “斩”。
3. 其他情况下平局
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
struct card{  //定义结构体 card
	int x,y,z;  // x 表示闪， y 表示杀， z 表示斩 
};
card c,d; //这里 c 表示小 C ，d 表示小 D 
int n;
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) {  //多组数据计算 
		scanf("%d %d %d",&c.x,&c.y,&c.z);
		scanf("%d %d %d",&d.x,&d.y,&d.z);
		if(c.x>d.y||c.z>d.x) cout<<"C"<<endl; //小 C 赢 
		else if(d.x>c.y+c.z||d.z>c.x) cout<<"D"<<endl; //小 D 赢 
		else cout<<"E"<<endl; //平局 
	}
	return 0;
}
```


---

## 作者：卷王 (赞：7)

## 题目大意

有三种手牌：杀、闪、斩。杀克斩，闪克杀。你知道两个人分别有多少杀、闪、斩，请问 **在两人都进行最优策略的情况下** 最终谁会赢。

## 大体思路

总评：思维中等，代码短，一道贪心好题。

读题就可以发现，斩就是老大，杀是老二，闪是老三。因为出斩永远是主动的，不可能是被动的；杀虽然有可能是主动的，但是也有可能是克制斩；闪就非常的被动了，出闪的唯一目的就是克制杀。

所以，考虑贪心，我们让小 C 先出斩，如果无法把对方杀死，就直接把回合转给对方。因为斩用光了也没有事，无论对方怎么出，都不用出斩来克制对方。而如果把杀和斩一次性都用完，如果对方出斩，就无法出牌回应，就输掉了。

小 D 也是这样操作。

如果一个轮回过去两人都没有输，那么就依次出杀。

为什么？因为两人的斩都出完了，就没有任何的牌对杀构成威胁。杀就是老大了。如果某个人杀的数量比另一个人的闪的数量大，那么这个人就赢了。

最后如果两人还是没有分出上下，那么表示两人都只剩下闪了。在两人都没有杀的情况下出闪就没有任何意义了，于是，答案就是平局。

代码如下：

```cpp
#include <stdio.h>

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int T, a1, b1, c1, a2, b2, c2;
int a[1000007];

//c 用 a 缓解
//a 用 b 缓解

int main() {
	T = read();
	while(T--) {
		a1 = read(), b1 = read(), c1 = read();
		a2 = read(), b2 = read(), c2 = read();
		if(c1 > a2 || a1 > b2) { printf("C\n"); continue; }
		a2 -= c1; c1 = 0; //小 C 用掉所有斩
		if(c2 > a1 || a2 > b1) { printf("D\n"); continue; }
		a1 -= c2; c2 = 0; //小 D 用掉所有斩
		if(a1 > b2) { printf("C\n"); continue; }
		if(a2 > b1) { printf("D\n"); continue; }
		printf("E\n");
	}
	return 0;
}
```

---

## 作者：二叉苹果树 (赞：4)

对于先手的小 C，如果能直接用杀和斩秒了小 D（$c_1>d_2$  或 $c_3>d_1$），那必然是小 C 获胜。反之，如果小 C 不能秒了小 D，那会优先用斩去消耗小 D 的杀，然后判断小 C 能否挡住小 D 的杀和斩。如果可以，则平局，否则小 D 获胜。

```cpp
#include <bits/stdc++.h>

int main()
{
    int t;
    std::cin >> t;
    while (t--)
    {
        int a, b, c, d, e, f;
        std::cin >> a >> b >> c >> d >> e >> f;
        if (a <= e && c <= d)
        {
            if (d - c <= b && a >= f)
                std::cout << "E\n";
            else
                std::cout << "D\n";
        }
        else
            std::cout << "C\n";
    }
} 
``` 

---

## 作者：WoodReal12 (赞：4)

本题只需简要分析即可。

## 算法分析
我们只要想出所有最优策略的情况就可以了：

1. 小 C 可以只用杀和斩杀掉小 D：小 C 胜

2. 小 C 不可以只用杀和斩杀掉小 D：尽量用斩去消耗小 D 的杀。若小 C 用完了所有的斩，检查小C能否抵挡小D剩下的斩和杀，可以则平局，否则小 D 胜。

小 D 同理。
这样就可以得出最终的代码了。

## 代码

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int t;
int c1,c2,c3,d1,d2,d3;
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>c1>>c2>>c3>>d1>>d2>>d3;
        if(c1<=d2&&c3<=d1){//无法杀小D
            if(d1-c3<=c2&&c1>=d3)
                cout<<"E"<<endl;
            else
                cout<<"D"<<endl;
        }
        else//可以杀小D
            cout<<"C"<<endl;
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/123101531)

---

## 作者：Cloud_Umbrella (赞：3)

## 分析

这是一个简单的博弈游戏，结局共有三种：小 C 赢、小 D 赢、平局。结局只可能是这三者中的一个。

第一轮较量（$1$）：首先，小 C 是先手，他如果有“杀”，肯定要先出（并没有限制），而小 D 如果有“闪”，也必须要回牌。所以第一轮较量就是看到底是小 C 的“杀”多还是小 D 的“闪”多。

第一轮较量（$2$）：其次，如若小 C 的“斩”多于小 D 的“杀”，胜者也是小 C。

第二轮较量：如果小 C 在第一轮并没有赢小 D，那么小 D 就会发起跟小 C 一样的进攻。所以在第一轮，小 C 会尽可能多出“斩”用以消耗小 D 的“杀”。

最后，当第一、二轮都没分出胜负时，那么就平局了。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
		int c1,c2,c3,d1,d2,d3;
		cin>>c1>>c2>>c3>>d1>>d2>>d3;
		if(c1>d2 || c3>d1) cout<<"C\n";//第一轮较量
		else if(d3>c1 || d1-c3>c2) cout<<"D\n";//第二轮较量
		else cout<<"E\n";//平局
	}
	return 0;
}
```

---

## 作者：Lizj (赞：3)

## 分析

由于双方都进行最优策略，所以有几个结论：

1. 当对方出斩时，如果有杀一定会出杀回应。

1. 当对方出杀时，如果有闪一定闪。

得出结论后，根据手牌性质找规律：

斩：只能在自己回合时对对方使用，此时对方需要用杀应对，所以出斩不会使情况更坏。即对于小 C 与小 D 中任何一人，出斩都不会使自己处于劣势。

闪：只能被动使用，当对方出杀时使用。

杀：可以在自己回合使用，也可以应对对方的斩。

根据以上规律，可以得出结论：

- 双方在有斩时必出斩。

- 当自己杀的数量比对方闪少时，直接进入对方的回合。

- 当自己斩的数量比对方杀多或杀的数量比对方闪多，自己获胜。

- 当牌只剩闪时，平局。

按分析模拟即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int c1,c2,c3,d1,d2,d3;
		cin>>c1>>c2>>c3>>d1>>d2>>d3;
		if(c3>d1)
			cout<<'C'<<endl;
		else{
			d1-=c3;
			c3=0;
			if(c1>d2)
				cout<<'C'<<endl;
			else{
				if(d3>c1)
					cout<<'D'<<endl;
				else{
					c1-=d3;
					d3=0;
					if(d1>c2)
						cout<<'D'<<endl;
					else
						cout<<'E'<<endl;
				}
			}
		}
	}
	return 0;
}
```


---

## 作者：Ferm_fire_yu (赞：2)

小 C 先手，如果他的杀的数量大于小 D 闪的数量或者斩的数量大于小 D 杀的数量就可以先手秒杀，则此时小 C 必胜，若无法秒杀则小 C 要想办法获得平局，就会用斩尽量消耗小 D 的杀，如果成功让小 D 无法后手秒杀就平局，否则小 D 获胜。
```cpp
#include <bits/stdc++.h>
using namespace std;

int c[10],d[10],T;
int main(){
	cin>>T;
	while(T){
		T--;
		scanf("%d%d%d%d%d%d",&c[1],&c[2],&c[3],&d[1],&d[2],&d[3]);
		if(c[1]>d[2]||c[3]>d[1]){
		//	cout<<"C"<<endl;
			printf("C\n");
		}else if(c[1]>=d[3]&&c[2]>=d[1]-c[3]){
			printf("E\n");
		}else if(d[1]>c[2]||d[3]>c[1]){
			printf("D\n");
		}else printf("E\n");
	}
	return 0;
}
```


---

## 作者：FS_qwq (赞：2)

## 题目大意

有三种牌：

* **杀**：如果你出杀，那么对方就要出闪，否则对方就输掉了游戏。

* **闪**：对方出杀，那么你就要出闪，否则你就输掉了游戏。

* **斩**：如果你出斩，那么对方就要出杀，否则对方就输掉了游戏。

现在小 C 和小 D 正在玩这个游戏，现在给定两个人杀、闪、斩三种牌的数量，并且双方出牌都是最优的情况下，求出谁会赢。

## 题目解答

我们假设小 C 有 $a$ 张杀、$b$ 张闪、$c$ 张斩，小 D 有 $d$ 张杀、$e$ 张闪、$f$ 张斩。

**小 C 赢的情况**：

如果 $c>d$ 或 $a>e$，就是说如果小 C 斩的数量比小 D 杀的数量多或小 C 杀的数量比小 D 闪的数量多，那么根据题目可得，小 C 赢。

**小 D 赢的情况**：

如果小 C 尽量多出斩，那么消耗了小 D 大量的杀，那么如果现在小 D 的杀比小 C 的闪多，小 D 就赢了，这就是 $d-c>b$，即小 D 杀的数量减去小 C 斩的数量大于小 C 闪的数量。

如果 $f>a$，即小 D 的斩的数量比小 C 杀的数量要多，那么根据题目可得，小 D 赢。

**平局的情况**：

如果不满足小 C 赢的情况和小 D 赢的情况，那么就是平局。

## 代码

代码比较简单，把上面的情况判断一遍，就能知道谁赢了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,d,e,f,q;
int main(){
	cin>>n;
	int i;
	for(i=1;i<=n;i++){
		cin>>a>>b>>c>>d>>e>>f;
		q=d-c;
		if(c>d||a>e)cout<<"C"<<endl;//小 C 赢
		else if(q>b||f>a)cout<<"D"<<endl;//小 D 赢
		else cout<<"E"<<endl;//平局
	}
	return 0;
}
```


---

## 作者：Double_Light (赞：1)

容易发现，如果前两个回合没有人赢，那么游戏结果一定是平局。原因很简单，如果小 C 能用杀或斩赢得游戏，那么第一回合他就会获得胜利；同理，如果小 D 能用杀或斩赢得游戏，那么第二回合他就会获得胜利。

接下来看看前两个回合他们能赢的条件：

对于第一回合，如果小 C 杀的数量大于小 D 闪的数量，或是小 C 斩的数量大于小 D 杀的数量，那么小 C 赢得游戏。

对于第二回合，如果小 D 斩的数量大于小 C 杀的数量，那么小 D 赢得游戏。如果小 D 杀的数量减掉小 C 斩的数量大于小 C 闪的数量（因为如果小 D 杀的数量比小 C 闪的数量大，小 C 会在第一回合用所有的斩消耗掉小 D 的杀），那么同样小 D 赢得游戏。

否则两人平局，因为如果有能够继续攻击死对方的牌，他们早就在前两个回合出完了。

最后放上代码：

```cpp
#include<iostream>
using namespace std;
int t,a,b,c,d,e,f;
int main(){
	cin>>t;
	while(t--){
		cin>>a>>b>>c>>d>>e>>f;
		if(a>e)cout<<"C\n";
		else if(c>d)cout<<"C\n";
		else if((d-c)>b)cout<<"D\n";
		else if(f>a)cout<<"D\n";
		else cout<<"E\n";
	}
	return 0;
}
```


---

## 作者：zhu_wen (赞：1)

# 主要思路
本题为小 C 先手，如果小 C 能够秒了小 D 那么小 C 获胜。
有两个秒的方法。
### 方法
- 杀大于闪。
- 斩大于杀。

如果小 C 秒不了小 D 那么小 D 反过来秒小 C 通过同样的方法。

**但注意，因为小 C 先手，通过斩来消耗了小 D 的杀，因此小 D 的杀只有——小 D 的杀减去小 C 的斩。**

因为我们是最优策略，如果都互相秒不了，那么为平局。
 
## 代码
```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fi first
#define se second
#define re register
#define swap(a, b) a ^= b, b ^= a, a ^= b
#define pb push_back
#define all(x) x.begin(), x.end()
#define fst                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int Max = 1e3 + 5;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

inline int read()
{
    int x = 0;
    bool f = true;
    char c = getchar();
    while (c < 48 || c > 57)
    {
        if (c == '-')
            f = false;
        c = getchar();
    }
    while (c >= 48 && c <= 57)
        x = (x << 3) + (x << 1) + c - 48, c = getchar();
    return f ? x : -x;
}
inline void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}
inline void wsp(int x) { write(x), putchar(' '); }
inline void wel(int x) { write(x), putchar('\n'); }

int t;
int c1, c2, c3, d1, d2, d3;

signed main()
{
    fst;
    cin >> t;
    while (t--)
    {
        cin >> c1 >> c2 >> c3 >> d1 >> d2 >> d3;
        if (c1 > d2)   //小 C 的杀>小 D 的闪
            cout << "C" << endl;
        else if (c3 > d1) //小 C 的斩>小 D 的杀
            cout << "C" << endl;
        else if (d3 > c1) //小 D 的斩>小 C 的杀
            cout << "D" << endl;
        else if (d1 - c3 > c2)//小 D 的杀>小 C 的闪
            cout << "D" << endl;
        else //都不满足
            cout << "E" << endl;
    }
    return 0;
}
```


---

## 作者：jxbe6666 (赞：1)

### 题意
小 C 和小 D 正在玩一款蒸蒸日上的游戏。

这款游戏共有 $3$ 种手牌：杀、闪、斩。他们的用途分别如下：

- 杀：对对方使用，对方需要使用一张**闪**，否则对方输掉游戏；**或**回应对方的**斩**；

- 闪：回应对方的**杀**；

- 斩：对对方使用，对方需要使用一张**杀**，否则对方输掉游戏。

玩家在每使用一张牌后，都需要弃掉该使用的牌。

从小 C 开始，每个回合依次属于小 C 和小 D。在玩家的回合内，该玩家可以出**任意**张**杀**和**斩**，对方需要做出对应的回应。当然，玩家也可以不出牌，直接进入对方的回合。

现在，小 C 共有 $c_1$ 张杀、$c_2$ 张闪、$c_3$ 张斩，小 D 共有 $d_1$ 张杀、$d_2$ 张闪、$d_3$ 张斩，**双方都知道对方的手牌**。你需要求出，双方在都进行最优策略的情况下，游戏的结果会如何。

-----

### 思路
当 $c_1>d_2$ 或 $c_3>d_1$ 时，小 C 获胜；  
当小 C 不能获胜，且 $d_1>c_2+c_3$ 或 $d_3>c1$ 时，小 D 获胜。

其他情况皆为平局。


-----

### 代码
-----
```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll N = 1e6 + 5;
const ll M = 1e3 + 5;
ll c1,c2,c3,d1,d2,d3,t;
inline ll read() {
	ll x = 0, y = 1;
	char c = getchar();
	while (!isdigit(c)) {
		y = (c == '-') ? -1 : 1;
		c = getchar();
	}
	while (isdigit(c)) {
		x = x * 10 + c - 48;
		c = getchar();
	}
	return x * y;
}
int main() {
	t=read();
	while(t--){
		c1=read(),c2=read(),c3=read();
		d1=read(),d2=read(),d3=read();
		if(c1>d2 || c3>d1){
			cout<<"C\n";
			continue;
		}
		d1-=c3;
		if(d1>c2 || d3>c1){
			cout<<"D\n";
			continue;
		}
		cout<<"E\n";
	}

	return 0;
}
```


---

## 作者：Special_Tony (赞：1)

[题目传送门](/problem/P9596)
# 思路
这题的平局条件是什么？平局的条件就是小 C 和小 D 都没有杀和斩了。我们要想让游戏尽可能简单一点（也就是尽可能早点结束），就是让小 C 把能出的牌一下子出完，小 D 也是，这样一回合之后如果还没分出胜负，那就是平局。

首先，我们可以让小 C 把 $c3$ 张斩都出完，如果 $d1<c3$，则小 C 就赢了，游戏结束。否则 $d1$ 就要减去 $c3$ 以应对小 C 的所有斩。然后，如果小 C 的杀比小 D 的闪多，那么小 C 就赢了，游戏结束。否则，小 C 的杀就不出，因为他还要应对小 D 的斩呢！

小 C 的回合结束了，小 D 的回合也同理。如果小 D 的回合结束后还没分出胜负，那就是平局了。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int a1, a2, a3, b1, b2, b3, t;
int main () {
	cin >> t;
	while (t --) {
		cin >> a1 >> a2 >> a3 >> b1 >> b2 >> b3;
		if (b1 < a3 || b2 < a1) {
			cout << "C\n";
			continue ;
		}
		b1 -= a3;
		if (a1 < b3 || a2 < b1) {
			cout << "D\n";
			continue ;
		}
		cout << "E\n";
	}
	return 0;
}
```

---

## 作者：wcop114514 (赞：1)

**题目分析**

小 C 先手，判断能否秒了小 D（$c_{1}>d_{2}$ 或 $c_{3}>d_{1}$）若能小 C 嬴。

若不能判断能否抵挡小 D 的攻击，若能，则平局，否则小 D 嬴。

给各位大佬奉上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    multipleTests([&] {
        dR(u32, c1, c2, c3, d1, d2, d3);
        if (c1 <= d2 && c3 <= d1) { 
            d1 -= c3; 
            if (d1 <= c2 && d3 <= c1) 
                writeln('E');
            else
                writeln('D');
        }
        else
            writeln('C');
    });
    return 0;
}

---

## 作者：sbno333 (赞：1)

这道题是一道贪心的题，由于双方抽不了牌，所以不难。

对于小 C，如果能干掉对方就干掉对方，干不掉就要想办法求和，他唯一能做的是出对不输没有啥贡献的斩，将对方的杀耗掉，就有可能让对方的杀干不掉自己，然后是小 D 的贪心，将能出的都出了，如果干的掉小 C，就是他赢，否则平。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c,d,e,f,t;
	cin>>t;
	while(t--){
		cin>>a>>b>>c>>d>>e>>f;
		cout<<(a>e||c>d?"C":(d-c>b)||f>a?"D":"E")<<endl;}
	}
```

---

## 作者：zhang_Jimmy (赞：0)

# 思路：

由于本题**先手一次可以出多张牌且可以同时出不同数量的杀和斩**，所以我们可以先手把杀和斩都出掉，最大程度消耗对面的牌。如果对面的闪和杀的数量低于我们的杀和斩时，我们就可以赢下这局比赛。

如果小 C 和小 D 把手上的杀和斩都出完了游戏都没有分出胜负，那么就平局了（因为两边都没有杀和斩了）。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int c[4], d[4], t;
int main(){
	cin >> t;
	while(t --){
		cin >> c[1] >> c[2] >> c[3] >> d[1] >> d[2] >> d[3];
		d[1] -= c[3];
		d[2] -= c[1];
		if(d[1] < 0 || d[2] < 0){
			cout << "C\n";
			continue;
		}
		c[1] -= d[3];
		c[2] -= d[1];
		if(c[1] < 0 || c[2] < 0){
			cout << "D\n";
			continue;
		}
		cout << "E\n";
	}
}

```


---

## 作者：Xswarx_XL (赞：0)

# 题目分析

小 C 的最优策略，要么先手秒掉对方，即自己的杀比对方的闪多，或者自己的斩比对方的杀多；要么赢不了，用斩先消耗对方的杀尽量求平手或被对方的回合秒掉。

小 D 的最优策略与小 C 同理，不过因为后手可能第一回合直接被秒，来不及用斩消耗对方的杀或秒了对方。

双方如果第一回合都赢不了对方，即视为平局。

# Code
```cpp
#include<iostream>
using namespace std;
long long T,c1,c2,c3,d1,d2,d3;
int main(){
	cin>>T;
	while(T--){
		cin>>c1>>c2>>c3>>d1>>d2>>d3;
		if(c1>d2||c3>d1){
			cout<<"C\n";
			continue;
		}
		if(d1>c2+c3||d3>c1){
			cout<<"D\n";
			continue;
		}
		cout<<"E\n";
	}
	return 0;
}
```

---

## 作者：liangbob (赞：0)

### P9586 题解

被除名的验题人题解。

#### 思路分析

模拟。

首先，如果小 C 的斩的数量大于小 D 的杀的数量，又或者小 C 的杀的数量大于小 D 的闪的数量，显然小 C 赢。

如果小 D 的斩的数量大于小 C 的杀的数量，显然小 D 赢。

但是如果小 D 的杀的数量大于小 C 的闪的数量，小 D 还不一定能赢。

因小 C 采用最优策略，那肯定是优先把对方的杀给消耗完，不然对自己有威胁。（因为杀有攻击性，而闪没有）

而小 C 只能靠斩来消耗对方的杀。所以，只有当小 D 的杀的数量减去小 C 斩的数量大于小 C 闪的数量时，小 D 才能赢。

如果谁都没赢，显然平局。

#### 代码

```cpp
#include <iostream>

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int c1, c2, c3, d1, d2, d3;
		cin >> c1 >> c2 >> c3 >> d1 >> d2 >> d3;
		if(c3 > d1 || c1 > d2)
		{
			cout << "C" << endl;
			continue; 
		}
		if(d3 > c1)
		{
			cout << "D" << endl;
			continue;
		}
		d1 -= c3;
		if(d1 > c2)
		{
			cout << "D" << endl;
			continue;
		}
		cout << "E" << endl;
	}
    return 0;
}
```



---


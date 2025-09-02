# Swap Game

## 题目描述

Alice 和 Bob 正在玩一个关于数组 $a$ 的游戏，数组包含 $n$ 个正整数。Alice 和 Bob 轮流行动，Alice 先手。

在每一回合，玩家需要进行如下操作：

- 如果 $a_1 = 0$，该玩家输掉游戏，否则：
- 玩家选择某个 $i$，其中 $2 \leq i \leq n$。然后玩家将 $a_1$ 的值减少 $1$，并将 $a_1$ 与 $a_i$ 交换。

如果两位玩家都采取最优策略，判断谁会赢得游戏。

## 说明/提示

在第一个测试用例中，Alice 在她的回合只能选择 $i = 2$，使数组变为 $[1, 0]$。然后 Bob 也只能选择 $i = 2$，使数组变为 $[0, 0]$。由于 $a_1 = 0$，Alice 输掉了游戏。

在第二个测试用例中，玩家同样只能选择 $i = 2$。数组变化过程为：$[2, 1] \to [1, 1] \to [1, 0] \to [0, 0]$，Bob 输掉了游戏。

在第三个测试用例中，可以证明 Alice 有必胜策略。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2
1 1
2
2 1
3
5 4 4```

### 输出

```
Bob
Alice
Alice```

# 题解

## 作者：CE_Prince (赞：7)

### 题意简述

我们将 Alice 简称为 A ， Bob 简称为 B

有一个长度为 $n$ 的序列， A 和 B 轮流进行一种操作

当前操作者 $a_1-1$ 后与序列中 $a_2,a_3,a_4,......,a_n$ 中任意一个元素交换

如果当前操作者操作前 $a_1=0$ 则当前操作者输

### 思路：

因为 A 先手，所以 A 肯定会挑选 $a_2,a_3,......,a_n$ 中最小的数与 $a_1$ 交换。

因为 B 在操作前无法交换元素的位置， $a_2,a_3,......,a_n$ 中最小的元素就是 A 最小的操作次数。
所以如果 $a_2,a_3,......,a_n$ 中最小值严格小于 $a_1$ ，那么 A 赢，反之则 B 赢。

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,x;
bool flag;
int main()
{
	cin>>t;
	while(t--)
	{
		flag=false;
		cin>>n>>x;
		for(int i=2;i<=n;i++)
		{
			cin>>a;
			if(x>a)flag=true;
		}
		if(flag)cout<<"Alice"<<endl;
		else cout<<"Bob"<<endl;
	}
	return 0;
} 
```


---

## 作者：sunzz3183 (赞：4)

# CF1747C-Swap Game 题解

## 题意

Alice 和 Bob 在玩一种游戏。

Alice 先手，两人轮流操作。

游戏方式为：

1.如果 $a_1=0$，当前人输掉游戏，游戏结束。

2.将 $a_1-1$，然后与后面的 $a_2,a_3,...,a_n$ 之间选择一个数与 $a_1$交换。

## 思路

性质题。

因为 Alice 先手，那么她肯定会把 $2\sim n$ 中最小的数放到最前面，因为 Bob 无法替换最小值，这样 Alice 的操作次数，就是最小值的大小。如此，Bob 肯定也是这样操作。

那么当 $a_1$ 为最小值时，Alice 永远无法选择最小值，所以 Bob 的操作次数一定比 Alice 少，Bob 一定会赢。

如果后面存在比 $a_1$ **严格小**的数，那么 Alice 的操作次数一定比 Bob 少，Alice 一定会赢。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int T,n,x,a;
signed main(){
	T=read();
	while(T--){
		n=read();x=read();
		bool flg=0;
		for(int i=1;i<n;i++){
			a=read();
			if(a<x)flg=1;//严格小
		}
		if(flg)puts("Alice");
		else puts("Bob");
	}
	return 0;
}
```


---

## 作者：Silence_World (赞：2)

# 思路

一道很水的博弈论，首先我们看先手情况，能发现无论 $b$ 怎么换（后手称为      $b$），$a$ 只要找一个最小的数放上去，那在经过一番减后都为 0，也就是说无论 $b$ 一直选哪个数，只要 $a$ 一直把那个最小的数放上来，那 $b$ 每次肯定只能让那个数减，且 $b$ 没有选择空间，那 $b$ 该怎么赢呢？我们发现，$a$ 第一次减的一定是 $a_{1}$，也就是说，当后面所有数都大于或等于 $a_{1}$ 时，$b$ 肯定会一直换 $a_{1}$，即 $b$ 必胜，特判一下 $a_{1}$ 大于 $a_{i}$ 的情况就可以了。

# 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[100005]; 
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		bool fl=1;
		for(int j=2;j<=n;j++){
			if(a[1]>a[j]){
				cout<<"Alice"<<endl;
				fl=0;
				break;
			}
		}
		if(fl){
			cout<<"Bob"<<endl; 
		}
	} 
}
```


---

## 作者：luo_shen (赞：2)

诈骗题
## 题意简述
有一个序列长度为 $n$ 的序列 $a$，`Alice` 和 `Bob` 两人轮流操作，`Alice` 先手，将当前序列中的第一个数减 $1$，并可以选择当前序列中一个数交换（不能是当前序列中的第一个数），当一个人操作前，当前序列中的第一个数为 $0$，这个人就输了。问最后谁会赢。
## 题目分析
结论：两人每次操作交换的必是当前的 $a_1$，与除去 $a_1$ 后序列的最小值。
>证明：若 `Alice` 操作交换到的是序列中的次小值 $y$，，不是最小值 $x$，且 `Bob` 不取 $x$，那么她需要操作的使其变为 $0$ 的次数会由 $x$ 上升为 $\min(x+1,y)$；若 `Bob` 取 $x$ ，操作次数又 $x$ 上升为 $y$，操作步数增多，因此这样操作更劣，她会选择交换序列中最小值 $x$。同理可知，`Bob` 也会选择他操作时的序列中的最小值。

将除去 $a_1$ 后的序列 $a$，从小到大排好序。很明显，只有 `Alice` 的第一步操作会被限制减少的是 $a_1$，两个人剩下的操作都会选择能选择的最小的数。这样数字相对与初始值减小的数最多只有三个。`Alice` 交换时可取序列中的最小值 $a_2$ 与 `Bob` 交换时序列中可能的最小值 $a_1-1$ 和 `Alice` 操作前可取序列中次小值 $a_3$。将 $\min(a_1-1,a_3)$ 与 $a_2$ 比较，若前者小，则 `Bob` 胜，反之 `Alice` 胜。需特殊处理 $n=2$ 情况。

## Code
```
int n,a[100100];
void solve(){
    read(n);
    for(int i=1;i<=n;i++){
        read(a[i]);
    }
    sort(a+2,a+n+1);//将除去a[1]以外的所有数排序
    if(n==2){//特判只有两个数情况，此时Bob没有其它数可选
        if(a[2]<=a[1]-1){
            puts("Alice");
        }
        else{
            puts("Bob");
        }
        return;
    }
    if(a[2]<=min(a[1]-1,a[3])){
        puts("Alice");
    }
    else{
        puts("Bob");
    }
}
```
## 题外话
为什么说这题诈骗题呢？因为我看到的第一眼，发现他是博弈论，以为要求 `SG函数`，想了五分钟就跑去看 `d` 了，然后就发生了一些很难受的事（详情请见[我的d题题解](https://www.luogu.com.cn/blog/luoshen0/solution-cf1747d)的题外话部分），做完后看了两分钟 `c` 思路就出来了，就很绷不住。

---

## 作者：Stars_visitor_tyw (赞：1)

## CF1747C Swap Game 题解
### 思路：
先手如果想要后手败，肯定会从剩下的数中挑一个最小值 $min$ 与 $a_1$ 交换，让 $a_1$ 尽量小，所以 $min$ 就是先手最小的操作次数，这时我们便可以得出结论：如果 $min<a_1$，则先手胜，反之则后手胜。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n, a1;
		bool flag=false;
		cin>>n>>a1;
		for(int i=2;i<=n;i++)
		{
			int a;
			cin>>a;
			if(a1>a)
			{
			    flag=true;
			}
		}
		if(flag==true)
		{
		    cout<<"Alice"<<endl;
		}
		else
		{
		    cout<<"Bob"<<endl;
		}
	}
	return 0;
} 

---

## 作者：zhangzinan1224 (赞：1)

把问题分成两种不同的情况。当 $a_1 > \min(a)$ 和当 $a_1=\min(a)$。

情况1：$a_1 > \min(a)$

$\texttt{Alice}$ 可以通过在她的回合中总是选择 $a$ 数组的最小元素来迫使 $\texttt{Bob}$ 总是减少最小元素。当 $\texttt{Bob}$ 不能做太多事情时，他要交换的所有其他元素都大于或等于 $\min(a)$。即使 $a$ 数组中存在多个最小值，在第一步中 $\texttt{Alice}$ 会从 $a_1$ 减少，因此在这种情况下$\texttt{Alice}$ 总是会赢。


情况2：$a_1 = \min(a)$

在这种情况下，$\texttt{Bob}$ 的最佳策略是总是选择数组中最小的元素，也就是 $a_1$。$\texttt{Alice}$ 总是在她的回合中交换大于 $a_1$ 的元素，因此在这种情况下 $\texttt{Bob}$ 总是赢。


### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,n)     for(int i=a;i<n;i++)
#define ll             long long
#define int            long long
#define pb             push_back
#define all(v)         v.begin(),v.end()
#define endl           "\n"
#define x              first
#define y              second
#define gcd(a,b)       __gcd(a,b)
#define mem1(a)        memset(a,-1,sizeof(a))
#define mem0(a)        memset(a,0,sizeof(a))
#define sz(a)          (int)a.size()
#define pii            pair<int,int>
#define hell           1000000007
#define elasped_time   1.0 * clock() / CLOCKS_PER_SEC



template<typename T1,typename T2>istream& operator>>(istream& in,pair<T1,T2> &a){in>>a.x>>a.y;return in;}
template<typename T1,typename T2>ostream& operator<<(ostream& out,pair<T1,T2> a){out<<a.x<<" "<<a.y;return out;}
template<typename T,typename T1>T maxs(T &a,T1 b){if(b>a)a=b;return a;}
template<typename T,typename T1>T mins(T &a,T1 b){if(b<a)a=b;return a;}


int solve(){
 		int n; cin >> n;
 		vector<int> a(n);
 		for(auto &i:a)cin >> i;
 		sort(a.begin() + 1,a.end());
 		cout << (a[0] > a[1] ? "Alice" : "Bob") << endl;
 return 0;
}
signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    #ifdef SIEVE
    sieve();
    #endif
    #ifdef NCR
    init();
    #endif
    int t=1;cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
```


---

## 作者：shinzanmono (赞：1)

~~这是我第一道赛时通过的CF题~~

看下题面我们可以知道两人追求的都是 $a_1$ 最小，但是交换不得不换，根据贪心，可以选取除了 $a_1$ 外最小的数，设这个数字为 $a_m$，进行反复交换，暴力交换的话，时间复杂度 $\Theta(t\max a_i)$，$t\leq2\cdot10^4,a_i\leq10^9$（有那么一丢丢超时）。

考虑优化，既然是每次都找最小的，那么一定在两轮过后，即 Alice 和 Bob 都操作一次后，$a_m, a_1$ 都自减。所以 $a_1 > a_m$ 时，必将最后在 Alice 结束操作时 $a_1 = 0$，所以 Bob 必输，反之 Bob 必胜。

附代码：

```cpp
#include <iostream>
#include <algorithm>
#include <limits> // 使用numeric_limits模板类
const int inf = std::numeric_limits<int>::max(); // 最大值
int main() {
    std::ios::sync_with_stdio(false); // 优化cin, cout
    int t, n;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        int a1, am = inf, x;
        std::cin >> a1;
        for (int i = 2; i <= n; i++) std::cin >> x, am = std::min(am, x); // 查找区间[2, n]最小值
        if (a1 > am) std::cout << "alice\n"; 
        else std::cout << "bob\n";// 比较最小值，得出结果
    }
}

```

---

## 作者：hmh100211 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1747C)

## 题意分析：

Alice 和 Bob 两个人在玩游戏，游戏规则如下：

给定一个长度为 $ n $ 的序列 $ a $，从 Alice 先开始，两人轮流操作。

每次操作：

- 将 $ a_1 $ 减 $ 1 $。

- 将减 $ 1 $ 后的 $ a_1 $ 与 $ a_2,a_3,\cdots,a_n $ 中的一个数交换。

获胜条件：如果一个人**操作前** $ a_1 $ 为 $ 0 $，那**另一个人**就赢了。

保证两个人的交换都是最优情况，问最后谁会赢？

数据范围都在 `int` 范围内，正常开 `int` 即可。

## 思路：

（为方便，以下将用 A 和 B 来代替 Alice 和 Bob）

首先因为 $ n \ge 2 $，所以 $ n=1 $ 的特殊情况可以不考虑。

我们可以先考虑 A 的策略。A 的目标是尽量使得 B 输，即交换后 $ a_1 = 0 $。为了达到这个目标，A 把 $ a_1 $ 减少 $ 1 $ 后应该与 $ a_2 $ 到 $ a_n $ 中最小的数进行交换，以确保 B 的选择空间受到限制。

基于上述观察，我们可以得到：若 A 将 $ a_1 $ 减少 $ 1 $ 后的数与比 $ a_1 $ 小的数交换后， B 无论如何选择，都至少有一次操作无法让第一个数变为 $ 0 $，从使而 A 获胜。

综上，我们就可以推出最后的结论：

若 $ a_2 $ 到 $ a_n $ 中有一个数小于 $ a_1 $ 时，A 有必胜策略。反之，若 $ a_2 $ 到 $ a_n $ 所有数都大于等于 $ a_1 $ 时，B 有必胜策略。

# AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[114514];
bool flag=0; //bool型变量记录 
int main() {
	scanf("%d",&t); //读入数据组数
	while(t--) {
		scanf("%d",&n); //读入序列长度
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]); //读入序列a
		for(int i=2;i<=n;i++) { //下标从2开始遍历a序列
			if(a[1]>a[i]) { //如果有一个数比第一个数小
				flag=1; //记录
				break; //跳出循环
			}
		}
		if(flag) //有一个数比第一个数小
			printf("Alice\n"); //Alice有必胜策略
		else //反之 
			printf("Bob\n"); //Bob有必胜策略
		flag=0; //重置变量 
	}
	return 0;
}
```

# [AC](https://www.luogu.com.cn/record/117831485)

---

## 作者：_Memory (赞：0)

## 一、题意简述

有一个长度为 $ n $ 的序列 $ a $，Alice 和 Bob 两人轮流完成一个操作。Alice 为先手。每个人可以将数列的第一个数减 $ 1 $，并将它与后面序列的一个数进行交换，如果一个人操作之前发现当前序列中的第一个数为 $ 0 $，这个人就输了。那么请问，最后谁会赢。

## 二、解题思路

这道题有点像小学奥数里的摸棋子，所以写起来也是非常容易的。首先，Alice 肯定会将 $ a $ 序列中最小的数与 $ a1 $ 进行交换，并且这个最小值就是 Alice 的操作次数。轮到 Bob 时，他是无法改变顺序的，但他也一定会采取跟 Alice 一样的方式转换。此时，如果 $ a1 $ 为最小值，Alice 就永远无法选择最小值，那 Bob 一定赢。反之，如果后面的数有严格小于 $ a1 $ 的，Alice 一定赢。

## 三、核心代码

```cpp
 int a,b[10010],n;
 cin>>n;
 bool qwq;
 while(n--){
   qwq=false;
   cin>>a;
   for(int i=1;i<=a;i++){
     cin>>b[i];
     if(b[1]>b[i]) qwq=1;
   }  
   if(qwq) cout<<"Alice"<<endl;
   else cout<<"Bob"<<endl; 
    }
```

---

## 作者：Fengyiwei1234 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1747C)

# 思路：博弈论

因为 Alice 是先手，所以为了使第一个变成零最快，他一定会让 ${a}_{1}$ 与之后最小的那个进行交换。

所以只需要考虑 ${a}_{1}$ 是否是最小的即可。

如果 ${a}_{1}$ 是最小的，那么 Bob 赢，否则 Alice 赢。

AC 代码：

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9;
int T,n,a[N];
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n;
        int minn=-1;bool flag=0;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            if(a[1]>a[i])flag=1;
        }
        if(flag)cout<<"Alice"<<endl;
        else cout<<"Bob"<<endl;
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/113244917)

---

## 作者：ZHANGyutao123 (赞：0)

## [CF1747C Swap Game ](https://www.luogu.com.cn/problem/CF1747C)

# 题目大意

给定一个长度为 $n$ 的正整数数组 $a$，两个人 Alice 和 Bob 轮流进行操作，每次操作选择一个 $2\leq i\leq n$，减少 $a_1$ 的值 $1$，并交换 $a_1$ 和 $a_i$ 的位置，直到 $a_1$ 变为 $0$。Alice 先手，两人都采用最优策略，求最后谁获胜。

# 解题思路

先分析一下题目的性质：

- 每个数只能交换一次，而且只能被交换到最前面；
- 游戏结束的条件是 $a_1=0$。

显然，Bob 在他的回合中只能通过交换 $a_{2...n}$ 中的数来影响 $a_1$ 的值，因为在 Alice 回合的时候 $a_1$ 已经不能变了。

因此，问题转化为，如果 $a_{2...n}$ 中有比 $a_1$ 大的数，则 Alice 可以把它交换到 $a_1$ 的位置上，从而减小 $a_1$ 使得 Bob 无法交换。

如果 $a_{2...n}$ 中不存在比 $a_1$ 大的数，则 Alice 没有办法避免 Bob 改变 $a_{2...n}$ 的值，最终 Bob 可以通过自己的操作使 $a_1$ 变为 $0$。

综上，若存在 $a_{2...n}$ 中的数大于 $a_1$，Alice 可以获胜，否则 Bob 取胜。

# 参考代码
```cpp
#include <iostream>
using namespace std;
int t, n, x, a;
bool alice_win;
int main() {
    cin >> t; // 读取测试数据组数
    while (t--) { 
        alice_win = false; // Alice 初始没有获胜
        cin >> n >> x; // 读取数组长度和第一个数 x
        for (int i = 2; i <= n; i++) { // 从第二个数开始读取
            cin >> a;
            if (x > a) { // 如果当前数比第一个数小
                alice_win = true; // Alice 可以把它交换到第一个位置取胜
            }
        }
        if (alice_win) { // 如果 Alice 获胜，则输出 Alice
            cout << "Alice\n";
        } else { // 否则 Bob 获胜，输出 Bob
            cout << "Bob\n";
        }
    }
    return 0;
}
```


---


# Circle Game

## 题目描述

Mike 和 Joe 正在玩石子，迈克先手。他们有 $n$ 堆大小为 $a_1 , a_2,\ldots,a_n$ 的石子，堆呈圆形排列。

玩家从第一堆开始，顺时针依次从一堆中取出一些正数的石头。如果一个玩家在回合中从第 $i$ 堆取石头，另一个玩家在下一轮从 $ ((i\bmod n) + 1) $ 堆取石头。

如果玩家在回合中无法取走任何石头（因为堆是空的），他就输了。

假设 Mike 和 Joe 都采取最优策略，那么谁会赢？

## 样例 #1

### 输入

```
2
1
37
2
100 100```

### 输出

```
Mike
Joe```

# 题解

## 作者：saixingzhe (赞：4)

# 思路
首先，如果 $n$ 是奇数，那一定 $\texttt{Mike}$ 赢，因为他只需要每次把石子拿空即可。因为到了第二轮，$\texttt{Joe}$ 变成了拿奇数编号的石头堆的人，而第一轮 $\texttt{Mike}$ 直接把第一堆石头全拿完， 就没得拿了， 也就输了。

其次，如果 $n$ 是偶数，$\texttt{Mike}$ 将一直拿奇数位置的石子，$\texttt{Joe}$ 一直拿偶数位置的石子，为了保证拿的次数尽可能的多，所以要保证每次拿的石子尽可能少，即每次都只取 $1$ 个。因此只需要找出最先被拿空的石子堆，也就是数组中的下标最靠前的最小值，判断如果它为奇数，则 $\texttt{Joe}$ 必胜，反之则 $\texttt{Mike}$ 必胜。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[100],n;
int main(){
    cin>>t;
    while(t--){
        int ans=1;
        cin>>n;
        for(int i=1;i<=n;i++)   cin>>a[i];
        if(n&1){//判断
            printf("Mike\n");
            continue;   
        }
        for(int i=1;i<=n;i++)   if(a[i]<a[ans]) ans=i;//寻找最先被拿空的石子堆
        if(ans&1)   printf("Joe\n");
        else    printf("Mike\n");   
    }
    return 0;
}
```

---

## 作者：saixingzhe (赞：2)

# 思路
首先，如果 $n$ 是奇数，那一定 Mike 赢，因为他只需要每次把石子拿空即可。因为到了第二轮，Joe 变成了拿奇数编号的石头堆的人，而第一轮 Mike 直接把第一堆石头全拿完，就没得拿了，Joe 也就输了。

其次，如果 $n$ 是偶数，Mike 将一直拿奇数位置的石子，Joe 一直拿偶数位置的石子，为了保证拿的次数尽可能的多，所以要保证每次拿的石子尽可能少，即每次都只取 $1$ 个。因此只需要找出最先被拿空的石子堆，也就是数组中的下标最靠前的最小值，判断如果它的下标为奇数，则 Joe 必胜，反之则 Mike 必胜。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[100],n;
int main(){
    cin>>t;
    while(t--){
        int ans=1;
        cin>>n;
        for(int i=1;i<=n;i++)   cin>>a[i];
        if(n&1){//判断
            printf("Mike\n");
            continue;   
        }
        for(int i=1;i<=n;i++)   if(a[i]<a[ans]) ans=i;//寻找最先被拿空的石子堆
        if(ans&1)   printf("Joe\n");
        else    printf("Mike\n");   
    }
    return 0;
}
```

---

## 作者：litachloveyou (赞：2)

这是一个很有趣的游戏，两个人轮流拿走一些石子。

------------
当轮到自己时，没有石头可以拿了，就说明输了。那么我们怎么确保自己能够尽量获得胜利呢？

------------
**注意到**如果是奇数堆石头时，两个人拿的石堆会发生变化。举个例子，假如说有三堆石头，那么第一个人拿的顺序就是一、三、二、一，第二个人拿的顺序就是二、一、三、二。所以有奇数堆石头时，两个人会轮流交换摸的石堆。这样我们就可以利用这个性质，第一个人拿的时候，直接把第一堆拿空，那么等到下次第二个人拿第一堆的时候，他就一定会输。

------------
如果是偶数堆呢？**那么他们拿的石堆不会变**，所以每个人一次就拿一块石头，尽量保证拿的次数多。可以直接比较他们两个人要拿的石堆中的最小个数，将所有的石堆都减去这个最小个数，再判断轮到每个人拿的时候，如果小于等于零了，那么这个人就会输。

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve()
{
    int n;
    scanf("%d", &n);
    vector<int>a(n + 1);
    int minm = 1e9 + 10, minj = 1e9 + 10;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        i & 1 ? minm = min(minm, a[i]) : minj = min(minj, a[i]);
    }
    if (n & 1)puts("Mike");//奇数情况，一定赢。
    else
    {
        int check = 0;
        for (int i = 1; i <= n; i++)
        {
            a[i] -= min(minm, minj);
            if (a[i] <= 0)
            {
                check = (i & 1);
                puts(!check ? "Mike" : "Joe");判断轮到谁没的拿。
                return;
            }
        }
    }
}
int main()
{
    int T = 1;
    scanf("%d", &T);
    while (T--)solve();
    return 0;
}
```


---

## 作者：Jadebo1 (赞：1)

### 题目大意
$M$ 和 $J$ 在 $n$ 堆石子轮流取任意数量的石子， $M$ 先手。如果当前玩家取的是第 $i$ 堆，那么下一个玩家就要从第 $i\bmod n + 1$ 堆中取石子。并且石子堆的堆数始终保持为 $n$ ，即取完该堆石子后，该堆石子也不会被移走。哪个玩家面临没有石子可取的情况就输掉比赛。
### 解题思路
如果 $n$ 为奇数时， $M$ 将在前 $n$ 轮拿奇数位置的石子，$J$ 则需要在第 $n+1$ 轮中拿 $1$ 号堆的石子。因此 $M$ 只需要在第 $1$ 轮把第 $1$ 堆的石子全部拿走即可保证必胜。  
如果 $n$ 为偶数时， $M$ 将一直拿奇数位置的石子， $J$ 一直拿偶数位置的石子，为了保证拿的次数尽可能的多，所以要保证每次拿的石子尽可能少，即每次都只取 $1$ 个。因此只需要找出数组中的最小值 $minn$ ，并且找到第一个等于 $minn$ 的 $a_i$ ，如果 $i$ 为奇数，则 $J$ 必胜，反之则 $M$ 必胜。
###  代码实现
```
void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++)
    cin>>a[i];
    if(n&1)
    cout<<"Mike"<<endl;
    else
    {
        int minn=*min_element(a+1,a+1+n);
        int p;
       for(int i=1;i<=n;i++)
        {
            if(a[i]==minn)
            {
             p=i;
             break;             
            }
        }
        if(p&1)
        cout<<"Joe"<<endl;
        else
        cout<<"Mike"<<endl;
    }
}

---

## 作者：cyrxdzj (赞：1)

### 一、思路

分为两种情况。

当 $n$ 为奇数的时候，Mike 必赢。因为，第一轮，Mike 拿的是石头堆中奇数编号的石头，Joe 拿的是偶数编号的。

但是，到了第二轮，Joe 反了过来，拿的是奇数编号的了。因此，如果第一轮 Mike 就把第一堆石头全拿完了，Joe 就没得拿了，Joe 必输。

当 $n$ 为偶数的时候，显然，每一轮，所有人都不可能拿到别人拿过的那一堆。Mike 始终拿奇数编号的，Joe 始终拿偶数编号的。因此，所有人都只能在每一次取石只拿一个。

那么，根据上面的分析，我们可以发现，对于石头堆中，最小堆的石头（如果存在多个最小，我们认为编号最小的才是真正最小的）是第一个被拿完的。因此，这堆石头属于谁，谁就必输。

### 二、代码

```cpp
#include<cstdio>
using namespace std;
int t;
int n;
int a[55];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		if(n%2)//n为奇数
		{
			printf("Mike\n");
		}
		else
		{
			int min_index=1;//选取最小的那一堆
			for(int i=2;i<=n;i++)
			{
				if(a[i]<a[min_index])
				{
					min_index=i;
				}
			}
			if(min_index%2)//判断这一堆属于谁
			{
				printf("Joe\n");
			}
			else
			{
				printf("Mike\n");
			}
		}
	}
	return 0;
}

```


---

## 作者：zhang_kevin (赞：0)

# $\texttt{Solution}$

当给定的 $n$ 为奇数时，$\texttt{Mike}$ 必胜。原因是，第一轮，他所拿到的石头堆是奇数编号的石头堆，$\texttt{Joe}$ 只能拿偶数编号的石头堆。然而，到了第二轮，$\texttt{Joe}$ 变成了拿奇数编号的石头堆的人。因此，如果第一轮 $\texttt{Mike}$ 直接把第一堆石头全拿完，$\texttt{Joe}$ 就没得拿了，她也就输了。

当 $n$ 为偶数时，每一轮所有人都不会拿到别人拿过的那一堆。因此，$\texttt{Mike}$ 始终拿奇数编号的，而 $\texttt{Joe}$ 始终会拿偶数编号的。因此，所有人都只能在每一次取石头时拿一个。

通过分析，可以发现最小堆的石头（如果存在多个，我们取编号最小的）是第一个被拿完的，这堆石头的主人也必定会输。

# $\texttt{Code}$

```cpp
#include<bits/stdc++.h>

#define endl '\n'
#define ri register int
#define rll register ll
#define rull register unsigned long long
#define ruint register unsigned int
#define iv inline void
#define ii inline int
#define ib inline bool

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair <int, int> pii;
typedef pair <int, bool> pib;
typedef pair <int, ll> pil;
typedef pair <ll, ll> pll;
typedef stack <int> si;
typedef stack <ll> sll;
typedef stack <ull> sull;
typedef stack <uint> suint;
typedef stack <pii> spii;
typedef stack <pib> spib;
typedef stack <pil> spil;
typedef stack <pll> spll;
typedef queue <int> qi;
typedef queue <ll> qll;
typedef queue <ull> qull;
typedef queue <uint> quint;
typedef queue <pii> qpii;
typedef queue <pib> qpib;
typedef queue <pil> qpil;
typedef queue <pll> qpll;
typedef vector <int> vi;
typedef vector <ll> vll;
typedef vector <ull> vull;
typedef vector <uint> vuint;
typedef vector <pii> vpii;
typedef vector <pib> vpib;
typedef vector <pil> vpil;
typedef vector <pll> vpll;


#ifndef ONLINE_JUDGE
#include<windows.h>
#else
#define debug(...) 42
#endif

/*
	When you are coding,remember to:
		- clear the arrays if a problem has many tasks.
		- pay attention to some special cases(n=0,1).
		- Don't code before think completely.
		- ...
*/

ll a[51];

iv Solve(){
	ll n;
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	if(n & 1) return cout << "Mike" << endl, void();
	int Min = 1;
	for(int i = 2; i <= n; i++){
		if(a[i] < a[Min]){
			Min = i;
		}
	}
	if(Min & 1) cout << "Joe" << endl;
	else cout << "Mike" << endl;
	return;
}

int main(){
	//freopen("文件名.in", "r", stdin);
	//freopen("文件名.out", "w", stdout);
	int T;
	cin >> T;
	while(T--) Solve();
	cerr << clock() << " ms." << endl; 
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
```


---

## 作者：Marshall001 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1695B)

## 题目大意

玩家从第一堆开始，顺时针依次从一堆中取出一些正数的石头。

如果一个玩家在回合中从第 $i$ 堆取石头，另一个玩家在下一轮从 $((i\bmod n) + 1)$ 堆取石头。

如果玩家在回合中无法取走任何石头，他就输了。

问：两人都采取最优策略，那么谁会赢？

## 思路

如果 $n$ 是奇数，那么玩家一 (Mike) 一定赢，为什么呢？因为第一次，玩家一 (Mike) 拿奇数堆，，然而第二次 （轮玩一圈了），玩家二 (Joe) 拿奇数堆，所以玩家一 (Mike) 只要在第一次把第一堆拿走就可以了（玩家二拿不了了）。

如果 $n$ 是偶数，那么玩家一 (Mike) 拿奇数堆，玩家二 (Joe) 拿偶数堆，所以最少的那一堆就一定最先被拿光（如果有多个最小，那么编号小的小），所以最少的那堆是谁的，谁就必输。

## 代码

```cpp
#include <iostream>
using namespace std;
int a[55];
int main(){
	int t;
	cin>>t;
	while(t--){//t次输入
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];//输入每堆的数量
		}
		if(n%2==1){//如果n是奇数
			cout<<"Mike"<<endl;//那么Mike赢
			continue;
		}
		int min_cur=1;
		for(int i=2;i<=n;i++){
			if(a[i]<a[min_cur]){
				min_cur=i;//记录最小的
			}
		}
		if(min_cur%2==0){//如果最小的是Joe的
			cout<<"Mike"<<endl;//那么Mike赢
		}
		else{//否则
			cout<<"Joe"<<endl;//Joe赢
		}
	}
	return 0;
}
```

## THE END

---


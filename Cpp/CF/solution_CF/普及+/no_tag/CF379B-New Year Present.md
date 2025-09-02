# New Year Present

## 题目描述

The New Year is coming! That's why many people today are busy preparing New Year presents. Vasily the Programmer is no exception.

Vasily knows that the best present is (no, it's not a contest) money. He's put $ n $ empty wallets from left to right in a row and decided how much money to put in what wallet. Vasily decided to put $ a_{i} $ coins to the $ i $ -th wallet from the left.

Vasily is a very busy man, so the money are sorted into the bags by his robot. Initially, the robot stands by the leftmost wallet in the row. The robot can follow instructions of three types: go to the wallet that is to the left of the current one (if such wallet exists), go to the wallet that is to the right of the current one (if such wallet exists), put a coin to the current wallet. Due to some technical malfunctions the robot cannot follow two "put a coin" instructions in a row.

Vasily doesn't want to wait for long, so he wants to write a program for the robot that contains at most $ 10^{6} $ operations (not necessarily minimum in length) the robot can use to put coins into the wallets. Help him.

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
PRPLRP```

## 样例 #2

### 输入

```
4
0 2 0 2
```

### 输出

```
RPRRPLLPLRRRP```

# 题解

## 作者：Da_un (赞：4)

## [题目传送门](https://www.luogu.com.cn/problem/CF379B)

大体意思就是有一个机器人在最左边在放硬币，它每一次操作都可以选择向左移动一个单位或向右移动一个单位，也可以选择在它所在的位置放一枚硬币，要求的输出的是达到目标状态的任意一种方案。

## 思路
既然题目要求的是输出任意一种方案，那么我们只要保证达到目标状态就行了，多余的步骤是不会影响结果的。

我们就可以每一次都从头走到尾或从尾走到头，对于每一次从头走到尾，我们先判断能不能放硬币，然后再往右走，对于每一次从尾到头，我们也还是先判断能不能放硬币，然后再往左走，这样进行若干次后，机器人的步骤会一直重复，此时结束循环即可。

这里还有些细节需要我们注意，因为题目中要求机器人不能连续两次进行投币操作，所以我们在从头到尾进入从尾到头的操作或从尾到头进入从头到尾的操作时需要特判一下它上一步是否进行了投币操作，如果进行了投币操作，那么直接向左或向右走，否则先去判断是否可以投币然后再向左或向右走。

对于我们枚举从头到尾以及从尾到头的次数，题目中给出的 $n$ 最大到 $300$，给出的某一个地方的硬币数 $a_i$ 最大到 $300$，所以我们没有必要去枚举一个特别大的数，可能还会出现误差，我们的枚举次数在 $400$ 到 $1000$ 之间最为安全。

总的来说，本题细节还是比较多的。

## Code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,t,q,p;
int f[500];
void pre(int s)
{
	while(t<=900){//安全的枚举次数 
		for(int i=s;i<=n;i++){
			if(p==1&&i==s){
				p=0;
				cout<<'R';
				continue;
				//上一次的头放过，此次直接向右走 
			}
			if(f[i]>0){
				if(i==n)
					q=1;//特判从尾到头的尾 
				f[i]--;//投币 
				cout<<"P";
			}
			if(i!=n)
				cout<<"R";//到最右端，没必要在往右走 
		}
		for(int i=n;i>=s;i--){
			if(q==1&&i==n){
				q=0;
				cout<<'L';
				continue;
				//上一次的尾放过，此次直接向左走
			}
			if(f[i]>0){
				if(i==s)
					p=1;///特判从头到尾的头  
				f[i]--;//投币 
				cout<<"P";
			}
			if(i!=s)
				cout<<"L";//到最左端，没必要在往左走	
		}
		t++;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&f[i]);
	pre(1);//从最左边开始 
	return 0;
	//完结撒花~~ 
}
```
### [AC记录](https://www.luogu.com.cn/record/60204823)

---

## 作者：TheTrash (赞：2)

我们只需枚举从左到右的钱包，判断里面是否要装钱，如果要装钱，就输出 ```P```。

但是机器人不能连续两次塞钱，于是我们还要让机器人向左再向右走（相当于输出 ```LR```，这样机器人就可以继续塞钱了。注意当机器人在最左边时，得让它先向右再向左走）。

```cpp
#include<iostream>
using namespace std;
bool flag=1;//这个变量的作用是检查机器人是否上一次操作是否是塞钱
void money(int a[],int n){
	for(int i=0;i<n;i++){
		if(flag==0&&a[i]>=1&&i!=0){cout<<"LR";flag=1;}
		if(flag==0&&a[i]>=1&&i==0){cout<<"RL";flag=1;} //如果当机器人在最左边时，输出“RL”，否则输出“LR”
		if(flag==1&&a[i]>1){ //如果要在这个钱包里塞多个钱的话，就可以用while循环一直让机器人塞钱，直到这个钱包里要塞的钱只剩1为止
			while(a[i]>1){
				if(i==0)cout<<"PRL";
				else cout<<"PLR";
				a[i]--;
			}
			cout<<"P";//直接让机器人塞钱
                        a[i]--;
			flag=0;
		}
		if(flag==1&&a[i]==1)cout<<"P",a[i]--,flag=0;
                //当这个钱包里只要塞一个钱（听起来好怪）时，直接输出“P”
		if(a[i]==0&&i!=(n-1)){cout<<"R";} //如果机器人在最边上，那么就不用再向右走了
	}
}
int main(){
	int n;
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	money(a,n);
	return 0;
}
```

---

## 作者：Chinese_Dragon (赞：1)

第一眼看时：

#### 这不就模拟吗？！

按题目说的一步步搞就好了。

- 第一步：输入——一个 scanf 加一个 for 搞定。

- 第二步：模拟放钱的过程（重点）——这里用一个 while 循环来一步一步模拟，当当前钱袋没放满前就放一个硬币，再向左/右移动，判断移动方向的方法：一旦到达最左端就往右；同理，一旦到达最右端就往左。放完钱判断一下看，要是全放完了就自动退出。注意！移动和放钱的过程要一步一步输出。

###### ~~这不就好了嘛。~~

**3·**

上~~丑陋~~代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[350],b[350];
int main()
{
    int n,l=1,h=1;
    bool f=0;
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    while (1)
    {
        if (b[l]<a[l])
        {
            ++b[l];
            cout<<'P';
        }
        f=1;
        for (int i=1;i<=n;++i)
        {
            if (b[i]!=a[i])
            {
                f=0;
            }
        }
        if (f==1)
        {
            return 0;
        }
        if (l==n)
        {
            h=2;
        }
        if (l==1)
        {
            h=1;
        }
        if (h==1)
        {
            cout<<"R";
            ++l;
        }
        else
        {
            cout<<"L";
            --l;
        }
    }
    return 0;
}
```

本蒟的第一篇题解，求通过~

---

## 作者：流绪 (赞：1)

就是模拟,因为没有必要输出最短,且 300*300=90000 比起题目给的 1e6 小太多了!

所以我们就可以很简单的模拟它!从 1 开始走,遇到要填的点就填,然后 RLP 再填,十分暴力!注意第一个位置和最后一个位置的时候,因为不能越界且第一次到 1 不用输出怎么走过来的,因为他一开始就在 1

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin >> n ;
	for(int i=1;i<=n;i++)
	{
		int a;
		cin >> a;
		if(a==0)
		{
			if(i!=1)
				cout << "R";
		}
		else
		{	
			if(i==1)
				cout <<"P";
			else
				cout << "RP";
			a--;
			while(a--)
				if(i!=n)
					cout << "RLP";
				else
					cout << "LRP";//在最右边不能越界那我们先往左走
		}
	}
}
```


---

## 作者：liuli688 (赞：0)

其实本题难度（个人）不超过橙题。
### 思路：
由于题目要求方案长度不要求最短，只要长度不超过 $10^6$ 就行了，算一下极端情况（$n = 300$，$a_i=300$）的情况操作数为 $300 \cdot 300 \cdot 3 = 2.7 \cdot 10^5$，不会超限，所以只要暴力输出即可。

- 如果目前不在最后一个：输出 $a_i-1$ 次 `PRL`（凑步数，因为不能连续两次塞钱），然后输出 `PR`（不用回来了，如果 $a_i \ne 0$ 则放）。
- 在最后一个：输出 $a_i-1$ 次 `PLR`（不能越界），然后输出 `P`。
### 代码：
```cpp
#define MAIN signed main()
#define SPEEDUP ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define USING using namespace std
#define END return 0
#define LL long long
#define ULL unsigned long long
#define LD long double
#define STR string
#define EL '\n'
#define BK break
#define CTN continue
#define INF INT_MAX
#define UINF INT_MIN
#define IN(n) cin >> n
#define OUT(n) cout << n
#define OUTL(n) cout << n << EL
#define FP(i,a,b) for(i = a;i < b;i++)
#define FM(i,a,b) for(i = a;i > b;i--)
#define FL(i,a,b) for(i = a;i <= b;i++)
#define FG(i,a,b) for(i = a;i >= b;i--)
//以上为缺省源
#include <bits/stdc++.h>
USING;
int n,a[300],i,j;
MAIN
{
	SPEEDUP;
	IN(n);
	FP(i,0,n)
		IN(a[i]);
	FP(i,0,n-1)
	{
		if(a[i])//如果这个钱包需要放钱
		{
			FP(j,0,a[i]-1)//不断放钱
				OUT("PRL");
			OUT("PR");//放完后直接右移，不回来
		}
		else//直接右移跳过
			OUT('R');
	}
	if(a[n-1])//同样判断最后一个钱包
	{
		FP(j,0,a[n-1]-1)//不断放钱
			OUT("PLR");
		OUT('P');//放最后一个钱
	}
	END;
}
```

---

## 作者：I_AK_IOI_6648 (赞：0)

## 题意简述
有一个机器人在放硬币，从最左边开始，每次可以选择向左一步或向右一步或放一个硬币，但是不能连续进行两次放硬币操作，求一个操作方式可以放完所有硬币，不要求最短。

## 思路
首先看到 $n$ 的范围，$n\le300$，序列长度小于 $10^6$。

所以，不用怕序列过长。

又因为有 SPJ ，所以只要输出一个合法序列即可

用模拟即可解决。

如果没有不能连续进行两次放硬币操作这个限制，那解法显而易见，放完一个地方再放下一个。

那如果加上限制呢？

其实也差不多，放完一个后，左右横跳缓冲一下即可。

注意第一个位置不能先向左跳，最后一个位置不能先向右跳。

放完一个位置后要向右移动到达下一个位置，最后一个位置就不用了。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[305];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=n;i++)
    {
        if(a[i]==0) //如果不用放
        {
            if(i!=n)
            {
                cout<<"R";
                continue;
            }
        }
        while(a[i]--)
        {
            if(i!=n)
            {
                cout<<"PRL";
            }
            else    //对于最后一个位置要特判
            {
                cout<<"PLR";
            }
        }
        if(i!=n)    如果已经是最后一个位置，就不用再往后了
        {
            cout<<"R";
        }
    }
    cout<<endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# CF379B New Year Present 题解

[题目](https://www.luogu.com.cn/problem/CF379B)

## 题意：
一个机器人，初始位置在 $1$ ，要在 $n$ 个位置上放硬币，第 $i$ 给位置要放 $a_i$ 个硬币。
机器人允许
- $l$ 向左走一个位置，不能越界。
- $r$ 向右走一个位置，不能越界。
- $p$ 在当前位置上发一枚硬币，不能连续放硬币。

## 思路

这就是一道模拟~~水~~只需要往右走，有就放。

- 当 $a_i=0$ 直接往右走，输出 $r$。
- 当 $a_i=1$ 放一枚硬币后往右走，输出 $pr$。
- 当 $a_i>1$ 先放一枚硬币，再放硬币加左右走达到不连续放硬币~~磨~~。
	- 当 $i=1$ 因为不能越界所以只有输出 $rpl$
   - 当 $i=n$ 因为不能越界所以只有输出 $lpr$
   - 其他时候随便，因为有 Special Judge
	- 最后往右走，输出 $r$。
    
## code 

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define re register
#define endl '\n'

const int maxn=301;
int n,a[maxn];

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==0)
		{
			if(i<n)
			{
				cout<<'R';
			}
			continue;
		}
		cout<<'P';
		if(i==1)
		{
			while(--a[i])
			{
				cout<<"RLP";
			}
		}
		else
		{
			while(--a[i])
			{
				cout<<"LRP";
			}
		}
		if(i<n)
		{
			cout<<'R';
		}
	}
	cout<<endl;
	return 0;
}
```

## 写在最后
因为这道题的不越界，导致我花费了 2.5 小时研究怎么 WA 的。

---

## 作者：nxd_oxm (赞：0)

# 题意
题目说有个人他发明了机器人，要在一些格子里放硬币。机器人捏可以向左向右和放硬币。但机器人不能连续放，他说求出一种组合方式。
# 思路
其实他没说一定要最短解，因为是 ``Special Judge``，所以我们只要找出一种就行啦。

暴力枚举每个点，只要还有就在这放。

因为不能连续放，所以我们先移动缓冲一下。

向左向右缓冲，也就是 ``LRP``。但要特判，如果是第一个点就要向右向左缓冲，不然就出去了。

没了!

~~就这么简单~~
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
using namespace std;
signed main(){
    int n,a[1001];
    cin>>n;
	f(i,1,n){
        cin>>a[i];
    }
    f(i,1,n){
        if(!a[i]){
            if(i==n){
                break;
            }
            cout<<'R';
        }else{
            cout<<'P';
            a[i]--;
            while(a[i]){
                if(i==1){
                    cout<<"RLP";
                }else{
                    cout<<"LRP";
                }
                a[i]--;
            }
            if(i!=n){
                cout<<'R';
            }
        }
    }
	return 0;
}

```

---

## 作者：qiuzijin2026 (赞：0)

# New Year Present

## [题面](https://www.luogu.com.cn/problem/CF379B)

## 思路

暴力构造即可。

分以下情况讨论：

1. 如果 $a_{i}=0$：

	- 如果 $i \ne n$，输出 ``R``。
   
   - 否则结束程序。
 
2. 如果 $a_{i}=1$，输出 ``P``： 

	- 如果 $i \ne n$，输出 ``R``。
   
   - 否则结束程序。
   
3. 如果 $a_{i}>1$：

	- 如果 $i \ne 1$，输出 ``LRP``，然后 $i$ 不变。
   
   - 否则，输出 ``RLP``，然后 $i$ 不变。
   
按顺序枚举即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[305];
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		if(a[i]==0){
			if(i!=n) printf("R");
			continue;
		}
		printf("P");
		a[i]--;
		while(a[i]){
			if(i!=1) printf("LRP");
			else printf("RLP");
			a[i]--;
		} 
		if(i!=n) printf("R"); 
	}
	return 0;
}
```

---

## 作者：BZHZS (赞：0)

### 关于题目
[题面传送门](https://www.luogu.com.cn/problem/CF379B)

这又是一道水绿题，实际难度应该只有红到橙左右。

### 思路分析

这道题比较方便的地方时不要求求出最短方案，而是合理即可。观察数据范围 $2≤n≤300$ 且 $1≤k≤10^6$。很容易可以发现我们从第一位开始一个数位一个数位的放钱，把一个数位放完后在去放下一个。但是，由于不能连续两步放钱，所以我们需要在放一次钱后来回走两步。举个例子，比如说现在第 $1$ 位需要放 $2$ 块钱。
我们可以先放 $1$ 块钱，再走到第 $2$ 位， 再走回第 $1$ 位， 再放 $1$ 块钱。放完了过后就向右走，找下一个需要放钱的地方。

### 细节注意

- 不能越界，也就是不能在第 $1$ 个点向左走， 第 $n$ 个点向右走。
- 就算所有的钱都放完了，也还可以继续移动。
- 其他细节详见代码。

### 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

int n;
int a[N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
	{
		if (!a[i])//如果不用放钱，就直接往右走。
		{
			if (i != n)//如果在最右边，就不能往右走了。
				printf("R");
			continue;
		}
		while (a[i]--)//放钱
		{
			if (i < n)//不同的徘徊凑步数方式，为了防止越界。
				printf("PRL");
			if (i == n)//最左边不能往最左边走，最右边不能往最右边走。
				printf("PLR");
		}
		if (i != n)//如果不是最右边，继续往右边走。
			printf("R");
	}

	return 0;
}
```


---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF379B)
## 思路
这是一道很简单的模拟题。

显然我们可以分成很多种情况：

  1. $a_i>a_{i+1}$ 我们先往右跳，然后往左跳，跳的过程中给 $a_i$ 和 $a_{i+1}$ 都消掉一个 $1$，直到 $a_{i+1}$ 消完，我们就只消 $a_i$。
  2. $a_i=a_{i+1}$ 与第一种情况一样。
  3. $a_i<a_{i+1}$ 与第一种差不多，区别只是 $a_i$ 先消完，我们就不消了，让 $i$ 加一。

## 代码
```cpp
//A tree without skin will surely die. 
//A man without face is invincible.
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
int const N=3e2+10;
int a[N];
vector<char>ans;
signed main(){
    ios::sync_with_stdio(false);
    cout.tie(0),cout.tie(0);
    int n;cin>>n;
    for (rint i=1;i<=n;++i) cin>>a[i];
    int now=1;
    for (rint i=1;i<=n;++i){
        if (i!=1) ans.push_back('R');
        if (!a[i]) continue;
        if (i==n){
            for (rint j=1;j<=a[i];++j)
                ans.push_back('P'),ans.push_back('L'),ans.push_back('R');
            break;
        }
        if (a[i]>=a[i+1]){
            for (rint j=1;j<=a[i+1];++j)
                ans.push_back('P'),ans.push_back('R'),ans.push_back('P'),ans.push_back('L');
            a[i]-=a[i+1],a[i+1]=0;
            for (rint j=1;j<=a[i];++j)
                ans.push_back('P'),ans.push_back('R'),ans.push_back('L');
        }else{
            for (rint j=1;j<=a[i];++j)
                ans.push_back('P'),ans.push_back('R'),ans.push_back('P'),ans.push_back('L');
            a[i+1]-=a[i];
        }
    }
    for (rint i=0;i<ans.size();++i) cout<<ans[i];cout<<'\n';
    return 0;
}

```


---

## 作者：TheSky233 (赞：0)

## Description

给定一些钱包 $\{a\}$，每个钱包需要 $a_i$ 个硬币，现在有一个机器人站在 $a_1$ 的位置，它可以进行三个操作：

- 放一个硬币（不允许连续执行两次），此时 $a_i \gets a_{i} -1$，输出 $\tt P$。

- 向左走一格（不允许越界），此时 $i\gets i-1$，输出 $\tt L$。

- 向右走一格（不允许越界），此时 $i\gets i+1$，输出 $\tt R$。

机器人需要把所有钱包填满，求一个合法的操作序列（长度不超过 $10^6$）。

## Solution

我们把机器人不停地从左到右，碰到边界返回。扫描一遍，此时如果 $a_i>0$，让 $a_i \gets a_i-1$。设 $\max\limits_{i=1}^{n} a_i$ 的值为 $m$，这样，我们就可以在 $\mathcal O(nm)$ 的操作数内解决这道题。

同时，因为 $2 \le n \le 300, 0 \le a_i \le 300$，所以操作数的上界为 $9 \times 10^4$，远小于题目要求的 $10^6$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
    char c; bool f (true);
    while (c = getchar(), c < '0' || c > '9') f = c != '-';
    int x (c ^ 48);
    while (c = getchar(), c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48);
    return f ? x : -x;
}

int n,a[305],full,pos=1,dir=1;

int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]) full++; // 有几个钱包是满的
	}
	while(full){
		if(pos==n) dir=-1; // 右边界，回头
		else if(pos==1) dir=1; //左边界，回头
		
		if(a[pos]){
			a[pos]--;
			if(!a[pos]) full--;
			putchar('P');
			if(!full) return 0;
		}
		if(dir==1) putchar('R'),pos+=dir;
		else putchar('L'),pos+=dir;
	}
	return 0;
}
```

---


# Waiting for...

## 题目描述

Monocarp 正在车站等公共汽车。不幸的是，也有很多人想乘坐公共汽车。

你会得到两类事件的列表：

- B $b_i$  ：有 $b_i$ 个免费座位的巴士到达车站；
- P $p_i$  ： $p_i$ 人到站。

这些事件是按时间顺序列出的。

当公共汽车到达时，会发生以下情况。公车站的所有人（除了 Monocarp ）都试图上车。如果所有人都有足够的空位，他们就都上车。否则，有些人会留在公交车站（上车的人数等于免费座位的数量）。

如果在所有人（除了 Monocarp ）进入公共汽车后仍然至少有一个空闲座位，那么 Monocarp 可以决定也进入这辆公共汽车（但他可能选择等待另一辆公共汽车）。对于每一辆公共汽车，您必须确定 Monocarp 是否有可能乘坐该公共汽车。

## 样例 #1

### 输入

```
10
P 2
P 5
B 8
P 14
B 5
B 9
B 3
P 2
B 1
B 2```

### 输出

```
YES
NO
NO
YES
NO
YES```

# 题解

## 作者：ryf2011 (赞：6)

# 题解：CF2038J Waiting for...

## 题目思路
我们思考，在什么情况下，人物可以上车？

答案为：当来了若干辆车，使得当前所有人都上车后还能留下不少于一个空位。

本题还有一个重点：如果当前车辆不能装下所有人再加上 $1$ 则不成立，这时应该让所有能上车的人上车。

我们维护多个变量，按上述过程模拟即可。

## 代码
注：本代码仅供参考。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,p,nowp;
char b;
int main(){
	//输入 
	scanf("%d",&n);
	for(int z=1;z<=n;z++){
		scanf("%c",&b);
		scanf("%c %d",&b,&p);
		if(b=='P'){ //车站进人 
			nowp+=p;
		}
		else{
			if(p>=nowp+1){ //如果当前可以装下所有人，则 nowp=0。 
				printf("YES\n");
				nowp=0;
			}
			else{ //否则，让所有能上车的人上车。 
				printf("NO\n");
				nowp-=p;
			}
		}
	}
	return 0;
}
```

#### 后记
更多内容，请移步至 [$\color{orange}\texttt{ryf2011}$](https://www.luogu.com.cn/user/1151973 "点我进入ryf2011")。

---

## 作者：linch (赞：2)

## Problem
共有 $n$ 个请求，第 $i$ 个请求要么是来了一辆载客为 $b_i$ 公交车，要么是来个 $p_i$ 个人。对于每次来了车的请求，不超过此车座位数量的乘客可以上车，如果等车的所有乘客都能上车，且上完还有空位，输出 `YES`，否则输出 `NO`。

## Solution
模拟即可。

可以维护一个变量 $p$，代表等车总人数。每次来了车，如果座位数大于等于人数，让他们全上车，否则让这辆车坐满。然后判断是否还有空位即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, p;
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		char op;
		int x;
		cin >> op >> x;
		if(op == 'P') p += x;
		else {
			if(p <= x) {
				x -= p;
				p = 0;
			}
			else {
				p -= x;
				x = 0;
			}
			if(x > 0) cout << "YES\n";
			else cout << "NO\n";
		}
	}
	return 0;
}
```

[AC record](https://codeforces.com/contest/2038/submission/293105558)

---

## 作者：jubaoyi2011 (赞：2)

在下文中 Monocarp 简称为 M。

我们可以定义一个 $s$ 变量来表示当前在车站的人数，这里唯一要注意的就是 **M 一开始就在车站**，所以 $s$ 也可以不包括 M。

对于每次 `P` 操作，只需要让 $s$ 加上到站的人数 $p_i$ 即可。

对于每次 `B` 操作，只需要判断在所有人都上车后 M 还能不能上车，也就是比较 $s - 1$ 和 $b_i$ 的大小（若 $s$ 不包括 M 的话就比较 $s$ 和 $b_i$ 的大小），如果 $s - 1 \le b_i$（或 $s \le b_i$），就输出 `YES`，否则就输出 `NO`。

然后还需要让总人数减去上车的人数，要注意的是 **M 是不会上车的**。当所有人都上车后 M 还能上车的话就令 $s$ 减去 $s-1$（或令 $s$ 减去 $s$），否则就令 $s$ 减去 $b_i$；综上所述，需要令 $s$ 减去 $\min{s-1,b_i}$（或令 $s$ 减去 $\min{s,b_i}$）。


```cpp
#include <bits/stdc++.h>
main(){
    int n;
    std::cin>>n;
    int s=1;//当前人数，也可以写成 int s=0;
    while(n--){
        char c;
        int bp;
        std::cin>>c>>bp;
        if(c=='P')s+=bp;
        else{
            std::cout<<(s<=bp?"YES":"NO")<<'\n';
            s-=std::min(s-1,bp);//s-=min(s,bp);
        }
    }
    return 0;
}
```

---

## 作者：adsd45666 (赞：1)

确实是简单就是了。

## 题意概述

有一个车站，按时间顺序发生了 $n$ 件事：

- $B \space x$ 表示车站来了一辆载客量为 $x$ 的巴士。
- $P \space x$ 表示车站来了 $x$ 个排队上车的人。

对于每次来车，你需要估计你能否上车，可输出 `YES`，否输出 `NO`。

特殊的，定义你能否上车为车的载客量减去车站现有量是否还能再加一个人（~~因为你比较善~~）



## 解题思路

简单的模拟，建立车站现人数变量 $sum$。

那么对于每次 $B$ 操作来说，若 $x-sum \geqslant 1$ 即输出 `YES`，否则输出 `NO`。

对于每次的 $P$ 操作，只需累加 $sum$ 即可。

## code

```cpp
#include <bits/stdc++.h>
#define seq(q, w, e) for (int q = w; q <= e; q++)
#define ll long long
using namespace std;
const int maxn = 1e5+10,inf=0x7fffffff;
int t,sum,x;
char op;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>t;
    while(t--){
        cin>>op>>x;
        if(op=='B')
            if(x-sum>=1){
                cout<<"YES"<<"\n";
                sum=0;
            }
            else{
                cout<<"NO"<<"\n";
                sum-=x;
            }
        if(op=='P') sum+=x;
    }
    return 0;
}
```

---

## 作者：c_legg (赞：1)

## 题目链接

[洛谷](https://www.luogu.com.cn/problem/CF2038J)

[CodeForces](https://codeforces.com/problemset/problem/2038/J)

## 题目大意（DeepL 翻译）

Monocarp 正在公交车站等车。不幸的是，有很多人也想乘坐公共汽车。

你会得到一份两类事件的清单：

- `B` $b_i$ - 一辆有 $b_i$ 个空座位的公交车到站；
- `P` $p_i$ - 有 $p_i$ 人到达车站。

这些事件按时间顺序排列。

当一辆公共汽车到达时，会发生以下情况。公交车站的所有人（除了 Monocarp）都试图进入公交车。如果有足够的空位，他们就都上车。否则，一些人将留在公交车站（进入公交车的人数等于空余座位数）。

如果所有的人（除了 Monocarp）都进入公交车后还有至少一个空座位，那么 Monocarp 也可以决定进入这辆公交车（但他可能会选择等另一辆公交车）。对于每辆公交车，您都必须确定 Monocarp 是否有可能乘坐该公交车。

## 思路

用 $x$ 表示车站剩下的人数，如果遇到事件 `P`，就让 $x$ 加上 $p_i$；如果遇到事件 `B`，就比较 $x$ 和 $b_i$：如果 $x\geq b_i$，就让 $x$ 减去 $b_i$，输出 `NO`，否则 $x$ 就变为 $0$，输出 `YES`。

## 代码

``` cpp
#include <iostream>
using namespace std;

int main() {
  int n, x=0, i;
  char thi;
  cin>>n;
  while(n--) {
    cin>>thi>>i;
    if(thi=='P') x+=i;
    else if(thi=='B') {
      if(x>=i) {
        cout<<"NO"<<endl;
        x-=i;
      }else {
        cout<<"YES"<<endl;
        x=0;
      }
    }
  }
  return 0;
}
```

[AC 记录](https://codeforces.com/contest/2038/submission/293239697)

---

## 作者：GeYang (赞：1)

# 题意

一个人在站台上等车，站台上也有其他人等车。每辆公交车来时给你车上剩余位置和应上车人数，上不去的留在站台。假设那个人每次都最后上车，且可以上任何一辆。

每来一辆车，就问你他能不能上去。

# 思路

用 $people$ 记录站台上的人数，来车时判断，座位数不小于应上车人数就输出 ```YES``` 这个字符串，站台人数变为一；否则输出 ```NO``` 这个字符串，并将站台人数减去实际上车人数即空位数。

# 代码


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t;
void solve()
{
	char c;
	ll n,people;
	cin>>c>>n;
	if(c=='P') people+=n;
	else
	{
		if(people<=n)
		{
			cout<<"YES\n";
			people=1;
		} 
		else
		{
			cout<<"NO\n";
			people-=n;
		}
	}
}
int main()
{
	cin>>t;
	while(t--) solve();
	return 0;
} 
```

---

## 作者：TheTrash (赞：1)

### 题意

Monocarp 正在等公交车。每次 ```P``` 操作时会来 $p_i$ 个人，每次 ```B``` 操作时会来一辆公交车带走 $b_i$ 个人。当公交车上的座位数大于站台上等的人数时 Monocarp 就会上车。求每次 ```B``` 操作后 Monocarp 是否可以上车。

### 思路

用变量 $s$ 记录当前站台上除 Monocarp 外有多少人。每次 ```B``` 操作时可以判断站台上的人数是不是可以全部上公交。如果是就输出 ```YES```，让 $s$ 变为 $0$，否则输出 ```NO```，让 $s$ 减去公交车的空位数。每次 ```P``` 操作就直接让 $s$ 加上来的人数。

```cpp
#include<iostream>
using namespace std;
int n,x,s;
char c;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>c>>x;
		if(c=='B'){
			if(x>s) puts("YES"),s=0;
			else puts("NO"),s-=x;
		}
		else s+=x;
	}
}
```

---

## 作者：wuyouawa (赞：1)

### 题目大意


Monocarp 正在公交站等车。不幸的是，站里有很多人也想搭公交。给定一系列事件，这些事件有两种类型：

- B $b_i$，表示一辆公交车到达，车上有 $b_i$ 个空座位；

- P $p_i$，表示 $p_i$ 个人到达公交站。

这些事件按时间顺序排列。当公交车到达时，会发生以下事情：站内的所有人（除了 Monocarp）都会尝试上车。如果公交车上的空座位足够容纳所有人，他们都会上车。否则，只有空座位数量的人能上车，剩下的人将继续等待。如果在所有非 Monocarp 的人上车后，仍然有至少一个空座位，那么 Monocarp 可以选择是否上这辆车（但他也可以选择等下一班车）。对于每辆公交车，你需要判断 Monocarp 是否能上车。

### 思路

定义一个变量统计现在有多少人等车，如果是巴士来了，那么那些人加上 Monocarp $1$ 个人已经超过车上空位数就不行，否则可以。上了车之后的那些人要从等车的那里减掉，如果没有人等车则置为 $0$。如果又有人来等车，那么变量要加上这些人。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,w,b;
char c;
int main(){
    cin>>n;
    while(n--)
    {
    	cin>>c>>b;
    	if(c=='B')//如果有巴士来 
    	{
    		if(w+1<=b)  cout<<"YES\n";
    		else  cout<<"NO\n";//判断是否容下 
    		w-=b;
    		if(w<0)  w=0;//特判没有乘客等 
    	}
    	else//如果有乘客来 
    	{
    		w+=b;//直接加 
    	}
    }
    return 0;
}
```

---

## 作者：GCSG01 (赞：1)

### 思路
**注意** Monocarp 是不会上车的。  
首先我们用一个变量 $s$ 表示当前车站还有多少个人（不包括 Monocarp），对于 `p` 事件，直接让 $s$ 加上到站人数即可。对于 `b` 事件，如果位置数大于 $s$，则说明在所有人上车后 Monocarp 是可以上的，则将 $s$ 重置为 $0$，因为除 Monocarp 外的所有人的坐车走了，同时输出 `YES`。否则所有位置都会被坐，Monocarp 就坐不了了，将 $s$ 减去位置数并输出 `NO`，因为其他能坐车的人不管怎样都会坐车走。
### Code
赛时代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("1.in","r",stdin);
    #endif
    int s=0;
    int t;
    cin>>t;
    while(t--)
    {
        char op;
        int k;
        cin>>op>>k;
        if(op=='B')
        {
            if(s<k)cout<<"YES\n";
            else cout<<"NO\n";
            s-=k;
            s=max(s,0ll);
        }
        else
            s+=k;
    }
    return 0;
}
```

---

## 作者：Wei_ch (赞：0)

### 大意
Monocarp 正在车站等公交车，还有其他的人进入车站。你会得到一个事情的序列，表示这些人的到来或公交车的到来。你要判断 Monocarp 有没有可能乘坐每辆到来的公交车。Monocarp 只有在所有人上车后仍有空座位的情况下才能乘坐这辆车。
### 思路
用一个数组记录当前车站的人数，每次公交车到来时就进行判断，再把目前车站里人数减掉上车的人数就行了。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,man=1;
	cin>>n;
	while(n--){
		char opt;
		cin>>opt;
		if(opt=='B'){
			int num;
			cin>>num;
			if(man>num){
				man-=num;
				cout<<"NO"<<endl;
			}else{
				man=1;
				cout<<"YES"<<endl;
			}
		}else{
			int add;
			cin>>add;
			man+=add;
		}
	} 
	return 0;
}
```

---

## 作者：Loyal_Soldier (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2038J)

### 思路
如果是公交车到站，就判断座位是否够，如果够则输出`YES`（记住，这时车站还剩 $1$ 个人），否则输出`NO`，减去相应人数。如果有人来了就将人数增加。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int now=1;//now表示当前有多少人
int main(){
	int n;
	cin>>n;
	while(n--){
		char c;
		int x;
		cin>>c>>x;
		if(c=='B'){
			if(now<=x){
				cout<<"YES\n"; 
				now=1;//记住 ，Monocarp 不会上车，所以要变为1 
			}
			else{
				cout<<"NO\n";
				now-=x;
			}
		}
		else
			now+=x;
	}
	return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：0)

# 题解：CF2038J Waiting for...
## 分析
先存一下当前还剩 $x$ 人在等车。下车操作就将 $x$ 加上下车的人数。上车操作则看当前有几个空位置，若空位置的数量大于 $x$，则主角可以上车，将等车的人数重置；否则主角不能上车，将 $x$ 减去座位数。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char opt;
int X;
signed main()
{
	int t, x=0;
	for(cin>>t;t;t--)
	{
		cin>>opt>>X;
		if(opt=='P')
		{
			x+=X;
		}
		else
		{
			if(X>x)
			{
				cout<<"YES\n";
				x=0;
			}
			else
			{
				cout<<"NO\n";
				x-=X;
			}
		}
	}
	
}

---

## 作者：_Sky_Dream_ (赞：0)

# [传送门](https://www.luogu.com.cn/problem/CF2038J)

相信在没有翻译时，我们需要翻译。

有一辆公交车，刚发车时是满员的，途径 $T$ 个站点，对于每个站点，存在有两种类型的操作，对于操作 $B$，就是在该站点有 $x$ 个人上车；对于操作 $P$，就是在该站点有 $x$ 个人下车。

当然，如果出现座位不够，那么多余的人就会打道回府。

现在，对于每一组操作 $B$，询问是否有人打道回府。

直接模拟即可。设立变量统计空余的座位数。


```cpp
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define int long long
#define MAX 1145141919810
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define dep(i,x,y) for(int i=x;i>=y;--i)
#define N 114514
using namespace std;
int T;
char xd;
int k,seats;
inline void Main(){
	cin>>xd>>k;
	if(xd=='B'){
		if(seats<k)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
		seats-=k;
		seats=max(seats,0);
	}
	else seats+=k;
} 
void Enchanted(){
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>T;
	while(T--)Main();
}
signed main(){Enchanted();}



```

---

## 作者：MournInk (赞：0)

非常朴实无华的模拟题。

令当前车站人数为 $P_{\text{station}}$。

当来了 $p_i$ 人时：我们使 $P_{\text{station}}$ 增加 $p_i$。

当来了有 $b_i$ 个空座的公交车时：
- 如果 $P_{\text{station}} \geq b_i$，那么会有 $b_i$ 个人上车，且此时 `Monocarp` 无法上车。那么当前令 $P_{\text{station}}$ 减少 $b_i$ 并输出答案 `NO`。
- 否则当前车站所有人都会上车，并且车上还会有空位，`Monocarp` 可以上车，此时令 $P_{\text{station}}$ 变为 $0$ 并输出答案 `YES`。

附代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, p = 0;
    for(cin >> n; n --; )
    {
        char op; int x;
        cin >> op >> x;
        if(op == 'P') p += x;
        else
        {
            if(p < x) puts("YES"), p = 0;
            else puts("NO"), p -= x;
        }
    }
    return 0;
}
```

> 本文来自：
> ![做干净的奥赛](https://img.picgo.net/2024/11/19/950f46f6adff54912eadac7f86ab204670735f7200db90bb.png)
>
> 另附[官方题解](https://codeforces.com/contest/2038/attachments/download/28397/presentation_eng.pdf)。

---

## 作者：tanzexiaodezhonghao (赞：0)

## 思路
题意大概是这样：
- 输入 `P`，有 $x$ 人来到这个站点。
- 输入 `B`，有一辆有 $x$ 个空座的巴士来。

你需要判断，当巴士来的时候，这个站点的所有人能否全部上车，可以上车的就全部上车，并输出 `YES`，不可以的就上一部分，输出 `NO`。

接下来直接模拟，用一个变量 $ans$ 记录站点人数，车来了就判断，并让 $ans$ 减去 $\min(x,ans)$。
## 代码
[AC记录](https://codeforces.com/contest/2038/submission/292609031)
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,x,n;char op;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>op>>x;
        if(op=='P'){ans+=x;}
        if(op=='B'){
            if(x>ans) cout<<"YES\n";
            else cout<<"NO\n";
            ans-=min(x,ans);
        }
    }
    return 0;
}
```

---

## 作者：_dbq_ (赞：0)

## 前言
[题目传送门](https://www.luogu.com.cn/problem/CF2038J)

## 思路
用一个变量 $now$ 记录当前车站里有多少人，读到一辆车到达，判断空位是否大于当前人数。如果成立，输出 `YES`，将 $now$ 设为一；否则，输出 `NO`，并让尽可能多的人上车。

## 代码

```cpp
#include<iostream>
using namespace std;
int n,now=1;
string s;
int x;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s>>x;
		if(s[0]=='P'){
			now+=x;
		}
		else{
			if(now<=x){
				cout<<"YES"<<'\n';
				now=1;//把自己留下来
			}
			else{
				cout<<"NO"<<'\n';
				now-=x;
			}
		}
	}
} 
```

---

## 作者：Vct14 (赞：0)

签到题，一发过了。

考虑用变量 $x$ 存一下除 Monocarp 外车站当前人数。如果人数小于座位数就能上车，否则不能上车。因为每次要么上 $x$ 个人要么 $p_i$ 个人全上车，所以每次让人数减去 $\min(p_i,x)$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;cin>>n;
	int x=0;
	while(n--){
		int b;char ch;cin>>ch>>b;
		if(ch=='B'){
			if(x<b) puts("YES");
			else puts("NO");
			x-=min(x,b);
		}
		else x+=b;
	}
	return 0;
}

```

---

## 作者：Eason_cyx (赞：0)

不测样例一发过！

-----

题意很清楚了。

我们用 $n$ 表示现在在车站的人数。注意初始时 Monocarp 就在车站，所以初始时车站是有 $1$ 个人的。那么每次 `P` 操作我们只需要将 $n$ 增加 $p_i$ 个人即可。

对于 `B` 操作，根据题目描述，如果在除 Monocarp 以外的所有人都上车了，而且车上还有空位置，那么 Monocarp 就可以上车，此时输出 `YES`，否则输出 `NO`。**注意：就算 Monocarp 能上车，他也不会真的上车。**

那么，在这辆车走了以后，有两种情况：

1. 把除 Monocarp 以外的所有人都运走了：此时 $n$ 就会变为 $1$，也就是减少 $n-1$。

2. 将这辆车坐满了，但车站除 Monocarp 外还有没上车的人：此时运走了 $b_i$ 人，所以让 $n$ 减少 $b_i$。

不难可以看出，减少的就是 $\min(n-1,b_i)$。那么这个问题到这里就完成了。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    int n = 1; //当前人数
    while(t--) {
        char opt; int x; cin >> opt >> x;
        if(opt == 'P') n += x;
        else {
            cout << (n <= x ? "YES" : "NO") << endl;
            n -= min(n-1,x);
        }
    }
    return 0;
}

---

## 作者：_xguagua_Firefly_ (赞：0)

### 分析

Monocarp 能上车，当且仅当来了一辆车，并且剩余人数减去车上空位小于 $0$。所以，对于每个 $P$ 操作，增加剩余人数的数量，对于每个 $B$ 操作，先将剩余人数减去空位，若剩余人数小于 $0$，则可以上车，否则不行。

### Code

[AC 记录](https://codeforces.com/contest/2038/submission/292161706)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,cnt,x,p;
char c;
signed main()
{
    scanf("%lld",&n);
    for(int i = 1;i <= n * 2;i++)
    {
        scanf("%c%lld",&c,&x);
        if(c == 'P')
            p += x;
        else if(c == 'B')
        {
            p = p - x;
            if(p >= 0)
                printf("NO\n");
            else
                printf("YES\n");
            p = ((p > 0) ? p : 0);
        }
    }
}
```

---

## 作者：JoeZYQ (赞：0)

### 思路
用一个计数器统计当前等车的总人数，随后按照题意模拟即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
main(){
   	int T,sum=0;
   	cin>>T;
   	while(T--){
   		char c;
   		cin>>c;
   		int x;
   		cin>>x;
   		if(c=='P')sum+=x;
   		else{
   			if(sum<x){
   				cout<<"YES\n";
   				sum=x;
   			}
   			else cout<<"NO\n";
   			sum-=x;
   		}
   	}
}
```

---


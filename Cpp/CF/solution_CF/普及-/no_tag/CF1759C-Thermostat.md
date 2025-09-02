# Thermostat

## 题目描述

Vlad came home and found out that someone had reconfigured the old thermostat to the temperature of $ a $ .

The thermostat can only be set to a temperature from $ l $ to $ r $ inclusive, the temperature cannot change by less than $ x $ . Formally, in one operation you can reconfigure the thermostat from temperature $ a $ to temperature $ b $ if $ |a - b| \ge x $ and $ l \le b \le r $ .

You are given $ l $ , $ r $ , $ x $ , $ a $ and $ b $ . Find the minimum number of operations required to get temperature $ b $ from temperature $ a $ , or say that it is impossible.

## 说明/提示

In the first example, the thermostat is already set up correctly.

In the second example, you can achieve the desired temperature as follows: $ 4 \rightarrow 10 \rightarrow 5 $ .

In the third example, you can achieve the desired temperature as follows: $ 3 \rightarrow 8 \rightarrow 2 \rightarrow 7 $ .

In the fourth test, it is impossible to make any operation.

## 样例 #1

### 输入

```
10
3 5 6
3 3
0 15 5
4 5
0 10 5
3 7
3 5 6
3 4
-10 10 11
-5 6
-3 3 4
1 0
-5 10 8
9 2
1 5 1
2 5
-1 4 3
0 2
-6 3 6
-1 -4```

### 输出

```
0
2
3
-1
1
-1
3
1
3
-1```

# 题解

## 作者：xiaomuyun (赞：4)

- [Luogu 传送门](https://www.luogu.com.cn/problem/CF1759C)
- [CodeForces 传送门](https://codeforces.com/contest/1759/problem/C)

## 思路分析

### 1. 无解条件

不难发现，如果以下条件满足，那么答案就是无解：

$$
\begin{cases}a-l<x\\r-a<x\end{cases}
$$

就是说，温度一开始在 $a$，但是不论是下调还是上调温度，都做不到可以调 $\ge x$ 度的。

以此类推，如果以下条件满足，那么答案也是无解：

$$
\begin{cases}b-l<x\\r-b<x\end{cases}
$$

和上面同理。

### 2. 可以 $1$ 步或 $0$ 步到达

如果 $a=b$，则输出 $0$；如果 $|a-b|\ge x$，则输出 $1$。

因此，后面的其他情况中，$|a-b|$ 均 $<x$。

### 3. $2$ 步到达

如果最少可以 $2$ 步从温度 $a$ 到达温度 $b$ 的话，那么方案肯定是先将 $a$ 调低到 $l$ 再升高到 $b$，或者如果往下调满足不了调节的温度 $\ge x$ 的情况的话，就将 $a$ 调高到 $r$ 再降低到 $b$。

### 4. $3$ 步到达

如果 $2$ 步到达的两种做法都因为 $\ge x$ 的条件走不了的话，就只能先降低到 $l$ 再升高到 $r$ 最后降低到 $b$，或者先升高到 $r$ 再降低到 $l$ 最后升高到 $b$。因为 $-1$ 的情况前面已经判断过了，所以这种做法一定可行。

## 代码实现

```cpp
#include<cstdio>
#include<cmath> 
using namespace std;
int t,l,r,x,a,b;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d%d",&l,&r,&x,&a,&b);
		if(a==b) printf("0\n");
		else if(abs(a-b)>=x) printf("1\n");
		else if((b-l<x&&r-b<x)||(a-l<x&&r-a<x)||r-l<x) printf("-1\n");
		else if((r-a>=x&&r-b>=x)||(a-l>=x&&b-l>=x)) printf("2\n");
		else printf("3\n");//最多就是 3 步，读者可自行思考证明
	}
	return 0;
}
```

---

## 作者：Cczzyy20150005 (赞：2)

赛时这题我30分钟才过，不过思路比较简单。
## 思路
可以证明，只要可达，必定在三步之内就能得到答案。

于是我们分成多种情况讨论：

1. $a=b$，步数为 $0$。
2. $\lvert a-b \rvert \ge x$，直接走，步数为 $1$。
3. 当 $a$ 能直接到左边界，且左边界能直接到 $b$ 时，只要走 $2$ 步。
4. 当 $a$ 能直接到右边界，且右边界能直接到 $b$ 时，只要走 $2$ 步。
5. 当 $a$ 能到左右边界的任意一个，且 $b$ 也能到左右边界的任意一个时，步数为 $3$。
6. 其他情况不可达。

### 一点细节
- 注意判断的优先级。
- 可以直接用 $f1$，$f2$ 分别表示 $a$ 能否到左右边界，这样会简洁一些。

## code

```cpp
#include<bits/stdc++.h>
#define inbt int
#define itn int
#define Int int
#define sacnf scanf
#define scnaf scanf
#define scafn scanf
#define pritnf printf
#define ciN cin
#define fior for
#define foir for
using namespace std;
int l,r,x,a,b;
void solve(){
	cin>>l>>r>>x>>a>>b;
	int f1=((a-x)>=l),f2=((r-x)>=a);//标记a能否直达左右边界
	if(a==b)puts("0");//第1种情况
	else if(abs(a-b)>=x)puts("1");//第2种情况
	else if(f1&&l+x<=b)puts("2");//第3种情况
	else if(f2&&r-x>=b)puts("2");//第4种情况
	else{
		if(!f1&&!f2)puts("-1");//不可达
		else if(!((b-x)>=l||((r-x)>=b)))puts("-1");//不可达
		else puts("3");//第5种情况
	}
}
int main(){
	int t;cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1759C)

由题意可知，记答案为 $ans$，则 $ -1\leq ans \leq 3$，我们只需判断一下各种情况即可。

- 当 $a=b$ 时，$ans=0$。

- 当 $a$ 可以一步到 $b$ 时**即** $|a-b| \geq x$  时，$ans=1$。

- 当 $a$ 可以到左边界，左边界可以到 $b$ 时**即**  $|a-l| \geq x$ 且 $|l-b| \geq x$ 时，$ans=2$。

- 同理，当 $a$ 可以到右边界，右边界可以到 $b$ 时**即** $|a-r| \geq x$ 且 $|r-b| \geq x$ 时，$ans=2$。

- 当 $a$ 到不了左边界和右边界时**即** $|a-r| < x$ 且 $|a-l| < x$ 时，$ans=-1$。

- 同理，当 $b$ 到不了左边界和右边界时**即** $|b-r| < x$ 且 $|b-l| < x$ 时，$ans=-1$。

- 如果都不满足则 $ans=3$。

上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,l,r,x,a,b;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>l>>r>>x>>a>>b;
		if(a==b){cout<<0<<endl;continue;}
		if(abs(a-b)>=x){cout<<1<<endl;continue;}
		if(abs(a-l)>=x&&abs(l-b)>=x){cout<<2<<endl;continue;}
		if(abs(a-r)>=x&&abs(r-b)>=x){cout<<2<<endl;continue;}
		if((abs(a-r)<x&&abs(a-l)<x)||(abs(b-r)<x&&abs(b-l)<x)){cout<<-1<<endl;continue;}
		else {cout<<3<<endl;continue;}
	}
	return 0;
}
```


---

## 作者：sz_jinzikai (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1759C) [CF传送门](https://codeforces.com/contest/1759/problem/C)

# 思路

1. $a$ 本来就等于 $b$，直接输出 $0$。
2. $|a-b|\ge x$，能直接一步到位，输出 $1$。
3. $a$ 可以直接到 $l$，$l$ 也可以直接到 $b$，则可以先从 $a$ 到 $l$，再从 $l$ 到 $b$，需要变 $2$ 次，$r$ 也同理。
4. 如果 $a$ 到不了 $l$ 或 $r$，或者说 $b$ 到不了 $l$ 或 $r$，则无解，输出 $-1$。
5. 剩下的就是 $3$ 步走了，也就是从 $a$ 到 $l$，再从 $l$ 到 $r$，最后从 $r$ 到 $b$，反之同理。

# 代码

```cpp
# include <bits/stdc++.h>
using namespace std;
int l, r, x, a, b, t;
bool f1, f2;
int main () {
	ios::sync_with_stdio (0); //三行快读
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> l >> r >> x >> a >> b;
		f1 = ((a - x) >= l), f2 = ((r - x) >= a); //预处理好能否从 a 到边界，b同理
		if (a == b) //第 1 种
			cout << "0\n";
		else if (abs (a - b) >= x) //第 2 种，注意绝对值
			cout << "1\n";
		else if (f1 && l + x <= b || f2 && r - x >= b) //第 3 种
			cout << "2\n";
		else if (! f1 && ! f2 || (b - x) < l && (r - x) < b) //第 4 种
			cout << "-1\n";
		else //第 5 种
			cout << "3\n";
	}
	return 0;
}
```

---

## 作者：cff_0102 (赞：0)

首先判断 $a$ 能不能直接一步（或者零步）到 $b$。如果可以，直接输出 $1$（或者是 $0$）。

要是不行，继续判断。

每一次移动最多到左右边界，所以如果在开始的 $a$ 处要到 $b$ 处，需要满足 $a$ 和 $b$ 都有能力到达边界。可以先记录它们都能到哪个边界，再进行分类讨论。

假设 $a_l,a_r$ 表示 $a$ 到达 $l,r$ 是否可行，$b_l,b_r$ 表示从 $l,r$ 到达 $b$ 是否可行。如果：

- $a_l=b_l=1$ 或 $a_r=b_r=1$ 时，$a$ 可以两步到 $b$，也就是通过先到一次 $l$ 或 $r$ 边界，再到一次 $b$ 就行了。
- 否则，当 $a_l=0,a_r=1$（此时 $b_l=1,b_r=0$）或相反（此时 $b_l=0,b_r=1$）时，可以通过先走到 $r$ 再到 $l$ 再回到 $b$（或相反的路径），就能三步到达。容易证明，如果 $l,r$ 不能互通，只有可能是下面的情况。
- 剩下的情况，只有 $a_l=a_r=0$ 或 $b_l=b_r=0$。此时你根本无法移动，所以输出 `-1`。

```cpp
#include<bits/stdc++.h>
using namespace std;
int cff_0102 = 542457;
int main(){
	int t;
	cin>>t;
	while(t--){
		int l,r,x,a,b;cin>>l>>r>>x>>a>>b;
		if(a==b){cout<<"0\n";continue;}//不用动
		if(abs(a-b)>=x){cout<<"1\n";continue;}//一次直达
		bool al=(a-l>=x),ar=(r-a>=x);
		bool bl=(b-l>=x),br=(r-b>=x);//见上面分析
		if(((al==bl)&&(bl==1))||((ar==br)&&(br==1))){
			cout<<"2\n"; //先到其中一边再回到 b
			continue;
		}if(((al==0)&&(ar==0))||((bl==0)&&(br==0))){
			cout<<"-1\n";//无解 
			continue;
		}cout<<3<<endl;//剩下的最后一种情况
	}
	return 0;
}
```


---

## 作者：lrmlrm_ (赞：0)

## 题意

一共有 $t$ 组数据，每组数据有 $l,r,x,a,b$ 五个数，如果要把 $p$ 变成 $q$，就要满足 $ \left|p-q\right|\geq x$ 且 $l\leq q\leq r$。问把 $a$ 变成 $b$ 最少要用多少步。

## 思路

这道题是一道分类讨论题 ：

+ 当 $ a=b $ 时，$0$ 步可以直接到达。

+ 当 $x\leq\left|a-b\right|$ 时，$1$ 步可以直接到达。（题目保证 $l\leq a,b\leq r$）

+ 当 $a$ 可以到最左边界，并且 $b$ 也可以到最左边界时，也就是 $a-x\geq l$ 并且 $b-x\geq l$，同理 $a$ 可以到最右边界，并且 $b$ 也可以到最右边界时，也就是 $a+x\leq r$ 并且 $b+x\leq r$ 时 $2$ 步就可以到达。

+ 当 $a$ 能到左或右边界，且 $b$ 能到另一边界，且左边界能到右边界时，$3$ 步可以到达。（先到左或右边界，再到另一边界，最后到 $b$）也就是 $a-x\geq l$ 或者 $r\geq a+x$ 并且（此处并且的优先级是最低的）$b-x\geq l$ 或者 $r-x\geq b$，$3$ 步可以到达。

+ 其他情况无解，输出 $-1$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,l,r,x,a,b;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d%d",&l,&r,&x,&a,&b);
		if(a==b)printf("0");
		else if(abs(a-b)>=x)printf("1");
		else if((a-x>=l&&b-x>=l)||(a+x<=r&&b+x<=r))printf("2");
		else{
		    if((a-x>=l||r>=a+x)&&(b-x>=l||r-x>=b))printf("3");
			else printf("-1");
		}
		printf("\n");
	}
	return 0;
} 
```

---

## 作者：white_carton (赞：0)

[$\color{#52C41A}\text{题目传送门}$](https://www.luogu.com.cn/problem/CF1759C)

[$\color{#52C41A}\text{更好的体验}$](https://www.luogu.com.cn/blog/ulbinksennns/cf1759c-thermostat-ti-xie)

---
### 思路

首先我们可以证明：答案肯定小于 $3$ 。因为答案最大是从 $a$ 到某一边界再到另一边界再到 $b$ ,如果这种方法都不行肯定无解。

接下来分类讨论， $a=b$ 时，输出 $0$ 。

$a$ 能直接到 $b$ 时，也就是 $\left|a-b\right|\ge x$ 时，答案为 $1$ 。

如果最少 $2$ 步到达，那肯定是先从 $a$ 降到某端点再到 $b$ ，所以需要$\left|a-l\right|,\left|b-l\right|\ge x$ 或 $\left|a-r\right|,\left|b-r\right|\ge x$。

最后就是 $3$ 步到达的情况，就是从 $a$ 到某端点，再到另一端点，最后到 $b$ ，需要  $\left|a-l\right|,\left|r-l\right|,\left|r-b\right|\ge x$ 或 $\left|a-r\right|,\left|r-l\right|,\left|l-b\right|\ge x$ 。

如果上面 $4$ 种情况都不行，就输出 $-1$

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cout.tie();
	int t;
	cin>>t;
	while(t--){
		int x,l,r,a,b;
		cin>>l>>r>>x>>a>>b;
		if(a==b){
			cout<<0<<endl;
			continue;
		}
		if(abs(a-b)>=x){
			cout<<1<<endl;
			continue;
		}
		if(abs(l-b)>=x&&abs(l-a)>=x)
		{
			cout<<2<<endl;
			continue;
		}
		if(abs(r-b)>=x&&abs(r-a)>=x)
		{
			cout<<2<<endl;
			continue;
		}
		if(abs(r-a)>=x&&abs(l-r)>=x&&abs(l-b)>=x)
		{
			cout<<3<<endl;
			continue;
		}
		if(abs(l-a)>=x&&abs(l-r)>=x&&abs(r-b)>=x)
		{
			cout<<3<<endl;
			continue;
		}
		cout<<-1<<endl;
	}
	return 0;
}
/*
1.是否需要开long long！开long long空间是否足够！！！
2.禁止摆烂！禁止摆烂！禁止摆烂！！！
3.该打的暴力一定要打！！！不能打暴力也要打随机！！！
警钟撅烂！！！
*/
```

---

## 作者：隐仞Mrsu (赞：0)

# 分析
### 当 $a=b$ 时
此时两点已经重合，无需操作，答案为 $0$。

### 当 $\vert a-b\vert \ge x$ 时
满足操作条件，通过一次操作即可达到要求，答案为 $1$。

### 当 $\vert l-b\vert <x$ 且 $\vert r-b\vert <x$ 时
即 $b$ 无法通过边界 $l,r$ 调到，所以区间内所有值都不能通过操作调整到 $b$，答案为 $-1$。

### 考虑剩下的情况
要使得操作能够进行，$\vert a-b\vert$ 应该要足够大。

于是，不妨先把 $a$ 的值移到边界 $l,r$ 上，判断此时能否触发条件进行操作，将其值调整到 $b$ 上，如果能，答案为 $2$；否则跳到另一端的边界上，再次判断能否在这端的边界将其值调整为 $b$，如果能，答案为 $3$，否则不更新答案。

对两个边界进行模拟，并更新答案，取各情况的**最小值**为最终答案。通过上述模拟，若无论怎么调整都无法将其值调整到 $b$ 上的，答案为 $-1$。

# 代码
```cpp
#include<bits/stdc++.h>
#define LL long long 
using namespace std;
LL _,l,r,x,a,b;
void work(){
	cin>>l>>r>>x>>a>>b;
	if(a==b){
		cout<<"0\n";
		return;
	}
	if(abs(a-b)>=x){
		cout<<"1\n";
		return;
	}
	LL lb=abs(l-b),rb=abs(r-b);
	if(lb<x&&rb<x){
		cout<<"-1\n";
		return;
	}
	LL res=6;//初始值大于3，用于后续判断
	if(abs(l-a)>=x){
		if(abs(l-b)>=x){
			res=2;
		}
		else{
			res=3;
		}
	}
	if(abs(r-a)>=x){
		if(abs(r-b)>=x){
			res=2;
		}
		else{
			res=res<3?res:3;
		}
	}
	if(res>3)cout<<"-1\n";
	else cout<<res<<'\n';
}
int main(){
	ios::sync_with_stdio(false);
	cin>>_;
	while(_--){
		work();
	}
} 
```


---

## 作者：Engulf (赞：0)

分类讨论题。

设最小操作次数为 $t$。

可以证明，$t \in [-1, 3]$。

1. 当 $a = b$ 时，$t = 0$。
2. 当 $|a - b| \ge x$ 时，$t = 1$（可以一步到位）。

上面两种情况很好想吧。

如果不能一步呢？

摆在我们面前的有 4 条道路：

- $a \rightarrow l \rightarrow b$（$t = 2$）
- $a \rightarrow r \rightarrow b$（$t = 2$）
- $a \rightarrow l \rightarrow r \rightarrow b$（$t = 3$）
- $a \rightarrow r \rightarrow l \rightarrow b$（$t = 3$）

当然条件是上面任意一个转移的 $u \rightarrow v$ 都得满足 $|u - v |\ge x$。

如果上述路径均不可行，一定无解，能到达的最值 $l, r$ 都无解，由绝对值的几何意义得，在 $(l, r)$ 内的数也一定无解。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main()
{
	int tt;
	cin >> tt;
	while (tt -- )
	{
		LL l, r, x, a, b;
		cin >> l >> r >> x >> a >> b;
		int ans = 0;
		if (a == b) ans = 0;
		else if (abs(a - b) >= x) ans = 1;
		else
		{
			if (abs(a - l) >= x && abs(l - b) >= x) ans = 2;
			else if (abs(a - r) >= x && abs(r - b) >= x) ans = 2;
			else
			{
				if (abs(a - l) >= x && abs(l - r) >= x && abs(r - b) >= x) ans = 3;
				else if (abs(a - r) >= x && abs(r - l) >= x && abs(l - b) >= x) ans = 3;
				else ans = -1;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---


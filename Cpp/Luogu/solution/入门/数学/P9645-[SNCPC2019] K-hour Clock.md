# [SNCPC2019] K-hour Clock

## 题目描述

一个 $k$ 小时制的时钟是一种计时方法，遵循以下规则：

- 一天被分为 $k$ 小时，其中第 $i$ 小时称为 $(i-1)$ 点；
- 如果现在是 $x$ 点，那么在 $1$ 小时后将是 $(x+1)$ 点，前提是 $0 \le x < k - 1$；
- 如果现在是 $(k - 1)$ 点，那么在 $1$ 小时后将是 $0$ 点。

我们知道现在是 $x$ 点，经过 $y$ 小时后将是 $z$ 点。求 $k$ 的值。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
11 18 5
3 49 4
1 9 1
1 3 10```

### 输出

```
12
24
3
-1```

# 题解

## 作者：RedStoneShark (赞：6)

[SNCPC2019] K-hour Clock题解

### 思路：分类讨论

 - 如果 $x+y=z$，那么任何 $k>z$ 都可以。
 
 - 如果 $y \le z$，那么就不能从 $x$ 到 $z$。
 
 - 如果 $x+y\le z \times 2$，那么不能过一天后到达 $z$ 点。
 
 - 否则就都输出 $x+y-z$，表示只过了一天，或者还不到一天。
 
 
### 那么，代码就很简单了：
 ```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int, int> PII;
signed main() {
	const int mod = 1e9 + 7;
	int T;
	cin >> T;
	while (T--) {

		int x, y, z;
		cin >> x >> y >> z;
		int cha = x + y - z;
		if (!cha)
			cout << z + 1 << endl;
		else if (y <= z || x + y <= z + z)
			cout << -1 << endl;
		else cout << cha << endl;
	}

	return 0;
}
 
 ```
 ~~这题为什么只有满分五十啊喂~~~

---

## 作者：luan341502 (赞：4)

签到题。~~但是挂了一发~~

题意很简单，选择一个模数 $p > x,z$，使得 $x+y\equiv z \pmod p $。

考虑当 $x+y < z$ 时，显然不满足条件，无法使其到达 $z$。

再满足 $p > x,z$，若 $y\le z$ 或 $x+y-z\leq z$ 时也不满足条件。

其余情况直接选择 $x+y-z$ 作为模数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,z;
int main(){
	int t;
	cin>>t;
	while(t--){
		scanf("%d%d%d",&x,&y,&z);
		if(x+y-z<0) puts("-1");
		else if(x+y==z) cout<<z+1<<endl;
		else{
			if(x+y-z<=x||x+y-z<=z) puts("-1"); 
			else printf("%d\n",x+y-z);
		}
	}
	return 0;
}
```


---

## 作者：small_john (赞：3)

## 题目大意

给定三个数 $x,y,z$，求一个数 $k$ 使得 $x+y\equiv z\pmod k$。

## 思路

简单的分类讨论题。

1. $x+y=z$：说明只要 $k>z$ 即可取到 $z$，输出 $z+1$；
2. $x+y\ne z$：由于 $x+y\equiv x+y-k\pmod k$，所以一般来说，模数 $k$ 最大为 $x+y-z$。但要记得特判不合法的情况：$x,z$ 的取值范围应该是 $0\sim k-1$，所以当任意一个大于等于 $k$ 的时候，就不合法。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T> void write(T x)
{
	if(x<0) x = -x,putchar('-');
	if(x<=9) return putchar(x+48),void();
	write(x/10);
	putchar(x%10+48);
}
template<typename T> void writen(T x)
{
	write(x);
	puts("");
}
int t;
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(t);
	while(t--)
	{
		int x,y,z;
		read(x),read(y),read(z);
		if(x+y==z)//注意放前面
		{
			writen(z+1);
			continue;
		}
		int k = x+y-z;
		if(k<=x||k<=z) k = -1;//不合法
		writen(k);
	}
 	return 0;
}
```

---

## 作者：InversionShadow (赞：1)

+ $x+y \neq z$ 时，$k$ 肯定会大于 $z+1$，因为求任意解，输出 $z+1$ 即可。

当 $x+y=z$ 时：

设 $a=x+y-z$。就是说，$x$ 过去 $y$ 时是 $(x+y)$ 时，但 最后是 $z$，那么 $k$ 就有可能等于 $(x+y)-z$，因为 $x+y-(x+y-z)=z$。

+ $a \le x$ 或 $a \le y$，$k$ 不肯能会小于题目输入的起始时间或结束时间，输出 `-1`。

否则输出 $a$ 即可。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int x, y, z, t; 

void solve() {
  cin >> x >> y >> z;
  cout << (x + y != z ? (x + y - z <= x || x + y - z <= z ? -1 : x + y - z) : z + 1) << '\n';
}

signed main() {
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P9645)

# 题目大意

一种 $k$ 小时钟是一种日常时间表示方法，遵循以下规则：

- 一天被分为 $k$ 个小时，第 $i$ 个小时为 $(i-1)$ 点钟；
- 如果现在是 $x$ 点钟，那么经过 $1$ 小时后将是 $(x+1)$ 点钟，如果 $0 \le x < k - 1$；
- 如果现在是 $(k - 1)$ 点钟，那么经过 $1$ 小时后将是 $0$ 点钟。

我们知道现在是 $x$ 点钟，经过 $y$ 小时后将是 $z$ 点钟。求 $k$ 的值是多少。

# 题目解法

这个题目要求你根据一种时间表示方法，找出每个测试用例中 $k$ 的值。给定的时间表示方法是一个 $k$，它遵循 $3$ 个规则。题目给出了 $x$、$y$ 和 $z$，表示现在是 $x$ 点钟，经过 $y$ 小时后将会是 $z$ 点钟。求 $k$ 的值，或者如果无法确定 $k$ 的值，则输出 ```-1```。

须注意的是，$x+y=z$ 要在最开始判断。

所以代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int T;cin>>T;
	while(T!=0){
		T--;
		int x,y,z;cin>>x>>y>>z;
		if(x+y==z)cout<<z+1<<endl; 
		else if(x+y-z<0||x+y-z<=x||x+y-z<=z)cout<<-1<<endl; 
		else cout<<x+y-z<<endl;
	}
	return 0;
}
 

```

---

## 作者：封禁用户 (赞：1)

分类判断即可。

若 $x + y = z$，那么比 $z$ 大的任何数都是解，输出 $z + 1$ 即可；

若 $x + y > z$ 则说明至少过了一天，若 $k$ 不大于 $z$ 则说明无解，输出 `-1` ，$k$ 越大越好，则输出 $y - (z - x)$；

若 $x > z$ 则说明 $x$ 跨过了 $0$ 点，那么 $y$ 必须大于 $z$，如果成立则输出 $x + (y - z)$。

若都不满足也属于无解，输出 `-1` 。

```cpp

#include <bits/stdc++.h>
using namespace std;

void solve() 
{
    int x, y, z; 
    cin >> x >> y >> z;
    if (x + y == z) cout << z + 1 << endl;
    else if (x <= z && x + y > z) 
    {
        int k = y - (z - x);
        if (k > z) cout << k << endl;
        else cout << -1 << endl;
    }
    else if (x > z && y > z) cout << x + (y - z) << endl;
    else cout << -1 << endl;
}

int main() 
{
    int n; 
    cin >> n;
    while (n--) solve();
    return 0;
}

```

---

## 作者：Xdwjs (赞：0)

**设“现在的时间”为 $x+y$，“时钟上的时间”即为 $z$。**

- 当 $x+y<z$ 时：

因为 $k$ 不可能大于等于 $z$，所以时间绝对到不了 $z$。

- 当 $x+y=z$ 时：

时间显然正好，但当时间正好等于 $k$ 时会直接变成 $0$，所以我们可以直接输出 $z+1$。

这里有个特判：我们的输出不能大于 $2\times10^9$，也就是如果 $x$ 和 $y$ 都正好等于上限 $10^9$ 时，无解。

- 当 $x+y>z$ 时：

我们认为时针转了一圈多一点后才得到了“时钟上的时间”。这“一点”是时针现在指向的时间，即 $z$；“一圈”即为时针转动的总长度减去上文中的“一点”，即 $x+y-z$。

然而这里还有个特判：时针也有可能转了两圈多一点、三圈多一点，但很显然转的圈数越多，一圈的长度越小，所以上面得出的结果是所有解中的最大解。如果这个结果仍然小于等于 $x$ 或 $z$，无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		if(x+y<z||(x+y==z&&x==1000000000&&y==1000000000)||(x+y>z&&x+y-z<=max(x,z))) cout<<-1<<endl;
		else if(x+y==z) cout<<z+1<<endl;
		else cout<<x+y-z<<endl;
	}
	return 0;
}
```


---

## 作者：skyskyCCC (赞：0)

## 前言。
一道基本的计算题。
## 分析。
题意：给定 $T$ 个数据，现在有一个 $k$ 小时的表，现在**钟表上**是 $x$ 小时，再过 $y$ 个小时后，时钟就到了 $z$ 小时，求一个可能的 $k$ 的值，若无解则输出 ```-1```。

分类讨论： 
- 若 $x+y=z$：很显然 $x+y$ 没有超过 $k$ 的情况。所以 $x+y<k$ 即 $z<k$ 所以直接令 $k=z+1$ 即可。
- 若 $y \leqslant z$ 且 $x+y \neq z$：则说明不能从 $x$ 点到达 $z$ 点。我们可以令 $k=z$ 则若 $y<z$ 导致本来加上都到不了 $z$ 点却又借给 $x$ 到 $k$ 的点数，所以更无法到达 $z$ 点。若 $y=z$ 则若 $x=0$ 就可以到达，但偏偏 $x>0$ 导致超过了 $z$ 点。 
- 若 $x+y \leqslant z+z$：则说明过一天后仍然不能到达 $z$ 点。
- 其余情况直接输出 $x+y-z$ 即可，因为我们可以当做只过了一天，或者还不到一天。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
long long t,x,y,z;
int main(){
	cin>>t;
	while(t--){
		cin>>x>>y>>z;
		if(x+y-z==0){
			cout<<z+1<<"\n";
		}
		else if(y<=z||x+y<=z*2){
			cout<<"-1\n";
		}
		else cout<<x+y-z<<"\n";
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：SDLTF_凌亭风 (赞：0)

来自某不愿意透露姓名的队友。

---
比较签到，但是 corner case 比较多。

很明显能看出是一个模加法，也即 $x+y$ 与 $z$ 在某一个模数下等价，或者说 $x+y-z$ 是某个模数的倍数。 如果是正的我们很明显可以直接把模数设为 $x+y-z$ 来判断，但是并不一定是正的，所以要对这个值进行讨论。

如果 $x+y-z=0$ 的话，相当于不需要模这个也成立，直接把模数设成 $z+1$ 就可以了。

接下来的话，首先模数必然是 $x+y-z$ 的一个倍数，肯定不大于 $x+y-z$，但是又需要 $x$ 和 $z$ 小于模数，所以如果 $x+y-z\leq\max(x,z)$ 的时候显然不成立。

其他情况直接把模数设成 $x+y-z$ 就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
ll test,x,y,z,t;
inline ll read()
{
	register ll num=0,neg=1;
	register char ch=getchar();
	while(!isdigit(ch)&&ch!='-')
	{
		ch=getchar();
	}
	if(ch=='-')
	{
		neg=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		num=(num<<3)+(num<<1)+(ch-'0');
		ch=getchar();		
	}
	return num*neg;
}
inline void solve()
{
	x=read(),y=read(),z=read(),t=x+y-z;
	if(t==0)
	{
		return (void)printf("%d\n",z+1);
	}
	if(t<=max(x,z))
	{
		return (void)puts("-1");
	}
	printf("%d\n",t);
}
int main()
{
	test=read();
	for(register int i=1;i<=test;i++)
	{
		solve();
	}
}
```


---

## 作者：myyyIisq2R (赞：0)

## [P9645 SNCPC2019 K-hour Clock](https://www.luogu.com.cn/problem/P9645)

### Solution
按题意推结论，易得答案的情况有可能为 $x + y - z$，一般情况下直接输出该结果即可，下面讨论几种特殊情况：

1. $x + y = z$ 时：出现该情况即没有显示出周期 $k$ 的可能情况。举个例子，$\text{1 3 4}$ 这种情况下我们并不知道周期可能是多少，直接输出一个超大数即可（不能超过 $10^9$）。

2. $x + y - z \leq  x$ 或 $x + y - z  \leq z$ 时：举个例子，$\text{2 5 4}$ 按照结论算出来 $k = 3$，但当 $k = 3$ 时 $z$ 就不应为 $4$ ，应进行进位，不符合题意，因此这里输出 $-1$。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int T;
    cin>>T;

    while(T--){
        int x,y,z;
		cin>>x>>y>>z;
        int ans=x+y-z;
        if(x+y==z)
		{
            cout<<(int)1e9-1<<endl;  //输出小于1e9的极大值
            continue;
        }
        if(ans<=x||ans<=z) //情况不可能存在
		{
			puts("-1"); 
			continue;
		}
        cout<<ans<<endl;
    }
}
```

---


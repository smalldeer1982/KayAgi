# 「PEOI Rd1」Morning or Afternoon

## 题目描述

有一个可用转盘显示日期的指针闹钟，我从一个时刻观测到了另一个时刻（闭区间），现在我想知道我是否一定可以通过判断这期间日期的变化情况来推断出现在是上午还是下午。

闹钟在上午 $12:00$ 准时更新日期。

上午/下午 $11:59$ 后的时刻为 下午/上午 $12:00$，上午/下午 $12:59$ 后的时刻为 上午/下午 $1:00$。

## 说明/提示

### 样例解释#1
因为我从 $11:30$ 看到了 $12:20$（假设 $12:20$ 是第一次观测到；后面的 $12:20$ 的上下午情况可以根据现在的情况推出，因为我知道右端点的 $12:20$ 是第几次观测到），我可以通过判断这期间日期有没有变化来判断这个时刻是上午还是下午。比如，我看到这段时间里闹钟更新了日期，那么 $12:20$ 一定是上午；反之 $12:20$ 一定是下午。

样例#3 同理。
### 样例解释#2
有可能是上午 $12:20$ 到上午 $5:00$，也有可能是下午 $12:20$ 到下午 $5:00$，这两种情况日期都不可能发生改变，所以我无法判断。

### 数据范围
对于 $18\%$ 分数的数据，所有时刻保证不会出现 小时数 $=12$ 的情况（即不会出现 `12:25` 类型的时刻）。

对于另外 $9\%$ 分数的数据有 $T=1$。$\color{#fff}\sout\text{不可以，总司令！}$

对于 $100\%$ 的数据 $T\leqslant 100$，$\overline\texttt{ab}\in[1,12]$，$\overline\texttt{cd}\in[0,59]$。

## 样例 #1

### 输入

```
7
11:30 12:20
12:20 5:00
11:45 1:04
12:10 12:59
1:09 8:01
12:00 1:00
12:00 12:00```

### 输出

```
Yes
No
Yes
No
No
No
No```

# 题解

## 作者：MasCotangent (赞：6)

# P9222 「PEOI Rd1」Morning or Afternoon 题解
[题目传送门](https://www.luogu.com.cn/problem/P9222)

------------

这题的难点在于题面弯弯绕绕，不好理解~~当然如果大佬秒懂当我没说~~。所以我们需要**形式化题意**。
## 形式化题意
- 题目有多测。
- 对每一组测试数据，给出两个十二小时制时间，且你能知道这两个时间之间日期共变化了多少次，问你是否能判断是上午还是下午。
- 对每一组数据，能判断，输出 `Yes`，否则输出 `No`。然后换行。
- 特别的，没有形如 $00 : 14$ 的时间，而是以 $12 : 14$ 取而代之。
## 思路
这道题看似是逻辑难题，实则徒有其表。因为如下三点。  
1. 如果开始时间于十二小时意义下晚于结束时间，则必然可以判断。
2. 否则，不能判断。
3. 容易证明我们实际上不用考虑日期的变化。

思路有了，还有一个注意点。由于形如 $12:34$ 的时间属于实际是上午/下午的开始，所以我们要把 $12$ 提前处理为 $0$ 。

于是就能通过此题了，细节详见代码。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int a1,a2,b1,b2,t;
    char c;//用于吸收冒号
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>a1>>c>>a2>>b1>>c>>b2;
        if(a1==12) a1=0;
        if(b1==12) b1=0;//特殊处理
        if(a1>b1||(a1==b1&&a2>b2)) cout<<"Yes\n";//判断开始时间是否“大于”结束时间
        else cout<<"No\n";
    }
    return 0;
}
```


---

## 作者：_GeorgeAAAADHD_ (赞：4)

原题题意:给定两个十二小时制下的时间，求是否可以通过看日期是否变化来判断现在是上午还是下午。

那么很显然，如果开始时间晚于结束时间，则必定可以判断现在是上午还是下午。

还有一个重要的点，就是 `12:00` 时会更改日期。原题题意:给定两个十二小时制下的时间，求是否可以通过看日期是否变化来判断现在是上午还是下午。

那么很显然，如果开始时间晚于结束时间，则必定可以判断现在是上午还是下午。

还有一个重要的点，就是上午 `12:00` 时会更改日期。因此，我们需要将 $12$ 时改为 $0$ 时，这样才能正确地进行判断。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b,c,d;
int main(){
    cin>>t;
    while(t--){
        scanf("%d:%d %d:%d",&a,&b,&c,&d);//格式化读入
        if(a==12)a=0;
        if(c==12)c=0;
        if(a>c||a==c&&b>d)cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}
```

---

## 作者：Mx_sky (赞：1)

[题目传送门。](https://www.luogu.com.cn/problem/P9222)
### 解题思路：
本题采用 $12$ 小时制，因此我们可以将 $12$ 点看成 $0$ 点。

显然，如果我们可以判断是上下午，那么绝对是越过了 $12$ 点的，并且右边界的时间（就是 $c:d$）必须小于左边界的时间（也就是 $a:b$）。

不可以判断的话就不符合上面的某一个条件。
### AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,a,b,c,d;
int main()
{
	std::ios::sync_with_stdio(false);    //无用的优化请，忽略 
    scanf("%d",&T);
    while(T--)
    {
    	scanf("%d:%d %d:%d",&a,&b,&c,&d);    //格式化输入 
    	// 12小时制，a或c=12时需要变成0 
		if(a==12) a=0;    
		if(c==12) c=0; 
		// 根据上面的条件判断 
		if(a>c) printf("Yes\n");
		else if(a==c&&b>d) printf("Yes\n");
		else printf("No\n");
    }
    return 0;
}
```


---

## 作者：AKPC (赞：1)

### 思路
设输入时间为 $a:b$ 和 $c:d$。判断是上午还是下午，只需要判断时间是否更新即可，因为没有更新的话你是不知道现在是上午还是下午的。

不难发现，如果时刻 $a,c$ 不相等，需要判断特殊值，即较大的是否为 $12$，因为除了这种情况我们都是可以判断出时钟更新了时刻。

当 $a,c$ 相等，判断 $b,d$ 的大小关系，不难发现只有在 $b >d$ 的情况下才更新了时刻。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,a,b,c,d;
signed main(){
	cin>>n;
	while (n--){
		scanf("%d:%d %d:%d",&a,&b,&c,&d);
		if (a>c) a==12?puts("No"):puts("Yes");
		else if (a==c) b<=d?puts("No"):puts("Yes");
		else c==12?puts("Yes"):puts("No");
	}
	return 0;
}
```

---

## 作者：hycqwq (赞：1)

## 思路

在生活中，我们经常~~熬到下半夜然后~~发现，在 $11:59$ 之后，居然是 $00:00$！

于是我们把输入的小时转换成 $00 \sim 11$ 之间的数，然后我们看到样例。观察两个时间之间的大小关系。

```text
11:30 > 00:20   Yes
00:20 < 05:00   No
11:45 > 01:04   Yes
00:10 < 00:59   No
01:09 < 08:01   No
00:00 < 01:00   No
00:00 = 00:00   No
```

发现规律：前一个时间比后一个大的，就可以，否则不行。

那这是为什么呢？

只有从上午跨到下午时，时间才会看起来往前走了。所以我们可以通过看在时间从 $11:59$ 变成 $00:00$ 的时刻，日期有没有变化来判断现在是上午还是下午。

注意，观测的时间跨度不会超过一天。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int inf = 0x3f3f3f3f;
#define elif else if
#define il inline

struct tim
{
    int h, m;
    void read()
    {
        scanf("%d:%d", &h, &m);
        if (h == 12)
            h = 0;
    }
};
bool operator<(tim x, tim y)
{
    if (x.h != y.h)
        return x.h < y.h;
    return x.m < y.m;
}
bool operator>(tim x, tim y) {return y < x;}

int t;

int main()
{
    cin >> t;
    while (t--)
    {
        tim x, y;
        x.read(), y.read();
        if (x > y)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
```

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/P9222)

我们可以先把 $12$ 点看做 $0$ 点，先使其符合十二小时制的时间。

接着我们可以发现，如果我们不能判断，那么这两个时刻就一定是既可以同为上午又可以同为下午还可以一个为上午一个为下午。如果我们能判断，那么它就一定一个为上午一个为下午。

我们可以先把这两个时刻化为从 $0$ 点起已经过了的分钟数，一个为 $a$ 一个为 $b$。由于 $a$ 是起始时间， $b$ 是终止时间，所以如果一个时刻与另一个时刻同为上午或下午，那么 $a$ 就要小于或等于 $b$，才能使时间正序从 $a$ 至 $b$。

否则如果情况为 `11:30 1:30` 时，如果 `11:30` 和 `1:30` 同为同一天的上午，那么要从 `11:30` 到 `1:30` 就得时光倒流，往前 $10$ 小时才能到。`11:30` 和 `1:30` 这组数据明显是 $a$ 大于 $b$。所以我们可以得出结论：当 $a>b$ 时，可以判断，否则不能。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
    	int a,b,c,d;
    	scanf("%d:%d%d:%d",&a,&b,&c,&d);
    	if(a==12) a=0;
    	if(c==12) c=0;
    	a=a*60+b,c=c*60+d;
    	if(a>c) puts("Yes");
    	else puts("No");
	}
    return 0;
}
```

---

## 作者：Red0rangE (赞：0)

## 题意理解 & 思路阐述

给出两个时间以 $\overline\texttt{ab}:\overline\texttt{cd}$ 形式表示（$a$ 可省略，这时 $a = 0$），为了方便，我们将这两个时间表示为 $a : b$ 和 $c : d$。

首先如果 $a = 12$，$12 : b$ 其实就是 $00 : b$，为了后续处理方便，我们需要先初始化一下。

是否一定可以通过判断日期的变化情况来推断出上午还是下午，我们可以从无法判断的情况开始思考：如果前一个时间比后一个时间小，那么这既可以在上午也可以在下午，再观察样例发现如果两个时间跨越了 $12 : 00$ 就满足题意，即 $a : b$ 表示的时间在 $c : d$ 之前。

可能有点绕，举几个例子：

$$begin:11:10$$
$$end:12:00$$

此时既可以是上午，也可以是下午。

$$begin:11:10$$
$$end:12:01$$

乍一看第一个时间在第二个之后，但是我们需要对第二个时间进行初始化， 实际上它们跨越了 $12:00$，初始化后得出的结论就完全不同了，这就是我们初始化的作用。

综上所述，题目的本质就是询问前后时间是否跨越 $12:00$，解法即在对时间初始化后判断前后两个时间的前后。

## 代码呈现

```cpp
#include <bits/stdc++.h>
using namespace std;

int a,b,c,d;//时间
int t;

bool cc(int a,int b,int c,int d){//判断时间前后
    if (a>c) return 1;
    else if (a<c) return 0;
    else return b>d;
}

void init(){//初始化
    if (a==12) a=0;
    if (c==12) c=0;
}

signed main(){
    
    scanf("%d",&t);
    while (t--){
        scanf("%d:%d %d:%d",&a,&b,&c,&d);
        init();
        if (!cc(a,b,c,d))
            puts("No");
        else puts("Yes");
    }
    return 0;
    
}
```

希望给位大佬在 $OI$ 和 $whk$ 上齐头并进。

---

## 作者：Double_Light (赞：0)

## P9222 「PEOI Rd1」Morning or Afternoon 题解

### 思路部分

首先，我们将 `12:xx` 的时间转化为 `00:xx`，将 `x:xx` 的时间转化为 `0x:xx`，方便计算。

事实上，题目所说的“更新日期”可以看作是上午变成了下午。那么我们就可以得出，如果开始观测时间的小时数大于截止时间的小时数，那么相当于这个区间内一定更新过一次日期。这样，我们就可以判断现在一定是下午。

否则，我们可以认为观测区间一直在上午，或是一直在下午，所以不能判断现在是上午还是下午。

### 代码部分

```cpp
#include<iostream>
using namespace std;
string a,b;
int t;
int main(){
	cin>>t;
	while(t--){//t组测试数据
		cin>>a>>b;
		if(a.size()==4)a="0"+a;//统一为xx:xx的格式，在小时数前补零
		if(b.size()==4)b="0"+b;
		if(a[0]=='1'&&a[1]=='2')a[0]='0',a[1]='0';//12点转化为0点
		if(b[0]=='1'&&b[1]=='2')b[0]='0',b[1]='0';
		if(a>b)cout<<"Yes";//由于是闭区间，所以用大于号
		else cout<<"No";
		cout<<endl;
	}
	return 0;
} 
```

---


# Polycarp's New Job

## 题目描述

题意简述

维护一个初始为空的点集，支持两种操作：

$+\ x\ y$：向点集中加入$(x,y)$

$?\ h\ w$：查询是否对于点集中的所有点都满足$x  \leq h \&\& y \leq w$或者$x \leq w \&\& y \leq h$

## 样例 #1

### 输入

```
9
+ 3 2
+ 2 3
? 1 20
? 3 3
? 2 3
+ 1 5
? 10 10
? 1 5
+ 1 1
```

### 输出

```
NO
YES
YES
YES
NO
```

# 题解

## 作者：xuchuhan (赞：3)

很容易想到思路的题目。

可以直接将题目操作化成 $x\leq y,h\leq w$ 的形式，然后对于每次询问，判断是否有所有 $x$ 的最大值小于等于 $h$，同时所有 $y$ 的最大值小于等于 $w$。若是，输出 `YES`，否则输出 `NO`。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,maxx,maxy;
int main(){
	cin>>T;
	while(T--){
		char op;
		int x,y;
		cin>>op>>x>>y;
		if(x>y)//方便处理 
			swap(x,y);
		if(op=='+'){
			maxx=max(maxx,x);
			maxy=max(maxy,y);
			//统计最大的x,y 
		}
		else{
			if(maxx>x||maxy>y)
				cout<<"NO\n";
			else
				cout<<"YES\n";
			//判断 
		}
	}
	return 0;
} 
```

---

## 作者：activeO (赞：2)

## 题目大意 

维护一个初始为空的点集，支持两种操作：

$ +\ x\ y$：向点集中加入 (x,y)。

$ ?\ h\ w $：查询是否对于点集中的所有点都满足 $ x \leq h \&\& y \leq w  $ 或者 $ x \leq w \&\& y \leq h $

## 解法

1.如果 $ x > y $，先 $ swap(x,y) $ .

2.记录最大值 maxx 和 maxy，每次询问 如果 $ maxx \leq x  \&\&  maxy \leq y$ 就输出 YES 否则输出 NO。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int main(){
	
	int n,maxx=0,maxy=0;
	
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++){
		char op;
		int x,y;
		scanf(" %c %d %d",&op,&x,&y);
		if(x<y) swap(x,y);//为了方便比较
		if(op=='+'){
			maxx=max(maxx,x);
			maxy=max(maxy,y);//维护最大值
		}else{
			if(maxx<=x&&maxy<=y) puts("YES");//如上文
			else puts("NO");
		}
	}
	
	return 0;
}
```


---

## 作者：decoqwq (赞：2)

两种操作：$1.$添加一个$x\times y$的矩形

$2.$查询之前的所有矩形是否都能放在$h\times w$的方框内

为了方便，如果$x>y$或者$h>w$，都$swap$一下

然后记录添加了的最大的$x,y$，和查询的$h,w$对比，如果$max\_x \leq h$并且$max\_y \leq w$，就是$YES$，否则就是$NO$

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    char opt[4];
    int x,y;
    int maxx=0,maxy=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%s%d%d",opt,&x,&y);
        if(opt[0]=='+')
        {
            if(x>y)
            {
                swap(x,y);
            }
            maxx=max(maxx,x);
            maxy=max(maxy,y);
        }
        else
        {
            if(x>y)
            {
                swap(x,y);
            }
            if(x>=maxx&&y>=maxy)
            {
                printf("YES\n");
            }
            else
            {
                printf("NO\n");
            }
        }
    }
}
```



---

## 作者：__zyq_666_kpzc__ (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1101E)
### 思路分析
每次插入时，我们可以统计一下所有 $x$ 的最大值以及所有 $y$ 的最大值，询问时呢，就让 $h$ 和 $w$ 分别与 $x$ 的最大值，$y$ 的最大值作比较即可，如果符合条件，就说明最大值都小于等于 $h$ 和 $w$，其他的肯定不可能比 $h$ 和 $w$ 大，直接输出；不符合，就说明有不符合条件的点，也直接输出。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
  	int T,ma_x=-1e9,ma_y=-1e9;
	cin>>T;
	while(T--){
		char ID;
		cin>>ID;
		int x,y;
		cin>>x>>y;
		if(ID=='+'){
			ma_x=max(ma_x,max(x,y));
			ma_y=max(ma_y,min(x,y));
		}
		else{
			if(ma_x<=x&&ma_y<=y)cout<<"YES\n";
			else if(ma_x<=y&&ma_y<=x)cout<<"YES\n";
			else cout<<"NO\n";
		}
	} 
	return 0;
} 
```

---

## 作者：翟翟 (赞：1)

在每次加点操作时，若 $x_i>y_i$，则交换 $x_i$ 和 $y_i$。
记 $xa$ 为所有 $x_i$ 的最大值，$ya$ 为所有 $y_i$ 的最大值。

在每次询问操作时，若 $h_i>h_i$，则交换 $h_i$ 和 $w_i$。
若 $h_i>xa$ 并且 $w_i>ya$，输出`YES`，否则，输出`NO`。

时间复杂度：$\mathcal O(n)$。

## Code
```
#include<cstdio>
int n,x,y,xa,ya;
char s[1];
int main(){
	for(scanf("%d",&n);n--;){
		scanf("%s%d%d",s,&x,&y);
		if(x>y)x^=y^=x^=y;
		if(s[0]=='+'){
			if(x>xa)xa=x;
			if(y>ya)ya=y;
		}
		else
			puts(xa<=x&&ya<=y?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：1)

考前写题解据说能增加 rp（

## 思路

对于每次操作，如果 $x > y$，先交换 $x,y$。

于是只需要维护 $x,y$ 的最大值，然后询问时比较就可以了。

时间复杂度 $O(n)$。

## 代码

```cpp
/*

p_b_p_b txdy
AThousandMoon txdy
AThousandSuns txdy
hxy txdy

*/

#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define scd second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

int n, mx, my;

void solve() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		char op[9];
		int x, y;
		scanf("%s%d%d", op, &x, &y);
		if (x > y) {
			swap(x, y);
		}
		if (op[0] == '+') {
			mx = max(mx, x);
			my = max(my, y);
		} else {
			puts(mx <= x && my <= y ? "YES" : "NO");
		}
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```


---

## 作者：z_yq (赞：0)

### 题意
每一次有两个操作，操作一是向数组里面加入一个元素 ${(x,y)}$，操作二是询问是否二元数组里的二元组均满足 $x \le h$，$y \le w$，或者 $x \le w$，$y \le h$。

### 思路
不难想到，我们可以用 ${(x,y)}$ 中较小的匹配 ${(h,w)}$ 中较小的，较大的匹配较大的，所以我们在输入 ${(x,y)}$ 或者 ${(h,w)}$ 的时候，就让这个二元组满足 $x \le y$， 或者 $h \le w$，如果是操作一，就记录最大值 $maxx$ 和 $maxy$，然后到了操作二，让较小的 $maxx$ 匹配 $h$，$maxy$ 去匹配 $maxy$ 就可以了。

### Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,maxx,maxy;
int main()
{
	maxx=maxy=LONG_LONG_MIN;
	cin>>n;
	while(n--)
	{
		char opt;ll x,y;
		cin>>opt>>x>>y;
		if(x>y) swap(x,y);
		if(opt=='+')
			maxx=max(maxx,x),
			maxy=max(maxy,y);
		else if(maxx<=x && maxy<=y)
			cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：charlieqi (赞：0)

# 题意
维护一个集合，并有两种操作：`+ x y` 和 `?h w`。`+ x y` 为加入操作，`? h w` 为查询操作，查询集合中的 $x,y$ 是否满足 $x\le w,y\le h$，如满足，输出 `YES`，否则输出 `NO`。
# 分析
插入操作很简单，但是，查询操作要遍历一遍吗？答案是不用，为什么呢，因为我们可以在输入时就找出输入 $x,y$ 的最大值，用最大值和 $h,w$ 作比较判断输出即可。用这样的方法，一边输入一边操作，时间复杂度为 $O(n)$，空间复杂度为 $O(1)$。
# 易错点
- 输出大小写。
- $x$ 的值比 $y$ 小而没有交换。

---

## 作者：xujingyu (赞：0)

## 题意

维护一个集合，每次加入 $(x,y)$ 或者询问其中是否每个 $(x,y)$ 都满足 $x\leq h$ 且 $y\leq w$（或者 $x\leq w$ 且 $y\leq h$）

## 解法

首先可以想到开两个变量，分别维护 $x$ 和 $y$ 的最小值，代表所有的 $x$ 和 $y$。

不过如果 $x$ 集体都比 $y$ 大很多，那么大部分时候都用 $y$ 去比较 $\min(h,w)$，所以那个做法会出错。

那么可以将两个变量的定义改为其中一个每次分别储存 $x$ 和 $y$ 中较小值的最大值设为 $mx$，另一个分别储存 $x$ 和 $y$ 中较大值的最大值设为 $my$，那以 $mx$ 和 $\min(h,w)$ 比较，$my$ 和 $\max(h,w)$ 比较，即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,x,y,mx,my;
char c;

signed main()
{
	scanf("%d",&n);
	while(n--)
	{
		cin >> c;
		scanf("%d%d",&x,&y);
		if(c == '+')
		{
			mx = max(mx,min(x,y));//储存
			my = max(my,max(x,y));
			continue;
		}
		if(mx <= min(x,y) && my <= max(x,y)) printf("YES\n");//比较
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：WoodReal12 (赞：0)

## 思路

### 具体代码思路

用 $mxx$ 和 $mxy$ 存储当前集合中所有账单的最大宽度和最大高度。

然后对每种操作进行以下维护：
   - 如果是 `+`，则读取账单的尺寸 $(x, y)$，并更新 $mxx$ 和 $mxy$。
   - 如果是 `?`，则读取钱包的尺寸 $(h, w)$，检查是否满足题目条件，并输出相应的结果。

### 代码思路的逻辑

- 当遇到 `+` 操作时，记录并持续更新所有账单中最大的长和宽。
- 当遇到 `?` 操作时，只需检查当前记录的最大账单尺寸是否能放入给定的钱包尺寸中。


## 代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int n;
    cin >> n;
    int mxx = 0, mxy = 0;
    for (int i = 0; i < n; ++i) {
        char op;
        cin >> op;
        if (op == '+') {
            int x, y;
            cin >> x >> y;
            mxx = max(mxx, min(x, y)),mxy = max(mxy, max(x, y));
        }
		if (op == '?') {
            int h, w;
            cin >> h >> w;
            ((mxx <= h && mxy <= w) || (mxx <= w && mxy <= h))?puts("YES"):puts("NO");//题目条件判断
        }
    }
    return 0;
}
```

---

## 作者：lqsy002 (赞：0)

## 题目大意

当输入的是 $+$ 时，表示要装入一张 $x\times y$ 的现金，当输入的是 $?$ 时，表示现在有一个 $x\times y$ 的钱包，能不能把之前的那些现金都装进去。[题目链接](https://www.luogu.com.cn/problem/CF1101E)。

## 解题思路

以 $x$ 为短边，$y$ 为长边，维护两个最大值。

时间复杂度 $O(n)$。

## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,l,r;
char str[10];
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>str>>l>>r;
        if(l>r) 
            swap(l,r);
        if(str[0]=='+'){
            x=max(x,l);
            y=max(y,r);
        }else
            if(x<=l&&y<=r) 
                cout<<"YES\n";
            else 
                cout<<"NO\n";
    }
    return 0;
}
```

---

## 作者：_Violet_Evergarden (赞：0)

看到题解有些空缺，来发一发。

# 思路
这道题我们只需在输入时将加入的点中最大的 $x$ 和 $y$ 记录下来，然后再把加入的点集中最小值的最大值记录下来，记为 $z$。然后在查询中我们只需要判断输入进来的数中较大的数是否大于 $x$ 和 $y$ 且较小的数是否大于 $z$ 若同时满足则输出 $YES$ 否则输出 $NO$。

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int maxx;
int maxy;
int maxz;
int xiax;
int xiay;
int x[500001];
int y[500001];
int xx;
int yy;
char ch;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>ch;
		if(ch=='+'){
			cin>>x[i]>>y[i];
			maxz=max(maxz,min(x[i],y[i]));
			maxx=max(maxx,x[i]);
			maxy=max(maxy,y[i]);
		}
		else{
			cin>>xx>>yy;
			if(xx<yy){
				xx^=yy;
				yy^=xx;
				xx^=yy;
			}
			if(xx>=maxx&&xx>=maxy&&yy>=maxz){
				cout<<"YES"<<endl;
				continue;
			}
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：user470883 (赞：0)

## 思路：

如果是加号：

我们往点集里加入 $x,y$，我们用 `maxx` 记录最大的，`maxy` 记录最小中最大的，当 $x<y$ 时，将其交换。

如果是问号：

我们看能否满足条件，得益于刚刚记录好的 `maxx` 和 `maxy`，我们直接用 `if` 语句判断 `x>=maxx&&y>=maxy` 即可，然后根据题目要求输出 `YES` 或 `NO`。

根据思路其实重要代码板块都出来了，代码就不放了。

---

## 作者：红尘仙 (赞：0)

### 【引言】
~~呜呜呜，没有贡献分了~~，我看CF的题太可爱了，来切几道，来几篇题解

### 【思路分析】：

我们看到题目中要求，加入点集$(x,y)$,很容易就想到这是一个类似于直角坐标系之类的，在就是查询从头到点$(x,y)$,不难想到需要建立一个$n * m$的矩阵就可以满足这类条件

----
### 【代码实现】：
1. 建立矩阵就不必说了

2. 建立完矩阵添加点集，也就是直接加入就可以了

3. 查询$(x,y)$这一个区间，这些数，是否都满足，我们只需要记录一下这个区间的最大值和$h,w$比较一下,也就是记录一下最大值即可。

---
### 【code】:
```
#include <bits/stdc++.h>
inline int read()
{
  int x=0 , f=1; char ch=getchar();
  while( !isdigit(ch) ){ if(ch == '-')f = -1; ch = getchar();}
  while( isdigit(ch) ){ x = x *10 + ch - '0';ch = getchar();}
  return x * f;
}
int n ;
int max_x,max_y;
int main()
{
    n = read();
    while(n--)
    {
        char opt = getchar();
        int x = read(), y = read();
        if(x > y) std::swap( x , y );
        if(opt == '+')
        {
            max_x = std:: max( max_x , x) ;
            max_y = std:: max( max_y , y) ;
        }
        if(opt == '?')
        {
            if( x >= max_x && y >= max_y )
            {
                printf("YES\n");
            }
            else
            {
                printf("NO\n");
            }
        }
    }
    return 0;//好习惯 
}
```

---

## 作者：CSP_Sept (赞：0)

开学第一天留念
___
### 题目大意

给定 $n$ 个操作：

1. 插入一个 $x\times y$ 的矩形。
2. 询问所有插入的矩形是否都可以放进一个 $h\times w$ 的矩形。

### 思路

为了方便，我们直接处理成 $x<y,h<w$ 的形式。

这样我们只要维护两个量：$\max x,\max y$，每次操作判断 $\max x<h \text{ and }\max y<w$ 是否成立即可。

### $\mathcal{Code}$

```cpp
scanf("%s%d%d", opt, &x, &y);
if(x > y) Swap(x, y);
if(opt[0] == '+'){
    Max_x = max(Max_x, x);
	Max_y = max(Max_y, y);
}
if(opt[0] == '?')
	puts((Max_x <= x && Max_y <= y) ? "YES" : "NO");
```

---


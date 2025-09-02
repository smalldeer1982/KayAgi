# 「QFOI R1」抱抱

## 题目描述

小 R 是一个可爱的女孩子，她希望跟大家抱抱，顺便给大家分蛋糕吃。

蛋糕是一个大小为 $a\times b\times c$ 的长方体，其中每个单位正方体都被赋予了一个坐标 $(x,y,z)$（$1\le x\le a,1\le y\le b,1\le z\le c$）。

共进行 $m$ 次切蛋糕操作，每次按如下三种方式之一切分：

1. 切出 $x\le k$ 的部分分给大家。
2. 切出 $y\le k$ 的部分分给大家。
3. 切出 $z\le k$ 的部分分给大家。

由于她自己也想吃蛋糕，她希望知道在每次切蛋糕后，还剩下多少体积没有分给大家。

## 说明/提示

**样例 $1$ 解释**

第一次切蛋糕，将所有 $x\le 2$ 的部分切掉，剩余的单位正方体有 $(3,1,1),(3,1,2),(3,1,3),(3,2,1),(3,2,2),(3,2,3),(3,3,1),(3,3,2),(3,3,3)$ 共 $9$ 个。

第二次切蛋糕，将所有 $y\le 1$ 的部分切掉，剩余的单位正方体有 $(3,2,1),(3,2,2),(3,2,3),(3,3,1),(3,3,2),(3,3,3)$ 共 $6$ 个。

---

**样例 $2$ 解释**

第四次切蛋糕没有任何作用，因为第二次切蛋糕时 $y\le 654321$ 的部分已经被切掉，此时已经不存在 $y\le 111111$ 的单位正方体。

注意每次操作中的参数 $k$ 是初始时决定的绝对坐标，不会随着操作的进行而改变。

---

**数据范围**

本题共 $20$ 个测试点，每个测试点 $5$ 分。

对于全部数据，保证 $1\le a,b,c\le 10^6$，$1\le m\le 2\times 10^5$，$op\in\{1,2,3\}$，若 $op=1$ 则 $1\le k\le a$，若 $op=2$ 则 $1\le k\le b$，若 $op=3$ 则 $1\le k\le c$。

- 对于测试点 $1\sim 5$：保证 $a,b,c,m\le 100$。
- 对于测试点 $6\sim 10$：保证 $b=c=1$，$op=1$。
- 对于测试点 $11\sim 15$：保证 $c=1$，$op\in\{1,2\}$。
- 对于测试点 $16\sim 20$：无特殊限制。

## 样例 #1

### 输入

```
3 3 3 2
1 2
2 1```

### 输出

```
9
6```

## 样例 #2

### 输入

```
1000000 1000000 1000000 6
1 123456
2 654321
3 233333
2 111111
1 333333
3 1000000```

### 输出

```
876544000000000000
303002853376000000
232302288589217792
232302288589217792
176680542935560631
0
```

# 题解

## 作者：rui_er (赞：12)

这里是官方题解。

众所周知，设长方体的长、宽、高分别为 $a,b,c$，则长方体的体积 $V=abc$。显然，经过若干次操作后，蛋糕的剩余部分依然是长方体。我们只需要知道每次操作后，剩余部分的长、宽、高分别是多少，即可解决问题。

考察剩余部分的横坐标 $x$，由于每次操作只会切掉 $x\le k$ 的部分，因此任意时刻剩余部分的 $x$ 一定是一段后缀 $x > k_{\max}$。这段后缀的长度是好求的，只需要维护当前所有对 $x$ 的切割的 $k$ 的最大值即可。纵坐标和竖坐标 $y,z$ 同理。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

int a, b, c, m, x, y, z;

int main() {
    for(scanf("%d%d%d%d", &a, &b, &c, &m); m; m--) {
        int op, k;
        scanf("%d%d", &op, &k);
        if(op == 1) chkmax(x, k);
        else if(op == 2) chkmax(y, k);
        else chkmax(z, k);
        printf("%lld\n", 1LL * (a - x) * (b - y) * (c - z));
    }
    return 0;
}
```

---

## 作者：hjqhs (赞：9)

记录每次操作的 $x,y,z$ 最大值 $mx,my,mz$。所有 $x$ 轴坐标大于 $mx$ 的，$y$ 轴坐标大于 $my$ 的，$z$ 轴坐标大于 $mz$ 的格子肯定保留下来了。用立方体求体积公式即可。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,c,m;
int mx,my,mz;
signed main(){
	cin>>a>>b>>c>>m;
	for(int i=1;i<=m;++i){
		int op,k;
		cin>>op>>k;
		if(op==1)mx=max(mx,k);
		if(op==2)my=max(my,k);
		if(op==3)mz=max(mz,k);
		cout<<(a-mx)*(b-my)*(c-mz)<<'\n';
	}
	return 0;
} 
```

---

## 作者：LegendaryGrandmaster (赞：4)

不大一样的写法。

操作时当前 `k` 如果比同种操作中 `k` 的最大值小，则说明这部分已经被切掉，无需考虑。

单次体积：在同种操作之前最大值的基础上，当前 `k` 多出的部分乘上另外两个坐标剩余长度的积。

每次减去后输出即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int a,b,c,m;
    cin>>a>>b>>c>>m;
    int ans=a*b*c;
    int A=0,B=0,C=0;
    while(m--){
    	int op,k;
    	cin>>op>>k;
    	if(op==1&&k>=A){
    		ans-=(k-A)*b*c;
    		a=a-k+A;
    		A=max(A,k);
    	}
    	if(op==2&&k>=B){
    		ans-=(k-B)*a*c;
    		b=b-k+B;
    		B=max(B,k);
    	}
    	if(op==3&&k>=C){
    		ans-=(k-C)*b*a;
    		c=c-k+C;
    		C=max(C,k);
    	}
    	cout<<ans<<'\n';
    }
}
```

---

## 作者：Lemon_zqp (赞：3)

### 题目大意
说了一堆，其实就是说一开始有 $a$ 和 $b$ 和 $c$ 三个变量，如果 $op$ 等于 $1$，就将 $a$ 减去 $k$，如果 $op$ 等于 $2$，就将 $b$ 减去 $k$，如果 $op$ 等于 $3$，就将 $c$ 减去 $k$，每次减完之后，输出三个数的乘积即可。
### 思路
这道题直接按照题目操作就可以了，有几个坑要注意一下，一个就是如果 $a$ 或者 $b$ 或者 $c$ 减完之后小于零，那么就让这个变量等于 $0$，不然答案有可能是负数，还有就是如果这次输入 $op$ 为 $1$，$k$ 为 $3$，上次输入的 $op$ 为 $1$，$k$ 为 $5$，那么就不进行操作，因为上一次切蛋糕的时候已经把 $y \leq 5$ 的部分切掉了，所以 $y \leq 3$ 的部分就不存在了，所以每次要把最大值存起来。其他的按照题目操作即可。
### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
	int a, b, c, m, amx = 0, bmx = 0, cmx = 0;
	cin >> a >> b >> c >> m;
	for(int i = 1; i <= m; i++){
		int op, k;
		cin >> op >> k;
		if(op == 1){
			if(k > amx){
				int t = k;
				t -= amx;
				amx = k;
				a -= t;
			}
			if(a <= 0){
				a = 0;
			}
			cout << a * b * c << endl;
		}
		else if(op == 2){
			if(k > bmx){
				int t = k;
				t -= bmx;
				bmx = k;
				b -= t;
			}
			if(b <= 0){
				b = 0;
			}
			cout << a * b * c << endl;
		}
		else{
			if(k > cmx){
				int t = k;
				t -= cmx;
				cmx = k;
				c -= t;
			}
			if(c <= 0){
				c = 0;
			}
			cout << a * b * c << endl;
		}
	}
	return 0;
}
```


---

## 作者：__O_v_O__ (赞：2)

注意到每次切完后，剩下的部分还是一个立方体，所以我们可以把每条边切下来的长度记录下来，每次输出每条边剩下的长度乘积即可。

**AC code:**

```cpp
#include<bits/extc++.h>
using namespace std;
#define int long long
int a,b,c,m,op,k,mx,my,mz;
signed main(){
	ios::sync_with_stdio(0);
	cin>>a>>b>>c>>m;
	for(int i=1;i<=m;i++){
		cin>>op>>k;
		if(op==1){
			mx=max(mx,k);
			cout<<(a-mx)*(b-my)*(c-mz)<<endl;
		}else if(op==2){
			my=max(my,k);
			cout<<(a-mx)*(b-my)*(c-mz)<<endl;
		}else{
			mz=max(mz,k);
			cout<<(a-mx)*(b-my)*(c-mz)<<endl;
		}
	}return 0;
}
```

---

## 作者：ICU152_lowa_IS8 (赞：2)

本题仅仅只需要那么一丢丢的思维即可。

统计当前被切掉的最大坐标 $na,nb,nc$ （比它更小的肯定都被切掉了），然后用 $a,b,c$ 分别减一下得到剩余的长宽高，算出 $(a-na)(b-nb)(c-nc)$ 的值即可。

注意到数据范围和样例，本题不需要写高精但是要开 `long long`。

代码如下：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int a,b,c,m,na=0,nb=0,nc=0;
	cin>>a>>b>>c>>m;
	for(int i=1;i<=m;i++){
		int op,k;
		cin>>op>>k;
		if(op==1){
			na=max(na,k);
		}
		if(op==2){
			nb=max(nb,k);
		}
		if(op==3){
			nc=max(nc,k);
		}
		cout<<(a-na)*(b-nb)*(c-nc)<<endl;
	}
	return 0;
}
```


---

## 作者：zhang_Jimmy (赞：2)

# 思路：

数据范围 $1\le a,b,c \le 10^6$，开三维数组模拟肯定 MLE。

所以，我就想到了另一种方法：

对于 $a,b,c$，我们对于每个变量再另外定义两个变量：$a1,a2,b1,b2,c1,c2$。

变量名最后一个数字为 $1$ 的表示现在删除了多长的长/宽/高，变量名最后一个数字为 $2$ 的表示还剩多长的长/宽/高。

这样，我们就好办了。

定义 $tmp$ 为变量名最后一个数字为 $1$ 的变量修改前的值，$ans$ 是还剩的蛋糕总数，那么：

- 对于 $op = 1$:

	- 如果 $a1 - tmp > 0$，$ans \gets ans - (a1 - tmp) \times b2 \times c2,a2 \gets a2 - a1 - tmp$；

	- 否则，$ans$ 不变。

- 其他情况类似，不再赘述。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int a, b, c, a1, b1, c1, a2, b2, c2, m, op, k;

int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	cin >> a >> b >> c >> m;
	long long ans = 1ll * a * b * c;
	a2 = a, b2 = b, c2 = c;
	while(m --){
		cin >> op >> k;
		if(op == 1){
			int tmp = a1;
			a1 = max(a1, k);
			ans -= 1ll * (a1 - tmp < 0 ? 0 : a1 - tmp) * b2 * c2;
			a2 -= (a1 - tmp < 0 ? 0 : a1 - tmp);
		}
		if(op == 2){
			int tmp = b1;
			b1 = max(b1, k);
			ans -= 1ll * (b1 - tmp < 0 ? 0 : b1 - tmp) * a2 * c2;
			b2 -= (b1 - tmp < 0 ? 0 : b1 - tmp);
		}
		if(op == 3){
			int tmp = c1;
			c1 = max(c1, k);
			ans -= 1ll * (c1 - tmp < 0 ? 0 : c1 - tmp) * a2 * b2;
			c2 -= (c1 - tmp < 0 ? 0 : c1 - tmp);
		}
		cout << (ans < 0 ? 0 : ans) << endl;
	}
	return 0;
}

```


---

## 作者：Lovely_Elaina (赞：2)

有一点要注意的是切除某一部分后其他部分位置不变。

比如说切除 $z\leq k$ 的部分后大于 $k$ 的部分没有下降（即不存在小于 $z\leq k$ 的部分）。

那么我们只要记录 $k$ 的最大值即可。

记得开 long long。

小 R 可爱，抱抱小 R。

```cpp
#include <bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define int unsigned long long
#define endl '\n'
using namespace std;

int a,b,c,m;
int i,j,z;
int op,k;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    // freopen("app.in","r",stdin);
    // freopen("app.out","w",stdout);
    
    // i = j = z = 1145141919;

    cin >> a >> b >> c >> m;
    for(int ll = 1; ll <= m; ll++){
        cin >> op >> k;
        if(op == 1) i = max(i,k);
        if(op == 2) j = max(j,k);
        if(op == 3) z = max(z,k);
        cout << (a-i)*(b-j)*(c-z) << endl;
    }
    return 0;
}
```

---

## 作者：XRRRRcode (赞：1)

## 题解
小模拟题， 比较简单。先用 $3$ 个变量分别储存读入的数据，方便后续操作。然后开始操作，读入 $k$ 后先判断一下能不能切下来，这时候之前储存的变量就起作用了，用储存下来的数据减去目前的数据计算一下一共剩下多少，与 $k$ 比较即可。但这里还要注意一个点，就是即使能切下来也不一定全能切下来，单纯靠样例是无法看出这点的。最后输出三个数据的乘积，显然不会爆 long long。时间复杂度 $O(m)$。

## 代码
```cpp
#include<iostream>
#include<string>
using namespace std;
int main()
{
    long long x,y,z,k,a,b,c;//不开long long见祖宗
    int op,m,i;
    cin>>x>>y>>z>>m;
    a=x,b=y,c=z;//储存数据
    for(i=0;i<m;i++)
    {
        cin>>op>>k;
        if(op==1&&k>a-x)//判断能不能切
            x-=(k-a+x);//计算能切多少
        if(op==2&&k>b-y)
            y-=(k-b+y);
        if(op==3&&k>c-z)
            z-=(k-c+z);
        cout<<x*y*z<<endl;//计算体积输出
    }
    return 0;
}
```


---

## 作者：FurippuWRY (赞：0)

按题意模拟。

设体积为 $V$，体积变化量为 $\Delta V$。

对于三个方向，分别设一个变量 $x=0,y=0,z=0$，用来判断 $k$ 所在的部分是否已被切除。

每切除一部分的蛋糕，就更新一次变量。若 $op=1$，$x\leftarrow \max(k,x)$，若 $op=2$，$y\leftarrow \max(k,y)$，若 $op=3$，$z\leftarrow \max(k,z)$。

对于不同的 $op$，用其对应的变量与 $k$ 进行比较，若 $k$ 更小，则代表 $k$ 所在的部分已经被切除了，此时体积不会减少，直接输出 $V$ 即可。

若 $k$ 更大或者等于，则 $\Delta V=(k - x) \times (b - y) \times (c - z)$，然后将 $V-\Delta V$ 赋值给 $V$，为切除后剩余的体积，输出 $V$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int a, b, c, m, op, k, v, x, y, z;

signed main() {
	cin >> a >> b >> c >> m;
	v = a * b * c; 
	for (int i = 0; i < m; ++i) {
		cin >> op >> k;
		if (op == 1) {
			if (k < x) {
				cout << v << '\n';
				continue;
			} 
			else{
				v -= (k - x) * (b - y) * (c - z);
				x = max (x, k);
			}
			
		}
		if (op == 2) {
			if (k < y) {
				cout << v << '\n';
				continue;
			} 
			else{
				v -= (k - y) * (a - x) * (c - z);
				y = max (y, k);
			}
		}
		if (op == 3) {
			if (k < z) {
				cout << v << '\n';
				continue;
			} 
			else{
				v -= (k - z) * (b - y) * (a - x);
				z = max (z, k);
			}
		}
		cout << v << '\n';
	}
    return 0;
}
```

---

## 作者：Moon_Traveller (赞：0)

[>> 传送门 <<](/problem/P9713)

### 题目大意

有一个 $a\times b \times c$ 的长方体，切 $m$ 次。有以下三种切法：

1. $op=1$ 时，将 $x\le k$ 的部分切掉。
1. $op=2$ 时，将 $y\le k$ 的部分切掉。
1. $op=3$ 时，将 $z\le k$ 的部分切掉。

输出每次切完后的剩余体积。

**注意：$k$ 是「坐标」，而不是「长度」！**

### 思路

声明 $3$ 个变量 $x,y,z$，用来存储被删掉后剩余的 长、宽、高。

每次切去后，将对应的变量的数值设为 $k$，并重新计算体积。

观察到样例解释中的：

> 第四次切蛋糕没有任何作用，因为第二次切蛋糕时 $y\le 654321$ 的部分已经被切掉，此时已经不存在 $y≤111111$ 的单位正方体。

所以每次截取要先判断一下 $k\ge a-x$。

### 代码

```cpp
#include <iostream>
using namespace std;
#define int long long // 不开 long long 见祖宗！

int a, b, c, m;
int op, k;
int v;
int x, y, z;

signed main()
{
    cin >> a >> b >> c >> m;
    v = a * b * c;
    x = a;
    y = b;
    z = c;
    while(m--)
    {
        cin >> op >> k;
        switch (op)
        {
            case 1:
                if(k < a - x)
                {
                    break;
                }
                x = a - k;
                v = x * y * z;
                break;
            case 2:
                if(k < b - y)
                {
                    break;
                }
                y = b - k;
                v = x * y * z;
                break;
            case 3:
                if(k < c - z)
                {
                    break;
                }
                z = c - k;
                v = x * y * z;
                break;
        }
        cout << v << endl;
    }
    return 0;
}
```

---

## 作者：Crasole (赞：0)

## 思路

因为每次切割的范围都是从当前的起始端到 $k$，那么我们就可以用 $x, y, z$ 来分别表示当前三条边的起始端。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int x, a, y, b, z, c, m, k, ans;
int op;
signed main() {
	cin >> a >> b >> c >> m;
	x = y = z = 0;
	ans = a * b * c;//算出初始方块的数量
	while(m--) {
		cin >> op >> k;
		if(op == 1)
			if(k <= x)//特判
				cout << ans << endl;
			else //计算长方体公式
				ans -= (k - x) * (b - y) * (c - z), x = k,
				cout << ans << endl;
		else if(op == 2)
			if(k <= y)
				cout << ans << endl;
			else 
				ans -= (k - y) * (a - x) * (c - z), y = k,
				cout << ans << endl;
		else 
			if(k <= z)
				cout << ans << endl;
			else 
				ans -= (k - z) * (b - y) * (a - x), z = k,
				cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Miyamizu_Mitsuha (赞：0)

如果一开始坐标系原点为左下角的话，那我们考虑维护蛋糕左下角顶点。然后利用左下角顶点的坐标和 $k$ 的对比就可以判断每次要切下来多少体积了。注意判断一下什么都没切到的情况已经切没了的情况。

```
#include <iostream>
using namespace std;
#define int long long
signed main() {
    int a, b, c, m,bj=1;
    cin >>a>> b>>c>>m;
    long long volume = 1LL * a * b * c;
    int na=0,nb=0,nc=0;
    while(m--){
        int op,k;
        cin>>op>>k;
        if(op==1){
            if(na<=k){//如果切到了
              volume -= 1LL * (k-na) * b * c;//k-na就是切下的长
              a-=(k-na);//减少了
              if(a<0)bj=0;//如果为0了那就保存一下，以后的输出都为0
              na=k;//左下角顶点坐标随之变化
            }
        }else if (op==2) {
            if(nb<=k){
              volume -= 1LL * a * (k-nb) * c;
              b-=(k-nb);
              if(b<0)bj=0;
              nb=k;
            }
        }else{
          if(nc<=k){
            volume -= 1LL * a * b * (k-nc);
            c-=(k-nc);
            if(c<0)bj=0;
            nc=k;
          }
        }
        if(!bj)cout<<0<<endl;
        else cout << volume << endl;
    }

    return 0;
}
```


---

## 作者：Yzmddsw (赞：0)

# P9713

## 实现

存储这个立方体的最大坐标 $(x_1,y_1,z_1)$ 和最小坐标 $(x_2,y_2,z_2)$，最大的坐标初值为 $(a,b,c)$，最小的坐标初值为 $(0,0,0)$。

每次切的时候判断坐标，改变对应的最小坐标即可，每次输出体积就是 $(x_1-x_2)(y_1-y_2)(z_1-z_2)$。

当然，代码中不建议使用上面的命名方式。

## 代码

```cpp
#include <iostream>
#define FOR(i, m, n) for (long long i = m; i <= n; i++)
#define ll long long
using namespace std;
ll xs,ys,zs;//最小坐标
ll xe,ye,ze;//最大坐标
int main(){
    ll m;
    cin>>xe>>ye>>ze>>m;
    xs=ys=zs=0;
    FOR(i,1,m){
        ll op,k;
        cin>>op>>k;
        if(op==1&&k>=xs)xs=k;
        else if(op==2&&k>=ys)ys=k;
        else if(op==3&&k>=zs)zs=k;
        cout<<(xe-xs)*(ye-ys)*(ze-zs)<<endl;//公式输出
    }
    return 0;
}
```


---

## 作者：Loser_Syx (赞：0)

考虑每次切蛋糕时都是将一部分的立方体切下来，于是记录 $x,y,z$ 被更改到了多少，最后计算体积即可。

```cpp
#include <iostream>
using namespace std;
int main(){
	int a, b, c, t;
	cin >> a >> b >> c >> t;
	int i = 1, j = 1, k = 1;
	while (t--) {
		int op, x;
		cin >> op >> x;
		if (op == 1) i = max(i, x + 1);
		else if (op == 2) j = max(j, x + 1);
		else k = max(k, x + 1);
		cout << 1LL * (a - i + 1) * (b - j + 1) * (c - k + 1) << '\n';
	}
}
```

---

## 作者：PineappleSummer (赞：0)

基础赛 T2，难度下位橙。

以操作 $1$ 为例：切出 $x\le k $ 的部分给大家，那么剩下的就是 $k+1\sim a$ 的部分，越切剩下的越少，所以我们只关心 $k+1$ 的最大值是多少。

用 $mx$ 表示操作 $1$ 中 $k+1$ 的最大值，$my$ 表示操作 $2$ 中 $k+1$ 的最大值，$mz$ 表示操作 $3$ 中 $k+1$ 的最大值。那么剩下部分的长、宽、高分别为 $a-mx,b-my,c-mz$，剩下部分的体积就为 $(a-mx)\times(b-my)\times(c-mz)$。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a,b,c,mx,my,mz;
int m;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>a>>b>>c>>m;
	while(m--)
	{
		int op;
		ll k;
		cin>>op>>k;
		if(op==1) mx=max(mx,k);
		else if(op==2) my=max(my,k);
		else mz=max(mz,k);
		cout<<(ll)(a-mx)*(b-my)*(c-mz)<<'\n';
	}
    return 0;
}
```

---

## 作者：Clarinet (赞：0)

# 简要题意
给出一个蛋糕的长宽高 $a$、$b$、$c$，每次根据原坐标来切蛋糕，求每次切完后剩下的蛋糕体积。
# 分析
这道题的要点主要在于，对每次切蛋糕的操作要判断其是否有效，就是样例二解释中的**注意每次操作中的参数 $k$ 是初始时决定的绝对坐标，不会随着操作的进行而改变。**我们多加一个判断就能解决这个问题啦。另外就是不要忘记开 long long。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,m,x,y,z;
int main(){
	cin>>a>>b>>c>>m;
	x=a;
	y=b;
	z=c;
	for(int i=1;i<=m;i++){
		long long op,k,s=0;
		cin>>op>>k;
		if(op==1)a=min(a,x-k);
		if(op==2)b=min(b,y-k);
		if(op==3)c=min(c,z-k);
		cout<<max(s,a*b*c)<<endl;
	}
	return 0;
}
```
感谢阅读！

---


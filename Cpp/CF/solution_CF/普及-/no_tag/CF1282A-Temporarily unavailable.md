# Temporarily unavailable

## 题目描述

Polycarp lives on the coordinate axis $ Ox $ and travels from the point $ x=a $ to $ x=b $ . It moves uniformly rectilinearly at a speed of one unit of distance per minute.

On the axis $ Ox $ at the point $ x=c $ the base station of the mobile operator is placed. It is known that the radius of its coverage is $ r $ . Thus, if Polycarp is at a distance less than or equal to $ r $ from the point $ x=c $ , then he is in the network coverage area, otherwise — no. The base station can be located both on the route of Polycarp and outside it.

Print the time in minutes during which Polycarp will not be in the coverage area of the network, with a rectilinear uniform movement from $ x=a $ to $ x=b $ . His speed — one unit of distance per minute.

## 说明/提示

The following picture illustrates the first test case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1282A/307b325125eb4f2400d0fb03b9026999f9da2b19.png)Polycarp goes from $ 1 $ to $ 10 $ . The yellow area shows the coverage area of the station with a radius of coverage of $ 1 $ , which is located at the point of $ 7 $ . The green area shows a part of the path when Polycarp is out of coverage area.

## 样例 #1

### 输入

```
9
1 10 7 1
3 3 3 0
8 2 10 4
8 2 10 100
-10 20 -17 2
-3 2 2 0
-3 1 2 0
2 3 2 3
-1 3 -2 2
```

### 输出

```
7
0
4
0
30
5
4
0
3
```

# 题解

## 作者：chenyuchenghsefz (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1282A)

先把 $a$ 和 $b$ 从小到大排序一下。

- 如果 $c+r<a$。

输出 $b-a$。

- 如果 $c-r>b$。

同上，输出 $b-a$。

- 如果都不是的话，那就输出 $b-a-(\min(c+r,b)-\max(c-r,a))$。

[AC 记录](https://www.luogu.com.cn/record/105030229)

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		int a,b,c,r;
		cin>>a>>b>>c>>r;
		if(a>b)
		swap(a,b);
		if(c+r<a||c-r>b)
		cout<<b-a<<endl;
		else
		cout<<b-a-min(b,c+r)+max(a,c-r)<<endl;
	}
	return 0;
}
```


---

## 作者：_ouhsnaijgnat_ (赞：1)

这个翻译有点问题。是没有被覆盖而不是被覆盖，管理员看到尽量改一下。

# 题目大意

首先，有一个数轴。在数轴上有一个动点。

这个动点移动一个长度单位的时间为 $1$。

然后，给出你 $a,b,c,r$。

表示这个动点从 $a$ 点到 $b$ 点。

然后在这个数轴上有一个网格，其覆盖部分是以 $c$ 为圆心的半径为 $r$ 的圆。

让你求出有多少个时间单位这个动点没有被覆盖。

# 思路

咱们一步一步来。首先，如果这个圆不在动点的运动范围之内，也就是 $c+r<a$ 或者 $c-r>b$ 时，直接输出 $b-a$。

如果在动点运动范围之内，那么就算出网格覆盖的面积，在整体减空白，便是要得到的答案。那么，怎么求出来覆盖面积呢？

判断下限：用 $c-r$ 与 $a$ 做比较，取一个大值。

判断上限：用 $c+r$ 与 $b$ 做比较，取一个小值。

用这两个值一相减，便是覆盖面积。

注意：本题解是默认 $a<b$ 的，所以如果 $b<a$，要调换它们俩的值。

---

## 作者：liuyz11 (赞：1)

# 题解 CF1282A 【Temporarily unavailable】

**该场比赛的题解：[我的博客求围观](https://www.cnblogs.com/nblyz2003/p/12173579.html)**

题目大意：有一条数轴，要从a点跑到b点，在c点的地方有网络，覆盖范围为半径为r的圆。问在多少时间有网路覆盖。

因为是在数轴上的，所以有网路覆盖的地方就是(c - r，c + r)，那么只要减一下就好，注意可能有些区域在跑的地方的外面。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		int a, b, c, r;
		scanf("%d%d%d%d", &a, &b, &c, &r);
		printf("%d\n", max(a, b) - min(a, b) - max(0, min(max(a, b), c + r) - max(min(a, b), c - r)));
	}
    return 0;
}
```

---

## 作者：So_noSlack (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1282A)&[CF 链接](http://codeforces.com/problemset/problem/1282/A)

## 题目简述

共有 $T$ 组数据。

有一条数轴，要从 $a$ 点跑到 $b$ 点，在 $c$ 点的地方有网络，覆盖区间为 $[c - r, c+ r]$，问在多少时间没有网络覆盖。

## 思路

分类讨论：

1. $c + r \le a$ 或 $c - r \ge b$，表示区间 $[a, b]$ 内都没有网络，直接输出 $b - a$。

2. $c + r \ge b$ 且 $c - r \ge a$，表示区间 $[c - r, b]$ 区间有网络，输出 $c - r - a$。

3. $c - r \le a$ 且 $c + r \le b$，表示区间 $[a, c + r]$ 有网络，输出 $b - c - r$。

4. $c + r \ge b$ 且 $c - r \le a$，表示区间 $[a, b]$ 内都有网络，输出 $0$ 即可。

5. $c + r \le b$ 且 $c - r \ge a$，表示区间 $[c - 1, c + r]$ 有网络，正常输出 $b - a - 2 \times r$ 即可。

那么代码就很好实现了：

```cpp
#include<iostream>
using namespace std;

int T, a, b, c, r;

int main(){
	cin >> T;
	while(T --) {
		cin >> a >> b >> c >> r;
		if(a > b) swap(a, b); // 保证 a <= b
		if(c + r <= a || c - r >= b) cout << b - a << endl; // 情况 1
		else if(c + r >= b && c - r >= a) cout << c - r - a << endl; // 情况 2
		else if(c - r <= a && c + r <= b) cout << b - c - r << endl; // 情况 3
		else if(c + r >= b && c - r <= a) cout << 0 << endl; // 情况 4
		else cout << b - a - 2 * r << endl;  // 情况 5
	}
	return 0;
}

```

[提交记录](https://www.luogu.com.cn/record/118609720)

$$\text{The End!}$$

---

## 作者：__Octhyccc__ (赞：0)

简要题意：有一根数轴，选择两个点，点 $a$ 和点 $b$，现在有一个点 $c$，在点 $c$ 周围半径 $r$ 个单位长度的地方都有网格，现在一点从 $\min(a,b)$ 出发，到 $\max(a,b)$ 停止，求在这段路程中没有走过网格的整点数（当然 $a,b,c,r$ 是整数）。

**一定要先判断 $a,b$ 哪个大**，一定要注意大小关系，~~我就是因为这个调自闭了。~~

一道分类讨论题，十分的简单，有以下 $5$ 种情况：

先设 $P1$ 为 $c-r$，设 $P2$ 为 $c+r$，那么网格覆盖区间就是 $P1\sim P2$，严格保证 $P1\le P2$，再设 $S$ 为 $b-a$。

- 如果 $P1\le a$，并且 $P2\geq b$，直接输出 $0$。
- 如果 $P2\le a$，或者 $P1\geq b$，说明 $a\sim b$ 之间没有被网格覆盖，直接输出 $S$**（再重申一遍，一定要保证 $a\le b$！）**。
- 如果 $P1\geq a$，并且 $P2\le b$，这就是正常情况，输出 $S-P2+P1$。
- 如果 $P1\le a$，并且 $P2\geq a$，输出 $S-P2+a$。
- 其余情况就输出 $S-b+P1$。

接下来就是愉快的代码啦！

```cpp
#include<cstdio>
#define enter putchar(10)
int max(int x,int y){
	return x>y?x:y;
}
int min(int x,int y){
	return x>y?y:x;
}
void swap(int &x,int &y){
	int z=x;
	x=y,y=z;
}//交换函数，用到了址传递。
int read() {
    register int x = 0,f = 1;register char ch;
    ch = getchar();
    while(ch > '9' || ch < '0'){if(ch == '-') f = -f;ch = getchar();}
    while(ch <= '9' && ch >= '0'){x = x * 10 + ch - 48;ch = getchar();}
    return x * f;
}
void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9){write(x/10);putchar(x%10+'0');}
	else putchar(x+'0');
	return; 
}
int x,a,b,c,r,S;
int P1,P2;
int main(){
	x=read();
	while(x--){
		a=read();b=read();c=read();r=read();
		if(a>b)swap(a,b);//千万别忘了避开这个坑。
		S=b-a;P1=c-r;P2=c+r;
		if(P1<=a && P2>=b){//尽量用 <=，因为有可能因为这个原因 WA 而自闭（这不就是我嘛）。
			puts("0");
		}
		else if((P1<=a && P2<=a) || (P1>=b && P2>=b)){
			write(S);enter;
		}
		else if(P1>=a && P2<=b){
			write(S-P2+P1);enter;
		}
		else if(P1<=a && P2>=a){
			write(S-(P2-a));enter;
		}
		else{
			write(S-(b-P1));enter;
		}//分类讨论。
	}
	return 0;//完美结束。
} 

```

---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1282A) & [CF链接](http://codeforces.com/problemset/problem/1282/A)

## 题意简述：

一条数轴上，从 $c-r$ 到 $c+r$ 的所有点都会被覆盖，求 $a$ 到 $b$ 中有多少点没有被覆盖。

## 思路分析：

这就是一道数学上的分类讨论题，我大致分了 $5$ 种情况：

我们设原左右端点为 $a$ 和 $b$，覆盖左右端点为 $c$ 和 $d$。

1.  $c>b$ 或 $d<a$，这两种情况肯定都不会被覆盖，输出 $b-a$。

2. $b\le d$，只有后半部分被覆盖，输出 $c-a$。

3. $c\le a$，只有前半部分被覆盖，输出 $b-d$。

4. $b\le d$ 且 $c\le a$，也就是上面的 $2$ 和 $3$ 都满足，全部覆盖，输出 $0$。

5. 正常情况，覆盖中间一部分，直接输出 $c-a+b-d$。

## 代码：

```cpp
#include<iostream>
using namespace std;
int a,b,c,r,d;
int main(){
	int T;
	cin>>T;
	while(T--){
		cin>>a>>b>>c>>r;
		if(a>b){
			swap(a,b);//防止a>b
		}
		//计算覆盖范围
		d=c+r;
		c-=r;
		if(c>b||d<a){
			cout<<b-a<<endl;
		}else if(b<=d&&c<=a){
			cout<<0<<endl;
		}else if(b<=d){
			cout<<c-a<<endl;
		}else if(c<=a){
			cout<<b-d<<endl;
		}else{
			cout<<c-a+b-d<<endl;
		}
	}
	return 0;
}
```

---

## 作者：blsya23a2 (赞：0)

## 分析
首先，我们可以把这道题需要的数据都算出来，包括信号范围的两个端点和路线的两个端点，分别表示为 $g,h,i,j$。然后就是分类讨论：

- 当 $i\le g$ 时，

  - 当 $j\le g$ 时，一直在信号范围外，输出 $j-i$。
  - 当 $g<j\le h$ 时，进入信号范围前在信号范围外，输出 $g-i$。
  - 当 $h<j$ 时，进入信号范围前和离开信号范围后在信号范围外，输出 $j-i-2*r$。
- 当 $g<i\le h$ 时，
  - 当 $j\le h$ 时，一直不在信号范围外，输出 $0$。
  - 当 $h<j$ 时，离开信号范围后在信号范围外，输出 $j-h$。
- 当 $h<i$ 时，一直在信号范围外，输出 $j-i$。
## 代码
```python
a=int(input())
for b in range(a):
    c,d,e,f=map(int,input().split())
    g,h=e-f,e+f
    i,j=min(c,d),max(c,d)
    if i<=g:
        if j<=g:
            print(j-i)
        elif j<=h:
            print(g-i)
        else:
            print(j-i-2*f)
    elif i<=h:
        if j<=h:
            print(0)
        else:
            print(j-h)
    else:
        print(j-i)
```

---

## 作者：xuhanxi_dada117 (赞：0)

[题目传送门&题目大意](https://www.luogu.com.cn/problem/CF1282A)

# 解法

直接计算区间覆盖范围，统计即可。

注意多测！

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int _;cin>>_;
	while(_--){//多测
		int a,b,c,r;
		cin>>a>>b>>c>>r;
		int r1=c-r,r2=c+r;//统计覆盖区间左右端点
		if(a>b) swap(a,b);//注意交换左右端点！！
		if(r2<a||r1>b) cout<<b-a<<"\n";//如果原区间没有被覆盖
		else cout<<b-a/*原区间长*/-min(b,r2)+max(a,r1)/*被覆盖长*/<<"\n";//统计答案
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/112265249)



---


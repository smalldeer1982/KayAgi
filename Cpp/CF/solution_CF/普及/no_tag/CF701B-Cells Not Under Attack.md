# Cells Not Under Attack

## 题目描述

给定一个 $n \times n$ 的棋盘和 $m$ 个车以及这 $m$ 个车的坐标，问在放下第 $i$ 个车的时候，有多少个格子不会被已放下的车攻击到。

## 样例 #1

### 输入

```
3 3
1 1
3 1
2 2
```

### 输出

```
4 2 0 
```

## 样例 #2

### 输入

```
5 2
1 5
5 1
```

### 输出

```
16 9 
```

## 样例 #3

### 输入

```
100000 1
300 400
```

### 输出

```
9999800001 
```

# 题解

## 作者：kster__ (赞：3)

因为一辆车会对它所在列和所在行都造成伤害，只需要定义两个变量x和y，分别统计有几列和几行是有车的了。

同一行或者同一列上的车是对相同的一行或一列造成伤害，所以再用两个bool类型的一维数组分别记录下已经放了车的行号和列号（每放下一辆车就把数组中它的横纵坐标对应的值分别改成true），输入时判定一次，如果是false就把x或y加一。

最后用棋盘行数和列数与统计的已占用的行数和列数减出剩余的总行数和剩余的总列数，再将它们相乘就能得到答案。

```cpp
#include <bits/stdc++.h>
using namespace std;

bool x[100010],y[100010];	//存放当前行号和列号是否已经有过车 

int main()
{
	long long m,n,a,b,sx=0,sy=0;	//sx，sy用来存储已经存在车的行数和列数 ，数据比较大，要开long long 
	cin>>m>>n;
	
	for(int i=0;i<n;i++)
	{
		cin>>a>>b;		//输入车的坐标 
		
		if(!x[a]) sx++;		 
		if(!y[b]) sy++;		//如果该行/该列已还没有放过车，sx/sy加一 
		
		x[a]=true;
		y[b]=true;		//把这行/这列的值改成true，表示已经放过了车 
		
		cout<<((m-sx)*(m-sy))<<" ";		//剩余没有放过车的行数和列数相乘就是答案 
	}
	
	return 0;
 } 
```


---

## 作者：Andysun06 (赞：2)

## CF701B 题解
### 题目分析：
这道题是给出了一个棋盘，大小为 $n×n$ 并且里面有 $m$ 个棋子，每个棋子可以攻击与他同一行，列的位置，并且 $n$ 和 $m$ 都很大，数据范围为 ( $1 \leq n \leq 100000, 1 \leq m \leq min(100000,n^{2} )$)。我们要输出每放一个棋子后，有多少个地方是攻击不到的。
### 题目难度：
个人认为在 普及/提高- 左右。
### 算法分析：
当看到这题的第一眼，我就想到了二维数组模拟，但是，在看了数据范围之后，发现行不通，二维数组绝对会爆，于是我就想到了 $stl$ 中的 $set$ 成员函数，下面我们来介绍一下什么是 $set$：

- 定义 $set$：

>格式：$set <value\_type> name;$
>
>其中 $value\_type$ 是 $set$ 中所要存储的元素类型，例如 `int`,`string`,或自定义的结构体名称。
>
>定义 $set$ 还要包含 $set$ 头文件，即 `#include<set>`。

- 介绍 $set$

> $set$ 的内部实现其实是一棵红黑树，`int`，`string` 等C++自带变量类型已经帮我们定义好了小于号，也就是他会自动帮我们进行排序，其中 `int` 在 $set$ 中从小到大排，`string` 在 $set$ 中按字典序排。

- 使用 $set$

> $set$ 有众多的内置函数，包括 `insert(x)`,`erase(x)`,`empty()`,`size()`,`clear()`,`find(x)` 等等，下面让我们来介绍一下这些内置函数的作用。
>
> 1.`insert(x)`/`erase(x)` 是在 $set$ 中 **插入/删除** 一个元素 $x$。
>
> 2.`empty()`/`size()` 是判断 $set$ 是否为空/返回 $set$ 的元素个数。
>
> 3.`clear()` 清空一个 $set$ 的所有元素。
>
> 4.`find(x)` 查找 $set$ 中是否有 $x$ 这个元素。

了解了 $set$ 函数之后，就可以开始编写我们的程序了。

### 完整代码&解析：
```cpp
#include<iostream>
#include<cstdio>
#include<set> //包含 set 的头文件
#define ll long long 
using namespace std; //定义 long long 变量
ll n,m,a,b,ans;
int i;
int main() {
   set<ll> set1,set2; //定义一个 $set$
   set1.clear(); //把两个 $set$ 函数清空，具体见上面
   set2.clear();
   scanf("%lld%lld",&n,&m);//输入，注意要用 %lld
   for(i=1; i<=m; ++i) {
      scanf("%lld%lld",&a,&b); //输入，注意要用 %lld
      set1.insert(a); //插入一个元素a
      set2.insert(b); //插入一个元素b
      ll len1=set1.size(),len2=set2.size(); //把 set1 和 set2 的长度分别赋值给 len1 和 len2
      ans=n*n-len2*n-n*len1+len1*len2; //用公式计算答案 ans
      printf("%lld ",ans); //输出，注意要用 %lld
	}
}
```
希望本题解对大家有帮助，也感谢管理员百忙之中抽空为我审核题解，谢谢！

---

## 作者：ImposterAnYu (赞：1)

~~我从未见过如此水的黄题。~~
# 解析
我们先设 $h_i$ 表示第 $i$ 行是否有车，$l_i$ 表示第 $i$ 列是否有车，$hh$ 表示现在有 $hh$ 行有车，$ll$ 表示现在有 $ll$ 列有车。

每当地图上新加入一个车时（假设 TA 在第 $i$ 行，第 $j$ 列），我们可以分情况讨论：

当 $h_i = 0$ 时，说明这一整行都没有车。这时，这一行里没被攻击过的格子都会被这个新的车攻击到。

那么，在这之前，第 $i$ 行究竟有多少个格子没被攻击到呢？我们可以想到，当第 $i$ 行没有车时，被攻击到的格子只可能是被那一列的车给攻击了，所以，在这之前，第 $i$ 行只可能有 $ll$ 个格子被攻击了。那么，这一行未被攻击的格子数自然就是 $n - ll$ 了。

但是，现在第 $i$ 行既然放入了一个新车，就意味着这一行所有的格子都会被攻击到。所以，放了这个车后，未被攻击的格子数要减去 $n - ll$。

当 $h_i = 1$ 时，说明第 $i$ 行已经有车了，这一行的格子已经被全部攻击了，所以不需要统计答案。

至于 $l_i = 0$ 和 $l_i = 1$ 的情况，也就同理啦~
# code
```c++
#include<bits/stdc++.h>
#define int1 long long
#define p 100005
using namespace std;
int1 n,m,x,y,s,hh,ll;
bool h[p],l[p];
int1 read(){//快读。
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch & 15);
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){//快写。
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar((x % 10) ^ 48);
  	return ;
}
int main(){
	n = read(),m = read(),s = n * n;
	while(m--){
		x = read(),y = read();
		if(!h[x]){//如果第 x 行没有车，
			hh++,s -= n - ll,h[x] = 1;统计答案，标记。
		}
		if(!l[y]){//如果第 y 列没有车，
			ll++,s -= n - hh,l[y] = 1;统计答案，标记。
		}
		print(s);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Mysterious_bird (赞：1)

# CF701B 题解
#### 题目分析：
这题是给出一个大小为n\*n的棋盘，然后在上面放上m个“车”，每个“车”的坐标为Xi和Yi，要你分别算出**各个棋子**放上去后棋盘上还有多少个**安全位置**

#### 使用算法：
本人一开始看到这篇水题也以为是一道二维模拟题，但看清题目要求后，发现n的范围很大，不能开二维数组，就想到了STL中的set

1：set是自动分配大小的，所以不用考虑n的大小

2：set用于计算一列的大小很简便

#### 做题思路：
这道题算不上很难，我们只要稍加思考就能想出来，接下来讲一下我的方法：

0 0 0 0 0

0 0 0 0 0

0 0 0 0 0

0 0 0 0 0

0 0 0 0 0

我们模拟出一个5\*5的棋盘

接着在（1,1）的地方放置一个“车”

h里插入1，v里插入1（详情见代码）

而“车”能吃到的地方就是下图

1 1 1 1 1

1 0 0 0 0

1 0 0 0 0

1 0 0 0 0

1 0 0 0 0

所以计算后我们发现，目前的安全位置就是（5-1）\*（5-1）=16
再向（3,1）放置“车”

1 1 1 1 1

1 0 0 0 0

1 1 1 1 1

1 0 0 0 0

1 0 0 0 0

目前的安全位置就是（5-2）\*（5-1）=12

而减去的2就是目前纵轴上插入的2枚，减去的1就是横轴上插入的1枚

1 1 1 1 1  <-（第一行）

1 0 0 0 0

1 1 1 1 1  <-（第二行）

1 0 0 0 0

1 0 0 0 0

^（一列）

代码实现：
```cpp
now=(n-h.size())*(n-v.size());  //计算安全位置的数量
```
#### 代码部分：
~~我知道你们就想看这个~~
```cpp
#include <cstdio>
#include <set>
using namespace std;
set <long long> h;  //横方向
set <long long> v;  //纵方向
long long n,m,now;  //n表示棋盘大小，m表示放置“车”的数量，now表示现在还剩的安全位置
int main()
{
    scanf("%lld%lld",&n,&m);    //这里要注意，使用scanf和printf时输入输出long long类型的数要用%lld
    for(int i=1;i<=m;i++)
    {
        long long x,y;
        scanf("%lld%lld",&x,&y);    //这里要注意，使用scanf和printf时输入输出long long类型的数要用%lld
        h.insert(x);    //插入元素x
        v.insert(y);    //插入元素y
        now=(n-h.size())*(n-v.size());  //计算安全位置的数量
        printf("%lld ",now);    //这里要注意，使用scanf和printf时输入输出long long类型的数要用%lld
    }
    printf("\n");   //换行
    return 0;   
}
```
这是本xxs的第一篇题解，希望可以通过审核，谢谢

---

## 作者：qfpjm (赞：0)

# 题目大意

- 在一个 $n \times n$ 的棋盘上，一次放下 m 个车，每个车的摆放位置为 $(x_i,y_i)$。问摆第 i 个车时，棋盘上还有几个位子不受到攻击。

# 题解

- 做这题之前，要知道车的攻击范围。即为第 $x_i$ 行的所有格和第 $y_i$ 行的所有格。

- 首先想到用二维数组标记，但是对于 $1\leq n\leq 100000$ 的数据是明显会 MLE 的。

- 那么，我们就可以只考虑每行每列，无需每个格子考虑。

- 于是，我们可以开两个数组，表示第 i 行和第 i 列的格子有没有受到攻击。 因为是放车之前统计，那么如果放下前，第 i 行和第 i 列没有受到攻击，那么受到攻击的行列数量分别加 1。

- 如果看不懂，那么我就画一下图：

初始棋盘：
```
0 0 0
0 0 0
0 0 0
```
第一个车的位置为 $1,1$：

```
1 1 1
1 0 0
1 0 0
```
那么受到攻击的行列数量为 1 和 1，那么剩下的格子数量为 $(3-1)\times(3-1)$。

以此类推。

- 综上，我们可以得到剩下格子数的公式（cnt1 为被攻击行的数量，cnt2 为被攻击列的数量）：$(n-cnt1)\times(n-cnt2)$。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

long long n, m, x, y, cnt1, cnt2;
bool visited1[1000005], visited2[1000005];

int main()
{
	cin >> n >> m;
	for (int i = 1 ; i <= m ; i ++)
	{
		cin >> x >> y;
		if (!visited1[x])
		{
			cnt1 ++;
		}
		if (!visited2[y])
		{
			cnt2 ++;
		}
		visited1[x] = 1;
		visited2[y] = 1;
		cout << (n - cnt1) * (n - cnt2) << " ";
	}
	return 0;
}
```


---

## 作者：YuntianZhao (赞：0)

# CF701B

两个set快速水过。

两个set分别记录被占的行和列，显然空余的格子数量是$(n - row.size()) * (n - col.size())$。

时间复杂度是$O(N log N )$的，可以水过...

```c++
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;
long long n, m, x, y, cnt1, cnt2;
set<int> col;
set<int> row;

int main() {
  int i, j, k, t;
  cin >> n >> m;
  long long now = 0;
  while (m--) {
    cin >> x >> y;
    col.insert(x);
    row.insert(y);
    now = (n - col.size()) * (n - row.size());
    cout << now << " ";
  }
  return 0;
}

```





---


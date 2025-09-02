# Fractal Shortest Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/panasonic2020/tasks/panasonic2020_f

非負整数 $ K $ に対し、以下のようにレベル $ K $ のフラクタルを定義します。

- レベル $ 0 $ のフラクタルとは、白いマス一個のみからなるグリッドである。
- $ K\ >\ 0 $ のとき、レベル $ K $ のフラクタルは $ 3^K\ \times\ 3^K $ のグリッドである。このグリッドを $ 3^{K-1}\ \times\ 3^{K-1} $ のブロック $ 9 $ 個に分割したとき、
  - 中央のブロックは全て黒マスからなる。
  - 他の $ 8 $ 個のブロックは、レベル $ K-1 $ のフラクタルになっている。

たとえば、レベル $ 2 $ のフラクタルは下図の通りです。

![レベル 2 のフラクタル](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_panasonic2020_f/b750f0bcdb56d49489148f9973188d07d9333b40.png)

レベル $ 30 $ のフラクタルにおいて、上から $ r $ 番目、左から $ c $ 番目のマスを $ (r,\ c) $ と書きます。

$ Q $ 個の整数組 $ (a_i,\ b_i,\ c_i,\ d_i) $ が与えられます。 それぞれの組について、$ (a_i,\ b_i) $ から $ (c_i,\ d_i) $ への距離を求めてください。

ただし、$ (a,\ b) $ から $ (c,\ d) $ への距離とは、以下の条件を満たすような最小の $ n $ とします。

- ある白マスの列 $ (x_0,\ y_0),\ \ldots,\ (x_n,\ y_n) $ が存在して、以下の条件を満たす。
  - $ (x_0,\ y_0)\ =\ (a,\ b) $
  - $ (x_n,\ y_n)\ =\ (c,\ d) $
  - 任意の $ i\ (0\ \leq\ i\ \leq\ n-1) $ に対し、マス $ (x_i,\ y_i) $ と $ (x_{i+1},\ y_{i+1}) $ は辺で接する。

## 说明/提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 10000 $
- $ 1\ \leq\ a_i,\ b_i,\ c_i,\ d_i\ \leq\ 3^{30} $
- $ (a_i,\ b_i)\ \neq\ (c_i,\ d_i) $
- $ (a_i,\ b_i),\ (c_i,\ d_i) $ は白マスである。
- 入力は全て整数である。

### Sample Explanation 1

!\[\](https://img.atcoder.jp/panasonic2020/b590cee9850abdad4109ab940f9efe5a.png)

## 样例 #1

### 输入

```
2
4 2 7 4
9 9 1 9```

### 输出

```
5
8```

# 题解

## 作者：JackMerryYoung (赞：2)

# 前言

小清新分类讨论题。

# 正文

类似于一般有无限的题目，我们考虑分治。

不过要分类讨论（借张图）：

![](https://cdn.luogu.com.cn/upload/image_hosting/qoy0f4di.png)

将 123, 456, 789 各自分一组。

设级别为 $K$, 则大小为 $3^K$.

## 1. $K = 0$

由于没有黑块阻隔，所以 $y$ 坐标相减即可。

## 2. $K \neq 0$

## 2. 1 不在同一组

除了 2 8, 求出曼哈顿距离即可。

2 8 也可以利用轴对称性，交换 $x, y$ 坐标再求解。

## 2. 2 在同一组，但是在 456 这一组

肯定要绕过 5.

考虑左右两种走法即可。答案（不会用 $\LaTeX$ 表示取模，所以用了代码块请见谅）：

`abs(b - d) + min(a % size + c % size + 2, size * 2 - a % size - c % size)`

（$size = 3^{K - 1}$）

## 2. 3 在同一组，但是不在 456 这一组

递归分治求解即可。

注意 $y$ 坐标不变, $x$ 坐标模去 $3^{K - 1}$.

# 代码 

``` cpp
// Problem: AT5809 Fractal Shortest Path
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT5809
// Memory Limit: 1000 MB
// Time Limit: 2000 ms

#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll Q;

ll div(ll a, ll b, ll c, ll d, ll k)
{
	if(k == 0)
		return abs(b - d);
		
	ll size = pow(3ll, (long long) k - 1ll);
	if(a / size != c / size) 
		return abs(a - c) + abs(b - d);
		
	else if(a / size == 1 && abs(b / size - d / size) >= 2)
		return abs(b - d) + min(a % size + c % size + 2, size * 2 - a % size - c % size);
		
	else
		return div(a % size, b, c % size, d, k - 1);
}

signed main()
{
	cin >> Q;
	for(ll i = 1; i <= Q; ++ i)
	{
		ll a, b, c, d;
		cin >> a >> b >> c >> d;
		-- a; -- b; -- c; -- d;
		if(abs(a - c) > abs(b - d)) 
		{
			swap(a, b);
			swap(c, d);
		}
		
		cout << div(a, b, c, d, 30) << endl;
	}
    
	return 0;
}
```

# 后言

思维题一定要多思考...

---

## 作者：封禁用户 (赞：1)

### 思路：  
将图分为 9 块，其中 123 为一层，456 为一层，789为一层。


![](https://cdn.luogu.com.cn/upload/image_hosting/qoy0f4di.png)
1.两点在不同层（除了 2 ，8 ）：两点之间的距离即为两点曼哈顿距离，

![](https://cdn.luogu.com.cn/upload/image_hosting/87kmaqwo.png)

为了避免（2，8）这种情况，可以通过交换（x，y）转化为（4，6）。

下图中(0,3)->(3,0),(8,5)->(5,8)


![](https://cdn.luogu.com.cn/upload/image_hosting/jrynzkcw.png)
2.两点在同一层，并且不在456 这层：可以往下递归，y轴保持不变。

3.两点在同一层，并且在 456这层：由于需要绕过中间这块，只要判断往左走还是往右走即可。

向左走，走过的距离 $$    \left |  y1-y2\right | +x1 \%w+1+x2 \%w +1 $$ 由来，详见下图


![](https://cdn.luogu.com.cn/upload/image_hosting/yqbve2r7.png)
向右走，走过的距离 $$\left |  y1-y2\right | +\left ( w-x1\%w \right )

+\left ( w-x2\%w \right )$$由来，详见下图

![](https://cdn.luogu.com.cn/upload/image_hosting/r7o5vtli.png)

在向左走，向右走，路径中，取最小值。
### 代码:
```cpp
#include <cstdio>

#include <algorithm>

#define LL long long

using namespace std;

LL width[35];

LL cal(LL x1,LL y1,LL x2,LL y2,int level){

	LL w;

	if(level==0)return abs(y1-y2);//路径上一直未遇到黑色方块

	w=width[level-1];//当前级别level,深入到9个level-1级别中进行处理

	if(x1/w!=x2/w)return abs(x1-x2)+abs(y1-y2);//处在不同层中，可用曼哈顿距离处理

	if(x1/w==1&&abs(y1/w-y2/w)>=2)//x1/w==x2/w  处于同一层，且在456这一层

		return abs(y1-y2)+min(x1%w+1+x2%w+1,(w-x1%w)+(w-x2%w));//x1%w+1+x2%w+1向左推进，(w-x1%w)+(w-x2%w)向右推进

	return cal(x1%w,y1,x2%w,y2,level-1);//当前处理不了，只能深入到level-级别中进行处理，固定abs(y1-y2),针对x进行处理,因x1/w==x2/w，故可取模

}

int main(){

	int i,q;

	width[0]=1;

	for(i=1;i<=29;i++)width[i]=width[i-1]*3;

	LL x1,y1,x2,y2;

	scanf("%d",&q);

	while(q--){

		scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);

		x1--,y1--,x2--,y2--;//涉及取模运算，故第1行变成第0行，故第1列变成第0列

		if(abs(x1-x2)>abs(y1-y2))swap(x1,y1),swap(x2,y2);//抓住图形具有对称性，避免出现258的情况。

		printf("%lld\n",cal(x1,y1,x2,y2,30));

	}

	return 0;

}

---

## 作者：nynkqh_yzp (赞：0)

# 一、性质
对于两个黑色块，在一维坐标上不会相交，只有可能包含或相离。

由上述性质可以推出整个过程中只需要专门绕开最大的一个黑色块，就可以绕开全部的黑色块。

# 二、解法
枚举黑色块的大小，判断两点间是否存在黑色块，并计算答案，具体实现请看代码。
# 三、代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
long long q;
inline long long ck(long long a1,long long b1,long long a2,long long b2){
	if(a1>a2)
		swap(a1,a2),swap(b1,b2);
	long long an=1,ans=0;
	for(int i=1;i<=30;i++){
		if(a2/an-a1/an+1>=3)                      //判断两点间的宽度是否可能有指定大小的黑色块 
			if(b1/an==b2/an)                      //判断两点间的高度是否在同一黑色块的覆盖范围内 
				if(b1%(an*3)>=an&&b1%(an*3)<an*2) //同上 
					ans=min((min(b1%an,b2%an)+1)*2,(an-max(b1%an,b2%an))*2);//计算绕路的花费 
		an*=3;
	}
	return ans;
}
int main(){
	scanf("%lld",&q);
	while(q--){
		long long a1,a2,b1,b2,ans=0;
		scanf("%lld%lld%lld%lld",&a1,&b1,&a2,&b2);
		a1--,b1--,a2--,b2--;
		ans=max(a2-a1,a1-a2)+max(b1-b2,b2-b1);//计算不绕路情况下的花费，即曼哈顿距离 
		ans+=ck(a1,b1,a2,b2)+ck(b1,a1,b2,a2);//从两个维度分别去找黑色块，但实际只会有一个维度可能有黑色块 
		printf("%lld\n",ans);
	}
	return 0;
}
```

---


# Caisa and Sugar

## 题目描述

Caisa 要举办一个派对，他要购买巧克力蛋糕的原料。为此，他去了镇上最大的超市。

不巧，他只有 $s$ 美元买食糖。但这可不是悲伤的理由，因为超市里有 $n$ 种食糖，或许他可以买某一个。但这还没完。超市有着非常特别的找零政策：把糖果给买家作为找零，而不是美分。当然，给的糖果的数量始终不会超过 $99$，因为每个卖家都会最大化找零中美元的数量（$100$ 美分可以换成 $1$ 美元）。

Caisa 只想买一种食糖，同时他也希望找零中的糖果数量最多。他最多能得到多少糖果？请注意，Caisa 并不想降低买食糖的开销，他只想得到最多的糖果找零。

## 说明/提示

在第一个样例中，Caisa 可以买第四种食糖，这种情况下他能得到 $50$ 个糖果找零。

## 样例 #1

### 输入

```
5 10
3 90
12 0
9 70
5 50
7 0
```

### 输出

```
50
```

## 样例 #2

### 输入

```
5 5
10 10
20 20
30 30
40 40
50 50
```

### 输出

```
-1
```

# 题解

## 作者：丧黑福造 (赞：3)

题意：Caisa去超市买东西，有s美元，一美元等于100美分，现在给定n种商品的价格x美元y美分，超市找零是用糖果替代美分，一美分为一颗糖果，Caisa想要尽量多的糖果。

思路：模拟，当x==s时注意判断y。如果y=0，则前面的x可以等于s，否则不能取等。然后将y转化为100就可以了。

$code:$
```cpp

#include <stdio.h> 
main () {
    int n, s, ans = -1, x, y;
    scanf("%d%d", &n, &s);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &x, &y);
        if (x < s || (x == s && y == 0))
            ans = ans > (y == 0 ? 0 : 100 - y) ? ans : (y == 0 ? 0 : 100 - y);//这行代码相当与ans=max(ans,y==0?0:100-y);
    }
    printf ("%d\n", ans);
    return 0;
}
```

---

## 作者：Light_Star_RPmax_AFO (赞：2)

# 思路——模拟 & 打擂台

题目还是很好理解的，就是 **Caisa** 想要自己得到找零的糖果最多。

这个商人少了几美分就会找你几颗糖。

那么我们就可以去模拟再打擂台就可以了。

## 核心代码

我们先判断是否有解，如果钱大于了钱的总数我们就无解（ _注意我们要取等，否则如果价格等于钱的时候他也会输出 -1_ ）。

如果有解我们就算出会找出几个糖果（ _这里也需要特判，否则如果在 $y_i=0$ 的时候，本来不会找零，可是代码会判断为找糖 100_ ）。

```cpp
for(int i=1;i<=n;i++){
	if (x[i] + 0.01 * y[i]) <= s) {
		maxn = max(maxn, (y[i] != 0 ? 100 - y[i] : 0));
		g = 1;
	}
}
```
# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

inline void read(int& a)
{
	int s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch>'9')
	{
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	a = s * w;
}//快读部分可以省略。

int main()
{
	int n;
	double s;//这里使用 double 来存储 s 因为美分需要用到。
	cin >> n >> s;//读入糖果数量与钱数。
	double x[101]，y[101];
	for (int i = 1; i <= n; i++) {
		read(x[i]);
		read(y[i]);
	}//将价格读入。
	int maxn=INT_MIN;//记录答案。
	bool g = 0;//记录有没有解。
	for(int i=1;i<=n;i++){
		if (x[i] + 0.01 * y[i]) <= s) {
			maxn = max(maxn, (y[i] != 0 ? 100 - y[i] : 0));
			g = 1;
		}
	}
	if (!g)cout << -1;
	else cout << maxn;
	return 0;
}

```



---

## 作者：ice_fish01 (赞：1)

## $\texttt{CF463A Caisa and Sugar}$ 题解

## $\text\color{red}Knowledge$

本题考查对**循环语句**的应用。

## 文字题解

### 解析

当看到求糖果找零的最大值时，我们很容易想到“打擂台”，使用方法如下：

- 我们定义一个存最大值的变量 $\text{maxi}$；
- 从头遍历所有元素，使用 $\max$ 函数替换或比较 $\text{maxi}$ 与当前元素谁更大。

**打擂台代码如下：**

```cpp
int maxi = -1,a;
for(int i = 1;i <= n;i++)
{
	cin >> a;
	maxi = max(a,maxi);
}
```

注意事项：

- 需要将 $\text{maxi}$ 定义一个很小的值（比元素中最小的值要小）；

**本题另外一个考点：模拟（本处不做过多解释）**

## $\text\color{green}AC$ $\text\color{green}Coding$

```
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n,s,x,y,maxi = -1,price; //定义变量
	cin >> n >> s;
	s *= 100; //将s化为美分 
	for(int i = 1;i <= n;i++)
	{
		cin >> x >> y;
		price = x * 100 + y;
		if(price > s) //钱太少了，不够买
			continue;
		if(y == 0) //应对y=0的情况，防止找零100颗糖果
			y += 100;
		maxi = max(maxi,100-y); //打擂台
	}
	cout << maxi;
	return 0;
}
```


---

## 作者：xiaobeng_0912 (赞：0)

## 题意：

给你 $n$ 种糖以及它的标价，和 $s$ 元，让你选择找零最多的那一种。


## 分析：

先输入，统一单位为美分。再判断钱够不够买这种糖，如果够，就计算赠送的糖的数量并特判没有赠送糖（即刚刚好够买）的种类（防止算成赠送 $100$ 个），最后打擂台求出最大值。

-----
## AC代码（禁止抄）：
```cpp
#include<bits/stdc++.h>//万能头，懒人必备
using namespace std;//max函数需要
int main(){
	int n,s,x,y,maxn=-1,p;
	scanf("%d%d",&n,&s);
	s*=100;//变为美分，方便计算
	for(int i=0;i<n;i++){
		scanf("%d%d",&x,&y);
		p=x*100+y;//统一单位到美分
		if(p<=s){ //钱够买这种糖
			maxn=max(maxn,y==0?0:100-y); //打擂台，特判0
		}
	}
	printf("%d",maxn);//开头maxn就是-1了，不用特判
	return 0;
}
```

---

## 作者：NotNaLocker (赞：0)

## Caisa and Sugar 题解
### 题目算法：
纯纯的**模拟**。

### 变量初始化：
$candy$ 结构体：为了防止题解代码重复，我把 $x_i$，$y_i$ 两个变量放进了这个结构体中。

$maxx$，初值 $\texttt{-1}$，要输出的最大值。如果每次输入都不符合题意，直接输出初值即可。

### 算法实现の细节：
$s$ 与 $x_i$ 变量要乘以 $100$，毕竟正整数比浮点数好算。

当 $y_i$ 为 $0$ 时，取最大值的 $x_i$ 值会多加 $1$，所以要将 $y_i$ 变为 $100$，具体原因见代码。

### 算法具体实现：
重点代码如下：
```cpp
for(i=1->n){
	cin>>candy[i].x>>candy[i].y;
	if(candy[i].x*100+candy[i].y<=s*100){
		if(candy[i].y==0) candy[i].y=100; //特判
		maxx=max(maxx, 100-y_i);
	}
}
```
题目中要求**最大的糖果找零**，意思就是让第 $i$ 种糖果的总钱数与 $x_i+1$ 的差要**最大**。因此取最大值时需要将 $maxx$ 与 $(x_i+1)\times 100 - (x_i\times 100 + y_i)$ 比较，可以化简为 $100-y_i$。

## AC coding
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s;
struct mod{
	int x,y;
}candy[105];
int main(){
	cin>>n>>s;
	int maxx=-1;
	for(int i=1;i<=n;i++){
		cin>>candy[i].x>>candy[i].y;
		if(candy[i].x*100+candy[i].y<=s*100){
			if(candy[i].y==0) candy[i].y=100;
			maxx=max(maxx,100-candy[i].y);
		}
	}
	cout<<maxx;
	return 0;
} 
```
### Thanks for watching.

---

## 作者：qfpjm (赞：0)

# 题解

- 由于只有美分可以把糖果给买家作为找零，所以只需要考虑两个问题：

	1. Caisa 的钱够不够买糖。
   1. 如果够，那获得的糖果是不是最多的。
   
- 对于第一个问题，判断一下就行了。第二个问题用一个变量记录，取 $\max$ 即可。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, s, ans = -1;

int main()
{
	cin >> n >> s;
	for (int i = 1 ; i <= n ; i ++)
	{
		int x, y;
		cin >> x >> y;
		if (x < s || (x == s && y == 0))
		{
			if (ans == -1)
			{
				ans = 0;
			}
		}
		if (x < s)
		{
			if (y != 0)
			{
				ans = max(ans, 100 - y);
			}
		}
	}
	cout << ans;
}
```


---

## 作者：vincehex (赞：0)

只买一种类型的糖果,也只买一次。因为使用美分来替代糖果，所以遍历一次找最大的就可以了。
```cpp
#include <bits/stdc++.h> 
using namespace std;
int main() {
	int n, s, mx = -1;
	cin >> n >> s;
	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		x += (y > 0);
		if(x <= s) {
			mx = max(mx, (100 - y) % 100);
		}
	}
	cout << mx;
	return 0;
}
```


---


# Slava and tanks

## 题目描述

Slava plays his favorite game "Peace Lightning". Now he is flying a bomber on a very specific map.

Formally, map is a checkered field of size $ 1×n $ , the cells of which are numbered from $ 1 $ to $ n $ , in each cell there can be one or several tanks. Slava doesn't know the number of tanks and their positions, because he flies very high, but he can drop a bomb in any cell. All tanks in this cell will be damaged.

If a tank takes damage for the first time, it instantly moves to one of the neighboring cells (a tank in the cell $ n $ can only move to the cell $ n-1 $ , a tank in the cell $ 1 $ can only move to the cell $ 2 $ ). If a tank takes damage for the second time, it's counted as destroyed and never moves again. The tanks move only when they are damaged for the first time, they do not move by themselves.

Help Slava to destroy all tanks using as few bombs as possible.

## 样例 #1

### 输入

```
2
```

### 输出

```
3
2 1 2 ```

## 样例 #2

### 输入

```
3
```

### 输出

```
4
2 1 3 2 ```

# 题解

## 作者：BYWYR (赞：3)

## Solution

因为坦克只有 $2$ 条命，所以炸 $3$ 次必炸死。

以下为轰炸方法：

- 先炸偶数格的坦克，这时坦克会到奇数格；

- 然后炸奇数格的坦克，原本在奇数格的坦克就会到偶数格去，这时从偶数格移动过来的坦克就会被摧毁；

- 最后再炸一次偶数格内的坦克即可。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
int main(){
    cin>>n;
    cout<<n+n/2<<endl;
    for(int i=2;i<=n;i+=2) 
		cout<<i<<" ";
    for(int i=1;i<=n;i+=2) 
		cout<<i<<" ";
    for(int i=2;i<=n;i+=2) 
		cout<<i<<" ";
	return 0;
}
```


---

## 作者：Wsy_flying_forever (赞：3)

## 有趣的推理题  

### 思路
看到所有其他题解对于为什么三次循环能炸死所有坦克的解释都是《可以证明》《想要》《直接上结论》（这根本就是凭着感觉，而没完全体现题解的作用），本文则会解释其原因。  

1. 第一次我们任选偶数格或奇数格进行轰炸，那么被轰炸坦克所在格子的奇偶性取反。    
ps: 由于奇偶性某种意义上可以看成对称的性质，所以我们不妨设第一次轰炸奇数格。那么剩下两次的操作也就一目了然。  
2. 轰炸偶数格，原先奇数格坦克全部被摧毁，倘若偶数格原来有坦克，偶数格坦克转移到奇数格。  
3. 再次轰炸奇数格，全部坦克被摧毁。

至此，我们对三次轰炸有了清晰的认识，理解之后，代码实现其实很简单。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    cout<<n+n/2<<endl;
    for(int i=2;i<=n;i+=2) cout<<i<<" ";
    for(int i=1;i<=n;i+=2) cout<<i<<" ";
    for(int i=2;i<=n;i+=2) cout<<i<<" ";
}
```
完结撒花！


---

## 作者：xiaozeyu (赞：2)

**这道题想得烦，写得简单**

**想要最优就要每次炸死最多的坦克**

**先分割开来，输出**

**我们可以三重循环，因为坦克两条命，三次最优必死光。**

**坦克被打会动，所以每次起始位置不一样，2,1,2**

**炸了后有坦克的地区中间一格为空，所以i+=2**


上代码


------------


```c
#include <bits/stdc++.h>
using namespace std;
int n;
int main()
{
	cin>>n;//输入
	cout<<n+n/2<<endl;//先输出一个
	for(int i=2;i<=n;i+=2)//第一回炸
		cout<<i<<" ";
	for(int i=1;i<=n;i+=2)//第二回炸，炸的都是有了坦克的地方
		cout<<i<<" ";
	for(int i=2;i<=n;i+=2)//被炸后移动，炸移动后位置
		cout<<i<<" ";//每次要有空格
}
```


---

## 作者：Nuyoah_awa (赞：1)

### 题目大意
有一个 $1\times n$ 的棋盘格子段，其单元格的编号从 $1$ 到 $n$，每个单元格中可以有一个或多个坦克。

每次可以在任意格子里投炸弹，这个格子里的所有坦克都会被损坏。每个坦克有两条命，求如何投炸弹可以摧毁所有坦克并且使用尽可能少的炸弹

### 题目分析

这道题很明显是一道构造题，只需找到通解即可

因为一辆坦克有两条命，所以我们至少要打两次。

如果我们每回将所有的格子扔炸弹，扔两次，总炸弹数为 $n \times 2$。

为了使扔的炸弹尽可能的少，我们可以先将所有偶数格扔炸弹，这样原本在偶数格的坦克会来到奇数格，并且少一条命，奇数格的坦克不动。然后再将所有奇数格扔炸弹，这样原本在偶数格的坦克就没了，原本在奇数格的坦克到偶数格并且少一条命。最后，只需要再在偶数格投炸弹就可以一举歼灭了。

### code
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int n;

int main()
{
    scanf("%d", &n);
    printf("%d\n", n / 2 + n);
    for(int i = 2;i <= n;i += 2)
		printf("%d ", i);
    for(int i = 1;i <= n;i += 2)
		printf("%d ", i);
    for(int i = 2;i <= n;i += 2)
		printf("%d ", i);
    return 0;
}
```

---

## 作者：kimidonatsu (赞：1)

# CF877C Slava and tanks 题解

## 题意简述

有一条长度为 $n$ 的 $map$，每个格子 $map_i$ 有坦克若干，每次都可以轰炸一个格子 $map_i$ 中的所有坦克，每只坦克都需要进行两次轰炸才能摧毁，第一次轰炸后被炸的坦克就会移动到 $map_{i - 1}$ 或 $map_{i + 1}$。题目要我们摧毁所有坦克使用尽可能少的炸弹。

## 思路分析

其实比较烦的是坦克会移动，那我们就分批来炸，每只坦克有 2 条命，也就是炸 3 次才必死，所以便有以下思路：

1. 此时我们第一次先轰炸偶数格子内的坦克，这个时候偶数格子内的坦克会移动到奇数格子内；
2. 这时我们再轰炸一次奇数格子中的坦克，奇数格子内中的坦克会移动回偶数格子，此时轰炸两次的坦克已被摧毁，只剩下在偶数格子中的坦克还需轰炸一次；
3. 轰炸偶数格子中的坦克，轰炸完毕。

这道题确实很难下标签，类似贪心的思路，实际又是推理题。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;

void work() {
    for (int i = 2; i <= n; i += 2) printf("%d ", i);
    for (int i = 1; i <= n; i += 2) printf("%d ", i);
    for (int i = 2; i <= n; i += 2) printf("%d ", i);
}

int main() {
    scanf("%d", &n);
    printf("%d\n", n + n / 2);
    work();
    return 0;
}

```


---

## 作者：力巴尔 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF877C)

这道题最烦的就是坦克会动，所以不能仅仅只是把所有格子炸一遍。

因为坦克只能在被炸后移动**一格**，所以我们可以将格子按编号的奇偶分为两类，再按一定顺序轰炸，就可以得到正确做法：

首先将所有奇数格炸一遍，然后将所有偶数格炸一遍，最后再把所有奇数格炸一遍。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    cout<<n / 2 + n<<"\n";
    for (int i = 2;i <= n;i += 2)
        cout<<i<<" ";
    for (int i = 1;i <= n;i += 2)
        cout<<i<<" ";
    for (int i = 2;i <= n;i += 2)
        cout<<i<<" ";
}
```


---

## 作者：___wa___ (赞：0)

一道推理题。
### 题意

现有一排坦克，每个坦克需要炸两次才可以摧毁，需要用最少的炸弹摧毁坦克。

### 思路

示意图：
![](https://cdn.luogu.com.cn/upload/image_hosting/cuiarf3h.png)

我们把奇数和偶数格分开标两种颜色。

如果要用最少的炸弹摧毁最多的坦克，就要尽量让一枚炸弹炸到更多的坦克，因为坦克被炸到一次后会移到相邻的一格，改变坐标奇偶性，坦克就更密集了，所以可以先炸偶数格。

（不炸奇数格是因为在 $n$ 是奇数的情况下奇数格比偶数格多，先炸奇数格需要的炸弹也就更多。

![](https://cdn.luogu.com.cn/upload/image_hosting/jc3a17wa.png)

炸完之后就是这个样子。
这时再炸奇数格可以摧毁原坐标是偶数的坦克，并炸到一次原坐标是奇数的坦克。
![](https://cdn.luogu.com.cn/upload/image_hosting/ulgre897.png)

上次炸完后原坐标是奇数的坦克移到了偶数格，所以最后只要再炸一次偶数格就能炸毁所有坦克了。






---

## 作者：Not_lazy (赞：0)


## 思路
因为如果一辆坦克第二次受到伤害，它将被视为被摧毁，再也不会移动，所以可以视为坦克只有 $2$ 条命，第三次就会被摧毁。

但是坦克会动，就不能仅仅是全炸一遍。

具体做法是先炸偶数格，再炸奇数格，最后再炸一遍偶数格。

**输出注意要空格！**

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    scanf("%d",&n);
    printf("%d\n",n/2+n);
    for(int i=2;i<=n;i+=2)printf("%d ",i);
    for(int i=1;i<=n;i+=2)printf("%d ",i);
    for(int i=2;i<=n;i+=2)printf("%d ",i);
    return 0;
}
```


---

## 作者：_Weslie_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF877C)

首先，让我们来想：

如果我们轰炸第 $i(i>1)$ 格，那么第 $i$ 格上的坦克会跑到第 $i-1$ 格。

不妨我们先统一轰炸偶数格，那么此时所有坦克都会到奇数格。

接着，我们再统一轰炸奇数格，那么此时原先偶数格的坦克会被摧毁，而奇数格的坦克会再次到偶数格。

再次轰炸偶数格，则原先奇数格的坦克会被摧毁。

次数：

$\frac{1}{2}n+\frac{1}{2}n+\frac{1}{2}n=\frac{3}{2}n=n+\frac{n}{2}$ 次

此题终。

```
#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	cout<<n+n/2<<endl;
	for(int i=2;i<=n;i+=2)cout<<i<<' ';
	for(int i=1;i<=n;i+=2)cout<<i<<' ';
	for(int i=2;i<=n;i+=2)cout<<i<<' ';
	return 0;
}
```


---

## 作者：Xjin (赞：0)

# 题意描述
翻译很明确，略。
# 分析
因为坦克炸一次之后会向周围的地方转移，所以无法一路轰过去。对于第 $i$ 个位置上的坦克可能会闪到 $i+1$ 或 $i-1$ 的位置，所以不难发现坦克移动之后的奇偶性发生了改变。于是我们可以先对奇数位置的格子进行轰炸，然后再对偶数的格子进行轰炸，最后再对奇数的格子进行轰炸。这时所花的次数是最少的，只需 $n\times 1.5$ 次，比 $n\times 2$ 的更优。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
signed main(){
	cin>>n;
	if(n%2==0)ans=n/2*3;
	else ans=n/2*3+1;  //奇数要注意特判
    
	cout<<ans<<endl;
	for(int i=2;i<=n;i+=2)cout<<i<<' ';
	for(int i=1;i<=n;i+=2)cout<<i<<' ';
	for(int i=2;i<=n;i+=2)cout<<i<<' ';
	return 0;
} 
```

---

## 作者：猜一猜我是谁 (赞：0)

# 思路
可以证明进行三次循环后坦克一定全部都被炸毁。

比如对于样例 3，先在第 2 格投弹，这时第 2 格的坦克会移到第 1 格或第 3 格。再在第 1 格和第 3 格投弹，这时第 1 格和第 3 格的坦克会移到第 2 格，第 2 格移来的坦克会被炸毁。最后在第 2 格投弹，这时从第 1 格和第 3 格来的坦克会被炸毁。所以总方案数为 $n+n/2$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    cout<<n+n/2<<endl;
    for(int i=2;i<=n;i+=2) cout<<i<<" ";//第一次轰炸
    for(int i=1;i<=n;i+=2) cout<<i<<" ";//第二次轰炸
    for(int i=2;i<=n;i+=2) cout<<i<<" ";//第三次轰炸
}
```

---

## 作者：精神小伙！ (赞：0)

## 思路

我们可以进行三次循环，这样坦克肯定就会全部被摧毁。

首先轰炸偶数格内的坦克，这时坦克会移动到奇数格。接下来轰炸奇数格内的坦克，这样原本在奇数格的坦克会移动到偶数格，而由偶数格移动过来的坦克就会被摧毁。最后再轰炸一遍偶数格内的坦克即可。

## 代码

```cpp
#include<iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;
    if(n==1)
    {
    	cout<<2<<endl;
    	cout<<1<<" "<<endl;
	}//特判 
	else
	{
		if(n%2==0)   cout<<n/2*3<<endl;
    	else         cout<<n/2*3+1<<endl;
		for(int i=2;i<=n;i+=2)
        	cout<<i<<" ";
    	for(int i=1;i<=n;i+=2)
        	cout<<i<<" ";
    	for(int i=2;i<=n;i+=2)
        	cout<<i<<" ";
	}
	return 0;
}

```

---


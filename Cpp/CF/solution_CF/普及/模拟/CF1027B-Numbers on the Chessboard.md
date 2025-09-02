# Numbers on the Chessboard

## 题目描述

你有一个 **n×n** 的棋盘，这个棋盘中的数字是由 **1** 至 **n×n** 的数组成的。这些数的填法满足：

前面的 **⌈n×n/2⌉** 个数字，即 **1** 至 **⌈n×n/2⌉** ，被按照从左到右、从上到下的次序依次写在那些横纵坐标相加为偶数的格子里。
剩下的 **n×n-⌈n×n/2⌉** 个数，即 **⌈n×n/2⌉+1** 至 **n×n** ，也被按照如上顺序依次写在那些横纵坐标相加为奇数的格子里。

这里的 **⌈y/x⌉** 代表y除以x**向上**取整

你被给到了q个询问，第i个询问是形如xi，yi的。你要对应输出的是在坐标为xi,yi的格子里的数字（xi为行，yi为列），行和列的大小都是从 **1** 至 **n** 。

## 样例 #1

### 输入

```
4 5
1 1
4 4
4 3
3 2
2 4
```

### 输出

```
1
8
16
13
4
```

## 样例 #2

### 输入

```
5 4
2 1
4 2
3 3
3 4
```

### 输出

```
16
9
7
20
```

# 题解

## 作者：zsc2003 (赞：4)

- codeforcs div2 2018.8.18
- B题
- 题目大意：
- 读入一个正整数n，共有q次查询，每次查询输入一对x,y；希望查询表格中第(x,y)的数字大小是多少。请你输出每次查询的结果
- 一看n的数据范围，显然不可以用模拟，那么只能使用找规律了。
![](https://cdn.luogu.com.cn/upload/pic/29515.png )


- 可以根据以上两张表格找规律
- 首先，将表格分为两种，n为奇数和偶数的两种
- 然后可以分类讨论，令查询为(x,y)，答案为ans

- 因为有横纵坐标是奇数偶数之分，所以预先让和为奇数的点的ans加上mid(若n为奇数，mid=n*n/2,否则mid=n*n/2+1)

- 先说n是偶数的情况：
- 可以发现，x行前共有(x-1)行，每行有n/2个数
- 所以让ans+=(x-1)*(n/2)
- 然后考虑第x行
- 第x行y列所排的数为y/2（上取整）
- 所以让ans+=y/2(上取整)即可

- 若n为奇数同理，只不过分为每行有n/2个数和n/2+1个数两种
- 详细细节可以查看我的代码


- 注意事项
- 记住一定要开long long...
- 本人第一次提交的时候莫名WA掉（我太菜了）
- 后来仔细检查才发现没开long long
- 记得codeferces用scanf输出long long 必须用I64d


- 下面附上我的代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,q,x,y;
inline void read(ll &x)
{
	x=0;
	char ch=getchar();
	bool flag=0;
	while('0'>ch||ch>'9')
	{
		if(ch=='-')
			flag=1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	if(flag)
		x=-x;
}
int main()
{
	read(n),read(q);
	ll mid=(ll)((ll)n*(ll)n/2);
	if(n%2!=0)
	{
		mid++;
		while(q--)
		{
			ll ans=0;
			read(x),read(y);
			if((x+y)%2==0)//<=mid
			{
				if(x%2==0)
					ans=(n/2+1)*(x/2)+(n/2)*(x/2-1);
				else
					ans=(n/2+1)*(x/2)+(n/2)*(x/2);
				if(y%2==0)
					ans+=y/2;
				else
					ans+=y/2+1;
			}
			else//>mid
			{
				if(x%2==0)
					ans=(n/2+1)*(x/2)+(n/2)*(x/2-1);
				else
					ans=(n/2+1)*(x/2)+(n/2)*(x/2);				
				ans+=mid;
				if(y%2==0)
					ans+=y/2;
				else
					ans+=y/2;
			}
			printf("%I64d\n",ans);
		}
	}
	else
	{
		while(q--)
		{
			ll ans=0;
			read(x),read(y);
			if((x+y)%2==0)//<=mid
			{
				ans=(n/2)*(x-1);
				if(x%2==0)
					ans+=y/2;
				else
					ans+=y/2+1;
			}
			else//>mid
			{
				ans=mid;
				ans+=(n/2)*(x-1);
				if(x%2==0)
					ans+=y/2+1;
				else
					ans+=y/2;
			}
			printf("%I64d\n",ans);//codeferces用scanf输出long long 必须用I64d
		}
	}
	return 0;
}
```

---

## 作者：Vct14 (赞：2)

题目挺简单，咋题解这么复杂/jk

考虑将棋盘看为一行。第 $x$ 行第 $y$ 列的数就为这一行中的第 $n(x-1)+y$ 个数。将这 $n\times n$ 个数两两一组，一个数为 $k$，另一个数为 $k+\left\lceil\dfrac{n\times n}{2}\right\rceil$（如果 $n$ 为奇数，那么最后一组只有一个数且为 $k$，但这不会对下面的结论产生影响）。放到原表中看，$x+y$ 为偶数时当前数为 $k$，$x+y$ 为奇数时为 $k+\left\lceil\dfrac{n\times n}{2}\right\rceil$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int n,q;cin>>n>>q;
	int f=n*n/2;
	if(n*n%2) f++;
	while(q--){
		int x,y;cin>>x>>y;
		int k=((x-1)*n+y-1)/2+1;
		if((x+y)%2) k+=f;
		cout<<k<<"\n";
	}
	return 0;
}
```

---

## 作者：Big_Dinosaur (赞：0)

## 思路
填入的数可看作到它时已填入多少数，先按 $x+y$ 的奇偶性来分类讨论，再按 $x$ 的奇偶性分类最后得出答案。
### $x+y$ 是偶数
首先，第 $x$ 行前面每 $2$ 行已填入的数就有 $n$ 个；因此，答案可以先设为 $\lfloor\frac x 2\rfloor\times n$。

当 $x$ 是奇数时，第 $y$ 个前有 $\lfloor\frac y 2\rfloor$ 个数，再加上它有 $\lfloor\frac y 2\rfloor+1$ 个，把它加入答案。答案为 $\lfloor\frac x 2\rfloor\times n+\lfloor\frac y 2\rfloor+1$。

$x$ 是偶数时，其前一行已填入 $\lceil\frac n 2\rceil$ 个数，这一行当 $y$ 是偶数时也填，共 $\frac y 2$ 个。答案为 $\lfloor\frac x 2\rfloor\times n+\lfloor\frac n 2\rfloor+\frac y 2$。
### $x+y$ 是奇数
$x+y$ 是偶数时已填入 $\lceil\frac {n^2} 2\rceil$ 个数，另外第 $x$ 行前面每 $2$ 行已填入的数就有 $n$ 个。答案可以先设为 $\lfloor\frac x 2\rfloor\times n+\lceil\frac {n^2} 2\rceil$。

接下来与上文类似。

当 $x$ 是奇数时，当 $y$ 是偶数时也填，共 $\frac y 2$ 个。答案为 $\lfloor\frac x 2\rfloor\times n+\lceil\frac {n^2} 2\rceil+\frac y 2$。

$x$ 是偶数时，其前一行已填入 $\lfloor\frac n 2\rfloor$ 个数，该行第 $y$ 个前有 $\lfloor\frac y 2\rfloor$ 个数，再加上它有 $\lfloor\frac y 2\rfloor+1$ 个，把它加入答案。答案为 $\lfloor\frac x 2\rfloor\times n+\lceil\frac {n^2} 2\rceil+\lfloor\frac n 2\rfloor+\lfloor\frac y 2\rfloor+1$。

代码不给了，根据前面所述模拟即可。

---


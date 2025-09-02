# 100個の円

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-formula-2014-final/tasks/code_formula_2014_final_f

$ 100 $ 個の円があります。 このうち $ k $ 番目の円の半径は $ k $ であることがわかっています。

これを、$ 1500 $ × $ 1500 $ の正方形の中に敷き詰めることにしました。

敷き詰め方の一例を出力してください。

なお、円の中心の座標は、$ x $ 座標、 $ y $ 座標ともに、整数でないといけないことに注意してください。

## 说明/提示

### Sample Explanation 1

以上の例では、半径 $ 1 $ の円を座標 $ (1,1) $ に、半径 $ 2 $ の円を座標 $ (5,10) $ に、半径 $ 3 $ の円を座標 $ (500,30) $ に置いています。 上記のような形で、 $ 100 $ 行出力するのが、今回の課題です。

## 样例 #1

### 输入

```
None```

### 输出

```
1 1
5 10
500 30
:```

# 题解

## 作者：Strelitzia_ (赞：2)

## 题目大意

------------
在一个 $1500*1500$ 的正方形中填入 $100$ 个半径分别为 $1,2,3,...,100$ 的圆，边缘可以重合但不能越界；现在要求我们给出这 $100$ 个圆的圆心坐标。

## 思路
我们把这个正方形想成一个容器，把圆想象成石子。向容器中放石子，最好的方式当然是从大向小放。于是我们从大到小开始构造。

我们考虑这样一种方式：从左向右平铺式地放圆；如果横坐标越界就去上一行重新开始。这么推的话，我们第一行可以有：$200+198+196+194+192+190+188$，即 $7$ 个圆；第二行 $186+184+182+180+178+176+174+172$，共 $8$ 个圆。

以此类推：

$$3:170+...+156\ (sum:9)$$
$$4:154+...+136\ (sum:10)$$
$$5:134+...+114\ (sum:11)$$
$$...$$

最后我们得到验证：这样构造符合要求。

最后在代码实现部分，我们将 $x$ 作为这个圆最右点的横坐标，$y$ 同理。我们把 $x$ 一步步向后推，超出边界就去上一行。代码如下：

```cpp
int x=0,y=200;
struct ToT{
	int x,y;
}a[N];

int main(){
	for(int i=100;i>0;i--){
		if(x+2*i>1500){
			x=2*i;
			y+=2*i;
		}
		else x+=2*i;
		a[i].x=x-i;
		a[i].y=y-i;
	}
	for(int i=1;i<=100;i++)
	 printf("%d %d\n",a[i].x,a[i].y);
	return 0;
}
```


---

## 作者：CodingOIer (赞：1)

## Code Formula 2014 本選 F 100個の円

### 思路分析

在一个 $1500 \times 1500$ 的矩阵中，要你填入 $r = 1, 2, 3 \dots 100$ 的 $100$ 个圆。求一种合法的填入方式使填入的圆**可以相切但不能重叠**。

我们发现，$1500 \times 1500$ 的矩阵范围远远大于最大的直径 $l = 200$， 所以我们可以将其看为一个 $l \times l$ 的正方形。

只考虑只填一行的情况：对于每一个正方形，将其紧挨在上一个正方形旁边，代码如下：

```cpp
#include <cstdio>
int main()
{
    int x, y;
    x = 0;
    y = 0;
    for (int i = 1; i <= 100; i++)
    {
        printf("%d %d\n", x + i, y + i);
        x += 2 * i;
    }
    return 0;
}
```

但是，按照此方式得到的结果最大的长度为 $2 + 4 + 6 + \dots + 200 = 10100$ 超出了题目的限制。此时，当坐标超出 $1500 \times 1500$ 的矩阵范围时便开启下一行，代码如下：

```cpp
if (x + i > 1500)
{
    x = 0;
    y += 2 * (i - 1);
}
```

### 代码实现

```cpp
#include <cstdio>
int main()
{
    int x, y;
    x = 0;
    y = 0;
    for (int i = 1; i <= 100; i++)
    {
        if (x + i > 1500)
        {
            x = 0;
            y += 2 * (i - 1);
        }
        printf("%d %d\n", x + i, y + i);
        x += 2 * i;
    }
    return 0;
}
```

---

## 作者：L_Obsession_TO (赞：1)

### 思路
- 按半径由小到大安放，从左到右，一行放不下就去下一行，把每个圆看做一个正方形，边长就是 $2\times r $。  
- 圆可以挨着（虽然不挨着好像也行），注意对每个圆的坐标的掌握。
- 按圆半径从小到大枚举，每次判断当前是否超过边界。超过就换一行放，这时下一行的纵坐标要加当前枚举圆的直径。但是纵边界不用判断，因为肯定能放下。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
int x,y;         //每个“正方形 ”的右上角 的坐标 
//圆心坐标即 x-i , y+i  
int main(){
	for(int i=1;i<=100;i++){
		if(x+2*i>1500){		//判断边界（纵轴不用） 
			y+=i*2;
			x=i*2;
		}
		else x+=2*i;
		cout<<x-i<<" "<<y+i<<endl;
	}
	return 0;//结束 
}
//
```


---

## 作者：whx2009 (赞：0)

## 本题思路：
这道题目乍一看上去要放圆形到一个正方形里面很难，但我们不妨转换一下思路，把每一个圆形都看成一个正方形，然后把这些小正方形放进一个大正方之中。

这样我们就可以只判断是否到达边界了，到了就换行即可。

那么换行怎么换呢？我们可以直接画出一条下一行的通用线，在这条线上加上当前的编号即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int x=0,y=0;
	for(int i=1;i<=100;x+=i*2,i++)
	{
		if(x+i>1500){
			x=0;y+=2*(i-1);
		}
		cout<<x+i<<" "<<y+i<<endl;
	}
	return 0;
}
```

---

## 作者：Gaoyx (赞：0)

感觉很水的一道题。
## 思路
从第一个圆开始枚举位置，再将每个圆形抽象成一个半径加一的正方形，在判断边界如果触碰或超过边界就换一行枚举，建议结合代码理解。
## 代码
```
#include <bits/stdc++.h>
using namespace std;
int x, y;
int main(){

	for(int i=1;i<=100;i++){
		if(x+2*i+1 > 1500){
			x = 2*i+1;
			y += i*2+1;
		}
		else x += 2*i+1;
		cout << x-i << " " << y+i+1 << endl;
	}
	return 0;
}
```


---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$
这题没什么难度，自己动动手指算一算就好了，最大圆的直径才 $200$，而正方形却有 $1500$，所以猜测是一种有规律的排放方式，最直观的就是一行一行的挨个放，直到有一行放不下了再开新的一行放，简单计算了一下得到了如下表格。

| 行数编号 | 放的圆的区间 | 占用的排数 |
| -----------: | -----------: | -----------: |
| $1$ | $[1,38]$ | $76$ |
| $2$ | $[39,54]$ | $108$ |
| $3$ | $[55,66]$ | $132$ |
| $4$ | $[67,76]$ | $152$ |
| $5$ | $[77,85]$ | $170$ |
| $6$ | $[86,93]$ | $186$ |
| $7$ | $[94,100]$ | $200$ |

总占用行数很明显是小于 $1500$ 的，所以这种方案可行，构造就是每次更新一下半径，然后判断是否需要新开一行。

```cpp
/*
	Luogu name: Symbolize
	Luogu uid: 672793
*/
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,x,y,z) for(register int i=x[y];~i;i=z[i])
#define rep4(i,x) for(auto i:x)
#define debug() puts("----------")
const int N=1e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
using namespace std;

int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int r=1,x=0,y=0;
	while(r<=100)
	{
		x=0;
		while(x+r*2<=1500)
		{
			cout<<x+r<<' '<<y+r<<endl;
			x+=r*2;
			++r;
			if(r>100) return 0;
		}
		y+=(r-1)*2;
	}
	return 0;
}

```

---

## 作者：zimujum (赞：0)

## 思路：

因为要求出 $100$ 个圆的圆心的坐标，每个圆的半径是 $1,2,3,\cdots,100$，所以我们可以从小到大依次输出，我们设每个圆变为正方形，它们的边长为 $2n+1$ 比如第一个圆就变为边长为 $3$ 的正方形，而圆心坐标就是 $1+1$ 和 $1+1$，第二个就是 $3+1$ 和 $2+1$。最后我们可以得知第 $i$ 个圆形的圆心坐标为 $x-i$ 和 $y+i+1$。

## 这是 AC 代码以及详细注释：
```
#include <bits/stdc++.h>//美丽的万能头~
//#define itn int 别看我 
#define ll long long
#define ull unsigned long long
#define AC return 0
using namespace std;
const ll M=114514;
int x,y;//每个圆的圆心坐标 ，不过我更认为把圆改为边长为2*i的正方形更好理解 
int main(){
//	freopen("eat.in","r",stdin);
//	freopen("eat.out","w",stdout);
	for(int i=1;i<=100;i++){//100个圆 
		if(x+2*i+1>1500){//如果圆的半径超过了正方形的边 
			x=2*i+1;//所以从第二行重新开始计数 
			y+=i*2+1;//y轴进行增加 
		}
		else x+=2*i+1;//这里是没有越过边界的话，就正常增加 
		cout << x-i << " " << y+i+1 << endl;//x-i指圆心的x轴，y+i同理 
	}
//	fclose(stdin);
//	fclose(stdout);
	AC;//功德圆满 
}
//有错误请指正


```


---

## 作者：nynkqh_yzp (赞：0)

从最大的圆开始构造，首先让每个圆的最右端在一条线上，每个圆的上端和上一个圆的下端或上边界重合，如果不能满足，就让右端的线右移。证了每个圆的横坐标与纵坐标不冲突，因此算法的正确性是显而易见的。

```cpp
#include <bits/stdc++.h>
using namespace std;
int x,y;
stack<pair<int,int> >q; 
int main(){
	y=200;
	for(int i=100;i>0;i--){
		if(x+i*2>1500)
			x=i*2,y+=i*2;
		else
			x+=i*2;
		q.push(make_pair(x-i,y-i));
	}
	while(!q.empty()){
		printf("%d %d\n",q.top().first,q.top().second);
		q.pop();
	}
	return 0;
}

```


---

## 作者：xps0606 (赞：0)

这里考虑从最大的圆开始构造，不断增加横坐标与纵坐标。在构造的过程中，把坐标加入答案即可。因为构造时保证每个圆的横坐标与纵坐标不冲突，因此算法的正确性是显而易见的。时间复杂度: $O(100)$ 。  
这里我用动态数组存储答案，不过普通的数组或结构体也行。  
AC代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
  int x=1500,y=0;
  vector<pair<int,int> >ans(100);//Vector<类型>标识符(最大容量)
  for(int i=100;i>0;i--){//从大到小构造 
    if(x+2*i>1500){x=2*i;y+=2*i;}//如果越界，则横坐标回到最低限度 
    else{x+=2*i;}ans[i-1]=pair<int,int>(x-i,y-i);//不然继续往下构造，并将上一个圆加入答案。因为是圆心，所以是x-i与y-i。
  }
  for(int i=0;i<100;i++) cout<<ans[i].first<<" "<<ans[i].second<<endl;//输出一定要换行！ 
  return 0;
}
```




---


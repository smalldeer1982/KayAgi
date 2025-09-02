# 正方形のチップ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/ddcc2016-final/tasks/ddcc_2016_final_a

半径 $ R $ cmの*ウェーハ*に*ダイシング*という操作を行い、正方形のチップをいくつか作成することにしました。 作成される正方形のチップの個数を求めてください。

ウェーハとは、ある部品を作るのに使われる薄い円盤状の物体です。 ダイシングという操作は、ウェーハの中心から $ C $ cm間隔で水平方向と垂直方向に切れ目を入れてウェーハを分割する操作です。

例として、$ R=15,\ \,\ C=4 $ の例を示します。 破線で示されるようなマス目状に分割がなされ、緑色の領域で示されるような $ 32 $ 個の正方形のチップを作成することができます。

 ![3b83484e97d59df50e3ee39c4a3cbca7.png](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_ddcc_2016_final_a/4884165f81392986b1bb775c3cf1b058de7f8e4a.png)

## 说明/提示

### 制約

- $ 1\ ≦\ R,\ \,\ C\ ≦\ 100 $
- $ R,\ \,\ C $ はいずれも整数

### Sample Explanation 1

\- 問題文中で示した通りです。

### Sample Explanation 2

\- ウェーハの中心を $ (0,0) $ としたとき $ (2,3),(3,3),(2,4),(3,4) $ の $ 4 $ 点で表される正方形のチップは $ (3,4) $ がウェーハの周上にありますが、このようなチップも作成することが可能です。

## 样例 #1

### 输入

```
15 4```

### 输出

```
32```

## 样例 #2

### 输入

```
5 1```

### 输出

```
60```

# 题解

## 作者：ShineEternal (赞：10)

此题目我已经写好翻译了，就在题面上。
```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int main()
{
    int R, C; 
    cin >> R >> C;//读入
    int cnt = 0;
    for(int yy=1;yy<=R+1;yy++)
    {
        for(int xx=1;xx<=R+1;xx++)//此处xx和yy的循环顺序无所谓
        {
            int x=xx*C;
            int y=yy*C;//要转换为题目要求的C个单位的
            if(x*x+y*y<=R*R)//在正方形内
            cnt++;//计数器＋1
        }
    }
    printf("%d",cnt*4);//因为我们计算了1/4圆，所以*4
    return 0;
}
```

---

## 作者：Jairon314 (赞：4)

$$ \textbf{\huge AT2243} $$
$$ \textbf{\LARGE Square} $$
$$ \text{\large ————Jair} $$

$$ \text{\small Warning: This problem's solving belongs to} $$
$$ \textbf {\huge $ \mathbb{TOP\;SECRET} $} $$
$$ \text {\small Unauthorized personnel are prohibited from visiting} $$
$$ \text {\small Perpetrators will be monitored, located, and dealt with} $$

$$ PAY\;ATTENTION: $$
$$ \text {\small cspJ踩线1$=$的蒟蒻没有想出十分优秀的AC解法，只会暴力} $$

$$ \large· $$
$$ \large· $$
$$ \large· $$

$$ \large \frak Forward $$
--------
上周随机跳到此题，感觉非常水，没一会儿就轻松AC了。今天看到[Special_gold](https://www.luogu.com.cn/user/361840)(同机房同学)发了题解，于是我也来水一水吧~

核心公式：

$$ (x-a)^2+(y-b)^2=r^2 $$

把这个公式在平面直角坐标系上画出来以后，发现它就是一个以$r$为半径，以$(a,b)$为圆心的一个圆。

![正方形](https://s3.ax1x.com/2021/01/02/rzwdnU.png)

那么，在看到本题的时候，需要用到的也就很简单了：
$$ a=0 $$
$$ b=0 $$
$$ r=read() $$
中途还需要处理一下单位一的长度，
然后，就可以得出$ans:$

$$ ans+=(i*c*c*i+j*c*c*j<=r*r)*4;  $$

那么，这里为什么要$×4$呢？

原因很简单，我们每次都是求的第一象限中的正方形的数量，而圆心在原点，一共有四个象限，每个象限中正方形的数量相等，所以$×4$就好啦~

$$ \large \frak CodeTime $$
--------

```cpp
//ACcode
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define maxn 1000010

int r,c,ans;

int main(){
	scanf("%d%d",&r,&c);
	for(int i=1;i<=r/c;i++){
		for(int j=1;j<=r/c;j++){
			ans+=(i*c*c*i+j*c*c*j<=r*r)*4;
		}
	}
	printf("%d",ans);
	return 0;
}
```


$$ \large \frak {in\;the\;end}$$
--------
祝大家元旦快乐，万事如意，在2021年绽放光彩！~~我相信我一定会的~~


---

## 作者：Mono_pigsicklie (赞：2)

#### 刷水题刷出学校自招题？？！这人品没谁了（捂脸痛哭）

~~莫名开始佩服学校老师~~

###### 本校自招题目：

![](https://t1.picb.cc/uploads/2019/03/28/VSyxIc.png)


###### 当时看很多人都在推公式，自己推了一下，发现有小数，然后还在心里嘀咕了一句说：“有小数还推，为了20%的数据值？”



------------

###### 学校的std：

```cpp
#include<cstdio>
#include<iostream>
#include<cmath> 
using namespace std;
int main()
{
	freopen("cover.in","r",stdin);
    freopen("cover.out","w",stdout); 
    double r;
    long long s=0;
    int temp,i,l;
    cin>>r;
    l=floor(r);
    for (i=1;i<=l;i++)
    {
    	temp=sqrt(r*r-i*i);
    	s+=temp;
	}
    cout<<s*4;
   fclose(stdin);fclose(stdout);
    return 0;    
}
```

------------

其实两个题细看会发现很相像，~~（大致看都能一眼看出）~~我们可以把它分成四份，这样只需要求一部分，最后只需要*4就可以啦。但是答案呐，它就是推公式（托腮无奈）

附上代码:

```cpp
#include"bits/stdc++.h"
using namespace std;
int main() {
	long int r,c;
	long long s=0;
	int temp,i,l;
	cin>>r>>c;
	for (i=1; i<=r+1; i++) {
		for(int l=1; l<=r+1; l++) {
			int a=i*c;int b=l*c;
			if(a*a+b*b<=r*r)s++;
		}
	}
	cout<<s*4;
	return 0;
}
```

还是自己做来的稳，切勿抄袭啦


---

## 作者：Lithium_Chestnut (赞：1)

~~AT 的黄题还是一如既往的水。~~

此题不包含任何算法，直接依题意二层循环模拟即可。

题目已经直接帮你把圆分成了四个大小相同、面积相等的部分，显然，这四个 $\frac{1}{4}$ 圆的所有正方形个数相等。所以我们的目标就是找出每个 $\frac{1}{4}$ 圆包含正方形的个数，然后乘 $4$ 即可。

解释一下循环内的：显然我们需要把每次模拟的 $i,j$ 按题意所说转化为 $c$ 个单位，然后每次判断是否在正方形内，是的话，就把答案 $+1$。

最后输出别忘记把答案乘 $4$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int r,c,x,y,ans;
int main()
{
    cin>>r>>c;
    for(int i=1;i<=r+1;i++)
    {
        for(int j=1;j<=r+1;j++)
        {
            x=i*c,y=j*c;
            if(x*x+y*y<=r*r) ans++;
        }
    }
    ans*=4;
    cout<<ans;
    return 0;
}
```


---

## 作者：A_Đark_Horcrux (赞：1)

首先看数据范围， $1\leq R,C \leq 100$ ，那完全可以枚举。

其次，这个图形可以分成四个相同的部分，那我们只需计算其中一部分的答案再乘以4即可。为了简便，我们选取右上角这一块qwq

我们枚举每一个点，如果它到圆心的距离小于等于半径，说明以这个点为右上角顶点的单位正方形在圆内， $ans++$ ，最后乘以4即可awa

```cpp
#include<cstdio>
using namespace std;
inline int read()
{
	int s=0,b=1; char c=getchar();
	while(c<'0'||c>'9') {if (c=='-') b=-1; c=getchar();}
	while(c>='0'&&c<='9') s=s*10+c-'0',c=getchar();
	return s*b;
}//快读
int main()
{
	int r=read(),c=read(),s=0;//r为半径，c为单位长度，s为四分之一的答案
	for(int i=c;i<=r;i+=c)
		for(int j=c;j<=r;j+=c)//注意枚举的起点是c，每次更新时加上的也是c。
			s+=(i*i+j*j<=r*r);//运用距离公式计算，若点到圆心距离小于等于半径则在圆内，s++
	printf("%d\n",s<<2); return 0;//乘4输出
}

```


---

## 作者：Fire_Raku (赞：0)

## 题目分析

看到圆，我第一想的到的是小数。但是！我们可以想想判断正方形是否在圆里的条件——是不是只需要判断正方形的四个点是否在圆里就行了？我们在简化一下，就只需要判断正方形中离圆最远的那个点是否在圆里就行了。

我们知道，求两点的距离公式是 $\sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}$，但是这里我们有一个点是原点，所以就变成了 $\sqrt{x^2 + y^2}$ ， 但这样子做还有一个问题，就是精度问题，所以，我们把根号消掉，根据勾股定理，我们就可以写出这样的判断式：

$x^2 + y^2 \le r \times r$

其中 $r$ 为半径。如果满足这个条件，正方形的数量就加一。这样，我们看图，发现圆可以分为四部分，这四部分的正方形数量都是一样的，所以我们只需要算其中一部分，最后再乘四就行了。

```cpp
#include<bits/stdc++.h>
using namespace std ;
int ans ;
int main(){
	int r , c ; 
	cin >> r >> c ; 
	for(int i = 1 ; i <= r + 1 ; i++){ //因为乘法的缘故，我们不能使原点为（0,0）
		for(int j = 1 ; j <= r + 1 ; j++){ //枚举的是右上角的正方形
			int x = i * c , y = j * c ; 
			if(x * x + y * y <= r * r) ans++ ; //判断是否在圆内
		}
	}
	cout << ans * 4 << endl ; //记得乘4加回车qwq
	return 0 ;
}
```

---

## 作者：Miracle_ZX (赞：0)

### Part 0

希望能过审~

### Part 1 分析

首先，拿到了一道题，我们要先看数据范围：$1 \leq R$，$C \leq 100$，才 100 的范围，完全可以暴力。但是暴力一定要找到方法，否则会使你的代码很繁杂。

我认为，与其从圆心处考虑，还不如考虑外接圆的（包裹了整个圆的）正方形区域内有多少个整点符合在圆内的条件，由于四个象限的情况都相同，我们可以只模拟一个象限的情况，之后 $\times 4$ 便可，其中又以右上角的为最简便，所以我们直接模拟即可。

当然，为了使得思路简洁，我们可以让 $i$ 和 $j$ 从单位长度，也就是 $(c, c)$ 处开始模拟，一直模拟到外包正方形的边缘 $(r, r)$ 处。另外，判断是否在圆内，可以用坐标系上的距离公式：$\sqrt{(x_1 - x_2)^2+(y_1 - y_2)^2} $，由于这里的 $(x_2, y_2)$ 为原点，带入简化并拆根号即可简化判断式。

### Part 2 Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int r, c, ans = 0;
    cin >> r >> c;
    for(int i = c; i <= r; i+= c)
    {
        for(int j = c; j <= r; j += c)
        {
            if(i * i + j * j <= r * r) ans += 1;
        }
    }
    cout << ans * 4;
    return 0;
}

```

### Part 3 AC

[58ms, 3.54MB](https://www.luogu.com.cn/record/57735113)


---

## 作者：听取MLE声一片 (赞：0)

本题目要求圆中最多的正方形数量。

首先，我们发现本题目的切割基于一个“格子的单位长度 $C$ ”，于是我们可以`n=r/c`，求得实际上圆的“半径”；`unit=c*c`，求得实际的单位长度

在直角坐标系上，这个圆的圆心位于原点 $O(0,0)$ ，那么对于任意一个整点 $P(x,y)$ ，其与圆心的距离的平方 $ OP^2 =  x^2 + y^2  $ ，如果这个距离小于圆的半径 $dist$ ，那么这个点左下方的正方形必然符合题意。

那么这道题就迎刃而解了，根据数据范围，我们可以直接在第一象限枚举整点 $P$ ，此时必有 $x \re 0 , y \re 0$ ，最后把结果乘 $4$ 得到答案 `ans` 。复杂度 $ \Theta ( n^2 ) $ ，由于 $R \le 100$ ,可以通过。

---

### 代码能力在普及阶段非常重要呢，知道思路了就别看代码了！

比较表达式：

$ OP < R $

$ i^2 + j^2 < R ( 1 \le i,j \le R/C) $

这个地方尤其重要，容易出错，具体自行理解，不再多说

$ (i\times c)^2 + (j\times c)^2 < (R)$

```cpp
#include <cstdio>
using namespace std;
int r,c,n,ans,dist,unit;
int main(){
	scanf("%d%d",&r,&c);
	n=r/c;dist=r*r;unit=c*c;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			ans+=(i*i*unit+j*j*unit<=dist)*4;
			//i(j)*i(j)*unit算出实际长度才能与dist比较
			//注意：不能两边同时约去unit
			//原因：大多数语言中整数类型相除会得到整除结果，会把一些结果省去，导致WA
		}
	printf("%d",ans);
	return 0;
}
```

#### P.S. 附：本题目原来的大意

> 在半径 $R cm$ 的晶片上进行切割操作来制作几个正方形的芯片。请计算制作的正方形芯片的个数。

> 晶圆是用来制作某个零件的薄圆盘状物体。所谓切割操作，是从晶片中心以 $C cm$ 间隔在水平方向和垂直方向上切口，分割晶片的操作。

---


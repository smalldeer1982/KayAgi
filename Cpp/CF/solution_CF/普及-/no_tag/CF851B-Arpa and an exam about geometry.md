# Arpa and an exam about geometry

## 题目描述

题意

Arpa正在参加一场几何学考试。这是这场考试的最后一题。
给你三个点。让你找一个点和一个角度使得按这个点旋转这个角度后，a的新位置与b的原位置重合，b的新位置与c的原位置重合。
Arpa怀疑这个问题是否有解（如果存在一个点和一个角度满足条件）。请帮助Arpa确定这个问题是否有解决方案。

## 样例 #1

### 输入

```
0 1 1 1 1 0
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
1 1 0 0 1000 1000
```

### 输出

```
No
```

# 题解

## 作者：oddy (赞：1)

做题方法前面的题解讲得很详细了，这里主要讲推导和证明。

## Description

给定三个点 $A, B, C$，求能否找到一个点和一个角度，使得点 $A$ 绕该点旋转该角度后能与点 $B$ 重合，且点 $B$ 绕该点旋转该角度后能与点 $C$ 重合。

## Solution

学过初中数学的我们都知道全等三角形的性质：

> 全等三角形的对应边相等，全等三角形的对应角相等。

> ——《义务教育教科书 数学 八年级上册》

所以有以下结论：

三点符合题意，当且仅当 $AB = BC$。

找出一个符合题意的新点 $D$ 的方法如下：

作线段 $AB$、$CB$ 的垂直平分线，交点即为点 $D$。

附赠一张图辅助理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/qm636eer.png)

证明：由线段垂直平分线的性质，$AD = CD$.

又 $BD = BD$，$AB = CB$，

$\therefore \triangle ABD \cong \triangle CBD\left(\operatorname{SSS}\right)$.

$\therefore \angle ADB = \angle CDB$.

同理可证，$AB \neq BC$ 时不符合题意。

但是还没完，**有例外！**

例外：三点共线时，那个点在无穷远处，写不出坐标，因此要特判。

## Code

```cpp
#include <cstdio>

long long x1, y1, x2, y2, x3, y3;

inline bool judge() {
    return (y3 - y1) * (x2 - x1) != (y2 - y1) * (x3 - x1) &&                                               // 判断距离是否相等
           (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) == (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3); // 判断是否不共线
}

int main() {
    scanf("%lld%lld%lld%lld%lld%lld", &x1, &y1, &x2, &y2, &x3, &y3);
    puts(judge() ? "Yes" : "No"); // 简洁而优雅
    return 0;
}
```

---

## 作者：lihanyang (赞：1)

# 其实本体就是求：
# 给你三个点的坐标，如果ab=bc，三点不共线，就输出Yes，否则输出No
# 废话不说，直接上代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	long long a1,a2,b1,b2,c1,c2;
	cin>>a1>>a2>>b1>>b2>>c1>>c2;
	long long x=(a1-b1)*(a1-b1)+(a2-b2)*(a2-b2),y=(b1-c1)*(b1-c1)+(b2-c2)*(b2-c2);
	if(x!=y) puts("No");//判断ab是否等于bc
	else
	{
		if((a2-b2)*(c1-b1)==(a1-b1)*(c2-b2))//公式，判断是否三点共线
		{
			puts("No");
		}
		else puts("Yes");
	} 
}
```

---

## 作者：Zq_water (赞：0)

数学题

判断两个东西，一个是判断三点距离是否两两相等，另一个是三点是否共线。


先看第一个问题，我们只需要判断 $\sqrt{(a_x-b_x)^2+(a_y-b_y)^2}$ 等于 $\sqrt{(b_x-c_x)^2+(b_y-c_y)^2}$ 就行了。

第二个问题也只需要判断 $(a_x-b_x)\times(c_y-b_y)$ 不等于 $(c_x-b_x)\times(a_y-b_y)$ 就行了。

代码按照上面写就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ax,ay,bx,by,cx,cy;
bool check1(){
	return (ax-bx)*(ax-bx)+(ay-by)*(ay-by)==(cx-bx)*(cx-bx)+(cy-by)*(cy-by);
}
bool check2(){
	return (ax-bx)*(cy-by)!=(cx-bx)*(ay-by);
}
int main(){
	cin>>ax>>ay>>bx>>by>>cx>>cy;
	if(check1()&&check2()) cout<<"Yes";
	else cout<<"No";
	return 0;
} 
```

---

## 作者：haozinojc (赞：0)

比较**数学**的一道水题。

### 思路：

无解决方案的情况有两种：

1. 因为经过旋转后，$a$ 要在 $b$ 的原位置，$b$ 要在 $c$ 的原位置，由于 $ab$ 的长度是不变的，所以 $ab$ 需要等于 $bc$。那么当 $ab\ne bc$ 时，无解决方案。两点之间的距离都会求吧，小学勾股，不过在程序中可以选择把求根这一步去掉，简化后：

$(a_x-b_x)^2+(a_y-b_y)^2$。

2. 当 $a$、$b$、$c$ 三点在一条直线上时，$a$、$b$ 是无法通过旋转到达 $b$、$c$ 的原位置的，即：

$(a_x-b_x)\times(c_y-b_y)=(a_y-b_y)\times(c_x-b_x)$。

经过这么一总结，相信大家都明白了此题的实质：只需两个判断，只要满足任意一个，就没有解决方案。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ax,ay,bx,by,cx,cy;
signed main(){
	cin>>ax>>ay>>bx>>by>>cx>>cy;
	if((ax-bx)*(ax-bx)+(ay-by)*(ay-by)!=(cy-by)*(cy-by)+(cx-bx)*(cx-bx))puts("No");
	else if((ax-bx)*(cy-by)==(cx-bx)*(ay-by))puts("No");
	else puts("Yes");
	return 0;
} 
```


---

## 作者：zct_sky (赞：0)

### Solution:
-----
~~只需要两个 `if` 就能过的大水题。~~

先判断 $ab$ 是否等于 $bc$，距离公式：$\sqrt{{(a_x-b_x)}^2+{(a_y-b_y)}^2}$。

再判断 $a,b,c$ 三点是否共线，判断公式：

$(a_x-b_x)\times (c_y-b_y) \neq (c_x-b_x)\times(a_y-b_y)$，

当公式成立时 $a,b,c$ 三点不共线。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
using namespace std;
ll ax,ay,bx,by,cx,cy; 
inline ll read(){//快读，虽然在这题用处不大 
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
int main(){
	ax=read(),ay=read(),bx=read(),by=read(),cx=read(),cy=read();
	if((ax-bx)*(ax-bx)+(ay-by)*(ay-by)!=(cx-bx)*(cx-bx)+(cy-by)*(cy-by)) printf("No");//判断ab是否等于bc 
	else if((ax-bx)*(cy-by)==(cx-bx)*(ay-by)) printf("No");//判断a,b,c是否共线 
	else printf("Yes");
	return 0;
} 
```

---

## 作者：SoyTony (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF851B)

[博客广告](https://www.luogu.com.cn/blog/Tony-ZhuJialiang/#)

# 题意
给出点 $A(A_x,A_y)$、$B(B_x,B_y)$、$C(C_x,C_y)$，判断是否存在一点 $O$ 使点 $A$、$B$ 绕点 $O$ 旋转一定度数后分别与 $B$、$C$ 重合。

# 分析
具备一定的初中数学知识就可以得出下面几个结论：

- 如果有解，那么有 $\triangle AOB\cong \triangle BOC$.
- 如果有解，那么 $A$、$B$、$C$ 三点一定不共线

下面给出证明：

![](https://cdn.luogu.com.cn/upload/image_hosting/0m40qfuj.png)

可以把旋转点 $A$，点 $B$ 看作旋转这两点分别与旋转中心的连线，那么因为被旋转的点重合且旋转中心不变，就有 $OA=OB$，$OB=OC$，这里我们可以发现点 $O$ 到 $\triangle ABC$ 三个顶点的距离相等,点 $O$ 就是该三角形的外心（外接圆圆心），那么同时旋转角相等，所以 $\angle AOB=\angle COB$，可以证得 $\triangle AOB\cong \triangle BOC$，而共线的三点自然无法共圆，所以结论二正确。

# 实现

由勾股定理可得，两点间距离公式为：
$$AB=\sqrt{(A_x-B_x)^2+(A_y-B_y)^2}$$

如果 $AB=BC$ 且 $B$ 不为 $AC$ 中点，那么三点不共线，所以中点坐标公式：
$$P(\dfrac{A_x+C_x}{2},\dfrac{A_y+C_y}{2})$$

# 代码
**要开long long**
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef double db;
ll ax,ay,bx,by,cx,cy;
inline ll read(){
    ll x=0,w=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
    while(c<='9'&&c>='0'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*w;
}
int main(){
    ax=read(),ay=read(),bx=read(),by=read(),cx=read(),cy=read();
    //printf("%lld %lld %lld %lld %lld %lld\n",ax,ay,bx,by,cx,cy);
    ll dis1=(ax-bx)*(ax-bx)+(ay-by)*(ay-by);
    ll dis2=(bx-cx)*(bx-cx)+(by-cy)*(by-cy);
    //printf("%lld %lld\n",dis1,dis2);
    if(dis1==dis2){
        if(((ax+cx)/2.0!=bx)||(ay+cy)/2.0!=by)
            printf("Yes\n");
        else printf("No\n");
    }
    else printf("No\n");
}
```


---

## 作者：int32 (赞：0)

## $\textsf{Description}$

给定 $A(a_x,a_y),B(b_x,b_y),C(c_x,c_y)$，判断 $A,B,C$ 是否**共线**且 $AB=BC$。

## $\textsf{Solution}$

首先给出共线公式：当 $(a_y-b_y)(c_x-b_x)\neq(a_x-b_x)(c_y-b_y)$ 时，$A,B,C$ 三点共线。

然后是距离公式：$dis_{A,B}=\sqrt{(a_x-b_x)^2+(a_y-b_y)^2}$。

判断即可。

## $\textsf{Code}$

```cpp
// Problem: B. Diameter of Graph
// Contest: Codeforces - Codeforces Round #745 (Div. 2)
// URL: https://codeforces.com/contest/1581/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
using namespace std;
int ax, ay, bx, by, cx, cy, ab, bc;
bool line, equals;
signed main(){
	cin>>ax>>ay>>bx>>by>>cx>>cy;//坐标
	ab=(ax-bx)*(ax-bx)+(ay-by)*(ay-by);//AB^2
	bc=(bx-cx)*(bx-cx)+(by-cy)*(by-cy);//BC^2
	equals=(ab==bc);//AB^2=BC^2 -> AB=BC
	line=((ay-by)*(cx-bx)!=(ax-bx)*(cy-by));//共线
	puts(line&&equals?"Yes":"No");//判断
	return 0;
}
```

---

## 作者：Fearliciz (赞：0)

#### 题目翻译

给你三个点的坐标，如果 $ab=bc$ 三点不共线，就输出 $\texttt{Yes}$，否则输出 $\texttt{No}$。

开始没仔细看数据范围就直接写的 $\texttt{int}$ 后来才改的 $\texttt{long long}$。

这道题题目已经很显然了，直接代入斜率公式计算即可。

要使 $ab=ac$ 即旋转前的三角形和旋转后的三角形要全等。

压行代码：

```c
#include<cstdio>
int main(){long long a,b,c,d,e,f; scanf("%lld%lld%lld%lld%lld%lld",&a,&b,&c,&d,&e,&f); ((a-c)*(a-c)+(b-d)*(b-d)!=(c-e)*(c-e)+(d-f)*(d-f)) ? printf("No") : (((b-d)*(e-c)==(a-c)*(f-d)) ? printf("No") : printf("Yes"));}
```

正常代码：

```c
#include<cstdio>
int main()
{
	long long a,b,c,d,e,f;
	scanf("%lld%lld%lld%lld%lld%lld",&a,&b,&c,&d,&e,&f);
	((a-c)*(a-c)+(b-d)*(b-d)!=(c-e)*(c-e)+(d-f)*(d-f)) ? printf("No") : (((b-d)*(e-c)==(a-c)*(f-d)) ? printf("No") : printf("Yes"));
}
```


---

## 作者：FJ·不觉·莫笑 (赞：0)

### **一道纯数学题**  


------------
### **读题：**  
   给你三个点。让你找一个点和一个角度使得按这个点旋转这个角度后，$a$的新位置与 $b$的原位置重合，$b$的新位置与$c$的原位置重合。  
   **_可能有点难懂，稍微思考即可得出简洁的题意_ ：**  
   给你三个点的坐标，如果$ab=bc$，三点不共线，就输出$Yes$，否则输出$No$.  


------------
### **思路：**  
  也没啥了，照着上面做即可。  


------------
### **注意：**  
 1. 要开$long$ $long$。  
 2. 要先判断$ab=bc$。  


------------
### **上代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[3],b[3];//a表示ax,ay,az;b表示bx,by,bz  
int main()
{
	cin>>a[1]>>a[2]>>a[3]>>b[1]>>b[2]>>b[3];
	long long x=(a[1]-a[3])*(a[1]-a[3])+(a[2]-b[1])*(a[2]-b[1]),y=(a[3]-b[2])*(a[3]-b[2])+(b[1]-b[3])*(b[1]-b[3]);
	if(x!=y) 
  		cout<<"No";//判断ab是否等于bc
	else
	{
		if((a[2]-b[1])*(b[2]-a[3])==(a[1]-a[3])*(b[3]-b[1]))//公式，判断是否三点共线
			cout<<"No";
		else 
  			cout<<"Yes";
	} 
}
```


---

## 作者：Node_Edge (赞：0)

**题目：**

给你三个点。让你找一个点和一个角度使得按这个点旋转这个角度后，$a$ 的新位置与 $b$ 的原位置重合，$b$ 的新位置与 $c$ 的原位置重合。

**思路：**

三个点的坐标，如果 $ab=bc$，三点不共线，就输出 $Yes$，否则输出 $No$.

**注意：**

三年 OI 一场空，不开 long long 见祖宗

**Code**

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
int main() {
	LL a1,a2,b1,b2,c1,c2;
	cin>>a1>>a2>>b1>>b2>>c1>>c2;
	LL x=(a1-b1)*(a1-b1)+(a2-b2)*(a2-b2);
	LL y=(b1-c1)*(b1-c1)+(b2-c2)*(b2-c2);
	if(x!=y||(a2-b2)*(c1-b1)==(a1-b1)*(c2-b2)){
		cout<<"No";
	}else {
		cout<<"Yes";
	}
	return 0;
}
```


---

## 作者：yzx72424 (赞：0)

一道纯数学题，没有任何编程技术含量。。

设找到的点为O点则角aob=角boc，且ao=bo=co，这样△aob就全等于△boc,所以ab=bc.

反过来，只要保证ab=bc，且abc不共线（k ab!=k bc）即可

考虑到分母不为0的情况,把斜率公式移项。

 ```
#include<bits/stdc++.h>
using namespace std;
int main() {
	int a,b,m,n,j,i;
	scanf("%d%d%d%d%d%d",&a,&b,&i,&j,&n,&m);
	if((1LL*(a-i)*(a-i)+1LL*(b-j)*(b-j)==1LL*(i-n)*(i-n)+1LL*(j-m)*(j-m))&&(1LL*(b-j)*(i-n)!=1LL*(a-i)*(j-m)))printf("Yes");
	else printf("No");
}
```

---

## 作者：lhjy666 (赞：0)

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	ll ax,ay,bx,by,cx,cy;
	scanf("%lld%lld%lld%lld%lld%lld",&ax,&ay,&bx,&by,&cx,&cy);
	if((cy-by)*(cx-ax)==(cy-ay)*(cx-bx))
	{
		printf("No");
		return 0;
	}
	else
	{
		if((ax-bx)*(ax-bx)+(ay-by)*(ay-by)==(bx-cx)*(bx-cx)+(by-cy)*(by-cy))
		{
			printf("Yes");
			return 0;
		}
```

---


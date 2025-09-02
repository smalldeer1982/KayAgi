# Magic Spheres

## 题目描述

Carl 有三种类型的魔法球分别有 $a$ 个, $b$ 个, $c$ 个，他可以使任意两个相同类型的魔法球变为另一种类型的魔法球，当他三种类型的魔法球数量分别对应为 $x$ 个, $y$ 个, $z$ 个的时候可以组成魔法阵，现在请你求 Carl 能否成功组成魔法阵。

## 样例 #1

### 输入

```
4 4 0
2 1 2
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
5 6 1
2 7 2
```

### 输出

```
No
```

## 样例 #3

### 输入

```
3 3 3
2 2 2
```

### 输出

```
Yes
```

# 题解

## 作者：EdenSky (赞：4)

# [CF606A Magic Spheres](https://www.luogu.com.cn/problem/CF606A)
- [更好的阅读体验](https://www.cnblogs.com/wanguan/p/17020016.html)

## 正文

妥妥的模拟，当然这边有个易错的地方：**最后合并出来的所有类型球数只要大于等于这种类型的目标球数就可以合成**。

我们设 $g$，对于每一种类型的球，如果它的现有球数（即 $k\in\{a,b,c\}$）大于等于它的目标球数（即 $t\in\{x,y,z\}$），那么 $g\leftarrow g+\left \lfloor (k-t)\div 2 \right \rfloor$，代表可以用来转换的球数；相反的，我们设 $d$ 代表需要转换的球数，显而易见当 $t>k$ 时 $d\leftarrow d+(t-k)$。

最后只要判断可以用来转换的球数是否大于等于需要转换的球数，即如果 $k\geq d$，输出 `Yes`，否则输出 `No`。

```cpp
#include<iostream>
using namespace std;
int a,b,c,x,y,z;
int d,g;
int main(){
	cin>>a>>b>>c>>x>>y>>z;
	if(a>=x)	g+=(a-x)/2;
	else	d+=x-a;
	if(b>=y)	g+=(b-y)/2;
	else	d+=y-b;
	if(c>=z)	g+=(c-z)/2;
	else	d+=z-c;
	if(g>=d)	cout<<"Yes";
	else	cout<<"No";
}
```

---

## 作者：cff_0102 (赞：3)

先求出 $a,b,c$ 与 $x,y,z$ 之间的差，把 $x,y,z$ 视为基准线，求出 $a,b,c$ 分别比基准线多多少，少多少。

因为比基准线多的两个球可以换一个（比基准线少的）球，所以把比基准线少的球的总数和比基准线多的球的总数的一半作比较，可以得出最后能不能换成。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	int a,b,c,x,y,z;cin>>a>>b>>c>>x>>y>>z;
	int d=0,s=0;//比“基准线”多的和比它少的球数，记得初始化 
	if(a>x)d+=(a-x)/2;
	else s+=x-a; 
	if(b>y)d+=(b-y)/2;
	else s+=y-b; 
	if(c>z)d+=(c-z)/2;
	else s+=z-c;
	//cout<<d<<" "<<s; 
	//这样求出了多的总数和少的总数
	if(d>=s)cout<<"Yes";
	else cout<<"No";//判断 
	return 0;
}
```
~~七十九道测试点吓我一跳~~

---

## 作者：KarmaticEnding (赞：2)



- 首先，如果他三个魔术球都不满足需求：直接```No```掉。

- 其次，如果它只有一个魔术球数量满足要求：无论怎么调配，都无法使另外两个数量满足需求：厚此薄彼，厚彼薄此。```No```。

- 然后，如果他三个魔术球都满足需求：算都不用算,```Yes```。

- 最难的是两个魔术球。（__先特判简单情况，再入手复杂情况不仅能提高程序速度，还能更好的理清思路__） 


两个魔术球：如果 $A$ 和 $B$ 的数量可以适当调配使得 $C$ 满足要求，则输出 ```Yes```，反之则输出 ```No```。

那么，怎么适当调配呢？很简单，如果 $A$ 和 $B$ 中数量少的那个与要求之差 $\ge C$ 与要求之差即可。




听懂了吗，上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c;
	int x,y,z;
	scanf("%d%d%d%d%d%d",&a,&b,&c,&x,&y,&z);//使用格式化的原因：快，为以后做准备
	if(a<x && b<y && c<z) printf("No");
  	else if((a<x && b<y) || (a<x && c<z) || (c<z && b<y)) printf("No");
   	else if(a>x && b>y && c>z) printf("Yes");
  	else {//最关键的一步
  		//简写
  		if(min(a-x,b-y)>z-c) printf("Yes");
  		else if(min(a-x,c-z)>y-b) printf("Yes");
  		else if(min(c-z,b-y)>x-a) printf("Yes");
  		else printf("No");
  }
  return 0;//一定要写，因为NOI用的linux没有这句话会RE（我自己就犯过这样的错）
}
```

---

## 作者：Larryyu (赞：1)

## _Description_
给定三种球的初始和目标数量，且两个同种的球可以换为一个任意种类的球，问能否达到目标。
## _Solution_
设初始数量为 $i$，目标数量为 $j$：

- 当 $i>j$ 时，$i$ 有多余的球去转换，具体能转换的次数为 $(i-j) \div 2$；
- 当 $i<j$ 时，$i$ 需要其他种类来补数量，具体数量为 $j-i$；

所以直接比较三类球初始与目标数量的大小关系，按上述两类存入或取出于 $rest$ 即可。

需注意的是，两个同种球是可以转为另一个与其同种的球，即消耗一个球，所以 $rest \ge 0$ 就可以达成目标。

代码实现难度不大。

## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,x,y,z;
int rest;		//意义同上
int main(){
    cin>>a>>b>>c>>x>>y>>z;
    if(a>x){
        rest+=((a-x)/2);//多则存
    }else{
        rest-=(x-a);    //少则取
    }
    if(b>y){
        rest+=((b-y)/2);
    }else{
        rest-=(y-b);
    }
    if(c>z){
        rest+=((c-z)/2);
    }else{
        rest-=(z-c);
    }
    if(rest>=0) cout<<"Yes";
    else cout<<"No";
    return 0;
}
```
#### 完结撒花！！

---

## 作者：AirQwQ (赞：1)

## 入手
- 肯定不能暴力尝试，必须用一些数学方法，比如整体思想。

- 因为两个**同色球**可随便换一个新球，所以用一个求和变量 $ sum $ 记录就行。

## 实现

1. 用 $ a $ 与 $ x $ 为例，如果 $ a>x $ 那么 $ sum $ 变量加上 $ (a-x) \div2 $ 即可，反之减去 $ (x-a) $。

2. 在最后判断判断 $ sum \ge 0 $ 输出即可。

## 坑点

1. 必须是同色球，所以必须单个处理，不能最后一起除以二。

2. 同样是因为要同色，就不能在 $ a>x $ 时 $ sum $ 加上 $ (a-x) $，$ a \le x $ 时减去 $ (x-a)\times 2 $，会 [WA](https://www.luogu.com.cn/record/86039361) 掉。

## AcCode：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,c,x,y,z,sum=0;
    cin>>a>>b>>c>>x>>y>>z;
    if(a>x) sum+=((a-x)/2); else sum-=(x-a);
    if(b>y) sum+=((b-y)/2); else sum-=(y-b);
    if(c>z) sum+=((c-z)/2); else sum-=(z-c);
    if(sum>=0) puts("Yes");
    else puts("No");
    return 0;
}


```

---

## 作者：ztxtjz (赞：1)

## 【题意】
可将两个同种颜色的球体转换为一个任意颜色的球体，使每种颜色的球体数量超过要求的数量，判断能否完成。
## 【思路】
①若已有个数＞要求个数，则（已有个数-要求个数）÷ 2为多出的球体能够转换得到的球体个数，记为l。

②若已有个数＜要求个数，则（要求个数-已有个数）为需要转换得到的球体个数，记为r。

③若l≥r，则能完成；反之不能完成。

先上一份错误代码，有注意点
```cpp
#include <cstdio>
int a,b,c,x,y,z;  
int l,r;   
int main()
{
	
	scanf("%d%d%d%d%d%d",&a,&b,&c,&x,&y,&z);
	a>x?l+=a-x:r+=x-a;
	b>y?l+=b-y:r+=y-b;
	c>z?l+=c-z:r+=z-c;
	if(l>=r*2) printf("Yes");
	else printf("No");
	return 0;
}
```
不能将**多出的总个数**与**缺少总个数的两倍**进行比较，可能会导致两种颜色不同的球体转换成另一球体，比如一个蓝色的和一个紫色的合成一个橙色的，不符合题意。
## 【代码】
```cpp
#include <cstdio>
int a,b,c,x,y,z;  //与题目内含义相同 
int l,r;  //l表示多出的球体个数能转换得到的球体个数，r表示缺少的球体个数 
int main()
{
	
	scanf("%d%d%d%d%d%d",&a,&b,&c,&x,&y,&z);
	a>x?l+=(a-x)/2:r+=x-a;
	b>y?l+=(b-y)/2:r+=y-b;
	c>z?l+=(c-z)/2:r+=z-c;
	if(l>=r) printf("Yes");  //转换得到的个数≥缺少的个数 
	else printf("No");  //转换得到的个数＜缺少的个数
	return 0;
}
```

---

## 作者：yuangq (赞：1)

这题直接模拟即可

详情请见注释
~~~ cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<ctime>
#include<climits>
#include<vector>
using namespace std;
int main()
{
    int a,b,c;//a，b，c的数量 
	int wa,wb,wc;//a，b，c的需求 
	cin>>a>>b>>c>>wa>>wb>>wc;
	int n=0;
	if(a>=wa)
	{
		if((a-wa)%2==1)//因为必须配对出现，所以要把多余的舍掉 
		{
			wa++; 
		}
		n=n+a-wa;//多了a-wa个废球 
	}
	if(b>=wb)
	{
		if((b-wb)%2==1)
		{
			wb++;
		}
		n=n+b-wb;
	} 
	if(c>=wc)
	{
		if((c-wc)%2==1)
		{
			wc++;
		}
		n=n+c-wc;
	}  
	if(a<wa)
	{
		n=n-2*(wa-a);//如果不够，就从废球中补充 
	} 
	if(b<wb)
	{
		n=n-2*(wb-b);
	} 
	if(c<wc)
	{
		n=n-2*(wc-c);
	} 
	if(n>=0)
	{
		cout<<"Yes";
	}
	else
	{
		cout<<"No";
	}
    return 0;
}
~~~

---

## 作者：Symbolize (赞：0)

# 思路
将可变换球数与距离达成阵法相差球数进行比较，若前者大，则可以达成阵法，否则不可达成。

可变换球数：

$\max(0,(a-x)\div2)+\max(0,(b-y)\div2)+\max(0,(c-z)\div2)$。

距离达成阵法相差球数：

$\max(0,x-a)+\max(0,y-b)+\max(0,z-c)$。

最后附上 AC 代码！！！

## Code
```cpp
#include<bits/stdc++.h>//万能头
#define int long long
using namespace std;
int a,b,c,x,y,z;
signed main()
{
	cin>>a>>b>>c>>x>>y>>z;//输入
	cout<<((max((int)0,(a-x)/2)+max((int)0,(b-y)/2)+max((int)0,(c-z)/2)>=max((int)0,x-a)+max((int)0,y-b)+max((int)0,z-c)) ? "Yes" : "No")<<endl;//输出
	return 0;//收场
}
```

---

## 作者：lolsq (赞：0)

### 我的思路
+ 就是在开始的时候先进性一个处理，比较出 $a$ 和 $x$ , $b$ 和 $y$   , $c$ 和 $z$ 之间谁更大.这样在后面就不用在判定了，可以直接就进行加减。最后就看加减过后的值是正还是负，就能看出是不是能组成魔法阵。

### 注意点
+   c++里的 `/2` 会向下取整。

### 代码

~~~
#include<bits/stdc++.h>
using namespace std;
int ans;
int main()
{
    int a,b,c,x,y,z;
    cin>>a>>b>>c>>x>>y>>z;
    a=a-x;
    b=b-y;
    c=c-z;//这里就是处理了一个初值，这样可以化简很多的计算， 
    if(a>0)
	ans+=a/2;//因为两个同种的才能换一个另外一种的，所以要/2， 
    else if(a<=0) 
	ans+=a;
    if(b>0)
	ans+=b/2;
    else if(b<=0) 
	ans+=b;
    if(c>0)
	ans+=c/2;
    else if(c<=0)
	ans+=c;
    if(ans>=0)
	printf("Yes");
    else 
	printf("No");
    return 0;//看他是正是负
}
~~~

---

## 作者：NATO (赞：0)

### 题目分析：
模拟，如果原来所有魔法球都比组成魔法阵的多，直接输出 ```Yes```，否则先记录比组成魔法阵的数量多的魔法球的数量与该种魔法球组成魔法阵的数量之差，再补充给不够的魔法球，如果补充完了还是不够，那就输出 ```No```。

#### 注意事项：
注意，是两个魔法球变成一个另一种魔法球。

#### 参考代码：
```cpp
#include<bits/stdc++.h> 
#define ll long long
using namespace std;
ll a,b,c;
ll x,y,z;
ll ans;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>a>>b>>c>>x>>y>>z;
	if(a>=x&&b>=y&&c>=z)
	{
		cout<<"Yes";return 0;
	}
	if(a>x)	ans+=(a-x)/2;
	if(b>y)	ans+=(b-y)/2;
	if(c>z)	ans+=(c-z)/2;
	if(a<x)	ans-=((x-a-1)/2+1);
	if(b<y)	ans-=((y-b-1)/2+1);
	if(c<z)	ans-=((z-c-1)/2+1);
	if(ans>=0)
		cout<<"Yes";
	else
		cout<<"No";
}
```


---

## 作者：Dovish (赞：0)

这是一道适合新手入门的模拟。

直接记录三种魔法球多余的数量和总共缺少的数量。

然后计算将三种魔法球多余的数量全部转换后得到的数量是否大于总共缺少的数量。是则输出 Yes，否则输出 No。

### 贴上代码：

------------
```
#include<bits/stdc++.h>
using namespace std;
int x[3],y[3],z[3],f;
int main()
{
	cin>>x[0]>>x[1]>>x[2]>>y[0]>>y[1]>>y[2];//输入
	for(int i=0;i<=2;i++)
	if(x[i]>y[i])z[i]=x[i]-y[i];//如果当前魔法球施展法术后还有剩余,那就去转换为不足的魔法球
	else if(x[i]<y[i])f+=y[i]-x[i];//否则，记录下缺失的数量
	f-=z[0]/2;
	f-=z[1]/2;
	f-=z[2]/2;//分别将三种多余的魔法球转化为不足的
  	//注意：c++中整型的除法会舍去末尾小数，所以不用考虑剩余的魔法球是奇数个
	if(f<=0)cout<<"Yes";//不会有缺少的魔法球，则可以组成魔法阵
	else cout<<"No";//否则就不行
	return 0;
}
```

---

## 作者：xuorange (赞：0)

#### 题意简化

有三种颜色的小球，已知各有 $a,b,c$ 个，现在想要得到至少 $x,y,z$ 个，你可以消耗两个相同颜色的小球得到一个其他颜色的小球。给定 $a,b,c$ 和 $x,y,z$ ，求是否能得到想要的结果。

#### 题解与代码

首先，如果 $a>x$ 且 $b>y$ 且 $c>z$ 的话，就是直接输出 Yes 。

否则，如果有一种颜色有少的，假设一共少 $m$ 个，那么至少要进行 $m$ 次转换。又因为每次转换需要消耗两个相同颜色的小球，所以，计算每个颜色比最低要求多的数目，然后让这个数整除 $2$ ，把所得到的相加，若此时 $\ge m$ ，则是 Yes ，否则就是 No 。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
int main(){
	int a[3],x[3],ans = 0;
	for(int i=0;i<3;++i)scanf("%d",&a[i]);
	for(int i=0;i<3;++i){
		scanf("%d",&x[i]);
		if(a[i]-x[i]<0)ans+=a[i]-x[i]; //当前够用
		else ans+=(a[i]-x[i])/2; //不够就补
	}
	if(ans<0)printf("No\n"); //不够用
	else printf("Yes\n");
	return 0;
}
```

---


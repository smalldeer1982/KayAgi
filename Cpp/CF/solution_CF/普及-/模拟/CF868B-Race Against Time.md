# Race Against Time

## 题目描述

Have you ever tried to explain to the coordinator, why it is eight hours to the contest and not a single problem has been prepared yet? Misha had. And this time he has a really strong excuse: he faced a space-time paradox! Space and time replaced each other.

The entire universe turned into an enormous clock face with three hands — hour, minute, and second. Time froze, and clocks now show the time $ h $ hours, $ m $ minutes, $ s $ seconds.

Last time Misha talked with the coordinator at $ t_{1} $ o'clock, so now he stands on the number $ t_{1} $ on the clock face. The contest should be ready by $ t_{2} $ o'clock. In the terms of paradox it means that Misha has to go to number $ t_{2} $ somehow. Note that he doesn't have to move forward only: in these circumstances time has no direction.

Clock hands are very long, and Misha cannot get round them. He also cannot step over as it leads to the collapse of space-time. That is, if hour clock points 12 and Misha stands at 11 then he cannot move to 1 along the top arc. He has to follow all the way round the clock center (of course, if there are no other hands on his way).

Given the hands' positions, $ t_{1} $ , and $ t_{2} $ , find if Misha can prepare the contest on time (or should we say on space?). That is, find if he can move from $ t_{1} $ to $ t_{2} $ by the clock face.

## 说明/提示

The three examples are shown on the pictures below from left to right. The starting position of Misha is shown with green, the ending position is shown with pink. Note that the positions of the hands on the pictures are not exact, but are close to the exact and the answer is the same.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF868B/a67db32a4530841b7d57b21ea225d21a83f385f3.png)

## 样例 #1

### 输入

```
12 30 45 3 11
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
12 0 1 12 1
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
3 47 0 4 9
```

### 输出

```
YES
```

# 题解

## 作者：过氧化氢_syq0057 (赞：7)

我感觉这题就是代码有点多，题意还是很好懂的

解释在代码中，请自行观看

$Code$
```cpp
#include <iostream>
using namespace std;
double ms[6];
double h, m, s, t1, t2;
double d1, d2, d3, dt1, dt2;//按照题意定义变量 
int swap(int a, int b) {//自己写的交换函数 
	int temp = a;
	a = b;
	b = temp;//交换过程 
}
void sort(double a[]) {//自己写的排序 
	for (int i=1; i<=5; i++) {
		for (int j=i+1; j<=5; j++) {//循环交换最大值和最小值 
			if (a[j] > a[i]) {//如果比后面的数大 
				swap(a[j], a[i]);//交换两个数 
			}
		}
	}
}
int main(){
	cin >> h >> m >> s >> t1 >> t2;//输入h时，m分，s秒，出发位置t1，目的地t2 
	d1 = (h + m / 60 + s / 3600) / 12;//如果h是12且s&&m大于0，就减1，保证h小于12 
	if(d1 > 1) {
		d1--;
	}
	d2 = (m + s / 60) / 60;//同h
	if(d2 > 1) {
		d2--;
	}
	d3 = s / 60;
	dt1 = t1 / 12;//米莎的位置 
	dt2 = t2 / 12;//目标的位置 
	ms[1] = d1;
	ms[2] = d2;
	ms[3] = d3;
	ms[4] = dt1;
	ms[5] = dt2;
	sort(ms);//sort对浮点数排序会错，所以自己写了一个sort 
	if((ms[1] == dt1 && ms[2] == dt2) || (ms[2] == dt1 && ms[1] == dt2)
	 || (ms[2] == dt1 && ms[3] == dt2) || (ms[3] == dt1 && ms[2] == dt2)
	 || (ms[4] == dt1 && ms[3] == dt2) || (ms[3] == dt1 && ms[4] == dt2)
	 || (ms[5] == dt1 && ms[4] == dt2) || (ms[4] == dt1 && ms[5] == dt2)
	 || (ms[5] == dt1 && ms[1] == dt2) || (ms[1] == dt1 && ms[5] == dt2)
	 ) {//强制if判断是否相邻 
        	cout << "Yes";//如果能到t2（相邻）就输出Yes 
	}
	else {
		cout << "No";//如果到不了t2（不相邻）就输出No 
	}
	return 0;//完美结束 
}
```

嗯，希望大家理解
~~（别忘了留赞啊）~~

---

## 作者：王熙文 (赞：2)

这道题堆在我的尝试过的题目里很久，今天终于 AC 了，这道题的细节还是非常多的。

## 题意

还是有必要说一下题意的：

在一个时钟上，有 $3$ 个针（挡着的东西）和两个点，问能否从一个点到另一个点，**注意**：如果起点与一根针是同一个位置，判断下一时刻（一瞬间）（按时针的运动顺序，顺时针走）中这根针是否挡着去路，如果挡着则过不去，否则可以过去。

其中输入的第一个数和最后两个数默认乘上 $5$（其实是因为它们是时针）。

提供两个神奇的数据来帮助理解题意：（我 WA 过的点）

Test $4$ :

```10 22 59 6 10```

这组数据，要输出 ```YES```，这就涉及了“注意”里的。这两个点是介于第一根针和第二根针里的，而第二个点与第一个针重合，但第一根针正在向着第三根针走，接下来不挡去路，所以可以到达。

Test $8$ :

```5 41 11 5 8```

这组数据，要输出 ```NO```。这与第四组数据正好相反。第一个点向着第二个点顺时针走的时候，第一根针正好也顺时针走。下一瞬间，第一根针正好挡住了去路，所以不能到达。

## 题解

首先，将三根针的位置从小到大排序，此时不用分哪根是哪根，因为它们都顺时针运动。其次，将两个点的位置也从小到大排序。

接下来，检查这两个点是否在三根针的两根中（如果在这两根中，就能到达）。设排序之后**下标**较小的针的位置为 $a$，另外一个为 $b$，两个点中位置较小的位置为 $c$，另外一个为 $d$。

分两种情况：

* $a$ 位置的针和 $b$ 位置的针，两根针跨越了 $0$ 点位置，也就是 $a>b$ 时：判断这两个点是否都在这两段中的任意一个：$0$ 点到 $b$ 点之间或者 $a$ 点到 $0$ 点之间（这里注意边界问题，即如果在 $0 \sim b$，$b$ 点是可以取到的，如果在 $a \sim 0(60)$，$a$ 点不能取到）。

* $a$ 位置的针和 $b$ 位置的针，两根针不跨越 $0$ 点位置，也就是 $a \le b$ 时：判断这两个点是否都在 $a \sim b$ 这个段即可。

注意有一个细节，即两针或三针共线：我的程序可以通过两针共线的情况，但不能通过三针共线的情况（建议手动模拟），特判即可。

## 参考代码

注：我的大括号换行和这一行的字符数有关，码风不喜勿喷。

```cpp
#include<bits/stdc++.h>
using namespace std;

bool check(int a,int b,int c,int d) // 检查 c 点到 d 点是否能在 a~b 这段走
{
    if(a>b) // 跨越 0
    {
        if((c<=b || c>a) && (d<=b || d>a)) // 是否在两段内
        {
            return 1;
        }
        else return 0;
    }
    else // 不跨越
    {
        if(c>a && d<=b) return 1; // 是否在一段内
        else return 0;
    }
}

int main()
{
    int a,b,c,d,e;
    cin>>a>>b>>c>>d>>e;
    a*=5,d*=5,e*=5; // 注意 a,d,e 要 *5
    if(a>b) swap(a,b); // 排序
    if(b>c) swap(b,c);
    if(a>b) swap(a,b);
    if(d>e) swap(d,e);
    if(a==b && b==c) cout<<"YES"; // 特判三点共线的情况
    else if(check(a,b,d,e) || check(b,c,d,e) || check(c,a,d,e))
    { // 对于每两针都检查
        cout<<"YES";
    }
    else cout<<"NO";
    return 0;
}
```

---

## 作者：Dark_Sky (赞：2)

既然这题没人写题解，那我就来水一篇了

这题我的做法主要是if，思路是把所有的时,分,秒除以指针的数(12,60,60)

也把Misha的位置和目标位置÷12

保证它们的单位统一,可以判断它们的位置

然后把所有情况都判断一遍(我这里用的是sort来判断)

只要两个位置(t1,t2)是相邻的就输出yes,不相邻输出no.

中间有几个要点，我在程序中简单说一下
```
#include <iostream>

using namespace std;

void paixu(double a[6]){//因为double的不稳定性,用sort会有问题,所以自己写了一个排序
	int i, j;
	double temp;
	for(i = 1;i <= 5;i++){
		for(j = i;j <= 5;j++){
			if(a[j]<a[i]){//排序就不解释了
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
}

int main(){
	double time[6];
	double h,m,s,t1,t2;
	double dh,dm,ds,dt1,dt2;
	cin>>h>>m>>s>>t1>>t2;
	dh = (h+m/60+s/3600)/12;//如果时针是12且分针与秒针大于0,就减1,保证小时小于12
	if(dh > 1)dh--;
	dm = (m+s/60)/60;//同小时
	if(dm > 1)dm--;
	ds = s/60;
	dt1 = t1/12;//Misha的位置
	dt2 = t2/12;//目标位置
	time[1]=dh;time[2]=dm;time[3]=ds;time[4]=dt1;time[5]=dt2;
	paixu(time);//因为sort的不稳定,所以自己写了一个排序函数
	if((time[1]==dt1&&time[2]==dt2)||(time[2]==dt1&&time[1]==dt2)||(time[2]==dt1&&time[3]==dt2)||(time[3]==dt1&&time[2]==dt2)||(time[4]==dt1&&time[3]==dt2)||(time[3]==dt1&&time[4]==dt2)||(time[5]==dt1&&time[4]==dt2)||(time[4]==dt1&&time[5]==dt2)||(time[5]==dt1&&time[1]==dt2)||(time[1]==dt1&&time[5]==dt2)){
		//疯狂的if,来判断是否相邻
        	cout<<"Yes"<<endl;//相邻输出yes
	}
	else cout<<"No"<<endl;//不相邻输出no
	return 0;//结束!
}
```


---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF868B)

------------
# 思路：
求出每个针所指的角度范围，然后记得从小到大排序，最后按照左闭右开去判断是否属于同一块区域。

### AC 记录：
![](https://cdn.luogu.com.cn/upload/image_hosting/wdv8pxuj.png)

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
double x,y,a,b,c;
int h,m,s,t1,t2,ans1,ans2;
signed main(){
	cin>>h>>m>>s>>t1>>t2;
	t1%=12;
	t2%=12;
	x=t1*30.0,y=t2*30.0;
	h%=12;
	a=s*6.0,b=m*6.0+s/10.0;
	c=h*30.0+m/10.0+s/360.0;
	if(a>b){
		swap(a,b);
	}
	if(a>c){
		swap(a,c);
	}
	if(b>c){
		swap(b,c);
	}
	if(x>=a&&x<b){
		ans1=1;
	}else if(x>=b&&x<c){
		ans1=2;
	}else{
		ans1=3;
	}
	if(y>=a&&y<b){
		ans2=1;
	}else if(y>=b&&y<c){
		ans2=2;
	}else{
		ans2=3;
	}
	if(ans1==ans2){
		cout<<"YES"<<endl;
	}else{
		cout<<"NO"<<endl;
	}
	return 0;
}
```

---

## 作者：expecto__patronum (赞：0)

## 题意
给定 $5$ 个数 $h$，$m$，$s$，$t_1$，$t_2$。

询问是否能在表盘上不跨越表针地从起始位置走到终止位置，表针无限长。

位置和指针均不重合。

## 解法
注意时针会被分和秒影响，分针会被秒影响。所以 $h$ 可以等于 $t_1$，此时 $h$ 仍在 $t_1$ 之后。

只需要考虑两个位置之间一侧是否 $0$ 个或三个指针即可。

## 代码
```
/* LittleFall : Hello! */
#include <bits/stdc++.h>
using namespace std;
int main(void)
{
    int h,m,s,t1,t2,ans=0;
    scanf("%d%d%d%d%d",&h,&m,&s,&t1,&t2);
    if(t1>t2)
        swap(t1,t2);
    if(h>=t1&&h<t2)
        ans++;
    if(m>=t1*5&&m<t2*5)
        ans++;
    if(s>=t1*5&&s<t2*5)
        ans++;
    if(ans==0||ans==3)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
```
[blog](https://blog.csdn.net/m0_37809890/article/details/78164240)


---

## 作者：_775spacing747_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF868B)
# 1 题意
在一个平面上，有 $3$ 个障碍和 $2$ 个点，请问能否从一个点到另一个点。
# 2 思路
首先需要特殊处理一下 $h$，接着存储一下起点和终点，最后用一堆分支语句来判断有没有解。
# 3 代码
```
#include<bits/stdc++.h>//万能头yyds! 
using namespace std;
double a[6];
int main()
{
	double h,m,s,x,y,p,q,z,e,r;
	cin>>h>>m>>s>>x>>y;
	//开始计算 
	p=(h+m/60+s/3600)/12;//算一下时间 
	if(p>1)p--;//特判p 
	q=(m+s/60)/60;
	if(q>1)q--;
	z=s/60;
	e=x/12;
	e=y/12;
	//把数存一下
	a[1]=p;
	a[2]=q;
	a[3]=z;
	a[4]=e;
	a[5]=r;
	sort(a+1,a+5+1);//排序很重要！！！ 
	//开始判断 
	if(a[4]==e&&a[5]==r)cout<<"YES";
	else if(a[1]==e&&a[2]==r)cout<<"YES";
	else if(a[4]==e&&a[3]==r)cout<<"YES";
	else if(a[3]==e&&a[2]==r)cout<<"YES";
	else if(a[2]==e&&a[3]==r)cout<<"YES";
	else if(a[1]==e&&a[5]==r)cout<<"YES";
	else if(a[5]==e&&a[1]==r)cout<<"YES";
	else if(a[2]==e&&a[1]==r)cout<<"YES";
	else cout<<"NO";//实在不行只好输出NO 
	return 0;//完美结束(^_^)
}
```

---

## 作者：Rookie_t (赞：0)

首先输入对应的时分秒还有出发位置，目的地。
 
如果 $h = 12$ 且 $s>0$，$m>0$，就减 $1$，保证 $h<12$。

然后定义变量存储米莎的位置和目标的位置。 

最后判断有解的情况和无解的情况。 

代码：
 
```cpp 
#include <bits/stdc++.h>
using namespace std;
double ms[6];
double h, m, s, t1, t2;
double d1, d2, d3, dt1, dt2;
int main(){
	cin>>h>>m>>s>>t1>>t2;
	d1 = (h + m / 60 + s / 3600) / 12;
	if(d1 > 1) {
		d1--;
	} 
	d2 = (m + s / 60) / 60;
	if(d2 > 1) {
		d2--;
	}
	d3 = s / 60;
	dt1 = t1 / 12;//米莎的位置 
	dt2 = t2 / 12;//目标的位置 
	ms[1] = d1;
	ms[2] = d2;
	ms[3] = d3;
	ms[4] = dt1;
	ms[5] = dt2;
	sort(ms+1,ms+5+1);//排序 
	if(ms[1] == dt1 && ms[2] == dt2){
		cout<<"YES";
	}
	else if(ms[2] == dt1 && ms[1] == dt2){
		cout<<"YES";
	}
	else if(ms[2] == dt1 && ms[3] == dt2){
		cout<<"YES";
	}
	else if(ms[3] == dt1 && ms[2] == dt2){
		cout<<"YES";
	}
	else if(ms[4] == dt1 && ms[3] == dt2){
		cout<<"YES";
	}
	else if(ms[4] == dt1 && ms[5] == dt2){
		cout<<"YES";
	}
	else if(ms[5] == dt1 && ms[1] == dt2){
		cout<<"YES";
	}
	else if(ms[1] == dt1 && ms[5] == dt2){
		cout<<"YES";
	}
	else{
		cout<<"NO";
	}
	return 0;
}
```

---

## 作者：blsya23a2 (赞：0)

## 分析
为了方便计算，可以把用小时数表示的第 1、4、5 个输入的整数转化为用分钟数表示。由题知，这道题出发点和结束点分别在哪里并不重要，我们只需要知道较小的点和较大的点分别在哪里，用 $f$ 和 $g$ 分别表示。任何指针的位置用 $a_i$ 表示。
### 判断方法
从$f$ 到 $g$ 的路线有：
- 从 $f$ 增加到 $g$。当 $f<a_i<g$ 时，这条路线不通。

- 从 $f$ 减小到 $0$ 再从 $60$ 减小到 $g$。当 $0<a_i<f$ 或 $g<a_i<60$ 时，这条路线不通。

如果两条路线都不通，输出 `NO`，否则输出 `YES`。
### 继续分析
注意指针是顺时针转的，也就是指针和端点重合时有两种情况，顺时针方向不能通过，因为被指针转过去挡住了，而逆时针方向可以通过。所以，我给每根指针的位置都加了 $0.5$，这样既可以体现出转动又不会挡住合法路线。为了避免指针的位置超过 $60$，我对指针的位置取模了 $60$。所以最终，$a_i\gets(a_i+0.5)\bmod60$。
## 代码
```python
a,b,c,d,e = map(int,input().split())
a,b,c,d,e = (5*a+0.5)%60,(b+0.5)%60,(c+0.5)%60,5*d,5*e
f,g = min(d,e),max(d,e)
if (f<a<g or f<b<g or f<c<g) and ((0<a<f or g<a<60) or (0<b<f or g<b<60) or (0<c<f or g<c<60)):
    print('NO')
else:
    print('YES')
```

---

## 作者：zhang_kevin (赞：0)

# Content

在一个时钟上，有 $3$ 个指针（障碍物，不能跨过去）和两个点，问能否从一个点到另一个点。

# Solution

我们可以模拟一下表盘。

要知道，每过一秒钟，秒针就会转动 $6^{\circ}$，分针就会转动 $\dfrac{6^{\circ}}{60} = 0.1^{\circ}$，时针就会转动 $\dfrac{360^{\circ}}{\frac{12}{60}} \div 60 = (\dfrac{1}{120})^{\circ}$。

因此，我们可以把表盘模拟出来（算出每个指针在多少度的位置上），计算是否可以从两边走即可。

当然，由于精度原因，不能直接用 `double`，但我们可以自己手写分数代码（实现 `+`、`-`、`*`、`/`、`<`、`>`、`==` 即可）：

```cpp
struct Frac{//分数
	int mol, den;
	friend Frac operator + (Frac const a, Frac const b){
		int gbs = lcm(a.den, b.den);
		return {(a.mol*(gbs/a.den))+(b.mol*(gbs/b.den)), gbs};
	}
	friend Frac operator - (Frac const a, Frac const b){
		int gbs = lcm(a.den, b.den);
		return {(a.mol*(gbs/a.den))-(b.mol*(gbs/b.den)), gbs};
	}
	friend Frac operator * (Frac const a, Frac const b){
		return {a.mol*b.mol, a.den*b.den};
	}
	friend Frac operator / (Frac const a, Frac const b){
		return {a.mol*b.den, a.den*b.mol};
	}
	friend bool operator < (Frac const a, Frac const b){
		return a.den * b.mol > a.mol * b.den;
	}
	friend bool operator > (Frac const a, Frac const b){
		return a.den * b.mol < a.mol * b.den;
	}
	friend bool operator == (Frac const a, Frac const b){
		if(!(a>b) && !(a<b)){
			return true;
		}
		return false;
	}
};
inline void yf(Frac a){
	int gcd = __gcd(a.mol, a.den);
	a.mol /= gcd;
	a.den /= gcd;
	return;
}
```

解决精度问题，这道题的代码也就呼之欲出啦。

# Code

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define lcm(a, b) (a/__gcd(a, b)*b)
#define Max(a, b) (((a)>(b))?(a):(b))
#define Min(a, b) (((a)<(b))?(a):(b))

using namespace std;

struct Frac{//分数
	int mol, den;
	friend Frac operator + (Frac const a, Frac const b){
		int gbs = lcm(a.den, b.den);
		return {(a.mol*(gbs/a.den))+(b.mol*(gbs/b.den)), gbs};
	}
	friend Frac operator - (Frac const a, Frac const b){
		int gbs = lcm(a.den, b.den);
		return {(a.mol*(gbs/a.den))-(b.mol*(gbs/b.den)), gbs};
	}
	friend Frac operator * (Frac const a, Frac const b){
		return {a.mol*b.mol, a.den*b.den};
	}
	friend Frac operator / (Frac const a, Frac const b){
		return {a.mol*b.den, a.den*b.mol};
	}
	friend bool operator < (Frac const a, Frac const b){
		return a.den * b.mol > a.mol * b.den;
	}
	friend bool operator > (Frac const a, Frac const b){
		return a.den * b.mol < a.mol * b.den;
	}
	friend bool operator == (Frac const a, Frac const b){
		if(!(a>b) && !(a<b)){
			return true;
		}
		return false;
	}
};
inline void yf(Frac a){
	int gcd = __gcd(a.mol, a.den);
	a.mol /= gcd;
	a.den /= gcd;
	return;
}

Frac H, M, S, T1, T2;

inline bool check(const char fmt[]){
	Frac mx, mn;
	mx = Max(T1, T2);
	mn = Min(T1, T2);
	if(fmt == "bts"){
		if((mx>H&&mn<H) || (mx>M&&mn<M) || (mx>S&&mn<S)){
			return false;
		}
		return true;
	}else if(fmt == "stb"){
		if(mx < H || mn > H || mx < M || mn > M || mx < S || mn > S){
			return false;
		}
		return true;	
	}else{
		assert(0);
	}
	return 114514; 
}

int main(){
	int h, m, s, t1, t2;
	cin >> h >> m >> s >> t1 >> t2;
	
	S = {6*s, 1};
	M = {1*s+60*m, 10};
	H = {1*s+60*m+3600*h, 120};
	T1 = {t1*30, 1};
	T2 = {t2*30, 1};
	yf(S), yf(M), yf(H), yf(T1), yf(T2);
	
	if(check("bts") || check("stb")){
		cout << "YES" << endl;
	}else{
		cout << "NO" << endl;
	}
	return 0;
}
```


---


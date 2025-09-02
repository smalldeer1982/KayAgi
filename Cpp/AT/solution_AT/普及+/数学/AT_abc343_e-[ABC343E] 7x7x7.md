# [ABC343E] 7x7x7

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc343/tasks/abc343_e

> 座標空間上に一辺 $ 7 $ の立方体を $ 3 $ つ、ちょうど $ 1,2,3 $ 個の立方体に含まれる領域の体積がそれぞれ $ V_1,V_2,V_3 $ となるように配置したいです。

$ 3 $ つの整数 $ a,b,c $ に対し、$ (a\leq\ x\leq\ a+7)\ \land\ (b\leq\ y\leq\ b+7)\ \land\ (c\leq\ z\leq\ c+7) $ で表される立方体領域を $ C(a,b,c) $ とおきます。

以下の条件を全て満たすような $ 9 $ つの整数 $ a_1,b_1,c_1,a_2,b_2,c_2,a_3,b_3,c_3 $ が存在するか判定し、存在するならば実際に $ 1 $ つ求めてください。

- $ |a_1|,|b_1|,|c_1|,|a_2|,|b_2|,|c_2|,|a_3|,|b_3|,|c_3|\ \leq\ 100 $
- $ C_i\ =\ C(a_i,b_i,c_i)\ (i=1,2,3) $ とおいたとき、
  - $ C_1,C_2,C_3 $ のうちちょうど $ 1 $ 個に含まれる領域の体積は $ V_1 $ である。
  - $ C_1,C_2,C_3 $ のうちちょうど $ 2 $ 個に含まれる領域の体積は $ V_2 $ である。
  - $ C_1,C_2,C_3 $ の全てに含まれる領域の体積は $ V_3 $ である。

## 说明/提示

### 制約

- $ 0\leq\ V_1,V_2,V_3\ \leq\ 3\times\ 7^3 $
- 入力は全て整数

### Sample Explanation 1

$ (a_1,b_1,c_1,a_2,b_2,c_2,a_3,b_3,c_3)=(0,0,0,0,6,0,6,0,0) $ の場合を考えます。 !\[\](https://img.atcoder.jp/abc343/aa534bf0a0e8e3f3487c5eeb540e54dc.png) この図は $ C_1,C_2,C_3 $ の位置関係を表したもので、それぞれ橙、水色、緑の立方体に対応しています。 このとき、 - $ |a_1|,|b_1|,|c_1|,|a_2|,|b_2|,|c_2|,|a_3|,|b_3|,|c_3| $ は全て $ 100 $ 以下 - $ C_1,C_2,C_3 $ の全てに含まれる領域は $ (6\leq\ x\leq\ 7)\land\ (6\leq\ y\leq\ 7)\ \land\ (0\leq\ z\leq\ 7) $ であり、その体積は $ (7-6)\times(7-6)\times(7-0)=7 $ - $ C_1,C_2,C_3 $ のうちちょうど $ 2 $ 個に含まれる領域は $ ((0\leq\ x\ <\ 6)\land\ (6\leq\ y\leq\ 7)\ \land\ (0\leq\ z\leq\ 7))\lor((6\leq\ x\leq\ 7)\land\ (0\leq\ y\ <\ 6)\ \land\ (0\leq\ z\leq\ 7)) $ であり、 その体積は $ (6-0)\times(7-6)\times(7-0)\times\ 2=84 $ - $ C_1,C_2,C_3 $ のうちちょうど $ 1 $ 個に含まれる領域の体積は $ 840 $ であり、条件を全て満たします。 $ (a_1,b_1,c_1,a_2,b_2,c_2,a_3,b_3,c_3)=(-10,\ 0,\ 0,\ -10,\ 0,\ 6,\ -10,\ 6,\ 1) $ なども同様に条件を全て満たすため、正当な出力として判定されます。

### Sample Explanation 2

条件を全て満たすような $ 9 $ つの整数 $ a_1,b_1,c_1,a_2,b_2,c_2,a_3,b_3,c_3 $ は存在しません。

## 样例 #1

### 输入

```
840 84 7```

### 输出

```
Yes
0 0 0 0 6 0 6 0 0```

## 样例 #2

### 输入

```
343 34 3```

### 输出

```
No```

# 题解

## 作者：wenlebo (赞：6)

一道暴力题。

只需枚举三个正方体顶点坐标在判断是否满足条件即可。

```
#include <bits/stdc++.h>
using namespace std;
int a,b,c;
int s[30][30][30];
void dr(int x,int y,int z){//“画出”正方体
	for(int i=x+1,o=1;o<=7;o++,i++){
		for(int j=y+1,oo=1;oo<=7;oo++,j++){
			for(int k=z+1,ooo=1;ooo<=7;ooo++,k++){
				s[i][j][k]++;
			}
		}
	}
}
bool ch(int x1,int y1,int z1,int x2,int y2,int z2,int x3,int y3,int z3){//检查
	memset(s,0,sizeof(s));
	dr(x1,y1,z1);
	dr(x2,y2,z2);
	dr(x3,y3,z3);
	int u=0,v=0,w=0;
	for(int i=1;i<=20;i++){
		for(int j=1;j<=20;j++){
			for(int k=1;k<=20;k++){
				if(s[i][j][k]){
					if(s[i][j][k]==1){
						u++;
					}else{
						if(s[i][j][k]==2){
							v++;
						}else{
							w++;
						}
					}
				}
			}
		}
	}
	if(u==a&&v==b&&w==c){
		return 1;
	}else{
		return 0;
	}
}
int main(){
	cin>>a>>b>>c;
	if(a+2*b+c*3!=1029){
		cout<<"No";
		return 0;
	}
   //枚举坐标
   for(int x1=0;x1<=7;x1++){
		for(int y1=0;y1<=7;y1++){
			for(int z1=0;z1<=7;z1++){
	for(int x2=0;x2<=7;x2++){
		for(int y2=0;y2<=7;y2++){
			for(int z2=0;z2<=7;z2++){
	for(int x3=0;x3<=7;x3++){
		for(int y3=0;y3<=7;y3++){
				for(int z3=0;z3<=7;z3++){
							if(ch(x1,y1,z1,x2,y2,z2,x3,y3,z3)){
								cout<<"Yes\n"<<x1<<" "<<y1<<" "<<z1<<" "<<x2<<" "<<y2<<" "<<z2<<" "<<x3<<" "<<y3<<" "<<z3;
								return 0;
							}
	}}}}}}}}}
	cout<<"No";
    return 0;
}


```

---

## 作者：_Weslie_ (赞：4)

## [题目传送门。](https://www.luogu.com.cn/problem/AT_abc343_e)

PS：比赛时题目数据过弱，把我的错误做法放过去了，感谢@CheZiHe929 提供的 [hack](https://www.luogu.com.cn/discuss/786011)。

错误代码可以看[这里](https://www.luogu.com.cn/paste/gbtk6wkq)。

### 思路

固定第一个立方体位置不动，那么第二个立方体三个坐标从 $[-7,7]$ 枚举，第三个立方体也一样。

### 正确性证明

- 如果两个立方体完全不相交，那么完全可以移动到相切的位置。例如：$(0,0,0)$ 与 $(0,1145141919810,0)$ 完全等价于 $(0,0,0)$ 与 $(0,7,0)$。

- 如果两个立方体相切，在 $[-7,7]$ 范围内可以满足所有的相切情况。

因此，该算法在实际上是可以找到答案的。

### 时间复杂度

第一个立方体 $\operatorname{O}(1)$，后面两个需要 $15^6=11390625$ 的时间复杂度，完全可以跑得过。

### Code

```
#include<bits/stdc++.h>
using namespace std;
int f1(int a1,int b1,int c1,int a2,int b2,int c2) {
	int res=1;
	res*=max(0,min(a1,a2)+7-max(a1,a2));
	res*=max(0,min(b1,b2)+7-max(b1,b2));
	res*=max(0,min(c1,c2)+7-max(c1,c2));
	return res;
}
int f2(int a1,int b1,int c1,int a2,int b2,int c2,int a3,int b3,int c3) {
	int res=1;
	res*=max(0,min(min(a1,a2),a3)+7-max(max(a1,a2),a3));
	res*=max(0,min(min(b1,b2),b3)+7-max(max(b1,b2),b3));
	res*=max(0,min(min(c1,c2),c3)+7-max(max(c1,c2),c3));
	return res;
}
int a,b,c;
int main() {
	scanf("%d%d%d",&a,&b,&c);
	if(a+2*b+3*c!=1029) {
		printf("No");
		return 0;
	}
	int x[4],y[4],z[4],rx;
	int x2,y2,z2,x3,y3,z3;
	for(x2=-7; x2<=7; x2++) {
		for(y2=-7; y2<=7; y2++) {
			for(z2=-7; z2<=7; z2++) {
				for(x3=-7; x3<=7; x3++) {
					for(y3=-7; y3<=7; y3++) {
						for(z3=-7; z3<=7; z3++) {
							int three= f2(0,0,0,x2,y2,z2,x3,y3,z3);
							int ab= f1(0,0,0,x2,y2,z2),
							    bc= f1(x2,y2,z2,x3,y3,z3),
							    ac= f1(0,0,0,x3,y3,z3);
							int two=bc+ac+ab-3*three;
							if(two==b&&three==c){
								printf("Yes\n0 0 0 %d %d %d %d %d %d",x2,y2,z2,x3,y3,z3);
								exit(0);
							}
						}
					}
				}
			}
		}
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：kczw (赞：1)

# 题意
已知有三个棱长 $7$ 的正方体，用 $C(a_i,b_i,c_i)(1\le i\le3)$ 表示三个正方体某个统一朝向的顶点。现求一种放置方式使得三个正方体重合部分体积为 $V3$，两个正方体重合部分体积和为 $V2$，只有一个正方体部分的体积和为 $V1$。
# 思路
首先，我想到了暴力做法，但是有 $|a_i|,|b_i|,|c_i|\le100$。很明显的，如果每个值都靠枚举，最坏情况下会枚举 $200^9=2^9\times10^{18}$，死得透透的。

但是我们真的需要枚举这么多次吗？不妨假设三个正方形不重合，此时 $a_i$ 的值的跨度则最多为 $7$（这里不过多解释，因为很简单）。

于是最坏情况下枚举次数变为了 $7^9$，我们将 $7^3=343$ 近似看作 $400$，$7^9$ 近似看作 $6.4\times10^7$，在此题的时限下以及可以通过了。

然后就是枚举过程中的判断，其实很简单。

取三个正方体的所有维度跨度的交集，相乘算出 $V3$，此时第一次判断看是否合法。然后取正方体两两之间所有维度跨度的交集相乘减去 $3\times V3$ 算出 $V2$，此时最后一次判断看是否合法。

之所以不比较 $V1$ 是因为知道 $V3$ 和 $V2$ 是可以直接确定 $V1$ 的。三个正方体总体积为 $3\times7^3=1029$，根据对 $V1,V2,V3$ 的定义，不难知道 $V1+V2\times2+V3\times3=1029$。所以，对于直接输出 `No` 的情况，只需要判断 $V1,V2,V3$ 是否合法即可，如果合法，则只需比较 $V3,V2$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int V1,V2,V3,v1,v2,v3;
int f(int a,int b,int c){
    if(min(a,min(b,c))+7-max(a,max(b,c))<1)return 0;//判空集
    return min(a,min(b,c))+7-max(a,max(b,c));
}
int F(int a,int b){
    if(min(a,b)+7-max(a,b)<1)return 0;//判空集
    return min(a,b)+7-max(a,b);
}
int main(){
    scanf("%d%d%d",&V1,&V2,&V3);
    if(V1+V2*2+V3*3!=1029)puts("No"),exit(0);
    for(int a1=0;a1<=7;a1++)
    for(int b1=0;b1<=7;b1++)
    for(int c1=0;c1<=7;c1++)
    for(int a2=0;a2<=7;a2++)
    for(int b2=0;b2<=7;b2++)
    for(int c2=0;c2<=7;c2++)
    for(int a3=0;a3<=7;a3++)
    for(int b3=0;b3<=7;b3++)
    for(int c3=0;c3<=7;c3++){
        v3=f(a1,a2,a3)*f(b1,b2,b3)*f(c1,c2,c3);
        if(v3!=V3)continue;
        v2=F(a1,a2)*F(b1,b2)*F(c1,c2)+F(a1,a3)*F(b1,b3)*F(c1,c3)+F(a2,a3)*F(b2,b3)*F(c2,c3)-v3*3;
        if(v2!=V2)continue;
        printf("Yes\n%d %d %d %d %d %d %d %d %d",a1,b1,c1,a2,b2,c2,a3,b3,c3);
        exit(0);
    }
}
```

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc343_e)

容易想到，对于暴力枚举三个正方形的位置时，如果其中两个正方形位置已经确定，假设有一个正方形与其他两个都不相交，那么还有一些与其他两个都不相交的情况都不用枚举了，同时，如果三个正方形相对位置固定，将三个同时移动，算出来的体积也不会变，所以可以先固定一个正方形的位置，例如 $0,0,0$，另外两个就直接枚举，由于正方形长度为 $7$ 所以最多枚举顶点的范围为 $-7\le i \le7$，可以通过。

对于求两个正方形的相交体积，直接看 $x,y,z$ 轴相对距离为几，大于等于七就不管，否则将其乘起来，可自行画图理解，三个相交也类似，看三个距离的最小值，有一个大于等于七就不管，然后算一下就行了，具体实现见代码。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int v1,v2,v3,x,y,z,fx,fy,fz,sum,sum1,ans;
int main()
{
	scanf("%d%d%d",&v1,&v2,&v3);//这里默认第一个正方体顶点在0,0,0位置 
	for(int i = -7;i <= 7;++i)//x
		for(int j = -7;j <= 7;++j)//y
			for(int z = -7;z <= 7;++z)//z
				for(int i1 = i;i1 <= 7;++i1)//x
					for(int j1 = j;j1 <= 7;++j1)//y
						for(int z1 = z;z1 <= 7;++z1)//z
						{
							sum = sum1 = 0;
							if(abs(i1 - i) < 7) fx = 7 - abs(i1 - i); else fx = 0;//枚举的两个正方形相交体积 
							if(abs(j1 - j) < 7) fy = 7 - abs(j1 - j); else fy = 0;
							if(abs(z1 - z) < 7) fz = 7 - abs(z1 - z); else fz = 0;
							sum += fx * fy * fz;
							if(abs(i1) < 7) fx = 7 - abs(i1); else fx = 0;//第三个和第一个相交体积 
							if(abs(j1) < 7) fy = 7 - abs(j1); else fy = 0;
							if(abs(z1) < 7) fz = 7 - abs(z1); else fz = 0;
							sum += fx * fy * fz;
							if(abs(i) < 7) fx = 7 - abs(i); else fx = 0;
							if(abs(j) < 7) fy = 7 - abs(j); else fy = 0;
							if(abs(z) < 7) fz = 7 - abs(z); else fz = 0;
							sum += fx * fy * fz;
							if(abs(i1 - i) < 7 && abs(i) < 7 && abs(i1) < 7) fx = 7 - max(abs(i1 - i),max(abs(i1),abs(i))); else fx = 0;//计算三个正方形相交体积 
							if(abs(j1 - j) < 7 && abs(j) < 7 && abs(j1) < 7) fy = 7 - max(abs(j1 - j),max(abs(j1),abs(j))); else fy = 0;
							if(abs(z1 - z) < 7 && abs(z) < 7 && abs(z1) < 7) fz = 7 - max(abs(z1 - z),max(abs(z1),abs(z))); else fz = 0;
							sum1 = fx * fy * fz; sum -= 3 * sum1;//去重 
							if(sum == v2 && sum1 == v3 && 7 * 7 * 7 * 3 - sum * 2 - sum1 * 3 == v1)//是否合法 
							{
								printf("Yes\n");
								printf("%d %d %d %d %d %d %d %d %d",0,0,0,i,j,z,i1,j1,z1);
								return 0;
							}
						}
	printf("No");//没有合法情况 
	return 0;
}
```

---

## 作者：FReQuenter (赞：0)

不难发现，$v1,v2,v3$ 只和三个立方体的位置关系有关。

所以我们钦定第一个立方体的一个顶点位于 $(0,0,0)$。

接下来依次枚举剩余的两个立方体的其中一个顶点位置。记为 $(x2,y2,z2)$ 和 $(x3,y3,z3)$。

接下来通过类似三维前缀和的容斥，就可以获得对应条件下 $v1,v2,v3$ 的值。只需要实现求两个或三个立方体重叠部分的体积即可。

---


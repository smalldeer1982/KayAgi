# [ABC223E] Placing Rectangles

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc223/tasks/abc223_e

正整数 $ X,\ Y $ に対し、$ 2 $ 次元平面上において以下の条件を満たす長方形を**良い長方形**と呼びます。

- 全ての辺は $ x $ 軸または $ y $ 軸に並行である。
- 全ての頂点に対し、その $ x $ 座標は $ 0 $ 以上 $ X $ 以下の整数であり、その $ y $ 座標は $ 0 $ 以上 $ Y $ 以下の整数である。

面積がそれぞれ $ A $ 以上、$ B $ 以上、$ C $ 以上であるような $ 3 $ つの良い長方形を重ならないように配置することができるか判定してください。

ただし、$ 3 $ つの長方形が重ならないとは、どの $ 2 $ つの長方形についても、それらの共通部分の面積が $ 0 $ であることを指します。

## 说明/提示

### 制約

- $ 1\ \leq\ X,\ Y\ \leq\ 10^9 $
- $ 1\ \leq\ A,\ B,\ C\ \leq\ 10^{18} $
- 入力は全て整数である。

### Sample Explanation 1

下の図のように配置すればよいです。長方形内の数値は面積を表します。 $ 2\ \geq\ A,\ 3\ \geq\ B,\ 3\ \geq\ C $ であるので、問題文で与えられた条件を満たします。 !\[image\](https://img.atcoder.jp/ghi/abc223e\_sample.png)

### Sample Explanation 2

条件を満たすように配置することはできません。

## 样例 #1

### 输入

```
3 3 2 2 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3 3 4 4 1```

### 输出

```
No```

## 样例 #3

### 输入

```
1000000000 1000000000 1000000000000000000 1000000000000000000 1000000000000000000```

### 输出

```
No```

# 题解

## 作者：SCAR_L (赞：3)

注：本文中使用的图片为俄罗斯和马达加斯加的国旗，并没有任何政治倾向，只是作者懒的画了。


---
嗯题目说的很明白了所以对于题意就不再多说了。  

首先来看这个问题棘手的点：要求是大于等于 $a, b, c$ 的矩形而不是恰好为 $a, b, c$ 的矩形，这导致我们**并不容易判断每个举矩形的形状**。    
但我们观察到最有可能的方案一定是“贴边”的。也就是说，矩形的一边是固定的。     
于是便得出主要结论：**在固定一条边长的情况下，根据最小面积得出另一边的最小边长**。（即 ```ll cal(...)```函数）

于是矩形的形状这个问题就被我们解决了

---

再来考虑拼接的可能，大致可以分为两种：都叠在一块的，和两个叠一块、另一个插空的：
![](https://cdn.luogu.com.cn/upload/image_hosting/xi48d8rw.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/7fsisgjq.png)

对于都叠在一起的情况当然好说，那对于第二种情况呢？      
我们发现（以图二为例）白色矩形是贴着其中一边的，所以我们不妨先考虑那个“插空”的矩形。    
决定了白色矩形后，红/绿色矩形就和情况一同理了。

有几个小提示：
1. 记得考虑白色正方形太大（即剩余边长为非正数）的情况，要特判。
2. **全程开```long long```！！！**


```cpp
#include <iostream>
#define ll long long
using namespace std;
const int NR = 1e6 + 4;
int x, y;
long long a, b, c;
ll cal(ll s, ll a){return (s + (a-1)) / a;} // 固定一边长和面积后另一边的最小边长, = ceil(s / a) 
bool work(ll aa, ll bb, ll cc) // a, b横，c竖（即情况二） 
{
	ll x1 = x - cal(cc, y);	// 剩下的长度 
	return x1 > 0 && cal(aa, x1) + cal(bb, x1) <= y; // 注意要判x1 > 0，返回叠在一起的高度得小于本身高度 
}
int main()
{
	cin >> x >> y;
	cin >> a >> b >> c;
		
	bool ans = false;	// 记录答案 
	ans |= cal(a, x) + cal(b, x) + cal(c, x) <= y || cal(a, y) + cal(b, y) + cal(c, y) <= x;	// 情况一，都叠在一起 
	ans |= work(a, b, c) || work(b, c, a) || work(c, a, b);	// 其实前两个参数的顺序无所谓，主要是第三个参数为“白色矩形” 
	swap(x, y);	// 减少代码量，直接交换就不用再写一遍work()函数了 
	ans |= work(a, b, c) || work(b, c, a) || work(c, a, b);	// 同样的判断 
	// 输出： 
	if(ans) cout << "Yes" << endl;
	else cout << "No" << endl;
	return 0;
}
```

---

## 作者：FL_sleake (赞：3)

## 题目大意

给定三个数 $a,b,c$，询问是否有某种摆放三个面积分别**至少**为 $a,b,c$ 的矩形的方式，满足摆放出来的图形能被一个 $x\times y$ 的矩形区域完全包含。

## 解题思路

很显然是数学题。又因为要摆放矩形总共只有三个，于是考虑枚举，情况只有以下三种：

$\circ$ 三个矩形均横放或竖放。

$\circ$ 两个矩形横放，剩下一个贴着这两个竖放。

$\circ$ 两个矩形竖放，剩下一个贴着这两个横放。

（一个矩形竖放或横放其实和上面情况无本质区别）

## 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//已知矩形一边时，计算另一边至少为多少满足面积至少为a或b或c。
#define getans(a,b) (a+b-1)/b
int x,y,a,b,c,ld,ans=0;
signed main(){
	cin>>x>>y>>a>>b>>c;
    //三个都横放或竖放
	if(getans(a,x)+getans(b,x)+getans(c,x)<=y||getans(a,y)+getans(b,y)+getans(c,y)<=x) ans=1;
    
	ld=x-getans(a,y);
	if(ld>0&&getans(b,ld)+getans(c,ld)<=y) ans=1;
	ld=x-getans(b,y);
	if(ld>0&&getans(a,ld)+getans(c,ld)<=y) ans=1;
	ld=x-getans(c,y);
	if(ld>0&&getans(a,ld)+getans(b,ld)<=y) ans=1;
    
	ld=y-getans(a,x);
	if(ld>0&&getans(b,ld)+getans(c,ld)<=x) ans=1;
	ld=y-getans(b,x);
	if(ld>0&&getans(a,ld)+getans(c,ld)<=x) ans=1;
	ld=y-getans(c,x);
    
	if(ld>0&&getans(a,ld)+getans(b,ld)<=x) ans=1;
	if(ans==1) cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：2)

# 思路
我们可以考虑贪心，显然放 $3$ 个长方形只需要 $2$ 种情况，当然长和宽互换也有 $2$ 种，我们只讨论一种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/qt8ghq8l.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/tyf2z0al.png)

这是两总情况，我们可以先确定一个长方形，然后剩下的地方放 $2$ 个长方形，我们就可以递归处理了。

先确定的长方形的宽可以直接算出来 $\lceil \frac{a}{x}\rceil$，这里的 $a$ 指先确定的长方形的长，因为这一题的范围太大我们可以用 $\frac{a+x-1}{x}$ 来进行上去整操作。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool f2(int x,int y,int a,int b) {
	for (int i=1;i<=2;i++){
		int len=(a+x-1)/x;
		if(x*(y-len)>=b) {
			return 1;
		}
		swap(x,y);
	}
	return 0;
}
bool f3(int x, int y,int a,int b,int c){
	for(int i=1;i<=2;i++){
		for(int j=1;j<=3;j++){
			int len=(a+x-1)/x;
			if(len<y&&f2(x,y-len,b,c))return 1;
			swap(a,b);
			swap(b,c);
		}
		swap(x,y);
	}
	return 0;
}
signed main(){
	int x,y,a,b,c;
	cin>>x>>y>>a>>b>>c;
	if(f3(x,y,a,b,c))cout<<"Yes\n";
	else cout<<"No\n";
	return 0;
}
```

---

## 作者：mickey2021 (赞：1)

## 题目大意

给定 $A,B,C$，问能否通过摆放平面中三个面积分别**至少**为 $A,B,C$ 的小矩形使得它们能被一个 $X \times  Y$ 的矩形完全包含。

## 思路

因为总共只有3个长方形，可以发现摆放方式只有4种：

- 三个长方形均横着放。
- 三个长方形均竖着放。
- 两个长方形横着放，一个长方形竖着放。
- 两个长方形竖着放，一个长方形横着放。

只需依次判断4种情况是否可行即可。

## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int check(int a,int b)//当面积至少为a，一条边长为b时另外一条边的长度 。
{
	return (a+b-1)/b;
}
signed main()
{
	int x,y,a,b,c;
	cin>>x>>y>>a>>b>>c;
	bool flag=0;
	if(check(a,x)+check(b,x)+check(c,x)<=y)
	{
		flag|=1;
	}
	if(x-check(a,y)>0&&check(b,x-check(a,y))+check(c,x-check(a,y))<=y)
	{
		flag|=1;
	}
	swap(a,b);
	if(x-check(a,y)>0&&check(b,x-check(a,y))+check(c,x-check(a,y))<=y)
	{
		flag|=1;
	}
	swap(a,c);
	if(x-check(a,y)>0&&check(b,x-check(a,y))+check(c,x-check(a,y))<=y)
	{
		flag|=1;
	}
	swap(x,y);//调换x，y，相当于调换了横，竖。
	if(check(a,x)+check(b,x)+check(c,x)<=y)
	{
		flag|=1;
	}
	if(x-check(a,y)>0&&check(b,x-check(a,y))+check(c,x-check(a,y))<=y)
	{
		flag|=1;
	}
	swap(a,b);
	if(x-check(a,y)>0&&check(b,x-check(a,y))+check(c,x-check(a,y))<=y)
	{
		flag|=1;
	}
	swap(a,c);
	if(x-check(a,y)>0&&check(b,x-check(a,y))+check(c,x-check(a,y))<=y)
	{
		flag|=1;
	}
	if(flag)cout<<"Yes\n";
	else cout<<"No\n"; 
	return 0;
}

```

---

## 作者：skyskyCCC (赞：1)

## 前言。
一道比较基础但是很有意思的思维题。

题目大意：摆放三个面积至少分别为三个常量的小矩形使得它们能够在一个 $x\times y$ 的矩形中被完全覆盖。
## 分析。
简单地分析一下，我们可以如何摆放，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/h1cjzu3d.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

分析上图，我们发现其实其中有一些情况是重复的。那么我们就只剩下四种方案（第三行的分割和第二行是等价的）：
- 三个矩形都竖着放。
- 三个矩形都横着放。
- 三个矩形中两个横着放，一个贴着那两个矩形竖着放。
- 三个矩形中两个竖着放，一个贴着那两个矩形横着放。

注意到，前面的两个分法无法就是旋转了一下，其实可以归到同一种情况中去。那么一共可能否分割方式只有 $3$ 种，所以直接暴力枚举即可。剩下的小细节无非就是定宽定长，计算这些矩形的长和宽然后判断。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
long long x,y,a,b,c;
//bool flag;
long long dis(long long fir,long long sed){
	return (fir+sed-1)/sed;
}
bool pd(long long x,long long y,long long a,long long b){
    long long sum2=dis(a,y)+dis(b,y);
    return sum2<=x;
}
bool cheak(long long x,long long y,long long a,long long b,long long c){
    long long sum=dis(a,y);
    //计算三个拼起来的宽，记得取整。 
    if(sum>=x){
	    return false;
	}
    x-=sum;
    return pd(x,y,b,c) or pd(y,x,b,c);  
}
int main(){
    cin>>x>>y>>a>>b>>c;
    for (int i=0;i<2;i++){
        for (int j=0;j<3;j++){
            if(cheak(x,y,a,b,c)){
             // flag=1;
			    cout<<"Yes\n";
            //  break;
                return 0;
            }
            swap(a,b);
			swap(b,c);
			//这里相当于改变顺序即摆放方式。 
        }
        swap(x,y);
        //记得这个x乘y的矩形的位置不确定。 
    }
   // if(flag==1){
   // 	cout<<"Yes\n";
//	}
   // else cout<<"No\n";
    cout<<"No\n";
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：2020luke (赞：0)

# [[ABC223E] Placing Rectangles](https://www.luogu.com.cn/problem/AT_abc223_e) 题解

## 思路解析

根据题目可知，其实三个长方形无非只有以下两种摆放方式。

![](https://cdn.luogu.com.cn/upload/image_hosting/vv6hjezo.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/larz2hvj.png)

若大长方形长为 $y$，宽为 $x$，则我们对于第一种情况就固定住宽，判断能否使长度小于等于长；对于第二种情况同样固定住宽，此时 A 长方形右边空间的长就确定了，就只需要判断 B,C 的宽之和能否小于大长方形的宽即可。

注意大长方形的长宽可以互换，小长方形的顺序可以互换。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define double long double
ll x, y, a, b, c;
bool check() {
	ll ax = ceil((double)a / x), bx = ceil((double)b / x), cx = ceil((double)c / x);
	if(ax + bx + cx <= y) return true;
	ll yy = y - ax;
	if(yy <= 0) return false;
	ll by = ceil((double)b / yy), cy = ceil((double)c / yy);
	if(by + cy <= x) return true;
	return false;
}
int main() {
	cin >> x >> y >> a >> b >> c;
	bool ans = check();
	swap(a, b); ans |= check();
	swap(a, c); ans |= check();
	
	swap(x, y); ans |= check();
	swap(a, b); ans |= check();
	swap(a, c); ans |= check();
	if(ans) puts("Yes");
	else puts("No");
	return 0;
}
```

---


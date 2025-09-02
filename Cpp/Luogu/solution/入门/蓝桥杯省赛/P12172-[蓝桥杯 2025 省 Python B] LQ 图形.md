# [蓝桥杯 2025 省 Python B] LQ 图形

## 题目背景

本站蓝桥杯 2025 省赛测试数据均为洛谷自造，与官方数据可能存在差异，仅供学习参考。

## 题目描述

小蓝要为蓝桥画一个图形。由于小蓝的画图能力有限，他准备用大写字母 Q 画一个 L 形状的字符画。他希望 L 的粗细正好是 $w$ 个字符宽，竖的笔划伸出 $h$ 高（因此图形总共 $h + w$ 高），横的笔划伸出 $v$ 宽（因此图形总共 $v + w$ 宽），要求每个笔划方方正正不能有多余内容。

例如，当 $w = 2, h = 3, v = 4$ 时，图形如下所示：

```
QQ
QQ
QQ
QQQQQQ
QQQQQQ
```

给定 $w, h, v$，请帮助小蓝画出这个图形。

## 说明/提示

### 评测用例规模与约定

对于 $30\%$ 的评测用例，$w = 1$，$1 \leq h, v \leq 20$；

对于 $60\%$ 的评测用例，$1 \leq w, h, v \leq 20$；

对于所有评测用例，$1 \leq w, h, v \leq 100$。

## 样例 #1

### 输入

```
3 4 5```

### 输出

```
QQQ
QQQ
QQQ
QQQ
QQQQQQQQ
QQQQQQQQ
QQQQQQQQ```

# 题解

## 作者：thr31825 (赞：2)

### P12172 题解

#### 思路

非常简单的模拟题。

根据题意，可以将图形分为两部分进行打印，一部分为上方的矩形，一部分为下方的矩形（~~废话~~）。

其中上方的矩形长宽分别为 $w,h$，下方的矩形长宽为 $v+w,w$。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int u,h,v;
int main()
{
	scanf("%d%d%d",&u,&h,&v);//读入
	for(int i=1;i<=h;i++){//注意外层控制列，内层控制行
		for(int j=1;j<=u;j++){
			cout<<"Q";
		}
		cout<<endl;//每打完一行就换行
	 } 
	for(int i=1;i<=u;i++){
		for(int j=1;j<=v+u;j++){
			cout<<"Q";
		}
		cout<<endl;
	}
	return 0;
}
			
```

蒟蒻的第一篇题解，求审核大大通过 qaq。

---

## 作者：CCY20130127 (赞：2)

## 题目大意：
[题目传送门](https://www.luogu.com.cn/problem/P12172)

## 题目思路：
这道题应该学过循环语句的人都会。

![](https://cdn.luogu.com.cn/upload/image_hosting/zth3l3t7.png)
本题分两个矩阵，分别为有 $h$ 行 $w$ 列的矩阵和一个有 $w$ 行 $w+v$ 列的矩阵，看不懂的建议再看一看原题。

说完不就好做多了，不要忘记换行哟。

## 正解：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//开long long 防止见祖宗
int a,b,c;//定义
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);//防止TLE
	cin>>a>>b>>c;//输入
	for(int i=1;i<=b;i++){//一共有b行
		for(int j=1;j<=a;j++){//一共有a列
			cout<<"Q";//输出Q
		}
		cout<<endl;//换行
	}
	for(int i=1;i<=a;i++){//一共有a行
		for(int j=1;j<=a+c;j++){//一共有a+c列
			cout<<"Q";//输出Q
		}
		cout<<endl;//换行
	}
	return 0;//结束
}
```

---

## 作者：Eric1030 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P12172)

## 思路讲解
这道题是一道非常简单的模拟题（看标签知道的）。我们发现这个图形是由一个长为 $h$，宽为 $w$ 的长方形和一个长为 $w+v$，宽为 $w$ 的长方形组成的，所以我们只要输出两个我描述的长方形即可，但要注意的是第一个长方形是竖着放的，而第二个长方形是横着放的。

## [AC](https://www.luogu.com.cn/record/213748124) 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int h,v,w;
int main()
{
    cin>>w>>h>>v;//输入数据
    for(int i=1;i<=h;i++)//第一个长方形的长
    {
        for(int j=1;j<=w;j++)//第一个长方形的宽
        {
            cout<<"Q";//输出字符
        }
        cout<<endl;//记得换行
    }
    for(int i=1;i<=w;i++)//第二个长方形的宽
    {
        for(int j=1;j<=w+v;j++)//第二个长方形的长
        {
            cout<<"Q";
        }
        cout<<endl;
    }
    return 0;//结束！
}
```

---

## 作者：jiayunli (赞：1)

五年级蒟蒻题解，大佬见谅。

~~小蓝画画真菜~~ ~~
## 直接看题
小蓝希望 $L$ 的粗细正好是 $w$ 个字符宽，竖的笔划伸出 $h$ 高所以：

```cpp
for(ll i=1;i<=h;i++){
	for(ll j=1;j<=w;j++){
	cout<<"Q";
}
	cout<<endl;
}
```
小蓝希望横的笔划伸出 $v$ 宽（因此图形总共 $v+w$ 宽），要求每个笔划方方正正不能有多余内容所以：

```cpp
for(ll i=1;i<=w;i++){
	for(ll j=1;j<=w+v;j++){
	cout<<"Q";
}
	cout<<endl;
}
```
## 上代码

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
using ll=long long;
ll w,h,v;//w:L 的粗细宽  h:竖的笔划伸出的高  v:横的笔划伸出的宽
int main(){
	ios::sync_with_stdio(false);//速读
	cin.tie(0);cout.tie(0);
	cin>>w>>h>>v;
	for(ll i=1;i<=h;i++){//打印 L 的竖的笔
		for(ll j=1;j<=w;j++){
			cout<<"Q";
		}
		cout<<endl;
	}
	for(ll i=1;i<=w;i++){//打印 L 的横的笔
		for(ll j=1;j<=w+v;j++){
			cout<<"Q";
		}
		cout<<endl;
	}
	return 0;//完美收尾
}
```

---

## 作者：Zskioaert1106 (赞：1)

题目传送门：[P12172 [蓝桥杯 2025 省 Python B] LQ 图形](https://www.luogu.com.cn/problem/P12172)

### 做题过程

按照题意模拟即可。但是题意有点含混。

我们可以把图形分成上下两个长方形。上面的长方形高为 $h$，长为 $w$；下面的长方形高为 $w$，宽为 $v+w$。

就是这样。

### C++

```cpp
#include<bits/stdc++.h>
using namespace std;
int w,h,v;
int main(){
    cin>>w>>h>>v;
    for(int i=0;i<h;putchar('\n'),i++)
        for(int j=0;j<w;j++)
            putchar('Q');
    for(int i=0;i<w;putchar('\n'),i++)
        for(int j=0;j<v+w;j++)
            putchar('Q');
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/213559082)。

### Python

要更简短一些。

```python
w, h, v = map(int, input().split())
for i in range(h):
    print('Q' * w)
for i in range(w):
    print('Q' * (w + v))
```

[AC 记录](https://www.luogu.com.cn/record/213560251)。

---

## 作者：AFO_Lzx (赞：1)

### $\texttt{Solution}$

实际上输出的图形可以分为一个竖着的 $h \times w$ 的矩形和一个横着的 $w \times(w+v)$ 的矩形，我们把这两个矩形的所有点标记成 $\texttt{Q}$，然后其余的都是空格即可。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn = 1e3 + 5;
char a[maxn][maxn];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int w, h, v;
	cin >> w >> h >> v;
	
	for (int i = 1; i <= w; i++) {
		for (int j = 1; j <= h; j++) {
			a[i][j] = 'Q';
		}
	}
	
	for (int i = h + 1; i <= w + h; i++) {
		for (int j = 1; j <= w + v; j++) {
			a[i][j] = 'Q';
		}
	}
	
	for (int i = 1; i <= w + h; i++) {
		for (int j = 1; j <= w + v; j++) {
			if (a[i][j] == 0) cout << ' ';
			else cout << 'Q';
		}
		cout << '\n';
	}
	
	return 0;
}
```

---

## 作者：wen_hao_shi_wo (赞：1)

## 前置

[AC 记录](https://www.luogu.com.cn/record/213583702)

[题目传送门](https://www.luogu.com.cn/problem/P12172)

## 题目思路

题面很直白，就是小蓝想用 Q 画一个 L，高为 $h+w$，宽为 $v+w$，这题可以分为两个部分，先输出 $h$ 行，$w$ 列的 Q，在输出 $w$ 行，$w+v$ 列的 Q，就完成了。

思路到此为止，建议大家先自己尝试，有不懂的再看一下代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define code return
#define by 0
#define wen_hao_shi_wo ;
using namespace std;
int w,h,v;
void accelerate(){
	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}
int main(){
    accelerate();//提高运行速度
    cin>>w>>h>>v;
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            cout<<"Q";
        }
        cout<<"\n";
    }//第一部分
    for(int i=1;i<=w;i++){
        for(int j=1;j<=w+v;j++){
            cout<<"Q";
        }
        cout<<"\n";
    }//第二部分
	code by wen_hao_shi_wo
}
```

---

## 作者：封禁用户 (赞：0)

## 题目大意
[题目不传送门](https://www.luogu.com.cn/problem/P12172)
## 题目分析
画一个 L 形状的字符画。L 的粗细正好是 $w$ 个字符宽，竖的笔划伸出 $h$ 高（因此图形总共 $h + w$ 高），横的笔划伸出 $v$ 宽（因此图形总共 $v + w$ 宽）。

直接按照题目的意思去做就能 AC。
## 题目代码（不要复制）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int w,h,v;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin>>w>>h>>v;
	for(int i=1;i<h;i++){
		for(int j=1;j<w;j++)cout<<"Q";
		cout<<'\n';
	}
	for(int i=1;i<w;i++){
		for(int j=1;j<(w+v);j++)cout<<"Q";
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：yangdezuo (赞：0)

## 解析

### 题意
输出：前 $h$ 行，每行 $w$ 个大写字母 Q，后 $w$ 行，每行 $w + v$ 个大写字母 Q。

### 提示
作为一道 python 题，$w$、$h$、$v$ 是一行输入，普通的输入：
```python
w=int(input())
h=int(input())
v=int(input())
```
只能输入换行的数据，所以我们需要更高级的输入方式，比如：
```python
w,h,v=map(int,input().split())
```
就能解决这一问题。

## 参考代码

```python
w,h,v=map(int,input().split())
for x in range(h):
    s=""
    for i in range(w):
        s+="Q"
    print(s)
for x in range(w):
    s=""
    for i in range(w+v):
        s+="Q"
    print(s)
```

---

## 作者：maomitgd (赞：0)

这题 py 签到题，还算基础，可以循环逐个字符输出，但我选择加在一起循环输出字符串，话不多说，代码如下

Python 代码：


```python
q=input().strip()
w,h,v=[eval(x) for x in q.split(" ")]
b=a=""
for i in range(w):
    b+="Q"
for i in range(w+v):
    a+="Q"
for i in range(h):
    print(b)
for i in range(w):
    print(a)
if "__name__"=="__main__":
    main()

```

CPP 代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	ios::sync_with_stdio(false);
	int a,b,c;
	cin>>a>>b>>c;
	string x="",y="";
	for (int i=0;i<a;i++){
		x+="Q";
	}
	for (int i=0;i<a+c;i++){
		y+="Q";
	}
	for(int i=0;i<b;i++)cout<<x<<endl;
	for(int i=0;i<a;i++)cout<<y<<endl;
	return 0;
}
```

---

## 作者：3_14 (赞：0)

[**题目传送门**](https://www.luogu.com.cn/problem/P12172)

# 思路

竖笔划绘制：采用双重循环结构来绘制竖笔划。外层循环控制行数，由于竖笔划高度为 $h$，所以外层循环执行 $h$ 次。内层循环控制每行输出的字符数，因为笔划宽度为 $w$，所以内层循环执行 $w$ 次。在内层循环中，每次输出一个大写字母 Q。

横笔划绘制：同样使用双重循环来绘制横笔划。外层循环控制行数，由于横笔划的高度实际上就是其宽度 $w$（因为要求方方正正），所以外层循环执行 $w$ 次。内层循环控制每行输出的字符数，横笔划的总宽度为 $v + w$，所以内层循环执行 $v + w$ 次。每次内层循环输出一个大写字母 Q。

每一行输出后，注意换行。

# 代码

```cpp
#include<bits/stdc++.h>
#define Freopen(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
#define lcm(x,y) x/__gcd(x,y)*y
#define lb(x) (x&-x)
#define str to_string
using namespace std;
using ll=long long;
const double EPS=1e-6,PAI=acos(-1.0);
const int MAX=1e3+5,mod=1e9+7,MOD=998244353;
int w,h,v;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>w>>h>>v;
    for(int i=0;i<h;i++){// 绘制竖的笔划
        for(int j=0;j<w;j++)cout<<'Q';
        cout<<'\n';
    }
    for(int i=0;i<w;i++){// 绘制横的笔划
        for(int j=0;j<v+w;j++)cout<<'Q';
        cout<<'\n';
    }
    return 0;
}
```

[**AC 记录**](https://www.luogu.com.cn/record/213658538)

---

## 作者：Vct14 (赞：0)

一定可以把图形分割为一个 $h\times w$ 的矩形和一个 $w\times(w+v)$ 的矩形。分别输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

void draw(int x,int y){
	for(int i=1; i<=x; i++){
		for(int j=1; j<=y; j++) cout<<"Q";
		cout<<"\n";
	} 
}

int main(){
	int w,h,v;cin>>w>>h>>v;
	draw(h,w);draw(w,w+v);
	return 0;
}
```

---


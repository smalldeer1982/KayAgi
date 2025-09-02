# 【MX-J2-T0】Turtle and Equations

## 题目背景

原题链接：<https://oier.team/problems/J2A>。

## 题目描述

给你四个正整数 $a, b, c, d$。

现在你有一条算式 $(a\ \Box\ b)\ \Box\ c$。你需要判断能否在两个方框内分别填入三种运算符 $+, -, \times$ 之一（运算符可以重复使用），使得算式运算的结果等于 $d$。

## 说明/提示

#### 【样例解释 #1】

因为 $(1 + 1) + 1 = 3$，可以在第一个方框内填入 $+$，第二个方框内填入 $+$。

#### 【样例解释 #2】

因为 $(5 - 2) \times 9 = 27$，可以在第一个方框内填入 $-$，第二个方框内填入 $\times$。

#### 【样例解释 #3】

无论填什么运算符都不能使得算式的结果为 $514$。

#### 【数据范围】

对于所有数据，满足 $1 \le a, b, c \le 10$，$1 \le d \le 1000$。

## 样例 #1

### 输入

```
1 1 1 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5 2 9 27```

### 输出

```
Yes```

## 样例 #3

### 输入

```
1 1 4 514```

### 输出

```
No```

# 题解

## 作者：Little_x_starTYJ (赞：6)

### 解题思路
一共有 $3\times 3 = 9$ 种情况。

我们进行分类讨论。

- $(a\ \Box\ b) + c = d$，那么我们将 $+,-,\times$ 都放到方框里面去试试，如果等式成立，那么打印 `Yes`。

- $(a\ \Box\ b) - c = d$，那么我们将 $+,-,\times$ 都放到方框里面去试试，如果等式成立，那么打印 `Yes`。
 
- $(a\ \Box\ b) \times c = d$，那么我们将 $+,-,\times$ 都放到方框里面去试试，如果等式成立，那么打印 `Yes`。

如果以上情况等式都不成立，我们打印 `No`。

CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	if ((a + b) + c == d || (a - b) + c == d || a * b + c == d
	    || (a + b) - c == d || (a - b) - c == d || a * b - c == d
	    || (a + b) * c == d || (a - b) * c == d || a * b * c == d) {
		cout << "Yes";
	} else
		cout << "No";
	return 0;
}
```

---

## 作者：gbw555 (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P10839)
### 思路
由于只有 $2$ 个方框，每个方框最多只有 $3$ 种情况，一共只有 $3^2=9$ 种情况，所以考虑打表，枚举每种情况。
### Code

```cpp
#include<bits/stdc++.h> //万能头文件
using namespace std;
int a,b,c,d;            //声明变量   
int main(){             //主函数
	cin>>a>>b>>c>>d;      //输入
	if((a+b)*c==d){       //开始打表，枚举每种情况
		cout<<"Yes";
		return 0;
	}else if((a+b)-c==d){
		cout<<"Yes";
		return 0;
	}else if((a+b)+c==d){
		cout<<"Yes";
		return 0;
	}else if((a*b)*c==d){
		cout<<"Yes";
		return 0;
	}else if((a*b)+c==d){
		cout<<"Yes";
		return 0;
	}else if((a*b)-c==d){
		cout<<"Yes";
		return 0;
	}else if((a-b)*c==d){
		cout<<"Yes";
		return 0;
	}else if((a-b)-c==d){
		cout<<"Yes";
		return 0;
	}else if((a-b)+c==d){
		cout<<"Yes";
		return 0;
	}
	cout<<"No";  //如果每种情况都不成立，就输出 No
	return 0;
}
```

---

## 作者：hhztl (赞：3)

一道非常水的题。

考虑使用递归算法。对于每一个数，均可以对原来的数加、减、乘操作。直接搜索每个状态即可。

## 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5],ans;
void dfs(int k,int s){
	if(k>3){//边界条件
		if(s==ans){//若符合要求
			cout<<"Yes";//输出Yes
			exit(0);//直接结束程序
		}return;//返回上一层函数
	}dfs(k+1,s+a[k]);//加
	dfs(k+1,s-a[k]);//减
	dfs(k+1,s*a[k]);//乘
}int main(){
	for(int i=1;i<4;i++)cin>>a[i];
	cin>>ans;
	dfs(2,a[1]);//k要从2开始，因为已经预先算出k为1时s的值（即a[1]）
	cout<<"No";//若始终不满足要求，输出No
}
```

---

## 作者：残阳如血 (赞：2)

### $\textbf{Description}$

给你四个正整数 $a, b, c, d$。

现在你有一条算式 $(a\ \Box\ b)\ \Box\ c$。你需要判断能否在两个方框内分别填入三种运算符 $+, -, \times$ 之一（运算符可以重复使用），使得算式运算的结果等于 $d$。

### $\textbf{Solution}$

每个方框有 $3$​ 种可能性，所以整个方案数总共有 $3^2=9$​ 种，所以可以枚举每一种情况，然后判断即可。

时间复杂度 $O(1)$。

### $\textbf{Code}$

```cpp
#include <bits/stdc++.h>

int a, b, c, d;

int main() {
  std::cin >> a >> b >> c >> d;
  if ((a + b) + c == d || 
      (a + b) - c == d ||
      (a + b) * c == d ||
      (a - b) + c == d ||
      (a - b) - c == d ||
      (a - b) * c == d ||
      (a * b) + c == d ||
      (a * b) - c == d ||
      (a * b) * c == d) puts("Yes"); // 枚举 9 种情况
  else puts("No");
  return 0;
}
```

---

## 作者：__Kyw666__ (赞：2)

## 题意解释
给算式 $(a\ \Box\ b)\ \Box\ c$ 的方格里填上运算符 $+$、$-$ 或 $\times$，符号可以重复使用。问是否有算式结果得出为 $d$。

## 思路分析
简单模拟 $+$ 枚举。  
算式中共有两个方格，也就是说有两处可任选符号。且有三种可选符号，因此很容易得出算式的不同符号组合方式，共 $3 ^ 2$ 种。  
这么少的组合方式，直接暴力枚举，~~太水了~~。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;

int a,b,c,d;
int main()
{
	cin>>a>>b>>c>>d;
	if(a+b+c==d)
	{
		cout<<"Yes";
		return 0;
	}
	if(a+b-c==d)
	{
		cout<<"Yes";
		return 0;
	}
	if((a+b)*c==d)
	{
		cout<<"Yes";
		return 0;
	}
	if(a-b+c==d)
	{
		cout<<"Yes";
		return 0;
	}
	if(a-b-c==d)
	{
		cout<<"Yes";
		return 0;
	}
	if((a-b)*c==d)
	{
		cout<<"Yes";
		return 0;
	}
	if(a*b+c==d)
	{
		cout<<"Yes";
		return 0;
	}
	if(a*b-c==d)
	{
		cout<<"Yes";
		return 0;
	}
	if(a*b*c==d)
	{
		cout<<"Yes";
		return 0;
	}
	cout<<"No";
	return 0;
 } 
```
简单明了，相信大家都会。  
2024.09.04
感谢热心谷民 [pipilong2024](https://www.luogu.com.cn/user/1258210) 提出错误。  

结束！

---

## 作者：Brain_Huger (赞：1)

upd：2024.9.4 附上代码

## 题目大意

给你 $a,b,c,d$，问能否构造出 $(a\ \substack{+\\-\\\times}\ b)\ \substack{+\\-\\\times}\ c=d$。

## 解题思路

按照题目模拟即可，枚举每个运算符能否凑出 $d$。

时间复杂度 $O(1)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
int a,b,c,d;
int sol(int x,int y,int id){
	switch(id){
		case 1:return x+y;
		case 2:return x-y;
		case 3:return x*y;
		default:while(1)puts("IAKIOI");
	}
	exit(-1);
}
signed main(){
	scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
	for(int i=1;i<=3;i++)for(int j=1;j<=3;j++)if(sol(sol(a,b,i),c,j)==d)return!puts("Yes");
	puts("No");
	return 0;
}

```

---

## 作者：David_yang (赞：1)

[传送门](https://www.luogu.com.cn/problem/P10839)

我的第十四篇题解。

## 题目大意：

题目比较简洁，就不概括了。

## 算法或数据结构：

模拟、枚举。

## 解析：

这是一道红题，比较简单。我就简单讲几句。直接一个 if 判断，小括号里写 $9$ 个判断句，从 $a+b+c$ 一直写到 $a\times b\times c$，每条判断是否等于 $d$，中间用逻辑或连接起来就行了。

就这么简单，我放代码了。注意该加括号时要加括号。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,sum;
int main()
{
	scanf("%d%d%d%d",&a,&b,&c,&d);
	if(a+b+c==d || a+b-c==d || (a+b)*c==d || a-b+c==d || a-b-c==d || (a-b)*c==d || a*b+c==d || a*b-c==d || a*b*c==d)           //有点长，请原谅。注意加括号
	{
		printf("Yes");
	}
	else
	{
		printf("No");
	}
	return 0;
}
```

注：代码已 AC 过，请放心食用。

最后，浏览过看过也要赞过！

---

## 作者：cff_0102 (赞：1)

可能性不多，直接手动枚举。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c,d;cin>>a>>b>>c>>d;
	if(a+b+c==d||a+b-c==d||(a+b)*c==d||a-b+c==d||a-b-c==d||(a-b)*c==d||a*b+c==d||a*b-c==d||a*b*c==d)cout<<"Yes";
	else cout<<"No";
	return 0;
}
```

AC 记录：<https://www.luogu.com.cn/record/175730376>。

---

## 作者：sbh2012 (赞：1)

## 分析：
只需要把 $+, -, \times$ 这三种符号的摆放顺序枚举一下即可，共 $3 \times 3 = 9$ 种。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  int a,b,c,d;
  cin>>a>>b>>c>>d;
  if((a+b)+c==d||(a+b)-c==d||(a+b)*c==d||(a-b)+c==d||(a-b)-c==d||(a-b)*c==d||(a*b)+c==d||(a*b)-c==d||(a*b)*c==d){//9种情况
    cout<<"Yes";
  }else{
    cout<<"No";
  }
  return 0;
}
```

---

## 作者：Aoharu_shiroko (赞：0)

# P10839 解题报告

## 0x00 前言

~~这题好水。~~

## 0x01 题目大意

讲的这么明白，就没有必要解释了。

## 0x02 解析

我们先分别假设以下符号用数字表示是什么：

+ $1$ 表示 $+$。

+ $2$ 表示 $-$。

+ $3$ 表示 $\times$。

两层循环，分别枚举这两个位置的符号，然后统计结果，最后判断它是否与 $d$ 相等，最后输出答案就可以了。

## 0x03 ac code

```cpp
#include <bits/stdc++.h>
using namespace std;

int a,b,c,d;
int ans;

int main()
{
	cin >> a >> b >> c >> d;
	for (int i=1;i<=3;i++)
	{
		ans=0;
		for (int j=1;j<=3;j++)
		{
			if (i==1)
			{
				ans=a+b;
			}
			if (i==2) ans=a-b;
			if (i==3) ans=a*b;
			if (j==1) ans+=c;
			if (j==2) ans-=c;
			if (j==3) ans*=c;
			if (ans==d)
			{
				cout << "Yes" << endl;
				return 0;
			}
		}
	}
	cout << "No" << endl;
	return 0;
}
```

---

## 作者：Tracy_Loght (赞：0)

简单入门题。

## 题目分析：

给定一个算式 $(a\ \Box\ b)\ \Box\ c$。判断能否在两个方框内分别填入三种运算符 $+, -, \times$ 之一，使得算式运算的结果等于 $d$。

## 思路：

首先，我们注意到方框**只有**两个，而且除方框外的一切都无法改变。方框内也**只能**填三个符号，于是就可以直接判断。

判断什么，当然是填哪些符号可以使算式的结果等于 $d$。

总共就有 $3^2$ 种情况，由两个方框，每个方框可以填三个符号得来。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d;
int A,B;//A表示（a 与 b 的答案），B 为最终的结果 
int main(){
	cin>>a>>b>>c>>d;
	for(int i=1;i<=3;i++){//1=+，2=-，3=* 
		for(int j=1;j<=3;j++){//1=+，2=-，3=* 
			if(i==1) A=a+b;//判断当前用什么符号 
			if(i==2) A=a-b;
			if(i==3) A=a*b;
			if(j==1) B=A+c;
			if(j==2) B=A-c;
			if(j==3) B=A*c;
			if(B==d) {cout<<"Yes";return 0;}
		}
	} 
	cout<<"No";//因为前面如果有 Yes 直接结束了，所以可以直接输出 
	return 0;
}

```

---

## 作者：gzwm (赞：0)

看标签可以知道，本题为枚举，我们只需要枚举两个符号即可

第一次发题解可能不会太好看，请谅解。

上代码，应该比较好理解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c,d; 
	cin>>a>>b>>c>>d;//输入 
	for(int i=1;i<=3;i++){//枚举3种运算 
		for(int j=1;j<=3;j++){
			if(i==1){//有点多，但可以ctrl+c,ctrl+v。  
				if(j==1){
					if(a+b+c==d){
						cout<<"Yes";
						return 0;//记得结束 
					}
				}
				if(j==2){
					if(a+b-c==d){
						cout<<"Yes";
						return 0;
					}
				}
				if(j==3){
					if((a+b)*c==d){
						cout<<"Yes";
						return 0;
					}
				}
			}
			if(i==2){
				if(j==1){
					if(a-b+c==d){
						cout<<"Yes";
						return 0;
					}
				}
				if(j==2){
					if(a-b-c==d){
						cout<<"Yes";
						return 0;
					}
				}
				if(j==3){
					if((a-b)*c==d){
						cout<<"Yes";
						return 0;
					}
				}
			}
			if(i==3){
				if(j==1){
					if(a*b+c==d){
						cout<<"Yes";
						return 0;
					}
				}
				if(j==2){
					if(a*b-c==d){
						cout<<"Yes";
						return 0;
					}
				}
				if(j==3){
					if(a*b*c==d){
						cout<<"Yes";
						return 0;
					}
				}
			}
		} 
	}
	cout<<"No";//如果到这里还没结束，则输出No。 
	return 0;
}

```

---


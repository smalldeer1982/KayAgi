# New Year Garland

## 题目描述

### 题意简述

给定 $r$ 个字符 R，$g$ 个字符 G，$b$ 个字符 B，问是否存在一种方案，使得所有字符排列组成的字符串不存在两个相邻且相同的字符。

## 样例 #1

### 输入

```
3
3 3 3
1 10 2
2 1 1
```

### 输出

```
Yes
No
Yes
```

# 题解

## 作者：柳下惠 (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1279A)。

根据贪心的思想，我们肯定先会把最多的字符消耗完，也就是说我们只需判断最多字符的数量和剩下两种字符的数量就好了。

如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/l7b5zfcx.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这里给出了反例（$c$ 代表最多的字符，$a$ 和 $b$ 分别代表剩下两种字符），我们能得结论：当 $c>a+b+1$ 时，无解。

### code:

```cpp
#include<bits/stdc++.h>
#define I using
#define her std
#define very_much ;
#define ll long long
#define Love namespace
#define INF 0x7fffffff
I Love her very_much
int T;
int a[4];
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
void print(int x)
{
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
int main()
{
	T=read();
	while(T--)
	{
		a[1]=read(),a[2]=read(),a[3]=read();
		sort(a+1,a+4);//排序后进行判断
		if(a[1]+a[2]+1<a[3]) printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}
```

---

## 作者：Ryo_Yamada (赞：2)

看到这题唯一的一篇题解和我的方法不一样，来写个题解。

我的思路是，将最长的排一排，剩下的往空里插入。比如：$rrrr$, $g$, $bb$ -> $r-r-r-r$ -> $rgrbrbr$。

如果够的话输出$Yes$，否则输出$No$。

于是这题变得很简单。

$Code:$
```cpp
#include <iostream>
typedef long long LL;//不用LL也行
using namespace std;
bool ans(LL r, LL g, LL b) {
    if(r - 1 > g + b || g - 1 > r + b || b - 1 > g + r) return 0;//如果剩下两种不够返回false
    return 1;//返回true
}
int main() {
    ios::sync_with_stdio(0);
    LL r, g, b;
    int t;
    cin >> t;
    for(int i=0; i<t; i++) {
        cin >> r >> g >> b;
        if(ans(r, g, b)) {
            cout << "Yes\n";
        }//调用函数判断
        else cout << "No\n";
    }
    return 0;
}
```


---

## 作者：yydfj (赞：1)

**这是本蒟蒻第二十三次写的题解，如有错误点请好心指出！**

## 问题简述

__这道题我们可以换另一种思路去看待它，就容易理解了：__

给你 $r$ 个字符 ```R```，$g$ 个字符 ```G```，$b$ 个字符 ```B```，将这些字符随意组合在一起变成一个字符串，问有没有一种可能使该字符串中没有两个相邻且相同的字符。

## 解法综述

我们假设 $r$ 最长，将 $r$ 个字符 ```R``` 组成字符串 $s$，则最优方案就是将 ```G``` 和 ```B``` 分别插入字符串 $s$ 中两个相邻且为 ```R``` 的字符中，多出来的 ```G``` 和 ```B``` 可以在字符串 $s$ 的末端交替插入。通过这些操作，我们发现如果插入字符串 $s$ 的字符个数不够，则不可能出现字符串 $s$ 中存在两个相邻且不相同的字符。

由此得出结论，假设 $r$ 最长，若 $r≤g+b+1$，则有字符串满足题意。

## 代码描述
```cpp
#include<queue>
#include<cstdio>
using namespace std;
priority_queue<int> q;//采用优先队列，自动将里面的数从大到小排序
inline int read()//快读
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){f=ch=='-'?-1:1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int T,r,g,b;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		q.push(read());
		q.push(read());
		q.push(read());
		r=q.top();q.pop();//假设r最大
		g=q.top();q.pop();
		b=q.top();q.pop();
		printf(r<=g+b+1?"Yes\n":"No\n");//得出结论
	}
	return 0;
}
```

---

## 作者：Sniper_jyb (赞：1)

个人认为题目简述已十分简洁明了，不必多说。
[题目传送门](https://www.luogu.com.cn/problem/CF1279A)

### 题目分析
题目要求给出三种字符，要使它们不存在两个相邻且相同的字符进行排列。

我们可以将其看成将两种字符插入相邻的第三种字符中，插满或还有剩余即为符合。

**显而易见的，最优的办法莫过于将其余两种数量较少的字符插入数量较多的第三者中。**

在最极端的情况下，其余两种字符会将第三者每两个相邻的字符之间的空当全部插满。

现在给定字符 $\texttt{"a"}$ 有 $a$ 个，字符 $\texttt{"b"}$ 有 $b$ 个，字符 $\texttt{"c"}$ 有 $c$ 个。

例：给出字符串 $\texttt{abacababaca}$.

* 此时，$b$ 与 $c$ 的数量和为 $a-1$。即，符合条件为 $a-1 \le b+c$，若不符合，则无解。

例：给出字符串 $\texttt{aaaaabbc}$.

* 此时，$a=5,b=2,c=3,a-1>b+c$，与条件不符。

#### 上代码——
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <bits/stdc++.h>
using namespace std;
int a,b,c,t;
int main(){
    cin>>t;
    while(t--){
        cin>>a>>b>>c;
        if(b>a&&b>c)swap(b,a);
        else if(c>a&&c>b)swap(a,c);//也可以用a[4]来存，用sort排序
        if(a-1>=b+c)cout<<"No"<<endl;
        else cout<<"Yes"<<endl;
    }
    return 0;
}
```





---

## 作者：Qerucy (赞：0)

考虑一个一个放字符到一个字符串中，最后一定要把所有字符放完才能满足要求。

先定义字符串 $a$。

那么可以把数量最多的一堆字符全部拿出来放在 $a$ 中，再把剩下的两堆字符一个个拿出来插在 $a$ 中每两个字符之间。如果剩下两堆没有足够的字符来完成这种操作，则不能满足题意。

如果排到最后剩下两堆中还有多余的字符，则剩下两堆剩下的字符交叉排列即可。

这道题没有要求我们输出操作后的字符串，所以我们只需要排到有没有足够的字符来完成操作。

只要数量最多的一堆字符间隙数量不大于剩下两堆字符的数量和便能够完成操作。

代码：

```cpp
#include<cstdio>
#include<algorithm>

using namespace std;

int t;
int r,g,b;

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&r,&g,&b);
		int maxn=max(r,max(g,b));//找字符数量最多的一堆字符
		if(maxn==r) puts(g+b+1>=r?"Yes":"No");//三目运算符压行
		else if(maxn==g) puts(r+b+1>=g?"Yes":"No");
		else if(maxn==b) puts(g+r+1>=b?"Yes":"No");
	}
	return 0;
}
```


---

## 作者：Little_Cart (赞：0)

## 1. 题意简述
多组询问，给定 $r$ 个字符 R，$g$ 个字符 G，$b$ 个字符 B，问是否存在一种方案，使得所有字符排列组成的字符串不存在两个相邻且相同的字符。能 输出“YES”（不输出引号），不能 输出“NO”（不输出引号）。

$1≤t≤100,1≤r,g,b≤10^9$
## 2. 题目简析
考点：数论

时间复杂度：$Θ(n)$

这道题较简单，但是要思考一会儿就可以做出来。

（分析开始）

我们先看一下能的方法：

4R 2G 2B（字符）
| R | G |R  | G | R | B | R |B|
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |

4R 2G 1B（字符）
| R | G | R | G | R | B | R |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |


不能的方法：

4R 1G 1B（字符）
| R | G | R | B | R | x(不能填) |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
5R 1G 1B（字符）
| R |G  |  R|  B|R  |x(不能填)  | R |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |


由此可以看出一个共性：

要分类讨论一下

总个数为奇数时：$r,g,b$中最大的$≤$剩下的两个+1 能

总个数为偶数时：$r,g,b$中最大的$≤$剩下的两个 能

（推理结束）

## 3. 主代码 和 简单讲解

```cpp
                int a[3];
                cin>>a[0]>>a[1]>>a[2];
		int zong;
		zong=a[0]+a[1]+a[2];
		sort(a,a+3);//sort排序，新手不建议选择
		if(zong%2==0){//判断奇偶
			if(a[2]<=a[1]+a[0]){//总个数为偶数时：r,g,b中最大的<=剩下的两个
				cout<<"Yes\n";//记得换行
			}
			else{
				cout<<"No\n";
			}
		}
		else{
			if(a[2]<=a[1]+a[0]+1){//总个数为奇数时：r,g,b中最大的<=剩下的两个+1
				cout<<"Yes\n";
			}
			else{
				cout<<"No\n";
			}
		}
```

## 4. 全代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t,a[3];
    cin>>t;
    int i;
    for(i=1;i<=t;i++){
        cin>>a[0]>>a[1]>>a[2];
        int zong;
        zong=a[0]+a[1]+a[2];
        sort(a,a+3);
        if(zong%2==0){
            if(a[2]<=a[1]+a[0]){
                cout<<"Yes\n";
            }
            else{
                cout<<"No\n";
            }
        }
        else{
            if(a[2]<=a[1]+a[0]+1){
                cout<<"Yes\n";
            }
            else{
                cout<<"No\n";
            }
        }
    }
    return 0;
}
```

## 5. 小结

本题解使用C++，欢迎大佬指正！

---


# Magic Stick

## 题目描述

Recently Petya walked in the forest and found a magic stick.

Since Petya really likes numbers, the first thing he learned was spells for changing numbers. So far, he knows only two spells that can be applied to a positive integer:

1. If the chosen number $ a $ is even, then the spell will turn it into $ \frac{3a}{2} $ ;
2. If the chosen number $ a $ is greater than one, then the spell will turn it into $ a-1 $ .

Note that if the number is even and greater than one, then Petya can choose which spell to apply.

Petya now has only one number $ x $ . He wants to know if his favorite number $ y $ can be obtained from $ x $ using the spells he knows. The spells can be used any number of times in any order. It is not required to use spells, Petya can leave $ x $ as it is.

## 样例 #1

### 输入

```
7
2 3
1 1
3 6
6 8
1 2
4 1
31235 6578234
```

### 输出

```
YES
YES
NO
YES
NO
YES
YES
```

# 题解

## 作者：B_Qu1e7 (赞：2)

注意到除$B=1$外，$A=1$的情况都是`NO`。

否则，除$B\leq 3$外，若最大能变到的偶数是$2$，则答案为`NO`。

否则为`YES`。

```
#include<cstdio>
#define R register
int T,X,Y;
template<class T>inline void read(R T &m)
{
	m=0;
	R char c=getchar();
	while(c<48||c>57)c=getchar();
	while(c>47&&c<58)m=(m<<3)+(m<<1)+(c&15),c=getchar();
}
int main()
{
	read(T);
	while(T--)
	{
		read(X),read(Y);
		if(X==Y)puts("YES");
		else if(X==1)puts("NO");
		else
		{
			X-=X&1;//令X为最大偶数
			if(X==2)
			{
				puts(Y>3?"NO":"YES");//X=2,Y≤3,YES
			}
			else
			{
				puts("YES");
			}
		}
	}
}
```

---

## 作者：Sya_Resory (赞：1)

upd after 3 years: 修改了 Latex 和部分叙述。

[题目链接](//codeforces.com/problemset/problem/1257/B)

## 题目描述

对于一个正整数 $a$，可以进行若干次下面两种操作：

1. 若 $a$ 是偶数，$a\mapsto\frac{3}{2}a$;

2. 若 $a>1$，$a\mapsto a - 1$。

给定 $x,y$，问能否通过以上操作将 $x$ 变成 $y$。

~~观测 CF 标签可得这是个数学题~~，考虑乱搞过去。

首先，由第二种操作，当 $x \ge y$ 时一定能成功。于是问题变为将 $x < y$ 转化为 $x\ge y$。

然后判断第一种操作。我们的目标是让 $x\ge y$，那么只有 $(\frac{3}{2})^kx$ 永远不会变大时，即 $a \le 3$ 时，才不能成功。特判即可。

--------------

以下是代码：

```cpp
// 1257B Magic Stick
#include <cstdio>

int t,x,y;
bool flag; // 判断可不可以

int main() {
	scanf("%d",&t);
	for(;t;t --) {
		flag = true; //初始化
		scanf("%d%d",&x,&y);
		if(x >= y) { // 如果仅凭借第二种操作可以的话
			puts("YES");
			continue;
		}
		if(x == 1) flag = false; // 特判 x = 1，什么都做不了
		if(x <= 3 && y > 3) flag = false; // 如果x <= 3，就永远达不到比 3 大的 y
       // 注意，如果不加判断 y > 3，会被 2 3 这组数据卡掉
		flag ? puts("YES") : puts("NO");
	}
	return 0;
}
```

---

## 作者：xiaofeng_and_xiaoyu (赞：0)

题目中的条件给得很明白了，一个是 $\times \frac{3}{2}$，另一个是 $-1$。

第一个相当于 $3$ 以上扩大，第二个相当于缩小。

也就是说，对 $3$ 以下特判即可。

给出代码：
```cpp
#include<iostream>
using namespace std;
int main(){
	int t;
	cin>>t;//多组数据
	while(t--){
		int a,b;
		cin>>a>>b;
		if(a==1&&b!=1){
			cout<<"NO"<<endl;
		}else if(a==3&&b>3){
			cout<<"NO"<<endl;//注意3和2还是可以互相转化的
		}else{
			cout<<"YES"<<endl;
		}
			
	} 
	
}
```


---

## 作者：Smg18 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1257B)。

看题，可以知道本题有两个修改条件，所以我们可以试试找规律。

他要保证做到 $x=y$，所以我们可以分类讨论。

- 当遇到 $x$ 判断是否等于 $y$，等于输出正确，直接满足条件。

- 当 $x=2$ 时，$y$ 可以等于一或二或三。

- 当 $x=3$ 时，同上，$y$ 可以等于一或二或三。

- 当 $x>3$ 时，如果 $x>y$ 就减下去。如果 $y>x$ 我们可以使 $x \times \frac{3}{2}$，此时 $x$ 必定大于原来的，然后大于 $y$ 就减，小于 $y$ 就减成偶数再变大。

所以代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define Test ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e5+10,NN=1e4+10;
ll n,m,k,len,T;
ll minn=INT_MAX,maxn=0;
char c[N];
ll arr[N];
bool dfs(int x,int y){
	if(x==y)return 1;
	if(x<y)return 0;
	if(x%2==0)dfs((3*x)/2,y);
	if(x>1)dfs(x-1,y);
}
int main(){
	cin>>T;
	while(T--){
		int x;int y;
		cin>>x>>y;
		if(x==y){cout<<"YES"<<endl;continue;}//等于
		if(x==1){cout<<"NO"<<endl;continue;}//1
		if(x<=3&&y<=3){cout<<"YES"<<endl;continue;}//小于3
		if(x<=3){cout<<"NO"<<endl;continue;}//大于
		cout<<"YES"<<endl;
	}

	return 0;
}



```


---

## 作者：chenyuchenghsefz (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1257B)

分类讨论：

- $x=1$ 时，$y$ 只能等于 $1$。

- $x=2$ 时，$y$ 可以等于 $2-1=1$ 或 $2$ 或 $2\times\frac{3}{2}=3$，到了 $3$ 只能回到 $2$。

- $x=3$ 时，$y$ 可以等于 $1$ 或 $2$ 或 $3$。

- $x\ge3$ 时，如果可以使得 $x\ge y$ 就可以一直 $-1$ 了。当 $x$ 为奇数时，$(x-1)\times\frac{3}{2}>x$。当 $x$ 为偶数时，$x\times\frac{3}{2}>x$。所以 $x$ 可以大于 $y$。

[AC 记录](https://www.luogu.com.cn/record/108917539)

# 代码

```cpp
#include <iostream>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int x,y;
		cin>>x>>y;
		if(x==1)
		{
			if(y==1)
			cout<<"YES\n";
			else
			cout<<"NO\n";
		}
		else if(x<=3)
		{
			if(y<=3)
			cout<<"YES\n";
			else
			cout<<"NO\n";
		}
		else
		cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：ivyjiao (赞：0)

## 题目分析：

对于 $a$，题目支持两种操作：

1.	如果目前的数 $a$ 是**偶数**，那么你可以将其变成 $\dfrac{3a}{2}$；
2.	如果目前的数 $a$ 大于 $1$，那么你可以将其变成 $a-1$。

现在有一个数 $x$。请问你是否可以通过上述操作将其变成 $y$。

显然，在 $x$ 为 $1$ 时，不可以。

当 $x>y$ 时，每次将 $x$ 减 $1$ 即可。

当 $x \leq 3$ 并且 $y > 3$ 时，$x$ 永远也变不到 $y$。因为能执行操作 $1$ 的数只有 $2$。变化为 $2 \to 6 \to 3 \to 2$。

当 $x >3$ 时，只要让 $x$ 每次乘 $3$ 除 $2$ 就一定能大于 $y$。因为一个大于 $2$ 的偶数 $\times \dfrac{3}{2}$ （注：乘完如果是奇数再 $-1$）之后都不会回到原来的数。

代码：

```cpp
#include<iostream>
using namespace std;
int t,x,y;
int main(){
    cin>>t;
    while(t--){
        cin>>x>>y;
        if(x>=y)cout<<"YES"<<endl;
        else if(x==1)cout<<"NO"<<endl;
        else if(x<=3&&y>3)cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
}
```


---

## 作者：zgy_123 (赞：0)

9明显的，当 $x \ge y$ 时，可以直接通过第二种操作解决。反之，如果 $x < y$ 就需要先用第一种操作将 $x$ 变大。

在进行一些尝试后，我们发现：

- 当 $x=1$ 时，无法将 $x$ 增大；
- 当 $x=2,3$ 时，经过任意次操作一后 $x$ 只能变为 $3$；
- 当 $x \ge 3$ 时，经过一定次数的操作一和操作二，$x$ 可以变为 $\infty$。

所以我们的代码就是：

1. 如果 $x \ge y$ 则输出 `YES`；
2. 剩余情况中，如果 $x=2$ 且 $y=3$ 或 $x>3$ 也输出 `YES`；
3. 剩余情况输出 `NO`。

AC 代码（也许最短）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,x,y;
	cin>>t;
	while(t--){
		cin>>x>>y;
		if(x>=y||x==2&&y==3||x>3) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}

```

---


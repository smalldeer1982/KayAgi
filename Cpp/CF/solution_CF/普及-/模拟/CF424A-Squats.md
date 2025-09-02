# Squats

## 题目描述

Pasha has many hamsters and he makes them work out. Today, $ n $ hamsters ( $ n $ is even) came to work out. The hamsters lined up and each hamster either sat down or stood up.

For another exercise, Pasha needs exactly ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF424A/666f6519688863e0a36337875170dd12050e1c31.png) hamsters to stand up and the other hamsters to sit down. In one minute, Pasha can make some hamster ether sit down or stand up. How many minutes will he need to get what he wants if he acts optimally well?

## 样例 #1

### 输入

```
4
xxXx
```

### 输出

```
1
XxXx
```

## 样例 #2

### 输入

```
2
XX
```

### 输出

```
1
xX
```

## 样例 #3

### 输入

```
6
xXXxXx
```

### 输出

```
0
xXXxXx
```

# 题解

## 作者：L_zaa_L (赞：5)

## 分析
首先呢，既然是需要两个字符出现的次数相等，就可以先记录每个字符出现的次数，由于 $n\bmod 2 = 0$，使得这两个数的可以差除二（因为这两个的差是他们字符数量的差距，当一个变成另一个，这两个数值会差两个数），所以需要更改的最小次数就是 $\dfrac{\left\vert sumx-sumX\right\vert{}}{2}$（也可以边更改边记录）,而更改只需要找到数量较多的那个字符串，当遇到一个时，就改为另一个，直到两个数量相等为止。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],numx,numX,ans;
string s;
int main(){
	cin>>n;
	cin>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='x') numx++;
		else numX++; 
//记录两个字符出现的次数
	} 
	ans=abs(numx-numX)/2; 
//求最少更改
	for(int i=1;i<=n;i++){
		if(numx==numX) break;
//相等就不换了
		if(s[i-1]=='x')
			if(numx>numX) numx--,numX++,s[i-1]='X';
		if(s[i-1]=='X')
			if(numx<numX) numX--,numx++,s[i-1]='x';
//找到并更改
	}
	cout<<ans<<endl;
	cout<<s;
	return 0;
}

```
难度：橘。

---

## 作者：cff_0102 (赞：2)

建议评分：红/橙。

不讲废话，直接开始推导。

字符串里面只包含 `X` 和 `x` 两个字符，$n$ 是偶数，所以要移动的个数是 $|\frac{(\text{\textquotedblleft X\textquotedblright的个数}-\text{\textquotedblleft x\textquotedblright的个数})}{2}|$。

接着从头到尾遍历整个字符串，把多的字符替换为少的那个，直到两个字符个数相等。

接着输出即可。

代码如下（禁抄）：

```cpp
#include <bits\stdc++.h>
using namespace std;
char s[205];//输入的字符串
int main() {
    int n,x=0,X=0;//n如原题，x为“x”的个数，X为“X”的个数
	cin>>n>>s;//输入
	for(int i=0;i<n;i++){
        (s[i]=='x')?x++:X++;//用三目运算符计数
    }
    int c=abs((X-x)/2);//上面的推导
	for(int i=0; i<n;i++) {
		if(s[i]=='x'&&x>X) {
			s[i]='X';
            x--,X++;
		}if(s[i]=='X'&&X>x) {
			s[i]='x';
            X--,x++;//这6行是把多的字符替换为少的那个
		}if(x==X)break;//直到两个字符个数相等
	}
    cout<<c<<endl<<s;//接着输出即可
	return 0;
}
```

求过。

---

## 作者：Eason_AC (赞：1)

## Content
给定一个长度为 $n$ 的仅由 `x` 和 `X` 组成的字符串，求使得字符串中 `x` 和 `X` 的数量相等需要修改的次数，并输出修改后的字符串。

**数据范围：$2\leqslant n\leqslant 200,2\mid n$。**
## Solution
首先得统计一下 `x` 的个数 $num_x$ 和 `X` 的个数 $num_X$，不难看出，答案就是 $\dfrac{|num_x-num_X|}{2}$。得到答案后再扫一遍把出现次数多的字符替换成出现次数少的字符，直到出现次数相等为止。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int len, numx, numX;
string s;

int main() {
	scanf("%d", &len);
	cin >> s;
	for(int i = 0; i < len; ++i) numx += (s[i] == 'x'), numX += (s[i] == 'X');
	printf("%d\n", abs(numx - numX) / 2);
	if(numx > numX)
		for(int i = 0; i < len; ++i) {
			if(s[i] == 'x') {
				s[i] = 'X', numx--, numX++;
				if(numx == numX) {cout << s; return 0;}
			}
		}
	else if(numx == numX) {cout << s; return 0;}
	else
		for(int i = 0; i < len; ++i)
			if(s[i] == 'X') {
				s[i] = 'x', numx++, numX--;
				if(numx == numX) {cout << s; return 0;}
			}
	return 0;
}

```

---

## 作者：ztxtjz (赞：1)

## 【思路】
分别统计 x 和 X 出现的次数，修改次数为差的一半的绝对值。

输出时优先将靠前的次数多的字母替换掉，直至次数相等，则输出原字母。

## 【代码】
```cpp
#include <cstdio>
char a[205];
int n,x,y;
int main()
{
	scanf("%d",&n);getchar();
	for(int i=1;i<=n;i++)
		(a[i]=getchar())=='x'?x++:y++;
	printf("%d\n",(x>y?x-y:y-x)>>1);
	for(int i=1;i<=n;i++)
	{
		while(x>y)
		{
			if(a[i++]=='x') x--,y++;
			printf("X");
		}
		while(x<y)
		{
			if(a[i++]=='X') x++,y--;
			printf("x");
		}
		printf("%c",a[i]);
	}
	return 0;
}
```


---

## 作者：Life_alone (赞：0)

一道字符串模拟题。

#### 题目大意：

给定一个只有 x 和 X 的字符串，求最少要几次才能让字符串中的 x 和 X 的数量相同，输出后来的字符串和操作次数。

#### 思路：

显然，最后的操作数就是 $\frac{\left|s_x-s_X\right|}{2}$，再遍历一次，得出后来的字符串，输出即可。

#### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[210];

int main()
{
    int n, s = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if (a[i] == 'X')
            s++;
    }
    if (s == n / 2)//如果输入的字符串x和X数量正好相等。 
        cout << 0 << endl
             << a << endl;
    else
    {
        cout << abs(s - n / 2) << endl;
        if (s < n / 2)
        {
            s = n / 2 - s;
            for (int i = 1; i <= n; i++)
                if (s && a[i] == 'x')
                    cout << 'X', s--;
                else
                    cout << a[i];
        }
        else
        {
            s = s - n / 2;
            for (int i = 1; i <= n; i++)
                if (s && a[i] == 'X')
                    cout << 'x', s--;
                else
                    cout << a[i];
        }
    }
    return 0;
}
```


---

## 作者：CLCK (赞：0)

 难度：橙

### 一道简单的字符串模拟问题。

给定一个长度为 $n$ 的字符串 $s$ 作为输入，只含有字符 `x` 或 `X` ，要求：最少需要多少次操作，使字符串中的 `x` 与 `X` 的数量相同，输出最少操作数以及操作完的字符串。

思路：统计原始字串中的 `x` 与 `X` 的数量，因为长度 $n \mod 2 = 0$ ，所以 $|n_x - n_X| \mod 2 = 0$ ，且操作一次会使二者同时变化 $1$ ，所以显而易见，答案要求的操作数就是 $\frac{|n_x - n_X|}{2}$ ，然后进行遍历操作，题目应该有SPJ，输出正确即可。

```cpp
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
int n;
string s;
int nx, nX;
int main() {
    cin >> n >> s;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'x') {
            nx++;
        } else if (s[i] == 'X') {
            nX++;
        }
    }
    if (nx < nX) {
        cout << (nX - nx) / 2 << endl; //独树一帜的操作计数法，else部分同。
        int cnt = 0;
        for (int i = 0; i < s.size(); i++) {
            if (cnt == (nX - nx) / 2) break; //符合条件即可结束操作，else部分同。
            if (s[i] == 'X') {
                s[i] = 'x'; cnt++; //WA了几次居然是操作写反了呜呜呜
            }
        }
        cout << s << endl;
    } else {
        cout << (nx - nX) / 2 << endl;
        int cnt = 0;
        for (int i = 0; i < s.size(); i++) {
            if (cnt == (nx - nX) / 2) break;
            if (s[i] == 'x') {
                s[i] = 'X'; cnt++;
            }
        }
        cout << s << endl;
    }
    return 0;
}
```

完结撒花～

管理大大求过 `：D`

---

## 作者：CobaltChloride (赞：0)

```
#include<bits/stdc++.h>
using namespace std;
int n,i,ans;
char c[201];
int main(){
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>c[i];
		if(c[i]=='x') ans--;
		if(c[i]=='X') ans++;
	}//求出X的个数减去x的个数
	i=1;
	ans/=2;//注意改变的是差的一半
	cout<<abs(ans)<<endl;
	while(ans!=0&&i<=n){
		if(ans>0){
			while(c[i]!='X') i++;
			c[i]='x';
			ans--;
		}
		if(ans<0){
			while(c[i]!='x') i++;
			c[i]='X';
			ans++;
		}
	}//制作串
	for(i=1;i<=n;i++) cout<<c[i];
	return 0;
}
```

---


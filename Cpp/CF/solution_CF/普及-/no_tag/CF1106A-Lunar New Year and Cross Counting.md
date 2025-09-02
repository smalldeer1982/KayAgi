# Lunar New Year and Cross Counting

## 题目描述

在一个 $n \times n$ 的地图中寻找有几个图案，满足

$M(i,j)=M(i-1,j-1)=M(i-1,j+1)=M(i+1,j-1)=M(i+1,j+1)=X$

形似下图。
```
X.X
.X.
X.X
```
如果图案中心所在位置不同即视作不同。

## 样例 #1

### 输入

```
5
.....
.XXX.
.XXX.
.XXX.
.....
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
XX
XX
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6
......
X.X.X.
.X.X.X
X.X.X.
.X.X.X
......
```

### 输出

```
4
```

# 题解

## 作者：Atmizz (赞：5)

## ~~基本思路~~：


------------

这个题并不是很难，完全可以~~暴力~~枚举。分别列举出这个点周围的点是否是'X'，是的话就计数器加加，然后在看下一个点。（蒟蒻的思路应该很好理解吧！？）


------------

### AC代码如下：


------------

```cpp
#include<cstdio>//不推荐使用万能头
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
int n;
int ans=0;//最终答案answer英语就是很好（其实不好了）
char map[520][520];//520很吉利！！给你们的
int main()
{
	cin>>n;
	memset(map,'.',sizeof(map));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>map[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)//暴力枚举即可
			if(map[i][j]=='X')//这个点是
				if(map[i+1][j+1]=='X')//看周围四个点
					if(map[i+1][j-1]=='X')
						if(map[i-1][j-1]=='X')
							if(map[i-1][j+1]=='X')
								ans++;//计数器加加
	cout<<ans;
	return 0;
}
```
## 求过！！！
感谢观看！！

---

## 作者：hswfwkj_ (赞：2)

本题其实很简单，只需要暴力枚举每个点，判断该点以及周围四个点是不是 $X$ 就行了。因为数据很弱，就算最多也只需要${2*500^2}=500000$次，因此枚举完全没问题。

代码应该很好理解，就不做过多赘述了，贴上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,i,j,ans=0;
	char c[510][510];
	cin>>n;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			cin>>c[i][j];
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(c[i][j]=='X'&&
            			c[i-1][j-1]=='X'&&
            				c[i-1][j+1]=='X'&&
            					c[i+1][j-1]=='X'&&
            						c[i+1][j+1]=='X')//看起来美观一点
			ans++;
	cout<<ans;
}
```
谢谢你们用心看完我的这篇题解，希望你们能给我点赞，你们的支持就是对我最大的鼓励！

---

## 作者：Aw顿顿 (赞：1)

思路：

- 暴力双重循环，逐一判断。

时间复杂度 $\mathcal O(n^2)$ ，空间复杂度 $n^2$。

此时读入最多 

$$500^2=250000$$

次。

故不会超时。

每次仅需判断 `X` 即可。

代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s=0;
char p[1001][1001];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>p[i][j];
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
        if(p[i][j]=='X'&&p[i+1][j+1]=='X'&&p[i+1][j-1]=='X'&&p[i-1][j-1]=='X'&&p[i-1][j+1]=='X')
            ++s;
    cout<<s<<endl;
    return 0;
}
```

谢谢大家。


---

## 作者：松毛虫 (赞：1)

这个题目呢，就是判断给你的输入里面有几个斜着的十字，题目灰常简单，甚至枚举每个点的IF语句的大概内容都给你了，话不多说了，放代码啦！
```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,ans=0;
	cin>>n;
	char M[505][505]; //先定义一个二维数组
	for(int i=0;i<n;i++){
	for(int j=0;j<n;j++){
	cin>>M[i][j];//把这个二维数组整进来
	}
	}
	for(int i=0;i<n;i++){
	for(int j=0;j<n;j++){
	if(M[i][j]=='X'&&M[i-1][j+1]=='X'&&M[i+1][j-1]=='X'&&M[i+1][j+1]=='X'&&M[i-1][j-1]=='X')
    //枚举每一个点，看看满足吗
	ans++;//满足就让输出的值+1
	}
	}
	cout<<ans;
	return 0;
} 

```

---

## 作者：Anguei (赞：1)

题意：给定一个字符矩阵，求矩阵中由五个 `X` 组成的大 `X` 的数量。

思路：枚举每个点，判断是否是 `X` 的中心点。

```cpp
const int N = 500 + 5;
int n, ans = 0;
char a[N][N];

void solution() {
    n = read();
    rep(i, 1, n) scanf("%s", a[i] + 1);
    rep(i, 1, n) rep(j, 1, n) ans += (a[i][j] == a[i - 1][j - 1] && a[i][j] == a[i - 1][j + 1] && a[i][j] == a[i + 1][j - 1] && a[i][j] == a[i + 1][j + 1] && a[i][j] == 'X');
    println(ans);
}
```

---

## 作者：xgwpp6710 (赞：0)

这题非常水，建议降红题。

因为这个 $n$ 是不超过 $500$ 的，所以这个矩阵不会很大，因此按照题意暴力模拟即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char mp[509][509];
int n,ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) cin>>mp[i][j];
	for(int i=2;i<=n-1;i++)//这里从(1,1)开始也可以，因为这样会搜索到第0行和第0列，但这些数据都不是"X"，因此不会对结果造成影响
		for(int j=2;j<=n-1;j++)
			if(mp[i][j]=='X'&&mp[i-1][j-1]=='X'&&mp[i-1][j+1]=='X'&&mp[i+1][j-1]=='X'&&mp[i+1][j+1]=='X') ans++;//按题意模拟
	cout<<ans;
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
试求出在一个 $n\times n$ 的地图 $M$ 中，满足 $1\leqslant i,j\leqslant n$ 且 $M_{i,j}=M_{i+1,j+1}=M_{i-1,j+1}=M_{i-1,j-1}=M_{i+1,j-1}=$ ``X`` 这个字符的 $(i,j)$ 的对数。

**数据范围：$1\leqslant n\leqslant 500$，字符只包含 ``X`` 或者 ``.``。**
## Solution
直接暴力枚举判断就好了，建议用 $i=1\sim n,j=1\sim n$ 的方式读入，再将数组开大点，就不需要考虑越界的问题了。具体见代码。
## Code
```cpp
int n, ans;
char a[507][507];

int main() {
	getint(n);
	_for(i, 1, n)	scanf("%s", a[i] + 1);
	_for(i, 1, n)
		_for(j, 1, n)
			if(a[i][j] == 'X' && a[i + 1][j + 1] == 'X' && a[i - 1][j + 1] == 'X' && a[i - 1][j - 1] == 'X' && a[i + 1][j - 1] == 'X')	ans++; 
	writeint(ans);
	return 0;
}
```

---

## 作者：FP·荷兰猪 (赞：0)

先吐槽一下，好不容易等到一个CF的Chinese Round，时间很好，认真比了一回，结果变成Unrate的了555

这题就是统计由5个'X'组成的大图形的数量
```cpp
X.X
.X.
XXX
```
一道字符串水题

```cpp
#include <bits/stdc++.h>
using namespace std;
char c[501][501];
int main()
{
	int n;
	cin>>n;
	int i,j;
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=n;j++)
		{
			cin>>c[i][j];
		}
	}
	int ans=0;
	for (i=2;i<=n-1;i++)
	{
		for (j=2;j<=n-1;j++)
		{
			if (c[i][j]=='X' && c[i-1][j-1]=='X' && c[i-1][j+1]=='X' && c[i+1][j-1]=='X' && c[i+1][j+1]=='X')//判断以这个坐标为中心有没有大'X'
			{
				ans++;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：WYFwyf (赞：0)

遍历一遍，遇到X后按题目要求判断X是否是中心点
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
int n,ans=0;
char m[501][501];
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
      cin>>m[i][j];
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
     {
     	if(m[i][j]=='X')
     	{
     		if(m[i-1][j-1]=='X'&&m[i-1][j+1]=='X'&&m[i+1][j-1]=='X'&&m[i+1][j+1]=='X')
     		 ans++;
        }
     }
     cout<<ans<<endl;
     return 0;
}
```

---

## 作者：梦游的小雪球 (赞：0)

**这道题题目应该不用讲吧，那么我们直接来讲思路：**
- 这道题我们只需要一个一个搜中心。
- 搜中心时不要搜最外层，原因：确认中心后还要向四周搜，最外层不可能是中心。
### AC代码：
**如果思路还没懂，就请看看注释吧**
```
#include<bits/stdc++.h>
using namespace std;
int n,s;//s用来统计图形个数
char c[502][502];//定义
int main(){
    cin>>n;
	for(int i=1;i<=n;i++)
    	for(int j=1;j<=n;j++)
    		cin>>c[i][j];//输入。
	for(int i=2;i<n;i++)
		for(int j=2;j<n;j++)//枚举所有可能为中心的点。
			if(c[i][j]=='X'&&c[i-1][j-1]=='X'&&c[i+1][j+1]=='X'&&c[i-1][j+1]=='X'&&c[i+1][j-1]=='X')//判断是否为这种图形。
				s++;//如果是，s就+1。
	cout<<s;//输出
    return 0;
}
```
#### 恳求管理通过QWQ

---


# [NOISG 2023 Qualification] Area

## 题目描述

Stuart 有 $n$ 个长方形，第 $i$ 个长方形长 $h_i$，宽 $w_i$。

长方形的面积是它所覆盖的区域的大小。Stuart 想请你帮他找到这 $n$ 个长方形中面积最大的一个的面积。

## 说明/提示

### 【数据范围】

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$1$|$50$|$n=1$|
|$2$|$50$|无|

对于所有数据，$1\le n\le100,1\le h_i,w_i\le1000$。

## 样例 #1

### 输入

```
3
5 9
19 4
8 10```

### 输出

```
80```

## 样例 #2

### 输入

```
5
8 2
4 9
3 8
1 7
9 4
```

### 输出

```
36```

# 题解

## 作者：Stars_visitor_tyw (赞：5)

### 分析
这什么逆天简单题。

众所周知，长方形的面积公式为 $h_i \times w_i$，对于每个长方形算出面积再取最大值就行了。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    int n;
    cin>>n;
    int maxi=0;
    for(int i=1;i<=n;i++)
    {
        int x, y;
        cin>>x>>y;
        maxi=max(maxi,x*y);
    }
    cout<<maxi;
}

---

## 作者：letianJOE (赞：1)

## 题目大意

给定 $n$ 个长方形的长和宽，求面积最大的长方形。

## 思路

长方形的面积公式是

$$s_{长方形}=ab$$

$a$ 是长，$b$ 是宽。

所以直接按照面积公式算出每个长方形的面积在比较大小即可。

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x7fffffff;
main()
{
	int n;
	int maxx=-inf;
	cin>>n;
	while(n--)
	{
		int a,b;
		cin>>a>>b;
		maxx=max(maxx,a*b);
	}
	cout<<maxx<<"\n";
	return 0;
}
```

---

## 作者：zhanghy123 (赞：1)

长方形面积公式为长乘宽，所以计算每个 $h_i \times w_i$ 的值，并选择最大的一个输出即可。

### 参考代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,a,b,maxx=-1;//maxx表示最大值，初始值最好设小一点 
int main()
{
	cin>>n;
	while(n--)//n个长方形，循环n次 
	{
		cin>>a>>b;
		maxx=max(maxx,a*b);//计算长乘宽，选择最大的 
	}
	cout<<maxx;
	return 0;
}


```

---

## 作者：封禁用户 (赞：1)

大水题。

题目让你找到这 $n$ 个长方形中面积最大的一个的面积，排序题诶。

先输入 $h_i$ 和 $w_i$，用数组 $S$ 存储 $h_i\times w_i$，即长方形的面积：

```cpp
for(int i=1;i=n;i++){
	cin>>h[i]>>w[i];//input
	S[i]=h[i]*w[i];//存储长方形面积
}
```

倒序排序：

```cpp
sort(S+1,S+n+1,greater<int>);
```
最后输出一下就好啦！！！完结撒花！！！

---

## 作者：Mark0104 (赞：0)

## 题目大意：
给定 $n$ 个长方形的长和宽，求这些长方形中最大的面积。
## 思路
在输入时处理好每个长方形的面积然后排序即可。
## 上代码
```

#include<bits/stdc++.h>
using namespace std;
int n,h,w,s[1001];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>h>>w;
		s[i]=h*w;//预处理面积 
	}
	sort(s+1,s+n+1);//排序 
	cout<<s[n];
}
```

---

## 作者：donnieguo (赞：0)

对于第 $i$ 个长方形，它的面积为 $h_i \times w_i$，所以我们只需要枚举 $1 \sim n$ 中所有的长方形并计算它们的面积，如果比当前的答案更大，那么就更新答案。最后输出即可。

code：

```cpp
#include <iostream>
using namespace std;

int ans = -1, n;
int h, w;
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> h >> w;
		ans = max(ans, h * w);//打擂法
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：sxq9 (赞：0)

## 读题

给出若干个长方形的长和宽，求最大长方形的面积。

## 思路

由于长方形面积为长乘宽，所以我们依次求出每个长方形面积再求最大值即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a,b,maxn=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		maxn=max(maxn,a*b);
	}
	cout<<maxn;
	return 0;
}
```

---

## 作者：Eason_cyx (赞：0)

长方形的面积等于长乘宽。

所以我们顺着暴力枚举每一个长方形，枚举最大值即可。时间复杂度 $\Theta(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
  int n;
  cin>>n;
  int max_area=0;
  for(int i=0;i<n;i++){
    int height,width;
    cin>>height>>width;
    int area=height*width;
    if(area>max_area)max_area=area;
  }

  cout<<max_area;
  return 0;
}
```

---


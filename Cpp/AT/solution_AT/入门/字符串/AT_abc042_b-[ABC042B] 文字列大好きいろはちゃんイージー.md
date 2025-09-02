# [ABC042B] 文字列大好きいろはちゃんイージー

## 题目描述

有n个长为L的字符串
 
 要求把他们按照字典序进行排序并在一行内输出

## 说明/提示

1，1 <= n,L <= 100且n，L 都是正整数
 
 2，对于第i(1 <= i <= n)个字符串，保证长度为L
 
 3，所有字符串都由小写字母构成

感谢@lsy263  提供的翻译

## 样例 #1

### 输入

```
3 3
dxx
axx
cxx```

### 输出

```
axxcxxdxx```

# 题解

## 作者：StarLbright40 (赞：12)

emm由于有dalao已经讲了具体思路

~~所以作为蒟蒻的我就不写具体思路了~~

就只介绍一个sao操作

```
#include<bits/stdc++.h>//我爱万能头 
using namespace std;
string a[101];int n,i;
int main(){
	scanf("%d%*d",&n);//sao操作所在地 
	for(i=0;i<n;i++)
		cin>>a[i];
	sort(a,a+n);//虽然会其他排序方法但懒得打QwQ 
	for(i=0;i<n;i++)
		cout<<a[i];
	return 0;
}
```

由于那个L也用不着，所以~~懒得声明变量的~~我就记起了这样一个sao操作

接下来简单介绍一下~~~

在C++的scanf中，**在%后面添加一个*就是过滤掉这个位置的变量**

举个栗子：

```
scanf("%d%*d%d",&a,&b);
```
输入：13 18 24

实际存储：a==13,b==24;


---

## 作者：Kevin_Zhen (赞：2)

# 优先队列解法
我们来玩一些好玩的。  
此种解法可以参照我在 [AT2646](https://www.luogu.com.cn/problem/AT2646) 撰写的题解。
## 题目大意
给你 $n$ 个字符串，按字典序排序后输出。
## 变量介绍
1. $q$ 是用于保证存储字符串有序的优先队列，因为按照字典序排序，所以是小根堆。
2. $n$、$l$ 记录字符串的个数和长度（其实 $l$ 根本没用）。

## 解题过程
首先定义一个字符串类型的小根堆。
```cpp
priority_queue<string, vector<string >, greater<string > > q;
```
然后输入 $n$ 个字符串，压入小根堆。
```cpp
for (int i = 1; i <= n; ++i) {
	string t;
	cin >> t;
	q.push(t);
}
```
最后只要小根堆非空，输出堆顶元素即可。
```cpp
while (!q.empty()) {
	cout << q.top();
	q.pop();
}
```
## AC CODE
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <string>
#define int string
using namespace std;

priority_queue<int, vector<int >, greater<int > > q;
long n, l;

signed main() {
	cin >> n >> l;
	for (long i = 1; i <= n; ++i) {
		int t;
		cin >> t;
		q.push(t);
	}
	while (!q.empty()) {
		cout << q.top();
		q.pop();
	}
	putchar('\n');
	return 0;
}
```
## 感谢观赏！

---

## 作者：Frank_R_Z (赞：0)

###
sort虽然~~时间复杂度小，代码短~~，但我还是觉得冒泡排序也不错，至少是稳定的，保持在O(n²)。[https://baike.so.com/doc/2392104-2529369.html](具体看这里)
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,l;
	string st[102];
	cin>>n>>l;
	for(int i=1;i<=n;i++)
		cin>>st[i];
	for(int i=1;i<=n;i++)//冒泡排序主部分
		for(int j=1;j<=n-i;j++)
		{
			if(st[j]>st[j+1])swap(st[j],st[j+1]);//交换
		}
	for(int i=1;i<=n;i++)
	{
		cout<<st[i];//输出
	}	
	cout<<endl;
	return 0;
}

```


---

## 作者：RioBlu (赞：0)

sort大法好

因为长度一样，只要把字符串sort(快排)一次即可

其实我觉得$L$没有任何用
```
#include<bits/stdc++.h>
using namespace std;
int a,n;
string b[105];
int main()
{
    cin>>a>>n;
	for(int s=0;s<a;s++)
	{
		cin>>b[s];
	}
	sort(b,b+a);
	for(int s=0;s<a;s++)
	cout<<b[s];
	cout<<endl;
}
```

---


# [ABC164C] gacha

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc164/tasks/abc164_c

くじ引きを $ N $ 回行い、$ i $ 回目には種類が文字列 $ S_i $ で表される景品を手に入れました。

何種類の景品を手に入れましたか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ S_i $ は英小文字のみからなり、長さは $ 1 $ 以上 $ 10 $ 以下

### Sample Explanation 1

`apple` と `orange` の $ 2 $ 種類の景品を手に入れました。

## 样例 #1

### 输入

```
3
apple
orange
apple```

### 输出

```
2```

## 样例 #2

### 输入

```
5
grape
grape
grape
grape
grape```

### 输出

```
1```

## 样例 #3

### 输入

```
4
aaaa
a
aaa
aa```

### 输出

```
4```

# 题解

## 作者：Diamiko (赞：5)

题目要求所有字符串中不相同的有几个。

可以直接使用set，因为set有去重的功能。把所有输入的字符串放入set中，然后直接输出set的长度即可。

```python
n=int(input())
s=set()
for i in range(n):
	s.add(input())
print(len(s))
```

---

## 作者：Miller2019 (赞：4)

题意：检查有多少种不重复的字符串。我这里有两种方法：
1. 排序+去重 先使用 `sort` 函数排序字符串数组，在使用`unique`函数计算出无重复的个数。
1. 使用 map ,以 string 类型作为下标，每次读入并赋值数组中以该 string 为下标的 bool 变量。最后调用函数 size()，输出即可。

排序+去重的方法：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,t;string str[1000000];//注意开大一点，我就RE了，多亏 qym2008 巨佬。
int main()
{
    ios::sync_with_stdio(0); //取消同步。
    cin>>n;	//读入变量 n 。
    for(;t<n;t++)
    {
        cin>>str[t];	//读入字符串str[t]。
    }
    if(!is_sorted(str,str+n))/*这是C++11的函数，可以判断是否有序。*/   sort(str,str+n); //如果有序，就不用排了，省时间。
    cout<<unique(str,str+n)-str<<'\n';//重点：unique(str,str+n)-str 去重并计算个数。
    return 0;//Don't forget this.
}
```
map的方法:
```cpp
#include<iostream>
#include<map>
using namespace std;
map<string,bool>strs; //定义以 string 为下标的 bool 数组。
string str;
int main()
{
	cin>>str; //不用管第一个。
	while(cin>>str)	//每次循环，读入字符串 str ，如果读到输入的末尾会停止循环。
	{
		strs[str]=1; //赋值。
	}
	cout<<strs.size()<<endl; //输出strs的大小。
	return 0;
}
```
蒟蒻橙后第 5 篇题解。

---

## 作者：ADay (赞：4)

### ~~STL大法好~~
我们可以使用$STL$的$unique$函数。   
用法：  
对于一个$vector:a$，$unique(a.begin(),a.end())$会把重复的**相邻**元素放到末尾，并且返回最后一个**不重复元素的指针**，那么想要获取去重后的$size$，要先排序，然后把它减去$a.begin()$即可  
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

vector<string>a;
int n,cnt=1;
string x;

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);//加速cincout
	cin>>n;
	while(n--)cin>>x,a.push_back(x);//把字符串都塞进a
	sort(a.begin(),a.end());//排序
	cout<<unique(a.begin(),a.end())-a.begin();//去重
	return 0;
}
```


---

## 作者：第二小题 (赞：1)

~~我一个只会模拟的蒟蒻只会用比较低级的方法~~

[AC记录](https://www.luogu.com.cn/record/33334992)

就拿样例1举例吧

我们可以把这些字符串存在数组里：

![](https://cdn.luogu.com.cn/upload/image_hosting/5kpuvri0.png)

然后再排一个序：

![](https://cdn.luogu.com.cn/upload/image_hosting/c0tm4tz0.png)

由于已经排序，所以字符串相同的一定会连接在一起；

那么我们可以直接用当前的下标+1来判断它的下一个字符串是否与它相同，因为排了序，所以不再担心重复计算的问题。若相同，那就用累加器加1。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
long long n,l,ans;
int main()
{
	string a[200010];
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);//排序
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=a[i+1])//若此字符串不与下一个相同，计数器+1
		{
			ans++;
		}
	}
	cout<<ans<<endl;//输出
}
```

---

## 作者：Scrutiny (赞：1)

这题其实是和$P3370$重题的，这里提供一种与$P3370$的$HASH$不同的解法：$set$。

我们知道$set$有自动去重的功能，因此解决这题再合适不过了。

思路：对于每个输入的字符串，将其插入进$set$中，全部输入完后统计$set$中元素个数即可。


### 注意：

1.$set$最好定义指针。

2.$set$的类型必须是`string`。

### CODE:


```cpp

#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	string s;
	set<string> ss;
	set<string>::iterator it;
	std::ios::sync_with_stdio(false);
	cin>>n;
	getline(cin,s);
	for(int i=1;i<=n;++i){
		getline(cin,s);
		ss.insert(s);
	}
	cout<<ss.size();
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

题目传送门：[AT5366 [ABC164C] gacha](https://www.luogu.com.cn/problem/AT5366)

**题目大意：** 给你$N$个字符串，求有多少个不同的字符串。

**题解：** $set$有去重功能，所以放到$set$里计数即可。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define in inline
#define re register
in ll read(){
   ll s=0;bool w=1;char ch=getchar();while(ch<'0' || ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0' && ch<='9')s=s*10+ch-'0',ch=getchar();return s*w;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);putchar(x%10+'0');
}
unordered_set<string> S;
int main() {
    int n=read();
    for(re int i=0;i<n;i++){
        string s;
        cin>>s;
        S.insert(s);
    }
    write(S.size());
    return 0;
}
```


---


# Balanced Shuffle (Easy)

## 题目描述

A parentheses sequence is a string consisting of characters "(" and ")", for example "(()((".

A balanced parentheses sequence is a parentheses sequence which can become a valid mathematical expression after inserting numbers and operations into it, for example "(()(()))".

The balance of a parentheses sequence is defined as the number of opening parentheses "(" minus the number of closing parentheses ")". For example, the balance of the sequence "(()((" is 3.

A balanced parentheses sequence can also be defined as a parentheses sequence with balance 0 such that each of its prefixes has a non-negative balance.

We define the balanced shuffle operation that takes a parentheses sequence and returns a parentheses sequence as follows: first, for every character of the input sequence, we compute the balance of the prefix of the sequence before that character and write those down in a table together with the positions of the characters in the input sequence, for example:

Prefix balance01212321Position12345678Character(()(()))Then, we sort the columns of this table in increasing order of prefix balance, breaking ties in decreasing order of position. In the above example, we get:

Prefix balance01112223Position18427536Character()(()())The last row of this table forms another parentheses sequence, in this case "()(()())". This sequence is called the result of applying the balanced shuffle operation to the input sequence, or in short just the balanced shuffle of the input sequence.

You are given a balanced parentheses sequence. Print its balanced shuffle.

## 样例 #1

### 输入

```
(()(()))```

### 输出

```
()(()())```

# 题解

## 作者：Dream_Mr_li (赞：2)

## 思路

按题意模拟即可。

直接用前缀，因为字符串 $a_i$ 前字符串的平衡度就等于 `(` 的数量减去 `)` 的数量，所以我们让 `(` 的地方 $+1$，再让 `)` 的地方 $-1$，然后将前缀和存入结构体中进行排序，最后输出结构体中的信息即可。

## 代码

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
string s;
struct node{
	int x,y;
}a[N];
bool cmp(node aa,node bb){
	if(aa.x!=bb.x)
	return aa.x<bb.x;
	return aa.y>bb.y;
}
signed main(){
	cin>>s;
	for(int i=2;i<=s.size();i++){
		a[i].x=a[i-1].x;
		if(s[i-2]=='('){
			a[i].x++;
		}else{
			a[i].x--;
		}
		a[i].y=i-1;
	}
	sort(a+1,a+s.size()+1,cmp);
	for(int i=1;i<=s.size();i++){
		cout<<s[a[i].y];
	}
	return 0;
}
```

---

## 作者：banglee (赞：1)

## CF1970A1 Balanced Shuffle (Easy) 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1970A1)

## 正文
既然问题已经给出了我们要干什么了，那我们便可以直接模拟。

输出的时候要注意每个括号对应另一个括号哦，这样才算是一对完整的括号。

补充一点，下文所使用到的 ```tuple``` 很多同学可能不知道什么意思，让我来解释一下吧。

```tuple``` 是一个固定大小的不同类型值的集合，是泛化的```pair```。我们也可以把它当做一个通用的结构体来用，不需要创建结构体又获取结构体的特征，在某些情况下可以取代结构体使程序更简洁，直观。```tuple``` 理论上可以有无数个任意类型的成员变量，```pair``` 只能是 $2$ 个成员，因此在需要保存 $3$ 个及以上的数据时就需要使用 ```tuple``` 元组了。

想要了解更多的同学 [戳这里](https://blog.csdn.net/sinat_31608641/article/details/123315773)。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int b;
string s,res;
vector<tuple<int,int,char>> a;
int main(){
    getline(cin,s); // 读取一行字符串
    for(int i=0;i<s.size();i++)
    {
        a.push_back(make_tuple(b,-i,s[i]));
        if(s[i]=='(') b++;
        else if(s[i]==')') b--;
    }
    //对数组进行排序
    sort(a.begin(),a.end()); //使用 C++ 的 sort 函数对 vector 中的元组进行排序。默认情况下，tuple 会先比较第一个元素，如果相等则比较第二个，依此类推。
    // 拼接排序后的字符
    for(const auto& x : a)
        res.push_back(get<2>(x));
    // 输出结果
    cout<<res;
    return 0;
}
```

---

## 作者：Furina_Saikou (赞：0)

# 思路

用结构体存储字符，前缀平衡度，在原来数组的位置，先预处理出前缀平衡度，再使用结构体快排，最后输出。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1919810;
struct node{
	char c;//原字符
	int val,id;//前缀平衡度，原位置
}a[N];
string s;
int n;
bool cmp(node x,node y)
{
	return x.val!=y.val?x.val<y.val:x.id>y.id;//三目运算符，意思是前缀平衡度不同就按前缀平衡度从小到大排序，相同就按原位置从大到小排序 
}
int main()
{
	cin>>s;
	n=s.size();
	for(int i=0,l=0,r=0;i<n;i++)//l,r分别是左括号数和右括号数
	{
		a[i].c=s[i],a[i].val=l-r,a[i].id=i;
		if(s[i]=='(')l++;
		else r++;
	}
	sort(a,a+n,cmp);
	for(int i=0;i<n;i++)
	{
		cout<<a[i].c;
	}
}
```

---

## 作者：OIer_Hhy (赞：0)

这道题太水了。

直接用前缀和+排序就 AC 了。

$sum _ {i}$ 存储的是 $sum _ {1},sum _ {2},\cdots,sum _ {i}$ 中 `(`  的个数减去 `)` 的个数。 

代码：
``` cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n,sum[500100];
map<char,int> m;
struct node{
	int x,y;
}a[500010];
int cmp(node a,node b){
	return a.x<b.x||a.x==b.x&&a.y>b.y;
}
signed main(){
	cin>>s;
	n=s.size();
	m['(']=1;
	m[')']=-1;
	for(int i=2;i<=n;i++){
		sum[i]=sum[i-1]+m[s[i-2]];
		a[i].x=sum[i];
		a[i].y=i-1;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++) cout<<s[a[i].y];
	return 0;
}
```

---

## 作者：szhqwq (赞：0)

## $\tt{Translate}$

给定一个括号序列，定义一个序列的平衡度为序列中左括号 `(` 的数量减去右括号 `)` 的数量，前缀平衡度为一个字符之前的平衡度（**不包括这个字符**），现以前缀平衡度递增，再位置递减的顺序对序列进行排序，输出最终序列。

## $\tt{Solution}$

根据题意进行模拟，求出序列每一位上的前缀平衡度，然后存入结构体中，按照前缀平衡度从小到大为第一关键字，位置编号从大到小为第二关键字对其进行排序，最后遍历结构体中的信息直接输出即可。

[Link](https://codeforces.com/contest/1970/submission/261979948)

---


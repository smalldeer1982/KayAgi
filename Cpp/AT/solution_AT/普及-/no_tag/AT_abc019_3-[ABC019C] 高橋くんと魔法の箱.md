# [ABC019C] 高橋くんと魔法の箱

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc019/tasks/abc019_3

高橋くんは魔法の箱を持っています。

この箱に整数を入れるとそれに対応した整数が出てきます。

出てくる整数は入れた整数だけによって決まり、同じ整数を入れると毎回同じ結果が得られます。

高橋くんは任意の整数 $ x $ について、$ x $ を入れた時と $ 2x $ を入れた時に出てくる整数が同じであることに気づきました。

高橋くんが入れた整数が $ N $ 個与えられるので、最大で何種類の整数が出てくるか答えてください。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ 20 $ 点分のテストケースにおいて、$ 1\ ≦\ N\ ≦\ 3,000 $ を満たす。
- 別の $ 30 $ 点分のテストケースにおいて、$ 1\ ≦\ a_i\ ≦\ 5*10^5\ (\ 1\ ≦\ i\ ≦\ N) $ を満たす。

### Sample Explanation 1

$ 2 $ を入れた時に出てくる整数は、$ 1 $ を入れた時に出てくる整数と等しいので、最大で $ 2 $ 種類の整数が出てきます。

### Sample Explanation 2

すべて同じ整数が出てきます。

### Sample Explanation 3

出てくる整数が全て違う可能性があります。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
4
2 4 8 16```

### 输出

```
1```

## 样例 #3

### 输入

```
4
2 3 5 7```

### 输出

```
4```

# 题解

## 作者：Wang1006 (赞：5)

题目中说要去重，用 `set`。它有自己去重的功能。    
```cpp
#include<iostream>
#include<set>
using namespace std;
set<int>s;
int n;
int f;
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>f;
        while(f%2==0){ // 把因子 2 删掉
            f/=2;
        }
        s.insert(f); // 加入容器
    }
    cout<<s.size()<<endl; // 输出大小
}
```

---

## 作者：Failure_Terminator (赞：1)

## Solution

和楼下各位用 `set` 和 `map` 的大佬思路略有不同，也许更好理解吧。

由于放入 $2x$ 和 放入 $x$ 的输出结果是一样的，所以我们可以将输入的数做处理，将里面 $2$ 的因子去掉。

这里可以使用 $\operatorname{lowbit}$ 。

接着排序，利用 STL 的 `unique` 去重。

去重后的元素个数即为所求的答案。

## AC Code

```cpp

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
vector<int> a;
int n;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i ++){
        int x;
        scanf("%d", &x);
        a.push_back(x / (x & -x));
    }
    sort(a.begin(), a.end());
    vector<int>::iterator it = unique (a.begin(), a.end());
    cout << it - a.begin() << endl;
    return 0;
}
```

---

## 作者：yinpeichu2021 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc019_3)

## 思路

这道题目的意思差不多就是，把每个数不断地除以 $2$ 直到它是奇数，丢进盒子里所得到的数都相等。我们可以根据这一特点来将每一个数都除以 $2$ 使其变成奇数,再将其去重。

什么办法可以快速地去重？用 `set`。每一次将这个奇数丢进 `set` 中，最后输出 `set` 的大小即可。

## code

```cpp
#include<bits/stdc++.h>
#define int long long//记得开long long
using namespace std;
set<int>s;
signed main(){
	int n,a;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		while(a%2==0)a/=2;
		s.insert(a);
	}
	cout<<s.size()<<'\n';//AT \n已成常态
}
```

---

## 作者：sto_yyrdxh_orz (赞：0)

### 题目大意：
第一行输入一个 $n$，接下来 $1$ 行 $n$ 个数字 $x$，删除所有 $2x$ 的数，输出剩余数字的个数。

### 题目分析：
`set` 有升序和去重功能，我们先用 `set` 把 $n$ 个数字存起来，然后利用迭代器删除当前数字 $x$ 的倍数 $2x$，最后输出 `set` 的长度。

### 具体代码：
```cpp
#include <iostream>
#include <set>
//需要的头文件 
using namespace std;
int n, x;
set<int> s;
//定义方法 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
		s.insert(x);
		//插入 
	}
	for(set<int>::iterator it=s.begin();it!=s.end();it++){
		//迭代器 
		int a=(*it)*2;
		//2x 
		if(s.count(a)){
			//如果同时出现了x和2x 
			s.erase(a);
			//删除一个 
		}
	}
	cout<<s.size();
	//输出长度 
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

## 题目简述：

给定 $n$ 个整数，已知函数 $f(x)$ 满足对于 $x\in Z $ ， $f(x)=f(2x)$ ，这 $n$ 个整数至多有多少个不同的函数返回值。

## 题目分析

若 $x_1,x_2\in Z , f(x_1)=f(x_2)$ 当 $x_1$=$2^y\times x_2$ 必然成立，其中 $y\in Z$ 。

又因为问最大值，对于可以不同的值让他的函数返回值也不同即可，又对于 $x=2^x\times y$ ， $f(x)=f(y)$ 干脆拿到一个数就把他的质因数 $2$ 全部抛弃，剩下的东西直接用数组记录是否出现过即可。

Q ： 哪来那么大的数组 。

A ： 用 map 。

## $Code$

```cpp
#include<iostream>
#include<cstdio> 
#include<map>
using namespace std;
map <int,bool> q;
int n,a;
int main(){
	cin>>n;
	while(n--){
		cin>>a;
		while(a%2==0)
			a/=2;
		q[a]=true;
	}
	cout<<q.size()<<endl;
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

这是本蒟蒻的第 $40$ 篇题解，AT1203。

### 题目大意

有 $n$ 个不同的数，给定一个函数 $f(x)$，规定 $f(x)=f(2x)$。求这 $n$ 个数中通过函数计算一次后最多会出现多少个不同的整数。

考虑一种字典思想。输入一个数，当其为 $2$ 的倍数时不断除以 $2$，再将其加入集合中。我们知道 `set` 的 `insert(p)` 函数插入后会自动判断是否出现过，出现过其实是我们看来没有加入到容器中的。所以我们可以利用这个思想完美进行去重。最后输出集合的大小就是总不同整数的个数。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
set <int> a;
int cnt=0;

int main(){
    cin>>n;
    for (int i=1; i<=n; i++){
        int p;
        cin>>p;
        while (!(p%2)) p/=2; // 将其转换为“最简”形态
        a.insert(p); // 插入
    }
    cout<<a.size()<<endl; // 输出集合大小即可
    return 0;
}
```

---


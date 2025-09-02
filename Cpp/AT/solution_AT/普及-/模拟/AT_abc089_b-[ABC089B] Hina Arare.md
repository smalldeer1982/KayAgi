# [ABC089B] Hina Arare

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc089/tasks/abc089_b

日本では、$ 3 $ 月 $ 3 $ 日にひなあられという、色のついたお菓子をお供えする習慣があります。

$ 1 $ つの袋があり、ひなあられが $ N $ 個入っています。

この袋には、桃色、白色、緑色の $ 3 $ 種類か、桃色、白色、緑色、黄色の $ 4 $ 種類のひなあられが入っていることが分かっています。

桃色を `P`、白色を `W`、緑色を `G`、黄色を `Y` と表したとき、袋からひなあられを $ 1 $ 粒ずつ取り出していったところ、$ i $ 番目に取り出したひなあられの色は $ S_i $ でした。

この袋に $ 3 $ 種類のひなあられが入っていた場合は `Three`、$ 4 $ 種類のひなあられが入っていた場合は `Four` と出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ S_i $ は `P` か `W` か `G` か `Y`
- $ S_i= $`P`、$ S_j= $`W`、$ S_k= $`G` を満たす $ i,j,k $ が必ず存在する

### Sample Explanation 1

袋に $ 4 $ 種類のひなあられが入っていたので `Four` と出力するとよいです。

### Sample Explanation 2

袋に $ 3 $ 種類のひなあられが入っていたので `Three` と出力するとよいです。

## 样例 #1

### 输入

```
6
G W Y P Y W```

### 输出

```
Four```

## 样例 #2

### 输入

```
9
G W W G P W P G G```

### 输出

```
Three```

## 样例 #3

### 输入

```
8
P Y W G Y W Y Y```

### 输出

```
Four```

# 题解

## 作者：昒昕 (赞：2)

**题意简述**

给定 $n$ 个花色，问有几个不同的花色。

**题目分析**

可以用 STL 中自带的 `set` 集合容器，内部用红黑树实现，可以自动去重和从小到大排序。

插入或删除操作所要的时间复杂度是 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

set <char> s; //value的类型为char
string ch[6]={"","","","Three","Four"};
int main() {
	int n; char c;
	cin >>n;
	while (n--) {
		cin >>c;
		s.insert(c); //插入花色
	}
	cout <<ch[(int)s.size()]<< endl; //自动去重，所以只需转换大小
	return 0;
}

```

---

## 作者：封禁用户 (赞：2)

这道题大家都看懂了，进入正题

## 题目思路

拿到这道题，我们要想办法去重，怎么办？

set!!!

set 这个东西真是太好了。他可是根据红黑树创造的东西，重要的一点就是去重。

我们只要来一个字符，我们就 push 进这个 set ，这样，最后我们判断一下 st.size() ，根据题目打表即可。

当然，大家知道 unique 也是不错的，但是要去重完还要遍历一遍，太麻烦，在这里不讲了。

上代码吧！

```cpp
#include <iostream>
#include <set>

using namespace std;
typedef long long l;

set<char> st;//注意要存字符型！

int main() {
    l n;
    cin >> n;
    for (l i = 1; i <= n; ++i) {
        char ch;
        cin >> ch;
        st.insert(ch);
    }
  	//接下来判断，撑死了也就4种，打表最好不过了
    if (st.size() == 1) {
        cout << "One" << endl;
    } else if (st.size() == 2) {
        cout << "Two" << endl;
    } else if (st.size() == 3) {
        cout << "Three" << endl;
    } else if (st.size() == 4) {
        cout << "Four" << endl;
    }
  	//学会（废）了吗？
    return 0;
}

```


---

## 作者：AgrumeStly (赞：1)

### solution

简单模拟。

- 法一  
	我们定义 4 个变量 $p,w,g,y$ ，要是出现了就赋值为 1，最后一加就是个数。
- 法二  
	定义 4 个变量 $p,w,g,y$ 分别记录 P,W,G,Y 是否出现过，若未出现则 $ans+1$ 并标记为出现过。

### code

法一

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#define ll long long
using namespace std;
int n, p, w, g, y;
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		char c;
		cin >> c;
		if (c == 'P') p = 1;
		if (c == 'W') w = 1;
		if (c == 'G') g = 1;
		if (c == 'Y') y = 1;
	}
	if (p + w + g + y == 3) cout << "Three" << endl;
	else cout << "Four" << endl;
	return 0;
}

```

法二

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#define ll long long
using namespace std;
int n;
bool p, w, g, y;
int main() {
	cin >> n;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		char c;
		cin >> c;
		if (c == 'P' && !p) ans++, p = true;
		if (c == 'W' && !w) ans++, w = true;
		if (c == 'G' && !g) ans++, g = true;
		if (c == 'Y' && !y) ans++, y = true;
	}
	if (ans == 3) cout << "Three" << endl;
	else cout << "Four" << endl;
	return 0;
}
```

---

## 作者：3a51_ (赞：1)

### 思路1

每读入一个字符，就判断一下，将相对应的计数器加 $1$ ，最后判断有没有计数器为 $0$ 的情况就可以了。

时间复杂度 $O(n)$ 。

```cpp
#include<iostream>
using namespace std;
int main()
{
	char c[105];
	int n,g=0,w=0,y=0,p=0;//计数器
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];//输入
		if(c[i]=='G')//判断是否为G
			g++;
		else if(c[i]=='W')//是否为W
			w++;
		else if(c[i]=='Y')//是否为Y
			y++;
		else//既然都不是，那就只能是P了。
			p++; 
	}
	if(y==0 || p==0 || g==0 || w==0)//判断有没有0
		cout<<"Three";
	else
		cout<<"Four";
	return 0;
}
```

### 思路2

#### STL大法好！

STL库里面，有一个好玩的东东叫做```map``` ，它可以将字符与数字产生映射。

加上
```cpp
#include<map>
```
然后
```cpp
map<char,int> m;
```
即可，表示一个```char,int```来做映射的```map``` ，具体地，就是说你可以这么访问了：
```cpp
m['s']=1;
m['s']--;
```
所以，每输入一个字符，将它加入到```map```里，最后特判。

时间复杂度 $O(nlogn)$ (```map```插入是 $O(log \times $ ```map```的大小 $)$ )。

```cpp
#include<iostream>
#include<map>
using namespace std;
map<char,int> m;
int main()
{
	char c[105];
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];
		m[c[i]]++;
	}
	if(m['G']==0 || m['Y']==0 || m['P']==0 || m['W']==0)
		cout<<"Three";
	else
		cout<<"Four";
	return 0;
}
```

留个赞吧qwq

---

## 作者：锦阳2006 (赞：0)

简述一下题意   
输入一个数$n$,然后输入$n$个字符，如果包含了$G$,$W$,$P$,$Y$中的四个就输出Four,包含三个就输出Three。

所以简单模拟即可   
上代码
```c
#include<bits/stdc++.h>//万能头文件
using namespace std;//命名空间
#define rd read()
char s[1001];
int a,b,c,d;
int read() {
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
int main() {
    int n=rd;
    gets(s);//输入
    for(int i=0;i<strlen(s);i++)
    {           if(s[i]=='G')a=1;
		if(s[i]=='W')b=1;
		if(s[i]=='P')c=1;
		if(s[i]=='Y')d=1;
}//判断是否含有字母
int ans=a+b+c+d;
if(ans==4)cout<<"Four"<<endl;//如果四种都有输出Four
else cout<<"Three"<<endl;//否则输出Three
return 0;
}
```
最后提醒一句:AT输出要换行！

---


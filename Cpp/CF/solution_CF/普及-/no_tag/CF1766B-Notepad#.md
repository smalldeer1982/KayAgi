# Notepad#

## 题目描述

一开始打出的内容为空。现在你要打出一个长度为 $n$ 的字符串 $s$（全为英文小写字母组成），为此每次你可以进行如下操作中的一种：

- 在已打出内容的最后添加一个字符。
- 复制已打出内容的一个连续的子串并加到内容的末尾。

问你能不能在严格小于 $n$ 次操作下打出字符串 $s$？

## 样例 #1

### 输入

```
6
10
codeforces
8
labacaba
5
uohhh
16
isthissuffixtree
1
x
4
momo```

### 输出

```
NO
YES
NO
YES
NO
YES```

# 题解

## 作者：_Starlit__Sky_ (赞：5)

# 洛谷 CF1610B 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1766B)

## 题目算法

for 循环 枚举

## 题目思路

题目要求我们用两种操作来打出指定字符串。

- 操作一 可以打出任意字符；

- 操作二 可以复制任意长度的字符串。

两种操作可以打出的字符长度不同，显然操作二在复制长度 $ > 1$ 的字符串时相对于操作一更加简便。

所以我们需要找指定字符串中重复出现且长度为二的子串。

```python
    for i in range(len(string) - 1):
        if string.count(string[i:i+2]) > 1:
            cnt += 1
```

但是可以发现，在 `ABCCC` 这个字符串中虽然有两个重复子串，但并不可以用操作二打出。所以我们还需要对此情况进行特殊判断。

```python
    (i == len(string) - 2 or (string[i+2] != string[i+1] and string[i+1] != string[i]))
```

因为每使用一次操作二相当于使用了两次操作一，所以每使用一次操作二可以节省一次操作数，所以最终打出指定字符串所需的操作数为 $f(s) - cnt$ ，其中 $f(s)$ 为指定字符串的长度，$cnt$ 为重复出现且长度为二的子串的数量（即使用操作二的次数）。

## 代码

```python
T = int(input())
for i in range(T):
    cnt = 0 # 重复出现且长度为二的子串的数量
    # 输入
    n = int(input())
    string = input()
    # for 循环 枚举
    for i in range(len(string) - 1):
        if string.count(string[i:i+2]) > 1 and (i == len(string) - 2 or (string[i+2] != string[i+1] and string[i+1] != string[i])):
            cnt += 1
    # 输出
    if len(string) - cnt < n: print("YES")
    else: print("NO")
```


---

## 作者：yutong_Seafloor (赞：2)

# [题目在这里 · CF1766B Notepad#](https://www.luogu.com.cn/problem/CF1766B) 
**食用前提醒:
本题解更多倾向于 `map` 基础用法，大佬可以划了。**
### 题目简要：
现在我们有一个字符串，我们需要通过操作制作出另一个一样的字符串，操作有两种：
操作 $1$：在我们新建的字符串末尾添加字符串。
操作 $2$：复制我们前面的一部份内容粘贴到字符串末尾。
我们需要在小于给定的次数内成功制作出另一个字符串，问我们可以做到吗？
### 题意分析
结合样例，我们可以知道：不能只使用操作 $1$，这样绝对不够，操作 $2$ 才是关键，但前提是我们的样例字符串必须有两个相同的字串，这两个字串不光需要字串组成为连续，长度也需要大于 $2$，原因很简单：如果长度是 $1$ 的话那和操作 $1$ 差别不大，显示不出其优越性，具体看第三个样例，为了方便储存，我们需要 `map`，`map` 具体是什么呢？

`map` 是STL的一个关联容器，可以储存任何类型的数据，在使用 `map` 的时候需要 `include<map>`。

- 定义：`map<索引数据类型，指向数据类型> 名称`；
- 插入元素：
1. `名称.insert(map<索引数据类型, 指向数据类型>::value_type(关键字,“对应值”))；`
2. `名称.insert(pair<索引数据类型, 指向数据类型>(关键字,“对应值”))；`
3. 数组直接插入。

在以上三种方法中，方法 $1$，方法 $2$ 效果相同，方法 $3$ 可以直接覆盖原来的值。
- 大小获取：`？？？=名称.size();`
- 基本操作函数
`begin()`：返回指向 `map` 头部的第一个元素。

`end()`：返回指向 `map` 尾部的最后一个元素。

`find()`：查找一个元素。

`erase()`：删除一个元素。

`clear()`：清空 `map`。

`count()`：是否存在某元素，只会返回 $0$ 或 $1$。

`empty()`：`map` 是否为空。
## 代码 


```cpp 
#include<bits/stdc++.h>
using namespace std;
int t,n,i,j,pd;
string s1,s2;
int main()
{
	cin>>t;
	for(i=1;i<=t;i++)
	{
		pd=1;
		map<string,int> yt;
		cin>>n>>s1;
		for(j=0;j<n;j++)
		{
			string s2="";
			s2=s1[j-1];
			s2+=s1[j];
			if(!yt[s2])
			{
				yt[s2]=j;
				continue;
			}
			if(yt[s2]!=j-1 && yt.find(s2)!=yt.end())
			{
				cout<<"YES"<<endl;
				pd=0;
				break;
			}
		}
		if(pd) 
		cout<<"NO"<<endl;	
	}
	return 0;
}//by·yutong_Seafloor 
``` 
每日提醒：注意恢复初始值。

---

## 作者：cjh20090318 (赞：2)

大家好，我是 CQ-C2024 蒟蒻 CJH。

## 题意

给定一个字符串，有以下两个操作：

- 在字符串的结尾添加任何一个字母。

- 复制一个已经输入的字符串的连续子串，并将这个子串粘贴到字符串的结尾。

请用小于 $n$ 个操作，完成这个字符串。

## 分析

因为要小于 $n$ 次操作完成这个字符串，所以不可能每一次都添加单独一个字符或复制单独一个字符。

所以字符串必须要存在两个不重叠且长度大于 $1$ 的相同子串，这样才能保证可以少用一次操作就可以添加两个字符。

只需要用 `map<string,int>` 来记录每两个字符构成的子串第一次出现的位置，如果有出现过还需要判断这两个子串是否重叠。

## 注意事项

如果你的 `map` 定义在全局中，一定要**清空**。~~多测不清空，爆零两行泪。~~

## 代码

```cpp
//the code is from chenjh
#include<bits/stdc++.h>
using namespace std;
string s;
map<string,int> m;
void solve(){
	m.clear();//定义在全局中一定要清空！
	int n;scanf("%d",&n);
	cin>>s;
	string tmp;
	for(int i=0;i<n-1;i++){
		tmp=(char)s[i];
		tmp+=(char)s[i+1];//取出字符串的第 i 和 i+1 个字符，构成一个长度为 2 的子串。
		if(m.find(tmp)==m.end()) m[tmp]=i;//如果不存在这个字串则标记当前位置。
		else{
			if(m[tmp]!=i-1){//如果不重叠。
				puts("YES");
				return;
			}
		}
	}
	puts("NO");
}
int main(){
	int t;scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：qifan_maker (赞：1)

### 题目链接
[洛谷](https://www.luogu.com.cn/problem/CF1766B)

[Codeforces](https://codeforces.com/problemset/problem/1766/B)
### 题目解法
题目要求我们用小于 $n$ 次操作来打出长度为 $n$ 的字符串，仔细观察两种操作方法可以发现：

- 操作一是用 $1$ 次操作来打出 $1$ 个字符；
- 操作二是用 $1$ 次操作来打出 $x$ 个字符，$x$ 指可复制的长度。

如果 $x$ 为 $1$，此时操作一和操作二是等价的，并不能节省操作次数，所以只有在有两个及以上字符可复制的情况下，才能节省操作次数。

现在题目转变为了：求字符串中相同且长度大于 $1$ 的子串。

由于任一长度大于 $2$ 的子串都包含一个长度为 $2$ 的子串，所以题目又转变为了：求字符串中长度为 $2$ 的相同子串。

我们可以用 `map` 来储存这个子串有没有出现过，也就是桶的思想。

有一点需要注意，两个子串一定是不能重合的，例如字符串 `luooogu`，`ooo` 可能会被拆成 $[S_3,S_4]$ 和 $[S_4,S_5]$ 两个子串，所以我们需要判断一下。
### [AC](https://www.luogu.com.cn/record/119968619) Code
```
/*
Problem：
CF1766B Notepad#
By：
qifan_maker
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--){
		int n;
		string s;
		cin >> n >> s;
		s = ' '+s;
		map<string,int> t;
		bool flag = true;
		for (int i=1;i<s.size();i++){
			string temp = "";
			temp += s[i];
			temp += s[i+1];
			if (t[temp] and t[temp]+1<i){
				cout << "YES" << endl;
				flag = false;
				break;
			}
			else if (!t[temp]){
				t[temp] = i;
			}
		}
		if (flag){
			cout << "NO" << endl;
		}
	}
    return 0;
}
```

---

## 作者：_dijkstra_ (赞：1)

很容易想的一道题。

## 思路

我们发现，既然只需要操作次数小于 $n$，那么其实，我们**只需要找一组**长度为 $2$ 的相同的子串即可。

如果有更长的子串不用管，因为只用一个长度为 $2$ 的子串，就已经满足要求了。

想到这个就很容易了。不过注意，这两个子串**不能在同位置出现**。例如 $\texttt{IAKIII}$ 中，两个 $\texttt{II}$ 子串并不能组成一组，因为无法复制。

解决这个问题的方案也很简单：特判一下即可。

## 代码

为了方便直接用了 `map`。

```cpp
unordered_map <string, int> mp;
bool solve()
{
	mp.clear(); //多测，一定要记得清空！
	string s;
	int n;
	cin >> n >> s;
	for (int i = 0; i < n - 1; i++)
	{
		string t = s.substr(i, 2); //暴力截子串
		bool flag = mp.count(t);
		if (flag && mp[t] + 1 != i) return true; //如果之前已经出现过，并且不是重叠的，那么就完事了
		if (!flag) mp[t] = i;
	}
	return false;
}
```

---

## 作者：aCssen (赞：1)

### 题意
你可以对一个字符串 $p$ 进行如下两种操作（开始 $p$ 为空串）。
+ 在 $p$ 的末尾添加一个字符。
+ 将一个 $p$ 的连续子串复制到 $p$ 的末尾。

现在给你一个字符串，问能否在 $|s|-1$ 次操作内使 $p=s$
### Solution
令 $n=|s|$。

显然，我们可以在 $n$ 次操作内使 $p=s$，使用 $n$ 次操作一即可。

所以，如果想要减少操作次数，就必须使用操作二，且选择的字串长度要大于 $1$（否则还是不能减少操作次数）。钦定长度为 $2$，显然，这样不会影响答案。

更具体地，我们记录下每个长度为 $2$ 的连续子串**第一次**出现的位置 $p$，只要存在一个长度为 $2$ 的连续子串 $k$，满足它第一次出现的位置在它当前位置之前，即 $p_k \lt k$，就可以把上个子串复制过来，使操作次数小于 $n$。
### 细节
$p$ 记录的位置应是末尾的位置，因为两个相同子串不能有重合，例如 `aaa`，如果记录开头的位置就会认为第二个 `aa` 可以通过复制得到而得出错误答案。
### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<map>
using namespace std;
string s;
int t,n;
int main(){
	cin>>t;
	while(t--){
		map<string,int>p;
		bool f=false;
		cin>>n>>s;
		for(int i=0;i<s.size()-1;i++){
			string m="";
			m+=s[i];
			m+=s[i+1];
			if(p[m]<i&&p[m]) f=true;//m出现过且一定
			if(!p[m]) p[m]=i+1;//，如果没出现过，记录末尾
		}
		if(f) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：Night_sea_64 (赞：1)

纪念本蒟蒻第一次打的 CF 比赛！

字符串长度为 $n$，而我们的操作次数 $<n$ 就行了。如果我们每次都打出一个字符或者复制一个字符，操作次数肯定是 $n$ 次。

但是，我们只要确保至少有一次操作能打出一个以上的字符，操作次数肯定 $<n$。显然这次操作一定是复制操作。

于是我们看看 $s$ 中有没有：出现次数超过一次的两个字符的子串。为什么是两个字符呢？因为如果有更多字符的子串满足要求，那这个子串的子串都满足要求，而这个子串就一定会有两个字符的子串。

为了方便记录这个东西，我就开 map 记录了。

但是为了防止 `hhh` 的这种东西，被查到，我们存的不仅是这个字符串有没有出现，还要记录位置。

本蒟蒻的 AC 代码：

```cpp
#include<iostream>
#include<cstring>
#include<map>
using namespace std;
map<string,int>mp;//mp 记录字符串第一个字符的位置。
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        mp.clear();//注意要清空
        int n;
        bool flag=0;
        string s;
        cin>>n>>s;
        s=' '+s;//一定要前面空出来一个字符，因为 mp[s]=0 表示这个 s 没出现。
        for(int i=1;i<n;i++)
        {
            string tmp=s.substr(i,2);
            if(mp[tmp]<i-1&&mp[tmp])flag=1;
            if(!mp[tmp])mp[tmp]=i;
        }
        cout<<(flag?"YES":"NO")<<endl;
    }
    return 0;
}
```


---

## 作者：shinzanmono (赞：1)

# 题意：

给出一个字符串，请求出这个字符串中是否有两个不重叠的长度 $\geq2$ 的子串相同。

# Solution:
我们考虑两个长度 $\geq2$ 的相同子串中，必定有一个长度 $=2$ 的子串，所以我们把所有长度为 $2$ 子串枚举出来，统计一下是否有出现两次以上的即可。

结果你会发现：居然样例也过不去。

## 重点：$\downarrow$

我们看一下错误的字符串：`ouhhh`，发现如果按照如上算法，则会算出 `hh` 的出现次数为 $2$，但是实际上两个字符串有重叠，那么我们考虑如何更改。

对于每个子串，维护子串第一次出现的位置，如果当前子串的位置与是该子串出现位置的下一个位置，那么我们就忽略这个子串，然后再统计是否有出现两次以上的字符串即可。

# Code:
```cpp	
#include<iostream>
#include<string>
#include<map>
using piit = std::pair<int, int>; // 第一个数字为出现的次数，第二个为出现的第一个位置。
int main() {
    std::ios::sync_with_stdio(false);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::string s;
        std::cin >> n >> s;
        std::map<std::string, piit> dict;
        for (int i = 0; i < n - 1; i++) {
            if (dict[s.substr(i, 2)].first == 0) dict[s.substr(i, 2)].second = i;
            if (i != dict[s.substr(i, 2)].second + 1) dict[s.substr(i, 2)].first++;
        }
        bool flag = false;
        for (auto i: dict) {
            if (i.second.first >= 2) {
                flag = true;
                break;
            }
        }
        if (!flag) std::cout << "NO\n";
        else std::cout << "YES\n";
    }
    return 0;
}

```

---

## 作者：FQR_ (赞：1)

## 思路

不难想到，如果全选择“在字符串末尾添加一个字符”这个操作，需要操作 $n$ 次。

但是，如果使用了至少一次复制，且复制的字符串长度大于 $1$，就可以将操作次数减少。所以此时操作次数小于 $n$。

显然，当字符串拥有相同的子串，且子串长度大于 $1$，就可以在 $n$ 步以内完成。

还要判断一种情况：例如`aaa`，前后各有一个子串`aa`，但两个子串重合，因此不能在 $n$ 步以内完成。

## 代码思路

因为相同子串长度需要大于 $1$，所以我们只需判断是否有长度为 $2$ 的相同子串即可。

用一个二维的 map：`map<char,map<char,int> >a`，用来标记某个子串是否出现过。

其中，$a_{i,j}$（$i,j$是两个字符）表示以 $i$ 与 $j$ 组成的子串出现的位置。如果没有出现，则值为 $0$。

遍历每一个长度为 $2$ 的子串，判断这个子串是否被记录过。如果被记录过，还要判断两个子串是否重合。如果没被记录过，则记录它。

单次询问的时间复杂度为 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve()
{
	map<char,map<char,int> >a;
	int n;string s;cin>>n>>s;
	s.insert(s.begin(),' ');//将字符串整体向后移一位，方便记录
	for(int i=1;i<n;i++)
	{
		if(a[s[i]][s[i+1]])//如果被标记过
		{
			if(a[s[i]][s[i+1]]!=i-1)//判断是否重合
			{
				cout<<"YES"<<endl;
				return;
			}
		}
		else a[s[i]][s[i+1]]=i;//标记这个子串
	}
	cout<<"NO"<<endl;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--) solve();
	return 0; 
}
```

---

## 作者：yhx0322 (赞：0)

## 题目简述
给你一个整数 $n$ 和字符串 $s$，问：能不能在小于 $n$ 次操作的情况下，输出字符串 $s$。

有两次操作可供使用：
- 在已打出内容的最后添加一个字符。
- 复制已打出内容的一个连续的子串并加到内容的末尾。

## 思路
用到的容器：$\text{map}$。

用 $\text{map}$ 来记录每个子串出现的次数，然后求出字符串中长度为 $2$ 的相同字串个数。

附：$\text{map}$ 的简单介绍：

`map<key的数据类型, value的数据类型>`

它是 C++ 里的 STL 容器，底层用红黑树实现，如果需要 $\text{map}$ 需要 `include <map>。`

取 $\text{map}$ 里面元素的方法：`mp[key]`。

本题里面 $\text{map}$ 的函数介绍：

- `mp.find()` 查找元素(没找到返回 `mp.end()`)
- `mp.end()` 返回的是 $\text{map}$ **最后一个元素地址的下一个地址**，一定注意不是最后一个元素！

## 代码
```c++
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int t, n;
bool f;
string s1, s2;
map<string, int> mp;

int main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0); // 读入流优化
	cin >> t;
	while (t--) {
		mp.clear(); // 注意多组测试数据的情况下，一定看看哪些变量需要清空
		f = false;
		cin >> n >> s1;
		for (int i = 0; i < n; i++) {
			s2 = "";
			s2 = s1[i - 1];
			s2 += s1[i];
			if (!mp[s2]) { mp[s2] = i; continue; }
			if(mp[s2] != i - 1 && mp.find(s2) != mp.end()) { // 找到字符
				cout << "YES" << endl;
				f = true;
				break;
			}
		}
		if (!f) cout << "NO" << endl;
	}
	return 0;
}
```

---

## 作者：MuLinnnnn (赞：0)

[洛谷 题面](https://www.luogu.com.cn/problem/CF1766B) & [CodeForces 题面](https://codeforces.com/problemset/problem/1766/B)

**题意：**

给定 $T$ 组整数 $n$ 和字符串 $s$，求出是否在 $n$ 步能利用“新写”或“复制之前的连续子串”完成原串 $s$。

**思路：**

可以~~轻易~~看出，如果原串中有长度至少为 **2** 的大于等于 **2** 个的连续子串相同，那么就可以在 $n$ 步之内完成原串的书写。因为当有长度为 **2** 的子串时，我们可以使用一次“复制”将两次“新写”合并成一次，总步骤也就严格小于 $n$ 步了。这时，问题转化为了怎样求一个串中是否有相同连续长度大于等于 **2** 的子串。我们可以使用难一点的哈希（将子串压成一个数），但这里我用了比较偷懒但速度很慢的`map`。

取出子串我用了`s.substr(begin, len)`。`mp[tmp]`里存的是字符串 $tmp$ 出现的位置。


------------

`map`的定义：`map<类型，类型> mp;`。

`map`清空：`mp.clear();`。

`map`增加、修改元素：同普通数组，使用`mp[下标] = value`更改或添加。

`map`子串数量：`mp.count(s)`。

------------

**Accept Code：**

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
typedef long long ll;
#define endl '\n'
#define FAST ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
map< string, ll > mp;

int main(){
	FAST;

	ll T;
    cin >> T;
    while(T--){
    	mp.clear();
    	ll n;
    	cin >> n;
    	string s;
    	cin >> s;
    	bool flag = false;
    	for(ll i = 0; i < n - 1; ++i){
    		string tmp = s.substr(i, 2);
    		if(mp.count(tmp) >= 1 && mp[tmp] + 1 != i){ // 注意判断位置不同
    			cout << "YES" << endl;
    			flag = true;
    			break;
			}
			if(mp.count(tmp) == 0){
				mp[tmp] = i; // 记录下标
			}
		}
		if(!flag){
			cout << "NO" << endl;
		}
	}
	return 0;
}

```

---

## 作者：hao_zi6366 (赞：0)

## 题意简述

可以有两种操作：

- 在已打出内容的最后再打一个字符。
- 复制一段已打出内容的并加到内容的末尾。

要求在次数 $ < n $ 的情况下打出这个字符串。

## 题意分析

设我们进行的操作次数 $= a$，既然只要求在 $a < n$ 的次数下打出字符串，那么显然，只要 $a=n-1$ 就可以满足题目要求。

也就是说，我们只要找到两个字符串 $s_1 $ 和 $s_2$, 满足$s_1=s_2$ 和 $\lvert {s_1} \rvert = 2 $ 且 $ \lvert {s_2} \rvert = 2$，并且这两个字符串不重叠（长度更长的子串已经包含在长度为 2 的子串中了）。

那么不难想到，可以直接暴力查找，不过显然，这么直接做会超时。

然而，因为只要有一对像这样重复出现的子串就满足题目要求，我们可以进行优化：如果达到要求则跳出循环。

## 完整代码

```cpp
#include<bits/stdc++.h>
#define N 100005
typedef long long ll;

int main(){
	/*freopen("xxx.in","r",stdin);
	freopen("xxx.out","w",stdout);*/
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	
	int t;
	std::cin>>t;
	while(t--){
		int n;
		bool flag=0;
		std::cin>>n;
		std::string s;
		std::cin>>s;
		for(int i=0;i<n;i++){
			std::string s1=s.substr(i,2);		//裁剪出一个长度为2的字符串 
			for(int j=i+2;j<n;j++){
				std::string s2=(s.substr(j,2));	//在这个字符串后再裁一个长度为2的字符串
				if(s2==s1){						//如果找到相等的，标记并跳出循环 
					flag=1;break; 
				}
			}
		}
		std::cout<<(flag?"YES\n":"NO\n");
	}
	return 0;
}
```


---

## 作者：filletoto (赞：0)

### [题目](https://www.luogu.com.cn/problem/CF1766B)

## 思路
因为要在 $n$ 此操作内完成这个字符串，所以我们不可能每次操作只添加 $1$ 个字符。

我们看看 $s$ 中有没有出现次数超过 $1$ 次的两个字符的子串。

于是，我们可以用 `map<string,int>` 来记录长度为 $2$ 的每个子串第 $1$ 次出现的位置，如果有出现过还需要判两个子串是否重叠。

## 代码
```cpp
#include <iostream>
#include <string>
#include <map>
using namespace std;
int T,n;
string s;
map<string,int> mp;
int main()
{
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--)
	{
		cin>>n>>s;
		mp.clear();//注意要清空
		int f=1;
		for(int i=0;i<s.size()-1;i++)
		{
			string t=s.substr(i,2);//截取长度为2的子串
			bool flag=mp.count(t);//查找是否已经出现过
			if (flag&&mp[t]+1!=i) {puts("YES");f=0;break;}
			if (!flag) mp[t]=i;
		}		
		if(f) puts("NO");
	}



	return 0;
}
```

---

## 作者：Air_Color5 (赞：0)

# 题意
[CF1766B题目传送门](https://www.luogu.com.cn/problem/CF1766B)
# 分析
对于每一组数据，我们想在恰好 $n$ 步操作内打出这个字符串，其实是很简单的：只要把字符一个一个打出来就行了。但是题目要求是在**严格少于 $n$ 步内**完成，所以我们**必须使用至少一次复制一节长度大于2的字符串的操作**。那么这道题就转换成了：

**对于每一组数据，如果字符串中有两段不重合的子串，那么就输出 YES ，否则输出 NO 。**

这样一看，题目的解法就已经很明显了。我们将整个串遍历一遍，并且用 $cnt_{i,j}$ 记录下由字符 $i$ 和字符 $j$ 组成的长度为 $2$ 且不重合的子串出现的次数。接下来，我们再考虑有重合的情况。显然，如果有重合，则 $i$ 和 $j$ 必定是相同字符。因此，我们用 $last_i$ 记录由两个 $i$ 组成的子串最后一次出现位置，同时每次发现目前的子串两位字符相同（设都为 $i$ ），就检查 $last_i$ 数组中这个串的最后一次出现位置，如果没有和这个串重合，那就 $cnt_{i,i}$ 加 $1$ ，并在 $last_i$ 中记录现在位置。
# 代码
看到这里，想必大家都已经知道代码怎么写了。不过为了确保题解完整性，这里把代码和注释一同放上来。这份代码时间复杂度 $O(nt)$ ，其中 $t$ 为测试数据组数。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n; 
char cr[200005];
void solve(){
	scanf("%d%s", &n, cr); //输入 
	int cnt[26][26] = {}, last[26]; // cnt 数组和 last 数组 
	memset(last, -1, sizeof(last));
	// cnt 和 last 都别忘了初始化哦！ 
	for(int i = 1; i < n; i++){ // 遍历 
		if(cr[i] == cr[i - 1]){ // 判断当前两个字符是否相同 
			if(last[cr[i] - 'a'] == i - 1) // 如果有重合 
			continue; // 跳过 
			else last[cr[i] - 'a'] = i; // 记录当前位置 
		}
		cnt[cr[i - 1] - 'a'][cr[i] - 'a']++; // 记录出现次数 
	}
	for(int i = 0; i < 26; i++)
	for(int j = 0; j < 26; j++) // 遍历两个字符的所有组合 
	if(cnt[i][j] > 1){ // 如果有出现次数超过两次的 
		printf("YES\n"); //说明可以复制粘贴，此时答案为 YES  
		return ;
	}
	printf("NO\n"); // 说明没有可以复制粘贴的，此时答案为 NO 
}
int main(){
	scanf("%d", &t);
	while(t--)
	solve(); //多组测试数据 
	return 0; // 华丽地结束！
}
```
## 代码仅供参考

---

## 作者：BlackPanda (赞：0)

*[Problem](https://www.luogu.com.cn/problem/CF1766B)*

------------
## *Description：*

有两种操作：

- 在已打出内容的最后添加一个字符。

- 复制已打出内容的一个连续的子串并加到内容的末尾。

每次询问给出正整数 $n$ 和字符串 $s$，问是否可以在严格小于 $n$ 次操作内，由一个空串打出字符串 $s$。

------------
## *Solution：*

首先对于 $n$ 次操作，可以直接进行 $n$ 次添加操作，但是要想在 $n - 1$ 次操作之内完成，至少要进行一次复制操作，并且复制字串的长度大于 $1$（否则等同于一次添加操作）。

所以我们只需要查找字符串中是否有长度为 $2$ 的子串重复出现即可。

**这里需要注意：查找到的多个子串不能重叠。**

例如字符串 $aaab$，这里枚举到了两个 $aa$ 子串，但是该字符串无法在 $3$ 次以内完成。

------------
## *Code：*

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n;
string s;

int main()
{
    cin >> t;
    while (t -- )
    {
        cin >> n >> s;
        map<string, int> mp;
        bool f = 1;
        for (int i = 0; i < s.length(); i ++ )
        {
            string str = s.substr(i, 2);
            if (mp.find(str) != mp.end())
            {
                if (mp[str] == i - 1)   continue;
                else
                {
                    cout << "YES\n";
                    f = 0;
                    break;
                }
            }
            else
            {
                mp[str] = i;
            }
        }
        if (f)  cout << "NO\n";
    }
    return 0;
}
```

---

## 作者：tZEROちゃん (赞：0)

注意到只要让操作次数 $<n$ 就可以了，那如果是要求 $\le n$ 怎么做呢。

显然一个一个按就可以了对吧。

那么，这就意味着如果要降到 $<n$ 次，就 **至少** 需要一次「复制」操作。

换而言之，只要我们使用一次「复制」操作，就可以控制操作次数 $<n$。

那么，只需要找到有两个相同的，且长度大于等于 $2$ 的子串就可以了。

然后你发现是错误的，为什么呢？

考虑字符串 `kwww`，我们注意到即使 `ww` 子串符合「有两个相同的，且长度大于等于 $2$ 的子串」，但还是无法在 $<4$ 次内完成，所以又要增加一个条件，即，两个子串不重叠。

因此，结论是，**若有两个相同的，且长度大于等于 $2$ 的子串，且这两个子串不重叠，那么就是 `YES`，否则就是 `NO`**。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve() {
  string s; cin >> s >> s; s += '$';
  unordered_map<string, int> mp;
  for (int i = 0; i < (int)s.size() - 1; ++i) {
    string q; q += s[i]; q += s[i + 1];
    if (mp[q]) {
      if (mp[q] <= i - 1) { cout << "YES\n"; return ; }
    } else {
      mp[q] = i + 1;
    }
  }
  cout << "NO\n";
}

int main() {
  int q; cin >> q;
  while (q--) solve(); 
}
```

---

## 作者：loser_seele (赞：0)

首先观察到题目有用的能减少操作次数的操作只有复制，于是考虑复制怎么做。

不难发现，只有存在长度至少为 $ 2 $ 的子段的时候复制才有效，不然不如直接打字。

于是找出所有长为 $ 2 $ 的子段的出现次数，如果有一个子段出现不少于 $ 3 $ 次则显然有解，否则需要判断这个子段出现的位置是否重叠，如果重叠则形式类似于三个字母重复这样的形式，则打字出前两个字母后还是需要一次复制，不会减少操作次数，因此还需要判断这两个位置间的距离是否为 $ 1 $。

因为需要扫描整个数组一遍找到所有长度为 $ 2 $ 的子串，所以总时间复杂度 $ \mathcal{O}(n) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int a[20000020],ans=0;
void gen(int n)
{
int f[2000020];
for(int i=1;i<=n;i++)
f[i]=i;
do
{
if(0)//add something here.
ans++;
}while(next_permutation(f+1,f+n+1));
}
#define Y cout<<"Yes"<<'\n'
#define N cout<<"No"<<'\n'
int check(int n)
{
int cnt=0;
while(n)
{
if(n%10)
cnt++;
n/=10;
}
return cnt==1;
}
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		string s;
		cin>>s;
		map<string,int>p;
		int cnt=0;
		vector<int>g[n+1];
		for(int i=1;i<n;i++)
		{
			string t=s.substr(i-1,2);
			if(!p[t])
				p[t]=++cnt;
			g[p[t]].push_back(i);
		}
		bool ok=0;
		for(int i=1;i<=n;i++)
			if(g[i].size()>=3||(g[i].size()==2&&abs(g[i][0]-g[i][1])!=1))
				ok=1;
		if(ok)
			cout<<"YES\n";
		else
			cout<<"NO\n";
	}
}
```


---


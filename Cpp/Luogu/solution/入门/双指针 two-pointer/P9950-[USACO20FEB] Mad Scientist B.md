# [USACO20FEB] Mad Scientist B

## 题目描述

Farmer John 的远房亲戚 Ben 是一个疯狂的科学家。通常这会在家庭聚会时造成不小的摩擦，但这偶尔也会带来些好处，尤其是当 Farmer John 发现他正面对一些有关他的奶牛们的独特而不寻常的问题时。

Farmer John 当前正面对一个有关她的奶牛们的独特而不寻常的问题。他最近订购了 $N$ 头奶牛（$1\le N\le 1000$），包含两种不同品种：荷斯坦牛和更赛牛。他在订单中用一个长为 $N$ 的字符串来指定奶牛，其中的字符为 `H`（表示荷斯坦牛）或 `G`（表示更赛牛）。不幸的是，当这些奶牛到达他的农场，他给她们排队时，她们的品种组成的字符串与原先的不同。

我们将这两个字符串称为 $A$ 和 $B$，其中 $A$ 是 Farmer John 原先想要的品种字符组成的字符串，$B$ 是他的奶牛们到达时组成的字符串。Farmer John 并没有简单地检查重新排列 $B$ 中的奶牛是否能得到 $A$，而是请他的远房亲戚 Ben 利用他的科学才华来解决这一问题。

经过数月的研究，Ben 发明了一台不同寻常的机器：奶牛品种转换机 3000，能够选择任意奶牛组成的子串并反转她们的品种：在这个子串中的所有 `H` 变为 `G`，所有 `G` 变为 `H`。Farmer John 想要求出将他当前的序列 $B$ 变为他本来订购时想要的 $A$ 需要使用这台机器的最小次数。然而，Ben 的疯狂的科学家技能并不会处理开发奇异机器以外的事，所以你需要帮助 Farmer John 解决这个计算难题。 

## 说明/提示

### 样例解释 1

首先，FJ 可以仅改变第一个字符组成的子串，将 $B$ 变为 `GHGGGHH`。然后，他可以改变由第三和第四个字符组成的子串，得到 $A$。当然，还存在其他有效的执行两次操作的方案。 

## 样例 #1

### 输入

```
7
GHHHGHH
HHGGGHH```

### 输出

```
2```

# 题解

## 作者：nightwatch.ryan (赞：10)

### 思路
求这两个字符串中有多少个连续的子串不同。枚举 $A$ 和 $B$ 这两个字符串，首先特判第一个字符，如果 $A$ 和 $B$ 的第一个字符一样，答案直接加一。如果 $A$ 的第 $i$ 个字符和 $B$ 的第 $i$ 个字符不一样，并且 $A$ 的第 $i-1$ 个字符和 $B$ 的第 $i-1$ 个字符一样，答案加一。
### 代码
```cpp
#include<iostream>
#include<string>
int n,res;
std::string a,b;
int main(){
	std::cin>>n>>a>>b,res=0;
	for(int i=0;i<n;i++)
		if(a[i]!=b[i] and i==0)res++;//第一个字符不同一定要变
		else if(a[i]!=b[i] and a[i-1]==b[i-1])res++;//当前字符不相同，但是前一个字符相同（说明前一个字符不用变）答案+1
	std::cout<<res;
}
```


---

## 作者：ny_Dacong (赞：5)

这是一道双指针的题目。

我们采用贪心的思想。

* 如果 $A_i \neq B_i$，那这一位就需要变化。如果它前面一位也要变化，那我们可以把这一位连着前面一位**一起变化**。

* 如果 $A_i = B_i$，那么我们是**绝对不能变化这一位的**。因为这一位已经符合条件，如果我们变化了这一位，那么我们肯定还要再变一次来还原。这样无疑是浪费的。

那么具体的编程方法，我们可以采用**快慢指针**的编程方法。

我们先用一个快指针依次枚举第 $i$ 位，判断是否符合条件。比较难处理的条件是：

> 如果它前面一位也要变化，那我们可以把这一位连着前面一位**一起变化**。

所以我们需要一个慢指针，来记录变换区间的起点。接下来快乐模拟就行了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,ans = 0;
char a[1005],b[1005];
int main(){
	scanf("%d",&n);
	scanf("\n%s\n%s",a,b);//别忘了吃掉换行符
	l = -1;
	for(int i = 0; i < n; i++){
		if(a[i] == b[i]){
			if(l != i-1){
				ans++;
			}
			l = i;
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Addicted_Game (赞：5)

# [传送门](https://www.luogu.com.cn/problem/P9950)

## 题目大意
给定两个字符串（只包含 **H** 与 **G**），一次操作可以选择择一个区间的字符转换为另一种字符，问最少几次操作可以让第一个字符串变为第二个字符串。

## 思路
只需要暴力枚举就可以了，先从开始枚举到结束，如果两个字符串对应的位置不同，那没就要进行变换，而如果后面也不一样，就可以一次变换为第二个字符串。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n;
string s1,s2;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	cin>>s1>>s2;
	int sum=0;
	bool j=false;//是否已经改变
	for(int i=0;i<n;i++){//枚举没个位置
		if(s1[i]==s2[i]){//相同
			j=false;
			continue;
		}
      if(!j){
			j=true;
			sum++;//不是新的改变次数，计数加一
		}
	}
	cout<<sum;
	return 0;
}
```


---

## 作者：wei2013 (赞：4)

## 题目大意：
两个长度为 $n$ 的字符串，要把第一个变成第二个，可以一次更改一整条连续的需要修改的子串，最少要改几次。
## 思路：
直接暴力模拟，统计出每一段的最长需修改的子串，直到不同时，答案加 $1$，再从不同的地方开始统计下一段，就可以了。
## code：
```cpp
#include <bits/stdc++.h>
using namespace std;
string a,b;
int main(){
	int n,ans=0;
	cin>>n;
	cin>>a>>b;
	for(int i=0;i<n;i++){
		if(a[i]!=b[i]){// 当需要修改时
			for(int j=i;j<n;j++){
				if(a[j]==b[j]){// 统计需要修改的最长子串
					ans++;
					i=j;// 从相同的地方继续统计下一段
					break;
				}
			}
		}
	}
	cout<<ans;
   return 0;
}
```


望审核通过！

---

## 作者：watergod (赞：3)

# P9950 [USACO20FEB] Mad Scientist B 题解

~~这题感觉很水。~~

## 题目大意

可以粗略的理解成，给定两个字符串，去求这两个字符串中有多少个连续的子串不同，最后输出个数。

## 题目思路

我们可以直接暴力。

循环遍历每个字符，如果两个字符串中这个下标的字符是一样的，就直接跳过；如果不一样，则从这一个下标开始往后遍历，不一样则继续遍历，一样则 $ans$ 加 $1$。

详细分析在代码里

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n;
long long ans;
char a[114514],b[114514]; 

int main(){
	// 输入 
	cin >> n;
	for(register int i=1;i<=n;i++){
		cin >> a[i];
	}
	for(register int i=1;i<=n;i++){
		cin >> b[i];
	}
	// 遍历每一个字符判断  
	for(register int i=1;i<=n;i++){
		// 相同则不需要转变  
		if(a[i] == b[i]){
			continue;
		}
		for(register int j=i;j<=n;j++){
			// 不相同，如果下一个字符也不相同，说明不相同的连续子串还没有结束，继续遍历 
			if(a[j] != b[j]){
				continue;
			}else{
				// 相同则说明这一个子串需要转变，将遍历下标设为这个子串的下一位 
				ans++;
				i = j-1;
				break;
			}
		}
	}
	cout << ans << endl;
	return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/140204896)

---

## 作者：Fa_Nanf1204 (赞：2)

## string 大法好！！！
### 题意简述
给定两个字符串 $A$ 和 $B$，一次操作可以将一个区间内的 `H` 变成 `G` 或者 `G` 变成 `H`，求最少需要几次操作才可以让 $B$ 变为 $A$。
- - -
### 分析
我们可以用 string 数组存下两个字符串，因为两个字符串长度相同，所以我们可以遍历字符串来计算最少的操作。
- - -
### 具体思路
每次判断字符串 $A_i$ 和 $B_i$ 是否相同，如果不同则一直向后判断，直到两个字符相同为止，那么这样就算一次操作了，之后再统计操作次数就是最后的答案了。
- - -
### 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,s1;//建数组 
int len,sum=0;
int main(){
    cin>>len;
    cin>>s>>s1;//输入 
    for (int i=0;i<len;){
		if (s[i]!=s1[i]){   //判断 
			sum++;  //计答案 
			while(s[i]!=s1[i]){   //一直向后判断 
				i++;
			}
		}
		else{
			i++;
		}
    }
    cout<<sum;//输出 
    return 0;
}
```

---

## 作者：huangzhixia (赞：2)

**[题目传送门](https://www.luogu.com.cn/problem/P9950)**

## 题意
 
给我们两个字符串，字符串中只有两种字符 H 与 G，现在我们有一个操作，可以让随意一个区间中的字符（H 或 G）转换成另外一种字符。

如下：

- 当这个字符为 H 时，将它变成 G。
	
- 当这个字符为 G 时，将它变成 H。 
	
现在我们要求最少用几次这个操作可以让第一个字符串变得跟第二个字符串长得一样?

## 思路 
我们暴力枚举每个区间，先从最开始的区间再到结束。 

这是我们看看如果两个字符串对应第 $i$ 个位置不同的话，就要进行一次操作，再看看后面第 $i+1$ 个位置也不一样，就让我们这一次操作变换两个字符。  
	
之后就看下去，直到我们当前位置的字符在这两个字符串里都相同。 

## code

```c
#include <bits/stdc++.h>

using namespace std;
           
bool ok; //看看我们是否已经操作了。 
           
int n, ans;

string s, c;

int main(){
	scanf("%d", &n);
	cin >> s >> c;
	for (int i = 0; i < n; i++){ //枚举，string 是从 0 开始读入的。  
		if (s[i] == c[i]){ //如果第 i 个位置上的字符相同。 
			ok = false; //还没操作。 
			continue; //走人。    			
		}
		if (ok == false){
			ok = true; //现在已经当前位置不相同了，所以要进行操作。 
			ans += 1; //要操作的次数加 1。 
		}
	}
	printf("%d\n", ans);
}
```


---

## 作者：lbh666 (赞：2)

## 题目大意
给你两个只包含 **H** 和 **G** 的字符串，每次操作可以选择一个区间的字符转换成另一种字符，求第一个字符串最少要多少次操作才能变成第二个字符串。

## 思路分析
- 不妨采用暴力枚举的方式，去找每一个不匹配的字符串区间的长度，如果遇到一个位置的两个字符相同，那就说明这个不匹配的字符串区间结束了，答案加上 $1$ 即可。

- 具体见代码。

## 代码实现
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n,ans=0;
string s,s2;
bool flag=0;

int main(){
	int n;
	cin>>n>>s>>s2;
	for(int i=0;i<n;++i){
		if(s[i]==s2[i]){
			flag=0;//flag=0代表当前不匹配的区间已结束 
			continue;
		}
		if(!flag){//如果这两个字符不相同且上一个区间已结束，那就新增一个区间 
			flag=1;//两个字符不匹配时flag=1 
			++ans;//更新区间数 
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：nominater (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P9950)
### 题意
将字符串 $A$ 转换为 $B$，其实就是求这两个字符串中有几个子串完全不同。
### 思路
只需要暴力枚举子串即可，判断字符是否相同，如果相同便继续遍历。若不同，则从此字符开始，向后遍历。
### 代码
```
#include<bits/stdc++.h>
#define int register int
using namespace std;
typedef long long ll;
const int N=1e3+10;
ll n,ans;
char a[N],b[N]; 
signed main()
{
	//ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin >> n;
	for(int i=1;i<=n;i++)
		cin >> a[i];
	for(int i=1;i<=n;i++)
		cin >> b[i]; 
	for(int i=1;i<=n;i++)
	{ 
		if(a[i] == b[i]) continue;
		for(int j = i; j <= n ; j + +)
		{
			if(a[j] != b[j]) 
				continue;
			else
			{
				ans++,i = j - 1;
				break;
			}
		}
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：DHT666 (赞：2)

## 题意

[传送门](https://www.luogu.com.cn/problem/P9950)

给出两个长度为 $N$ 且只包括 `H` 或 `G` 的字符串，每次可以把**一段区间**内的字符取反，求从字符串 $A$ 变化到 字符串 $B$ 的最小次数。

## 思路

考虑暴力完成该题，我们在字符串 $A$ 中从头遍历到尾，依次考虑每个字符：

- `a[i] == b[i]`，这种情况不需变化，直接跳过。
- `a[i] != b[i]`，需要变化，于是新开一个区间来变化字符。从 $i$ 向后遍历，直到出现一个字符不需变化停止。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
string a,b;
int main() {
	cin>>n>>a>>b;
	for(int i=0;i<n;i++) {
		if(a[i] == b[i]) continue; // 不需变化
		for(int j=i+1;j<n;j++) { // 从 i 向后遍历
			if(a[j] == b[j]) { // 出现字符不需变化
				ans++; // 累加答案
				i = j - 1; // 设置新的 i 
				break;
			}
		}
	}
	cout<<ans;
	return 0;
}
~~~

完结撒花~

---

## 作者：201012280925LSY (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/P9950)
## 题意
比较两个字符串，输出字符串 $A$ 和 字符串 $B$ 的不同字符连续段个数

## 思路
用一个 bool 类型变量表示当前字符是否在连续不同字符上，如果是第一个字符，答案累加。

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string x,y;
long long n,answer;
bool flag=0;
int main()
{
	ios::sync_with_stdio(false);//关闭同步流
	cin.tie(0);
	cout.tie(0);
	cin>>n;//字符串长度
	cin>>x>>y;
	x=' '+x;//字符串从1开始
	y=' '+y;
	for(int i=1;i<=n;i++)
	{
		if(x[i]!=y[i]&&flag==0)//如果是不同，且是第一个字符
		{
			answer++;//答案累加
			flag=1;
		}
		else if(x[i]==y[i])//相等flag=0
		{
			flag=0;
		}
	}
	cout<<answer;//输出答案
	return 0;
} 
```

---

## 作者：封禁用户 (赞：1)

## 题意简述
给定两字符串 $A$ 与 $B$，可以将 $B$ 的一个区间内的 `H` 变成 `G`，`G` 变成 `H`，使得 $A$ 与 $B$ 每一个字符都相同，问最小操作次数。
- - -
## 样例解释
将 $B_0$ 进行操作，`G` 变成 `H`。

再操作 $B_2$ 到 $B_3$ 的区间，里面所有的 `H` 均变成 `G`。

两次操作后，$A$ 为 $\texttt{GHHHGHH}$，$B$ 为 $\texttt{GHHHGHH}$，两串一样，故只要两次。
- - -
## 分析
我们可以从左到右扫一遍：若这个字符需要变化，就开始区间；若这里不用变化，就结束区间并将该区间计入答案。

所以我们可以搞一个标记变量来记录区间是否结束。

时间复杂度：$\mathcal{O}(N)$。
- - -
## AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;//ans 是答案
char a[1001],b[1001];
bool flag=0;//flag 是区间是否结束
int main(){
    cin>>n>>a>>b;
    for(int i=0;i<n;i++){//char 数组从零开始
		if(a[i]==b[i])flag=0;//这里需要变换，所以区间开始 
		else if(!flag)flag=1,ans++;//结束区间并记录答案 
    }cout<<ans; 
    return 0;
}
```

---

## 作者：WsW_ (赞：1)

难度约为橙。

---
### 思路
贪心。  

对于某个 $i$：
* 如果 $A_i=B_i$，我们**一定不能变 $i$ 位置**。  
* 如果 $A_i\neq B_i$，我们**一定要变 $i$ 位置**。  

每次操作能把连续的一段全部改变，所以答案为：  
一共有多少段 $[l,r]$，满足 $\forall i \in[l,r],A_i\neq B_i$。  

对于程序实现，当 $A_i=B_i$ 时，$i\gets i+1$，直到 $A_i\neq B_i$。  
再一直往后跳，直到再次出现 $A_i=B_i$。  
这样跳一轮就找到了一段相同的和一段不同的。操作数加一。

遍历一遍即可，时间复杂度 $O(n)$。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
string a,b;
int ans;
int p;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>a>>b;
	while(p<n){
		while(p<n&&a[p]==b[p])++p;//相同，一直跳
		if(p==n)break;//如果已经跳到了结尾就退出
		while(p<n&&a[p]!=b[p])++p;//不同，一直跳
		++ans;
	}
	cout<<ans;
	return 0;
}
```

---


# 『MGOI』Simple Round I | B. 魔法照相馆

## 题目背景

> 照片留下了值得留恋的瞬间，但对于魔法士来说最重要的是向前看。——殿堂魔法士 W

## 题目描述

小 M 正在准备入学所必需的魔法士证件，因此他来到了纵深巷的魔法照相馆。

在等待的时候，小 M 注意到魔法照相馆有三个幕布，颜色从左到右分别是红色、蓝色和白色。店主 zx 先生会根据客人的需求拉上或拉下这三个幕布，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/vpo182he.png)

幕布摆放在左边，按照红蓝白的顺序排列。人则坐在幕布右边，而 zx 先生则站在最右边给人拍照。幕布从右往左数，第一个没有拉上的幕布颜色将成为照片的背景颜色。

每次 zx 先生拉上或拉下一个幕布都需要消耗一个时间单位，而拍照不消耗时间。小 M 已经知道了他前面所有总共 $n$ 个客人的需求。在初始状态为 **全部拉下** 的情况下，请你帮助小 M 计算他至少需要等待多少个时间单位。

## 说明/提示

**【样例 1 解释】**

开始三个幕布是全部拉下的。

- 第一位客人要求蓝色，所以拉上白色，消耗一个时间单位。
- 第二位客人要求蓝色，无需改动。
- 第三位客人要求红色，所以在之前基础上拉上蓝色，消耗一个时间单位。
- 第四位客人要求白色，所以拉下白色，消耗一个时间单位。
- 第五位客人要求蓝色，所以拉上白色，拉下蓝色，消耗两个时间单位。

共计消耗五个时间单位。

**【数据范围】**

本题共有五个测试点。

| 测试点编号 | $n =$ | 特殊性质 |
| :------------: | :----------: | :----------: |
| $1$ | $1$ | 无 |
| $2$ | $1000$| 有 |
| $3$ | $1000$ | 无 |
| $4$ | $10^5$ | 有 |
| $5$ | $10^5$ | 无 |

特殊性质：只出现 `W` 和 `B` 两种颜色。

## 样例 #1

### 输入

```
5
BBRWB```

### 输出

```
5```

## 样例 #2

### 输入

```
10
BBBBBBBBBB```

### 输出

```
1```

# 题解

## 作者：lemon_qwq (赞：10)

一开始写了个 $70$ 多行分讨，找了好久没找到错误，但是 $60$ 分。

但是好像不用那么麻烦。

直接用三个布尔类型的变量模拟这三个幕布即可。

对于客人需求的幕布，判断这个幕布是否拉下，如果否，则计数器加 $1$，拉下这个颜色的幕布。

然后根据颜色判断位置，判断这个幕布图层之上的幕布是否拉上，如果没拉上，改没拉上的幕布的状态，计数器加 $1$。

代码仅供参考，讲的和写的有点细微的差别，讲的思路应该比写的更简单点。


```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int ans,n;
bool a[3];//w b r
int main(){	
	a[0]=1,a[1]=1,a[2]=1;
	cin>>n;
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]=='W'){
			if(!a[0]){
				ans++;
				a[0]=!a[0];
			}
		}else if(s[i]=='B'){
			if(a[0]){
				ans++;
				a[0]=!a[0];
			}
			if(!a[1]){
				ans++;
				a[1]=!a[1];
			}
		}else{
			if(a[0]){
				ans++;
				a[0]=!a[0];
			}
			if(a[1]){
				ans++;
				a[1]=!a[1];
			}
			if(!a[2]){
				ans++;
				a[2]=!a[2];
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Lemon_zqp (赞：9)

### 思路
这道题简单判断一下就可以了，只要先看在这块幕布前面的幕布有没有放下来，放下来了就花费 $1$ 个时间来把这块幕布拉上去，然后再判断一下当前这块幕布有没有拉下来，如果没有就再花费 $1$ 个时间单位拉下来即可，最后输出一共要几个时间单位即可。
### 代码
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
	int n;
	ll cnt = 0;
	bool if_b = true, if_r = true, if_w = true;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		char a;
		cin >> a;
		if(a == 'B')
		{
			if(if_w)//拉上前一块幕布 
			{
				cnt++;
				if_w = false;
			}
			if(!if_b)//拉下当前的幕布 
			{
				cnt++;
				if_b = true;
			}
		}
		else if(a == 'R')
		{
			if(if_w)//拉上前一块幕布 
			{
				cnt++;
				if_w = false;
			}
			if(if_b)//拉上前一块幕布 
			{
				cnt++;
				if_b = false;
			}
			if(!if_r)//拉下当前的幕布 
			{
				cnt++;
				if_r = true;
			}
		}
		else
		{
			if(!if_w)//拉下当前的幕布 
			{
				cnt++;
				if_w = true;
			}
		}
	}
	cout << cnt;
	return 0;
}


```


---

## 作者：qwerty_____ (赞：8)

这道题是一道**模拟**题，坑点不多，但是**细节特多**，所以导致大部分人 $A$ 不了这道题。这道题我也写了注释，如果思路没明白可以看代码和注释的。

先创建一个长度为 $3$ 的字符串 $s1$ ，这个字符串的意思就是模拟现在的这几个幕布的情况，这里分了四个字符代表着四种情况，详细如下

- 该字符串 $s1$ 下标为 $0$ 时该元素若为 `R` 则代表**最左侧**的颜色为**红色的幕布**被拉下。
- 该字符串 $s1$ 下标为 $1$ 时该元素若为 `B` 则代表**中间**的颜色为**蓝色的幕布**被拉下。
- 该字符串 $s1$ 下标为 $2$ 时该元素若为 `W` 则代表**最右侧**的颜色为**白色的幕布**被拉下。
- 该字符串 $s1$ 任意下标内的元素里面若为 `N` 则代表幕布被拉上去。

要注意，字符串 $s1$ 的定义必须是 `s1 = "RBW";` 这样才能满足题目对于幕布的顺序要求。

之后我们完成基本的输入， $n$ 是指接下来客人们要求的幕布颜色个数， $s$ 则是个字符串，用来存储客户要求的幕布颜色，别忘了定义一个变量 $times$ ，注意别定义成 $time$ ，这样会编译错误，因为会和 $time$ 函数冲突。

正式开始模拟！先创建个循环，遍历一下字符串 $s$ ，如果 $s$ 为 $W$ ，则要判断 `s1[2]` 是否为 $N$ ，如果是，则代表着幕布已拉上，需要花费 $1$ 个单位时间拉下，之后要更新 `s1[2]` 为 `W` ，如果不是 `N` 则什么也不用做，如果你实在想做点什么，只需要写一个 `time += 0;` 即可，这样你回顾代码的时候也能看得更明白。

其他情况也比较类似，只不过要判断右边的那个幕布是否拉下，如果拉下则又要花费一个单位时间拉上去，因为会挡住你要用的那个幕布，如果还是不明白，我的代码也有注释，可以搭配代码理解。最后，有问题请私信我，不要在底下评论。

```cpp
#include <iostream>
#include <string>
using namespace std;
int n, len, times = 0;
string s, s1;
int main(){
    cin >> n >> s;
    len = s.length();
    s1.resize(3);
    s1 = "RBW"; //当前的幕布状态
    for(int i = 0; i < len; i++){
        if(s[i] == 'W'){ //如果客户要求是W
            if(s1[2] == 'W') times += 0; //如果最右边已经拉下了，拍照
            else if(s1[2] == 'N'){ //如果最右边没被拉下
                times++;
                s1[2] = 'W'; //那就拉下去
            }
        }
        else if(s[i] == 'B'){ //如果客户要求是B
            if(s1[2] == 'W'){ //如果最右边被拉下
                times++;
                s1[2] = 'N'; //拉上去
                if(s1[1] == 'B') times += 0; //如果中间被拉下，拍照
                else if(s1[1] == 'N'){ //如果没有
                    times++;
                    s1[1] = 'B'; //那就拉下去
                }
            }
            else if(s1[2] == 'N'){ //如果最右边没被拉下，就不必管了
                if(s1[1] == 'B') times += 0; //如果中间被拉下，拍照
                else if(s1[1] == 'N'){ //如果没有
                    times++;
                    s1[1] = 'B'; //那就拉下去
                }
            }
        }
        else if(s[i] == 'R'){ //如果客户要求是R
            if(s1[2] == 'W'){ //如果最右边被拉下
                times++;
                s1[2] = 'N'; //拉上去
                if(s1[1] == 'B'){ //如果中间被拉下
                    times++;
                    s1[1] = 'N'; //拉上去
                    if(s1[0] == 'R') times += 0; //如果最左边被拉下，拍照
                    else if(s1[0] == 'N'){ //若没有
                        times++;
                        s1[0] = 'R';
                    }
                }
                else if(s1[1] == 'N'){ //如果没被拉下
                    if(s1[0] == 'R') times += 0; //如果最左边被拉下，拍照
                    else if(s1[0] == 'N'){ //若没有
                        times++;
                        s1[0] = 'R';
                    }
                }
            }
            else if(s1[2] == 'N'){ //若没被拉下
                if(s1[1] == 'B'){ //如果中间被拉下
                    times++;
                    s1[1] = 'N'; //拉上去
                    if(s1[0] == 'R') times += 0; //如果最左边被拉下，拍照
                    else if(s1[0] == 'N'){ //若没有
                        times++;
                        s1[0] = 'R';
                    }
                }
                else if(s1[1] == 'N'){ //如果没被拉下
                    if(s1[0] == 'R') times += 0; //如果最左边被拉下，拍照
                    else if(s1[0] == 'N'){ //若没有
                        times++;
                        s1[0] = 'R';
                    }
                }
            }
        }
        // cout << times << "->";
    }
    cout << times;
    return 0;
}
```

---

## 作者：WsW_ (赞：7)

### 思路：
把红、蓝、白分别用 $1,2,3$ 代替。  
如果要让 $1$ 露出，那么 $2,3$ 必须拉上去。如果要让 $2$ 露出，那么 $3$ 必须拉上去。  
这就非常类似于一个单调栈，我们直接用栈模拟即可。  

设栈顶颜色为 $top$，对于每次要一个颜色 $x$，存在如下三种情况:  
* $top=x$ 无需任何操作。
* $top<x$ 直接拉上 $x$ 即可。
* $top>x$ 不断弹出栈顶，直到 $top\le x$。

**注意，一开始三个颜色都是已经被拉下的，操作前要把 $1,2,3$ 依次加入栈。**

---
### 代码和[提交记录](https://www.luogu.com.cn/record/119365655)
```cpp
#include<bits/stdc++.h>
using namespace std;
stack<int>s;
int n,x;
int cnt;
char c[100003];
int main(){
	scanf("%d",&n);
	cin>>c;
	s.push(1);
	s.push(2);
	s.push(3);
	for(int i=0;i<n;i++){
		if(c[i]=='R')x=1;
		if(c[i]=='B')x=2;
		if(c[i]=='W')x=3;
		while(!s.empty()&&s.top()>x){
			cnt++;
			s.pop();
		}
		if(s.empty()||s.top()<x){
			s.push(x);
			cnt++;
		}
	}
	printf("%d",cnt);
	return 0;
}
```

---

## 作者：LegendaryGrandmaster (赞：6)

设三种幕布**拉下**的状态为 $1$，**拉上**的状态为 $0$，依次按每次遇到的幕布分类讨论即可。

**以下省略幕布二字。**

1. 白：如果白是拉上状态，花费一时间单位，白拉下。

2. 蓝：如果白是拉下状态，花费一时间单位，白拉上；如果蓝是拉上状态，花费一时间单位，蓝拉下。

3. 红：如果白是拉下状态，花费一时间单位，白拉上；如果蓝是拉下状态，花费一时间单位，蓝拉上；如果红是拉上状态，花费一时间单位，红拉下。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool a[3]={1,1,1};
signed main()
{
	int n;
	string st;
	cin>>n>>st;
	int ans=0;
	for(int i=0;i<st.size();i++){
		if(st[i]=='W')
			if(!a[0])a[0]=1,ans++;
		if(st[i]=='B'){
			if(a[0])a[0]=0,ans++;
			if(!a[1])a[1]=1,ans++;
		}
		if(st[i]=='R'){
			if(!a[2])a[2]=1,ans++;
			if(a[1])a[1]=0,ans++;
			if(a[0])a[0]=0,ans++;
		}
	}
	cout<<ans;
}
```

---

## 作者：_colin1112_ (赞：5)

## 思路

本题是一道简单的模拟题，只需要一个一个遍历使用 `if` 嵌套进行判断即可。

如果是白色，直接一个 `if` 判断幕布是否拉起，如果是，就不用操作，反之则时间单位 $+1$ 即可。

其他颜色一样操作即可。

## AC Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E=1e6+5;
ll n,cnt=0;
string arr;
bool r=1,b=1,w=1;
int main(){
	cin >>n;
	cin >>arr;
	for(int i=0;i<n;i++){
		if(arr[i]=='W'){
			if(w==1){
				
			}
			else{
				cnt++;
				w=1;
			}
		}
		if(arr[i]=='B'){
			if(w==1){
				cnt++;
				w=0;
				if(b==0){
					b=1;
					cnt++;
				}
			}
			else{
				if(b==0){
					b=1;
					cnt++;
				}
			}
		}
		if(arr[i]=='R'){
			if(w==1){
				cnt++;
				w=0;
				if(b==1){
					cnt++;
					b=0;
					if(r==0){
						cnt++;
						r=1;
					}
				}
				else{
					if(r==0){
						cnt++;
						r=1;
					}
				}
			}
			else{
				if(b==1){
					cnt++;
					b=0;
					if(r==0){
						cnt++;
						r=1;
					}
				}
				else{
					if(r==0){
						cnt++;
						r=1;
					}
				}
			}
		}
		
	}
	cout <<cnt;
    return 0;
}
```

~~话说我是不是做的太复杂了~~

---

## 作者：残阳如血 (赞：3)

一道简单的模拟题~~尽管我花了好久才写出来~~。
# 思路分析
我们可以知道，如果想让背景为某个颜色，那么颜色前面的所有幕布都需要被拉起来，而这个颜色的幕布则需要被放下。

所以我们对于每次操作，只需检查一遍它前面的幕布和这块幕布的状况即可。
# 程序实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[3];
// a数组记录幕布的状态，1表示没拉上，0表示拉上了
// a[0]代表白色，a[1]代表蓝色，a[2]代表红色
int main() {
	int n, ans = 0; // 非全局变量一定要清零！
	string str;
	cin >> n >> str;
	a[0] = a[1] = a[2] = 1; // 初始化状态为全部没拉上
	for (auto ch : str) {
		switch (ch) {
		case 'B':
			ans += a[1] == 0; // 是否拉上了
			// 因为==优先级比+=高，所以可以这样写
			ans += a[0] == 1; // 是否没拉上
			a[0] = 0, a[1] = 1; // 修改状态
			// 其他的大同小异，以此类推即可
			break;
		case 'R':
			ans += a[2] == 0;
			ans += a[1] == 1;
			ans += a[0] == 1;
			a[0] = a[1] = 0, a[2] = 1;
			break;
		case 'W':
			ans += a[0] == 0;
			a[0] = 1;
			break;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：xvl_ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P9503)

一道模拟题。

并不复杂的模拟题，也不需要用到贪心。

我们可以创建一个数组来记录每个幕布是否被拉上，统计答案的时候，就看看这块幕布前面有多少个没拉上的，最后如果这块幕布拉上了，就重新放下来就行了。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
ll n, ans;
string s;
bool vis[4]; // vis[i] = 1 表示第 i 个幕布当前是拉起来的
int main() {
    ios :: sync_with_stdio(0);
    cin >> n >> s;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'W') {
            if (vis[3]) {
                ans++;
                vis[3] = 0;
            }
        }
        else if (s[i] == 'B') {
            if (!vis[3]) {
                ans++;
                vis[3] = 1;
            }
            if (vis[2]) {
                ans++;
                vis[2] = 0;
            }
        }
        else {
            if (!vis[3]) {
                ans++;
                vis[3] = 1;
            }
            if (!vis[2]) {
                ans++;
                vis[2] = 1;
            }
            if (vis[1]) {
                ans++;
                vis[1] = 0;
            }
        }
    }
    cout << ans;
    return 0;
}
```


---

## 作者：RegisterFault (赞：3)

考虑设计二进制状态 $s$，第 $i$ 位为 $0 / 1$，表示对应幕布有没有拉下。若使白、蓝、红分别对应第 $0, 1,  2$ 位，则当客户需求为 $i$ 时，小于 $i$ 的幕布必须全部被拉上。所以暴力转移就可以了。

时间复杂度 $O(n (2 ^ V) ^ 2)$

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int N = 100010;
int f[N][1 << 4], n;
char s[N];

int get(char ch) {
	if (ch == 'W') return 0;
	if (ch == 'B') return 1;
	if (ch == 'R') return 2;
}
int cost(int x, int y) {
	int cnt = 0;
	for (int i = 0; i < 3; i ++ )
		if (((x >> i) & 1) ^ (((y >> i) & 1)))
			cnt ++ ;
	return cnt;
}
int main() {
	scanf("%d", &n);
	scanf("%s", s + 1);
	memset(f, 0x3f, sizeof f);
	f[0][7] = 0;
	for (int i = 1; i <= n; i ++ ) {
		for (int j = 0; j < 1 << 3; j ++ ) {
			for (int k = 0; k < 1 << 3; k ++ ) {
				bool flag = false;
				for (int x = 0; x < get(s[i]); x ++ )
					if ((k >> x) & 1) flag = true;
				if (flag) continue;
				if ((k & (1 << get(s[i]))) == 0) continue;
				f[i][k] = min(f[i][k], f[i - 1][j] + cost(j, k));
			}
		}
	}
	int ans = 0x3f3f3f3f;
	for (int i = 0; i < 1 << 3; i ++ )
		ans = min(ans, f[n][i]);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：zsh_haha (赞：2)

### 思路讲解

这里不需要什么贪心策略，直接按顺序来就行了。

这里每一次需要判断当前幕布是否已经拉下来，若没有，则用 $1$ 个时间单位拉下来；然后再看前面的是否都已经拉上去了，若没有，则用 $x$ 个时间单位拉上，这里 $x$ 指前面没有拉上去的幕布数量。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	bool w=true,b=true,r=true;//三个幕布的状态，true 为拉下，false 为拉上（w 白色，b 蓝色，r 红色） 
	int sum=0;//记录时间 
	for(int i=1;i<=n;i++){
		char x;
		cin>>x;
		if(x=='W'){
			if(!w){//判断当前是否为拉下状态 
				sum++;//不是则花时间 
				w=true;
			}
		}else if(x=='B'){
			if(w){//判断前面是否是拉上状态 
				sum++;//不是则花时间 
				w=false;
			}
			if(!b){//判断当前是否为拉下状态 
				sum++;//不是则花时间 
				b=true;
			}
		}else{
			if(w){//判断前面是否是拉上状态 
				sum++;//不是则花时间 
				w=false;
			}
			if(b){//判断前面是否是拉上状态 
				sum++;//不是则花时间 
				b=false;
			}
			if(!r){//判断当前是否为拉下状态 
				sum++;//不是则花时间 
				r=true;
			}
		}
	}
	cout<<sum;
    return 0;
}
```

---


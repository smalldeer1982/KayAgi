# 【MX-X9-T0】『GROI-R3』NaiLong

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/5rob14vd.png)

## 题目描述

Isj2OO9 加入了一个奶龙群，里面很喜欢发各种奶龙表情包。

Isj2OO9 注意到奶龙表情包中有两个表情很奇怪：

![](https://cdn.luogu.com.cn/upload/image_hosting/ljxnjm2w.png)

左侧的表情包被标号为 $0$，它指向发下一条消息的人；右侧的表情包被标号为 $1$，它指向发上一条消息的人。其他表情包均被标号为 $2$。

一位群成员被称为「奶批」，当且仅当 ta 至少被其他人指向一次。

有 $n$ 位**不同**的群成员连续发送了 $n$ 条含有表情包的消息。按照时间顺序，称第 $i$（$1 \leq i \leq n$）条消息的发送者为第 $i$ 个人。记第 $i$ 条消息中含有的表情包的标号为 $a_i$（$\boldsymbol{0 \leq a_i \leq 2}$）。

Isj2OO9 记录下了一段聊天记录对应的序列 $a_1, \ldots, a_n$。为了检验你是不是奶龙领域大神，他还给定一个整数 $1 \leq k \leq n$，并向你询问，在仅关心这 $n$ 条聊天记录的前提下，第 $k$ 个人是否为「奶批」。

## 说明/提示

**【样例解释 #1】**

第一个人发送了表情 $1$，指向上一个人；第二个人发送了表情 $0$，指向下一个人；第三个人发送了表情 $2$。因此在本段聊天记录内，只有第三个人为「奶批」。所以当 $k = 1$ 时，输出 `No`。

**【样例解释 #2】**

第一个人发送了表情 $0$，指向下一个人；第二个人发送了表情 $1$，指向上一个人；第三个人发送了表情 $2$。因此在本段聊天记录内，第一、第二个人均为「奶批」。所以当 $k = 2$ 时，输出 `Yes`。

**【数据范围】**

对于 $100\%$ 的数据，保证 $1 \leq k \leq n \leq 100$，$0 \leq a_i \leq 2$。

## 样例 #1

### 输入

```
3 1
1 0 2
```

### 输出

```
No
```

## 样例 #2

### 输入

```
3 2
0 1 2
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
19 17
0 0 2 0 1 0 0 0 2 0 2 0 2 0 2 1 1 0 0
```

### 输出

```
No
```

# 题解

## 作者：Lovely_yhb (赞：6)

### 题意

一个由 $0,1,2$ 组成的长度为 $n$ 序列 $a$，$0$ 表示向后指，$1$ 表示向前指，$2$ 表示哪都不指。问位置 $k$ 有没有被指。

### 思路

如果一个位置的前面是 $0$ 或后面是 $1$ 就说明被指到了，所以只需要判断 $a_{k-1}=0$ 或 $a_{k+1}=1$ 即可。

还有一个坑点，就是 $a_0$ 和 $a_{n+1}$ 是 $0$，会影响 $1$ 和 $n$ 位置的查询，需要把这两个位置赋成 $2$。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[105];
int main(){
	cin>>n>>k;
	a[0]=a[n+1]=2;
	for(int i=1;i<=n;i++) cin>>a[i];
	if(a[k-1]==0||a[k+1]==1) puts("Yes");
	else puts("No");
	return 0;
}
```

---

## 作者：ShiYuXuan1234 (赞：3)

## 前言
这题这么简单，为啥题解通道还开着啊……

那我就~~勉为其难地~~写一篇题解吧。

---
## 思路
首先，我们需要一个数组，并初始化为 $2$（因为其余奶龙表情包都为 $2$），然而众所周知，`mamset`函数只能把全部数字初始化为 $0$，因此，我们在这里讲一下`vector`:

用`vector`定义数组，一个好处就是变量可以初始化成任何数，只需要以下代码：

```cpp
vector<\*数组类型*\> a(\*数组大小*\,\*想要初始化成的数*\);
```
这样，我们就可以直接找到 $a_{k-1}$ 和 $a_{k+1}$，然后按题意判断即可。

## 代码（无注释）

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> a(101,2);
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	if(a[k-1]==0||a[k+1]==1){
		cout<<"Yes";
	}else{
		cout<<"No";
	}
	return 0;
}
```
最后，[AC 记录](https://www.luogu.com.cn/record/204422210)。

---

## 作者：Sheep_YCH (赞：2)

## 洛谷 P11796

[题目传送门](https://www.luogu.com.cn/problem/P11796)

## 题目分析

简单的模拟题。

本题要求第 $k$ 个人是否为“奶批”（一个人为“奶批”当且仅当他的上一个人或者下一个人指向他）。所以直接根据要求判断即可。注意特判 $k = 1$ 和 $k = n$ 的情况就行。代码实现难度比较低。

## Code

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#define ll long long
using namespace std;
const int MAXN = 1e6 + 5;
int a[MAXN];

int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k; cin >> n >> k;
	for(int i = 1; i <= n; i ++) cin >> a[i];
	if(k == 1) a[2] == 1 ? cout << "Yes" : cout << "No";
	else if(k == n) a[n - 1] == 0 ? cout << "Yes" : cout << "No";
	else if(a[k + 1] == 1 || a[k - 1] == 0) cout << "Yes";
	else cout << "No";
	
	return 0;

}

```

---

## 作者：Curry_mvp (赞：2)

![](https://cdn.luogu.com.cn/upload/image_hosting/nca85swd.png)

~~盗图~~

这太有生活了~

定义一个标记数组，输入一次处理一次，如果这个人被知道了就改变，否则不变，然后按照要求输出即可，具体看代码

挺水的

注意小心数组访问越界或者出现负数下标

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=105;
int a[maxn];
int n,k;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
signed main ()
{
	n=read();
	k=read();
	for(int i=1;i<=n;i++)
	{
		int x;
		x=read();
		if(x==0)
		{
			a[i+1]++;
		}
		if(x==1)
		{
			a[i-1]++;
		}
	}
	if(a[k]!=0)
	{
		cout<<"Yes"<<"\n";
	}
	else
	{
		cout<<"No"<<"\n"; 
	}
	return 0;
}
```
水

---

## 作者：dear_deer_land (赞：2)

## 题意

给定一个序列 $a$，如果 $a_i$ 为 $0$，那么对 $a_{i+1}$ 进行标记，如果 $a_i$ 为 $1$ 那么对 $a_{i-1}$ 进行标记，最后查询 $a_k$ 是否被标记。

## 思路

本题直接进行暴力枚举，枚举对于每一个 $i$，$a_i$ 的值，如果 $a_i$ 为 $0$，那么对 $flag_{i+1}$ 进行标记，如果 $a_i$ 为 $1$ 那么对 $flag_{i-1}$ 进行标记，最终查询 $flag_k$ 的值。

## 代码

本题代码实现十分简单，代码如下（已省略快读快输，快读快输见[剪贴板](https://www.luogu.me/paste/fzqp4e4k)）

```
int n,a[11000],k;
bool flag[10010];
signed main(){
    read(n,k);
    for(int i=1;i<=n;i++){
        read(a[i]);
        if(a[i]==0){
            flag[i+1]=1;
        }
        if(a[i]==1){
            flag[i-1]=1;
        }
    }
    if(flag[k]){
        write("Yes");
    }
    else{
        write("No");
    }
    return 0;
}
```

---

## 作者：canwen (赞：2)

简单来说就是，当 $a_{i} = 0(i<n)$，第 $i+1$ 个人就能收到信息，当 $a_{i} = 1(i>1)$ 时，第 $i-1$ 个人就能接收到信息。

于是 $O(n)$ 跑一遍判断是否存在 $a_{k-1} = 0$ 或者 $a_{k+1} = 1$ 即可。

---

## 作者：GSQ0829 (赞：1)

### 思路：
简单的入门题。

设置一个用于判断是不是奶批的数组。

如果表情包标号为零，下一个人就被标记为奶批。

如果为一，上一个人被标记为奶批。

最后，如果第 $k$ 个人没被标记过那就输出 ```No```。

否则，输出 ```Yes```。

---
### code：
```cpp
#include <bits/stdc++.h>
using namespace std; 

const int MAXN = 101;
int a[MAXN], n, k;
bool b[MAXN];

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (a[i] == 0) b[i + 1] = 1;
		else if (a[i] == 1) b[i - 1] = 1;
	}
	if (b[k]) cout << "Yes";
	else cout << "No";
	return 0;
}
```

---

## 作者：Program_A2 (赞：1)

据题意，本题只是一个，一个一个一个普通的简单的模拟啊。只需根据描述写就对了。

如果 $a_i=0$，那么 $a_{i+1}$ 是「奶批」；如果 $a_i=1$，那么 $a_{i-1}$ 是「奶批」。最后再看一下 $a_k$ 是不是「奶批」就行了。

```
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,k;
    cin>>n>>k;
    int a[n+1],b[n+1]={0};
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]==0){
            b[i+1]++;
        }
        if(a[i]==1){
            b[i-1]++;
        }
    }
    if(b[k]){
        cout<<"Yes";
    }else{
        cout<<"No";
    }
    return 0;
}
```

---

## 作者：liuzhuoran141516 (赞：1)

# 题解：P11796 【MX-X9-T0】『GROI-R3』NaiLong

[题目传送门](https://www.luogu.com.cn/problem/P11796)

## 解题思路
本题非常简单，我们只需要遍历每一条消息
   - 如果表情包标号为 $0$，则表示该消息的发送者指向了下一条消息的发送者。如果下一条消息的发送者正好是第 $k$ 个人，则第 $k$ 个人被指向了。
   - 如果表情包标号为 $1$，则表示该消息的发送者指向上一条消息的发送者。如果上一条消息的发送者正好是第 $k$ 个人，则第 $k$ 个人被指向了。
   - 如果表情包标号为 $2$，则不进行任何操作，因为这种表情包不指向任何人。  
在遍历过程中，如果发现第 $k$ 个人被指向了，则将标志变量 `f` 置为 `true`，并跳出循环。最后根据 `f` 的值输出 `Yes` 或 `No` 即可。

## Code

```cpp
#include <iostream>
using namespace std;
int n, k, a[105];
int main() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    bool found = false;
    for (int i = 1; i <= n; ++i) {
        int ai = a[i - 1];
        if (ai == 0) {
            if (i + 1 <= n && (i + 1) == k) {
                found = true;
                break;
            }
        } else if (ai == 1) {
            if (i - 1 >= 1 && (i - 1) == k) {
                found = true;
                break;
            }
        }
    }
    cout << (found ? "Yes" : "No") << endl;
    return 0;
}
```

---

## 作者：getchar_unlocked (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P11796)

### 思路

对于第 $i$ 个表情包：若 $a_i=0$，那么标记前一个表情包 $a_{i-1}=1$；若 $a_i=1$，那么标记下一个表情包 $a_{i+1}=1$。最后判断第 $k$ 个表情包是否被标记（$a_k=1$）即可。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=105;
int a[N],cnt[N];
int main(){
	int n=read(),k=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	for(int i=1;i<=n;++i)
		if(a[i]==0&&i<n)
			++cnt[i+1];
		else if(a[i]==1&&i>=1)
			++cnt[i-1];
	printf(cnt[k]?"Yes\n":"No\n");
	return 0;
}
```

---

## 作者：lcfollower (赞：1)

签到题。

可以开一个大小为 $n$ 的数组，记 $sum_i$ 表示第 $i$ 个人被别人指的次数。

- 若 $a_i = 0$，$sum_{i + 1} \to sum_{i + 1} + 1$。
- 若 $a_i = 1$，$sum_{i - 1} \to sum_{i - 1} + 1$。
- 若 $a_i = 2$，不变。

最后判断 $sum_k$ 是否大于 $0$ 即可判断第 $k$ 个人是不是「奶批」。

```cpp
# include <bits/stdc++.h>

# define int long long
# define up(i ,x ,y) for (int i = x ; i <= y ; i ++)
# define dn(i ,x ,y) for (int i = x ; i >= y ; i --)
# define inf 100000000000000

using namespace std;

inline int read (){int s = 0 ; bool w = 0 ; char c = getchar () ; while (!isdigit (c)) {w |= (c == '-') ,c = getchar () ;} while (isdigit (c)){s = (s << 1) + (s << 3) + (c ^ 48) ; c = getchar ();}return w ? -s : s;}
inline void write (int x){if (x < 0) putchar ('-') ,x = -x; if (x > 9) write (x / 10) ; putchar (x % 10 | 48);}
inline void writesp (int x){write (x) ,putchar (' ');}
inline void writeln (int x){write (x) ,putchar ('\n');}

const int N = 1e6 + 10;
int n ,k ,sum[105];

signed main (){
  n = read () ,k = read ();

  up (i ,1 ,n){
    int x = read ();

    if (!x && (i ^ n)) sum[i + 1] ++  ;//i ^ n 等价于 i != n，下同，删了也没关系。
    else if (x == 1 && (i ^ 1)) sum[i - 1] ++ ;
    else continue;
      
  }

  if (sum[k] > 0) puts("Yes");
  else puts("No");
  
  return 0 ;
}
```# include <bits/stdc++.h>

# define int long long
# define up(i ,x ,y) for (int i = x ; i <= y ; i ++)
# define dn(i ,x ,y) for (int i = x ; i >= y ; i --)
# define inf 100000000000000

using namespace std;

inline int read (){int s = 0 ; bool w = 0 ; char c = getchar () ; while (!isdigit (c)) {w |= (c == '-') ,c = getchar () ;} while (isdigit (c)){s = (s << 1) + (s << 3) + (c ^ 48) ; c = getchar ();}return w ? -s : s;}
inline void write (int x){if (x < 0) putchar ('-') ,x = -x; if (x > 9) write (x / 10) ; putchar (x % 10 | 48);}
inline void writesp (int x){write (x) ,putchar (' ');}
inline void writeln (int x){write (x) ,putchar ('\n');}

const int N = 1e6 + 10;
int n ,k ,sum[105];

signed main (){
  n = read () ,k = read ();

  up (i ,1 ,n){
    int x = read ();

    if (!x && (i ^ n)) sum[i + 1] ++  ;
    else if (x == 1 && (i ^ 1)) sum[i - 1] ++ ;
    else continue;
      
  }

  if (sum[k] > 0) puts("Yes");
  else puts("No");
  
  return 0 ;
}

---

## 作者：niuniudundun (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P11796)

# 题目大意

有一个长度为 $n$ 的序列 $a$，如果 $a_i=0$ 则 $a_{i+1}$ 是「奶批」，如果 $a_i=1$ 则 $a_{i-1}$ 是「奶批」，问 $a_k$ 是否是「奶批」。

# 解法

输入 $n$、$k$ 和 $a$，如果 $a_{k-1}=0$ 或 $a_{k+1}=1$，则是「奶批」，输出 `Yes`；否则不是，输出 `No`。

不过，**如果你的 $a$ 从 $1$ 计数，$a_0$ 会默认为 $0$，需要让 $a_0$ 等于一个非零数。**

代码：

复杂度：$O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=101;
int n,k,a[maxn];
int main(){
	cin>>n>>k;
	a[0]=-1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	if(a[k-1]==0||a[k+1]==1){
		cout<<"Yes\n";
	}else{
		cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：zsjaaaxy (赞：1)

使用 $vis$ 数组存储每个成员是否为「奶批」，模拟即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[1000];
bool vis[1000];
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=n;i++)
    {
        if(a[i]==1)
        {
            vis[i-1]=1;
        }
        if(a[i]==0)
        {
            vis[i+1]=1;
        }
    }
    if(vis[k])
    {
        cout<<"Yes";
    }
    else
    {
        cout<<"No";
    }
    return 0;
}
```

---

## 作者：Eric1030 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P11796)

这道题不难，我们只要先把数据输入进来，然后看 ```a[k-1]``` 是不是 $0$ 或 ```a[k+1]``` 是不是 $1$，满足至少一项就输出 ```Yes```，否则输出 ```No```。

## [AC](https://www.luogu.com.cn/record/204407142) 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, a[105];
int main()
{
    //输入数据
    cin >> n >> k;
    for (int i = 1;i <= n;i++)
    {
        cin >> a[i];
    }
    a[0] = -1;//避免在k=1时遇到a[k-1]也就是a[0]是0的情况
    a[0] = 3;//不写也可以
    if (a[k - 1] == 0 || a[k + 1] == 1)//如果被人知道了
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
    return 0;//结束！
}
```

---

## 作者：Stars_visitor_tyw (赞：1)

# 题解：P11796 【MX-X9-T0】『GROI-R3』NaiLong
## 思路
由于只关心第 $k$ 个人，所以只要判断第 $k$ 个人有没有被指向，按题意模拟即可。


## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, k;

signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
          int a;
        cin>>a;
        if(a==0)
        {
            if(i+1==k)
            {
                cout<<"Yes";
                return 0;
            }
        }
        if(a==1)
        {
            if(i-1==k)
            {
                cout<<"Yes";
                return 0;
            }
        }
    }
    cout<<"No";
}

---

## 作者：guer_loser_lcz (赞：0)

# 题解
## 题意
$0$ 指向下 $1$ 指向上，问第 $k$ 个人有没有被指。

如果 $k - 1 = 0$ 或 $k + 1 = 1$ 就证明他被指了。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[100100],k;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];//输入
	a[0]=a[n+1]=114514;//边界处理
	if(a[k-1]==0||a[k+1]==1)cout<<"Yes";//判断
	else cout<<"No";
}
```

---

## 作者：easy42 (赞：0)

非常的简单，对于每个 $k$，只要判断它周围就好了。

就像这样：

```cpp
if(a[k - 1] == 0 && k - 1 > 0 || a[k + 1] == 1 && k + 1 <= n)
```

由“一位群成员被称为「奶批」，当且仅当 ta 至少被其他人指向一次。” 得。

其中，`k - 1 > 0` 和 `k + 1 <= n` 是边界，`a[k - 1] == 0` 和 `a[k + 1] == 1` 是判断条件。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005] , n , k;
signed main(){
	cin >> n >> k;
	for(int i = 1;i <= n;i ++){
		cin >> a[i];
	}
	if(a[k - 1] == 0 && k - 1 > 0 || a[k + 1] == 1 && k + 1 <= n) cout << "Yes";
	else  cout << "No";
	return 0;
}
```

---

## 作者：huanglihuan (赞：0)

### Solution
我们考虑，若 $k-1$ 位的人指向下一个人，那么他指向的就是 $k$，满足要求。  
若 $k+1$ 位的人指向上一个人，那么他指向的就是 $k$，满足要求。  
### Code
```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 988444333
#define MOD 1000000007
#define in(x,y,z) x>=y&&x<=z
using namespace std;
const int N = 2e6 + 5;
int a [N];
inline int read ()
{
	int x = 0;
	char c = getchar ();
	while (c < '0' || c > '9') c = getchar ();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48),c = getchar ();
	return x;
}
inline void write (int x)
{
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
	return ;
}
int sum (int x)
{
	int p = 1;
	while (p <= x) p <<= 1;
	return p >> 1;
}
signed main ()
{
	int n,k;
	cin >> n >> k;
	for (int i = 1;i <= n;i ++)
	{
		cin >> a [i];
		if (i == k - 1 && a [i] == 0) return cout << "Yes",0;
		if (i == k + 1 && a [i] == 1) return cout << "Yes",0;
	}
	cout << "No";
	return 0;
}
```

---

## 作者：Na1L0n9 (赞：0)

# Solution

## 思路
简单题，如果这个数的上一个数是 $0$ 或者这个数的下一个数是 $1$ 则该群成员就是「奶批」。注意处理 $k=1$ 与 $k=n$ 的情况。

## Code


```cpp
#include <bits/stdc++.h>
#define Write ios::sync_with_stdio(0);
#define by cin.tie(0);
#define AquaDaMean1e cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 10;
const int MOD = 998244353;
int n, k, ans, a[N];
int main() {
	Write by AquaDaMean1e
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
    a[0] = a[n + 1] = 2; // 处理 k=1 与 k=n 的情况
	if (a[k - 1] == 0 || a[k + 1] == 1) {
		cout << "Yes";
	}
	else {
		cout << "No";
	}
	return 0;
}
```

---

## 作者：zhangrui2023 (赞：0)

维护一个数组用来记录每个人是否被指向过，判断第 $k$ 个人有没有被指向过并输出即可。

### AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a[1010],b[1010];
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]==1)b[i-1]=1;
        if(a[i]==0)b[i+1]=1;
    }
    if(b[k]>0)cout<<"Yes";
    else cout<<"No";
    return 0;
}
```

---

## 作者：M1__ (赞：0)

# P11796 【MX-X9-T0】『GROI-R3』NaiLong 题解
[题目传送门](https://www.luogu.com.cn/problem/P11796)
## 形式化题意
- 对于每个项 $a_i(1<i<n)$，当 $a_{i-1}=0$ 或 $a_{i+1}=1$ 时成立。
- 对于 $a_1$ 和 $a_n$，当 $a_2=1$ 时前者成立，当 $a_{n-1}=0$ 后者成立。
- 按题意模拟即可。
## 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k,a[1000];
int main (){
    bool f=0;
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    if(k==1){
        if(a[k+1]==1) cout<<"Yes";
        else cout<<"No";
    }
    else if(k==n){
        if(a[k-1]==0) cout<<"Yes";
        else cout<<"No";
    }
    else{
        if(a[k+1]==1||a[k-1]==0) cout<<"Yes";
        else cout<<"No";
    }
    return 0;
}
```

---

## 作者：qjh_2014 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P11796)

## 思路
读入表情包后，按照题目意思判断上一个 $1$ 或者下一个 $0$ 是否为奶批，如果是输出  ```Yes``` 否则输出 ```No```。
## 代码
```
#include <bits/stdc++.h>
using namespace std;
void uprint(int x){//输出无符号类型数
  	if(x>9){
    	uprint(x/10);
  	}
  	putchar(x%10^48);
  	return ;
}
void print(int x){//有符号类型，可直接调用这个
  	if(x<0){
    	putchar('-');
    	x=-x;
	}
	uprint(x);
	return ;
}
int read() {
	int x=0, w=1;
	char ch=0;
	while (ch<'0'||ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return x*w;
}
int a[105];//定义数组 
int main() {
    int n=read(),k=read();//读入数据
    for(int i=1; i<=n; i++){
        cin>>a[i];//读入表情包 
    }
    bool answer=false;//答案如果为 true 输出 Yes 否则输出 No 
    for(int i=1; i<=n; i++){
        if (a[i]==0){//表情包是 0 指向下一个人
            if(i<n&&i+1==k){//判断越界和是否为奶批 
                answer=true;//是 
                break;
            }
        } 
		else if(a[i]==1) {//表情包是 1 指向上一个人
            if(i>1&&i-1==k){//判断越界和是否为奶批 
                answer=true;//是 
                break;
            }
        }
    }
    if(answer){//是的情况 
        cout<<"Yes"<<endl;
    } 
	else{
        cout<<"No"<<endl;
    }
    return 0;
}
```
注释在代码里有看不懂私信。

---


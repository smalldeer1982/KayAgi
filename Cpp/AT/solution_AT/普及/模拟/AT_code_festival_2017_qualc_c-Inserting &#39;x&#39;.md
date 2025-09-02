# Inserting &#39;x&#39;

## 题目描述

输入一个字符串S，您可以重复执行以下操作：

在S的任意位置（包含开头和结尾），插入一个小写字母 x ， 使其变成回文的字符串。

请输出所需的最少操作次数 ，如果不能变为回文 ，输出 -1 。

## 样例 #1

### 输入

```
xabxa```

### 输出

```
2```

## 样例 #2

### 输入

```
ab```

### 输出

```
-1```

## 样例 #3

### 输入

```
a```

### 输出

```
0```

## 样例 #4

### 输入

```
oxxx```

### 输出

```
3```

# 题解

## 作者：zjyqwq (赞：6)

### AT3590 Inserting 'x'题解


------------
#### 解题思路
这里 $|s|>10^5$ 纯暴力显然不行，我们需要采用线性复杂度。

这里有一种思路类似暴力但是复杂度为 $O(n)$ 的方法，我来讲一讲。

因为他是判断回文，我们就可以使用两个指针 $l$ 和 $r$ ，一个在前一个在后，分别代表 $s$ 串回文的两边，慢慢缩小待判断的范围，最后得出结果。

##### 判断回文
1. 如果 $s[l]$ 等于 $s[r]$，直接缩小范围$\ L=L+1,R=R-1\ $，然后 $continue$ 结束当前这次循环。
2. 如果 $s[l]$ 和 $s[r]$ 其中任意有一个为 $x$，那么还可以补救，在 $s[$ 对面 $]$ 的后面插入一个 $x$,就行了；这时，我们要让等于 $x$的一方向镜像中心靠近，并且增加答案的数量。然后 $continue$。
3. 没救了。输出 $-1$，$return\ 0$。

如果执行到现在，那么说明还是可以变成回文的，输出答案。


------------
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register
#define w_ putchar(' ')
#define wn putchar('\n')
inline int mmax(R int x,R int y){return x>y?x:y;}
inline int mmin(R int x,R int y){return x<y?x:y;}
inline void swap(R int &x,R int &y){R int t=x;x=y;y=t;}
inline void read(R int &y){
   R int s=0,w=1;
   R char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   y=s*w;
}
inline void write(R int x){
    if(x < 0){
        putchar('-');
        write(-x);
        return;
    }
    if(x >= 10) write(x / 10);
    putchar(x % 10 + '0');
}
 int main(){
 	R string s;
 	R int l,r,ans=0;
	ios::sync_with_stdio(0);
 	cin>>s;
 	for(l=0,r=s.size()-1;l<=r;){
 		if(s[l]==s[r]){++l;--r;continue;}
 		if(s[l]=='x'){++l;++ans;continue;}
 		if(s[r]=='x'){--r;++ans;continue;}
 		puts("-1\n");
 		return 0;
	 }
	write(ans);wn;
 	return 0;
}

```

---

## 作者：scp020 (赞：2)

本题是一道双指针的模拟题。

### 题意

给你一个字符串 $s$，你可以在 $s$ 的任意位置插入 $x$，是 $s$ 变为回文。

### 解决

定义双指针 $l$ 和 $r$，$l$ 和 $r$ 初始化为 $s$ 的两端。

定义一个计数的 $ans$，用来计算到底需要插入多少个 $x$。

模拟规则如下：

- 如果 $l$ 所在的位置的值和 $r$ 所在的位置的值相同，则构成回文，不用插入 $x$，可忽略这个位置，跳过 $l$，向前跳过 $r$。

- 如果 $l$ 所在位置的值是 $x$，则我们要把 $r$ 所在位置的值插入一个 $x$，现在 $l$ 和 $r+1$ 对称构成回文，然后跳过 $l$。

- 如果 $r$ 所在位置的值是 $x$，则我们要把 $l$ 所在位置的值插入一个 $x$，现在 $-1l$ 和 $r$ 对称构成回文，然后向前跳过 $r$。

- 如果都不满足，则原串无论如何也无法构成回文，则输出 $-1$，跳出程序。

### 样例解释

首先 $l$ 指向 $0$，$r$ 指向 $4$，两个位置的数值不等，满足上述第 $2$ 条，所以要向末尾插入 $x$，$ans$ 自增 $1$，$l$ 自增 $1$。

现在 $l$ 指向 $1$，$r$ 指向 $4$，两个位置的数值相等，$l$ 自增 $1$，$r$ 自减 $1$。

现在 $l$ 指向 $2$，$r$ 指向 $3$，两个位置的数不同，满足上述第 $3$ 条，所以在 $l$ 前插入一个 $x$，$ans$ 自增 $1$，$r$ 自减 $1$。

现在 $l$ 指向 $2$，$r$ 指向 $2$，两个位置的数值相等，$l$ 自增 $1$，$r$ 自减 $1$。

现在 $l$ 指向 $3$，$r$ 指向 $1$，不满足循环条件，退出程序。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int l,r,ans;
int main()
{
	ios::sync_with_stdio(false);
	cin>>s,r=s.size()-1;
	while(l<=r)//这个双指针越看越像二分 
	{
		if(s[l]==s[r]) l++,r--;
		else if(s[l]=='x') l++,ans++;
		else if(s[r]=='x') r--,ans++;
		else
		{
			cout<<-1;
			return 0;
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：_Give_up_ (赞：2)

## 题目大意
给定一个字符串，你能往里面随意加入 `x`，求最少的操作使此串变成回文串

## 题目思路
判断回文串想必大家都会，这回我们只需要往里面加 `x` 就行了

我们定义变量 `l` 和 `r`，`l` 是字符串的最前端，`r` 是字符串的最后端。

如果 `s[l]==s[r]`,我们不做任何操作，把 `l` 向前推进以为，`r` 向后推进一位就行了。

如果 `s[l]=='x'`，我们要在字符串里添加一个 `x`，把步骤加一，并把 `l` 向前推进一位，`r` 不变。

同理，如果 `s[r]=='x'`，我们也要在字符串里添加一个 `x`，把步骤加一，并把 `r` 向前推进一位，`l` 不变。

如果这三种情况都没有的话，我们直接输出 `-1`，`return 0;` 结束整个程序。

## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
	string s;
	cin >> s;
	int l=0,r=s.length()-1,ans=0;
	while(l<=r)
	{
		if(s[l]==s[r])
		{
			l++;
			r--;
		}
		else if(s[l]=='x')
		{
			ans++;
			l++;
		}
		else if(s[r]=='x')
		{
			ans++;
			r--;
		}
		else
		{
			cout << -1 << endl;
			return 0;
		}
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：Smoggy (赞：1)

### **题意**：

输入一个字符串$S$，您可以重复执行以下操作：

在$S$的任意位置（包含开头和结尾），插入一个小写字母 $x$ ， 使其变成回文的字符串。

请输出所需的最少操作次数 ，如果不能变为回文 ，输出 $-1$ 。

**输入格式**：

输入文件仅有一行，一个仅包含小写字母的字符串$S$。

**输出格式**：

如果目标可实现 ，则输出所需的最少操作次数。如果不行，请输出$-1$。

$$\texttt{---------------------}$$

其实，根据题目意思我们可以知道只能通过添加$x$来使其变成回文。

那么我们可以用一个十分基础的判回文的方法，从左右两端找：

```cpp
	int L=0,R = st.size() - 1;
	while ( L <= R )
	{
    	...
    }
```

如果左右两边字母相同，则左、右端点往中间走：

```cpp
	if ( st[L] == st[R] ) {L++,R--;continue;}
```

如果不同，我们就要通过添加字母$x$来构造回文。

但是有一个**前提**：

就是当前所判断字母为$\color{red}x$时，才能通过添加字母$x$来使其对称。

那么我们判断一下即可

```cpp
	if ( st[L] == 'x' ) {L++,ans++;continue;}
```

右端同理

```cpp
	if ( st[R] == 'x' ) {R--,ans++;continue;}
```

如果左、右端都没有x且不相同的话，那么即使添加$x$也不能构造回文惹...所以我们就可以跳出循环，输出$-1$即可。

完整代码如下：
```cpp
#include <bits/stdc++.h>	//万能头文件
using namespace std;
string	st;
int	ans;		//记录次数
bool	flag = true;	//用来标记是否能构造回文
int main()
{
	cin >> st;
	int L=0,R = st.size() - 1;	//定义左、右端
	while ( L <= R )	//运行到字符串中间
	{
		if ( st[L] == st[R] ) {L++,R--;continue;}	//相同则不管它
		if ( st[L] == 'x' ) {L++,ans++;continue;}	//判断左端是否为x
		if ( st[R] == 'x' ) {R--,ans++;continue;}	//同理
		flag = false; break;	//上面方法都行不通，标记，退出循环
	}
	ans = flag ? ans : -1;	
	cout << ans ;	//输出
	return(0);	//记得打return 0
}
```


---

## 作者：BeetyX (赞：0)

题意：输入一个字符串S，然后在它里面不断插入字符串，每插入一次计数器就+1，再判断是否为回文字符串，是的话就停止。最后输出计数器里的数（也就是总步数），如果不能达到目标就输出-1。

这题可以分几步：

①插入字符“x”。

②判断是否为回文字符串。

③如果是，ans（计数器）+1。

④最后输出ans，如果不能达到目标，输出-1。

其中的②，也就是判断是否为回文字符串这一步稍难，可以用两个变量l和r，l代表左端点，r代表右端点。（这里用len代表字符串长度）

l=0；r=len-1（此时l、r都在字符串的最左和最右）

l=1；r=len-2（此时l、r在字符串的左二和右二）

……（l不断+1，r不断-1，直到l≥r的时候结束。）

在每次l、r变化时都要判断l是否等于r，如果l=r，那么就continue，否则就插入一个x，ans再+1。

值得注意的是：是要l和r中要有一个x，否则加了一个x也没用（没法构成回文数）。




代码如下
------------
```
#include<bits/stdc++.h>
using namespace std;
string s;//定义字符串
int ans=0;//计数器
int main()
{
     cin>>s;//输入
     int l=0;//左端点
     int r=s.length()-1;//右端点
     while(l<=r)//当左右不在一起的时候
     {
	 if(s[l]==s[r])//如果左右端点相同
	 {
	      l++;//左端点移动
	      r--;//右端点移动
	      continue;//继续
	 } 
	 if(s[l]=='x')//如果左端点为x
	 {
	      l++;//左端点移动
	      ans++;//计数器+1
	      continue;//继续
	 }
	 if(s[j]=='x')//如果右端点也为x
	 {
	      r--;//右端点移动
	      ans++;//计数器+1
	      continue;//继续
         }
	 else//如果都不满足
	 {
	      cout<<"-1"<<endl;输出-1
	      return 0;//提前结束
	 }
     }
     cout<<ans<<endl;//输出ans 
     return 0;
}
```


---

## 作者：零殇 (赞：0)

#### 题意
给定一个字符串，每次可以插入一个小写字母 $x$（注意 $x$ 的意思是**只能**插入 $x$ 这个字符而不是任意小写字母），求最少多少次操作后，可以得到一个回文串。如果永远无法满足，则输出 $-1$ 。

#### 思路
对于如何判断回文串，我们采取双指针判断。

我们不妨把字符串设为 $s$ ，两个指针设为 $l $和 $r$ 。

将 $l$ 初始值定为 $0$ ， $r$ 定为字符串最后一位的位置。

每一次判断 $s[l]$ 和$s [r]$ ，如果相等就将 $l$ 加 $1$ ， $r$ 减 $1$ 。

重复至$ l$ 和 $r$ 交错为止。

那么对于 $s[l]$ 和 $s[r]$ 不相等的情况，有$3$种。

#### 第一种：$s[l]$等于$x$

此时，我们就需要在 $s[r+1]$ 的地方放一个 $x$ ，并将 $r+1$ ，然后就变回了相等的情况。

因为 $r+1$ 和我们之后会进行的 $r-1$ 相互抵消，所以只要将$l$加$1$并累加计数器就好了。

```
else if(s[l]=='x') {
	ans++;
	l++;
}
```

#### 第二种：$s[r]$等于$x$

和第二种思路相同，只不过这次要修改的变成了 $r$ 。

```
else if(s[r]=='x') {
	ans++;
	r--;
}
```

#### 第三种：$s[l]$和$s[r]$都不等于$x$

此时，无论怎么增加 $x$ ，也不可能让 $s[l]=s[r]$ 。输出 $-1$ 。

这里就不放代码片段了。

最后，上完整代码：
```
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
int main() {
	int l,r,ans=0;
	string s;
	cin>>s;
	l=0;
	r=s.size()-1;
	while(l<=r) {
		if(s[l]==s[r]) {//相等情况
			l++;
			r--;
		}
		else if(s[l]=='x') {
			ans++;
			l++;
		}
		else if(s[r]=='x') {
			ans++;
			r--;
		}
		else {//不相等且都不等于x
			printf("-1\n");
			return 0;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```
完结撒花~

---

## 作者：Griseo_nya (赞：0)

一道字符串水题。

输入s后从两侧开始判回文。很明显，在一端去掉 $x$ 和在另一端的对称位置加上一个 $x$ 有相同的效果，所以在此处我们只采用去掉的方法。

从两边开始逼近，如果两端对称就各往中间走一个字符。如果不对称的话，若两边有一边是 $x$ ，则删去（即仅该侧向中间逼近）。若不对称且两侧均无 $x$ ，则直接退出。

下面就是代码哒☆

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin>>s;
	int siz=s.size();		//读出字符串长度
	int l=0,r=siz-1;		//设定初始l,r
	int ans=0;
	while(l<r){
		if(s[l]==s[r])r--,l++;			//两端对称
		else if(s[l]=='x')l++,ans++;	//两端不对称，左端是 x
		else if(s[r]=='x')r--,ans++;	//两端不对称，右端是 x
		else puts("-1"),exit(0);		//两端不对称，两端均不为 x
	}
	cout<<ans<<endl;					//输出答案
	return 0;	
} 
```


---

## 作者：七夜 (赞：0)

这道题一开始我竟然用了栈，后来才发现自己的做法有点low

为什么呢，因为我记录了当前字符有没有出现过，出现过就开始进行弹栈操作

是不是有点傻，比如下面这组数据：ababababa（中间可以随便插入x），用栈打的就是输出-1，所以我思索了一下，判断首位是否相等就行了，但是一开始还是能错几个点，因为我在while里面套了while
没有考虑x与x相等的情况，在改过之后终于A掉了

~~奉上本蒟蒻丑陋的代码~~

```
#include<bits/stdc++.h>//偷懒专用开 
#define INF 9999999;//宏定义 
using namespace std;
inline int read() {
	char c = getchar(); int x = 0, f = 1;
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}//快读，想学的可以借鉴一下 
string ss;//字符串 
int tot;//答案 
int main()
{
	cin>>ss;//快读读入字符串貌似不太对，所以用了cin 
	int i=0;//这是左边，即第一个字符 
	int j=ss.size()-1;//右边，即第二个字符 
	while(i<=j)//只要左右没碰在一起 
	 {
	 	if(ss[i]==ss[j])
	 	 {
	 	 	i++;
	 	 	j--;
	 	 	continue;
		 }//这是相等，证明匹配 （包括两个x） 
		if(ss[i]=='x')
		 {
		 	i++;
		 	tot++;
		 	continue;
		 }//如果右边不是x，左边是，就让答案加一，相当于在右边加了一个x，然后左边右移 
		if(ss[j]=='x')
		 {
		 	j--;
		 	tot++;
		 	continue;
		 }//同理 
		else
		{
		 cout<<"-1\n";
		 return 0;
	   }//两边不匹配切都不为x，证明不符合题意，输出-1然后结束 
	 }
	cout<<tot<<'\n';//能到这代表符合题意，直接输出记录的答案 
	return 0;//结束喽 
}
```


---

## 作者：cjZYZtcl (赞：0)

## 简单的回文字符串题
#### PS：样例3有错误，输出应该是0，而不是没有输出（实测）
我们可以用普通的判断回文的方法（双指针比较）来做这道题。

- 如果左右两指针所指的位置相等，那么就继续判断；
- 如果左边指针指的位置是 x，那么就在右边的位置插入一个 x，然后继续判断（相当于）；
- 如果右边指针指的位置是 x，那么就在左边对位置插入一个 x，然后继续判断；
- 否则输出 -1，退出程序。

最后输出插入的 x 的总数即可。

但是如果真的插入就太麻烦了，而插入的时候，实际上只有一个指针移动了，所以不需要插入，只要移动相应的指针，然后把插入总数累加一即可。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
char a[100005];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = 0;
	char ch = getchar();
	while(ch >= 'a' && ch <= 'z'){
		a[++n] = ch;
		ch = getchar();
	}
	int l = 1, r = n, sum = 0;
	while(l <= r){
		if(a[l] == a[r]){
			l++;
			r--;
		}
		else if(a[l] == 'x'){
			l++;
			sum++;
		}
		else if(a[r] == 'x'){
			r--;
			sum++;
		}
		else{
			write(-1);
			return 0;
		}
	}
	write(sum);
}
```


---


# Bishwock

## 题目描述

Bishwock is a chess figure that consists of three squares resembling an "L-bar". This figure can be rotated by 90, 180 and 270 degrees so it can have four possible states:

```
XX   XX   .X   X.
X.   .X   XX   XX
```

Bishwocks don't attack any squares and can even occupy on the adjacent squares as long as they don't occupy the same square.

Vasya has a board with $ 2\times n $ squares onto which he wants to put some bishwocks. To his dismay, several squares on this board are already occupied by pawns and Vasya can't put bishwocks there. However, pawns also don't attack bishwocks and they can occupy adjacent squares peacefully.

Knowing the positions of pawns on the board, help Vasya to determine the maximum amount of bishwocks he can put onto the board so that they wouldn't occupy the same squares and wouldn't occupy squares with pawns.

## 样例 #1

### 输入

```
00
00
```

### 输出

```
1```

## 样例 #2

### 输入

```
00X00X0XXX0
0XXX0X00X00
```

### 输出

```
4```

## 样例 #3

### 输入

```
0X0X0
0X0X0
```

### 输出

```
0```

## 样例 #4

### 输入

```
0XXX0
00000
```

### 输出

```
2```

# 题解

## 作者：QWQ_jyc (赞：4)

 表面上很复杂，其实贪心即可。
 
题目问可以往这个棋盘上放上多少个  L  型。

对两个字符数组进行排查四种情况。

```cpp
00 0X 00 X0
0X 00 X0 00
```
然后发现的  L  型进行标记。

因为我们让它填上格子，后面相同格子就不会误判。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,s;
char a[100],b[100];
int main(){
	cin>>a>>b;
	n=strlen(a);
	for(int i=0;i<n;i++){
		if(a[i]=='0'&&b[i]=='0'&&a[i+1]=='0'){
			a[i]='1';
			b[i]='1';
			a[i+1]='1';
			s++;
		}else
		if(a[i]=='0'&&b[i]=='0'&&b[i+1]=='0'){
			a[i]='1';
			b[i]='1';
			b[i+1]='1';
			s++;
		}else
		if(a[i]=='0'&&a[i+1]=='0'&&b[i+1]=='0'){
			a[i]='1';
			b[i+1]='1';
			a[i+1]='1';
			s++;
		}else
		if(a[i+1]=='0'&&b[i]=='0'&&b[i+1]=='0'){
			a[i+1]='1';
			b[i]='1';
			b[i+1]='1';
			s++;
		}	
	}		
	cout<<s;
	return 0;
}
```

后记：

贪心的正确性体现在这题能放就尽量放的思路，在对于题目查找 
  L  型较其它算法更简单易懂。

---

## 作者：fish_love_cat (赞：3)

贪心。

---

**思路：**

贪心的思考一下，把地图从左到右扫过去，能放则放，这样结果必然最优。因为现在你能放，假设它不会影响下一个摆放，那么不放白不放，肯定要放；假设他会影响，那么摆下一个也会影响这一个，结果还是摆 $1$ 个，不变，不如直接放。

还有，当某区域怎么放都行时，一定要优先放开口朝外的，不然结果可能会出现误差。

比如这组输入：

```
000
000
```

输出应为：

```
2
```

可是若前四格放开口朝内，会有一格无法放置导致误差。

哦对了在每放一个后记得先打上标记，防止误判多算。

---

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans;
int main(){
    string a,b;
    cin>>a>>b;//地图
    for(int i=1;i<a.size();i++)//四种摆法
    if(a[i-1]=='0'&&a[i]=='0'&&b[i-1]=='0')ans++,a[i]='X';//优先开口
    else if(a[i-1]=='0'&&a[i]=='0'&&b[i]=='0')ans++,a[i]='X',b[i]='X';//其他随便
    else if(a[i-1]=='0'&&b[i]=='0'&&b[i-1]=='0')ans++,b[i]='X';
    else if(b[i-1]=='0'&&a[i]=='0'&&b[i]=='0')ans++,a[i]='X',b[i]='X';
    cout<<ans;//答案
    return 0;
}
//？
```

---

## 作者：NOILinux_Ubuntu (赞：2)

### 前面的题解有点带坏小朋友们的意思，其实这道题不用DP，贪心即可

由于只有两行，对于每个棋子竖着的那条边，显然每列顶多放一个，那么如果我们顺着递推枚举列的话，肯定是能放则放。

因为如果现在能放却不放的话，对于后面的列本来只占用一个格子的再放就要占用两个格子，而且前面的格子也不会给后面的棋子提供空间。

所以如果这一列有两个格子，我们一定是尽量让它填上格子，然后由于前面的不会给后面的加贡献，所以先选前面的。

极短代码奉上
```
#include<bits/stdc++.h>
using namespace std;
#define ri register int
#define For(i,a,b) for(ri i=(a);i<=(b);++i)
const int MAXN=105;
int a[MAXN],ans,n;
char s[2][MAXN];
int main(){
	For(i,0,1)scanf("%s",s[i]+1); 
	n=strlen(s[0]+1);
	For(i,1,n)a[i]=((s[0][i]=='0')<<1)+(s[1][i]=='0'); 
	
	For(i,1,n)if(a[i]==3){
		if(a[i-1])++ans;
		else if(a[i+1])++ans,a[i+1]-=a[i+1]&(-a[i+1]);
		a[i]=0;
	}
	printf("%d\n",ans);
 return 0;
}
```

---

## 作者：Aelt (赞：1)

### 分析

一道贪心题。题目给定 $2 \times n$ 个字符，让你判定可以填充多少个由 `#` 组成的 `L` 图形。

观察样例，我们可以发现只有四种情况为可以填充，这四种情况如图所示（红色为不可填充，蓝色为可填充）：
![](https://cdn.luogu.com.cn/upload/image_hosting/gs4re1og.png)

这样，我们就可以从左往右扫一遍，如果符合如上这四种形态就可以增加答案数量。

例如上图第一组，就可以这样写：

```cpp
// 判断
if(a[i] == '0' && a[i + 1] == '0' && b[i] == '0') {
    ans ++;
    a[i] = 'X', a[i + 1] = 'X', b[i] = 'X'; // 标记为已填充
}
```
另外三种可能同理。

对于存棋盘，因为题目只给定了两行，所以就输入两个字符串即可。

[AClink](https://codeforces.com/problemset/submission/991/277764739)。

---

## 作者：cff_0102 (赞：1)

输入只有两行，所以完全可以直接从左到右判断每个 $4\times4$ 的正方形，只要能填一个“L”形，即这 $4\times4$ 的空间中被占用的格子数量 $\le1$，那么就直接把它靠左填上。

既然只用判断每个 $4\times4$ 空间格子数量，那么可以把第一行和第二行每一列的格子数量加到一起，这样更好判断。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	string s;cin>>s;
	int n=s.length();
	int a[n];
	for(int i=0;i<n;i++){
		char c;cin>>c;
		a[i]=(s[i]=='X')+(c=='X');//这一列“X”的个数
	}
	int ans=0;
	for(int i=1;i<n;i++){
		if(a[i]+a[i-1]<=1){
			ans++;
			if(a[i-1]==1)a[i-1]++,a[i]+=2;//左边那一格有东西了，那只能拐角向左
			else a[i-1]+=2,a[i]++;//否则拐角向右填
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ALIN_lin (赞：1)

这一题可以用贪心法来写。

如果落下来很多直角形的块块，（其实不只是直角形），那么肯定要让它尽量地把下面填满（不留空隙），这样得到的答案才是最优的。

那么我们分析一下：如果全是空的话，就一正一反地放就成了。

但如果不全是空的话，即会有 X 分割，那么会有完全分割和不完全分割两种情况（如下图）。

完全分割：
```cpp
00X0XX
0XX00X
```
不完全分割：
```cpp
XX00XX
X0000X
```
如果碰到了一种情况：
```cpp
X0X
000
```
那么我们将会面临着一个艰难的抉择：往左边放，还是往右边放？

所以我们往右边放的话，肯定会占用其它的空间，使得其不能再放一个合法的直角。所以我们碰到这种情况的时候，选左边的先放，这就是贪心策略。

~~题解仅供学习参考使用，禁止抄袭~~

AC 代码如下：

```cpp
#include<iostream>
#include<cstring>
using namespace std;

long long s;
char a[105],b[105];

int main(){
	cin>>a>>b;
	for(int i=0;i<strlen(a);i++){
		if(a[i]=='0'&&b[i]=='0'&&a[i+1]=='0'){
			a[i]='1',b[i]='1',a[i+1]='1';
			s++;
		}
		else if(a[i]=='0'&&b[i]=='0'&&b[i+1]=='0'){	 
			a[i]='1',b[i]='1',b[i+1]='1';
			s++;
		}
		else if(a[i]=='0'&&a[i+1]=='0'&&b[i+1]=='0'){
			a[i]='1',b[i+1]='1',a[i+1]='1';
			s++;
		}
		else if(a[i+1]=='0'&&b[i]=='0'&&b[i+1]=='0'){
			a[i+1]='1',b[i]='1',b[i+1]='1';
			s++;
		}	
	}		
	cout<<s;
	return 0;
}
```
```

---

## 作者：lin134 (赞：1)

这是一道很简单的题，用贪心即可。

题目问可以往这个棋盘上放上多少个 L 型。

四种情况即可。

```cpp
?0 0? 00 00
00 00 ?0 0?
```

但问题来了，如果遇到下面这几种情况要怎么办？

```cpp
?0? 000
000 ?0?
```
我们发现，如果往右边放的话，肯定会占用其它的空间，使得其不能再放一个合法的直角。所以我们碰到这种情况的时候，选左边的先放。

所以我们对两个字符数组进行排查，如果发现的 L 型进行标记，防止后面相同格子误判。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
#define Int int
using namespace std;
Int main(){
	int n,s;
	char a[105],b[105];
	scanf("%s%s",a,b);
	n=strlen(a);
	for(int i=0;i<n;i++){
		if(a[i]=='0'&&b[i]=='0'&&a[i+1]=='0'){
			a[i]='X',b[i]='X',a[i+1]='X',s++;
		}
		else if(a[i]=='0'&&b[i]=='0'&&b[i+1]=='0'){	 
			a[i]='X',b[i]='X',b[i+1]='X',s++;
		}
		else if(a[i]=='0'&&a[i+1]=='0'&&b[i+1]=='0'){
			a[i]='X',b[i+1]='X',a[i+1]='X',s++;
		}
		else if(a[i+1]=='0'&&b[i]=='0'&&b[i+1]=='0'){
			a[i+1]='X',b[i]='X',b[i+1]='X',s++;
		}	
	}		
	printf("%lld",s);
	return 0;
}
```


---

## 作者：傅思维666 (赞：1)


## 题解：

~~2019.10.24模拟赛各种假做法后来模拟AC场~~

模拟：

我们发现，所有的情况无外乎这么几种：

第一种：连着三列都是0，当且仅当这时，能一次性放进去两个直角形。

```
000
000
```

第二种：

```
?0  00
00  ?0
```

（双0在右侧）

第三种：

```
00  0?
0?  00
```

（双零在左侧）

依照题意模拟就行了

AC模拟代码：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=1e5+10;
bool v[5][maxn];
char s[5][maxn];
int ans,len;
int main()
{
	scanf("%s%s",s[1]+1,s[2]+1);
	memset(v,1,sizeof(v));
	len=strlen(s[1]+1);
	for(int i=1;i<=2;i++)
		for(int j=1;j<=len;j++)
			if(s[i][j]=='0')
				v[i][j]=0;
	for(int i=1;i<=len;i++)
	{
		if(!v[1][i]&&!v[2][i]&&!v[1][i+1]&&!v[2][i+1]&&!v[1][i+2]&&!v[2][i+2])//000
		{                                                                     //000
			v[1][i]=v[2][i]=v[1][i+1]=v[2][i+1]=v[1][i+2]=v[2][i+2]=1;
			i+=2;
			ans+=2;
			continue;
		}
		else if((!v[1][i+1]&&!v[2][i+1])&&(!v[1][i]||!v[2][i]))
	    {
			v[1][i+1]=v[2][i+1]=1;
			if(!v[1][i])
			{
				v[1][i]=1;
				i++,ans++;
				continue;
			}
			else
			{
				v[2][i]=1;
				i++,ans++;
				continue;
			}
			continue;
		}
		else if((!v[1][i]&&!v[2][i])&&(!v[1][i+1]||!v[2][i+1]))
		{
			v[1][i]=v[2][i]=1;
			if(!v[1][i+1])
			{
				v[1][i+1]=1;
				i++,ans++;
				continue;
			}
			else
			{
				v[2][i+1]=1;
				i++,ans++;
				continue;
			}
			continue;
		}
	}
	printf("%d",ans);
	return 0;
}
```



后来，本蒟蒻知道了还可以**贪心**？

~~玩过俄罗斯方块的都知道~~，如果落下来很多直角形的块块，（其实不只是直角形），那么肯定要让它尽量地把下面填满（不留空隙），这样得到的答案才是最优的。

那么我们分析一下：如果全是空的话，就一正一反地放就成了。

如果不全是空的话，即会有X分割，那么会有完全分割和不完全分割两种情况。

完全分割：（让人一看就很舒坦）

```
00X0XX
0XX00X
```

不完全分割：

```
XX00XX
X0000X
```

如果如果碰到了一种情况：（这里只是举局部例子）

```
X0X
000
```

那么我们将会面临着一个艰难的抉择：往左边放，还是往右边放？

根据刚刚的“俄罗斯方块原理”，如果往右边放的话，肯定会占用其它的空间，使得其不能再放一个合法的直角。所以我们碰到这种情况的时候，选左边的先放，这就是贪心策略。



---

## 作者：shenbairui (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF991D)
### 题目分析
其实题目意思是可以往这个棋盘上放上多少个 L 型。

不难证明有四种情况：

```cpp
00 0X 00 X0
0X 00 X0 00
```
然后搞一个变量进行计数，把格子进行标记，就可以了！
但是还有一种特殊的情况：当某区域怎么放都行时，一定要优先放开口朝外的，不然结果可能会出现误差。具体可以看楼上 @fish_love_cat 的写法。

情况如下：
```cpp
000
000
```



代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
string a,b;
int main(){
	cin>>a>>b;
	for(int i=0;i<a.size();i++){
		if(a[i]=='0'&&b[i]=='0'&&a[i+1]=='0'){
			a[i]='X';b[i]='X';a[i+1]='X';//标记
			ans++;//计数
		}else
			if(a[i]=='0'&&b[i]=='0'&&b[i+1]=='0'){
				a[i]='X';b[i]='X';b[i+1]='X';//标记
				ans++;//计数
			}else{
				if(a[i]=='0'&&a[i+1]=='0'&&b[i+1]=='0'){
					a[i]='X';b[i+1]='X';a[i+1]='X';//标记
					ans++;//计数
				}else{
					if(a[i+1]=='0'&&b[i]=='0'&&b[i+1]=='0'){
						a[i+1]='X';b[i]='X';b[i+1]='X';//标记
						ans++;//计数
					}
				}
			}
	}		
	cout<<ans;
	return 0;
}
```
由于洛谷的 RMJ 寄了，具体看[公告](https://www.luogu.com.cn/discuss/598533)，所以我到 CF 试了一下，能过。

[记录如下](https://codeforces.com/problemset/submission/991/276061559)

下期见！拜拜！

---

## 作者：Laoda_Bryant (赞：0)

## 思路
考虑贪心。  
从左往右扫，找到一个就标记一个即可。  
但是要注意，当遇见这种情况时

```
000
000
```

最优的方法是左右各放一个积木，共放入两块。但如果按照刚刚的方法，则有可能会是这样

```
0X0
XX0
```
所以在一些地方有多种放法时，应该优先放置开口朝右的积木。
## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string h1,h2;
int ans=0;
int main(){
	cin>>h1>>h2;
	int n=h1.size();
	for(int i=1;i<n;i++){
		if(h1[i-1]=='0'&&h2[i-1]=='0'&&h1[i]=='0'){
		    h1[i-1]='X',h2[i-1]='X',h1[i]='X';
			ans++;
		}
		if(h1[i-1]=='0'&&h2[i-1]=='0'&&h2[i]=='0'){
			h1[i-1]='X',h2[i-1]='X',h2[i]='X';
			ans++;
		}
		if(h1[i-1]=='0'&&h1[i]=='0'&&h2[i]=='0'){
		    h1[i-1]='X',h1[i]='X',h2[i]='X';
			ans++;
		}
		if(h2[i-1]=='0'&&h1[i]=='0'&&h2[i]=='0'){
			h2[i-1]='X',h1[i]='X',h2[i]='X';
			ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Union_Find (赞：0)

题目就是说，给你一个双层的图，让你求可以放多少个 L 形。

其实很简单，只需要一点贪心就够了，直接从左到右扫一遍过去，能放则放。但有一点，如果四个位置都空，就放开口朝右的，不然像下面这个就会卡住。

```
000
000
```

然后就是代码了，一定要把放过的记录起来。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll n, ans;
char a[100], b[100];
int main(){
    scanf ("%s %s", a + 1, b + 1);
    n = strlen(a + 1);
    for (int i = 1; i <= n; i++){
        if (a[i - 1] == '0' && a[i] == '0' && b[i - 1] == '0') ans++, a[i] = 'X';
        else if (a[i - 1] == '0' && a[i] == '0' && b[i] == '0') ans++, a[i] = 'X', b[i] = 'X';
        else if (a[i - 1] == '0' && b[i] == '0' && b[i - 1] == '0') ans++, b[i] = 'X';
        else if (b[i - 1] == '0' && a[i] == '0' && b[i] == '0') ans++, a[i] = 'X', b[i] = 'X';
    }
    printf ("%lld", ans);
	return 0;
}
```

---

## 作者：SpringFullGarden (赞：0)

## 题意

有一个 $2 \times n$ 的网格，求可以放下几个 `L`，即 

```
XX   XX   .X   X.
X.   .X   XX   XX
```

## 思路

考虑贪心。

从左往右找，找到就标记即可。

注意：当某区域有多种放法时，要先放这样的：

```
XX   X.
X.   XX
```

因为可能有这种情况出现：

```
112
122
```

## 代码

```cpp
int mp[3][105];

int main() {
	int n, ans = 0;
	for(int i = 1; i <= 2; i++) {
		string s; cin >> s; n = s.size(); s = " " + s;
		for(int j = 1; j <= n; j++) mp[i][j] = (s[j] == '0');
	}
	for(int i = 1; i < n; i++) {
		if(mp[1][i] && mp[1][i + 1] && mp[2][i]) 
			ans++, mp[1][i] = mp[1][i + 1] = mp[2][i] = 0;
		if(mp[1][i] && mp[1][i + 1] && mp[2][i + 1]) 
			ans++, mp[1][i] = mp[1][i + 1] = mp[2][i + 1] = 0;
		if(mp[1][i] && mp[2][i] && mp[2][i + 1]) 
			ans++, mp[1][i] = mp[2][i] = mp[2][i + 1] = 0;
		if(mp[1][i + 1] && mp[2][i] && mp[2][i + 1]) 
			ans++, mp[1][i + 1] = mp[2][i] = mp[2][i + 1] = 0;
	}
	cout << ans;
    return 0;
}
```

---

## 作者：Seanq (赞：0)

**线性dp**    
f[i][j][k]表示进行到第i列，第一格取不取，第二格取不取  
std:  

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int n;
int f[N][2][2]={0};//f[i][j][k]表示进行到第i列，第一格取不取，第二格取不取
char a[N],b[N];
bool x[N],y[N];
int ans=0;
int main()
{
	scanf("%s%s",a,b);//输入
	n=strlen(a);
	for(int i=0;i<n;i++)//预处理
	{
		x[i+1]=(a[i]=='0'?0:1);
		y[i+1]=(b[i]=='0'?0:1);
	}	
	for(int i=2;i<=n;i++)//dp转移
	{
		f[i][0][0]=max(max(f[i-1][0][0],f[i-1][1][1]),max(f[i-1][0][1],f[i-1][1][0]));
		if(x[i-1]==0&&y[i-1]==0&&y[i]==0)
			f[i][0][1]=f[i-1][0][0]+1;
		if(x[i-1]==0&&y[i-1]==0&&x[i]==0)
			f[i][1][0]=f[i-1][0][0]+1;
		if(x[i-1]==0&&x[i]==0&&y[i]==0)
			f[i][1][1]=max(f[i-1][0][1],f[i-1][0][0])+1;
		if(y[i-1]==0&&x[i]==0&&y[i]==0)
			f[i][1][1]=max(f[i][1][1],max(f[i-1][1][0]+1,f[i-1][0][0]+1));
	}
	for(int i=0;i<=1;i++)//找最大值
	{
		for(int j=0;j<=1;j++)
		{
			ans=max(ans,f[n][i][j]);
		}
	}
	printf("%d\n",ans);//愉快输出
	return 0;
} 
```

---

## 作者：flora715 (赞：0)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
/*【D. Bishwock】
给你一个2*n的棋盘，X表示障碍，问你可以往这个棋盘上放上多少个L型积木。  */
 
char s1[105],s2[105]; //上下两行
 
int main(){
    int ans=0; cin>>s1>>s2;
    int len=strlen(s1); //得到列数n的大小
    for(int i=0;i<len;i++){ //直接搜索4种L型
        if(s1[i]=='0'&&s2[i]=='0'&&s1[i+1]=='0') 
            s1[i]=s1[i+1]=s2[i]='x',ans++;
        else if(s1[i]=='0'&&s2[i]=='0'&&s2[i+1]=='0') 
            s1[i]=s2[i]=s2[i+1]='x',ans++;
        else if(s1[i]=='0'&&s1[i+1]=='0'&&s2[i+1]=='0') 
            s1[i]=s1[i+1]=s2[i+1]='x',ans++;
        else if(s2[i]=='0'&&s1[i+1]=='0'&&s2[i+1]=='0') 
            s2[i]=s1[i+1]=s2[i+1]='x',ans++;
    }
    cout<<ans<<endl;
}
```

---


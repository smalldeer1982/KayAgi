# Flag of Berland

## 题目描述

Berland之旗是满足以下条件的 $n \times m$ 矩形区域：

- 旗中包含三种颜色，相应地以字母“R”, “G”和“B”表示。

- 旗中包含三个“长条”，他们的长度和宽度相等（长条1的长度等于长条2的长度，也等于长条3的长度，宽度类似），并且互相平行，同时还平行于旗子的边缘。每个“长条”仅有一种颜色。

- 每个颜色仅能在一个“长条”中出现。 

现在给定由“R”, “G”和“B”构成的 $n \times m$ 矩形区域。请判断它是否是一个正确的Berland之旗，是则输出 "YES"，否则输出"NO"。

## 说明/提示

第三个样例中的区域不包含平行的“长条”。

第四个样例中虽然“长条”间互相平行，且都平行于边缘，但他们高度不同——2，1和1。

## 样例 #1

### 输入

```
6 5
RRRRR
RRRRR
BBBBB
BBBBB
GGGGG
GGGGG
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 3
BRG
BRG
BRG
BRG
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
6 7
RRRGGGG
RRRGGGG
RRRGGGG
RRRBBBB
RRRBBBB
RRRBBBB
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
4 4
RRRR
RRRR
BBBB
GGGG
```

### 输出

```
NO
```

# 题解

## 作者：array2022 (赞：2)

# 题解 003 题目 [CF837B](https://www.luogu.com.cn/problem/CF837B)

### 题目分析
* 主要思路是把旗子分成 $3$ 条，每次计算出这条中三种字符的数量，用数组记录。由于每条中只有一种字符，且每条中字符都不同，所以统计结束后数组中的元素不是 $0$ 就是 $\frac {n \times m} 3$（每条的字符数）。
* 在进行竖条判断和横条判断时，应该先判断 $n$ 和 $m$ 是否能被 $3$ 整除。因为如果 $n$ 不能被 $3$ 整除，显然横条判断结果为否（因为每条的宽度不可能一致），竖条判断同理。

------------

### 通过代码
```cpp
#include<iostream>
using namespace std;
int n,m,i,j,b[128],k,t;//数组开到这么多元素是为了方便访问。
bool ans;
char f[100][100],ch[3]={'R','G','B'};//这个字符数组也是为了后面方便。
bool check(){//判断是否全为 0 或 n*m/3。
	for (t=0;t<3;t++){
		if (b[ch[t]]!=0&&b[ch[t]]!=n*m/3){
			return 0;
		}
	}
	return 1;
}
int main(){
	cin>>n>>m;
	for (i=0;i<n;i++){
		for (j=0;j<m;j++){
			cin>>f[i][j];
		}
	}
	if (n%3==0){//开始横条判断。
		for (k=0;k<3;k++){
			for (i=k*n/3;i<(k+1)*n/3;i++){//遍历一个条。k*n/3表示开始的位置，(k+1)*n/3 表示结束的位置。
				for (j=0;j<m;j++){
					b[f[i][j]]++;//该字符的个数加一。
				}
			}
			if (check()){
				ans=1;
			}
			else{//只要有一次不满足，判断结果就为否，可以直接停止判断。
				ans=0;
				break;
			}
		}
	}
	b['R']=0;b['G']=0;b['B']=0;//还原用于的记录数组，方便竖条判断后面使用。
	if (m%3==0&&ans==0){
		for (k=0;k<3;k++){
			for (i=0;i<n;i++){
				for (j=k*m/3;j<(k+1)*m/3;j++){
					b[f[i][j]]++;
				}
			}
			if (check()){
				ans=1;
			}
			else{
				ans=0;
				break;
			}
		}
	}
	cout<<(ans?"YES":"NO");
	return 0;
}
```

------------

End.

---

## 作者：Elma_ (赞：1)

## Descreption
Berland之旗是满足以下条件的 $n \times m$ 矩形区域：

- 旗中包含三种颜色，相应地以字母“R”, “G”和“B”表示。

- 旗中包含三个“长条”，他们的长度和宽度相等（长条1的长度等于长条2的长度，也等于长条3的长度，宽度类似），并且互相平行，同时还平行于旗子的边缘。每个“长条”仅有一种颜色。

- 每个颜色仅能在一个“长条”中出现。

现在给定由“R”, “G”和“B”构成的 $n \times m$ 矩形区域。请判断它是否是一个正确的Berland之旗，是则输出 "YES"，否则输出"NO"。

## Solution&Code

这题的难度不高，只需要注意一些细节就可以，可以当做基础练习。

几个小优化（可能没什么用，看数据的强度）：

- 如果$n$和$m$都无法三等分，那么无论如何都不可能是Berland之旗。代码如下：

	```cpp
	if(n%3 != 0 && m%3 != 0)
	{
		cout<<"NO"<<endl;
		return 0;
	}
	```
- 如果旗子根本没有三种颜色，那么也无论如何都不可能是Berland之旗。我们可以在输入的时候顺便统计颜色。代码如下：
	```cpp
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			cin>>map[i][j];
			if(map[i][j] == 'R') r++;
			if(map[i][j] == 'G') g++;
			if(map[i][j] == 'B') b++;
		}
		
		if(!r || !g || !b)
		{
			cout<<"NO"<<endl;
			return 0;
		}
	```
然后就是正常的部分了。两种情况：

- 如果$n$能三等分：即长条的形状是横向的。考虑把每一个长条的第一个颜色作为这个长条颜色的代表。写一个函数判断：
```cpp
	void row()
	{
		if(map[0][0] == map[n/3][0] || map[0][0] == map[n/3*2][0] || map[n/3][0] == map[n/3*2][0])//如果有其中两个长条的颜色一样
			return;
		
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(map[i][j] != map[(i/(n/3))*(n/3)][0])//如果有颜色和这个长条应该有的颜色不一样
					return;
				
		cout<<"YES"<<endl;
		exit(0);//这里直接结束程序，以免之后多于输出
	}

```

- 如果$m$能三等分：长条形状是竖向的。思想同上，代码如下：
```cpp
	void col()
	{
		if(map[0][0] == map[0][m/3] || map[0][0] == map[0][m/3*2] || map[0][m/3] == map[0][m/3*2])
			return;
		
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(map[i][j] != map[0][(j/(m/3))*(m/3)])
					return;
				
		cout<<"YES"<<endl;
		exit(0);
	}

```

如果两个函数都return了，即不能组成Berland之旗，就输出NO。

完整代码就不贴了，把上面的代码整合起来也不难嘛。（逃

---

## 作者：xhz0311 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF837B)
## 题意理解
给出一个 $n \times m$ 的矩阵，判断是否满足以下条件：

- 有三个长宽均相等的“长条”，“长条”的边平行于旗帜边缘（这要求 $n$ $m$ 至少有一个为 $3$ 的倍数）；
- 每个长条中包含且只包含 $R$ $G$ $B$ 中的一个；
- $R$ $G$ $B$ 出现且只出现在三个“长条”中的一个。

如果满足，输出 `YES`，否则输出 `NO`。

## 思路
1. 如果 $n$ $m$ 均不为 $3$ 的倍数，直接 `NO`（违反第一条）。
2. 如果 $n \bmod 3=0, m \bmod 3 \neq 0$，
	1. 检查前 $\dfrac{n}{3}$ 行是否全为某一个颜色
    2. 检查中间 $\dfrac{n}{3}$ 行是否全为另一个颜色
    3. 检查后 $\dfrac{n}{3}$ 行是否全为第三个颜色
3. 如果 $m \bmod 3=0, n \bmod 3 \neq 0$
	1. 与上同理
4. 如果 $n \bmod 3=0, m \bmod 3 = 0$
	1. 以 $2$ 的方法检查
    2. 以 $3$ 的方法检查
    3. 满足一个即可

综上，可以把 $2$ 的检查方法和 $3$ 的检查方法封装为 `bool` 函数 `check_1` 和 `check_2`，然后只要给出的矩阵满足 `check_1 || check_2` 即可。


## 一大坑点
注意可能会有这种情况：
```
3 3
QQQ
WWW
EEE
```
完全符合 `check_2`，但是没有 $R$ $G$ $B$ 三种颜色！

---

## 作者：WOERDESUGX (赞：0)



### 题目大意

给你一个 $n×m$ 的矩阵，问它是否满足：　

 $1.$ 旗中只包含 ```R,G,B``` 三个字母。
 
 $2.$ 每一纵列或横列必须是同一种颜色，且每个长条的长对应相等，宽对应相等。
 
 $3.$ 已出现过的字母不得在后面再出现。
 
问给出的矩阵符不符合以上条件。

----------------------------

### 思路

我们通过读题可以得知，如果矩形的长和宽都不是三的倍数是不符合条件的，此时输出 ```NO```，在输入时我们可以记录一下，如果有字母不是 ```R,G,B``` 也是不符合条件的。此时输出然后直接结束~~我才不会告诉你我在这错了呢~~。

作为一名蒟蒻我就直接开始暴力，我对它进行分情况讨论，即 $n$ 为三的倍数 $m$ 不为三的倍数；$n$ 不为三的倍数 $m$ 为三的倍数和 $n$ 为三的倍数 $m$ 为三的倍数。

当 $n$ 为三的倍数 $m$ 不为三的倍数时，枚举 $n$ 如果 $n$ 不为 $n$ 除三的倍数并且第一个与上边的字母不同输出 ```NO```，并结束，否则继续枚举。当 $n$ 不为三的倍数 $m$ 为三的倍数和 $n$ 为三的倍数 $m$ 为三的倍数与其同理。

## ACcode

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,f=0,t1,t2,t3;
char c[110][110],s[5];
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j) {
        cin>>c[i][j];
        if(c[i][j]!='G'&&c[i][j]!='R'&&c[i][j]!='B') {
            cout<<"NO";return 0;
        }//如果出现不为R,G,B的字母直接结束
        if(c[i][j]=='G') t1++;else if(c[i][j]=='R') t2++;else if(c[i][j]=='B') t3++;
    }
    if(t1==0||t2==0||t3==0) {
        cout<<"NO";return 0;
    }//如果有一个字母未出现则必定不满足条件
    if(n%3!=0&&m%3!=0) {
        cout<<"NO";return 0;
    }
    else if(n%3==0&&m%3!=0) {
        for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j) {
            if(c[i][j]!=s[k]&&j==1&&(i%(n/3)==1||n==3)) s[++k]=c[i][j];//当
            if(c[i][j]!=s[k]&&(j!=1||(i%(n/3)!=1))) {
                cout<<"NO";return 0;
            }
        }
        cout<<"YES";
    }
    else if(m%3==0&&n%3!=0) {
        for(int i=1;i<=m;++i)
        for(int j=1;j<=n;++j) {
            if(c[j][i]!=s[k]&&j==1&&((i%(m/3)==1)||m==3)) s[++k]=c[j][i];
            else if(c[j][i]!=s[k]&&(j!=1||(i%(m/3)!=1))) {
                cout<<"NO";return 0;
            }
        }
        cout<<"YES";
    }
    else if(m%3==0&&n%3==0) {
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j) {
                if(c[i][j]!=s[k]&&j==1&&(i%(n/3)==1||n==3)) s[++k]=c[i][j];
                if(c[i][j]!=s[k]&&(j!=1||(i%(n/3)!=1))) {
                    f=1;break;//当不满足当前循环时直接跳出
                }
            }
            if(f==1) break;
        }
        memset(s,0,sizeof(s));k=0;
        if(f==1) {//当不满足上一个时再进行枚举
            for(int i=1;i<=m;++i) {
                for(int j=1;j<=n;++j) {
                    if(c[j][i]!=s[k]&&j==1&&((i%(m/3)==1)||m==3)) s[++k]=c[j][i];
                    else if(c[j][i]!=s[k]&&(j!=1||(i%(m/3)!=1))) {
                        cout<<"NO";return 0;
                    }
                }
            }
        }
        cout<<"YES";
    }
    return 0;
}
```

-----------------

~~终于码完力~~。

---

## 作者：Jamison (赞：0)

~~浅浅写个题解qwq~~

### 题目大意

 给出一个 $ n×m $ 的矩形，满足条件（这里省略）输出 YES，否则输出 NO。
 

------------
### 题目做法

先判断输出可以 NO 的条件：

1. 没有包含 3 种字母，缺少或增多了都不行。

1. 横或者列都不能被完全分成 3 份。

在看一下主程序，可以分成横或者列来进行枚举，分成三段进行枚举，遇到不符合的就直接退出即可。


------------
### 注意事项

注意横列时数组的变化即可，基本没有什么难度。


------------

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
bool r,g,b;
char a[101][101];
bool h(){//横
	if(n%3) return 0;
	for(int i=1;i<=n/3;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]!=a[1][1]) return 0;
		}
	}
	for(int i=n/3+1;i<=n/3*2;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]!=a[n/3+1][1]) return 0;
		}
	}
	for(int i=n/3*2+1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]!=a[n/3*2+1][1]) return 0;
		}
	}//分成三段
	return 1;
}
bool l(){  //和上面一样
	if(m%3) return 0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m/3;j++){
			if(a[i][j]!=a[1][1]) return 0;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=m/3+1;j<=m/3*2;j++){
			if(a[i][j]!=a[1][m/3+1]) return 0;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=m/3*2+1;j<=m;j++){
			if(a[i][j]!=a[1][m/3*2+1]) return 0;
		}
	}
	return 1;
}
int main(){
	cin>>n>>m;
	if(n%3 && m%3){cout<<"NO";return 0;}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];	
			if(a[i][j]=='R') r=1;
			else if(a[i][j]=='G') g=1;
			else if(a[i][j]=='B') b=1;
		}//判断是否缺少字母
	}
	if(!r||!g||!b){cout<<"NO";return 0;}
	if(h() || l()){cout<<"YES";return 0;}
	cout<<"NO";
}
```





---

## 作者：Sternenlicht (赞：0)

思路：

先特判无解情况：

1. $n$ 和 $m$ 均不能被 $3$ 整除。

2. 读入数据中 R,B,G 至少有一个没出现。

这时输出 NO。

主程序：

1. 判断横向情况：若 $n$ 不能被 $3$ 整除，返回 $0$。否则，将 $n$ 平均分成 $3$ 份，判断每份中的字符是否全部相等。

2. 判断竖向情况：若 $m$ 不能被 $3$ 整除，返回 $0$。否则，将 $m$ 平均分成 $3$ 份，判断每份中的字符是否全部相等。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define endl '\n'
#define lowbit(x) (x&-x)
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define INF 0x3f3f3f3f
namespace IO{
	inline LL read(){
	    LL x=0,f=1;char ch=getchar();
	    for (;!isdigit(ch);ch=getchar())if (ch=='-')f=-1;
	    for (;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
	    return x*f;
	}
	inline void write(LL x,char c='\n'){
	    if (x){
	    	if (x<0)x=-x,putchar('-');
	    	char a[30];short l;
	    	for (l=0;x;x/=10)a[l++]=x%10^48;
	    	for (l--;l>=0;l--)putchar(a[l]);
		}
		else putchar('0');putchar(c);
	}
	inline char getc(){
		char ch=getchar();
		while (isspace(ch))ch=getchar();
		return ch;
	}
}
using namespace IO;
using namespace std;

const int N = 110;
char a[N][N];int n,m,R,G,B;
bool line(){//横向判断 
	if (n%3)return 0;
	for (int i=1;i<=n/3;i++)
		for (int j=1;j<=m;j++)
			if (a[i][j]!=a[1][1])
				return 0;
	for (int i=n/3+1;i<=n/3*2;i++)
		for (int j=1;j<=m;j++)
			if (a[i][j]!=a[n/3+1][1])
				return 0;
	for (int i=n/3*2+1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (a[i][j]!=a[n/3*2+1][1])
				return 0;
	return 1;
}
bool rows(){//竖向判断 
	if (m%3)return 0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m/3;j++)
			if (a[i][j]!=a[1][1])
				return 0;
	for (int i=1;i<=n;i++)
		for (int j=m/3+1;j<=m/3*2;j++)
			if (a[i][j]!=a[1][m/3+1])
				return 0;
	for (int i=1;i<=n;i++)
		for (int j=m/3*2+1;j<=m;j++)
			if (a[i][j]!=a[1][m/3*2+1])
				return 0;
	return 1;
}
int main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			a[i][j]=getc();
			if (a[i][j]=='R')R++;
			if (a[i][j]=='G')G++;
			if (a[i][j]=='B')B++;
		}
	if (n%3&&m%3||!R||!G||!B)return puts("NO"),0;//特判无解情况 
	if (line())return puts("YES"),0;//判断行 
	if (rows())return puts("YES"),0;//判断列 
	return puts("NO"),0;
}
```

---

## 作者：_xxy_ (赞：0)

**一道简单的模拟题**，只需注意处理细节即可

无解特判：

因为三个长条的长度和宽度相等，所以当行数 $ n $ 和列数 $ m $ 均不能被 $ 3 $ 整除时答案为无解。

当字符数组中只出现了不到 $ 3 $ 种颜色时，很明显答案为无解，这一点可以在输入时判断。

**核心部分：**

分横向均分和竖向均分判断。

当 $ n $ 能被 $ 3 $ 整除时，把字符数组横向均分成 $ 3 $ 份，暴力枚举判断每一份中的字符是否全部相同即可。

竖向均分也同理。

**AC Code**

```cpp
#include<iostream>
using namespace std;
int n,m;
bool r,g,b;
char a[101][101];
bool hang(){    //判断横向均分
	if(n%3) return 0;
	char c=a[1][1];
	for(int i=1;i<=n/3;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]!=c) return 0;
		}
	}
	c=a[n/3+1][1];
	for(int i=n/3+1;i<=n/3*2;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]!=c) return 0;
		}
	}
	c=a[n/3*2+1][1];
	for(int i=n/3*2+1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]!=c) return 0;
		}
	}
	return 1;
}
bool lie(){    //判断竖向均分
	if(m%3) return 0;
	char c=a[1][1];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m/3;j++){
			if(a[i][j]!=c) return 0;
		}
	}
	c=a[1][m/3+1];
	for(int i=1;i<=n;i++){
		for(int j=m/3+1;j<=m/3*2;j++){
			if(a[i][j]!=c) return 0;
		}
	}
	c=a[1][m/3*2+1];
	for(int i=1;i<=n;i++){
		for(int j=m/3*2+1;j<=m;j++){
			if(a[i][j]!=c) return 0;
		}
	}
	return 1;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	if(n%3&&m%3){
		cout<<"NO";
		return 0;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];	
			if(a[i][j]=='R') r=1;
			else if(a[i][j]=='G') g=1;
			else if(a[i][j]=='B') b=1;
		}
	}
	if(!r||!g||!b){
		cout<<"NO";
		return 0;
	}
	if(hang()){
		cout<<"YES";
		return 0;
	}
	if(lie()){
		cout<<"YES";
		return 0;
	}
	cout<<"NO";
	return 0;
}
```

**完结撒花！！！**

---

## 作者：XMK_萌新 (赞：0)

emmmm真心不是特别难，只要找对方法就可以了             
首先，一只合格滴berland旗应该是这样的：         
每一列的颜色都相同，每一行三种颜色均分。       
但是！      	 然而！          
有可能像样例1那样，每行的颜色相同，每列三颜色均分。        
那就把它行列倒过来嘛……（为了统一操作）

可得思路如下：           
1. 读入
2. 判断是否可能不需倒过来 （如果可能不需倒，那就不倒；如果按当前判断会出问题，就一定倒。逻辑有点晕，思考一下。）
  
3. 判断是否是berland旗

上代码

```cpp
//码风较丑，请勿围观。
#include <iostream>
#include <cstdio>
using namespace std;
int n,m;
char b[103][103];
bool check()	//是否要倒过来
{
    for(int i=1;i<m;i++)
        if(b[0][i]!=b[0][i-1]) return false;
    return true;
    //如果|第一列|就不符合，就倒过来，否则不用倒。。
}
void exchange()	//矩阵转换。c++党一枚，不习惯用strcpy，凑合着看吧。。
{
    char c[103][103];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) c[j][i]=b[i][j];
    swap(n,m);	//长宽交换
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) b[i][j]=c[i][j];
}
bool samecol(int l,int r,char color)	//在第l列~第r列区间内，是否颜色全都一致为'color'
{
    for(int i=0;i<n;i++)
        for(int j=l;j<=r;j++)
            if(b[i][j]!=color) return false;
    return true;
}
int main()
{
    cin>>n>>m;
    gets(b[102]);	//把回车读进来
    for(int i=0;i<n;i++) gets(b[i]);	//读入
    if(check()) exchange();	//如果按当前判断会出问题，就倒过来
    if(m%3!=0||	//emmmm一行不能三等分还搞虾米(O_o)？？  果断判掉。
       !samecol(0,m/3-1,b[0][0])||
       !samecol(m/3,m*2/3-1,b[0][m/3])||
       !samecol(m*2/3,m-1,b[0][m-1])) cout<<"NO";	//三段
    else if(b[0][0]==b[0][m/3]||b[0][0]==b[0][m-1]||b[0][m-1]==b[0][m/3]) cout<<"NO";	//颜色不同
    else cout<<"YES";
    return 0;	//圆满结束

```
也就41行（不压行），不是特别繁琐，思路对就容易了。

---


# Inna and Choose Options

## 题目描述

Inna 在玩井字棋的升级版。游戏规则如下：

在游戏开始前，他将 $12$ 张卡片排列在桌子上。每张卡片上都有一个字符 `X` 或 `O`。然后玩家选择两个正整数 $a$ 和 $b$ $(a\times b=12)$ 
，然后根据放在桌子上的卡片制作一个 $a\times b$ 大小的表格，前 $b$ 
 张卡片组成第一行，接下来的 $b$ 张卡片组成第二行，依此类推，最后的 $b$ 张卡片组成最后一行（第 $a$ 行）。玩家获胜的条件是表格中某一列的所有卡片都含有字符 `X`。否则，玩家失败。

Inna 已经把 $12$ 张卡片按顺序放在了桌子上。但不幸的是，她不知道选择什么样的 $a$ 和 $b$ 来帮助她赢得游戏，所以她让你输出可能的所有选择 $a,b$，以及能够获胜的方式。

## 样例 #1

### 输入

```
4
OXXXOXOOXOOX
OXOXOXOXOXOX
XXXXXXXXXXXX
OOOOOOOOOOOO
```

### 输出

```
3 1x12 2x6 4x3
4 1x12 2x6 3x4 6x2
6 1x12 2x6 3x4 4x3 6x2 12x1
0
```

# 题解

## 作者：shiziyu111 (赞：2)

## 题目巨意
给定一个长为 $12$，仅包含 ```O``` 和 ```X``` 的字符串，其中，每 $b$ 张卡片组成一行，共组成 $a$ 行（$a$，$b$ 为整数，自己选择）。

例如：

```OOXOOXXOXXXX``` 可以组成：
```
OOX
OOX
XOX
XXX
（b=4）
```
或：
```
OOXO
XOXO
XXXX
（b=3）
```
以及更多的排列方式。

当有一列全部为 ```X``` 时，此排列算作一种获胜的方式。

请求出所有获胜方式，以递增的方式输出。
## 分析
由于 $a\times b$ 一共只有 $6$ 种可能，即：

$1\times12$。

$2\times6$。

$3\times4$。

$4\times3$。

$2\times6$。

$12\times1$。

因此我们可以模拟所有的情况。

具体做法如下：

1. 设一个数组 $b$，表示列数。
2. 在第 $i$ 种情况下，枚举第一到第 $b[i]$ 种情况。
3. 当该列符合标准时，存入答案。
4. 最后再快乐的输出，就可以了。
## $\color{lightgreen}{AC}$  $\color{lightgreen}{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	for(int i=1;i<=T;i++)
	{
		char s[13];
		int b[6]={1,2,3,4,6,12};//具体方案
		int ans[7]={0},cnt=0;
		for(int i=1;i<=12;i++)
		{
			cin>>s[i];
		}
		for(int i=0;i<6;i++)
		{
			int flagg=0;//记录此方案是否成立
			for(int k=1;k<=b[i];k++)
			{
				if(flagg==1)
				{
					continue;
				}
				int flag=1;
				for(int j=k;j<=12;j+=b[i])
				{
					if(s[j]=='O')
					{
						flag=0;
					}
				}
				if(flag==1)
				{
					cnt++;
					ans[cnt]=b[i];
					flagg=1;
				}
			}	
		}
		cout<<cnt<<" ";
		for(int i=cnt;i>=1;i--)
		{
			cout<<12/ans[i]<<"x"<<ans[i]<<" ";//用正序存的b，但是要正序输出a，所以要逆序输出
		}
		cout<<endl;
	}
	
	return 0;
}
```

---

## 作者：xuchuhan (赞：2)

## Description

给定 $n$ 个长度为 $12$ 的只包含 `X` 或 `O` 的字符串。对于每个字符串，可以将其按顺序转化成一个长为 $a$，宽为 $b$ 的字符矩阵。输出满足要求的矩阵个数，以及每个满足要求的矩阵的 $a,b$。

定义一个满足要求的矩形为这个矩形中的至少一列的字符全为 `X`。

## Solution

按题意模拟。

枚举每个合法的 $a,b$ 使得 $a \times b = 12$，得到 $a,b$ 后就可以将字符串转换为字符矩阵，然后判断这个矩阵是否合法，如果合法，答案加 $1$ 并存储好这组合法的 $a,b$，最后统一输出。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,ans;
char a[20];
int y12[15]={0,1,2,3,4,6,12};
char c[15][15];
int p[15];
signed main(){
	cin>>t;
	while(t--){
		for(int i=1;i<=12;i++)
			cin>>a[i];
		for(int i=1;i<=6;i++){
			int x=y12[i];
			int y=12/y12[i];
			//合法的两条边
			for(int j=1;j<=12;j++){
				int h=j/y+(j%y!=0);
				int l=j%y+y*(j%y==0);
				c[h][l]=a[j];
			}
			//转化矩阵
			bool flag=0;
			for(int j=1;j<=y;j++){
				bool f=0;
				for(int i=1;i<=x;i++){
					if(c[i][j]!='X')
						f=1;
				}
				if(!f)
					flag=1;
			}
			if(flag){
				ans++;
				p[ans]=x;
			}
			//如果合法就存储
		}
		cout<<ans<<" ";
		for(int i=1;i<=ans;i++)
			cout<<p[i]<<"x"<<12/p[i]<<" ";
		cout<<"\n";
		//统一输出
		ans=0;
	}
	return 0;
}
```

---

## 作者：wangzihan_ (赞：1)

## 题目大意
给 $n$ 个长为 $12$ 的序列，把他以一段接一段的方式排成一个矩形。
要求这个矩形至少有一列每个字符都为 `X`。如果有则输出这个矩形的长宽。

## 做法

首先明确，矩形的长度共有以下 $6$ 种情况：
- $1\times12$
- $2\times6$
- $3\times4$
- $4\times3$
- $6\times2$
- $12\times1$

如下图所示，我们可以通过枚举，先找到每一列的第一个，通过加上现在的 $j$ 往下扫描，发现这一列相同后直接统计这个矩形的答案即可。


```
0 1 2 3 4
1 X O X O
2 X X X O
3 X O O O
4 X O X X
```
如：现在找到 $(1,2)$，所在序列位置为 $2$，接下来要找 $(2,2)$，也就是在序列上第 $6$ 个字符，不难发现，所在序列位置为 $2+4$，也就是加上当前矩形的列数。

这样暴力统计，就可以得出答案了。

- 更加详细的解释已经放到代码里了，具体代码如下：

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n; 
char st[10005];
int ansa[1005],ansb[1005],cnt=0,ans=0;//保存输出 
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s",st+1);
		cnt=0,ans=0;
		for(int i=1;i<=12;i++)//从1开始枚举能被12整除的所有数 
			if(12%i==0)//如果能被12整除 
			{
				int j=12/i;//转换j=12/i 
				int flag=-1;//赋值为-1，后续如果发现满足则改为0 
				for(int x=1;x<=j;x++)//枚举每一列中的第一个位置 
				{
					if(st[x]=='O') continue;//如果为O则跳过 
					flag=0;
					int y=x;
					while(y<=12)//循环枚举每一列 
					{
						if(st[y]!=st[x]) {flag=1;break;}//如果发现不同，则退出 
						y+=j;
					}
					if(!flag) break;//如果在循环中发现了相同，那么这种情况满足，直接退出统计答案 
				}
				if(flag==0)//发现flag被改成了1，说明这一种情况满足 
				{
					ans++;//统计答案 
					ansa[++cnt]=i;
					ansb[cnt]=j;
				}
			}
		printf("%d ",ans);//输出答案 
		for(int i=1;i<=ans;i++)
			printf("%dx%d ",ansa[i],ansb[i]);
		printf("\n");
	}
}


```

---

## 作者：Andy_WA (赞：1)

## 题意
有 $T$ 组测试数据：
> 每行一个十二个字符的 `OX` 字符串。\
> 你需要将其划分为 $b$ 个 $a$ 个字符的字串。\
> 对于其中一个字串，如果一行均为 `X` 则此字符串为合法的，求 $a,b$ 如何划分是合法的，输出合法的划分个数，以及所有划分方法。
## 分析
### 题目类型
多测题：**多测不清空，爆零两行泪。**
### 数据范围
+ $1≤t≤100$
+ $a~·~b=12$ 且 $a$ 与 $b$ 是 $12$ 的因数

**So，直接暴力不会超时！**
## 思路
~~没啥思路，直接暴力。~~

### 判断条件
+ $1×12$：\
  若有一个 `X` 就合法。\
  `arr[0]=='X' || arr[1]=='X' || arr[2]=='X' || arr[3]=='X' || arr[4]=='X' || arr[5]=='X' || arr[6]=='X' || arr[7]=='X' || arr[8]=='X' || arr[9]=='X' || arr[10]=='X' || arr[11]=='X'`


---


+ $2×6$：\
  若有连续两个 `X` 就合法。\
  `arr[0]=='X' && arr[6]=='X' || arr[1]=='X' && arr[7]=='X' || arr[2]=='X' && arr[8]=='X' || arr[3]=='X' && arr[9]=='X' || arr[4]=='X' && arr[10]=='X' || arr[5]=='X' && arr[11]=='X'`


---


+ $3×4$：\
  以此类推。\
  `Text_3x4 arr[0]=='X' && arr[4]=='X' && arr[8]=='X' || arr[1]=='X' && arr[5]=='X' && arr[9]=='X' || arr[2]=='X' && arr[6]=='X' && arr[10]=='X' || arr[3]=='X' && arr[7]=='X' && arr[11]=='X'
arr[9]=='X' || arr[10]=='X' || arr[11]=='X'`


---


+ $4×3$：\
  以此类推。\
  `Text_4x3 arr[0]=='X' && arr[3]=='X' && arr[6]=='X' && arr[9]=='X' || arr[1]=='X' && arr[4]=='X' && arr[7]=='X' && arr[10]=='X' || arr[2]=='X' && arr[5]=='X' && arr[8]=='X' && arr[11]=='X'`


---


+ $6×2$：\
  以此类推。\
  `Text_6x2 arr[0]=='X' && arr[2]=='X' && arr[4]=='X' && arr[6]=='X' && arr[8]=='X' && arr[10]=='X' || arr[1]=='X'  &&  arr[3]=='X' && arr[5]=='X' && arr[7]=='X' && arr[9]=='X' && arr[11]=='X'`


---


+ $12×1$：\
  以此类推。\
  `Text_12x1 arr[0]=='X' && arr[1]=='X' && arr[2]=='X' && arr[3]=='X' && arr[4]=='X' && arr[5]=='X' && arr[6]=='X' && arr[7]=='X' && arr[8]=='X' && arr[9]=='X' && arr[10]=='X' && arr[11]=='X'`

**有这些代码就好好写了。。。**
## 代码

```cpp
#include<bits/stdc++.h>
#define Text_1x12 arr[0]=='X' || arr[1]=='X' || arr[2]=='X' || arr[3]=='X' || arr[4]=='X' || arr[5]=='X' || arr[6]=='X' || arr[7]=='X' || arr[8]=='X' || arr[9]=='X' || arr[10]=='X' || arr[11]=='X'
#define Text_2x6 arr[0]=='X' && arr[6]=='X' || arr[1]=='X' && arr[7]=='X' || arr[2]=='X' && arr[8]=='X' || arr[3]=='X' && arr[9]=='X' || arr[4]=='X' && arr[10]=='X' || arr[5]=='X' && arr[11]=='X'
#define Text_3x4 arr[0]=='X' && arr[4]=='X' && arr[8]=='X' || arr[1]=='X' && arr[5]=='X' && arr[9]=='X' || arr[2]=='X' && arr[6]=='X' && arr[10]=='X' || arr[3]=='X' && arr[7]=='X' && arr[11]=='X'
#define Text_4x3 arr[0]=='X' && arr[3]=='X' && arr[6]=='X' && arr[9]=='X' || arr[1]=='X' && arr[4]=='X' && arr[7]=='X' && arr[10]=='X' || arr[2]=='X' && arr[5]=='X' && arr[8]=='X' && arr[11]=='X'
#define Text_6x2 arr[0]=='X' && arr[2]=='X' && arr[4]=='X' && arr[6]=='X' && arr[8]=='X' && arr[10]=='X' || arr[1]=='X'  &&  arr[3]=='X' && arr[5]=='X' && arr[7]=='X' && arr[9]=='X' && arr[11]=='X'
#define Text_12x1 arr[0]=='X' && arr[1]=='X' && arr[2]=='X' && arr[3]=='X' && arr[4]=='X' && arr[5]=='X' && arr[6]=='X' && arr[7]=='X' && arr[8]=='X' && arr[9]=='X' && arr[10]=='X' && arr[11]=='X'
using namespace std;
long long T; 
int main(){
	cin>>T;
	while(T--){
		long long cnt=0;
		string arr,ans="";
		cin>>arr;
		if(Text_1x12) ans+=" 1x12",cnt++;
		if(Text_2x6) ans+=" 2x6",cnt++;
		if(Text_3x4) ans+=" 3x4",cnt++;
		if(Text_4x3) ans+=" 4x3",cnt++;
		if(Text_6x2) ans+=" 6x2",cnt++;
		if(Text_12x1) ans+=" 12x1",cnt++;
		cout<<cnt<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：__owowow__ (赞：1)

## CF400A Inna and Choose Options 题解
[CF传送门](https://codeforces.com/problemset/problem/400/A)

[洛谷传送门](https://www.luogu.com.cn/problem/CF400A)

### 题目大意
给定 $n$ 个长为 $12$ 的字符串 $s$，字符串的每一项为 ```x``` 或者 ```O```。将其按顺序转化为 $a \times b$ 的矩阵。

一个矩阵满足要求定义为有任意一列全部是 ```X```。求字符串 $s$ 的所有转化矩形有几个满足要求。

### 题目思路
由于 $12$ 很小，只可能分解出 $6$ 种矩形。分别为

- $1 \times 12$
- $2 \times 6$
- $3 \times 4$
- $4 \times 3$
- $6 \times 2$
- $12 \times 1$

针对每一种情况进行模拟即可。

### AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t;
string str,ans;
bool fl;
signed main(){
    cin>>n;
    while(n--){
        ans=' ';
        t=0;
        cin>>str;
        fl=false;
        for(int i=0;i<12;i++) if(str[i]=='X') fl=true; //模拟 1*12 情况
        if(fl) t++,ans+="1x12 ";
        fl=false;
        for(int i=0;i<6;i++) if(str[i]=='X'&&str[i+6]=='X') fl=true; //模拟 2*6 情况
        if(fl) t++,ans+="2x6 ";
        fl=false;
        for(int i=0;i<4;i++) if(str[i]=='X'&&str[i+4]=='X'&&str[i+8]=='X') fl=true; //模拟 3*4 情况
        if(fl) t++,ans+="3x4 ";
        fl=false;
        for(int i=0;i<3;i++) if(str[i]=='X'&&str[i+3]=='X'&&str[i+6]=='X'&&str[i+9]=='X') fl=true; //模拟 4*3 情况
        if(fl) t++,ans+="4x3 ";
        fl=false;
        for(int i=0;i<2;i++) if(str[i]=='X'&&str[i+2]=='X'&&str[i+4]=='X'&&str[i+6]=='X'&&str[i+8]=='X'&&str[i+10]=='X') fl=true; //模拟 6*2 情况
        if(fl) t++,ans+="6x2 ";
        fl=true;
        for(int i=0;i<12;i++) if(str[i]=='O') fl=false; //模拟 12*1 情况
        if(fl) t++,ans+="12x1";
        cout<<t<<ans<<endl;
    }
    return 0;
}


```

---

## 作者：OIerWu_829 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF400A)

## 思路

由于情况最多只有 $6$ 种，所以直接暴力枚举所有情况。

先用 $n$ 行 $m$ 列的二维矩阵存储字符串 $s$，然后一列一列的看，如果有一列的所有字符都是 `X`，那么这个方案是可行的，要把计数器 $cnt$ 加一，再把这个方案存储到数组中，最后输出就可以了。

```cpp
#include <iostream>
using namespace std;
char a[20][20];
int ans1[10], ans2[10];
const int x[] = {1, 2, 3, 4, 6, 12};
const int y[] = {12, 6, 4, 3, 2, 1};
int main()
{
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int cnt = 0;
        for (int k = 0; k < 6; k++) {
            int n = x[k], m = y[k], id = 0;
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= m; j++)
                    a[i][j] = s[id++]; // 存储字符串 s 的每一个字符
            for (int i = 1; i <= m; i++) {
                bool flag = true;
                for (int j = 1; j <= n; j++)
                    if (a[j][i] == 'O') flag = false;
                if (flag) { ans1[++cnt] = n; ans2[cnt] = m; break; } // 可行，存储起来
            }
        }
        cout << cnt << " \n"[cnt == 0]; // 如果方案数为 0 则直接换行
        for (int i = 1; i <= cnt; i++)
            cout << ans1[i] << "x" << ans2[i] << " \n"[i == cnt];
    }
    return 0;
}
```

---

## 作者：BigSmall_En (赞：1)

就是一道模拟题，纯模拟就行，关键就是读题了（之前因为题目没有读懂直接做错了）

## 题意描述

（英文不好，只能说一下大致意思）

给定 $n$ 个长度为 $12$ 的只包含 `X` 或 `O` 的字符串。对于每个字符串，可以将其转化成一个 $a\times b=12$ 的二维字符矩阵。对于这样一个 $a\times b$ 的矩形，认为它可行就是要找到**一列的字符全部为 `X`** 。

输出对于每一个字符串他的合法矩形数量和每个合法方案的 $a,b$ 。

## 题解

对于每一个字符串，利用循环划分成若干个长度为 $i$ 的字符串 $S$ ，则对于 $S$ 的长度开一个桶，则在原字符串中第 $k$ 个字符就在整个矩阵的第 $k\bmod i$ 列上。然后判断每个列上的 `X` 个数时候等于 $\frac{12}{i}$ 即可，有则合法。

## 代码

```cpp
#include <cstdio>
using namespace std;
const int N=12;
char s[N+1];
int stk[N],top,bot[N+1];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%s",s+1);top=0;
		for(int i=1;i<=N;++i){
			if(N%i!=0)continue;
			memset(bot,0,sizeof(bot));
			for(int j=1;j<=N;++j)
				bot[j%i+1]+=s[j]=='X'?1:0;
			for(int j=1;j<=i;++j)
				if(bot[j]==N/i)
					{stk[++top]=i;break;}
		}
		printf("%d",top);//首先输出可行数
		for(int i=top;i>=1;--i){//栈顶的划分序列长度长一些
			printf(" %dx%d",N/stk[i],stk[i]);
		}putchar('\n');
	}
	return 0;
}
```





---

## 作者：CobaltChloride (赞：1)

```
#include<bits/stdc++.h>
using namespace std;
int t,i,n;
char _26[6][2],_34[4][3],_43[3][4],_62[2][6];
int a[7];
string s;
int check(char c){
	return c=='X';
}
int main(){
	cin>>t;
	while(t--){
		n=0;
		memset(a,0,sizeof(a));
		//清零 
		cin>>s;
		for(i=0;i<=11;i++) _26[i%6][i/6]=_34[i%4][i/4]=_43[i%3][i/3]=_62[i%2][i/2]=s[i];//构造图形 
		for(i=0;i<=11;i++) if(s[i]=='X') n++;
		if(n==0){
			cout<<0<<endl;
			continue;
		}
		if(n==12){
			cout<<"6 1x12 2x6 3x4 4x3 6x2 12x1"<<endl;
			continue;
		}
		//特判 
		a[1]=1;
		for(i=0;i<=5;i++) if(check(_26[i][0])&&check(_26[i][1])){
			a[2]=1;
			break;
		}
		for(i=0;i<=3;i++) if(check(_34[i][0])&&check(_34[i][1])&&check(_34[i][2])){
			a[3]=1;
			break;
		}
		for(i=0;i<=2;i++) if(check(_43[i][0])&&check(_43[i][1])&&check(_43[i][2])&&check(_43[i][3])){
			a[4]=1;
			break;
		}
		for(i=0;i<=1;i++) if(check(_62[i][0])&&check(_62[i][1])&&check(_62[i][2])&&check(_62[i][3])&&check(_62[i][4])&&check(_62[i][5])){
			a[5]=1;
			break;
		}
		//判断是否可行 
		n=0;
		for(i=1;i<=6;i++) if(a[i]==1) n++;//统计可行方法个数 
		cout<<n;
		if(a[1]==1) cout<<" 1x12";
		if(a[2]==1) cout<<" 2x6";
		if(a[3]==1) cout<<" 3x4";
		if(a[4]==1) cout<<" 4x3";
		if(a[5]==1) cout<<" 6x2";
		//判断输出 
		cout<<endl;//别忘换行 
	}
	return 0;
}
```

---

## 作者：Hanrui1206 (赞：0)

## 思路
这是一道模拟题，纯模拟就行。

给定 $n$ 个长度为 $12$ 的只包含 `X` 或 `O` 的字符串。对于每个字符串，可以将其按顺序转化成一个长为 $a$，宽为 
$b$ 的字符矩阵。

由于 $12$ 很小，只可能分解出 $6$ 种矩形。分别为：
- $1 \times 12$
- $2 \times 6$
- $3 \times 4$
- $4 \times 3$
- $6 \times 2$
- $12 \times 1$

我们一一模拟就行。用 `if` 语句每种方法都判断一遍。

## 核心代码
```cpp
//判断1×12的情况
if (a[0] == 'X' || a[1] == 'X' || a[2] == 'X' || a[3] == 'X' || a[4] == 'X' || a[5] == 'X' || a[6] == 'X' || a[7] == 'X' || a[8] == 'X' || a[9] == 'X' || a[10] == 'X' || a[11] == 'X') ans += " 1x12";
//判断2×6的情况
if (a[0] == 'X' && a[6] == 'X' || a[1] == 'X' && a[7] == 'X' || a[2] == 'X' && a[8] == 'X' || a[3] == 'X' && a[9] == 'X' || a[4] == 'X' && a[10] == 'X' || a[5] == 'X' && a[11] == 'X') ans += " 2x6";
//判断3×4的情况
if (a[0] == 'X' && a[4] == 'X' && a[8] == 'X' || a[1] == 'X' && a[5] == 'X' && a[9] == 'X' || a[2] == 'X' && a[6] == 'X' && a[10] == 'X' || a[3] == 'X' && a[7] == 'X' && a[11] == 'X') ans += " 3x4";
//判断4×3的情况
if (a[0] == 'X' && a[3] == 'X' && a[6] == 'X' && a[9] == 'X' || a[1] == 'X' && a[4] == 'X' && a[7] == 'X' && a[10] == 'X' || a[2] == 'X' && a[5] == 'X' && a[8] == 'X' && a[11] == 'X') ans += " 4x3";
//判断6×2的情况
if (a[0] == 'X' && a[2] == 'X' && a[4] == 'X' && a[6] == 'X' && a[8] == 'X' && a[10] == 'X' || a[1] == 'X' && a[3] == 'X' && a[5] == 'X' && a[7] == 'X' && a[9] == 'X' && a[11] == 'X') ans += " 6x2";
//判断12×1的情况
if (a[0] == 'X' && a[1] == 'X' && a[2] == 'X' && a[3] == 'X' && a[4] == 'X' && a[5] == 'X' && a[6] == 'X' && a[7] == 'X' && a[8] == 'X' && a[9] == 'X' && a[10] == 'X' && a[11] == 'X') ans += " 12x1";
```

---

## 作者：Norsuman371 (赞：0)

# 思路
将 $12$ 张卡片分成矩阵，如果矩阵中有一列全都是 `X` 就输出这种排列方式，输出方式看样例，这里要注意输出的是 `x` 是小写的，还有对应关系。最终结果按照题意模拟即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        char str[15];
        int vis[15];
        memset(vis, 0, sizeof(vis));
        memset(str, '\0', sizeof(str));
        cin >> str;
        int ans = 0, cnt = 0;
        for (int i = 0; i < 12; i++)
            if (str[i] == 'X')
                cnt++;
        if (cnt == 0)
            cout << 0 << endl;
        else {
            vis[0] = 1;
            ans++;

            int f = false;
            for (int i = 0; i < 6; i++) //2*6
                if (str[i] == 'X' && str[i + 6] == 'X')
                    f = true;
            if (f)
                vis[1] = 1, ans++;

            f = false;
            for (int i = 0; i < 3; i++) //4*3
                if (str[i] == 'X' && str[i + 3] == 'X' && str[i + 6] == 'X' && str[i + 9] == 'X')
                    f = true;
            if (f)
                vis[2] = 1, ans++;

            f = false;
            for (int i = 0; i < 4; i++) //3*4
                if (str[i] == 'X' && str[i + 4] == 'X' && str[i + 8] == 'X')
                    f = true;
            if (f)
                vis[3] = 1, ans++;

            f = false;
            for (int i = 0; i < 2; i++) //6*2
                if (str[i] == 'X' && str[i + 2] == 'X' && str[i + 4] == 'X' && str[i + 6] == 'X' && str[i + 8] == 'X' && str[i + 10] == 'X')
                    f = true;
            if (f)
                vis[4] = 1, ans++;
            if (cnt == 12) ans++;
            printf("%d", ans);
            if (vis[0]) printf(" 1x12");
            if (vis[1]) printf(" 2x6");
            if (vis[3]) printf(" 3x4");
            if (vis[2]) printf(" 4x3");
            if (vis[4]) printf(" 6x2");
            if (cnt == 12) printf(" 12x1");
            printf("\n");
        }
    }
    return 0;
}
```

# 记录

[$\textup{AC}$](https://www.luogu.com.cn/record/163391542)

---

## 作者：xzz_0611 (赞：0)

[题目传送门](/problem/CF400A)

---
这道题很简单，由于只有 $12$ 张卡牌，想要构成长方形的表格，只有 $6$ 种办法：
- $1 \times 12$
- $2 \times 6$
- $3 \times 4$
- $4 \times 3$
- $6 \times 2$
- $12 \times 1$

既然只有这 $6$ 种办法，同时，又只有 $12$ 张卡牌，完全可以用 `if` 语句每种方法都判断一遍，并不需要像楼下那些题解那样用循环一个一个判断，不过当卡片张数变多时就不能一个一个判断了，所以还是要学会楼下那些大佬们的方法。

废话不多说，直接上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) {
		string arr,ans="";//ans为最终的答案
		cin>>arr;
		//判断1×12的情况
		if(arr[0]=='X'||arr[1]=='X'||arr[2]=='X'||arr[3]=='X'||arr[4]=='X'||arr[5]=='X'||arr[6]=='X'||arr[7]=='X'||arr[8]=='X'||arr[9]=='X'||arr[10]=='X'||arr[11]=='X') ans+=" 1x12";
		//判断2×6的情况
		if(arr[0]=='X'&&arr[6]=='X'||arr[1]=='X'&&arr[7]=='X'||arr[2]=='X'&&arr[8]=='X'||arr[3]=='X'&&arr[9]=='X'||arr[4]=='X'&&arr[10]=='X'||arr[5]=='X'&&arr[11]=='X') ans+=" 2x6";
		//判断3×4的情况
		if(arr[0]=='X'&&arr[4]=='X'&&arr[8]=='X'||arr[1]=='X'&&arr[5]=='X'&&arr[9]=='X'||arr[2]=='X'&&arr[6]=='X'&&arr[10]=='X'||arr[3]=='X'&&arr[7]=='X'&&arr[11]=='X') ans+=" 3x4";
		//判断4×3的情况
		if(arr[0]=='X'&&arr[3]=='X'&&arr[6]=='X'&&arr[9]=='X'||arr[1]=='X'&&arr[4]=='X'&&arr[7]=='X'&&arr[10]=='X'||arr[2]=='X'&&arr[5]=='X'&&arr[8]=='X'&&arr[11]=='X') ans+=" 4x3";
		//判断6×2的情况
		if(arr[0]=='X'&&arr[2]=='X'&&arr[4]=='X'&&arr[6]=='X'&&arr[8]=='X'&&arr[10]=='X'||arr[1]=='X'&&arr[3]=='X'&&arr[5]=='X'&&arr[7]=='X'&&arr[9]=='X'&&arr[11]=='X') ans+=" 6x2";
		//判断12×1的情况
		if(arr[0]=='X'&&arr[1]=='X'&&arr[2]=='X'&&arr[3]=='X'&&arr[4]=='X'&&arr[5]=='X'&&arr[6]=='X'&&arr[7]=='X'&&arr[8]=='X'&&arr[9]=='X'&&arr[10]=='X'&&arr[11]=='X') ans+=" 12x1";
		cout<<ans.size()/4<<ans<<endl;//因为每多一种方案，ans的长度就会加4，所以用ans.size()/4可以算出可行方案的数量
	}
	return 0;
}
```
---
管理员给过，QAQ

---


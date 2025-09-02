# [NWRRC 2015] Black and White

## 题目描述

陪审团有一个很棒的艺术创意——用一大堆相同大小的黑白方块创建一个矩形面板。面板应该有恰好 $b$ 个 4-连通的黑色区域和 $w$ 个 4-连通的白色区域。

请记住，一个颜色的 4-连通区域是面板方块的一个极大集合，使得：

任何两个区域的方块颜色相同；

对于区域的任何两个方块，都存在一个连接它们的方块序列，使得序列中的任何两个连续方块共享一个公共边。

除了这个艺术创意，陪审团已经开发了一个程序来生成面板的设计。但由于这个问题涉及艺术，任何新的解决方案对陪审团来说都极其重要。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2 3
```

### 输出

```
6 7
@@@@@@@
@.@@@@@
@@...@@
@@@@@@@
.......
@@@@@@@
```

# 题解

## 作者：gaoyangyang (赞：5)

会解题的前提是知题意
## 翻译
#### 题目描述（精简版）
给定正整数 $b$,$w$ 请你构造出一个黑白矩阵，使得矩阵内恰有 $b$ 个黑色连通块和 $w$ 个白色连通块。
#### 输入格式
输入仅有一行，包含 $b$,$w$ 即黑色和白色区域的数量。（$1 \le b , w \le 1000$）
#### 输出格式
输出的第一行包含两个整数 $r$,$c$，表示你构造出的矩阵的行数和列数。接下来是一个 $r\times c$ 的矩阵，表示你构造出的黑白矩阵。其中 $@$ 代表黑色,$.$ 代表白色。
## 题解
看到这道题我们的第一反应应该是将问题简单化。在这里我们将问题分为两个部分：

1. 构建矩阵
2. 输出规格

首先我们先考虑构建矩阵，我们不妨先不考虑黑和白，先想如何构建一个单一符号矩阵，如下：

```
@@
@@
@@
@@
@@

//这是一个有@组成的2*5矩阵
```

想必大家都会，并且在这里还可少考虑一个“列”的因素（因为矩阵大小自定，所以满足题目条件只需调整“行”而不用考虑“列”），在这里我用 $2$ 作为列：


```cpp
for (int i=0;i<n;i++)
{
  cout<<"@@"<<endl;
}
//n为行数
```

接下来，我们考虑符号，这里要考虑两种情况：

1. $w$ 等于 $b$
2. $w$ 或 $b$ 等于1

我们先考虑第一种，$w$ 等于 $b$，我们可以轻易构出下方矩阵。

```cpp
//b=2,w=2
@@
..
@@
..
//————华丽分割线————
..
@@
..
@@

```

代码实现：

```cpp
for (int i=0;i<(w+b)/2;i++)
{
  cout<<"@@"<<endl;
  cout<<".."<<endl;
}
//n为行数
```

接下来是第二种 $w$ 或 $b$ 等于1，我们可以轻易构出下方矩阵。

```cpp
//b=1,w=3
@@
.@
@@
.@
@@
.@
@@
//反之
```

代码实现：

```cpp
for (int i=0;i<w;i++)
{
  cout<<"@@"<<endl;
  cout<<".@"<<endl;
 }cout<<"@@";
```
接着我们就会发现任何的 $b$ 和 $w$ 都可以拆成以上两种情况的组合，例如：$6$ 和 $7$ 可以拆成 $5$ 和 $5$ 组合 $1$ 和 $2$。

下方是矩阵构造的代码：
```cpp
//思路是一样的，这里为了方便书写采用while循环
while (w!=0 or b!=0)
	{
		if (b>w)
		{
			while (w>1 and b>1)
			{
				cout<<"@@"<<endl;
				b--;
				cout<<".."<<endl;
				w--;
			}
			if (w==1)
			{
				w--;
				cout<<"@@"<<endl;
				while (b!=0)
				{
					cout<<".@"<<endl;
					cout<<"@@"<<endl;
					b--;
				}
			}		
		}
		else
		{
			while (w>1 and b>1)
			{
				cout<<".."<<endl;
				w--;
				cout<<"@@"<<endl;
				b--;
			}
			if (b==1)
			{
				b--;
				cout<<".."<<endl;
				while (w!=0)
				{
					cout<<"@."<<endl;
					cout<<".."<<endl;
					w--;
				}
			}			
		}
	}
```

接下来我们考虑第二块：输出规格。

同上将矩阵分成两个部分，就可以得出：

部分一的大小为 $(\min(w,b)-1) \times 2$。

部分二的大小为 $(\max(w,b) - \min(w,b) + 1) \times 2+1$。

我们再相加，就可得出 $(\min(w,b)-1) \times 2 + (\max(w,b) - \min(w,b) + 1) \times 2+1$。

”行“我们就解决了，我们再将列人为的定为 $2$（其他也可以，只要对应矩阵就好）。

至此这道题我们就解决了，下面上代码！！！

```cpp

#include<bits/stdc++.h>
using namespace std;
int main()
{
	int w,b;
	cin>>w>>b;
	cout<<(min(w,b)-1)*2+1+(max(w,b)-min(w,b)+1)*2<<" "<<2<<endl;
	
	while (w!=0 or b!=0)
	{
		if (b>w)
		{
			while (w>1 and b>1)
			{
				cout<<"@@"<<endl;
				b--;
				cout<<".."<<endl;
				w--;
			}
			if (w==1)
			{
				w--;
				cout<<"@@"<<endl;
				while (b!=0)
				{
					cout<<".@"<<endl;
					cout<<"@@"<<endl;
					b--;
				}
			}		
		}
		else
		{
			while (w>1 and b>1)
			{
				cout<<".."<<endl;
				w--;
				cout<<"@@"<<endl;
				b--;
			}
			if (b==1)
			{
				b--;
				cout<<".."<<endl;
				while (w!=0)
				{
					cout<<"@."<<endl;
					cout<<".."<<endl;
					w--;
				}
			}			
		}
	}
	return 0;
}
 
```

---

## 作者：pythoner713 (赞：4)

基础构造题。对于 $b\le w$ 的情况（如 $b=4,w=5$），我们可以构造出如下的通解：

![](https://cdn.luogu.com.cn/upload/image_hosting/h3em3uth.png)

- 上端 $2(b-1)$ 行是交替的黑白条纹。可以看出，这一部分包含： $(b-1)$ 个黑色连通块，$(b-1)$ 个白色连通块。

- 下端是 $2(w-b)+3$ 行被黑块包围住的白块。计算发现，这一部分包含：$1$ 个黑色连通块，$(w-b+1)$ 个白色连通块。

因此一共包含 ：

$(b-1)+1={\bf b}$ **个黑色连通块**

$(b-1)+(w-b+1)={\bf w}$ **个白色连通块**

正好符合题目要求。

另外对于 $b>w$ 的情况，只需交换 $b,w$，然后反色输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

int b, w, t;

int main(){
	cin >> b >> w;
	if(b > w) swap(b, w), t = 1;
	printf("%d %d\n", w * 2 + 1, 3);
	for(int i = 1; i < b; i++){
		cout << (t ? "...\n@@@\n" : "@@@\n...\n");
	}
	for(int i = 1; i <= (w - b) * 2 + 3; i++){
		if(i & 1) cout << (t ? "...\n" : "@@@\n");
		else cout << (t ? ".@.\n" : "@.@\n");
	}
	return 0;
}
```


（顺便写了 SPJ，如果发现我理解错了欢迎指正

---

## 作者：ycy1124 (赞：2)

### 题意
给出 $b,w$，希望你构造一个有 $b$ 个黑色连通块和 $w$ 个白色连通块的矩阵。
### 思路
首先发现，此题的难点是如何将黑白连通块之间的差补上。我们可以默认黑色连通块大于白色连通块，不满足时输出交换一下两个字符即可。

当 $b=w$ 的时候非常简单，只需要类似 `.@.@` 输出即可。

考虑如何补差，最开始想的是将他们的相同部分按一行 `.` 一行 `@` 处理掉，在最后一行放一行 `@` 和 `.` 交替出现的即可。你会发现，最后一行所有的 `@` 都和上一行的 `@` 连在一起，所以这一行的 `.` 就可以拿去补差。此时矩阵的大小为 $(2\times b+1)\times(2\times b-2\times w)$，在 $b=1000,w=500$ 时给出的矩阵大小不符合条件。

此时我们换一种方法。我们默认第一行是 `.@.`，第二行是 `@@@` 的 $2\times 3$ 的矩阵为一组，我们发现，在一组矩阵中白色连通块比黑色连通块多 $1$。我们不妨将两组这样的举证上下相连，发现其白色连通块比黑色连通块多 $3$。当 $n$ 组上下相连白色就比黑色多 $2\times n-1$ 块。于是我们可以通过这样的方式来补差，当补多了的时候将第一行的白色连通块减一即可。在补完差之后又可以按原来的一行 `.`，一行 `@` 来填。最终得到的矩阵大小为 $((n-m)\div2\times2+m\times2)\times3$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[2]={'.','@'};
int n,m;//n就是题面中的b，m就是w
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m;
    if(n==m){
        cout<<m*2<<' '<<1<<'\n';
        for(int i=1;i<=m;i++){
            cout<<ch[0]<<'\n';//当相等的时候一行@一行.
            cout<<ch[1]<<'\n';
        }
        return 0;
    }
    if(m>n){
        swap(n,m);
        swap(ch[0],ch[1]);
    }
    cout<<(n-m)/2*2+m*2<<' '<<3<<'\n';
    int w=n-m+1;//需要补的数量，由于黑的多了1，所以要多补一个
    while(w){
        if(w>=2){
            cout<<ch[1]<<ch[0]<<ch[1]<<'\n';//@.@或.@.
            cout<<ch[0]<<ch[0]<<ch[0]<<'\n';//...或@@@
            w-=2;
        }
        else{
            cout<<ch[1]<<ch[0]<<ch[0]<<'\n';//@..或.@@
            cout<<ch[0]<<ch[0]<<ch[0]<<'\n';//...或@@@
            w--;
        }
    }
    for(int i=1;i<=m-1;i++){
        cout<<ch[1]<<ch[1]<<ch[1]<<'\n';//一行.一行@
        cout<<ch[0]<<ch[0]<<ch[0]<<'\n';
    }
    return 0;
}
```
[AC 记录。](https://www.luogu.com.cn/record/198305477)

---

## 作者：lostxxx (赞：1)

# 题目分析

一开始，我的思路是构造一个形如一列一列的方式，对于每个 $b,w$ 单独开一列，大概是这样，$b=4,w=4$。

```
01010101
01010101
01010101
```

对于这种构造方式，需要对 $b,w$ 之间的大小关系进行一定的处理，但是当时不知道为什么突然就放弃了这种方式，换成了类似于城墙一样的方式，大小为 $2 \times l$。

我们可以先只构造第一行，我们不妨设 $b\ge w$，长度为 $l$，那么，对于黑色的联通块就可以实现每隔 $\left \lfloor \frac{l}{n} \right \rfloor $ 的长度放置一个 `@`。

然后，我们先暂时假定第二行全部为 `.`，那么此时的白色联通块数量为一，我们发现，每当我们将上面的 `@` 和下面的 `@` 连通起来，那么黑色联通块数量不变，而白色联通块数量增加 $1$。那么我们可以继续构造知道黑色联通块数量和白色联通块数量相同。

那么对于 $b<w$ 的情况同理，我们只用将 `@` 和 `.` 的符号对调一下即可。

代码如下。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m;
char ma[3][2010];
ll maxn=2000;
int main(){
	cin>>n>>m;
	cout<<2<<' '<<maxn<<endl;
	if (n>=m){
		m--;
		ll tmp=maxn/n;
		ll times=1;
		for (int i=1;i<=max(1ll,maxn-tmp*n);i++){
			cout<<'.';
			ma[1][i]='.';
		}
		for (int i=max(1ll,maxn-tmp*n)+1;i<=maxn;i++){
			if (times%tmp==1){
				cout<<'@';
				ma[1][i]='@';
			}else{
				cout<<'.';
				ma[1][i]='.';
			}
			times++;
		}
		cout<<endl;
		for (int i=1;i<=maxn;i++){
			if (ma[1][i]=='@' && m>0){
				m--;
				cout<<'@';
			}else{
				cout<<'.';
			}
		}
	}else{
		swap(n,m);
		m--;
		ll tmp=maxn/n;
		ll times=1;
		for (int i=1;i<=max(1ll,maxn-tmp*n);i++){
			cout<<'@';
			ma[1][i]='@';
		}
		for (int i=max(1ll,maxn-tmp*n)+1;i<=maxn;i++){
			if (times%tmp==1){
				cout<<'.';
				ma[1][i]='.';
			}else{
				cout<<'@';
				ma[1][i]='@';
			}
			times++;
		}
		cout<<endl;
		for (int i=1;i<=maxn;i++){
			if (ma[1][i]=='.' && m>0){
				m--;
				cout<<'.';
			}else{
				cout<<'@';
			}
		}
	}
}
/*2000 2
*/
```

---

## 作者：wang1h (赞：1)

### [P7049 \[NWRRC2015\] Black and White](https://www.luogu.com.cn/problem/P7049)

## 题意

给定正整数 $b,w$，构造一个黑白矩阵，使得矩阵内恰有 $b$ 个黑色连通块和 $w$ 个白色连通块（连通块分别以 `@` 和 `.` 表示）。

## 思路

为了方便表述，本文中矩阵左上角坐标为 $(1,1)$，右下角坐标为 $(n,m)$（即这是一个 $n$ 行 $m$ 列的矩阵，其中 $n,m$ 的具体取值见后文）。

在这里提供一种较简便的构造方案：

1\. 将 $(1,1)$ 至 $(n,m)$ 设为白色。

```
..........
..........
..........
..........
```

2\. 将 $(2,1)$ 至 $(2,m-1)$ 设为黑色，为第三步做准备。

```
..........
@@@@@@@@@.
..........
..........
```

3\. 将 $(1,2),(1,4),(1,6)\dots (1,2w-2)$ 设为黑色，构造出 $w-1$ 个白色连通块，加上第一步 $1$ 个作为背景的，共 $w$ 个白色连通块。

```
.@.@.@.@..
@@@@@@@@@.
..........
..........
```

4\. 将 $(4,2),(4,4),(4,6)\dots (4,2b-2)$ 设为黑色，构造出 $b-1$ 个白色连通块，加上第三步 $1$ 个用于分隔白色的，共 $b$ 个黑色连通块。

```
.@.@.@.@..
@@@@@@@@@.
..........
.@.@.@....
```

这是 $b=4,w=5$ 时的一种构造方式，至此可以发现矩阵长为 $2\times\max(b,w)$ , 宽为 $4$，矩阵大小在题目限定范围内。

## 代码

```cpp
#include<cstdio>
bool a[5][2005];//0表示白，1表示黑
int b,w,n,m;
int main(){
	scanf("%d%d",&b,&w);
	n=4;m=2*(b>w?b:w);
	printf("%d %d\n",n,m);
	for(int i=1;i<m;i++)a[2][i]=1;
	for(int i=2;--w;i+=2)a[1][i]=1;//循环 w-1 次
	for(int i=2;--b;i+=2)a[4][i]=1;
	for(int i=1;i<=n;i++,putchar('\n'))
		for(int j=1;j<=m;j++)putchar(a[i][j]?'@':'.');
	return 0;
}
```

---

## 作者：liujunxi1001 (赞：1)

[P7049 [NWRRC2015] Black and White](https://www.luogu.com.cn/problem/P7049)

# Solution

对于这道构造题，我们其实可以这么做：

我们将列设为 $3$。

###### ~~别问就是懒~~

               
在 **$b\ne1 $ 或 $w\ne1$** 时我们可以这么打印：
```cpp
while(){	//while我就不写了	
	if(b>=w) cout<<"***"<<endl<<"@@@"<<endl;//部分一
	else cout<<"@@@"<<endl<<"***"<<endl;
}
```
然后可以开始这样打印通解：
```cpp
if(b==w){				//特判
	cout<<"***"<<endl<<"@@@";
	return 0;
} 
else if(b>w) cout<<"***"<<endl;
else cout<<"@@@"<<endl;
while(){	//while我就不写了
	if(b>w) cout<<"@*@"<<endl<<"***"<<endl;b-=2;//部分二
	else cout<<"*@*"<<endl<<"@@@"<<endl;w-=2;
}
if(b>w && b==1) cout<<"**@"<<endl;
else if(b<w && w==1) cout<<"*@@"<<endl;
```
通过以上代码可以发现部分一有 **$(\min(b,w)-1 )\times2$** 行，
部分二有 **$\max(b,w)-\min(b,w)+2$** 行。

所以可得：$\\(\min(b,w)-1)\times2+(\max(b,w)-\min(b,w)+2)\\=\min(b,w) \times 2-2+\max(b,w)-\min(b,w)+2\\=\max(b,w)+\min(b,w)\\=b+w$

所以最后的矩阵就是 $b+w$ 行 $3$ 列啦。

# Code


```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int b,w;
	cin>>b>>w;
	cout<<b+w<<" "<<3<<endl;
	int p=0; 
	if(b>=w){
		while(b!=1&&w!=1){
			cout<<"***"<<endl<<"@@@"<<endl;
			b--;w--;
			p+=2;
		}
		if(b==w){
			cout<<"***"<<endl<<"@@@";
			return 0;
		} 
		else cout<<"***"<<endl;
		while(b>1){
			cout<<"@*@"<<endl<<"***"<<endl;
			b-=2;
		}
		if(b==1) cout<<"@@*"<<endl;
	}
	else{
		while(b!=1&&w!=1){
			cout<<"@@@"<<endl<<"***"<<endl;
			b--;w--;
		}
		cout<<"@@@"<<endl;
		while(w>1){
			cout<<"*@*"<<endl<<"@@@"<<endl;
			w-=2;
		}
		if(w==1) cout<<"*@@"<<endl;
	}
	return 0;
}
```

---

## 作者：ADNAP (赞：1)

很明显的构造痕迹，我们可以这样构造：

先写出一个行为二，列为两种颜色中较多者的数量乘以二的矩阵。

对于每一行，一开始从左到右黑色和白色交替出现。

根据需要，我们每改变第一行的一个黑色就能让白色少一个；改变白色的同理。由此即可构造出满足题意的矩阵。

但其实第二行不需要在一开始写出了，因为是固定的。

注意第一行第一个是不能进行操作的，其操作并不能减少连通块。

### Code
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+1e4,M=1e3+1e2;
ll b,w;
ll len;
char s[M*2];
signed main()
{
    cin>>b>>w;
    len=max(b,w)*2;
    cout<<2<<" "<<len<<"\n";
    for(ll i=1;i<=len;i+=2)s[i]='@',s[i+1]='.';
    for(ll i=3;i<=len,b>w;i+=2)s[i]='.',b--;
    for(ll i=2;i<=len,w>b;i+=2)s[i]='@',w--;
    for(ll i=1;i<=len;i++)cout<<s[i];
    cout<<"\n";
    for(ll i=1;i<=len/2;i++)cout<<"@.";
}
```

---


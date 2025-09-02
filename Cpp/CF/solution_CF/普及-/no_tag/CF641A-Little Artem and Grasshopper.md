# Little Artem and Grasshopper

## 题目描述

有一只蚱蜢和一个有着$n$个格子的条子，蚱蜢刚开始在第$1$个格子上。每个格子上都标有下次跳的方向以及距离。当蚱蜢跳出边界时就会停止。请问蚱蜢是否会一直跳下去？

## 样例 #1

### 输入

```
2
&gt;&lt;
1 2
```

### 输出

```
FINITE
```

## 样例 #2

### 输入

```
3
&gt;&gt;&lt;
2 1 1
```

### 输出

```
INFINITE```

# 题解

## 作者：cyz_czy (赞：1)

这道题面有点坑，一开始我以为要将`&lt;`和`&gt;`两种表示法读取成$<$和$>$两种方向标，结果不是。。。。。。

## 正片开始：

对于方向标，题目会直接给我们，即$<$和$>$两个符号会直接输入，不需进行额外判断；然后我们就可以根据每个格子上的方向标和距离标识来递推（递归）进行蚱蜢的跳跃。若一个格子被蚱蜢踩了两次，则蚱蜢是可以无限跳的；若蹦出了条子，则是无法无限跳跃的。

# Code：
递归：
只要没有格子被踩两次或者蚱蜢跳出条子则继续。

```
#include <iostream>

const int N=1e5+1e1;

int l[N];//距离表示

int p[N];//判断每个格子被踩过的次数

std::string a;//方向标


int m;


void f(int x){
	p[x]++;//踩一次
	if(p[x]==2){//若踩了两次则可以无限跳跃
		printf("INFINITE");
		exit(0);//直接终止程序
	}
	
	if(a[x-1]=='>')
		x+=l[x];
	else
		x-=l[x];//跳跃
	
	if(x>m||x<1){//若跳出界限则不能无限跳
		printf("FINITE");
		exit(0);//直接终止程序
	}
	
	f(x);//继续跳
	
	return ;//养成好习惯
}

int main(){//此部分自行理解
	scanf("%d",&m);
	
	std::cin>>a;
	
	for (int i = 1 ; i <= m ; i++ )	
		scanf("%d",&l[i]);
	
	f(1);
	
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/109745860)


------------


递推：
即进行死循环，若一个格子被踩两次或者跳出界限则终止循环。

```
#include <iostream>

const int N=1e5+1e1;

int l[N];//距离表示

int p[N];//判断每个格子被踩过的次数

std::string a;//方向标


int m;


int main(){//此部分自行理解
	scanf("%d",&m);
	
	std::cin>>a;
	
	for (int i = 1 ; i <= m ; i++ )	
		scanf("%d",&l[i]);
	
	for(int i=1;;){
		
		p[i]++;
		if(p[i]==2){
			printf("INFINITE");
			exit(0);//直接终止程序
		}
		
		if(a[i-1]=='>')
			i+=l[i];
		else
			i-=l[i];
		
		if(i<1||i>m){
			printf("FINITE");
			exit(0);//直接终止程序
		}
	}
	
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/109748685)

祝你 $\color{green}AC$ ！

---

## 作者：WoodReal12 (赞：0)

## 题意

有一只蚱蜢和一个有着 $n$ 个格子的条子，蚱蜢刚开始在第 $1$ 个格子上。每个格子上都标有下次跳的方向以及距离。当蚱蜢跳出边界时就会停止，输出 `FINITY`；若不会停止，输出 `INFINITY`。

## 思路

我们可以发现，当蚱蜢跳到同一个位置上两次时，代表永远也不会停止。于是，我们可以打出暴力代码：

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int n;
struct gezi{
	bool op;//0为向左，1为向右
	int x; 
}a[100005];
int book[100005];//标记每个点到达次数 
bool chk(){
	for(int i=1;i<=n;i++)
		if(book[i]>=2)
			return true;
	return false;
}
int main() {
	cin>>n;
	for(int i=1;i<=n;i++){
		char c;
		cin>>c;
		if(c=='<')
			a[i].op=0;
		else
			a[i].op=1;
	}
	for(int i=1;i<=n;i++)
		cin>>a[i].x;
	int now=1;
	while(!chk()){
		book[now]++;
//		cout<<now<<endl;
		if(a[now].op==0)
			now-=a[now].x;
		else
			now+=a[now].x;
//		cout<<now<<endl;
		if(now<1||now>n){
			cout<<"FINITE"<<endl;
			return 0;
		}
	}
	cout<<"INFINITE"<<endl;
    return 0;
}
```

~~然后我们就可以获得 [TLE](https://www.luogu.com.cn/record/155966913) 的好成绩。~~

那么，怎么优化呢？

在暴力代码中，我们超时的原因是每次都要检查一遍 $book$ 数组，这使得效率很低。

于是，我们可以将原代码中的检查更改为下面这种代码：

```cpp
int tmp=now+a[now].op*a[now].x;
```

这一行代码可以将原来的数组记录换成 $tmp$ 和 $now$ 两个变量的滚动记录，效率必然大大提高。

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int n;
struct gezi{
	int op;//-1为向左，1为向右
	int x; 
}a[100005];
int book[100005];
int main() {
	cin>>n;
	for(int i=1;i<=n;i++){
		char c;
		cin>>c;
		if(c=='<')
			a[i].op=-1;
		else
			a[i].op=1;
	}
	for(int i=1;i<=n;i++)
		cin>>a[i].x;
	int now=1;
	while(book[now]!=1){
//		cout<<now<<endl;
		int tmp=now+a[now].op*a[now].x;
//		cout<<now<<endl;
		if(tmp>=1&&tmp<=n){
			book[now]=1;
			now=tmp;
		}
		else{
			cout<<"FINITE"<<endl;
			return 0;
		}
	}
	cout<<"INFINITE"<<endl;
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/155969074)

---

## 作者：Dongliang1 (赞：0)

## 题意
有一只蚱蜢和一个有着 $n$ 个格子的条子，蚱蜢刚开始在第 $1$ 个格子上。当蚱蜢跳出边界时就会停止。如果蚱蜢会永远跳下去，输出 `INFINITE`，否则输出 `FINITE`。
## 思路
我们可以思考一下，当什么时候蚂蚱会永远跳下去呢？可以发现，当蚂蚱跳到同一个地方两次时，蚂蚱会沿着之前的路线一直跳下去，此时输出 `INFINITE`，否则当蚂蚱跳出边界之外时就会停下来，此时输出 `FINITE`。


```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

struct Call
{
    int op,x;
    bool jump;
}c[N];

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        char k;
        cin>>k;
        if(k=='<')
        {
            c[i].op=-1;
        }
        else
        {
            c[i].op=1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        cin>>c[i].x;
    }
    int cur=1;
    while(c[cur].jump!=true)
    {
        int now=cur+c[cur].op*c[cur].x;
        if(now>=1&&now<=n)
        {
            c[cur].jump=true;
            cur=now;
        }
        else
        {
            cout<<"FINITE"<<"\n";
            return 0;
        }
    }
    cout<<"INFINITE"<<"\n";
    return 0;
}
```

---

## 作者：ZBH_123 (赞：0)

### 思路分析
这道题没什么好说的，直接模拟就行了。我们可以把格子上标有 $<$ 的格子标记为 $-1$，将标有 $>$ 的格子标记为 $1$。每次跳动时，将当前的格子数加上格子上的标记乘以格子上标的距离就行了。当蚂蚱走到曾经走过的格子时，蚂蚱的跳动必定会无限循环下去。而当蚂蚱跳出条子时，这个跳动就会结束。

### 代码实现
这里给出两种实现方式，一种是 BFS 式，一种是 DFS 式。

BFS 式示范代码：
```cpp
#include<iostream>
using namespace std;
const int maxn=1e5+5;
int n,a[maxn],b[maxn],cnt,x;
char ch;
bool vis[maxn];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>ch;
		if(ch=='<'){
			b[i]=-1;
		}
		else{
			b[i]=1;
		}
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	x=1;
	while(1){
		if(x>n||x<1){//越界就代表跳动结束
			cout<<"FINITE";
			return 0;
		}
		if(vis[x]){//跳到曾经跳到过的格子时，就代表跳动会陷入无限循环。
			cout<<"INFINITE";
			return 0;
		}
		vis[x]=true;//标记已走过
		x+=a[x]*b[x];//进行跳动
	}
	return 0;
}
```
运行效果：

![](https://cdn.luogu.com.cn/upload/image_hosting/btvb2ru3.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

![](https://cdn.luogu.com.cn/upload/image_hosting/zoqoc8bk.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

DFS 式示范代码：
```cpp
#include<iostream>
using namespace std;
const int maxn=1e5+5;
int n,a[maxn],b[maxn],cnt,x;
char ch;
bool vis[maxn];
bool dfs(int x){
	if(x<1||x>n){
		return true;
	}
	if(vis[x]){
		return false;
	}
	vis[x]=true;
	return dfs(x+a[x]*b[x]);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>ch;
		if(ch=='<'){
			b[i]=-1;
		}
		else{
			b[i]=1;
		}
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	if(dfs(1)){
		cout<<"FINITE";
	}
	else{
		cout<<"INFINITE";
	}
	return 0;
}
```
运行效果：

![](https://cdn.luogu.com.cn/upload/image_hosting/f2cbo96c.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

![](https://cdn.luogu.com.cn/upload/image_hosting/8xn6zbpj.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

上述两个代码的时间复杂度均为 $O(n)$。

---

## 作者：SY_nzwmb83 (赞：0)

### 题意

蚂蚱在条子上从第 $1$ 个格子开始跳，每个格子写有下一次跳的方向与长度，求这个蚂蚱会不会跳完（即越界）。

### 分析

首先明确，当这个蚂蚱跳到某个格子达到 $2$ 次，就证明不会跳完，因为它仍然会按以前的路跳下去。所以这种情况直接输出 `INFINITE`。

另外，如果蚂蚱跳出了条子，那么就一定可以跳完，直接输出 `FINITE`。

两种情况分析完毕，下面考虑实现。注意到 $n$ 比较小，可以直接暴力递归，即对每个格子 $x$，判断按这个格子的指令行走会不会越界，也要判断是否走过这个格子，如果出现这两种情况就输出答案。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,opt[100005],num[100005],fnd[100005];//opt存方向，num存长度，fnd存是否来过
void solve(int x)
{
	if(fnd[x]>1)//注意不是判断等于1，因为来这个格子前就已经自加了
	{
		cout<<"INFINITE";
		exit(0);
	}
	int nx=x+opt[x]*num[x];//下一个位置
	if(nx>=1&&nx<=n)
	{
		fnd[nx]++;
		solve(nx);
	}//没越界
	else
	{
		cout<<"FINITE";
		exit(0);
	}//越界了
}
signed main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		char ch;
		cin>>ch;
		if(ch=='<')
		{
			opt[i]=-1;
		}//朝负方向运动
		else
		{
			opt[i]=1;
		}//朝正方向运动
	}
	for(int i=1;i<=n;i++)
	{
		cin>>num[i];
	}
	solve(1);//从1开始
	return 0;
}
```

---

## 作者：IkunTeddy (赞：0)

# 题目分析
一看数据范围这么小 $1\le N\le 100000$ 直接模拟啊，有什么好说的。那在什么情况下会无限循环呢？

是不是只要有一个点被走过了两次，那么就肯定会死循环，接下来又会走回来，只要建一个 $vis$ 数组标记一下就完结撒花了！

### 警示后人
我不知道这个样例在搞什么，非要用这个奇奇怪怪的输入，直接输入 >，< 不好吗？硬生生弄了我 20 分钟。无语了。

# Code
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=100000+10;
int way[maxn];
int a[maxn];
int vis[maxn];
int now=1;
int main(){
	int n;
	cin>>n;
	int flag=0;
	getchar();
	for(int i=1;i<=n;i++){
		char b;
		scanf("%c",&b);
		if(b=='>'){
			way[i]=1;
		}if(b=='<') way[i]=0;
	}
	for(int i=1;i<=n;i++) cin>>a[i];
	while(1){
		if(now<1||now>n) break;
		if(vis[now]==2){
			flag=1;
			break;
		}
		
		vis[now]++;
		way[now]==1?now+=a[now]:now-=a[now];
	}
	if(flag){
		cout<<"INFINITE";
	}else{
		cout<<"FINITE";
	}

	return 0;
}


```


---

## 作者：Chang_Pei (赞：0)

这道题我用的是 while(1) （死循环） + 模拟 解的。

#### 题意：

事实上题意没什么好讲的，但是我在写题时发现了一点。

那个，
```
&lt; 和 &gt;
```
很迷惑人。

我大胆的尝试了一下，发现直接按照 < 和 > 输入并处理可以 AC 。


#### 下面简单的说一下思路（有思路不会写的看代码部分）：

>这个蚱蜢它只会左跳或右跳，所以这就可以模拟 AC 。

>因为只要求蚱蜢能不能跳出这个条子（即求否会一直跳下去），使用 while 循环就可以了。

$ Q $ : 如果会一直跳下去，那死循环岂不会超时？

$ A $ : 可以使用 bool 数组，将走过的路标记一下。如果再次走到了这个点，那么就 **必定** 会一直跳下去（大家可以思考一下），即可输出答案并退出循环。

### 代码与实践：

如果已经有了思路，就可以打代码了。

赠 核心代码框架 ，如下：

```cpp
while(1) {
	if(     ) {
		
	} else if(     ) {
		
	}
	if(    ) {
		cout<<"FINITE";
		break;
	}
	if(    ) {
		cout<<"INFINITE";
		break;
	}
	 
}
```

#### 核心代码：

我们来一个一个的看：
```cpp
int t=1;
```
这是在定义一个记录蚱蜢跳到哪儿的变量。

```cpp
if(a[t]=='<' ){
	t-=a2[t];
}
```

这就是模拟如果是往左跳的情况，注意往左是减。

```cpp
else if(a[t]=='>' ) {
	t+=a2[t];
```

原理同上

```cpp
if(t>n || t<1) {
	cout<<"FINITE";
	break;
}
```
这就是在判断有没有跳出（即判断 t 有没有小于 1 或 大于 n ），如果有就输出并退出循环。


```cpp
if(flag[t]==1) {
	cout<<"INFINITE";
	break;
}
```
判断这个蚱蜢有没有跳在同一个格子上过，如果有就输出并退出循环。

```cpp
flag[t]=1;
```
千万不要丢掉这个！

这是用来标记这个点已走过。

#### 完整代码：
见下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char a[100005];
int a2[100005];
bool flag[100005];
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>a[i];
	}
	for(int i=1; i<=n; i++) {
		cin>>a2[i];
	}
	int t=1;
	while(1) {
		if(a[t]=='<' ) {
			t-=a2[t];
		} else if(a[t]=='>' ) {
			t+=a2[t];
		}
		if(t>n || t<1) {
			cout<<"FINITE";
			break;
		}
		if(flag[t]==1) {
			cout<<"INFINITE";
			break;
		}
		flag[t]=1;
	}

	return 0;
}
```
#### 完结撒花！



---

## 作者：Misaka_Mik0t0 (赞：0)

此题虽简单，可是必须要有必要的解释，而其它几篇题解都没有。这里就来写一篇个人认为好一点的。

### 分析：
先令**向右跳**的跳动格数为**题目中所述跳动格数**，**向左跳**的跳动格数为**题目中所述跳动格数的相反数**。
##### **首先来分析一下怎么样会死循环**：
当蚱蜢从 $a$ 点跳了 $b$ 次时，再次回到 $a$ 点，会出现死循环。因为它再跳 $b$ 次任然会回到 $a$ 点，再跳 $b$ 次栽回到 $a$ 点。以次类推，它会永远执行这个循环，**跳动永不停止**。

更近一步：若蚱蜢已经跳了若干次，其中有两次的出发点一样，则会出现死循环。
##### **下面来证明只会有死循环能让蚱蜢永不停止**：
当蚱蜢跳了 $n$ 次（$n$ 为题目所述），一共会产生 $n+1$ 个的出发点（第 $n+1$ 次的也产生了）。若跳出了边界，则不是“永不停止”，不用讨论。根据抽屉原理（不知道的往下看），必然会有两个出发点相同，则是死循环。

因此，**死循环与跳动永不停止是等价的**。
### 代码实现：
方法与证明刚刚已经说过了。**只用模拟 $n$ 次跳动，看有没有跳出边界**。

##### 主体代码：
```cpp
int g=1;
for(int i=1;i<=n;++i){
	g+=p[g];
	if(g<=0||g>n){
		printf("FINITE");
		return 0;//结束程序
	}
}
printf("INFINITE");
```
##### 读入部分代码：
```cpp
int read(){
	char ch=getchar();int res=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+ch-'0';
		ch=getchar(); 
	}
	return res;
}//速度函数，返回数值为读入的数，速度很快。也可以换成scanf或cin

//p数组存储每个格子的跳动格数
n=read();scanf("\n");
for(int i=1;i<=n;++i){
	char ch=getchar();
	if(ch=='>')p[i]=1;
	else p[i]=-1;
}
for(int i=1;i<=n;++i)p[i]*=read();
```

**附：抽屉原理及其证明：（重要程度：4星）**

1. 有 $k$ 个人与 $k+1$ 块糖，每块糖分给一个人，则必然有人分到了 $2$ 块糖及以上。

证明：

若每个人都分不到 $2$ 块糖，则每人最多有 $1$ 块糖，一共最多有 $k$ 块糖。则 $k+1$ 块糖必然会让某人分到了 $2$ 块糖及以上。

2. 有 $k$ 个人与 $k \times m+1$ 块糖，每块糖分给一个人，则必然有人分到了 $m+1$ 块糖及以上。

证明留给读者去想，方法和上面一样。

---

## 作者：tribool4_in (赞：0)

一道简单模拟，如果跳出界则会停止（废话），如果跳到已经跳到过的地方则表示将会无限循环（~~正确性显然~~）。

最终不是跳出界就是无限循环。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, a[N];
char s[N];
int pos = 1;
bool vis[N];
int main() {
	scanf("%d%s", &n, s + 1);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), a[i] = (s[i] == '<') ? -a[i] : a[i];
	while (1) {
		if (pos < 1 || pos > n) {
			printf("FINITE\n");
			break;
		}
		else if (vis[pos]) {
			printf("INFINITE\n");
			break;
		}
		vis[pos] = 1;
		pos += a[pos];
	}
	return 0;
}

```


---

## 作者：FuriousC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF641A)

# 思路

此题根据题意模拟即可

代码中有一个特殊的点：当蚱蜢再次回到它走过的点时，必定是循环的。

$eg:$样例二$1\Rightarrow 3\Rightarrow 2\Rightarrow 3\Rightarrow  2\Rightarrow 3......$此时蚱蜢就是循环的，以为它又回到了它走过的点上，循环体：$2\Rightarrow 3$

# 废话不多说，上代码：

```cpp
#include<bits/stdc++.h>//懒人专属头文件 
using namespace std;
int n,now=1,w[100005],dir[100005];
//now表示当前蚱蜢所在的格子 
//w是每个格子需所移动的步数
//dir是每个格子所需移动的方向 
bool vis[100005];
//判断这个格子是否走过（具体作用见上文）  
string a;
//输入的方向字符串 
int main(){
    cin>>n>>a;//输入 
    for(int i=0;i<n;i++){
        if(a[i]=='<'){//如果是向左走 
            dir[i+1]='l';//将此点的方向改为l（左） 
        }else{//如果是向右走 
        dir[i+1]='r';//将此点的方向改为r（右） 
        }
    }
    for(int i=1;i<=n;i++){
        cin>>w[i];//输入每个点要走的距离 
    }
    while(true){
        if(now<1||now>n){//判断是否越界 
            cout<<"FINITE"<<endl;//输出有限的 
            return 0;//结束 
        }else if(vis[now]==true){//判断是否走过 
            cout<<"INFINITE"<<endl;//输出无限的 
            return 0;//结束 
        }
        vis[now]=true;//将此点标记为走过的 
        if(dir[now]=='l'){//如果此点是向左走的 
            now-=w[now];//减去此点的距离 
        }else{//如果此点是向右走的 
            now+=w[now];//加上词典的距离 
        }//在这个操作方面我还是觉得楼上的dalao的处理方法更好一些，建议去学习一下/kk 
    }
    return 0;//好习惯 
}
```

代码看完了，你学废了吗？

---

## 作者：XMK_萌新 (赞：0)

一道很简单的题                  
如果蚱蜢回到了以前跳过的一个格子$A$，那么必定有路线$A$ - $B$ - $C$ - $...$ - $A$，那么它就会永远在这条路上循环，即`INFINITE`              
而如果它跳出了边界那肯定就是`FINITE`              
时间是$O(N)$的，因为最多在把每个格子都跳一遍后，要么跳回跳过的格子，要么跳出边界           
代码如下

```cpp
#include <iostream>
#include <cstring>
using namespace std;
int n,idx=1,d[100003],x[100003];	//idx当前位置，初始为1
bool vis[100003];	//有没有跳过
string m;
int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++) x[i+1]=(m[i]=='<'?-1:1);	//往左跳记为-1，往右跳记为1
    for(int i=1;i<=n;i++) cin>>d[i];
    while(1)
    {
        if(idx<1||idx>n)	//跳出边界
        {
            cout<<"FINITE"; 
            break;
        }          
        if(vis[idx])	//以前跳过
        {
            cout<<"INFINITE";
            break;
        }
        vis[idx]=true;	//标记
        idx+=x[idx]*d[idx];	//移动，往左跳会加上一个负数（即减去d[idx]），往右跳会加上d[idx]。
    }
    return 0;
} 
```


---


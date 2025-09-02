# Find The Bone

## 题目描述

Zane the wizard is going to perform a magic show shuffling the cups.

There are $ n $ cups, numbered from $ 1 $ to $ n $ , placed along the $ x $ -axis on a table that has $ m $ holes on it. More precisely, cup $ i $ is on the table at the position $ x=i $ .

The problematic bone is initially at the position $ x=1 $ . Zane will confuse the audience by swapping the cups $ k $ times, the $ i $ -th time of which involves the cups at the positions $ x=u_{i} $ and $ x=v_{i} $ . If the bone happens to be at the position where there is a hole at any time, it will fall into the hole onto the ground and will not be affected by future swapping operations.

Do not forget that Zane is a wizard. When he swaps the cups, he does not move them ordinarily. Instead, he teleports the cups (along with the bone, if it is inside) to the intended positions. Therefore, for example, when he swaps the cup at $ x=4 $ and the one at $ x=6 $ , they will not be at the position $ x=5 $ at any moment during the operation.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF796B/190b731b36b585b1537188535b06ba518cad612c.png)Zane’s puppy, Inzane, is in trouble. Zane is away on his vacation, and Inzane cannot find his beloved bone, as it would be too exhausting to try opening all the cups. Inzane knows that the Codeforces community has successfully helped Zane, so he wants to see if it could help him solve his problem too. Help Inzane determine the final position of the bone.

## 说明/提示

In the first sample, after the operations, the bone becomes at $ x=2 $ , $ x=5 $ , $ x=7 $ , and $ x=1 $ , respectively.

In the second sample, after the first operation, the bone becomes at $ x=2 $ , and falls into the hole onto the ground.

## 样例 #1

### 输入

```
7 3 4
3 4 6
1 2
2 5
5 7
7 1
```

### 输出

```
1```

## 样例 #2

### 输入

```
5 1 2
2
1 2
2 4
```

### 输出

```
2```

# 题解

## 作者：Super_dark (赞：3)

## 思路
就是一个模拟

最开始骨头的位置在 $1$ 的位置上，在交换 $x$ 和 $y$ 时，如果骨头的位置与其中一个值重合，就把它的位置赋成另一个值。

因为骨头进洞后就不能交换，动不了了，所以直接输出。

为判断一个地方有无坑，我们在输入第二行的时候我们要用一个桶来存储。交换时如果这个位置对应的桶值大于零，则此处为坑。直接输出即可。

## 代码实现
```c
#include <bits/stdc++.h>
using namespace std;
int kk[1000010],tong[1000100],now=1;
int main(){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		cin>>kk[i];
		tong[kk[i]]++;
	}
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		if(tong[now]) {
			cout<<now<<endl;
			return 0;
		}
		if(now==x){
			now=y;
		}
		else {
            if(now==y) {
                now=x;
            }
        }
	}
	cout<<now;
	return 0;
}
}
```


---

## 作者：Cutler (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF796B)

一道小模拟。

提前给有坑的地方打上标记，一旦骨头到达有坑的地方就跳出，之后的交换都没有意义了。

然后每次如果交换的两个位置有骨头，就把骨头的位置改为另外一个位置。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;
const int Maxn = 1e6+10;

int f[Maxn], cur, n, m, k, x, y;

int main(){
	
	scanf("%d%d%d", & n, & m, & k);
	while(m --) scanf("%d",& x),f[x] = 1;
	
	cur = 1;
	while(k --){
		if(f[cur]) break;
		scanf("%d%d", & x,& y);
		if(cur == x) cur = y;
		else if(cur == y) cur = x;
	}
	
	printf("%d\n", cur);
	return 0;
}
```

优雅结束。

---

## 作者：Eason_cyx (赞：0)

一道比较简单的模拟题。

因为坑的值域是 $10^{6}$，所以我们直接使用一个桶来存每个坑的位置，用一个 $pos$ 变量存骨头的位置。

每一次交换，如果跟骨头有关，那么就换；如果骨头进洞，此时它不可能再移动了，就直接输出这个位置就行了。如果全部操作结束骨头还没有进洞，那就直接输出最终位置。

这题的思路大致是这样的，注意以下的小细节：

- 在判断时，要用 `if` 和 `else`，不能用两个 `if`，不然会死循环。

- 输出最终位置后直接 `return 0`，不执行下面的操作。

好了，下面是代码：
```cpp
#include <iostream>
using namespace std;
bool flag[1000005];
int main() {
    int n,m,k; cin >> n >> m >> k;
    for(int i = 1;i <= m;i++) {
        int x; cin >> x;
        flag[x] = true;
    }
    int pos = 1;
    if(flag[pos]) {
        cout << pos << endl;
        return 0;
    }
    for(int i = 1;i <= k;i++) {
        int u,v; cin >> u >> v;
        if(u == pos) {
            pos = v;
            if(flag[pos]) {
                cout << pos << endl;
                return 0;
            }
        }
        else if(v == pos) {
            pos = u;
            if(flag[pos]) {
                cout << pos << endl;
                return 0;
            }
        }
    }
    cout << pos << endl;
    return 0;
}
```

---

## 作者：cxy000 (赞：0)

这道题看起来很复杂，但实际上就是一道模拟题。

首先在输入第二行的时候我们要用一个桶来存储，由于数据允许，只开 $10^6$ 即可。

然后在输入交换的时候，若此时记录骨头位置的数对应的桶的排位大于零（即此位置为坑），那么输出这个数字即可。

最后交换记得用 
```cpp
if ...
else if...
```
的形式。

就这些，没了。

上代码：

## Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int ke[1000010];
int tong[1000100];
int main(){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		cin>>ke[i];
		tong[ke[i]]++;
	}
	int now=1;
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		if(tong[now]) {
			cout<<now<<endl;
			return 0;
		}
		if(now==x){
			now=y;
		}
		else if(now==y) now=x;
	}
	cout<<now;
	return 0;
}
```


---

## 作者：Supor__Shoep (赞：0)

这道题是一道小小的模拟。

首先骨头的位置原先是在 $1$ 的位置上，在所有交换 $x$ 和 $y$ 的操作当中，如果骨头的位置与其中一个值重合，我们就把它的位置赋成另一个值。

根据特殊规则，如果骨头掉进坑里面就不会再进行交换。我们定义一个数组，数组当中 $1$ 表示坑，而 $0$ 表示没有坑。每次准备进行操作是，我们判断一下此时骨头的位置，如果骨头的位置在数组中刚好是 $1$，就省略下面所有的操作。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int vis[2000005];//存放是否有坑的数组
int zb;//骨头的当前坐标
int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)
    {
        int x;
        cin>>x;
        vis[x]=1;//有坑的位置赋值
    }
    zb=1;//骨头初始坐标为1
    for(int i=1;i<=k;i++)
    {
        if(vis[zb])//省略操作
        {
            continue;
        }
        int x,y;
        cin>>x>>y;
        if(zb==x)//当其中两个坐标当中有骨头才进行操作
        {
            zb=y;
        }
        else if(zb==y)
        {
            zb=x;
        }
    }
    cout<<zb;
    return 0;
}
```

---

## 作者：happybob (赞：0)

话说为啥你们都用快读快写，我用 `cout` 和 `cin` 也过了？~~（其实我是懒）~~。

很简单的模拟，每次交换时判断当前位置是否在交换的位置 $x,y$ 中，在的话就交换，不在啥都不用做，中途如果进坑就直接退出。

代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e6 + 5;
bool mp[N];
int n, m, k, x, y, place = 1;

int main()
{
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++)
	{
		int l;
		cin >> l;
		mp[l] = true;
	}
	while (k-- && !mp[place])
	{
		cin >> x >> y;
		if (place == x)
		{
			place = y;
		}
		else if (place == y)
		{
			place = x;
		}
	}
	cout << place << endl;
	return 0;
}
```


---

## 作者：Daidly (赞：0)

模拟+判断。

- 把每个坑的坐标用一个桶储存。

- 判断初始点 $1$ 是否有坑。

- 模拟，如果当前坐标为 $x$，那就移到 $y$，反之移到 $x$。

- 移动后判断是否有坑，如有坑，停止，输出。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
inline void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}
const int MAXN=1e6+5;
int n,m,k,a,f[MAXN],x,y,ans=1;
int main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;++i){
		a=read();
		f[a]++;
	}
	if(f[1]){
		puts("1");
		return 0;
	}
	while(k--){
		x=read(),y=read();
		if(ans==x){
			ans=y;
			if(f[y])break;
		}else if(ans==y){
			ans=x;
			if(f[x])break;
		}
	}
	print(ans);
	return 0;
}
```
七夕节祭！

---

## 作者：Mr_WA的大号 (赞：0)

这题比“米奇妙妙屋还妙”——Mr_WA的大号

题号：CF796B

难度：★★

算法：模拟

这一次要给大家普及的知识叫做模拟。

模拟，一种“机器人”算法，即生硬地模拟题目给出的方法，不加任何优化（~~不包括火车头优化~~），虽然容易TLE但是很常用，可以用来比赛坑分。

这一题讲的就是模拟算法。根据题目的意思来控制代码运行，不断地进行交换操作，如果中途调到了坑里，就直接输出。

事实真的是这样吗……

当然会有一些注意事项，比如要用快读，否则会TLE哦。

上代码：
```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
using namespace std;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}//快读
int t,m,n,x,y,w;
bool a[1000010];
int main()
{
	t=read();
	m=read();
	n=read();
	for(int i=1; i<=m; i++)
	{
		x=read();
		a[x]=true;
	}
	if(a[1]==true)
	{
		cout<<1;
		return 0;
	}//如果在1号点就有坑，特判输出
	w=1;
	for(int i=1; i<=n; i++)
	{
		x=read();
		y=read();
		if(w==x)w=y;
		else if(w==y)w=x;//交换位置
		if(a[w]==true)
		{
			cout<<w;//如果有坑，就直接输出
			return 0;
		}
	}
	cout<<w;//输出答案
	return 0;
}

```
祝大家能AC！

---

## 作者：yxy666 (赞：0)

这道题是纯模拟，我们只用每次交换位置，并且判断当前位置是否是坑，是坑的话就结束循环，输出当前位置。因为一旦进了坑就无法移动了，后面的操作就没有意义了。注意，如果初始位置 $1$ 也是坑，那就直接输出初始位置 $1$ 。

 $code$ :
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,sx; 
bool vis[1000005];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}//快读 
int main(){
	n=read();m=read();k=read();sx=1;
	for(int i=1;i<=m;i++)vis[read()]=1;//标记那几个点是坑 
	if(vis[1]==1){printf("1");return 0;}//特判 
	for(int i=1;i<=k;i++){
		int x=read(),y=read();
		if(sx==x)sx=y;//交换位置
		else if(sx==y)sx=x;//交换位置 
		if(vis[sx]==1){printf("%d\n",sx);return 0;}//如果踩到坑了，输出，结束 
	}
	printf("%d\n",sx);$
	return 0;
}
```


---

## 作者：xiaozeyu (赞：0)

模拟，就硬生生的模拟

看到题目如此少的介绍，写起来是会有很多小问号

![小问号](https://cdn.luogu.com.cn/upload/image_hosting/ajevxku6.png)

![题目](https://cdn.luogu.com.cn/upload/image_hosting/l6sf1pwc.png)

帮你们少走弯路

1. 这就是个模拟，按照要求一步步做下去

2. k个操作是按顺序来的，有一些是无意义操作

3. 输入的x,y不一定是从小到大的，需要进行交换

4. 给的m个坑是排好序的，不要再次排序浪费时间

5. 坑不用交换

6. 数据小，$ 2\le n\le 10^6 ,$ $1\le m\le n,$ $ 1\le k \le 3\cdot 10^5   $ 不需要写二分了
------------
其实只要交换有效的x,y就行了

正解:

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read() {
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x; return x;
}
const int maxn=1000050;
int n,m,k,now=1;
bool d[maxn];
int main()
{
	n=read(); m=read(); k=read();
	For(i,1,m)
	{
		int a=read();
		d[a]=true;
	}
	while(k--)
	{
		int x,y;
		if(d[now]) break;
		x=read(); y=read();
		if(x==now) now=y;
		else if(y==now) now=x;
	}
	cout<<now<<endl;
	return 0;
}

```
假如数字的总量大一点

那就差不多这么写(二分)

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,x,y,lsy=1,b[1000010],mid;
bool ef(int l,int r,int y)
{
	if(l>r) return true;
	mid=(l+r+1)>>1;
	if(b[mid]==y) return false; 
	if(b[mid]>y&&b[mid-1]<y) return true;
	if(b[mid]<y&&b[mid+1]>y) return true;
	if(b[mid]>y) return ef(l,mid-1,y);
	if(b[mid]<y) return ef(mid+1,r,y);
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&b[i]);
		if(b[i]==1)
		{
			printf("1");
			return 0;	
		}
	}
	sort(b+1,b+m+1);
	for(int i=1;i<=k;i++)
	{
		scanf("%d%d",&x,&y);
		if(x^lsy) 
			swap(x,y);
		if(x^lsy)
			continue;
		if(!ef(1,m,y))
		{
			printf("%d",y);
			return 0;
		}
		lsy=y;
	}
	printf("%d",lsy);
}

```

---

## 作者：WCG2025 (赞：0)

~~又是一道大水题~~


------------

这道题的大意是这样的：你有N个盒子，最开始时第一个盒子里面装着骨头，然后给你m个数，代表这m个位子上有漏洞，骨头掉到漏洞里面就拿不出来了，问你最后骨头的位置

其实看这道题的数据范围，没必要想什么高级算法，模拟就好了
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int vis[1000000];//用于记录这个点是否为漏洞
int n,m,k;
int main()
{
		n=read();
		m=read();
		k=read();
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=m;i++)//读入漏洞
        {
            int x;
            x=read();
            vis[x]=1;//进行标记
        }
        int ans=1;//赋初值
        while(k--)
        {
            int x,y;
            x=read();//两个盒子进行交换，如果两个盒子里面没有骨头，就直接跳过
            y=read();
            if(x==ans)
            {
                if(vis[x]!=1)ans=y;//主要在于判断点是否在洞上
            }
            else if(y==ans)
            {
                if(vis[y]!=1)ans=x;
            }
        }
        printf("%d\n",ans);//输出就好了
        return 0；
}
```
祝大家新年快乐！！！！

---


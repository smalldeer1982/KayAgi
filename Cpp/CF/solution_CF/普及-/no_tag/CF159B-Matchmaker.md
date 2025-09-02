# Matchmaker

## 题目描述

ygg 有 $n$ 只马克笔和 $m$ 个笔盖。我们可以使用二元组 $(a, b)$ 来描述一只笔或一个笔盖，其中 $a$ 表示颜色，$b$ 表示大小。任意一对笔和笔盖只有在**大小相同**的时候才可以配对，如果这一对笔和笔盖**大小相同且颜色相同**，我们就称这一对笔和笔盖为**优秀的配对**。  
现在 ygg 希望知道他最多可以构成多少**优秀的配对**，以及最多共有多少对配对。

## 样例 #1

### 输入

```
3 4
1 2
3 4
2 4
5 4
2 4
1 1
1 2
```

### 输出

```
3 2
```

## 样例 #2

### 输入

```
2 2
1 2
2 1
3 4
5 1
```

### 输出

```
1 0
```

# 题解

## 作者：Cute_Furina (赞：5)

**思路：**

这题显然可以用桶来模拟，用 $c$ 来存储第 $i$ 种大小的笔盖的个数，用 $d$ 来存储颜色为 $i$ 的第 $j$ 种大小的笔盖。

**code:**


```cpp
#include <bits/stdc++.h>
using namespace std;
int c[1010], d[1010][1010], n, m, a, b, ans1, ans2;
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> a >> b;
		c[b]++;
		d[a][b]++;
	}
	for(int i = 1; i <= m; i++) {
		cin >> a >> b;
		if(c[b] >= 1) ans1 ++;
		c[b] --;
		if(d[a][b] >= 1) {
			ans2 ++;
			
		}d[a][b] --;
	}
	cout << ans1 << " " << ans2;
	return 0;
}
```

---

## 作者：fanchenghao201061 (赞：3)

# 题意
---
   输入 $n$ 只笔和 $m$ 个笔盖的颜色与大小，进行配对，若任意一对笔和笔盖只有在大小相同的时候才可以配对，如果这一对笔和笔盖大小相同且颜色相同，我们就称这一对笔和笔盖为优秀的配对。
   
   输出最多共有多少优秀的配对，以及最多共有多少对配对。
# 代码思路
---
  先输入 $n$ 只笔颜色与大小，创建二维数组对第 $i$ 只笔颜色与大小进行标记，创建一维数组对第 $i$ 只笔大小进行标记。
  
  再输入 $m$ 只个笔盖的颜色和大小，在二维与一维数组中进行查找，若二维数组中有值，优秀的配对加一，若一维数组中有值，配对加一。

# 代码
---

```c++
#include <bits/stdc++.h>
//引入万能头
using namespace std;
int n,m,a,b;
//m,m,a,b意义题中有
int p[1010][1010],y[1010];
//创建二维数组p记录颜色，大小，一维数组p记录大小
int sum,ans,
//创建变量sum,ans分别记录配对，优秀的配对

int main(){
    cin>>n>>m;
    //输入n，m
    for(int i=1;i<=n;i++){
    //循环n次
        cin>>a>>b;
        p[a][b]++;
        //在p中对颜色，大小标记
        y[b]++;
        //在y中对大小标记
    }
    for(int i=1;i<=m;i++){
    //循环m次
        cin>>a>>b;
        if(y[b]){
        //如果在y中有与笔帽相同大小的笔
            y[b]--;
            //取消一个标记
            sum++;
            //配对加一
        }
        if(p[a][b]){
        //如果在y中有与笔帽相同大小，颜色的笔
            p[a][b]--;
            //取消一个标记
            ans++;
            //优秀的配对加一
        }
    }
    cout<<sum<<' '<<ans;
    //输出配对与优秀的配对
return 0;
}

```
[通过记录](https://www.luogu.com.cn/record/169004525)

---

## 作者：HFZ20111110 (赞：2)

# 题解：CF159B Matchmaker.


---


### [题目链接](https://www.luogu.com.cn/problem/CF159B)


---


## 题目分析

我的想法和 @[zhanghanrui123](/user/951050) 一样但是我觉得他讲的不够详细，我再讲的详细一点。

看到这道题，有颜色和大小两个数，我最先想到的是：可以先用结构体存储 $a_i$ 和 $b_i$ 。但是使用结构体的时间复杂度为 $O(nm)$ 评测机一般 $10^9$ 次执行 $1.5$ 秒。
虽然此题有 $3$ 秒的时限但是对于 $nm$ 还是远远不够的。那我们应该怎么办呢？

此时我注意到了 $a_i$ 和 $b_i$ 的数据范围。于是我就想到了：数据这么小是不是可以用两个二维的桶和两个一维的桶来做。

肯定有人会问了：桶不是用来排序的吗？其实并不是，桶的本质是统计，桶排序就是利用了桶的统计来统计所有的数字。并且利用下标输出：统计个数大于 $0$ 的数。

我们可以先定义两个一维数组 $a$ 和 $b$ ，用于统计每种大小的笔与笔盖分别有多少个。再定义两个二维数组 $ga$ 和 $gb$ ，二维数组第一个下标表示颜色，第二个下标表示大小。 如 $ga_{ij}=10$，就表示颜色为 $i$ 大小为 $j$ 的笔有 $10$ 支。


---


##  代码实现

### 定义部分

$match$ 用于统计普通的配对， $gmatch$ 用于统计优秀的的配对。
```cpp
int n,m,color,size,ga[1005][1005],gb[1005][1005],match,gmatch,a[1005],b[1005];
```

### 输入部分

循环里面边输入，边统计。
```cpp
cin>>n>>m;
for(int i=1;i<=n;++i){
  cin>>color>>size;
  ++ga[color][size];
  ++a[size];
}
for(int i=1;i<=m;++i){
  cin>>color>>size;
  ++gb[color][size];
  ++b[size];
}
```

### 计算答案

外层循环计算普通配对。内层循环计算优秀的配对。

**注意：无论是算优秀的配对还是普通的配对都只能增加其中最少的因为最多的配不了**
```cpp
for(int i=1;i<=1000;++i){
  match+=min(a[i],b[i]);
  for(int j=1;j<=1000;++j){
    gmatch+=min(ga[i][j],gb[i][j]);
  }
}
```
### 输出部分

分别输出普通的配对和优秀的配对。**注意中间有空格**
```cpp
cout<<match<<" "<<gmatch;
```

---

## 作者：Amm_awa (赞：2)

$$\huge{\texttt{CF159B 题解}}\tag*{\texttt{作者：wjl\_100930}}$$
## 链接

[$\color{red}\fbox{\text{洛谷链接}}$](https://www.luogu.com.cn/problem/CF159)

[$\color{red}\fbox{\text{ CF 链接 }}$](https://codeforces.com/problemset/problem/159/B)

## 分析

这里可以使用 `map` 保存笔的颜色和大小（需通过 $a \times 10^{5} + b$ 将笔的颜色和大小存储在一个地方），并通过一个桶 `box` 来保存笔的大小。在输入笔盖时，我们按照大小相等和完全相等进行比较，并删除对应的笔。其余讲解在代码中。

## 代码
```cpp
#include<bits/stdc++.h>
#define N 100005
#define D 10000
using namespace std;
int n,m,a,b,pa,ppa;
//n,m,a,b 定义见体面，pa表示配对个数，ppa表示优秀的配对数
int box[N];
//box[i] 表示大小为 i 的笔的个数
map<int,int> mp;
//mp[n] 表示 颜色*10^5+大小==n 的个数
//map 可以有效减少空间的消耗
int read()//快读
{
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
void readNum()
//输入部分
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		a=read(),b=read();
		box[b]++;
		//记录大小为 b 的笔的个数
		mp[a*1e5+b]++;
		//这里是将 a 和 b 拼在一起
	}
}
void solve()
//边输入边配对
{
	for(int i=1;i<=m;i++)
	{
		a=read(),b=read();
		if(box[b])
		//如果有同等大小的笔
			box[b]--,pa++;
			//那么将这个笔删去，配对数增加
		if(mp[a*1e5+b])
		//如果有颜色和大小都相等的笔
			mp[a*1e5+b]--,ppa++;
			//那么将这个笔删去，优秀的配对数增加
	}
	cout<<pa<<' '<<ppa;
}
signed main()
{
	readNum();
	solve();
	return 0;
}
```

$$ \color{red}end $$

---

## 作者：yggdyy_ (赞：2)

看这题没有题解，就来水一波。  
  
看到了这题，查一波CF上的评分，是 $1100$ ，很明显是一道水题。看了看题面，发现是一个小模拟，稍微想了想就给他写了出来。  
定义两个一维数组 `mkdia` 和 `cpdia` ，`mkdia[i]` 表示大小为 $i$ 的笔有多少只，`cpdia[i]` 表示大小为 $i$ 的笔盖有多少个。再定义两个二维数组 `mkcol` 和 `cpcol` ，`mkcol[i][j]` 表示大小为 $i$ 颜色为 $j$ 的笔有多少只，`cpcol[i][j]` 表示大小为 $i$ 颜色为 $j$ 的笔盖有多少个。  
先计算**优秀的配对的数量**，代码如下：  
```cpp
for(int i=1; i<=1000; i++) { //枚举大小
	for(int j=1; j<=1000; j++) { //枚举颜色
    	int tmp=min(mkcol[i][j], cpcol[i][j] ); 
        mkdia[i]-=tmp, cpdia[i]-=tmp; //配对之后减少数量
        c+=tmp, g+=tmp; //c表示普通配对数，g表示优秀配对数，普通配对包含优秀配对
	}
} 
```  
然后计算**普通的配对的数量**，代码如下：  
```cpp
for(int i=1; i<=1000; i++) { //枚举大小
	c+=min(mkdia[i], cpdia[i] ); 
}
```  
给完整代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, c, g;
int mkcol[1010][1010], cpcol[1010][1010];
int mkdia[1010], cpdia[1010]; 
int main() {
    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; i++) { //输入笔的数据
        int x, y; scanf("%d%d", &x, &y);
        mkcol[y][x]++, mkdia[y]++;
    }
    for(int i=1; i<=m; i++) { //输入笔盖的数据
        int a, b; scanf("%d%d", &a, &b);
        cpcol[b][a]++, cpdia[b]++;
    }
    
    //计算优秀的配对
    for(int i=1; i<=1000; i++) { 
        for(int j=1; j<=1000; j++) {
            int tmp=min(mkcol[i][j], cpcol[i][j] );
            mkdia[i]-=tmp, cpdia[i]-=tmp;
            c+=tmp, g+=tmp;
        }
    } 
    
    //计算普通的配对
    for(int i=1; i<=1000; i++) {
        c+=min(mkdia[i], cpdia[i] );
    }
    printf("%d %d\n", c, g);
    return 0;
}
```

---

## 作者：Guagua_ (赞：2)

### 这里提供一种 $O(n\log n)$ 的做法，似乎是这道题的最优解。


## 题意：
输入 $n$ 支笔的颜色与大小，和 $m$ 个笔盖的颜色与大小，规定当笔和笔盖的大小相等时，就是普通的配对；当笔和笔盖的大小和颜色都相等时，就是优秀的配对。
## 思路：
由于笔的颜色 $a_i$ 和大小 $b_i$ 都小于等于 $10^3$，所以对于一支笔或者笔盖，我们可以把它的下标 $id$ 设置为 $a_i \times 10^5 + b_i$，并使用 ```map``` 进行储存。
## 注意事项:
此题的笔和笔盖配对成功以后是不可以继续进行配对的，所以每一次配对完成就得把配对过的笔和笔盖都除去。

### code:
```cpp
#include<bits/stdc++.h>
#include<map>
#define int long long
using namespace std;
const int N=1e5;
map<int,int>pen;
int a[N];
int n,m;
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		int x,y;
		scanf("%lld%lld",&x,&y);
		a[y]++;
		pen[x+(y*N)]++;
	}
	int ans1=0,ans2=0;
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%lld%lld",&x,&y);
		if(a[y]!=0){
			ans1++;
			a[y]--;
		}
		if(pen[x+(y*N)]!=0){
			ans2++;
			pen[x+(y*N)]--;
		}
	}
	printf("%lld %lld",ans1,ans2);
    return 0;
}

```
[耗时：$248ms$   空间： $7.89MB$](https://www.luogu.com.cn/record/122407413)

**后言：** 一道水题，难度应该在橙题左右，为什么会没人做呢？

---

## 作者：fengyuxuan (赞：1)

# 题目大意

有 $n$ 只笔和 $m$ 个笔盖。每只笔和每个笔盖，都有相应的颜色和大小。当一对笔和笔盖大小相同就是一对配对，当一对笔和笔盖大小和颜色都相同，就是一对优秀的配对。

求这些笔和笔盖中，最多能有几对优秀的配对，以及最多能有几对配对。 

# 题目解析

用一个一维数组 $vis1_j$ 标记大小为 $j$ 的笔的数量，用来判断配对的构成。

再用一个二维数组 $vis2_{i,j}$ 标记颜色为 $i$，大小为 $j$ 的笔的数量，用来判断优秀的配对的构成。

接下来对于每一个笔盖，设其颜色为 $a$ 大小为 $b$，分别查询 $vis1_b$ 和 $vis2_{a,b}$，判段是否可以构成配对或优秀的配对，最后累加数量即可。

同时应该删除当前可以配对或可以优秀的配对的笔，避免重复，即 $vis1_b-1$ 或 $vis2_{a,b}-1$。

# 最终代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,vis1[1005],vis2[1005][1005],p,pp;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a>>b,vis1[b]++,vis2[a][b]++;
	for(int i=1;i<=m;i++)
	{
		cin>>a>>b;
		if(vis1[b])
			vis1[b]--,p++;
		if(vis2[a][b])
			vis2[a][b]--,pp++;
	}
	cout<<p<<" "<<pp;
	return 0;
}
```

---

## 作者：leo120306 (赞：1)

看见没有 01Trie 的，赶紧来交一篇。

## 题意简述
笔和笔盖分别有两个属性 $x$ 和 $y$，$y$ 相同的笔和笔盖可以组成**配对**，$x$ 和 $y$ 都相同的笔和笔盖可以组成**优秀的配对**。问最多有几个配对，几个优秀的配对。

## 思路
配对很简单，开两个桶，把不同东西的 $y$ 分别统计一下，答案就是 $\sum\min(b_1(i),b_2(i))$。

优秀的配对虽然也可以开桶，但是如果数据范围再大一点就会爆空间。发现桶的大部分空间都被浪费，这个时候我们就可以用到 `map` 了。然而 `map` 常数略大，更好的选择是动态开点的字典树。对于每一个物品，我们把它的两个属性压进一个 `int`，然后扔进一个 01Trie，就能优美地统计优秀的配对了。

## 实现
动态开点字典树可以用数组模拟。
```
#include<cstdio>
#include<cstring>
using namespace std;

#define ll long long
#define ull unsigned long long
namespace io{
	const int size=(1<<20)+1;
	char buf[size],*p1=buf,*p2=buf;
	char buffer[size];
	int op1=-1;
	const int op2=size-1;
	
	inline char readchar() {
		if(p1!=p2) {
			return *p1++;
		}
		return p1==(p2=(p1=buf)+fread(buf,1,size-1,stdin))?EOF:*p1++;
	}
	
	inline void flush() {
		fwrite(buffer,1,op1+1,stdout),op1=-1;
	}
	
	inline void writechar(const char &x) {
		if(op1==op2) flush();
		buffer[++op1]=x;
	}
	#define gc readchar
	#define pc writechar
	#define el pc(10)
	#define sp pc(32)
	
	template<typename Tp>
	inline Tp read(){
		Tp x=0;
		bool w=0;
		char ch=gc();
		while(ch<'0'||ch>'9')ch=='-'&&(w=1),ch=gc();
		while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=gc();
		return x;
	}
	
	template<typename Tp>
	void write(Tp x){
		if(x<0)pc('-'),x=-x;
		if(x>9)write(x/10);
		pc((x%10)^48);
	}
};
using namespace io;

struct node{
	int l,r,v,v2;
}t[2000005];
int tcnt;

struct node2{
	int v,v2;
}b[1005];

#define newnode (++tcnt)
#define s(x,y) ((x)<<10)|(y)

void add(int k,int v){
	if(!v){
		t[k].v++;
		return;
	}
	if(v&1){ // 1->r
		if(t[k].r) add(t[k].r,v>>1);
		else t[k].r=newnode,add(t[k].r,v>>1);
	}else{ // 0->l
		if(t[k].l) add(t[k].l,v>>1);
		else t[k].l=newnode,add(t[k].l,v>>1);
	}
}

void add2(int k,int v){
	if(!v){
		t[k].v2++;
		return;
	}
	if(v&1){ // 1->r
		if(t[k].r) add2(t[k].r,v>>1);
		else t[k].r=newnode,add2(t[k].r,v>>1);
	}else{ // 0->l
		if(t[k].l) add2(t[k].l,v>>1);
		else t[k].l=newnode,add2(t[k].l,v>>1);
	}
}

template<typename Tp>
inline const Tp& min(const Tp& x,const Tp& y){
	return x<y?x:y;
}

int main(){
	int n=read<int>(),m=read<int>();
	newnode;
	for(int i=1;i<=n;i++){
		int x,y;
		x=read<int>(),y=read<int>();
		add(1,s(x,y));
		b[y].v++;
	}
	
	for(int i=1;i<=m;i++){
		int x,y;
		x=read<int>(),y=read<int>();
		add2(1,s(x,y));
		b[y].v2++;
	}
	
	int cnt=0;
	for(int i=1;i<=1000;i++){
		cnt+=min(b[i].v,b[i].v2);
	}
	write(cnt);sp;
	
	cnt=0;
	for(int i=1;i<=2000000;i++){
		cnt+=min(t[i].v,t[i].v2);
	}
	write(cnt);el;
	
	flush();
	return 0;
}
```

---

## 作者：KyleShen1213 (赞：0)

## 解题思路
思路很简单，循环输入笔的信息，用一个一维数组记录不同大小的笔的个数，再用一个二维数组记录不同颜色不同大小的笔个数。再循环输入笔盖的信息，若分别找到配对的笔，存储答案的两个变量就加一（用两个如果语句就行了）。

话不多说，直接上代码～～

## AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int size_[1005],size_colour[1005][1005],n,m;
int colour,size,ans_match,ans_super_match;
//变量名应该很清楚了，我就不用多说了吧  
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>colour>>size;
		size_[size]++,size_colour[colour][size]++;//记录 
	}
	for(int i=1;i<=m;i++)
	{
		cin>>colour>>size;
		if(size_[size]>=1)//如果配对就加一 
		{
			ans_match++;size_[size]--;//答案加1，笔个数减1 
		}
		if(size_colour[colour][size]>=1)//如果配对就加一 
		{
			ans_super_match++;size_colour[colour][size]--;//答案加1，笔个数减1 
		}
	}
	cout<<ans_match<<" "<<ans_super_match;
	return 0;
}
```

---

## 作者：a18981826590 (赞：0)

# [Matchmaker](https://www.luogu.com.cn/problem/CF159B)
## 解题思路
看到大家都是用二维数组做的，时间复杂度较高。

题目中说可以使用二元组 $(a,b)$ 来描述一只笔或一个笔盖，但由于 $1 \le a,b \le 1000$，我们可以用 $a \times 10^{4}+b$ 来描述一只笔或一个笔盖，使用 `map` 存储，用于寻找优秀的配对；同时把笔的大小存储起来，用于寻找配对。

我们可以在输入笔时就把参数存储起来，在输入笔盖时寻找优秀的配对（同时把这支笔删掉），并把不是优秀的配对的笔盖存储起来，最后寻找配对（为防止普通配对影响了优秀的配对），而总配对数即为优秀的配对数与剩余配对数之和。

## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int>a;
int b[100010],c,d,e[1010],l,m,n,x,y;
int main(){
	cin>>m>>n;
	while(m--){
		cin>>x>>y;
		a[x*10000+y]++;
		e[y]++;
	}
	while(n--){
		cin>>x>>y;
		if(a[x*10000+y]>0){
			c++;
			a[x*10000+y]--;
			e[y]--;
		}
		else b[l++]=y;
	}
	for(int i=0;i<l;i++){
		if(e[b[i]]>0){
			d++;
			e[b[i]]--;
		}
	}
	cout<<c+d<<' '<<c;
	return 0;
}
```

---

## 作者：lostxxx (赞：0)

## CF159B Matchmaker 题解

## 题目分析

我们开两个数组 $siz1$ 和 $siz2$ 分别存储笔和笔盖的大小相同的数量，再用两个二维数组存储笔和笔盖的颜色和大小相同的数量。然后对于普通匹配，我们枚举所有可能的大小，然后取 $siz1$ 和 $siz2$ 中大小相同的数量的最小值，对于优秀的匹配，同上利用二维数组枚举颜色和大小即可。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m;
ll a,b;
ll col1[1010],col2[1010];
ll all1[1010][1010],all2[1010][1010];
ll sum1,sum2;
int main(){
    cin>>n>>m;
    for (int i=1;i<=n;i++){
        cin>>a>>b;
        col1[b]++;
        all1[a][b]++;
    }
    for (int i=1;i<=m;i++){
        cin>>a>>b;
        col2[b]++;
        all2[a][b]++;
    }
    for (int i=1;i<=1000;i++){
        sum1+=min(col1[i],col2[i]);
        for (int j=1;j<=1000;j++){
            //cout<<min(min(ma1[j],ma3[j]),min(ma2[i],ma4[i]))<<" "<<i<<" "<<j<<endl;
            sum2+=min(all1[j][i],all2[j][i]);
        }
    }
    cout<<sum1<<" "<<sum2;
}
```

---

## 作者：LJMljm (赞：0)

## 题目大意
根据题目描述可以得出题目就是要找 $1$ 个能够和另 $1$ 个马克笔配对的笔盖，既要寻找大小配对，也要寻找大小颜色都配对的,那么就可以使用下标计数。

## 代码如下↓
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,x,y,a[1005],b[1005][1005],ans1,ans2;
int main(){
    cin>>n>>m;
    while(n--)
    	cin>>x>>y,a[y]++,b[x][y]++;
    while(m--)
    {
    	cin>>x>>y;
    	if(a[y])ans1++,a[y]--;
    	if(b[x][y])ans2++,b[x][y]--;
    }
    cout<<ans1<<' '<<ans2;
    return 0;
}
```

---

## 作者：IOI_official (赞：0)

此题暴力肯定过不了，会在第九个点 TLE。

## 暴力代码（#9 TLE）

代码就不写注释了，反正 AC 不了。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int a,b;
}qj[114514],qjj[114514];
bool f[114514],ff,fff[114514],ffff[114514],g[114514];
int n,m,c,cc,jj;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>qj[i].a>>qj[i].b;
	}
	for(int i=1;i<=m;i++){
		cin>>qjj[i].a>>qjj[i].b;
	}
	for(int i=1;i<=n;i++){
		ff=0;jj=0;
		for(int j=1;j<=m;j++){
			if(qj[i].b==qjj[j].b){
				if(!f[j]&&!ff){
					c++;
					f[j]=1;
					jj=j;
					ff=1;
				}
				if(qj[i].a==qjj[j].a&&!fff[j]){
					if(!g[i]){
						cc++;
						g[i]=1;
					}
					f[jj]=fff[jj]=0;
					f[j]=fff[j]=1;
					jj=j;
				}
			}
		}
	}
	cout<<c<<" "<<cc;
	return 0;
}
```
[提交记录。](https://www.luogu.com.cn/record/142597343)

## 正解
**先看普通配对。**

储存每个大小的笔的个数，$s_{i}$ 为大小为 $i$ 的笔的个数，后面再判断当前笔帽的大小是否有笔身可配对，有就将他们配对，然后将这支笔删掉。

**再看优秀的配对。**

将 map 的下标作为每个笔的哈希值，将大小和颜色作为参数进行计算，遇到相同哈希值的笔便 $map_{hash} + 1$ 此后如果有笔盖的哈希值与笔身的哈希值相等，就将他们配对，然后将这支笔删掉。

然后就没有然后了。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long N=1e5;
map<int,int> c;
int n,m,s[114514],a,b,a1,a2;//s为大小数组，a1为普通配对数，a2为优秀配对数 
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		s[b]++;
		c[a+b*N]++;//计算哈希值 
	}//储存 
	for(int i=1;i<=m;i++){
		cin>>a>>b;
		if(s[b]!=0){
			a1++;
			s[b]--;
		}//统计普通配对数 
		if(c[a+b*N]!=0){
			a2++;
			c[a+b*N]--;
		}//统计优秀配对数 
	}
	cout<<a1<<" "<<a2;
	return 0;
}
```

---

## 作者：crzcqh (赞：0)

## 思路

根据题意，既然优秀的配对是要颜色和大小都相等，不妨二元化一元，考虑哈希，$n\le 10^5$，那么可以轻松得到哈希值：$a_i+b_i\times 10^5$，这样可以保证哈希值不会重复，可以用 map 记录，到时候算出笔盖的哈希值并判断是否有就可以了，即优秀的配对。

普通的配对要记录每根笔的大小，如果大小相同，就是普通的配对。

时间复杂度：$O(n\log n)$

## CODE

```cpp
#include<bits/stdc++.h>
#define M 100007
using namespace std;
int n,m,s,c;
int Size[M];
map<int,int> Color;
int ans1,ans2;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>c>>s;
		Size[s]++;
		Color[c+(s*M)]++; // 哈希 
	}
	for(int i=1;i<=m;i++){
		cin>>c>>s;
		if(Size[s]) ans1++; // 普通的配对 
		if(Color[c+(s*M)]) ans2++,Color[c+(s*M)]--; // 优秀的配对，注意，要把这只笔删掉，防止重复 
	}
	cout<<ans1<<' '<<ans2;
	return 0;
}



```



---

## 作者：_int123_ (赞：0)

题目：

## Matchmaker

### 思路：

由于翻译已经很清晰了，直接讲思路。

1. 我们先定义一个数组 $a$，其中 $a_i$ 代表大小为 $i$ 的笔盖的数量。

2. 由于优秀的配对需要满足大小与颜色两个条件，利用哈希思想，定义一个 `map` 类型的 $b$，其中 $b_{i+j \times100000}$ 代表满足 $i$ 和 $j$ 条件的笔的数量。

3. 若判到可行的之后就不能再判了，所以 $a$ 与 $b$ 直接减一。

### AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
map <int,int> b;
int a[100005];
int n,m;
int ans=0,anss=0;
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m; 
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		a[y]++;
		b[x+(y*100000)]++;
	}
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		if(a[y]) ans++,a[y]--;
		if(b[x+(y*100000)]) anss++,b[x+(y*100000)]--;
	}
	cout<<ans<<" "<<anss;
    return 0;
}
```

完结撒花！！！

---

## 作者：qusia_MC (赞：0)

## 第一种做法
利用哈希函数，将每一个盖子和笔的数组都改成 $99999 \times a + b$，到时候直接找有没有对应的就可以了。

我们用图存起来，不然空间复杂度虽然不会爆但是不够简洁。

代码：
```
#include<bits/stdc++.h>
using namespace std;
const int N=99999;
int main()
{
	int n,m,abi=0,abg=0;
	cin>>n>>m;
	map<int,int>bi;//bi就是笔的颜色。
	map<int,int>bg;//顾名思义，bg就是笔的大小（big）。
	int a,b;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b;
		bg[b]++;//统计大小
		bi[a*N+b]++;//统计这根笔的哈希值。（a*99999+b)
	}
	for(int i=1;i<=m;i++){
		cin>>a>>b;
		if(bg[b])
		{
			abg++;bg[b]--;//大小匹配，是“不完美的匹配”
		}
		if(bi[a*N+b])
		{
			abi++;bi[a*N+b]--;//哈希值相同，是“完美匹配”
		}
	}
	cout<<abg<<" "<<abi;return 0;//输出
}
```

## 暴力枚举
由于数据范围不大直接暴力枚举。

时间复杂度 $O({a_i}^2)$。

```
#include<bits/stdc++.h>
using namespace std;
const int N=99999;
int bi[1011],bg[1011][1011];
int bi2[1011],bg2[1011][1011];
int n,m,abi=0,abg=0;
int main()
{

	cin>>n>>m;
	int a,b;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b;
        bg[b][a]++;
        bi[b]++;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>a>>b;
		bg2[b][a]++;
		bi2[b]++;
		
	}
	for(int i=1;i<=1000;i++)
	{
		for(int j=1;j<=1000;j++)
		{
			int cnt=min(bg[i][j],bg2[i][j]);
 //累加所有颜色，大小相同的“完美配对”。
			if(cnt>0)
			{
			    abi+=cnt;
			    abg+=cnt;
			    bi[i]-=cnt;
			    bi2[i]-=cnt;
//由于每一个笔帽不能“分身”，只能匹配一次。
			}
		}
	}
	for(int i=1;i<=1000;i++)
	{
		if(bi2[i]&&bi[i])abi+=min(bi2[i],bi[i]),bi2[i]-=min(bi2[i],bi[i]),bi[i]-=min(bi2[i],bi[i]);
        //累加所有大小为i的笔盖和笔。
	}
	cout<<abi<<" "<<abg;
	return 0;
}
```
完结撒花。

---

## 作者：WZWZWZWY (赞：0)

一道简单的橙题，但是没人做，主要是 $n\le 1e5$，一开始翻译还有点锅，幸好我提出来了……

+ 配对过的不能再与其他的配对。优秀配对数和总配对数的答案互不影响。
+ 输出应该是最多的总配对数和优秀配对数。

**思路**：分别记录某个大小的笔盖有多少个（用来求总配对数）、某个大小并且是某个颜色的笔盖有多少个（存优秀配对数）。时间复杂度 $O(n\operatorname{log}n)$。

然后就没有什么了。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m, cnt[1005]/*存特定大小的笔盖数量*/, x, y, ans1, ans2;
map <int, int> a; //map相当于一个桶存特定的大小和颜色的笔盖。

signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> x >> y;
		cnt[y] ++;
		a[x * 10000 + y] ++; //x,y 小于等于1e3，所以x或y乘1e4就可以把x和y连接起来。比如x=1000，y=2222，连接起来变成10002222。
	}
	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		if (cnt[y]) { //总配对数
			cnt[y] --;
			ans1 ++;
		}
		if (a[x * 10000 + y]) { //优秀配对数
			a[x * 10000 + y] --;
			ans2 ++;
		}
	}
	cout << ans1 << " " << ans2;
}
```

还有什么不懂的可以在评论区问我。

---


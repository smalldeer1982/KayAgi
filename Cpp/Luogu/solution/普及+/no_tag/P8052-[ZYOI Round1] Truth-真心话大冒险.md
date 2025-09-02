# [ZYOI Round1] Truth/真心话大冒险

## 题目背景

**注意：请勿恶意提交代码，浪费评测资源。**

一群人参加了聚会，在玩“真心话大冒险”。

## 题目描述

Charlie 现在盯上了一个人 Percy，Ta 打算找出 Percy 对于 $n$ 个异性的好感度的排名。  

具体地，Charlie 可以提出两种要求：  

1. 【真心话】给定 $3$ 个正整数 $x,y,z$，要求 Percy 回答其中他第二喜欢的异性的编号。要求：$1 \leq x,y,z \leq n$。

2. 【大冒险】给定 $2$ 个正整数 $x,y$，要求 Percy 拥抱其中他更喜欢的那个异性。要求：$1 \leq x,y \leq n$ 且必须保证异性 $x,y$ 之中必有一个是 Percy 最喜欢的。  

Charlie 希望通过至多 $2 \times 10^6$ 次询问达到他的目的。

**交互格式：**  

一开始读入一个正整数 $n$ 开始交互。

你可以输出 $3$ 种信息：  

1. `1 x y z`，表示“真心话”询问，并读入结果。
2. `2 x y`，表示“大冒险”询问，并读入结果。
3. `3 a1 a2 ... an`，表示你已经得出了答案，按顺序输出 Percy 最喜欢、第二喜欢、……的异性的编号。


## 说明/提示

**以上输入输出只是为了演示交互格式，可能并不符合逻辑**。

对于 $20\%$ 的数据，$1 \leq n \leq 10$。

对于 $40\%$ 的数据，$1 \leq n \leq 100$。 

对于 $60\%$ 的数据，$1 \leq n \leq 10^3$。 

对于 $80\%$ 的数据，$1 \leq n \leq 10^4$。

对于 $100\%$ 的数据，$1 \leq n \leq 2 \times 10^4$。  

注意输出不合法可能导致 WA/RE/TLE/MLE 等玄学问题。

## 样例 #1

### 输入

```
5

3

5```

### 输出

```

1 1 2 3

2 1 5

3 5 2 4 3 1```

# 题解

## 作者：Rnfmabj (赞：14)

做题背景：期末考试复习，下午有两节自习。我和长老 @Yeegle 趁自习用班上的希沃一体机打题，代码都是在你谷 IDE 里用屏幕键盘一点一点码的，就这还能切两道，离谱。

屏幕键盘的效率相当低下，所以长老为了压缩码量想出了 “ 用 cmp 魔改 sort 实现全自动交互 ” 的思路，在此表示膜拜及感谢。



------------
### 思路

官方的做法是分类讨论 + 归并排序，码量对于两个一体机 OIer 而言相当 EX 。当然复杂度还是很优秀的，“ 带巨大常数 ” 系 fAKe 言论。

我们考虑题目中操作的实际意义，或者用文化课老师的话来说，就是：**揣测出题人的意图**。

首先看到操作 1 ， “ 给 3 个数，得知其中排名中间的那个 ” ，乍看之下毫无头绪，既不能暴力一个一个比，也不能像 RMQ 那样得知区间的最大。

然后看到操作 2 ，这个操作不仅有 “ 2 个数中必须有一个排名第一 ” 的限制，而且只能得知谁排名第一，可我怎么保证我进行这个操作时，两个数里一定有一个排名第一呢？

…… 也就是说这个排名第一 一定可以只靠操作 1 得到？假如我做无数次操作 1 ，会发生什么？

**一定会有两个数绝对不会出现在操作 1 的回答中，这就是排名第一和排名最后。** 因为 排名第一 和 排名最后 无法靠后 / 靠前于任何一个人，自己也不行。

那我们只要做 $n-2$ 次操作就可以得到这两个人：用一个队列存下所有人的序号，每次从队首取 3 个序号出来并将其出队，对这 3 个序号执行操作 1 。然后将除回答得到的序号外的 2 个序号重新入队。

由于每次操作都会出队一个序号，在 $n-2$ 次操作后队列中就只剩下 2 个序号了，这就是排名最前和排名最后的序号。

接下来取出这两个序号，执行操作 2 ，就得到了排名第一。如此，操作 2 物尽其用。

接下来，我们已经知道了排名第一是谁，然后呢？

注意到 3 个数中排名最前已经确定时， “ 回答 3 个数中中间那个 ” 就是 “回答剩下 2 个数中排名靠前那个。”那么我们就可以利用排名第一执行操作 1 ，这样回答的就是剩下两个数中排名靠前那个。

**……那不就是一个赤裸裸的比较函数吗。**

借助这个性质，我们可以将其写成 cmp ，利用工具人 sort 同学进行 “ 全自动交互 ” ，从而节省不少码量。~~起码对于两个一体机打题人而言足够了~~

细节见代码。

### 代码

```
#include<bits/stdc++.h>
#define ll long long
#define R read()
using namespace std;
inline ll read() {
	ll s=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')f*=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*f;
}
inline void write(ll x) {
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10),x%=10;
	putchar('0'+x);
}//Don't use it for CF.
inline void wk(ll x){write(x);putchar(' ');}
inline void we(ll x){write(x);putchar('\n');}
ll n,a[20005]; 
ll i,j,k,b;// b 为通过第一轮操作 1 得出的最受喜爱，其余为工具变量。 
ll x[3];//第一轮操作 1 最后一步所用工具变量 
queue<ll> q;
bool cmp(ll l,ll r){//第二轮操作 1, 通过魔改cmp实现sort全自动交互（不是） 
    wk(1),wk(b),wk(l),we(r);//输出1,b,l,r。由于b已知最受喜爱，因此回答必为l,r中更受喜爱的那个。 
    fflush(stdout);
    i=R;
    return i==l?1:0;
}
int main(){
    n=R;
    for(i=0;i<n;i++)q.push(i+1);//将所有人入队，一会挨个踢出来 
    
    for(i=0;i<n-2;i++){
        wk(1);//第一轮操作 1 ，此阶段通过操作 1 将所有人筛得只剩最喜欢的和最不喜欢的。 
        for(j=0;j<3;j++){
        	wk(x[j]=q.front());
        	q.pop();
        }
        fflush(stdout);
        k=R;
        for(j=0;j<3;j++)if(x[j]!=k)q.push(x[j]);//将未被输出的重新入队。这样一来一定会剩两个从未被输出的，这就是最大和最小。 
    }
	x[0]=q.front();
    q.pop();
    x[1]=q.front();
    q.pop();//把最大最小拎出来 
    wk(2),wk(x[0]),wk(x[1]);//操作 2 ，揪出最喜欢的 
    fflush(stdout);
    b=R;//这样 b 就是最喜欢的了，然后拿去给 cmp 当工具人。 
    for(i=j=0;i<n;i++)if(i!=b-1)a[j++]=i+1;
    sort(a,a+n-1,cmp);//排序 ·魔改 ver
	//这样用这种画风清奇的快排，就可以轻松地用操作 1 来当做大小比较，从而得到排列。 
    wk(3),wk(b);//先把最喜欢的输了 
    for(i=0;i<n-1;i++)wk(a[i]);//依次输出 
    fflush(stdout);
    return 0;
}
```

坑点：记得 

```
fflush(stdout); 
```

劲 爆 交 互

超 长 输 出

评 测 特 性

当 场 超 时

---

## 作者：封禁用户 (赞：5)

这是本蒟蒻的第 $44$ 篇题解，P8052。

此前一直以为交互题很难，直到我这次成功做出了一题。就过来分享了。

思路大致与 @yeshubo_qwq 的代码是相似的。可惜这位大佬的题解并不是很清晰。

首先来分析**真心话**和**大冒险**两种操作。为简洁而言，我使用我们班俗称的“第一”、“第二”、“第三”表示喜欢的程度。（懂的都懂）

我们知道真心话最后返回的是第二大的。换个角度想，这个返回的可怜虫就不是“第一”。

我建立了一个队列，首先可以把所有人的编号入队（即循环 $1 \sim n$），然后每次取头三个元素，依次弹出，再询问，获取回答，将剩下两个归队。

这样在剩余三个时，进行一次真心话，就会剩余两个。我们知道每一次排除的既不是这三个中最令 Percy 稀饭的，也不是这三个中最令 Percy 掏盐的。那更不可能是全体的最稀饭或最掏盐的了。那这两个会出现在哪里呢？很容易想到，就是剩下这两个。

然后呢？经过我的推理，你一定想到该怎么做了：进行一次**大冒险**判断这两个哪个是“第一”，哪个是“第 $n$”。（即最令 Percy 稀饭和最令 Percy 掏盐）

我们得到了“第一“。然后如何判断其余的顺序？你也会一举反三的对吧，判断相邻两个编号的喜欢程度大小，类似冒泡排序，直接用 `sort` 从大到小排出顺序。记得不要排”第一“，因为我们已经知道其为第一个了。

这里有一个小坑点：**大冒险需要使两个参数有一个是最喜欢的**。

那我们就可以用**真心话**，传入”第一“，和这两个编号。因为”第一“肯定是稀饭程度最大的，所以返回的其实就是这两个编号中更稀饭的。因为我们输出的是”第二大“的。

不要忘记询问、输出后 `fflush(stdout);`，不然你的评测记录就会 五 彩 斑 斓 。（[MLE](https://www.luogu.com.cn/user/253738) 预警（））

最后贴一下代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
queue <int> devout;
int cupcake[20001];
int truelove;

bool meessing(int jiaoyan, int shaobing){ // cmp
	cout<<"1 "<<truelove<<" "<<jiaoyan<<" "<<shaobing<<endl; // 真心话
	fflush(stdout);
	int not_able;
	cin>>not_able;
	return not_able==jiaoyan; // 直接return里面判断
}

int main(){
	cin>>n;
	for (int i=1; i<=n; i++) devout.push(i); // 压入
	while (devout.size()!=2){
		for (int i=1; i<=3; i++) cupcake[i]=devout.front(), devout.pop(); // 依次弹出获取前三个元素并真心话
		cout<<"1 "<<cupcake[1]<<" "<<cupcake[2]<<" "<<cupcake[3]<<endl;
		fflush(stdout);
		int secbig;
		cin>>secbig;
		for (int i=1; i<=3; i++) 
			if (cupcake[i]!=secbig) devout.push(cupcake[i]); // 将没有排除的再次”审问“
	}
	
	int lovest=devout.front(), hatest; // ”第一“”第n“
	devout.pop(), hatest=devout.front();
	cout<<"2 "<<lovest<<" "<<hatest<<endl; // 询问
	fflush(stdout);
	cin>>truelove; // 哎呀呀，真爱啊~~~
	
	int cur=0;
	for (int i=1; i<=n; i++)
		if (truelove!=i) cur++, cupcake[cur]=i; // 这里就是排除”第一“，剩下的排序
	sort(cupcake+1, cupcake+cur+1, meessing); // 排序，直接这样就行
	
	cout<<"3 "<<truelove; // 输出
	for (int i=1; i<=cur; i++) cout<<" "<<cupcake[i]; // 输出
	fflush(stdout); // Do not be ＣＯＬＯＵＲＦＵＬ
	return 0;
}
```

谢谢大家，希望这篇题解能让你茅塞顿开。我从来没有这么认真写过一篇题解，这是第一次。

---

## 作者：CaiZi (赞：4)

## P8052 [ZYOI Round1] Truth/真心话大冒险 题解
#### [题目链接](https://www.luogu.com.cn/problem/P8052)
### 题目分析
非常好玩的一道交互题，并且难度也比较宜人。

有 $n$ 个人，你想知道 Percy 对于这 $n$ 个人的好感度，其中我们设 $a_i$ 为编号为 $i$ 的人的在 Percy 中的排名。其中，你可以和交互库进行两种不同的操作。

操作 $1$ 输出 $3$ 个编号 $x,y,z$，返回 $a_x,a_y,a_z$ 中第 $2$ 大的数的编号。

操作 $2$ 输出 $2$ 个编号 $x,y$，返回 $a_x,a_y$ 中第 $1$ 大的数的编号。这个操作有一个重点：必须保证异性 $x,y$ 之中必有一个是 Percy 最喜欢的。这意味着，你需要在确定 $a_x=\max\limits_{1 \le i \le n} a_i$ 或 $a_y=\max\limits_{1 \le i \le n} a_i$ 的情况下才可以使用操作 $2$。

那问题来了。我们如何只利用操作 $1$ 找出最大值，在使用操作 $2$ 呢？

操作 $1$ 返回的是输出的 $a_x,a_y,a_z$ 中的第 $2$ 喜欢的人的编号，也就意味着，操作 $1$ 找出的数字一定不是全部人中的最大值和最小值，那么我们使用队列将 $1\sim n$ 储存，每次取出队头的 $3$ 个数进行操作 $1$，然后将返回值以外的数加回队列。比较完成后，队列里剩下的就是 $\max\limits_{1 \le i \le n} a_i$ 的编号和 $\min\limits_{1 \le i \le n} a_i$ 的编号了。接下来使用操作 $2$，就可以得到 $\max\limits_{1 \le i \le n} a_i$ 的编号了，记为 $ans$。

已知最喜欢的人了，接下来就简单了，我们设 $m_i\gets i$，然后使用 ```std::sort```。我们可以拿两个喜欢的人与最喜欢的人比较。在这里，我们通过修改 ```sort``` 函数的比较方式，将每次比较时进行操作 $1$，输出 $x,y,ans$，输入 $u$，最后输出序列就行了。需要注意的是，我们在比较前需要使 $m_0\gets ans$，同时使 $m_{ans}\gets n$，否则将会在一次比较中输出两个相同的数导致 WA。
### 代码展示
最多进行 $n\log n+n$ 次操作，可以通过本题。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[4],ans,m[21451],u;
queue<int>q;
bool cmp(int a,int b){
	cout<<"1 "<<ans<<' '<<a<<' '<<b<<endl;//将最喜欢的人和剩下两人比较，找出两人中Percy更喜欢的
	cin>>u;
	return u==a;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		q.push(i);
		m[i]=i;
		if(i>=3){
			cout<<"1 ";
			for(int j=1;j<=3;j++){
				x[j]=q.front();
				q.pop();
				cout<<x[j]<<' ';//将队头3个数进行操作 1
			}
			cout<<endl;
			cin>>ans;
			for(int j=1;j<=3;j++){
				if(x[j]!=ans){//去除Percy第2喜欢的人
					q.push(x[j]);
				}
			}
		}
	}
	cout<<"2 ";
	for(int i=1;i<=2;i++){
		cout<<q.front()<<' ';
		q.pop();
	}
	cout<<endl;
	cin>>ans;//Percy最喜欢的人
	m[ans]=m[n];
	m[0]=ans;//避免将ans与ans比较
	sort(m+1,m+n,cmp);
	cout<<"3 ";
	for(int i=0;i<n;i++){//输出答案，注意ans在第0位
		cout<<m[i]<<' ';
	}
	cout<<endl;
	return 0;
}
```

---

## 作者：yeshubo_qwq (赞：2)

## 思路
首先，求出最大值。

用一种数据结构（单端队列，双端队列，优先队列，栈等都行，最好用方便删除与插入的），把全部人放进去，每次取出三个人，进行真心话操作，返回的是值第二大的人，那个人一定不是最大的，把剩下两个人放回去。如此操作，最后剩下两个人一定是最大的和最小的，进行大冒险操作，即可求出最大值。

然后，真心话操作就变成了比较工具。

真心话操作询问最大值和另外两个人，因为最大值一定在三个人中排第一，所以返回的就是另外两个人中较大的那个人。

因此，我们可以直接将其写成 cmp，直接 sort 完事。

最后直接输出答案就可以了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int _1(int x,int y,int z){//真心话操作 
	printf("1 %d %d %d\n",x,y,z);
	fflush(stdout);
	//注意：程序中的fflush(stdout);一定要加，否则会TLE
	int ans;
	scanf("%d",&ans);
	return ans;
}
int _2(int x,int y){//大冒险操作 
	printf("2 %d %d\n",x,y);
	fflush(stdout);
	int ans;
	scanf("%d",&ans);
	return ans;
}
int n,i,x,fir,a[20005];
queue <int> p;
bool cmp(int x,int y){
	return _1(fir,x,y)==x;
}
int main(){
	scanf("%d",&n);
	//求出最大值存入fir 
	for(i=1;i<=n;i++)p.push(i);
	while(p.size()>2){
		for(i=1;i<=3;i++){a[i]=p.front();p.pop();}
		x=_1(a[1],a[2],a[3]);
		for(i=1;i<=3;i++)
			if(a[i]!=x)p.push(a[i]);		
	}
	x=p.front();p.pop();
	fir=_2(x,p.front());
	//除了最大值放进数组并用sort进行排序 
	int m=n;n=0;
	for(i=1;i<=m;i++)
		if(i!=fir)a[++n]=i;
	sort(a+1,a+1+n,cmp);
	//完结输出答案 
	printf("3 %d",fir);
	for(i=1;i<=n;i++)printf(" %d",a[i]);
	fflush(stdout);
	return 0;
}
```


---

## 作者：KidA (赞：1)

$$
\text{Solution}
$$

一道十分有趣的交互题。

我们知道，“真心话”操作返回的是 $x,y,z$ 中 Percy **第二喜欢的人**，所以该操作不可能返回 Percy **最喜欢的人**与**最不喜欢的人**。

既然如此，我们便可以维护一个队列 $q$，初始时存入 $1 \sim n$ 每个人，接着不断取出队首的 $3$ 个元素进行”真心话操作，得出其中第二喜欢的人，并将剩余的人重新放回队列中。这样循环 $n-2$ 次之后，队列中便只剩下了 Percy 最喜欢与最不喜欢的人了。对这两人进行一次“大冒险”操作，就得到了 Percy 最喜欢的人。先将其输出。

在得到了 Percy 最喜欢的人之后，我们将除去此人之外的所有人存入 $a$ 数组，并将 $a$ 数组排序并输出即可。

那么问题来了，如何对 $a$ 数组排序？注意到“真心话”操作返回的是 Percy 第二喜欢的人，也就相当于返回 **在除去第一喜欢的人之外的两人中，Percy 最喜欢的人**。利用这一机制，我们便可将其写成 `cmp` 函数，不断地将待比较的两数与 Percy 最喜欢的人进行“真心话”操作，从而确定这两个数的排名。具体实现如下：

```cpp
bool cmp(int x,int y){
    cout<<1<<' '<<best<<' '<<x<<' '<<y<<' ';
    //best、x、y分别表示Percy最喜欢的人与待比较的两数
    fflush(stdout);
    
    k=read(); //k接收“真心话”操作的返回值
    return k==x?1:0;
}
```

注意：

- 每次输出后要勤加 `fflush(stdout)` ！！！

- 每次操作前，不要忘记输出操作种类！！！

---

$$
\text{Code}
$$

- [代码](https://www.luogu.com.cn/paste/1zgbt9o8)。

- [测评记录](https://www.luogu.com.cn/record/list?pid=P8052&user=542221&page=1)。

完结撒花~

---

## 作者：BreakPlus (赞：1)

挺有意思的交互题。

首先我们考虑找出最大值。由于三个数中的第二大值绝对不是最大值，考虑一下算法。


0. 将 $1,2,3,...,n$ 放入一个栈。
1. （执行 $n-2$ 次）取栈顶三个数，使用 $1$ 号询问出次大值，然后这三个数中不是次大值的两个数弹回队列。
2. （执行 $1$ 次）此时栈里还剩两个数，其中必然有一个是最大值，因为之前排出的都不是最大值。进行 $2$ 号询问就可以找到最大值。

找到最大值后，我们有以下比较两个数 $x,y$ 的方法：

询问 ``1 max x y ``，其中 max 是最大值的编号。如果得出结果是 $x$ 说明 $x$ 更大，否则 $y$ 更大。

既然有了比较的方法，我们就可以选取稳定的 $O(n \log n)$ 排序算法——归并排序解决了。

代码实现较为简单。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,maxx;
stack<ll>stk; ll a[20005],b[20005],cnt;
bool less_than(ll a,ll b){
	cout<<"1 "<<maxx<<" "<<a<<" "<<b<<endl;
	ll temp; cin>>temp;
	return temp==b; 
} // 判断
void msort(ll l,ll r){
    if(l==r) return;
    ll mid=l+r>>1;
    msort(l,mid),msort(mid+1,r);
    ll i=l,j=mid+1,now=l;
    while(i<=mid&&j<=r) b[now++]=less_than(a[i],a[j])?a[i++]:a[j++];
    while(i<=mid) b[now++]=a[i++];
    while(j<=r) b[now++]=a[j++];
    for(ll i=l;i<=r;i++) a[i]=b[i];
} // 归并排序模板
int main(){
	cin>>n;
	if(n==1){
		cout<<"3 1"<<endl;
		return 0;
	}// 特判 n=1
	if(n==2){
		cout<<"2 1 2"<<endl;
		ll temp; cin>>temp;
		if(temp==2) cout<<"3 2 1"<<endl;
		else cout<<"3 1 2"<<endl;
        return 0;
	}// 特判 n=2
	for(ll i=1;i<=n;i++) stk.push(i);
	for(ll i=1;i<n-1;i++){
		ll a1=stk.top(); stk.pop();
		ll a2=stk.top(); stk.pop();
		ll a3=stk.top(); stk.pop();
		cout<<"1 "<<a1<<" "<<a2<<" "<<a3<<endl;
		ll temp; cin>>temp;
		if(a1!=temp) stk.push(a1);
		if(a2!=temp) stk.push(a2);
		if(a3!=temp) stk.push(a3);
	}
	ll no1=stk.top(); stk.pop(); ll no2=stk.top();
	cout<<"2 "<<no1<<" "<<no2<<endl;
	ll temp; cin>>temp;
	if(temp==no1) maxx=no1;
	else maxx=no2;
	// 以上算法找出最大值
	for(ll i=1;i<=n;i++) 
		if(i!=maxx) a[++cnt]=i;
	// 抠出不是最大值的，进行归并排序
	msort(1,cnt);
    
	cout<<"3 "<<maxx<<" ";
	for(ll i=cnt;i>=1;i--) cout<<a[i]<<" ";
	cout<<endl;
} 
```

---

## 作者：Tiger_Rory (赞：0)

本题太有趣了，感谢 @[CaiZi](https://www.luogu.com.cn/user/728853) 把本题搬到了模拟赛中。

考虑先进行 $n-2$ 次真心话，每次把排名第二的异性丢掉，从而把好感度最高和最低的异性求出来。然后我们固定一个异性（最高最低异性中的一个）将其他异性进行排序。如何排序？我们可以排序时通过真心话来确定顺序，可以保证单调性（递增或递减）。这是本题的精髓所在。排序完后可以发现序列不是单调递增就是单调递减，做一次大冒险就可以容易地确定答案，解决本题了！

接下来对代码部分进行一些解释，可能与一些题解有雷同。


```cpp
int qry1(int x,int y,int z){
	cout<<"1 "<<x<<' '<<y<<' '<<z<<'\n';  
	int answer; cin>>answer;   
	return answer;    
}
int qry2(int x,int y){
	cout<<"2 "<<x<<' '<<y<<'\n'; 
	int answer; cin>>answer;  
	return answer; 
}
```

输出函数，不必多说。

```cpp
q.push(1);q.push(2); 
for(int i=3;i<=n;i++){
  int x=q.front();q.pop(); 
  int y=q.front();q.pop(); 
  int ans=qry1(x,y,i);  
  if(ans!=x)q.push(x); 
  if(ans!=y)q.push(y); 
  if(ans!=i)q.push(i); 	
}
s[1]=q.front();q.pop(); 
```
用队列实现每次真心话，把排名第二的异性丢掉，从而把好感度最高和最低的异性求出来。最后固定一个异性。


```cpp
bool cmp(int x,int y){
	return qry1(x,y,s[1])==x;    
}
for(int i=2;i<=n;i++){
	if(i<=s[1]){
		s[i]=i-1; 
	}
	else{
		s[i]=i; 
	}
}
sort(s+2,s+n+1,cmp); 
```
排序，需要稍微预处理一下，不然编号对不上。

排序中调用的判断函数可以保证返回的那个异性一定是高的那个或低的那个，这样答案序列就可以求出来了，应该比较好理解。


```cpp
int ans=qry2(s[1],q.front());

cout<<"3 ";   
if(ans==s[1]){
	for(int i=1;i<=n;i++){
		cout<<s[i]<<' '; 
	}
        cout<<'\n';
}
else{
	for(int i=n;i>=1;i--){
		cout<<s[i]<<' '; 
	}
	cout<<'\n'; 
} 
```
大冒险后输出答案，解决本题。

如有不足，欢迎批评指出。

再次感谢 @[CaiZi](https://www.luogu.com.cn/user/728853) 的辛勤付出。

---


# Photographer

## 题目描述

Valera's lifelong ambition was to be a photographer, so he bought a new camera. Every day he got more and more clients asking for photos, and one day Valera needed a program that would determine the maximum number of people he can serve.

The camera's memory is $ d $ megabytes. Valera's camera can take photos of high and low quality. One low quality photo takes $ a $ megabytes of memory, one high quality photo take $ b $ megabytes of memory. For unknown reasons, each client asks him to make several low quality photos and several high quality photos. More formally, the $ i $ -th client asks to make $ x_{i} $ low quality photos and $ y_{i} $ high quality photos.

Valera wants to serve as many clients per day as possible, provided that they will be pleased with his work. To please the $ i $ -th client, Valera needs to give him everything he wants, that is, to make $ x_{i} $ low quality photos and $ y_{i} $ high quality photos. To make one low quality photo, the camera must have at least $ a $ megabytes of free memory space. Similarly, to make one high quality photo, the camera must have at least $ b $ megabytes of free memory space. Initially the camera's memory is empty. Valera also does not delete photos from the camera so that the camera's memory gradually fills up.

Calculate the maximum number of clients Valera can successfully serve and print the numbers of these clients.

## 样例 #1

### 输入

```
3 10
2 3
1 4
2 1
1 0
```

### 输出

```
2
3 2 ```

## 样例 #2

### 输入

```
3 6
6 6
1 1
1 0
1 0
```

### 输出

```
1
2 ```

# 题解

## 作者：Szr__QAQ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF203C)


------------
**思路**：

本题无坑点，又因为题目所求最多可以满足多少位客户，所以用贪心，写一个让结构体**从小到大**排序的函数即可。

首先定义一个结构体，结构体内部存储低与高质量照片的张数，该用户的编号以及该用户的所有照片所需占用的内存，之后就正常输入，在输入时计算第 $i$ 名用户所有照片所需占用的内存，之后就将全部用户的所有照片所需占用的内存从小到大排序，之后再计算最多可以满足多少位客户，最后再输出用户编号即可。


------------
**完整代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int qwq=1e5+10;
struct szr{
	int x,y,id,sum;
}photo[qwq];
int n,d,a,b,cnt=0;

bool cmp(szr a,szr b){//从小到大排序的函数 
	return a.sum<b.sum;
}

int main()
{
	cin>>n>>d>>a>>b;
	for(int i=1;i<=n;i++)
	{
		cin>>photo[i].x>>photo[i].y;
		photo[i].id=i;
		photo[i].sum=photo[i].x*a+photo[i].y*b;
	}
	
	sort(photo+1,photo+n+1,cmp);
	
	for(int i=1;i<=n;i++){//计算可以满足多少位客户 
		if(photo[i].sum<=d)
		{
			d-=photo[i].sum;
			cnt++;
		}
		else
		{
			break;
		}
	}
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)//最后根据满足用户的人数，输出编号即可 
	{
		cout<<photo[i].id<<" ";
	}
	return 0;	
} 
```


------------
本人只是一名小蒟蒻，若有错误请指正，谢谢大家。

---

## 作者：yzm0325 (赞：2)

upd：因为之前 RMJ 炸了，导致一开始代码时错的，非常抱歉。现在已将代码改正。

---

一道贪心的例题。很明显，只要满足需要内存比较少的客户，就能满足更多的客户。

所以可以先把每个用户用到的总共的内存和这个用户的编号存进结构体里，再根据内存从小到大排序，然后依次进行判断，如果内存不够了就退出循环，否则增加满足人数并把用户编号加入答案数组里。

最后，先输出答案，再依次输出答案数组里的每个数，用空格隔开。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct client {
    int s, id; // 因为要输出用户编号，所以加一个 id。
} yh[100010];
int n, a, b, d, ans;
bool cmp(client a, client b) {
    return a.s < b.s;
}
int main() {
    cin >> n >> d >> a >> b;
    for(int i = 1; i <= n; i++) {
        int x, y; // 两种照片的数量。
        cin >> x >> y;
        yh[i].s = x * a + y * b; // 计算总共多少兆字节。
        yh[i].id = i;
    }
    sort(yh + 1, yh + n + 1, cmp); // 贪心。
    for(int i = 1; i <= n; i++) {
        d -= yh[i].s; // 占用内存。
        if(d < 0) break;
        ans++; // 满足要求的用户数加一。
    }
    cout << ans << "\n";
    for(int i = 1; i <= ans; i++) cout << yh[i].id << " "; // 别忘了空格。
    return 0;
}
```


---

## 作者：liupan2010 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF203C)

------------

此题直接将客户所需的内存 ```sort``` 一下，再一个个用 $d$ 去减去靠在前面的客户内存，如果 $d>0$ 就将答案加一，最后输出即可。

具体可见代码。

------------

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int get=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{	
		if(c=='-')w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		get=get*10+c-'0';
		c=getchar();
	}
	return get*w;
}
void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>=10)
		write(x/10);
	putchar(x%10+'0');
}
int n,d,a,b,s,i;
struct kehu
{
    int x,y,num;
    int id;
}kh[100001];
bool cmp(kehu A,kehu B)
{
    return A.num<B.num;
}
int main()
{
    n=read(),d=read(),a=read(),b=read();
    for(i=1;i<=n;i++)
    {
        kh[i].x=read(),kh[i].y=read();
        kh[i].id=i;
        kh[i].num=kh[i].x*a+kh[i].y*b;
    }
    sort(kh+1,kh+n+1,cmp); 
    for(i=1;i<=n;i++)
    {
        d-=kh[i].num;
        if(d<0)
        	break;
        s++;
    }
    write(s);
    puts("");
    for(i=1;i<=s;i++)
        write(kh[i].id),putchar(' ');
    return 0;   
} 
```

------------

后记：

因为 RMJ 暂时炸了，导致最开始给出的代码是错的。现在已经将代码改正，可以正常 AC 了。

---

## 作者：zhuweiqi (赞：1)

非常简单的贪心问题。

先开一个结构体数组记录每位客户的序号以及他所需要的内存，再按内存从小到大排序，然后判断最多能满足多少位客户的要求，输出这个答案，最后再分别输出他们的序号即可。上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int f=1,n=0;
	char c=getchar();
	while(c<'0' || c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n*f;
}
struct node{
	int x,y,idx,t;
}s[100005];
bool cmp(node a,node b){return a.t<b.t;}
int main(){
	int n=read(),d=read(),a=read(),b=read();
	for(int i=1;i<=n;i++){
		s[i].x=read(),s[i].y=read();
		s[i].t=s[i].x*a+s[i].y*b;
		s[i].idx=i;
	}
	sort(s+1,s+1+n,cmp);
	int x=d,ans=0;
	for(int i=1;i<=n;i++){
		if(x>=s[i].t){
			x-=s[i].t;
			ans++;
		}
		else break;
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++){
		if(d>=s[i].t){
			d-=s[i].t;
			printf("%d ",s[i].idx);
		}
	}
	return 0;
}
```

---

## 作者：Dr_Glitch (赞：0)

## 思路

[题目传送门](https://www.luogu.com.cn/problem/CF203C)

首先回顾题目，要求在给定内存上限 $d$ 的条件下，已知每张低质量照片所占的内存为 $a$，每张高质量照片所占的内存为 $b$。第 $i$ 个客户需要存 $X_i$ 张低质量照片和 $Y_i$ 张高质量照片，求最多能满足多少客户及他们的编号。

根据题目信息，显然一个客户被满足就等价于他要求的每一张照片都被存了下来。考虑贪心，将每一个客户所需的内存从小到大排序，依次存入照片，直到存不下下一位客户的所有照片时停止，最后输出即可。

## Code

```cpp
#include<bits/stdc++.h>
#define init read()
using namespace std;
const int N=100005;
int n,d,a,b,tot=0;
struct Person //每一位用户的编号及所需的内存
{
	int id;
	int val;
}p[N];
inline int read()
{
	int mmm=0,ff=1;char xx=getchar();
	while((xx<'0'||xx>'9')&&xx!='-')xx=getchar();
	if(xx=='-')ff=-1,xx=getchar();
	while(xx>='0'&&xx<='9')
	mmm=mmm*10+xx-'0',xx=getchar();
	return mmm*ff;
}
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
inline bool comp(const Person &i,const Person &j) //按内存占用升序排序
{
	return i.val<j.val;
}
int main()
{
	n=init;d=init;a=init;b=init;
	for(int i=1;i<=n;i++)
	{
		int x=init,y=init;
		p[i].id=i;
		p[i].val=a*x+b*y; //计算每个客户所需的总内存
	}
	sort(p+1,p+n+1,comp);
	for(int i=1;i<=n;i++)
	{
		if(p[i].val<=d)
		{
			tot++;
			d-=p[i].val;
		}
		else break; //剩下的客户一定不能存入所有照片
	}
	write(tot);putchar('\n');
	for(int i=1;i<=tot;i++)
	{
		write(p[i].id);putchar(' ');
	}
	return 0;
}
```

---

## 作者：CleverRaccoon (赞：0)

## 题目

[题目传送门](https://www.luogu.com.cn/problem/CF203C)


## 思路

典型的贪心算法。

贪心的策略是：首先满足需求字节数少的用户。

你想到了哪个函数？```sort```！

因为最后要输出用户的编号，所以排序时要用结构体记录用户的编号，使用 ```sort``` 函数，根据每个用户需要的内存，从小到大排序。~~（当然你要是想手写排序算法我也不拦着你）~~

然后循环依次判断能满足多少个用户，将剩余的内存值减去当前的用户需要的内存。如果内存不够，就终止循环。否则就记录用户编号。

这里使用了 ```vector``` 来记录，因为长度不确定，而且到最后直接输出它的长度就是能满足的用户数量了。

## 细节

1. 要在输入时计算出每个用户需要的内存。这里运用了 ```C++``` 的新特性，大括号里面两个元素分别是内存和用户编号，直接一行就搞定！

```cpp
a[i] = {aa * x + b * y, i};
```


2. ```lambda``` 是一个好东西，排序时，不用定义比较函数，用一个匿名函数即可。语法格式大概就是下面这样了。


```cpp
sort(a + 1, a + n + 1, [](node a, node b) {
	return a.use < b.use;
});
```

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
struct node {
    // use是每个用户需要的字节数，id是用户编号
    int use, id;
} a[N];
vector<int> ans;    // 记录答案的vector（用数组也可以，这里是因为长度不确定所以使用的vector）
int n, d, aa, b;
// aa是为了避免与数组名重复

int main() {
    cin >> n >> d >> aa >> b;
    for(int i = 1, x, y; i <= n; ++i) {
        cin >> x >> y;
        a[i] = {aa * x + b * y, i};  // 使用C++新特性的写法
    }
    // 使用lambda
    sort(a + 1, a + n + 1, [](node a, node b) {
        return a.use < b.use;   // 从小到大排序
    });
    for(int i = 1; i <= n; ++i) {
        if((d -= a[i].use) <= 0)    // d -= a[i].use返回的就是d进行减少操作后的值
            break;
        ans.push_back(a[i].id);
    }
    cout << ans.size() << '\n'; // ans数组的大小就是最多可以满足的用户数量
    for(int i = 0; i < ans.size(); ++i)
        cout << ans[i] << ' ';
    return 0;
}
```

谢谢大家！完结撒花！




---


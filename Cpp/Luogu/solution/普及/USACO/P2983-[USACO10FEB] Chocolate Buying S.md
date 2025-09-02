# [USACO10FEB] Chocolate Buying S

## 题目描述

Bessie and the herd love chocolate so Farmer John is buying them some.

The Bovine Chocolate Store features $N (1 \le N \le 100,000)$ kinds of chocolate in essentially unlimited quantities.  Each type i of chocolate has price $P_i (1 \le P_i \le 10^{18})$ per piece and there are $C_i (1 \le C_i \le 10^{18})$ cows that want that type of chocolate.

Farmer John has a budget of $B (1 \le B \le 10^{18})$ that he can spend on chocolates for the cows. What is the maximum number of cows that he can satisfy?  All cows only want one type of chocolate, and will be satisfied only by that type.

Consider an example where FJ has $50$ to spend on $5$ different types of chocolate. A total of eleven cows have various chocolate preferences:

|Chocolate\_Type|Per\_Chocolate\_Cost|Cows\_preferring\_this\_type| 
|:-----------:|:-----------:|:-----------:|
|$1$|$5$|$3$|
|$2$|$1$|$1$|
|$3$|$10$|$4$|
|$4$|$7$|$2$|
|$5$|$60$|$1$|

Obviously, FJ can't purchase chocolate type $5$, since he doesn't have enough money. Even if it cost only $50$, it's a counterproductive purchase since only one cow would be satisfied.

Looking at the chocolates start at the less expensive ones, he can purchase $1$ chocolate of type $2$ for $1 \times 1$ leaving $50-1=49$, then purchase $3$ chocolate of type $1$ for $3 \times 5$ leaving $49-15=34$, then  purchase $2$ chocolate of type $4$ for $2 \times 7$ leaving $34-14=20$, then  purchase $2$ chocolate of type $3$ for $2 \times 10$ leaving $20-20=0$.

He would thus satisfy $1 + 3 + 2 + 2 = 8$ cows. 

## 样例 #1

### 输入

```
5 50 
5 3 
1 1 
10 4 
7 2 
60 1 
```

### 输出

```
8 
```

# 题解

## 作者：K0stlin (赞：21)

## 纯贪心+结构体排序
~~一开始我还以为是背包，自从看到了10^18~~

没用int64之类，而是unsigned long long（代码如下）
```cpp
#include<iostream>
#include<algorithm>
using namespace std;//正常
int n;
unsigned long long ans,v;
struct cz{
	unsigned long long p,c;
}a[100005];//全部开unsigned long long
bool cmp(cz x,cz y){return x.p<y.p;}//结构体排序必要的cmp QAQ
int main(){
	cin>>n>>v;
	for(int i=1;i<=n;i++)cin>>a[i].p>>a[i].c;//表示不会用scanf（unsigned long long）
	sort(a+1,a+n+1,cmp);//结构体排序
	for(int i=1;i<=n;i++){//贪心ing
		if(v>a[i].p*a[i].c){v=v-a[i].p*a[i].c;ans+=a[i].c;}//能让第i种奶牛全部高兴就高兴
		else{ans+=v/a[i].p;break;}//不能了就尽量是奶牛高兴
	}
	cout<<ans;
	return 0;
}
```
SEE YOU!
（蒟蒻的第一篇题解，求过QAQ）

---

## 作者：llzzxx712 (赞：9)

# 十分基础的贪心
   但是对一些初学者来说还是有一些难度的。具体的算法和其它题解差不多，就是排序巧克力价格，尽量多的买便宜的，但是注释非常详细，可以让初学者很容易看懂。
   **下面是AC代码**
   ```cpp
#include<bits/stdc++.h>
using namespace std;
long long int x,y;
struct cow
{
	    long long int p,c;//p代表该巧克力价格，c表示喜欢该巧克力的奶牛数 
}c[100002];
int com(cow a,cow b)//结构体排序自定义比较 
{
	    return a.p<b.p;//比较价格，'<'就从小到大排，'>'就从大到小排（方便记忆） 
}
int main()
{
        int n;
	    unsigned long long int b,ans=0;//刚开始用long long 爆了，就用了unsigned long long 
        cin>>n>>b;//n同题目意思，b表示还剩下的预算 
        for(int i=0;i<n;i++){
    	    cin>>c[i].p>>c[i].c;
	    }
	    sort(c,c+n,com);//快排 
	    for(int i=0;i<n;i++){ //现在已经从小到大排好序了，从价格低的到价格高的买 
		if(b>c[i].c*c[i].p){/*如果现在剩余的钱可以买下这堆巧克力
                             （即剩下的钱b大于该巧克力价格乘喜欢该巧克力的奶牛数*/
		    ans+=c[i].c;//更新答案，加上这次高兴的奶牛 
		    b-=c[i].c*c[i].p;//更新b，减掉这次花费的钱 
		    continue; 
		}
		else{//如果现在的钱不够买光这堆巧克力 
		    ans+=b/c[i].p;/*那么就尽量多地买，剩下的钱除以这种巧克力价格，
                              自动向下（其实是向0）取整后就是本次可以买的数量 */
	           break;/*由于剩下的钱不够买这种巧克力了，而下次循环中的巧克力更贵
               （排序过了），所以可以直接跳出循环输出答案 */
		}
	    }
	    cout<<ans;
	    return 0;
}
	

	

```


---

## 作者：wisdom_grass (赞：5)

吐槽：

---------------

本魔芋初学**dp**，想找些水题看看。

翻到这题，乍看以为多重背包，然后发现是**贪心**！

看标签，上面明显写着[动态规划，动规，dp](https://www.luogu.org/problem/lists?name=&orderitem=difficulty&tag=3&type=)。

初学不久的我看题解，明显的**贪心**。

于是我A了这题。

# (这个故事告诉我们：千万不要相信**洛谷标签**！要靠自己！标签只是一个参考！不能随意相信标签！)

---------------

楼下dalao都写得很清楚了，我之所以想发这篇题解，是因为我想介绍一下C++的STL。

---------------

（正片：）

我想这题dp，一看就是个背包，

### 巧克力售价是**价值**，喜欢第$i$种巧克力的奶牛是**体积**。

但是，再看了一会儿以后，发现不一定要全部满足第$i$种巧克力的奶牛，可以只满足一半。这正是贪心成立的理由。

然后，我们发现，希望满足$N$只奶牛，先用价值最小的巧克力去满足那只奶牛是最优的方法。因为这样就可以更加省钱，为后面还没吃到巧克力的奶牛给予希望。

总体如下：

- 1：我们将价值从小到大排序；
- 2：先用价值最小的巧克力去满足这只奶牛；
- 3：重复第2步骤，直到钱不够或奶牛都被满足为止。

## 不过要注意数据范围，记得开longlong，否则会爆！！！

上代码：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 100004;
long long n,b;
vector < pair < long long, long long > > a;
//vector和数组差不多，只不过他不定长，在不确定数据大小的情况下，vector可能可以节省很多空间
//pair和结构体差不多，只不过他不用写变量名、定义类型名等等，在只有两个量的情况下推荐写pair
long long ans;

int main() {
	cin >> n >> b;
	long long x,y;
	for(long long i = 1; i <= n; i++) {
		scanf("%lld %lld", &x, &y);
        //%lld读入longlong占位符
		a.push_back({x, y});
        //在a数组中插入一个元素在末尾，{x, y}表示一个pair型的量，第一个元素是x，第二个是y
	}

	sort(a.begin(), a.end());
    //begin()获得第一个元素的位置，end()获得最后一个元素的位置

	for(long long i = 0; i < n; i++) {
    //vector数组第一个数下标为0

		if(b / a[i].first < a[i].second) {
        //如果这种巧克力不能满足所有奶牛
			ans += b / a[i].first;
            //那么满足能满足的奶牛，满足完毕后肯定不能再满足其它奶牛了
			break;
            //跳出循环
		}
        //如果可以满足所有奶牛，那么全部满足
		ans += a[i].second;
		b -= a[i].first * a[i].second;
        //这里的.first .second表示调用这个结构体中第一个元素、第二个元素
	}
	cout << ans;
	return 0;
}

```

---

## 作者：lshhhhhh (赞：4)

#其实这题非常简单，非常水，就是纯贪心，不过要注意这题的数据范围，所以要开long long,使用结构体排序，按价格从小到大排序，然后从最便宜的开始贪心就可以啦

```cpp
#include<cstdio>
#include<algorithm>
struct aa{
    long long p,c;
}t[100001];
bool kmp(const aa &a1,const aa &a2){
    return a1.p<a2.p;
}
int n;
long long b,ans;
using namespace std;
int main()
{
    scanf("%d%lld",&n,&b);
    for(int i=1;i<=n;i++)scanf("%lld%lld",&t[i].p,&t[i].c);
    sort(t+1,t+1+n,kmp);
    for(int i=1;i<=n;i++)
    {
        long long k=b/t[i].p;
        if(k>t[i].c)
        {
            b-=t[i].c*t[i].p,ans+=t[i].c;
        }
        else {ans+=k;break;}
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：ViXpop (赞：1)

### 正解：排序+贪心

当我看到这样的题面的时候：

```
有N种巧克力，每种巧克力的数量都是无限多的。每头奶牛只喜欢一种巧克力，调查显示，

有Ci头奶牛喜欢第i种巧克力，这种巧克力的售价是P。

约翰手上有B元预算，怎样用这些钱让尽量多的奶牛高兴呢？
```

哎呀真爽，裸的背包DP，直接开打

打完交一发，瞬间爆炸

再一看数据，1e18，不炸才怪

#### 但是标签确实写的是DP啊！！！

这件事告诉我，千万不要乱相信标签

既然背包行不通，我们不妨尝试一下贪心，尽量满足喜欢价格低的巧克力的所有奶牛，然后价格依次上涨，只到没钱或者全部满足

#### 由于数据比较大，一定要开long long

~~蒟蒻之前因为开int炸了，果然还是define int long long比较适合我~~

#### 下面上代码

```
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#define mem(i,j) memset(i,j,sizeof(i))
#define int long long 
using namespace std;
inline int read(){
    int res=0,f=1;char ch=' ';
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
    return res*f;
}
void write(int x){
    if(x<0){putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=1e7+5;
int n,m,ans;
struct node{
    int p,c;
}q[N];
bool cmp(node x,node y){return x.p<y.p;}
#undef int 
int main(){
    n=read(),m=read();
    for(register int i=1;i<=n;i++)q[i].p=read(),q[i].c=read();
    sort(q+1,q+n+1,cmp);
    for(register int i=1;i<=n;i++){
        long long k=m/q[i].p;
        if(k>q[i].c)ans+=q[i].c,m-=q[i].p*q[i].c;
        else{ans+=k;break;}
    }
    printf("%lld",ans);
    return 0;
}

```
快乐结束~qwq

---

## 作者：Dr_殇 (赞：1)

#其实这题就是一个简单的贪心，没有什么难度，只要会一点结构体，就会做了。


##这题要用有限的钱，买到尽量多的巧克力，但巧克力是有限的，每种巧克力只会有一定的奶牛喜欢，我用ans来存储最多的奶牛数，然后根据价格从高到低排序，然后逐个判断就行了。


##注：这题除了n以外的变量，都要开long long类型的，要不然会超！（像我，没有用long long，提交了十多次才过）


##代码如下：







```cpp
#include <ctime>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>//头文件准备
using namespace std;
long long n,m,ans;//所有值都要开long long
struct Cow{
    long long c;
    long long v;
}cow[100005];//定义结构体，方便排序
bool cmp(Cow x,Cow y){//结构体排序规则
    if (x.c!=y.c)return x.c<y.c;//按价格从低到高排序
    else return x.v>y.v;//价格一样就按可以满足的奶牛数从多到少排序
}
int main(){
    scanf ("%lld %lld",&n,&m);//这里提醒一下，long long读入要用%lld
    for (int i=1;i<=n;i++){
        scanf ("%lld %lld",&cow[i].c,&cow[i].v);
    }
    sort (cow+1,cow+1+n,cmp);
    for (int i=1;i<=n;i++){
        if (cow[i].c<=m){//如果剩下的钱够买这种巧克力，那么就尽量能买多少就买多少
            long long k=min(m/cow[i].c,cow[i].v);//如果有钱，就把这种巧克力全买了，要么能买多少就买多少
            m-=k*cow[i].c;//然后减去花掉的钱
            ans+=k;//加上满足的奶牛数
        }
    }
    printf ("%lld\n",ans);//最后输出结果，提醒一下，long long的输出也要用%lld
    return 0;
}
```
完成！

#这题千万要用long long！


##珍爱生命，拒绝抄袭！


---

## 作者：AkiwaZawa (赞：0)

## 贪心

~~刚看到的时候还以为是背包~~

开个结构体，然后按价格排序一遍。
然后用所有的钱尽多的买便宜的

如果能买，就加上高兴地奶牛
否则，就尽量多的买


#### 打上代码


```
#include<bits/stdc++.h>
#define MAXN 100010
#define Ull unsigned long long
using namespace std;
Ull n,m,ans=0;
struct node{
	Ull p,c;
}a[MAXN];
bool cmp(const node x,const node y)
{
	if(x.p==y.p)return x.c>y.c;
	return x.p<y.p;
}
int main()
{
	scanf("%llu%llu",&n,&m);
	for(int i=1;i<=n;i++)scanf("%llu%llu",&a[i].p,&a[i].c);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		if(m>=a[i].p*a[i].c)
		{
			m-=a[i].p*a[i].c;
			ans+=a[i].c;
		}
		else
		{
			ans+=m/a[i].p;
			m-=(m/a[i].p*a[i].p);
		}
	}
	printf("%llu\n",ans);
	return 0;
}
```


---

## 作者：EarthGiao (赞：0)

## 【思路】
贪心   
小水题   

### 【题目大意】
很多巧克力，很多奶牛    
奶牛都有自己喜欢的巧克力   
巧克力都有不同的价格   
你有b多的钱    
求最多满足的奶牛数      
（这是自己总结的意思，和真正的题目大意不太一样，   
这样总结的理由在后面）     

### 【题目分析】
可以这样看    
每满足一头奶牛都要消耗不同的钱   
想要满足最多的奶牛    
那一定是要找最便宜的去满足   
这就是贪心思想     
 
### 【最终思路】
知道了怎么贪心    
但是题目中给出的是巧克力的价格和喜欢这个巧克力的奶牛的数量   
这里的贪心和奶牛的数量没有关系    
因为理由可以看成【题目大意】分解之后的题意+【题目分析】里面的解释   
然后结构体根据巧克力的价格来排序   
从小到大枚举    
看看最多能够满足多少奶牛就可以啦     

## 【注意】
一道秒切的小水题   
但是需要开unsigned long long     
我是一步一步从int->long long -> unsigned long long 变化过来的     
## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm> 
#define int unsigned long long 
using namespace std;
const int Max = 100005;
struct node
{
	int p,c;
}a[Max];

bool cmp(const node x,const node y)
{
	return x.p < y.p;
}

signed main()
{
	int n,b;
	cin >> n >> b;
	for(register int i = 1;i <= n;++ i)
		cin >> a[i].p >> a[i].c;
	sort(a + 1,a + 1 + n,cmp);
	int js = 0;
	for(register int i = 1;i <= n;++ i)
	{
		if(b >= a[i].p * a[i].c)
			b -= a[i].p * a[i].c,js += a[i].c;
		else
		{
			js += b / a[i].p;
			break;
		}
	}
	cout << js << endl;
	return 0;
}
```

---

## 作者：冰桨 (赞：0)

这道题直接将花费从小到大排一下，然后满足小的，直到剩余的钱再也不能买东西为止，注意要开long long。

~~吐槽一下，被标签害惨了，想背包想了一节课~~
```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1010101;
long long n,b,ans;
struct node{
	long long p,c;
	bool operator<(const node&a)const {
	return p<a.p;
	}
}e[N];
int main(){
	scanf("%lld%lld",&n,&b);
	for(int i=1;i<=n;i++)
	scanf("%lld%lld",&e[i].p,&e[i].c);
	sort(e+1,e+n+1);
	for(int i=1;i<=n;i++){
		if(b/e[i].p>=e[i].c){
			ans+=e[i].c;
			b-=e[i].c*e[i].p;
		}
		else{
			ans+=b/e[i].p;
			b=0;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```



---


# [USACO2.1] 健康的荷斯坦奶牛 Healthy Holsteins

## 题目描述

农民 John 以拥有世界上最健康的奶牛为傲。他知道每种饲料中所包含的牛所需的最低的维他命量是多少。请你帮助农夫喂养他的牛，以保持它们的健康，使喂给牛的饲料的种数最少。

给出牛所需的最低的维他命量，输出喂给牛需要哪些种类的饲料，且所需的饲料剂量最少。

维他命量以整数表示，每种饲料最多只能对牛使用一次，数据保证存在解。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le v \le 25$，$1\le g \le 15$。  
输入的所有整数在 $[1,1000]$ 范围内。

USACO 2.1

翻译来自NOCOW


## 样例 #1

### 输入

```
4
100 200 300 400
3
50  50  50  50
200 300 200 300
900 150 389 399```

### 输出

```
2 1 3
```

# 题解

## 作者：06ray (赞：146)

这道题算是很简单的dfs，都不需要剪枝。

首先定义一个搜索函数，函数传递的变量为t和s,t表示搜索到了第t种饲料，s表示目前选的饲料的总数。

然后确定搜索的边界，也就是t>饲料的种数，然后判断每次选的那些饲料中的维生素之和是不是都大于等于牛每天需要的每种维他命的最小量（可以用个函数写）。如果是，就判断选的饲料的总数小于以前的最优解（类似于打擂台的那种操作），如果小于，那么当前最优解就要被替换掉，而最优解的一个数组也要被替换掉。最后return即可。

接着开始写函数的主体部分。首先我们选第t种饲料，那么s就要加一，并且我们还要把t存在一个数组当中（想想为什么要存）。然后就可以调用函数，即search(t+1,s+1);  调完函数后，记得要回溯.把t从数组中拿走。接下来我们不选第t种饲料，这样做很简单，直接搜索一步：search(t+1,s); 就行了。

最后输出解即可。

思路就这么多。

下面是代码部分。

# 请勿抄袭！！！

```cpp
#include <bits/stdc++.h>//懒人最爱的万能头文件 
using namespace std;//名字空间 
int ans[1000];//这个数组是来存储解的。 
int a[1000];//表示牛每天需要的每种维他命的最小量。 
int b[1000][1000];//每种饲料包含的各种维他命的量的多少。
int c[1000];//每次搜索选的饲料编号 
int n,m,minn=100000000;
bool pd(int x)//这是判断每次选的那些饲料中的维生素之和是不是都大于等于牛每天需要的每种维他命的最小量的函数 
{
	for(int i=1; i<=n; i++)
	{
		int sum=0;
		for(int j=1; j<=x; j++)
		sum+=b[c[j]][i];//用一个sum累加 
		if(sum<a[i]) return false;//如果有一项维生素比牛需要的维生素要少，直接返回false 
	}
	return true;
}
void search(int t,int s)//搜索的函数 
{
	if(t>m)//边界
	{
		if(pd(s))//必须得满足条件
		{
			if(s<minn)//判断选的饲料的总数小于以前的最优解
			{
				minn=s;//替换掉
				for(int i=1; i<=minn; i++)
				{
					ans[i]=c[i];//答案的数组也要被替换
				}
			}
		}
		return; //返回
	}
	c[s+1]=t;//把t放在数组里
	search(t+1,s+1);//搜索一步
	c[s+1]=0;//回溯一步
	search(t+1,s);//如果不选第t种饲料的操作
}
int main()//主函数部分
{
	cin>>n;//读入
	for(int i=1; i<=n; i++)
	cin>>a[i];//读入
	cin>>m;//读入
	for(int i=1; i<=m; i++)
	{
		for(int j=1; j<=n; j++)
		cin>>b[i][j];//还是读入
	}
	search(1,0);//调用搜索函数
	cout<<minn<<' ';//输出
	for(int i=1; i<=minn; i++)
	cout<<ans[i]<<' ';//还是输出
	return 0;//结束程序
}
```




---

## 作者：In_blue (赞：73)

看了半天，结果发现大佬们用的都是dfs，好奇的我于是打了一个bfs，后来调试调了半天，终于AC。

思路说明：

	1、定义队列，类型为结构体，结构体内一共一个变量，两个数组，分别保存饲料个数、饲料编号和饲料内维生素含量之和；
    
	2、先将所有类型的饲料放入队列，因为有可能其中一种饲料就可以满足所有的奶牛；

	3、进入循环，循环内判断队首元素是否满足，若满足输出再结束函数即可，否则再从此元素加上此元素最后一种饲料+1开始的所有饲料的和，并保存饲料的序号，饲料数+1，最后再放入队尾；
    
以下是代码

```
#include<iostream>
#include<queue>
using namespace std;
int a[30][30],b[30];
int n,m;
struct node{
	int wss[30];
	int num[30];
	int ans;
}q;
void bfs()
{
	queue<node>que;
	q=que.front();
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
			q.wss[j]=a[i][j];
		q.num[1]=i;
		q.ans=1;
		que.push(q);
	}
	while(!que.empty())
	{
		node s,t;
		s=que.front();
		t=que.front();
		que.pop();
		bool w=1;
		for(int i=1;i<=n;i++)
		{
			if(s.wss[i]<b[i])
			{
				w=0;
				break;
			}
		}
		if(w==1)
		{
			cout<<s.ans<<' ';
			for(int i=1;i<=s.ans;i++)cout<<s.num[i]<<" ";
			return;
		}
		for(int i=s.num[s.ans]+1;i<=m;i++)
		{
			for(int j=1;j<=n;j++)
				t.wss[j]=s.wss[j]+a[i][j];
			t.ans=s.ans+1;
			t.num[t.ans]=i;
			que.push(t);
		}
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>b[i];
	cin>>m;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	bfs();
	return 0;
}
```
求过QAQ

---

## 作者：tmp27 (赞：39)

这道题的方法很多，我很菜，就只给大家来个$dfs$。       
写$dfs$最重要的是你得有个结束条件（要不然你写了很长的代码一运行——死循环。）这里的接数条件很容易想到就是牛满足了他的维他命，通俗一点说就是喂饱了牛。          
然后就很简单了，直接枚举！（简单粗暴）。       
接着我们来看代码：

```
#include<iostream>//头文件
using namespace std;//空间命名。
int f,nfeed[30],type,t[30][30],m=20,mx[30],ans[30];//定义
bool cz(int x)
{
	for(int i=1;i<=f;i++)
	{
		int he=0; //别忘了初始化！！！
		for(int j=1;j<=x;j++)
		{
			he+=t[ans[j]][i];//累加
		}
		if(he<nfeed[i]) return false;//一旦没喂饱就赶紧跳的
	}
	return true;//喂饱了。
}
void dfs(int pos,int z)
{
	if(pos>type)//搜完了，不管它成功不成功我都要结束了，否则就会死循环。
	{
		if(cz(z) && z<m)//成功了
		{
			m=z;
			for(int i=1;i<=z;i++)
			{
				mx[i]=ans[i];//复制
			}
		}
		return ;//快给我结束！
	}
	ans[z+1]=pos;
	dfs(pos+1,z+1);//继续搜索
	dfs(pos+1,z);//继续搜索
   //是不是感觉很像动归！
}
int main()
{
	cin>>f;//读入奶牛需要的维他命的种类数。
	for(int i=1;i<=f;i++)
		cin>>nfeed[i];//读入牛每天需要的每种维他命的最小量。
	cin>>type;//读入可用来喂牛的饲料的种数。
	for(int i=1;i<=type;i++)
	{
		for(int j=1;j<=f;j++)
		{
			cin>>t[i][j];饲料包含的各种维他命的量的多少。
		} 
	}
	dfs(1,0);//爆搜！
	cout<<m<<" ";//输出
	for(int i=1;i<=m;i++)
		cout<<mx[i]<<" ";//输出
	cout<<endl;//输出
	return 0;
}
```


---

## 作者：Youngsc (赞：26)

[Youngsc](http://youngscc.github.io/)

来一波迭代加深的代码。。

之前被退回来说我说明太少。然而我想说一波搜索我也没什么好说的呀。。。

因为题目中要求饲料越少越好，所以我们可以借助迭代加深的思想，先限制每一次搜索的深度，搜到一定的深度就返回，即每一次选择的饲料数量，选择了足够的饲料就返回，然后判断是否存在一种这样数量的组合，满足题目条件，这样的话能把最优解放搜在前边，不需要任何的剪枝就能AC。


### 代码在这里


PS: 29行有一个判断返回是一个剪枝，就是说如果剩下的不够我要选择的数量了，那么我就返回，由于数据比较水，所以可有可无。


```cpp
# include <algorithm>
# include <iostream>
# include <cstring>
# include <cstdio>
# include <cmath>
# define R register
# define LL long long

using namespace std;

int n,m,vc[30],c[20][30],a[30];
bool v[20];

inline void in(R int &a){
    R char c = getchar();R int x=0,f=1;
    while(!isdigit(c)){if(c == '-') f=-1; c=getchar();}
    while(isdigit(c)) x = (x<<1)+(x<<3)+c-'0',c = getchar();
    a = x*f;
}

inline void dfs(R int x,R int sum,R int num){ //num就是迭代加深的限制条件
    if(sum == num)//判断边界条件
    {
        for(R int i=1; i<=m; ++i) if(a[i] < vc[i]) return;
        cout << num << ' ';
        for(R int i=1; i<=n; ++i) if(v[i]) cout << i << ' ';
        exit(0);//直接在函数中结束程序
    }
    if(n-x<num-sum) return;//所谓可有可无的剪枝。
    for(R int i=x+1; i<=n; ++i)
    {
        v[i] = 1;
        for(R int j=1; j<=m; ++j) a[j] += c[i][j];
        dfs(i,sum+1,num);
        for(R int j=1; j<=m; ++j) a[j] -= c[i][j];
        v[i] = 0;//回溯
    }
}

inline int yg(){
    in(m);
    for(R int i=1; i<=m; ++i) in(vc[i]);
    in(n);
    for(R int i=1; i<=n; ++i)
        for(R int j=1; j<=m; ++j) in(c[i][j]);
    for(R int i=1; i<=n; ++i) dfs(0,0,i);//枚举迭代加深的不同深度。
    return 0;
}

int youngsc = yg();
int main(){;}

```

---

## 作者：_Andrea (赞：25)

很简单的一道DFS，但是居然写了我一整个晚自习？？？

于是心血来潮写了蒟蒻人生第一篇题解

反正有很多细节要注意

具体看注释叭
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
using namespace std;
#define INF 0x3f3f3f3f
#define N 100
int v, g, minn = INF, lenth;//v,g如题，minn存答案长度，lenth存当前长度
int vet[N], food[N][N], save[N], ans[N];//vet存每种维生素最少需要量，food存每种食物可以提供维生素的多少，save存已经选择的饲料，ans存答案选择c的饲料种类
bool vis[N];//标记
bool check(int lenth){//判断当前是否已经满足牛牛维生素的需求量
    int niu[N];
    memset(niu, 0, sizeof(niu));//一定要初始化，我因为没有初始化卡了好久！！！
    for(int i = 1; i <= lenth; i ++){
        for(int l = 1; l <= v; l ++)
            niu[l] += food[save[i]][l];//存食物提供给牛牛的维生素
    }
    for(int i = 1; i <= v; i++){
        if(niu[i] < vet[i])    return false;//如果有一种维生素不够就返回false
    }
    return true;//每种维生素都够了就返回true
}
void dfs(){
    if(lenth > g || lenth > minn)    return;//剪枝优化m，如果选择的饲料种类超过了一共有的饲料种类，或是选择的种类已经超过了之前的最优解
    if(check(lenth) == true){//如果满足了每种维生素的需求量
        if(minn > lenth){//如果当前解最优
            minn = lenth;
            for(int i = 1; i <= minn; i ++)
                ans[i] = save[i];//存储答案
        }
        return;//结束
    }
    int start = save[lenth]; //从上一步选择的饲料开始选择，可以避免出现1，2，3和3，2，1的情况，特别重要，不然会T两个点
    if(start == 0)  start = 0;
    for(int i = start; i <= g; i ++){//枚举选择的饲料种类
        if(vis[i] == false){//如果未被选择过
            vis[i] = true;//标记已被选择
            lenth ++;//答案长度++
            save[lenth] = i;//存储答案
            dfs();//递归进行下一次选择
            vis[i] = false;//回溯时还原
            save[lenth] = 0;
            lenth --;
        }
    }
}
int main(){
    scanf("%d", &v);
    for(int i = 1; i <= v; i ++)
        scanf("%d", &vet[i]);
    scanf("%d", &g);
    for(int i = 1; i <= g; i ++)
        for(int l = 1; l <= v; l ++)
            scanf("%d", &food[i][l]);//输入
    dfs();
    printf("%d ", minn);
    for(int i = 1; i <= minn; i ++)
        printf("%d ", ans[i]);//输出
    return 0;
}

```


---

## 作者：「QQ红包」 (赞：17)

题解by：[redbag](http://www.luogu.org/space/show?uid=2674)

原题解地址：[http://redbag.duapp.com/?p=1160](http://redbag.duapp.com/?p=1160)

ac记录：[http://www.luogu.org/record/show?rid=779120](http://www.luogu.org/record/show?rid=779120)

原题地址：[http://www.luogu.org/problem/show?pid=1460](http://www.luogu.org/problem/show?pid=1460)


这道题我开始纠结了很久是用dfs还是用bfs呢，但是由于结果要求如果有多种情况，就输出字典序最小的，这样子dfs就会比较方便，就会省很多判断。总的来说这是简单的搜索。


/\*
ID: ylx14274

PROG: holstein

LANG: C++

\*/
```cpp
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int vv;//维他命种类 
int v[26];//每种所需数量 
int n;//喂牛的饲料种类数
int a[16][26];//每种饲料每种维他命含量
int w[26];//存最小需要饲料的方案 
int p,mm,he;//存需吃的种类的数量 
int c[26];//c[i]标记吃不吃第i种饲料，1为吃 
int pd()
{
    for (int i=1;i<=vv;i++) 
    if (v[i]>0) return 0;//不符合条件
    return 1; 
}
int pr()
{
    if (p<mm)//这种方案需要的饲料种类更少
    //由于搜索保证了先搜到的字典序会小，所以不需比较p=min的情况
    {
        he=0;
        mm=p;
        for (int i=1;i<=n;i++)
        if (c[i]==1)
        {
            he++;
            w[he]=i;
        }
    } 
}
void dfs(int t)
{
    if (pd()==1)//牛吃这些能满足所需维他命的最小量 
    {pr();return;}
    if (t>n)//每种饲料都选过了 
    {return;} 
    ////吃第t种饲料
    for (int i=1;i<=vv;i++)
    {
        v[i]-=a[t][i];//标记 
    }
    c[t]=1;//标记吃第t种饲料 
    p++; 
    dfs(t+1); 
    for (int i=1;i<=vv;i++)
    {
        v[i]+=a[t][i];//还原标记 
    }
    c[t]=0;//还原标记 
    p--; 
    ////不吃第t种饲料
    dfs(t+1); 
}
int main() 
{
    mm=23333;
    freopen("holstein.in","r",stdin);
    freopen("holstein.out","w",stdout); 
    scanf("%d",&vv);//读入需要的维他命总数 
    for (int i=1;i<=vv;i++) scanf("%d",&v[i]);//读入牛所需的维他命量 
    scanf("%d",&n);//读入喂牛的饲料种数 
    for (int i=1;i<=n;i++)//读入编号i所包含的各种维他命量 
        for (int j=1;j<=vv;j++)
        scanf("%d",&a[i][j]);
    dfs(1);
    printf("%d",mm);
    for (int i=1;i<=mm;i++)
        printf(" %d",w[i]);
    printf("\n");
    return 0;
}
```

---

## 作者：ouuan (赞：13)

下面那篇二进制枚举子集题解被我叉了！~~我第一次交的代码也被自己叉了~~

### 整体思路

因为每种饲料只有选或不选两种状态，所以可以用二进制枚举子集，共2^g个子集，每种子集需要gv的时间判断是否合法，所以时间复杂度是gv*2^g，因为这题数据很小，可以过。

### 字典序的保证

考虑用二进制来枚举子集，右数第i位为0代表不选饲料g+1-i（这里比较特殊，原因待会儿说），为1代表选饲料g+1-i，选的饲料个数就是1的数量，那么从2^g-1枚举到0，第一个遇到的最优解即为字典序最小的。因为：（这里可以自己想清楚，证明感觉略繁琐）
- 假设有两个最优解a和b（a的字典序小于b），它们都有x个1
- 从二进制表示中比较方案的字典序即比较：
	1. 若a的左数第一个1比b的左数第一个1靠左则a的字典序大，反之b的字典序大
    2. 若位置一样，则比较左数第二个1的位置
    3. 继续比较，直至不同
- 可以看出，在a的字典序小于b时，a本身是大于b的，即a先于b被枚举到

为什么要用第i位表示选不选饲料g+1-i而不是饲料i呢？因为二进制枚举的时候是固定高位不变先变低位，只有把编号小的饲料放在二进制的高位上才能保证第一个遇到的解是字典序最小的

### 数饲料个数

第一个遇到只能保证字典序小，不能保证饲料个数少，所以还要数饲料的个数

数饲料个数就是在二进制表示中数1的个数，代码如下：

```
int count(int x)
{
	int out=0;
	while (x)
	{
		out+=x&1;
		x>>=1;
	}
	return out;
}
```

### 完整代码

```
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int v,need[30],g,a[20][30],ans,minn=0x7fffffff,t[30];

int count(int x);

int main()
{
    int i,j,k;
    bool flag;
    
    cin>>v;
    
    for (i=0;i<v;++i)
    {
        cin>>need[i];
    }
    
    cin>>g;
    
    for (i=1;i<=g;++i)
    {
        for (j=0;j<v;++j)
        {
            cin>>a[i][j];
        }
    }
    
    for (i=(1<<g)-1;i>=0;--i) //二进制枚举子集
    {
        if (count(i)<minn) //若当前子集的饲料数大于等于当前的最优解则当前子集一定不是答案
        {
            memset(t,0,sizeof(t));
            for (j=0;j<g;++j)
            {
                if ((1<<j)&i) //i的右数第j+1位为1代表饲料g-j在当前枚举的子集中
                {
                    for (k=0;k<v;++k)
                    {
                        t[k]+=a[g-j][k];
                    }
                }
            }
            flag=true;
            for (j=0;j<v;++j) //判断当前方案是否合法
            {
                if (t[j]<need[j])
                {
                    flag=false;
                    break;
                }
            }
            if (flag) //因为已经判断过当前子集饲料数小于当前最优解，若当前方案合法则直接更新最优解
            {
                minn=count(i);
                ans=i;
            }
        }
    }
    
    cout<<minn;
    
    for (i=g-1;i>=0;--i) //输出方案
    {
        if ((1<<i)&ans)
        {
            cout<<" "<<g-i;
        }
    }
    
    return 0;
}

int count(int x) //数1的个数
{
    int out=0;
    while (x)
    {
        out+=x&1;
        x>>=1;
    }
    return out;
}
```

---

## 作者：封禁用户 (赞：12)

此题我用的疯狂的bfs，用位运算记录状态（就是选了哪种饲料，对应位置1），我们暴力枚举所有的饲料（因为每种饲料都有可能是第一个被选取的），然后分别让他们为起点bfs，最后找出一个数目最小且最先出现的方案。

代码如下：

```cpp
    #include<iostream>
    #include<cstdio>
    #include<queue>
    #include<cstring>
    using namespace std;
    int zuixiao[30];//最小维生素
    int v[30][30];//各种饲料的维生素
    int tmps[30];
    int main(){
        int vs;
        cin>>vs;
        for(int i=0;i<vs;i++)cin>>zuixiao[i];
        int n;
        cin>>n;
        for(int i=0;i<n;i++){
            for(int j=0;j<vs;j++){
                cin>>v[i][j];
            }
        }
        unsigned int best;//最优的方案，按位存储
        int minn=0x7fffffff;//最小的数目
        for(int i=0;i<n;i++){//暴力枚举以每个饲料为起点的bfs
            for(int j=0;j<vs;j++){
                if(v[i][j]<zuixiao[j])goto lcd;
            }
            printf("1 %d",i+1);//如果一种就可满足需求，直接输出这一种
            return(0);
```
lcd:
```cpp
            queue<int> steps;//存储步数的队列
            queue<unsigned int> que;//存储状态位的队列
            queue<int> lasts;//存储最后一个选了哪个的队列
            que.push(1<<i);
            lasts.push(i);
            steps.push(1);
            do{
                unsigned int flags=que.front();
                int step=steps.front();
                int last=lasts.front();
                que.pop();
                lasts.pop();
                steps.pop();
                for(int j=last+1;j<n;j++){
                    unsigned int nf=flags|(1<<j);//标记这个饲料
                    for(int k=0;k<vs;k++){
                        tmps[k]=v[j][k];
                    }
                    for(int k=0;k<n;k++){
                        if(flags&(1<<k)){
                            for(int l=0;l<vs;l++){
                                tmps[l]+=v[k][l];
                            }
                        }
                    }
                    for(int k=0;k<vs;k++){
                        if(tmps[k]<zuixiao[k])goto g;  
                    }
                    if(step+1<minn){//维生素已经满足最小需求，而且数目也更小
                        minn=step+1;
                        best=nf;
                    }
                    goto jh;
```
g:
```cpp
                    que.push(nf);
                    lasts.push(j);
                    steps.push(step+1);
                }
            }while(!que.empty());
            jh:int zyc;
        }
        printf("%d",minn);
        for(int i=0;i<n;i++){
            if(best&(1<<i)){
                printf(" %d",i+1);//输出按位存储的方案
            }
        }
        return(0);
}
```

---

## 作者：小白四个白 (赞：5)

```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define mem(x) memset(x,0,sizeof(x)) //偷懒而已 
short int v,g,p=50; //short int 节省空间 【这道题其实没必要】 
short int need[30],food[20][30];

struct node{
    bool chos[20]; //chos[i] -> 第i种饲料是否被选 
    short int now[30],sum,cnt; //now[i] -> 当前第i种维他命的数量; sum->状压用的; cnt->当前选了的饲料种数; 
    void init(){ //初始化
        mem(chos);
        mem(now);
        sum=cnt=0;
    }
    void add(bool t,int k){ //确认第k种饲料是否使用 
        cnt+=t; //如果选了，cnt++ 
        sum=(sum<<1)|(chos[k]=t); //更新sum值 和 chos[k] 
        if(t) for(int i=1;i<=v;i++) now[i]+=food[k][i]; //如果选择使用，更新当前维他命数 
    }
    bool pd(){ //判断是否符合题意 
        for(int i=1;i<=v;i++) if(now[i]<need[i]) return false; //只要有一个不够就直接返回 
        return true;
    }
}ans;

void dfs(node now,int k){
    if(now.pd()){//任何时候到了都可以直接停下了 
        if(now.cnt<ans.cnt) ans=now; //优先考虑种数大小 
        if(k<g) now.sum<<=(g-k); //有可能还没有运行到第g层，把sum后面的值加上以免下一行比较的时候发生错误 
        if(now.cnt==ans.cnt && now.sum<ans.sum) //可以证明状压之后的sum的大小关系等价于字典序的大小关系 
        return;
    }
    if(k==g+1) return;
    node next1=now,next2=now; //创建两个新的，也可以在原本的上面改
    next1.add(true,k);//选当前的第k种饲料 
    dfs(next1,k+1);//dfs过程 
    next2.add(false,k);//不选 
    dfs(next2,k+1);//dfs过程 
    return;
}

void scan(){
    mem(need); //初始化 
    mem(food); //初始化 
    cin.sync_with_stdio(false); //优化 cin 读入速度  【这道题其实也没必要】 
    cin>>v;
    for(int i=1;i<=v;i++) cin>>need[i];
    cin>>g;
    for(int i=1;i<=g;i++) for(int j=1;j<=v;j++) cin>>food[i][j];
}

void print(){
    cout<<ans.cnt; //输入选了的饲料的种数 
    for(int i=1;i<=g;i++) if(ans.chos[i]) cout<<" "<<i; //输出每个被选的饲料的序号 
    putchar('\n'); //习惯性换行 
    return;
}

void Healthy_Holsteins(){
    scan(); //输入 
    node start; //创建空结构体 
    start.init(); //初始化一下以免出问题 
    ans.cnt=g+2;  //把ans初始化超过最大值 
    dfs(start,0); //深度优先搜索 
    print(); //输出 
    return; 
}
int main(){
    Healthy_Holsteins();
    return 0; //结束 
}
```

---

## 作者：zengqinyi (赞：5)

遇到这个题，既然有多重维生素需要达标，那么贪心就是不可能的了，于是就想到搜索。


因为要以字典序排序，就想到DFS，因为由于DFS的性质,搜索出来的第一个最优解则是字典序最小的


如果暴力搜索的话，会TLE2~3个点，那么这时候就要考虑一些剪枝了。


1、最优性剪枝：如果当前使用的维生素超过已有答案或使用的维生素超过维生素总类，则剪枝


2、如果要使用1 2 3 4 5这5种维生素时，可能会有5 4 3 2 1等重复搜索，浪费时间，所以就可以从当前使用的最大数开始枚举，搜索


附上代码：


（PS：自动忽略“inline”、“register”等字样，据说是有加速效果的，但好像已被证伪，只是本人习惯打而已）


```cpp
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cstdio>
using namespace std;
#define rint register int//此代码中所有的“rint”即为“register int”，但可以自动忽略register
inline void read(int &x)//读入优化
{
    x=0;int w=1;char ch=getchar();
    while(!isdigit(ch)&&ch!='-')ch=getchar();
    if(ch=='-')w=-1,ch=getchar();
    while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^'0'),ch=getchar();
    x=x*w;
}
const int maxn=30,maxm=20;
int n,m,vita[maxn],food[maxm][maxn],a[maxn]={0},e=0,A[maxm],ans=maxm,ansA[maxm];
//n为维生素数量，m为饲料数量，vita[]表示所需的维生素，a表示当前的维生素总量
//e表示目前使用的维生素个数，A[]存储目前使用的维生素种类，ans、ansA[]为答案
bool vis[maxn]={0},flag=0;
//vis[]表示是否使用过，flag表示是否为答案
inline bool judge()//判定方案是否可行
{
    for(rint i=1;i<=n;i++)
        if(a[i]<vita[i])
            return false;//有一种维生素不达标就不行
    return true;//每种都达标则可以
}
inline void dfs()
{
    if(e>ans||e>m)return;
    //最优性剪枝：如果使用的维生素超过已有答案或使用的维生素超过维生素总类，则剪枝
    flag=judge();//评判此方案是否可行
    if(flag)//如果可行
    {
        if(e<ans)//如果答案比之前的更小
        {
            ans=e;
            for(rint i=1;i<=e;i++)ansA[i]=A[i];
            flag=0;
            //则将此答案赋值给最终答案吗，再将此flag标记为0，继续搜索下一个答案
        }
        return;
    }
    int k=A[e];
    if(k==0)k=1;
    for(rint i=k;i<=m;i++)//从当前使用的最后一种维生素开始寻找（否则1 2 3 4 5和5 4 3 2 1会重复计算）
    {
        if(vis[i]==0)//如果没有被使用
        {
            vis[i]=1;
            A[++e]=i;
            for(rint j=1;j<=n;j++)a[j]+=food[i][j];
            //将此种维生素使用并继续搜索
            dfs();
            for(rint j=1;j<=n;j++)a[j]-=food[i][j];
            vis[i]=0;
            e--;
            //再标记回来
        }
    }
}
int main()
{
    read(n);
    for(rint i=1;i<=n;i++)read(vita[i]);
    read(m);
    for(rint i=1;i<=m;i++)
        for(rint j=1;j<=n;j++)
            read(food[i][j]);
    //读入
    dfs();
    printf("%d",ans);
    for(rint i=1;i<=ans;i++)printf(" %d",ansA[i]);
    //输出答案
    return 0; 
}
```

---

## 作者：撤云 (赞：2)

这一道题第一眼看起来认为是动态规划，其实一个dfs就可以解决

代码如下：

```cpp
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
using namespace std;
int a[26][26],b[26];
int bj[26],js=2147483,ko=1,n,m;
char s[100],l[100];
int pd() { 
    for(int i=1; i<=n; i++)
        if(bj[i]<b[i])//判断是不是维生素大于牛所需的最低的维他命 
            return 0;//如果不是返回0 
    return 1;//如果是返回1 
}
void dfs(int k,int ans) {
    if(pd()==1) {//如果 维生素大于牛所需的最低的维他命 
        if(js>ans) {//如果当前最小值大于本次的值 
            for(int i=1; i<=m; i++)
                l[i]=s[i];//把s数组的值赋给l数组 
        }
        js=min(js,ans);//取js和ans中的最小值 
        return ;//返回 
    }
    for(int i=k+1; i<=m; i++) {
        for(int j=1; j<=n; j++)
            bj[j]+=a[i][j];
        s[i]='1';//表记i说明i点别被选过 
        dfs(i,ans+1);//搜索 
        for(int j=1; j<=n; j++)
            bj[j]=bj[j]-a[i][j];
        s[i]='0';//讲i的表记清空 
    }
}
int main() {
    cin>>n;//输入 
    for(int i=1; i<=n; i++)
        cin>>b[i];
    cin>>m;
    for(int i=1; i<=m; i++)
        for(int j=1; j<=n; j++)
            cin>>a[i][j];
    for(int ii=1; ii<=m; ii++) {
        memset(s,0,sizeof(s));//把s数组的值清空 
        s[ii]='1';//表记ii 
        memset(bj,0,sizeof(bj));//把bj数组清空 
        for(int j=1; j<=n; j++)
            bj[j]=a[ii][j]; 
        dfs(ii,1);//搜索 
    }
    cout<<js<<" ";
    for(int i=1; i<=m; i++) {
        if(l[i]=='1')//如果点i被标记过 
            cout<<i<<" ";//输出 
    }
    return 0;
}
```

---

## 作者：VanillaYuzume (赞：2)



------------
void dfs(int x){

    if(满足输出条件){
        输出解;
    }
    else{
        for(int i=1;i<=尝试方法数;i++)
            if(满足进一步搜索条件){
                为进一步搜索所需要的状态打上标记;
               dfs(x+1);
                恢复到打标记前的状态;//也就是说的{回溯}
        }
    }
}
参考用dfs模板

解题思路：因为食物数量及所需维他命种类很少 所以使用dfs来解题

核心思想：从第一组食物的第一个数开始枚举出当前一种食物中所含的各维他命值
然后用需求减去每种维他命值...从所有可行方案中找出最小解 

**献上代码**

-----------

```cpp
#include <cstdio>

int V,G;//v需要的维他命的种类数,G可用的食物的种数

int a[30];//存牛每天需要的每种维他命的最小量

int Y[30][30];//编号为n食物包含的各种维他命的量的多少

int book[20];//记录尝试过的食物

int m=1000000,min1;//记录使用最小食物种类

int ans[20];//输出方案


void flag(){//每次尝试一种后 记录尝试的食物
	
    int tmp=0;
    for(int i=1;i<=G;i++)
        if(book[i]==1)//
            ans[++tmp]=i;//记录答案
}

//检测 牛所需的每种维他命量 是否满足 有-->true 没-->false

bool check(){

    for(int i=1; i<=V;i++)
        if(a[i]>0)
            return false;
    return true;
}

//深搜...
void dfs(int x){

	
    //判断是否满足牛所需的每种维他命量,满足后继续
    
	if(check()){
    
        //记录使用最小食物种类,及 比较最小的输出方案
		if(min1<m){
            m=min1;
            flag();//调用flag()记录使用最小食物种类
            return;
        }
    }
	
	//当可用食物种数<1时，跳出函数
    if(x>G) 
        return;
    
	//二维数组第一个下标(1,1)开始读,及 每种食物中维他命含量的第一个值
	for(int i=1;i<=V;i++)
        a[i]-=Y[x][i];//每次读取一个后牛所需的维他命量减少
        book[x]=1;//标记已读取过的
        min1++;//更新min1的值
        dfs(x+1);
	//回溯到初始状态...
    for(int i=1;i<=V;i++)
        a[i]+=Y[x][i];
    book[x]=0;
    min1--;
    dfs(x+1);
}

int main(){

    scanf("%d", &V);
    for(int i=1;i<=V;i++)
        scanf("%d",&a[i]);
    scanf("%d",&G);
    for(int i=1;i<=G;i++)
        for(int j=1;j<=V;j++)
            scanf("%d",&Y[i][j]);
        dfs(1);//运行函数...输出最小使用食物种类及最小方案
    printf("%d ",m);
    for(int i=1;i<=m;i++)
        printf("%d ",ans[i]);
    return 0;
}
```


---

## 作者：Celebrate (赞：2)

这一题采用递归+剪枝来做

如果不懂递归的，赶紧去学一下P1706 全排列问题吧

代码如下：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
int d[310],f[310][310];
int a[310],b[310],cnt[310],min=999999999;
bool v[310];
inline bool pd()//判断是否可以供给奶牛足够的维他命 
{
	for(int i=1;i<=n;i++) if(cnt[i]<d[i]) return false;
	return true;
}
void dfs(int k,int s)//k表示当前的位置，s表示已经用了多少种饲料了 
{
	if(s>=min) return;//如果超过了最小值，那么肯定不是 
	if(pd()==true)//如果可以的话，就肯定是更优值了，前面已经排除过了 
	{
		min=s;//赋值，取最优值 
		for(int i=1;i<=min;i++) a[i]=b[i];
	}
	else if(k==m+1) return;//如果超过了上限，就不用管了 
	else
	{
		for(int i=k;i<=m;i++)//搜索 
		{
			if(v[i]==true)//如果没有被用过 
			{
				for(int j=1;j<=n;j++) cnt[j]+=f[i][j];//增加总数 
				b[s+1]=i;v[i]=false;//记录 
				dfs(i+1,s+1);//往下搜索 
				b[s+1]=0;v[i]=true;//回溯 
				for(int j=1;j<=n;j++) cnt[j]-=f[i][j];
			}
		}
	}
}
int main()
{
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&d[i]);//初始化 
	scanf("%d",&m);
	for(i=1;i<=m;i++) 
	{
		for(j=1;j<=n;j++) scanf("%d",&f[i][j]);
		v[i]=true;
	}
	dfs(1,0);printf("%d ",min);for(i=1;i<min;i++) printf("%d ",a[i]);//递归和输出 
	printf("%d\n",a[min]);return 0;//结束 
}
```

---

## 作者：lukelin (赞：2)

\* 这里主要用了一个状态压缩的技巧，用一个二进制数表示取不取该饲料

\* 下面是代码，变量含义如其名字

***
```cpp
#include <iostream> //我习惯用iostream，用cstdio的勿喷 
using namespace std;
const int MAX = (1 << 31) - 1; //一个很大的数 注：int最大为2^32,一半用于负数故最大值为2^31，直接平移31会爆炸导致出现负数，故需要-1 
int vita_min_need[26]; // 
int feeds_vita_content[16][26]; //表示饲料中所含的维他命数，第一维为饲料编号，第二维为饲料 
// vita_num表示维他命的种类数，feed_num表示饲料的种类数，都由输入得知 
int vita_num, feed_num;

//找到总共选取的饲料数，即改状态在二进制下数字1的数量
int cac_feed_num(int status)
{
    int feed_num = 0;//统计当前状态下的饲料总数 
    while (status > 0)
    {
        feed_num += status & 1; //巧妙利用位与操作算出当前状态在二进制下的当前位是否为1,如为1，表示选了当前饲料，饲料数+1 
        status >>= 1;//使用平移，比除法效率更高
    }
    return feed_num;
}

//判断一个状态是否符合要求
bool jud(int status)
{
    int tot_vitamin[26] = {0};
    int now_feed = 0, now_vitamin;
    while (status > 0) 
    {
        if (status & 1)
        {
            for (now_vitamin = 0; now_vitamin < vita_num; now_vitamin++)
                tot_vitamin[now_vitamin] += feeds_vita_content[now_feed][now_vitamin];
        }
        status >>= 1;
        now_feed++;
    }
    for (now_vitamin = 0; now_vitamin < vita_num; now_vitamin++)
        if (tot_vitamin[now_vitamin] < vita_min_need[now_vitamin])
            return false;
    return true;
}

void print_status(int status)
{
    int now_feed = 0;
    bool feed_using_situation[16] = {false};
    while (status > 0) 
    {
        if (status & 1)
            feed_using_situation[now_feed] = true;
        status >>= 1;
        now_feed++;
    }
    for (now_feed = 0; now_feed < feed_num; now_feed++)
        if (feed_using_situation[now_feed] == true)
            cout << (now_feed + 1) << ' ';
}

int main()
{
    //读入 
    cin >> vita_num;
    int i;
    for (i = 0; i < vita_num; i++)
        cin >> vita_min_need[i];
    cin >> feed_num;
    int j;
    for (i = 0; i < feed_num; i++)
        for (j = 0; j < vita_num; j++)
            cin >> feeds_vita_content[i][j];
    
    //以下代码遍历
    int max_choise = 1 << feed_num, min_c;
    int min_feed_num = MAX, min_status = 0, cur_feed_num, cur_status;
    for (cur_status = 1; cur_status < max_choise; cur_status++)
    {
        cur_feed_num = cac_feed_num(cur_status);
        //主要剪枝，如果它所需的饲料数大于最小所需饲料数，或相等但字典序大，它能否满足要求无关紧要，直接跳过
        if (cur_feed_num < min_feed_num || (cur_feed_num == min_feed_num && cur_status < min_status))
            if (jud(cur_status))
            {
                min_status = cur_status; //将最小状态置为当前状态
                min_feed_num = cur_feed_num; //将最小所需饲料的总数设置为当前所需饲料的总数 
            }
    }
    
    //打印 
    cout << min_feed_num << ' '; //打印最小所需饲料的总数 
    print_status(min_status); //将最小所需饲料总数对应的 
    return 0;
}
```

---

## 作者：远航之曲 (赞：2)

来一发题解

这题用的BFS结合位运算加速,并且用一个数组记录已计算过的前缀,很容易大幅度剪枝.而且一得到解就能返回,因为BFS最先找到的一定是最优解.


（减少代码复制，共创美好洛谷）


```cpp
#include <fstream>
#include <vector>
#include <deque>
using namespace std;
```
 
```cpp
static int type_of_vitamin;
static int type_of_feed;
static vector<int> vitamin;
static  vector< vector<int> > feeds;
```
 
```cpp
vector<int> GetMinFeed();
inline bool IsEnough(const vector<int> &feed);
inline vector<int> GetState(int feed);
inline void AddFeed(vector<int> &state, const vector<int> feed);
vector<int> BitToVector(int feed);
```
 
int main() {

  ifstream fin("holstein.in");

  ofstream fout("holstein.out");

 
```cpp
  fin >> type_of_vitamin;
  int v, counter = 0;
  while (counter++ < type_of_vitamin) {
    fin >> v;
    vitamin.push_back(v);
  }
```
 
```cpp
  fin >> type_of_feed;
  int g;
  counter = 0;
  vector<int> feed;
  while (fin >> g) {
    feed.push_back(g);
    ++counter;
    if (counter == type_of_vitamin) {
      feeds.push_back(feed);
      feed.clear();
      counter = 0;
    }
  }
```
 
```cpp
  vector<int> min_feed = GetMinFeed();
  fout << min_feed.size() << ' ';
  for (int i = 0; i < min_feed.size(); ++i) {
    fout << min_feed[i];
    if (i+1 < min_feed.size())
      fout << ' ';
  }
  fout << endl;
  return 0;
}
```
 
```cpp
vector<int> GetMinFeed() {
  vector<bool> is_searched(1 << type_of_feed + 1, false); // 记录饲料组合是否已被搜索到,最长2^15 + 1
  deque<int> q;
  int feed = 0, current_feed = 0;  // 用bit位来记录搜索到的饲料组合
  vector<int> state, current_state; // 记录饲料组合的维他命数
```
 
```cpp
  while (true) {
    if (!q.empty()) {
      feed = q.front();
      q.pop_front();
      state = GetState(feed);
    }
```
 
    for (int i = 0; i < type\_of\_feed; ++i) {

      current\_feed = feed;

      current\_state = state;

 
current\_feed |= (1 << i);  // 用或运算把当前的饲料加到原有的组合当中

// 如果或运算之后未变,则搜索到重复饲料, 若当前组合已访问, 则也可剪枝

      if (current\_feed == feed || is\_searched[current\_feed]) 
        continue;

 
```cpp
      is_searched[current_feed] = true;
      AddFeed(current_state, feeds[i]);
      if (IsEnough(current_state))
        return BitToVector(current_feed);
      else
        q.push_back(current_feed);
    }
  }
}
```
 
```cpp
inline bool IsEnough(const vector<int> &feed) {
  // 判断一个饲料组合是否满足需要
  if (feed.empty()) return false;
  for (int i = 0; i < type_of_vitamin; ++i)
    if (feed[i] < vitamin[i])
      return false;
  return true;
}
```
 
```cpp
inline vector<int> GetState(int feed) {
  // 从一个数取出二进制位并生成饲料组合及其维他命数
  vector<int> state;
  int bit = 0;
  while (feed) {
    if (feed & 1)
      AddFeed(state, feeds[bit]);
    ++bit;
    feed >>= 1;
  }
  return state;
}
```
 
inline void AddFeed(vector<int> &state, const vector<int> feed) {

// 将一个新的饲料加到原有的的饲料组合中并计算维他命数

```cpp
  if (state.empty()) {
    state = feed;
  } else {
    for (int i = 0; i < type_of_vitamin; ++i)
      state[i] += feed[i];
  }
}
```
 
```cpp
vector<int> BitToVector(int feed) {
  // 把一个二进制饲料组合转化成数组,用于最后输出
  vector<int> feeds;
  int bit = 0;
  while (feed) {
    if (feed & 1)
      feeds.push_back(bit + 1);
    ++bit;
    feed >>= 1;
  }
  return feeds;
}
```

---

## 作者：zqiceberg (赞：1)

```cpp

//求必须的最小饲料种数，从idx种开始往后遍历
//没找到一个可行的方案，对比一下是否种类数最小，最小就存起来
//最后输出ans，ansqueue[]

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

const int N = 30, M = 25;

int vita[N], vitatmp[N];   //vitatmp存当前的维生素的量，用来判断是否够用
int g[M][N];

int vitaqueue[M];
int ansqueue[M];     //用来存放饲料的序号
int ans = 0x3f;      //记录最小方案的维生素方案种数
int vis[M];          //是否使用过

int n, m;
int idx;

bool check()
{   
    for (int i = 1; i <= n; i++)
        if (vitatmp[i] < vita[i]) return false;
    
    return  true;
}

void dfs()
{
    //for (int i = 1; i <= idx; i++) printf("%d ", ansqueue[i]);
    //puts("");

	//这个地方不进行剪枝，数据也能过
    //if (idx > ans || idx > m) return;

    if (check())
    {
        //vitatmp够用，但是饲料种数不是最小，就剪枝
        if (idx >= ans) return ;

        //暴力搜索，会不断刷新出来优化的方案，存起来
        ans = idx;
        for (int i = 1; i <= ans; i++) ansqueue[i] = vitaqueue[i];

        //for (int i = 1; i <= ans; i++) printf("%d ", ansqueue[i]);
        //puts("");
    }
    //如果当前vitatmp还不够用，需要继续去找

   for (int i = vitaqueue[idx]; i <= m; i++)
    {
        if (i >= 1 && !vis[i])
        {
            vis[i] = 1;
            vitaqueue[++idx] = i;
            for (int j = 1; j <= n; j++) vitatmp[j] += g[i][j];

            dfs();
   
            for (int j = 1; j <= n; j++) vitatmp[j] -= g[i][j];   //j<=n 打成i<=n，调试3小时，溺, bus error 10
            idx--;
            vis[i] = 0;
        }
    }

    return ;
}


int main()
{
    //freopen("P1460_2.in", "r", stdin);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> vita[i];   //vita[]存所需vita标准值

    cin >> m;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> g[i][j];

    dfs();

    printf("%d ", ans);
    for (int i = 1; i <= ans; i++) printf("%d ", ansqueue[i]);
    puts("");

    return 0;
}

```

### 总结一下：
dfs真香

很多题解用的类似DP，那个解法很好，集合思想

如果数据很大的时候，可以用二进制进行优化，那就高级了

MacOS下，第一次遇到 Bus error 10的错误，知道是栈溢出，查了3小时也没整明白。最后用printf大法，打断点看执行过程，一下就揪出了问题（for循环里面i打成了j，溺）

---

## 作者：liyifan24 (赞：1)

这道题其实就是DFS，也不知道那么多人为什么用BFS做，稍微判断加搜索一下就过了：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum[101],a[101],mina=100001,ans,b[101][101],k,s,r[101],o[101];
void dfs(int x)
{
	int l=0,i;
	for(i=1;i<=n;i++)
	{
		if(sum[i]<a[i])
		{
			l=1;//判断是否符合要求 
		}
	}
	if(l==0)
	{
		if(ans<mina)//更新
		{
			mina=ans;
			for(i=1;i<=ans;i++)
			{
				r[i]=o[i];//赋值
			}
		}
		return;
	}	
	if(l==1)
	{
		ans++;
		o[ans]=x;
		for(i=1;i<=n;i++)
		{
			sum[i]=sum[i]+b[x][i];
		}
		for(i=1;i<=k-x+1;i++)
		dfs(x+i);//枚举所有方案 
		ans--;
		for(i=1;i<=n;i++)
		{
			sum[i]=sum[i]-b[x][i];
		}
	}
}
int main()
{
	int i,j;
	//freopen("holstein.in","r",stdin);
	//freopen("holstein.out","w",stdout);
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	cin>>k;
	for(j=1;j<=k;j++)
	{
		for(i=1;i<=n;i++)
		{
		    cin>>b[j][i];//二维要稍微处理一下
		}
	}
	dfs(0);
	cout<<mina-1<<" ";//注意这里千万要减一
	for(i=2;i<=mina;i++)
	{
		cout<<r[i]<<" ";//同理，从二开始枚举
	}
}
```

---

## 作者：天·三玖 (赞：1)

思想：随机化，从1开始增加种数p，对于种数p，随机枚举选p个维他命的情况。对于每一种枚举5000次即可，然后取最优解(事实上可以枚举对种数p总情况数的3/4可以优化，不过也很快了)

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<iomanip>
#include<map>
#include<vector>
#include<ctime>
#include<algorithm>
using namespace std;
#define RG register
#define IL inline
#define File(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
template<typename T>
T qget(void)
{
  T xi=0;
  char ch=getchar();
  bool f=false;
  while(ch<'0'||ch>'9')
    {
      if(ch=='-')f=1;
      ch=getchar( );
    }
  while( ch>='0'&&ch<='9')xi=xi*10+ch-48,ch=getchar();
  if(f)xi=-xi;
  return xi;
}
struct HAHA{//存枚举的状态
  short c[26];
  bool a[16];
  HAHA()
  {
    memset(c,0,sizeof(c));
    memset(a,0,sizeof(a));
  }
  bool operator < (HAHA b)
  {
    HAHA *a=this;
    for(int i=1;i<=25;i++)if(a->c[i]<b.c[i])return true;else if(a->c[i]>b.c[i])return false;
    return false;
  }
};
short a[16][26],need[26],n,g,ok;
bool xa[16];
void letrand(int n)//随机打乱
{
  for(int i=1;i<=n;i++)swap(xa[rand()%n+1],xa[rand()%n+1]);
}
HAHA check()
{
  HAHA c;
  ok=1;
  for(int i=1;i<=g;i++)if(xa[i]){for(int j=1;j<=n;j++)c.c[j]+=a[i][j];c.a[i]=1;}
  for(int i=1;i<=n;i++)if(c.c[i]<need[i]){ok=0;return c;}//是否满足要求
  return c;
}
void print(int p,HAHA q)
{
//  int p=0;
//  for(int i=1;i<=g;i++)if(q.a[i])p++;
  cout<<p<<" ";
  for(int i=1;i<=g;i++)if(q.a[i])printf("%d ",i);
  exit(0);
}
void work()
{
  int p=0;
  while(1)
    {
      ++p;//种数
      vector<HAHA>k;
      int u=5000;//枚举次数
      memset(xa,0,sizeof(xa));
      for(RG int i=1;i<=p;i++)xa[i]=1;
      for(RG int i=1;i<=u;i++)
        {
          letrand(g);//打乱
          HAHA p1=check();//判断并存结果
          if(ok)k.push_back(p1);//满足要求
        }
      if(k.size()>0)
        {
          sort(k.begin(),k.end());//其实可以不用sort
          print(p,k[0]);
        }
    }
}
int main()
{
  srand(time(NULL));//随机数种子
  n=qget<int>();
  for(RG int i=1;i<=n;i++)need[i]=qget<int>();
  g=qget<int>();
  for(RG int i=1;i<=g;i++)for(RG int j=1;j<=n;j++)a[i][j]=qget<int>();
  work();
  return 0;
}
```

---

## 作者：ergeda (赞：1)

```cpp
//只要加一个小小的剪枝即可
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#define inf 999999999
using namespace std;
const int maxn=100010;
int a[maxn];
int m,n;
int b[101][101];
bool p[maxn];
int ans=inf;
int top[maxn];//用来保存答案
int cnt;
int c[maxn],coot;
bool pd;
bool flag2;
void dfs(int sum,int h){
    bool flag=0;
    for(int i=1;i<=m;i++){
        if(a[i]>0){flag=1;break;}
    }
    if(!flag){
        if(sum<ans){//根据dfs的性质，不用比较sum==ans的情况
            coot=cnt;
            ans=sum;
            for(int i=1;i<=cnt;i++){
                c[i]=top[i];
            }
        }
        return;
    }
    for(int i=h+1;i<=n;i++){//从h+1这一行开始往下搜，这就是那个小小的剪枝
        if(!p[i]){
            p[i]=1;
            for(int j=1;j<=m;j++){
                a[j]-=b[i][j];
            }
            top[++cnt]=i;
            dfs(sum+1,i);//下次搜索只往下搜，避免搜回来导致超时
            --cnt;//回溯
            p[i]=0;
            for(int j=1;j<=m;j++){
                a[j]+=b[i][j];
            }
        }
    }
}
int main(){
    int i,j,k;
    scanf("%d",&m);
    for(i=1;i<=m;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            scanf("%d",&b[i][j]);
        }
    }
    dfs(0,0);
    printf("%d ",coot);
    for(i=1;i<coot;i++){
        printf("%d ",c[i]);
    }
    printf("%d\n",c[coot]);
    return 0;
}
```

---

## 作者：蒟蒻lxy (赞：1)

## 题解 [P1460 【健康的荷斯坦奶牛 Healthy Holsteins 】](https://www.luogu.org/problemnew/show/P1460)

作者： [刘星宇0508](https://www.luogu.org/space/show?uid=34500)


------------
**思路：用二进制枚举子集，从而找到最优解**

------------
代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,wtm[505],g,sl[505][505],ans=0x7f7f7f7f,a[50005][505],an;
// n:维他命种数  wtm:维他命需求量  g:饲料种数  sl[i][j]：第i种饲料中第j种维他命的含量
// ans:需求的最小个数  a:保存结果  an:保存结果的二进制子集 
int read()//快读，请忽略 
{
    int x=0,f=1;//快读，请忽略
    char c=getchar();
    while(!isdigit(c))
	{
		if(c=='-')//快读，请忽略
			f=-1;
		c=getchar();//快读，请忽略
	}
    while(isdigit(c))//快读，请忽略
	{
		x=x*10+c-'0';//快读，请忽略
		c=getchar();
	}
    return x*f;//快读，请忽略
}
int main()
{
	n=read();//读入 
	for(int i=1;i<=n;i++)
		wtm[i]=read();//还是读入 
	g=read();//仍然是读入 
	for(int i=1;i<=g;i++)
		for(int j=1;j<=n;j++)
			sl[i][j]=read();//依旧是读入 
	for(int i=0;i<(1<<g);i++)
	//二进制枚举子集，从全部不取（000000000……）到全取（111111……） 
	{
		int la=0,_wtm[505],dontok=0;
		// l:这次选择的饲料，_wtm:这次的总维他命量 
		// dontok:标记是否不行 
		memset(_wtm,0,sizeof(_wtm));//置0 
		for(int j=0;j<g;j++)//枚举第j+1位 
			if(i&(1<<j))
			/*
			如果第j+1位上是1（即为要取） 
			那 i&(1<<j)的值为1
			反之为0 
			&号即为按为与
			1<<j的二进制值为：100000……(j个0) 
			*/ 
			{
				a[i][++la]=j;//记录 
				for(int k=1;k<=n;k++)
					_wtm[k]+=sl[j+1][k];//增加总维他命量 
			}
		for(int j=1;j<=n;j++)
			if(_wtm[j]<wtm[j])//如果维他命不够 
			{
				dontok=1;//标记：不行 
				break;//退出 
			}
		if(dontok)//如果不行，执行下一个 
			continue;
		if(ans>la)//记录最小答案 
		{
			ans=la;//记录最小答案饲料个数 
			an=i;//记录最小答案的二进制子集 
		}
	}
	cout << ans <<' ';//输出 
	for(int i=1;i<=ans;i++) 
		cout << a[an][i]+1 <<' ';//再次输出 
	cout << endl;
	return 0;
}

```

**PS:**
```    之前程序炸了，显示TLE，于是我打了快读，后来才发现是BUG，于是快读就留着了。。。```

---


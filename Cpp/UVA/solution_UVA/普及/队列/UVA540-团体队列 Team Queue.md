# 团体队列 Team Queue

## 题目描述

有 $t$ 个团队的人正在排长队。每有一个新来的人时，他会从队首开始向后搜寻，如果发现有队友正在排队，他就会插队到他队友的身后；如果没有发现任何一个队友排队，他就只好站在长队的队尾。

输入每个团队中所有队员的编号，要求支持如下 $3$ 种指令：

`ENQUEUE x`：编号为 $x$ 的人进入长队。

`DEQUEUE`：长队的队首出队。

`STOP`：停止模拟。

对于每个 `DEQUEUE` 指令，输出出队的人的编号。

## 样例 #1

### 输入

```
2
3 101 102 103
3 201 202 203
ENQUEUE 101
ENQUEUE 201
ENQUEUE 102
ENQUEUE 202
ENQUEUE 103
ENQUEUE 203
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
STOP
2
5 259001 259002 259003 259004 259005
6 260001 260002 260003 260004 260005 260006
ENQUEUE 259001
ENQUEUE 260001
ENQUEUE 259002
ENQUEUE 259003
ENQUEUE 259004
ENQUEUE 259005
DEQUEUE
DEQUEUE
ENQUEUE 260002
ENQUEUE 260003
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
STOP
0```

### 输出

```
Scenario #1
101
102
103
201
202
203

Scenario #2
259001
259002
259003
259004
259005
260001```

# 题解

## 作者：Punny (赞：25)

**先看代码**

```cpp
#include<iostream>
#include<queue>
#include<cstdio>
#include<cstdlib>
using namespace std;
int n,team[1000001],w;
string s;
int main()
{
//	freopen("out.txt","w",stdout);
    while(1)
    {
        w++;
        int fl=0;
        queue<int>q;
        queue<int>p[1001];
        scanf("%d",&n);
        if(n==0)
        return 0;
        for(int i=1;i<=n;i++)
        {
            int num;
            scanf("%d",&num);
            for(int j=1;j<=num;j++)
            {
                int k;
                scanf("%d",&k);
                team[k]=i;
            }
        }
        while(1)
        {
        	cin>>s;
            int num;
            if(s[0]=='E')
            {
                scanf("%d",&num);
                if(p[team[num]].empty())
                {
                    q.push(team[num]);
                    p[team[num]].push(num);
                }
                else
                p[team[num]].push(num);
            }
            if(s[0]=='D')
            {
                if(fl==0)
                    printf("Scenario #%d\n",w),fl=1;
                    while(p[q.front()].empty())
                    {
                    	q.pop();
					}
                    printf("%d\n",p[q.front()].front());
                    p[q.front()].pop();
            }
            if(s[0]=='S')
            {
                printf("\n");
                break;
            }
        }
    }
    return 0;
}
```

本题的思路先讲一下：

我是用队列来做的，先建n+1个队列，一个队列q是储存每一个队伍的编号，之后p[1~n]个队列是用来储存每个队伍成员的编号的，再用一个数组team来存每个队员的所属的队伍team[队员编号]=队伍编号。

插入成员时先判断q队列里有没有这个成员所属于的队伍，没有就需要把队伍编号插入到q里，若有则把成员直接插入到他本队伍的p中。

出成员时，因为q队列已经记录了队伍的优先级，只要按照q队列里的队伍编号把此编号对应的p里的成员弹出即可，直到其所对应的p队列里为空，就把q队列中的这个队伍编号弹出。

注意输出格式

p队列不要开太大



---

## 作者：Sparda (赞：14)


**题目大意**
有t个团队的人排队，每有一个新来的人时，如果他有队友正在排队，那么他就会站在他队友的后面。如果没有队友，就站在队伍的最后面。

输入每个团队中所有队员的编号，要求支持如下3中指令： 

ENQUEUE x：编号为x的人进入长队；

DEQUEUE：长队的队首出队；

STOP：停止模拟。

对于每个DEQUEUE指令，输出出队的人的编号。

~~这道题给我的第一印象：这不就是平时的我在插队嘛。。。~~ 

那么。。。。。。就~~按照平时我的行为~~ 来模拟一下排（插）队吧！

**上样例！**

```
2
3 101 102 103
3 201 202 203
ENQUEUE 101
ENQUEUE 201
ENQUEUE 102
ENQUEUE 202
ENQUEUE 103
ENQUEUE 203
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
STOP
```


最开始队伍是空的，然后，一号团的101号大妈来了。

（此时，队伍顺序为：101.）

接着二号团201大爷也跟了过来。

（此时，队伍顺序为：101，201.）

接着，一号团的102号大妈也来了，不把二号团的大爷放眼里，站在了201号大爷前面。

（此时，队伍顺序为：101，102，201.）

二号团202号大爷见状，不好吭声，只好紧接在201号大爷之后。

（此时，队伍顺序为：101，102，201，202）

一号团又来一103号大姐，不把二团放眼里般站在了一团之后。

（此时，队伍顺序为：101，102，103，201，202）

二团最后203号大爷不急不慢走到了队尾。

（此时，队伍顺序为：101，102，103，201，202，203）

从样例和生活常识综合分析可得：无论后面来的人是谁，都可以插入到自己的团队内排在后面。

所以可以简单找到做题突破口：**将每个团体当成一个个体进行排队，然后再队每个团队内部进行一次排队。**

那么！用什么方法呢？

answer：都说了是排队了，那~~TMD~~ 肯定是用队列了啊！

队列是啥？![在这里插入图片描述](https://img-blog.csdnimg.cn/20190717200645555.png)
那么队列怎么写呢？

answer：用STL啊！

## STL大法吼啊！！！吼啊！！!

因为题目给了每个人的编号是<=999999的，所以，我用了类似桶排的方法记录了每个人所在队伍。

即：

```
int a[10000000];
for(int i = 0;i < n;++ i){
	scanf("%d",&hhh);
	for(int j = 0;j < hhh;++ j){
		scanf("%d",&x);
		a[x] = i;
	}
}
```
然后剩下的就只用对操作进行简单的模拟就好了！
下面附上完整代码！



```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring> 
#include <queue>
using namespace std;
int n;
queue<int> Q;
queue<int> q[1006];
char ch[30];
int a[10000000];
int x;
int f;
int k = 1;
int main(void){
	while(scanf("%d",&n)){
		if(n == 0)//结束标志，跳出循环
			break;
		cout << "Scenario #" << k<<endl;	
		k ++;
		memset(a,0,sizeof(a));
		for(int i = 1;i <= 1005;++ i){
			while(!q[i].empty())
				q[i].pop();
		}
			
		while(!Q.empty())
			Q.pop();
		int hhh;
		for(int i = 0;i < n;++ i){
			scanf("%d",&hhh);
			for(int j = 0;j < hhh;++ j){
				scanf("%d",&x);
				a[x] = i;
			}
		}//while开始到这里都是在初始化，因为有多组数据
		while(scanf("%s",&ch)){
			if(ch[0] == 'S')
				break;
			if(ch[0] == 'E'){
				scanf("%d",&x);
				if(q[a[x]].empty()){
					Q.push(x);
					q[a[x]].push(x);
				}//某个团队第一个人入队的情况。
				else{
					q[a[x]].push(x);//有队友直接插队！
				}
			}
			if(ch[0] == 'D'){
				printf("%d\n",q[a[Q.front()]].front());
				q[a[Q.front()]].pop();//出队！！！
				if(q[a[Q.front()]].empty())//这个团队走完了。
					Q.pop();
			}
		}
		cout << endl;
	}
	
	return 0;
}
```


码风较丑，请勿嘲笑。

---

## 作者：Anguei (赞：9)

一个不错的**队列套队列**模拟题。

## 思路
1. 开一个包含 $T$ 个队列的数组 $Q$。其中，$Q_0$ 表示所有小团队在整个大队列当中的排队顺序。$Q_1 - Q_t$ 表示 $t$ 个小团队内部的排队顺序。

2. 入队时，将该成员 push 进其所属的小团队队列当中去。如果小队列当中只有一个人，则表示他是该团队第一个排队成员，将团队 push 到 $Q_0$ 当中。

3. 出队时，把第一个团队的第一个成员出队。出队后如果该小团队大小为零，则表示他是最后一个该团队的成员。在 $Q_0$ 中把该团队 pop 掉。

## 核心代码
```cpp
const int T = 1000 + 5;
int t;
std::queue<int> q[T];
std::map<int, int> belong; // 使用 std::map 存储该成员所属团队编号。时间效率低，空间效率高。

void solution() {
	belong.clear();
	rep(i, 0, T - 1) while (!q[i].empty()) q[i].pop(); // 清空上次的数据
	rep(i, 1, t) {
		int n = read();
		rep(j, 1, n) {
            int num = read();
            belong[num] = i; 
        }
	}
	std::string s; while (std::cin >> s && s != "STOP") {
		if (s == "ENQUEUE") {
			int num = read();
			q[belong[num]].push(num); // 在该团队末尾排队
			if (q[belong[num]].size() == 1) q[0].push(belong[num]); // 该团队第一人
		} else if (s == "DEQUEUE") {
			int front = q[q[0].front()].front(); q[q[0].front()].pop();
			print(front), puts(""); // 最首位团队的队头出队
			if (q[belong[front]].empty()) q[0].pop(); // 是否需要删掉这个团队
		}
	}
}

// 注意输出格式
int kase = 0; while (std::cin >> t && t) printf("Scenario #%d\n", ++kase), solution(), puts("");
```

---

## 作者：Nempt (赞：6)

这个代码好理解！！！！先上为快：

```
#include <iostream>
#include<queue>
#include<map>
using namespace std;
#define MAX 1001
int main(){
    int t;
    int m=1;
    while(cin>>t && t){
        map<int,int> v;//建立队员到某队的映射
        for(int i=1;i<=t;i++){
            int n;
            cin>>n;
            while(n--){
                int x;
                cin>>x;
                v[x]=i;
            }
        }
        cout<<"Scenario #"<<m++<<endl;
        queue<int> team[MAX];
        queue<int> total;
        string op;
        while(cin>>op){
            if(op=="STOP")  break;
            if(op=="ENQUEUE"){
                int x;
                cin>>x;
                int t=v[x];		//首先找这个人对应的队列编号
                if(team[t].empty())     total.push(t);		//如果该队列目前还没有人，那么需要在total队列新增加一个队列号
                team[t].push(x);		//在team[t]加入新成员。
            }
            if(op=="DEQUEUE"){
                if(!total.empty()){
                    int t=total.front();		//首先从团里队列的front（第一支队伍）出发
                    cout<<team[t].front()<<endl;		
                    team[t].pop();				//弹出首个成员
                    if(team[t].empty())     total.pop();	//该队空了的话还需要把其队伍编号从total中移除。
                }
            }
        }
        cout<<endl;
    }
    return 0;
}

```
程序首先对队里的每个成员用map映射到其所在的队列。

程序第19行，定义了团体队列team；第20行定义了队列集合total（记录队伍编号）。

当输入“ENQUEUE”时，首先找这个人对应的队列编号，如果该队列目前还没有人，那么需要在total队列新增加一个队列号，同时需要在team[t]加入新成员。

当输入“DEQUEUE”时，首先从团里队列的front（第一支队伍）出发，弹出首个成员，接着还需要判断team[t]是否已空，空了的话还需要把其队伍编号从total中移除。


---

## 作者：陷语 (赞：4)

## 团体队列

**思路：**

题目首先会给出t个团队的元素，根据题意我们知道到了后面我们需要判断这个元素是否有队友，所以我们可以开一个数组来储存每个元素所对应的队列的号数，然后就可以直接判断自己是否能够去队友那个队列，如果可以就直接push进去，否则就新开一个队列，在此我们可以另开一个队列来维护每个队列的组号，以便完成 **DEQUEUE**这个询问，既将这个队列对头所储存的组号所对应的组的对头输出。

**代码：**

```cpp
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
const int N = 1050;
const int T = 1000050;

int t, k, x;
int team[T];
char c[20];
queue <int> que[N];

int main() {
	freopen("in.txt", "r", stdin);
	
	while(~scanf("%d", &t) && t != 0) {
		//read 
		que[0] = queue <int>();//初始化，可以理解为把这个队列赋为空队列 
		for(int i = 1; i <= t; ++i) {
			scanf("%d", &x);
			int temp;
			while(x--) {
				scanf("%d", &temp);
				team[temp] = i;//储存这个数所在的组的号数 
			}
			que[i] = queue <int>();
		}
		
		printf("Scenario #%d\n", ++k);
		while(~scanf("%s", c) && c[0] != 'S') {
			
			if(c[0] == 'E') {
				scanf("%d", &x);
				if(que[team[x]].empty()) que[0].push(team[x]);//新增一队 
				que[team[x]].push(x); 
			}
			else {
				int p = que[0].front();
				printf("%d\n", que[p].front());
				que[p].pop();
				if(que[p].empty()) que[0].pop();
			}
		}
		puts("");
	}
	return 0;
}
```

写完后的感受：**~~初始化太重要了~~**

---

## 作者：ZRHan (赞：2)

本蒟蒻第一篇题解。

[UVA540 团体队列 Team Queue](https://www.luogu.com.cn/problem/UVA540)

可以想到模拟队列，但是插入操作无法O(1)解决。

可以发现同一小组的成员只会出现在队列中的连续一段，所以对每个小组各自维护一个队列，表示该小组段的细节。然后再维护一个总队列，里边放小组编号，表示各个小组段在队列中的顺序。

## 代码

```cpp
#include<cstdio>
#include<vector>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxid = 1e6+5, maxt = 1005;
int group[maxid];  //group[i]表示编号为i的人所在的小组编号 
queue <int> base;  //维护各个小组段在队列中的顺序 
queue <int> q[maxt];  //q[i]维护编号为i的小组那段队列

char ins[20];

int t;

void initt()  //对每组询问初始化 
{
	for(int i=1; i<=1000; ++i)
	{
		while(!q[i].empty()) q[i].pop();
	}
	while(!base.empty()) base.pop();
	memset(group, 0, sizeof(group));
}


int main()
{
	int qwq=0;
	while(1)
	{
		initt();
		++qwq;
		scanf("%d", &t);
		if(t==0)
		{
			return 0;
		}
		printf("Scenario #%d\n", qwq);
		for(int i=1, n; i<=t; ++i)
		{
			scanf("%d", &n);
			for(int j=1, x; j<=n; ++j)
			{
				scanf("%d", &x);
				group[x] = i;
			}
		}
		
		while(1)
		{
			scanf("%s", ins);
			if(ins[0] == 'E')
			{
				int x, gro;
				scanf("%d", &x);
				gro = group[x];
				if(q[gro].empty())  //如果这个小组还没有人在队列中，那么把该小组的编号放进base队列 
				{
					base.push(gro);
				}
				q[gro].push(x);
			}
			else if(ins[0] == 'D')
			{
				int gro = base.front();
				int peo = q[gro].front();
				printf("%d\n", peo);
				q[gro].pop();
				if(q[gro].empty())  //如果这个小组没人了，那么把小组编号从base中丢掉 
				{
					base.pop();
				}
			}
			else if(ins[0] == 'S')
			{
				printf("\n");  //注意格式 
				break;
			}
		}
	}
	return 0;
}
```


---

## 作者：MONIEN (赞：2)

# 谁道人生无再少，门前流水尚能西。
***

~~由于不太会用队列~~打了一个小小的模拟，思路其实很简单（题目怎么说就怎么做呗），附上变量说明：

> * #### $team[i][j]$ 代表团队 $i$ 中的 $j$ 成员
>
> * #### $b[i]$ 用于判断 $i$ 团队中是否有成员在队列中
>
> * #### $array[i][j]$ 表示在队列中的团队 $[i]$ 里的成员 $j$

以及有详细注释的代码：

***
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<queue>
#define Maxn 1005
using namespace std;
int k,t;
int team[Maxn][Maxn],b[Maxn],array[Maxn][Maxn],order[Maxn];
void preset()
{
    memset(team,-1,sizeof(team));
    memset(b,-1,sizeof(b));
    memset(array,-1,sizeof(array));
    memset(order,-1,sizeof(order));
    for(int i=0;i<Maxn;i++) array[i][0]=0;//用于记录每个team在队列中的人数
    order[0]=0;//用于记录在队列中的团队个数
}
int search(int len,int mem)
{
    for(int i=1;i<=t;i++)
        for(int j=1;j<=len;j++)
        {
            if(team[i][j]==mem) return i;
            else if(team[i][j]==-1) break;//一个小小的优化
        }
    return 0;
};
int main()
{
    ios::sync_with_stdio(false);
    while(cin>>t,t!=0)
    {
        k++;
        cout<<"Scenario #"<<k<<endl;
        preset();//预处理（初始化）
        int n,len=0;
        for(int i=1;i<=t;i++)
        {
            cin>>n;
            for(int j=1;j<=n;j++) cin>>team[i][j];
            len=max(len,n);//一个小小的记录（其实无关紧要反正时间复杂度还是很高）
        }
        string s;
        while(cin>>s,s!="STOP")
        {
            int tmp,p;
            if(s=="ENQUEUE")
            {
                cin>>tmp;
                p=search(len,tmp);//找出所在团队
                if(b[p]==1) array[p][++array[p][0]]=tmp;//有队友就直接插入
                else
                {
                    order[++order[0]]=p;
                    array[p][++array[p][0]]=tmp;
                    b[p]=1;
                }//没有队友代表这是一个新加入的团队，在order中插入团队编号
            }
            else if(s=="DEQUEUE")
            {
                    for(int i=1;i<=order[0];i++)
                    {
                        if(array[order[i]][array[order[i]][0]]==-1)
                        {
                            b[order[i]]=-1;
                            for(int j=i;j<order[0];j++) order[j]=order[j+1];
                            order[order[0]]=-1;
                            order[0]--;
                            i--;
                        }//若已经没有队员则从order中剔除
                        else
                        {
                            for(int j=1;j<=array[order[i]][0];j++)
                                if(array[order[i]][j]!=-1)
                                {
                                    cout<<array[order[i]][j]<<endl;
                                    array[order[i]][j]=-1;
                                    break;
                                }
                            break;
                        }//若还有队员则从队首开始输出
                    }
            }
        }
        cout<<endl;
    }
    return 0;
}
```
***

这道题就在愉快的模拟中结束啦！（逃

***
_2019-08-08 Update_
***

***
> # $END$
***

---

## 作者：mol茶蛋糕 (赞：2)

这道题就是一道**模拟**题。  

只需要开两组队列，一组记录每一个team中的已经排队的人的情况，另一组记录总的队伍中每一对的排列情况。  

当出队时，先判断大队伍顶部的team中是否还有人，没人就需要把大队伍中的pop掉，直到有一个team中有人。  

且这一道题一定要注意
# 格式！  
~~~
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
struct node{
	queue<int> q;
	bool flag;
}a[1003];
int tq[1000001];
queue<int> v;
void init()
{
	for(int i=1;i<=1001;i++)
	{
		while(!a[i].q.empty()) a[i].q.pop();
		a[i].flag=0;
	}
	while(!v.empty())
		v.pop();
	memset(tq,0,sizeof tq);
}
int main()
{
	int n,k=0;
	while(~scanf("%d",&n)&&n)
	{
		k++;
		printf("Scenario #%d\n",k);
		init();
		for(int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			for(int j=1;j<=x;j++)
			{
				int g;
				scanf("%d",&g);
				tq[g]=i;
			}
		}
		char s[10];
		while(scanf("%s",s))
		{
			if(s[0]=='S')
			{
				putchar('\n');
				break;
			}
//			cout<<s[0]<<endl;
			if(s[0]=='E')
			{
				int gg;
				scanf("%d",&gg);
				int team=tq[gg];
				a[team].q.push(gg);
				if(a[team].flag==0)
				{
					v.push(team);
					a[team].flag=1;
				}
			}
			else if(s[0]=='D'&&!v.empty())
			{
				while(a[v.front()].q.empty())
				{
					a[v.front()].flag=0;
					v.pop();
				}
				printf("%d\n",a[v.front()].q.front());
				a[v.front()].q.pop();
			}
		}
	}
	return 0;
}
~~~


---

## 作者：LB_tq (赞：1)

# Solution
直观的想法是开一个队列，然后存储每个人的编号。但是这样会导致插入时耗时过长。

那么如何进行方便地插入呢？考虑题意。只有有队友的才能插队。
**所以我们可以用队列维护每个组的编号，之后开n个小队列存储队列里每个小组中人的编号。**

当执行ENQUEUE操作时，判断这个人所对应的小组的队列中是否有人，若有，直接插入小组队列；若没有，同时插入小组编号队列。

当执行DEQUEUE操作时，直接输出小组编号队列队头所对应小组的队头。若小组中没有人了，则将小组编号弹出。

b[i]代表编号为i的人的小组，a[i][j]代表第i个小组的队列。

# Code
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
const int maxn=1e3+10;
const int maxm=1e6+10;
using namespace std;
int n,k,a[maxn][maxn],h[maxn],t[maxn],b[maxm];
int q[maxn],t1,h1;
string s;
int fr(){
	char ch=getchar();
	while(ch>'9'||ch<'0')
		ch=getchar();
	int sum=ch-'0';
	while((ch=getchar())>='0'&&ch<='9')
		sum=(sum<<3)+(sum<<1)+ch-'0';
	return sum;
}
void csh(){
	t1=0;
	h1=1;
	memset(t,0,sizeof(t));
	memset(h,0,sizeof(h));
}
int main(){
	int x,y;
	while(1){
		n=fr();
		if(n==0)
			break;
		k++;
		printf("Scenario #%d\n",k);
		for(int i=1;i<=n;i++){
			x=fr();
			for(int j=1;j<=x;j++){
				y=fr();
				b[y]=i;
			}
		}
		csh();
		while(1){
			cin>>s;
			if(s=="STOP")
				break;
			else if(s=="ENQUEUE"){
				x=fr();
				if(h[b[x]]==t[b[x]])
					q[++t1]=b[x];
				a[b[x]][++t[b[x]]]=x;
			}
			else{
				h[q[h1]]++;
				printf("%d\n",a[q[h1]][h[q[h1]]]);
				if(h[q[h1]]==t[q[h1]])
					h1++;
			}
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：fls233666 (赞：1)

这是一道很经典的队列练习题，题目中点明了是与队列有关的题目。但是，我们发现，如果只用一个队列是无法实现的。因为当一个团队的第二个人进入队列时，要**插入**到已经在队列中的第一个人的后面。这种中间插入的操作队列是肯定做不到的，这时候要怎么办？

这时我们发现：上述的**插入**操作也是符合队列性质的。也就是说，一个小组的人进入队列和出队列是符合队列的先进先出性质的。

那么，我们可以把一个小组的人看成**一个小队列**，当小组的第一个人进入到队列中时，**把这个小队列对应的编号插入到大队列中**；当小组的最后一个人出了队列时，**把这个小队列的编号从大队列中出队**。这样，我们就实现了**队列套队列**。

对上述思想进行对应的程序实现，就得到了下面的这段代码：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<map>
#include<string>

#define rgt register int

using namespace std;

const int mxn = 1010; 

queue <int> zz;   //大队列
queue <string> fz[mxn];   //小队列

map <string,int> zb;   //存储每个编号的人所在的小组编号

int main()
{
	int n,tt=1,pz;
	cin>>n;
	string str;
	while(n){
		printf("Scenario #%d\n",tt);
		tt++;
        //开始一组新数据
        
		zb.clear(); //清空上一组数据残留的
		for(rgt len,i=1;i<=n;i++){
			cin>>len;  //读入小组的长度
			while(!fz[i].empty())
				fz[i].pop();   //清空上一组数据残留的
			for(rgt j=1;j<=len;j++){
				cin>>str;   //读入每个人的编号
				zb[str]=i;   //存储
			}
		}
        
        //读入操作字符串
		cin>>str;
		while(str!="STOP"){
        
				if(str=="ENQUEUE"){  //进队
					cin>>str;   //读入编号
					pz=zb[str];   //找到组别
					if(fz[pz].empty())
						zz.push(pz);   //如果没有人在大队列中，小队列加入大队列末尾
					fz[pz].push(str);   //进入小队列
				}
                
				if(str=="DEQUEUE"){   //出队
					pz=zz.front();   //找到大队列队首的小队列
					cout<<fz[pz].front()<<endl;   //输出队头
					fz[pz].pop();  //小队列中的人出队
					if(fz[pz].empty())   //如果小队列为空，出大队列
						zz.pop();
				}
                
			cin>>str;   //读入新操作
		}
		cout<<endl;
        
		while(!zz.empty())
			zz.pop();   //清空大队列
            
		cin>>n;  //开始新的一组数据
	}
	return 0;
}

```


---

## 作者：圣光天子 (赞：0)

建一个大队列存在队中的小组，再建N个队列存每个小组中在队中的人，每一次出队时将大队列队头小组的队列队头元素出队。

代码（没用STL的循环队列）
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;
#define N 1005
int n,x;
int team[1000000],numt[N];
int dl[5000][N];
int tdl[N];
int head[N],tail[N],thead,ttail;
int num;
string s;

int main(){
    while ("QAQ"=="QAQ")
    {
        scanf("%d",&n);
        if (n==0) break;
        num++;
        printf("Scenario #%d\n",num);
        for (int i=1; i<=n; i++)
        {
            scanf("%d",&numt[i]);
            for (int j=1; j<=numt[i]; j++)
            {
                scanf("%d",&x);
                team[x]=i;
            }
        }
        thead=1; ttail=0; 
        memset(tail,0,sizeof(tail));
        memset(head,0,sizeof(head));
        while ("QwQ"=="QwQ")
        {
            cin >> s;
            if (s=="STOP") break;
            if (s=="ENQUEUE") 
            {
                scanf("%d",&x);
                if (head[team[x]]==tail[team[x]])
                {
                    ttail++;
                    tdl[ttail]=team[x];
                }
                tail[team[x]]++;
                dl[team[x]][tail[team[x]]]=x;
            }
            if (s=="DEQUEUE")
            {
                head[tdl[thead]]++;
                printf("%d\n",dl[tdl[thead]][head[tdl[thead]]]);
                if (head[tdl[thead]]==tail[tdl[thead]])
                    thead++;
            }
        }
        printf("\n");
    }
}
```

---

